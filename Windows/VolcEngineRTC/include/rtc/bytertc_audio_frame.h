/*
 * Copyright (c) 2020 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngine audio Frame
 */

#pragma once

#include <stdint.h>
#include <stddef.h>
#include <memory>
#include "bytertc_defines.h"

namespace bytertc {

/**
 * @type keytype
 * @region 音频管理
 * @brief 音频帧类型
 */
enum AudioFrameType {
    /**
     * @brief PCM 16bit
     */
    kFrameTypePCM16 = 0
};

/**
 * @type keytype
 * @region 音频管理
 * @brief 音频帧构建类
 */
typedef struct AudioFrameBuilder {
    /**
     * @brief 音频采样率
     */
    AudioSampleRate sample_rate;

    /**
     * @brief 音频通道数
     */
    AudioChannel channel;

    /**
     * @brief 音频帧时间戳，单位：微秒
     */
    int64_t timestamp_us = 0;

    /**
     * @brief 音频帧数据
     */
    uint8_t* data;

    /**
     * @brief 音频帧数据大小
     */
    int64_t data_size = 0;
} AudioFrameBuilder;

/**
 * @type keytype
 * @brief 音频帧
 */
class IAudioFrame {
public:
    /**
     * @type api
     * @region 音频管理
     * @brief 获取音频帧时间戳。
     * @return 音频帧时间戳，单位：微秒
     */
    virtual int64_t timestamp_us() const = 0;
    /**
     * @type api
     * @region 音频管理
     * @brief 获取音频采样率。参看 AudioSampleRate{@link #AudioSampleRate}
     * @return 音频采样率，单位：Hz
     */
    virtual AudioSampleRate sample_rate() const = 0;
    /**
     * @type api
     * @region 音频管理
     * @brief 获取音频通道数。参看 AudioChannel{@link #AudioChannel}
     * @return 音频通道数
     */
    virtual AudioChannel channel() const = 0;
    /**
     * @type api
     * @region 音频管理
     * @brief 获取音频帧内存块地址
     * @return 音频帧内存块地址
     */
    virtual uint8_t* data() const = 0;
    /**
     * @type api
     * @region 音频管理
     * @brief 获取音频帧数据大小
     * @return 音频帧数据大小
     */
    virtual int data_size() const = 0;
    /**
     * @type api
     * @region 音频管理
     * @brief 获取音频帧类型
     * @return 音频帧类型，目前只支持 PCM，详见 AudioFrameType{@link #AudioFrameType}
     */
    virtual AudioFrameType frame_type() const = 0;
    /**
     * @type api
     * @region 音频管理
     * @brief 释放音频帧
     */
    virtual void release() = 0;
    /**
     * @type api
     * @region 音频管理
     * @brief 获取音频静音标志
     * @return 是否静音数据  <br>
     *        + true: 是  <br>
     *        + false: 否
     */
    virtual bool is_muted_data() const = 0;
    /**
     * @hidden
     */
protected:
    /**
     * @brief 析构函数
     */
    virtual ~IAudioFrame() = default;
};

/**
 * @type api
 * @region 音频管理
 * @brief 创建 IAudioFrame
 * @param [in] builder 音频帧构建实例，参看 AudioFrameBuilder{@link #AudioFrameBuilder}
 */
BYTERTC_API IAudioFrame* BuildAudioFrame(const AudioFrameBuilder& builder);

}  // namespace bytertc
