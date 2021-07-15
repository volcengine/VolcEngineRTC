//
//  MeetingAlertCompoments.h
//  SceneRTCDemo
//
//  Created by  on 2021/3/12.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface MeetingAlertCompoments : NSObject

+ (MeetingAlertCompoments *)share;

- (void)showWithTitle:(NSString *)title clickBlock:(void (^)(BOOL result))block;

@end

NS_ASSUME_NONNULL_END
