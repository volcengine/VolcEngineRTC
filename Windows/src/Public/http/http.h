#pragma once

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>

struct HttpRequestData {
    QUrl url;
    QByteArray body;
    QNetworkAccessManager::Operation operation;
    QMap<QByteArray, QByteArray> headers;
};

class HttpReply : public QObject {
    Q_OBJECT

public:
    HttpReply(const HttpRequestData& request);
    int statusCode() const;
    QString reasonPhrase() const;
    QByteArray body() const;
    int isSuccessful() const;

private slots:
    void replyFinished();
    void replyError(QNetworkReply::NetworkError);

signals:
    void error(const QString& message);
    void finished(const HttpReply& reply);

private:
    QNetworkReply* getNetworkReply(const HttpRequestData& request);
    QMap<QByteArray, QByteArray> getDefaultRequestHeaders();
    void initReplyConnections();
    void emitError();
    void emitFinished();

    HttpRequestData req_;
    QNetworkReply* reply_;
    QByteArray bytes_;
};

class Http {

public:
    static Http& instance();
    Http() = default;
    ~Http() = default;

    HttpReply* get(const QUrl& url);
    HttpReply* post(const QUrl& url, const QByteArray& body, const QByteArray& contentType);
};
