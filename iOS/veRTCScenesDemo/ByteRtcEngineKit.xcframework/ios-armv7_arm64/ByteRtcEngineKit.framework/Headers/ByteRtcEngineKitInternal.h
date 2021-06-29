//
//  ByteRtcEngineKitInternal.h
//  ByteRtcEngineKit
//
//  Created by xiewei on 2018/7/26.
//  Copyright © 2018年 xiewei. All rights reserved.
//

#ifndef ByteRtcEngineKitInternal_h
#define ByteRtcEngineKitInternal_h

//#import "sdk/ios/ByteRtcEngineKit/ByteRtcEngineKitDefines.h"
//#import "sdk/objc/base/RTCVideoFrame.h"

@protocol ByteRtcEngineKitInternalEventDelegate <NSObject>
@optional
- (void) onPeerConnectionICEMux:(bool) muxed;
- (void) onSystemInfoLog:(double)appCpuUsage
           totalCpuUsage:(double)totalCpuUsage
          appMemeryUsage:(double)appMemeryUsage;
- (void) onSignalingAddrChanged:(NSString*_Nonnull)addr;
- (void) onConfigAddrChanged:(NSString*_Nonnull)addr;
- (void) onMediaServerAddrChanged:(NSString*_Nonnull)addr;
- (void) onChannelTypeChanged:(bool)isPreICE;
@end

@interface ByteRtcEngineKit()
@property (nonatomic, strong)  NSString *  _Nullable userAgentIP;
@property (nonatomic, strong)  NSString *  _Nullable signalServerAddr;
//@property (nonatomic, strong)  NSString *  _Nullable mediaServerAddr;
@property (nonatomic, strong)  NSString *  _Nullable trunkServerAddr;
@property (nonatomic, strong)  NSArray *   _Nullable  configHostsArray;
@property (nonatomic, strong)  NSString *  _Nullable  signalHost;
@property (nonatomic) BOOL isFirstConnect;//report joinroomsuccess while isFirstConnect is YES
@property (nonatomic) BOOL  enableRtcVideo;
@property (nonatomic) BOOL  enableRtcAudio;
// sdk developer used only

- (void)setDebugLogCallback:(void(^ _Nullable)(NSString* _Nullable log))logCallback
                 withFilter:(ByteRtcLogLevel)level;

- (void)enableSubscribeSelf:(BOOL)enable;
//- (void)enableSRTP:(BOOL)enable;

- (void)notifyErrorCode:(ByteRtcErrorCode)errorCode;

- (void)forceCrash:(int)type;

- (void)setInternalEventDelegate:(id<ByteRtcEngineKitInternalEventDelegate>_Nullable)delegate;

- (void)destroyRtcRoom:(NSString *_Nonnull)roomId;

//- (int)sendToVideoSink:(RTCVideoFrame * _Nonnull)frame consumer:(_Nullable id<ByteVideoFrameConsumerObserver>)consumer;

+ (NSString * _Nonnull)getGitCommit;
/**
 *  Get the version of ByteRTC SDK.
 *
 *  @return NSUInteger, sdk version
 */
+ (NSUInteger)getSdkVersionNum;
@end


#endif /* ByteRtcEngineKitInternal_h */

