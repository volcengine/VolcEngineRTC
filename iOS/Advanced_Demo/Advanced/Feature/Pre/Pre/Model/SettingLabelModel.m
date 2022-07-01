//
//  SettingLabelModel.m
//  Advanced
//
//  Created by bytedance on 2022/3/16.
//

#import "SettingLabelModel.h"

@implementation SettingLabelModel

- (instancetype)initWithTitle:(NSString *)title
                  describeStr:(NSString *)describeStr  {
    self = [super init];
    if (self) {
        self.cellType = SettingTableViewCellType_Label;
        self.title = title;
        self.describe = describeStr;
    }
    return self;
}

@end
