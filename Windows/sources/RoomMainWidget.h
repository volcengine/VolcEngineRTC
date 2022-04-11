#pragma once

#include <QtWidgets/QMainWindow>
#include <QSharedPointer>
#include "ui_RoomMainWidget.h"
#include "bytertc_engine_interface.h"

class LoginWidget;

class OperateWidget;

class RoomMainWidget : public QWidget, public bytertc::IRtcEngineEventHandler {
    Q_OBJECT

public:
    RoomMainWidget(QWidget *parent = Q_NULLPTR);

private
    slots:
            void on_closeBtn_clicked();
protected:
    void mousePressEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

protected:
    void OnJoinRoomResult(const char *room_id, const char *uid, int error_code, bytertc::JoinRoomType join_type,
                          int elapsed) override;

    void OnError(int err) override;

	void OnUserJoined(const bytertc::UserInfo &user_info, 
		int elapsed) override;

    void OnUserLeave(const char *uid, bytertc::UserOfflineReason reason) override;

    void OnFirstLocalVideoFrameCaptured(bytertc::StreamIndex index, bytertc::VideoFrameInfo info) override;

    void OnFirstRemoteVideoFrameDecoded(
            const bytertc::RemoteStreamKey key, const bytertc::VideoFrameInfo &info) override;

public
    slots:
            void slotOnEnterRoom(
    const QString &roomID,
    const QString &userID
    );

    void slotOnHangup();

    signals:
            void sigJoinChannelSuccess(std::string
    channel,
    std::string uid,
    int elapsed
    );

    void sigJoinChannelFailed(std::string room_id, std::string uid, int error_code);

    void sigRoomJoinChannelSuccess(std::string channel, std::string uid, int elapsed);

    void sigUserEnter(const QString &uid);

    void sigUserLeave(const QString &uid);

	void sigError(int errorCode);
private:
    void setupView();

    void setupSignals();

    void toggleShowFloatWidget(bool isEnterRoom);

    void leaveRoom();

    void setRenderCanvas(bool isLocal, void *view, const std::string &id);

    void clearVideoView();

private:
    Ui::RoomMainForm ui;
    bool m_bLeftBtnPressed = false;
    QPoint m_prevGlobalPoint;
    QSharedPointer <LoginWidget> m_loginWidget;
    QSharedPointer <OperateWidget> m_operateWidget;
    bytertc::IRtcEngine *m_byteEngine = nullptr;
    std::string m_uid;
    std::string m_roomId;
    QList<VideoWidget *> m_videoWidgetList;
    QMap<QString, VideoWidget *> m_activeWidgetMap;
};
