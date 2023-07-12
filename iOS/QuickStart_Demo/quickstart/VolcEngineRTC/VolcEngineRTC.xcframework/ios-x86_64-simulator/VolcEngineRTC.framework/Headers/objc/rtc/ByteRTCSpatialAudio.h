/*
 *  Copyright (c) 2022 The ByteRtc project authors. All Rights Reserved.
 *  @company ByteDance.Inc
 *  @brief spatial audio interface
 */

#pragma once

#import <Foundation/Foundation.h>
#import "ByteRTCAudioDefines.h"

/**  
 * @type api
 * @brief 空间音频接口实例
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCSpatialAudio :NSObject
/**  
 * @type api
 * @region 空间音频
 * @brief 开启/关闭空间音频功能。  <br>
 * @param enable 是否开启空间音频功能：  <br>
 *        + YES：开启  <br>
 *        + NO：关闭（默认）
 * @notes 该方法仅开启空间音频功能，你须调用 updatePosition:{@link #ByteRTCSpatialAudio#updatePosition:} 设置自身位置坐标后方可收听空间音频效果。空间音频相关 API 和调用时序详见[空间音频](https://www.volcengine.com/docs/6348/93903)。
 */
- (void)enableSpatialAudio:(BOOL)enable;
/** 
 * @deprecated since 352.1, will be deleted in 357，use updateSelfPosition instead
 * @type api
 * @region 空间音频
 * @brief 更新本地用户发声时，在房间内空间直角坐标系中的位置坐标。  <br>
 *        如果未调用 updateListenerPosition:{@link #ByteRTCSpatialAudio#updateListenerPosition:} 设定收听位置，默认的收听位置和发声位置一致。
 * @param pos 三维坐标的值，默认为 [0, 0, 0]。参看 Position{@link #Position}。
 * @return  <br>
 *        + 0: 成功；  <br>
 *        + !0: 失败。  <br>
 * @notes 调用该接口更新坐标前，你需调用 enableSpatialAudio:{@link #ByteRTCSpatialAudio#enableSpatialAudio:} 开启空间音频功能。空间音频相关 API 和调用时序详见[空间音频](https://www.volcengine.com/docs/6348/93903)。 <br>
 */
-(int)updatePosition:(Position* _Nonnull) pos
__deprecated_msg("deprecated since 352, use updateSelfPosition instead");

/** 
 * @deprecated since 352.1, will be deleted in 357，use updateSelfPosition instead
 * @type api
 * @region 空间音频
 * @brief 更新本地用户发声时，在空间音频坐标系下的朝向。  <br>
 *        如果未调用 updateListenerOrientation:{@link #ByteRTCSpatialAudio#updateListenerOrientation:} 设定收听朝向，默认的收听位朝向和发声朝向一致。
 * @param orientation 参看 HumanOrientation{@link #HumanOrientation}。
 * @return 方法调用结果：  <br>
 *        + 0：成功  <br>
 *        + !0：失败
 * @notes  <br>
 *        + 空间音频相关 API 和调用时序详见[空间音频](https://www.volcengine.com/docs/6348/93903)。<br>
 *        + 调用 disableRemoteOrientation{@link #ByteRTCSpatialAudio#disableRemoteOrientation} 可关闭声源朝向效果。
 */
-(int)updateSelfOrientation:(HumanOrientation* _Nonnull) orientation
__deprecated_msg("deprecated since 352, use updateSelfPosition instead");

/** 
 * @type api
 * @region 音频管理
 * @brief 关闭本地用户朝向对本地用户发声效果的影响。<br>
 *        调用此接口后，房间内的其他用户收听本地发声时，声源都在收听者正面。
 * @notes <br>
 *        + 调用本接口关闭朝向功能后，在当前的空间音频实例的生命周期内无法再次开启。<br>
 *        + 调用此接口不影响本地用户收听朝向的音频效果。要改变本地用户收听朝向，参看 updateSelfOrientation:{@link #ByteRTCSpatialAudio#updateSelfOrientation:} 和 updateListenerOrientation:{@link #ByteRTCSpatialAudio#updateListenerOrientation:} 。
 */
-(void)disableRemoteOrientation;
/** 
 * @deprecated since 352.1, will be deleted in 357，use updateRemotePosition instead
 * @type api
 * @region 空间音频
 * @brief 更新在房间内收听音频时的位置。<br>
 *        通过此接口，你可以设定本地发声位置和收听位置不同。
 * @param pos 空间直角坐标系下的坐标值。参看 Position{@link #Position}。<br>
 *            如果未调用此接口设定收听位置，那么默认值为通过 updatePosition:{@link #ByteRTCSpatialAudio#updatePosition:} 设定的值。
 * @return  <br>
 *        + 0: 成功；  <br>
 *        + !0: 失败。  <br>
 * @notes <br>
 *        + 调用此接口前，你需调用 enableSpatialAudio:{@link #ByteRTCSpatialAudio#enableSpatialAudio:} 开启空间音频功能。<br>
 *        + 空间音频相关 API 和调用时序详见[空间音频](https://www.volcengine.com/docs/6348/93903)。
 */
-(int)updateListenerPosition:(Position* _Nonnull) pos
__deprecated_msg("deprecated since 352, use updateRemotePosition instead");
/** 
 * @deprecated since 352.1, will be deleted in 357，use updateRemotePosition instead
 * @type api
 * @region 空间音频
 * @brief 更新在房间内收听音频时的朝向。<br>
 *        通过此接口，你可以设定本地用户的发声朝向和收听朝向不同。
 * @param [in] orientation 自身朝向信息，参看 HumanOrientation{@link #HumanOrientation}。<br>
 *                         如果未调用此接口设定收听朝向，那么默认值为通过 updateSelfOrientation:{@link #ByteRTCSpatialAudio#updateSelfOrientation:} 设定的值。
 * @return 方法调用结果：  <br>
 *        + 0：成功  <br>
 *        + !0：失败
 * @notes 空间音频相关 API 和调用时序详见[空间音频](https://www.volcengine.com/docs/6348/93903)。
 */
-(int)updateListenerOrientation:(HumanOrientation* _Nonnull)orientation
__deprecated_msg("deprecated since 352, use updateRemotePosition instead");
/** 
 * @valid since 3.52.
 * @type api
 * @region 音频管理
 * @brief 设置本地用户在自建空间直角坐标系中的收听坐标和收听朝向，以实现本地用户预期的空间音频收听效果。 
 * @param positionInfo 空间音频位置信息。参看 ByteRTCPositionInfo{@link #ByteRTCPositionInfo}。<br>
 * @return  <br>
 *        + 0：成功。  <br>
 *        + <0：失败。 <br>
 *        + -2: 失败，原因是校验本地用户的三维朝向信息时，三个向量没有两两垂直。
 * @notes <br>
 *        该方法需在进房后调用。调用该接口更新坐标前，你需调用 enableSpatialAudio{@link #ByteRTCSpatialAudio#enableSpatialAudio} 开启空间音频功能。空间音频相关 API 和调用时序详见[空间音频](https://www.volcengine.com/docs/6348/93903)。<br>
 *        调用此接口在本地进行的设定对其他用户的空间音频收听效果不会产生任何影响。
 */
-(int)updateSelfPosition:(ByteRTCPositionInfo* _Nonnull)positionInfo;
/** 
 * @valid since 3.52.
 * @type api
 * @region 音频管理
 * @brief 设置房间内某一远端用户在本地用户自建的空间音频坐标系中的发声位置和发声朝向，以实现本地用户预期的空间音频收听效果。 
 * @param uid 用户 ID
 * @param positionInfo 远端用户的空间音频位置信息。参看 ByteRTCPositionInfo{@link #ByteRTCPositionInfo}。
 * @return  <br>
 *        + 0：成功。  <br>
 *        + <0：失败。 <br>
 *        + -2: 失败，原因是校验远端用户的三维朝向信息时，三个向量没有两两垂直。
 * @notes <br>
 *        该方法需在创建房间后调用。 <br>
 *        调用此接口在本地进行的设定对其他用户的空间音频收听效果不会产生任何影响。
 */
-(int)updateRemotePosition:(NSString * _Nonnull)uid
                         positionInfo:(ByteRTCPositionInfo* _Nonnull)positionInfo;
/** 
 * @valid since 3.52.
 * @type api
 * @region 音频管理
 * @brief 移除调用 updateRemotePosition{@link #ByteRTCSpatialAudio#updateRemotePosition} 为某一远端用户设置的空间音频效果。
 * @param uid 远端用户 ID。
 * @return  <br>
 *        + 0：成功。  <br>
 *        + <0：失败。 
 */
-(int)removeRemotePosition:(NSString * _Nonnull)uid;
/** 
 * @valid since 3.52.
 * @type api
 * @region 音频管理
 * @brief 移除调用 updateRemotePosition{@link #ByteRTCSpatialAudio#updateRemotePosition} 为所有远端用户设置的空间音频效果。
 * @return  <br>
 *        + 0：成功。  <br>
 *        + <0：失败。
 */
-(int)removeAllRemotePosition;
@end
