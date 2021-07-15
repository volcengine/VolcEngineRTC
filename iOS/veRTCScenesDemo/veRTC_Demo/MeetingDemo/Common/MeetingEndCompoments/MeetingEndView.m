//
//  MeetingEndView.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/10.
//

#import "MeetingEndView.h"

@interface MeetingEndView ()

@property (nonatomic, strong) UILabel *titleLabel;
@property (nonatomic, strong) UIButton *endButton;
@property (nonatomic, strong) UIButton *leaveButton;
@property (nonatomic, strong) UIButton *cancelButton;

@end

@implementation MeetingEndView

- (instancetype)init {
    self = [super init];
    if (self) {
        [self addSubview:self.titleLabel];
        [self.titleLabel mas_remakeConstraints:^(MASConstraintMaker *make) {
            make.centerX.equalTo(self);
            make.top.mas_equalTo(20);
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

- (void)leaveMeetingButtonAction {
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
    
    NSInteger buttonTop = 0;
    NSInteger titleTop = 0;
    NSInteger contentHeight = 0;
    NSMutableArray *viewLists = [[NSMutableArray alloc] init];
    if (meetingEndStatus == MeetingEndStatusHost) {
        [self updateButtonColorWithType:ButtonColorTypeRemind button:self.endButton];
        [self updateButtonColorWithType:ButtonColorTypeDisable button:self.leaveButton];
        [self updateButtonColorWithType:ButtonColorTypeNone button:self.cancelButton];
        [viewLists addObject:self.endButton];
        [viewLists addObject:self.leaveButton];
        [viewLists addObject:self.cancelButton];
        self.titleLabel.text = @"请移交主持人给指定参会者，方 \n 能离开会议";
        titleTop = 20;
        buttonTop = 192 / 2;
        contentHeight = 596 /2;
    } else {
        [self updateButtonColorWithType:ButtonColorTypeRemind button:self.leaveButton];
        [self updateButtonColorWithType:ButtonColorTypeNone button:self.cancelButton];
        [viewLists addObject:self.leaveButton];
        [viewLists addObject:self.cancelButton];
        self.titleLabel.text = @"请再次确认是否要离开会议？";
        titleTop = 30;
        buttonTop = 176 / 2;
        contentHeight = 452 /2;
    }
    [self.titleLabel mas_updateConstraints:^(MASConstraintMaker *make) {
        make.top.mas_equalTo(titleTop);
    }];
    
    [viewLists mas_distributeViewsAlongAxis:MASAxisTypeVertical withFixedSpacing:20 leadSpacing:buttonTop tailSpacing:30];
    [viewLists mas_updateConstraints:^(MASConstraintMaker *make) {
        make.width.mas_equalTo(510/2);
        make.centerX.equalTo(self);
    }];
    
    [self mas_updateConstraints:^(MASConstraintMaker *make) {
        make.height.mas_equalTo(contentHeight);
    }];
}

#pragma mark - Private Action

- (void)updateButtonColorWithType:(ButtonColorType)type button:(UIButton *)button {
    button.enabled = YES;
    if (type == ButtonColorTypeRemind) {
        [button setTitleColor:[UIColor colorFromHexString:@"#FFFFFF"] forState:UIControlStateNormal];
        [button setBackgroundColor:[UIColor colorFromHexString:@"#F53F3F"]];
    } else if (type == ButtonColorTypeDisable) {
        [button setTitleColor:[UIColor colorFromRGBHexString:@"#FFFFFF" andAlpha:(0.05 * 255)] forState:UIControlStateNormal];
        [button setBackgroundColor:[UIColor colorFromRGBHexString:@"FFFFFF" andAlpha:(0.05 * 255)]];
        button.enabled = NO;
    } else {
        [button setTitleColor:[UIColor colorFromHexString:@"#FFFFFF"] forState:UIControlStateNormal];
        [button setBackgroundColor:[UIColor colorFromRGBHexString:@"#FFFFFF" andAlpha:(0.1 * 255)]];
    }
}

#pragma mark - getter

- (UILabel *)titleLabel {
    if (!_titleLabel) {
        _titleLabel = [[UILabel alloc] init];
        _titleLabel.textColor = [UIColor colorFromHexString:@"#FFFFFF"];
        _titleLabel.font = [UIFont systemFontOfSize:32/2 weight:UIFontWeightMedium];
        _titleLabel.numberOfLines = 0;
        _titleLabel.textAlignment = NSTextAlignmentCenter;
    }
    return _titleLabel;
}

- (UIButton *)endButton {
    if (!_endButton) {
        _endButton = [[UIButton alloc] init];
        [_endButton setTitle:@"结束全部会议" forState:UIControlStateNormal];
        _endButton.layer.cornerRadius = 44/2;
        _endButton.layer.masksToBounds = YES;
        [_endButton addTarget:self action:@selector(endMeetingButtonAction) forControlEvents:UIControlEventTouchUpInside];
    }
    return _endButton;
}

- (UIButton *)leaveButton {
    if (!_leaveButton) {
        _leaveButton = [[UIButton alloc] init];
        [_leaveButton addTarget:self action:@selector(leaveMeetingButtonAction) forControlEvents:UIControlEventTouchUpInside];
        [_leaveButton setTitle:@"离开会议" forState:UIControlStateNormal];
        _leaveButton.titleLabel.font = [UIFont systemFontOfSize:32/2];
        _leaveButton.layer.cornerRadius = 44/2;
        _leaveButton.layer.masksToBounds = YES;
    }
    return _leaveButton;
}

- (UIButton *)cancelButton {
    if (!_cancelButton) {
        _cancelButton = [[UIButton alloc] init];
        [_cancelButton addTarget:self action:@selector(cancelMeetingButtonAction) forControlEvents:UIControlEventTouchUpInside];
        [_cancelButton setTitle:@"取消" forState:UIControlStateNormal];
        _cancelButton.layer.cornerRadius = 44/2;
        _cancelButton.titleLabel.font = [UIFont systemFontOfSize:32/2];
        _cancelButton.layer.masksToBounds = YES;
    }
    return _cancelButton;
}

@end
