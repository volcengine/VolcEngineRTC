//
//  BitRateSelectView.h
//  SceneRTCDemo
//
//  Created by  on 2021/3/9.
//

#import <Cocoa/Cocoa.h>
#import "MeetingBaseSetingComponents.h"

NS_ASSUME_NONNULL_BEGIN

@interface BitRateSelectView : MeetingBaseSetingComponents

@property (nonatomic, copy) NSString *unitStr;

@property (nonatomic, assign, readonly) NSInteger numValue;

@property (nonatomic, copy) void (^sliderValueChangedBlock)(NSInteger value);

- (void)updateMinValue:(CGFloat)minValue maxValue:(CGFloat)maxValue;

- (void)updateValue:(NSInteger)value;

@end

NS_ASSUME_NONNULL_END
