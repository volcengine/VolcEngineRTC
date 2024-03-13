//
//  FUMakeupViewModel.h
//  FUDemo
//
//  Created by 项林平 on 2021/6/15.
//  美妆功能模块
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@class FUMakeupModel;

NS_ASSUME_NONNULL_BEGIN

@interface FUMakeupViewModel : NSObject

@property (nonatomic, copy, readonly) NSArray<FUMakeupModel *> *combinationMakeups;

/// 当前选中组合妆索引
/// @note 0表示卸妆状态
@property (nonatomic, assign, readonly) NSInteger selectedIndex;

/// 当前选中组合妆程度值
@property (nonatomic, assign) double selectedMakeupValue;

/// 选择组合妆
/// @param index 组合妆索引，0为卸妆
- (void)selectCombinationMakeupAtIndex:(NSInteger)index;

/// 组合妆名称
/// @param index 索引
- (NSString *)combinationMakeupNameAtIndex:(NSUInteger)index;

/// 组合妆icon
/// @param index 索引
- (UIImage *)combinationMakeupIconAtIndex:(NSUInteger)index;


@end

NS_ASSUME_NONNULL_END
