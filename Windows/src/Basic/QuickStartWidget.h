#ifndef QUICKSTARTWIDGET_H
#define QUICKSTARTWIDGET_H

#include "BaseWidget.h"
#include "ByteRTCEventHandler.h"
#include <memory>

#include <QWidget>

namespace bytertc {
    class IRTCEngine;
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
    void onSigUserPublishStreamVideo(std::string stream_id, std::string roomid, std::string uid, bool pub);
    void onSigUserPublishStreamAudio(std::string stream_id, std::string roomid, std::string uid, bool pub);
    void onSigUserJoined(ByteRTCRoomHandler::UserInfo);
    void onSigUserLeave(std::string, std::string, bytertc::UserOfflineReason);
    void onSigLeaveRoom(std::string, std::string, bytertc::RtcRoomStats);


private:
    Ui::QuickStartWidget *ui;

    bytertc::IRTCEngine* m_video = nullptr;
    bytertc::IRTCRoom* m_room = nullptr;
    std::unique_ptr<ByteRTCEventHandler> m_handler;
    std::unique_ptr<ByteRTCRoomHandler> m_roomHandler;
    bool  m_remote_rendered = false;
};

#endif // QUICKSTARTWIDGET_H
