//
//  FUBeautyFilterViewModel.h
//  FUBeautyComponent
//
//  Created by 项林平 on 2022/7/7.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@class FUBeautyFilterModel;

NS_ASSUME_NONNULL_BEGIN

@interface FUBeautyFilterViewModel : NSObject

@property (nonatomic, copy, readonly) NSArray<FUBeautyFilterModel *> *beautyFilters;
/// 选中滤镜索引
@property (nonatomic, assign) NSInteger selectedIndex;

/// 设置滤镜程度
/// @param value 程度值
- (void)setFilterValue:(double)value;

/// 滤镜名称
/// @param index 索引
- (NSString *)filterNameAtIndex:(NSUInteger)index;

/// 滤镜icon
/// @param index 索引
- (UIImage *)filterIconAtIndex:(NSUInteger)index;

/// 滤镜程度值
/// @param index 索引
- (double)filterValueAtIndex:(NSUInteger)index;

@end

NS_ASSUME_NONNULL_END
