#include "VideoConfigWidget.h"
#include "ui_VideoConfigWidget.h"

#include "bytertc_video.h"
#include "bytertc_room.h"

#include "Config.h"
#include "Utils.h"
#include "Resources.h"

#include <QMessageBox>
#include <QDebug>
#include <QComboBox>
#include <QApplication>

/**
* 功能名称： VolcEngineRTC 视频常用配置
* 功能简单描述：修改视频常用的采集、编码参数，设置旋转角度、水印等功能
* 参考文档：https://www.volcengine.com/docs/6348/70122
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
*     setVideoCaptureConfig 设置 RTC SDK 内部采集时的视频采集参数
*     setVideoEncoderConfig 设置视频编码参数
*     setLocalVideoMirrorType 为采集到的视频流开启镜像
*     setVideoWatermark 在指定视频流上添加水印
*     clearVideoWatermark 清除水印
*     setVideoCaptureRotation 设置本端采集的视频帧的旋转角度
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
*    本Demo演示功能：视频常用参数的设置
*    为了展示简单，所有功能的token都由客户端生成，接口Utils::generateToken，接入SDK时建议将Token生成逻辑放在服务端
*/


VideoConfigWidget::VideoConfigWidget(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::VideoConfigWidget)
{
    ui->setupUi(this);
    initConnections();
    initRTCVideo();
}

VideoConfigWidget::~VideoConfigWidget()
{
    cleanRTCVideo();
    m_rendering.clear();
    delete ui;
}

void VideoConfigWidget::initConnections()
{
    connect(ui->btn_join, &QPushButton::clicked, this, &VideoConfigWidget::onBtnJoinClicked);
    connect(ui->btn_fix_capture, &QPushButton::clicked, this, &VideoConfigWidget::onBtnCaptureClicked);
    connect(ui->btn_fix_encoder, &QPushButton::clicked, this, &VideoConfigWidget::onBtnEncoderClicked);
    connect(ui->comboBox_morror, &QComboBox::currentTextChanged, this, &VideoConfigWidget::onComboMirrorClicked);
    connect(ui->comboBox_c_render, &QComboBox::currentTextChanged, this, &VideoConfigWidget::onComboLocalRenderTextChanged);
    connect(ui->comboBox_remote_render, &QComboBox::currentTextChanged, this, &VideoConfigWidget::onComboRemoteRenderTextChanged);
    connect(ui->comboBox_rotation, &QComboBox::currentTextChanged, this, &VideoConfigWidget::onComboboRotationClicked);
    connect(ui->checkBox_water, &QCheckBox::stateChanged, this, &VideoConfigWidget::onCheckWaterClicked);
}

void VideoConfigWidget::initRTCVideo()
{
    auto handler = new ByteRTCEventHandler();
    m_video = bytertc::createRTCVideo(g_appid.c_str(), handler, nullptr);
    m_video->startAudioCapture();
    m_video->startVideoCapture();

    QStringList list = {"createRTCVideo", "startAudioCapture", "startVideoCapture"};
    ui->widget_log->appendAPI(list);
}

void VideoConfigWidget::cleanRTCVideo()
{
    if (m_video) {
        if (m_room) {
            m_room->leaveRoom();
            m_room->setRTCRoomEventHandler(nullptr);
            m_room->destroy();
            m_room = nullptr;
        }

        m_video->stopAudioCapture();
        m_video->stopVideoCapture();
        bytertc::destroyRTCVideo();
        m_video = nullptr;
    }
    QStringList list = { "leaveRoom", "setRTCRoomEventHandler", "destroy", "stopAudioCapture", "stopVideoCapture", "destroyRTCVideo"};
    ui->widget_log->appendAPI(list);
}

ByteRTCRoomHandler* VideoConfigWidget::createRoomHandler(std::string roomid, std::string uid)
{
    auto roomH = new ByteRTCRoomHandler(roomid, uid);
    connect(roomH, &ByteRTCRoomHandler::sigRoomStateChanged, this, &VideoConfigWidget::onSigRoomStateChanged);
    connect(roomH, &ByteRTCRoomHandler::sigUserPublishStream, this, &VideoConfigWidget::onSigUserPublishStream);
    connect(roomH, &ByteRTCRoomHandler::sigUserUnPublishStream, this, &VideoConfigWidget::onSigUserUnPublishStream);

    return roomH;
}

bytertc::RenderMode VideoConfigWidget::getRenderMode(QComboBox* box)
{
    bytertc::RenderMode result = bytertc::kRenderModeHidden;
    QString text = box->currentText();
    if (box == nullptr) return result;
    if (text.contains("Hidden")) {
        result = bytertc::kRenderModeHidden;
    }
    else if (text.contains("Fill")) {
        result = bytertc::kRenderModeFill;
    }
    else {
        result = bytertc::kRenderModeFit;
    }

    return result;
}

void VideoConfigWidget::onBtnJoinClicked() {
    std::string str_room = ui->lineEdit_room->text().toStdString();
    std::string str_uid = ui->lineEdit_uid->text().toStdString();
    std::string str_token;
    QString qstr_error;
    QStringList list;
    if (m_video == nullptr) {
        qWarning() << Q_FUNC_INFO << "m_video = nullptr";
        return;
    }

    if (ui->btn_join->text() == QStringLiteral("进房")) {
        if (!Utils::checkIDValid(QString::fromStdString(str_uid), QStringLiteral("用户名"), qstr_error)) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), qstr_error, QMessageBox::Ok);
            box.exec();
            return;
        }

        if (!Utils::checkIDValid(QString::fromStdString(str_room), QStringLiteral("房间号"), qstr_error)) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), qstr_error, QMessageBox::Ok);
            box.exec();
            return;
        }

        m_room = m_video->createRTCRoom(str_room.c_str());
        if (m_room == nullptr) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("createRTCRoom error"), QMessageBox::Ok);
            box.exec();
            return;
        }

        bytertc::VideoCanvas cavs;
        cavs.view = (void*)ui->widget->winId();
        cavs.render_mode = getRenderMode(ui->comboBox_c_render); //渲染参数
        cavs.background_color = 0x00FF0000;
        m_video->setLocalVideoCanvas(bytertc::kStreamIndexMain, cavs); 
        

        onBtnCaptureClicked();//采集参数
        onBtnEncoderClicked();//编码参数

        m_video->startAudioCapture();
        m_video->startVideoCapture();

        auto handler = createRoomHandler(str_room, str_uid);
        m_room->setRTCRoomEventHandler(handler);

        bytertc::UserInfo info;
        bytertc::RTCRoomConfig config;

        info.uid = str_uid.c_str();
        config.is_auto_publish = true;
        config.is_auto_subscribe_audio = true;
        config.is_auto_subscribe_video = true;
        config.remote_video_config.framerate = 15;
        config.remote_video_config.resolution_height = ui->widget_2->height();
        config.remote_video_config.resolution_width = ui->widget_2->height();
        config.room_profile_type = bytertc::kRoomProfileTypeCommunication;
        str_token = Utils::generateToken(str_room, str_uid);
        int ret = m_room->joinRoom(str_token.c_str(), info, config);
        if (ret < 0) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("joinRoom error"), QMessageBox::Ok);
            box.exec();
            return;
        }
        list = QStringList{"createRTCRoom", "setLocalVideoCanvas", "setRTCRoomEventHandler", "joinRoom"};
    } else {
        if (m_room) {
            m_room->leaveRoom();
            m_room->destroy();
            m_room = nullptr;
        }
        m_rendering.clear();
        ui->btn_join->setText(QStringLiteral("进房"));
        list = QStringList{ "leaveRoom", "destroy"};
    }
    ui->widget_log->appendAPI(list);
}

void VideoConfigWidget::onBtnCaptureClicked()
{
    int ret = 0;
    bytertc::VideoCaptureConfig config;
    config.width = ui->spinBox_c_w->value(); //采集宽度
    config.height = ui->spinBox_c_h->value(); //采集高度
    config.frameRate = ui->spinBox_c_fps->value(); //采集帧率
    config.capturePreference = getCapturePreference(); //采集偏好设置
    
    if (m_video) {
        
        ret = m_video->setVideoCaptureConfig(config);
        if (ret < 0) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("setVideoCaptureConfig error"), QMessageBox::Ok);
            box.exec();
            return;
        }
        ui->widget_log->appendAPI("setVideoCaptureConfig");
    }
}

void VideoConfigWidget::onBtnEncoderClicked()
{
    int ret = 0;
    if (m_video) {
        bytertc::VideoEncoderConfig config;
        config.width = ui->spinBox_e_w->value();
        config.height = ui->spinBox_e_h->value();
        config.frameRate = ui->spinBox_e_fps->value();
        config.encoderPreference = getEncoderPreference();
        config.minBitrate = ui->spinBox_e_bps_min->value();
        config.maxBitrate = ui->spinBox_e_bps_max->value();
        ret = m_video->setVideoEncoderConfig(config);
        if (ret < 0) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("setVideoEncoderConfig error"), QMessageBox::Ok);
            box.exec();
            return;
        }
        ui->widget_log->appendAPI("setVideoEncoderConfig");
    }
}

void VideoConfigWidget::onComboMirrorClicked(const QString& text) //镜像
{
    if (m_video) {
        bytertc::MirrorType type = getMirrorType();
        int ret = m_video->setLocalVideoMirrorType(type);
        if (ret < 0) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("setLocalVideoMirrorType error"), QMessageBox::Ok);
            box.exec();
        }
        ui->widget_log->appendAPI("setLocalVideoMirrorType");
    }
}

void VideoConfigWidget::onComboLocalRenderTextChanged(const QString &text) //本地渲染模式
{
    if (m_video) {
        int ret = 0;
        bytertc::VideoCanvas cas;
        cas.view = nullptr;
        m_video->setLocalVideoCanvas(bytertc::kStreamIndexMain, cas);

        cas.view = (void*)ui->widget->winId();
        cas.render_mode = getRenderMode(ui->comboBox_c_render);
        cas.background_color = 0; //默认黑色背景
        ret = m_video->setLocalVideoCanvas(bytertc::kStreamIndexMain, cas);

        if (ret < 0) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("setLocalVideoMirrorType error"), QMessageBox::Ok);
            box.exec();
        }

        ui->widget_log->appendAPI("setLocalVideoCanvas");
    }
}

void VideoConfigWidget::onComboRemoteRenderTextChanged(const QString &text) //远端渲染模式
{
    if (m_rendering.empty()) {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QStringLiteral("没有远端流，无法修改渲染模式 error"), QMessageBox::Ok);
        box.exec();
    }
    if (m_video) {
        int ret = 0;
        bytertc::VideoCanvas cas;
        bytertc::RemoteStreamKey key;
        key.room_id = m_roomid.c_str();
        key.stream_index = bytertc::kStreamIndexMain;
        key.user_id = m_rendering.c_str();
        cas.background_color = 0;
        cas.render_mode = getRenderMode(ui->comboBox_remote_render);
        cas.view = nullptr;
        m_video->setRemoteVideoCanvas(key, cas);
        cas.view = (void*)ui->widget_2->winId();
        ret = m_video->setRemoteVideoCanvas(key, cas);
        if (ret < 0) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("setRemoteVideoCanvas error"), QMessageBox::Ok);
            box.exec();
        }
        ui->widget_log->appendAPI("setRemoteVideoCanvas");
    }
}

void VideoConfigWidget::onCheckWaterClicked(int state) { //水印
    if (m_video == nullptr) {
        return;
    }
    int ret = 0;
    bytertc::RTCWatermarkConfig config;
    if (ui->checkBox_water->isChecked()) {
        std::string path = QApplication::applicationDirPath().toStdString() + APIDemo::str_Video_Watermark;
        bytertc::ByteWatermark mark;
        config.visibleInPreview = true;
        mark.x = 0;
        mark.y = 0;
        mark.width = 0.5;
        mark.height = 0.5;
        config.positionInLandscapeMode = mark;
        config.positionInPortraitMode = mark;

        ret = m_video->setVideoWatermark(bytertc::kStreamIndexMain, path.c_str(), config);
        if (ret < 0) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("setVideoWatermark error:") + QString::number(ret), QMessageBox::Ok);
            box.exec();
        }
        ui->widget_log->appendAPI("setVideoWatermark");
    }
    else {
        ret = m_video->clearVideoWatermark(bytertc::kStreamIndexMain);
        if (ret < 0) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("clearVideoWatermark error") + QString::number(ret), QMessageBox::Ok);
            box.exec();
        }

        ui->widget_log->appendAPI("clearVideoWatermark");
    }
   
}

void VideoConfigWidget::onSigRoomStateChanged(std::string roomid, std::string uid, int state, std::string extra_info)
{
    QString log_str = QString("onRoomStateChanged,roomid:")
        + QString::fromStdString(roomid)
        + ",uid:" + QString::fromStdString(uid)
        + ",state:" + QString::number(state)
        + ",extra:" + QString::fromStdString(extra_info);
    ui->widget_log->appendCallback(log_str);
    m_roomid = roomid;

    if (state == 0) {
        ui->btn_join->setText(QStringLiteral("离房"));
        //ui->widget->setUserInfo(roomid, uid);
    }
    else {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("onRoomStateChanged:") + QString::number(state), QMessageBox::Ok);
        box.exec();
    }
}

void VideoConfigWidget::onSigUserPublishStream(std::string roomid, std::string uid, bytertc::MediaStreamType type)
{
    QString str = QString("onUserPublishStream, roomid:") + QString::fromStdString(roomid)
                      + ",uid:" + QString::fromStdString(uid);
    ui->widget_log->appendCallback(str);

    if (type & bytertc::kMediaStreamTypeVideo) {
        Stru_User user(roomid, uid);
        m_rusers[uid] = user;
        
        if (m_rendering.empty()) //没有正在渲染的用户
        {
            if (m_video) {
                bytertc::RemoteStreamKey key;
                bytertc::VideoCanvas cas;
                key.room_id = roomid.c_str();
                key.user_id = uid.c_str();
                key.stream_index = bytertc::StreamIndex::kStreamIndexMain;
                cas.render_mode = getRenderMode(ui->comboBox_remote_render);
                cas.view = (void*)ui->widget_2->winId();
                m_video->setRemoteVideoCanvas(key, cas);
                m_rendering = uid;
                ui->widget_log->appendAPI("setRemoteVideoCanvas");
            }
        }
    }
}

void VideoConfigWidget::onSigUserUnPublishStream(std::string roomid, std::string uid, bytertc::MediaStreamType type, bytertc::StreamRemoveReason)
{
    QString str = QString("onUserUnPublishStream, roomid:") + QString::fromStdString(roomid)
                  + ",uid:" + QString::fromStdString(uid);

    ui->widget_log->appendCallback(str);
    if (m_video == nullptr) return;
    if (type & bytertc::kMediaStreamTypeVideo) {
        if (m_rusers.count(uid) > 0) {
            m_rusers.erase(uid);
        }


        if (uid == m_rendering) {
            bytertc::RemoteStreamKey key;
            bytertc::VideoCanvas cas;

            m_rendering = "";
            key.room_id = roomid.c_str();
            key.stream_index = bytertc::kStreamIndexMain;
            key.user_id = uid.c_str();
            cas.view = nullptr;
            m_video->setRemoteVideoCanvas(key, cas);

            if (m_rusers.size() > 0) {
                key.room_id = m_rusers.begin()->second.roomId.c_str();
                key.user_id = m_rusers.begin()->first.c_str();
                key.stream_index = bytertc::StreamIndex::kStreamIndexMain;
                cas.render_mode = getRenderMode(ui->comboBox_remote_render);
                cas.view = (void*)ui->widget_2->winId();
                m_video->setRemoteVideoCanvas(key, cas);
                m_rendering = m_rusers.begin()->first;
                ui->widget_log->appendAPI("setRemoteVideoCanvas");
            }
        }
        
    }
}

bytertc::VideoCaptureConfig::CapturePreference VideoConfigWidget::getCapturePreference()
{
    bytertc::VideoCaptureConfig::CapturePreference result;
    QString str = ui->comboBox_capture_preference->currentText();
    if (str.contains("Auto")) {
        result = bytertc::VideoCaptureConfig::CapturePreference::KAuto;
    }
    else if (str.contains("Manual")) {
        result = bytertc::VideoCaptureConfig::CapturePreference::KManual;
    }
    else {
        result = bytertc::VideoCaptureConfig::CapturePreference::KAutoPerformance;
    }

    return result;
}

bytertc::VideoEncodePreference VideoConfigWidget::getEncoderPreference()
{
    bytertc::VideoEncodePreference result;
    QString str = ui->comboBox_e_preference->currentText();
    if (str.contains("Disabled")) {
        result = bytertc::kVideoEncodePreferenceDisabled;
    }
    else if (str.contains("Framerate")) {
        result = bytertc::kVideoEncodePreferenceFramerate;
    }
    else if (str.contains("Quality")) {
        result = bytertc::kVideoEncodePreferenceQuality;
    }
    else if (str.contains("Balance")) {
        result = bytertc::kVideoEncodePreferenceBalance;
    }
    else {
        result = bytertc::kVideoEncodePreferenceDisabled;
    }
    return result;
}

bytertc::MirrorType VideoConfigWidget::getMirrorType()
{
    bytertc::MirrorType type = bytertc::kMirrorTypeNone;
    QString str = ui->comboBox_morror->currentText();
    if (str.contains("None")) {
        type = bytertc::kMirrorTypeNone;
    }
    else if (str.contains("RenderAndEncoder")) {
        type = bytertc::kMirrorTypeRenderAndEncoder;
    }
    else {
        type = bytertc::kMirrorTypeRender;
    }
    return type;
}

bytertc::VideoRotation VideoConfigWidget::getRotation()
{
    bytertc::VideoRotation result = bytertc::kVideoRotation0;
    QString str = ui->comboBox_rotation->currentText();
    if (str.contains("90")) {
        result = bytertc::kVideoRotation90;
    }
    else if (str.contains("180")) {
        result = bytertc::kVideoRotation180;
    }
    else if (str.contains("270")) {
        result = bytertc::kVideoRotation270;
    }
    else {
        result = bytertc::kVideoRotation0;
    }

    return result;
}

void VideoConfigWidget::onComboboRotationClicked(const QString& text)
{
    if (m_video == nullptr) return;
    int ret = m_video->setVideoCaptureRotation(getRotation());
    if (ret < 0) {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("setVideoCaptureRotation error:") + QString::number(ret), QMessageBox::Ok);
        box.exec();
        return;
    }
    ui->widget_log->appendAPI("setVideoCaptureRotation");
}
