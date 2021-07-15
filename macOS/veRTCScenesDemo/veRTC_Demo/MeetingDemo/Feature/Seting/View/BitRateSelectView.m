//
//  BitRateSelectView.m
//  SceneRTCDemo
//
//  Created by  on 2021/3/9.
//

#import "BitRateSelectView.h"
#import "BaseSilder.h"

@interface BitRateSelectView ()

@property (nonatomic, strong) NSLabel *unitLabel;
@property (nonatomic, strong) NSLabel *valueLabel;
@property (nonatomic, strong) NSView *valueBgView;
@property (nonatomic, strong) BaseSilder *slider;

@end

@implementation BitRateSelectView

- (instancetype)init {
    self = [super init];
    if (self) {
        
        [self addSubview:self.unitLabel];
        [self.unitLabel mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.equalTo(self.mas_right).offset(8);
            make.centerY.equalTo(self);
        }];
        
        [self addSubview:self.valueBgView];
        [self.valueBgView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.size.mas_equalTo(CGSizeMake(56, 32));
            make.centerY.right.equalTo(self);
        }];
        
        [self addSubview:self.valueLabel];
        [self.valueLabel mas_makeConstraints:^(MASConstraintMaker *make) {
            make.center.equalTo(self.valueBgView);
        }];
        
        [self addSubview:self.slider];
        [self.slider mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.centerY.left.equalTo(self);
            make.right.equalTo(self.valueBgView.mas_left).offset(-8);
        }];
    }
    return self;
}

- (void)updateMinValue:(CGFloat)minValue maxValue:(CGFloat)maxValue {
    self.slider.minValue = minValue;
    self.slider.maxValue = maxValue;
    CGFloat currentValue = self.slider.floatValue;
    if (self.slider.floatValue <= minValue) {
        self.slider.floatValue = minValue;
        currentValue = minValue;
    }
    if (self.slider.floatValue >= maxValue) {
        self.slider.floatValue = maxValue;
        currentValue = maxValue;
    }
    self.valueLabel.text = [NSString stringWithFormat:@"%.0f", currentValue];
}

#pragma mark - Publish Action

- (void)setUnitStr:(NSString *)unitStr {
    _unitStr = unitStr;
    self.unitLabel.text = unitStr;
}

- (NSInteger)numValue {
    return [self.valueLabel.text integerValue];
}

- (void)updateValue:(NSInteger)value {
    self.valueLabel.text = [NSString stringWithFormat:@"%ld", (long)value];
    self.slider.intValue = value;
}

#pragma mark - Private Action

- (void)bitRateSliderValueChanged:(NSSlider *)slider {
    self.valueLabel.text = [NSString stringWithFormat:@"%ld", (long)slider.intValue];
    if (self.sliderValueChangedBlock) {
        self.sliderValueChangedBlock(slider.intValue);
    }
}

#pragma mark - getter


- (NSLabel *)unitLabel {
    if (!_unitLabel) {
        _unitLabel = [[NSLabel alloc] init];
        _unitLabel.textColor = [NSColor colorFromHexString:@"#1D2129"];
        _unitLabel.font = [NSFont systemFontOfSize:12 weight:NSFontWeightRegular];
        _unitLabel.wantsLayer = YES;
    }
    return _unitLabel;
}

- (NSLabel *)valueLabel {
    if (!_valueLabel) {
        _valueLabel = [[NSLabel alloc] init];
        _valueLabel.textColor = [NSColor colorFromHexString:@"#1D2129"];
        _valueLabel.font = [NSFont systemFontOfSize:12 weight:NSFontWeightRegular];
    }
    return _valueLabel;
}

- (NSView *)valueBgView {
    if (!_valueBgView) {
        _valueBgView = [[NSView alloc] init];
        [_valueBgView setBackgroundColorWithHexString:@"#F2F3F8"];
        _valueBgView.wantsLayer = YES;
        _valueBgView.layer.cornerRadius = 2;
        _valueBgView.layer.masksToBounds = YES;
    }
    return _valueBgView;
}

- (BaseSilder *)slider {
    if (!_slider) {
        _slider = [[BaseSilder alloc] init];
        _slider.sliderType = NSSliderTypeLinear;
        _slider.target = self;
        _slider.action = @selector(bitRateSliderValueChanged:);
    }
    return _slider;
}

@end
