/*
 * Copyright (c) 2020 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC Audio Device Manager
*/

#pragma once

#include "bytertc_audio_defines.h"

namespace bytertc {

/**
 * @locale zh
 * @deprecated since 3.42 and will be deleted in 3.51, use IAudioDeviceCollection{@link #IAudioDeviceCollection} and IVideoDeviceCollection{@link #IVideoDeviceCollection} instead.
 * @type api
 * @region 引擎管理
 * @brief 音视频设备相关的信息
 */
/**
 * @locale en
 * @deprecated since 3.45 and will be deleted in 3.51, use IAudioDeviceCollection{@link #IAudioDeviceCollection} and IVideoDeviceCollection{@link #IVideoDeviceCollection} instead.
 * @type api
 * @region engine management
 * @brief Audio & video equipment related information
 */
class IDeviceCollection {
public:
    /**
     * @locale zh
     * @hidden constructor/destructor
     * @brief 构造函数
     */
    /**
     * @locale en
     * @hidden constructor/destructor
     * @brief Constructor
     */
    IDeviceCollection() {
    }
    /**
     * @locale zh
     * @type api
     * @region 引擎管理
     * @brief 获取当前系统内音视频设备数量
     * @return 音视频设备数量
     */
    /**
     * @locale en
     * @type api
     * @region engine management
     * @brief Get the number of audio & video devices in the current system
     * @return Number of audio & video devices
     */
    virtual int getCount() = 0;
    /**
     * @locale zh
     * @type api
     * @region 引擎管理
     * @brief 根据索引号，获取设备信息
     * @param index 设备索引号，从 0 开始，注意需小于 getCount{@link #IAudioDeviceCollection#getCount} 返回值。
     * @param [out] device_name 设备名称
     * @param [out] device_id 设备 ID
     * @return  
     *        + 0：方法调用成功  <br>
     *        + !0：方法调用失败  
     */
    /**
     * @locale en
     * @type api
     * @region Engine management
     * @brief According to the index number, get device information
     * @param index Device index number, starting from 0, note that it must be less than the return value of getCount{@link #IAudioDeviceCollection#getCount}.
     * @param [out] device_name device name
     * @param [out] device_id device ID
     * @return  
     *         + 0: Success. <br>
     *         +! 0: failure 
     */
    virtual int getDevice(int index, char device_name[MAX_DEVICE_ID_LENGTH], char device_id[MAX_DEVICE_ID_LENGTH]) = 0;
    /**
     * @locale zh
     * @type api
     * @region 引擎管理
     * @brief 释放当前 IAudioDeviceCollection{@link #IAudioDeviceCollection} 对象占用的资源。
     * @note 不需要返回音视频设备相关信息列表时应该调用本方法释放相关资源。
     */
    /**
     * @locale en
     * @type api
     * @region engine management
     * @brief Releases the resources occupied by the current IDeviceCollection{@link #IAudioDeviceCollection} object.
     * @note This method should be called to release related resources when you do not need to return a list of audio & video device related information.
     */
    virtual void release() = 0;
/**
 * @hidden constructor/destructor
 */
protected:
    /**
     * @locale zh
     * @hidden constructor/destructor
     * @brief 析构函数
     */
    /**
     * @locale en
     * @hidden constructor/destructor
     * @brief Destructor
     */
    virtual ~IDeviceCollection() {
    }
};

/**
 * @locale zh
 * @hidden(Android,iOS)
 * @type api
 * @region 引擎管理
 * @brief 音频设备相关的信息
 */
/**
 * @locale en
 * @hidden(Android,iOS)
 * @type api
 * @region  engine management
 * @brief Audio equipment related information
 */
class IAudioDeviceCollection : public IDeviceCollection {
public:
    /**
     * @locale zh
     * @hidden constructor/destructor
     * @brief 构造函数
     */
    /**
     * @locale en
     * @hidden constructor/destructor
     * @brief Constructor
     */
    IAudioDeviceCollection() {};
    /**
     * @locale zh
     * @type api
     * @region 引擎管理
     * @brief 获取当前系统内音频设备数量
     * @return 音频设备数量
     */
    /**
     * @locale en
     * @type api
     * @region engine management
     * @brief Get the number of audio & video devices in the current system
     * @return Number of audio devices
     */
    virtual int getCount() override {return 0;};
    /**
     * @locale zh
     * @type api
     * @region 引擎管理
     * @brief 根据索引号，获取设备信息
     * @param index 设备索引号，从 0 开始，注意需小于 getCount{@link #IAudioDeviceCollection#getCount} 返回值。
     * @param [out] device_name 设备名称
     * @param [out] device_id 设备 ID
     * @return  
     *        + 0：方法调用成功  <br>
     *        + !0：方法调用失败  
     */
    /**
     * @locale en
     * @type api
     * @region Engine management
     * @brief According to the index number, get device information
     * @param index Device index number, starting from 0, note that it must be less than the return value of getCount{@link #IAudioDeviceCollection#getCount}.
     * @param  [out] device_name Device name
     * @param  [out] device_id Device ID
     * @return   
     *         + 0: Success. <br>
     *         +! 0: failure 
     */
    virtual int getDevice(int index, char device_name[MAX_DEVICE_ID_LENGTH], char device_id[MAX_DEVICE_ID_LENGTH]) override {return 0;};
    /**
     * @locale zh
     * @type api
     * @region 引擎管理
     * @brief 释放当前 IAudioDeviceCollection{@link #IAudioDeviceCollection} 对象占用的资源。
     * @note 不需要返回音频设备相关信息列表时应该调用本方法释放相关资源。
     */
    /**
     * @locale en
     * @type api
     * @region  engine management
     * @brief  Releases the resources occupied by the current IAudioDeviceCollection{@link #IAudioDeviceCollection} object.
     * @note This method should be called to release related resources when you do not need to return a list of audio device related information.
     */
    virtual void release()override {};
    /**
     * @locale zh
     * @type api
     * @region 引擎管理
     * @brief 根据索引号，获取设备信息
     * @param index 设备索引号，从 0 开始，注意需小于 getCount{@link #IAudioDeviceCollection#getCount} 返回值。
     * @param [out] audio_device_info 设备信息，详见 AudioDeviceInfo{@link #AudioDeviceInfo}
     * @return  
     *        + 0：方法调用成功  <br>
     *        + !0：方法调用失败  
     */
    /**
     * @locale en
     * @type api
     * @region Engine management
     * @brief According to the index number, get device information
     * @param index Device index number, starting from 0, note that it must be less than the return value of GetCount{@link #IAudioDeviceCollection#getCount}.
     * @param  [out] audio_device_info device info. Refer to AudioDeviceInfo{@link #AudioDeviceInfo} for details.
     * @return   
     *         + 0: Success. <br>
     *         +! 0: failure 
     */
    virtual int getDevice(int index, AudioDeviceInfo* audio_device_info) = 0;
protected:
    /**
     * @locale zh
     * @hidden constructor/destructor
     * @brief 析构函数
     */
    /**
     * @locale en
     * @hidden constructor/destructor
     * @brief Destructor
     */
    virtual ~IAudioDeviceCollection() {};
};

/**
 * @locale zh
 * @hidden(Android,iOS)
 * @type api
 * @brief 音频设备管理类
 */
/**
 * @locale en
 * @hidden(Android,iOS)
 * @type api
 * @brief Audio device management
 */
class IAudioDeviceManager {
public:
    /**
     * @locale zh
     * @hidden constructor/destructor
     * @brief 构造函数
     */
    /**
     * @locale en
     * @hidden constructor/destructor
     * @brief Constructor
     */
    IAudioDeviceManager() {
    }
    /**
     * @locale zh
     * @type api
     * @region 音频设备管理
     * @brief 获取当前系统内音频播放设备列表。如果后续设备有变更，你会收到 `onAudioMediaDeviceStateChanged` 回调通知，然后需要重新调用本接口以获得新的设备列表。
     * @return 包含系统中所有音频播放设备的列表，参看 IAudioDeviceCollection{@link #IAudioDeviceCollection}。<br>
     * 等待超时后会返回空列表。超时时间默认为 10 s。建议通过 onAudioDeviceStateChanged{@link #IRTCVideoEventHandler#onAudioDeviceStateChanged} 监听到 `kMediaDeviceListUpdated` 后，再次调用本接口获取。
     * @note 你可以在收到 onAudioDeviceStateChanged{@link #IRTCVideoEventHandler#onAudioDeviceStateChanged} 了解设备变更后，重新调用本接口以获得新的设备列表。
     */
    /**
     * @locale en
     * @type api
     * @region  Audio device management
     * @brief  Get a list of the audio playback device. When the audio playback device changes, you will receive `onAudioMediaDeviceStateChanged` and you need to call this API again to get the new device list.
     * @return  A list of all audio playback devices. See IAudioDeviceCollection{@link #IAudioDeviceCollection}.<br>
     * If a time-out occurs, it returns an empty list. By default, the time-out duration is set to 10 seconds. We recommend to call this API once you get notification of `kMediaDeviceListUpdated` via onAudioDeviceStateChanged{@link #IRTCVideoEventHandler#onAudioDeviceStateChanged}.
     * @note When receiving onAudioDeviceStateChanged{@link #IRTCVideoEventHandler#onAudioDeviceStateChanged} for device change, you can call this API to get the latest list of audio playback devices.
     */
    virtual IAudioDeviceCollection* enumerateAudioPlaybackDevices() = 0;
    /**
     * @locale zh
     * @type api
     * @region 音频设备管理
     * @brief 获取当前系统内音频采集设备列表。如果后续设备有变更，你需要重新调用本接口以获得新的设备列表。
     * @return 一个包含系统中所有音频采集设备列表的对象，详见 IAudioDeviceCollection{@link #IAudioDeviceCollection}。<br>
     * 等待超时后会返回空列表。超时时间默认为 10 s。建议通过 onAudioDeviceStateChanged{@link #IRTCVideoEventHandler#onAudioDeviceStateChanged} 监听到 `kMediaDeviceListUpdated` 后，再次调用本接口获取。
     * @note 你可以在收到 onAudioDeviceStateChanged{@link #IRTCVideoEventHandler#onAudioDeviceStateChanged} 了解设备变更后，重新调用本接口以获得新的设备列表。
     */
    /**
     * @locale en
     * @type api
     * @region  Audio Facility Management
     * @brief  Get a list of audio acquisition devices in the current system. If there are subsequent device changes, you need to call this interface again to get a new device list.
     * @return An object that contains a list of all audio capture devices in the system. See IAudioDeviceCollection{@link #IAudioDeviceCollection}.<br>
     * If a time-out occurs, it returns an empty list. By default, the time-out duration is set to 10 seconds. We recommend to call this API once you get notification of `kMediaDeviceListUpdated` via onAudioDeviceStateChanged{@link #IRTCVideoEventHandler#onAudioDeviceStateChanged}.
     * @note When receiving onAudioDeviceStateChanged{@link #IRTCVideoEventHandler#onAudioDeviceStateChanged} for device change, you can call this API to get the latest list of audio playback devices.
     */
    virtual IAudioDeviceCollection* enumerateAudioCaptureDevices() = 0;

    /**
     * @locale zh
     * @type api
     * @region 音频设备管理
     * @brief 设置音频播放路由是否跟随系统。
     * @param followed <br>
     *        + true: 跟随。此时，调用 setAudioPlaybackDevice{@link #IAudioDeviceManager#setAudioPlaybackDevice} 会失败。默认值。<br>
     *        + false: 不跟随系统。此时，可以调用 setAudioPlaybackDevice{@link #IAudioDeviceManager#setAudioPlaybackDevice} 进行设置。
     */
    /**
     * @locale en
     * @type api
     * @region Audio Facility Management
     * @brief Set the audio playback device to follow the OS setting or not.
     * @param followed <br>
     *        + true: follow the OS setting. You can not call setAudioPlaybackDevice{@link #IAudioDeviceManager#setAudioPlaybackDevice} at the same time. The default value.<br>
     *        + false: do not follow the OS setting. You can call setAudioPlaybackDevice{@link #IAudioDeviceManager#setAudioPlaybackDevice} to set the audio playback device.
     */
    virtual void followSystemPlaybackDevice(bool followed) = 0;

    /**
     * @locale zh
     * @type api
     * @region 音频设备管理
     * @brief 设置音频采集路由是否跟随系统。
     * @param followed <br>
     *        + true: 跟随。此时，调用 setAudioCaptureDevice{@link #IAudioDeviceManager#setAudioCaptureDevice} 会失败。默认值。<br>
     *        + false: 不跟随系统。此时，可以调用 setAudioCaptureDevice{@link #IAudioDeviceManager#setAudioCaptureDevice} 进行设置。
     */
    /**
     * @locale en
     * @type api
     * @region Audio Facility Management
     * @brief Set the audio capture device to follow the OS setting or not.
     * @param followed <br>
     *        + true: follow the OS setting. You can not call setAudioCaptureDevice{@link #IAudioDeviceManager#setAudioCaptureDevice} at the same time. The default value.<br>
     *        + false: do not follow the OS setting. You can call setAudioCaptureDevice{@link #IAudioDeviceManager#setAudioCaptureDevice} to set the audio capture device.
     */
    virtual void followSystemCaptureDevice(bool followed) = 0;
    /**
     * @locale zh
     * @type api
     * @region 音频设备管理
     * @brief 设置音频播放设备。
     * @param device_id 音频播放设备 ID，可通过 enumerateAudioPlaybackDevices{@link #enumerateAudioPlaybackDevices}<br>
     * 获取。
     * @return   
     *        + 0：方法调用成功  <br>
     *        + < 0：方法调用失败
     * @note 当你调用 followSystemPlaybackDevice{@link #IAudioDeviceManager#followSystemPlaybackDevice} 设置音频播放设备跟随系统后，将无法调用此接口设置音频播放设备。
     */
    /**
     * @locale en
     * @type api
     * @region Audio device management
     * @brief Sets the audio playback device.
     * @param device_id Audio playback device's ID. You can get the ID by calling<br>
     * enumerateAudioPlaybackDevices{@link #enumerateAudioPlaybackDevices}.
     * @return    
     *         + 0: Success <br>
     *         + < 0: Failure 
     * @note After you call followSystemPlaybackDevice{@link #IAudioDeviceManager#followSystemPlaybackDevice} to set the audio playback device to follow the system setting, you cannot call this API to set the audio playback device.
     */
    virtual int setAudioPlaybackDevice(const char device_id[MAX_DEVICE_ID_LENGTH]) = 0;
    /**
     * @locale zh
     * @type api
     * @region 音频设备管理
     * @brief 设置音频采集设备。
     * @param device_id 音频采集设备 ID，可通过 enumerateAudioCaptureDevices{@link #enumerateAudioCaptureDevices} 获取。
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + < 0：方法调用失败
     * @note 当你调用 followSystemCaptureDevice{@link #IAudioDeviceManager#followSystemCaptureDevice} 设置音频采集设备跟随系统后，将无法调用此接口设置音频采集设备。
     */
    /**
     * @locale en
     * @type api
     * @region Audio Facility Management
     * @brief Set up audio capture devices.
     * @param device_id Audio capture device ID, available through enumerateAudioCaptureDevices{@link #enumerateAudioCaptureDevices}.
     * @return  Method call result   <br>
     *         + 0: Success. <br>
     *         + < 0: failure 
     * @note After you call followSystemCaptureDevice{@link #IAudioDeviceManager#followSystemCaptureDevice} to set the audio playback device to follow the system setting, you cannot call this API to set the audio capture device.
     */
    virtual int setAudioCaptureDevice(const char device_id[MAX_DEVICE_ID_LENGTH]) = 0;
    /**
     * @locale zh
     * @type api
     * @region 音频设备管理
     * @brief 设置当前音频播放设备音量
     * @param volume 音频播放设备音量，取值范围为 [0,255], 超出此范围设置无效。<br>
     *       + [0,25] 接近无声；  <br>
     *       + [25,75] 为低音量；  <br>
     *       + [76,204] 为中音量；  <br>
     *       + [205,255] 为高音量。  
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + < 0：方法调用失败
     */
    /**
     * @locale en
     * @type api
     * @region  Audio Facility Management
     * @brief Set the current audio playback device volume
     * @param volume Audio playback device volume, the value range is [0,255], the setting beyond this range is invalid.<br>
     *        + [0,25] Is nearly silent; <br>
     *        + [25,75] Is low volume; <br>
     *        + [76,204] Is medium volume; <br>
     *        + [205,255] Is high volume. 
     * @return   Method call result   <br>
     *         + 0: Success. <br>
     *         + < 0: failure 
     */
    virtual int setAudioPlaybackDeviceVolume(unsigned int volume) = 0;
    /**
     * @locale zh
     * @type api
     * @region 音频设备管理
     * @brief 获取当前音频播放设备音量
     * @param [out] volume 音频播放设备音量，范围应在 [0,255] 内。<br>
     *       + [0,25] 接近无声；  <br>
     *       + [25,75] 为低音量；  <br>
     *       + [76,204] 为中音量；  <br>
     *       + [205,255] 为高音量。  
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + < 0：方法调用失败
     */
    /**
     * @locale en
     * @type api
     * @region Audio Facility Management
     * @brief Get the current audio playback device volume.
     * @param [out] volume Audio playback device volume, the range should be within [0,255].<br>
     *        + [0,25] Is nearly silent; <br>
     *        + [25,75] Is low volume; <br>
     *        + [76,204] Is medium volume; <br>
     *        + [205,255] Is high volume. 
     * @return   Method call result   <br>
     *         + 0: Success. <br>
     *         + < 0: failure 
     */
    virtual int getAudioPlaybackDeviceVolume(unsigned int* volume) = 0;
    /**
     * @locale zh
     * @type api
     * @region 音频设备管理
     * @brief 设置当前音频采集设备音量
     * @param volume 音频采集设备音量，取值范围为 [0,255], 超出此范围设置无效。<br>
     *       + [0,25] 接近无声；  <br>
     *       + [25,75] 为低音量；  <br>
     *       + [76,204] 为中音量；  <br>
     *       + [205,255] 为高音量。  
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + < 0：方法调用失败
     */
    /**
     * @locale en
     * @type api
     * @region  Audio Facility Management
     * @brief Set the current audio capture volume
     * @param volume Audio capture volume, the value range is [0,255], the setting beyond this range is invalid.<br>
     *        + [0,25] Is nearly silent; <br>
     *        + [25,75] Is low volume; <br>
     *        + [76,204] Is medium volume; <br>
     *        + [205,255] Is high volume. 
     * @return   Method call result   <br>
     *         + 0: Success. <br>
     *         + < 0: failure 
     */
    virtual int setAudioCaptureDeviceVolume(unsigned int volume) = 0;
    /**
     * @locale zh
     * @type api
     * @region 音频设备管理
     * @brief 获取当前音频采集设备音量
     * @param [out] volume 音频采集设备音量，范围应在 [0,255] 内。<br>
     *       + [0,25] 接近无声；  <br>
     *       + [25,75] 为低音量；  <br>
     *       + [76,204] 为中音量；  <br>
     *       + [205,255] 为高音量。  
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + < 0：方法调用失败
     */
    /**
     * @locale en
     * @type api
     * @region Audio Facility Management
     * @brief Get the current audio capture volume.
     * @param [out] volume Audio capture volume, the range is within [0,255].<br>
     *        + [0,25] Is nearly silent; <br>
     *        + [25,75] Is low volume; <br>
     *        + [76,204] Is medium volume; <br>
     *        + [205,255] Is high volume. 
     * @return   Method call result   <br>
     *         + 0: Success. <br>
     *         + < 0: failure 
     */
    virtual int getAudioCaptureDeviceVolume(unsigned int* volume) = 0;
    /**
     * @locale zh
     * @type api
     * @region 音频设备管理
     * @brief 设置当前音频播放设备静音状态，默认为非静音。
     * @param mute  <br>
     *       + true：静音  <br>
     *       + false：非静音  
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + < 0：方法调用失败
     */
    /**
     * @locale en
     * @type api
     * @region Audio Facility Management
     * @brief Mute or Unmute the current audio playback device. The default state is speaking.
     * @param mute <br>
     *        + true: Mute <br>
     *        + false: Speaking 
     * @return   Method call result   <br>
     *         + 0: Success. <br>
     *         + < 0: failure 
     */
    virtual int setAudioPlaybackDeviceMute(bool mute) = 0;
    /**
     * @locale zh
     * @type api
     * @region 音频设备管理
     * @brief 获取当前音频播放设备是否静音的信息。
     * @param [out] mute  <br>
     *       + true：静音  <br>
     *       + false：非静音  
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + < 0：方法调用失败
     */
    /**
     * @locale en
     * @type api
     * @region Audio Facility Management
     * @brief Get the mute state of the current audio playback device.
     * @param [out] mute <br>
     *        + true: Mute <br>
     *        + false: Speaking 
     * @return   Method call result   <br>
     *         + 0: Success. <br>
     *         + < 0: failure 
     */
    virtual int getAudioPlaybackDeviceMute(bool* mute) = 0;
    /**
     * @locale zh
     * @type api
     * @region 音频设备管理
     * @brief 设置当前音频采集设备静音状态，默认为非静音。
     * @param mute  <br>
     *       + true：静音  <br>
     *       + false：非静音  
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + < 0：方法调用失败
     */
    /**
     * @locale en
     * @type api
     * @region Audio Facility Management
     * @brief Mute or Unmute the current audio capture device. The default state is speaking.
     * @param mute <br>
     *        + true: Mute <br>
     *        + false: Speaking 
     * @return   Method call result   <br>
     *         + 0: Success. <br>
     *         + < 0: failure 
     */
    virtual int setAudioCaptureDeviceMute(bool mute) = 0;
    /**
     * @locale zh
     * @type api
     * @region 音频设备管理
     * @brief 获取当前音频采集设备是否静音的信息。
     * @param [out] mute  <br>
     *       + true：静音  <br>
     *       + false：非静音  
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + < 0：方法调用失败
     */
    /**
     * @locale en
     * @type api
     * @region Audio Facility Management
     * @brief Get state of the audio capture device.
     * @param [out] mute <br>
     *        + true: Mute <br>
     *        + false: Speaking 
     * @return   Method call result   <br>
     *         + 0: Success. <br>
     *         + < 0: failure 
     */
    virtual int getAudioCaptureDeviceMute(bool* mute) = 0;
    /**
     * @locale zh
     * @type api
     * @region 音频设备管理
     * @brief 获取当前音频播放设备 ID。
     * @param [out] device_id 音频播放设备 ID
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + < 0：方法调用失败
     */
    /**
     * @locale en
     * @type api
     * @region Audio Facility Management
     * @brief Gets the current audio playback device ID.
     * @param [out] device_id Audio playback device ID
     * @return   Method call result   <br>
     *         + 0: Success. <br>
     *         + < 0: failure 
     */
    virtual int getAudioPlaybackDevice(char device_id[MAX_DEVICE_ID_LENGTH]) = 0;
    /**
     * @locale zh
     * @type api
     * @region 音频设备管理
     * @brief 获取当前音频采集设备 ID。
     * @param [out] device_id 音频采集设备 ID，使用方负责按 MAX_DEVICE_ID_LENGTH 大小，分配与释放内存
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + < 0：方法调用失败
     */
    /**
     * @locale en
     * @type api
     * @region Audio Facility Management
     * @brief Gets the current audio capture device ID.
     * @param [out] device_id audio capture device ID. You should allocate and free memory according to the MAX_DEVICE_ID_LENGTH size.
     * @return   Method call result   <br>
     *         + 0: Success. <br>
     *         + < 0: failure 
     */
    virtual int getAudioCaptureDevice(char device_id[MAX_DEVICE_ID_LENGTH]) = 0;
    /**
     * @locale zh
     * @type api
     * @region 音频设备管理
     * @brief 尝试初始化音频播放设备，可检测出设备不存在、权限被拒绝/禁用等异常问题。
     * @param device_id 设备索引号
     * @return 设备状态错误码<br>
     *        + 0: 设备检测结果正常<br>
     *        + -1: 接口状态不正确，例如在正常启动采集后再调用该接口进行检测<br>
     *        + -2: 采集设备无麦克风权限，尝试初始化设备失败<br>
     *        + -3: 设备不存在，当前没有设备或设备被移除时返回<br>
     *        + -4: 设备音频格式不支持<br>
     *        + -5: 其它原因错误
     * @note 1. 该接口需在进房前调用；  <br>
     *        2. 检测成功不代表设备一定可以启动成功，还可能因设备被其他应用进程独占，或 CPU/内存不足等原因导致启动失败。
     */
    /**
     * @locale en
     * @type api
     * @region Audio Facility Management
     * @brief Try to initialize the audio playback device, and you can detect abnormal problems such as the device does not exist, permissions are denied/disabled, etc.
     * @param device_id Device index number
     * @return Device status error code<br>
     *         + 0: device detection result is normal<br>
     *         + -1: The interface status is incorrect, for example, the interface is called for detection after the acquisition is started normally<br>
     *         + -2: The acquisition device does not have microphone permission, and attempts to initialize the device fail<br>
     *         + -3: The device does not exist, there is currently no device or return when the device is removed<br>
     *         + -4: Device audio format not supported<br>
     *         + -5: Error for other reasons
     * @note 1. This interface needs to be called before entering the room; <br>
     *        2. Successful detection does not necessarily mean that the device can be started successfully. It may also fail to start due to the device being monopolized by other application processes, or CPU/memory shortage.
     */
    virtual int initAudioPlaybackDeviceForTest(const char device_id[MAX_DEVICE_ID_LENGTH]) = 0;
    /**
     * @locale zh
     * @type api
     * @region 音频设备管理
     * @brief 尝试初始化音频采集设备，可检测设备不存在、权限被拒绝/禁用等异常问题。
     * @param device_id 设备索引
     * @return 设备状态错误码<br>
     *        + 0: 设备检测结果正常<br>
     *        + -1: 接口状态不正确，例如在正常启动采集后再调用该接口进行检测<br>
     *        + -2: 采集设备无麦克风权限，尝试初始化设备失败<br>
     *        + -3: 设备不存在，当前没有设备或设备被移除时返回<br>
     *        + -4: 设备音频格式不支持<br>
     *        + -5: 其它原因错误
     * @note 1. 该接口需在进房前调用;  <br>
     *        2. 检测成功不代表设备一定可以启动成功，还可能因设备被其他应用进程独占，或 CPU/内存不足等原因导致启动失败。
     */
    /**
     * @locale en
     * @type api
     * @region Audio Facility Management
     * @brief Try to initialize the audio capture device, which can detect abnormal problems such as the device does not exist, permissions are denied/disabled, etc.
     * @param device_id Device index
     * @return Device status error code<br>
     *         + 0: device detection result is normal<br>
     *         + -1: The interface status is incorrect, for example, the interface is called for detection after the acquisition is started normally<br>
     *         + -2: The acquisition device does not have microphone permission, and attempts to initialize the device fail<br>
     *         + -3: The device does not exist, there is currently no device or return when the device is removed<br>
     *         + -4: Device audio format not supported<br>
     *         + -5: Error for other reasons
     * @note 1. This interface needs to be called before entering the room; <br>
     *        2. Successful detection does not necessarily mean that the device can be started successfully. It may also fail to start due to the device being monopolized by other application processes, or CPU/memory shortage.
     */
    virtual int initAudioCaptureDeviceForTest(const char device_id[MAX_DEVICE_ID_LENGTH]) = 0;

    /**
     * @locale zh
     * @type api
     * @region 音频设备管理
     * @brief 启动音频播放设备检测。测试启动后，循环播放指定的音频文件，同时将通过 `onAudioPlaybackDeviceTestVolume` 回调播放时的音量信息。
     * @param test_audio_file_path 指定播放设备检测的音频文件网络地址。支持的格式包括 mp3，aac，m4a，3gp 和 wav。
     * @param indication_interval 设置 `onAudioPlaybackDeviceTestVolume` 音量回调的时间间隔，推荐设置为 200 毫秒或以上。单位为毫秒。最小值为 10 毫秒。
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + < 0：方法调用失败
     * @note  
     *       + 该方法可在进房前和进房后调用，不可与其它音频设备测试功能同时应用。  <br>
     *       + 调用 stopAudioPlaybackDeviceTest{@link #IAudioDeviceManager#stopAudioPlaybackDeviceTest} 可以停止测试。
     */
    /**
     * @locale en
     * @type api
     * @region Audio Facility Management
     * @brief Start the playback test for the local audio device. RTC will start playing the audio file specified. And RTC will notify the audio volume via the `onAudioPlaybackDeviceTestVolume` periodically.
     * @param test_audio_file_path  Specify the path of the audio file for the playback test, including *.mp3, *.aac, *.m4a, *.3gp, and *.wav.
     * @param indication_interval The time interval between each callback in milliseconds. We recommend setting it to 200 ms. The minimal value is 10 ms.
     * @return 
     *         + 0: Success  <br>
     *         + < 0: Failure
     * @note 
     *       + You can call this API whether the user is in the room.   <br>
     *       + Call stopAudioPlaybackDeviceTest{@link #IAudioDeviceManager#stopAudioPlaybackDeviceTest} to stop the playback test before moving on to the other device tests.
     */
     virtual int startAudioPlaybackDeviceTest(const char* test_audio_file_path, int indication_interval) = 0;

    /**
     * @locale zh
     * @type api
     * @region 音频设备管理
     * @brief 停止音频播放测试。  
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + < 0：方法调用失败
     * @note 调用 startAudioPlaybackDeviceTest{@link #IAudioDeviceManager#startAudioPlaybackDeviceTest} 后，调用本方法停止测试。
     */
    /**
     * @locale en
     * @type api
     * @region Audio Facility Management
     * @brief Stop the playback test for the local audio device.
     * @return Result <br>
     *         + 0: Success  <br>
     *         + < 0: Failure
     * @note  Call this API to stop the playback test started by calling startAudioPlaybackDeviceTest{@link #IAudioDeviceManager#startAudioPlaybackDeviceTest} before moving on to the other device tests.
     */
    virtual int stopAudioPlaybackDeviceTest() = 0;

    /**
     * @locale zh
     * @hidden(Android, iOS, Linux)
     * @type api
     * @region 音频设备管理
     * @brief 开始音频采集设备和音频播放设备测试。
     * @param indication_interval 测试中会收到 `onLocalAudioPropertiesReport` 回调，本参数指定了该周期回调的时间间隔，单位为毫秒。建议设置到大于 200 毫秒。最小不得少于 10 毫秒。
     * @return  方法调用结果  <br>
     *       + 0：方法调用成功  <br>
     *       + < 0：方法调用失败  
     * @note  
     *       + 该方法在进房前后均可调用。且不可与其它音频设备测试功能同时应用。  <br>
     *       + 调用本接口 30 s 后，采集自动停止，并开始播放采集到的声音。录音播放完毕后，设备测试流程自动结束。你也可以在 30 s 内调用 stopAudioDeviceRecordAndPlayTest{@link #IAudioDeviceManager#stopAudioDeviceRecordAndPlayTest} 来停止采集并开始播放此前采集到的声音。<br>
     *       + 调用 stopAudioDevicePlayTest{@link #IAudioDeviceManager#stopAudioDevicePlayTest} 可以停止音频设备采集和播放测试。<br>
     *       + 你不应在测试过程中，调用 `enableAudioPropertiesReport` 注册音量提示回调。<br>
     *       + 该方法仅在本地进行音频设备测试，不涉及网络连接。  
     */
    /**
     * @locale en
     * @hidden(Android, iOS, Linux)
     * @type api
     * @region Audio Facility Management
     * @brief Start the capture and playback test for local audio devices.
     * @param indication_interval During the test, you'll receive `onLocalAudioPropertiesReport` periodically. Set the period in ms with this parameter. Recommended value is 200 ms; the minimal value is 10 ms.
     * @return  result<br>
     *         + 0: success  <br>
     *         + < 0: failure  
     * @note  
     *       + The audio capturing stops in 30s after calling this API and begins to play the recording audio. Before that, you can call stopAudioDeviceRecordAndPlayTest{@link #IAudioDeviceManager#stopAudioDeviceRecordAndPlayTest} to stop audio capturing and start playing the recording audio. <br>
     *       + Call stopAudioDevicePlayTest{@link #IAudioDeviceManager#stopAudioDevicePlayTest} to stop the test, including capturing and playing the recording. <br>
     *       + You must stop the test before starting another test for audio devices. <br>
     *       + You must stop the test before calling `enableAudioPropertiesReport`. <br>
     *       + This test performs locally and does not involve network connection testing. 
     */
    virtual int startAudioDeviceRecordTest(int indication_interval) = 0;

    /**
     * @locale zh
     * @hidden(Android, iOS, Linux)
     * @type api
     * @region 音频设备管理
     * @brief 停止采集本地音频，并开始播放采集到的声音。录音播放完毕后，设备测试流程结束。<br>
     *        调用 startAudioDeviceRecordTest{@link #IAudioDeviceManager#startAudioDeviceRecordTest} 30 s 内调用本接口来停止采集并开始播放此前采集到的声音。
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + < 0：方法调用失败
     * @note 调用本接口开始播放录音后，可以在播放过程中调用 stopAudioDevicePlayTest{@link #IAudioDeviceManager#stopAudioDevicePlayTest} 停止播放。
     */
    /**
     * @locale en
     * @hidden(Android, iOS, Linux)
     * @type api
     * @region Audio Facility Management
     * @brief Call this API to stop recording in the test and start to play the recording in 30 s after calling startAudioDeviceRecordTest{@link #IAudioDeviceManager#startAudioDeviceRecordTest}.
     * @return result<br>
     *         + 0: Success  <br>
     *         + < 0: Failure
     * @note After calling this API, the recording starts playing during which you can call stopAudioDevicePlayTest{@link #IAudioDeviceManager#stopAudioDevicePlayTest} to stop playing.
     */
    virtual int stopAudioDeviceRecordAndPlayTest() = 0;

    /**
     * @locale zh
     * @hidden(Android, iOS, Linux)
     * @type api
     * @region 音频设备管理
     * @brief 停止由调用 startAudioDeviceRecordTest{@link #IAudioDeviceManager#startAudioDeviceRecordTest} 开始的音频播放设备测试。<br>
     *        在音频播放设备测试自动结束前，可调用本接口停止音频采集与播放测试。
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + < 0：方法调用失败
     */
    /**
     * @locale en
     * @hidden(Android, iOS, Linux)
     * @type api
     * @region Audio Facility Management
     * @brief Stop the capture and playback test for local audio devices which is started by calling startAudioDeviceRecordTest{@link #IAudioDeviceManager#startAudioDeviceRecordTest}.<br>
     * Before the test ends by itself, you can call this API to stop the recording or playing.
     * @return 
     *         + 0: Success  <br>
     *         + < 0: failure
     */
    virtual int stopAudioDevicePlayTest() = 0;

    /**
     * @locale zh
     * @type api
     * @region 音频设备管理
     * @brief 开启/关闭过滤无声设备功能。
     * @param enable 是否开启过滤无声设备功能:<br>
     *        + 1: 是。<br>
     *        + 0: 否。
     * @return  + 0：方法调用成功。
     */
    /**
     * @locale en
     * @type api
     * @region Audio Facility Management
     * @brief Enables/disables the silent device filter function.
     * @param enable Whether to enable the silent device filter function:<br>
     *        + 1: true.<br>
     *        + 0: false.
     * @return + 0: Success.
     */
    virtual int enableFilterSilentDevice(bool enable) = 0;

    /**
     * @locale zh
     * @hidden constructor/destructor
     * @brief 析构函数
     */
    /**
     * @locale en
     * @hidden constructor/destructor
     * @brief Destructor
     */
    virtual ~IAudioDeviceManager() {
    }
};

}  // namespace bytertc
