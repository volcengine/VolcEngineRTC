/*
 * Copyright (c) 2020 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC Room Object
*/

#import <CoreMedia/CMTime.h>
#import <AppKit/AppKit.h>
#import "ByteRTCDefines.h"

@class ByteRTCRoom;

@protocol ByteRTCRoomDelegate <NSObject>
@optional

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom
    onJoinRoomResult:(NSString *_Nonnull)roomId
             withUid:(nonnull NSString *)uid
           errorCode:(NSInteger)errorCode
            joinType:(NSInteger)joinType
             elapsed:(NSInteger)elapsed;

- (void)onLeaveRoom:(ByteRTCRoom *_Nonnull)rtcRoom withStats:(ByteRTCRoomStats *_Nonnull)stats;

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onRoomWarning:(ByteRTCWarningCode)warningCode;

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onRoomError:(ByteRTCErrorCode)errorCode;

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom
    audioQualityOfUid:(NSString *_Nonnull)uid
              quality:(ByteRTCNetworkQuality)quality
                delay:(NSUInteger)delay
                 lost:(NSUInteger)lost;

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onAudioVolumeIndication:(NSArray<ByteRTCAudioVolumeInfo *> * _Nonnull)speakers totalRemoteVolume:(NSInteger)totalRemoteVolume;

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onRoomStats:(ByteRTCRoomStats *_Nonnull)stats;

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom
    networkQuality:(NSString *_Nonnull)uid
         txQuality:(ByteRTCNetworkQuality)txQuality
         rxQuality:(ByteRTCNetworkQuality)rxQuality;

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onLocalStreamStats:(ByteRTCLocalStreamStats *_Nonnull)stats;

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onRemoteStreamStats:(ByteRTCRemoteStreamStats *_Nonnull)stats;

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onUserJoined:(ByteRTCUserInfo *_Nonnull)userInfo elapsed:(NSInteger)elapsed;

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onUserLeave:(NSString *_Nonnull)uid reason:(ByteRTCUserOfflineReason)reason;

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onMuteAllRemoteAudio:(NSString * _Nonnull)uid muteState:(ByteRTCMuteState)muteState;

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom didAllRemoteVideoMuted:(BOOL)muted byUid:(NSString *_Nonnull)uid;

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onUserMuteAudio:(NSString * _Nonnull)uid muteState:(ByteRTCMuteState)muteState;

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom didLocalAudioEnabled:(BOOL)enabled byUid:(NSString *_Nonnull)uid;

- (void)rtcRoomConnectionDidLost:(ByteRTCRoom *_Nonnull)rtcRoom;

- (void)rtcRoomConnectionDidInterrupted:(ByteRTCRoom *_Nonnull)rtcRoom;

// todo: OnRequestToken, 未实现

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onFirstLocalAudioFrame:(ByteRTCStreamIndex) streamIndex;

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onFirstRemoteAudioFrame:(ByteRTCRemoteStreamKey * _Nonnull)key;

// todo: OnClientRoleChanged, 未实现

// todo: OnStreamPublished, 未实现

// todo: OnStreamUnpublished, 未实现

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onStreamAdd:(id<ByteRTCStream> _Nonnull)stream;

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom
    didStreamRemoved:(NSString *_Nonnull)uid
              stream:(id<ByteRTCStream> _Nonnull)stream
              reason:(VEStreamRemoveReason)reason;

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom
    onStreamSubscribed:(ByteRTCSubscribeState)state
                userId:(NSString *_Nonnull)userId
       subscribeConfig:(ByteRTCSubscribeConfig *_Nonnull)info;

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom OnStreamPublishSuccess:(NSString *_Nonnull)userId isScreen:(BOOL)isScreen;

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onRoomMessageReceived:(NSString *_Nonnull)uid
        message:(NSString *_Nonnull)message;

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onRoomBinaryMessageReceived:(NSString *_Nonnull)uid
        message:(NSData *_Nonnull)message;

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom
    onUserMessageReceived:(NSString *_Nonnull)uid
               message:(NSString *_Nonnull)message;

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom
    onUserBinaryMessageReceived:(NSString *_Nonnull)uid
               message:(NSData *_Nonnull)message;

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onUserMessageSendResult:(long)msgid error:(ByteRTCUserMessageSendResult)error;

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onRoomMessageSendResult:(long)msgid error:(ByteRTCUserMessageSendResult)error;

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom OnLiveTranscodingResult:(NSString *_Nonnull)url errorCode:(ByteRTCTranscodingError)errorCode;

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom firstLocalVideoFrameWithSize:(CGSize)size elapsed:(NSInteger)elapsed;

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom
    firstRemoteVideoDecodedOfUid:(NSString *_Nonnull)uid
                            size:(CGSize)size
                         elapsed:(NSInteger)elapsed;

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom videoSizeChangedOfUid:(NSString *_Nonnull)uid size:(CGSize)size rotation:(ByteRTCVideoRotation)rotation;

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom
    firstRemoteVideoFrameOfUid:(NSString *_Nonnull)uid
                          size:(CGSize)size
                       elapsed:(NSInteger)elapsed;

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom didVideoMuted:(BOOL)muted byUid:(NSString *_Nonnull)uid;

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom didLocalVideoEnabled:(BOOL)enabled byUid:(NSString *_Nonnull)uid;

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onVideoStreamBanned:(NSString *_Nonnull)uid isBanned:(BOOL)banned;

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onAudioStreamBanned:(NSString *_Nonnull)uid isBanned:(BOOL)banned;

@end

BYTERTC_APPLE_EXPORT @interface ByteRTCRoom : NSObject @property(nonatomic, weak) id<ByteRTCRoomDelegate> _Nullable delegate;

#pragma mark - Core Methods

- (void)setEngine:(id _Nullable)engine;

- (void)destroy;

- (NSString *_Nullable)getRoomId;

- (void)setRtcRoomDelegate:(id<ByteRTCRoomDelegate> _Nullable)roomDelegate;

- (int)joinRoomByToken:(NSString *_Nullable)token userInfo:(ByteRTCUserInfo *_Nonnull)userId roomProfile:(ByteRTCRoomProfile)roomProfile;

- (int)setUserRole:(ByteRTCUserRoleType)role;

- (ByteRTCUserRoleType)clientRole;

- (int)leaveRoom;

- (int)updateToken:(NSString *_Nonnull)token;

- (int)publish;

- (int)unpublish;

- (int)subscribeStream:(NSString *_Nonnull)userId subscribeConfig:(ByteRTCSubscribeConfig *_Nonnull)info;

- (int)unSubscribeStream:(NSString *_Nonnull)userId isScreen:(BOOL)isScreen;

- (BOOL)enableAutoSubscribe:(ByteRTCSubscribeMode)audioMode videoMode:(ByteRTCSubscribeMode)videoMode;

- (void)setAudioVolumeIndicationInterval:(NSInteger)interval;

- (void)muteAllRemoteAudio:(ByteRTCMuteState)muteState;

- (void)muteRemoteAudio:(NSString * _Nonnull)userId muteState:(ByteRTCMuteState)muteState;

- (int)muteAllRemoteVideoStreams;

- (int)unMuteAllRemoteVideoStreams;

- (int)muteRemoteVideoStream:(NSString *_Nonnull)userId;

- (int)unMuteRemoteVideoStream:(NSString *_Nonnull)userId;

- (int)startLiveTranscoding:(ByteRTCLiveTranscoding *_Nullable)transcoding;

- (int)stopLiveTranscoding;

- (int)updateLiveTranscodingLayout:(ByteRTCVideoCompositingLayout *_Nonnull)layout;

- (int)setupRemoteVideo:(ByteRTCVideoCanvas *_Nonnull)remote;

- (void)removeAllRemoteVideo;

- (int)setupRemoteScreen:(ByteRTCVideoCanvas *_Nonnull)screen;

- (void)removeAllRemoteScreen;

- (long)sendUserMessage:(NSString *_Nonnull)userId message:(NSString *_Nonnull)message;

- (long)sendUserBinaryMessage:(NSString * _Nonnull)uid message:(NSData * _Nonnull)message;

- (long)sendRoomMessage:(NSString *_Nonnull)message;

- (long)sendRoomBinaryMessage:(NSData *  _Nonnull)message;

- (int)setRemoteScreenRenderer:(id<ByteRTCVideoSinkProtocol> _Nullable)videoRenderer
                    forRoomId:(NSString * _Nonnull)roomId
                     forUserId:(NSString * _Nonnull)userId;

@end
