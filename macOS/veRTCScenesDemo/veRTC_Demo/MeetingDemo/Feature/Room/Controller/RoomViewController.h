//
//  RoomViewController.h
//  SceneRTCDemo
//
//  Created by on 2021/3/10.
//

#import <Cocoa/Cocoa.h>
#import "LoginModel.h"
#import "RoomBottomBarView.h"
#import "NavigationBarViewController.h"
#import "ParticipantViewController.h"

typedef NS_ENUM(NSInteger, RoomModeStatus) {
    //Nine Palaces
    RoomModeStatusGallery,
    //Speaker
    RoomModeStatusSpaker,
};

@interface RoomViewController : NSViewController

@property (nonatomic, strong) RoomBottomBarView *roomBottomBarView;
@property (nonatomic, weak) ParticipantViewController *participantViewController;
@property (nonatomic, strong) LoginModel *loginModel;
@property (nonatomic, strong) MeetingControlRoomModel *currentRoomModel;
@property (nonatomic, copy) void (^clickHangUpBlock)(LoginModel *loginModel);

@property (nonatomic, copy) void (^updateNavBlock)(NSInteger meetingTime);

- (instancetype)initWithLoginModel:(LoginModel *)loginModel;

- (void)updateModeWithStatus:(RoomModeStatus)roomModeStatus;

- (void)updateRenderModeView;

- (void)updateRenderModeViewWithCameraStatus:(NSString *)uid enableCamera:(BOOL)isEnable;

- (void)updateRenderModeViewWithMicStatus:(NSString *)uid enableMic:(BOOL)isEnable;

- (void)updateRenderModeViewWithScreenStatus:(NSString *)uid enableScreen:(BOOL)isShare;

- (void)updateCurrentUserListHostStatus;

- (void)updateRenderModeViewUserRankeWithAudioVolume:(NSDictionary *)volumeInfo;

- (void)addUser:(RoomUserModel *)roomUserModel;

- (void)removeUser:(NSString *)uid;

- (void)hangUpAction;

- (void)showEndView;

@end
