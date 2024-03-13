#ifndef SEIMESSAGE_H
#define SEIMESSAGE_H

#include <QWidget>
#include "BaseWidget.h"
#include "ByteRTCEventHandler.h"

namespace Ui {
class SEIMessage;
}

namespace bytertc {
class IRTCVideo;
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


private slots:
    void onBtnJoinClicked();
    void onBtnStarRTMPhClicked();
    void onBtnStopRTMPClicked();
    void onBtnSendSeiClicked();
    void onBtnUpdate2Clicked();

private slots:
    void onSigRoomStateChanged(std::string roomid, std::string uid, int state, std::string extra_info);
    void onSigUserPublishStream(std::string roomid, std::string uid, bytertc::MediaStreamType);
    void onSigUserUnPublishStream(std::string roomid, std::string uid, bytertc::MediaStreamType, bytertc::StreamRemoveReason);
    void onSEIMessageReceived(ByteRTCEventHandler::Stru_RemoteStreamKey stream_key, std::string str);
    void onSigMixingEvent(bytertc::StreamMixingEvent event, std::string task_id, bytertc::StreamMixingErrorCode error, bytertc::MixedStreamType mix_type);
    void onSigUserJoined(ByteRTCRoomHandler::UserInfo info, int);
    void onSigUserLeave(std::string, std::string, bytertc::UserOfflineReason);


private:
    Ui::SEIMessage *ui;
    std::string m_uid, m_roomid;
    bytertc::IRTCVideo* m_video = nullptr;
    bytertc::IRTCRoom* m_room = nullptr;
    std::unique_ptr<ByteRTCEventHandler> m_handler;
    std::unique_ptr<ByteRTCRoomHandler>  m_room_handler;

};

#endif // SEIMESSAGE_H
