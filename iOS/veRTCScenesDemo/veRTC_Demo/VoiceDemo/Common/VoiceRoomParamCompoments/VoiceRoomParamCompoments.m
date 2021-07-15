//
//  VoiceRoomParamCompoments.m
//  veRTC_Demo
//
//  Created by  on 2021/5/24.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import "VoiceRoomParamCompoments.h"
#import "VoiceRoomTopSelectView.h"
#import "VoiceRoomParamInfoView.h"

@interface VoiceRoomParamCompoments () <VoiceRoomTopSelectViewDelegate>

@property (nonatomic, strong) VoiceRoomTopSelectView *topSelectView;
@property (nonatomic, strong) VoiceRoomParamInfoView *paramInfoView;
@property (nonatomic, strong) UIButton *maskButton;

@end

@implementation VoiceRoomParamCompoments

- (instancetype)init {
    self = [super init];
    if (self) {
        
    }
    return self;
}

#pragma mark - Publish Action

- (void)show {
    UIViewController *rootVC = [DeviceInforTool topViewController];;
    
    [rootVC.view addSubview:self.maskButton];
    [self.maskButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(rootVC.view);
    }];
    
    [self.maskButton addSubview:self.paramInfoView];
    [self.paramInfoView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.mas_equalTo(0);
        make.right.mas_equalTo(0);
        make.height.mas_offset(612 / 2 + [DeviceInforTool getVirtualHomeHeight]);
        make.bottom.mas_offset(0);
    }];

    [self.maskButton addSubview:self.topSelectView];
    [self.topSelectView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.right.equalTo(rootVC.view);
        make.bottom.equalTo(self.paramInfoView.mas_top);
        make.height.mas_equalTo(44);
    }];
}

- (void)updateModel:(VoiceRoomParamInfoModel *)model {
    if (self.paramInfoView.superview) {
        self.paramInfoView.paramInfoModel = model;
    }
}

#pragma mark - VoiceRoomTopSelectViewDelegate

- (void)voiceRoomTopSelectView:(VoiceRoomTopSelectView *)voiceRoomTopSelectView clickCancelAction:(id)model {
    [self dismissUserListView];
}

- (void)voiceRoomTopSelectView:(VoiceRoomTopSelectView *)voiceRoomTopSelectView clickSwitchItem:(BOOL)isAudience {

}

#pragma mark - Private Action

- (void)maskButtonAction {
    [self dismissUserListView];
}

- (void)dismissUserListView {
    [self.maskButton removeAllSubviews];
    [self.maskButton removeFromSuperview];
    self.maskButton = nil;
}

#pragma mark - Getter

- (UIButton *)maskButton {
    if (!_maskButton) {
        _maskButton = [[UIButton alloc] init];
        [_maskButton addTarget:self action:@selector(maskButtonAction) forControlEvents:UIControlEventTouchUpInside];
        [_maskButton setBackgroundColor:[UIColor colorFromRGBHexString:@"#101319" andAlpha:0.5 * 255]];
    }
    return _maskButton;
}

- (VoiceRoomTopSelectView *)topSelectView {
    if (!_topSelectView) {
        _topSelectView = [[VoiceRoomTopSelectView alloc] init];
        _topSelectView.delegate = self;
        _topSelectView.titleStr = @"实时音频数据";
    }
    return _topSelectView;
}

- (VoiceRoomParamInfoView *)paramInfoView {
    if (!_paramInfoView) {
        _paramInfoView = [[VoiceRoomParamInfoView alloc] init];
    }
    return _paramInfoView;
}

- (void)dealloc {
    NSLog(@"dealloc %@",NSStringFromClass([self class]));
}
@end
