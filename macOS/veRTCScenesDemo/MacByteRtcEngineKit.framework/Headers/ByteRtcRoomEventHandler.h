//
//  ByteRtcRoomEventHandler.h
//  ByteRtcEngineKitSrc
//
//  Created by sakura on 2020/3/18.
//

#ifndef ByteRtcRoomEventHandler_h
#define ByteRtcRoomEventHandler_h

#include "byte_rtc_room_interface.h"

@protocol ByteRtcRoomDelegate;
@class ByteRtcRoom;

class ByteRtcRoomEventHandler : public bytertc::IRTCRoomEventHandler {
public:
    ByteRtcRoomEventHandler(ByteRtcRoom * rtcRoom, id<ByteRtcRoomDelegate> delegate);
    ~ByteRtcRoomEventHandler();

    void updateByteRtcRoomDelegate(id<ByteRtcRoomDelegate> delegate);

public:

    virtual void OnJoinChannelSuccess(const char* roomId, const char *uid, int elapsed) override;

    virtual void OnRejoinChannelSuccess(const char* roomId, const char *uid, int elapsed) override;

    virtual void OnLeaveChannel(const bytertc::RtcStats& stats) override;

    virtual void OnChannelWarning(int warn) override;

    virtual void OnChannelError(int err) override;

    virtual void OnAudioQuality(const char* uid, int quality, unsigned short delay, unsigned short lost) override;

    virtual void OnAudioVolumeIndication(
            const bytertc::AudioVolumeInfo* speakers, unsigned int speakerNumber, int totalVolume) override;

    virtual void OnRtcStats(const bytertc::RtcStats& stats) override;

    virtual void OnNetworkQuality(const char* uid, bytertc::NetworkQuality txQuality, bytertc::NetworkQuality rxQuality) override;

    virtual void OnUserJoined(
            const char* uid, const char* teamId, const bytertc::RangeAudioMode sendMode, int elapsed) override;

    virtual void OnUserOffline(const char* uid, bytertc::USER_OFFLINE_REASON_TYPE reason) override;

    virtual void OnMuteAllRemoteAudio(const char* uid, bytertc::MuteState mute_state) override;

    virtual void OnMuteAllRemoteVideo(const char* uid, bytertc::MuteState mute) override;

    virtual void OnUserMuteAudio(const char* uid, bytertc::MuteState mute_state) override;

    virtual void OnUserEnableLocalAudio(const char* uid, bool enabled) override;

    virtual void OnLocalAudioStats(const bytertc::LocalAudioStats& stats) override;

    virtual void OnRemoteAudioStats(const bytertc::RemoteAudioStats& stats) override;

    virtual void OnFirstLocalAudioFrame(bytertc::StreamIndex index) override;

    virtual void OnFirstRemoteAudioFrame(const bytertc::RemoteStreamKey& key) override;

    virtual void OnStreamRemove(const bytertc::ByteStream& stream, bytertc::RtcStreamRemoveReason reason) override;

    virtual void OnStreamAdd(const bytertc::ByteStream& stream) override;

    virtual void OnStreamSubscribed(bytertc::SUBSCRIBE_STATE stateCode, const char *user_id, const bytertc::SubscribeConfig &info) override;

    virtual void OnStreamPublishSucceed(const char *user_id, bool is_screen) override;

    virtual void OnRoomMessageReceived(const char* uid, const char* message) override;
    
    virtual void OnRoomBinaryMessageReceived(const char* uid, int size, const uint8_t* message) override;
    
    virtual void OnUserMessageReceived(const char* uid, const char* message) override;
    
    virtual void OnUserBinaryMessageReceived(const char* uid, int size, const uint8_t* message) override;
    
    virtual void OnUserMessageSendResult(int64_t msgid, int error) override;
    
    virtual void OnRoomMessageSendResult(int64_t msgid, int error) override;

    virtual void OnTranscodingError(const char* url, int error) override;

    virtual void OnFirstLocalVideoFrameCaptured(bytertc::StreamIndex index, bytertc::VideoFrameInfo info) override;

    virtual void OnLocalVideoSizeChanged(bytertc::StreamIndex index, const bytertc::VideoFrameInfo& info) override;
    
    virtual void OnRemoteVideoSizeChanged(bytertc::RemoteStreamKey key, const bytertc::VideoFrameInfo& info) override;

    virtual void OnFirstRemoteVideoFrameRendered(const bytertc::RemoteStreamKey key, const bytertc::VideoFrameInfo& info) override;

    virtual void OnUserMuteVideo(const char* uid, bytertc::MuteState mute) override;

    virtual void OnUserEnableLocalVideo(const char* uid, bool enabled) override;

    virtual void OnLocalVideoStats(const bytertc::LocalVideoStats& stats) override;

    virtual void OnRemoteVideoStats(const bytertc::RemoteVideoStats& stats) override;

private:
    __weak id<ByteRtcRoomDelegate> _delegate;
    __weak ByteRtcRoom * _rtcRoom;
};

#endif /* ByteRtcRoomEventHandler_h */
