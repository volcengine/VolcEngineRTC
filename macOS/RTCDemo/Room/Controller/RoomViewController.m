/**
 * VolcEngineRTC 视频通话的主页面
 * 本示例不限制房间内最大用户数；同时最多渲染四个用户的视频数据（自己和三个远端用户视频数据）；
 *
 * 包含如下简单功能：
 * - 创建引擎
 * - 设置视频发布参数
 * - 渲染自己的视频数据
 * - 加入音视频通话房间
 * - 打开/关闭麦克风
 * - 打开/关闭摄像头
 * - 渲染远端用户的视频数据
 * - 离开房间
 * - 销毁引擎
 *
 * 实现一个基本的音视频通话的流程如下：
 * 1.创建引擎 initWithAppId:delegate:parameters:
 * 2.设置编码参数 setVideoEncoderConfig:
 * 3.开启本地视频采集 :enableLocalVideo、startPreview:
 * 4.设置本地视频渲染视图 setLocalVideoCanvas:withCanvas:
 * 4.加入音视频通话房间 joinRoomByKey:roomId:roomProfile:userInfo:
 * 5.在收到远端用户视频首帧之后，设置用户的视频渲染视图 setRemoteVideoCanvas:withIndex:withCanvas:
 * 6.离开音视频通话房间 leaveRoom:
 * 7.销毁引擎 destroyEngine:
 *
 * 有以下常见的注意事项：
 * 1.本示例中，我们在 onFirstRemoteVideoFrameRendered:withFrameInfo: 这个事件中给远端用户设置远端用户视频渲染视图，这个回调表示的是收到了远端用户的视频第一帧。当然也可以在 onUserJoined:elapsed: 回调中设置远端用户视频渲染视图
 * 2.SDK 回调不在主线程，UI 操作需要切换线程
 * 3.用户成功加入房间后，SDK 会通过 onUserJoined:elapsed: 回调已经在房间的用户信息
 * 4.SDK 支持同时发布多个参数的视频流，接口是 setVideoEncoderConfig:
 * 5.加入房间时，需要有有效的 token，加入失败时会通过 onError: 输出对应的错误码
 * 6.用户可以通过 ByteRTCEngineKit 实例的joinRoomByKey:roomId:roomProfile:userInfo: 中的 roomProfile 来获得不同场景下的性能优化。本示例是音视频通话场景，因此使用 ByteRTCRoomProfileCommunication
 * 7.不需要在每次加入/退出房间时销毁引擎。本示例退出房间时销毁引擎是为了展示完整的使用流程
 *
 * 详细的API文档参见: https://www.volcengine.com/docs/6348/70092
 */

#import "RoomViewController.h"
#import "Masonry.h"
#import "NSColor+CorlorString.h"
#import "NSView+Snippet.h"
#import "NSLabel.h"
#import "RenderView.h"
#import "BottomView.h"
#import "Constants.h"

#import <VolcEngineRTC/objc/rtc/ByteRTCEngineKit.h>

@interface RoomViewController () <ByteRTCEngineDelegate>

@property (nonatomic, strong) NSView *navView;
@property (nonatomic, strong) RenderView *renderView;
@property (nonatomic, strong) BottomView *bottomView;
@property (nonatomic, copy) NSString *currentRoomID;
@property (nonatomic, copy) NSString *currentUid;
@property (nonatomic, strong) ByteRTCEngineKit *rtcEngineKit;

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
        self.rtcEngineKit = [[ByteRTCEngineKit alloc] initWithAppId:APPID
                                                           delegate:self
                                                         parameters:@{}];
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
        [wself.rtcEngineKit leaveRoom:^(ByteRTCRoomStats * _Nonnull stat) {
                    
        }];
        if (wself.clickBackBlock) {
            wself.clickBackBlock();
        }
    };
    self.bottomView.clickCameraBlock = ^(BOOL enable) {
        /// 开启/关闭本地视频采集
        if (enable) {
            [wself.rtcEngineKit  StartVideoCapture];
        }else{
            [wself.rtcEngineKit StopVideoCapture];
        }
    };
    self.bottomView.clickMicBlock = ^(BOOL enable) {
        /// 开启/关闭本地音频发送
        [wself.rtcEngineKit muteLocalAudio:!enable];
    };
    
    /// 设置视频发布参数
    ByteRTCVideoSolution *videoSolution = [[ByteRTCVideoSolution alloc] init];
    videoSolution.width = 640;
    videoSolution.height = 360;
    videoSolution.frameRate = 15;
    videoSolution.maxKbps = 800;
    [self.rtcEngineKit setVideoProfiles:@[videoSolution]];
    self.renderView.currentUid = self.currentUid;
    [self.renderView addUser:self.currentUid];
    /// 开启本地视频采集
    [wself.rtcEngineKit  StartVideoCapture];

    /// 开启本地音频采集
    [self.rtcEngineKit StartAudioCapture];

    ByteRTCUserInfo *userInfo = [[ByteRTCUserInfo alloc] init];
    userInfo.userId = self.currentUid;
    /// 加入房间
    [self.rtcEngineKit joinRoomByToken:TOKEN
                            roomId:self.currentRoomID
                          userInfo:userInfo
                       roomProfile:ByteRTCRoomProfileCommunication];
}

#pragma mark - ByteRTCEngineDelegate


- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine
    onJoinRoomResult:(NSString *_Nonnull)roomId
             withUid:(nonnull NSString *)uid
           errorCode:(NSInteger)errorCode
            joinType:(NSInteger)joinType
          elapsed:(NSInteger)elapsed {
    NSLog(@"onJoinRoomResult uid:%@  roomid:%@ errorcode:%ld",uid, roomId, (long)errorCode);
    if (errorCode != 0) {
        [self showAlert:[NSString stringWithFormat:@"error:%ld", (long)errorCode]];
    }
}

- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine firstRemoteVideoFrameOfUid:(NSString* _Nonnull )uid size:(CGSize)size elapsed:(NSInteger)elapsed {
    NSLog(@"firstRemoteVideoFrameOfUid uid:%@",uid);
    [self.renderView addUser:uid];
}

- (void)rtcEngine:(ByteRTCEngineKit *)engine onUserJoined:(ByteRTCUserInfo *)userInfo elapsed:(NSInteger)elapsed {
    NSLog(@"onUserJoined uid:%@", userInfo.userId);
}

- (void)rtcEngine:(ByteRTCEngineKit *)engine onUserLeave:(NSString *)uid reason:(ByteRTCUserOfflineReason)reason {
    NSLog(@"onUserLeave uid:%@", uid);
    [self.renderView removeUser:uid];
}

- (void)rtcEngine:(ByteRTCEngineKit *)engine onError:(ByteRTCErrorCode)errorCode {
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
        verLabel.font = [NSFont systemFontOfSize:16];;
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
        _renderView = [[RenderView alloc] initWithRTC:self.rtcEngineKit
                                             localUid:self.currentUid];
    }
    return _renderView;
}

- (void)dealloc {
    /// 销毁引擎
    [self.rtcEngineKit destroyEngine];
    self.rtcEngineKit = nil;
}

@end
