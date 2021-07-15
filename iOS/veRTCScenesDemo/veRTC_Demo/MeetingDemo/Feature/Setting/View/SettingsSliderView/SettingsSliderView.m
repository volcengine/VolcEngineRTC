//
//  SettingsSliderView.m
//  quickstart
//
//  Created by  on 2021/3/23.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import "SettingsSliderView.h"

@interface SettingsSliderView ()

@property (nonatomic, strong) UIView *maskView;
@property (nonatomic, strong) UIView *contentView;
@property (nonatomic, strong) UILabel *titleLabel;
@property (nonatomic, strong) UIButton *cancelButton;
@property (nonatomic, strong) UIButton *confirmButton;

@property (nonatomic, assign) CGFloat currentHeight;

@property (nonatomic, strong) UISlider *sliderView;
@property (nonatomic, strong) UILabel *valueLabel;
@property (nonatomic, strong) UILabel *unitLabel;

@end

@implementation SettingsSliderView

- (instancetype)init {
    self = [super init];
    if (self) {
        _currentHeight = 284/2 + [DeviceInforTool getVirtualHomeHeight];
        
        [self addSubViewAndConstraints];
    }
    return self;
}

#pragma mark - Publish Action

- (void)show:(CGFloat)minValue maxValue:(CGFloat)maxValue value:(CGFloat)value {
    [self.sliderView setMinimumValue:minValue];
    [self.sliderView setMaximumValue:maxValue];
    self.sliderView.value = value;
    
    NSString *valueStr = [NSString stringWithFormat:@"%d", (int)value];
    self.valueLabel.text = valueStr;
    
    dispatch_async(dispatch_get_main_queue(), ^{
        [UIView animateWithDuration:0.25 animations:^{
            [self.contentView mas_updateConstraints:^(MASConstraintMaker *make) {
                make.bottom.equalTo(self.maskView).offset(0);
            }];
            [self.contentView.superview layoutIfNeeded];
        }];
    });
}


- (void)sliderValueChanged:(UISlider *)slider forEvent:(UIEvent *)event {
    NSString *valueStr = [NSString stringWithFormat:@"%d", (int)slider.value];
    self.valueLabel.text = valueStr;
}

#pragma mark - Action Method


- (void)cancelButtonAction:(UIButton *)sender {
    __weak __typeof(self) wself = self;
    [self dismiss:^{
        if (wself.clickDismissBlock) {
            wself.clickDismissBlock(YES, @(self.sliderView.value));
        }
    }];
}

- (void)confirmButtonAction:(UIButton *)sender {
    __weak __typeof(self) wself = self;
    [self dismiss:^{
        if (wself.clickDismissBlock) {
            wself.clickDismissBlock(NO, @(self.sliderView.value));
        }
    }];
}

#pragma mark - Private Action

- (void)dismiss:(void (^)(void))block {
    dispatch_async(dispatch_get_main_queue(), ^{
        [UIView animateWithDuration:0.25 animations:^{
            [self.contentView mas_updateConstraints:^(MASConstraintMaker *make) {
                make.bottom.equalTo(self.maskView).offset(self.currentHeight);
            }];
            [self.contentView.superview layoutIfNeeded];
        }];
    });
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.25 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        [self removeAllSubviews];
        [self removeFromSuperview];
        if (block) {
            block();
        }
    });
}

- (void)addSubViewAndConstraints {
    [self addSubview:self.maskView];
    [self.maskView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(self);
    }];
    
    [self.maskView addSubview:self.contentView];
    [self.contentView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.right.equalTo(self.maskView);
        make.bottom.equalTo(self.maskView).offset(_currentHeight);
        make.height.mas_equalTo(_currentHeight);
    }];
    
    [self.contentView addSubview:self.titleLabel];
    [self.titleLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.height.mas_equalTo(108/2);
        make.width.top.centerX.equalTo(self.contentView);
    }];
    
    [self.contentView addSubview:self.cancelButton];
    [self.cancelButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.width.height.mas_equalTo(44);
        make.left.equalTo(self.titleLabel).offset(18);
        make.centerY.equalTo(self.titleLabel);
    }];
    
    [self.contentView addSubview:self.confirmButton];
    [self.confirmButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.width.height.mas_equalTo(44);
        make.right.equalTo(self.titleLabel).offset(-18);
        make.centerY.equalTo(self.titleLabel);
    }];
    
    [self.contentView addSubview:self.sliderView];
    [self.sliderView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.mas_equalTo(32/2);
        make.right.mas_equalTo(-223/2);
        make.height.mas_equalTo(48/2);
        make.bottom.mas_equalTo(-80/2 - [DeviceInforTool getVirtualHomeHeight]);
    }];
    
    [self.contentView addSubview:self.unitLabel];
    [self.unitLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerY.equalTo(self.sliderView);
        make.right.mas_equalTo(-32/2);
    }];
    
    [self.contentView addSubview:self.valueLabel];
    [self.valueLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerY.equalTo(self.sliderView);
        make.left.equalTo(self.sliderView.mas_right);
        make.right.equalTo(self.unitLabel.mas_left);
    }];
}

#pragma mark - getter

- (UISlider *)sliderView {
    if (!_sliderView) {
        _sliderView = [[UISlider alloc] init];
        _sliderView.minimumTrackTintColor = [UIColor colorFromHexString:@"#4080FF"];
        _sliderView.maximumTrackTintColor = [UIColor colorFromHexString:@"#4E5969"];
        [_sliderView setContinuous:YES];
        [_sliderView addTarget:self action:@selector(sliderValueChanged:forEvent:) forControlEvents:UIControlEventValueChanged];
    }
    return _sliderView;
}

- (UIView *)maskView {
    if (!_maskView) {
        _maskView = [[UIView alloc] init];
        _maskView.backgroundColor = [UIColor colorFromRGBHexString:@"#101319" andAlpha:0.5 * 255];
    }
    return _maskView;
}

- (UIView *)contentView {
    if (!_contentView) {
        _contentView = [[UIView alloc] init];
        _contentView.backgroundColor = [UIColor colorFromHexString:@"#272E3B"];
    }
    return _contentView;
}
- (UILabel *)titleLabel {
    if (!_titleLabel) {
        _titleLabel = [[UILabel alloc] init];
        _titleLabel.textColor = [UIColor colorFromHexString:@"#E5E6EB"];
        _titleLabel.textAlignment = NSTextAlignmentCenter;
        _titleLabel.text = @"码率";
    }
    return _titleLabel;
}

- (UIButton *)cancelButton {
    if (!_cancelButton) {
        _cancelButton = [[UIButton alloc] init];
        [_cancelButton addTarget:self action:@selector(cancelButtonAction:) forControlEvents:UIControlEventTouchUpInside];
        _cancelButton.backgroundColor = [UIColor clearColor];
        [_cancelButton setTitle:@"取消" forState:UIControlStateNormal];
        _cancelButton.titleLabel.font = [UIFont systemFontOfSize:15 weight:UIFontWeightRegular];
        [_cancelButton setTitleColor:[UIColor colorFromHexString:@"#86909C"] forState:UIControlStateNormal];
    }
    return _cancelButton;
}

- (UIButton *)confirmButton {
    if (!_confirmButton) {
        _confirmButton = [[UIButton alloc] init];
        [_confirmButton addTarget:self action:@selector(confirmButtonAction:) forControlEvents:UIControlEventTouchUpInside];
        _confirmButton.backgroundColor = [UIColor clearColor];
        [_confirmButton setTitle:@"确定" forState:UIControlStateNormal];
        _confirmButton.titleLabel.font = [UIFont systemFontOfSize:15 weight:UIFontWeightRegular];
        [_confirmButton setTitleColor:[UIColor colorFromHexString:@"#4080FF"] forState:UIControlStateNormal];
    }
    return _confirmButton;
}

- (UILabel *)unitLabel {
    if (!_unitLabel) {
        _unitLabel = [[UILabel alloc] init];
        _unitLabel.text = @"kbps";
        _unitLabel.textColor = [UIColor colorFromHexString:@"#86909C"];
    }
    return _unitLabel;
}

- (UILabel *)valueLabel {
    if (!_valueLabel) {
        _valueLabel = [[UILabel alloc] init];
        _valueLabel.text = @"0";
        _valueLabel.textColor = [UIColor colorFromHexString:@"#E5E6EB"];
        _valueLabel.textAlignment = NSTextAlignmentCenter;
    }
    return _valueLabel;
}

@end
