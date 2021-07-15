//
//  RoomViewController.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/10.
//

#import "RoomViewController.h"
#import "RoomViewController+Listener.h"
#import "RoomViewController+Sort.h"
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
@property (nonatomic, weak) ParticipantViewController *participantViewController;
@property (nonatomic, strong) GalleryModeView *galleryModeView;
@property (nonatomic, strong) SpeakerModeView *speakerModeView;
@property (nonatomic, strong) ParamView *paramView;
@property (nonatomic, strong) MeetingEndCompoments *endCompoments;

@property (nonatomic, strong) NSMutableDictionary <NSString *, NSString *> *currentStreamDic;

@property (nonatomic, strong) NSView *videoViewTest;
@property (nonatomic, strong) NSString *recordID;

@property (nonatomic, strong) dispatch_semaphore_t lock;


@end

@implementation RoomViewController

- (instancetype)initWithLoginModel:(LoginModel *)loginModel userLists:(NSArray<RoomUserModel *> *)userLists {
    self = [super init];
    if (self) {
        self.loginModel = loginModel;
        [self.userDataPool removeAllObjects];
        [self.userDataPool addObjectsFromArray:userLists];
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
    
    //Sort user lists
    __weak __typeof(self) wself = self;
    [self statrSort:^(NSMutableArray * _Nonnull userLists) {
        [wself sortEndCallback:userLists];
    }];
    
    //Refresh now render view
    [self updateRenderModeView:[self updateSortListsPromptly]];
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
        [appDelegate.windowManager showMeetingWindowController:NO];
        [self hangUpAction];
        //socket api end Meeting
        [MeetingControlCompoments endMeeting];
        //sdk api end Meeting
        [[MeetingRTCManager shareMeetingRTCManager] stopScreenCapture];
    } else if ([key isEqualToString:@"leave"]) {
        [appDelegate.windowManager showMeetingWindowController:NO];
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
    [MeetingControlCompoments recordMeeting:[self getRecordUids]
                                   screenId:self.currentRoomModel.screen_shared_uid];
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
                if ([self.currentRoomModel.screen_shared_uid isEqualToString:[LocalUserCompoments userModel].uid]) {
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
                if ([self.currentRoomModel.host_id isEqualToString:[LocalUserCompoments userModel].uid]) {
                    button.isClose = YES;
                    [[NSNotificationCenter defaultCenter] postNotificationName:NoticeUpdateRoomRecordName object:@(button.isClose)];
                
                    //Start record Meeting socket api
                    [MeetingControlCompoments recordMeeting:[self getRecordUids]
                                                   screenId:self.currentRoomModel.screen_shared_uid];
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

- (void)rtcManager:(MeetingRTCManager * _Nonnull)rtcManager didStreamAdded:(NSString * _Nullable)streamsUid {
    if (NOEmptyStr(streamsUid)) {
        [self.currentStreamDic setValue:@"1" forKey:streamsUid];
    }
}

- (void)rtcManager:(MeetingRTCManager *_Nonnull)rtcManager didStreamRemoved:(NSString *_Nullable)streamsUid {
    if (NOEmptyStr(streamsUid)) {
        [self.currentStreamDic removeObjectForKey:streamsUid];
    }
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

#pragma mark - ParticipantVC

- (void)showParticipantVC {
    if (self.participantViewController) {
        [self dismissParticipantVC];
    }
    
    ParticipantViewController *participantViewController = [[ParticipantViewController alloc] init];
    [self.view addSubview:participantViewController];
    CGFloat parWidth = 280;
    [participantViewController mas_makeConstraints:^(MASConstraintMaker *make) {
        make.right.top.bottom.equalTo(self.view);
        make.width.mas_equalTo(parWidth);
    }];
    __weak __typeof(self) wself = self;
    participantViewController.clickCancelBlock = ^(BOOL isEnable) {
        [wself.roomBottomBarView updateButtonStatus:BottomBarStatusPeople close:NO];
        [wself dismissParticipantVC];
    };
    participantViewController.isLoginHost = [[LocalUserCompoments userModel].uid isEqualToString:self.currentRoomModel.host_id] ? YES : NO;
    participantViewController.loginModel = self.loginModel;
    self.participantViewController = participantViewController;
}

- (void)dismissParticipantVC {
    if (self.participantViewController) {
        [self.participantViewController removeAllSubView];
        [self.participantViewController removeFromSuperview];
        self.participantViewController = nil;
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

- (void)updateRenderModeView:(NSArray *)userLists {
    dispatch_async(dispatch_get_main_queue(), ^{
        if (!self.galleryModeView.hidden) {
            self.galleryModeView.dataLists = userLists;
        } else if (!self.speakerModeView.hidden) {
            self.speakerModeView.dataLists = userLists;
        } else {
            //error
        }
        self.participantViewController.videoSessions = userLists;
    });
}

- (void)addUser:(RoomUserModel *)roomUserModel {
    //add lock
    dispatch_semaphore_wait(self.lock, DISPATCH_TIME_FOREVER);
    //重复数据删除
    //Deduplication
    NSInteger index = -1;
    for (int i = 0; i < self.userDataPool.count; i++) {
        RoomUserModel *userModel = self.userDataPool[i];
        if ([userModel.uid isEqualToString:roomUserModel.uid]) {
            index = i;
            break;
        }
    }
    if (index >= 0) {
        [self.userDataPool replaceObjectAtIndex:index withObject:roomUserModel];
    } else {
        if ([roomUserModel.uid isEqualToString:[LocalUserCompoments userModel].uid]) {
            [self.userDataPool insertObject:roomUserModel atIndex:0];
        } else {
            [self.userDataPool addObject:roomUserModel];
        }
    }
    dispatch_semaphore_signal(self.lock);
}

- (void)removeUser:(NSString *)uid {
    NSMutableArray *sortUserLists = [self removeSortListsPromptly:uid];
    [self updateRenderModeView:sortUserLists];
}

- (void)hangUpAction {
    //Stop sort timer
    [self stopSort];
    
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
    [self.endCompoments showWithStatus:[self.currentRoomModel.host_id isEqualToString:[LocalUserCompoments userModel].uid] ? MeetingEndStatusHost : MeetingEndStatusNone];
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

- (void)updateRecordLayout:(NSArray<NSString *> *)uids screenId:(NSString *)screenId {
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

- (NSArray<NSString *> *)getRecordUids {
    NSArray *userLists = [self getSortUserLists];
    NSInteger maxLimit = 9;
    if (self.currentRoomModel.screen_shared_uid.length > 0) {
        //There is screen flow
        maxLimit = 8;
    }
    NSInteger currentLen = MIN(userLists.count, maxLimit);
    NSArray *lists = [userLists subarrayWithRange:NSMakeRange(0, currentLen)];
    NSMutableArray *uids = [[NSMutableArray alloc] init];
    for (int i = 0; i < lists.count; i++) {
        RoomUserModel *userModel = lists[i];
        [uids addObject:userModel.uid];
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

- (void)loadDataWithMeetingContrller {
    __weak __typeof(self) wself = self;
    [MeetingControlCompoments getMeetingInfoWithBlock:^(MeetingControlRoomModel * _Nonnull roomModel, MeetingControlAckModel * _Nonnull model) {
        wself.currentRoomModel = roomModel;
        BOOL isOpenScreen = (roomModel.screen_shared_uid.length > 0);
        [wself updateModeWithStatus:!isOpenScreen ? RoomModeStatusGallery : RoomModeStatusSpaker];
        [wself.roomBottomBarView updateButtonStatus:BottomBarStatusRecord close:roomModel.record];
        [wself.roomBottomBarView updateButtonStatus:BottomBarStatusScreenShare close:isOpenScreen];
        [[NSNotificationCenter defaultCenter] postNotificationName:NoticeUpdateRoomRecordName object:@(roomModel.record)];
        [[NSNotificationCenter defaultCenter] postNotificationName:NoticeUpdateRoomExpandListName object:@(!wself.speakerModeView.hidden)];
        [wself updateNavTimeWithModel:roomModel];
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

#pragma mark - RoomViewController + Sort

- (void)sortEndCallback:(NSMutableArray * _Nonnull)userLists {
    NSDictionary *subscribeUidDic = [[MeetingRTCManager shareMeetingRTCManager] getSubscribeUidDic];
    //Unsubscribe first
    if (subscribeUidDic.count > 0) {
        for (int i = 0; i < userLists.count; i++) {
            RoomUserModel *userModel = userLists[i];
            NSString *value = [subscribeUidDic objectForKey:userModel.uid];
            if ([value integerValue] == 1 && i >= MaxAvatarNumber) {
                [[MeetingRTCManager shareMeetingRTCManager] unsubscribe:userModel.uid];
                userModel.isVideoStream = NO;
            }
        }
    }

    for (int i = 0; i < userLists.count; i++) {
        RoomUserModel *userModel = userLists[i];
        if (![userModel.uid isEqualToString:[LocalUserCompoments userModel].uid]) {
            //Don't subscribe self
            NSString *isStream = self.currentStreamDic[userModel.uid];
            if (i < MaxAvatarNumber) {
                if ([isStream integerValue] == 1) {
                    //subscribe
                    userModel.isVideoStream = YES;
                    [[MeetingRTCManager shareMeetingRTCManager] subscribeStream:userModel.uid];
                } else {
                    //unsubscribe
                    userModel.isVideoStream = NO;
                    [[MeetingRTCManager shareMeetingRTCManager] unsubscribe:userModel.uid];
                }
            } else {
                
            }
        }
    }
    
    [self updateRenderModeView:userLists];
    
    if ([[LocalUserCompoments userModel].uid isEqualToString:self.currentRoomModel.host_id]) {
        [self updateRecordLayout:[self getRecordUids]
                        screenId:self.currentRoomModel.screen_shared_uid];
    }
}

- (void)updateRenderModeViewUserRankeWithAudioVolume:(NSDictionary<NSString *, ByteRtcAudioVolumeInfo *> *)volumeInfo {
    dispatch_semaphore_wait(self.lock, DISPATCH_TIME_FOREVER);
    for (RoomUserModel *userModel in self.userDataPool) {
        ByteRtcAudioVolumeInfo *volumeModel = [volumeInfo objectForKey:userModel.uid];
        if (volumeModel) {
            userModel.volume = volumeModel.volume;
        } else {
            userModel.volume = 0;
        }
    }
    dispatch_semaphore_signal(self.lock);
}

- (void)updateRenderModeViewWithCameraStatus:(NSString *)uid enableCamera:(BOOL)isEnable {
    dispatch_semaphore_wait(self.lock, DISPATCH_TIME_FOREVER);
    for (RoomUserModel *userModel in self.userDataPool) {
        if ([userModel.uid isEqualToString:uid]) {
            userModel.isEnableCamera = isEnable;
            break;
        }
    }
    dispatch_semaphore_signal(self.lock);
}

- (void)updateRenderModeViewWithMicStatus:(NSString *)uid enableMic:(BOOL)isEnable {
    dispatch_semaphore_wait(self.lock, DISPATCH_TIME_FOREVER);
    if (IsEmptyStr(uid)) {
        //mute all user
        for (RoomUserModel *userModel in self.userDataPool) {
            if (![userModel.uid isEqualToString:self.currentRoomModel.host_id]) {
                userModel.isEnableMic = isEnable;
            }
        }
    } else {
        //mute user
        for (RoomUserModel *userModel in self.userDataPool) {
            if ([userModel.uid isEqualToString:uid]) {
                userModel.isEnableMic = isEnable;
                break;
            }
        }
    }
    dispatch_semaphore_signal(self.lock);
}

- (void)updateRenderModeViewWithHost:(NSString *)hostID {
    dispatch_semaphore_wait(self.lock, DISPATCH_TIME_FOREVER);
    for (RoomUserModel *userModel in self.userDataPool) {
        //Because there is only one host, the status of everyone needs to be updated
        userModel.isHost = ([userModel.uid isEqualToString:hostID]) ? YES : NO;
    }
    self.participantViewController.isLoginHost = [[LocalUserCompoments userModel].uid isEqualToString:hostID] ? YES : NO;
    dispatch_semaphore_signal(self.lock);
}

- (void)updateRenderModeViewWithScreenStatus:(NSString *)uid enableScreen:(BOOL)isShare {
    dispatch_semaphore_wait(self.lock, DISPATCH_TIME_FOREVER);
    for (RoomUserModel *userModel in self.userDataPool) {
        if (isShare) {
            if ([userModel.uid isEqualToString:uid]) {
                userModel.isOpenScreen = YES;
            } else {
                userModel.isOpenScreen = NO;
            }
        } else {
            userModel.isOpenScreen = NO;
        }
    }
    dispatch_semaphore_signal(self.lock);
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

- (NSMutableArray<RoomUserModel *> *)userDataPool {
    if (!_userDataPool) {
        _userDataPool = [[NSMutableArray alloc] init];
    }
    return _userDataPool;
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
