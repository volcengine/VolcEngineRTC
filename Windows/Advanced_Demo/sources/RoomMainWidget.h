#pragma once

#include <QtWidgets/QMainWindow>
#include <QSharedPointer>
#include "ui_RoomMainWidget.h"
#include "bytertc_video.h"
#include "bytertc_room.h"
#include "bytertc_video_event_handler.h"
#include "bytertc_room_event_handler.h"
#include "model.h"

class LoginWidget;
class OperateWidget;
class BeautySettingWidget;

class RoomMainWidget : public QWidget, public bytertc::IRTCRoomEventHandler, public bytertc::IRTCVideoEventHandler {
    Q_OBJECT

public:
    RoomMainWidget(QWidget *parent = Q_NULLPTR);

private slots:
    void on_closeBtn_clicked();

protected:
    void mousePressEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

protected:
    void onError(int err) override;

	void onUserJoined(const bytertc::UserInfo &user_info,
		int elapsed) override;

    void onUserLeave(const char *uid, bytertc::UserOfflineReason reason) override;

    void onFirstLocalVideoFrameCaptured(bytertc::StreamIndex index, bytertc::VideoFrameInfo info) override;

    void onFirstRemoteVideoFrameDecoded(
            const bytertc::RemoteStreamKey key, const bytertc::VideoFrameInfo &info) override;
	void onUserPublishStream(const char* uid, bytertc::MediaStreamType type)override;

	void onUserPublishScreen(const char* uid, bytertc::MediaStreamType type) override;

    void onUserUnpublishStream(const char* uid, bytertc::MediaStreamType type, bytertc::StreamRemoveReason reason)override;

    void onUserUnpublishScreen(const char* uid, bytertc::MediaStreamType type, bytertc::StreamRemoveReason reason) override;
	
	void onUserStartVideoCapture(const char* room_id, const char* user_id)  override;

	void onUserStopVideoCapture(const char* room_id, const char* user_id) override;
 
public slots:
    void slotOnEnterRoom(
    const QString &roomID,
    const QString &userID
    );

	bytertc::IVideoEffect* GetIVideoEffectPtr();
    void slotOnHangup();

signals:
    void sigJoinChannelSuccess(std::string
    channel,
    std::string uid,
    int elapsed
    );

    void sigJoinChannelFailed(std::string room_id, std::string uid, int error_code);

    void sigRoomJoinChannelSuccess(std::string channel, std::string uid, int elapsed);

    void sigUserEnter(int stream_index, const QString &uid);

    void sigUserLeave(int stream_index, const QString &uid);

	void sigError(int errorCode);

    void sigUserVideoStateChanged(const QString& uid, bool isMuted); 
     
    void updateLocalVideoStreamType(int stream_index);
private:
    void setupView();

    void setupSignals();

    void toggleShowFloatWidget(bool isEnterRoom);

    void leaveRoom();

    void setRenderCanvas(bool isLocal, void* view, const std::string& user_id,bytertc::StreamIndex index = bytertc::kStreamIndexMain);

    void clearVideoView();

private:
    Ui::RoomMainForm ui;
    bool m_bLeftBtnPressed{ false };
    bool m_localSharing{ false };
    QPoint m_prevGlobalPoint;
    QSharedPointer <LoginWidget> m_loginWidget;
    QSharedPointer <OperateWidget> m_operateWidget;
	QSharedPointer <BeautySettingWidget> m_beautySettingWidget;

    bytertc::IRTCVideo *m_rtc_video = nullptr;
    bytertc::IRTCRoom* m_rtc_room = nullptr;
    std::string m_uid;
    std::string m_roomId;
    QList<VideoWidget *> m_videoWidgetList;
    QMap<QString, VideoWidget*> m_activeWidgetMap;
    SettingModel m_settingModel;
};
