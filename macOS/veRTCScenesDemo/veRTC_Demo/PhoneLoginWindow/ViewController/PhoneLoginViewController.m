//
//  PhoneLoginViewController.m
//  veRTC_Demo
//
//  Created by  on 2021/6/7.
//

#import "PhoneLoginViewController.h"
#import "PhoneLoginCodeButton.h"
#import "PhoneLoginTextFieldView.h"

@interface PhoneLoginViewController ()

@property (nonatomic, strong) NSImageView *iconImageView;
@property (nonatomic, strong) PhoneLoginTextFieldView *phoneTextFieldView;
@property (nonatomic, strong) TrackButton *loginButton;

@end

@implementation PhoneLoginViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self.view setBackgroundColor:[NSColor colorFromHexString:@"#272E3B"]];
    
    [self.view addSubview:self.iconImageView];
    [self.iconImageView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(212, 40));
        make.centerX.equalTo(self.view);
        make.top.mas_equalTo(100);
    }];
    
    [self.view addSubview:self.loginButton];
    [self.loginButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(320, 48));
        make.centerX.equalTo(self.view);
        make.bottom.equalTo(self.view).offset(-120);
    }];
    
    [self.view addSubview:self.phoneTextFieldView];
    [self.phoneTextFieldView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(320, 48));
        make.centerX.equalTo(self.view);
        make.bottom.equalTo(self.loginButton.mas_top).offset(-68);
    }];
    
    __weak __typeof(self) wself = self;
    self.phoneTextFieldView.changeInputIllegal = ^(BOOL isIllegal) {
        [wself updateLoginButton];
    };
    [self updateLoginButton];
}

- (void)updateLoginButton {
    if (self.phoneTextFieldView.isIllegal) {
        self.loginButton.enabled = NO;
        [self.loginButton setTitleColor:@"FFFFFF" andAlpha:0.3 * 255 title:@"登录"];
        self.loginButton.backgroundColor = [NSColor colorFromRGBHexString:@"#4080FF" andAlpha:0.3 * 255];
        self.loginButton.currentStatus = TrackButtonStatusDisabled;
    } else {
        self.loginButton.enabled = YES;
        [self.loginButton setTitleColor:@"#FFFFFF" title:@"登录"];
        self.loginButton.backgroundColor = [NSColor colorFromHexString:@"#4080FF"];
        self.loginButton.currentStatus = TrackButtonStatusDefault;
    }
}

#pragma mark - Private Action

- (void)loginButtonAction:(NSButton *)sender {
    if (IsEmptyStr(self.phoneTextFieldView.text)) {
        return;
    }
    __weak __typeof(self) wself = self;
    [MeetingControlCompoments login:self.phoneTextFieldView.text
                              block:^(BaseUserModel * _Nonnull userModel,
                                      MeetingControlAckModel * _Nonnull ackModel) {
        if (ackModel.result) {
            [LocalUserCompoments updateLocalUserModel:userModel];
            if (wself.loginBlock) {
                wself.loginBlock();
            }
        } else {
            [[MeetingToastComponents shareMeetingToastComponents] showWithMessage:ackModel.message];
        }
    }];
}

- (void)maskAction {
    [self.phoneTextFieldView resignFirstResponder];
}

#pragma mark - getter

- (PhoneLoginTextFieldView *)phoneTextFieldView {
    if (!_phoneTextFieldView) {
        _phoneTextFieldView = [[PhoneLoginTextFieldView alloc] init];
        _phoneTextFieldView.maxLimit = 18;
        _phoneTextFieldView.placeholderStr = @"输入用户名";
        _phoneTextFieldView.errorStr = @"仅支持中文、字母、数字，1-18位";
        _phoneTextFieldView.isNeedBorder = YES;
    }
    return _phoneTextFieldView;
}

- (NSImageView *)iconImageView {
    if (!_iconImageView) {
        _iconImageView = [[NSImageView alloc] init];
        _iconImageView.image = [NSImage imageNamed:@"menu_login"];
    }
    return _iconImageView;
}

- (TrackButton *)loginButton {
    if (!_loginButton) {
        _loginButton = [[TrackButton alloc] init];
        _loginButton.wantsLayer = YES;
        _loginButton.layer.masksToBounds = YES;
        _loginButton.layer.cornerRadius = 48/2;
        [_loginButton setTitleColor:@"#FFFFFF" title:@"登录"];
        [_loginButton setTarget:self];
        [_loginButton setAction:@selector(loginButtonAction:)];
        _loginButton.font = [NSFont systemFontOfSize:14];
        
        [_loginButton bingBackColorWithStatus:TrackButtonStatusDefault color:[NSColor colorFromHexString:@"#4080FF"]];
        [_loginButton bingBackColorWithStatus:TrackButtonStatusHover color:[NSColor colorFromHexString:@"#165DFF"]];
        [_loginButton bingBackColorWithStatus:TrackButtonStatusActive color:[NSColor colorFromHexString:@"#0E42D2"]];
    }
    return _loginButton;
}

@end
