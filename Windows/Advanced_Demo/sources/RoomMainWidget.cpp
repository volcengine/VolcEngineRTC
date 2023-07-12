#include <QMouseEvent>
#include "RoomMainWidget.h"
#include "LoginWidget.h"
#include "OperateWidget.h"
#include "Constants.h"
#include <QDebug>
#include <vector>
#include <QTimer>
#include "VideoWidget.h"
#include <QMessageBox>
#include "BeautySettingWidget.h"
#include "share_screen_widget.h"
#include "setting.h"
#include "utils.h"

/**
 * VolcEngineRTC 视频通话的主页面
 * 本示例不限制房间内最大用户数；同时最多渲染四个用户的视频数据（自己和三个远端用户视频数据）；
 *
 * 包含如下简单功能：
 * - 创建引擎
 * - 设置视频发布参数
 * - 渲染自己的视频数据
 * - 创建房间
 * - 加入音视频通话房间
 * - 打开/关闭麦克风
 * - 打开/关闭摄像头
 * - 渲染远端用户的视频数据
 * - 离开房间
 * - 销毁引擎
 *
 * 实现一个基本的音视频通话的流程如下：
 * 1.创建 IRTCVideo 实例。 bytertc::IRTCVideo* bytertc::createRTCVideo(
 *                          const char* app_id,
 *                          bytertc::IRTCVideoEventHandler *event_handler,
 *                          const char* parameters)
 * 2.视频发布端设置推送多路流时各路流的参数，包括分辨率、帧率、码率、缩放模式、网络不佳时的回退策略等。
 *   bytertc::IRTCVideo::setVideoEncoderConfig(
 *       const VideoEncoderConfig* channel_solutions,
 *       int solution_num)
 * 3.开启本地视频采集。 bytertc::IRTCVideo::startVideoCapture()
 * 4.设置本地视频渲染时，使用的视图，并设置渲染模式。
 *   bytertc::IRTCVideo::setLocalVideoCanvas(
 *       StreamIndex index,
 *       const VideoCanvas& canvas)
 * 5.创建房间。IRTCRoom* bytertc::IRTCVideo::createRTCRoom(const char* room_id)
 * 6.加入音视频通话房间。 bytertc::IRTCRoom::joinRoom(
 *                         const char* token,
 *                         const UserInfo& user_info,
 *                         const RTCRoomConfig& config)
 * 7.SDK 接收并解码远端视频流首帧后，设置用户的视频渲染视图。
 *   bytertc::IRTCVideo::setRemoteStreamVideoCanvas(
 *       RemoteStreamKey stream_key,
 *       const VideoCanvas& canvas)
 * 8.在用户离开房间之后移出用户的视频渲染视图。
 * 9.离开音视频通话房间。 bytertc::IRTCRoom::leaveRoom()
 * 10.销毁房间。 bytertc::IRTCRoom::destroy()
 * 11.销毁引擎。 bytertc::destroyRTCVideo()
 *
 * 详细的API文档参见: https://www.volcengine.com/docs/6348/70095
 */

RoomMainWidget::RoomMainWidget(QWidget *parent)
        : QWidget(parent) {
    ui.setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());

    setupView();
    setupSignals();
}

void RoomMainWidget::leaveRoom() {

}

void RoomMainWidget::setupView() {
    m_videoWidgetList.append(ui.remoteWidget1);
    m_videoWidgetList.append(ui.remoteWidget2);
    m_videoWidgetList.append(ui.remoteWidget3);

    m_loginWidget = QSharedPointer<LoginWidget>::create(this);
    m_operateWidget = QSharedPointer<OperateWidget>::create(this);
	m_beautySettingWidget = QSharedPointer<BeautySettingWidget>::create(this);
	toggleShowFloatWidget(false);

    ui.sdkVersionLabel->setText(QStringLiteral(u"VolcEngineRTC v") + QString(bytertc::getSDKVersion()));
}

void RoomMainWidget::on_closeBtn_clicked() {
    qDebug() << "receive close event";
    slotOnHangup();
    m_settingModel = SettingModel();
    close();
}

void RoomMainWidget::mousePressEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton && ui.titleWidget->rect().contains(event->pos())) {
        m_prevGlobalPoint = event->globalPos();
        m_bLeftBtnPressed = true;
    }
}

void RoomMainWidget::mouseMoveEvent(QMouseEvent *event) {
    if (m_bLeftBtnPressed) {
        auto offset = event->globalPos() - m_prevGlobalPoint;
        m_prevGlobalPoint = event->globalPos();
        move(pos() + offset);
    }
}

void RoomMainWidget::mouseReleaseEvent(QMouseEvent *event) {
    m_bLeftBtnPressed = false;
}

void RoomMainWidget::closeEvent(QCloseEvent* event)
{
    qDebug() << Q_FUNC_INFO << "will close";
    on_closeBtn_clicked();
}

void RoomMainWidget::slotOnEnterRoom(const QString &roomID, const QString &userID) {
    m_uid = userID.toStdString();
    m_roomId = roomID.toStdString();
    ui.roomIdLabel->setText(m_roomId.c_str());

    // 创建引擎
    m_rtc_video = bytertc::createRTCVideo(Constants::APP_ID.c_str(), this, nullptr);
    if (m_rtc_video == nullptr) {
        qWarning() << "create engine failed";
        return;
    }

    // 设置视频发布参数
    utils::setVideoProfile(m_rtc_video,m_settingModel.camera.resolution.width,m_settingModel.camera.resolution.height,m_settingModel.camera.fps,m_settingModel.camera.kbps);
    utils::setScreenProfile(m_rtc_video, m_settingModel.screen.resolution.width, m_settingModel.screen.resolution.height, m_settingModel.screen.fps, m_settingModel.screen.kbps);
    setRenderCanvas(true, (void *) ui.localWidget->getVideoWidget()->winId(), m_uid.c_str());
    ui.localWidget->showVideo(m_uid.c_str());
    // 开启本地视频采集
    m_rtc_video->startVideoCapture();
    // 开启本地音频采集
    m_rtc_video->startAudioCapture();

    m_rtc_room = m_rtc_video->createRTCRoom(m_roomId.c_str());
    m_rtc_room->setRTCRoomEventHandler(this);
    bytertc::UserInfo userInfo;
    userInfo.uid = m_uid.c_str();
    userInfo.extra_info = nullptr;
    // 加入房间
	m_beautySettingWidget->startCheckLicense();
    bytertc::RTCRoomConfig rtcRoomConfig;
    rtcRoomConfig.is_auto_publish = true;
    rtcRoomConfig.is_auto_subscribe_audio = true;
    rtcRoomConfig.is_auto_subscribe_video = true;
    auto ret = m_rtc_room->joinRoom(Constants::TOKEN.c_str(), userInfo, rtcRoomConfig);
	toggleShowFloatWidget(true);
}

void RoomMainWidget::toggleShowFloatWidget(bool isEnterRoom) {
    m_loginWidget->setVisible(!isEnterRoom);
    m_operateWidget->setVisible(isEnterRoom);
    ui.roomIdLabel->setVisible(isEnterRoom);
}

bytertc::IVideoEffect* RoomMainWidget::GetIVideoEffectPtr()
{
	if (m_rtc_video) 
	{
		return m_rtc_video->getVideoEffectInterface();
	}
	else 
	{
		return nullptr;
	}
}

void RoomMainWidget::slotOnHangup() {
    clearVideoView();

    if (m_rtc_room) {
        // 离开房间
        m_rtc_room->leaveRoom();
        m_rtc_room->destroy();
        m_rtc_room = nullptr;
    }
    // 销毁引擎
    bytertc::destroyRTCVideo();
    m_rtc_video = nullptr;
	if (m_operateWidget) 
	{
		m_operateWidget->reset();
	}
	if (m_beautySettingWidget)
	{
		m_beautySettingWidget->hide();
	}

    toggleShowFloatWidget(false);
}

void RoomMainWidget::onError(int err) {
    qDebug() << "bytertc::OnError err" << err;
	emit sigError(err);
}

void RoomMainWidget::onUserJoined(const bytertc::UserInfo &user_info, int elapsed) {
    qDebug() << "bytertc::OnUserJoined " << user_info.uid;
}

void RoomMainWidget::onUserLeave(const char *uid, bytertc::UserOfflineReason reason) {
    qDebug() << "user leave id = " << uid;
    emit sigUserLeave(bytertc::StreamIndex::kStreamIndexMain, uid);
    emit sigUserLeave(bytertc::StreamIndex::kStreamIndexScreen, uid);
}

void RoomMainWidget::onFirstLocalVideoFrameCaptured(bytertc::StreamIndex index, bytertc::VideoFrameInfo info) {
    qDebug() << "first local video frame is rendered";
    emit updateLocalVideoStreamType(index);
}

void RoomMainWidget::onFirstRemoteVideoFrameDecoded(
        const bytertc::RemoteStreamKey key, const bytertc::VideoFrameInfo &info) {
    qDebug() << "first remote video frame is decoded uid = " << key.user_id << ", stream_index = " << key.stream_index;
    emit sigUserEnter(key.stream_index, key.user_id);
}

void RoomMainWidget::onUserPublishStream(const char* uid, bytertc::MediaStreamType type)
{
    qDebug() << "OnUserPublishStream uid: " << uid << "stream type: "<< type;
    if(type & bytertc::kMediaStreamTypeVideo)
        emit sigUserEnter(bytertc::StreamIndex::kStreamIndexMain, uid);
}

void RoomMainWidget::onUserPublishScreen(const char* uid, bytertc::MediaStreamType type)
{
    qDebug() << "OnUserPublishScreen uid = " << uid;
    if (type & bytertc::kMediaStreamTypeVideo)
        emit sigUserEnter(bytertc::StreamIndex::kStreamIndexScreen, uid);
}

void RoomMainWidget::onUserUnpublishStream(const char* uid, bytertc::MediaStreamType type, bytertc::StreamRemoveReason reason)
{
    qDebug() << "OnUserUnPublishStream uid = " << uid;
    if (type & bytertc::kMediaStreamTypeVideo)
        emit sigUserLeave(bytertc::StreamIndex::kStreamIndexMain, uid);
}

void RoomMainWidget::onUserUnpublishScreen(const char* uid, bytertc::MediaStreamType type, bytertc::StreamRemoveReason reason)
{
    qDebug() << "OnUserUnPublishScreen uid = " << uid;
    if (type & bytertc::kMediaStreamTypeVideo)
        emit sigUserLeave(bytertc::StreamIndex::kStreamIndexScreen, uid);
}

void RoomMainWidget::onUserStartVideoCapture(const char* room_id, const char* user_id) {
    qDebug() << "onUserStartVideoCapture uid = " << user_id;
    emit sigUserVideoStateChanged(user_id, false);
}

void RoomMainWidget::onUserStopVideoCapture(const char* room_id, const char* user_id) {
    qDebug() << "onUserStopVideoCapture uid = " << user_id;
    emit sigUserVideoStateChanged(user_id, true);
}

void RoomMainWidget::setRenderCanvas(bool isLocal, void *view, const std::string &user_id,bytertc::StreamIndex stream_index) {
    if (m_rtc_video == nullptr) {
        qDebug() << "byte engine is null ptr";
    }

    bytertc::VideoCanvas canvas;
    canvas.view = view;
    canvas.render_mode = bytertc::RenderMode::kRenderModeFit;

    if (isLocal) {
        // 设置本地视频渲染视图
        m_rtc_video->setLocalVideoCanvas(stream_index, canvas);
    } else {
        // 设置远端用户视频渲染视图
        bytertc::RemoteStreamKey remote_stream_key;
        remote_stream_key.room_id = m_roomId.c_str();
        remote_stream_key.user_id = user_id.c_str();
        remote_stream_key.stream_index = stream_index;
        m_rtc_video->setRemoteVideoCanvas(remote_stream_key, canvas);
    }
}

void RoomMainWidget::setupSignals() {
    connect(this, &RoomMainWidget::sigUserEnter, this, [=](int stream_index, const QString &userID) {
        if (m_activeWidgetMap.size() >= 3) {
            qDebug() << "ignore add stream event,for users above 4";
            return;
        }

        if (m_activeWidgetMap.contains(userID)) {
            qDebug() << "user id = " << userID << " is exist";
            if (auto videoView = m_activeWidgetMap[userID]) {
                setRenderCanvas(false, nullptr, userID.toStdString(), static_cast<bytertc::StreamIndex>(videoView->getVideoStreamType()));
                if (stream_index == bytertc::StreamIndex::kStreamIndexMain) {
                    videoView->setVideoStreamType(VideoStreamType::kVideoStream);
                }
                else if (stream_index == bytertc::StreamIndex::kStreamIndexScreen) {
                    videoView->setVideoStreamType(VideoStreamType::kScreenStream);
                }
                setRenderCanvas(false, (void*)videoView->getVideoWidget()->winId(), userID.toStdString(), static_cast<bytertc::StreamIndex>(stream_index));
            }
            return;
        }

        for (int i = 0; i < m_videoWidgetList.size(); i++) {
            if (!m_videoWidgetList[i]->isActive()) {
                m_videoWidgetList[i]->showVideo(userID);
				if (stream_index == bytertc::StreamIndex::kStreamIndexMain) {
                    m_videoWidgetList[i]->setVideoStreamType(VideoStreamType::kVideoStream);
				}
				else if (stream_index == bytertc::StreamIndex::kStreamIndexScreen) {
                    m_videoWidgetList[i]->setVideoStreamType(VideoStreamType::kScreenStream);
				}
                setRenderCanvas(false, (void *)m_videoWidgetList[i]->getVideoWidget()->winId(), userID.toStdString(), static_cast<bytertc::StreamIndex>(stream_index));
                m_activeWidgetMap[userID] = m_videoWidgetList[i];
                break;
            }
        }
    });

    connect(this, &RoomMainWidget::sigUserLeave, this, [=](int stream_index, const QString &userID) {
        if (m_activeWidgetMap.contains(userID)) {
            setRenderCanvas(false, nullptr, userID.toStdString());
            VideoWidget* videoView = m_activeWidgetMap[userID];
            if (videoView) {
                videoView->hideVideo();
            }
            m_activeWidgetMap.remove(userID);
        } else {
            qDebug() << "ignore user leave event";
        }
    });

	connect(this, &RoomMainWidget::sigUserVideoStateChanged, this, [=](const QString& userID, bool isMuted) {
		if (m_activeWidgetMap.contains(userID)) {
            auto videoView = m_activeWidgetMap[userID];
			if (videoView && videoView->getVideoStreamType() == VideoStreamType::kVideoStream) {
                if (isMuted) {
                    videoView->getVideoWidget()->setUpdatesEnabled(true);
                }
                else {
                    QTimer::singleShot(100, this, [=] {
                        videoView->getVideoWidget()->setUpdatesEnabled(isMuted);
                        });
                }
			}
		}
	});

    connect(this, &RoomMainWidget::updateLocalVideoStreamType, this, [=](int stream_index) {
        if (stream_index == bytertc::StreamIndex::kStreamIndexMain) {
            ui.localWidget->setVideoStreamType(VideoStreamType::kVideoStream);
        }
        else if (stream_index == bytertc::StreamIndex::kStreamIndexScreen) {
            ui.localWidget->setVideoStreamType(VideoStreamType::kScreenStream);
        }
    });

    connect(m_operateWidget.get(), &OperateWidget::sigMuteAudio, this, [this](bool bMute) {
        if (m_rtc_room) {
            if (bMute) {
                // 关闭本地音频发送
                m_rtc_room->unpublishStream(bytertc::kMediaStreamTypeAudio);
            } else {
                // 开启本地音频发送
                m_rtc_room->publishStream(bytertc::kMediaStreamTypeAudio);
            }
        }
    });

    connect(m_operateWidget.get(), &OperateWidget::sigMuteVideo, this, [this](bool bMute) {
        if (m_rtc_video) {
            if (bMute) {
                // 关闭视频采集
                m_rtc_video->stopVideoCapture();
            } else {
                // 开启视频采集
                m_rtc_video->startVideoCapture();
            }
        }
        if (ui.localWidget->getVideoStreamType() == VideoStreamType::kVideoStream && !m_localSharing) {
            ui.localWidget->getVideoWidget()->setUpdatesEnabled(bMute);
            QTimer::singleShot(100, this, [=] {
                ui.localWidget->update();
            });
        }
    });

	connect(m_operateWidget.get(), &OperateWidget::sigBeautySettingBtn, this, [this]() {
		if (m_beautySettingWidget && !m_beautySettingWidget->isVisible()) {
			m_beautySettingWidget->show();
		}
	});

    connect(m_operateWidget.get(), &OperateWidget::sigSetting, this, [this]() {
        if (m_beautySettingWidget && !m_beautySettingWidget->isVisible()) {
          auto dlg = new Setting();
          std::vector<RtcDevice> devices;
          utils::getVideoCaptureDevices(m_rtc_video, devices);
          dlg->initView(m_settingModel, devices);
          connect(dlg, &Setting::sigSettingChanged, this, [=](SettingModel model) {
                m_settingModel = model;
                utils::setVideoCaptureDevice(m_rtc_video, devices[model.camera_idx].device_id);
                utils::setScreenProfile(m_rtc_video, model.screen.resolution.width,
                    model.screen.resolution.height, model.screen.fps,model.screen.kbps);
                utils::setVideoProfile(m_rtc_video, model.camera.resolution.width,
                    model.camera.resolution.height, model.camera.fps, model.camera.kbps);
              });
          dlg->exec();

        }
    });

    connect(m_operateWidget.get(), &OperateWidget::sigShareScreen, this, [this](bool share) {
        if (share) {
            auto dlg = new ShareScreenWidget;
            std::vector<SnapshotAttr> attrs;
            utils::getShareList(m_rtc_video, attrs);
            dlg->updateData(m_rtc_video, attrs);
            connect(dlg, &ShareScreenWidget::sigScreenShare, this, [=](SnapshotAttr attr) {
                m_localSharing = true;
                m_rtc_room->unpublishStream(bytertc::MediaStreamType::kMediaStreamTypeVideo);
                utils::StartScreenCapture(m_rtc_video, m_rtc_room, attr.source_id);
                utils::StartScreenAudioCapture(m_rtc_video);
                setRenderCanvas(true, nullptr, m_uid.c_str(), bytertc::StreamIndex::kStreamIndexMain);
                setRenderCanvas(true, (void*)ui.localWidget->getVideoWidget()->winId(), m_uid.c_str(), bytertc::StreamIndex::kStreamIndexScreen);
                });

            connect(dlg, &ShareScreenWidget::sigWndShare, this, [=](SnapshotAttr attr) {
                m_localSharing = true;
                m_rtc_room->unpublishStream(bytertc::MediaStreamType::kMediaStreamTypeVideo);
                utils::StartWindowCapture(m_rtc_video, m_rtc_room, attr.source_id);
                utils::StartScreenAudioCapture(m_rtc_video);
                setRenderCanvas(true, nullptr, m_uid.c_str(), bytertc::StreamIndex::kStreamIndexMain);
                setRenderCanvas(true, (void*)ui.localWidget->getVideoWidget()->winId(), m_uid.c_str(), bytertc::StreamIndex::kStreamIndexScreen);
                });

            connect(dlg, &ShareScreenWidget::sigClose, this, [=]() {
                m_operateWidget->setScreen(true);
                });
            dlg->exec();
        }
        else {
            utils::StopScreenCapture(m_rtc_video, m_rtc_room);
            utils::StopScreenAudioCapture(m_rtc_video);
            m_localSharing = false;
            setRenderCanvas(true, nullptr, m_uid.c_str(), bytertc::StreamIndex::kStreamIndexScreen);
            setRenderCanvas(true, (void*)ui.localWidget->getVideoWidget()->winId(), m_uid.c_str(), bytertc::StreamIndex::kStreamIndexMain);
            m_rtc_room->publishStream(bytertc::MediaStreamType::kMediaStreamTypeVideo);
            ui.localWidget->update();
        }
     });

	connect(this, &RoomMainWidget::sigError, this, [this](int errorCode) {
		QString errorInfo = "error:";
		errorInfo += QString::number(errorCode);
		QMessageBox::warning(this, QStringLiteral(u"提示"),errorInfo ,QStringLiteral(u"确定"));
	});
}

void RoomMainWidget::clearVideoView() {
    ui.localWidget->hideVideo();
    for (auto uid : m_activeWidgetMap.keys()) {
        if(m_activeWidgetMap[uid])
            m_activeWidgetMap[uid]->hideVideo();
    }
    m_activeWidgetMap.clear();
}