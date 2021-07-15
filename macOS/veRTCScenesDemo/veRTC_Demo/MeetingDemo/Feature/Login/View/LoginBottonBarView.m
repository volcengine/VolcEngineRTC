//
//  LoginBottonBarView.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/8.
//

#import "LoginBottonBarView.h"
#import "NSLabel.h"
#import "MeetingTextFileComponents.h"
#import "LoginBottonErrorView.h"
#import "SystemAuthority.h"

@interface LoginBottonBarView () <MeetingTextFileComponentsDelegate>

@property (nonatomic, strong) NSLabel *messageLabel;
@property (nonatomic, strong) MeetingTextFileComponents *roomIDTextFile;
@property (nonatomic, strong) MeetingTextFileComponents *userNameTextFile;
@property (nonatomic, assign) bool isRoomIllegal;
@property (nonatomic, assign) bool isUserIllegal;
@property (nonatomic, strong) TrackButton *startButton;

@property (nonatomic, strong) TrackButton *micButton;
@property (nonatomic, strong) TrackButton *videoButton;
@property (nonatomic, strong) TrackButton *setButton;

@end

@implementation LoginBottonBarView

- (instancetype)init {
    self = [super init];
    if (self) {
        self.isRoomIllegal = NO;
        self.isUserIllegal = NO;
        [self updateLayoutViewFrame];
        
        self.startButton.currentStatus = TrackButtonStatusDisabled;
        
        [self updateSystemAuthority];
        
        __weak __typeof(self) wself = self;
        self.roomIDTextFile.keyboardClickTab = ^{
            [wself.userNameTextFile textBecomeFirstResponder];
        };
        self.userNameTextFile.keyboardClickEnter = ^{
            [wself startButtonAction];
        };
    }
    return self;
}

- (void)updateLayoutViewFrame {
    [self addSubview:self.messageLabel];
    [self.messageLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.mas_equalTo(40);
        make.centerY.equalTo(self);
    }];
    
    [self addSubview:self.roomIDTextFile];
    [self.roomIDTextFile mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(160, 32));
        make.centerY.equalTo(self);
        make.left.equalTo(self.messageLabel.mas_right).offset(24);
    }];
    
    [self addSubview:self.userNameTextFile];
    [self.userNameTextFile mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(160, 32));
        make.centerY.equalTo(self);
        make.left.equalTo(self.roomIDTextFile.mas_right).offset(16);
    }];
    
    [self addSubview:self.startButton];
    [self.startButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(88, 32));
        make.centerY.equalTo(self);
        make.left.equalTo(self.userNameTextFile.mas_right).offset(16);
    }];
    
    [self addSubview:self.micButton];
    [self.micButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(32, 32));
        make.centerY.equalTo(self);
        make.left.equalTo(self.startButton.mas_right).offset(32);
    }];
    
    [self addSubview:self.videoButton];
    [self.videoButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(32, 32));
        make.centerY.equalTo(self);
        make.left.equalTo(self.micButton.mas_right).offset(16);
    }];
    
    [self addSubview:self.setButton];
    [self.setButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(32, 32));
        make.centerY.equalTo(self);
        make.left.equalTo(self.videoButton.mas_right).offset(16);
    }];
}

#pragma mark - Publish Action

- (void)updateUserNameTextFile:(NSString *)text {
    self.userNameTextFile.text = text;   
}

- (NSString *)roomId {
    return self.roomIDTextFile.text;
}

- (NSString *)userName {
    return self.userNameTextFile.text;
}

- (BOOL)isEnableVideo {
    return !self.videoButton.isClose;
}

- (BOOL)isEnableAudio {
    return !self.micButton.isClose;
}

- (void)updateBottomBar:(LoginModel *)loginModel {
    self.micButton.isClose = !loginModel.isEnableAudio;
    
    self.videoButton.isClose = !loginModel.isEnableVideo;
}

#pragma mark - Touch Action

- (void)setButtonAction {
    if ([self.delegate respondsToSelector:@selector(loginBottonBarView:didSelectItemsAtStatus:clickButton:)]) {
        [self.delegate loginBottonBarView:self didSelectItemsAtStatus:ButtonStatusSet clickButton:self.setButton];
    }
}

- (void)videoButtonAction {
    [SystemAuthority authorCamera:^(BOOL granted) {
        if (granted) {
            if ([self.delegate respondsToSelector:@selector(loginBottonBarView:didSelectItemsAtStatus:clickButton:)]) {
                [self.delegate loginBottonBarView:self didSelectItemsAtStatus:ButtonStatusVideo clickButton:self.videoButton];
            }
        } else {
            [[MeetingAlertCompoments share] showWithTitle:@"摄像头权限已关闭，请至设备设置页开启。" clickBlock:^(BOOL result) {
                if (result) {
                    [[NSWorkspace sharedWorkspace] openURL:[NSURL URLWithString:@"x-apple.systempreferences:com.apple.preference.security?Privacy"]];
                }
            }];
        }
    }];
}

- (void)micButtonAction {
    [SystemAuthority authorMicphone:^(BOOL granted) {
        if (granted) {
            if ([self.delegate respondsToSelector:@selector(loginBottonBarView:didSelectItemsAtStatus:clickButton:)]) {
                [self.delegate loginBottonBarView:self didSelectItemsAtStatus:ButtonStatusMic clickButton:self.micButton];
            }
        } else {
            [[MeetingAlertCompoments share] showWithTitle:@"麦克风权限已关闭，请至设备设置页开启。" clickBlock:^(BOOL result) {
                if (result) {
                    [[NSWorkspace sharedWorkspace] openURL:[NSURL URLWithString:@"x-apple.systempreferences:com.apple.preference.security?Privacy"]];
                }
            }];
        }
    }];
    
}

- (void)startButtonAction {
    if ([self.delegate respondsToSelector:@selector(loginBottonBarView:didSelectItemsAtStatus:clickButton:)]) {
        [self.delegate loginBottonBarView:self didSelectItemsAtStatus:ButtonStatusStart clickButton:self.startButton];
    }
}

#pragma mark - MeetingTextFileComponentsDelegate

- (void)meetingTextFileComponents:(MeetingTextFileComponents *)meetingTextFileComponents checkInputIllegal:(BOOL)isIllegal {
    if (meetingTextFileComponents == self.roomIDTextFile) {
        self.isRoomIllegal = isIllegal;
        [self updateInputState:meetingTextFileComponents isIllegal:isIllegal];
    } else if (meetingTextFileComponents == self.userNameTextFile) {
        self.isUserIllegal = isIllegal;
        [self updateInputState:meetingTextFileComponents isIllegal:isIllegal];
    }
    BOOL isEmpty = (self.roomIDTextFile.text.length <= 0) || (self.userNameTextFile.text.length <= 0);
    BOOL isAllisIllegal = self.isUserIllegal || self.isRoomIllegal;
    [self updateInputErrorView:isAllisIllegal];
    
    self.startButton.currentStatus = isAllisIllegal ? TrackButtonStatusDisabled : TrackButtonStatusDefault;
    if (isEmpty) {
        self.startButton.currentStatus = TrackButtonStatusDisabled;
    }
}

#pragma mark - Private Action

- (void)updateInputState:(MeetingTextFileComponents *)fileComponents isIllegal:(BOOL)isIllegal {
    if (isIllegal) {
        [fileComponents setBackgroundColorWithHexString:@"#FFECE8"];
        fileComponents.cancelButton.hidden = NO;
    } else {
        fileComponents.cancelButton.hidden = YES;
        [fileComponents setBackgroundColorWithHexString:@"#F2F3F5"];
    }
}

- (void)updateInputErrorView:(BOOL)isIllegal {
    if (isIllegal) {
        LoginBottonErrorView *errorView = [LoginBottonErrorView shareLoginBottonErrorView];
        errorView.title = @"非法输入，输入规则如下：";
        errorView.message = @"1. 26个大写字母 A ~ Z \n2. 26个小写字母 a ~ z \n3. 10个数字 0 ~ 9 \n4. 下划线\"_\", at符\"@\", 减号\"-\"";
        [errorView show:self.superview];
    } else {
        [[LoginBottonErrorView shareLoginBottonErrorView] dismiss];
    }
}

- (void)updateSystemAuthority {
    [SystemAuthority authorCamera:^(BOOL granted) {
        if (!granted) {
            self.videoButton.isClose = YES;
        }
    }];
    
    [SystemAuthority authorMicphone:^(BOOL granted) {
        if (!granted) {
            self.micButton.isClose = YES;
        }
    }];
}

#pragma mark - getter

- (NSLabel *)messageLabel {
    if (!_messageLabel) {
        _messageLabel = [[NSLabel alloc] init];
        _messageLabel.text = @"登录";
        _messageLabel.textColor = [NSColor blackColor];
        _messageLabel.font = [NSFont systemFontOfSize:16 weight:NSFontWeightMedium];
    }
    return _messageLabel;
}

- (MeetingTextFileComponents *)roomIDTextFile {
    if (!_roomIDTextFile) {
        _roomIDTextFile = [[MeetingTextFileComponents alloc] init];
        _roomIDTextFile.placeholderString = @"房间ID";
        _roomIDTextFile.maxLength = 18;
        _roomIDTextFile.isCheckNumberEng = YES;
        _roomIDTextFile.wantsLayer = YES;
        _roomIDTextFile.layer.cornerRadius = 2;
        _roomIDTextFile.layer.masksToBounds = YES;
        _roomIDTextFile.delegate = self;
    }
    return _roomIDTextFile;
}

- (MeetingTextFileComponents *)userNameTextFile {
    if (!_userNameTextFile) {
        _userNameTextFile = [[MeetingTextFileComponents alloc] init];
        _userNameTextFile.placeholderString = @"用户昵称";
        _userNameTextFile.maxLength = 18;
        _userNameTextFile.isCheckAll = YES;
        _userNameTextFile.wantsLayer = YES;
        _userNameTextFile.layer.cornerRadius = 2;
        _userNameTextFile.layer.masksToBounds = YES;
        _userNameTextFile.delegate = self;
    }
    return _userNameTextFile;
}

- (TrackButton *)startButton {
    if (!_startButton) {
        _startButton = [[TrackButton alloc] init];
        _startButton.wantsLayer = YES;
        _startButton.layer.cornerRadius = 2;
        _startButton.layer.masksToBounds = YES;
        
        [_startButton bingBackColorWithStatus:TrackButtonStatusDefault color:[NSColor colorFromHexString:@"#165DFF"]];
        [_startButton bingBackColorWithStatus:TrackButtonStatusHover color:[NSColor colorFromHexString:@"#4080FF"]];
        [_startButton bingBackColorWithStatus:TrackButtonStatusActive color:[NSColor colorFromHexString:@"#0E42D2"]];
        [_startButton bingBackColorWithStatus:TrackButtonStatusDisabled color:[NSColor colorFromHexString:@"#94BFFF"]];
        
        [_startButton setTitleColor:@"#FFFFFF" title:@"进入房间"];
        [_startButton setTarget:self];
        [_startButton setAction:@selector(startButtonAction)];
    }
    return _startButton;
}

- (TrackButton *)micButton {
    if (!_micButton) {
        _micButton = [[TrackButton alloc] init];
        [_micButton setTarget:self];
        [_micButton setAction:@selector(micButtonAction)];
        
        [_micButton bingImageWithType:NO image:[NSImage imageNamed:@"metting_login_audio"]];
        [_micButton bingImageWithType:YES image:[NSImage imageNamed:@"metting_login_audio_close"]];
        
        [_micButton bingBackColorWithStatus:TrackButtonStatusDefault color:[NSColor colorFromHexString:@"#F2F3F5"]];
        [_micButton bingBackColorWithStatus:TrackButtonStatusHover color:[NSColor colorFromHexString:@"#E5E6EB"]];
        [_micButton bingBackColorWithStatus:TrackButtonStatusActive color:[NSColor colorFromHexString:@"#C9CDD4"]];
        
        _micButton.wantsLayer = YES;
        _micButton.layer.cornerRadius = 16;
        _micButton.layer.masksToBounds = YES;
    }
    return _micButton;
}

- (TrackButton *)videoButton {
    if (!_videoButton) {
        _videoButton = [[TrackButton alloc] init];
        [_videoButton setTarget:self];
        [_videoButton setAction:@selector(videoButtonAction)];
        
        [_videoButton bingImageWithType:NO image:[NSImage imageNamed:@"metting_login_video"]];
        [_videoButton bingImageWithType:YES image:[NSImage imageNamed:@"metting_login_video_close"]];
        
        [_videoButton bingBackColorWithStatus:TrackButtonStatusDefault color:[NSColor colorFromHexString:@"#F2F3F5"]];
        [_videoButton bingBackColorWithStatus:TrackButtonStatusHover color:[NSColor colorFromHexString:@"#E5E6EB"]];
        [_videoButton bingBackColorWithStatus:TrackButtonStatusActive color:[NSColor colorFromHexString:@"#C9CDD4"]];
        
        _videoButton.wantsLayer = YES;
        _videoButton.layer.cornerRadius = 16;
        _videoButton.layer.masksToBounds = YES;
    }
    return _videoButton;
}

- (TrackButton *)setButton {
    if (!_setButton) {
        _setButton = [[TrackButton alloc] init];
        [_setButton setImage:[NSImage imageNamed:@"metting_login_set"]];
        [_setButton setTarget:self];
        [_setButton setAction:@selector(setButtonAction)];
        
        [_setButton bingBackColorWithStatus:TrackButtonStatusDefault color:[NSColor colorFromHexString:@"#F2F3F5"]];
        [_setButton bingBackColorWithStatus:TrackButtonStatusHover color:[NSColor colorFromHexString:@"#E5E6EB"]];
        [_setButton bingBackColorWithStatus:TrackButtonStatusActive color:[NSColor colorFromHexString:@"#C9CDD4"]];

        _setButton.wantsLayer = YES;
        _setButton.layer.cornerRadius = 16;
        _setButton.layer.masksToBounds = YES;
    }
    return _setButton;
}

@end
