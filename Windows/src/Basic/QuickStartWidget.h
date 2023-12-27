#ifndef QUICKSTARTWIDGET_H
#define QUICKSTARTWIDGET_H

#include "BaseWidget.h"
#include "ByteRTCEventHandler.h"
#include <memory>

#include <QWidget>

namespace bytertc {
    class IRTCVideo;
    class IRTCRoom;
};

namespace Ui {
class QuickStartWidget;
}

class QuickStartWidget : public BaseWidget
{
    Q_OBJECT

public:
    explicit QuickStartWidget(QWidget *parent = nullptr);
    ~QuickStartWidget();

private:
    void initConnections();
    void initUI();

private slots:
    void onBtnCreateVideoClicked();
    void onBtnStartCaptureClicked();
    void onBtnJoinRoomClicked();
    void onBtnLeaveRoomClicked();
    void onBtnDestroyVideoClicked();
    void onBtnSetLocalViewClicked();
private:
    std::unique_ptr<ByteRTCRoomHandler> createRoomHandler(std::string roomid, std::string uid);



private slots:
    void onSigRoomStateChanged(std::string roomid, std::string uid, int state, std::string extra_info);
    void onSigUserPublishStream(std::string roomid, std::string uid, bytertc::MediaStreamType);
    void onSigUserUnPublishStream(std::string roomid, std::string uid, bytertc::MediaStreamType, bytertc::StreamRemoveReason);
    void onSigUserJoined(ByteRTCRoomHandler::UserInfo, int);
    void onSigUserLeave(std::string, std::string, bytertc::UserOfflineReason);
    void onSigLeaveRoom(std::string, std::string, bytertc::RtcRoomStats);


private:
    Ui::QuickStartWidget *ui;

    bytertc::IRTCVideo* m_video = nullptr;
    bytertc::IRTCRoom* m_room = nullptr;
    std::unique_ptr<ByteRTCEventHandler> m_handler;
    std::unique_ptr<ByteRTCRoomHandler> m_roomHandler;
    bool  m_remote_rendered = false;
};

#endif // QUICKSTARTWIDGET_H
