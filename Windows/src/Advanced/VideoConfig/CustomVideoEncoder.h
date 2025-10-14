#ifndef CUSTOMVIDEOENCODER_H
#define CUSTOMVIDEOENCODER_H

#include <QWidget>
#include "ByteRTCEventHandler.h"
#include "BaseWidget.h"

#include <set>
#include <thread>
#include <memory>
#include "H264Reader.h"

namespace Ui {
class CustomVideoEncoder;
}

namespace bytertc {
class IRTCEngine;
class IRTCRoom;
};

class H264Reader;
class CustomVideoEncoder : public BaseWidget, public bytertc::IExternalVideoEncoderEventHandler, bytertc::IRemoteEncodedVideoFrameObserver
{
    Q_OBJECT

public:
    explicit CustomVideoEncoder(QWidget *parent = nullptr);
    ~CustomVideoEncoder();

private:
    void initConnections();
    void initRTCVideo();
    void cleanRTCVideo();
    void initUI();
    std::unique_ptr<ByteRTCRoomHandler> createRoomHandler(std::string roomid, std::string uid);

    void pushThreadRun();
    bool PushEncodeFrame(int w, int h, int fps, std::vector<uint8_t>& frame, bool is_key_frame);


private slots:
    void onBtnJoinClicked();
    void onBtnStartClicked();
    void onBtnStopClicked();
    void onBtnChooseClicked();

private slots:
    void onSigRoomStateChanged(std::string roomid, std::string uid, int state, std::string extra_info);
    void onSigUserPublishStreamVideo(std::string stream_id, std::string roomid, std::string uid, bool pub);
    void onSigUserPublishStreamAudio(std::string stream_id, std::string roomid, std::string uid, bool pub);

private:
    virtual void onStart(bytertc::StreamIndex index) override;
    virtual void onStop(bytertc::StreamIndex index) override;
    virtual void onRateUpdate(bytertc::StreamIndex index, int32_t video_index, bytertc::VideoRateInfo info) override;
    virtual void onRequestKeyFrame(bytertc::StreamIndex index, int32_t video_index) override;
    virtual void onActiveVideoLayer(bytertc::StreamIndex index, int32_t video_index, bool active) override;


private:
    virtual void onRemoteEncodedVideoFrame(const bytertc::RemoteStreamKey& stream_info, const bytertc::IEncodedVideoFrame& video_stream) override;


private:
    Ui::CustomVideoEncoder *ui;
    bytertc::IRTCEngine* m_video = nullptr;
    bytertc::IRTCRoom* m_room = nullptr;
    std::string m_roomid;
    std::string m_rendering;
    std::unique_ptr<ByteRTCEventHandler> m_handler;
    std::unique_ptr<ByteRTCRoomHandler>  m_room_handler;
    std::thread *m_push_thread = nullptr;
    std::atomic_bool  m_thread_run = false;

    std::set<std::string> m_remote_uids;
    std::unique_ptr<H264Reader> m_h264_reader;
};


#endif // CUSTOMVIDEOENCODER_H
