//
//  ByteRtcRoom.h
//  ByteRtcEngineKitSrc
//
//  Created by sakura on 2020/3/18.
//

#import <CoreMedia/CMTime.h>
#import <UIKit/UIKit.h>
#import "ByteRtcEngineKitDefines.h"

@class ByteRtcRoom;

@protocol ByteRtcRoomDelegate <NSObject>
@optional

- (void)rtcRoom:(ByteRtcRoom *_Nonnull)rtcRoom
    didJoinRoom:(NSString *_Nonnull)roomId
        withUid:(NSString *_Nonnull)uid
        elapsed:(NSInteger)elapsed;

- (void)rtcRoom:(ByteRtcRoom *_Nonnull)rtcRoom
    didRejoinRoom:(NSString *_Nonnull)roomId
          withUid:(NSString *_Nonnull)uid
          elapsed:(NSInteger)elapsed;

- (void)rtcRoomDidLeaveRoom:(ByteRtcRoom *_Nonnull)rtcRoom withStats:(ByteRtcStats *_Nonnull)stats;

- (void)rtcRoom:(ByteRtcRoom *_Nonnull)rtcRoom didOccurWarning:(ByteRtcWarningCode)warningCode;

- (void)rtcRoom:(ByteRtcRoom *_Nonnull)rtcRoom didOccurError:(ByteRtcErrorCode)errorCode;

- (void)rtcRoom:(ByteRtcRoom *_Nonnull)rtcRoom
    audioQualityOfUid:(NSString *_Nonnull)uid
              quality:(ByteNetworkQuality)quality
                delay:(NSUInteger)delay
                 lost:(NSUInteger)lost;

- (void)rtcRoom:(ByteRtcRoom *_Nonnull)rtcRoom
    reportAudioVolumeIndicationOfSpeakers:(NSArray<ByteRtcAudioVolumeInfo *> *_Nonnull)speakers
                              totalVolume:(NSInteger)totalVolume;

- (void)rtcRoom:(ByteRtcRoom *_Nonnull)rtcRoom reportRtcStats:(ByteRtcStats *_Nonnull)stats;

- (void)rtcRoom:(ByteRtcRoom *_Nonnull)rtcRoom
    networkQuality:(NSString *_Nonnull)uid
         txQuality:(ByteNetworkQuality)txQuality
         rxQuality:(ByteNetworkQuality)rxQuality;

- (void)rtcRoom:(ByteRtcRoom *_Nonnull)rtcRoom didJoinedOfUid:(NSString *_Nonnull)uid elapsed:(NSInteger)elapsed;

- (void)rtcRoom:(ByteRtcRoom *_Nonnull)rtcRoom
    didOfflineOfUid:(NSString *_Nonnull)uid
             reason:(ByteRtcUserOfflineReason)reason;

- (void)rtcRoom:(ByteRtcRoom *_Nonnull)rtcRoom didAllRemoteAudioMuted:(BOOL)muted byUid:(NSString *_Nonnull)uid;

- (void)rtcRoom:(ByteRtcRoom *_Nonnull)rtcRoom didAllRemoteVideoMuted:(BOOL)muted byUid:(NSString *_Nonnull)uid;

- (void)rtcRoom:(ByteRtcRoom *_Nonnull)rtcRoom didAudioMuted:(BOOL)muted byUid:(NSString *_Nonnull)uid;

- (void)rtcRoom:(ByteRtcRoom *_Nonnull)rtcRoom didLocalAudioEnabled:(BOOL)enabled byUid:(NSString *_Nonnull)uid;

- (void)rtcRoom:(ByteRtcRoom *_Nonnull)rtcRoom localAudioStats:(ByteRtcLocalAudioStats *_Nonnull)stats;

- (void)rtcRoom:(ByteRtcRoom *_Nonnull)rtcRoom remoteAudioStats:(ByteRtcRemoteAudioStats *_Nonnull)stats;

- (void)rtcRoom:(ByteRtcRoom *_Nonnull)rtcRoom firstLocalAudioFrame:(NSInteger)elapsed;

- (void)rtcRoom:(ByteRtcRoom *_Nonnull)rtcRoom
    firstRemoteAudioFrameOfUid:(NSString *_Nonnull)uid
                       elapsed:(NSInteger)elapsed;

- (void)rtcRoom:(ByteRtcRoom *_Nonnull)rtcRoom onStreamAdd:(id<ByteStream> _Nonnull)stream;

- (void)rtcRoom:(ByteRtcRoom *_Nonnull)rtcRoom
    didStreamRemoved:(NSString *_Nonnull)uid
              stream:(id<ByteStream> _Nonnull)stream
              reason:(RtcStreamRemoveReason)reason;

- (void)rtcRoom:(ByteRtcRoom *_Nonnull)rtcRoom
    onStreamSubscribed:(SubscribeState)state
                userId:(NSString *_Nonnull)userId
       subscribeConfig:(SubscribeConfig *_Nonnull)info;

- (void)rtcRoom:(ByteRtcRoom *_Nonnull)rtcRoom didPublishSucceedOfStream:(NSString *_Nonnull)userId isScreen:(BOOL)isScreen;

- (void)rtcRoom:(ByteRtcRoom *_Nonnull)rtcRoom onRoomMessageReceived:(NSString *_Nonnull)uid
        message:(NSString *_Nonnull)message;

- (void)rtcRoom:(ByteRtcRoom *_Nonnull)rtcRoom onRoomBinaryMessageReceived:(NSString *_Nonnull)uid
        message:(NSData *_Nonnull)message;

- (void)rtcRoom:(ByteRtcRoom *_Nonnull)rtcRoom
    onUserMessageReceived:(NSString *_Nonnull)uid
               message:(NSString *_Nonnull)message;

- (void)rtcRoom:(ByteRtcRoom *_Nonnull)rtcRoom
    onUserBinaryMessageReceived:(NSString *_Nonnull)uid
               message:(NSData *_Nonnull)message;

- (void)rtcRoom:(ByteRtcRoom *_Nonnull)rtcRoom onUserMessageSendResult:(int64_t)msgid error:(UserMessageCode)error;

- (void)rtcRoom:(ByteRtcRoom *_Nonnull)rtcRoom onRoomMessageSendResult:(int64_t)msgid error:(RoomMessageCode)error;

- (void)rtcRoom:(ByteRtcRoom *_Nonnull)rtcRoom
    TransCodingWithUrl:(NSString *_Nonnull)url
             errorCode:(ByteRtcTransCodeingErrorCode)errorCode;

- (void)rtcRoom:(ByteRtcRoom *_Nonnull)rtcRoom firstLocalVideoFrameWithSize:(CGSize)size elapsed:(NSInteger)elapsed;

- (void)rtcRoom:(ByteRtcRoom *_Nonnull)rtcRoom
    firstRemoteVideoDecodedOfUid:(NSString *_Nonnull)uid
                            size:(CGSize)size
                         elapsed:(NSInteger)elapsed;

- (void)rtcRoom:(ByteRtcRoom *_Nonnull)rtcRoom
    videoSizeChangedOfUid:(NSString *_Nonnull)uid
                     size:(CGSize)size
                 rotation:(ByteVideoRotation)rotation;

- (void)rtcRoom:(ByteRtcRoom *_Nonnull)rtcRoom
    firstRemoteVideoFrameOfUid:(NSString *_Nonnull)uid
                          size:(CGSize)size
                       elapsed:(NSInteger)elapsed;

- (void)rtcRoom:(ByteRtcRoom *_Nonnull)rtcRoom
    firstRemoteScreenFrameOfUid:(NSString *_Nonnull)uid
                          size:(CGSize)size
                       elapsed:(NSInteger)elapsed;

- (void)rtcRoom:(ByteRtcRoom *_Nonnull)rtcRoom
    firstRemoteScreenDecodedOfUid:(NSString *_Nonnull)uid
                          size:(CGSize)size
                       elapsed:(NSInteger)elapsed;

- (void)rtcRoom:(ByteRtcRoom *_Nonnull)rtcRoom didVideoMuted:(BOOL)muted byUid:(NSString *_Nonnull)uid;

- (void)rtcRoom:(ByteRtcRoom *_Nonnull)rtcRoom didLocalVideoEnabled:(BOOL)enabled byUid:(NSString *_Nonnull)uid;

- (void)rtcRoom:(ByteRtcRoom *_Nonnull)rtcRoom localVideoStats:(ByteRtcLocalVideoStats *_Nonnull)stats;

- (void)rtcRoom:(ByteRtcRoom *_Nonnull)rtcRoom remoteVideoStats:(ByteRtcRemoteVideoStats *_Nonnull)stats;

- (void)rtcRoom:(ByteRtcRoom *_Nonnull)rtcRoom
    localAudioStateChanged:(ByteLocalAudioStreamState)state
                     error:(ByteLocalAudioStreamError)error;

- (void)rtcRoom:(ByteRtcRoom *_Nonnull)rtcRoom
    remoteAudioStateChanged:(NSString *_Nonnull)uid
                      state:(ByteRemoteAudioState)state
                     reason:(ByteRemoteAudioReason)reason
                    elapsed:(NSInteger)elapsed;

- (void)rtcRoom:(ByteRtcRoom *_Nonnull)rtcRoom
    localVideoStateChanged:(ByteLocalVideoStreamState)state
                     error:(ByteLocalVideoStreamError)error;

- (void)rtcRoom:(ByteRtcRoom *_Nonnull)rtcRoom
    remoteVideoStateChanged:(NSString *_Nonnull)uid
                      state:(ByteRemoteVideoState)state
                     reason:(ByteRemoteVideoReason)reason
                    elapsed:(NSInteger)elapsed;

- (void)rtcRoom:(ByteRtcRoom *_Nonnull)engine onAudioFrameSendStateChanged:(ByteRtcUser *_Nonnull)user state:(FirstFrameSendState)state;

- (void)rtcRoom:(ByteRtcRoom *_Nonnull)engine onVideoFrameSendStateChanged:(ByteRtcUser *_Nonnull)user state:(FirstFrameSendState)state;

- (void)rtcRoom:(ByteRtcRoom *_Nonnull)engine onScreenVideoFrameSendStateChanged:(ByteRtcUser *_Nonnull)user state:(FirstFrameSendState)state;

- (void)rtcRoom:(ByteRtcRoom *_Nonnull)engine onAudioFramePlayStateChanged:(ByteRtcUser *_Nonnull)user state:(FirstFramePlayState)state;

- (void)rtcRoom:(ByteRtcRoom *_Nonnull)engine onVideoFramePlayStateChanged:(ByteRtcUser *_Nonnull)user state:(FirstFramePlayState)state;

- (void)rtcRoom:(ByteRtcRoom *_Nonnull)engine onScreenVideoFramePlayStateChanged:(ByteRtcUser *_Nonnull)user state:(FirstFramePlayState)state;

@end

BYTE_RTC_EXPORT @interface ByteRtcRoom : NSObject @property(nonatomic, weak) id<ByteRtcRoomDelegate> _Nullable delegate;

#pragma mark - Core Methods

- (void)destroy;

- (NSString *_Nullable)getRoomId;

- (void)setRtcRoomDelegate:(id<ByteRtcRoomDelegate> _Nullable)roomDelegate;

- (int)joinRoomByToken:(NSString *_Nullable)token userId:(NSString *_Nullable)userId info:(NSString *_Nullable)info;

- (int)joinRoomByToken:(NSString *_Nullable)token
                userId:(NSString *_Nullable)userId
                  info:(NSString *_Nullable)info
               tracdId:(NSString *_Nullable)traceId;

- (int)setClientRole:(ByteRtcClientRole)role;

- (ByteRtcClientRole)clientRole;

- (int)setChannelProfile:(ByteChannelProfile)profile;

- (int)leaveRoom;

- (int)renewToken:(NSString *_Nullable)token;

- (int)publish;

- (int)unpublish;

- (int)publishScreen:(ScreenParam * _Nonnull)param;

- (int)unpublishScreen;

- (int)subscribeStream:(NSString *_Nonnull)userId subscribeConfig:(SubscribeConfig *_Nonnull)info;

- (int)unSubscribeStream:(NSString *_Nonnull)userId isScreen:(BOOL)isScreen;

- (int)enableAutoSubscribe:(ByteSubscribeMode)audioMode videoMode:(ByteSubscribeMode)videoMode;

- (int)enableAudioVolumeIndication:(NSInteger)interval smooth:(NSInteger)smooth;

- (int)muteAllRemoteAudioStreams;

- (int)unMuteAllRemoteAudioStreams;

- (int)setDefaultMuteAllRemoteAudioStreams:(BOOL)mute;

- (int)muteRemoteAudioStream:(NSString *_Nonnull)userId;

- (int)unMuteRemoteAudioStream:(NSString *_Nonnull)userId;

- (int)muteAllRemoteVideoStreams;

- (int)unMuteAllRemoteVideoStreams;

- (int)setDefaultMuteAllRemoteVideoStreams:(BOOL)mute;

- (int)muteRemoteVideoStream:(NSString *_Nonnull)userId;

- (int)unMuteRemoteVideoStream:(NSString *_Nonnull)userId;

- (int)enableLiveTranscoding:(ByteRtcLiveTranscoding *_Nonnull)transcoding;

- (int)disableLiveTranscoding;

- (int)setVideoCompositingLayout:(ByteRtcVideoCompositingLayout *_Nonnull)layout;

- (int)setupRemoteVideo:(ByteRtcVideoCanvas *_Nonnull)remote;

- (int)setupRemoteScreen:(ByteRtcVideoCanvas *_Nonnull)screen;

- (int)setRemoteVideoRenderer:(id<ByteVideoSinkProtocol> _Nullable)videoRenderer
                    forRoomId:(NSString * _Nonnull)roomId
                    forUserId:(NSString * _Nonnull)userId;

- (int)setRemoteScreenRenderer:(id<ByteVideoSinkProtocol> _Nullable)videoRenderer
                    forRoomId:(NSString * _Nonnull)roomId
                    forUserId:(NSString * _Nonnull)userId;

- (int64_t)sendUserMessage:(NSString *_Nonnull)userId message:(NSString *_Nonnull)message;

- (int64_t)sendUserBinaryMessage:(NSString * _Nonnull)uid message:(NSData * _Nonnull)message;

- (int64_t)sendRoomMessage:(NSString *_Nonnull)message;

- (int64_t)sendRoomBinaryMessage:(NSData *  _Nonnull)message;

@end
