//
//  MeetingWindowController.m
//  SceneRTCDemo
//
//  Created by on 2021/3/2.
//

#import "MeetingWindowController.h"
#import "RoomViewController.h"
#import "LoginViewController.h"
#import "NavigationBarViewController.h"
#import "MeetingSocketIOManager.h"

#import "ScreenBottomWindowController.h"


@interface MeetingWindowController ()

@property (nonatomic, strong) NavigationBarViewController *navBarViewController;
@property (nonatomic, strong) LoginViewController *loginViewController;
@property (nonatomic, strong) RoomViewController *roomViewController;

@property (nonatomic, copy) NSString *currentAppID;

@end

@implementation MeetingWindowController

- (instancetype)initWithWindowNibName:(NSNibName)windowNibName {
    self = [super initWithWindowNibName:windowNibName];
    if (self) {
        NSString *sdkVersion = [[MeetingRTCManager shareMeetingRTCManager] getSdkVersion];
        [[MeetingSocketIOManager shareSocketManager] connectWithSdkVersion:sdkVersion block:^(BOOL relust) {
            if (relust) {
                [MeetingControlCompoments getAppIDWithUid:@"" roomId:@"" block:^(NSString * _Nonnull appID, MeetingControlAckModel * _Nonnull model) {
                    if (self.currentAppID.length <= 0) {
                        [[MeetingRTCManager shareMeetingRTCManager] createEngine:appID];
                        [self showNavBarVC];
                        [self showLoginVC:appID];
                        self.currentAppID = appID;
                    }
                }];
            }
        }];
    }
    return self;
}

- (void)windowDidLoad {
    [super windowDidLoad];
    
    [self.window.contentView setBackgroundColorWithHexString:@"#1D2129"];
    
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

- (void)hangUpAction:(LoginModel * _Nonnull)loginModel {
    [self dismissRoomVC];
    [self.navBarViewController updateUIWithStatus:NavigationBarStatusLogin];
    [self.loginViewController reStartPreview];
    [self.loginViewController updateBottomBar:loginModel];
}

- (void)joinRoomAction:(LoginModel *)loginModel {
    [[NSApplication sharedApplication].mainWindow makeFirstResponder:0];
    
    [[MeetingRTCManager shareMeetingRTCManager] stopPreview];
    [self showRoomVCWithModel:loginModel];
    [self.navBarViewController updateUIWithStatus:NavigationBarStatusRoom];
    self.navBarViewController.loginModel = loginModel;
}

#pragma mark - Room VC

- (void)showRoomVCWithModel:(LoginModel *)loginModel {
    self.loginViewController.view.hidden = YES;
    RoomViewController *roomViewController = [[RoomViewController alloc] initWithLoginModel:loginModel];
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
    self.loginViewController.view.hidden = NO;
    if (self.roomViewController) {
        [self.roomViewController.view removeFromSuperview];
        [self.roomViewController removeFromParentViewController];
        self.roomViewController = nil;
    }
}

#pragma mark - Login VC

- (void)showLoginVC:(NSString *)appId {
    [self.window.contentViewController addChildViewController:self.loginViewController];
    [self.window.contentView addSubview:self.loginViewController.view];
    self.loginViewController.appId = appId;
    [self.loginViewController.view mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.right.bottom.equalTo(self.window.contentView);
        make.top.equalTo(self.navBarViewController.view.mas_bottom);
    }];
    __weak __typeof(self) wself = self;
    self.loginViewController.clickJoinRoomBlock = ^(LoginModel * _Nonnull loginModel) {
        [wself joinRoomAction:loginModel];
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

- (LoginViewController *)loginViewController {
    if (!_loginViewController) {
        _loginViewController = [[LoginViewController alloc] init];
    }
    return _loginViewController;
}

- (NavigationBarViewController *)navBarViewController {
    if (!_navBarViewController) {
        _navBarViewController = [[NavigationBarViewController alloc] init];
    }
    return _navBarViewController;
}

@end
