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

@interface MeetingSocketIOManager : NSObject

@property (nonatomic, strong) SocketIOClient *socket;

/*
 * RTC Manager Singleton
 */
+ (MeetingSocketIOManager *_Nullable)shareSocketManager;

- (void)connectWithSdkVersion:(NSString *)sdkVersion block:(void (^)(BOOL relust))block;

- (void)disConnect;

@end

NS_ASSUME_NONNULL_END
