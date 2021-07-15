#import "UserListCell.h"
#import "MeetingRTCManager.h"
#import "MeetingAvatarCompoments.h"

@interface UserListCell ()
@property (nonatomic, strong) MeetingAvatarCompoments *avatarView;
@property (nonatomic, strong) UILabel *userIDLabel;
@property (nonatomic, strong) BaseButton *enableAudioBtn;
@property (nonatomic, strong) BaseButton *enableVideoBtn;
@property (nonatomic, strong) UIImageView *screenImageView;
@property (nonatomic, strong) UILabel *hostTipView;

@property (nonatomic, strong) UIView *lineView;
@property (nonatomic, strong) UIView *avatarSpeakView;

@end

@implementation UserListCell

- (instancetype)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier {
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (self) {
        self.backgroundColor = [UIColor clearColor];
        self.contentView.backgroundColor = [UIColor clearColor];
        
        [self createUIComponents];
    }
    return self;
}

#pragma mark - Publish Action

- (void)setVideoSession:(RoomVideoSession *)videoSession {
    _videoSession = videoSession;
    
    //name
    self.userIDLabel.text = videoSession.name;
    self.avatarView.text = videoSession.name;
    
    //camera
    BOOL isOpenVideo = videoSession.isEnableVideo;
    self.enableVideoBtn.status = isOpenVideo ? ButtonStatusNone : ButtonStatusActive;
    
    //mic
    if (videoSession.isEnableAudio) {
        if (videoSession.volume > 0) {
            //ing
            self.enableAudioBtn.status = ButtonStatusIng;
            self.avatarSpeakView.hidden = NO;
        } else {
            //open
            self.enableAudioBtn.status = ButtonStatusNone;
            self.avatarSpeakView.hidden = YES;
        }
    } else {
        //close
        self.enableAudioBtn.status = ButtonStatusActive;
        self.avatarSpeakView.hidden = YES;
    }
    
    //host
    self.hostTipView.hidden = !videoSession.isHost;
    CGFloat centerOffY = videoSession.isHost ? -12 : 0;
    [self.userIDLabel mas_updateConstraints:^(MASConstraintMaker *make) {
        make.centerY.equalTo(self.contentView).offset(centerOffY);
    }];
    
    //screen
    self.screenImageView.hidden = !videoSession.isScreen;
}

- (void)enableVideoBtnAction:(BaseButton *)sender {
    
}

- (void)enableAudioBtnAction:(BaseButton *)sender {
    
}

#pragma mark - Private Action

- (void)createUIComponents {
    [self.contentView addSubview:self.avatarView];
    [self.avatarView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(40, 40));
        make.left.equalTo(self.contentView).offset(32/2);
        make.centerY.equalTo(self.contentView);
    }];

    [self.contentView addSubview:self.enableVideoBtn];
    [self.enableVideoBtn mas_makeConstraints:^(MASConstraintMaker *make) {
        make.right.equalTo(self.contentView).mas_offset(-30);
        make.centerY.equalTo(self.contentView);
        make.height.width.mas_equalTo(24);
    }];
    
    [self.contentView addSubview:self.enableAudioBtn];
    [self.enableAudioBtn mas_makeConstraints:^(MASConstraintMaker *make) {
        make.right.equalTo(self.enableVideoBtn.mas_left).mas_offset(-30);
        make.centerY.equalTo(self.contentView);
        make.height.width.mas_equalTo(24);
    }];
    
    [self addSubview:self.lineView];
    [self.lineView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.height.mas_equalTo(XH_1PX_WIDTH);
        make.left.mas_equalTo(32/2);
        make.right.bottom.equalTo(self.contentView);
    }];
    
    [self.contentView addSubview:self.userIDLabel];
    [self.userIDLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.equalTo(self.avatarView.mas_right).mas_offset(9);
        make.right.lessThanOrEqualTo(self.enableAudioBtn.mas_left).offset(-32);
        make.centerY.equalTo(self.contentView).offset(0);
    }];
    
    [self addSubview:self.screenImageView];
    [self.screenImageView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.width.height.mas_equalTo(32/2);
        make.left.equalTo(self.userIDLabel.mas_right).offset(8);
        make.centerY.equalTo(self.userIDLabel);
    }];
    
    [self addSubview:self.hostTipView];
    [self.hostTipView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(44, 20));
        make.left.equalTo(self.userIDLabel);
        make.top.equalTo(self.userIDLabel.mas_bottom).offset(4);
    }];
    
    [self addSubview:self.avatarSpeakView];
    [self.avatarSpeakView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(self.avatarView);
    }];
}



#pragma mark - getter

- (BaseButton *)enableAudioBtn {
    if (!_enableAudioBtn) {
        _enableAudioBtn = [[BaseButton alloc] init];
        [_enableAudioBtn addTarget:self action:@selector(enableAudioBtnAction:) forControlEvents:UIControlEventTouchUpInside];
        [_enableAudioBtn bingImage:[UIImage imageNamed:@"meeting_par_mic"] status:ButtonStatusNone];
        [_enableAudioBtn bingImage:[UIImage imageNamed:@"meeting_par_mic_s"] status:ButtonStatusActive];
        [_enableAudioBtn bingImage:[UIImage imageNamed:@"meeting_par_mic_i"] status:ButtonStatusIng];
        _enableAudioBtn.userInteractionEnabled = NO;
    }
    return _enableAudioBtn;
}

- (BaseButton *)enableVideoBtn {
    if (!_enableVideoBtn) {
        _enableVideoBtn = [[BaseButton alloc] init];
        [_enableVideoBtn addTarget:self action:@selector(enableVideoBtnAction:) forControlEvents:UIControlEventTouchUpInside];
        [_enableVideoBtn bingImage:[UIImage imageNamed:@"meeting_par_camera"] status:ButtonStatusNone];
        [_enableVideoBtn bingImage:[UIImage imageNamed:@"meeting_par_camera_s"] status:ButtonStatusActive];
        _enableVideoBtn.userInteractionEnabled = NO;
    }
    return _enableVideoBtn;
}

- (MeetingAvatarCompoments *)avatarView {
    if (!_avatarView) {
        _avatarView = [[MeetingAvatarCompoments alloc] init];
        _avatarView.fontSize = 20;
        _avatarView.layer.masksToBounds = YES;
        _avatarView.layer.cornerRadius = 20;
    }
    return _avatarView;
}

- (UIView *)lineView {
    if (!_lineView) {
        _lineView = [[UIView alloc] init];
        _lineView.backgroundColor = [UIColor colorFromHexString:@"#4E5969"];
    }
    return _lineView;
}

- (UILabel *)userIDLabel {
    if (!_userIDLabel) {
        _userIDLabel = [[UILabel alloc] init];
        _userIDLabel.textColor = [UIColor colorFromHexString:@"#E5E6EB"];
        _userIDLabel.font = [UIFont systemFontOfSize:32/2 weight:UIFontWeightRegular];
    }
    return _userIDLabel;
}

- (UILabel *)hostTipView {
    if (!_hostTipView) {
        _hostTipView = [[UILabel alloc] init];
        _hostTipView.textAlignment = NSTextAlignmentCenter;
        _hostTipView.textColor = [UIColor colorFromHexString:@"#4080FF"];
        _hostTipView.text = @"主持人";
        _hostTipView.backgroundColor = [UIColor colorFromHexString:@"#272E3B"];
        _hostTipView.layer.masksToBounds = YES;
        _hostTipView.layer.cornerRadius = 2;
        _hostTipView.font = [UIFont systemFontOfSize:12];
    }
    return _hostTipView;
}

- (UIImageView *)screenImageView {
    if (!_screenImageView) {
        _screenImageView = [[UIImageView alloc] init];
        _screenImageView.image = [UIImage imageNamed:@"meeting_par_screen"];
    }
    return _screenImageView;
}

- (UIView *)avatarSpeakView {
    if (!_avatarSpeakView) {
        _avatarSpeakView = [[UIView alloc] init];
        _avatarSpeakView.layer.masksToBounds = YES;
        _avatarSpeakView.layer.borderWidth = 2;
        _avatarSpeakView.layer.cornerRadius = 20;
        _avatarSpeakView.layer.borderColor = [UIColor colorFromHexString:@"#4080FF"].CGColor;
        _avatarSpeakView.hidden = YES;
    }
    return _avatarSpeakView;
}


@end
