//
//  PreJoinSettingsViewController.m
//  Advanced
//
//  Created by bytedance on 2021/12/6.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import "PreJoinSettingsViewController.h"
#import "PreJoinNetViewController.h"
#import "PreNotifyViewController.h"
#import "SettingView.h"

@interface PreJoinSettingsViewController ()

@property (nonatomic, strong) SettingView *settingView;
@property (nonatomic, strong) SettingView *effectsView;
@property (nonatomic, strong) SettingView *detectionView;
@property (nonatomic, strong) SettingView *notifyView;

@end

@implementation PreJoinSettingsViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor whiteColor];
    
    // 采集渲染设定
    [self.view addSubview: self.settingView];
    [self.settingView mas_makeConstraints:^(MASConstraintMaker *make) {
        CGFloat topInset = 0;
        if (@available(iOS 11.0, *)) {
            topInset = [UIApplication sharedApplication].keyWindow.safeAreaInsets.top;
        }
        make.top.mas_equalTo(topInset + 44 + 30);
        make.left.right.equalTo(self.view);
        make.height.mas_equalTo(220);
    }];
    self.settingView.title = @"采集渲染设定";
    
    __weak typeof(self) weakSelf = self;
    
    BOOL useCustomCapture = self.preJoinSetting.useCustomCapture;
    SettingSwitchModel *externalSourceModel = [[SettingSwitchModel alloc] initWithDefaultStatus:useCustomCapture];
    externalSourceModel.title = @"外部源采集";
    [externalSourceModel setSwitchDidChangeStatus:^(BOOL isOn) {
        weakSelf.preJoinSetting.useCustomCapture = isOn;
    }];
    
    BOOL useCustomRender = self.preJoinSetting.useCustomRender;
    SettingSwitchModel *externalRenderModel = [[SettingSwitchModel alloc] initWithDefaultStatus:useCustomRender];
    externalRenderModel.title = @"外部源渲染";
    [externalRenderModel setSwitchDidChangeStatus:^(BOOL isOn) {
        weakSelf.preJoinSetting.useCustomRender = isOn;
    }];
    
    NSArray *renderModeArray = @[@"填充(Hidden)",@"适应(Fit)",@"拉伸(Stretch)"];
    NSInteger localRenderDefaultIndex = self.preJoinSetting.localRenderMode;
    SettingOptionArrayModel *localRenderModeModel = [[SettingOptionArrayModel alloc] initWithOptionArray:renderModeArray defaultIndex:localRenderDefaultIndex];
    localRenderModeModel.title = @"本地视图填充模式";
    [localRenderModeModel setDidSelectedIndex:^(NSInteger index, NSString * _Nonnull title) {
        weakSelf.preJoinSetting.localRenderMode = index;
    }];
    
    NSInteger remoteRenderDefaultIndex = self.preJoinSetting.remoteRenderMode;
    SettingOptionArrayModel *remoteRenderModeModel = [[SettingOptionArrayModel alloc] initWithOptionArray:renderModeArray defaultIndex:remoteRenderDefaultIndex];
    remoteRenderModeModel.title = @"远端视图填充模式";
    [remoteRenderModeModel setDidSelectedIndex:^(NSInteger index, NSString * _Nonnull title) {
        weakSelf.preJoinSetting.remoteRenderMode = index;
    }];
    
    self.settingView.dataArray = @[externalSourceModel,externalRenderModel,localRenderModeModel,remoteRenderModeModel];
    
    // 特效
    [self.view addSubview:self.effectsView];
    [self.effectsView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(self.settingView.mas_bottom).offset(20);
        make.left.right.equalTo(self.view);
        make.height.mas_equalTo(84);
    }];
    self.effectsView.title = @"特效";
    
    NSArray *effectsArray = @[@"火山美颜",@"无美颜"];
    NSInteger effectsDefault = self.preJoinSetting.effectsMode;
    SettingOptionArrayModel *effectsModel = [[SettingOptionArrayModel alloc] initWithOptionArray:effectsArray defaultIndex:effectsDefault];
    effectsModel.title = @"美颜方案";
    effectsModel.describe = @"火山方案：调用enableVideoEffect开启美颜贴纸特效";
    [effectsModel setDidSelectedIndex:^(NSInteger index, NSString * _Nonnull title) {
        weakSelf.preJoinSetting.effectsMode = index;
    }];
    
    self.effectsView.dataArray = @[effectsModel];
    
    // 进房前检测
    [self.view addSubview:self.detectionView];
    [self.detectionView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(self.effectsView.mas_bottom).offset(20);
        make.left.right.equalTo(self.view);
        make.height.mas_equalTo(84);
    }];
    self.detectionView.title = @"进房前检测";
    
    SettingButtonModel *netModel = [[SettingButtonModel alloc] initWithTitle:@"网络检测" describeStr:@""];
    __weak __typeof(self) wself = self;
    netModel.clickBlock = ^{
        PreJoinNetViewController *next = [[PreJoinNetViewController alloc] init];
        [wself.navigationController pushViewController:next animated:YES];
    };
    self.detectionView.dataArray = @[netModel];
    
    // 消息
    [self.view addSubview:self.notifyView];
    [self.notifyView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(self.detectionView.mas_bottom).offset(20);
        make.left.right.equalTo(self.view);
        make.height.mas_equalTo(84);
    }];
    self.notifyView.title = @"消息";
    
    SettingButtonModel *notifyModel = [[SettingButtonModel alloc] initWithTitle:@"房间外实时消息" describeStr:@""];
    notifyModel.clickBlock = ^{
        PreNotifyViewController *next = [[PreNotifyViewController alloc] init];
        [wself.navigationController pushViewController:next animated:YES];
    };
    self.notifyView.dataArray = @[notifyModel];
    
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    
    self.navigationController.navigationBarHidden = NO;
    if (@available(iOS 13.0, *)) {
        self.overrideUserInterfaceStyle = UIUserInterfaceStyleLight;
    } else {
        // Fallback on earlier versions
    }
}

- (void)back {
    [self.navigationController popViewControllerAnimated:YES];
}
    
#pragma mark - getter

- (SettingView *)settingView {
    if(!_settingView) {
        _settingView = [[SettingView alloc] init];
    }
    return _settingView;
}

- (SettingView *)effectsView {
    if (!_effectsView) {
        _effectsView = [[SettingView alloc] init];
    }
    return _effectsView;
}

- (SettingView *)detectionView {
    if (!_detectionView) {
        _detectionView = [[SettingView alloc] init];
    }
    return _detectionView;
}

- (SettingView *)notifyView {
    if (!_notifyView) {
        _notifyView = [[SettingView alloc] init];
    }
    return _notifyView;
}

@end
