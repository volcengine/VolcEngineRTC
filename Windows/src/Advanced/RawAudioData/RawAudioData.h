#ifndef RAWAUDIODATA_H
#define RAWAUDIODATA_H

#include <QWidget>
#include <atomic>
#include "ByteRTCEventHandler.h"
#include "BaseWidget.h"

namespace Ui {
class RawAudioData;
}

namespace bytertc{
class IRTCVideo;
class IRTCRoom;
class IAudioDeviceManager;
};

class QFile;
class RawAudioDataObserver : public QObject, public bytertc::IAudioFrameObserver
{
    Q_OBJECT
public:
    RawAudioDataObserver();
    ~RawAudioDataObserver();

    virtual void onRecordAudioFrameOriginal(const bytertc::IAudioFrame& audio_frame) override;

    virtual void onRecordAudioFrame(const bytertc::IAudioFrame& audio_frame) override;

    virtual void onPlaybackAudioFrame(const bytertc::IAudioFrame& audio_frame) override;

    virtual void onRemoteUserAudioFrame(const bytertc::RemoteStreamKey& stream_info, const bytertc::IAudioFrame& audio_frame) override;

    virtual void onMixedAudioFrame(const bytertc::IAudioFrame& audio_frame) override;

    virtual void onRecordScreenAudioFrame(const bytertc::IAudioFrame& audio_frame);

signals:
    void showCallbackLog(QString str);



private:
    QFile* m_file = nullptr;
};


class RawAudioData : public BaseWidget
{
    Q_OBJECT

public:
    explicit RawAudioData(QWidget *parent = nullptr);
    ~RawAudioData();

private:
    void initConnections();
    void initRTCVideo();
    void cleanRTCVideo();
    std::unique_ptr<ByteRTCRoomHandler> createRoomHandler(std::string roomid, std::string uid);
    void updateAudioCaptureList();
    void initUI();

private slots:
    void onBtnJoinClicked();
    void onComboDeviceIndexChanged(int);
    void onCheckRecordChanged(int);
    void onCheckPlaybackChanged(int);
    void onCheckMixedChanged(int);
    void onCheckRemoteUserChanged(int);

private slots:
    void onSigRoomStateChanged(std::string roomid, std::string uid, int state, std::string extra_info);
    void onSigAudioDeviceWarning(std::string device_id, bytertc::RTCAudioDeviceType device_type,
                    bytertc::MediaDeviceWarning device_warning);
    void onSigAudioDeviceStateChanged(std::string device_id, bytertc::RTCAudioDeviceType device_type,
        bytertc::MediaDeviceState device_state,
        bytertc::MediaDeviceError device_error);

    void onSigUserPublishStream(std::string roomid, std::string uid, bytertc::MediaStreamType);
    void onSigUserUnPublishStream(std::string roomid, std::string uid, bytertc::MediaStreamType, bytertc::StreamRemoveReason);
    void onSigUserJoined(ByteRTCRoomHandler::UserInfo info, int);
    void onSigUserLeave(std::string roomid, std::string uid, bytertc::UserOfflineReason);
    void onSigLeaveRoom(std::string roomid, std::string uid, bytertc::RtcRoomStats);


private:
    Ui::RawAudioData *ui;
    bytertc::IRTCVideo *m_video = nullptr;
    bytertc::IRTCRoom *m_room = nullptr;
    std::string m_roomid;
    std::unique_ptr<ByteRTCEventHandler> m_handler;
    std::unique_ptr<ByteRTCRoomHandler>  m_room_handler;
    bytertc::IAudioDeviceManager* m_audio = nullptr;
    RawAudioDataObserver* m_observer = nullptr;

};

#endif // RAWAUDIODATA_H
