/*
 * Copyright (c) 2020 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngine Room Event Handler
*/

#import "src/sdk/native/rtc/bytertc_room_interface.h"

@protocol ByteRTCRoomDelegate;
@class ByteRTCRoom;

class ByteRTCRoomEventHandler : public bytertc::IRTCRoomEventHandler {
public:
    ByteRTCRoomEventHandler(ByteRTCRoom * rtcRoom, id<ByteRTCRoomDelegate> delegate);
    ~ByteRTCRoomEventHandler();

    void updateRoomDelegate(id<ByteRTCRoomDelegate> delegate);

public:
    virtual void OnJoinRoomResult(const char* room_id, const char* uid, int error_code, bytertc::JoinRoomType join_type, int elapsed) override;

    virtual void OnLeaveRoom(const bytertc::RtcRoomStats &stats) override;

    virtual void OnRoomWarning(int warn) override;

    virtual void OnRoomError(int err) override;

    virtual void OnAudioVolumeIndication(
            const bytertc::AudioVolumeInfo* speakers, unsigned int speakerNumber, int totalVolume) override;

    virtual void OnRoomStats(const bytertc::RtcRoomStats &stats) override;

    virtual void OnUserJoined(const bytertc::UserInfo& userInfo, int elapsed) override;

    virtual void OnUserLeave(const char* uid, bytertc::UserOfflineReason reason) override;

    virtual void OnMuteAllRemoteAudio(const char* uid, bytertc::MuteState mute_state) override;

    virtual void OnMuteAllRemoteVideo(const char* uid, bytertc::MuteState mute) override;

    virtual void OnUserMuteAudio(const char* uid, bytertc::MuteState mute_state) override;

    virtual void OnUserEnableLocalAudio(const char* uid, bool enabled) override;

    virtual void OnLocalStreamStats(const bytertc::LocalStreamStats &stats) override;

    virtual void OnRemoteStreamStats(const bytertc::RemoteStreamStats &stats) override;

    virtual void OnFirstLocalAudioFrame(bytertc::StreamIndex index) override;

    virtual void OnFirstRemoteAudioFrame(const bytertc::RemoteStreamKey& key) override;

    virtual void OnStreamRemove(const bytertc::MediaStreamInfo& stream, bytertc::StreamRemoveReason reason) override;

    virtual void OnStreamAdd(const bytertc::MediaStreamInfo& stream) override;

    virtual void OnStreamSubscribed(bytertc::SubscribeState stateCode, const char *user_id, const bytertc::SubscribeConfig &info) override;

    virtual void OnStreamPublishSuccess(const char* user_id, bool is_screen) override;

    virtual void OnRoomMessageReceived(const char* uid, const char* message) override;
    
    virtual void OnRoomBinaryMessageReceived(const char* uid, int size, const uint8_t* message) override;
    
    virtual void OnUserMessageReceived(const char* uid, const char* message) override;
    
    virtual void OnUserBinaryMessageReceived(const char* uid, int size, const uint8_t* message) override;
    
    virtual void OnUserMessageSendResult(int64_t msgid, int error) override;
    
    virtual void OnRoomMessageSendResult(int64_t msgid, int error) override;

    virtual void OnLiveTranscodingResult(const char* url, int error) override;

    virtual void OnFirstLocalVideoFrameCaptured(bytertc::StreamIndex index, bytertc::VideoFrameInfo info) override;

    virtual void OnLocalVideoSizeChanged(bytertc::StreamIndex index, const bytertc::VideoFrameInfo& info) override;
    
    virtual void OnRemoteVideoSizeChanged(bytertc::RemoteStreamKey key, const bytertc::VideoFrameInfo& info) override;

    virtual void OnFirstRemoteVideoFrameRendered(const bytertc::RemoteStreamKey key, const bytertc::VideoFrameInfo& info) override;

    virtual void OnUserMuteVideo(const char* uid, bytertc::MuteState mute) override;

    virtual void OnUserEnableLocalVideo(const char* uid, bool enabled) override;

    virtual void OnVideoStreamBanned(const char* uid, bool banned) override;

    virtual void OnAudioStreamBanned(const char* uid, bool banned) override;

private:
    __weak id<ByteRTCRoomDelegate> _delegate;
    __weak ByteRTCRoom * _rtcRoom;
};
