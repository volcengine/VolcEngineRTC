//
//  RoomAvatarRenderView.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/12.
//

#import "RoomAvatarRenderView.h"
#import "MeetingAvatarCompoments.h"
#import "RoomAvatarRenderTagView.h"

@interface RoomAvatarRenderView ()

//Show when there is no video
@property (nonatomic, strong) MeetingAvatarCompoments *avatarBgView;
@property (nonatomic, strong) RoomAvatarRenderTagView *emptyVideoTagView;
@property (nonatomic, strong) UIView *avatarSpeakView;

//Show when there is a video
@property (nonatomic, strong) RoomAvatarRenderTagView *tagView;
@property (nonatomic, strong) UIView *renderView;
@property (nonatomic, strong) UIView *speakView;

@property (nonatomic, assign) RoomAvatarStatus currentStatus;

@end

@implementation RoomAvatarRenderView

- (instancetype)init {
    self = [super init];
    if (self) {
        self.backgroundColor = [UIColor colorFromHexString:@"#272E3B"];
        
        self.layer.masksToBounds = YES;
        self.layer.cornerRadius = 2;
        
        [self addSubview:self.avatarBgView];
        [self.avatarBgView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.size.mas_equalTo(CGSizeMake(90, 90));
            make.centerX.equalTo(self);
            make.centerY.equalTo(self).offset(0);
        }];

        [self addSubview:self.emptyVideoTagView];
        [self.emptyVideoTagView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.centerX.equalTo(self);
            make.top.equalTo(self.avatarBgView.mas_bottom).offset(12);
            make.height.mas_equalTo(20);
        }];
        
        [self addSubview:self.renderView];
        [self.renderView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.edges.equalTo(self);
        }];
        
        [self addSubview:self.tagView];
        [self.tagView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.right.bottom.equalTo(self);
            make.height.mas_equalTo(20);
        }];
        
        [self addSubview:self.speakView];
        [self.speakView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.edges.equalTo(self);
        }];
        
        [self addSubview:self.avatarSpeakView];
        [self.avatarSpeakView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.edges.equalTo(self.avatarBgView);
        }];
    }
    return self;
}

#pragma mark - Publish Action

- (void)setAvatarStatus:(RoomAvatarStatus)avatarStatus {
    _avatarStatus = avatarStatus;
    
    NSInteger itemWith = 0;
    NSInteger centerYOffset = 0;
    NSInteger fontNum = 0;
    NSInteger avatarBgFontNum = 0;
    switch (avatarStatus) {
        case RoomAvatarStatusSpaker:
            itemWith = 40;
            centerYOffset = -14;
            fontNum = 12;
            avatarBgFontNum = 20;
            break;
        case RoomAvatarStatusGalleryNone:
            itemWith = 90;
            centerYOffset = -18;
            fontNum = 16;
            avatarBgFontNum = 32;
            break;
        case RoomAvatarStatusGalleryFull:
            itemWith = 60;
            centerYOffset = -16;
            fontNum = 16;
            avatarBgFontNum = 24;
            break;
        case RoomAvatarStatusGalleryOne:
            itemWith = 120;
            centerYOffset = -18;
            fontNum = 20;
            avatarBgFontNum = 44;
            break;
        default:
            break;
    }
    self.avatarBgView.layer.cornerRadius = itemWith / 2;
    self.avatarSpeakView.layer.cornerRadius = itemWith / 2;
    self.avatarBgView.fontSize = avatarBgFontNum;
    self.emptyVideoTagView.font = [UIFont systemFontOfSize:fontNum weight:UIFontWeightRegular];
    [self.avatarBgView mas_updateConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(itemWith, itemWith));
        make.centerY.equalTo(self).offset(centerYOffset);
    }];
}

- (void)setUserModel:(RoomVideoSession *)userModel {
    _userModel = userModel;

    [self updateUIWithModel:userModel];
}

- (void)updateUIWithModel:(RoomVideoSession *)userModel {
    BOOL isSpeack = userModel.isMaxVolume && userModel.volume > 0;
    if (userModel.isEnableVideo && userModel.isVideoStream) {
        [self.renderView addSubview:userModel.streamView];
        [userModel.streamView mas_remakeConstraints:^(MASConstraintMaker *make) {
            make.edges.equalTo(self.renderView);
        }];
        self.tagView.userModel = userModel;
        self.tagView.hidden = NO;
        self.renderView.hidden = NO;
        self.avatarBgView.hidden = YES;
        self.emptyVideoTagView.hidden = YES;
        self.speakView.hidden = !isSpeack;
        self.avatarSpeakView.hidden = YES;
    } else {
        self.emptyVideoTagView.userModel = userModel;
        self.emptyVideoTagView.hidden = NO;
        self.renderView.hidden = YES;
        self.tagView.hidden = YES;
        self.avatarBgView.text = userModel.name;
        self.avatarBgView.hidden = NO;
        self.speakView.hidden = YES;
        self.avatarSpeakView.hidden = !isSpeack;
    }
}

#pragma mark - getter

- (UIView *)renderView {
    if (!_renderView) {
        _renderView = [[UIView alloc] init];
        [_renderView setBackgroundColor:[UIColor clearColor]];
    }
    return _renderView;
}

- (MeetingAvatarCompoments *)avatarBgView {
    if (!_avatarBgView) {
        _avatarBgView = [[MeetingAvatarCompoments alloc] init];
        _avatarBgView.layer.masksToBounds = YES;
    }
    return _avatarBgView;
}

- (RoomAvatarRenderTagView *)emptyVideoTagView {
    if (!_emptyVideoTagView) {
        _emptyVideoTagView = [[RoomAvatarRenderTagView alloc] init];
        _emptyVideoTagView.textColor = [UIColor colorFromHexString:@"#FFFFFF"];
    }
    return _emptyVideoTagView;
}

- (RoomAvatarRenderTagView *)tagView {
    if (!_tagView) {
        _tagView = [[RoomAvatarRenderTagView alloc] init];
        [_tagView setBackgroundColor:[UIColor clearColor]];
        _tagView.hidden = YES;
    }
    return _tagView;
}

- (UIView *)speakView {
    if (!_speakView) {
        _speakView = [[UIView alloc] init];
        _speakView.layer.masksToBounds = YES;
        _speakView.layer.borderWidth = 2;
        _speakView.layer.borderColor = [UIColor colorFromHexString:@"#4080FF"].CGColor;
        _speakView.layer.cornerRadius = 2;
        _speakView.hidden = YES;
    }
    return _speakView;
}

- (UIView *)avatarSpeakView {
    if (!_avatarSpeakView) {
        _avatarSpeakView = [[UIView alloc] init];
        _avatarSpeakView.layer.masksToBounds = YES;
        _avatarSpeakView.layer.borderWidth = 2;
        _avatarSpeakView.layer.borderColor = [UIColor colorFromHexString:@"#4080FF"].CGColor;
        _avatarSpeakView.hidden = YES;
    }
    return _avatarSpeakView;
}


- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

@end
