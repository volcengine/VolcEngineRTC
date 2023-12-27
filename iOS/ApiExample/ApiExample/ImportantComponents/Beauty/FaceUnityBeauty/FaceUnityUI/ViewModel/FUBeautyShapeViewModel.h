//
//  FUBeautyShapeViewModel.h
//  FUDemo
//
//  Created by 项林平 on 2021/6/11.
//  美型功能模块
//

#import <Foundation/Foundation.h>
#import <FURenderKit/FURenderKit.h>
#import "FUBeautyShapeModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface FUBeautyShapeViewModel : NSObject

@property (nonatomic, copy, readonly) NSArray<FUBeautyShapeModel *> *beautyShapes;
/// 是否所有值都是默认
@property (nonatomic, assign, readonly) BOOL isDefaultValue;
/// 当前选中索引，默认为-1
@property (nonatomic, assign) NSInteger selectedIndex;
/// 美型属性需要根据高低端机适配
@property (nonatomic, assign) FUDevicePerformanceLevel performanceLevel;

/// 设置单项美型值
/// @param value 当前选中单项的值
- (void)setShapeValue:(double)value;

/// 恢复所有美型值为默认
- (void)recoverAllShapeValuesToDefault;

@end

NS_ASSUME_NONNULL_END
