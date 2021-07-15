//
//  MeetingRecordComponents.h
//  veRTC_Demo
//
//  Created by  on 2021/6/11.
//

#import "MeetingBaseSetingComponents.h"

NS_ASSUME_NONNULL_BEGIN

@interface MeetingRecordComponents : MeetingBaseSetingComponents

@property (nonatomic, copy) NSArray <NSString *> *dataLists;

@property (nonatomic, copy) NSString *stringValue;

@property (nonatomic, assign) BOOL isDelete;

@property (nonatomic, copy) void (^clickBlock)(NSString *key);

@property (nonatomic, copy) void (^deleteBlock)(NSString *key);

@end

NS_ASSUME_NONNULL_END
