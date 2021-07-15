//
//  MeetingToastComponents.m
//  quickstart
//
//  Created by  on 2021/4/1.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import "MeetingToastComponents.h"
#import "ToastView.h"

@interface MeetingToastComponents ()

@property (nonatomic, weak) ToastView *keepToastView;

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
    if (isKeep && _keepToastView) {
        return;
    }
    
    __block ToastView *toastView = [[ToastView alloc] initWithMeeage:message];
    BOOL hasNav = YES;
    [windowView addSubview:toastView];
    [toastView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.mas_equalTo((hasNav ? 44 : 0) + [DeviceInforTool getStatusBarHight]);
        make.height.mas_equalTo(50);
        make.width.centerX.equalTo(windowView);
    }];
    
    if (isKeep) {
        _keepToastView = toastView;
    } else {
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(2 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
            [toastView removeAllSubviews];
            [toastView removeFromSuperview];
            toastView = nil;
        });
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
    UIViewController *windowVC = [DeviceInforTool topViewController];
    [self showWithMessage:message view:windowVC.view];
}

- (void)dismiss {
    [_keepToastView removeAllSubviews];
    [_keepToastView removeFromSuperview];
    _keepToastView = nil;
}

@end
