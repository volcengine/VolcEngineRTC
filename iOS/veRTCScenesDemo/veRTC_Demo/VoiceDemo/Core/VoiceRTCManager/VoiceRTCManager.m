#import "SettingsService.h"
#import "VoiceRTCManager.h"
#import "AlertActionManager.h"

@interface VoiceRTCManager () <ByteRtcEngineDelegate>

@property (nonatomic, strong) ByteRtcEngineKit *rtcKit;
@property (nonatomic, strong) VoiceRoomParamInfoModel *paramInfoModel;

@end

@implementation VoiceRTCManager

+ (VoiceRTCManager *_Nullable)shareRtc {
    static VoiceRTCManager *voiceRTCManager = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        voiceRTCManager = [[VoiceRTCManager alloc] init];
    });
    return voiceRTCManager;
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

- (void)joinChannelWithToken:(NSString *)token roomID:(NSString *)roomID uid:(NSString *)uid {
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

    //关闭 本地音频/视频采集
    //Turn on/off local audio capture
    [self.rtcKit enableLocalAudio:NO];
    [self.rtcKit enableLocalVideo:NO];

    //设置音频路由模式，YES 扬声器/NO 听筒
    //Set the audio routing mode, YES speaker/NO earpiece
    [self.rtcKit setEnableSpeakerphone:YES];
    
    //开启/关闭发言者音量键控
    //Turn on/off speaker volume keying
    [self.rtcKit enableAudioVolumeIndication:200 smooth:8];

    //加入房间，开始连麦,需要申请AppId和Token
    //Join the room, start connecting the microphone, you need to apply for AppId and Token
    [self.rtcKit joinChannelByKey:token
                      channelName:roomID
                             info:nil
                              uid:uid];
}

- (NSString *_Nullable)getSdkVersion {
    return [ByteRtcEngineKit getSdkVersion];
}

#pragma mark - rtc method

- (void)enableLocalAudio:(BOOL)enable {
    //开启/关闭 本地音频采集
    //Turn on/off local audio capture
    [self.rtcKit enableLocalAudio:enable];
}

- (void)muteLocalAudio:(BOOL)mute {
    //开启/关闭 本地音频采集
    //Turn on/off local audio capture
    [self.rtcKit muteLocalAudioStream:mute];
}

- (void)leaveChannel {
    //离开频道
    //Leave the channel
    [self.rtcKit leaveChannel:^(ByteRtcStats *_Nonnull stat){
        //do something
        NSLog(@"dealloc == leaveChannel");
    }];
}

- (void)destroy {
    [ByteRtcEngineKit destroy];
}

#pragma mark - ByteRtcEngineDelegate

- (void)rtcEngine:(ByteRtcEngineKit *_Nonnull)engine localAudioStats:(ByteRtcLocalAudioStats *_Nonnull)stats {
    self.paramInfoModel.numChannels = [NSString stringWithFormat:@"%.0ld",(long)stats.numChannels];
    self.paramInfoModel.sentSampleRate = [NSString stringWithFormat:@"%.0ld",(long)stats.sentSampleRate];
    self.paramInfoModel.sentKBitrate = [NSString stringWithFormat:@"%.0f",stats.sentKBitrate];
    self.paramInfoModel.audioLossRate = [NSString stringWithFormat:@"%.0f",stats.audioLossRate];
    
    self.paramInfoModel.recordKBitrate = @"";
    self.paramInfoModel.recordLossRate = @"";
    self.paramInfoModel.rtt = [NSString stringWithFormat:@"%.0ld",(long)stats.rtt];
    
    [self updateRoomParamInfoModel];
}

- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine reportAudioVolumeIndicationOfSpeakers:(NSArray<ByteRtcAudioVolumeInfo *> * _Nonnull)speakers totalVolume:(NSInteger)totalVolume {
    NSMutableDictionary *dic = [[NSMutableDictionary alloc] init];
    for (int i = 0; i < speakers.count; i++) {
        ByteRtcAudioVolumeInfo *model = speakers[i];
        [dic setValue:@(model.volume) forKey:model.uid];
    }
    if ([self.delegate respondsToSelector:@selector(voiceRTCManager:reportAllAudioVolume:)]) {
        [self.delegate voiceRTCManager:self reportAllAudioVolume:dic];
    }
}

#pragma mark - Private Action

- (void)updateRoomParamInfoModel {
    dispatch_async(dispatch_get_main_queue(), ^{
        if ([self.delegate respondsToSelector:@selector(voiceRTCManager:changeParamInfo:)]) {
            [self.delegate voiceRTCManager:self changeParamInfo:self.paramInfoModel];
        }
    });
}

#pragma mark - getter

- (VoiceRoomParamInfoModel *)paramInfoModel {
    if (!_paramInfoModel) {
        _paramInfoModel = [[VoiceRoomParamInfoModel alloc] init];
    }
    return _paramInfoModel;
}

@end
