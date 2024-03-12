#include "SEIMessage.h"
#include "ui_SEIMessage.h"

#include "Resources.h"

#include "bytertc_video.h"
#include "bytertc_room.h"
#include "Config.h"
#include "Utils.h"

#include <QMessageBox>
#include <QDateTime>

/**
* 功能名称： VolcEngineRTC SEI方案
* 功能简单描述：在音视频流媒体应用中，除了可以收发音视频内容外，可能还需要收发一些与音视频内容同步的文本消息。
*   你可以 H.264/H.265 视频视频流中插入 SEI，并在订阅端接收这些信息。
* 参考文档：https://www.volcengine.com/docs/6348/70140
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
*     通用方案： RTC本端通过sendSEIMessage发送SEI， RTC远端收到onSEIMessageReceived，当合流转推时，RTMP流 h264视频中包含SEI信息
*     相关接口：
*     sendSEIMessage 发送SEI信息
*     onSEIMessageReceived 收到SEI信息的回调
*     当时纯音频场景时，本端需要发布视频流，远端需要订阅视频流才能收到SEI
*
*     合流转推方案：合流转推时通过 setLayoutConfig 接口将app_data设置在SEI信息中，观众端拉流时可以解析SEI，SEI结构如下
*     {
        "app_data": "自定义消息",
        "canvas": {
            "bgnd": "#000000",
            "h": 640,
            "w": 360
        },
        "regions": [{
            "alpha": 1.0,
            "contentControl": 0,
            "height": 640,
            "locationX": 0,
            "locationY": 50,
            "renderMode": 1,
            "uid": "user_343",
            "width": 360,
            "zorder": 0
            }],
        "ts": 1705994199709
    }
      相关接口：
*     startPushMixedStreamToCDN 开始合流转推
*     setLayoutConfig 设置SEI中的app_data信息
*     stopPushStreamToCDN 停止合流转推
*
*
*     音频随帧方案：请参考音频随帧部分
*
*     其他接口：
*     setLocalVideoCanvas 设置本地视频渲染视图

*
*     onRoomStateChanged 房间状态回调
*     onLeaveRoom 离房回调
*     onUserJoined 用户加入回调
*     onUserLeave  用户离开回调
*     onUserPublishStream 用户发流回调
*     onUserUnpublishStream 用户停止发流回调
*/

SEIMessage::SEIMessage(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::SEIMessage)
{
    ui->setupUi(this);
    initUI();
    initConnections();
    initRTCVideo();
}

SEIMessage::~SEIMessage()
{
    cleanRTCVideo();
    delete ui;
}

void SEIMessage::initUI()
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
    ui->btn_join->setStyleSheet(APIDemo::str_qss_btn1);
    ui->textEdit_receive1->setStyleSheet(APIDemo::str_qss_text);
    ui->textEdit_send1->setStyleSheet(APIDemo::str_qss_text);
    ui->textEdit_send2->setStyleSheet(APIDemo::str_qss_text);
    ui->btn_send1->setStyleSheet(APIDemo::str_qss_btn2_3);
    ui->btn_start1->setStyleSheet(APIDemo::str_qss_btn2_3);
    ui->btn_start2->setStyleSheet(APIDemo::str_qss_btn2_3);
    ui->btn_stop1->setStyleSheet(APIDemo::str_qss_btn2_3);
    ui->btn_stop2->setStyleSheet(APIDemo::str_qss_btn2_3);
    ui->btn_update2->setStyleSheet(APIDemo::str_qss_btn2_3);
    ui->label_title->setStyleSheet(APIDemo::str_qss_label_ttile);
}

void SEIMessage::initConnections()
{
    connect(ui->btn_join, &QPushButton::clicked, this, &SEIMessage::onBtnJoinClicked);
    connect(ui->btn_send1, &QPushButton::clicked, this, &SEIMessage::onBtnSendSeiClicked);
    connect(ui->btn_start1, &QPushButton::clicked, this, &SEIMessage::onBtnStarRTMPhClicked);
    connect(ui->btn_start2, &QPushButton::clicked, this, &SEIMessage::onBtnStarRTMPhClicked);
    connect(ui->btn_stop1, &QPushButton::clicked, this, &SEIMessage::onBtnStopRTMPClicked);
    connect(ui->btn_stop2, &QPushButton::clicked, this, &SEIMessage::onBtnStopRTMPClicked);
    connect(ui->btn_update2, &QPushButton::clicked, this, &SEIMessage::onBtnUpdate2Clicked);

}

void SEIMessage::initRTCVideo()
{
    m_handler.reset(new ByteRTCEventHandler());
    m_handler->setIsSupportClientPushStream(false); //本Demo使用RTC服务器推流，因此isSupportClientPushStream返回false
    connect(m_handler.get(), &ByteRTCEventHandler::sigMixingEvent, this, &SEIMessage::onSigMixingEvent);
    connect(m_handler.get(), &ByteRTCEventHandler::sigSEIMessageReceived, this, &SEIMessage::onSEIMessageReceived);
    m_video = bytertc::createRTCVideo(g_appid.c_str(), m_handler.get(), nullptr);
    m_video->startAudioCapture();
    m_video->startVideoCapture();

    QStringList list = {"createRTCVideo", "startAudioCapture", "startVideoCapture"};
    appendAPI(list);
}

void SEIMessage::cleanRTCVideo()
{
    QStringList list = {"stopAudioCapture", "stopVideoCapture", "destroyRTCVideo"};
    if (m_video) {
        if (m_room) {
            m_room->leaveRoom();
            m_room->setRTCRoomEventHandler(nullptr);
            m_room->destroy();
            m_room = nullptr;
            list = QStringList{"leaveRoom", "setRTCRoomEventHandler", "destroy"} + list;
        }
        m_video->stopAudioCapture();
        m_video->stopVideoCapture();
        bytertc::destroyRTCVideo();
        m_video = nullptr;
        appendAPI(list);
    }
    ui->btn_join->setText(QStringLiteral("进房"));
}

std::unique_ptr<ByteRTCRoomHandler> SEIMessage::createRoomHandler(std::string roomid, std::string uid)
{
    std::unique_ptr<ByteRTCRoomHandler> roomH = std::make_unique<ByteRTCRoomHandler>(roomid, uid);
    connect(roomH.get(), &ByteRTCRoomHandler::sigRoomStateChanged, this, &SEIMessage::onSigRoomStateChanged);
    connect(roomH.get(), &ByteRTCRoomHandler::sigUserPublishStream, this, &SEIMessage::onSigUserPublishStream);
    connect(roomH.get(), &ByteRTCRoomHandler::sigUserUnPublishStream, this, &SEIMessage::onSigUserUnPublishStream);
    connect(roomH.get(), &ByteRTCRoomHandler::sigUserLeave, this, &SEIMessage::onSigUserLeave);
    connect(roomH.get(), &ByteRTCRoomHandler::sigUserJoined, this, &SEIMessage::onSigUserJoined);

    connect(roomH.get(), &ByteRTCRoomHandler::sigTokenWillExpire, this, [this]() {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("Token will expire,please updateToken"), QMessageBox::Ok);
        box.exec();
        });

    return roomH;

}

void SEIMessage::onBtnJoinClicked()
{
    QString str_error;
    QStringList list;
    std::string roomid, uid, token;
    roomid = ui->lineEdit_room->text().toStdString();
    uid = ui->lineEdit_uid->text().toStdString();
    if (ui->btn_join->text() == QStringLiteral("进房")) {

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

        m_room = m_video->createRTCRoom(roomid.c_str());
        if (m_room == nullptr) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("createRTCRoom error"), QMessageBox::Ok);
            box.exec();
            return;
        }
        m_room_handler = createRoomHandler(roomid, uid);
        m_room->setRTCRoomEventHandler(m_room_handler.get());

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
        int ret = m_room->joinRoom(token.c_str(), info, config);
        m_uid = uid;
        m_roomid = roomid;
        if (ret < 0) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("createRTCRoom error"), QMessageBox::Ok);
            box.exec();
            return;
        }
        list = QStringList{"createRTCRoom", "setRTCRoomEventHandler", "setLocalVideoCanvas", "joinRoom"};
    }
    else {
        if (m_room) {
            m_room->leaveRoom();
            m_room->destroy();
            m_room = nullptr;
            list = QStringList{ "leaveRoom", "destroy" };
        }
        ui->btn_join->setText(QStringLiteral("进房"));
    }
    appendAPI(list);

}


bytertc::IMixedStreamConfig* SEIMessage::getMixedStreamConfig(std::string url, std::string app_data)
{
    // audio
    bytertc::MixedStreamAudioConfig audioParam;
    audioParam.audio_codec = bytertc::MixedStreamAudioCodecType::kMixedStreamAudioCodecTypeAAC;
    audioParam.channels = 2;
    audioParam.bitrate = 64;
    audioParam.sample_rate = 48000;

    audioParam.audio_profile = bytertc::MixedStreamAudioProfile::kMixedStreamAudioProfileLC;

    // video
    bytertc::MixedStreamVideoConfig videoParam;
    videoParam.bitrate = 500;
    videoParam.fps = 15;
    videoParam.gop = 2;
    videoParam.width = 640;
    videoParam.height = 360;
    videoParam.enable_bframe = false;
    videoParam.video_codec = bytertc::kMixedStreamVideoCodecTypeH264;


    // layout
    bytertc::MixedStreamLayoutRegionConfig* layouts = new bytertc::MixedStreamLayoutRegionConfig[1];

    bytertc::MixedStreamLayoutRegionConfig lay;
    lay.region_id = m_uid.c_str();
    lay.room_id = m_roomid.c_str();

    lay.location_x = 0; //确定每个流的位置
    lay.location_y = 0;
    lay.width = videoParam.width;
    lay.height = videoParam.height;
    lay.is_local_user = true;
    lay.alpha = 1.0f;
    lay.z_order = 0;

    lay.render_mode = bytertc::MixedStreamRenderMode::kMixedStreamRenderModeHidden;
    lay.stream_type = bytertc::MixedStreamVideoType::kMixedStreamVideoTypeMain;
    lay.media_type = bytertc::MixedStreamMediaType::kMixedStreamMediaTypeAudioAndVideo;
    lay.apply_spatial_audio = false;
    layouts[0] = lay;

    bytertc::MixedStreamClientMixConfig client_conf;
    client_conf.use_audio_mixer = true;
    client_conf.video_format = bytertc::kMixedStreamClientMixVideoFormatI420;

    bytertc::IMixedStreamConfig* mixed_stream_param = bytertc::createMixedStreamConfig();
    mixed_stream_param->setAudioConfig(audioParam);
    mixed_stream_param->setVideoConfig(videoParam);
    mixed_stream_param->setLayoutConfig(layouts, 1, "#000000", app_data.c_str());
    mixed_stream_param->setExpectedMixingType(bytertc::kMixedStreamTypeByServer); //由RTC服务端进行合流转推
    mixed_stream_param->setPushURL(url.c_str());
    mixed_stream_param->setRoomID(m_roomid.c_str());
    mixed_stream_param->setUserID(m_uid.c_str());
    mixed_stream_param->setClientMixConfig(client_conf);

    delete[]layouts;
    return mixed_stream_param;

    QStringList list = {"setAudioConfig", "setVideoConfig", "setLayoutConfig", "setExpectedMixingType", "setPushURL", "setRoomID", "setUserID", "setClientMixConfig"};
    appendAPI(list);
}


void SEIMessage::onBtnStarRTMPhClicked()
{
    if (m_video == nullptr) return;
    QString url, app_data;

    if (sender() == ui->btn_start1) { //sendSEIMessage方案
        url = ui->lineEdit_url->text();
        bytertc::IMixedStreamConfig *config = getMixedStreamConfig(url.toStdString(), "");
        int ret = m_video->startPushMixedStreamToCDN("task1", config, m_handler.get());
        appendAPI("startPushMixedStreamToCDN,ret=" + QString::number(ret));
        if (ret != 0) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("startPushMixedStreamToCDN error，请检查是否已经在控制台开通该功能"), QMessageBox::Ok);
            box.exec();
            return;
        }
        ui->btn_start1->setEnabled(false);
    } else {
        url = ui->lineEdit_url2->text(); //合流转推布局方案
        app_data = ui->textEdit_send2->toPlainText();

        bytertc::IMixedStreamConfig *config = getMixedStreamConfig(url.toStdString(), app_data.toStdString());
        int ret = m_video->startPushMixedStreamToCDN("task2", config, m_handler.get());
        appendAPI("startPushMixedStreamToCDN,ret=" + QString::number(ret));

        if (ret != 0) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("startPushMixedStreamToCDN error，请检查是否已经在控制台开通该功能"), QMessageBox::Ok);
            box.exec();
            return;
        }
        ui->btn_start2->setEnabled(false);
    }

    appendAPI("startPushMixedStreamToCDN, app_data=" + app_data);
}

void SEIMessage::onBtnStopRTMPClicked()
{
    if (m_video == nullptr) return;
    int ret = 0;
    if (sender() == ui->btn_stop1) { //sendSEIMEssage 方案

        ret = m_video->stopPushStreamToCDN("task1");
        ui->btn_start1->setEnabled(true);
    } else { // 合流转推布局方案
        ret = m_video->stopPushStreamToCDN("task2");
        ui->btn_start2->setEnabled(true);
    }
    appendAPI("stopPushStreamToCDN,ret=" + QString::number(ret));

    if (ret < 0) {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("stopPushStreamToCDN error:") + QString::number(ret), QMessageBox::Ok);
        box.exec();
    }


    appendAPI("stopPushStreamToCDN,ret=" + QString::number(ret));
}

void SEIMessage::onBtnSendSeiClicked()
{
    if (m_video == nullptr) return;
    QString qstr_text = ui->textEdit_send1->toPlainText();
    if (qstr_text.isEmpty()) {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("text is empty"), QMessageBox::Ok);
        box.exec();
        return;
    }

    std::string str_text = qstr_text.toStdString();
    int ret = m_video->sendSEIMessage(bytertc::kStreamIndexMain, (uint8_t*)str_text.c_str(), str_text.size(), 2, bytertc::kSEICountPerFrameSingle);
    if (ret < 0) {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QStringLiteral("sendSEIMessage error:") + QString::number(ret), QMessageBox::Ok);
        box.exec();
    }
    appendAPI("sendSEIMessage,ret=" + QString::number(ret));

}

void SEIMessage::onBtnUpdate2Clicked()
{
    if (m_video == nullptr) return;
    QString url, app_data;

    url = ui->lineEdit_url2->text(); //合流转推布局方案
    app_data = ui->textEdit_send2->toPlainText();

    bytertc::IMixedStreamConfig *config = getMixedStreamConfig(url.toStdString(), app_data.toStdString());
    int ret = m_video->updatePushMixedStreamToCDN("task2", config);

    if (ret != 0) {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("updatePushMixedStreamToCDN error，请检查是否已经在控制台开通该功能"), QMessageBox::Ok);
        box.exec();
        return;
    }
    ui->btn_start2->setEnabled(false);
    appendAPI("updatePushMixedStreamToCDN, app_data=" + app_data);
}

void SEIMessage::onSigRoomStateChanged(std::string roomid, std::string uid, int state, std::string extra_info)
{
    QString log_str = QString("onRoomStateChanged,roomid:")
        + QString::fromStdString(roomid)
        + ",uid:" + QString::fromStdString(uid)
        + ",state:" + QString::number(state)
        + ",extra:" + QString::fromStdString(extra_info);

    appendCallback(log_str);

    if (state == 0) {
        ui->btn_join->setText(QStringLiteral("离房"));
    }
    else {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("onRoomStateChanged state:") + QString::number(state), QMessageBox::Ok);
        box.exec();
        return;
    }

}

void SEIMessage::onSigUserPublishStream(std::string roomid, std::string uid, bytertc::MediaStreamType type)
{
    QString log_str = QString("onUserPublishStream,roomid:")
                      + QString::fromStdString(roomid)
                      + ",uid:" + QString::fromStdString(uid)
                      + ",state:" + QString::number(type);
    appendCallback(log_str);

}

void SEIMessage::onSigUserUnPublishStream(std::string roomid, std::string uid, bytertc::MediaStreamType type, bytertc::StreamRemoveReason reason)
{
    QString log_str = QString("onUserUnPublishStream,roomid:")
                      + QString::fromStdString(roomid)
                      + ",uid:" + QString::fromStdString(uid)
                      + ",state:" + QString::number(type);
    appendCallback(log_str);

}

void SEIMessage::onSEIMessageReceived(ByteRTCEventHandler::Stru_RemoteStreamKey stream_key, std::string str)
{
    QString sss = "onSEIMessageReceived, roomid:" + QString::fromStdString(stream_key.room_id) +
                  ",uid:" + QString::fromStdString(stream_key.user_id) +
                  ",message:" + QString::fromStdString(str);
    ui->textEdit_receive1->append(sss);

    appendCallback(sss);
}

void SEIMessage::onSigMixingEvent(bytertc::StreamMixingEvent event, std::string task_id, bytertc::StreamMixingErrorCode error, bytertc::MixedStreamType mix_type)
{
    QString str = "onMixingEvent, event:" + QString::number(event) + ",taskid:" + QString::fromStdString(task_id)
                  + ",error:" + QString::number(error) + ",type:" + QString::number(mix_type);
    appendCallback(str);
}

void SEIMessage::onSigUserJoined(ByteRTCRoomHandler::UserInfo info, int)
{
    QString str = "onUserJoined, roomid:" + QString::fromStdString(info.roomid)
                  + ",uid:" + QString::fromStdString(info.uid);
    appendCallback(str);

}

void SEIMessage::onSigUserLeave(std::string roomid, std::string uid, bytertc::UserOfflineReason)
{
    QString str = "onUserLeave, roomid:" + QString::fromStdString(roomid)
                  + ",uid:" + QString::fromStdString(uid);
    appendCallback(str);

}

