//
//  MeetingSelectComponents.h
//  SceneRTCDemo
//
//  Created by  on 2021/3/9.
//

#import <Cocoa/Cocoa.h>
#import "MeetingBaseSetingComponents.h"

NS_ASSUME_NONNULL_BEGIN

@interface MeetingSelectComponents : MeetingBaseSetingComponents

@property (nonatomic, copy) NSArray <NSString *> *dataLists;

@property (nonatomic, copy) NSString *stringValue;

@property (nonatomic, copy) void (^clickBlock)(NSString *key);

@end

NS_ASSUME_NONNULL_END
