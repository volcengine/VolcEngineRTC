/*
 * Copyright (c) 2021 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief ByteRTCPositionAudioRender
*/

#import <Foundation/Foundation.h>
#import "ByteRTCDefines.h"

/**
 * @type api
 * @region 音频管理
 * @author majun.lvhiei
 * @brief 空间音频接口。
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCPositionAudioRender :NSObject

/**
 * @type api
 * @region 音频管理
 * @author majun.lvhiei
 * @brief 开启或关闭空间音频效果。  <br>
 * @param [in] enable 空间音频效果开关，默认关闭。  <br>
 *       + true: 开启空间音频效果；  <br>
 *       + false: 关闭空间音频效果。  <br>
 */
-(void)enableAudioSpatialRender:(BOOL) enable;

/**
 * @type api
 * @region 音频管理
 * @author majun.lvhiei
 * @brief 更新自己的位置坐标。  <br>
 * @param [in] pos 三维坐标的值，默认为 [0, 0, 0]。根据需要，自行建立空间直角坐标系，并将需要使用空间音频功能的用户，都置于同一坐标系下。  <br>
 * @return  <br>
 *        + 0: 参数检查通过，但不代表更新成功；  <br>
 *        + 其他: 更新失败。  <br>

 */
-(int)updatePosition:(Position* _Nonnull) pos;


/**
 * @type api
 * @region 音频管理
 * @author majun.lvhiei
 * @brief 更新自己的朝向。本地朝向的设置只影响本地听到的音频效果，不影响本地发出的音频效果。  <br>
 * @param [in] orientation 朝向信息，必须是单位向量。参看 HumanOrientation{@link #HumanOrientation}。当朝向的正方向使用默认值时，朝向的坐标系和位置信息使用的坐标系一致。此时，正前方朝向是：`[1, 0, 0]`，正右方朝向是：`[0, 1, 0]`，正上方朝向是：`[0, 0, 1]`。
 * @return 0: 代表更新成功
 * @notes  本地用户调用 enableAudioSpatialRender:{@link #ByteRTCPositionAudioRender#enableAudioSpatialRender:} 使用空间音频功能时，需要调用 updatePosition:{@link #ByteRTCPositionAudioRender#updatePosition:} 接口更新位置坐标后，才能调用此接口。  <br>
 */
-(int)updateSelfOrientation:(HumanOrientation* _Nonnull) orientation;

@end
