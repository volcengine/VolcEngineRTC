#ifndef BYTERTCEVENTHANDLER_H
#define BYTERTCEVENTHANDLER_H

#include <QObject>
#include "bytertc_room_event_handler.h"
#include "bytertc_video_event_handler.h"
#include "qglobal.h"
#include "rtc/bytertc_audio_effect_player.h"
#include "rtc/bytertc_media_player.h"
#include "rtc/bytertc_transcoder_interface.h"
#include "rtc/bytertc_video_processor_interface.h"

#include <vector>


class ByteRTCRoomHandler : public QObject,
    public bytertc::IRTCRoomEventHandler
{
    Q_OBJECT
public:
    struct UserInfo {
        std::string uid;
        std::string roomid;
        std::string extra_info;
    };

    struct Stru_ForwardStreamStateInfo {
        std::string roomid;
        bytertc::ForwardStreamState state;
        bytertc::ForwardStreamError error;
    } ;
    struct Stru_ForwardStreamEvent {
        std::string roomid;
        bytertc::ForwardStreamEvent event;
    };

    ByteRTCRoomHandler();
    ~ByteRTCRoomHandler();
    ByteRTCRoomHandler(std::string roomid, std::string uid);

    std::string getRoomID();

    //from IRTCRoomEventHandler
    void onTokenWillExpire() override;

    void onRoomStateChanged(
        const char* room_id, const char* uid, int state, const char* extra_info) override;
    void onUserPublishStream(const char* uid, bytertc::MediaStreamType type) override;

    void onUserUnpublishStream(const char* uid, bytertc::MediaStreamType type, bytertc::StreamRemoveReason reason) override;

    void onUserJoined(const bytertc::UserInfo& user_info, int elapsed) override;

    void onUserLeave(const char* uid, bytertc::UserOfflineReason reason) override;

    void onLeaveRoom(const bytertc::RtcRoomStats& stats) override;

    void onForwardStreamStateChanged(bytertc::ForwardStreamStateInfo* infos, int info_count) override;

    void onForwardStreamEvent(bytertc::ForwardStreamEventInfo* infos, int info_count) override;

    signals:
    //room
    void sigRoomStateChanged(std::string roomid, std::string uid, int state, std::string extra_info);
    void sigUserPublishStream(std::string, std::string uid, bytertc::MediaStreamType);
    void sigUserUnPublishStream(std::string, std::string uid, bytertc::MediaStreamType, bytertc::StreamRemoveReason);
    void sigUserJoined(ByteRTCRoomHandler::UserInfo, int);
    void sigUserLeave(std::string, std::string, bytertc::UserOfflineReason);
    void sigLeaveRoom(std::string roomid, std::string uid, bytertc::RtcRoomStats);
    void sigForwardStreamStateChanged(std::vector<ByteRTCRoomHandler::Stru_ForwardStreamStateInfo> result);
    void sigTokenWillExpire();
    void sigForwardStreamEvent(std::vector<ByteRTCRoomHandler::Stru_ForwardStreamEvent> events);
    

private:
    std::string m_roomid, m_uid;
};


class ByteRTCEventHandler : public QObject,
        public bytertc::IRTCVideoEventHandler,
        public bytertc::IAudioEffectPlayerEventHandler,
        public bytertc::IMixedStreamObserver,
                            public bytertc::IMediaPlayerEventHandler

{
    Q_OBJECT
public:

    struct Stru_RemoteStreamKey {
        std::string room_id;
        std::string user_id;
        bytertc::StreamIndex stream_index;

    };

    explicit ByteRTCEventHandler(QObject *parent = nullptr);
    ~ByteRTCEventHandler();
    void setIsSupportClientPushStream(bool support);


private:
    //from IRTCVideoEventHandler
    void onWarning(int warn) override;
    void onError(int err) override;
    void onConnectionStateChanged(bytertc::ConnectionState state) override;
    void onNetworkTypeChanged(bytertc::NetworkType type) override;
    void onAudioDeviceStateChanged(const char* device_id, bytertc::RTCAudioDeviceType device_type,
                bytertc::MediaDeviceState device_state, bytertc::MediaDeviceError device_error) override;
    void onVideoDeviceStateChanged(const char* device_id, bytertc::RTCVideoDeviceType device_type,
                bytertc::MediaDeviceState device_state, bytertc::MediaDeviceError device_error) override;
    void onAudioDeviceWarning(const char* device_id, bytertc::RTCAudioDeviceType device_type,
                bytertc::MediaDeviceWarning device_warning) override;
    void onVideoDeviceWarning(const char* device_id, bytertc::RTCVideoDeviceType device_type,
                bytertc::MediaDeviceWarning device_warning) override;
    void onSysStats(const bytertc::SysStats& stats) override;
    void onLocalVideoSizeChanged(bytertc::StreamIndex index,
                                 const bytertc::VideoFrameInfo& info) override;
    void onFirstLocalVideoFrameCaptured(bytertc::StreamIndex index, bytertc::VideoFrameInfo info) override;
    void onFirstLocalAudioFrame(bytertc::StreamIndex index) override;

    void onFirstRemoteVideoFrameRendered(const bytertc::RemoteStreamKey key, const bytertc::VideoFrameInfo& info) override;
    void onFirstRemoteVideoFrameDecoded(const bytertc::RemoteStreamKey key, const bytertc::VideoFrameInfo& info) override;

    //from IAudioEffectPlayerEventHandler
    void onAudioEffectPlayerStateChanged(int effect_id, bytertc::PlayerState state, bytertc::PlayerError error);

    //from IMixedStreamObserver
    virtual bool isSupportClientPushStream() override;

    virtual void onMixingEvent(
        bytertc::StreamMixingEvent event, const char* task_id, bytertc::StreamMixingErrorCode error, bytertc::MixedStreamType mix_type) override;

    virtual void onMixingVideoFrame(const char* task_id, bytertc::IVideoFrame* video_frame) override;

    virtual void onMixingAudioFrame(const char* task_id, bytertc::IAudioFrame* audio_frame) override;

    virtual void onMixingDataFrame(const char* task_id, bytertc::IDataFrame* data_frame) override;

    virtual void onCacheSyncVideoFrames(const char* task_id, const char* uids[], bytertc::IVideoFrame* video_frames[],
        bytertc::IDataFrame* data_frame[], int count) override;

    // from IMediaPlayerEventHandler
    virtual void onMediaPlayerStateChanged(int playerId, bytertc::PlayerState state, bytertc::PlayerError error) override;

    virtual void onMediaPlayerPlayingProgress(int playerId, int64_t progress) override;


signals:
    void sigWarning(int);
    void sigError(int);
    void sigConnectionStateChanged(bytertc::ConnectionState state);
    void sigNetworkTypeChanged(bytertc::NetworkType type);
    void sigAudioDeviceStateChanged(std::string device_id, bytertc::RTCAudioDeviceType device_type,
                                  bytertc::MediaDeviceState device_state,
                                  bytertc::MediaDeviceError device_error);
    void sigVideoDeviceStateChanged(std::string device_id, bytertc::RTCVideoDeviceType device_type,
                                    bytertc::MediaDeviceState device_state, bytertc::MediaDeviceError device_error);

    void sigAudioDeviceWarning(std::string device_id, bytertc::RTCAudioDeviceType device_type,
                    bytertc::MediaDeviceWarning device_warning);
    void sigVideoDeviceWarning(std::string device_id, bytertc::RTCVideoDeviceType device_type,
                    bytertc::MediaDeviceWarning device_warning);
    void sigSysStats(const bytertc::SysStats stats);
    void sigLocalVideoSizeChanged(bytertc::StreamIndex index,
                               const bytertc::VideoFrameInfo info);
    void sigFirstLocalVideoFrameCaptured(bytertc::StreamIndex index, bytertc::VideoFrameInfo info);
    void sigFirstLocalAudioFrame(bytertc::StreamIndex index);

    //IAudioEffectPlayerEventHandler
    void sigAudioEffectPlayerStateChanged(int effect_id, bytertc::PlayerState state, bytertc::PlayerError error);

    //IMixedStreamObserver
    void sigMixingEvent(bytertc::StreamMixingEvent event, std::string task_id, bytertc::StreamMixingErrorCode error, bytertc::MixedStreamType mix_type);

    void sigFirstRemoteVideoFrameRendered(const ByteRTCEventHandler::Stru_RemoteStreamKey key, const bytertc::VideoFrameInfo& info);

    //IMediaPlayerEventHandler
    void sigMediaPlayerStateChanged(int playerId, bytertc::PlayerState state, bytertc::PlayerError error) ;

    void sigMediaPlayerPlayingProgress(int playerId, int64_t progress);


private:
    bool m_supportClientPushStream = false;

};

Q_DECLARE_METATYPE(std::string)
Q_DECLARE_METATYPE(int64_t)
Q_DECLARE_METATYPE(bytertc::MediaStreamType)
Q_DECLARE_METATYPE(bytertc::StreamRemoveReason)
Q_DECLARE_METATYPE(bytertc::UserOfflineReason)
Q_DECLARE_METATYPE(bytertc::RtcRoomStats)
Q_DECLARE_METATYPE(ByteRTCRoomHandler::UserInfo)
Q_DECLARE_METATYPE(bytertc::PlayerState);
Q_DECLARE_METATYPE(bytertc::PlayerError);
Q_DECLARE_METATYPE(ByteRTCRoomHandler::Stru_ForwardStreamStateInfo)
Q_DECLARE_METATYPE(std::vector<ByteRTCRoomHandler::Stru_ForwardStreamStateInfo>)
Q_DECLARE_METATYPE(ByteRTCRoomHandler::Stru_ForwardStreamEvent)
Q_DECLARE_METATYPE(std::vector<ByteRTCRoomHandler::Stru_ForwardStreamEvent>)
Q_DECLARE_METATYPE(bytertc::StreamMixingEvent)
Q_DECLARE_METATYPE(bytertc::StreamMixingErrorCode)
Q_DECLARE_METATYPE(bytertc::MixedStreamType)
Q_DECLARE_METATYPE(bytertc::RTCAudioDeviceType)
Q_DECLARE_METATYPE(bytertc::MediaDeviceState)
Q_DECLARE_METATYPE(bytertc::MediaDeviceError)
Q_DECLARE_METATYPE(bytertc::VideoFrameInfo)
Q_DECLARE_METATYPE(bytertc::RemoteStreamKey)
Q_DECLARE_METATYPE(bytertc::StreamIndex)

#endif // BYTERTCEVENTHANDLER_H
