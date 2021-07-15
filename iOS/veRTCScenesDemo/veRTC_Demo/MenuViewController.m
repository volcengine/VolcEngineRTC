//
//  MenuViewController.m
//  veRTC_Demo
//
//  Created by  on 2021/5/18.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import "MenuViewController.h"
#import "ScenesViewController.h"
#import "UserViewController.h"
#import "MenuItemButton.h"
#import "MenuLoginViewController.h"
#import "MenuUpgradeCompoments.h"

@interface MenuViewController ()

@property (nonatomic, strong) MenuItemButton *scenesButton;
@property (nonatomic, strong) MenuItemButton *userButton;

@property (nonatomic, strong) UserViewController *userViewController;
@property (nonatomic, strong) ScenesViewController *scenesViewController;

@property (nonatomic, strong) MenuUpgradeCompoments *upgradeCompoments;

@end

@implementation MenuViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(loginExpiredNotificate) name:NotificationLoginExpired object:nil];
    
    [self addChildViewController:self.userViewController];
    [self.view addSubview:self.userViewController.view];
    [self.userViewController.view mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(self.view);
    }];
    
    [self addChildViewController:self.scenesViewController];
    [self.view addSubview:self.scenesViewController.view];
    [self.scenesViewController.view mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(self.view);
    }];
    
    [self.view addSubview:self.scenesButton];
    [self.scenesButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.width.equalTo(self.view).multipliedBy(0.5);
        make.height.mas_equalTo(64);
        make.left.mas_equalTo(0);
        make.bottom.mas_equalTo(-[DeviceInforTool getVirtualHomeHeight]);
    }];
    
    [self.view addSubview:self.userButton];
    [self.userButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.width.equalTo(self.view).multipliedBy(0.5);
        make.height.mas_equalTo(64);
        make.right.mas_equalTo(0);
        make.bottom.mas_equalTo(-[DeviceInforTool getVirtualHomeHeight]);
    }];
    
    [self scenesButtonAction];
    [self.upgradeCompoments checkUpgrade];
    if (IsEmptyStr([MenuTokenCompoments token])) {
        [self showLoginVC:NO];
    } else {
        [VoiceControlCompoments verifyLoginToken];
    }
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    [self.navigationController setNavigationBarHidden:YES animated:NO];
    [UIApplication sharedApplication].statusBarStyle = UIStatusBarStyleLightContent;
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    self.navigationController.interactivePopGestureRecognizer.enabled = NO;
}

- (void)loginExpiredNotificate {
    [MenuTokenCompoments updateToken:@""];
    [LocalUserComponents updateLocalUserModel:nil];
    [self showLoginVC:YES];
}

#pragma mark - Private Action

- (void)showLoginVC:(BOOL)isAnimation {
    MenuLoginViewController *loginVC = [[MenuLoginViewController alloc] init];
    loginVC.modalPresentationStyle = UIModalPresentationFullScreen;
    [self presentViewController:loginVC animated:isAnimation completion:^{

    }];
}

#pragma mark - Touch Action

- (void)scenesButtonAction {
    self.userViewController.view.hidden = YES;
    self.scenesViewController.view.hidden = NO;
    self.scenesButton.status = ButtonStatusActive;
    self.userButton.status = ButtonStatusNone;
    self.scenesButton.isAction = YES;
    self.userButton.isAction = NO;
}

- (void)userButtonAction {
    self.userViewController.view.hidden = NO;
    self.scenesViewController.view.hidden = YES;
    self.userButton.status = ButtonStatusActive;
    self.scenesButton.status = ButtonStatusNone;
    self.scenesButton.isAction = NO;
    self.userButton.isAction = YES;
}

#pragma mark - getter

- (ScenesViewController *)scenesViewController {
    if (!_scenesViewController) {
        _scenesViewController = [[ScenesViewController alloc] init];
    }
    return _scenesViewController;
}

- (UserViewController *)userViewController {
    if (!_userViewController) {
        _userViewController = [[UserViewController alloc] init];
    }
    return _userViewController;
}

- (MenuItemButton *)scenesButton {
    if (!_scenesButton) {
        _scenesButton = [[MenuItemButton alloc] init];
        _scenesButton.backgroundColor = [UIColor clearColor];
        [_scenesButton addTarget:self action:@selector(scenesButtonAction) forControlEvents:UIControlEventTouchUpInside];
        
        _scenesButton.imageEdgeInsets = UIEdgeInsetsMake(4, 0, 20, 0);
        _scenesButton.desTitle = @"主页";
        _scenesButton.isAction = NO;
        
        [_scenesButton bingImage:[UIImage imageNamed:@"menu_list"] status:ButtonStatusNone];
        [_scenesButton bingImage:[UIImage imageNamed:@"menu_list_s"] status:ButtonStatusActive];
    }
    return _scenesButton;
}

- (MenuItemButton *)userButton {
    if (!_userButton) {
        _userButton = [[MenuItemButton alloc] init];
        _userButton.backgroundColor = [UIColor clearColor];
        [_userButton addTarget:self action:@selector(userButtonAction) forControlEvents:UIControlEventTouchUpInside];
        
        _userButton.imageEdgeInsets = UIEdgeInsetsMake(4, 0, 20, 0);
        _userButton.desTitle = @"我的";
        _userButton.isAction = NO;
        
        [_userButton bingImage:[UIImage imageNamed:@"menu_user"] status:ButtonStatusNone];
        [_userButton bingImage:[UIImage imageNamed:@"menu_user_s"] status:ButtonStatusActive];
    }
    return _userButton;
}

- (MenuUpgradeCompoments *)upgradeCompoments {
    if (!_upgradeCompoments) {
        _upgradeCompoments = [[MenuUpgradeCompoments alloc] init];
    }
    return _upgradeCompoments;
}

@end
