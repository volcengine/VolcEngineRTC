//
//  FUBeautySkinModel.h
//  FUDemo
//
//  Created by 项林平 on 2021/7/19.
//

#import <Foundation/Foundation.h>
#import "FUDefines.h"

NS_ASSUME_NONNULL_BEGIN

@interface FUBeautySkinModel : NSObject

@property (nonatomic, copy) NSString *name;
/// 美肤类型
@property (nonatomic, assign) FUBeautySkin type;
/// 当前值
@property (nonatomic, assign) double currentValue;
/// 默认值
@property (nonatomic, assign) double defaultValue;
/// 默认值是否中位数
@property (nonatomic, assign) BOOL defaultValueInMiddle;
/// 实际值对应0.0-1.0的倍率
@property (nonatomic, assign) NSInteger ratio;

@end

NS_ASSUME_NONNULL_END
