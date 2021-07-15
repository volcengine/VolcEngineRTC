//
//  ParticipantViewController.h
//  SceneRTCDemo
//
//  Created by  on 2021/3/9.
//

#import <Cocoa/Cocoa.h>
#import "RoomUserModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface ParticipantViewController : NSView

@property (nonatomic, assign) BOOL isLoginHost;

@property (nonatomic, strong) LoginModel *loginModel;

@property (nonatomic, strong) NSArray<RoomUserModel *> *videoSessions;

@property (nonatomic, copy) void (^clickCancelBlock)(BOOL isEnable);

@end

NS_ASSUME_NONNULL_END
