/*
 * Copyright (c) 2020 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngine Event Handler Lite
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
     * @deprecated from 325.1, use IAudioMixingManager instead
     * @type callback
     * @region 混音
     * @brief 本地音乐文件播放已结束回调。
     *        当调用 StartAudioMixing{@link #StartAudioMixing} 启动的混音文件播放结束后，会触发该回调。
     */
    virtual void OnAudioMixingFinished() {
    }

    /**
     * @type callback
     * @region 混音
     * @brief  音频混音文件播放状态改变时回调
     * @param [in] id  <br>
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
     *       + 当调用 StartAudioMixing{@link #StartAudioMixing} 方法成功后，会触发 state 值为 kAudioMixingStatePlaying 回调；否则触发 state 值为 kAudioMixingStateFailed 的回调。  <br>
     *       + 当使用相同的 ID 重复调用 StartAudioMixing{@link #StartAudioMixing} 后，后一次会覆盖前一次，且本回调会以 kAudioMixingStateStopped 通知前一次混音已停止。  <br>
     *       + 当调用 PauseAudioMixing{@link #PauseAudioMixing} 方法暂停播放成功后，会触发 state 值为 kAudioMixingStatePaused 回调；否则触发 state 值为 kAudioMixingStateFailed 的回调。  <br>
     *       + 当调用 ResumeAudioMixing{@link #ResumeAudioMixing} 方法恢复播放成功后，会触发 state 值为 kAudioMixingStatePlaying 回调；否则触发 state 值为 kAudioMixingStateFailed 的回调。  <br>
     *       + 当调用 StopAudioMixing{@link #StopAudioMixing} 方法暂停止播放成功后，会触发 state 值为 kAudioMixingStateStopped 回调；否则触发 state 值为 kAudioMixingStateFailed 的回调。  <br>
     *       + 播放结束会触发 state 值为 kAudioMixingStateFinished 回调。
     */
    virtual void OnAudioMixingStateChanged(int id, bytertc::AudioMixingState state, bytertc::AudioMixingError error) {
    }

    /**
     * @hidden
     * @deprecated
     * @type callback
     * @region 混音
     * @deprecated from 325.1, use IAudioMixingManager instead
     * @brief 本地音效文件播放已结束回调。
     *        当调用 StartAudioMixing{@link #StartAudioMixing}  方法开始播放指定音效文件， 音效文件播放结束后， 应用会收到该回调。
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
     * @type callback
     * @region 引擎管理
     * @brief 媒体设备状态回调。提示音频采集、音频渲染、视频采集三种媒体设备的状态。
     * @param [in] device_id 设备 ID
     * @param [in] device_type 设备类型，详见 MediaDeviceType{@link #MediaDeviceType}
     * @param [in] device_state 设备状态，详见 MediaDeviceState{@link #MediaDeviceState}
     * @param [in] device_error 设备错误类型，详见 MediaDeviceError{@link #MediaDeviceError}
     * @notes   <br>
     *        + 媒体设备包括音频采集、音频渲染、视频采集三种设备类型。
     *        + 此回调返回媒体设备的状态，包括：设备的插入、移除，以及使用中的设备开启、停止、运行时错误等状态。  <br>
     */
    virtual void OnMediaDeviceStateChanged(const char* device_id,
                                           bytertc::MediaDeviceType device_type,
                                           bytertc::MediaDeviceState device_state,
                                           bytertc::MediaDeviceError device_error) {
        (void)device_id;
        (void)device_type;
        (void)device_state;
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
     *        该回调由 StartFileRecording{@link #StartFileRecording} 或 StopFileRecording{@link #StopFileRecording} 触发。
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
     *        该回调由 StartFileRecording{@link #StartFileRecording} 触发，录制状态正常时，系统每秒钟都会通过该回调提示录制进度。
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
     * @brief 设置业务服务器参数的返回结果
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
     * @brief 给业务服务器发送消息的回调
     * @param [in] msgid  <br>
     *        本条消息的 ID  <br>
     *        所有的 P2P 和 P2Server 消息共用一个 ID 序列。
     * @param [in] error  <br>
     *        消息发送结果  <br>
     *        详见 UserMessageSendResult{@link #UserMessageSendResult}。
     * @notes 当调用 SendServerMessage{@link #IRtcEngineLite#SendServerMessage} 或 SendServerBinaryMessage{@link #IRtcEngineLite#SendServerBinaryMessage} 接口发送消息后，会收到此回调。
     */
    virtual void OnServerMessageSendResult(int64_t msgid, int error) {
        (void)msgid;
        (void)error;
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
     * @brief 调用 EnableAudioPropertiesReport{@link #IRtcEngineLite#EnableAudioPropertiesReport} 后，可能会周期性收到此回调，获取订阅的远端用户的音量信息。  <br>
     * @param audio_properties_infos 远端音频信息，其中包含音频流属性、房间 ID、用户 ID ，详见 RemoteAudioPropertiesInfo{@link #RemoteAudioPropertiesInfo}。  <br>
     * @param audio_properties_info_number
     * @param total_remote_volume 所有订阅的远端流的总音量，范围是 [0,255]。  <br>
     *       + [0,25] 接近无声；  <br>
     *       + [25,75] 为低音量；  <br>
     *       + [76,204] 为中音量；  <br>
     *       + [205,255] 为高音量。  <br>
     * @notes 要获取接收的来自远端的音频音量信息时，不限定音频采集方式，RTC SDK 内部采集机制和自定义采集都可以。
     */
    virtual void OnRemoteAudioPropertiesReport(const RemoteAudioPropertiesInfo* audio_properties_infos, int audio_properties_info_number, int total_remote_volume) {
        (void)audio_properties_infos;
        (void)audio_properties_info_number;
        (void)total_remote_volume;
    }
    
    /**
     * @type callback
     * @region 视频管理
     * @brief 调用 EnableAudioPropertiesReport{@link #IRtcEngineLite#EnableAudioPropertiesReport} 后，可能会周期性收到此回调，获取本地音量信息。  <br>
     * @param audio_properties_infos 本地音频信息，详见 LocalAudioPropertiesInfo{@link #localAudioPropertiesInfo} 。
     * @param audio_properties_info_number
     * @notes <br>
     *       + 使用 RTC SDK 内部机制采集麦克风音频时，回调麦克风的音量；  <br>
     *       + 使用 RTC SDK 内部机制采集屏幕音频时，回调屏幕音频的音量。  <br>
     */
    virtual void OnLocalAudioPropertiesReport(const LocalAudioPropertiesInfo * audio_properties_infos, int audio_properties_info_number) {
        (void)audio_properties_infos;
        (void)audio_properties_info_number;
    }

    /**
     * @type api
     * @region 音频管理
     * @brief 音频流同步信息回调。可以通过此回调，在远端用户调用 SendStreamSyncInfo{@link #IRtcEngineLite#SendStreamSyncInfo} 发送音频流同步消息后，收到远端发送的音频流同步信息。  <br>
     * @param [in] stream_key 远端流信息，详见 RemoteStreamKey{@link #RemoteStreamKey} 。
     * @param [in] stream_type 媒体流类型，目前仅支持用麦克风采集到的音频流，详见 SyncInfoStreamType{@link #SyncInfoStreamType} 。
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
};

} // namespace bytertc

#endif // BYTE_RTC_LITE_EVENT_HANDLER_H__
