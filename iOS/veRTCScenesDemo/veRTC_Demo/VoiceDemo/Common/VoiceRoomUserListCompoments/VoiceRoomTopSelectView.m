//
//  VoiceRoomTopSelectView.m
//  veRTC_Demo
//
//  Created by  on 2021/5/24.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import "VoiceRoomTopSelectView.h"

@interface VoiceRoomTopSelectView ()

@property (nonatomic, strong) BaseButton *raiseButton;
@property (nonatomic, strong) BaseButton *audienceButton;
@property (nonatomic, strong) BaseButton *cancelButton;
@property (nonatomic, strong) UIView *selectLineView;
@property (nonatomic, strong) UIView *lineView;
@property (nonatomic, strong) UILabel *titleLabel;

@end

@implementation VoiceRoomTopSelectView

- (instancetype)init
{
    self = [super init];
    if (self) {
        self.backgroundColor = [UIColor colorFromHexString:@"#272E3B"];
        
        [self addSubview:self.raiseButton];
        [self addSubview:self.audienceButton];
        [self addSubview:self.selectLineView];
        [self addSubview:self.lineView];
        [self addSubview:self.cancelButton];
        [self addSubview:self.titleLabel];
        
        [self addConstraints];
    }
    return self;
}

- (void)addConstraints {
    [self.raiseButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.height.equalTo(self);
        make.bottom.mas_equalTo(0);
        make.left.mas_equalTo(20);
    }];
    
    [self.audienceButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.height.equalTo(self);
        make.bottom.mas_equalTo(0);
        make.left.equalTo(self.raiseButton.mas_right).offset(40);
    }];
    
    [self.selectLineView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.width.mas_equalTo(64);
        make.height.mas_equalTo(2);
        make.bottom.mas_equalTo(-2);
        make.centerX.equalTo(self.raiseButton);
    }];
    
    [self.lineView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.bottom.centerX.equalTo(self);
        make.height.mas_equalTo(XH_1PX_WIDTH);
        make.width.equalTo(self);
    }];
    
    [self.cancelButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.mas_equalTo(CGSizeMake(16, 16));
        make.right.mas_offset(-16);
        make.centerY.equalTo(self.audienceButton);
    }];
    
    [self.titleLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.center.equalTo(self);
    }];
}

- (void)setTitleStr:(NSString *)titleStr {
    _titleStr = titleStr;
    if (NOEmptyStr(titleStr)) {
        self.raiseButton.hidden = YES;
        self.audienceButton.hidden = YES;
        self.selectLineView.hidden = YES;
        self.lineView.hidden = YES;
        self.titleLabel.hidden = NO;
        self.titleLabel.text = titleStr;
    } else {
        self.raiseButton.hidden = NO;
        self.audienceButton.hidden = NO;
        self.selectLineView.hidden = NO;
        self.lineView.hidden = NO;
        self.titleLabel.hidden = YES;
    }
}

- (void)raiseButtonAction {
    [self.raiseButton setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    [self.audienceButton setTitleColor:[UIColor colorFromHexString:@"#86909C"] forState:UIControlStateNormal];
    
    [self.selectLineView mas_remakeConstraints:^(MASConstraintMaker *make) {
        make.width.equalTo(self.raiseButton);
        make.height.mas_equalTo(2);
        make.bottom.mas_equalTo(-2);
        make.centerX.equalTo(self.raiseButton);
    }];
    
    if ([self.delegate respondsToSelector:@selector(voiceRoomTopSelectView:clickSwitchItem:)]) {
        [self.delegate voiceRoomTopSelectView:self clickSwitchItem:NO];
    }
}

- (void)audienceButtonAction {
    [self.raiseButton setTitleColor:[UIColor colorFromHexString:@"#86909C"] forState:UIControlStateNormal];
    [self.audienceButton setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    
    [self.selectLineView mas_remakeConstraints:^(MASConstraintMaker *make) {
        make.width.equalTo(self.audienceButton);
        make.height.mas_equalTo(2);
        make.bottom.mas_equalTo(-2);
        make.centerX.equalTo(self.audienceButton);
    }];
    
    if ([self.delegate respondsToSelector:@selector(voiceRoomTopSelectView:clickSwitchItem:)]) {
        [self.delegate voiceRoomTopSelectView:self clickSwitchItem:YES];
    }
}

- (void)cancelButtonAction {
    if ([self.delegate respondsToSelector:@selector(voiceRoomTopSelectView:clickCancelAction:)]) {
        [self.delegate voiceRoomTopSelectView:self clickCancelAction:@""];
    }
}

#pragma mark - getter

- (BaseButton *)raiseButton {
    if (!_raiseButton) {
        _raiseButton = [[BaseButton alloc] init];
        _raiseButton.backgroundColor = [UIColor clearColor];
        [_raiseButton setTitle:@"举手列表" forState:UIControlStateNormal];
        [_raiseButton setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
        _raiseButton.titleLabel.font = [UIFont systemFontOfSize:16];
        [_raiseButton addTarget:self action:@selector(raiseButtonAction) forControlEvents:UIControlEventTouchUpInside];
    }
    return _raiseButton;
}

- (BaseButton *)audienceButton {
    if (!_audienceButton) {
        _audienceButton = [[BaseButton alloc] init];
        _audienceButton.backgroundColor = [UIColor clearColor];
        [_audienceButton setTitle:@"听众列表" forState:UIControlStateNormal];
        [_audienceButton setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
        _audienceButton.titleLabel.font = [UIFont systemFontOfSize:16];
        [_audienceButton addTarget:self action:@selector(audienceButtonAction) forControlEvents:UIControlEventTouchUpInside];
    }
    return _audienceButton;
}

- (UIView *)selectLineView {
    if (!_selectLineView) {
        _selectLineView = [[UIView alloc] init];
        _selectLineView.backgroundColor = [UIColor colorFromRGBHexString:@"#4080FF"];
    }
    return _selectLineView;
}

- (UIView *)lineView {
    if (!_lineView) {
        _lineView = [[UIView alloc] init];
        _lineView.backgroundColor = [UIColor colorFromRGBHexString:@"#FFFFFF" andAlpha:0.1 * 255];
    }
    return _lineView;
}

- (BaseButton *)cancelButton {
    if (!_cancelButton) {
        _cancelButton = [BaseButton buttonWithType:UIButtonTypeCustom];
        [_cancelButton setImage:[UIImage imageNamed:@"voice_cancel"] forState:UIControlStateNormal];
        [_cancelButton addTarget:self action:@selector(cancelButtonAction) forControlEvents:UIControlEventTouchUpInside];
    }
    return _cancelButton;
}

- (UILabel *)titleLabel {
    if (!_titleLabel) {
        _titleLabel = [[UILabel alloc] init];
        _titleLabel.textColor = [UIColor whiteColor];
        _titleLabel.font = [UIFont systemFontOfSize:16 weight:UIFontWeightRegular];
        _titleLabel.numberOfLines = 1;
        _titleLabel.hidden = YES;
    }
    return _titleLabel;
}

@end
