#ifndef AUDIOMESSAGE_H
#define AUDIOMESSAGE_H

#include <QWidget>

#include "ByteRTCEventHandler.h"
#include "BaseWidget.h"

namespace Ui {
class AudioMessage;
}

namespace bytertc {
class IRTCVideo;
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
    void onSigUserPublishStream(std::string roomid, std::string uid, bytertc::MediaStreamType);
    void onSigUserUnPublishStream(std::string roomid, std::string uid, bytertc::MediaStreamType, bytertc::StreamRemoveReason);
    void onSigUserJoined(ByteRTCRoomHandler::UserInfo, int);
    void onSigUserLeave(std::string, std::string, bytertc::UserOfflineReason);
    void onSigStreamSyncInfoReceived(ByteRTCEventHandler::Stru_RemoteStreamKey stream_key, bytertc::SyncInfoStreamType stream_type, std::string str);


private:
    Ui::AudioMessage *ui;
    bytertc::IRTCVideo* m_video = nullptr;
    bytertc::IRTCRoom* m_room = nullptr;
    std::string m_roomid;
    std::string m_uid;
    std::unique_ptr<ByteRTCEventHandler> m_handler;
    std::unique_ptr<ByteRTCRoomHandler> m_roomHandler;
};

#endif // AUDIOMESSAGE_H
