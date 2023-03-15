/**
 * VolcEngineRTC 视频通话的主页面
 * 本示例不限制房间内最大用户数；同时最多渲染四个用户的视频数据（自己和三个远端用户视频数据）；
 *
 * 包含如下简单功能：
 * - 创建引擎
 * - 设置视频发布参数
 * - 渲染自己的视频数据
 * - 创建房间
 * - 加入音视频通话房间
 * - 打开/关闭麦克风
 * - 打开/关闭摄像头
 * - 渲染远端用户的视频数据
 * - 离开房间
 * - 销毁引擎
 *
 * 实现一个基本的音视频通话的流程如下：
 * 1.创建 IRTCVideo 实例。
 *   + (ByteRTCVideo * _Nullable) createRTCVideo:(NSString * _Nonnull)appId
 *                                      delegate:(id<ByteRTCVideoDelegate> _Nullable)delegate
 *                                    parameters:(NSDictionary * _Nonnull)parameters;
 * 2.视频发布端设置期望发布的最大分辨率视频流参数，包括分辨率、帧率、码率、缩放模式、网络不佳时的回退策略等。
 *   - (int)SetMaxVideoEncoderConfig:(ByteRTCVideoEncoderConfig * _Nullable) max_solution;
 * 3.开启本地视频采集。 - (void)startVideoCapture;
 * 4.设置本地视频渲染时，使用的视图，并设置渲染模式。
 *   - (int)setLocalVideoCanvas:(ByteRTCStreamIndex)streamIndex
 *                   withCanvas:(ByteRTCVideoCanvas * _Nullable)canvas;
 * 5.创建房间。- ( ByteRTCRoom * _Nullable)createRTCRoom:(NSString * _Nonnull)roomId;
 * 6.加入音视频通话房间。
 *   - (int)joinRoomByToken:(NSString *_Nullable)token
 *                 userInfo:(ByteRTCUserInfo *_Nonnull)userInfo
 *               roomConfig:(ByteRTCRoomConfig *_Nonnull)roomConfig;
 * 7.SDK 接收并解码远端视频流首帧后，设置用户的视频渲染视图。
 *   - (int)setRemoteVideoCanvas:(NSString * _Nonnull)uid
 *                     withIndex:(ByteRTCStreamIndex)streamIndex
 *                    withCanvas:(ByteRTCVideoCanvas * _Nullable)canvas;
 * 8.在用户离开房间之后移出用户的视频渲染视图。
 * 9.离开音视频通话房间，调用 ByteRTCRoom 实例的 (int)leaveRoom
 * 10.调用 ByteRTCRoom 实例的 (void)destroy 销毁房间对象。
 * 11.调用 ByteRTCVideo  + (void)destroyRTCVideo 销毁引擎。
 *
 * 详细的API文档参见: https://www.volcengine.com/docs/6348/70092
 */

#import "BottomView.h"
#import "Constants.h"
#import "Masonry.h"
#import "NSColor+CorlorString.h"
#import "NSLabel.h"
#import "NSView+Snippet.h"
#import "RenderView.h"
#import "RoomViewController.h"

#import <VolcEngineRTC/VolcEngineRTC.h>

@interface RoomViewController () <ByteRTCVideoDelegate, ByteRTCRoomDelegate>

@property (nonatomic, strong) NSView *navView;
@property (nonatomic, strong) RenderView *renderView;
@property (nonatomic, strong) BottomView *bottomView;
@property (nonatomic, copy) NSString *currentRoomID;
@property (nonatomic, copy) NSString *currentUid;
@property (nonatomic, strong) ByteRTCVideo *videoEngine;
@property (nonatomic, strong) ByteRTCRoom *room;

@end

@implementation RoomViewController

- (instancetype)initWithNibName:(NSNibName)nibNameOrNil
                         bundle:(NSBundle *)nibBundleOrNil
                         roomID:(NSString *)roomid
                            uid:(NSString *)uid {
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        _currentRoomID = roomid;
        _currentUid = uid;
        /// 创建引擎
        self.videoEngine = [ByteRTCVideo createRTCVideo:APPID delegate:self parameters:@{}];
    }
    return self;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    [self.view setBackgroundColor:[NSColor colorFromHexString:@"#C4C4C4"]];
    [self addViewAndMakeConstraints];

    __weak __typeof(self) wself = self;
    self.bottomView.clickCancelBlock = ^{
      /// 离开房间

        [wself.room leaveRoom];

        if (wself.clickBackBlock) {
            wself.clickBackBlock();
        }
    };
    self.bottomView.clickCameraBlock = ^(BOOL enable) {
        /// 开启/关闭本地视频采集
        if (enable) {
            [wself.videoEngine startVideoCapture];
        } else {
            [wself.videoEngine stopVideoCapture];
        }
    };
    self.bottomView.clickMicBlock = ^(BOOL enable) {
        /// 开启/关闭本地音频发送
        if (enable) {
            [wself.room publishStream:ByteRTCMediaStreamTypeAudio];
        } else {
            [wself.room unpublishStream:ByteRTCMediaStreamTypeAudio];
        }
    };

    /// 设置视频发布参数
    ByteRTCVideoEncoderConfig *config = [[ByteRTCVideoEncoderConfig alloc] init];
    config.width = 640;
    config.height = 360;
    config.frameRate = 15;
    config.maxBitrate = 800;
    config.encoderPreference = ByteRTCVideoEncoderPreferenceDisabled;

    [self.videoEngine SetMaxVideoEncoderConfig:config];

    self.renderView.currentUid = self.currentUid;
    [self.renderView addUser:self.currentUid roomid:self.currentRoomID];
    /// 开启本地视频采集
    [wself.videoEngine startVideoCapture];

    /// 开启本地音频采集
    [self.videoEngine startAudioCapture];

    ByteRTCUserInfo *userInfo = [[ByteRTCUserInfo alloc] init];
    userInfo.userId = self.currentUid;

    ByteRTCRoomConfig *roomConfig = [[ByteRTCRoomConfig alloc] init];
    roomConfig.profile = ByteRTCRoomProfileCommunication;
    roomConfig.isAutoPublish = YES;
    roomConfig.isAutoSubscribeAudio = YES;
    roomConfig.isAutoSubscribeVideo = YES;

    /// 加入房间
    self.room = [self.videoEngine createRTCRoom:self.currentRoomID];
    [self.room setDelegate:self];

    int code = [self.room joinRoomByToken:TOKEN userInfo:userInfo roomConfig:roomConfig];
    if (code != 0) {
        [self showAlert:@"加入房间失败"];
    }
}

#pragma mark - ByteRTCEngineDelegate

- (void)rtcRoom:(ByteRTCRoom *)rtcRoom onRoomStateChanged:(NSString *)roomId withUid:(NSString *)uid state:(NSInteger)state extraInfo:(NSString *)extraInfo {
}

- (void)rtcEngine:(ByteRTCVideo *)engine onFirstRemoteVideoFrameDecoded:(ByteRTCRemoteStreamKey *)streamKey withFrameInfo:(ByteRTCVideoFrameInfo *)frameInfo {
    [self.renderView addUser:streamKey.userId roomid:self.currentRoomID];
}

- (void)rtcRoom:(ByteRTCRoom *)rtcRoom onUserJoined:(ByteRTCUserInfo *)userInfo elapsed:(NSInteger)elapsed {
    NSLog(@"onUserJoined uid:%@", userInfo.userId);
}

- (void)rtcRoom:(ByteRTCRoom *)rtcRoom onUserLeave:(NSString *)uid reason:(ByteRTCUserOfflineReason)reason {
    NSLog(@"onUserLeave uid:%@", uid);
    [self.renderView removeUser:uid roomid:self.currentRoomID];
}

- (void)rtcRoom:(ByteRTCRoom *)rtcRoom onRoomError:(ByteRTCErrorCode)errorCode {
    NSLog(@"onError uid:%ld", (long)errorCode);
    [self showAlert:[NSString stringWithFormat:@"error:%ld", (long)errorCode]];
}

#pragma mark - Private Action

- (void)showAlert:(NSString *)message {
    dispatch_async(dispatch_get_main_queue(), ^{
        NSAlert *alert = [NSAlert new];
        [alert addButtonWithTitle:@"知道了"];
        [alert setMessageText:message];
        [alert setAlertStyle:NSWarningAlertStyle];
        [alert runModal];
    });
}

- (void)addViewAndMakeConstraints {
    [self.view addSubview:self.navView];
    [self.navView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.top.right.equalTo(self.view);
        make.height.mas_equalTo(64);
    }];

    [self.view addSubview:self.renderView];
    [self.renderView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.bottom.right.equalTo(self.view);
        make.top.equalTo(self.navView.mas_bottom);
    }];

    [self.view addSubview:self.bottomView];
    [self.bottomView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerX.equalTo(self.view);
        make.bottom.mas_equalTo(-64);
        make.size.mas_equalTo(CGSizeMake(348, 59));
    }];
}

#pragma mark - getter

- (NSView *)navView {
    if (!_navView) {
        _navView = [[NSView alloc] init];
        [_navView setBackgroundColor:[NSColor colorFromHexString:@"#0A1E39"]];

        NSLabel *verLabel = [[NSLabel alloc] init];
        verLabel.font = [NSFont systemFontOfSize:16];
        
        verLabel.text = self.currentRoomID;
        verLabel.textColor = [NSColor colorFromHexString:@"#FFFFFF"];
        [_navView addSubview:verLabel];
        [verLabel mas_makeConstraints:^(MASConstraintMaker *make) {
            make.center.equalTo(_navView);
        }];
    }
    return _navView;
}

- (BottomView *)bottomView {
    if (!_bottomView) {
        _bottomView = [[BottomView alloc] init];
        [_bottomView setBackgroundColor:[NSColor colorFromHexString:@"#36393F"]];
        _bottomView.wantsLayer = YES;
        _bottomView.layer.cornerRadius = 29.5;
        _bottomView.layer.masksToBounds = YES;
    }
    return _bottomView;
}

- (RenderView *)renderView {
    if (!_renderView) {
        _renderView = [[RenderView alloc] initWithRTC:self.videoEngine
                                             localUid:self.currentUid];
    }
    return _renderView;
}

- (void)dealloc {
    /// 销毁房间
    [self.room destroy];
    /// 销毁引擎
    [ByteRTCVideo destroyRTCVideo];
    self.videoEngine = nil;
    self.room = nil;
}

@end
