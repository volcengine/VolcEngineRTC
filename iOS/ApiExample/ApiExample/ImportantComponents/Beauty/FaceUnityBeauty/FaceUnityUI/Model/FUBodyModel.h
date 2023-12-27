//
//  FUBodyModel.h
//  FURTCDemo
//
//  Created by 项林平 on 2023/2/7.
//

#import <Foundation/Foundation.h>
#import "FUDefines.h"

NS_ASSUME_NONNULL_BEGIN

@interface FUBodyModel : NSObject

@property (nonatomic, copy) NSString *name;
/// 美体类型
@property (nonatomic, assign) FUBeautyBodyItem type;
/// 当前值
@property (nonatomic, assign) double currentValue;
/// 默认值
@property (nonatomic, assign) double defaultValue;
/// 默认值是否中位数
@property (nonatomic, assign) BOOL defaultValueInMiddle;

@end

NS_ASSUME_NONNULL_END
