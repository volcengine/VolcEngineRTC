#import "ByteRTCVideo.h"
#import "rtc/ByteRTCVideoDefinesEx.h"

@class ByteRTCVideoEx;
@class ByteRTCRoomEx;

@protocol ByteRTCVideoDelegateEx <NSObject>
@optional
- (void)rtcEngine:(ByteRTCVideo* _Nonnull)engine
        onAudioFrameSendStateChanged:(ByteRTCStreamKey* _Nonnull)streamKey
                            metaData:(NSString* _Nonnull)metaData
                               state:(ByteRTCFirstFrameSendState)state;
- (void)rtcEngine:(ByteRTCVideo* _Nonnull)engine
        onVideoFrameSendStateChanged:(ByteRTCStreamKey* _Nonnull)streamKey
                            metaData:(NSString* _Nonnull)metaData
                               state:(ByteRTCFirstFrameSendState)state;
- (void)rtcEngine:(ByteRTCVideo* _Nonnull)engine
        onAudioFramePlayStateChanged:(ByteRTCStreamKey* _Nonnull)streamKey
                            metaData:(NSString* _Nonnull)metaData
                               state:(ByteRTCFirstFramePlayState)state;
- (void)rtcEngine:(ByteRTCVideo* _Nonnull)engine
        onVideoFramePlayStateChanged:(ByteRTCStreamKey* _Nonnull)streamKey
                            metaData:(NSString* _Nonnull)metaData
                               state:(ByteRTCFirstFramePlayState)state;

- (void)rtcEngine:(ByteRTCVideo* _Nonnull)engine
        onLocalStreamStats:(ByteRTCStreamIndex)streamIndex
                     stats:(ByteRTCLocalStreamStats* _Nonnull)stats;
- (void)rtcEngine:(ByteRTCVideo* _Nonnull)engine
        onRemoteStreamStats:(ByteRTCStreamKey* _Nonnull)streamKey
                      stats:(ByteRTCRemoteStreamStats* _Nonnull)stats;
- (void)rtcEngine:(ByteRTCVideo* _Nonnull)engine
        onSimulcastSubscribeFallback:(ByteRTCStreamKey* _Nonnull)streamKey
                               event:(ByteRTCRemoteStreamSwitchEvent* _Nonnull)event;
- (void)rtcEngine:(ByteRTCVideo* _Nonnull)engine
        onPerformanceAlarms:(ByteRTCStreamIndex)streamIndex
                       mode:(ByteRTCPerformanceAlarmMode)mode
                     reason:(ByteRTCPerformanceAlarmReason)reason
           sourceWantedData:(ByteRTCSourceWantedData* _Nonnull)data;
@end

BYTERTC_APPLE_EXPORT @interface ByteRTCVideoEx : ByteRTCVideo

+ (ByteRTCVideoEx* _Nullable)createRTCVideoEx:(NSString* _Nonnull)appId
                                     delegate:(id<ByteRTCVideoDelegate> _Nullable)delegate
                                   delegateEx:(id<ByteRTCVideoDelegateEx> _Nullable)delegateEx
                                   parameters:(NSDictionary* _Nonnull)parameters;

+ (void)destroyRTCVideoEx NS_SWIFT_NAME(destroyRTCVideoEx());

- (ByteRTCRoomEx* _Nullable)createRTCRoomEx:(NSString* _Nonnull)roomId;

- (int)setVideoSource:(ByteRTCStreamIndex)streamIndex videoSourceConfig:(ByteRTCVideoSourceConfig* _Nonnull)config;

- (int)pushExternalVideoFrame:(ByteRTCStreamIndex)streamIndex videoFrame:(ByteRTCVideoFrame* _Nonnull)frame;

- (int)setLocalStreamPriority:(ByteRTCStreamIndex)streamIndex priority:(ByteRTCStreamPriority)priority;

- (int)setVideoCaptureConfig:(ByteRTCStreamIndex)streamIndex
               captureConfig:(ByteRTCVideoCaptureConfig* _Nullable)captureConfig;

#if BYTERTC_TARGET_MAC
- (int)startVideoCapture:(ByteRTCStreamIndex)streamIndex deviceId:(NSString* _Nonnull)deviceId;
#endif

- (int)stopVideoCapture:(ByteRTCStreamIndex)streamIndex;

- (int)setRemoteAudioPlaybackVolume:(ByteRTCStreamKey* _Nonnull)streamKey volume:(int)volume;

- (int)setCaptureVolume:(int)volume;

- (int)setScreenCaptureVolume:(int)volume;

- (int)setAudioSourceVolume:(ByteRTCStreamIndex)streamIndex volume:(int)volume;

- (int)setAudioContentType:(ByteRTCStreamIndex)streamIndex config:(ByteRTCAudioContentTypeConfig* _Nonnull)config;

- (int)setAudioEncodeConfig:(ByteRTCStreamIndex)streamIndex config:(ByteRTCAudioEncodeConfig* _Nonnull)config;

@end
