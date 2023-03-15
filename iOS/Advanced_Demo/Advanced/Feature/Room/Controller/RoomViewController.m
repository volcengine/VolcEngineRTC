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
 * 9.离开音视频通话房间，- (int)leaveRoom;
 * 10.调用 ByteRTCRoom 实例的 - (void)destroy; 销毁房间对象。
 * 11.调用 ByteRTCVideo  + (void)destroyRTCVideo; 销毁引擎。
 *
 * 详细的API文档参见: https://www.volcengine.com/docs/6348/70086
 */
#import "RoomViewController.h"
#import "Masonry.h"
#import "UserLiveView.h"
#import "RoomSettingView.h"
#import "Constants.h"
#import "CustomCameraCapture.h"
#import "CustomVideoRenderView.h"
#import "BeautyBarView.h"
#import "VolcBeautyCommon.h"
#import "ToastComponents.h"
#import <VolcEngineRTC/objc/ByteRTCVideo.h>
#import <VolcEngineRTC/objc/ByteRTCRoom.h>
#import "SystemAuthority.h"

@interface RoomViewController ()<ByteRTCRoomDelegate, ByteRTCVideoDelegate, BeautyBarViewDelegate, CustomCameraCaptureDelegate>
@property (nonatomic, strong) UIView *headerView;
@property (nonatomic, strong) UIButton *switchCameraBtn;
@property (nonatomic, strong) UILabel *roomIdLabel;
@property (nonatomic, strong) UIButton *switchAudioRouteBtn;
@property (nonatomic, strong) UIView *foooterView;
@property (nonatomic, strong) UIView *footerBackView;
@property (nonatomic, strong) UIButton *localAudioBtn;
@property (nonatomic, strong) UIButton *localVideoBtn;
@property (nonatomic, strong) UIButton *settingBtn;
@property (nonatomic, strong) UIButton *hangUpBtn;
@property (nonatomic, strong) UIButton *beautyBtn;
@property (nonatomic, strong) UIButton *screenShareBtn;
@property (nonatomic, strong) UIView *containerView;
@property (nonatomic, strong) UserLiveView *localView;
@property (nonatomic, strong) UserLiveView *firstRemoteView;
@property (nonatomic, strong) UserLiveView *secondRemoteView;
@property (nonatomic, strong) UserLiveView *thirdRemoteView;
@property (nonatomic, strong) RoomSettingView *roomSettingView;
@property (nonatomic, strong) RoomSetting *roomSetting;

// RTC SDK 引擎
@property (nonatomic, strong) ByteRTCVideo *rtcVideo;
@property (nonatomic, strong) ByteRTCRoom *rtcRoom;

// SDK 外部采集
@property (nonatomic, strong) CustomCameraCapture *cameraCapture;

// 美颜UI
@property (nonatomic, strong) BeautyBarView *beautyBarView;

// 美颜组件
@property (nonatomic, strong) VolcBeautyCommon *beautyCommon;

@end

@implementation RoomViewController

- (void)dealloc{
    /// 销毁引擎
    [ByteRTCVideo destroyRTCVideo];
    self.rtcVideo = nil;
    self.rtcRoom = nil;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self initEngineAndJoinRoom];
    
    [self buildUI];
    
    [self.beautyCommon didDefaultSetting];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    if (@available(iOS 13.0, *)) {
        self.overrideUserInterfaceStyle = UIUserInterfaceStyleLight;
    } else {
        // Fallback on earlier versions
    }
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    
    if (self.preJoinSetting.isScreenShare) {
        [self startScreenShare];
    }
}

#pragma mark - RTC Method

- (void)initEngineAndJoinRoom {
    /// 创建引擎
    self.rtcVideo = [ByteRTCVideo createRTCVideo:APPID delegate:self parameters:@{}];
    /// 加入房间
    self.rtcRoom =[self.rtcVideo createRTCRoom:self.roomID];
    [self.rtcRoom setDelegate:self];
    ByteRTCUserInfo *userInfo = [[ByteRTCUserInfo alloc] init];
    userInfo.userId = self.userID;
    ByteRTCRoomConfig *roomConfig = [[ByteRTCRoomConfig alloc] init];
    roomConfig.isAutoPublish = true;
    roomConfig.isAutoSubscribeAudio = true;
    roomConfig.isAutoSubscribeVideo = true;
    [self.rtcRoom joinRoomByToken:TOKEN userInfo:userInfo roomConfig:roomConfig];
    
    if (self.preJoinSetting.isScreenShare) {
        /// 设置groupID
        [self.rtcVideo setExtensionConfig:APP_GROUP];
        /// 设置屏幕共享发布参数，宽高设为00，意味着SDK不会对系统采集到的屏幕视频帧进行裁剪缩放处理
        ByteRTCVideoEncoderConfig * config = [[ByteRTCVideoEncoderConfig alloc] init];
        config.width = self.roomSetting.resolution.width;
        config.height = self.roomSetting.resolution.height;
        config.frameRate = self.roomSetting.fps;
        config.maxBitrate = self.roomSetting.bitrate;
        [self.rtcVideo SetScreenVideoEncoderConfig:config];
        
        /// 开启本地音频采集
        [self.rtcVideo startAudioCapture];
        
        self.localView.uid = @"等待屏幕共享";
        [self.rtcRoom unpublishStream:ByteRTCMediaStreamTypeVideo];
    }
    else {
        /// 设置视频发布参数
        ByteRTCVideoEncoderConfig *solution = [[ByteRTCVideoEncoderConfig alloc] init];
        solution.width = self.roomSetting.resolution.width;
        solution.height = self.roomSetting.resolution.height;
        solution.frameRate = self.roomSetting.fps;
        solution.maxBitrate = self.roomSetting.bitrate;
        [self.rtcVideo SetMaxVideoEncoderConfig:solution];
        /// 设置本地渲染
        [self setLocalRenderView];
        
        /// 开启视频采集
        [self startVideoCapture];
        
        /// 开启本地音频采集
        [self.rtcVideo startAudioCapture];
    }
}

- (void)setLocalRenderView{
    if (self.preJoinSetting.useCustomRender) {
        /// 外部渲染
        [self.rtcVideo setLocalVideoSink:ByteRTCStreamIndexMain withSink:self.localView.customRenderView withPixelFormat:ByteRTCVideoSinkPixelFormatNV12];
        self.localView.uid = self.userID;
    } else {
        /// RTC SDK 内部渲染
        ByteRTCRenderMode rtcRenderMode =  [self RTCRenderModeFromRenderMode:self.preJoinSetting.localRenderMode];

        ByteRTCVideoCanvas *canvas = [[ByteRTCVideoCanvas alloc] init];
        canvas.view = self.localView.liveView;
        canvas.renderMode = rtcRenderMode;
        self.localView.uid = self.userID;
        /// 设置本地视频渲染视图
        [self.rtcVideo setLocalVideoCanvas:ByteRTCStreamIndexMain withCanvas:canvas];
    }
}

- (ByteRTCRenderMode)RTCRenderModeFromRenderMode:(RenderMode)renderMode {
    ByteRTCRenderMode rtcRenderMode;
    switch (renderMode) {
        case RenderMode_Hidden:
        {
            rtcRenderMode = ByteRTCRenderModeHidden;
        }
            break;
        case RenderMode_Fit:
        {
            rtcRenderMode = ByteRTCRenderModeFit;
        }
            break;
        case RenderMode_Stretch:
        {
            rtcRenderMode = ByteRTCRenderModeFill;
        }
            break;
            
        default:
        {
            
        }
            break;
    }
    
    return rtcRenderMode;
}

- (void)startVideoCapture {
    if (self.preJoinSetting.useCustomCapture) {
        /// 外部采集
        /// sdk开启外部采集
        [self.rtcVideo setVideoSourceType:ByteRTCVideoSourceTypeExternal WithStreamIndex:ByteRTCStreamIndexMain];
        /// 开启采集相机
        [self.cameraCapture switchCameraIsFront:YES];
        [SystemAuthority authorizationStatusWithType:AuthorizationTypeCamera
                                               block:^(BOOL isAuthorize) {
            if (isAuthorize) {
                [self.cameraCapture startCamera];
            }
        }];
    } else {
        /// 内部采集
        /// 默认是内部采集，不需要手动调用
        [self.rtcVideo setVideoSourceType:ByteRTCVideoSourceTypeInternal WithStreamIndex:ByteRTCStreamIndexMain];
        /// 开启本地视频采集
        [self.rtcVideo setVideoOrientation:ByteRTCVideoOrientationPortrait];
        [self.rtcVideo startVideoCapture];
    }
}

- (void)stopVideoCapture {
    if (self.preJoinSetting.useCustomCapture) {
        /// 外部采集
        [self.cameraCapture stopCamera];
    } else {
        /// 内部采集
        /// 关闭本地视频采集
        [self.rtcVideo stopVideoCapture];
    }
}

- (void)setupRemoteView:(UserLiveView *)userLiveView streamKey:(ByteRTCRemoteStreamKey *)streamKey {
    
    if (self.preJoinSetting.useCustomRender) {
        /// 设置远端用户视频渲染视图(外部渲染)
        [self.rtcVideo setRemoteVideoSink:streamKey withSink:userLiveView.customRenderView withPixelFormat:ByteRTCVideoSinkPixelFormatNV12];
        NSString *uid = streamKey.userId;
        userLiveView.uid = uid;
    } else {
        NSString *uid = streamKey.userId;
        ByteRTCRenderMode rtcRenderMode =  [self RTCRenderModeFromRenderMode:self.preJoinSetting.remoteRenderMode];

        UIView *view = [[UIView alloc] init];
        ByteRTCVideoCanvas *canvas = [[ByteRTCVideoCanvas alloc] init];
        canvas.view = view;
        canvas.roomId = streamKey.roomId;
        canvas.uid = streamKey.userId;
        canvas.renderMode = rtcRenderMode;
        userLiveView.uid = uid;
        
        [userLiveView replaceCanvasView:view];

        /// 设置远端用户视频渲染视图(内部渲染)
        [self.rtcVideo setRemoteVideoCanvas:uid withIndex:streamKey.streamIndex withCanvas:canvas];
    }
}

#pragma mark - RTC delegate
- (void)rtcRoom:(ByteRTCRoom *)rtcRoom onUserPublishStream:(NSString *)userId type:(ByteRTCMediaStreamType)type {
    if (type == ByteRTCMediaStreamTypeVideo || type == ByteRTCMediaStreamTypeBoth) {
        ByteRTCRemoteStreamKey *streamKey = [[ByteRTCRemoteStreamKey alloc] init];
        streamKey.userId = userId;
        streamKey.streamIndex = ByteRTCStreamIndexMain;
        streamKey.roomId = self.roomID;
        [self setRemoteView:streamKey];
    }
}

- (void)rtcRoom:(ByteRTCRoom *)rtcRoom onUserPublishScreen:(NSString *)userId type:(ByteRTCMediaStreamType)type {
    if (type == ByteRTCMediaStreamTypeVideo || type == ByteRTCMediaStreamTypeBoth) {
        ByteRTCRemoteStreamKey *streamKey = [[ByteRTCRemoteStreamKey alloc] init];
        streamKey.userId = userId;
        streamKey.streamIndex = ByteRTCStreamIndexScreen;
        streamKey.roomId = self.roomID;
        [self setRemoteView:streamKey];
    }
    
}

- (void)setRemoteView:(ByteRTCRemoteStreamKey *)streamKey {
    dispatch_async(dispatch_get_main_queue(), ^{
        
        NSString *uid = streamKey.userId;

      if ([self.firstRemoteView.uid isEqualToString:uid]) {
          [self setupRemoteView:self.firstRemoteView streamKey:streamKey];
          return;
      } else if ([self.secondRemoteView.uid isEqualToString:uid]) {
          [self setupRemoteView:self.secondRemoteView streamKey:streamKey];
          return;
      } else if ([self.thirdRemoteView.uid isEqualToString:uid]) {
          [self setupRemoteView:self.thirdRemoteView streamKey:streamKey];
          return;
      } else {
      }

      if (self.firstRemoteView.uid.length == 0) {
          [self setupRemoteView:self.firstRemoteView streamKey:streamKey];
      } else if (self.secondRemoteView.uid.length == 0) {
          [self setupRemoteView:self.secondRemoteView streamKey:streamKey];
      } else if (self.thirdRemoteView.uid.length == 0) {
          [self setupRemoteView:self.thirdRemoteView streamKey:streamKey];
      } else {
      }
    });
}

- (void)rtcRoom:(ByteRTCRoom *)rtcRoom onUserJoined:(ByteRTCUserInfo *)userInfo elapsed:(NSInteger)elapsed {
    NSLog(@"%@,%s",[NSThread currentThread],__func__);

}

- (void)rtcRoom:(ByteRTCRoom *)rtcRoom onUserUnpublishScreen:(NSString *)userId type:(ByteRTCMediaStreamType)type reason:(ByteRTCStreamRemoveReason)reason {
    if (type != ByteRTCMediaStreamTypeAudio) {
        dispatch_async(dispatch_get_main_queue(), ^{
            
            for (UserLiveView *liveView in self.containerView.subviews) {
                if ([userId isEqualToString:liveView.uid]) {
                    liveView.uid = @"";
                }
            }
        });
    }
}

- (void)rtcRoom:(ByteRTCRoom *)rtcRoom onUserUnpublishStream:(NSString *)userId type:(ByteRTCMediaStreamType)type reason:(ByteRTCStreamRemoveReason)reason {
    if (type != ByteRTCMediaStreamTypeAudio) {
        dispatch_async(dispatch_get_main_queue(), ^{
            for (UserLiveView *liveView in self.containerView.subviews) {
                if ([userId isEqualToString:liveView.uid]) {
                    liveView.uid = @"";
                }
            }
        });
    }
}

- (void)rtcEngine:(ByteRTCVideo *)engine onVideoDeviceStateChanged:(NSString *)device_id device_type:(ByteRTCVideoDeviceType)device_type device_state:(ByteRTCMediaDeviceState)device_state device_error:(ByteRTCMediaDeviceError)device_error {
    if (device_type == ByteRTCVideoDeviceTypeScreenCaptureDevice && self.preJoinSetting.isScreenShare) {
        
        if (device_state == ByteRTCMediaDeviceStateStarted) {
            [_rtcRoom publishScreen:ByteRTCMediaStreamTypeBoth];
                
            dispatch_async(dispatch_get_main_queue(), ^{
                self.localView.uid = @"正在共享";
                self.screenShareBtn.selected = YES;
                self.screenShareBtn.imageView.backgroundColor = UIColor.clearColor;
            });
        } else if (device_state == ByteRTCMediaDeviceStateStopped ||
                   device_state == ByteRTCMediaDeviceStateRuntimeError) {
            [_rtcRoom unpublishScreen:ByteRTCMediaStreamTypeBoth];
            
            dispatch_async(dispatch_get_main_queue(), ^{
                self.localView.uid = @"等待屏幕共享";
                self.screenShareBtn.selected = NO;
                self.screenShareBtn.imageView.backgroundColor = UIColor.lightGrayColor;
            });
        }
    }
}


- (void)rtcEngine:(ByteRTCVideo *)engine onWarning:(ByteRTCWarningCode)Code {
    NSLog(@"warningCode = %ld", (long)Code);
}

- (void)rtcEngine:(ByteRTCVideo *)engine onError:(ByteRTCErrorCode)errorCode {
    NSLog(@"errorCode = %ld",(long)errorCode);
    [self showAlert:[NSString stringWithFormat:@"error:%ld", (long)errorCode]];
}

#pragma mark - RTC delegate （实时消息）

- (void)rtcRoom:(ByteRTCRoom *)rtcRoom onUserMessageReceived:(NSString * _Nonnull)uid message:(NSString * _Nonnull)message {
    NSString *str = [NSString stringWithFormat:@"接收到点对点文本实时消息：%@：%@",uid,message];
    [[ToastComponents shareToastComponents] showWithMessage:str];
}

- (void)rtcRoom:(ByteRTCRoom *)rtcRoom onUserBinaryMessageReceived:(NSString *)uid message:(NSData *)message {
    NSString *str = [[NSString alloc] initWithData:message encoding:NSUTF8StringEncoding];
    NSString *allStr = [NSString stringWithFormat:@"接收到点对点二进制实时消息：%@：%@",uid,str];
    [[ToastComponents shareToastComponents] showWithMessage:allStr];
}

- (void)rtcRoom:(ByteRTCRoom *)rtcRoom onRoomMessageReceived:(NSString *)uid message:(NSString *)message {
    NSString *str = [NSString stringWithFormat:@"接收到广播文本实时消息：%@：%@",uid,message];
    [[ToastComponents shareToastComponents] showWithMessage:str];
}

- (void)rtcRoom:(ByteRTCRoom *)rtcRoom onRoomBinaryMessageReceived:(NSString *)uid message:(NSData *)message {
    NSString *str = [[NSString alloc] initWithData:message encoding:NSUTF8StringEncoding];
    NSString *allStr = [NSString stringWithFormat:@"接收到广播二进制实时消息：%@：%@",uid,str];
    [[ToastComponents shareToastComponents] showWithMessage:allStr];
}

- (void)rtcRoom:(ByteRTCRoom *)rtcRoom onUserMessageSendResult:(int64_t)msgid error:(ByteRTCUserMessageSendResult)error {
    NSString *message = @"";
    if (error == ByteRTCUserMessageSendResultSuccess) {
        message = @"点对点消息发送成功";
    } else {
        message = [NSString stringWithFormat:@"点对点消息发送失败（%ld）", (long)error];
    }
    [[ToastComponents shareToastComponents] showWithMessage:message];
}

- (void)rtcRoom:(ByteRTCRoom *)rtcRoom onRoomMessageSendResult:(int64_t)msgid error:(ByteRTCRoomMessageSendResult)error {
    NSString *message = @"";
    if (error == ByteRTCRoomMessageSendResultSuccess) {
        message = @"广播消息发送成功";
    } else {
        message =
        [NSString stringWithFormat:@"广播消息发送失败（%ld）", (long)error];
    }
    [[ToastComponents shareToastComponents] showWithMessage:message];
}

#pragma mark - RTC delegate (SEI)

- (void)rtcEngine:(ByteRTCVideo *)engine onSEIMessageReceived:(ByteRTCRemoteStreamKey *)remoteStreamKey andMessage:(NSData *)message {
    NSString *str = [[NSString alloc] initWithData:message encoding:NSUTF8StringEncoding];
    NSString *allStr = [NSString stringWithFormat:@"接收到 SEI 消息：%@：%@",remoteStreamKey.userId,str];
    [[ToastComponents shareToastComponents] showWithMessage:allStr];
}

#pragma mark - Private Method

- (void)showAlert:(NSString *)message {
    UIAlertController *alert = [UIAlertController
                                alertControllerWithTitle:@""
                                message:message
                                preferredStyle:UIAlertControllerStyleAlert];
    UIAlertAction *alertAction = [UIAlertAction actionWithTitle:@"知道了" style:UIAlertActionStyleDefault handler:^(UIAlertAction *_Nonnull action) {
    }];
    [alert addAction:alertAction];
    dispatch_async(dispatch_get_main_queue(), ^{
        [self presentViewController:alert animated:YES completion:nil];
    });
}

- (void)switchCamera:(UIButton *)button {
    button.selected = !button.selected;
    ByteRTCCameraID cameraID = ByteRTCCameraIDFront;
    if (button.selected) {
        cameraID = ByteRTCCameraIDBack;
    }
    /// 切换前置/后置摄像头（默认使用前置摄像头）
    if (self.preJoinSetting.useCustomCapture) {
        [self.cameraCapture switchCameraIsFront:!button.selected];
    }else {
        [self.rtcVideo switchCamera:button.selected];
    }
}

- (void)switchAudioRoute:(UIButton *)button {
    button.selected = !button.selected;
    if (button.selected) {
        /// 设置使用听筒播放音频数据
        [self.rtcVideo setAudioPlaybackDevice:ByteRTCAudioPlaybackDeviceEarpiece];
    }else{
        /// 设置使用扬声器播放音频数据
        [self.rtcVideo setAudioPlaybackDevice:ByteRTCAudioPlaybackDeviceSpeakerphone];
    }
}

- (void)enableLocalAudio:(UIButton *)button {
    button.selected = !button.selected;
    if (button.selected) {
        /// 关闭本地音频发送
        [self.rtcRoom unpublishStream:ByteRTCMediaStreamTypeAudio];
    }else{
        /// 开启本地音频发送
        [self.rtcRoom publishStream:ByteRTCMediaStreamTypeAudio];
    }
}

- (void)enableLocalVideo:(UIButton *)button {
    button.selected = !button.selected;
    if (button.selected) {
        /// 关闭视频采集
        [self stopVideoCapture];
    }else{
        /// 开启视频采集
        [self startVideoCapture];
    }
}

- (void)settingButtonClicked:(UIButton *)button {
    self.roomSettingView.hidden = !self.roomSettingView.hidden;
    BOOL show = (self.roomSettingView.hidden == NO);
    if (show) {
        /// 打开设置界面
        self.roomSettingView.roomSetting = self.roomSetting;
    }else {
        /// 关闭设置界面
        [self updateVideoConfig];
    }
    
    self.beautyBarView.hidden = YES;
}

- (void)updateVideoConfig {
    
    if (self.preJoinSetting.isScreenShare) {
        // 修改屏幕共享参数，需要重新开启屏幕共享后生效
        ByteRTCVideoEncoderConfig * config = [[ByteRTCVideoEncoderConfig alloc] init];
        config.width = self.roomSetting.resolution.width;
        config.height = self.roomSetting.resolution.height;
        config.frameRate = self.roomSetting.fps;
        config.maxBitrate = self.roomSetting.bitrate;
        [self.rtcVideo SetScreenVideoEncoderConfig:config];
    }
    else {
        ByteRTCVideoEncoderConfig *solution = [[ByteRTCVideoEncoderConfig alloc] init];
        solution.width = self.roomSetting.resolution.width;
        solution.height = self.roomSetting.resolution.height;
        solution.frameRate = self.roomSetting.fps;
        solution.maxBitrate = self.roomSetting.bitrate;
        [self.rtcVideo SetMaxVideoEncoderConfig:solution];
        
        if (!self.preJoinSetting.useCustomRender) {
            if (self.roomSetting.localRenderMirror == 0) {
                [self.rtcVideo setLocalVideoMirrorType:ByteRTCMirrorTypeNone];
            } else if (self.roomSetting.localRenderMirror == 1) {
                [self.rtcVideo setLocalVideoMirrorType:ByteRTCMirrorTypeRender];
            } else if (self.roomSetting.localRenderMirror == 2) {
                [self.rtcVideo setLocalVideoMirrorType:ByteRTCMirrorTypeRenderAndEncoder];
            } else {
                //error
            }
        }
    }
}

- (void)hangUp:(UIButton *)button {
    /// 离开房间
    [self.rtcRoom leaveRoom];
    
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (void)showBeautyBar:(UIButton *)button{
    self.beautyBarView.hidden = !self.beautyBarView.hidden;
    
    if (!self.roomSettingView.hidden) {
        self.roomSettingView.hidden = YES;
        [self updateVideoConfig];
    }

}

- (void)screenShareButtonClick:(UIButton *)button {
    if (button.selected) {
        [self stopScreenShare];
    }
    else {
        [self startScreenShare];
    }
}

- (void)startScreenShare {
    [self.rtcVideo startScreenCapture:ByteRTCScreenMediaTypeVideoAndAudio bundleId:EXTENSION_BUNDLE_ID];
}

- (void)stopScreenShare {
    [self.rtcVideo stopScreenCapture];
}

#pragma mark - CustomCameraCaptureDelegate

- (void)customCameraCapture:(CustomCameraCapture *)customCameraCapture
            didOutputBuffer:(CVImageBufferRef)buffer
                       time:(CMTime)time {
    /// 自定义采集相机 使用sdk 推流
    [self.rtcVideo pushExternalVideoFrame:buffer time:time];
}

#pragma mark - BeautyBarViewDelegate

- (void)beautyBarView:(BeautyBarView *)barView didClickedEffect:(EffectModel *)model {
    switch (model.type) {
        case EffectModelTypeSticker: {
            NSString *stickerPath = [EffectResource stickerPathWithName:model.dic[@"key"]];
            [self.beautyCommon didClickedStickerEffect:stickerPath
                                              selected:model.selected];
        }
            break;
        case EffectModelTypeFilter: {
            NSString *filterPath = [EffectResource filterPathWithName:model.dic[@"key"]];
            [self.beautyCommon didClickedFilterEffect:filterPath
                                                value:model.value];
        }
            break;
        case EffectModelTypeVirtual: {
            [self.beautyCommon didClickedVirtualEffect:model.dic[@"type"]
                                              selected:model.selected];
        }
            break;
            
        default:
            break;
    }
}

- (void)beautyBarView:(BeautyBarView *)barView didChangeEffectValue:(EffectModel *)model {
    switch (model.type) {
        case EffectModelTypeBeauty: {
            if ([model.dic[@"type"] isEqualToString:@"reshape"]) {
                [self.beautyCommon didChangeReshapeEffect:model.dic[@"key"]
                                                    value:model.value];
            } else {
                [self.beautyCommon didChangeBeautyEffect:model.dic[@"key"]
                                                   value:model.value];
            }
        }
            break;
        case EffectModelTypeFilter: {
            [self.beautyCommon didChangeFilterEffect:model.value];
        }
            break;
        default:
            break;
    }
}

#pragma mark - Private Action

- (void)buildUI {
    self.view.backgroundColor = [UIColor whiteColor];
    
    UIEdgeInsets edgeInsets = UIEdgeInsetsZero;
    if (@available(iOS 11.0, *)) {
        edgeInsets = [UIApplication sharedApplication].keyWindow.safeAreaInsets;
    }
    
    [self.view addSubview:self.headerView];
    [self.headerView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.mas_equalTo(edgeInsets.top);
        make.left.right.equalTo(self.view);
        make.height.mas_equalTo(49);
    }];
    
     self.switchCameraBtn.frame = CGRectMake(22, 14, 26, 26);
    [self.headerView addSubview:self.switchCameraBtn];
    [self.switchCameraBtn mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.mas_equalTo(22);
        make.centerY.equalTo(self.headerView);
    }];
    
    [self.headerView addSubview:self.roomIdLabel];
    [self.roomIdLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.center.equalTo(self.headerView);
    }];
    self.roomIdLabel.text = [NSString stringWithFormat:@"RoomID: %@",self.roomID];
    
    [self.headerView addSubview:self.switchAudioRouteBtn];
    [self.switchAudioRouteBtn mas_makeConstraints:^(MASConstraintMaker *make) {
        make.right.mas_equalTo(-20);
        make.centerY.equalTo(self.headerView);
    }];
    
    [self.view addSubview: self.foooterView];
    [self.foooterView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.right.equalTo(self.view);
        make.bottom.equalTo(self.view).offset(-edgeInsets.bottom);
        make.height.mas_equalTo(49);
    }];
    
    CGFloat itemWidth = self.view.frame.size.width / 5;
    
    [self.foooterView addSubview:self.localAudioBtn];
    [self.localAudioBtn mas_makeConstraints:^(MASConstraintMaker *make) {
        make.width.mas_equalTo(itemWidth);
        make.height.equalTo(self.foooterView);
        make.left.equalTo(self.foooterView);
        make.centerY.equalTo(self.foooterView);
    }];
    
    [self.foooterView addSubview:self.localVideoBtn];
    [self.localVideoBtn mas_makeConstraints:^(MASConstraintMaker *make) {
        make.width.mas_equalTo(itemWidth);
        make.height.equalTo(self.foooterView);
        make.left.equalTo(self.localAudioBtn.mas_right);
        make.centerY.equalTo(self.foooterView);
    }];
    
    [self.foooterView addSubview:self.hangUpBtn];
    [self.hangUpBtn mas_makeConstraints:^(MASConstraintMaker *make) {
        make.width.mas_equalTo(itemWidth);
        make.height.equalTo(self.foooterView);
        make.left.equalTo(self.localVideoBtn.mas_right);
        make.centerY.equalTo(self.foooterView);
    }];
    
    UIButton *settingLeftBtn = nil;
    if (self.preJoinSetting.isScreenShare) {
        [self.view insertSubview:self.footerBackView belowSubview:self.foooterView];
        [self.footerBackView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.right.bottom.equalTo(self.view);
            make.top.equalTo(self.foooterView);
        }];
        [self.foooterView addSubview:self.screenShareBtn];
        [self.screenShareBtn mas_makeConstraints:^(MASConstraintMaker *make) {
            make.width.mas_equalTo(itemWidth);
            make.height.equalTo(self.foooterView);
            make.left.equalTo(self.hangUpBtn.mas_right);
            make.centerY.equalTo(self.foooterView);
        }];
        self.localVideoBtn.selected = YES;
        self.localVideoBtn.alpha = 0.5;
        self.localVideoBtn.userInteractionEnabled = NO;
        
        settingLeftBtn = self.screenShareBtn;
    }
    else {
        [self.foooterView addSubview:self.beautyBtn];
        [self.beautyBtn mas_makeConstraints:^(MASConstraintMaker *make) {
            make.width.mas_equalTo(itemWidth);
            make.height.equalTo(self.foooterView);
            make.left.equalTo(self.hangUpBtn.mas_right);
            make.centerY.equalTo(self.foooterView);
        }];
        
        settingLeftBtn = self.beautyBtn;
    }
    
    [self.foooterView addSubview:self.settingBtn];
    [self.settingBtn mas_makeConstraints:^(MASConstraintMaker *make) {
        make.width.mas_equalTo(itemWidth);
        make.height.equalTo(self.foooterView);
        make.left.equalTo(settingLeftBtn.mas_right);
        make.centerY.equalTo(self.foooterView);
    }];
    
    [self.view addSubview:self.containerView];
    [self.containerView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.right.equalTo(self.view);
        make.top.equalTo(self.headerView.mas_bottom);
        make.bottom.equalTo(self.foooterView.mas_top);
    }];
    
    [self.containerView addSubview:self.localView];
    [self.localView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.left.equalTo(self.containerView);
        make.width.height.equalTo(self.containerView).multipliedBy(0.5);
    }];
    
    [self.containerView addSubview:self.firstRemoteView];
    [self.firstRemoteView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.right.equalTo(self.containerView);
        make.width.height.equalTo(self.containerView).multipliedBy(0.5);
    }];
    
    [self.containerView addSubview:self.secondRemoteView];
    [self.secondRemoteView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.bottom.left.equalTo(self.containerView);
        make.width.height.equalTo(self.containerView).multipliedBy(0.5);
    }];
    
    [self.containerView addSubview:self.thirdRemoteView];
    [self.thirdRemoteView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.bottom.right.equalTo(self.containerView);
        make.width.height.equalTo(self.containerView).multipliedBy(0.5);
    }];
    
    [self.view addSubview: self.roomSettingView];
    [self.roomSettingView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(self.headerView.mas_bottom);
        make.left.right.equalTo(self.view);
        make.bottom.equalTo(self.foooterView.mas_top);
    }];
    
    [self.view addSubview:self.beautyBarView];
    [self.beautyBarView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.bottom.equalTo(self.foooterView.mas_top);
        make.left.right.equalTo(self.view);
        make.height.mas_equalTo(320);
    }];
}

#pragma mark - Getter

- (UIView *)headerView{
    if(!_headerView){
        _headerView = [[UIView alloc] init];
    }
    return _headerView;
}

- (UIButton *)switchCameraBtn{
    if(!_switchCameraBtn){
        _switchCameraBtn = [[UIButton alloc] init];
        [_switchCameraBtn setImage:[UIImage imageNamed:@"switch_camera"] forState:UIControlStateNormal];
        [_switchCameraBtn addTarget:self action:@selector(switchCamera:) forControlEvents:UIControlEventTouchUpInside];
    }
    return _switchCameraBtn;
}

- (UILabel *)roomIdLabel{
    if(!_roomIdLabel){
        _roomIdLabel = [[UILabel alloc] init];
        _roomIdLabel.font = [UIFont systemFontOfSize:18];
    }
    return _roomIdLabel;
}

- (UIButton *)switchAudioRouteBtn{
    if(!_switchAudioRouteBtn){
        _switchAudioRouteBtn = [[UIButton alloc] init];
        [_switchAudioRouteBtn setImage:[UIImage imageNamed:@"speaker"] forState:UIControlStateNormal];
        [_switchAudioRouteBtn setImage:[UIImage imageNamed:@"ear_on"] forState:UIControlStateSelected];

        [_switchAudioRouteBtn addTarget:self action:@selector(switchAudioRoute:) forControlEvents:UIControlEventTouchUpInside];
    }
    return _switchAudioRouteBtn;
}

- (UIView *)foooterView{
    if(!_foooterView){
        _foooterView = [[UIView alloc] init];
    }
    return _foooterView;
}

- (UIButton *)localAudioBtn{
    if(!_localAudioBtn){
        _localAudioBtn = [[UIButton alloc] init];
        [_localAudioBtn setImage:[UIImage imageNamed:@"normal_audio"] forState:UIControlStateNormal];
        [_localAudioBtn setImage:[UIImage imageNamed:@"mute_audio"] forState:UIControlStateSelected];
        [_localAudioBtn addTarget:self action:@selector(enableLocalAudio:) forControlEvents:UIControlEventTouchUpInside];

    }
    return _localAudioBtn;
}

- (UIButton *)localVideoBtn{
    if(!_localVideoBtn){
        _localVideoBtn = [[UIButton alloc] init];
        [_localVideoBtn setImage:[UIImage imageNamed:@"normal_video"] forState:UIControlStateNormal];
        [_localVideoBtn setImage:[UIImage imageNamed:@"mute_video"] forState:UIControlStateSelected];

        [_localVideoBtn addTarget:self action:@selector(enableLocalVideo:) forControlEvents:UIControlEventTouchUpInside];
    }
    return _localVideoBtn;
}

- (UIButton *)hangUpBtn{
    if(!_hangUpBtn){
        _hangUpBtn = [[UIButton alloc] init];
        [_hangUpBtn setImage:[UIImage imageNamed:@"hang_up"] forState:UIControlStateNormal];
        [_hangUpBtn addTarget:self action:@selector(hangUp:) forControlEvents:UIControlEventTouchUpInside];
    }
    return _hangUpBtn;
}

- (UIButton *)beautyBtn{
    if(!_beautyBtn){
        _beautyBtn = [[UIButton alloc] init];
        [_beautyBtn setImage:[UIImage imageNamed:@"beauty"] forState:UIControlStateNormal];
        [_beautyBtn addTarget:self action:@selector(showBeautyBar:) forControlEvents:UIControlEventTouchUpInside];
    }
    return _beautyBtn;
}

- (UIButton *)screenShareBtn {
    if (!_screenShareBtn) {
        _screenShareBtn = [[UIButton alloc] init];
        [_screenShareBtn setImage:[UIImage imageNamed:@"screen_share_start"] forState:UIControlStateNormal];
        [_screenShareBtn setImage:[UIImage imageNamed:@"screen_share_stop"] forState:UIControlStateSelected];
        [_screenShareBtn addTarget:self action:@selector(screenShareButtonClick:) forControlEvents:UIControlEventTouchUpInside];
        _screenShareBtn.imageView.backgroundColor = UIColor.lightGrayColor;
    }
    return _screenShareBtn;
}

- (UIView *)footerBackView {
    if (!_footerBackView) {
        _footerBackView = [[UIView alloc] init];
        _footerBackView.backgroundColor = [UIColor colorWithRed:204 green:204 blue:204 alpha:1.0];
    }
    return _footerBackView;
}

- (BeautyBarView *)beautyBarView{
    if(!_beautyBarView){
        _beautyBarView = [[BeautyBarView alloc] init];
        _beautyBarView.hidden = YES;
        _beautyBarView.delegate = self;
    }
    return _beautyBarView;
}

- (UIView *)containerView{
    if(!_containerView){
        _containerView = [[UIView alloc] init];
        _containerView.backgroundColor = [UIColor lightGrayColor];
    }
    return _containerView;
}

- (UserLiveView *)localView{
    if(!_localView){
        _localView = [[UserLiveView alloc] init];
        _localView.useCustomRender = self.preJoinSetting.useCustomRender;
    }
    return _localView;
}

- (UserLiveView *)firstRemoteView{
    if(!_firstRemoteView){
        _firstRemoteView = [[UserLiveView alloc] init];
        _firstRemoteView.useCustomRender = self.preJoinSetting.useCustomRender;
    }
    return _firstRemoteView;
}

- (UserLiveView *)secondRemoteView{
    if(!_secondRemoteView){
        _secondRemoteView = [[UserLiveView alloc] init];
        _secondRemoteView.useCustomRender = self.preJoinSetting.useCustomRender;
    }
    return _secondRemoteView;
}

- (UserLiveView *)thirdRemoteView{
    if(!_thirdRemoteView){
        _thirdRemoteView = [[UserLiveView alloc] init];
        _thirdRemoteView.useCustomRender = self.preJoinSetting.useCustomRender;
    }
    return _thirdRemoteView;
}

- (UIButton *)settingBtn {
    if(!_settingBtn) {
        _settingBtn = [[UIButton alloc] init];
        [_settingBtn setImage:[UIImage imageNamed:@"setting"] forState:UIControlStateNormal];
        [_settingBtn addTarget:self action:@selector(settingButtonClicked:) forControlEvents:UIControlEventTouchUpInside];
    }
    return _settingBtn;
}

- (RoomSettingView *)roomSettingView {
    if(!_roomSettingView) {
        _roomSettingView = [[RoomSettingView alloc] initWithRtcKit:self.rtcVideo rtcRoom:self.rtcRoom];
        _roomSettingView.hidden = YES;
    }
    return _roomSettingView;
}

- (RoomSetting *)roomSetting {
    if(!_roomSetting) {
        _roomSetting = [[RoomSetting alloc] init];
    }
    return _roomSetting;
}

- (CustomCameraCapture *)cameraCapture {
    if (!_cameraCapture) {
        _cameraCapture = [[CustomCameraCapture alloc] init];
        _cameraCapture.captureDelegate = self;
    }
    return _cameraCapture;
}

- (VolcBeautyCommon *)beautyCommon {
    if (!_beautyCommon) {
        _beautyCommon = [[VolcBeautyCommon alloc] initWithRtcKit:self.rtcVideo];
    }
    return _beautyCommon;
}

@end
