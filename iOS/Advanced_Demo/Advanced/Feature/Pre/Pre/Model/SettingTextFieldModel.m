//
//  SettingTextFieldModel.m
//  Advanced
//
//

#import "SettingTextFieldModel.h"

@implementation SettingTextFieldModel

- (instancetype)initWithTitle:(NSString *)title
                   defaultStr:(NSString *)defaultStr  {
    self = [super init];
    if (self) {
        self.cellType = SettingTableViewCellType_TextField;
        self.title = title;
        self.describe = defaultStr;
        self.unit = @"";
    }
    return self;
}
@end
