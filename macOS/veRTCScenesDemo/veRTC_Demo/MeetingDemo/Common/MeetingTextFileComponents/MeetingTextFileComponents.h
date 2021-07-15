//
//  MeetingTextFileComponents.h
//  SceneRTCDemo
//
//  Created by  on 2021/3/8.
//

#import <Cocoa/Cocoa.h>
@class MeetingTextFileComponents;
NS_ASSUME_NONNULL_BEGIN

@protocol MeetingTextFileComponentsDelegate <NSObject>

- (void)meetingTextFileComponents:(MeetingTextFileComponents *)meetingTextFileComponents checkInputIllegal:(BOOL)isIllegal;

@end

@interface MeetingTextFileComponents : NSView

@property (nonatomic, copy) NSString *text;

@property (nonatomic, assign) NSInteger maxLength;

@property (nonatomic, copy) NSString *placeholderString;

@property (nonatomic, assign) BOOL isCheckNumberEng;

@property (nonatomic, assign) BOOL isCheckAll;

@property (nonatomic, weak) id<MeetingTextFileComponentsDelegate> delegate;

@property (nonatomic, strong) NSButton *cancelButton;

@property (nonatomic, copy) void (^keyboardClickTab)(void);

@property (nonatomic, copy) void (^keyboardClickEnter)(void);

- (void)textBecomeFirstResponder;

@end

NS_ASSUME_NONNULL_END
