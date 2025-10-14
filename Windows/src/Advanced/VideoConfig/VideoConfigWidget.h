#ifndef VIDEOCONFIGWIDGET_H
#define VIDEOCONFIGWIDGET_H

#include <QWidget>
#include <map>
#include <vector>

#include "ByteRTCEventHandler.h"
#include "BaseWidget.h"

namespace Ui {
class VideoConfigWidget;
}

class QComboBox;
namespace bytertc {
    class IRTCEngine;
    class IRTCRoom;
};

class VideoConfigWidget : public BaseWidget
{
    Q_OBJECT

public:
    struct Stru_User {
        std::string streamId;
        std::string roomId;
        std::string uid;
    public:
        Stru_User() {}
        Stru_User(std::string stream, std::string room,std::string u) {
            streamId = stream;
            roomId = room;
            uid = u;
        }
    };

    explicit VideoConfigWidget(QWidget *parent = nullptr);
    ~VideoConfigWidget();
private:
    void initConnections();
    void initRTCVideo();
    void cleanRTCVideo();
    void initUI();
    ByteRTCRoomHandler* createRoomHandler(std::string roomid, std::string uid);
    bytertc::RenderMode getRenderMode(QComboBox *box);
    bytertc::VideoCaptureConfig::CapturePreference getCapturePreference();
    bytertc::VideoEncodePreference getEncoderPreference();
    bytertc::MirrorType getMirrorType();
    bytertc::VideoRotation getRotation();

private slots:
    void onBtnJoinClicked();
    void onBtnCaptureClicked();
    void onBtnEncoderClicked();
    void onComboMirrorClicked(const QString& text);
    void onComboLocalRenderTextChanged(const QString &text);
    void onComboRemoteRenderTextChanged(const QString &text);
    void onCheckWaterClicked(int );
    void onComboboRotationClicked(const QString &text);

private slots:
    void onSigRoomStateChanged(std::string roomid, std::string uid, int state, std::string extra_info);
    void onSigUserPublishStreamVideo(std::string stream_id, std::string roomid, std::string uid, bool pub);
    void onSigUserPublishStreamAudio(std::string stream_id, std::string roomid, std::string uid, bool pub);
    void onSigLocalVideoSizeChanged(const bytertc::VideoFrameInfo info);

private:
    Ui::VideoConfigWidget *ui;
    bytertc::IRTCEngine* m_video = nullptr;
    bytertc::IRTCRoom* m_room = nullptr;
    std::string m_roomid;
    std::map<std::string, Stru_User> m_rusers;
    std::string m_rendering;
    std::unique_ptr<ByteRTCEventHandler> m_handler;

};

#endif // VIDEOCONFIGWIDGET_H
