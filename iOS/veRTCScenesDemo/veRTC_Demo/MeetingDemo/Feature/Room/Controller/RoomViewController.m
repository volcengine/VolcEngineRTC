#import "RoomViewController.h"
#import "SettingViewController.h"
#import "SettingsService.h"
#import "SystemAuthority.h"
#import "RoomNavView.h"
#import "UIViewController+Orientation.h"
#import "RoomViewController+Listener.h"
#import "RoomSpeakerView.h"
#import "RoomParamInfoView.h"
#import "MeetingEndCompoments.h"
#import "MeetingScreenComponents.h"

@interface RoomViewController () <UINavigationControllerDelegate, MeetingRTCManagerDelegate, RoomNavViewDelegate, RoomBottomViewDelegate>
@property (nonatomic, strong) RoomNavView *navView;
@property (nonatomic, strong) RoomParamInfoView *paramInfoView;
@property (nonatomic, strong) UIView *toastView;
@property (nonatomic, strong) UIImageView *recordTipView;
@property (nonatomic, strong) NSString *recordID;
@property (nonatomic, strong) RoomMatrixView *videoMatrixView;
@property (nonatomic, strong) RoomSpeakerView *videoSpeakerView;
@property (nonatomic, strong) MeetingEndCompoments *endCompoments;

@property (nonatomic, strong) NSMutableArray<RoomVideoSession *> *currentUserLists;
@property (nonatomic, copy) NSArray <RoomVideoSession *> *currentTopUserLists;
@property (nonatomic, strong) NSMutableDictionary <NSString *, NSString *> *currentStreamDic;
@property (nonatomic, assign) BOOL isLandscape;
@property (nonatomic, strong) MeetingScreenComponents *screenComponents;

@property (nonatomic, strong) dispatch_semaphore_t lock;

@end

@implementation RoomViewController

- (instancetype)initWithVideoSession:(RoomVideoSession *)videoSession {
    self = [super init];
    if (self) {
        [UIApplication sharedApplication].idleTimerDisabled = YES;
        _localVideoSession = videoSession;
        _isLandscape = NO;
    }
    return self;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor colorFromHexString:@"#1D2129"];
    
    [self addSocketListener];
    [self addOrientationNotice];
    [self createUIComponents];

    [self loadDataWithMeetingContrller];
    [MeetingRTCManager shareRtc].delegate = self;
    [[MeetingRTCManager shareRtc] joinChannelWithRoomVideoSession:_localVideoSession];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(meetingControlChange:) name:NotificationMeetingControlChange object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(socketStatusChange:) name:NotificationSocketStatusChange object:nil];
    
    __weak __typeof(self) wself = self;
    self.videoSpeakerView.clickOrientationBlock = ^{
        if (!wself.isLandscape) {
            [wself setDeviceInterfaceOrientation:UIDeviceOrientationLandscapeLeft];
        } else {
            [wself setDeviceInterfaceOrientation:UIDeviceOrientationPortrait];
        }
    };
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    
    [self.navigationController setNavigationBarHidden:YES animated:NO];
    [[MeetingRTCManager shareRtc] updateRtcVideoParams];
    
    if (self.currentRoomModel) {
        if (!self.videoSpeakerView.hidden) {
            [self setAllowAutoRotate:YES];
        } else {
            [self setAllowAutoRotate:NO];
        }
    }
}

- (void)viewDidDisappear:(BOOL)animated {
    [super viewDidDisappear:animated];
    
    [self setAllowAutoRotate:NO];
}

- (void)orientationDidChang:(BOOL)isLandscape {
    _isLandscape = isLandscape;
    CGFloat navHeight = 44 + [DeviceInforTool getStatusBarHight];
    CGFloat bottomBottom = 0;
    if (isLandscape) {
        navHeight = 0;
        bottomBottom = (128/2 + [DeviceInforTool getVirtualHomeHeight] * 2);
    }
    
    [self.navView mas_updateConstraints:^(MASConstraintMaker *make) {
        make.height.mas_equalTo(navHeight);
    }];
    [self.bottomView mas_updateConstraints:^(MASConstraintMaker *make) {
        make.bottom.equalTo(self.view).offset(bottomBottom);
    }];
    self.videoSpeakerView.isLandscape = isLandscape;
    [self.bottomView dismissMoreView];
    [self updateRecordTipViewTop];
}

#pragma mark - Publish Action

- (void)updateRenderModeViewWithCameraStatus:(NSString *)uid enableCamera:(BOOL)isEnable {
    for (RoomVideoSession *userModel in self.currentTopUserLists) {
        if ([userModel.uid isEqualToString:uid]) {
            userModel.isEnableVideo = isEnable;
            break;
        }
    }
    [self updateRenderModeView];
}

- (void)updateRenderModeViewWithMicStatus:(NSString *)uid enableMic:(BOOL)isEnable {
    for (RoomVideoSession *userModel in self.currentUserLists) {
        if ([userModel.uid isEqualToString:uid]) {
            userModel.audioType = isEnable ? 1 : 2;
            break;
        }
    }
}

- (void)hangUp {
    //User screen sharing
    if ([self.currentRoomModel.screen_shared_uid isEqualToString:self.localVideoSession.uid]) {
        [MeetingControlCompoments endShareScreen];
        [[MeetingRTCManager shareRtc] stopScreenSharing];
    }
    //socket api end/leave Meeting
    if ([self.currentRoomModel.host_id isEqualToString:self.localVideoSession.uid]) {
        [MeetingControlCompoments endMeeting];
    } else {
        [MeetingControlCompoments leaveMeeting];
    }
    //sdk api end Meeting
    [[MeetingRTCManager shareRtc] leaveChannel];
    //ui
    [self dismissViewControllerAnimated:YES completion:nil];
    if (self.closeRoomBlock) {
        BOOL isEnableAudio = ([self.bottomView getButtonStatus:RoomBottomStatusMic] == ButtonStatusActive) ? NO : YES;
        BOOL isEnableVideo = ([self.bottomView getButtonStatus:RoomBottomStatusCamera] == ButtonStatusActive) ? NO : YES;
        self.closeRoomBlock(isEnableAudio, isEnableVideo);
    }
}

- (void)updateModeWithStatus:(RoomModeStatus)roomModeStatus {
    if (roomModeStatus == RoomModeStatusGallery) {
        self.videoSpeakerView.hidden = YES;
        self.videoMatrixView.hidden = NO;
        [self setAllowAutoRotate:NO];
    } else {
        self.videoMatrixView.hidden = YES;
        self.videoSpeakerView.hidden = NO;
        self.videoSpeakerView.localVideoSession = self.localVideoSession;
        self.videoSpeakerView.currentRoomModel = self.currentRoomModel;
        [self setAllowAutoRotate:YES];
    }
    [self updateRecordTipViewTop];
}

- (void)updateRecordTipViewTop {
    CGFloat recorderTop = 12;
    if (!self.videoMatrixView.hidden) {
        recorderTop = 12;
    } else if (!self.videoSpeakerView.hidden) {
        if (self.isLandscape) {
            recorderTop = 30;
        } else {
            recorderTop = 104;
        }
    } else {
        recorderTop = 12;
    }
    [self.recordTipView mas_updateConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(self.navView.mas_bottom).offset(recorderTop);
    }];
}

- (void)updateRenderModeView {
    dispatch_semaphore_wait(self.lock, DISPATCH_TIME_FOREVER);
    dispatch_async(dispatch_get_main_queue(), ^{
        if (!self.videoMatrixView.hidden) {
            [self.videoMatrixView bindVideoSessions:self.currentUserLists];
        } else if (!self.videoSpeakerView.hidden) {
            [self.videoSpeakerView bindVideoSessions:self.currentUserLists];
        } else {
            //error
        }
        [self updateCurrentUserListHostStatus];
    });
    dispatch_semaphore_signal(self.lock);
}


- (void)updateRecordTipStatusWithHidden:(BOOL)isHidden {
    self.recordTipView.hidden = isHidden;
    [self.bottomView updateButtonStatus:RoomBottomStatusRecord close:!isHidden];
}

- (void)updateRenderModeViewWithScreenStatus:(NSString *)uid enableScreen:(BOOL)isShare {
    for (RoomVideoSession *userModel in self.currentTopUserLists) {
        if (isShare) {
            if ([userModel.uid isEqualToString:uid]) {
                userModel.isScreen = YES;
            } else {
                userModel.isScreen = NO;
            }
        } else {
            userModel.isScreen = NO;
        }
    }
    [self updateRenderModeView];
}

- (void)restoreScreenOrientation {
    if (self.isLandscape) {
        [self setDeviceInterfaceOrientation:UIDeviceOrientationPortrait];
    }
}

#pragma mark - MeetingRTCManagerDelegate

- (void)rtcManager:(MeetingRTCManager * _Nonnull)rtcManager didStreamAdded:(NSArray<NSString *> *_Nullable)streamsUid {
    if ([self getRenderViewTopUserModel].count < 9) {
        //需要立即刷新
        //Need to refresh immediately
        for (NSString *uid in streamsUid) {
            for (RoomVideoSession *userModel in self.currentTopUserLists) {
                if ([userModel.uid isEqualToString:uid]) {
                    userModel.isVideoStream = YES;
                    [[MeetingRTCManager shareRtc] subscribeStream:userModel.uid];
                }
            }
        }
        [self updateRenderModeView];
    }
    //添加到缓存池
    //Current video stream buffer pool
    for (NSString *uid in streamsUid) {
        [self.currentStreamDic setValue:@"1" forKey:uid];
    }
}

- (void)rtcManager:(MeetingRTCManager *_Nonnull)rtcManager didStreamRemoved:(NSArray<NSString *> *_Nullable)streamsUid {
    for (RoomVideoSession *model in self.currentTopUserLists) {
        for (NSString *removeUid in streamsUid) {
            if ([model.uid isEqualToString:removeUid]) {
                model.isVideoStream = NO;
            }
        }
    }
    [self.currentStreamDic removeObjectsForKeys:streamsUid];
    [self updateRenderModeView];
}

- (void)rtcManager:(MeetingRTCManager * _Nonnull)rtcManager didScreenStreamAdded:(NSString *_Nullable)screenStreamsUid {
    self.videoSpeakerView.screenStreamsUid = screenStreamsUid;
}

- (void)rtcManager:(MeetingRTCManager *_Nonnull)rtcManager didScreenStreamRemoved:(NSString *)screenStreamsUid {
    if ([self.videoSpeakerView.screenStreamsUid isEqualToString:screenStreamsUid]) {
        self.videoSpeakerView.screenStreamsUid = nil;
    }
}

- (void)meetingRTCManager:(MeetingRTCManager *)meetingRTCManager changeParamInfo:(RoomParamInfoModel *)model {
    self.paramInfoView.paramInfoModel = model;
}

- (void)rtcManager:(MeetingRTCManager *)rtcManager reportAudioVolume:(NSDictionary<NSString *,ByteRtcAudioVolumeInfo *> *)volumeInfo {
    [self updateRenderModeViewUserRankeWithAudioVolume:volumeInfo];
}

- (void)rtcManager:(MeetingRTCManager *)rtcManager reportAllAudioVolume:(NSDictionary<NSString *, NSNumber *> *)volumeInfo {
    [self.userListViewController updateUserMicStatus:volumeInfo];
}

#pragma mark - RoomBottomViewDelegate

- (void)roomBottomView:(RoomBottomView *)roomBottomView itemButton:(RoomItemButton *)itemButton didSelectStatus:(RoomBottomStatus)status {
    if (status == RoomBottomStatusMic) {
        [self clickRoomBottomStatusMic:itemButton];
    } else if (status == RoomBottomStatusCamera) {
        [self clickRoomBottomStatusCamera:itemButton];
    } else if (status == RoomBottomStatusScreen) {
        if (itemButton.status == ButtonStatusNone) {
            __weak __typeof(self) wself = self;
            [self.screenComponents start:^{
                [MeetingControlCompoments startShareScreen];
                [wself startScreenWithCamera];
            }];
        } else {
            if (![self.currentRoomModel.screen_shared_uid isEqualToString:self.localVideoSession.uid]) {
                [[MeetingToastComponents shareMeetingToastComponents] showWithMessage:@"屏幕共享发起失败，请提示前一位参会者结束共享"];
            }
        }
        __weak __typeof(self) wself = self;
        self.videoSpeakerView.clickCloseBlock = ^{
            [wself.screenComponents stop];
            [[MeetingRTCManager shareRtc] stopScreenSharing];
        };
    } else if (status == RoomBottomStatusPar) {
        UserListViewController *userListViewController = [[UserListViewController alloc] init];
        userListViewController.localVideoSession = self.localVideoSession;
        userListViewController.isLoginHost = [self.localVideoSession.uid isEqualToString:self.currentRoomModel.host_id] ? YES : NO;
        [self.navigationController pushViewController:userListViewController animated:YES];
        self.userListViewController = userListViewController;
    } else if (status == RoomBottomStatusAudio) {
        BOOL micEarpiece = (itemButton.status == ButtonStatusActive);
        if (micEarpiece) {
            itemButton.status = ButtonStatusNone;
            itemButton.desTitle = @"扬声器";
        } else {
            itemButton.status = ButtonStatusActive;
            itemButton.desTitle = @"听筒";
        }
        [[MeetingRTCManager shareRtc] setEnableSpeakerphone:micEarpiece];
    } else if (status == RoomBottomStatusSet) {
        SettingViewController *settingsVC = [[SettingViewController alloc] init];
        [self.navigationController pushViewController:settingsVC animated:YES];
        __weak typeof(self) weakSelf = self;
        settingsVC.switchValueChangeBlock = ^(BOOL on) {
            weakSelf.paramInfoView.hidden = !on;
        };
    } else if (status == RoomBottomStatusRecord) {
        if (itemButton.status == ButtonStatusNone) {
            if ([self.currentRoomModel.host_id isEqualToString:self.localVideoSession.uid]) {
                //ui
                [self updateRecordTipStatusWithHidden:NO];
            
                //Start record Meeting socket api
                [MeetingControlCompoments recordMeeting:[self getRecordUids] screenId:self.currentRoomModel.screen_shared_uid];
            } else {
                [[MeetingToastComponents shareMeetingToastComponents] showWithMessage:@"如需录制会议，请提醒主持人开启录制。"];
            }
        }
    } else {
        
    }
}

#pragma mark - RoomNavViewDelegate

- (void)roomNavView:(RoomNavView *)roomNavView didSelectStatus:(RoomNavStatus)status {
    if (status == RoomNavStatusHangeup) {
        [self showEndView];
    } else if (status == RoomNavStatusSwitchCamera) {
        if (self.localVideoSession.isEnableVideo) {
            [[MeetingRTCManager shareRtc] switchCamera];
        }
    }
}

#pragma mark - 通知

- (void)meetingControlChange:(NSNotification *)notification {
    NSString *type = (NSString *)notification.object;
    if ([type isEqualToString:@"resume"]) {
        [self loadDataWithMeetingContrller];
    } else if ([type isEqualToString:@"exit"]) {
        [self hangUp];
    } else {
        
    }
}

- (void)socketStatusChange:(NSNotification *)notifiction {
    NSString *statsuStr = (NSString *)notifiction.object;
    if ([statsuStr isEqualToString:@"faile"]) {
        [[MeetingToastComponents shareMeetingToastComponents] showWithMessage:@"网络链接已断开，请检查设置。" view:self.toastView keep:YES block:^(BOOL result) {
            
        }];
    } else {
        
    }
}

#pragma mark - Private Action

- (void)loadDataWithMeetingContrller {
    [MeetingControlCompoments getMeetingInfoWithBlock:^(MeetingControlRoomModel * _Nonnull roomModel, MeetingControlAckModel * _Nonnull model) {
        if (model.result) {
            self.currentRoomModel = roomModel;
            BOOL isOpenScreen = (roomModel.screen_shared_uid.length > 0);
            [self updateModeWithStatus:!isOpenScreen ? RoomModeStatusGallery : RoomModeStatusSpaker];
            [self updateRecordTipStatusWithHidden:!roomModel.record];
            [self.bottomView updateButtonStatus:RoomBottomStatusMic close:(self.localVideoSession.audioType == 2)];
            [self.bottomView updateButtonStatus:RoomBottomStatusCamera close:!self.localVideoSession.isEnableVideo];
            [self.bottomView updateButtonStatus:RoomBottomStatusScreen close:isOpenScreen];
            [self updateNavTimeWithModel:roomModel];
        } else {
            AlertActionModel *alertModel = [[AlertActionModel alloc] init];
            alertModel.title = @"确定";
            [[AlertActionManager shareAlertActionManager] showWithMessage:model.message actions:@[alertModel]];
        }
    }];
    
    [MeetingControlCompoments getMeetingUserInfo:@"" block:^(NSArray<MeetingControlUserModel *> * _Nonnull userLists, MeetingControlAckModel * _Nonnull model) {
        for (int i = 0; i < userLists.count; i++) {
            RoomVideoSession *videoSession = [RoomVideoSession roomVideoSessionToMeetingControlUserModel:userLists[i]];
            if ([videoSession.uid isEqualToString:self.localVideoSession.uid]) {
                [self addLocalUser:self.localVideoSession];
            } else {
                [self addUser:videoSession];
            }
        }
    }];
}

- (void)updateNavTimeWithModel:(MeetingControlRoomModel *)roomModel {
    NSInteger time = (roomModel.now - roomModel.created_at) / 1000000000;
    if (time < 0) {
        time = 0;
    }
    self.navView.meetingTime = time;
    self.navView.localVideoSession = self.localVideoSession;
}

- (void)updateCurrentUserListHostStatus {
    for (RoomVideoSession *userModel in self.currentUserLists) {
        //Because there is only one host, the status of everyone needs to be updated
        userModel.isHost = ([userModel.uid isEqualToString:self.currentRoomModel.host_id]) ? YES : NO;
    }
}

- (void)addLocalUser:(RoomVideoSession *)localVideoSession {
    localVideoSession.isVideoStream = YES;
    [self addUser:localVideoSession];
}

- (void)addUser:(RoomVideoSession *)roomUserModel {
    //重复数据删除
    //Deduplication
    NSInteger index = -1;
    for (int i = 0; i < self.currentUserLists.count; i++) {
        RoomVideoSession *userModel = self.currentUserLists[i];
        if ([userModel.uid isEqualToString:roomUserModel.uid]) {
            index = i;
            break;
        }
    }
    if (index >= 0) {
        [self.currentUserLists replaceObjectAtIndex:index withObject:roomUserModel];
    } else {
        if ([roomUserModel.uid isEqualToString:self.localVideoSession.uid]) {
            [self.currentUserLists insertObject:roomUserModel atIndex:0];
        } else {
            [self.currentUserLists addObject:roomUserModel];
        }
    }
    
    //只有前9个用户才需要展示视频流
    //Only the first 6 users need to show the video stream
    if (index <= MaxAvatarNumber) {
        NSString *value = self.currentStreamDic[roomUserModel.uid];
        if ([value integerValue] == 1) {
            roomUserModel.isVideoStream = YES;
            [[MeetingRTCManager shareRtc] subscribeStream:roomUserModel.uid];
        }
    }
    
    if ([self.localVideoSession.uid isEqualToString:self.currentRoomModel.host_id]) {
        [self updateRecordLayout:[self getRecordUids] screenId:self.currentRoomModel.screen_shared_uid];
    }
    [self updateRenderModeView];
}

- (void)removeUser:(NSString *)uid {
    RoomVideoSession *deleteModel = nil;
    for (RoomVideoSession *roomUserModel in self.currentUserLists) {
        if ([roomUserModel.uid isEqualToString:uid]) {
            deleteModel = roomUserModel;
            break;
        }
    }
    if (deleteModel) {
        [self.currentUserLists removeObject:deleteModel];
    }
    
    if ([self.localVideoSession.uid isEqualToString:self.currentRoomModel.host_id]) {
        [self updateRecordLayout:[self getRecordUids] screenId:self.currentRoomModel.screen_shared_uid];
    }
    [self updateRenderModeView];
}

- (void)updateVideoParamInfoLabel {
    
        
    
}

- (void)createUIComponents {
    //header view
    [self.view addSubview:self.navView];
    [self.view addSubview:self.videoMatrixView];
    [self.view addSubview:self.videoSpeakerView];
    [self.view addSubview:self.paramInfoView];
    [self.view addSubview:self.bottomView];
    [self.view addSubview:self.toastView];
    [self.view addSubview:self.recordTipView];
    
    [self.navView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.left.right.equalTo(self.view);
        make.height.mas_equalTo(44 + [DeviceInforTool getStatusBarHight]);
    }];

    [self.videoMatrixView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(self.navView.mas_bottom);
        make.left.right.equalTo(self.view);
        make.bottom.equalTo(self.bottomView.mas_top);
    }];
    
    [self.videoSpeakerView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(self.videoMatrixView);
    }];
    
    [self.bottomView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.right.equalTo(self.view);
        make.bottom.equalTo(self.view).offset(0);
        make.height.mas_equalTo(128/2 + [DeviceInforTool getVirtualHomeHeight]);
    }];

    [self.paramInfoView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.equalTo(self.view);
        make.bottom.equalTo(self.bottomView.mas_top);
        make.width.mas_equalTo(150.f);
        make.height.mas_equalTo(16 * 16 + 10 + 10);
        //16 * n + 10 + 10
    }];
    
    [self.toastView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(self.view);
    }];
    
    [self.recordTipView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(130/2, 60/2));
        make.top.equalTo(self.navView.mas_bottom).offset(12);
        make.right.equalTo(self.view).offset(-12);
    }];
    
    self.paramInfoView.hidden = ![SettingsService getOpenParam];
}

- (void)showEndView {
    [self.endCompoments showWithStatus:[self.currentRoomModel.host_id isEqualToString:self.localVideoSession.uid] ? MeetingEndStatusHost : MeetingEndStatusNone];
    __weak __typeof(self) wself = self;
    self.endCompoments.clickButtonBlock = ^(MeetingButtonStatus status) {
        if (status == MeetingButtonStatusEnd ||
            status == MeetingButtonStatusLeave) {
            [wself hangUp];
        } else if (status == MeetingButtonStatusCancel) {
            //cancel
        }
        wself.endCompoments = nil;
    };
}

- (void)updateRenderModeViewUserRankeWithAudioVolume:(NSDictionary<NSString *, ByteRtcAudioVolumeInfo *> *)volumeInfo {
    NSMutableArray *speakUserLists = [[NSMutableArray alloc] init];
    NSMutableArray *volumeUserLists = [[NSMutableArray alloc] init];
    for (int i = 0; i < self.currentUserLists.count; i++) {
        //ranke
        RoomVideoSession *userModel = self.currentUserLists[i];
        BOOL isMicOpen = NO;
        if ([userModel.uid isEqualToString:self.localVideoSession.uid]) {
            isMicOpen = (self.localVideoSession.audioType == 2) ? NO : YES;
        } else {
            isMicOpen = (userModel.audioType == 2) ? NO : YES;
        }
        //每次重新计算最大音量用户
        //Recalculate the maximum volume user
        userModel.isMaxVolume = NO;
        if ([userModel.uid isEqualToString:self.localVideoSession.uid]) {
            userModel.rankeFactor = 257;
        } else {
            //音量取值范围为 [0, 255]
            //The volume range is [0, 255]
            if (volumeInfo &&
                [volumeInfo isKindOfClass:[NSDictionary class]] &&
                volumeInfo.count > 0 &&
                isMicOpen) {
                ByteRtcAudioVolumeInfo *volumeModel = [volumeInfo objectForKey:userModel.uid];
                if (volumeModel) {
                    userModel.rankeFactor = volumeModel.volume;
                } else {
                    userModel.rankeFactor = 0;
                }
            } else {
                userModel.rankeFactor = 0;
            }
        }
        [speakUserLists addObject:userModel];
        
        //volume
        if (volumeInfo &&
            [volumeInfo isKindOfClass:[NSDictionary class]] &&
            volumeInfo.count > 0 &&
            isMicOpen) {
            ByteRtcAudioVolumeInfo *volumeModel = [volumeInfo objectForKey:userModel.uid];
            if (volumeModel && [volumeModel isKindOfClass:[ByteRtcAudioVolumeInfo class]]) {
                userModel.volume = volumeModel.volume;
            } else {
                userModel.volume = 0;
            }
            [volumeUserLists addObject:userModel];
        }
    }
    NSArray *sorceSpeakUserLists = [speakUserLists sortedArrayUsingComparator:^NSComparisonResult(RoomVideoSession *_Nonnull obj1, RoomVideoSession *_Nonnull obj2) {
        if (obj1.rankeFactor > obj2.rankeFactor) {
            return NSOrderedAscending;
        } else if (obj1.rankeFactor == obj2.rankeFactor) {
            return NSOrderedSame;
        } else {
            return NSOrderedDescending;
        }
    }];
    
    NSArray *sorceVolumeUserLists = [volumeUserLists sortedArrayUsingComparator:^NSComparisonResult(RoomVideoSession *_Nonnull obj1, RoomVideoSession *_Nonnull obj2) {
        if (obj1.volume > obj2.volume) {
            return NSOrderedAscending;
        } else if (obj1.volume == obj2.volume) {
            return NSOrderedSame;
        } else {
            return NSOrderedDescending;
        }
    }];
    if (sorceVolumeUserLists.count > 0) {
        RoomVideoSession *maxVolumeUser = sorceVolumeUserLists.firstObject;
        if (maxVolumeUser.volume > 0) {
            maxVolumeUser.isMaxVolume = YES;
        }
    }
    
    //只需要前6名用户
    //Only the first 6 users are required
    NSInteger maxLen = MIN(sorceSpeakUserLists.count, MaxAvatarNumber);
    sorceSpeakUserLists = [sorceSpeakUserLists subarrayWithRange:NSMakeRange(0, maxLen)];
    
    if (sorceSpeakUserLists.count > 0) {
        NSMutableArray *resultLists = [[NSMutableArray alloc] init];
        [self.currentUserLists removeObjectsInArray:sorceSpeakUserLists];
        
        [resultLists addObjectsFromArray:sorceSpeakUserLists];
        [resultLists addObjectsFromArray:[self.currentUserLists copy]];
        self.currentUserLists = [resultLists mutableCopy];
        
        [self needToSubscribeStreams:self.currentUserLists];
        
        if ([self.localVideoSession.uid isEqualToString:self.currentRoomModel.host_id]) {
            [self updateRecordLayout:[self getRecordUids] screenId:self.currentRoomModel.screen_shared_uid];
        }
        [self updateRenderModeView];
    }
}

- (void)needToSubscribeStreams:(NSArray<RoomVideoSession *> *)userList {
    NSDictionary *subscribeUidDic = [[MeetingRTCManager shareRtc] getSubscribeUidDic];
    //Unsubscribe first
    if (subscribeUidDic.count > 0) {
        for (int i = 0; i < userList.count; i++) {
            RoomVideoSession *userModel = userList[i];
            NSString *value = [subscribeUidDic objectForKey:userModel.uid];
            if ([value integerValue] == 1 && i >= MaxAvatarNumber) {
                [[MeetingRTCManager shareRtc] unsubscribe:userModel.uid];
            }
        }
    }
    
    for (int i = 0; i < userList.count; i++) {
        RoomVideoSession *userModel = userList[i];
        if (![userModel.uid isEqualToString:self.localVideoSession.uid]) {
            //Don't subscribe self
            NSString *isStream = self.currentStreamDic[userModel.uid];
            if (i < MaxAvatarNumber) {
                if ([isStream integerValue] == 1) {
                    //subscribe
                    userModel.isVideoStream = YES;
                    [[MeetingRTCManager shareRtc] subscribeStream:userModel.uid];
                } else {
                    //unsubscribe
                    [[MeetingRTCManager shareRtc] unsubscribe:userModel.uid];
                }
            }
        }
    }
}

- (NSArray<NSString *> *)getRecordUids {
    NSArray *lists = @[];
    if (self.currentRoomModel.screen_shared_uid.length > 0) {
        //There is screen flow
        NSInteger maxLen = MIN(self.currentUserLists.count, 8);
        lists = [self.currentUserLists subarrayWithRange:NSMakeRange(0, maxLen)];
    } else {
        lists = self.currentTopUserLists;
    }
    NSMutableArray *uids = [[NSMutableArray alloc] init];
    for (int i = 0; i < lists.count; i++) {
        RoomVideoSession *userModel = lists[i];
        [uids addObject:userModel.uid];
    }
    return [uids copy];
}

- (NSArray *)getRenderViewTopUserModel {
    NSMutableArray *lists = [[NSMutableArray alloc] init];
    for (int i = 0 ; i < self.currentUserLists.count; i++) {
        RoomVideoSession *mdoel = self.currentUserLists[i];
        if (mdoel.isVideoStream && mdoel.isEnableVideo) {
            [lists addObject:mdoel];
            if (lists.count >= 9) {
                break;
            }
        }
    }
    return [lists copy];
}

- (void)startScreenWithCamera {
    ButtonStatus cameraStatus = [self.bottomView getButtonStatus:RoomBottomStatusCamera];
    if (cameraStatus == ButtonStatusNone) {
        //Turn on screen sharing, turn off the camera
        self.localVideoSession.isEnableVideo = NO;
        [[MeetingRTCManager shareRtc] enableLocalVideo:NO];
        [MeetingControlCompoments turnOffCamera];
        [self.bottomView updateButtonStatus:RoomBottomStatusCamera close:YES];
        self.screenComponents.isTurnOffCamera = YES;
    }
}

- (void)clickRoomBottomStatusMic:(RoomItemButton *)itemButton {
    [SystemAuthority authorizationStatusWithType:AuthorizationTypeAudio block:^(BOOL isAuthorize) {
        if (isAuthorize) {
            itemButton.status = (itemButton.status == ButtonStatusActive) ? ButtonStatusNone : ButtonStatusActive;
            BOOL isEnableAudio = (self.localVideoSession.audioType == 2) ? NO : YES;
            [[MeetingRTCManager shareRtc] enableLocalAudio:!isEnableAudio];
            [SystemAuthority autoJumpWithAuthorizationStatusWithType:AuthorizationTypeAudio];
            if (itemButton.status == ButtonStatusActive) {
                //off
                [MeetingControlCompoments turnOffMic];
                self.localVideoSession.audioType = 2;
            } else if (itemButton.status == ButtonStatusNone) {
                [MeetingControlCompoments turnOnMic];
                self.localVideoSession.audioType = 1;
            }
        } else {
            [[MeetingToastComponents shareMeetingToastComponents] showWithMessage:@"麦克风权限已关闭，请至设备设置页开启"];
        }
    }];
}

- (void)clickRoomBottomStatusCamera:(RoomItemButton *)itemButton {
    [SystemAuthority authorizationStatusWithType:AuthorizationTypeCamera block:^(BOOL isAuthorize) {
        if (isAuthorize) {
            if (self.screenComponents.isSharing) {
                //Screen Sharing
                [[MeetingToastComponents shareMeetingToastComponents] showWithMessage:@"结束共享后方可打开摄像头"];
            } else {
                itemButton.status = (itemButton.status == ButtonStatusActive) ? ButtonStatusNone : ButtonStatusActive;
                self.localVideoSession.isEnableVideo = !self.localVideoSession.isEnableVideo;
                [[MeetingRTCManager shareRtc] enableLocalVideo:self.localVideoSession.isEnableVideo];
                [SystemAuthority autoJumpWithAuthorizationStatusWithType:AuthorizationTypeCamera];
                if (itemButton.status == ButtonStatusActive) {
                    //off
                    [MeetingControlCompoments turnOffCamera];
                } else if (itemButton.status == ButtonStatusNone) {
                    [MeetingControlCompoments turnOnCamera];
                }
            }
        } else {
            [[MeetingToastComponents shareMeetingToastComponents] showWithMessage:@"摄像机权限已关闭，请至设备设置页开启"];
        }
    }];
}

- (void)updateRecordLayout:(NSArray *)uids screenId:(NSString *)screenId {
    NSString *temoRecordID = @"";
    for (int i = 0; i < uids.count; i++) {
        temoRecordID = [NSString stringWithFormat:@"%@%@", temoRecordID, uids[i]];
    }
    temoRecordID = [NSString stringWithFormat:@"%@%@", temoRecordID, screenId];
    if (![temoRecordID isEqualToString:self.recordID] && self.currentRoomModel.record) {
        self.recordID = temoRecordID;
        [MeetingControlCompoments updateRecordLayout:uids screenId:screenId];
    }
}

#pragma mark - getter

- (RoomBottomView *)bottomView {
    if (!_bottomView) {
        _bottomView = [[RoomBottomView alloc] init];
        _bottomView.delegate = self;
    }
    return _bottomView;
}

- (RoomNavView *)navView {
    if (!_navView) {
        _navView = [[RoomNavView alloc] init];
        _navView.delegate = self;
    }
    return _navView;
}

- (RoomParamInfoView *)paramInfoView {
    if (!_paramInfoView) {
        _paramInfoView = [[RoomParamInfoView alloc] init];
        _paramInfoView.backgroundColor = [UIColor clearColor];
        _paramInfoView.hidden = YES;
    }
    return _paramInfoView;
}

- (UIImageView *)recordTipView {
    if (!_recordTipView) {
        _recordTipView = [[UIImageView alloc] init];
        _recordTipView.image = [UIImage imageNamed:@"meeting_room_recore"];
        _recordTipView.hidden = YES;
    }
    return _recordTipView;
}

- (RoomMatrixView *)videoMatrixView {
    if (!_videoMatrixView) {
        _videoMatrixView = [[RoomMatrixView alloc] init];
        _videoMatrixView.backgroundColor = [UIColor colorFromHexString:@"#1D2129"];
        
        _videoMatrixView.userInteractionEnabled = YES;
        UITapGestureRecognizer *tap = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(videoMatrixViewTouchAction)];
        [_videoMatrixView addGestureRecognizer:tap];
    }
    return _videoMatrixView;
}

- (void)videoSpeakerViewTouchAction {
    [self.bottomView dismissMoreView];
    if (self.isLandscape) {
        [self setDeviceInterfaceOrientation:UIDeviceOrientationPortrait];
    }
}

- (void)videoMatrixViewTouchAction {
    [self.bottomView dismissMoreView];
}

- (RoomSpeakerView *)videoSpeakerView {
    if (!_videoSpeakerView) {
        _videoSpeakerView = [[RoomSpeakerView alloc] init];
        _videoSpeakerView.hidden = YES;
        
        _videoSpeakerView.userInteractionEnabled = YES;
        UITapGestureRecognizer *tap = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(videoSpeakerViewTouchAction)];
        [_videoSpeakerView addGestureRecognizer:tap];
    }
    return _videoSpeakerView;
}

- (MeetingEndCompoments *)endCompoments {
    if (!_endCompoments) {
        _endCompoments = [[MeetingEndCompoments alloc] init];
    }
    return _endCompoments;
}

- (NSMutableArray<RoomVideoSession *> *)currentUserLists {
    if (!_currentUserLists) {
        _currentUserLists = [[NSMutableArray alloc] init];
    }
    return _currentUserLists;
}

- (NSArray<RoomVideoSession *> *)currentTopUserLists {
    NSInteger maxLen = MIN(self.currentUserLists.count, MaxAvatarNumber);
    _currentTopUserLists = [self.currentUserLists subarrayWithRange:NSMakeRange(0, maxLen)];
    return _currentTopUserLists;
}

- (NSMutableDictionary<NSString *,NSString *> *)currentStreamDic {
    if (!_currentStreamDic) {
        _currentStreamDic = [[NSMutableDictionary alloc] init];
    }
    return _currentStreamDic;
}

- (MeetingScreenComponents *)screenComponents {
    if (!_screenComponents) {
        _screenComponents = [[MeetingScreenComponents alloc] init];
    }
    return _screenComponents;
}

- (dispatch_semaphore_t)lock {
    if (_lock == nil) {
        _lock = dispatch_semaphore_create(1);
    }
    return _lock;
}

- (UIView *)toastView {
    if (!_toastView) {
        _toastView = [[UIView alloc] init];
        _toastView.backgroundColor = [UIColor clearColor];
        _toastView.userInteractionEnabled = NO;
    }
    return _toastView;
}

- (void)dealloc {
    [UIApplication sharedApplication].idleTimerDisabled = NO;
    NSLog(@"dealloc %@",NSStringFromClass([self class]));
}

@end
