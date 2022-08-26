//
//  SettingSegmentModel.m
//  Advanced
//
//

#import "SettingSegmentModel.h"

@implementation SettingSegmentModel

- (instancetype)initWithDefaultSelectedIndex:(NSInteger)index {
    if (self = [super init]) {
        self.cellType = SettingTableViewCellType_Segment;
        self.selectedIndex = index;
    }
    return self;
}

@end
