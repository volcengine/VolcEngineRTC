/*
 * Copyright (c) 2020 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC Interface
 */

#pragma once

#ifndef BYTE_RTC_INTERFACE_H__
#define BYTE_RTC_INTERFACE_H__

#include <stddef.h>
#include <stdio.h>
#include <stdarg.h>
#include <memory>
#include "bytertc_defines.h"
#include "bytertc_engine_event_handler.h"
#include "bytertc_camera_control_interface.h"
#include "bytertc_video_frame.h"
#include "bytertc_audio_frame.h"
#include "bytertc_video_device_manager.h"
#include "bytertc_video_effect_interface.h"
#include "bytertc_audio_frame.h"
#include "byte_rtc_asr_engine_event_handler.h"
#include "bytertc_audio_mixing_manager.h"
#include "bytertc_video_processor_interface.h"
#include "bytertc_transcoder_interface.h"
#include "bytertc_publicstream_interface.h"
#include "bytertc_range_audio_interface.h"
#include "bytertc_spatial_audio_interface.h"

namespace bytertc {
/** 
 * @type api
 * @brief 引擎API
 *      IRtcEngine用IRtcEngineEventHandler 注册接口类方法向应用程序发送回调通知
 */
class IRtcEngine {
public:
    /** 
     * @hidden
     * @brief 析构函数
     */
    virtual ~IRtcEngine() {
    }
    /** 
     * @hidden
     * @deprecated since 326.1, use function joinRoom with RTCRoomConfig parameter instead
     * @type api
     * @region 房间管理
     * @brief 创建/加入房间：房间不存在时即创建房间；房间存在时即加入这个房间。  <br>
     *        同一房间内的用户间可以相互通话。  <br>
     *        进房后重复调用无效，用户必须调用 leaveRoom{@link #leaveRoom} 退出当前房间后，才能加入下一个房间。  <br>
     *        本地用户调用此方法加入房间成功后，会收到 OnRoomStateChanged{@link #IRTCRoomEventHandler#OnRoomStateChanged} 回调通知，远端用户会收到 onUserJoined{@link #IRTCRoomEventHandler#onUserJoined} 回调通知。  <br>
     * @param [in] token 动态密钥，用于对登录用户进行鉴权验证。  <br>
     *        进入房间需要携带 Token。测试时可使用控制台生成临时 Token，正式上线需要使用密钥 SDK 在你的服务端生成并下发 Token。  <br>
     * @param [in] room_id 加入的房间 ID。  <br>
     *        房间 ID 为长度在 128 字节以内的非空字符串，支持以下字符集范围:  <br>
     *            1. 26 个大写字母 A ~ Z 。  <br>
     *            2. 26 个小写字母 a ~ z 。  <br>
     *            3. 10 个数字 0 ~ 9 。  <br>
     *            4. 下划线 "_"，at 符 "@"，减号 "-"。  <br>
     * @param [in] user_info 用户信息，参看 UserInfo{@link #UserInfo}。  <br>
     * @param [in] profile_type 房间模式。  <br>
     *        你应该根据业务需要，选择合适的房间模式。  <br>
     *        你必须在进房前设置房间模式，并且进房后不可更改。  <br>
     *        房间模式参看 RoomProfileType{@link #RoomProfileType}。  <br>
     * @return  <br>
     *        +  0: 成功  <br>
     *        + -1: room_id 为空，失败  <br>
     *        + -2: user_info 为空，失败  <br>
     * @notes  <br>
     *       + 使用不同 App ID 的 App 是不能互通的。  <br>
     *       + 请务必保证生成 Token 使用的 App ID 和创建引擎时使用的 App ID 相同，否则会导致加入房间失败。  <br>
     *       + 用户加入房间成功后，在本地网络状况不佳的情况下，SDK 可能会与服务器失去连接，此时 SDK 将会自动重连。重连成功后，本地会收到 OnRoomStateChanged{@link #IRTCRoomEventHandler#OnRoomStateChanged} 回调通知。  <br>
     *       + 同一个 App ID 的同一个房间内，每个用户的用户 ID 必须是唯一的。如果两个用户的用户 ID 相同，则后进房的用户会将先进房的用户踢出房间，并且先进房的用户会收到 onError{@link #IRtcEngineEventHandler#onError} 回调通知，错误类型详见 ErrorCode{@link #ErrorCode}。  <br>
     */
    virtual int joinRoom(
            const char* token, const char* room_id, const UserInfo& user_info, RoomProfileType profile_type) = 0;
    /** 
     * @type api
     * @region 房间管理
     * @brief 创建/加入房间：房间不存在时即创建房间；房间存在时即加入这个房间。  <br>
     *        同一房间内的用户间可以相互通话。  <br>
     *        进房后重复调用无效，用户必须调用 leaveRoom{@link #IRTCRoom#leaveRoom} 退出当前房间后，才能加入下一个房间。  <br>
     * @param [in] token 动态密钥，用于对登录用户进行鉴权验证。  <br>
     *        进入房间需要携带 Token。测试时可使用控制台生成临时 Token，正式上线需要使用密钥 SDK 在您的服务端生成并下发 Token。  <br>
     *        请务必保证生成 Token 使用的 App ID 和创建引擎时使用的 App ID 相同，否则会导致加入房间失败。  <br>
     * @param [in] room_id 加入的房间 ID。  <br>
     *        该字符串符合正则表达式：`[a-zA-Z0-9_@\-\.]{1,128}`
     * @param [in] user_info 用户信息，参看 UserInfo{@link #UserInfo}。  <br>
     * @param [in] room_config 房间参数配置，设置房间模式以及是否自动发布或订阅流。具体配置模式参看 RTCRoomConfig{@link #RTCRoomConfig}。  <br>
     * @return  <br>
     *        +  0: 成功  <br>
     *        + -1：失败。room_id / user_info.uid 包含了无效的参数  <br>
     *        + -2：已经在房间内。接口调用成功后，只要收到返回值为 0 ，且未调用 leaveRoom:{@link #IRTCRoom#leaveRoom} 成功，则再次调用进房接口时，无论填写的房间 ID 和用户 ID 是否重复，均触发此返回值。  <br>  <br>
     * @notes  <br>
     *       + 同一个 App ID 的同一个房间内，每个用户的用户 ID 必须是唯一的。如果两个用户的用户 ID 相同，则后进房的用户会将先进房的用户踢出房间，并且先进房的用户会收到 onError{@link #IRtcEngineEventHandler#onError} 回调通知，错误类型详见 ErrorCode{@link #ErrorCode} 中的 kErrorCodeDuplicateLogin。  <br>
     *       + 本地用户调用此方法加入房间成功后，会收到 onRoomStateChanged{@link #IRTCRoomEventHandler#onRoomStateChanged} 回调通知。  <br>
     *       + 本地用户调用 setUserVisibility{@link #IRTCRoom#setUserVisibility} 将自身设为可见后加入房间，远端用户会收到 onUserJoined{@link #IRTCRoomEventHandler#onUserJoined}。  <br>
     *       + 用户加入房间成功后，在本地网络状况不佳的情况下，SDK 可能会与服务器失去连接，此时 SDK 将会自动重连。重连成功后，本地会收到 onRoomStateChanged{@link #IRTCRoomEventHandler#onRoomStateChanged} 回调通知；如果加入房间的用户可见，远端用户会收到 onUserJoined{@link #IRTCRoomEventHandler#onUserJoined}。  <br>
     */
     virtual int joinRoom(const char* token, const char* room_id, const UserInfo& user_info, const RTCRoomConfig& room_config) = 0;

/** 
     * @hidden
     * @deprecated since 327.1, use setCaptureVolume instead
     * @type api
     * @region 音频管理
     * @brief 调节音频采集音量
     * @param [in] volume 音频采集音量，取值范围： [0,400]  <br>
     *       + 0: 静音  <br>
     *       + 100: 原始音量  <br>
     *       + 400: 最大可为原始音量的 4 倍(自带溢出保护)  <br>
     * @notes 为保证更好的通话质量，建议将 volume 值设为 [0,100], 该接口已废弃，请使用 setCaptureVolume{@link #setCaptureVolume}。
     */
    virtual void setRecordingVolume(const int volume) = 0;

    /** 
     * @hidden(Linux)
     * @type api
     * @region 音量管理
     * @brief 调节音频采集音量
     * @param [in] index 流索引，指定调节主流还是调节屏幕流的音量，参看 StreamIndex{@link #StreamIndex}
     * @param [in] volume 采集的音量值和原始音量的比值，范围是 [0, 400]，单位为 %，自带溢出保护。
     *        为保证更好的通话质量，建议将 volume 值设为 [0,100]。
     *       + 0：静音  <br>
     *       + 100：原始音量  <br>
     *       + 400: 最大可为原始音量的 4 倍(自带溢出保护)  <br>
     * @notes 在开启音频采集前后，你都可以使用此接口设定采集音量。
     */
    virtual void setCaptureVolume(StreamIndex index, int volume) = 0;

    /** 
     * @hidden(Linux)
     * @type api
     * @region 音频管理
     * @brief 调节本地播放的所有远端用户混音后的音量。播放音频前或播放音频时，你都可以使用此接口设定播放音量。
     * @param [in] volume 音频播放音量值和原始音量的比值，范围是 [0, 400]，单位为 %，自带溢出保护。  <br>
     *        为保证更好的通话质量，建议将 volume 值设为 [0,100]。  <br>
     *       + 0: 静音  <br>
     *       + 100: 原始音量  <br>
     *       + 400: 最大可为原始音量的 4 倍(自带溢出保护)  <br>
     */
    virtual void setPlaybackVolume(const int volume) = 0;


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
    virtual void setEarMonitorVolume(const int volume) = 0;

    /** 
    * @hidden(macOS,Windows,Linux,Android)
    * @type api
    * @region 蓝牙模式化设置
    * @brief 设置蓝牙模式
    * @notes 仅在媒体场景下生效。
    */
   virtual void setBluetoothMode(BluetoothMode mode) = 0;

    /** 
     * @hidden
     * @deprecated since 327.1, use setScreenAudioStreamIndex instead
     * @type api
     * @region 屏幕共享
     * @brief 开启声卡采集，将声卡播放的音频流合到本地采集的音频流中。<br>
     *         如果你希望将声卡播放的声音传输到远端（比如屏幕共享等场景），你必须开启声卡采集。如此，声卡播放的声音会合到本地采集的音频流在中，一起发送到远端。
     * @notes  <br>
     *       + 开启声卡采集后，你可以设置对应音量，参看 setScreenAudioVolumeBeforeMixing{@link
     * #setScreenAudioVolumeBeforeMixing} <br>
     *       + 如果需要关闭声卡采集，参看 StopMixScreenAudioToMainStream{@link #StopMixScreenAudioToMainStream}
     */
    virtual void startMixScreenAudioToMainStream() = 0;

    /** 
     * @hidden
     * @deprecated since 327.1, use setScreenAudioStreamIndex instead
     * @type api
     * @region 屏幕共享
     * @brief 关闭声卡采集，声卡播放的音频流不再合到本地采集的音频流中。
     * @notes 如果需要开启声卡采集，请参看 startMixScreenAudioToMainStream{@link #startMixScreenAudioToMainStream}
     */
    virtual void stopMixScreenAudioToMainStream() = 0;

    /** 
     * @hidden
     * @deprecated since 327.1, use setCaptureVolume instead
     * @type api
     * @region 屏幕共享
     * @brief 调节本地声卡采集音量。<br>
     *        开启本地声卡采集后，你可以使用此接口调节采集音量。
     *        关于如何开启本地声卡采集，参考 startMixScreenAudioToMainStream{@link #startMixScreenAudioToMainStream}。
     * @param volume 声卡采集音量，取值范围： [0,400]  <br>
     *       + 0: 静音  <br>
     *       + 100: 原始音量  <br>
     *       + 400: 最大可为原始音量的 4 倍(自带溢出保护)  <br>
     */
    virtual void setScreenAudioVolumeBeforeMixing(int volume) = 0;

    /** 
     * @hidden(Linux)
     * @type api
     * @region 音频管理
     * @brief 开启内部音频采集。默认为关闭状态。  <br>
     *        内部采集是指：使用 RTC SDK 内置的音频采集机制进行视频采集。
     *        调用该方法开启后，本地用户会收到 onAudioDeviceStateChanged{@link #IRtcEngineEventHandler#onAudioDeviceStateChanged} 的回调。 <br>
     *        非隐身用户进房后调用该方法，房间中的其他用户会收到 onUserStartAudioCapture{@link #IRtcEngineEventHandler#onUserStartAudioCapture} 的回调。
     * @notes  <br>
     *       + 若未取得当前设备的麦克风权限，调用该方法后会触发 onWarning{@link #IRtcEngineEventHandler#onWarning} 回调。  <br>
     *       + 调用 stopAudioCapture{@link IRtcEngine#stopAudioCapture} 可以关闭音频采集设备，否则，SDK 只会在销毁引擎的时候自动关闭设备。  <br>
     *       + 由于不同硬件设备初始化响应时间不同，频繁调用 stopAudioCapture{@link IRtcEngine#stopAudioCapture} 和本接口闭麦/开麦可能出现短暂无声问题，建议使用 publish{@link IRtcEngine#publish}/unpublish{@link IRtcEngine#unpublish} 实现临时闭麦和重新开麦。
     *       + 创建引擎后，无论是否发布音频数据，你都可以调用该方法开启音频采集，并且调用后方可发布音频。  <br>
     *       + 如果需要从自定义音频采集切换为内部音频采集，你必须先停止发布流，调用 setAudioSourceType{@link #IRtcEngine#setAudioSourceType} 关闭自定义采集，再调用此方法手动开启内部采集。
     */
    virtual void startAudioCapture() = 0;

    /** 
     * @hidden(Linux)
     * @type api
     * @region 音频管理
     * @brief 立即关闭内部音频采集。默认为关闭状态。  <br>
     *        内部采集是指：使用 RTC SDK 内置的音频采集机制进行视频采集。
     *        调用该方法，本地用户会收到 onAudioDeviceStateChanged{@link #IRtcEngineEventHandler#onAudioDeviceStateChanged} 的回调。  <br>
     *        非隐身用户进房后调用该方法后，房间中的其他用户会收到 onUserStopAudioCapture{@link #IRtcEngineEventHandler#onUserStopAudioCapture} 的回调。
     * @notes  <br>
     *       + 调用 startAudioCapture{@link #startAudioCapture} 可以开启音频采集设备。  <br>
     *       + 如果不调用本方法停止内部视频采集，则只有当销毁引擎实例时，内部音频采集才会停止。
     */
    virtual void stopAudioCapture() = 0;

    /** 
     * @hidden(macOS,Windows,Linux)
     * @type api
     * @region 音频管理
     * @brief 设置音频场景类型。  <br>
     *        你可以根据你的应用所在场景，选择合适的音频场景类型。
     *        选择音频场景后，RTC 会自动根据客户端音频路由和发布订阅状态，适用通话音量/媒体音量。  <br>
     *        在进房前和进房后设置均可生效。
     * @param [in] scenario 音频场景类型，
     *        参见 AudioScenarioType{@link #AudioScenarioType}
     * @notes  <br>
     *        +
     * 通话音量更适合通话，会议等对信息准确度要求更高的场景。通话音量会激活系统硬件信号处理，使通话声音会更清晰。此时，音量无法降低到
     * 0。<br>
     *        + 媒体音量更适合娱乐场景，因其声音的表现力会更强。媒体音量下，音量最低可以降低到 0。
     */
    virtual void setAudioScenario(AudioScenarioType scenario) = 0;

    /** 
     * @type api
     * @region 美声特效管理
     * @brief 设置变声特效类型
     * @param [in] voice_changer 变声特效类型，参看 VoiceChangerType{@link #VoiceChangerType}
     * @notes  <br>
     *        + 在进房前后都可设置。  <br>
     *        + 对 RTC SDK 内部采集的音频和自定义采集的音频都生效。 <br>
     *        + 只对单声道音频生效。<br>
     *        + 只在包含美声特效能力的 SDK 中有效。<br>
     *        + 与 setVoiceReverbType{@link #setVoiceReverbType} 互斥，后设置的特效会覆盖先设置的特效。 <br>
     */
    virtual int setVoiceChangerType(VoiceChangerType voice_changer) = 0;

    /** 
     * @type api
     * @region 美声特效管理
     * @brief 设置混响特效类型
     * @param [in] voice_reverb 混响特效类型，参看 VoiceReverbType{@link #VoiceReverbType}
     * @notes  <br>
     *        + 在进房前后都可设置。  <br>
     *        + 对 RTC SDK 内部采集的音频和自定义采集的音频都生效。 <br>
     *        + 只对单声道音频生效。<br>
     *        + 只在包含美声特效能力的 SDK 中有效。<br>
     *        + 与 setVoiceChangerType{@link #setVoiceChangerType} 互斥，后设置的特效会覆盖先设置的特效。 <br>
     */
    virtual int setVoiceReverbType(VoiceReverbType voice_reverb) = 0;

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
     * @hidden
     * @deprecated since 336.1, use unpublishStream and publishStream instead.
     * @type api
     * @region 媒体流管理
     * @brief 控制本地音频流的发送状态：发送/不发送  <br>
     *        非隐身用户使用此方法后，房间中的其他用户会收到回调： onUserMuteAudio{@link #IRTCRoomEventHandler#onUserMuteAudio}
     * @param [in] mute_state 发送状态，标识是否发送本地音频流，详见：MuteState{@link #MuteState}
     * @notes  <br>
     *        + 本方法仅控制本地音频流的发送状态，并不影响本地音频采集状态。
     *        + 无论是否开启音频采集，你都可以启动发送本地音频流。如果在采集前启用发送，音频将在采集开始后立即发送。
     */
    virtual void muteLocalAudio(MuteState mute_state) = 0;
    /** 
     * @hidden
     * @deprecated since 340.1, use SetAudioSourceType and SetAudioRenderType instead.
     * @type api
     * @region 自定义音频采集渲染
     * @brief 启用自定义音频采集渲染
     * @param [in] recording_format 自定义音频数据采集格式，详见 AudioFormat{@link #AudioFormat}
     * @param [in] playback_format 自定义音频数据渲染格式，详见 AudioFormat{@link #AudioFormat}
     * @notes  <br>
     *      + 该方法需要在进房前调用。  <br>
     *      + 启用自定义音频采集渲染的状态在离开房间后仍然有效，会一直持续到调用 disableExternalAudioDevice{@link #IRtcEngine#disableExternalAudioDevice} 关闭自定义音频采集渲染为止。  <br>
     *      + 必须同时启用自定义音频采集和自定义音频渲染，或同时启用内部音频采集和内部音频渲染。默认使用内部音频采集和渲染。 <br>
     *      + 启用自定义音频采集渲染后，仍需要使用 pushExternalAudioFrame{@link #IRtcEngine#pushExternalAudioFrame}，推送外部音频数据，再使用 pullExternalAudioFrame{@link #IRtcEngine#pullExternalAudioFrame} 拉取外部音频数据。  <br>
     *      + 当你调用此 API 由内部采集切换至自定义音频采集时，SDK 会自动关闭内部采集。  <br>
     *      + 当你调用此方法开启自定义采集后，想要切换至内部采集，你必须先调用 disableExternalAudioDevice{@link #IRtcEngine#disableExternalAudioDevice} 关闭自定义采集，然后调用 startAudioCapture{@link #IRtcEngine#startAudioCapture} 手动开启内部采集。
     */
     virtual void enableExternalAudioDevice(const AudioFormat &recording_format, const AudioFormat &playback_format) = 0;

     /** 
      * @hidden
      * @deprecated since 340.1, use SetAudioSourceType and SetAudioRenderType instead.
      * @type api
      * @region 自定义音频采集渲染
      * @brief 禁用自定义音频采集和渲染。
      * @notes  <br>
      *      + 如果已开启自定义采集，需要切换至内部采集，必须禁用已开启的自定义音频采集和渲染，然后调用 startAudioCapture{@link #IRtcEngine#startAudioCapture} 手动开启内部采集。<br>
      *      + 要启用自定义音频采集和渲染，调用 enableExternalAudioDevice{@link #IRtcEngine#enableExternalAudioDevice}。
      */
     virtual void disableExternalAudioDevice() = 0;

    /** 
     * @hidden
     * @deprecated since 340.1, use PushExternalAudioFrame with IAudioFrame parameter instead.
     * @type api
     * @region 自定义音频采集渲染
     * @brief 推送自定义音频数据。
     * @param [in] data pcm 数据。音频采样格式必须为 S16。音频缓冲区内的数据格式必须为 PCM，内存大小应该为 `samples × record_format.channel × 2`。
     * @param [in] samples 采样点数量，应该为 enableExternalAudioDevice{@link #IRtcEngine#enableExternalAudioDevice} 中设置的 `record_format.sample_rate / 100`。 例如，当设置采样率为 48000 时， 每次应该推送 480 个采样点。
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + < 0：方法调用失败  <br>
     * @notes  <br>
     *       + 推送自定义采集的音频数据前，必须先调用 enableExternalAudioDevice{@link #IRtcEngine#enableExternalAudioDevice} 开启自定义采集。<br>
     *       + 你必须每 10 us 推送一次数据
     */
     virtual bool pushExternalAudioFrame(int8_t* data, int samples) = 0;

    /** 
     * @hidden
     * @deprecated since 340.1, use PullExternalAudioFrame with IAudioFrame parameter instead.
     * @type api
     * @region 自定义音频采集渲染
     * @brief 拉取远端音频数据。使用 enableExternalAudioDevice{@link #IRtcEngine#enableExternalAudioDevice}
     * 启用自定义音频采集渲染后，可以使用本方法拉取远端音频数据。
     * @param [out] data
     *        pcm 数据，内存大小应该为 samples × playback_format.channel × 2。
     * @param [in] samples
     *        采样点数量，应该为 enableExternalAudioDevice{@link #IRtcEngine#enableExternalAudioDevice} 中设置的
     * playback_format.sample_rate / 100。 当设置采样率为 48000 时， 每次应该拉取 480 个采样点
     * @return  方法调用结果  <br>
     *        + true:方法调用成功  <br>
     *        + false：方法调用失败  <br>
     * @notes  <br>
     *       + 必须是 pcm 数据，拉取间隔是 10ms，音频采样格式为 s16。  <br>
     *       + 该函数运行在用户调用线程内，是一个同步函数  <br>
     */
    virtual bool pullExternalAudioFrame(int8_t* data, int samples) = 0;


    virtual int setAudioSourceType (AudioSourceType type) = 0;

    virtual int setAudioRenderType (AudioRenderType type) = 0;

    virtual bool pushExternalAudioFrame(IAudioFrame* audioFrame) = 0;

    virtual bool pullExternalAudioFrame(IAudioFrame* audioFrame) = 0;

    /** 
     * @hidden
     * @deprecated since 325.1, use IAudioMixingManager instead
     * @type api
     * @region 混音
     * @brief 开始播放音乐文件及混音。
     * @param [in] file_path  <br>
     *        指定需要混音的本地文件的绝对路径。支持音频文件格式有: mp3，aac，m4a，3gp，wav。
     * @param [in] loopback  <br>
     *       + true: 只有本地可以听到混音或替换后的音频流。  <br>
     *       + false: 本地和对方都可以听到混音或替换后的音频流
     * @param [in] replace  <br>
     *       + true: 只推送设置的本地音频文件，不传输麦克风采集的音频。  <br>
     *       + false: 音频文件内容将会和麦克风采集的音频流进行混音
     * @param [in] cycle 指定音频文件循环播放的次数。  <br>
     *       + >0: 循环的次数。  <br>
     *       + -1: 无限循环
     * @return  <br>
     *       + 0: 成功  <br>
     *       + < 0: 失败
     * @notes  <br>
     *      + 该方法指定本地和麦克风采集的音频流进行混音或替换。替换是指用音频文件替换麦克风采集的音频流。  <br>
     *      + 该方法可以选择是否让对方听到本地播放的音频，并指定循环播放的次数。
     * 调用本方法播放音乐文件及混音结束后，应用会收到 onAudioMixingStateChanged{@link #IRtcEngineEventHandler#onAudioMixingStateChanged} 回调。  <br>
     *      + 开始播放音乐文件及混音后，可以调用 stopAudioMixing{@link #IAudioMixingManager#stopAudioMixing} 方法停止播放音乐文件。  <br>
     *      + 该方法混音数据来源外部文件，且支持的文件格式有: mp3，aac，m4a，3gp，wav；而SetAudioPlayoutMixStream{@link
     * #setAudioPlayoutMixStream} 混音的数据来源外部缓存且音频格式为PCM；这两种混音方式可以共存。  <br>
     *      + 单个房间只支持一路音乐文件的播放，多次调用该函数后，只有最后一次调用会生效。  <br>
     *      + 请在房间内调用该方法。
     */
    virtual int startAudioMixing(const char* file_path, bool loopback, bool replace, int cycle) = 0;

    /** 
     * @hidden
     * @deprecated since 325.1, use IAudioMixingManager instead
     * @type api
     * @region 混音
     * @brief 停止播放音乐文件及混音
     * @notes  <br>
     *      + 调用 startAudioMixing{@link #IAudioMixingManager#startAudioMixing}
     * 方法开始播放音乐文件及混音后，调用该方法可以停止播放音乐文件及混音。  <br>
     *      + 请在房间内调用该方法。
     */
    virtual void stopAudioMixing() = 0;

    /** 
     * @hidden
     * @deprecated since 325.1, use IAudioMixingManager instead
     * @type api
     * @region 混音
     * @brief 暂停播放音乐文件
     * @return  <br>
     *        + 0: 成功  <br>
     *        + < 0: 失败
     * @notes  <br>
     *      + 调用 startAudioMixing{@link #IAudioMixingManager#startAudioMixing}
     * 方法开始播放音乐文件及混音后，可以通过调用该方法暂停播放音乐文件。  <br>
     *      + 调用该方法暂停播放音乐文件后，可调用 resumeAudioMixing{@link #IAudioMixingManager#resumeAudioMixing} 方法恢复播放。  <br>
     *      + 请在房间内调用该方法。
     */
    virtual int pauseAudioMixing() = 0;

    /** 
     * @hidden
     * @deprecated since 325.1, use IAudioMixingManager instead
     * @type api
     * @region 混音
     * @brief 恢复播放音乐文件
     * @return  <br>
     *       + 0: 成功  <br>
     *       + < 0: 失败
     * @notes  <br>
     *      + 调用 pauseAudioMixing{@link #IAudioMixingManager#pauseAudioMixing} 方法暂停播放音乐文件后，可以通过调用该方法恢复播放。  <br>
     *      + 请在房间内调用该方法
     */
    virtual int resumeAudioMixing() = 0;

    /** 
     * @hidden
     * @deprecated since 325.1, use IAudioMixingManager instead
     * @type api
     * @region 混音
     * @brief 调节音乐文件的文件音量。为保证更好的音质，建议将 volume 值设为 [0,100]。
     * @param [in] volume 音乐文件播放音量范围为 [0,400]。  <br>
     *       + 0：静音  <br>
     *       + 100：原始音量  <br>
     *       + 400: 最大可调音量 (自带溢出保护)
     * @return  <br>
     *       + 0: 成功  <br>
     *       + < 0: 失败
     * @notes  <br>
     *      + 调用该方法可同时调节的是本地和远端播放音量。仅调节本端音量可使用 adjustAudioMixingPlayoutVolume{@link
     * #adjustAudioMixingPlayoutVolume} ， 仅调节远端音量可使用 adjustAudioMixingPublishVolume{@link
     * #adjustAudioMixingPublishVolume}。  <br>
     *      + 该方法对 adjustAudioMixingPlayoutVolume{@link #adjustAudioMixingPlayoutVolume} 和
     * adjustAudioMixingPublishVolume{@link #adjustAudioMixingPublishVolume} 的音量调节影响是乘积关系。  <br>
     *      + 请在房间内调用该方法。
     */
    virtual int adjustAudioMixingVolume(int volume) = 0;

    /** 
     * @hidden
     * @deprecated since 325.1, use IAudioMixingManager instead
     * @type api
     * @region 混音
     * @brief 调节音乐文件的本地播放音量。为保证更好的音质，建议将 volume 值设为 [0,100]。
     * @param [in] volume 音乐文件播放音量范围为 [0,400]。  <br>
     *       + 0：静音  <br>
     *       + 100：原始音量  <br>
     *       + 400: 最大可调音量 (自带溢出保护)
     * @return  <br>
     *       + 0: 成功  <br>
     *       + < 0: 失败
     * @notes  <br>
     *      + 调用该方法可以调节混音的音乐文件在本地播放的音量大小。如果需要同时调节本地和远端播放音量可使用
     * adjustAudioMixingVolume{@link #adjustAudioMixingVolume} 方法。  <br>
     *      + 请在房间内调用该方法。
     */
    virtual int adjustAudioMixingPlayoutVolume(int volume) = 0;

    /** 
     * @hidden
     * @deprecated since 325.1, use IAudioMixingManager instead
     * @type api
     * @region 混音
     * @brief 调节音乐文件的远端播放音量。为保证更好的音质，建议将 volume 值设为 [0,100]。
     * @param [in] volume 音乐文件播放音量范围为 [0,400]。  <br>
     *       + 0：静音  <br>
     *       + 100：原始音量  <br>
     *       + 400: 最大可调音量 (自带溢出保护)
     * @return  <br>
     *       + 0: 成功  <br>
     *       + < 0: 失败
     * @notes  <br>
     *      + 该方法调节混音的音乐文件在远端播放的音量大小。如果需要同时调节本地和远端播放音量可使用
     * adjustAudioMixingVolume{@link #adjustAudioMixingVolume} 方法。  <br>
     *      + 请在房间内调用该方法。
     */
    virtual int adjustAudioMixingPublishVolume(int volume) = 0;

    /** 
     * @hidden
     * @deprecated since 325.1, use IAudioMixingManager instead
     * @type api
     * @region 混音
     * @brief 获取音乐文件时长
     * @return  <br>
     *       + >0: 成功, 音乐文件时长，单位为毫秒。  <br>
     *       + < 0: 失败
     * @notes <br>
     *       请在房间内调用该方法。
     */
    virtual int getAudioMixingDuration() = 0;

    /** 
     * @hidden
     * @deprecated since 325.1, use IAudioMixingManager instead
     * @type api
     * @region 混音
     * @brief 获取音乐文件播放进度
     * @return  <br>
     *       + >0: 成功, 音乐文件播放进度，单位为毫秒。  <br>
     *       + < 0: 失败
     * @notes <br>
     *       请在房间内调用该方法。
     */
    virtual int getAudioMixingCurrentPosition() = 0;

    /** 
     * @hidden
     * @deprecated since 325.1, use IAudioMixingManager instead
     * @type api
     * @region 混音
     * @brief 设置音频文件的播放位置
     * @param [in] pos
     *        整数。进度条位置，单位为毫秒。
     * @return  <br>
     *       + 0: 成功  <br>
     *       + < 0: 失败
     * @notes  <br>
     *       该方法可以设置音频文件的播放位置，这样你可以根据实际情况从指定的位置播放音乐文件，无需从头到尾完整播放一个音乐文件。
     */
    virtual int setAudioMixingPosition(int pos) = 0;

    /** 
     * @hidden
     * @deprecated since 325.1, use IAudioMixingManager instead
     * @type api
     * @region 混音
     * @brief 获取指定音效文件的文件音量
     * @param [in] sound_id  <br>
     *        音效ID，应用调用者维护，请保证唯一性。确保此处的 sound_id 与  startAudioMixing{@link #IAudioMixingManager#startAudioMixing}
     * 设置的 sound_id 相同。
     * @return  <br>
     *       + >0: 成功，文件音量，音量范围为 [0,400]。  <br>
     *       + < 0: 失败
     * @notes  <br>
     *       请在房间内调用该方法。
     */
    virtual int getEffectVolume(int sound_id) = 0;

    /** 
     * @hidden
     * @deprecated since 325.1, use IAudioMixingManager instead
     * @type api
     * @region 混音
     * @brief 调节指定音效文件的文件音量
     * @param [in] sound_id  <br>
     *        音效ID，应用调用者维护，请保证唯一性。确保此处的 sound_id 与  startAudioMixing{@link #IAudioMixingManager#startAudioMixing}
     * 设置的 sound_id 相同。
     * @param [in] volume  <br>
     *        音乐文件播放音量范围为 [0,400]。默认 100 为原始文件音量
     * @return  <br>
     *       + 0: 成功  <br>
     *       + < 0: 失败
     * @notes
     *       + 该方法调节音效文件在本地和远端播放的音量大小。  <br>
     *       + 请在房间内调用该方法。
     */
    virtual int setVolumeOfEffect(int sound_id, int volume) = 0;

    /** 
     * @hidden
     * @deprecated since 325.1, use IAudioMixingManager instead
     * @type api
     * @region 混音
     * @brief 开始播放指定音效文件。你可以在该方法中设置音效文件的播放次数、音量大小，以及远端用户是否能听到该音效。
     * @param [in] sound_id  <br>
     *        音效ID，应用调用者维护，请保证唯一性。如果已经通过 preloadEffect{@link #preloadEffect}
     * 将音效加载至内存，确保此处的 sound_id 与 preloadEffect{@link #preloadEffect} 设置的 sound_id 相同。
     * @param [in] file_path  <br>
     *        指定需要混音的音频文件名和文件路径名。支持以下音频格式: mp3，aac，m4a，3gp，wav
     * @param [in] loopback  <br>
     *       + true: 只有本地可以听到该音效。  <br>
     *       + false: 本地和远端用户都可以听到该音效。
     * @param  cycle 指定音频文件循环播放的次数。  <br>
     *       + >0：循环的次数。  <br>
     *       + -1：无限循环，直至调用 stopEffect{@link #stopEffect} 或 stopAllEffects{@link #stopAllEffects} 后停止。
     * @param [in] volume  <br>
     *        音效文件播放音量范围为 [0,400]。默认 100 为原始文件音量。
     * @return  <br>
     *       + 0: 成功  <br>
     *       + < 0: 失败
     * @notes  <br>
     *      + 调用该方法播放音效结束后，应用会收到 onAudioMixingStateChanged{@link #IRtcEngineEventHandler#onAudioMixingStateChanged} 回调。  <br>
     *      + 可以多次调用该方法，通过传入不同的音效文件的 sound_id 和
     * file_path，以实现同时播放多个音效文件，实现音效叠加。  <br>
     *      + 可以调用 stopEffect{@link #stopEffect} 方法停止播放指定音效文件。  <br>
     *      + 请在房间内调用该方法。
     */
    virtual int playEffect(int sound_id, const char* file_path, bool loopback, int cycle, int volume) = 0;

    /** 
     * @hidden
     * @deprecated since 325.1, use IAudioMixingManager instead
     * @type api
     * @region 混音
     * @brief 预加载指定音效文件。
     * @param [in] sound_id  <br>
     *        音效ID，应用调用者维护，请保证唯一性。
     * @param [in] file_path  <br>
     *        指定需要混音的音频文件名和文件路径名。支持以下音频格式: mp3，aac，m4a，3gp，wav。
     * @return  <br>
     *        + 0: 成功  <br>
     *        + < 0: 失败
     * @notes  <br>
     *       +
     * 调用该方法预加载播放指定音效文件。预加载操作可以在进房间之前完成（所有混音相关接口，如果没有标注请在房间内调用都可在没有进入房间的时候调用）。如果音效文件很长，加载操作可能会耗时较长，建议应用开发者将预加载操作放在子线程进行。
     * <br>
     *       + 该方法只是预加载播放指定音效文件，只有调用 startAudioMixing{@link #IAudioMixingManager#startAudioMixing}
     * 方法才开始播放指定音效文件。 <br>
     *       + 该方法预加载指定音效文件可以通过 unloadEffect{@link #unloadEffect} 来卸载。
     */
    virtual int preloadEffect(int sound_id, const char* file_path) = 0;

    /** 
     * @hidden
     * @deprecated since 325.1, use IAudioMixingManager instead
     * @type api
     * @region 混音
     * @brief 卸载指定音效文件
     * @param [in] sound_id  <br>
     *        音效ID，应用调用者维护，请保证唯一性。
     * @return  <br>
     *       + 0: 成功  <br>
     *       + < 0: 失败
     * @notes  <br>
     *       + 调用该方法卸载指定音效文件。  <br>
     *       + 如果调用 stopEffect{@link #stopEffect} 方法时，音效文件没有被卸载，SDK会自动调用该方法卸载音效文件。
     */
    virtual int unloadEffect(int sound_id) = 0;

    /** 
     * @hidden
     * @deprecated since 325.1, use IAudioMixingManager instead
     * @type api
     * @region 混音
     * @brief 停止播放指定音效文件
     * @param [in] sound_id  <br>
     *        音效ID，应用调用者维护，请保证唯一性。如果已经通过 preloadEffect{@link #preloadEffect}
     * 将音效加载至内存，确保此处的 sound_id 与  preloadEffect{@link #preloadEffect} 设置的 sound_id 相同。
     * @return  <br>
     *       + 0: 成功  <br>
     *       + < 0: 失败
     * @notes  <br>
     *       + 调用该方法停止播放指定音效文件。  <br>
     *       + 该方法内部会主动调用 unloadEffect{@link #unloadEffect} 来卸载指定音效文。
     */
    virtual int stopEffect(int sound_id) = 0;

    /** 
     * @hidden
     * @deprecated since 325.1, use IAudioMixingManager instead
     * @type api
     * @region 混音
     * @brief 暂停播放指定音效文件
     * @param [in] sound_id  <br>
     *        音效ID，应用调用者维护，请保证唯一性
     * @return  <br>
     *       + 0: 成功  <br>
     *       + < 0: 失败
     * @notes  <br>
     *       调用该方法暂停播放指定音效文件，可以调用 resumeEffect{@link #resumeEffect} 方法恢复播放。
     */
    virtual int pauseEffect(int sound_id) = 0;

    /** 
     * @hidden
     * @deprecated since 325.1, use IAudioMixingManager instead
     * @type api
     * @region 混音
     * @brief 恢复播放指定音效文件
     * @param [in] sound_id  <br>
     *        音效ID，应用调用者维护，请保证唯一性。
     * @return  <br>
     *       + 0: 成功  <br>
     *       + < 0: 失败
     * @notes  <br>
     *      + 调用 pauseEffect{@link #pauseEffect} 方法暂停播放指定音效文件后， 可以通过该方法恢复播放。  <br>
     *      + 调用 pauseAllEffects{@link #pauseAllEffects}
     * 方法暂停所有音效文件的播放后，也可以通过该方法恢复单个音效文件播放。
     */
    virtual int resumeEffect(int sound_id) = 0;

    /** 
     * @hidden
     * @deprecated since 325.1, use IAudioMixingManager instead
     * @type api
     * @region 混音
     * @brief 调节所有音效文件的文件音量
     * @param [in] volume  <br>
     *        音乐文件播放音量范围为 [0,400]。默认 100 为原始文件音量。
     * @notes  <br>
     *      + 该方法调节混音的所有音效文件在本地和远端播放的音量大小。  <br>
     *      + 请在房间内调用该方法。
     */
    virtual void setEffectsVolume(int volume) = 0;

    /** 
     * @hidden
     * @deprecated since 325.1, use IAudioMixingManager instead
     * @type api
     * @region 混音
     * @brief 停止所有音效文件的播放
     * @notes  <br>
     *      该方法停止所有音效文件的播放。
     */
    virtual void stopAllEffects() = 0;

    /** 
     * @hidden
     * @deprecated since 325.1, use IAudioMixingManager instead
     * @type api
     * @region 混音
     * @brief 暂停所有音效文件的播放。
     * @notes  <br>
     *      调用该方法暂停所有音效文件的播放，可调用 resumeAllEffects{@link #resumeAllEffects} 方法恢复播放。
     */
    virtual void pauseAllEffects() = 0;

    /** 
     * @hidden
     * @deprecated since 325.1, use IAudioMixingManager instead
     * @type api
     * @region 混音
     * @brief 恢复所有音效文件的播放
     * @notes  <br>
     *     + 调用该方法恢复所有音效文件的播放。在调用 pauseAllEffects{@link #pauseAllEffects}
     * 暂停所有音效文件的播放后，可以调用该方法可恢复所有音效文件的播放。  <br>
     *     + 调用 pauseEffect{@link #pauseEffect}
     * 方法暂停单个指定音效文件的播放后，也可以调用该方法恢复播放，但是效率太低，不推荐这么使用。
     */
    virtual void resumeAllEffects() = 0;

    /** 
     * @hidden
     * @deprecated since 325.1, use IAudioMixingManager instead
     * @type api
     * @region 混音
     * @brief 卸载所有音效文件
     * @notes  <br>
     *      + 调用该方法卸载所有音效文件。如果引擎被销毁时有音效文件没有被卸载，SDK会自动调用该方法卸载所有音效文件。
     * <br>
     *      + 调用 leaveRoom{@link #leaveRoom}
     * 离开房间后，不会自动调用该方法卸载所有音效文件。如果需要在离开房间后卸载所有音效文件，需要应用主动调用该方法。
     */
    virtual void unloadAllEffects() = 0;

    /** 
     * @hidden
     * @deprecated since 325.1, use IAudioMixingManager instead
     * @type api
     * @region 混音
     * @brief 启动/停止外部音频流混音， 并设置混音数据格式
     * @param [in] enable  <br>
     *       + true: 启用外部音频流混音。  <br>
     *       + false: 停止外部音频流混音。
     * @param [in] sample_rate  <br>
     *        音频采样率，单位HZ。目前支持的采样率有：8000HZ， 16000HZ， 32000HZ， 44100HZ，48000HZ。
     * @param [in] channel_num  <br>
     *        音频声道个数。目前支持单通道(1)，双通道(2)
     * @notes  <br>
     *      + 调用该方法设置外部音频混音的PCM格式，即 pushAudioMixingStreamData{@link #pushAudioMixingStreamData} 的
     * audio_frame 的音频数据格式。  <br>
     *      + 调用该方法混音的数据来源外部缓存，且音频格式为PCM； startAudioMixing{@link #IAudioMixingManager#startAudioMixing}
     * 方法混音数据来源外部文件，且支持的文件格式有: mp3，aac，m4a，3gp，wav。这两种混音方式可以共存。  <br>
     *      + enable 为 false 时，停止外部音频流混音。 或者引擎释放时，SDK内部会停止混音。  <br>
     *      + 该方法启动的外部音频流混音不支持音量调节，暂停，暂停恢复操作。
     */
    virtual void setAudioPlayoutMixStream(bool enable, int sample_rate, int channel_num) = 0;

    /** 
     * @hidden
     * @deprecated since 325.1, use IAudioMixingManager instead
     * @type api
     * @region 混音
     * @brief 获取SDK当前缓冲数据
     * @return  <br>
     *       + >0: 成功，缓冲的音频采样点个数。  <br>
     *       + 0: 失败
     * @notes
     *      调用该方法可以实时获取缓存数据量，并以此数据为基准调整数据推送节奏来避免内存溢出
     */
    virtual int getAudioMixingStreamCachedFrameNum() = 0;

    /** 
     * @hidden
     * @deprecated since 325.1, use IAudioMixingManager instead
     * @type api
     * @region 混音
     * @brief 向SDK推送混音的音频数据
     * @param [in] audio_frame  <br>
     *        PCM音频数据，其格式与 setAudioPlayoutMixStream{@link #setAudioPlayoutMixStream} 保持一致。
     * @param [in] frame_num  <br>
     *        采样点数量，应该为 setAudioPlayoutMixStream{@link #setAudioPlayoutMixStream} 中设置的 sample_rate / 100。
     *        当设置采样率为48000时， 每次应该推送480个采样点
     * @return
     *       + true: 成功  <br>
     *       + false: 失败
     * @notes
     *      + 调用该方法前，必须通过 setAudioPlayoutMixStream{@link #setAudioPlayoutMixStream} 方法设置 audio_frame
     * 的数据格式。  <br>
     *      + 调用该方法前，先通过 getAudioMixingStreamCachedFrameNum
     * 获取缓存的数据量，并调整推送数据的节奏以避免内部缓存溢出导致推送失败。  <br>
     *      + 使用参考建议：首次推送数据，请在应用侧先缓存一定数据（如 200 毫秒），
     * 然后一次性推送过去；此后的推送操作定时 10 毫秒一次，并且每次的音频数据量为 10 毫秒数据量。
     */
    virtual bool pushAudioMixingStreamData(int8_t* audio_frame, int frame_num) = 0;

#ifndef ByteRTC_AUDIO_ONLY

    /** 
     * @hidden(Linux)
     * @type api
     * @region 视频管理
     * @brief 立即开启内部视频采集。默认为关闭状态。  <br>
     *        内部视频采集指：使用 RTC SDK 内置视频采集模块，进行采集。<br>
     *        调用该方法后，本地用户会收到 onVideoDeviceStateChanged{@link #IRtcEngineEventHandler#onVideoDeviceStateChanged} 的回调。  <br>
     *        本地用户在非隐身状态下调用该方法后，房间中的其他用户会收到 onUserStartVideoCapture{@link #IRtcEngineEventHandler#onUserStartVideoCapture} 的回调。
     * @notes  <br>
     *       + 调用 stopVideoCapture{@link #IRtcEngine#stopVideoCapture} 可以停止内部视频采集。否则，只有当销毁引擎实例时，内部视频采集才会停止。  <br>
     *       + 创建引擎后，无论是否发布视频数据，你都可以调用该方法开启内部视频采集。只有当（内部或外部）视频采集开始以后视频流才会发布。  <br>
     *       + 如果需要从自定义视频采集切换为内部视频采集，你必须先关闭自定义采集，再调用此方法手动开启内部采集。
     */
    virtual void startVideoCapture() = 0;

    /** 
     * @hidden(Linux)
     * @type api
     * @region 视频管理
     * @brief 立即关闭内部视频采集。默认为关闭状态。  <br>
     *        内部视频采集指：使用 RTC SDK 内置视频采集模块，进行采集。<br>
     *        调用该方法后，本地用户会收到 onVideoDeviceStateChanged{@link #IRtcEngineEventHandler#onVideoDeviceStateChanged} 的回调。  <br>
     *        非隐身用户进房后调用该方法，房间中的其他用户会收到 onUserStopVideoCapture{@link #IRtcEngineEventHandler#onUserStopVideoCapture} 的回调。
     * @notes  <br>
     *       + 调用 startVideoCapture{@link #IRtcEngine#startVideoCapture} 可以开启内部视频采集。  <br>
     *       + 如果不调用本方法停止内部视频采集，则只有当销毁引擎实例时，内部视频采集才会停止。   <br>
     */
    virtual void stopVideoCapture() = 0;

   /** 
    * @hidden(Linux)
    * @type api
    * @region 视频管理
    * @brief 设置 RTC SDK 内部采集时的视频采集参数。<br>
    *        如果你的项目使用了 SDK 内部采集模块，可以通过本接口指定视频采集参数，包括模式、分辨率、帧率。
    * @param videoCaptureConfig 视频采集参数。参看: VideoCaptureConfig{@link #VideoCaptureConfig}。
    * @return  <br>
    *        + 0: 成功；  <br>
    *        + < 0: 失败；  <br>
    * @notes  <br>
    * + 本接口在引擎创建后可调用，调用后立即生效。建议在调用 startVideoCapture{@link #IRtcEngine#startVideoCapture} 前调用本接口。<br>
    * + 建议同一设备上的不同 Engine 使用相同的视频采集参数。<br>
    * + 如果调用本接口前使用内部模块开始视频采集，采集参数默认为 Auto 模式。
    */
   virtual int setVideoCaptureConfig(const VideoCaptureConfig& videoCaptureConfig) = 0;

    /** 
     * @hidden(Android,iOS)
     * @type api
     * @region 视频管理
     * @brief 调整相机朝向角度，默认0度。
     *        只支持PC端，建议使用场景为 外接摄像头倒置或者倾斜安装时，设置相机安装朝向角度。
     *
     * @param rotation
     */
    virtual void setVideoCaptureRotation(VideoRotation rotation) = 0;

    /** 
     * @type api
     * @region 视频管理
     * @brief 该方法设置视频流发布端是否开启发布多路编码参数不同的视频流的模式。
     * @param [in] enabled 是否开启推送多路视频流模式： <br>
     *        + True：开启 <br>
     *        + False：关闭（默认）
     * @return 方法调用结果： <br>
     *        + 0: 成功 <br>
     *        + <0: 失败
     * @notes <br>
     *        + 你应在进房前或进房后但未发布流时，调用此方法。  <br>
     *        + 开启推送多路视频流模式后，你可以调用 [SetVideoEncoderConfig](#IRtcEngineLite-setvideoencoderconfig-1) 为多路视频流分别设置编码参数。  <br>
     *        + 该功能关闭时，或该功能开启但未设置多路流参数时，默认只发一路视频流，该流的编码参数为：分辨率 640px × 360px，帧率 15fps。
     */
    virtual int enableSimulcastMode(bool enabled) = 0;

    /** 
     * @type api
     * @region 视频管理
     * @brief <span id="IRtcEngineLite-setvideoencoderconfig-1"></span>
     *        视频发布端设置期望发布的最大分辨率视频流参数，包括分辨率、帧率、码率、缩放模式、网络不佳时的回退策略等。  <br>
     *        该接口支持设置一路视频流参数，设置多路参数请使用重载 API：[SetVideoEncoderConfig](#IRtcEngineLite-setvideoencoderconfig-2)。
     * @param [in] max_solution 期望发布的最大分辨率视频流参数。参看 VideoEncoderConfig{@link #VideoEncoderConfig}。
     * @return 方法调用结果： <br>
     *        + 0：成功  <br>
     *        + !0：失败  <br>
     * @notes  <br>
     *        + 若调用该方法设置了期望发布的最大分辨率的流参数之前，已调用 enableSimulcastMode{@link #IRtcEngine#enableSimulcastMode} 开启发布多路视频流的模式，SDK 会根据订阅端的设置自动调整发布的流数以及各路流的参数，其中最大分辨率为设置的分辨率，流数最多 4 条，具体参看[推送多路流](70139)文档；否则仅发布该条最大分辨率的视频流。 <br>
     *        + 调用该方法设置多路视频流参数前，SDK 默认仅发布一条分辨率为 640px × 360px，帧率为 15fps 的视频流。  <br>
     *        + 该方法适用于摄像头采集的视频流，设置屏幕共享视频流参数参看 setScreenVideoEncoderConfig{@link #IRtcEngine#setScreenVideoEncoderConfig}。
     */
    virtual int setVideoEncoderConfig(const VideoEncoderConfig& max_solution) = 0;

    /** 
     * @type api
     * @region 视频管理
     * @brief <span id="IRtcEngineLite-setvideoencoderconfig-2"></span>
     *        视频发布端设置推送多路流时各路流的参数，包括分辨率、帧率、码率、缩放模式、网络不佳时的回退策略等。
     * @param [in] channel_solutions 要推送的多路视频流的参数需注意，所设置的分辨率是各路流的最大分辨率。参看 VideoEncoderConfig{@link #VideoEncoderConfig}。
     * @param [in] solution_num 视频参数数组长度，最多支持设置 3 路参数，超过 3 路时默认取前 3 路的值。当设置了多路参数时，分辨率必须是从大到小排列。
     * @return 方法调用结果： <br>
     *        + 0：成功  <br>
     *        + !0：失败  <br>
     * @notes  <br>
     *        + 该方法是否生效取决于是否同时调用了 enableSimulcastMode{@link #IRtcEngine#enableSimulcastMode} 开启发布多路参数不同的视频流模式。若未开启推送多路流模式，但调用本方法设置了多个分辨率，SDK 默认发布分辨率最大的一条流，多个分辨率的设置会在开启推送多路流模式之后生效。  <br>
     *        + 调用该方法设置多路视频流参数前，SDK 默认仅发布一条分辨率为 640px × 360px，帧率为 15fps 的视频流。  <br>
     *        + 调用该方法设置分辨率不同的多条流后，SDK 会根据订阅端设置的期望订阅参数自动匹配发送的流，具体规则参看[推送多路流](70139)文档。  <br>
     *        + 该方法适用于摄像头采集的视频流，设置屏幕共享视频流参数参看 setScreenVideoEncoderConfig{@link #IRtcEngine#setScreenVideoEncoderConfig}。
     */
    virtual int setVideoEncoderConfig(const VideoEncoderConfig* channel_solutions, int solution_num) = 0;

    /** 
     * @type api
     * @region 共享屏幕管理
     * @brief 为发布的屏幕共享视频流设置期望的编码参数，包括分辨率、帧率、码率、缩放模式、网络不佳时的回退策略等。
     * @param [in] screen_solution 屏幕共享视频流参数。参看 VideoEncoderConfig{@link #VideoEncoderConfig}。
     * @return 方法调用结果： <br>
     *         0：成功  <br>
     *         !0：失败  <br>
     * @notes 调用该方法之前，屏幕共享视频流默认的编码参数为：分辨率 1920px × 1080px，帧率 15fps。
     */
    virtual int setScreenVideoEncoderConfig(const VideoEncoderConfig& screen_solution) = 0;

    /** 
     * @hidden
     * @deprecated since 336, using SetVideoEncoderConfig instead.
     * @type api
     * @region 视频管理
     * @brief 设置推送多路流时的各路视频参数，包括分辨率、帧率、码率、缩放模式、网络不佳时的回退策略等。
     * @param [in] index 视频流属性，参看 StreamIndex{@link #StreamIndex}。
     * @param [in] solutions    要推送的多路视频流参数，参看 VideoSolution{@link #VideoSolution}。
     *                          最大分辨率为 4096px × 4096px，超过或设置的分辨率无法编码时，会导致编码推流失败。<br>
     * @param [in] solution_num 视频参数数组长度。<br>
     *                          最多支持 4 路参数。当设置了多路参数时，分辨率必须是从大到小排列。 <br>
     * @return  <br>
     *        + 0：成功  <br>
     *        + !0：失败  <br>
     * @notes  <br>
     *       + 该接口已废弃，请使用同名新接口代替；若仍需使用该旧接口，请注意无需先调用 `enableSimulcastMode` 开启推送多路流模式。
     *       + 当使用内部采集时，视频采集的分辨率、帧率会根据最大的编码分辨率、帧率进行适配<br>
     *       + 默认的视频编码参数为：分辨率 640px × 360px，帧率 15fps。<br>
     *       + 变更编码分辨率后马上生效，可能会引发相机重启。<br>
     *       + 屏幕流只取视频参数数组的第一组数据。
     */
    virtual int setVideoEncoderConfig(StreamIndex index, const VideoSolution* solutions, int solution_num) = 0;

    /** 
     * @hidden
     * @deprecated since 329.1, use setVideoEncoderConfig instead
     * @type api
     * @region 视频管理
     * @brief 启动推送多路视频流，设置推送多路流时的各路视频参数，
     *        包括分辨率、帧率、码率、缩放模式、网络不佳时的回退策略等。
     * @param [in] solutions 视频参数数组首地址。参看 VideoSolution{@link #VideoSolution}。
     * @param [in] solution_num 视频参数数组长度。 <br>
     *                          最多支持 3 路参数。当设置了多路参数时，分辨率必须是依次减小，从大到小排列的。 <br>
     *                          最大分辨率没有限制。但是如果设置的分辨率无法编码，就会导致编码推流失败。
     * @return  <br>
     *        + 0：成功  <br>
     *        + !0：失败  <br>
     * @notes  <br>
     *        + 当使用内部采集时，视频采集的分辨率、帧率会根据编码参数进行适配。<br>
     *        + 默认的视频编码参数为：分辨率 640px × 360px，帧率 15fps。<br>
     *        + 变更编码分辨率后马上生效，可能会引发相机重启。
     */
    virtual int setVideoEncoderConfig(const VideoSolution* solutions, int solution_num) = 0;

    /** 
     * @hidden(Linux)
     * @type api
     * @region 视频管理
     * @brief 设置本地视频渲染时，使用的视图，并设置渲染模式。
     * @param [in] index 视频流属性, 参看 StreamIndex{@link #StreamIndex}
     * @param [in] canvas 视图信息和渲染模式，参看：VideoCanvas{@link #VideoCanvas}
     * @return  <br>
     *        + 0：成功  <br>
     *        + !0：失败  <br>
     * @notes  <br>
     *        + 你应在加入房间前，绑定本地视图。退出房间后，此设置仍然有效。  <br>
     *        + 如果需要解除绑定，你可以调用本方法传入空视图。
     */
    virtual int setLocalVideoCanvas(StreamIndex index, const VideoCanvas& canvas) = 0;
    /** 
     * @hidden(Linux)
     * @type api
     * @region 视频管理
     * @brief 修改本地视频渲染模式和背景色。
     * @param [in] index 视频流属性, 参看 StreamIndex{@link #StreamIndex}
     * @param [in] renderMode 渲染模式，参看 RenderMode{@link #RenderMode}
     * @param [in] backgroundColor 背景颜色，参看 VideoCanvas{@link #VideoCanvas}.background_color
     * @notes 你可以在本地视频渲染过程中，调用此接口。调用结果会实时生效。
     */
    virtual void updateLocalVideoCanvas(StreamIndex index, const enum RenderMode renderMode, const uint32_t backgroundColor) = 0;

    /** 
     * @type api
     * @hidden(Linux)
     * @region 视频管理
     * @brief 设置渲染指定视频流 `stream_key` 时，使用的视图和渲染模式。 <br>
     *        如果需要解除某个用户的绑定视图，你可以把 `canvas` 设置为空。
     * @param [in] stream_key 参看 RemoteStreamKey{@link #RemoteStreamKey}
     * @param [in] canvas 视图信息和渲染模式，参看：VideoCanvas{@link #VideoCanvas}
     * @return  <br>
     *        + 0：成功  <br>
     *        + !0：失败  <br>
     * @notes  <br>
     *       + 你应在收到 onUserJoined{@link #IRTCRoomEventHandler#onUserJoined} 或 onFirstRemoteVideoFrameDecoded{@link #IRtcEngineEventHandler#onFirstRemoteVideoFrameDecoded} 后，为远端视频绑定渲染视图。这两个回调的差别是：如果启用了视频录制功能，视频录制服务会作为一个哑客户端加入房间，因此其他客户端会收到对应的 onUserJoined{@link #IRTCRoomEventHandler#onUserJoined} 回调，而不会收到 onFirstRemoteVideoFrameDecoded{@link #IRtcEngineEventHandler#onFirstRemoteVideoFrameDecoded} 回调。你不应给录制的哑亚客户端绑定视图（因为它不会发送视频流）。<br>
     *       + 本地用户离开房间时，会解除调用此 API 建立的绑定关系；远端用户离开房间则不会影响。
     */
    virtual void setRemoteStreamVideoCanvas(RemoteStreamKey stream_key, const VideoCanvas& canvas) = 0;
    /** 
     * @hidden(Linux)
     * @type api
     * @region 视频管理
     * @brief 修改远端视频渲染模式和背景色。
     * @param [in] stream_key 远端流信息。参看 RemoteStreamKey{@link #RemoteStreamKey}
     * @param [in] renderMode 渲染模式，参看 RenderMode{@link #RenderMode}
     * @param [in] backgroundColor 背景颜色，参看 VideoCanvas{@link #VideoCanvas}.background_color
     * @notes 你可以在远端视频渲染过程中，调用此接口。调用结果会实时生效。
     */
    virtual void updateRemoteStreamVideoCanvas(RemoteStreamKey stream_key, const enum RenderMode renderMode, const uint32_t backgroundColor) = 0;

    /** 
     * @hidden(Linux)
     * @type api
     * @region 自定义视频采集渲染
     * @brief 将本地视频流与自定义渲染器绑定。
     * @param [in] index 视频流属性。采集的视频流/屏幕视频流，参看 StreamIndex{@link #StreamIndex}
     * @param [in] video_sink 自定义视频渲染器，参看 IVideoSink{@link #IVideoSink}。
     * @param [in] required_format video_sink 适用的视频帧编码格式，参看 PixelFormat{@link #PixelFormat}
     * @notes  <br>
     *        + RTC SDK 默认使用 RTC SDK 自带的渲染器（内部渲染器）进行视频渲染。
     *        + 如果需要解除绑定，必须将 video_sink 设置为 null。退房时将清除绑定状态。
     *        + 一般在收到 onFirstLocalVideoFrameCaptured{@link #IRtcEngineEventHandler#onFirstLocalVideoFrameCaptured} 回调通知完成本地视频首帧采集后，调用此方法为视频流绑定自定义渲染器；然后加入房间。
     */
    virtual void setLocalVideoSink(
            StreamIndex index, IVideoSink* video_sink, IVideoSink::PixelFormat required_format) = 0;

    /** 
     * @hidden(Linux)
     * @type api
     * @region 自定义视频采集渲染
     * @brief 将远端视频流与自定义渲染器绑定。
     * @param [in] stream_key 远端流信息，用于指定需要渲染的视频流来源及属性，参看 RemoteStreamKey{@link #RemoteStreamKey}。
     * @param [in] video_sink 自定义视频渲染器，参看 IVideoSink{@link #IVideoSink}。
     * @param [in] required_format video_sink 适用的视频帧编码格式，参看 PixelFormat{@link #PixelFormat}。
     * @notes  <br>
     *        + RTC SDK 默认使用 RTC SDK 自带的渲染器（内部渲染器）进行视频渲染。
     *        + 该方法进房前后均可以调用。若想在进房前调用，你需要在加入房间前获取远端流信息；若无法预先获取远端流信息，你可以在加入房间并通过 onUserPublishStream{@link #IRTCRoomEventHandler#onUserPublishStream} 回调获取到远端流信息之后，再调用该方法。
     *        + 如果需要解除绑定，必须将 video_sink 设置为 null。退房时将清除绑定状态。
     */
    virtual void setRemoteVideoSink(RemoteStreamKey stream_key, IVideoSink* video_sink,
                                   IVideoSink::PixelFormat required_format) = 0;

    /** 
     * @hidden
     * @deprecated since 336.1, use unpublishStream and publishStream instead.
     * @type api
     * @region 视频管理
     * @brief 停止/启动发送本地视频流，默认不发送。<br>
     *        无论你使用内部视频采集，还是自定义视频采集，你都应使用此接口启动发送本地视频流。<br>
     *        调用该方法后，房间中的其他用户会收到 onUserMuteVideo{@link #IRTCRoomEventHandler#onUserMuteVideo} 的回调。
     * @param  [in] muteState 发送状态，标识是否发送本地视频流，参看 MuteState{@link #MuteState}   <br>
     * @notes <br>
     *        + 本方法只是停止/启动本地视频流的发送，不影响视频采集状态。
     *        + 无论是否开启视频采集，你都可以启动发送本地视频流。如果在采集前启用发送，视频将在采集开始后立即发送。
     */
    virtual void muteLocalVideo(MuteState muteState) = 0;

    /** 
     * @hidden
     * @type api
     * @region 音频管理
     * @brief 发送屏幕共享本地音频数据
     * @param [in] pData
     *        音频数据
     * @param [in] nSamples
     *        采样数
     * @param [in] nBytesPerSample
     *        单个采样数据长度
     * @param [in] nChannels
     *        音频通道数
     * @param [in] sampleRate
     *        采样率
     * @return  <br>
     *        + true  :成功；  <br>
     *        + false :失败；  <br>
     * @notes  <br>
     *       + 暂时只支持 YUV420P 格式的视频帧。  <br>
     *       + 该函数运行在用户调用线程内，即将销毁 RtcEngine 实例前，请停止调用该函数推送屏幕共享数据  <br>
     */
    virtual void pushScreenAudioFrame(const void* pData, const size_t nSamples, const size_t nBytesPerSample,
            const size_t nChannels, const uint32_t sampleRate) = 0;

    /** 
     * @hidden(macOS,Windows,Linux)
     * @type api
     * @region 视频管理
     * @brief 切换视频内部采集时使用的前置/后置摄像头 <br>
     *        调用此接口后，在本地会触发 onVideoDeviceStateChanged{@link #IRtcEngineEventHandler#onVideoDeviceStateChanged} 回调。
     * @param  [in] Camera ID，移动端摄像头。参看 CameraID {@link #CameraID}。
     * @return  <br>
     *        + 0：成功  <br>
     *        + !0：失败  <br>
     * @notes  <br>
     *       + 默认使用前置摄像头。
     *       + 如果你正在使用相机进行视频采集，切换操作当即生效；如果相机未启动，后续开启内部采集时，会打开设定的摄像头。
     *       + 如果本地有多个摄像头且想选择特定工作摄像头可通过 IVideoDeviceManager{@link #IVideoDeviceManager} 来控制。  <br>
     */
    virtual int switchCamera(CameraID camera_id) = 0;

    /** 
     * @type api
     * @region 屏幕共享
     * @brief 推送屏幕视频帧
     * @param [in] frame 设置屏幕视频帧，详见：IVideoFrame{@link #IVideoFrame}。  <br>
     * @return  <br>
     *        + true: 成功；  <br>
     *        + false: 失败；  <br>
     * @notes  <br>
     *       + 暂时只支持 YUV420P 格式的视频帧。  <br>
     *       + 该函数运行在用户调用线程内，即将销毁 RtcEngine 实例前，请停止调用该函数推送屏幕共享数据  <br>
     */
    virtual bool pushScreenFrame(IVideoFrame* frame) = 0;

    /** 
     * @hidden
     * @deprecated since 327.1, use startScreenVideoCapture and publishScreen instead
     * @type api
     * @region 屏幕共享
     * @brief 该方法共享一个窗口或该窗口的部分区域。用户需要在该方法中指定想要共享的窗口 id 。
     * @param [in] window_id
     *        指定待共享的窗口 id，详见：view_t{@link #view_t}
     * @param [in] region_rect
     *        指定共享区域相对于整个窗口的位置，当值都为0时共享整个窗口，详见：Rectangle{@link #Rectangle}
     * @param [in] capture_params
     *        屏幕共享的编码参数配置，详见：DesktopCaptureParameters{@link #DesktopCaptureParameters}
     * @return  <br>
     *        + 0: 成功；  <br>
     *        + -1: 失败；  <br>
     * @notes  <br>
     *       + 本函数和 publishScreen{@link #IRTCRoom#publishScreen} 互斥使用，当调用 stopScreenCapture{@link
     * #stopScreenCapture} 后方可再用 publishScreen{@link #IRTCRoom#publishScreen}。  <br>
     *       + 本函数和 stopScreenCapture{@link #stopScreenCapture} 是成对调用的。  <br>
     *       + 在收到 onFirstRemoteVideoFrameRendered{@link #IRtcEngineEventHandler#onFirstRemoteVideoFrameRendered}
     *         事件后通过调用 setRemoteVideoCanvas{@link #setRemoteVideoCanvas} 或 setRemoteVideoSink{@link #setRemoteVideoSink}
     *         函数来设置远端屏幕共享视图。  <br>
     *       + 本地可调用 setLocalVideoCanvas{@link #IRtcEngine#setLocalVideoCanvas} 或 setLocalVideoSink{@link
     * #setLocalVideoSink} 函数设置本地屏幕共享视图。  <br>
     *       + 也可通过注册 registerVideoFrameObserver{@link #registerVideoFrameObserver} 视频回调对象，监听
     * onLocalScreenFrame{@link #IVideoFrameObserver#onLocalScreenFrame} 本地屏幕视频回调事件和
     * onRemoteScreenFrame{@link #IVideoFrameObserver#onRemoteScreenFrame} 远端屏幕共享视频回调事件来获取原始数据。 <br>
     */
    virtual int startScreenCaptureByWindowId(
            view_t window_id, const Rectangle& region_rect, const DesktopCaptureParameters& capture_params) = 0;

    /** 
     * @hidden
     * @deprecated since 327.1, use startScreenVideoCapture and publishScreen instead
     * @type api
     * @region 屏幕共享
     * @brief 通过指定区域共享屏幕，共享一个屏幕或该屏幕的部分区域。用户需要在该方法中指定想要共享的屏幕区域。
     * @param [in] screen_rect
     *        指定待共享的屏幕相对于虚拟屏的位置，虚拟屏指所有屏幕组成的图像区域，详见：Rectangle{@link #Rectangle}
     * @param [in] region_rect
     *        指定待共享区域相对于screen_rect的位置，详见：Rectangle{@link #Rectangle}
     * @param [in] capture_params
     *        屏幕共享的编码参数配置，详见：DesktopCaptureParameters{@link #DesktopCaptureParameters}
     * @return  <br>
     *        + 0: 成功；  <br>
     *        + -1: 失败；  <br>
     * @notes  <br>
     *       + 本函数和 publishScreen{@link #IRTCRoom#publishScreen} 互斥使用，当调用 stopScreenCapture{@link
     * #stopScreenCapture} 后方可再用 publishScreen{@link #IRTCRoom#publishScreen}。  <br>
     *       + 本函数和 stopScreenCapture{@link #stopScreenCapture} 是成对调用的  <br>
     *       + 在收到 onFirstRemoteVideoFrameRendered{@link #IRtcEngineEventHandler#onFirstRemoteVideoFrameRendered}
     *         事件后通过调用
     * setRemoteVideoCanvas{@link #setRemoteVideoCanvas} 或 setRemoteVideoSink{@link #setRemoteVideoSink}
     * 函数来设置远端屏幕共享视图。  <br>
     *       + 本地可调用 setLocalVideoCanvas{@link #IRtcEngine#setLocalVideoCanvas} 或 setLocalVideoSink{@link
     * #setLocalVideoSink} 函数设置本地屏幕共享视图。  <br>
     *       + 也可通过注册 registerVideoFrameObserver{@link #registerVideoFrameObserver} 视频回调对象，监听
     * onLocalScreenFrame{@link #IVideoFrameObserver#onLocalScreenFrame} 本地屏幕视频回调事件和
     * onRemoteScreenFrame{@link #IVideoFrameObserver#onRemoteScreenFrame} 远端屏幕共享视频回调事件来获取原始数据。 <br>
     */
    virtual int startScreenCaptureByScreenRect(const Rectangle& screen_rect, const Rectangle& region_rect,
            const DesktopCaptureParameters& capture_params) = 0;

    /** 
     * @hidden(iOS,Android)
     * @deprecated since 327.1, use startScreenVideoCapture and publishScreen instead
     * @type api
     * @region 屏幕共享
     * @brief 通过屏幕 id 共享屏幕，共享一个屏幕或该屏幕的部分区域。用户需要在该方法中指定想要共享的屏幕 id 。
     * @param [in] display_id
     *        指定待共享的屏幕 id 。
     * @param [in] region_rect
     *        指定待共享区域相对于整个屏幕的位置，详见：Rectangle{@link #Rectangle}
     * @param [in] capture_params
     *        屏幕共享的编码参数配置，详见：DesktopCaptureParameters{@link #DesktopCaptureParameters}
     * @return  <br>
     *        + 0: 成功；  <br>
     *        + -1: 失败；  <br>
     * @notes 共享一个窗口或该窗口的部分区域。需要在该方法中指定想要共享的窗口 id 。
     */
    virtual int startScreenCaptureByDisplayId(
            unsigned int display_id, const Rectangle& region_rect, const DesktopCaptureParameters& capture_params) = 0;

    /** 
     * @hidden(macOS,Windows,iOS)
     * @deprecated since 327.1, use startScreenVideoCapture and publishScreen instead
     * @type api
     * @region 屏幕共享
     * @brief 通过传入的Context开启屏幕共享。
     * @param [in] context
     *        Android平台是MediaProjection对象，由业务方申请系统录屏权限后获得, iOS上暂未用到，传空即可。
     * @param [in] group_id
     *        iOS 平台需传入 App 和 Extension 共同使用的 group id，Android平台传空即可。
     * @param [in] capture_params
     *        屏幕共享的编码参数配置，详见：DesktopCaptureParameters{@link #DesktopCaptureParameters}
     * @return  <br>
     *        + 0: 成功；  <br>
     *        + -1: 失败；  <br>
     * @notes 开启屏幕共享，移动端专用接口。
     */
    virtual int startScreenCapture(
            void* context, const char* group_id, const DesktopCaptureParameters& capture_params) = 0;

    /** 
     * @hidden(iOS,Android,Linux)
     * @type api
     * @region 屏幕共享
     * @brief 通过 RTC SDK 提供的采集模块采集屏幕视频流时，更新采集区域。
     * @param  [in] region_rect 采集区域。参见 Rectangle{@link #Rectangle}  <br>
     *                          此参数描述了调用此接口后的采集区域，和 startScreenVideoCapture{@link #IRtcEngine#startScreenVideoCapture} 中 `source_info` 设定区域的相对关系。
     * @notes 调用此接口前，必须已通过调用 startScreenVideoCapture{@link #IRtcEngine#startScreenVideoCapture} 开启了内部屏幕流采集。
     */
    virtual void updateScreenCaptureRegion(const Rectangle& region_rect) = 0;

    /** 
     * @hidden
     * @deprecated since 327.1, use setVideoEncoderConfig、updateScreenCaptureHighlightConfig、
     *                  updateScreenCaptureFilterConfig、updateScreenCaptureMouseCursor instead
     * @type api
     * @region 屏幕共享
     * @brief 更新屏幕共享的编码参数配置。
     * @param [in] capture_params
     *        屏幕共享的编码参数配置，详见：DesktopCaptureParameters{@link #DesktopCaptureParameters}
     * @return  <br>
     *        + 0: 成功；  <br>
     *        + -1: 失败；  <br>
     */
    virtual int updateScreenCaptureParameters(const DesktopCaptureParameters& capture_params) = 0;

    /** 
     * @hidden(iOS,Android,Linux)
     * @type api
     * @region 屏幕共享
     * @brief 采集屏幕视频流，用于共享。屏幕视频流包括：屏幕上显示的内容，应用窗口中显示的内容，或虚拟屏幕中显示的内容。<br>
     *        其中，虚拟屏幕中显示的内容仅在 Windows 平台上支持。
     * @param [in] source_info 待共享的屏幕源，参看 ScreenCaptureSourceInfo{@link #ScreenCaptureSourceInfo}。<br>
     *                         你可以调用 getScreenCaptureSourceList{@link #IRtcEngine#getScreenCaptureSourceList} 获得所有可以共享的屏幕源。
     * @param [in] capture_params 共享参数。参看 ScreenCaptureParameters{@link #ScreenCaptureParameters}
     * @return  <br>
     *        + 0: 成功；  <br>
     *        + -1: 失败；  <br>
     * @notes  <br>
     *       + 调用此方法仅开启屏幕流视频采集，不会发布采集到的视频。发布屏幕流视频需要调用 publishScreen{@link #IRTCRoom#publishScreen}。<br>
     *       + 要关闭屏幕视频源采集，调用 stopScreenVideoCapture{@link #IRtcEngine#stopScreenVideoCapture}。  <br>
     *       + 本地用户通过 onVideoDeviceStateChanged{@link #IRtcEngineEventHandler#onVideoDeviceStateChanged} 的回调获取屏幕采集状态，包括开始、暂停、恢复、错误等。  <br>
     *       + 调用成功后，本端会收到 onFirstLocalVideoFrameCaptured{@link #IRtcEngineEventHandler#onFirstLocalVideoFrameCaptured} 回调。  <br>
     *       + 调用此接口前，你可以调用 setVideoEncoderConfig{@link #setVideoEncoderConfig} 设置屏幕视频流的采集帧率和编码分辨率。  <br>
     *       + 在收到 onFirstLocalVideoFrameCaptured{@link #IRtcEngineEventHandler#onFirstLocalVideoFrameCaptured} 回调后通过调用 setLocalVideoCanvas{@link #IRtcEngine#setLocalVideoCanvas} 或 setLocalVideoSink{@link #setLocalVideoSink} 函数设置本地屏幕共享视图。  <br>
     *       + 也可通过注册 registerVideoFrameObserver{@link #registerVideoFrameObserver} 视频回调对象，监听 onLocalScreenFrame{@link #IVideoFrameObserver#onLocalScreenFrame} 本地屏幕视频回调事件。 <br>
     */
    virtual int startScreenVideoCapture(const ScreenCaptureSourceInfo& source_info, const ScreenCaptureParameters& capture_params) = 0;

    /** 
     * @hidden(macOS,Windows,iOS,Linux)
     * @deprecated since 336.1, use startScreenCapture instead
     * @type api
     * @region 屏幕共享
     * @brief 通过传入的Context开启屏幕共享。
     * @param [in] context
     *        Android平台传入MediaProjection对象，由业务方申请系统录屏权限后获得。
     * @return  <br>
     *        + 0: 成功；  <br>
     *        + -1: 失败；  <br>
     * @notes 开启屏幕共享，Android专用接口。
     */
    virtual int startScreenVideoCapture(void* context) = 0;

    /** 
     * @hidden(Linux,iOS)
     * @type api
     * @region 屏幕共享
     * @brief 停止屏幕视频流采集。
     * @notes  <br>
     *       + 要开启屏幕视频流采集，调用 startScreenVideoCapture{@link #IRtcEngine#startScreenVideoCapture}。  <br>
     *       + 调用后，本地用户会收到 onVideoDeviceStateChanged{@link #IRtcEngineEventHandler#onVideoDeviceStateChanged} 的回调。  <br>
     *       + 调用此接口不影响屏幕视频流发布。  <br>
     */
    virtual void stopScreenVideoCapture() = 0;

    /** 
     * @hidden(iOS,Android,Linux)
     * @type api
     * @region 屏幕共享
     * @brief 通过 RTC SDK 提供的采集模块采集屏幕视频流时，更新边框高亮设置。默认展示表框。
     * @param [in] highlight_config 边框高亮设置。参见 HighlightConfig{@link #HighlightConfig}
     * @notes 调用此接口前，必须已通过调用 startScreenVideoCapture{@link #IRtcEngine#startScreenVideoCapture} 开启了内部屏幕流采集。
     */
    virtual void updateScreenCaptureHighlightConfig(const HighlightConfig& highlight_config) = 0;

    /** 
     * @hidden(iOS,Android,Linux)
     * @type api
     * @region 屏幕共享
     * @brief 通过 RTC SDK 提供的采集模块采集屏幕视频流时，更新对鼠标的处理设置。默认采集鼠标。
     * @param [in] capture_mouse_cursor 参看 MouseCursorCaptureState{@link #MouseCursorCaptureState}
     * @notes 调用此接口前，必须已通过调用 startScreenVideoCapture{@link #IRtcEngine#startScreenVideoCapture} 开启了内部屏幕流采集。
     */
    virtual void updateScreenCaptureMouseCursor(MouseCursorCaptureState capture_mouse_cursor) = 0;

    /** 
     * @hidden(iOS,Android,Linux)
     * @type api
     * @region 屏幕共享
     * @brief 通过 RTC SDK 提供的采集模块采集屏幕视频流时，设置需要过滤的窗口。
     * @param [in] ScreenFilterConfig 窗口过滤设置，参看 ScreenFilterConfig{@link #ScreenFilterConfig}  <br>
     * @notes <br>
     *       + 调用此接口前，必须已通过调用 startScreenVideoCapture{@link #IRtcEngine#startScreenVideoCapture} 开启了内部屏幕流采集。<br>
     *       + 本函数在屏幕源类别是屏幕而非应用窗体时才起作用。详见：ScreenCaptureSourceType{@link #ScreenCaptureSourceType}
     */
    virtual void updateScreenCaptureFilterConfig(const ScreenFilterConfig& filter_config) = 0;

    /** 
     * @hidden(Linux)
     * @brief 获取共享对象列表。使用完之后需要调用 release{@link #IScreenCaptureSourceList#release} 接口释放。
     * @return 共享对象列表，包括应用窗口和屏幕。详见 IScreenCaptureSourceList{@link #IScreenCaptureSourceList}。由用户选择其中一个共享对象，并在调用 startScreenVideoCapture{@link #IRtcEngine#startScreenVideoCapture} 时作为参数传给 RTC SDK。
     * @region 屏幕共享
     * @notes  <br>
     *       + 枚举的窗体可作为开启屏幕共享时的输入参数，详见：StartScreenVideoCapture{@link #IRtcEngine#startScreenVideoCapture} <br>
     *       + 本函数仅供PC端使用
     */
    virtual IScreenCaptureSourceList* getScreenCaptureSourceList() = 0;

    /** 
     * @hidden(Linux)
     * @brief 获取共享对象缩略图
     * @region 屏幕共享
     * @param type 屏幕采集对象的类型。详见 ScreenCaptureSourceType{@link #ScreenCaptureSourceType}。
     * @param source_id 屏幕共享对象的 ID，可通过 getScreenCaptureSourceList{@link #getScreenCaptureSourceList} 枚举共享对象列表中获取。详见 view_t{@link #view_t}
     * @param max_width 最大宽度。保持采集对象本身的宽高比不变，将缩略图缩放到指定范围内的最大宽高。如果给出的尺寸与共享对象比例不同，得到的缩略图会有黑边。
     * @param max_height 最大高度。参见 `max_width` 的说明。
     * @return 共享对象缩略图，详见 IVideoFrame{@link #IVideoFrame}。
     */
    virtual IVideoFrame* getThumbnail(
            ScreenCaptureSourceType type, view_t source_id, int max_width, int max_height) = 0;

    /** 
     * @hidden(Linux)
     * @brief 获取应用窗体所属应用的图标。
     * @region 屏幕共享
     * @param source_id 屏幕共享对象的 ID，可通过 getScreenCaptureSourceList{@link #getScreenCaptureSourceList} 枚举共享对象列表中获取。详见 view_t{@link #view_t}
     * @param max_width 最大宽度。返回的图标将是宽高相等的，输入宽高不等时，取二者较小值。宽高范围为 [32,256]，超出该范围将返回 nullptr，默认输出 100 x 100 的图像。
     * @param max_height 最大高度。参见 max_width 的说明。
     * @return 详见 IVideoFrame{@link #IVideoFrame}。当屏幕共享对象为应用窗体时有效，否则返回 nullptr。
     */
     virtual IVideoFrame* getWindowAppIcon(view_t source_id, int max_width = 100, int max_height = 100) = 0;

    /** 
     * @hidden
     * @deprecated since 324.1, use setVideoSourceType instead
     * @type api
     * @region 视频管理
     * @brief 设置是否启用自定义视频采集
     * @param  [in] enable  <br>
     *       + true: 开启  <br>
     *       + false: 关闭
     * @notes  <br>
     *       + 1. 该方法在进房前后均可以调用。  <br>
     *       + 2. 当你已调用 startVideoCapture{@link #IRtcEngine#startVideoCapture} 开启内部采集后，再调用此方法切换至自定义采集时，SDK 会自动关闭内部采集。  <br>
     *       + 3. 当你调用此方法开启自定义采集后，想要切换至内部采集，你必须先调用此方法关闭自定义采集，然后调用 startVideoCapture{@link #IRtcEngine#startVideoCapture} 手动开启内部采集。
     */
    virtual void setExternalVideoSource(bool enable) = 0;

    /** 
     * @hidden
     * @deprecated since 329.1, use setVideoSourceType instead
     * @type api
     * @region 视频管理
     * @brief 切换视频采集方式（内部采集/自定义采集）
     * @param  [in] type 视频采集方式，参看 VideoSourceType{@link #VideoSourceType}
     * @notes  <br>
     *       + 默认使用内部采集。内部采集指：使用 RTC SDK 内置的视频采集机制进行视频采集。 <br>
     *       + 该方法进房前后均可调用。  <br>
     *       + 当你已调用 startVideoCapture{@link #IRtcEngine#startVideoCapture} 开启内部采集后，再调用此方法切换至自定义采集时，SDK 会自动关闭内部采集。  <br>
     *       + 当你调用此方法开启自定义采集后，想要切换至内部采集，你必须先调用此方法关闭自定义采集，然后调用 startVideoCapture{@link #IRtcEngine#startVideoCapture} 手动开启内部采集。
     */
    virtual void setVideoSourceType(VideoSourceType type) = 0;

    /** 
     * @type api
     * @region 视频管理
     * @brief 设置向 SDK 输入的视频源
     *        默认使用内部采集。内部采集指：使用 RTC SDK 内置的视频采集机制进行视频采集。 <br>
     * @param [in] stream_index 视频流的属性，参看 StreamIndex{@link #StreamIndex}
     * @param [in] type 视频输入源类型，参看 VideoSourceType{@link #VideoSourceType}
     * @notes  <br>
     *        + 该方法进房前后均可调用。  <br>
     *        + 当你已调用 startVideoCapture{@link #IRtcEngine#startVideoCapture} 开启内部采集后，再调用此方法切换至自定义采集时，SDK 会自动关闭内部采集。  <br>
     *        + 当你调用此方法开启自定义采集后，想要切换至内部采集，你必须先调用此方法关闭自定义采集，然后调用 startVideoCapture{@link #IRtcEngine#startVideoCapture} 手动开启内部采集。  <br>
     *        + 当你需要向 SDK 推送自定义编码后的视频帧，你需调用该方法将视频源切换至自定义编码视频源。
     */
    virtual void setVideoSourceType(StreamIndex stream_index, VideoSourceType type) = 0;

    /** 
     * @type api
     * @region 视频管理
     * @brief 发送外部源视频数据
     * @param [in] frame 设置视频帧，参看 IVideoFrame{@link #IVideoFrame}。  <br>
     * @notes  <br>
     *       + 支持格式：I420, NV12, RGBA, BGRA, ARGB  <br>
     *       + 该函数运行在用户调用线程内  <br>
     * @notes 推送外部视频帧前，必须调用 setVideoSourceType{@link #setVideoSourceType} 开启外部视频源采集。
     */
    virtual bool pushExternalVideoFrame(IVideoFrame* frame) = 0;

    /**
     * @hidden
     */
    virtual void setupDynamicLayoutRender(IVideoSink* render) = 0;
#endif

    /** 
     * @hidden(macOS,Windows,Linux)
     * @type api
     * @region 音频设备管理
     * @brief 设置音频播放设备，默认使用扬声器。  <br>
     *        音频播放设备发生变化时，会收到 onAudioPlaybackDeviceChanged{@link #IRtcEngineLiteEventHandler#onAudioPlaybackDeviceChanged} 回调。
     * @param [in] device 音频播放设备。参看 AudioPlaybackDevice{@link #AudioPlaybackDevice} <br>
     * @return 方法调用结果  <br>
     *        + 0: 方法调用成功  <br>
     *        + < 0: 方法调用失败  <br>
     * @notes  <br>
     *       + 1. 该接口仅适用于移动设备。  <br>
     *       + 2. 该方法只支持将音视频播放设备设置为听筒或者扬声器。当 App 连接有线或蓝牙音频播放设备时，SDK
     * 会自动切换到有线或蓝牙音频播放设备。主动设置为有线或蓝牙音频播放设备，会返回调用失败。  <br>
     *       + 3.
     * 若连接有线或者蓝牙音频播放设备时，将音频播放设备设置为扬声器或听筒将调用成功，但不会立马切换到扬声器或听筒，会在有线或者蓝牙音频播放设备移除后，根据设置自动切换到听筒或者扬声器。
     * <br>
     *       + 4. 通话前和通话中都可以调用该方法。  <br>
     */
    virtual int setAudioPlaybackDevice(AudioPlaybackDevice device) = 0;

    /** 
     * @hidden(macOS,Windows)
     * @type api
     * @region 音频管理
     * @brief 设置当前音频播放路由。默认使用 setDefaultAudioRoute{@link #IRtcEngine#setDefaultAudioRoute} 中设置的音频路由。  <br>
     *        音频播放路由发生变化时，会收到 onAudioRouteChanged{@link #IRtcEngineEventHandler#onAudioRouteChanged} 回调。  <br>
     * @param [in] route 音频播放路由，参见 AudioRoute{@link #AudioRoute}。不支持 `kAudioRouteDefault`。<br>
     *        当音量类型为媒体音量时，此参数不可设置为 `kAudioRouteEarpiece`；当音量模式为通话音量时，此参数不可设置为 `kAudioRouteHeadsetBluetooth` 或 `kAudioRouteHeadsetUSB`。
     * @return  <br>
     *        + 0: 方法调用成功  <br>
     *        + < 0: 方法调用失败。失败原因参看 ByteRTCMediaDeviceWarning{@link #ByteRTCMediaDeviceWarning} 回调。指定为 `kAudioRouteDefault` 时将会失败。  <br>
     * @notes<br>
     *          + 你需要调用 setAudioScenario{@link #IRtcEngine#setAudioScenario} 将音频场景切换为 `kAudioScenarioTypeCommunication` 后再调用本接口。<br>
     *          + 连接有线或者蓝牙音频播放设备后，音频路由将自动切换至此设备；移除后，音频设备会自动切换回原设备。不同音频场景中，音频路由和发布订阅状态到音量类型的映射关系详见 AudioScenarioType{@link #AudioScenarioType}。
     */
    virtual int setAudioRoute(AudioRoute route) = 0;

    /** 
     * @hidden(macOS,Windows)
     * @type api
     * @region 音频设备管理
     * @brief 将默认的音频播放设备设置为听筒或扬声器。  <br>
     * @param [in] route 音频播放设备。参看 AudioRoute{@link #AudioRoute} <br>
     * @return 方法调用结果  <br>
     *        + 0: 方法调用成功。立即生效。当所有音频外设移除后，音频路由将被切换到默认设备。<br>
     *        + < 0: 方法调用失败。指定除扬声器和听筒以外的设备将会失败。   <br>
     * @notes    <br>
     *        + 进房前后都可以调用。 <br>
     *        + 更多注意事项参见[音频路由](117836)。
     */
    virtual int setDefaultAudioRoute(AudioRoute route) = 0;

    /** 
     * @hidden(macOS,Windows)
     * @type api
     * @region 音频设备管理
     * @brief 获取当前音频播放设备  <br>
     *        音频播放设备发生变化时，会收到 OnAudioRouteChanged{@link #IRtcEngineEventHandler#OnAudioRouteChanged}
     * 回调。
     * @return device 当前音频播放设备。参看 AudioRoute{@link #AudioRoute}
     * @notes  <br>
     *       + 1. 该接口仅适用于移动设备。  <br>
     * <br>
     *       + 2. 通话前和通话中都可以调用该方法。  <br>
     */
    virtual AudioRoute getAudioRoute() = 0;
    /** 
     * @type api
     * @region 音视频回退
     * @brief 设置发布的音视频流的回退选项。  <br>
     *        你可以调用该接口设置网络不佳或设备性能不足时从大流起进行降级处理，以保证通话质量。
     * @param [in] option 本地发布的音视频流回退选项，参看 PublishFallbackOption{@link #PublishFallbackOption}。  <br>
     * @return 方法调用结果： <br>
     *        + 0：成功  <br>
     *        + < 0：失败
     * @notes  <br>
     *        + 该方法仅在调用 enableSimulcastMode{@link #IRtcEngine#enableSimulcastMode} 开启了发送多路视频流的情况下生效。  <br>
     *        + 该方法必须在进房前设置，进房后设置或更改设置无效。  <br>
     *        + 设置回退后，本地发布的音视频流发生回退或从回退中恢复时，远端会收到 onSimulcastSubscribeFallback{@link #IRtcEngineEventHandler#onSimulcastSubscribeFallback} 回调通知。  <br>
     *        + 你可以调用客户端 API 或者在服务端下发策略设置回退。当使用服务端下发配置实现时，下发配置优先级高于在客户端使用 API 设定的配置。
     */
    virtual int setPublishFallbackOption(PublishFallbackOption option) = 0;

    /** 
     * @type api
     * @region 音视频回退
     * @brief 设置订阅的音视频流的回退选项。 <br>
     *        你可调用该接口设置网络不佳或设备性能不足时允许订阅流进行降级或只订阅音频流，以保证通话流畅。
     * @param [in] option 订阅的音视频流回退选项，参看 SubscribeFallbackOption{@link #SubscribeFallbackOption} 。
     * @return 方法调用结果： <br>
     *        + 0：成功  <br>
     *        + < 0：失败
     *  @notes  <br>
     *        + 你必须在进房前设置，进房后设置或更改设置无效。  <br>
     *        + 设置回退选项后，订阅的音视频流发生回退或从回退中恢复时，会收到 onSimulcastSubscribeFallback{@link #IRtcEngineEventHandler#onSimulcastSubscribeFallback} 和 onRemoteVideoSizeChanged{@link #IRtcEngineEventHandler#onRemoteVideoSizeChanged} 回调通知。  <br>
     *        + 你可以调用 API 或者在服务端下发策略设置回退。当使用服务端下发配置实现时，下发配置优先级高于在客户端使用 API 设定的配置。
     */
    virtual int setSubscribeFallbackOption(SubscribeFallbackOption option) = 0;

    /** 
     * @type api
     * @region 音视频回退
     * @brief 设置用户优先级
     * @param [in] user_id 远端用户的 ID
     * @param [in] priority 远端用户的需求优先级，详见枚举类型RemoteUserPriority{@link #RemoteUserPriority}
     * @return 0: 方法调用成功  <br>
     *        + < 0: 方法调用失败  <br>
     * @notes  <br>
     *        + 1. 该方法与 setSubscribeFallbackOption{@link #setSubscribeFallbackOption} 搭配使用。  <br>
     *        + 2. 如果开启了订阅流回退选项，弱网或性能不足时会优先保证收到的高优先级用户的流的质量。  <br>
     *        + 3. 该方法在进房前后都可以使用，可以修改远端用户的优先级。  <br>
     */
    virtual int setRemoteUserPriority(const char* user_id, RemoteUserPriority priority) = 0;

    /** 
     * @type api
     * @region 引擎管理
     * @brief 设置业务标识参数  <br>
     *        可通过 businessId 区分不同的业务场景。businessId 由客户自定义，相当于一个“标签”，可以分担和细化现在 AppId 的逻辑划分的功能，但不需要鉴权。
     * @param [in] business_id  <br>
     *        用户设置的自己的 businessId 值
     *        businessId 只是一个标签，颗粒度需要用户自定义。
     * @return  <br>
     *        + 0： 成功  <br>
     *        + < 0： 失败，具体原因参照 BusinessCheckCode{@link #BusinessCheckCode} 。  <br>
     *        + -6001： 用户已经在房间中。  <br>
     *        + -6002： 输入非法，合法字符包括所有小写字母、大写字母和数字，除此外还包括四个独立字符，分别是：英文句号，短横线，下划线和 @ 。
     * @notes  <br>
     *        + 需要在调用 joinRoom{@link #IRtcEngine#joinRoom} 之前调用，joinRoom{@link #IRtcEngine#joinRoom}之后调用该方法无效。
     */
    virtual int setBusinessId(const char* business_id) = 0;

    /** 
     * @hidden
     * @deprecated since 332.1, use enableVirtualBackground instead
     * @type api
     * @region 视频特效
     * @brief 开启背景并设置背景模式与分割模式
     * @param [in] mode 背景模式，参看 BackgroundMode{@link #BackgroundMode}。  <br>
     * @param [in] divide_model 分割模型，参看 DivideMode{@link #DivideMode}。  <br>
     * @return  <br>
     *        + 0：成功  <br>
     *        + !0：失败  <br>
     */
    virtual int replaceBackground(BackgroundMode mode, DivideMode divide_model) = 0;

    /** 
     * @hidden
     * @deprecated since 332.1, use disableVirtualBackground instead
     * @type api
     * @region 视频特效
     * @brief 关闭背景
     */
    virtual void disableBackground() = 0;

    /** 
     * @deprecated since 329.1, use setLocalVideoMirrorType instead
     * @hidden
     * @type api
     * @region 视频管理
     * @brief 设置采用前置摄像头采集时，是否开启镜像模式。 <br>
     * @param  [in] mirrorMode 是否开启镜像模式
     */
    virtual void setLocalVideoMirrorMode(MirrorMode mirrorMode) = 0;

    /** 
     * @type api
     * @hidden(Windows,MacOS,Linux)
     * @brief 设置采集视频的旋转模式。默认以 App 方向为旋转参考系。<br>
     *        接收端渲染视频时，将按照和发送端相同的方式进行旋转。<br>
     * @param [in] rotationMode 视频旋转参考系为 App 方向或重力方向，参看  VideoRotationMode{@link #VideoRotationMode}
     * @return 0:设置成功
     *        <0:设置失败
     * @notes <br>
     *        + 旋转仅对内部视频采集生效，不适用于外部视频源和屏幕源。
     *        + 调用该接口时已开启视频采集，将立即生效；调用该接口时未开启视频采集，则将在采集开启后生效。
     *        + 更多信息请参考[视频采集方向](https://www.volcengine.com/docs/6348/106458)。
     */
    virtual int setVideoRotationMode(VideoRotationMode rotationMode) = 0;

    /** 
     * @type api
     * @region 视频管理
     * @brief 为采集到的视频流开启镜像
     * @param [in] mirrorType 镜像类型，参看 MirrorType{@link #MirrorType}
     * @notes <br>
     *        + 切换视频源不影响镜像设置。<br>
     *        + 屏幕视频流始终不受镜像设置影响。<br>
     *        + 该接口调用前，各视频源的初始状态如下：<br>
     *        <table>
     *           <tr><th></th><th>前置摄像头</th><th>后置摄像头</th><th>自定义采集视频源</th> <th>桌面端摄像头</th> </tr>
     *           <tr><td>移动端</td><td>本地预览镜像，编码传输不镜像</td><td> 本地预览不镜像，编码传输不镜像 </td><td> 本地预览不镜像，编码传输不镜像 </td><td>/</td></tr>
     *           <tr><td>桌面端</td><td>/</td><td>/</td><td> 本地预览不镜像，编码传输不镜像 </td><td> 本地预览镜像，编码传输不镜像 </td></tr> <br>
     *        </table>
     */
    virtual void setLocalVideoMirrorType(MirrorType mirrorType) = 0;

    /** 
     * @type api
     * @region 音视频处理
     * @brief 开启/关闭基础美颜
     * @param [in] enable 基础美颜开关 <br>
     *        + true: 开启基础美颜 <br>
     *        + false: 关闭基础美颜（默认） <br>
     * @return  <br>
     *        + 0: 开启/关闭成功。 <br>
     *        + 1000: 未集成特效 SDK。 <br>
     *        + 1001: RTC SDK 版本不支持此功能。 <br>
     *        + 1002: 特效 SDK 当前版本不支持此功能，建议使用特效 SDK V4.3.1 版本。 <br>
     *        + 1003: 联系技术支持人员。 <br>
     *        + 1004: 正在下载相关资源，下载完成后生效。 <br>
     *        + <0: 调用失败，特效 SDK 内部错误，具体错误码请参考[错误码表](https://www.volcengine.com/docs/5889/61813)。  <br>
     * @notes <br>
     *        + 本方法不能与高级视频特效接口共用。如已购买高级视频特效，建议调用 enableVideoEffect{@link #IVideoEffect#enableVideoEffect} 使用高级特效、贴纸功能等。 <br>
     *        + 使用此功能需要集成特效 SDK，建议使用特效 SDK V4.3.1+ 版本。 <br>
     *        + 调用 setBeautyIntensity{@link #IRtcEngine#setBeautyIntensity} 设置基础美颜强度。若在调用本方法前没有设置美颜强度，则初始美白、磨皮、锐化强度均为 0.5。 <br>
     *        + 本方法仅适用于视频源，不适用于屏幕源。 <br>
     */
    virtual int enableEffectBeauty(bool enable) = 0;

    /** 
     * @type api
     * @region 音视频处理
     * @brief 调整基础美颜强度
     * @param [in] beautyMode 基础美颜模式，参看 EffectBeautyMode{@link #EffectBeautyMode}。
     * @param [in] intensity 美颜强度，取值范围为 [0,1]。强度为 0 表示关闭，默认强度为 0.5。
     * @return  <br>
     *        + 0: 开启成功。 <br>
     *        + 1000: 未集成特效 SDK。 <br>
     *        + 1001: RTC SDK 版本不支持此功能。 <br>
     *        + <0: 调用失败，特效 SDK 内部错误，具体错误码请参考[错误码表](https://www.volcengine.com/docs/5889/61813)。  <br>
     * @notes <br>
     *        + 若在调用 enableEffectBeauty{@link #IRtcEngine#enableEffectBeauty} 前设置美颜强度，则对应美颜功能的强度初始值会根据设置更新。 <br>
     *        + 销毁引擎后，美颜功能强度恢复默认值。 <br>
     */
    virtual int setBeautyIntensity(EffectBeautyMode beautyMode, float intensity) = 0;

    /** 
     * @hidden
     * @type api
     * @region 视频特效
     * @brief 获取视频特效接口
     * @return 视频特效接口指针
     */
    virtual IVideoEffect* getVideoEffectInterface() = 0;

    /** 
     * @hidden
     * @type api
     * @region 视频管理
     * @brief 获取相机控制接口
     * @return 相机控制接口指针
     */
    virtual ICameraControl* getCameraControl() = 0;

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
     *       + 该方法与 setEncryptInfo{@link #IRtcEngine#setEncryptInfo} 为互斥关系，只能选择自定义加密方式或者默认加密方式。最终生效的加密方式取决于最后一个调用的方法。  <br>
     *       + 该方法必须在进房之前调用，可重复调用，以最后调用的参数作为生效参数。  <br>
     *       + 无论加密或者解密，其对原始数据的长度修改，需要控制在 90% ~ 120% 之间，即如果输入数据为 100 字节，则处理完成后的数据必须在 90 至 120 字节之间，如果加密或解密结果超出该长度限制，则该音视频帧会被丢弃。  <br>
     *       + 数据加密/解密为串行执行，因而视实现方式不同，可能会影响到最终渲染效率。是否使用该方法，需要由使用方谨慎评估。
     * <br>
     */
    virtual void setCustomizeEncryptHandler(IEncryptHandler* handler) = 0;

    virtual void setVideoOrientation(VideoOrientation orientation) = 0;

    /** 
    * @type api
    * @region 音频数据回调
     * @brief 开启音频回调
     * @param [in] method 音频回调方法，参看 AudioFrameCallbackMethod{@link #AudioFrameCallbackMethod}。  <br>
     *               当音频回调方法设置为 `kAudioFrameCallbackRecord`、`kAudioFrameCallbackPlayback`、`kAudioFrameCallbackMixed`、`kAudioFrameCallbackRecordScreen`时，你需要在参数 `format` 中指定准确的采样率和声道，暂不支持设置为自动。  <br>
     *               当音频回调方法设置为 `kAudioFrameCallbackRemoteUser`时，暂不支持音频参数格式中设置准确的采样率和声道，你需要设置为自动。
     * @param [in] format 音频参数格式，参看 AudioFormat{@link #AudioFormat}。
     * @notes 开启音频回调并调用 registerAudioFrameObserver{@link #IRtcEngine#registerAudioFrameObserver} 后，IAudioFrameObserver{@link #IAudioFrameObserver} 会收到对应的音频回调。两者调用顺序没有限制且相互独立。  <br>
    */
    virtual void enableAudioFrameCallback(AudioFrameCallbackMethod method, AudioFormat format) = 0;

    /** 
     * @type api
     * @region 音频数据回调
     * @brief 关闭音频回调
     * @param [in] method 音频回调方法，参看 AudioFrameCallbackMethod{@link #AudioFrameCallbackMethod}。
     * @notes 该方法需要在调用 enableAudioFrameCallback{@link #IRtcEngine#enableAudioFrameCallback} 之后调用。
     */
    virtual void disableAudioFrameCallback(AudioFrameCallbackMethod method) = 0;

    /** 
     * @type api
     * @region 音频数据回调
     * @brief 注册音频数据回调观察者。  <br>
     * @param [in] observer 音频数据观察者，参看 IAudioFrameObserver{@link #IAudioFrameObserver}。如果传入 null，则取消注册。
     * @return  <br>
     *        + 0: 方法调用成功 <br>
     *        + < 0: 方法调用失败 <br>
     * @notes 注册音频数据回调观察者并调用 enableAudioFrameCallback{@link #IRtcEngine#enableAudioFrameCallback} 后，IAudioFrameObserver{@link #IAudioFrameObserver} 会收到对应的音频回调。
     */
    virtual void registerAudioFrameObserver(IAudioFrameObserver* observer) = 0;
    /** 
     * @type api
     * @hidden
     * @deprecated since 342, use registerAudioProcessor instead.
     * @region 音频处理
     * @brief 设置自定义音频处理器。  <br>
     *        使用该处理器，你可以调用 processAudioFrame{@link #IAudioProcessor#processAudioFrame} 对 RTC SDK 采集得到的音频帧进行自定义处理，并将处理后的音频帧用于 RTC 音视频通信。  <br>
     *        SDK 只持有 processor 的弱引用，你应保证其生命周期。
     * @param [in] processor 自定义音频处理器，参看 IAudioProcessor{@link #IAudioProcessor}。如果传入 null，则不对 RTC SDK 采集得到的音频帧进行自定义处理。
     * @param [in] audioFormat 自定义音频参数格式，参看 AudioFormat{@link #AudioFormat}，SDK 将按指定设置给出音频帧。
     * @notes 重复调用此接口时，仅最后一次调用生效。效果不会叠加。
     */
    virtual void registerLocalAudioProcessor(IAudioProcessor* processor, AudioFormat audioFormat) = 0;
   /** 
    * @type api
    * @brief 注册自定义音频处理器。<br>
    *        注册完成后，你可以调用 enableAudioProcessor{@link #IRtcEngine#enableAudioProcessor}，对本地采集或接收到的远端音频进行处理。
    * @param [in] processor 自定义音频处理器，详见 IAudioFrameProcessor{@link #IAudioFrameProcessor}。<br>
    *        SDK 只持有 processor 的弱引用，你应保证其生命周期。
    * @notes 重复调用此接口时，仅最后一次调用生效。
    */
   virtual void registerAudioProcessor(IAudioFrameProcessor* processor) = 0;
   /** 
    * @type api
    * @brief 获取本地采集的音频帧或接收到的远端音频帧，进行自定义处理。
    * @param [in] method 音频帧类型，参看 AudioProcessorMethod{@link #AudioProcessorMethod}。通过多次调用此接口，可以对不同的音频帧进行自定义处理。<br>
    *        选择不同的值时，收到的回调不同：<br>
    *        + 选择本地采集的音频时，会收到 onProcessRecordAudioFrame{@link #IAudioFrameProcessor#onProcessRecordAudioFrame} <br>
    *        + 选择远端音频流的混音音频时，会收到 onProcessPlayBackAudioFrame{@link #IAudioFrameProcessor#onProcessPlayBackAudioFrame} <br>
    *        + 选择远端音频流时，会收到 onProcessRemoteUserAudioFrame{@link #IAudioFrameProcessor#onProcessRemoteUserAudioFrame} <br>
    * @param [in] format 设定自定义处理时获取的音频帧格式，参看 AudioFormat{@link #AudioFormat}。
    * @notes <br>
    *        + 在调用此接口前，你需要调用 registerAudioProcessor{@link #IRtcEngine#registerAudioProcessor} 注册自定义音频处理器。<br>
    *        + 要关闭音频自定义处理，调用 disableAudioProcessor{@link #IRtcEngine#disableAudioProcessor}。
    */
   virtual void enableAudioProcessor(AudioProcessorMethod method, AudioFormat format) = 0;
    /** 
    * @type api
    * @brief 关闭自定义音频处理。
    * @param [in] method 音频帧类型，参看 AudioProcessorMethod{@link #AudioProcessorMethod}。
    */
   virtual void disableAudioProcessor(AudioProcessorMethod method) = 0;
    /** 
     * @hidden
     * @deprecated
     * @type api
     * @region 视频数据回调
     * @brief 注册视频数据回调观察者
     * @param [in] observer 数据回调函数，详见 IVideoFrameObserver{@link #IVideoFrameObserver}，将参数设置为 nullptr 则取消注册。
     * @notes 该方法可以在任意时间调用，建议在 joinRoom{@link #IRtcEngine#joinRoom} 前。
     */
    virtual void registerVideoFrameObserver(IVideoFrameObserver* observer) = 0;

    /** 
      * @type api
      * @region 视频处理
      * @brief 设置自定义视频前处理器。<br>
      *        使用这个视频前处理器，你可以调用 processVideoFrame{@link #IVideoProcessor#processVideoFrame} 对 RTC SDK 采集得到的视频帧进行前处理，并将处理后的视频帧用于 RTC 音视频通信。
      * @param [in] processor 自定义视频处理器，详见 IVideoProcessor{@link #IVideoProcessor}。如果传入 null，则不对 RTC SDK 采集得到的视频帧进行前处理。<br>
      *        SDK 只持有 processor 的弱引用，你应保证其生命周期。
      * @param [in] config 自定义视频前处理器适用的设置，详见 VideoPreprocessorConfig{@link #VideoPreprocessorConfig}。<br>
      *               当前，`config` 中的 `required_pixel_format` 仅支持：`kVideoPixelFormatI420` 和 `kVideoPixelFormatUnknown`：<br>
      *               + 设置为 `kVideoPixelFormatUnknown` 时，RTC SDK 给出供 processor 处理的视频帧格式即采集的格式。
      *                 你可以通过 frameType{@link #IVideoFrame#frameType} 和 pixelFormat{@link #IVideoFrame#pixelFormat} 获取实际采集的视频帧格式和像素类型。<br>
      *               + 设置为 `kVideoPixelFormatI420` 时，RTC SDK 会将采集得到的视频帧转变为对应的格式，供前处理使用。<br>
      *               + 设置为其他值时，此方法调用失败。
      * @return <br>
      *         + 0：方法调用成功 <br>
      *         + !0：方法调用失败 <br>
      * @notes  <br>
      *        + 对于 Windows 平台，经前处理返回的视频帧格式仅支持 `kVideoPixelFormatI420` <br>
      *        + 对于 Windows 平台，将 `config` 中的 required_pixel_format 设置为 `kVideoPixelFormatI420`，可以通过避免格式转换带来一些性能优化。<br>
      *        + 重复调用此接口时，仅最后一次调用生效。效果不会叠加。
      */
     virtual int registerLocalVideoProcessor(IVideoProcessor* processor, VideoPreprocessorConfig config) = 0;

    /** 
     * @hidden
     * @deprecated since 326.1, use sendSEIMessage instead
     * @type api
     * @region 视频数据回调
     * @brief 注册 metadata 观察者，用于接收或发送 metadata，底层通过在视频帧中添加 SEI 数据实现该功能。  <br>
     *        注册观察者后，发送的视频帧里面没有 SEI 信息， 会触发 onReadyToSendMetadata{@link
     * #IMetadataObserver#onReadyToSendMetadata} 回调。  <br> 注册观察者后，接收的视频帧里面有 SEI 信息，会触发接收
     * onMetadataReceived{@link #IMetadataObserver#onMetadataReceived} 回调。  <br>
     * @param [in] observer metadata 观察者，详见：IMetadataObserver{@link #IMetadataObserver}
     * @notes  <br>
     *      + 使用视频自定义采集与渲染时，可以直接在视频帧中添加与获取 metadata，不建议使用本接口。
     *      + 本接口支持动态取消注册，将参数设置为 nullptr 取消注册。  <br>
     */
    virtual void registerMetadataObserver(IMetadataObserver* observer) = 0;

    /** 
     * @type api
     * @region 视频管理
     * @brief 在视频通信时，通过视频帧发送 SEI 数据。
     * @param [in] stream_index 媒体流类型，参看 StreamIndex{@link #StreamIndex}
     * @param [in] message SEI 消息。长度不超过 4 kB。<br>
     * @param [in] length SEI 消息长度。<br>
     * @return <br>
     *        + >=0: 将被添加到视频帧中的 SEI 的数量  <br>
     *        + < 0: 发送失败
     * @notes <br>
     *        + 你可以通过此接口对 RTC SDK 内部采集的视频帧添加 SEI。对于采用自定义采集获得的视频帧：如果原视频帧中没有添加 SEI 数据，那么你可以调用此接口为其中添加 SEI 信息后，进行编码传输；如果原视频帧中已添加了 SEI 数据，那么，调用此接口不生效。<br>
     *        + 如果调用此接口之后的 2s 内，没有可带 SEI 的视频帧（比如没有开启视频采集和传输），那么，SEI 数据不会被加进视频帧中。
     *        + 消息发送成功后，远端会收到 onSEIMessageReceived{@link #IRtcEngineEventHandler#onSEIMessageReceived} 回调。
     */
    virtual int sendSEIMessage(StreamIndex stream_index, const uint8_t* message, int length, int repeat_count) = 0;
    virtual int sendSEIMessage(StreamIndex stream_index, const uint8_t* message, int length, int repeat_count, SEICountPerFrame mode) = 0;

    /** 
     * @hidden
     * @deprecated
     * @type api
     * @region 房间管理
     * @brief 设置引擎自动发布属性
     * @param [in] engine
     *       要设置的引擎，详见：{@link #IRtcEngine}
     * @param [in] auto_publish
     *       是否自动发布流，默认是true自动发布，设置false时可通过engine->publish()、engine->unpublish()来发布和取消发布本地流
     * @notes
     * 设置引擎是否自动发布用户的本地流，必须在joinChannel前调用。engine引擎默认auto_publish为true。当auto_publish为true时engine->publish()、
     * engine->unpublish()接口不应当被调用。
     */
    virtual void enableAutoPublish(bool auto_publish) = 0;

    /** 
     * @hidden(Linux)
     * @type api
     * @region 视频设备管理
     * @brief 创建视频设备管理实例
     * @return 视频设备管理实例，详见IVideoDeviceManager{@link #IVideoDeviceManager}
     */
    virtual IVideoDeviceManager* getVideoDeviceManager() = 0;

    /** 
     * @hidden(Linux)
     * @type api
     * @region 音频管理
     * @brief 设备音频管理接口创建
     * @return 音频设备管理接口
     */
    virtual IAudioDeviceManager* getAudioDeviceManager() = 0;

    /** 
     * @type api
     * @region 范围语音
     * @brief 获取范围语音接口实例。
     * @return 方法调用结果： <br>
     *        + IRangeAudio：成功，返回一个 IRangeAudio{@link #IRangeAudio} 实例。  <br>
     *        + nullptr：失败，当前 SDK 不支持范围语音功能。
     * @notes 首次调用该方法须在创建房间后、加入房间前。
     */
    virtual IRangeAudio* getRangeAudio() = 0;
    /** 
     * @type api
     * @region 空间音频
     * @brief 获取空间音频接口实例。  <br>
     * @return 方法调用结果：  <br>
     *        + ISpatialAudio：成功，返回一个 ISpatialAudio{@link #ISpatialAudio} 实例。  <br>
     *        + nullptr：失败，当前 SDK 不支持空间音频功能。
     * @notes  <br>
     *        + 首次调用该方法须在创建房间后、加入房间前。 空间音频相关 API 和调用时序详见[空间音频](https://www.volcengine.com/docs/6348/93903)。 <br>
     *        + 只有在使用支持真双声道播放的设备时，才能开启空间音频效果；  <br>
     *        + 机型性能不足可能会导致音频卡顿，使用低端机时，不建议开启空间音频效果；  <br>
     *        + SDK 最多支持 30 个用户同时开启空间音频功能。
     */
    virtual ISpatialAudio* getSpatialAudio() = 0;

    /** 
     * @hidden
     * @type api
     * @region 音频数据回调
     * @brief 注册音频数据回调观察者。
     * @param [in] observer 音频数据回调观察者，详见 IRemoteAudioFrameObserver{@link #IRemoteAudioFrameObserver}
     * @notes  <br>
     *         注册该回调，可以收到单个远端用户的 PCM 数据。
     */
    virtual void registerRemoteAudioFrameObserver(IRemoteAudioFrameObserver* observer) = 0;

    /** 
     * @type api
     * @region 本地录制
     * @brief 该方法将通话过程中的音视频数据录制到本地的文件中。
     * @param [in] type 流属性，指定录制主流还是屏幕流，参看 StreamIndex{@link #StreamIndex}
     * @param [in] config 本地录制参数配置，参看 RecordingConfig{@link #RecordingConfig}
     * @param [in] recording_type 本地录制的媒体类型，参看 RecordingType{@link #RecordingType}
     * @return  <br>
     *        + 0: 正常
     *        + -1: 参数设置异常
     *        + -2: 当前版本 SDK 不支持该特性，请联系技术支持人员
     * @notes  <br>
     *        + 调用该方法后，你会收到 onRecordingStateUpdate{@link #IRtcEngineEventHandler#onRecordingStateUpdate} 回调。  <br>
     *        + 如果录制正常，系统每秒钟会通过 onRecordingProgressUpdate{@link #IRtcEngineEventHandler#onRecordingProgressUpdate}
     * 回调通知录制进度。
     */
    virtual int startFileRecording(StreamIndex type, RecordingConfig config, RecordingType recording_type) = 0;

    /** 
     * @type api
     * @region 本地录制
     * @brief 停止本地录制
     * @param [in] type 流属性，指定停止主流或者屏幕流录制，参看 StreamIndex{@link #StreamIndex}
     * @notes  <br>
     *        + 调用 startFileRecording{@link #IRtcEngine#startFileRecording} 开启本地录制后，你必须调用该方法停止录制。  <br>
     *        + 调用该方法后，你会收到 onRecordingStateUpdate{@link #IRtcEngineEventHandler#onRecordingStateUpdate} 回调提示录制结果。
     */
    virtual void stopFileRecording(StreamIndex type) = 0;
    /** 
     * @type api
     * @hidden(Linux)
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
     * @region 引擎管理
     * @brief 设置运行时的参数
     * @param [in] json_string  json 序列化之后的字符串
     * @notes
     */
    virtual void setRuntimeParameters(const char * json_string) = 0;

    /** 
     * @type api
     * @region 语音识别服务
     * @brief 开启自动语音识别服务。该方法将识别后的用户语音转化成文字，并通过 onMessage{@link #IRTCASREngineEventHandler#onMessage}
     * 事件回调给用户。
     * @param [in] asr_config 校验信息，参看 RTCASRConfig{@link #RTCASRConfig}
     * @param [in] handler 语音识别服务使用状态回调，参看 IRTCASREngineEventHandler{@link #IRTCASREngineEventHandler}
     */
    virtual void startASR(const RTCASRConfig& asr_config, IRTCASREngineEventHandler* handler) = 0;

    /** 
     * @type api
     * @region 语音识别服务
     * @brief 关闭语音识别服务
     */
    virtual void stopASR() = 0;
    /** 
     * @type api
     * @region 引擎管理
     * @brief 将用户反馈的问题上报到 RTC
     * @param [in] types 预设问题列表，参看 ProblemFeedbackOption{@link #ProblemFeedbackOption}
     * @param [in] info 预设问题以外的其他问题的具体描述，房间信息。参看 ProblemFeedbackInfo{@link #ProblemFeedbackInfo}
     * @return <br>
     *         + 0: 上报成功  <br>
     *         + -1: 上报失败，还没加入过房间 <br>
     *         + -2: 上报失败，数据解析错误  <br>
     *         + -3: 上报失败，字段缺失  <br>
     * @notes 如果用户上报时在房间内，那么问题会定位到用户当前所在的一个或多个房间；
     *        如果用户上报时不在房间内，那么问题会定位到引擎此前退出的房间。
     */
    virtual int feedback(uint64_t types, const ProblemFeedbackInfo* info) = 0;

    /** 
     * @type api
     * @region 混音
     * @brief 混音管理接口创建
     * @return 混音管理实例，详见IAudioMixingManager{@link #IAudioMixingManager}
     */
    virtual IAudioMixingManager* getAudioMixingManager() = 0;

    /** 
     * @type api
     * @region 实时消息通信
     * @brief 必须先登录，才能发送房间外点对点消息和向应用服务器发送消息<br>
     *        在调用本接口登录后，如果想要登出，需要调用 logout{@link #IRtcEngine#logout}。  <br>
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
     * @notes  <br>
     *       + 在调用本接口登录后，如果想要登出，需要调用 logout{@link #IRtcEngine#logout}。  <br>
     *       + 本地用户调用此方法登录后，会收到 onLoginResult{@link #IRtcEngineEventHandler#onLoginResult} 回调通知登录结果，远端用户不会收到通知。
     */
    virtual int64_t login(const char* token, const char* uid) = 0;
    /** 
     * @type api
     * @region 实时消息通信
     * @brief 调用本接口登出后，无法调用房间外消息以及端到服务器消息相关的方法或收到相关回调。
     * @notes  <br>
     *       + 调用本接口登出前，必须先调用 login{@link #IRtcEngine#login} 登录。  <br>
     *       + 本地用户调用此方法登出后，会收到 onLogout{@link #IRtcEngineEventHandler#onLogout} 回调通知结果，远端用户不会收到通知。
     */
    virtual void logout() = 0;
    /** 
     * @type api
     * @region 实时消息通信
     * @brief 更新用户用于登录的 Token  <br>
     *        Token 有一定的有效期，当 Token 过期时，需调用此方法更新登录的 Token 信息。  <br>
     *        调用 login{@link #IRtcEngine#login} 方法登录时，如果使用了过期的 Token 将导致登录失败，并会收到 onLoginResult{@link #IRtcEngineEventHandler#onLoginResult} 回调通知，错误码为 kLoginErrorCodeInvalidToken。此时需要重新获取 Token，并调用此方法更新 Token。
     * @param [in] token  <br>
     *        更新的动态密钥
     * @notes  <br>
     *       + 如果 Token 无效导致登录失败，则调用此方法更新 Token 后，SDK 会自动重新登录，而用户不需要自己调用 login{@link #IRtcEngine#login} 方法。  <br>
     *       + Token 过期时，如果已经成功登录，则不会受到影响。Token 过期的错误会在下一次使用过期 Token 登录时，或因本地网络状况不佳导致断网重新登录时通知给用户。
     */
    virtual void updateLoginToken(const char* token) = 0;
    /** 
     * @type api
     * @region 实时消息通信
     * @brief 设置应用服务器参数  <br>
     *        客户端调用 sendServerMessage{@link #IRtcEngine#sendServerMessage} 或 sendServerBinaryMessage{@link #IRtcEngine#sendServerBinaryMessage} 发送消息给业务服务器之前，必须设置有效签名和业务服务器地址。
     * @param [in] signature  <br>
     *        动态签名  <br>
     *        应用服务器会使用该签名对请求进行鉴权验证。
     * @param [in] url  <br>
     *        应用服务器的地址
     * @notes  <br>
     *       + 用户必须调用 login{@link #IRtcEngine#login} 登录后，才能调用本接口。  <br>
     *       + 调用本接口后，SDK 会使用 onServerParamsSetResult{@link #IRtcEngineEventHandler#onServerParamsSetResult} 返回相应结果。
     */
    virtual void setServerParams(const char* signature, const char* url) = 0;
    /** 
     * @type api
     * @region 实时消息通信
     * @brief 查询对端用户或本端用户的登录状态
     * @param [in] peer_user_id  <br>
     *        需要查询的用户 ID
     * @notes  <br>
     *       + 必须调用 login{@link #IRtcEngine#login} 登录后，才能调用本接口。  <br>
     *       + 调用本接口后，SDK 会使用 onGetPeerOnlineStatus{@link #IRtcEngineEventHandler#onGetPeerOnlineStatus} 回调通知查询结果。  <br>
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
     *       + 在发送房间外文本消息前，必须先调用 login{@link #IRtcEngine#login} 完成登录。  <br>
     *       + 用户调用本接口发送文本信息后，会收到一次 onUserMessageSendResultOutsideRoom{@link #IRtcEngineEventHandler#onUserMessageSendResultOutsideRoom} 回调，得知消息是否成功发送。  <br>
     *       + 若文本消息发送成功，则 uid 所指定的用户会通过 onUserMessageReceivedOutsideRoom{@link #IRtcEngineEventHandler#onUserMessageReceivedOutsideRoom} 回调收到该消息。
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
     *       + 在发送房间外二进制消息前，必须先调用 login{@link #IRtcEngine#login} 完成登录。  <br>
     *       + 用户调用本接口发送二进制消息后，会收到一次 onUserMessageSendResultOutsideRoom{@link #IRtcEngineEventHandler#onUserMessageSendResultOutsideRoom} 回调，通知消息是否发送成功。  <br>
     *       + 若二进制消息发送成功，则 uid 所指定的用户会通过 onUserBinaryMessageReceivedOutsideRoom{@link #IRtcEngineEventHandler#onUserBinaryMessageReceivedOutsideRoom} 回调收到该条消息。
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
     *       + 在向业务服务器发送文本消息前，必须先调用 login{@link #IRtcEngine#login} 完成登录，随后调用 setServerParams{@link #IRtcEngine#setServerParams} 设置业务服务器。  <br>
     *       + 调用本接口后，会收到一次 onServerMessageSendResult{@link #IRtcEngineEventHandler#onServerMessageSendResult} 回调，通知消息发送方是否发送成功。  <br>
     *       + 若文本消息发送成功，则之前调用 setServerParams{@link #IRtcEngine#setServerParams} 设置的业务服务器会收到该条消息。
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
     *       + 在向业务服务器发送二进制消息前，必须先调用 login{@link #IRtcEngine#login} 完成登录，随后调用 setServerParams{@link #IRtcEngine#setServerParams} 设置业务服务器。  <br>
     *       + 调用本接口后，会收到一次 onServerMessageSendResult{@link #IRtcEngineEventHandler#onServerMessageSendResult} 回调，通知消息发送方发送成功或失败。  <br>
     *       + 若二进制消息发送成功，则之前调用 setServerParams{@link #IRtcEngine#setServerParams} 设置的业务服务器会收到该条消息。
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
     *       + 成功调用本接口后，会在 3s 内收到一次 onNetworkDetectionResult{@link #IRtcEngineEventHandler#onNetworkDetectionResult} 回调，此后每 2s 会收到一次该回调，通知探测结果；  <br>
     *       + 若探测停止，则会收到一次 onNetworkDetectionStopped{@link #IRtcEngineEventHandler#onNetworkDetectionStopped} 通知探测停止。
     */
    virtual NetworkDetectionStartReturn startNetworkDetection(bool is_test_uplink, int expected_uplink_bitrate,
                                   bool is_test_downlink, int expected_downlink_biterate) = 0;

    /** 
     * @type api
     * @region 通话前网络探测
     * @brief 停止通话前网络探测
     * @notes  <br>
     *       + 调用本接口后，会收到一次 onNetworkDetectionStopped{@link #IRtcEngineEventHandler#onNetworkDetectionStopped} 回调通知探测停止。
     */
    virtual void stopNetworkDetection() = 0;

    /** 
     * @hidden(Android,iOS)
     * @type api
     * @region 屏幕共享
     * @brief 在屏幕共享时，设置屏幕音频的采集方式（内部采集/自定义采集）
     * @param [in] source_type 屏幕音频输入源类型, 参看 AudioSourceType{@link #AudioSourceType}
     * @notes  <br>
     *      + 默认采集方式是 RTC SDK 内部采集。<br>
     *      + 你应该在 publishScreen{@link #IRTCRoom#publishScreen} 前，调用此方法。否则，你将收到 onWarning{@link #IRtcEngineEventHandler#onWarning} 的报错：`kWarningCodeSetScreenAudioSourceTypeFailed` <br>
     *      + 如果设定为内部采集，你必须再调用 startScreenAudioCapture{@link #IRtcEngine#startScreenAudioCapture} 开始采集；<br>
     *      + 如果设定为自定义采集，你必须再调用 pushScreenAudioFrame{@link #IRtcEngine#pushScreenAudioFrame} 将自定义采集到的屏幕音频帧推送到 RTC SDK。<br>
     *      + 无论是内部采集还是自定义采集，你都必须调用 publishScreen{@link #IRTCRoom#publishScreen} 将采集到的屏幕音频推送到远端。
     */
    virtual void setScreenAudioSourceType(AudioSourceType source_type) = 0;

    /** 
     * @type api
     * @region 屏幕共享
     * @brief 在屏幕共享时，设置屏幕音频流和麦克风采集到的音频流的混流方式
     * @param [in] index 混流方式，参看 StreamIndex{@link #StreamIndex} <br>
     *        + `kStreamIndexMain`: 将屏幕音频流和麦克风采集到的音频流混流 <br>
     *        + `kStreamIndexScreen`: 默认值，将屏幕音频流和麦克风采集到的音频流分为两路音频流
     * @notes 你应该在 publishScreen{@link #IRTCRoom#publishScreen} 之前，调用此方法。否则，你将收到 onWarning{@link #IRtcEngineEventHandler#onWarning} `的报错：kWarningCodeSetScreenAudioStreamIndexFailed`
     */
    virtual void setScreenAudioStreamIndex(StreamIndex index) = 0;

    /** 
     * @hidden(Android,iOS,Linux)
     * @type api
     * @region 屏幕共享
     * @brief 在屏幕共享时，设置屏幕音频流的声道数
     * @param [in] channel 声道数，参看 AudioChannel{@link #AudioChannel} <br>
     * @notes 你应该在 joinRoom{@link #IRTCRoom#joinRoom} 之后，调用此方法。
     */
    virtual void setScreenAudioChannel(AudioChannel channel) = 0;

    /** 
     * @hidden(Android,iOS,Linux,macOS)
     * @type api
     * @region 屏幕共享
     * @brief 在屏幕共享时，开始使用 RTC SDK 内部采集方式，采集屏幕音频
     * @notes <br>
     *        + 采集后，你还需要调用 publishScreen{@link #IRTCRoom#publishScreen} 将采集到的屏幕音频推送到远端。<br>
     *        + 要关闭屏幕音频内部采集，调用 stopScreenAudioCapture{@link #IRtcEngine#stopScreenAudioCapture}。
     */
    virtual void startScreenAudioCapture() = 0;

    /** 
     * @hidden(Android,iOS,Linux,Windows)
     * @type api
     * @region 屏幕共享
     * @brief 在屏幕共享时，开始使用 RTC SDK 内部采集方式，采集屏幕音频
     * @param  [in] device_id 虚拟设备 ID
     * @notes <br>
     *        + 采集后，你还需要调用 publishScreen{@link #IRtcRoom#publishScreen} 将采集到的屏幕音频推送到远端。<br>
     *        + 要关闭屏幕音频内部采集，调用 stopScreenAudioCapture{@link #IRtcEngine#stopScreenAudioCapture}。
     */
    virtual void startScreenAudioCapture(const char device_id[MAX_DEVICE_ID_LENGTH]) = 0;

    /** 
     * @hidden(Linux)
     * @type api
     * @region 屏幕共享
     * @brief 在屏幕共享时，停止使用 RTC SDK 内部采集方式，采集屏幕音频。
     * @notes 要开始屏幕音频内部采集，调用 startScreenAudioCapture{@link #IRtcEngine#startScreenAudioCapture}。
     */
    virtual void stopScreenAudioCapture() = 0;

    /** 
     * @type api
     * @region 屏幕共享
     * @brief 使用自定义采集方式，采集屏幕共享时的屏幕音频时，将音频帧推送至 RTC SDK 处进行编码等处理。
     * @param [in] frame 音频数据帧，参见 IAudioFrame{@link #IAudioFrame}
     * @return 方法调用结果  <br>
     *        + 0: 设置成功  <br>
     *        + < 0: 设置失败  <br>
     * @notes  <br>
     *        + 调用此接口推送屏幕共享时的自定义采集的音频数据前，必须调用 setScreenAudioSourceType{@link #IRtcEngine#setScreenAudioSourceType} 开启屏幕音频自定义采集。  <br>
     *        + 你应每隔 10 毫秒，调用一次此方法推送一次自定义采集的音频帧。一次推送的音频帧中应包含 frame.sample_rate / 100 个音频采样点。比如，假如采样率为 48000Hz，则每次应该推送 480 个采样点。  <br>
     *        + 音频采样格式为 S16。音频缓冲区内的数据格式必须为 PCM 数据，其容量大小应该为 samples × frame.channel × 2。  <br>
     *        + 调用此接口将自定义采集的音频帧推送到 RTC SDK 后，你必须调用 publishScreen{@link #IRTCRoom#publishScreen} 将采集到的屏幕音频推送到远端。在调用 publishScreen{@link #IRTCRoom#publishScreen} 前，推送到 RTC SDK 的音频帧信息会丢失。
     */
    virtual int pushScreenAudioFrame(IAudioFrame* frame) = 0;


    /** 
     * @hidden
     * @type api
     * @deprecated since 327.1, use stopScreenVideoCapture instead
     * @region 屏幕共享
     * @brief 停止屏幕或者窗口共享。
     * @notes  <br>
     *       + 本函数必须在 startScreenVideoCapture{@link #IRtcEngine#startScreenVideoCapture} 之后调用  <br>
     *       + 本函数不可和 publishScreen{@link #IRTCRoom#publishScreen} 、unpublishScreen{@link #IRTCRoom#unpublishScreen} 混用。  <br>
     */
    virtual void stopScreenCapture() = 0;

    /** 
     * @hidden (macOS,Windows,Android,Linux)
     * @type api
     * @region 屏幕共享
     * @brief 设置 Extension 配置项
     * @param groupId App 和 Extension 应该归属于同一个 App Group，此处需要传入 Group Id
     * @notes 该函数必须在 sharedEngineWithAppId 函数之后立即调用 <br>
     *       如果不调用或者调用时机比较晚，本地用户会收到 rtcEngine:onMediaDeviceStateChanged:deviceType:device_state:device_error:{@link #ByteRTCEngineDelegate#rtcEngine:onMediaDeviceStateChanged:deviceType:device_state:device_error:} 的回调。 <br>
     *       参数 device_state 值为 ByteRTCMediaDeviceStateStopped，device_error 值为 ByteRTCMediaDeviceErrorNotFindGroupId
     */
    virtual void setExtensionConfig(const char* group_id) = 0;

    /** 
     * @hidden (macOS,Windows,Android,Linux)
     * @type api
     * @region 屏幕共享
     * @brief 发送屏幕共享 Extension 程序消息
     * @param message :发送给 Extension 程序的消息内容
     * @param size :message 大小
     * @notes 该函数必须在 startScreenCapture 函数之后调用
     */
    virtual void sendScreenCaptureExtensionMessage(const char* message, size_t size) = 0;

    /** 
     * @hidden (macOS,Windows,Android,Linux)
     * @type api
     * @region 屏幕共享
     * @brief 开启本地屏幕共享数据采集
     * @param type 屏幕共享数据采集类型
     * @param bundle_id 传入 Broadcast Upload Extension 的 Bundle Id，用于在设置中优先展示 Extension
     * @notes 当从 ios 控制中心异常启动 Extension 时可以不用调用本函数 <br>
     *       本地用户会收到 rtcEngine:onMediaDeviceStateChanged:deviceType:device_state:device_error:{@link #ByteRTCEngineDelegate#rtcEngine:onMediaDeviceStateChanged:deviceType:device_state:device_error:} 的回调。 <br>
     *       参数 device_state 值为 ByteRTCMediaDeviceStateStarted，device_error 值为 ByteRTCMediaDeviceErrorOK
     */
    virtual void startScreenCapture(ScreenMediaType type, const char* bundle_id) = 0;

    /** 
     * @hidden(macOS, Windows, iOS, Linux)
     * @type api
     * @region 屏幕共享
     * @brief 通过传入的Type和Context开启屏幕音视频内部采集。
     * @param [in] type
     *        指定的屏幕媒体采集类型，参看ScreenMediaType{@link #ScreenMediaType}
     * @param [in] context
     *        Android平台传入Intent对象，由业务方申请系统录屏权限后获得。
     * @notes <br>
     *        + 采集后，你还需要调用 publishScreen {@link #IRtcRoom #publishScreen} 将采集到的屏幕音视频推送到远端。<br>
     *        + 开启屏幕音视频内部采集，Android专用接口。
     */
    virtual void startScreenCapture(ScreenMediaType type, void* context) = 0;

    /** 
     * @hidden (macOS,Windows,Linux)
     * @type api
     * @region 屏幕共享
     * @brief 更新屏幕采集数据类型
     * @param type 屏幕采集数据类型
     * @notes 该函数必须在 startScreenCapture 函数之后调用
     *       本地用户会收到 rtcEngine:onMediaDeviceStateChanged:deviceType:device_state:device_error:{@link #ByteRTCEngineDelegate#rtcEngine:onMediaDeviceStateChanged:deviceType:device_state:device_error:} 的回调。 <br>
     *       参数 device_state 值为 ByteRTCMediaDeviceStateStarted 或 ByteRTCMediaDeviceStateStopped，device_error 值为 ByteRTCMediaDeviceErrorOK
     */
    virtual void updateScreenCapture(ScreenMediaType type) = 0;


     /** 
      * @type api
      * @region 音频管理
      * @brief 启用音频信息提示。  <br>
      * @param config 详见 AudioPropertiesConfig{@link #AudioPropertiesConfig}
      * @notes 开启提示后，你可以：  <br>
      *       + 通过 onLocalAudioPropertiesReport{@link #IRtcEngineEventHandler#onLocalAudioPropertiesReport} 回调获取本地麦克风和屏幕音频流采集的音频信息；  <br>
      *       + 通过 onRemoteAudioPropertiesReport{@link #IRtcEngineEventHandler#onRemoteAudioPropertiesReport} 回调获取订阅的远端用户的音频信息。  <br>
      */
     virtual void enableAudioPropertiesReport(const AudioPropertiesConfig& config) = 0;
    /** 
     * @type api
     * @region 音频管理
     * @brief 开启/关闭音量均衡功能。  <br>
     *        开启音量均衡功能后，人声的响度会调整为 -16lufs。如果已调用 setAudioMixingLoudness{@link #IAudioMixingManager#setAudioMixingLoudness} 传入了混音音乐的原始响度，此音乐播放时，响度会调整为 -20lufs。
     * @param [in] enable 是否开启音量均衡功能：  <br>
     *       + True: 是  <br>
     *       + False: 否
     * @notes 该接口须在调用 startAudioMixing{@link #IAudioMixingManager#startAudioMixing} 开始播放音频文件之前调用。
     */
    virtual void enableVocalInstrumentBalance(bool enable) = 0;
    /** 
     * @type api
     * @region 音频管理
     * @brief 打开/关闭音量闪避功能，适用于“一起看”等场景。  <br>
     *        开启该功能后，当检测到远端人声时，本地的媒体播放音量会自动减弱，从而保证远端人声的清晰可辨；当远端人声消失时，本地媒体音量会恢复到闪避前的音量水平。
     * @param enable 是否开启音量闪避：  <br>
     *        + True: 是  <br>
     *        + False: 否
     */
    virtual void enablePlaybackDucking(bool enable) = 0;
    /** 
     * @type api
     * @region 视频数据回调
     * @brief 注册本地视频帧监测器。  <br>
     *        无论使用内部采集还是自定义采集，调用该方法后，SDK 每监测到一帧本地视频帧时，都会将视频帧信息通过 onLocalEncodedVideoFrame{@link #ILocalEncodedVideoFrameObserver#onLocalEncodedVideoFrame} 回调给用户
     * @param [in] observer 本地视频帧监测器，参看 ILocalEncodedVideoFrameObserver{@link #ILocalEncodedVideoFrameObserver}。将参数设置为 nullptr 则取消注册。
     * @notes 该方法可在进房前后的任意时间调用，在进房前调用可保证尽可能早地监测视频帧并触发回调
     */
    virtual void registerLocalEncodedVideoFrameObserver(ILocalEncodedVideoFrameObserver* observer) = 0;

    /** 
     * @type api
     * @region 视频管理
     * @brief 注册远端编码后视频数据回調。  <br>
     *        完成注册后，当 SDK 监测到远端编码后视频帧时，会触发 onRemoteEncodedVideoFrame{@link #IRemoteEncodedVideoFrameObserver#onRemoteEncodedVideoFrame} 回调
     * @param [in] observer 远端编码后视频数据监测器，参看 IRemoteEncodedVideoFrameObserver{@link #IRemoteEncodedVideoFrameObserver}
     * @notes  <br>
     *       + 该方法需在进房前调用。 <br>
     *       + 引擎销毁前需取消注册，调用该方法将参数设置为 nullptr 即可。
     */
    virtual void registerRemoteEncodedVideoFrameObserver(IRemoteEncodedVideoFrameObserver* observer) = 0;

    /** 
     * @type api
     * @region 视频管理
     * @brief 注册自定义编码帧推送事件回调
     * @param [in] encoder_handler 自定义编码帧回调类，参看 IExternalVideoEncoderEventHandler{@link #IExternalVideoEncoderEventHandler}
     * @notes  <br>
     *       + 该方法需在进房前调用。 <br>
     *       + 引擎销毁前需取消注册，调用该方法将参数设置为 nullptr 即可。
     */
    virtual void setExternalVideoEncoderEventHandler(IExternalVideoEncoderEventHandler* encoder_handler) = 0;

    /** 
     * @type api
     * @region 视频管理
     * @brief 推送自定义编码后的视频流
     * @param [in] index 需要推送的编码流的属性，参看 StreamIndex{@link #StreamIndex}
     * @param [in] video_index 对应的编码流下标，从 0 开始，如果调用 setVideoEncoderConfig{@link #IRtcEngine#setVideoEncoderConfig} 设置了多路流，此处数量须与之保持一致
     * @param [in] video_stream 编码流视频帧信息，参看 IEncodedVideoFrame{@link #IEncodedVideoFrame}。  <br>
     * @notes  <br>
     *        + 目前仅支持推送 H264 和 ByteVC1 格式的视频帧，且视频流协议格式须为 Annex B 格式。  <br>
     *        + 该函数运行在用户调用线程内  <br>
     *        + 推送自定义编码视频帧前，必须调用 setVideoSourceType{@link #IRtcEngine#setVideoSourceType} 将视频输入源切换至自定义编码视频源。
     */
    virtual bool pushExternalEncodedVideoFrame(StreamIndex index, int video_index, IEncodedVideoFrame* video_stream) = 0;

    /** 
     * @type api
     * @region 视频管理
     * @brief 在订阅远端视频流之前，设置远端视频数据解码方式
     * @param [in] key 远端流信息，即对哪一路视频流进行解码方式设置，参看 RemoteStreamKey{@link #RemoteStreamKey}。
     * @param [in] config 视频解码方式，参看 VideoDecoderConfig{@link #VideoDecoderConfig}。
     * @notes  <br>
     *        + 该方法仅适用于手动订阅模式，并且在订阅远端流之前使用。  <br>
     *        + 当你想要对远端流进行自定义解码时，你需要先调用 registerRemoteEncodedVideoFrameObserver{@link #IRtcEngine#registerRemoteEncodedVideoFrameObserver} 注册远端视频流监测器，然后再调用该接口将解码方式设置为自定义解码。监测到的视频数据会通过 onRemoteEncodedVideoFrame{@link #IRemoteEncodedVideoFrameObserver#onRemoteEncodedVideoFrame} 回调出来。
     */
    virtual void setVideoDecoderConfig(RemoteStreamKey key, VideoDecoderConfig config) = 0;

    /** 
     * @type api
     * @region 视频管理
     * @brief 在订阅远端视频流之后，向远端请求关键帧
     * @param [in] stream_info 远端流信息，参看 RemoteStreamKey{@link #RemoteStreamKey}。
     * @notes  <br>
     *        + 该方法仅适用于手动订阅模式，并且在成功订阅远端流之后使用。  <br>
     *        + 该方法适用于调用 setVideoDecoderConfig{@link #IRtcEngine#setVideoDecoderConfig} 开启自定义解码功能后，并且自定义解码失败的情况下使用
     */
    virtual void requestRemoteVideoKeyFrame(const RemoteStreamKey& stream_info) = 0;

    /** 
     * @type api
     * @region 音频管理
     * @brief 发送音频流同步信息。将消息通过音频流发送到远端，并实现与音频流同步，该接口调用成功后，远端用户会收到 onStreamSyncInfoReceived{@link #IRtcEngineEventHandler#onStreamSyncInfoReceived} 回调。
     * @param [in] data 消息内容。
     * @param [in] length 消息长度。消息长度必须是 [1,16] 字节。
     * @param [in] config 媒体流信息同步的相关配置，详见 StreamSycnInfoConfig{@link #StreamSycnInfoConfig} 。
     * @return  <br>
     *        + >=0: 消息发送成功。返回成功发送的次数。  <br>
     *        + -1: 消息发送失败。消息长度大于 255 字节。  <br>
     *        + -2: 消息发送失败。传入的消息内容为空。  <br>
     *        + -3: 消息发送失败。通过屏幕流进行消息同步时，此屏幕流还未发布。  <br>
     *        + -4: 消息发送失败。通过用麦克风或自定义设备采集到的音频流进行消息同步时，此音频流还未发布，详见错误码 ErrorCode{@link #ErrorCode}。  <br>
     * @notes 在采用 `kRoomProfileTypeLiveBroadcasting` 作为房间模式时，此消息一定会送达。在其他房间模式下，如果本地用户未说话，此消息不一定会送达。
     */
    virtual int sendStreamSyncInfo(const uint8_t* data, int32_t length, const StreamSycnInfoConfig& config) = 0;

    /** 
     * @type api
     * @region 混音
     * @brief 开启本地语音变调功能，多用于 K 歌场景。  <br>
     *        使用该方法，你可以对本地语音的音调进行升调或降调等调整。
     * @param [in] pitch 相对于语音原始音调的升高/降低值，取值范围[-12，12]，默认值为 0，即不做调整。  <br>
     *        取值范围内每相邻两个值的音高距离相差半音，正值表示升调，负值表示降调，设置的绝对值越大表示音调升高或降低越多。  <br>
     *        超出取值范围则设置失败，并且会触发 onWarning{@link #IRtcEngineEventHandler#onWarning} 回调，提示 WarningCode{@link #WarningCode} 错误码为 `WARNING_CODE_SET_SCREEN_STREAM_INVALID_VOICE_PITCH` 设置语音音调不合法
     */
    virtual void setLocalVoicePitch(int pitch) = 0;

    /** 
     * @hidden
     * @type api
     * @region 媒体流管理
     * @brief 控制本地音频流播放状态：播放/不播放  <br>
     * @param [in] mute_state 播放状态，标识是否播放本地音频流，详见：MuteState{@link #MuteState}
     * @notes 本方法仅控制本地收到音频流的播放状态，并不影响本地音频播放设备。
     */
    virtual void muteAudioPlayback(MuteState mute_state) = 0;

    /** 
     * @type api
     * @brief 订阅指定公共流<br>
     *        无论用户是否在房间内，都可以调用本接口获取和播放指定的公共流。
     * @param [in] public_streamid 公共流 ID，如果指定流暂未发布，则本地客户端将在其开始发布后接收到流数据。<br>
     * @return <br>
     *        + 0: 成功。同时将收到 onPlayPublicStreamResult{@link #IRtcEngineEventHandler#onPlayPublicStreamResult} 回调。<br>
     *        + !0: 失败。当参数不合法或参数为空，调用失败。<br>
     * @notes  <br>
     *        + 在调用本接口之前，建议先绑定渲染视图。<br>
     *              - 调用 setPublicStreamVideoCanvas{@link #IRtcEngine#setPublicStreamVideoCanvas} 绑定内部渲染视图：<br>
     *              - 调用 setPublicStreamVideoSink{@link #IRtcEngine#setPublicStreamVideoSink} 绑定自定义渲染视图：<br>
     *        + 调用本接口后，可以通过 onFirstPublicStreamVideoFrameDecoded{@link #IRtcEngineEventHandler#onFirstPublicStreamVideoFrameDecoded} 和 onFirstPublicStreamAudioFrame{@link #IRtcEngineEventHandler#onFirstPublicStreamAudioFrame} 回调公共流的视频和音频首帧解码情况。<br>
     *        + 调用本接口后，可以通过 onPublicStreamSEIMessageReceived{@link #IRtcEngineEventHandler#onPublicStreamSEIMessageReceived} 回调公共流中包含的 SEI 信息。<br>
     *        + 订阅公共流之后，可以通过调用 stopPlayPublicStream{@link #IRtcEngine#stopPlayPublicStream} 接口取消订阅公共流。
     */
    virtual int startPlayPublicStream(const char* public_streamid) = 0;
    /** 
     * @type api
     * @brief 取消订阅指定公共流<br>
     *        关于订阅公共流，查看 startPlayPublicStream{@link #IRtcEngine#startPlayPublicStream}。
     * @param [in] public_streamid 公共流 ID
     * @return  <br>
     *        + 0：成功  <br>
     *        + !0：失败  <br>
     */
    virtual int stopPlayPublicStream(const char* public_streamid) = 0;
    /** 
     * @type api
     * @brief 为指定公共流绑定内部渲染视图
     * @param [in] public_streamid 公共流 ID
     * @param [in] canvas 内部渲染视图，如果需要解除视频的绑定视图，把 videoCanvas 设置为空。详见 VideoCanvas{@link #VideoCanvas}。
     * @return  <br>
     *        + 0：成功  <br>
     *        + !0：失败  <br>
     */
    virtual int setPublicStreamVideoCanvas(const char* public_streamid, const VideoCanvas& canvas) = 0;
    /** 
     * @type api
     * @brief 为指定公共流绑定自定义渲染器。详见[自定义视频渲染](81201)。
     * @param [in] public_streamid 公共流 ID
     * @param [in] video_sink 自定义视频渲染器，自定义视频渲染器，需要释放渲染器资源时，将 videoSink 设置为 `null`。参看 IVideoSink{@link #IVideoSink}
     * @return  <br>
     *        + 0：成功  <br>
     *        + !0：失败  <br>
     */
    virtual void setPublicStreamVideoSink(const char* public_streamid, IVideoSink* video_sink,
                                          IVideoSink::PixelFormat format) = 0;

    virtual void setVideoWatermark(StreamIndex index, const char * image_path, RTCWatermarkConfig config) = 0;

    virtual void clearVideoWatermark(StreamIndex index) = 0;

    virtual long takeLocalSnapshot(StreamIndex streamIndex, ISnapshotResultCallback *callback) = 0;

    virtual long takeRemoteSnapshot(RemoteStreamKey streamKey, ISnapshotResultCallback *callback) = 0;

    /** 
     * @type api
     * @region 视频管理
     * @brief 设置静态图片路径，该图片在用户关闭摄像头后用来推送到远端
     * @param file_path 静态图片路径，支持本地文件绝对路径和Asset 资源路径（/assets/xx.png），长度限制为 512 字节。   <br>
     *        静态图片为 BMP, PNG 或 JPG 格式。
     * @notes  <br>
     *        + 当设置的路径为空字符串时移除指定的静态图片。  <br>
     *        + 只有主流能设置静态图片，屏幕流不支持设置。新设置的图片会代替上一次的设置。  <br>
     *        + 进入房间前后均可调用此方法。  <br>
     *        + 设置的静态图片不会在本地预览中显示  <br>
     *        + 开启大小流后，静态图片对大小流均生效，且针对小流进行等比例缩小。
     */
    virtual int setDummyCaptureImagePath(const char* file_path) = 0;

  /** 
     * @hidden
     * @type api
     * @region 多房间
     * @brief 退出并销毁调用 createRtcRoom{@link #IRtcEngine#createRtcRoom} 所创建的房间。
     */
    virtual void destroy() = 0;
    /** 
     * @hidden
     * @deprecated since 327.1, use setUserVisibility instead
     * @type api
     * @region 多房间
     * @brief 设置用户角色。默认角色为主播。  <br>
     *        通过设置不同的用户角色，可以控制用户在房间内的行为：<br>
     *        + 能否发布音视频流；<br>
     *        + 用户自身是否在房间中隐身。<br>
     * @param [in] role 用户角色，参看 UserRoleType{@link #UserRoleType}。
     * @notes  <br>
     *       + 在加入房间前后，用户均可调用此方法设置用户角色。 <br>
     *       + 在房间内，调用此方法成功切换角色后，房间内其他用户会收到相应的回调通知：<br>
     *            - 从隐身用户切换至主播时，房间内其他用户会收到 onUserJoined{@link #IRTCRoomEventHandler#onUserJoined}；  <br>
     *            - 从主播切换至隐身用户时，房间内其他用户会收到 onUserLeave{@link #onUserLeave} 。
     */
    virtual void setUserRole(UserRoleType role) = 0;
    /** 
     * @type api
     * @region 多房间
     * @brief 设置用户可见性。默认可见。  <br>
     * @param enable 设置用户是否对房间内其他用户可见：  <br>
     *        + true: 可以在房间内发布音视频流，房间中的其他用户将收到用户的行为通知，例如进房、开启视频采集和退房。  <br>
     *        + false: 不可以在房间内发布音视频流，房间中的其他用户不会收到用户的行为通知，例如进房、开启视频采集和退房。
     * @notes  <br>
     *       + 该方法在加入房间前后均可调用。 <br>
     *       + 在房间内调用此方法，房间内其他用户会收到相应的回调通知：<br>
     *            - 从 false 切换至 true 时，房间内其他用户会收到 onUserJoined{@link #IRTCRoomEventHandler#onUserJoined} 回调通知；  <br>
     *            - 从 true 切换至 false 时，房间内其他用户会收到 onUserLeave{@link #IRTCRoomEventHandler#onUserLeave} 回调通知。  <br>
     *       + 若调用该方法将可见性设为 false，此时尝试发布流会收到 `kWarningCodePublishStreamForbiden` 警告。
     */
    virtual void setUserVisibility(bool enable) = 0;
    /** 
     * @type api
     * @region 多房间
     * @brief 离开房间。  <br>
     *        用户调用此方法离开房间，结束通话过程，释放所有通话相关的资源。  <br>
     *        加入房间后，必须调用此方法结束通话，否则无法开始下一次通话。无论当前是否在房间内，都可以调用此方法。重复调用此方法没有负面影响。  <br>
     *        此方法是异步操作，调用返回时并没有真正退出房间。真正退出房间后，本地会收到 onLeaveRoom{@link #IRTCRoomEventHandler#onLeaveRoom} 回调通知。  <br>
     * @notes  <br>
     *       + 可见的用户离开房间后，房间内其他用户会收到 onUserLeave{@link #IRTCRoomEventHandler#onUserLeave} 回调通知。  <br>
     *       + 如果调用此方法后立即销毁引擎，SDK 将无法触发 onLeaveRoom{@link #IRTCRoomEventHandler#onLeaveRoom} 回调。  <br>
     *       + 调用 joinRoom{@link #IRTCRoom#joinRoom} 方法加入房间后，必须调用此方法离开房间，否则无法进入下一个房间。无论当前是否在房间内，都可以调用此方法。重复调用此方法没有负面影响。  <br>
     */
     virtual void leaveRoom() = 0;
    /** 
     * @type api
     * @brief 更新 Token。  <br>
     *        用于加入房间的 Token 有一定的有效期。在 Token 过期前 30 秒，会收到 onTokenWillExpire{@link #IRTCRoomEventHandler#onTokenWillExpire} 回调，此时需要重新获取 Token，并调用此方法更新 Token，否则用户将因为 Token 过期被移出房间。 <br>
     *        调用 joinRoom{@link #IRTCRoom#joinRoom} 方法加入房间或断网重连进入房间时，如果 Token 过期或无效，将导致加入房间失败，并会收到 onRoomStateChanged{@link #IRTCRoomEventHandler#onRoomStateChanged} 回调通知，回调错误码为 ErrorCode{@link #ErrorCode} 中的 `ERROR_CODE_INVALID_TOKEN`。此时需要重新获取 Token，并调用此方法更新 Token。 更新 Token 后，SDK 会自动加入房间。 <br>
     * @param [in] token 有效的 Token。  <br>
     *        如果传入的 Token 无效，回调错误码为 ErrorCode{@link #ErrorCode} 中的 `ERROR_CODE_UPDATE_TOKEN_WITH_INVALID_TOKEN`。
     * @notes 当 Token 过期时，用户将被移出房间并将收到 onStreamStateChanged{@link #IRTCRoomEventHandler#onStreamStateChanged} 回调， `ERROR_CODE_EXPIRED_TOKEN`，此时需要重新获取 Token，并调用 joinRoom{@link #IRTCRoom#joinRoom} 重新加入房间。
     */
    virtual void updateToken(const char* token) = 0;
    /** 
     * @type api
     * @region 多房间
     * @brief 给房间内的所有其他用户发送广播消息。
     * @param [in] uid 消息接收用户的 ID
     * @param [in] message  <br>
     *        发送的文本消息内容。  <br>
     *        消息不超过 64 KB。
     * @param [in] config 消息类型，参看 MessageConfig{@link #MessageConfig}。
     * @notes  <br>
     *       + 在发送房间内二进制消息前，必须先调用 joinRoom{@link #IRTCRoom#joinRoom} 加入房间。  <br>
     *       + 调用该函数后，会收到一次 onRoomMessageSendResult{@link #IRTCRoomEventHandler#onRoomMessageSendResult} 回调。  <br>
     *       + 同一房间内的其他用户会收到 onRoomMessageReceived{@link #IRTCRoomEventHandler#onRoomMessageReceived} 回调。
     */
    virtual int64_t sendUserMessage(const char* uid, const char* message, MessageConfig config) = 0;
    /** 
     * @type api
     * @region 多房间
     * @brief 给房间内指定的用户发送二进制消息（P2P）
     * @param [in] uid  <br>
     *        消息接收用户的 ID
     * @param [in] length   <br>
     *        二进制字符串的长度。
     * @param [in] message   <br>
     *        二进制消息的内容。
     *        消息不超过 46KB。
     * @param [in] config 消息类型，参看 MessageConfig{@link #MessageConfig}。
     * @return 这次发送消息的编号，从 1 开始递增。
     * @notes  <br>
     *       + 在发送房间内二进制消息前，必须先调用 joinRoom{@link #IRTCRoom#joinRoom} 加入房间。  <br>
     *       + 调用该函数后会收到一次 onUserMessageSendResult{@link #IRTCRoomEventHandler#onUserMessageSendResult} 回调，通知消息发送方发送成功或失败；  <br>
     *       + 若二进制消息发送成功，则 uid 所指定的用户会收到 onUserBinaryMessageReceived{@link #IRTCRoomEventHandler#onUserBinaryMessageReceived} 回调。
     */
    virtual int64_t sendUserBinaryMessage(const char* uid, int length, const uint8_t* message, MessageConfig config) = 0;
    /** 
     * @type api
     * @region 多房间
     * @brief 给房间内的所有其他用户发送广播消息。
     * @param [in] message  <br>
     *        用户发送的广播消息  <br>
     *        消息不超过 64 KB。
     * @notes  <br>
     *       + 在发送房间内二进制消息前，必须先调用 joinRoom{@link #IRTCRoom#joinRoom} 加入房间。  <br>
     *       + 调用该函数后，会收到一次 onRoomMessageSendResult{@link #IRTCRoomEventHandler#onRoomMessageSendResult} 回调。  <br>
     *       + 同一房间内的其他用户会收到 onRoomMessageReceived{@link #IRTCRoomEventHandler#onRoomMessageReceived} 回调。
     */
    virtual int64_t sendRoomMessage(const char* message) = 0;
    /** 
     * @type api
     * @region 多房间
     * @brief 给房间内的所有其他用户发送广播消息。
     * @param [in] size  <br>
     *        发送的二进制消息长度
     * @param [in] message  <br>
     *        用户发送的二进制广播消息  <br>
     *        消息不超过 46KB。
     * @notes  <br>
     *       + 在发送房间内二进制消息前，必须先调用 joinRoom{@link #IRTCRoom#joinRoom} 加入房间。  <br>
     *       + 调用该函数后，会收到一次 onRoomMessageSendResult{@link #IRTCRoomEventHandler#onRoomMessageSendResult} 回调。  <br>
     *       + 同一房间内的其他用户会收到 onRoomBinaryMessageReceived{@link #IRTCRoomEventHandler#onRoomBinaryMessageReceived} 回调。
     */
    virtual int64_t sendRoomBinaryMessage(int size, const uint8_t* message) = 0;
    /** 
     * @hidden
     * @deprecated since 336.1, use publishStream instead.
     * @type api
     * @region 多房间
     * @brief 在当前所在房间内停止发布本地音视频流
     * @notes  <br>
     *        + 多房间模式下，默认音视频流不自动发布。你必须调用此接口，进行手动发布。<br>
     *        + 调用 setUserVisibility{@link #IRTCRoom#setUserVisibility} 方法将自身设置为不可见后无法调用该方法，需将自身切换至可见后方可调用该方法发布音视频流。 <br>
     *        + 如果你需要发布屏幕共享流，调用 publishScreen{@link #IRTCRoom#publishScreen}。<br>
     *        + 如果你需要向多个房间发布音视频流，调用 startForwardStreamToRooms{@link #IRTCRoom#startForwardStreamToRooms}。
     *        + 用户调用此方法成功发布音视频流后，房间中的其他用户将会收到 onStreamAdd{@link #IRTCRoomEventHandler#onStreamAdd} 回调通知。
     */
    virtual void publish() = 0;
    /** 
     * @type api
     * @region 房间管理
     * @brief 在当前所在房间内发布本地通过摄像头/麦克风采集的媒体流
     * @param [in] type 媒体流类型，用于指定发布音频/视频，参看 MediaStreamType{@link #MediaStreamType}
     * @notes <br>
     *        + 如果你已经在用户进房时通过调用 joinRoom{@link #IRTCRoom#joinRoom} 成功选择了自动发布，则无需再调用本接口。<br>
     *        + 调用 setUserVisibility{@link #IRTCRoom#setUserVisibility} 方法将自身设置为不可见后无法调用该方法，需将自身切换至可见后方可调用该方法发布摄像头音视频流。 <br>
     *        + 如果你需要发布屏幕共享流，调用 publishScreen{@link #IRTCRoom#publishScreen}。<br>
     *        + 如果你需要向多个房间发布流，调用 startForwardStreamToRooms{@link #IRTCRoom#startForwardStreamToRooms}。  <br>
     *        + 调用此方法后，房间中的所有远端用户会收到 onUserPublishStream{@link #IRTCRoomEventHandler#onUserPublishStream} 回调通知，其中成功收到了音频流的远端用户会收到 onFirstRemoteAudioFrame{@link #IRtcEngineEventHandler#onFirstRemoteAudioFrame} 回调，订阅了视频流的远端用户会收到 onFirstRemoteVideoFrameDecoded{@link #IRtcEngineEventHandler#onFirstRemoteVideoFrameDecoded} 回调。<br>
     *        + 调用 unpublishStream{@link #IRTCRoom#unpublishStream} 取消发布。
     */
    virtual void publishStream(MediaStreamType type) = 0;
    /** 
     * @hidden
     * @deprecated since 336.1, use unpublishStream instead.
     * @type api
     * @region 多房间
     * @brief 停止将本端音视频流发布到此房间
     * @notes  <br>
     *        + 在多房间模式下，调用 publish{@link #IRTCRoom#publish} 手动发布音视频流后，调用此接口停止发布。<br>
     *        + 房间内用户调用此方法停止发布音视频流后，房间中的其他用户将会收到 onStreamRemove{@link #IRTCRoomEventHandler#onStreamRemove} 回调通知。
     */
    virtual void unpublish() = 0;
    /** 
     * @type api
     * @region 房间管理
     * @brief 停止将本地摄像头/麦克风采集的媒体流发布到当前所在房间中
     * @param [in] type 媒体流类型，用于指定停止发布音频/视频，参看 MediaStreamType{@link #MediaStreamType}
     * @notes  <br>
     *        + 调用 publishStream{@link #IRtcEngine#publishStream} 手动发布摄像头音视频流后，你需调用此接口停止发布。<br>
     *        + 调用此方法停止发布音视频流后，房间中的其他用户将会收到 onUserUnPublishStream{@link #IRtcEngineEventHandler#onUserUnPublishStream} 回调通知。
     */
    virtual void unpublishStream(MediaStreamType type) = 0;
    /** 
     * @hidden
     * @deprecated since 327.1, use publishScreen without params instead
     * @type api
     * @region 多房间
     * @brief 发布本地屏幕共享流到房间。
     * @param [in] parameters
     *        屏幕共享流编码参数，详见 ScreenParameters{@link #ScreenParameters}
     * @notes  <br>
     *       + 此方法适用于调用 setUserVisibility{@link #IRTCRoom#setUserVisibility} 方法将自身设为可见的用户。  <br>
     *       + 调用此方法发布本端屏幕共享流后，用户还需要通过设置定时任务周期性调用 pushScreenFrame{@link
     * #IRtcEngine#pushScreenFrame} 方法，将需要发送的屏幕数据推送给 SDK。  <br>
     *       + 远端会收到 onFirstRemoteVideoFrameRendered{@link #IRtcEngineEventHandler#onFirstRemoteVideoFrameRendered}
     * 、onStreamAdd{@link#IRTCRoomEventHandler#onStreamAdd} 事件。  <br>
     *       + 该函数和 startScreenVideoCapture{@link#IRtcEngine#startScreenVideoCapture} 函数是互斥调用的，可在调用
     * unpublishScreen{@link#unpublishScreen} 函数后调用上述函数。  <br>
     *       + 在收到 onFirstRemoteVideoFrameRendered{@link#IRTCRoomEventHandler#onFirstRemoteVideoFrameRendered}
     * 事件后通过调用 setRemoteVideoCanvas{@link #setRemoteVideoCanvas} 或 setRemoteVideoSink{@link #setRemoteVideoSink}
     * 函数来设置远端屏幕共享视图。  <br>
     *       + 本地可调用 setLocalVideoCanvas{@link #IRtcEngine#setLocalVideoCanvas} 或
     * setLocalVideoSink{@link #IRtcEngine#setLocalVideoSink} 函数设置本地屏幕共享视图。  <br>
     *       + 也可通过注册 registerVideoFrameObserver{@link#registerVideoFrameObserver} 视频回调对象，监听
     * onLocalScreenFrame{@link #IVideoFrameObserver#onLocalScreenFrame}本地屏幕视频回调事件和 onRemoteScreenFrame{@link
     * #IVideoFrameObserver#onRemoteScreenFrame}远端屏幕共享视频回调事件来获取原始数据。  <br>
     *       + 该方法在 joinRoom{@link #IRTCRoom#joinRoom} 后才能调用。  <br>
     */
    virtual void publishScreen(const ScreenParameters& parameters) = 0;
    /** 
     * @hidden
     * @deprecated since 336.1
     * @type api
     * @region 屏幕共享
     * @brief 发布本地屏幕共享流到房间。
     * @notes  <br>
     *       + 你必须先加入房间，才能调用此方法。<br>
     *       + 直播、游戏、云游戏房间模式下，仅可见的用户可以调用此方法。你可以调用 setUserVisibility{@link #IRTCRoom#setUserVisibility} 方法设置用户在房间中的可见性。  <br>
     *       + 此方法只影响屏幕共享视频流的发布状态，并不影响屏幕视频流的采集情况。你可以通过两种方式进行采集：<br>
     *              - RTC SDK 内部采集：参看 startScreenVideoCapture{@link#IRtcEngine#startScreenVideoCapture} 和 startScreenAudioCapture{@link#IRtcEngine#startScreenAudioCapture} <br>
     *              - RTC SDK 外部采集：你可以自行采集屏幕音视频流，并周期性调用 pushScreenFrame{@link#IRtcEngine#pushScreenFrame} 和 pushScreenAudioFrame{@link#IRtcEngine#pushScreenAudioFrame} 将采集得到的音视频帧推送到 RTC SDK 用于编码传输。<br>
     *       + 发布成功后，远端会收到 onStreamAdd{@link #IRTCRoomEventHandler#onStreamAdd} 回调；如果调用 registerVideoFrameObserver{@link#registerVideoFrameObserver} 注册了视频帧回调观察者，那么也会收到 onRemoteScreenFrame{@link #IVideoFrameObserver#onRemoteScreenFrame} 回调。
     *       + 调用 unpublishScreen{@link #IRTCRoom#unpublishScreen} 取消发布。
     */
    virtual void publishScreen() = 0;
    /** 
     * @type api
     * @region 屏幕共享
     * @brief 在当前所在房间内发布本地屏幕共享音视频流
     * @param [in] type 媒体流类型，用于指定发布屏幕音频/视频，参看 MediaStreamType{@link #MediaStreamType}。
     * @notes <br>
     *        + 如果你已经在用户进房时通过调用 joinRoom{@link #IRTCRoom#joinRoom} 成功选择了自动发布，则无需再调用本接口。<br>
     *        + 调用 setUserVisibility{@link #IRTCRoom#setUserVisibility} 方法将自身设置为不可见后无法调用该方法，需将自身切换至可见后方可调用该方法发布屏幕流。 <br>
     *        + 调用该方法后，房间中的所有远端用户会收到 onUserPublishScreen{@link #IRTCRoomEventHandler#onUserPublishScreen} 回调，其中成功收到音频流的远端用户会收到 onFirstRemoteAudioFrame{@link #IRtcEngineEventHandler#onFirstRemoteAudioFrame} 回调，订阅了视频流的远端用户会收到 onFirstRemoteVideoFrameDecoded{@link #IRtcEngineEventHandler#onFirstRemoteVideoFrameDecoded} 回调。<br>
     *        + 如果你需要向多个房间发布流，调用 startForwardStreamToRooms{@link #IRTCRoom#startForwardStreamToRooms}。  <br>
     *        + 调用 unpublishScreen{@link #IRTCRoom#unpublishScreen} 取消发布。
     */
    virtual void publishScreen(MediaStreamType type) = 0;
    /** 
     * @hidden
     * @deprecated since 336.1
     * @type api
     * @region 屏幕共享
     * @brief 停止发布本地屏幕共享流到房间。
     * @notes 远端会收到 onStreamRemove{@link #IRTCRoomEventHandler#onStreamRemove} 事件。
     * @notes  <br>
     *       + 此方法只影响屏幕共享视频流的发布状态，并不影响屏幕视频流的采集情况。<br>
     *       + 调用 publishScreen{@link #IRTCRoom#publishScreen} 启动发布。
     */
    virtual void unpublishScreen() = 0;
    /** 
     * @type api
     * @region 屏幕共享
     * @brief 停止将本地屏幕共享音视频流发布到当前所在房间中
     * @param [in] type 媒体流类型，用于指定停止发布屏幕音频/视频，参看 MediaStreamType{@link #MediaStreamType}
     * @notes <br>
     *        + 调用 publishScreen{@link #IRTCRoom#publishScreen} 发布屏幕流后，你需调用此接口停止发布。 <br>
     *        + 调用此方法停止发布屏幕音视频流后，房间中的其他用户将会收到 onUserUnPublishScreen{@link #IRtcEngineEventHandler#onUserUnPublishScreen} 回调。
     */
    virtual void unpublishScreen(MediaStreamType type) = 0;
    /** 
     * @hidden
     * @deprecated since 326.1, use subscribeUserStream instead
     * @type api
     * @region 多房间
     * @brief 订阅指定的房间内远端音视频流。  <br>
     *        关闭自动订阅功能，使用手动订阅模式时用户调用此方法按需订阅房间中的音视频流。  <br>
     *        此方法仅在关闭自动订阅功能时生效。用户需在加入房间前调用 enableAutoSubscribe{@link #enableAutoSubscribe}
     * 方法关闭自动订阅功能以使用手动订阅模式。  <br> 用户在自动订阅功能开启时调用此方法，SDK 不会订阅音视频流，并通过
     * onRoomWarning{@link #onRoomWarning} 回调通知用户订阅失败，回调警告码为
     * kWarningCodeSubscribeStreamForbiden{@link #kWarningCodeSubscribeStreamForbiden} 。  <br> 订阅流失败时，SDK
     * 会按失败原因回调 onRoomError{@link #onRoomError} 通知用户，具体错误可参考错误码 ErrorCode{@link
     * #ErrorCode} 描述。  <br>
     * @param [in] user_id 指定订阅的远端用户的用户ID 。  <br>
     * @param [in] info 选择订阅配置，详见数据结构 SubscribeConfig{@link #SubscribeConfig} 。  <br>
     * @notes  <br>
     *       + 此方法仅支持订阅当前房间中的远端音视频流。如果指定的流在当前房间内不曾存在，则 SDK 不会订阅。  <br>
     *       + 用户调用 joinRoom{@link #IRTCRoom#joinRoom} 方法加入房间后：1.当房间内有新的音视频流发布时，本地会收到
     * onStreamAdd{@link #onStreamAdd} 回调通知；2.当房间内音视频流停止发布时，本地会收到 onStreamRemove{@link
     * #onStreamRemove}
     * 回调通知。通过这两个回调用户可以获得当前房间中的音视频流信息，并在需要时调用此方法订阅该音视频流。  <br>
     */
    virtual void subscribeStream(const char* user_id, const SubscribeConfig& info) = 0;
    /** 
     * @hidden
     * @deprecated since 336.1, use subscribeStream, unsubscribeStream, subscribeScreen and unsubscribeScreen instead.
     * @type api
     * @region 多房间
     * @brief 订阅房间内指定的远端音视频流。  <br>
     *        无论是自动订阅还是手动订阅模式，你都可以调用此方法按需订阅房间中的音视频流。  <br>
     *        该方法也可用于更新已经订阅的流的属性、媒体类型等配置。 <br>
     * @param [in] user_id 指定订阅的远端发布音视频流的用户 ID。
     * @param [in] stream_type 流属性，用于指定订阅主流/屏幕流，参看 StreamIndex{@link #StreamIndex}。
     * @param [in] media_type 媒体类型，用于指定订阅音/视频，参看 SubscribeMediaType{@link #SubscribeMediaType}。
     * @param [in] video_config 视频订阅配置，参看 SubscribeVideoConfig{@link #SubscribeVideoConfig}。
     * @notes  <br>
     *        + 你必须通过 onStreamAdd{@link #IRTCRoomEventHandler#onStreamAdd} 和 onStreamRemove{@link #IRTCRoomEventHandler#onStreamRemove} 两个回调获取当前房间里的音视频流信息，并调用本方法按需订阅流或修改订阅配置。  <br>
     *        + 若订阅失败，你会收到 onRoomError{@link #IRTCRoomEventHandler#onRoomError} 回调通知，具体失败原因参看 ErrorCode{@link #ErrorCode}。
     *        + 若调用 pauseAllSubscribedStream{@link #IRTCRoom#pauseAllSubscribedStream} 暂停接收远端音视频流，此时仍可使用该方法对暂停接收的流进行设置，你会在调用 resumeAllSubscribedStream{@link #IRTCRoom#resumeAllSubscribedStream} 恢复接收流后收到修改设置后的流。  <br>
     */
    virtual void subscribeUserStream(const char* user_id, StreamIndex stream_type, SubscribeMediaType media_type, const SubscribeVideoConfig& video_config) = 0;
    /** 
     * @type api
     * @region 视频管理
     * @brief 设置期望订阅的远端视频流的参数。
     * @param [in] user_id 期望订阅的远端视频流发布用户的 ID。
     * @param [in] remote_video_config 期望订阅的远端视频流参数，参看 RemoteVideoConfig{@link #RemoteVideoConfig}。
     * @notes <br>
     *        + 若使用 342 及以前版本的 SDK，调用该方法前请联系技术支持人员通过配置下发开启按需订阅功能。  <br>
     *        + 该方法仅在发布端调用 enableSimulcastMode{@link #IRtcEngine#enableSimulcastMode} 开启了发送多路视频流的情况下生效，此时订阅端将收到来自发布端与期望设置的参数最相近的一路流；否则订阅端只会收到一路参数为分辨率 640px × 360px、帧率 15fps 的视频流。  <br>
     *        + 若发布端开启了推送多路流功能，但订阅端不对流参数进行设置，则默认接受发送端设置的分辨率最大的一路视频流。  <br>
     *        + 该方法需在进房后调用，若想进房前设置，你需调用 joinRoom{@link #IRTCRoom#joinRoom}，并对 `room_config` 中的 `remote_video_config` 进行设置。  <br>
     *        + SDK 会根据发布端和所有订阅端的设置灵活调整视频流的参数，具体调整策略详见[推送多路流](https://www.volcengine.com/docs/6348/70139)文档。
     */
    virtual void setRemoteVideoConfig(const char *user_id,const RemoteVideoConfig &remote_video_config) = 0;
    /** 
     * @type api
     * @region 房间管理
     * @brief 订阅房间内指定的通过摄像头/麦克风采集的媒体流，或更新对指定远端用户的订阅选项
     * @param [in] user_id 指定订阅的远端发布音视频流的用户 ID。
     * @param [in] type 媒体流类型，用于指定订阅音频/视频。参看 MediaStreamType{@link #MediaStreamType}。
     * @notes  <br>
     *        + 当调用本接口时，当前用户已经订阅该远端用户，不论是通过手动订阅还是自动订阅，都将根据本次传入的参数，更新订阅配置。<br>
     *        + 你必须先通过 onUserPublishStream{@link #IRTCRoomEventHandler#onUserPublishStream} 回调获取当前房间里的远端摄像头音视频流信息，然后调用本方法按需订阅。  <br>
     *        + 调用该方法后，你会收到 onStreamSubscribed{@link #IRTCRoomEventHandler#onStreamSubscribed} 通知方法调用结果。  <br>
     *        + 成功订阅远端用户的媒体流后，订阅关系将持续到调用 unsubscribeStream{@link #RTCEngine#unsubscribeStream} 取消订阅或本端用户退房。 <br>
     *        + 关于其他调用异常，你会收到 onStreamStateChanged{@link #IRTCRoomEventHandler#onStreamStateChanged} 回调通知，具体异常原因参看 ErrorCode{@link #ErrorCode}。
     */
    virtual void subscribeStream(const char *user_id,MediaStreamType type) = 0;
    /** 
     * @type api
     * @region 房间管理
     * @brief 取消订阅房间内指定的通过摄像头/麦克风采集的媒体流。  <br>
     *        该方法对自动订阅和手动订阅模式均适用。
     * @param [in] user_id 指定取消订阅的远端发布音视频流的用户 ID。
     * @param [in] type 媒体流类型，用于指定取消订阅音频/视频。参看 MediaStreamType{@link #MediaStreamType}。
     * @notes  <br>
     *        + 调用该方法后，你会收到 onStreamSubscribed{@link #IRTCRoomEventHandler#onStreamSubscribed} 通知流的退订结果。  <br>
     *        + 关于其他调用异常，你会收到 onStreamStateChanged{@link #IRTCRoomEventHandler#onStreamStateChanged} 回调通知，具体失败原因参看 ErrorCode{@link #ErrorCode}。
     */
    virtual void unsubscribeStream(const char *user_id,MediaStreamType type) = 0;
    /** 
     * @type api
     * @region 房间管理
     * @brief 订阅房间内指定的远端屏幕共享音视频流，或更新对指定远端用户的订阅选项
     * @param [in] user_id 指定订阅的远端发布屏幕流的用户 ID。
     * @param [in] type 媒体流类型，用于指定订阅音频/视频。参看 MediaStreamType{@link #MediaStreamType}。
     * @notes  <br>
     *        + 当调用本接口时，当前用户已经订阅该远端用户，不论是通过手动订阅还是自动订阅，都将根据本次传入的参数，更新订阅配置。<br>
     *        + 你必须先通过 onUserPublishScreen{@link #IRTCRoomEventHandler#onUserPublishScreen} 回调获取当前房间里的远端屏幕流信息，然后调用本方法按需订阅。  <br>
     *        + 调用该方法后，你会收到 onStreamSubscribed{@link #IRTCRoomEventHandler#onStreamSubscribed} 通知流的订阅结果。  <br>
     *        + 成功订阅远端用户的媒体流后，订阅关系将持续到调用 unsubscribeScreen{@link #RTCEngine#unsubscribeScreen} 取消订阅或本端用户退房。 <br>
     *        + 关于其他调用异常，你会收到 onStreamStateChanged{@link #IRTCRoomEventHandler#onStreamStateChanged} 回调通知，具体异常原因参看 ErrorCode{@link #ErrorCode}。
     */
    virtual void subscribeScreen(const char *user_id,MediaStreamType type) = 0;
    /** 
     * @type api
     * @region 房间管理
     * @brief 取消订阅房间内指定的远端屏幕共享音视频流。  <br>
     *        该方法对自动订阅和手动订阅模式均适用。
     * @param [in] user_id 指定取消订阅的远端发布屏幕流的用户 ID。
     * @param [in] type 媒体流类型，用于指定取消订阅音频/视频。参看 MediaStreamType{@link #MediaStreamType}。
     * @notes  <br>
     *        + 调用该方法后，你会收到 onStreamSubscribed{@link #IRTCRoomEventHandler#onStreamSubscribed} 通知流的退订结果。  <br>
     *        + 关于其他调用异常，你会收到 onStreamStateChanged{@link #IRTCRoomEventHandler#onStreamStateChanged} 回调通知，具体失败原因参看 ErrorCode{@link #ErrorCode}。
     */
    virtual void unsubscribeScreen(const char *user_id,MediaStreamType type) = 0;
    /** 
     * @type api
     * @region 多房间
     * @brief 停止订阅指定的房间内远端音视频流。  <br>
     *        关闭自动订阅功能，使用手动订阅模式时用户调用此方法停止订阅已订阅的音视频流。  <br>
     *        此方法仅在关闭自动订阅功能时生效。用户需在加入房间时设置 config 关闭自动订阅功能以使用手动订阅模式。  <br>
     * @param [in] user_id 指定停止订阅的远端音视频流的用户的ID。  <br>
     * @param [in] is_screen 指定停止的流是不是屏幕流。  <br>
     * @notes  <br>
     *       + 不管是否订阅了指定的远端音视频流，都可以调用此方法停止订阅。停止订阅的 stream_id 无效或未订阅时，SDK不会做任何处理，没有负面影响。  <br>
     */
    virtual void unsubscribe(const char* user_id, bool is_screen) = 0;
    /**
     * @hidden
     */
    virtual void enableSubscribeLocalStream(bool enable) = 0;
    /** 
     * @hidden
     * @deprecated since 323.1, use enableAudioPropertiesReport instead
     * @type api
     * @region 多房间
     * @brief 开启/关闭音量提示。默认关闭。<br>
     *        开启音量提示后，将按设置的时间间隔收到本地采集音量或订阅的远端用户的音量信息回调。
     *        关于回调的具体信息，参看 onAudioVolumeIndication{@link #IRTCRoomEventHandler#onAudioVolumeIndication}
     * @param [in] interval 收到音量提示回调的时间间隔：  <br>
     *                + ≤ 0：禁用音量提示功能。  <br>
     *                + > 0：启用音量提示功能，并设置收到音量提示回调的时间间隔。单位为毫秒。<br>
     *                建议设置为大于等于 200 毫秒；小于 10 毫秒时，行为未定义。
     */
    virtual void setAudioVolumeIndicationInterval(int interval) = 0;
    /** 
     * @type api
     * @region 多房间
     * @brief 调节来自远端用户的音频播放音量
     * @param [in] user_id 音频来源的远端用户 ID
     * @param [in] volume 音频播放音量值和原始音量的比值，范围是 [0, 400]，单位为 %，自带溢出保护。为保证更好的通话质量，建议将 volume 值设为 [0,100]。 <br>
     *              + 0: 静音  <br>
     *              + 100: 原始音量，默认值  <br>
     *              + 400: 最大可为原始音量的 4 倍(自带溢出保护)  <br>
     */
    virtual void setRemoteAudioPlaybackVolume(const char* user_id, int volume) = 0;

    virtual void setAudioAlignmentProperty(const RemoteStreamKey& streamKey, AudioAlignmentMode mode) = 0;

    /** 
     * @hidden
     * @deprecated since 326.1, use pauseAllSubscribedStream/resumeAllSubscribedStream instead
     * @type api
     * @region 多房间
     * @brief 设置对来自远端的所有音频流的接收状态。默认为接收。
     * @param [in] mute_state 接收状态。参看：MuteState{@link #MuteState}
     * @notes 本方法只影响本地是否接收远端音频流，并不影响远端音频设备的采集发送功能。
     */
    virtual void muteAllRemoteAudio(MuteState mute_state) = 0;
    /** 
     * @type api
     * @region 多房间
     * @brief 暂停接收来自远端的媒体流。
     * @param [in] media_type 媒体流类型，指定需要暂停接收音频还是视频流，参看 PauseResumeControlMediaType{@link #PauseResumeControlMediaType}。
     * @notes  <br>
     *        + 该方法仅暂停远端流的接收，并不影响远端流的采集和发送；  <br>
     *        + 该方法不改变用户的订阅状态以及订阅流的属性。  <br>
     *        + 若想恢复接收远端流，需调用 resumeAllSubscribedStream{@link #IRTCRoom#resumeAllSubscribedStream}。
     */
    virtual void pauseAllSubscribedStream(PauseResumeControlMediaType media_type) = 0;
    /** 
     * @type api
     * @region 多房间
     * @brief 恢复接收来自远端的媒体流
     * @param [in] media_type 媒体流类型，指定需要暂停接收音频还是视频流，参看 PauseResumeControlMediaType{@link #PauseResumeControlMediaType}
     * @notes <br>
     *        + 该方法仅恢复远端流的接收，并不影响远端流的采集和发送；  <br>
     *        + 该方法不改变用户的订阅状态以及订阅流的属性。
     */
    virtual void resumeAllSubscribedStream(PauseResumeControlMediaType media_type) = 0;
    /** 
     * @hidden
     * @deprecated since 326.1, use subscribeUserStream instead
     * @type api
     * @region 多房间
     * @brief 设置对来自远端指定用户的音频流的接收状态。默认为接收。
     * @param [in] uid 指定远端用户的 ID
     * @param [in] mute_state 接收状态。参看：MuteState{@link #MuteState}
     * @notes 本方法只影响本地是否接收远端音频流，并不影响远端音频设备的采集发送功能。
     */
    virtual void muteRemoteAudio(const char* uid, MuteState mute_state) = 0;
#ifndef ByteRTC_AUDIO_ONLY
    /**
     * @hidden
    */
    virtual void updateCloudRending(const char* cloudrenderJsonString) = 0;


    /** 
     * @type api
     * @region 多房间
     * @brief 设置发流端音画同步。  <br>
     *        当同一用户同时使用两个通话设备分别采集发送音频和视频时，有可能会因两个设备所处的网络环境不一致而导致发布的流不同步，此时你可以在视频发送端调用该接口，SDK 会根据音频流的时间戳自动校准视频流，以保证接收端听到音频和看到视频在时间上的同步性。
     * @param [in] audio_user_id 音频发送端的用户 ID，将该参数设为空则可解除当前音视频的同步关系。
     * @notes <br>
     *        + 该方法在进房前后均可调用。  <br>
     *        + 进行音画同步的音频发布用户 ID 和视频发布用户 ID 须在同一个 RTC 房间内。  <br>
     *        + 调用该接口后音画同步状态发生改变时，你会收到 onAVSyncStateChange{@link #IRTCRoomEventHandler#onAVSyncStateChange} 回调。  <br>
     *        + 同一 RTC 房间内允许存在多个音视频同步关系，但需注意单个音频源不支持与多个视频源同时同步。  <br>
     *        + 如需更换同步音频源，再次调用该接口传入新的 `audio_user_id` 即可；如需更换同步视频源，需先解除当前的同步关系，后在新视频源端开启同步。
     */
    virtual void setMultiDeviceAVSync(const char* audio_user_id) = 0;


    /** 
     * @deprecated since 3.52, use startPushMixedStreamToCDN instead.
     * @type api
     * @region 多房间
     * @brief 新增转推直播任务，并设置合流的图片、视频视图布局和音频属性。  <br>
     *        同一个任务中转推多路直播流时，SDK 会先将多路流合成一路流，然后再进行转推。
     * @param [in] task_id 转推直播任务 ID。<br>
     *               你可以在同一房间内发起多个转推直播任务，并用不同的任务 ID 加以区。当你需要发起多个转推直播任务时，应使用多个 ID；当你仅需发起一个转推直播任务时，建议使用空字符串。
     * @param [in] param 转推直播配置参数。参看 ITranscoderParam{@link #ITranscoderParam}。
     * @param [in] observer 端云一体转推直播观察者。参看 ITranscoderObserver{@link #ITranscoderObserver}。  <br>
     *        通过注册 observer 接收转推直播相关的回调。
     * @notes  <br>
     *       + 调用该方法后，关于启动结果和推流过程中的错误，会收到 onStreamMixingEvent{@link #ITranscoderObserver#onStreamMixingEvent} 回调。
     *       + 调用 stopLiveTranscoding{@link #IRtcEngine#stopLiveTranscoding} 停止转推直播。
     */
    virtual void startLiveTranscoding(const char* task_id, ITranscoderParam* param, ITranscoderObserver* observer) = 0;
    /** 
     * @deprecated since 3.52, use stopPushStreamToCDN instead.
     * @type api
     * @region 多房间
     * @brief 停止转推直播。，会收到 onStreamMixingEvent{@link #ITranscoderObserver#onStreamMixingEvent} 回调。  <br>
     *        关于启动转推直播，参看 startLiveTranscoding{@link #IRtcEngine#startLiveTranscoding}}。
     * @param [in] task_id 转推直播任务 ID。可以指定想要停止的转推直播任务。
     */
    virtual void stopLiveTranscoding(const char* task_id) = 0;
    /** 
     * @deprecated since 3.52, use updatePushMixedStreamToCDN instead.
     * @type api
     * @region 多房间
     * @brief 更新转推直播参数，会收到 onStreamMixingEvent{@link #ITranscoderObserver#onStreamMixingEvent} 回调。  <br>
     *        使用 startLiveTranscoding{@link #IRtcEngine#startLiveTranscoding}} 启用转推直播功能后，使用此方法更新功能配置参数。
     * @param [in] task_id 转推直播任务 ID。指定想要更新参数设置的转推直播任务。
     * @param [in] param 配置参数，参看 ITranscoderParam{@link #ITranscoderParam}。
     */
    virtual void updateLiveTranscoding(const char* task_id, ITranscoderParam* param) = 0;
    /** 
     * @type api
     * @region 多房间
     * @brief 停止转推直播。，会收到 onMixingEvent{@link #IMixedStreamObserver#onMixingEvent} 回调。  <br>
     *        关于启动转推直播，参看 startPushMixedStreamToCDN{@link #IRtcEngine#startPushMixedStreamToCDN}}。
     * @param [in] task_id 转推直播任务 ID。可以指定想要停止的转推直播任务。
     */
    virtual void stopPushStreamToCDN(const char* task_id) = 0;
    /** 
     * @deprecated  since 336, use setRemoteStreamVideoCanvas instead
     * @hidden
     * @type api
     * @region 多房间
     * @brief 设置来自指定远端用户 user_id 的视频渲染时，使用的视图，并设置渲染模式。 <br>
     *        如果需要解除某个用户的绑定视图，你可以把 view 设置为空。
     * @param [in] user_id 视频来源的远端用户 ID。
     * @param [in] index 视频流属性，参看 StreamIndex{@link #StreamIndex}
     * @param [in] canvas 视图信息和渲染模式，参看：VideoCanvas{@link #VideoCanvas}
     * @return  <br>
     *        + 0：成功  <br>
     *        + !0：失败  <br>
     * @notes  <br>
     *        + 你应在加入房间后，绑定视图。退出房间后，此设置不失效。
     *        + 实际使用时，你可以在收到回调 onUserJoined{@link #IRTCRoomEventHandler#onUserJoined} 或 onFirstRemoteVideoFrameRendered{@link #IRtcEngineEventHandler#onFirstRemoteVideoFrameRendered} 时获得远端用户 user_id。  <br>
     *        + 这两个回调的差别是：如果启用了视频录制功能，视频录制服务会作为一个哑客户端加入房间，因此其他客户端会收到对应的 onUserJoined{@link #IRTCRoomEventHandler#onUserJoined} 回调，而不会收到 onFirstRemoteVideoFrameDecoded{@link #IRtcEngineEventHandler#onFirstRemoteVideoFrameDecoded} 回调。你不应给录制的哑亚客户端绑定视图（因为它不会发送视频流）。
     */
    virtual void setRemoteVideoCanvas(const char* user_id, StreamIndex index, const VideoCanvas& canvas) = 0;
    /** 
     * @deprecated since 325.1
     * @hidden
     * @type api
     * @region 多房间
     * @brief 去除所有远端视频。
     */
    virtual void removeAllRemoteVideo() = 0;
    /** 
     * @deprecated since 325.1
     * @hidden
     * @type api
     * @region 多房间
     * @brief 去除屏幕共享所有远端视图。
     */
    virtual void removeAllRemoteScreen() = 0;
    /** 
     * @hidden
     * @deprecated since 326.1, use pauseAllSubscribedStream/resumeAllSubscribedStream instead
     * @type api
     * @region 多房间
     * @brief 设置是否播放所有远端视频流
     * @param  [in] muteState 接收状态，标识是否接收所有远端音/视频流，参看 MuteState{@link #MuteState}   <br>
     *       + true：停止播放  <br>
     *       + false：开启播放  <br>
     * @notes 本方法不影响远端视频采集和发送状态
     */
    virtual void muteAllRemoteVideo(MuteState muteState) = 0;
    /** 
     * @hidden
     * @deprecated since 326.1, use subscribeUserStream instead
     * @type api
     * @region 多房间
     * @brief 设置是否播放远端视频流
     * @param [in] userid 视频来源的远端用户 ID
     * @param  [in] muteState 接收状态，标识是否接收远端音/视频流，参看 MuteState{@link #MuteState}   <br>
     *       + true：停止播放  <br>
     *       + false：开启播放  <br>
     * @notes 本方法不影响远端视频采集和发送状态
     */
    virtual void muteRemoteVideo(const char* userid, MuteState muteState) = 0;
#endif
    /**
     * @hidden
     */
    virtual void setCustomUserRole(const char* role) = 0;
    /** 
     * @hidden
     * @deprecated since 326.1, use joinRoom instead
     * @type api
     * @region 多房间
     * @brief 设置订阅模式。  <br>
     *        用户调用此方法设置房间中音视频流的订阅模式。默认为自动订阅。  <br>
     *        如需开启手动订阅功能，建议在调用 joinRoom{@link #IRTCRoom#joinRoom} 方法加入房间前完成设置。  <br>
     * @param [in] audio_mode 音频流的订阅模式。参看 SubscribeMode{@link #SubscribeMode}。  <br>
     * @param [in] video_mode 视频流的订阅模式。参看 SubscribeMode{@link #SubscribeMode}。  <br>
     */
    virtual void enableAutoSubscribe(SubscribeMode audio_mode, SubscribeMode video_mode) = 0;
    /** 
     * @type api
     * @region 多房间
     * @brief 开始跨房间转发媒体流。
     *        在用户进入房间后调用本接口，实现向多个房间转发媒体流，适用于跨房间连麦等场景。<br>
     * @param [in] configuration 跨房间媒体流转发指定房间的信息。参看 ForwardStreamConfiguration{@link #ForwardStreamConfiguration}。
     * @return  <br>
     *        0: 方法调用成功  <br>
     *        <0: 方法调用失败  <br>
     * @notes <br>
     *        + 调用本方法后，将在本端触发 onForwardStreamStateChanged{@link #IRTCRoomEventHandler#onForwardStreamStateChanged} 回调。
     *        + 调用本方法后，你可以通过监听 onForwardStreamEvent{@link #IRTCRoomEventHandler#onForwardStreamEvent} 回调来获取各个目标房间在转发媒体流过程中的相关事件。
     *        + 开始转发后，目标房间中的用户将接收到本地用户进房 onUserJoined{@link #IRTCRoomEventHandler#onUserJoined} 和发流 onUserPublishStream{@link #IRTCRoomEventHandler#onUserPublishStream}/onUserPublishScreen{@link #IRTCRoomEventHandler#onUserPublishScreen} 的回调。
     *        + 调用本方法后，可以调用 updateForwardStreamToRooms{@link #IRTCRoom#updateForwardStreamToRooms} 更新目标房间信息，例如，增加或减少目标房间等。
     *        + 调用本方法后，可以调用 stopForwardStreamToRooms{@link #IRTCRoom#stopForwardStreamToRooms} 停止向所有房间转发媒体流。
     *        + 调用本方法后，可以调用 pauseForwardStreamToAllRooms{@link #IRTCRoom#pauseForwardStreamToAllRooms} 暂停向所有房间转发媒体流。
     */
    virtual int startForwardStreamToRooms(const ForwardStreamConfiguration& configuration) = 0;
    /** 
     * @type api
     * @region 房间管理
     * @brief 更新跨房间媒体流转发信息。<br>
     *        通过 startForwardStreamToRooms{@link #IRTCRoom#startForwardStreamToRooms} 发起媒体流转发后，可调用本方法增加或者减少目标房间，或更新房间密钥。
     *        调用本方法增加或删减房间后，将在本端触发 onForwardStreamStateChanged{@link #IRTCRoomEventHandler#onForwardStreamStateChanged} 回调，包含发生了变动的目标房间中媒体流转发状态。
     * @param [in] configuration 跨房间媒体流转发目标房间信息。参看 ForwardStreamConfiguration{@link #ForwardStreamConfiguration}。
     * @return  <br>
     *        0: 方法调用成功  <br>
     *        <0: 方法调用失败  <br>
     * @notes <br>
     *        + 增加目标房间后，新增目标房间中的用户将接收到本地用户进房 onUserJoined{@link #IRTCRoomEventHandler#onUserJoined} 和发布 onUserPublishStream{@link #IRTCRoomEventHandler#onUserPublishStream}/onUserPublishScreen{@link #IRTCRoomEventHandler#onUserPublishScreen} 的回调。
     *        + 删减目标房间后，原目标房间中的用户将接收到本地用户停止发布 onUserUnPublishStream{@link #IRtcEngineEventHandler#onUserUnPublishStream}/onUserUnPublishScreen{@link #IRtcEngineEventHandler#onUserUnPublishScreen} 和退房 onUserLeave{@link #IRTCRoomEventHandler#onUserLeave} 的回调。
     */
    virtual int updateForwardStreamToRooms(const ForwardStreamConfiguration& configuration) = 0;
    /** 
     * @type api
     * @region 多房间
     * @brief 停止跨房间媒体流转发。
     *        通过 startForwardStreamToRooms{@link #IRTCRoom#startForwardStreamToRooms} 发起媒体流转发后，可调用本方法停止向所有目标房间转发媒体流。
     * @notes <br>
     *        + 调用本方法后，将在本端触发 onForwardStreamStateChanged{@link #IRTCRoomEventHandler#onForwardStreamStateChanged} 回调。
     *        + 调用本方法后，原目标房间中的用户将接收到本地用户停止发布 onUserUnPublishStream{@link #IRtcEngineEventHandler#onUserUnPublishStream}/onUserUnPublishScreen{@link #IRtcEngineEventHandler#onUserUnPublishScreen} 和退房 onUserLeave{@link #IRTCRoomEventHandler#onUserLeave} 的回调。
     *        + 如果需要停止向指定的房间转发媒体流，请调用 updateForwardStreamToRooms{@link #IRTCRoom#updateForwardStreamToRooms} 更新房间信息。
     *        + 如果需要暂停转发，请调用 pauseForwardStreamToAllRooms{@link #IRTCRoom#pauseForwardStreamToAllRooms}，并在之后随时调用 resumeForwardStreamToAllRooms{@link #IRTCRoom#resumeForwardStreamToAllRooms} 快速恢复转发。
     */
    virtual void stopForwardStreamToRooms() = 0;
    /** 
     * @type api
     * @region 多房间
     * @brief 暂停跨房间媒体流转发。
     *        通过 startForwardStreamToRooms{@link #IRTCRoom#startForwardStreamToRooms} 发起媒体流转发后，可调用本方法暂停向所有目标房间转发媒体流。
     *        调用本方法暂停向所有目标房间转发后，你可以随时调用 resumeForwardStreamToAllRooms{@link #IRTCRoom#resumeForwardStreamToAllRooms} 快速恢复转发。
     * @notes 调用本方法后，目标房间中的用户将接收到本地用户停止发布 onUserUnPublishStream{@link #IRtcEngineEventHandler#onUserUnPublishStream}/onUserUnPublishScreen{@link #IRtcEngineEventHandler#onUserUnPublishScreen} 和退房 onUserLeave{@link #IRTCRoomEventHandler#onUserLeave} 的回调。
     */
     virtual void pauseForwardStreamToAllRooms() = 0;
    /** 
     * @type api
     * @region 多房间
     * @brief 恢复跨房间媒体流转发。
     *        调用 pauseForwardStreamToAllRooms{@link #IRTCRoom#pauseForwardStreamToAllRooms} 暂停转发之后，调用本方法恢复向所有目标房间转发媒体流。
     * @notes <br>
     *        目标房间中的用户将接收到本地用户进房 onUserJoined{@link #IRTCRoomEventHandler#onUserJoined} 和发布 onUserPublishStream{@link #IRTCRoomEventHandler#onUserPublishStream}/onUserPublishScreen{@link #IRTCRoomEventHandler#onUserPublishScreen} 的回调。
     */
    virtual void resumeForwardStreamToAllRooms() = 0;
    /** 
     * @type api
     * @brief 发布一路公共流<br>
     *        用户可以指定房间内多个用户发布的媒体流合成一路公共流。使用同一 `appID` 的用户，可以调用 startPlayPublicStream{@link #IRtcEngine#startPlayPublicStream} 获取和播放指定的公共流。
     * @param public_stream_id 公共流 ID
     * @param param 公共流参数。详见 IPublicStreamParam{@link #IPublicStreamParam}。<br>
     *              一路公共流可以包含多路房间内的媒体流，按照指定的布局方式进行聚合。<br>
     *              如果指定的媒体流还未发布，则公共流将在指定流开始发布后实时更新。
     * @return
     *        + 0: 成功。同时将收到 onPushPublicStreamResult{@link #IRtcEngineEventHandler#onPushPublicStreamResult} 回调。<br>
     *        + !0: 失败。当参数不合法或参数为空，调用失败。<br>
     * @notes <br>
     *        + 同一用户使用同一公共流 ID 多次调用本接口无效。如果你希望更新公共流参数，调用 updatePublicStreamParam{@link #IRtcEngine#updatePublicStreamParam} 接口。<br>
     *        + 不同用户使用同一公共流 ID 多次调用本接口时，RTC 将使用最后一次调用时传入的参数更新公共流。<br>
     *        + 使用不同的 ID 多次调用本接口可以发布多路公共流。<br>
     *        + 调用 stopPushPublicStream{@link #IRtcEngine#stopPushPublicStream} 停止发布公共流。<br>
     *        + 关于公共流功能的介绍，详见[发布和订阅公共流](https://www.volcengine.com/docs/6348/108930)
     */
    virtual int startPushPublicStream(const char* public_stream_id, IPublicStreamParam* param) = 0;
    /** 
     * @type api
     * @brief 停止发布当前用户发布的公共流<br>
     *        关于发布公共流，查看 startPushPublicStream{@link #IRtcEngine#startPushPublicStream}。
     * @param public_stream_id 公共流 ID<br>
     *                  指定的流必须为当前用户所发布。
     * @return
     *        + 0: 成功<br>
     *        + !0: 失败<br>
     */
    virtual int stopPushPublicStream(const char* public_stream_id) = 0;
    /** 
     * @type api
     * @brief 更新公共流参数<br>
     *        关于发布公共流，查看 startPushPublicStream{@link #IRtcEngine#startPushPublicStream}。
     *        建议调用更新公共流前判断公共流是否已经成功启动，相关回调详见：onPushPublicStreamResult{@link #IRTCVideoEventHandler#onPushPublicStreamResult}。        
     * @param public_stream_id 公共流 ID<br>
     * @param param 公共流参数。详见 IPublicStreamParam{@link #IPublicStreamParam}。<br>
     *              指定的流必须为当前用户所发布的。
     * @return
     *        + 0: 成功<br>
     *        + !0: 失败<br>
     */
    virtual int updatePublicStreamParam(const char* public_stream_id, IPublicStreamParam* param) = 0;

    /** 
     * @type api
     * @region 网络管理
     * @brief 开启音视频回路测试。  <br>
     *        在进房前，用户可调用该接口对音视频通话全链路进行检测，包括对音视频设备以及用户上下行网络的检测，从而帮助用户判断是否可以正常发布和接收音视频流。  <br>
     *        开始检测后，SDK 会录制你声音或视频。如果你在设置的延时范围内收到了回放，则视为音视频回路测试正常。
     * @param [in] echo_test_config 回路测试参数设置，参看 EchoTestConfig{@link #EchoTestConfig}。
     * @param [in] play_delay_time 音视频延迟播放的时间间隔，用于指定在开始检测多长时间后期望收到回放。取值范围为 [2,10]，单位为秒，默认为 2 秒。
     * @return 方法调用结果：  <br>
     *        + 0：成功  <br>
     *        + -1：失败，当前用户已经在检测中  <br>
     *        + -2：失败，用户已进房  <br>
     *        + -3：失败，音视频均未采集  <br>
     *        + -4：失败，参数异常  <br>
     *        + -5：失败，已经存在相同 roomId 的房间
     * @notes  <br>
     *        + 调用该方法开始音视频回路检测后，你可以调用 stopEchoTest{@link #IRtcEngine#stopEchoTest} 立即结束测试，也可等待测试 60s 后自动结束，以更换设备进行下一次测试，或进房。  <br>
     *        + 在该方法之前调用的所有跟设备控制、流控制相关的方法均在开始检测时失效，在结束检测后恢复生效。  <br>
     *        + 在调用 startEchoTest{@link #IRtcEngine#startEchoTest} 和 stopEchoTest{@link #IRtcEngine#stopEchoTest} 之间调用的所有跟设备采集、流控制、进房相关的方法均不生效，并会收到 onWarning{@link #IRtcEngineEventHandler#onWarning} 回调，提示警告码为 `kWarningCodeInEchoTestMode`。  <br>
     *        + 音视频回路检测的结果会通过 onEchoTestResult{@link #IRtcEngineEventHandler#onEchoTestResult} 回调通知。
     */
    virtual int startEchoTest(EchoTestConfig echo_test_config, unsigned int play_delay_time) = 0;

    /** 
     * @type api
     * @region 网络管理
     * @brief 停止音视频回路测试。  <br>
     *        调用 startEchoTest{@link #IRtcEngine#startEchoTest} 开启音视频回路检测后，你必须调用该方法停止检测。
     * @return 方法调用结果：  <br>
     *        + 0：成功  <br>
     *        + -1：失败，未开启回路检测
     * @notes 音视频回路检测结束后，所有对系统设备及音视频流的控制均会恢复到开始检测前的状态。
     */
    virtual int stopEchoTest() = 0;

    /** 
     * @type api
     * @region 云代理
     * @brief 开启云代理
     * @param [in] configuration 云代理服务器信息列表。参看 CloudProxyConfiguration{@link #CloudProxyConfiguration}。
     * @notes  <br>
     *        + 在加入房间前调用此接口  <br>
     *        + 在开启云代理后，进行通话前网络探测 <br>
     *        + 开启云代理后，并成功链接云代理服务器后，会收到 onCloudProxyConnected{@link #IRtcEngineEventHandler#onCloudProxyConnected}。<br>
     *        + 要关闭云代理，调用 stopCloudProxy{@link #IRtcEngine#stopCloudProxy}。
     */
    virtual void startCloudProxy(const CloudProxyConfiguration& configuration) = 0;
    /** 
     * @type api
     * @region 云代理
     * @brief 关闭云代理
     * @notes 要开启云代理，调用 startCloudProxy{@link #IRtcEngine#startCloudProxy}。
     */
    virtual void stopCloudProxy() = 0;

    /** 
     * @type api
     * @region cdn
     * @brief 调用实验性API
     * @notes 入参 params 格式如下：
     * {
     *   "api_name":"startPublish",
     *   "params":{
     *     "streamID":"",
     *     "observer":"",
     *     "uri":"",
     *     "option":""
     *   }
     * }
     * @return ret = 0 ? success : failed
     */
    virtual int invokeExperimentalAPI(const char* param) = 0;


    /** 
     * @type api
     * @brief 用蜂窝网络改善通话质量。
     * @param config 蜂窝增强的配置参数
     * @notes <br>
     *       + 调用此接口可设置蜂窝增强的媒体类型。
     */
    virtual void setCellularEnhancement(const MediaTypeEnhancementConfig& config) = 0;
};

/** 
 * @type api
 * @region 引擎管理
 * @brief 创建 RTCEngine 实例。  <br>
 *        如果当前线程中未创建引擎实例，那么你必须先使用此方法，以使用 RTC 提供的各种音视频能力。  <br>
 *        如果当前线程中已创建了引擎实例，再次调用此方法时，会创建另一个独立的引擎实例。
 * @param [in] app_id 每个应用的唯一标识符。只有使用相同的 app_id 生成的实例，才能够进行音视频通信。
 * @param [in] event_handler SDK 回调给应用层的 Callback 对象，详见 IRtcEngineEventHandler{@link #IRtcEngineEventHandler} 。
 * @param [in] parameters 用以覆盖默认参数的本引擎实例参数。JSON 字符串格式。
 * @return  <br>
 *        + IRtcEngine：创建成功。返回一个可用的 IRtcEngine{@link #IRtcEngine} 实例  <br>
 *        + Null：创建失败。
 * @notes  <br>
 *        + 如果你在同一个线程中创建了多个引擎实例，这些实例必须分别调用 destroyRtcEngine{@link #destroyRtcEngine} 销毁。
 *        + 在 Linux 平台上创建引擎实例的数量取决于系统的硬件性能。
 */
BYTERTC_API bytertc::IRtcEngine* createRtcEngine(const char* app_id,
        bytertc::IRtcEngineEventHandler* event_handler, const char* parameters);

/** 
 * @hidden
 * @region 引擎管理
 * @brief 创建 RTCEngine 实例。
 * @param [in] app_id  <br>
 *        每个应用的唯一标识符。不同的 AppId 生成的实例进行音视频通话完全独立，无法互通。
 * @param [in] event_handler  <br>
 *        SDK 回调给应用层的 Callback 对象，详见 IRtcEngineEventHandler{@link #IRtcEngineEventHandler} 。
 * @param [in] parameters 保留参数
 * @return 可用的 IRtcEngine{@link #IRtcEngine} 实例。
 * @notes  <br>
 *        + 该方法创建并初始化 IRtcEngine{@link #IRtcEngine} 实例。使用 IRtcEngine，必须先调用该接口进行初始化。  <br>
 *        + IRtcEngine{@link #IRtcEngine} 实例通过指定的 IRtcEngineEventHandler{@link #IRtcEngineEventHandler}
 *          通知应用程序引擎运行时的事件。IRtcEngineEventHandler{@link #IRtcEngineEventHandler} 中定义的所有方法都是可选实现的。
 */
BYTERTC_API bytertc::IRtcEngine* createRtcEngineWithPtr(
        const char* app_id, std::unique_ptr<bytertc::IRtcEngineEventHandler> event_handler,
        const char* parameters);

/** 
 * @type api
 * @region 引擎管理
 * @brief 销毁由 createRtcEngine{@link #createRtcEngine} 创建的 RTCEngine 实例，并释放所有相关资源。
 * @param [in] engine createRtcEngine{@link #createRtcEngine} 时，返回的实例。
 * @notes  <br>
 *        + 请确保和需要销毁的 IRtcEngine{@link #IRtcEngine} 实例相关的业务场景全部结束后，才调用此方法。如果在多线程场景下，调用此接口后，又调用了其他 IRtcEngine{@link #IRtcEngine} 相关接口，可能导致 SDK 崩溃。该方法在调用之后，会销毁所有和此 IRtcEngine{@link #IRtcEngine} 实例相关的内存，并且停止与媒体服务器的任何交互。  <br>
 *        + 调用本方法会启动 SDK 退出逻辑。引擎线程会保留，直到退出逻辑完成。因此，不要在回调线程中直接调用此 API，也不要在回调中等待主线程的执行，并同时在主线程调用本方法。不然会造成死锁。
 */
BYTERTC_API void destroyRtcEngine(bytertc::IRtcEngine* engine);

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

}    // namespace bytertc

#endif  // BYTE_RTC_INTERFACE_H__
