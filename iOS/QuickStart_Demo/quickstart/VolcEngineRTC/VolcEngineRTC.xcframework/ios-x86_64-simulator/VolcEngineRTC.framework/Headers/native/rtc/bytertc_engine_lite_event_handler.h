/*
 * Copyright (c) 2020 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC Event Handler Lite
*/

#pragma once

#ifndef BYTE_RTC_LITE_EVENT_HANDLER_H__
#define BYTE_RTC_LITE_EVENT_HANDLER_H__

#include "bytertc_defines.h"

namespace bytertc {
/** 
 * @type callback
 * @brief 音视频引擎事件回调接口
 */
class IRtcEngineLiteEventHandler {
public:
    /** 
     * @type callback
     * @region 警告码
     * @brief 当内部发生警告事件时触发该回调
     * @param [in] warn
     *        警告标识码，详见:WarningCode{@link #WarningCode}
     */
    virtual void OnWarning(int warn) {
        (void)warn;
    }

    /** 
     * @type callback
     * @region 错误码
     * @brief 当 SDK 内部发生不可逆转错误时触发该回调。
     * @param [in] err 错误标识码，参看 ErrorCode{@link #ErrorCode}
     */
    virtual void OnError(int err) {
        (void)err;
    }

    /** 
     * @hidden
     * @deprecated since 325.1, use IAudioMixingManager instead
     * @type callback
     * @region 混音
     * @brief 本地音乐文件播放已结束回调。
     *        当调用 StartAudioMixing{@link #IAudioMixingManager#StartAudioMixing} 启动的混音文件播放结束后，会触发该回调。
     */
    virtual void OnAudioMixingFinished() {
    }

    /** 
     * @type callback
     * @region 混音
     * @brief  音频混音文件播放状态改变时回调
     * @param [in] mix_id  <br>
     *        混音 ID  <br>
     *        使用 IAudioMixingManager{@link #IAudioMixingManager} 相关接口时传入的唯一 ID。
     * @param [in] state  <br>
     *        混音状态  <br>
     *        其混音状态可参考： AudioMixingState{@link #AudioMixingState}。
     * @param [in] error
     *        错误码  <br>
     *        详见 AudioMixingError{@link #AudioMixingError}
     * @notes  <br>
     *       + 此回调会被触发的时机汇总如下：  <br>
     *       + 1. 音乐文件类型： <br>
     *       + 当调用 StartAudioMixing{@link #IAudioMixingManager#StartAudioMixing} 方法成功后，会触发 state 值为 kAudioMixingStatePlaying 回调；否则触发 state 值为 kAudioMixingStateFailed 的回调。  <br>
     *       + 当使用相同的 ID 重复调用 StartAudioMixing{@link #IAudioMixingManager#StartAudioMixing} 后，后一次会覆盖前一次，且本回调会以 kAudioMixingStateStopped 通知前一次混音已停止。  <br>
     *       + 当调用 PauseAudioMixing{@link #IAudioMixingManager#PauseAudioMixing} 方法暂停播放成功后，会触发 state 值为 kAudioMixingStatePaused 回调；否则触发 state 值为 kAudioMixingStateFailed 的回调。  <br>
     *       + 当调用 ResumeAudioMixing{@link #IAudioMixingManager#ResumeAudioMixing} 方法恢复播放成功后，会触发 state 值为 kAudioMixingStatePlaying 回调；否则触发 state 值为 kAudioMixingStateFailed 的回调。  <br>
     *       + 当调用 StopAudioMixing{@link #IAudioMixingManager#StopAudioMixing} 方法暂停止播放成功后，会触发 state 值为 kAudioMixingStateStopped 回调；否则触发 state 值为 kAudioMixingStateFailed 的回调。  <br>
     *       + 播放结束会触发 state 值为 kAudioMixingStateFinished 回调。 <br>
     *       + 2. PCM 流类型： <br>
     *       + 当调用 EnableAudioMixingFrame{@link #IAudioMixingManager#EnableAudioMixingFrame} 方法成功后，会触发 state 值为 kAudioMixingStatePCMEnabled 回调；否则触发 state 值为 kAudioMixingStateFailed 的回调。  <br>
     *       + 当调用 DisableAudioMixingFrame{@link #IAudioMixingManager#DisableAudioMixingFrame} 方法成功后，会触发 state 值为 kAudioMixingStatePCMDisabled 回调；否则触发 state 值为 kAudioMixingStateFailed 的回调。
     */
    virtual void OnAudioMixingStateChanged(int mix_id, bytertc::AudioMixingState state, bytertc::AudioMixingError error) {
    }

    /** 
     * @type callback
     * @region 混音
     * @brief 混音音频文件播放进度回调
     * @param [in] mix_id 混音 ID  <br>
     * @param [in] progress 当前混音音频文件播放进度，单位毫秒
     * @notes 调用 SetAudioMixingProgressInterval{@link #IAudioMixingManager#SetAudioMixingProgressInterval} 将时间间隔设为大于 0 的值后，或调用 StartAudioMixing{@link #IAudioMixingManager#StartAudioMixing} 将 AudioMixingConfig{@link #AudioMixingConfig} 中的时间间隔设为大于 0 的值后，SDK 会按照设置的时间间隔回调该事件。 <br>
     */
    virtual void OnAudioMixingPlayingProgress(int mix_id, int64_t progress){
    }

    /** 
     * @hidden
     * @deprecated since 325.1, use IAudioMixingManager instead
     * @type callback
     * @region 混音
     * @brief 本地音效文件播放已结束回调。
     *        当调用 StartAudioMixing{@link #IAudioMixingManager#StartAudioMixing}  方法开始播放指定音效文件， 音效文件播放结束后， 应用会收到该回调。
     * @param [in] sound_id
     *        音效ID，应用调用者维护，请保证唯一性。
     */
    virtual void OnAudioEffectFinished(int sound_id) {
    }

    /** 
     * @type callback
     * @region 引擎管理
     * @brief 端监控日志回调。当产生一个端监控事件时触发该回调。
     * @param [in] log_type  <br>
     *        事件类型。目前类型固定为 "live_webrtc_monitor_log"。
     * @param [in] log_content  <br>
     *        端监控日志内容。
     */
    virtual void OnLogReport(const char* log_type, const char* log_content) {
        (void)log_type;
        (void)log_content;
    }

    /** 
     * @hidden(macOS,Windows)
     * @type callback
     * @region 音频事件回调
     * @brief 音频播放设备变化时回调该事件。
     * @param [in] device 变化后的音频播放设备，参看 AudioPlaybackDevice{@link #AudioPlaybackDevice}。  <br>
     */
    virtual void OnAudioPlaybackDeviceChanged(AudioPlaybackDevice device) {
        (void)device;
    };

    /** 
     * @hidden(macOS,Windows)
     * @type callback
     * @region 音频事件回调
     * @brief 音频播放设备变化时回调该事件。
     * @param [in] device 变化后的音频播放设备，参看 AudioRoute{@link #AudioRoute}。  <br>
     */
    virtual void OnAudioRouteChanged(AudioRoute device) {
        (void)device;
    };

    /** 
     * @type callback
     * @region 引擎管理
     * @brief SDK 与信令服务器连接状态改变回调。连接状态改变时触发。
     * @param [in] state 当前 SDK 与信令服务器的连接状态，详见 ConnectionState{@link #ConnectionState}
     */
    virtual void OnConnectionStateChanged(bytertc::ConnectionState state) {
    }

    /** 
     * @type callback
     * @region 引擎管理
     * @brief SDK 当前网络连接类型改变回调。当 SDK 的当前网络连接类型发生改变时回调该事件。
     * @param [in] type  <br>
     *        SDK 当前的网络连接类型，详见：NetworkType{@link #NetworkType} 。
     */
    virtual void OnNetworkTypeChanged(bytertc::NetworkType type) {
    }

    /** 
     * @type callback
     * @region 音视频回退
     * @brief 本地未开启发布性能回退，检测到设备性能不足时，收到此回调。<br>
     *        本地开启发布性能回退，因设备性能/网络原因，造成发布性能回退/恢复时，收到此回调。
     * @param [in] mode 指示本地是否开启发布回退功能。参看 PerformanceAlarmMode{@link #PerformanceAlarmMode}  <br>
     *                  + 当发布端未开启发布性能回退时，mode 值为 kPerformanceAlarmModeNormal。  <br>
     *                  + 当发布端开启发布性能回退时，mode 值为 kPerformanceAlarmModeSimulcast。
     * @param [in] room_id  <br>
     *                      + 未开启发布性能回退时，room_id 为空 <br>
     *                      + 开启发布性能回退时，room_id 是告警影响的房间 ID。
     * @param [in] reason 告警原因，参看 PerformanceAlarmReason{@link #PerformanceAlarmReason}
     * @param [in] data 性能回退相关数据，详见 SourceWantedData{@link #SourceWantedData}。
     */
    virtual void OnPerformanceAlarms(bytertc::PerformanceAlarmMode mode, const char* room_id,
            bytertc::PerformanceAlarmReason reason, const bytertc::SourceWantedData& data) {
        (void)mode;
        (void)room_id;
        (void)reason;
        (void)data;
    }

    /** 
     * @hidden
     * @deprecated since 337, using OnAudioDeviceStateChanged and OnVideoDeviceStateChanged instead.
     * @type callback
     * @region 引擎管理
     * @brief 媒体设备状态回调。提示音频采集、音频播放、摄像头视频采集、屏幕视频采集四种媒体设备的状态。
     * @param [in] device_id 设备 ID   <br>
     *                       采集屏幕视频流时，设备 ID 为固定字符串 `screen_capture_video`
     * @param [in] device_type 设备类型，详见 MediaDeviceType{@link #MediaDeviceType}
     * @param [in] device_state 设备状态，详见 MediaDeviceState{@link #MediaDeviceState}
     * @param [in] device_error 设备错误类型，详见 MediaDeviceError{@link #MediaDeviceError}
     */
    virtual void OnMediaDeviceStateChanged(const char* device_id,
                                           bytertc::MediaDeviceType device_type,
                                           bytertc::MediaDeviceState device_state,
                                           bytertc::MediaDeviceError device_error) {
        (void)device_id;
        (void)device_type;
        (void)device_state;
        (void)device_error;
    }
    /** 
     * @type callback
     * @region 引擎管理
     * @brief 音频设备状态回调。提示音频采集、音频播放等设备设备的状态。
     * @param [in] device_id 设备 ID。
     * @param [in] device_type 设备类型，详见 RTCAudioDeviceType{@link #RTCAudioDeviceType}
     * @param [in] device_state 设备状态，详见 MediaDeviceState{@link #MediaDeviceState}
     * @param [in] device_error 设备错误类型，详见 MediaDeviceError{@link #MediaDeviceError}
     */
    virtual void OnAudioDeviceStateChanged(const char* device_id, bytertc::RTCAudioDeviceType device_type,
            bytertc::MediaDeviceState device_state, bytertc::MediaDeviceError device_error) {
        (void)device_id;
        (void)device_type;
        (void)device_state;
        (void)device_error;
    }
    /** 
     * @type callback
     * @region 引擎管理
     * @brief 视频频设备状态回调。提示摄像头视频采集、屏幕视频采集等设备的状态。
     * @param [in] device_id 设备 ID。采集屏幕共享流时，设备 ID 为固定字符串 `screen_capture_video`
     * @param [in] device_type 设备类型，详见 RTCVideoDeviceType{@link #RTCVideoDeviceType}
     * @param [in] device_state 设备状态，详见 MediaDeviceState{@link #MediaDeviceState}
     * @param [in] device_error 设备错误类型，详见 MediaDeviceError{@link #MediaDeviceError}
     */
    virtual void OnVideoDeviceStateChanged(const char* device_id, bytertc::RTCVideoDeviceType device_type,
            bytertc::MediaDeviceState device_state, bytertc::MediaDeviceError device_error) {
        (void)device_id;
        (void)device_type;
        (void)device_state;
        (void)device_error;
    }

    /** 
     * @hidden
     * @deprecated since 337, using OnAudioDeviceWarning and OnVideoDeviceWarning instead.
     * @type callback
     * @region 引擎管理
     * @brief 媒体设备警告回调。媒体设备包括：音频采集设备、音频渲染设备、和视频采集设备。
     * @param [in] device_id 设备 ID
     * @param [in] device_type 详见 MediaDeviceType{@link #MediaDeviceType}
     * @param [in] device_warning 详见 MediaDeviceWarning{@link #MediaDeviceWarning}
     */
     virtual void OnMediaDeviceWarning(const char* device_id, bytertc::MediaDeviceType device_type,
            bytertc::MediaDeviceWarning device_warning){
        (void)device_id;
        (void)device_type;
        (void)device_warning;
    }
    /** 
     * @type callback
     * @region 引擎管理
     * @brief 音频设备警告回调。音频设备包括音频采集设备和音频渲染设备。
     * @param [in] device_id 设备 ID
     * @param [in] device_type 详见 RTCAudioDeviceType{@link #RTCAudioDeviceType}
     * @param [in] device_warning 详见 MediaDeviceWarning{@link #MediaDeviceWarning}
     */
     virtual void OnAudioDeviceWarning(const char* device_id, bytertc::RTCAudioDeviceType device_type,
            bytertc::MediaDeviceWarning device_warning) {
        (void)device_id;
        (void)device_type;
        (void)device_warning;
    }
    /** 
     * @type callback
     * @region 引擎管理
     * @brief 视频设备警告回调，包括视频采集设备等。
     * @param [in] device_id 设备 ID
     * @param [in] device_type 详见 RTCVideoDeviceType{@link #RTCVideoDeviceType}
     * @param [in] device_warning 详见 MediaDeviceWarning{@link #MediaDeviceWarning}
     */
     virtual void OnVideoDeviceWarning(const char* device_id, bytertc::RTCVideoDeviceType device_type,
            bytertc::MediaDeviceWarning device_warning) {
        (void)device_id;
        (void)device_type;
        (void)device_warning;
    }

    /** 
     * @type callback
     * @region 引擎管理
     * @brief 周期性（2s）地发出回调，报告当前cpu与memory使用率
     * @param [in] stats 返回包含当前系统状态信息的结构体，详见 SysStats{@link #SysStats}
     */
    virtual void OnSysStats(const bytertc::SysStats& stats) {
    }

    /** 
     * @type callback
     * @region 代理回调
     * @brief HTTP 代理连接状态改变时，收到该回调。
     * @param [in] state 当前 HTTP 代理连接状态，详见 HttpProxyState{@link #HttpProxyState}
     */
    virtual void OnHttpProxyState(int state) {
    }

    /** 
     * @type callback
     * @region 代理回调
     * @brief HTTPS 代理连接状态改变时，收到该回调。
     * @param  [out] state 当前 HTTPS 代理连接状态，详见 HttpProxyState{@link #HttpProxyState}
     */
    virtual void OnHttpsProxyState(int state) {
    }

    /** 
     * @type callback
     * @region 代理回调
     * @brief Socks5 代理状态改变时，收到该回调。
     * @param [out] state SOCKS5 代理连接状态，详见 Socks5ProxyState{@link #Socks5ProxyState}
     * @param [out] cmd 代理连接的每一步操作命令
     * @param [out] proxy_address 代理地址信息
     * @param [out] local_address 当前连接使用的本地地址
     * @param [out] remote_address 远端的连接地址
     */
    virtual void OnSocks5ProxyState(int state,
        const char* cmd,
        const char* proxy_address,
        const char* local_address,
        const char* remote_address) {
    }

    /** 
     * @type callback
     * @region 本地录制
     * @brief 获取本地录制状态回调。  <br>
     *        该回调由 StartFileRecording{@link #IRtcEngineLite#StartFileRecording} 或 StopFileRecording{@link #IRtcEngineLite#StopFileRecording} 触发。
     * @param [out] type 录制流的流属性，参看 StreamIndex{@link #StreamIndex}
     * @param [out] state 录制状态，参看 RecordingState{@link #RecordingState}
     * @param [out] error_code 录制错误码，参看 RecordingErrorCode{@link #RecordingErrorCode}
     * @param [out] info 录制文件的详细信息，参看 RecordingInfo{@link #RecordingInfo}
     */
    virtual void OnRecordingStateUpdate(
            StreamIndex type, RecordingState state, RecordingErrorCode error_code, RecordingInfo info) {
    }

    /** 
     * @type callback
     * @region 本地录制
     * @brief 本地录制进度回调。  <br>
     *        该回调由 StartFileRecording{@link #IRtcEngineLite#StartFileRecording} 触发，录制状态正常时，系统每秒钟都会通过该回调提示录制进度。
     * @param [out] type 录制流的流属性，参看 StreamIndex{@link #StreamIndex}
     * @param [out] process 录制进度，参看 RecordingProgress{@link #RecordingProgress}
     * @param [out] info 录制文件的详细信息，参看 RecordingInfo{@link #RecordingInfo}
     */
    virtual void OnRecordingProgressUpdate(StreamIndex type, RecordingProgress process, RecordingInfo info) {
    }

    /** 
     * @type callback
     * @region 实时消息通信
     * @brief 登录结果回调
     * @param [in] uid  <br>
     *        登录用户 ID
     * @param [in] error_code  <br>
     *        登录结果  <br>
     *        详见 LoginErrorCode{@link #LoginErrorCode}。
     * @param [in] elapsed  <br>
     *        从调用 Login{@link #IRtcEngineLite#Login} 接口开始到返回结果所用时长  <br>
     *        单位为 ms。
     * @notes 调用 Login{@link #IRtcEngineLite#Login} 后，会收到此回调。
     */
    virtual void OnLoginResult(const char* uid, int error_code, int elapsed) {
        (void)uid;
        (void)error_code;
        (void)elapsed;
    }
    /** 
     * @type callback
     * @region 实时消息通信
     * @brief 登出结果回调
     * @notes 调用 Logout{@link #IRtcEngineLite#Logout} 后，会收到此回调。
     */
    virtual void OnLogout() {
    }
    /** 
     * @type callback
     * @region 实时消息通信
     * @brief 设置应用服务器参数的返回结果
     * @param [in] error <br>
     *        设置结果  <br>
     *        + 返回 200，设置成功  <br>
     *        + 返回其他，设置失败
     * @notes 调用 SetServerParams{@link #IRtcEngineLite#SetServerParams} 后，会收到此回调。
     */
    virtual void OnServerParamsSetResult(int error) {
        (void)error;
    }
    /** 
     * @type callback
     * @region 实时消息通信
     * @brief 查询对端或本端用户登录状态的返回结果
     * @param [in] peer_user_id  <br>
     *        需要查询的用户 ID
     * @param [in] status  <br>
     *        查询的用户登录状态  <br>
     *        详见 USER_ONLINE_STATUS{@link #USER_ONLINE_STATUS}.
     * @notes 必须先调用 GetPeerOnlineStatus{@link #IRtcEngineLite#GetPeerOnlineStatus}，才能收到此回调。
     */
    virtual void OnGetPeerOnlineStatus(const char* peer_user_id, int status) {
        (void)peer_user_id;
        (void)status;
    }
    /** 
     * @type callback
     * @region 实时消息通信
     * @brief 收到房间外用户调用 SendUserMessageOutsideRoom{@link #IRtcEngineLite#SendUserMessageOutsideRoom} 发来的文本消息时，会收到此回调
     * @param [in] uid  <br>
     *        消息发送者 ID
     * @param [in] message  <br>
     *        收到的文本消息内容
     */
    virtual void OnUserMessageReceivedOutsideRoom(const char* uid, const char* message) {
        (void)uid;
        (void)message;
    }
    /** 
     * @type callback
     * @region 实时消息通信
     * @brief 收到房间外用户调用 SendUserBinaryMessageOutsideRoom{@link #IRtcEngineLite#SendUserBinaryMessageOutsideRoom} 发来的二进制消息时，会收到此回调
     * @param [in] uid  <br>
     *        消息发送者 ID
     * @param [in] size  <br>
     *        二进制消息长度
     * @param [in] message  <br>
     *        收到的二进制消息内容
     */
    virtual void OnUserBinaryMessageReceivedOutsideRoom(const char* uid, int size, const uint8_t* message) {
        (void)uid;
        (void)size;
        (void)message;
    }
    /** 
     * @type callback
     * @region 实时消息通信
     * @brief 给房间外指定的用户发送消息的回调
     * @param [in] msgid  <br>
     *        本条消息的 ID  <br>
     *        所有的 P2P 和 P2Server 消息共用一个 ID 序列。
     * @param [in] error  <br>
     *        消息发送结果  <br>
     *        详见 UserMessageSendResult{@link #UserMessageSendResult}。
     * @notes 当调用 SendUserMessageOutsideRoom{@link #IRtcEngineLite#SendUserMessageOutsideRoom} 或 SendUserBinaryMessageOutsideRoom{@link #IRtcEngineLite#SendUserBinaryMessageOutsideRoom} 发送消息后，会收到此回调。
     */
    virtual void OnUserMessageSendResultOutsideRoom(int64_t msgid, int error) {
        (void)msgid;
        (void)error;
    }

    /** 
     * @type callback
     * @region 实时消息通信
     * @brief 给应用服务器发送消息的回调
     * @param [in] msgid 本条消息的 ID  <br>
     *        所有的 P2P 和 P2Server 消息共用一个 ID 序列。
     * @param [in] error 消息发送结果，详见 UserMessageSendResult{@link #UserMessageSendResult}。
     * @param [in] message 应用服务器收到 HTTP 请求后，在 ACK 中返回的信息。
     * @notes 当调用 SendServerMessage{@link #IRtcEngineLite#SendServerMessage} 或 SendServerBinaryMessage{@link #IRtcEngineLite#SendServerBinaryMessage} 发送消息后，会收到此回调。
     */
    virtual void OnServerMessageSendResult(int64_t msgid, int error, const bytertc::ServerACKMsg& msg) {
        (void)msgid;
        (void)error;
        (void)msg;
    }

    /** 
     * @type callback
     * @region 视频管理
     * @brief 收到通过 SendSEIMessage{@link #IRtcEngineLite#SendSEIMessage} 发送的带有 SEI 消息的视频帧时，收到此回调
     * @param [in] stream_key 包含 SEI 发送者的用户名，所在的房间名和媒体流，参看 RemoteStreamKey{@link #RemoteStreamKey}
     * @param [in] message 收到的 SEI 消息内容
     * @param [in] length 收到的 SEI 消息长度
    */
   virtual void OnSEIMessageReceived(RemoteStreamKey stream_key, const uint8_t* message, int length){
        (void)stream_key;
        (void)message;
        (void)length;
    }

     /** 
      * @type callback
      * @region 音频管理
      * @brief 远端用户进房后，本地调用 EnableAudioPropertiesReport{@link #IRtcEngineLite#EnableAudioPropertiesReport}，根据设置的 interval 值，本地会周期性地收到此回调，了解订阅的远端用户的音频信息。<br>
      *        远端用户的音频包括使用 RTC SDK 内部机制/自定义机制采集的麦克风音频和屏幕音频。
      * @param [in] audio_properties_infos 远端音频信息，其中包含音频流属性、房间 ID、用户 ID ，详见 RemoteAudioPropertiesInfo{@link #RemoteAudioPropertiesInfo}。
      * @param [in] audio_properties_info_number 数组长度
      * @param [in] total_remote_volume 所有订阅的远端流的总音量，范围是 [0,255]。  <br>
      *       + [0,25] 接近无声；  <br>
      *       + [25,75] 为低音量；  <br>
      *       + [76,204] 为中音量；  <br>
      *       + [205,255] 为高音量。  <br>
      */
     virtual void OnRemoteAudioPropertiesReport(const RemoteAudioPropertiesInfo* audio_properties_infos, int audio_properties_info_number, int total_remote_volume) {
        (void)audio_properties_infos;
        (void)audio_properties_info_number;
        (void)total_remote_volume;
    }

     /** 
      * @type callback
      * @region 音频管理
      * @brief 调用 EnableAudioPropertiesReport{@link #IRtcEngineLite#EnableAudioPropertiesReport} 后，根据设置的 interval 值，你会周期性地收到此回调，了解本地音频的相关信息。  <br>
      *        本地音频包括使用 RTC SDK 内部机制采集的麦克风音频和屏幕音频。
      * @param [in] audio_properties_infos 本地音频信息，详见 LocalAudioPropertiesInfo{@link #LocalAudioPropertiesInfo} 。
      * @param [in] audio_properties_info_number 数组长度
      */
     virtual void OnLocalAudioPropertiesReport(const LocalAudioPropertiesInfo * audio_properties_infos, int audio_properties_info_number) {
        (void)audio_properties_infos;
        (void)audio_properties_info_number;
    }
    /** 
     * @type callback
     * @region 音频管理
     * @brief 调用 EnableAudioPropertiesReport{@link #IRtcEngineLite#EnableAudioPropertiesReport} 后，根据设置的 `config.interval`，你会周期性地收到此回调，获取房间内的最活跃用户信息。
     * @param room_id 房间 ID
     * @param uid 最活跃用户（ActiveSpeaker）的用户 ID
     */
    virtual void OnActiveSpeaker(const char* room_id, const char* uid) {
        (void)room_id;
        (void)uid;
    }

    /** 
     * @type api
     * @region 音频管理
     * @brief 音频流同步信息回调。可以通过此回调，在远端用户调用 SendStreamSyncInfo{@link #IRtcEngineLite#SendStreamSyncInfo} 发送音频流同步消息后，收到远端发送的音频流同步信息。  <br>
     * @param [in] stream_key 远端流信息，详见 RemoteStreamKey{@link #RemoteStreamKey} 。
     * @param [in] stream_type 媒体流类型，详见 SyncInfoStreamType{@link #SyncInfoStreamType} 。
     * @param [in] data 消息内容。
     * @param [in] length 消息长度。
     */
    virtual void OnStreamSyncInfoReceived(RemoteStreamKey stream_key, SyncInfoStreamType stream_type,
                                         const uint8_t* data,
                                         int32_t length) {
        (void)stream_key;
        (void)stream_type;
        (void)data;
        (void)length;
    }

    /** 
     * @type callback
     * @region 通话前网络探测
     * @brief 通话前网络探测结果
     * @param type  <br>
     *        探测网络类型为上行/下行  <br>
     * @param quality  <br>
     *        探测网络的质量，值含义参考 NetworkQuality{@link #NetworkQuality} <br>
     * @param rtt  <br>
     *        探测网络的 RTT，单位：ms  <br>
     * @param lost_rate  <br>
     *        探测网络的丢包率  <br>
     * @param bitrate  <br>
     *        探测网络的带宽，单位：kbps  <br>
     * @param jitter  <br>
     *        探测网络的抖动,单位：ms  <br>
     * @notes 成功调用 StartNetworkDetection{@link #IRtcEngineLite#StartNetworkDetection} 接口开始探测后，会每 2s 收到一次此回调。
     */
    virtual void OnNetworkDetectionResult(NetworkDetectionLinkType type, NetworkQuality quality, int rtt, double lost_rate,
                                      int bitrate, int jitter){
        (void)type;
        (void)quality;
        (void)rtt;
        (void)lost_rate;
        (void)bitrate;
        (void)jitter;
    }

    /** 
     * @type callback
     * @region 通话前网络探测
     * @brief 通话前网络探测结束
     *        以下情况将停止探测并收到本一次本回调：<br>
     *        1. 当调用 StopNetworkDetection{@link #IRtcEngineLite#StopNetworkDetection} 接口停止探测后，会收到一次该回调；
     *        2. 当收到远端/本端音频首帧后，停止探测；
     *        3. 当探测超过3分钟后，停止探测；
     *        4. 当探测链路断开一定时间之后，停止探测。
     * @param [in] reason  <br>
     *        停止探测的原因类型,参考 NetworkDetectionStopReason{@link #NetworkDetectionStopReason}  <br>
     */
    virtual void OnNetworkDetectionStopped(NetworkDetectionStopReason reason){
        (void)reason;
    }
    /** 
     * @type callback
     * @brief 订阅公共流的结果回调<br>
     *        通过 StartPlayPublicStream{@link #IRtcEngineLite#StartPlayPublicStream} 订阅公共流后，可以通过本回调获取订阅结果。
     * @param [in] public_stream_id 公共流的 ID
     * @param [in] errorCode 公共流订阅结果状态码。<br>
     *             `200`: 订阅成功
     */
    virtual void OnPlayPublicStreamResult(const char* public_stream_id, int errorCode) {
        (void)public_stream_id;
        (void)errorCode;
    }
    /** 
     * @type callback
     * @brief 回调公共流中包含的 SEI 信息<br>
     *        通过 StartPlayPublicStream{@link #IRtcEngineLite#StartPlayPublicStream} 开始播放公共流后，可以通过本回调获取公共流中包含的 SEI 信息。
     * @param [in] public_stream_id 公共流 ID
     * @param [in] message SEI 信息
     * @param [in] message_length SEI 信息的长度
     * @notes 当公共流中的多路视频流均包含有 SEI 信息时：<br>
     *       SEI 不互相冲突时，将通过多次回调分别发送；<br>
     *       SEI 在同一帧有冲突时，则只有一条流中的 SEI 信息被透传并融合到公共流中。
     */
    virtual void OnPublicStreamSEIMessageReceived(const char* public_stream_id, const uint8_t* message, int message_length) {
        (void)public_stream_id;
        (void)message;
        (void)message_length;
    }
    /** 
     * @type callback
     * @brief 公共流的首帧视频解码成功<br>
     *        关于订阅公共流，详见 StartPlayPublicStream{@link #IRtcEngineLite#StartPlayPublicStream}。
     * @param [in] public_stream_id 公共流 ID
     * @param [in] info 视频帧信息。详见 VideoFrameInfo{@link #VideoFrameInfo}。
     */
    virtual void OnFirstPublicStreamVideoFrameDecoded(const char* public_stream_id, const VideoFrameInfo& info) {
        (void)public_stream_id;
    }
    /** 
     * @type callback
     * @brief 公共流的音频首帧解码成功<br>
     *        关于订阅公共流，详见 StartPlayPublicStream{@link #IRtcEngineLite#StartPlayPublicStream}。
     * @param [in] public_stream_id 公共流 ID
     */
    virtual void OnFirstPublicStreamAudioFrame(const char* public_stream_id) {
        (void)public_stream_id;
    }
    /** 
     * @type callback
     * @brief 调用 StartCloudProxy{@link #IRtcEngineLite#StartCloudProxy} 开启云代理，SDK 首次成功连接云代理服务器时，回调此事件。
     * @param [in] interval 从开启云代理到连接成功经过的时间，单位为 ms
     */
    virtual void OnCloudProxyConnected(int interval) {
        (void)interval;
    }
};

} // namespace bytertc

#endif // BYTE_RTC_LITE_EVENT_HANDLER_H__
