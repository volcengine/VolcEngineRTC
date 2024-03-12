/*
 * Copyright (c) 2020 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC Interface Lite
 */

#pragma once

#include "bytertc_room.h"
#include "rtc/bytertc_video_device_manager.h"
#include "rtc/bytertc_audio_frame.h"
#include "rtc/byte_rtc_asr_engine_event_handler.h"
#include "rtc/bytertc_audio_mixing_manager.h"
#include "rtc/bytertc_audio_effect_player.h"
#include "rtc/bytertc_media_player.h"
#include "rtc/bytertc_video_processor_interface.h"
#include "rtc/bytertc_camera_control_interface.h"
#include "bytertc_video_event_handler.h"
#include "rtc/bytertc_sing_scoring_interface.h"
#include "rtc/bytertc_ktv_manager_interface.h"

namespace bytertc {

/**
 * @locale zh
 * @type api
 * @brief 引擎 API
 */
/**
 * @locale en
 * @type api
 * @brief Engine API
 */
class IRTCVideo {
public:
    /**
     * @locale zh
     * @valid since 3.58.1
     * @type api
     * @region 音量管理
     * @brief 设置是否将录音信号静音（不改变本端硬件）。
     * @param index 流索引，指定调节主流/屏幕流音量，参看 [StreamIndex](70083#streamindex-2)。
     * @param mute 是否静音音频采集。<br>
     *        + True：静音（关闭麦克风）<br>
     *        + False：（默认）开启麦克风
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。具体失败原因参看 ReturnStatus{@link #ReturnStatus}。
     * @note 
              + 该方法支持选择静音或取消静音麦克风采集，而不影响 SDK 音频流发布状态。<br>
              + 静音后通过 setCaptureVolume{@link #IRTCVideo#setCaptureVolume} 调整音量不会取消静音状态，音量状态会保存至取消静音。<br>
              + 调用 startAudioCapture{@link #IRTCVideo#startAudioCapture} 开启音频采集前后，都可以使用此接口设置采集音量。
     */
    /**
     * @locale en
     * @valid since 3.58.1
     * @type api
     * @region Volume management
     * @brief Set whether to mute the recording signal (without changing the local hardware).
     * @param index Stream index, specifying the main stream or screen stream volume adjustment. See [StreamIndex](70083#streamindex-2).
     * @param mute Whether to mute audio capture.<br>
     *        + True: Mute (disable microphone) <br>
     *        + False: (Default) Enable microphone 
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Failure. See ReturnStatus{@link #ReturnStatus} for more details.
     * @note  
              + Calling this API does not affect the status of SDK audio stream publishing.<br>
              + Adjusting the volume by calling setCaptureVolume{@link #IRTCVideo#setCaptureVolume} after muting will not cancel the mute state. The volume state will be retained until unmuted.<br>
              + You can use this interface to set the capture volume before or after calling startAudioCapture{@link #IRTCVideo#startAudioCapture} to enable audio capture.
     */
    virtual int muteAudioCapture(StreamIndex index, bool mute) = 0;

    /**
     * @locale zh
     * @type api
     * @region 音量管理
     * @brief 调节音频采集音量
     * @param index 流索引，指定调节主流还是调节屏幕流的音量，参看 StreamIndex{@link #StreamIndex}
     * @param volume 采集的音量值和原始音量的比值，范围是 [0, 400]，单位为 %，自带溢出保护。<br>
     *                    只改变音频数据的音量信息，不涉及本端硬件的音量调节。<br>
     *        为保证更好的通话质量，建议将 volume 值设为 [0,100]。<br>
     *       + 0：静音  <br>
     *       + 100：原始音量  <br>
     *       + 400: 最大可为原始音量的 4 倍(自带溢出保护)  
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note 在开启音频采集前后，你都可以使用此接口设定采集音量。
     */
    /**
     * @locale en
     * @type api
     * @region Volume management
     * @brief Adjust the audio capture volume
     * @param index Index of the stream, whose volume needs to be adjusted. Refer to StreamIndex{@link #StreamIndex} for more details.
     * @param volume Ratio of capture volume to original volume. Ranging: [0,400]. Unit: %<br>
     *                     This changes the volume property of the audio data other than the hardware volume.<br>
     *        + 0: Mute <br>
     *        + 100: Original volume. To ensure the audio quality, we recommend [0, 100].<br>
     *        + 400: Four times the original volume with signal-clipping protection.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note  Call this API to set the volume of the audio capture before or during the audio capture.
     */
    virtual int setCaptureVolume(StreamIndex index, int volume) = 0;
    /**
     * @locale zh
     * @type api
     * @region 音量管理
     * @brief 调节本地播放的所有远端用户混音后的音量。<br>
     *        播放音频前或播放音频时，你都可以使用此接口设定播放音量。
     * @param volume 音频播放音量值和原始音量的比值，范围是 [0, 400]，单位为 %，自带溢出保护。  <br>
     *                    只改变音频数据的音量信息，不涉及本端硬件的音量调节。<br>
     *        为保证更好的通话质量，建议将 volume 值设为 [0,100]。  <br>
     *       + 0: 静音  <br>
     *       + 100: 原始音量  <br>
     *       + 400: 最大可为原始音量的 4 倍(自带溢出保护)  
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note 假设某远端用户 A 始终在被调节的目标用户范围内，当该方法与 setRemoteAudioPlaybackVolume{@link #IRTCVideo#setRemoteAudioPlaybackVolume} 或 setRemoteRoomAudioPlaybackVolume{@link #IRTCRoom#setRemoteRoomAudioPlaybackVolume} 共同使用时，本地收听用户 A 的音量将为两次设置的音量效果的叠加。
     */
    /**
     * @locale en
     * @type api
     * @region volume management
     * @brief Adjust the playback volume of the mixed remote audios.  You can call this API before or during the playback.
     * @param volume Ratio(%) of playback volume to original volume, in the range [0, 400], with overflow protection.  <br>
     *                    This changes the volume property of the audio data other than the hardware volume.<br>
     *        To ensure the audio quality, we recommend setting the volume to `100`.  <br>
     *        + 0: mute <br>
     *        + 100: original volume <br>
     *        + 400: Four times the original volume with signal-clipping protection.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note Suppose a remote user A is always within the range of the target user whose playback volume will be adjusted, if you use both this method and setRemoteAudioPlaybackVolume{@link #IRTCVideo#setRemoteAudioPlaybackVolume}/setRemoteRoomAudioPlaybackVolume{@link #IRTCRoom#setRemoteRoomAudioPlaybackVolume}, the volume that the local user hears from user A is the overlay of both settings.
     */
    virtual int setPlaybackVolume(const int volume) = 0;

    /**
     * @locale zh
     * @hidden(Linux)
     * @type api
     * @region 音频管理
     * @brief 开启/关闭耳返功能
     * @param mode 是否开启耳返功能，参看 EarMonitorMode{@link #EarMonitorMode}
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note 耳返功能仅支持设备通过 3.5mm 接口、USB 接口、或蓝牙方式直连耳机时可以使用。对于通过 HDMI 或 USB-C 接口连接显示器，再连接，或通过连接 OTG 外接声卡再连接的耳机，不支持耳返功能。
     */
    /**
     * @locale en
     * @hidden(Linux)
     * @type api
     * @region Audio management
     * @brief Turn on/off the earphone monitor function
     * @param mode Whether to turn on the earphone monitor function. See EarMonitorMode{@link #EarMonitorMode}.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note You can use ear monitoring feature when the earpiece is directly connected to the device by 3.5mm interface, USB interface, or BlueTooth. You cannot use ear monitoring feature when the earpiece is connected to a monitor via the HDMI or USB-C interface, and then connected to the device, or connected to an OTG external sound card, and then connected to the device.
     */
    virtual int setEarMonitorMode(EarMonitorMode mode) = 0;

    /**
     * @locale zh
     * @hidden(Linux)
     * @type api
     * @region 音频管理
     * @brief 设置耳返的音量
     * @param volume 耳返的音量相对原始音量的比值，取值范围：[0,100]，单位：%
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note 设置耳返音量前，你必须先调用 setEarMonitorMode{@link #IRTCVideo#setEarMonitorMode} 打开耳返功能。
     */
    /**
     * @locale en
     * @hidden(Linux)
     * @type api
     * @region Audio Management
     * @brief Set the volume of the earphone monitor
     * @param volume The volume of the earphone monitor, the value range: [0,100], the unit:%
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note Before setting the volume of the earphone monitor, you must first call setEarMonitorMode{@link #IRTCVideo#setEarMonitorMode} to turn on the earphone monitor function.
     */
    virtual int setEarMonitorVolume(const int volume) = 0;

    /**
     * @locale zh
     * @hidden(macOS,Windows,Linux,Android)
     * @type api
     * @region 蓝牙模式化设置
     * @brief 设置蓝牙模式
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note 仅在媒体场景下生效。
     */
    /**
     * @locale en
     * @hidden(macOS,Windows,Linux,Android)
     * @type api
     * @region  bluetooth mode settings
     * @brief  set bluetooh mode in media scenario
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note bluetooth mode can be setted only in media scenario.
     */
    virtual int setBluetoothMode(BluetoothMode mode) = 0;

    /**
     * @locale zh
     * @type api
     * @region 音频管理
     * @brief 开启内部音频采集。默认为关闭状态。  <br>
     *        内部采集是指：使用 RTC SDK 内置的音频采集机制进行音频采集。<br>
     *        调用该方法开启后，本地用户会收到 onAudioDeviceStateChanged{@link #IRTCVideoEventHandler#onAudioDeviceStateChanged} 的回调。 <br>
     *        非隐身用户进房后调用该方法，房间中的其他用户会收到 onUserStartAudioCapture{@link #IRTCVideoEventHandler#onUserStartAudioCapture} 的回调。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note  
     *       + 若未取得当前设备的麦克风权限，调用该方法后会触发 onAudioDeviceStateChanged{@link #IRTCVideoEventHandler#onAudioDeviceStateChanged} 回调，对应的错误码为 `MediaDeviceError.kMediaDeviceErrorDeviceNoPermission = 1`。<br>
     *       + 调用 stopAudioCapture{@link #IRTCVideo#stopAudioCapture} 可以关闭音频采集设备，否则，SDK 只会在销毁引擎的时候自动关闭设备。  <br>
     *       + 由于不同硬件设备初始化响应时间不同，频繁调用 stopAudioCapture{@link #IRTCVideo#stopAudioCapture} 和本接口闭麦/开麦可能出现短暂无声问题，建议使用 publishStream{@link #IRTCRoom#publishStream}/unpublishStream{@link #IRTCRoom#unpublishStream} 实现临时闭麦和重新开麦。<br>
     *       + 创建引擎后，无论是否发布音频数据，你都可以调用该方法开启音频采集，并且调用后方可发布音频。  <br>
     *       + 如果需要从自定义音频采集切换为内部音频采集，你必须先停止发布流，调用 setAudioSourceType{@link #IRTCVideo#setAudioSourceType} 关闭自定义采集，再调用此方法手动开启内部采集。
     */
    /**
     * @locale en
     * @type api
     * @region Audio management
     * @brief Start internal audio capture. The default is off.   <br>
     *        Internal audio capture refers to: capturing audio using the built-in module.<br>
     *        The local client will be informed via onAudioDeviceStateChanged{@link #IRTCVideoEventHandler#onAudioDeviceStateChanged} after starting audio capture by calling this API. <br>
     *        The remote clients in the room will be informed of the state change via onUserStartAudioCapture{@link #IRTCVideoEventHandler#onUserStartAudioCapture} after the visible user starts audio capture by calling this API..
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note   
     *        + To enable a microphone without the user's permission will trigger onWarning{@link #IRTCVideoEventHandler#onWarning}. <br>
     *        + Call stopAudioCapture{@link #IRTCVideo#stopAudioCapture} to stop the internal audio capture. Otherwise, the internal audio capture will sustain until you destroy the engine instance. <br>
     *       +  To mute and unmute microphones, we recommend using publishStream{@link #IRTCRoom#publishStream} and unpublishStream{@link #IRTCRoom#unpublishStream}, other than stopAudioCapture{@link #IRTCVideo#stopAudioCapture} and this API. Because starting and stopping capture devices often need some time waiting for the response of the device, that may lead to a short silence during the communication.<br>
     *        + Once you create the engine instance, you can start internal audio capture regardless of the audio publishing state. The audio stream will start publishing only after the audio capture starts. <br>
     *        + To switch from custom to internal audio capture, stop publishing before disabling the custom audio capture module and then call this API to enable the internal audio capture.
     */
    virtual int startAudioCapture() = 0;

    /**
     * @locale zh
     * @type api
     * @region 音频管理
     * @brief 立即关闭内部音频采集。默认为关闭状态。  <br>
     *        内部采集是指：使用 RTC SDK 内置的音频采集机制进行音频采集。<br>
     *        调用该方法，本地用户会收到 onAudioDeviceStateChanged{@link #IRTCVideoEventHandler#onAudioDeviceStateChanged} 的回调。  <br>
     *        非隐身用户进房后调用该方法后，房间中的其他用户会收到 onUserStopAudioCapture{@link #IRTCVideoEventHandler#onUserStopAudioCapture} 的回调。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note  
     *       + 调用 startAudioCapture{@link #startAudioCapture} 可以开启音频采集设备。  <br>
     *       + 如果不调用本方法停止内部视频采集，则只有当销毁引擎实例时，内部音频采集才会停止。
     */
    /**
     * @locale en
     * @type api
     * @region Audio management
     * @brief Stop internal audio capture. The default is off.   <br>
     *        Internal audio capture refers to: capturing audio using the built-in module.<br>
     *         The local client will be informed via  onAudioDeviceStateChanged{@link #IRTCVideoEventHandler#onAudioDeviceStateChanged}  after stopping audio capture by calling this API.<br>. <br>
     *        The remote clients in the room will be informed of the state change via onUserStopAudioCapture{@link #IRTCVideoEventHandler#onUserStopAudioCapture} after the visible client stops audio capture by calling this API.<br>.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note   
     *        + Call startAudioCapture{@link #startAudioCapture} to enable the internal audio capture. <br>
     *        + Without calling this API the internal audio capture will sustain until you destroy the engine instance.
     */
    virtual int stopAudioCapture() = 0;
    /**
     * @locale zh
     * @hidden(macOS,Windows,Linux)
     * @type api
     * @region 音频管理
     * @brief 设置音频场景类型。<br>
     *        你可以根据你的应用所在场景，选择合适的音频场景类型。<br>
     *        选择音频场景后，SDK 会自动根据客户端音频采集播放设备和状态，适用通话音量/媒体音量。
     * @param scenario 音频场景类型，参看 AudioScenarioType{@link #AudioScenarioType}。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note  
     *        + 建议在加入房间和调用音频相关接口之前，调用此接口设置音频场景类型。如果在此之后调用此接口，可能会引入音频卡顿。<br>
     *        + 通话音量更适合通话、会议等对信息准确度更高的场景。通话音量会激活系统硬件信号处理，使通话声音更清晰。同时，音量无法降低到 0。<br>
     *        + 媒体音量更适合娱乐场景，因其声音的表现力会更强。媒体音量下，最低音量可以为 0。
     */
    /**
     * @locale en
     * @hidden(macOS,Windows,Linux)
     * @type api
     * @region Audio management
     * @brief Sets the audio scenarios.<br>
     *        You can choose the appropriate audio scenario according to your application.<br>
     *        After selecting the audio scenario, SDK will automatically select the call/media volume, according to the client-side audio device and status.
     * @param scenario  Audio scenarios. See AudioScenarioType{@link #AudioScenarioType}.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note   
     *         + It is recommended to call this API before joining the room and calling other audio related interfaces. If this API is called afterwards, audio lag may be introduced.<br>
     *         + Call volume is more suitable for calls, meetings and other scenarios that demand information accuracy. Call volume will activate the system hardware signal processor, making the sound clearer. The volume cannot be reduced to 0. <br>
     *         + Media volume is more suitable for entertainment scenarios, which require musical expression. The volume can be reduced to 0.
     */
    virtual int setAudioScenario(AudioScenarioType scenario) = 0;
    /**
     * @locale zh
     * @hidden(macOS,Windows,Linux) internal use only
     * @valid since 3.55
     * @type api
     * @brief 设置音频场景类型。<br>
     *        选择音频场景后，SDK 会自动根据场景切换对应的音量模式（通话音量/媒体音量）和改场景下的最佳音频配置。和 `setAudioScenario` 不同的是，`audioScenario` 只修改了音量模式，不会修改音频相关的算法配置。<br>
     *        该接口不应与旧接口 `setAudioScenario` 混用。
     * @param scenario 音频场景类型，参看 AudioSceneType{@link #AudioSceneType}。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note  
     *        + 此接口在进房前后调用都有效。<br>
     *        + 通话音量更适合通话、会议等对信息准确度更高的场景。通话音量会激活系统硬件信号处理，使通话声音更清晰。同时，音量无法降低到 0。<br>
     *        + 媒体音量更适合娱乐场景，因其声音的表现力会更强。媒体音量下，最低音量可以为 0。
     */
    /**
     * @locale en
     * @hidden(macOS,Windows,Linux) internal use only
     * @valid since 3.55
     * @type api
     * @brief Sets the audio scenarios.<br>
     *        After selecting the audio scenario, SDK will automatically switch to the proper volume modes (the call/media volume) according to the scenarios and the best audio configurations under such scenarios. This API is different with `setAudioScenario` in that `audioScenario` will only change the volume mode and will not change the algorithm related to audio. <br>
     *        This API should not be used at the same time with the old one. 
     * @param scenario  Audio scenarios. See AudioSceneType{@link #AudioSceneType}.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note   
     *         + You can use this API both before and after joining the room.<br>
     *         + Call volume is more suitable for calls, meetings and other scenarios that demand information accuracy. Call volume will activate the system hardware signal processor, making the sound clearer. The volume cannot be reduced to 0. <br>
     *         + Media volume is more suitable for entertainment scenarios, which require musical expression. The volume can be reduced to 0.
     */
    virtual int setAudioScene(AudioSceneType scene) = 0;

    /**
     * @locale zh
     * @hidden(Linux)
     * @type api
     * @region 美声特效管理
     * @brief 设置变声特效类型
     * @param voice_changer 变声特效类型，参看 VoiceChangerType{@link #VoiceChangerType}。
     * @return 方法调用结果： <br>
     *        + 0：成功；<br>
     *        + !0：失败。
     * @note  
     *        + 在进房前后都可设置。  <br>
     *        + 对 RTC SDK 内部采集的音频和自定义采集的音频都生效。 <br>
     *        + 只对单声道音频生效。<br>
     *        + 与 setVoiceReverbType{@link #setVoiceReverbType} 互斥，后设置的特效会覆盖先设置的特效。<br>
     *        + 在 Windows 端使用此功能前，必须额外接入 [音频技术](https://www.volcengine.com/docs/6489/71986)。请联系技术支持了解详情。
     */
    /**
     * @locale en
     * @hidden(Linux)
     * @type api
     * @region Bel Sound Effect Management
     * @brief Set the sound change effect type
     * @param voice_changer The sound change effect type. See VoiceChangerType{@link #VoiceChangerType}.
     * @return API call result: <br>
     *        + 0: Success <br>
     *        + !0: Failure
     * @note   
     *         + You can call it before and after entering the room. <br>
     *         + Effective for both internal and external audio source. <br>
     *         + Only valid for mono-channel audio. <br>
     *         + Mutually exclusive with setVoiceReverbType{@link #setVoiceReverbType}, and the effects set later will override the effects set first.<br>
     *         + Before using the feature, you must implement [Audio SDK](https://go.byteplus.com/audio-sdk). Please contact the technical supporters.
     */
    virtual int setVoiceChangerType(VoiceChangerType voice_changer) = 0;

    /**
     * @locale zh
     * @hidden(Linux)
     * @type api
     * @region 美声特效管理
     * @brief 设置混响特效类型
     * @param voice_reverb 混响特效类型，参看 VoiceReverbType{@link #VoiceReverbType}。
     * @return 方法调用结果： <br>
     *        + 0：成功；<br>
     *        + !0：失败。
     * @note  
     *        + 在进房前后都可设置。  <br>
     *        + 对 RTC SDK 内部采集的音频和自定义采集的音频都生效。 <br>
     *        + 只对单声道音频生效。<br>
     *        + 只在包含美声特效能力的 SDK 中有效。<br>
     *        + 与 setVoiceChangerType{@link #setVoiceChangerType} 互斥，后设置的特效会覆盖先设置的特效。
     */
    /**
     * @locale en
     * @hidden(Linux)
     * @type api
     * @region Bel Sound Effect Management
     * @brief Set the reverb effect type
     * @param voice_reverb The reverb effect type. See VoiceReverbType{@link #VoiceReverbType}.
     * @return API call result: <br>
     *        + 0: Success <br>
     *        + !0: Failure
     * @note   
     *         + You can call it before and after entering the room. <br>
     *         + Effective for both internal and external audio source.  <br>
     *         + Only valid for mono-channel audio.  <br>
     *         + Mutually exclusive with setVoiceChangerType{@link #setVoiceChangerType}, and the effects set later will override the effects set first.
     */
    virtual int setVoiceReverbType(VoiceReverbType voice_reverb) = 0;
    /**
     * @locale zh
     * @hidden(Linux)
     * @type api
     * @brief 设置本地采集语音的均衡效果。包含内部采集和外部采集，但不包含混音音频文件。
     * @param config 语音均衡效果，参看 VoiceEqualizationConfig{@link #VoiceEqualizationConfig}
     * @return  
     *        + 0： 成功。  <br>
     *        + < 0： 失败。
     * @note 根据奈奎斯特采样率，音频采样率必须大于等于设置的中心频率的两倍，否则，设置不生效。
     */
    /**
     * @locale en
     * @hidden(Linux)
     * @type api
     * @brief Set the equalization effect for the local captured audio. The audio includes both internal captured audio and external captured voice, but not the mixing audio file.
     * @param config See VoiceEqualizationConfig{@link #VoiceEqualizationConfig}.
     * @return   
     *         + 0: Success. <br>
     *         + < 0: Failure.
     * @note According to the Nyquist acquisition rate, the audio acquisition rate must be greater than twice the set center frequency. Otherwise, the setting will not be effective.
     */
    virtual int setLocalVoiceEqualization(VoiceEqualizationConfig config) = 0;
    /**
     * @locale zh
     * @type api
     * @hidden(Linux)
     * @brief 设置本地采集音频的混响效果。包含内部采集和外部采集，但不包含混音音频文件。
     * @param param 混响效果，参看 VoiceReverbConfig{@link #VoiceReverbConfig}
     * @return  
     *        + 0： 成功。  <br>
     *        + < 0： 失败。
     * @note 调用 enableLocalVoiceReverb{@link #IRTCVideo#enableLocalVoiceReverb} 开启混响效果。
     */
    /**
     * @locale en
     * @type api
     * @hidden(Linux)
     * @brief Set the reverb effect for the local captured audio. The audio includes both internal captured audio and external captured voice, but not the mixing audio file.
     * @param param See VoiceReverbConfig{@link #VoiceReverbConfig}.
     * @return   
     *         + 0: Success. <br>
     *         + < 0: Failure.
     * @note Call enableLocalVoiceReverb{@link #IRTCVideo#enableLocalVoiceReverb} to enable the reverb effect.
     */
    virtual int setLocalVoiceReverbParam(VoiceReverbConfig param) = 0;
    /**
     * @locale zh
     * @type api
     * @hidden(Linux)
     * @brief 开启本地音效混响效果
     * @param enable 是否开启
     * @return  
     *        + 0： 成功。  <br>
     *        + < 0： 失败。
     * @note 调用 setLocalVoiceReverbParam{@link #IRTCVideo#setLocalVoiceReverbParam} 设置混响效果。
     */
    /**
     * @locale en
     * @type api
     * @hidden(Linux)
     * @brief Enable the reverb effect for the local captured voice.
     * @param enable
     * @return   
     *         + 0: Success. <br>
     *         + < 0: Failure.
     * @note Call setLocalVoiceReverbParam{@link #IRTCVideo#setLocalVoiceReverbParam} to set the reverb effect.
     */
    virtual int enableLocalVoiceReverb(bool enable) = 0;

    /**
     * @locale zh
     * @type api
     * @region 音频管理
     * @brief 设置音质档位。<br>
     *        当所选的 RoomProfileType{@link #RoomProfileType} 中的音频参数无法满足你的场景需求时，调用本接口切换的音质档位。
     * @param audio_profile 音质档位，参看 AudioProfileType{@link #AudioProfileType}
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note  
     *        + 该方法在进房前后均可调用；  <br>
     *        + 支持通话过程中动态切换音质档位。
     */
    /**
     * @locale en
     * @type api
     * @region audio management
     * @brief Sets the sound quality. Call this API to change the sound quality if the audio settings in the current RoomProfileType{@link #RoomProfileType} can not meet your requirements.
     * @param audio_profile Sound quality. See AudioProfileType{@link #AudioProfileType}
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note   
     *         + You can call this API before and after entering the room. <br>
     *         + Support dynamic switching of sound quality during a call.
     */
    virtual int setAudioProfile(AudioProfileType audio_profile) = 0;

    /**
     * @locale zh
     * @type api
     * @region 音频管理
     * @brief 支持根据业务场景，设置通话中的音频降噪模式。
     * @param ans_mode 降噪模式。具体参见 AnsMode{@link #AnsMode}。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note  
     *        + 该接口进房前后均可调用，可重复调用，仅最后一次调用生效。<br>
     *        + 降噪算法包含传统降噪和 AI 降噪。传统降噪主要是抑制平稳噪声，比如空调声、风扇声等。而 AI 降噪主要是抑制非平稳噪声，比如键盘敲击声、桌椅碰撞声等。<br>
     *        + 在 V3.57.1 之前的版本，只有以下 RoomProfileType{@link #RoomProfileType} 场景时，调用本接口可以开启 AI 降噪。其余场景的 AI 降噪不会生效。<br>
     *                 -  游戏语音模式：kRoomProfileTypeGame<br>
     *                 -  高音质游戏模式：kRoomProfileTypeGameHD<br>
     *                 -  云游戏模式：kRoomProfileTypeCloudGame<br>
     *                 -  1 vs 1 音视频通话：kRoomProfileTypeChat<br>
     *                 -  多端同步播放音视频：kRoomProfileTypeLwTogether<br>
     *                 -  云端会议中的个人设备：kRoomProfileTypeMeeting<br>
     *                 -  课堂互动模式：kRoomProfileTypeClassroom<br>
     *                 -  云端会议中的会议室终端：kRoomProfileTypeMeetingRoom
     */
    /**
     * @locale en
     * @type api
     * @region audio management
     * @brief Set the Active Noise Cancellation(ANC) mode during audio and video communications.
     * @param ans_mode ANC modes. See AnsMode{@link #AnsMode}.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note  You can call this API before or after entering a room. When you repeatedly call it, only the last call takes effect.
     * @note  When you repeatedly call this API, only the last call takes effect.
     */
    virtual int setAnsMode(AnsMode ans_mode) = 0;

    /**
     * @locale zh
     * @type api
     * @valid since 3.51
     * @region 音频设备管理
     * @brief 打开/关闭 AGC(Automatic Gain Control) 自动增益控制功能。<br>
     *        开启该功能后，SDK 会自动调节麦克风的采集音量，确保音量稳定。
     * @param enable 是否打开 AGC 功能: <br>
     *        + true: 打开 AGC 功能。<br>
     *        + false: 关闭 AGC 功能。
     * @return  
     *        +  0: 调用成功。<br>
     *        + -1: 调用失败。
     * @note  
     *         该方法在进房前后均可调用。如果你需要在进房前使用 AGC 功能，请联系技术支持获得私有参数，传入对应 RoomProfileType{@link #RoomProfileType} 。 <br>
     *         要想在进房后开启 AGC 功能，你需要把 RoomProfileType{@link #RoomProfileType} 设置为 `kRoomProfileTypeMeeting` 、`kRoomProfileTypeMeetingRoom` 或 `kRoomProfileTypeClassroom` 。 <br>
     *         AGC 功能生效后，不建议再调用 setAudioCaptureDeviceVolume{@link #IAudioDeviceManager#setAudioCaptureDeviceVolume} 来调节设备麦克风的采集音量。
     */
    /**
     * @locale en
     * @type api
     * @valid since 3.51
     * @region Audio device Management
     * @brief  Turns on/ off AGC(Analog Automatic Gain Control). <br>
     *         After AGC is enabled, SDK can automatically adjust microphone pickup volume to keep the output volume at a steady level.
     * @param enable whether to turn on AGC. <br>
     *        + true: AGC is turned on.  <br>
     *        + false: AGC is turned off. 
     * @return  
     *         + 0: Success. <br>
     *         + -1: Failure.
     * @note  
     *         You can call this method before and after joining the room. To turn on AGC before joining the room, you need to contact the technical support to get a private parameter to set RoomProfileType{@link #RoomProfileType}. <br>
     *         To enable AGC after joining the room, you must set RoomProfileType{@link #RoomProfileType} to `kRoomProfileTypeMeeting`,`kRoomProfileTypeMeetingRoom` or `kRoomProfileTypeClassroom` .  <br>
     *         It is not recommended to call setAudioCaptureDeviceVolume{@link #IAudioDeviceManager#setAudioCaptureDeviceVolume} to adjust microphone pickup volume with AGC on.
     */
    virtual int enableAGC(bool enable) = 0;

    /**
     * @locale zh
     * @hidden(Linux)
     * @type api
     * @region 自定义音频采集渲染
     * @brief 切换音频采集方式
     * @param type 音频数据源，详见 AudioSourceType{@link #AudioSourceType}。<br>
     *             默认使用内部音频采集。音频采集和渲染方式无需对应。
     * @return  方法调用结果：  <br>
     *        + >0: 切换成功。<br>
     *        + -1：切换失败。
     * @note  
     *      + 进房前后调用此方法均有效。<br>
     *      + 如果你调用此方法由内部采集切换至自定义采集，SDK 会自动关闭内部采集。然后，调用 pushExternalAudioFrame{@link #IRTCVideo#pushExternalAudioFrame} 推送自定义采集的音频数据到 RTC SDK 用于传输。 <br>
     *      + 如果你调用此方法由自定义采集切换至内部采集，你必须再调用 startAudioCapture{@link #IRTCVideo#startAudioCapture} 手动开启内部采集。 
     */
    /**
     * @locale en
     * @hidden(Linux)
     * @type api
     * @region Custom Audio Capture and Rendering
     * @brief Switch the audio capture type.
     * @param type Audio input source type. See AudioSourceType{@link #AudioSourceType} <br>
     *            Use internal audio capture by default. The audio capture type and the audio render type may be different from each other.
     * @return   Method call result:   <br>
     *         + >0: Success. <br>
     *         + -1: Failure.
     * @note   
     *       + You can call this API before or after joining the room.<br>
     *       + If you call this API to switch from internal audio capture to custom capture, the internal audio capture is automatically disabled. You must call pushExternalAudioFrame{@link #IRTCVideo#pushExternalAudioFrame} to push custom captured audio data to RTC SDK for transmission. <br>
     *       + If you call this API to switch from custom capture to internal capture, you must then call startAudioCapture{@link #IRTCVideo#startAudioCapture} to enable internal capture. 
     */
    virtual int setAudioSourceType (AudioSourceType type) = 0;
    /**
     * @locale zh
     * @hidden(Linux)
     * @type api
     * @region 自定义音频采集渲染
     * @brief  切换音频渲染方式
     * @param type 音频输出类型，详见 AudioRenderType{@link #AudioRenderType} <br>
     *             默认使用内部音频渲染。音频采集和渲染方式无需对应。
     * @return  方法调用结果：  <br>
     *        + >0: 切换成功。<br>
     *        + -1：切换失败。
     * @note  
     *      + 进房前后调用此方法均有效。<br>
     *      + 如果你调用此方法切换至自定义渲染，调用 pullExternalAudioFrame{@link #IRTCVideo#pullExternalAudioFrame} 获取音频数据。 
     */
    /**
     * @locale en
     * @hidden(Linux)
     * @type api
     * @region Custom Audio Capture and Rendering
     * @brief Switch the audio render type.
     * @param type Audio output source type. See AudioRenderType{@link #AudioRenderType}. <br>
     *             Use internal audio render by default. The audio capture type and the audio render type may be different from each other.
     * @return  Method call result:   <br>
     *         + >0: Success. <br>
     *         + -1: Failure.
     * @note   
     *       + You can call this API before or after joining the room. <br>
     *       + After calling this API to enable custom audio rendering, call pullExternalAudioFrame{@link #IRTCVideo#pullExternalAudioFrame} for audio data.
     */
    virtual int setAudioRenderType (AudioRenderType type) = 0;
    /**
     * @locale zh
     * @hidden(Linux)
     * @type api
     * @region 自定义音频采集渲染
     * @brief 推送自定义采集的音频数据到 RTC SDK。
     * @param audio_frame 10 ms 对应的音频数据。详见 IAudioFrame{@link #IAudioFrame}。<br>
     *        + 音频采样格式必须为 S16。音频缓冲区内的数据格式必须为 PCM，其容量大小应该为 audioFrame.samples × audioFrame.channel × 2。<br>
     *        + 必须指定具体的采样率和声道数，不支持设置为自动。
     * @return  方法调用结果  <br>
     *        + 0：方法调用成功  <br>
     *        + < 0：方法调用失败  
     * @note  
     *       + 推送自定义采集的音频数据前，必须先调用 setAudioSourceType{@link #IRTCVideo#setAudioSourceType} 开启自定义采集。<br>
     *       + 你必须每 10 ms 推送一次数据。
     */
    /**
     * @locale en
     * @hidden(Linux)
     * @type api
     * @region Custom Audio Capture and Rendering
     * @brief Push custom captured audio data to the RTC SDK.
     * @param audio_frame The audio data of 10 ms. See IAudioFrame{@link #IAudioFrame}。
     * @return 
     *         + 0: Success <br>
     *         + < 0: Failure 
     * @note   
     *        + Before calling this API, you must call setAudioSourceType{@link #IRTCVideo#setAudioSourceType} to enable custom audio capture. <br>
     *        + You must push custom captured audio data every 10 ms. 
     */
    virtual int pushExternalAudioFrame(IAudioFrame* audio_frame) = 0;
    /**
     * @locale zh
     * @hidden(Linux)
     * @region 自定义音频采集渲染
     * @brief 拉取下行音频数据用于自定义音频渲染。<br>
     *        调用该方法后，SDK 会主动拉取待播放的音频数据，包括远端已解码和混音后的音频数据，用于外部播放。
     * @param [out] audio_frame 获取的 10 ms 内的音频数据。详见 IAudioFrame{@link #IAudioFrame}。
     * @return 方法调用结果：<br>
     *        + 0：成功；<br>
     *        + <0：失败。具体失败原因参看 ReturnStatus{@link #ReturnStatus}。
     * @note  
     *       + 获取音频数据用于自定义渲染前，必须先调用 setAudioRenderType{@link #IRTCVideo#setAudioRenderType} 开启自定义渲染。<br>
     *       + 由于 RTC SDK 的帧长为 10 毫秒，你应当每隔 10 毫秒拉取一次音频数据。确保音频采样点数（sample）x 拉取频率等于 audio_frame 的采样率 （sampleRate）。如设置采样率为 48000 时，每 10 毫秒调用本接口拉取数据，每次应拉取 480 个采样点。  <br>
     *       + 该函数运行在用户调用线程内，是一个同步函数。  
     */
    /**
     * @locale en
     * @hidden(Linux)
     * @region  custom audio acquisition rendering
     * @brief  Pull remote audio data. You can use the data for audio processing or custom rendering.
     * @param [out] audio_frame The obtained audio data of 10 ms. See IAudioFrame{@link #IAudioFrame}。
     * @return API call result:<br>
     *        + 0: Success.<br>
     *        + <0: Failure. See ReturnStatus{@link #ReturnStatus} for specific reasons.
     * @note   
     *        + Before pulling the audio data, call setAudioRenderType{@link #IRTCVideo#setAudioRenderType} to enable custom rendering. <br>
     *        + You should pull audio data every 10 milliseconds since the duration of a RTC SDK audio frame is 10 milliseconds. Samples x call frequency = audio_frame's sample rate. Assume that the sampling rate is set to 48000, call this API every 10 ms, so that 480 sampling points should be pulled each time. <br>
     *        + This function runs in the user calling thread and is a synchronous function. 
     */
    virtual int pullExternalAudioFrame(IAudioFrame* audio_frame) = 0;

    /**
     * @locale zh
     * @type api
     * @region 视频管理
     * @brief 立即开启内部视频采集。默认为关闭状态。  <br>
     *        内部视频采集指：使用 RTC SDK 内置视频采集模块，进行采集。<br>
     *        调用该方法后，本地用户会收到 onVideoDeviceStateChanged{@link #IRTCVideoEventHandler#onVideoDeviceStateChanged} 的回调。  <br>
     *        本地用户在非隐身状态下调用该方法后，房间中的其他用户会收到 onUserStartVideoCapture{@link #IRTCVideoEventHandler#onUserStartVideoCapture} 的回调。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note  
     *       + 调用 stopVideoCapture{@link #IRTCVideo#stopVideoCapture} 可以停止内部视频采集。否则，只有当销毁引擎实例时，内部视频采集才会停止。  <br>
     *       + 创建引擎后，无论是否发布视频数据，你都可以调用该方法开启内部视频采集。只有当（内部或外部）视频采集开始以后视频流才会发布。  <br>
     *       + 如果需要从自定义视频采集切换为内部视频采集，你必须先关闭自定义采集，再调用此方法手动开启内部采集。
     */
    /**
     * @locale en
     * @type api
     * @region Video management
     * @brief Enable internal video capture immediately. The default is off.   <br>
     *        Internal video capture refers to: use the RTC SDK built-in video capture module to capture.<br>
     *        The local client will be informed via onVideoDeviceStateChanged{@link #IRTCVideoEventHandler#onVideoDeviceStateChanged} after starting video capture by calling this API.<br>
     *        The remote clients in the room will be informed of the state change via onUserStartVideoCapture{@link #IRTCVideoEventHandler#onUserStartVideoCapture} after the visible client starts video capture by calling this API.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note   
     *        + Call stopVideoCapture{@link #IRTCVideo#stopVideoCapture} to stop the internal video capture. Otherwise, the internal video capture will sustain until you destroy the engine instance.<br>
     *        + Once you create the engine instance, you can start internal video capture regardless of the video publishing state. The video stream will start publishing only after the video capture starts. <br>
     *        + To switch from custom to internal video capture, stop publishing before disabling the custom video capture module and then call this API to enable the internal video capture.
     */
    virtual int startVideoCapture() = 0;

    /**
     * @locale zh
     * @type api
     * @region 视频管理
     * @brief 立即关闭内部视频采集。默认为关闭状态。  <br>
     *        内部视频采集指：使用 RTC SDK 内置视频采集模块，进行采集。<br>
     *        调用该方法后，本地用户会收到 onVideoDeviceStateChanged{@link #IRTCVideoEventHandler#onVideoDeviceStateChanged} 的回调。  <br>
     *        非隐身用户进房后调用该方法，房间中的其他用户会收到 onUserStopVideoCapture{@link #IRTCVideoEventHandler#onUserStopVideoCapture} 的回调。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note  
     *       + 调用 startVideoCapture{@link #IRTCVideo#startVideoCapture} 可以开启内部视频采集。  <br>
     *       + 如果不调用本方法停止内部视频采集，则只有当销毁引擎实例时，内部视频采集才会停止。
     */
    /**
     * @locale en
     * @type api
     * @region Video management
     * @brief Disable internal video capture immediately. The default is off.   <br>
     *        Internal video capture refers to: use the RTC SDK built-in video capture module to capture.<br>
     *        The local client will be informed via onVideoDeviceStateChanged{@link #IRTCVideoEventHandler#onVideoDeviceStateChanged} after stopping video capture by calling this API.<br>
     *        The remote clients in the room will be informed of the state change via onUserStopVideoCapture{@link #IRTCVideoEventHandler#onUserStopVideoCapture} after the visible client stops video capture by calling this API.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note   
     *        + Call startVideoCapture{@link #IRTCVideo#startVideoCapture} to enable the internal video capture. <br>
     *        + Without calling this API the internal video capture will sustain until you destroy the engine instance.
     */
    virtual int stopVideoCapture() = 0;

   /**
    * @locale zh
    * @type api
    * @region 视频管理
    * @brief 设置 RTC SDK 内部采集时的视频采集参数。<br>
    *        如果你的项目使用了 SDK 内部采集模块，可以通过本接口指定视频采集参数，包括模式、分辨率、帧率。
    * @param video_capture_config 视频采集参数。参看: VideoCaptureConfig{@link #VideoCaptureConfig}。
    * @return  
    *        + 0: 成功；  <br>
    *        + < 0: 失败；  
    * @note  
    * + 本接口在引擎创建后可调用，调用后立即生效。建议在调用 startVideoCapture{@link #IRTCVideo#startVideoCapture} 前调用本接口。<br>
    * + 建议同一设备上的不同引擎使用相同的视频采集参数。<br>
    * + 如果调用本接口前使用内部模块开始视频采集，采集参数默认为 Auto 模式。
    */
   /**
    * @locale en
    * @type api
    * @region  Video Management
    * @brief  Set the video capture parameters for internal capture of the RTC SDK. <br>
    *         If your project uses the SDK internal capture module, you can specify the video capture parameters including preference, resolution and frame rate through this interface.
    * @param video_capture_config  Video capture parameters. See: VideoCaptureConfig{@link #VideoCaptureConfig}.
    * @return   
    *         + 0: Success; <br>
    *         + < 0: Failure; 
    * @note   
    *  + This interface can be called after the engine is created and takes effect immediately after being called. It is recommended to call this interface before calling startVideoCapture{@link #IRTCVideo#startVideoCapture}.<br>
    *  + It is recommended that different Engines on the same device use the same video capture parameters.<br>
    *  + If you used the internal module to start video capture before calling this interface, the capture parameters default to Auto.
    */
    virtual int setVideoCaptureConfig(const VideoCaptureConfig& video_capture_config) = 0;

    /**
     * @locale zh
     * @type api
     * @region 视频管理
     * @brief 设置本端采集的视频帧的旋转角度。<br>
     *        当摄像头倒置或者倾斜安装时，可调用本接口进行调整。
     * @param rotation 相机朝向角度，默认为 `VIDEO_ROTATION_0(0)`，无旋转角度。详见 VideoRotation{@link #VideoRotation}。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note 
     *        + 调用本接口也将对自定义采集视频画面生效，在原有的旋转角度基础上叠加本次设置。<br>
     *        + 对于 Windows SDK，视频贴纸特效或通过 enableVirtualBackground{@link #IVideoEffect#enableVirtualBackground} 增加的虚拟背景，也会跟随本接口的设置进行旋转。<br>
     *        + 本地渲染视频和发送到远端的视频都会相应旋转，但不会应用到单流转推中。如果希望在单流转推的视频中应用旋转，调用 setVideoOrientation{@link #IRTCVideo#setVideoOrientation}。
     */
    /**
     * @locale en
     * @type api
     * @brief Set the rotation of the video images captured from the local device.<br>
     *        Call this API to rotate the videos when the camera is fixed upside down or tilted.
     * @param rotation It defaults to `VIDEO_ROTATION_0(0)`, which means not to rotate. Refer to VideoRotation{@link #VideoRotation}.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note 
     *        + For the videos captured by the internal module, the rotation will be combined with that set by calling setVideoRotationMode{@link #IRTCVideo#setVideoRotationMode}.<br>
     *        + This API affects the external-sourced videos. The final rotation would be the original rotation angles adding up with the rotation set by calling this API.<br>
     *        + For the Windows SDK, the elements added during the video pre-processing stage, such as video sticker and background applied using enableVirtualBackground{@link #IVideoEffect#enableVirtualBackground} will also be rotated by this API.<br>
     *        + The rotation would be applied to both locally rendered video s and those sent out. However, if you need to rotate a video which is intended for pushing to CDN individually, use setVideoOrientation{@link #IRTCVideo#setVideoOrientation}.
     */
    virtual int setVideoCaptureRotation(VideoRotation rotation) = 0;

    /**
     * @locale zh
     * @type api
     * @region 视频管理
     * @brief 该方法设置视频流发布端是否开启发布多路编码参数不同的视频流的模式。
     * @param enabled 是否开启推送多路视频流模式： <br>
     *        + true：开启 <br>
     *        + false：关闭（默认）
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note 
     *        + 你应在进房前或进房后但未发布流时，调用此方法。  <br>
     *        + 开启推送多路流后，不能动态关闭，也不能更新多路流的路数和编码参数。  <br>
     *        + 开启推送多路视频流模式后，你可以在发布流前调用 [setVideoEncoderConfig](#IRTCVideo-setvideoencoderconfig-1) 为多路视频流分别设置编码参数。  <br>
     *        + 该功能关闭时，或该功能开启但未设置多路流参数时，默认只发一路视频流，该流的编码参数为：分辨率 640px × 360px，帧率 15fps。
     */
    /**
     * @locale en
     * @type api
     * @region Video Management
     * @brief Enables/Disables the mode of publishing multiple video streams with different encoding configuration.
     * @param enabled Whether to enable the mode of publishing multiple video streams:  <br>
     *        + true: Yes  <br>
     *        + false: No(Default setting)
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note 
     *        + You can call this API  <br>
     *            - Before entering the room, or  <br>
     *            - After entering the room but before publishing streams.  <br>
     *        + When the simulcast mode is turned on, it cannot be turned off dynamically, nor can the parameters for video encoding be updated.  <br>
     *        + After setting this API to "True", you can call [setVideoEncoderConfig](#IRTCVideo-setvideoencoderconfig-1) to set encoding configuration for each stream before you publish stream.  <br>
     *        + If this function is off, or if this function is on but you don't set the configuration of any stream, only one stream will be sent with a resolution of 640px × 360px and a frame rate of 15fps.
     */
    virtual int enableSimulcastMode(bool enabled) = 0;

    /**
     * @locale zh
     * @type api
     * @region 视频管理
     * @brief <span id="IRTCVideo-setvideoencoderconfig-1"></span> 视频发布端设置期望发布的最大分辨率视频流参数，包括分辨率、帧率、码率、网络不佳时的回退策略等。  <br>
     *        该接口支持设置一路视频流参数，设置多路参数请使用重载 API：[setVideoEncoderConfig](#IRTCVideo-setvideoencoderconfig-2)。
     * @param max_solution 期望发布的最大分辨率视频流参数。参看 VideoEncoderConfig{@link #VideoEncoderConfig}。
     * @return 方法调用结果： <br>
     *        + 0：成功  <br>
     *        + !0：失败  
     * @note  
     *        + 你可以同时使用 enableSimulcastMode{@link #IRTCVideo#enableSimulcastMode} 方法来发布多路分辨率不同的流。具体而言，若期望发布多路不同分辨率的流，你需要在发布流之前调用本方法以及 enableSimulcastMode{@link #IRTCVideo#enableSimulcastMode} 方法开启多路流模式，SDK 会根据订阅端的设置智能调整发布的流数（最多发布 4 条）以及各路流的参数。其中，调用本方法设置的分辨率为各路流中的最大分辨率。具体规则参看[推送多路流](https://www.volcengine.com/docs/6348/70139)文档。<br>
     *        + 调用该方法前，SDK 默认仅发布一条分辨率为 640px × 360px，帧率为 15fps 的视频流。  <br>
     *        + 使用自定义采集时，必须调用该方法设置编码参数，以保证远端收到画面的完整性。<br>
     *        + 该方法适用于摄像头采集的视频流，设置屏幕共享视频流参数参看 setScreenVideoEncoderConfig{@link #IRTCVideo#setScreenVideoEncoderConfig}（Linux 不适用）。
     */
    /**
     * {en}
     * @type api
     * @region Video Management
     * @brief <span id="IRTCVideo-setvideoencoderconfig-1"></span> Video publisher call this API to set the parameters of the maximum resolution video stream that is expected to be published, including resolution, frame rate, bitrate, and fallback strategy in poor network conditions.<br>
     *        You can only set configuration for one stream with this API. If you want to set configuration for multiple streams, Call [setVideoEncoderConfig](#IRTCVideo-setvideoencoderconfig-2).
     * @param max_solution The maximum video encoding parameter. See VideoEncoderConfig{@link #VideoEncoderConfig}.
     * @return  API call result: <br>
     *        + 0: Success <br>
     *        + ! 0: Failure 
     * @note  
     *        + You can use enableSimulcastMode{@link #IRTCVideo#enableSimulcastMode} simultaneously to publish streams with different resolutions. Specifically, if you want to publish multiple streams with different resolutions, you need to call this method and enable the simulcast mode with enableSimulcastMode{@link #IRTCVideo#enableSimulcastMode} before publishing your streams. The SDK will intelligently adjust the number of streams to be published (up to 4) and their parameters based on the settings of the subscribing end. The resolution set by calling this method will be the maximum resolution among the streams. For specific rules, please refer to [Simulcasting](https://docs.byteplus.com/en/byteplus-rtc/docs/70139).<br>
     *        + Without calling this API, SDK will only publish one stream for you with a resolution of 640px × 360px and a frame rate of 15fps.  <br>
     *        + In custom capturing scenario, you must call this API to set encoding configurations to ensure the integrity of the picture received by the remote users.<br>
     *        + This API is applicable to the video stream captured by the camera, see setScreenVideoEncoderConfig{@link #IRTCVideo#setScreenVideoEncoderConfig} for setting parameters for screen sharing video stream.
     */
    virtual int setVideoEncoderConfig(const VideoEncoderConfig& max_solution) = 0;

    /**
     * @locale zh
     * @hidden for internal use only on Windows and Android
     * @type api
     * @region 视频管理
     * @brief <span id="RTCVideo-setvideoencoderconfig-3"></span> 发布端设置全景视频，包括分辨率、高清视野和低清背景分辨率、Tile 大小，以及其他常规编码参数。
     * @param encoder_config 期望发布的最大分辨率视频流参数。参看 VideoEncoderConfig{@link #VideoEncoderConfig}。<br>
     *                      支持 8K 和 4K 两种分辨率的全景视频。
     * @param parameters 全景视频的编码参数，JSON 字符串格式<br>
     *                  + 8K: HD: 7680x3840, LD: 2560x1280, Tile: 640x640<br>
     *                  + 4K: HD: 3840x1920, LD: 1280x640, Tile: 320x320<br>
     * {<br>
     *  "rtc.fov_config":{<br>
     *      "mode":0,   //模式，只支持 `0` 等距柱状投影（Equirectangular Projection，ERP）模式<br>
     *      "hd_width":3840,    //高清视野的宽<br>
     *      "hd_height":1920,   //高清视野的高<br>
     *      "ld_width":1280,    //低清背景的宽<br>
     *      "ld_height":640,    //低清背景的高<br>
     *      "tile_width":320,   //Tile 的宽，取值建议能被全景视频宽、高清视野宽、低清背景宽整除<br>
     *      "tile_height":320,  //Tile 的高，取值建议能被全景视频高、高清视野高、低清背景高整除<br>
     *      "framerate":30, //帧率<br>
     *      "max_kbps":40000} //期望编码码率<br>
     *}
     * @return 方法调用结果： <br>
     *        + 0：成功  <br>
     *        + !0：失败  
     * @note  
     *        + 发布全景视频前，绑定自定义采集器，必须调用该方法设置编码参数。支持的视频格式包括 YUV 或者 Texture 纹理。<br>
     *        + 通过 onFrame{@link #IVideoSink#onFrame} ,接收端获取到视频帧和解码需要的信息，传给自定义渲染器进行渲染。
     */
    /**
     * @locale en
     * @hidden for internal use only on Windows and Android
     * @type api
     * @brief <span id="RTCVideo-setvideoencoderconfig-3"></span> Video publishers call this API to set the parameters of the panoramic video, including resolution of the Fov, HD field, LD background, sizes of the Tiles, and the other regular configurations.<br>
     *        You can only set configuration for one stream with this API. If you want to set configuration for multiple streams, Call [setVideoEncoderConfig](#IRTCVideo-setvideoencoderconfig-2).
     * @param encoder_config The maximum video encoding parameter. Refer to VideoEncoderConfig{@link #VideoEncoderConfig} for more details..  <br>
     *                      Panoramic video of 8K or 4K is supported.
     * @param parameters JSON string of encoder configuration of the panoramic video <br>
     *                  + 8K: HD: 7680x3840, LD: 2560x1280, Tile: 640x640<br>
     *                  + 4K: HD: 3840x1920, LD: 1280x640, Tile: 320x320<br>
     * {<br>
     *  "rtc.fov_config":{<br>
     *      "mode":0,   //Only `0` is available for now. `0` for Equirectangular Projection(ERP).<br>
     *      "hd_width":3840,    //Width of the HD field.<br>
     *      "hd_height":1920,   //Height of the HD field<br>
     *      "ld_width":1280,    //Width of the background<br>
     *      "ld_height":640,    //Height of the background<br>
     *      "tile_width":320,   //Width of a tile<br>
     *      "tile_height":320,  //Height of a tile<br>
     *      "framerate":30, // Frame rate in fps<br>
     *      "max_kbps":40000} // Expected encoding bitrate in kbps<br>
     *}
     * @return  API call result: <br>
     *        + 0: Success <br>
     *        + ! 0: Failure 
     * @note  
     *        + Call this API to set encoding configurations for the panoramic video and designate an external video source. The format of the video can be YUV or Texture.<br>
     *        + Receivers get the video frames and decoding configurations via onFrame{@link #IVideoSink#onFrame} and pass them to the external renderer.
     */
    virtual int setVideoEncoderConfig(const VideoEncoderConfig& encoder_config, const char* parameters) = 0;

    /**
     * @locale zh
     * @type api
     * @region 视频管理
     * @brief <span id="IRTCVideo-setvideoencoderconfig-2"></span> 视频发布端设置推送多路流时各路流的参数，包括分辨率、帧率、码率、网络不佳时的回退策略等。
     * @param channel_solutions 要推送的多路视频流的参数需注意，所设置的分辨率是各路流的最大分辨率。参看 VideoEncoderConfig{@link #VideoEncoderConfig}。
     * @param solution_num 视频参数数组长度，最多支持设置 3 路参数，超过 3 路时默认取前 3 路的值。当设置了多路参数时，分辨率和帧率必须是从大到小排列。需注意，所设置的分辨率是各路流的最大分辨率。
     * @return 方法调用结果： <br>
     *        + 0：成功  <br>
     *        + !0：失败  
     * @note  
     *        + 该方法设置的多路参数是否均生效，取决于是否同时调用了 enableSimulcastMode{@link #IRTCVideo#enableSimulcastMode} 开启发布多路参数不同的视频流模式。若未开启推送多路流模式，但调用本方法设置了多个分辨率，SDK 则默认发布设置的第一条流，多个分辨率的设置会在开启推送多路流模式之后生效。  <br>
     *        + 若期望推送多路不同分辨率的流，你需要在发布流之前调用本方法以及 enableSimulcastMode{@link #IRTCVideo#enableSimulcastMode} 方法。<br>
     *        + 开启推送多路流后，不能动态关闭，也不能更新多路流的路数和编码参数。  <br>
     *        + 调用该方法设置多路视频流参数前，SDK 默认仅发布一条分辨率为 640px × 360px，帧率为 15fps 的视频流。  <br>
     *        + 调用该方法设置分辨率不同的多条流后，SDK 会根据订阅端设置的期望订阅参数自动匹配发送的流，具体规则参看[推送多路流](https://www.volcengine.com/docs/6348/70139)文档。  <br>
     *        + 该方法适用于摄像头采集的视频流，设置屏幕共享视频流参数参看 setScreenVideoEncoderConfig{@link #IRTCVideo#setScreenVideoEncoderConfig}（Linux 不适用）。
     */
    /**
     * @locale en
     * @type api
     * @region Video Management
     * @brief <span id="IRTCVideo-setvideoencoderconfig-2"></span> Video publisher call this API to set the configurations of each stream published, including resolution, frame rate, bitrate, and fallback strategy in poor network conditions.
     * @param channel_solutions List of configurations for multiple streams. You can set parameters for up to 3 streams, SDK will always take the value of the first 3 streams when parameters for more streams are set.<br>
     *        The resolution you set is the maximum resolution of each stream, and must be arranged in descending order. The frame rates must be arranged in descending order. See VideoEncoderConfig{@link #VideoEncoderConfig}.
     * @param solution_num Numbers of streams
     * @return  API call result: <br>
     *        + 0: Success <br>
     *        + ! 0: Failure 
     * @note  
     *        + If you call this API after enabling the mode of publishing multiple streams with enableSimulcastMode{@link #IRTCVideo#enableSimulcastMode}, SDK will publish streams as you set, otherwise the SDK by default publishes the first stream that you have set. <br>
     *        + If you want to publish multiple streams with different resolutions, you need to call this method and enableSimulcastMode{@link #IRTCVideo#enableSimulcastMode}.<br>
     *        + When the simulcast mode is turned on, it cannot be turned off dynamically, nor can the parameters for video encoding be updated.  <br>
     *        + Without calling this API to set parameters for multiple video streams, the SDK only publishes one video stream with a resolution of 640px × 360px and a frame rate of 15fps.  <br>
     *        + After setting parameters for multiple video streams, SDK will automatically match the streams to be published based on the desired subscription parameters set by subscribers, see [Simulcasting](https://docs.byteplus.com/en/byteplus-rtc/docs/70139) for details.  <br>
     *        + This API is applicable to the video stream captured by the camera, see setScreenVideoEncoderConfig{@link #IRTCVideo#setScreenVideoEncoderConfig} for setting parameters for screen sharing video stream.
     */
    virtual int setVideoEncoderConfig(const VideoEncoderConfig* channel_solutions, int solution_num) = 0;

    /**
     * @locale zh
     * @type api
     * @region 屏幕共享
     * @brief 为发布的屏幕共享视频流设置期望的编码参数，包括分辨率、帧率、码率、网络不佳时的回退策略等。
     * @param screen_solution 屏幕共享视频流参数。参看 ScreenVideoEncoderConfig{@link #ScreenVideoEncoderConfig}。
     * @return  
     *         0：成功。  <br>
     *         !0：失败。
     * @note 建议在采集视频前设置编码参数。若采集前未设置编码参数，则使用默认编码参数: 分辨率 1920px × 1080px，帧率 15fps。
     */
    /**
     * @locale en
     * @type api
     * @region Screen Sharing
     * @brief  Set the configuration for shared-screen streams, including the resolution, frame rate, bitrate, and fallback strategies under challenging network conditions.
     * @param screen_solution The configuration for shared-screen streams. See ScreenVideoEncoderConfig{@link #ScreenVideoEncoderConfig}.
     * @return  
     *        + 0: Success. <br>
     *        + ! 0: Failure.
     * @note We recommend that you set the encoding configuration before video capture. Otherwise, the video will be captured based on the default configuration(1080p@15fps).
     */
    virtual int setScreenVideoEncoderConfig(const ScreenVideoEncoderConfig& screen_solution) = 0;

    /**
     * @locale zh
     * @deprecated since 3.36 and will be deleted in 3.51, use [setVideoEncoderConfig](#IRTCVideo-setvideoencoderconfig-2) instead.
     * @type api
     * @region 视频管理
     * @brief 设置推送多路流时的各路视频参数，包括分辨率、帧率、码率、缩放模式、网络不佳时的回退策略等。
     * @param index 视频流属性，参看 StreamIndex{@link #StreamIndex}。
     * @param solutions 要推送的多路视频流参数，参看 VideoSolution{@link #VideoSolution}。<br>
     *                       最大分辨率为 4096px × 4096px，超过或设置的分辨率无法编码时，会导致编码推流失败。
     * @param solution_num 视频参数数组长度。<br>
     *                          最多支持 4 路参数。当设置了多路参数时，分辨率必须是从大到小排列。 
     * @return  
     *        + 0：成功  <br>
     *        + !0：失败  
     * @note  
     *       + 该接口已废弃，请使用同名新接口代替；若仍需使用该旧接口，请注意无需先调用 `enableSimulcastMode` 开启推送多路流模式。<br>
     *       + 当使用内部采集时，视频采集的分辨率、帧率会根据最大的编码分辨率、帧率进行适配<br>
     *       + 默认的视频编码参数为：分辨率 640px × 360px，帧率 15fps。<br>
     *       + 变更编码分辨率后马上生效，可能会引发相机重启。<br>
     *       + 屏幕流只取视频参数数组的第一组数据。
     */
    /**
     * @locale en
     * @deprecated since 3.45 and will be deleted in 3.51, use [setVideoEncoderConfig](#IRTCVideo-setvideoencoderconfig-2) instead.
     * @type api
     * @region  Video management
     * @brief  Sets the video encoder configuration of each individual stream for simulcasting, including resolution, frame rate, bitrate, scale mode, fallback strategy under poor network conditions, etc.
     * @param index Stream type. See StreamIndex{@link #StreamIndex}.
     * @param solutions    Video parameters of each individual stream for simulcasting. See VideoSolution{@link #VideoSolution}.<br>
     *                           The maximum resolution is 4096px × 4096px. If the resolution exceeds the limit or the video cannot be encoded, the simulcasting will fail.
     * @param solution_num The length of `solutions`. <br>
     *                           The length of `solutions` is no more than 4. The resolutions must be in descending sort. 
     * @return   
     *         + 0: Success <br>
     *         +! 0: Failure 
     * @note   
     *        + When using the internal capture, the resolution and frame rate will be adapted to the maximum resolution and frame rate for encoding. <br>
     *        + The video streams are encoded by default with resolution of 640px × 360px and frame rate of 15fps. <br>
     *        When you call this API, it will take effect immediately, which may cause the camera to restart. <br>
     *        + The screen stream takes the first set of parameters.
     */
    BYTERTC_DEPRECATED virtual int setVideoEncoderConfig(StreamIndex index, const VideoSolution* solutions, int solution_num) = 0;

    /**
     * @locale zh
     * @hidden(Linux, macOS)
     * @valid since 3.58
     * @type api
     * @region 视频管理
     * @brief 开启自定义采集视频帧的 Alpha 通道编码功能。
     *        适用于需要分离推流端视频主体与背景，且在拉流端可自定义渲染背景的场景。
     * @param index 需开启该功能的视频流类型，当前仅支持对 StreamIndex.kStreamIndexMain 即主流开启。
     * @param layout 分离后的 Alpha 通道相对于 RGB 通道信息的排列位置。当前仅支持 AlphaLayout.kAlphaLayoutTop，即置于 RGB 通道信息上方。
     * @return 方法调用结果：
     *         - 0：成功；
     *         - !0：失败。
     * @notes <br>
     *        - 该接口仅作用于自定义采集的、并且使用 RGBA 色彩模型的视频帧，包括：
     *            - Windows：VideoPixelFormat.kVideoPixelFormatRGBA；
     *            - Android：VideoPixelFormat.TEXTURE_2D、VideoPixelFormat.TEXTURE_OES、VideoPixelFormat.RGBA；
     *            - iOS：ByteRTCVideoPixelFormat.ByteRTCVideoPixelFormatCVPixelBuffer。
     *        - 该接口须在发布视频流之前调用。
     *        - 调用本接口开启 Alpha 通道编码后，你需调用 pushExternalVideoFrame{@link #IRTCVideo#pushExternalVideoFrame} 把自定义采集的视频帧推送至 RTC SDK。若推送了不支持的视频帧格式，则调用 pushExternalVideoFrame{@link #IRTCVideo#pushExternalVideoFrame} 时会返回错误码 ReturnStatus.kReturnStatusParameterErr。
     */
    virtual int enableAlphaChannelVideoEncode(StreamIndex streamIndex, AlphaLayout alphaLayout) = 0;

    /**
     * @locale zh
     * @valid since 3.58
     * @type api
     * @region 视频管理
     * @brief 关闭外部采集视频帧的 Alpha 通道编码功能。
     * @param streamIndex 需关闭该功能的视频流类型，当前仅支持设置为 StreamIndex.kStreamIndexMain 即主流。
     * @return 方法调用结果：
     *         - 0：成功；
     *         - !0：失败。
     * @notes 该接口须在停止发布视频流之后调用。 
     */
    virtual int disableAlphaChannelVideoEncode(StreamIndex streamIndex) = 0;

    /**
     * @locale zh 
     * @type api
     * @region 视频管理
     * @brief 设置本地视频渲染时使用的视图，并设置渲染模式。
     * @param index 视频流属性, 参看 StreamIndex{@link #StreamIndex}
     * @param canvas 视图信息和渲染模式，参看：VideoCanvas{@link #VideoCanvas}
     * @return  
     *        + 0：成功  <br>
     *        + !0：失败  
     * @note  
     *        + 你应在加入房间前，绑定本地视图。退出房间后，此设置仍然有效。  <br>
     *        + 如果需要解除绑定，你可以调用本方法传入空视图。
     */
    /**
     * @locale en
     * @type api
     * @region Video Management
     * @brief Sets the view to be used for local video rendering and the rendering mode.  
     * @param index Video stream type. See StreamIndex{@link #StreamIndex}.
     * @param canvas View information and rendering mode. See VideoCanvas{@link #VideoCanvas}.
     * @return  
     *        + 0: Success <br>
     *        + -1: Failure 
     * @note  
     *       + You should bind your stream to a view before joining the room. This setting will remain in effect after you leave the room. <br>
     *       + If you need to unbind the local video stream from the current view, you can call this API and set the videoCanvas to `null`.
     */
    virtual int setLocalVideoCanvas(StreamIndex index, const VideoCanvas& canvas) = 0;

    /**
     * @locale zh
     * @type api
     * @region 视频管理
     * @brief 修改本地视频渲染模式和背景色。
     * @param index 视频流属性, 参看 StreamIndex{@link #StreamIndex}
     * @param render_mode 渲染模式，参看 RenderMode{@link #RenderMode}
     * @param background_color 背景颜色，参看 VideoCanvas{@link #VideoCanvas}.background_color
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note 你可以在本地视频渲染过程中，调用此接口。调用结果会实时生效。
     */
    /**
     * @locale en
     * @type api
     * @region Video management
     * @brief Update the render mode and background color of local video rendering
     * @param index See StreamIndex{@link #StreamIndex}.
     * @param render_mode See RenderMode{@link #RenderMode}.
     * @param background_color See VideoCanvas{@link #VideoCanvas}.background_color.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note Calling this API during local video rendering will be effective immediately.
     */
    virtual int updateLocalVideoCanvas(StreamIndex index, const enum RenderMode render_mode, const uint32_t background_color) = 0;

    /**
     * @locale zh
     * @type api
     * @region 视频管理
     * @brief 设置渲染指定视频流 `stream_key` 时，使用的视图和渲染模式。 <br>
     *        如果需要解除某个用户的绑定视图，你可以把 `canvas` 设置为空。
     * @param stream_key 参看 RemoteStreamKey{@link #RemoteStreamKey}
     * @param canvas 视图信息和渲染模式，参看：VideoCanvas{@link #VideoCanvas}
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note 本地用户离开房间时，会解除调用此 API 建立的绑定关系；远端用户离开房间则不会影响。
     */
    /**
     * @locale en
     * @type api
     * @region Video Management
     * @brief Set the view and mode for rendering the specific video stream. <br>
     *        If you need to unbind the canvas for the video stream, set the canvas to `Null`.
     * @param stream_key See RemoteStreamKey{@link #RemoteStreamKey}.
     * @param canvas canvas and rendering mode. See VideoCanvas{@link #VideoCanvas}
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note When the local user leaves the room, the setting will be invalid. The remote user leaving the room does not affect the setting.
     */
    virtual int setRemoteVideoCanvas(RemoteStreamKey stream_key, const VideoCanvas& canvas) = 0;

    /**
     * @locale zh
     * @deprecated since 3.56 on iOS and Android, and will be deleted in 3.62. Use [updateRemoteStreamVideoCanvas](70095#updateremotestreamvideocanvas-2) instead.
     * @type api
     * @region 视频管理
     * @brief 修改远端视频帧的渲染设置，包括渲染模式和背景颜色。
     * @param stream_key 远端流信息。参看 RemoteStreamKey{@link #RemoteStreamKey}。
     * @param render_mode 渲染模式，参看 RenderMode{@link #RenderMode}。
     * @param background_color 背景颜色，参看 VideoCanvas{@link #VideoCanvas}.background_color
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note 你可以在远端视频渲染过程中，调用此接口。调用结果会实时生效。
     */
    /**
     * @locale en
     * @deprecated since 3.56 on iOS and Android, and will be deleted in 3.62. Use [updateRemoteStreamVideoCanvas](70095#updateremotestreamvideocanvas-2) instead.
     * @type api
     * @region Video management
     * @brief Modifies remote video frame rendering settings, including render mode and background color.
     * @param stream_key See RemoteStreamKey{@link #RemoteStreamKey}.
     * @param render_mode See RenderMode{@link #RenderMode}.
     * @param background_color See VideoCanvas{@link #VideoCanvas}.background_color.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note Calling this API during remote video rendering will be effective immediately.
     */
    virtual int updateRemoteStreamVideoCanvas(RemoteStreamKey stream_key, const enum RenderMode render_mode, const uint32_t background_color) = 0;

    /**
     * @locale zh
     * @hidden(Windows, macOS, Linux)
     * @valid since 3.56
     * @type api
     * @region 视频管理
     * @brief 使用 SDK 内部渲染时，修改远端视频帧的渲染设置，包括渲染模式、背景颜色和旋转角度。
     * @param stream_key 远端流信息。参看 RemoteStreamKey{@link #RemoteStreamKey}。
     * @param remote_video_render_config 视频帧渲染设置。具体参看 RemoteVideoRenderConfig{@link #RemoteVideoRenderConfig}。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note
     *        + 调用 setRemoteVideoCanvas{@link #IRTCVideo#setRemoteVideoCanvas} 设置了远端视频渲染模式后，你可以调用此接口更新渲染模式、背景颜色、旋转角度的设置。<br>
     *        + 该接口可以在远端视频渲染过程中调用，调用结果会实时生效。
     */
    /**
     * @locale en
     * @hidden(Windows, macOS, Linux)
     * @valid since 3.56
     * @type api
     * @region Video management
     * @brief Modifies remote video frame rendering settings, including render mode, background color, and rotation angle, while using the internal rendering of the SDK.
     * @param stream_key Information about the remote stream. See RemoteStreamKey{@link #RemoteStreamKey}.
     * @param remote_video_render_config Video rendering settings. See RemoteVideoRenderConfig{@link #RemoteVideoRenderConfig}.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Failure. See ReturnStatus{@link #ReturnStatus} for more details
     * @note
     *        + After setting the rendering configuration for the remote video frame with setRemoteVideoCanvas{@link #IRTCVideo#setRemoteVideoCanvas}, you can call this API to update settings including render mode, background color, and rotation angle.<br>
     *        + Calling this API during remote video rendering will be effective immediately.
     */
    virtual int updateRemoteStreamVideoCanvas(RemoteStreamKey stream_key, const RemoteVideoRenderConfig& remote_video_render_config) = 0;

    /**
     * @locale zh
     * @type api
     * @deprecated since 3.57, use setLocalVideoRender{@link #IRTCVideo#setLocalVideoRender} instead.
     * @region 自定义视频采集渲染
     * @brief 将本地视频流与自定义渲染器绑定。
     * @param index 视频流属性。采集的视频流/屏幕视频流，参看 StreamIndex{@link #StreamIndex}
     * @param video_sink 自定义视频渲染器，参看 IVideoSink{@link #IVideoSink}。
     * @param required_format video_sink 适用的视频帧编码格式，参看 PixelFormat{@link #PixelFormat}
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note  
     *        + RTC SDK 默认使用 RTC SDK 自带的渲染器（内部渲染器）进行视频渲染。<br>
     *        + 如果需要解除绑定，必须将 video_sink 设置为 null。退房时将清除绑定状态。<br>
     *        + 一般在收到 onFirstLocalVideoFrameCaptured{@link #IRTCVideoEventHandler#onFirstLocalVideoFrameCaptured} 回调通知完成本地视频首帧采集后，调用此方法为视频流绑定自定义渲染器；然后加入房间。<br>
     *        + 本方法获取的是前处理后的视频帧，如需获取其他位置的视频帧（如采集后的视频帧），请调用 setLocalVideoRender{@link #IRTCVideo#setLocalVideoRender}。
     */
    /**
     * @locale en
     * @type api
     * @region Custom Video Capturing & Rendering
     * @brief Binds the local video stream to a custom renderer.
     * @param index Video stream type. See StreamIndex{@link #StreamIndex}.
     * @param video_sink Custom video renderer. See IVideoSink{@link #IVideoSink}.
     * @param required_format Video frame encoding format that applys to custom rendering. See PixelFormat{@link #PixelFormat}.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note  
     *        + RTC SDK uses its own renderer (internal renderer) for video rendering by default.  <br>
     *        + Joining or leaving the room will not affect the binding state. <br>
     *        + If you need to unbind the video stream from the custom renderer, you must set video_sink to `null`.  <br>
     *        + You should call this API before joining the room, and after receiving onFirstLocalVideoFrameCaptured{@link #IRTCVideoEventHandler#onFirstLocalVideoFrameCaptured} which reports that the first local video frame has been successfully captured.<br>
     *        + This method gets video frames that have undergone preprocessing. If you need to obtain video frames from other positions, such as after capture, you should call setLocalVideoRender{@link #IRTCVideo#setLocalVideoRender} instead.
     */
    virtual int setLocalVideoSink(StreamIndex index, IVideoSink* video_sink, IVideoSink::PixelFormat required_format) = 0;

    /**
     * @locale zh
     * @valid since 3.57
     * @type api
     * @region 自定义视频帧回调
     * @brief 将本地视频流与自定义渲染器绑定。你可以通过参数设置返回指定位置和格式的视频帧数据。
     * @param index 视频流属性。采集的视频流/屏幕视频流，参看 StreamIndex{@link #StreamIndex}。
     * @param video_sink 自定义视频渲染器，参看 IVideoSink{@link #IVideoSink}。
     * @param render_config 本地视频帧回调配置，参看 LocalVideoSinkConfig{@link #LocalVideoSinkConfig}。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0: 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明。
     * @note  
     *        + RTC SDK 默认使用自带的渲染器（内部渲染器）进行视频渲染。<br>
     *        + 退房时将清除绑定状态。<br>
     *        + 如果需要解除绑定，你必须将 video_sink 设置为 null。<br>
     *        + 一般在收到 onFirstLocalVideoFrameCaptured{@link #IRTCVideoEventHandler#onFirstLocalVideoFrameCaptured} 回调通知完成本地视频首帧采集后，调用此方法为视频流绑定自定义渲染器；然后加入房间。
     */
    virtual int setLocalVideoRender(StreamIndex index, IVideoSink* video_sink, LocalVideoSinkConfig& render_config) = 0;

    /**
     * @locale zh
     * @type api
     * @deprecated since 3.57, use setRemoteVideoRender{@link #IRTCVideo#setRemoteVideoRender} instead.
     * @region 自定义视频采集渲染
     * @brief 将远端视频流与自定义渲染器绑定。
     * @param stream_key 远端流信息，用于指定需要渲染的视频流来源及属性，参看 RemoteStreamKey{@link #RemoteStreamKey}。
     * @param video_sink 自定义视频渲染器，参看 IVideoSink{@link #IVideoSink}。
     * @param required_format video_sink 适用的视频帧编码格式，参看 PixelFormat{@link #PixelFormat}。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note  
     *        + RTC SDK 默认使用 RTC SDK 自带的渲染器（内部渲染器）进行视频渲染。<br>
     *        + 该方法进房前后均可以调用。若想在进房前调用，你需要在加入房间前获取远端流信息；若无法预先获取远端流信息，你可以在加入房间并通过 onUserPublishStream{@link #IRTCRoomEventHandler#onUserPublishStream} 回调获取到远端流信息之后，再调用该方法。<br>
     *        + 如果需要解除绑定，必须将 video_sink 设置为 null。退房时将清除绑定状态。<br>
     *        + 本方法获取的是后处理后的视频帧，如需获取其他位置的视频帧（如解码后的视频帧），请调用 setRemoteVideoRender{@link #IRTCVideo#setRemoteVideoRender}。
     */
    /**
     * @locale en
     * @type api
     * @region Custom Video Capturing & Rendering
     * @brief Binds the remote video stream to a custom renderer.
     * @param stream_key Remote stream information which specifys the source and type of the video stream to be rendered. See RemoteStreamKey{@link #RemoteStreamKey}.
     * @param video_sink Custom video renderer. See IVideoSink{@link #IVideoSink}.
     * @param required_format Encoding format which applys to the custom renderer. See PixelFormat{@link #PixelFormat}.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note   
     *        + RTC SDK uses its own renderer (internal renderer) for video rendering by default.  <br>
     *        + Joining or leaving the room will not affect the binding state. <br>
     *         + This API can be called before and after entering the room. To call before entering the room, you need to get the remote stream information before joining the room; if you cannot get the remote stream information in advance, you can call the API after joining the room and getting the remote stream information via onUserPublishStream{@link #IRTCRoomEventHandler#onUserPublishStream}.<br>
     *         + If you need to unbind, you must set videoSink to null.
     */
    virtual int setRemoteVideoSink(RemoteStreamKey stream_key, IVideoSink* video_sink, IVideoSink::PixelFormat required_format) = 0;
    
    /**
     * @locale zh
     * @valid since 3.57
     * @type api
     * @region 自定义视频帧回调
     * @brief 将远端视频流与自定义渲染器绑定。你可以通过参数设置返回指定位置和格式的视频帧数据。
     * @param stream_key 远端流信息，用于指定需要渲染的视频流来源及属性，参看 RemoteStreamKey{@link #RemoteStreamKey}。
     * @param video_sink 自定义视频渲染器，参看 IVideoSink{@link #IVideoSink}。
     * @param config 远端视频帧回调配置，参看 RemoteVideoSinkConfig{@link #RemoteVideoSinkConfig}。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0: 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明。
     * @note  
     *        + RTC SDK 默认使用自带的渲染器（内部渲染器）进行视频渲染。<br>
     *        + 该方法进房前后均可以调用。若想在进房前调用，你需要在加入房间前获取远端流信息；若无法预先获取远端流信息，你可以在加入房间并通过 onUserPublishStream{@link #IRTCRoomEventHandler#onUserPublishStream} 回调获取到远端流信息之后，再调用该方法。<br>
     *        + 退房时将清除绑定状态。<br>
     *        + 如果需要解除绑定，你必须将 video_sink 设置为 null。
     */
    virtual int setRemoteVideoRender(RemoteStreamKey stream_key, IVideoSink* video_sink, RemoteVideoSinkConfig& config) = 0;

    /**
     * @locale zh
     * @hidden(macOS,Windows,Linux)
     * @type api
     * @region 视频管理
     * @brief 切换视频内部采集时使用的前置/后置摄像头 <br>
     *        调用此接口后，在本地会触发 onVideoDeviceStateChanged{@link #IRTCVideoEventHandler#onVideoDeviceStateChanged} 回调。
     * @param camera_id 参看 CameraID {@link #CameraID}。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note  
     *       + 默认使用前置摄像头。<br>
     *       + 如果你正在使用相机进行视频采集，切换操作当即生效；如果相机未启动，后续开启内部采集时，会打开设定的摄像头。<br>
     *       + 如果本地有多个摄像头且想选择特定工作摄像头可通过 IVideoDeviceManager{@link #IVideoDeviceManager} 来控制。  
     */
    /**
     * @locale en
     * @hidden(macOS,Windows,Linux)
     * @type api
     * @region Video management
     * @brief Toggle the front/postcondition camera used for internal video capture  <br>
     *        After calling this interface, onVideoDeviceStateChanged{@link #IRTCVideoEventHandler#onVideoDeviceStateChanged} callback will be triggered locally.
     * @param camera_id See CameraID{@link #CameraID}.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note   
     *        + Default uses front-facing camera.<br>
     *        + If you are using the camera for video capture, the toggle operation will take effect immediately; if the camera is not activated, the set camera will be turned on when the internal capture is turned on later.<br>
     *        + If you have multiple cameras locally and want to select a specific working camera, you can control it through IVideoDeviceManager{@link #IVideoDeviceManager}. 
     */
    virtual int switchCamera(CameraID camera_id) = 0;

    /**
     * @locale zh
     * @type api
     * @region 屏幕共享
     * @brief 推送屏幕视频帧
     * @param frame 设置屏幕视频帧，详见：IVideoFrame{@link #IVideoFrame}。  
     * @return 方法调用结果：<br>
     *        + 0：成功；<br>
     *        + <0：失败。具体失败原因参看 ReturnStatus{@link #ReturnStatus}。
     * @note  
     *       + 暂时只支持 YUV420P 格式的视频帧。  <br>
     *       + 该函数运行在用户调用线程内，即将销毁 IRTCVideo 实例前，请停止调用该函数推送屏幕共享数据  
     */
    /**
     * @locale en
     * @type api
     * @region Screen sharing
     * @brief Push screen video frame.
     * @param frame Set the screen video frame, see: IVideoFrame{@link #IVideoFrame}. 
     * @return API call result:<br>
     *        + 0: Success.<br>
     *        + <0: Failure. See ReturnStatus{@link #ReturnStatus} for specific reasons.
     * @note   
     *        + Only video frames in YUV420P format are supported for the time being. <br>
     *        + This function runs in the user calling thread. Before destroying the IRTCVideo instance, please stop calling this function to push screen shared data 
     */
    virtual int pushScreenVideoFrame(IVideoFrame* frame) = 0;

    /**
     * @locale zh
     * @hidden(Linux,iOS,Android)
     * @type api
     * @region 屏幕共享
     * @brief  外部采集时，当屏幕或待采集窗口大小发生改变，为了使 RTC 更好地决策合适的帧率和分辨率积，调用此接口设置改变前的分辨率。
     * @param original_capture_width 首次采集屏幕流的宽度。
     * @param original_capture_height 首次采集屏幕流的高度。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note  
     *        + 调用此接口之前，建议调用 setScreenVideoEncoderConfig{@link #IRTCVideo#setScreenVideoEncoderConfig} 设置屏幕流编码相关参数：编码模式设置为智能模式，屏幕帧宽高设置为0，最大码率设置为-1，最小码率设置为0。<br>
     *        + 调用此接口后，你将收到回调 onExternalScreenFrameUpdate{@link #IRTCVideoEventHandler#onExternalScreenFrameUpdate}，根据推荐的帧率和分辨率积重新采集。
     */
    /**
     * @locale en
     * @hidden(Linux,iOS,Android)
     * @type api
     * @region screen sharing
     * @brief When the resolution of the external shared-screen stream changes, you can call this API to set the original pixel and framerate to help RTC(in the automatic mode) recommend these configurations.
     * @param original_capture_width The original width of shared-screen streams.
     * @param original_capture_height The original height of shared-screen streams.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note  
     *        + Before calling this API，you are advised to call setScreenVideoEncoderConfig{@link #IRTCVideo#setScreenVideoEncoderConfig} to set the encoding configurations: set the encoding mode to the automatic mode, the width and height to 0, the maximum bitrate to -1, and the minimum bitrate to 0.<br>
     *        + After calling this API，you will receive onExternalScreenFrameUpdate{@link #IRTCVideoEventHandler#onExternalScreenFrameUpdate} to re-capture the stream based on the recommended pixel and framerate by RTC.
     */
    virtual int setOriginalScreenVideoInfo(int original_capture_width, int original_capture_height) = 0;

    /**
     * @locale zh
     * @hidden(Android,iOS)
     * @type api
     * @region 屏幕共享
     * @brief 通过 RTC SDK 提供的采集模块采集屏幕视频流时，更新采集区域。仅用于采集源为显示器屏幕时。
     * @param region_rect 采集区域。参见 Rectangle{@link #Rectangle}  <br>
     *                         此参数描述了调用此接口后的采集区域，和 startScreenVideoCapture{@link #IRTCVideo#startScreenVideoCapture} 中 `source_info` 设定区域的相对关系。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note 调用此接口前，必须已通过调用 startScreenVideoCapture{@link #IRTCVideo#startScreenVideoCapture} 开启了内部屏幕流采集。
     */
    /**
     * @locale en
     * @hidden(Android,iOS)
     * @type api
     * @region Screen sharing
     * @brief Update the capture area when capturing screen video streams through the capture module provided by the RTC SDK. Only used when the capture source is the monitor screen.
     * @param region_rect Region to be shared. See Rectangle{@link #Rectangle} <br>
     *                         This parameter describes the region to be shared after calling this API, and the relative relationship between the `source_info` setting area in startScreenVideoCapture{@link #IRTCVideo#startScreenVideoCapture}.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note Before calling this interface, internal screen stream capture must have been turned on by calling startScreenVideoCapture{@link #IRTCVideo#startScreenVideoCapture}.
     */
    virtual int updateScreenCaptureRegion(const Rectangle& region_rect) = 0;

    /**
     * @locale zh
     * @hidden(Android,iOS)
     * @type api
     * @region 屏幕共享
     * @brief 采集屏幕视频流，用于共享。屏幕视频流包括：屏幕上显示的内容，应用窗口中显示的内容，或虚拟屏幕中显示的内容。<br>
     *        其中，虚拟屏幕中显示的内容仅在 Windows 平台上支持。
     * @param source_info 待共享的屏幕源，参看 ScreenCaptureSourceInfo{@link #ScreenCaptureSourceInfo}。<br>
     *                         你可以调用 getScreenCaptureSourceList{@link #IRTCVideo#getScreenCaptureSourceList} 获得所有可以共享的屏幕源。
     * @param capture_params 共享参数。参看 ScreenCaptureParameters{@link #ScreenCaptureParameters}。
     * @return  
     *        + 0: 成功  <br>
     *        + -1: 失败  
     * @note  
     *       + 调用本接口时，采集模式应为内部模式。在外部采集模式下调用无效，并将触发 onVideoDeviceWarning{@link #IRTCVideoEventHandler#onVideoDeviceWarning} 回调。<br>
     *       + 调用此方法仅开启屏幕流视频采集，不会发布采集到的视频。发布屏幕流视频需要调用 publishScreen{@link #IRTCRoom#publishScreen}。<br>
     *       + 调用 stopScreenVideoCapture{@link #IRTCVideo#stopScreenVideoCapture} 关闭屏幕视频源采集。  <br>
     *       + 本地用户通过 onVideoDeviceStateChanged{@link #IRTCVideoEventHandler#onVideoDeviceStateChanged} 的回调获取屏幕采集状态，包括开始、暂停、恢复、错误等。  <br>
     *       + 调用成功后，本端会收到 onFirstLocalVideoFrameCaptured{@link #IRTCVideoEventHandler#onFirstLocalVideoFrameCaptured} 回调。  <br>
     *       + 调用此接口前，你可以调用 setScreenVideoEncoderConfig{@link #IRTCVideo#setScreenVideoEncoderConfig} 设置屏幕视频流的采集帧率和编码分辨率。  <br>
     *       + 在收到 onFirstLocalVideoFrameCaptured{@link #IRTCVideoEventHandler#onFirstLocalVideoFrameCaptured} 回调后通过调用 setLocalVideoCanvas{@link #IRTCVideo#setLocalVideoCanvas} 或 setLocalVideoSink{@link #setLocalVideoSink} 函数设置本地屏幕共享视图。  <br>
     *       + 可以调用 setLocalVideoSink{@link #IRTCVideo#setLocalVideoSink} 将本地视频流与自定义渲染器绑定，通过回调 onFrame{@link #IVideoSink#onFrame} 获取采集成功的本地视频帧。 <br>
     *       + 对于 Windows SDK，再开启采集屏幕视频流后，你可以调用 updateScreenCaptureHighlightConfig{@link #IRTCVideo#updateScreenCaptureHighlightConfig}更新边框高亮设置，调用 updateScreenCaptureMouseCursor{@link #IRTCVideo#updateScreenCaptureMouseCursor}更新对鼠标的处理设置，调用 updateScreenCaptureFilterConfig{@link #IRTCVideo#updateScreenCaptureFilterConfig}设置需要过滤的窗口。  
     */
    /**
     * @locale en
     * @hidden(Android,iOS)
     * @type api
     * @region  screen sharing
     * @brief  Capture screen video stream for sharing. Screen video stream includes: content displayed on the screen, in the application window, or in the virtual screen. <br>
     *        Displaying contents in virtual screens is only available on Windows.
     * @param source_info Screen capture source information. See ScreenCaptureSourceInfo{@link #ScreenCaptureSourceInfo}. <br>
     *                          Call getScreenCaptureSourceList{@link #IRTCVideo#getScreenCaptureSourceList} to get all the screen sources that can be shared.
     * @param capture_params Screen capture parameters. See ScreenCaptureParameters{@link #ScreenCaptureParameters}.
     * @return   
     *         + 0: Success; <br>
     *         + -1: Failure; 
     * @note   
     *        + The call of this API takes effects only when you are using RTC SDK to record screen. You will get a warning by onVideoDeviceWarning{@link #IRTCVideoEventHandler#onVideoDeviceWarning} after calling this API when the video source is set to an external recorder.<br>
     *        + This API only starts screen capturing but does not publish the captured video. Call publishScreen{@link #IRTCRoom#publishScreen} to publish the captured video. <br>
     *        + To turn off screen video capture, call stopScreenVideoCapture{@link #IRTCVideo#stopScreenVideoCapture}. <br>
     *        + Local users will receive onVideoDeviceStateChanged{@link #IRTCVideoEventHandler#onVideoDeviceStateChanged} on the state of screen capturing such as start, pause, resume, and error. <br>
     *        + After successfully calling this API, local users will receive onFirstLocalVideoFrameCaptured{@link #IRTCVideoEventHandler#onFirstLocalVideoFrameCaptured}. <br>
     *        + Before calling this API, you can call setScreenVideoEncoderConfig{@link #IRTCVideo#setScreenVideoEncoderConfig} to set the frame rate and encoding resolution of the screen video stream. <br>
     *        + After receiving onFirstLocalVideoFrameCaptured{@link #IRTCVideoEventHandler#onFirstLocalVideoFrameCaptured}, you can set the local screen sharing view by calling setLocalVideoCanvas{@link #IRTCVideo#setLocalVideoCanvas} or setLocalVideoSink {@link #setLocalVideoSink}. <br>
     *        + You can also register an observer by calling setLocalVideoSink{@link #IRTCVideo#setLocalVideoSink} and receive the captured screen video frame through onFrame{@link #IVideoSink#onFrame}.<br>
     *        + For Windows SDK, after you start capturing screen video stream for sharing，you can call updateScreenCaptureHighlightConfig{@link #IRTCVideo#updateScreenCaptureHighlightConfig} to update border highlighting settings, updateScreenCaptureMouseCursor{@link #IRTCVideo#updateScreenCaptureMouseCursor} to update the processing settings for the mouse, and updateScreenCaptureFilterConfig{@link #IRTCVideo#updateScreenCaptureFilterConfig} to set the window that needs to be filtered.
     */
    virtual int startScreenVideoCapture(const ScreenCaptureSourceInfo& source_info, const ScreenCaptureParameters& capture_params) = 0;

    /**
     * @locale zh
     * @hidden(Android,iOS)
     * @type api
     * @region 屏幕共享
     * @brief 停止屏幕视频流采集。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note  
     *       + 调用本接口时，采集模式应为内部模式。在外部采集模式下调用无效，并将触发 onVideoDeviceWarning{@link #IRTCVideoEventHandler#onVideoDeviceWarning} 回调。<br>
     *       + 要开启屏幕视频流采集，调用 startScreenVideoCapture{@link #IRTCVideo#startScreenVideoCapture}。  <br>
     *       + 调用后，本地用户会收到 onVideoDeviceStateChanged{@link #IRTCVideoEventHandler#onVideoDeviceStateChanged} 的回调。  <br>
     *       + 调用此接口不影响屏幕视频流发布。
     */
    /**
     * @locale en
     * @hidden(Android,iOS)
     * @type api
     * @region screen sharing
     * @brief Stop screen video streaming.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note   
     *        + This API can only stop the screen capture by the RTC SDK. If the video source has been set to external recorder, the call of this API will fail. You need to stop it in the external recorder. <br>
     *        + The call of this API takes effects only when you are using RTC SDK to record screen. You will get a warning by onVideoDeviceWarning{@link #IRTCVideoEventHandler#onVideoDeviceWarning} after calling this API when the video source is set to an external recorder.<br>
     *        + To turn on screen video stream capture, calling startScreenVideoCapture{@link #IRTCVideo#startScreenVideoCapture} <br>
     *        + Local users will receive the onVideoDeviceStateChanged{@link #IRTCVideoEventHandler#onVideoDeviceStateChanged} callback. <br>
     *        + Calling this interface does not affect screen video stream publishing.
     */
    virtual int stopScreenVideoCapture() = 0;

    /**
     * @locale zh
     * @hidden(Android,iOS)
     * @type api
     * @region 屏幕共享
     * @brief 通过 RTC SDK 提供的采集模块采集屏幕视频流时，更新边框高亮设置。默认展示表框。
     * @param highlight_config 边框高亮设置。参见 HighlightConfig{@link #HighlightConfig}
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note 
     *        + 调用此接口前，必须已通过调用 startScreenVideoCapture{@link #IRTCVideo#startScreenVideoCapture} 开启了内部屏幕流采集。<br>
     *        + 对 Linux 系统，采用 X11 协议时可用；采用 Wayland 协议时不可用。
     */
    /**
     * @locale en
     * @hidden(Android,iOS)
     * @type api
     * @region Screen sharing
     * @brief Update border highlighting settings when capturing screen video streams through the capture module provided by the RTC SDK. The default display table box.
     * @param highlight_config Border highlighting settings. See HighlightConfig{@link #HighlightConfig}
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note  
     *        + Before calling this interface, you must have turned on internal screen flow collection by calling startScreenVideoCapture{@link #IRTCVideo#startScreenVideoCapture}. <br>
     *        + For Linux with X11 protocal, the API is valid; for Linux with Wayland, the API is not valid.
     */
    virtual int updateScreenCaptureHighlightConfig(const HighlightConfig& highlight_config) = 0;

    /**
     * @locale zh
     * @hidden(Android,iOS)
     * @type api
     * @region 屏幕共享
     * @brief 通过 RTC SDK 提供的采集模块采集屏幕视频流时，更新对鼠标的处理设置。默认采集鼠标。
     * @param capture_mouse_cursor 参看 MouseCursorCaptureState{@link #MouseCursorCaptureState}
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note 调用此接口前，必须已通过调用 startScreenVideoCapture{@link #IRTCVideo#startScreenVideoCapture} 开启了内部屏幕流采集。
     */
    /**
     * @locale en
     * @hidden(Android,iOS)
     * @type api
     * @region Screen sharing
     * @brief Update the processing settings for the mouse when capturing screen video streams through the capture module provided by the RTC SDK. Default acquisition mouse.
     * @param capture_mouse_cursor See MouseCursorCaptureState{@link #MouseCursorCaptureState}
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note  Before calling this interface, internal screen stream capture must have been turned on by calling startScreenVideoCapture{@link #IRTCVideo#startScreenVideoCapture}.
     */
    virtual int updateScreenCaptureMouseCursor(MouseCursorCaptureState capture_mouse_cursor) = 0;

    /**
     * @locale zh
     * @hidden(Linux,iOS,Android)
     * @type api
     * @region 屏幕共享
     * @brief 通过 RTC SDK 提供的采集模块采集屏幕视频流时，设置需要过滤的窗口。
     * @param filter_config 窗口过滤设置，参看 ScreenFilterConfig{@link #ScreenFilterConfig}  
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note 
     *       + 调用此接口前，必须已通过调用 startScreenVideoCapture{@link #IRTCVideo#startScreenVideoCapture} 开启了内部屏幕流采集。<br>
     *       + 本函数在屏幕源类别是屏幕而非应用窗体时才起作用。详见：ScreenCaptureSourceType{@link #ScreenCaptureSourceType}。 
     */
    /**
     * @locale en
     * @hidden(Linux,iOS,Android)
     * @type api
     * @region Screen sharing
     * @brief When capturing screen video streams through the capture module provided by the RTC SDK, set the window that needs to be filtered.
     * @param filter_config Window filtering settings. See ScreenFilterConfig{@link #ScreenFilterConfig} 
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note 
     *        + Before calling this interface, internal screen stream capture must have been turned on by calling startScreenVideoCapture{@link #IRTCVideo#startScreenVideoCapture}. <br>
     *        + This function only works when the screen source category is a screen rather than an application form. See ScreenCaptureSourceType{@link #ScreenCaptureSourceType}. 
     */
    virtual int updateScreenCaptureFilterConfig(const ScreenFilterConfig& filter_config) = 0;

    /**
     * @locale zh
     * @hidden(Android,iOS)
     * @brief 获取共享对象列表。
     * @return 共享对象列表，包括应用窗口和屏幕。详见 IScreenCaptureSourceList{@link #IScreenCaptureSourceList}。用户选择后，可调用 startScreenVideoCapture{@link #IRTCVideo#startScreenVideoCapture} 进行共享。
     * @note 
     *        + 对 Linux 系统，采用 X11 协议时可用；采用 Wayland 协议时不可用。采用 Wayland 协议，调用 startScreenVideoCapture{@link #IRTCVideo#startScreenVideoCapture} 时，系统会通过弹窗供用户选择共享对象。<br>
     *        + 使用完之后需要调用 release{@link #IScreenCaptureSourceList#release} 接口释放。
     */
    /**
     * @locale en
     * @hidden(Android,iOS)
     * @brief Get the item list for screen sharing.
     * @return List of the screen-sharing objects, including application window and screens. See IScreenCaptureSourceList{@link #IScreenCaptureSourceList}. After deciding which item to be shared, the user can share the object with startScreenVideoCapture{@link #IRTCVideo#startScreenVideoCapture}.
     * @note 
     *        + For Linux with X11 protocal, the API is valid; for Linux with Wayland, the API is not valid. For Linux with Wayland, when you call startScreenVideoCapture{@link #IRTCVideo#startScreenVideoCapture}, the system pops a windows for the user to choose the object to share. <br>
     *        + Call release{@link #IScreenCaptureSourceList#release} to release the resources.
     */
    virtual IScreenCaptureSourceList* getScreenCaptureSourceList() = 0;

    /**
     * @locale zh
     * @hidden(Android,iOS)
     * @brief 获取共享对象缩略图
     * @region 屏幕共享
     * @param type 屏幕采集对象的类型。详见 ScreenCaptureSourceType{@link #ScreenCaptureSourceType}。
     * @param source_id 屏幕共享对象的 ID，可通过 getScreenCaptureSourceList{@link #IRTCVideo#getScreenCaptureSourceList} 枚举共享对象列表中获取。详见 [view_t](70098#view-t)。
     * @param max_width 最大宽度。保持采集对象本身的宽高比不变，将缩略图缩放到指定范围内的最大宽高。如果给出的尺寸与共享对象比例不同，得到的缩略图会有黑边。
     * @param max_height 最大高度。参见 max_width 的说明。
     * @return 共享对象缩略图，详见 IVideoFrame{@link #IVideoFrame}。
     * @note 对 Linux 系统，采用 X11 协议时可用；采用 Wayland 协议时不可用。
     */
    /**
     * @locale en
     * @hidden(Android,iOS)
     * @brief Get the preview thumbnail of the screen-sharing object
     * @region  screen share
     * @param type Type of the screen capture object. Refer to ScreenCaptureSourceType{@link #ScreenCaptureSourceType} for more details.
     * @param source_id ID of the screen-shared object. Refer to view_t{@link #view_t} for more details.
     * @param max_width Maximum width of the preview thumbnail. RTC will scale the thumbnail to fit the given size while maintaining the original aspect ratio. If the aspect ratio of the given size does not match the sharing object, the thumbnail will have blank borders.
     * @param max_height Maximum height of the preview thumbnail. Refer to the note for `max_width`.
     * @return Preview thumbnail of the screen-sharing object Refer to IVideoFrame{@link #IVideoFrame} for more details.
     * @note For Linux with X11 protocal, the API is valid; for Linux with Wayland, the API is not valid.
     */
    virtual IVideoFrame* getThumbnail(
            ScreenCaptureSourceType type, view_t source_id, int max_width, int max_height) = 0;
    /**
     * @locale zh
     * @hidden(Android,iOS)
     * @region 屏幕共享
     * @brief 获取应用窗体所属应用的图标。
     * @param source_id 屏幕共享对象的 ID，可通过 getScreenCaptureSourceList{@link #IRTCVideo#getScreenCaptureSourceList} 枚举共享对象列表中获取。详见 [view_t](70098#view-t)。
     * @param max_width 最大宽度。返回的图标将是宽高相等的，输入宽高不等时，取二者较小值。宽高范围为 [32,256]，超出该范围将返回 nullptr，默认输出 100 x 100 的图像。
     * @param max_height 最大高度。参见 max_width 的说明。
     * @return 详见 IVideoFrame{@link #IVideoFrame}。当屏幕共享对象为应用窗体，且有图标时有效，否则返回 nullptr。
     * @note 对 Linux 系统，采用 X11 协议时可用；采用 Wayland 协议时不可用。
     */
    /**
     * @locale en
     * @hidden(Android,iOS)
     * @brief Get application window preview thumbnail for screen sharing.
     * @param source_id ID of the screen-sharing object. You can get the ID by calling getScreenCaptureSourceList{@link #IRTCVideo#getScreenCaptureSourceList}. Refer to view_t{@link #view_t} for more details.
     * @param max_width Maximum width of the App icon. The width is always equal to the height. SDK will set the height and width to the smaller value if the given values are unequal. RTC will return nullptr if you set the value with a number out of the valid range, [32, 256]. The default size is 100 x 100.
     * @param max_height Maximum height of the app icon. Refer to the note for  `max_width`
     * @return Refer to IVideoFrame{@link #IVideoFrame} for more details. You can get the icon when the item to be shared is an application and the application is assigned with an icon. If not, the return value will be nullptr.
     * @note For Linux with X11 protocal, the API is valid; for Linux with Wayland, the API is not valid.
     */
    virtual IVideoFrame* getWindowAppIcon(view_t source_id, int max_width = 100, int max_height = 100) = 0;

    /**
     * @locale zh
     * @type api
     * @region 视频管理
     * @brief 设置向 SDK 输入的视频源，包括屏幕流<br>
     *        默认使用内部采集。内部采集指：使用 RTC SDK 内置的视频采集机制进行视频采集。 
     * @param stream_index 视频流的属性，参看 StreamIndex{@link #StreamIndex}
     * @param type 视频输入源类型，参看 VideoSourceType{@link #VideoSourceType}
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note  
     *        + 该方法进房前后均可调用。  <br>
     *        + 当你已调用 startVideoCapture{@link #IRTCVideo#startVideoCapture} 开启内部采集后，再调用此方法切换至自定义采集时，SDK 会自动关闭内部采集。  <br>
     *        + 当你调用此方法开启自定义采集后，想要切换至内部采集，你必须先调用此方法关闭自定义采集，然后调用 startVideoCapture{@link #IRTCVideo#startVideoCapture} 手动开启内部采集。  <br>
     *        + 当你需要向 SDK 推送自定义编码后的视频帧，你需调用该方法将视频源切换至自定义编码视频源。
     */
    /**
     * @locale en
     * @type api
     * @region Video management
     * @brief Set the video source, including the screen recordings.<br>
     *        The internal video capture is the default, which refers to capturing video using the built-in module.
     * @param stream_index Stream index. Refer to StreamIndex{@link #StreamIndex} for more details.
     * @param type Video source type. Refer to VideoSourceType{@link #VideoSourceType} for more details.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note   
     *         + You can call this API whether the user is in a room or not. <br>
     *         + Calling this API to switch to the custom video source will stop the enabled internal video capture.<br>
     *         + To switch to internal video capture, call this API to stop custom capture and then call startVideoCapture{@link #IRTCVideo#startVideoCapture} to enable internal video capture.<br>
     *         + To push custom encoded video frames to the SDK, call this API to switch `VideoSourceType` to `VideoSourceTypeEncodedWithAutoSimulcast` or `VideoSourceTypeEncodedWithoutAutoSimulcast`.
     */
    virtual int setVideoSourceType(StreamIndex stream_index, VideoSourceType type) = 0;

    /**
     * @locale zh
     * @type api
     * @region 视频管理
     * @brief 推送外部视频帧。
     * @param frame 设置视频帧，参看 IVideoFrame{@link #IVideoFrame}。
     * @return 方法调用结果：<br>
     *        + 0：成功；<br>
     *        + <0：失败。具体失败原因参看 ReturnStatus{@link #ReturnStatus}。
     * @note  
     *       + 支持格式：I420, NV12, RGBA, BGRA, ARGB  <br>
     *       + 该函数运行在用户调用线程内  <br>
     *       + 推送外部视频帧前，必须调用 setVideoSourceType{@link #setVideoSourceType} 开启外部视频源采集。
     */
    /**
     * @locale en
     * @type api
     * @region  Video Management
     * @brief Pushes external video frames.
     * @param frame Set the video frame. See IVideoFrame{@link #IVideoFrame}.
     * @return API call result:<br>
     *        + 0: Success.<br>
     *        + <0: Failure. See ReturnStatus{@link #ReturnStatus} for specific reasons.
     * @note  
     *        + Support for I420, NV12, RGBA, BGRA, and ARGB.<br>
     *        + This function runs in the user calling thread. <br>
     *        + Before pushing external video frames, you must call setVideoSourceType{@link #setVideoSourceType} to turn on external video source capture.
     */
    virtual int pushExternalVideoFrame(IVideoFrame* frame) = 0;

    /**
     * @locale zh
     * @hidden(Windows,Linux,macOS)
     * @deprecated since 3.38 and will be deleted in 3.51, use setDefaultAudioRoute{@link #IRTCVideo#setDefaultAudioRoute} instead on Android and iOS.
     * @type api
     * @region 音频设备管理
     * @brief 设置音频播放设备，默认使用扬声器。  
     * @param device 音频播放设备。参看 AudioPlaybackDevice{@link #AudioPlaybackDevice} 
     * @return 方法调用结果  <br>
     *        + 0: 方法调用成功  <br>
     *        + < 0: 方法调用失败  
     * @note  
     *       + 该接口仅适用于移动设备。  <br>
     *       + 该方法只支持将音视频播放设备设置为听筒或者扬声器。当 App 连接有线或蓝牙音频播放设备时，SDK 会自动切换到有线或蓝牙音频播放设备。主动设置为有线或蓝牙音频播放设备，会返回调用失败。  <br>
     *       + 若连接有线或者蓝牙音频播放设备时，将音频播放设备设置为扬声器或听筒将调用成功，但不会立马切换到扬声器或听筒，会在有线或者蓝牙音频播放设备移除后，根据设置自动切换到听筒或者扬声器。  <br>
     *       + 通话前和通话中都可以调用该方法。  
     */
    /**
     * @locale en
     * @hidden(Windows,Linux,macOS)
     * @deprecated since 3.45 and will be deleted in 3.51, use setDefaultAudioRoute{@link #IRTCVideo#setDefaultAudioRoute} instead on Android and iOS.
     * @type api
     * @region Audio Facility Management
     * @brief Set the audio playback device, and use speakers by default.   
     * @param device Audio playback device. See AudioPlaybackDevice{@link #AudioPlaybackDevice} 
     * @return Method call result   <br>
     *         + 0: Success. <br>
     *         + < 0: failure 
     * @note   
     *        + This interface is only available for mobile devices. <br>
     *        + This method only supports setting audio & video playback devices as earphones or speakers. When the app connects to a wired or Bluetooth audio playback device, the SDK automatically switches to a wired or Bluetooth audio playback device. Active setting as a wired or Bluetooth audio playback device will return Failure. <br>
     *        + If you connect a wired or Bluetooth audio playback device, setting the audio playback device as a speaker or earpiece will successfully call, but it will not immediately switch to the speaker or earpiece. After the wired or Bluetooth audio playback device is removed, it will automatically switch to the earpiece or speaker according to the settings.  <br>
     *        + This method can be called before and during a call. 
     */
    BYTERTC_DEPRECATED virtual int setAudioPlaybackDevice(AudioPlaybackDevice device) = 0;

    /**
     * @locale zh
     * @hidden(Windows,Linux,macOS)
     * @type api
     * @region 音频设备管理
     * @brief 设置音频播放设备。默认使用通过 setDefaultAudioRoute{@link #IRTCVideo#setDefaultAudioRoute} 设置的默认音频路由。<br>
     *        音频播放设备发生变化时，会收到 onAudioRouteChanged{@link #IRTCVideoEventHandler#onAudioRouteChanged} 回调。
     * @param device 音频播放设备。参看 AudioRoute{@link #AudioRoute}。仅支持听筒或者扬声器。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note  
     *       + 对于绝大多数音频场景，使用 setDefaultAudioRoute{@link #IRTCVideo#setDefaultAudioRoute} 设置默认音频路由，并借助 RTC SDK 的音频路由自动切换逻辑即可完成。切换逻辑参见[移动端设置音频路由](https://www.volcengine.com/docs/6348/117836)。你应仅在例外的场景下，使用此接口，比如在接入外接音频设备时，手动切换音频路由。<br>
     *       + 本接口仅支持在 `AUDIO_SCENARIO_COMMUNICATION` 音频场景下使用。你可以通过调用 setAudioScenario{@link #IRTCVideo#setAudioScenario} 切换音频场景。
     */
    /**
     * @locale en
     * @hidden(Windows,Linux,macOS)
     * @type api
     * @region Audio Facility Management
     * @brief Set the audio playback device. The audio route set by setDefaultAudioRoute{@link #IRTCVideo#setDefaultAudioRoute} by default.<br>
     *         When the audio playback device changes, you will receive an onAudioRouteChanged{@link #IRTCVideoEventHandler#onAudioRouteChanged} Callback.
     * @param device Audio playback device. See AudioRoute{@link #AudioRoute}. You can only set to earpiece or speakerphone.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note   
     *        + You can implement most scenarios by calling setDefaultAudioRoute{@link #IRTCVideo#setDefaultAudioRoute} and the default audio route switching strategy of the RTC SDK. For details about the strategy, see [Set the Audio Route](https://docs.byteplus.com/byteplus-rtc/docs/117836). You should use this API only in a few exceptional scenarios like manually switching audio route with external audio device connected.<br>
     *       + This interface is only supported in the `AUDIO_SCENARIO_COMMUNICATION` audio scenario. Call setAudioScenario{@link #IRTCVideo#setAudioScenario} to switch between different audio scenarios.
     */
    virtual int setAudioRoute(AudioRoute route) = 0;

    /**
     * @locale zh
     * @hidden(macOS,Windows,Linux)
     * @type api
     * @region 音频设备管理
     * @brief 将默认的音频播放设备设置为听筒或扬声器。  
     * @param route 音频播放设备。参看 AudioRoute{@link #AudioRoute} 
     * @return 方法调用结果  <br>
     *        + 0: 方法调用成功。立即生效。当所有音频外设移除后，音频路由将被切换到默认设备。<br>
     *        + < 0: 方法调用失败。指定除扬声器和听筒以外的设备将会失败。   
     * @note 对于音频路由切换逻辑，参见[移动端设置音频路由](https://www.volcengine.com/docs/6348/117836)。
     */
    /**
     * @locale en
     * @hidden(macOS,Windows,Linux)
     * @type api
     * @region Audio Facility Management
     * @brief Set the speaker or earpiece as the default audio playback device.   
     * @param route Audio playback device. Refer to AudioRoute{@link #AudioRoute} 
     * @return 
     *         + 0: Success. The setting takes effect immediately. However, the audio route will not switch to the default device until all the audio peripheral devices are disconnected. <br>
     *         + < 0: failure. It fails when the device designated is neither a speaker nor an earpiece.
     * @note For the audio route switching strategy of the RTC SDK, see [Set the Audio Route](https://docs.byteplus.com/byteplus-rtc/docs/117836).
     */
    virtual int setDefaultAudioRoute(AudioRoute route) = 0;

    /**
     * @locale zh
     * @hidden(macOS,Windows,Linux)
     * @type api
     * @region 音频设备管理
     * @brief 获取当前音频播放设备  <br>
     *        音频播放设备发生变化时，会收到 onAudioRouteChanged{@link #IRTCVideoEventHandler#onAudioRouteChanged} 回调。
     * @return device 当前音频播放设备。参看 AudioRoute{@link #AudioRoute}
     * @note  
     *       + 1. 该接口仅适用于移动设备。  <br>
     *       + 2. 通话前和通话中都可以调用该方法。  
     */
    /**
     * @locale en
     * @hidden(macOS,Windows,Linux)
     * @type api
     * @region Audio Facility Management
     * @brief get current using audio playback device.   <br>
     *         When the audio playback device changes, you will receive an onAudioRouteChanged{@link #IRTCVideoEventHandler#onAudioRouteChanged} Callback.
     * @return  device current using Audio playback device. See AudioRoute{@link #AudioRoute}
     * @note   
     *        + 1. This interface is only available for mobile devices. <br>
     *        + 2. This method can be called before and during a call. 
     */
    virtual AudioRoute getAudioRoute() = 0;
    /**
     * @locale zh
     * @type api
     * @region 房间管理
     * @brief 创建房间实例。<br>
     *        调用此方法仅返回一个房间实例，你仍需调用 joinRoom{@link #IRTCRoom#joinRoom} 才能真正地创建/加入房间。<br>
     *        多次调用此方法以创建多个 IRTCRoom{@link #IRTCRoom} 实例。分别调用各 IRTCRoom 实例中的 joinRoom{@link #IRTCRoom#joinRoom} 方法，同时加入多个房间。<br>
     *        多房间模式下，用户可以同时订阅各房间的音视频流。
     * @param room_id 标识通话房间的房间 ID。该字符串符合正则表达式：`[a-zA-Z0-9_@\-\.]{1,128}`。
     * @return 创建的 IRTCRoom{@link #IRTCRoom} 房间实例。
     * @note 
     *        + 如果需要加入的房间已存在，你仍需先调用本方法来获取 IRTCRoom 实例，再调用 joinRoom{@link #IRTCRoom#joinRoom} 加入房间。<br>
     *        + 请勿使用同样的 roomId 创建多个房间，否则后创建的房间实例会替换先创建的房间实例。<br>
     *        + 如果你需要在多个房间发布音视频流，无须创建多房间，直接调用 startForwardStreamToRooms{@link #IRTCRoom#startForwardStreamToRooms} 开始跨房间转发媒体流。
     */
    /**
     * @locale en
     * @type api
     * @region Room Management
     * @brief Create a room instance.<br>
     *        This API only returns a room instance. You still need to call joinRoom{@link #IRTCRoom#joinRoom} to actually create/join the room.<br>
     *        Each call of this API creates one IRTCRoom{@link #IRTCRoom} instance. Call this API as many times as the number of rooms you need, and then call joinRoom{@link #IRTCRoom#joinRoom} of each IRTCRoom instance to join multiple rooms at the same time.<br>
     *        In multi-room mode, a user can subscribe to media streams in the joined rooms at the same time.
     * @param room_id The string matches the regular expression: `[a-zA-Z0-9_@\-\.]{1,128}`.
     * @return IRTCRoom{@link #IRTCRoom} instance.
     * @note 
     *       + If the room that you wish to join already exists, you still need to call this API first to create the IRTCRoom instance, and then call joinRoom{@link #IRTCRoom#joinRoom}.<br>
     *       + Do not create multiple rooms with the same roomId, otherwise the newly created room instance will replace the old one.<br>
     *       + To forward streams to the other rooms, call startForwardStreamToRooms{@link #IRTCRoom#startForwardStreamToRooms} instead of enabling Multi-room mode.
     */
    virtual IRTCRoom* createRTCRoom(const char* room_id) = 0;

    /**
     * @locale zh
     * @type api
     * @region 音视频回退
     * @brief 设置发布的音视频流的回退选项。  <br>
     *        你可以调用该接口设置网络不佳或设备性能不足时从大流起进行降级处理，以保证通话质量。
     * @param option 本地发布的音视频流回退选项，参看 PublishFallbackOption{@link #PublishFallbackOption}。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note  
     *        + 该方法仅在调用 enableSimulcastMode{@link #IRTCVideo#enableSimulcastMode} 开启了发送多路视频流的情况下生效。  <br>
     *        + 该方法必须在进房前设置，进房后设置或更改设置无效。  <br>
     *        + 调用该方法后，如因性能或网络不佳产生发布性能回退或恢复，本端会提前收到 onPerformanceAlarms{@link #IRTCVideoEventHandler#onPerformanceAlarms} 回调发出的告警，以便采集设备配合调整。<br>
     *        + 设置回退后，本地发布的音视频流发生回退或从回退中恢复后，远端会收到 onSimulcastSubscribeFallback{@link #IRTCVideoEventHandler#onSimulcastSubscribeFallback} 回调，通知该情况。  <br>
     *        + 你可以调用客户端 API 或者在服务端下发策略设置回退。当使用服务端下发配置实现时，下发配置优先级高于在客户端使用 API 设定的配置。
     */
    /**
     * @locale en
     * @type api
     * @region Audio & Video Fallback
     * @brief Sets the fallback option for published audio & video streams.   <br>
     *        You can call this API to set whether to automatically lower the resolution you set of the published streams under limited network conditions.
     * @param option Fallback option, see PublishFallbackOption{@link #PublishFallbackOption}.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note  
     *         + This API only works after you call enableSimulcastMode{@link #IRTCVideo#enableSimulcastMode} to enable the mode of publishing multiple streams. <br>
     *         + You must call this API before entering the room.  <br>
     *         + After calling this method, if there is a performance degradation or recovery due to poor performance or network conditions, the local end will receive early warnings through the onPerformanceAlarms{@link #IRTCVideoEventHandler#onPerformanceAlarms} callback to adjust the capture device. <br>
     *         + After you allow video stream to fallback, your stream subscribers will receive onSimulcastSubscribeFallback{@link #IRTCVideoEventHandler#onSimulcastSubscribeFallback} when the resolution of your published stream are lowered or restored.  <br>
     *         + You can alternatively set fallback options with distrubutions from server side, which is of higher priority.
     */
    virtual int setPublishFallbackOption(PublishFallbackOption option) = 0;
    /**
     * @locale zh
     * @type api
     * @region 音视频回退
     * @brief 设置订阅的音视频流的回退选项。 <br>
     *        你可调用该接口设置网络不佳或设备性能不足时允许订阅流进行降级或只订阅音频流，以保证通话流畅。
     * @param option 订阅的音视频流回退选项，参看 SubscribeFallbackOption{@link #SubscribeFallbackOption}。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note  
     *        + 你必须在进房前设置，进房后设置或更改设置无效。  <br>
     *        + 设置回退选项后，订阅的音视频流发生回退或从回退中恢复时，会收到 onSimulcastSubscribeFallback{@link #IRTCVideoEventHandler#onSimulcastSubscribeFallback} 和 onRemoteVideoSizeChanged{@link #IRTCVideoEventHandler#onRemoteVideoSizeChanged} 回调通知。  <br>
     *        + 你可以调用 API 或者在服务端下发策略设置回退。当使用服务端下发配置实现时，下发配置优先级高于在客户端使用 API 设定的配置。
     */
    /**
     * @locale en
     * @type api
     * @region Audio & Video Fallback
     * @brief Sets the fallback option for subscribed RTC streams.   <br>
     *        You can call this API to set whether to lower the resolution of currently subscribed stream under limited network conditions.
     * @param option Fallback option, see SubscribeFallbackOption{@link #SubscribeFallbackOption} for more details.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note  
     *         + You must call this API before enterting the room.  <br>
     *         + After you enables the fallback, you will receive onSimulcastSubscribeFallback{@link #IRTCVideoEventHandler#onSimulcastSubscribeFallback} and onRemoteVideoSizeChanged{@link #IRTCVideoEventHandler#onRemoteVideoSizeChanged} when the resolution of your subscribed stream is lowered or restored.  <br>
     *         + You can alternatively set fallback options with distrubutions from server side, which is of higher priority.
     */
    virtual int setSubscribeFallbackOption(SubscribeFallbackOption option) = 0;

    /**
     * @locale zh
     * @type api
     * @region 音视频回退
     * @brief 设置用户优先级。
     * @param room_id 房间 ID
     * @param user_id 远端用户的 ID
     * @param priority 远端用户的需求优先级，详见枚举类型RemoteUserPriority{@link #RemoteUserPriority}
     * @return 0: 方法调用成功  <br>
     *        + < 0: 方法调用失败  
     * @note  
     *        + 1. 该方法与 setSubscribeFallbackOption{@link #IRTCVideo#setSubscribeFallbackOption} 搭配使用。  <br>
     *        + 2. 如果开启了订阅流回退选项，弱网或性能不足时会优先保证收到的高优先级用户的流的质量。  <br>
     *        + 3. 该方法在进房前后都可以使用，可以修改远端用户的优先级。  
     */
    /**
     * @locale en
     * @type api
     * @region  audio & video fallback
     * @brief  Set user priority
     * @param room_id Room ID
     * @param user_id Remote user's ID
     * @param priority Remote user's requirement priority. See enumeration type RemoteUserPriority{@link #RemoteUserPriority}
     * @return 0:  Success. <br>
     *         + < 0: failure 
     * @note   
     *         + 1. This method is used with setSubscribeFallbackOption{@link #IRTCVideo#setSubscribeFallbackOption}. <br>
     *         + 2. If the subscription flow fallback option is turned on, weak connections or insufficient performance will give priority to ensuring the quality of the flow received by high-priority users. <br>
     *         + 3. This method can be used before and after entering the room, and the priority of the remote user can be modified. 
     */
    virtual int setRemoteUserPriority(const char* room_id, const char* user_id, RemoteUserPriority priority) = 0;

    /**
     * @locale zh
     * @type api
     * @region 引擎管理
     * @brief 设置业务标识参数  <br>
     *        可通过 businessId 区分不同的业务场景。businessId 由客户自定义，相当于一个“标签”，可以分担和细化现在 AppId 的逻辑划分的功能，但不需要鉴权。
     * @param business_id  <br>
     *        用户设置的自己的 businessId 值<br>
     *        businessId 只是一个标签，颗粒度需要用户自定义。
     * @return  
     *        + 0： 成功  <br>
     *        + < 0： 失败，具体原因参照 BusinessCheckCode{@link #BusinessCheckCode} 。  <br>
     *        + -6001： 用户已经在房间中。  <br>
     *        + -6002： 输入非法，合法字符包括所有小写字母、大写字母和数字，除此外还包括四个独立字符，分别是：英文句号，短横线，下划线和 @ 。
     * @note  
     *        + 需要在调用 joinRoom{@link #IRTCRoom#joinRoom} 之前调用，joinRoom{@link #IRTCRoom#joinRoom}之后调用该方法无效。
     * @list 引擎管理
     * @order 20
     */
    /**
     * @locale en
     * @type api
     * @region Engine management
     * @brief  Sets the business ID   <br>
     *         You can use businessId to distinguish different business scenarios. You can customize your businessId to serve as a sub AppId, which can share and refine the function of the AppId, but it does not need authentication.
     * @param business_id <br>
     *         Your customized businessId<br>
     *         BusinessId is a tag, and you can customize its granularity.
     * @return   
     *         + 0: Success <br>
     *         + < 0: Failure. See BusinessCheckCode{@link #BusinessCheckCode} for specific reasons. <br>
     *         + -6001: The user is already in the room. <br>
     *         + -6002: The input is invalid. Legal characters include all lowercase letters, uppercase letters, numbers, and four other symbols, including '.', '-','_', and '@'.
     * @note   
     *         + You must call this API before the joinRoom{@link #IRTCRoom#joinRoom} API, otherwise it will be invalid.
     * @list Engine Management
     * @order 20
     */
    virtual int setBusinessId(const char* business_id) = 0;

    /**
     * @locale zh
     * @type api
     * @hidden(Windows,macOS,Linux)
     * @brief 设置采集视频的旋转模式。默认以 App 方向为旋转参考系。<br>
     *        接收端渲染视频时，将按照和发送端相同的方式进行旋转。
     * @param rotation_mode 视频旋转参考系为 App 方向或重力方向，参看  VideoRotationMode{@link #VideoRotationMode}
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note 
     *        + 旋转仅对内部视频采集生效，不适用于外部视频源和屏幕源。<br>
     *        + 调用该接口时已开启视频采集，将立即生效；调用该接口时未开启视频采集，则将在采集开启后生效。<br>
     *        + 更多信息请参考[视频采集方向](https://www.volcengine.com/docs/6348/106458)。
     */
    /**
     * @locale en
     * @type api
     * @hidden(Windows,macOS,Linux)
     * @brief Set the orientation of the video capture. By default, the App direction is used as the orientation reference.<br>
     *        During rendering, the receiving client rotates the video in the same way as the sending client did.
     * @param rotation_mode Rotation reference can be the orientation of the App or gravity. Refer to VideoRotationMode{@link #VideoRotationMode} for details.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note 
     *        + The orientation setting is effective for internal video capture only. That is, the orientation setting is not effective to the custom video source or the screen-sharing stream.<br>
     *        + If the video capture is on, the setting will be effective once you call this API. If the video capture is off, the setting will be effective on when capture starts.
     */
    virtual int setVideoRotationMode(VideoRotationMode rotation_mode) = 0;

    /**
     * @locale zh
     * @hidden(Linux)
     * @type api
     * @region 视频管理
     * @brief 为采集到的视频流开启镜像
     * @param mirror_type 镜像类型，参看 MirrorType{@link #MirrorType}
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note 
     *        + 切换视频源不影响镜像设置。<br>
     *        + 屏幕视频流始终不受镜像设置影响。<br>
     *        + 使用外部渲染器时，`mirrorType` 支持设置为 `0`（无镜像）和 `3`（本地预览和编码传输镜像），不支持设置为 `1`（本地预览镜像）。<br>
     *        + 该接口调用前，各视频源的初始状态如下：<br>
     *        <table>
     *           <tr><th></th><th>前置摄像头</th><th>后置摄像头</th><th>自定义采集视频源</th> <th>桌面端摄像头</th> </tr>
     *           <tr><td>移动端</td><td>本地预览镜像，编码传输不镜像</td><td> 本地预览不镜像，编码传输不镜像 </td><td> 本地预览不镜像，编码传输不镜像 </td><td>/</td></tr>
     *           <tr><td>桌面端</td><td>/</td><td>/</td><td> 本地预览不镜像，编码传输不镜像 </td><td> 本地预览镜像，编码传输不镜像 </td></tr> 
     *        </table>
     */
    /**
     * @locale en
     * @hidden(Linux)
     * @type api
     * @region Video management
     * @brief Sets the mirror mode for the captured video stream.
     * @param mirror_type Mirror type. See MirrorType{@link #MirrorType}.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note 
     *        + Switching video streams does not affect the settings of the mirror type. <br>
     *        + This API is not applicable to screen-sharing streams. <br>
     *        + When using an external renderer, you can set `mirrorType` to `0` and `3`, but you cannot set it to `1`. <br>
     *        + Before you call this API, the initial states of each video stream are as follows: <br>
     *        <table>
     *           <tr><th></th><th>Front-facing camera</th><th>Back-facing camera</th><th>Custom capturing</th><th>Built-in camera</th></tr>
     *           <tr><td>Mobile device</td><td>The preview is mirrored. The published video stream is not mirrored.</td><td>The preview and the published video stream are not mirrored.</td><td>The preview and the published video stream are not mirrored.</td><td>/</td></tr>
     *           <tr><td>PC</td><td>/</td><td>/</td><td>The preview and the published video stream are not mirrored.</td><td>The preview is mirrored. The published video stream is not mirrored.</td></tr>
     *        </table>
     */
    virtual int setLocalVideoMirrorType(MirrorType mirror_type) = 0;

    /**
     * @locale zh
     * @type api
     * @valid since 3.57
     * @region 视频管理
     * @brief 使用内部渲染时，为远端流开启镜像。
     * @param stream_key 远端流信息，用于指定需要镜像的视频流来源及属性，参看 RemoteStreamKey{@link #RemoteStreamKey}。
     * @param mirror_type 远端流的镜像类型，参看 RemoteMirrorType{@link #RemoteMirrorType}。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0: 调用失败，参看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明。
     */
    virtual int setRemoteVideoMirrorType(RemoteStreamKey stream_key, RemoteMirrorType mirror_type) = 0;

    /**
     * @locale zh
     * @type api
     * @region 音视频处理
     * @brief 获取视频特效接口。
     * @return 视频特效接口，参看 IVideoEffect{@link #IVideoEffect}。
     */
    /**
     * @locale en
     * @type api
     * @region Audio & Video Processing
     * @brief Gets video effect interfaces.
     * @return Video effect interfaces. See IVideoEffect{@link #IVideoEffect}.
     */
    virtual IVideoEffect* getVideoEffectInterface() = 0;

    /**
     * @locale zh
     * @hidden(Linux)
     * @type api
     * @region 音视频处理
     * @brief 开启/关闭基础美颜。
     * @param enable 基础美颜开关 <br>
     *        + true: 开启基础美颜 <br>
     *        + false: 关闭基础美颜（默认） 
     * @return  
     *        + 0: 调用成功。<br>
     *        + –1000: 未集成特效 SDK。<br>
     *        + –1001: RTC SDK 版本不支持此功能。<br>
     *        + –1002: 特效 SDK 当前版本不支持此功能，建议使用特效 SDK v4.4.2+ 版本。<br>
     *        + –1003: 联系技术支持人员。<br>
     *        + –1004: 正在下载相关资源，下载完成后生效。<br>
     *        + <0: 调用失败，特效 SDK 内部错误，具体错误码请参考[错误码表](https://www.volcengine.com/docs/6705/102042)。
     * @note 
     *        + 本方法不能与高级视频特效接口共用。如已购买高级视频特效，建议参看[集成指南](https://www.volcengine.com/docs/6348/114717)使用高级美颜、特效、贴纸功能等。<br>
     *        + 使用此功能需要集成特效 SDK，建议使用特效 SDK v4.4.2+ 版本。更多信息参看 [Native 端基础美颜](https://www.volcengine.com/docs/6348/372605)。<br>
     *        + 调用 setBeautyIntensity{@link #IRTCVideo#setBeautyIntensity} 设置基础美颜强度。若在调用本方法前没有设置美颜强度，则使用默认强度。各基础美颜模式的强度默认值分别为：美白 0.7，磨皮 0.8，锐化 0.5，清晰 0.7。<br>
     *        + 本方法仅适用于视频源，不适用于屏幕源。
     */
    /**
     * @locale en
     * @hidden(Linux)
     * @type api
     * @region Audio & Video Processing
     * @brief Enables/Disables basic beauty effects.
     * @param enable Whether to enable basic beauty effects. <br>
     *        + true: Enables basic beauty effects. <br>
     *        + false: (Default) Disables basic beauty effects. 
     * @return  
     *        + 0: Success.<br>
     *        + –1000: The Effect SDK is not integrated.<br>
     *        + –1001: This API is not available for your current RTC SDK.<br>
     *        + –1002: This API is not available for your current Effect SDK. You can upgrade your Effect SDK to v4.4.2+.<br>
     *        + –1003: Contact our technical support team for further instructions.<br>
     *        + –1004: Downloading related resources. The beauty effects will take effect after downloading.<br>
     *        + <0: Failure. Effect SDK internal error. For specific error code, see [Error Code Table](https://docs.byteplus.com/effects/docs/error-code-table).
     * @note 
     *        + You cannot use the basic beauty effects and the advanced effect features at the same time. See [how to use advanced effect features](https://docs.byteplus.com/byteplus-rtc/docs/114717) for more information.<br>
     *        + You need to integrate Effect SDK before calling this API. Effect SDK v4.4.2+ is recommended.<br>
     *        + Call setBeautyIntensity{@link #IRTCVideo#setBeautyIntensity} to set the beauty effect intensity. If you do not set the intensity before calling this API, the default intensity will be enabled. The default values for the intensity of each beauty mode are as follows: 0.7 for brightning, 0.8 for smoothing, 0.5 for sharpening, and 0.7 for clarity.<br>
     *        + This API is not applicable to screen capturing.
     */
    virtual int enableEffectBeauty(bool enable) = 0;

    /**
     * @locale zh
     * @hidden(Linux)
     * @type api
     * @region 音视频处理
     * @brief 调整基础美颜强度。
     * @param beauty_mode 基础美颜模式，参看 EffectBeautyMode{@link #EffectBeautyMode}。
     * @param intensity 美颜强度，取值范围为 [0,1]。强度为 0 表示关闭。<br>
     *                       各基础美颜模式的强度默认值分别为：美白 0.7，磨皮 0.8，锐化 0.5，清晰 0.7。
     * @return  
     *        + 0: 调用成功。<br>
     *        + –1000: 未集成特效 SDK。<br>
     *        + –1001: RTC SDK 版本不支持此功能。<br>
     *        + <0: 调用失败，特效 SDK 内部错误，具体错误码请参考[错误码表](https://www.volcengine.com/docs/6705/102042)。
     * @note 
     *        + 若在调用 enableEffectBeauty{@link #IRTCVideo#enableEffectBeauty} 前设置美颜强度，则对应美颜功能的强度初始值会根据设置更新。 <br>
     *        + 销毁引擎后，美颜功能强度恢复默认值。
     */
    /**
     * @locale en
     * @hidden(Linux)
     * @type api
     * @region Audio & Video Processing
     * @brief Sets the beauty effect intensity.
     * @param beauty_mode Basic beauty effect. See EffectBeautyMode{@link #EffectBeautyMode}.
     * @param intensity Beauty effect intensity in range of [0,1]. When you set it to 0, the beauty effect will be turned off.<br>
     *                       The default values for the intensity of each beauty mode are as follows: 0.7 for brightning, 0.8 for smoothing, 0.5 for sharpening, and 0.7 for clarity.
     * @return  
     *        + 0: Success.<br>
     *        + –1000: The Effect SDK is not integrated.<br>
     *        + –1001: This API is not available for your current RTC SDK.<br>
     *        + <0: Failure. Effect SDK internal error. For specific error code, see [error codes](https://docs.byteplus.com/effects/docs/error-code-table).
     * @note 
     *        + If you call this API before calling enableEffectBeauty{@link #IRTCVideo#enableEffectBeauty}, the default settings of beauty effect intensity will adjust accordingly. <br>
     *        + If you destroy the engine, the beauty effect settings will be invalid.
     */
    virtual int setBeautyIntensity(EffectBeautyMode beauty_mode, float intensity) = 0;

    /**
     * @locale zh
     * @valid since 3.54
     * @hidden(Windows, macOS, Linux)
     * @type api
     * @region 音视频处理
     * @brief 设置远端视频超分模式。
     * @param stream_key 远端流信息，用于指定需要设置超分的视频流来源及属性，参看 RemoteStreamKey{@link #RemoteStreamKey}。
     * @param mode 超分模式，参看 VideoSuperResolutionMode{@link #VideoSuperResolutionMode}。
     * @return 
     *        + 0: kReturnStatusSuccess，SDK 调用成功，并不代表超分模式实际状态，需要根据回调 onRemoteVideoSuperResolutionModeChanged{@link #IRTCVideoEventHandler#onRemoteVideoSuperResolutionModeChanged} 判断实际状态。<br>
     *        + -1: kReturnStatusNativeInvalid，native library 未加载。<br>
     *        + -2: kReturnStatusParameterErr，参数非法，指针为空或字符串为空。<br>
     *        + -9: kReturnStatusScreenNotSupport，不支持对屏幕流开启超分。
     * @note 
     *        + 该方法须进房后调用。<br>
     *        + 远端用户视频流的原始分辨率不能超过 640 × 360 px。<br>
     *        + 支持对一路远端流开启超分，不支持对多路流开启超分。
     */
    /**
     * @locale en
     * @hidden not available
     * @type api
     * @region Audio & Video Processing
     * @brief Sets the super resolution mode for remote video stream.
     * @param stream_key Remote stream information that specifies the source and type of the video stream. See RemoteStreamKey{@link #RemoteStreamKey}.
     * @param mode Super resolution mode. See VideoSuperResolutionMode{@link #VideoSuperResolutionMode}.
     * @return. <br>
     *        + 0: kReturnStatusSuccess. It does not indicate the actual status of the super resolution mode, you should refer to onRemoteVideoSuperResolutionModeChanged{@link #IRTCVideoEventHandler#onRemoteVideoSuperResolutionModeChanged} callback.<br>
     *        + -1: kReturnStatusNativeInValid. Native library is not loaded.<br>
     *        + -2: kReturnStatusParameterErr. Invalid parameter.<br>
     *        + -9: kReturnStatusScreenNotSupport. Failure. Screen stream is not supported.<br>
     *        See ReturnStatus{@link #ReturnStatus} for more return value indications.
     * @note 
     *        + Call this API after joining room.<br>
     *        + The original resolution of the remote video stream should not exceed 640 × 360 pixels.<br>
     *        + You can only turn on super-resolution mode for one stream.
     */
    virtual int setRemoteVideoSuperResolution(RemoteStreamKey stream_key, VideoSuperResolutionMode mode) = 0;

    /**
     * @locale zh
     * @valid since 3.54
     * @hidden(Windows, macOS, Linux)
     * @type api
     * @region 音视频处理
     * @brief 设置视频降噪模式。
     * @param mode 视频降噪模式，启用后能够增强视频画质，但同时会增加性能负载。参看 VideoDenoiseMode{@link #VideoDenoiseMode}。
     * @return 
     *        + 0: API 调用成功。 用户可以根据回调函数 onVideoDenoiseModeChanged{@link #IRTCVideoEventHandler#onVideoDenoiseModeChanged} 判断视频降噪是否开启。<br>
     *        + < 0：API 调用失败。
     */
    /**
     * @locale en
     * @hidden not available
     * @type api
     * @region Audio & Video Processing
     * @brief Sets the video noise reduction mode.
     * @param mode Video noise reduction mode which helps enhance video quality but will increase CPU utilization.<br>
     * Refer to VideoDenoiseMode{@link #VideoDenoiseMode} for more details.
     * @return 
     *        + 0: Success. Please refer to onVideoDenoiseModeChanged{@link #IRTCVideoEventHandler#onVideoDenoiseModeChanged} callback for the actual state of video noise reduction mode.<br>
     *        + < 0：Failure.
     */
    virtual int setVideoDenoiser(VideoDenoiseMode mode) = 0;

    /**
     * @locale zh
     * @hidden(Windows, Linux, macOS)
     * @type api
     * @region 自定义流处理
     * @brief 在自定义视频前处理及编码前，设置 RTC 链路中的视频帧朝向，默认为 Adaptive 模式。<br>
     *        移动端开启视频特效贴纸，或使用自定义视频前处理时，建议固定视频帧朝向为 Portrait 模式。单流转推场景下，建议根据业务需要固定视频帧朝向为 Portrait 或 Landscape 模式。不同模式的具体显示效果参看[视频帧朝向](https://www.volcengine.com/docs/6348/128787)。
     * @param orientation 视频帧朝向，参看 VideoOrientation{@link #VideoOrientation}。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note
     *        + 视频帧朝向设置仅适用于内部采集视频源。对于自定义采集视频源，设置视频帧朝向可能会导致错误，例如宽高对调。屏幕源不支持设置视频帧朝向。  <br>
     *        + 编码分辨率的更新与视频帧处理是异步操作，进房后切换视频帧朝向可能导致画面出现短暂的裁切异常，因此建议在进房前设置视频帧朝向，且不在进房后进行切换。
     */
    /**
     * @locale en
     * @hidden(Windows,Linux,macOS)
     * @type api
     * @region Audio & Video Processing
     * @brief Sets the orientation of the video frame before custom video processing and encoding. The default value is `Adaptive`.<br>
     *        You should set the orientation to `Portrait` when using video effects or custom processing.<br>
     *        You should set the orientation to `Portrait` or `Landscape` when pushing a single stream to the CDN.
     * @param orientation Orientation of the video frame. See VideoOrientation{@link #VideoOrientation}.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note 
     *        + The orientation setting is only applicable to internal captured video sources. For custom captured video sources, setting the video frame orientation may result in errors, such as swapping width and height. Screen sources do not support video frame orientation setting.  <br>
     *        + We recommend setting the orientation before joining room. The updates of encoding configurations and the orientation are asynchronous, therefore can cause a brief malfunction in preview if you change the orientation after joining room.
     */
    virtual int setVideoOrientation(VideoOrientation orientation) = 0;

    /**
     * @locale zh
     * @hidden(macOS, Windows,Linux)
     * @type api
     * @region 视频管理
     * @brief 获取相机控制接口
     * @return 相机控制接口指针，参看 ICameraControl{@link #ICameraControl}
     */
    /**
     * @locale en
     * @hidden(macOS, Windows,Linux)
     * @type api
     * @region  video management
     * @brief  Get camera control interface
     * @return  Camera control interface pointer, see ICameraControl{@link #ICameraControl}.
     */
    virtual ICameraControl* getCameraControl() = 0;

    /**
     * @locale zh
     * @type api
     * @region 加密
     * @brief 设置传输时使用内置加密的方式。
     * @param encrypt_type 内置加密算法，详见 EncryptType{@link #EncryptType}
     * @param encrypt_type 加密类型，详见 EncryptType{@link #EncryptType}
     * @param key 加密密钥，长度限制为 36 位，超出部分将会被截断
     * @param key_size 参数 key 的长度
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note  
     *       + 使用传输时内置加密时，使用此方法；如果需要使用传输时自定义加密，参看 onEncryptData{@link #IEncryptHandler#onEncryptData}。 内置加密和自定义加密互斥，根据最后一个调用的方法确定传输是加密的方案。  <br>
     *       + 该方法必须在进房之前调用，可重复调用，以最后调用的参数作为生效参数。  
     */
    /**
     * @locale en
     * @type api
     * @region Encryption
     * @brief Sets the way to use built-in encryption when transmitting.
     * @param encrypt_type Built-in encryption algorithm. See EncryptType{@link #EncryptType}
     * @param encrypt_type Encryption type. See EncryptType{@link #EncryptType}
     * @param key Encryption key, the length is limited to 36 bits, and the excess will be Truncate
     * @param key_size The length of the parameter key
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note   
     *        + Use this method when using the built-in encryption on transfer; if you need to use custom encryption on transfer. See onEncryptData {@link #IEncryptHandler#onEncryptData}. Built-in encryption and custom encryption are mutually exclusive, and the transmission is determined to be encrypted according to the last method called. <br>
     *        + This method must be called before entering the room, and can be called repeatedly, taking the last called parameter as the effective parameter. 
     */
    virtual int setEncryptInfo(EncryptType encrypt_type, const char* key, int key_size) = 0;

    /**
     * @locale zh
     * @type api
     * @region 加密
     * @brief 设置自定义加密和解密方式。
     * @param handler 自定义加密 handler，需要实现 handler 的加密和解密方法。参看 IEncryptHandler{@link #IEncryptHandler}。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note  
     *       + 该方法与 setEncryptInfo{@link #IRTCVideo#setEncryptInfo} 为互斥关系，只能选择自定义加密方式或者默认加密方式。最终生效的加密方式取决于最后一个调用的方法。  <br>
     *       + 该方法必须在进房之前调用，可重复调用，以最后调用的参数作为生效参数。  <br>
     *       + 无论加密或者解密，其对原始数据的长度修改，需要控制在 180% 之间，即如果输入数据为 100 字节，则处理完成后的数据必须不超过 180 字节，如果加密或解密结果超出该长度限制，则该音视频帧可能会被丢弃。  <br>
     *       + 数据加密/解密为串行执行，因而视实现方式不同，可能会影响到最终渲染效率。是否使用该方法，需要由使用方谨慎评估。<br>
     * 
     */
    /**
     * @locale en
     * @type api
     * @region Encryption
     * @brief Sets custom encryption and decryption methods.
     * @param handler Custom encryption handler, you need to implement the handler's encryption and decryption method. See IEncryptHandler{@link #IEncryptHandler}. 
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note   
     *        + This method is mutually exclusive with setEncryptInfo{@link #IRTCVideo#setEncryptInfo}, you can only select custom encryption method or default encryption method. The encryption method that takes effect depends on the last method called. <br>
     *        + This method must be called before entering the room, and can be called repeatedly, taking the last called parameter as the effective parameter. <br>
     *        + Whether encrypted or decrypted, the length of the modified data needs to be controlled under 180%. That is, if the input data is 100 bytes, the processed data must be less than 180 bytes. If the encryption or decryption result exceeds the limit, the audio & video frame may be discarded. <br>
     *        + Data encryption/decryption is performed serially, so depending on the implementation, it may affect the final rendering efficiency. Whether to use this method needs to be carefully evaluated by users.
     */
    virtual int setCustomizeEncryptHandler(IEncryptHandler* handler) = 0;

    /**
     * @locale zh
     * @type api
     * @region 音频数据回调
     * @brief 设置并开启指定的音频数据帧回调
     * @param method 音频回调方法，参看 AudioFrameCallbackMethod{@link #AudioFrameCallbackMethod}。  <br>
     *               当音频回调方法设置为 `kRecord`、`kPlayback`、`kMixed`、`kRecordScreen`时，你需要在参数 `format` 中指定准确的采样率和声道，暂不支持设置为自动。  <br>
     *               当音频回调方法设置为 `kRemoteUser`时，暂不支持音频参数格式中设置准确的采样率和声道，你需要设置为自动。
     * @param format 音频参数格式，参看 AudioFormat{@link #AudioFormat}。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note 开启音频回调并调用 registerAudioFrameObserver{@link #IRTCVideo#registerAudioFrameObserver} 后，IAudioFrameObserver{@link #IAudioFrameObserver} 会收到对应的音频回调。两者调用顺序没有限制且相互独立。  
     */
    /**
     * @locale en
     * @type api
     * @region Audio Data Callback
     * @brief Enable audio frames callback and set the format for the specified type of audio frames.
     * @param method Audio data callback method. See AudioFrameCallbackMethod{@link #AudioFrameCallbackMethod}. <br>
     *               If `method` is set as `kRecord`, `kPlayback`, `kMixed`, `kRecordScreen`, set `format` to the accurate value listed in the audio parameters format.<br>
     *               If `method` is set as `kRemoteUser`, set `format` to `auto`.
     * @param format Audio parameters format. See AudioFormat{@link #AudioFormat}.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note After calling this API and registerAudioFrameObserver{@link #IRTCVideo#registerAudioFrameObserver}, IAudioFrameObserver{@link #IAudioFrameObserver} will receive the corresponding audio data callback. However, these two APIs are independent of each other and the calling order is not restricted. 
     */
    virtual int enableAudioFrameCallback(AudioFrameCallbackMethod method, AudioFormat format) = 0;

    /**
     * @locale zh
     * @type api
     * @region 音频数据回调
     * @brief 关闭音频回调
     * @param method 音频回调方法，参看 AudioFrameCallbackMethod{@link #AudioFrameCallbackMethod}。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note 该方法需要在调用 enableAudioFrameCallback{@link #IRTCVideo#enableAudioFrameCallback} 之后调用。
     */
    /**
     * @locale en
     * @type api
     * @region Audio Data Callback
     * @brief Disables audio data callback.
     * @param method Audio data callback method. See AudioFrameCallbackMethod{@link #AudioFrameCallbackMethod}.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note Call this API after calling enableAudioFrameCallback{@link #IRTCVideo#enableAudioFrameCallback}.
     */
    virtual int disableAudioFrameCallback(AudioFrameCallbackMethod method) = 0;

    /**
     * @locale zh
     * @type api
     * @region 音频数据回调
     * @brief 注册音频数据回调观察者。  
     * @param observer 音频数据观察者，参看 IAudioFrameObserver{@link #IAudioFrameObserver}。如果传入 null，则取消注册。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note 注册音频数据回调观察者并调用 enableAudioFrameCallback{@link #IRTCVideo#enableAudioFrameCallback} 后，IAudioFrameObserver{@link #IAudioFrameObserver} 会收到对应的音频回调。对回调中收到的音频数据进行处理，不会影响 RTC 的编码发送或渲染。
     */
    /**
     * @locale en
     * @type api
     * @region Audio Data Callback
     * @brief Register an audio frame observer.  
     * @param observer Audio data callback observer. See IAudioFrameObserver{@link #IAudioFrameObserver}. Use `null` to cancel the registration.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note After calling this API and enableAudioFrameCallback{@link #IRTCVideo#enableAudioFrameCallback}, IAudioFrameObserver{@link #IAudioFrameObserver} receives the corresponding audio data callback. You can retrieve the audio data and perform processing on it without affecting the audio that RTC SDK uses to encode or render.
     */
    virtual int registerAudioFrameObserver(IAudioFrameObserver* observer) = 0;

    /**
     * @locale zh
     * @type api
     * @brief 注册自定义音频处理器。<br>
     *        注册完成后，你可以调用 enableAudioProcessor{@link #IRTCVideo#enableAudioProcessor}，对本地采集到的音频进行处理，RTC SDK 将对处理后的音频进行编码和发送。也可以对接收到的远端音频进行自定义处理，RTC SDK 将对处理后的音频进行渲染。
     * @param processor 自定义音频处理器，详见 IAudioFrameProcessor{@link #IAudioFrameProcessor}。<br>
     *        SDK 只持有 processor 的弱引用，你应保证其生命周期。需要取消注册时，设置此参数为 nullptr。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note
     * + 重复调用此接口时，仅最后一次调用生效。<br>
     * + 更多相关信息，详见[音频自定义处理](https://www.volcengine.com/docs/6348/80635)。
     */
    /**
     * @locale en
     * @type api
     * @brief Register a custom audio preprocessor. <br>
     *        After that, you can call enableAudioProcessor{@link #IRTCVideo#enableAudioProcessor} to process the audio streams that either captured locally or received from the remote side. RTC SDK then encodes or renders the processed data.
     * @param processor Custom audio processor. See IAudioFrameProcessor{@link #IAudioFrameProcessor}。<br>
     *        SDK only holds weak references to the processor, you should guarantee its Life Time. To cancel registration, set the parameter to nullptr.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note 
     * + When this interface is repeatedly called, only the last call takes effect.<br>
     * + Refer to [Custom Audio Processing](https://docs.byteplus.com/en/byteplus-rtc/docs/80635) for more information.
     */
    virtual int registerAudioProcessor(IAudioFrameProcessor* processor) = 0;

    /**
     * @locale zh
     * @type api
     * @brief 设置并开启指定的音频帧回调，进行自定义处理。
     * @param method 音频帧类型，参看 AudioProcessorMethod{@link #AudioProcessorMethod}。可多次调用此接口，处理不同类型的音频帧。<br>
     *        选择不同类型的音频帧将收到对应的回调：  <br>
     *        + 选择本地采集的音频时，会收到 onProcessRecordAudioFrame{@link #IAudioFrameProcessor#onProcessRecordAudioFrame}。  <br>
     *        + 选择远端音频流的混音音频时，会收到 onProcessPlayBackAudioFrame{@link #IAudioFrameProcessor#onProcessPlayBackAudioFrame}。  <br>
     *        + 选择远端音频流时，会收到 onProcessRemoteUserAudioFrame{@link #IAudioFrameProcessor#onProcessRemoteUserAudioFrame}。  <br>
     *        + 选择屏幕共享音频流时，会收到 onProcessScreenAudioFrame{@link #IAudioFrameProcessor#onProcessScreenAudioFrame}。（Linux 不适用）
     * @param format 设定自定义处理时获取的音频帧格式，参看 AudioFormat{@link #AudioFormat}。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note 
     *        + 在调用此接口前，你需要调用 registerAudioProcessor{@link #IRTCVideo#registerAudioProcessor} 注册自定义音频处理器。<br>
     *        + 要关闭音频自定义处理，调用 disableAudioProcessor{@link #IRTCVideo#disableAudioProcessor}。
     */
    /**
     * @locale en
     * @type api
     * @brief Enable audio frames callback for custom processing and set the format for the specified type of audio frames.
     * @param method The types of audio frames. See AudioProcessorMethod{@link #AudioProcessorMethod}. Set this parameter to process multiple types of audio. <br>
     *        With different values, you will receive the corresponding callback: <br>
     *        + For locally captured audio, you will receive onProcessRecordAudioFrame{@link #IAudioFrameProcessor#onProcessRecordAudioFrame}. <br>
     *        + For mixed remote audio, you will receive onProcessPlayBackAudioFrame{@link #IAudioFrameProcessor#onProcessPlayBackAudioFrame}.  <br>
     *        + For audio from remote users, you will receive onProcessRemoteUserAudioFrame{@link #IAudioFrameProcessor#onProcessRemoteUserAudioFrame}.  <br>
     *        + For shared-screen audio, you will receive onProcessScreenAudioFrame{@link #IAudioFrameProcessor#onProcessScreenAudioFrame}. (Only on Windows)
     * @param format The format of audio frames. See AudioFormat{@link #AudioFormat}.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note 
     *        + Before calling this API, call registerAudioProcessor{@link #IRTCVideo#registerAudioProcessor} to register a processor. <br>
     *        + To disable custom audio processing, call disableAudioProcessor{@link #IRTCVideo#disableAudioProcessor}.
     */
    virtual int enableAudioProcessor(AudioProcessorMethod method, AudioFormat format) = 0;

    /**
     * @locale zh
     * @type api
     * @brief 关闭自定义音频处理。
     * @param method 音频帧类型，参看 AudioProcessorMethod{@link #AudioProcessorMethod}。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     */
    /**
     * @locale en
     * @type api
     * @brief Disable custom audio processing.
     * @param method Audio Frame type. See AudioProcessorMethod{@link #AudioProcessorMethod}.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     */
    virtual int disableAudioProcessor(AudioProcessorMethod method) = 0;

    /**
     * @locale zh
     * @hidden
     * @deprecated since 3.50 and will be deleted in 3.55, use setLocalVideoSink{@link #IRTCVideo#setLocalVideoSink} instead.
     * @type api
     * @region 视频数据回调
     * @brief 注册视频数据回调观察者
     * @param observer 数据回调函数，详见 IVideoFrameObserver{@link #IVideoFrameObserver}，将参数设置为 nullptr 则取消注册。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note 该方法可以在任意时间调用，建议在 joinRoom{@link #IRTCRoom#joinRoom} 前。
     */
    /**
     * @locale en
     * @hidden
     * @deprecated since 3.50 and will be deleted in 3.55, use setLocalVideoSink{@link #IRTCVideo#setLocalVideoSink} instead.
     * @type api
     * @region Video Data Callback
     * @brief Register a video data callback observer
     * @param observer Video data callback observer, see IVideoFrameObserver{@link #IVideoFrameObserver}. Cancel the registration by setting it to `null`.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note We recommended you call this API before calling joinRoom{@link #IRTCRoom#joinRoom}.
     */
    BYTERTC_DEPRECATED virtual int registerVideoFrameObserver(IVideoFrameObserver* observer) = 0;

    /**
     * @locale zh
     * @type api
     * @region 视频处理
     * @brief 设置自定义视频前处理器。<br>
     *        使用这个视频前处理器，你可以调用 processVideoFrame{@link #IVideoProcessor#processVideoFrame} 对 RTC SDK 采集得到的视频帧进行前处理，并将处理后的视频帧用于 RTC 音视频通信。
     * @param processor 自定义视频处理器，详见 IVideoProcessor{@link #IVideoProcessor}。如果传入 null，则不对 RTC SDK 采集得到的视频帧进行前处理。<br>
     *        SDK 只持有 processor 的弱引用，你应保证其生命周期。
     * @param config 自定义视频前处理器适用的设置，详见 VideoPreprocessorConfig{@link #VideoPreprocessorConfig}。<br>
     *               当前，`config` 中的 `required_pixel_format` 仅支持：`kVideoPixelFormatI420` 和 `kVideoPixelFormatUnknown`：<br>
     *               + 设置为 `kVideoPixelFormatUnknown` 时，RTC SDK 给出供 processor 处理的视频帧格式即采集的格式。<br>
     *                 你可以通过 VideoFrameType{@link #VideoFrameType} 和 VideoPixelFormat{@link #VideoPixelFormat} 获取实际采集的视频帧格式和像素类型。<br>
     *               + 设置为 `kVideoPixelFormatI420` 时，RTC SDK 会将采集得到的视频帧转变为对应的格式，供前处理使用。<br>
     *               + 设置为其他值时，此方法调用失败。
     * @return 
     *         + 0：方法调用成功 <br>
     *         + !0：方法调用失败 
     * @note  
     *        + 对于 Windows 平台，经前处理返回的视频帧格式仅支持 `kVideoPixelFormatI420` <br>
     *        + 对于 Windows 平台，将 `config` 中的 required_pixel_format 设置为 `kVideoPixelFormatI420`，可以通过避免格式转换带来一些性能优化。<br>
     *        + 重复调用此接口时，仅最后一次调用生效。效果不会叠加。
     */
    /**
     * @locale en
     * @type api
     * @region  Video Processing
     * @brief Set up a custom video preprocessor. <br>
     *        Using this video preprocessor, you can call processVideoFrame{@link #IVideoProcessor#processVideoFrame} to preprocess the video frames collected by the RTC SDK, and use the processed video frames for RTC audio & video communication.
     * @param processor Custom video processor. See IVideoProcessor{@link #IVideoProcessor}. If null is passed in, the video frames captured by the RTC SDK are not preprocessed. <br>
     *        SDK only holds weak references to the processor, you should guarantee its Life Time.
     * @param config Customize the settings applicable to the video pre-processor. See VideoPreprocessorConfig{@link #VideoPreprocessorConfig}. <br>
     *             Currently, the 'required_pixel_format 'in'config' only supports: 'kVideoPixelFormatI420' and'kVideoPixelFormatUnknown ': <br>
     *             + When set to'kVideoPixelFormatUnknown', the RTC SDK gives the format of the video frame for processing by the processor, that is, the format of the acquisition.<br>
     *               You can get the actual captured video frame format and pixel type by VideoFrameType{@link #VideoFrameType} and VideoPixelFormat{@link #VideoPixelFormat}. <br>
     *             + When set to'kVideoPixelFormatI420 ', the RTC SDK converts the captured video frames into the corresponding format for pre-processing. This method call fails when <br>
     *             + Is set to another value.
     * @return 
     *         + 0: Success. <br>
     *         +! 0: failure 
     * @note 
     *        + For Windows platforms, the preprocessed video frame format returned only supports'kVideoPixelFormatI420 '<br>
     *        + For Windows platforms, setting the required_pixel_format in'config' to'kVideoPixelFormatI420 'can bring some performance optimization by avoiding format conversion. <br>
     *        + When this interface is repeatedly called, only the last call takes effect. The effects do not stack.
     */
    virtual int registerLocalVideoProcessor(IVideoProcessor* processor, VideoPreprocessorConfig config) = 0;
    /**
     * @locale zh
     * @type api
     * @valid since 3.51
     * @brief 设置本地摄像头数码变焦参数，包括缩放倍数，移动步长。
     * @param type 数码变焦参数类型，缩放系数或移动步长。参看 ZoomConfigType{@link #ZoomConfigType}。必填。
     * @param size 缩放系数或移动步长，保留到小数点后三位。默认值为 0。必填。<br>
     *                  选择不同 `type` 时有不同的取值范围。当计算后的结果超过缩放和移动边界时，取临界值。<br>
     *                  + `kZoomConfigTypeFocusOffset`：缩放系数增量，范围为 [0, 7]。例如，设置为 0.5 时，如果调用 setVideoDigitalZoomControl{@link #IRTCVideo#setVideoDigitalZoomControl} 选择 Zoom in，则缩放系数增加 0.5。缩放系数范围 [1，8]，默认为 `1`，原始大小。<br>
     *                  + `kZoomConfigTypeMoveOffset`：移动百分比，范围为 [0, 0.5]，默认为 0，不移动。如果调用 setVideoDigitalZoomControl{@link #IRTCVideo#setVideoDigitalZoomControl} 选择的是左右移动，则移动距离为 size x 原始视频宽度；如果选择的是上下移动，则移动距离为 size x 原始视频高度。例如，视频帧边长为 1080 px，设置为 0.5 时，实际移动距离为 0.5 x 1080 px = 540 px。
     * @return  
     *        + 0：成功。  <br>
     *        + !0：失败。  
     * @note
     *        + 每次调用本接口只能设置一种参数。如果缩放系数和移动步长都需要设置，分别调用本接口传入相应参数。<br>
     *        + 由于移动步长的默认值为 `0` ，在调用 setVideoDigitalZoomControl{@link #IRTCVideo#setVideoDigitalZoomControl} 或 startVideoDigitalZoomControl{@link #IRTCVideo#startVideoDigitalZoomControl} 进行数码变焦操作前，应先调用本接口。
     */
    /**
     * @locale en
     * @type api
     * @valid since 3.51
     * @brief Set the step size for each digital zooming control to the local videos.
     * @param type Required. Identifying which type the `size` is referring to. Refer to ZoomConfigType{@link #ZoomConfigType}. 
     * @param size Required. Reserved to three decimal places. It defaults to `0`. <br>
     *                  The meaning and range vary from different `type`s. If the scale or moving distance exceeds the range, the limit is taken as the result.<br>
     *                  + `kZoomConfigTypeFocusOffset`: Increasement or decrease to the scaling factor. Range: [0, 7]. For example, when it is set to 0.5 and setVideoDigitalZoomControl{@link #IRTCVideo#setVideoDigitalZoomControl} is called to zoom in, the scale will increase `0.5`. The scale ranges [1，8] and defaults to `1`, which means an original size.<br>
     *                  + `kZoomConfigTypeMoveOffset`：Ratio of the distance to the border of video images. It ranges [0, 0.5] and defaults to `0`, which means no offset. When you call setVideoDigitalZoomControl{@link #IRTCVideo#setVideoDigitalZoomControl} and choose `CAMERA_MOVE_LEFT`, the moving distance is size x original width. While for the `CAMERA_MOVE_UP`, the moving distance is size x original height. Suppose that a video spans 1080 px and the `size` is set to `0.5` so that the distance would be 0.5 x 1080 px = 540 px.
     * @return  
     *        + 0: Success. <br>
     *        + ! 0: Failure.
     * @note
     *        + Only one size can be set for a single call. You must call this API to pass values respectively if you intend to set multiple `size`s.<br>
     *        + As the default `size` is `0`, you must call this API before performing any digital zoom control by calling setVideoDigitalZoomControl{@link #IRTCVideo#setVideoDigitalZoomControl} or startVideoDigitalZoomControl{@link #IRTCVideo#startVideoDigitalZoomControl}.
     */
    virtual int setVideoDigitalZoomConfig(ZoomConfigType type, float size) = 0;

    /**
     * @locale zh
     * @type api
     * @valid since 3.51
     * @brief 控制本地摄像头数码变焦，缩放或移动一次。设置对本地预览画面和发布到远端的视频都生效。
     * @param direction 数码变焦操作类型，参看 ZoomDirectionType{@link #ZoomDirectionType}。
     * @return  
     *        + 0：成功。  <br>
     *        + !0：失败。  
     * @note
     *        + 由于默认步长为 `0`，调用该方法前需通过 setVideoDigitalZoomConfig{@link #IRTCVideo#setVideoDigitalZoomConfig} 设置参数。<br>
     *        + 调用该方法进行移动前，应先使用本方法或 startVideoDigitalZoomControl{@link #IRTCVideo#startVideoDigitalZoomControl} 进行放大，否则无法移动。<br>
     *        + 当数码变焦操作超出范围时，将置为临界值。例如，移动到了图片边界、放大到了 8 倍、缩小到原图大小。<br>
     *        + 如果你希望实现持续数码变焦操作，调用 startVideoDigitalZoomControl{@link #IRTCVideo#startVideoDigitalZoomControl}。
     *        + 移动端可对摄像头进行光学变焦控制，参看 `setCameraZoomRatio`。
     */
    /**
     * @locale en
     * @type api
     * @valid since 3.51
     * @brief Digital zoom or move the local video image once. This action affects both the video preview locally and the stream published.
     * @param direction Action of the digital zoom control. Refer to ZoomDirectionType{@link #ZoomDirectionType}.
     * @return  
     *        + 0: Success. <br>
     *        + ! 0: Failure.
     * @note
     *        + As the default offset is `0`, you must call setVideoDigitalZoomConfig{@link #IRTCVideo#setVideoDigitalZoomConfig} before this API.<br>
     *        + You can only move video images after they are magnified via this API or startVideoDigitalZoomControl{@link #IRTCVideo#startVideoDigitalZoomControl}.<br>
     *        + When you request an out-of-range scale or movement, SDK will execute it with the limits. For example, when the image has been moved to the border, the image cannot be zoomed out, or has been magnified to 8x.<br>
     *        + Call startVideoDigitalZoomControl{@link #IRTCVideo#startVideoDigitalZoomControl} to have a continuous and repeatedly digital zoom control.
     */
    virtual int setVideoDigitalZoomControl(ZoomDirectionType direction) = 0;

    /**
     * @locale zh
     * @type api
     * @valid since 3.51
     * @brief 开启本地摄像头持续数码变焦，缩放或移动。设置对本地预览画面和发布到远端的视频都生效。
     * @param direction 数码变焦操作类型，参看 ZoomDirectionType{@link #ZoomDirectionType}。
     * @return  
     *        + 0：成功。  <br>
     *        + !0：失败。  
     * @note 
     *        + 由于默认步长为 `0`，调用该方法前需通过 setVideoDigitalZoomConfig{@link #IRTCVideo#setVideoDigitalZoomConfig} 设置参数。<br>
     *        + 调用该方法进行移动前，应先使用本方法或 setVideoDigitalZoomControl{@link #IRTCVideo#setVideoDigitalZoomControl} 进行放大，否则无法移动。<br>
     *        + 当数码变焦操作超出范围时，将置为临界值并停止操作。例如，移动到了图片边界、放大到了 8 倍、缩小到原图大小。<br>
     *        + 你也可以调用 stopVideoDigitalZoomControl{@link #IRTCVideo#stopVideoDigitalZoomControl} 手动停止控制。<br>
     *        + 如果你希望实现单次数码变焦操作，调用 setVideoDigitalZoomControl{@link #IRTCVideo#setVideoDigitalZoomControl}。
     *        + 移动端可对摄像头进行光学变焦控制，参看 `setCameraZoomRatio`。
     */
    /**
     * @locale en
     * @type api
     * @valid since 3.51
     * @brief Continuous and repeatedly digital zoom control. This action effect both the video preview locally and the stream published.
     * @param direction Action of the digital zoom control. Refer to ZoomDirectionType{@link #ZoomDirectionType}.
     * @return  
     *        + 0: Success. <br>
     *        + ! 0: Failure.
     * @note 
     *        + As the default offset is `0`, you must call setVideoDigitalZoomConfig{@link #IRTCVideo#setVideoDigitalZoomConfig} before this API.<br>
     *        + You can only move video images after they are magnified via this API or setVideoDigitalZoomControl{@link #IRTCVideo#setVideoDigitalZoomControl}.<br>
     *        + The control process stops when the scale reaches the limit, or the images have been moved to the border. if the next action exceeds the scale or movement range, SDK will execute it with the limits. <br>
     *        + Call stopVideoDigitalZoomControl{@link #IRTCVideo#stopVideoDigitalZoomControl} to stop the ongoing zoom control.<br>
     *        + Call setVideoDigitalZoomControl{@link #IRTCVideo#setVideoDigitalZoomControl} to have a one-time digital zoom control.
     */
    virtual int startVideoDigitalZoomControl(ZoomDirectionType direction) = 0;

    /**
     * @locale zh
     * @type api
     * @valid since 3.51
     * @brief 停止本地摄像头持续数码变焦。
     * @return  
     *        + 0：成功。  <br>
     *        + !0：失败。  
     * @note 关于开始数码变焦，参看 startVideoDigitalZoomControl{@link #IRTCVideo#startVideoDigitalZoomControl}。
     */
    /**
     * @locale en
     * @type api
     * @valid since 3.51
     * @brief Stop the ongoing digital zoom control instantly. 
     * @return  
     *        + 0: Success. <br>
     *        + ! 0: Failure.
     * @note Refer to startVideoDigitalZoomControl{@link #IRTCVideo#startVideoDigitalZoomControl} for starting digital zooming.
     */
    virtual int stopVideoDigitalZoomControl() = 0;

    /**
     * @locale zh
     * @hidden
     * @deprecated since 3.37 and will be deleted in 3.51, use registerAudioFrameObserver{@link #IRTCVideo#registerAudioFrameObserver} instead.
     * @type api
     * @region 音频数据回调
     * @brief 注册音频数据回调观察者。
     * @param observer 音频数据回调观察者，详见 IRemoteAudioFrameObserver{@link #IRemoteAudioFrameObserver}
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note  注册该回调，可以收到单个远端用户的 PCM 数据。
     */
    /**
     * @locale en
     * @deprecated since 3.45 and will be deleted in 3.51, use registerAudioFrameObserver{@link #IRTCVideo#registerAudioFrameObserver} instead.
     * @type api
     * @region audio data callback
     * @brief Register an audio data callback observer.
     * @param observer Audio data callback observer. See IRemoteAudioFrameObserver{@link #IRemoteAudioFrameObserver}
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note Register the callback to receive PCM data from a single remote user.
     */
    BYTERTC_DEPRECATED virtual int registerRemoteAudioFrameObserver(IRemoteAudioFrameObserver* observer) = 0;

    /**
     * @locale zh
     * @deprecated since 3.50 and will be deleted in 3.55, use [sendSEIMessage](#IRTCVideo-sendseimessage-2) instead.
     * @type api
     * @region 消息
     * @brief <span id="IRTCVideo-sendseimessage-1"></span> 通过视频帧发送 SEI 数据。  <br>
     *        在视频通话场景下，SEI 数据会随视频帧发送；在语音通话场景下，SDK 会自动生成一路 16px × 16px 的黑帧视频流用来发送 SEI 数据。
     * @param stream_index 指定携带 SEI 数据的媒体流类型，参看 StreamIndex{@link #StreamIndex}。  <br>
     *        语音通话场景下，该值需设为 `kStreamIndexMain`，否则 SEI 数据会被丢弃从而无法送达远端。
     * @param message SEI 消息。
     * @param length SEI 消息长度，不超过 4KB。
     * @param repeat_count 消息发送重复次数。取值范围是 [0, 30]。<br>
     *                    调用此接口后，SEI 数据会添加到从当前视频帧开始的连续 `repeat_count+1` 个视频帧中。
     * @return 
     *        + >=0: 将被添加到视频帧中的 SEI 的数量  <br>
     *        + <0: 发送失败
     * @note 
     *        + 语音通话场景中，仅支持在内部采集模式下调用该接口发送 SEI 数据，且调用频率需为 15/repeat_count FPS。  <br>
     *        + 视频帧仅携带前后 2s 内收到的 SEI 数据；语音通话场景下，若调用此接口后 1min 内未有 SEI 数据发送，则 SDK 会自动取消发布视频黑帧。  <br>
     *        + 消息发送成功后，远端会收到 onSEIMessageReceived{@link #IRTCVideoEventHandler#onSEIMessageReceived} 回调。  <br>
     *        + 语音通话切换至视频通话时，会停止使用黑帧发送 SEI 数据，自动转为用采集到的正常视频帧发送 SEI 数据。
     */
    /**
     * @locale en
     * @deprecated since 3.50 and will be deleted in 3.55, use [sendSEIMessage](#IRTCVideo-sendseimessage-2) instead.
     * @type api
     * @region Message
     * @brief <span id="IRTCVideo-sendseimessage-1"></span> Sends SEI data.  <br>
     *        In a video call scenario, SEI is sent with the video frame, while in a voice call scenario, SDK will automatically publish a black frame with a resolution of 16px × 16px to carry SEI data.
     * @param stream_index Specifys the type of media stream that carries SEI data. See StreamIndex{@link #StreamIndex}.  <br>
     *        In a voice call, you should set this parameter to `kStreamIndexMain`, otherwise the SEI data is discarded and cannot be sent to the remote user.
     * @param message SEI data
     * @param length SEI data length, no more than 4KB.
     * @param repeat_count Number of times a message is sent repeatedly. The value range is [0,30]. <br>
     *                    After calling this API, the SEI data will be added to a consecutive `repeat_count+1` number of video frames starting from the current frame.
     * @return  
     *         + `>=0`: The number of SEIs to be added to the video frame <br>
     *         + `<0`: Failure
     * @note  
     *         + In a voice call scenario, this API can be called to send SEI data only in internal capture mode and with a frequency of 15/repeat_count FPS.  <br>
     *         + Each video frame carrys only the SEI data received within 2s before and after. In a voice call scenario, if no SEI data is sent within 1min after calling this API, SDK will automatically cancel publishing black frames.  <br>
     *         + After the message is sent successfully, the remote user who subscribed your video stream will receive onSEIMessageReceived{@link #IRTCVideoEventHandler#onSEIMessageReceived}.<br>
     *         + When you switch from a voice call to a video call, SEI data will automatically start to be sent with normally captured video frames instead of black frames.
     */
    BYTERTC_DEPRECATED virtual int sendSEIMessage(StreamIndex stream_index, const uint8_t* message, int length, int repeat_count) = 0;

    /**
     * @locale zh
     * @type api
     * @region 消息
     * @brief <span id="IRTCVideo-sendseimessage-2"></span> 通过视频帧发送 SEI 数据。<br>
     *        在视频通话场景下，SEI 数据会随视频帧发送；在语音通话场景下，SDK 会自动生成一路 16px × 16px 的黑帧视频流用来发送 SEI 数据。
     * @param stream_index 指定携带 SEI 数据的媒体流类型，参看 StreamIndex{@link #StreamIndex}。<br>
     *        语音通话场景下，该值需设为 `kStreamIndexMain`，否则 SEI 数据会被丢弃从而无法送达远端。
     * @param message SEI 消息。
     * @param length SEI 消息长度，建议每帧 SEI 数据总长度长度不超过 4 KB。
     * @param repeat_count 消息发送重复次数。取值范围是 [0, max{29, %{视频帧率}-1}]。推荐范围 [2,4]。<br>
     *                    调用此接口后，SEI 数据会添加到从当前视频帧开始的连续 `repeat_count+1` 个视频帧中。
     * @param mode SEI 发送模式，参看 SEICountPerFrame{@link #SEICountPerFrame}。
     * @return 
     *        + >= 0: 将被添加到视频帧中的 SEI 的数量。<br>
     *        + < 0: 发送失败。
     * @note 
     *        + 每秒发送的 SEI 消息数量建议不超过当前的视频帧率。在语音通话场景下，黑帧帧率为 15 fps。<br>
     *        + 语音通话场景中，仅支持在内部采集模式下调用该接口发送 SEI 数据。<br>
     *        + 视频通话场景中，使用自定义采集并通过 pushExternalVideoFrame{@link #IRTCVideo#pushExternalVideoFrame} 推送至 SDK 的视频帧，若本身未携带 SEI 数据，也可通过本接口发送 SEI 数据；若原视频帧中已添加了 SEI 数据，则调用此方法不生效。<br>
     *        + 视频帧仅携带前后 2s 内收到的 SEI 数据；语音通话场景下，若调用此接口后 1min 内未有 SEI 数据发送，则 SDK 会自动取消发布视频黑帧。<br>
     *        + 消息发送成功后，远端会收到 onSEIMessageReceived{@link #IRTCVideoEventHandler#onSEIMessageReceived} 回调。<br>
     *        + 语音通话切换至视频通话时，会停止使用黑帧发送 SEI 数据，自动转为用采集到的正常视频帧发送 SEI 数据。
     */
    /**
     * @locale en
     * @type api
     * @region Message
     * @brief <span id="IRTCVideo-sendseimessage-2"></span> Sends SEI data.<br>
     *        In a video call scenario, SEI is sent with the video frame, while in a voice call scenario, SDK will automatically publish a black frame with a resolution of 16 × 16 pixels to carry SEI data.
     * @param stream_index Specifys the type of media stream that carries SEI data. See StreamIndex{@link #StreamIndex}.  <br>
     *        In a voice call, you should set this parameter to `kStreamIndexMain`, otherwise the SEI data is discarded and cannot be sent to the remote user.
     * @param message SEI data.
     * @param length SEI data length. No more than 4 KB SEI data per frame is recommended.
     * @param repeat_count Number of times a message is sent repeatedly. The value range is [0, max{29, %{video frame rate}-1}]. Recommended range: [2,4].<br>
     *                    After calling this API, the SEI data will be added to a consecutive `repeat_count+1` number of video frames starting from the current frame.
     * @param mode SEI sending mode. See SEICountPerFrame{@link #SEICountPerFrame}.
     * @return  
     *         + >= 0: The number of SEIs to be added to the video frame <br>
     *         + < 0: Failure
     * @note  
     *         + We recommend the number of SEI messages per second should not exceed the current video frame rate. In a voice call, the blank-frame rate is 15 fps.<br>
     *         + In a voice call, this API can be called to send SEI data only in internal capture mode.<br>
     *         + In a video call, the custom captured video frame can also be used for sending SEI data if the original video frame contains no SEI data, otherwise calling this method will not take effect.<br>
     *         + Each video frame carrys only the SEI data received within 2s before and after. In a voice call scenario, if no SEI data is sent within 1min after calling this API, SDK will automatically cancel publishing black frames.<br>
     *         + After the message is sent successfully, the remote user who subscribed your video stream will receive onSEIMessageReceived{@link #IRTCVideoEventHandler#onSEIMessageReceived}.<br>
     *         + When you switch from a voice call to a video call, SEI data will automatically start to be sent with normally captured video frames instead of black frames.
     */
    virtual int sendSEIMessage(StreamIndex stream_index, const uint8_t* message, int length, int repeat_count, SEICountPerFrame mode) = 0;

    /**
     * @locale zh
     * @valid since 3.56
     * @hidden for internal use only
     * @type api
     * @region 消息
     * @brief <span id="IRTCVideo-sendseimessage-2"></span> 公共流视频帧发送 SEI 数据。
     * @param stream_index 指定携带 SEI 数据的媒体流类型，参看 StreamIndex{@link #StreamIndex}。
     * @param channel_id SEI 消息传输通道，取值范围 [0 - 255]。通过此参数，你可以为不同接受方设置不同的 ChannelID，这样不同接收方可以根据回调中的 ChannelID 选择应关注的 SEI 信息。
     * @param message SEI 消息。
     * @param length SEI 消息长度，建议每帧 SEI 数据总长度长度不超过 4 KB。
     * @param repeat_count 消息发送重复次数。取值范围是 [0, max{29, %{视频帧率}-1}]。推荐范围 [2,4]。<br>
     *                    调用此接口后，SEI 数据会添加到从当前视频帧开始的连续 `repeat_count+1` 个视频帧中。
     * @param mode SEI 发送模式，参看 SEICountPerFrame{@link #SEICountPerFrame}。
     * @return 
     *        + < 0：说明调用失败<br>
     *        + = 0：说明当前发送队列已满，无法发送<br>
     *        + > 0: 说明调用成功，该数值为已经发送 SEI 的数量
     * @note 
     *        + 每秒发送的 SEI 消息数量建议不超过当前的视频帧率<br>
     *        + 视频通话场景中，使用自定义采集并通过 pushExternalVideoFrame{@link #IRTCVideo#pushExternalVideoFrame} 推送至 SDK 的视频帧，若本身未携带 SEI 数据，也可通过本接口发送 SEI 数据；若原视频帧中已添加了 SEI 数据，则调用此方法不生效。<br>
     *        + 视频帧仅携带前后 2s 内收到的 SEI 数据<br>
     *        + 消息发送成功后，远端会收到 onPublicStreamSEIMessageReceivedWithChannel{@link #IRTCVideoEventHandler#onPublicStreamSEIMessageReceivedWithChannel} 回调。<br>
     *        + 调用失败时，本地及远端都不会收到回调。
     */
    /**
     * @locale en
     * @valid since 3.56
     * @hidden for internal use only
     * @type api
     * @region Message
     * @brief <span id="IRTCVideo-sendseimessage-2"></span> Public stream sends SEI data.
     * @param stream_index Specifys the type of media stream that carries SEI data. See StreamIndex{@link #StreamIndex}.  
     * @param channel_id SEI message channel id. The value range is [0 - 255]. With this parameter, you can set different ChannelIDs for different recipients. In this way, different recipients can choose the SEI information  based on the ChannelID received in the callback.
     * @param message SEI data.
     * @param length SEI data length. No more than 4 KB SEI data per frame is recommended.
     * @param repeat_count Number of times a message is sent repeatedly. The value range is [0, max{29, %{video frame rate}-1}]. Recommended range: [2,4].<br>
     *                    After calling this API, the SEI data will be added to a consecutive `repeat_count+1` number of video frames starting from the current frame.
     * @param mode SEI sending mode. See SEICountPerFrame{@link #SEICountPerFrame}.
     * @return  
     *         + < 0：Failure<br>
     *         + = 0: You are unable to send SEI as the current send queue is full. <br>
     *         + > 0: Success, and the value represents the amount of sent SEI. 
     * @note  
     *         + We recommend the number of SEI messages per second should not exceed the current video frame rate.<br>
     *         + In a video call, the custom captured video frame can also be used for sending SEI data if the original video frame contains no SEI data, otherwise calling this method will not take effect.<br>
     *         + Each video frame carrys only the SEI data received within 2s before and after. In a voice call scenario, if no SEI data is sent within 1min after calling this API, SDK will automatically cancel publishing black frames.<br>
     *         + After the message is sent successfully, the remote user who subscribed your video stream will receive onPublicStreamSEIMessageReceivedWithChannel{@link #IRTCVideoEventHandler#onPublicStreamSEIMessageReceivedWithChannel}.<br>
     *         + When the call fails, neither the local nor the remote side will receive a callback.
     */
    virtual int sendPublicStreamSEIMessage(StreamIndex stream_index, int channel_id, const uint8_t* message, int length,
                                           int repeat_count, SEICountPerFrame mode) = 0;

    /**
     * @locale zh
     * @type api
     * @region 视频设备管理
     * @brief 创建视频设备管理实例
     * @return 视频设备管理实例，详见IVideoDeviceManager{@link #IVideoDeviceManager}
     */
    /**
     * @locale en
     * @type api
     * @region Video Facility Management
     * @brief Create a video Facility Management instance
     * @return Video Facility Management instance. See IVideoDeviceManager{@link #IVideoDeviceManager}
     */
    virtual IVideoDeviceManager* getVideoDeviceManager() = 0;

    /**
     * @locale zh
     * @hidden(Android,iOS)
     * @type api
     * @region 音频管理
     * @brief 设备音频管理接口创建
     * @return 音频设备管理接口
     */
    /**
     * @locale en
     * @hidden(Android,iOS)
     * @type api
     * @region audio management
     * @brief Device audio management interface creation
     * @return Audio Facility Management interface
     */
    virtual IAudioDeviceManager* getAudioDeviceManager() = 0;

    /**
     * @locale zh
     * @type api
     * @region 本地录制
     * @brief 录制通话过程中的音视频数据到本地的文件中。
     * @param type 流属性，指定录制主流还是屏幕流，参看 StreamIndex{@link #StreamIndex}
     * @param config 本地录制参数配置，参看 RecordingConfig{@link #RecordingConfig}
     * @param recording_type 本地录制的媒体类型，参看 RecordingType{@link #RecordingType}
     * @return  
     *        + 0: 正常<br>
     *        + -1: 参数设置异常<br>
     *        + -2: 当前版本 SDK 不支持该特性，请联系技术支持人员
     * @note  
     *        + 调用该方法后，你会收到 onRecordingStateUpdate{@link #IRTCVideoEventHandler#onRecordingStateUpdate} 回调。  <br>
     *        + 如果录制正常，系统每秒钟会通过 onRecordingProgressUpdate{@link #IRTCVideoEventHandler#onRecordingProgressUpdate} 回调通知录制进度。
     */
    /**
     * @locale en
     * @type api
     * @region Local recording
     * @brief This method records the audio & video data during the call to a local file.
     * @param type Stream attribute, specify whether to record mainstream or screen stream. See StreamIndex{@link #StreamIndex}
     * @param config Local recording parameter configuration. See RecordingConfig{@link #RecordingConfig}
     * @param recording_type Local recording media type. See RecordingType{@link #RecordingType}.
     * @return   
     *         + 0: normal<br>
     *         + -1: Parameter setting exception<br>
     *         + -2: The current version of the SDK does not support this Feature, please contact technical support staff
     * @note   
     *         + After calling this method, you will receive an onRecordingStateUpdate{@link #IRTCVideoEventHandler#onRecordingStateUpdate} callback. <br>
     *         + If the recording is normal, the system will notify the recording progress through onRecordingProgressUpdate{@link #IRTCVideoEventHandler#onRecordingProgressUpdate} Callback every second.
     */
    virtual int startFileRecording(StreamIndex type, RecordingConfig config, RecordingType recording_type) = 0;

    /**
     * @locale zh
     * @type api
     * @region 本地录制
     * @brief 停止本地录制
     * @param type 流属性，指定停止主流或者屏幕流录制，参看 StreamIndex{@link #StreamIndex}
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note  
     *        + 调用 startFileRecording{@link #IRTCVideo#startFileRecording} 开启本地录制后，你必须调用该方法停止录制。  <br>
     *        + 调用该方法后，你会收到 onRecordingStateUpdate{@link #IRTCVideoEventHandler#onRecordingStateUpdate} 回调提示录制结果。
     */
    /**
     * @locale en
     * @type api
     * @region local recording
     * @brief Stop local recording
     * @param type Stream attribute, specify to stop mainstream or screen stream recording. See StreamIndex{@link #StreamIndex}
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note   
     *         + Call startFileRecording{@link #IRTCVideo#startFileRecording} After starting local recording, you must call this method to stop recording. <br>
     *         + After calling this method, you will receive an onRecordingStateUpdate{@link #IRTCVideoEventHandler#onRecordingStateUpdate} callback prompting you to record the result.
     */
    virtual int stopFileRecording(StreamIndex type) = 0;

    /**
     * @locale zh
     * @type api
     * @brief 开启录制语音通话，生成本地文件。<br>
     *        在进房前后开启录制，如果未打开麦克风采集，录制任务正常进行，只是不会将数据写入生成的本地文件；只有调用 startAudioCapture{@link #IRTCVideo#startAudioCapture} 接口打开麦克风采集后，才会将录制数据写入本地文件。
     * @param config 参看 AudioRecordingConfig{@link #AudioRecordingConfig}
     * @return  
     *        + 0: 正常 <br>
     *        + -2: 参数设置异常 <br>
     *        + -3: 当前版本 SDK 不支持该特性，请联系技术支持人员
     * @note 
     *        + 录制包含各种音频效果。但不包含背景音乐。<br>
     *        + 调用 stopAudioRecording{@link #IRTCVideo#stopAudioRecording} 关闭录制。<br>
     *        + 加入房间前后均可调用。在进房前调用该方法，退房之后，录制任务不会自动停止，需调用stopAudioRecording{@link #IRTCVideo#stopAudioRecording} 关闭录制。在进房后调用该方法，退房之后，录制任务会自动被停止。如果加入了多个房间，录制的文件中会包含各个房间的音频。<br>
     *        + 调用该方法后，你会收到 onAudioRecordingStateUpdate{@link #IRTCVideoEventHandler#onAudioRecordingStateUpdate} 回调。  
     */
    /**
     * @locale en
     * @type api
     * @brief Starts recording audio communication, and generate the local file.<br>
     *        If you call this API before or after joining the room without internal audio capture, then the recording task can still begin but the data will not be recorded in the local files. Only when you call startAudioCapture{@link #IRTCVideo#startAudioCapture} to enable internal audio capture, the data will be recorded in the local files. 
     * @param config See AudioRecordingConfig{@link #AudioRecordingConfig}.
     * @return  
     *        + 0: `kReturnStatusSuccess`: Success <br>
     *        + -2: `kReturnStatusParameterErr`: Invalid parameters <br>
     *        + -3: `kReturnStatusWrongState`: Not valid in this SDK. Please contact the technical support.
     * @note 
     *        + All audio effects are valid in the file. Mixed audio file is not included in the file. <br>
     *        + Call stopAudioRecording{@link #IRTCVideo#stopAudioRecording} to stop recording. <br>
     *        + You can call this API before and after joining the room. If this API is called before you join the room, you need to call stopAudioRecording{@link #IRTCVideo#stopAudioRecording} to stop recording. If this API is called after you join the room, the recording task ends automatically. If you join multiple rooms, audio from all rooms are recorded in one file.  <br>
     *        + After calling the API, you'll receive onAudioRecordingStateUpdate{@link #IRTCVideoEventHandler#onAudioRecordingStateUpdate}. 
     */
    virtual int startAudioRecording(AudioRecordingConfig& config) = 0;

    /**
     * @locale zh
     * @type api
     * @brief 停止音频文件录制
     * @return 
     *         + 0: 正常 <br>
     *         + -3: 当前版本 SDK 不支持该特性，请联系技术支持人员
     * @note 调用 startAudioRecording{@link #IRTCVideo#startAudioRecording} 开启本地录制。
     */
     /**
     * @locale en
     * @type api
     * @brief Stop audio recording.
     * @return 
     *         + 0: Success <br>
     *         + <0: Failure
     * @note Call startAudioRecording{@link #IRTCVideo#startAudioRecording} to start the recording task.
     */
    virtual int stopAudioRecording() = 0;

    /**
     * @locale zh
     * @type api
     * @brief 启用匹配外置声卡的音频处理模式
     * @param enable <br>
     *        + true: 开启 <br>
     *        + false: 不开启(默认)
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note  
     *        + 当采用外接声卡进行音频采集时，建议开启此模式，以获得更好的音质。<br>
     *        + 开启此模式时，仅支持耳机播放。如果需要使用扬声器或者外置音箱播放，关闭此模式。
     */
    /**
     * @locale en
     * @type api
     * @brief Enable the audio process mode for external sound card.
     * @param enable <br>
     *        + true: enable <br>
     *        + false: disable (by default)
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note   
     *         + When you use external sound card for audio capture, enable this mode for better audio quality. <br>
     *         + When using the mode, you can only use earphones. If you need to use internal or external speaker, disable this mode.
     */
    virtual int enableExternalSoundCard(bool enable) = 0;

    /**
     * @locale zh
     * @type api
     * @region 引擎管理
     * @brief 设置运行时的参数
     * @param json_string  json 序列化之后的字符串
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note 该接口需在 joinRoom{@link #IRTCRoom#joinRoom} 和 startAudioCapture{@link #IRTCVideo#startAudioCapture} 之前调用。
     * @list 引擎管理
     * @order 25
     */
    /**
     * @locale en
     * @type api
     * @region Engine management
     * @brief Set runtime parameters
     * @param json_string String after json serialization
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note Call this API before joinRoom{@link #IRTCRoom#joinRoom} and startAudioCapture{@link #IRTCVideo#startAudioCapture}.
     * @list Engine Management
     * @order 25
     */
    virtual int setRuntimeParameters(const char * json_string) = 0;

    /**
     * @locale zh
     * @hidden(Windows,Linux,macOS)
     * @type api
     * @region 语音识别服务
     * @brief 开启自动语音识别服务。<br>
     *        该方法将识别后的用户语音转化成文字，并通过 onMessage{@link #IRTCASREngineEventHandler#onMessage} 事件回调给用户。
     * @param asr_config 校验信息，参看 RTCASRConfig{@link #RTCASRConfig}
     * @param handler 语音识别服务使用状态回调，参看 IRTCASREngineEventHandler{@link #IRTCASREngineEventHandler}
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     */
    /**
     * @locale en
     * @hidden currently not available
     * @type api
     * @region speech recognition service
     * @brief Enables automatic speech recognition service. This method converts the recognized user's voice into text and calls it back to the user through onMessage{@link #IRTCASREngineEventHandler#onMessage}.
     * @param asr_config Check information. See RTCASRConfig{@link #RTCASRConfig}
     * @param handler Speech recognition service usage status callback. See IRTCASREngineEventHandler{@link #IRTCASREngineEventHandler}
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     */
    virtual int startASR(const RTCASRConfig& asr_config, IRTCASREngineEventHandler* handler) = 0;

    /**
     * @locale zh
     * @hidden(Windows,Linux,macOS)
     * @type api
     * @region 语音识别服务
     * @brief 关闭语音识别服务
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     */
    /**
     * @locale en
     * @hidden currently not available
     * @type api
     * @region speech recognition service
     * @brief Turn off speech recognition service
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     */
    virtual int stopASR() = 0;
    /**
     * @locale zh
     * @type api
     * @region 引擎管理
     * @brief 将用户反馈的问题上报到 RTC。
     * @param type 预设问题列表，参看 ProblemFeedbackOption{@link #ProblemFeedbackOption}
     * @param info 预设问题以外的其他问题的具体描述，房间信息。 参看 ProblemFeedbackInfo{@link #ProblemFeedbackInfo}
     * @return 
     *         + 0: 上报成功  <br>
     *         + -1: 上报失败，还没加入过房间 <br>
     *         + -2: 上报失败，数据解析错误  <br>
     *         + -3: 上报失败，字段缺失  
     * @note 
     *         + 你可以在 [RTC 控制台](https://console.volcengine.com/rtc/callQualityRTC/feedback)上查看用户通过此接口提交的反馈详情和整体趋势。 <br>
     *         + 如果用户上报时在房间内，那么问题会定位到用户当前所在的一个或多个房间；如果用户上报时不在房间内，那么问题会定位到引擎此前退出的房间。
     * @list 引擎管理
     * @order 10
     */
    /**
     * @locale en
     * @type api
     * @region Engine management
     * @brief Report the user feedback to RTC.
     * @param type List of preset problems. See ProblemFeedbackOption{@link #ProblemFeedbackOption}
     * @param info Specific description of other problems other than the preset problem, and room's information. See ProblemFeedbackInfo{@link #ProblemFeedbackInfo}
     * @return  
     *          + 0: Report successfully <br>
     *          + -1: Failed to report, not yet joined the room <br>
     *          + -2: Failed to report, data analysis error <br>
     *          + -3: Failed to report, missing fields 
     * @note If the user is in the room when reporting, the report leads to the room / rooms where the user is currently located;<br>
     *        If the user is not in the room when reporting, the report leads to the previously exited Room.
     * @list Engine Management
     * @order 10
     */
    virtual int feedback(uint64_t type, const ProblemFeedbackInfo* info) = 0;
    /**
     * @locale zh
     * @type api
     * @deprecated since 353.1, will be deleted in 359, use getAudioEffectPlayer{@link #IRTCVideo#getAudioEffectPlayer} or getMediaPlayer{@link #IRTCVideo#getMediaPlayer} instead
     * @region 混音
     * @brief 混音管理接口创建
     * @return 混音管理实例，详见IAudioMixingManager{@link #IAudioMixingManager}
     */
    /**
     * @locale en
     * @type api
     * @deprecated since 353.1, will be deleted in 359, use getAudioEffectPlayer{@link #IRTCVideo#getAudioEffectPlayer} or getMediaPlayer{@link #IRTCVideo#getMediaPlayer} instead
     * @region  mixing
     * @brief  Mixing management interface creation
     * @return  Mixing management instance. See IAudioMixingManager{@link #IAudioMixingManager}
     */
    virtual IAudioMixingManager* getAudioMixingManager() = 0;
    /**
     * @locale zh
     * @type api
     * @valid since 3.53
     * @brief 创建音效播放器实例。
     * @return 音效播放器。详见 IAudioEffectPlayer{@link #IAudioEffectPlayer}。
     */
    /**
     * @locale en
     * @type api
     * @valid since 3.53
     * @brief Create an instance for audio effect player.
     * @return See IAudioEffectPlayer{@link #IAudioEffectPlayer}.
     */
    virtual IAudioEffectPlayer* getAudioEffectPlayer() = 0;
    /**
     * @locale zh
     * @type api
     * @valid since 3.53
     * @brief 创建音乐播放器实例。
     * @param player_id 音乐播放器实例 id。取值范围为 `[0, 3]`。最多同时存在4个实例，超出取值范围时返回 nullptr。
     * @return 音乐播放器实例，详见 IMediaPlayer{@link #IMediaPlayer}
     */
    /**
     * @locale en
     * @type api
     * @valid since 3.53
     * @brief Create a media player instance.
     * @param player_id Media player id. The range is `[0, 3]`. You can create up to 4 instances at the same time. If it exceeds the range, nullptr will be returned.
     * @return Media player instance. See IMediaPlayer{@link #IMediaPlayer}.
     */
    virtual IMediaPlayer* getMediaPlayer(int player_id) = 0;
    
    /**
     * @locale zh
     * @type api
     * @region 实时消息通信
     * @brief 登陆 RTS 服务器。
     *        必须先登录，才能调用 sendUserMessageOutsideRoom{@link #IRTCVideo#sendUserMessageOutsideRoom} 和 sendServerMessage{@link #IRTCVideo#sendServerMessage} 发送房间外点对点消息和向应用服务器发送消息 <br>
     *        在调用本接口登录后，如果想要登出，需要调用 logout{@link #IRTCVideo#logout}。
     * @param token  用户登录必须携带的 Token，用于鉴权验证。<br>
     *               测试时可使用[控制台](https://console.volcengine.com/rtc/listRTC)生成临时 Token，`roomId` 填任意值。<br>
     *               正式上线需要使用密钥 SDK 在你的服务端生成并下发 Token，`roomId` 置空，Token 有效期及生成方式参看[使用 Token 完成鉴权](70121)。
     * @param uid  <br>
     *        用户 ID  <br>
     *        用户 ID 在 appid 的维度下是唯一的。
     * @return 
     *        + 0：成功；<br>
     *        + <0：失败。具体失败原因参看 ReturnStatus{@link #ReturnStatus}。
     * @note 本地用户调用此方法登录后，会收到 onLoginResult{@link #IRTCVideoEventHandler#onLoginResult} 回调通知登录结果，远端用户不会收到通知。
     */
    /**
     * @locale en
     * @type api
     * @region Real-time messaging
     * @brief Log in to call sendUserMessageOutsideRoom{@link #IRTCVideo#sendUserMessageOutsideRoom} and sendServerMessage{@link #IRTCVideo#sendServerMessage} to send P2P messages or send messages to a server without joining the RTC room. <br>
     *        To log out, call logout{@link #IRTCVideo#logout}.
     * @param token <br>
     *        Token is required during login for authentication. <br>
     *        This Token is different from that required by calling joinRoom. You can assign any value even null to `roomId` to generate a login token. During developing and testing, you can use temporary tokens generated on the console. Deploy the token generating application on your server.
     * @param uid <br>
     *        User ID <br>
     *        User ID is unique within one appid.
     * @return 
     *        + 0: Success.<br>
     *        + <0: Failure. See ReturnStatus{@link #ReturnStatus} for specific reasons.
     * @note  You will receive onLoginResult{@link #IRTCVideoEventHandler#onLoginResult} after calling this API and log in successfully. But remote users will not receive notification about that.
     */
    virtual int login(const char* token, const char* uid) = 0;

    /**
     * @locale zh
     * @type api
     * @region 实时消息通信
     * @brief 登出 RTS 服务器。
     *        调用本接口登出后，无法调用房间外消息以及端到服务器消息相关的方法或收到相关回调。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note  
     *       + 调用本接口登出前，必须先调用 login{@link #IRTCVideo#login} 登录。  <br>
     *       + 本地用户调用此方法登出后，会收到 onLogout{@link #IRTCVideoEventHandler#onLogout} 回调通知结果，远端用户不会收到通知。
     */
    /**
     * @locale en
     * @type After api
     * @region  real-time messaging
     * @brief  Calls this interface to log out, it is impossible to call methods related to out-of-room messages and end-to-server messages or receive related callbacks.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note   
     *        + Before calling this interface to log out, you must call login{@link #IRTCVideo#login} to log in. <br>
     *        + After local users call this method to log out, they will receive the result of the onLogout{@link #IRTCVideoEventHandler#onLogout} callback notification, and remote users will not receive the notification.
     */
    virtual int logout() = 0;

    /**
     * @locale zh
     * @type api
     * @region 实时消息通信
     * @brief 更新用户用于登录的 Token  <br>
     *        Token 有一定的有效期，当 Token 过期时，需调用此方法更新登录的 Token 信息。  <br>
     *        调用 login{@link #IRTCVideo#login} 方法登录时，如果使用了过期的 Token 将导致登录失败，并会收到 onLoginResult{@link #IRTCVideoEventHandler#onLoginResult} 回调通知，错误码为 kLoginErrorCodeInvalidToken。此时需要重新获取 Token，并调用此方法更新 Token。
     * @param token  <br>
     *        更新的动态密钥
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note  
     *       + 如果 Token 无效导致登录失败，则调用此方法更新 Token 后，SDK 会自动重新登录，而用户不需要自己调用 login{@link #IRTCVideo#login} 方法。  <br>
     *       + Token 过期时，如果已经成功登录，则不会受到影响。Token 过期的错误会在下一次使用过期 Token 登录时，或因本地网络状况不佳导致断网重新登录时通知给用户。
     */
    /**
     * @locale en
     * @type api
     * @region Real-time messaging
     * @brief Update the Token <br>
     *        Token used by the user to log in has a certain valid period. When the Token expires, you need to call this method to update the login Token information. <br>
     *         When calling the login{@link #IRTCVideo#login} method to log in, if an expired token is used, the login will fail and you will receive an onLoginResult{@link #IRTCVideoEventHandler#onLoginResult} callback notification with an error code of kLoginErrorCodeInvalidToken. You need to reacquire the token and call this method to update the token.
     * @param token <br>
     *        Updated dynamic key
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note   
     *        + If the token is invalid and the login fails, call this method. After updating the token, the SDK will automatically log back in, and the user does not need to call the login{@link #IRTCVideo#login} method. <br>
     *        + Token expires, if you have successfully logged in, it will not be affected. An expired Token error will be notified to the user the next time you log in with an expired Token, or when you log in again due to a disconnection due to poor local network conditions.
     */
    virtual int updateLoginToken(const char* token) = 0;

    /**
     * @locale zh
     * @type api
     * @region 实时消息通信
     * @brief 设置应用服务器参数  <br>
     *        客户端调用 sendServerMessage{@link #IRTCVideo#sendServerMessage} 或 sendServerBinaryMessage{@link #IRTCVideo#sendServerBinaryMessage} 发送消息给应用服务器之前，必须设置有效签名和应用服务器地址。
     * @param signature 动态签名，应用服务器可使用该签名验证消息来源。<br>
     *        签名需自行定义，可传入任意非空字符串，建议将 uid 等信息编码为签名。<br>
     *        设置的签名会以 post 形式发送至通过本方法中 url 参数设置的应用服务器地址。
     * @param url 应用服务器的地址
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note  
     *       + 用户必须调用 login{@link #IRTCVideo#login} 登录后，才能调用本接口。  <br>
     *       + 调用本接口后，SDK 会使用 onServerParamsSetResult{@link #IRTCVideoEventHandler#onServerParamsSetResult} 返回相应结果。
     */
    /**
     * @locale en
     * @type api
     * @region Real-time messaging
     * @brief Set application server parameters   <br>
     *        Client side calls sendServerMessage{@link #IRTCVideo#sendServerMessage} or sendServerBinaryMessage{@link #IRTCVideo#sendServerBinaryMessage} Before sending a message to the application server, a valid signature and application server address must be set.
     * @param signature Dynamic signature. The App server may use the signature to verify the source of messages.<br>
     *        You need to define the signature yourself. It can be any non-empty string. It is recommended to encode information such as UID into the signature.<br>
     *        The signature will be sent to the address set through the "url" parameter in the form of a POST request.
     * @param url The address of the application server
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note   
     *        + The user must call login{@link #IRTCVideo#login} to log in before calling this interface. <br>
     *        + After calling this interface, the SDK will use onServerParamsSetResult{@link #IRTCVideoEventHandler#onServerParamsSetResult} to return the corresponding result.
     */
    virtual int setServerParams(const char* signature, const char* url) = 0;

    /**
     * @locale zh
     * @type api
     * @region 实时消息通信
     * @brief 查询对端用户或本端用户的登录状态
     * @param peer_user_id  <br>
     *        需要查询的用户 ID
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note  
     *       + 必须调用 login{@link #IRTCVideo#login} 登录后，才能调用本接口。  <br>
     *       + 调用本接口后，SDK 会使用 onGetPeerOnlineStatus{@link #IRTCVideoEventHandler#onGetPeerOnlineStatus} 回调通知查询结果。  <br>
     *       + 在发送房间外消息之前，用户可以通过本接口了解对端用户是否登录，从而决定是否发送消息。也可以通过本接口查询自己查看自己的登录状态。
     */
    /**
     * @locale en
     * @type api
     * @region Real-time messaging
     * @brief Query the login status of the opposite or local user
     * @param peer_user_id <br>
     *        User ID to be queried
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note   
     *        + login{@link #IRTCVideo#login} must be called before this interface can be called. <br>
     *        + After calling this interface, the SDK notifies the query result using the onGetPeerOnlineStatus{@link #IRTCVideoEventHandler#onGetPeerOnlineStatus} callback. <br>
     *        + Before sending an out-of-room message, the user can know whether the peer user is logged in through this interface to decide whether to send a message. You can also check your login status through this interface.
     */
    virtual int getPeerOnlineStatus(const char* peer_user_id) = 0;

    /**
     * @locale zh
     * @type api
     * @region 实时消息通信
     * @brief 给房间外指定的用户发送文本消息（P2P）
     * @param uid  <br>
     *        消息接收用户的 ID
     * @param message  <br>
     *        发送的文本消息内容  <br>
     *        消息不超过 64 KB。
     * @param config 消息类型，参看 MessageConfig{@link #MessageConfig}。
     * @return  
     *        + >0：发送成功，返回这次发送消息的编号，从 1 开始递增  <br>
     *        + -1：发送失败，IRTCVideo 实例未创建  <br>
     *        + -2：发送失败，uid 为空
     * @note  
     *       + 在发送房间外文本消息前，必须先调用 login{@link #IRTCVideo#login} 完成登录。  <br>
     *       + 用户调用本接口发送文本信息后，会收到一次 onUserMessageSendResultOutsideRoom{@link #IRTCVideoEventHandler#onUserMessageSendResultOutsideRoom} 回调，得知消息是否成功发送。  <br>
     *       + 若文本消息发送成功，则 uid 所指定的用户会通过 onUserMessageReceivedOutsideRoom{@link #IRTCVideoEventHandler#onUserMessageReceivedOutsideRoom} 回调收到该消息。
     */
    /**
     * @locale en
     * @type api
     * @region Real-time messaging
     * @brief Send a text message (P2P) to a specified user outside the room
     * @param uid User ID of the message receiver
     * @param message <br>
     *        Text message content sent <br>
     *        Message does not exceed 64 KB.
     * @param config Message type, see MessageConfig{@link #MessageConfig}.
     * @return   
     *         + > 0: Sent successfully, return the number of the sent message, increment from 1 <br>
     *         + -1: Sent failed, IRTCVideo instance not created <br>
     *         + -2: Sent failed, uid is empty
     * @note   
     *        + You must call login{@link #IRTCVideo#login} to complete the login before you can send a message in a foreign text of the room. <br>
     *        + After the user calls this interface to send a text message, he will receive an onUserMessageSendResultOutsideRoom{@link #IRTCVideoEventHandler#onUserMessageSendResultOutsideRoom} callback to know whether the message was successfully sent. <br>
     *        + If the text message is sent successfully, the user specified by uid receives the message via the onUserMessageReceivedOutsideRoom{@link #IRTCVideoEventHandler#onUserMessageReceivedOutsideRoom} callback.
     */
    virtual int64_t sendUserMessageOutsideRoom(const char* uid, const char* message, MessageConfig config = kMessageConfigReliableOrdered) = 0;

    /**
     * @locale zh
     * @type api
     * @region 实时消息通信
     * @brief 给房间外指定的用户发送二进制消息（P2P）
     * @param uid  <br>
     *        消息接收用户的 ID
     * @param length <br>
     *        二进制字符串的长度
     * @param message  <br>
     *        发送的二进制消息内容  <br>
     *        消息不超过 46KB。
     * @param config 消息类型，参看 MessageConfig{@link #MessageConfig}。
     * @return  
     *        + >0：发送成功，返回这次发送消息的编号，从 1 开始递增  <br>
     *        + -1：发送失败，IRTCVideo 实例未创建  <br>
     *        + -2：发送失败，uid 为空
     * @note  
     *       + 在发送房间外二进制消息前，必须先调用 login{@link #IRTCVideo#login} 完成登录。  <br>
     *       + 用户调用本接口发送二进制消息后，会收到一次 onUserMessageSendResultOutsideRoom{@link #IRTCVideoEventHandler#onUserMessageSendResultOutsideRoom} 回调，通知消息是否发送成功。  <br>
     *       + 若二进制消息发送成功，则 uid 所指定的用户会通过 onUserBinaryMessageReceivedOutsideRoom{@link #IRTCVideoEventHandler#onUserBinaryMessageReceivedOutsideRoom} 回调收到该条消息。
     */
    /**
     * @locale en
     * @type api
     * @region Real-time messaging
     * @brief Send binary messages (P2P) to a specified user outside the room
     * @param uid <br>
     *        ID of the user receiving the message
     * @param length <br>
     *        Length of the binary string
     * @param message <br>
     *        Content of the binary message sent <br>
     *        Message does not exceed 46KB.
     * @param config Message type, see MessageConfig{@link #MessageConfig}.
     * @return   
     *         + > 0: sent successfully, return the number of the sent message, increment from 1 <br>
     *         + -1: Sent failed, IRTCVideo instance not created <br>
     *         + -2: Sent failed, uid is empty
     * @note   
     *        + login{@link #IRTCVideo#login} must be called before sending out-of-room binary messages. <br>
     *        + After the user calls this interface to send a binary message, he will receive an onUserMessageSendResultOutsideRoom{@link #IRTCVideoEventHandler#onUserMessageSendResultOutsideRoom} callback to notify whether the message was sent successfully. <br>
     *        + If the binary message is sent successfully, the user specified by uid will receive the message through the onUserBinaryMessageReceivedOutsideRoom{@link #IRTCVideoEventHandler#onUserBinaryMessageReceivedOutsideRoom} callback.
     */
    virtual int64_t sendUserBinaryMessageOutsideRoom(const char* uid, int length, const uint8_t* message, MessageConfig config = kMessageConfigReliableOrdered) = 0;
    /**
     * @locale zh
     * @type api
     * @region 实时消息通信
     * @brief 客户端给应用服务器发送文本消息（P2Server）
     * @param message  <br>
     *        发送的文本消息内容  <br>
     *        消息不超过 64 KB。
     * @return  
     *        + >0：发送成功，返回这次发送消息的编号，从 1 开始递增  <br>
     *        + -1：发送失败，IRTCVideo 实例未创建
     * @note  
     *       + 在向应用服务器发送文本消息前，必须先调用 login{@link #IRTCVideo#login} 完成登录，随后调用 setServerParams{@link #IRTCVideo#setServerParams} 设置应用服务器。  <br>
     *       + 调用本接口后，会收到一次 onServerMessageSendResult{@link #IRTCVideoEventHandler#onServerMessageSendResult} 回调，通知消息发送方是否发送成功。  <br>
     *       + 若文本消息发送成功，则之前调用 setServerParams{@link #IRTCVideo#setServerParams} 设置的应用服务器会收到该条消息。
     */
    /**
     * @locale en
     * @type api
     * @region Real-time messaging
     * @brief The client side sends a text message to the application server (P2Server)
     * @param message <br>
     *        The content of the text message sent <br>
     *        The message does not exceed 64 KB.
     * @return   
     *         + > 0: Sent successfully, return the number of the sent message, increment from 1 <br>
     *         + -1: Sent failed, IRTCVideo instance not created
     * @note   
     *        + Before sending a text message to the application server, you must first call login{@link #IRTCVideo#login} to complete the login, and then call setServerParams{@link #IRTCVideo#setServerParams} Set up the application server. <br>
     *        + After calling this interface, you will receive an onServerMessageSendResult{@link #IRTCVideoEventHandler#onServerMessageSendResult} callback to inform the message sender whether the message was sent successfully. <br>
     *        + If the text message is sent successfully, the application server that previously called setServerParams{@link #IRTCVideo#setServerParams} will receive the message.
     */
    virtual int64_t sendServerMessage(const char* message) = 0;
    /**
     * @locale zh
     * @type api
     * @region 实时消息通信
     * @brief 客户端给应用服务器发送二进制消息（P2Server）
     * @param length <br>
     *        二进制字符串的长度
     * @param message  <br>
     *        发送的二进制消息内容  <br>
     *        消息不超过 46KB。
     * @return  
     *        + >0：发送成功，返回这次发送消息的编号，从 1 开始递增  <br>
     *        + -1：发送失败，IRTCVideo 实例未创建
     * @note  
     *       + 在向应用服务器发送二进制消息前，必须先调用 login{@link #IRTCVideo#login} 完成登录，随后调用 setServerParams{@link #IRTCVideo#setServerParams} 设置应用服务器。  <br>
     *       + 调用本接口后，会收到一次 onServerMessageSendResult{@link #IRTCVideoEventHandler#onServerMessageSendResult} 回调，通知消息发送方发送成功或失败。  <br>
     *       + 若二进制消息发送成功，则之前调用 setServerParams{@link #IRTCVideo#setServerParams} 设置的应用服务器会收到该条消息。
     */
    /**
     * @locale en
     * @type api
     * @region Real-time messaging
     * @brief Client side sends binary messages to the application server (P2Server)
     * @param length <br>
     *        Length of binary string
     * @param message <br>
     *        Binary message content sent <br>
     *        Message does not exceed 46KB.
     * @return   
     *         + > 0: Sent successfully, return the number of the sent message, increment from 1 <br>
     *         + -1: Sent failed, IRTCVideo instance not created
     * @note   
     *        + Before sending a binary message to the application server, you must first call login{@link #IRTCVideo#login} to complete the login, and then call setServerParams{@link #IRTCVideo#setServerParams} Set up the application server. <br>
     *        + After calling this interface, you will receive an onServerMessageSendResult{@link #IRTCVideoEventHandler#onServerMessageSendResult} callback to inform the message sender that the sending succeeded or failed. <br>
     *        + If the binary message is sent successfully, the application server that previously called setServerParams{@link #IRTCVideo#setServerParams} will receive the message.
     */
    virtual int64_t sendServerBinaryMessage(int length, const uint8_t* message) = 0;

    /**
     * @locale zh
     * @type api
     * @region 通话前网络探测
     * @brief 开启通话前网络探测
     * @param is_test_uplink  是否探测上行带宽
     * @param expected_uplink_bitrate  期望上行带宽，单位：kbps<br>范围为 {0, [100-10000]}，其中， `0` 表示由 SDK 指定最高码率。
     * @param is_test_downlink  是否探测下行带宽
     * @param expected_downlink_biterate  期望下行带宽，单位：kbps<br>范围为 {0, [100-10000]}，其中， `0` 表示由 SDK 指定最高码率。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note  
     *       + 成功调用本接口后，会在 3s 内收到一次 onNetworkDetectionResult{@link #IRTCVideoEventHandler#onNetworkDetectionResult} 回调，此后每 2s 会收到一次该回调，通知探测结果；  <br>
     *       + 若探测停止，则会收到一次 onNetworkDetectionStopped{@link #IRTCVideoEventHandler#onNetworkDetectionStopped} 通知探测停止。
     */
    /**
     * @locale en
     * @type api
     * @region Pre-call network detection
     * @brief Pre-call network detection
     * @param is_test_uplink Whether to detect uplink bandwidth
     * @param expected_uplink_bitrate Expected uplink bandwidth, unit: kbps<br>Range: {0, [100-10000]}, `0`: Auto, that RTC will set the highest bite rate.
     * @param is_test_downlink Whether to detect downlink bandwidth
     * @param expected_downlink_biterate Expected downlink bandwidth, unit: kbps<br>Range: {0, [100-10000]}, `0`: Auto, that RTC will set the highest bite rate.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note   
     *        + After calling this interface, you will receive onNetworkDetectionResult{@link #IRTCVideoEventHandler#onNetworkDetectionResult} within 3s and every 2s thereafter notifying the probe result; <br>
     *        + If the probe stops, you will receive onNetworkDetectionStopped{@link #IRTCVideoEventHandler#onNetworkDetectionStopped} notify that probing has stopped.
     */
    virtual int startNetworkDetection(bool is_test_uplink, int expected_uplink_bitrate, bool is_test_downlink, int expected_downlink_biterate) = 0;

    /**
     * @locale zh
     * @type api
     * @region 通话前网络探测
     * @brief 停止通话前网络探测
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note  
     *       + 调用本接口后，会收到一次 onNetworkDetectionStopped{@link #IRTCVideoEventHandler#onNetworkDetectionStopped} 回调通知探测停止。
     */
    /**
     * @locale en
     * @type api
     * @region Pre-call network probe
     * @brief Stop pre-call network probe
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note   
     *        + After calling this interface, you will receive onNetworkDetectionStopped{@link #IRTCVideoEventHandler#onNetworkDetectionStopped} notifying that the the probing has stopped.
     */
    virtual int stopNetworkDetection() = 0;

    /**
     * @locale zh
     * @hidden(Linux)
     * @type api
     * @region 屏幕共享
     * @brief 在屏幕共享时，设置屏幕音频的采集方式（内部采集/自定义采集）
     * @param source_type 屏幕音频输入源类型, 参看 AudioSourceType{@link #AudioSourceType}
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note  
     *      + 默认采集方式是 RTC SDK 内部采集。<br>
     *      + 你应该在 publishScreen{@link #IRTCRoom#publishScreen} 前，调用此方法。否则，你将收到 onWarning{@link #IRTCVideoEventHandler#onWarning} 的报错：`kWarningCodeSetScreenAudioSourceTypeFailed` <br>
     *      + 如果设定为内部采集，你必须再调用 startScreenAudioCapture{@link #IRTCVideo#startScreenAudioCapture} 开始采集；<br>
     *      + 如果设定为自定义采集，你必须再调用 pushScreenAudioFrame{@link #IRTCVideo#pushScreenAudioFrame} 将自定义采集到的屏幕音频帧推送到 RTC SDK。<br>
     *      + 无论是内部采集还是自定义采集，你都必须调用 publishScreen{@link #IRTCRoom#publishScreen} 将采集到的屏幕音频推送到远端。
     */
    /**
     * @locale en
     * @hidden(Linux)
     * @type api
     * @region Screen sharing
     * @brief Set the screen audio acquisition method (internal acquisition/custom acquisition)
     * @param source_type Screen audio input source type. See AudioSourceType{@link #AudioSourceType}
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note   
     *       + The default acquisition method is internal to the RTC SDK Collect. <br>
     *       + You should call this method before publishScreen{@link #IRTCRoom#publishScreen}. Otherwise, you will receive an error from onWarning{@link #IRTCVideoEventHandler#onWarning}: 'kWarningCodeSetScreenAudioSourceTypeFailed' <br>
     *       + If it is set to internal collection, you must call startScreenAudioCapture{@link #IRTCVideo#startScreenAudioCapture} to start collection; <br>
     *       + If it is set to custom collection, you must call pushScreenAudioFrame{@link #IRTCVideo#pushScreenAudioFrame} to customize the collected screen audio frame Push to the RTC SDK. <br>
     *       + Whether it is an internal capture or a custom capture, you must call publishScreen{@link #IRTCRoom#publishScreen} to push the captured screen audio to the remote end.
     */
    virtual int setScreenAudioSourceType(AudioSourceType source_type) = 0;

    /**
     * @locale zh
     * @hidden(Linux)
     * @type api
     * @region 屏幕共享
     * @brief 在屏幕共享时，设置屏幕音频流和麦克风采集到的音频流的混流方式
     * @param index 混流方式，参看 StreamIndex{@link #StreamIndex} <br>
     *        + `kStreamIndexMain`: 将屏幕音频流和麦克风采集到的音频流混流 <br>
     *        + `kStreamIndexScreen`: 默认值， 将屏幕音频流和麦克风采集到的音频流分为两路音频流
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note 你应该在 publishScreen{@link #IRTCRoom#publishScreen} 之前，调用此方法。否则，你将收到 onWarning{@link #IRTCVideoEventHandler#onWarning} `的报错：kWarningCodeSetScreenAudioStreamIndexFailed`
     */
    /**
     * @locale en
     * @hidden(Linux)
     * @type api
     * @region Screen sharing
     * @brief Set the mixing mode of the screen audio stream and the audio stream collected by the microphone when the screen is shared
     * @param index The mixing mode. See StreamIndex{@link #StreamIndex} <br>
     *         + 'kStreamIndexMain': Mix the audio stream collected by the screen audio stream and the microphone <br>
     *         + 'KStreamIndexScreen ': By default, it divides  the screen audio stream and the audio stream collected by the microphone into two audio streams
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note You should call this method before publishScreen{@link #IRTCRoom#publishScreen}. Otherwise, you will receive an error from onWarning{@link #IRTCVideoEventHandler#onWarning} ': kWarningCodeSetScreenAudioStreamIndexFailed'
     */
    virtual int setScreenAudioStreamIndex(StreamIndex index) = 0;

    /**
     * @locale zh
     * @hidden(iOS,Android,Linux)
     * @type api
     * @region 屏幕共享
     * @brief 在屏幕共享时，设置屏幕音频流的声道数
     * @param channel 声道数，参看 AudioChannel{@link #AudioChannel}
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note 当你调用 setScreenAudioStreamIndex{@link #IRTCVideo#setScreenAudioStreamIndex} 并设置屏幕音频流和麦克风音频流混流时，此接口不生效，音频通道数由 setAudioProfile{@link #IRTCVideo#setAudioProfile} 控制。
     */
    /**
     * @locale en
     * @hidden(iOS,Android,Linux)
     * @type api
     * @region Screen sharing
     * @brief Set the audio channel of the screen-sharing audio stream
     * @param channel The number of Audio channels. See AudioChannel{@link #AudioChannel}.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note When you call setScreenAudioStreamIndex{@link #IRTCVideo#setScreenAudioStreamIndex} to mix the microphone audio stream and the screen-sharing audio stream, the audio channel is set by setAudioProfile{@link #IRTCVideo#setAudioProfile} rather than this API.
     */
    virtual int setScreenAudioChannel(AudioChannel channel) = 0;

    /**
     * @locale zh
     * @hidden(Android,iOS,macOS)
     * @type api
     * @region 屏幕共享
     * @brief 在屏幕共享时，开始使用 RTC SDK 内部采集方式，采集屏幕音频
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note 
     *        + 调用本接口时，采集模式应为内部模式。在外部采集模式下调用无效，并将触发 onAudioDeviceWarning{@link #IRTCVideoEventHandler#onAudioDeviceWarning} 回调。<br>
     *        + 采集后，你还需要调用 publishScreen{@link #IRTCRoom#publishScreen} 将采集到的屏幕音频推送到远端。<br>
     *        + 要关闭屏幕音频内部采集，调用 stopScreenAudioCapture{@link #IRTCVideo#stopScreenAudioCapture}。
     */
    /**
     * @locale en
     * @hidden(Android,iOS,macOS)
     * @type api
     * @region screen sharing
     * @brief When sharing the screen, start using RTC SDK internal collection method to collect screen audio
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note  
     *         + The call of this API takes effects only when you are using RTC SDK to record screen. You will get a warning by onAudioDeviceWarning{@link #IRTCVideoEventHandler#onAudioDeviceWarning} after calling this API when the video source is set to an external recorder.<br>
     *         + After collection, you also need to call publishScreen{@link #IRTCRoom#publishScreen} to collect the screen audio Push to the far end. <br>
     *         + To turn off screen audio internal capture, call stopScreenAudioCapture{@link #IRTCVideo#stopScreenAudioCapture}.
     */
    virtual int startScreenAudioCapture() = 0;

    /**
     * @locale zh
     * @hidden(Windows,Linux,Android,iOS)
     * @type api
     * @region 屏幕共享
     * @brief 在屏幕共享时，开始使用 RTC SDK 内部采集方式，采集屏幕音频
     * @param device_id 虚拟设备 ID
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note 
     *        + 调用本接口时，采集模式应为内部模式。在外部采集模式下调用无效，并将触发 onAudioDeviceWarning{@link #IRTCVideoEventHandler#onAudioDeviceWarning} 回调。<br>
     *        + 采集后，你还需要调用 publishScreen{@link #IRTCRoom#publishScreen} 将采集到的屏幕音频推送到远端。<br>
     *        + 要关闭屏幕音频内部采集，调用 stopScreenAudioCapture{@link #IRTCVideo#stopScreenAudioCapture}。
     */
    /**
     * @locale en
     * @hidden(Windows,Linux,Android,iOS)
     * @type api
     * @region screen sharing
     * @brief When sharing the screen, start using RTC SDK internal collection method to collect screen audio
     * @param device_id ID of the virtual device
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note  
     *        + The call of this API takes effects only when you are using RTC SDK to record screen. You will get a warning by onAudioDeviceWarning{@link #IRTCVideoEventHandler#onAudioDeviceWarning} after calling this API when the video source is set to an external recorder.<br>
     *        + After collection, you also need to call publishScreen{@link #IRTCRoom#publishScreen} to collect the screen audio Push to the far end. <br>
     *        + To turn off screen audio internal capture, call stopScreenAudioCapture{@link #IRTCVideo#stopScreenAudioCapture}.
     */
    virtual int startScreenAudioCapture(const char device_id[MAX_DEVICE_ID_LENGTH]) = 0;

    /**
     * @locale zh
     * @hidden(Android,iOS)
     * @type api
     * @region 屏幕共享
     * @brief 在屏幕共享时，停止使用 RTC SDK 内部采集方式，采集屏幕音频。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note 
     *        + 调用本接口时，采集模式应为内部模式。在外部采集模式下调用无效，并将触发 onAudioDeviceWarning{@link #IRTCVideoEventHandler#onAudioDeviceWarning} 回调。<br>
     *        + 本接口仅对内部采集生效。如果为外部采集模式，调用本接口失败。你需要在外部采集器中实现停止采集的逻辑。<br>
     *        + 要开始屏幕音频内部采集，调用 startScreenAudioCapture{@link #IRTCVideo#startScreenAudioCapture}。
     */
    /**
     * @locale en
     * @hidden(Android,iOS)
     * @type api
     * @region Screen sharing
     * @brief Stop RTC SDK's device audio recorder.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note  
     *         + The call of this API takes effects only when you are using RTC SDK to record screen. You will get a warning by onAudioDeviceWarning{@link #IRTCVideoEventHandler#onAudioDeviceWarning} after calling this API when the video source is set to an external recorder.<br>
     *        + This API can only stop the screen capture by the RTC SDK. If the video source has been set to external recorder, the call of this API will fail with a warning message. You need to stop it in the external recorder. <br>
     *        + To start the device audio recording, call startScreenAudioCapture{@link #IRTCVideo#startScreenAudioCapture}.
     */
    virtual int stopScreenAudioCapture() = 0;

    /**
     * @locale zh
     * @hidden(Linux)
     * @type api
     * @region 屏幕共享
     * @brief 使用自定义采集方式，采集屏幕共享时的屏幕音频时，将音频帧推送至 RTC SDK 处进行编码等处理。
     * @param frame 音频数据帧，参见 IAudioFrame{@link #IAudioFrame}<br>
     *                   + 音频采样格式为 S16。音频缓冲区内的数据格式必须为 PCM 数据，其容量大小应该为 samples × frame.channel × 2。  <br>
     *                   + 必须指定具体的采样率和声道数，不支持设置为自动。
     * @return 方法调用结果  <br>
     *        + 0: 设置成功  <br>
     *        + < 0: 设置失败  
     * @note  
     *        + 调用此接口推送屏幕共享时的自定义采集的音频数据前，必须调用 setScreenAudioSourceType{@link #IRTCVideo#setScreenAudioSourceType} 开启屏幕音频自定义采集。  <br>
     *        + 你应每隔 10 毫秒，调用一次此方法推送一次自定义采集的音频帧。一次推送的音频帧中应包含 frame.sample_rate / 100 个音频采样点。比如，假如采样率为 48000Hz，则每次应该推送 480 个采样点。  <br>
     *        + 调用此接口将自定义采集的音频帧推送到 RTC SDK 后，你必须调用 publishScreen{@link #IRTCRoom#publishScreen} 将采集到的屏幕音频推送到远端。在调用 publishScreen{@link #IRTCRoom#publishScreen} 前，推送到 RTC SDK 的音频帧信息会丢失。
     */
    /**
     * @locale en
     * @hidden(Linux)
     * @type api
     * @region Screen Sharing
     * @brief Using a custom capture method, when capturing screen audio during screen sharing, push the audio frame to the RTC SDK for encoding and other processing.
     * @param frame Audio data frame. See IAudioFrame{@link #IAudioFrame}
     * @return  Method call result   <br>
     *         + 0: Setup succeeded <br>
     *         + < 0: Setup failed 
     * @note   
     *         + Before calling this interface to push custom collected audio data during screen sharing, you must call setScreenAudioSourceType{@link #IRTCVideo#setScreenAudioSourceType} Enable custom capture of screen audio. <br>
     *         + You should call this method every 10 milliseconds to push a custom captured audio frame. A push audio frame should contain frame.sample _rate/100 audio sample points. For example, if the sampling rate is 48000Hz, 480 sampling points should be pushed each time. <br>
     *         + The audio sampling format is S16. The data format in the audio buffer must be PCM data, and its capacity size should be samples × frame.channel × 2. <br>
     *         + After calling this interface to push the custom captured audio frame to the RTC SDK, you must call publishScreen{@link #IRTCRoom#publishScreen} to push the captured screen audio to the remote end. Audio frame information pushed to the RTC SDK is lost before calling publishScreen{@link #IRTCRoom#publishScreen}.
     */
    virtual int pushScreenAudioFrame(IAudioFrame* frame) = 0;

    /**
     * @locale zh
     * @type api
     * @brief 在听众端，设置订阅的所有远端音频流精准对齐后播放。
     * @param stream_key 作为对齐基准的远端音频流。参看 RemoteStreamKey{@link #RemoteStreamKey}。<br>
     *                  一般选择主唱的音频流。<br>
     *                  你必须在收到 onUserPublishStream{@link #IRTCRoomEventHandler#onUserPublishStream}，确认此音频流已发布后，调用此 API。
     * @param mode 是否对齐，默认不对齐。参看 AudioAlignmentMode{@link #AudioAlignmentMode}。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note 
     *        + 你必须在实时合唱场景下使用此功能。在加入房间时，所有人应设置 RoomProfileType{@link #RoomProfileType} 为 `kRoomProfileTypeChorus`。<br>
     *        + 订阅的所有远端流必须通过 startAudioMixing{@link #IAudioMixingManager#startAudioMixing} 开启了背景音乐混音，并将 AudioMixingConfig{@link #AudioMixingConfig} 中的 `sync_progress_to_record_frame` 设置为 `true`。<br>
     *        + 如果订阅的某个音频流延迟过大，可能无法实现精准对齐。<br>
     *        + 合唱的参与者不应调用此 API，因为调用此 API 会增加延迟。如果希望从听众变为合唱参与者，应关闭对齐功能。
     */
    /**
     * @locale en
     * @type api
     * @brief On the listener side, set all subscribed audio streams precisely timely aligned.
     * @param stream_key The remote audio stream used as the benchmark during time alignment. See RemoteStreamKey{@link #RemoteStreamKey}. <br>
     *                  You are recommended to use the audio stream from the lead singer. <br>
     *                  You must call this API after receiving onUserPublishStream{@link #IRTCRoomEventHandler#onUserPublishStream}.
     * @param mode Whether to enable the alignment. Disabled by default. See AudioAlignmentMode{@link #AudioAlignmentMode}.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note 
     *        + You must use the function when all participants set RoomProfileType{@link #RoomProfileType} to `kRoomProfileTypeChorus` when joining the room. <br>
     *        + All remote participants must call startAudioMixing{@link #IAudioMixingManager#startAudioMixing} to play background music and set `sync_progress_to_record_frame` of AudioMixingConfig{@link #AudioMixingConfig} to `true`. <br>
     *        + If the subscribed audio stream is delayed too much, it may not be precisely aligned. <br>
     *        + The chorus participants must not enable the alignment. If you wish to change the role from listener to participant, you should disable the alignment.
     */
    virtual int setAudioAlignmentProperty(const RemoteStreamKey& stream_key, AudioAlignmentMode mode) = 0;

    /**
     * @locale zh
     * @hidden(macOS,Windows,Android,Linux)
     * @type api
     * @region 屏幕共享
     * @brief 设置 Extension 配置项
     * @param group_id App 和 Extension 应该归属于同一个 App Group，此处需要传入 Group Id
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note 该函数必须在 sharedEngineWithAppId 函数之后立即调用。如果不调用或者调用时机比较晚，本地用户会收到 onMediaDeviceStateChanged{@link #ByteRTCVideoEventHandler#onMediaDeviceStateChanged} 的回调。 <br>
     *        参数 device_state 值为 ByteRTCMediaDeviceStateStopped，device_error 值为 `ByteRTCMediaDeviceErrorNotFindGroupId`
     */
    /**
     * @locale en
     * @hidden(macOS,Windows,Android,Linux)
     * @type api
     * @region screen sharing
     * @brief set extension configuration
     * @param group_id App and extension should belong to the same app group. Group ID needs to be passed in here
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note This function must be called immediately after the sharedenginewithappid function. If it is not called or the call time is late, local users will receive a callback to onMediaDeviceStateChanged{@link #ByteRTCVideoEventHandler#onMediaDeviceStateChanged}. <br>
     *        Parameter device_state value is ByteRTCMediaDeviceStateStopped, device_error value is `ByteRTCMediaDeviceErrorNotFindGroupId`.
     */
    virtual int setExtensionConfig(const char* group_id) = 0;

    /**
     * @locale zh
     * @hidden(macOS,Windows,Android,Linux)
     * @type api
     * @region 屏幕共享
     * @brief 发送屏幕共享 Extension 程序消息
     * @param message :发送给 Extension 程序的消息内容
     * @param size :message 大小
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note 该函数必须在 startScreenCapture 函数之后调用
     */
    /**
     * @locale en
     * @hidden(macOS,Windows,Android,Linux)
     * @type api
     * @region  screen sharing
     * @brief send screen sharing extension program message
     * @param message:  Message content sent to extension program
     * @param size : size of message
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note This function must be called after the startScreenCapture function
     */
    virtual int sendScreenCaptureExtensionMessage(const char* message, size_t size) = 0;

    /**
     * @locale zh
     * @hidden(macOS,Windows,Android,Linux)
     * @type api
     * @region 屏幕共享
     * @brief 开启本地屏幕共享数据采集
     * @param type 屏幕共享数据采集类型
     * @param bundle_id 传入 Broadcast Upload Extension 的 Bundle Id，用于在设置中优先展示 Extension
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note 当从 ios 控制中心异常启动 Extension 时可以不用调用本函数 <br>
     *       本地用户会收到 onMediaDeviceStateChanged{@link #ByteRTCVideoEventHandler#onMediaDeviceStateChanged} 的回调。 <br>
     *       参数 device_state 值为 ByteRTCMediaDeviceStateStarted，device_error 值为 ByteRTCMediaDeviceErrorOK
     */
    /**
     * @locale en
     * @hidden(macOS,Windows,Android,Linux)
     * @type api
     * @region  screen sharing
     * @brief  start local screen shared data collection
     * @param type screen shared data collection type
     * @param bundleId the bundle ID of the broadcast upload extension passed in, which is used to display the extension preferentially in settings
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note when the extension is started abnormally from the IOS control center, you don't need to call this function <br>
     *       local users will receive a callback to onMediaDeviceStateChanged{@link #ByteRTCVideoEventHandler#onMediaDeviceStateChanged}. <br>
     *       Parameter  device_state value is ByteRTCMediaDeviceStateStarted, device_error value is ByteRTCMediaDeviceErrorOK
     */
    virtual int startScreenCapture(ScreenMediaType type, const char* bundle_id) = 0;

    /**
     * @locale zh
     * @hidden(macOS,Windows,iOS,Linux)
     * @type api
     * @region 屏幕共享
     * @brief 通过传入的Type和Context开启屏幕音视频内部采集。
     * @param type<br>
     *        指定的屏幕媒体采集类型，参看ScreenMediaType{@link #ScreenMediaType}
     * @param context<br>
     *        Android平台传入Intent对象，由业务方申请系统录屏权限后获得。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note 
     *        + 采集后，你还需要调用 publishScreen {@link #IRtcRoom#publishScreen} 将采集到的屏幕音视频推送到远端。<br>
     *        + 开启屏幕音视频内部采集，Android专用接口。
     */
    /**
     * @locale en
     * @hidden(macOS,Windows,iOS,Linux)
     * @type api
     * @region  Screen sharing
     * @brief  Start to capture screen audio/video through the incoming Type and Context.
     * @param type<br>
     *        specifying the media type of screen capture，see ScreenMediaType{@link #ScreenMediaType}
     * @param context<br>
     *        Android platform incoming Intent object, obtained by the business party after applying for system recording permission.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note  
     *        + After collection, you also need to call publishScreen {@link #IRtcRoom#publishScreen} to collect the screen audio/vieo Push to the far end. <br>
     *        + Enable internal screen audio/video capture, Android-specific interface.
     */
    virtual int startScreenCapture(ScreenMediaType type, void* context) = 0;

    /**
     * @locale zh
     * @hidden(macOS,Windows,Linux)
     * @type api
     * @region 屏幕共享
     * @brief 停止本地屏幕共享数据采集
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     */
    /**
     * @locale en
     * @hidden(macOS,Windows,Linux)
     * @type api
     * @region  screen sharing
     * @brief  stop local screen shared data collection
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     */
    virtual int stopScreenCapture() = 0;

    /**
     * @locale zh
     * @deprecated since 3.52, will be deleted in 3.58, using startPushMixedStreamToCDN{@link #IRTCVideo#startPushMixedStreamToCDN} instead.
     * @hidden(Linux) not available
     * @type api
     * @region 多房间
     * @brief 新增转推直播任务，并设置合流的图片、视频视图布局和音频属性。  <br>
     *        同一个任务中转推多路直播流时，SDK 会先将多路流合成一路流，然后再进行转推。
     * @param task_id 转推直播任务 ID，长度不超过 126 字节。<br>
     *               你可以在同一房间内发起多个转推直播任务，并用不同的任务 ID 加以区分。当你需要发起多个转推直播任务时，应使用多个 ID；当你仅需发起一个转推直播任务时，建议使用空字符串。
     * @param param 转推直播配置参数。参看 ITranscoderParam{@link #ITranscoderParam}。
     * @param observer 端云一体转推直播观察者。参看 ITranscoderObserver{@link #ITranscoderObserver}。  <br>
     *        通过注册 observer 接收转推直播相关的回调。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note  
     *       + 在调用该接口前，你需要在[控制台](https://console.volcengine.com/rtc/workplaceRTC)开启转推直播功能。      <br>
     *       + 调用该方法后，关于启动结果和推流过程中的错误，会收到 onStreamMixingEvent{@link #ITranscoderObserver#onStreamMixingEvent} 回调。<br>
     *       + 调用 stopLiveTranscoding{@link #IRTCVideo#stopLiveTranscoding} 停止转推直播。
     */
    /**
     * @locale en
     * @deprecated since 3.52, will be deleted in 3.58, using startPushMixedStreamToCDN{@link #IRTCVideo#startPushMixedStreamToCDN} instead.
     * @hidden(Linux) not available
     * @type api
     * @region Multi-room
     * @brief Create a new task of pushing media streams to CDN and sets the relevant configurations.  <br>
     *        When pushing more than one live streams in the same task, SDK will first mix those streams into one single stream and then push it to CDN.
     * @param task_id Task ID. The length should not exceed 126 bytes.<br>
     *        You may want to push more than one mixed stream to CDN from the same room. When you do that, use different ID for corresponding tasks; if you will start only one task, use an empty string.
     * @param param Configurations to be set when pushing streams to CDN. See ITranscoderParam{@link #ITranscoderParam}.
     * @param observer Register this observer to receive callbacks from the SDK. See ITranscoderObserver{@link #ITranscoderObserver}.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note   
     *       + Before calling this API，you need to enable Push to CDN on the [console](https://console.byteplus.com/rtc/workplaceRTC).  <br>
     *       + After calling this API, you will be informed of the result and errors during the pushing process via the onStreamMixingEvent{@link #ITranscoderObserver#onStreamMixingEvent} callback.<br>
     *       + Call stopLiveTranscoding{@link #IRTCVideo#stopLiveTranscoding} to stop pushing streams to CDN.
     */
    BYTERTC_DEPRECATED virtual int startLiveTranscoding(const char* task_id, ITranscoderParam* param, ITranscoderObserver* observer) = 0;

    /**
     * @locale zh
     * @deprecated since 3.52, will be deleted in 3.58, using stopPushStreamToCDN{@link #IRTCVideo#stopPushStreamToCDN} instead.
     * @hidden(Linux) not available
     * @type api
     * @region 多房间
     * @brief 停止转推直播，会收到 onStreamMixingEvent{@link #ITranscoderObserver#onStreamMixingEvent} 回调。  <br>
     *        关于启动转推直播，参看 startLiveTranscoding{@link #IRTCVideo#startLiveTranscoding}。
     * @param task_id 转推直播任务 ID。可以指定想要停止的转推直播任务。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     */
    /**
     * @locale en
     * @deprecated since 3.52, will be deleted in 3.58, using stopPushStreamToCDN{@link #IRTCVideo#stopPushStreamToCDN} instead.
     * @hidden(Linux) not available
     * @type api
     * @region Multi-room
     * @brief Stops pushing media streams to CDN. You will be informed of the change via the onStreamMixingEvent{@link #ITranscoderObserver#onStreamMixingEvent} callback. <br>
     *        For starting pushing media streams to CDN, see startLiveTranscoding{@link #IRTCVideo#startLiveTranscoding}.
     * @param task_id Task ID. Specifys which pushing task you want to stop.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     */
    BYTERTC_DEPRECATED virtual int stopLiveTranscoding(const char* task_id) = 0;

    /**
     * @locale zh
     * @deprecated since 3.52, will be deleted in 3.58, using updatePushMixedStreamToCDN{@link #IRTCVideo#updatePushMixedStreamToCDN} instead.
     * @hidden(Linux) not available
     * @type api
     * @region 多房间
     * @brief 更新转推直播参数，会收到 onStreamMixingEvent{@link #ITranscoderObserver#onStreamMixingEvent} 回调。  <br>
     *        使用 startLiveTranscoding{@link #IRTCVideo#startLiveTranscoding} 启用转推直播功能后，使用此方法更新功能配置参数。
     * @param task_id 转推直播任务 ID。指定想要更新参数设置的转推直播任务。
     * @param param 转推直播配置参数，参看 ITranscoderParam{@link #ITranscoderParam}。除特殊说明外，均支持过程中更新。<br>
     *                   调用时，结构体中没有传入值的属性，会被更新为默认值。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     */
    /**
     * @locale en
     * @deprecated since 3.52, will be deleted in 3.58, using updatePushMixedStreamToCDN{@link #IRTCVideo#updatePushMixedStreamToCDN} instead.
     * @hidden(Linux) not available
     * @type api
     * @region Multi-room
     * @brief Update parameters needed when pushing media streams to CDN.  You will be informed of the change via the onStreamMixingEvent{@link #ITranscoderObserver#onStreamMixingEvent} callback. <br>
     *        After calling startLiveTranscoding{@link #IRTCVideo#startLiveTranscoding} to enable the function of pushing streams to CDN, you can call this API to update the relevant configurations.
     * @param task_id Task ID. Specifys of which pushing task you want to update the parameters.
     * @param param Configurations that you want to update. See ITranscoderParam{@link #ITranscoderParam} for specific indications. You can update any property for the task unless it is specified as unavailable for updates.<br>
     *                   If you left some properties blank, you can expect these properties to be set to their default values.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     */
    BYTERTC_DEPRECATED virtual int updateLiveTranscoding(const char* task_id, ITranscoderParam* param) = 0;

    /**
     * @locale zh
     * @valid since 3.52
     * @hidden(Linux) not available
     * @type api
     * @region 多房间
     * @brief 新增合流转推直播任务，并设置合流的图片、视频视图布局和音频属性。  <br>
     *        同一个任务中转推多路直播流时，SDK 会先将多路流合成一路流，然后再进行转推。
     * @param task_id 转推直播任务 ID，长度不超过 126 字节。<br>
     *        你可以在同一房间内发起多个转推直播任务，并用不同的任务 ID 加以区分。当你需要发起多个转推直播任务时，应使用多个 ID；当你仅需发起一个转推直播任务时，建议使用空字符串。
     * @param config 转推直播配置参数。参看 IMixedStreamConfig{@link #IMixedStreamConfig}。
     * @param observer 端云一体转推直播观察者。参看 IMixedStreamObserver{@link #IMixedStreamObserver}。  <br>
     *        通过注册 observer 接收转推直播相关的回调。
     * @return 
     *        + 0: 成功<br>
     *        + !0: 失败
     * @note  
     *       + 在调用该接口前，你需要在[控制台](https://console.volcengine.com/rtc/workplaceRTC)开启转推直播功能。<br>
     *       + 调用该方法后，关于启动结果和推流过程中的错误，会收到 onMixingEvent{@link #IMixedStreamObserver#onMixingEvent} 回调。<br>
     *       + 如果已在[控制台](https://console.volcengine.com/rtc/cloudRTC?tab=callback)配置了转推直播的服务端回调，调用本接口会收到 [TranscodeStarted](https://www.volcengine.com/docs/6348/75125#transcodestarted)。重复调用该接口时，第二次调用会同时触发 [TranscodeStarted](https://www.volcengine.com/docs/6348/75125#transcodestarted) 和 [TranscodeUpdated](https://www.volcengine.com/docs/6348/75125#transcodeupdated)。<br>
     *       + 调用 stopPushStreamToCDN{@link #IRTCVideo#stopPushStreamToCDN} 停止转推直播。
     */
    /**
     * @locale en
     * @valid since 3.52
     * @hidden(Linux) not available
     * @type api
     * @region Multi-room
     * @brief Create a new task of pushing mixed media streams to CDN and sets the relevant configurations.  <br>
     *        When pushing more than one live streams in the same task, SDK will first mix those streams into one single stream and then push it to CDN.
     * @param task_id Task ID. The length should not exceed 126 bytes.<br>
     *        You may want to push more than one mixed stream to CDN from the same room. When you do that, use different ID for corresponding tasks; if you will start only one task, use an empty string.
     * @param config Configurations to be set when pushing streams to CDN. See IMixedStreamConfig{@link #IMixedStreamConfig}.
     * @param observer Register this observer to receive callbacks from the SDK. See IMixedStreamObserver{@link #IMixedStreamObserver}.
     * @return 
     *        + 0: Success<br>
     *        + !0: Failure
     * @note   
     *       + Before calling this API，you need to enable Push to CDN on the [console](https://console.byteplus.com/rtc/workplaceRTC).     <br>
     *       + After calling this API, you will be informed of the result and errors during the pushing process via the onMixingEvent{@link #IMixedStreamObserver#onMixingEvent} callback.<br>
     *       + If you have subscribed to the push-to-CDN server callback in the [console](https://console.byteplus.com/rtc/cloudRTC?tab=callback), calling this API will receive a [TranscodeStarted](https://docs.byteplus.com/en/byteplus-rtc/docs/75125#transcodestarted) server callback notification. When calling this API repeatedly, subsequent calls to this API will trigger both [TranscodeStarted](https://docs.byteplus.com/en/byteplus-rtc/docs/75125#transcodestarted) and [TranscodeUpdated](https://docs.byteplus.com/en/byteplus-rtc/docs/75125#transcodeupdated) callbacks.<br>
     *       + Call stopPushStreamToCDN{@link #IRTCVideo#stopPushStreamToCDN} to stop pushing streams to CDN.
     */
    virtual int startPushMixedStreamToCDN(const char* task_id, IMixedStreamConfig* config, IMixedStreamObserver* observer) = 0;
    /**
     * @locale zh
     * @valid since 3.52
     * @hidden(Linux) not available
     * @type api
     * @region 多房间
     * @brief 更新合流转推直播参数，会收到 onMixingEvent{@link #IMixedStreamObserver#onMixingEvent} 回调。  <br>
     *        使用 startPushMixedStreamToCDN{@link #IRTCVideo#startPushMixedStreamToCDN} 启用转推直播功能后，使用此方法更新功能配置参数。
     * @param task_id 转推直播任务 ID。指定想要更新参数设置的转推直播任务。
     * @param config 转推直播配置参数，参看 IMixedStreamConfig{@link #IMixedStreamConfig}。除特殊说明外，均支持过程中更新。<br>
     *        调用时，结构体中没有传入值的属性，会被更新为默认值。
     * @return 
     *        + 0: 成功<br>
     *        + !0: 失败
     */
    /**
     * @locale en
     * @valid since 3.52
     * @hidden(Linux) not available
     * @type api
     * @region Multi-room
     * @brief Update parameters needed when pushing mixed media streams to CDN.  You will be informed of the change via the onMixingEvent{@link #IMixedStreamObserver#onMixingEvent} callback. <br>
     *        After calling startPushMixedStreamToCDN{@link #IRTCVideo#startPushMixedStreamToCDN} to enable the function of pushing streams to CDN, you can call this API to update the relevant configurations.
     * @param task_id Task ID. Specifys of which pushing task you want to update the parameters.
     * @param config Configurations that you want to update. See IMixedStreamConfig{@link #IMixedStreamConfig} for specific indications. You can update any property for the task unless it is specified as unavailable for updates.<br>
     *        If you left some properties blank, you can expect these properties to be set to their default values.
     * @return 
     *        + 0: Success<br>
     *        + !0: Failure
     */
    virtual int updatePushMixedStreamToCDN(const char* task_id, IMixedStreamConfig* config) = 0;
    /**
     * @locale zh
     * @hidden(Linux)
     * @type api
     * @region 转推直播
     * @brief 新增单流转推直播任务。
     * @param task_id 任务 ID。<br>
     *               你可以发起多个转推直播任务，并用不同的任务 ID 加以区分。当你需要发起多个转推直播任务时，应使用多个 ID；当你仅需发起一个转推直播任务时，建议使用空字符串。
     * @param param 转推直播配置参数。详见 PushSingleStreamParam{@link #PushSingleStreamParam}。
     * @param observer 单流转推直播观察者。详见 IPushSingleStreamToCDNObserver{@link #IPushSingleStreamToCDNObserver}。  <br>
     *        通过注册 observer 接收单流转推直播相关的回调。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note  
     *       + 在调用该接口前，你需要在[控制台](https://console.volcengine.com/rtc/workplaceRTC)开启转推直播功能。     <br>
     *       + 调用该方法后，关于启动结果和推流过程中的错误，会收到 onStreamPushEvent{@link #IPushSingleStreamToCDNObserver#onStreamPushEvent} 回调。<br>
     *       + 调用 stopPushStreamToCDN{@link #IRTCVideo#stopPushStreamToCDN} 停止任务。<br>
     *       + 由于本功能不进行编解码，所以推到 RTMP 的视频流会根据推流端的分辨率、编码方式、关闭摄像头等变化而变化。
     */
    /**
     * @locale en
     * @hidden(Linux)
     * @type api
     * @region Push to CDN
     * @brief Create a new task of pushing a single media stream to CDN.
     * @param task_id Task ID. <br>
     *        You may want to start more than one task to push streams to CDN. When you do that, use different IDs for corresponding tasks; if you will start only one task, use an empty string.
     * @param param Configurations for pushing a single stream to CDN. See PushSingleStreamParam{@link #PushSingleStreamParam}.
     * @param observer Register this observer to receive callbacks from the SDK. See IPushSingleStreamToCDNObserver{@link #IPushSingleStreamToCDNObserver}.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note   
     *       + Before calling this API，you need to enable Push to CDN on the [console](https://console.byteplus.com/rtc/workplaceRTC).     <br>
     *       + After calling this API, you will be informed of the result and errors during the pushing process with onStreamPushEvent{@link #IPushSingleStreamToCDNObserver#onStreamPushEvent}.<br>
     *       + Call stopPushStreamToCDN{@link #IRTCVideo#stopPushStreamToCDN} to stop the task.<br>
     *       + Since this API does not perform encoding and decoding, the video stream pushed to RTMP will change according to the resolution, encoding method, and turning off the camera of the end of pushing streams.
     */
    virtual int startPushSingleStreamToCDN(const char* task_id, PushSingleStreamParam& param, IPushSingleStreamToCDNObserver* observer) = 0;

    /**
     * @locale zh
     * @hidden(Linux)
     * @type api
     * @region 转推直播
     * @brief 停止转推直播。<br>
     *        该方法可用于停止单流转推直播或停止合流转推直播，通过 taskId 区分需要停止的任务。
     * @param task_id 任务 ID。可以指定想要停止的单流转推直播或合流转推直播任务。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note 
     *        + 关于启动单流转推直播，参看 startPushSingleStreamToCDN{@link #IRTCVideo#startPushSingleStreamToCDN}。<br>
     *        + 关于启动合流转推直播，参看 startPushMixedStreamToCDN{@link #IRTCVideo#startPushMixedStreamToCDN}。
     */
    /**
     * @locale en
     * @hidden(Linux)
     * @type api
     * @region Push to CDN
     * @brief Stops the task to push a single media stream to CDN. <br>
     *        This API can be used to stop both pushing single and mixed stream to CDN. You need to distinguish the tasks to be stopped by different "taskId".
     * @param task_id Task ID. Specifys the task you want to stop.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note 
     *        + To start pushing single stream to CDN, see startPushSingleStreamToCDN{@link #IRTCVideo#startPushSingleStreamToCDN}.<br>
     *        + To start pushing mixed stream to CDN, see startPushMixedStreamToCDN{@link #IRTCVideo#startPushMixedStreamToCDN}.
     */
    virtual int stopPushStreamToCDN(const char* task_id) = 0;

    /**
      * @locale zh
      * @hidden internal use only
      * @type api
      * @brief 开启缓存同步功能。开启后，会缓存收到的实时音视频数据，并对齐不同数据中的时间戳完成同步。此功能会影响音视频数据消费的实时性。
      * @param config 参看 ChorusCacheSyncConfig{@link #ChorusCacheSyncConfig}。
      * @param observer 事件和数据观察者，参看 IChorusCacheSyncObserver{@link #IChorusCacheSyncObserver}。
      * @return 查看 ReturnStatus{@link #ReturnStatus}。
      * @note 要关闭缓存同步功能，调用 stopChorusCacheSync{@link #IRTCVideo#stopChorusCacheSync}。
      */
     /**
      * @locale en
      * @hidden internal use only
      * @type api
      * @brief Start aligning RTC data by cache. Received RTC data from different sources will be cached, and aligned based on the included timestamps. This feature compromizes the real-time nature of RTC data consumption.
      * @param config See ChorusCacheSyncConfig{@link #ChorusCacheSyncConfig}.
      * @param observer Event and data observer. See IChorusCacheSyncObserver{@link #IChorusCacheSyncObserver}.
      * @return See ReturnStatus{@link #ReturnStatus}.
      * @note To disable the feature, call stopChorusCacheSync{@link #IRTCVideo#stopChorusCacheSync}.
      */
    virtual int startChorusCacheSync(ChorusCacheSyncConfig * config, IChorusCacheSyncObserver* observer) = 0;
    /**
      * @locale zh
      * @hidden internal use only
      * @type api
      * @brief 关闭缓存同步功能。
      * @return 查看 ReturnStatus{@link #ReturnStatus}。
      */
     /**
      * @locale en
      * @hidden internal use only
      * @type api
      * @brief Stop aligning RTC data by cache.
      * @return See ReturnStatus{@link #ReturnStatus}.
      */
    virtual int stopChorusCacheSync() = 0;
  
    /**
     * @locale zh
     * @type api
     * @brief 发布一路公共流<br>
     *        用户可以指定房间内多个用户发布的媒体流合成一路公共流。使用同一 `appID` 的用户，可以调用 startPlayPublicStream{@link #IRTCVideo#startPlayPublicStream} 获取和播放指定的公共流。
     * @param public_stream_id 公共流 ID
     * @param param 公共流参数。详见 IPublicStreamParam{@link #IPublicStreamParam}。<br>
     *              一路公共流可以包含多路房间内的媒体流，按照指定的布局方式进行聚合。<br>
     *              如果指定的媒体流还未发布，则公共流将在指定流开始发布后实时更新。
     * @return
     *        + 0: 成功。同时将收到 onPushPublicStreamResult{@link #IRTCVideoEventHandler#onPushPublicStreamResult} 回调。<br>
     *        + !0: 失败。当参数不合法或参数为空，调用失败。
     * @note
     *        + 同一用户使用同一公共流 ID 多次调用本接口无效。如果你希望更新公共流参数，调用 updatePublicStreamParam{@link #IRTCVideo#updatePublicStreamParam} 接口。<br>
     *        + 不同用户使用同一公共流 ID 多次调用本接口时，RTC 将使用最后一次调用时传入的参数更新公共流。<br>
     *        + 使用不同的 ID 多次调用本接口可以发布多路公共流。<br>
     *        + 调用 stopPushPublicStream{@link #IRTCVideo#stopPushPublicStream} 停止发布公共流。<br>
     *        + 关于公共流功能的介绍，详见[发布和订阅公共流](https://www.volcengine.com/docs/6348/108930)
     */
    /**
     * @locale en
     * @hidden currently not available
     * @type api
     * @brief Start publishing a public media stream.<br>
     *        A public stream refers to a media stream that does not belong to any room or any user. Users within the same `appID` can call startPlayPublicStream{@link #IRTCVideo#startPlayPublicStream} to subscribe to the public stream regardless the user has joined which room or has not joined any room.
     * @param public_stream_id ID of the public stream
     * @param param Properties of the public stream. Refer to IPublicStreamParam{@link #IPublicStreamParam} for more details.<br>
     *              A public stream can include a bundle of media streams and appears as the designated layout.
     * @return 
     *        + 0: Success. And you will be informed by onPushPublicStreamResult{@link #IRTCVideoEventHandler#onPushPublicStreamResult}. <br>
     *        + !0: Failure because of invalid parameter or empty parameters.
     * @note 
     *        + Call updatePublicStreamParam{@link #IRTCVideo#updatePublicStreamParam} to update the properties of the public stream which is published by the same user. Calling this API with the same stream ID repeatedly by the same user can not update the existing public stream.<br>
     *        + If Users with different userID call this API with the same stream ID, the public stream will be updated with the parameters passed in the latest call.<br>
     *        + To publish multiple public streams, call this API with different stream ID respectively.<br>
     *        + To stop publishing the public stream, call stopPushPublicStream{@link #IRTCVideo#stopPushPublicStream}.<br>
     *        + Please contact ts to enable this function before using it.
     */
    virtual int startPushPublicStream(const char* public_stream_id, IPublicStreamParam* param) = 0;
    /**
     * @locale zh
     * @type api
     * @brief 停止发布当前用户发布的公共流<br>
     *        关于发布公共流，查看 startPushPublicStream{@link #IRTCVideo#startPushPublicStream}。
     * @param public_stream_id 公共流 ID<br>
     *                  指定的流必须为当前用户所发布。
     * @return 
     *        + 0: 成功<br>
     *        + !0: 失败
     */
    /**
     * @locale en
     * @hidden currently not available.
     * @type api
     * @brief Stop the public stream published by the current user.<br>
     *        Refer to startPushPublicStream{@link #IRTCVideo#startPushPublicStream} for details about starting publishing a public stream.
     * @param public_stream_id ID of the public stream<br>
     *                  The public stream must be published by the current user.
     * @return 
     *        + 0: Success<br>
     *        + !0: Failure
     */
    virtual int stopPushPublicStream(const char* public_stream_id) = 0;

    /**
     * @locale zh
     * @type api
     * @brief 更新公共流参数<br>
     *        关于发布公共流，查看 startPushPublicStream{@link #IRTCVideo#startPushPublicStream}。
     * @param public_stream_id 公共流 ID
     * @param param 公共流参数。详见 IPublicStreamParam{@link #IPublicStreamParam}。<br>
     *              指定的流必须为当前用户所发布的。
     * @return 
     *        + 0: 成功<br>
     *        + !0: 失败
     * @note 调用本接口前需要通过 onPushPublicStreamResult{@link #IRTCVideoEventHandler#onPushPublicStreamResult} 确认公共流是否已经成功启动。
     */
    /**
     * @locale en
     * @hidden currently not available.
     * @type api
     * @brief Update the properties of the public stream published by the current user.<br>
     *        Refer to startPushPublicStream{@link #IRTCVideo#startPushPublicStream} for details about starting publishing a public stream.
     * @param public_stream_id ID of the public stream
     * @param param Properties of the public stream. Refer to IPublicStreamParam{@link #IPublicStreamParam} for more details.<br>
     *              The stream to be updated must be published by the current user.
     * @return 
     *        + 0: Success<br>
     *        + !0: Failure
     * @note Make sure the public stream has started successfully via onPushPublicStreamResult{@link #IRTCVideoEventHandler#onPushPublicStreamResult} before calling this API.
     */
    virtual int updatePublicStreamParam(const char* public_stream_id, IPublicStreamParam* param) = 0;


    /**
     * @locale zh
     * @hidden(macOS,Windows,Linux)
     * @type api
     * @region 屏幕共享
     * @brief 更新屏幕采集数据类型
     * @param type 屏幕采集数据类型
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note 该函数必须在 startScreenCapture 函数之后调用。本地用户会收到 onMediaDeviceStateChanged{@link #ByteRTCVideoEventHandler#onMediaDeviceStateChanged} 的回调。 <br>
     *        参数 device_state 值为 ByteRTCMediaDeviceStateStarted 或 ByteRTCMediaDeviceStateStopped，device_error 值为 ByteRTCMediaDeviceErrorOK。
     */
    /**
     * @locale en
     * @hidden(macOS,Windows,Linux)
     * @type api
     * @region  screen sharing
     * @brief  update screen acquisition data type
     * @param type screen acquisition data type
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note This API must be called after the startScreenCapture function. Local users will receive a callback to onMediaDeviceStateChanged{@link #ByteRTCVideoEventHandler#onMediaDeviceStateChanged}. <br>
     *        Parameter device_state value is ByteRTCMediaDeviceStateStarted or ByteRTCMediaDeviceStateStopped, device_error value is ByteRTCMediaDeviceErrorOK.
     */
    virtual int updateScreenCapture(ScreenMediaType type) = 0;

     /**
      * @locale zh
      * @type api
      * @region 音频管理
      * @brief 启用音频信息提示。开启提示后，你会收到 onLocalAudioPropertiesReport{@link #IRTCVideoEventHandler#onLocalAudioPropertiesReport}，onRemoteAudioPropertiesReport{@link #IRTCVideoEventHandler#onRemoteAudioPropertiesReport} 和 onActiveSpeaker{@link #IRTCVideoEventHandler#onActiveSpeaker}。
      * @param config 详见 AudioPropertiesConfig{@link #AudioPropertiesConfig}
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
      */
     /**
      * @locale en
      * @type api
      * @region Audio Management
      * @brief Enable audio information prompts. After that, you will receive onLocalAudioPropertiesReport{@link #IRTCVideoEventHandler#onLocalAudioPropertiesReport}, onRemoteAudioPropertiesReport{@link #IRTCVideoEventHandler#onRemoteAudioPropertiesReport}, and onActiveSpeaker{@link #IRTCVideoEventHandler#onActiveSpeaker}.
      * @param config See AudioPropertiesConfig{@link #AudioPropertiesConfig}
      * @return  
      *        + 0: Success.<br>
      *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
      */
    virtual int enableAudioPropertiesReport(const AudioPropertiesConfig& config) = 0;

    /**
     * @locale zh
     * @type api
     * @region 多房间
     * @brief 调节来自指定远端用户的音频播放音量。
     * @param room_id 音频来源用户所在的房间 ID
     * @param user_id 音频来源的远端用户 ID
     * @param volume 音频播放音量值和原始音量的比值，范围是 [0, 400]，单位为 %，自带溢出保护。为保证更好的通话质量，建议将 volume 值设为 [0,100]。 <br>
     *                    只改变音频数据的音量信息，不涉及本端硬件的音量调节。<br>
     *              + 0: 静音  <br>
     *              + 100: 原始音量，默认值  <br>
     *              + 400: 最大可为原始音量的 4 倍(自带溢出保护)  
     * @return 方法调用结果：<br>
     *        + 0：成功；<br>
     *        + <0：失败。具体失败原因参看 ReturnStatus{@link #ReturnStatus}。
     * @note 假设某远端用户 A 始终在被调节的目标用户范围内，<br>
     *        + 当该方法与 setRemoteRoomAudioPlaybackVolume{@link #IRTCRoom#setRemoteRoomAudioPlaybackVolume} 共同使用时，本地收听用户 A 的音量为后调用的方法设置的音量；<br>
     *        + 当该方法与 setPlaybackVolume{@link #IRTCVideo#setPlaybackVolume} 方法共同使用时，本地收听用户 A 的音量将为两次设置的音量效果的叠加。
     */
    /**
     * @locale en
     * @type api
     * @region  multi-room
     * @brief Adjusts the audio playback volume of the specified remote user.
     * @param room_id ID of the room from which the remote audio source is published.
     * @param user_id  The remote user ID of the audio source
     * @param volume Ratio(%) of playback volume to original volume, in the range [0, 400], with overflow protection.  <br>
     *                    This changes the volume property of the audio data other than the hardware volume.<br>
     *               To ensure the audio quality, we recommend setting the volume to `100`.  <br>
     *               + 0: mute <br>
     *               + 100: original volume. Default value. <br>
     *               + 400: Up to 4 times the original volume (with overflow protection)
     * @return API call result:<br>
     *        + 0: Success.<br>
     *        + <0: Failure. See ReturnStatus{@link #ReturnStatus} for specific reasons.
     * @note Suppose a remote user A is always within the range of the target user whose playback volume will be adjusted,<br>
     *        + If you use both this method and setRemoteRoomAudioPlaybackVolume{@link #IRTCRoom#setRemoteRoomAudioPlaybackVolume}, the volume that the local user hears from user A is the volume set by the method called later.<br>
     *        + If you use both this method and setPlaybackVolume{@link #IRTCVideo#setPlaybackVolume}, the volume that the local user hears from user A is the overlay of both settings.
     */
    virtual int setRemoteAudioPlaybackVolume(const char* room_id,const char* user_id, int volume) = 0;

    /**
     * @locale zh
     * @type api
     * @region 音频管理
     * @brief 开启/关闭音量均衡功能。  <br>
     *        开启音量均衡功能后，人声的响度会调整为 -16lufs。如果已调用 setAudioMixingLoudness{@link #IAudioMixingManager#setAudioMixingLoudness} 传入了混音音乐的原始响度，此音乐播放时，响度会调整为 -20lufs。（Linux 不支持）
     * @param enable 是否开启音量均衡功能：  <br>
     *       + true: 是  <br>
     *       + false: 否
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note 该接口须在调用 startAudioMixing{@link #IAudioMixingManager#startAudioMixing} 开始播放音频文件之前调用。
     */
    /**
     * @locale en
     * @type api
     * @region Audio Management
     * @brief Enables/disables the loudness equalization function.  <br>
     *        If you call this API with the parameter set to True, the loudness of user's voice will be adjusted to -16lufs. If then you also call setAudioMixingLoudness{@link #IAudioMixingManager#setAudioMixingLoudness} and import the original loudness of the audio data used in audio mixing, the loudness will be adjusted to -20lufs when the audio data starts to play.
     * @param enable Whether to enable loudness equalization function:  <br>
     *        + true: Yes <br>
     *        + false: No
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note You must call this API before starting to play the audio file with startAudioMixing{@link #IAudioMixingManager#startAudioMixing}.
     */
    virtual int enableVocalInstrumentBalance(bool enable) = 0;

    /**
     * @locale zh
     * @type api
     * @region 音频管理
     * @brief 打开/关闭音量闪避功能，适用于在 RTC 通话过程中会同时播放短视频或音乐的场景，如“一起看”、“在线 KTV”等。  <br>
     *        开启该功能后，当检测到远端人声时，本地的媒体播放音量会自动减弱，从而保证远端人声的清晰可辨；当远端人声消失时，本地媒体音量会恢复到闪避前的音量水平。
     * @param enable 是否开启音量闪避：  <br>
     *        + true: 是  <br>
     *        + false: 否
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     */
    /**
     * @locale en
     * @type api
     * @region Audio Management
     * @brief Enables/disables the playback ducking function. This function is usually used in scenarios where short videos or music will be played simultaneously during RTC calls. <br>
     *        With the function on, if remote voice is detected, the local media volume will be lowered to ensure the clarity of the remote voice. If remote voice disappears, the local media volume restores.
     * @param enable Whether to enable playback ducking:  <br>
     *        + true: Yes  <br>
     *        + false: No
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     */
    virtual int enablePlaybackDucking(bool enable) = 0;

    /**
     * @locale zh
     * @type api
     * @region 视频数据回调
     * @brief 注册本地视频帧监测器。  <br>
     *        无论使用内部采集还是自定义采集，调用该方法后，SDK 每监测到一帧本地视频帧时，都会将视频帧信息通过 onLocalEncodedVideoFrame{@link #ILocalEncodedVideoFrameObserver#onLocalEncodedVideoFrame} 回调给用户
     * @param observer 本地视频帧监测器，参看 ILocalEncodedVideoFrameObserver{@link #ILocalEncodedVideoFrameObserver}。将参数设置为 nullptr 则取消注册。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note 该方法可在进房前后的任意时间调用，在进房前调用可保证尽可能早地监测视频帧并触发回调
     */
    /**
     * @locale en
     * @type api
     * @region Video Data Callback
     * @brief Register a local video frame observer.   <br>
     *        This method applys to both internal capturing and custom capturing.  <br>
     *        After calling this API, SDK triggers onLocalEncodedVideoFrame{@link #ILocalEncodedVideoFrameObserver#onLocalEncodedVideoFrame} whenever a video frame is captured.
     * @param observer Local video frame observer. See ILocalEncodedVideoFrameObserver{@link #ILocalEncodedVideoFrameObserver}. You can cancel the registration by setting it to `nullptr`.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note You can call this API before or after entering the RTC room. Calling this API before entering the room ensures that video frames are monitored and callbacks are triggered as early as possible.
     */
    virtual int registerLocalEncodedVideoFrameObserver(ILocalEncodedVideoFrameObserver* observer) = 0;

    /**
     * @locale zh
     * @type api
     * @region 视频管理
     * @brief 注册远端编码后视频数据回调。  <br>
     *        完成注册后，当 SDK 监测到远端编码后视频帧时，会触发 onRemoteEncodedVideoFrame{@link #IRemoteEncodedVideoFrameObserver#onRemoteEncodedVideoFrame} 回调
     * @param observer 远端编码后视频数据监测器，参看 IRemoteEncodedVideoFrameObserver{@link #IRemoteEncodedVideoFrameObserver}
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note  
     *       + 更多自定义解码功能说明参看 [自定义视频编解码](https://www.volcengine.com/docs/6348/82921#%E8%87%AA%E5%AE%9A%E4%B9%89%E8%A7%86%E9%A2%91%E8%A7%A3%E7%A0%81)。<br>
     *       + 该方法适用于手动订阅，并且进房前后均可调用，建议在进房前调用。 <br>
     *       + 引擎销毁前需取消注册，调用该方法将参数设置为 nullptr 即可。
     */
    /**
     * @locale en
     * @type api
     * @region video management
     * @brief Video data callback after registering remote encoding.   <br>
     *         After registration, when the SDK detects a remote encoded video frame, it will trigger the onRemoteEncodedVideoFrame{@link #IRemoteEncodedVideoFrameObserver#onRemoteEncodedVideoFrame} callback
     * @param observer Remote encoded video data monitor. See IRemoteEncodedVideoFrameObserver{@link #IRemoteEncodedVideoFrameObserver}
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note 
     *        + See [Custom Video Encoding and Decoding](https://docs.byteplus.com/byteplus-rtc/docs/82921#custom-video-decoding) for more details about custom video decoding. <br>
     *        + This method applys to manual subscription mode and can be called either before or after entering the Room. It is recommended to call it before entering the room. <br>
     *        + The engine needs to be unregistered before it is destroyed. Call this method to set the parameter to nullptr.
     */
    virtual int registerRemoteEncodedVideoFrameObserver(IRemoteEncodedVideoFrameObserver* observer) = 0;

    /**
     * @locale zh
     * @type api
     * @region 视频管理
     * @brief 注册自定义编码帧推送事件回调
     * @param encoder_handler 自定义编码帧回调类，参看 IExternalVideoEncoderEventHandler{@link #IExternalVideoEncoderEventHandler}
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note  
     *       + 该方法需在进房前调用。 <br>
     *       + 引擎销毁前需取消注册，调用该方法将参数设置为 nullptr 即可。
     */
    /**
     * @locale en
     * @type api
     * @region Video management
     * @brief Register custom encoded frame push event callback
     * @param encoder_handler Custom encoded frame callback class. See IExternalVideoEncoderEventHandler{@link #IExternalVideoEncoderEventHandler}
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note   
     *        + This method needs to be called before entering the room. <br>
     *        + The engine needs to be unregistered before it is destroyed. Call this method to set the parameter to nullptr.
     */
    virtual int setExternalVideoEncoderEventHandler(IExternalVideoEncoderEventHandler* encoder_handler) = 0;

    /**
     * @locale zh
     * @type api
     * @region 视频管理
     * @brief 推送自定义编码后的视频流
     * @param index 需要推送的编码流的属性，参看 StreamIndex{@link #StreamIndex}
     * @param video_index 对应的编码流下标，从 0 开始，如果调用 setVideoEncoderConfig{@link #IRTCVideo#setVideoEncoderConfig} 设置了多路流，此处数量须与之保持一致
     * @param video_stream 编码流视频帧信息，参看 IEncodedVideoFrame{@link #IEncodedVideoFrame}。
     * @return 方法调用结果：<br>
     *        + 0：成功；<br>
     *        + <0：失败。具体失败原因参看 ReturnStatus{@link #ReturnStatus}。
     * @note  
     *        + 目前仅支持推送 H264 和 ByteVC1 格式的视频帧，且视频流协议格式须为 Annex B 格式。  <br>
     *        + 该函数运行在用户调用线程内  <br>
     *        + 推送自定义编码视频帧前，必须调用 setVideoSourceType{@link #IRTCVideo#setVideoSourceType} 将视频输入源切换至自定义编码视频源。
     */
    /**
     * @locale en
     * @type api
     * @region  video management
     * @brief Push custom encoded video stream
     * @param index The attributes of the encoded stream that need to be pushed. See StreamIndex{@link #StreamIndex}
     * @param video_index The corresponding encoded stream subscript, starting from 0, if you call setVideoEncoderConfig{@link #IRTCVideo#setVideoEncoderConfig} to set multiple streams, the number here must be consistent with it
     * @param video_stream Encoded stream video frame information. See IEncodedVideoFrame{@link #IEncodedVideoFrame}.
     * @return API call result:<br>
     *        + 0: Success.<br>
     *        + <0: Failure. See ReturnStatus{@link #ReturnStatus} for specific reasons.
     * @note  
     *         + Currently, only video frames in H264 and ByteVC1 formats are supported, and the video stream protocol must be in an Annex B format. <br>
     *         + This function runs within the user calling thread <br>
     *         + Before pushing a custom encoded video frame, you must call setVideoSourceType{@link #IRTCVideo#setVideoSourceType} to switch the video input source to the custom encoded video source.
     */
    virtual int pushExternalEncodedVideoFrame(StreamIndex index, int video_index, IEncodedVideoFrame* video_stream) = 0;

    /**
     * @locale zh
     * @type api
     * @region 视频管理
     * @brief 在订阅远端视频流之前，设置远端视频数据解码方式
     * @param key 远端流信息，即对哪一路视频流进行解码方式设置，参看 RemoteStreamKey{@link #RemoteStreamKey}。
     * @param config 视频解码方式，参看 VideoDecoderConfig{@link #VideoDecoderConfig}。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note  
     *        + 当你想要对远端流进行自定义解码时，你需要先调用 registerRemoteEncodedVideoFrameObserver{@link #IRTCVideo#registerRemoteEncodedVideoFrameObserver} 注册远端视频流监测器，然后再调用该接口将解码方式设置为自定义解码。监测到的视频数据会通过 onRemoteEncodedVideoFrame{@link #IRemoteEncodedVideoFrameObserver#onRemoteEncodedVideoFrame} 回调出来。<br>
     *        + 自 3.56 起，要用于自动订阅场景下，你可以设置 `key` 中的 `RoomId` 和 `UserId` 为 `nullptr`，此时，通过此接口设置的解码方式根据 `key` 中的 `StreamIndex` 值，适用于所有的远端主流或屏幕流的解码方式。
     */
    /**
     * @locale en
     * @type api
     * @region Video Management
     * @brief Before subscribing to the remote video stream, set the remote video data decoding method
     * @param key The remote stream information, that is, which video stream is decoded. See RemoteStreamKey{@link #RemoteStreamKey}.
     * @param config Video decoding method. See VideoDecoderConfig{@link #VideoDecoderConfig}.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note   
     *         + When you want to custom decode a remote stream, you need to call registerRemoteEncodedVideoFrameObserver{@link #IRTCVideo#registerRemoteEncodedVideoFrameObserver} to register the remote video stream monitor, and then call the interface to set the decoding method to custom decoding. The monitored video data will be called back through onRemoteEncodedVideoFrame{@link #IRemoteEncodedVideoFrameObserver#onRemoteEncodedVideoFrame}.<br>
     *         + Since version 3.56, for automatic subscription, you can set the `RoomId` and `UserId` of `key` as `nullptr`. In this case, the decoding settings set by calling the API applies to all remote main streams or screen sharing streams based on the `StreamIndex` value of `key`.
     */
    virtual int setVideoDecoderConfig(RemoteStreamKey key, VideoDecoderConfig config) = 0;

    /**
     * @locale zh
     * @type api
     * @region 视频管理
     * @brief 在订阅远端视频流之后，向远端请求关键帧
     * @param stream_info 远端流信息，参看 RemoteStreamKey{@link #RemoteStreamKey}。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note  
     *        + 该方法仅适用于手动订阅模式，并且在成功订阅远端流之后使用。  <br>
     *        + 该方法适用于调用 setVideoDecoderConfig{@link #IRTCVideo#setVideoDecoderConfig} 开启自定义解码功能后，并且自定义解码失败的情况下使用
     */
    /**
     * @locale en
     * @type api
     * @region Video Management
     * @brief After subscribing to the remote video stream, request the key frame to the remote
     * @param stream_info The remote stream information. See RemoteStreamKey{@link #RemoteStreamKey}.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note   
     *         + This method is only suitable for manual subscription mode and is used after successful subscription to the remote flow. <br>
     *         + This method is suitable for calling setVideoDecoderConfig{@link #IRTCVideo#setVideoDecoderConfig} to turn on the custom decoding function, and the custom decoding fails
     */
    virtual int requestRemoteVideoKeyFrame(const RemoteStreamKey& stream_info) = 0;

    /**
     * @locale zh
     * @type api
     * @region 音频管理
     * @brief 发送音频流同步信息。将消息通过音频流发送到远端，并实现与音频流同步，该接口调用成功后，远端用户会收到 onStreamSyncInfoReceived{@link #IRTCVideoEventHandler#onStreamSyncInfoReceived} 回调。
     * @param data 消息内容。
     * @param length 消息长度。取值范围是 [1,255] 字节，建议小于 16 字节，否则可能占用较大带宽。
     * @param config 媒体流信息同步的相关配置，详见 StreamSycnInfoConfig{@link #StreamSycnInfoConfig} 。
     * @return  
     *        + >=0: 消息发送成功。返回成功发送的次数。  <br>
     *        + -1: 消息发送失败。消息长度大于 255 字节。  <br>
     *        + -2: 消息发送失败。传入的消息内容为空。  <br>
     *        + -3: 消息发送失败。通过屏幕流进行消息同步时，此屏幕流还未发布。  <br>
     *        + -4: 消息发送失败。通过用麦克风或自定义设备采集到的音频流进行消息同步时，此音频流还未发布，详见错误码 ErrorCode{@link #ErrorCode}。  
     * @note
     * + 调用本接口的频率建议不超过 50 次每秒。<br>
     * + 在 `kRoomProfileTypeInteractivePodcast` 房间模式下，此消息一定会送达。在其他房间模式下，如果本地用户未说话，此消息不一定会送达。
     */
    /**
     * @locale en
     * @type api
     * @region Audio management
     * @brief Send audio stream synchronization information. The message is sent to the remote end through the audio stream and synchronized with the audio stream. After the interface is successfully called, the remote user will receive a onStreamSyncInfoReceived{@link #IRTCVideoEventHandler#onStreamSyncInfoReceived} callback.
     * @param data Message content.
     * @param length Message length. Message length must be [1,16] bytes.
     * @param config For configuration of media stream information synchronization. See StreamSycnInfoConfig{@link #StreamSycnInfoConfig}.
     * @return   
     *         + > = 0: Message sent successfully. Returns the number of successful sends. <br>
     *         + -1: Message sending failed. Message length greater than 16 bytes. <br>
     *         + -2: Message sending failed. The content of the incoming message is empty. <br>
     *         + -3: Message sending failed. This screen stream was not published when the message was synchronized through the screen stream. <br>
     *         + -4: Message sending failed. This audio stream is not yet published when you synchronize messages with an audio stream captured by a microphone or custom device, as described in ErrorCode{@link #ErrorCode}. 
     * @note
     * + Regarding the frequency, we recommend no more than 50 calls per second.<br>
     * + When using `kRoomProfileTypeInteractivePodcast` as room profile, the data will be delivered. For other coom profiles, the data may be lost when the local user is muted.
     */
    virtual int sendStreamSyncInfo(const uint8_t* data, int32_t length, const StreamSycnInfoConfig& config) = 0;

    /**
     * @locale zh
     * @type api
     * @region 混音
     * @brief 开启本地语音变调功能，多用于 K 歌场景。  <br>
     *        使用该方法，你可以对本地语音的音调进行升调或降调等调整。
     * @param pitch 相对于语音原始音调的升高/降低值，取值范围[-12，12]，默认值为 0，即不做调整。  <br>
     *        取值范围内每相邻两个值的音高距离相差半音，正值表示升调，负值表示降调，设置的绝对值越大表示音调升高或降低越多。  <br>
     *        超出取值范围则设置失败，并且会触发 onWarning{@link #IRTCVideoEventHandler#onWarning} 回调，提示 WarningCode{@link #WarningCode} 错误码为 `WARNING_CODE_SET_SCREEN_STREAM_INVALID_VOICE_PITCH` 设置语音音调不合法
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     */
    /**
     * @locale en
     * @type api
     * @region Audio Mixing
     * @brief Change local voice to a different key, mostly used in Karaoke scenarios.  <br>
     *        You can adjust the pitch of local voice such as ascending or descending with this method.
     * @param pitch The value that is higher or lower than the original local voice within a range from -12 to 12. The default value is 0, i.e. No adjustment is made.  <br>
     *        The difference in pitch between two adjacent values within the value range is a semitone, with positive values indicating an ascending tone and negative values indicating a descending tone, and the larger the absolute value set, the more the pitch is raised or lowered.  <br>
     *        Out of the value range, the setting fails and triggers onWarning{@link #IRTCVideoEventHandler#onWarning} callback, indicating `WARNING_CODE_SET_SCREEN_STREAM_INVALID_VOICE_PITCH` for invalid value setting with WarningCode{@link #WarningCode}.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     */
    virtual int setLocalVoicePitch(int pitch) = 0;

    /**
     * @locale zh
     * @deprecated since 3.45 and will be deleted in 3.51, use setPlaybackVolume{@link #IRTCVideo#setPlaybackVolume} instead.
     * @type api
     * @region 媒体流管理
     * @brief 控制本地音频流播放状态：播放/不播放  
     * @param mute_state 播放状态，标识是否播放本地音频流，详见：MuteState{@link #MuteState}
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note 本方法仅控制本地收到音频流的播放状态，并不影响本地音频播放设备。
     */
    /**
     * @locale en
     * @deprecated since 3.45 and will be deleted in 3.51, use setPlaybackVolume{@link #IRTCVideo#setPlaybackVolume} instead.
     * @type api
     * @region Media stream management
     * @brief Play/Stop the local audio stream.
     * @param mute_state Playinging status to identify whether to play the local audio stream, see: MuteState {@link #MuteState}
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note This method controls the local audio stream but does not affect the local audio playback device.
     */
    BYTERTC_DEPRECATED virtual int muteAudioPlayback(MuteState mute_state) = 0;

    /**
     * @locale zh
     * @type api
     * @brief 订阅指定公共流<br>
     *        无论用户是否在房间内，都可以调用本接口获取和播放指定的公共流。
     * @param public_stream_id 公共流 ID，如果指定流暂未发布，则本地客户端将在其开始发布后接收到流数据。
     * @return 
     *        + 0: 成功。同时将收到 onPlayPublicStreamResult{@link #IRTCVideoEventHandler#onPlayPublicStreamResult} 回调。<br>
     *        + !0: 失败。当参数不合法或参数为空，调用失败。
     * @note  
     *        + 在调用本接口之前，建议先绑定渲染视图。<br>
     *              - 调用 setPublicStreamVideoCanvas{@link #IRTCVideo#setPublicStreamVideoCanvas} 绑定内部渲染视图：<br>
     *              - 调用 setPublicStreamVideoSink{@link #IRTCVideo#setPublicStreamVideoSink} 绑定自定义渲染视图：<br>
     *        + 调用本接口后，可以通过 onFirstPublicStreamVideoFrameDecoded{@link #IRTCVideoEventHandler#onFirstPublicStreamVideoFrameDecoded} 和 onFirstPublicStreamAudioFrame{@link #IRTCVideoEventHandler#onFirstPublicStreamAudioFrame} 回调公共流的视频和音频首帧解码情况。<br>
     *        + 调用本接口后，可以通过 onPublicStreamSEIMessageReceived{@link #IRTCVideoEventHandler#onPublicStreamSEIMessageReceived} 回调公共流中包含的 SEI 信息。<br>
     *        + 订阅公共流之后，可以通过调用 stopPlayPublicStream{@link #IRTCVideo#stopPlayPublicStream} 接口取消订阅公共流。
     */
    /**
     * @locale en
     * @hidden currently not available.
     * @type api
     * @brief Subscribe the public stream<br>
     *        A user can call this method to subscribe a public stream whether he/she has joined the room or not.
     * @param public_stream_id ID of the public stream. If the stream has not been published then, the local client will receive the public stream once it starts publishing.
     * @return 
     *        + 0: Success. You will also be informed by onPlayPublicStreamResult{@link #IRTCVideoEventHandler#onPlayPublicStreamResult}.  <br>
     *        + !0: Failure because of invalid parameter or empty parameters.
     * @note  
     *        + We recommend to bind a view for the public stream before calling this API to subscribe a public stream. <br>
     *              - Internal renderer: By calling setPublicStreamVideoCanvas{@link #IRTCVideo# setPublicStreamVideoCanvas} or <br>
     *              - Custom renderer: By calling setPublicStreamVideoSink{@link #IRTCVideo#setPublicStreamVideoSink}<br>
     *        + After calling this API, you will be informed once the first frame has been decoded successfully by onFirstPublicStreamVideoFrameDecoded{@link #IRTCVideoEventHandler#onFirstPublicStreamVideoFrameDecoded} and onFirstPublicStreamAudioFrame{@link #IRTCVideoEventHandler#onFirstPublicStreamAudioFrame}.<br>
     *        + If the public stream contains SEI information, you will be informed by onPublicStreamSEIMessageReceived{@link #IRTCVideoEventHandler#onPublicStreamSEIMessageReceived}.<br>
     *        + Call stopPlayPublicStream{@link #IRTCVideo#stopPlayPublicStream} to cancel subscribing the public stream.
     */
    virtual int startPlayPublicStream(const char* public_stream_id) = 0;
    /**
     * @locale zh
     * @type api
     * @brief 取消订阅指定公共流<br>
     *        关于订阅公共流，查看 startPlayPublicStream{@link #IRTCVideo#startPlayPublicStream}。
     * @param public_stream_id 公共流 ID
     * @return  
     *        + 0：成功  <br>
     *        + !0：失败  
     */
    /**
     * @locale en
     * @hidden currently not available
     * @type api
     * @brief Cancel subscribing the public stream.<br>
     *        Call this method to cancel subscribing to the public stream by calling startPlayPublicStream{@link #IRTCVideo#startPlayPublicStream}.
     * @param public_stream_id ID of the public stream
     * @return
     *        + 0: Success<br>
     *        + !0: Failure
     */

    virtual int stopPlayPublicStream(const char* public_stream_id) = 0;
    /**
     * @locale zh
     * @type api
     * @brief 为指定公共流绑定内部渲染视图。
     * @param public_stream_id 公共流 ID
     * @param canvas 内部渲染视图，如果需要解除视频的绑定视图，把 videoCanvas 设置为空。详见 VideoCanvas{@link #VideoCanvas}。
     * @return  
     *        + 0：成功  <br>
     *        + !0：失败  
     */
    /**
     * @locale en
     * @hidden currently not available
     * @type api
     * @brief Assign a internal render view to the public stream
     * @param public_stream_id ID of the public stream
     * @param canvas Internal render view. Refer to VideoCanvas{@link #VideoCanvas} for more details.
     * @return
     *        + 0: Success<br>
     *        + !0: Failure
     */
    virtual int setPublicStreamVideoCanvas(const char* public_stream_id, const VideoCanvas& canvas) = 0;
    /**
     * @locale zh
     * @type api
     * @brief 为指定公共流绑定自定义渲染器。详见[自定义视频渲染](https://www.volcengine.com/docs/6348/81201)。
     * @param public_stream_id 公共流 ID
     * @param video_sink 自定义视频渲染器，自定义视频渲染器，需要释放渲染器资源时，将 videoSink 设置为 `null`。参看 IVideoSink{@link #IVideoSink}
     * @param format videoSink 适用的视频帧编码格式，参看 PixelFormat{@link #PixelFormat}
     * @return 方法调用结果：<br>
     *        + 0：成功；<br>
     *        + <0：失败。具体失败原因参看 ReturnStatus{@link #ReturnStatus}。
     */
    /**
     * @locale en
     * @hidden currently not available
     * @type api
     * @brief Assign a custom renderer to the public stream
     * @param public_stream_id ID of the public stream
     * @param video_sink Custom renderer. Set to be `null` when you want to release the renderer. Refer to IVideoSink{@link #IVideoSink} for more details.
     * @param format Format of the video frames required by the external video renderer. Refer to PixelFormat{@link #PixelFormat} for more details.
     * @return API call result:<br>
     *        + 0: Success.<br>
     *        + <0: Failure. See ReturnStatus{@link #ReturnStatus} for specific reasons.
     */
    virtual int setPublicStreamVideoSink(const char* public_stream_id, IVideoSink* video_sink,
                                          IVideoSink::PixelFormat format) = 0;
    
    /**
     * @locale zh
     * @type api
     * @valid since 3.51
     * @brief 调节公共流的音频播放音量。
     * @param public_stream_id 公共流 ID
     * @param volume 音频播放音量值和原始音量值的比值，该比值的范围是 `[0, 400]`，单位为 %，且自带溢出保护。为保证更好的音频质量，建议设定在 `[0, 100]` 之间，其中 100 为系统默认值。 
     * @return   
     *         + 0: 成功调用。<br>
     *         + -2: 参数错误。
     */
    /**
     * @locale en
     * @type api
     * @valid since 3.51
     * @brief Set the audio playback volume of the public stream.
     * @param public_stream_id ID of the public stream.
     * @param volume Ratio(%) of the audio playback volume to the original volume, in the range `[0, 400]`, with overflow protection. The default volume is 100. <br>
     *               To ensure the audio quality, the recommended range is `[0,  100]`.  
     * @return   
     *         + 0: Success. <br>
     *         + -2: Wrong parameter.
     */
    virtual int setPublicStreamAudioPlaybackVolume(const char* public_stream_id, int volume) = 0;
    
    /**
     * @locale zh
     * @type api
     * @region 音视频处理
     * @brief 在指定视频流上添加水印。
     * @param stream_index 需要添加水印的视频流属性，参看 StreamIndex{@link #StreamIndex}。
     * @param image_path 水印图片路径，仅支持本地文件绝对路径，长度限制为 512 字节。  <br>
     *          水印图片为 PNG 或 JPG 格式。
     * @param config 水印参数，参看 RTCWatermarkConfig{@link #RTCWatermarkConfig}。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note  
     *        + 调用 clearVideoWatermark{@link #IRTCVideo#clearVideoWatermark} 移除指定视频流的水印。  <br>
     *        + 同一路流只能设置一个水印，新设置的水印会代替上一次的设置。你可以多次调用本方法来设置不同流的水印。  <br>
     *        + 若开启本地预览镜像，或开启本地预览和编码传输镜像，则远端水印均不镜像；在开启本地预览水印时，本端水印会镜像。  <br>
     *        + 开启大小流后，水印对大小流均生效，且针对小流进行等比例缩小。
     */
    /**
     * @locale en
     * @type api
     * @region Audio & Video Processing
     * @brief Adds watermark to designated video stream.
     * @param stream_index The index of the target stream. See StreamIndex{@link #StreamIndex}.
     * @param image_path The absolute path of the watermark image. The path should be less than 512 bytes.<br>
     *        The watermark image should be in PNG or JPG format.
     * @param config Watermark configurations. See RTCWatermarkConfig{@link #RTCWatermarkConfig}.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note 
     *        + Call clearVideoWatermark{@link #IRTCVideo#clearVideoWatermark} to remove the watermark from the designated video stream. <br>
     *        + You can only add one watermark to one video stream. The newly added watermark replaces the previous one. You can call this API multiple times to add watermarks to different streams. <br>
     *        + If you mirror the preview, or the preview and the published stream, the watermark will also be mirrored locally, but the published watermark will not be mirrored. <br>
     *        + When you enable simulcast mode, the watermark will be added to all video streams, and it will be scaled down to smaller encoding configurations accordingly. 
     */
    virtual int setVideoWatermark(StreamIndex stream_index, const char* image_path, RTCWatermarkConfig config) = 0;

    /**
     * @locale zh
     * @type api
     * @region 音视频处理
     * @brief 移除指定视频流的水印。
     * @param stream_index 需要移除水印的视频流属性，参看 StreamIndex{@link #StreamIndex}。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     */
    /**
     * @locale en
     * @type api
     * @region Audio & Video Processing
     * @brief  Removes video watermark from designated video stream.
     * @param stream_index The index of the target stream. See StreamIndex{@link #StreamIndex}.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     */
    virtual int clearVideoWatermark(StreamIndex stream_index) = 0;

    /**
     * @locale zh
     * @hidden(Linux)
     * @type api
     * @brief 截取本地视频画面
     * @param stream_index 截图的视频流的属性，参看 StreamIndex{@link #StreamIndex}。
     * @param callback 本地截图的回调。参看 ISnapshotResultCallback{@link #ISnapshotResultCallback}。
     * @return 本地截图任务的编号，从 `1` 开始递增。
     * @note 
     *        + 对截取的画面，包含本地视频处理的全部效果，包含旋转，镜像，美颜等。<br>
     *        + 不管采用 SDK 内部采集，还是自定义采集，都可以进行截图。
     */
    /**
     * @locale en
     * @hidden(Linux)
     * @type api
     * @brief Take a snapshot of the local video.
     * @param stream_index See StreamIndex{@link #StreamIndex}.
     * @param callback See ISnapshotResultCallback{@link #ISnapshotResultCallback}.
     * @return The index of the local snapshot task, starting from `1`.
     * @note 
     *        + The snapshot is taken with all video effects on, like rotation, and mirroring. <br>
     *        + You can take the snapshot either using SDK internal video capture or customized capture.
     */
    virtual long takeLocalSnapshot(const StreamIndex stream_index, ISnapshotResultCallback* callback) = 0;

    /**
     * @locale zh
     * @hidden(Linux)
     * @type api
     * @brief 截取远端视频画面
     * @param stream_key 截图的视频流，参看 RemoteStreamKey{@link #RemoteStreamKey}。
     * @param callback 参看 ISnapshotResultCallback{@link #ISnapshotResultCallback}。
     * @return 远端截图任务的编号，从 `1` 开始递增。
     */
    /**
     * @locale en
     * @hidden(Linux)
     * @type api
     * @brief Take a snapshot of the remote video.
     * @param stream_key See RemoteStreamKey{@link #RemoteStreamKey}.
     * @param callback See ISnapshotResultCallback{@link #ISnapshotResultCallback}.
     * @return The index of the remote snapshot task, starting from `1`.
     */
    virtual long takeRemoteSnapshot(const RemoteStreamKey stream_key, ISnapshotResultCallback* callback) = 0;

    /**
     * @locale zh
     * @type api
     * @region 音视频传输
     * @brief 摄像头处于关闭状态时，使用静态图片填充本地推送的视频流。<br>
     *        调用 `stopVideoCapture` 接口时，会开始推静态图片。若要停止发送图片，可传入空字符串或启用内部摄像头采集。<br>
     *        可重复调用该接口来更新图片。
     * @param file_path 设置静态图片的路径。  <br>
     *        支持本地文件绝对路径，不支持网络链接，长度限制为 512 字节。   <br>
     *        静态图片支持类型为 JPEG/JPG、PNG、BMP。  <br>
     *        若图片宽高比与设置的编码宽高比不一致，图片会按编码高宽等比缩放，并裁剪长边。推流帧率与码率与设置的编码参数一致。
     * @return  
     *        + 0: 成功。  <br>
     *        + -1: 失败。
     * @note  
     *        + 该接口只适用于 SDK 内部摄像头采集，不适用于自定义视频采集。  <br>
     *        + 本地预览无法看到静态图片。  <br>
     *        + 进入房间前后均可调用此方法。在多房间场景中，静态图片仅在发布的房间中生效。  <br>
     *        + 针对该静态图片，滤镜和镜像效果不生效，水印效果生效。  <br>
     *        + 只有主流能设置静态图片，屏幕流不支持设置。  <br>
     *        + 开启大小流后，静态图片对大小流均生效，且针对小流进行等比例缩小。
     */
    /**
     * @locale en
     * @type api
     * @region Audio & Video Transport
     * @brief Set an alternative image when the local internal video capture is not enabled.<br>
     *        When you call `stopVideoCapture`, an alternative image will be pushed. You can set the path to null or open the camera to stop publishing the image.<br>
     *        You can repeatedly call this API to update the image.
     * @param file_path Set the path of the static image.  <br>
     *        You can use the absolute path (file://xxx). The maximum size for the path is 512 bytes.  <br>
     *        You can upload a .JPG, .JPEG, .PNG, or .BMP file.  <br>
     *        When the aspect ratio of the image is inconsistent with the video encoder configuration, keep the aspect-ratio to scale the image and the crop the longer sides. The framerate and the bitrate are consistent with the video encoder configuration.
     * @return  
     *        + 0: Success.  <br>
     *        + -1: Failure.
     * @note  
     *        + The API is only effective when publishing an internally captured video.  <br>
     *        + You cannot locally preview the image.  <br>
     *        + You can call this API before and after joining an RTC room. In the multi-room mode, the image can be only displayed in the room you publish the stream.  <br>
     *        + You cannot apply effects like filters and mirroring to the image, while you can watermark the image.  <br>
     *        + The image is not effective for a screen-sharing stream.  <br>
     *        + When you enable the simulcast mode, the image will be added to all video streams, and it will be proportionally scaled down to smaller encoding configurations.
     */
    virtual int setDummyCaptureImagePath(const char* file_path) = 0;

    /**
     * @locale zh
     * @type api
     * @region 云代理
     * @brief 开启云代理
     * @param configuration 云代理服务器信息列表。参看 CloudProxyConfiguration{@link #CloudProxyConfiguration}。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note  
     *        + 在加入房间前调用此接口  <br>
     *        + 在开启云代理后，进行通话前网络探测 <br>
     *        + 开启云代理后，并成功链接云代理服务器后，会收到 onCloudProxyConnected{@link #IRTCVideoEventHandler#onCloudProxyConnected}。<br>
     *        + 要关闭云代理，调用 stopCloudProxy{@link #IRTCVideo#stopCloudProxy}。
     */
    /**
     * @locale en
     * @type api
     * @region  cloud proxy
     * @brief  Start cloud proxy
     * @param configuration cloud proxy informarion list. See CloudProxyConfiguration{@link #CloudProxyConfiguration}.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note   
     *         + Call this API before joining the room.<br>
     *         + Start pre-call network detection after starting cloud proxy. <br>
     *         + After starting cloud proxy and connects the cloud proxy server successfully, receives onCloudProxyConnected{@link #IRTCVideoEventHandler#onCloudProxyConnected}. <br>
     *         + To stop cloud proxy, call stopCloudProxy{@link #IRTCVideo#stopCloudProxy}.
     */
    virtual int startCloudProxy(const CloudProxyConfiguration& configuration) = 0;

    /**
     * @locale zh
     * @type api
     * @region 云代理
     * @brief 关闭云代理
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note 要开启云代理，调用 startCloudProxy{@link #IRTCVideo#startCloudProxy}。
     */
    /**
     * @locale en
     * @type api
     * @region  cloud proxy
     * @brief  Stop cloud proxy
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note To start cloud proxy, call startCloudProxy{@link #IRTCVideo#startCloudProxy}.
     */
    virtual int stopCloudProxy() = 0;

    /**
     * @locale zh
     * @hidden(Linux)
     * @type api
     * @region 网络管理
     * @brief 开启音视频回路测试。  <br>
     *        在进房前，用户可调用该接口对音视频通话全链路进行检测，包括对音视频设备以及用户上下行网络的检测，从而帮助用户判断是否可以正常发布和接收音视频流。  <br>
     *        开始检测后，SDK 会录制你声音或视频。如果你在设置的延时范围内收到了回放，则视为音视频回路测试正常。
     * @param echo_test_config 回路测试参数设置，参看 EchoTestConfig{@link #EchoTestConfig}。
     * @param play_delay_time 音视频延迟播放的时间间隔，用于指定在开始检测多长时间后期望收到回放。取值范围为 [2,10]，单位为秒，默认为 2 秒。
     * @return 方法调用结果：  <br>
     *        + 0：成功  <br>
     *        + -1：失败，当前用户已经在检测中  <br>
     *        + -2：失败，用户已进房  <br>
     *        + -3：失败，音视频均未采集  <br>
     *        + -4：失败，参数异常  <br>
     *        + -5：失败，已经存在相同 roomId 的房间
     * @note  
     *        + 调用该方法开始音视频回路检测后，你可以调用 stopEchoTest{@link #IRTCVideo#stopEchoTest} 立即结束测试，也可等待测试 60s 后自动结束，以更换设备进行下一次测试，或进房。  <br>
     *        + 在该方法之前调用的所有跟设备控制、流控制相关的方法均在开始检测时失效，在结束检测后恢复生效。  <br>
     *        + 在调用 startEchoTest{@link #IRTCVideo#startEchoTest} 和 stopEchoTest{@link #IRTCVideo#stopEchoTest} 之间调用的所有跟设备采集、流控制、进房相关的方法均不生效，并会收到 onWarning{@link #IRTCVideoEventHandler#onWarning} 回调，提示警告码为 `kWarningCodeInEchoTestMode`。  <br>
     *        + 音视频回路检测的结果会通过 onEchoTestResult{@link #IRTCVideoEventHandler#onEchoTestResult} 回调通知。
     */
    /**
     * @locale en
     * @hidden(Linux)
     * @type api
     * @region Network Management
     * @brief Starts a call test.  <br>
     *        Before entering the room, you can call this API to test whether your local audio/video equipment as well as the upstream and downstream networks are working correctly.  <br>
     *        Once the test starts, SDK will record your sound or video. If you receive the playback within the delay range you set, the test is considered normal.
     * @param echo_test_config Test configurations, see EchoTestConfig{@link #EchoTestConfig}.
     * @param play_delay_time Delayed audio/video playback time specifying how long you expect to receive the playback after starting the. The range of the value is [2,10] in seconds and the default value is 2.
     * @return API call result:  <br>
     *        + 0: Success  <br>
     *        + -1: Failure, testing in progress  <br>
     *        + -2: Failure, you are in the room  <br>
     *        + -3: Failure, neither video nor audio is captured  <br>
     *        + -4: Failure, Parameter exception  <br>
     *        + -5: Failure, the roomID is already used
     * @note  
     *        + Once you start the test, you can either call stopEchoTest{@link #IRTCVideo#stopEchoTest} or wait until the test stops automatically after 60s, to start the next test or enter the room.  <br>
     *        + All APIs related to device control and stream control called before this API are invalidated during the test and are restored after the test.  <br>
     *        + All APIs related to device control, stream control, and room entry called during the test do not take effect, and you will receive onWarning{@link #IRTCVideoEventHandler#onWarning} with the warning code `kWarningCodeInEchoTestMode`.<br>
     *        + You will receive the test result from onEchoTestResult{@link #IRTCVideoEventHandler#onEchoTestResult}.
     */
    virtual int startEchoTest(EchoTestConfig echo_test_config, unsigned int play_delay_time) = 0;
    /**
     * @locale zh
     * @hidden(Linux)
     * @type api
     * @region 网络管理
     * @brief 停止音视频回路测试。  <br>
     *        调用 startEchoTest{@link #IRTCVideo#startEchoTest} 开启音视频回路检测后，你必须调用该方法停止检测。
     * @return 方法调用结果：  <br>
     *        + 0：成功  <br>
     *        + -1：失败，未开启回路检测
     * @note 音视频回路检测结束后，所有对系统设备及音视频流的控制均会恢复到开始检测前的状态。
     */
    /**
     * @locale en
     * @hidden(Linux)
     * @type api
     * @region Network Management
     * @brief Stop the current call test.  <br>
     *        After calling startEchoTest{@link #IRTCVideo#startEchoTest}, you must call this API to stop the test.
     * @return API call result:  <br>
     *        + 0: Success  <br>
     *        + -1: Failure, no test is in progress
     * @note After stopping the test with this API, all the system devices and streams are restored to the state they were in before the test.
     */
    virtual int stopEchoTest() = 0;
    /**
     * @locale zh
     * @hidden(Linux)
     * @type api
     * @brief 创建 K 歌评分管理接口。
     * @return K 歌评分管理接口,详见 ISingScoringManager{@link #ISingScoringManager}。
     */
    /**
     * @locale en
     * @hidden(Linux)
     * @type api
     * @brief Create a karaoke scoring management interface.
     * @return Karaoke scoring management interface, see ISingScoringManager{@link #ISingScoringManager}.
     */
    virtual ISingScoringManager* getSingScoringManager() = 0;
    /**
     * @locale zh
     * @hidden(Linux)
     * @type api
     * @brief 通过 NTP 协议，获取网络时间。
     * @return 网络时间。参看 NetworkTimeInfo{@link #NetworkTimeInfo}。
     * @note 
     *        + 第一次调用此接口会启动网络时间同步功能，并返回 `0`。同步完成后，会收到 onNetworkTimeSynchronized{@link #IRTCVideoEventHandler#onNetworkTimeSynchronized}，此后，再次调用此 API，即可获取准确的网络时间。<br>
     *        + 在合唱场景下，合唱参与者应在相同的网络时间播放背景音乐。
     */
    /**
     * @locale en
     * @type api
     * @hidden(Linux)
     * @brief Obtain the synchronization network time information.
     * @return See NetworkTimeInfo{@link #NetworkTimeInfo}.
     * @note 
     *        + When you call this API for the first time, you starts synchornizing the network time information and receive the return value `0`. After the synchonization finishes, you will receive onNetworkTimeSynchronized{@link #IRTCVideoEventHandler#onNetworkTimeSynchronized}. After that, calling this API will get you the correct network time. <br>
     *        + Under chorus scenario, participants shall start audio mixing at the same network time.
     */
    virtual NetworkTimeInfo getNetworkTimeInfo() = 0;
    /**
     * @locale zh
     * @hidden internal use
     * @valid since 3.52
     * @type api
     * @brief 调用实验性 API。<br>
     *        调用后，可能会触发 onInvokeExperimentalAPI{@link #IRTCVideoEventHandler#onInvokeExperimentalAPI}。
     * @param param JSON 字符串，形如：<br>
     * ```{<br>
     *   "api_name":"startPublish",<br>
     *   "params":{<br>
     *     "streamID":"",<br>
     *     "observer":"",<br>
     *     "uri":"",<br>
     *     "option":""<br>
     *   }<br>
     * }```
     * @return  
     *        + 0： 成功。  <br>
     *        + < 0： 失败。  
     */
    /**
     * @locale en
     * @hidden internal use
     * @valid since 3.52
     * @type api
     * @brief invoke experimental API. <br>
     *        You may receive onInvokeExperimentalAPI{@link #IRTCVideoEventHandler#onInvokeExperimentalAPI}.
     * @note [in] param JSON string like:<br>
     * ```{<br>
     *   "api_name":"startPublish",<br>
     *   "params":{<br>
     *     "streamID":"",<br>
     *     "observer":"",<br>
     *     "uri":"",<br>
     *     "option":""<br>
     *   }<br>
     * }```
     * @return  
     *        + 0: Success.  <br>
     *        + < 0: Failure.
     */
    virtual int invokeExperimentalAPI(const char* param) = 0;


    /**
     * @locale zh
     * @hidden(Linux,macOS)
     * @type api
     * @brief 创建 KTV 管理接口。
     * @return KTV 管理接口，参看 IKTVManager{@link #IKTVManager}。
     */
    /**
     * @locale en
     * @hidden currently not available
     * @type api
     * @brief Creates the KTV manager interfaces.
     * @return KTV manager interfaces. See IKTVManager{@link #IKTVManager}.
     */
    virtual IKTVManager* getKTVManager() = 0;

    /**
     * @locale zh
     * @hidden(Linux)
     * @type api
     * @region 音频设备
     * @brief 开启通话前回声检测
     * @param test_audio_file_path 用于回声检测的音频文件的绝对路径，路径字符串使用 UTF-8 编码格式，支持以下音频格式: mp3，aac，m4a，3gp，wav。<br>
     *         音频文件不为静音文件，推荐时长为 10 ～ 20 秒。
     * @return 方法调用结果：  <br>
     *        + 0: 成功。<br>
     *        + -1：失败。上一次检测未结束，请先调用 stopHardwareEchoDetection{@link #IRTCVideo#stopHardwareEchoDetection} 停止检测 后重新调用本接口。<br>
     *        + -2：失败。路径不合法或音频文件格式不支持。
     * @note 
     *        + 只有当 RoomProfileType{@link #RoomProfileType} 为 `kRoomProfileTypeMeeting` 和 `kRoomProfileTypeMeetingRoom` 时支持开启本功能。<br>
     *        + 开启检测前，你需要向用户获取音频设备的使用权限。<br>
     *        + 开启检测前，请确保音频设备没有被静音，采集和播放音量正常。<br>
     *        + 调用本接口后监听 onHardwareEchoDetectionResult{@link #IRTCVideoEventHandler#onHardwareEchoDetectionResult} 获取检测结果。<br>
     *        + 检测期间，进程将独占音频设备，无法使用其他音频设备测试接口： startEchoTest{@link #IRTCVideo#startEchoTest}、startAudioDeviceRecordTest{@link #IAudioDeviceManager#startAudioDeviceRecordTest} 或 startAudioPlaybackDeviceTest{@link #IAudioDeviceManager#startAudioPlaybackDeviceTest}。 <br>
     *        + 调用 stopHardwareEchoDetection{@link #IRTCVideo#stopHardwareEchoDetection} 停止检测，释放对音频设备的占用。
     */
    /**
     * @locale en
     * @hidden(Linux)
     * @type api
     * @region Audio Management
    * @brief Start echo detection before joining a room.
    * @param test_audio_file_path Absolute path of the music file for the detection. It is expected to encode with UTF-8. The following files are supported: mp3, aac, m4a, 3gp, wav. <br>
    *          We recommend to assign a music file whose duration is between 10 to 20 seconds.<br>
    *        Do not pass a Silent file.
    * @return Method call result: <br>
    *        + 0: Success. <br>
    *        + -1: Failure due to the onging process of the previous detection. Call stopHardwareEchoDetection{@link #IRTCVideo#stopHardwareEchoDetection} to stop it before calling this API again.<br>
    *        + -2: Failure due to an invalid file path or file format.
    * @note 
    *        + You can use this feature only when RoomProfileType{@link #RoomProfileType} is set to `kRoomProfileTypeMeeting` or `kRoomProfileTypeMeetingRoom`.<br>
    *        + Before calling this API, ask the user for the permissions to access the local audio devices. <br>
    *        + Before calling this api, make sure the audio devices are activate and keep the capture volume and the playback volume within a reasonable range.<br>
    *        + The detection result is passed as the argument of onHardwareEchoDetectionResult{@link #IRTCVideoEventHandler#onHardwareEchoDetectionResult}. <br>
    *        + During the detection, the SDK is not able to response to the other testing APIs, such as startEchoTest{@link #IRTCVideo#startEchoTest}、startAudioDeviceRecordTest{@link #IAudioDeviceManager#startAudioDeviceRecordTest} or startAudioPlaybackDeviceTest{@link #IAudioDeviceManager#startAudioPlaybackDeviceTest}. <br>
    *        + Call stopHardwareEchoDetection{@link #IRTCVideo#stopHardwareEchoDetection} to stop the detection and release the audio devices.
    */
    virtual int startHardwareEchoDetection(const char* test_audio_file_path) = 0;
    /**
     * @locale zh
     * @hidden(Linux)
     * @type api
     * @region 音频设备
     * @brief 停止通话前回声检测
     * @return 方法调用结果：  <br>
     *        + 0: 成功。<br>
     *        + -1：失败。
     * @note 
     *       + 关于开启通话前回声检测，参看 startHardwareEchoDetection{@link #IRTCVideo#startHardwareEchoDetection} 。<br>
     *       + 建议在收到 onHardwareEchoDetectionResult{@link #IRTCVideoEventHandler#onHardwareEchoDetectionResult} 通知的检测结果后，调用本接口停止检测。<br>
     *       + 在用户进入房间前结束回声检测，释放对音频设备的占用，以免影响正常通话。
     */
    /**
     * @locale en
     * @hidden(Linux)
     * @type api
     * @brief Stop the echo detection before joining a room.
     * @return   Method call result:   <br>
     *        + 0: Success. <br>
     *        + -1: Failure.
     * @note 
     *        + Refer to startHardwareEchoDetection{@link #IRTCVideo#startHardwareEchoDetection} for information on how to start a echo detection. <br>
     *        + We recommend calling this API to stop the detection once getting the detection result from onHardwareEchoDetectionResult{@link #IRTCVideoEventHandler#onHardwareEchoDetectionResult}. <br>
     *        + You must stop the echo detection to release the audio devices before the user joins a room. Otherwise, the detection may interfere with the call.
     */
    virtual int stopHardwareEchoDetection() = 0;


    /**
     * @locale zh
     * @hidden(macOS, Windows, Linux)
     * @type api
     * @brief 启用蜂窝网络辅助增强，改善通话质量。
     * @param config 参看 MediaTypeEnhancementConfig{@link #MediaTypeEnhancementConfig}。
     * @return 方法调用结果：  <br>
     *        + 0: 成功。<br>
     *        + -1：失败，内部错误。 <br>
     *        + -2: 失败，输入参数错误。 
     * @note 此功能默认不开启。
     */
    /**
     * @locale en
     * @hidden(macOS, Windows, Linux)
     * @type api
     * @brief Enable cellular network assisted communication to improve call quality.
     * @param config See MediaTypeEnhancementConfig{@link #MediaTypeEnhancementConfig}.
     * @return Method call result:   <br>
     *        + 0: Success. <br>
     *        + -1: Failure, internal error. <br>
     *        + -2: Failure, invalid parameters. 
     * @note The function is off by default.
     */
    virtual int setCellularEnhancement(const MediaTypeEnhancementConfig& config) = 0;

    /**
     * @locale zh
     * @type api
     * @region 代理
     * @brief 设置本地代理。
     * @param configurations 本地代理配置参数。参看 LocalProxyConfiguration{@link #LocalProxyConfiguration}。 <br>
     *        你可以根据自己的需要选择同时设置 Http 隧道 和 Socks5 两类代理，或者单独设置其中一类代理。如果你同时设置了 Http 隧道 和 Socks5 两类代理，此时，媒体和信令采用 Socks5 代理， Http 请求采用 Http 隧道代理；如果只设置 Http 隧道 或 Socks5 一类代理，媒体、信令和 Http 请求均采用已设置的代理。 <br>
     *        调用此接口设置本地代理后，若想清空当前已有的代理设置，可再次调用此接口，选择不设置任何代理即可清空。
     * @param configuration_num 本地代理配置参数的数量。
     * @note 
     *       + 该方法需要在进房前调用。<br>
     *       + 调用该方法设置本地代理后，SDK 会触发 onLocalProxyStateChanged{@link #IRTCVideoEventHandler#onLocalProxyStateChanged} ，返回代理连接的状态。
     */
    /**
     * @locale en
     * @type api
     * @region proxy
     * @brief Sets local proxy.
     * @param configurations Local proxy configurations. Refer to LocalProxyConfiguration{@link #LocalProxyConfiguration}. <br>
     *         You can set both Http tunnel and Socks5 as your local proxies, or only set one of them based on your needs. If you set both Http tunnel and Socks5 as your local proxies, then media traffic and signaling are routed through Socks5 proxy and Http requests through Http tunnel proxy. If you set either Http tunnel or Socks5 as your local proxy, then media traffic, signaling and Http requests are all routed through the proxy you chose. <br>
     *         If you want to remove the existing local proxy configurations, you can call this API with the parameter set to null. 
     * @param configuration_num The number of local proxy configurations. 
     * @note 
     *       + You must call this API before joining the room.  <br>
     *       + After calling this API, you will receive onLocalProxyStateChanged{@link #IRTCVideoEventHandler#onLocalProxyStateChanged} callback that informs you of the states of local proxy connection. 
     */
    virtual int setLocalProxy(const LocalProxyConfiguration* configurations, int configuration_num) = 0;


    /**
     * @locale zh
     * @valid since 3.57
     * @hidden(Android,iOS)
     * @type api
     * @region 音视频处理
     * @brief 设置视频暗光增强模式。<br>
     *        对于光线不足、照明不均匀或背光等场景下推荐开启，可有效改善画面质量。
     * @param mode 默认不开启。参看 VideoEnhancementMode{@link #VideoEnhancementMode}。
     * @return 
     *        + 0: API 调用成功。会立即生效，但需要等待下载和检测完成后才能看到增强后的效果。<br>
     *        + < 0: API 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明。
     * @note 
     *        + 开启后会影响设备性能，应根据实际需求和设备性能决定是否开启。<br>
     *        + 对 RTC SDK 内部采集的视频和自定义采集的视频都生效。
     */
    /**
     * @locale en
     * @valid since 3.57
     * @hidden(Android,iOS)
     * @type api
     * @region Audio & Video Processing
     * @brief Sets the video lowlight enhancement mode.<br>
     *        It can significantly improve image quality in scenarios with insufficient light, contrast lighting, or backlit situations.
     * @param mode It defaults to Disable. Refer to VideoEnhancementMode{@link #VideoEnhancementMode} for more details.
     * @return 
     *        + 0: Success. The RTC SDK takes immediate action, yet it may require some time for downloads and detection processes before you can see the enhancement.<br>
     *        + < 0: Failure. See ReturnStatus{@link #ReturnStatus} for more details.
     * @note 
     *        + Turning on this mode will impact device performance. This feature should be activated only when required and the device performance is adequate.<br>
     *        + Functionality applies to videos captured by the internal module as well as those from custom collections.
     */
    virtual int setLowLightAdjusted(VideoEnhancementMode mode) = 0;
};

/**
* @locale zh
* @type api
* @region 引擎管理
* @brief 创建 IRTCVideo 实例。  <br>
*        如果当前进程中未创建引擎实例，那么你必须先使用此方法，以使用 RTC 提供的各种音视频能力。  <br>
*        如果当前进程中已创建了引擎实例，再次调用此方法时，会返回已创建的引擎实例。
* @param app_id 每个应用的唯一标识符。只有使用相同的 app_id 生成的实例，才能够进行音视频通信。
* @param event_handler SDK 回调给应用层的 Callback 对象，详见 IRTCVideoEventHandler{@link #IRTCVideoEventHandler} 。
* @param parameters 私有参数。如需使用请联系技术支持人员。
* @return  
*        + IRTCVideo：创建成功。返回一个可用的 IRTCVideo{@link #IRTCVideo} 实例  <br>
*        + Null：app_id 或者event_handler为空, event_handler 为空。
* @list 引擎管理
* @order 1
*/
/**
* @locale en
* @type api
* @region Engine Management
* @brief Creates an engine instance.   <br>
*        This is the very first API that you must call if you want to use all the RTC capabilities.  <br>
*        If there is no engine instance in current process, calling this API will create one. If an engine instance has been created, calling this API again will have the created engine instance returned.
* @param app_id A unique identifier for each App, randomly generated by the RTC console. Only instances created with the same app_id are able to communicate with each other.
* @param event_handler Handler sent from SDK to App. See IRTCVideoEventHandler{@link #IRTCVideoEventHandler}.
* @param parameters Reserved parameters. Please contact technical support fellow if needed.
* @return  
*        + IRTCVideo: A successfully created engine instance.  <br>
*        + Null:  app_id is null or empty. event_handler is null.
* @list Engine Management
* @order 1
*/
BYTERTC_API bytertc::IRTCVideo* createRTCVideo(const char* app_id,
     bytertc::IRTCVideoEventHandler *event_handler, const char* parameters);

/**
 * @locale zh
 * @hidden internal use only
 * @type api
 * @region 引擎管理
 * @brief 创建多实例引擎对象  <br>
 *        如果当前进程中未创建引擎实例，那么你必须先使用此方法，以使用 RTC 提供的各种音视频能力。  <br>
 *        如果当前进程中已创建了引擎实例，再次调用此方法时，会返回新创建的引擎实例。
 * @param context Android Application Context
 * @param appId 每个应用的唯一标识符，由 RTC 控制台随机生成的。不同的 AppId 生成的实例在 RTC 中进行音视频通话完全独立，无法互通。  
 * @param handler SDK 回调给应用层的 Handler，详见 IRTCVideoEventHandler{@link #IRTCVideoEventHandler}  
 * @param eglContext 如果需要支持外部纹理硬编码，则需要以 `JObject` 方式传入 `eglContext`。  
 * @param parameters 私有参数。如需使用请联系技术支持人员。
 * @return  
 *        + RTCVideo：创建成功。返回一个可用的 IRTCVideo{@link #IRTCVideo} 实例  <br>
 *        + Null：.so 文件加载失败，创建失败。
 * @note 你应注意保持 handler 的生命周期必须大于 IRTCVideo{@link #IRTCVideo} 的生命周期，即 handler 必须在调用 destroyRTCVideo{@link #IRTCVideo#destroyRTCVideo} 之后销毁。
 */
/**
 * @locale en
 * @hidden internal use only
 * @type api
 * @region Engine Management
 * @brief Creates an engine instance for multi-engine senario.   <br>
 *        This is the very first API that you must call if you want to use all the RTC capabilities.  <br>
 *        If there is no engine instance in current process, calling this API will create one. If an engine instance has been created, calling this API again will have a new created engine instance returned.
 * @param context Android application context
 * @param appId A unique identifier for each App, randomly generated by the RTC console. Engine instances created with different AppIds cannot communicate with each other.
 * @param handler Handler sent from SDK to App. See IRTCVideoEventHandler{@link #IRTCVideoEventHandler} 
 * @param eglContext If you need SDK to support custom texture hardcoding, you must import the eglContext in a JObject. 
 * @param parameters Reserved parameters. Please contact technical support fellow if needed.
 * @return  
 *         + RTCVideo: A successfully created engine instance.  <br>
 *         + Null: Failed to load the .so file. No instance is returned.
 * @note The lifecycle of the handler must be longer than that of the RTCVideo, i.e. the handler must be created before calling createRTCVideo{@link #IRTCVideo#createRTCVideo} and destroyed after calling destroyRTCVideo{@link #IRTCVideo#destroyRTCVideo}.
 */
BYTERTC_API bytertc::IRTCVideo* createRTCVideoMulti(const char* app_id,
                                                    bytertc::IRTCVideoEventHandler* event_handler, const char* parameters);
/**
 * @locale zh
 * @type api
 * @region 引擎管理
 * @brief 销毁由 createRTCVideo{@link #createRTCVideo} 所创建的引擎实例，并释放所有相关资源。
 * @note  
 *        + 请确保和需要销毁的 IRTCVideo{@link #IRTCVideo} 实例相关的业务场景全部结束后，才调用此方法。如果在多线程场景下，调用此接口后，又调用了其他 IRTCVideo{@link #IRTCVideo} 相关接口，可能导致 SDK 崩溃。该方法在调用之后，会销毁所有和此 IRTCVideo{@link #IRTCVideo} 实例相关的内存，并且停止与媒体服务器的任何交互。  <br>
 *        + 调用本方法会启动 SDK 退出逻辑。引擎线程会保留，直到退出逻辑完成。因此，不要在回调线程中直接调用此 API，会导致死锁。同时此方法是耗时操作，不建议在主线程调用本方法，避免主线程阻塞。
 * @list 引擎管理
 * @order 2
 */
/**
 * @locale en
 * @type api
 * @region Engine Management
 * @brief Destroy the engine instance created by createRTCVideo{@link #createRTCVideo}, and release all related resources.
 * @note  
 *         + Call this API after all business scenarios related to the engine instance are destroyed. In a multi-thread scenario, you must not call IRTCVideo{@link #IRTCVideo} related APIs after calling this interface, or the SDK may crash. When the API is called, RTC SDK destroys all memory associated with the engine instance and stops any interaction with the media server.  <br>
 *         + Calling this API will start the SDK exit logic. The engine thread is held until the exit logic is complete. The engine thread is retained until the exit logic is complete. Therefore, do not call this API directly in the callback thread, or it will cause a deadlock. This function takes a long time to execute, so it's not recommended to call this API in the main thread, or the main thread may be blocked.
 * @list Engine Management
 * @order 2
 */
BYTERTC_API void destroyRTCVideo();

/**
 * @locale zh
 * @hidden internal use only
 * @type api
 * @region 引擎管理
 * @brief 销毁由 createRTCVideoMulti{@link #IRTCVideo#createRTCVideoMulti} 所创建的引擎实例，并释放所有相关资源。
 * @note  
 *      + 请确保和需要销毁的 IRTCVideo{@link #IRTCVideo} 实例相关的业务场景全部结束后，才调用此方法  <br>
 *      + 该方法在调用之后，会销毁所有和此 IRTCVideo{@link #IRTCVideo} 实例相关的内存，并且停止与媒体服务器的任何交互  <br>
 *      + 调用本方法会启动 SDK 退出逻辑。引擎线程会保留，直到退出逻辑完成。因此，不要在回调线程中直接调用此 API，会导致死锁。同时此方法是耗时操作，不建议在主线程调用本方法，避免主线程阻塞。
 */
/**
 * @locale en
 * @hidden internal use only
 * @type api
 * @region Engine management
 * @brief Destroy the engine instance created by createRTCVideoMulti{@link #IRTCVideo#createRTCVideoMulti}, and release all related resources. 
 * @note  
 *       + Call this API after all business scenarios related to the engine instance are destroyed.  <br>
 *       + When the API is called, RTC SDK destroys all memory associated with the engine instance and stops any interaction with the media server.  <br>
 *       + Calling this API will start the SDK exit logic. The engine thread is held until the exit logic is complete. The engine thread is retained until the exit logic is complete. Therefore, do not call this API directly in the callback thread, or it will cause a deadlock. This function takes a long time to execute, so it's not recommended to call this API in the main thread, or the main thread may be blocked.
 */
BYTERTC_API void destroyRTCVideoMulti(IRTCVideo* instance_multi);
/**
 * @locale zh
 * @type api
 * @region 错误码
 * @brief 获取 SDK 内各种错误码、警告码的描述文字。
 * @param code 需要获取描述的错误码
 * @return 错误码的描述
 * @note  该接口是通用功能，调用时不需要依赖引擎对象。
 * @list 引擎管理
 * @order 15
 */
/**
 * @locale en
 * @type api
 * @region  error code
 * @brief Gets the description text of different error codes and warning codes in the SDK.
 * @param code Needs to get the description of the error code
 * @return The description of the error code
 * @note This interface is a general function and does not need to rely on the engine object when calling.
 * @list Engine Management
 * @order 15
 */
BYTERTC_API const char* getErrorDescription(int code);
/**
 * @locale zh
 * @type api
 * @region 引擎管理
 * @brief 获取当前 SDK 版本信息。
 * @return 当前 SDK 版本信息。
 * @list 引擎管理
 * @order 5
 */
/**
 * @locale en
 * @type api
 * @region  engine management
 * @brief  Get the current SDK version information.
 * @return Current SDK version information.
 * @list Engine Management
 * @order 5
 */
BYTERTC_API const char* getSDKVersion();

/**
 * @locale zh
 * @type api
 * @region 引擎管理
 * @brief 配置 SDK 本地日志参数，包括日志级别、存储路径、日志文件最大占用的总空间、日志文件名前缀。
 * @param log_config 本地日志参数，参看 LogConfig{@link #LogConfig}。
 * @return 
 *        + 0：成功。<br>
 *        + –1：失败，本方法必须在创建引擎前调用。<br>
 *        + –2：失败，参数填写错误。
 * @note 本方法必须在调用 createRTCVideo{@link #createRTCVideo} 之前调用。
 * @list 引擎管理
 * @order 30
 */
/**
 * @locale en
 * @type api
 * @region Engine Management
 * @brief Configures the local log parameters of RTC SDK, including the logging level, directory, and the limits for total log file size.
 * @param log_config Local log parameters. See LogConfig{@link #LogConfig}.
 * @return 
 *        + 0: Success.<br>
 *        + –1: Failure. This API must be called before creating engine.<br>
 *        + –2: Failure. Invalid parameters.
 * @note This API must be called before createRTCVideo{@link #createRTCVideo}.
 * @list Engine Management
 * @order 30
 */
BYTERTC_API int setLogConfig(const LogConfig& log_config);



}  // namespace bytertc
