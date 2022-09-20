/*
 *  Copyright (c) 2022 The ByteRtc project authors. All Rights Reserved.
 *  @company ByteDance.Inc
 *  @brief range audio interface
 */

#pragma once

#include "bytertc_audio_defines.h"

namespace bytertc {
/** 
 * @type keytype
 * @brief 本地用户能收听到、且具有衰减效果的音频接收范围
 */
struct ReceiveRange {
    /** 
     * @brief 能够接收语音、并且具有衰减效果的最小距离值，该值须 ≥ 0，但 ≤ max。  <br>
     *        小于该值的范围内没有范围语音效果，即收听到的音频音量相同。
     */
    int min;
    /** 
     * @brief 能够收听语音的最大距离值，该值须 > 0 且 ≥ min。  <br>
     *        当收听者和声源距离处于 [min, max) 之间时，收听到的音量根据距离呈衰减效果。  <br>
     *        超出该值范围的音频将无法收听到。
     */
    int max;
};

/** 
 * @type keytype
 * @brief 范围语音流信息
 */
struct RangeAudioInfo {
    /** 
     * @brief 远端音频发布用户 ID
     */
    const char* user_id;
    /** 
     * @brief 本地用户听到该远端音频发布用户的衰减系数，范围 [0,100]，数值为 0 时表示远端用户音频音量为 0。
     */
    int factor = 0;
};

/** 
 * @type keytype
 * @brief 空间音频音量随距离衰减模式
 */
 enum AttenuationType {
    /** 
     * @brief 不随距离衰减
     */
    kAttenuationTypeNone = 0,
    /** 
     * @brief 线性衰减，音量随距离增大而线性减小
     */
    kAttenuationTypeLinear = 1,
    /** 
     * @brief 指数型衰减，音量随距离增大进行指数衰减
     */
    kAttenuationTypeExponential = 2,
};

/** 
 * @hidden(Linux)
 * @type callback
 * @brief 范围语音衰减系数监测器
 */
class IRangeAudioObserver {
public:
    /** 
     * @type callback
     * @region 范围语音
     * @brief 关于当前范围语音衰减系数的回调。  <br>
     *        手动订阅的场景下，房间内任一用户调用 updatePosition{@link #IRangeAudio#updatePosition} 更新自身位置或调用 updateReceiveRange{@link #IRangeAudio#updateReceiveRange} 更新语音接收范围时，该用户与房间内其他用户的相对距离都会发生改变，据此计算的衰减系数也会发生改变，并通过该回调通知用户。 <br>
     *        你可以通过关注该回调中包含的远端用户的衰减系数决定是否订阅该远端用户的流。
     * @param [in] range_audio_info 包含范围语音流信息的数组，参看 RangeAudioInfo{@link #RangeAudioInfo}
     * @param [in] len 范围语音流信息数组长度
     * @notes 更新自身位置或语音接收范围后，并不会马上触发该回调。SDK 会每 500 ms 计算一次衰减系数，并且只在计算结果与上次不同，或结果相同但是距离上次计算已超过 3 秒的时候推送回调。
     */
    virtual void onRangeAudioInfo(const RangeAudioInfo* range_audio_info, int len) {}
    /**
     * @hidden
     */
    virtual ~IRangeAudioObserver() {}
};

/** 
 * @hidden(Linux)
 * @type api
 * @brief 范围语音接口实例
 */
class IRangeAudio {
public:
    /** 
     * @type api
     * @region 范围语音
     * @brief 开启/关闭范围语音功能。  <br>
     *        范围语音是指，在同一 RTC 房间中设定的音频接收距离范围内，本地用户收听到的远端用户音频音量会随着远端用户的靠近/远离而放大/衰减；若远端用户在房间内的位置超出设定范围，则本地用户无法接收其音频。音频接收范围设置参看 updateReceiveRange{@link #IRangeAudio#updateReceiveRange}。
     * @param [in] enable 是否开启范围语音功能：  <br>
     *        + true: 开启  <br>
     *        + false: 关闭（默认）
     * @notes 该方法进房前后都可调用，为保证进房后范围语音效果的平滑切换，你需在该方法前先调用 updatePosition{@link #IRangeAudio#updatePosition} 设置自身位置坐标，然后开启该方法收听范围语音效果。
     */
    virtual void enableRangeAudio(bool enable) = 0;
    /** 
     * @type api
     * @region 范围语音
     * @brief 更新本地用户的音频收听范围。
     * @param [in] range 音频收听范围，参看 ReceiveRange{@link #ReceiveRange}。
     * @return 方法调用结果：  <br>
     *        + 0：成功；  <br>
     *        + !0: 失败。
     * @notes 若此前你已调用 registerRangeAudioObserver{@link #IRangeAudio#registerRangeAudioObserver} 注册了范围语音衰减系数监测器，房间内有任何用户调用该接口更新音频收听范围后，你都会收到 onRangeAudioInfo{@link #IRangeAudioObserver#onRangeAudioInfo} 回调。
     */
    virtual int updateReceiveRange(const ReceiveRange &range) = 0;
    /** 
     * @type api
     * @region 范围语音
     * @brief 更新本地用户在房间内空间直角坐标系中的位置坐标。
     * @param [in] pos 三维坐标的值，默认为 [0, 0, 0]，参看 [Position](70098#position-2)
     * @return 方法调用结果： <br>
     *        + 0：成功；  <br>
     *        + !0：失败。
     * @notes  <br>
     *        + 调用该接口更新坐标后，你需调用 enableRangeAudio{@link #IRangeAudio#enableRangeAudio} 开启范围语音功能以收听范围语音效果。 <br>
     *        + 若此前你已调用 registerRangeAudioObserver{@link #IRangeAudio#registerRangeAudioObserver} 注册了范围语音衰减系数监测器，房间内有任何用户调用该接口更新自身位置坐标后，你都会收到 onRangeAudioInfo{@link #IRangeAudioObserver#onRangeAudioInfo} 回调。
     */
    virtual int updatePosition(const Position &pos) = 0;
    /** 
     * @type api
     * @region 范围语音
     * @brief 设置范围语音衰减系数监测器。
     * @param observer 范围语音衰减系数监测器。  <br>
     *        设置后，SDK 会在监测到房间内有用户更新自身位置坐标或音频收听范围后，触发 onRangeAudioInfo{@link #IRangeAudioObserver#onRangeAudioInfo} 回调。具体参看 IRangeAudioObserver{@link #IRangeAudioObserver}。
     * @notes 该方法仅适用于手动订阅模式，自动订阅无需设置。
     */
    virtual void registerRangeAudioObserver(IRangeAudioObserver* observer) = 0;
    /** 
     * @type api
     * @region 范围语音
     * @brief 设置范围语音的音量衰减模式。<br>
     *        衰减模式更改后，onRangeAudioInfo{@link #IRangeAudioObserver#onRangeAudioInfo} 回调将根据最后设置的衰减模式进行计算并返回音量衰减数值
     * @param type 音量衰减模式。默认为线性衰减。详见 AttenuationType{@link #AttenuationType}。
     * @param coefficient 指数衰减模式下的音量衰减系数，默认值为 1。范围 [0.1,100]，推荐设置为 `50`。数值越大，音量的衰减速度越快。
     * @return 调用是否成功<br>
     *         + `0`:调用成功<br>
     *         + `-1`:调用失败。失败原因为，在调用 enableRangeAudio{@link #IRangeAudio#enableRangeAudio} 开启范围语音前或进房前调用本接口
     * @notes 音量衰减范围通过 updateReceiveRange{@link #IRangeAudio#updateReceiveRange} 进行设置。
     */
    virtual int setAttenuationModel(AttenuationType type, float coefficient) = 0;
    /**
     * @hidden
     */
    virtual ~IRangeAudio() {}
};
}  // namespace bytertc
