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
#import "Constants.h"
#import <VolcEngineRTC/objc/ByteRTCVideo.h>
#import <VolcEngineRTC/objc/ByteRTCRoom.h>

@interface RoomViewController ()<ByteRTCRoomDelegate, ByteRTCVideoDelegate>
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

// RTC SDK 引擎
@property (nonatomic, strong) ByteRTCVideo *rtcVideo;
@property (nonatomic, strong) ByteRTCRoom *rtcRoom;
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
        make.size.mas_equalTo(26);
        make.centerY.equalTo(self.headerView);
    }];
    
    [self.headerView addSubview:self.roomIdLabel];
    [self.roomIdLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.center.equalTo(self.headerView);
        make.left.greaterThanOrEqualTo(self.switchCameraBtn.mas_right).mas_offset(22);
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
    self.rtcVideo = [ByteRTCVideo createRTCVideo:APPID delegate:self parameters:@{}];
    /// 设置视频发布参数
    ByteRTCVideoEncoderConfig *solution = [[ByteRTCVideoEncoderConfig alloc] init];
    solution.width = 360;
    solution.height = 640;
    solution.frameRate = 15;
    solution.maxBitrate = 800;
    [self.rtcVideo SetMaxVideoEncoderConfig:solution];
    [self setLocalRenderView];
    /// 开启本地视频采集
    [self.rtcVideo startVideoCapture];

    /// 开启本地音频采集
    [self.rtcVideo startAudioCapture];
    
    self.rtcRoom =[self.rtcVideo createRTCRoom:self.roomID];
    [self.rtcRoom setDelegate:self];
    ByteRTCUserInfo *userInfo = [[ByteRTCUserInfo alloc] init];
    userInfo.userId = self.userID;
    /// 加入房间
    ByteRTCRoomConfig *roomConfig = [[ByteRTCRoomConfig alloc] init];
    roomConfig.isAutoPublish = true;
    roomConfig.isAutoSubscribeAudio = true;
    roomConfig.isAutoSubscribeVideo = true;
    [self.rtcRoom joinRoomByToken:TOKEN userInfo:userInfo roomConfig:roomConfig];
}

- (void)setLocalRenderView{
    ByteRTCVideoCanvas *canvas = [[ByteRTCVideoCanvas alloc] init];
    canvas.view = self.localView.liveView;
    canvas.renderMode = ByteRTCRenderModeHidden;
    self.localView.uid = self.userID;
    /// 设置本地视频渲染视图
    [self.rtcVideo setLocalVideoCanvas:ByteRTCStreamIndexMain withCanvas:canvas];
}

- (void)setupRemoteView:(UserLiveView *)userLiveView roomId:(NSString*)roomId uid:(NSString *)uid{
    ByteRTCVideoCanvas *canvas = [[ByteRTCVideoCanvas alloc] init];
    canvas.view = userLiveView.liveView;
    canvas.renderMode = ByteRTCRenderModeHidden;
    canvas.uid = uid;
    canvas.roomId = roomId;
    userLiveView.uid = uid;
    /// 设置远端用户视频渲染视图
    [self.rtcVideo setRemoteVideoCanvas:uid withIndex:ByteRTCStreamIndexMain withCanvas:canvas];
}

#pragma mark - RTC delegate
- (void)rtcEngine:(ByteRTCVideo *)engine onFirstRemoteVideoFrameDecoded:(ByteRTCRemoteStreamKey *)streamKey withFrameInfo:(ByteRTCVideoFrameInfo *)frameInfo{
    NSLog(@"%@,%s",[NSThread currentThread],__func__);

    dispatch_async(dispatch_get_main_queue(), ^{
        if ([self.firstRemoteView.uid isEqualToString:streamKey.userId]) {
            [self setupRemoteView:self.firstRemoteView roomId:streamKey.roomId uid:streamKey.userId];
            return;
        }else if ([self.secondRemoteView.uid isEqualToString:streamKey.userId]) {
            [self setupRemoteView:self.secondRemoteView roomId:streamKey.roomId uid:streamKey.userId];
            return;
        }else if ([self.thirdRemoteView.uid isEqualToString: streamKey.userId]) {
            [self setupRemoteView:self.thirdRemoteView roomId:streamKey.roomId uid:streamKey.userId];
            return;
        }else{
            
        }
        
        if (self.firstRemoteView.uid.length == 0) {
            [self setupRemoteView:self.firstRemoteView roomId:streamKey.roomId uid:streamKey.userId];
        }else if (self.secondRemoteView.uid.length == 0) {
            [self setupRemoteView:self.secondRemoteView roomId:streamKey.roomId uid:streamKey.userId];
        }else if (self.thirdRemoteView.uid.length == 0) {
            [self setupRemoteView:self.thirdRemoteView roomId:streamKey.roomId uid:streamKey.userId];
        }else{
            
        }
    });
}

- (void)rtcRoom:(ByteRTCRoom *)rtcRoom onUserJoined:(ByteRTCUserInfo *)userInfo elapsed:(NSInteger)elapsed {
    NSLog(@"%@,%s",[NSThread currentThread],__func__);

}

- (void)rtcRoom:(ByteRTCRoom *)rtcRoom onUserLeave:(NSString *)uid reason:(ByteRTCUserOfflineReason)reason{
    NSLog(@"%@,%s",[NSThread currentThread],__func__);
    
    dispatch_async(dispatch_get_main_queue(), ^{
        for (UserLiveView *liveView in self.containerView.subviews) {
            if ([uid isEqualToString:liveView.uid]) {
                liveView.uid = @"";
            }
        }
    });
}

- (void)rtcEngine:(ByteRTCVideo *)engine onWarning:(ByteRTCWarningCode)Code {
    NSLog(@"warningCode = %ld", (long)Code);
}

- (void)rtcEngine:(ByteRTCVideo *)engine onError:(ByteRTCErrorCode)errorCode {
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
    [self.rtcVideo switchCamera:cameraID];
}

- (void)switchAudioRoute:(UIButton *)button{
    button.selected = !button.selected;
    if (button.selected) {
        /// 设置使用听筒播放音频数据
        [self.rtcVideo setAudioPlaybackDevice:ByteRTCAudioPlaybackDeviceEarpiece];
    }else{
        /// 设置使用扬声器播放音频数据
        [self.rtcVideo setAudioPlaybackDevice:ByteRTCAudioPlaybackDeviceSpeakerphone];
    }
}

- (void)enableLocalAudio:(UIButton *)button{
    button.selected = !button.selected;
    if (button.selected) {
        /// 关闭本地音频发送
        [self.rtcRoom unpublishStream:ByteRTCMediaStreamTypeAudio];
    }else{
        /// 开启本地音频发送
        [self.rtcRoom publishStream:ByteRTCMediaStreamTypeAudio];
    }
}

- (void)enableLocalVideo:(UIButton *)button{
    button.selected = !button.selected;
    if (button.selected) {
        /// 关闭视频采集
        [self.rtcVideo stopVideoCapture];
    }else{
        /// 开启视频采集
        [self.rtcVideo startVideoCapture];
    }
}

- (void)hangUp:(UIButton *)button{
    /// 离开房间
    [self.rtcRoom leaveRoom];
    
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
