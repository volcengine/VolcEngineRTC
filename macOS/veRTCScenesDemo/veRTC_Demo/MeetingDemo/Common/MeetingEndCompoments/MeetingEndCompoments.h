//
//  MeetingEndCompoments.h
//  SceneRTCDemo
//
//  Created by  on 2021/3/10.
//

#import <Foundation/Foundation.h>
#import "MeetingEndView.h"

NS_ASSUME_NONNULL_BEGIN

@interface MeetingEndCompoments : NSObject

@property (nonatomic, assign) BOOL isWindow;

@property (nonatomic, copy) void (^clickButtonBlock)(MeetingButtonStatus status);

- (void)showWithStatus:(MeetingEndStatus)status;

- (void)showWithStatus:(MeetingEndStatus)status view:(NSView *)view;

- (void)dismissEndView;

@end

NS_ASSUME_NONNULL_END
