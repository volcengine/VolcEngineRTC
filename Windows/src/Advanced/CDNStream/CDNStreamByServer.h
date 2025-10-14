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
    class IRTCEngine;
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
    void onSigUserPublishStreamVideo(std::string stream_id, std::string roomid, std::string uid, bool pub);
    void onSigUserPublishStreamAudio(std::string stream_id, std::string roomid, std::string uid, bool pub);
    void onSigMixingEvent(ByteRTCEventHandler::MixedStreamTaskInfo info, bytertc::MixedStreamTaskEvent event, bytertc::MixedStreamTaskErrorCode error_code);
    void onSigUserJoined(ByteRTCRoomHandler::UserInfo);
    void onSigUserLeave(std::string, std::string, bytertc::UserOfflineReason);
    void onSigLeaveRoom(std::string, std::string, bytertc::RtcRoomStats);

    // 最终要推流的CDN URL
    std::string get_final_url(const std::string&, const std::string&, const std::string&);

    // 停止CDN推流
    void stop_push_cdn();


private slots:
    void on_btnjoinroom_clicked();
    void on_start_clicked();
    void on_update_clicked();
    void on_stop_clicked();

signals:
    void showState(QString str);

private:
    Ui::CDNStreamByServer *ui;
    bytertc::IRTCEngine* m_video = nullptr;
    bytertc::IRTCRoom* m_room = nullptr;
    std::map<std::string, UserWidget*> m_rendered_users; //已经渲染的用户
    std::map<std::string, UserWidget*> m_unrender_users; //没有渲染的用户
    std::vector<UserWidget*> m_widgets;
    std::string m_roomid;
    std::string m_localid;
    std::recursive_mutex  m_mutex;
    std::string m_task;
    std::unique_ptr<ByteRTCEventHandler> m_handler;
    std::unique_ptr<ByteRTCRoomHandler> m_roomHandler;
};

#endif // CDNSTREAMBYSERVER_H
