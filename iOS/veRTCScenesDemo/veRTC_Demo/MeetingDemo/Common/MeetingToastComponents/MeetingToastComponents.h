//
//  MeetingToastComponents.h
//  quickstart
//
//  Created by  on 2021/4/1.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface MeetingToastComponents : NSObject

+ (MeetingToastComponents *)shareMeetingToastComponents;

- (void)showWithMessage:(NSString *)message;

- (void)showWithMessage:(NSString *)message view:(UIView *)windowView;

- (void)showWithMessage:(NSString *)message view:(UIView *)windowView block:(void (^)(BOOL result))block;

- (void)showWithMessage:(NSString *)message view:(UIView *)windowView keep:(BOOL)isKeep block:(void (^)(BOOL result))block;

- (void)dismiss;

@end

NS_ASSUME_NONNULL_END
