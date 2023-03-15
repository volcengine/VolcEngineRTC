/*
 * Copyright (c) 2020 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC Audio Device Manager
*/

#pragma once

#include "bytertc_audio_defines.h"

namespace bytertc {

/** 
 * @hidden
 * @type api
 * @region 引擎管理
 * @brief 音视频设备相关的信息
 */
class IDeviceCollection {
public:
    /** 
     * @hidden
     * @brief 构造函数
     */
    IDeviceCollection() {
    }
    /** 
     * @hidden
     * @type api
     * @region 引擎管理
     * @brief 获取当前系统内音视频设备数量
     * @return 音视频设备数量
     */
    virtual int getCount() = 0;
    /** 
     * @hidden
     * @type api
     * @region 引擎管理
     * @brief 根据索引号，获取设备信息
     * @param [in] index 设备索引号，从 0 开始，注意需小于 getCount{@link #IAudioDeviceCollection#getCount} 返回值。
     * @param [out] device_name 设备名称
     * @param [out] device_id 设备 ID
     * @return  <br>
     *        + 0：方法调用成功  <br>
     *        + !0：方法调用失败  <br>
     */
    virtual int getDevice(int index, char device_name[MAX_DEVICE_ID_LENGTH], char device_id[MAX_DEVICE_ID_LENGTH]) = 0;
    /** 
     * @hidden
     * @type api
     * @region 引擎管理
     * @brief 释放当前 IAudioDeviceCollection{@link #IAudioDeviceCollection} 对象占用的资源。
     * @notes 不需要返回音视频设备相关信息列表时应该调用本方法释放相关资源。
     */
    virtual void release() = 0;
/**
 * @hidden
 */
protected:
    /** 
     * @hidden
     * @brief 析构函数
     */
    virtual ~IDeviceCollection() {
    }
};

/** 
 * @type api
 * @region 引擎管理
 * @brief 音频设备相关的信息
 */
class IAudioDeviceCollection : public IDeviceCollection {
public:
    /** 
     * @hidden
     * @brief 构造函数
     */
    IAudioDeviceCollection() {};
    /** 
     * @type api
     * @region 引擎管理
     * @brief 获取当前系统内音频设备数量
     * @return 音频设备数量
     */
    virtual int getCount() override {return 0;};
    /** 
     * @type api
     * @region 引擎管理
     * @brief 根据索引号，获取设备信息
     * @param [in] index 设备索引号，从 0 开始，注意需小于 getCount{@link #IAudioDeviceCollection#getCount} 返回值。
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
     * @brief 释放当前 IAudioDeviceCollection{@link #IAudioDeviceCollection} 对象占用的资源。
     * @notes 不需要返回音频设备相关信息列表时应该调用本方法释放相关资源。
     */
    virtual void release()override {};
    /** 
     * @type api
     * @region 引擎管理
     * @brief 根据索引号，获取设备信息
     * @param [in] index 设备索引号，从 0 开始，注意需小于 getCount{@link #IAudioDeviceCollection#getCount} 返回值。
     * @param [out] audio_device_info 设备信息，详见 AudioDeviceInfo{@link #AudioDeviceInfo}
     * @return  <br>
     *        + 0：方法调用成功  <br>
     *        + !0：方法调用失败  <br>
     */
    virtual int getDevice(int index, AudioDeviceInfo* audio_device_info) = 0;
protected:
    /** 
     * @hidden
     * @brief 析构函数
     */
    virtual ~IAudioDeviceCollection() {};
};

/** 
 * @type api
 * @brief 音频设备管理类
 */
class IAudioDeviceManager {
public:
    /** 
     * @hidden
     * @brief 构造函数
     */
    IAudioDeviceManager() {
    }
    /** 
     * @type api
     * @region 音频设备管理
     * @brief 获取当前系统内音频播放设备列表。如果后续设备有变更，你会收到 `onAudioMediaDeviceStateChanged` 回调通知，然后需要重新调用本接口以获得新的设备列表。
     * @return 包含系统中所有音频播放设备的列表，参看 IAudioDeviceCollection{@link #IAudioDeviceCollection}。
     */
    virtual IAudioDeviceCollection* enumerateAudioPlaybackDevices() = 0;
    /** 
     * @type api
     * @region 音频设备管理
     * @brief 获取当前系统内音频采集设备列表。如果后续设备有变更，你需要重新调用本接口以获得新的设备列表。
     * @return 一个包含系统中所有音频采集设备列表的对象，详见 IAudioDeviceCollection{@link #IAudioDeviceCollection}。
     */
    virtual IAudioDeviceCollection* enumerateAudioCaptureDevices() = 0;

    /** 
     * @type api
     * @region 音频设备管理
     * @brief 设置音频播放路由是否跟随系统。
     * @param followed <br>
     *        + true: 跟随。此时，调用 setAudioPlaybackDevice{@link #IAudioDeviceManager#setAudioPlaybackDevice} 会失败。
     *        + false: 不跟随系统。此时，可以调用 setAudioPlaybackDevice{@link #IAudioDeviceManager#setAudioPlaybackDevice} 进行设置。
     */
    virtual void followSystemPlaybackDevice(bool followed) = 0;

    /** 
     * @type api
     * @region 音频设备管理
     * @brief 设置音频采集路由是否跟随系统。
     * @param followed <br>
     *        + true: 跟随。此时，调用 setAudioCaptureDevice{@link #IAudioDeviceManager#setAudioCaptureDevice} 会失败。
     *        + false: 不跟随系统。此时，可以调用 setAudioCaptureDevice{@link #IAudioDeviceManager#setAudioCaptureDevice} 进行设置。
     */
    virtual void followSystemCaptureDevice(bool followed) = 0;
    /** 
     * @type api
     * @region 音频设备管理
     * @brief 设置音频播放设备。
     * @param [in] device_id 音频播放设备 ID，可通过 enumerateAudioPlaybackDevices{@link #enumerateAudioPlaybackDevices}
     * 获取。
     * @return   <br>
     *        + 0：方法调用成功  <br>
     *        + < 0：方法调用失败
     * @notes 当你调用 followSystemPlaybackDevice{@link #IAudioDeviceManager#followSystemPlaybackDevice} 设置音频播放设备跟随系统后，将无法调用此接口设置音频播放设备。
     */
    virtual int setAudioPlaybackDevice(const char device_id[MAX_DEVICE_ID_LENGTH]) = 0;
    /** 
     * @type api
     * @region 音频设备管理
     * @brief 设置音频采集设备。
     * @param [in] device_id 音频采集设备 ID，可通过 enumerateAudioCaptureDevices{@link #enumerateAudioCaptureDevices} 获取。
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + < 0：方法调用失败
     * @notes 当你调用 followSystemCaptureDevice{@link #IAudioDeviceManager#followSystemCaptureDevice} 设置音频采集设备跟随系统后，将无法调用此接口设置音频采集设备。
     */
    virtual int setAudioCaptureDevice(const char device_id[MAX_DEVICE_ID_LENGTH]) = 0;
    /** 
     * @type api
     * @region 音频设备管理
     * @brief 设置当前音频播放设备音量
     * @param [in] volume 音频播放设备音量，取值范围为 [0,255], 超出此范围设置无效。
     *       + [0,25] 接近无声；  <br>
     *       + [25,75] 为低音量；  <br>
     *       + [76,204] 为中音量；  <br>
     *       + [205,255] 为高音量。  <br>
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + < 0：方法调用失败
     */
    virtual int setAudioPlaybackDeviceVolume(unsigned int volume) = 0;
    /** 
     * @type api
     * @region 音频设备管理
     * @brief 获取当前音频播放设备音量
     * @param [out] volume 音频播放设备音量，范围应在 [0,255] 内。
     *       + [0,25] 接近无声；  <br>
     *       + [25,75] 为低音量；  <br>
     *       + [76,204] 为中音量；  <br>
     *       + [205,255] 为高音量。  <br>
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + < 0：方法调用失败
     */
    virtual int getAudioPlaybackDeviceVolume(unsigned int* volume) = 0;
    /** 
     * @type api
     * @region 音频设备管理
     * @brief 设置当前音频采集设备音量
     * @param [in] volume 音频采集设备音量，取值范围为 [0,255], 超出此范围设置无效。
     *       + [0,25] 接近无声；  <br>
     *       + [25,75] 为低音量；  <br>
     *       + [76,204] 为中音量；  <br>
     *       + [205,255] 为高音量。  <br>
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + < 0：方法调用失败
     */
    virtual int setAudioCaptureDeviceVolume(unsigned int volume) = 0;
    /** 
     * @type api
     * @region 音频设备管理
     * @brief 获取当前音频采集设备音量
     * @param [out] volume 音频采集设备音量，范围应在 [0,255] 内。
     *       + [0,25] 接近无声；  <br>
     *       + [25,75] 为低音量；  <br>
     *       + [76,204] 为中音量；  <br>
     *       + [205,255] 为高音量。  <br>
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + < 0：方法调用失败
     */
    virtual int getAudioCaptureDeviceVolume(unsigned int* volume) = 0;
    /** 
     * @type api
     * @region 音频设备管理
     * @brief 设置当前音频播放设备静音状态，默认为非静音。
     * @param [in] mute  <br>
     *       + true：静音  <br>
     *       + false：非静音  <br>
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + < 0：方法调用失败
     */
    virtual int setAudioPlaybackDeviceMute(bool mute) = 0;
    /** 
     * @type api
     * @region 音频设备管理
     * @brief 获取当前音频播放设备是否静音的信息。
     * @param [out] mute  <br>
     *       + true：静音  <br>
     *       + false：非静音  <br>
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + < 0：方法调用失败
     */
    virtual int getAudioPlaybackDeviceMute(bool* mute) = 0;
    /** 
     * @type api
     * @region 音频设备管理
     * @brief 设置当前音频采集设备静音状态，默认为非静音。
     * @param [in] mute  <br>
     *       + true：静音  <br>
     *       + false：非静音  <br>
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + < 0：方法调用失败
     */
    virtual int setAudioCaptureDeviceMute(bool mute) = 0;
    /** 
     * @type api
     * @region 音频设备管理
     * @brief 获取当前音频采集设备是否静音的信息。
     * @param [out] mute  <br>
     *       + true：静音  <br>
     *       + false：非静音  <br>
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + < 0：方法调用失败
     */
    virtual int getAudioCaptureDeviceMute(bool* mute) = 0;
    /** 
     * @type api
     * @region 音频设备管理
     * @brief 获取当前音频播放设备 ID。
     * @param [out] device_id 音频播放设备 ID
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + < 0：方法调用失败
     */
    virtual int getAudioPlaybackDevice(char device_id[MAX_DEVICE_ID_LENGTH]) = 0;
    /** 
     * @type api
     * @region 音频设备管理
     * @brief 获取当前音频采集设备 ID。
     * @param [out] device_id 音频采集设备 ID，使用方负责按 MAX_DEVICE_ID_LENGTH 大小，分配与释放内存
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + < 0：方法调用失败
     */
    virtual int getAudioCaptureDevice(char device_id[MAX_DEVICE_ID_LENGTH]) = 0;
    /** 
     * @type api
     * @region 音频设备管理
     * @brief 尝试初始化音频播放设备，可检测出设备不存在、权限被拒绝/禁用等异常问题。
     * @param [in] deviceId 设备索引号
     * @return 设备状态错误码
     *        + 0: 设备检测结果正常
     *        + -1: 接口状态不正确，例如在正常启动采集后再调用该接口进行检测
     *        + -2: 采集设备无麦克风权限，尝试初始化设备失败
     *        + -3: 设备不存在，当前没有设备或设备被移除时返回
     *        + -4: 设备音频格式不支持
     *        + -5: 其它原因错误
     * @notes 1. 该接口需在进房前调用；  <br>
     *        2. 检测成功不代表设备一定可以启动成功，还可能因设备被其他应用进程独占，或 CPU/内存不足等原因导致启动失败。
     */
    virtual int initAudioPlaybackDeviceForTest(const char deviceId[MAX_DEVICE_ID_LENGTH]) = 0;
    /** 
     * @type api
     * @region 音频设备管理
     * @brief 尝试初始化音频采集设备，可检测设备不存在、权限被拒绝/禁用等异常问题。
     * @param [in] deviceId 设备索引
     * @return 设备状态错误码
     *        + 0: 设备检测结果正常
     *        + -1: 接口状态不正确，例如在正常启动采集后再调用该接口进行检测
     *        + -2: 采集设备无麦克风权限，尝试初始化设备失败
     *        + -3: 设备不存在，当前没有设备或设备被移除时返回
     *        + -4: 设备音频格式不支持
     *        + -5: 其它原因错误
     * @notes 1. 该接口需在进房前调用;  <br>
     *        2. 检测成功不代表设备一定可以启动成功，还可能因设备被其他应用进程独占，或 CPU/内存不足等原因导致启动失败。
     */
    virtual int initAudioCaptureDeviceForTest(const char deviceId[MAX_DEVICE_ID_LENGTH]) = 0;

    /** 
     * @type api
     * @region 音频设备管理
     * @brief 启动音频播放设备检测。测试启动后，循环播放指定的音频文件，同时将通过 `onAudioPlaybackDeviceTestVolume` 回调播放时的音量信息。
     * @param [in] test_audio_file_path 指定播放设备检测的音频文件网络地址。支持的格式包括 mp3，aac，m4a，3gp 和 wav。
     * @param [in] indication_interval 设置 `onAudioPlaybackDeviceTestVolume` 音量回调的时间间隔，推荐设置为 200 毫秒或以上。单位为毫秒。最小值为 10 毫秒。
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + < 0：方法调用失败
     * @notes  <br>
     *       + 该方法可在进房前和进房后调用，不可与其它音频设备测试功能同时应用。  <br>
     *       + 调用 stopAudioPlaybackDeviceTest{@link #IAudioDeviceManager#stopAudioPlaybackDeviceTest} 可以停止测试。
     */
    virtual int startAudioPlaybackDeviceTest(const char* test_audio_file_path, int indication_interval) = 0;

    /** 
    * @type api
    * @region 音频设备管理
    * @brief 停止音频播放测试。  <br>
    * @return  方法调用结果  <br>
    *        + 0：方法调用成功  <br>
    *        + < 0：方法调用失败
    * @notes 调用 startAudioPlaybackDeviceTest{@link #IAudioDeviceManager#startAudioPlaybackDeviceTest} 后，调用本方法停止测试。
    */
    virtual int stopAudioPlaybackDeviceTest() = 0;

    /** 
     * @type api
     * @region 音频设备管理
     * @brief 开始音频采集设备和音频播放设备测试。<br>
     *        建议提前调用 `enableAudioPropertiesReport` 启用音频信息提示，测试开始后，音频设备开始采集本地声音，可以通过 `onLocalAudioPropertiesReport` 获取采集音量。<br>
     * @param [in] indication_interval 测试录音播放时触发 `onLocalAudioPropertiesReport` 播放音量回调，本参数指定了该周期回调的时间间隔，单位为毫秒。建议设置到大于 200 毫秒。最小不得少于 10 毫秒。
     * @return  方法调用结果  <br>
     *       + 0：方法调用成功  <br>
     *       + < 0：方法调用失败
     * @notes  <br>
     *       + 该方法在进房前后均可调用。且不可与其它音频设备测试功能同时应用。  <br>
     *       + 调用本接口 30 s 后，采集自动停止，并开始播放采集到的声音。录音播放完毕后，设备测试流程自动结束。你也可以在 30 s 内调用 stopAudioDeviceRecordAndPlayTest{@link #IAudioDeviceManager#stopAudioDeviceRecordAndPlayTest}  来停止采集并开始播放此前采集到的声音。<br>
     *       + 调用 stopAudioDevicePlayTest{@link #IAudioDeviceManager#stopAudioDevicePlayTest} 可以停止音频设备采集和播放测试。<br>
     *       + 该方法仅在本地进行音频设备测试，不涉及网络连接。  <br>
     */
    virtual int startAudioDeviceRecordTest(int indication_interval) = 0;

    /** 
     * @type api
     * @region 音频设备管理
     * @brief 停止采集本地音频，并开始播放采集到的声音。录音播放完毕后，设备测试流程结束。<br>
     * 调用 startAudioDeviceRecordTest{@link #IAudioDeviceManager#startAudioDeviceRecordTest} 30 s 内调用本接口来停止采集并开始播放此前采集到的声音。
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + < 0：方法调用失败
     * @notes 调用本接口开始播放录音后，可以在播放过程中调用 stopAudioDevicePlayTest{@link #IAudioDeviceManager#stopAudioDevicePlayTest} 停止播放。
     */
    virtual int stopAudioDeviceRecordAndPlayTest() = 0;

    /** 
     * @type api
     * @region 音频设备管理
     * @brief 停止由调用 startAudioDeviceRecordTest{@link #IAudioDeviceManager#startAudioDeviceRecordTest} 开始的音频播放设备测试。<br>
     *        在音频播放设备测试自动结束前，可调用本接口停止音频采集与播放测试。
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + < 0：方法调用失败
     */
    virtual int stopAudioDevicePlayTest() = 0;

    /** 
     * @hidden
     * @brief 析构函数
     */
    virtual ~IAudioDeviceManager() {
    }
};

}  // namespace bytertc
