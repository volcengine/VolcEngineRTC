//
//  HistoryTableView.h
//  quickstart
//
//  Created by  on 2021/3/23.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "HistoryTableCell.h"

NS_ASSUME_NONNULL_BEGIN

@interface HistoryTableView : UIView

@property (nonatomic, assign) BOOL isDelete;

@property (nonatomic, copy) NSArray *dataLists;

@end

NS_ASSUME_NONNULL_END
