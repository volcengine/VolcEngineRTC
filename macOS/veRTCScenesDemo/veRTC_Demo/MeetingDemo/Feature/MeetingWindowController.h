//
//  MeetingWindowController.h
//  SceneRTCDemo
//
//  Created by  on 2021/3/2.
//

#import <Cocoa/Cocoa.h>

NS_ASSUME_NONNULL_BEGIN

@interface MeetingWindowController : NSWindowController

- (void)show;

- (BOOL)isNeedClose;

- (void)showEndView;

@end

NS_ASSUME_NONNULL_END
