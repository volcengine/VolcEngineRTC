//
//  MeetingEndCompoments.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/10.
//

#import "MeetingEndCompoments.h"
#import "MeetingEndView.h"

@interface MeetingEndCompoments ()

@property (nonatomic, strong) MeetingEndView *endView;

@property (nonatomic, strong) UIButton *maskView;

@end

@implementation MeetingEndCompoments

- (instancetype)init {
    self = [super init];
    if (self) {
        
    }
    return self;
}

#pragma mark - Publish Action

- (void)showWithStatus:(MeetingEndStatus)status {
    UIViewController *rootVC = [DeviceInforTool topViewController];;
    
    [rootVC.view addSubview:self.maskView];
    [self.maskView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(rootVC.view);
    }];

    [rootVC.view addSubview:self.endView];
    [self.endView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.width.mas_equalTo(590/2);
        make.center.equalTo(rootVC.view);
    }];

    self.endView.meetingEndStatus = status;
    __weak __typeof(self) wself = self;
    self.endView.clickButtonBlock = ^(MeetingButtonStatus status) {
        [wself dismissEndView];
        if (wself.clickButtonBlock) {
            wself.clickButtonBlock(status);
        }
    };
}

#pragma mark - Private Action

- (void)dismissEndView {
    [self.endView removeFromSuperview];
    self.endView = nil;
    [self.maskView removeFromSuperview];
    self.maskView = nil;
}

#pragma mark - getter

- (MeetingEndView *)endView {
    if (!_endView) {
        _endView = [[MeetingEndView alloc] init];
        [_endView setBackgroundColor:[UIColor colorFromHexString:@"#272E3B"]];
        _endView.layer.masksToBounds = YES;
        _endView.layer.cornerRadius = 4;
    }
    return _endView;
}

- (UIButton *)maskView {
    if (!_maskView) {
        _maskView = [[UIButton alloc] init];
        [_maskView setBackgroundColor:[UIColor colorFromRGBHexString:@"#101319" andAlpha:0.7 * 255]];
    }
    return _maskView;
}

- (void)dealloc {
    NSLog(@"dealloc %@",NSStringFromClass([self class]));
}

@end
