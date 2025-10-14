#ifndef CUSTOMAUDIOCAPTURE_H
#define CUSTOMAUDIOCAPTURE_H

#include <QWidget>
#include <set>
#include <QTimer>
#include <QFile>

#include "ByteRTCEventHandler.h"
#include "BaseWidget.h"

namespace Ui {
class CustomAudioCapture;
}


namespace bytertc {
class IRTCEngine;
class IRTCRoom;
};

class CustomAudioCapture : public BaseWidget
{
    Q_OBJECT

public:
    explicit CustomAudioCapture(QWidget *parent = nullptr);
    ~CustomAudioCapture();

private:

    void initConnections();
    void initRTCVideo();
    void cleanRTCVideo();
    void initUI();
    ByteRTCRoomHandler *createRoomHandler(std::string roomid, std::string uid);
    void cleanFile();

private slots:
    void onBtnStartClicked();
    void onBtnStopClicked();
    void onBtnJoinRoomClicked();

private slots:
    void onSigRoomStateChanged(std::string roomid, std::string uid, int state, std::string extra_info);
    void onSigUserPublishStreamVideo(std::string stream_id, std::string roomid, std::string uid, bool pub);
    void onSigUserPublishStreamAudio(std::string stream_id, std::string roomid, std::string uid, bool pub);

private slots:
    void onPushDataTimer();

private:
    Ui::CustomAudioCapture *ui;

    bytertc::IRTCEngine* m_video = nullptr;
    bytertc::IRTCRoom* m_room = nullptr;
    std::string m_roomid;
    std::string m_rendering;
    std::set<std::string> m_remote_uids;
    std::unique_ptr<ByteRTCEventHandler> m_handler;
    QTimer m_timer;
    QFile *m_pcm_file = nullptr;

};

#endif // CUSTOMAUDIOCAPTURE_H
