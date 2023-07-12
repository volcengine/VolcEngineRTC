/*
 * Copyright (c) 2021 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC SAMI SDK
*/

#pragma once

#ifndef BYTE_SING_SCORING_INTERFACE_H__
#define BYTE_SING_SCORING_INTERFACE_H__

#include "bytertc_audio_defines.h"

namespace bytertc {
/** 
 * @type callback
 * @brief K 歌评分事件回调类。
 */
class ISingScoringEventHandler {
public:
    /** 
     * @type callback
     * @brief 实时评分信息回调。调用 startSingScoring{@link #ISingScoringManager#startSingScoring} 后，会收到该回调。
     * @param info 实时评分信息。
     */
    virtual void onCurrentScoringInfo(
                 const SingScoringRealtimeInfo& info) = 0;
};
/** 
 * @hidden(Linux)
 * @type api
 * @brief 标准音高数据数组。
 */
class IStandardPitchCollection {
public:
    /** 
     * @type api
     * @brief 获取歌词句子总数
     */
    virtual int getCount() = 0;
    /** 
     * @type api
     * @brief 获取每句歌词的标准音高信息
     * @param index 歌词句子数，取值范围为 0 到调用 getCount{@link #IStandardPitchCollection#getCount} 获取到的句子总数减 1。
     * @return 标准音高数据，参看 StandardPitchInfo{@link #StandardPitchInfo}。
     */
    virtual StandardPitchInfo getStandardPitchInfo(int index) = 0;
    /** 
     * @type api
     * @brief 销毁 IStandardPitchCollection 类，释放资源
     */
    virtual void release() = 0;
};
/** 
 * @hidden(Linux)
 * @type api
 * @brief K 歌评分管理接口。
 */
class ISingScoringManager {
public:
    /** 
     * @hidden constructor/destructor
     * @brief 构造函数
     */
    ISingScoringManager() {
    }
    /** 
     * @type api
     * @brief 初始化 K 歌评分。
     * @param sing_scoring_appkey K 歌评分密钥，用于鉴权验证 K 歌功能是否开通。
     * @param sing_scoring_token K 歌评分密钥，用于鉴权验证 K 歌功能是否开通。
     * @param handler K 歌评分事件回调类，详见 ISingScoringEventHandler{@link #ISingScoringEventHandler}。
     * @notes 输入正确的鉴权信息才可以使用 K 歌评分相关的功能，鉴权方式为离线鉴权，根据包名（bundleID）绑定 Appkey 及 Token，K 歌评分密钥请联系技术支持人员申请。
     * @return  <br>
     *        + 0：配置成功。
     *        + -1：接口调用失败。
     *        + -2：未集成 K 歌评分模块。
     *        + >0：其他错误，具体参看[错误码表](https://www.volcengine.com/docs/6489/148198)。   
     */
    virtual int initSingScoring(
                     const char* sing_scoring_appkey,
                     const char* sing_scoring_token,
                     ISingScoringEventHandler* handler) = 0;
    /** 
     * @type api
     * @brief 设置 K 歌评分参数。
     * @param config K 歌评分的各项参数，详见 SingScoringConfig{@link #SingScoringConfig}。
     * @return  <br>
     *        + 0：配置成功。
     *        + -1：接口调用失败。
     *        + -2：未集成 K 歌评分模块。
     *        + >0：其他错误，具体参看[错误码表](https://www.volcengine.com/docs/6489/148198)。   
     */
    virtual int setSingScoringConfig(
                 const SingScoringConfig& config) = 0;
    /** 
     * @type api
     * @brief 获取标准音高数据。
     * @param midi_filepath 歌曲 midi 文件路径。
     * @return IStandardPitchCollection{@link #IStandardPitchCollection} 标准音高数据数组。
     * @notes 请保证此接口传入的 midi 文件路径与 setSingScoringConfig{@link #ISingScoringManager#setSingScoringConfig} 接口中传入的路径一致。
     */
    virtual IStandardPitchCollection* getStandardPitchInfoCollection(const char* midi_filepath) = 0;
    /** 
     * @hidden(Linux)
     * @type api
     * @brief 开始 K 歌评分。
     * @param position 开始评分时，音乐的播放进度，单位：ms。
     * @param scoring_info_interval 实时回调的时间间隔，单位：ms；默认 50 ms。最低间隔为 20 ms。
     * @return  <br>
     *        + 0：配置成功。
     *        + -1：接口调用失败。
     *        + -2：未集成 K 歌评分模块。
     *        + >0：其他错误，具体参看[错误码表](https://www.volcengine.com/docs/6489/148198)。 
     * @notes  <br>
     *        + 在调用 initSingScoring{@link #initSingScoring} 初始化 K 歌评分功能后调用该接口。
     *        + 调用该接口后，将会根据设置的回调时间间隔，收到评分结果 onCurrentScoringInfo{@link #ISingScoringEventHandler#onCurrentScoringInfo} 回调。
     *        + 如果调用 startAudioMixing{@link #startAudioMixing} 接口播放音频文件，请在收到 onAudioMixingStateChanged{@link #IRTCVideoEventHandler#onAudioMixingStateChanged}(AUDIO_MIXING_STATE_PLAYING(1)) 之后调用此接口。
     */
    virtual int startSingScoring(int position,
                                 int scoring_info_interval) = 0;
    /** 
     * @type api
     * @brief 停止 K 歌评分。
     * @return  <br>
     *        + 0：成功。
     *        + <0：失败。
     */
    virtual int stopSingScoring() = 0;
    /** 
     * @type api
     * @brief 获取上一句的演唱评分。调用 startSingScoring{@link #ISingScoringManager#startSingScoring} 开始评分后可以调用该接口。
     * @return  <br>
     *        + <0：获取评分失败。
     *        + >=0：上一句歌词的演唱评分。
     */
    virtual int getLastSentenceScore() = 0;
    /** 
     * @type api
     * @brief 获取当前演唱总分。调用 startSingScoring{@link #ISingScoringManager#startSingScoring} 开始评分后可以调用该接口。
     * @return  <br>
     *        + <0：获取总分失败。
     *        + >=0：当前演唱总分。
     */
    virtual int getTotalScore() = 0;
    /** 
     * @type api
     * @brief 获取当前演唱歌曲的平均分。
     * @return  <br>
     *        + <0：获取平均分失败。
     *        + >=0：当前演唱平均分。
     */
    virtual int getAverageScore() = 0;
    /**
     * @hidden constructor/destructor
     */
    virtual ~ISingScoringManager() {
    }
};

}  // namespace bytertc

#endif // BYTE_SING_SCORING_INTERFACE_H__
