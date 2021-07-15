//
//  ParamModel.h
//  SceneRTCDemo
//
//  Created by  on 2021/3/18.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface ParamModel : NSObject

@property (nonatomic, copy) NSString *local_res;
@property (nonatomic, copy) NSString *local_fps;
@property (nonatomic, copy) NSString *local_bit_video;
@property (nonatomic, copy) NSString *local_bit_audio;

@property (nonatomic, copy) NSString *remote_rtt_video;
@property (nonatomic, copy) NSString *remote_rtt_audio;
@property (nonatomic, copy) NSString *remote_cpu_avg;
@property (nonatomic, copy) NSString *remote_cpu_max;
@property (nonatomic, copy) NSString *remote_bit_video;
@property (nonatomic, copy) NSString *remote_bit_audio;
@property (nonatomic, copy) NSString *remote_res_min;
@property (nonatomic, copy) NSString *remote_res_max;
@property (nonatomic, copy) NSString *remote_fps_min;
@property (nonatomic, copy) NSString *remote_fps_max;
@property (nonatomic, copy) NSString *remote_loss_video;
@property (nonatomic, copy) NSString *remote_loss_audio;


@property (nonatomic, assign) NSInteger remote_res_min_w;
@property (nonatomic, assign) NSInteger remote_res_min_h;
@property (nonatomic, assign) NSInteger remote_res_max_w;
@property (nonatomic, assign) NSInteger remote_res_max_h;

@end

NS_ASSUME_NONNULL_END
