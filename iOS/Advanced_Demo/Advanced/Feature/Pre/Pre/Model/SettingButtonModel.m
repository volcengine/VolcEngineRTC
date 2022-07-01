//
//  SettingButtonModel.m
//  Advanced
//
//  Created by bytedance on 2022/3/15.
//

#import "SettingButtonModel.h"

@implementation SettingButtonModel

- (instancetype)initWithTitle:(NSString *)title
                  describeStr:(NSString *)describeStr {
    self = [super init];
    if (self) {
        self.cellType = SettingTableViewCellType_Button;
        self.title = title;
        self.describe = describeStr;
    }
    return self;
}

@end
