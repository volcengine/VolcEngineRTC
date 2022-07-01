//
//  SettingSwitchModel.h
//  Advanced
//
//  Created by bytedance on 2021/12/7.
//  Copyright © 2021 bytedance. All rights reserved.
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
