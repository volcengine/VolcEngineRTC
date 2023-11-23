/*
 * Copyright (c) 2020 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC audio Frame
 */

#pragma once

#include <stdint.h>
#include <stddef.h>
#include <memory>
#include "bytertc_audio_defines.h"

namespace bytertc {

/** 
 * @type keytype
 * @region 音频管理
 * @brief 音频帧类型
 */
enum AudioFrameType {
    /** 
     * @brief PCM 16bit
     */
    kFrameTypePCM16 = 0
};

/** 
 * @type keytype
 * @region 音频管理
 * @brief 音频帧构建类
 */
typedef struct AudioFrameBuilder {
    /** 
     * @brief 音频采样率
     */
    AudioSampleRate sample_rate;

    /** 
     * @brief 音频通道数
     */
    AudioChannel channel;

    /** 
     * @brief 音频帧时间戳，单位：微秒
     */
    int64_t timestamp_us = 0;

    /** 
     * @brief 音频帧数据
     */
    uint8_t* data;

    /** 
     * @brief 音频帧数据大小
     */
    int64_t data_size = 0;

    /** 
     * @brief 是否深拷贝
     */
    bool deep_copy = true;
} AudioFrameBuilder;
/** 
 * @type keytype
 * @brief 音频帧
 */
class IAudioFrame {
public:
    /** 
     * @type api
     * @region 音频管理
     * @brief 获取音频帧时间戳。
     * @return 音频帧时间戳，单位：微秒
     */
    virtual int64_t timestampUs() const = 0;
    /** 
     * @type api
     * @region 音频管理
     * @brief 获取音频采样率。参看 AudioSampleRate{@link #AudioSampleRate}
     * @return 音频采样率，单位：Hz
     */
    virtual AudioSampleRate sampleRate() const = 0;
    /** 
     * @type api
     * @region 音频管理
     * @brief 获取音频通道数。参看 AudioChannel{@link #AudioChannel}
     * @return 音频通道数
     * @notes 双声道的情况下，左右声道的音频帧数据以 LRLRLR 形式排布。
     */
    virtual AudioChannel channel() const = 0;
    /** 
     * @type api
     * @region 音频管理
     * @brief 获取音频帧内存块地址
     * @return 音频帧内存块地址
     */
    virtual uint8_t* data() const = 0;
    /** 
     * @type api
     * @region 音频管理
     * @brief 获取音频帧数据大小
     * @return 音频帧数据大小，单位：字节。
     */
    virtual int dataSize() const = 0;
    /** 
     * @type api
     * @region 音频管理
     * @brief 获取音频帧类型
     * @return 音频帧类型，目前只支持 PCM，详见 AudioFrameType{@link #AudioFrameType}
     */
    virtual AudioFrameType frameType() const = 0;
    /** 
     * @type api
     * @region 音频管理
     * @brief 释放音频帧
     */
    virtual void release() = 0;
    /** 
     * @type api
     * @region 音频管理
     * @brief 获取音频静音标志
     * @return 是否静音数据  <br>
     *        + true: 是  <br>
     *        + false: 否
     */
    virtual bool isMutedData() const = 0;
    /**
     * @hidden constructor/destructor
     */
protected:
    /** 
     * @hidden constructor/destructor
     * @brief 析构函数
     */
    virtual ~IAudioFrame() = default;
};

/** 
 * @type api
 * @region 音频管理
 * @brief 创建 IAudioFrame
 * @param [in] builder 音频帧构建实例，参看 AudioFrameBuilder{@link #AudioFrameBuilder}
 * @return 详见 IAudioFrame{@link #IAudioFrame}
 */
BYTERTC_API IAudioFrame* buildAudioFrame(const AudioFrameBuilder& builder);

/** 
 * @type keytype
 * @brief 音频回调方法
 */
enum class AudioFrameCallbackMethod{
    /** 
     * @brief 本地麦克风录制的音频数据回调
     */
    kAudioFrameCallbackRecord,
    /** 
     * @brief 订阅的远端所有用户混音后的音频数据回调
     */
    kAudioFrameCallbackPlayback,
    /** 
     * @brief 本地麦克风录制和订阅的远端所有用户混音后的音频数据回调
     */
    kAudioFrameCallbackMixed,
    /** 
     * @brief 订阅的远端每个用户混音前的音频数据回调
     */
    kAudioFrameCallbackRemoteUser,
    /** 
     * @brief 本地屏幕录制的音频数据回调
     */
    kAudioFrameCallbackRecordScreen,
};

/** 
 * @type callback
 * @region 音频数据回调
 * @brief 音频数据回调观察者
 * 注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。
 * 本接口类中的回调周期均为 20 ms。
 */
class IAudioFrameObserver {
public:
    /** 
     * @hidden constructor/destructor
     * @brief 析构函数
     */
    virtual ~IAudioFrameObserver() {
    }
    /**
     * @hidden for internal use only
     * @valid since 3.50
     */
    virtual void onRecordAudioFrameOriginal(const IAudioFrame& audio_frame) = 0;
    
    /** 
     * @type callback
     * @region 音频数据回调
     * @brief 返回麦克风录制的音频数据
     * @param [in] audio_frame 音频数据, 详见：IAudioFrame{@link #IAudioFrame}
     */
    virtual void onRecordAudioFrame(const IAudioFrame& audio_frame) = 0;

    /** 
     * @type callback
     * @region 音频数据回调
     * @brief 返回订阅的所有远端用户混音后的音频数据。
     * @param [in] audio_frame 音频数据, 详见：IAudioFrame{@link #IAudioFrame}
     */
    virtual void onPlaybackAudioFrame(const IAudioFrame& audio_frame) = 0;
    /** 
     * @type callback
     * @region 音频数据回调
     * @brief 返回远端单个用户的音频数据
     * @param [in] stream_info 远端流信息，参看 RemoteStreamKey{@link #RemoteStreamKey}。
     * @param [in] audio_frame 音频数据, 参看 IAudioFrame{@link #IAudioFrame}。
     * @notes 此回调在播放线程调用。不要在此回调中做任何耗时的事情，否则可能会影响整个音频播放链路。
     */
    virtual void onRemoteUserAudioFrame(const RemoteStreamKey& stream_info, const IAudioFrame& audio_frame) = 0;

    /** 
     * @type callback
     * @region 音频数据回调
     * @brief 返回本地麦克风录制和订阅的所有远端用户混音后的音频数据
     * @param [in] audio_frame 音频数据, 详见：IAudioFrame{@link #IAudioFrame}
     */
    virtual void onMixedAudioFrame(const IAudioFrame& audio_frame) = 0;

    /** 
     * @type callback
     * @region 屏幕音频数据回调
     * @brief 返回本地屏幕录制的音频数据
     * @param [in] audio_frame 音频数据, 详见：IAudioFrame{@link #IAudioFrame}
     */
    virtual void onRecordScreenAudioFrame(const IAudioFrame& audio_frame) {
    }
};
/** 
 * @deprecated since 3.42 and will be deleted in 3.51, use IAudioFrameProcessor{@link #IAudioFrameProcessor} instead.
 * @type callback
 * @region 音频处理
 * @brief 自定义音频处理器
 * 注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。
 */
class IAudioProcessor{
public:
    /** 
     * @type callback
     * @region 音频处理
     * @brief 获取 RTC SDK 采集得到的音频帧，并进行自定义处理，最终将处理后的音频帧给到 RTC SDK 用于编码传输。
     * @param [in] audio_frame RTC SDK 采集到的音频帧，自定义处理可直接对音频 data 中的数据进行修改。参看 IAudioFrame{@link #IAudioFrame}。
     * @return  <br>
     *        0: 未处理  <br>
     *        >0: 处理成功  <br>
     *        < 0: 处理失败
     * @notes 在进行音频自定义处理前，你需要调用 `registerLocalAudioProcessor` 设置音频自定义处理器。
     */
    virtual int processAudioFrame(const IAudioFrame& audio_frame) = 0;
};
/** 
 * @type callback
 * @brief 自定义音频处理器。
 * 注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。
 */
class IAudioFrameProcessor{
public:
    /** 
     * @type callback
     * @brief 回调本地采集的音频帧地址，供自定义音频处理。
     * @param [in] audioFrame 音频帧地址，参看 IAudioFrame{@link #IAudioFrame}
     * @notes <br>
     *        + 完成自定义音频处理后，SDK 会对处理后的音频帧进行编码，并传输到远端。 <br>
     *        + 调用 `enableAudioProcessor`，并在参数中选择本地采集的音频时，每 10 ms 收到此回调。
     */
    virtual int onProcessRecordAudioFrame(IAudioFrame& audioFrame) = 0;
    /** 
     * @type callback
     * @brief 回调远端音频混音的音频帧地址，供自定义音频处理。
     * @param [in] audioFrame 音频帧地址，参看 IAudioFrame{@link #IAudioFrame}
     * @notes 调用 `enableAudioProcessor`，并在参数中选择远端音频流的的混音音频时，每 10 ms 收到此回调。
     */
    virtual int onProcessPlayBackAudioFrame(IAudioFrame& audioFrame) = 0;
    /** 
     * @type callback
     * @brief 回调单个远端用户的音频帧地址，供自定义音频处理。
     * @param [in] stream_info 音频流信息，参看 RemoteStreamKey{@link #RemoteStreamKey}
     * @param [in] audioFrame 音频帧地址，参看 IAudioFrame{@link #IAudioFrame}
     * @notes 调用 `enableAudioProcessor`，并在参数中选择各个远端音频流时，每 10 ms 收到此回调。
     */
    virtual int onProcessRemoteUserAudioFrame(const RemoteStreamKey& stream_info, IAudioFrame& audioFrame) = 0;
    /** 
     * @hidden(macOS, Windows, Linux)
     * @valid since 3.50
     * @type callback
     * @brief 软件耳返音频数据的回调。你可根据此回调自定义处理音频。
     *        耳返音频中包含通过调用 `setVoiceReverbType` 和 `setVoiceChangerType` 设置的音频特效。
     * @param audioFrame 音频帧地址。参看 IAudioFrame{@link #IAudioFrame}。
     * @notes  <br>
     *        + 此数据处理只影响软件耳返音频数据。  <br>
     *        + 要启用此回调，必须调用 `enableAudioProcessor`，并选择耳返音频，每 10 ms 收到此回调。
     * @return  <br>
     *        + 0： 成功。  <br>
     *        + < 0： 失败。  <br>
     */
    virtual int onProcessEarMonitorAudioFrame(IAudioFrame& audioFrame) = 0;
    /** 
     * @type callback
     * @brief 屏幕共享的音频帧地址回调。你可根据此回调自定义处理音频。
     * @param [in] audioFrame 音频帧地址，参看 IAudioFrame{@link #IAudioFrame}。
     * @notes 调用 `enableAudioProcessor`，把返回给音频处理器的音频类型设置为屏幕共享音频后，每 10 ms 收到此回调。
     */
    virtual int onProcessScreenAudioFrame(IAudioFrame& audioFrame) = 0;
};

/** 
 * @deprecated since 3.37 and will be deleted in 3.51.
 * @type callback
 * @region 音频数据回调
 * @brief 音频数据回调观察者
 * 注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。
 */
class IRemoteAudioFrameObserver {
public:
    /** 
     * @hidden constructor/destructor
     * @brief 析构函数
     */
    virtual ~IRemoteAudioFrameObserver() {
    }

    /** 
     * @type callback
     * @region 音频数据回调
     * @brief 获得单个流的音频数据，此回调通过调用 registerAudioFrameObserver{@link #IRTCVideo#registerAudioFrameObserver} 触发。
     * @param [in] audio_frame 音频数据, 详见： IAudioFrame{@link #IAudioFrame}
     * @param [in] stream_info 该音频流的业务信息, 详见： RemoteStreamKey{@link #RemoteStreamKey}
     */
    virtual void onRemoteAudioFrame(const IAudioFrame& audio_frame, const RemoteStreamKey& stream_info) = 0;
};



}  // namespace bytertc
