//
//  ScreenBottomWindowController.h
//  SceneRTCDemo
//
//  Created by  on 2021/3/28.
//

#import <Cocoa/Cocoa.h>

NS_ASSUME_NONNULL_BEGIN

@interface ScreenBottomWindowController : NSWindowController

@property (nonatomic, strong) LoginModel *loginModel;

@property (nonatomic, strong) MeetingControlRoomModel *roomModel;

@end

NS_ASSUME_NONNULL_END
