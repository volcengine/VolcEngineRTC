//
//  VoiceNavViewController.m
//  quickstart
//
//  Created by  on 2021/3/22.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import "VoiceNavViewController.h"

@interface VoiceNavViewController ()<UIGestureRecognizerDelegate>

@property (nonatomic, strong) UILabel *navLabel;
@property (nonatomic, strong) BaseButton *leftButton;
@property (nonatomic, strong) BaseButton *rightButton;

@end

@implementation VoiceNavViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.navigationController.interactivePopGestureRecognizer.delegate = self;
    
    [self.view addSubview:self.bgView];
    [self.view addSubview:self.navView];
    [self.navView addSubview:self.navLabel];
    [self.navView addSubview:self.leftButton];
    [self.navView addSubview:self.rightButton];
    [self addConstraints];
    [self addBgGradientLayer];
}

- (void)addConstraints {
    [self.bgView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(self.view);
    }];
    
    [self.navView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.top.right.equalTo(self.view);
        make.height.mas_equalTo([DeviceInforTool getStatusBarHight] + 44);
    }];
    
    [self.navLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerX.equalTo(self.navView);
        make.centerY.equalTo(self.navView).offset([DeviceInforTool getStatusBarHight]/2);
    }];
    
    [self.leftButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.height.width.mas_equalTo(16);
        make.left.mas_equalTo(16);
        make.centerY.equalTo(self.navLabel);
    }];
    
    [self.rightButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.right.mas_equalTo(-16);
        make.centerY.equalTo(self.navLabel);
    }];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    [self.navigationController setNavigationBarHidden:YES animated:NO];
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    
    self.navigationController.interactivePopGestureRecognizer.enabled = YES;
}

- (void)navBackAction:(UIButton *)sender {
    [self.navigationController popViewControllerAnimated:YES];
}

- (void)rightButtonAction:(BaseButton *)sender {
    
}

- (void)setNavTitle:(NSString *)navTitle {
    _navTitle = navTitle;
    self.navLabel.text = navTitle;
}

- (void)setRightTitle:(NSString *)rightTitle {
    _rightTitle = rightTitle;
    
    [self.rightButton setTitle:rightTitle forState:UIControlStateNormal];
}

- (void)addBgGradientLayer {
    UIColor *startColor = [UIColor colorFromHexString:@"#30394A"];
    UIColor *endColor = [UIColor colorFromHexString:@"#1D2129"];
    CAGradientLayer *gradientLayer = [CAGradientLayer layer];
    gradientLayer.frame = self.view.bounds;
    gradientLayer.colors = @[(__bridge id)[startColor colorWithAlphaComponent:1.0].CGColor,
                             (__bridge id)[endColor colorWithAlphaComponent:1.0].CGColor];
    gradientLayer.startPoint = CGPointMake(.0, .0);
    gradientLayer.endPoint = CGPointMake(.0, 1.0);
    [self.bgView.layer addSublayer:gradientLayer];
}


#pragma mark - getter

- (BaseButton *)leftButton {
    if (!_leftButton) {
        _leftButton = [[BaseButton alloc] init];
        [_leftButton setImage:[UIImage imageNamed:@"meeting_nav_left"] forState:UIControlStateNormal];
        _leftButton.contentHorizontalAlignment = UIControlContentHorizontalAlignmentLeft;
        [_leftButton addTarget:self action:@selector(navBackAction:) forControlEvents:UIControlEventTouchUpInside];
    }
    return _leftButton;
}

- (BaseButton *)rightButton {
    if (!_rightButton) {
        _rightButton = [[BaseButton alloc] init];;
        [_rightButton setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
        _rightButton.titleLabel.font = [UIFont systemFontOfSize:15];
        [_rightButton addTarget:self action:@selector(rightButtonAction:) forControlEvents:UIControlEventTouchUpInside];
    }
    return _rightButton;
}

- (UIView *)navView {
    if (!_navView) {
        _navView = [[UIView alloc] init];
        _navView.backgroundColor = [UIColor colorFromHexString:@"#272E3B"];
    }
    return _navView;
}

- (UILabel *)navLabel {
    if (!_navLabel) {
        _navLabel = [[UILabel alloc] init];
        _navLabel.font = [UIFont systemFontOfSize:17];
        _navLabel.textColor = [UIColor whiteColor];
    }
    return _navLabel;
}

- (UIView *)bgView {
    if (!_bgView) {
        _bgView = [[UIView alloc] init];
        _bgView.hidden = YES;
    }
    return _bgView;
}

@end
