//
//  PhoneLoginTextfileView.h
//  veRTC_Demo
//
//  Created by  on 2021/6/7.
//

#import <Cocoa/Cocoa.h>

NS_ASSUME_NONNULL_BEGIN

@interface PhoneLoginTextFieldView : NSView

@property (nonatomic, assign) CGFloat rightSpace;

@property (nonatomic, copy) NSString *placeholderStr;

@property (nonatomic, copy) NSString *errorStr;

@property (nonatomic, assign) BOOL isNeedBorder;

@property (nonatomic, copy) NSString *text;

@property (nonatomic, assign) NSInteger maxLimit;

@property (nonatomic, copy) void (^changeInputIllegal)(BOOL isIllegal);

@property (nonatomic, copy) void (^keyboardClickTab)(void);

@property (nonatomic, copy) void (^keyboardClickEnter)(void);

@property (nonatomic, assign, readonly) BOOL isIllegal;

- (void)textBecomeFirstResponder;

@end

NS_ASSUME_NONNULL_END
