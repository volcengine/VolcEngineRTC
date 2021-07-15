//
//  PhoneLoginCodeButton.m
//  veRTC_Demo
//
//  Created by  on 2021/6/6.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import "PhoneLoginCodeButton.h"
#import "GCDTimer.h"

@interface PhoneLoginCodeButton ()

@property (nonatomic, strong) NSView *maskView;
@property (nonatomic, strong) NSLabel *messageLabel;
@property (nonatomic, strong) GCDTimer *timer;
@property (nonatomic, assign) NSInteger secondValue;

@end

@implementation PhoneLoginCodeButton

- (instancetype)init {
    self = [super init];
    if (self) {
        [self addSubview:self.maskView];
        [self.maskView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.edges.equalTo(self);
        }];
        
        [self addSubview:self.messageLabel];
        [self.messageLabel mas_makeConstraints:^(MASConstraintMaker *make) {
            make.center.equalTo(self);
        }];
        
        self.loginCodeStatus = LoginCodeStatusNone;
        self.messageLabel.text = [self getMessageWithStatus:self.loginCodeStatus];
        __weak __typeof(self) wself = self;
        [self.timer startTimerWithSpace:1 block:^(BOOL result) {
            [wself timerMethod];
        }];
        [self.timer suspend];
        
        self.changeStatus = ^(TrackButtonStatus status) {
            if (!wself.isDisabled) {
                if (status == TrackButtonStatusDefault) {
                    wself.maskView.backgroundColor = [NSColor colorFromRGBHexString:@"#ffffff" andAlpha:0.1 * 255];
                } else if (status == TrackButtonStatusHover) {
                    wself.maskView.backgroundColor = [NSColor colorFromRGBHexString:@"#ffffff" andAlpha:0.2 * 255];
                } else if (status == TrackButtonStatusActive) {
                    wself.maskView.backgroundColor = [NSColor colorFromRGBHexString:@"#ffffff" andAlpha:0.1 * 255];
                } else {
                    wself.maskView.backgroundColor = [NSColor colorFromRGBHexString:@"#ffffff" andAlpha:0.1 * 255];
                }
            }
        };
    }
    return self;
}

#pragma mark - Publish Action

- (void)setIsDisabled:(BOOL)isDisabled {
    _isDisabled = isDisabled;
    [self updateStatus:isDisabled];
}

- (void)updateStatus:(BOOL)isDisabled {
    if (self.loginCodeStatus == LoginCodeStatusCountdown) {
        //倒计时不可点击，且展示不失效UI
        self.enabled = NO;
        isDisabled = NO;
    }
    if (isDisabled) {
        self.enabled = NO;
        self.maskView.backgroundColor = [NSColor colorFromRGBHexString:@"#ffffff" andAlpha:0.05 * 255];
        self.messageLabel.textColor = [NSColor colorFromHexString:@"#4E5969"];
    } else {
        self.enabled = YES;
        self.maskView.backgroundColor = [NSColor colorFromRGBHexString:@"#ffffff" andAlpha:0.1 * 255];
        self.messageLabel.textColor = [NSColor whiteColor];
    }
}

- (void)setLoginCodeStatus:(LoginCodeStatus)loginCodeStatus {
    _loginCodeStatus = loginCodeStatus;
    
    if (loginCodeStatus == LoginCodeStatusLoading ||
        loginCodeStatus == LoginCodeStatusCountdown) {
        //网络请求， 倒计时不可点击
        self.enabled = NO;
    } else {
        self.enabled = YES;
    }
    
    if (loginCodeStatus == LoginCodeStatusCountdown) {
        [self.timer resume];
        self.secondValue = 0;
    } else {
        [self.timer suspend];
    }
    
    if (loginCodeStatus == LoginCodeStatusAgain) {
        self.messageLabel.text = [self getMessageWithStatus:LoginCodeStatusAgain];
    }
}

#pragma mark - Private Action

- (void)timerMethod {
    self.messageLabel.text = [NSString stringWithFormat:@"%lds", 60 - (long)self.secondValue];
    if ([self.messageLabel.text integerValue] <= 0) {
        self.secondValue = 0;
        [self.timer suspend];
        self.loginCodeStatus = LoginCodeStatusAgain;
        [self updateStatus:self.isDisabled];
    } else {
        self.secondValue++;
    }
}

- (NSString *)getMessageWithStatus:(LoginCodeStatus)loginCodeStatus {
    NSString *message = @"";
    switch (loginCodeStatus) {
        case LoginCodeStatusNone:
            message = @"获取验证码";
            break;
        case LoginCodeStatusLoading:
            message = @"获取验证码";
            break;
        case LoginCodeStatusCountdown:
            message = @"";
            break;
        case LoginCodeStatusAgain:
            message = @"获取验证码";
            break;
        default:
            break;
    }
    return message;
}

- (NSLabel *)messageLabel {
    if (!_messageLabel) {
        _messageLabel = [[NSLabel alloc] init];
        _messageLabel.font = [NSFont systemFontOfSize:16];
        _messageLabel.enabled = NO;
    }
    return _messageLabel;
}

- (NSView *)maskView {
    if (!_maskView) {
        _maskView = [[NSView alloc] init];
        _maskView.wantsLayer = YES;
        _maskView.layer.cornerRadius = 4;
        _maskView.layer.masksToBounds = YES;
    }
    return _maskView;
}

- (GCDTimer *)timer {
    if (!_timer) {
        _timer = [[GCDTimer alloc] init];
    }
    return _timer;
}

@end
