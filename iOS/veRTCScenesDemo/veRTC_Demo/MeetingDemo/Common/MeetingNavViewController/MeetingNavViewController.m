//
//  MeetingNavViewController.m
//  quickstart
//
//  Created by  on 2021/3/22.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import "MeetingNavViewController.h"

@interface MeetingNavViewController ()<UIGestureRecognizerDelegate>

@property (nonatomic, strong) UILabel *navLabel;
@property (nonatomic, strong) BaseButton *leftButton;

@end

@implementation MeetingNavViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.navigationController.interactivePopGestureRecognizer.delegate = self;
    
    [self.view addSubview:self.navView];
    [self.navView addSubview:self.navLabel];
    [self.navView addSubview:self.leftButton];
    [self addConstraints];
}

- (void)addConstraints {
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

- (void)setNavTitle:(NSString *)navTitle {
    _navTitle = navTitle;
    self.navLabel.text = navTitle;
}

#pragma mark - getter

- (BaseButton *)leftButton {
    if (!_leftButton) {
        _leftButton = [BaseButton buttonWithType:UIButtonTypeCustom];
        [_leftButton setImage:[UIImage imageNamed:@"meeting_nav_left"] forState:UIControlStateNormal];
        _leftButton.contentHorizontalAlignment = UIControlContentHorizontalAlignmentLeft;
        [_leftButton addTarget:self action:@selector(navBackAction:) forControlEvents:UIControlEventTouchUpInside];
    }
    return _leftButton;
}

- (UIView *)navView {
    if (!_navView) {
        _navView = [[UIView alloc] init];
        _navView.backgroundColor = [UIColor colorFromHexString:@"#1D2129"];
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

@end
