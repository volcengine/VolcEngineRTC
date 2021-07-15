//
//  MeetingToastComponents.h
//  SceneRTCDemo
//
//  Created by  on 2021/3/8.
//

#import <Cocoa/Cocoa.h>

NS_ASSUME_NONNULL_BEGIN

@interface MeetingToastComponents : NSObject

+ (MeetingToastComponents *)shareMeetingToastComponents;

- (void)showWithMessage:(NSString *)message;

- (void)showWithMessage:(NSString *)message view:(NSView *)windowView;

- (void)showWithMessage:(NSString *)message view:(NSView *)windowView block:(void (^)(BOOL result))block;

- (void)showWithMessage:(NSString *)message view:(NSView *)windowView keep:(BOOL)isKeep block:(void (^)(BOOL result))block;

- (void)dismiss;

@end

NS_ASSUME_NONNULL_END
