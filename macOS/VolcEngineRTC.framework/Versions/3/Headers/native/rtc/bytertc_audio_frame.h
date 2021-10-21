/*
 * Copyright (c) 2020 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngine audio Frame
 */

#pragma once

#include <stdint.h>
#include <stddef.h>
#include <memory>

namespace bytertc {

/**
 * @type keytype
 * @brief 音频帧
 */
class IAudioFrame {
public:
    /**
     * @hidden
     * @brief 析构函数
     */
    virtual ~IAudioFrame() {
    } 
    /**
     * @type api
     * @region 音频管理    
     * @author wangjunzheng
     * @brief 获取音频帧时间戳。
     * @return 音频帧时间戳，单位：微秒
     */     
    virtual int64_t timestamp_us() const = 0;
    /**
     * @type api
     * @region 音频管理    
     * @author wangjunzheng
     * @brief 设置音频帧时间戳。
     * @param [in] timestamp_us 音频帧时间戳，单位：微秒
     */    
    virtual void set_timestamp_us(int64_t timestamp_us) = 0;
    /**
     * @type api
     * @region 音频管理    
     * @author wangjunzheng
     * @brief 获取音频采样率
     * @return 音频采样率
     */     
    virtual int sample_rate() const = 0;
    /**
     * @type api
     * @region 音频管理    
     * @author wangjunzheng
     * @brief 设置音频采样率
     * @param [in] sample_rate 音频采样率
     */    
    virtual void set_sample_rate(int sample_rate) = 0;
    /**
     * @type api
     * @region 音频管理    
     * @author wangjunzheng
     * @brief 获取音频通道数
     * @return 音频通道数
     */     
    virtual int channels_num() const = 0;
    /**
     * @type api
     * @region 音频管理    
     * @author wangjunzheng
     * @brief 设置音频通道数
     * @param [in] channels_num 音频通道数
     */    
    virtual void set_channels_num(int channels_num) = 0;
    /**
     * @type api
     * @region 音频管理
     * @author wangjunzheng
     * @brief 设置音频帧内存管理信息
     * @param [in] memory 音频帧内存管理信息，详见 ManagedMemory{@link #ManagedMemory}
     */
    virtual void set_frame_memory(const ManagedMemory& memory) = 0;
    /**
     * @type api
     * @region 音频管理    
     * @author wangjunzheng
     * @brief 获取音频帧内存块地址
     * @return  音频帧内存块地址
     */ 
    virtual uint8_t* data() const = 0;
    /**
     * @type api
     * @region 音频管理    
     * @author wangjunzheng
     * @brief 获取音频帧数据大小
     * @return  音频帧数据大小
     */
    virtual int data_size() const = 0;
};

}  // namespace bytertc
