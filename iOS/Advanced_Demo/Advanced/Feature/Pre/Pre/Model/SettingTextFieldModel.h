//
//  SettingTextFieldModel.h
//  Advanced
//
//  Created by bytedance on 2022/3/15.
//

#import "SettingBaseModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface SettingTextFieldModel : SettingBaseModel

@property (nonatomic, copy) void(^inputBlock)(NSInteger index, NSString *valueStr);

@property (nonatomic, copy) NSString *alertTitle;

@property (nonatomic, copy) NSString *alertMessage;

@property (nonatomic, copy) NSString *unit;

@property (nonatomic, copy) NSArray<NSString *> *placeholders;

- (instancetype)initWithTitle:(NSString *)title
                   defaultStr:(NSString *)defaultStr;

@end

NS_ASSUME_NONNULL_END
