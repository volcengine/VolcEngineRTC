//
//  SettingSliderModel.m
//  Advanced
//
//

#import "SettingSliderModel.h"

@implementation SettingSliderModel

- (instancetype)initWithMinValue:(NSInteger)minValue maxBitrate:(NSInteger)maxValue defaultValue:(NSInteger)defaultValue {
    if (self = [super init]) {
        self.cellType = SettingTableViewCellType_Slider;
        self.minValue = minValue;
        self.maxValue = maxValue;
        
        self.currentValue = defaultValue;

    }
    return self;
}

- (void)setCurrentValue:(NSInteger)currentValue {
    if (currentValue > _maxValue) {
        currentValue = _maxValue;
    }
    if (currentValue < _minValue) {
        currentValue = _minValue;
    }
    
    _currentValue = currentValue;
    
}
@end
