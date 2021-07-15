//
//  MeetingToastWindowController.h
//  SceneRTCDemo
//
//  Created by  on 2021/3/29.
//

#import <Cocoa/Cocoa.h>

NS_ASSUME_NONNULL_BEGIN

@interface MeetingToastWindowController : NSWindowController

- (void)showWithMessage:(NSString *)message block:(void (^)(BOOL result))block;

@end

NS_ASSUME_NONNULL_END
