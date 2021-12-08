/*
 * Copyright (c) 2021 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngine Video Processor Interface
*/

#pragma once

#include "bytertc_video_frame.h"

namespace bytertc {

/**
 * @type api
 * @region 视频处理
 */
class IVideoProcessor
{
public:
    /**
     * @hidden
     */
    virtual ~IVideoProcessor() = default;

   /**
    * @type api
    * @region 视频处理
    * @brief 获取 RTC SDK 采集得到的视频帧，根据 RegisterLocalVideoProcessor{@link #IRtcEngineLite#RegisterLocalVideoProcessor} 设置的视频前处理器，进行视频前处理，最终将处理后的视频帧给到 RTC SDK 用于编码传输。
    * @param [in] src_frame RTC SDK 采集得到的视频帧，参看 IVideoFrame{@link #IVideoFrame}。
    * @return 经过视频前处理后的视频帧，返回给 RTC SDK 供编码和传输，参看 IVideoFrame{@link #IVideoFrame}。
    * @notes <br>
    *       + 在进行视频前处理前，你需要调用 RegisterLocalVideoProcessor{@link #IRtcEngineLite#RegisterLocalVideoProcessor} 设置视频前处理器。<br>
    *       + 如果需要取消视频前处理，可以将视频前处理器设置为 nullptr。
    */
    virtual IVideoFrame* ProcessVideoFrame(IVideoFrame* src_frame) = 0;
};

} // namespace bytertc
