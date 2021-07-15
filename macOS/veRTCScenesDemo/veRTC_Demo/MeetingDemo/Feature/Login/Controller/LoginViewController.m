//
//  LoginViewController.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/10.
//

#import "LoginViewController.h"
#import "LoginBottonBarView.h"
#import "SetingViewController.h"
#import "FeedbackViewController.h"
#import "SystemAuthority.h"

@interface LoginViewController () <LoginBottonBarViewDelegate, SetingViewControllerDelegate>

@property (nonatomic, strong) NSImageView *closeVideoImageView;
@property (nonatomic, strong) NSView *videoPreview;
@property (nonatomic, strong) NSView *maskView;
@property (nonatomic, strong) LoginBottonBarView *loginBottonBarView;
@property (nonatomic, strong) SetingViewController *setingViewController;
@property (nonatomic, strong) FeedbackViewController *feedbackViewController;

@property (nonatomic, strong) LoginModel *loginModel;

@end

@implementation LoginViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    [self.view setBackgroundColorWithHexString:@"#1D2129"];
    [self updateLayoutViewFrame];

    [[MeetingRTCManager shareMeetingRTCManager] setVideoProfiles:[self getCacheSetingModel]];
    [[MeetingRTCManager shareMeetingRTCManager] startPreview:self.videoPreview];
    
    [self updateAuthorCameraWithBgImage];
}

- (void)viewDidAppear {
    [super viewDidAppear];
    
    [self.loginBottonBarView updateUserNameTextFile:[LocalUserCompoments userModel].name];
}

- (void)updateLayoutViewFrame {
    [self.view addSubview:self.videoPreview];
    [self.videoPreview mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(self.view);
    }];
    
    [self.view addSubview:self.maskView];
    [self.maskView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(self.view);
    }];
    
    [self.view addSubview:self.closeVideoImageView];
    [self.closeVideoImageView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerX.equalTo(self.view);
        make.centerY.equalTo(self.view).offset(-80);
        make.size.mas_equalTo(CGSizeMake(180, 180));
    }];
    
    [self.view addSubview:self.loginBottonBarView];
    [self.loginBottonBarView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(736, 80));
        make.bottom.mas_equalTo(-100);
        make.centerX.equalTo(self.view);
    }];
}

- (void)reStartPreview {
    dispatch_async(dispatch_get_main_queue(), ^{
        [[MeetingRTCManager shareMeetingRTCManager] startPreview:self.videoPreview];
        [self showFeedbackVC];
    });
}

#pragma mark - LoginBottonBarViewDelegate

- (void)loginBottonBarView:(LoginBottonBarView *)loginBottonBarView didSelectItemsAtStatus:(ButtonStatus)status clickButton:(nonnull TrackButton *)button {
    if (status == ButtonStatusSet) {
        [self showSetingVC];
    } else if (status == ButtonStatusMic) {
        button.isClose = !button.isClose;
    } else if (status == ButtonStatusVideo) {
        button.isClose = !button.isClose;
        if (button.isClose) {
            self.closeVideoImageView.hidden = NO;
            self.videoPreview.hidden = YES;
        } else {
            self.closeVideoImageView.hidden = YES;
            self.videoPreview.hidden = NO;
        }
    } else if (status == ButtonStatusStart) {
        if (IsEmptyStr(self.loginBottonBarView.roomId) || IsEmptyStr(self.loginBottonBarView.userName)) {
            return;
        }
        __block LoginModel *loginModel = [[LoginModel alloc] init];
        loginModel.isEnableVideo = self.loginBottonBarView.isEnableVideo;
        loginModel.isEnableAudio = self.loginBottonBarView.isEnableAudio;
        loginModel.roomId = self.loginBottonBarView.roomId;
        loginModel.name = self.loginBottonBarView.userName;
        loginModel.uid = [LocalUserCompoments userModel].uid;
        loginModel.token = @"";
        loginModel.appid = self.appId;
        
        __weak __typeof(self) wself = self;
        [MeetingControlCompoments joinMeeting:loginModel block:^(NSString * _Nonnull token, NSArray<RoomUserModel *> * _Nonnull userLists, MeetingControlAckModel * _Nonnull model) {
            if (model.result) {
                loginModel.token = token;
                if (wself.clickJoinRoomBlock) {
                    wself.clickJoinRoomBlock(loginModel, userLists);
                }
            } else {
                [[MeetingToastComponents shareMeetingToastComponents] showWithMessage:model.message];
            }
        }];
    }
}

#pragma mark - Publish Action

- (void)updateBottomBar:(LoginModel *)loginModel {
    [self.loginBottonBarView updateBottomBar:loginModel];
    if (!loginModel.isEnableVideo) {
        self.closeVideoImageView.hidden = NO;
        self.videoPreview.hidden = YES;
    } else {
        self.closeVideoImageView.hidden = YES;
        self.videoPreview.hidden = NO;
    }
}

#pragma mark - SetingViewControllerDelegate

- (void)setingViewController:(SetingViewController *)setingViewController cancelAction:(BOOL)isCancel {
    [self dismissSetingVC];
}

#pragma mark - Private Action

- (SetingModel *)getCacheSetingModel {
    NSData *data = [[NSUserDefaults standardUserDefaults] objectForKey:@"SetingModelCacheKey"];
    if (data == nil || ![data isKindOfClass:[NSData class]]) {
        SetingModel *setingModel = [[SetingModel alloc] init];
        [self userDefaultsSetModel:setingModel];
    }
    SetingModel *setingModel = [NSKeyedUnarchiver unarchiveObjectWithData:data];
    return setingModel;
}

- (void)userDefaultsSetModel:(id)model {
    NSError *error;
    NSData *data = nil;
    if (@available(macOS 10.13, *)) {
        data = [NSKeyedArchiver archivedDataWithRootObject:model requiringSecureCoding:NO error:&error];
    } else {
        data = [NSKeyedArchiver archivedDataWithRootObject:model];
    }
    if (data && !error) {
        [[NSUserDefaults standardUserDefaults] setValue:data forKey:@"SetingModelCacheKey"];
        [[NSUserDefaults standardUserDefaults] synchronize];
    }
}

- (void)updateAuthorCameraWithBgImage {
    [SystemAuthority authorCamera:^(BOOL granted) {
        self.closeVideoImageView.hidden = granted;
    }];
}

- (void)showSetingVC {
    [self addChildViewController:self.setingViewController];
    [self.view addSubview:self.setingViewController.view];
    [self.setingViewController.view mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(self.view);
    }];
}

- (void)dismissSetingVC {
    [self.setingViewController.view removeFromSuperview];
    [self.setingViewController removeFromParentViewController];
    self.setingViewController = nil;
}

- (void)showFeedbackVC {
    [self addChildViewController:self.feedbackViewController];
    [self.view addSubview:self.feedbackViewController.view];
    [self.feedbackViewController.view mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(self.view);
    }];
    __weak __typeof(self) wself = self;
    self.feedbackViewController.clickCancelBlock = ^{
        [wself dismissFeedbackVC];
    };
}

- (void)dismissFeedbackVC {
    [self.feedbackViewController.view removeFromSuperview];
    [self.feedbackViewController removeFromParentViewController];
    self.feedbackViewController = nil;
}

#pragma mark - getter

- (LoginBottonBarView *)loginBottonBarView {
    if (!_loginBottonBarView) {
        _loginBottonBarView = [[LoginBottonBarView alloc] init];
        _loginBottonBarView.wantsLayer = YES;
        _loginBottonBarView.layer.backgroundColor = [NSColor whiteColor].CGColor;
        _loginBottonBarView.layer.cornerRadius = 40;
        _loginBottonBarView.delegate = self;
    }
    return _loginBottonBarView;
}

- (SetingViewController *)setingViewController {
    if (!_setingViewController) {
        _setingViewController = [[SetingViewController alloc] init];
        _setingViewController.delegate = self;
    }
    return _setingViewController;
}

- (FeedbackViewController *)feedbackViewController {
    if (!_feedbackViewController) {
        _feedbackViewController = [[FeedbackViewController alloc] init];
    }
    return _feedbackViewController;
}

- (NSView *)videoPreview {
    if (!_videoPreview) {
        _videoPreview = [[NSView alloc] init];
    }
    return _videoPreview;
}

- (NSView *)maskView {
    if (!_maskView) {
        _maskView = [[NSView alloc] init];
        [_maskView setBackgroundColorWithHexString:@"000000" andAlpha:0.5 * 255];
    }
    return _maskView;
}

- (NSImageView *)closeVideoImageView {
    if (!_closeVideoImageView) {
        _closeVideoImageView = [[NSImageView alloc] init];
        [_closeVideoImageView setBackgroundColor:[NSColor clearColor]];
        _closeVideoImageView.image = [NSImage imageNamed:@"meeting_login_closevideo"];
        _closeVideoImageView.hidden = YES;
    }
    return _closeVideoImageView;
}




@end
