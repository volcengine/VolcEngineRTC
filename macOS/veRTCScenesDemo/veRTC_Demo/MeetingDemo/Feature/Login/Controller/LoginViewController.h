//
//  LoginViewController.h
//  SceneRTCDemo
//
//  Created by  on 2021/3/10.
//

#import <Cocoa/Cocoa.h>
#import "LoginModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface LoginViewController : NSViewController

@property (nonatomic, copy) NSString *appId;

@property (nonatomic, copy) void (^clickJoinRoomBlock)(LoginModel *loginModel, NSArray<RoomUserModel *> * _Nonnull userLists);

- (void)reStartPreview;

- (void)updateBottomBar:(LoginModel *)loginModel;

@end

NS_ASSUME_NONNULL_END
