#ifndef CUSTOMVIDEOCAPTURE_H
#define CUSTOMVIDEOCAPTURE_H

#include <QWidget>
#include <set>
#include "BaseWidget.h"
#include "ByteRTCEventHandler.h"

namespace Ui {
class CustomVideoCapture;
}
namespace bytertc {
class IRTCEngine;
class IRTCRoom;
};

class QTimer;
class CustomVideoCapture : public BaseWidget
{
    Q_OBJECT

public:
    explicit CustomVideoCapture(QWidget *parent = nullptr);
    ~CustomVideoCapture();


private:
    void initConnections();
    void initRTCVideo();
    void cleanRTCVideo();
    void initUI();
    std::unique_ptr<ByteRTCRoomHandler> createRoomHandler(std::string roomid, std::string uid);

    std::string getLocalPath();

private slots:
    void onBtnJoinClicked();
    void onBtnInitClicked();
    void onBtnUninitClicked();
    void onBtnStartClicked();
    void onBtnStopClicked();

    void onTimeout();
    void onTimeoutRGBA();

private slots:
    void onSigRoomStateChanged(std::string roomid, std::string uid, int state, std::string extra_info);
    void onSigUserPublishStreamVideo(std::string stream_id, std::string roomid, std::string uid, bool pub);
    void onSigUserPublishStreamAudio(std::string stream_id, std::string roomid, std::string uid, bool pub);


private:
    Ui::CustomVideoCapture *ui;
    bytertc::IRTCEngine* m_video = nullptr;
    bytertc::IRTCRoom* m_room = nullptr;
    std::string m_roomid;
    std::unique_ptr<ByteRTCEventHandler> m_handler;
    std::unique_ptr<ByteRTCRoomHandler>  m_room_handler;
    QTimer* m_timer = nullptr;
    int m_push_fps = 15; //推送的帧率
    FILE* m_file = nullptr;
    int m_push_width = 256; //推送外部视频源宽度
    int m_push_height = 144;//推送外部视频源高度
    int m_frame_count = 0;//推送外部视频源的帧数
    int m_frame_index = 0; //当前推送的视频帧索引
    int m_pixel_fmt = 0; //当前的视频格式
    int m_1frame_size = 0; //一帧大小

    std::string m_rendering;
    std::set<std::string> m_remote_uids;

    
};

#endif // CUSTOMVIDEOCAPTURE_H
