#ifndef MULTIROOM_H
#define MULTIROOM_H
#include <map>
#include <QWidget>

#include "BaseWidget.h"

#include "ByteRTCEventHandler.h"

namespace Ui {
class MultiRoom;
}

namespace bytertc {
    class IRTCVideo;
    class IRTCRoom;
};

class UserWidget;
class MultiRoom : public BaseWidget
{
    Q_OBJECT
public:
    struct UserInfos
    {
        std::string uid;
        std::string roomid;
        UserWidget* widget;

    public:
        void reset(){
            uid = "";
            roomid = "";
            widget = nullptr;
        }
    } ;

    explicit MultiRoom(QWidget *parent = nullptr);
    ~MultiRoom();

private slots:
    void onBtn1Clicked();
    void onBtn2Clicked();

private:
    void createRTC();
    void cleanRTC();
    std::unique_ptr<ByteRTCRoomHandler> createRoomHandler(std::string roomid, std::string uid);

    void removeCavas(std::string roomid, std::string uid);

private slots:
    void onSigRoomStateChanged(std::string roomid, std::string uid, int state, std::string extra_info);
    void onSigUserPublishStream(std::string roomid, std::string uid, bytertc::MediaStreamType);
    void onSigUserUnPublishStream(std::string roomid, std::string uid, bytertc::MediaStreamType, bytertc::StreamRemoveReason);
    void onSigUserJoined(ByteRTCRoomHandler::UserInfo, int);
    void onSigUserLeave(std::string, std::string, bytertc::UserOfflineReason);
    void onSigLeaveRoom(std::string, std::string,  bytertc::RtcRoomStats);

private:
    Ui::MultiRoom *ui;
    bytertc::IRTCVideo* m_video = nullptr;
    bytertc::IRTCRoom* m_room1 = nullptr;
    bytertc::IRTCRoom* m_room2 = nullptr;
    std::string m_uid1, m_uid2; //本地用户
    UserInfos m_remote_u1, m_remote_u2; //远端用户

    std::unique_ptr<ByteRTCEventHandler> m_handler;
    std::unique_ptr<ByteRTCRoomHandler>  m_room_handler1, m_room_handler2;

};

#endif // MULTIROOM_H
