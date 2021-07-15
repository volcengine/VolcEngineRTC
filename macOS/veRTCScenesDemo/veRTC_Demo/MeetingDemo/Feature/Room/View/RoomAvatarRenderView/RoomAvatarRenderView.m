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
@property (nonatomic, strong) NSView *noVideoMaskView;
@property (nonatomic, strong) MeetingAvatarCompoments *avatarBgView;
@property (nonatomic, strong) RoomAvatarRenderTagView *nameTagView;
@property (nonatomic, strong) NSView *avatarSpeakView;

//Show when there is a video
@property (nonatomic, strong) RoomAvatarRenderTagView *tagView;
@property (nonatomic, strong) NSView *speakView;

@end

@implementation RoomAvatarRenderView

- (instancetype)init {
    self = [super init];
    if (self) {
        [self setBackgroundColorWithHexString:@"#272E3B"];
        
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(updateLocalCameraStatusNotice:) name:NoticeUpdateLocalCameraStatusName object:nil];
        
        self.wantsLayer = YES;
        self.layer.masksToBounds = YES;
        self.layer.cornerRadius = 2;
        
        [self addSubview:self.noVideoMaskView];
        [self.noVideoMaskView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.edges.equalTo(self);
        }];
        
        [self addSubview:self.avatarBgView];
        [self.avatarBgView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.size.mas_equalTo(CGSizeMake(0, 0));
            make.centerX.equalTo(self);
            make.centerY.equalTo(self).offset(0);
        }];

        [self addSubview:self.nameTagView];
        [self.nameTagView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.centerX.equalTo(self);
            make.top.equalTo(self.avatarBgView.mas_bottom).offset(12);
            make.height.mas_equalTo(20);
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

- (void)setAvatarStatus:(RoomAvatarStatus)avatarStatus {
    _avatarStatus = avatarStatus;
    
    NSInteger itemWith = 0;
    NSInteger centerOffsetY = 0;
    NSInteger fontNum = 0;
    NSInteger avatarBgFontNum = 0;
    switch (avatarStatus) {
        case RoomAvatarStatusGalleryOne:
            itemWith = 200;
            centerOffsetY = (24 + 16)/2;
            fontNum = 16;
            avatarBgFontNum = 40;
            break;
        case RoomAvatarStatusGalleryTwo:
            itemWith = 80;
            centerOffsetY = (24 + 16)/2;
            fontNum = 16;
            avatarBgFontNum = 36;
            break;
        case RoomAvatarStatusGalleryFour:
            itemWith = 80;
            centerOffsetY = (24 + 16)/2;
            fontNum = 16;
            avatarBgFontNum = 36;
            break;
        case RoomAvatarStatusGalleryNine:
            itemWith = 64;
            centerOffsetY = (22 + 12)/2;
            fontNum = 14;
            avatarBgFontNum = 24;
            break;
        case RoomAvatarStatusSpaker:
            itemWith = 40;
            centerOffsetY = (20 +8)/2;
            fontNum = 12;
            avatarBgFontNum = 20;
            break;
            
        default:
            break;
    }
    [self.avatarBgView mas_updateConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(itemWith, itemWith));
        make.centerY.equalTo(self).offset(-centerOffsetY);
    }];
    self.avatarBgView.fontSize = avatarBgFontNum;
    
    self.avatarBgView.layer.cornerRadius = itemWith / 2;
    self.nameTagView.font = [NSFont systemFontOfSize:fontNum weight:NSFontWeightRegular];
    self.avatarSpeakView.layer.cornerRadius = itemWith / 2;
}

#pragma mark - Notice Method

- (void)updateLocalCameraStatusNotice:(NSNotification *)notification {
    if (self.userModel.isSelf) {
        NSNumber *number = (NSNumber *)notification.object;
        self.userModel.isEnableCamera = number.boolValue;
        [self updateUIWithModel:self.userModel];
    }
}

#pragma mark - Publish Action

- (void)setUserModel:(RoomUserModel *)userModel {
    _userModel = userModel;

    [self updateUIWithModel:userModel];
}

- (void)updateUIWithModel:(RoomUserModel *)userModel {
    if (userModel.isEnableCamera && userModel.isVideoStream) {
        userModel.streamView.hidden = NO;
        [self addSubview:userModel.streamView positioned:NSWindowBelow relativeTo:nil];
        [userModel.streamView mas_remakeConstraints:^(MASConstraintMaker *make) {
            make.edges.equalTo(self);
        }];
        
        self.tagView.userModel = userModel;
        self.tagView.hidden = NO;
        self.avatarBgView.hidden = YES;
        self.noVideoMaskView.hidden = YES;
        self.nameTagView.hidden = YES;
        self.speakView.hidden = !userModel.isMaxVolume;
        self.avatarSpeakView.hidden = YES;
    } else {
        userModel.streamView.hidden = YES;
        [userModel.streamView removeFromSuperview];
        
        self.tagView.hidden = YES;
        self.nameTagView.userModel = userModel;
        self.avatarBgView.text = userModel.name;
        self.avatarBgView.hidden = NO;
        self.noVideoMaskView.hidden = NO;
        self.nameTagView.hidden = NO;
        self.speakView.hidden = YES;
        self.avatarSpeakView.hidden = !userModel.isMaxVolume;
    }
}

#pragma mark - getter

- (MeetingAvatarCompoments *)avatarBgView {
    if (!_avatarBgView) {
        _avatarBgView = [[MeetingAvatarCompoments alloc] init];
        _avatarBgView.wantsLayer = YES;
        _avatarBgView.layer.masksToBounds = YES;
        _avatarBgView.hidden = YES;
    }
    return _avatarBgView;
}

- (RoomAvatarRenderTagView *)nameTagView {
    if (!_nameTagView) {
        _nameTagView = [[RoomAvatarRenderTagView alloc] init];
        _nameTagView.textColor = [NSColor colorFromHexString:@"#FFFFFF"];
        _nameTagView.hidden = YES;
    }
    return _nameTagView;
}

- (RoomAvatarRenderTagView *)tagView {
    if (!_tagView) {
        _tagView = [[RoomAvatarRenderTagView alloc] init];
        [_tagView setBackgroundColor:[NSColor clearColor]];
    }
    return _tagView;
}

- (NSView *)speakView {
    if (!_speakView) {
        _speakView = [[NSView alloc] init];
        _speakView.wantsLayer = YES;
        _speakView.layer.masksToBounds = YES;
        _speakView.layer.borderWidth = 2;
        _speakView.layer.borderColor = [NSColor colorFromHexString:@"#4080FF"].CGColor;
        _speakView.layer.cornerRadius = 2;
        _speakView.hidden = YES;
    }
    return _speakView;
}

- (NSView *)avatarSpeakView {
    if (!_avatarSpeakView) {
        _avatarSpeakView = [[NSView alloc] init];
        _avatarSpeakView.wantsLayer = YES;
        _avatarSpeakView.layer.masksToBounds = YES;
        _avatarSpeakView.layer.borderWidth = 2;
        _avatarSpeakView.layer.borderColor = [NSColor colorFromHexString:@"#4080FF"].CGColor;
        _avatarSpeakView.hidden = YES;
    }
    return _avatarSpeakView;
}

- (NSView *)noVideoMaskView {
    if (!_noVideoMaskView) {
        _noVideoMaskView = [[NSView alloc] init];
        [_noVideoMaskView setBackgroundColorWithHexString:@"#272E3B"];
        _noVideoMaskView.hidden = YES;
    }
    return _noVideoMaskView;
}

- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

@end
