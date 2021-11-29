//
//  LiveRtc.h
//

#ifndef LIVERTC_H_
#define LIVERTC_H_

#import "../rtc/ByteRTCEngineKit.h"

#define LIVE_RTC_EXPORT __attribute__((visibility("default")))

@class ByteRtcEngineKit;

typedef NS_ENUM(NSInteger, LIVERTC_MIX_TYPE) {
    LIVERTC_MIX_TYPE_SERVER = 0,
    LIVERTC_MIX_TYPE_CLIENT = 1,
    LIVERTC_MIX_TYPE_AUTO = 2,
    LIVERTC_MIX_TYPE_DISABLE = 3,
};

typedef NS_ENUM(NSInteger, LIVERTC_PARAMS_MODE) {
    LIVERTC_PARAMS_MODE_CLIENT = 0,
    LIVERTC_PARAMS_MODE_SERVER = 1,
    LIVERTC_PARAMS_MODE_DUALSTREAM = 2,
    LIVERTC_PARAMS_MODE_PK = 3,
};

typedef void (^LiveRtcVideoFrameCallBack)(NSString *_Nonnull uid, CVPixelBufferRef _Nonnull pixelBuffer, NSData *_Nullable extData, ByteRTCVideoRotation rotation);

LIVE_RTC_EXPORT @interface LiveRtcExtInfo : NSObject
@property (copy, nonatomic) NSString *_Nullable liveRtcAppId;
@property (copy, nonatomic) NSString *_Nullable liveRtcAppSign;
@property (copy, nonatomic) NSString *_Nullable liveRtcToken;
@property (copy, nonatomic) NSString *_Nullable liveRtcRoomId;
@property (copy, nonatomic) NSString *_Nullable liveRtcUserId;
@property (copy, nonatomic) NSString *_Nullable liveRtcVendorName;
@property (assign, nonatomic) NSInteger liveRtcVendorType; // 1:agora 2:zego 4:byte 8:twilio
@property (copy, nonatomic) NSString *_Nullable liveRtcbusinessID;

// Mix setting
@property (assign, nonatomic) LIVERTC_MIX_TYPE liveMixType;
@property (assign, nonatomic) NSInteger liveRtcMixBitrateKbps;
// video params setting
@property (assign, nonatomic) LIVERTC_PARAMS_MODE liveRtcParamMode;
@property (nonatomic, strong) ByteRTCVideoSolution *_Nullable liveRtcVideoInputParam;
@end

LIVE_RTC_EXPORT @interface LiveRtc : ByteRTCEngineKit
// mix params
@property (atomic, assign) LIVERTC_MIX_TYPE liveRtcExpectedMixType;
// A/V pipeline setting
@property (atomic, assign) BOOL isVideoExtSource;
@property (atomic, assign) BOOL isVideoExtRender;
@property (atomic, assign) BOOL isAudioExtSource;
@property (atomic, assign) BOOL isAudioExtRender;

// audio params setting
@property (nonatomic, assign) NSUInteger audioInputSampleRate;
@property (nonatomic, assign) NSUInteger audioInputChannelNum;
@property (nonatomic, assign) NSUInteger audioOutputSampleRate; // unused
@property (nonatomic, assign) NSUInteger audioOutputChannelNum;

- (instancetype _Nonnull)initLiveRtcWithAppId:(NSString *_Nonnull)liveRtcExtInfo
                                     delegate:(id<ByteRTCEngineDelegate> _Nullable)delegate
                              monitorDelegate:(id<ByteRTCMonitorDelegate> _Nullable)monitorDelegate
                                   parameters:(NSDictionary *_Nullable)parameters;
- (void)dealloc;
- (void)rtcExtInfoParse:(NSString *_Nonnull)rtcExtInfo;
- (LiveRtcExtInfo *_Nullable)rtcExtInfoObtain;
// update && config rtc paramters in room
- (void)rtcExtInfoRefresh:(NSString *_Nonnull)rtcExtInfo;
- (BOOL)configEngine;
- (int)joinChannel;
- (int)leaveChannel:(void (^_Nullable)(ByteRTCRoomStats *_Nullable stat))leaveChannelBlock;
- (BOOL)pushExternalVideoFrame:(CVPixelBufferRef _Nonnull)frame
                          time:(CMTime)pts
                      rotation:(ByteRTCVideoRotation)rotation
                  extendedData:(NSData *_Nullable)extendedData
             supplementaryInfo:(NSData *_Nullable)supplementaryInfo;

- (void)setVideoFrameCallBack:(LiveRtcVideoFrameCallBack _Nonnull)block userId:(NSString *_Nonnull)userId;
- (int)pushExternalAudioFrame:(void *_Nonnull)frame size:(int32_t)size timestamp:(NSTimeInterval)pts;
- (int)pullExternalAudioFrame:(void *_Nonnull)frame size:(int32_t)size;
// dualStream
- (int)dualStreamSubOfUid:(NSString *_Nonnull)userId streamID:(NSString *_Nonnull)streamID subVideo:(BOOL)videoFlag subAudio:(BOOL)audioFlag;
- (int)dualStreamUnsubOfUid:(NSString *_Nonnull)userId streamID:(NSString *_Nonnull)streamID subVideo:(BOOL)videoFlag subAudio:(BOOL)audioFlag;
- (ByteRTCVideoStreamState)setVideoProfiles:(NSArray<ByteRTCVideoSolution *> *_Nullable)videoStreamDescriptions orientationMode:(ByteRTCVideoOutputOrientationMode)mode;

@end

LIVE_RTC_EXPORT @interface LiveRtcSingleWrapper : NSObject

+ (NSString *_Nullable)getAppId:(NSString *_Nullable)params;
+ (LIVERTC_MIX_TYPE)getMixType:(NSString *_Nullable)rtcExtInfo;
+ (LiveRtc *_Nullable)sharedLiveRtcInstance:(NSString *_Nonnull)liveRtcExtInfo delegate:(id<ByteRTCEngineDelegate> _Nullable)delegate parameters:(NSDictionary *_Nullable)parameters ;
+ (void)destroyLiveRtc;
+ (void)setTTMonitorCallBack:(void (^_Nullable)(NSDictionary *_Nonnull data, NSString *_Nullable logType))callBack;
+ (void)setByteLog:(BOOL)isConsole
          callBack:(void (^_Nullable)(ByteRTCLogLevel leave,
                                      NSString *_Nonnull filename,
                                      NSString *_Nonnull tag,
                                      int line,
                                      NSString *_Nonnull funcName,
                                      NSString *_Nullable format))callBack;
@end

#undef LIVE_RTC_EXPORT

#endif // LIVERTC_H_
