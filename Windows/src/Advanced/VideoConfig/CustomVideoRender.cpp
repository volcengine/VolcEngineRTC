#include "CustomVideoRender.h"
#include "ui_CustomVideoRender.h"

#include "bytertc_engine.h"
#include "bytertc_room.h"

#include "Resources.h"
#include "Utils.h"
#include "Config.h"

#include <QMessageBox>
#include <QImage>
#include <QDebug>
#include <QFile>
#include <QStringList>
#include <QImage>

#include "RenderRGB.h"
#include "PlayerYUVNV12.h"
#ifdef Q_OS_MAC
#include <CoreVideo/CoreVideo.h>
#endif // Q_OS_MAC


CustomVideoRender::CustomVideoRender(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::CustomVideoRender)
{
    ui->setupUi(this);
    initUI();
    initConnections();
    initRTCVideo();
    initPlayer();
    ui->btn_stop->setEnabled(false);
}

CustomVideoRender::~CustomVideoRender()
{
    cleanRTCVideo();
    cleanFile();
    cleanPlayer();
    cleanBuffer();
    delete ui;
}

void CustomVideoRender::initConnections()
{
    connect(ui->btn_join, &QPushButton::clicked, this, &CustomVideoRender::onBtnJoinClicked);
    connect(ui->btn_start, &QPushButton::clicked, this, &CustomVideoRender::onBtnStartClicked);
    connect(ui->btn_stop, &QPushButton::clicked, this, &CustomVideoRender::onBtnStopClicked);
    connect(this, &CustomVideoRender::updateFrame, this, &CustomVideoRender::onUpdateFrame);
}

void CustomVideoRender::initRTCVideo()
{
    m_handler.reset(new ByteRTCEventHandler());
    connect(m_handler.get(), &ByteRTCEventHandler::sigFirstLocalVideoFrameCaptured, this, &CustomVideoRender::onSigFirstLocalVideoFrameCaptured);
    bytertc::EngineConfig conf;
    conf.app_id = g_appid.c_str();
    conf.parameters = Utils::getParameters();
    m_video = bytertc::IRTCEngine::createRTCEngine(conf, m_handler.get());

    m_video->startAudioCapture();
    m_video->startVideoCapture();

    QStringList list = {"createRTCEngine", "startAudioCapture", "startVideoCapture"};
    appendAPI(list);

}

void CustomVideoRender::cleanRTCVideo()
{
    if (m_video) {
        if (m_room) {
            m_room->leaveRoom();
            m_room->setRTCRoomEventHandler(nullptr);
            m_room->destroy();
            m_room = nullptr;
        }

        bytertc::LocalVideoSinkConfig conf;
        m_video->setLocalVideoSink(nullptr, conf);
        m_video->stopAudioCapture();
        m_video->stopVideoCapture();
        bytertc::IRTCEngine::destroyRTCEngine();
        m_video = nullptr;
    }
    QStringList list = { "leaveRoom", "setRTCRoomEventHandler", "destroy", "stopAudioCapture", "stopVideoCapture", "destroyRTCEngine"};
    appendAPI(list);

}

void CustomVideoRender::initUI()
{
//#ifdef Q_OS_WIN
    QStringList list_fmt = {"I420", "NV12"};
    ui->comboBox_format->addItems(list_fmt);
//#endif
    ui->comboBox_format->addItem("RGBA");

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
    ui->label_state_first->setText(QStringLiteral("未收到"));
    ui->comboBox_format->setStyleSheet(APIDemo::str_qss_combobox);
    ui->comboBox_type->setStyleSheet(APIDemo::str_qss_combobox);
    ui->btn_start->setStyleSheet(APIDemo::str_qss_btn2_3);
    ui->btn_stop->setStyleSheet(APIDemo::str_qss_btn2_3);
    enableRender(false);

}

void CustomVideoRender::initPlayer()
{
    QHBoxLayout *lay = new QHBoxLayout;
    lay->setContentsMargins(6,0,6,0);
    lay->addStretch();

    if (m_yuvPlayer == nullptr) {
        m_yuvPlayer = new PlayerYUVNV12(this);
        lay->addWidget(m_yuvPlayer);
        m_yuvPlayer->setFixedSize(320, ui->widget_u->height());
    }
    if (m_rgbPlayer == nullptr) {
        m_rgbPlayer = new RenderRGB(this);
        lay->addWidget(m_rgbPlayer);
        m_rgbPlayer->hide();
        m_rgbPlayer->setFixedSize(320, ui->widget_u->height());
    }
    lay->addStretch();
    ui->widget_u->setLayout(lay);
}

void CustomVideoRender::cleanPlayer()
{
    if (m_yuvPlayer) {
        delete m_yuvPlayer;
        m_yuvPlayer = nullptr;
    }
}

void CustomVideoRender::cleanBuffer()
{
    std::lock_guard<std::mutex> locker(m_mutex_vframe);
    if (m_vframe) {
        m_vframe->clean();
        m_vframe = nullptr;
    }
}

ByteRTCRoomHandler *CustomVideoRender::createRoomHandler(std::string roomid, std::string uid)
{
    auto roomH = new ByteRTCRoomHandler(roomid, uid);
    connect(roomH, &ByteRTCRoomHandler::sigRoomStateChanged, this, &CustomVideoRender::onSigRoomStateChanged);
    connect(roomH, &ByteRTCRoomHandler::sigUserPublishStreamVideo, this, &CustomVideoRender::onSigUserPublishStreamVideo);
    connect(roomH, &ByteRTCRoomHandler::sigUserPublishStreamAudio, this, &CustomVideoRender::onSigUserPublishStreamAudio);

    return roomH;

}

bytertc::LocalVideoSinkPosition CustomVideoRender::getPosition()
{
    bytertc::LocalVideoSinkPosition pos;
    QString text = ui->comboBox_type->currentText();
    if (text.contains(QStringLiteral("采集后"))) {
        pos = bytertc::LocalVideoSinkPosition::kLocalVideoSinkPositionAfterCapture;
    } else {
        pos = bytertc::LocalVideoSinkPosition::kLocalVideoSinkPositionAfterPreProcess;
    }

    return pos;
}

bytertc::VideoPixelFormat CustomVideoRender::getPixelFormat()
{
    m_yuvPlayer->hide();
    m_rgbPlayer->hide();
    bytertc::VideoPixelFormat format = bytertc::kVideoPixelFormatUnknown;
    QString text = ui->comboBox_format->currentText();
    if (text.contains("I420")) {
        format = bytertc::kVideoPixelFormatI420;
        m_yuvPlayer->show();
    } else if (text.contains("NV12")) {
        format = bytertc::kVideoPixelFormatNV12;
        m_yuvPlayer->show();
    } else if (text.contains("NV21")) {
        format = bytertc::kVideoPixelFormatNV21;
    } else if (text.contains("RGB24")) {
        format = bytertc::kVideoPixelFormatRGB24;
    } else if (text.contains("RGBA")) {
        format = bytertc::kVideoPixelFormatRGBA;
        m_rgbPlayer->show();
    } else if (text.contains("ARGB")) {
        format = bytertc::kVideoPixelFormatARGB;
    } else if (text.contains("BGRA")) {
        format = bytertc::kVideoPixelFormatBGRA;
    } else if (text.contains("Texture2D")) {
        format = bytertc::kVideoPixelFormatTexture2D;
    } else if (text.contains("TextureOES")) {
        format = bytertc::kVideoPixelFormatTextureOES;
    } else {
        format = bytertc::kVideoPixelFormatUnknown;
    }
    return format;
}

void CustomVideoRender::onBtnJoinClicked()
{
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

        m_video->startAudioCapture();
        m_video->startVideoCapture();

        auto handler = createRoomHandler(str_room, str_uid);
        m_room->setRTCRoomEventHandler(handler);

        bytertc::UserInfo info;
        bytertc::RTCRoomConfig config;

        info.uid = str_uid.c_str();
        config.is_auto_publish_audio = true;
        config.is_auto_publish_video = true;
        config.is_auto_subscribe_audio = true;
        config.is_auto_subscribe_video = true;
        config.room_profile_type = bytertc::kRoomProfileTypeCommunication;
        str_token = Utils::generateToken(str_room, str_uid);
        int ret = m_room->joinRoom(str_token.c_str(), info, true, config);
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
        ui->btn_join->setText(QStringLiteral("进房"));
        list = QStringList{ "leaveRoom", "destroy"};
    }
    appendAPI(list);

}

void CustomVideoRender::onBtnInitClicked()
{
    initRTCVideo();
}

void CustomVideoRender::onBtnUninitClicked()
{
    cleanRTCVideo();
}

void CustomVideoRender::onBtnStartClicked()
{
    if (m_video == nullptr) return;
    bytertc::LocalVideoSinkConfig conf;
    conf.pixel_format = getPixelFormat();
    conf.position = getPosition();
    int ret = m_video->setLocalVideoSink(this, conf);
    if (ret < 0) {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("setLocalVideoRender, ret=") + QString::number(ret), QMessageBox::Ok);
        box.exec();
        return;
    }

    openFile(getSuffixByPixelFormat(conf.pixel_format));
    appendAPI("setLocalVideoRender");
    ui->btn_stop->setEnabled(true);
}

void CustomVideoRender::onBtnStopClicked()
{
    if (m_video == nullptr) return;
    bytertc::LocalVideoSinkConfig conf;
    conf.pixel_format = getPixelFormat();
    conf.position = getPosition();
    closeFile();
    int ret = m_video->setLocalVideoSink(nullptr, conf);
    if (ret < 0) {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("setLocalVideoRender, ret=") + QString::number(ret), QMessageBox::Ok);
        box.exec();
        return;
    }
    appendAPI("setLocalVideoRender");
    ui->btn_start->setEnabled(true);
}

void CustomVideoRender::onSigRoomStateChanged(std::string roomid, std::string uid, int state, std::string extra_info)
{
    QString log_str = QString("onRoomStateChanged,roomid:")
        + QString::fromStdString(roomid)
        + ",uid:" + QString::fromStdString(uid)
        + ",state:" + QString::number(state)
        + ",extra:" + QString::fromStdString(extra_info);
    appendCallback(log_str);
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

void CustomVideoRender::onSigUserPublishStreamVideo(std::string stream_id, std::string roomid, std::string uid, bool pub)
{
    QString log_str = QString("onUserPublishStreamVideo")
        + ",stream_id:" + QString::fromStdString(stream_id)
        + ",roomid:" + QString::fromStdString(roomid)
        + ",uid:" + QString::fromStdString(uid)
        + ",pub:" + QString::number(pub);
    appendCallback(log_str);
}

void CustomVideoRender::onSigUserPublishStreamAudio(std::string stream_id, std::string roomid, std::string uid, bool pub)
{
    QString log_str = QString("onUserPublishStreamAudio")
        + ",stream_id:" + QString::fromStdString(stream_id)
        + ",roomid:" + QString::fromStdString(roomid)
        + ",uid:" + QString::fromStdString(uid)
        + ",pub:" + QString::number(pub);

    appendCallback(log_str);
}



void CustomVideoRender::onSigFirstLocalVideoFrameCaptured(bytertc::VideoFrameInfo info)
{

    if (m_video) {
        ui->label_state_first->setText(QStringLiteral("已收到"));
        enableRender(true);
    }
}

bool CustomVideoRender::onFrame(bytertc::IVideoFrame *video_frame)
{
    if (video_frame == nullptr) return false;
    qDebug() << Q_FUNC_INFO << "width:" << video_frame->width()
        << ",height:" << video_frame->height()
        << ",fmt:" << video_frame->pixelFormat()
        << ",stride0:" << video_frame->planeStride(0)
        << ",stride1:" << video_frame->planeStride(1)
        << ",stride2:" << video_frame->planeStride(2)
         << ",data0~data3:" << video_frame->planeStride(0)
         << video_frame->planeStride(1) << video_frame->planeStride(2)
         << ",videoContentType:" << video_frame->contentType();

    std::lock_guard<std::mutex> locker(m_mutex_vframe);
    int size = video_frame->width() * video_frame->height();
    if (m_vframe && (m_vframe->width != video_frame->width() || m_vframe->height != video_frame->height() || m_vframe->format != video_frame->pixelFormat())) {
        m_vframe->clean();
        m_vframe = nullptr;
    }

    if (m_vframe == nullptr) {
        m_vframe = new VFrame();
        m_vframe->data[0] = new uint8_t[size*8];
        m_vframe->data[1] = new uint8_t[size*2];
        m_vframe->data[2] = new uint8_t[size*2];
    }
    m_vframe->format = (int)video_frame->pixelFormat();
    m_vframe->width = video_frame->width();
    m_vframe->height = video_frame->height();

    switch (video_frame->pixelFormat())
    {
    case bytertc::kVideoPixelFormatI420:
        if (video_frame->bufferType() == bytertc::kVideoBufferTypeRawMemory) {
            memcpy(m_vframe->data[0], video_frame->planeData(0), video_frame->planeStride(0) * video_frame->height());
            memcpy(m_vframe->data[1], video_frame->planeData(1), video_frame->planeStride(1) * video_frame->height() / 2);
            memcpy(m_vframe->data[2], video_frame->planeData(2), video_frame->planeStride(2) * video_frame->height() / 2);
            for (int i = 0; i < video_frame->numberOfPlanes(); i++) {
                m_vframe->linesize[i] = video_frame->planeStride(i);
            }

        } else {
#ifdef Q_OS_MAC

            CVPixelBufferRef sourceBuffer = reinterpret_cast<CVPixelBufferRef>(video_frame->hwBuffer());
            if (sourceBuffer) {
                CVPixelBufferLockBaseAddress(sourceBuffer, 0);
                int planeSizeY = CVPixelBufferGetBytesPerRowOfPlane(sourceBuffer, 0);
                int planeSizeU = CVPixelBufferGetBytesPerRowOfPlane(sourceBuffer, 1);
                int planeSizeV = CVPixelBufferGetBytesPerRowOfPlane(sourceBuffer, 2);

                uint8_t * yData = static_cast<uint8_t *>(CVPixelBufferGetBaseAddressOfPlane(sourceBuffer, 0));
                uint8_t * uData = static_cast<uint8_t *>(CVPixelBufferGetBaseAddressOfPlane(sourceBuffer, 1));
                uint8_t * vData = static_cast<uint8_t *>(CVPixelBufferGetBaseAddressOfPlane(sourceBuffer, 2));
                CVPixelBufferUnlockBaseAddress(sourceBuffer, 0);

                if (m_vframe) {
                    memcpy(m_vframe->data[0], yData, planeSizeY*video_frame->height());
                    memcpy(m_vframe->data[1], uData, planeSizeU*video_frame->height()/2);
                    memcpy(m_vframe->data[2], vData, planeSizeV*video_frame->height()/2);
                    m_vframe->linesize[0] = planeSizeY;
                    m_vframe->linesize[1] = planeSizeU;
                    m_vframe->linesize[2] = planeSizeV;
                    qDebug() << Q_FUNC_INFO << "mac,planY=" << planeSizeY << ",plansizeu:" << planeSizeU
                             << ",v=" << planeSizeV;
                }
            }
#endif // Q_OS_MAC
        emit updateFrame();
        break;
    }

    case bytertc::kVideoPixelFormatNV12:
        if (video_frame->bufferType() == bytertc::kVideoBufferTypeRawMemory) {
            memcpy(m_vframe->data[0], video_frame->planeData(0), video_frame->height()*video_frame->planeStride(0));
            memcpy(m_vframe->data[1], video_frame->planeData(1), video_frame->height()*video_frame->planeStride(1) / 2);
            for (int i = 0; i < video_frame->numberOfPlanes(); i++) {
                m_vframe->linesize[i] = video_frame->planeStride(i);
            }
        } else {
#ifdef  Q_OS_MAC
            CVPixelBufferRef sourceBuffer = reinterpret_cast<CVPixelBufferRef>(video_frame->hwBuffer());
            if (sourceBuffer) {
                CVPixelBufferLockBaseAddress(sourceBuffer, 0);
                int planeSizeY = CVPixelBufferGetBytesPerRowOfPlane(sourceBuffer, 0);
                int planeSizeUV = CVPixelBufferGetBytesPerRowOfPlane(sourceBuffer, 1);
                uint8_t * yData = static_cast<uint8_t *>(CVPixelBufferGetBaseAddressOfPlane(sourceBuffer, 0));
                uint8_t * uvData = static_cast<uint8_t *>(CVPixelBufferGetBaseAddressOfPlane(sourceBuffer, 1));
                CVPixelBufferUnlockBaseAddress(sourceBuffer, 0);
                memcpy(m_vframe->data[0], yData, planeSizeY*video_frame->height());
                memcpy(m_vframe->data[1], uvData, planeSizeUV*video_frame->height()/2);
                m_vframe->linesize[0] = planeSizeY;
                m_vframe->linesize[1] = planeSizeUV;
            }
#endif //  Q_OS_MAC
        }


        emit updateFrame();
        break;

    case bytertc::kVideoPixelFormatRGBA:
        m_vframe->linesize[0] = video_frame->planeStride(0);
        memcpy(m_vframe->data[0], video_frame->planeData(0), video_frame->planeStride(0)*video_frame->height());
        emit updateFrame();
        break;

    case bytertc::kVideoPixelFormatBGRA:
        break;
    default:
        break;
    }
    return true;
}

int CustomVideoRender::getRenderElapse()
{
    return 0;
}

void CustomVideoRender::openFile(std::string suffix)
{
    if (m_frame_file == nullptr) {
        QString file_name = QString("render.%1").arg(QString::fromStdString(suffix));
        m_frame_file = new QFile(file_name);
        m_frame_file->open(QIODevice::WriteOnly);
        m_file_names.push_back(file_name.toStdString());
    }

}

void CustomVideoRender::closeFile()
{
    if (m_frame_file) {
        m_frame_file->close();
        delete m_frame_file;
        m_frame_file = nullptr;
    }
}

void CustomVideoRender::cleanFile()
{
    for (auto m : m_file_names) {
        QFile::remove(QString::fromStdString(m));
    }
}

std::string CustomVideoRender::getSuffixByPixelFormat(bytertc::VideoPixelFormat fmt)
{
    std::string suffix = "yuv";
    switch (fmt)
    {
    case bytertc::kVideoPixelFormatUnknown:
        break;
    case bytertc::kVideoPixelFormatI420:
        suffix = "yuv";
        break;
    case bytertc::kVideoPixelFormatNV12:
        suffix = "nv12";
        break;
    case bytertc::kVideoPixelFormatNV21:
        suffix = "nv21";
        break;
    case bytertc::kVideoPixelFormatRGB24:
        suffix = "rgb24";
        break;
    case bytertc::kVideoPixelFormatRGBA:
        suffix = "rgba";
        break;
    case bytertc::kVideoPixelFormatARGB:
        suffix = "argb";
        break;
    case bytertc::kVideoPixelFormatBGRA:
        suffix = "bgra";
        break;
    case bytertc::kVideoPixelFormatTexture2D:
        suffix = "Texture2D";
        break;
    case bytertc::kVideoPixelFormatTextureOES:
        suffix = "TextureOES";
        break;
    default:
        break;
    }
    return suffix;
}

void CustomVideoRender::enableRender(bool enable)
{
    ui->comboBox_format->setEnabled(enable);
    ui->comboBox_type->setEnabled(enable);
    ui->btn_start->setEnabled(enable);
}

void CustomVideoRender::writeFile(bytertc::IVideoFrame * video_frame)
{
    if (m_width != video_frame->width() || m_height != video_frame->height()) { //视频大小发生变化
        closeFile();
        m_width = video_frame->width();
        m_height = video_frame->height();
        openFile(getSuffixByPixelFormat(video_frame->pixelFormat()));
    }

    if (video_frame->pixelFormat() == bytertc::kVideoPixelFormatI420) {
        if (video_frame->planeStride(0) > video_frame->width()
            || video_frame->planeStride(1) > video_frame->width() / 2
            || video_frame->planeStride(2) > video_frame->width() / 2) {
            //TODO

        } else {
            uint64_t size = (uint64_t)video_frame->width() * (uint64_t)video_frame->height();
            static uint8_t* buffer = new uint8_t [size*3/2];

            memcpy(buffer, video_frame->planeData(0), size);
            memcpy((buffer + size), video_frame->planeData(1), size / 4);
            memcpy((buffer + size * 5/4), video_frame->planeData(2), size/4);
            if (m_frame_file) {
                m_frame_file->write((const char*)buffer, size * 3 / 2);
            }

        }

    } else if (video_frame->pixelFormat() == bytertc::kVideoPixelFormatNV12) {
        uint64_t size = (uint64_t)video_frame->width() * (uint64_t)video_frame->height();
        static uint8_t* buffer_nv12 = new uint8_t[size * 3 / 2];

        memcpy(buffer_nv12, video_frame->planeData(0), size);
        memcpy((buffer_nv12 + size), video_frame->planeData(1), size / 2);
        if (m_frame_file) {
            m_frame_file->write((const char*)buffer_nv12, size * 3 / 2);
        }

    } else if (video_frame->pixelFormat() == bytertc::kVideoPixelFormatRGBA) {
        uint64_t size = (uint64_t)video_frame->width() * (uint64_t)video_frame->height()*4;
        static uint8_t* buffer_rgba = new uint8_t[size];

        memcpy(buffer_rgba, video_frame->planeData(0), size);
        
        if (m_frame_file) {
            m_frame_file->write((const char*)buffer_rgba, size);
        }
    } else {
        return ;
    }
    return ;
}

void CustomVideoRender::onUpdateFrame()
{
    std::lock_guard<std::mutex> locker(m_mutex_vframe);
    if (m_vframe == nullptr) return;
    if (m_vframe->format == bytertc::kVideoPixelFormatRGBA) {
        QImage img(m_vframe->data[0], m_vframe->width, m_vframe->height, m_vframe->linesize[0], QImage::Format_RGBA8888);
        m_rgbPlayer->setImage(img);
    } else {
       m_yuvPlayer->repaint(m_vframe);
    }

}
