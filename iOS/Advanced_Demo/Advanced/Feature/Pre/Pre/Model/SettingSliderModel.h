//
//  SettingSliderModel.h
//  Advanced
//
//

#import "SettingBaseModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface SettingSliderModel : SettingBaseModel
@property (nonatomic, assign) NSInteger minValue;
@property (nonatomic, assign) NSInteger maxValue;
@property (nonatomic, assign) NSInteger currentValue;
@property (nonatomic, copy) NSString *suffix;

@property (nonatomic, copy) void(^sliderValueDidChanged)(NSInteger value);

- (instancetype)initWithMinValue:(NSInteger)minValue maxBitrate:(NSInteger)maxValue defaultValue:(NSInteger)defaultValue;
@end

NS_ASSUME_NONNULL_END
