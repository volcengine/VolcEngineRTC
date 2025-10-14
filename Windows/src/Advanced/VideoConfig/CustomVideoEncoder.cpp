#include "CustomVideoEncoder.h"
#include "ui_CustomVideoEncoder.h"


#include "Config.h"
#include "Resources.h"
#include "Utils.h"

#include "bytertc_engine.h"
#include "bytertc_room.h"

#include <QMessageBox>
#include <QDebug>
#include <QDateTime>
#include <QFileDialog>


#include <chrono>
#include "H264Reader.h"

//#include "VideoDecoder.h"

/** TODO 完善
* 功能名称： VolcEngineRTC 自定义编码
* 功能简单描述：
* 参考文档：


*
* 此功能涉及的API及回调：
*     createRTCEngine 创建引擎
*     destroyRTCEngine 销毁引擎
*     startAudioCapture 开启音频采集
*     startVideoCapture 开启视频采集
*     createRTCRoom 创建RTC房间
*     joinRoom 进入RTC房间
*     leaveRoom 离开RTC房间
*     destroy 销毁RTC房间
*

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
*    本Demo演示功能：外部推送编码后的视频帧
*    为了展示简单，所有功能的token都由客户端生成，接口Utils::generateToken，接入SDK时建议将Token生成逻辑放在服务端
*/

CustomVideoEncoder::CustomVideoEncoder(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::CustomVideoEncoder)
{
    ui->setupUi(this);
    initConnections();
    initRTCVideo();
    initUI();
    m_h264_reader.reset(new H264Reader());
}

CustomVideoEncoder::~CustomVideoEncoder()
{
    m_thread_run = false;
    if (m_push_thread && m_push_thread->joinable()) {
        m_push_thread->join();
        delete m_push_thread;
        m_push_thread = nullptr;
    }
    cleanRTCVideo();
    m_h264_reader.release();
    delete ui;
}

void CustomVideoEncoder::initConnections()
{
    connect(ui->btn_join, &QPushButton::clicked, this, &CustomVideoEncoder::onBtnJoinClicked);
    connect(ui->btn_choose, &QPushButton::clicked, this, &CustomVideoEncoder::onBtnChooseClicked);
}

void CustomVideoEncoder::initRTCVideo()
{
    m_handler.reset(new ByteRTCEventHandler());
    bytertc::EngineConfig conf;
    conf.app_id = g_appid.c_str();
    conf.parameters = Utils::getParameters();
    m_video = bytertc::IRTCEngine::createRTCEngine(conf, m_handler.get());
    m_video->startAudioCapture();
    m_video->startVideoCapture();
    

    QStringList list = {"createRTCEngine", "startAudioCapture", "startVideoCapture"};
    appendAPI(list);

}

void CustomVideoEncoder::cleanRTCVideo()
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
        bytertc::IRTCEngine::destroyRTCEngine();
        m_video = nullptr;
        list = list + QStringList{"stopAudioCapture", "stopVideoCapture", "destroyRTCEngine"};
        appendAPI(list);
    }

}

void CustomVideoEncoder::initUI()
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
    ui->btn_join->setFixedSize(118, 32);
    ui->btn_choose->setStyleSheet(APIDemo::str_qss_btn1);
    ui->btn_choose->setFixedSize(118,32);
}

std::unique_ptr<ByteRTCRoomHandler> CustomVideoEncoder::createRoomHandler(std::string roomid, std::string uid)
{
    std::unique_ptr<ByteRTCRoomHandler> roomH = std::make_unique<ByteRTCRoomHandler>(roomid, uid);
    connect(roomH.get(), &ByteRTCRoomHandler::sigRoomStateChanged, this, &CustomVideoEncoder::onSigRoomStateChanged);
    connect(roomH.get(), &ByteRTCRoomHandler::sigUserPublishStreamVideo, this, &CustomVideoEncoder::onSigUserPublishStreamVideo);
    connect(roomH.get(), &ByteRTCRoomHandler::sigUserPublishStreamAudio, this, &CustomVideoEncoder::onSigUserPublishStreamAudio);

    return roomH;

}

void CustomVideoEncoder::pushThreadRun()
{
    if (m_h264_reader.get() == nullptr || m_video == nullptr) return;

    while (m_thread_run)
    {
        int ret = 0;
        std::vector<uint8_t> data;
        H264Reader::FrameType type;

        int len = m_h264_reader->getNextFrame(data, type);
        if (data.size() == 0) return;

        uint8_t* raw_data = new uint8_t[data.size()];
        memcpy(raw_data, data.data(), data.size());

        auto now = std::chrono::system_clock::now();

        bytertc::EncodedVideoFrameBuilder builder;
        builder.codec_type = bytertc::kVideoCodecTypeH264;
        builder.data = raw_data;
        builder.picture_type = bytertc::VideoPictureType(type);
        builder.rotation = bytertc::kVideoRotation0;
        builder.size = data.size();
        builder.timestamp_us = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()).count();
        builder.timestamp_dts_us = builder.timestamp_us;
        
        builder.width = m_h264_reader->getWidth(); 
        builder.height = m_h264_reader->getHeight();
        builder.memory_deleter = nullptr;

        bytertc::IEncodedVideoFrame* frame = bytertc::buildEncodedVideoFrame(builder);
        
        if (frame && frame->data()) {
            bytertc::IEncodedVideoFrame* frame2 = frame->shallowCopy();
            ret = m_video->pushExternalEncodedVideoFrame(bytertc::kStreamIndexMain, 0, frame2);
            if (ret < 0) {
                qWarning() << Q_FUNC_INFO << "pushExternalEncodedVideoFrame error, ret:" << ret;
                continue;
            }
        }
        delete []raw_data;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000/m_h264_reader->getFps()));
    }
    
}

bool CustomVideoEncoder::PushEncodeFrame(int w, int h, int fps, std::vector<uint8_t>& frame, bool is_key_frame)
{
    return false;
    if (frame.size() <= 0) {
        return false;
    }
    static unsigned char* buffer = (unsigned char*)malloc(frame.size());
    if (!buffer) {
        return false;
    }

    memcpy(buffer, frame.data(), frame.size());

    bytertc::EncodedVideoFrameBuilder builder;
    builder.picture_type = is_key_frame ? bytertc::VideoPictureType::kVideoPictureTypeI : bytertc::VideoPictureType::kVideoPictureTypeP;
    builder.data = buffer;
    builder.width = w;
    builder.height = h;
    builder.size = frame.size();
    builder.codec_type = bytertc::VideoCodecType::kVideoCodecTypeH264;

    auto fun_del = [](uint8_t* data, int size, void* user_opaque) {
        delete[]data; data = nullptr; return 0;
    };

    int(*fun_ptr)(uint8_t*, int, void*) = fun_del;
    builder.memory_deleter = fun_ptr;

    bytertc::IEncodedVideoFrame* pEncodeFrame = bytertc::buildEncodedVideoFrame(builder);
    if (pEncodeFrame && pEncodeFrame->data()) {
        m_video->pushExternalEncodedVideoFrame(bytertc::kStreamIndexMain, 0, pEncodeFrame);
    }

    pEncodeFrame->release();
    return true;
}

void CustomVideoEncoder::onBtnJoinClicked(){
    std::string str_room = ui->lineEdit_room->text().toStdString();
    std::string str_uid = ui->lineEdit_uid->text().toStdString();
    std::string str_token;
    QString qstr_error;
    if (m_video == nullptr) {
        qWarning() << Q_FUNC_INFO << "m_video = nullptr";
        return;
    }

    if (ui->btn_join->text() == QStringLiteral("进房")) {
        if (!Utils::checkIDValid(QString::fromStdString(str_uid), QStringLiteral("用户名"), qstr_error)) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), "uid error " + qstr_error, QMessageBox::Ok);
            box.exec();
            return;

        }

        if (!Utils::checkIDValid(QString::fromStdString(str_room), QStringLiteral("房间号"), qstr_error)) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), "roomid error " + qstr_error, QMessageBox::Ok);
            box.exec();
            return;
        }

        m_room = m_video->createRTCRoom(str_room.c_str());
        if (m_room == nullptr) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("createRTCRoom error"), QMessageBox::Ok);
            box.exec();
            return;
        }

        m_room_handler = createRoomHandler(str_room, str_uid);
        m_room->setRTCRoomEventHandler(m_room_handler.get());

        m_video->setVideoSourceType(bytertc::kStreamIndexMain, bytertc::kVideoSourceTypeEncodedWithoutAutoSimulcast);
        m_video->setExternalVideoEncoderEventHandler(this);//需要在进房前调用

        bytertc::VideoCanvas cavs;
        cavs.view = (void*)ui->widget->getWinId();
        cavs.render_mode = bytertc::kRenderModeHidden;
        m_video->setLocalVideoCanvas(bytertc::kStreamIndexMain, cavs);
        ui->widget->setUserInfo(str_room, str_uid);

        bytertc::UserInfo info;
        bytertc::RTCRoomConfig config;

        info.uid = str_uid.c_str();
        config.is_publish_audio = true;
        config.is_publish_video = true;
        config.is_auto_subscribe_audio = true;
        config.is_auto_subscribe_video = true;

        str_token = Utils::generateToken(str_room, str_uid);
        int ret = m_room->joinRoom(str_token.c_str(), info, true, config);
        if (ret < 0) {
            QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("joinRoom error"), QMessageBox::Ok);
            box.exec();
            return;
        }

        QStringList list = QStringList{"createRTCRoom", "setRTCRoomEventHandler", "setLocalVideoCanvas", "joinRoom"};
        appendAPI(list);
    } else { //离房
        if (m_room) {
            m_room->leaveRoom();
            m_room->destroy();
            m_room = nullptr;
            ui->btn_join->setText(QStringLiteral("进房"));
            QStringList list = {"leaveRoom", "destroy"};
            appendAPI(list);
        }
    }

}

void CustomVideoEncoder::onBtnStartClicked()
{
    if (m_video == nullptr) return;
    m_video->registerRemoteEncodedVideoFrameObserver(this);
}

void CustomVideoEncoder::onBtnStopClicked()
{

}

void CustomVideoEncoder::onBtnChooseClicked()
{
    if (m_h264_reader == nullptr) return;
    QString exe_path = QApplication::applicationDirPath() + "/Resources/video";
    QFileDialog dlg(this, "open encoded h264 file", exe_path, "(*.h264)");
    QString file_path;
    if (dlg.exec() == QDialog::Accepted) {
        QStringList list = dlg.selectedFiles();
        ui->lineEdit_file->setText(list.first());
        m_h264_reader->loadFile(list.first().toStdString());
    }

}

void CustomVideoEncoder::onSigRoomStateChanged(std::string roomid, std::string uid, int state, std::string extra_info)
{
    QString log_str = QString("onRoomStateChanged,roomid:")
        + QString::fromStdString(roomid)
        + ",uid:" + QString::fromStdString(uid)
        + ",state:" + QString::number(state)
        + ",extra:" + QString::fromStdString(extra_info);
    appendCallback(log_str);

    if (state == 0) {
        ui->btn_join->setText(QStringLiteral("离房"));
        ui->widget->setUserInfo(roomid, uid);
    }
    else {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("onRoomStateChanged:") + QString::number(state), QMessageBox::Ok);
        box.exec();

    }

}

void CustomVideoEncoder::onSigUserPublishStreamVideo(std::string stream_id, std::string roomid, std::string uid, bool pub)
{
    QString log_str = QString("onUserPublishStreamVideo")
        + ",stream_id:" + QString::fromStdString(stream_id)
        + ",roomid:" + QString::fromStdString(roomid)
        + ",uid:" + QString::fromStdString(uid)
        + ",pub:" + QString::number(pub);
    appendCallback(log_str);

    if (m_video == nullptr) return;
    if (pub) {
        m_remote_uids.insert(uid);
        if (m_rendering.empty()) //没有正在渲染的用户
        {
            //bytertc::RemoteStreamKey key;
            bytertc::VideoCanvas cas;
            //key.room_id = roomid.c_str();
            //key.user_id = uid.c_str();
            //key.stream_index = bytertc::StreamIndex::kStreamIndexMain;
            cas.render_mode = bytertc::kRenderModeHidden;
            cas.view = (void*)ui->widget_2->getWinId();
            m_video->setRemoteVideoCanvas(stream_id.c_str(), cas);
            m_rendering = uid;
            ui->widget_2->setUserInfo(roomid, uid);
            appendAPI("setRemoteVideoCanvas");
        }
    }

}

void CustomVideoEncoder::onSigUserPublishStreamAudio(std::string stream_id, std::string roomid, std::string uid, bool pub)
{
    QString log_str = QString("onUserPublishStreamAudio")
        + ",stream_id:" + QString::fromStdString(stream_id)
        + ",roomid:" + QString::fromStdString(roomid)
        + ",uid:" + QString::fromStdString(uid)
        + ",pub:" + QString::number(pub);

    appendCallback(log_str);
}

void CustomVideoEncoder::onStart(bytertc::StreamIndex index)
{
    qDebug() << Q_FUNC_INFO << "start thread";
    if (m_video == nullptr) return;

    if (m_push_thread == nullptr)
        m_push_thread = new std::thread(&CustomVideoEncoder::pushThreadRun, this);

    m_thread_run = true;
}

void CustomVideoEncoder::onStop(bytertc::StreamIndex index)
{
    qDebug() << Q_FUNC_INFO << "stop thread";
    m_thread_run = false;
    if (m_push_thread && m_push_thread->joinable()) {
        m_push_thread->join();
        delete m_push_thread;
        m_push_thread = nullptr;
    }
}

void CustomVideoEncoder::onRateUpdate(bytertc::StreamIndex index, int32_t video_index, bytertc::VideoRateInfo info)
{
    //TODO 
}

void CustomVideoEncoder::onRequestKeyFrame(bytertc::StreamIndex index, int32_t video_index)
{
    qDebug() << Q_FUNC_INFO << "video_index=" << video_index;
    if (m_video == nullptr) return;

    std::vector<uint8_t> data;
    H264Reader::FrameType type;

    int len = m_h264_reader->getKeyFrame(data);
    if (data.size() == 0) return;

    auto now = std::chrono::system_clock::now();

    bytertc::EncodedVideoFrameBuilder builder;
    builder.codec_type = bytertc::kVideoCodecTypeH264;
    builder.data = data.data();
    builder.picture_type = bytertc::VideoPictureType::kVideoPictureTypeI;
    builder.rotation = bytertc::kVideoRotation0;
    builder.size = data.size();
    builder.timestamp_us = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()).count();
    builder.timestamp_dts_us = builder.timestamp_us;

    builder.width = m_h264_reader->getWidth();
    builder.height = m_h264_reader->getHeight();
    builder.memory_deleter = nullptr;

    bytertc::IEncodedVideoFrame* frame = bytertc::buildEncodedVideoFrame(builder);
    bytertc::IEncodedVideoFrame* frame2 = frame->shallowCopy();
    int ret = m_video->pushExternalEncodedVideoFrame(bytertc::kStreamIndexMain, 0, frame2);
    if (ret < 0) {
        qDebug() << Q_FUNC_INFO << "ret:" << ret;
    }
    
}

void CustomVideoEncoder::onActiveVideoLayer(bytertc::StreamIndex index, int32_t video_index, bool active)
{
}

void CustomVideoEncoder::onRemoteEncodedVideoFrame(const bytertc::RemoteStreamKey& stream_info, 
    const bytertc::IEncodedVideoFrame& video_stream)
{
    return;
    static int index = 0;

    if (m_video) {
        unsigned char* buffer = (unsigned char*)malloc(video_stream.dataSize());
        memcpy(buffer, video_stream.data(), video_stream.dataSize());
        auto now = std::chrono::system_clock::now();
        bytertc::EncodedVideoFrameBuilder builder;
        builder.codec_type = bytertc::kVideoCodecTypeH264;
        builder.data = buffer;
        builder.picture_type = video_stream.pictureType();
        builder.rotation = video_stream.rotation();
        builder.size = video_stream.dataSize();
        builder.timestamp_us = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()).count();
        builder.timestamp_dts_us = builder.timestamp_us;
        builder.height = video_stream.height();
        builder.width = video_stream.width();
        builder.memory_deleter = nullptr;


        bytertc::IEncodedVideoFrame* fff = bytertc::buildEncodedVideoFrame(builder);
        bytertc::IEncodedVideoFrame*  fff22 = fff->shallowCopy();
        int ret = m_video->pushExternalEncodedVideoFrame(bytertc::kStreamIndexMain, 0, fff22);
        //qDebug() << Q_FUNC_INFO << "ret=" << ret << ",index="
        //    << index++ << ",frametype:" << video_stream.pictureType()
        //    << ", size=" << video_stream.dataSize();


        

        std::string file_name = "remote_h264_" + std::to_string(video_stream.width()) + "_" + std::to_string(video_stream.height()) + ".h264";
        static FILE *file = fopen(file_name.c_str(), "wb");
        if (file) {
            int wret = fwrite(video_stream.data(), sizeof(uint8_t), video_stream.dataSize(), file);
            qDebug() << Q_FUNC_INFO << wret << video_stream.data() << "size:" << video_stream.dataSize();
        }

        free(buffer);
    }
}
