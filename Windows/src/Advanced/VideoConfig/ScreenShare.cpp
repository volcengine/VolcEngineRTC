#include "ScreenShare.h"
#include "ui_ScreenShare.h"

#include "bytertc_engine.h"
#include "bytertc_room.h"


#include <QLabel>
#include <vector>
#include <QLineEdit>
#include <QImage>

#include "Resources.h"
#include "Utils.h"
#include "Config.h"
#include "ShareWidget.h"

#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QTimer>
#include <QDateTime>

/*
 * mac下使用屏幕共享功能 “共享桌面音频” 时，需要安装虚拟声卡，
 * 虚拟声卡参考：https://www.volcengine.com/docs/6348/125703
 * 当共享桌面音频时，通过音频设备下拉框选择 VeRTCVirtualSoundCard，开始共享即可

**/


ScreenShare::ScreenShare(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::ScreenShare)
{
    ui->setupUi(this);
    initConnections();
    initRTCVideo();
    initUI();

}

ScreenShare::~ScreenShare()
{
    qDebug() << Q_FUNC_INFO;
    cleanRTCVideo();
    delete ui;
}

void ScreenShare::initConnections()
{
    connect(ui->btn_join, &QPushButton::clicked, this, &ScreenShare::onBtnJoinClicked);
    connect(ui->btn_stop, &QPushButton::clicked, this, &ScreenShare::onBtnStopClicked);
    connect(ui->btn_choose_widget, &QPushButton::clicked, this, &ScreenShare::onBtnChooseWindowClicked);
    connect(ui->btn_set, &QPushButton::clicked, this, &ScreenShare::onBtnSetClicked);
}

void ScreenShare::initRTCVideo()
{
    m_handler.reset(new ByteRTCEventHandler());
    bytertc::EngineConfig conf;
    conf.app_id = g_appid.c_str();
    conf.parameters = Utils::getParameters();
    m_video = bytertc::IRTCEngine::createRTCEngine(conf, m_handler.get());

    QStringList list = {"createRTCEngine"};
    appendAPI(list);

}

void ScreenShare::cleanRTCVideo()
{
    if (m_video) {
        //m_video->stopScreenVideoCapture();
        m_video->stopScreenAudioCapture();
        bytertc::VideoCanvas cas;
        cas.view = nullptr;
        m_video->setLocalVideoCanvas(cas);
        if (m_room) {
            m_room->leaveRoom();
            m_room->setRTCRoomEventHandler(nullptr);
            m_room->destroy();
            m_room = nullptr;
        }

        bytertc::IRTCEngine::destroyRTCEngine();
        m_video = nullptr;
    }
    QStringList list = { "leaveRoom", "setRTCRoomEventHandler", "destroy", "stopAudioCapture", "stopVideoCapture", "destroyRTCEngine"};
    appendAPI(list);

}

void ScreenShare::initUI()
{
    ui->label_mac->hide();
#ifdef Q_OS_MAC
    ui->label_mac->show();
    ui->label_audio->show();
    ui->comboBox_audio->show();
    ui->comboBox_audio->clear();
    char device_name[512];
    char device_id[512];

    std::string result;
    bytertc::IAudioDeviceManager *manager = m_video->getAudioDeviceManager();
    if (manager) {
        bytertc::IAudioDeviceCollection *collection = manager->enumerateAudioCaptureDevices();
        for (int i=0; i<collection->getCount(); i++) {
            collection->getDevice(i, device_name, device_id);
            std::string str_device_name(device_name);
            ui->comboBox_audio->addItem(QString::fromStdString(str_device_name));
        }
    }

#else
    ui->label_audio->hide();
    ui->comboBox_audio->hide();
#endif
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
            qDebug() << Q_FUNC_INFO << edit->objectName();
            edit->setStyleSheet(APIDemo::str_qss_text);
            edit->setFixedHeight(26);
        }
    };
    ui->btn_join->setStyleSheet(APIDemo::str_qss_btn1);
    ui->btn_choose_widget->setStyleSheet(APIDemo::str_qss_btn2_3);
    ui->btn_stop->setStyleSheet(APIDemo::str_qss_btn2_3);
    ui->btn_choose_widget->setFixedHeight(36);
    ui->btn_stop->setFixedHeight(36);
    ui->btn_set->setStyleSheet(APIDemo::str_qss_btn2_3);
    ui->btn_set->setFixedHeight(36);

    auto set_resoultion_data = [](QComboBox* cmb) {
        std::vector<QSize> resolutions{
                                                 {160, 160}, {320, 180}, {320, 240},  {640, 360},  {480, 480},
                                                 {640, 480}, {960, 540}, {1280, 720}, {1920, 1080}};
        for (auto item : resolutions) {
            QVariant var;
            var.setValue(item);
            cmb->addItem(QString("%1*%2").arg(item.width()).arg(item.height()), var);
        }
    };

    auto set_fps_data = [](QComboBox* cmb) {
        std::vector<int> vec_fps{15, 20, 24};
        for (auto item : vec_fps) {
            QVariant var;
            var.setValue(item);
            cmb->addItem(QString("%1 fps").arg(item).arg(item), var);
        }
    };

    set_resoultion_data(ui->comboBox_resolution);
    set_fps_data(ui->comboBox_fps);

}

std::unique_ptr<ByteRTCRoomHandler> ScreenShare::createRoomHandler(std::string roomid, std::string uid)
{
    std::unique_ptr<ByteRTCRoomHandler> roomH = std::make_unique<ByteRTCRoomHandler>(roomid, uid);
    connect(roomH.get(), &ByteRTCRoomHandler::sigRoomStateChanged, this, &ScreenShare::onSigRoomStateChanged);
    connect(roomH.get(), &ByteRTCRoomHandler::sigUserPublishStreamVideo, this, &ScreenShare::onSigUserPublishStreamVideo);
    connect(roomH.get(), &ByteRTCRoomHandler::sigUserPublishStreamAudio, this, &ScreenShare::onSigUserPublishStreamAudio);
    //connect(roomH.get(), &ByteRTCRoomHandler::sigUserPublishScreenVideo, this, &ScreenShare::onSigUserPublishScrreenVideo);
    //connect(roomH.get(), &ByteRTCRoomHandler::sigUserPublishScreenAudio, this, &ScreenShare::onSigUserPublishScreenAudio);

    return roomH;

}

std::vector<SnapshotAttr> ScreenShare::getShareWidgets()
{
    SnapshotAttr snapshot;
    std::vector<SnapshotAttr> list;
    if (m_video == nullptr) return list;

    static std::string desktop_names[] = {
        "桌面一", "桌面二", "桌面三", "桌面四", "桌面五",
        "桌面六", "桌面七", "桌面八", "桌面九", "桌面十",
    };

    bytertc::IScreenCaptureSourceList* sourcelist = m_video->getScreenCaptureSourceList();
    if (sourcelist == nullptr) return list;

    int count = sourcelist->getCount();
    for (int i = 0; i < count; ++i) {
        auto source = sourcelist->getSourceInfo(i);
        snapshot.name = source.source_name == nullptr ? "" : source.source_name;
        snapshot.source_id = source.source_id;
        snapshot.application = source.application == nullptr ? "" : source.application;
        snapshot.pid = source.pid;
        snapshot.primary_monitor = source.primary_monitor;
        snapshot.type = source.type;
        bytertc::IVideoFrame* frame = nullptr;
        frame = m_video->getThumbnail(static_cast<bytertc::ScreenCaptureSourceType>(snapshot.type), snapshot.source_id, 160, 90);
        
       if (frame == nullptr) {
            QString log = QString("getThumbnail is null, count:") + QString::number(count) + 
                          QString(", i:") + QString::number(i) + 
                          QString(", name:") + QString::fromStdString(snapshot.name) + 
                          QString(", application:") + QString::fromStdString(snapshot.application) + 
                          QString(", type:") + QString::number(snapshot.type);
            appendAPI(log);
            continue;
       }

        snapshot.img = QImage(reinterpret_cast<uchar*>(frame->planeData(0)), frame->width(),
                              frame->height(), QImage::Format::Format_RGB32).scaled(QSize(160, 90));

        list.push_back(snapshot);
        qDebug() << Q_FUNC_INFO << "i=" << i << ",name=" << source.source_name
                 << ",id=" << source.source_id
                 << ",application=" << source.application
                 << ",pid=" << source.pid
                 << ",primary_screen=" << source.primary_monitor
                 << ",type=" << source.type
                 << ",img size=" << snapshot.img.size()
                 << "\n\n";
    }

    sourcelist->release();

    return list;
}

void ScreenShare::startAudioCapture()
{
    if (m_video == nullptr) return;
#ifdef Q_OS_MAC

    char device_name[512];
    char device_id[512];

    std::string result;
    bytertc::IAudioDeviceManager *manager = m_video->getAudioDeviceManager();
    std::string str_ui = ui->comboBox_audio->currentText().toStdString();
    if (manager) {
        bytertc::IAudioDeviceCollection *collection = manager->enumerateAudioCaptureDevices();
        for (int i=0; i<collection->getCount(); i++) {
            collection->getDevice(i, device_name, device_id);

            qDebug() << Q_FUNC_INFO << "name:" << device_name << ",id:" << device_id << ",uiname=" <<QString::fromStdString(str_ui);
            std::string test(device_name);
            if (test == str_ui)  {
                result = device_id;
                break;
            }
        }
    }

    int ret = m_video->startScreenAudioCapture(result.c_str());
    qDebug() << Q_FUNC_INFO << QDateTime::currentMSecsSinceEpoch() << " result=" << QString::fromStdString(result) << ",ret=" << ret;

#else
    m_video->startScreenAudioCapture();
#endif
}

void ScreenShare::onBtnJoinClicked()
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
        cavs.view = (void*)ui->widget_local->getWinId();
        cavs.render_mode = bytertc::kRenderModeFit;
        cavs.background_color = 0x00000000;
        m_video->setLocalVideoCanvas(cavs);
        ui->widget_local->setUserInfo(str_room, str_uid);

        m_room_handler = createRoomHandler(str_room, str_uid);
        m_room->setRTCRoomEventHandler(m_room_handler.get());

        bytertc::UserInfo info;
        bytertc::RTCRoomConfig config;

        info.uid = str_uid.c_str();
        config.is_auto_publish_audio = true;
        config.is_auto_publish_video = true;
        config.is_auto_subscribe_audio = true;
        config.is_auto_subscribe_video = true;
        //config.remote_video_config.resolution_height = ui->widget_2->height();
        //config.remote_video_config.resolution_width = ui->widget_2->height();
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

void ScreenShare::onBtnStopClicked()
{
    if (m_video == nullptr) return;
    m_video->stopScreenVideoCapture();
    m_video->stopScreenAudioCapture();
    QStringList list{"stopScreenVideoCapture", "stopScreenAudioCapture"};
    appendAPI(list);
}

void ScreenShare::onBtnChooseWindowClicked()
{
    if (m_room == nullptr) {
        qWarning() << Q_FUNC_INFO << "room is null";
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("Please JoinRoom"), QMessageBox::Ok);
        box.exec();

    }
    auto dlg = new ShareWidget;
    std::vector<SnapshotAttr> attrs = getShareWidgets();
    dlg->updateData(m_video, attrs);

    connect(dlg, &ShareWidget::sigScreenShare, this, [=](SnapshotAttr attr) {
        m_localSharing = true;

        bytertc::ScreenCaptureSourceInfo info;
        bytertc::ScreenCaptureParameters param;
        info.type = static_cast<bytertc::ScreenCaptureSourceType>(attr.type);
        info.source_id = attr.source_id;
        info.source_name = attr.name.c_str();
        info.application = attr.application.c_str();
        info.pid = attr.pid;
        param.capture_mouse_cursor = bytertc::MouseCursorCaptureState::kMouseCursorCaptureStateOn;
        int ret = m_video->startScreenVideoCapture(info, param);
        startAudioCapture();
        //m_room->publishScreenAudio(true);
        //m_room->publishScreenVideo(true);
        qDebug() << Q_FUNC_INFO << "startScreenVideoCapture ret=" << ret;

    });

    dlg->exec();
}

void ScreenShare::onBtnSetClicked()
{
    if (m_video == nullptr) return;

    bytertc::VideoEncoderConfig conf;
    conf.width = ui->comboBox_resolution->currentData().value<QSize>().width();
    conf.height = ui->comboBox_resolution->currentData().value<QSize>().height();
    conf.frame_rate = ui->comboBox_fps->currentData().toInt();
    conf.max_bitrate = ui->lineEdit_max->text().toInt();
    conf.min_bitrate = ui->lineEdit_min->text().toInt();
    m_video->setVideoEncoderConfig(conf);
}

void ScreenShare::onSigRoomStateChanged(std::string roomid, std::string uid, int state, std::string extra_info)
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
        ui->widget_local->setUserInfo(roomid, uid);
    }
    else {
        QMessageBox box(QMessageBox::Warning, QStringLiteral("提示"), QString("onRoomStateChanged:") + QString::number(state), QMessageBox::Ok);
        box.exec();
    }
}

void ScreenShare::onSigUserPublishStreamVideo(std::string stream_id, std::string roomid, std::string uid, bool pub)
{
    QString log_str = QString("onUserPublishStreamVideo")
        + ",stream_id:" + QString::fromStdString(stream_id)
        + ",roomid:" + QString::fromStdString(roomid)
        + ",uid:" + QString::fromStdString(uid)
        + ",pub:" + QString::number(pub);

    if (pub) {
        bytertc::VideoCanvas cas;
        cas.background_color = 0;
        cas.render_mode = bytertc::kRenderModeHidden;
        cas.view = nullptr;
        m_video->setRemoteVideoCanvas(stream_id.c_str(), cas);
        cas.view = (void*)ui->widget_remote->getWinId();
        m_video->setRemoteVideoCanvas(stream_id.c_str(), cas);
        ui->widget_remote->setUserInfo(roomid, uid);
    } else {
        if (ui->widget_remote->getRoomid() == roomid && ui->widget_remote->getUid() == uid) {
            bytertc::VideoCanvas cas;
            cas.background_color = 0;
            cas.render_mode = bytertc::kRenderModeHidden;
            cas.view = nullptr;
            m_video->setRemoteVideoCanvas(stream_id.c_str(), cas);
            ui->widget_remote->setUserInfo("", "");
            ui->widget_remote->update();
        }
    }

    appendCallback(log_str);
}

void ScreenShare::onSigUserPublishStreamAudio(std::string stream_id, std::string roomid, std::string uid, bool pub)
{
    QString log_str = QString("onUserPublishStreamAudio")
        + ",stream_id:" + QString::fromStdString(stream_id)
        + ",roomid:" + QString::fromStdString(roomid)
        + ",uid:" + QString::fromStdString(uid)
        + ",pub:" + QString::number(pub);
    appendCallback(log_str);
}

//void ScreenShare::onSigUserPublishScrreenVideo(std::string roomid, std::string uid, bool pub)
//{
//    QString str = QString("onUserPublishScreenVideo, roomid:") + QString::fromStdString(roomid)
//                  + ",uid:" + QString::fromStdString(uid) + ",pub:" + QString::number(pub);
//    appendCallback(str);
//    if (m_video == nullptr) return;
//    if (pub) {
//        m_remote_uids.insert(uid);
//        bytertc::RemoteStreamKey key;
//        bytertc::VideoCanvas cas;
//        key.room_id = roomid.c_str();
//        key.user_id = uid.c_str();
//        key.stream_index = bytertc::StreamIndex::kStreamIndexScreen;
//        cas.render_mode = bytertc::kRenderModeFit;
//        cas.view = (void*)ui->widget_2->getWinId();
//        m_video->setRemoteVideoCanvas(key, cas);
//        m_rendering = uid;
//        ui->widget_2->setUserInfo(roomid, uid);
//        appendAPI("setRemoteVideoCanvas");
//    }
//}
//
//void ScreenShare::onSigUserPublishScreenAudio(std::string roomid, std::string uid, bool pub)
//{
//    QString str = QString("onUserPublishScreenAudio, roomid:") + QString::fromStdString(roomid)
//                  + ",uid:" + QString::fromStdString(uid) + ",type:" + QString::number(pub);
//
//    appendCallback(str);
//
//}
