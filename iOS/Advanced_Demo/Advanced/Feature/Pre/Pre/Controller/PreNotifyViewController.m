//
//  PreNotifyViewController.m
//  Advanced
//
//

#import <VolcEngineRTC/objc/rtc/ByteRTCEngineKit.h>
#import "PreNotifyViewController.h"
#import "SettingView.h"
#import "Constants.h"

@interface PreNotifyViewController () <ByteRTCEngineDelegate>

@property (nonatomic, strong) SettingView *settingView;

@property (nonatomic, strong) ByteRTCEngineKit *rtcKit;

@end

@implementation PreNotifyViewController

- (instancetype)init {
    self = [super init];
    if (self) {
        self.rtcKit = [[ByteRTCEngineKit alloc] initWithAppId:APPID delegate:self parameters:nil];
    }
    return self;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor whiteColor];
    
    [self.view addSubview:self.settingView];
    [self.settingView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.mas_equalTo([DeviceInforTool getStatusBarHight] + 44 + 30);
        make.left.right.equalTo(self.view);
        make.height.mas_equalTo(220);
    }];
    self.settingView.title = @"房间外实时消息";
    
    __weak __typeof(self) wself = self;
    SettingTextFieldModel *userIDFieldModel = [[SettingTextFieldModel alloc] initWithTitle:@"Login UserID" defaultStr:@""];
    userIDFieldModel.alertTitle = @"Login UserID";
    userIDFieldModel.alertMessage = @"发送房间外消息前，需要 Login，\nLogin UID 可以和 joinRoom UID 不一致。";
    userIDFieldModel.placeholders = @[@"Login UserID"];
    __weak SettingTextFieldModel *weakuserIDFieldModel = userIDFieldModel;
    userIDFieldModel.inputBlock = ^(NSInteger index, NSString * _Nonnull valueStr) {
        [wself login:@"" uid:valueStr];
    };
    
    SettingTextFieldModel *notifyFieldModel = [[SettingTextFieldModel alloc] initWithTitle:@"点对点消息" defaultStr:@""];
    notifyFieldModel.alertTitle = @"发送点对点消息";
    notifyFieldModel.alertMessage = @"您可以使用点对点消息实现多种场景，如呼叫，邀请等";
    notifyFieldModel.placeholders = @[@"接收用户ID",@"消息"];
    __block NSString *uid = @"";
    notifyFieldModel.inputBlock = ^(NSInteger index, NSString * _Nonnull valueStr) {
        if (index == 0) {
            uid = valueStr;
        } else if (index == 1) {
            [wself sendUserMessageOutsideRoom:uid
                                      message:valueStr];
        }
    };
    
    SettingButtonModel *logoutModel = [[SettingButtonModel alloc] initWithTitle:@"Logout" describeStr:@""];
    logoutModel.clickBlock = ^{
        [wself logout];
    };
    
    self.settingView.dataArray = @[userIDFieldModel,
                                   notifyFieldModel,
                                   logoutModel];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    
    self.navigationController.navigationBarHidden = NO;
}

- (void)back {
    [self.navigationController popViewControllerAnimated:YES];
}

#pragma mark - Private Action

- (void)login:(NSString *)token uid:(NSString *)uid {
    [_rtcKit login:token uid:uid];
}

- (void)sendUserMessageOutsideRoom:(NSString *)uid
                           message:(NSString *)message {
    [_rtcKit sendUserMessageOutsideRoom:uid message:message config:0];
}

- (void)logout {
    [_rtcKit logout];
}

#pragma mark - ByteRTCEngineDelegate

- (void)rtcEngine:(ByteRTCEngineKit *)engine onUserMessageSendResultOutsideRoom:(int64_t)msgid error:(ByteRTCUserMessageSendResult)error {
    NSString *message = @"";
    if (error == ByteRTCUserMessageSendResultSuccess) {
        message = @"点对点消息发送成功";
    } else {
        message =
        [NSString stringWithFormat:@"点对点消息发送失败（%ld）", (long)error];
    }
    [[ToastComponents shareToastComponents] showWithMessage:message];
}

- (void)rtcEngine:(ByteRTCEngineKit *)engine onUserMessageReceivedOutsideRoom:(NSString * _Nonnull)uid message:(NSString * _Nonnull)message {
    NSString *str = [NSString stringWithFormat:@"接收到房间外实时消息：%@：%@",uid,message];
    [[ToastComponents shareToastComponents] showWithMessage:str];
}

- (void)rtcEngine:(ByteRTCEngineKit *)engine onLoginResult:(NSString *)uid errorCode:(ByteRTCLoginErrorCode)errorCode elapsed:(NSInteger)elapsed {
    dispatch_async(dispatch_get_main_queue(), ^{
        NSString *message = @"";
        if (errorCode == ByteRTCLoginErrorCodeSuccess) {
            message = @"Login 成功";
            SettingTextFieldModel *userIDFieldModel = self.settingView.dataArray[0];
            userIDFieldModel.describe = uid;
            [self.settingView reloadData];
        } else {
            message =
            [NSString stringWithFormat:@"Login 失败（%ld）", (long)errorCode];
        }
        [[ToastComponents shareToastComponents] showWithMessage:message];
    });
}

- (void)rtcEngineOnLogout:(ByteRTCEngineKit *)engine {
    dispatch_async(dispatch_get_main_queue(), ^{
        SettingTextFieldModel *userIDFieldModel = self.settingView.dataArray[0];
        userIDFieldModel.describe = @"";
        [self.settingView reloadData];
        [[ToastComponents shareToastComponents]
         showWithMessage:@"Logout 成功"];
    });
}

#pragma mark - Getter

- (SettingView *)settingView {
    if(!_settingView) {
        _settingView = [[SettingView alloc] init];
    }
    return _settingView;
}

- (void)dealloc {
    [self.rtcKit destroyEngine];
    self.rtcKit = nil;
}

@end
