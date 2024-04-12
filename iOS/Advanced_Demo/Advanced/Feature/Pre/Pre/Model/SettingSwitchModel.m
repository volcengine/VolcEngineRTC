//
//  SettingSwitchModel.m
//  Advanced
//
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
