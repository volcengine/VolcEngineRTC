//
//  NSLabel.h
//  SceneRTCDemo


#import <Cocoa/Cocoa.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSLabel : NSTextField

@property (nonatomic, copy) NSString *text;

@property (nonatomic, assign) CGFloat lineSpacing;

@property (nonatomic, assign) BOOL oneLine;

@end

NS_ASSUME_NONNULL_END
