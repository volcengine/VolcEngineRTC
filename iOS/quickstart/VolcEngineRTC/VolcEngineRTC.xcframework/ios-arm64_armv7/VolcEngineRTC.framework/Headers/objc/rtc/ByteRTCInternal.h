/*
 * Copyright (c) 2020 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngine Internal
*/

@protocol ByteRTCEngineKitInternalEventDelegate <NSObject>

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

@interface ByteRTCEngineKit()
@property (nonatomic, strong)  NSString *  _Nullable userAgentIP;
@property (nonatomic, strong)  NSString *  _Nullable signalServerAddr;
@property (nonatomic, strong)  NSString *  _Nullable trunkServerAddr;
@property (nonatomic, strong)  NSArray *   _Nullable  configHostsArray;
@property (nonatomic, strong)  NSString *  _Nullable  signalHost;
@property (nonatomic) BOOL isFirstConnect; //report joinroomsuccess while isFirstConnect is YES
@property (nonatomic) BOOL  enableRtcVideo;
@property (nonatomic) BOOL  enableRtcAudio;

// sdk developer used only
- (void)enableSubscribeSelf:(BOOL)enable;

- (void)notifyErrorCode:(ByteRTCErrorCode)errorCode;

- (void)forceCrash:(int)type;

- (void)setInternalEventDelegate:(id<ByteRTCEngineKitInternalEventDelegate>_Nullable)delegate;

- (void)destroyRtcRoom:(NSString *_Nonnull)roomId;

+ (NSString * _Nonnull)getGitCommit;
/**
 *  Get the version of Volc Engine SDK.
 *
 *  @return NSUInteger, sdk version
 */
+ (NSUInteger)getSdkVersionNum;

@end
