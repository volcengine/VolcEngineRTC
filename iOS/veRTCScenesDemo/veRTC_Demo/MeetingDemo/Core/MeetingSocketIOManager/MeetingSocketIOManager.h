//
//  MeetingSocketIOManager.h
//  SceneRTCDemo
//
//  Created by  on 2021/3/16.
//

#import <Foundation/Foundation.h>
#import "veRTC_Demo-Bridging-Header.h"

NS_ASSUME_NONNULL_BEGIN

static NSString *const NotificationMeetingControlChange = @"NotificationMeetingControlChange";
static NSString *const NotificationSocketStatusChange = @"NotificationSocketStatusChange";

@interface MeetingSocketIOManager : NSObject

@property (nonatomic, strong) SocketIOClient *socket;

/*
 * RTC Manager Singletons
 */
+ (MeetingSocketIOManager *_Nullable)shareSocketManager;

- (void)connectWithSdkVersion:(NSString *)sdkVersion block:(void (^)(BOOL relust))block;

- (void)connect;

- (void)disConnect;

@end

NS_ASSUME_NONNULL_END
