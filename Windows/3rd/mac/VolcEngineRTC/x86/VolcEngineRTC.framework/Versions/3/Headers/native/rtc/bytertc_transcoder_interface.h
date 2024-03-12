
/*
 * Copyright 2021 @bytedance
 *  Created on: june 20, 2021
 */

#pragma once

#include "bytertc_defines.h"
#include "bytertc_transcoder_define.h"

namespace bytertc {
/**
 * @locale zh
 * @type callback
 * @region 转推直播
 * @brief 合流推流 Observer<br>
 * 注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。
 */
/**
 * @locale en
 * @type callback
 * @region Push to CDN
 * @brief Register this observer to receive stream mixing related callbacks from the SDK.<br>
 * Note: Callback functions are thrown synchronously in a non-UI thread within the SDK. Therefore, you must not perform any time-consuming operations or direct UI operations within the callback function, as this may cause the app to crash.
 */
class IMixedStreamObserver {
public:
    /**
     * @locale zh
     * @type callback
     * @region 转推直播
     * @brief 是否具有推流能力。  <br>
     *       + false：不具备推流能力（默认值）  <br>
     *       + true：具备推流能力
     * @note  
     *         + 如果需要开启端云一体转推直播功能，你必须确保你的 App 包含 librtmp，具有推流能力。此时，设置该回调为<br>
     * true。
     */
    /**
     * @locale en
     * @type callback
     * @region Push to CDN
     * @brief Whether your App has the ability to push streams to CDN.   <br>
     *        + True: Yes <br>
     *        + False: No (default value)
     * @note   
     *       + If you need to use the function of intelligently pushing streams to CDN, you should ensure that your App<br>
     * contains librtmp and has the ability to push streams out. If so, set the callback to True.
     */
    virtual bool isSupportClientPushStream() = 0;
    /**
     * @locale zh
     * @hidden(Linux) not available
     * @type callback
     * @region 转推直播
     * @brief 转推直播状态回调
     * @param event 转推直播任务状态，参看 StreamMixingEvent{@link #StreamMixingEvent}
     * @param task_id 转推直播任务 ID
     * @param error 转推直播错误码，参看 StreamMixingErrorCode{@link #StreamMixingErrorCode}。
     * @param mix_type 转推直播类型，参看 MixedStreamType{@link #MixedStreamType}
     */
    /**
     * @locale en
     * @hidden(Linux) not available
     * @type callback
     * @region Push to CDN
     * @brief Used for reporting events during pushing streams to CDN
     * @param event Type Stream mixing status, see StreamMixingEvent{@link #StreamMixingEvent}
     * @param task_id Task ID
     * @param error Errors occuring during the pushing process. See StreamMixingErrorCode{@link #StreamMixingErrorCode}
     * @param mix_type Stream mixing and pushing type. See MixedStreamType{@link #MixedStreamType}
     */
    virtual void onMixingEvent(
            StreamMixingEvent event, const char* task_id, StreamMixingErrorCode error, MixedStreamType mix_type) = 0;

    /**
     * @locale zh
     * @type callback
     * @region 转推直播
     * @brief 合流视频回调，运行在视频回调线程
     * @param task_id 合流任务 ID
     * @param video_frame 视频帧，参看 IVideoFrame{@link #IVideoFrame}。
     * @note 收到该回调的周期与视频的帧间隔一致。
     */
    /**
     * @locale en
     * @type callback
     * @region Push to CDN
     * @brief Callback with the video data after stream mixing, running on the video callback thread
     * @param task_id Task ID
     * @param video_frame Video Frame, see IVideoFrame{@link #IVideoFrame}.
     * @note The interval between callbacks is the same with that between video frames.
     */
    virtual void onMixingVideoFrame(const char* task_id, IVideoFrame* video_frame) = 0;

    /**
     * @locale zh
     * @type callback
     * @region 转推直播
     * @brief 合流音频回调，运行在音频回调线程
     * @param task_id 转推直播任务 ID
     * @param audio_frame 音频帧，参看 IAudioFrame{@link #IAudioFrame}。
     * @note 收到该回调的周期为每 10 毫秒一次，并且每次的音频数据量为 10 毫秒数据量。
     */
    /**
     * @locale en
     * @type callback
     * @region Push to CDN
     * @brief Callback with the audio data after stream mixing, running on the audio callback thread
     * @param task_id Task ID.
     * @param audio_frame Audio Frame, see IAudioFrame{@link #IAudioFrame}.
     * @note You will receive the callback every 10 milliseconds. Each callback carries data collected in the last 10<br>
     * milliseconds.
     */
    virtual void onMixingAudioFrame(const char* task_id, IAudioFrame* audio_frame) = 0;

    /**
     * @locale zh
     * @type callback
     * @region 转推直播
     * @brief 视频 SEI 帧回调，运行在视频回调线程
     * @param task_id 转推直播任务 ID
     * @param data_frame SEI 数据
     */
    /**
     * @locale en
     * @type callback
     * @region Push to CDN
     * @brief This callback carries SEI data, running on the video callback thread
     * @param task_id Task ID
     * @param data_frame SEI data
     */
    virtual void onMixingDataFrame(const char* task_id, IDataFrame* data_frame) = 0;

    /**
     * @locale zh
     * @hidden for internal use only
     * @type callback
     * @region 转推直播
     * @brief 同步视频帧回调。
     * @param task_id 转推直播任务 ID。
     * @param uids 同步视频帧对应的 uid 数组。
     * @param video_frames 同步视频帧数组，与 uids 对应。
     * @param data_frame SEI 数据。
     * @param count 数组的长度。
     */
    /**
     * @locale en
     * @hidden for internal use only
     * @type callback
     * @region Push to CDN
     * @brief Synchronized video frame callback.
     * @param task_id Task ID.
     * @param uids Array of synchronized video frames corresponding to uids.
     * @param video_frames Array of synchronized video frames corresponding to uids.
     * @param data_frame SEI data.
     * @param count The length of the array.
     */
    virtual void onCacheSyncVideoFrames(const char* task_id, const char* uids[], IVideoFrame* video_frames[],
            IDataFrame* data_frame[], int count) = 0;

    /**
     * @locale zh
     * @hidden constructor/destructor
     * @brief 析构函数
     */
    /**
     * @locale en
     * @hidden constructor/destructor
     * @brief Destructor
     */
    virtual ~IMixedStreamObserver() = default;
};

/**
 * @locale zh
 * @deprecated since 3.52, use IMixedStreamObserver{@link #IMixedStreamObserver} instead.
 * @type callback
 * @region 转推直播
 * @brief 推流 Observer<br>
 * 注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。
 */
/**
 * @locale en
 * @deprecated since 3.52, use IMixedStreamObserver{@link #IMixedStreamObserver} instead.
 * @type callback
 * @region Push to CDN
 * @brief Register this observer to receive stream mixing related callbacks from the SDK.
 * @brief  Custom coded frame callback class.<br>
 * Note: Callback functions are thrown synchronously in a non-UI thread within the SDK. Therefore, you must not perform any time-consuming operations or direct UI operations within the callback function, as this may cause the app to crash.
 */
class ITranscoderObserver {
public:
    /**
     * @locale zh
     * @type callback
     * @region 转推直播
     * @brief 是否具有推流能力。  <br>
     *       + false：不具备推流能力（默认值）  <br>
     *       + true：具备推流能力
     * @note 如果需要开启端云一体转推直播功能，你必须确保你的 App 包含 librtmp，具有推流能力。此时，设置该回调为 true。
     */
    /**
     * @locale en
     * @type callback
     * @region Push to CDN
     * @brief Whether your App has the ability to push streams to CDN.   <br>
     *        + true: Yes <br>
     *        + false: No (default value)
     * @note If you need to use the function of intelligently pushing streams to CDN, you should ensure that your App contains librtmp and has the ability to push streams out. If so, set the callback to True.
     */
    virtual bool isSupportClientPushStream() {
        return false;
    }
    /**
     * @locale zh
     * @hidden(Linux) not available
     * @type callback
     * @region 转推直播
     * @brief 转推直播状态回调
     * @param event 转推直播任务状态，参看 StreamMixingEvent{@link #StreamMixingEvent}
     * @param task_id 转推直播任务 ID
     * @param error 转推直播错误码，参看 StreamMixingErrorCode{@link #StreamMixingErrorCode}。
     * @param mix_type 转推直播类型，参看 StreamMixingType{@link #StreamMixingType}
     */
    /**
     * @locale en
     * @hidden(Linux) not available
     * @type callback
     * @region Push to CDN
     * @brief Used for reporting events during pushing streams to CDN
     * @param event Type Stream mixing status, see StreamMixingEvent{@link #StreamMixingEvent}
     * @param task_id Task ID
     * @param error Errors occuring during the pushing process. See StreamMixingErrorCode{@link #StreamMixingErrorCode}
     * @param mix_type Stream mixing and pushing type. See StreamMixingType{@link #StreamMixingType}
     */
    virtual void onStreamMixingEvent(
            StreamMixingEvent event, const char* task_id, StreamMixingErrorCode error, StreamMixingType mix_type) = 0;

    /**
     * @locale zh
     * @type callback
     * @region 转推直播
     * @brief 合流视频回调，运行在视频回调线程
     * @param task_id 合流任务 ID
     * @param video_frame 视频帧，参看 IVideoFrame{@link #IVideoFrame}。
     * @note 收到该回调的周期与视频的帧间隔一致。
     */
    /**
     * @locale en
     * @type callback
     * @region Push to CDN
     * @brief Callback with the video data after stream mixing, running on the video callback thread
     * @param task_id Task ID
     * @param video_frame Video Frame, see IVideoFrame{@link #IVideoFrame}.
     * @note The interval between callbacks is the same with that between video frames.
     */
    virtual void onMixingVideoFrame(const char* task_id, IVideoFrame* video_frame) = 0;

    /**
     * @locale zh
     * @type callback
     * @region 转推直播
     * @brief 合流音频回调，运行在音频回调线程
     * @param task_id 转推直播任务 ID
     * @param audio_frame 音频帧，参看 IAudioFrame{@link #IAudioFrame}。
     * @note 收到该回调的周期为每 10 毫秒一次，并且每次的音频数据量为 10 毫秒数据量。
     */
    /**
     * @locale en
     * @type callback
     * @region Push to CDN
     * @brief Callback with the audio data after stream mixing, running on the audio callback thread
     * @param task_id Task ID.
     * @param audio_frame Audio Frame, see IAudioFrame{@link #IAudioFrame}.
     * @note You will receive the callback every 10 milliseconds. Each callback carries data collected in the last 10 milliseconds.
     */
    virtual void onMixingAudioFrame(const char* task_id, IAudioFrame* audio_frame) = 0;

    /**
     * @locale zh
     * @type callback
     * @region 转推直播
     * @brief 视频 SEI 帧回调，运行在视频回调线程
     * @param task_id 转推直播任务 ID
     * @param data_frame SEI 数据
     */
    /**
     * @locale en
     * @type callback
     * @region Push to CDN
     * @brief This callback carries SEI data, running on the video callback thread
     * @param task_id Task ID
     * @param data_frame SEI data
     */
    virtual void onMixingDataFrame(const char* task_id, IDataFrame* data_frame) = 0;
    /**
     * @locale zh
     * @hidden for internal use only
     * @type callback
     * @valid since 3.50
     * @brief 同步视频帧回调。仅在通过 setSyncControlparam{@link #ITranscoderParam#setSyncControlparam} 设置启用单通同步模式，且其中 `sync_client_video_need_mix=False` 时收到此回调。
     * @param video_frames 同步视频帧数组，与 uids 对应。参看 IVideoFrame{@link #IVideoFrame}。
     * @param data_frame SEI 数据。参看 IDataFrame{@link #IDataFrame}。
     * @param uids 同步视频帧对应的 uid 数组。
     * @param task_id 转推直播任务 ID。
     * @param count `video_frames` 数组长度。
     */
    /**
     * @locale en
     * @hidden for internal use only
     * @type callback
     * @valid since 3.50
     * @brief Synchronized video frame callback. Receive this callback when you enable simplex chorus mode by calling setSyncControlparam{@link #ITranscoderParam#setSyncControlparam} and set `sync_client_video_need_mix=False`. 
     * @param video_frames Array of synchronized video frames. See IVideoFrame{@link #IVideoFrame}.
     * @param data_frame SEI data. See IDataFrame{@link #IDataFrame}.
     * @param uids Array of uids corresponding to the video frames.
     * @param task_id Task ID.
     * @param count length of `video_frames`.
     */
    virtual void onCacheSyncVideoFrames(const char* task_id, const char* uids[], IVideoFrame* video_frames[], IDataFrame* data_frame[], int count) = 0;

    /**
     * @locale zh
     * @hidden constructor/destructor
     * @brief 析构函数
     */
    /**
     * @locale en
     * @hidden constructor/destructor
     * @brief Destructor
     */
    virtual ~ITranscoderObserver() = default;
};
/**
 * @locale zh
 * @hidden(Linux)
 * @type callback
 * @region 转推直播
 * @brief 单流转推直播观察者。  <br>
 * 注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。
 */
/**
 * @locale en
 * @hidden(Linux)
 * @type callback
 * @region Push to CDN
 * @brief Register this observer to receive the callbacks about pushing a single stream to CDN.<br>
 * Note: Callback functions are thrown synchronously in a non-UI thread within the SDK. Therefore, you must not perform any time-consuming operations or direct UI operations within the callback function, as this may cause the app to crash.
 */
class IPushSingleStreamToCDNObserver {
public:
     /**
     * @locale zh
     * @type callback
     * @region 转推直播
     * @brief 单流转推直播状态回调
     * @param event 任务状态, 参看 SingleStreamPushEvent{@link #SingleStreamPushEvent}
     * @param task_id 任务 ID
     * @param error 错误码，参看 StreamMixingErrorCode{@link #StreamMixingErrorCode}
     */
    /**
     * @locale en
     * @type callback
     * @region Push to CDN
     * @brief Used for reporting events during pushing a single stream to CDN.
     * @param event Stream mixing and pushing status, see SingleStreamPushEvent{@link #SingleStreamPushEvent}.
     * @param task_id Task ID
     * @param error Errors occurring during the pushing process. See StreamMixingErrorCode{@link #StreamMixingErrorCode}
     */
    virtual void onStreamPushEvent(SingleStreamPushEvent event, const char *task_id, int error) = 0;
    /**
     * @hidden constructor/destructor
     */
    virtual ~IPushSingleStreamToCDNObserver() = default;
};

/**
 * @locale zh
 * @type callback
 * @brief 缓存同步 Observer
 */
/**
 * @locale en
 * @type callback
 * @brief Observer
 */
class IChorusCacheSyncObserver {
public:
    /**
     * @hidden constructor/destructor
    */
    virtual ~IChorusCacheSyncObserver() {
    }
    /**
     * @locale zh
     * @type callback
     * @brief 调用 startChorusCacheSync{@link #IRTCVideo#startChorusCacheSync}，并设置为 `consumer` 的用户会通过此回调获取经缓存同步后的视频帧。获取频率通过启动同步时的 `fps` 进行设置。
     * @param count `uids` 和 `videoFrames` 的数组长度
     * @param uids[] 参与合唱缓存同步的 `producer` 和 `retransmitter` 的列表，不包括参与但未发送媒体数据的用户。
     * @param video_frames[] 对应 `uids` 的视频帧。参看 IVideoFrame{@link #IVideoFrame}。
     */
    /**
     * @locale en
     * @type callback
     * @brief The user who calls startChorusCacheSync{@link #IRTCVideo#startChorusCacheSync} as `consumer` receives the callback with synced video frames. The interval of receiving the callback is set by `fps`.
     * @param count length of `uids`
     * @param uids[] The list of participants as `producer` and `retransmitter`. The participants not sending media data are excluded.
     * @param video_frames[] Video data frame corresponding to `uids`. See IVideoFrame{@link #IVideoFrame}.
     */    
    virtual void onSyncedVideoFrames(int count, const char* uids[], bytertc::IVideoFrame* video_frames[]) = 0;
    /**
     * @locale zh
     * @type callback
     * @brief 参与合唱缓存同步的 `producer` 和 `retransmitter` 发生变化时，收到此回调。
     * @param count 当前的 `uids` 的长度
     * @param uids  当前的参与者列表
     * @note 有以下情况可能造成参与者发生变化：<br>
     *        + 用户主动调用 startChorusCacheSync{@link #IRTCVideo#startChorusCacheSync} 或 stopChorusCacheSync{@link #IRTCVideo#stopChorusCacheSync};<br>
     *        + 原本参与缓存同步的用户发生异常退出。
     */
    /**
     * @locale en
     * @type callback
     * @brief Receives the callback when the `producer` or `retransmitter` changes.
     * @param count Current length of `uids`
     * @param uids Current list of the participants
     * @note You may receive the callback is the following cases:<br>
     *        + The user calls startChorusCacheSync{@link #IRTCVideo#startChorusCacheSync} or stopChorusCacheSync{@link #IRTCVideo#stopChorusCacheSync};<br>
     *        + The cache syncing participant quits abnormally. 
     */
    virtual void onSyncedUsersChanged(int count, const char* uids[]) = 0;
    /**
     * @locale zh
     * @type callback
     * @brief 缓存同步事件回调
     * @param event 事件，参看 ChorusCacheSyncEvent{@link #ChorusCacheSyncEvent}。
     * @param error 错误码，参看 ChorusCacheSyncError{@link #ChorusCacheSyncError}。
     */
    /**
     * @locale en
     * @type callback
     * @brief Chorus cache sync event callback
     * @param event See ChorusCacheSyncEvent{@link #ChorusCacheSyncEvent}.
     * @param error See ChorusCacheSyncError{@link #ChorusCacheSyncError}.
     */
    virtual void onSyncEvent(ChorusCacheSyncEvent event, ChorusCacheSyncError error) = 0;
};

/**
 * @locale zh
 * @type api
 * @brief 创建合流参数实例
 */
/**
 * @locale en
 * @type api
 * @brief Create an instance with stream mixing configurations
 */
BYTERTC_API ITranscoderParam* createTranscoderParam();
/**
 * @locale zh
 * @type api
 * @brief 创建合流参数实例(新)
 */
/**
 * @locale en
 * @type api
 * @brief Create an instance with stream mixing configurations
 */
BYTERTC_API IMixedStreamConfig* createMixedStreamConfig();
} /* namespace bytertc */
