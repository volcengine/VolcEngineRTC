//
//  SettingTableViewCell.h
//  Advanced
//
//

#import <UIKit/UIKit.h>
#import "SettingSwitchModel.h"
#import "SettingOptionArrayModel.h"
#import "SettingSliderModel.h"
#import "SettingButtonModel.h"
#import "SettingTextFieldModel.h"
#import "SettingLabelModel.h"
#import "SettingSegmentModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface SettingTableViewCell : UITableViewCell
@property (nonatomic, strong) SettingBaseModel *model;
@end

NS_ASSUME_NONNULL_END
