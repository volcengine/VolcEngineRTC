/*
 * Copyright (c) 2020 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC Event Handler Lite
*/

#pragma once

#include "rtc/bytertc_defines.h"
#include "bytertc_video_event_handler.h"
#include "rtc/bytertc_video_defines_ex.h"
namespace bytertc {
/**
 * @locale zh
 * @type callback
 * @brief IRTCVideoEventHandlerEx Class<br>
 * 注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。
 */
class IRTCVideoEventHandlerEx {
public:
    /**
     * @hidden
     */
    virtual ~IRTCVideoEventHandlerEx() {
    }
    /**
     * @locale zh
     * @type callback
     * @brief 本地音频首帧发送状态发生改变时，收到此回调。
     * @param stream_key 参看 StreamKey{@link #StreamKey}。
     * @param meta_data 发送 ID
     * @param state 首帧发送状态，详见 FirstFrameSendState{@link #FirstFrameSendState}
     */
    virtual void onAudioFrameSendStateChanged(
            const StreamKey& stream_key, const char* meta_data, FirstFrameSendState state) {
    }
    /**
     * @locale zh
     * @type callback
     * @brief 本地视频首帧发送状态发生改变时，收到此回调。
     * @param stream_key 参看 StreamKey{@link #StreamKey}。
     * @param meta_data 发送 ID
     * @param state 首帧发送状态，详见 FirstFrameSendState{@link #FirstFrameSendState}
     */
    virtual void onVideoFrameSendStateChanged(
            const StreamKey& stream_key, const char* meta_data, FirstFrameSendState state) {
    }
    /**
     * @locale zh
     * @type callback
     * @brief 音频首帧播放状态发生改变时，收到此回调。
     * @param stream_key 参看 StreamKey{@link #StreamKey}。
     * @param meta_data 接收 ID
     * @param state 首帧播放状态，详见 FirstFramePlayState{@link #FirstFramePlayState}
     */
    virtual void onAudioFramePlayStateChanged(
            const StreamKey& stream_key, const char* meta_data, FirstFramePlayState state) {
    }
    /**
     * @locale zh
     * @type callback
     * @brief 视频首帧播放状态发生改变时，收到此回调。
     * @param stream_key 参看 StreamKey{@link #StreamKey}。
     * @param meta_data 接收 ID
     * @param state 首帧播放状态，详见 FirstFramePlayState{@link #FirstFramePlayState}
     */
    virtual void onVideoFramePlayStateChanged(
            const StreamKey& stream_key,  const char* meta_data, FirstFramePlayState state) {
    }
    /**
     * @locale zh
     * @type callback
     * @region 数据统计
     * @brief 反映通话中本地设备发送音/视频流的统计信息以及网络状况的回调，每 2s 触发一次。
     * @param stream_index 流索引，参看 StreamIndex{@link #StreamIndex}。
     * @param stats 详见 LocalStreamStats{@link #LocalStreamStats}
     */
    virtual void onLocalStreamStats(StreamIndex index, const LocalStreamStats& stats) {
    }
    /**
     * @locale zh
     * @type callback
     * @region 数据统计
     * @brief 通话中本地设备接收订阅的远端音/视频流的统计信息以及网络状况，每 2s 触发一次。
     * @param stream_index 流索引，参看 StreamIndex{@link #StreamIndex}。
     * @param stats 当前 RtcEngine 统计数据，详见 RemoteStreamStats{@link #RemoteStreamStats}
     */
    virtual void onRemoteStreamStats(const StreamKey& stream_key, const RemoteStreamStats& stats) {
    }
    /**
     * @locale zh
     * @type callback
     * @region 音视频回退
     * @brief 音视频流因网络环境变化等原因发生回退，或从回退中恢复时，触发该回调。
     * @param stream_index 流索引，参看 StreamIndex{@link #StreamIndex}。
     * @param event 音视频流发生变化的信息。参看 RemoteStreamSwitch{@link #RemoteStreamSwitch}。
     */
    virtual void onSimulcastSubscribeFallback(
            const StreamKey& stream_key, const RemoteStreamSwitch& event) {
    }
    /**
     * @locale zh
     * @type callback
     * @region 音视频回退
     * @brief 本地未通过 setPublishFallbackOption{@link #IRTCVideo#setPublishFallbackOption} 开启发布性能回退，检测到设备性能不足时，收到此回调。<br>
     *        本地通过 setPublishFallbackOption{@link #IRTCVideo#setPublishFallbackOption} 开启发布性能回退，因设备性能/网络原因，造成发布性能回退/恢复时，收到此回调。
     * @param stream_index 流索引，参看 StreamIndex{@link #StreamIndex}。
     * @param mode 指示本地是否开启发布回退功能。参看 PerformanceAlarmMode{@link #PerformanceAlarmMode}  <br>
     *                  + 当发布端未开启发布性能回退时，mode 值为 kPerformanceAlarmModeNormal。  <br>
     *                  + 当发布端开启发布性能回退时，mode 值为 kPerformanceAlarmModeSimulcast。
     * @param reason 告警原因，参看 PerformanceAlarmReason{@link #PerformanceAlarmReason}
     * @param data 性能回退相关数据，详见 SourceWantedData{@link #SourceWantedData}。
     */
    virtual void onPerformanceAlarms(StreamIndex stream_index, bytertc::PerformanceAlarmMode mode,
            bytertc::PerformanceAlarmReason reason, const bytertc::SourceWantedData& data) {
    }
};
} /* namespace bytertc */