/*
 *  Copyright (c) 2022 The ByteRtc project authors. All Rights Reserved.
 *  @company ByteDance.Inc
 *  @brief spatial audio interface
 */

#pragma once

#include "bytertc_audio_defines.h"

namespace bytertc {

/** 
 * @type keytype
 * @brief 方向朝向信息
 */
struct Orientation {
    /**  
     * @brief x 方向向量
     */
    float x;
    /**  
     * @brief y 方向向量
     */
    float y;
    /**  
     * @brief z 方向向量
     */
    float z;
};

/**  
 * @type keytype
 * @brief 三维朝向信息，三个向量需要两两垂直。参看 Orientation{@link #Orientation}。
 */
struct HumanOrientation {
    /**  
     * @brief 正前方朝向，默认值为 {1,0,0}，即正前方朝向 x 轴正方向
     */
    Orientation forward =  { 1, 0, 0 };
    /**  
     * @brief 正右方朝向，默认值为 {0,1,0}，即右手朝向 y 轴正方向
     */
    Orientation right = { 0, 1, 0 };
    /**  
     * @brief 正上方朝向，默认值为 {0,0,1}，即头顶朝向 z 轴正方向
     */
    Orientation up = { 0, 0, 1 };
};

/**  
 * @type api
 * @brief 空间音频接口实例
 */
class ISpatialAudio {
public:
    /**  
     * @type api
     * @region 空间音频
     * @brief 开启/关闭空间音频功能。  <br>
     * @param [in] enable 是否开启空间音频功能：  <br>
     *        + true：开启  <br>
     *        + false：关闭（默认）
     * @notes 该方法仅开启空间音频功能，你须调用 UpdatePosition{@link #ISpatialAudio#UpdatePosition} 设置自身位置坐标后方可收听空间音频效果。
     */
    virtual void EnableSpatialAudio(bool enable) = 0;

    /**  
     * @type api
     * @region 空间音频
     * @brief 更新本地用户在房间内空间直角坐标系中的位置坐标。  <br>
     * @param [in] pos 三维坐标的值，默认为 [0, 0, 0]。参看 Position{@link #Position}
     * @return  <br>
     *        + 0: 成功；  <br>
     *        + !0: 失败。  <br>
     * @notes 调用该接口更新坐标前，你需调用 EnableSpatialAudio{@link #ISpatialAudio#EnableSpatialAudio} 开启空间音频功能。 <br>
     */
    virtual int UpdatePosition(const Position& pos) = 0;

    /**  
     * @type api
     * @region 空间音频
     * @brief 更新本地用户在房间内的朝向。该设置只影响本地用户听到的音频效果，并不影响本地用户发出的音频效果。  <br>
     * @param [in] orientation 自身朝向信息，参看 HumanOrientation{@link #HumanOrientation}。
     * @return 方法调用结果：  <br>
     *        + 0：成功  <br>
     *        + !0：失败
     * @notes 调用该接口更新坐标前，你需调用 EnableSpatialAudio{@link #ISpatialAudio#EnableSpatialAudio} 开启空间音频功能，且调用 UpdatePosition{@link #ISpatialAudio#UpdatePosition} 更新自身位置坐标。
     */
    virtual int UpdateSelfOrientation(const HumanOrientation& orientation) = 0;

    /**  
     * @hidden
     * @brief 析构函数
     */
    virtual ~ISpatialAudio() = default;
};

}  // namespace bytertc
