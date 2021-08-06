//
//  byte_rtc_engine_lite_event_handler.h
//  bytertc
//
//  Created by valley On 2020/7/2.
//

#pragma once
#include "byte_rtc_engine_defines.h"

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
     *        警告标识码，详见:RTC_WARN_CODE{@link #RTC_WARN_CODE}
     */
    virtual void OnWarning(int warn) {
        (void)warn;
    }

    /**
     * @type callback
     * @region 错误码
     * @brief 当内部发生不可逆转错误时触发该回调
     * @param [in] err
     *        错误标识码，详见:RTC_ERROR_CODE{@link #RTC_ERROR_CODE}
     */
    virtual void OnError(int err) {
        (void)err;
    }
    
   /**
     * @type callback
     * @region 混音
     * @brief 本地音乐文件播放已结束回调。
     *        当调用 StartAudioMixing{@link #IRtcEngineLite#StartAudioMixing} 启动的混音文件播放结束后，会触发该回调。
     */
    virtual void OnAudioMixingFinished() {
    }

    /** 
     * @type callback
     * @region 混音
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
     * @brief 音频路由变化时回调该事件
     * @param [in] routing 新的音频路由，值含义如下：  <br>
     *      + -1  默认音频路由，实际不会出现  <br>
     *      + 0   耳机  <br>
     *      + 1   听筒  <br>
     *      + 3   扬声器  <br>
     *      + 5   蓝牙耳机  <br>
     * @notes  <br>
     *       + 该事件在移动端，包括 Android、iOS，音频路由变化时回调  <br>
     *       + 移动端音频路由设置与音频路由策略详见 SetEnableSpeakerphone{@link #IRtcEngineLite#SetEnableSpeakerphone}  <br>
     */
    virtual void OnAudioRouteChanged(int routing) {
        (void)routing;
    };

    /**
     * @type callback
     * @region 引擎管理
     * @brief SDK 与 RTC 服务器的网络连接状态改变时，会收到此回调。
     * @param [in] state 发生改变后的连接状态，参看 CONNECTION_STATE{@link #CONNECTION_STATE} 。
     */
    virtual void OnConnectionStateChanged(bytertc::CONNECTION_STATE state) {
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
     *  @hidden
     *  @type callback
     *  @region 音视频回退
     *  @brief 当检测到设备性能不足时，回调性能告警。可通过调整 effect 等级等，降低性能消耗。
     *  @param [in] level 告警等级。目前可能无法区分告警的等级。
     *         初期 level 值可以只包含 0 和 1，1 为性能告警，0 则为解除告警。
     *  @param [in] data 性能回退相关数据，详见 SourceWantedData{@link #SourceWantedData}。
     */
    virtual void OnPerformanceAlarms(int level, const bytertc::SourceWantedData& data) {
        (void)level;
        (void)data;
    }
    
    /**
     * @type callback
     * @region 视频管理
     * @brief 当本地视频镜像状态改变时回调该事件。默认回调该事件。
     * @param  [in] mirrored 当前是否开启镜像  <br>
     *       + true: 当前本地视频状态为开启镜像；  <br>
     *       + false: 当前本地视频状态为关闭镜像。  <br>
     */
    virtual void OnMirrorStateChanged(bool mirrored) {
        (void) mirrored;
    }
    
    /**
     * @type callback
     * @region 引擎管理
     * @brief 媒体设备开启、停止状态回调
     * @param [in] device_id
     *        设备 id，目前暂未实现
     * @param [in] device_type  
     *        设备类型，详见MediaDeviceType{@link #MediaDeviceType}
     * @param [in] device_state 
     *        设备状态，详见MediaDeviceState{@link #MediaDeviceState}
     * @notes 当前正在使用中的设备开启成功/失败，停止成功/失败时回调该事件，目前仅支持音频录制设备和播放设备。
     */
    virtual void OnMediaDeviceStateChanged(const char* device_id,
                                           bytertc::MediaDeviceType device_type,
                                           bytertc::MediaDeviceState device_state) {
        (void)device_id;
        (void)device_type;
        (void)device_state;
    }
    
    /**
     * @hidden(iOS,Android)
     * @type callback
     * @region 引擎管理
     * @brief 媒体设备事件回调。
     * @param [in] device_id
     *        设备 id
     * @param [in] device_type
     *        媒体设备类型，详见MediaDeviceType{@link #MediaDeviceType}
     * @param [in] notification_type
     *        媒体设备事件通知类型，详见MediaDeviceNotification{@link #MediaDeviceNotification}
     * @notes 该回调包括了系统内媒体设备的事件通知，如设备的插入、拔出事件通知。
    */
    virtual void OnMediaDeviceNotification(const char* device_id,
                                           bytertc::MediaDeviceType device_type,
                                           bytertc::MediaDeviceNotification notification_type) {
        (void)device_id;
        (void)device_type;
        (void)notification_type;
    }

    /**
     * @type callback
     * @region 引擎管理
     * @brief 周期性地发出回调，报告当前cpu与memory使用率
     * @param  [out] stats 返回包含当前系统状态信息的结构体，详见 SysStats{@link #SysStats}
     */
    virtual void OnSysStats(const bytertc::SysStats& stats) {
    }
};
