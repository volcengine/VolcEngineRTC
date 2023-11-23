#ifndef FACEUNITYWIDGET_H
#define FACEUNITYWIDGET_H

#include <QWidget>
#include <mutex>
#include "ByteRTCEventHandler.h"

#if __has_include("CNamaSDK.h")
#include "CNamaSDK.h"
#include "Nama.h"
#endif


namespace Ui {
class FaceUnityWidget;
}

namespace bytertc {
    class IRTCVideo;
    class IRTCRoom;
    class IVideoFrame;
};
namespace NamaNameSpace {
class Nama;
};

class PixTextWidget;
class FaceUnityWidget :
        public QWidget,
        public bytertc::IVideoProcessor
{
    Q_OBJECT

public:
    explicit FaceUnityWidget(QWidget *parent = nullptr);
    ~FaceUnityWidget();


private:
    void initConnections();
    void resetData();
    void showItem();
    void initRTC();
    void cleanRTC();
    std::unique_ptr<ByteRTCRoomHandler> createRoomHandler(std::string roomid, std::string uid);
    int initNama();
    void cleanNama();

    int joinRoom();
    int leaveRoom();
    int checkIDValid();

    void funcProcessVideoFrame();
    void dealVideoFrame();
    

    virtual bytertc::IVideoFrame *processVideoFrame(bytertc::IVideoFrame* src_frame) override;
    void cleanThread();

    void resetFaceBueatyValue();

public slots:
    void onBtnJoinRoomClicked();
    void onSliderValueChanged(int value);
    void onBtnRevertClicked();
    void onShowErrorTips(int error, QString);
    void onBtnFilterClicked();
    void onButton1Clicked();
    void onButton2Clicked();

private slots:
    void onRTCState(std::string str);
    void onSigRoomStateChanged(std::string roomid, std::string uid, int state, std::string extra_info);

    void onSigUserPublishStream(std::string roomid, std::string uid, bytertc::MediaStreamType);
    void onSigUserUnPublishStream(std::string roomid, std::string uid, bytertc::MediaStreamType, bytertc::StreamRemoveReason);
    void onSigUserJoined(ByteRTCRoomHandler::UserInfo info, int);
    void onSigUserLeave(std::string roomid, std::string uid, bytertc::UserOfflineReason);
    void onSigLeaveRoom(std::string roomid, std::string uid, bytertc::RtcRoomStats);



private:
    Ui::FaceUnityWidget *ui;
    std::vector<PixTextWidget*> m_pixWidgets;
    std::vector<PixTextWidget*>  m_mapTools;
    std::vector<PixTextWidget*>  m_mapMasks;

    bytertc::IRTCVideo *m_video = nullptr;
    bytertc::IRTCRoom  *m_room = nullptr;
    std::unique_ptr<ByteRTCEventHandler> m_handler;
    std::unique_ptr<ByteRTCRoomHandler>  m_room_handler;
    NamaNameSpace::Nama* m_nama = nullptr;

    std::thread* m_thread_process = nullptr;
    std::mutex   m_mutex_process;
    std::atomic<bool>         m_thread_run {true};
    std::condition_variable m_cond1, m_cond2;
    std::atomic<int>    m_process_num;
    bytertc::IVideoFrame* m_currentFrame = nullptr;
};

#endif // FACEUNITYWIDGET_H
