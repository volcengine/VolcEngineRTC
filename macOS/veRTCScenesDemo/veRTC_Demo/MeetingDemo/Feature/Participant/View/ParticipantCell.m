//
//  ParticipantCell.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/10.
//

#import "ParticipantCell.h"
#import "MeetingAvatarCompoments.h"

@interface ParticipantCell ()

@property (nonatomic, strong) MeetingAvatarCompoments *avatartView;
@property (nonatomic, strong) NSView *avatarSpeakView;
@property (nonatomic, strong) NSLabel *nameLabel;
@property (nonatomic, strong) NSImageView *micImageView;
@property (nonatomic, strong) NSImageView *videoImageView;

@property (nonatomic, strong) NSButton *hostTipView;
@property (nonatomic, strong) NSImageView *screenImageView;

@property (nonatomic, strong) TrackButton *hostButton;
@property (nonatomic, strong) TrackButton *micButton;

@end

@implementation ParticipantCell

- (void)awakeFromNib {
    [self setBackgroundColor:[NSColor clearColor]];
    [self updateTrackingAreas];
    
    [self addSubview:self.avatartView];
    [self addSubview:self.nameLabel];
    [self addSubview:self.micImageView];
    [self addSubview:self.videoImageView];
    
    [self addSubview:self.hostTipView];
    [self addSubview:self.screenImageView];
    
    [self addSubview:self.hostButton];
    [self addSubview:self.micButton];
    
    [self.avatartView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(28, 28));
        make.left.mas_equalTo(16);
        make.centerY.equalTo(self);
    }];
    
    [self.nameLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.equalTo(self.avatartView.mas_right).offset(8);
        make.centerY.equalTo(self);
    }];
    
    [self.micImageView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(16, 16));
        make.right.equalTo(self.videoImageView.mas_left).offset(-8);
        make.centerY.equalTo(self);
    }];
    
    [self.videoImageView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(16, 16));
        make.right.mas_equalTo(-16);
        make.centerY.equalTo(self);
    }];
    
    [self.hostTipView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(44, 16));
        make.left.equalTo(self.nameLabel);
        make.top.equalTo(self.nameLabel.mas_bottom).offset(3);
    }];
    
    [self.screenImageView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(16, 16));
        make.centerY.equalTo(self.nameLabel);
        make.left.equalTo(self.nameLabel.mas_right).offset(2);
    }];
    
    [self.hostButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(24, 24));
        make.right.equalTo(self).offset(-12);
        make.centerY.equalTo(self);
    }];
    
    [self.micButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(24, 24));
        make.right.equalTo(self.hostButton.mas_left).offset(-8);
        make.centerY.equalTo(self);
    }];
    
    [self addSubview:self.avatarSpeakView];
    [self.avatarSpeakView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(self.avatartView);
    }];
}

#pragma mark - Click Actuion

- (void)hostButtonAction {
    if (self.clickChangeHost) {
        self.clickChangeHost(self.roomUserModel.uid, self.roomUserModel.name);
    }
}

- (void)micButtonAction {
    BOOL isOpenAudio = self.roomUserModel.isEnableMic;
    if (isOpenAudio) {
        //mute microphone
        [MeetingControlCompoments muteUser:self.roomUserModel.uid block:^(BOOL result, MeetingControlAckModel * _Nonnull model) {
            if (!model.result) {
                [[MeetingToastComponents shareMeetingToastComponents] showWithMessage:model.message];
            }
        }];
    } else {
        //Ask microphone On
        [MeetingControlCompoments askMicOn:self.roomUserModel.uid block:^(BOOL result) {
                    
        }];
    }
}

#pragma mark - Publish Action

- (void)setRoomUserModel:(RoomUserModel *)roomUserModel {
    _roomUserModel = roomUserModel;
    self.hidden = roomUserModel == nil ? YES : NO;
    
    NSString *name = roomUserModel.name;
    NSInteger macLength = 12;
    if (name.length > macLength) {
        name = [roomUserModel.name substringToIndex:macLength];
        name = [NSString stringWithFormat:@"%@...", name];
    }
    self.avatartView.text = roomUserModel.name;
    self.nameLabel.text = name;

    if (roomUserModel.isEnableMic) {
        if (roomUserModel.volume > 0) {
            //ing
            self.micImageView.image = [NSImage imageNamed:@"metting_audio_ing"];
            self.micButton.isClose = NO;
            self.avatarSpeakView.hidden = NO;
        } else {
            self.micImageView.image = [NSImage imageNamed:@"metting_audio_de"];
            self.micButton.isClose = NO;
            self.avatarSpeakView.hidden = YES;
        }
    } else {
        //close
        self.micImageView.image = [NSImage imageNamed:@"metting_login_audio_close"];
        self.micButton.isClose = YES;
        self.avatarSpeakView.hidden = YES;
    }

    if (roomUserModel.isEnableCamera) {
        self.videoImageView.image = [NSImage imageNamed:@"metting_video_de"];
    } else {
        self.videoImageView.image = [NSImage imageNamed:@"metting_login_video_close"];
    }

    if (roomUserModel.isHost) {
        self.hostTipView.hidden = NO;
        [self.nameLabel mas_updateConstraints:^(MASConstraintMaker *make) {
            make.centerY.equalTo(self).offset(-8);
        }];
    } else {
        self.hostTipView.hidden = YES;
        [self.nameLabel mas_updateConstraints:^(MASConstraintMaker *make) {
            make.centerY.equalTo(self);
        }];
    }

    if (roomUserModel.isOpenScreen) {
        self.screenImageView.hidden = NO;
    } else {
        self.screenImageView.hidden = YES;
    }

    [self updateEnterStatus];
}

- (void)mouseEntered:(NSEvent *)event {
    [self trackWithEnter:YES];
}

- (void)mouseExited:(NSEvent *)event {
    [self trackWithEnter:NO];
}

- (void)scrollWheel:(NSEvent *)event {
    [super scrollWheel:event];
    
    [self trackWithEnter:NO];
}

#pragma mark - Private Action

- (void)trackWithEnter:(BOOL)isEnter {
    if (!self.isLoginHost ||
        self.roomUserModel.isSelf) {
        return;
    }
    self.roomUserModel.isTrack = isEnter;
    [self updateEnterStatus];
    if (isEnter) {
        if (self.moveTrackBlock) {
            self.moveTrackBlock(self.roomUserModel.uid);
        }
    }
}

- (void)updateEnterStatus {
    if (self.roomUserModel.isTrack) {
        [self setBackgroundColorWithHexString:@"#272E3B"];
        self.micImageView.hidden = YES;
        self.videoImageView.hidden = YES;
        self.hostButton.hidden = NO;
        self.micButton.hidden = NO;
    } else {
        [self setBackgroundColor:[NSColor clearColor]];
        self.micImageView.hidden = NO;
        self.videoImageView.hidden = NO;
        self.hostButton.hidden = YES;
        self.micButton.hidden = YES;
    }
}

- (void)updateTrackingAreas {
    NSArray * trackingAreas = [self trackingAreas];
    for (NSTrackingArea *area in trackingAreas) {
        [self removeTrackingArea:area];
    }
    
    NSTrackingArea *trackingArea = [[NSTrackingArea alloc] initWithRect:self.bounds
                                                                options:(NSTrackingMouseEnteredAndExited |
                                                                         NSTrackingMouseMoved |
                                                                         NSTrackingActiveInActiveApp |
                                                                         NSTrackingInVisibleRect |
                                                                         NSTrackingAssumeInside |
                                                                         NSTrackingCursorUpdate)
                                                                  owner:self
                                                               userInfo:nil];
    [self addTrackingArea:trackingArea];
}


#pragma mark - getter

- (NSButton *)hostTipView {
    if (!_hostTipView) {
        _hostTipView = [[NSButton alloc] init];
        [_hostTipView setTitleColor:@"#4080FF" title:@"主持人"];
        [_hostTipView setBackgroundColorWithHexString:@"#1D2129"];
        _hostTipView.wantsLayer = YES;
        _hostTipView.layer.masksToBounds = YES;
        _hostTipView.layer.cornerRadius = 2;
    }
    return _hostTipView;
}

- (NSImageView *)screenImageView {
    if (!_screenImageView) {
        _screenImageView = [[NSImageView alloc] init];
        _screenImageView.image = [NSImage imageNamed:@"meeting_par_screen"];
    }
    return _screenImageView;
}

- (MeetingAvatarCompoments *)avatartView {
    if (!_avatartView) {
        _avatartView = [[MeetingAvatarCompoments alloc] init];
        _avatartView.fontSize = 14;
        _avatartView.wantsLayer = YES;
        _avatartView.layer.masksToBounds = YES;
        _avatartView.layer.cornerRadius = 14;
    }
    return _avatartView;
}

- (NSLabel *)nameLabel {
    if (!_nameLabel) {
        _nameLabel = [[NSLabel alloc] init];
        _nameLabel.textColor = [NSColor colorFromHexString:@"#FFFFFF"];
        _nameLabel.font = [NSFont systemFontOfSize:12 weight:NSFontWeightRegular];
        _nameLabel.lineBreakMode = NSLineBreakByTruncatingTail;
    }
    return _nameLabel;
}

- (NSImageView *)micImageView {
    if (!_micImageView) {
        _micImageView = [[NSImageView alloc] init];
        [_micImageView setBackgroundColor:[NSColor clearColor]];
    }
    return _micImageView;
}

- (NSImageView *)videoImageView {
    if (!_videoImageView) {
        _videoImageView = [[NSImageView alloc] init];
        [_videoImageView setBackgroundColor:[NSColor clearColor]];
    }
    return _videoImageView;
}

- (TrackButton *)hostButton {
    if (!_hostButton) {
        _hostButton = [[TrackButton alloc] init];
        [_hostButton setTarget:self];
        [_hostButton setAction:@selector(hostButtonAction)];
        
        [_hostButton bingImageWithType:NO image:[NSImage imageNamed:@"meeting_host_icon"]];
        
        [_hostButton bingBackColorWithStatus:TrackButtonStatusDefault color:[NSColor clearColor]];
        [_hostButton bingBackColorWithStatus:TrackButtonStatusHover color:[NSColor colorFromHexString:@"#1D2129"]];
        
        _hostButton.wantsLayer = YES;
        _hostButton.layer.cornerRadius = 12;
        _hostButton.layer.masksToBounds = YES;
        _hostButton.hidden = YES;
        
        _hostButton.tipTitle = @"移交主持人";
        _hostButton.offsetX = -27;
    }
    return _hostButton;
}

- (TrackButton *)micButton {
    if (!_micButton) {
        _micButton = [[TrackButton alloc] init];
        [_micButton setTarget:self];
        [_micButton setAction:@selector(micButtonAction)];
        
        [_micButton bingImageWithType:NO image:[NSImage imageNamed:@"metting_audio_de"]];
        [_micButton bingImageWithType:YES image:[NSImage imageNamed:@"metting_login_audio_close"]];
        
        [_micButton bingBackColorWithStatus:TrackButtonStatusDefault color:[NSColor clearColor]];
        [_micButton bingBackColorWithStatus:TrackButtonStatusHover color:[NSColor colorFromHexString:@"#1D2129"]];
        
        _micButton.wantsLayer = YES;
        _micButton.layer.cornerRadius = 12;
        _micButton.layer.masksToBounds = YES;
        _micButton.hidden = YES;
        
        _micButton.tipTitle = @"";
    }
    return _micButton;
}

- (NSView *)avatarSpeakView {
    if (!_avatarSpeakView) {
        _avatarSpeakView = [[NSView alloc] init];
        
        _avatarSpeakView.wantsLayer = YES;
        _avatarSpeakView.layer.masksToBounds = YES;
        _avatarSpeakView.layer.borderWidth = 2;
        _avatarSpeakView.layer.cornerRadius = 14;
        _avatarSpeakView.layer.borderColor = [NSColor colorFromHexString:@"#4080FF"].CGColor;
        _avatarSpeakView.hidden = YES;
    }
    return _avatarSpeakView;
}


@end
