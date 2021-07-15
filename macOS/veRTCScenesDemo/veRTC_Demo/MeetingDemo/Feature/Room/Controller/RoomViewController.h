//
//  RoomViewController.h
//  SceneRTCDemo
//
//  Created by  on 2021/3/10.
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

@property (nonatomic, strong) LoginModel *loginModel;

@property (nonatomic, strong) MeetingControlRoomModel *currentRoomModel;

@property (nonatomic, strong) NSMutableArray<RoomUserModel *> *userDataPool;

@property (nonatomic, weak) RoomUserModel *maxVolumeUserModel;

@property (nonatomic, copy) void (^clickHangUpBlock)(LoginModel *loginModel);

@property (nonatomic, copy) void (^updateNavBlock)(NSInteger meetingTime);

- (instancetype)initWithLoginModel:(LoginModel *)loginModel userLists:(NSArray<RoomUserModel *> *)userLists;

- (void)updateModeWithStatus:(RoomModeStatus)roomModeStatus;

- (void)updateRenderModeViewWithCameraStatus:(NSString *)uid enableCamera:(BOOL)isEnable;

- (void)updateRenderModeViewWithMicStatus:(NSString *)uid enableMic:(BOOL)isEnable;

- (void)updateRenderModeViewWithScreenStatus:(NSString *)uid enableScreen:(BOOL)isShare;

- (void)updateRenderModeViewWithHost:(NSString *)hostID;

- (void)addUser:(RoomUserModel *)roomUserModel;

- (void)removeUser:(NSString *)uid;

- (void)hangUpAction;

- (void)showEndView;

@end
