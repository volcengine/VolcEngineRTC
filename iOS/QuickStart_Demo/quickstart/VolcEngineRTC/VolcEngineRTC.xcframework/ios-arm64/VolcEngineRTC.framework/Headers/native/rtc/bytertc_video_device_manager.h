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
 * @region 引擎管理
 * @brief 视频设备相关的信息
 */
class IVideoDeviceCollection : public IDeviceCollection {
public:
    /** 
     * @hidden constructor/destructor
     * @brief 构造函数
     */
    IVideoDeviceCollection() {};
    /** 
     * @type api
     * @region 引擎管理
     * @brief 获取当前系统内视频设备数量
     * @return 视频设备数量
     */
    virtual int getCount() override {return 0;};
    /** 
     * @type api
     * @region 引擎管理
     * @brief 根据索引号，获取设备信息
     * @param [in] index 设备索引号，从 0 开始，注意需小于 getCount{@link #IVideoDeviceCollection#getCount} 返回值。
     * @param [out] device_name 设备名称
     * @param [out] device_id 设备 ID
     * @return  <br>
     *        + 0：方法调用成功  <br>
     *        + !0：方法调用失败  <br>
     */
    virtual int getDevice(int index, char device_name[MAX_DEVICE_ID_LENGTH], char device_id[MAX_DEVICE_ID_LENGTH]) override {return 0;};
    /** 
     * @type api
     * @region 引擎管理
     * @brief 释放当前 IVideoDeviceCollection{@link #IVideoDeviceCollection} 对象占用的资源。
     * @notes 不需要返回视频设备相关信息列表时应该调用本方法释放相关资源。
     */
    virtual void release()override {};
    /** 
     * @type api
     * @region 引擎管理
     * @brief 根据索引号，获取设备信息
     * @param [in] index 设备索引号，从 0 开始，注意需小于 getCount{@link #IVideoDeviceCollection#getCount} 返回值。
     * @param [out] video_device_info 设备信息
     * @return  <br>
     *        + 0：方法调用成功  <br>
     *        + !0：方法调用失败  <br>
     */
    virtual int getDevice(int index, VideoDeviceInfo* video_device_info) = 0;
protected:
    /** 
     * @hidden constructor/destructor
     * @brief 析构函数
     */
    virtual ~IVideoDeviceCollection() {};
};

/** 
 * @type api
 * @region 视频设备管理
 * @brief 主要用于枚举、设置视频采集设备
 */
class IVideoDeviceManager {
public:
    /** 
     * @hidden constructor/destructor
     * @brief 构造函数
     */
    IVideoDeviceManager() {
    }
    /** 
     * @type api
     * @region 视频设备管理
     * @brief 获取当前系统内视频采集设备列表。
     * @return 包含系统中所有视频采集设备的列表，参看 IVideoDeviceCollection{@link #IVideoDeviceCollection}。  <br>
     */
    virtual IVideoDeviceCollection* enumerateVideoCaptureDevices() = 0;
    /** 
     * @type api
     * @region 视频设备管理
     * @brief 设置当前视频采集设备
     * @param [in] device_id 视频设备 ID，可以通过 enumerateVideoCaptureDevices{@link #IVideoDeviceManager#enumerateVideoCaptureDevices} 获取
     * @return  <br>
     *        + 0：方法调用成功  <br>
     *        + !0：方法调用失败  <br>
     */
    virtual int setVideoCaptureDevice(const char device_id[MAX_DEVICE_ID_LENGTH]) = 0;
    /** 
     * @type api
     * @region 视频设备管理
     * @brief 获取当前 SDK 正在使用的视频采集设备信息
     * @param [out] device_id 视频设备 ID。此参数同时是入参和出参。
     * @return  <br>
     *        + 0：方法调用成功  <br>
     *        + !0：方法调用失败  <br>
     */
    virtual int getVideoCaptureDevice(char device_id[MAX_DEVICE_ID_LENGTH]) = 0;

    /** 
     * @hidden constructor/destructor
     * @brief 析构函数
     */
    virtual ~IVideoDeviceManager() {
    }
};

#endif  // ByteRTC_AUDIO_ONLY

}  // namespace bytertc
