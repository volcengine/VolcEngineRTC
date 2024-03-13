#include "http.h"

#include <iostream>
#include <QDebug>
#include <sstream>

HttpReply::HttpReply(const HttpRequestData& request)
    :req_(request) {

    std::stringstream stream;
    stream << QSslSocket::sslLibraryBuildVersionString().toStdString() <<",support:" <<  int(QSslSocket::supportsSsl());
    if (req_.url.isEmpty()) {
        qWarning() << "URL is empty";
    }
    reply_ = getNetworkReply(req_);
    initReplyConnections();
}

QNetworkReply* HttpReply::getNetworkReply(const HttpRequestData& request) {
    QNetworkRequest req(request.url);

    auto headers = getDefaultRequestHeaders();
    if (!request.headers.isEmpty()) headers = request.headers;

    for (auto it = headers.cbegin(); it != headers.cend(); ++it) {
        req.setRawHeader(it.key(), it.value());
    }

    QNetworkAccessManager* manager = new QNetworkAccessManager();
    manager->setRedirectPolicy(QNetworkRequest::NoLessSafeRedirectPolicy);
//    if (manager->networkAccessible() == QNetworkAccessManager::NotAccessible) {
//        manager->setNetworkAccessible(QNetworkAccessManager::Accessible);
//    }

    QNetworkReply* networkReply = nullptr;
    switch (request.operation) {
    case QNetworkAccessManager::GetOperation:
        networkReply = manager->get(req);
        break;
    case QNetworkAccessManager::PostOperation:
        networkReply = manager->post(req, request.body);
        break;
    default:
        qWarning() << "not handle this operation:" << request.operation;
    }

    return networkReply;
}

QMap<QByteArray, QByteArray> HttpReply::getDefaultRequestHeaders() {
    QMap<QByteArray, QByteArray> heads;
    heads.insert("Accept-Charset", "utf-8");
    heads.insert("Connection", "Keep-Alive");
    return heads;
}

void HttpReply::initReplyConnections() {
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    connect(reply_, &QNetworkReply::errorOccurred, this, &HttpReply::replyError,
        Qt::UniqueConnection);
#else
    connect(reply_, SIGNAL(error(QNetworkReply::NetworkError)),
        SLOT(replyError(QNetworkReply::NetworkError)), Qt::UniqueConnection);
#endif
    connect(reply_, &QNetworkReply::finished, this, &HttpReply::replyFinished, Qt::UniqueConnection);
}

void HttpReply::emitError() {
    const QString msg = req_.url.toString() + " " + QString::number(statusCode()) + " " + reasonPhrase();
    qDebug() << "Http:" << msg;
    if (!req_.body.isEmpty()) qDebug() << "Http:" << req_.body;
    emit error(msg);
    emitFinished();
}

void HttpReply::emitFinished() {
    reply_->disconnect();
    emit finished(*this);
    reply_->deleteLater();
}

void HttpReply::replyFinished() {
    if (isSuccessful()) {
        bytes_ = reply_->readAll();
    }
    emitFinished();
}

int HttpReply::isSuccessful() const {
    return statusCode() >= 200 && statusCode() < 300;
}

void HttpReply::replyError(QNetworkReply::NetworkError code) {

    if (reply_) {
        std::string ss = reply_->readAll().toStdString();
        
    }
    emitError();
    return;
}

int HttpReply::statusCode() const {
    return reply_->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
}

QString HttpReply::reasonPhrase() const {
    return reply_->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
}

QByteArray HttpReply::body() const {
    return bytes_;
}

Http& Http::instance() {
    static Http ins;
    return ins;
}

HttpReply* Http::get(const QUrl& url) {
    HttpRequestData req;
    req.url = url;
    req.operation = QNetworkAccessManager::Operation::GetOperation;
    return new HttpReply(req);
}

HttpReply* Http::post(const QUrl& url, const QByteArray& body, const QByteArray& contentType) {
    HttpRequestData req;
    req.url = url;
    req.body = body;
    req.operation = QNetworkAccessManager::Operation::PostOperation;

    QByteArray cType = contentType;
    if (cType.isEmpty()) cType = "application/x-www-form-urlencoded";
    req.headers.insert("Content-Type", cType);
    return new HttpReply(req);
}
