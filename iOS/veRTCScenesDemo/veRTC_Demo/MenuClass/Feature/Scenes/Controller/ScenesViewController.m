//
//  ScenesViewController.m
//  veRTC_Demo
//
//  Created by  on 2021/5/21.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import "ScenesViewController.h"
#import "MeetingLoginViewController.h"
#import "VoiceRoomListsViewController.h"
#import "ScenesItemButton.h"

@interface ScenesViewController ()

@property (nonatomic, strong) UIImageView *iconImageView;
@property (nonatomic, strong) ScenesItemButton *meetingButton;
@property (nonatomic, strong) ScenesItemButton *voiceButton;
@property (nonatomic, assign) BOOL isFirst;
@end

@implementation ScenesViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    [self addBgGradientLayer];
    
    [self.view addSubview:self.iconImageView];
    [self.iconImageView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(195, 25));
        make.left.mas_equalTo(20);
        make.top.mas_equalTo(45 + [DeviceInforTool getStatusBarHight]);
    }];
    
    [self.view addSubview:self.meetingButton];
    [self.meetingButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.mas_equalTo(20);
        make.right.mas_equalTo(-20);
        make.height.mas_equalTo(120);
        make.top.mas_equalTo(125 + [DeviceInforTool getStatusBarHight]);
    }];
    
    [self.view addSubview:self.voiceButton];
    [self.voiceButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.mas_equalTo(20);
        make.right.mas_equalTo(-20);
        make.height.mas_equalTo(120);
        make.top.equalTo(self.meetingButton.mas_bottom).offset(20);
    }];
    
    self.isFirst = NO;
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    
    if (!self.isFirst) {
        self.isFirst = YES;
        [self.meetingButton addItemLayer];
        [self.voiceButton addItemLayer];
        [self addInfoView:self.meetingButton type:0];
        [self addInfoView:self.voiceButton type:1];
    }
}

#pragma mark - Touch Action

- (void)meetingButtonAction:(UIButton *)sender {
    MeetingLoginViewController *meetingLoginVC = [[MeetingLoginViewController alloc] init];
    [self.navigationController pushViewController:meetingLoginVC animated:YES];
}

- (void)voiceButtonAction:(UIButton *)sender {
    VoiceRoomListsViewController *next = [[VoiceRoomListsViewController alloc] init];
    [self.navigationController pushViewController:next animated:YES];
}

#pragma mark - Private Action

- (void)addBgGradientLayer {
    UIColor *startColor = [UIColor colorFromHexString:@"#30394A"];
    UIColor *endColor = [UIColor colorFromHexString:@"#1D2129"];
    CAGradientLayer *gradientLayer = [CAGradientLayer layer];
    gradientLayer.frame = self.view.bounds;
    gradientLayer.colors = @[(__bridge id)[startColor colorWithAlphaComponent:1.0].CGColor,
                             (__bridge id)[endColor colorWithAlphaComponent:1.0].CGColor];
    gradientLayer.startPoint = CGPointMake(.0, .0);
    gradientLayer.endPoint = CGPointMake(.0, 1.0);
    [self.view.layer addSublayer:gradientLayer];
}


- (void)addInfoView:(UIButton *)button type:(NSInteger)type {
    NSString *iconName = @"";
    NSString *bgName = @"";
    NSString *message = @"";
    if (type == 0) {
        iconName = @"menu_metting";
        message = @"视频会议";
        bgName = @"menu_meeting_icon_bg";
    } else if (type == 1) {
        iconName = @"menu_voice";
        message = @"语音沙龙";
        bgName = @"menu_voice_icon_bg";
    } else {
        
    }
    UIImageView *bgImageView = [[UIImageView alloc] init];
    [button addSubview:bgImageView];
    
    UIImageView *iconImageView = [[UIImageView alloc] init];
    iconImageView.contentMode = UIViewContentModeScaleAspectFit;
    [button addSubview:iconImageView];
    
    iconImageView.image = [UIImage imageNamed:iconName];
    [iconImageView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(90, 90));
        make.centerY.equalTo(button);
        make.centerX.equalTo(button).multipliedBy(0.5);
    }];
    
    bgImageView.image = [UIImage imageNamed:bgName];
    [bgImageView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(300 / 2, 236 / 2));
        make.center.equalTo(iconImageView);
    }];
    
    UILabel *titleLabel = [[UILabel alloc] init];
    titleLabel.text = message;
    titleLabel.textColor = [UIColor whiteColor];
    titleLabel.font = [UIFont systemFontOfSize:24 weight:UIFontWeightRegular];
    [button addSubview:titleLabel];
    [titleLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerY.equalTo(button);
        make.left.equalTo(button.mas_right).multipliedBy(0.5);
    }];
}

#pragma mark - getter

- (ScenesItemButton *)meetingButton {
    if (!_meetingButton) {
        _meetingButton = [[ScenesItemButton alloc] init];
        _meetingButton.backgroundColor = [UIColor clearColor];
        _meetingButton.layer.cornerRadius = 20;
        _meetingButton.layer.masksToBounds = YES;
        [_meetingButton addTarget:self action:@selector(meetingButtonAction:) forControlEvents:UIControlEventTouchUpInside];
        [_meetingButton setImage:[UIImage imageNamed:@"menu_bg"] forState:UIControlStateNormal];
        
    }
    return _meetingButton;
}

- (ScenesItemButton *)voiceButton {
    if (!_voiceButton) {
        _voiceButton = [[ScenesItemButton alloc] init];
        _voiceButton.layer.cornerRadius = 20;
        _voiceButton.layer.masksToBounds = YES;
        _voiceButton.backgroundColor = [UIColor clearColor];
        [_voiceButton addTarget:self action:@selector(voiceButtonAction:) forControlEvents:UIControlEventTouchUpInside];
        [_voiceButton setImage:[UIImage imageNamed:@"menu_bg"] forState:UIControlStateNormal];
    }
    return _voiceButton;
}

- (UIImageView *)iconImageView {
    if (!_iconImageView) {
        _iconImageView = [[UIImageView alloc] init];
        _iconImageView.image = [UIImage imageNamed:@"voice_icon"];
    }
    return _iconImageView;
}


@end
