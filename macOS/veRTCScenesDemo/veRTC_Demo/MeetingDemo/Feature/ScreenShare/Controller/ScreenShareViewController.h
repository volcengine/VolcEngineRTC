//
//  ScreenShareViewController.h
//  SceneRTCDemo
//
//  Created by  on 2021/3/10.
//

#import <Cocoa/Cocoa.h>

NS_ASSUME_NONNULL_BEGIN

@interface ScreenShareViewController : NSViewController

@property (nonatomic, strong) LoginModel *loginModel;
@property (nonatomic, strong) MeetingControlRoomModel *roomModel;

@property (nonatomic, copy) void (^clickCancelBlock)(void);

@end

NS_ASSUME_NONNULL_END
