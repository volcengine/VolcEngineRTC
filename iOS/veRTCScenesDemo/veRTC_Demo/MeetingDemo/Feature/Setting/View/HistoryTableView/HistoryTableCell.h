//
//  HistoryTableCell.h
//  quickstart
//
//  Created by  on 2021/3/23.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface HistoryTableCell : UITableViewCell

@property (nonatomic, copy) MeetingControlRecordModel *model;

@end

NS_ASSUME_NONNULL_END
