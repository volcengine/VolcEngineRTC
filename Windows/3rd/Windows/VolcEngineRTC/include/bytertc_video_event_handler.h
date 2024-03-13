/*
 * Copyright (c) 2020 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC Event Handler Lite
*/

#pragma once

#include "rtc/bytertc_defines.h"

namespace bytertc {
/**
 * @locale zh
 * @type callback
 * @brief 音视频引擎事件回调接口<br>
 * 注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。
 */
/**
 * @locale en
 * @type callback
 * @brief Audio & video engine event callback interface<br>
 * Note: Callback functions are thrown synchronously in a non-UI thread within the SDK. Therefore, you must not perform any time-consuming operations or direct UI operations within the callback function, as this may cause the app to crash.
 */
class IRTCVideoEventHandler {
public:

    /**
     * @hidden constructor/destructor
     */
    virtual ~IRTCVideoEventHandler() {
    }

    /**
     * @locale zh
     * @type callback
     * @region 警告码
     * @brief 发生警告回调。  <br>
     *        SDK 运行时出现了警告。SDK 通常会自动恢复，警告信息可以忽略。<br>
     *        你可能需要干预.
     * @param warn 警告标识码，详见:WarningCode{@link #WarningCode}
     * @list 引擎管理
     * @order 5
     */
    /**
     * @locale en
     * @type callback
     * @region Warning code
     * @brief A warning occurred during the SDK runtime. The SDK usually recovers automatically and warnings can be ignored.
     * @param warn Warning identification code, see: WarningCode{@link #WarningCode}
     * @list Engine Management
     * @order 5
     */
    virtual void onWarning(int warn) {
        (void)warn;
    }

    /**
     * @locale zh
     * @type callback
     * @region 错误码
     * @brief 发生错误回调。<br>
     *        SDK 运行时出现了网络或媒体相关的错误，且无法自动恢复时触发此回调。
     * @param err 错误标识码，参看 ErrorCode{@link #ErrorCode}
     * @list 引擎管理
     * @order 6
     */
    /**
     * @locale en
     * @type callback
     * @region Error code
     * @brief Error callback occurred. This callback is triggered when a network or media-related error occurs during the <br>
     *        SDK runtime and cannot be automatically recovered and you may need to intervene.
     * @param err Error code. See ErrorCode{@link #ErrorCode}
     * @list Engine Management
     * @order 6
     */
    virtual void onError(int err) {
        (void)err;
    }

    /** {zh}
     *  @valid since 3.57
     *  @type callback
     *  @brief 当内部线程发生block时，将收到此回调。
     *  @param [in] deadLockMsg  block线程的线程名和block检测次数;
     */
    virtual void onDeadLockError(const DeadLockMsg& msg) {
        (void)msg;
    }
    /**
    * @locale zh
    * @valid since 3.52
    * @type callback
    * @brief 当访问插件失败时，收到此回调。<br>
    *        RTC SDK 将一些功能封装成插件。当使用这些功能时，如果插件不存在，功能将无法使用。
    * @param extension_name 插件名字
    * @param msg 失败说明
    */
    /**
    * {en}
    * @valid since 3.52
    * @type callback
    * @brief Failed to access the extension.<br>
    *        RTC SDK provides some features with extensions. Without implementing the extension, you cannot use the corresponding feature.
    * @param extension_name The name of extension.
    * @param msg Error message.
    */
    virtual void onExtensionAccessError(const char* extension_name, const char* msg) {

    }


    /**
     * @locale zh
     * @deprecated since 353. Use IMediaPlayerEventHandler{@link #IMediaPlayerEventHandler} and IAudioEffectPlayerEventHandler{@link #IAudioEffectPlayerEventHandler} instead.
     * @type callback
     * @region 混音
     * @brief  音频混音文件播放状态改变时回调
     * @param mix_id  <br>
     *        混音 ID  <br>
     *        使用 IAudioMixingManager{@link #IAudioMixingManager} 相关接口时传入的唯一 ID。
     * @param state  <br>
     *        混音状态  <br>
     *        其混音状态可参考： AudioMixingState{@link #AudioMixingState}。
     * @param error<br>
     *        错误码  <br>
     *        详见 AudioMixingError{@link #AudioMixingError}
     * @note  
     *       此回调会被触发的时机汇总如下：  <br>
     *       + 1. 音乐文件类型： <br>
     *       + 当调用 startAudioMixing{@link #IAudioMixingManager#startAudioMixing} 方法成功后，会触发 state 值为 kAudioMixingStatePlaying 回调；否则触发 state 值为 kAudioMixingStateFailed 的回调。  <br>
     *       + 当使用相同的 ID 重复调用 startAudioMixing{@link #IAudioMixingManager#startAudioMixing} 后，后一次会覆盖前一次，且本回调会以 kAudioMixingStateStopped 通知前一次混音已停止。  <br>
     *       + 当调用 pauseAudioMixing{@link #IAudioMixingManager#pauseAudioMixing} 方法暂停播放成功后，会触发 state 值为 kAudioMixingStatePaused 回调；否则触发 state 值为 kAudioMixingStateFailed 的回调。  <br>
     *       + 当调用 resumeAudioMixing{@link #IAudioMixingManager#resumeAudioMixing} 方法恢复播放成功后，会触发 state 值为 kAudioMixingStatePlaying 回调；否则触发 state 值为 kAudioMixingStateFailed 的回调。  <br>
     *       + 当调用 stopAudioMixing{@link #IAudioMixingManager#stopAudioMixing} 方法暂停止播放成功后，会触发 state 值为 kAudioMixingStateStopped 回调；否则触发 state 值为 kAudioMixingStateFailed 的回调。  <br>
     *       + 播放结束会触发 state 值为 kAudioMixingStateFinished 回调。 <br>
     *       + 2. PCM 流类型： <br>
     *       + 当调用 enableAudioMixingFrame{@link #IAudioMixingManager#enableAudioMixingFrame} 方法成功后，会触发 state 值为 kAudioMixingStatePCMEnabled 回调；否则触发 state 值为 kAudioMixingStateFailed 的回调。（Linux 不支持）  <br>
     *       + 当调用 disableAudioMixingFrame{@link #IAudioMixingManager#disableAudioMixingFrame} 方法成功后，会触发 state 值为 kAudioMixingStatePCMDisabled 回调；否则触发 state 值为 kAudioMixingStateFailed 的回调。
     */
    /**
     * @locale en
     * @deprecated since 353. Use IMediaPlayerEventHandler{@link #IMediaPlayerEventHandler} and IAudioEffectPlayerEventHandler{@link #IAudioEffectPlayerEventHandler} instead.
     * @type callback
     * @region  Mix
     * @brief   Callback when audio mix file playback state changes
     * @param mix_id <br>
     *         Mix ID <br>
     *         Unique ID passed in when using IAudioMixingManager{@link #IAudioMixingManager} related interface.
     * @param state <br>
     *        Mix status <br>
     *        The mix status can be referred to: AudioMixingState{@link #AudioMixingState}.
     * @param error<br>
     *         Error code <br>
     *         See AudioMixingError{@link #AudioMixingError}
     * @note   
     *        The timing of this callback will be triggered is summarized as follows: <br>
     *        + When the startAudioMixing{@link #IAudioMixingManager#startAudioMixing} method is successfully called, a callback with a state value of kAudioMixingStatePlaying will be triggered; otherwise the state will be triggered A callback with a value of kAudioMixingStateFailed. <br>
     *        + When startAudioMixing{@link #IAudioMixingManager#startAudioMixing} is called repeatedly with the same ID, the latter overrides the previous, and this callback notifies the previous mix has stopped with kAudioMixingStateStopped. <br>
     *        + When calling the pauseAudioMixing{@link #IAudioMixingManager#pauseAudioMixing} method to pause playback successfully, a callback with a state value of kAudioMixingStatePaused will be triggered; otherwise, a callback with a state value of kAudioMixingStateFailed will be triggered. <br>
     *        + When the resumeAudioMixing{@link #IAudioMixingManager#resumeAudioMixing} method is called to resume playing successfully, a callback with a state value of kAudioMixingStatePlaying will be triggered; otherwise, a callback with a state value of kAudioMixingStateFailed will be triggered. <br>
     *        + When calling the stopAudioMixing{@link #IAudioMixingManager#stopAudioMixing} method to pause playback successfully, a callback with a state value of kAudioMixingStateStopped will be triggered; otherwise, a callback with a state value of kAudioMixingStateFailed will be triggered. <br>
     *        + The end of playback triggers a callback with the state value kAudioMixingStateFinished.
     */
    virtual void onAudioMixingStateChanged(int mix_id, bytertc::AudioMixingState state, bytertc::AudioMixingError error) {
    }

    /**
     * @locale zh
     * @type callback
     * @region 混音
     * @brief 混音音频文件播放进度回调
     * @param mix_id 混音 ID  
     * @param progress 当前混音音频文件播放进度，单位毫秒
     * @note 调用 setAudioMixingProgressInterval{@link #IAudioMixingManager#setAudioMixingProgressInterval} 将时间间隔设为大于 0 的值后，或调用 startAudioMixing{@link #IAudioMixingManager#startAudioMixing} 将 AudioMixingConfig{@link #AudioMixingConfig} 中的时间间隔设为大于 0 的值后，SDK 会按照设置的时间间隔回调该事件。 
     */
    /**
     * @locale en
     * @type callback
     * @region Audio Mixing
     * @brief Callback for playback progress of mixed audio files
     * @param mix_id ID of the mixing task  
     * @param progress The current playback progress (ms) of the mixed audio file
     * @note After calling setAudioMixingProgressInterval{@link #IAudioMixingManager#setAudioMixingProgressInterval} to set the time interval to a value greater than 0, or calling startAudioMixing{@link #IAudioMixingManager#startAudioMixing} to set the time interval in AudioMixingConfig{@link #AudioMixingConfig} to a value greater than 0, the SDK will trigger the callback according to the set time interval.
     */
    virtual void onAudioMixingPlayingProgress(int mix_id, int64_t progress) {
    }

    /**
     * @locale zh
     * @type callback
     * @region 引擎管理
     * @brief 上报日志时回调该事件。
     * @param log_type  <br>
     *        事件类型。目前类型固定为 "live_webrtc_monitor_log"。
     * @param log_content  <br>
     *        端监控日志内容。
     * @list 引擎管理
     * @order 1
     */
    /**
     * @locale en
     * @type callback
     * @region  engine management
     * @brief  Terminal monitoring log callback. The callback is triggered when a terminal monitoring event is generated.
     * @param log_type <br>
     *         Event type. The current type is fixed to "live_webrtc_monitor_log".
     * @param log_content <br>
     *         Terminal monitoring log content.
     * @list Engine Management
     * @order 1
     */
    virtual void onLogReport(const char* log_type, const char* log_content) {
        (void)log_type;
        (void)log_content;
    }

    /**
     * @locale zh
     * @hidden(Windows,Linux,macOS)
     * @deprecated since 3.38 and will be deleted in 3.51, use onAudioRouteChanged{@link #IRTCVideoEventHandler#onAudioRouteChanged} instead.
     * @type callback
     * @region 音频事件回调
     * @brief 移动端音频播放设备变化时回调该事件。
     * @param device 变化后的音频播放设备，参看 AudioPlaybackDevice{@link #AudioPlaybackDevice}。  
     */
    /**
     * @locale en
     * @hidden(Windows,Linux,macOS)
     * @deprecated since 3.45 and will be deleted in 3.51, use onAudioRouteChanged{@link #IRTCVideoEventHandler#onAudioRouteChanged} instead.
     * @type callback
     * @region Audio event callback
     * @brief Callback triggered when the audio playback device changed on mobile.
     * @param device Changed audio playback device. See AudioPlaybackDevice{@link #AudioPlaybackDevice}. 
     */
    BYTERTC_DEPRECATED virtual void onAudioPlaybackDeviceChanged(AudioPlaybackDevice device) {
        (void)device;
    };

    /**
     * @locale zh
     * @hidden(macOS,Windows,Linux)
     * @type callback
     * @region 音频事件回调
     * @brief 音频播放设备变化时回调该事件。
     * @param device 变化后的音频播放设备，参看 AudioRoute{@link #AudioRoute}。  
     */
    /**
     * @locale en
     * @hidden(macOS,Windows,Linux)
     * @type callback
     * @region Audio event callback
     * @brief Audio playback The event is called back when the device changes.
     * @param device Changed audio playback device. See AudioRoute{@link #AudioRoute}. 
     */
    virtual void onAudioRouteChanged(AudioRoute route) {
        (void)route;
    };

    /**
     * @locale zh
     * @type callback
     * @region 引擎管理
     * @brief SDK 与信令服务器连接状态改变回调。连接状态改变时触发。
     * @param state 当前 SDK 与信令服务器的连接状态，详见 ConnectionState{@link #ConnectionState}。
     * @note 更多信息参见 [连接状态提示](https://www.volcengine.com/docs/6348/95376)。
     */
    /**
     * @locale en
     * @type callback
     * @region  engine management
     * @brief SDK  connection state change callback with signaling server. Triggered when the connection state changes.
     * @param state The current connection status between the SDK and the signaling server. See ConnectionState{@link #ConnectionState}
     * @note Refer to [Getting Connection Status](https://docs.byteplus.com/byteplus-rtc/docs/95376) for more details.
     */
    virtual void onConnectionStateChanged(bytertc::ConnectionState state) {
    }

    /**
     * @locale zh
     * @type callback
     * @region 引擎管理
     * @brief SDK 当前网络连接类型改变回调。当 SDK 的当前网络连接类型发生改变时回调该事件。
     * @param type  <br>
     *        SDK 当前的网络连接类型，详见：NetworkType{@link #NetworkType} 。
     */
    /**
     * @locale en
     * @type callback
     * @region Engine management
     * @brief SDK Current network connection type change callback. Callbacks the event when the current network connection type of the SDK changes.
     * @param type <br>
     *        SDK The current network connection type, see: NetworkType{@link #NetworkType}.
     */
    virtual void onNetworkTypeChanged(bytertc::NetworkType type) {
    }
    /**
     * @locale zh
     * @type callback
     * @region 音视频回退
     * @brief 音视频流因网络环境变化等原因发生回退，或从回退中恢复时，触发该回调。
     * @param event 音视频流发生变化的信息。参看 RemoteStreamSwitch{@link #RemoteStreamSwitch}。
     */
    /**
     * @locale en
     * @type callback
     * @region Audio & Video Fallback
     * @brief This callback is triggered when media streams start to fall back or restore from a fallback.
     * @param event Information about the fallback. See RemoteStreamSwitch{@link #RemoteStreamSwitch}.
     */
    virtual void onSimulcastSubscribeFallback(const RemoteStreamSwitch& event) {
        (void)event;
    }
    
    /**
     * @locale zh
     * @type callback
     * @region 音视频回退
     * @brief 本地未通过 setPublishFallbackOption{@link #IRTCVideo#setPublishFallbackOption} 开启发布性能回退，检测到设备性能不足时，收到此回调。<br>
     *        本地通过 setPublishFallbackOption{@link #IRTCVideo#setPublishFallbackOption} 开启发布性能回退，因设备性能/网络原因，造成发布性能回退/恢复时，收到此回调。
     * @param mode 指示本地是否开启发布回退功能。参看 PerformanceAlarmMode{@link #PerformanceAlarmMode}  <br>
     *                  + 当发布端未开启发布性能回退时，mode 值为 kPerformanceAlarmModeNormal。  <br>
     *                  + 当发布端开启发布性能回退时，mode 值为 kPerformanceAlarmModeSimulcast。
     * @param room_id  <br>
     *                      + 未开启发布性能回退时，room_id 为空 <br>
     *                      + 开启发布性能回退时，room_id 是告警影响的房间 ID。
     * @param reason 告警原因，参看 PerformanceAlarmReason{@link #PerformanceAlarmReason}
     * @param data 性能回退相关数据，详见 SourceWantedData{@link #SourceWantedData}。
     */
    /**
     * @locale en
     * @type callback
     * @region audio & video fallback
     * @brief When the publish performance fallback setPublishFallbackOption{@link #IRTCVideo#setPublishFallbackOption} is not turned on locally, and when insufficient device performance is detected, this callback is received. <br>
     *        When the publish performance fallback setPublishFallbackOption{@link #IRTCVideo#setPublishFallbackOption} is locally turned on, and when the publish performance fallback/recovery is caused due to device performance/network reasons, this callback is received.
     * @param mode Indicates whether the release fallback function is turned on locally. See PerformanceAlarmMode{@link #PerformanceAlarmMode} <br>
     *                   + When the publisher does not turn on the release performance fallback, the mode value is kPerformanceAlarmModeNormal. <br>
     *                   + When the publisher turns on the release performance fallback, the mode value is kPerformance AlarmModeSimulcast.
     * @param room_id <br>
     *                       + When the release performance fallback is not turned on, the room_id is empty <br>
     *                       + When the release performance fallback is turned on, the room_id is the room ID affected by the alarm.
     * @param reason Reason for the alarm. See PerformanceAlarmReason{@link #PerformanceAlarmReason}
     * @param data Performance rollback related data. See SourceWantedData{@link #SourceWantedData}.
     */
    virtual void onPerformanceAlarms(bytertc::PerformanceAlarmMode mode, const char* room_id,
            bytertc::PerformanceAlarmReason reason, const bytertc::SourceWantedData& data) {
        (void)mode;
        (void)room_id;
        (void)reason;
        (void)data;
    }

    /**
     * @locale zh
     * @deprecated since 3.37 and will be deleted in 3.51, use onAudioDeviceStateChanged{@link #IRTCVideoEventHandler#onAudioDeviceStateChanged} and onVideoDeviceStateChanged{@link #IRTCVideoEventHandler#onVideoDeviceStateChanged} instead.
     * @type callback
     * @region 引擎管理
     * @brief 媒体设备状态回调。提示音频采集、音频播放、摄像头视频采集、屏幕视频采集四种媒体设备的状态。
     * @param device_id 设备 ID   <br>
     *                       采集屏幕视频流时，设备 ID 为固定字符串 `screen_capture_video`
     * @param device_type 设备类型，详见 MediaDeviceType{@link #MediaDeviceType}
     * @param device_state 设备状态，详见 MediaDeviceState{@link #MediaDeviceState}
     * @param device_error 设备错误类型，详见 MediaDeviceError{@link #MediaDeviceError}
     */
    /**
     * @locale en
     * @deprecated since 3.45 and will be deleted in 3.51, use onAudioDeviceStateChanged{@link #IRTCVideoEventHandler#onAudioDeviceStateChanged} and onVideoDeviceStateChanged{@link #IRTCVideoEventHandler#onVideoDeviceStateChanged} instead.
     * @type callback
     * @region engine management
     * @brief Callback of media-device state.  <br>
     *        Media devices includes the following three: audio capture devices, audio playback devices, and video capture devices.
     * @param device_id Device ID
     * @param device_type Device type. Refer to MediaDeviceType{@link #MediaDeviceType} for more details.
     * @param device_state Device state. Refer to MediaDeviceState{@link #MediaDeviceState} for more details.
     * @param device_error Device error. Refer to MediaDeviceError{@link #MediaDeviceError} for more details.
     */
    BYTERTC_DEPRECATED virtual void onMediaDeviceStateChanged(const char* device_id,
                                           bytertc::MediaDeviceType device_type,
                                           bytertc::MediaDeviceState device_state,
                                           bytertc::MediaDeviceError device_error) {
        (void)device_id;
        (void)device_type;
        (void)device_state;
        (void)device_error;
    }
    /**
     * @locale zh
     * @type callback
     * @region 引擎管理
     * @brief 音频设备状态回调。提示音频采集、音频播放等设备设备的状态。
     * @param device_id 设备 ID。
     * @param device_type 设备类型，详见 RTCAudioDeviceType{@link #RTCAudioDeviceType}
     * @param device_state 设备状态，详见 MediaDeviceState{@link #MediaDeviceState}
     * @param device_error 设备错误类型，详见 MediaDeviceError{@link #MediaDeviceError}
     */
    /**
     * @locale en
     * @type callback
     * @region  engine management
     * @brief Callback of audio device state. Audio devices include audio capture devices and audio playback devices.
     * @param device_id Device ID
     * @param device_type Device type. Refer to RTCAudioDeviceType{@link #RTCAudioDeviceType} for more details.
     * @param device_state Device state. Refer to MediaDeviceState{@link #MediaDeviceState} for more details.
     * @param device_error Device error. Refer to MediaDeviceError{@link #MediaDeviceError} for more details.
     */
    virtual void onAudioDeviceStateChanged(const char* device_id, bytertc::RTCAudioDeviceType device_type,
            bytertc::MediaDeviceState device_state, bytertc::MediaDeviceError device_error) {
        (void)device_id;
        (void)device_type;
        (void)device_state;
        (void)device_error;
    }
    /**
     * @locale zh
     * @type callback
     * @region 引擎管理
     * @brief 视频频设备状态回调。提示摄像头视频采集、屏幕视频采集等设备的状态。
     * @param device_id 设备 ID。采集屏幕共享流时，设备 ID 为固定字符串 `screen_capture_video`
     * @param device_type 设备类型，详见 RTCVideoDeviceType{@link #RTCVideoDeviceType}
     * @param device_state 设备状态，详见 MediaDeviceState{@link #MediaDeviceState}
     * @param device_error 设备错误类型，详见 MediaDeviceError{@link #MediaDeviceError}
     */
    /**
     * @locale en
     * @type callback
     * @region Engine Management
     * @brief Callback of video device state. Video devices include cameras and screen sharing video capture devices.
     * @param device_id Device ID
     * @param device_type Device type. Refer to RTCVideoDeviceType{@link #RTCVideoDeviceType} for more details.
     * @param device_state Device state. Refer to MediaDeviceState{@link #MediaDeviceState} for more details.
     * @param device_error Device error. Refer to MediaDeviceError{@link #MediaDeviceError} for more details.
     */
    virtual void onVideoDeviceStateChanged(const char* device_id, bytertc::RTCVideoDeviceType device_type,
            bytertc::MediaDeviceState device_state, bytertc::MediaDeviceError device_error) {
        (void)device_id;
        (void)device_type;
        (void)device_state;
        (void)device_error;
    }

    /**
     * @locale zh
     * @deprecated since 3.37 and will be deleted in 3.51, use onAudioDeviceWarning{@link #IRTCVideoEventHandler#onAudioDeviceWarning} and onVideoDeviceWarning{@link #IRTCVideoEventHandler#onVideoDeviceWarning} instead.
     * @type callback
     * @region 引擎管理
     * @brief 媒体设备警告回调。媒体设备包括：音频采集设备、音频渲染设备、和视频采集设备。
     * @param device_id 设备 ID
     * @param device_type 详见 MediaDeviceType{@link #MediaDeviceType}
     * @param device_warning 详见 MediaDeviceWarning{@link #MediaDeviceWarning}
     */
     /**
     * @locale en
     * @deprecated since 3.45 and will be deleted in 3.51, use onAudioDeviceWarning{@link #IRTCVideoEventHandler#onAudioDeviceWarning} and onVideoDeviceWarning{@link #IRTCVideoEventHandler#onVideoDeviceWarning} instead.
     * @type callback
     * @region Engine Management
     * @brief Media device warning callback. The media devices includes: audio capture devices, audio rendering devices, and video capture devices.
     * @param device_id Device ID
     * @param device_type Device type. See MediaDeviceType{@link #MediaDeviceType}
     * @param device_warning Device error type. See MediaDeviceWarning{@link #MediaDeviceWarning}
     */
    BYTERTC_DEPRECATED virtual void onMediaDeviceWarning(const char* device_id, bytertc::MediaDeviceType device_type,
            bytertc::MediaDeviceWarning device_warning) {
        (void)device_id;
        (void)device_type;
        (void)device_warning;
    }
    /**
     * @locale zh
     * @type callback
     * @region 引擎管理
     * @brief 音频设备警告回调。音频设备包括音频采集设备和音频渲染设备。
     * @param device_id 设备 ID
     * @param device_type 详见 RTCAudioDeviceType{@link #RTCAudioDeviceType}
     * @param device_warning 详见 MediaDeviceWarning{@link #MediaDeviceWarning}
     */
     /**
     * @locale en
     * @type callback
     * @region Engine Management
     * @brief Audio device warning callback. The audio devices include audio capture devices and audio rendering devices.
     * @param device_id Device ID
     * @param device_type Device type. See RTCAudioDeviceType{@link #RTCAudioDeviceType}
     * @param device_warning Device error type. See MediaDeviceWarning{@link #MediaDeviceWarning}
     */
    virtual void onAudioDeviceWarning(const char* device_id, bytertc::RTCAudioDeviceType device_type,
            bytertc::MediaDeviceWarning device_warning) {
        (void)device_id;
        (void)device_type;
        (void)device_warning;
    }
    /**
     * @locale zh
     * @type callback
     * @region 引擎管理
     * @brief 视频设备警告回调，包括视频采集设备等。
     * @param device_id 设备 ID
     * @param device_type 详见 RTCVideoDeviceType{@link #RTCVideoDeviceType}
     * @param device_warning 详见 MediaDeviceWarning{@link #MediaDeviceWarning}
     */
     /**
     * @locale en
     * @type callback
     * @region Engine Management
     * @brief Video device warning callback. The video devices include video capture devices.
     * @param device_id Device ID
     * @param device_type Device type. See RTCVideoDeviceType{@link #RTCVideoDeviceType}
     * @param device_warning Device error type. See MediaDeviceWarning{@link #MediaDeviceWarning}
     */
    virtual void onVideoDeviceWarning(const char* device_id, bytertc::RTCVideoDeviceType device_type,
            bytertc::MediaDeviceWarning device_warning) {
        (void)device_id;
        (void)device_type;
        (void)device_warning;
    }

    /**
     * @locale zh
     * @type callback
     * @region 引擎管理
     * @brief 周期性（2s）发出回调，报告当前 CPU 与内存的相关信息。
     * @param stats 包含当前 CPU 与内存相关信息的结构体。详见 SysStats{@link #SysStats}。
     * @list 引擎管理
     * @order 2
     */
    /**
     * @locale en
     * @type callback
     * @region  engine management
     * @brief  You will periodically(2s) receive the callbacks of the current CPU and memory information.
     * @param stats The structure containing the current CPU and memory information. See SysStats{@link #SysStats}.
     * @list Engine Management
     * @order 2
     */
    virtual void onSysStats(const bytertc::SysStats& stats) {
    }

    /**
     * @locale zh
     * @type callback
     * @region 引擎管理
     * @brief 创建房间失败回调。
     * @param room_id 房间 ID。
     * @param error_code 创建房间错误码，具体原因参看 ErrorCode{@link #ErrorCode}。
     */
    /**
     * @locale en
     * @type callback
     * @region Engine Management
     * @brief Callback on create room failure.
     * @param room_id  Room ID.
     * @param error_code Create room error code. See ErrorCode{@link #ErrorCode} for specific indications.
     */
    virtual void onCreateRoomStateChanged(const char* room_id, int error_code) {
        (void)room_id;
        (void)error_code;
    }

    /**
     * @locale zh
     * @deprecated since 3.52, will be deleted at 3.57, use onLocalProxyStateChanged{@link #IRTCVideoEventHandler#onLocalProxyStateChanged} instead
     * @type callback
     * @region 代理回调
     * @brief HTTP 代理连接状态改变时，收到该回调。
     * @param state 当前 HTTP 代理连接状态，详见 HttpProxyState{@link #HttpProxyState}
     */
    /**
     * @locale en
     * @deprecated since 3.52, will be deleted at 3.57, use onLocalProxyStateChanged{@link #IRTCVideoEventHandler#onLocalProxyStateChanged} instead
     * @type callback
     * @region Proxy callback
     * @brief HTTP Receive the callback when the proxy connection state changes.
     * @param state The current HTTP proxy connection status. See HttpProxyState{@link #HttpProxyState}
     */
        virtual void onHttpProxyState(int state) {
    }

    /**
     * @locale zh
     * @deprecated since 3.52, will be deleted at 3.57, use onLocalProxyStateChanged{@link #IRTCVideoEventHandler#onLocalProxyStateChanged} instead
     * @type callback
     * @region 代理回调
     * @brief HTTPS 代理连接状态改变时，收到该回调。
     * @param  [out] state 当前 HTTPS 代理连接状态，详见 HttpProxyState{@link #HttpProxyState}
     */
    /**
     * @locale en
     * @deprecated since 3.52, will be deleted at 3.57, use onLocalProxyStateChanged{@link #IRTCVideoEventHandler#onLocalProxyStateChanged} instead
     * @type callback
     * @region Proxy callback
     * @brief HTTPS Receive the callback when the proxy connection state changes.
     * @param   [out] State the current HTTPS proxy connection status. See HttpProxyState{@link #HttpProxyState}
     */
    virtual void onHttpsProxyState(int state) {
    }

    /**
     * @locale zh
     * @deprecated since 3.52, will be deleted at 3.57, use onLocalProxyStateChanged{@link #IRTCVideoEventHandler#onLocalProxyStateChanged} instead
     * @type callback
     * @region 代理回调
     * @brief SOCKS5 代理状态改变时，收到该回调。
     * @param [out] state SOCKS5 代理连接状态
     * @param [out] cmd 代理连接的每一步操作命令
     * @param [out] proxy_address 代理地址信息
     * @param [out] local_address 当前连接使用的本地地址
     * @param [out] remote_address 远端的连接地址
     */
    /**
     * @locale en
     * @deprecated since 3.52, will be deleted at 3.57, use onLocalProxyStateChanged{@link #IRTCVideoEventHandler#onLocalProxyStateChanged} instead
     * @type callback
     * @region Proxy callback
     * @brief Socks5 Receive the callback when the proxy state changes.
     * @param [out] state SOCKS5 proxy connection status. See Socks5ProxyState{@link #Socks5ProxyState}
     * @param [out] cmd every step of the proxy connection operating command
     * @param [out] proxy_address proxy address information
     * @param [out] local_address the local address used by the current connection
     * @param [out] remote_address the remote connection address
     */
    virtual void onSocks5ProxyState(int state,
        const char* cmd,
        const char* proxy_address,
        const char* local_address,
        const char* remote_address) {
    }

    /**
     * @locale zh
     * @type callback
     * @region 本地录制
     * @brief 获取本地录制状态回调。  <br>
     *        该回调由 startFileRecording{@link #IRTCVideo#startFileRecording} 或 stopFileRecording{@link #IRTCVideo#stopFileRecording} 触发。
     * @param [out] type 录制流的流属性，参看 StreamIndex{@link #StreamIndex}
     * @param [out] state 录制状态，参看 RecordingState{@link #RecordingState}
     * @param [out] error_code 录制错误码，参看 RecordingErrorCode{@link #RecordingErrorCode}
     * @param [out] info 录制文件的详细信息，参看 RecordingInfo{@link #RecordingInfo}
     */
    /**
     * @locale en
     * @type callback
     * @region Local recording
     * @brief Get a callback of the local recording status.   <br>
     *        The callback is triggered by startFileRecording{@link #IRTCVideo#startFileRecording} or stopFileRecording{@link #IRTCVideo#stopFileRecording}.
     * @param [out] type Stream properties of the recorded stream. See StreamIndex{@link #StreamIndex}
     * @param [out] state Recording state. See RecordingState{@link #RecordingState}
     * @param [out] error_code Recording error code. See RecordingErrorCode{@link #RecordingErrorCode}
     * @param [out] info For more information about the recorded file. See RecordingInfo{@link #RecordingInfo}
     */
    virtual void onRecordingStateUpdate(
            StreamIndex type, RecordingState state, RecordingErrorCode error_code, RecordingInfo info) {
    }

    /**
     * @locale zh
     * @type callback
     * @region 本地录制
     * @brief 本地录制进度回调。  <br>
     *        该回调由 startFileRecording{@link #IRTCVideo#startFileRecording} 触发，录制状态正常时，系统每秒钟都会通过该回调提示录制进度。
     * @param [out] type 录制流的流属性，参看 StreamIndex{@link #StreamIndex}
     * @param [out] process 录制进度，参看 RecordingProgress{@link #RecordingProgress}
     * @param [out] info 录制文件的详细信息，参看 RecordingInfo{@link #RecordingInfo}
     */
    /**
     * @locale en
     * @type callback
     * @region Local recording
     * @brief Local recording progress callback.   <br>
     *        This callback is triggered by startFileRecording{@link #IRTCVideo#startFileRecording}. When the recording state is normal, the system will prompt the recording progress through this callback every second.
     * @param [out] type Stream properties of the recorded stream. See StreamIndex{@link #StreamIndex}
     * @param [out] process Recording progress. See RecordingProgress{@link #RecordingProgress}
     * @param [out] info More information about the recorded file. See RecordingInfo{@link #RecordingInfo}
     */
    virtual void onRecordingProgressUpdate(StreamIndex type, RecordingProgress process, RecordingInfo info) {
    }
    /**
     * @locale zh
     *  @type callback
     *  @brief 调用 startAudioRecording{@link #IRTCVideo#startAudioRecording} 或 stopAudioRecording{@link #IRTCVideo#stopAudioRecording} 改变音频文件录制状态时，收到此回调。
     * @param state 录制状态，参看 AudioRecordingState{@link #AudioRecordingState}
     * @param error_code 录制错误码，参看 AudioRecordingErrorCode{@link #AudioRecordingErrorCode}
     */
    /**
     * @locale en
     *  @type callback
     *  @brief When calling startAudioRecording{@link #IRTCVideo#startAudioRecording} or stopAudioRecording{@link #IRTCVideo#stopAudioRecording} to change the recording status, receive the callback.
     * @param state See AudioRecordingState{@link #AudioRecordingState}.
     * @param error_code See AudioRecordingErrorCode{@link #AudioRecordingErrorCode}.
     */
    virtual void onAudioRecordingStateUpdate(AudioRecordingState state, AudioRecordingErrorCode error_code) {
    }

    /**
     * @locale zh
     * @type callback
     * @region 实时消息通信
     * @brief 登录结果回调
     * @param uid  <br>
     *        登录用户 ID
     * @param error_code  <br>
     *        登录结果  <br>
     *        详见 LoginErrorCode{@link #LoginErrorCode}。
     * @param elapsed  <br>
     *        从调用 login{@link #IRTCVideo#login} 接口开始到返回结果所用时长  <br>
     *        单位为 ms。
     * @note 调用 login{@link #IRTCVideo#login} 后，会收到此回调。
     */
    /**
     * @locale en
     * @type callback
     * @region Real-time messaging
     * @brief login result callback
     * @param uid <br>
     *        Login user ID
     * @param error_code <br>
     *        Login result <br>
     *        See LoginErrorCode{@link #LoginErrorCode}.
     * @param elapsed <br>
     *         The time taken from the call to the login{@link #IRTCVideo#login} interface to return the result is <br>
     *         In ms. This callback is received after
     * @note You will receive this callback after calling login{@link #IRTCVideo#login}.
     */
    virtual void onLoginResult(const char* uid, int error_code, int elapsed) {
        (void)uid;
        (void)error_code;
        (void)elapsed;
    }
    /**
     * @locale zh
     * @type callback
     * @region 实时消息通信
     * @brief 登出结果回调
     * @param reason 用户登出的原因，参看 LogoutReason{@link #LogoutReason}
     * @note 在以下两种情况下会收到此回调：调用 logout{@link #IRTCVideo#logout} 接口主动退出；或其他用户以相同 UserId 进行 `login` 导致本地用户被动登出。
     */
    /**
     * @locale en
     * @type callback
     * @region Real-time messaging
     * @brief Callback of logout result
     * @param reason It describes the reason why users log out. See LogoutReason{@link #LogoutReason}
     * @note You will receive this callback when calling logout{@link #IRTCVideo#logout} or when the local user is kicked out because another user logs in with the same UserId.
     */
    virtual void onLogout(LogoutReason reason) {
    }
    /**
     * @locale zh
     * @type callback
     * @region 实时消息通信
     * @brief 设置应用服务器参数的返回结果
     * @param error <br>
     *        设置结果  <br>
     *        + 返回 200，设置成功  <br>
     *        + 返回其他，设置失败，详见 UserMessageSendResult{@link #UserMessageSendResult}
     * @note 调用 setServerParams{@link #IRTCVideo#setServerParams} 后，会收到此回调。
     */
    /**
     * @locale en
     * @type callback
     * @region Real-time messaging
     * @brief Set the return result of the application server parameter
     * @param error <br>
     *         + 200, set successfully <br>
     *         + != 200: Failure. Refer to UserMessageSendResult{@link #UserMessageSendResult} for details.
     * @note Receive this callback after calling setServerParams{@link #IRTCVideo#setServerParams}.
     */
    virtual void onServerParamsSetResult(int error) {
        (void)error;
    }
    /**
     * @locale zh
     * @type callback
     * @region 实时消息通信
     * @brief 查询对端或本端用户登录状态的返回结果
     * @param peer_user_id  <br>
     *        需要查询的用户 ID
     * @param status  <br>
     *        查询的用户登录状态  <br>
     *        详见 UserOnlineStatus{@link #UserOnlineStatus}.
     * @note 必须先调用 getPeerOnlineStatus{@link #IRTCVideo#getPeerOnlineStatus}，才能收到此回调。
     */
    /**
     * @locale en
     * @type callback
     * @region Real-time messaging
     * @brief The return result of querying the login status of the peer or local user
     * @param peer_user_id User ID
     * @param status <br>
     *        The user login status of the query <br>
     *        See UserOnlineStatus{@link #UserOnlineStatus}.
     * @note You must first call getPeerOnlineStatus{@link #IRTCVideo#getPeerOnlineStatus} to receive this callback.
     */
    virtual void onGetPeerOnlineStatus(const char* peer_user_id, int status) {
        (void)peer_user_id;
        (void)status;
    }
    /**
     * @locale zh
     * @type callback
     * @region 实时消息通信
     * @brief 收到房间外用户调用 sendUserMessageOutsideRoom{@link #IRTCVideo#sendUserMessageOutsideRoom} 发来的文本消息时，会收到此回调
     * @param uid  <br>
     *        消息发送者 ID
     * @param message  <br>
     *        收到的文本消息内容
     */
    /**
     * @locale en
     * @type callback
     * @region Real-time messaging
     * @brief Receive this callback when you receive a text message from an out-of-room user calling sendUserMessageOutsideRoom{@link #IRTCVideo#sendUserMessageOutsideRoom}
     * @param uid User ID of the message sender
     * @param message <br>
     *        Received text message content
     */
    virtual void onUserMessageReceivedOutsideRoom(const char* uid, const char* message) {
        (void)uid;
        (void)message;
    }
    /**
     * @locale zh
     * @type callback
     * @region 实时消息通信
     * @brief 收到房间外用户调用 sendUserBinaryMessageOutsideRoom{@link #IRTCVideo#sendUserBinaryMessageOutsideRoom} 发来的二进制消息时，会收到此回调
     * @param uid  <br>
     *        消息发送者 ID
     * @param size  <br>
     *        二进制消息长度
     * @param message  <br>
     *        收到的二进制消息内容
     */
    /**
     * @locale en
     * @type callback
     * @region Real-time messaging
     * @brief Receive this callback when you receive a binary message from an out-of-room user calling sendUserBinaryMessageOutsideRoom{@link #IRTCVideo#sendUserBinaryMessageOutsideRoom}
     * @param uid <br>
     *        User ID of the message sender
     * @param size <br>
     *        Binary message length
     * @param message <br>
     *         Binary message content received
     */
    virtual void onUserBinaryMessageReceivedOutsideRoom(const char* uid, int size, const uint8_t* message) {
        (void)uid;
        (void)size;
        (void)message;
    }
    /**
     * @locale zh
     * @type callback
     * @region 实时消息通信
     * @brief 给房间外指定的用户发送消息的回调
     * @param msgid  <br>
     *        本条消息的 ID  <br>
     *        所有的 P2P 和 P2Server 消息共用一个 ID 序列。
     * @param error  <br>
     *        消息发送结果  <br>
     *        详见 UserMessageSendResult{@link #UserMessageSendResult}。
     * @note 当调用 sendUserMessageOutsideRoom{@link #IRTCVideo#sendUserMessageOutsideRoom} 或 sendUserBinaryMessageOutsideRoom{@link #IRTCVideo#sendUserBinaryMessageOutsideRoom} 发送消息后，会收到此回调。
     */
    /**
     * @locale en
     * @type callback
     * @region Real-time messaging
     * @brief A callback that sends a message to a specified user outside the room
     * @param msgid <br>
     *        The ID of this message <br>
     *        All P2P and P2Server messages share a single ID sequence.
     * @param error <br>
     *         Message sending result <br>
     *         See UserMessageSendResult{@link #UserMessageSendResult}.
     * @note Receive this callback when a message is sent by calling sendUserMessageOutsideRoom{@link #IRTCVideo#sendUserMessageOutsideRoom} or sendUserBinaryMessageOutsideRoom{@link #IRTCVideo#sendUserBinaryMessageOutsideRoom}.
     */
    virtual void onUserMessageSendResultOutsideRoom(int64_t msgid, int error) {
        (void)msgid;
        (void)error;
    }

    /**
     * @locale zh
     * @type callback
     * @region 实时消息通信
     * @brief 给应用服务器发送消息的回调。
     * @param msgid 本条消息的 ID。<br>
     *        所有的 P2P 和 P2Server 消息共用一个 ID 序列。
     * @param error 消息发送结果，详见 UserMessageSendResult{@link #UserMessageSendResult}。
     * @param msg 应用服务器收到 HTTP 请求后，在 ACK 中返回的信息。消息不超过 64 KB。
     * @note 本回调为异步回调。当调用 sendServerMessage{@link #IRTCVideo#sendServerMessage} 或 sendServerBinaryMessage{@link #IRTCVideo#sendServerBinaryMessage} 接口发送消息后，会收到此回调。
     */
    /**
     * @locale en
     * @type callback
     * @region Real-time messaging
     * @brief Receives the callback after sending the message to the application server successfully.
     * @param msgid The ID of this message <br>
     *        All P2P and P2Server messages share a single ID sequence.
     * @param error Message Sending Results. See UserMessageSendResult{@link #UserMessageSendResult}.
     * @param msg The message returned in ACK when the application server receives HTTP request. The message should not exceed 64 KB.
     * @note This callback is asynchronous. You will receive this callback when you call sendServerMessage{@link #IRTCVideo#sendServerMessage} or sendServerBinaryMessage{@link #IRTCVideo#sendServerBinaryMessage} to send a message to your application server.
     */
    virtual void onServerMessageSendResult(int64_t msgid, int error, const bytertc::ServerACKMsg& msg) {
        (void)msgid;
        (void)error;
        (void)msg;
    }

    /**
     * @locale zh
     * @type callback
     * @region 视频管理
     * @brief 收到通过调用 sendSEIMessage{@link #IRTCVideo#sendSEIMessage} 发送带有 SEI 消息的视频帧时，收到此回调。
     * @param stream_key 包含 SEI 发送者的用户名，所在的房间名和媒体流，参看 RemoteStreamKey{@link #RemoteStreamKey}
     * @param message 收到的 SEI 消息内容
     * @param length 收到的 SEI 消息长度
    */
   /**
     * @locale en
     * @type callback
     * @region Video management
     * @brief Receive this callback when you receive a video frame with a SEI message sent via sendSEIMessage{@link #IRTCVideo#sendSEIMessage}
     * @param stream_key Contains the user name, room name and media stream of the SEI sender. See RemoteStreamKey{@link #RemoteStreamKey}
     * @param message The content of the SEI message received
     * @param length Length of received SEI message
    */
    virtual void onSEIMessageReceived(RemoteStreamKey stream_key, const uint8_t* message, int length){
        (void)stream_key;
        (void)message;
        (void)length;
    }
    /**
     * @locale zh
     * @type callback
     * @region 消息
     * @brief 黑帧视频流发布状态回调。  <br>
     *        在语音通话场景下，本地用户调用 sendSEIMessage{@link #IRTCVideo#sendSEIMessage} 通过黑帧视频流发送 SEI 数据时，流的发送状态会通过该回调通知远端用户。  <br>
     *        你可以通过此回调判断携带 SEI 数据的视频帧为黑帧，从而不对该视频帧进行渲染。
     * @param key 远端流信息，参看 RemoteStreamKey{@link #RemoteStreamKey}。
     * @param type 黑帧视频流状态，参看 SEIStreamEventType{@link #SEIStreamEventType}
     */
    /**
     * @locale en
     * @type callback
     * @region Message
     * @brief Callback about publishing status of the black frame video stream .  <br>
     *        In a voice call scenario, when the local user calls sendSEIMessage{@link #IRTCVideo#sendSEIMessage} to send SEI data with a black frame, the sending status of the stream is notified to the remote user through this callback.  <br>
     *        You can tell from this callback that the video frame carrying SEI data is a black frame and thus not render that video frame.
     * @param key Information about stream from the remote user, see RemoteStreamKey{@link #RemoteStreamKey}.
     * @param type State of the black frame video stream, see SEIStreamEventType{@link #SEIStreamEventType}.
     */
    virtual void onSEIStreamUpdate(const RemoteStreamKey& key, SEIStreamEventType type) {
        (void)key;
        (void)type;
    }

     /**
      * @locale zh
      * @type callback
      * @region 音频管理
      * @brief 远端用户进房后，本地调用 enableAudioPropertiesReport{@link #IRTCVideo#enableAudioPropertiesReport}，根据设置的 interval 值，本地会周期性地收到此回调，了解订阅的远端用户的音频信息。<br>
      *        远端用户的音频包括使用 RTC SDK 内部机制/自定义机制采集的麦克风音频和屏幕音频。
      * @param audio_properties_infos 远端音频信息，其中包含音频流属性、房间 ID、用户 ID ，详见 RemoteAudioPropertiesInfo{@link #RemoteAudioPropertiesInfo}。
      * @param audio_properties_info_number 数组长度
      * @param total_remote_volume 所有订阅的远端流的总音量，范围是 [0,255]。  <br>
      *       + [0,25] 接近无声；  <br>
      *       + [25,75] 为低音量；  <br>
      *       + [76,204] 为中音量；  <br>
      *       + [205,255] 为高音量。  
      */
     /**
      * @locale en
      * @type callback
      * @region Audio Management
      * @brief After calling enableAudioPropertiesReport{@link #IRTCVideo#enableAudioPropertiesReport}, you will periodically receive this callback for the information about the subscribed remote audio streams. <br>
      *        The remote audio streams includes the microphone audio and screen audio collected using the RTC SDK internal mechanism/custom mechanism.
      * @param audio_properties_infos See RemoteAudioPropertiesInfo{@link #RemoteAudioPropertiesInfo}.
      * @param audio_properties_info_number The length of `audio_properties_infos`
      * @param total_remote_volume The total volume of all the subscribed remote streams. The range is [0,255]. <br>
      *        + [0,25] Is close to silent; <br>
      *        + [25,75] Is low volume; <br>
      *        + [76,204] Is medium volume; <br>
      *        + [205,255] Is high volume. 
      */
    virtual void onRemoteAudioPropertiesReport(const RemoteAudioPropertiesInfo* audio_properties_infos, int audio_properties_info_number, int total_remote_volume) {
        (void)audio_properties_infos;
        (void)audio_properties_info_number;
        (void)total_remote_volume;
    }

     /**
      * @locale zh
      * @type callback
      * @region 音频管理
      * @brief 调用 enableAudioPropertiesReport{@link #IRTCVideo#enableAudioPropertiesReport} 后，根据设置的 interval 值，你会周期性地收到此回调，了解本地音频的相关信息。  <br>
      *        本地音频包括使用 RTC SDK 内部机制采集的麦克风音频，屏幕音频和本地混音音频信息。
      * @param audio_properties_infos 本地音频信息，详见 LocalAudioPropertiesInfo{@link #LocalAudioPropertiesInfo} 。
      * @param audio_properties_info_number 数组长度
      */
     /**
      * @locale en
      * @type callback
      * @region Audio Management
      * @brief After calling enableAudioPropertiesReport{@link #IRTCVideo#enableAudioPropertiesReport}, you will periodically receive this callback for the information about local audio. <br>
      *        Local audio includes the microphone audio, the screen audio captured using RTC SDK internal mechanisms, and locally mixing audio.
      * @param audio_properties_infos See LocalAudioPropertiesInfo{@link #LocalAudioPropertiesInfo}.
      * @param audio_properties_info_number The length of `audio_properties_infos`
      */
    virtual void onLocalAudioPropertiesReport(const LocalAudioPropertiesInfo * audio_properties_infos, int audio_properties_info_number) {
        (void)audio_properties_infos;
        (void)audio_properties_info_number;
    }

    /**
     * @locale zh
     * @type callback
     * @region 音频设备管理
     * @brief 回调音频设备测试时的播放音量
     * @param volume 音频设备测试播放音量。取值范围：[0,255]
     * @note 调用 startAudioPlaybackDeviceTest{@link #IAudioDeviceManager#startAudioPlaybackDeviceTest} 或 startAudioDeviceRecordTest{@link #IAudioDeviceManager#startAudioDeviceRecordTest}，开始播放音频文件或录音时，将开启该回调。本回调为周期性回调，回调周期由上述接口的 `interval` 参数指定。
     */
    /**
     * @locale en
     * @type callback
     * @region Audio Device Management
     * @brief Notification on the playing volume during the test for the local audio devices
     * @param volume Playing volume during the test for the local audio devices. The range is [0,255].
     * @note Start an audio-device test by calling startAudioPlaybackDeviceTest{@link #IAudioDeviceManager#startAudioPlaybackDeviceTest} or startAudioDeviceRecordTest{@link #IAudioDeviceManager#startAudioDeviceRecordTest} will register this callback for regular notification on playing volume. You can set the time interval between each callback by passing a proper value when calling the API above.
     */
    virtual void onAudioPlaybackDeviceTestVolume(int volume) {
        (void)volume;
    }

    /**
     * @locale zh
     * @hidden(Android,iOS)
     * @type callback
     * @region 设备管理
     * @brief 音频设备音量改变回调。当通过系统设置，改变音频设备音量或静音状态时，触发本回调。本回调无需手动开启。
     * @param device_type 设备类型，包括麦克风和扬声器，参阅 RTCAudioDeviceType{@link #RTCAudioDeviceType}。
     * @param volume 音量值，[0, 255]。当 volume 变为 0 时，muted 会变为 True。注意：在 Windows 端，当麦克风 volume 变为 0 时，muted 值不变。
     * @param muted 是否禁音状态。扬声器被设置为禁音时，muted 为 True，但 volume 保持不变。
     */
    /**
     * @locale en
     * @hidden(Android,iOS)
     * @type callback
     * @region device management
     * @brief Callback to notify you the volume of the audio device has been changed or when the device has been muted or unmuted. No need to activate the notification beforehand.
     * @param device_type Includes microphones and speakers. Refer to RTCAudioDeviceType{@link #RTCAudioDeviceType} for more details.
     * @param volume Volume ranging [0, 255]. When the volume turns to 0, muted turns to True. Note that on Windows, when the volume of a microphone turns to 0, muted remains unchanged.
     * @param muted Whether is muted. When a speaker is muted, muted turns True but volume remains unchanged.
     */
    virtual void onAudioDeviceVolumeChanged(bytertc::RTCAudioDeviceType device_type, int volume, bool muted) {
        (void)device_type;
        (void)volume;
        (void)muted;
    }

    /**
     * @locale zh
     * @type callback
     * @region 音频事件回调
     * @brief 本地音频流的状态发生改变时，收到此回调。
     * @param state 本地音频设备的状态，详见： LocalAudioStreamState{@link #LocalAudioStreamState}
     * @param error 本地音频状态改变时的错误码，详见：LocalAudioStreamError{@link #LocalAudioStreamError}
     */
    /**
     * @locale en
     * @type callback
     * @region Audio event callback
     * @brief When the state of the local audio changes, the callback notifies the current local audio state.
     * @param state The state of the local audio device, see: LocalAudioStreamState{@link #LocalAudioStreamState}
     * @param error Error code when the local audio state changes, see: LocalAudioStreamError{@link #LocalAudioStreamError}
     */
    virtual void onLocalAudioStateChanged(LocalAudioStreamState state, LocalAudioStreamError error) {
        (void)state;
        (void)error;
    }
    /**
     * @locale zh
     * @type callback
     * @region 音频事件回调
     * @brief 房间内的用户调用 startAudioCapture{@link #IRTCVideo#startAudioCapture} 开启音频采集时，房间内其他用户会收到此回调。
     * @param room_id 开启音频采集的远端用户所在的房间 ID
     * @param user_id 开启音频采集的远端用户 ID
     */
    /**
     * @locale en
     * @type callback
     * @region Audio event callback
     * @brief Users in the room call startAudioCapture{@link #IRTCVideo#startAudioCapture} When audio capture is turned on, other users in the room will receive this callback.
     * @param room_id ID of the room where the remote user enables audio capture
     * @param user_id Remote user ID to enable audio capture
     */
    virtual void onUserStartAudioCapture(const char* room_id, const char* user_id) {
        (void)user_id;
    }

    /**
     * @locale zh
     * @type callback
     * @region 音频事件回调
     * @brief 房间内的用户调用 stopAudioCapture{@link #IRTCVideo#stopAudioCapture} 关闭音频采集时，房间内其他用户会收到此回调。
     * @param room_id 关闭音频采集的远端用户所在的房间 ID
     * @param user_id 关闭音频采集的远端用户 ID
     */
    /**
     * @locale en
     * @type callback
     * @region Audio event callback
     * @brief When a user in the room calls stopAudioCapture{@link #IRTCVideo#stopAudioCapture} to turn off audio capture, other users in the room will receive this callback.
     * @param room_id ID of the room where the remote user disables audio capture
     * @param user_id Remote user ID to turn off audio capture
     */
    virtual void onUserStopAudioCapture(const char* room_id, const char* user_id) {
        (void)user_id;
    }

    /**
     * @locale zh
     * @type callback
     * @region 音频管理
     * @brief 调用 enableAudioPropertiesReport{@link #IRTCVideo#enableAudioPropertiesReport} 后，根据设置的 `config.interval`，你会周期性地收到此回调，获取房间内的最活跃用户信息。
     * @param room_id 房间 ID
     * @param uid 最活跃用户（ActiveSpeaker）的用户 ID
     */
    /**
     * @locale en
     * @type callback
     * @region Audio Management
     * @brief After calling enableAudioPropertiesReport{@link #IRTCVideo#enableAudioPropertiesReport}, you will periodically receive this callback for the active speaker information. 
     * @param room_id  Room ID.
     * @param uid The user ID of the active speaker.
     */
    virtual void onActiveSpeaker(const char* room_id, const char* uid) {
        (void)room_id;
        (void)uid;
    }

    /**
     * @locale zh
     * @type callback
     * @region 音频管理
     * @brief 音频流同步信息回调。可以通过此回调，在远端用户调用 sendStreamSyncInfo{@link #IRTCVideo#sendStreamSyncInfo} 发送音频流同步消息后，收到远端发送的音频流同步信息。  
     * @param stream_key 远端流信息，详见 RemoteStreamKey{@link #RemoteStreamKey} 。
     * @param stream_type 媒体流类型，详见 SyncInfoStreamType{@link #SyncInfoStreamType} 。
     * @param data 消息内容。
     * @param length 消息长度。
     */
    /**
     * @locale en
     * @type callback
     * @region audio management
     * @brief Audio stream synchronization information callback. You can use this callback to receive audio stream synchronization information sent remotely after the remote user calls sendStreamSyncInfo{@link #IRTCVideo#sendStreamSyncInfo} to send an audio stream synchronization message. 
     * @param stream_key Remote stream information. See RemoteStreamKey{@link #RemoteStreamKey}.
     * @param stream_type Media stream type. See SyncInfoStreamType{@link #SyncInfoStreamType}.
     * @param data Message content.
     * @param length Message length.
     */
    virtual void onStreamSyncInfoReceived(RemoteStreamKey stream_key, SyncInfoStreamType stream_type,
                                         const uint8_t* data,
                                         int32_t length) {
        (void)stream_key;
        (void)stream_type;
        (void)data;
        (void)length;
    }

    /**
     * @locale zh
     * @type callback
     * @region 通话前网络探测
     * @brief 通话前网络探测结果。  <br>
     *        成功调用 startNetworkDetection{@link #IRTCVideo#startNetworkDetection} 接口开始探测后，会在 3s 内首次收到该回调，之后每 2s 收到一次该回调。
     * @param type 探测网络类型为上行/下行  
     * @param quality 探测网络的质量，参看 NetworkQuality{@link #NetworkQuality}。 
     * @param rtt 探测网络的 RTT，单位：ms  
     * @param lost_rate 探测网络的丢包率  
     * @param bitrate 探测网络的带宽，单位：kbps  
     * @param jitter 探测网络的抖动,单位：ms  
     */
    /**
     * @locale en
     * @type callback
     * @region Pre-call network detection
     * @brief Pre-call network detection result.  <br>
     *        After successfully calling startNetworkDetection{@link #IRTCVideo#startNetworkDetection}, you will receive this callback for the first time in 3s and every 2s thereafter.
     * @param type  Identifies the network type as uplink/downlink. 
     * @param quality Network quality, see NetworkQuality{@link #NetworkQuality}. 
     * @param rtt Network RTT in ms. 
     * @param lost_rate Packet loss rate. 
     * @param bitrate Network bandwidth in kbps. 
     * @param jitter Network jitter in ms 
     */
    virtual void onNetworkDetectionResult(NetworkDetectionLinkType type, NetworkQuality quality, int rtt, double lost_rate,
                                      int bitrate, int jitter){
        (void)type;
        (void)quality;
        (void)rtt;
        (void)lost_rate;
        (void)bitrate;
        (void)jitter;
    }

    /**
     * @locale zh
     * @type callback
     * @region 通话前网络探测
     * @brief 通话前网络探测结束<br>
     *        以下情况将停止探测并收到本一次本回调：<br>
     *        1. 当调用 stopNetworkDetection{@link #IRTCVideo#stopNetworkDetection} 接口停止探测后，会收到一次该回调；<br>
     *        2. 当收到远端/本端音频首帧后，停止探测；<br>
     *        3. 当探测超过3分钟后，停止探测；<br>
     *        4. 当探测链路断开一定时间之后，停止探测。
     * @param reason  <br>
     *        停止探测的原因类型,参考 NetworkDetectionStopReason{@link #NetworkDetectionStopReason}  
     */
    /**
     * @locale en
     * @type callback
     * @region Pre-call network probing
     * @brief Pre-call network probing ends <br>
     *        The following will stop detection and receive this primary callback:  <br>
     *        1. This callback is received once when the stopNetworkDetection{@link #IRTCVideo#stopNetworkDetection} interface is called to stop probing;  <br>
     *        2. Stop detection when the first frame of remote/local audio is received;  <br>
     *        3. Stop detecting when the detection exceeds 3 minutes;  <br>
     *        4. When the probe link is disconnected for a certain period of time, the probe is stopped.
     * @param reason   <br>
     *        See NetworkDetectionStopReason{@link #NetworkDetectionStopReason} for reasons of stopping probing.
     */
    virtual void onNetworkDetectionStopped(NetworkDetectionStopReason reason){
        (void)reason;
    }
    /**
     * @locale zh
     * @type callback
     * @brief 订阅公共流的结果回调<br>
     *        通过 startPlayPublicStream{@link #IRTCVideo#startPlayPublicStream} 订阅公共流后，可以通过本回调获取订阅结果。
     * @param public_stream_id 公共流的 ID
     * @param error_code 公共流订阅结果状态码。详见 PublicStreamErrorCode{@link #PublicStreamErrorCode}。
     */
    /**
     * @locale en
     * @hidden currently not available
     * @type callback
     * @brief Callback of the result of subscribing to the public stream<br>
     *        You will be informed of the result of subscribing to the public stream by this callback after calling startPlayPublicStream{@link #IRTCVideo#startPlayPublicStream}.
     * @param public_stream_id
     * @param error_code Code for the result of playing the public stream. Refer to PublicStreamErrorCode{@link #PublicStreamErrorCode} for details.
     */
    virtual void onPlayPublicStreamResult(const char* public_stream_id, PublicStreamErrorCode error_code) {
        (void)public_stream_id;
        (void)error_code;
    }
    /**
     * @locale zh
     * @type callback
     * @brief 回调公共流中包含的 SEI 信息。<br>
     *        调用 startPlayPublicStream{@link #IRTCVideo#startPlayPublicStream} 接口启动拉公共流功能后，通过此回调收到公共流中的 SEI 消息。
     * @param public_stream_id 公共流 ID。
     * @param message 收到的 SEI 消息内容。<br>
     * 通过调用客户端 `sendSEIMessage` 插入的 SEI 信息。<br>
     * 当公共流中的多路视频流均包含有 SEI 信息：SEI 不互相冲突时，将通过多次回调分别发送；SEI 在同一帧有冲突时，则只有一条流中的 SEI 信息被透传并融合到公共流中。
     * @param message_length SEI 信息的长度。
     * @param source_type SEI 消息类型，自 3.52.1 版本后固定为 `0`，自定义消息。参看 DataMessageSourceType{@link #DataMessageSourceType}。
     * @note  
     * 通过 Open API 插入的自定义信息，应通过回调 onPublicStreamDataMessageReceived{@link #IRTCVideoEventHandler#onPublicStreamDataMessageReceived} 获取。
     */
    /**
     * @locale en
     * @hidden currently not available
     * @type callback
     * @brief Callback on receiving the SEI message carried by the public video stream.<br>
     *        After calling startPlayPublicStream{@link #IRTCVideo#startPlayPublicStream}, you will receive this callback if the public stream has an SEI message.
     * @param public_stream_id The ID of the public stream.
     * @param message The SEI(supplemental enhancement information) message carried by the public video stream.<br>
     * The SEI you can get via this callback is inserted by calling `sendSEIMessage` in the SDK.<br>
     * You receive SEI from all the video streams if the SEI messages do not have conflicts. However, if the SEI messages from different video streams have conflicts, you will receive only one of them.
     * @param sourceType SEI source type. Since V3.52.1, the value is always `0`, for custom messages. See DataMessageSourceType{@link #DataMessageSourceType}. 
     * @note 
     * You also need to listen to onPublicStreamDataMessageReceived{@link #IRTCVideoEventHandler#onPublicStreamDataMessageReceived} to receive data messages inserted via Open API in the server.
     */
    virtual void onPublicStreamSEIMessageReceived(const char* public_stream_id,
        const uint8_t* message,
        int message_length,
        DataMessageSourceType source_type) {
        (void)public_stream_id;
        (void)message;
        (void)message_length;
        (void)source_type;
    }

    /**
     * @locale zh
     * @valid since 3.56
     * @hidden for internal use only
     * @type callback
     * @brief 回调公共流中包含的 SEI 信息。<br>
     *        调用 startPlayPublicStream{@link #IRTCVideo#startPlayPublicStream} 接口启动拉公共流功能后，通过此回调收到公共流中的 SEI 消息。
     * @param public_stream_id 公共流 ID。
     * @param channel_id SEI 的消息传输通道，取值范围 [0 - 255]。通过此参数，你可以为不同接受方设置不同的 ChannelID，这样不同接收方可以根据回调中的 ChannelID 选择应关注的 SEI 信息。
     * @param message 收到的 SEI 消息内容。<br>
     * 通过调用客户端 `sendPublicStreamSEIMessage` 插入的 SEI 信息。
     * @param message_length SEI 信息的长度。
     */
    /**
     * @locale en
     * @valid since 3.56
     * @hidden for internal use only
     * @type callback
     * @brief Callback on receiving the SEI message carried by the public video stream.<br>
     *        After calling startPlayPublicStream{@link #IRTCVideo#startPlayPublicStream}, you will receive this callback if the public stream has an SEI message.
     * @param public_stream_id The ID of the public stream.
     * @param channel_id SEI message channel ID. The value range is [0 - 255]. With this parameter, you can set different ChannelIDs for different recipients. In this way, different recipients can choose the SEI information  based on the ChannelID received in the callback.
     * @param message The SEI(supplemental enhancement information) message carried by the public video stream.<br>
     * The SEI you can get via this callback is inserted by calling `sendPublicStreamSEIMessage` in the SDK.
     * @param message_length SEI message length.
     */
    virtual void onPublicStreamSEIMessageReceivedWithChannel(const char* public_stream_id, int channel_id,
                                                  const uint8_t* message, int message_length) {
        (void)public_stream_id;
        (void)channel_id;
        (void)message;
        (void)message_length;
    }
    /**
     * @locale zh
     * @type callback
     * @valid since 3.52
     * @brief 回调公共流中包含的数据信息。<br>
     *        通过 startPlayPublicStream{@link #IRTCVideo#startPlayPublicStream} 订阅公共流后，通过监听本回调获取公共流中的数据消息，包括调用 Open API 发送的 SEI 消息和音量回调。
     * @param public_stream_id 公共流 ID
     * @param message 收到的数据消息内容，如下：<br>
     * + 调用公共流 OpenAPI 发送的自定义消息。<br>
     * + 媒体流音量变化，需要通过公共流 OpenAPI 开启回调。JSON 格式说明如下：<br>
     * {<br>
     * &nbsp;&nbsp;&nbsp;&nbsp;"Type"&nbsp;:&nbsp;"VolumeIndication", //具体业务类型<br>
     * &nbsp;&nbsp;&nbsp;&nbsp;"VolumeInfos"[&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;// 业务类型对应信息<br>
     * &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;{<br>
     * &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"RoomId":"1000001", // 房间ID<br>
     * &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"UserId":"1000001", // 用户ID<br>
     * &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"StreamType":0, // 0:摄像头流；1:屏幕流<br>
     * &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"LinearVolume":1 // 线性音量大小<br>
     * &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;}<br>
     * &nbsp;&nbsp;&nbsp;&nbsp;]<br>
     * }
     * @param message_length 消息的长度
     * @param source_type 数据消息来源，参看 DataMessageSourceType{@link #DataMessageSourceType}。
     * @note 通过调用客户端 API 插入的 SEI 信息，应通过回调 onPublicStreamSEIMessageReceived{@link #IRTCVideoEventHandler#onPublicStreamSEIMessageReceived} 获取。
     */
    /**
     * @locale en
     * @hidden currently not available
     * @type callback
     * @brief Callback on receiving the data message carried by the public video stream.<br>
     *        After calling startPlayPublicStream{@link #IRTCVideo#startPlayPublicStream}, you can listen to this callback and retrieve SEI messages inserted by Open API calls or audio volume.
     * @param public_stream_id ID of the public stream
     * @param message The data messages carried by the public video stream.<br>
     * + Data inserted by calling the OpenAPI.<br>
     * + Media volume in JSON, before you can receive which you need to enable it via calling the OpenAPI. Refer to the definition below to parse the JSON string.<br>
     * {<br>
     * &nbsp;&nbsp;&nbsp;&nbsp;"Type"&nbsp;:&nbsp;"VolumeIndication",<br>
     * &nbsp;&nbsp;&nbsp;&nbsp;"VolumeInfos":[<br>
     * &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;{<br>
     * &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"RoomId":"1000001",<br>
     * &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"UserId":"1000001",<br>
     * &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"StreamType":0,&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;//  `0` for main stream and `1` for the screen sharing stream<br>
     * &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"LinearVolume":1<br>
     * &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;}<br>
     * &nbsp;&nbsp;&nbsp;&nbsp;]<br>
     * }
     * @param message_length Length of the message
     * @param source_type Message source. See DataMessageSourceType{@link #DataMessageSourceType}.
     * @note You also need to listen to onPublicStreamSEIMessageReceived{@link #IRTCVideoEventHandler#onPublicStreamSEIMessageReceived} to receive SEI inserted via API in the client SDK.
     */
    virtual void onPublicStreamDataMessageReceived(const char* public_stream_id,
        const uint8_t* message,
        int message_length,
        DataMessageSourceType source_type) {
        (void)public_stream_id;
        (void)message;
        (void)message_length;
        (void)source_type;
    }
    /**
     * @locale zh
     * @type callback
     * @brief 公共流的首帧视频解码成功<br>
     *        关于订阅公共流，详见 startPlayPublicStream{@link #IRTCVideo#startPlayPublicStream}。
     * @param public_stream_id 公共流 ID
     * @param info 视频帧信息。详见 VideoFrameInfo{@link #VideoFrameInfo}。
     */
    /**
     * @locale en
     * @hidden currently not available
     * @type callback
     * @brief Callback of successfully decoding of the first video frame of the public stream<br>
     *        Refer to startPlayPublicStream{@link #IRTCVideo#startPlayPublicStream} for details about subscribing to a public stream.
     * @param public_stream_id ID of the public stream
     * @param info Information of the video stream. Refer to VideoFrameInfo{@link #VideoFrameInfo} for more details.
     */
    virtual void onFirstPublicStreamVideoFrameDecoded(const char* public_stream_id, const VideoFrameInfo& info) {
        (void)public_stream_id;
    }
    /**
     * @locale zh
     * @type callback
     * @region 视频事件回调
     * @brief 房间内的可见用户调用 startVideoCapture{@link #IRTCVideo#startVideoCapture} 开启内部视频采集时，房间内其他用户会收到此回调。
     * @param room_id 开启视频采集的远端用户所在的房间 ID
     * @param user_id 开启视频采集的远端用户 ID
     */
    /**
     * @locale en
     * @type callback
     * @region Video event callback
     * @brief The remote clients in the room will be informed of the state change via this callback after the visible user starts video capture by calling startVideoCapture{@link #IRTCVideo#startVideoCapture}.
     * @param room_id ID of the room from which the remote video stream is published.
     * @param user_id The user who starts the internal video capture
     */
    virtual void onUserStartVideoCapture(const char* room_id, const char* user_id) {
        (void)user_id;
    }
    /**
     * @locale zh
     * @type callback
     * @region 视频事件回调
     * @brief 房间内的可见用户调用 stopVideoCapture{@link #IRTCVideo#stopVideoCapture} 关闭内部视频采集时，房间内其他用户会收到此回调。<br>
     *        若发布视频数据前未开启采集，房间内所有可见用户会收到此回调。
     * @param room_id ID of the room where the remote video stream stops being published.
     * @param user_id 关闭视频采集的远端用户 ID
     */
    /**
     * @locale en
     * @type callback
     * @region Video event callback
     * @brief The remote clients in the room will be informed of the state change via  this callback after the visible user stops video capture by calling stopVideoCapture{@link #IRTCVideo#stopVideoCapture}.<br>
     *        If you don't start video capture before you publish video data, all visible user will receive this callback.
     * @param room_id ID of the room
     * @param user_id The user who stops the internal video capture
     */
    virtual void onUserStopVideoCapture(const char* room_id, const char* user_id) {
        (void)user_id;
    }
    /**
     * @locale zh
     * @type callback
     * @region 视频管理
     * @brief 本地视频大小或旋转信息发生改变时，收到此回调。
     * @param index 流属性。参看 StreamIndex{@link #StreamIndex}。
     * @param info 视频帧信息。参看 VideoFrameInfo{@link #VideoFrameInfo}。
     */
    /**
     * @locale en
     * @type callback
     * @region video management
     * @brief Receive this callback when the local video size or rotation configuration changes.
     * @param index See StreamIndex{@link #StreamIndex}。
     * @param info Video frame information. See VideoFrameInfo{@link #VideoFrameInfo}.
     */
    virtual void onLocalVideoSizeChanged(StreamIndex index, const VideoFrameInfo& info) {
        (void)index;
        (void)info;
    }
    /**
     * @locale zh
     * @type callback
     * @region 视频管理
     * @brief 远端视频大小或旋转信息发生改变时，房间内订阅此视频流的用户会收到此回调。
     * @param key 远端流信息。参看 RemoteStreamKey{@link #RemoteStreamKey}。
     * @param info 视频帧信息。参看 VideoFrameInfo{@link #VideoFrameInfo}。
     */
    /**
     * @locale en
     * @type callback
     * @region Video Management
     * @brief Users in the room who subscribe to this video stream receive this callback when the remote video size or rotation configuration changes.
     * @param key Remote stream information. See RemoteStreamKey{@link #RemoteStreamKey}.
     * @param info Video frame information. See VideoFrameInfo{@link #VideoFrameInfo}.
     */
    virtual void onRemoteVideoSizeChanged(RemoteStreamKey key, const VideoFrameInfo& info) {
        (void)key;
        (void)info;
    }
    /**
     * @locale zh
     * @type callback
     * @region 视频管理
     * @brief RTC SDK 在本地完成第一帧视频帧或屏幕视频帧采集时，收到此回调。
     * @param index 流属性。参看 StreamIndex{@link #StreamIndex}。
     * @param info 视频信息。参看 VideoFrameInfo{@link #VideoFrameInfo}。
     * @note 对于采集到的本地视频帧，你可以调用 setLocalVideoCanvas{@link #IRTCVideo#setLocalVideoCanvas} 或 setLocalVideoSink{@link #IRTCVideo#setLocalVideoSink} 在本地渲染。
     */
    /**
     * @locale en
     * @type callback
     * @region Video Management
     * @brief RTC SDK receives this callback when the first video frame or screen video frame capture is completed locally.
     * @param index Stream property. See StreamIndex{@link #StreamIndex}.
     * @param info Video information. See VideoFrameInfo{@link #VideoFrameInfo}.
     * @note For captured local video frames, you can call setLocalVideoCanvas{@link #IRTCVideo#setLocalVideoCanvas} or setLocalVideoSink{@link #IRTCVideo#setLocalVideoSink} to render locally.
     */
    virtual void onFirstLocalVideoFrameCaptured(StreamIndex index, VideoFrameInfo info) {
        (void)index;
        (void)info;
    }
    /**
     * @locale zh
     * @deprecated since 3.36 and will be deleted in 3.51, use onUserPublishStream{@link #IRTCRoomEventHandler#onUserPublishStream}, onUserPublishScreen{@link #IRTCRoomEventHandler#onUserPublishScreen}, onUserUnpublishStream{@link #IRTCRoomEventHandler#onUserUnpublishStream} and onUserUnpublishScreen{@link #IRTCRoomEventHandler#onUserUnpublishScreen} instead.
     * @type callback
     * @region 媒体流管理
     * @brief 房间内用户暂停/恢复发送音频流时，房间内其他用户会收到此回调。
     * @param user_id 改变本地音频发送状态的用户 ID
     * @param mute_state 发送状态，参看 MuteState{@link #MuteState}
     */
    /**
     * @locale en
     * @deprecated since 3.45 and will be deleted in 3.51, use onUserPublishStream{@link #IRTCRoomEventHandler#onUserPublishStream}, onUserPublishScreen{@link #IRTCRoomEventHandler#onUserPublishScreen}, onUserUnpublishStream{@link #IRTCRoomEventHandler#onUserUnpublishStream} and onUserUnpublishScreen{@link #IRTCRoomEventHandler#onUserUnpublishScreen} instead.
     * @type callback
     * @region Media Stream Management
     * @brief Transmission state change of an audio stream in the room triggers this callback.
     * @param user_id The user who changes his/her transmission state of the audio streams
     * @param mute_state Transmission state of the audio streams. Refer to MuteState{@link #MuteState} for more details.
     */
    BYTERTC_DEPRECATED virtual void onUserMuteAudio(const char* room_id, const char* user_id, MuteState mute_state) {
        (void)user_id;
        (void)mute_state;
    }
    /**
     * @locale zh
     * @type callback
     * @region 音频事件回调
     * @brief 接收到来自远端某音频流的第一帧时，收到该回调。
     * @param key 远端音频流信息, 详见 RemoteStreamKey{@link #RemoteStreamKey}
     * @note 用户刚收到房间内每一路音频流时，都会收到该回调。
     */
    /**
     * @locale en
     * @type callback
     * @region Audio event callback
     * @brief Receives the callback when the first frame from a remote audio stream is received.
     * @param key Remote audio stream information. See RemoteStreamKey{@link #RemoteStreamKey}
     * @note The callback is received when the user has just received each audio stream in the room.
     */
    virtual void onFirstRemoteAudioFrame(const RemoteStreamKey& key) {
        (void)key;
    }
    /**
     * @locale zh
     * @deprecated since 3.36 and will be deleted in 3.51, use onUserPublishStream{@link #IRTCRoomEventHandler#onUserPublishStream}, onUserPublishScreen{@link #IRTCRoomEventHandler#onUserPublishScreen}, onUserUnpublishStream{@link #IRTCRoomEventHandler#onUserUnpublishStream} and onUserUnpublishScreen{@link #IRTCRoomEventHandler#onUserUnpublishScreen} instead.
     * @type callback
     * @region 媒体流管理
     * @brief 房间内用户暂停/恢复发送视频流时，房间内其他用户会收到此回调。
     * @param uid 暂停/恢复发送视频流的用户 ID。
     * @param mute 视频流的发送状态。参看 MuteState{@link #MuteState}。
     */
    /**
     * @locale en
     * @deprecated since 3.45 and will be deleted in 3.51, use onUserPublishStream{@link #IRTCRoomEventHandler#onUserPublishStream}, onUserPublishScreen{@link #IRTCRoomEventHandler#onUserPublishScreen}, onUserUnpublishStream{@link #IRTCRoomEventHandler#onUserUnpublishStream} and onUserUnpublishScreen{@link #IRTCRoomEventHandler#onUserUnpublishScreen} instead.
     * @type callback
     * @region Media Stream Management
     * @brief Transmission state change of an video stream in the room triggers this callback.
     * @param uid The user who changes his/her transmission state of the video streams
     * @param mute Transmission state of the video streams. Refer to MuteState{@link #MuteState} for more details.
     */
    BYTERTC_DEPRECATED virtual void onUserMuteVideo(const char* room_id, const char* uid, MuteState mute) {
        (void)uid;
        (void)mute;
    }
    /**
     * @locale zh
     * @type callback
     * @region 音频事件回调
     * @brief 用户订阅来自远端的音频流状态发生改变时，会收到此回调，了解当前的远端音频流状态。
     * @param key 远端流信息, 参看 RemoteStreamKey{@link #RemoteStreamKey}
     * @param state 远端音频流状态，参看 RemoteAudioState{@link #RemoteAudioState}
     * @param reason 远端音频流状态改变的原因，参看 RemoteAudioStateChangeReason{@link #RemoteAudioStateChangeReason}
     */
    /**
     * @locale en
     * @type callback
     * @region Audio event callback
     * @brief When the state of the audio stream from the remote user subscribes to changes, this callback will be received to understand the current state of the remote audio stream.
     * @param key Remote stream information. See RemoteStreamKey{@link #RemoteStreamKey}
     * @param state Remote audio stream state. See RemoteAudioState{@link #RemoteAudioState}
     * @param reason For remote audio stream state change. See RemoteAudioStateChangeReason{@link #RemoteAudioStateChangeReason}
     */
    virtual void onRemoteAudioStateChanged(
            const RemoteStreamKey& key, RemoteAudioState state, RemoteAudioStateChangeReason reason) {
        (void)key;
        (void)state;
        (void)reason;
    }
    /**
     * @locale zh
     * @type callback
     * @region 视频管理
     * @brief 本地视频流的状态发生改变时，收到该事件。
     * @param index 音/视频属性，参看 StreamIndex{@link #StreamIndex}
     * @param state 本地视频流状态，参看 LocalVideoStreamState{@link #LocalVideoStreamState}
     * @param error 本地视频状态改变时的错误码，参看 LocalVideoStreamError{@link #LocalVideoStreamError}
     */
    /**
     * @locale en
     * @type callback
     * @region video management [in]
     * @brief Receive this event when the state of the local video stream changes.
     * @param index Index audio/video properties. See StreamIndex{@link #StreamIndex}
     * @param state Local video stream status. See LocalVideoStreamState{@link #LocalVideoStreamState}
     * @param error Error code when local video status changes. See LocalVideoStreamError{@link #LocalVideoStreamError}
     */
    virtual void onLocalVideoStateChanged(StreamIndex index, LocalVideoStreamState state, LocalVideoStreamError error) {
        (void)index;
        (void)state;
        (void)error;
    }
    /**
     * @locale zh
     * @type callback
     * @region 视频管理
     * @brief 远端视频流的状态发生改变时，房间内订阅此流的用户会收到该事件。
     * @param key 远端视频流的信息，房间、用户 ID、流属性等。参看 RemoteStreamKey{@link #RemoteStreamKey}。
     * @param state 远端视频流状态，参看 RemoteVideoState{@link #RemoteVideoState}。
     * @param reason 远端视频流状态改变的原因，参看 RemoteVideoStateChangeReason{@link #RemoteVideoStateChangeReason}。
     * @note 本回调仅适用于主流，不适用于屏幕流。
     */
    /**
     * @locale en
     * @type callback
     * @region Video Management
     * @brief When the state of a remote video stream changes, users in the room who subscribe to this stream receive the event.
     * @param key Information about the remote video stream, room, user ID, stream attributes, etc. See RemoteStreamKey{@link #RemoteStreamKey}.
     * @param state Remote video stream state. See RemoteVideoState{@link #RemoteVideoState}.
     * @param reason For the remote video stream state change. See RemoteVideoStateChangeReason{@link #RemoteVideoStateChangeReason}.
     */
    virtual void onRemoteVideoStateChanged(
            RemoteStreamKey key, RemoteVideoState state, RemoteVideoStateChangeReason reason) {
        (void)key;
        (void)state;
        (void)reason;
    }

    /**
     * @locale zh
     * @valid since 3.54
     * @hidden(Windows, macOS, Linux)
     * @type callback
     * @region 音视频处理
     * @brief 远端视频流的超分状态发生改变时，房间内订阅此流的用户会收到该回调。
     * @param stream_key 远端流信息，包括房间 ID、用户 ID、流属性，参看 RemoteStreamKey{@link #RemoteStreamKey}。
     * @param mode 超分模式，参看 VideoSuperResolutionMode{@link #VideoSuperResolutionMode}。
     * @param reason 超分模式改变原因，参看 VideoSuperResolutionModeChangedReason{@link #VideoSuperResolutionModeChangedReason}。
     */
    /**
     * @locale en
     * @hidden not available
     * @type callback
     * @region Audio & Video Processing
     * @brief When the super resolution mode of a remote video stream changes, users in the room who subscribe to this stream will receive this callback.
     * @param stream_key Remote stream information that includes the room ID, user ID, and stream type. See RemoteStreamKey{@link #RemoteStreamKey}.
     * @param mode Super resolution mode. See VideoSuperResolutionMode{@link #VideoSuperResolutionMode}.
     * @param reason Remote video stream super resolution mode change reason. See VideoSuperResolutionModeChangedReason{@link #VideoSuperResolutionModeChangedReason}
     */
    virtual void onRemoteVideoSuperResolutionModeChanged(
            RemoteStreamKey stream_key, VideoSuperResolutionMode mode, VideoSuperResolutionModeChangedReason reason) {
        (void)stream_key;
        (void)mode;
        (void)reason;
    }

    /**
     * @locale zh
     * @valid since 3.54
     * @hidden(Windows, macOS, Linux)
     * @type callback
     * @region 音视频处理
     * @brief 降噪模式状态变更回调。当降噪模式的运行状态发生改变，SDK 会触发该回调，提示用户降噪模式改变后的运行状态及状态发生改变的原因。          
     * @param mode 视频降噪模式，参看 VideoDenoiseMode{@link #VideoDenoiseMode}。
     * @param reason 视频降噪模式改变的原因，参看 VideoDenoiseModeChangedReason{@link #VideoDenoiseModeChangedReason}。
     */
    /**
     * @locale en
     * @hidden not available
     * @type callback
     * @region Audio & Video Processing
     * @brief When the state of the video noise reduction mode changes, this callback will return the real state of the<br>
     * mode and the reasons for the changes.
     * @param mode Video noise reduction mode. Refer to VideoDenoiseMode{@link #VideoDenoiseMode} for more details.
     * @param reason Video noise reduction mode change reason. Refer to VideoDenoiseModeChangedReason{@link<br>
     * #VideoDenoiseModeChangedReason} for more details.
     */
    virtual void onVideoDenoiseModeChanged(VideoDenoiseMode mode, VideoDenoiseModeChangedReason reason) {
       (void)mode;
       (void)reason;
    }
    
    /**
     * @locale zh
     * @type callback
     * @region 房间管理
     * @brief 本地音频首帧发送状态发生改变时，收到此回调。
     * @param room_id 音频发布用户所在的房间 ID
     * @param user 本地用户信息，详见 RtcUser{@link #RtcUser}
     * @param state 首帧发送状态，详见 FirstFrameSendState{@link #FirstFrameSendState}
     */
    /**
     * @locale en
     * @type callback
     * @region Room management
     * @brief Audio first frame sending status change callback
     * @param room_id ID of the room where the audio is published
     * @param user Local user information. See RtcUser{@link #RtcUser}
     * @param state First frame sending status. See FirstFrameSendState{@link #FirstFrameSendState}
     */
    virtual void onAudioFrameSendStateChanged(const char* room_id, const RtcUser& user, FirstFrameSendState state) {
        (void)user;
        (void)state;
    }

    /**
     * @locale zh
     * @type callback
     * @region 房间管理
     * @brief 屏幕音频首帧发送状态改变回调
     * @param room_id 音频发布用户所在的房间 ID
     * @param user 本地用户信息，详见 RtcUser{@link #RtcUser}
     * @param state 首帧发送状态，详见 FirstFrameSendState{@link #FirstFrameSendState}
     */
    /**
     * @locale en
     * @type callback
     * @region Room management
     * @brief Screen Audio first frame sending status change callback
     * @param room_id ID of the room where the audio is published
     * @param user Local user information. See RtcUser{@link #RtcUser}
     * @param state First frame sending status. See FirstFrameSendState{@link #FirstFrameSendState}
     */
    virtual void onScreenAudioFrameSendStateChanged(const char* room_id, const RtcUser& user, FirstFrameSendState state) {
        (void)user;
        (void)state;
    }

    /**
     * @locale zh
     * @type callback
     * @region 房间管理
     * @brief 本地视频首帧发送状态发生改变时，收到此回调。
     * @param room_id 视频发布用户所在的房间 ID
     * @param user 本地用户信息，详见 RtcUser{@link #RtcUser}
     * @param state 首帧发送状态，详见 FirstFrameSendState{@link #FirstFrameSendState}
     */
    /**
     * @locale en
     * @type callback
     * @region Room management
     * @brief Video first frame sending status change callback
     * @param room_id ID of the room where the video is published
     * @param user Local user information. See RtcUser{@link #RtcUser}
     * @param state First frame sending status. See FirstFrameSendState{@link #FirstFrameSendState}
     */
    virtual void onVideoFrameSendStateChanged(const char* room_id, const RtcUser& user, FirstFrameSendState state) {
        (void)user;
        (void)state;
    }
    /**
     * @locale zh
     * @type callback
     * @region 视频管理
     * @brief SDK 内部渲染成功远端视频流首帧后，收到此回调。
     * @param key 远端流信息。参看 RemoteStreamKey{@link #RemoteStreamKey}。
     * @param info 视频帧信息。参看 VideoFrameInfo{@link #VideoFrameInfo}。
     */
    /**
     * @locale en
     * @type callback
     * @region Video Management
     * @brief  Receive this callback after the first frame of remote video stream is locally rendered by SDK.
     * @param key Remote stream information. See RemoteStreamKey{@link #RemoteStreamKey}.
     * @param info Video frame information. See VideoFrameInfo{@link #VideoFrameInfo}.
     */
    virtual void onFirstRemoteVideoFrameRendered(const RemoteStreamKey key, const VideoFrameInfo& info) {
        (void)key;
        (void)info;
    }
    /**
     * @locale zh
     * @type callback
     * @region 视频管理
     * @brief SDK 接收并解码远端视频流首帧后，收到此回调。
     * @param key 远端流信息。参看 RemoteStreamKey{@link #RemoteStreamKey}。
     * @param info 视频帧信息。参看 VideoFrameInfo{@link #VideoFrameInfo}。
     * @note 
     *       + 对于主流，进入房间后，仅在发布端第一次发布的时候，订阅端会收到该回调，此后不受重新发布的影响，只要不重新加入房间，就不会再收到该回调。<br>
     *       + 对于屏幕流，用户每次重新发布屏幕视频流在订阅端都会重新触发一次该回调。
     */
    /**
     * @locale en
     * @type callback
     * @region Video Management
     * @brief Receive this callback after the first frame of remote video stream is received and decoded by SDK.
     * @param key Remote stream information. See RemoteStreamKey {@link #RemoteStreamKey}.
     * @param info Video frame information. See VideoFrameInfo {@link #VideoFrameInfo}.
     * @note 
     *       + For main stream, after joining the room, the subscriber will receive this callback only when the publisher publishes video stream for the first time.<br>
     *       + For screen-sharing stream, the subscriber will receive this callback every time the publisher publishes or republishes the screen video stream.
     */
    virtual void onFirstRemoteVideoFrameDecoded(const RemoteStreamKey key, const VideoFrameInfo& info) {
        (void)key;
        (void)info;
    }
    /**
     * @locale zh
     * @type callback
     * @region 房间管理
     * @brief 屏幕共享流的视频首帧发送状态发生改变时，收到此回调。
     * @param room_id 流的发布房间的 ID
     * @param user 本地用户信息，详见 RtcUser{@link #RtcUser}
     * @param state 首帧发送状态，详见 FirstFrameSendState{@link #FirstFrameSendState}
     */
    /**
     * @locale en
     * @type callback
     * @region room management
     * @brief Screen sharing streaming video first frame sending status change callback
     * @param room_id ID of the room from which the screen stream is published.
     * @param user Local user information. See RtcUser{@link #RtcUser}
     * @param state First frame sending status. See FirstFrameSendState{@link #FirstFrameSendState}
     */
    virtual void onScreenVideoFrameSendStateChanged(const char* room_id, const RtcUser& user, FirstFrameSendState state) {
        (void)user;
        (void)state;
    }
    /**
     * @locale zh
     * @type callback
     * @region 房间管理
     * @brief 音频首帧播放状态发生改变时，收到此回调。
     * @param room_id 首帧播放状态发生改变的流所在的房间 ID
     * @param user 远端用户信息，详见 RtcUser{@link #RtcUser}
     * @param state 首帧播放状态，详见 FirstFramePlayState{@link #FirstFramePlayState}
     */
    /**
     * @locale en
     * @type callback
     * @region  room management
     * @brief  Audio first frame playback state change callback
     * @param room_id ID of the room from which the stream is published
     * @param user Remote user information. See RtcUser{@link #RtcUser}
     * @param state First frame playback status. See FirstFramePlayState{@link #FirstFramePlayState}
     */
    virtual void onAudioFramePlayStateChanged(const char* room_id, const RtcUser& user, FirstFramePlayState state) {
        (void)user;
        (void)state;
    }
    /**
     * @locale zh
     * @type callback
     * @region 房间管理
     * @brief 屏幕音频首帧播放状态改变回调
     * @param room_id 首帧播放状态发生改变的流所在的房间 ID
     * @param user 远端用户信息，详见 RtcUser{@link #RtcUser}
     * @param state 首帧播放状态，详见 FirstFramePlayState{@link #FirstFramePlayState}
     */
    /**
     * @locale en
     * @type callback
     * @region  room management
     * @brief  Screen Audio first frame playback state change callback
     * @param room_id ID of the room from which the stream is published
     * @param user Remote user information. See RtcUser{@link #RtcUser}
     * @param state First frame playback status. See FirstFramePlayState{@link #FirstFramePlayState}
     */
    virtual void onScreenAudioFramePlayStateChanged(const char* room_id, const RtcUser& user, FirstFramePlayState state) {
        (void)user;
        (void)state;
    }
    /**
     * @locale zh
     * @type callback
     * @region 房间管理
     * @brief 视频首帧播放状态改变回调
     * @param room_id 首帧播放状态发生改变的流所在的房间 ID
     * @param user 远端用户信息，详见 RtcUser{@link #RtcUser}
     * @param state 首帧播放状态，详见 FirstFramePlayState{@link #FirstFramePlayState}
     */
    /**
     * @locale en
     * @type callback
     * @region  room management
     * @brief  Video first frame playback state change callback
     * @param room_id ID of the room from which the stream is published
     * @param user Remote user information. See RtcUser{@link #RtcUser}
     * @param state First frame playback state. See FirstFramePlayState{@link #FirstFramePlayState}
     */
    virtual void onVideoFramePlayStateChanged(const char* room_id, const RtcUser& user, FirstFramePlayState state) {
        (void)user;
        (void)state;
    }
    /**
     * @locale zh
     * @type callback
     * @region 房间管理
     * @brief 屏幕共享流视频首帧播放状态发生改变时，收到此回调。
     * @param room_id 首帧播放状态发生改变的流所在的房间 ID
     * @param user 远端用户信息，详见 RtcUser{@link #RtcUser}
     * @param state 首帧播放状态，详见 FirstFramePlayState{@link #FirstFramePlayState}
     */
    /**
     * @locale en
     * @type callback
     * @region room management
     * @brief Screen sharing streaming video first frame playback state change callback
     * @param room_id ID of the room from which the stream is published
     * @param user Remote user information. See RtcUser{@link #RtcUser}
     * @param state First frame playback state. See FirstFramePlayState{@link #FirstFramePlayState}
     */
    virtual void onScreenVideoFramePlayStateChanged(const char* room_id, const RtcUser& user, FirstFramePlayState state) {
        (void)user;
        (void)state;
    }

    /**
     * @locale zh
     * @type callback
     * @region 音频事件回调
     * @brief 发布音频流时，采集到第一帧音频帧，收到该回调。
     * @param index 音频流属性, 参看 StreamIndex{@link #StreamIndex}
     * @note 如果发布音频流时，未开启本地音频采集，SDK 会推送静音帧，也会收到此回调。
     */
    /**
     * @locale en
     * @type callback
     * @region Audio event callback
     * @brief Receive the callback when publishing local audio stream.
     * @param index Audio stream properties. See StreamIndex{@link #StreamIndex}
     */
    virtual void onFirstLocalAudioFrame(StreamIndex index) {
        (void)index;
    }
    /**
     * @locale zh
     * @type callback
     * @brief 公共流发布结果回调。<br>
     *        调用 startPushPublicStream{@link #IRTCVideo#startPushPublicStream} 接口发布公共流后，启动结果通过此回调方法通知用户。
     * @param room_id 公共流的发布房间的 ID
     * @param public_streamid 公共流 ID
     * @param error_code 公共流发布结果状态码。详见 PublicStreamErrorCode{@link #PublicStreamErrorCode}
     */
    /**
     * @locale en
     * @hidden currently not available
     * @type callback
     * @brief Callback of the result of publishing the public stream<br>
     *        You will be informed of the result of publishing the public stream by this callback after calling startPushPublicStream{@link #IRTCVideo#startPushPublicStream}.
     * @param room_id Room ID from which the public stream is published
     * @param public_streamid ID of the public stream
     * @param error_code Code for the result of publishing the public stream. Refer to PublicStreamErrorCode{@link #PublicStreamErrorCode} for details.
     */
    virtual void onPushPublicStreamResult(const char* room_id, const char* public_streamid, PublicStreamErrorCode error_code) {
        (void)room_id;
        (void)public_streamid;
        (void)error_code;
    }

    /**
     * @locale zh
     * @type callback
     * @brief 公共流的音频首帧解码成功<br>
     *        关于订阅公共流，详见 startPlayPublicStream{@link #IRTCVideo#startPlayPublicStream}。
     * @param public_stream_id 公共流 ID
     */
    /**
     * @locale en
     * @hidden currently not available
     * @type callback
     * @brief Callback of successfully decoding of the first audio frame of the public stream<br>
     *        Refer to startPlayPublicStream{@link #IRTCVideo#startPlayPublicStream} for details about subscribing to a public stream.
     * @param public_stream_id ID of the public stream
     */
    virtual void onFirstPublicStreamAudioFrame(const char* public_stream_id) {
        (void)public_stream_id;
    }
    /**
     * @locale zh
     * @type callback
     * @brief 调用 startCloudProxy{@link #IRTCVideo#startCloudProxy} 开启云代理，SDK 首次成功连接云代理服务器时，回调此事件。
     * @param interval 从开启云代理到连接成功经过的时间，单位为 ms
     */
    /**
     * @locale en
     * @type callback
     * @brief Receives the callback when you call startCloudProxy{@link #IRTCVideo#startCloudProxy} to start cloud proxy, and the SDK connects the proxy server successfully.
     * @param interval The interval in ms between starting cloud proxy and connects the cloud proxy server successfully.
     */
    virtual void onCloudProxyConnected(int interval) {
        (void)interval;
    }
    /**
     * @locale zh
     * @hidden(Linux)
     * @type callback
     * @region 网络管理
     * @brief 关于音视频回路测试结果的回调。
     * @param result 测试结果，参看 EchoTestResult{@link #EchoTestResult}
     * @note 该回调触发的时机包括： <br>
     *        + 检测过程中采集设备发生错误时；  <br>
     *        + 检测成功后；  <br>
     *        + 非设备原因导致检测过程中未接收到音/视频回放，停止检测后。
     */
    /**
     * @locale en
     * @hidden(Linux)
     * @type callback
     * @region Network Management
     * @brief Callback about the call test result.
     * @param result Test result, see EchoTestResult{@link #EchoTestResult}.
     * @note The timing when this callback will be triggered is as follows:  <br>
     *        + A device-related error occurred during the test；  <br>
     *        + After a successful test；  <br>
     *        + After stopping the test, provided that the audio/video playback was not received during the test due to non-device reasons.
     */
    virtual void onEchoTestResult(EchoTestResult result) {
        (void)result;
    };

    /**
     * @locale zh
     * @hidden for internal use only
     * @type callback
     * @brief 音频dump状态改变回调
     * @param status 音频dump状态，参见 AudioDumpStatus{@link #AudioDumpStatus}
     * @note 本回调用于内部排查音质相关异常问题，开发者无需关注。
     */

    /**
     * @locale en
     * @hidden for internal use only
     * @type callabck
     * @brief audio dump status change callback
     * @param status audio dump status, see AudioDumpStatus{@link #AudioDumpStatus}.
     * @note This callback is used to internally troubleshoot sound quality related exceptions, which developers need not pay attention to.
     */
    virtual void onAudioDumpStateChanged(AudioDumpStatus status) {
        (void)status;
    }
    /**
     * @locale zh
     * @hidden(Linux)
     * @type callback
     * @brief 首次调用 getNetworkTimeInfo{@link #IRTCVideo#getNetworkTimeInfo} 后，SDK 内部启动网络时间同步，同步完成时会触发此回调。
     */
    /**
     * @locale en
     * @hidden(Linux)
     * @type callback
     * @brief After calling getNetworkTimeInfo{@link #IRTCVideo#getNetworkTimeInfo} for the first time, the SDK starts network time synchronization internally. This callback will be triggered when the synchronization is completed.
     */
    virtual void onNetworkTimeSynchronized() {
    }
    /**
     * @locale zh
     * @hidden internal use only
     * @type callback
     * @brief license 过期提醒。在剩余天数低于 30 天时，收到此回调。
     * @param days license 剩余有效天数
     */
    /**
     * @locale en
     * @hidden internal use only
     * @type callabck
     * @brief License expiration reminder. Receive the callback when the license expires in less than 30 days.
     * @param days days remaining effective
     */
    virtual void onLicenseWillExpire(int days) {
        (void)days;
    }

    /**
     * @locale zh
     * @hidden(Linux,iOS)
     * @type callback
     * @brief 外部采集时，调用 setOriginalScreenVideoInfo{@link #IRTCVideo#setOriginalScreenVideoInfo}设置屏幕或窗口大小改变前的分辨率后，若屏幕采集模式为智能模式，你将收到此回调，根据 RTC 智能决策合适的帧率和分辨率积（宽*高）重新采集。
     * @param frame_update_info RTC 智能决策后合适的帧率和分辨率积（宽*高）。参看 FrameUpdateInfo{@link #FrameUpdateInfo}。
     */
    /**
     * @locale en
     * @hidden(Linux,iOS)
     * @type callback
     * @brief After calling setOriginalScreenVideoInfo{@link #IRTCVideo#setOriginalScreenVideoInfo} to set the original width and height of the external shared-screen stream and setting the encoding mode to the automatic mode, you will receive this callback to re-capture the stream based on the recommended pixel and framerate by RTC.
     * @param frame_update_info The recommended pixel and framerate by RTC. See FrameUpdateInfo{@link #FrameUpdateInfo}.
     */
    virtual void onExternalScreenFrameUpdate(FrameUpdateInfo frame_update_info) {
        (void)frame_update_info;
    }
    /**
     * @locale zh
     * @hidden internal use
     * @valid since 3.52
     * @type callback
     * @brief 试验性接口回调
     * @param param 回调内容(JSON string)
     */
    /**
     * @locale en
     * @hidden internal use
     * @valid since 3.52
     * @type callabck
     * @brief callback for experimental api
     * @param param result of callback in JSON string
     */
    virtual void onInvokeExperimentalAPI(const char* param) {
        (void)param;
    }
    /**
     * @locale zh
     * @hidden(Linux)
     * @type callback
     * @region 音频管理
     * @brief 通话前回声检测结果回调。
     * @param hardware_echo_detection_result 参见 HardwareEchoDetectionResult{@link #HardwareEchoDetectionResult}
     * @note 
     *        + 通话前调用 startHardwareEchoDetection{@link #IRTCVideo#startHardwareEchoDetection} 后，将触发本回调返回检测结果。<br>
     *        + 建议在收到检测结果后，调用 stopHardwareEchoDetection{@link #IRTCVideo#stopHardwareEchoDetection} 停止检测，释放对音频设备的占用。<br>
     *        + 如果 SDK 在通话中检测到回声，将通过 onAudioDeviceWarning{@link #IRTCVideoEventHandler#onAudioDeviceWarning} 回调 `kMediaDeviceWarningDetectLeakEcho`。
     */
    /**
     * @locale en
     * @hidden(Linux)
     * @type callback
     * @brief Callback that notifies you the result of the echo detection before a call
     * @param hardware_echo_detection_result Refer to HardwareEchoDetectionResult{@link #HardwareEchoDetectionResult} for more details.
     * @note  
     *        + This callback notifies you the result of the echo detection by calling startHardwareEchoDetection{@link #IRTCVideo#startHardwareEchoDetection}. <br>
     *        + We recommend to call stopHardwareEchoDetection{@link #IRTCVideo#stopHardwareEchoDetection} to stop the detection. <br>
     *        + Listen to `kMediaDeviceWarningDetectLeakEcho` in the callback of onAudioDeviceWarning{@link #IRTCVideoEventHandler#onAudioDeviceWarning} for the echo issue during a call.
     */
    virtual void onHardwareEchoDetectionResult(HardwareEchoDetectionResult hardware_echo_detection_result) {
        (void)hardware_echo_detection_result;
    }

    /**
     * @locale zh
     * @type callback
     * @region proxy
     * @brief 本地代理状态发生改变回调。调用 setLocalProxy{@link #IRTCVideo#setLocalProxy} 设置本地代理后，SDK 会触发此回调，返回代理连接的状态。
     * @param local_proxy_type 本地代理类型。参看 LocalProxyType{@link #LocalProxyType}。
     * @param local_proxy_state 本地代理状态。参看 LocalProxyState{@link #LocalProxyState}。
     * @param local_proxy_error 本地代理错误。参看 LocalProxyError{@link #LocalProxyError}。
     */
    /**
     * @locale en
     * @type callback
     * @region proxy
     * @brief Callback on local proxy connection. After calling setLocalProxy{@link #IRTCVideo#setLocalProxy} to set local proxies, you will receive this callback that informs you of the states of local proxy connection. 
     * @param local_proxy_type The types of local proxies. Refer to LocalProxyType{@link #LocalProxyType} for details.
     * @param local_proxy_state The states of local proxy connection. Refer to LocalProxyState{@link #LocalProxyState} for details.
     * @param local_proxy_error The errors of local proxy connection. Refer to LocalProxyError{@link #LocalProxyError} for details.
     */
    virtual void onLocalProxyStateChanged(LocalProxyType local_proxy_type, LocalProxyState local_proxy_state, LocalProxyError local_proxy_error) {
        (void)local_proxy_type;
        (void)local_proxy_state;
        (void)local_proxy_error;
    }
    /**
     * @locale zh
     * @hidden internal use only
     * @type callback
     * @brief 当特效设置失败时，收到此回调。
     * @param error 特效错误类型。参看 EffectErrorType{@link #EffectErrorType}。
     * @param msg 错误信息。
     */
    /**
     * @locale en
     * @hidden internal use only
     * @type callback
     * @brief Effect failed.
     * @param error The error type of effect. Refer to EffectErrorType{@link #EffectErrorType} for details.
     * @param msg Error message.
     */
    virtual void onEffectError(EffectErrorType error, const char* msg) {
        (void)error;
        (void)msg;
    }


    /**
     * @locale zh
     * @type callback
     * @region 视频渲染
     * @hidden for internal use only
     * @brief SDK 远端视频渲染发生错误时收到此回调
     * @param key 远端流信息。参看 RemoteStreamKey{@link #RemoteStreamKey}。
     * @param info 视频帧信息。参看 VideoFrameInfo{@link #VideoFrameInfo}。
     * @note 本回调暂时仅内部使用，开发者无需关注。
     */
    /**
     * @locale en
     * @type callback
     * @region Video Render
     * @hidden for internal use only
     * @brief Receive this callback when the render of remote video stream occurs error.
     * @param key Remote stream information. See RemoteStreamKey {@link #RemoteStreamKey}.
     * @param error Render error. See RenderError {@link #RenderError}.
     * @param message Error message
     * @note This callback is currently only used internally, which developers need not pay attention to.
     */
    virtual void onRemoteRenderError(const RemoteStreamKey key, RenderError error, const char* message) {
        (void)key;
        (void)error;
        (void)message;
    }

};

} // namespace bytertc
