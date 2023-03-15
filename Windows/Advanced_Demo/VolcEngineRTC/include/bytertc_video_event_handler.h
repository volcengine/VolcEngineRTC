/*
 * Copyright (c) 2020 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC Event Handler Lite
*/

#pragma once

#ifndef BYTE_RTC_LITE_EVENT_HANDLER_H__
#define BYTE_RTC_LITE_EVENT_HANDLER_H__

#include "rtc/bytertc_defines.h"

namespace bytertc {
/** 
 * @type callback
 * @brief 音视频引擎事件回调接口
 */
class IRTCVideoEventHandler {
public:

    /**
     * @hidden
     */
    virtual ~IRTCVideoEventHandler() {
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
     * @type callback
     * @region 混音
     * @author majun.lvhiei
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
    virtual void onAudioMixingStateChanged(int mix_id, bytertc::AudioMixingState state, bytertc::AudioMixingError error) {
    }

    /** 
     * @type callback
     * @region 混音
     * @author majun.lvhiei
     * @brief 混音音频文件播放进度回调
     * @param [in] mix_id 混音 ID  <br>
     * @param [in] progress 当前混音音频文件播放进度，单位毫秒
     * @notes 调用 setAudioMixingProgressInterval{@link #IAudioMixingManager#setAudioMixingProgressInterval} 将时间间隔设为大于 0 的值后，或调用 startAudioMixing{@link #IAudioMixingManager#startAudioMixing} 将 AudioMixingConfig{@link #AudioMixingConfig} 中的时间间隔设为大于 0 的值后，SDK 会按照设置的时间间隔回调该事件。 <br>
     */
    virtual void onAudioMixingPlayingProgress(int mix_id, int64_t progress){
    }

    /** 
     * @type callback
     * @region 引擎管理
     * @author chenweiming.push
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
     * @hidden
     * @type callback
     * @region 音频事件回调
     * @author dixing
     * @brief 音频播放设备变化时回调该事件。
     * @param [in] device 变化后的音频播放设备，参看 AudioPlaybackDevice{@link #AudioPlaybackDevice}。  <br>
     */
    virtual void onAudioPlaybackDeviceChanged(AudioPlaybackDevice device) {
        (void)device;
    };

    /** 
     * @hidden(macOS,Windows,Linux)
     * @type callback
     * @region 音频事件回调
     * @author dixing
     * @brief 音频播放设备变化时回调该事件。
     * @param [in] device 变化后的音频播放设备，参看 AudioRoute{@link #AudioRoute}。  <br>
     */
    virtual void onAudioRouteChanged(AudioRoute route) {
        (void)route;
    };

    /** 
     * @type callback
     * @region 引擎管理
     * @author hanchenchen.c
     * @brief SDK 与信令服务器连接状态改变回调。连接状态改变时触发。
     * @param [in] state 当前 SDK 与信令服务器的连接状态，详见 ConnectionState{@link #ConnectionState}。
     * @notes 更多信息参见 [连接状态提示](https://www.volcengine.com/docs/6348/95376)。
     */
    virtual void onConnectionStateChanged(bytertc::ConnectionState state) {
    }

    /** 
     * @hidden(Linux)
     * @type callback
     * @region 引擎管理
     * @author hanchenchen.c
     * @brief SDK 当前网络连接类型改变回调。当 SDK 的当前网络连接类型发生改变时回调该事件。
     * @param [in] type  <br>
     *        SDK 当前的网络连接类型，详见：NetworkType{@link #NetworkType} 。
     */
    virtual void onNetworkTypeChanged(bytertc::NetworkType type) {
    }
    /** 
     * @type callback
     * @region 音视频回退
     * @author panjian.fishing
     * @brief 音视频流因网络环境变化等原因发生回退，或从回退中恢复时，触发该回调。
     * @param [in] event 音视频流发生变化的信息。参看 RemoteStreamSwitch{@link #RemoteStreamSwitch}。
     */
    virtual void onSimulcastSubscribeFallback(const RemoteStreamSwitch& event) {
        (void)event;
    }
    /** 
     * @type callback
     * @region 音视频回退
     * @author panjian.fishing
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
     * @deprecated since 337, using onAudioDeviceStateChanged and onVideoDeviceStateChanged instead.
     * @type callback
     * @region 引擎管理
     * @author zhangzhenyu.samuel
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
     * @author zhangzhenyu.samuel
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
     * @author zhangzhenyu.samuel
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
     * @deprecated since 337, using onAudioDeviceWarning and onVideoDeviceWarning instead.
     * @type callback
     * @region 引擎管理
     * @author dixing
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
     * @author dixing
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
     * @author dixing
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
     * @author chenweiming.push
     * @brief 周期性（2s）地发出回调，报告当前cpu与memory使用率
     * @param [in] stats 返回包含当前系统状态信息的结构体，详见 SysStats{@link #SysStats}
     */
    virtual void onSysStats(const bytertc::SysStats& stats) {
    }

    /** 
     * @type callback
     * @region 引擎管理
     * @author shenpengliang
     * @brief 创建房间失败回调。
     * @param room_id 房间 ID。
     * @param error_code 创建房间错误码，具体原因参看 ErrorCode{@link #ErrorCode}。
     */
    virtual void onCreateRoomStateChanged(const char* room_id, int error_code) {
        (void)room_id;
        (void)error_code;
    }

    /** 
     * @type callback
     * @region 代理回调
     * @author qipengxiang
     * @brief HTTP 代理连接状态改变时，收到该回调。
     * @param [in] state 当前 HTTP 代理连接状态，详见 HttpProxyState{@link #HttpProxyState}
     */
    virtual void onHttpProxyState(int state) {
    }

    /** 
     * @type callback
     * @region 代理回调
     * @author qipengxiang
     * @brief HTTPS 代理连接状态改变时，收到该回调。
     * @param  [out] state 当前 HTTPS 代理连接状态，详见 HttpProxyState{@link #HttpProxyState}
     */
    virtual void onHttpsProxyState(int state) {
    }

    /** 
     * @type callback
     * @region 代理回调
     * @author qipengxiang
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
     * @hidden(Linux)
     * @type callback
     * @region 本地录制
     * @author wunailiang
     * @brief 获取本地录制状态回调。  <br>
     *        该回调由 startFileRecording{@link #IRTCVideo#startFileRecording} 或 stopFileRecording{@link #IRTCVideo#stopFileRecording} 触发。
     * @param [out] type 录制流的流属性，参看 StreamIndex{@link #StreamIndex}
     * @param [out] state 录制状态，参看 RecordingState{@link #RecordingState}
     * @param [out] error_code 录制错误码，参看 RecordingErrorCode{@link #RecordingErrorCode}
     * @param [out] info 录制文件的详细信息，参看 RecordingInfo{@link #RecordingInfo}
     */
    virtual void onRecordingStateUpdate(
            StreamIndex type, RecordingState state, RecordingErrorCode error_code, RecordingInfo info) {
    }

    /** 
     * @hidden(Linux)
     * @type callback
     * @region 本地录制
     * @author wunailiang
     * @brief 本地录制进度回调。  <br>
     *        该回调由 startFileRecording{@link #IRTCVideo#startFileRecording} 触发，录制状态正常时，系统每秒钟都会通过该回调提示录制进度。
     * @param [out] type 录制流的流属性，参看 StreamIndex{@link #StreamIndex}
     * @param [out] process 录制进度，参看 RecordingProgress{@link #RecordingProgress}
     * @param [out] info 录制文件的详细信息，参看 RecordingInfo{@link #RecordingInfo}
     */
    virtual void onRecordingProgressUpdate(StreamIndex type, RecordingProgress process, RecordingInfo info) {
    }

    /** 
     * @type callback
     * @region 实时消息通信
     * @author hanchenchen.c
     * @brief 登录结果回调
     * @param [in] uid  <br>
     *        登录用户 ID
     * @param [in] error_code  <br>
     *        登录结果  <br>
     *        详见 LoginErrorCode{@link #LoginErrorCode}。
     * @param [in] elapsed  <br>
     *        从调用 login{@link #IRTCVideo#login} 接口开始到返回结果所用时长  <br>
     *        单位为 ms。
     * @notes 调用 login{@link #IRTCVideo#login} 后，会收到此回调。
     */
    virtual void onLoginResult(const char* uid, int error_code, int elapsed) {
        (void)uid;
        (void)error_code;
        (void)elapsed;
    }
    /** 
     * @type callback
     * @region 实时消息通信
     * @author hanchenchen.c
     * @brief 登出结果回调
     * @notes 调用 logout{@link #IRTCVideo#logout} 后，会收到此回调。
     */
    virtual void onLogout() {
    }
    /** 
     * @type callback
     * @region 实时消息通信
     * @author hanchenchen.c
     * @brief 设置应用服务器参数的返回结果
     * @param [in] error <br>
     *        设置结果  <br>
     *        + 返回 200，设置成功  <br>
     *        + 返回其他，设置失败，详见 UserMessageSendResult{@link #UserMessageSendResult}
     * @notes 调用 setServerParams{@link #IRTCVideo#setServerParams} 后，会收到此回调。
     */
    virtual void onServerParamsSetResult(int error) {
        (void)error;
    }
    /** 
     * @type callback
     * @region 实时消息通信
     * @author hanchenchen.c
     * @brief 查询对端或本端用户登录状态的返回结果
     * @param [in] peer_user_id  <br>
     *        需要查询的用户 ID
     * @param [in] status  <br>
     *        查询的用户登录状态  <br>
     *        详见 USER_ONLINE_STATUS{@link #USER_ONLINE_STATUS}.
     * @notes 必须先调用 getPeerOnlineStatus{@link #IRTCVideo#getPeerOnlineStatus}，才能收到此回调。
     */
    virtual void onGetPeerOnlineStatus(const char* peer_user_id, int status) {
        (void)peer_user_id;
        (void)status;
    }
    /** 
     * @type callback
     * @region 实时消息通信
     * @author hanchenchen.c
     * @brief 收到房间外用户调用 sendUserMessageOutsideRoom{@link #IRTCVideo#sendUserMessageOutsideRoom} 发来的文本消息时，会收到此回调
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
     * @author hanchenchen.c
     * @brief 收到房间外用户调用 sendUserBinaryMessageOutsideRoom{@link #IRTCVideo#sendUserBinaryMessageOutsideRoom} 发来的二进制消息时，会收到此回调
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
     * @author hanchenchen.c
     * @brief 给房间外指定的用户发送消息的回调
     * @param [in] msgid  <br>
     *        本条消息的 ID  <br>
     *        所有的 P2P 和 P2Server 消息共用一个 ID 序列。
     * @param [in] error  <br>
     *        消息发送结果  <br>
     *        详见 UserMessageSendResult{@link #UserMessageSendResult}。
     * @notes 当调用 sendUserMessageOutsideRoom{@link #IRTCVideo#sendUserMessageOutsideRoom} 或 sendUserBinaryMessageOutsideRoom{@link #IRTCVideo#sendUserBinaryMessageOutsideRoom} 发送消息后，会收到此回调。
     */
    virtual void onUserMessageSendResultOutsideRoom(int64_t msgid, int error) {
        (void)msgid;
        (void)error;
    }

    /** 
     * @type callback
     * @region 实时消息通信
     * @author hanchenchen.c
     * @brief 给应用服务器发送消息的回调。
     * @param [in] msgid 本条消息的 ID。
     *        所有的 P2P 和 P2Server 消息共用一个 ID 序列。
     * @param [in] error 消息发送结果，详见 UserMessageSendResult{@link #UserMessageSendResult}。
     * @param [in] msg 应用服务器收到 HTTP 请求后，在 ACK 中返回的信息。消息不超过 64 KB。
     * @notes 本回调为异步回调。当调用 sendServerMessage{@link #IRTCVideo#sendServerMessage} 或 sendServerBinaryMessage{@link #IRTCVideo#sendServerBinaryMessage} 接口发送消息后，会收到此回调。
     */
    virtual void onServerMessageSendResult(int64_t msgid, int error, const bytertc::ServerACKMsg& msg) {
        (void)msgid;
        (void)error;
        (void)msg;
    }

    /** 
     * @type callback
     * @region 视频管理
     * @author wangjunlin.3182
     * @brief 收到通过 sendSEIMessage{@link #IRTCVideo#sendSEIMessage} 发送的带有 SEI 消息的视频帧时，收到此回调
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
     *        在语音通话场景下，本地用户调用 sendSEIMessage{@link #IRTCVideo#sendSEIMessage} 通过黑帧视频流发送 SEI 数据时，流的发送状态会通过该回调通知远端用户。  <br>
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
      * @author wangjunzheng
      * @brief 远端用户进房后，本地调用 enableAudioPropertiesReport{@link #IRTCVideo#enableAudioPropertiesReport}，根据设置的 interval 值，本地会周期性地收到此回调，了解订阅的远端用户的音频信息。<br>
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
      * @author wangjunzheng
      * @brief 调用 enableAudioPropertiesReport{@link #IRTCVideo#enableAudioPropertiesReport} 后，根据设置的 interval 值，你会周期性地收到此回调，了解本地音频的相关信息。  <br>
      *        本地音频包括使用 RTC SDK 内部机制采集的麦克风音频和屏幕音频。
      * @param [in] audio_properties_infos 本地音频信息，详见 LocalAudioPropertiesInfo{@link #LocalAudioPropertiesInfo} 。
      * @param [in] audio_properties_info_number 数组长度
      */
     virtual void onLocalAudioPropertiesReport(const LocalAudioPropertiesInfo * audio_properties_infos, int audio_properties_info_number) {
        (void)audio_properties_infos;
        (void)audio_properties_info_number;
    }

    /** 
     * @type callback
     * @region 音频设备管理
     * @brief 回调音频设备测试时的播放音量
     * @param [in] volume 音频设备测试播放音量。单位：毫秒。推荐设置为 200 ms。范围：[0,255]<br>
     * @notes 调用 startAudioPlaybackDeviceTest{@link #IAudioDeviceManager#startAudioPlaybackDeviceTest} 或 startAudioDeviceRecordTest{@link #IAudioDeviceManager#startAudioDeviceRecordTest}，开始播放音频文件或录音时，将开启该回调。本回调为周期性回调，回调周期由上述接口的 `interval` 参数指定。
     */
    virtual void onAudioPlaybackDeviceTestVolume(int volume) {
        (void)volume;
    }

    /** 
     * @hidden(Android,iOS)
     * @type callback
     * @region 设备管理
     * @author caocun
     * @brief 音频设备音量改变回调。当通过系统设置，改变音频设备音量或静音状态时，触发本回调。本回调无需手动开启。
     * @param device_type 设备类型，包括麦克风和扬声器，参阅 ByteRTCAudioDeviceType{@link #ByteRTCAudioDeviceType}。
     * @param volume 音量值，[0, 255]。当 volume 变为 0 时，muted 会变为 True。注意：在 Windows 端，当麦克风 volume 变为 0 时，muted 值不变。
     * @param muted 是否禁音状态。扬声器被设置为禁音时，muted 为 True，但 volume 保持不变。
     */
    virtual void onAudioDeviceVolumeChanged(bytertc::RTCAudioDeviceType device_type, int volume, bool muted) {
        (void)device_type;
        (void)volume;
        (void)muted;
    }

    /** 
     * @type callback
     * @region 音频事件回调
     * @author wangjunzheng
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
     * @author dixing
     * @brief 房间内的用户调用 startAudioCapture{@link #IRTCVideo#startAudioCapture} 开启音频采集时，房间内其他用户会收到此回调。
     * @param [in] room_id 开启音频采集的远端用户所在的房间 ID
     * @param [in] user_id 开启音频采集的远端用户 ID
     */
    virtual void onUserStartAudioCapture(const char* room_id, const char* user_id) {
        (void)user_id;
    }

    /** 
     * @type callback
     * @region 音频事件回调
     * @author dixing
     * @brief 房间内的用户调用 stopAudioCapture{@link #IRTCVideo#stopAudioCapture} 关闭音频采集时，房间内其他用户会收到此回调。
     * @param [in] room_id 关闭音频采集的远端用户所在的房间 ID
     * @param [in] user_id 关闭音频采集的远端用户 ID
     */
    virtual void onUserStopAudioCapture(const char* room_id, const char* user_id) {
        (void)user_id;
    }

    /** 
     * @type callback
     * @region 音频管理
     * @author zhangcaining
     * @brief 调用 enableAudioPropertiesReport{@link #IRTCVideo#enableAudioPropertiesReport} 后，根据设置的 `config.interval`，你会周期性地收到此回调，获取房间内的最活跃用户信息。
     * @param [in] room_id 房间 ID
     * @param [in] uid 最活跃用户（ActiveSpeaker）的用户 ID
     */
    virtual void onActiveSpeaker(const char* room_id, const char* uid) {
        (void)room_id;
        (void)uid;
    }

    /** 
     * @type api
     * @region 音频管理
     * @author wangjunzheng
     * @brief 音频流同步信息回调。可以通过此回调，在远端用户调用 sendStreamSyncInfo{@link #IRTCVideo#sendStreamSyncInfo} 发送音频流同步消息后，收到远端发送的音频流同步信息。  <br>
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
     * @author hanchenchen.c
     * @brief 通话前网络探测结果。  <br>
     *        成功调用 startNetworkDetection{@link #IRTCVideo#startNetworkDetection} 接口开始探测后，会在 3s 内首次收到该回调，之后每 2s 收到一次该回调。
     * @param [in] type 探测网络类型为上行/下行  <br>
     * @param [in] quality 探测网络的质量，参看 NetworkQuality{@link #NetworkQuality}。 <br>
     * @param [in] rtt 探测网络的 RTT，单位：ms  <br>
     * @param [in] lost_rate 探测网络的丢包率  <br>
     * @param [in] bitrate 探测网络的带宽，单位：kbps  <br>
     * @param [in] jitter 探测网络的抖动,单位：ms  <br>
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
     * @author hanchenchen.c
     * @brief 通话前网络探测结束
     *        以下情况将停止探测并收到本一次本回调：<br>
     *        1. 当调用 stopNetworkDetection{@link #IRTCVideo#stopNetworkDetection} 接口停止探测后，会收到一次该回调；
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
     * @author qipengxiang
     * @type callback
     * @brief 订阅公共流的结果回调<br>
     *        通过 startPlayPublicStream{@link #IRTCVideo#startPlayPublicStream} 订阅公共流后，可以通过本回调获取订阅结果。
     * @param [in] public_stream_id 公共流的 ID
     * @param [in] errorCode 公共流订阅结果状态码。详见 PublicStreamErrorCode{@link #PublicStreamErrorCode}。
     */
    virtual void onPlayPublicStreamResult(const char* public_stream_id, int errorCode) {
        (void)public_stream_id;
        (void)errorCode;
    }
    /** 
     * @author qipengxiang
     * @type callback
     * @brief 回调公共流中包含的 SEI 信息<br>
     *        通过 startPlayPublicStream{@link #IRTCVideo#startPlayPublicStream} 开始播放公共流后，可以通过本回调获取公共流中包含的 SEI 信息。
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
     * @author qipengxiang
     * @type callback
     * @brief 公共流的首帧视频解码成功<br>
     *        关于订阅公共流，详见 startPlayPublicStream{@link #IRTCVideo#startPlayPublicStream}。
     * @param [in] public_stream_id 公共流 ID
     * @param [in] info 视频帧信息。详见 VideoFrameInfo{@link #VideoFrameInfo}。
     */
    virtual void onFirstPublicStreamVideoFrameDecoded(const char* public_stream_id, const VideoFrameInfo& info) {
        (void)public_stream_id;
    }
    /** 
     * @type callback
     * @region 视频事件回调
     * @author zhushufan.ref
     * @brief 房间内的可见用户调用 startVideoCapture{@link #IRTCVideo#startVideoCapture} 开启内部视频采集时，房间内其他用户会收到此回调。
     * @param [in] room_id 开启视频采集的远端用户所在的房间 ID
     * @param [in] user_id 开启视频采集的远端用户 ID
     */
    virtual void onUserStartVideoCapture(const char* room_id, const char* user_id) {
        (void)user_id;
    }
    /** 
     * @type callback
     * @region 视频事件回调
     * @author zhushufan.ref
     * @brief 房间内的可见用户调用 stopVideoCapture{@link #IRTCVideo#stopVideoCapture} 关闭内部视频采集时，房间内其他用户会收到此回调。
     * @param [in] room_id ID of the room where the remote video stream stops being published.
     * @param [in] user_id 关闭视频采集的远端用户 ID
     */
    virtual void onUserStopVideoCapture(const char* room_id, const char* user_id) {
        (void)user_id;
    }
    /** 
     * @type callback
     * @region 视频管理
     * @author zhushufan.ref
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
     * @author zhushufan.ref
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
     * @brief RTC SDK 在本地完成第一帧视频帧或屏幕视频帧采集时，收到此回调。
     * @param [in] index 流属性。参看 StreamIndex{@link #StreamIndex}。
     * @param [in] info 视频信息。参看 VideoFrameInfo{@link #VideoFrameInfo}。
     * @notes 对于采集到的本地视频帧，你可以调用 setLocalVideoCanvas{@link #IRTCVideo#setLocalVideoCanvas} 或 setLocalVideoSink{@link #IRTCVideo#setLocalVideoSink} 在本地渲染。
     */
    virtual void onFirstLocalVideoFrameCaptured(StreamIndex index, VideoFrameInfo info) {
        (void)index;
        (void)info;
    }
    /** 
     * @hidden
     * @deprecated since 336.1, use onUserPublishStream, onUserPublishScreen, onUserUnPublishStream and onUserUnPublishScreen instead.
     * @type callback
     * @region 媒体流管理
     * @author shenpengliang
     * @brief 房间内用户暂停/恢复发送音频流时，房间内其他用户会收到此回调。参看 muteLocalAudio{@link #IRTCVideo#muteLocalAudio}。
     * @param [in] user_id 改变本地音频发送状态的用户 ID
     * @param [in] mute_state 发送状态，参看 MuteState{@link #MuteState}
     */
    virtual void onUserMuteAudio(const char* room_id, const char* user_id, MuteState mute_state) {
        (void)user_id;
        (void)mute_state;
    }
    /** 
     * @type callback
     * @region 音频事件回调
     * @author wangjunzheng
     * @brief 接收到来自远端某音频流的第一帧时，收到该回调。
     * @param [in] key 远端音频流信息, 详见 RemoteStreamKey{@link #RemoteStreamKey}
     * @notes 用户刚收到房间内每一路音频流时，都会收到该回调。
     */
    virtual void onFirstRemoteAudioFrame(const RemoteStreamKey& key) {
        (void)key;
    }
    /** 
     * @hidden
     * @deprecated since 336.1, use onUserPublishStream, onUserPublishScreen, onUserUnPublishStream and onUserUnPublishScreen instead.
     * @type callback
     * @region 媒体流管理
     * @author shenpengliang
     * @brief 房间内用户暂停/恢复发送视频流时，房间内其他用户会收到此回调。参看 muteLocalVideo{@link #IRTCVideo#muteLocalVideo}。
     * @param [in] uid 暂停/恢复发送视频流的用户 ID。
     * @param [in] mute 视频流的发送状态。参看 MuteState{@link #MuteState}。
     */
    virtual void onUserMuteVideo(const char* room_id, const char* uid, MuteState mute) {
        (void)uid;
        (void)mute;
    }
    /** 
     * @type callback
     * @region 音频事件回调
     * @author wangjunzheng
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
     * @type callback
     * @region 房间管理
     * @author shenpengliang
     * @brief 音频首帧发送状态改变回调
     * @param [in] room_id 音频发布用户所在的房间 ID
     * @param [in] user 本地用户信息，详见 RtcUser{@link #RtcUser}
     * @param [in] state 首帧发送状态，详见 FirstFrameSendState{@link #FirstFrameSendState}
     */
    virtual void onAudioFrameSendStateChanged(const char* room_id, const RtcUser& user, FirstFrameSendState state) {
        (void)user;
        (void)state;
    }
    /** 
     * @type callback
     * @region 房间管理
     * @author shenpengliang
     * @brief 视频首帧发送状态改变回调
     * @param [in] room_id 视频发布用户所在的房间 ID
     * @param [in] user 本地用户信息，详见 RtcUser{@link #RtcUser}
     * @param [in] state 首帧发送状态，详见 FirstFrameSendState{@link #FirstFrameSendState}
     */
    virtual void onVideoFrameSendStateChanged(const char* room_id, const RtcUser& user, FirstFrameSendState state) {
        (void)user;
        (void)state;
    }
    /** 
     * @type callback
     * @region 视频管理
     * @author zhushufan.ref
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
     * @author zhushufan.ref
     * @brief SDK 接收并解码远端视频流首帧后，收到此回调。
     * @param [in] key 远端流信息。参看 RemoteStreamKey{@link #RemoteStreamKey}。
     * @param [in] info 视频帧信息。参看 VideoFrameInfo{@link #VideoFrameInfo}。
     */
    virtual void onFirstRemoteVideoFrameDecoded(const RemoteStreamKey key, const VideoFrameInfo& info) {
        (void)key;
        (void)info;
    }
    /** 
     * @type callback
     * @region 房间管理
     * @author shenpengliang
     * @brief 屏幕共享流视频首帧发送状态改变回调
     * @param [in] room_id 流的发布房间的 ID
     * @param [in] user 本地用户信息，详见 RtcUser{@link #RtcUser}
     * @param [in] state 首帧发送状态，详见 FirstFrameSendState{@link #FirstFrameSendState}
     */
    virtual void onScreenVideoFrameSendStateChanged(const char* room_id, const RtcUser& user, FirstFrameSendState state) {
        (void)user;
        (void)state;
    }
    /** 
     * @type callback
     * @region 房间管理
     * @author shenpengliang
     * @brief 音频首帧播放状态改变回调
     * @param [in] room_id 首帧播放状态发生改变的流所在的房间 ID
     * @param [in] user 远端用户信息，详见 RtcUser{@link #RtcUser}
     * @param [in] state 首帧播放状态，详见 FirstFramePlayState{@link #FirstFramePlayState}
     */
    virtual void onAudioFramePlayStateChanged(const char* room_id, const RtcUser& user, FirstFramePlayState state) {
        (void)user;
        (void)state;
    }
    /** 
     * @type callback
     * @region 房间管理
     * @author shenpengliang
     * @brief 视频首帧播放状态改变回调
     * @param [in] room_id 首帧播放状态发生改变的流所在的房间 ID
     * @param [in] user 远端用户信息，详见 RtcUser{@link #RtcUser}
     * @param [in] state 首帧播放状态，详见 FirstFramePlayState{@link #FirstFramePlayState}
     */
    virtual void onVideoFramePlayStateChanged(const char* room_id, const RtcUser& user, FirstFramePlayState state) {
        (void)user;
        (void)state;
    }
    /** 
     * @type callback
     * @region 房间管理
     * @author shenpengliang
     * @brief 屏幕共享流视频首帧播放状态改变回调
     * @param [in] room_id 首帧播放状态发生改变的流所在的房间 ID
     * @param [in] user 远端用户信息，详见 RtcUser{@link #RtcUser}
     * @param [in] state 首帧播放状态，详见 FirstFramePlayState{@link #FirstFramePlayState}
     */
    virtual void onScreenVideoFramePlayStateChanged(const char* room_id, const RtcUser& user, FirstFramePlayState state) {
        (void)user;
        (void)state;
    }

    /** 
     * @type callback
     * @region 音频事件回调
     * @author wangjunzheng
     * @brief 发布音频流时，采集到第一帧音频帧，收到该回调。
     * @param [in] index 音频流属性, 参看 StreamIndex{@link #StreamIndex}
     * @notes 如果发布音频流时，未开启本地音频采集，SDK 会推送静音帧，也会收到此回调。
     */
    virtual void onFirstLocalAudioFrame(StreamIndex index) {
        (void)index;
    }
    /** 
     * @author qipengxiang
     * @type callback
     * @brief 公共流发布结果回调。<br>
     *        调用 startPushPublicStream{@link #IRTCVideo#startPushPublicStream} 接口发布公共流后，启动结果通过此回调方法通知用户。
     * @param [in] room_id 公共流的发布房间的 ID
     * @param [in] public_streamid 公共流 ID
     * @param [in] errorCode 公共流发布结果状态码。<br>
     *             `200`: 发布成功<br>
     *             `1191`: 推流参数存在异常 <br>
     *             `1192`: 当前状态异常，通常为无法发起任务<br>
     *             `1193`: 服务端错误，不可恢复<br>
     *             `1195`: 服务端调用发布接口返回失败<br>
     *             `1196`: 超时无响应。推流请求发送后 10s 没有收到服务端的结果回调。客户端将每隔 10s 重试，3 次重试失败后停止。
     */
    virtual void onPushPublicStreamResult(const char* room_id, const char* public_streamid, int errorCode) {
        (void)room_id;
        (void)public_streamid;
        (void)errorCode;
    }

    /** 
     * @author qipengxiang
     * @type callback
     * @brief 公共流的音频首帧解码成功<br>
     *        关于订阅公共流，详见 startPlayPublicStream{@link #IRTCVideo#startPlayPublicStream}。
     * @param [in] public_stream_id 公共流 ID
     */
    virtual void onFirstPublicStreamAudioFrame(const char* public_stream_id) {
        (void)public_stream_id;
    }
    /** 
     * @author daining.nemo
     * @type callback
     * @brief 调用 startCloudProxy{@link #IRTCVideo#startCloudProxy} 开启云代理，SDK 首次成功连接云代理服务器时，回调此事件。
     * @param [in] interval 从开启云代理到连接成功经过的时间，单位为 ms
     */
    virtual void onCloudProxyConnected(int interval) {
        (void)interval;
    }
    /** 
     * @hidden(Linux)
     * @type callback
     * @region 网络管理
     * @author qipengxiang
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

};

} // namespace bytertc

#endif // BYTE_RTC_LITE_EVENT_HANDLER_H__
