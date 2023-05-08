/**
 * VolcEngineRTC 音视频通话入口页面
 *
 * 包含如下简单功能：
 * - 该页面用来跳转至音视频通话主页面
 * - 校验房间名和用户名
 * - 展示当前 SDK 使用的版本号 ByteRTCEngineKit getSdkVersion:
 *
 * 有以下常见的注意事项：
 * 1.SDK 对房间名、用户名的限制是：非空且最大长度不超过128位的数字、大小写字母、@ . _ \ -
 */

#import "LoginViewController.h"
#import "RoomViewController.h"
#import "Masonry.h"
#import "Constants.h"
#import <VolcEngineRTC/objc/ByteRTCVideo.h>
#import <AVFoundation/AVCaptureDevice.h>


@interface LoginViewController ()<UITextFieldDelegate>
@property (nonatomic, strong) UITextField *roomIDTetxField;
@property (nonatomic, strong) UITextField *userIDTextField;
@property (nonatomic, strong) UIButton *enterRoomButton;
@property (nonatomic, strong) UILabel  *versionLabel;
@end

@implementation LoginViewController

- (void)viewDidLoad {
    [super viewDidLoad];
   
    [self buildUI];
    
    [self requestCameraAndAudioPermissions];
}


- (void)buildUI{
    [self.view addSubview:self.roomIDTetxField];
    [self.roomIDTetxField mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.mas_equalTo(20);
        make.top.equalTo(self.view.mas_bottom).multipliedBy(0.25);
        make.right.mas_equalTo(-20);
        make.height.mas_equalTo(44);
    }];
    
    [self.view addSubview:self.userIDTextField];
    [self.userIDTextField mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.mas_equalTo(20);
        make.top.equalTo(self.roomIDTetxField.mas_bottom).offset(20);
        make.right.mas_equalTo(-20);
        make.height.mas_equalTo(44);
    }];
    
    [self.view addSubview:self.enterRoomButton];
    [self.enterRoomButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.mas_equalTo(20);
        make.top.equalTo(self.userIDTextField.mas_bottom).offset(20);
        make.right.mas_equalTo(-20);
        make.height.mas_equalTo(44);
    }];
    
    [self.view addSubview:self.versionLabel];
    [self.versionLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.right.equalTo(self.view);
        make.bottom.equalTo(self.view).offset(-20);
    }];
}

- (void)requestCameraAndAudioPermissions{
  AVAuthorizationStatus videoStatus = [AVCaptureDevice authorizationStatusForMediaType:AVMediaTypeVideo];
  if (videoStatus == AVAuthorizationStatusAuthorized) {
    NSLog(@"Login- has camera permission");
  } else {
    [AVCaptureDevice requestAccessForMediaType:AVMediaTypeVideo completionHandler:^(BOOL granted) {
      if (granted) {
        NSLog(@"Login- request camera permission success.");
      }
    }];
  }

  AVAuthorizationStatus audioStatus = [AVCaptureDevice authorizationStatusForMediaType:AVMediaTypeAudio];
  if (audioStatus == AVAuthorizationStatusAuthorized) {
    NSLog(@"Login- has audio permission");
  } else {
    [AVCaptureDevice requestAccessForMediaType:AVMediaTypeAudio completionHandler:^(BOOL granted) {
      if (granted) {
        NSLog(@"Login- request audio permission success.");
      }
    }];
  }
}

#pragma mark - action

- (void)joinRoom:(UIButton *)button{
    [self.view endEditing:YES];
    
    NSString *roomID = self.roomIDTetxField.text;
    NSString *userID = self.userIDTextField.text;
    
    if (roomID.length == 0) {
        [self showAlertWithTitle:@"房间号不能为空" message:@""];
        return;;
    }
    
    if (userID.length == 0) {
        [self showAlertWithTitle:@"用户名不能为空" message:@""];
        return;;
    }
    
    // 校验合法性
    BOOL roomIDValid = [self checkVaild:roomID];
    BOOL userIDValid = [self checkVaild:userID];
    
    if (!roomIDValid) {
        [self showAlertWithTitle:@"输入不合法" message:@"只支持数字、大小写字母、@._-"];
        return;;
    }
    
    if (!userIDValid) {
        [self showAlertWithTitle:@"输入不合法" message:@"只支持数字、大小写字母、@._-"];
        return;;
    }
    
    RoomViewController *roomVC = [[RoomViewController alloc] init];
    roomVC.roomID = roomID;
    roomVC.userID = userID;
    roomVC.modalPresentationStyle = UIModalPresentationFullScreen;
    [self presentViewController:roomVC animated:YES completion:nil];
}

- (BOOL)checkVaild:(NSString *)string{
    NSRegularExpression *regex = [[NSRegularExpression alloc] initWithPattern:INPUT_REGEX options:0 error:nil];
   
    NSArray *results = [regex matchesInString:string options:0 range:NSMakeRange(0, string.length)];
    
    return results.count > 0;
}

- (void)showAlertWithTitle:(NSString *)title message:(NSString *)message {
    UIAlertController *alertVC = [UIAlertController alertControllerWithTitle:title message:message preferredStyle:UIAlertControllerStyleAlert];
    
    UIAlertAction *alertAction = [UIAlertAction actionWithTitle:@"确定" style:UIAlertActionStyleDefault handler:nil];
   
    [alertVC addAction:alertAction];
    
    [self presentViewController:alertVC animated:YES completion:nil];
}

- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event{
    [self.view endEditing:YES];
}
#pragma mark - getter

- (UITextField *)roomIDTetxField{
    if(!_roomIDTetxField){
        _roomIDTetxField = [[UITextField alloc] init];
        _roomIDTetxField.borderStyle = UITextBorderStyleRoundedRect;
        _roomIDTetxField.placeholder = @"请输入房间名";
        _roomIDTetxField.text = @"";
        _roomIDTetxField.delegate = self;
    }
    return _roomIDTetxField;
}

- (UITextField *)userIDTextField{
    if(!_userIDTextField){
        _userIDTextField = [[UITextField alloc] init];
        _userIDTextField.borderStyle = UITextBorderStyleRoundedRect;
        _userIDTextField.placeholder = @"请输入用户名";
        _userIDTextField.text = @"";
        _userIDTextField.delegate = self;
    }
    return _userIDTextField;
}

- (UIButton *)enterRoomButton{
    if(!_enterRoomButton){
        _enterRoomButton = [[UIButton alloc] init];
        [_enterRoomButton setTitle:@"加入房间" forState:UIControlStateNormal];
        _enterRoomButton.backgroundColor = [UIColor systemBlueColor];
        [_enterRoomButton addTarget:self action:@selector(joinRoom:) forControlEvents:UIControlEventTouchUpInside];
    }
    return _enterRoomButton;
}

- (UILabel *)versionLabel{
    if(!_versionLabel){
        _versionLabel = [[UILabel alloc] init];
        _versionLabel.textAlignment = NSTextAlignmentCenter;
        /// 获取当前SDK的版本号
        NSString *SDKVersion = [ByteRTCVideo getSDKVersion];
        _versionLabel.text = [NSString stringWithFormat:@"VolcEngineRTC v %@",SDKVersion];
    }
    return _versionLabel;
}
@end
