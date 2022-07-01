#pragma once

#include <QtWidgets/QMainWindow>
#include <QSharedPointer>
#include "ui_RoomMainWidget.h"
#include "bytertc_engine_interface.h"
#include "bytertc_advance.h"
#include "model.h"

class LoginWidget;
class OperateWidget;
class BeautySettingWidget;

class RoomMainWidget : public QWidget, public bytertc::IRtcEngineEventHandler {
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
    void OnError(int err) override;

	void OnUserJoined(const bytertc::UserInfo &user_info, 
		int elapsed) override;

    void OnUserLeave(const char *uid, bytertc::UserOfflineReason reason) override;

    void OnFirstLocalVideoFrameCaptured(bytertc::StreamIndex index, bytertc::VideoFrameInfo info) override;

    void OnFirstRemoteVideoFrameDecoded(
            const bytertc::RemoteStreamKey key, const bytertc::VideoFrameInfo &info) override;

    void OnUserPublishStream(const char* uid, bytertc::MediaStreamType type)override;

    void OnUserPublishScreen(const char* uid, bytertc::MediaStreamType type) override;

    void OnUserUnPublishStream(const char* uid, bytertc::MediaStreamType type, bytertc::StreamRemoveReason reason)override;

    void OnUserUnPublishScreen(const char* uid, bytertc::MediaStreamType type, bytertc::StreamRemoveReason reason) override;

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
private:
    void setupView();

    void setupSignals();

    void toggleShowFloatWidget(bool isEnterRoom);

    void leaveRoom();

    void setRenderCanvas(bool isLocal, void *view, const std::string &id, bytertc::StreamIndex index = bytertc::kStreamIndexMain);

    void clearVideoView();

private:
    Ui::RoomMainForm ui;
    bool m_bLeftBtnPressed{ false };
    bool m_localSharing{ false };
    QPoint m_prevGlobalPoint;
    QSharedPointer <LoginWidget> m_loginWidget;
    QSharedPointer <OperateWidget> m_operateWidget;
	QSharedPointer <BeautySettingWidget> m_beautySettingWidget;

    bytertc::IRtcEngine *m_byteEngine = nullptr;
    std::string m_uid;
    std::string m_roomId;
    QList<VideoWidget *> m_videoWidgetList;
    QMap<QString, std::pair<VideoWidget*, VideoWidget*>> m_activeWidgetMap;
    SettingModel m_settingModel;
};
