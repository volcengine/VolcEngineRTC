//
//  WindowManager.h
//  SceneRTCDemo
//
//  Created by on 2021/3/2.
//

#import <Foundation/Foundation.h>
#import "LoginModel.h"
#import "MeetingControlRoomModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface WindowManager : NSObject

@property (nonatomic, copy) void(^onQuit)(void);

@property (nonatomic, strong) NSWindowController *currentWindowController;

- (void)start;
- (void)stop;
- (void)awake;
- (void)showPreference;

- (void)showScreenBottomWindowController:(LoginModel *)loginModel roomModel:(MeetingControlRoomModel *)roomModel;

- (void)showMeetingWindowController;

- (void)showEndWindowController:(LoginModel *)loginModel roomModel:(MeetingControlRoomModel *)roomModel;
- (void)closeEndWindowController;

- (void)showToastWindowController:(NSString *)message;

@end

NS_ASSUME_NONNULL_END
