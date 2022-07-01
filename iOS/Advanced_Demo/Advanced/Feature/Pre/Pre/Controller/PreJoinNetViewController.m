//
//  PreJoinNetViewController.m
//  Advanced
//
//  Created by bytedance on 2022/3/15.
//

#import "PreJoinNetViewController.h"
#import "PreJoinNetResultViewController.h"
#import "SettingView.h"

@interface PreJoinNetViewController ()

@property (nonatomic, strong) SettingView *settingView;
@property (nonatomic, strong) UIButton *startButton;

@property (nonatomic, weak) SettingSwitchModel *uplinkmodel;
@property (nonatomic, weak) SettingSwitchModel *downlinkModel;
@property (nonatomic, weak) SettingTextFieldModel *upLinkFieldModel;
@property (nonatomic, weak) SettingTextFieldModel *downLinkFieldModel;

@end

@implementation PreJoinNetViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor whiteColor];
    
    CGFloat bottomInset = 0;
    if (@available(iOS 11.0, *)) {
        bottomInset = [UIApplication sharedApplication].keyWindow.safeAreaInsets.bottom;
    }
    [self.view addSubview:self.startButton];
    [self.startButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.mas_equalTo(20);
        make.bottom.equalTo(self.view).offset(-bottomInset - 20);
        make.right.mas_equalTo(-20);
        make.height.mas_equalTo(44);
    }];
    
    [self.view addSubview:self.settingView];
    [self.settingView mas_makeConstraints:^(MASConstraintMaker *make) {
        CGFloat topInset = 0;
        if (@available(iOS 11.0, *)) {
            topInset = [UIApplication sharedApplication].keyWindow.safeAreaInsets.top;
        }
        make.top.mas_equalTo(topInset + 44 + 30);
        make.left.right.equalTo(self.view);
        make.height.mas_equalTo(220);
    }];
    self.settingView.title = @"网络检测";
    
    BOOL isUplink = YES;
    SettingSwitchModel *uplinkmodel = [[SettingSwitchModel alloc] initWithDefaultStatus:isUplink];
    uplinkmodel.title = @"上行带宽探测";
    
    SettingTextFieldModel *upLinkFieldModel = [[SettingTextFieldModel alloc] initWithTitle:@"上行带宽探测目标码率" defaultStr:@"10000"];
    upLinkFieldModel.alertTitle = @"目标码率";
    upLinkFieldModel.alertMessage = @"默认值：由SDK自动上探最高码率（10000 kbps）";
    upLinkFieldModel.unit = @"kbps";
    upLinkFieldModel.placeholders = @[@"10000"];
    __weak SettingTextFieldModel *weakUpLinkFieldModel = upLinkFieldModel;
    upLinkFieldModel.inputBlock = ^(NSInteger index, NSString * _Nonnull valueStr) {
        weakUpLinkFieldModel.describe = valueStr;
    };
    
    BOOL isDownlink = YES;
    SettingSwitchModel *downlinkModel = [[SettingSwitchModel alloc] initWithDefaultStatus:isDownlink];
    downlinkModel.title = @"下行带宽探测";
    
    SettingTextFieldModel *downLinkFieldModel = [[SettingTextFieldModel alloc] initWithTitle:@"下行带宽探测目标码率" defaultStr:@"10000"];
    downLinkFieldModel.alertTitle = @"目标码率";
    downLinkFieldModel.alertMessage = @"默认值：由SDK自动上探最高码率（10000 kbps）";
    downLinkFieldModel.unit = @"kbps";
    downLinkFieldModel.placeholders = @[@"10000"];
    __weak SettingTextFieldModel *weakDownLinkFieldModel = downLinkFieldModel;
    downLinkFieldModel.inputBlock = ^(NSInteger index, NSString * _Nonnull valueStr) {
        weakDownLinkFieldModel.describe = valueStr;
    };
    
    self.settingView.dataArray =
    @[uplinkmodel,upLinkFieldModel,
      downlinkModel,downLinkFieldModel];
    
    _uplinkmodel = uplinkmodel;
    _upLinkFieldModel = upLinkFieldModel;
    _downlinkModel = downlinkModel;
    _downLinkFieldModel = downLinkFieldModel;
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    
    self.navigationController.navigationBarHidden = NO;
}

- (void)back {
    [self.navigationController popViewControllerAnimated:YES];
}

- (void)startButtonAction {
    PreJoinNetResultViewController *next = [[PreJoinNetResultViewController alloc] init];
    next.isUplink = _uplinkmodel.isOn;
    next.isDownlink = _downlinkModel.isOn;
    next.uplinkBandwidth = [_upLinkFieldModel.describe integerValue];
    next.downlinkBandwidth = [_downLinkFieldModel.describe integerValue];
    [self.navigationController pushViewController:next animated:YES];
}

#pragma mark - Getter

- (SettingView *)settingView {
    if(!_settingView) {
        _settingView = [[SettingView alloc] init];
    }
    return _settingView;
}

- (UIButton *)startButton {
    if(!_startButton){
        _startButton = [[UIButton alloc] init];
        [_startButton setTitle:@"开始检测" forState:UIControlStateNormal];
        _startButton.backgroundColor = [UIColor systemBlueColor];
        [_startButton addTarget:self action:@selector(startButtonAction) forControlEvents:UIControlEventTouchUpInside];
    }
    return _startButton;
}

@end
