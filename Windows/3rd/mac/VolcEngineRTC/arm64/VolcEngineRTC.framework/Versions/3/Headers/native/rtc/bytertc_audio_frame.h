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
 * @locale zh
 * @type keytype
 * @region 音频管理
 * @brief 音频帧类型
 */
/**
 * @locale en
 * @type keytype
 * @region Audio Management
 * @brief Audio frame type
 */
enum AudioFrameType {
    /**
     * @locale zh
     * @brief PCM 16bit
     */
    /**
     * @locale en
     * @brief PCM 16bit
     */
    kAudioFrameTypePCM16 = 0
};

/**
 * @locale zh
 * @type keytype
 * @region 音频管理
 * @brief 音频帧构建类
 */
/**
 * @locale en
 * @type keytype
 * @region audio management
 * @brief Audio frame construction class
 */
typedef struct AudioFrameBuilder {
    /**
     * @locale zh
     * @brief 音频采样率
     */
    /**
     * @locale en
     * @brief Audio Sampling Rate
     */
    AudioSampleRate sample_rate;

    /**
     * @locale zh
     * @brief 音频通道数
     */
    /**
     * @locale en
     * @brief Number of audio channels
     */
    AudioChannel channel;

    /**
     * @locale zh
     * @brief 音频帧时间戳，单位：微秒
     */
    /**
     * @locale en
     * @brief Audio frame timestamp in microseconds
     */
    int64_t timestamp_us = 0;

    /**
     * @locale zh
     * @brief 音频帧数据
     */
    /**
     * @locale en
     * @brief Audio frame data
     */
    uint8_t* data;

    /**
     * @locale zh
     * @brief 音频帧数据大小
     */
    /**
     * @locale en
     * @brief Audio frame data size
     */
    int64_t data_size = 0;

    /**
     * @locale zh
     * @brief 是否深拷贝
     */
    /**
     * @locale en
     * @brief Is deep-copy or not
     */
    bool deep_copy = true;
} AudioFrameBuilder;
/**
 * @locale zh
 * @type keytype
 * @brief 音频帧
 */
/**
 * @locale en
 * @type keytype
 * @brief Audio frame
 */
class IAudioFrame {
public:
    /**
     * @locale zh
     * @type api
     * @region 音频管理
     * @brief 获取音频帧时间戳。
     * @return 音频帧时间戳，单位：微秒
     */
    /**
     * @locale en
     * @type api
     * @region Audio Management
     * @brief Gets audio frame timestamp.
     * @return Audio frame timestamp in microseconds
     */
    virtual int64_t timestampUs() const = 0;
    /**
     * @locale zh
     * @type api
     * @region 音频管理
     * @brief 获取音频采样率。参看 AudioSampleRate{@link #AudioSampleRate}
     * @return 音频采样率，单位：Hz
     */
    /**
     * @locale en
     * @type api
     * @region Audio Management
     * @brief Gets audio sample rate. See AudioSampleRate{@link #AudioSampleRate}
     * @return Audio sample rate in Hz
     */
    virtual AudioSampleRate sampleRate() const = 0;
    /**
     * @locale zh
     * @type api
     * @region 音频管理
     * @brief 获取音频通道数。参看 AudioChannel{@link #AudioChannel}
     * @return 音频通道数
     * @note 双声道的情况下，左右声道的音频帧数据以 LRLRLR 形式排布。
     */
    /**
     * @locale en
     * @type api
     * @region Audio Management
     * @brief Gets the number of audio channels. See AudioChannel{@link #AudioChannel}
     * @return Number of audio channels
     * @note For dual channels, the audio frames are interleaved.
     */
    virtual AudioChannel channel() const = 0;
    /**
     * @locale zh
     * @type api
     * @region 音频管理
     * @brief 获取音频帧内存块地址
     * @return 音频帧内存块地址
     */
    /**
     * @locale en
     * @type api
     * @region Audio Management
     * @brief Gets audio frame memory address
     * @return Audio frame memory address
     */
    virtual uint8_t* data() const = 0;
    /**
     * @locale zh
     * @type api
     * @region 音频管理
     * @brief 获取音频帧数据大小
     * @return 音频帧数据大小，单位：字节。
     */
    /**
     * @locale en
     * @type api
     * @region Audio Management
     * @brief Getd audio frame data size
     * @return Audio frame data size in bytes.
     */
    virtual int dataSize() const = 0;
    /**
     * @locale zh
     * @type api
     * @region 音频管理
     * @brief 获取音频帧类型
     * @return 音频帧类型，目前只支持 PCM，详见 AudioFrameType{@link #AudioFrameType}
     */
    /**
     * @locale en
     * @type api
     * @region Audio Management
     * @brief Gets audio frame type
     * @return Audio frame type, support PCM only. See AudioFrameType{@link #AudioFrameType}
     */
    virtual AudioFrameType frameType() const = 0;
    /**
     * @locale zh
     * @type api
     * @region 音频管理
     * @brief 释放音频帧
     */
    /**
     * @locale en
     * @type api
     * @region Audio Management
     * @brief Release audio frames
     */
    virtual void release() = 0;
    /**
     * @locale zh
     * @type api
     * @region 音频管理
     * @brief 获取音频静音标志
     * @return 是否静音数据  <br>
     *        + true: 是  <br>
     *        + false: 否
     */
    /**
     * @locale en
     * @type api
     * @region Audio Management
     * @brief Gets audio mute state identifier
     * @return Is the data muted:  <br>
     *         + true: Yes <br>
     *         + false: No
     */
    virtual bool isMutedData() const = 0;
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
    virtual ~IAudioFrame() = default;
};

/**
 * @locale zh
 * @type api
 * @region 音频管理
 * @brief 创建 IAudioFrame
 * @param builder 音频帧构建实例，参看 AudioFrameBuilder{@link #AudioFrameBuilder}
 * @return 详见 IAudioFrame{@link #IAudioFrame}
 */
/**
 * @locale en
 * @type api
 * @region Audio Management
 * @brief Create IAudioFrame
 * @param builder Audio frame build instance. See AudioFrameBuilder{@link #AudioFrameBuilder}
 * @return Refer to IAudioFrame{@link #IAudioFrame} for more details.
 */
BYTERTC_API IAudioFrame* buildAudioFrame(const AudioFrameBuilder& builder);

/**
 * @locale zh
 * @type keytype
 * @brief 音频回调方法
 */
/**
 * @locale en
 * @type keytype
 * @brief Audio data callback method
 */
enum class AudioFrameCallbackMethod{
    /**
     * @locale zh
     * @brief 本地麦克风录制的音频数据回调
     */
    /**
     * @locale en
     * @brief The callback of the audio data recorded by local microphone.
     */
    kRecord,
    /**
     * @locale zh
     * @brief 订阅的远端所有用户混音后的音频数据回调
     */
    /**
     * @locale en
     * @brief The callback of the mixed audio data of all remote users subscribed by the local user.
     */
    kPlayback,
    /**
     * @locale zh
     * @brief 本地麦克风录制和订阅的远端所有用户混音后的音频数据回调
     */
    /**
     * @locale en
     * @brief The callback of the mixed audio data including the data recorded by local microphone and that of all remote users subscribed by the local user.
     */
    kMixed,
    /**
     * @locale zh
     * @brief 订阅的远端每个用户混音前的音频数据回调
     */
    /**
     * @locale en
     * @brief The callback of the audio data before mixing of each remote user subscribed by the local user.
     */
    kRemoteUser,
    /**
     * @locale zh
     * @brief 本地屏幕录制的音频数据回调
     */
    /**
     * @locale en
     * @brief The callback of screen audio data captured locally.
     */
    kRecordScreen,
};

/**
 * @locale zh
 * @type callback
 * @region 音频数据回调
 * @brief 音频数据回调观察者<br>
 * 注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。<br>
 * 本接口类中的回调周期均为 20 ms。
 */
/**
 * @locale en
 * @type callback
 * @region Audio Data Callback
 * @brief Audio data callback observer<br>
 * Note: Callback functions are thrown synchronously in a non-UI thread within the SDK. Therefore, you must not perform any time-consuming operations or direct UI operations within the callback function, as this may cause the app to crash.<br>
 * The time interval for all callback functions in this interface is 20 ms.
 */
class IAudioFrameObserver {
public:
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
    virtual ~IAudioFrameObserver() {
    }
    /**
     * @hidden for internal use only
     * @valid since 3.50
     */
    virtual void onRecordAudioFrameOriginal(const IAudioFrame& audio_frame) = 0;
    
    /**
     * @locale zh
     * @type callback
     * @region 音频数据回调
     * @brief 返回麦克风录制的音频数据
     * @param audio_frame 音频数据, 详见：IAudioFrame{@link #IAudioFrame}
     */
    /**
     * @locale en
     * @type callback
     * @region Audio Data Callback
     * @brief Returns audio data recorded by microphone
     * @param audio_frame Audio data. See IAudioFrame{@link #IAudioFrame}
     */
    virtual void onRecordAudioFrame(const IAudioFrame& audio_frame) = 0;

    /**
     * @locale zh
     * @type callback
     * @region 音频数据回调
     * @brief 返回订阅的所有远端用户混音后的音频数据。
     * @param audio_frame 音频数据, 详见：IAudioFrame{@link #IAudioFrame}
     */
    /**
     * @locale en
     * @type callback
     * @region Audio Data Callback
     * @brief Returns the mixed audio data of all subscribed remote users
     * @param audio_frame Audio data. See IAudioFrame{@link #IAudioFrame}
     */
    virtual void onPlaybackAudioFrame(const IAudioFrame& audio_frame) = 0;
    /**
     * @locale zh
     * @type callback
     * @region 音频数据回调
     * @brief 返回远端单个用户的音频数据
     * @param stream_info 远端流信息，参看 RemoteStreamKey{@link #RemoteStreamKey}。
     * @param audio_frame 音频数据, 参看 IAudioFrame{@link #IAudioFrame}。
     * @note 此回调在播放线程调用。不要在此回调中做任何耗时的事情，否则可能会影响整个音频播放链路。
     */
    /**
     * @locale en
     * @type callback
     * @region Audio Data Callback
     * @brief Returns the audio data of one remote user.
     * @param stream_info Remote stream information. See RemoteStreamKey{@link #RemoteStreamKey}.
     * @param audio_frame Audio data. See IAudioFrame{@link #IAudioFrame}
     * @note This callback works on the playback thread. Don't do anything time-consuming in this callback, or it may affect the entire audio playback chain.
     */
    virtual void onRemoteUserAudioFrame(const RemoteStreamKey& stream_info, const IAudioFrame& audio_frame) = 0;

    /**
     * @locale zh
     * @type callback
     * @region 音频数据回调
     * @brief 返回本地麦克风录制和订阅的所有远端用户混音后的音频数据
     * @param audio_frame 音频数据, 详见：IAudioFrame{@link #IAudioFrame}
     */
    /**
     * @locale en
     * @type callback
     * @region Audio Data Callback
     * @brief Returns mixed audio data including both data recorded by the local microphone and data from all subscribed remote users
     * @param audio_frame Audio data. See IAudioFrame{@link #IAudioFrame}
     */
    virtual void onMixedAudioFrame(const IAudioFrame& audio_frame) = 0;

    /**
     * @locale zh
     * @type callback
     * @region 屏幕音频数据回调
     * @brief 返回本地屏幕录制的音频数据
     * @param audio_frame 音频数据, 详见：IAudioFrame{@link #IAudioFrame}
     */
    /**
     * @locale en
     * @type callback
     * @region Screen audio data callback
     * @brief Returns the audio data played locally
     * @param audio_frame Audio data. See IAudioFrame{@link #IAudioFrame}
     */
    virtual void onRecordScreenAudioFrame(const IAudioFrame& audio_frame) {
    }
};
/**
 * @locale zh
 * @type callback
 * @brief 自定义音频处理器。<br>
 * 注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。
 */
/**
 * @locale en
 * @type callback
 * @brief The custom audio processor.<br>
 * Note: Callback functions are thrown synchronously in a non-UI thread within the SDK. Therefore, you must not perform any time-consuming operations or direct UI operations within the callback function, as this may cause the app to crash.
 */
class IAudioFrameProcessor{
public:
    /**
     * @locale zh
     * @type callback
     * @brief 回调本地采集的音频帧地址，供自定义音频处理。
     * @param audio_frame 音频帧地址，参看 IAudioFrame{@link #IAudioFrame}
     * @note 
     *        + 完成自定义音频处理后，SDK 会对处理后的音频帧进行编码，并传输到远端。 <br>
     *        + 调用 `enableAudioProcessor`，并在参数中选择本地采集的音频时，每 10 ms 收到此回调。
     */
    /**
     * @locale en
     * @type callback
     * @brief Returns the address of the locally captured audio frame for custom processing.
     * @param audio_frame The address of the audio frame. See IAudioFrame{@link #IAudioFrame}
     * @note 
     *        + After custom processing, SDK will encode the processed audio frames and transmit to the remote user.  <br>
     *        + After calling `enableAudioProcessor` with locally captured audio frame specified, you will receive this callback every 10 ms.
     */
    virtual int onProcessRecordAudioFrame(IAudioFrame& audio_frame) = 0;
    /**
     * @locale zh
     * @type callback
     * @brief 回调远端音频混音的音频帧地址，供自定义音频处理。
     * @param audio_frame 音频帧地址，参看 IAudioFrame{@link #IAudioFrame}
     * @note 调用 `enableAudioProcessor`，并在参数中选择远端音频流的的混音音频时，每 10 ms 收到此回调。
     */
    /**
     * @locale en
     * @type callback
     * @brief Returns the address of the locally captured audio frame for custom processing.
     * @param audio_frame The address of the audio frame. See IAudioFrame{@link #IAudioFrame}
     * @note After calling `enableAudioProcessor` with mixed remote audio, you will receive this callback every 10 ms.
     */
    virtual int onProcessPlayBackAudioFrame(IAudioFrame& audio_frame) = 0;
    /**
     * @locale zh
     * @type callback
     * @brief 回调单个远端用户的音频帧地址，供自定义音频处理。
     * @param stream_info 音频流信息，参看 RemoteStreamKey{@link #RemoteStreamKey}
     * @param audio_frame 音频帧地址，参看 IAudioFrame{@link #IAudioFrame}
     * @note 调用 `enableAudioProcessor`，并在参数中选择各个远端音频流时，每 10 ms 收到此回调。
     */
    /**
     * @locale en
     * @type callback
     * @brief Returns the address of the locally captured audio frame for custom processing.
     * @param stream_info Information of the audio stream. See RemoteStreamKey{@link #RemoteStreamKey}
     * @param audio_frame The address of the audio frame. See IAudioFrame{@link #IAudioFrame}
     * @note After calling `enableAudioProcessor` with audio streams of the remote users. You will receive this callback every 10 ms.
     */
    virtual int onProcessRemoteUserAudioFrame(const RemoteStreamKey& stream_info, IAudioFrame& audio_frame) = 0;
    /**
     * @locale zh
     * @hidden(macOS, Windows, Linux)
     * @valid since 3.50
     * @type callback
     * @brief 软件耳返音频数据的回调。你可根据此回调自定义处理音频。<br>
     *        耳返音频中包含通过调用 `setVoiceReverbType` 和 `setVoiceChangerType` 设置的音频特效。
     * @param audio_frame 音频帧地址。参看 IAudioFrame{@link #IAudioFrame}。
     * @note  
     *        + 此数据处理只影响软件耳返音频数据。  <br>
     *        + 要启用此回调，必须调用 `enableAudioProcessor`，并选择耳返音频，每 10 ms 收到此回调。
     * @return  
     *        + 0： 成功。  <br>
     *        + < 0： 失败。  
     */
    /**
     * @locale en
     * @hidden(macOS, Windows, Linux)
     * @valid since 3.50
     * @type callback
     * @brief You will receive the address of SDK-level in-ear monitoring audio frames for custom processing.<br>
     *        The audio effects set by `setVoiceReverbType` and `setVoiceChangerType` are included.
     * @param  audio_frame The address of the in-ear monitoring audio frames. See IAudioFrame{@link #IAudioFrame}.
     * @note 
     *        + Modifying the data affects only SDK-level in-ear monitoring audio.  <br>
     *        + To enable this callback, call `enableAudioProcessor`. You will receive this callback every 10 ms.
     * @return  
     *        + 0: Success. <br>
     *        + <0: Failure.  
     */
    virtual int onProcessEarMonitorAudioFrame(IAudioFrame& audio_frame) = 0;
    /**
     * @locale zh
     * @type callback
     * @brief 屏幕共享的音频帧地址回调。你可根据此回调自定义处理音频。
     * @param audio_frame 音频帧地址，参看 IAudioFrame{@link #IAudioFrame}。
     * @note 调用 `enableAudioProcessor`，把返回给音频处理器的音频类型设置为屏幕共享音频后，每 10 ms 收到此回调。
     */
    /**
     * @locale en
     * @type callback
     * @brief Returns the address of the shared-screen audio frames for custom processing.
     * @param audio_frame The address of audio frames. See IAudioFrame{@link #IAudioFrame}.
     * @note After calling `enableAudioProcessor` to set the audio input to the shared-screen audio. You will receive this callback every 10 ms.
     */
    virtual int onProcessScreenAudioFrame(IAudioFrame& audio_frame) = 0;
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
    virtual ~IAudioFrameProcessor() {
    }
};

/**
 * @locale zh
 * @deprecated since 3.37 and will be deleted in 3.51.
 * @type callback
 * @region 音频数据回调
 * @brief 音频数据回调观察者<br>
 * 注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。
 */
/**
 * @locale en
 * @deprecated since 3.45 and will be deleted in 3.51.
 * @type callback
 * @region audio data callback
 * @brief Audio data callback observer<br>
 * Note: Callback functions are thrown synchronously in a non-UI thread within the SDK. Therefore, you must not perform any time-consuming operations or direct UI operations within the callback function, as this may cause the app to crash.
 */
class IRemoteAudioFrameObserver {
public:
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
    virtual ~IRemoteAudioFrameObserver() {
    }

    /**
     * @locale zh
     * @type callback
     * @region 音频数据回调
     * @brief 获得单个流的音频数据，此回调通过调用 registerAudioFrameObserver{@link #IRTCVideo#registerAudioFrameObserver} 触发。
     * @param audio_frame 音频数据, 详见： IAudioFrame{@link #IAudioFrame}
     * @param stream_info 该音频流的业务信息, 详见： RemoteStreamKey{@link #RemoteStreamKey}
     */
    /**
     * @locale en
     * @type callback
     * @region Audio data callback
     * @brief Get audio data for a single stream, this callback is triggered by calling registerAudioFrameObserver {@link #IRTCVideo#registerAudioFrameObserver}.
     * @param audio_frame Audio data, see: IAudioFrame{@link #IAudioFrame}
     * @param stream_info The audio stream business information, see: RemoteStreamKey{@link #RemoteStreamKey}
     */
    virtual void onRemoteAudioFrame(const IAudioFrame& audio_frame, const RemoteStreamKey& stream_info) = 0;
};



}  // namespace bytertc
