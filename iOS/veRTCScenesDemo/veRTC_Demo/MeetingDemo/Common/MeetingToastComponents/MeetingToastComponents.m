//
//  MeetingToastComponents.m
//  quickstart
//
//  Created by on 2021/4/1.
//  Copyright © 2021. All rights reserved.
//

#import "MeetingToastComponents.h"

@interface MeetingToastComponents ()

@property (nonatomic, strong) UIView *bgView;

@end

@implementation MeetingToastComponents

+ (MeetingToastComponents *)shareMeetingToastComponents {
    static dispatch_once_t onceToken ;
    static MeetingToastComponents *toastComponents = nil;
    dispatch_once(&onceToken, ^{
        toastComponents = [[self alloc] init];
    });
    return toastComponents ;
}


#pragma mark - Publish Action

- (void)showWithMessage:(NSString *)message view:(UIView *)windowView keep:(BOOL)isKeep block:(void (^)(BOOL result))block {
    if (message.length <= 0) {
        return;
    }
    if (!self.bgView) {
        self.bgView = [[UIView alloc] init];
    } else {
        [self.bgView removeAllSubviews];
    }
    self.bgView.backgroundColor = [UIColor colorFromHexString:@"#FFECE8"];
    
    UILabel *titleLabel = [[UILabel alloc] init];
    titleLabel.textColor = [UIColor colorFromHexString:@"#4E5969"];
    titleLabel.font = [UIFont systemFontOfSize:14.0 * (SCREEN_WIDTH / 375) weight:UIFontWeightRegular];
    titleLabel.text = message;
    
    UIImageView *iconImageView = [[UIImageView alloc] init];
    iconImageView.image = [UIImage imageNamed:@"meeting_end_waring"];
    
    [windowView addSubview:self.bgView];
    [self.bgView addSubview:iconImageView];
    [self.bgView addSubview:titleLabel];
    
    [self.bgView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.mas_equalTo(44 + [DeviceInforTool getStatusBarHight]);
        make.height.mas_equalTo(40);
        make.width.centerX.equalTo(windowView);
    }];
    
    [iconImageView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(16.0 * (SCREEN_WIDTH / 375), 16.0 * (SCREEN_WIDTH / 375)));
        make.centerY.equalTo(self.bgView);
        make.left.equalTo(self.bgView).offset(16.0 * (SCREEN_WIDTH / 375));
    }];
    
    [titleLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerY.equalTo(self.bgView);
        make.left.equalTo(iconImageView.mas_right).offset(16.0 * (SCREEN_WIDTH / 375));
    }];
    
    if (!isKeep) {
        [NSObject cancelPreviousPerformRequestsWithTarget:self selector:@selector(dismiss) object:nil];
        [self performSelector:@selector(dismiss) withObject:nil afterDelay:2];
    }
}

- (void)showWithMessage:(NSString *)message view:(UIView *)windowView block:(void (^)(BOOL result))block {
    [self showWithMessage:message view:windowView keep:NO block:block];
}

- (void)showWithMessage:(NSString *)message view:(UIView *)windowView {
    [self showWithMessage:message view:windowView block:^(BOOL result) {
        
    }];
}

- (void)showWithMessage:(NSString *)message {
    UIViewController *topVC = [DeviceInforTool topViewController];
    [self showWithMessage:message view:topVC.view];
}

- (void)dismiss {
    [self.bgView removeAllSubviews];
    [self.bgView removeFromSuperview];
    self.bgView = nil;
}

@end
