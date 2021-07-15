//
//  RoomSpeakerView.m
//  quickstart
//
//  Created by  on 2021/3/25.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import "RoomSpeakerView.h"
#import "RoomAvatarRenderView.h"
#import "RoomAvatarRenderTagView.h"
#import "RoomScreenView.h"

@interface RoomSpeakerView ()

@property (nonatomic, strong) RoomAvatarRenderView *renderFirstView;
@property (nonatomic, strong) RoomAvatarRenderView *renderSeconsView;
@property (nonatomic, strong) UIView *renderScreenView;
@property (nonatomic, strong) RoomScreenView *screenView;

@property (nonatomic, strong) RoomAvatarRenderTagView *landscapeStatusView;

@property (nonatomic, strong) BaseButton *orientationButton;

@end

@implementation RoomSpeakerView

- (instancetype)init {
    self = [super init];
    if (self) {
        self.backgroundColor = [UIColor colorFromHexString:@"#1D2129"];
        
        [self addSubview:self.renderFirstView];
        [self addSubview:self.renderSeconsView];
        [self addSubview:self.renderScreenView];
        [self addSubview:self.orientationButton];
        [self addSubview:self.landscapeStatusView];
        [self addSubview:self.screenView];
        [self addConstraints];
    }
    return self;
}

#pragma mark - Publish Action

- (void)bindVideoSessions:(NSArray<RoomVideoSession *> *)videoSessions {
    if (videoSessions.count <= 0) {
        return;
    }
    self.landscapeStatusView.userModel = [self getScreenUser:videoSessions];
    NSArray *dataLists = [self screenStreamShowUsers:videoSessions];
    
    if (dataLists.count >= 1) {
        self.renderFirstView.hidden = NO;
        self.renderFirstView.userModel = dataLists.firstObject;
        self.renderSeconsView.hidden = YES;
        [self.renderFirstView mas_updateConstraints:^(MASConstraintMaker *make) {
            make.centerX.mas_equalTo(0);
        }];
    }
    if (dataLists.count >= 2) {
        self.renderSeconsView.userModel = dataLists[1];
        self.renderSeconsView.hidden = NO;
        [self.renderFirstView mas_updateConstraints:^(MASConstraintMaker *make) {
            make.centerX.mas_equalTo(-88);
        }];
    }
}

- (NSArray *)screenStreamShowUsers:(NSArray<RoomVideoSession *> *)videoSessions {
    NSMutableArray *dataLists = [[NSMutableArray alloc] init];
    if ([self.localVideoSession.uid isEqualToString:self.currentRoomModel.host_id]) {
        //login user is host
        NSInteger length = MIN(videoSessions.count, 2);
        for (int i = 0; i < length; i++) {
            [dataLists addObject:videoSessions[i]];
        }
    } else {
        NSInteger selfNumber = 0;
        for (int i = 0; i < videoSessions.count; i++) {
            RoomVideoSession *user = videoSessions[i];
            if ([user.uid isEqualToString:self.localVideoSession.uid]) {
                [dataLists addObject:user];
                selfNumber = i;
                break;
            }
        }
        if (selfNumber + 1 >= videoSessions.count) {
            [dataLists addObject:videoSessions.firstObject];
        } else {
            [dataLists addObject:videoSessions[selfNumber + 1]];
        }
    }
    return dataLists;
}

- (void)setIsLandscape:(BOOL)isLandscape {
    _isLandscape = isLandscape;
    
    self.landscapeStatusView.hidden = !isLandscape;
    
    CGSize size = CGSizeMake(320/2, 184/2);
    if (isLandscape) {
        size = CGSizeZero;
    }
    [self.renderSeconsView mas_updateConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(size);
    }];
    [self.renderFirstView mas_updateConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(size);
    }];
    [self.renderScreenView mas_updateConstraints:^(MASConstraintMaker *make) {
        if (isLandscape) {
            make.top.equalTo(self.renderSeconsView.mas_bottom).offset(30);
        } else {
            make.top.equalTo(self.renderSeconsView.mas_bottom).offset(12);
        }
    }];
    self.orientationButton.status = isLandscape ? ButtonStatusActive : ButtonStatusNone;
}

- (void)setCurrentRoomModel:(MeetingControlRoomModel *)currentRoomModel {
    _currentRoomModel = currentRoomModel;
    if ([self.localVideoSession.uid isEqualToString:currentRoomModel.screen_shared_uid]) {
        self.screenView.hidden = NO;
        self.screenView.clickCloseBlock = self.clickCloseBlock;
    } else {
        self.screenView.hidden = YES;
    }
}

- (void)setScreenStreamsUid:(NSString *)screenStreamsUid {
    _screenStreamsUid = screenStreamsUid;
    if (screenStreamsUid && screenStreamsUid.length > 0) {
        [[MeetingRTCManager shareRtc] setupRemoteScreen:self.renderScreenView uid:screenStreamsUid];
        [[MeetingRTCManager shareRtc] subscribeScreenStream:screenStreamsUid];
    } else {
        [[MeetingRTCManager shareRtc] unsubscribeScreen:NOEmptyStr(screenStreamsUid) ? screenStreamsUid : @""];
    }
}

#pragma mark - Action Method

- (void)orientationButtonAction {
    if (self.clickOrientationBlock) {
        self.clickOrientationBlock();
    }
}

#pragma mark - Private Action

- (RoomVideoSession *)getScreenUser:(NSArray<RoomVideoSession *> *)videoSessions {
    RoomVideoSession *currentUserModel = nil;
    for (RoomVideoSession *userModel in videoSessions) {
        if (userModel.isScreen) {
            currentUserModel = userModel;
            break;
        }
    }
    return currentUserModel;
}

- (void)addConstraints {
    [self.renderFirstView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(320/2, 184/2));
        make.top.equalTo(self);
        make.centerX.mas_equalTo(-88);
    }];
    
    [self.renderSeconsView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(320/2, 184/2));
        make.top.equalTo(self);
        make.left.equalTo(self.renderFirstView.mas_right).offset(32/2);
    }];
    
    [self.renderScreenView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(self.renderSeconsView.mas_bottom).offset(12);
        make.left.right.bottom.equalTo(self);
    }];
    
    [self.screenView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(self.renderSeconsView.mas_bottom).offset(0);
        make.left.right.bottom.equalTo(self);
    }];
    
    [self.orientationButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(44, 44));
        make.right.bottom.mas_equalTo(-32/2);
    }];
    
    [self.landscapeStatusView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.height.mas_equalTo(30);
        make.centerX.top.equalTo(self);
    }];
}

#pragma mark - getter

- (RoomAvatarRenderView *)renderFirstView {
    if (!_renderFirstView) {
        _renderFirstView = [[RoomAvatarRenderView alloc] init];
        _renderFirstView.hidden = YES;
        _renderFirstView.avatarStatus = RoomAvatarStatusSpaker;
        _renderFirstView.backgroundColor = [UIColor colorFromHexString:@"#272E3B"];
        _renderFirstView.layer.masksToBounds = YES;
        _renderFirstView.layer.cornerRadius = 2;
    }
    return _renderFirstView;
}

- (RoomAvatarRenderView *)renderSeconsView {
    if (!_renderSeconsView) {
        _renderSeconsView = [[RoomAvatarRenderView alloc] init];
        _renderSeconsView.hidden = YES;
        _renderSeconsView.avatarStatus = RoomAvatarStatusSpaker;
        _renderSeconsView.backgroundColor = [UIColor colorFromHexString:@"#272E3B"];
        _renderSeconsView.layer.masksToBounds = YES;
        _renderSeconsView.layer.cornerRadius = 2;
    }
    return _renderSeconsView;
}

- (UIView *)renderScreenView {
    if (!_renderScreenView) {
        _renderScreenView = [[UIView alloc] init];
    }
    return _renderScreenView;
}

- (RoomScreenView *)screenView {
    if (!_screenView) {
        _screenView = [[RoomScreenView alloc] init];
        _screenView.backgroundColor = [UIColor colorFromHexString:@"#1D2129"];
        _screenView.hidden = YES;
    }
    return _screenView;
}

- (BaseButton *)orientationButton {
    if (!_orientationButton) {
        _orientationButton = [[BaseButton alloc] init];
        [_orientationButton addTarget:self action:@selector(orientationButtonAction) forControlEvents:UIControlEventTouchUpInside];
        [_orientationButton bingImage:[UIImage imageNamed:@"meeting_room_orientation"] status:ButtonStatusNone];
        [_orientationButton bingImage:[UIImage imageNamed:@"meeting_room_orientation_v"] status:ButtonStatusActive];
    }
    return _orientationButton;
}

- (RoomAvatarRenderTagView *)landscapeStatusView {
    if (!_landscapeStatusView) {
        _landscapeStatusView = [[RoomAvatarRenderTagView alloc] init];
        _landscapeStatusView.hidden = YES;
        _landscapeStatusView.hiddenBG = YES;
    }
    return _landscapeStatusView;
}

@end
