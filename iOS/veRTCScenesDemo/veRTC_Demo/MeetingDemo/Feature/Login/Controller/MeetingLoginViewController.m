#import "SystemAuthority.h"
#import "SettingsService.h"
#import "MeetingLoginViewController.h"
#import "MeetingRTCManager.h"
#import "RoomViewController.h"
#import "FeedbackManager.h"
#import "RoomVideoSession.h"
#import "SettingViewController.h"
#import "MeetingSocketIOManager.h"

#define TEXTFIELD_MAX_LENGTH 18

@interface MeetingLoginViewController () <UITextFieldDelegate>
@property (nonatomic, strong) UIImageView *logoImageView;
@property (nonatomic, strong) BaseButton *enableAudioBtn;
@property (nonatomic, strong) BaseButton *enableVideoBtn;
@property (nonatomic, strong) UIButton *setingBtn;
@property (nonatomic, strong) UIButton *enterRoomBtn;
@property (nonatomic, strong) BaseButton *navLeftButton;
@property (nonatomic, strong) UITextField *roomIdTextField;
@property (nonatomic, strong) UITextField *userIdTextField;
@property (nonatomic, strong) UILabel *verLabel;
@property (nonatomic, strong) UIImageView *emptImageView;
@property (nonatomic, strong) UIView *videoView;
@property (nonatomic, strong) UIView *maskView;
@property (nonatomic, weak) FeedbackManager *feedbackManager;

@property (nonatomic, strong) UITapGestureRecognizer *tap;
@property (nonatomic, copy) NSString *currentAppid;

@end

@implementation MeetingLoginViewController
- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor blackColor];
    [self initUIComponents];
    [self authorizationStatusMicAndCamera];
    
    NSString *sdkVer = [[MeetingRTCManager shareRtc] getSdkVersion];
    NSString *appVer = [[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleShortVersionString"];
    self.verLabel.text = [NSString stringWithFormat:@"App版本 v%@ / SDK版本 v%@", appVer, sdkVer];
    self.userIdTextField.text = [LocalUserComponents userModel].name;
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyBoardDidShow:) name:UIKeyboardWillShowNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyBoardDidHide:) name:UIKeyboardWillHideNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(socketStatusChange:) name:NotificationSocketStatusChange object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(applicationBecomeActive) name:UIApplicationDidBecomeActiveNotification object:nil];
    
    __weak __typeof(self) wself = self;
    [[MeetingSocketIOManager shareSocketManager] connectWithSdkVersion:sdkVer block:^(BOOL relust) {
        if (relust) {
            if (wself.currentAppid.length <= 0) {
                [wself loadDataWithGetAppIDWithUid];
            }
        }
    }];
    
    [self applicationBecomeActive];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    [self.navigationController setNavigationBarHidden:YES animated:NO];
    [UIApplication sharedApplication].statusBarStyle = UIStatusBarStyleLightContent;
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    if (self.currentAppid.length > 0) {
        [[MeetingRTCManager shareRtc] updateRtcVideoParams];
        [[MeetingRTCManager shareRtc] startPreview:self.videoView];
    }
}

#pragma mark - 通知

- (void)applicationBecomeActive {
    UIViewController *topVC = [DeviceInforTool topViewController];
    if ([topVC isKindOfClass:[MeetingLoginViewController class]]) {
        AlertActionModel *alertModel = [[AlertActionModel alloc] init];
        alertModel.title = @"确定";
        [[AlertActionManager shareAlertActionManager] showWithMessage:@"本产品仅用于功能体验，单次会议时长不超过10分钟"
                                                              actions:@[alertModel]];
    }
}

- (void)keyBoardDidShow:(NSNotification *)notifiction {
    CGRect keyboardRect = [[notifiction.userInfo objectForKey:UIKeyboardFrameEndUserInfoKey] CGRectValue];
    [UIView animateWithDuration:0.25 animations:^{
        [self.enterRoomBtn mas_updateConstraints:^(MASConstraintMaker *make) {
            make.bottom.equalTo(self.view).offset(-keyboardRect.size.height - 80/2);
        }];
    }];
    self.emptImageView.hidden = YES;
    [self.view layoutIfNeeded];
}

- (void)keyBoardDidHide:(NSNotification *)notifiction {
    [UIView animateWithDuration:0.25 animations:^{
        [self.enterRoomBtn mas_updateConstraints:^(MASConstraintMaker *make) {
            make.bottom.equalTo(self.view).offset(-288/2 - [DeviceInforTool getVirtualHomeHeight]);
        }];
    }];
    self.emptImageView.hidden = (self.enableVideoBtn.status == ButtonStatusNone);
    [self.view layoutIfNeeded];
}

- (void)socketStatusChange:(NSNotification *)notifiction {

}

#pragma mark - Action Method

- (void)tapGestureAction:(id)sender {
    [self.roomIdTextField resignFirstResponder];
    [self.userIdTextField resignFirstResponder];
}

- (void)onClickEnterRoom:(UIButton *)sender {
    if (self.roomIdTextField.text.length <= 0) {
        return;
    }
    if (self.userIdTextField.text.length <= 0) {
        return;
    }
    BOOL checkRoomId = ![LocalUserComponents isMatchRoomID:self.roomIdTextField.text];
    if (checkRoomId) {
        return;
    }
    
    __block RoomVideoSession *roomVideoSession = [[RoomVideoSession alloc] initWithUid:[LocalUserComponents userModel].uid];
    roomVideoSession.name = self.userIdTextField.text;
    roomVideoSession.appid = self.currentAppid;
    roomVideoSession.roomId = self.roomIdTextField.text;
    roomVideoSession.isLoginUser = YES;
    roomVideoSession.isEnableAudio = self.enableAudioBtn.status == ButtonStatusNone;
    roomVideoSession.isEnableVideo = self.enableVideoBtn.status == ButtonStatusNone;
    roomVideoSession.isHost = NO;
    roomVideoSession.isScreen = NO;
    
    sender.userInteractionEnabled = NO;
    __weak __typeof(self) wself = self;
    [MeetingControlCompoments joinMeeting:roomVideoSession block:^(NSString * _Nonnull token, NSArray<RoomVideoSession *> * _Nonnull userLists, MeetingControlAckModel * _Nonnull model) {
        if (model.result) {
            roomVideoSession.token = token;
            [wself jumpToRoomVC:roomVideoSession userLists:userLists];
        } else {
            AlertActionModel *alertModel = [[AlertActionModel alloc] init];
            alertModel.title = @"确定";
            [[AlertActionManager shareAlertActionManager] showWithMessage:model.message actions:@[alertModel]];
        }
        sender.userInteractionEnabled = YES;
    }];
}

- (void)jumpToRoomVC:(RoomVideoSession *)localSession userLists:(NSArray<RoomVideoSession *> *)userLists {
    RoomViewController *roomVC = [[RoomViewController alloc] initWithVideoSession:localSession userLists:userLists];
    UINavigationController *navController = [[UINavigationController alloc] initWithRootViewController:roomVC];
    navController.modalPresentationStyle = UIModalPresentationFullScreen;
    [self presentViewController:navController animated:YES completion:nil];
    __weak __typeof(self) wself = self;
    roomVC.closeRoomBlock = ^(BOOL isEnableAudio, BOOL isEnableVideo) {
        [wself closeRoomAction:isEnableAudio isEnableVideo:isEnableVideo];
    };
}

- (void)onClickEnableAudio:(BaseButton *)sender {
    if (sender.status != ButtonStatusIllegal) {
        sender.status = (sender.status == ButtonStatusActive) ? ButtonStatusNone : ButtonStatusActive;
    } else {
        AlertActionModel *alertCancelModel = [[AlertActionModel alloc] init];
        alertCancelModel.title = @"取消";
        AlertActionModel *alertModel = [[AlertActionModel alloc] init];
        alertModel.title = @"确定";
        alertModel.alertModelClickBlock = ^(UIAlertAction * _Nonnull action) {
            if ([action.title isEqualToString:@"确定"]) {
                [SystemAuthority autoJumpWithAuthorizationStatusWithType:AuthorizationTypeAudio];
            }
        };
        [[AlertActionManager shareAlertActionManager] showWithMessage:@"麦克风权限已关闭，请至设备设置页开启" actions:@[alertCancelModel, alertModel]];
    }
}

- (void)onClickEnableVideo:(BaseButton *)sender {
    if (sender.status != ButtonStatusIllegal) {
        sender.status = (sender.status == ButtonStatusActive) ? ButtonStatusNone : ButtonStatusActive;
        BOOL isEnableVideo = (sender.status == ButtonStatusActive) ? NO : YES;
        self.videoView.hidden = !isEnableVideo;
        self.emptImageView.hidden = isEnableVideo;
    } else {
        AlertActionModel *alertCancelModel = [[AlertActionModel alloc] init];
        alertCancelModel.title = @"取消";
        AlertActionModel *alertModel = [[AlertActionModel alloc] init];
        alertModel.title = @"确定";
        alertModel.alertModelClickBlock = ^(UIAlertAction * _Nonnull action) {
            if ([action.title isEqualToString:@"确定"]) {
                [SystemAuthority autoJumpWithAuthorizationStatusWithType:AuthorizationTypeCamera];
            }
        };
        [[AlertActionManager shareAlertActionManager] showWithMessage:@"摄像头权限已关闭，请至设备设置页开启" actions:@[alertCancelModel, alertModel]];
    }
}

- (void)onClickSet:(id)sender {
    SettingViewController *settingsVC = [[SettingViewController alloc] init];
    [self.navigationController pushViewController:settingsVC animated:YES];
}

- (void)navBackAction:(BaseButton *)sender {
    [self.navigationController popViewControllerAnimated:YES];
}

#pragma mark - UITextField delegate

- (void)roomNumTextFieldChange:(UITextField *)textField {
    [self updateTextFieldChange:textField];
}

- (void)updateTextFieldChange:(UITextField *)textField {
    NSInteger tagNum = (self.roomIdTextField == textField) ? 3001 : 3002;
    UILabel *label = [self.view viewWithTag:tagNum];
    
    NSString *message = @"";
    BOOL isExceedMaximLength = NO;
    if (textField.text.length > TEXTFIELD_MAX_LENGTH) {
        textField.text = [textField.text substringToIndex:TEXTFIELD_MAX_LENGTH];
        isExceedMaximLength = YES;
    }
    
    [NSObject cancelPreviousPerformRequestsWithTarget:self selector:@selector(dismissErrorLabel:) object:textField];
    BOOL isIllegal = NO;
    if (self.userIdTextField == textField) {
        isIllegal = ![LocalUserComponents isMatchUserName:textField.text];;
    }
    if (self.roomIdTextField == textField) {
        isIllegal = ![LocalUserComponents isMatchRoomID:textField.text];
    }
    if (isIllegal || isExceedMaximLength) {
        if (isIllegal) {
            message = @"请输入数字、英文字母或符号@_-";
            if (self.userIdTextField == textField) {
                message = @"仅支持中文、字母、数字，1-18位";
            }
        } else if (isExceedMaximLength) {
            [self performSelector:@selector(dismissErrorLabel:) withObject:textField afterDelay:2];
            message = @"输入长度不能超过18位";
        } else {
            message = @"";
        }
        [self updateEnterRoomButtonColor:NO];
    } else {
        BOOL isEnterEnable = self.roomIdTextField.text.length > 0 && self.userIdTextField.text.length > 0;
        [self updateEnterRoomButtonColor:isEnterEnable];
        message = @"";
    }
    label.text = message;
}

- (void)dismissErrorLabel:(UITextField *)textField {
    NSInteger tagNum = (self.roomIdTextField == textField) ? 3001 : 3002;
    UILabel *label = [self.view viewWithTag:tagNum];
    label.text = @"";
}

#pragma mark - Private Action

- (void)loadDataWithGetAppIDWithUid {
    __weak __typeof(self) wself = self;
    [MeetingControlCompoments getAppIDWithUid:@"" roomId:@"" block:^(NSString * _Nonnull appID, MeetingControlAckModel * _Nonnull model) {
        if (model.result) {
            wself.currentAppid = appID;
            [[MeetingRTCManager shareRtc] createEngine:appID];
            [[MeetingRTCManager shareRtc] updateRtcVideoParams];
            [[MeetingRTCManager shareRtc] startPreview:wself.videoView];
        } else {
            AlertActionModel *alertModel = [[AlertActionModel alloc] init];
            alertModel.title = @"重试";
            alertModel.alertModelClickBlock = ^(UIAlertAction * _Nonnull action) {
                if ([action.title isEqualToString:@"重试"]) {
                    [wself loadDataWithGetAppIDWithUid];
                }
            };
            [[AlertActionManager shareAlertActionManager] showWithMessage:model.message actions:@[alertModel]];
        }
    }];
}

- (void)updateButtonColor:(UIButton *)button {
    [button setImageEdgeInsets:UIEdgeInsetsMake(11, 11, 11, 11)];
    button.imageView.contentMode = UIViewContentModeScaleAspectFit;
    button.backgroundColor = [UIColor colorWithWhite:1 alpha:0.1];
    button.layer.masksToBounds = YES;
    button.layer.cornerRadius = 44/2;
}

- (void)updateEnterRoomButtonColor:(BOOL)isEnable {
    if (isEnable) {
        self.enterRoomBtn.layer.borderColor = [UIColor colorFromHexString:@"#C9CDD4"].CGColor;
        [self.enterRoomBtn setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    } else {
        self.enterRoomBtn.layer.borderColor = [UIColor colorFromHexString:@"#4E5969"].CGColor;
        [self.enterRoomBtn setTitleColor:[UIColor colorFromHexString:@"#86909C"] forState:UIControlStateNormal];
    }
}

- (void)addLineView:(UIView *)view {
    UIView *lineView = [[UIView alloc] init];
    lineView.backgroundColor = [UIColor colorFromHexString:@"#4E5969"];
    [self.view addSubview:lineView];
    [lineView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(630/2, XH_1PX_WIDTH));
        make.centerX.equalTo(self.view);
        make.top.mas_equalTo(view.mas_bottom).offset(0);
    }];
}

- (void)addErrorLabel:(UIView *)view tag:(NSInteger)tag {
    UILabel *label = [[UILabel alloc] init];
    label.tag = tag;
    label.text = @"";
    label.textColor = [UIColor colorFromHexString:@"#F53F3F"];
    [self.view addSubview:label];
    [label mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.equalTo(view);
        make.top.mas_equalTo(view.mas_bottom).offset(4);
    }];
}

- (void)initUIComponents {
    [self.view addSubview:self.videoView];
    [self.videoView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(self.view);
    }];
    
    [self.view addSubview:self.maskView];
    [self.maskView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(self.view);
    }];
    
    [self.view addSubview:self.logoImageView];
    [self.logoImageView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(262/2, 50/2));
        make.centerX.equalTo(self.view);
        make.top.mas_equalTo(128/2 + [DeviceInforTool getStatusBarHight]);
    }];
    
    [self.view addSubview:self.emptImageView];
    [self.emptImageView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.width.height.mas_equalTo(120);
        make.centerX.equalTo(self.view);
        make.top.mas_equalTo(self.logoImageView.mas_bottom).offset(50);
    }];
    
    [self.maskView addGestureRecognizer:self.tap];
    
    [self.view addSubview:self.enableAudioBtn];
    [self.enableAudioBtn mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(44, 44));
        make.left.mas_equalTo(123/2);
        make.bottom.mas_equalTo(-120/2 - [DeviceInforTool getVirtualHomeHeight]);
    }];
    
    [self.view addSubview:self.enableVideoBtn];
    [self.enableVideoBtn mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(44, 44));
        make.centerX.equalTo(self.view);
        make.bottom.mas_equalTo(-120/2 - [DeviceInforTool getVirtualHomeHeight]);
    }];
    
    [self.view addSubview:self.setingBtn];
    [self.setingBtn mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(44, 44));
        make.right.mas_equalTo(-123/2);
        make.bottom.mas_equalTo(-120/2 - [DeviceInforTool getVirtualHomeHeight]);
    }];
    
    [self.view addSubview:self.enterRoomBtn];
    [self.enterRoomBtn mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(630/2, 100/2));
        make.centerX.equalTo(self.view);
        make.bottom.equalTo(self.view).offset(-288/2 - [DeviceInforTool getVirtualHomeHeight]);
    }];
    
    [self.view addSubview:self.userIdTextField];
    [self.userIdTextField mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(630/2, (40 + 46)/2));
        make.centerX.equalTo(self.view);
        make.bottom.equalTo(self.enterRoomBtn.mas_top).offset(-104/2);
    }];
    
    [self.view addSubview:self.roomIdTextField];
    [self.roomIdTextField mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(630/2, (40 + 46)/2));
        make.centerX.equalTo(self.view);
        make.bottom.equalTo(self.userIdTextField.mas_top).offset(-88/2);
    }];
    
    [self.view addSubview:self.verLabel];
    [self.verLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerX.equalTo(self.view);
        make.bottom.equalTo(self.view).offset(-([DeviceInforTool getVirtualHomeHeight] + 20));
    }];
    
    [self.view addSubview:self.navLeftButton];
    [self.navLeftButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.height.width.mas_equalTo(16);
        make.left.mas_equalTo(16);
        make.top.equalTo(self.view).offset([DeviceInforTool getStatusBarHight] + 16);
    }];
    
    [self addLineView:self.userIdTextField];
    [self addLineView:self.roomIdTextField];
    
    [self addErrorLabel:self.roomIdTextField tag:3001];
    [self addErrorLabel:self.userIdTextField tag:3002];
}

- (void)closeRoomAction:(BOOL)isEnableAudio isEnableVideo:(BOOL)isEnableVideo {
    if (!self.feedbackManager) {
        __block FeedbackManager *feedbackManager = [[FeedbackManager alloc] init];
        self.feedbackManager = feedbackManager;
        [feedbackManager show];
        feedbackManager.clickCancelBlock = ^{
            feedbackManager = nil;
        };
    }
    [self.videoView setHidden:!isEnableVideo];
    self.emptImageView.hidden = isEnableVideo;
    self.enableVideoBtn.status = isEnableVideo ? ButtonStatusNone : ButtonStatusActive;
    self.enableAudioBtn.status = !isEnableAudio ? ButtonStatusActive : ButtonStatusNone;
    [self authorizationStatusMicAndCamera];
}

- (void)authorizationStatusMicAndCamera {
    [SystemAuthority authorizationStatusWithType:AuthorizationTypeAudio block:^(BOOL isAuthorize) {
        if (!isAuthorize) {
            self.enableAudioBtn.status = ButtonStatusIllegal;
        }
    }];
    
    [SystemAuthority authorizationStatusWithType:AuthorizationTypeCamera block:^(BOOL isAuthorize) {
        if (!isAuthorize) {
            self.emptImageView.hidden = NO;
            self.enableVideoBtn.status = ButtonStatusIllegal;
        }
    }];
}

#pragma mark - getter

- (UITextField *)roomIdTextField {
    if (!_roomIdTextField) {
        _roomIdTextField = [[UITextField alloc] init];
        _roomIdTextField.delegate = self;
        [_roomIdTextField setBackgroundColor:[UIColor clearColor]];
        [_roomIdTextField setTextColor:[UIColor whiteColor]];
        _roomIdTextField.font = [UIFont systemFontOfSize:16 weight:UIFontWeightRegular];
        [_roomIdTextField addTarget:self action:@selector(roomNumTextFieldChange:) forControlEvents:UIControlEventEditingChanged];
        NSAttributedString *attrString = [[NSAttributedString alloc] initWithString:@"请输入房间ID"
                                                                         attributes:
                                                                             @{NSForegroundColorAttributeName : [UIColor colorFromHexString:@"#86909C"]}];
        _roomIdTextField.attributedPlaceholder = attrString;
    }
    return _roomIdTextField;
}

- (UITextField *)userIdTextField {
    if (!_userIdTextField) {
        _userIdTextField = [[UITextField alloc] init];
        _userIdTextField.delegate = self;
        [_userIdTextField setBackgroundColor:[UIColor clearColor]];
        [_userIdTextField setTextColor:[UIColor whiteColor]];
        _userIdTextField.font = [UIFont systemFontOfSize:16 weight:UIFontWeightRegular];
        [_userIdTextField addTarget:self action:@selector(roomNumTextFieldChange:) forControlEvents:UIControlEventEditingChanged];
        NSAttributedString *attrString = [[NSAttributedString alloc] initWithString:@"请输入用户昵称"
                                                                         attributes:
                                                                             @{NSForegroundColorAttributeName : [UIColor colorFromHexString:@"#86909C"]}];
        _userIdTextField.attributedPlaceholder = attrString;
    }
    return _userIdTextField;
}

- (BaseButton *)enableAudioBtn {
    if (!_enableAudioBtn) {
        _enableAudioBtn = [[BaseButton alloc] init];
        [_enableAudioBtn bingImage:[UIImage imageNamed:@"meeting_room_mic"] status:ButtonStatusNone];
        [_enableAudioBtn bingImage:[UIImage imageNamed:@"meeting_room_mic_s"] status:ButtonStatusActive];
        [_enableAudioBtn bingImage:[UIImage imageNamed:@"meeting_room_mic_s"] status:ButtonStatusIllegal];
        [_enableAudioBtn addTarget:self action:@selector(onClickEnableAudio:) forControlEvents:UIControlEventTouchUpInside];
        [self updateButtonColor:_enableAudioBtn];
    }
    return _enableAudioBtn;
}

- (BaseButton *)enableVideoBtn {
    if (!_enableVideoBtn) {
        _enableVideoBtn = [[BaseButton alloc] init];
        [_enableVideoBtn bingImage:[UIImage imageNamed:@"meeting_login_video"] status:ButtonStatusNone];
        [_enableVideoBtn bingImage:[UIImage imageNamed:@"meeting_room_video_s"] status:ButtonStatusActive];
        [_enableVideoBtn bingImage:[UIImage imageNamed:@"meeting_room_video_s"] status:ButtonStatusIllegal];
        [_enableVideoBtn addTarget:self action:@selector(onClickEnableVideo:) forControlEvents:UIControlEventTouchUpInside];
        [self updateButtonColor:_enableVideoBtn];
    }
    return _enableVideoBtn;
}

- (UIButton *)setingBtn {
    if (!_setingBtn) {
        _setingBtn = [[UIButton alloc] init];
        [_setingBtn setImage:[UIImage imageNamed:@"meeting_login_set"] forState:UIControlStateNormal];
        [_setingBtn addTarget:self action:@selector(onClickSet:) forControlEvents:UIControlEventTouchUpInside];
        [self updateButtonColor:_setingBtn];
    }
    return _setingBtn;
}

- (UIButton *)enterRoomBtn {
    if (!_enterRoomBtn) {
        _enterRoomBtn = [[UIButton alloc] init];
        _enterRoomBtn.backgroundColor = [UIColor clearColor];
        _enterRoomBtn.layer.masksToBounds = YES;
        _enterRoomBtn.layer.cornerRadius = 50/2;
        _enterRoomBtn.layer.borderWidth = XH_1PX_WIDTH;
        [_enterRoomBtn setTitle:@"进入房间" forState:UIControlStateNormal];
        _enterRoomBtn.titleLabel.font = [UIFont systemFontOfSize:16 weight:UIFontWeightRegular];
        [_enterRoomBtn addTarget:self action:@selector(onClickEnterRoom:) forControlEvents:UIControlEventTouchUpInside];
        [self updateEnterRoomButtonColor:NO];
    }
    return _enterRoomBtn;
}

- (UIView *)videoView {
    if (!_videoView) {
        _videoView = [[UIView alloc] init];
    }
    return _videoView;
}

- (UIImageView *)logoImageView {
    if (!_logoImageView) {
        _logoImageView = [[UIImageView alloc] init];
        _logoImageView.image = [UIImage imageNamed:@"meeting_login_icon"];
        _logoImageView.contentMode = UIViewContentModeScaleAspectFit;
    }
    return _logoImageView;
}

- (UITapGestureRecognizer *)tap {
    if (!_tap) {
        _tap = [[UITapGestureRecognizer alloc] initWithTarget:self
                                                       action:@selector(tapGestureAction:)];
    }
    return _tap;
}

- (UIView *)maskView {
    if (!_maskView) {
        _maskView = [[UIView alloc] init];
        _maskView.backgroundColor = [UIColor colorFromRGBHexString:@"#101319" andAlpha:0.8 * 255];
        _maskView.userInteractionEnabled = YES;
    }
    return _maskView;
}

- (UIImageView *)emptImageView {
    if (!_emptImageView) {
        _emptImageView = [[UIImageView alloc] init];
        _emptImageView.image = [UIImage imageNamed:@"meeting_login_empt"];
        _emptImageView.hidden = YES;
    }
    return _emptImageView;
}

- (UILabel *)verLabel {
    if (!_verLabel) {
        _verLabel = [[UILabel alloc] init];
        _verLabel.textColor = [UIColor colorFromHexString:@"#86909C"];
        _verLabel.font = [UIFont systemFontOfSize:12 weight:UIFontWeightRegular];
    }
    return _verLabel;
}

- (BaseButton *)navLeftButton {
    if (!_navLeftButton) {
        _navLeftButton = [[BaseButton alloc] init];
        [_navLeftButton setImage:[UIImage imageNamed:@"meeting_nav_left"] forState:UIControlStateNormal];
        _navLeftButton.contentHorizontalAlignment = UIControlContentHorizontalAlignmentLeft;
        [_navLeftButton addTarget:self action:@selector(navBackAction:) forControlEvents:UIControlEventTouchUpInside];
    }
    return _navLeftButton;
}

- (void)dealloc {
    [[MeetingSocketIOManager shareSocketManager] disConnect];
    [[MeetingRTCManager shareRtc] destroy];
}

@end
