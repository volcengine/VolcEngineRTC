#include "AudioMessage.h"
#include "ui_AudioMessage.h"

#include "bytertc_video.h"
#include "bytertc_room.h"
#include "Config.h"
#include "Resources.h"
#include "Utils.h"

#include <QMessageBox>
#include <QDebug>
#include <sstream>


AudioMessage::AudioMessage(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::AudioMessage)
{
    ui->setupUi(this);
    initUI();
    initRTCVideo();
    initConnects();
}

AudioMessage::~AudioMessage()
{
    cleanRTCVideo();
    delete ui;
}

void AudioMessage::initUI()
{
    QList<QWidget*> childWidgets = this->findChildren<QWidget*>();
    // 遍历子控件并设置样式表
    foreach(QWidget * childWidget, childWidgets) {
        QLabel* label = qobject_cast<QLabel*>(childWidget);
        if (label) {
            if (label->objectName() != "label_user_id") {
                label->setStyleSheet(APIDemo::str_qss_label);
            } else {
                label->setStyleSheet(APIDemo::str_qss_label_user_info);
            }
        }
        QLineEdit* edit = qobject_cast<QLineEdit*>(childWidget);
        if (edit) {
            edit->setStyleSheet(APIDemo::str_qss_text);
        }
    };

    ui->btn_join->setStyleSheet(APIDemo::str_qss_btn1);
    ui->btn_send->setStyleSheet(APIDemo::str_qss_btn2_3);
    ui->label_title->setStyleSheet(APIDemo::str_qss_label_ttile);

}

void AudioMessage::initRTCVideo()
{
    m_handler.reset(new ByteRTCEventHandler());
    connect(m_handler.get(), &ByteRTCEventHandler::sigStreamSyncInfoReceived, this, &AudioMessage::onSigStreamSyncInfoReceived);
    m_video = bytertc::createRTCVideo(g_appid.c_str(), m_handler.get(), nullptr);
    m_video->startAudioCapture();
    m_video->startVideoCapture();

    QStringList list = {"createRTCVideo", "startAudioCapture", "startVideoCapture"};
    appendAPI(list);

}

void AudioMessage::cleanRTCVideo()
{
    QStringList list;
    if (m_video) {
        if (m_room) {
            m_room->leaveRoom();
            m_room->setRTCRoomEventHandler(nullptr);
            m_room->destroy();
            m_room = nullptr;
            list = QStringList{"leaveRoom", "setRTCRoomEventHandler", "destroy"};
        }
        m_video->stopAudioCapture();
        m_video->stopVideoCapture();
        bytertc::destroyRTCVideo();

        m_video = nullptr;
        list = list + QStringList{ "stopAudioCapture", "stopVideoCapture", "destroyRTCVideo" };
        appendAPI(list);
    }
}

void AudioMessage::initConnects()
{
    connect(ui->btn_join, &QPushButton::clicked, this, &AudioMessage::onBtnJoinClicked);
    connect(ui->btn_send, &QPushButton::clicked, this, &AudioMessage::onBtnSendClicked);
}

std::unique_ptr<ByteRTCRoomHandler> AudioMessage::createRoomHandler(std::string roomid, std::string uid)
{
    std::unique_ptr<ByteRTCRoomHandler> roomH = std::make_unique<ByteRTCRoomHandler>(roomid, uid);
    connect(roomH.get(), &ByteRTCRoomHandler::sigRoomStateChanged, this, &AudioMessage::onSigRoomStateChanged);
    connect(roomH.get(), &ByteRTCRoomHandler::sigUserPublishStream, this, &AudioMessage::onSigUserPublishStream);
    connect(roomH.get(), &ByteRTCRoomHandler::sigUserUnPublishStream, this, &AudioMessage::onSigUserUnPublishStream);
    connect(roomH.get(), &ByteRTCRoomHandler::sigUserJoined, this, &AudioMessage::onSigUserJoined);
    connect(roomH.get(), &ByteRTCRoomHandler::sigUserLeave, this, &AudioMessage::onSigUserLeave);
    connect(roomH.get(), &ByteRTCRoomHandler::sigTokenWillExpire, this, [this]() {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("Token will expire,please updateToken"), QMessageBox::Ok);
        box.exec();
        });
    return roomH;
}


void AudioMessage::onBtnJoinClicked()
{
    if (ui->btn_join->text() == QStringLiteral("进房")) {
        QString qstr_user_name = ui->lineEdit_uid->text();
        QString qstr_room = ui->lineEdit_room->text();
        QString qstr_error;

        m_uid = qstr_user_name.toStdString();
        m_roomid = qstr_room.toStdString();

        if (!Utils::checkIDValid(qstr_user_name, QStringLiteral("用户名"), qstr_error)) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), "uid error " + qstr_error, QMessageBox::Ok);
            box.exec();
            return;

        }

        if (!Utils::checkIDValid(qstr_room, QStringLiteral("房间号"), qstr_error)) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), "roomid error " + qstr_error, QMessageBox::Ok);
            box.exec();
            return;
        }

        m_room = m_video->createRTCRoom(m_roomid.c_str());
        if (m_room == nullptr) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("createRTCRoom error, please check"), QMessageBox::Ok);
            box.exec();
            return;
        }

        bytertc::VideoCanvas cas;

        cas.view = (void*)ui->widget_1->getWinId();
        ui->widget_1->setUserInfo(m_roomid, m_uid);
        m_video->setLocalVideoCanvas(bytertc::kStreamIndexMain, cas);

        m_roomHandler = createRoomHandler(m_roomid, m_uid);
        m_room->setRTCRoomEventHandler(m_roomHandler.get());
        std::string token = Utils::generateToken(m_roomid, m_uid);
        bytertc::UserInfo userinfo;
        userinfo.uid = m_uid.c_str();
        bytertc::RTCRoomConfig config;
        config.is_auto_publish = true;
        config.is_auto_subscribe_audio = true;
        config.is_auto_subscribe_video = true;

        int ret = m_room->joinRoom(token.c_str(), userinfo, config);
        if (ret != 0) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("joinRoom error, please check"), QMessageBox::Ok);
            box.exec();
            return;
        }
        QStringList list = { "createRTCRoom", "setLocalVideoCanvas", "setRTCRoomEventHandler", "joinRoom" };
        appendAPI(list);

    }else {
        if (m_room) {
            m_room->leaveRoom();
            m_room->destroy();
            m_room = nullptr;
        }

        ui->btn_join->setText(QStringLiteral("进房"));
        QStringList list = { "leaveRoom", "destroy"};
        appendAPI(list);
    }

}

void AudioMessage::onBtnSendClicked()
{
    if (m_video == nullptr) return;
    std::string str = ui->textEdit_send->toPlainText().toStdString();
    if (str.empty()) {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QStringLiteral("发送内容不能为空"), QMessageBox::Ok);
        box.exec();
        return;
    }
    bytertc::StreamSycnInfoConfig config;
    config.stream_index = bytertc::kStreamIndexMain;
    config.stream_type = bytertc::kSyncInfoStreamTypeAudio;
    config.repeat_count = 0; //0表示不重复
    int ret = m_video->sendStreamSyncInfo((const uint8_t*)str.c_str(), str.size(), config);
    if (ret < 0) {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QStringLiteral("sendStreamSyncInfo error:") + QString::number(ret), QMessageBox::Ok);
        box.exec();
    }

    appendAPI("sendStreamSyncInfo");
}

void AudioMessage::onSigRoomStateChanged(std::string roomid, std::string uid, int state, std::string extra_info)
{
    std::stringstream log_str;
    log_str << std::string("onRoomStateChanged,roomid:")
            << roomid
            << ",uid:" << uid
            << ",state:" << std::to_string(state)
            << ",extra:" << extra_info;
    appendCallback(QString::fromStdString(log_str.str()));
    if (state == 0) {
        ui->btn_join->setText(QStringLiteral("离房"));
    }

}

void AudioMessage::onSigUserPublishStream(std::string roomid, std::string uid, bytertc::MediaStreamType type)
{
    QString log_str = QString("onUserPublishStream,roomid:")
                      + QString::fromStdString(roomid)
                      + ",uid:" + QString::fromStdString(uid)
                      + ",type:" + QString::number(type);
    appendCallback(log_str);

}

void AudioMessage::onSigUserUnPublishStream(std::string roomid, std::string uid, bytertc::MediaStreamType type, bytertc::StreamRemoveReason)
{
    QString log_str = QString("onUserPublishStream,roomid:")
                      + QString::fromStdString(roomid)
                      + ",uid:" + QString::fromStdString(uid)
                      + ",type:" + QString::number(type);
    appendCallback(log_str);

}

void AudioMessage::onSigUserJoined(ByteRTCRoomHandler::UserInfo info, int)
{
    QString str = "onUserJoined, uid:" + QString::fromStdString(info.uid) + ",roomid:" + QString::fromStdString(info.roomid);
    appendCallback(str);

}

void AudioMessage::onSigUserLeave(std::string roomid, std::string uid, bytertc::UserOfflineReason)
{
    QString str = "onUserLeave, uid:" + QString::fromStdString(uid) + ",roomid:" + QString::fromStdString(roomid);
    appendCallback(str);

}

void AudioMessage::onSigStreamSyncInfoReceived(ByteRTCEventHandler::Stru_RemoteStreamKey stream_key, bytertc::SyncInfoStreamType stream_type, std::string str)
{
    QString sss = "onStreamSyncInfoReceived, roomid:" + QString::fromStdString(stream_key.room_id)
                  + ",uid:" + QString::fromStdString(stream_key.user_id)
                  + ",message:" + QString::fromStdString(str);
    ui->textEdit_receive->append(sss);
    appendCallback(sss);
}
