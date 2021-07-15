//
//  MeetingPickerCompoments.h
//  quickstart
//
//  Created by  on 2021/3/23.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface MeetingPickerCompoments : NSObject

@property (nonatomic, copy) NSString *titleStr;

@property (nonatomic, copy) void (^clickDismissBlock)(BOOL isCancel, id selectItem, NSInteger row);

- (instancetype)initWithHeight:(CGFloat)height superView:(UIView *)superView;

- (void)show:(NSArray *)dataLists selectItem:(id)item;

@end
