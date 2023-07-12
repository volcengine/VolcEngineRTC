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
 * @brief 用户在空间音频坐标系里的位置信息。
 */
struct PositionInfo {
    /** 
     * @brief 用户在空间音频坐标系里的位置，需自行建立空间直角坐标系。参看 Position{@link #Position}。
     */
    Position position;
    /** 
     * @brief 用户在空间音频坐标系里的三维朝向信息。三个向量需要两两垂直。参看 HumanOrientation{@link #HumanOrientation}。
     */
    HumanOrientation orientation;
};

/** 
 * @hidden(Linux)
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
     * @notes 该方法仅开启空间音频功能，你须调用 updatePosition{@link #ISpatialAudio#updatePosition} 设置自身位置坐标后方可收听空间音频效果。空间音频相关 API 和调用时序详见[空间音频](https://www.volcengine.com/docs/6348/93903)。
     */
    virtual void enableSpatialAudio(bool enable) = 0;

    /** 
     * @deprecated since 352.1, will be deleted in 357，use updateSelfPosition instead
     * @type api
     * @region 空间音频
     * @brief 更新本地用户发声时，在房间内空间直角坐标系中的位置坐标。  <br>
     *        如果未调用 updateListenerPosition{@link #ISpatialAudio#updateListenerPosition} 设定收听位置，默认的收听位置和发声位置一致。
     * @param [in] pos 三维坐标的值，默认为 [0, 0, 0]。参看 Position{@link #Position}。
     * @return  <br>
     *        + 0: 成功；  <br>
     *        + !0: 失败。  <br>
     * @notes 调用该接口更新坐标前，你需调用 enableSpatialAudio{@link #ISpatialAudio#enableSpatialAudio} 开启空间音频功能。空间音频相关 API 和调用时序详见[空间音频](https://www.volcengine.com/docs/6348/93903)。 <br>
     */
    BYTERTC_DEPRECATED virtual int updatePosition(const Position& pos) = 0;

    /** 
     * @deprecated since 352.1, will be deleted in 357，use updateSelfPosition instead
     * @type api
     * @region 空间音频
     * @brief 更新本地用户发声时，在空间音频坐标系下的朝向。  <br>
     *        如果未调用 updateListenerOrientation{@link #ISpatialAudio#updateListenerOrientation} 设定收听朝向，默认的收听位朝向和发声朝向一致。
     * @param [in] orientation 参看 HumanOrientation{@link #HumanOrientation}。
     * @return 方法调用结果：  <br>
     *        + 0：成功  <br>
     *        + !0：失败
     * @notes  <br>
     *        + 空间音频相关 API 和调用时序详见[空间音频](https://www.volcengine.com/docs/6348/93903)。<br>
     *        + 调用 disableRemoteOrientation{@link #ISpatialAudio#disableRemoteOrientation} 关闭此效果。
     */
    BYTERTC_DEPRECATED virtual int updateSelfOrientation(const HumanOrientation& orientation) = 0;

    /** 
     * @type api
     * @region 音频管理
     * @brief 关闭本地用户朝向对本地用户发声效果的影响。<br>
     *        调用此接口后，房间内的其他用户收听本地发声时，声源都在收听者正面。
     * @notes <br>
     *        + 调用本接口关闭朝向功能后，在当前的空间音频实例的生命周期内无法再次开启。<br>
     *        + 调用此接口不影响本地用户收听朝向的音频效果。要改变本地用户收听朝向，参看 updateSelfOrientation{@link #ISpatialAudio#updateSelfOrientation} 和 updateListenerOrientation{@link #ISpatialAudio#updateListenerOrientation} 。
     */
    virtual void disableRemoteOrientation() = 0;
    
    /** 
     * @deprecated since 352.1, will be deleted in 357，use updateRemotePosition instead
     * @type api
     * @region 空间音频
     * @brief 更新在房间内收听音频时的位置。<br>
     *        通过此接口，你可以设定本地发声位置和收听位置不同。
     * @param [in] pos 空间直角坐标系下的坐标值。参看 Position{@link #Position}。<br>
     *                 如果未调用此接口设定收听位置，那么默认值为通过 updatePosition{@link #ISpatialAudio#updatePosition} 设定的值。
     * @return  <br>
     *        + 0: 成功；  <br>
     *        + !0: 失败。  <br>
     * @notes <br>
     *        + 调用此接口前，你需调用 enableSpatialAudio{@link #ISpatialAudio#enableSpatialAudio} 开启空间音频功能。<br>
     *        + 空间音频相关 API 和调用时序详见[空间音频](https://www.volcengine.com/docs/6348/93903)。
     */
    BYTERTC_DEPRECATED virtual int updateListenerPosition(const Position &pos) = 0;
    
    /** 
     * @deprecated since 352.1, will be deleted in 357，use updateRemotePosition instead
     * @type api
     * @region 空间音频
     * @brief 更新在房间内收听音频时的朝向。<br>
     *        通过此接口，你可以设定本地用户的发声朝向和收听朝向不同。
     * @param [in] orientation 自身朝向信息，参看 HumanOrientation{@link #HumanOrientation}。<br>
     *                         如果未调用此接口设定收听朝向，那么默认值为通过 updateSelfOrientation{@link #ISpatialAudio#updateSelfOrientation} 设定的值。
     * @return 方法调用结果：  <br>
     *        + 0：成功  <br>
     *        + !0：失败
     * @notes 空间音频相关 API 和调用时序详见[空间音频](https://www.volcengine.com/docs/6348/93903)。
     */
    BYTERTC_DEPRECATED virtual int updateListenerOrientation(const HumanOrientation& orientation) = 0;
    /** 
     * @valid since 3.52.
     * @type api
     * @hidden(Linux)
     * @region 音频管理
     * @brief 设置本地用户在自建空间直角坐标系中的收听坐标和收听朝向，以实现本地用户预期的空间音频收听效果。 
     * @param positionInfo 空间音频位置信息。参看 PositionInfo{@link #PositionInfo}。
     * @return  <br>
     *        + 0：成功。  <br>
     *        + <0：失败。 <br>
     *        + -2: 失败，原因是校验本地用户的三维朝向信息时，三个向量没有两两垂直。
     * @notes <br>
     *        该方法需在进房后调用。调用该接口更新坐标前，你需调用 enableSpatialAudio{@link #ISpatialAudio#enableSpatialAudio} 开启空间音频功能。空间音频相关 API 和调用时序详见[空间音频](https://www.volcengine.com/docs/6348/93903)。<br>
     *        调用此接口在本地进行的设定对其他用户的空间音频收听效果不会产生任何影响。
     */
    virtual int updateSelfPosition(const PositionInfo& position_info) = 0;
    /** 
     * @valid since 3.52.
     * @type api
     * @hidden(Linux)
     * @region 音频管理
     * @brief 设置房间内某一远端用户在本地用户自建的空间音频坐标系中的发声位置和发声朝向，以实现本地用户预期的空间音频收听效果。
     * @param uid 用户 ID
     * @param positionInfo 远端用户的空间音频位置信息。参看 PositionInfo{@link #PositionInfo}。
     * @return  <br>
     *        + 0：成功。  <br>
     *        + <0：失败。 <br>
     *        + -2: 失败，原因是校验远端用户的三维朝向信息时，三个向量没有两两垂直。
     * @notes  <br>
     *        该方法需在创建房间后调用。 <br>
     *        调用此接口在本地进行的设定对其他用户的空间音频收听效果不会产生任何影响。
     */
    virtual int updateRemotePosition(const char* uid, const PositionInfo& position_info) = 0;
    /** 
     * @valid since 3.52.
     * @type api
     * @hidden(Linux)
     * @region 音频管理
     * @brief 移除调用 updateRemotePosition{@link #ISpatialAudio#updateRemotePosition} 为某一远端用户设置的空间音频效果。
     * @param uid 远端用户 ID。
     * @return  <br>
     *        + 0：成功。  <br>
     *        + <0：失败。 
     */
    virtual int removeRemotePosition(const char* uid) = 0;
    /** 
     * @valid since 3.52.
     * @type api
     * @hidden(Linux)
     * @region 音频管理
     * @brief 移除调用 updateRemotePosition{@link #ISpatialAudio#updateRemotePosition} 为所有远端用户设置的空间音频效果。
     * @return  <br>
     *        + 0：成功。  <br>
     *        + <0：失败。
     */
    virtual int removeAllRemotePosition() = 0;

    /** 
     * @hidden constructor/destructor
     * @brief 析构函数
     */
    virtual ~ISpatialAudio() = default;
};

}  // namespace bytertc
