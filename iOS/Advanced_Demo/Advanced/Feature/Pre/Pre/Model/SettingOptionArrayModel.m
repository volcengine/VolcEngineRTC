//
//  SettingOptionArrayModel.m
//  Advanced
//
//  Created by bytedance on 2021/12/7.
//  Copyright © 2021 bytedance. All rights reserved.
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
