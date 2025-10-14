#ifndef BYTERTCEVENTHANDLER_H
#define BYTERTCEVENTHANDLER_H

#include <QObject>
#include "bytertc_room_event_handler.h"
#include "bytertc_engine_event_handler.h"
#include "qglobal.h"
#include "rtc/bytertc_audio_effect_player.h"
#include "rtc/bytertc_media_player.h"
#include "rtc/bytertc_transcoder_define.h"
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
    void onUserPublishStreamAudio(const char* stream_id, const bytertc::StreamInfo& stream_info, bool is_publish) override;
    void onUserPublishStreamVideo(const char* stream_id, const bytertc::StreamInfo& stream_info, bool is_publish) override;

    //void onUserPublishScreenVideo(const char* room_id, const char* uid, bool is_publish) override;
    //void onUserPublishScreenAudio(const char* room_id, const char* uid, bool is_publish) override;

//    void onUserUnpublishStream(const char* uid, bytertc::MediaStreamType type, bytertc::StreamRemoveReason reason) override;

//    void onUserUnpublishScreen(const char* uid, bytertc::MediaStreamType type, bytertc::StreamRemoveReason reason) override;

   // void onUserPublishScreen(const char* uid, bytertc::MediaStreamType type) override;

    void onUserJoined(const bytertc::UserInfo& user_info) override;


    void onUserLeave(const char* uid, bytertc::UserOfflineReason reason) override;

    void onLeaveRoom(const bytertc::RtcRoomStats& stats) override;

    void onForwardStreamStateChanged(bytertc::ForwardStreamStateInfo* infos, int info_count) override;

    void onForwardStreamEvent(bytertc::ForwardStreamEventInfo* infos, int info_count) override;

    signals:
    //room
    void sigRoomStateChanged(std::string roomid, std::string uid, int state, std::string extra_info);
    void sigUserPublishStreamVideo(std::string stream_id, std::string roomid, std::string uid, bool pub);
    void sigUserPublishStreamAudio(std::string stream_id, std::string roomid, std::string uid, bool pub);
    //void sigUserPublishScreenVideo(std::string room_id, std::string uid, bool is_publish);
    //void sigUserPublishScreenAudio(std::string room_id, std::string uid, bool is_publish);

    void sigUserJoined(ByteRTCRoomHandler::UserInfo);
    void sigUserLeave(std::string, std::string, bytertc::UserOfflineReason);
    void sigLeaveRoom(std::string roomid, std::string uid, bytertc::RtcRoomStats);
    void sigForwardStreamStateChanged(std::vector<ByteRTCRoomHandler::Stru_ForwardStreamStateInfo> result);
    void sigTokenWillExpire();
    void sigForwardStreamEvent(std::vector<ByteRTCRoomHandler::Stru_ForwardStreamEvent> events);
    

private:
    std::string m_roomid, m_uid;
};


class ByteRTCEventHandler : public QObject,
        public bytertc::IRTCEngineEventHandler,
        public bytertc::IAudioEffectPlayerEventHandler,
        public bytertc::IMediaPlayerEventHandler

{
    Q_OBJECT
public:

    struct Stru_RemoteStreamKey {
        std::string stream_id;
        std::string room_id;
        std::string user_id;
        bytertc::StreamIndex stream_index;

    };

    struct Stru_RtcUser{
        std::string user_id;
        std::string meta_data;
    };

    struct MixedStreamTaskInfo{
        std::string task_id;
        int push_target_type;
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
    void onLocalVideoSizeChanged(bytertc::IVideoSource* video_source, const bytertc::VideoFrameInfo& info) override;
    void onFirstLocalVideoFrameCaptured(bytertc::IVideoSource* video_source, const bytertc::VideoFrameInfo& info) override;
    void onFirstLocalAudioFrame(bytertc::IAudioSource* audio_source) override;

    void onRemoteVideoSizeChanged(bytertc::RemoteStreamKey key, const bytertc::VideoFrameInfo& info);
    void onFirstRemoteVideoFrameRendered(const char* stream_id, const bytertc::StreamInfo& stream_info, const bytertc::VideoFrameInfo& info) override;
    void onFirstRemoteVideoFrameDecoded(const char* stream_id, const bytertc::StreamInfo& stream_info, const bytertc::VideoFrameInfo& info) override;

    //from IAudioEffectPlayerEventHandler
    void onAudioEffectPlayerStateChanged(int effect_id, bytertc::PlayerState state, bytertc::PlayerError error);

    //from IMixedStreamObserver
//    virtual bool isSupportClientPushStream() override;

//    virtual void onMixingEvent(
//        bytertc::StreamMixingEvent event, const char* task_id, bytertc::StreamMixingErrorCode error, bytertc::MixedStreamType mix_type) override;


//    virtual void onMixingVideoFrame(const char* task_id, bytertc::IVideoFrame* video_frame) override;

//    virtual void onMixingAudioFrame(const char* task_id, bytertc::IAudioFrame* audio_frame) override;

//    virtual void onMixingDataFrame(const char* task_id, bytertc::IDataFrame* data_frame) override;

//    virtual void onCacheSyncVideoFrames(const char* task_id, const char* uids[], bytertc::IVideoFrame* video_frames[],
//        bytertc::IDataFrame* data_frame[], int count) override;

    virtual void onMixedStreamEvent(bytertc::MixedStreamTaskInfo info, bytertc::MixedStreamTaskEvent event, bytertc::MixedStreamTaskErrorCode error_code) override;
    virtual void onSingleStreamEvent(const char *task_id, bytertc::SingleStreamTaskEvent event, bytertc::SingleStreamTaskErrorCode error_code) override;

    // from IMediaPlayerEventHandler
    virtual void onMediaPlayerStateChanged(int playerId, bytertc::PlayerState state, bytertc::PlayerError error) override;

    virtual void onMediaPlayerPlayingProgress(int playerId, int64_t progress) override;

    void onSEIMessageReceived(const char* stream_id, const bytertc::StreamInfo& stream_info, const uint8_t* message, int length) override;

    void onStreamSyncInfoReceived(const char* stream_id, const bytertc::StreamInfo& stream_info, bytertc::SyncInfoStreamType stream_type,
        const uint8_t* data, int32_t length) override;

    virtual void onMediaPlayerEvent(int player_id, bytertc::PlayerEvent event, const char* message) override;
    //screen
    //void onScreenVideoFrameSendStateChanged(const char* room_id, const bytertc::RtcUser& user, bytertc::FirstFrameSendState state) override;


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
    void sigLocalVideoSizeChanged(const bytertc::VideoFrameInfo info);
    void sigFirstLocalVideoFrameCaptured(bytertc::VideoFrameInfo info);
    void sigFirstLocalAudioFrame();

    //IAudioEffectPlayerEventHandler
    void sigAudioEffectPlayerStateChanged(int effect_id, bytertc::PlayerState state, bytertc::PlayerError error);

    //IMixedStreamObserver
    void sigMixingEvent(ByteRTCEventHandler::MixedStreamTaskInfo info, bytertc::MixedStreamTaskEvent event, bytertc::MixedStreamTaskErrorCode error_code);

    void sigFirstRemoteVideoFrameRendered(const ByteRTCEventHandler::Stru_RemoteStreamKey key, const bytertc::VideoFrameInfo& info);

    //IMediaPlayerEventHandler
    void sigMediaPlayerStateChanged(int playerId, bytertc::PlayerState state, bytertc::PlayerError error) ;

    void sigMediaPlayerPlayingProgress(int playerId, int64_t progress);

    void sigSEIMessageReceived(ByteRTCEventHandler::Stru_RemoteStreamKey stream_key, std::string str);

    void sigStreamSyncInfoReceived(ByteRTCEventHandler::Stru_RemoteStreamKey stream_key, bytertc::SyncInfoStreamType stream_type, std::string str);

    //void sigScreenVideoFrameSendStateChanged(std::string room_id, Stru_RtcUser user, bytertc::FirstFrameSendState state) ;


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
Q_DECLARE_METATYPE(ByteRTCEventHandler::MixedStreamTaskInfo)
Q_DECLARE_METATYPE(bytertc::MixedStreamTaskEvent)
Q_DECLARE_METATYPE(bytertc::MixedStreamTaskErrorCode)
Q_DECLARE_METATYPE(bytertc::MixedStreamType)
Q_DECLARE_METATYPE(bytertc::RTCAudioDeviceType)
Q_DECLARE_METATYPE(bytertc::MediaDeviceState)
Q_DECLARE_METATYPE(bytertc::MediaDeviceError)
Q_DECLARE_METATYPE(bytertc::VideoFrameInfo)
Q_DECLARE_METATYPE(bytertc::RemoteStreamKey)
Q_DECLARE_METATYPE(bytertc::StreamIndex)
Q_DECLARE_METATYPE(bytertc::SyncInfoStreamType)
Q_DECLARE_METATYPE(ByteRTCEventHandler::Stru_RemoteStreamKey)
Q_DECLARE_METATYPE(bytertc::FirstFramePlayState)
Q_DECLARE_METATYPE(ByteRTCEventHandler::Stru_RtcUser)
Q_DECLARE_METATYPE(bytertc::FirstFrameSendState);

#endif // BYTERTCEVENTHANDLER_H
