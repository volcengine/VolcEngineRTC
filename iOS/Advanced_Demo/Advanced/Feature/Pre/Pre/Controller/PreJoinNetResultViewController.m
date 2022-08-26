//
//  PreJoinNetResultViewController.m
//  Advanced
//
//

#import "PreJoinNetResultViewController.h"
#import "SettingView.h"
#import "Constants.h"
#import <VolcEngineRTC/objc/rtc/ByteRTCEngineKit.h>

@interface PreJoinNetResultViewController () <ByteRTCEngineDelegate>

@property (nonatomic, strong) SettingView *upLinkView;
@property (nonatomic, strong) SettingView *downLinkView;
@property (nonatomic, strong) UIButton *endButton;
@property (nonatomic, strong) ByteRTCEngineKit *rtcKit;

@end

@implementation PreJoinNetResultViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor whiteColor];
    
    // 上行
    [self.view addSubview:self.upLinkView];
    [self.upLinkView mas_makeConstraints:^(MASConstraintMaker *make) {
        CGFloat topInset = 0;
        if (@available(iOS 11.0, *)) {
            topInset = [UIApplication sharedApplication].keyWindow.safeAreaInsets.top;
        }
        make.top.mas_equalTo(topInset + 44 + 30);
        make.left.right.equalTo(self.view);
        make.height.mas_equalTo(280);
    }];
    self.upLinkView.title = @"上行网络";
    
    SettingLabelModel *label1_1 = [[SettingLabelModel alloc] initWithTitle:@"网络质量" describeStr:@""];
    SettingLabelModel *label1_2 = [[SettingLabelModel alloc] initWithTitle:@"RTT" describeStr:@""];
    SettingLabelModel *label1_3 = [[SettingLabelModel alloc] initWithTitle:@"丢包率" describeStr:@""];
    SettingLabelModel *label1_4 = [[SettingLabelModel alloc] initWithTitle:@"带宽" describeStr:@""];
    SettingLabelModel *label1_5 = [[SettingLabelModel alloc] initWithTitle:@"抖动" describeStr:@""];
    
    self.upLinkView.dataArray =
    @[label1_1,label1_2,label1_3,label1_4,label1_5];
    
    // 下行
    [self.view addSubview:self.downLinkView];
    [self.downLinkView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(self.upLinkView.mas_bottom).offset(20);
        make.bottom.left.right.equalTo(self.view);
    }];
    self.downLinkView.title = @"下行网络";
    
    SettingLabelModel *label2_1 = [[SettingLabelModel alloc] initWithTitle:@"网络质量" describeStr:@""];
    SettingLabelModel *label2_2 = [[SettingLabelModel alloc] initWithTitle:@"RTT" describeStr:@""];
    SettingLabelModel *label2_3 = [[SettingLabelModel alloc] initWithTitle:@"丢包率" describeStr:@""];
    SettingLabelModel *label2_4 = [[SettingLabelModel alloc] initWithTitle:@"带宽" describeStr:@""];
    SettingLabelModel *label2_5 = [[SettingLabelModel alloc] initWithTitle:@"抖动" describeStr:@""];
    self.downLinkView.dataArray =
    @[label2_1,label2_2,label2_3,label2_4,label2_5];
    
    CGFloat bottomInset = 0;
    if (@available(iOS 11.0, *)) {
        bottomInset = [UIApplication sharedApplication].keyWindow.safeAreaInsets.bottom;
    }
    [self.view addSubview:self.endButton];
    [self.endButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.mas_equalTo(20);
        make.bottom.equalTo(self.view).offset(-bottomInset - 20);
        make.right.mas_equalTo(-20);
        make.height.mas_equalTo(44);
    }];
    
    // 开启检测
    self.rtcKit = [[ByteRTCEngineKit alloc] initWithAppId:APPID delegate:self parameters:nil];
    ByteRTCNetworkDetectionStartReturn startReturn = [self.rtcKit startNetworkDetection:_isUplink
                       uplinkBandwidth:(int)_uplinkBandwidth
                              downlink:_isDownlink
                     downlinkBandwidth:(int)_downlinkBandwidth];
    if (startReturn == ByteRTCNetworkDetectionStartReturnSuccess) {
        NSLog(@"%s-Success",__func__);
    } else {
        NSLog(@"%s-Fail",__func__);
        NSString *message = [NSString stringWithFormat:@"开启失败code:%ld", (long)startReturn];
        [self showAlertWith:message];
    }
}

- (void)showAlertWith:(NSString *)message{
    UIAlertController *alertVC = [UIAlertController alertControllerWithTitle:message message:@"" preferredStyle:UIAlertControllerStyleAlert];
    
    UIAlertAction *alertAction = [UIAlertAction actionWithTitle:@"确定" style:UIAlertActionStyleDefault handler:nil];
   
    [alertVC addAction:alertAction];
    
    [self presentViewController:alertVC animated:YES completion:nil];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    
    self.navigationController.navigationBarHidden = NO;
}

- (void)back {
    [self.navigationController popViewControllerAnimated:YES];
}

- (void)endButtonAction {
    [self.rtcKit stopNetworkDetection];
    [self back];
}

#pragma mark - ByteRTCEngineDelegate

- (void)rtcEngine:(ByteRTCEngineKit *)engine onNetworkDetectionResult:(ByteRTCNetworkDetectionLinkType)type quality:(ByteRTCNetworkQuality)quality rtt:(int)rtt lostRate:(double)lost_rate bitrate:(int)bitrate jitter:(int)jitter {
    dispatch_async(dispatch_get_main_queue(), ^{
        BOOL isUpLink = (type == ByteRTCNetworkDetectionLinkTypeUp) ? YES : NO;
        
        [self updateView:isUpLink
                 quality:[self getStrWithQuality:quality]
                     rtt:rtt
                lostRate:lost_rate
                 bitrate:bitrate
                  jitter:jitter];
    });
}


#pragma mark - Private Action

- (void)updateView:(BOOL)isUplink
           quality:(NSString *)quality
               rtt:(int)rtt
          lostRate:(double)lost_rate
           bitrate:(int)bitrate
            jitter:(int)jitter {
    if (isUplink) {
        for (int i = 0; i < self.upLinkView.dataArray.count; i++) {
            SettingLabelModel *labelModel = self.upLinkView.dataArray[i];
            switch (i) {
                case 0:
                    labelModel.describe = quality;
                    break;
                case 1:
                    labelModel.describe = [NSString stringWithFormat:@"%dms", rtt];
                    break;
                case 2:
                    labelModel.describe = [NSString stringWithFormat:@"%.2f%%", lost_rate * 100];
                    break;
                case 3:
                    labelModel.describe = [NSString stringWithFormat:@"%dkbps", bitrate];
                    break;
                case 4:
                    labelModel.describe = [NSString stringWithFormat:@"%dms", jitter];
                    break;
                    
                default:
                    labelModel.describe = @"";
                    break;
            }
        }
        [self.upLinkView reloadData];
    } else {
        for (int i = 0; i < self.downLinkView.dataArray.count; i++) {
            SettingLabelModel *labelModel = self.downLinkView.dataArray[i];
            switch (i) {
                case 0:
                    labelModel.describe = quality;
                    break;
                case 1:
                    labelModel.describe = [NSString stringWithFormat:@"%dms", rtt];
                    break;
                case 2:
                    labelModel.describe = [NSString stringWithFormat:@"%.2f%%", lost_rate * 100];
                    break;
                case 3:
                    labelModel.describe = [NSString stringWithFormat:@"%dkbps", bitrate];
                    break;
                case 4:
                    labelModel.describe = [NSString stringWithFormat:@"%dms", jitter];
                    break;
                    
                default:
                    labelModel.describe = @"";
                    break;
            }
        }
        [self.downLinkView reloadData];
    }
}

- (NSString *)getStrWithQuality:(ByteRTCNetworkQuality)quality {
    NSString *str = @"";
    switch (quality) {
        case ByteRTCNetworkQualityUnknown:
            str = @"Unknown";
            break;
        case ByteRTCNetworkQualityExcellent:
            str = @"Excellent";
            break;
        case ByteRTCNetworkQualityGood:
            str = @"Good";
            break;
        case ByteRTCNetworkQualityVeryBad:
            str = @"VeryBad";
            break;
        case ByteRTCNetworkQualityBad:
            str = @"Bad";
            break;
        case ByteRTCNetworkQualityPoor:
            str = @"Poor";
            break;
            
        default:
            break;
    }
    return str;
}

#pragma mark - getter

- (SettingView *)upLinkView {
    if(!_upLinkView) {
        _upLinkView = [[SettingView alloc] init];
    }
    return _upLinkView;
}

- (SettingView *)downLinkView {
    if(!_downLinkView) {
        _downLinkView = [[SettingView alloc] init];
    }
    return _downLinkView;
}

- (UIButton *)endButton {
    if(!_endButton){
        _endButton = [[UIButton alloc] init];
        [_endButton setTitle:@"结束检测" forState:UIControlStateNormal];
        _endButton.backgroundColor = [UIColor systemBlueColor];
        [_endButton addTarget:self action:@selector(endButtonAction) forControlEvents:UIControlEventTouchUpInside];
    }
    return _endButton;
}

- (void)dealloc {
    [self.rtcKit destroyEngine];
    self.rtcKit = nil;
}

@end
