//
//  FUBodyViewModel.h
//  FURTCDemo
//
//  Created by 项林平 on 2023/2/7.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@class FUBodyModel;

NS_ASSUME_NONNULL_BEGIN

@interface FUBodyViewModel : NSObject

@property (nonatomic, copy, readonly) NSArray<FUBodyModel *> *bodies;
/// 是否所有值都是默认
@property (nonatomic, assign, readonly) BOOL isDefaultValue;
/// 当前选中索引，默认为-1
@property (nonatomic, assign) NSInteger selectedIndex;

/// 设置单项美肤值
/// @param value 当前选中单项的值
- (void)setBodyValue:(double)value;

/// 设置当前所有美体值
- (void)setAllBodyValues;

/// 恢复所有美肤值为默认
- (void)recoverAllBodyValuesToDefault;


- (double)currentValueAtIndex:(NSUInteger)index;

- (double)defaultValueAtIndex:(NSUInteger)index;

- (BOOL)defaultValueInMiddleAtIndex:(NSUInteger)index;

- (NSString *)nameAtIndex:(NSUInteger)index;

- (UIImage *)iconAtIndex:(NSUInteger)index;

@end

NS_ASSUME_NONNULL_END
