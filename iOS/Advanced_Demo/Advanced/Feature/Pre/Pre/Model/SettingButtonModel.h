//
//  SettingButtonModel.h
//  Advanced
//
//  Created by bytedance on 2022/3/15.
//

#import "SettingBaseModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface SettingButtonModel : SettingBaseModel

@property (nonatomic, copy) void(^clickBlock)(void);

- (instancetype)initWithTitle:(NSString *)title
                  describeStr:(NSString *)describeStr;

@end

NS_ASSUME_NONNULL_END
