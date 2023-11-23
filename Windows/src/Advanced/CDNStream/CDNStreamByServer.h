#ifndef CDNSTREAMBYSERVER_H
#define CDNSTREAMBYSERVER_H

#include <QWidget>
#include "ByteRTCEventHandler.h"


#include <map>
#include <vector>
#include <mutex>
#include "UserWidget.h"
#include "BaseWidget.h"

namespace Ui {
class CDNStreamByServer;
}

namespace bytertc {
    class IRTCVideo;
    class IRTCRoom;
};

class CDNStreamByServer : public BaseWidget
{
    Q_OBJECT

public:

    explicit CDNStreamByServer(QWidget *parent = nullptr);
    ~CDNStreamByServer();

private:
    void initRTCVideo();
    void cleanRTCVideo();

    void initConnects();
    void resetRTCVideo();
    void initData();
    void updateBtns(bool, bool, bool);
    UserWidget *getWidget();
    bytertc::IMixedStreamConfig *getMixedStreamConfig();
    std::unique_ptr<ByteRTCRoomHandler> createRoomHandler(std::string roomid, std::string uid);

private:
    void onSigRoomStateChanged(std::string roomid, std::string uid, int state, std::string extra_info);
    void onSigUserPublishStream(std::string roomid, std::string uid, bytertc::MediaStreamType);
    void onSigUserUnPublishStream(std::string roomid, std::string uid, bytertc::MediaStreamType, bytertc::StreamRemoveReason);
    void onSigMixingEvent(bytertc::StreamMixingEvent event, std::string task_id, bytertc::StreamMixingErrorCode error, bytertc::MixedStreamType mix_type);
    void onSigUserJoined(ByteRTCRoomHandler::UserInfo, int);
    void onSigUserLeave(std::string, std::string, bytertc::UserOfflineReason);
    void onSigLeaveRoom(std::string, std::string, bytertc::RtcRoomStats);


private slots:
    void on_btnjoinroom_clicked();
    void on_start_clicked();
    void on_update_clicked();
    void on_stop_clicked();
    void on_btncolor_clicked();

signals:
    void showState(QString str);

private:
    Ui::CDNStreamByServer *ui;
    bytertc::IRTCVideo* m_video = nullptr;
    bytertc::IRTCRoom* m_room = nullptr;
    std::map<std::string, UserWidget*> m_rendered_users; //已经渲染的用户
    std::map<std::string, UserWidget*> m_unrender_users; //没有渲染的用户
    std::vector<UserWidget*> m_widgets;
    std::string m_roomid;
    std::string m_localid;
    std::recursive_mutex  m_mutex;
    std::string   m_str_color = "#000000";
    std::string m_task;
    std::unique_ptr<ByteRTCEventHandler> m_handler;
    std::unique_ptr<ByteRTCRoomHandler> m_roomHandler;
};

#endif // CDNSTREAMBYSERVER_H
