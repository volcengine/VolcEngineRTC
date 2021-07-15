//
//  RoomParamInfoModel.h
//  veRTC_Demo
//
//  Created by  on 2021/4/9.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface RoomParamInfoModel : NSObject

@property (nonatomic, strong) NSString *local_res;
@property (nonatomic, strong) NSString *local_fps;
@property (nonatomic, strong) NSString *local_bit_video;
@property (nonatomic, strong) NSString *local_bit_audio;

@property (nonatomic, strong) NSString *remote_rtt_video;
@property (nonatomic, strong) NSString *remote_rtt_audio;
@property (nonatomic, strong) NSString *remote_cpu_avg;
@property (nonatomic, strong) NSString *remote_cpu_max;
@property (nonatomic, strong) NSString *remote_bit_video;
@property (nonatomic, strong) NSString *remote_bit_audio;
@property (nonatomic, strong) NSString *remote_res_min;
@property (nonatomic, strong) NSString *remote_res_max;
@property (nonatomic, strong) NSString *remote_fps_min;
@property (nonatomic, strong) NSString *remote_fps_max;
@property (nonatomic, strong) NSString *remote_loss_video;
@property (nonatomic, strong) NSString *remote_loss_audio;



@end

NS_ASSUME_NONNULL_END
