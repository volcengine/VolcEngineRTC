#import "SettingsService.h"
#import "MeetingRTCManager.h"
#import "AlertActionManager.h"

@interface MeetingRTCManager () <ByteRtcEngineDelegate>

@property (nonatomic, strong) ByteRtcEngineKit *rtcKit;
@property (nonatomic, strong) RoomParamInfoModel *paramInfoModel;
@property (nonatomic, strong) RoomVideoSession *localVideoSession;

@property (nonatomic, strong) NSMutableDictionary *subscribeUidDic;

@end

@implementation MeetingRTCManager

+ (MeetingRTCManager *_Nullable)shareRtc {
    static MeetingRTCManager *meetingRTCManager = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        meetingRTCManager = [[MeetingRTCManager alloc] init];
    });
    return meetingRTCManager;
}

#pragma mark - Publish Action

- (void)createEngine:(NSString *)appID {
    //设置SDK当前使用的环境
    //kByteRtcEnvProduct
    [ByteRtcEngineKit setEnv:kByteRtcEnvProduct];
    
    //创建ByteRtcEninekit,需要申请AppId和Token
    //To create ByteRtcEninekit, you need to apply for AppId and Token
    self.rtcKit = [ByteRtcEngineKit sharedEngineWithAppId:appID
                                                 delegate:self];
}

- (void)joinChannelWithRoomVideoSession:(RoomVideoSession *)videoSession {
    //置场景模式，多人场景中推荐使用 ByteChannelProfileLiveBroadcasting
    //Set scene mode, recommended to use ByteChannelProfileLiveBroadcasting in multiplayer scenes
    [self.rtcKit setChannelProfile:ByteChannelProfileLiveBroadcasting];
    
    //设置用户角色
    //Set user role
    [self.rtcKit setClientRole:ByteRtc_ClientRole_Broadcaster];
    
    //设置音频自动订阅，视频手动订阅
    //Set up automatic audio subscription, manual video subscription
    [self.rtcKit enableAutoSubscribe:kByteAutoSubscribeMode videoMode:kByteManualSubscribeMode];
    
    //设置订阅的音视频流回退选项
    //Set the subscribed audio and video stream fallback options
    [self.rtcKit setSubscribeFallbackOption:ByteSubscribeFallbackOptionAudioOnly];

    //开启/关闭 本地音频采集
    //Turn on/off local audio capture
    [self enableLocalAudio:videoSession.isEnableAudio];

    //Turn on/off local video capture
    [self enableLocalVideo:videoSession.isEnableVideo];

    //设置音频路由模式，YES 扬声器/NO 听筒
    //Set the audio routing mode, YES speaker/NO earpiece
    [self setEnableSpeakerphone:YES];

    //设置本地视频镜像
    //Set local video mirroring
    [self.rtcKit setLocalVideoMirrorMode:ByteVideoMirrorModeEnabled];
    
    //开启/关闭发言者音量键控
    //Turn on/off speaker volume keying
    [self.rtcKit enableAudioVolumeIndication:2000 smooth:8];

    //加入房间，开始连麦,需要申请AppId和Token
    //Join the room, start connecting the microphone, you need to apply for AppId and Token
    [self.rtcKit joinChannelByKey:videoSession.token
                      channelName:videoSession.roomId
                             info:nil
                              uid:videoSession.uid];
}

- (NSString *_Nullable)getSdkVersion {
    return [ByteRtcEngineKit getSdkVersion];
}

#pragma mark - rtc method

- (void)updateRtcVideoParams {
    NSMutableArray *profiles = [[NSMutableArray alloc] init];
    VideoStreamDescription *localSolution = [[VideoStreamDescription alloc] init];
    localSolution.videoSize = [SettingsService getResolution];
    localSolution.frameRate = [SettingsService getFrameRate];
    localSolution.maxKbps = [SettingsService getKBitRate];
    localSolution.mode = ByteVideoStreamScaleModeFitWithFilling;
    localSolution.encoderPreference = ByteVideoEncoderPreferMaintainFramerate;
    [profiles addObject:localSolution];
    
    //设置本地视频属性
    //Set local video attributes
    [self.rtcKit setVideoProfiles:profiles];
}

- (void)switchCamera {
    //切换 前置/后置 摄像头
    //Switch front/rear camera
    [self.rtcKit switchCamera];
}

- (int)setEnableSpeakerphone:(BOOL)enableSpeaker {
    //打开/关闭 外放
    //Turn on/off the loudspeaker
    return [self.rtcKit setEnableSpeakerphone:enableSpeaker];
}
- (void)enableLocalAudio:(BOOL)enable {
    //开启/关闭 本地音频采集
    //Turn on/off local audio capture
    [self.rtcKit muteLocalAudioStream:!enable];
}

- (void)enableLocalVideo:(BOOL)enable {
    //开启/关闭 本地视频采集
    //Turn on/off local video capture
    [self.rtcKit enableLocalVideo:enable];
}

- (void)leaveChannel {
    //离开频道
    //Leave the channel
    [self.rtcKit leaveChannel:^(ByteRtcStats *_Nonnull stat){
        //do something
        NSLog(@"dealloc == leaveChannel");
    }];
    [self.subscribeUidDic removeAllObjects];
}

- (void)destroy {
    [ByteRtcEngineKit destroy];
}

- (void)startPreview:(UIView *)view {
    ByteRtcVideoCanvas *canvas = [[ByteRtcVideoCanvas alloc] init];
    canvas.view = view;
    canvas.renderMode = ByteRtc_Render_Hidden;
    canvas.view.backgroundColor = [UIColor clearColor];
    //设置本地视频显示信息
    //Set local video display information
    [self.rtcKit setupLocalVideo:canvas];
    [self.rtcKit enableLocalVideo:YES];
    [self.rtcKit startPreview];
}

- (void)subscribeStream:(NSString *_Nullable)uid {
    if (IsEmptyStr(uid)) {
        return;
    }
    NSString *value = [self.subscribeUidDic objectForKey:uid];
    if ([value integerValue] != 1) {
        SubscribeConfig *config = [[SubscribeConfig alloc] init];
        config.isScreen = NO;
        config.subscribeVideo = YES;
        [self.rtcKit subscribeStream:uid subscribeConfig:config];
        [self.subscribeUidDic setValue:@"1" forKey:uid];
    }
}

- (void)subscribeScreenStream:(NSString *)uid {
    if (IsEmptyStr(uid)) {
        return;
    }
    SubscribeConfig *config = [[SubscribeConfig alloc] init];
    config.isScreen = YES;
    config.subscribeVideo = YES;
    [self.rtcKit subscribeStream:uid subscribeConfig:config];
}

- (void)unsubscribe:(NSString *_Nullable)uid {
    if (IsEmptyStr(uid)) {
        return;
    }
    NSString *value = [self.subscribeUidDic objectForKey:uid];
    if ([value integerValue] == 1) {
        [self.rtcKit unSubscribeStream:uid isScreen:NO];
        [self.subscribeUidDic setValue:@"0" forKey:uid];
    }
}

- (void)unsubscribeScreen:(NSString *)uid {
    if (IsEmptyStr(uid)) {
        return;
    }
    [self.rtcKit unSubscribeStream:uid isScreen:YES];
}

- (NSDictionary *_Nullable)getSubscribeUidDic {
    return [self.subscribeUidDic copy];
}

- (void)setupRemoteVideo:(ByteRtcVideoCanvas *)canvas {
    [self.rtcKit setupRemoteVideo:canvas];
}

- (void)setupLocalVideo:(ByteRtcVideoCanvas *)canvas {
    [self.rtcKit setupLocalVideo:canvas];
}

- (void)setupRemoteScreen:(UIView *)view uid:(NSString *)uid {
    ByteRtcVideoCanvas *cans = [[ByteRtcVideoCanvas alloc] init];
    cans.uid = uid;
    cans.renderMode = ByteRtc_Render_Fit;
    cans.view.backgroundColor = [UIColor clearColor];
    cans.view = view;
    [self.rtcKit setupRemoteScreen:cans];
}

#pragma mark - ByteRtcEngineDelegate

- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine
      onStreamAdd:(id <ByteStream> _Nonnull)stream {
    if (stream.isScreen) {
        if ([self.delegate respondsToSelector:@selector(rtcManager:didScreenStreamAdded:)]) {
            [self.delegate rtcManager:self didScreenStreamAdded:stream.userId];
        }
    } else {
        NSLog(@"yuboyang-onStreamAdd%@",stream.userId);
        if ([self.delegate respondsToSelector:@selector(rtcManager:didStreamAdded:)]) {
            [self.delegate rtcManager:self didStreamAdded:stream.userId];
        }
    }
}

- (void)rtcEngine:(ByteRtcEngineKit *_Nonnull)engine
    didStreamRemoved:(NSString *_Nonnull)uid
              stream:(id<ByteStream> _Nonnull)stream
              reason:(RtcStreamRemoveReason)reason {
    if (stream.isScreen) {
        if ([self.delegate respondsToSelector:@selector(rtcManager:didScreenStreamRemoved:)]) {
            [self.delegate rtcManager:self didScreenStreamRemoved:stream.userId];
        }
    } else {
        [self.subscribeUidDic setValue:@"0" forKey:stream.userId];
        if ([self.delegate respondsToSelector:@selector(rtcManager:didStreamRemoved:)]) {
            [self.delegate rtcManager:self didStreamRemoved:stream.userId];
        }
    }
}

#pragma mark - Rtc Stats

- (void)rtcEngine:(ByteRtcEngineKit *)engine localVideoStats:(ByteRtcLocalVideoStats *)stats {
    self.paramInfoModel.local_bit_video = [NSString stringWithFormat:@"%.0f",stats.sentKBitrate];
    self.paramInfoModel.local_fps = [NSString stringWithFormat:@"%ld",(long)stats.inputFrameRate];
    self.paramInfoModel.local_res = [NSString stringWithFormat:@"%ld*%ld",(long)stats.encodedFrameWidth, stats.encodedFrameHeight];
    
    [self updateRoomParamInfoModel];
}

- (void)rtcEngine:(ByteRtcEngineKit *_Nonnull)engine localAudioStats:(ByteRtcLocalAudioStats *_Nonnull)stats {
    self.paramInfoModel.local_bit_audio = [NSString stringWithFormat:@"%.0f",stats.sentKBitrate];
    
    [self updateRoomParamInfoModel];
}

- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine remoteVideoStats:(ByteRtcRemoteVideoStats * _Nonnull)stats {
    self.paramInfoModel.remote_rtt_video = [NSString stringWithFormat:@"%ld",(long)stats.rtt];
    self.paramInfoModel.remote_bit_video = [NSString stringWithFormat:@"%ld",(long)stats.receivedKBitrate];
    self.paramInfoModel.remote_res_min = [NSString stringWithFormat:@"%ld*%ld",(long)stats.width, stats.height];
    self.paramInfoModel.remote_res_max = [NSString stringWithFormat:@"%ld*%ld",(long)stats.width, stats.height];
    self.paramInfoModel.remote_fps_min = [NSString stringWithFormat:@"%ld",(long)stats.receivedFrameRate];
    self.paramInfoModel.remote_fps_max = [NSString stringWithFormat:@"%ld",(long)stats.receivedFrameRate];
    self.paramInfoModel.remote_loss_video = [NSString stringWithFormat:@"%ld",(long)stats.videoLossRate];
    
    [self updateRoomParamInfoModel];
}

- (void)rtcEngine:(ByteRtcEngineKit *)engine reportSysStats:(const ByteRtcSysStats *)stats {
    self.paramInfoModel.remote_cpu_avg = [NSString stringWithFormat:@"%.2f", stats.cpu_app_usage * 100];
    if (stats.cpu_app_usage > [self.paramInfoModel.remote_cpu_max floatValue] / 100.0) {
        self.paramInfoModel.remote_cpu_max = [NSString stringWithFormat:@"%.2f", stats.cpu_app_usage * 100];
    }
    
    [self updateRoomParamInfoModel];
}

- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine remoteAudioStats:(ByteRtcRemoteAudioStats * _Nonnull)stats {
    self.paramInfoModel.remote_rtt_audio = [NSString stringWithFormat:@"%ld",(long)stats.rtt];
    self.paramInfoModel.remote_bit_audio = [NSString stringWithFormat:@"%ld",(long)stats.receivedKBitrate];
    self.paramInfoModel.remote_loss_audio = [NSString stringWithFormat:@"%ld",(long)stats.audioLossRate];
    
    [self updateRoomParamInfoModel];
}

- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine reportAudioVolumeIndicationOfSpeakers:(NSArray<ByteRtcAudioVolumeInfo *> * _Nonnull)speakers totalVolume:(NSInteger)totalVolume {
    NSInteger minVolume = 10;
    NSMutableDictionary *parDic = [[NSMutableDictionary alloc] init];
    for (int i = 0; i < speakers.count; i++) {
        ByteRtcAudioVolumeInfo *model = speakers[i];
        if (model.volume > minVolume) {
            [parDic setValue:@(model.volume) forKey:model.uid];
        }
    }
    if ([self.delegate respondsToSelector:@selector(rtcManager:reportAllAudioVolume:)]) {
        [self.delegate rtcManager:self reportAllAudioVolume:[parDic copy]];
    }
}

- (void)startScreenSharingWithParam:(ScreenCaptureParam *_Nonnull)param preferredExtension:(NSString *_Nullable)extension groupId:(NSString *_Nonnull)groupId {
    [self.rtcKit startScreenSharingWithParam:param preferredExtension:extension groupId:groupId];
}

- (void)stopScreenSharing {
    [self.rtcKit stopScreenSharing];
}

#pragma mark - Private Action

- (void)updateRoomParamInfoModel {
    if ([self.delegate respondsToSelector:@selector(meetingRTCManager:changeParamInfo:)]) {
        [self.delegate meetingRTCManager:self changeParamInfo:self.paramInfoModel];
    }
}

#pragma mark - getter
- (RoomParamInfoModel *)paramInfoModel {
    if (!_paramInfoModel) {
        _paramInfoModel = [[RoomParamInfoModel alloc] init];
    }
    return _paramInfoModel;
}

- (NSMutableDictionary *)subscribeUidDic {
    if (!_subscribeUidDic) {
        _subscribeUidDic = [[NSMutableDictionary alloc] init];
    }
    return _subscribeUidDic;
}

- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

@end
