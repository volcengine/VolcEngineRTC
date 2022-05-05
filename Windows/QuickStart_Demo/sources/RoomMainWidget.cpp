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
 * 本示例不限制房间内最大用户数；同时最多渲染四个用户的视频数据（自己和三个远端用户视频数据）；
 *
 * 包含如下简单功能：
 * - 创建引擎
 * - 设置视频发布参数
 * - 渲染自己的视频数据
 * - 加入音视频通话房间
 * - 打开/关闭麦克风
 * - 打开/关闭摄像头
 * - 渲染远端用户的视频数据
 * - 离开房间
 * - 销毁引擎
 *
 * 实现一个基本的音视频通话的流程如下：
 * 1.创建引擎 bytertc::CreateRtcEngine(const char* app_id,bytertc::IRtcEngineEventHandler* event_handler,
 *   const char* parameters)
 * 2.设置编码参数 IRtcEngine->SetVideoEncoderConfig(const VideoSolution* solutions, int solution_num)
 * 3.开启本地视频采集 IRtcEngine->EnableLocalVideo(bool enable)，IRtcEngine->StartPreview()
 * 4.设置本地视频渲染视图 IRtcEngine->SetLocalVideoCanvas(StreamIndex index, const VideoCanvas& canvas)
 * 4.加入音视频通话房间 IRtcEngine->JoinRoom(const char* token, const UserInfo& user_info, RoomProfileType profile_type)
 * 5.在收到远端用户视频首帧之后，设置用户的视频渲染视图 IRtcEngine->
 *   SetRemoteVideoCanvas(const char* user_id, StreamIndex index, const VideoCanvas& canvas)
 * 6.在用户离开房间之后移出用户的视频渲染视图
 * 7.离开音视频通话房间 IRtcEngine->LeaveRoom()
 * 8.销毁引擎 bytertc::DestroyRtcEngine(bytertc::IRtcEngine* engine)
 *
 * 有以下常见的注意事项：
 * 1.本示例中，我们在 IRtcEngineEventHandler->OnFirstRemoteVideoFrameDecoded(const RemoteStreamKey key,
 *   const VideoFrameInfo& info) 这个事件中给远端用户设置远端用户视频渲染视图，这个回调表示的是收到了远端用户的视频第一帧。当然也可以在
 *   IRtcEngineEventHandler->OnUserJoined(const UserInfo& user_info, const char* team_id,
 *   const RangeAudioMode send_mode, int elapsed) 回调中设置远端用户视频渲染视图
 * 2.SDK 回调不在主线程，UI 操作需要切换线程
 * 3.用户成功加入房间后，SDK 会通过 IRtcEngineEventHandler->OnUserJoined(const UserInfo& user_info, const char* team_id,
 *   const RangeAudioMode send_mode, int elapsed) 回调已经在房间的用户信息
 * 4.SDK 支持同时发布多个参数的视频流，接口是 IRtcEngine->SetVideoEncoderConfig(const VideoSolution* solutions, int solution_num)
 * 5.加入房间时，需要有有效的 token，加入失败时会通过 IRtcEngine->OnRoomError(int err) 输出对应的错误码
 * 6.用户可以通过 JoinRoom(const char* token, const UserInfo& userInfo, RoomProfileType profile_type) 中的 profile_type
 *   来获得不同场景下的性能优化。本示例是音视频通话场景，因此使用 bytertc::kRoomProfileTypeCommunication
 * 7.不需要在每次加入/退出房间时销毁引擎。本示例退出房间时销毁引擎是为了展示完整的使用流程
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
    ui.sdkVersionLabel->setText(QStringLiteral(u"VolcEngineRTC v") + QString(bytertc::GetSDKVersion()));
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
    m_byteEngine = bytertc::CreateRtcEngine(Constants::APP_ID.c_str(), this, nullptr);
    if (m_byteEngine == nullptr) {
        qWarning() << "create engine failed";
        return;
    }

    std::vector <bytertc::VideoSolution> solutions;
    bytertc::VideoSolution s;
    s.fps = 15;
    s.width = 360;
    s.height = 640;
    s.max_send_kbps = 800;
    solutions.push_back(s);
    // 设置视频发布参数
    m_byteEngine->SetVideoEncoderConfig(solutions.data(), solutions.size());

    setRenderCanvas(true, (void *) ui.localWidget->getVideoWidget()->winId(), m_uid.c_str());
    ui.localWidget->showVideo(m_uid.c_str());
    // 开启本地视频采集
    m_byteEngine->StartVideoCapture();
    // 开启本地音频采集
    m_byteEngine->StartAudioCapture();

    bytertc::UserInfo userInfo;
    userInfo.uid = m_uid.c_str();
    userInfo.extra_info = nullptr;

    bytertc::RTCRoomConfig roomConfig;
    roomConfig.is_auto_publish = true;
    roomConfig.is_auto_subscribe_audio = true;
    roomConfig.is_auto_subscribe_video = true;
    roomConfig.room_profile_type = bytertc::kRoomProfileTypeCommunication;
    // 加入房间
    m_byteEngine->JoinRoom(Constants::TOKEN.c_str(),
                           m_roomId.c_str(), userInfo,
                           roomConfig);
}

void RoomMainWidget::toggleShowFloatWidget(bool isEnterRoom) {
    m_loginWidget->setVisible(!isEnterRoom);
    m_operateWidget->setVisible(isEnterRoom);
    ui.roomIdLabel->setVisible(isEnterRoom);
}

void RoomMainWidget::slotOnHangup() {
    toggleShowFloatWidget(false);
    if (m_byteEngine) {
        // 离开房间
        m_byteEngine->LeaveRoom();
        // 销毁引擎
        bytertc::DestroyRtcEngine(m_byteEngine);
        m_byteEngine = nullptr;
    }
	if (m_operateWidget) 
	{
		m_operateWidget->reset();
	}

    clearVideoView();
}

void RoomMainWidget::OnJoinRoomResult(const char *room_id, const char *uid, int error_code,
                                      bytertc::JoinRoomType join_type, int elapsed) {
    qDebug() << "error_code" << error_code << "bytertc::JoinRoomType join_type" << join_type;
    qDebug() << "receive join room result event";
	if(error_code != 0)
	emit sigError(error_code);
}

void RoomMainWidget::OnError(int err) {
    qDebug() << "bytertc::OnError err" << err;
	emit sigError(err);
}

void RoomMainWidget::OnUserJoined(const bytertc::UserInfo &user_info, int elapsed) {
    qDebug() << "bytertc::OnUserJoined " << user_info.uid;
}

void RoomMainWidget::OnUserLeave(const char *uid, bytertc::UserOfflineReason reason) {
    qDebug() << "user leave id = " << uid;
    emit sigUserLeave(uid);
}

void RoomMainWidget::OnFirstLocalVideoFrameCaptured(bytertc::StreamIndex index, bytertc::VideoFrameInfo info) {
    qDebug() << "first local video frame is rendered";
}

void RoomMainWidget::OnFirstRemoteVideoFrameDecoded(
        const bytertc::RemoteStreamKey key, const bytertc::VideoFrameInfo &info) {
    qDebug() << "first remote video frame is decoded uid = " << key.user_id;
    emit sigUserEnter(key.user_id);
}

void RoomMainWidget::setRenderCanvas(bool isLocal, void *view, const std::string &id) {
    if (m_byteEngine == nullptr) {
        qDebug() << "byte engine is null ptr";
    }

    bytertc::VideoCanvas canvas;
    canvas.view = view;
    canvas.render_mode = bytertc::RenderMode::kRenderModeFit;

    if (isLocal) {
        // 设置本地视频渲染视图
        m_byteEngine->SetLocalVideoCanvas(bytertc::kStreamIndexMain, canvas);
    } else {
        // 设置远端用户视频渲染视图
        m_byteEngine->SetRemoteVideoCanvas(id.c_str(), bytertc::kStreamIndexMain, canvas);
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
        if (m_byteEngine) {
            if (bMute) {
                // 开启本地音频发送
                m_byteEngine->MuteLocalAudio(bytertc::kMuteStateOn);
            } else {
                // 关闭本地音频发送
                m_byteEngine->MuteLocalAudio(bytertc::kMuteStateOff);
            }
        }
    });

    connect(m_operateWidget.get(), &OperateWidget::sigMuteVideo, this, [this](bool bMute) {
        if (m_byteEngine) {
            if (bMute) {
                // 关闭视频采集
                m_byteEngine->StopVideoCapture();
            } else {
                // 开启视频采集
                m_byteEngine->StartVideoCapture();
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