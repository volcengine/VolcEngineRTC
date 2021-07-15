//
//  VoiceSocketIOManager.h
//  SceneRTCDemo
//
//  Created by  on 2021/3/16.
//

#import <Foundation/Foundation.h>
#import "veRTC_Demo-Bridging-Header.h"

NS_ASSUME_NONNULL_BEGIN

static NSString *const NotificationVoiceControlChange = @"NotificationVoiceControlChange";

static NSString *const NotificationLoginExpired = @"NotificationLoginExpired";

//会控状态的链接，并不是socket的链接状态
//The link of the conference control state is not the link state of the socket
typedef NS_ENUM(NSInteger, VoiceConnectStatus) {
    VoiceConnectStatusNone = 0,
    VoiceConnectStatusSuccess,
    VoiceConnectStatusFailure,
    VoiceConnectStatusIng,
};

@interface VoiceSocketIOManager : NSObject

@property (nonatomic, strong) SocketIOClient *socket;

@property (nonatomic, assign) VoiceConnectStatus connectStatus;

/*
 * RTC Manager Singletons
 */
+ (VoiceSocketIOManager *_Nullable)shareSocketManager;

- (void)connectWithSdkVersion:(NSString *)sdkVersion block:(void (^)(BOOL relust))block;

- (void)disConnect;

- (NSString *)getDeviceId;

@end

NS_ASSUME_NONNULL_END
