
//
//  NavBarRoomView.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/11.
//

#import "NavBarRoomView.h"
#import "MeetingAvatarCompoments.h"
#import "NavigationBarViewController.h"
#import <Quartz/Quartz.h>

@interface NavBarRoomView ()

@property (nonatomic, strong) NSLabel *roomIDLabel;
@property (nonatomic, strong) NSLabel *timeLabel;
@property (nonatomic, strong) NSLabel *nameLabel;
@property (nonatomic, strong) NSView *lineView;
@property (nonatomic, strong) MeetingAvatarCompoments *avatarView;

@property (nonatomic, strong) NSImageView *expandImageView;
@property (nonatomic, strong) NSButton *expandButton;

@property (nonatomic, strong) NSImageView *recordIconImageView;
@property (nonatomic, strong) NSLabel *recordILabel;

@property (nonatomic, strong) GCDTimer *timer;
@property (nonatomic, assign) NSInteger secondValue;

@property (nonatomic, assign) BOOL currentExpand;

@end

@implementation NavBarRoomView

- (instancetype)init {
    self = [super init];
    if (self) {
        [self addSubviewAndConstraints];
        self.currentExpand = YES;
        
        __weak __typeof(self) wself = self;
        [self.timer startTimerWithSpace:1 block:^(BOOL result) {
            [wself timerMethod];
        }];
        [self.timer suspend];
    }
    return self;
}

- (void)setMeetingTime:(NSInteger)meetingTime {
    self.secondValue = meetingTime;
    [self.timer resume];
}

#pragma mark - Action Method

- (void)expandButtonAction {
    self.currentExpand = !self.currentExpand;
    
    if (!self.currentExpand) {
        self.expandImageView.image = [NSImage imageNamed:@"meeting_nav_arrow_down"];
    } else {
        self.expandImageView.image = [NSImage imageNamed:@"meeting_nav_arrow"];
    }
    [self.expandButton setTitleColor:@"#86909C" title:self.currentExpand ? @"隐藏列表" : @"展开列表"];
    
    [[NSNotificationCenter defaultCenter] postNotificationName:NoticeClickRoomExpandListName object:@(self.currentExpand)];
}

#pragma mark - Publish Action

- (void)setLoginModel:(LoginModel *)loginModel {
    _loginModel = loginModel;
    
    self.roomIDLabel.text = [NSString stringWithFormat:@"房间ID：%@",loginModel.roomId];
    self.nameLabel.text = [LocalUserCompoments userModel].name;
    self.avatarView.text = [LocalUserCompoments userModel].name;
}

- (void)setIsExpandList:(BOOL)isExpandList {
    _isExpandList = isExpandList;
    
    self.expandImageView.hidden = !isExpandList;
    self.expandButton.hidden = !isExpandList;
}

- (void)setIsRecord:(BOOL)isRecord {
    _isRecord = isRecord;
    
    self.recordIconImageView.hidden = !isRecord;
    self.recordILabel.hidden = !isRecord;
}

#pragma mark - Private Action

- (void)timerMethod {
    NSInteger minute = self.secondValue / 60;
    NSInteger second = self.secondValue - (minute * 60);
    NSString *minuteStr = (minute < 10) ? [NSString stringWithFormat:@"0%ld", minute] : [NSString stringWithFormat:@"%ld", (long)minute];
    NSString *secondStr = (second < 10) ? [NSString stringWithFormat:@"0%ld", second] : [NSString stringWithFormat:@"%ld", (long)second];
    self.timeLabel.text = [NSString stringWithFormat:@"%@:%@", minuteStr, secondStr];
    self.secondValue++;
}

- (void)addSubviewAndConstraints {
    [self addSubview:self.lineView];
    [self.lineView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(1, 12));
        make.center.equalTo(self);
    }];
    
    [self addSubview:self.roomIDLabel];
    [self.roomIDLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.right.equalTo(self.lineView.mas_left).offset(-8);
        make.centerY.equalTo(self);
    }];
    
    [self addSubview:self.timeLabel];
    [self.timeLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.equalTo(self.lineView.mas_right).offset(8);
        make.centerY.equalTo(self);
    }];
    
    [self addSubview:self.nameLabel];
    [self.nameLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.right.equalTo(self).offset(-24);
        make.centerY.equalTo(self);
    }];
    
    [self addSubview:self.avatarView];
    [self.avatarView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(28, 28));
        make.right.equalTo(self.nameLabel.mas_left).offset(-8);
        make.centerY.equalTo(self);
    }];
    
    [self addSubview:self.expandImageView];
    [self.expandImageView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(12, 12));
        make.left.equalTo(self.timeLabel.mas_right).offset(24);
        make.centerY.equalTo(self);
    }];
    
    [self addSubview:self.expandButton];
    [self.expandButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(52, 20));
        make.left.equalTo(self.expandImageView.mas_right).offset(4);
        make.centerY.equalTo(self);
    }];

    [self addSubview:self.recordIconImageView];
    [self.recordIconImageView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(8, 8));
        make.left.equalTo(self.expandButton.mas_right).offset(24);
        make.centerY.equalTo(self);
    }];
    
    [self addSubview:self.recordILabel];
    [self.recordILabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.equalTo(self.recordIconImageView.mas_right).offset(8);
        make.centerY.equalTo(self);
    }];
}

#pragma mark - getter

- (NSLabel *)roomIDLabel {
    if (!_roomIDLabel) {
        _roomIDLabel = [[NSLabel alloc] init];
        _roomIDLabel.textColor = [NSColor colorFromHexString:@"#FFFFFF"];
        _roomIDLabel.font = [NSFont systemFontOfSize:12 weight:NSFontWeightRegular];
    }
    return _roomIDLabel;
}

- (NSLabel *)timeLabel {
    if (!_timeLabel) {
        _timeLabel = [[NSLabel alloc] init];
        _timeLabel.textColor = [NSColor colorFromHexString:@"#FFFFFF"];
        _timeLabel.font = [NSFont systemFontOfSize:12 weight:NSFontWeightRegular];
    }
    return _timeLabel;
}

- (NSLabel *)nameLabel {
    if (!_nameLabel) {
        _nameLabel = [[NSLabel alloc] init];
        _nameLabel.textColor = [NSColor colorFromHexString:@"#FFFFFF"];
        _nameLabel.font = [NSFont systemFontOfSize:12 weight:NSFontWeightRegular];
    }
    return _nameLabel;
}

- (NSView *)lineView {
    if (!_lineView) {
        _lineView = [[NSView alloc] init];
        [_lineView setBackgroundColorWithHexString:@"#4E5969"];
    }
    return _lineView;
}

- (MeetingAvatarCompoments *)avatarView {
    if (!_avatarView) {
        _avatarView = [[MeetingAvatarCompoments alloc] init];
        _avatarView.fontSize = 14;
        _avatarView.wantsLayer = YES;
        _avatarView.layer.masksToBounds = YES;
        _avatarView.layer.cornerRadius = 14;
    }
    return _avatarView;
}

- (NSImageView *)expandImageView {
    if (!_expandImageView) {
        _expandImageView = [[NSImageView alloc] init];
        _expandImageView.image = [NSImage imageNamed:@"meeting_nav_arrow"];
        _expandImageView.hidden = YES;
    }
    return _expandImageView;
}

- (NSButton *)expandButton {
    if (!_expandButton) {
        _expandButton = [[NSButton alloc] init];
        [_expandButton setBackgroundColor:[NSColor clearColor]];
        [_expandButton setTitleColor:@"#86909C" title:@"隐藏列表"];
        [_expandButton setTarget:self];
        [_expandButton setAction:@selector(expandButtonAction)];
        _expandButton.font = [NSFont systemFontOfSize:12 weight:NSFontWeightRegular];
        _expandButton.hidden = YES;
    }
    return _expandButton;
}

- (NSImageView *)recordIconImageView {
    if (!_recordIconImageView) {
        _recordIconImageView = [[NSImageView alloc] init];
        [_recordIconImageView setBackgroundColorWithHexString:@"#F53F3F"];
        
        _recordIconImageView.wantsLayer = YES;
        _recordIconImageView.layer.masksToBounds = YES;
        _recordIconImageView.layer.cornerRadius = 4;
        _recordIconImageView.hidden = YES;
    }
    return _recordIconImageView;
}

- (NSLabel *)recordILabel {
    if (!_recordILabel) {
        _recordILabel = [[NSLabel alloc] init];
        _recordILabel.textColor = [NSColor colorFromHexString:@"#FFFFFF"];
        _recordILabel.font = [NSFont systemFontOfSize:12 weight:NSFontWeightRegular];
        _recordILabel.text = @"REC";
        _recordILabel.hidden = YES;
    }
    return _recordILabel;
}

- (GCDTimer *)timer {
    if (!_timer) {
        _timer = [[GCDTimer alloc] init];
    }
    return _timer;
}

- (void)dealloc {
    NSLog(@"[dealloc]%@",self.className);
}
@end

