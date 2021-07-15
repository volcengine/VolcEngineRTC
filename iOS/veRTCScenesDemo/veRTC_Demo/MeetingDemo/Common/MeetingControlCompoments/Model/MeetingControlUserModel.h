//
//  MeetingControlUserModel.h
//  SceneRTCDemo
//
//  Created by  on 2021/3/16.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface MeetingControlUserModel : NSObject

@property (nonatomic, copy) NSString *user_id;

@property (nonatomic, copy) NSString *user_name;

@property (nonatomic, copy) NSString *room_id;

@property (nonatomic, copy) NSString *user_uniform_name;

@property (nonatomic, assign) BOOL is_host;

@property (nonatomic, assign) BOOL is_mic_on;

@property (nonatomic, assign) BOOL is_camera_on;

@property (nonatomic, assign) BOOL is_sharing;

@property (nonatomic, assign) NSInteger created_at;

@end

NS_ASSUME_NONNULL_END
