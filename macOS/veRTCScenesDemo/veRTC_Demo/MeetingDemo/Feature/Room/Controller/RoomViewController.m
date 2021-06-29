//
//  RoomViewController.m
//  SceneRTCDemo
//
//  Created by on 2021/3/10.
//

#import "RoomViewController.h"
#import "RoomViewController+Listener.h"
#import "ScreenShareViewController.h"
#import "SetingViewController.h"

#import "MeetingEndCompoments.h"
#import "SpeakerModeView.h"
#import "GalleryModeView.h"
#import "ParamView.h"
#import "SystemAuthority.h"

@interface RoomViewController () <RoomBottomBarViewDelegate, SetingViewControllerDelegate, MeetingRTCManagerDelegate>

@property (nonatomic, strong) ScreenShareViewController *screenShareViewController;
@property (nonatomic, strong) SetingViewController *setingViewController;

@property (nonatomic, strong) GalleryModeView *galleryModeView;
@property (nonatomic, strong) SpeakerModeView *speakerModeView;
@property (nonatomic, strong) ParamView *paramView;
@property (nonatomic, strong) MeetingEndCompoments *endCompoments;

@property (nonatomic, strong) NSMutableArray <RoomUserModel *> *currentUserLists;
@property (nonatomic, copy) NSArray <RoomUserModel *> *currentTopUserLists;
@property (nonatomic, strong) NSMutableDictionary <NSString *, NSString *> *currentStreamDic;

@property (nonatomic, strong) NSView *videoViewTest;
@property (nonatomic, strong) NSString *recordID;

@property (nonatomic, strong) dispatch_semaphore_t lock;

@end

@implementation RoomViewController

- (instancetype)initWithLoginModel:(LoginModel *)loginModel {
    self = [super init];
    if (self) {
        self.loginModel = loginModel;
    }
    return self;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    [self.view setBackgroundColorWithHexString:@"#1D2129"];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(clickRoomExpandNotice:) name:NoticeClickRoomExpandListName object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(showEndWindowName:) name:NoticeShowEndWindowName object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(closeEndWindowName:) name:NoticeCloseEndWindowName object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(screenBottomStartRecordName) name:NoticeScreenBottomStartRecordName object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(meetingControlChange:) name:NotificationMeetingControlChange object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(screenUpdateRoomMicName:) name:NoticeScreenUpdateRoomMicName object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(screenUpdateRoomCameraName:) name:NoticeScreenUpdateRoomCameraName object:nil];
    
    [self addSubviewAndConstraints];
    
    self.paramView.hidden = ![SetingViewController getParamSwitch];
    if (!self.loginModel.isEnableAudio) {
        [self.roomBottomBarView clickButtonStatus:BottomBarStatusMic];
    }
    if (!self.loginModel.isEnableVideo) {
        [self.roomBottomBarView clickButtonStatus:BottomBarStatusVideo];
    }
    
    //Rtc join room
    [MeetingRTCManager shareMeetingRTCManager].delegate = self;
    [[MeetingRTCManager shareMeetingRTCManager] joinChannelWithUser:self.loginModel];
    [[MeetingRTCManager shareMeetingRTCManager] enableAudioVolumeIndication:2000 smooth:8];
    
    //Socket api
    [self loadDataWithMeetingContrller];
    
    //Add socket listener
    [self addSocketListener];
}

#pragma mark - Notice Method

- (void)screenUpdateRoomMicName:(NSNotification *)notice {
    NSNumber *mute = notice.object;
    self.loginModel.isEnableAudio = !mute.boolValue;
    [self.roomBottomBarView updateButtonStatus:BottomBarStatusMic close:mute.boolValue];
}

- (void)screenUpdateRoomCameraName:(NSNotification *)notice {
    NSNumber *mute = notice.object;
    self.loginModel.isEnableVideo = !mute.boolValue;
    [self.roomBottomBarView updateButtonStatus:BottomBarStatusVideo close:mute.boolValue];
}

- (void)clickRoomExpandNotice:(NSNotification *)notice {
    NSNumber *isExpand = (NSNumber *)notice.object;
    [self.speakerModeView updateAvatarHidden:![isExpand boolValue]];
}

- (void)showEndWindowName:(NSNotification *)notice {
    AppDelegate *appDelegate = (AppDelegate *)[NSApplication sharedApplication].delegate;
    [appDelegate.windowManager showEndWindowController:self.loginModel roomModel:self.currentRoomModel];
}

- (void)closeEndWindowName:(NSNotification *)notice {
    AppDelegate *appDelegate = (AppDelegate *)[NSApplication sharedApplication].delegate;
    NSString *key = (NSString *)notice.object;
    if ([key isEqualToString:@"end"]) {
        [appDelegate.windowManager showMeetingWindowController];
        [self hangUpAction];
        //socket api end Meeting
        [MeetingControlCompoments endMeeting];
        //sdk api end Meeting
        [[MeetingRTCManager shareMeetingRTCManager] stopScreenCapture];
    } else if ([key isEqualToString:@"leave"]) {
        [appDelegate.windowManager showMeetingWindowController];
        [self hangUpAction];
        //socket api leave Meeting
        [MeetingControlCompoments leaveMeeting];
        //sdk api end Meeting
        [[MeetingRTCManager shareMeetingRTCManager] stopScreenCapture];
    }
    [appDelegate.windowManager closeEndWindowController];
}

- (void)screenBottomStartRecordName {
    //Start record Meeting socket api
    [MeetingControlCompoments recordMeeting:[self getRecordUids] screenId:self.currentRoomModel.screen_shared_uid];
}

- (void)meetingControlChange:(NSNotification *)notification {
    NSString *type = (NSString *)notification.object;
    if ([type isEqualToString:@"resume"]) {
        [self loadDataWithMeetingContrller];
    } else if ([type isEqualToString:@"exit"]) {
        [self hangUpAction];
    } else {
        
    }
}

#pragma mark - SetingViewControllerDelegate

- (void)setingViewController:(SetingViewController *)setingViewController cancelAction:(BOOL)isCancel {
    [self dismissSetingVC];
    self.paramView.hidden = ![SetingViewController getParamSwitch];
}

#pragma mark - RoomBottomBarViewDelegate

- (void)roomBottomBarView:(RoomBottomBarView *)roomBottomBarView didSelectItemsAtButton:(RoomBottomBarModel *)roomBottomBarModel button:(nonnull TrackButton *)button {
    switch (roomBottomBarModel.status) {
        case BottomBarStatusMic:
            button.isClose = !button.isClose;
            button.tipTitle = button.isClose ? @"麦克风" : @"麦克风";
            
            //sdk api
            [[MeetingRTCManager shareMeetingRTCManager] enableLocalAudio:!button.isClose];
            
            //socket api
            if (button.isClose) {
                [MeetingControlCompoments turnOffMic];
            } else {
                [MeetingControlCompoments turnOnMic];
            }
            self.loginModel.isEnableAudio = !button.isClose;
            break;
        case BottomBarStatusVideo:
            button.isClose = !button.isClose;
            button.tipTitle = button.isClose ? @"摄像头" : @"摄像头";
            
            //sdk api
            [[MeetingRTCManager shareMeetingRTCManager] enableLocalVideo:!button.isClose];
            
            //socket api
            if (button.isClose) {
                [MeetingControlCompoments turnOffCamera];
            } else {
                [MeetingControlCompoments turnOnCamera];
            }
            self.loginModel.isEnableVideo = !button.isClose;
            break;
        case BottomBarStatusScreenShare:
            if (button.isClose) {
                if ([self.currentRoomModel.screen_shared_uid isEqualToString:self.loginModel.uid]) {
                    //End ShareScreen socket api
                    [MeetingControlCompoments endShareScreen];
                } else {
                    //error
                    if (NOEmptyStr(self.currentRoomModel.screen_shared_uid)) {
                        [[MeetingToastComponents shareMeetingToastComponents] showWithMessage:@"屏幕共享发起失败，请提示前一位参会者结束共享"];
                    }
                }
            } else {
                [self showScreenShareVCWithButton:button];
            }
            break;
        case BottomBarStatusRecord:
            if (!button.isClose) {
                if ([self.currentRoomModel.host_id isEqualToString:self.loginModel.uid]) {
                    button.isClose = YES;
                    [[NSNotificationCenter defaultCenter] postNotificationName:NoticeUpdateRoomRecordName object:@(button.isClose)];
                
                    //Start record Meeting socket api
                    [MeetingControlCompoments recordMeeting:[self getRecordUids] screenId:self.currentRoomModel.screen_shared_uid];
                } else {
                    [[MeetingToastComponents shareMeetingToastComponents] showWithMessage:@"如需录制会议，请提醒主持人开启录制。"];
                }
            }
            break;
        case BottomBarStatusPeople:
            if (!button.isClose) {
                [self showParticipantVC];
            } else {
                [self dismissParticipantVC];
            }
            button.isClose = !button.isClose;
            break;
        case BottomBarStatusSeting:
            [self showSetingVC];
            break;
        case BottomBarStatusHangUp:
            [self showEndView];
            break;
            
        default:
            break;
    }
}

#pragma mark - MeetingRTCManagerDelegate

- (void)rtcManager:(MeetingRTCManager *)rtcManager didScreenStreamAdded:(NSString *)screenStreamsUid {
    self.speakerModeView.screenStreamsUid = screenStreamsUid;
}

- (void)rtcManager:(MeetingRTCManager * _Nonnull)rtcManager didStreamAdded:(NSArray<NSString *> *_Nullable)streamsUid {
    if ([self getRenderViewTopUserModel].count < 9) {
        //需要立即刷新
        //Need to refresh immediately
        for (NSString *uid in streamsUid) {
            for (RoomUserModel *userModel in self.currentTopUserLists) {
                if ([userModel.name isEqualToString:uid]) {
                    userModel.isVideoStream = YES;
                    [[MeetingRTCManager shareMeetingRTCManager] subscribeStream:userModel.name];
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
    for (RoomUserModel *model in self.currentTopUserLists) {
        for (NSString *removeUid in streamsUid) {
            if ([model.name isEqualToString:removeUid]) {
                model.isVideoStream = NO;
            }
        }
    }
    [self.currentStreamDic removeObjectsForKeys:streamsUid];
    [self updateRenderModeView];
}

- (void)rtcManager:(MeetingRTCManager *_Nonnull)rtcManager didScreenStreamRemoved:(NSString *)screenStreamsUid {
    if ([self.speakerModeView.screenStreamsUid isEqualToString:screenStreamsUid]) {
        self.speakerModeView.screenStreamsUid = nil;
    }
}

- (void)rtcManager:(MeetingRTCManager *)rtcManager reportRtcParamModel:(ParamModel *)paramModel {
    self.paramView.paramModel = paramModel;
}

- (void)rtcManager:(MeetingRTCManager *)rtcManager reportAudioVolume:(NSDictionary<NSString *, ByteRtcAudioVolumeInfo *> *)volumeInfo {
    [self updateRenderModeViewUserRankeWithAudioVolume:volumeInfo];
}

- (void)rtcManager:(MeetingRTCManager *)rtcManager reportAllAudioVolume:(NSDictionary<NSString *, NSNumber *> *)volumeInfo {
    [self.participantViewController updateUserMicStatus:volumeInfo];
}

- (void)updateCurrentUserListHostStatus {
    for (RoomUserModel *userModel in self.currentUserLists) {
        //Because there is only one host, the status of everyone needs to be updated
        userModel.isHost = ([userModel.name isEqualToString:self.currentRoomModel.host_id]) ? YES : NO;
    }
}

- (void)updateRenderModeViewUserRankeWithAudioVolume:(NSDictionary<NSString *, ByteRtcAudioVolumeInfo *> *)volumeInfo {
    NSMutableArray *speakUserLists = [[NSMutableArray alloc] init];
    NSMutableArray *volumeUserLists = [[NSMutableArray alloc] init];
    for (int i = 0; i < self.currentUserLists.count; i++) {
        //ranke
        RoomUserModel *userModel = self.currentUserLists[i];
        BOOL isMicOpen = NO;
        if ([userModel.name isEqualToString:self.loginModel.uid]) {
            isMicOpen = self.loginModel.isEnableAudio;
        } else {
            isMicOpen = (userModel.audioType == 2) ? NO : YES;
        }
        //每次重新计算最大音量用户
        //Recalculate the maximum volume user each time
        userModel.isMaxVolume = NO;
        if (userModel.isHost) {
            userModel.rankeFactor = 257;
        } else if ([userModel.name isEqualToString:self.loginModel.uid]) {
            userModel.rankeFactor = 256;
        } else {
            //音量取值范围为 [0, 255]
            //The volume range is [0, 255]
            if (volumeInfo &&
                [volumeInfo isKindOfClass:[NSDictionary class]] &&
                volumeInfo.count > 0 &&
                isMicOpen) {
                ByteRtcAudioVolumeInfo *volumeModel = [volumeInfo objectForKey:userModel.name];
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
            ByteRtcAudioVolumeInfo *volumeModel = [volumeInfo objectForKey:userModel.name];
            if (volumeModel && [volumeModel isKindOfClass:[ByteRtcAudioVolumeInfo class]]) {
                userModel.volume = volumeModel.volume;
            } else {
                userModel.volume = 0;
            }
            [volumeUserLists addObject:userModel];
        }
    }
    NSArray *sorceSpeakUserLists = [speakUserLists sortedArrayUsingComparator:^NSComparisonResult(RoomUserModel *_Nonnull obj1, RoomUserModel *_Nonnull obj2) {
        if (obj1.rankeFactor > obj2.rankeFactor) {
            return NSOrderedAscending;
        } else if (obj1.rankeFactor == obj2.rankeFactor) {
            return NSOrderedSame;
        } else {
            return NSOrderedDescending;
        }
    }];
    
    NSArray *sorceVolumeUserLists = [volumeUserLists sortedArrayUsingComparator:^NSComparisonResult(RoomUserModel *_Nonnull obj1, RoomUserModel *_Nonnull obj2) {
        if (obj1.volume > obj2.volume) {
            return NSOrderedAscending;
        } else if (obj1.volume == obj2.volume) {
            return NSOrderedSame;
        } else {
            return NSOrderedDescending;
        }
    }];
    if (sorceVolumeUserLists.count > 0) {
        RoomUserModel *maxVolumeUser = sorceVolumeUserLists.firstObject;
        if (maxVolumeUser.volume > 0) {
            maxVolumeUser.isMaxVolume = YES;
        }
    }
    
    //只需要前9名用户
    //Only the first 9 users are required
    NSInteger maxLen = MIN(sorceSpeakUserLists.count, MaxAvatarNumber);
    sorceSpeakUserLists = [sorceSpeakUserLists subarrayWithRange:NSMakeRange(0, maxLen)];
    
    if (sorceSpeakUserLists.count > 0) {
        dispatch_semaphore_wait(self.lock, DISPATCH_TIME_FOREVER);
        dispatch_async(dispatch_get_main_queue(), ^{
            NSMutableArray *resultLists = [[NSMutableArray alloc] init];
            [self.currentUserLists removeObjectsInArray:sorceSpeakUserLists];
            
            [resultLists addObjectsFromArray:sorceSpeakUserLists];
            [resultLists addObjectsFromArray:[self.currentUserLists copy]];
            self.currentUserLists = [resultLists mutableCopy];
            
            if ([self.loginModel.uid isEqualToString:self.currentRoomModel.host_id]) {
                [self updateRecordLayout:[self getRecordUids] screenId:self.currentRoomModel.screen_shared_uid];
            }
            [self updateRenderModeView];
        });
        dispatch_semaphore_signal(self.lock);
    }
}

- (void)needToSubscribeStreams:(NSArray<RoomUserModel *> *)userList {
    NSDictionary *subscribeUidDic = [[MeetingRTCManager shareMeetingRTCManager] getSubscribeUidDic];
    //Unsubscribe first
    if (subscribeUidDic.count > 0) {
        for (int i = 0; i < userList.count; i++) {
            RoomUserModel *userModel = userList[i];
            NSString *value = [subscribeUidDic objectForKey:userModel.name];
            if ([value integerValue] == 1 && i >= MaxAvatarNumber) {
                [[MeetingRTCManager shareMeetingRTCManager] unsubscribe:userModel.name];
            }
        }
    }

    for (int i = 0; i < userList.count; i++) {
        RoomUserModel *userModel = userList[i];
        if (![userModel.name isEqualToString:self.loginModel.uid]) {
            //Don't subscribe self
            NSString *isStream = self.currentStreamDic[userModel.name];
            if (i < MaxAvatarNumber) {
                if ([isStream integerValue] == 1) {
                    //subscribe
                    userModel.isVideoStream = YES;
                    [[MeetingRTCManager shareMeetingRTCManager] subscribeStream:userModel.name];
                } else {
                    //unsubscribe
                    [[MeetingRTCManager shareMeetingRTCManager] unsubscribe:userModel.name];
                }
            }
        }
    }
}

#pragma mark - ParticipantVC

- (void)showParticipantVC {
    if (self.participantViewController) {
        [self dismissParticipantVC];
    }
    AppDelegate *appDelegate = (AppDelegate *)[NSApplication sharedApplication].delegate;
    NSView *windowView = appDelegate.windowManager.currentWindowController.window.contentView;
    
    ParticipantViewController *participantViewController = [[ParticipantViewController alloc] init];
    [windowView addSubview:participantViewController];
    CGFloat parWidth = 280;
    [participantViewController mas_makeConstraints:^(MASConstraintMaker *make) {
        make.right.top.bottom.equalTo(windowView);
        make.width.mas_equalTo(parWidth);
    }];
    __weak __typeof(self) wself = self;
    participantViewController.clickCancelBlock = ^(BOOL isEnable) {
        [wself.roomBottomBarView updateButtonStatus:BottomBarStatusPeople close:NO];
        [wself dismissParticipantVC];
    };
    participantViewController.isLoginHost = [self.loginModel.uid isEqualToString:self.currentRoomModel.host_id] ? YES : NO;
    participantViewController.loginModel = self.loginModel;
    self.participantViewController = participantViewController;
    [[NSNotificationCenter defaultCenter] postNotificationName:NoticeUpdateParticipantVCName object:@(parWidth)];
}

- (void)dismissParticipantVC {
    if (self.participantViewController) {
        [self.participantViewController removeAllSubView];
        [self.participantViewController removeFromSuperview];
        self.participantViewController = nil;
        [[NSNotificationCenter defaultCenter] postNotificationName:NoticeUpdateParticipantVCName object:@(0)];
    }
}

#pragma mark - ScreenShareVC

- (void)showScreenShareVCWithButton:(nonnull TrackButton *)button {
    button.isClose = YES;
    [self addChildViewController:self.screenShareViewController];
    [self.view addSubview:self.screenShareViewController.view];
    [self.screenShareViewController.view mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(self.view);
    }];
    self.screenShareViewController.loginModel = self.loginModel;
    self.screenShareViewController.roomModel = self.currentRoomModel;
    __weak __typeof(self) wself = self;
    __block TrackButton *blockButton = button;
    self.screenShareViewController.clickCancelBlock = ^{
        [wself dismissscreenShareVC];
        blockButton.isClose = NO;
    };
}

- (void)dismissscreenShareVC {
    [self.screenShareViewController.view removeFromSuperview];
    [self.screenShareViewController removeFromParentViewController];
    self.screenShareViewController = nil;
}

#pragma mark - SetingVC

- (void)showSetingVC {
    [self addChildViewController:self.setingViewController];
    [self.view addSubview:self.setingViewController.view];
    [self.setingViewController.view mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(self.view);
    }];
}

- (void)dismissSetingVC {
    [self.setingViewController.view removeFromSuperview];
    [self.setingViewController removeFromParentViewController];
    self.setingViewController = nil;
}

#pragma mark - Publish Action

- (void)updateModeWithStatus:(RoomModeStatus)roomModeStatus {
    if (roomModeStatus == RoomModeStatusGallery) {
        self.speakerModeView.hidden = YES;
        self.galleryModeView.hidden = NO;
        self.roomBottomBarView.isDragged = NO;
    } else {
        self.galleryModeView.hidden = YES;
        self.speakerModeView.hidden = NO;
        self.roomBottomBarView.isDragged = YES;
    }
    [[NSNotificationCenter defaultCenter] postNotificationName:NoticeUpdateRoomExpandListName object:@(!self.speakerModeView.hidden)];
}

- (void)updateRenderModeView {
    dispatch_semaphore_wait(self.lock, DISPATCH_TIME_FOREVER);
    if ([NSThread isMainThread]) {
        [self updateModeView];
    } else {
        dispatch_async(dispatch_get_main_queue(), ^{
            [self updateModeView];
        });
    }
    dispatch_semaphore_signal(self.lock);
}

- (void)updateModeView {
    [self updateCurrentUserListHostStatus];
    if (!self.galleryModeView.hidden) {
        self.galleryModeView.dataLists = self.currentUserLists;
    } else if (!self.speakerModeView.hidden) {
        self.speakerModeView.dataLists = self.currentUserLists;
    } else {
        //error
    }
    [self needToSubscribeStreams:self.currentUserLists];
}

- (void)updateRenderModeViewWithCameraStatus:(NSString *)uid enableCamera:(BOOL)isEnable {
    for (RoomUserModel *userModel in self.currentTopUserLists) {
        if ([userModel.name isEqualToString:uid]) {
            userModel.isOpenVideo = isEnable;
            break;
        }
    }
    [self updateRenderModeView];
}

- (void)updateRenderModeViewWithMicStatus:(NSString *)uid enableMic:(BOOL)isEnable {
    for (RoomUserModel *userModel in self.currentUserLists) {
        if ([userModel.name isEqualToString:uid]) {
            userModel.audioType = isEnable ? 1 : 2;;
            break;
        }
    }
}

- (void)updateRenderModeViewWithScreenStatus:(NSString *)uid enableScreen:(BOOL)isShare {
    for (RoomUserModel *userModel in self.currentTopUserLists) {
        if (isShare) {
            if ([userModel.name isEqualToString:uid]) {
                userModel.isOpenScreen = YES;
            } else {
                userModel.isOpenScreen = NO;
            }
        } else {
            userModel.isOpenScreen = NO;
        }
    }
    [self updateRenderModeView];
}

- (void)addUser:(RoomUserModel *)roomUserModel {
    //重复数据删除
    //Deduplication
    NSInteger index = -1;
    for (int i = 0; i < self.currentUserLists.count; i++) {
        RoomUserModel *userModel = self.currentUserLists[i];
        if ([userModel.name isEqualToString:roomUserModel.name]) {
            index = i;
            break;
        }
    }
    if (index >= 0) {
        [self.currentUserLists replaceObjectAtIndex:index withObject:roomUserModel];
    } else {
        [self.currentUserLists addObject:roomUserModel];
    }
    
    //只有前9个用户才需要展示视频流
    //Only the first 9 users need to show the video stream
    if (index <= MaxAvatarNumber) {
        NSString *value = self.currentStreamDic[roomUserModel.name];
        if ([value integerValue] == 1) {
            roomUserModel.isVideoStream = YES;
            [[MeetingRTCManager shareMeetingRTCManager] subscribeStream:roomUserModel.name];
        }
    }
    
    if ([self.loginModel.uid isEqualToString:self.currentRoomModel.host_id]) {
        [self updateRecordLayout:[self getRecordUids] screenId:self.currentRoomModel.screen_shared_uid];
    }
    [self updateRenderModeView];
}

- (void)removeUser:(NSString *)uid {
    RoomUserModel *deleteModel = nil;
    for (RoomUserModel *roomUserModel in self.currentUserLists) {
        if ([roomUserModel.name isEqualToString:uid]) {
            deleteModel = roomUserModel;
            break;
        }
    }
    if (deleteModel) {
        [self.currentUserLists removeObject:deleteModel];
    }
    
    if ([self.loginModel.uid isEqualToString:self.currentRoomModel.host_id]) {
        [self updateRecordLayout:[self getRecordUids] screenId:self.currentRoomModel.screen_shared_uid];
    }
    [self updateRenderModeView];
}

- (void)hangUpAction {
    //sdk api
    [[MeetingRTCManager shareMeetingRTCManager] leaveChannel:^(BOOL result) {
            
    }];
    
    //ui
    [self dismissParticipantVC];
    [self.endCompoments dismissEndView];
    
    if (self.clickHangUpBlock) {
        self.clickHangUpBlock(self.loginModel);
    }
}

- (void)showEndView {
    [self.endCompoments showWithStatus:[self.currentRoomModel.host_id isEqualToString:self.loginModel.uid] ? MeetingEndStatusHost : MeetingEndStatusNone];
    __weak __typeof(self) wself = self;
    self.endCompoments.clickButtonBlock = ^(MeetingButtonStatus status) {
        if (status == MeetingButtonStatusEnd) {
            [wself hangUpAction];
            
            //socket api end Meeting
            [MeetingControlCompoments endMeeting];
        } else if (status == MeetingButtonStatusLeave) {
            [wself hangUpAction];
            
            //socket api leave Meeting
            [MeetingControlCompoments leaveMeeting];
        } else if (status == MeetingButtonStatusCancel) {
            
        }
        wself.endCompoments = nil;
    };
}

#pragma mark - Private Action

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

- (void)addLocalUser:(LoginModel *)loginModel {
    RoomUserModel *model = [[RoomUserModel alloc] initWithUid:loginModel.uid];
    model.isOneself = ([loginModel.uid isEqualToString:self.loginModel.uid]) ? YES : NO;
    model.isHost = ([loginModel.uid isEqualToString:self.currentRoomModel.host_id]) ? YES : NO;
    model.roomId = self.currentRoomModel.room_id;
    model.audioType = loginModel.isEnableAudio ? 1 : 2;
    model.isOpenVideo = loginModel.isEnableVideo;
    model.isVideoStream = YES;
    
    [self addUser:model];
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
        RoomUserModel *userModel = lists[i];
        [uids addObject:userModel.name];
    }
    return [uids copy];
}

- (void)addSubviewAndConstraints {
    [self.view addSubview:self.speakerModeView];
    [self.speakerModeView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(self.view);
    }];
    
    [self.view addSubview:self.galleryModeView];
    [self.galleryModeView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(self.view);
    }];
    
    [self.view addSubview:self.roomBottomBarView];
    [self.roomBottomBarView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(400, 48));
        make.bottom.mas_equalTo(-8);
        make.centerX.equalTo(self.view);
    }];
    
    [self.view addSubview:self.paramView];
    [self.paramView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(180, 18 * 16 + 60));
        make.left.bottom.equalTo(self.view);
    }];
}

- (NSArray *)getRenderViewTopUserModel {
    NSMutableArray *lists = [[NSMutableArray alloc] init];
    for (int i = 0 ; i < self.currentUserLists.count; i++) {
        RoomUserModel *mdoel = self.currentUserLists[i];
        if (mdoel.isVideoStream && mdoel.isOpenVideo) {
            [lists addObject:mdoel];
            if (lists.count >= 9) {
                break;
            }
        }
    }
    return [lists copy];
}

- (void)loadDataWithMeetingContrller {
    [MeetingControlCompoments getMeetingInfoWithBlock:^(MeetingControlRoomModel * _Nonnull roomModel, MeetingControlAckModel * _Nonnull model) {
        self.currentRoomModel = roomModel;
        BOOL isOpenScreen = (roomModel.screen_shared_uid.length > 0);
        [self updateModeWithStatus:!isOpenScreen ? RoomModeStatusGallery : RoomModeStatusSpaker];
        [self.roomBottomBarView updateButtonStatus:BottomBarStatusRecord close:roomModel.record];
        [self.roomBottomBarView updateButtonStatus:BottomBarStatusScreenShare close:isOpenScreen];
        [[NSNotificationCenter defaultCenter] postNotificationName:NoticeUpdateRoomRecordName object:@(roomModel.record)];
        [[NSNotificationCenter defaultCenter] postNotificationName:NoticeUpdateRoomExpandListName object:@(!self.speakerModeView.hidden)];
        [self updateNavTimeWithModel:roomModel];
        [self getMeetingUserInfo];
    }];
}

- (void)getMeetingUserInfo {
    [MeetingControlCompoments getMeetingUserInfo:@"" block:^(NSArray<MeetingControlUserModel *> * _Nonnull userLists, MeetingControlAckModel * _Nonnull model) {
        for (int i = 0; i < userLists.count; i++) {
            MeetingControlUserModel *meetingControlUserModel = userLists[i];
            RoomUserModel *userModel = [RoomUserModel roomUserModelToMeetingControlUserModel:meetingControlUserModel];
            if ([userModel.name isEqualToString:self.loginModel.uid]) {
                [self addLocalUser:self.loginModel];
            } else {
                [self addUser:userModel];
            }
        }
    }];
}

- (void)updateNavTimeWithModel:(MeetingControlRoomModel *)roomModel {
    NSInteger time = (roomModel.now - roomModel.created_at) / 1000000000;
    if (time < 0) {
        time = 0;
    }
    if (self.updateNavBlock) {
        self.updateNavBlock(time);
    }
}

#pragma mark - getter

- (SpeakerModeView *)speakerModeView {
    if (!_speakerModeView) {
        _speakerModeView = [[SpeakerModeView alloc] init];
        _speakerModeView.hidden = YES;
    }
    return _speakerModeView;
}

- (GalleryModeView *)galleryModeView {
    if (!_galleryModeView) {
        _galleryModeView = [[GalleryModeView alloc] init];
        _galleryModeView.hidden = YES;
    }
    return _galleryModeView;
}

- (RoomBottomBarView *)roomBottomBarView {
    if (!_roomBottomBarView) {
        _roomBottomBarView = [[RoomBottomBarView alloc] initWithStatus:RoomBottomBarStatsuRoom];
        _roomBottomBarView.delegate = self;
    }
    return _roomBottomBarView;
}

- (ScreenShareViewController *)screenShareViewController {
    if (!_screenShareViewController) {
        _screenShareViewController = [[ScreenShareViewController alloc] init];
    }
    return _screenShareViewController;
}

- (SetingViewController *)setingViewController {
    if (!_setingViewController) {
        _setingViewController = [[SetingViewController alloc] init];
        _setingViewController.delegate = self;
    }
    return _setingViewController;
}

- (MeetingEndCompoments *)endCompoments {
    if (!_endCompoments) {
        _endCompoments = [[MeetingEndCompoments alloc] init];
        _endCompoments.isWindow = NO;
    }
    return _endCompoments;
}

- (ParamView *)paramView {
    if (!_paramView) {
        _paramView = [[ParamView alloc] init];
    }
    return _paramView;
}

- (NSMutableArray<RoomUserModel *> *)currentUserLists {
    if (!_currentUserLists) {
        _currentUserLists = [[NSMutableArray alloc] init];
    }
    return _currentUserLists;
}

- (NSArray<RoomUserModel *> *)currentTopUserLists {
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

- (dispatch_semaphore_t)lock {
    if (_lock == nil) {
        _lock = dispatch_semaphore_create(1);
    }
    return _lock;
}

- (void)dealloc {
    NSLog(@"[dealloc]%@",self.className);
}


@end
