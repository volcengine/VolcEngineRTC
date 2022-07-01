/*
 * Copyright (c) 2022 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC Event Handler Lite
*/

#pragma once

#include "bytertc_audio_defines.h"

namespace bytertc {
/** 
 * @type callback
 * @brief 音频引擎事件回调接口
 */
class IRTCAudioEngineEventHandler {
public:
    /** 
     * @hidden
     * @brief 析构函数
     */
    virtual ~IRTCAudioEngineEventHandler() {}
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
    virtual void OnAudioMixingStateChanged(int mix_id, bytertc::AudioMixingState state,
            bytertc::AudioMixingError error) {
        (void)mix_id;
        (void)state;
        (void)error;
    }

    /** 
     * @type callback
     * @region 混音
     * @brief 混音音频文件播放进度回调
     * @param [in] mix_id 混音 ID  <br>
     * @param [in] progress 当前混音音频文件播放进度，单位毫秒
     * @notes 调用 SetAudioMixingProgressInterval{@link #IAudioMixingManager#SetAudioMixingProgressInterval} 将时间间隔设为大于 0 的值后，或调用 StartAudioMixing{@link #IAudioMixingManager#StartAudioMixing} 将 AudioMixingConfig{@link #AudioMixingConfig} 中的时间间隔设为大于 0 的值后，SDK 会按照设置的时间间隔回调该事件。 <br>
     */
    virtual void OnAudioMixingPlayingProgress(int mix_id, int64_t progress) {
        (void)mix_id;
        (void)progress;
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
     * @param [in] device 变化后的音频播放设备，参看 AudioRoute{@link #AudioRoute}。  <br>
     */
    virtual void OnAudioRouteChanged(AudioRoute device) {
        (void)device;
    }

    /** 
     * @type callback
     * @region 引擎管理
     * @brief SDK 与信令服务器连接状态改变回调。连接状态改变时触发。
     * @param [in] state 当前 SDK 与信令服务器的连接状态，详见 ConnectionState{@link #ConnectionState}
     */
    virtual void OnConnectionStateChanged(bytertc::ConnectionState state) {
        (void)state;
    }

    /** 
     * @type callback
     * @region 引擎管理
     * @brief SDK 当前网络连接类型改变回调。当 SDK 的当前网络连接类型发生改变时回调该事件。
     * @param [in] type  <br>
     *        SDK 当前的网络连接类型，详见：NetworkType{@link #NetworkType} 。
     */
    virtual void OnNetworkTypeChanged(bytertc::NetworkType type) {
        (void)type;
    }

    /** 
     * @type callback
     * @region 引擎管理
     * @brief 音频设备状态回调。提示音频采集、音频播放等设备的状态。
     * @param [in] device_id 设备 ID
     * @param [in] device_type 设备类型，参看 RTCAudioDeviceType{@link #RTCAudioDeviceType}。
     * @param [in] device_state 设备状态，参看 MediaDeviceState{@link #MediaDeviceState}。
     * @param [in] device_error 设备错误类型，参看 MediaDeviceError{@link #MediaDeviceError}。
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
     * @brief 音频设备警告回调。音频设备包括音频采集设备和音频渲染设备。
     * @param [in] device_id 设备 ID
     * @param [in] device_type 参看 RTCAudioDeviceType{@link #RTCAudioDeviceType}
     * @param [in] device_warning 参看 MediaDeviceWarning{@link #MediaDeviceWarning}
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
     * @brief 周期性（2s）地发出回调，报告当前cpu与memory使用率
     * @param [in] stats 返回包含当前系统状态信息的结构体，详见 SysStats{@link #SysStats}
     */
    virtual void OnSysStats(const bytertc::SysStats& stats) {
        (void)stats;
    }

    /** 
     * @type callback
     * @region 代理回调
     * @brief HTTP 代理连接状态改变时，收到该回调。
     * @param [in] state 当前 HTTP 代理连接状态，详见 HttpProxyState{@link #HttpProxyState}
     */
    virtual void OnHttpProxyState(int state) {
        (void)state;
    }

    /** 
     * @type callback
     * @region 代理回调
     * @brief HTTPS 代理连接状态改变时，收到该回调。
     * @param  [out] state 当前 HTTPS 代理连接状态，详见 HttpProxyState{@link #HttpProxyState}
     */
    virtual void OnHttpsProxyState(int state) {
        (void)state;
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
    virtual void OnSocks5ProxyState(int state, const char* cmd, const char* proxy_address,
            const char* local_address, const char* remote_address) {
        (void)state;
        (void)cmd;
        (void)proxy_address;
        (void)local_address;
        (void)remote_address;
    }

    /** 
     * @type callback
     * @region 本地录制
     * @brief 获取本地录制状态回调。  <br>
     *        该回调由 StartFileRecording{@link #IRTCAudioEngine#StartFileRecording} 或 StopFileRecording{@link #IRTCAudioEngine#StopFileRecording} 触发。
     * @param [out] state 录制状态，参看 RecordingState{@link #RecordingState}
     * @param [out] error_code 录制错误码，参看 RecordingErrorCode{@link #RecordingErrorCode}
     * @param [out] info 录制文件的详细信息，参看 RecordingInfo{@link #RecordingInfo}
     */
    virtual void OnRecordingStateUpdate(RecordingState state, RecordingErrorCode error_code, RecordingInfo info) {
        (void)state;
        (void)error_code;
        (void)info;
    }

    /** 
     * @type callback
     * @region 本地录制
     * @brief 本地录制进度回调。  <br>
     *        该回调由 StartFileRecording{@link #IRTCAudioEngine#StartFileRecording} 触发，录制状态正常时，系统每秒钟都会通过该回调提示录制进度。
     * @param [out] process 录制进度，参看 RecordingProgress{@link #RecordingProgress}
     * @param [out] info 录制文件的详细信息，参看 RecordingInfo{@link #RecordingInfo}
     */
    virtual void OnRecordingProgressUpdate(RecordingProgress process, RecordingInfo info) {
        (void)process;
        (void)info;
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
     *        从调用 Login{@link #IRTCAudioEngine#Login} 接口开始到返回结果所用时长  <br>
     *        单位为 ms。
     * @notes 调用 Login{@link #IRTCAudioEngine#Login} 后，会收到此回调。
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
     * @notes 调用 Logout{@link #IRTCAudioEngine#Logout} 后，会收到此回调。
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
     * @notes 调用 SetServerParams{@link #IRTCAudioEngine#SetServerParams} 后，会收到此回调。
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
     * @notes 必须先调用 GetPeerOnlineStatus{@link #IRTCAudioEngine#GetPeerOnlineStatus}，才能收到此回调。
     */
    virtual void OnGetPeerOnlineStatus(const char* peer_user_id, int status) {
        (void)peer_user_id;
        (void)status;
    }

    /** 
     * @type callback
     * @region 实时消息通信
     * @brief 收到房间外用户调用 SendUserMessageOutsideRoom{@link #IRTCAudioEngine#SendUserMessageOutsideRoom} 发来的文本消息时，会收到此回调
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
     * @brief 收到房间外用户调用 SendUserBinaryMessageOutsideRoom{@link #IRTCAudioEngine#SendUserBinaryMessageOutsideRoom} 发来的二进制消息时，会收到此回调
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
     * @notes 当调用 SendUserMessageOutsideRoom{@link #IRTCAudioEngine#SendUserMessageOutsideRoom} 或 SendUserBinaryMessageOutsideRoom{@link #IRTCAudioEngine#SendUserBinaryMessageOutsideRoom} 发送消息后，会收到此回调。
     */
    virtual void OnUserMessageSendResultOutsideRoom(int64_t msgid, int error) {
        (void)msgid;
        (void)error;
    }

    /** 
     * @type callback
     * @region 实时消息通信
     * @brief 给应用服务器发送消息的回调
     * @param [in] msgid  <br>
     *        本条消息的 ID  <br>
     *        所有的 P2P 和 P2Server 消息共用一个 ID 序列。
     * @param [in] error  <br>
     *        消息发送结果  <br>
     *        详见 UserMessageSendResult{@link #UserMessageSendResult}。
     * @param [in] msg  <br>
     *        业务服务器返回的消息。
     * @notes 当调用 SendServerMessage{@link #IRTCAudioEngine#SendServerMessage} 或 SendServerBinaryMessage{@link #IRTCAudioEngine#SendServerBinaryMessage} 接口发送消息后，会收到此回调。
     */
    virtual void OnServerMessageSendResult(int64_t msgid, int error, const bytertc::ServerACKMsg& msg) {
        (void)msgid;
        (void)error;
        (void)msg;
    }

     /** 
      * @type callback
      * @region 音频管理
      * @brief 远端用户进房后，本地调用 EnableAudioPropertiesReport{@link #IRTCAudioEngine#EnableAudioPropertiesReport}，根据设置的 interval 值，本地会周期性地收到此回调，了解订阅的远端用户的音频信息。<br>
      *        远端用户的音频包括使用 RTC SDK 内部机制/自定义机制采集的麦克风音频和屏幕音频。
      * @param [in] audio_properties_infos 远端音频信息，其中包含音频流属性、房间 ID、用户 ID ，详见 RemoteAudioPropertiesInfo{@link #RemoteAudioPropertiesInfo}。
      * @param [in] audio_properties_info_number 数组长度
      * @param [in] total_remote_volume 所有订阅的远端流的总音量，范围是 [0,255]。  <br>
      *       + [0,25] 接近无声；  <br>
      *       + [25,75] 为低音量；  <br>
      *       + [76,204] 为中音量；  <br>
      *       + [205,255] 为高音量。  <br>
      */
     virtual void OnRemoteAudioPropertiesReport(const RemoteAudioPropertiesInfo* audio_properties_infos,
            int audio_properties_info_number, int total_remote_volume) {
        (void)audio_properties_infos;
        (void)audio_properties_info_number;
        (void)total_remote_volume;
    }

     /** 
      * @type callback
      * @region 音频管理
      * @brief 调用 EnableAudioPropertiesReport{@link #IRTCAudioEngine#EnableAudioPropertiesReport} 后，根据设置的 interval 值，你会周期性地收到此回调，了解本地音频的相关信息。  <br>
      *        本地音频包括使用 RTC SDK 内部机制采集的麦克风音频和屏幕音频。
      * @param [in] audio_properties_infos 本地音频信息，详见 LocalAudioPropertiesInfo{@link #LocalAudioPropertiesInfo} 。
      * @param [in] audio_properties_info_number 数组长度
      */
     virtual void OnLocalAudioPropertiesReport(const LocalAudioPropertiesInfo * audio_properties_infos,
            int audio_properties_info_number) {
        (void)audio_properties_infos;
        (void)audio_properties_info_number;
    }

    /** 
     * @type api
     * @region 音频管理
     * @brief 音频流同步信息回调。可以通过此回调，在远端用户调用 SendStreamSyncInfo{@link #IRTCAudioEngine#SendStreamSyncInfo} 发送音频流同步消息后，收到远端发送的音频流同步信息。  <br>
     * @param [in] stream_key 远端流信息，详见 RemoteStreamKey{@link #RemoteStreamKey} 。
     * @param [in] stream_type 媒体流类型，详见 SyncInfoStreamType{@link #SyncInfoStreamType} 。
     * @param [in] data 消息内容。
     * @param [in] length 消息长度。
     */
    virtual void OnStreamSyncInfoReceived(RemoteStreamKey stream_key, SyncInfoStreamType stream_type,
                                         const uint8_t* data, int32_t length) {
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
     * @notes 成功调用 StartNetworkDetection{@link #IRTCAudioEngine#StartNetworkDetection} 接口开始探测后，会每 2s 收到一次此回调。
     */
    virtual void OnNetworkDetectionResult(NetworkDetectionLinkType type, NetworkQuality quality, int rtt,
            double lost_rate, int bitrate, int jitter) {
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
     *        1. 当调用 StopNetworkDetection{@link #IRTCAudioEngine#StopNetworkDetection} 接口停止探测后，会收到一次该回调；
     *        2. 当收到远端/本端音频首帧后，停止探测；
     *        3. 当探测超过3分钟后，停止探测；
     *        4. 当探测链路断开一定时间之后，停止探测。
     * @param [in] reason  <br>
     *        停止探测的原因类型,参考 NetworkDetectionStopReason{@link #NetworkDetectionStopReason}  <br>
     */
    virtual void OnNetworkDetectionStopped(NetworkDetectionStopReason reason) {
        (void)reason;
    }

   /** 
    * @type callback
    * @brief 调用 startCloudProxy{@link #IRtcEngineLite#startCloudProxy} 开启云代理，SDK 首次成功连接云代理服务器时，回调此事件。
    * @param [in] interval 从开启云代理到连接成功经过的时间，单位为 ms
    */
   virtual void OnCloudProxyConnected(int interval) {
        (void)interval;
    }
};

}  // namespace bytertc
