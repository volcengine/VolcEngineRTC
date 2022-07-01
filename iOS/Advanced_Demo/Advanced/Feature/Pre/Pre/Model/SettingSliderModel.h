//
//  SettingSliderModel.h
//  Advanced
//
//  Created by bytedance on 2021/12/7.
//  Copyright © 2021 bytedance. All rights reserved.
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
