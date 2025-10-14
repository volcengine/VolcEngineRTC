#ifndef SCREENSHARE_H
#define SCREENSHARE_H

#include <QWidget>
#include <set>
#include <vector>

#include "BaseWidget.h"
#include "ByteRTCEventHandler.h"

namespace Ui {
class ScreenShare;
}

namespace bytertc {
class IRTCEngine;
class IRTCRoom;
};

struct SnapshotAttr {
    enum SnapshotType  // thumbnails type
    {
        kUnkonw = 0,
        kWindow,  //
        kScreen   //
    };

    std::string name;  // thumbnail name
    int type = 0;
    void* source_id;  // share source id
    int index = 0;    // thumbnail index
    std::string application;
    int pid = 0;
    bool primary_monitor = false;

    QImage img;
};


class ScreenShare : public BaseWidget
{
    Q_OBJECT

public:
    explicit ScreenShare(QWidget *parent = nullptr);
    ~ScreenShare();

private:
    void initConnections();
    void initRTCVideo();
    void cleanRTCVideo();
    void initUI();
    std::unique_ptr<ByteRTCRoomHandler> createRoomHandler(std::string roomid, std::string uid);
    std::vector<SnapshotAttr> getShareWidgets();

    void startAudioCapture();


private slots:
    void onBtnJoinClicked();
    void onBtnStopClicked();
    void onBtnChooseWindowClicked();
    void onBtnSetClicked();

private slots:
    void onSigRoomStateChanged(std::string roomid, std::string uid, int state, std::string extra_info);
    void onSigUserPublishStreamVideo(std::string stream_id, std::string roomid, std::string uid, bool pub);
    void onSigUserPublishStreamAudio(std::string stream_id, std::string roomid, std::string uid, bool pub);

    //void onSigUserPublishScrreenVideo(std::string roomid, std::string uid, bool pub);
    //void onSigUserPublishScreenAudio(std::string roomid, std::string uid, bool pub);



private:
    Ui::ScreenShare *ui;
    bytertc::IRTCEngine* m_video = nullptr;
    bytertc::IRTCRoom* m_room = nullptr;
    std::string m_roomid;
    std::unique_ptr<ByteRTCEventHandler> m_handler;
    std::unique_ptr<ByteRTCRoomHandler>  m_room_handler;

    std::string m_rendering;
    std::set<std::string> m_remote_uids;
    bool m_localSharing = false;
};

#endif // SCREENSHARE_H
