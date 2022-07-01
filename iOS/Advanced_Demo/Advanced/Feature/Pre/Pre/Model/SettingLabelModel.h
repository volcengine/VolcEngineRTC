//
//  SettingLabelModel.h
//  Advanced
//
//  Created by bytedance on 2022/3/16.
//

#import "SettingBaseModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface SettingLabelModel : SettingBaseModel

- (instancetype)initWithTitle:(NSString *)title
                  describeStr:(NSString *)describeStr;

@end

NS_ASSUME_NONNULL_END
