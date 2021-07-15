//
//  WindowManager.h
//  SceneRTCDemo
//
//  Created by  on 2021/3/2.
//

#import <Foundation/Foundation.h>
#import "LoginModel.h"
#import "MeetingControlRoomModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface WindowManager : NSObject

@property (nonatomic, copy) void(^onQuit)(void);

@property (nonatomic, strong) NSWindowController *currentWindowController;

- (void)start;

- (void)showScreenBottomWindowController:(LoginModel *)loginModel roomModel:(MeetingControlRoomModel *)roomModel;

- (void)showMeetingWindowController:(BOOL)isInitialize;

- (void)showEndWindowController:(LoginModel *)loginModel roomModel:(MeetingControlRoomModel *)roomModel;

- (void)closeEndWindowController;

- (void)showToastWindowController:(NSString *)message;

@end

NS_ASSUME_NONNULL_END
