#ifndef CUSTOMVIDEORENDER_H
#define CUSTOMVIDEORENDER_H

#include <QWidget>

#include "BaseWidget.h"
#include "ByteRTCEventHandler.h"
#include "PlayerYUVNV12.h"
#include "rtc/bytertc_video_defines.h"

#include <QFile>
#include <mutex>


namespace Ui {
class CustomVideoRender;
}

namespace bytertc {
class IRTCEngine;
class IRTCRoom;
};

class RenderRGB;
class CustomVideoRender : public BaseWidget, bytertc::IVideoSink
{
    Q_OBJECT

public:
    explicit CustomVideoRender(QWidget *parent = nullptr);
    ~CustomVideoRender();

private:
    void initConnections();
    void initRTCVideo();
    void cleanRTCVideo();
    void initUI();

    void initPlayer();
    void cleanPlayer();
    void cleanBuffer();
    ByteRTCRoomHandler* createRoomHandler(std::string roomid, std::string uid);

    bytertc::LocalVideoSinkPosition getPosition();
    bytertc::VideoPixelFormat getPixelFormat();


private slots:
    void onBtnJoinClicked();
    void onBtnInitClicked();
    void onBtnUninitClicked();
    void onBtnStartClicked();
    void onBtnStopClicked();

private slots:
    void onSigRoomStateChanged(std::string roomid, std::string uid, int state, std::string extra_info);
    void onSigUserPublishStreamVideo(std::string stream_id, std::string roomid, std::string uid, bool pub);
    void onSigUserPublishStreamAudio(std::string stream_id, std::string roomid, std::string uid, bool pub);
    void onSigFirstLocalVideoFrameCaptured(bytertc::VideoFrameInfo info);

private:
    virtual bool onFrame(bytertc::IVideoFrame* video_frame) override;
    virtual int getRenderElapse() override;

    void openFile(std::string suffix);
    void closeFile();
    void cleanFile();
    std::string getSuffixByPixelFormat(bytertc::VideoPixelFormat fmt);
    void enableRender(bool enable);
    void writeFile(bytertc::IVideoFrame *frame);

private slots:
    void onUpdateFrame();

signals:
    void updateFrame();


private:
    Ui::CustomVideoRender *ui;
    bytertc::IRTCEngine* m_video = nullptr;
    bytertc::IRTCRoom* m_room = nullptr;
    std::string m_roomid;
    std::unique_ptr<ByteRTCEventHandler> m_handler;
    QFile *m_frame_file = nullptr;
    int m_width = 0, m_height = 0;
    std::list<std::string> m_file_names;
    PlayerYUVNV12 *m_yuvPlayer = nullptr;
    VFrame* m_vframe = nullptr;
    RenderRGB *m_rgbPlayer = nullptr;
    std::mutex m_mutex_vframe;

};

#endif // CUSTOMVIDEORENDER_H
