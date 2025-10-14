#ifndef AUDIOMESSAGE_H
#define AUDIOMESSAGE_H

#include <QWidget>

#include "ByteRTCEventHandler.h"
#include "BaseWidget.h"

namespace Ui {
class AudioMessage;
}

namespace bytertc {
class IRTCEngine;
class IRTCRoom;
};


class AudioMessage : public BaseWidget
{
    Q_OBJECT

public:
    explicit AudioMessage(QWidget *parent = nullptr);
    ~AudioMessage();

private:
    void initUI();
    void initRTCVideo();
    void cleanRTCVideo();

    void initConnects();
    std::unique_ptr<ByteRTCRoomHandler> createRoomHandler(std::string roomid, std::string uid);


private slots:
    void onBtnJoinClicked();
    void onBtnSendClicked();

private slots:
    void onSigRoomStateChanged(std::string roomid, std::string uid, int state, std::string extra_info);
    void onSigUserPublishStreamVideo(std::string stream_id, std::string roomid, std::string uid, bool pub);
    void onSigUserPublishStreamAudio(std::string stream_id, std::string roomid, std::string uid, bool pub);
    void onSigUserJoined(ByteRTCRoomHandler::UserInfo);
    void onSigUserLeave(std::string, std::string, bytertc::UserOfflineReason);
    void onSigStreamSyncInfoReceived(ByteRTCEventHandler::Stru_RemoteStreamKey stream_key, bytertc::SyncInfoStreamType stream_type, std::string str);


private:
    Ui::AudioMessage *ui;
    bytertc::IRTCEngine* m_video = nullptr;
    bytertc::IRTCRoom* m_room = nullptr;
    std::string m_roomid;
    std::string m_uid;
    std::unique_ptr<ByteRTCEventHandler> m_handler;
    std::unique_ptr<ByteRTCRoomHandler> m_roomHandler;
};

#endif // AUDIOMESSAGE_H
