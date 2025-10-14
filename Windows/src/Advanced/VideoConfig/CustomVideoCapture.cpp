#include "CustomVideoCapture.h"
#include "ui_CustomVideoCapture.h"

#include "bytertc_engine.h"
#include "bytertc_room.h"

#include "Resources.h"
#include "Utils.h"
#include "Config.h"

#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QTimer>
#include <QDateTime>

#include <stdio.h>

QString qstr_file_nv12 = "/Resources/video/render_256x144_nv12.yuv";
QString qstr_file_yuv = "/Resources/video/render_256x144_yuv420.yuv";
QString qstr_file_rgba = "/Resources/video/render_320x180_rgba.rgba";


CustomVideoCapture::CustomVideoCapture(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::CustomVideoCapture)
{
    ui->setupUi(this);
    initUI();
    initConnections();
    initRTCVideo();
}

CustomVideoCapture::~CustomVideoCapture()
{
    cleanRTCVideo();
    delete ui;
}

void CustomVideoCapture::initConnections()
{
    connect(ui->btn_join, &QPushButton::clicked, this, &CustomVideoCapture::onBtnJoinClicked);
    connect(ui->btn_start, &QPushButton::clicked, this, &CustomVideoCapture::onBtnStartClicked);
    connect(ui->btn_stop, &QPushButton::clicked, this, &CustomVideoCapture::onBtnStopClicked);
}

void CustomVideoCapture::initRTCVideo()
{
    m_handler.reset(new ByteRTCEventHandler());
    //connect(m_handler.get(), &ByteRTCEventHandler::sigFirstLocalVideoFrameCaptured, this, &CustomVideoCapture::onSigFirstLocalVideoFrameCaptured);
    if (g_appid == "") {
        qWarning() << Q_FUNC_INFO << "appid is nullptr";
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("appid is null"), QMessageBox::Ok);
        box.exec();
        return;
    }
    bytertc::EngineConfig conf;
    conf.app_id = g_appid.c_str();
    conf.parameters = Utils::getParameters();
    m_video = bytertc::IRTCEngine::createRTCEngine(conf, m_handler.get());
    m_video->startAudioCapture();

    QStringList list = {"createRTCEngine", "startAudioCapture"};
    appendAPI(list);

}

void CustomVideoCapture::cleanRTCVideo()
{
    if (m_video) {
        if (m_room) {
            m_room->leaveRoom();
            m_room->setRTCRoomEventHandler(nullptr);
            m_room->destroy();
            m_room = nullptr;
        }


        m_video->stopAudioCapture();
        bytertc::IRTCEngine::destroyRTCEngine();
        m_video = nullptr;
    }
    QStringList list = { "leaveRoom", "setRTCRoomEventHandler", "destroy", "stopAudioCapture", "stopVideoCapture", "destroyRTCEngine"};
    appendAPI(list);

}

void CustomVideoCapture::initUI()
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
    ui->btn_start->setStyleSheet(APIDemo::str_qss_btn2_3);
    ui->btn_stop->setStyleSheet(APIDemo::str_qss_btn2_3);
    ui->comboBox->setStyleSheet(APIDemo::str_qss_combobox);


}

std::unique_ptr<ByteRTCRoomHandler> CustomVideoCapture::createRoomHandler(std::string roomid, std::string uid)
{
    std::unique_ptr<ByteRTCRoomHandler> roomH = std::make_unique<ByteRTCRoomHandler>(roomid, uid);
    connect(roomH.get(), &ByteRTCRoomHandler::sigRoomStateChanged, this, &CustomVideoCapture::onSigRoomStateChanged);
    connect(roomH.get(), &ByteRTCRoomHandler::sigUserPublishStreamVideo, this, &CustomVideoCapture::onSigUserPublishStreamVideo);
    connect(roomH.get(), &ByteRTCRoomHandler::sigUserPublishStreamAudio, this, &CustomVideoCapture::onSigUserPublishStreamAudio);

    return roomH;

}

std::string CustomVideoCapture::getLocalPath()
{
    std::string result;
    if (ui->comboBox->currentText().contains("yuv420")) {
        result = QString(QApplication::applicationDirPath() + qstr_file_yuv).toStdString();
        m_pixel_fmt = bytertc::kVideoPixelFormatI420;
        m_push_width = 256;
        m_push_height = 144;
        m_1frame_size = m_push_width * m_push_height * 3 / 2;
    }
    else if (ui->comboBox->currentText().contains("nv12")) {
        result = QString(QApplication::applicationDirPath() + qstr_file_nv12).toStdString();
        m_pixel_fmt = bytertc::kVideoPixelFormatNV12;
        m_push_width = 256;
        m_push_height = 144;
        m_1frame_size = m_push_width * m_push_height * 3 / 2;
    }
    else if (ui->comboBox->currentText().contains("rgba")){
        result = QString(QApplication::applicationDirPath() + qstr_file_rgba).toStdString();
        m_pixel_fmt = bytertc::kVideoPixelFormatRGBA;
        m_push_width = 320;
        m_push_height = 180;
        m_1frame_size = m_push_width * m_push_height * 4;

    } else {
        qWarning() << Q_FUNC_INFO << "not support";
    }
    return result;
}

void CustomVideoCapture::onBtnJoinClicked()
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

        bytertc::VideoCanvas cavs;
        cavs.view = (void*)ui->widget->getWinId();
        cavs.render_mode = bytertc::kRenderModeFit;
        cavs.background_color = 0x00000000;
        m_video->setLocalVideoCanvas(cavs);
        ui->widget->setUserInfo(str_room, str_uid);

        m_video->startAudioCapture();

        m_room_handler = createRoomHandler(str_room, str_uid);
        m_room->setRTCRoomEventHandler(m_room_handler.get());

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

        onBtnStopClicked();
    }
    appendAPI(list);

}

void CustomVideoCapture::onBtnInitClicked()
{
    initRTCVideo();
}

void CustomVideoCapture::onBtnUninitClicked()
{
    cleanRTCVideo();
}

void CustomVideoCapture::onBtnStartClicked()
{
    if (m_video == nullptr) {
        return;
    }

    if (m_file) {
        fclose(m_file);
        m_file = nullptr;
    }

    m_video->setVideoSourceType(bytertc::kVideoSourceTypeExternal);
    std::string file_path = getLocalPath();
    m_file = fopen(file_path.c_str(), "rb");
    if (m_file == nullptr) {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("警告"), QStringLiteral("打开文件失败"), QMessageBox::Ok);
        box.exec();
        return;
    }
    fpos_t file_size;
    fseek(m_file, 0, SEEK_END);
    fgetpos(m_file, &file_size);
    fseek(m_file, 0, SEEK_SET);

    m_frame_index = 0;
    m_frame_count = file_size / m_1frame_size;
    m_push_fps = m_push_fps == 0 ? 15 : m_push_fps;

    if (m_timer == nullptr) {
        m_timer = new QTimer(this);
        connect(m_timer, &QTimer::timeout, this, &CustomVideoCapture::onTimeout);
    }
    m_timer->start(1000/ m_push_fps);
    ui->comboBox->setEnabled(false);
}

void CustomVideoCapture::onBtnStopClicked()
{
    if (m_timer) {
        m_timer->stop();
    }
    ui->comboBox->setEnabled(true);
}

void CustomVideoCapture::onTimeout()
{
    if (m_file == nullptr) return;
    
    unsigned char* buffer = (unsigned char*)malloc(m_1frame_size);
    m_frame_index = m_frame_index % m_frame_count;
    auto fileOffset = (uint64_t)m_1frame_size * m_frame_index;
    m_frame_index++;
#if defined(WIN32)
    auto ret = _fseeki64(m_file, fileOffset, SEEK_SET);
#else
    auto ret = fseek(m_file, fileOffset, SEEK_SET);
#endif
    if (ret == -1) {
        free(buffer);
        return;
    }

    ret = fread(buffer, sizeof(char), m_1frame_size, m_file);
    if (ret == -1) {
        fseek(m_file, 0, SEEK_SET);
        fread(buffer, sizeof(char), m_1frame_size, m_file);
        if (ret == -1) {
            free(buffer);
            return;
        }
    }

    bytertc::VideoFrameData frameData;

    frameData.pixel_format = static_cast<bytertc::VideoPixelFormat>(m_pixel_fmt);
    frameData.rotation = bytertc::kVideoRotation0;
    frameData.timestamp_us = QDateTime::currentMSecsSinceEpoch();
    frameData.content_type = bytertc::kVideoContentTypeNormalFrame;
    frameData.width = m_push_width;
    frameData.height = m_push_height;

    if (m_pixel_fmt == bytertc::kVideoPixelFormatI420) {

        frameData.plane_data[0] = buffer;
        frameData.plane_data[1] = buffer + m_push_width * m_push_height;
        frameData.plane_data[2] = buffer + m_push_width * m_push_height * 5 / 4;

        frameData.plane_stride[0] = m_push_width;
        frameData.plane_stride[1] = m_push_width >> 1;
        frameData.plane_stride[2] = m_push_width >> 1;
    }
    else if (m_pixel_fmt == bytertc::kVideoPixelFormatNV12) {
        frameData.plane_data[0] = buffer;
        frameData.plane_data[1] = buffer + m_push_width * m_push_height;

        frameData.plane_stride[0] = m_push_width;
        frameData.plane_stride[1] = m_push_width;

    }
    else if (m_pixel_fmt == bytertc::kVideoPixelFormatRGBA) {
        frameData.plane_data[0] = buffer;
        frameData.plane_stride[0] = m_push_width*4;
    }
    

    m_video->pushExternalVideoFrame(frameData);
}

void CustomVideoCapture::onTimeoutRGBA()
{
    if (m_file == nullptr) return;
    int32_t len = m_push_width * m_push_height * 4;
    unsigned char* buffer = (unsigned char*)malloc(len);
    m_frame_index = m_frame_index % m_frame_count;
    auto fileOffset = (uint64_t)len * m_frame_index;
    m_frame_index++;
#if defined(WIN32)
    auto ret = _fseeki64(m_file, fileOffset, SEEK_SET);
#else
    auto ret = fseek(m_file, fileOffset, SEEK_SET);
#endif
    if (ret == -1) {
        free(buffer);
        return;
    }

    ret = fread(buffer, sizeof(char), len, m_file);
    if (ret == -1) {
        fseek(m_file, 0, SEEK_SET);
        fread(buffer, sizeof(char), len, m_file);
        if (ret == -1) {
            free(buffer);
            return;
        }
    }
    bytertc::VideoFrameData frameData;
    frameData.plane_data[0] = buffer;
    frameData.pixel_format = static_cast<bytertc::VideoPixelFormat>(m_pixel_fmt);
    frameData.rotation = bytertc::kVideoRotation0;
    frameData.timestamp_us = QDateTime::currentMSecsSinceEpoch();
    frameData.content_type = bytertc::kVideoContentTypeNormalFrame;
    frameData.width = m_push_width;
    frameData.height = m_push_height;
    frameData.plane_stride[0] = m_push_width;

    m_video->pushExternalVideoFrame(frameData);
}

void CustomVideoCapture::onSigRoomStateChanged(std::string roomid, std::string uid, int state, std::string extra_info)
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

void CustomVideoCapture::onSigUserPublishStreamVideo(std::string stream_id, std::string roomid, std::string uid, bool pub)
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
            bytertc::RemoteStreamKey key;
            bytertc::VideoCanvas cas;
            key.room_id = roomid.c_str();
            key.user_id = uid.c_str();
            key.stream_index = bytertc::StreamIndex::kStreamIndexMain;
            cas.render_mode = bytertc::kRenderModeFit;
            cas.view = (void*)ui->widget_2->getWinId();
            m_video->setRemoteVideoCanvas(stream_id.c_str(), cas);
            m_rendering = uid;
            ui->widget_2->setUserInfo(roomid, uid);
            appendAPI("setRemoteVideoCanvas");
        }
    }
}

void CustomVideoCapture::onSigUserPublishStreamAudio(std::string stream_id, std::string roomid, std::string uid, bool pub)
{
    QString log_str = QString("onUserPublishStreamAudio")
        + ",stream_id:" + QString::fromStdString(stream_id)
        + ",roomid:" + QString::fromStdString(roomid)
        + ",uid:" + QString::fromStdString(uid)
        + ",pub:" + QString::number(pub);

    appendCallback(log_str);
}
