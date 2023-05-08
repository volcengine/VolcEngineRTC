/*
 * Copyright (c) 2022 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief audio engine Interface
 */

#pragma once

#include <stddef.h>
#include <stdio.h>
#include <stdarg.h>
#include <memory>
#include "rtc/bytertc_audio_frame.h"
#include "rtc/bytertc_audio_mixing_manager.h"
#include "rtc/byte_rtc_asr_engine_event_handler.h"
#include "rtc/bytertc_audio_device_manager.h"
#include "bytertc_audio_room.h"
#include "bytertc_audio_event_handler.h"

namespace bytertc {
/** 
 * @type api
 * @brief 引擎API
 */
class IRTCAudio {
public:
    /** 
     * @hidden constructor/destructor
     * @brief 析构函数
     */
    virtual ~IRTCAudio() {}

    /** 
     * @type api
     * @region 引擎管理O
     * @brief 设置业务标识参数。  <br>
     *        可通过 business_id 区分不同的业务场景（角色/策略等）。business_id 由客户自定义，相当于一个“标签”，
     *        可以分担和细化现在 AppId 的逻辑划分的功能。
     * @param [in] business_id  <br>
     *        用户设置的自己的 business_id 值。business_id 相当于一个 sub AppId，可以分担和细化现在 AppId
     * 的逻辑划分的功能， 但不需要鉴权。business_id 只是一个标签，颗粒度需要用户自定义。
     * @return  <br>
     *        + 0： 成功。  <br>
     *        + < 0： 失败，具体原因参照 BusinessCheckCode{@link #BusinessCheckCode} 。  <br>
     *        + -6001： 用户已经在房间中。  <br>
     *        + -6002：
     * 输入非法，合法字符包括所有小写字母、大写字母和数字，除此外还包括四个独立字符分别是：英文句号，短横线，下划线和 @
     * 。
     * @notes  <br>
     *        + 需要在调用 joinRoom{@link #IRTCAudioRoom#joinRoom} 之前调用，joinRoom{@link #IRTCAudioRoom#joinRoom}之后调用该方法无效。
     */
    virtual int setBusinessId(const char* business_id) = 0;
    /** 
     * @type api
     * @region 引擎管理
     * @brief 将用户反馈的问题上报到 RTC
     * @param [in] type 预设问题列表，参看 ProblemFeedbackOption{@link #ProblemFeedbackOption}
     * @param [in] count `problemDesc` 的长度
     * @param [in] problemDesc 预设问题以外的其他问题的具体描述
     * @return <br>
     *         + 0: 上报成功  <br>
     *         + -1: 上报失败，还没加入过房间 <br>
     *         + -2: 上报失败，数据解析错误  <br>
     *         + -3: 上报失败，字段缺失  <br>
     * @notes 如果用户上报时在房间内，那么问题会定位到用户当前所在的一个或多个房间；
     *        如果用户上报时不在房间内，那么问题会定位到引擎此前退出的房间。
     */
    virtual int feedback(ProblemFeedbackOption *type, int count, const char* problem_desc) = 0;
    /** 
     * @type api
     * @region 引擎管理
     * @brief 设置运行时的参数
     * @param [in] json_string  json 序列化之后的字符串
     * @notes 该接口需在 joinRoom{@link #IRTCAudioRoom#joinRoom} 和 startAudioCapture{@link #IRTCAudio#startAudioCapture} 之前调用。
     */
    virtual void setRuntimeParameters(const char * json_string) = 0;
    /** 
     * @type api
     * @region 房间管理
     * @brief 创建房间实例。
     *        调用此方法仅返回一个房间实例，你仍需调用 joinRoom{@link #IRTCAudioRoom#joinRoom} 才能真正地创建/加入房间。
     *        多次调用此方法以创建多个 IRTCAudioRoom{@link #IRTCAudioRoom} 实例。分别调用各 IRTCAudioRoom 实例中的 joinRoom{@link #IRTCAudioRoom#joinRoom} 方法，同时加入多个房间。
     *        多房间模式下，用户可以同时订阅各房间的音频流。
     * @param [in] room_id 标识通话房间的房间 ID。该字符串符合正则表达式：`[a-zA-Z0-9_@\-\.]{1,128}`。
     * @return 创建的 IRTCAudioRoom{@link #IRTCAudioRoom} 房间实例。
     * @notes <br>
     *        + 如果需要加入的房间已存在，你仍需先调用本方法来获取 IRTCAudioRoom 实例，再调用 joinRoom{@link #IRTCAudioRoom#joinRoom} 加入房间。
     *        + 请勿使用同样的 roomId 创建多个房间，否则后创建的房间实例会替换先创建的房间实例。
     *        + 加入多个房间后，用户可以同时订阅各房间的音频流，同一时间仅能在一个房间内发布音频流。
     */
    virtual IRTCAudioRoom* createRTCRoom(const char* room_id) = 0;

    /** 
     * @hidden(Linux)
     * @type api
     * @region 音频管理
     * @brief 开启内部音频采集。默认为关闭状态。  <br>
     *        调用后，本地用户会收到 onAudioDeviceStateChanged{@link #IRTCAudioEventHandler#onAudioDeviceStateChanged}  的回调。 <br>
     *        进房后调用该方法，房间中的其他用户会收到 onUserStartAudioCapture{@link #IRTCAudioEventHandler#onUserStartAudioCapture} 的回调。
     * @notes  <br>
     *       + 若未取得当前设备的麦克风权限，调用该方法后会触发 onWarning{@link #IRTCAudioEventHandler#onWarning} 回调。  <br>
     *       + 调用 stopAudioCapture{@link #IRTCAudio#stopAudioCapture} 可以关闭音频采集设备，否则，SDK 只会在销毁引擎的时候自动关闭设备。  <br>
     *       + 由于不同硬件设备初始化响应时间不同，频繁调用 stopAudioCapture{@link #IRTCAudio#stopAudioCapture} 和本接口闭麦/开麦可能出现短暂无声问题，建议使用 publishStream{@link #IRTCAudioRoom#publishStream}/unpublishStream{@link #IRTCAudioRoom#unpublishStream} 实现临时闭麦和重新开麦。
     *       + 无论是否发布音频数据，你都可以调用该方法开启音频采集，并且调用后方可发布音频。  <br>
     */
    virtual void startAudioCapture() = 0;

    /** 
     * @hidden(Linux)
     * @type api
     * @region 音频管理
     * @brief 关闭内部音频采集。默认为关闭状态。  <br>
     *        进房前调用该方法，本地用户会收到 onAudioDeviceStateChanged{@link #IRTCAudioEventHandler#onAudioDeviceStateChanged}  的回调。  <br>
     *        进房后调用该方法后，房间中的其他用户会收到 onUserStopAudioCapture{@link #IRTCAudioEventHandler#onUserStopAudioCapture} 的回调。
     * @notes  <br>
     *       + 调用 startAudioCapture{@link #startAudioCapture} 可以开启音频采集设备。  <br>
     *       + 设备开启后若一直未调用该方法关闭，则 SDK 会在销毁引擎的时候自动关闭音频采集设备。  <br>
     */
    virtual void stopAudioCapture() = 0;

    /** 
     * @hidden(macOS,Windows,Linux)
     * @type api
     * @region 音频管理
     * @brief 设置音频场景类型。
     *        你可以根据你的应用所在场景，选择合适的音频场景类型。
     *        选择音频场景后，SDK 会自动根据客户端音频采集播放设备和状态，适用通话音量/媒体音量。
     * @param [in] scenario 音频场景类型，参看 AudioScenarioType{@link #AudioScenarioType}。
     * @notes  <br>
     *        + 建议在加入房间和调用音频相关接口之前，调用此接口设置音频场景类型。如果在此之后调用此接口，可能会引入音频卡顿。
     *        + 通话音量更适合通话、会议等对信息准确度更高的场景。通话音量会激活系统硬件信号处理，使通话声音更清晰。同时，音量无法降低到 0。
     *        + 媒体音量更适合娱乐场景，因其声音的表现力会更强。媒体音量下，最低音量可以为 0。
     */
    virtual void setAudioScenario(AudioScenarioType scenario) = 0;

    /** 
     * @type api
     * @region 音频管理
     * @brief 设置音质档位。当所选的 RoomProfileType{@link #RoomProfileType} 中的音频参数无法满足你的场景需求时，调用本接口切换的音质档位。
     * @param [in] audio_profile 音质档位，参看 AudioProfileType{@link #AudioProfileType}
     * @notes  <br>
     *        + 该方法在进房前后均可调用；  <br>
     *        + 支持通话过程中动态切换音质档位。
     */
    virtual void setAudioProfile(AudioProfileType audio_profile) = 0;

    /** 
     * @hidden(Linux)
     * @type api
     * @region 音量管理
     * @brief 调节音频采集音量
     * @param [in] volume 采集的音量值和原始音量的比值，范围是 [0, 400]，单位为 %，自带溢出保护。
     *                    只改变音频数据的音量信息，不涉及本端硬件的音量调节。
     * @notes <br>
     *        + 无论是采集来自麦克风的音频流，还是屏幕音频流；无论是 RTC SDK 内部采集，还是自定义采集，都可以使用此接口进行音量调节。
     *        + 在开启音频采集前后，你都可以使用此接口设定采集音量。
     */
    virtual void setCaptureVolume(int volume) = 0;

    /** 
     * @hidden(Linux)
     * @type api
     * @region 音频管理
     * @brief 调节本地播放的所有远端用户混音后的音量。播放音频前或播放音频时，你都可以使用此接口设定播放音量。
     * @param [in] volume 音频播放音量值和原始音量的比值，范围是 [0, 400]，单位为 %，自带溢出保护。  <br>
     *                    只改变音频数据的音量信息，不涉及本端硬件的音量调节。<br>
     *        为保证更好的通话质量，建议将 volume 值设为 [0,100]。  <br>
     *       + 0: 静音  <br>
     *       + 100: 原始音量  <br>
     *       + 400: 最大可为原始音量的 4 倍(自带溢出保护)
     * @notes 假设某远端用户 A 始终在被调节的目标用户范围内，当该方法与 setRemoteAudioPlaybackVolume{@link #IRTCAudio#setRemoteAudioPlaybackVolume} 或 setRemoteRoomAudioPlaybackVolume{@link #IRTCAudioRoom#setRemoteRoomAudioPlaybackVolume} 共同使用时，本地收听用户 A 的音量将为两次设置的音量效果的叠加。
     */
    virtual void setPlaybackVolume(int volume) = 0;

    /** 
      * @type api
      * @region 音频管理
      * @brief 启用音频信息提示。  <br>
      * @param config 详见 AudioPropertiesConfig{@link #AudioPropertiesConfig}
      * @notes 开启提示后，你可以：  <br>
      *       + 通过 onLocalAudioPropertiesReport{@link #IRTCAudioEventHandler#onLocalAudioPropertiesReport} 回调获取本地麦克风和屏幕音频流采集的音频信息；  <br>
      *       + 通过 onRemoteAudioPropertiesReport{@link #IRTCAudioEventHandler#onRemoteAudioPropertiesReport} 回调获取订阅的远端用户的音频信息。  <br>
      */
     virtual void enableAudioPropertiesReport(const AudioPropertiesConfig& config) = 0;

    /** 
     * @hidden(Windows)
     * @type api
     * @region 音频管理
     * @brief 开启/关闭耳返功能
     * @param [in] mode 是否开启耳返功能，参看 EarMonitorMode{@link #EarMonitorMode}
     */
    virtual void setEarMonitorMode(EarMonitorMode mode) = 0;

    /** 
     * @hidden(Windows)
     * @type api
     * @region 音频管理
     * @brief 设置耳返的音量
     * @param [in] volume 耳返的音量，取值范围：[0,100]，单位：%
     * @notes <br>
     *        + 设置耳返音量前，你必须先调用 setEarMonitorMode{@link #setEarMonitorMode} 打开耳返功能。<br>
     *        + 耳返功能仅在使用 RTC SDK 提供的内部音频采集功能，并连接了有线耳机时有效。<br>
     */
    virtual void setEarMonitorVolume(int volume) = 0;

    /** 
     * @type api
     * @region 混音
     * @brief 开启本地语音变调功能，多用于 K 歌场景。  <br>
     *        使用该方法，你可以对本地语音的音调进行升调或降调等调整。
     * @param [in] pitch 相对于语音原始音调的升高/降低值，取值范围[-12，12]，默认值为 0，即不做调整。  <br>
     *        取值范围内每相邻两个值的音高距离相差半音，正值表示升调，负值表示降调，设置的绝对值越大表示音调升高或降低越多。  <br>
     *        超出取值范围则设置失败，并且会触发 onWarning{@link #IRTCAudioEventHandler#onWarning} 回调，提示 WarningCode{@link #WarningCode} 错误码为 `WARNING_CODE_SET_SCREEN_STREAM_INVALID_VOICE_PITCH` 设置语音音调不合法
     */
    virtual void setLocalVoicePitch(int pitch) = 0;

    /** 
    * @hidden(macOS,Windows,Linux,Android)
    * @type api
    * @region 音频管理
    * @brief 在媒体场景下设置蓝牙传输模式
    * @notes  <br>
    *        + 只支持在iOS系统的媒体模式下切换。  <br>
    *        + 只有当设备是蓝牙设备的时候设置才立即生效，否则下次切换成蓝牙设备生效。  <br>
    *        + 进入房间前后均可调用此方法。  <br>
    */
    virtual void setBluetoothMode(BluetoothMode mode) = 0;

    /** 
     * @hidden(macOS,Windows)
     * @type api
     * @region 音频设备管理
     * @brief 设置音频播放设备，默认使用扬声器。  <br>
     *        音频播放设备发生变化时，会收到 onAudioRouteChanged{@link #IRTCAudioEventHandler#onAudioRouteChanged} 回调。
     * @param [in] device 音频播放设备。参看 AudioRoute{@link #AudioRoute} <br>
     * @return 方法调用结果  <br>
     *        + 0: 方法调用成功  <br>
     *        + < 0: 方法调用失败  <br>
     * @notes  <br>
     *       + 1. 该接口仅适用于移动设备。  <br>
     *       + 2. 该方法只支持将音频播放设备设置为听筒或者扬声器。当 App 连接有线或蓝牙音频播放设备时，SDK 会自动切换到有线或蓝牙音频播放设备。主动设置为有线或蓝牙音频播放设备，会返回调用失败。  <br>
     *       + 3. 若连接有线或者蓝牙音频播放设备时，将音频播放设备设置为扬声器或听筒将调用成功，但不会立马切换到扬声器或听筒，会在有线或者蓝牙音频播放设备移除后，根据设置自动切换到听筒或者扬声器。  <br>
     *       + 4. 通话前和通话中都可以调用该方法。  <br>
     *       + 5. 设置kAudioRouteUnknown时将会失败。 <br>
     */
    virtual int setAudioRoute(AudioRoute route) = 0;

    /** 
     * @hidden(macOS,Windows,Linux)
     * @type api
     * @region 音频设备管理
     * @brief 获取当前音频播放设备  <br>
     *        音频播放设备发生变化时，会收到 onAudioRouteChanged{@link #IRTCAudioEventHandler#onAudioRouteChanged} 回调。
     * @return device 当前音频播放设备。参看 AudioRoute{@link #AudioRoute}
     * @notes  <br>
     *       + 1. 该接口仅适用于移动设备。  <br>
     *       + 2. 通话前和通话中都可以调用该方法。  <br>
     */
    virtual AudioRoute getAudioRoute() = 0;

    /** 
     * @hidden(macOS,Windows,Linux)
     * @type api
     * @region 音频设备管理
     * @brief 将默认的音频播放设备设置为听筒或扬声器。  <br>
     * @param [in] route 音频播放设备。参看 AudioRoute{@link #AudioRoute} <br>
     * @return 方法调用结果  <br>
     *        + 0: 方法调用成功。立即生效。当所有音频外设移除后，音频路由将被切换到默认设备。<br>
     *        + < 0: 方法调用失败。指定除扬声器和听筒以外的设备将会失败。   <br>
     * @notes 参见[移动端设置音频路由](https://www.volcengine.com/docs/6348/117836)。
     */
    virtual int setDefaultAudioRoute(AudioRoute route) = 0;
    /** 
     * @type api
     * @region 多房间
     * @brief 调节来自远端用户的音频播放音量
     * @param [in] room_id 音频来源用户所在的房间 ID
     * @param [in] user_id 音频来源的远端用户 ID
     * @param [in] volume 音频播放音量值和原始音量的比值，范围是 [0, 400]，单位为 %，自带溢出保护。
     *                    只改变音频数据的音量信息，不涉及本端硬件的音量调节。<br>
     *                    为保证更好的通话质量，建议将 volume 值设为 [0,100]。 <br>
     *              + 0: 静音  <br>
     *              + 100: 原始音量，默认值  <br>
     *              + 400: 最大可为原始音量的 4 倍(自带溢出保护)  <br>
     * @notes 假设某远端用户 A 始终在被调节的目标用户范围内，<br>
     *        + 当该方法与 setRemoteRoomAudioPlaybackVolume{@link #IRTCAudioRoom#setRemoteRoomAudioPlaybackVolume} 共同使用时，本地收听用户 A 的音量为后调用的方法设置的音量；<br>
     *        + 当该方法与 setPlaybackVolume{@link #IRTCAudio#setPlaybackVolume} 方法共同使用时，本地收听用户 A 的音量将为两次设置的音量效果的叠加。
     */
    virtual void setRemoteAudioPlaybackVolume(const char* room_id, const char* user_id, int volume) = 0;

    /** 
     * @type api
     * @region 音频管理
     * @brief 发送音频流同步信息。将消息通过音频流发送到远端，并实现与音频流同步，该接口调用成功后，远端用户会收到 onStreamSyncInfoReceived{@link #IRTCAudioEventHandler#onStreamSyncInfoReceived} 回调。
     * @param [in] data 消息内容。
     * @param [in] length 消息长度。取值范围是 [1,255] 字节，建议小于 16 字节，否则可能占用较大带宽。
     * @param [in] repeat_count 消息发送重复次数。取值范围是 [0, 30]。
     * @return  <br>
     *        + >=0: 消息发送成功。返回成功发送的次数。  <br>
     *        + -1: 消息发送失败。消息长度大于 255 字节。  <br>
     *        + -2: 消息发送失败。传入的消息内容为空。  <br>
     *        + -3: 消息发送失败。通过屏幕流进行消息同步时，此屏幕流还未发布。  <br>
     *        + -4: 消息发送失败。通过用麦克风或自定义设备采集到的音频流进行消息同步时，此音频流还未发布，详见错误码 ErrorCode{@link #ErrorCode}。  <br>
     * @notes 
     * + 调用本接口的频率建议不超过 50 次每秒。
     * + 在 `kRoomProfileTypeInteractivePodcast` 房间模式下，此消息一定会送达。在其他房间模式下，如果本地用户未说话，此消息不一定会送达。
     */
    virtual int sendStreamSyncInfo(const uint8_t* data, int32_t length, int repeat_count) = 0;

    /** 
     * @type api
     * @region 音频管理
     * @brief 开启/关闭音量均衡功能。  <br>
     *        开启音量均衡功能后，人声的响度会调整为 -16lufs。如果已调用 setAudioMixingLoudness{@link #IAudioMixingManager#setAudioMixingLoudness} 传入了混音音乐的原始响度，此音乐播放时，响度会调整为 -20lufs。
     * @param [in] enable 是否开启音量均衡功能：  <br>
     *       + true: 是  <br>
     *       + false: 否
     * @notes 该接口须在调用 startAudioMixing{@link #IAudioMixingManager#startAudioMixing} 开始播放音频文件之前调用。
     */
    virtual void enableVocalInstrumentBalance(bool enable) = 0;
    /** 
     * @type api
     * @region 音频管理
     * @brief 打开/关闭音量闪避功能。  <br>
     *        开启该功能后，当检测到远端人声时，本地的媒体播放音量会自动减弱，从而保证远端人声的清晰可辨；当远端人声消失时，本地媒体音量会恢复到闪避前的音量水平。
     * @param enable 是否开启音量闪避：  <br>
     *        + true: 是  <br>
     *        + false: 否
     */
    virtual void enablePlaybackDucking(bool enable) = 0;
    /** 
     * @type api
     * @region 自定义音频采集渲染
     * @brief  切换音频采集方式
     * @param type 音频数据源，详见 AudioSourceType{@link #AudioSourceType}。<br>
     *             默认使用内部音频采集。音频采集和渲染方式无需对应。
     * @return  方法调用结果：  <br>
     *        + >0: 切换成功。<br>
     *        + -1：切换失败。
     * @notes  <br>
     *      + 进房前后调用此方法均有效。<br>
     *      + 如果你调用此方法由内部采集切换至自定义采集，SDK 会自动关闭内部采集。然后，调用 pushExternalAudioFrame{@link #IRTCAudio#pushExternalAudioFrame} 推送自定义采集的音频数据到 RTC SDK 用于传输。 <br>
     *      + 如果你调用此方法由自定义采集切换至内部采集，你必须再调用 startAudioCapture{@link #IRTCAudio#startAudioCapture} 手动开启内部采集。 <br>
     */
    virtual int setAudioSourceType(AudioSourceType type) = 0;
    /** 
     * @type api
     * @region 自定义音频采集渲染
     * @brief  切换音频渲染方式
     * @param type 音频输出类型，详见 AudioRenderType{@link #AudioRenderType} <br>
     *             默认使用内部音频渲染。音频采集和渲染方式无需对应。
     * @return  方法调用结果：  <br>
     *        + >0: 切换成功。<br>
     *        + -1：切换失败。
     * @notes  <br>
     *      + 进房前后调用此方法均有效。<br>
     *      + 如果你调用此方法切换至自定义渲染，调用 pullExternalAudioFrame{@link #IRTCAudio#pullExternalAudioFrame} 获取音频数据。 <br>
     */
    virtual int setAudioRenderType(AudioRenderType type) = 0;
    /** 
     * @type api
     * @region 自定义音频采集渲染
     * @brief 推送自定义音频数据。
     * @param [in] audioFrame 10 ms 对应的音频数据。详见 IAudioFrame{@link #IAudioFrame}。
     * @return  方法调用结果  <br>
     *        + true：方法调用成功  <br>
     *        + false：方法调用失败  <br>
     * @notes  <br>
     *       + 推送自定义采集的音频数据前，必须先调用 setAudioSourceType{@link #IRTCAudio#setAudioSourceType} 开启自定义采集。<br>
     *       + 你必须每 10 ms 推送一次数据。<br>
     */
    virtual bool pushExternalAudioFrame(IAudioFrame* audioFrame) = 0;
    /** 
     * @region 自定义音频采集渲染
     * @brief 拉取远端音频数据。可用于自定义音频渲染。
     * @param [out] audioFrame 获取的 10 ms 内的音频数据。详见 IAudioFrame{@link #IAudioFrame}。
     * @return  方法调用结果：  <br>
     *        + true: 方法调用成功  <br>
     *        + false：方法调用失败  <br>
     * @notes  <br>
     *       + 获取音频数据用于自定义渲染前，必须先调用 setAudioRenderType{@link #IRTCAudio#setAudioRenderType} 开启自定义渲染。<br>
     *       + 由于 RTC SDK 的帧长为 10 毫秒，你应当每隔 10 毫秒拉取一次音频数据。确保音频采样点数（sample）x 拉取频率等于 audioFrame 的采样率 （sampleRate）。如设置采样率为 48000 时，每 10 毫秒调用本接口拉取数据，每次应拉取 480 个采样点。  <br>
     *       + 该函数运行在用户调用线程内，是一个同步函数。  <br>
     */
    virtual bool pullExternalAudioFrame(IAudioFrame* audioFrame) = 0;

    /** 
     * @hidden(Android,iOS)
     * @type api
     * @region 音频管理
     * @brief 设备音频管理接口创建
     * @return 音频设备管理接口
     */
    virtual IAudioDeviceManager* getAudioDeviceManager() = 0;

    /** 
     * @type api
     * @region 音频数据回调
     * @brief 设置并开启指定的音频数据帧回调
     * @param [in] method 音频回调方法，参看 AudioFrameCallbackMethod{@link #AudioFrameCallbackMethod}。  <br>
     *               当音频回调方法设置为 `kAudioFrameCallbackRecord`、`kAudioFrameCallbackPlayback`、`kAudioFrameCallbackMixed`、`kAudioFrameCallbackRecordScreen`时，你需要在参数 `format` 中指定准确的采样率和声道，暂不支持设置为自动。  <br>
     *               当音频回调方法设置为 `kAudioFrameCallbackRemoteUser`时，暂不支持音频参数格式中设置准确的采样率和声道，你需要设置为自动。
     * @param [in] format 音频参数格式，参看 AudioFormat{@link #AudioFormat}。
     * @notes 开启音频回调并调用 registerAudioFrameObserver{@link #IRTCAudio#registerAudioFrameObserver} 后，IAudioFrameObserver{@link #IAudioFrameObserver} 会收到对应的音频回调。两者调用顺序没有限制且相互独立。  <br>
     */
    virtual void enableAudioFrameCallback(AudioFrameCallbackMethod method, AudioFormat format) = 0;

    /** 
     * @type api
     * @region 音频数据回调
     * @brief 关闭音频回调
     * @param [in] method 音频回调方法，参看 AudioFrameCallbackMethod{@link #AudioFrameCallbackMethod}。
     * @notes 该方法需要在调用 enableAudioFrameCallback{@link #IRTCAudio#enableAudioFrameCallback} 之后调用。
     */
    virtual void disableAudioFrameCallback(AudioFrameCallbackMethod method) = 0;

    /** 
     * @type api
     * @region 音频数据回调
     * @brief 注册音频数据回调观察者。  <br>
     * @param [in] observer 音频数据观察者，参看 IAudioFrameObserver{@link #IAudioFrameObserver}。如果传入 null，则取消注册。
     * @notes 注册音频数据回调观察者并调用 enableAudioFrameCallback{@link #IRTCAudio#enableAudioFrameCallback} 后，IAudioFrameObserver{@link #IAudioFrameObserver} 会收到对应的音频回调。
     */
    virtual void registerAudioFrameObserver(IAudioFrameObserver* observer) = 0;

    /** 
     * @hidden(Linux)
     * @type api
     * @region 美声特效管理
     * @brief 设置变声特效类型
     * @param [in] voice_changer 变声特效类型，参看 VoiceChangerType{@link #VoiceChangerType}。
     * @return 方法调用结果： <br>
     *        + 0：成功；<br>
     *        + !0：失败。
     * @notes  <br>
     *        + 在进房前后都可设置。  <br>
     *        + 对 RTC SDK 内部采集的音频和自定义采集的音频都生效。 <br>
     *        + 只对单声道音频生效。<br>
     *        + 与 setVoiceReverbType{@link #setVoiceReverbType} 互斥，后设置的特效会覆盖先设置的特效。 <br>
     *        + 使用本接口前，请联系 RTC 技术支持了解更多详情。
     */
    virtual int setVoiceChangerType(VoiceChangerType voice_changer) = 0;

    /** 
     * @hidden(Linux)
     * @type api
     * @region 美声特效管理
     * @brief 设置混响特效类型
     * @param [in] voice_reverb 混响特效类型，参看 VoiceReverbType{@link #VoiceReverbType}。
     * @return 方法调用结果： <br>
     *        + 0：成功；<br>
     *        + !0：失败。
     * @notes  <br>
     *        + 在进房前后都可设置。  <br>
     *        + 对 RTC SDK 内部采集的音频和自定义采集的音频都生效。 <br>
     *        + 只对单声道音频生效。<br>
     *        + 只在包含美声特效能力的 SDK 中有效。<br>
     *        + 与 setVoiceChangerType{@link #setVoiceChangerType} 互斥，后设置的特效会覆盖先设置的特效。 <br>
     *        + 使用本接口前，请联系 RTC 技术支持了解更多详情。
     */
    virtual int setVoiceReverbType(VoiceReverbType voice_reverb) = 0;
    /** 
     * @hidden(Linux)
     * @type api
     * @brief 设置本地采集语音的均衡效果。包含内部采集和外部采集，但不包含混音音频文件。
     * @param config 语音均衡效果，参看 VoiceEqualizationConfig{@link #VoiceEqualizationConfig}
     * @return  <br>
     *        + 0： 成功。  <br>
     *        + < 0： 失败。
     * @notes 根据奈奎斯特采样率，音频采样率必须大于等于设置的中心频率的两倍，否则，设置不生效。
     */
    virtual int setLocalVoiceEqualization(VoiceEqualizationConfig config) = 0;
    /** 
     * @type api
     * @hidden(Linux)
     * @brief 设置本地采集音频的混响效果。包含内部采集和外部采集，但不包含混音音频文件。
     * @param param 混响效果，参看 VoiceReverbConfig{@link #VoiceReverbConfig}
     * @return  <br>
     *        + 0： 成功。  <br>
     *        + < 0： 失败。
     * @notes 调用 enableLocalVoiceReverb{@link #IRTCAudio#enableLocalVoiceReverb} 开启混响效果。
     */
    virtual int setLocalVoiceReverbParam(VoiceReverbConfig param) = 0;
    /** 
     * @type api
     * @hidden(Linux)
     * @brief 开启本地音效混响效果
     * @param enable 是否开启
     * @return  <br>
     *        + 0： 成功。  <br>
     *        + < 0： 失败。
     * @notes 调用 setLocalVoiceReverbParam{@link #IRTCAudio#setLocalVoiceReverbParam} 设置混响效果。
     */
    virtual int enableLocalVoiceReverb(bool enable) = 0;

    /** 
     * @type api
     * @brief 注册自定义音频处理器。<br>
     *        注册完成后，你可以调用 enableAudioProcessor{@link #IRTCAudio#enableAudioProcessor}，对本地采集或接收到的远端音频进行处理。
     * @param [in] processor 自定义音频处理器，详见 IAudioFrameProcessor{@link #IAudioFrameProcessor}。<br>
     *        SDK 只持有 processor 的弱引用，你应保证其生命周期。
     * @notes 重复调用此接口时，仅最后一次调用生效。
     */
    virtual void registerAudioProcessor(IAudioFrameProcessor* processor) = 0;
   /** 
    * @type api
    * @brief 设置并开启指定的音频帧回调，进行自定义处理。
    * @param [in] method 音频帧类型，参看 AudioProcessorMethod{@link #AudioProcessorMethod}。可多次调用此接口，处理不同类型的音频帧。<br>
    *        选择不同类型的音频帧将收到对应的回调：  <br>
    *        + 选择本地采集的音频时，会收到 onProcessRecordAudioFrame{@link #IAudioFrameProcessor#onProcessRecordAudioFrame}。  <br>
    *        + 选择远端音频流的混音音频时，会收到 onProcessPlayBackAudioFrame{@link #IAudioFrameProcessor#onProcessPlayBackAudioFrame}。  <br>
    *        + 选择远端音频流时，会收到 onProcessRemoteUserAudioFrame{@link #IAudioFrameProcessor#onProcessRemoteUserAudioFrame}。  <br>
    *        + 选择屏幕共享音频流时，会收到 onProcessScreenAudioFrame{@link #IAudioFrameProcessor#onProcessScreenAudioFrame}。（Linux 不适用）
    * @param [in] format 设定自定义处理时获取的音频帧格式，参看 AudioFormat{@link #AudioFormat}。
    * @notes <br>
    *        + 在调用此接口前，你需要调用 registerAudioProcessor{@link #IRTCAudio#registerAudioProcessor} 注册自定义音频处理器。<br>
    *        + 要关闭音频自定义处理，调用 disableAudioProcessor{@link #IRTCAudio#disableAudioProcessor}。
    */
   virtual void enableAudioProcessor(AudioProcessorMethod method, AudioFormat format) = 0;
    /** 
     * @type api
     * @brief 关闭自定义音频处理。
     * @param [in] method 音频帧类型，参看 AudioProcessorMethod{@link #AudioProcessorMethod}。
     */
    virtual void disableAudioProcessor(AudioProcessorMethod method) = 0;
    /** 
     * @type api
     * @region 混音
     * @brief 混音管理接口创建
     * @return 混音管理实例，详见IAudioMixingManager{@link #IAudioMixingManager}
     */
    virtual IAudioMixingManager* getAudioMixingManager() = 0;

    /** 
     * @hidden(Windows,Linux,macOS)
     * @type api
     * @region 语音识别服务
     * @brief 开启自动语音识别服务。该方法将识别后的用户语音转化成文字，并通过 OnMessage{@link #IRTCASREngineEventHandler#OnMessage}
     * 事件回调给用户。
     * @param [in] asr_config 校验信息，参看 RTCASRConfig{@link #RTCASRConfig}
     * @param [in] handler 语音识别服务使用状态回调，参看 IRTCASREngineEventHandler{@link #IRTCASREngineEventHandler}
     */
    virtual void startASR(const RTCASRConfig& asr_config, IRTCASREngineEventHandler* handler) = 0;

    /** 
     * @hidden(Windows,Linux,macOS)
     * @type api
     * @region 语音识别服务
     * @brief 关闭语音识别服务
     */
    virtual void stopASR() = 0;

    /** 
     * @type api
     * @region 本地录制
     * @brief 该方法将通话过程中的音频数据录制到本地的文件中。
     * @param [in] config 本地录制参数配置，参看 RecordingConfig{@link #RecordingConfig}
     * @return  <br>
     *        + 0: 正常
     *        + -1: 参数设置异常
     *        + -2: 当前版本 SDK 不支持该特性，请联系技术支持人员
     * @notes  <br>
     *        + 调用该方法后，你会收到 onRecordingStateUpdate{@link #IRTCAudioEventHandler#onRecordingStateUpdate} 回调。  <br>
     *        + 如果录制正常，系统每秒钟会通过 onRecordingProgressUpdate{@link #IRTCAudioEventHandler#onRecordingProgressUpdate}
     * 回调通知录制进度。
     */
    virtual int startFileRecording(RecordingConfig config) = 0;

    /** 
     * @type api
     * @region 本地录制
     * @brief 停止本地录制
     * @notes  <br>
     *        + 调用 startFileRecording{@link #IRTCAudio#startFileRecording} 开启本地录制后，你必须调用该方法停止录制。  <br>
     *        + 调用该方法后，你会收到 onRecordingStateUpdate{@link #IRTCAudioEventHandler#onRecordingStateUpdate} 回调提示录制结果。
     */
    virtual void stopFileRecording() = 0;
    /** 
     * @type api
     * @brief 开启录制语音通话，生成本地文件。
     * @param [in] config 参看 AudioRecordingConfig{@link #AudioRecordingConfig}
     * @return  <br>
     *        + 0: 正常 <br>
     *        + -2: 参数设置异常 <br>
     *        + -3: 当前版本 SDK 不支持该特性，请联系技术支持人员
     * @notes <br>
     *        + 录制包含各种音频效果。但不包含背景音乐。<br>
     *        + 调用 stopAudioRecording{@link #IRTCAudio#stopAudioRecording} 关闭录制。<br>
     *        + 加入房间后才可调用。如果加入了多个房间，录制的文件中会包含各个房间的音频。离开最后一个房间后，录制任务自动停止。 <br>
     *        + 调用该方法后，你会收到 onAudioRecordingStateUpdate{@link #IRTCAudioEventHandler#onAudioRecordingStateUpdate} 回调。  <br>
     */
    virtual int startAudioRecording(AudioRecordingConfig& config) = 0;
    /** 
     * @type api
     * @brief 停止音频文件录制
     * @return <br>
     *         + 0: 正常 <br>
     *         + -3: 当前版本 SDK 不支持该特性，请联系技术支持人员
     * @notes 调用 startAudioRecording{@link #IRTCAudio#startAudioRecording} 开启本地录制。
     */
     virtual int stopAudioRecording() = 0;
    /** 
     * @type api
     * @brief 启用匹配外置声卡的音频处理模式
     * @param [in] enable <br>
     *        + true: 开启 <br>
     *        + false: 不开启(默认)
     * @notes  <br>
     *        + 当采用外接声卡进行音频采集时，建议开启此模式，以获得更好的音质。<br>
     *        + 开启此模式时，仅支持耳机播放。如果需要使用扬声器或者外置音箱播放，关闭此模式。
     */
    virtual void enableExternalSoundCard(bool enable) = 0;

    /** 
     * @type api
     * @region 加密
     * @brief 设置传输时使用内置加密的方式 <br>
     * @param encrypt_type 内置加密算法，详见 EncryptType{@link #EncryptType}
     * @param [in] encrypt_type 加密类型，详见 EncryptType{@link #EncryptType}
     * @param [in] key 加密密钥，长度限制为 36 位，超出部分将会被截断
     * @param [in] key_size 参数 key 的长度
     * @notes  <br>
     *       + 使用传输时内置加密时，使用此方法；如果需要使用传输时自定义加密，参看 onEncryptData{@link #IEncryptHandler#onEncryptData}。 内置加密和自定义加密互斥，根据最后一个调用的方法确定传输是加密的方案。  <br>
     *       + 该方法必须在进房之前调用，可重复调用，以最后调用的参数作为生效参数。  <br>
     */
    virtual void setEncryptInfo(EncryptType encrypt_type, const char* key, int key_size) = 0;

    /** 
     * @type api
     * @region 加密
     * @brief 设置自定义加密  <br>
     *        需要实现对应的加密/解密方法，详情参考 EncryptType{@link #EncryptType} 。 <br>
     * @param [in] handler 自定义加密 handler，需要实现 handler 的加密和解密方法  <br>
     * @notes  <br>
     *       + 该方法与 setEncryptInfo{@link #setEncryptInfo} 为互斥关系，
     *         只能选择自定义加密方式或者默认加密方式。最终生效的加密方式取决于最后一个调用的方法。  <br>
     *       + 该方法必须在进房之前调用，可重复调用，以最后调用的参数作为生效参数。  <br>
     *       + 无论加密或者解密，其对原始数据的长度修改，需要控制在 90% ~ 120% 之间，即如果输入数据为 100 字节，则处理完成后的数据必须在 90 至 120 字节之间，如果加密或解密结果超出该长度限制，则该音频帧会被丢弃。  <br>
     *       + 数据加密/解密为串行执行，因而视实现方式不同，可能会影响到最终渲染效率。是否使用该方法，需要由使用方谨慎评估。
     * <br>
     */
    virtual void setCustomizeEncryptHandler(IEncryptHandler* handler) = 0;
    /** 
     * @type api
     * @brief 在听众端，设置订阅的所有远端音频流精准对齐后播放。
     * @param streamKey 作为对齐基准的远端音频流。参看 RemoteStreamKey{@link #RemoteStreamKey}。<br>
     *                  一般选择主唱的音频流。<br>
     *                  你必须在收到 onUserPublishStream{@link #IRTCAudioRoomEventHandler#onUserPublishStream}，确认此音频流已发布后，调用此 API。
     * @param mode 是否对齐，默认不对齐。参看 AudioAlignmentMode{@link #AudioAlignmentMode}。
     * @notes <br>
     *        + 你必须在实时合唱场景下使用此功能。在加入房间时，所有人应设置 RoomProfileType{@link #RoomProfileType} 为 `kRoomProfileTypeChorus`。<br>
     *        + 订阅的所有远端流必须通过 startAudioMixing{@link #IAudioMixingManager#startAudioMixing} 开启了背景音乐混音，并将 AudioMixingConfig{@link #AudioMixingConfig} 中的 `sync_progress_to_record_frame` 设置为 `true`。<br>
     *        + 如果订阅的某个音频流延迟过大，可能无法实现精准对齐。<br>
     *        + 合唱的参与者不应调用此 API，因为调用此 API 会增加延迟。如果希望从听众变为合唱参与者，应关闭对齐功能。
     */
    virtual void setAudioAlignmentProperty(const RemoteStreamKey& streamKey, AudioAlignmentMode mode) = 0;


    /** 
     * @type api
     * @region 实时消息通信
     * @brief 必须先登录，才能调用 sendUserMessageOutsideRoom{@link #IRTCAudio#sendUserMessageOutsideRoom} 和 sendServerMessage{@link #IRTCAudio#sendServerMessage} 发送房间外点对点消息和向应用服务器发送消息 <br>
     *        在调用本接口登录后，如果想要登出，需要调用 logout{@link #IRTCAudio#logout}。  <br>
     * @param [in] token  <br>
     *        动态密钥  <br>
     *        用户登录必须携带的 Token，用于鉴权验证。  <br>
     *        登录 Token 与加入房间时必须携带的 Token 不同。测试时可使用控制台生成临时 Token，`roomId` 填任意值或置空，正式上线需要使用密钥 SDK 在你的服务端生成并下发 Token。
     * @param [in] uid  <br>
     *        用户 ID  <br>
     *        用户 ID 在 appid 的维度下是唯一的。
     * @return <br>
     *        + `0`：成功<br>
     *        + `-1`：失败。无效参数<br>
     *        + `-2`：无效调用。用户已经登录。成功登录后再次调用本接口将收到此返回值 <br>
     * @notes 本地用户调用此方法登录后，会收到 onLoginResult{@link #IRTCAudioEventHandler#onLoginResult} 回调通知登录结果，远端用户不会收到通知。
     */
    virtual int64_t login(const char* token, const char* uid) = 0;
    /** 
     * @type api
     * @region 实时消息通信
     * @brief 调用本接口登出后，无法调用房间外消息以及端到服务器消息相关的方法或收到相关回调。
     * @notes  <br>
     *       + 调用本接口登出前，必须先调用 login{@link #IRTCAudio#login} 登录。  <br>
     *       + 本地用户调用此方法登出后，会收到 onLogout{@link #IRTCAudioEventHandler#onLogout} 回调通知结果，远端用户不会收到通知。
     */
    virtual void logout() = 0;
    /** 
     * @type api
     * @region 实时消息通信
     * @brief 更新用户用于登录的 Token  <br>
     *        Token 有一定的有效期，当 Token 过期时，需调用此方法更新登录的 Token 信息。  <br>
     *        调用 login{@link #IRTCAudio#login} 方法登录时，如果使用了过期的 Token 将导致登录失败，并会收到 onLoginResult{@link #IRTCAudioEventHandler#onLoginResult} 回调通知，错误码为 kLoginErrorCodeInvalidToken。此时需要重新获取 Token，并调用此方法更新 Token。
     * @param [in] token  <br>
     *        更新的动态密钥
     * @notes  <br>
     *       + 如果 Token 无效导致登录失败，则调用此方法更新 Token 后，SDK 会自动重新登录，而用户不需要自己调用 login{@link #IRTCAudio#login} 方法。  <br>
     *       + Token 过期时，如果已经成功登录，则不会受到影响。Token 过期的错误会在下一次使用过期 Token 登录时，或因本地网络状况不佳导致断网重新登录时通知给用户。
     */
    virtual void updateLoginToken(const char* token) = 0;
    /** 
     * @type api
     * @region 实时消息通信
     * @brief 设置应用服务器参数  <br>
     *        客户端调用 sendServerMessage{@link #IRTCAudio#sendServerMessage} 或 sendServerBinaryMessage{@link #IRTCAudio#sendServerBinaryMessage} 发送消息给应用服务器之前，必须设置有效签名和应用服务器地址。
     * @param [in] signature  <br>
     *        动态签名  <br>
     *        应用服务器会使用该签名对请求进行鉴权验证。
     * @param [in] url  <br>
     *        应用服务器的地址
     * @notes  <br>
     *       + 用户必须调用 login{@link #IRTCAudio#login} 登录后，才能调用本接口。  <br>
     *       + 调用本接口后，SDK 会使用 onServerParamsSetResult{@link #IRTCAudioEventHandler#onServerParamsSetResult} 返回相应结果。
     */
    virtual void setServerParams(const char* signature, const char* url) = 0;
    /** 
     * @type api
     * @region 实时消息通信
     * @brief 查询对端用户或本端用户的登录状态
     * @param [in] peer_user_id  <br>
     *        需要查询的用户 ID
     * @notes  <br>
     *       + 必须调用 login{@link #IRTCAudio#login} 登录后，才能调用本接口。  <br>
     *       + 调用本接口后，SDK 会使用 onGetPeerOnlineStatus{@link #IRTCAudioEventHandler#onGetPeerOnlineStatus} 回调通知查询结果。  <br>
     *       + 在发送房间外消息之前，用户可以通过本接口了解对端用户是否登录，从而决定是否发送消息。也可以通过本接口查询自己查看自己的登录状态。
     */
    virtual void getPeerOnlineStatus(const char* peer_user_id) = 0;
    /** 
     * @type api
     * @region 实时消息通信
     * @brief 给房间外指定的用户发送文本消息（P2P）
     * @param [in] uid  <br>
     *        消息接收用户的 ID
     * @param [in] message  <br>
     *        发送的文本消息内容  <br>
     *        消息不超过 64 KB。
     * @param [in] config 消息类型，参看 MessageConfig{@link #MessageConfig}。
     * @return  <br>
     *        + >0：发送成功，返回这次发送消息的编号，从 1 开始递增  <br>
     *        + -1：发送失败，RtcEngine 实例未创建  <br>
     *        + -2：发送失败，uid 为空
     * @notes  <br>
     *       + 在发送房间外文本消息前，必须先调用 login{@link #IRTCAudio#login} 完成登录。  <br>
     *       + 用户调用本接口发送文本信息后，会收到一次 onUserMessageSendResultOutsideRoom{@link #IRTCAudioEventHandler#onUserMessageSendResultOutsideRoom} 回调，得知消息是否成功发送。  <br>
     *       + 若文本消息发送成功，则 uid 所指定的用户会通过 onUserMessageReceivedOutsideRoom{@link #IRTCAudioEventHandler#onUserMessageReceivedOutsideRoom} 回调收到该消息。
     */
    virtual int64_t sendUserMessageOutsideRoom(const char* uid, const char* message, MessageConfig config) = 0;
    /** 
     * @type api
     * @region 实时消息通信
     * @brief 给房间外指定的用户发送二进制消息（P2P）
     * @param [in] uid  <br>
     *        消息接收用户的 ID
     * @param [in] length <br>
     *        二进制字符串的长度
     * @param [in] message  <br>
     *        发送的二进制消息内容  <br>
     *        消息不超过 46KB。
     * @param [in] config 消息类型，参看 MessageConfig{@link #MessageConfig}。
     * @return  <br>
     *        + >0：发送成功，返回这次发送消息的编号，从 1 开始递增  <br>
     *        + -1：发送失败，RtcEngine 实例未创建  <br>
     *        + -2：发送失败，uid 为空
     * @notes  <br>
     *       + 在发送房间外二进制消息前，必须先调用 login{@link #IRTCAudio#login} 完成登录。  <br>
     *       + 用户调用本接口发送二进制消息后，会收到一次 onUserMessageSendResultOutsideRoom{@link #IRTCAudioEventHandler#onUserMessageSendResultOutsideRoom} 回调，通知消息是否发送成功。  <br>
     *       + 若二进制消息发送成功，则 uid 所指定的用户会通过 onUserBinaryMessageReceivedOutsideRoom{@link #IRTCAudioEventHandler#onUserBinaryMessageReceivedOutsideRoom} 回调收到该条消息。
     */
    virtual int64_t sendUserBinaryMessageOutsideRoom(const char* uid, int length, const uint8_t* message, MessageConfig config) = 0;
    /** 
     * @type api
     * @region 实时消息通信
     * @brief 客户端给应用服务器发送文本消息（P2Server）
     * @param [in] message  <br>
     *        发送的文本消息内容  <br>
     *        消息不超过 64 KB。
     * @return  <br>
     *        + >0：发送成功，返回这次发送消息的编号，从 1 开始递增  <br>
     *        + -1：发送失败，RtcEngine 实例未创建
     * @notes  <br>
     *       + 在向应用服务器发送文本消息前，必须先调用 login{@link #IRTCAudio#login} 完成登录，随后调用 setServerParams{@link #IRTCAudio#setServerParams} 设置应用服务器。  <br>
     *       + 调用本接口后，会收到一次 onServerMessageSendResult{@link #IRTCAudioEventHandler#onServerMessageSendResult} 回调，通知消息发送方是否发送成功。  <br>
     *       + 若文本消息发送成功，则之前调用 setServerParams{@link #IRTCAudio#setServerParams} 设置的应用服务器会收到该条消息。
     */
    virtual int64_t sendServerMessage(const char* message) = 0;
    /** 
     * @type api
     * @region 实时消息通信
     * @brief 客户端给应用服务器发送二进制消息（P2Server）
     * @param [in] length <br>
     *        二进制字符串的长度
     * @param [in] message  <br>
     *        发送的二进制消息内容  <br>
     *        消息不超过 46KB。
     * @return  <br>
     *        + >0：发送成功，返回这次发送消息的编号，从 1 开始递增  <br>
     *        + -1：发送失败，RtcEngine 实例未创建
     * @notes  <br>
     *       + 在向应用服务器发送二进制消息前，必须先调用 login{@link #IRTCAudio#login} 完成登录，随后调用 setServerParams{@link #IRTCAudio#setServerParams} 设置应用服务器。  <br>
     *       + 调用本接口后，会收到一次 onServerMessageSendResult{@link #IRTCAudioEventHandler#onServerMessageSendResult} 回调，通知消息发送方发送成功或失败。  <br>
     *       + 若二进制消息发送成功，则之前调用 setServerParams{@link #IRTCAudio#setServerParams} 设置的应用服务器会收到该条消息。
     */
    virtual int64_t sendServerBinaryMessage(int length, const uint8_t* message) = 0;

    /** 
     * @type api
     * @region 通话前网络探测
     * @brief 开启通话前网络探测
     * @param [in] is_test_uplink  是否探测上行带宽
     * @param [in] expected_uplink_bitrate  期望上行带宽，单位：kbps<br>范围为 {0, [100-10000]}，其中， `0` 表示由 SDK 指定最高码率。
     * @param [in] is_test_downlink  是否探测下行带宽
     * @param [in] expected_downlink_biterate  期望下行带宽，单位：kbps<br>范围为 {0, [100-10000]}，其中， `0` 表示由 SDK 指定最高码率。
     * @return 开启通话前网络探测结果，详见 NetworkDetectionStartReturn{@link #NetworkDetectionStartReturn}
     * @notes  <br>
     *       + 成功调用本接口后，会在 3s 内收到一次 onNetworkDetectionResult{@link #IRTCAudioEventHandler#onNetworkDetectionResult} 回调，此后每 2s 收到一次该回调，通知探测结果；  <br>
     *       + 若探测停止，则会收到一次 onNetworkDetectionStopped{@link #IRTCAudioEventHandler#onNetworkDetectionStopped} 通知探测停止。
     */
    virtual NetworkDetectionStartReturn startNetworkDetection(bool is_test_uplink, int expected_uplink_bitrate,
                                   bool is_test_downlink, int expected_downlink_biterate) = 0;

    /** 
     * @type api
     * @region 通话前网络探测
     * @brief 停止通话前网络探测
     * @notes  <br>
     *       + 调用本接口后，会收到一次 onNetworkDetectionStopped{@link #IRTCAudioEventHandler#onNetworkDetectionStopped} 回调通知探测停止。
     */
    virtual void stopNetworkDetection() = 0;

    /** 
     * @type api
     * @region 云代理
     * @brief 开启云代理
     * @param [in] configuration 云代理服务器信息列表。参看 CloudProxyConfiguration{@link #CloudProxyConfiguration}。
     * @notes  <br>
     *        + 在加入房间前调用此接口  <br>
     *        + 在开启云代理后，进行通话前网络探测 <br>
     *        + 开启云代理后，并成功链接云代理服务器后，会收到 onCloudProxyConnected{@link #IRTCAudioEventHandler#onCloudProxyConnected}。<br>
     *        + 要关闭云代理，调用 stopCloudProxy{@link #IRTCAudio#stopCloudProxy}。
     */
    virtual void startCloudProxy(const CloudProxyConfiguration& configuration) = 0;

    /** 
     * @type api
     * @region 云代理
     * @brief 关闭云代理
     * @notes 要开启云代理，调用 startCloudProxy{@link #IRTCAudio#startCloudProxy}。
     */
    virtual void stopCloudProxy() = 0;
    /** 
     * @hidden(Linux)
     * @type api
     * @brief 通过 NTP 协议，获取网络时间。
     * @return 网络时间。参看 NetworkTimeInfo{@link #NetworkTimeInfo}。
     * @notes <br>
     *        + 第一次调用此接口会启动网络时间同步功能，并返回 `0`。同步完成后，会收到 onNetworkTimeSynchronized{@link #IRTCAudioEventHandler#onNetworkTimeSynchronized}，此后，再次调用此 API，即可获取准确的网络时间。<br>
     *        + 在合唱场景下，合唱参与者应在相同的网络时间播放背景音乐。
     */
    virtual NetworkTimeInfo getNetworkTimeInfo() = 0;

};

/** 
 * @type api
 * @region 引擎管理
 * @brief 创建 IRTCAudio 实例。  <br>
 *        如果当前进程中未创建引擎实例，那么你必须先使用此方法，以使用 RTC 提供的各种音频能力。  <br>
 *        如果当前进程中已创建了引擎实例，再次调用此方法时，会返回已创建的引擎实例。
 * @param [in] app_id 每个应用的唯一标识符。只有使用相同的 app_id 生成的实例，才能够进行音频通信。
 * @param [in] event_handler SDK 回调给应用层的 Callback 对象，详见 IRTCAudioEventHandler{@link #IRTCAudioEventHandler} 。
 * @param [in] parameters 用以覆盖默认参数的本引擎实例参数。JSON 字符串格式。
 * @return  <br>
 *        + IRTCAudio：创建成功。返回一个可用的 IRTCAudio{@link #IRTCAudio} 实例。  <br>
 *        + Null：创建失败。
 */
BYTERTC_API IRTCAudio* createRTCAudio(const char* app_id,
        IRTCAudioEventHandler* event_handler, const char* parameters);

/** 
 * @type api
 * @region 引擎管理
 * @brief 销毁由 createRTCAudio{@link #createRTCAudio} 创建的 RTCEngine 实例，并释放所有相关资源。
 * @notes  <br>
 *        + 请确保和需要销毁的 IRTCAudio{@link #IRTCAudio} 实例相关的业务场景全部结束后，才调用此方法。如果在多线程场景下，调用此接口后，又调用了其他 IRTCAudio{@link #IRTCAudio} 相关接口，可能导致 SDK 崩溃。  <br>
 *        + 该方法在调用之后，会销毁所有和此 IRTCAudio{@link #IRTCAudio} 实例相关的内存，并且停止与媒体服务器的任何交互。  <br>
 *        + 调用本方法会启动 SDK 退出逻辑。引擎线程会保留，直到退出逻辑完成。因此，不要在回调线程中直接调用此 API，也不要在回调中等待主线程的执行，并同时在主线程调用本方法。不然会造成死锁。
 */
BYTERTC_API void destroyRTCAudio();

/** 
 * @type api
 * @region 错误码
 * @brief 获取错误码的描述
 * @param [in] code 需要获取描述的错误码
 * @return 错误码的描述
 * @notes  该接口是通用功能，调用时不需要依赖引擎对象。
 */
BYTERTC_API const char* getErrorDescription(int code);

/** 
 * @type api
 * @region 引擎管理
 * @brief 获取当前 SDK 版本信息。
 * @return 当前 SDK 版本信息。
 */
BYTERTC_API const char* getSDKVersion();

#ifdef __ANDROID__

/** 
 * @hidden(iOS,macOS,Windows,Linux)
 * @type api
 * @region 引擎管理
 * @brief 用于设置 Android 的 ApplicationContext 给 Engine 使用。<br>
 *        如果 Android 使用纯 C++ 接口，则该方法必须在创建引擎前设置。
 * @param [in] j_application_context 传入 Java 的 android.content.Context 类型
 */
BYTERTC_API void setApplicationContext(void* j_application_context);

#endif

}  // namespace bytertc
