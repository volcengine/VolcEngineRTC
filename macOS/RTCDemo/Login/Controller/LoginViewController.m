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
#import "LoginView.h"
#import "Masonry.h"
#import "NSColor+CorlorString.h"
#import "NSView+Snippet.h"
#import "NSLabel.h"
#import "Constants.h"
#import <VolcEngineRTC/objc/rtc/ByteRTCEngineKit.h>

@interface LoginViewController()

@property (nonatomic, strong) NSView *renderView;
@property (nonatomic, strong) LoginView *loginView;
@property (nonatomic, strong) NSView *navView;
@property (nonatomic, strong) NSLabel *verLabel;

@end

@implementation LoginViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    [self.view setBackgroundColor:[NSColor colorFromHexString:@"#C4C4C4"]];
    [self addViewAndMakeConstraints];
    
    __weak __typeof(self) wself = self;
    self.loginView.clickBlock = ^(NSString * _Nonnull roomID, NSString * _Nonnull userID) {
        if ([wself isMatchRoomID:roomID] &&
            [wself isMatchRoomID:userID]) {

            if (wself.joinRoomBlock) {
                wself.joinRoomBlock(roomID, userID);
            }
        } else {
            // error alert
            [wself showAlert];
        }
    };
}

#pragma mark - Private Action

- (void)addViewAndMakeConstraints {
    [self.view addSubview:self.renderView];
    [self.renderView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.bottom.right.equalTo(self.view);
        make.top.mas_equalTo(64);
    }];
    
    [self.navView addSubview:self.verLabel];
    [self.verLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerY.equalTo(self.navView);
        make.right.mas_equalTo(-22);
    }];
    
    [self.view addSubview:self.navView];
    [self.navView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.top.right.equalTo(self.view);
        make.bottom.equalTo(self.renderView.mas_top);
    }];
    
    [self.view addSubview:self.loginView];
    [self.loginView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(390, 365));
        make.center.equalTo(self.view);
    }];
}

- (BOOL)isMatchRoomID:(NSString *)roomid {
    if (roomid.length <= 0) {
        return NO;
    }
    if (roomid.length > 128) {
        return NO;
    }
    NSPredicate *predicate = [NSPredicate predicateWithFormat:@"SELF matches %@", INPUT_REGEX];
    return [predicate evaluateWithObject:roomid];
}

- (void)showAlert {
    NSAlert *alert = [[NSAlert alloc] init];
    alert.alertStyle = NSWarningAlertStyle;
    [alert addButtonWithTitle:@"确定"];
    alert.messageText = @"输入不合法";
    alert.informativeText = @"只支持数字、大小写字母、@._|-";
    [alert beginSheetModalForWindow:[NSApplication sharedApplication].keyWindow completionHandler:^(NSModalResponse returnCode) {

    }];
}

#pragma mark - getter

- (LoginView *)loginView {
    if (!_loginView) {
        _loginView = [[LoginView alloc] init];
        _loginView.wantsLayer = YES;
        _loginView.layer.cornerRadius = 8;
        _loginView.layer.masksToBounds = YES;
    }
    return _loginView;
}

- (NSLabel *)verLabel {
    if (!_verLabel) {
        _verLabel = [[NSLabel alloc] init];
        _verLabel.font = [NSFont systemFontOfSize:12];
        /// 获取当前SDK的版本号
        NSString *version = [ByteRTCEngineKit getSdkVersion];
        _verLabel.text = [@"VolcEngineRTC v" stringByAppendingString:version];
        _verLabel.textColor = [NSColor colorFromHexString:@"#FFFFFF"];
    }
    return _verLabel;
}

- (NSView *)navView {
    if (!_navView) {
        _navView = [[NSView alloc] init];
        [_navView setBackgroundColor:[NSColor colorFromHexString:@"#0A1E39"]];
    }
    return _navView;
}

- (NSView *)renderView {
    if (!_renderView) {
        _renderView = [[NSView alloc] init];
    }
    return _renderView;
}

- (void)dealloc {
    
}

@end
