#include "QuickStartWidget.h"
#include "ui_QuickStartWidget.h"

#include "bytertc_video.h"
#include "bytertc_room.h"

#include "Config.h"
#include "Utils.h"

#include <QDebug>
#include <QMessageBox>

/**
* 功能名称： VolcEngineRTC 快速开始
* 功能简单描述：快速跑通 ByteRTC 音视频通话功能
*
* 此功能涉及的API及回调：
*     createRTCVideo 创建引擎
*     destroyRTCVideo 销毁引擎
*     startAudioCapture 开启音频采集
*     startVideoCapture 开启视频采集
*     createRTCRoom 创建RTC房间
*     joinRoom 进入RTC房间
*     leaveRoom 离开RTC房间
*     destroy 销毁RTC房间
*
*     onRoomStateChanged 房间状态回调
*     onLeaveRoom 离房回调
*     onUserJoined 用户加入回调
*     onUserLeave  用户离开回调
*     onUserPublishStream 用户发流回调
*     onUserUnpublishStream 用户停止发流回调
*
*
* Demo实现时的逻辑
*    请按照界面给出的步骤开发音视频通话功能
*    为了展示简单，所有功能的token都由客户端生成，接口Utils::generateToken，请在真正接入时视具体情况而定
*/

QuickStartWidget::QuickStartWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QuickStartWidget)
{
    ui->setupUi(this);
    initConnections();
}

QuickStartWidget::~QuickStartWidget()
{
    onBtnLeaveRoomClicked();
    onBtnDestroyVideoClicked();
    delete ui;
}

//连接信号槽
void QuickStartWidget::initConnections()
{
    connect(ui->btn_createVideo, &QPushButton::clicked, this, &QuickStartWidget::onBtnCreateVideoClicked);
    connect(ui->btn_startCapture, &QPushButton::clicked, this, &QuickStartWidget::onBtnStartCaptureClicked);
    connect(ui->btn_joinroom, &QPushButton::clicked, this, &QuickStartWidget::onBtnJoinRoomClicked);
    connect(ui->btn_destroyroom, &QPushButton::clicked, this, &QuickStartWidget::onBtnLeaveRoomClicked);
    connect(ui->btn_destroyvideo, &QPushButton::clicked, this, &QuickStartWidget::onBtnDestroyVideoClicked);
    connect(ui->btn_setLocalView, &QPushButton::clicked, this, &QuickStartWidget::onBtnSetLocalViewClicked);

}

//创建引擎
void QuickStartWidget::onBtnCreateVideoClicked() 
{
    if (m_video == nullptr) {
        m_handler.reset(new ByteRTCEventHandler());
        m_video = bytertc::createRTCVideo(g_appid.c_str(), m_handler.get(), nullptr);

        QString str_log = "createRTCVideo";
        ui->widget_log->appendAPI(str_log);
        if (m_video == nullptr) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("CreateRTCVideo error"), QMessageBox::Ok);
            box.exec();
            return;
        }
    }
    else {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("RTCVideo has been created."), QMessageBox::Ok);
        box.exec();
        return;
    }
}

//开始采集音视频
void QuickStartWidget::onBtnStartCaptureClicked()
{
    if (m_video) {
        m_video->startAudioCapture();
        m_video->startVideoCapture();
        QStringList str_log = { "startAudioCapture", "startVideoCapture" };
        ui->widget_log->appendAPI(str_log);
    }
    else {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("RTCVideo has't been created."), QMessageBox::Ok);
        box.exec();
        return;
    }
}

//进房
void QuickStartWidget::onBtnJoinRoomClicked()
{
    if (m_video == nullptr) {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("RTCVideo has't been created."), QMessageBox::Ok);
        box.exec();
        return;
    }

    if (m_room == nullptr) {
        std::string roomid, uid, token;
        int ret = 0;
        QString str_error;
        roomid = ui->lineEdit_room->text().toStdString();
        uid = ui->lineEdit_uid->text().toStdString();
        if (!Utils::checkIDValid(QString::fromStdString(roomid), QStringLiteral("房间id"), str_error)) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("roomid is error."), QMessageBox::Ok);
            box.exec();
            return;
        }
        if (!Utils::checkIDValid(QString::fromStdString(uid), QStringLiteral("uid"), str_error)) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("uid is error."), QMessageBox::Ok);
            box.exec();
            return;
        }
        m_roomHandler = createRoomHandler(roomid, uid);
        token = Utils::generateToken(roomid, uid);
        m_room = m_video->createRTCRoom(roomid.c_str());
        ui->widget_log->appendAPI("createRTCRoom");
        if (m_room == nullptr) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("createRTCRoom error"), QMessageBox::Ok);
            box.exec();
            return;
        }

        m_room->setRTCRoomEventHandler(m_roomHandler.get());
        ui->widget_log->appendAPI("setRTCRoomEventHandler");

        bytertc::UserInfo uinfo;
        uinfo.uid = uid.c_str();
        uinfo.extra_info = nullptr;
        bytertc::RTCRoomConfig config;
        config.is_auto_publish = true;
        config.is_auto_subscribe_audio = true;
        config.is_auto_subscribe_video = true;
        config.room_profile_type = bytertc::kRoomProfileTypeCommunication;
        ret = m_room->joinRoom(token.c_str(), uinfo, config);
        ui->widget_log->appendAPI("joinRoom");

        if (ret < 0) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("joinRoom error, ret=") + QString::number(ret), QMessageBox::Ok);
            box.exec();
            return;
        }
    }
}

//离房
void QuickStartWidget::onBtnLeaveRoomClicked()
{
    if (m_video == nullptr) {
        return;
    }
    if (m_room) {
        m_room->leaveRoom();
        m_room->destroy();
        m_room = nullptr;
    }
    m_remote_rendered = false;

    ui->widget_log->appendAPI("leaveRoom");
    ui->widget_log->appendAPI("destroy");
}

//销毁引擎
void QuickStartWidget::onBtnDestroyVideoClicked()
{
    QStringList list = {"stopAudioCapture", "stopVideoCapture", "destroyRTCVideo"};
    if (m_video) {
        if (m_room) {
            m_room->leaveRoom();
            m_room->destroy();
            m_room = nullptr;
            list = QStringList{ "leaveRoom", "destroy" } + list;
        }
        
        m_video->stopAudioCapture();
        m_video->stopVideoCapture();
        bytertc::destroyRTCVideo();
        m_video = nullptr;
        ui->widget_log->appendAPI(list);
    }
    m_remote_rendered = false;
}

//设置本地视频渲染窗口
void QuickStartWidget::onBtnSetLocalViewClicked()
{
    int ret = 0;
    if (m_video == nullptr) {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("RTCVideo has been created."), QMessageBox::Ok);
        box.exec();
        return;
    }
    else {
        bytertc::VideoCanvas cas;
        cas.background_color = 0x00000000;
        cas.render_mode = bytertc::kRenderModeFit;
        cas.view = (void*)ui->widget_local->getWinId();
        ui->widget_local->setUserInfo(ui->lineEdit_room->text().toStdString(), ui->lineEdit_uid->text().toStdString());
        ret = m_video->setLocalVideoCanvas(bytertc::kStreamIndexMain, cas);
        ui->widget_log->appendAPI("setLocalVideoCanvas");
        if (ret < 0) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("setLocalVideoCanvas error, ret=") + QString::number(ret), QMessageBox::Ok);
            box.exec();
        }
    }
}

//连接来自RTC Room的信号槽
std::unique_ptr<ByteRTCRoomHandler> QuickStartWidget::createRoomHandler(std::string roomid, std::string uid)
{
    std::unique_ptr<ByteRTCRoomHandler> roomH = std::make_unique<ByteRTCRoomHandler>(roomid, uid);
    connect(roomH.get(), &ByteRTCRoomHandler::sigRoomStateChanged, this, &QuickStartWidget::onSigRoomStateChanged);
    connect(roomH.get(), &ByteRTCRoomHandler::sigUserPublishStream, this, &QuickStartWidget::onSigUserPublishStream);
    connect(roomH.get(), &ByteRTCRoomHandler::sigUserUnPublishStream, this, &QuickStartWidget::onSigUserUnPublishStream);
    connect(roomH.get(), &ByteRTCRoomHandler::sigUserJoined, this, &QuickStartWidget::onSigUserJoined);
    connect(roomH.get(), &ByteRTCRoomHandler::sigUserLeave, this, &QuickStartWidget::onSigUserLeave);
    connect(roomH.get(), &ByteRTCRoomHandler::sigLeaveRoom, this, &QuickStartWidget::onSigLeaveRoom);
    connect(roomH.get(), &ByteRTCRoomHandler::sigTokenWillExpire, this, [this]() {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("Token will expire,please updateToken"), QMessageBox::Ok);
        box.exec();
        });
    return roomH;
}

//进房状态
void QuickStartWidget::onSigRoomStateChanged(std::string roomid, std::string uid, int state, std::string extra_info)
{
    QString log_str;
    log_str = QString("onRoomStateChanged,roomid:")
        + QString::fromStdString(roomid)
        + ",uid:" + QString::fromStdString(uid)
        + ",state:"  + QString::number(state)
        + ",extra:" + QString::fromStdString( extra_info);
    ui->widget_log->appendCallback(log_str);
}

//远端用户发流
void QuickStartWidget::onSigUserPublishStream(std::string roomid, std::string uid, bytertc::MediaStreamType type)
{
    QString log_str = QString("onUserPublishStream,roomid:")
        + QString::fromStdString(roomid)
        + ",uid:" + QString::fromStdString(uid)
        + ",type:" + QString::number(type);
    ui->widget_log->appendCallback(log_str);

    if (!m_remote_rendered) {
        bytertc::VideoCanvas cas;
        bytertc::RemoteStreamKey key;
        key.room_id = roomid.c_str();
        key.user_id = uid.c_str();
        key.stream_index = bytertc::kStreamIndexMain;
        cas.background_color = 0;
        cas.render_mode = bytertc::kRenderModeFit;
        cas.view = nullptr;
        m_video->setRemoteVideoCanvas(key, cas);

        cas.view = (void*)ui->widget_remote->getWinId();
        m_video->setRemoteVideoCanvas(key, cas);

        ui->widget_remote->setUserInfo(roomid, uid);
        m_remote_rendered = true;
    }
}

//远端用户停止发流
void QuickStartWidget::onSigUserUnPublishStream(std::string roomid, std::string uid, bytertc::MediaStreamType type, bytertc::StreamRemoveReason)
{
    QString log_str = QString("onUserUnPublishStream,roomid:")
        + QString::fromStdString(roomid)
        + ",uid:" + QString::fromStdString(uid)
        + ",type:" + QString::number(type);
    ui->widget_log->appendCallback(log_str);

    if (m_remote_rendered) {
        if (ui->widget_remote->getRoomid() == roomid && ui->widget_remote->getUid() == uid) {
            bytertc::VideoCanvas cas;
            bytertc::RemoteStreamKey key;
            key.room_id = roomid.c_str();
            key.user_id = uid.c_str();
            key.stream_index = bytertc::kStreamIndexMain;
            cas.background_color = 0;
            cas.render_mode = bytertc::kRenderModeFit;
            cas.view = nullptr;
            m_video->setRemoteVideoCanvas(key, cas);
            ui->widget_remote->setUserInfo("", "");
            m_remote_rendered = false;
            ui->widget_remote->update();
        }
    }
}

//远端用户加入
void QuickStartWidget::onSigUserJoined(ByteRTCRoomHandler::UserInfo info, int)
{
    QString str = "onUserJoined, roomid:" + QString::fromStdString(info.roomid)
        + ",uid:" + QString::fromStdString(info.uid);
    ui->widget_log->appendCallback(str);
}

//远端用户离开
void QuickStartWidget::onSigUserLeave(std::string roomid, std::string uid, bytertc::UserOfflineReason)
{
    QString str = "onUserLeave, uid:" + QString::fromStdString(uid) + ",roomid:" + QString::fromStdString(roomid);
    ui->widget_log->appendCallback(str);
}

//离房
void QuickStartWidget::onSigLeaveRoom(std::string roomid, std::string uid, bytertc::RtcRoomStats)
{
    QString str = "onLeaveRoom, uid:" + QString::fromStdString(uid) + ",roomid:" + QString::fromStdString(roomid);
    ui->widget_log->appendCallback(str);
}
