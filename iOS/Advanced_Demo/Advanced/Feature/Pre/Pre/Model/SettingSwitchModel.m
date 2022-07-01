//
//  SettingSwitchModel.m
//  Advanced
//
//  Created by bytedance on 2021/12/7.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import "SettingSwitchModel.h"

@implementation SettingSwitchModel

- (instancetype)initWithDefaultStatus:(BOOL)isOn {
    if (self = [super init]) {
        self.cellType = SettingTableViewCellType_Switch;
        self.isOn = isOn;
    }
    return self;
}
@end
