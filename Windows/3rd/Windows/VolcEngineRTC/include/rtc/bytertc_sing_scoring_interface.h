/*
 * Copyright (c) 2021 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC SAMI SDK
*/

#pragma once

#include "bytertc_audio_defines.h"

namespace bytertc {
/**
 * @locale zh
 * @type callback
 * @brief K 歌评分事件回调类。<br>
 * 注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。
 */
/**
 * @locale en
 * @type callback
 * @brief Karaoke scoring event handler.<br>
 * Note: Callback functions are thrown synchronously in a non-UI thread within the SDK. Therefore, you must not perform any time-consuming operations or direct UI operations within the callback function, as this may cause the app to crash.
 */
class ISingScoringEventHandler {
public:
    /**
     * @locale zh
     * @type callback
     * @brief 实时评分信息回调。调用 startSingScoring{@link #ISingScoringManager#startSingScoring} 后，会收到该回调。
     * @param info 实时评分信息。
     */
    /**
     * @locale en
     * @type callback
     * @brief The callback for real-time scoring data. This callback is triggered after startSingScoring{@link #ISingScoringManager#startSingScoring} is called.
     * @param info Real-time scoring data.
     */
    virtual void onCurrentScoringInfo(
                 const SingScoringRealtimeInfo& info) = 0;
};
/**
 * @locale zh
 * @hidden(Linux)
 * @type api
 * @brief 标准音高数据数组。
 */
/**
 * @locale en
 * @hidden(Linux)
 * @type api
 * @brief Standard Pitch Data.
 */
class IStandardPitchCollection {
public:
    /**
     * @locale zh
     * @type api
     * @brief 获取歌词句子总数
     */
    /**
     * @locale en
     * @type api
     * @brief Get the total number of lyric lines
     */
    virtual int getCount() = 0;
    /**
     * @locale zh
     * @type api
     * @brief 获取每句歌词的标准音高信息
     * @param index 歌词句子数，取值范围为 0 到调用 getCount{@link #IStandardPitchCollection#getCount} 获取到的句子总数减 1。
     * @return 标准音高数据，参看 StandardPitchInfo{@link #StandardPitchInfo}。
     */
    /**
     * @locale en
     * @type api
     * @brief Get the standard pitch information of each lyric.
     * @param index Number of lines, of which the range is from 0 to the total number of lines obtained by calling getCount{@link #IStandardPitchCollection#getCount} minus 1.
     * @return See StandardPitchInfo{@link #StandardPitchInfo}.
     */
    virtual StandardPitchInfo getStandardPitchInfo(int index) = 0;
    /**
     * @locale zh
     * @type api
     * @brief 销毁 IStandardPitchCollection 类，释放资源
     */
    /**
     * @locale en
     * @type api
     * @brief Destroy the IStandardPitchCollection class and release the resources.
     */
    virtual void release() = 0;
};
/**
 * @locale zh
 * @hidden(Linux)
 * @type api
 * @brief K 歌评分管理接口。
 */
/**
 * @locale en
 * @hidden(Linux)
 * @type api
 * @brief Karaoke scoring management interface.
 */
class ISingScoringManager {
public:
    /**
     * @locale zh
     * @hidden constructor/destructor
     * @brief 构造函数
     */
    /**
     * @locale en
     * @hidden constructor/destructor
     * @brief Constructor
     */
    ISingScoringManager() {
    }
    /**
     * @locale zh
     * @type api
     * @brief 初始化 K 歌评分。
     * @param sing_scoring_appkey K 歌评分密钥，用于鉴权验证 K 歌功能是否开通。
     * @param sing_scoring_token K 歌评分密钥，用于鉴权验证 K 歌功能是否开通。
     * @param handler K 歌评分事件回调类，详见 ISingScoringEventHandler{@link #ISingScoringEventHandler}。
     * @note 输入正确的鉴权信息才可以使用 K 歌评分相关的功能，鉴权方式为离线鉴权，根据包名（bundleID）绑定 Appkey 及 Token，K 歌评分密钥请联系技术支持人员申请。
     * @return  
     *        + 0：配置成功。<br>
     *        + -1：接口调用失败。<br>
     *        + -2：未集成 K 歌评分模块。<br>
     *        + >0：其他错误，具体参看[错误码表](https://www.volcengine.com/docs/6489/148198)。   
     */
    /**
     * @locale en
     * @type api
     * @brief Initialize karaoke scoring feature.
     * @param sing_scoring_appkey The key for karaoke scoring, used to authenticate whether the karaoke scoring is enabled.
     * @param sing_scoring_token The key for karaoke scoring, used to authenticate whether the karaoke scoring is enabled.
     * @param handler Karaoke scoring event handler，see ISingScoringEventHandler{@link #ISingScoringEventHandler}.
     * @note Enter two keys to enable karaoke scoring. Authentication is done offline, bind the Appkey and Token according to the package name (bundleID). Please contact technical support to apply for the key.
     * @return  
     *        + 0：Success.<br>
     *        + -1：Interface call failed.<br>
     *        + -2： Karaoke scoring module not integrated.<br>
     *        + >0： Other error. For details, see[Error code].
     */
    virtual int initSingScoring(
                     const char* sing_scoring_appkey,
                     const char* sing_scoring_token,
                     ISingScoringEventHandler* handler) = 0;
    /**
     * @locale zh
     * @type api
     * @brief 设置 K 歌评分参数。
     * @param config K 歌评分的各项参数，详见 SingScoringConfig{@link #SingScoringConfig}。
     * @return  
     *        + 0：配置成功。<br>
     *        + -1：接口调用失败。<br>
     *        + -2：未集成 K 歌评分模块。<br>
     *        + >0：其他错误，具体参看[错误码表](https://www.volcengine.com/docs/6489/148198)。   
     */
    /**
     * @locale en
     * @type api
     * @brief Set the configuration of karaoke scoring.
     * @param config The parameters of karaoke scoring. See SingScoringConfig{@link #SingScoringConfig}.
     * @return  
     *        + 0：Success.<br>
     *        + -1：Interface call failed.<br>
     *        + -2： Karaoke scoring module not integrated.<br>
     *        + >0： Other errors. For details, see[Error code].
     */
    virtual int setSingScoringConfig(
                 const SingScoringConfig& config) = 0;
    /**
     * @locale zh
     * @type api
     * @brief 获取标准音高数据。
     * @param midi_filepath 歌曲 midi 文件路径。
     * @return IStandardPitchCollection{@link #IStandardPitchCollection} 标准音高数据数组。
     * @note 请保证此接口传入的 midi 文件路径与 setSingScoringConfig{@link #ISingScoringManager#setSingScoringConfig} 接口中传入的路径一致。
     */
    /**
     * @locale en
     * @type api
     * @brief Get standard pitch. 
     * @param midi_filepath Midi file path of the song.
     * @return IStandardPitchCollection{@link #IStandardPitchCollection} Standard pitch data array.
     * @note Please make sure the same midi file path is passed in this API and setSingScoringConfig{@link #ISingScoringManager#setSingScoringConfig}.
     */
    virtual IStandardPitchCollection* getStandardPitchInfoCollection(const char* midi_filepath) = 0;
    /**
     * @locale zh
     * @hidden(Linux)
     * @type api
     * @brief 开始 K 歌评分。
     * @param position 开始评分时，音乐的播放进度，单位：ms。
     * @param scoring_info_interval 实时回调的时间间隔，单位：ms；默认 50 ms。最低间隔为 20 ms。
     * @return  
     *        + 0：配置成功。<br>
     *        + -1：接口调用失败。<br>
     *        + -2：未集成 K 歌评分模块。<br>
     *        + >0：其他错误，具体参看[错误码表](https://www.volcengine.com/docs/6489/148198)。 
     * @note  
     *        + 在调用 initSingScoring{@link #initSingScoring} 初始化 K 歌评分功能后调用该接口。<br>
     *        + 调用该接口后，将会根据设置的回调时间间隔，收到评分结果 onCurrentScoringInfo{@link #ISingScoringEventHandler#onCurrentScoringInfo} 回调。<br>
     *        + 如果调用 startAudioMixing{@link #startAudioMixing} 接口播放音频文件，请在收到 onAudioMixingStateChanged{@link #IRTCVideoEventHandler#onAudioMixingStateChanged}(AUDIO_MIXING_STATE_PLAYING(1)) 之后调用此接口。
     */
    /**
     * @locale en
     * @hidden(Linux)
     * @type api
     * @brief Start karaoke scoring. 
     * @param position You can get the playback position where you start karaoke scoring. Unit: ms.
     * @param scoring_info_interval Time interval between two real-time callbacks. Unit: ms; Default interval: 50 ms. Minimum interval: 20 ms.
     * @return  
     *        + 0：Success.<br>
     *        + -1：Interface call failed.<br>
     *        + -2： Karaoke scoring module not integrated.<br>
     *        + >0： Other error. For details, see[Error code].
     * @note 
     *        + You can call this API after calling initSingScoring{@link #initSingScoring} to initialize karaoke scoring.<br>
     *        + After this interface is called, you will receive the scoring result onCurrentScoringInfo{@link #ISingScoringEventHandler#onCurrentScoringInfo} at set interval.<br>
     *        + If you call the startAudioMixing{@link #startAudioMixing} to play an audio file, call this interface after you receive onAudioMixingStateChanged{@link #IRTCVideoEventHandler#onAudioMixingStateChanged}(AUDIO_MIXING_STATE_PLAYING(1)).
     */    
    virtual int startSingScoring(int position,
                                 int scoring_info_interval) = 0;
    /**
     * @locale zh
     * @type api
     * @brief 停止 K 歌评分。
     * @return  
     *        + 0：成功。<br>
     *        + <0：失败。
     */
    /**
     * @locale en
     * @type api
     * @brief Stop karaoke scoring. 
     * @return  
     *        + 0：Success.<br>
     *        + <0：Failure.
     */   
    virtual int stopSingScoring() = 0;
    /**
     * @locale zh
     * @type api
     * @brief 获取上一句的演唱评分。调用 startSingScoring{@link #ISingScoringManager#startSingScoring} 开始评分后可以调用该接口。
     * @return  
     *        + <0：获取评分失败。<br>
     *        + >=0：上一句歌词的演唱评分。
     */
    /**
     * @locale en
     * @type api
     * @brief Get the score for the previous lyric. You can call this API after startSingScoring{@link #ISingScoringManager#startSingScoring} is called.
     * @return  
     *        + <0：Failed to get the score for the previous lyric.<br>
     *        + >=0：The score for the previous lyric.
     */   
    virtual int getLastSentenceScore() = 0;
    /**
     * @locale zh
     * @type api
     * @brief 获取当前演唱总分。调用 startSingScoring{@link #ISingScoringManager#startSingScoring} 开始评分后可以调用该接口。
     * @return  
     *        + <0：获取总分失败。<br>
     *        + >=0：当前演唱总分。
     */
    /**
     * @locale en
     * @type api
     * @brief Get the total score for the user's current performance.You can call this API after startSingScoring{@link #ISingScoringManager#startSingScoring} is called.
     * @return  
     *        + <0：Failed to get the total score.<br>
     *        + >=0：The current total score.
     */    
    virtual int getTotalScore() = 0;
    /**
     * @locale zh
     * @type api
     * @brief 获取当前演唱歌曲的平均分。
     * @return  
     *        + <0：获取平均分失败。<br>
     *        + >=0：当前演唱平均分。
     */
    /**
     * @locale en
     * @type api
     * @brief Get the average score for the user's current performance.
     * @return  
     *        + <0：Failed to get the average score.<br>
     *        + >=0：The average score.
     */   
    virtual int getAverageScore() = 0;
    /**
     * @hidden constructor/destructor
     */
    virtual ~ISingScoringManager() {
    }
};

}  // namespace bytertc
