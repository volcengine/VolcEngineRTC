//
//  FUBeautyShapeModel.h
//  FUDemo
//
//  Created by 项林平 on 2021/7/19.
//

#import <Foundation/Foundation.h>
#import "FUDefines.h"

NS_ASSUME_NONNULL_BEGIN

@interface FUBeautyShapeModel : NSObject

@property (nonatomic, copy) NSString *name;
/// 美型类型
@property (nonatomic, assign) FUBeautyShape type;
/// 当前值
@property (nonatomic) double currentValue;
/// 默认值
@property (nonatomic) double defaultValue;
/// 默认值是否中位数
@property (nonatomic, assign) BOOL defaultValueInMiddle;
/// 是否区分设备性能
@property (nonatomic, assign) BOOL differentiateDevicePerformance;

@end

NS_ASSUME_NONNULL_END
