//
//  SettingSwitchModel.h
//  Advanced
//
//

#import <Foundation/Foundation.h>
#import "SettingBaseModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface SettingSwitchModel : SettingBaseModel
@property (nonatomic, assign) BOOL isOn;

@property (nonatomic, copy) void(^switchDidChangeStatus)(BOOL isOn);

- (instancetype)initWithDefaultStatus:(BOOL)isOn;

@end

NS_ASSUME_NONNULL_END
