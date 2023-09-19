
/*
 * Copyright 2021 @bytedance
 *  Created on: june 20, 2021
 */

#pragma once

#include "bytertc_defines.h"
#include "bytertc_transcoder_define.h"

namespace bytertc {
/** 
 * @type callback
 * @region 转推直播
 * @brief 合流推流 Observer
 * 注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。
 */
class IMixedStreamObserver {
public:
    /** 
     * @type callback
     * @region 转推直播
     * @brief 是否具有推流能力。  <br>
     *       + false：不具备推流能力（默认值）  <br>
     *       + true：具备推流能力
     * @notes  <br>
     *         + 如果需要开启端云一体转推直播功能，你必须确保你的 App 包含 librtmp，具有推流能力。此时，设置该回调为
     * true。
     */
    virtual bool isSupportClientPushStream() = 0;
    /** 
     * @hidden(Linux) not available
     * @type callback
     * @region 转推直播
     * @brief 转推直播状态回调
     * @param [in] event 转推直播任务状态，参看 StreamMixingEvent{@link #StreamMixingEvent}
     * @param [in] task_id 转推直播任务 ID
     * @param [in] error 转推直播错误码，参看 StreamMixingErrorCode{@link #StreamMixingErrorCode}。
     * @param [in] mix_type 转推直播类型，参看 MixedStreamType{@link #MixedStreamType}
     */
    virtual void onMixingEvent(
            StreamMixingEvent event, const char* task_id, StreamMixingErrorCode error, MixedStreamType mix_type) = 0;

    /** 
     * @type callback
     * @region 转推直播
     * @brief 合流视频回调，运行在视频回调线程
     * @param [in] task_id 合流任务 ID
     * @param [in] video_frame 视频帧，参看 IVideoFrame{@link #IVideoFrame}。
     * @notes 收到该回调的周期与视频的帧间隔一致。
     */
    virtual void onMixingVideoFrame(const char* task_id, IVideoFrame* video_frame) = 0;

    /** 
     * @type callback
     * @region 转推直播
     * @brief 合流音频回调，运行在音频回调线程
     * @param [in] task_id 转推直播任务 ID
     * @param [in] audio_frame 音频帧，参看 IAudioFrame{@link #IAudioFrame}。
     * @notes 收到该回调的周期为每 10 毫秒一次，并且每次的音频数据量为 10 毫秒数据量。
     */
    virtual void onMixingAudioFrame(const char* task_id, IAudioFrame* audio_frame) = 0;

    /** 
     * @type callback
     * @region 转推直播
     * @brief 视频 SEI 帧回调，运行在视频回调线程
     * @param [in] task_id 转推直播任务 ID
     * @param [in] data_frame SEI 数据
     */
    virtual void onMixingDataFrame(const char* task_id, IDataFrame* data_frame) = 0;

    /** 
     * @hidden for internal use only
     * @type callback
     * @region 转推直播
     * @brief 同步视频帧回调。
     * @param [in] task_id 转推直播任务 ID。
     * @param [in] uids 同步视频帧对应的 uid 数组。
     * @param [in] video_frames 同步视频帧数组，与 uids 对应。
     * @param [in] data_frame SEI 数据。
     * @param [in] count 数组的长度。
     */
    virtual void onCacheSyncVideoFrames(const char* task_id, const char* uids[], IVideoFrame* video_frames[],
            IDataFrame* data_frame[], int count) = 0;

    /** 
     * @hidden constructor/destructor
     * @brief 析构函数
     */
    virtual ~IMixedStreamObserver() = default;
};

/** 
 * @deprecated since 3.52, use IMixedStreamObserver{@link #IMixedStreamObserver} instead.
 * @type callback
 * @region 转推直播
 * @brief 推流 Observer
 * 注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。
 */
class ITranscoderObserver {
public:
    /** 
     * @type callback
     * @region 转推直播
     * @brief 是否具有推流能力。  <br>
     *       + false：不具备推流能力（默认值）  <br>
     *       + true：具备推流能力
     * @notes 如果需要开启端云一体转推直播功能，你必须确保你的 App 包含 librtmp，具有推流能力。此时，设置该回调为 true。
     */
    virtual bool isSupportClientPushStream() {
        return false;
    }
    /** 
     * @hidden(Linux) not available
     * @type callback
     * @region 转推直播
     * @brief 转推直播状态回调
     * @param [in] event 转推直播任务状态，参看 StreamMixingEvent{@link #StreamMixingEvent}
     * @param [in] task_id 转推直播任务 ID
     * @param [in] error 转推直播错误码，参看 TransCodingError{@link #TransCodingError}。
     * @param [in] mix_type 转推直播类型，参看 StreamMixingType{@link #StreamMixingType}
     */
    virtual void onStreamMixingEvent(
            StreamMixingEvent event, const char* task_id, StreamMixingErrorCode error, StreamMixingType mix_type) = 0;

    /** 
     * @type callback
     * @region 转推直播
     * @brief 合流视频回调，运行在视频回调线程
     * @param [in] task_id 合流任务 ID
     * @param [in] video_frame 视频帧，参看 IVideoFrame{@link #IVideoFrame}。
     * @notes 收到该回调的周期与视频的帧间隔一致。
     */
    virtual void onMixingVideoFrame(const char* task_id, IVideoFrame* video_frame) = 0;

    /** 
     * @type callback
     * @region 转推直播
     * @brief 合流音频回调，运行在音频回调线程
     * @param [in] task_id 转推直播任务 ID
     * @param [in] audio_frame 音频帧，参看 IAudioFrame{@link #IAudioFrame}。
     * @notes 收到该回调的周期为每 10 毫秒一次，并且每次的音频数据量为 10 毫秒数据量。
     */
    virtual void onMixingAudioFrame(const char* task_id, IAudioFrame* audio_frame) = 0;

    /** 
     * @type callback
     * @region 转推直播
     * @brief 视频 SEI 帧回调，运行在视频回调线程
     * @param [in] task_id 转推直播任务 ID
     * @param [in] data_frame SEI 数据
     */
    virtual void onMixingDataFrame(const char* task_id, IDataFrame* data_frame) = 0;
    /** 
     * @hidden for internal use only
     * @type callback
     * @valid since 3.50
     * @brief 同步视频帧回调。仅在通过 setSyncControlparam{@link #ITranscoderParam#setSyncControlparam} 设置启用单通同步模式，且其中 `sync_client_video_need_mix=False` 时收到此回调。
     * @param [in] video_frames 同步视频帧数组，与 uids 对应。参看 IVideoFrame{@link #IVideoFrame}。
     * @param [in] data_frame SEI 数据。参看 IDataFrame{@link #IDataFrame}。
     * @param [in] uids 同步视频帧对应的 uid 数组。
     * @param [in] task_id 转推直播任务 ID。
     * @param [in] count `video_frames` 数组长度。
     */
    virtual void onCacheSyncVideoFrames(const char* task_id, const char* uids[], IVideoFrame* video_frames[], IDataFrame* data_frame[], int count) = 0;

    /** 
     * @hidden constructor/destructor
     * @brief 析构函数
     */
    virtual ~ITranscoderObserver() = default;
};
/** 
 * @type callback
 * @region 转推直播
 * @brief 单流转推直播观察者。  <br>
 * 注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。
 */
class IPushSingleStreamToCDNObserver {
public:
     /** 
     * @type callback
     * @region 转推直播
     * @brief 单流转推直播状态回调
     * @param event 任务状态, 参看 SingleStreamPushEvent{@link #SingleStreamPushEvent}
     * @param task_id 任务 ID
     * @param error 错误码，参看 TransCodingError{@link #TransCodingError}
     */
    virtual void onStreamPushEvent(SingleStreamPushEvent event, const char *task_id, int error) = 0;
    /**
     * @hidden constructor/destructor
     */
    virtual ~IPushSingleStreamToCDNObserver() = default;
};

/** 
 * @type callback
 * @brief 缓存同步 Observer
 */
class IChorusCacheSyncObserver {
public:
    /**
     * @hidden constructor/destructor
    */
    virtual ~IChorusCacheSyncObserver() {
    }
    /** 
     * @type callback
     * @brief 调用 startChorusCacheSync{@link #IRTCVideo#startChorusCacheSync}，并设置为 `consumer` 的用户会通过此回调获取经缓存同步后的视频帧。获取频率通过启动同步时的 `fps` 进行设置。
     * @param count `uids` 和 `videoFrames` 的数组长度
     * @param uids 参与合唱缓存同步的 `producer` 和 `retransmitter` 的列表，不包括参与但未发送媒体数据的用户。
     * @param videoFrames 对应 `uids` 的视频帧。参看 IVideoFrame{@link #IVideoFrame}。
     */
    virtual void onSyncedVideoFrames(int count, const char* uids[], bytertc::IVideoFrame* video_frames[]) = 0;
    /** 
     * @type callback
     * @brief 参与合唱缓存同步的 `producer` 和 `retransmitter` 发生变化时，收到此回调。
     * @param count 当前的 `uids` 的长度
     * @param uids  当前的参与者列表
     * @notes 有以下情况可能造成参与者发生变化：
     *        + 用户主动调用 startChorusCacheSync{@link #IRTCVideo#startChorusCacheSync} 或 stopChorusCacheSync{@link #IRTCVideo#stopChorusCacheSync};
     *        + 原本参与缓存同步的用户发生异常退出。
     */
    virtual void onSyncedUsersChanged(int count, const char* uids[]) = 0;
    /** 
     * @type callback
     * @brief 缓存同步事件回调
     * @param event 事件，参看 ChorusCacheSyncEvent{@link #ChorusCacheSyncEvent}。
     * @param error 错误码，参看 ChorusCacheSyncError{@link #ChorusCacheSyncError}。
     */
    virtual void onSyncEvent(ChorusCacheSyncEvent event, ChorusCacheSyncError error) = 0;
};

/** 
 * @type api
 * @brief 创建合流参数实例
 */
BYTERTC_API ITranscoderParam* createTranscoderParam();
/** 
 * @type api
 * @brief 创建合流参数实例(新)
 */
BYTERTC_API IMixedStreamConfig* createMixedStreamConfig();
} /* namespace bytertc */
