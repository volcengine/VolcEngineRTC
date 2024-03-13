/*
 * Copyright (c) 2021 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC Video Processor Interface
*/

#pragma once

#include "bytertc_video_frame.h"

namespace bytertc {

/**
 * @locale zh
 * @type api
 * @region 视频处理
 * @brief 视频处理接口类
 */
/**
 * @locale en
 * @type api
 * @region video processing
 * @brief Video processor
 */
class IVideoProcessor
{
public:
    /**
     * @hidden constructor/destructor
     */
    virtual ~IVideoProcessor() = default;

    /**
     * @locale zh
     * @type api
     * @region 视频处理
     * @brief 获取 RTC SDK 采集得到的视频帧，根据 registerLocalVideoProcessor{@link #IRTCVideo#registerLocalVideoProcessor} 设置的视频前处理器，进行视频前处理，最终将处理后的视频帧给到 RTC SDK 用于编码传输。
     * @param src_frame RTC SDK 采集得到的视频帧，参看 IVideoFrame{@link #IVideoFrame}。
     * @return 经过视频前处理后的视频帧，返回给 RTC SDK 供编码和传输，参看 IVideoFrame{@link #IVideoFrame}。
     * @note 
     *       + 在进行视频前处理前，你需要调用 registerLocalVideoProcessor{@link #IRTCVideo#registerLocalVideoProcessor} 设置视频前处理器。<br>
     *       + 如果需要取消视频前处理，可以将视频前处理器设置为 nullptr。
     */
    /**
     * @locale en
     * @type api
     * @region  video processing
     * @brief  Get RTC SDK acquired video frames obtained, according to the video pre-processor registerLocalVideoProcessor{@link #IRTCVideo#registerLocalVideoProcessor} set, video pre-processing, the final processed video frames to the RTC SDK for encoding transmission.
     * @param src_frame Video frames captured by the RTC SDK. See IVideoFrame{@link #IVideoFrame}.
     * @return The video frame after video preprocessing is returned to the RTC SDK for encoding and transmission. See IVideoFrame{@link #IVideoFrame}.
     * @note  
     *        + Before video preprocessing, you need to call registerLocalVideoProcessor{@link #IRTCVideo#registerLocalVideoProcessor} to set up the video preprocessor. <br>
     *        + If you need to cancel the video preprocessing, you can set the video preprocessor to nullptr.
     */
    virtual IVideoFrame* processVideoFrame(IVideoFrame* src_frame) = 0;
};

} // namespace bytertc
