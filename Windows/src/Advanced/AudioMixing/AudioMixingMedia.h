#ifndef AudioMixingMedia_H
#define AudioMixingMedia_H

#include <QWidget>
#include <QTimer>
#include "ByteRTCEventHandler.h"
#include "BaseWidget.h"
#include "rtc/bytertc_audio_defines.h"

class QFile;
namespace Ui {
class AudioMixingMedia;
}

namespace bytertc {
    class IRTCVideo;
    class IRTCRoom;
    class IMediaPlayer;
};


class AudioMixingMedia : public BaseWidget
{
    Q_OBJECT

public:

    struct Stru_Infos {
        bytertc::IMediaPlayer* player;
        int id;
    };

    explicit AudioMixingMedia(QWidget *parent = nullptr);
    ~AudioMixingMedia();

private:
    void initConnections();
    void initRTCVideo();
    void cleanRTCVideo();
    void initFile();
    void cleanFile();
    std::unique_ptr<ByteRTCRoomHandler> createRoomHandler(std::string roomid, std::string uid);
    bytertc::AudioMixingDualMonoMode getAudioDualMode();

private slots:
    void onBtnJoinClicked(); //进房

    //非PCM槽
    void onBtnBrowserClicked(); //浏览
    void onBtnPlayClicked();
    void onBtnPauseClicked();
    void onBtnResumeClicked();
    void onBtnStopClicked();
    void onSpinVolueChanged(int value);
    void onSpinPitchValueChanged(int value);
    void onSpinPostionValueChanged(int pos);
    void onComboModeChanged(const QString &);
    void onBtnSetTrackClicked();
    void onSpinSpeedChanged(int );
    void onBtnGetTimeClicked();

    //PCM 槽
    void onBtnPcmStartClicked();
    void onBtnPcmStopClicked();
    void onSpinPcmVolumeChanged(int);

private slots:
    void onSigRoomStateChanged(std::string roomid, std::string uid, int state, std::string extra_info);

    void onSigUserPublishStream(std::string, std::string uid, bytertc::MediaStreamType);
    void onSigUserUnPublishStream(std::string, std::string uid, bytertc::MediaStreamType, bytertc::StreamRemoveReason);
    void onSigUserJoined(ByteRTCRoomHandler::UserInfo, int);
    void onSigUserLeave(std::string, std::string, bytertc::UserOfflineReason);
    void onSigLeaveRoom(std::string roomid, std::string uid, bytertc::RtcRoomStats);
    void onSigMediaPlayerStateChanged(int playerId, bytertc::PlayerState state, bytertc::PlayerError error) ;
    void onSigMediaPlayerPlayingProgress(int playerId, int64_t progress);



private slots:
    void onPushDataTimer();

private:
    Ui::AudioMixingMedia *ui;
    bytertc::IRTCVideo* m_video = nullptr;
    bytertc::IRTCRoom* m_room = nullptr;
    std::unique_ptr<ByteRTCEventHandler> m_handler;
    std::unique_ptr<ByteRTCRoomHandler>  m_room_handler;
    std::string m_file_path; //音乐文件的路径

    std::map<int, bytertc::IMediaPlayer*> m_infos;
    QTimer m_timer;
    QFile *m_pcm_file = nullptr;
    bool m_first_push = true;
};

#endif // AudioMixingMedia_H
