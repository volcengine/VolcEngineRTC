//
//  MeetingTextViewCompoments.h
//  SceneRTCDemo
//
//  Created by  on 2021/3/12.
//

#import <Cocoa/Cocoa.h>

NS_ASSUME_NONNULL_BEGIN

@interface MeetingTextViewCompoments : NSView

@property (nonatomic, strong) NSFont *font;

@property (nonatomic, strong) NSColor *textColor;

@property (nonatomic, copy) NSString *placeholderString;

@end

NS_ASSUME_NONNULL_END
