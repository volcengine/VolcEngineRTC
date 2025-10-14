#ifndef SEIMESSAGE_H
#define SEIMESSAGE_H

#include <QWidget>
#include "BaseWidget.h"
#include "ByteRTCEventHandler.h"

#include <QTimer>

namespace Ui {
class SEIMessage;
}

namespace bytertc {
class IRTCEngine;
class IRTCRoom;
};

class SEIMessage : public BaseWidget
{
    Q_OBJECT

public:
    explicit SEIMessage(QWidget *parent = nullptr);
    ~SEIMessage();

private:
    void initUI();
    void initConnections();

    void initRTCVideo();
    void cleanRTCVideo();
    bytertc::IMixedStreamConfig *getMixedStreamConfig(std::string url, std::string app_data);

    std::unique_ptr<ByteRTCRoomHandler> createRoomHandler(std::string roomid, std::string uid);
    void startPushExternalVideo();

private slots:
    void onBtnJoinClicked();
    void onBtnStarRTMPhClicked();
    void onBtnStopRTMPClicked();
    void onBtnSendSeiClicked();
    void onBtnUpdate2Clicked();

private slots:
    void onSigRoomStateChanged(std::string roomid, std::string uid, int state, std::string extra_info);
    void onSigUserPublishStreamVideo(std::string stream_id, std::string roomid, std::string uid, bool pub);
    void onSigUserPublishStreamAudio(std::string stream_id, std::string roomid, std::string uid, bool pub);
    void onSEIMessageReceived(ByteRTCEventHandler::Stru_RemoteStreamKey stream_key, std::string str);
    void onSigMixingEvent(ByteRTCEventHandler::MixedStreamTaskInfo info, bytertc::MixedStreamTaskEvent event, bytertc::MixedStreamTaskErrorCode error_code);
    void onSigUserJoined(ByteRTCRoomHandler::UserInfo info);
    void onSigUserLeave(std::string, std::string, bytertc::UserOfflineReason);

    void onTimeoutExternalVideoSEI();

private:
    Ui::SEIMessage *ui;
    std::string m_uid, m_roomid;
    bytertc::IRTCEngine* m_video = nullptr;
    bytertc::IRTCRoom* m_room = nullptr;
    std::unique_ptr<ByteRTCEventHandler> m_handler;
    std::unique_ptr<ByteRTCRoomHandler>  m_room_handler;
    QTimer m_timer_send;
    FILE* m_file = nullptr;
    int m_frame_count = 0;
    int m_frame_index = 0;
    int m_push_width = 256;
    int m_push_height = 144;
    int m_1frame_size = 0;

};

#endif // SEIMESSAGE_H
