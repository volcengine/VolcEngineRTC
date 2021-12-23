/*
 * Copyright (c) 2020 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngine Device Manager
*/

#pragma once

#ifndef BYTE_RTC_DEVICE_MANAGER_H__
#define BYTE_RTC_DEVICE_MANAGER_H__

namespace bytertc {

/**
 * @hidden
 * @brief 设置id最大长度
 */
const unsigned int MAX_DEVICE_ID_LENGTH = 512;

/**
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
     * @type api
     * @region 引擎管理
     * @brief 获取当前系统内音视频设备数量
     * @return 音视频设备数量
     */
    virtual int GetCount() = 0;
    /**
     * @type api
     * @region 引擎管理
     * @brief 根据索引号，获取设备信息
     * @param [in] index 设备索引号，从 0 开始，注意需小于 GetCount{@link #IDeviceCollection#GetCount} 返回值。  
     * @param [out] device_name 设备名称
     * @param [out] device_id 设备 ID
     * @return  <br>
     *        + 0：方法调用成功  <br>
     *        + !0：方法调用失败  <br>
     */
    virtual int GetDevice(int index, char device_name[MAX_DEVICE_ID_LENGTH], char device_id[MAX_DEVICE_ID_LENGTH]) = 0;
    /**
     * @type api
     * @region 引擎管理
     * @brief 释放当前 IDeviceCollection{@link #IDeviceCollection} 对象占用的资源。
     * @notes 不需要返回音视频设备相关信息列表时应该调用本方法释放相关资源。
     */
    virtual void Release() = 0;
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
     * @brief 获取当前系统内音频播放设备列表。如果后续设备有变更，你会收到 OnMediaDeviceStateChanged{@link #OnMediaDeviceStateChanged} 回调通知，然后需要重新调用本接口以获得新的设备列表。
     * @return 包含系统中所有音频播放设备的列表，参看 IDeviceCollection{@link #IDeviceCollection}。
     */
    virtual IDeviceCollection* EnumerateAudioPlaybackDevices() = 0;
    /**
     * @type api
     * @region 音频设备管理
     * @brief 获取当前系统内音频采集设备列表。如果后续设备有变更，你需要重新调用本接口以获得新的设备列表。
     * @return 一个包含系统中所有音频采集设备列表的对象，详见 IDeviceCollection{@link #IDeviceCollection}。
     * @notes 当不再使用返回的对象时，你需要调用 Release{@link #IDeviceCollection#Release} 进行释放。
     */
    virtual IDeviceCollection* EnumerateAudioCaptureDevices() = 0;
    /**
     * @type api
     * @region 音频设备管理
     * @brief 设置音频播放设备。
     * @param [in] device_id 音频播放设备 ID，可通过 EnumerateAudioPlaybackDevices{@link #EnumerateAudioPlaybackDevices} 获取。
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + <0：方法调用失败  <br>
     */
    virtual int SetAudioPlaybackDevice(const char device_id[MAX_DEVICE_ID_LENGTH]) = 0;
    /**
     * @type api
     * @region 音频设备管理
     * @brief 设置音频采集设备。
     * @param [in] device_id 音频采集设备 ID，可通过 EnumerateAudioCaptureDevices{@link #EnumerateAudioCaptureDevices} 获取。
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + <0：方法调用失败  <br>
     */
    virtual int SetAudioCaptureDevice(const char device_id[MAX_DEVICE_ID_LENGTH]) = 0;
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
     *        + <0：方法调用失败  <br>
     */
    virtual int SetAudioPlaybackDeviceVolume(unsigned int volume) = 0;
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
     *        + <0：方法调用失败  <br>
     */
    virtual int GetAudioPlaybackDeviceVolume(unsigned int* volume) = 0;
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
     *        + <0：方法调用失败  <br>
     */
    virtual int SetAudioCaptureDeviceVolume(unsigned int volume) = 0;
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
     *        + <0：方法调用失败  <br>
     */
    virtual int GetAudioCaptureDeviceVolume(unsigned int* volume) = 0;
    /**
     * @type api
     * @region 音频设备管理
     * @brief 设置当前音频播放设备静音状态，默认为非静音。
     * @param [in] mute  <br>
     *       + true：静音  <br>
     *       + false：非静音  <br>
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + <0：方法调用失败  <br>
     */
    virtual int SetAudioPlaybackDeviceMute(bool mute) = 0;
    /**
     * @type api
     * @region 音频设备管理
     * @brief 获取当前音频播放设备是否静音的信息。
     * @param [out] mute  <br>
     *       + true：静音  <br>
     *       + false：非静音  <br>
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + <0：方法调用失败  <br>
     */
    virtual int GetAudioPlaybackDeviceMute(bool* mute) = 0;
    /**
     * @type api
     * @region 音频设备管理
     * @brief 设置当前音频采集设备静音状态，默认为非静音。
     * @param [in] mute  <br>
     *       + true：静音  <br>
     *       + false：非静音  <br>
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + <0：方法调用失败  <br>
     */
    virtual int SetAudioCaptureDeviceMute(bool mute) = 0;
    /**
     * @type api
     * @region 音频设备管理
     * @brief 获取当前音频采集设备是否静音的信息。
     * @param [out] mute  <br>
     *       + true：静音  <br>
     *       + false：非静音  <br>
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + <0：方法调用失败  <br>
     */
    virtual int GetAudioCaptureDeviceMute(bool* mute) = 0;
    /**
     * @type api
     * @region 音频设备管理
     * @brief 获取当前音频播放设备 ID。
     * @param [out] device_id 音频播放设备 ID
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + <0：方法调用失败  <br>
     */
    virtual int GetAudioPlaybackDevice(char device_id[MAX_DEVICE_ID_LENGTH]) = 0;
    /**
     * @type api
     * @region 音频设备管理
     * @brief 获取当前音频采集设备 ID。
     * @param [out] device_id 音频采集设备 ID，使用方负责按 MAX_DEVICE_ID_LENGTH 大小，分配与释放内存
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + <0：方法调用失败  <br>
     */
    virtual int GetAudioCaptureDevice(char device_id[MAX_DEVICE_ID_LENGTH]) = 0;
    /**
     * @type api
     * @region 音频设备管理
     * @brief 启动音频播放设备测试。  <br>
     *        该方法测试播放设备是否能正常工作。SDK 播放指定的音频文件，测试者如果能听到声音，说明播放设备能正常工作。
     * @param [in] test_audio_file_path 音频文件的绝对路径，路径字符串使用 UTF-8 编码格式，支持以下音频格式: mp3，aac，m4a，3gp，wav。
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + <0：方法调用失败  <br>
     * @notes  <br>
     *       + 该方法必须在 JoinRoom{@link #JoinRoom} 前调用，且不可与其它音频设备测试功能同时应用。  <br>
     *       + 你需调用 StopAudioPlaybackDeviceTest{@link #IAudioDeviceManager#StopAudioPlaybackDeviceTest} 停止测试。  <br>
     */
    virtual int StartAudioPlaybackDeviceTest(const char* test_audio_file_path) = 0;
    /**
     * @type api
     * @region 音频设备管理
     * @brief 停止音频播放设备测试。
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + <0：方法调用失败  <br>
     * @notes  调用 StartAudioPlaybackDeviceTest{@link #IAudioDeviceManager#StartAudioPlaybackDeviceTest} 后，需调用本方法停止测试。
     */
    virtual int StopAudioPlaybackDeviceTest() = 0;
    /**
     * @type api
     * @region 音频设备管理
     * @brief 启动音频采集设备测试。  <br>
     *        该方法测试音频采集设备是否能正常工作。启动测试后，会收到 OnAudioVolumeIndication{@link #IRTCRoomEventHandler#OnAudioVolumeIndication} 回调上报的音量信息。
     * @param [in] indication_interval
     *        OnAudioVolumeIndication{@link #IRTCRoomEventHandler#OnAudioVolumeIndication}
     *        回调的时间间隔，单位为毫秒。建议设置到大于 200 毫秒。最小不得少于 10 毫秒。小于10 毫秒行为未定义。
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + <0：方法调用失败  <br>
     * @notes  <br>
     *       + 该方法必须在 JoinRoom{@link #JoinRoom} 前调用，且不可与其它音频设备测试功能同时应用。  <br>
     *       + 你需调用 StopAudioCaptureDeviceTest{@link #IAudioDeviceManager#StopAudioCaptureDeviceTest} 停止测试。  <br>
     */
    virtual int StartAudioCaptureDeviceTest(int indication_interval) = 0;
    /**
     * @type api
     * @region 音频设备管理
     * @brief 停止音频采集设备测试。
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + <0：方法调用失败  <br>
     * @notes  调用 StartAudioCaptureDeviceTest{@link #IAudioDeviceManager#StartAudioCaptureDeviceTest} 后，需调用本方法停止测试。
     */
    virtual int StopAudioCaptureDeviceTest() = 0;
    /**
     * @type api
     * @region 音频设备管理
     * @brief 开始音频设备回路测试。  <br>
     *        该方法测试音频采集设备和音频播放设备是否能正常工作。一旦测试开始，音频采集设备会采集本地声音
     *        并通过音频播放设备播放出来，同时用户 App 会收到 OnAudioVolumeIndication{@link #IRTCRoomEventHandler#OnAudioVolumeIndication}
     *        回调上报的音量信息。
     * @param [in] indication_interval
     *        OnAudioVolumeIndication{@link #IRTCRoomEventHandler#OnAudioVolumeIndication}
     *        回调的时间间隔，单位为毫秒。建议设置到大于 200 毫秒。最小不得少于 10 毫秒。小于 10 毫秒行为未定义。
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + <0：方法调用失败  <br>
     * @notes  <br>
     *       + 该方法必须在 JoinRoom{@link #IRtcEngine#JoinRoom} 前调用。且不可与其它音频设备测试功能同时应用。  <br>
     *       + 你需调用 StopAudioDeviceLoopbackTest{@link #IAudioDeviceManager#StopAudioDeviceLoopbackTest} 停止测试。  <br>
     *       + 该方法仅在本地进行音频设备测试，不涉及网络连接。  <br>
     */
    virtual int StartAudioDeviceLoopbackTest(int indication_interval) = 0;
    /**
     * @type api
     * @region 音频设备管理
     * @brief 停止音频设备回路测试。
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + <0：方法调用失败  <br>
     * @notes 调用 StartAudioDeviceLoopbackTest{@link #IAudioDeviceManager#StartAudioDeviceLoopbackTest} 后，需调用本方法停止测试。
     */
    virtual int StopAudioDeviceLoopbackTest() = 0;
    /**
     * @type api    
     * @region 音频设备管理
     * @brief 尝试初始化音频播放设备，可检测出设备不存在、权限被拒绝/禁用等异常问题。
     * @param [in] index 设备索引号
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
    virtual int InitAudioPlaybackDeviceForTest(const char deviceId[MAX_DEVICE_ID_LENGTH]) = 0;
    /**
     * @type api
     * @region 音频设备管理
     * @brief 尝试初始化音频采集设备，可检测设备不存在、权限被拒绝/禁用等异常问题。
     * @param [in] index 设备索引
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
    virtual int InitAudioCaptureDeviceForTest(const char deviceId[MAX_DEVICE_ID_LENGTH]) = 0;

    /**
     * @hidden
     * @brief 析构函数
     */
    virtual ~IAudioDeviceManager() {
    }
};

}  // namespace bytertc

#endif // BYTE_RTC_DEVICE_MANAGER_H__
