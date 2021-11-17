/**
 * VolcEngineRTC 视频通话的主页面
 * 本示例不限制房间内最大用户数；同时最多渲染四个用户的视频数据（自己和三个远端用户视频数据）；
 *
 * 包含如下简单功能：
 * - 创建引擎
 * - 设置视频发布参数
 * - 渲染自己的视频数据
 * - 加入音视频通话房间
 * - 切换前置/后置摄像头
 * - 打开/关闭麦克风
 * - 打开/关闭摄像头
 * - 切换听筒/扬声器
 * - 渲染远端用户的视频数据
 * - 离开房间
 * - 销毁引擎
 *
 * 实现一个基本的音视频通话的流程如下：
 * 1.创建引擎 initWithAppId:delegate:parameters:
 * 2.设置编码参数 setVideoEncoderConfig:
 * 3.开启本地视频采集 startVideoCapture:、startPreview:
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
 * 详细的API文档参见: https://www.volcengine.com/docs/6348/70086
 */
#import "RoomViewController.h"
#import "Masonry.h"
#import "UserLiveView.h"
#import "Constants.h"
#import <VolcEngineRTC/objc/rtc/ByteRTCEngineKit.h>

@interface RoomViewController ()<ByteRTCEngineDelegate>
@property (nonatomic, strong) UIView *headerView;
@property (nonatomic, strong) UIButton *switchCameraBtn;
@property (nonatomic, strong) UILabel *roomIdLabel;
@property (nonatomic, strong) UIButton *switchAudioRouteBtn;

@property (nonatomic, strong) UIView *foooterView;
@property (nonatomic, strong) UIButton *localAudioBtn;
@property (nonatomic, strong) UIButton *localVideoBtn;
@property (nonatomic, strong) UIButton *hangUpBtn;

@property (nonatomic, strong) UIView *containerView;
@property (nonatomic, strong) UserLiveView *localView;
@property (nonatomic, strong) UserLiveView *firstRemoteView;
@property (nonatomic, strong) UserLiveView *secondRemoteView;
@property (nonatomic, strong) UserLiveView *thirdRemoteView;

@property (nonatomic, strong) ByteRTCEngineKit *rtcKit;
@end

@implementation RoomViewController

- (void)dealloc{
    /// 销毁引擎
    [self.rtcKit destroyEngine];
    
    self.rtcKit = nil;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self buildUI];
    
    [self initEngineAndJoinRoom];
}

- (void)buildUI{
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
    
    [self.foooterView addSubview:self.localAudioBtn];
    [self.localAudioBtn mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.mas_equalTo(42);
        make.centerY.equalTo(self.foooterView);
    }];
    
    [self.foooterView addSubview:self.localVideoBtn];
    [self.localVideoBtn mas_makeConstraints:^(MASConstraintMaker *make) {
        make.right.mas_equalTo(-42);
        make.centerY.equalTo(self.foooterView);
    }];
    
    [self.foooterView addSubview:self.hangUpBtn];
    [self.hangUpBtn mas_makeConstraints:^(MASConstraintMaker *make) {
        make.center.equalTo(self.foooterView);
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
}

#pragma mark - RTC Method

- (void)initEngineAndJoinRoom{
    /// 创建引擎
    self.rtcKit = [[ByteRTCEngineKit alloc] initWithAppId:APPID delegate:self parameters:nil];
    /// 设置视频发布参数
    ByteRTCVideoSolution *solution = [[ByteRTCVideoSolution alloc] init];
    solution.videoSize = CGSizeMake(360, 640);
    solution.frameRate = 15;
    solution.maxKbps = 800;
    [self.rtcKit setVideoEncoderConfig:@[solution]];
    [self setLocalRenderView];
    /// 开启本地视频采集
    [self.rtcKit startVideoCapture];

    /// 开启本地音频采集
    [self.rtcKit startAudioCapture];
    
    ByteRTCUserInfo *userInfo = [[ByteRTCUserInfo alloc] init];
    userInfo.userId = self.userID;
    /// 加入房间
    ByteRTCRoomConfig *roomConfig = [[ByteRTCRoomConfig alloc] init];
    roomConfig.isAutoPublish = true;
    roomConfig.isAutoSubscribeAudio = true;
    roomConfig.isAutoSubscribeVideo = true;
    [self.rtcKit joinRoomByKey:TOKEN roomId:self.roomID userInfo:userInfo rtcRoomConfig:roomConfig];
}

- (void)setLocalRenderView{
    ByteRTCVideoCanvas *canvas = [[ByteRTCVideoCanvas alloc] init];
    canvas.view = self.localView.liveView;
    canvas.renderMode = ByteRTCRenderModeHidden;
    self.localView.uid = self.userID;
    /// 设置本地视频渲染视图
    [self.rtcKit setLocalVideoCanvas:ByteRTCStreamIndexMain withCanvas:canvas];
}

- (void)setupRemoteView:(UserLiveView *)userLiveView uid:(NSString *)uid{
    ByteRTCVideoCanvas *canvas = [[ByteRTCVideoCanvas alloc] init];
    canvas.view = userLiveView.liveView;
    canvas.renderMode = ByteRTCRenderModeHidden;
    userLiveView.uid = uid;
    /// 设置远端用户视频渲染视图
    [self.rtcKit setRemoteVideoCanvas:uid withIndex:ByteRTCStreamIndexMain withCanvas:canvas];
}

#pragma mark - RTC delegate
- (void)rtcEngine:(ByteRTCEngineKit *)engine onJoinRoomResult:(NSString *)roomId withUid:(NSString *)uid errorCode:(NSInteger)errorCode joinType:(NSInteger)joinType elapsed:(NSInteger)elapsed{
    if (errorCode == 0) {
        NSLog(@"self join room %@ success",roomId);
    } else {
        [self showAlert:[NSString stringWithFormat:@"error:%ld", (long)errorCode]];
    }
}

- (void)rtcEngine:(ByteRTCEngineKit *)engine onFirstRemoteVideoFrameRendered:(ByteRTCRemoteStreamKey *)streamKey withFrameInfo:(ByteRTCVideoFrameInfo *)frameInfo{
    NSLog(@"%@,%s",[NSThread currentThread],__func__);

    dispatch_async(dispatch_get_main_queue(), ^{
        if ([self.firstRemoteView.uid isEqualToString:streamKey.userId]) {
            [self setupRemoteView:self.firstRemoteView uid:streamKey.userId];
            return;
        }else if ([self.secondRemoteView.uid isEqualToString:streamKey.userId]) {
            [self setupRemoteView:self.secondRemoteView uid:streamKey.userId];
            return;
        }else if ([self.thirdRemoteView.uid isEqualToString: streamKey.userId]) {
            [self setupRemoteView:self.thirdRemoteView uid:streamKey.userId];
            return;
        }else{
            
        }
        
        if (self.firstRemoteView.uid.length == 0) {
            [self setupRemoteView:self.firstRemoteView uid:streamKey.userId];
        }else if (self.secondRemoteView.uid.length == 0) {
            [self setupRemoteView:self.secondRemoteView uid:streamKey.userId];
        }else if (self.thirdRemoteView.uid.length == 0) {
            [self setupRemoteView:self.thirdRemoteView uid:streamKey.userId];
        }else{
            
        }
    });
}

- (void)rtcEngine:(ByteRTCEngineKit *)engine onUserJoined:(ByteRTCUserInfo *)userInfo elapsed:(NSInteger)elapsed{
    NSLog(@"%@,%s",[NSThread currentThread],__func__);

}

- (void)rtcEngine:(ByteRTCEngineKit *)engine onUserLeave:(NSString *)uid reason:(ByteRTCUserOfflineReason)reason{
    NSLog(@"%@,%s",[NSThread currentThread],__func__);
    
    dispatch_async(dispatch_get_main_queue(), ^{
        for (UserLiveView *liveView in self.containerView.subviews) {
            if ([uid isEqualToString:liveView.uid]) {
                liveView.uid = @"";
            }
        }
    });
}

- (void)rtcEngine:(ByteRTCEngineKit *)engine onWarning:(ByteRTCWarningCode)Code{
    NSLog(@"warningCode = %ld", (long)Code);
}

- (void)rtcEngine:(ByteRTCEngineKit *)engine onError:(ByteRTCErrorCode)errorCode{
    NSLog(@"errorCode = %ld",(long)errorCode);
    [self showAlert:[NSString stringWithFormat:@"error:%ld", (long)errorCode]];
}

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

#pragma mark - Private Method
- (void)switchCamera:(UIButton *)button{
    button.selected = !button.selected;
    ByteRTCCameraID cameraID = ByteRTCCameraIDFront;
    if (button.selected) {
        cameraID = ByteRTCCameraIDBack;
    }
    /// 切换前置/后置摄像头（默认使用前置摄像头）
    [self.rtcKit switchCamera:button.selected];
}

- (void)switchAudioRoute:(UIButton *)button{
    button.selected = !button.selected;
    if (button.selected) {
        /// 设置使用听筒播放音频数据
        [self.rtcKit setAudioPlaybackDevice:ByteRTCAudioPlaybackDeviceEarpiece];
    }else{
        /// 设置使用扬声器播放音频数据
        [self.rtcKit setAudioPlaybackDevice:ByteRTCAudioPlaybackDeviceSpeakerphone];
    }
}

- (void)enableLocalAudio:(UIButton *)button{
    button.selected = !button.selected;
    if (button.selected) {
        /// 关闭本地音频发送
        [self.rtcKit muteLocalAudio:ByteRTCMuteStateOn];
    }else{
        /// 开启本地音频发送
        [self.rtcKit muteLocalAudio:ByteRTCMuteStateOff];
    }
}

- (void)enableLocalVideo:(UIButton *)button{
    button.selected = !button.selected;
    if (button.selected) {
        /// 关闭视频采集
        [self.rtcKit stopVideoCapture];
    }else{
        /// 开启视频采集
        [self.rtcKit startVideoCapture];
    }
}

- (void)hangUp:(UIButton *)button{
    /// 离开房间
    [self.rtcKit leaveRoom:^(ByteRTCRoomStats * _Nonnull stat) {
        
    }];
    
    [self dismissViewControllerAnimated:YES completion:nil];
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
    }
    return _localView;
}

- (UserLiveView *)firstRemoteView{
    if(!_firstRemoteView){
        _firstRemoteView = [[UserLiveView alloc] init];
    }
    return _firstRemoteView;
}

- (UserLiveView *)secondRemoteView{
    if(!_secondRemoteView){
        _secondRemoteView = [[UserLiveView alloc] init];
    }
    return _secondRemoteView;
}

- (UserLiveView *)thirdRemoteView{
    if(!_thirdRemoteView){
        _thirdRemoteView = [[UserLiveView alloc] init];
    }
    return _thirdRemoteView;
}
@end
