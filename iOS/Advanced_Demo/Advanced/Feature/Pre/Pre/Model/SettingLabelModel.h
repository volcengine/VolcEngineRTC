//
//  SettingLabelModel.h
//  Advanced
//
//

#import "SettingBaseModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface SettingLabelModel : SettingBaseModel

- (instancetype)initWithTitle:(NSString *)title
                  describeStr:(NSString *)describeStr;

@end

NS_ASSUME_NONNULL_END
