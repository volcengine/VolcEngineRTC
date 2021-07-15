//
//  UserCell.h
//  veRTC_Demo
//
//  Created by  on 2021/5/23.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MenuCellModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface UserCell : UITableViewCell

@property (nonatomic, strong) MenuCellModel *model;

@end

NS_ASSUME_NONNULL_END
