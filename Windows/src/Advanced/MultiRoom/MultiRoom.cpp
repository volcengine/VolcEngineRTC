#include "MultiRoom.h"
#include "ui_MultiRoom.h"

#include "bytertc_video.h"
#include "bytertc_room.h"

#include "Config.h"
#include "Utils.h"
#include "Resources.h"


#include <QDebug>
#include <QMessageBox>
#include <QRegularExpression>

#include <sstream>
#include <regex>
#include <vector>

/**
 * 功能名称： VolcEngineRTC 多房间
 * 功能简单描述：你可能需要让同一个用户加入多个 RTC 房间，同时收听/收看不同房间中的音视频，并在其中一个房间中发布音视频
 * 参考文档： https://www.volcengine.com/docs/6348/196844
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
 *     setLocalVideoCanvas 设置本地视频渲染视图
 *     setRemoteVideoCanvas 设置远端视频渲染视图
 *
 *     onRoomStateChanged 房间状态回调
 *     onLeaveRoom 离房回调
 *     onUserJoined 用户加入回调
 *     onUserLeave  用户离开回调
 *     onUserPublishStream 用户发流回调
 *     onUserUnpublishStream 用户停止发流回调
 *
 * Demo实现时的逻辑
 *    为了展示简单，所有功能的token都由客户端生成，接口Utils::generateToken，请在真正接入时视具体情况而定
 *    本Demo演示功能：仅展示3个视频窗口，第一行展示本地采集画面，第二行分别展示room1 远端用户和room2远端用户
*/


MultiRoom::MultiRoom(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::MultiRoom)
{
    ui->setupUi(this);
    initUI();

    connect(ui->btn1, &QPushButton::clicked, this, &MultiRoom::onBtn1Clicked);
    connect(ui->btn2, &QPushButton::clicked, this, &MultiRoom::onBtn2Clicked);

    createRTC();
}

MultiRoom::~MultiRoom()
{
    cleanRTC();
    delete ui;
}

void MultiRoom::onBtn1Clicked()
{
    std::string token, room1, uid1;
    room1 = ui->lineEdit_room1->text().toStdString();
    uid1 = ui->lineEdit_user1->text().toStdString();
    bytertc::VideoCanvas cavas;
    QString qstr_error;
    

    if (m_video == nullptr) return;

    if (m_room1 == nullptr) {
        if (!Utils::checkIDValid(QString::fromStdString(room1), QStringLiteral("用户名"), qstr_error)) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QStringLiteral("roomid1 error ") + qstr_error, QMessageBox::Ok);
            box.exec();
            return;
        }
        if (!Utils::checkIDValid(QString::fromStdString(uid1), QStringLiteral("用户名"), qstr_error)) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QStringLiteral("uid1 error ") + qstr_error, QMessageBox::Ok);
            box.exec();
            return;
        }

        m_room1 = m_video->createRTCRoom(room1.c_str());
        if (m_room1 == nullptr) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("createRTCRoom error"), QMessageBox::Ok);
            box.exec();
            return;
        }
        token = Utils::generateToken(room1, uid1);
        m_room_handler1 = createRoomHandler(room1, uid1);
        m_room1->setRTCRoomEventHandler(m_room_handler1.get());

        cavas.view = (void*)ui->widget->getWinId();
        m_video->setLocalVideoCanvas(bytertc::StreamIndex::kStreamIndexMain, cavas);
        ui->widget->setUserInfo(room1, uid1);

        bytertc::UserInfo user;
        bytertc::RTCRoomConfig config;
        config.is_auto_publish = true; //第一个房间发流，发布后可以用unPublishStream 取消发布
        config.is_auto_subscribe_audio = true;
        config.is_auto_subscribe_video = true;
        config.room_profile_type = bytertc::kRoomProfileTypeCommunication;
        user.uid = uid1.c_str();
        int ret = m_room1->joinRoom(token.c_str(), user, config);
        if (ret < 0) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("joinRoom error,please check params"), QMessageBox::Ok);
            box.exec();
            return;
        }

        m_uid1 = uid1;
        m_remote_u1.roomid = room1;
        QStringList list = { "createRTCRoom", "setRTCRoomEventHandler", "setLocalVideoCanvas", "joinRoom" };
        appendAPI(list);

        QString str_message = "token:" + QString::fromStdString(token);
        appendAPI(str_message);
    }
    else {
        
        m_room1->leaveRoom();
        m_room1->setRTCRoomEventHandler(nullptr);
        m_room1->destroy();
        m_room1 = nullptr;
        m_uid1 = "";
        m_remote_u1.reset();


        ui->btn1->setText(QStringLiteral("进房"));
        ui->widget_2->setUserInfo("", "");
        QStringList list = { "leaveRoom", "setRTCRoomEventHandler", "destroy"};
        appendAPI(list);
    }
}

void MultiRoom::onBtn2Clicked()
{
    std::string token, room2, uid2;
    QString qstr_error;
    room2 = ui->lineEdit_room2->text().toStdString();
    uid2 = ui->lineEdit_user2->text().toStdString();

    if (m_room2 == nullptr) {
        if (!Utils::checkIDValid(QString::fromStdString(room2), QStringLiteral("用户名"), qstr_error)) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("roomid2 error ") + qstr_error, QMessageBox::Ok);
            box.exec();
            return;
        }
        if (!Utils::checkIDValid(QString::fromStdString(uid2), QStringLiteral("用户名"), qstr_error)) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("uid2 error ") + qstr_error, QMessageBox::Ok);
            box.exec();
            return;
        }

        m_room2 = m_video->createRTCRoom(room2.c_str());
        if (m_room2 == nullptr) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("createRTCRoom error"), QMessageBox::Ok);
            box.exec();
            return;
        }
        token = Utils::generateToken(room2, uid2);
        m_room_handler2 = createRoomHandler(room2, uid2);
        m_room2->setRTCRoomEventHandler(m_room_handler2.get());

        bytertc::UserInfo user;
        bytertc::RTCRoomConfig config;
        config.is_auto_publish = false; //第二个房间不发流
        config.is_auto_subscribe_audio = true;
        config.is_auto_subscribe_video = true;
        config.room_profile_type = bytertc::kRoomProfileTypeCommunication;
        user.uid = uid2.c_str();
        int ret = m_room2->joinRoom(token.c_str(), user, config);
        if (ret < 0) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("joinRoom error,please check params"), QMessageBox::Ok);
            box.exec();
            return;
        }

        m_uid2 = uid2;
        m_remote_u2.roomid = room2;
        QStringList list = { "createRTCRoom", "setRTCRoomEventHandler", "setLocalVideoCanvas", "joinRoom" };
        appendAPI(list);

    }
    else {

        m_room2->leaveRoom();
        m_room2->setRTCRoomEventHandler(nullptr);
        m_room2->destroy();
        m_room2 = nullptr;
        m_uid2 = "";
        m_remote_u2.reset();

        ui->btn2->setText(QStringLiteral("进房"));
        QStringList list = { "leaveRoom", "setRTCRoomEventHandler", "destroy" };
        appendAPI(list);

    }
}


void MultiRoom::createRTC()
{
    m_handler.reset(new ByteRTCEventHandler());
    m_video = bytertc::createRTCVideo(g_appid.c_str(), m_handler.get(), nullptr);
    m_video->startAudioCapture();
    m_video->startVideoCapture();
    QStringList list = {"createRTCVideo", "startAudioCapture", "startVideoCapture"};
    appendAPI(list);
}

void MultiRoom::cleanRTC()
{
    if (m_room1) {
        m_room1->leaveRoom();
        m_room1->destroy();
        m_room1 = nullptr;
    }

    if (m_room2) {
        m_room2->leaveRoom();
        m_room2->destroy();
        m_room2 = nullptr;
    }
    if (m_video) {
        m_video->stopAudioCapture();
        m_video->stopVideoCapture();
        bytertc::destroyRTCVideo();
        m_video = nullptr;
    }
    QStringList list = { "leaveRoom", "destroy", "stopAudioCapture", "stopVideoCapture", "destroyRTCVideo"};
    appendAPI(list);
}


std::unique_ptr<ByteRTCRoomHandler> MultiRoom::createRoomHandler(std::string roomid, std::string uid)
{
    std::unique_ptr<ByteRTCRoomHandler> roomH = std::make_unique<ByteRTCRoomHandler>(roomid, uid);
    connect(roomH.get(), &ByteRTCRoomHandler::sigRoomStateChanged, this, &MultiRoom::onSigRoomStateChanged);
    connect(roomH.get(), &ByteRTCRoomHandler::sigLeaveRoom, this, &MultiRoom::onSigLeaveRoom);
    connect(roomH.get(), &ByteRTCRoomHandler::sigUserLeave, this, &MultiRoom::onSigUserLeave);
    connect(roomH.get(), &ByteRTCRoomHandler::sigUserJoined, this, &MultiRoom::onSigUserJoined);
    connect(roomH.get(), &ByteRTCRoomHandler::sigUserPublishStream, this, &MultiRoom::onSigUserPublishStream);
    connect(roomH.get(), &ByteRTCRoomHandler::sigUserUnPublishStream, this, &MultiRoom::onSigUserUnPublishStream);
    connect(roomH.get(), &ByteRTCRoomHandler::sigTokenWillExpire, this, [this]() {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("Token will expire,please updateToken"), QMessageBox::Ok);
        box.exec();
        });

    return roomH;
}

void MultiRoom::onSigRoomStateChanged(std::string roomid, std::string uid, int state, std::string extra_info)
{
    QString str_log = "onRoomStateChanged,roomid:"
        + QString::fromStdString(roomid)
        + ",uid:" + QString::fromStdString(uid)
        + ",state:" + QString::number(state)
        + ",extra_info:" + QString::fromStdString(extra_info);
    appendCallback(str_log);

    QPushButton* btn = nullptr;
    if (state == 0) {
        if (uid == m_uid1 && roomid == ui->lineEdit_room1->text().toStdString()) {
            btn = ui->btn1;
        }
        else {
            btn = ui->btn2;
        }
        btn->setText(QStringLiteral("离房"));
    }
    else {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), 
            QString("onRoomstateChanged,state:") + 
            QString::number(state) +
            ",uid:" + QString::fromStdString(uid) +
            ",roomid:" + QString::fromStdString(roomid), QMessageBox::Ok);
        box.exec();
    }
    
}

void MultiRoom::onSigUserPublishStream(std::string roomid, std::string uid, bytertc::MediaStreamType type)
{
    QString str_log = "onUserPublishStream,roomid:"
        + QString::fromStdString(roomid)
        + ",uid:" + QString::fromStdString(uid)
        + ",type:" + QString::number(type);
    appendCallback(str_log);

    //仅渲染room1和room2的一个远端用户

    bytertc::RemoteStreamKey key;
    key.user_id = uid.c_str();
    key.room_id = roomid.c_str();
    key.stream_index = bytertc::StreamIndex::kStreamIndexMain;
    bytertc::VideoCanvas cavas;
    cavas.background_color = 0;
    cavas.render_mode = bytertc::kRenderModeHidden;
    cavas.view = nullptr;
    if (m_video == nullptr) return;
    if (roomid == m_remote_u1.roomid) {
        if (m_remote_u1.uid.empty() || m_remote_u1.uid == uid) {
            m_remote_u1.uid = uid;
            m_remote_u1.widget = ui->widget_2;
            cavas.view = (void*)m_remote_u1.widget->getWinId();
            m_remote_u1.widget->setUserInfo(roomid, uid);
        }
    } else {
        if (m_remote_u2.uid.empty()) {
            m_remote_u2.uid = uid;
            m_remote_u2.widget = ui->widget_3;
            cavas.view = (void*)m_remote_u2.widget->getWinId();
            m_remote_u2.widget->setUserInfo(roomid, uid);
        }
    }
    m_video->setRemoteVideoCanvas(key, cavas);
    appendAPI("setRemoteVideoCanvas");
}

void MultiRoom::onSigUserUnPublishStream(std::string roomid, std::string uid, bytertc::MediaStreamType type, bytertc::StreamRemoveReason reason)
{
    QString str_log = "onUserUnPublishStream,roomid:"
        + QString::fromStdString(roomid)
        + ",uid:" + QString::fromStdString(uid)
        + ",type:" + QString::number(type)
        + ",reason:" + QString::number(reason);
    appendCallback(str_log);

    if (type & bytertc::kMediaStreamTypeVideo) {
        removeCavas(roomid, uid);
    }
}

void MultiRoom::onSigUserJoined(ByteRTCRoomHandler::UserInfo userinfo, int elapsed)
{
    QString str_log = "onUserJoined,roomid:"
        + QString::fromStdString(userinfo.roomid)
        + ",uid:" + QString::fromStdString(userinfo.uid);
    appendCallback(str_log);
}

void MultiRoom::onSigUserLeave(std::string roomid, std::string uid, bytertc::UserOfflineReason)
{
    QString str_log = "onUserLeave,roomid:"
        + QString::fromStdString(roomid)
        + ",uid:" + QString::fromStdString(uid);
    appendCallback(str_log);
}

void MultiRoom::onSigLeaveRoom(std::string roomid, std::string uid, bytertc::RtcRoomStats) 
{
    QString str_log = "onLeaveRoom,roomid:"
        + QString::fromStdString(roomid)
        + ",uid:" + QString::fromStdString(uid);
    appendCallback(str_log);

    removeCavas(roomid, uid);
}

void MultiRoom::removeCavas(std::string roomid, std::string uid)
{
    if (m_video == nullptr) {
        return;
    }

    bytertc::RemoteStreamKey key;
    bytertc::VideoCanvas cavas;

    key.user_id = uid.c_str();
    key.room_id = roomid.c_str();
    key.stream_index = bytertc::StreamIndex::kStreamIndexMain;
    cavas.view = nullptr;
    m_video->setRemoteVideoCanvas(key, cavas);
    appendAPI("setRemoteVideoCanvas");

    if (roomid == m_remote_u1.roomid && uid == m_remote_u1.uid) {
        m_remote_u1.widget->setUserInfo("", "");
        m_remote_u1.uid = "";
    }
    else if (roomid == m_remote_u2.roomid && uid == m_remote_u2.uid) {
        m_remote_u2.widget->setUserInfo("", "");
        m_remote_u2.uid = "";
    }
    else {
    }

    this->update();
}

void MultiRoom::initUI()
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
    }

    ui->btn1->setStyleSheet(APIDemo::str_qss_btn1);
    ui->btn2->setStyleSheet(APIDemo::str_qss_btn1);
    ui->label_title->setStyleSheet(APIDemo::str_qss_label_ttile);
    ui->label_t1->setStyleSheet(APIDemo::str_qss_label_ttile);
}
