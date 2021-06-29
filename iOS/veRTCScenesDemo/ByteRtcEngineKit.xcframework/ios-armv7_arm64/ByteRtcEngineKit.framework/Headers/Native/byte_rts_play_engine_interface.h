/*
 * Copyright 2020 @bytedance
 *  Created on: Seq 05, 2020
 */

#pragma once

#include "byte_rts_play_engine_define.h"

#ifdef WIN32
#define BYTE_RTS_EXPORT __declspec(dllexport)
#else
#define BYTE_RTS_EXPORT __attribute__((__visibility__("default")))
#endif

namespace bytertc {

class IRTSPlayEngineObserver {
 public:
    /**
     * @brief 通知RtsPlay 关键事件
     * @param [out] event 事件类型
     *        [out] biz_data,  业务私有数据
     */
    virtual void OnEventNotify(RTSPlayEngineEvent event, void* biz_data) = 0;
    /**
     * @brief 通知RtsPlay 错误事件
     * @param [out] error 错误类型
     *        [out] private_data,  业务私有数据
     */
    virtual void OnErrorNotify(RTSPlayEngineError error, void* biz_data) = 0;
    /**
     * @brief 解码后音频数据帧回调
     * @param [out] aframe 音频数据帧(PCM)
     */
    virtual void OnAudioFrame(const RTSAudioFrame& aframe) = 0;
    /**
     * @brief 解码后音频数据帧回调
     * @param [out] vframe 视频数据帧(YUV420P)
     */
    virtual void OnVideoFrame(const RTSVideoFrame& vframe) = 0;
    /**
     * @brief 日志回调
     * @param [out] level 日志级别
     *        [out] content 日志内容
     *        [out] private_data,  业务私有数据
     *
     */
    virtual void OnLogPrint(RTSPlayEngineLogLevel level, const char* content, void* biz_data) = 0;
    /**
     * @brief 埋点回调
     * @param [out] level 埋点级别
     *        [out] trace_tag 埋点标签
     *        [out] content 埋点内容
     *        [out] private_data,  业务私有数据
     *
     */
    virtual void OnTracePrint(
            RTSPlayEngineTraceLevel level, const char* trace_tag, const char* content, void* biz_data) = 0;
    /**
     * @brief 析构函数
    */
    virtual ~IRTSPlayEngineObserver() = default;
};

class IRTSPlayEngine {
 public:
    /**
     * @brief Player 初始化
     * > Player 初始化自组件，线程对象
     * @param [in] observer 播放器委托对象
     *        [in] config  播放器配置
     * @return
     *        0: 成功；
     *    other: 失败；
     */
     virtual int32_t Init(IRTSPlayEngineObserver* observer, RTSPlayEngineConfigure config) = 0;
     /**
      * @brief Player 反初始化
      * >  释放子组件，释放线程对象
      * @return
      *        0: 成功；
      *    other: 失败；
      */
     virtual int32_t UnInit() = 0;
     /**
      * @brief Player 开播前准备
      * >  1， 请求answer 2, 建立ICE 3 ，解码首帧
      * @return
      *        0: 成功；
      *    other: 失败；
      */
     virtual int32_t Prepare() = 0;
     /**
      * @brief Player 开播
      * >  改变播放状态，并回调音视频数据
      * @return
      *        0: 成功；
      *    other: 失败；
      */
     virtual int32_t Start() = 0;
     /**
      * @brief Player 关播
      * >  改变播放状态，并停止音视频数据回调
      * @param reason
      *        停止播放原因,详见 RTSStopReason
      * @return
      *        0: 成功；
      *    other: 失败；
      */
     virtual int32_t Stop(RTSStopReason reason) = 0;
     /**
      * @brief Player 是否处于开播状态
      * >
      * @return
      *     true : 开播；
      *     false: 关播；
      */
     virtual bool IsPlaying() = 0;
     /**
      * @brief Player 获取SDK版本号
      */
     virtual const char* GetSdkVersion() const = 0;
     /**
      * @brief Player 设置私有参数
      * >
      * @param [in] params 私有参数（json 格式）
      */
     virtual int32_t SetParameter(const char* params) = 0;
     /**
      * @brief 设置ICE 重连次数，重连间隔
      * >  默认重连次数为3次，重连间隔为1000ms
      * @return
      *        0: 成功；
      *    other: 失败；
      */
     virtual bool SetConnectRetryCount(int count, int interval) = 0;
     /**
      * @brief 获取播放状态
      * >
      * @return
      *        0: 成功；
      *    other: 失败；
      */
     virtual int32_t GetStatsReport(RTSPlayEngineStats* rts_stats) = 0;
    /**
        * @brief 获取引擎上报信息
        * @param trace_type
        *        上报信息类型,详见 RTSTraceType
        * @param rts_trace
        *        上报信息指针,详见 RTCPlayEngineTrace
        * @return
        *        0: 成功；
        *    other: 失败；
        */
    virtual int32_t GetTracePrint(RTSTraceType trace_type, RTSPlayEngineTrace* rts_trace) = 0;
     /**
      * @brief 设置播放音量
      * >  设置下行音量（0～100）
      * @return
      *        0: 成功；
      *    other: 失败；
      */
     virtual bool SetAudioVolume(int32_t volume) = 0;
     /**
      * @brief 静音使能
      * >mute:true 静音，mute:false 解除静音
      * @param [in] mute 静音标志
      */
     virtual void SetAudioMute(bool mute) = 0;
     virtual ~IRTSPlayEngine() = default;
};

/**
 * @brief 创建播放引擎
 * > 该方法创建并初始化IRTSPlayEngine 一个实例。使用 IRTSPlayEngine，必须先调用该接口进行初始化。
 * @param [in] app_id,  Byte 为应用程序开发者签发的 App ID
 */
BYTE_RTS_EXPORT IRTSPlayEngine* CreateRtsPlayEngine(const char* app_id);

/**
 *@brief 销毁播放引擎
 * > 该方法释放IRTSPlayEngine实例所使用的所有资源。
 * @param [in] engine,   由CreateRtsPlayEngine创建的实例
 */
BYTE_RTS_EXPORT void DestroyRtsPlayEngine(IRTSPlayEngine* engine);


} /* namespace bytertc */
