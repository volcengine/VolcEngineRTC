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
 * @notes 该方法仅开启空间音频功能，你须调用 updatePosition:{@link #ByteRTCSpatialAudio#updatePosition:} 设置自身位置坐标后方可收听空间音频效果。空间音频相关 API 和调用时序详见[空间音频](https://www.volcengine.com/docs/6348/93903)。
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
 * @notes 调用该接口更新坐标前，你需调用 enableSpatialAudio:{@link #ByteRTCSpatialAudio#enableSpatialAudio:} 开启空间音频功能。 空间音频相关 API 和调用时序详见[空间音频](https://www.volcengine.com/docs/6348/93903)。<br>
 */
-(int)updatePosition:(Position* _Nonnull) pos;
/**  
 * @type api
 * @region 空间音频
 * @author majun.lvhiei
 * @brief 更新本地用户在空间音频坐标系下的朝向。 <br>
 * @param orientation 自身朝向信息，参看 HumanOrientation{@link #HumanOrientation}。
 * @return 方法调用结果：  <br>
 *        + 0：成功  <br>
 *        + !0：失败
 * @notes  <br>
 *        + 空间音频相关 API 和调用时序详见[空间音频](https://www.volcengine.com/docs/6348/93903)。<br>
 *        + 调用 disableRemoteOrientation{@link #ByteRTCSpatialAudio#disableRemoteOrientation} 可忽略远端用户朝向。
 */
-(int)updateSelfOrientation:(HumanOrientation* _Nonnull) orientation;

/** 
 * @type api
 * @region 音频管理
 * @author luomingkang.264
 * @brief 参与通话的各端调用本接口后，将忽略远端用户的朝向，认为所有远端用户都面向本地用户。<br>
 *        如果此后调用 updateSelfOrientation:{@link #ByteRTCSpatialAudio#updateSelfOrientation:} 更新本地用户朝向，远端用户无法感知这些变化，但本地用户接收音频时可以感知自身朝向改变带来的音频效果变化。
 * @notes <br>
 *        + 进房前后都可以调用该接口。  <br> 
 *        + 调用本接口关闭朝向功能后，在当前的空间音频实例的生命周期内无法再次开启。
 */
-(void)disableRemoteOrientation;
@end
