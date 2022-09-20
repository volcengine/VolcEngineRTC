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

/**
 * VolcEngineRTC 视频通话的主页面
 * 本示例不限制房间内最大用户数；同时最多渲染四个用户的视频数据 (自己和三个远端用户视频数据)
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
    toggleShowFloatWidget(false);
    ui.sdkVersionLabel->setText(QStringLiteral(u"VolcEngineRTC v") + QString(bytertc::getSDKVersion()));
}

void RoomMainWidget::on_closeBtn_clicked() {
    qDebug() << "receive close event";
    slotOnHangup();
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

void RoomMainWidget::slotOnEnterRoom(const QString &roomID, const QString &userID) {
    m_uid = userID.toStdString();
    m_roomId = roomID.toStdString();
    ui.roomIdLabel->setText(m_roomId.c_str());
    toggleShowFloatWidget(true);

    // 创建引擎
    m_rtc_video = bytertc::createRTCVideo(Constants::APP_ID.c_str(), this, nullptr);
    if (m_rtc_video == nullptr) {
        qWarning() << "create engine failed";
        return;
    }

    bytertc::VideoSolution video_solution;
    video_solution.fps = 15;
    video_solution.width = 360;
    video_solution.height = 640;
    video_solution.max_send_kbps = 800;
    // 设置视频发布参数
    m_rtc_video->setVideoEncoderConfig(bytertc::StreamIndex::kStreamIndexMain, &video_solution, 1);

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

    bytertc::RTCRoomConfig roomConfig;
    roomConfig.is_auto_publish = true;
    roomConfig.is_auto_subscribe_audio = true;
    roomConfig.is_auto_subscribe_video = true;
    roomConfig.room_profile_type = bytertc::kRoomProfileTypeCommunication;
    // 加入房间
    m_rtc_room->joinRoom(Constants::TOKEN.c_str(), userInfo, roomConfig);
}

void RoomMainWidget::toggleShowFloatWidget(bool isEnterRoom) {
    m_loginWidget->setVisible(!isEnterRoom);
    m_operateWidget->setVisible(isEnterRoom);
    ui.roomIdLabel->setVisible(isEnterRoom);
}

void RoomMainWidget::slotOnHangup() {
    toggleShowFloatWidget(false);
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

    clearVideoView();
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
    emit sigUserLeave(uid);
}

void RoomMainWidget::onFirstLocalVideoFrameCaptured(bytertc::StreamIndex index, bytertc::VideoFrameInfo info) {
    qDebug() << "first local video frame is rendered";
}

void RoomMainWidget::onFirstRemoteVideoFrameDecoded(
        const bytertc::RemoteStreamKey key, const bytertc::VideoFrameInfo &info) {
    qDebug() << "first remote video frame is decoded uid = " << key.user_id;
    emit sigUserEnter(key.user_id);
}

void RoomMainWidget::setRenderCanvas(bool isLocal, void *view, const std::string &user_id) {
    if (m_rtc_video == nullptr) {
        qDebug() << "byte engine is null ptr";
    }

    bytertc::VideoCanvas canvas;
    canvas.view = view;
    canvas.render_mode = bytertc::RenderMode::kRenderModeFit;

    if (isLocal) {
        // 设置本地视频渲染视图
        m_rtc_video->setLocalVideoCanvas(bytertc::kStreamIndexMain, canvas);
    } else {
        // 设置远端用户视频渲染视图
        bytertc::RemoteStreamKey remote_stream_key;
        remote_stream_key.room_id = m_roomId.c_str();
        remote_stream_key.user_id = user_id.c_str();
        remote_stream_key.stream_index = bytertc::kStreamIndexMain;
        m_rtc_video->setRemoteStreamVideoCanvas(remote_stream_key, canvas);
    }
}

void RoomMainWidget::setupSignals() {
    connect(this, &RoomMainWidget::sigUserEnter, this, [=](const QString &userID) {
        if (m_activeWidgetMap.size() >= 3) {
            qDebug() << "ignore add stream event,for users above 4";
            return;
        }

        if (m_activeWidgetMap.contains(userID)) {
            qDebug() << "user id = " << userID << " is exist";
            return;
        }

        for (int i = 0; i < m_videoWidgetList.size(); i++) {
            if (!m_videoWidgetList[i]->isActive()) {
                m_activeWidgetMap[userID] = m_videoWidgetList[i];
                m_videoWidgetList[i]->showVideo(userID);
                setRenderCanvas(false, (void *) m_videoWidgetList[i]->getVideoWidget()->winId(), userID.toStdString());
                break;
            }
        }
    });

    connect(this, &RoomMainWidget::sigUserLeave, this, [=](const QString &userID) {
        if (m_activeWidgetMap.contains(userID)) {
            auto videoView = m_activeWidgetMap[userID];
            videoView->hideVideo();
            m_activeWidgetMap.remove(userID);
        } else {
            qDebug() << "ignore user leave event";
        }
    });

    connect(m_operateWidget.get(), &OperateWidget::sigMuteAudio, this, [this](bool bMute) {
        if (m_rtc_room) {
            if (bMute) {
                // 关闭本地音频发送
                m_rtc_room->unpublishStream(bytertc::kMediaStreamTypeAudio);
            }
            else {
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
            QTimer::singleShot(10, this, [=] {
                ui.localWidget->update();
            });
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
        m_activeWidgetMap[uid]->hideVideo();
    }
    m_activeWidgetMap.clear();
}