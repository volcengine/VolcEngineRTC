/*
 * Copyright (c) 2020 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC Event Handler
*/

#pragma once

#ifndef BYTE_RTC_EVENT_HANDLER_H__
#define BYTE_RTC_EVENT_HANDLER_H__

#include "bytertc_defines.h"

namespace bytertc {

/**  
 * @type callback
 * @brief 音视频引擎事件回调接口。  <br>
 *        创建 RTCEngine 实例 createRtcEngine{@link #createRtcEngine} 时，传入该回调实例。  <br>
 *        详见 IRtcEngineEventHandler{@link #IRtcEngineEventHandler} 、IRTCRoomEventHandler{@link #IRTCRoomEventHandler}
 */
class IRtcEngineEventHandler {
public:
    /**
     * @hidden
     */
    virtual ~IRtcEngineEventHandler() {
    }
	
	/**  
    * @hidden
    * @type callback
    * @region 游戏接口
    * @brief 游戏场景中，当房间用户的的 sendmode 被修改的时候回调该事件，发送模式只有三种，分别是：静音、向小队发送、向世界发送。
    * @param [in] uid  <br>
    *        远端用户 id 。
    * @param [in] range_audio_mode  <br>
    *        远端用户的发送模式，详见: RangeAudioMode{@link #RangeAudioMode} 。
    */
   virtual void onUserAudioSendModeChange(const char* uid, int range_audio_mode) {
        (void)uid;
        (void)range_audio_mode;
    }

    /**  
     * @hidden
     * @type callback
     * @region 游戏接口
     *@brief 游戏场景中，当房间用户的的 recvmode 被修改的时候回调该事件，收听模式只有三种，分别是：静音、收听小队、收听世界。
     *@param [in] uid  <br>
     *       远端用户 id 。
     *@param [in] range_audio_mode  <br>
     *       远端用户的接收模式，详见: RangeAudioMode{@link #RangeAudioMode} 。
     */
    virtual void onUserAudioRecvModeChange(const char* uid, int range_audio_mode) {
        (void)uid;
        (void)range_audio_mode;
    }

        /** 
     * @type callback
     * @region 警告码
     * @brief 当内部发生警告事件时触发该回调
     * @param [in] warn
     *        警告标识码，详见:WarningCode{@link #WarningCode}
     */
    virtual void onWarning(int warn) {
        (void)warn;
    }

    /** 
     * @type callback
     * @region 错误码
     * @brief 当 SDK 内部发生不可逆转错误时触发该回调。
     * @param [in] err 错误标识码，参看 ErrorCode{@link #ErrorCode}
     */
    virtual void onError(int err) {
        (void)err;
    }

    /** 
     * @hidden
     * @deprecated since 325.1, use IAudioMixingManager instead
     * @type callback
     * @region 混音
     * @brief 本地音乐文件播放已结束回调。
     *        当调用 startAudioMixing{@link #IAudioMixingManager#startAudioMixing} 启动的混音文件播放结束后，会触发该回调。
     */
    virtual void onAudioMixingFinished() {
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
     *       + 当调用 startAudioMixing{@link #IAudioMixingManager#startAudioMixing} 方法成功后，会触发 state 值为 kAudioMixingStatePlaying 回调；否则触发 state 值为 kAudioMixingStateFailed 的回调。  <br>
     *       + 当使用相同的 ID 重复调用 startAudioMixing{@link #IAudioMixingManager#startAudioMixing} 后，后一次会覆盖前一次，且本回调会以 kAudioMixingStateStopped 通知前一次混音已停止。  <br>
     *       + 当调用 pauseAudioMixing{@link #IAudioMixingManager#pauseAudioMixing} 方法暂停播放成功后，会触发 state 值为 kAudioMixingStatePaused 回调；否则触发 state 值为 kAudioMixingStateFailed 的回调。  <br>
     *       + 当调用 resumeAudioMixing{@link #IAudioMixingManager#resumeAudioMixing} 方法恢复播放成功后，会触发 state 值为 kAudioMixingStatePlaying 回调；否则触发 state 值为 kAudioMixingStateFailed 的回调。  <br>
     *       + 当调用 stopAudioMixing{@link #IAudioMixingManager#stopAudioMixing} 方法暂停止播放成功后，会触发 state 值为 kAudioMixingStateStopped 回调；否则触发 state 值为 kAudioMixingStateFailed 的回调。  <br>
     *       + 播放结束会触发 state 值为 kAudioMixingStateFinished 回调。 <br>
     *       + 2. PCM 流类型： <br>
     *       + 当调用 enableAudioMixingFrame{@link #IAudioMixingManager#enableAudioMixingFrame} 方法成功后，会触发 state 值为 kAudioMixingStatePCMEnabled 回调；否则触发 state 值为 kAudioMixingStateFailed 的回调。  <br>
     *       + 当调用 disableAudioMixingFrame{@link #IAudioMixingManager#disableAudioMixingFrame} 方法成功后，会触发 state 值为 kAudioMixingStatePCMDisabled 回调；否则触发 state 值为 kAudioMixingStateFailed 的回调。
     */
    virtual void onAudioMixingStateChanged(int mix_id, bytertc::AudioMixingState state, bytertc::AudioMixingError error) {
    }

    /** 
     * @type callback
     * @region 混音
     * @brief 混音音频文件播放进度回调
     * @param [in] mix_id 混音 ID  <br>
     * @param [in] progress 当前混音音频文件播放进度，单位毫秒
     * @notes 调用 setAudioMixingProgressInterval{@link #IAudioMixingManager#setAudioMixingProgressInterval} 将时间间隔设为大于 0 的值后，或调用 startAudioMixing{@link #IAudioMixingManager#startAudioMixing} 将 AudioMixingConfig{@link #AudioMixingConfig} 中的时间间隔设为大于 0 的值后，SDK 会按照设置的时间间隔回调该事件。 <br>
     */
    virtual void onAudioMixingPlayingProgress(int mix_id, int64_t progress){
    }

    /** 
     * @hidden
     * @deprecated since 325.1, use IAudioMixingManager instead
     * @type callback
     * @region 混音
     * @brief 本地音效文件播放已结束回调。
     *        当调用 startAudioMixing{@link #IAudioMixingManager#startAudioMixing}  方法开始播放指定音效文件， 音效文件播放结束后， 应用会收到该回调。
     * @param [in] sound_id
     *        音效ID，应用调用者维护，请保证唯一性。
     */
    virtual void onAudioEffectFinished(int sound_id) {
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
    virtual void onLogReport(const char* log_type, const char* log_content) {
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
    virtual void onAudioPlaybackDeviceChanged(AudioPlaybackDevice device) {
        (void)device;
    };

    /** 
     * @hidden(macOS,Windows)
     * @type callback
     * @region 音频事件回调
     * @brief 音频播放设备变化时回调该事件。
     * @param [in] device 变化后的音频播放设备，参看 AudioRoute{@link #AudioRoute}。  <br>
     */
    virtual void onAudioRouteChanged(AudioRoute route) {
        (void)route;
    };

    /** 
     * @type callback
     * @region 引擎管理
     * @brief SDK 与信令服务器连接状态改变回调。连接状态改变时触发。
     * @param [in] state 当前 SDK 与信令服务器的连接状态，详见 ConnectionState{@link #ConnectionState}。
     * @notes 更多信息参见 [连接状态提示](https://www.volcengine.com/docs/6348/95376)。
     */
    virtual void onConnectionStateChanged(bytertc::ConnectionState state) {
    }

    /** 
     * @type callback
     * @region 引擎管理
     * @brief SDK 当前网络连接类型改变回调。当 SDK 的当前网络连接类型发生改变时回调该事件。
     * @param [in] type  <br>
     *        SDK 当前的网络连接类型，详见：NetworkType{@link #NetworkType} 。
     */
    virtual void onNetworkTypeChanged(bytertc::NetworkType type) {
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
    virtual void onPerformanceAlarms(bytertc::PerformanceAlarmMode mode, const char* room_id,
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
    virtual void onMediaDeviceStateChanged(const char* device_id,
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
    virtual void onAudioDeviceStateChanged(const char* device_id, bytertc::RTCAudioDeviceType device_type,
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
    virtual void onVideoDeviceStateChanged(const char* device_id, bytertc::RTCVideoDeviceType device_type,
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
     virtual void onMediaDeviceWarning(const char* device_id, bytertc::MediaDeviceType device_type,
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
     virtual void onAudioDeviceWarning(const char* device_id, bytertc::RTCAudioDeviceType device_type,
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
     virtual void onVideoDeviceWarning(const char* device_id, bytertc::RTCVideoDeviceType device_type,
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
    virtual void onSysStats(const bytertc::SysStats& stats) {
    }

    /** 
     * @type callback
     * @region 代理回调
     * @brief HTTP 代理连接状态改变时，收到该回调。
     * @param [in] state 当前 HTTP 代理连接状态，详见 HttpProxyState{@link #HttpProxyState}
     */
    virtual void onHttpProxyState(int state) {
    }

    /** 
     * @type callback
     * @region 代理回调
     * @brief HTTPS 代理连接状态改变时，收到该回调。
     * @param  [out] state 当前 HTTPS 代理连接状态，详见 HttpProxyState{@link #HttpProxyState}
     */
    virtual void onHttpsProxyState(int state) {
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
    virtual void onSocks5ProxyState(int state,
        const char* cmd,
        const char* proxy_address,
        const char* local_address,
        const char* remote_address) {
    }

    /** 
     * @type callback
     * @region 本地录制
     * @brief 获取本地录制状态回调。  <br>
     *        该回调由 startFileRecording{@link #IRtcEngine#startFileRecording} 或 stopFileRecording{@link #IRtcEngine#stopFileRecording} 触发。
     * @param [out] type 录制流的流属性，参看 StreamIndex{@link #StreamIndex}
     * @param [out] state 录制状态，参看 RecordingState{@link #RecordingState}
     * @param [out] error_code 录制错误码，参看 RecordingErrorCode{@link #RecordingErrorCode}
     * @param [out] info 录制文件的详细信息，参看 RecordingInfo{@link #RecordingInfo}
     */
    virtual void onRecordingStateUpdate(
            StreamIndex type, RecordingState state, RecordingErrorCode error_code, RecordingInfo info) {
    }

    /** 
     * @type callback
     * @region 本地录制
     * @brief 本地录制进度回调。  <br>
     *        该回调由 startFileRecording{@link #IRtcEngine#startFileRecording} 触发，录制状态正常时，系统每秒钟都会通过该回调提示录制进度。
     * @param [out] type 录制流的流属性，参看 StreamIndex{@link #StreamIndex}
     * @param [out] process 录制进度，参看 RecordingProgress{@link #RecordingProgress}
     * @param [out] info 录制文件的详细信息，参看 RecordingInfo{@link #RecordingInfo}
     */
    virtual void onRecordingProgressUpdate(StreamIndex type, RecordingProgress process, RecordingInfo info) {
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
     *        从调用 login{@link #IRtcEngine#login} 接口开始到返回结果所用时长  <br>
     *        单位为 ms。
     * @notes 调用 login{@link #IRtcEngine#login} 后，会收到此回调。
     */
    virtual void onLoginResult(const char* uid, int error_code, int elapsed) {
        (void)uid;
        (void)error_code;
        (void)elapsed;
    }
    /** 
     * @type callback
     * @region 实时消息通信
     * @brief 登出结果回调
     * @notes 调用 logout{@link #IRtcEngine#logout} 后，会收到此回调。
     */
    virtual void onLogout() {
    }
    /** 
     * @type callback
     * @region 实时消息通信
     * @brief 设置应用服务器参数的返回结果
     * @param [in] error <br>
     *        设置结果  <br>
     *        + 返回 200，设置成功  <br>
     *        + 返回其他，设置失败，详见 UserMessageSendResult{@link #UserMessageSendResult}
     * @notes 调用 setServerParams{@link #IRtcEngine#setServerParams} 后，会收到此回调。
     */
    virtual void onServerParamsSetResult(int error) {
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
     * @notes 必须先调用 getPeerOnlineStatus{@link #IRtcEngine#getPeerOnlineStatus}，才能收到此回调。
     */
    virtual void onGetPeerOnlineStatus(const char* peer_user_id, int status) {
        (void)peer_user_id;
        (void)status;
    }
    /** 
     * @type callback
     * @region 实时消息通信
     * @brief 收到房间外用户调用 sendUserMessageOutsideRoom{@link #IRtcEngine#sendUserMessageOutsideRoom} 发来的文本消息时，会收到此回调
     * @param [in] uid  <br>
     *        消息发送者 ID
     * @param [in] message  <br>
     *        收到的文本消息内容
     */
    virtual void onUserMessageReceivedOutsideRoom(const char* uid, const char* message) {
        (void)uid;
        (void)message;
    }
    /** 
     * @type callback
     * @region 实时消息通信
     * @brief 收到房间外用户调用 sendUserBinaryMessageOutsideRoom{@link #IRtcEngine#sendUserBinaryMessageOutsideRoom} 发来的二进制消息时，会收到此回调
     * @param [in] uid  <br>
     *        消息发送者 ID
     * @param [in] size  <br>
     *        二进制消息长度
     * @param [in] message  <br>
     *        收到的二进制消息内容
     */
    virtual void onUserBinaryMessageReceivedOutsideRoom(const char* uid, int size, const uint8_t* message) {
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
     * @notes 当调用 sendUserMessageOutsideRoom{@link #IRtcEngine#sendUserMessageOutsideRoom} 或 sendUserBinaryMessageOutsideRoom{@link #IRtcEngine#sendUserBinaryMessageOutsideRoom} 发送消息后，会收到此回调。
     */
    virtual void onUserMessageSendResultOutsideRoom(int64_t msgid, int error) {
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
     * @notes 当调用 sendServerMessage{@link #IRtcEngine#sendServerMessage} 或 sendServerBinaryMessage{@link #IRtcEngine#sendServerBinaryMessage}} 发送消息后，会收到此回调。
     */
    virtual void onServerMessageSendResult(int64_t msgid, int error, const bytertc::ServerACKMsg& msg) {
        (void)msgid;
        (void)error;
        (void)msg;
    }

    /** 
     * @type callback
     * @region 视频管理
     * @brief 收到通过 sendSEIMessage{@link #IRtcEngine#sendSEIMessage} 发送的带有 SEI 消息的视频帧时，收到此回调
     * @param [in] stream_key 包含 SEI 发送者的用户名，所在的房间名和媒体流，参看 RemoteStreamKey{@link #RemoteStreamKey}
     * @param [in] message 收到的 SEI 消息内容
     * @param [in] length 收到的 SEI 消息长度
    */
   virtual void onSEIMessageReceived(RemoteStreamKey stream_key, const uint8_t* message, int length){
        (void)stream_key;
        (void)message;
        (void)length;
    }

    /** 
     * @hidden
     * @type callback
     * @region 消息
     * @brief 黑帧视频流发布状态回调。  <br>
     *        在语音通话场景下，本地用户调用 sendSEIMessage{@link #IRtcEngine#sendSEIMessage} 通过黑帧视频流发送 SEI 数据时，流的发送状态会通过该回调通知远端用户。  <br>
     *        你可以通过此回调判断携带 SEI 数据的视频帧为黑帧，从而不对该视频帧进行渲染。
     * @param key 远端流信息，参看 RemoteStreamKey{@link #RemoteStreamKey}。
     * @param type 黑帧视频流状态，参看 SEIStreamEventType{@link #SEIStreamEventType}
     */
    virtual void onSEIStreamUpdate(const RemoteStreamKey& key, SEIStreamEventType type) {
        (void)key;
        (void)type;
    }

     /** 
      * @type callback
      * @region 音频管理
      * @brief 远端用户进房后，本地调用 enableAudioPropertiesReport{@link #IRtcEngine#enableAudioPropertiesReport}，根据设置的 interval 值，本地会周期性地收到此回调，了解订阅的远端用户的音频信息。<br>
      *        远端用户的音频包括使用 RTC SDK 内部机制/自定义机制采集的麦克风音频和屏幕音频。
      * @param [in] audio_properties_infos 远端音频信息，其中包含音频流属性、房间 ID、用户 ID ，详见 RemoteAudioPropertiesInfo{@link #RemoteAudioPropertiesInfo}。
      * @param [in] audio_properties_info_number 数组长度
      * @param [in] total_remote_volume 所有订阅的远端流的总音量，范围是 [0,255]。  <br>
      *       + [0,25] 接近无声；  <br>
      *       + [25,75] 为低音量；  <br>
      *       + [76,204] 为中音量；  <br>
      *       + [205,255] 为高音量。  <br>
      */
     virtual void onRemoteAudioPropertiesReport(const RemoteAudioPropertiesInfo* audio_properties_infos, int audio_properties_info_number, int total_remote_volume) {
        (void)audio_properties_infos;
        (void)audio_properties_info_number;
        (void)total_remote_volume;
    }

     /** 
      * @type callback
      * @region 音频管理
      * @brief 调用 enableAudioPropertiesReport{@link #IRtcEngine#enableAudioPropertiesReport} 后，根据设置的 interval 值，你会周期性地收到此回调，了解本地音频的相关信息。  <br>
      *        本地音频包括使用 RTC SDK 内部机制采集的麦克风音频和屏幕音频。
      * @param [in] audio_properties_infos 本地音频信息，详见 LocalAudioPropertiesInfo{@link #LocalAudioPropertiesInfo} 。
      * @param [in] audio_properties_info_number 数组长度
      */
     virtual void onLocalAudioPropertiesReport(const LocalAudioPropertiesInfo * audio_properties_infos, int audio_properties_info_number) {
        (void)audio_properties_infos;
        (void)audio_properties_info_number;
    }
    /** 
     * @hidden(Linux)
     * @type callback
     * @region 音频设备管理
     * @brief 回调音频设备测试时的播放音量
     * @param [in] volume 音频设备测试播放音量。单位：毫秒。推荐设置为 200 ms。范围：[0,255]
     * @notes 调用 startAudioPlaybackDeviceTest{@link #IAudioDeviceManager#startAudioPlaybackDeviceTest} 或 startAudioDeviceRecordTest{@link #IAudioDeviceManager#startAudioDeviceRecordTest}，开始播放音频文件或录音时，将开启该回调。本回调为周期性回调，回调周期由上述接口的 `interval` 参数指定。
     */
    virtual void onAudioPlaybackDeviceTestVolume(int volume) {
        (void)volume;
    }

    /** 
     * @hidden(Android,iOS)
     * @type callback
     * @region 设备管理
     * @brief 音频设备音量回调。
     * @param [in] device_type 设备类型，有关详细信息，请参阅 RTCAudioDeviceType{@link #RTCAudioDeviceType}。
     * @param [in] volume 音量值，[0,  255]。
     * @param [in] muted 是否禁音状态，{true, false}。
     */
    virtual void onAudioDeviceVolumeChanged(bytertc::RTCAudioDeviceType device_type, int volume, bool muted) {
        (void)device_type;
        (void)volume;
        (void)muted;
    }

    /** 
     * @type callback
     * @region 音频管理
     * @brief 调用 enableAudioPropertiesReport{@link #IRtcEngine#enableAudioPropertiesReport} 后，根据设置的 `config.interval`，你会周期性地收到此回调，获取房间内的最活跃用户信息。
     * @param room_id 房间 ID
     * @param uid 最活跃用户（ActiveSpeaker）的用户 ID
     */
    virtual void onActiveSpeaker(const char* room_id, const char* uid) {
        (void)room_id;
        (void)uid;
    }

    /** 
     * @type api
     * @region 音频管理
     * @brief 音频流同步信息回调。可以通过此回调，在远端用户调用 sendStreamSyncInfo{@link #IRtcEngine#sendStreamSyncInfo} 发送音频流同步消息后，收到远端发送的音频流同步信息。  <br>
     * @param [in] stream_key 远端流信息，详见 RemoteStreamKey{@link #RemoteStreamKey} 。
     * @param [in] stream_type 媒体流类型，详见 SyncInfoStreamType{@link #SyncInfoStreamType} 。
     * @param [in] data 消息内容。
     * @param [in] length 消息长度。
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
     * @notes 成功调用 startNetworkDetection{@link #IRtcEngine#startNetworkDetection} 接口开始探测后，会每 2s 收到一次此回调。
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
     * @type callback
     * @region 通话前网络探测
     * @brief 通话前网络探测结束
     *        以下情况将停止探测并收到本一次本回调：<br>
     *        1. 当调用 stopNetworkDetection{@link #IRtcEngine#stopNetworkDetection} 接口停止探测后，会收到一次该回调；
     *        2. 当收到远端/本端音频首帧后，停止探测；
     *        3. 当探测超过3分钟后，停止探测；
     *        4. 当探测链路断开一定时间之后，停止探测。
     * @param [in] reason  <br>
     *        停止探测的原因类型,参考 NetworkDetectionStopReason{@link #NetworkDetectionStopReason}  <br>
     */
    virtual void onNetworkDetectionStopped(NetworkDetectionStopReason reason){
        (void)reason;
    }
    /** 
     * @type callback
     * @brief 订阅公共流的结果回调<br>
     *        通过 startPlayPublicStream{@link #IRtcEngine#startPlayPublicStream} 订阅公共流后，可以通过本回调获取订阅结果。
     * @param [in] public_stream_id 公共流的 ID
     * @param [in] errorCode 公共流订阅结果状态码。<br>
     *             `200`: 订阅成功
     */
    virtual void onPlayPublicStreamResult(const char* public_stream_id, int errorCode) {
        (void)public_stream_id;
        (void)errorCode;
    }
    /** 
     * @type callback
     * @brief 回调公共流中包含的 SEI 信息<br>
     *        通过 startPlayPublicStream{@link #IRtcEngine#startPlayPublicStream} 开始播放公共流后，可以通过本回调获取公共流中包含的 SEI 信息。
     * @param [in] public_stream_id 公共流 ID
     * @param [in] message SEI 信息
     * @param [in] message_length SEI 信息的长度
     * @notes 当公共流中的多路视频流均包含有 SEI 信息时：<br>
     *       SEI 不互相冲突时，将通过多次回调分别发送；<br>
     *       SEI 在同一帧有冲突时，则只有一条流中的 SEI 信息被透传并融合到公共流中。
     */
    virtual void onPublicStreamSEIMessageReceived(const char* public_stream_id, const uint8_t* message, int message_length) {
        (void)public_stream_id;
        (void)message;
        (void)message_length;
    }
    /** 
     * @type callback
     * @brief 公共流的首帧视频解码成功<br>
     *        关于订阅公共流，详见 startPlayPublicStream{@link #IRtcEngine#startPlayPublicStream}。
     * @param [in] public_stream_id 公共流 ID
     * @param [in] info 视频帧信息。详见 VideoFrameInfo{@link #VideoFrameInfo}。
     */
    virtual void onFirstPublicStreamVideoFrameDecoded(const char* public_stream_id, const VideoFrameInfo& info) {
        (void)public_stream_id;
    }
    /** 
     * @type callback
     * @brief 公共流的音频首帧解码成功<br>
     *        关于订阅公共流，详见 startPlayPublicStream{@link #IRtcEngine#startPlayPublicStream}。
     * @param [in] public_stream_id 公共流 ID
     */
    virtual void onFirstPublicStreamAudioFrame(const char* public_stream_id) {
        (void)public_stream_id;
    }
    
    /** 
     * @type callback
     * @region 房间管理
     * @brief 房间状态改变回调，加入房间、异常退出房间、发生房间相关的警告或错误时会收到此回调。
     * @param [in] room_id 房间 ID。
     * @param [in] uid 用户 ID。
     * @param [in] state 房间状态码。  <br>
     *              + 0: 成功。  <br>
     *              + !0: 失败或异常退房。具体原因参看 ErrorCode{@link #ErrorCode} 及 WarningCode{@link #WarningCode}。异常退出房间，具体原因包括<br>
     *               - -1004：相同 ID 用户在其他端进房； <br>
     *               - -1006：用户被踢出当前房间。
     * @param [in] extra_info 额外信息。
     *                  `join_type`表示加入房间的类型，`0`为首次进房，`1`为重连进房。
     *                  `elapsed`表示加入房间耗时，即本地用户从调用 joinRoom{@link #IRTCRoom#joinRoom} 到加入房间成功所经历的时间间隔，单位为 ms。
     */
    virtual void onRoomStateChanged(
            const char* room_id, const char* uid, int state, const char* extra_info) {
        (void)room_id;
        (void)state;
        (void)extra_info;
    }
    
    /** 
     * @type callback
     * @region 房间管理
     * @brief 流状态改变回调，发生流相关的警告或错误时会收到此回调。
     * @param [in] room_id 房间 ID。
     * @param [in] uid 用户 ID。
     * @param [in] state 流状态码，参看 ErrorCode{@link #ErrorCode} 及 WarningCode{@link #WarningCode}。
     * @param [in] extra_info 附加信息，目前为空。
     */
    virtual void onStreamStateChanged(
            const char* room_id, const char* uid, int state, const char* extra_info) {
        (void)room_id;
        (void)state;
        (void)extra_info;
    }

    /** 
     * @type callback
     * @region 房间管理
     * @brief 离开房间回调。  <br>
     *        用户调用 leaveRoom{@link #IRTCRoom#leaveRoom} 方法后，SDK 会停止所有的发布订阅流，并在释放所有与通话相关的音视频资源后，通过此回调通知用户离开房间成功。  <br>
     * @param [in] stats 本次通话的统计数据，参看 RtcRoomStats{@link #RtcRoomStats} 。  <br>
     * @notes  <br>
     *       + 用户调用 leaveRoom{@link #IRTCRoom#leaveRoom} 方法离开房间后，若立即调用 destroyRtcEngine{@link #destroyRtcEngine} 方法销毁 RTC 引擎，则将无法收到此回调事件。  <br>
     *       + 离开房间后，如果 App 需要使用系统音视频设备，则建议收到此回调后再初始化音视频设备，否则可能由于 SDK 占用音视频设备而导致初始化失败。  <br>
     */
     virtual void onLeaveRoom(const RtcRoomStats& stats) {
        (void)stats;
    }

    virtual void onTokenWillExpire() {

    }

    /** 
     * @hidden
     * @deprecated since 329.1, use onLocalAudioPropertiesReport/onRemoteAudioPropertiesReport instead
     * @type callback
     * @region 音频事件回调
     * @brief 提示房间内所有用户发送音量的回调。
     * @param [in] speakers 本地用户和订阅的远端用户的 ID 和音量。
     *                      参见：AudioVolumeInfo{@link #AudioVolumeInfo}。
     * @param [in] speaker_number speakers 数组长度。
     * @param [in] total_remote_volume speakers 中包含的所有音频音量之和，取值范围是：[0,255]
     * @notes
     *        + 对于本地用户：只要进行本地音频采集，回调内就会包含本地音频流的音量信息。<br>
     *        + 对于远端用户：本地必须订阅某远端用户的音频流，回调内才会包含其发送的音频流的音量信息。
     */
    virtual void onAudioVolumeIndication(const AudioVolumeInfo* speakers, unsigned int speaker_number, int total_remote_volume) {
        (void)speakers;
        (void)speaker_number;
        (void)total_remote_volume;
    }


    /** 
     * @type callback
     * @region 数据统计
     * @brief 房间内通话统计信息回调。   <br>
     *        用户进房开始通话后，每 2s 收到一次本回调。
     * @param [in] stats 当前 RtcEngine 统计数据，详见 RtcRoomStats{@link #RtcRoomStats}
     */
    virtual void onRoomStats(const RtcRoomStats& stats) {
        (void)stats;
    }
    /** 
     * @type callback
     * @region 数据统计
     * @brief 发布流成功后，每隔 2s 收到此回调，了解发布的流在此周期内的网络质量信息。
     * @param [in] stats 当前 RtcEngine 统计数据，详见 LocalStreamStats{@link #LocalStreamStats}
     */
    virtual void onLocalStreamStats(const LocalStreamStats& stats) {
        (void)stats;
    }
    /** 
     * @type callback
     * @region 数据统计
     * @brief 每隔 2s 收到此回调，了解订阅的远端用户发布的流在此周期内的网络质量信息。
     * @param [in] stats 当前 RtcEngine 统计数据，详见 RemoteStreamStats{@link #RemoteStreamStats}
     */
    virtual void onRemoteStreamStats(const RemoteStreamStats& stats) {
        (void)stats;
    }

    /** 
     * @type callback
     * @region 房间管理
     * @brief 远端可见用户加入房间，或房内隐身用户切换为可见的回调。<br>
     *        1. 远端用户调用 setUserVisibility{@link #IRTCRoom#setUserVisibility} 方法将自身设为可见后加入房间时，房间内其他用户将收到该事件。  <br>
     *        2. 远端可见用户断网后重新连入房间时，房间内其他用户将收到该事件。  <br>
     *        3. 房间内隐身远端用户调用 setUserVisibility{@link #IRTCRoom#setUserVisibility} 方法切换至可见时，房间内其他用户将收到该事件。  <br>
     *        4. 新进房用户会收到进房前已在房内的可见用户的进房回调通知。  <br>
     * @param [in] user_info 用户信息，详见 UserInfo{@link #UserInfo}  <br>
     * @param [in] elapsed 此参数无意义
     */
     virtual void onUserJoined(const UserInfo& user_info, int elapsed) {
        (void)user_info;
        (void)elapsed;
    }

    /** 
     * @type callback
     * @brief 远端用户离开房间，或切至不可见时，本地用户会收到此事件
     * @param uid 离开房间，或切至不可见的的远端用户 ID。  <br>
     * @param reason 用户离开房间的原因：  <br>
     *              + 0: 远端用户调用 leaveRoom{@link #IRTCRoom#leaveRoom} 主动退出房间。  <br>
     *              + 1: 远端用户因 Token 过期或网络原因等掉线。详细信息请参看[连接状态提示](hhttps://www.volcengine.com/docs/6348/95376) <br>
     *              + 2: 远端用户调用 setUserVisibility{@link #IRTCRoom#setUserVisibility} 切换至不可见状态。 <br>
     *              + 3: 服务端调用 OpenAPI 将远端用户踢出房间。
     */
     virtual void onUserLeave(const char* uid, UserOfflineReason reason) {
        (void)uid;
        (void)reason;
    }

    /** 
     * @hidden
     * @type callback
     * @region 媒体流管理
     * @brief 当房间内用户调用 muteAllRemoteAudio{@link #IRTCRoom#muteAllRemoteAudio}，
     *        改变接收所有远端音频流的状态时, 房间内其他用户收到这个回调。
     * @param [in] user_id 改变接收状态的用户 ID
     * @param [in] mute_state 接收状态，详见：MuteState{@link #MuteState}
     */
    virtual void onMuteAllRemoteAudio(const char* user_id, MuteState mute_state) {
        (void)user_id;
        (void)mute_state;
    }


    /** 
     * @hidden
     * @type callback
     * @region 媒体流管理
     * @brief 房间内用户暂停/恢复接收所有视频流时，房间内其他用户收到此回调。参看 muteAllRemoteVideo{@link #muteAllRemoteVideo}。
     * @param [in] uid 暂停/恢复接收视频流的用户 ID。
     * @param  [in] mute 暂停/恢复接收视频流的状态。参看 MuteState{@link #MuteState}。
     */
    virtual void onMuteAllRemoteVideo(const char* uid, MuteState mute) {
        (void)uid;
        (void)mute;
    }


    /** 
     * @hidden
     * @deprecated since 336.1, use onUserPublishStream, onUserPublishScreen, onUserUnPublishStream and onUserUnPublishScreen instead.
     * @type callback
     * @region 媒体流管理
     * @brief 房间内用户暂停/恢复发送音频流时，房间内其他用户会收到此回调。参看 muteLocalAudio{@link #IRtcEngine#muteLocalAudio}。
     * @param [in] user_id 改变本地音频发送状态的用户 ID
     * @param [in] mute_state 发送状态，参看 MuteState{@link #MuteState}
     */
    virtual void onUserMuteAudio(const char* user_id, MuteState mute_state) {
        (void)user_id;
        (void)mute_state;
    }


    /** 
     * @hidden
     * @deprecated since 323.1, use onUserStartAudioCapture instead
     * @type callback
     * @region 音频事件回调
     * @brief 远端用户开启/关闭音频设备采集时，房间内其他人会收到这个回调。
     *        该回调由远端用户调用 startAudioCapture{@link #IRtcEngine#startAudioCapture} 方法触发。
     * @param [in] uid 远端用户ID
     * @param [in] enabled 该用户是否开启了音频设备采集  <br>
     *       + true: 该用户开启了音频设备采集  <br>
     *       + false: 该用户关闭了音频设备采集  <br>
     *       + 该接口已废弃，请使用 OnUserStartAudioCapture{@link #IRtcEngineEventHandler#OnUserStartAudioCapture} 以及 onUserStopAudioCapture{@link #IRTCRoomEventHandler#onUserStopAudioCapture} <br>
     */
    virtual void onUserEnableLocalAudio(const char* uid, bool enabled) {
        (void)uid;
        (void)enabled;
    }

    /** 
     * @type callback
     * @region 音频事件回调
     * @brief 房间内的可见用户调用 startAudioCapture{@link #IRtcEngine#startAudioCapture} 开启音频采集时，房间内其他用户会收到此回调。
     * @param [in] user_id 开启音频采集的远端用户 ID
     */
    virtual void onUserStartAudioCapture(const char* user_id) {
        (void)user_id;
    }

    /** 
     * @type callback
     * @region 音频事件回调
     * @brief 房间内的可见用户调用 stopAudioCapture{@link #IRtcEngine#stopAudioCapture} 关闭音频采集时，房间内其他用户会收到此回调。
     * @param [in] user_id 关闭音频采集的远端用户 ID
     */
    virtual void onUserStopAudioCapture(const char* user_id) {
        (void)user_id;
    }

    /** 
     * @type callback
     * @region 音频事件回调
     * @brief 本地采集到第一帧音频帧时，收到该回调
     * @param [in] index 音频流属性, 参看 StreamIndex{@link #StreamIndex}
     */
    virtual void onFirstLocalAudioFrame(StreamIndex index) {
        (void)index;
    }


    /** 
     * @type callback
     * @region 音频事件回调
     * @brief 接收到来自远端某音频流的第一帧时，收到该回调。
     * @param [in] key 远端音频流信息, 详见 RemoteStreamKey{@link #RemoteStreamKey}
     * @notes 用户刚收到房间内每一路音频流时，都会收到该回调。
     */
    virtual void onFirstRemoteAudioFrame(const RemoteStreamKey& key) {
        (void)key;
    }


    /** 
     * @hidden
     * @deprecated since 336.1, use onUserUnPublishStream and onUserUnPublishScreen instead.
     * @type callback
     * @region 房间管理
     * @brief 房间内的远端用户停止发布音视频流时，本地用户会收到此回调。
     * @param [in] stream 流的属性。参看 MediaStreamInfo{@link #MediaStreamInfo} 。
     * @param [in] reason 远端流移除的原因。参看 StreamRemoveReason{@link #StreamRemoveReason} 。
     */
    virtual void onStreamRemove(const MediaStreamInfo& stream, StreamRemoveReason reason) {
        (void)stream;
    }


    /** 
     * @hidden
     * @deprecated since 336.1, use onUserPublishStream and onUserPublishScreen instead.
     * @type callback
     * @region 房间管理
     * @brief 房间内的用户发布新的音视频流时，房间内的其他用户会收到此回调。包括移除后又重新发布的流。  <br>
     * @param [in] stream 流属性，参看 MediaStreamInfo{@link #MediaStreamInfo} 。  <br>
     */
    virtual void onStreamAdd(const MediaStreamInfo& stream) {
        (void)stream;
    }
    /** 
     * @type callback
     * @region 房间管理
     * @brief 房间内新增远端摄像头/麦克风采集的媒体流的回调。
     * @param [in] uid 远端流发布用户的用户 ID。
     * @param [in] type 远端媒体流的类型，参看 MediaStreamType{@link #MediaStreamType}。
     * @notes 当房间内的远端用户调用 publishStream{@link #IRTCRoom#publishStream} 成功发布由摄像头/麦克风采集的媒体流时，本地用户会收到该回调，此时本地用户可以自行选择是否调用 subscribeStream{@link #IRTCRoom#subscribeStream} 订阅此流。
     */
    virtual void onUserPublishStream(const char* uid, MediaStreamType type) {
        (void)uid;
        (void)type;
    }
    /** 
     * @type callback
     * @region 房间管理
     * @brief 房间内远端摄像头/麦克风采集的媒体流移除的回调。
     * @param [in] uid 移除的远端流发布用户的用户 ID。  <br>
     * @param [in] type 移除的远端流类型，参看 MediaStreamType{@link #MediaStreamType}。  <br>
     * @param [in] reason 远端流移除的原因，参看 StreamRemoveReason{@link #StreamRemoveReason}。
     * @notes 收到该回调通知后，你可以自行选择是否调用 unsubscribeStream{@link #IRTCRoom#unsubscribeStream} 取消订阅此流。
     */
    virtual void onUserUnPublishStream(const char* uid, MediaStreamType type,StreamRemoveReason reason) {
        (void)uid;
        (void)type;
        (void)reason;
    }
    /** 
     * @type callback
     * @region 房间管理
     * @brief 房间内新增远端屏幕共享音视频流的回调。
     * @param [in] uid 远端流发布用户的用户 ID。
     * @param [in] type 远端媒体流的类型，参看 MediaStreamType{@link #MediaStreamType}。
     * @notes 当房间内的远端用户调用 publishScreen{@link #IRTCRoom#publishScreen} 成功发布来自屏幕共享的音视频流时，本地用户会收到该回调，此时本地用户可以自行选择是否调用 subscribeScreen{@link #IRTCRoom#subscribeScreen} 订阅此流。
     */
    virtual void onUserPublishScreen(const char* uid, MediaStreamType type) {
        (void)uid;
        (void)type;
    }
    /** 
     * @type callback
     * @region 房间管理
     * @brief 房间内远端屏幕共享音视频流移除的回调。
     * @param [in] uid 移除的远端流发布用户的用户 ID。  <br>
     * @param [in] type 移除的远端流类型，参看 MediaStreamType{@link #MediaStreamType}。  <br>
     * @param [in] reason 远端流移除的原因，参看 StreamRemoveReason{@link #StreamRemoveReason}。
     * @notes 收到该回调通知后，你可以自行选择是否调用 unsubscribeScreen{@link #IRTCRoom#unsubscribeScreen} 取消订阅此流。
     */
    virtual void onUserUnPublishScreen(const char* uid, MediaStreamType type,StreamRemoveReason reason) {
        (void)uid;
        (void)type;
        (void)reason;
    }
    
    /** 
     * @type callback
     * @region 房间管理
     * @brief 关于订阅媒体流状态改变的回调
     * @param [in] state_code 订阅媒体流状态，参看 SubscribeState{@link #SubscribeState}
     * @param [in] user_id 流发布用户的用户 ID
     * @param [in] info 流的属性，参看 SubscribeConfig{@link #SubscribeConfig}
     * @notes 本地用户收到该回调的时机包括：  <br>
     *        + 调用 subscribeStream{@link #IRTCRoom#subscribeStream} 或 unsubscribeStream{@link #IRTCRoom#unsubscribeStream} 订阅/取消订阅指定远端摄像头音视频流后；  <br>
     *        + 调用 subscribeScreen{@link #IRTCRoom#subscribeScreen} 或 unsubscribeScreen{@link #IRTCRoom#unsubscribeScreen} 订阅/取消订阅指定远端屏幕共享流后。
     */
    virtual void onStreamSubscribed(SubscribeState state_code, const char* user_id, const SubscribeConfig& info) {
        (void)state_code;
        (void)user_id;
        (void)info;
    }

    /** 
     * @type callback
     * @region 音视频回退
     * @brief 因发布/订阅性能回退或退出回退状态，订阅的音视频流，发生流的切换时，收到该回调。
     * @param [in] event 流切换信息。详见 RemoteStreamSwitch{@link #RemoteStreamSwitch}。
     * @notes  <br>
     *        + 你必须先通过 API 或控制台设置音视频流订阅回退功能时，你才能收到此回调。
     */
    virtual void onSimulcastSubscribeFallback(const RemoteStreamSwitch& event) {
        (void)event;
    }

    /** 
     * @hidden
     * @type callback
     * @region 房间管理
     * @brief 当发布流成功的时候回调该事件。
     * @param [in] user_id 发布流的用户 ID。
     * @param [in] is_screen 该流是否为屏幕流。  <br>
     *             + Ture: 屏幕流；  <br>
     *             + False: 非屏幕流。  <br>
     */
    virtual void onStreamPublishSuccess(const char* user_id, bool is_screen) {
        (void)is_screen;
    }

    /** 
     * @type callback
     * @region 实时消息通信
     * @brief 接收到房间内广播消息的回调。
     * @param [in] uid  <br>
     *        消息发送者 ID
     * @param [in] message  <br>
     *        收到的消息内容
     * @notes 同一房间内其他用户调用 sendRoomMessage{@link #IRTCRoom#sendRoomMessage} 发送广播消息时会收到该回调。
     */
    virtual void onRoomMessageReceived(const char* uid, const char* message) {
        (void)uid;
        (void)message;
    }

    /** 
     * @type callback
     * @region 实时消息通信
     * @brief 接收到房间内二进制广播消息的回调。
     * @param [in] uid  <br>
     *        消息发送者 ID
     * @param [in] size <br>
     *        收到的二进制消息长度
     * @param [in] message <br>
     *        收到的二进制消息内容
     * @notes 同一房间内其他用户调用 sendRoomBinaryMessage{@link #IRTCRoom#sendRoomBinaryMessage} 发送二进制广播消息时会收到该回调。
     */
    virtual void onRoomBinaryMessageReceived(const char* uid, int size, const uint8_t* message) {
        (void)uid;
        (void)size;
        (void)message;
    }
    /** 
     * @type callback
     * @region 实时消息通信
     * @brief 收到来自房间中其他用户发来的文本消息时（P2P），会收到此回调。
     * @param [in] uid  <br>
     *        消息发送者 ID 。
     * @param [in] message  <br>
     *        收到的文本消息内容。
     * @notes  <br>
     *        + 你必须先调用 sendUserMessage{@link #IRTCRoom#sendUserMessage} 方法，才能收到该回调。
     */
    virtual void onUserMessageReceived(const char* uid, const char* message) {
        (void)uid;
        (void)message;
    }

    /** 
     * @type callback
     * @region 实时消息通信
     * @brief 单个用户接收到同一房间内其他 uid 所属用户发来二进制消息的回调（P2P）。
     * @param [in] uid  <br>
     *        消息发送者 ID 。
     * @param [in] message  <br>
     *        收到的二进制消息内容。
     * @notes  <br>
     *        + 同一房间内其他用户调用 sendUserBinaryMessage{@link #IRTCRoom#sendUserBinaryMessage} 发送二进制消息给本地用户时，本地用户会收到该回调。
     */
    virtual void onUserBinaryMessageReceived(const char* uid, int size, const uint8_t* message) {
        (void)uid;
        (void)size;
        (void)message;
    }

    /** 
     * @type callback
     * @region 实时消息通信
     * @brief 向房间内单个用户发送文本或二进制消息后（P2P），消息发送方会收到该消息发送结果回调。
     * @param [in] msgid  <br>
     *            本条消息的 ID。
     * @param [in] error  <br>
     *            文本或二进制消息发送结果，详见 UserMessageSendResult{@link #UserMessageSendResult}
     * @notes  <br>
     *        + 你必须先调用 sendUserMessage{@link #IRTCRoom#sendUserMessage} 或 sendUserBinaryMessage{@link #IRTCRoom#sendUserBinaryMessage} 接口，才能收到此回调。
     */
    virtual void onUserMessageSendResult(int64_t msgid, int error) {
        (void)msgid;
        (void)error;
    }

    /** 
     * @type callback
     * @region 实时消息通信
     * @brief 当调用 sendRoomMessage{@link #IRTCRoom#sendRoomMessage} 函数发送消息后，回调此条消息的发送结果（反馈）。
     * @param [in] msgid  <br>
     *        本条消息的 ID
     * @param [in] error  <br>
     *        消息发送结果  <br>
     *        详见 RoomMessageSendResult{@link #RoomMessageSendResult}
     */
    virtual void onRoomMessageSendResult(int64_t msgid, int error) {
        (void)msgid;
        (void)error;
    }

    /*
     * @hidden
     * @deprecated
     */
    virtual void onRoomModeChanged(RtcRoomMode mode) {
        (void)mode;
    }

#ifndef ByteRTC_AUDIO_ONLY
    /** 
     * @type callback
     * @region 视频管理
     * @brief RTC SDK 在本地完成第一帧视频帧或屏幕视频帧采集时，收到此回调。
     * @param [in] index 流属性。参看 StreamIndex{@link #StreamIndex}。
     * @param [in] info 视频信息。参看 VideoFrameInfo{@link #VideoFrameInfo}。
     * @notes 对于采集到的本地视频帧，你可以调用 setLocalVideoCanvas{@link #IRtcEngine#setLocalVideoCanvas} 或 setLocalVideoSink{@link #IRtcEngine#setLocalVideoSink} 在本地渲染。
     */
    virtual void onFirstLocalVideoFrameCaptured(StreamIndex index, VideoFrameInfo info) {
        (void)index;
        (void)info;
    }


    /** 
     * @type callback
     * @region 视频管理
     * @brief 本地视频大小或旋转配置发生改变时，收到此回调。
     * @param [in] index 流属性。参看 StreamIndex{@link #StreamIndex}。
     * @param [in] info 视频帧信息。参看 VideoFrameInfo{@link #VideoFrameInfo}。
     */
    virtual void onLocalVideoSizeChanged(StreamIndex index, const VideoFrameInfo& info) {
        (void)index;
        (void)info;
    }


    /** 
     * @type callback
     * @region 视频管理
     * @brief 远端视频大小或旋转配置发生改变时，房间内订阅此视频流的用户会收到此回调。
     * @param [in] key 远端流信息。参看 RemoteStreamKey{@link #RemoteStreamKey}。
     * @param [in] info 视频帧信息。参看 VideoFrameInfo{@link #VideoFrameInfo}。
     */
    virtual void onRemoteVideoSizeChanged(RemoteStreamKey key, const VideoFrameInfo& info) {
        (void)key;
        (void)info;
    }


    /** 
     * @type callback
     * @region 视频管理
     * @brief SDK 内部渲染成功远端视频流首帧后，收到此回调。
     * @param [in] key 远端流信息。参看 RemoteStreamKey{@link #RemoteStreamKey}。
     * @param [in] info 视频帧信息。参看 VideoFrameInfo{@link #VideoFrameInfo}。
     */
    virtual void onFirstRemoteVideoFrameRendered(const RemoteStreamKey key, const VideoFrameInfo& info) {
        (void)key;
        (void)info;
    }

    /** 
     * @type callback
     * @region 视频管理
     * @brief SDK 接收并解码远端视频流首帧后，收到此回调。
     * @param [in] key 远端流信息。参看 RemoteStreamKey{@link #RemoteStreamKey}。
     * @param [in] info 视频帧信息。参看 VideoFrameInfo{@link #VideoFrameInfo}。
     */
    virtual void onFirstRemoteVideoFrameDecoded(const RemoteStreamKey key, const VideoFrameInfo& info) {
        (void)key;
        (void)info;
    }

    /** 
     * @hidden
     * @deprecated since 336.1, use onUserPublishStream, onUserPublishScreen, onUserUnPublishStream and onUserUnPublishScreen instead.
     * @type callback
     * @region 媒体流管理
     * @brief 房间内用户暂停/恢复发送视频流时，房间内其他用户会收到此回调。参看 muteLocalVideo{@link #IRtcEngine#muteLocalVideo}。
     * @param [in] uid 暂停/恢复发送视频流的用户 ID。
     * @param [in] mute 视频流的发送状态。参看 MuteState{@link #MuteState}。
     */
    virtual void onUserMuteVideo(const char* uid, MuteState mute) {
        (void)uid;
        (void)mute;
    }

    /** 
     * @hidden
     * @deprecated since 325.1, use onUserStartVideoCapture instead
     * @type callback
     * @region 视频管理
     * @brief 远端用户开启/关闭本地视频采集时回调该事件，当远端用户调用 EnableLocalVideo 时，其他用户会触发此回调。
     * @param [in] uid 用户ID，提示是哪个用户的视频流。
     * @param [in] enabled 是否启用本地视频功能。  <br>
     *       + true：该用户已启用本地视频功能。启用后，其他用户可以接收到该用户的视频流。  <br>
     *       + false：该用户已关闭视频功能。关闭后，该用户仍然可以接收其他用户的视频流，但其他用户接收不到该用户的视频流。  <br>
     * @notes 提示有其他用户启用/关闭了本地视频功能。
     *       + 该接口已废弃，请使用 onUserStartVideoCapture{@link #IRtcEngineEventHandler#onUserStartVideoCapture} 以及 onUserStopVideoCapture{@link #IRtcEngineEventHandler#onUserStopVideoCapture} <br>
     */
    virtual void onUserEnableLocalVideo(const char* uid, bool enabled) {
        (void)uid;
        (void)enabled;
    }

    /** 
     * @type callback
     * @region 视频事件回调
     * @brief 房间内的可见用户调用 startVideoCapture{@link #IRtcEngine#startVideoCapture} 开启内部视频采集时，房间内其他用户会收到此回调。
     * @param [in] user_id 开启视频采集的远端用户 ID
     */
    virtual void onUserStartVideoCapture(const char* user_id) {
        (void)user_id;
    }

    /** 
     * @type callback
     * @region 视频事件回调
     * @brief 房间内的可见用户调用 stopVideoCapture{@link #IRtcEngine#stopVideoCapture} 关闭内部视频采集时，房间内其他用户会收到此回调。
     * @param [in] user_id 关闭视频采集的远端用户 ID
     */
    virtual void onUserStopVideoCapture(const char* user_id) {
        (void)user_id;
    }

    /** 
     * @type callback
     * @region 音频事件回调
     * @brief 本地音频的状态发生改变时，该回调通知当前的本地音频状态。
     * @param [in] state 本地音频设备的状态，详见： LocalAudioStreamState{@link #LocalAudioStreamState}
     * @param [in] error 本地音频状态改变时的错误码，详见：LocalAudioStreamError{@link #LocalAudioStreamError}
     */
    virtual void onLocalAudioStateChanged(LocalAudioStreamState state, LocalAudioStreamError error) {
        (void)state;
        (void)error;
    }

    /** 
     * @type callback
     * @region 音频事件回调
     * @brief 用户订阅来自远端的音频流状态发生改变时，会收到此回调，了解当前的远端音频流状态。
     * @param [in] key 远端流信息, 参看 RemoteStreamKey{@link #RemoteStreamKey}
     * @param [in] state 远端音频流状态，参看 RemoteAudioState{@link #RemoteAudioState}
     * @param [in] reason 远端音频流状态改变的原因，参看 RemoteAudioStateChangeReason{@link #RemoteAudioStateChangeReason}
     */
    virtual void onRemoteAudioStateChanged(
            const RemoteStreamKey& key, RemoteAudioState state, RemoteAudioStateChangeReason reason) {
        (void)key;
        (void)state;
        (void)reason;
    }

    /** 
     * @type callback
     * @region 视频管理
     * @brief 本地视频流的状态发生改变时，收到该事件。
     * @param [in] index 音/视频属性，参看 StreamIndex{@link #StreamIndex}
     * @param [in] state 本地视频流状态，参看 LocalVideoStreamState{@link #LocalVideoStreamState}
     * @param [in] error 本地视频状态改变时的错误码，参看 LocalVideoStreamError{@link #LocalVideoStreamError}
     */
    virtual void onLocalVideoStateChanged(StreamIndex index, LocalVideoStreamState state, LocalVideoStreamError error) {
        (void)index;
        (void)state;
        (void)error;
    }


    /** 
     * @type callback
     * @region 视频管理
     * @brief 远端视频流的状态发生改变时，房间内订阅此流的用户会收到该事件。
     * @param [in] key 远端视频流的信息，房间、用户 ID、流属性等。参看 RemoteStreamKey{@link #RemoteStreamKey}。
     * @param [in] state 远端视频流状态，参看 RemoteVideoState{@link #RemoteVideoState}。
     * @param [in] reason 远端视频流状态改变的原因，参看 RemoteVideoStateChangeReason{@link #RemoteVideoStateChangeReason}。
     */
    virtual void onRemoteVideoStateChanged(
            RemoteStreamKey key, RemoteVideoState state, RemoteVideoStateChangeReason reason) {
        (void)key;
        (void)state;
        (void)reason;
    }


    /** 
     * @hidden
     * @type callback
     * @region 视频管理
     * @brief 当订阅远端用户的时候触发此回调
     * @param [in] user_id 远端用户的 ID
     * @param [in] is_reconnect 是否为重连
     */
    virtual void onSubscribe(const char* user_id, bool is_reconnect) {
        (void)user_id;
        (void)is_reconnect;
    }

    /** 
     * @hidden
     * @type callback
     * @region 视频管理
     * @brief 当取消订阅远端用户的时候触发此回调
     * @param [in] user_id 远端用户的 ID
     * @param [in] is_reconnect 是否为重连
     */
    virtual void onUnSubscribe(const char* user_id, bool is_reconnect) {
        (void)user_id;
        (void)is_reconnect;
    }

    /** 
     * @type callback
     * @region 房间管理
     * @brief 音频首帧发送状态改变回调
     * @param [in] user 本地用户信息，详见 RtcUser{@link #RtcUser}
     * @param [in] state 首帧发送状态，详见 FirstFrameSendState{@link #FirstFrameSendState}
     */
    virtual void onAudioFrameSendStateChanged(const RtcUser& user, FirstFrameSendState state) {
        (void)user;
        (void)state;
    }

    /** 
     * @type callback
     * @region 房间管理
     * @brief 视频首帧发送状态改变回调
     * @param [in] user 本地用户信息，详见 RtcUser{@link #RtcUser}
     * @param [in] state 首帧发送状态，详见 FirstFrameSendState{@link #FirstFrameSendState}
     */
    virtual void onVideoFrameSendStateChanged(const RtcUser& user, FirstFrameSendState state) {
        (void)user;
        (void)state;
    }

    /** 
     * @type callback
     * @region 房间管理
     * @brief 屏幕共享流视频首帧发送状态改变回调
     * @param [in] user 本地用户信息，详见 RtcUser{@link #RtcUser}
     * @param [in] state 首帧发送状态，详见 FirstFrameSendState{@link #FirstFrameSendState}
     */
    virtual void onScreenVideoFrameSendStateChanged(const RtcUser& user, FirstFrameSendState state) {
        (void)user;
        (void)state;
    }

    /** 
     * @type callback
     * @region 房间管理
     * @brief 音频首帧播放状态改变回调
     * @param [in] user 远端用户信息，详见 RtcUser{@link #RtcUser}
     * @param [in] state 首帧播放状态，详见 FirstFramePlayState{@link #FirstFramePlayState}
     */
    virtual void onAudioFramePlayStateChanged(const RtcUser& user, FirstFramePlayState state) {
        (void)user;
        (void)state;
    }

    /** 
     * @type callback
     * @region 房间管理
     * @brief 视频首帧播放状态改变回调
     * @param [in] user 远端用户信息，详见 RtcUser{@link #RtcUser}
     * @param [in] state 首帧播放状态，详见 FirstFramePlayState{@link #FirstFramePlayState}
     */
    virtual void onVideoFramePlayStateChanged(const RtcUser& user, FirstFramePlayState state) {
        (void)user;
        (void)state;
    }

    /** 
     * @type callback
     * @region 房间管理
     * @brief 屏幕共享流视频首帧播放状态改变回调
     * @param [in] user 远端用户信息，详见 RtcUser{@link #RtcUser}
     * @param [in] state 首帧播放状态，详见 FirstFramePlayState{@link #FirstFramePlayState}
     */
    virtual void onScreenVideoFramePlayStateChanged(const RtcUser& user, FirstFramePlayState state) {
        (void)user;
        (void)state;
    }

    /*
     * @hidden
     * @brief callback when the maximum screen share fps is changed
     * @param [in] fps
     *           maximum screen share fps
     */
    virtual void onMaximumScreenShareFpsUpdated(int fps) {
        (void)fps;
    }

    /** 
     * @hidden
     * @brief 最大屏幕共享帧率改变时的回调
     * @param [in] screenPixels
     *        为了保持帧率而推荐的最大视频宽度×高度的值
     *
     */
    virtual void onMaximumScreenSharePixelsUpdated(int screenPixels) {
        (void)screenPixels;
    }

    /** 
     * @hidden
     * @type callback
     * @region 视频管理
     * @brief 拼接视图用户请求头像回调
     * @param [in] uid 用户ID
     */
    virtual void onNeedAvatar(const char* uid) {
        (void)uid;
    }

    /** 
     * @type callback
     * @region 视频管理
     * @brief 通过调用服务端 BanUserStream/UnbanUserStream 方法禁用/解禁指定房间内指定用户视频流的发送时，触发此回调。
     * @param [in] uid 被禁用/解禁的视频流用户 ID
     * @param [in] banned 视频流发送状态 <br>
     *        + true: 视频流发送被禁用 <br>
     *        + false: 视频流发送被解禁
     * @notes  <br>
     *        + 房间内指定用户被禁止/解禁视频流发送时，房间内所有用户都会收到该回调。  <br>
     *        + 若被封禁用户断网或退房后再进房，则依然是封禁状态，且房间内所有人会再次收到该回调。  <br>
     *        + 指定用户被封禁后，房间内其他用户退房后再进房，会再次收到该回调。  <br>
     *        + 通话人数超过 5 人时，只有被封禁/解禁用户会收到该回调。  <br>
     *        + 同一房间解散后再次创建，房间内状态清空。
     */
    virtual void onVideoStreamBanned(const char* uid, bool banned) {
        (void)uid;
        (void)banned;
    }

#endif  // ByteRTC_AUDIO_ONLY
    /** 
     * @type callback
     * @region 音频事件回调
     * @brief 通过调用服务端 BanUserStream/UnbanUserStream 方法禁用/解禁指定房间内指定用户音频流的发送时，触发此回调。
     * @param [in] uid 被禁用/解禁的音频流用户 ID
     * @param [in] banned 音频流发送状态 <br>
     *        + true: 音频流发送被禁用 <br>
     *        + false: 音频流发送被解禁
     * @notes  <br>
     *        + 房间内指定用户被禁止/解禁音频流发送时，房间内所有用户都会收到该回调。  <br>
     *        + 若被封禁用户断网或退房后再进房，则依然是封禁状态，且房间内所有人会再次收到该回调。  <br>
     *        + 指定用户被封禁后，房间内其他用户退房后再进房，会再次收到该回调。  <br>
     *        + 通话人数超过 5 人时，只有被封禁/解禁用户会收到该回调。   <br>
     *        + 同一房间解散后再次创建，房间内状态清空。
     */
    virtual void onAudioStreamBanned(const char* uid, bool banned) {
        (void)uid;
        (void)banned;
    }

    /** 
     * @type callback
     * @region 多房间
     * @brief 跨房间媒体流转发状态和错误回调
     * @param infos 跨房间媒体流转发目标房间信息数组，详见 ForwardStreamStateInfo{@link #ForwardStreamStateInfo}
     * @param info_count 数组长度，代表目标房间数
     */
    virtual void onForwardStreamStateChanged(ForwardStreamStateInfo* infos, int info_count) {
    }

    /** 
     * @type callback
     * @region 多房间
     * @brief 跨房间媒体流转发事件回调
     * @param infos 跨房间媒体流转发目标房间事件数组，详见 ForwardStreamEventInfo{@link #ForwardStreamEventInfo}
     * @param info_count 数组长度，代表目标房间数
     */
    virtual void onForwardStreamEvent(ForwardStreamEventInfo* infos, int info_count) {
    }

    /** 
     * @hidden(Linux)
     * @type callback
     * @brief 加入房间后， 以 2 秒 1 次的频率，报告用户的网络质量信息
     * @param [in] localQuality 本端网络质量，详见 NetworkQualityStats{@link #NetworkQualityStats}。
     * @param [in] remoteQualities 已订阅用户的网络质量，详见 NetworkQualityStats{@link #NetworkQualityStats}。
     * @param [in] remoteQualityNum `remoteQualities` 数组长度
     * @note 更多通话中的监测接口，详见[通话中质量监测](106866)
     */
    virtual void onNetworkQuality(const NetworkQualityStats& localQuality, const NetworkQualityStats* remoteQualities, int remoteQualityNum) {
    }

    /** 
     * @type callback
     * @brief 公共流发布结果回调。<br>
     *        调用 startPushPublicStream{@link #IRtcEngine#startPushPublicStream} 接口发布公共流后，启动结果通过此回调方法通知用户。
     * @param [in] public_streamid 公共流 ID
     * @param [in] errorCode 公共流发布结果状态码。<br>
     *             `200`: 发布成功<br>
     *             `1191`: 推流参数存在异常 <br>
     *             `1192`: 当前状态异常，通常为无法发起任务<br>
     *             `1193`: 服务端错误，不可恢复<br>
     *             `1195`: 服务端调用发布接口返回失败<br>
     *             `1196`: 超时无响应。推流请求发送后 10s 没有收到服务端的结果回调。客户端将每隔 10s 重试，3 次重试失败后停止。
     */
    virtual void onPushPublicStreamResult(const char* public_streamid, int errorCode) {
        (void)public_streamid;
        (void)errorCode;
    }
    /** 
     * @type callback
     * @region 网络管理
     * @brief 关于音视频回路测试结果的回调。
     * @param [in] result 测试结果，参看 EchoTestResult{@link #EchoTestResult}
     * @notes 该回调触发的时机包括： <br>
     *        + 检测过程中采集设备发生错误时；  <br>
     *        + 检测成功后；  <br>
     *        + 非设备原因导致检测过程中未接收到音/视频回放，停止检测后。
     */
    virtual void onEchoTestResult(EchoTestResult result) {
        (void)result;
    };
    
    /** 
     * @type callback
     * @region 多房间
     * @brief 发布端调用 setMultiDeviceAVSync{@link #IRTCRoom#setMultiDeviceAVSync} 后音视频同步状态发生改变时，会收到此回调。
     * @param state 音视频同步状态，参看 AVSyncState{@link #AVSyncState}。
     */
    virtual void onAVSyncStateChange(AVSyncState state) {
        (void)state;
    }
    /** 
     * @type callback
     * @brief 调用 startCloudProxy{@link #IRtcEngine#startCloudProxy} 开启云代理，SDK 首次成功连接云代理服务器时，回调此事件。
     * @param [in] interval 从开启云代理到连接成功经过的时间，单位为 ms
     */
    virtual void onCloudProxyConnected(int interval) {
        (void)interval;
    }


};

} // namespace bytertc

#endif // BYTE_RTC_EVENT_HANDLER_H__
