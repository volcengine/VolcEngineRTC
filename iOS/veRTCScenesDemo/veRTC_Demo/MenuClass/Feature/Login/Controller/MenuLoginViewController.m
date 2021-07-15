//
//  MenuLoginViewController.m
//  veRTC_Demo
//
//  Created by  on 2021/6/6.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import "MenuLoginViewController.h"
#import "VocieCreateTextFieldView.h"
#import "MenuLoginCodeButton.h"
#import "MenuUpgradeCompoments.h"

@interface MenuLoginViewController ()

@property (nonatomic, strong) UIImageView *maskImageView;
@property (nonatomic, strong) UIImageView *iconImageView;
@property (nonatomic, strong) VocieCreateTextFieldView *userNameTextFieldView;
@property (nonatomic, strong) UIButton *loginButton;

@end

@implementation MenuLoginViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyBoardDidShow:) name:UIKeyboardWillShowNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyBoardDidHide:) name:UIKeyboardWillHideNotification object:nil];
    
    [self addMakeConstraints];
    
    __weak __typeof(self) wself = self;
    self.userNameTextFieldView.textFieldChangeBlock = ^(NSString * _Nonnull text) {
        [wself updateLoginButtonStatus];
    };
    [self updateLoginButtonStatus];
}

#pragma mark - Private Action

- (void)keyBoardDidShow:(NSNotification *)notifiction {
    CGRect keyboardRect = [[notifiction.userInfo objectForKey:UIKeyboardFrameEndUserInfoKey] CGRectValue];
    [UIView animateWithDuration:0.25 animations:^{
        [self.loginButton mas_updateConstraints:^(MASConstraintMaker *make) {
            make.bottom.equalTo(self.view).offset(-keyboardRect.size.height - 80/2);
        }];
    }];
    self.iconImageView.hidden = SCREEN_WIDTH <= 320 ? YES : NO;
    [self.view layoutIfNeeded];
}

- (void)keyBoardDidHide:(NSNotification *)notifiction {
    [UIView animateWithDuration:0.25 animations:^{
        [self.loginButton mas_updateConstraints:^(MASConstraintMaker *make) {
            make.bottom.equalTo(self.view).offset(-288 - [DeviceInforTool getVirtualHomeHeight]);
        }];
    }];
    self.iconImageView.hidden = NO;
    [self.view layoutIfNeeded];
}

- (void)loginButtonAction:(UIButton *)sender {
    __weak __typeof(self) wself = self;
    [VoiceControlCompoments login:self.userNameTextFieldView.text
                            block:^(BaseUserModel * _Nonnull userModel,
                                    VoiceControlAckModel * _Nonnull ackModel) {
        if (ackModel.result) {
            [LocalUserComponents updateLocalUserModel:userModel];
            [wself dismissViewControllerAnimated:YES completion:^{
                    
            }];
        } else {
            [[MeetingToastComponents shareMeetingToastComponents] showWithMessage:ackModel.message];
        }
    }];
}


- (void)maskAction {
    [self.userNameTextFieldView resignFirstResponder];
}

#pragma mark - Private Action

- (void)updateLoginButtonStatus {
    BOOL isDisable = IsEmptyStr(self.userNameTextFieldView.text);
    BOOL isIllega = self.userNameTextFieldView.isIllega;
    if (isDisable || isIllega) {
        self.loginButton.userInteractionEnabled = NO;
        self.loginButton.backgroundColor = [UIColor colorFromRGBHexString:@"#4080FF" andAlpha:0.3 * 255];
        [self.loginButton setTitleColor:[UIColor colorFromRGBHexString:@"#ffffff" andAlpha:0.3 * 255] forState:UIControlStateNormal];
    } else {
        self.loginButton.userInteractionEnabled = YES;
        self.loginButton.backgroundColor = [UIColor colorFromHexString:@"#0E42D2"];
        [self.loginButton setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    }
}

- (void)addMakeConstraints {
    [self.view addSubview:self.maskImageView];
    [self.maskImageView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(self.view);
    }];
    
    [self.view addSubview:self.iconImageView];
    [self.iconImageView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(160, 30));
        make.centerX.equalTo(self.view);
        make.top.mas_equalTo(100 + [DeviceInforTool getStatusBarHight]);
    }];
    
    [self.view addSubview:self.loginButton];
    [self.loginButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.mas_equalTo(30);
        make.right.mas_equalTo(-30);
        make.height.mas_equalTo(50);
        make.bottom.equalTo(self.view).offset(-288 - [DeviceInforTool getVirtualHomeHeight]);
    }];
    
    [self.view addSubview:self.userNameTextFieldView];
    [self.userNameTextFieldView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.mas_equalTo(30);
        make.right.mas_equalTo(-30);
        make.height.mas_equalTo(32);
        make.bottom.equalTo(self.loginButton.mas_top).offset(-40);
    }];
}

#pragma mark - getter

- (VocieCreateTextFieldView *)userNameTextFieldView {
    if (!_userNameTextFieldView) {
        _userNameTextFieldView = [[VocieCreateTextFieldView alloc] initWithModify:NO];
        _userNameTextFieldView.maxLimit = 18;
        _userNameTextFieldView.placeholderStr = @"请输入用户名";
    }
    return _userNameTextFieldView;
}

- (UIImageView *)maskImageView {
    if (!_maskImageView) {
        _maskImageView = [[UIImageView alloc] init];
        _maskImageView.image = [UIImage imageNamed:@"menu_mask"];
        _maskImageView.contentMode = UIViewContentModeScaleAspectFill;
        _maskImageView.clipsToBounds = YES;
        
        UIView *view = [[UIView alloc] init];
        view.userInteractionEnabled = NO;
        view.backgroundColor = [UIColor colorFromRGBHexString:@"#141C2C" andAlpha:0.7 * 255];
        [_maskImageView addSubview:view];
        [view mas_makeConstraints:^(MASConstraintMaker *make) {
            make.edges.equalTo(_maskImageView);
        }];
        
        _maskImageView.userInteractionEnabled = YES;
        UITapGestureRecognizer *tap = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(maskAction)];
        [_maskImageView addGestureRecognizer:tap];
    }
    return _maskImageView;
}

- (UIImageView *)iconImageView {
    if (!_iconImageView) {
        _iconImageView = [[UIImageView alloc] init];
        _iconImageView.image = [UIImage imageNamed:@"menu_login"];
        _iconImageView.contentMode = UIViewContentModeScaleAspectFit;
    }
    return _iconImageView;
}

- (UIButton *)loginButton {
    if (!_loginButton) {
        _loginButton = [[UIButton alloc] init];
        _loginButton.layer.masksToBounds = YES;
        _loginButton.layer.cornerRadius = 50/2;
        [_loginButton setTitle:@"登录" forState:UIControlStateNormal];
        _loginButton.titleLabel.font = [UIFont systemFontOfSize:16 weight:UIFontWeightRegular];
        [_loginButton addTarget:self action:@selector(loginButtonAction:) forControlEvents:UIControlEventTouchUpInside];
    }
    return _loginButton;
}

- (void)dealloc {

}

@end
