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
     * @type callback
     * @region 混音
     * @author wangjunzheng
     * @brief 本地音乐文件播放已结束回调。
     *        当调用 StartAudioMixing{@link #IRtcEngineLite#StartAudioMixing} 启动的混音文件播放结束后，会触发该回调。
     */
    virtual void OnAudioMixingFinished() {
    }

    /**
     * @type callback
     * @region 混音
     * @author wangjunzheng
     * @brief  音频混音文件播放状态改变时回调。此回调会被触发的时机汇总如下：  <br>
     *       + 当调用 StartAudioMixing{@link #IRtcEngineLite#StartAudioMixing} 方法成功后， 会触发该 state 值为 kAudioMixingStatePlaying 回调； 否则触发 state 值为 kAudioMixingStateFailed 的回调。  <br>
     *       + 当调用 ResumeAudioMixing{@link #ResumeAudioMixing} 方法恢复播放成功后， 会触发该 state 值为 kAudioMixingStatePlaying 回调； 否则触发 state 值为 kAudioMixingStateFailed 的回调。  <br>
     *       + 当调用 PauseAudioMixing{@link #PauseAudioMixing} 方法暂停播放后， 会触发该 state 值为 kAudioMixingStatePlaying 回调； 否则触发 state 值为 kAudioMixingStateFailed 的回调。  <br>
     *       + 当调用 StopAudioMixing{@link #StopAudioMixing} 方法暂停止播放后， 会触发该 state 值为 kAudioMixingStatePlaying 回调； 否则触发 state 值为 kAudioMixingStateFailed 的回调。  <br>
     * @param [in] state 混音状态。其混音状态可参考： AudioMixingState{@link #AudioMixingState}
     * @param [in] error 错误码。  <br>
     *        + kAudioMixingErrorOk        ： state 值为 kAudioMixingStatePlaying/kAudioMixingStatePaused/kAudioMixingStateStoped 返回该错误码。  <br>
     *        + kAudioMixingErrorCanNotOpen： state 值为 kAudioMixingStateFailed 返回该错误码。  <br>
     */
    virtual void OnAudioMixingStateChanged(bytertc::AudioMixingState state, bytertc::AudioMixingError error) {
    }

    /**
     * @type callback
     * @region 混音
     * @author wangjunzheng
     * @brief 本地音效文件播放已结束回调。
     *        当调用 PlayEffect{@link #PlayEffect}  方法开始播放指定音效文件， 音效文件播放结束后， 应用会收到该回调。
     * @param [in] sound_id
     *        音效ID，应用调用者维护，请保证唯一性。
     */
    virtual void OnAudioEffectFinished(int sound_id) {
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
    virtual void OnLogReport(const char* log_type, const char* log_content) {
        (void)log_type;
        (void)log_content;
    }

    /**
     * @hidden(macOS,Windows)    
     * @type callback
     * @region 音频事件回调
     * @author wangjunzheng     
     * @brief 音频播放设备变化时回调该事件。
     * @param [in] device 变化后的音频播放设备，参看 AudioPlaybackDevice{@link #AudioPlaybackDevice}。  <br>
     */
    virtual void OnAudioPlaybackDeviceChanged(AudioPlaybackDevice device) {
        (void)device;
    };

    /**
     * @type callback
     * @region 引擎管理
     * @author hanchenchen.c
     * @brief SDK 与信令服务器连接状态改变回调。连接状态改变时触发。
     * @param [in] state 当前 SDK 与信令服务器的连接状态，详见 ConnectionState{@link #ConnectionState} 
     */
    virtual void OnConnectionStateChanged(bytertc::ConnectionState state) {
    }

    /**
     * @type callback
     * @region 引擎管理
     * @author hanchenchen.c
     * @brief SDK 当前网络连接类型改变回调。当 SDK 的当前网络连接类型发生改变时回调该事件。
     * @param [in] type  <br>
     *        SDK 当前的网络连接类型，详见：NetworkType{@link #NetworkType} 。
     */
    virtual void OnNetworkTypeChanged(bytertc::NetworkType type) {
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
     * @author panjian.fishing
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
     * @author chenweiming.push
     * @brief 周期性地发出回调，报告当前cpu与memory使用率
     * @param  [out] stats 返回包含当前系统状态信息的结构体，详见 SysStats{@link #SysStats}
     */
    virtual void OnSysStats(const bytertc::SysStats& stats) {
    }

    /**
     * @type callback
     * @region 代理回调
     * @author qipengxiang
     * @brief HTTP 代理连接状态改变时，收到该回调。
     * @param  [out] state 当前 HTTP 代理连接状态，详见 HttpProxyState{@link #HttpProxyState}
     */     
        virtual void OnHttpProxyState(int state) {
    }

    /**
     * @type callback
     * @region 代理回调
     * @author qipengxiang
     * @brief HTTPS 代理连接状态改变时，收到该回调。
     * @param  [out] state 当前 HTTPS 代理连接状态，详见 HttpProxyState{@link #HttpProxyState}
     */        
    virtual void OnHttpsProxyState(int state) {
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
    virtual void OnSocks5ProxyState(int state,
        const char* cmd,
        const char* proxy_address,
        const char* local_address,
        const char* remote_address) {
    }

};

} // namespace bytertc

#endif // BYTE_RTC_LITE_EVENT_HANDLER_H__
