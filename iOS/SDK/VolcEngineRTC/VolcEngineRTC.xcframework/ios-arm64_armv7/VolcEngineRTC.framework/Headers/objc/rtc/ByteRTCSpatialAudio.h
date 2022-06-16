/*
 *  Copyright (c) 2022 The ByteRtc project authors. All Rights Reserved.
 *  @company ByteDance.Inc
 *  @brief spatial audio interface
 */

#pragma once

#import <Foundation/Foundation.h>
#import "ByteRTCAudioDefines.h"

/** 
 * @type keytype
 * @brief 方向朝向信息
 */
BYTERTC_APPLE_EXPORT @interface Orientation : NSObject
/** 
 * @brief x 方向向量
 */
@property(nonatomic, assign) float x;
/** 
 * @brief y 方向向量
 */
@property(nonatomic, assign) float y;
/** 
 * @brief z 方向向量
 */
@property(nonatomic, assign) float z;

@end

/**  
 * @type keytype
 * @brief 三维朝向信息，三个向量需要两两垂直。参看 Orientation{@link #Orientation}。
 */
BYTERTC_APPLE_EXPORT @interface HumanOrientation : NSObject
/**  
 * @brief 正前方朝向，默认值为 {1,0,0}，即正前方朝向 x 轴正方向
 */
@property(nonatomic, strong) Orientation* _Nonnull forward;
/**  
 * @brief 正右方朝向，默认值为 {0,1,0}，即右手朝向 y 轴正方向
 */
@property(nonatomic, strong) Orientation* _Nonnull right;
/**  
 * @brief 正上方朝向，默认值为 {0,0,1}，即头顶朝向 z 轴正方向
 */
@property(nonatomic, strong) Orientation* _Nonnull up;

@end

/**  
 * @type api
 * @brief 空间音频接口实例
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCSpatialAudio :NSObject
/**  
 * @type api
 * @region 空间音频
 * @author majun.lvhiei
 * @brief 开启/关闭空间音频功能。  <br>
 * @param enable 是否开启空间音频功能：  <br>
 *        + true：开启  <br>
 *        + false：关闭（默认）
 * @notes 该方法仅开启空间音频功能，你须调用 updatePosition:{@link #ByteRTCSpatialAudio#updatePosition:} 设置自身位置坐标后方可收听空间音频效果。
 */
- (void)enableSpatialAudio:(BOOL)enable;
/**  
 * @type api
 * @region 空间音频
 * @author majun.lvhiei
 * @brief 更新本地用户在房间内空间直角坐标系中的位置坐标。  <br>
 * @param pos 三维坐标的值，默认为 [0, 0, 0]。参看 Position{@link #Position}
 * @return  <br>
 *        + 0: 成功；  <br>
 *        + !0: 失败。  <br>
 * @notes 调用该接口更新坐标前，你需调用 enableSpatialAudio:{@link #ByteRTCSpatialAudio#enableSpatialAudio:} 开启空间音频功能。 <br>
 */
-(int)updatePosition:(Position* _Nonnull) pos;
/**  
 * @type api
 * @region 空间音频
 * @author majun.lvhiei
 * @brief 更新本地用户在房间内的朝向。该设置只影响本地用户听到的音频效果，并不影响本地用户发出的音频效果。  <br>
 * @param orientation 自身朝向信息，参看 HumanOrientation{@link #HumanOrientation}。
 * @return 方法调用结果：  <br>
 *        + 0：成功  <br>
 *        + !0：失败
 * @notes 调用该接口更新坐标前，你需调用 enableSpatialAudio:{@link #ByteRTCSpatialAudio#enableSpatialAudio:} 开启空间音频功能，且调用 updatePosition:{@link #ByteRTCSpatialAudio#updatePosition:} 更新自身位置坐标。
 */
-(int)updateSelfOrientation:(HumanOrientation* _Nonnull) orientation;

@end
