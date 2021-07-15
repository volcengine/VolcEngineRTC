//
//  BaseTextField.h
//  veRTC_Demo
//
//  Created by  on 2021/7/7.
//

#import <Cocoa/Cocoa.h>

NS_ASSUME_NONNULL_BEGIN

@interface BaseTextField : NSTextField

@property (nonatomic, assign, readonly) BOOL isFirstResponder;

@property (nonatomic, copy) void (^changeFirstResponder)(BOOL isFirst);

@end

NS_ASSUME_NONNULL_END
