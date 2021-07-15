//
//  NSSelectPopCell.h
//  veRTC_Demo
//
//  Created by  on 2021/6/11.
//

#import <Cocoa/Cocoa.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSSelectPopCell : NSTableCellView

@property (nonatomic, copy) NSString *messageStr;

@property (nonatomic, assign) BOOL isDelete;

@property (nonatomic, copy) void (^clickBlock)(NSString *str);

@property (nonatomic, copy) void (^clickDeleteBlock)(NSString *str);

@end

NS_ASSUME_NONNULL_END
