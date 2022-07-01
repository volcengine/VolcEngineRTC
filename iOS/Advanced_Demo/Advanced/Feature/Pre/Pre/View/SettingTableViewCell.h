//
//  SettingTableViewCell.h
//  Advanced
//
//  Created by bytedance on 2021/12/7.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SettingSwitchModel.h"
#import "SettingOptionArrayModel.h"
#import "SettingSliderModel.h"
#import "SettingButtonModel.h"
#import "SettingTextFieldModel.h"
#import "SettingLabelModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface SettingTableViewCell : UITableViewCell
@property (nonatomic, strong) SettingBaseModel *model;
@end

NS_ASSUME_NONNULL_END
