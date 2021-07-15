//
//  MeetingWindowController.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/2.
//

#import "MeetingWindowController.h"
#import "RoomViewController.h"
#import "LoginViewController.h"
#import "NavigationBarViewController.h"
#import "MeetingSocketIOManager.h"
#import "ScreenBottomWindowController.h"


@interface MeetingWindowController ()

@property (nonatomic, strong) NavigationBarViewController *navBarViewController;
@property (nonatomic, strong) LoginViewController *meetingLoginViewController;
@property (nonatomic, strong) RoomViewController *roomViewController;

@property (nonatomic, copy) NSString *currentAppID;

@end

@implementation MeetingWindowController

- (instancetype)initWithWindowNibName:(NSNibName)windowNibName {
    self = [super initWithWindowNibName:windowNibName];
    if (self) {
        
    }
    return self;
}

- (void)windowDidLoad {
    [super windowDidLoad];
    [self.window.contentView setBackgroundColorWithHexString:@"#1D2129"];
}

- (void)show {
    [self getAppIDWithUid];
    [self showTestAlert];
}

#pragma mark - Publish Action

- (BOOL)isNeedClose {
    if (self.roomViewController) {
        return NO;
    } else {
        return YES;
    }
}

- (void)showEndView {
    [self.roomViewController showEndView];
}

#pragma mark - Private Action

- (void)getAppIDWithUid {
    __weak __typeof(self) wself = self;
    NSString *sdkVersion = [[MeetingRTCManager shareMeetingRTCManager] getSdkVersion];
    [[MeetingSocketIOManager shareSocketManager] connectWithSdkVersion:sdkVersion block:^(BOOL relust) {
        if (relust) {
            [MeetingControlCompoments getAppIDWithUid:@"" roomId:@"" block:^(NSString * _Nonnull appID, MeetingControlAckModel * _Nonnull model) {
                if (wself.currentAppID.length <= 0) {
                    [[MeetingRTCManager shareMeetingRTCManager] createEngine:appID];
                    [wself showNavBarVC];
                    [wself showLoginVC:appID];
                    wself.currentAppID = appID;
                }
            }];
        }
    }];
}

- (void)hangUpAction:(LoginModel * _Nonnull)loginModel {
    [self dismissRoomVC];
    [self.navBarViewController updateUIWithStatus:NavigationBarStatusLogin];
    [self.meetingLoginViewController reStartPreview];
    [self.meetingLoginViewController updateBottomBar:loginModel];
}

- (void)joinRoomAction:(LoginModel *)loginModel userLists:(NSArray<RoomUserModel *> *)userLists {
    [[NSApplication sharedApplication].mainWindow makeFirstResponder:0];
    
    [[MeetingRTCManager shareMeetingRTCManager] stopPreview];
    [self showRoomVCWithModel:loginModel userLists:userLists];
    [self.navBarViewController updateUIWithStatus:NavigationBarStatusRoom];
    self.navBarViewController.loginModel = loginModel;
}

#pragma mark - Room VC

- (void)showRoomVCWithModel:(LoginModel *)loginModel userLists:(NSArray<RoomUserModel *> *)userLists {
    self.meetingLoginViewController.view.hidden = YES;
    RoomViewController *roomViewController = [[RoomViewController alloc] initWithLoginModel:loginModel
                                                                                  userLists:userLists];
    self.roomViewController = roomViewController;
    [self.window.contentViewController addChildViewController:self.roomViewController];
    [self.window.contentView addSubview:self.roomViewController.view];
    [self.roomViewController.view mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.right.bottom.equalTo(self.window.contentView);
        make.top.equalTo(self.navBarViewController.view.mas_bottom);
    }];
    __weak __typeof(self) wself = self;
    self.roomViewController.clickHangUpBlock = ^(LoginModel * _Nonnull loginModel) {
        [wself hangUpAction:loginModel];
    };
    self.roomViewController.updateNavBlock = ^(NSInteger meetingTime) {
        wself.navBarViewController.meetingTime = meetingTime;
    };
}

- (void)dismissRoomVC {
    self.meetingLoginViewController.view.hidden = NO;
    if (self.roomViewController) {
        [self.roomViewController.view removeFromSuperview];
        [self.roomViewController removeFromParentViewController];
        self.roomViewController = nil;
    }
}

#pragma mark - Login VC

- (void)showLoginVC:(NSString *)appId {
    [self.window.contentViewController addChildViewController:self.meetingLoginViewController];
    [self.window.contentView addSubview:self.meetingLoginViewController.view];
    self.meetingLoginViewController.appId = appId;
    [self.meetingLoginViewController.view mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.right.bottom.equalTo(self.window.contentView);
        make.top.equalTo(self.navBarViewController.view.mas_bottom);
    }];
    __weak __typeof(self) wself = self;
    self.meetingLoginViewController.clickJoinRoomBlock = ^(LoginModel * _Nonnull loginModel, NSArray<RoomUserModel *> * _Nonnull userLists) {
        [wself joinRoomAction:loginModel userLists:userLists];
    };
}

#pragma mark - NavBar VC

- (void)showNavBarVC {
    [self.window.contentViewController addChildViewController:self.navBarViewController];
    [self.window.contentView addSubview:self.navBarViewController.view];
    [self.navBarViewController.view mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.top.right.equalTo(self.window.contentView);
        make.height.mas_equalTo(50);
    }];
}

#pragma mark - getter

- (LoginViewController *)meetingLoginViewController {
    if (!_meetingLoginViewController) {
        _meetingLoginViewController = [[LoginViewController alloc] init];
    }
    return _meetingLoginViewController;
}

- (NavigationBarViewController *)navBarViewController {
    if (!_navBarViewController) {
        _navBarViewController = [[NavigationBarViewController alloc] init];
    }
    return _navBarViewController;
}

- (void)showTestAlert {
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.5 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        NSAlert *alert = [NSAlert new];
        [alert addButtonWithTitle:@"确定"];
        [alert setMessageText:@"本产品仅用于功能体验，单次会议时长不超过10分钟"];
        [alert setAlertStyle:NSWarningAlertStyle];
        [alert runModal];
    });
}

@end
