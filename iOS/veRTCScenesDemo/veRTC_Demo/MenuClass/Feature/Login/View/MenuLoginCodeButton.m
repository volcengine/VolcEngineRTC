//
//  MenuLoginCodeButton.m
//  veRTC_Demo
//
//  Created by  on 2021/6/6.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import "MenuLoginCodeButton.h"
#import "GCDTimer.h"

@interface MenuLoginCodeButton ()

@property (nonatomic, strong) UIView *maskView;
@property (nonatomic, strong) UILabel *messageLabel;
@property (nonatomic, strong) GCDTimer *timer;
@property (nonatomic, assign) NSInteger secondValue;

@end

@implementation MenuLoginCodeButton

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
    }
    return self;
}

#pragma mark - Publish Action

- (void)setLoginCodeStatus:(LoginCodeStatus)loginCodeStatus {
    _loginCodeStatus = loginCodeStatus;
    
    if (loginCodeStatus == LoginCodeStatusLoading ||
        loginCodeStatus == LoginCodeStatusCountdown) {
        //网络请求， 倒计时不可点击
        self.userInteractionEnabled = NO;
    } else {
        self.userInteractionEnabled = YES;
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

- (void)setIsDisable:(BOOL)isDisable {
    _isDisable = isDisable;
    if (self.loginCodeStatus == LoginCodeStatusCountdown) {
        return;
    }
    
    if (isDisable) {
        self.userInteractionEnabled = NO;
        self.maskView.backgroundColor = [UIColor colorFromRGBHexString:@"#ffffff" andAlpha:0.05 * 255];
        self.messageLabel.textColor = [UIColor colorFromRGBHexString:@"#86909C"];
    } else {
        self.userInteractionEnabled = YES;
        self.maskView.backgroundColor = [UIColor colorFromRGBHexString:@"#ffffff" andAlpha:0.1 * 255];
        self.messageLabel.textColor = [UIColor whiteColor];
    }
}

#pragma mark - Private Action

- (void)timerMethod {
    self.messageLabel.text = [NSString stringWithFormat:@"%lds", 60 - (long)self.secondValue];
    if ([self.messageLabel.text integerValue] <= 0) {
        self.secondValue = 0;
        [self.timer suspend];
        self.loginCodeStatus = LoginCodeStatusAgain;
        [self setIsDisable:self.isDisable];
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

- (UILabel *)messageLabel {
    if (!_messageLabel) {
        _messageLabel = [[UILabel alloc] init];
        _messageLabel.font = [UIFont systemFontOfSize:16];
        _messageLabel.userInteractionEnabled = NO;
    }
    return _messageLabel;
}

- (UIView *)maskView {
    if (!_maskView) {
        _maskView = [[UIView alloc] init];
        _maskView.layer.cornerRadius = 4;
        _maskView.layer.masksToBounds = YES;
        _maskView.userInteractionEnabled = NO;
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
