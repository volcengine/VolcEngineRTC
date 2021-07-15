//
//  MeetingEndWindowController.h
//  SceneRTCDemo
//
//  Created by  on 2021/3/29.
//

#import <Cocoa/Cocoa.h>
#import "MeetingControlRoomModel.h"
#import "LoginModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface MeetingEndWindowController : NSWindowController

@property (nonatomic, strong) LoginModel *loginModel;

@property (nonatomic, strong) MeetingControlRoomModel *roomModel;

- (void)show;

@end

NS_ASSUME_NONNULL_END
