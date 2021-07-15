//
//  MeetingEndView.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/10.
//

#import "MeetingEndView.h"

@interface MeetingEndView ()

@property (nonatomic, strong) NSImageView *waringImageView;
@property (nonatomic, strong) NSLabel *titleLabel;
@property (nonatomic, strong) NSButton *endButton;
@property (nonatomic, strong) NSButton *leaveButton;
@property (nonatomic, strong) NSButton *cancelButton;

@end

@implementation MeetingEndView

- (instancetype)init {
    self = [super init];
    if (self) {
        [self addSubview:self.titleLabel];
        [self.titleLabel mas_makeConstraints:^(MASConstraintMaker *make) {
            make.centerX.equalTo(self).offset(14);
            make.top.mas_equalTo(32);
        }];
        
        [self addSubview:self.waringImageView];
        [self.waringImageView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.right.equalTo(self.titleLabel.mas_left).offset(-8);
            make.centerY.equalTo(self.titleLabel);
        }];
        
        [self addSubview:self.endButton];
        [self addSubview:self.leaveButton];
        [self addSubview:self.cancelButton];
    }
    return self;
}

- (void)endMeetingButtonAction {
    if (self.clickButtonBlock) {
        self.clickButtonBlock(MeetingButtonStatusEnd);
    }
}

- (void)leaveMeetingButtonAction:(NSButton *)sender {
    if (sender.tag == ButtonColorTypeDisable) {
        return;
    }
    if (self.clickButtonBlock) {
        self.clickButtonBlock(MeetingButtonStatusLeave);
    }
}

- (void)cancelMeetingButtonAction {
    if (self.clickButtonBlock) {
        self.clickButtonBlock(MeetingButtonStatusCancel);
    }
}

- (void)setMeetingEndStatus:(MeetingEndStatus)meetingEndStatus {
    _meetingEndStatus = meetingEndStatus;
    
    NSMutableArray *viewLists = [[NSMutableArray alloc] init];
    if (meetingEndStatus == MeetingEndStatusHost) {
        [self updateButtonColorWithType:ButtonColorTypeRemind button:self.endButton];
        [self updateButtonColorWithType:ButtonColorTypeDisable button:self.leaveButton];
        [self updateButtonColorWithType:ButtonColorTypeNone button:self.cancelButton];
        [viewLists addObject:self.endButton];
        [viewLists addObject:self.leaveButton];
        [viewLists addObject:self.cancelButton];
        self.titleLabel.text = @"请移交主持人给指定参会者，方能离开会议";
    } else {
        [self updateButtonColorWithType:ButtonColorTypeRemind button:self.leaveButton];
        [self updateButtonColorWithType:ButtonColorTypeNone button:self.cancelButton];
        [viewLists addObject:self.leaveButton];
        [viewLists addObject:self.cancelButton];
        self.titleLabel.text = @"请再次确认是否要离开会议？";
    }
    
    [viewLists mas_distributeViewsAlongAxis:MASAxisTypeVertical withFixedItemLength:36 leadSpacing:78 tailSpacing:32];
    [viewLists mas_updateConstraints:^(MASConstraintMaker *make) {
        make.width.mas_equalTo(240);
        make.centerX.equalTo(self);
    }];
    
    CGFloat topSapce = 24;
    CGFloat bottomSapce = 32;
    CGFloat allButtonHeight = (36 * viewLists.count) + (20 * (viewLists.count - 1));
    [self mas_updateConstraints:^(MASConstraintMaker *make) {
        make.bottom.equalTo(self.titleLabel).offset(topSapce + allButtonHeight + bottomSapce);
    }];
}

#pragma mark - Private Action

- (void)updateButtonColorWithType:(ButtonColorType)type button:(NSButton *)button {
    button.tag = type;
    if (type == ButtonColorTypeRemind) {
        [button setTitleColor:@"#FFFFFF" title:button.title];
        [button setBackgroundColorWithHexString:@"#F53F3F"];
    } else if (type == ButtonColorTypeDisable) {
        [button setTitleColor:@"#C9CDD4" title:button.title];
        [button setBackgroundColorWithHexString:@"#F7F8FA"];
    } else {
        [button setTitleColor:@"#1D2129" title:button.title];
        [button setBackgroundColorWithHexString:@"#F2F3F5"];
    }
}

#pragma mark - getter

- (NSImageView *)waringImageView {
    if (!_waringImageView) {
        _waringImageView = [[NSImageView alloc] init];
        [_waringImageView setBackgroundColor:[NSColor clearColor]];
        _waringImageView.image = [NSImage imageNamed:@"meeting_end_waring"];
    }
    return _waringImageView;
}

- (NSLabel *)titleLabel {
    if (!_titleLabel) {
        _titleLabel = [[NSLabel alloc] init];
        _titleLabel.textColor = [NSColor colorFromHexString:@"#1D2129"];
        _titleLabel.font = [NSFont systemFontOfSize:14 weight:NSFontWeightMedium];
    }
    return _titleLabel;
}

- (NSButton *)endButton {
    if (!_endButton) {
        _endButton = [[NSButton alloc] init];
        _endButton.title = @"结束全部会议";
        _endButton.wantsLayer = YES;
        _endButton.layer.cornerRadius = 2;
        _endButton.layer.masksToBounds = YES;
        [_endButton setTarget:self];
        [_endButton setAction:@selector(endMeetingButtonAction)];
    }
    return _endButton;
}

- (NSButton *)leaveButton {
    if (!_leaveButton) {
        _leaveButton = [[NSButton alloc] init];
        [_leaveButton setTarget:self];
        [_leaveButton setAction:@selector(leaveMeetingButtonAction:)];
        _leaveButton.title = @"离开会议";
        _leaveButton.wantsLayer = YES;
        _leaveButton.layer.cornerRadius = 2;
        _leaveButton.layer.masksToBounds = YES;
    }
    return _leaveButton;
}

- (NSButton *)cancelButton {
    if (!_cancelButton) {
        _cancelButton = [[NSButton alloc] init];
        [_cancelButton setTarget:self];
        [_cancelButton setAction:@selector(cancelMeetingButtonAction)];
        _cancelButton.title = @"取消";
        _cancelButton.wantsLayer = YES;
        _cancelButton.layer.cornerRadius = 2;
        _cancelButton.layer.masksToBounds = YES;
    }
    return _cancelButton;
}

@end
