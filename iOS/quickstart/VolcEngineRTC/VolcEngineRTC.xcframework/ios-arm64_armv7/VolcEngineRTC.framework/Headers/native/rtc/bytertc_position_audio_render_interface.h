/*
 * Copyright (c) 2021 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngine Video Processor Interface
*/

#pragma once

#include "position_audio_render_define.h"

namespace bytertc {

/**
 * @type callback
 * @brief 远端用户位置信息回调
 */
class IRemotePositionInfoObserver{
public:
    virtual ~IRemotePositionInfoObserver() = default;

    /**
     * @hidden(iOS, Android, Windows, macOS)    
     * @type callback
     * @region 音频管理
     * @brief 调用 RegisterRemoteInfoObserver{@link #IPositionAudioRenderInterface#RegisterRemoteInfoObserver} 后，每隔 3s 收到远端的位置信息；如果远端用户更新了位置，会在 500ms 内收到更新后的位置信息。  <br>
     * @param user_infos  远端用户位置信息数组，详见 RemoteUserPositionInfo{@link #RemoteUserPositionInfo} 。
     * @param len  数组长度。
     */
    virtual void OnRemoteUserPositionInfo(const RemoteUserPositionInfo* user_infos, unsigned int len) = 0;

    /**
     * @hidden(iOS, Android, Windows, macOS)    
     * @type callback
     * @region 音频管理
     * @brief 调用 RegisterRemoteInfoObserver{@link #IPositionAudioRenderInterface#RegisterRemoteInfoObserver} 后，如果远端调用 UpdatePosition{@link #IPositionAudioRenderInterface#UpdatePosition} 更新了位置，会在 500ms 内收到远端变更后的位置信息。  <br>
     * @param user_infos  远端位置信息数组，详见 RemoteUserPositionInfo{@link #RemoteUserPositionInfo} 。
     * @param len  数组长度。
     */
    virtual void OnRemoteUserPositionChanged(const RemoteUserPositionInfo* user_infos, unsigned int len) = 0;
};

/**
 * @type api
 * @region 音频管理
 * @brief 空间音频接口
 */
class IPositionAudioRenderInterface
{
public:
    /**
     * @hidden
     * @brief 析构函数
     */
    virtual ~IPositionAudioRenderInterface() = default;

    /**
     * @type api
     * @region 音频管理
     * @brief 开启或关闭空间音频效果。  <br>
     * @param [in] enable 空间音频效果开关，默认关闭。  <br>
     *       + true: 开启空间音频效果；  <br>
     *       + false: 关闭空间音频效果。  <br>
     */
    virtual void EnableAudioSpatialRender(bool enable) = 0;

    /**
     * @type api
     * @region 音频管理
     * @brief 更新自己的位置坐标。  <br>
     * @param [in] pos 三维坐标的值，默认为 [0, 0, 0]。根据需要，自行建立空间直角坐标系，并将需要使用空间音频功能的用户，都置于同一坐标系下。  <br>
     * @return  <br>
     *        + 0: 参数检查通过，但不代表更新成功；  <br>
     *        + 其他: 更新失败。  <br>
     */
    virtual int UpdatePosition(const Position& pos) = 0;

    /**
     * @type api
     * @region 音频管理
     * @brief 更新自己的朝向。本地朝向的设置只影响本地听到的音频效果，不影响本地发出的音频效果。  <br>
     * @param [in] orientation 朝向信息，必须是单位向量。参看 HumanOrientation{@link #HumanOrientation}。当朝向的正方向使用默认值时，朝向的坐标系和位置信息使用的坐标系一致。此时，正前方朝向是：`[1, 0, 0]`，正右方朝向是：`[0, 1, 0]`，正上方朝向是：`[0, 0, 1]`。
     * @return 0: 朝向更新成功。
     * @notes  本地用户调用 EnableAudioSpatialRender{@link #IPositionAudioRenderInterface#EnableAudioSpatialRender} 使用空间音频功能时，需要调用 UpdatePosition{@link #IPositionAudioRenderInterface#UpdatePosition} 接口更新位置坐标后，才能调用此接口。  <br>
     */
    virtual int UpdateSelfOrientation(const HumanOrientation& orientation) = 0;

    /**
     * @hidden(iOS, Android, Windows, macOS)    
     * @type api
     * @region 音频管理
     * @brief 注册远端用户位置信息回调
     * @param [in] observer 用户位置信息观察者。详见 IRemotePositionInfoObserver{@link #IRemotePositionInfoObserver} 。如果传入 null，则取消注册。  <br>
     * @notes 只有在远端用户调用 EnableAudioSpatialRender{@link #IPositionAudioRenderInterface#EnableAudioSpatialRender} 使用空间音频效果时，调用 UpdatePosition{@link #IPositionAudioRenderInterface#UpdatePosition} 更新位置坐标，本地用户才可以通过本接口注册的回调获取远端用户的位置信息。  <br>
     */
    virtual void RegisterRemoteInfoObserver(IRemotePositionInfoObserver* observer) = 0;
};

} // namespace bytertc
