//
//  SettingOptionArrayModel.m
//  Advanced
//
//

#import "SettingOptionArrayModel.h"

@implementation SettingOptionArrayModel

- (instancetype)initWithOptionArray:(NSArray<NSString *> *)optionArray defaultIndex:(NSInteger)defaultIndex {
    if (self = [super init]) {
        self.cellType = SettingTableViewCellType_OptionArray;
        self.optionArray = optionArray;
        self.currentIndex = defaultIndex;
    }
    return self;
}

@end
