//
//  ParticipantViewController.h
//  SceneRTCDemo
//
//  Created by on 2021/3/9.
//

#import <Cocoa/Cocoa.h>
#import "RoomUserModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface ParticipantViewController : NSView

@property (nonatomic, assign) BOOL isLoginHost;

@property (nonatomic, strong) LoginModel *loginModel;

@property (nonatomic, copy) void (^clickCancelBlock)(BOOL isEnable);

- (void)updateUserMicStatus:(BOOL)isOpen uid:(NSString *)uid;

- (void)updateUserCameraStatus:(BOOL)isOpen uid:(NSString *)uid;

- (void)updateUserScreenStatus:(BOOL)isOpen uid:(NSString *)uid;

- (void)updateUserHostStatusWithUid:(NSString *)uid;

- (void)loadDataWithGetMeetingUserInfo;

- (void)updateUserMicStatus:(NSDictionary<NSString *,NSNumber *> *)speakUid;

@end

NS_ASSUME_NONNULL_END
