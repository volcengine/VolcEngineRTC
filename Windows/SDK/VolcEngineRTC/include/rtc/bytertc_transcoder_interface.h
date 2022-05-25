
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
 * @brief 推流 Observer
 */
class ITranscoderObserver {
public:
    /**
     * @hidden
     */
    virtual bool IsSupportClientPushStream() {
        return false;
    }
    /**  
     * @type callback
     * @region 转推直播
     * @brief 转推直播状态回调
     * @param [in] event 转推直播任务状态，参看 StreamMixingEvent{@link #StreamMixingEvent}
     * @param [in] task_id 转推直播任务 ID
     * @param [in] error 转推直播错误码，参看 TransCodingError{@link #TransCodingError}。
     * @param [in] mix_type 转推直播类型，参看 StreamMixingType{@link #StreamMixingType}
     */
    virtual void OnStreamMixingEvent(
            StreamMixingEvent event, const char* task_id, StreamMixingErrorCode error, StreamMixingType mix_type) = 0;

    /**  
     * @type callback
     * @region 转推直播
     * @brief 合流视频回调，运行在视频回调线程
     * @param [in] task_id 合流任务 ID
     * @param [in] video_frame 视频帧，参看 IVideoFrame{@link #IVideoFrame}。
     * @notes 收到该回调的周期与视频的帧间隔一致。
     */
    virtual void OnStreamMixingVideoFrame(const char* task_id, IVideoFrame* video_frame) = 0;

    /**  
     * @type callback
     * @region 转推直播
     * @brief 合流音频回调，运行在音频回调线程
     * @param [in] task_id 转推直播任务 ID
     * @param [in] audio_frame 音频帧，参看 IAudioFrame{@link #IAudioFrame}。
     * @notes 收到该回调的周期为每 10 毫秒一次，并且每次的音频数据量为 10 毫秒数据量。
     */
    virtual void OnStreamMixingAudioFrame(const char* task_id, IAudioFrame* audio_frame) = 0;

    /**  
     * @type callback
     * @region 转推直播
     * @brief 视频 SEI 帧回调，运行在视频回调线程
     * @param [in] task_id 转推直播任务 ID
     * @param [in] data_frame SEI 数据
     */
    virtual void OnStreamMixingDataFrame(const char* task_id, IDataFrame* data_frame) = 0;

    /**  
     * @hidden
     * @brief 析构函数
     */
    virtual ~ITranscoderObserver() = default;
};

/**  
 * @hidden
 * @type api
 * @brief 创建合流参数实例
 */
BYTERTC_API ITranscoderParam* CreateTranscoderParam();

} /* namespace bytertc */
