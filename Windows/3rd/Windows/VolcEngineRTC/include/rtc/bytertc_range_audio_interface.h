/*
 *  Copyright (c) 2022 The ByteRtc project authors. All Rights Reserved.
 *  @company ByteDance.Inc
 *  @brief range audio interface
 */

#pragma once

#include "bytertc_audio_defines.h"

namespace bytertc {
/**
 * @locale zh
 * @type keytype
 * @brief 本地用户能收听到、且具有衰减效果的音频接收范围
 */
/**
 * @locale en
 * @type keytype
 * @brief The range where local user can hear audio with attenuation effect.
 */
struct ReceiveRange {
    /**
     * @locale zh
     * @brief 能够接收语音、并且具有衰减效果的最小距离值，该值须 ≥ 0，但 ≤ max。  <br>
     *        小于该值的范围内没有范围语音效果，即收听到的音频音量相同。
     */
    /**
     * @locale en
     * @brief The minimum distance at which the local user can hear the attenuated audio from remote users.  <br>
     *        The value must be ≥ 0, but ≤ max.  <br>
     *        No attenuation effect for audio from distances less than this value you set.
     */
    int min;
    /**
     * @locale zh
     * @brief 能够收听语音的最大距离值，该值须 > 0 且 ≥ min。  <br>
     *        当收听者和声源距离处于 [min, max) 之间时，收听到的音量根据距离呈衰减效果。  <br>
     *        超出该值范围的音频将无法收听到。
     */
    /**
     * @locale en
     * @brief The maximum distance at which the local user can hear audio from remote users.  <br>
     *        The value must be ≥ min, and > 0.  <br>
     *        Audio from distances larger than the value you set cannot be heard.
     */
    int max;
};

/**
 * @locale zh
 * @type keytype
 * @brief 空间音频音量随距离衰减模式
 */
 /**
 * @locale en
 * @type keytype
 * @brief Volume Roll-off modes that a sound has in an audio source
 */
enum AttenuationType {
    /**
     * @locale zh
     * @brief 不随距离衰减
     */
    /**
     * @locale en
     * @brief Disable Volume Attenuation
     */
    kAttenuationTypeNone = 0,
    /**
     * @locale zh
     * @brief 线性衰减，音量随距离增大而线性减小
     */
    /**
     * @locale en
     * @brief Linear roll-off mode which lowers the volume of the sound over the distance
     */
    kAttenuationTypeLinear = 1,
    /**
     * @locale zh
     * @brief 指数型衰减，音量随距离增大进行指数衰减
     */
    /**
     * @locale en
     * @brief Exponential roll-off mode which exponentially decreases the volume of the sound with the distance raising
     */
    kAttenuationTypeExponential = 2,
};

/**
 * @locale zh
 * @hidden(Linux)
 * @type api
 * @brief 范围语音接口实例
 */
/**
 * @locale en
 * @hidden(Linux)
 * @type api
 * @brief Range audio instance
 */
class IRangeAudio {
public:
    /**
     * @locale zh
     * @type api
     * @region 范围语音
     * @brief 开启/关闭范围语音功能。  <br>
     *        范围语音是指，在同一 RTC 房间中设定的音频接收距离范围内，本地用户收听到的远端用户音频音量会随着远端用户的靠近/远离而放大/衰减；若远端用户在房间内的位置超出设定范围，则本地用户无法接收其音频。音频接收范围设置参看 updateReceiveRange{@link #IRangeAudio#updateReceiveRange}。
     * @param enable 是否开启范围语音功能：  <br>
     *        + true: 开启  <br>
     *        + false: 关闭（默认）
     * @note 该方法进房前后都可调用，为保证进房后范围语音效果的平滑切换，你需在该方法前先调用 updatePosition{@link #IRangeAudio#updatePosition} 设置自身位置坐标，然后开启该方法收听范围语音效果。
     */
    /**
     * @locale en
     * @type api
     * @region Range Audio
     * @brief Enable/disable the range audio function.  <br>
     *        Range audio means that within a certain range in a same RTC room, the audio volume of the remote user received by the local user will be amplified/attenuated as the remote user moves closer/away. The audio coming from out of the range cannot be heard. See updateReceiveRange{@link #IRangeAudio#updateReceiveRange} to set audio receiving range.
     * @param enable Whether to enable audio range function：  <br>
     *        + true: Enable  <br>
     *        + false: Disable（Defaulting setting）
     * @note You can call this API anytime before or after entering a room. To ensure a smooth switch to the range audio mode after entering the room, you need to call updatePosition{@link #IRangeAudio#updatePosition} before this API to set your own position coordinates, and then enable the range audio function.
     */
    virtual void enableRangeAudio(bool enable) = 0;
    /**
     * @locale zh
     * @type api
     * @region 范围语音
     * @brief 更新本地用户的音频收听范围。
     * @param range 音频收听范围，参看 ReceiveRange{@link #ReceiveRange}。
     * @return 方法调用结果：  <br>
     *        + 0：成功；  <br>
     *        + !0: 失败。
     */
    /**
     * @locale en
     * @type api
     * @region Range Audio
     * @brief Updates the audio receiving range for the local user.
     * @param range Audio receiving range, see ReceiveRange{@link #ReceiveRange}.
     * @return API call result:  <br>
     *        + 0: Success  <br>
     *        + !0: Failure
     */
    virtual int updateReceiveRange(const ReceiveRange &range) = 0;
    /**
     * @locale zh
     * @type api
     * @region 范围语音
     * @brief 更新本地用户在房间内空间直角坐标系中的位置坐标。
     * @param pos 三维坐标的值，默认为 [0, 0, 0]，参看 [Position](70098#position-2)
     * @return 方法调用结果： <br>
     *        + 0：成功；  <br>
     *        + !0：失败。
     * @note  
     *        + 调用该接口更新坐标后，你需调用 enableRangeAudio{@link #IRangeAudio#enableRangeAudio} 开启范围语音功能以收听范围语音效果。 
     */
    /**
     * @locale en
     * @type api
     * @region Range Audio
     * @brief Updates the coordinate of the local user's position in the rectangular coordinate system in the current room.
     * @param pos 3D coordinate values, the default value is [0, 0, 0], see [Position](70098#position-2).
     * @return API call result: <br>
     *        + 0: Success  <br>
     *        + !0: Failure
     * @note  
     *        + After calling this API, you should call enableRangeAudio{@link #IRangeAudio#enableRangeAudio} to enable range audio function to actually enjoy the range audio effect.  
     */
    virtual int updatePosition(const Position &pos) = 0;

    /**
     * @locale zh
     * @type api
     * @region 范围语音
     * @brief 设置范围语音的音量衰减模式。
     * @param type 音量衰减模式。默认为线性衰减。详见 AttenuationType{@link #AttenuationType}。
     * @param coefficient 指数衰减模式下的音量衰减系数，默认值为 1。范围 [0.1,100]，推荐设置为 `50`。数值越大，音量的衰减速度越快。
     * @return 调用是否成功<br>
     *         + `0`:调用成功<br>
     *         + `-1`:调用失败。原因为在调用 enableRangeAudio{@link #IRangeAudio#enableRangeAudio} 开启范围语音前或进房前调用本接口
     * @note 音量衰减范围通过 updateReceiveRange{@link #IRangeAudio#updateReceiveRange} 进行设置。
     */
    /**
     * @locale en
     * @type api
     * @region Range Audio
     * @brief Set the volume roll-off mode that a 3D sound has in an audio source when using the Range Audio feature.
     * @param type Volume roll-off mode. It is linear roll-off mode by default. Refer to AttenuationType{@link #AttenuationType} for more details.
     * @param coefficient Coefficient for the exponential roll-off mode. The default value is 1. It ranges [0.1,100]. We recommended to set it to `50`. The volume roll-off speed gets faster as this value increases.
     * @return Result of the call<br>
     *         + `0`: Success<br>
     *         + `-1`: Failure because of calling this API before the user has joined a room or before enabling the Range Audio feature by calling enableRangeAudio{@link #IRangeAudio#enableRangeAudio}.
     * @note Call updateReceiveRange{@link #IRangeAudio#updateReceiveRange} to set the range outside which the volume of the sound does not attenuate.
     */
    virtual int setAttenuationModel(AttenuationType type, float coefficient) = 0;

    /**
     * @locale zh
     * @type api
     * @region 范围语音
     * @brief 添加标签组，用于标记相互之间通话不衰减的用户组。<br>
     *        在同一个 RTC 房间中，如果多个用户的标签组之间有交集，那么，他们之间互相通话时，通话不衰减。<br>
     *        比如，用户身处多个队伍，队伍成员间通话不衰减。那么，可以为每个队伍绑定专属标签，每个用户的标签组包含用户所属各个队伍的标签。
     * @param flags 标签组  
     */
    /**
     * @locale en
     * @type api
     * @region Range Audio
     * @brief Set the flags to mark the user groups, within which the users talk without attenuation. <br>
     *        In the RTC room, if the flags of the users intersects with each other, the users talk without attenuation. <br>
     *        For example, the user is a member of multiple teams, and teammates of the same team talks without attentuation. You can set the flag for each team, and includes the flags of the user's teams in the user's flags. 
     * @param flags Array of flags.
     */
    virtual void setNoAttenuationFlags(const char** flags, int len) = 0;

    /**
     * @hidden constructor/destructor
     */
    virtual ~IRangeAudio() {}
};
}  // namespace bytertc
