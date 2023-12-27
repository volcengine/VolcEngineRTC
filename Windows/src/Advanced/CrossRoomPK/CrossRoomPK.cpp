#include "CrossRoomPK.h"

#include "ui_CrossRoomPK.h"

#include <sstream>

#include <QDebug>
#include <QMessageBox>
#include <QDateTime>

#include "ByteRTCEventHandler.h"
#include "bytertc_video.h"
#include "bytertc_room.h"
#include "Config.h"
#include "Utils.h"
#include "Resources.h"

/**
* 功能名称： VolcEngineRTC 跨房转推
* 功能简单描述：跨房间转发媒体流，指可见用户的媒体流可以同时转发到多个 RTC 房间。
*             转发目标房间的数量在 RTC 侧没有限制。 本功能适用于以下场景，观众在原来的房间中就能够接收到来自其他房间主播的媒体流。
* 参考文档： https://www.volcengine.com/docs/6348/104398
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
*     startForwardStreamToRooms 开始转发媒体流
*     updateForwardStreamToRooms 更新转发媒体流
*     pauseForwardStreamToAllRooms 暂停转发媒体流
*     resumeForwardStreamToAllRooms 恢复转发媒体流
*     stopForwardStreamToRooms  停止转发媒体流
*
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
*     onForwardStreamStateChanged 跨房间媒体流转发状态和错误回调
*     onForwardStreamEvent 跨房间媒体流转发事件回调
*
* Demo实现时的逻辑
*    本Demo演示功能：在本端房间向其他房间转推媒体流，多个房间id之间用空格间隔
*    为了展示简单，所有功能的token都由客户端生成，接口Utils::generateToken，请在真正接入时视具体情况而定
*/

const std::string str_uid1 = "crosspk_uid_win";

CrossRoomPK::CrossRoomPK(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::CrossRoomPK)
{
    ui->setupUi(this);

    initUI();
    connect(ui->btn_join1, &QPushButton::clicked, this, &CrossRoomPK::onBtnJoinClicked);
    connect(ui->btn_cross_start, &QPushButton::clicked, this, &CrossRoomPK::onBtnCrossStartClicked);
    connect(ui->btn_cross_pause, &QPushButton::clicked, this, &CrossRoomPK::onBtnCrossPauseClicked);
    connect(ui->btn_cross_stop, &QPushButton::clicked, this, &CrossRoomPK::onBtnCrossStopClicked);
    connect(ui->btn_cross_resume, &QPushButton::clicked, this, &CrossRoomPK::onBtnCrossResumeClicked);
    connect(ui->btn_cross_update, &QPushButton::clicked, this, &CrossRoomPK::onBtnCrossUpdateClicked);

    initRTCVideo();
}

CrossRoomPK::~CrossRoomPK()
{
    cleanRTCVideo();
    delete ui;
}

void CrossRoomPK::onBtnCrossStartClicked()
{
    if (m_video == nullptr || m_room1 == nullptr) return;
    std::string uid = m_uid;

    QStringList list = ui->lineEdit_cross->text().split(" ", Qt::SkipEmptyParts);

    std::vector<bytertc::ForwardStreamInfo> forward_stream_dests;
    std::vector<std::string> roomids, tokens;

    for (int i=0; i<list.size(); i++) {
        roomids.push_back(list[i].toStdString());
        std::string token = Utils::generateToken(roomids[i], uid);
        tokens.push_back(token);
        qDebug() << Q_FUNC_INFO << "roomid:" << list[i] << ",uid:" << QString::fromStdString(uid)
                 << ",token:" << QString::fromStdString(token);
    }

    for (int i=0; i<list.size(); i++) {
        bytertc::ForwardStreamInfo one;
        one.room_id = roomids[i].c_str();
        one.token = tokens[i].c_str();
        forward_stream_dests.push_back(one);
    }


    bytertc::ForwardStreamConfiguration configuration;
    configuration.dest_count = forward_stream_dests.size();
    configuration.forward_stream_dests = forward_stream_dests.data();
    int ret = m_room1->startForwardStreamToRooms(configuration);
    if (ret < 0) {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QStringLiteral("startForwardStreamToRooms error:") + QString::number(ret), QMessageBox::Ok);
        box.exec();
        return;
    }
    appendAPI("startForwardStreamToRooms");
    ui->btn_cross_start->setEnabled(false);

}

void CrossRoomPK::onBtnCrossUpdateClicked()
{
    if (m_video == nullptr || m_room1 == nullptr) return;
    std::string uid = str_uid1;

    QStringList list = ui->lineEdit_cross->text().split(" ", Qt::SkipEmptyParts);

    std::vector<bytertc::ForwardStreamInfo> forward_stream_dests;
    std::vector<std::string> roomids, tokens;

    for (int i=0; i<list.size(); i++) {
        roomids.push_back(list[i].toStdString());
        tokens.push_back(Utils::generateToken(roomids[i], uid));
    }

    for (int i=0; i<list.size(); i++) {
        bytertc::ForwardStreamInfo one;
        one.room_id = roomids[i].c_str();
        one.token = tokens[i].c_str();
        forward_stream_dests.push_back(one);
    }


    bytertc::ForwardStreamConfiguration configuration;
    configuration.dest_count = forward_stream_dests.size();
    configuration.forward_stream_dests = forward_stream_dests.data();
    int ret = m_room1->updateForwardStreamToRooms(configuration);
    if (ret < 0) {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QStringLiteral("updateForwardStreamToRooms error:") + QString::number(ret), QMessageBox::Ok);
        box.exec();
        return;
    }
    appendAPI("updateForwardStreamToRooms");
}


void CrossRoomPK::onBtnCrossPauseClicked()
{
    if (m_video == nullptr || m_room1 == nullptr) return;
    int ret = m_room1->pauseForwardStreamToAllRooms();
    if (ret < 0) {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("pauseForwardStreamToAllRooms error"), QMessageBox::Ok);
        box.exec();
        return;
    }
}

void CrossRoomPK::onBtnCrossResumeClicked()
{
    if (m_video == nullptr || m_room1 == nullptr) return;
    int ret = m_room1->resumeForwardStreamToAllRooms();
    if (ret < 0) {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("resumeForwardStreamToAllRooms error"), QMessageBox::Ok);
        box.exec();
        return;
    }
    appendAPI("resumeForwardStreamToAllRooms");
}

void CrossRoomPK::onBtnCrossStopClicked()
{
    if (m_video == nullptr || m_room1 == nullptr) return;
    int ret = m_room1->stopForwardStreamToRooms();
    if (ret < 0) {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("stopForwardStreamToRooms error"), QMessageBox::Ok);
        box.exec();
    }
    ui->btn_cross_start->setEnabled(true);
    appendAPI("stopForwardStreamToRooms");
}

void CrossRoomPK::onBtnJoinClicked() {

    QString str_error;
    QStringList list;
    std::string roomid, uid, token;
    roomid = ui->lineEdit_room->text().toStdString();
    uid = ui->lineEdit_uid->text().toStdString();
    if (ui->btn_join1->text() == QStringLiteral("进房")) {
        
        if (!Utils::checkIDValid(QString::fromStdString(roomid), QStringLiteral("房间id"), str_error)) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("roomid error ") + str_error, QMessageBox::Ok);
            box.exec();
            return;
        }

        if (!Utils::checkIDValid(QString::fromStdString(uid), QStringLiteral("uid"), str_error)) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("uid error ") + str_error, QMessageBox::Ok);
            box.exec();
            return;
        }

        m_room1 = m_video->createRTCRoom(roomid.c_str());
        if (m_room1 == nullptr) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("createRTCRoom error"), QMessageBox::Ok);
            box.exec();
            return;
        }
        m_room_handler1 = createRoomHandler(roomid, uid);
        m_room1->setRTCRoomEventHandler(m_room_handler1.get());

        bytertc::VideoCanvas cavas;
        cavas.view = (void*)ui->widget->getWinId();
        m_video->setLocalVideoCanvas(bytertc::StreamIndex::kStreamIndexMain, cavas);
        ui->widget->setUserInfo(roomid, uid);


        token = Utils::generateToken(roomid, uid);
        bytertc::UserInfo info;
        bytertc::RTCRoomConfig config;
        info.uid = uid.c_str();
        config.is_auto_publish = true;
        config.is_auto_subscribe_audio = true;
        config.is_auto_subscribe_video = true;
        config.room_profile_type = bytertc::kRoomProfileTypeCommunication;
        int ret = m_room1->joinRoom(token.c_str(), info, config);
        m_uid = uid;
        if (ret < 0) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("createRTCRoom error"), QMessageBox::Ok);
            box.exec();
            return;
        }
        list = QStringList{"createRTCRoom", "setRTCRoomEventHandler", "setLocalVideoCanvas", "joinRoom"};
    }
    else {
        if (m_room1) {
            m_room1->leaveRoom();
            m_room1->destroy();
            m_room1 = nullptr;
            list = QStringList{ "leaveRoom", "destroy" };
        }
        ui->btn_join1->setText(QStringLiteral("进房"));
        ui->btn_cross_start->setEnabled(true);
        ui->btn_cross_stop->setEnabled(true);
    }
    appendAPI(list);
}

void CrossRoomPK::initRTCVideo()
{
    m_handler.reset(new ByteRTCEventHandler());
    m_video = bytertc::createRTCVideo(g_appid.c_str(), m_handler.get(), nullptr);
    m_video->startAudioCapture();
    m_video->startVideoCapture();

    QStringList list = {"createRTCVideo", "startAudioCapture", "startVideoCapture"};
    appendAPI(list);
}

void CrossRoomPK::cleanRTCVideo()
{
    QStringList list = {"stopAudioCapture", "stopVideoCapture", "destroyRTCVideo"};
    if (m_video) {
        if (m_room1) {
            m_room1->leaveRoom();
            m_room1->setRTCRoomEventHandler(nullptr);
            m_room1->destroy();
            m_room1 = nullptr;
            list = QStringList{"leaveRoom", "setRTCRoomEventHandler", "destroy"} + list;
        }
        m_video->stopAudioCapture();
        m_video->stopVideoCapture();
        bytertc::destroyRTCVideo();
        m_video = nullptr;
        appendAPI(list);
    }
    
}

void CrossRoomPK::initUI()
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
    ui->btn_join1->setStyleSheet(APIDemo::str_qss_btn1);
    auto func_sty = [this](QPushButton *btn){
        if (btn) {
            btn->setStyleSheet(APIDemo::str_qss_btn2_3);
            btn->setFixedSize(80, 24);
        }
    };

    func_sty(ui->btn_cross_pause);
    func_sty(ui->btn_cross_resume);
    func_sty(ui->btn_cross_start);
    func_sty(ui->btn_cross_stop);
    func_sty(ui->btn_cross_update);
    ui->label_title->setStyleSheet(APIDemo::str_qss_label_ttile);
    ui->label_t1->setStyleSheet(APIDemo::str_qss_label_ttile);
    ui->label_t2->setStyleSheet(APIDemo::str_qss_label_ttile);
}

std::unique_ptr<ByteRTCRoomHandler> CrossRoomPK::createRoomHandler(std::string roomid, std::string uid)
{
    std::unique_ptr<ByteRTCRoomHandler> roomH = std::make_unique<ByteRTCRoomHandler>(roomid, uid);
    connect(roomH.get(), &ByteRTCRoomHandler::sigRoomStateChanged, this, &CrossRoomPK::onSigRoomStateChanged);
    connect(roomH.get(), &ByteRTCRoomHandler::sigUserPublishStream, this, &CrossRoomPK::onSigUserPublishStream);
    connect(roomH.get(), &ByteRTCRoomHandler::sigUserUnPublishStream, this, &CrossRoomPK::onSigUserUnPublishStream);
    connect(roomH.get(), &ByteRTCRoomHandler::sigLeaveRoom, this, &CrossRoomPK::onSigLeaveRoom);
    connect(roomH.get(), &ByteRTCRoomHandler::sigForwardStreamStateChanged, this, &CrossRoomPK::onSigForwardStreamStateChanged);
    connect(roomH.get(), &ByteRTCRoomHandler::sigForwardStreamEvent, this, &CrossRoomPK::onForwardStreamEvent);
    connect(roomH.get(), &ByteRTCRoomHandler::sigTokenWillExpire, this, [this]() {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("Token will expire,please updateToken"), QMessageBox::Ok);
        box.exec();
        });

    return roomH;
}

void CrossRoomPK::onSigRoomStateChanged(std::string roomid, std::string uid, int state, std::string extra_info) {
    QString log_str = QString("onRoomStateChanged,roomid:")
        + QString::fromStdString(roomid)
        + ",uid:" + QString::fromStdString(uid)
        + ",state:" + QString::number(state)
        + ",extra:" + QString::fromStdString(extra_info);

    appendCallback(log_str);

    if (state == 0) {
        ui->btn_join1->setText(QStringLiteral("离房"));
    }
    else {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("onRoomStateChanged state:") + QString::number(state), QMessageBox::Ok);
        box.exec();
        return;
    }
}

void CrossRoomPK::onSigUserPublishStream(std::string roomid, std::string uid, bytertc::MediaStreamType type)
{
    QString log_str = QString("onUserPublishStream,roomid:")
        + QString::fromStdString(roomid)
        + ",uid:" + QString::fromStdString(uid)
        + ",state:" + QString::number(type);
    appendCallback(log_str);
}

void CrossRoomPK::onSigUserUnPublishStream(std::string roomid, std::string uid, bytertc::MediaStreamType type, bytertc::StreamRemoveReason)
{
    QString log_str = QString("onUserUnPublishStream,roomid:")
        + QString::fromStdString(roomid)
        + ",uid:" + QString::fromStdString(uid)
        + ",state:" + QString::number(type);
    appendCallback(log_str);

}

void CrossRoomPK::onSigLeaveRoom(std::string roomid, std::string uid, const bytertc::RtcRoomStats stats)
{
    ui->btn_join1->setText(QStringLiteral("进房"));
    QString str = "onLeaveRoom, roomid:" + QString::fromStdString(roomid) + ",uid:" + QString::fromStdString(uid);
    appendCallback(str);
}

void CrossRoomPK::onSigForwardStreamStateChanged(std::vector<ByteRTCRoomHandler::Stru_ForwardStreamStateInfo> result)
{
    qDebug() << Q_FUNC_INFO << result.size();
    std::stringstream stream;
    stream << "onForwardStreamStateChanged,";
    for (unsigned int i = 0; i < result.size(); i++) {
        stream << ",roomid:" << result[i].roomid << ", state:" << result[i].state << ", error:" << result[i].error;
    }
    appendCallback(QString::fromStdString(stream.str()));

    qDebug() << Q_FUNC_INFO << QString::fromStdString(stream.str());

}

void CrossRoomPK::onForwardStreamEvent(std::vector<ByteRTCRoomHandler::Stru_ForwardStreamEvent> events)
{
    std::stringstream stream;
    stream << "onForwardStreamEvent,";
    for (unsigned int i = 0; i < events.size(); i++) {
        stream << ",roomid:" << events[i].roomid << ", state:" << events[i].event << ", event:" << events[i].event;
    }
    appendCallback(QString::fromStdString(stream.str()));
}
