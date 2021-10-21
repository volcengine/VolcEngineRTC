
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
 * @region 合流转推
 * @brief 推流 Observer
 * @author wanghaoxu
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
     * @region 合流转推
     * @brief 通知 Transcoding 关键事件
     * @author wanghaoxu
     * @param [in] event 事件类型
     * @param [in] event_data 事件参数
     * @param [in] error 错误类型
     * @param [in] mix_type 合流类型
     */
    virtual void OnStreamMixingEvent(
            StreamMixingEvent event, const char* event_data, int error, StreamMixingType mix_type) = 0;

    /**
     * @type callback
     * @region 合流转推
     * @brief 合流视频回调，运行在视频回调线程
     * @author wanghaoxu
     * @param videoFrame 视频帧
     */
    virtual void OnStreamMixingVideoFrame(IVideoFrame* video_frame) = 0;

    /**
     * @type callback
     * @region 合流转推
     * @brief 合流音频回调，运行在音频回调线程
     * @author wanghaoxu
     * @param audioFrame 音频帧
     */
    virtual void OnStreamMixingAudioFrame(IAudioFrame* audio_frame) = 0;

    /**
     * @type callback
     * @region 合流转推
     * @brief 视频SEI帧回调，运行在视频回调线程
     * @author wanghaoxu
     * @param dataFrame SEI 数据
     */
    virtual void OnStreamMixingDataFrame(IDataFrame* data_frame) = 0;
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
