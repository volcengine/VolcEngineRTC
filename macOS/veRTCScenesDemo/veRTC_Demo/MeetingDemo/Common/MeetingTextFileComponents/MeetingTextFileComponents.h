//
//  MeetingTextFileComponents.h
//  SceneRTCDemo
//
//  Created by on 2021/3/8.
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

@property (nonatomic, assign) BOOL isCheck;

@property (nonatomic, weak) id<MeetingTextFileComponentsDelegate> delegate;

@property (nonatomic, strong) NSButton *cancelButton;

@end

NS_ASSUME_NONNULL_END
