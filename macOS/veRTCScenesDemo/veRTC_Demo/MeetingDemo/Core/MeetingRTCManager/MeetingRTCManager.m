//
//  MeetingRTCManager.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/3.
//

#import "MeetingRTCManager.h"

@interface MeetingRTCManager () <ByteRtcEngineDelegate>

@property (nonatomic, strong) ByteRtcEngineKit *rtcKit;

@property (nonatomic, strong) ByteRtcAudioDeviceManager *audioDeviceManager;
@property (nonatomic, strong) ByteRtcVideoDeviceManager *videoDeviceManager;

@property (nonatomic, strong) NSString *currentMicDeviceID;
@property (nonatomic, strong) NSString *currentCameraDeviceID;
@property (nonatomic, strong) NSMutableDictionary *subscribeUidDic;

@property (nonatomic, strong) ParamModel *currentParamModel;

@end


@implementation MeetingRTCManager

+ (MeetingRTCManager *)shareMeetingRTCManager {
    static MeetingRTCManager *meetingRTCManager = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        meetingRTCManager = [[self alloc] init];
    });
    return meetingRTCManager;
}

#pragma mark - Base Method

- (void)createEngine:(NSString *)appID {
    //设置rtc环境
    //kByteRtcEnvProduct
    [ByteRtcEngineKit setEnv:kByteRtcEnvProduct];
    
    //创建ByteRtcEninekit,需要申请AppId和Token
    //To create ByteRtcEninekit, you need to apply for AppId and Token
    self.rtcKit = [ByteRtcEngineKit sharedEngineWithAppId:appID
                                                 delegate:self];
    
}

- (void)startPreview:(NSView *)view {
    //绑定本地视图
    //Bind local view
    ByteRtcVideoCanvas *canvas = [[ByteRtcVideoCanvas alloc] init];
    canvas.view = view;
    canvas.renderMode = ByteRtc_Render_Hidden;
    [self.rtcKit setupLocalVideo:canvas];
    [self.rtcKit enableLocalVideo:YES];
    [self.rtcKit startPreview];
}

- (void)stopPreview {
    if (self.rtcKit != nil) {
        [self.rtcKit stopPreview];
        [self.rtcKit setupLocalVideo:nil];
    }
}

- (void)joinChannelWithUser:(LoginModel *_Nullable)loginModel {
    //置场景模式，多人场景中推荐使用 ByteChannelProfileLiveBroadcasting
    //Set scene mode, recommended to use ByteChannelProfileLiveBroadcasting in multiplayer scenes
    [self.rtcKit setChannelProfile:ByteChannelProfileLiveBroadcasting];
    
    //设置用户角色
    //Set user role
    [self.rtcKit setClientRole:ByteRtc_ClientRole_Broadcaster withKey:@""];
    
    //设置音频自动订阅，视频手动订阅
    //Set up automatic audio subscription, manual video subscription
    [self.rtcKit enableAutoSubscribe:kByteAutoSubscribeMode videoMode:kByteManualSubscribeMode];
    
    //设置订阅的音视频流回退选项
    //Set the subscribed audio and video stream fallback options
    [self.rtcKit setSubscribeFallbackOption:ByteSubscribeFallbackOptionsAudioOnly];
    
    //加入房间，开始连麦,需要申请AppId和Token
    //Join the room, start connecting the microphone, you need to apply for AppId and Token
    [self.rtcKit joinChannelByKey:loginModel.token
                      channelName:loginModel.roomId
                             info:nil
                              uid:loginModel.uid];
    //设置本地视频镜像
    //Set local video mirroring
    [self.rtcKit setLocalVideoMirrorMode:ByteVideoMirrorModeEnabled];
    //开启/关闭 本地音频采集
    //Turn on/off local audio capture
    [self enableLocalAudio:loginModel.isEnableAudio];
    //开启/关闭 本地视频采集
    //Turn on/off local video capture
    [self enableLocalVideo:loginModel.isEnableVideo];
}

- (void)leaveChannel:(void(^ _Nullable)(BOOL result))block {
    //离开房间
    //Leave the room
    [self.rtcKit leaveChannel:^(ByteRtcStats * _Nonnull stat) {
        if (block) {
            block(YES);
        }
    }];
    
    [self.subscribeUidDic removeAllObjects];
}

#pragma mark - Set Method

- (void)setupLocalVideo:(ByteRtcVideoCanvas *)videoCanvas {
    if (videoCanvas.view) {
        [self.rtcKit setupLocalVideo:videoCanvas];
    }
}

- (void)setupRemoteVideo:(ByteRtcVideoCanvas *)videoCanvas {
    if (videoCanvas.view) {
        [self.rtcKit setupRemoteVideo:videoCanvas];
    }
}

- (void)enableLocalVideo:(BOOL)isEnableVideo {
    [self.rtcKit enableLocalVideo:isEnableVideo];
    
    [[NSNotificationCenter defaultCenter] postNotificationName:NoticeUpdateLocalCameraStatusName object:@(isEnableVideo)];
}

- (void)enableLocalAudio:(BOOL)isEnableAudio {
    [self.rtcKit muteLocalAudioStream:!isEnableAudio];
}


- (int)setMicDevice:(NSString *)deviceID {
    _currentMicDeviceID = deviceID;
    return [self.audioDeviceManager setRecordingDevice:deviceID];
}

- (int)setCameraDevice:(NSString *)deviceID {
    _currentCameraDeviceID = deviceID;
    return [self.videoDeviceManager setDevice:deviceID];
}

- (void)setVideoProfiles:(SetingModel *)setingModel {
    if (!setingModel || ![setingModel isKindOfClass:[SetingModel class]]) {
        return;
    }
    NSMutableArray *profiles = [NSMutableArray new];
    ByteVideoSolution *localSolution = [[ByteVideoSolution alloc] init];
    localSolution.width = setingModel.resolutionSize.width;
    localSolution.height = setingModel.resolutionSize.height;
    localSolution.frameRate = setingModel.frameRate;
    localSolution.maxKbps = setingModel.bitRate;
    localSolution.scaleMode = FitWithFilling;
    localSolution.encoderPreference = ByteVideoEncoderPreferMaintainFramerate;
    [profiles addObject:localSolution];
    [self.rtcKit setVideoProfiles:profiles];
    
    self.currentParamModel.local_res = [NSString stringWithFormat:@"%ld * %ld", (long)localSolution.width, (long)localSolution.height];
    self.currentParamModel.local_fps = [NSString stringWithFormat:@"%ld", (long)localSolution.frameRate];
}

#pragma mark - Get Method

- (NSString *)getSdkVersion {
    return [ByteRtcEngineKit getSdkVersion];
}

- (ByteRtcAudioDeviceCollection * _Nullable)getRecordingDevices {
    self.audioDeviceManager = [self.rtcKit getAudioDeviceManager];
    return [self.audioDeviceManager enumerateRecordingDevices];
}

- (ByteRtcVideoDeviceCollection * _Nullable)getVideoDeviceDevices {
    self.videoDeviceManager = [self.rtcKit getVideoDeviceManager];
    return [self.videoDeviceManager enumerateVideoDevices];
}

- (NSString * _Nullable)getMicDeviceID {
    if (IsEmptyStr(_currentMicDeviceID)) {
        NSString *selectMicInputDeviceID = [[NSString alloc] init];
        [self.audioDeviceManager getRecordingDevice:&selectMicInputDeviceID];
        _currentMicDeviceID = selectMicInputDeviceID;
    }
    return _currentMicDeviceID;
}

- (NSString * _Nullable)getCameraDeviceID {
    if (IsEmptyStr(_currentCameraDeviceID)) {
        NSString *selectCameraInputDeviceID = [[NSString alloc] init];;
        [self.videoDeviceManager getDevice:&selectCameraInputDeviceID];
        _currentCameraDeviceID = selectCameraInputDeviceID;
    }
    return _currentCameraDeviceID;
}

#pragma mark - Subscribe Stream

- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine didStreamAdded:(ByteRtcByteStream* _Nonnull)stream {
    if (stream.isScreen) {
        if ([self.delegate respondsToSelector:@selector(rtcManager:didScreenStreamAdded:)]) {
            [self.delegate rtcManager:self didScreenStreamAdded:stream.uid];
        }
    } else {
        if ([self.delegate respondsToSelector:@selector(rtcManager:didStreamAdded:)]) {
            [self.delegate rtcManager:self didStreamAdded:stream.uid];
        }
    }
}

- (void)rtcEngine:(ByteRtcEngineKit *_Nonnull)engine didStreamRemoved:(ByteRtcByteStream *_Nonnull)stream reason:(RtcStreamRemoveReason)reason {
    if (stream.isScreen) {
        if ([self.delegate respondsToSelector:@selector(rtcManager:didScreenStreamRemoved:)]) {
            [self.delegate rtcManager:self didScreenStreamRemoved:stream.uid];
        }
    } else {
        [self.subscribeUidDic setValue:@"0" forKey:stream.uid];
        if ([self.delegate respondsToSelector:@selector(rtcManager:didStreamRemoved:)]) {
            [self.delegate rtcManager:self didStreamRemoved:stream.uid];
        }
    }
}

- (void)subscribeStream:(NSString *)uid {
    if (IsEmptyStr(uid)) {
        return;
    }
    NSString *value = [self.subscribeUidDic objectForKey:uid];
    if ([value integerValue] != 1) {
        ByteSubscribeConfig *config = [[ByteSubscribeConfig alloc] init];
        config.isScreen = NO;
        config.subVideo = YES;
        [self.rtcKit subscribeStream:uid info:config];
        [self.subscribeUidDic setValue:@"1" forKey:uid];
    }
}

- (void)subscribeScreenStream:(NSString *)uid {
    if (IsEmptyStr(uid)) {
        return;
    }
    ByteSubscribeConfig *config = [[ByteSubscribeConfig alloc] init];
    config.isScreen = YES;
    config.subVideo = YES;
    [self.rtcKit subscribeStream:uid info:config];
}

- (void)unsubscribe:(NSString *)uid {
    if (IsEmptyStr(uid)) {
        return;
    }
    NSString *value = [self.subscribeUidDic objectForKey:uid];
    if ([value integerValue] == 1) {
        [self.rtcKit unsubscribe:uid isScreen:NO];
        [self.subscribeUidDic setValue:@"0" forKey:uid];
    }
}

- (void)unsubscribeScreen:(NSString *)uid {
    if (IsEmptyStr(uid)) {
        return;
    }
    [self.rtcKit unsubscribe:uid isScreen:YES];
}

- (NSDictionary *_Nullable)getSubscribeUidDic {
    return [self.subscribeUidDic copy];
}

#pragma mark - Screen Method

- (void)updateScreenParameters {
    NSMutableArray *excludedWindowList = [[NSMutableArray alloc] init];
    CFArrayRef windowListArray = CGWindowListCreate(kCGWindowListOptionOnScreenAboveWindow, kCGNullWindowID);
    NSArray *windows = CFBridgingRelease(CGWindowListCreateDescriptionFromArray(windowListArray));
    for (NSMutableDictionary *dic in windows) {
        NSString *name = [dic objectForKey:(__bridge id)kCGWindowOwnerName];
        if ([name isEqualToString:@"veRTC"] ||
            [name isEqualToString:@"veRTC_Toast"]) {
            NSString *windowsID = [dic objectForKey:(__bridge id)kCGWindowNumber];
            if (windowsID) {
                [excludedWindowList addObject:windowsID];
            }
        }
    }
    CFRelease(windowListArray);
    NSData *data = [[NSUserDefaults standardUserDefaults] objectForKey:@"SetingModelCacheKey"];
    SetingModel *setingModel = [NSKeyedUnarchiver unarchiveObjectWithData:data];
    
    ByteRtcScreenCaptureParameters *parameters = [[ByteRtcScreenCaptureParameters alloc] init];
    parameters.maxWidth = setingModel.screenResolutionSize.width;
    parameters.maxHeight = setingModel.screenResolutionSize.height;
    parameters.frameRate = (int)setingModel.screenFrameRate;
    parameters.bitrate = (int)setingModel.screenBitRate;
    parameters.captureMouseCursor = YES;
    parameters.excludedWindowList = [excludedWindowList copy];
    
    ByteRtcHighlightConfig *config = [[ByteRtcHighlightConfig alloc] init];
    config.enableHighlight = YES;
    config.borderWidth = 4;
    config.borderColor = 0xFF29CCA3;
    parameters.highlightConfig = config;
    
    [self.rtcKit updateScreenCaptureParameters:parameters];
}

- (void)startScreenCaptureByDisplayId:(int)displayId {

    NSMutableArray *excludedWindowList = [[NSMutableArray alloc] init];
    CFArrayRef windowListArray = CGWindowListCreate(kCGWindowListOptionOnScreenAboveWindow, kCGNullWindowID);
    NSArray *windows = CFBridgingRelease(CGWindowListCreateDescriptionFromArray(windowListArray));
    for (NSMutableDictionary *dic in windows) {
        NSString *name = [dic objectForKey:(__bridge id)kCGWindowOwnerName];
        if ([name isEqualToString:@"veRTC"]) {
            NSString *windowsID = [dic objectForKey:(__bridge id)kCGWindowNumber];
            if (windowsID) {
                [excludedWindowList addObject:windowsID];
            }
        }
    }
    CFRelease(windowListArray);
    
    NSData *data = [[NSUserDefaults standardUserDefaults] objectForKey:@"SetingModelCacheKey"];
    SetingModel *setingModel = [NSKeyedUnarchiver unarchiveObjectWithData:data];
    
    ByteRtcScreenCaptureParameters *parameters = [[ByteRtcScreenCaptureParameters alloc] init];
    parameters.maxWidth = setingModel.screenResolutionSize.width;
    parameters.maxHeight = setingModel.screenResolutionSize.height;
    parameters.frameRate = (int)setingModel.screenFrameRate;
    parameters.bitrate = (int)setingModel.screenBitRate;
    parameters.captureMouseCursor = YES;
    parameters.excludedWindowList = [excludedWindowList copy];
    
    ByteRtcHighlightConfig *config = [[ByteRtcHighlightConfig alloc] init];
    config.enableHighlight = YES;
    config.borderWidth = 4;
    config.borderColor = 0xFF29CCA3;
    parameters.highlightConfig = config;
    
    [self.rtcKit startScreenCaptureByDisplayId:(intptr_t)(displayId) regionRect:CGRectZero captureParameters:parameters];
}

- (void)startScreenCaptureByWindowId:(int)windowId {
    NSData *data = [[NSUserDefaults standardUserDefaults] objectForKey:@"SetingModelCacheKey"];
    SetingModel *setingModel = [NSKeyedUnarchiver unarchiveObjectWithData:data];
    
    ByteRtcScreenCaptureParameters *parameters = [[ByteRtcScreenCaptureParameters alloc] init];
    parameters.maxWidth = setingModel.screenResolutionSize.width;
    parameters.maxHeight = setingModel.screenResolutionSize.height;
    parameters.frameRate = (int)setingModel.screenFrameRate;
    parameters.bitrate = (int)setingModel.screenBitRate;
    parameters.captureMouseCursor = YES;

    ByteRtcHighlightConfig *config = [[ByteRtcHighlightConfig alloc] init];
    config.enableHighlight = YES;
    config.borderWidth = 4;
    config.borderColor = 0xFF29CCA3;
    parameters.highlightConfig = config;
    
    [self.rtcKit startScreenCaptureByWindowId:(intptr_t)(windowId) regionRect:CGRectZero captureParameters:parameters];
}

- (void)stopScreenCapture {
    [self.rtcKit stopScreenCapture];
}

- (void)setupRemoteScreen:(NSView *)view uid:(NSString *)uid {
    ByteRtcVideoCanvas *cans = [[ByteRtcVideoCanvas alloc] init];
    cans.uid = uid;
    cans.renderMode = ByteRtc_Render_Fit;
    cans.view.backgroundColor = [NSColor clearColor];
    cans.view = view;
    [self.rtcKit setupRemoteScreen:cans];
}

- (void)removeAllRemoteScreen {
    [self.rtcKit removeAllRemoteScreen];
}

- (NSArray<ByteRtcScreenCaptureSourceInfo *> *_Nonnull)getScreenCaptureSourceList {
    return [self.rtcKit getScreenCaptureSourceList];
}

- (NSImage *_Nonnull)getScreenCaptureSourceThumbnail:(ByteScreenCaptureSourceType)sourceType sourceId:(intptr_t)sourceId maxWidth:(int)maxWidth maxHeight:(int)maxHeight {
    return [self.rtcKit getScreenCaptureSourceThumbnail:sourceType sourceId:sourceId maxWidth:maxWidth maxHeight:maxHeight];
}

#pragma mark - Volume Change

- (int)enableAudioVolumeIndication:(NSInteger)interval
                            smooth:(NSInteger)smooth {
    return [self.rtcKit enableAudioVolumeIndication:interval
                                             smooth:smooth];
}

- (void)rtcEngine:(ByteRtcEngineKit *)engine reportAudioVolumeIndicationOfSpeakers:(NSArray<ByteRtcAudioVolumeInfo *> *)speakers totalVolume:(NSInteger)totalVolume {
    NSArray *sorce = [speakers sortedArrayUsingComparator:^NSComparisonResult(ByteRtcAudioVolumeInfo *_Nonnull obj1, ByteRtcAudioVolumeInfo *_Nonnull obj2) {
        if (obj1.volume > obj2.volume) {
            return NSOrderedAscending;
        } else if (obj1.volume == obj2.volume) {
            return NSOrderedSame;
        } else {
            return NSOrderedDescending;
        }
    }];
    
    NSInteger minVolume = 10;
    sorce = [sorce subarrayWithRange:NSMakeRange(0, MIN(sorce.count, 9))];
    NSMutableDictionary *dic = [[NSMutableDictionary alloc] init];
    for (int i = 0; i < sorce.count; i++) {
        ByteRtcAudioVolumeInfo *model = sorce[i];
        if (model.volume > minVolume) {
            [dic setValue:model forKey:model.uid];
        }
    }
    if ([self.delegate respondsToSelector:@selector(rtcManager:reportAudioVolume:)]) {
        [self.delegate rtcManager:self reportAudioVolume:[dic copy]];
    }
}

#pragma mark - Rtc Stats

- (void)rtcEngine:(ByteRtcEngineKit *_Nonnull)engine localAudioStats:(ByteRtcLocalAudioStats *_Nonnull)stats {
    self.currentParamModel.local_bit_audio = [NSString stringWithFormat:@"%ld", (long)stats.sentKBitrate];
    
    [self updateReportRtcParamModel];
}

- (void)rtcEngine:(ByteRtcEngineKit *)engine localVideoStats:(ByteRtcLocalVideoStats *)stat {
    self.currentParamModel.local_bit_video = [NSString stringWithFormat:@"%ld", (long)stat.sentKBitrate];
    
    [self updateReportRtcParamModel];
}

- (void)rtcEngine:(ByteRtcEngineKit *)engine reportSysStats:(const ByteRtcSysStats *)stats {
    self.currentParamModel.remote_cpu_avg = [NSString stringWithFormat:@"%.2f", stats.cpu_app_usage * 100];
    if (stats.cpu_app_usage > [self.currentParamModel.remote_cpu_max floatValue] / 100.0) {
        self.currentParamModel.remote_cpu_max = [NSString stringWithFormat:@"%.2f", stats.cpu_app_usage * 100];
    }
    
    [self updateReportRtcParamModel];
}

- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine remoteAudioStats:(ByteRtcRemoteAudioStats * _Nonnull)stats {
    self.currentParamModel.remote_rtt_audio = [NSString stringWithFormat:@"%ld",(long)stats.rtt];
    self.currentParamModel.remote_bit_audio = [NSString stringWithFormat:@"%ld",(long)stats.receivedKBitrate];
    self.currentParamModel.remote_loss_audio = [NSString stringWithFormat:@"%ld",(long)stats.audioLossRate];
    
    [self updateReportRtcParamModel];
}

- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine remoteVideoStats:(ByteRtcRemoteVideoStats * _Nonnull)stats {
    self.currentParamModel.remote_rtt_video = [NSString stringWithFormat:@"%ld",(long)stats.rtt];
    self.currentParamModel.remote_bit_video = [NSString stringWithFormat:@"%ld",(long)stats.receivedKBitrate];
    
    if (stats.width * stats.height <= self.currentParamModel.remote_res_min_w * self.currentParamModel.remote_res_min_h ||
        (self.currentParamModel.remote_res_min_w == 0 && self.currentParamModel.remote_res_min_h == 0)) {
        self.currentParamModel.remote_res_min_w = stats.width;
        self.currentParamModel.remote_res_min_h = stats.height;
    }
    if (stats.width * stats.height > self.currentParamModel.remote_res_max_w * self.currentParamModel.remote_res_max_h) {
        self.currentParamModel.remote_res_max_w = stats.width;
        self.currentParamModel.remote_res_max_h = stats.height;
    }
    self.currentParamModel.remote_res_min = [NSString stringWithFormat:@"%ld*%ld",
                                             (long)self.currentParamModel.remote_res_min_w,
                                             (long)self.currentParamModel.remote_res_min_h];
    self.currentParamModel.remote_res_max = [NSString stringWithFormat:@"%ld*%ld",
                                             (long)self.currentParamModel.remote_res_max_w,
                                             (long)self.currentParamModel.remote_res_max_h];
    self.currentParamModel.remote_fps_min = [NSString stringWithFormat:@"%ld",(long)stats.receivedFrameRate];
    self.currentParamModel.remote_fps_max = [NSString stringWithFormat:@"%ld",(long)stats.receivedFrameRate];
    self.currentParamModel.remote_loss_video = [NSString stringWithFormat:@"%ld",(long)stats.videoLossRate];
    
    [self updateReportRtcParamModel];
}

#pragma mark - Private Action

- (void)updateReportRtcParamModel {
    dispatch_async(dispatch_get_main_queue(), ^{
        if ([self.delegate respondsToSelector:@selector(rtcManager:reportRtcParamModel:)]) {
            [self.delegate rtcManager:self reportRtcParamModel:self.currentParamModel];
        }
    });
}

#pragma mark - tool

- (void)log:(NSString *)message {
    NSLog(@"[%@]%@", self.className, message);
}

#pragma mark - getter

- (ParamModel *)currentParamModel {
    if (!_currentParamModel) {
        _currentParamModel = [[ParamModel alloc] init];
    }
    return _currentParamModel;
}

- (NSMutableDictionary *)subscribeUidDic {
    if (!_subscribeUidDic) {
        _subscribeUidDic = [[NSMutableDictionary alloc] init];
    }
    return _subscribeUidDic;
}

@end
