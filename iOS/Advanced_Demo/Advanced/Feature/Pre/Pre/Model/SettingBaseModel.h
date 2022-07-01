//
//  SettingBaseModel.h
//  Advanced
//
//  Created by bytedance on 2021/12/7.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSUInteger, SettingTableViewCellType) {
    SettingTableViewCellType_Switch,
    SettingTableViewCellType_OptionArray,
    SettingTableViewCellType_Slider,
    SettingTableViewCellType_Button,
    SettingTableViewCellType_Label,
    SettingTableViewCellType_TextField,
};

NS_ASSUME_NONNULL_BEGIN

@interface SettingBaseModel : NSObject
@property (nonatomic, copy) NSString *title;
@property (nonatomic, copy) NSString *describe;

@property (nonatomic, assign) SettingTableViewCellType cellType;
@end

NS_ASSUME_NONNULL_END
