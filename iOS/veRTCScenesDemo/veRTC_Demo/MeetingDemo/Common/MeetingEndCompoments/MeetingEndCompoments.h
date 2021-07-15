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

@property (nonatomic, copy) void (^clickButtonBlock)(MeetingButtonStatus status);

- (void)showWithStatus:(MeetingEndStatus)status;

@end

NS_ASSUME_NONNULL_END
