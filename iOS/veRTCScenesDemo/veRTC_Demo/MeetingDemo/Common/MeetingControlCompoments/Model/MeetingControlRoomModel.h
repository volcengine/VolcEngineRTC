//
//  MeetingControlRoomModel.h
//  SceneRTCDemo
//
//  Created by  on 2021/3/16.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface MeetingControlRoomModel : NSObject

@property (nonatomic, copy) NSString *room_id;

@property (nonatomic, copy) NSString *host_id;

@property (nonatomic, assign) BOOL record;

@property (nonatomic, copy) NSString *screen_shared_uid;

@property (nonatomic, assign) NSInteger created_at;

@property (nonatomic, assign) NSInteger now;

@end

NS_ASSUME_NONNULL_END
