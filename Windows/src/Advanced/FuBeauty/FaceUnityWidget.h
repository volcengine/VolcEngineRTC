#ifndef FACEUNITYWIDGET_H
#define FACEUNITYWIDGET_H

#include <QWidget>
#include <mutex>
#include <QFile>
#include <thread>
#include "BaseWidget.h"
#include "ByteRTCEventHandler.h"

#if __has_include("CNamaSDK.h")
#include "CNamaSDK.h"
#include "Namas.h"
#endif


namespace Ui {
class FaceUnityWidget;
}

namespace bytertc {
    class IRTCEngine;
    class IRTCRoom;
    class IVideoFrame;
};
namespace NamasNameSpace {
class Namas;
};

class PixTextWidget;
class FaceUnityWidget :public BaseWidget, public bytertc::IVideoProcessor
{
    Q_OBJECT

public:
    typedef struct VideoFrame {
        bytertc::IVideoFrame* frame = nullptr;
        uint8_t* yuv_buffer = new uint8_t[1280*720*3];
        int width =0 ,height = 0;

    public:
        void cleanBuffer() {
            if (yuv_buffer) delete[]yuv_buffer;
            yuv_buffer = nullptr;
        }
    };

    explicit FaceUnityWidget(QWidget *parent = nullptr);
    ~FaceUnityWidget();


private:
    void initConnections();
    void showItem();
    void initRTC();
    void cleanRTC();
    std::unique_ptr<ByteRTCRoomHandler> createRoomHandler(std::string roomid, std::string uid);
    int initNama();
    void cleanNama();
    void initUI();

    int joinRoom();
    int leaveRoom();
    int checkIDValid();

    void funcProcessVideoFrame();
    

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

    void onSigUserPublishStreamVideo(std::string stream_id, std::string roomid, std::string uid, bool pub);
    void onSigUserPublishStreamAudio(std::string stream_id, std::string roomid, std::string uid, bool pub);
    void onSigUserJoined(ByteRTCRoomHandler::UserInfo info);
    void onSigUserLeave(std::string roomid, std::string uid, bytertc::UserOfflineReason);
    void onSigLeaveRoom(std::string roomid, std::string uid, bytertc::RtcRoomStats);

    


private:
    void pushVideoFrame(bytertc::IVideoFrame *src);
    bytertc::IVideoFrame *popVideoFrame(bytertc::IVideoFrame *src);
    void clearVideoFrames();
    
    void copyIVideoFram2LocalFrame(bytertc::IVideoFrame *src, VideoFrame &frame);
    void copyLocalFrame2IVideoFrame(bytertc::IVideoFrame* dst, VideoFrame &frame);



private:
    Ui::FaceUnityWidget *ui;
    std::vector<PixTextWidget*> m_pixWidgets;
    std::vector<PixTextWidget*>  m_mapTools;
    std::vector<PixTextWidget*>  m_mapMasks;

    bytertc::IRTCEngine *m_video = nullptr;
    bytertc::IRTCRoom  *m_room = nullptr;
    std::unique_ptr<ByteRTCEventHandler> m_handler;
    std::unique_ptr<ByteRTCRoomHandler>  m_room_handler;
    NamasNameSpace::Namas* m_nama = nullptr;

    std::thread* m_thread_process = nullptr;
    std::mutex   m_mutex_process;
    std::atomic<bool>         m_thread_run {true};

    std::vector<VideoFrame> m_inLocalFrames; //未处理的视频帧
    std::vector<VideoFrame> m_outLocalFrames;//已经处理好的视频帧

    std::mutex m_mutex_in, m_mutex_out;
    std::condition_variable m_cond_in, m_cond_out;

    QFile* m_outFile = nullptr;
    bool m_dmp_out = false;
    QFile* m_inFile = nullptr;
};

#endif // FACEUNITYWIDGET_H
