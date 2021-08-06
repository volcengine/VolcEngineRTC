//
//  byte_rtc_deivce_manager.h
//
//  Copyright (c) 2021. All rights reserved.
//

#pragma once


namespace bytertc {

/**
 * @hidden
 * @brief 设置id最大长度
 */
const unsigned int MAX_DEVICE_ID_LENGTH = 512;

#ifndef BYTERTC_AUDIO_ONLY


/**
 * @type api
 * @region 视频设备管理
 * @brief 获取视频设备相关的信息
 */
class IVideoDeviceCollection {
public:
    /**
     * @hidden
     * @brief 构造函数
     */
    IVideoDeviceCollection() {
    }

    /**
     * @type api
     * @region 视频设备管理
     * @brief 获取当前系统内视频采集设备数量
     * @return 视频采集设备数量
     */
    virtual int GetCount() = 0;

    /**
     * @type api
     * @region 视频设备管理
     * @brief 根据索引号，获取设备信息
     * @param [in] index
     *       视频设备索引号，从0开始， 注意小于GetCount{@link #IVideoDeviceCollection#GetCount}返回值
     * @param [out] device_name
     *       视频设备名称
     * @param [out] device_id
     *       视频设备ID
     * @return  <br>
     *        + 0：方法调用成功  <br>
     *        + !0：方法调用失败  <br>
     * @notes 使用方负责按MAX_DEVICE_ID_LENGTH大小，分配与释放内存
     */
    virtual int GetDevice(int index, char device_name[MAX_DEVICE_ID_LENGTH], char device_id[MAX_DEVICE_ID_LENGTH]) = 0;

    /**
     * @type api
     * @region 视频设备管理
     * @brief 释放当前IVideoDeviceCollection{@link #IVideoDeviceCollection}对象占用的资源
     * @notes  该结构不需要的时候应该调用本函数释放视频操作相关的资源
     */
    virtual void Release() = 0;

protected:
    /**
     * @hidden
     * @brief 析构函数
     */
    virtual ~IVideoDeviceCollection() {
    }
};

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
     * @brief 获取当前系统视频设备列表
     * @return 一个包含系统中所有视频设备列表的对象，详见 IVideoDeviceCollection{@link #IVideoDeviceCollection}
     * @notes  <br>
     *       + 该方法返回一个IVideoDeviceCollection{@link #IVideoDeviceCollection}对象，可以通过该对象枚举系统中视频设备  <br>
     *       + 不再使用返回的对象时，调用IVideoDeviceCollection{@link #IVideoDeviceCollection}对象的Release{@link #IVideoDeviceCollection#Release}进行释放  <br>
     */
    virtual IVideoDeviceCollection* EnumerateVideoDevices() = 0;

    /**
     * @type api
     * @region 视频设备管理
     * @brief 设置当前视频采集设备
     * @param [in] device_id
     *       视频设备ID，可以通过EnumerateVideoDevices{@link #EnumerateVideoDevices}获取
     * @return  <br>
     *        + 0：方法调用成功  <br>
     *        + !0：方法调用失败  <br>
     */
    virtual int SetDevice(const char device_id[MAX_DEVICE_ID_LENGTH]) = 0;

    /**
     * @type api
     * @region 视频设备管理
     * @brief 获取当前SDK正在使用的设备信息
     * @param [out] device_id
     *       视频设备ID
     * @return  <br>
     *        + 0：方法调用成功  <br>
     *        + !0：方法调用失败  <br>
     * @notes 使用方负责按MAX_DEVICE_ID_LENGTH大小，分配与释放内存
     */
    virtual int GetDevice(char device_id[MAX_DEVICE_ID_LENGTH]) = 0;

    /**
     * @type api
     * @region 视频设备管理
     * @brief 释放当前IVideoDeviceManager{@link #IVideoDeviceManager}
     * @notes 不需要的时候应该调用本函数释放视频设备管理实例
     */
    virtual void Release() = 0;

protected:
    /**
     * @hidden
     * @brief 析构函数
     */
    virtual ~IVideoDeviceManager() {
    }
};

#endif  // BYTERTC_AUDIO_ONLY

/**
 * @type api
 * @brief 音频设备列表。
 *        EnumeratePlaybackDevices{@link #IAudioDeviceManager#EnumeratePlaybackDevices} 返回音频播放设备列表。
 *        EnumerateRecordingDevices{@link #IAudioDeviceManager#EnumerateRecordingDevices} 返回音频采集设备列表。
 */
class IAudioDeviceCollection {
public:
    /**
     * @hidden
     * @region 音频设备管理
     * @brief 构造函数
     */
    IAudioDeviceCollection() {
    }

    /**
     * @type api
     * @region 音频设备管理
     * @brief 获取设备列表中设备个数
     * @return 设备列表中设备个数
     * @notes  <br>
     *       + 当本集合是播放设备集合时返回播放设备，当是音频采集设备集合时返回音频采集设备  <br>
     *       + 如果音频播放设备有变更，你需要重新调用 EnumeratePlaybackDevices{@link #IAudioDeviceManager#EnumeratePlaybackDevices} 以获得新的设备列表.  <br>
     *       + 如果音频采集设备有变更，你需要重新调用 EnumerateRecordingDevices{@link #IAudioDeviceManager#EnumerateRecordingDevices} 以获得新的设备列表.  <br>
     */
    virtual int GetCount() = 0;

    /**
     * @type api
     * @region 音频设备管理
     * @brief 根据索引，获取当前设备列表中设备信息
     * @param [in] index
     *        设备索引号，从0开始，注意小于 GetCount{@link #IAudioDeviceCollection#GetCount}返回值
     * @param [out] device_name
     *        设备名称，使用方负责按 MAX_DEVICE_ID_LENGTH 大小，分配与释放内存
     * @param [out] device_id
     *        设备ID，使用方负责按 MAX_DEVICE_ID_LENGTH 大小，分配与释放内存
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + <0：方法调用失败  <br>
     * @notes  <br>
     *       + 当本集合是播放设备集合时返回播放设备，当是音频采集设备集合时返回音频采集设备  <br>
     *       + 如果音频播放设备有变更，你需要重新调用 EnumeratePlaybackDevices{@link #IAudioDeviceManager#EnumeratePlaybackDevices} 以获得新的设备列表.  <br>
     *       + 如果音频采集设备有变更，你需要重新调用 EnumerateRecordingDevices{@link #IAudioDeviceManager#EnumerateRecordingDevices} 以获得新的设备列表.  <br>
     */
    virtual int GetDevice(int index, char device_name[MAX_DEVICE_ID_LENGTH], char device_id[MAX_DEVICE_ID_LENGTH]) = 0;

    /**
     * @type api
     * @region 音频设备管理
     * @brief 析构当前对象，释放内存
     * @notes 严禁调用 delete 该结构体，该结构不需要的时候应该调用本函数释放音频操作相关的资源
     */
    virtual void Release() = 0;

protected:
    /**
     * @hidden
     * @brief 析构函数
     */
    virtual ~IAudioDeviceCollection() {
    }
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
     * @brief 创建音频播放设备列表，该集合包含你调用本接口时系统中的音频播放设备。如果后续设备有变更，你需要重新调用本接口以获得新的设备列表.
     * @return 音频播放设备列表，详见 IAudioDeviceCollection{@link #IAudioDeviceCollection}
     * @notes 当不再使用返回的列表时，需要使用 Release{@link #IAudioDeviceCollection#Release} 进行释放
     */
    virtual IAudioDeviceCollection* EnumeratePlaybackDevices() = 0;

    /**
     * @type api
     * @region 音频设备管理
     * @brief 创建音频采集设备列表，该集合包含你调用本接口时系统中的音频采集设备。如果后续设备有变更，你需要重新调用本接口以获得新的设备列表.
     * @return 音频采集设备列表，详见 IAudioDeviceCollection{@link #IAudioDeviceCollection}
     * @notes 当不再使用返回的列表时，需要使用 Release{@link #IAudioDeviceCollection#Release} 进行释放
     */
    virtual IAudioDeviceCollection* EnumerateRecordingDevices() = 0;

    /**
     * @type api
     * @region 音频设备管理
     * @brief 设置音频播放设备
     * @param [in] device_id
     *        音频播放设备ID, 可通过 EnumeratePlaybackDevices{@link #EnumeratePlaybackDevices} 获取。
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + <0：方法调用失败  <br>
     */
    virtual int SetPlaybackDevice(const char device_id[MAX_DEVICE_ID_LENGTH]) = 0;

    /**
     * @type api
     * @region 音频设备管理
     * @brief 设置音频采集设备
     * @param [in] device_id
     *        音频采集设备ID, 可通过 EnumerateRecordingDevices{@link #EnumerateRecordingDevices} 获取。
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + <0：方法调用失败  <br>
     */
    virtual int SetRecordingDevice(const char device_id[MAX_DEVICE_ID_LENGTH]) = 0;

    /**
     * @type api
     * @region 音频设备管理
     * @brief 设置音频播放设备音量
     * @param [in] volume
     *        音频播放设备音量, 取值范围 [0,255], 超出此范围设置无效
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + <0：方法调用失败  <br>
     */
    virtual int SetPlaybackDeviceVolume(unsigned int volume) = 0;

    /**
     * @type api
     * @region 音频设备管理
     * @brief 获取音频播放设备音量
     * @param [out] volume
     *        音频播放设备音量, 取值范围 [0,255]
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + <0：方法调用失败  <br>
     */
    virtual int GetPlaybackDeviceVolume(unsigned int* volume) = 0;

    /**
     * @type api
     * @region 音频设备管理
     * @brief 设置音频采集设备音量
     * @param [in] volume
     *       音频采集设备音量, 取值范围 [0,255], 超出此范围设置无效
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + <0：方法调用失败  <br>
     */
    virtual int SetRecordingDeviceVolume(unsigned int volume) = 0;

    /**
     * @type api
     * @region 音频设备管理
     * @brief 获取音频采集设备音量
     * @param [out] volume
     *        音频采集设备音量, 取值范围 [0,255]
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + <0：方法调用失败  <br>
     */
    virtual int GetRecordingDeviceVolume(unsigned int* volume) = 0;

    /**
     * @type api
     * @region 音频设备管理
     * @brief 设置音频播放设备静音，默认为非静音。
     * @param  [in] mute  <br>
     *       + true：静音  <br>
     *       + false：非静音  <br>
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + <0：方法调用失败  <br>
     */
    virtual int SetPlaybackDeviceMute(bool mute) = 0;

    /**
     * @type api
     * @region 音频设备管理
     * @brief 获取音频播放设备静音信息
     * @param  [out] mute  <br>
     *       + true：静音  <br>
     *       + false：非静音  <br>
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + <0：方法调用失败  <br>
     */
    virtual int GetPlaybackDeviceMute(bool* mute) = 0;

    /**
     * @type api
     * @region 音频设备管理
     * @brief 设置音频采集设备静音，默认为非静音
     * @param  [in] mute  <br>
     *       + true：静音  <br>
     *       + false：非静音  <br>
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + <0：方法调用失败  <br>
     */
    virtual int SetRecordingDeviceMute(bool mute) = 0;

    /**
     * @type api
     * @region 音频设备管理
     * @brief 获取音频采集设备静音信息
     * @param  [out] mute  <br>
     *       + true：静音  <br>
     *       + false：非静音  <br>
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + <0：方法调用失败  <br>
     */
    virtual int GetRecordingDeviceMute(bool* mute) = 0;

    /**
     * @type api
     * @region 音频设备管理
     * @brief 获取当前使用的音频播放设备ID
     * @param [out] device_id
     *        设备ID，使用方负责按 MAX_DEVICE_ID_LENGTH 大小，分配与释放内存
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + <0：方法调用失败  <br>
     */
    virtual int GetPlaybackDevice(char device_id[MAX_DEVICE_ID_LENGTH]) = 0;

    /**
     * @type api
     * @region 音频设备管理
     * @brief 获取当前音频播放设备信息
     * @param [out] device_id
     *       设备ID，使用方负责按 MAX_DEVICE_ID_LENGTH 大小，分配与释放内存
     * @param [out] device_name
     *       设备名称，使用方负责按 MAX_DEVICE_ID_LENGTH 大小，分配与释放内存
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + <0：方法调用失败  <br>
     * @notes  <br>
     *       + 注意参数前后顺序，设备ID在前，设备名称在后  <br>
     *       + 该接口可能会废弃，请使用 GetPlaybackDevice{@link #IAudioDeviceManager#GetPlaybackDevice}  <br>
     */
    virtual int GetPlaybackDeviceInfo(char device_id[MAX_DEVICE_ID_LENGTH], char device_name[MAX_DEVICE_ID_LENGTH]) = 0;

    /**
     * @type api
     * @region 音频设备管理
     * @brief 获取当前音频采集设备ID
     * @param [out] device_id
     *        设备ID，使用方负责按 MAX_DEVICE_ID_LENGTH 大小，分配与释放内存
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + <0：方法调用失败  <br>
     */
    virtual int GetRecordingDevice(char device_id[MAX_DEVICE_ID_LENGTH]) = 0;

    /**
     * @type api
     * @region 音频设备管理
     * @brief 获取当前音频采集设备信息
     * @param [out] device_id
     *       设备ID，使用方负责按 MAX_DEVICE_ID_LENGTH 大小，分配与释放内存
     * @param [out] device_name
     *       设备名称，使用方负责按 MAX_DEVICE_ID_LENGTH 大小，分配与释放内存
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + <0：方法调用失败  <br>
     * @notes  <br>
     *       + 注意参数前后顺序，设备ID在前，设备名称在后  <br>
     *       + 该接口可能会废弃，请使用 GetRecordingDevice{@link #IAudioDeviceManager#GetRecordingDevice}  <br>
     */
    virtual int GetRecordingDeviceInfo(
            char device_id[MAX_DEVICE_ID_LENGTH], char device_name[MAX_DEVICE_ID_LENGTH]) = 0;

    /**
     * @type api
     * @region 音频设备管理
     * @brief 启动音频播放设备测试
     *        该方法测试播放设备是否能正常工作。SDK 播放指定的音频文件，测试者如果能听到声音，说明播放设备能正常工作。
     * @param [in] test_audio_file_path
     *        音频文件的绝对路径，路径字符串使用 UTF-8 编码格式，支持以下音频格式: mp3，aac，m4a，3gp，wav
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + <0：方法调用失败  <br>
     * @notes  <br>
     *       + 测试功能必须在 JoinChannel{@link #IRtcEngine#JoinChannel} 前应用，且不可与其它音频设备测试功能同时应用。  <br>
     *       + 使用 StopPlaybackDeviceTest{@link #IAudioDeviceManager#StopPlaybackDeviceTest} 停止测试。  <br>
     */
    virtual int StartPlaybackDeviceTest(const char* test_audio_file_path) = 0;

    /**
     * @type api
     * @region 音频设备管理
     * @brief 停止音频播放设备测试。
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + <0：方法调用失败  <br>
     * @notes  调用 StartPlaybackDeviceTest{@link #StartPlaybackDeviceTest} 后，调用本方法停止测试。
     */
    virtual int StopPlaybackDeviceTest() = 0;

    /**
     * @type api
     * @region 音频设备管理
     * @brief 启动音频采集设备测试。
     *        该方法测试音频采集是否能正常工作，启动测试后，SDK 通过 OnAudioVolumeIndication{@link
     *        #IRTCRoomEventHandler#OnAudioVolumeIndication} 回调方法向应用上报音量信息
     * @param [in] indication_interval
     *        OnAudioVolumeIndication{@link #IRTCRoomEventHandler#OnAudioVolumeIndication}
     *        回调的时间间隔，单位为毫秒。建议设置到大于 200 毫秒。最小不得少于 10 毫秒。小于10ms行为未定义
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + <0：方法调用失败  <br>
     * @notes  <br>
     *       + 测试功能必须在 JoinChannel{@link #IRtcEngine#JoinChannel} 前应用。且不可与其它音频设备测试功能同时应用。  <br>
     *       + 使用 StopAudioRecordingDeviceTest{@link #IAudioDeviceManager#StopAudioRecordingDeviceTest} 停止测试。  <br>
     */
    virtual int StartAudioRecordingDeviceTest(int indication_interval) = 0;

    /**
     * @type api
     * @region 音频设备管理
     * @brief 停止音频采集设备测试。
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + <0：方法调用失败  <br>
     * @notes  调用 StartAudioRecordingDeviceTest{@link #StartAudioRecordingDeviceTest} 后，调用本方法停止测试。
     */
    virtual int StopAudioRecordingDeviceTest() = 0;

    /**
     * @type api
     * @region 音频设备管理
     * @brief 开始音频设备回路测试。
     *        该方法测试音频采集设备和音频播放设备是否能正常工作。一旦测试开始，音频采集设备会采集本地讲话声音
     *        然后使用音频播放设备播放出来，同时 SDK 会通过 OnAudioVolumeIndication{@link #IRTCRoomEventHandler#OnAudioVolumeIndication}
     *        回调向应用程序上报音量信息。
     * @param [in] indication_interval
     *        OnAudioVolumeIndication{@link #IRTCRoomEventHandler#OnAudioVolumeIndication}
     *        回调的时间间隔，单位为毫秒。建议设置到大于 200 毫秒。最小不得少于 10 毫秒。小于10ms行为未定义
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + <0：方法调用失败  <br>
     * @notes  <br>
     *       + 测试功能必须在 JoinChannel{@link #IRtcEngine#JoinChannel} 前应用。且不可与其它音频设备测试功能同时应用。  <br>
     *       + 使用 StopAudioDeviceLoopbackTest{@link #IAudioDeviceManager#StopAudioDeviceLoopbackTest} 停止测试。  <br>
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
     * @notes 调用 StartAudioDeviceLoopbackTest{@link #StartAudioDeviceLoopbackTest} 后，调用本方法停止测试。
     */
    virtual int StopAudioDeviceLoopbackTest() = 0;
     
    /**
     * @hidden
     * @type api
     * @region 音频设备管理
     * @brief 切换音频播放到扬声器或者听筒，默认播放设备是扬声器
     * @param [in] enable  <br>
     *       + true：切换至扬声器  <br>
     *       + false：切换至听筒  <br>
     * @notes 本方法只在移动设备上有效
     */
    virtual void SetEnableSpeakerphone(bool enable) = 0;
    
    /*
     * @hidden
     * @type api
     * @region 音频设备管理
     * @brief 尝试初始化播放设备，可检测设备不存在、权限被拒绝/禁用等异常问题
     * @param [in] index 设备索引
     * @return 设备状态错误码
     *       0: 设备检测结果正常
     *      -1: 接口状态不正确，如已经正常启动采集后再进行设备检查
     *      -2: 采集设备无麦克风权限，尝试初始化设备失败
     *      -3: 设备不存在，当前没有设备或设备被移除时返回
     *      -4: 设备音频格式不支持
     *      -5: 其它原因错误
     * @notes 1. 该接口适用于joinchannel前调用
     *        2. 检测成功不代表设备一定可以启动成功
     */
    virtual int InitPlaybackDeviceForTest(const char deviceId[MAX_DEVICE_ID_LENGTH]) = 0;

    /*
     * @hidden
     * @type api
     * @region 音频设备管理
     * @brief 尝试初始化录音设备，可检测设备不存在、权限被拒绝/禁用等异常问题
     * @param [in] index 设备索引
     * @return 设备状态错误码
     *       0: 设备检测结果正常
     *      -1: 接口状态不正确，如已经正常启动采集后再进行设备检查
     *      -2: 采集设备无麦克风权限，尝试初始化设备失败
     *      -3: 设备不存在，当前没有设备或设备被移除时返回
     *      -4: 设备音频格式不支持
     *      -5: 其它原因错误
     * @notes 1. 该接口适用于joinchannel前调用
     *        2. 检测成功不代表设备一定可以启动成功
     */
    virtual int InitRecordingDeviceForTest(const char deviceId[MAX_DEVICE_ID_LENGTH]) = 0;

    /**
     * @type api
     * @region 音频设备管理
     * @brief 析构当前对象，释放内存
     * @notes 严禁调用 delete 该结构体，该结构不需要的时候应该调用本函数释放音频操作相关的资源
     */
    virtual void Release() = 0;

protected:
    /**
     * @hidden
     * @brief 析构函数
     */
    virtual ~IAudioDeviceManager() {
    }
};

}  // namespace bytertc
