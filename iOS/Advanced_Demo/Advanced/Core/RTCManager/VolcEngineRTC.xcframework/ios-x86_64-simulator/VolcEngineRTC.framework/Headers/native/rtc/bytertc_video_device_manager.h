/*
 * Copyright (c) 2020 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC Video Device Manager
*/

#pragma once

#include "bytertc_audio_device_manager.h"

namespace bytertc {

#ifndef ByteRTC_AUDIO_ONLY

/** 
 * @type api
 * @region 视频设备管理
 * @brief 主要用于枚举、设置视频采集设备
 */
class IVideoDeviceManager {
public:
    /** 
     * @hidden
     * @brief 构造函数
     */
    IVideoDeviceManager() {
    }
    /** 
     * @type api
     * @region 视频设备管理
     * @brief 获取当前系统内视频采集设备列表。
     * @return 包含系统中所有视频采集设备的列表，参看 IDeviceCollection{@link #IDeviceCollection}。  <br>
     */
    virtual IDeviceCollection* EnumerateVideoCaptureDevices() = 0;
    /** 
     * @type api
     * @region 视频设备管理
     * @brief 设置当前视频采集设备
     * @param [in] device_id 视频设备 ID，可以通过 EnumerateVideoCaptureDevices{@link #IVideoDeviceManager#EnumerateVideoCaptureDevices} 获取
     * @return  <br>
     *        + 0：方法调用成功  <br>
     *        + !0：方法调用失败  <br>
     */
    virtual int SetVideoCaptureDevice(const char device_id[MAX_DEVICE_ID_LENGTH]) = 0;
    /** 
     * @type api
     * @region 视频设备管理
     * @brief 获取当前 SDK 正在使用的视频采集设备信息
     * @param [out] device_id 视频设备 ID
     * @return  <br>
     *        + 0：方法调用成功  <br>
     *        + !0：方法调用失败  <br>
     */
    virtual int GetVideoCaptureDevice(char device_id[MAX_DEVICE_ID_LENGTH]) = 0;

    /** 
     * @hidden
     * @brief 析构函数
     */
    virtual ~IVideoDeviceManager() {
    }
};

#endif  // ByteRTC_AUDIO_ONLY

}  // namespace bytertc
