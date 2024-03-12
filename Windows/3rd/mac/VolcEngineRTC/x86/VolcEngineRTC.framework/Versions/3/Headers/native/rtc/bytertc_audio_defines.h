/*
 * Copyright (c) 2022 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC Audio Defines
 */

#pragma once

#include "bytertc_media_defines.h"
#include <string.h>
#include <math.h>
// use fft size 512 to calculate spectrum, so spectrum size is 512 / 2 + 1 = 257
#define SPECTRUM_SIZE 257

namespace bytertc {
/**
 * @locale zh
 * @type keytype
 * @brief 音频采样率，单位为 Hz。
 */
/**
 * @locale en
 * @type keytype
 * @brief Audio sample rate in Hz.
 */
enum AudioSampleRate {
    /**
     * @locale zh
     * @brief 默认设置。48000Hz。
     */
    /**
     * @locale en
     * @brief Default value. 48000Hz.
     */
    kAudioSampleRateAuto = -1,
    /**
     * @locale zh
     * @brief 8000Hz
     */
    /**
     * @locale en
     * @brief 8000Hz
     */
    kAudioSampleRate8000 = 8000,
    /**
     * @locale zh
     * @brief 16000Hz
     */
    /**
     * @locale en
     * @brief 16000Hz
     */
    kAudioSampleRate16000 = 16000,
    /**
     * @locale zh
     * @brief 32000Hz
     */
    /**
     * @locale en
     * @brief 32000Hz
     */
    kAudioSampleRate32000 = 32000,
    /**
     * @locale zh
     * @brief 44100Hz
     */
    /**
     * @locale en
     * @brief 44100Hz
     */
    kAudioSampleRate44100 = 44100,
    /**
     * @locale zh
     * @brief 48000Hz
     */
    /**
     * @locale en
     * @brief 48000Hz
     */
    kAudioSampleRate48000 = 48000
};
/**
 * @locale zh
 * @type keytype
 * @brief 音频声道。
 */
/**
 * @locale en
 * @type keytype
 * @brief Audio channel
 */
enum AudioChannel {
    /**
     * @locale zh
     * @brief 默认设置。
     */
    /**
     * @locale en
     * @brief Default value.
     */
    kAudioChannelAuto = -1,
    /**
     * @locale zh
     * @brief 单声道
     */
    /**
     * @locale en
     * @brief Mono channel.
     */
    kAudioChannelMono = 1,
    /**
     * @locale zh
     * @brief 双声道
     */
    /**
     * @locale en
     * @brief Dual channels.
     */
    kAudioChannelStereo = 2
};

/**
 * @locale zh
 * @type keytype
 * @brief 音频格式
 */
/**
 * @locale en
 * @type keytype
 * @brief Audio format
 */
struct AudioFormat {
    /**
     * @locale zh
     * @brief 音频采样率，详见 AudioSampleRate{@link #AudioSampleRate}
     */
    /**
     * @locale en
     * @brief Audio sample rate. See AudioSampleRate{@link #AudioSampleRate}
     */
    AudioSampleRate sample_rate = kAudioSampleRateAuto;
    /**
     * @locale zh
     * @brief 音频声道，详见 AudioChannel{@link #AudioChannel}
     */
    /**
     * @locale en
     * @brief Audio channels. See AudioChannel{@link #AudioChannel}
     */
    AudioChannel channel = kAudioChannelAuto;
    /**
     * @locale zh
     * @brief 单次回调的音频帧中包含的采样点数。默认值为 `0`，此时，采样点数取最小值。<br>
     *        最小值为回调间隔是 0.01s 时的值，即 `sampleRate * channel * 0.01s`。<br>
     *        最大值是 `2048`。超出取值范围时，采样点数取默认值。<br>
     *        该参数仅在设置读写回调时生效，调用 enableAudioFrameCallback{@link #IRTCVideo#enableAudioFrameCallback} 开启只读模式回调时设置该参数不生效。
     */
    /**
     * @locale en
     * @brief Samples per audio frame returned by callback. `0` by default. The default samples per callback is the minimum value.<br>
     *        The minimum value is `sampleRate * channel * 0.01s`, the value when the callback interval is 0.01s.<br>
     *        The maximum value is `2048`. If the value is invalid, the samples per callback uses the default value.<br>
     *        This parameter only takes effect when setting the read-write callback. It does not take effect when calling enableAudioFrameCallback{@link #IRTCVideo#enableAudioFrameCallback} to enable read-only callback.
     */
    int samples_per_call = 0;
};
/**
 * @locale zh
 * @type keytype
 * @brief 返回给音频处理器的音频类型。
 */
/**
 * @locale en
 * @type keytype
 * @brief The audio input for the audio processor.
 */
enum AudioProcessorMethod{
    /**
     * @locale zh
     * @brief 本地采集的音频。
     */
    /**
     * @locale en
     * @brief Locally captured audio frame.
     */
    kAudioProcessorMethodRecord = 0,
    /**
     * @locale zh
     * @brief 远端音频流的混音音频。
     */
    /**
     * @locale en
     * @brief The mixed remote audio.
     */
    kAudioProcessorMethodPlayback = 1,
    /**
     * @locale zh
     * @brief 各个远端音频流。
     */
    /**
     * @locale en
     * @brief The audio streams from remote users.
     */
    kAudioProcessorMethodRemoteUser = 2,
    /**
     * @locale zh
     * @hidden(Windows,Linux,macOS)
     * @brief 软件耳返音频。
     */
    /**
     * @locale en
     * @hidden(Windows,Linux,macOS)
     * @brief The SDK-level in-ear monitoring.
     */
    kAudioProcessorMethodEarMonitor = 3,
    /**
     * @locale zh
     * @hidden(Linux)
     * @brief 屏幕共享音频。
     */
    /**
     * @locale en
     * @hidden(Linux)
     * @brief The shared-screen audio.
     */
    kAudioProcessorMethodScreen = 4,
};
/**
 * @locale zh
 * @type keytype
 * @brief 音频设备类型
 */
/**
 * @locale en
 * @type keytype
 * @brief Type of audio device
 */
enum RTCAudioDeviceType {
    /**
     * @locale zh
     * @brief 未知设备类型
     */
    /**
     * @locale en
     * @brief Unknown device
     */
    kRTCAudioDeviceTypeUnknown = -1,
    /**
     * @locale zh
     * @brief 音频渲染设备
     */
    /**
     * @locale en
     * @brief Speaker or headphone
     */
    kRTCAudioDeviceTypeRenderDevice = 0,
    /**
     * @locale zh
     * @brief 音频采集设备
     */
    /**
     * @locale en
     * @brief Microphone
     */
    kRTCAudioDeviceTypeCaptureDevice = 1,
    /**
     * @locale zh
     * @brief 屏幕流音频设备
     */
    /**
     * @locale en
     * @brief Screen capturing audio device
     */
    kRTCAudioDeviceTypeScreenCaptureDevice = 2,
};

/**
 * @locale zh
 * @type keytype
 * @brief 音频播放设备
 */
/**
 * @locale en
 * @type keytype
 * @brief Audio playback device
 */
enum AudioRoute {
    /**
     * @locale zh
     * @brief 默认设备
     */
    /**
     * @locale en
     * @brief Default devices
     */
    kAudioRouteDefault = -1,
    /**
     * @locale zh
     * @brief 有线耳机
     */
    /**
     * @locale en
     * @brief Wired earphones
     */
    kAudioRouteHeadset = 1,
    /**
     * @locale zh
     * @brief 听筒
     */
    /**
     * @locale en
     * @brief Earpiece
     */
    kAudioRouteEarpiece = 2,
    /**
     * @locale zh
     * @brief 扬声器
     */
    /**
     * @locale en
     * @brief Speaker
     */
    kAudioRouteSpeakerphone = 3,
    /**
     * @locale zh
     * @brief 蓝牙耳机
     */
    /**
     * @locale en
     * @brief Bluetooth earphones
     */
    kAudioRouteHeadsetBluetooth = 4,
    /**
     * @locale zh
     * @brief USB设备
     */
    /**
     * @locale en
     * @brief USB Device
     */
    kAudioRouteHeadsetUSB = 5
};

/**
 * @locale zh
 * @type keytype
 * @brief 音频播放设备
 */
/**
 * @locale en
 * @type keytype
 * @brief  Audio playback device
 */
enum AudioPlaybackDevice {
    /**
     * @locale zh
     * @brief 有线耳机
     */
    /**
     * @locale en
     * @brief Wired earphones
     */
    kAudioPlaybackDeviceHeadset = 1,
    /**
     * @locale zh
     * @brief 听筒
     */
    /**
     * @locale en
     * @brief Earpiece
     */
    kAudioPlaybackDeviceEarpiece = 2,
    /**
     * @locale zh
     * @brief 扬声器
     */
    /**
     * @locale en
     * @brief Speaker
     */
    kAudioPlaybackDeviceSpeakerphone = 3,
    /**
     * @locale zh
     * @brief 蓝牙耳机
     */
    /**
     * @locale en
     * @brief Bluetooth earphones
     */
    kAudioPlaybackDeviceHeadsetBluetooth = 4,
    /**
     * @locale zh
     * @brief USB设备
     */
    /**
     * @locale en
     * @brief USB Device
     */
    kAudioPlaybackDeviceHeadsetUSB = 5
};

/**
 * @locale zh
 * @type keytype
 * @brief 音频场景类型。<br>
 *        选择音频场景后，RTC 会自动根据客户端音频采集播放设备和采集播放状态，适用通话音量/媒体音量。<br>
 *        如果预设的音频场景类型无法满足你的业务需要，请联系技术支持人员进行定制。
 */
/**
 * @locale en
 * @type keytype
 * @brief Audio scene type. <br>
 *        After selecting an audio scene, RTC will automatically apply call volume/media volume based on the client's audio capture playback device and status. <br>
 *        If the preset audio scene type cannot meet your business needs, please contact technical support classmate for customization.
 */
enum AudioScenarioType {
    /**
     * @locale zh
     * @brief 音乐场景。默认为此场景。<br>
     *        此场景适用于对音乐表现力有要求的场景。如音乐直播等。<br>
     *        音频采集播放设备和采集播放状态，到音量类型的映射如下：<br>
     *        <table>
     *           <tr><th></th><th>不采集音频</th><th>采集音频</th><th>备注</th></tr>
     *           <tr><td>设备自带麦克风和扬声器/听筒</td><td>媒体音量</td><td>通话音量</td><td>/</td></tr>
     *           <tr><td>有线耳机/ USB 耳机/ 外置声卡</td><td>媒体音量</td><td>媒体音量</td><td>/</td></tr>
     *           <tr><td>蓝牙耳机</td><td>媒体音量</td><td>媒体音量</td><td>即使蓝牙耳机有麦克风，也只能使用设备自带麦克风进行本地音频采集。</td></tr>
     *        </table>
     */
    /**
     * @locale en
     * @brief Music scene. Default setting. <br>
     *        This scene is suitable for scenes that require musical expression. Such as live music, etc. <br>
     *         Audio capture playback device and capture playback status, the mapping to the volume type is as follows: <br>
     *         <table>
     *            <tr><th></th><th>Mic Off</th><th>Mic On</th><th>Remarks</th><tr>
     *            <tr><td>Build-in microphone and speaker/earpiece</td><td>Media volume</td><td>Call volume</td><td>/</td></tr>
     *            <tr><td>Wired headset/ USB headset/ external sound card</td><td>Media volume</td><td> Media Volume</td><td>/</td></tr>
     *            <tr><td>Bluetooth Headset</td><td>Media Volume</td><td>Media Volume</td><td>Even if the Bluetooth headset has a microphone, you can only use the build-in microphone for local audio capture.</td></tr>
     *         </table>
     */
    kAudioScenarioTypeMusic = 0,
    /**
     * @locale zh
     * @brief 高质量通话场景。<br>
     *        此场景适用于对音乐表现力有要求，但又希望能够使用蓝牙耳机上自带的麦克风进行音频采集的场景。<br>
     *        此场景下，更倾向于使用媒体音量。由此，可能引起开关麦时音量突变。如不希望有此突变，请使用 `kAudioScenarioTypeHighQualityChat`。<br>
     *        此场景可以兼顾外放/使用蓝牙耳机时的音频体验；并尽可能避免使用蓝牙耳机时音量类型切换导致的听感突变。<br>
     *        音频采集播放设备和采集播放状态，到音量类型的映射如下：<br>
     *        <table>
     *           <tr><th></th><th>不采集音频</th><th>采集音频</th><th>备注</th></tr>
     *           <tr><td>设备自带麦克风和扬声器/听筒</td><td>媒体音量</td><td>通话音量</td><td>/</td></tr>
     *           <tr><td>有线耳机/ USB 耳机/ 外置声卡</td><td>媒体音量</td><td>媒体音量</td><td>/</td></tr>
     *           <tr><td>蓝牙耳机</td><td>通话音量</td><td>通话音量</td><td>能够使用蓝牙耳机上自带的麦克风进行音频采集。</td></tr>
     *        </table>
     */
    /**
     * @locale en
     * @brief High-quality call scenarios. <br>
     *        Media volume is perferred in this scenario. The preference may introduce switch of volume type when you switch on/off the microphone. To avoid the switch, use `AUDIO_SCENARIO_HIGHQUALITY_CHAT`.<br>
     *        This scenario can provide decent audio performance using the speaker/bluetooth earphones. It can also avoid sudden changes of volume type when switching to bluetooth earphones.<br>
     *         Audio capture playback device and capture playback status, the mapping to the volume type is as follows: <br>
     *         <table>
     *            <tr><th></th><th>Mic Off</th><th>Mic On</th><th>Remarks</th><tr>
     *            <tr><td>Build-in microphone and speaker/earpiece</td><td> Media volume </td><td> call volume </td><td>/</td></tr>
     *            <tr><td>Wired headset/ USB headset/ external sound card</td><td> Media volume </td><td> Media Volume </td><td>/</td></tr>
     *            <tr><td> Bluetooth Headset </td><td> Call Volume </td><td> Call Volume </td><td>The microphone on the Bluetooth headset can be used for audio capture. </td></tr>
     *         </table>
     */
    kAudioScenarioTypeHighQualityCommunication = 1,
    /**
     * @locale zh
     * @brief 纯通话音量场景。<br>
     *        此场景下，无论客户端音频采集播放设备和采集播放状态，全程使用通话音量。<br>
     *        适用于需要频繁上下麦的通话或会议场景。<br>
     *        此场景可以保持统一的音频模式，不会有音量突变的听感；<br>
     *        最大程度上的消除回声，使通话清晰度达到最优；<br>
     *        使用蓝牙耳机时，能够使用蓝牙耳机上自带的麦克风进行音频采集。<br>
     *        但是，使用媒体音量进行播放的其他音频的音量会被压低，且音质会变差。
     */
    /**
     * @locale en
     * @brief Call volume-only scene.<br>
     *        In this scenario, regardless of the client side audio acquisition and playback device and the acquisition and playback status, the call volume is used throughout the process.<br>
     *        Suitable for calls or meeting scenarios that require frequent access. <br>
     *        This scene maintains a uniform audio pattern without sudden volume changes in listening; echoes are eliminated to the greatest extent possible for optimum call clarity.<br>
     *        When using a Bluetooth headset, you can use the microphone that comes with the Bluetooth headset for audio capture. <br>
     *        However, this scene will depress the volume of other audio being played back using the media volume and the sound quality will deteriorate.
     */
    kAudioScenarioTypeCommunication = 2,
    /**
     * @locale zh
     * @brief 纯媒体场景。一般不建议使用。<br>
     *        此场景下，无论客户端音频采集播放设备和采集播放状态，全程使用媒体音量。<br>
     *        外放通话时，可能出现回声和啸叫，请联系技术支持人员。
     */
    /**
     * @locale en
     * @brief Pure media scene. It is generally not recommended.<br>
     *        In this scenario, regardless of the client side audio acquisition and playback device and the acquisition and playback status, the media volume is used throughout the process.<br>
     *        If the audio quality is unsatisfactory when you put on speaker, please contact our technical support team.
     */
    kAudioScenarioTypeMedia = 3,
    /**
     * @locale zh
     * @brief 游戏媒体场景。仅适合游戏场景。<br>
     *        若外放通话且无游戏音效消除优化时音质不理想，请联系技术支持人员。<br>
     *        音频采集播放设备和采集播放状态，到音量类型的映射如下：<br>
     *        <table>
     *           <tr><th></th><th>不采集音频</th><th>采集音频</th><th>备注</th></tr>
     *           <tr><td>设备自带麦克风和扬声器/听筒</td><td>媒体音量</td><td>媒体音量</td><td>/</td></tr>
     *           <tr><td>有线耳机/ USB 耳机/ 外置声卡</td><td>媒体音量</td><td>媒体音量</td><td>/</td></tr>
     *           <tr><td>蓝牙耳机</td><td>通话音量</td><td>通话音量</td><td>能够使用蓝牙耳机上自带的麦克风进行音频采集。</td></tr>
     *        </table>
     */
    /**
     * @locale en
     * @brief Game media scene. Only suitable for game scenes.<br>
     *        If the audio quality is unsatisfactory when you put on speaker, please contact our technical support team.<br>
     *        For different audio device and status, the selected volume type is as follows:<br>
     *         <table>
     *            <tr><th></th><th>Mic Off</th><th>Mic On</th><th>Remarks</th><tr>
     *            <tr><td>Build-in microphone and speaker/earpiece</td><td> Media volume </td><td> Media volume </td><td>/</td></tr>
     *            <tr><td>Wired headset/ USB headset/ external sound card</td><td> Media volume </td><td> Media Volume </td><td>/</td></tr>
     *            <tr><td> Bluetooth Headset </td><td> Call Volume </td><td> Call Volume </td><td> Ability to use the microphone included in the Bluetooth headset for audio capture. </td></tr>
     *         </table>
     */
    kAudioScenarioTypeGameStreaming = 4,
    /**
     * @locale zh
     * @brief 高质量畅聊场景。  <br>
     *        此场景和 `kAudioScenarioTypeHighQualityCommunication` 高度类似，唯一的差异在于：此场景下，在使用设备自带的麦克风和扬声器/听筒进行通话时，开关麦始终采用通话音量，不会引起音量类型突变。 <br>
     *        音频采集播放设备和采集播放状态，到音量类型的映射如下：<br>
     *        <table>
     *           <tr><th></th><th>不采集音频</th><th>采集音频</th><th>备注</th></tr>
     *           <tr><td>设备自带麦克风和扬声器/听筒</td><td>通话音量</td><td>通话音量</td><td>/</td></tr>
     *           <tr><td>有线耳机/ USB 耳机/ 外置声卡</td><td>媒体音量</td><td>媒体音量</td><td>/</td></tr>
     *           <tr><td>蓝牙耳机</td><td>通话音量</td><td>通话音量</td><td>能够使用蓝牙耳机上自带的麦克风进行音频采集。</td></tr>
     *        </table>
     */
    /**
     * @locale en
     * @brief High-quality chatting scenario <br>
     *        This scenerio is the same as `kAudioScenarioTypeHighQualityCommunication`, but in one case: in this scenerio, switching on/off the microphone does not change the volume type. When you talk with the built-in microphone and speaker/earpiece, the call volume is used all the time. <br>
     *        For different audio device and status, the selected volume type is as follows:<br>
     *         <table>
     *            <tr><th></th><th>Mic Off</th><th>Mic On</th><th>Remarks</th><tr>
     *            <tr><td>Build-in microphone and speaker/earpiece</td><td> Call volume </td><td> call volume </td><td>/</td></tr>
     *            <tr><td>Wired headset/ USB headset/ external sound card</td><td> Media volume </td><td> Media Volume </td><td>/</td></tr>
     *            <tr><td> Bluetooth Headset </td><td> Call Volume </td><td> Call Volume </td><td> Ability to use the microphone included in the Bluetooth headset for audio capture. </td></tr>
     *         </table>
     */
    kAudioScenarioTypeHighQualityChat = 5,
};
 /**
    * @locale zh
    * @hidden internal use only.
    * @type keytype
    * @brief 如果以下音频场景类型无法满足你的业务需要，请联系技术支持人员。
    */
 /**
    * @locale en
    * @hidden internal use only.
    * @type keytype
    * @brief If the following audio scenarios cannot meet your business needs, please contact our technical support team.
*/
enum AudioSceneType {
/**
     * @locale zh
     * @brief 默认场景 <br>
     *        此场景适用于对音乐表现力有要求的场景，如音乐直播等。 <br>
     *        音频采集播放设备和采集播放状态，到音量类型的映射如下：<br>
     * <table>
     *     <tr><th></th><th>不采集音频</th><th>采集音频</th><th>备注</th></tr>
     *     <tr><td>内置麦克风和扬声器</td><td>媒体音量</td><td>通话音量</td><td>/</td></tr>
     *     <tr><td>内置听筒</td><td>媒体音量</td><td>媒体音量</td><td>/</td></tr>
     *     <tr><td>有线耳机/ USB 耳机/ 外置声卡</td><td>媒体音量</td><td>媒体音量</td><td>/</td></tr>
     *     <tr><td>蓝牙耳机</td><td>媒体音量</td><td>媒体音量</td><td>即使蓝牙耳机有麦克风，也只能使用设备自带麦克风进行本地音频采集。</td></tr>
     * </table>
*/
/**
    * @locale en
    * @brief Default scenario. <br>
    *        This scenario is suitable for scenes that require musical expression, such as music live.<br>
    *        For different audio device and status, the selected volume type is as follows:       <br>
             <table>
     *          <tr><th></th><th>Mic Off</th><th>Mic On</th><th>Remarks</th><tr>
     *          <tr><td>Build-in microphone and speaker</td><td>Media volume</td><td>Call volume</td><td>/</td></tr>
     *          <tr><td>Build-in earpiece</td><td>Media volume</td><td>Media volume</td><td>/</td></tr>
     *          <tr><td>Wired headset/ USB headset/ external sound card</td><td>Media volume</td><td> Media Volume</td><td>/</td></tr>
     *          <tr><td>Bluetooth Headset</td><td>Media Volume</td><td>Media Volume</td><td>Even if the Bluetooth headset has a microphone, you can only use the build-in microphone for local audio capture.</td></tr>
     *       </table>
*/ 
    kAudioSceneTypeDefault = 0,
/**
     * @locale zh
     * @brief 语聊场景  <br>
     *        此场景下，无论客户端音频采集播放设备和采集播放状态，全程使用通话音量。<br>
     *        适用于需要频繁上下麦的通话或会议场景以及视频聊天室场景。<br>
     *        此场景可以保持统一的音频模式，不会有音量突变的听感。<br>
     *        此场景可以最大程度地消除回声，使通话清晰度达到最优。<br>
     *        使用蓝牙耳机时，能够使用蓝牙耳机上自带的麦克风进行音频采集。<br>
     *        但是，此场景会压低使用媒体音量进行播放的其他音频的音量，且音质会变差。
     */
/**
     * @locale en
     * @brief Chat scenario <br>
     *        This scenario uses the call volume regardless of the client-side audio device or status. <br>
     *        This scenario is suitable for calls or meetings that require turning on and off the microphone frequently. <br>
     *        Call volume is used the whole time and there will not be sudden changes in volume.<br>
     *        This scenario maximizes the elimination of echoes and has optimal call clarity.<br>
     *        You can use the microphone on the bluetooth earphones for audio capturing.<br>
     *        However, the volume of other audio played using media volume will be lowered, and the audio quality is worse.
*/
    kAudioSceneTypeChatRoom = 1,
/**
     * @locale zh
     * @brief 高音质语聊场景 <br>
     *        此场景下，无论客户端音频采集播放设备和采集播放状态，全程使用媒体音量。<br>
     *        外放通话时，可能出现回声和啸叫，请联系技术支持人员。
     */
/**
     * @locale en
     * @brief High-quality chat scenarios <br>
     *        This scenario uses the media volume regardless of the client-side audio device or status. <br>
     *        If the audio quality is unsatisfactory when you put on speaker, please contact the technical support.     
*/
    kAudioSceneTypeHighQualityChatRoom = 2,
    /**
     * @locale zh
     * @brief 低延迟场景 <br>
     *      适合低时延场景，如 k 歌场景。 <br>
     *      此场景下，无论客户端音频采集播放设备和采集播放状态，全程使用媒体音量。
     */
/**
     * @locale en
     * @brief low-latency scenarios <br>
     *        This scenario is suitable for low-latency scenarios such as Karaoke. <br>
     *        This scenario uses the media volume regardless of the client-side audio device or status. 
*/     
    kAudioSceneTypeLowLatency = 3,
};

/**
 * @locale zh
 * @type keytype
 * @brief 变声特效类型。如需更多类型，联系技术支持。
 */
/**
 * @locale en
 * @type keytype
 * @brief Change sound effect type. For more types, contact the technical supporters.
 */
enum VoiceChangerType {
    /**
     * @locale zh
     * @brief 原声，不含特效
     */
    /**
     * @locale en
     * @brief Acoustic, no special effects
     */
    kVoiceChangerTypeOriginal = 0,
    /**
     * @locale zh
     * @brief 巨人
     */
    /**
     * @locale en
     * @brief Giant
     */
    kVoiceChangerTypeGiant = 1,
    /**
     * @locale zh
     * @brief 花栗鼠
     */
    /**
     * @locale en
     * @brief Chipmunk
     */
    kVoiceChangerTypeChipmunk = 2,
    /**
     * @locale zh
     * @brief 小黄人
     */
    /**
     * @locale en
     * @brief Little yellow man
     */
    kVoiceChangerTypeMinionst = 3,
    /**
     * @locale zh
     * @brief 颤音
     */
    /**
     * @locale en
     * @brief Trill
     */
    kVoiceChangerTypeVibrato = 4,
    /**
     * @locale zh
     * @brief 机器人
     */
    /**
     * @locale en
     * @brief Robot
     */
    kVoiceChangerTypeRobot = 5,
};

/**
 * @locale zh
 * @type keytype
 * @brief Private method. 混响特效类型
 */
/**
 * @locale en
 * @type keytype
 * @brief Private method.  Reverb effect type
 */
enum VoiceReverbType {
    /**
     * @locale zh
     * @brief 原声，不含特效
     */
    /**
     * @locale en
     * @brief Acoustic, no special effects
     */
    kVoiceReverbTypeOriginal = 0,
    /**
     * @locale zh
     * @brief 回声
     */
    /**
     * @locale en
     * @brief Echo
     */
    kVoiceReverbTypeEcho = 1,
    /**
     * @locale zh
     * @brief 演唱会
     */
    /**
     * @locale en
     * @brief Concert
     */
    kVoiceReverbTypeConcert = 2,
    /**
     * @locale zh
     * @brief 空灵
     */
    /**
     * @locale en
     * @brief Ethereal
     */
    kVoiceReverbTypeEthereal = 3,
    /**
     * @locale zh
     * @brief KTV
     */
    /**
     * @locale en
     * @brief Karaoke
     */
    kVoiceReverbTypeKTV = 4,
    /**
     * @locale zh
     * @brief 录音棚
     */
    /**
     * @locale en
     * @brief Recording studio
     */
    kVoiceReverbTypeStudio = 5,
    /**
     * @locale zh
     * @brief 虚拟立体声
     */
    /**
     * @locale en
     * @brief Virtual Stereo
     */
    kVoiceReverbTypeVirtualStereo = 6,
    /**
     * @locale zh
     * @brief 空旷
     */
    /**
     * @locale en
     * @brief Spacious
     */
    kVoiceReverbTypeSpacious = 7,
    /**
     * @locale zh
     * @brief 3D人声
     */
    /**
     * @locale en
     * @brief 3D vocal
     */
    kVoiceReverbType3D = 8,
    /**
     * @locale zh
     * @hidden for internal use only
     * @brief 流行
     */
    /**
     * @locale en
     * @hidden for internal use only
     * @brief Pop
     */
    kVoiceReverbTypePop = 9,
    /**
     * @locale zh
     * @hidden for internal use only
     * @brief 蹦迪
     */
    /**
     * @locale en
     * @hidden for internal use only
     * @brief Disco
     */
    kVoiceReverbTypeDisco = 10,
    /**
     * @locale zh
     * @hidden for internal use only
     * @brief 老唱片
     */
    /**
     * @locale en
     * @hidden for internal use only
     * @brief Old Record
     */
    kVoiceReverbTypeOldRecord = 11,
    /**
     * @locale zh
     * @hidden for internal use only
     * @brief 和声
     */
    /**
     * @locale en
     * @hidden for internal use only
     * @brief Harmony
     */
    kVoiceReverbTypeHarmony = 12,
    /**
     * @locale zh
     * @hidden for internal use only
     * @brief 摇滚
     */
    /**
     * @locale en
     * @hidden for internal use only
     * @brief Rock
     */
    kVoiceReverbTypeRock = 13,
    /**
     * @locale zh
     * @hidden for internal use only
     * @brief 蓝调
     */
    /**
     * @locale en
     * @hidden for internal use only
     * @brief Blues
     */
    kVoiceReverbTypeBlues = 14,
    /**
     * @locale zh
     * @hidden for internal use only
     * @brief 爵士
     */
    /**
     * @locale en
     * @hidden for internal use only
     * @brief Jazz
     */
    kVoiceReverbTypeJazz = 15,
    /**
     * @locale zh
     * @hidden for internal use only
     * @brief 电子
     */
    /**
     * @locale en
     * @hidden for internal use only
     * @brief Electronic
     */
    kVoiceReverbTypeElectronic = 16,
    /**
     * @locale zh
     * @hidden for internal use only
     * @brief 黑胶
     */
    /**
     * @locale en
     * @hidden for internal use only
     * @brief Vinyl
     */
    kVoiceReverbTypeVinyl = 17,
    /**
     * @locale zh
     * @hidden for internal use only
     * @brief 密室
     */
    /**
     * @locale en
     * @hidden for internal use only
     * @brief Chamber
     */
    kVoiceReverbTypeChamber = 18,
};
/**
 * @locale zh
 * @type keytype
 * @brief 音频均衡效果。
 */
/**
 * @locale en
 * @type keytype
 * @brief Audio Equalization effect.
 */
enum VoiceEqualizationBandFrequency {
    /**
     * @locale zh
     * @brief 中心频率为 31Hz 的频带。
     */
    /**
     * @locale en
     * @brief The frequency band with a center frequency of 31Hz.
     */
    kVoiceEqualizationBandFrequency31 = 0,
    /**
     * @locale zh
     * @brief 中心频率为 62Hz 的频带。
     */
    /**
     * @locale en
     * @brief The frequency band with a center frequency of 62Hz.
     */
    kVoiceEqualizationBandFrequency62 = 1,
    /**
     * @locale zh
     * @brief 中心频率为 125Hz 的频带。
     */
    /**
     * @locale en
     * @brief The frequency band with a center frequency of 125Hz.
     */
    kVoiceEqualizationBandFrequency125 = 2,
        /**
     * @locale zh
     * @brief 中心频率为 250Hz 的频带。
     */
    /**
     * @locale en
     * @brief The frequency band with a center frequency of 250Hz.
     */
    kVoiceEqualizationBandFrequency250 = 3,
        /**
     * @locale zh
     * @brief 中心频率为 500Hz 的频带。
     */
    /**
     * @locale en
     * @brief The frequency band with a center frequency of 500Hz.
     */
    kVoiceEqualizationBandFrequency500 = 4,
        /**
     * @locale zh
     * @brief 中心频率为 1kHz 的频带。
     */
    /**
     * @locale en
     * @brief The frequency band with a center frequency of 1kHz.
     */
    kVoiceEqualizationBandFrequency1k = 5,
    /**
     * @locale zh
     * @brief 中心频率为 2kHz 的频带。
     */
    /**
     * @locale en
     * @brief The frequency band with a center frequency of 2kHz.
     */
    kVoiceEqualizationBandFrequency2k = 6,
    /**
     * @locale zh
     * @brief 中心频率为 4kHz 的频带。
     */
    /**
     * @locale en
     * @brief The frequency band with a center frequency of 4kHz.
     */
    kVoiceEqualizationBandFrequency4k = 7,
    /**
     * @locale zh
     * @brief 中心频率为 8kHz 的频带。
     */
    /**
     * @locale en
     * @brief The frequency band with a center frequency of 8kHz.
     */
    kVoiceEqualizationBandFrequency8k = 8,
    /**
     * @locale zh
     * @brief 中心频率为 16kHz 的频带。
     */
    /**
     * @locale en
     * @brief The frequency band with a center frequency of 16kHz.
     */
    kVoiceEqualizationBandFrequency16k = 9,
};
/**
 * @locale zh
 * @type keytype
 * @brief 语音均衡效果。
 */
/**
 * @locale en
 * @type keytype
 * @brief Voice equalization effect.
 */
struct VoiceEqualizationConfig {
    /**
     * @locale zh
     * @brief 频带。参看 VoiceEqualizationBandFrequency{@link #VoiceEqualizationBandFrequency}。
     */
    /**
     * @locale en
     * @brief Frequency band. See VoiceEqualizationBandFrequency{@link #VoiceEqualizationBandFrequency}.
     */
    VoiceEqualizationBandFrequency frequency;
    /**
     * @locale zh
     * @brief 频带增益（dB）。取值范围是 `[-15, 15]`。
     */
    /**
     * @locale en
     * @brief Gain of the frequency band in dB. The range is `[-15, 15]`.
     */
    int gain;
};
/**
 * @locale zh
 * @type keytype
 * @brief 音频混响效果。
 */
/**
 * @locale en
 * @type keytype
 * @brief Voice reverb effect.
 */
struct VoiceReverbConfig {
    /**
     * @locale zh
     * @brief 混响模拟的房间大小，取值范围 `[0.0, 100.0]`。默认值为 `50.0f`。房间越大，混响越强。
     */
    /**
     * @locale en
     * @brief The room size for reverb simulation. The range is `[0.0, 100.0]`. The default value is `50.0f`. The larger the room, the stronger the reverberation.
     */
    float room_size = 50.0f;
    /**
     * @locale zh
     * @brief 混响的拖尾长度，取值范围 `[0.0, 100.0]`。默认值为 `50.0f`。
     */
    /**
     * @locale en
     * @brief The decay time of the reverb effect. The range is `[0.0, 100.0]`. The default value is `50.0f`. 
     */
    float decay_time = 50.0f;
    /**
     * @locale zh
     * @brief 混响的衰减阻尼大小，取值范围 `[0.0, 100.0]`。默认值为 `50.0f`。
     */
    /**
     * @locale en
     * @brief The damping index of the reverb effect. The range is `[0.0, 100.0]`. The default value is `50.0f`. 
     */
    float damping = 50.0f;
    /**
     * @locale zh
     * @brief 早期反射信号强度。取值范围 `[-20.0, 10.0]`，单位为 dB。默认值为 `0.0f`。
     */
    /**
     * @locale en
     * @brief The Intensity of the wet signal in dB. The range is `[-20.0, 10.0]`. The default value is `0.0f`. 
     */
    float wet_gain = 0.0f;
    /**
     * @locale zh
     * @brief 原始信号强度。取值范围 `[-20.0, 10.0]`，单位为 dB。默认值为 `0.0f`。
     */
    /**
     * @locale en
     * @brief The Intensity of the dry signal in dB. The range is `[-20.0, 10.0]`. The default value is `0.0f`. 
     */
    float dry_gain = 0.0f;
    /**
     * @locale zh
     * @brief 早期反射信号的延迟。取值范围 `[0.0, 200.0]`，单位为 ms。默认值为 `0.0f`。
     */
    /**
     * @locale en
     * @brief The delay of the wet signal in ms. The range is `[0.0, 200.0]`. The default value is `0.0f`. 
     */
    float pre_delay = 0.0f;
};

/**
 * @locale zh
 * @type keytype
 * @brief 音频流来源的用户 ID 及对应的音量。
 */
/**
 * @locale en
 * @type keytype
 * @brief User ID of the source of the audio stream and the corresponding volume.
 */
struct AudioVolumeInfo {
    /**
     * @locale zh
     * @brief 线性音量，取值范围是：[0, 255]，与原始音量呈线性关系，数值越大，音量越大。<br>
     *        无声为 25 以下（绝对无声为 0，25 以下可视为无声），低音量为 25～76，中音量为 76～204，高音量为 204 以上。
     */
    /**
     * @locale en
     * @brief Linear volume, the value range is: [0,255], which has a linear relationship with the original volume.<br>
     * The larger the value, the greater the volume. Silence is below 25 (absolutely silent is 0, below 25 there is basically no sound, which can be regarded as silent),<br>
     * low volume is 25~76, medium volume is 76~204, and high volume is above 204
     */
    int linear_volume;
    /**
     * @locale zh
     * @brief 非线性音量，取值范围是：[–127, 0]，单位 dB。此音量范围是将原始音量进行对数转化，在中低音量时分辨更为灵敏，适用于 Active Speaker（房间内最活跃用户）的识别。<br>
     *        高音量为 0～–20 dB，中音量为 –20～–40dB，低音量为 –40～–60dB，若低于 –60 dB，则为无声。
     */
    /**
     * @locale en
     * @brief Non-linear volume, the value range is: [-127, 0], the unit is dB. This volume range is a logarithmic conversion of the original volume,<br>
     * and the resolution is more sensitive at medium and low volume, which is suitable for identification as an Active Speaker (the most active user in the room).<br>
     * The high volume is 0~-20dB, the medium volume is -20~-40dB, and the low volume is -40~-60dB. If it is lower than -60dB, it is silent.
     */
    int nonlinear_volume;
    /**
     * @locale zh
     * @brief 音频流来源的用户 ID
     */
    /**
     * @locale en
     * @brief User of the audio stream source ID
     */
    const char* uid;
};

/**
 * @locale zh
 * @type keytype
 * @brief 音频混音文件播放状态。
 */
/**
 * @locale en
 * @type keytype
 * @brief  Audio mix file playback status.
 */
enum AudioMixingState {
    /**
     * @locale zh
     * @brief 混音已加载
     */
    /**
     * @locale en
     * @brief Mix loaded
     */
    kAudioMixingStatePreloaded = 0,
    /**
     * @locale zh
     * @brief 混音正在播放
     */
    /**
     * @locale en
     * @brief Mix is playing
     */
    kAudioMixingStatePlaying,
    /**
     * @locale zh
     * @brief 混音暂停
     */
    /**
     * @locale en
     * @brief Mix Pause
     */
    kAudioMixingStatePaused,
    /**
     * @locale zh
     * @brief 混音停止
     */
    /**
     * @locale en
     * @brief Mixing stopped
     */
    kAudioMixingStateStopped,
    /**
     * @locale zh
     * @brief 混音播放失败
     */
    /**
     * @locale en
     * @brief Mix playback failed
     */
    kAudioMixingStateFailed,
    /**
     * @locale zh
     * @brief 混音播放结束
     */
    /**
     * @locale en
     * @brief End of mixing
     */
    kAudioMixingStateFinished,
    /**
     * @locale zh
     * @brief 准备PCM混音
     */
    /**
     * @locale en
     * @brief Prepare PCM Mix
     */
    kAudioMixingStatePCMEnabled,
    /**
     * @locale zh
     * @brief PCM混音播放结束
     */
    /**
     * @locale en
     * @brief End of PCM mix playback
     */
    kAudioMixingStatePCMDisabled,
};
/**
 * @locale zh
 * @type keytype
 * @brief 混音错误码。
 */
/**
 * @locale en
 * @type keytype
 * @brief Error code for audio mixing
 */
enum AudioMixingError {
    /**
     * @locale zh
     * @brief 正常
     */
    /**
     * @locale en
     * @brief OK
     */
    kAudioMixingErrorOk = 0,
    /**
     * @locale zh
     * @brief 预加载失败。找不到混音文件或者文件长度超出 20s
     */
    /**
     * @locale en
     * @brief Preload failed. Invalid path or the length exceeds 20s.
     */
    kAudioMixingErrorPreloadFailed,
    /**
     * @locale zh
     * @brief 混音开启失败。找不到混音文件或者混音文件打开失败
     */
    /**
     * @locale en
     * @brief Mixing failed. Invalid path or fail to open the file.
     */
    kAudioMixingErrorStartFailed,
    /**
     * @locale zh
     * @brief 混音 ID 异常
     */
    /**
     * @locale en
     * @brief Invalid mixID
     */
    kAudioMixingErrorIdNotFound,
    /**
     * @locale zh
     * @brief 设置混音文件的播放位置出错
     */
    /**
     * @locale en
     * @brief Invalid position
     */
    kAudioMixingErrorSetPositionFailed,
    /**
     * @locale zh
     * @brief 音量参数不合法，仅支持设置的音量值为[0, 400]
     */
    /**
     * @locale en
     * @brief Invalid volume. The range is [0, 400].
     */
    kAudioMixingErrorInValidVolume,
    /**
     * @locale zh
     * @brief 播放的文件与预加载的文件不一致。请先使用 unloadAudioMixing{@link #IAudioMixingManager#unloadAudioMixing} 卸载此前的文件。
     */
    /**
     * @locale en
     * @brief Another file was preloaded for mixing. Call unloadAudioMixing{@link #IAudioMixingManager#unloadAudioMixing} first.
     */
    kAudioMixingErrorLoadConflict,
    /**
     * @locale zh
     * @brief 不支持此混音类型。
     */
    /**
     * @locale en
     * @brief Do not support the mix type.
     */
    kAudioMixingErrorIdTypeNotMatch,
    /**
     * @locale zh
     * @brief 设置混音文件的音调不合法
     */
    /**
     * @locale en
     * @brief Invalid pitch value.
     */
    kAudioMixingErrorInValidPitch,
    /**
     * @locale zh
     * @brief 设置混音文件的音轨不合法
     */
    /**
     * @locale en
     * @brief Invalid audio track.
     */
    kAudioMixingErrorInValidAudioTrack,
    /**
     * @locale zh
     * @brief 混音文件正在启动中
     */
    /**
     * @locale en
     * @brief Mixing starting
     */
    kAudioMixingErrorIsStarting,
    /**
     * @locale zh
     * @brief 设置混音文件的播放速度不合法
     */
    /**
     * @locale en
     * @brief Invalid playback speed
     */
    kAudioMixingErrorInValidPlaybackSpeed,
    /**
     * @locale zh
     * @deprecated since 3.25 and will be deleted in 3.51
     * @brief 混音错误码，失败，已废弃
     */
    /**
     * @locale en
     * @deprecated since 3.45 and will be deleted in 3.51
     * @brief Audio mixing error code. Deprecated.
     */
    kAudioMixingErrorCanNotOpen = 701,
};
/**
 * @locale zh
 * @type keytype
 * @brief 播放状态。
 */
/**
 * @locale en
 * @type keytype
 * @brief Player state.
 */
enum PlayerState {
    /**
     * @locale zh
     * @brief 播放未启动
     */
    /**
     * @locale en
     * @brief Not started.
     */
    kPlayerStateIdle = 0,
    /**
     * @locale zh
     * @brief 已加载
     */
    /**
     * @locale en
     * @brief Preloaded.
     */
    kPlayerStatePreloaded,
    /**
     * @locale zh
     * @brief 已打开
     */
    /**
     * @locale en
     * @brief Opened.
     */
    kPlayerStateOpened,
    /**
     * @locale zh
     * @brief 正在播放
     */
    /**
     * @locale en
     * @brief Playing.
     */
    kPlayerStatePlaying,
    /**
     * @locale zh
     * @brief 播放已暂停
     */
    /**
     * @locale en
     * @brief Paused.
     */
    kPlayerStatePaused,
    /**
     * @locale zh
     * @brief 播放已停止
     */
    /**
     * @locale en
     * @brief Stopped.
     */
    kPlayerStateStopped,
    /**
     * @locale zh
     * @brief 播放失败
     */
    /**
     * @locale en
     * @brief Failed.
     */
    kPlayerStateFailed,
    /** {zh}
     * @brief 播放结束
     */
    /** {en}
     * @brief  finished.
     */
    kPlayerStateFinished,
};
/**
 * @locale zh
 * @type keytype
 * @brief 播放错误码。
 */
/**
 * @locale en
 * @type keytype
 * @brief Error code for audio playout.
 */
enum PlayerError {
    /**
     * @locale zh
     * @brief 正常
     */
    /**
     * @locale en
     * @brief OK
     */
    kPlayerErrorOK = 0,
    /**
     * @locale zh
     * @brief 不支持此类型
     */
    /**
     * @locale en
     * @brief Format not supported.
     */
    kPlayerErrorFormatNotSupport,
    /**
     * @locale zh
     * @brief 无效的播放路径
     */
    /**
     * @locale en
     * @brief Invalid file path.
     */
    kPlayerErrorInvalidPath,
    /**
     * @locale zh
     * @brief 未满足前序接口调用的要求。请查看具体接口文档。
     */
    /**
     * @locale en
     * @brief The prerequisite is not met. Check the specific API doc.
     */
    kPlayerErrorInvalidState,
    /**
     * @locale zh
     * @brief 设置播放位置出错。
     */
    /**
     * @locale en
     * @brief Invalid position.
     */
    kPlayerErrorInvalidPosition,
    /**
     * @locale zh
     * @brief 音量参数不合法。
     */
    /**
     * @locale en
     * @brief Invalid volume.
     */
    kPlayerErrorInvalidVolume,
    /**
     * @locale zh
     * @brief 音调参数设置不合法。
     */
    /**
     * @locale en
     * @brief Invalid pitch value.
     */
    kPlayerErrorInvalidPitch,
    /**
     * @locale zh
     * @brief 音轨参数设置不合法。
     */
    /**
     * @locale en
     * @brief Invalid audio track.
     */
    kPlayerErrorInvalidAudioTrackIndex,
    /**
     * @locale zh
     * @brief 播放速度参数设置不合法
     */
    /**
     * @locale en
     * @brief Invalid playback speed.
     */
    kPlayerErrorInvalidPlaybackSpeed,
    /**
     * @locale zh
     * @brief 音效 ID 异常。还未加载或播放文件，就调用其他 API。
     */
    /**
     * @locale en
     * @brief Invalid effect ID. Receive this error code when you call other APIs before the audio file is preloaded or opened.
     */
    kPlayerErrorInvalidEffectId,
};

/**
 * @locale zh
 * @type keytype
 * @brief 是否开启耳返功能
 */
/**
 * @locale en
 * @type keytype
 * @brief  Whether to turn on the earphone monitoring function
 */
enum EarMonitorMode {
    /**
     * @locale zh
     * @brief 不开启
     */
    /**
     * @locale en
     * @brief Not open
     */
    kEarMonitorModeOff = 0,
    /**
     * @locale zh
     * @brief 开启
     */
    /**
     * @locale en
     * @brief Open
     */
    kEarMonitorModeOn = 1,
};

/**
 * @locale zh
 * @hidden currently not available
 * @type keytype
 * @region 音频管理
 * @brief 音频编码类型
 */
/**
 * @locale en
 * @hidden currently not available
 * @type keytype
 * @region audio management
 * @brief Audio encoding type
 */
enum AudioCodecType {
    /**
     * @locale zh
     * @brief 未知编码类型
     */
    /**
     * @locale en
     * @brief Unknown encoding type
     */
    kAudioCodecTypeNone = 0,
    /**
     * @locale zh
     * @brief Opus 编码类型
     */
    /**
     * @locale en
     * @brief Opus  encoding type
     */
    kAudioCodecTypeOpus,
    /**
     * @hidden internal use only
     */
    kAudioCodecTypeAac,
    /**
     * @hidden internal use only
     */
    kAudioCodecTypeAacLC = 2,
    /**
     * @hidden internal use only
     */
    kAudioCodecTypeAacHEv1,
    /**
     * @hidden internal use only
     */
    kAudioCodecTypeAacHEv2,
    /**
     * @hidden internal use only
     */
    kAudioCodecTypeAacLCadts,
};
/**
 * @locale zh
 * @type keytype
 * @brief 音频输入格式
 */
/**
 * @locale en
 * @type keytype
 * @brief Audio input format type
 */
enum class AudioFormatType {
    /**
     * @locale zh<br>
     *  PCM_S16
     */
    /**
     * @locale en<br>
     *  PCM_S16
     */
    kRawPCMs16 = 0,
    /**
     * @locale zh<br>
     *  PCM_S32
     */
    /**
     * @locale en<br>
     *  PCM_S32
     */
    kRawPCMs32 = 1,
};

/**
 * @locale zh
 * @type keytype
 * @brief 蓝牙模式, 仅能在媒体模式下被设置
 */
/**
 * @locale en
 * @type keytype
 * @brief bluetooth mode, it works only in media mode.
 */
enum BluetoothMode {
    /**
     * @locale zh
     * @brief 自动选择模式
     */
    /**
     * @locale en
     * @brief select bluetooth mode automatically.
     */
    kBluetoothModeAuto = 0,
    /**
     * @locale zh
     * @brief 使用A2DP模式
     */
    /**
     * @locale en
     * @brief use A2DP mode
     */
    kBluetoothModeA2DP,
    /**
     * @locale zh
     * @brief HFP 模式
     */
    /**
     * @locale en
     * @brief use HFP mode
     */
    kBluetoothModeHFP
};

/**
 * @locale zh
 * @type keytype
 * @brief 音频输入源类型
 */
/**
 * @locale en
 * @type keytype
 * @brief  Audio input source type
 */
enum AudioSourceType {
    /**
     * @locale zh<br>
     *  自定义采集音频源
     */
    /**
     * @locale en<br>
     *  Custom Capture Audio Source
     */
    kAudioSourceTypeExternal = 0,
    /**
     * @locale zh<br>
     *  RTC SDK 内部采集音频源
     */
    /**
     * @locale en<br>
     *  RTC SDK internal acquisition audio source
     */
    kAudioSourceTypeInternal,
};

/**
 * @locale zh
 * @type keytype
 * @brief 音频输出类型
 */
/**
 * @locale en
 * @type keytype
 * @brief Audio output type
 */
enum AudioRenderType {
    /**
     * @locale zh<br>
     *  自定义渲染
     */
    /**
     * @locale en<br>
     *  Custom Render
     */
    kAudioRenderTypeExternal = 0,
    /**
     * @locale zh<br>
     *  RTC SDK 内部渲染
     */
    /**
     * @locale en<br>
     *  RTC SDK internal render
     */
    kAudioRenderTypeInternal,
};

/**
 * @locale zh
 * @type keytype
 * @brief 语音识别服务鉴权方式，详情请咨询语音识别服务相关人员
 */
/**
 * @locale en
 * @type keytype
 * @brief Speech recognition service authentication method, please consult the speech recognition service related classmates for details
 */
enum ASRAuthorizationType {
    /**
     * @locale zh
     * @brief Token 鉴权
     */
    /**
     * @locale en
     * @brief Token authentication
     */
    kASRAuthorizationTypeToken = 0,
    /**
     * @locale zh
     * @brief Signature 鉴权
     */
    /**
     * @locale en
     * @brief Signature authentication
     */
    kASRAuthorizationTypeSignature = 1,
};

/**
 * @locale zh
 * @type keytype
 * @brief 使用自动语音识别服务所需校验信息
 */
/**
 * @locale en
 * @type keytype
 * @brief Verification information required to use automatic speech recognition services
 */
struct RTCASRConfig {
    /**
     * @locale zh
     * @brief 应用 ID
     */
    /**
     * @locale en
     * @brief Application ID
     */
    const char* app_id = 0;
    /**
     * @locale zh
     * @brief 用户 ID
     */
    /**
     * @locale en
     * @brief User ID
     */
    const char* user_id = 0;
    /**
     * @locale zh
     * @brief 鉴权方式，参看 ASRAuthorizationType{@link #ASRAuthorizationType}
     */
    /**
     * @locale en
     * @brief For authentication methods. See ASRAuthorizationType{@link #ASRAuthorizationType}
     */
    ASRAuthorizationType authorization_type = kASRAuthorizationTypeToken;
    /**
     * @locale zh
     * @brief 访问令牌
     */
    /**
     * @locale en
     * @brief Access token
     */
    const char* access_token = 0;
    /**
     * @locale zh
     * @brief 私钥。Signature 鉴权模式下不能为空，token 鉴权模式下为空。参看[关于鉴权](https://www.volcengine.com/docs/6561/107789)
     */
    /**
     * @locale en
     * @brief Private key. Signature  cannot be empty in authentication mode, and it is empty in token authentication mode. See [Authentication Method](https://docs.byteplus.com/speech/docs/authentication-method).
     */
    const char* secret_key = 0;
    /**
     * @locale zh
     * @brief 场景信息，参看[业务集群](https://www.volcengine.com/docs/6561/80818#_3-2-2-%E5%8F%91%E9%80%81-full-client-request)
     */
    /**
     * @locale en
     * @brief For scenario information. See Business Clusters (https://docs.byteplus.com/en/speech/docs/real-time-speech-recog)
     */
    const char* cluster = 0;
};

/**
 * @locale zh
 * @hidden(Windows,Linux,macOS)
 * @type keytype
 * @brief 语音识别服务错误码。  <br>
 *        除网络原因导致的错误，语音识别服务内部会自行重试之外，其他错误都会停止服务，此时建议再次调用 `startASR` 重启语音识别功能。
 */
/**
 * @locale en
 * @hidden currently not available
 * @type keytype
 * @brief Speech recognition service error code.   <br>
 *        Except for errors caused by network reasons, the speech recognition service will retry itself, other errors will stop the service. At this time, it is recommended to call `startASR` again to restart the speech recognition function.
 */
enum RTCASRErrorCode {
    /**
     * @locale zh
     * @brief 网络连接中断，服务不可用，内部会进行重连
     */
    /**
     * @locale en
     * @brief The network connection is broken, the service is unavailable, and internal reconnection will be carried out
     */
    kRTCASRErrorNetworkInterrupted = -1,
    /**
     * @locale zh
     * @brief 重复调用 `startASR`。开启语音识别服务后，你需要先调用 `stopASR` 停止语音识别服务，才能二次调用 `startASR` 再次开启服务。
     */
    /**
     * @locale en
     * @brief Repeatedly call `startASR`. After starting the speech recognition service, you need to call `stopASR` to stop the speech recognition service before you can call `startASR` again to start the service.
     */
    kRTCASRErrorAlreadyStarted = -2,
    /**
     * @locale zh
     * @brief 语音识别服务所需 token 为空
     */
    /**
     * @locale en
     * @brief The token required by the speech recognition service is empty
     */
    kRTCASRErrorTokenEmpty = -3,
    /**
     * @locale zh
     * @brief Signature 鉴权模式下 secret_key 为空
     */
    /**
     * @locale en
     * @brief Signature  secret_key empty in authentication mode
     */
    kRTCErrorSignatureKeyEmpty = -4,
    /**
     * @locale zh
     * @brief 用户 ID 为空
     */
    /**
     * @locale en
     * @brief User ID is empty
     */
    kRTCASRErrorUserIdNull = -5,
    /**
     * @locale zh
     * @brief 应用 ID 为空
     */
    /**
     * @locale en
     * @brief Application ID is empty
     */
    kRTCASRErrorAPPIDNull = -6,
    /**
     * @locale zh
     * @brief 语音识别服务 cluster 为空
     */
    /**
     * @locale en
     * @brief Speech recognition service cluster is empty
     */
    kRTCASRErrorClusterNull = -7,
    /**
     * @locale zh
     * @brief 语音识别服务连接失败，该版本没有语音识别功能，请联系 RTC 技术支持。
     */
    /**
     * @locale en
     * @brief The speech recognition service connection failed, this version does not have speech recognition function, please contact RTC technical support.
     */
    kRTCASRErrorOperationDenied = -8
};

/**
 * @locale zh
 * @type keytype
 * @brief 混音播放类型
 */
/**
 * @locale en
 * @type keytype
 * @brief Mixing type
 */
enum AudioMixingType {
    /**
     * @locale zh
     * @brief 仅本地播放
     */
    /**
     * @locale en
     * @brief Played at the local device only
     */
    kAudioMixingTypePlayout,
    /**
     * @locale zh
     * @brief 仅远端播放
     */
    /**
     * @locale en
     * @brief Sent to the remote devices only
     */
    kAudioMixingTypePublish,
    /**
     * @locale zh
     * @brief 本地和远端同时播放
     */
    /**
     * @locale en
     * @brief Played at the local device and sent to the remote devices.
     */
    kAudioMixingTypePlayoutAndPublish
};

/**
 * @locale zh
 * @type keytype
 * @brief 混音配置
 */
/**
 * @locale en
 * @type keytype
 * @brief  Mixing configuration
 */
struct AudioMixingConfig {
    /**
     * @locale zh
     * @brief 混音播放类型，详见 AudioMixingType{@link #AudioMixingType}
     */
    /**
     * @locale en
     * @brief For mixing playback types. See AudioMixingType{@link #AudioMixingType}
     */
    AudioMixingType type;
    /**
     * @locale zh
     * @brief 混音播放次数，<br>
     *       + play_count <= 0: 无限循环  <br>
     *       + play_count == 1: 播放一次（默认）  <br>
     *       + play_count > 1: 播放 play_count 次
     */
    /**
     * @locale en
     * @brief Mix playback times,<br>
     *        + Play_count < = 0: Infinite loop <br>
     *        + Play_count == 1: Play once (default) <br>
     *        + Play_count > 1: Play play_count times
     */
    int play_count;
     /**
      * @locale zh
      * @brief 混音时音频文件播放进度条位置，参数为整数，单位为毫秒
      */
     /**
      * @locale en
      * @brief The position of the audio file playback progress bar during audio mixing, the parameter should be an integer, in milliseconds.
      */
     int position;
     /**
      * @locale zh
      * @brief 设置音频文件播放进度回调的时间间隔，参数为大于 0 的 10 的倍数，单位为毫秒，设置后 SDK 将按照设置的值触发 `onAudioMixingPlayingProgress` 回调，默认不回调。  <br>
      *        + 当传入的值不能被 10 整除时，则默认向上取整 10，如设为 52ms 时会默认调整为 60ms。  <br>
      *        + 当传入的值小于等于 0 时，不会触发进度回调。  
      */
     /**
      * @locale en
      * @brief Set the time interval (ms) for the audio file playing progress callback. The `onAudioMixingPlayingProgress` callback then will be triggered according to the set value, no callback by default.  <br>
      *       + The value of interval is a multiple of 10 greater than 0. When the value set is not divisible by 10, the default is rounded up by 10. For example, if the value is set to 52ms, it will be automatically adjusted to 60ms, then the SDK will trigger `onAudioMixingPlayingProgress` callback at the set interval.  <br>
      *       + If the value is less than or equals to 0, the callback will not be triggered.  
      */
    int64_t callback_on_progress_interval = 0;
    /**
     * @locale zh
     * @brief 在采集音频数据时，附带本地混音文件播放进度的时间戳。启用此功能会提升远端人声和音频文件混音播放时的同步效果。 <br>
     *        + 仅在单个音频文件混音时使用有效。<br>
     *        + `true` 时开启此功能，`false` 时关闭此功能，默认为关闭。
     */
    /**
     * @locale en
     * @brief Attach the process information of local audio file mixing to the captured audio data. Enable the function to enhance the synchronicity of the remote audio mixing. <br>
     *        + The function is effective when mixing a single audio file. <br>
     *        + Use `true` for enabling the function and `false` for disable the function. The default is `false`.
     */
    bool sync_progress_to_record_frame = false;
};

/**
 * @locale zh
 * @type keytype
 * @brief 混音播放声道类型
 */
/**
 * @locale en
 * @type keytype
 * @brief  Mix playback channel type
 */
enum AudioMixingDualMonoMode{
    /**
     * @locale zh
     * @brief 和音频文件一致
     */
    /**
     * @locale en
     * @brief Consistent with audio files
     */
    kAudioMixingDualMonoModeAuto,
    /**
     * @locale zh
     * @brief 只能听到音频文件中左声道的音频
     */
    /**
     * @locale en
     * @brief Only the left channel audio in the audio file can be heard
     */
    kAudioMixingDualMonoModeL,
    /**
     * @locale zh
     * @brief 只能听到音频文件中右声道的音频
     */
    /**
     * @locale en
     * @brief Only the right channel audio in the audio file can be heard
     */
    kAudioMixingDualMonoModeR,
    /**
     * @locale zh
     * @brief 能同时听到音频文件中左右声道的音频
     */
    /**
     * @locale en
     * @brief Can hear the left and right audio channels in the audio file at the same time
     */
    kAudioMixingDualMonoModeMix
};
/**
 * @locale zh
 * @type keytype
 * @brief 混音配置
 */
/**
 * @locale en
 * @type keytype
 * @brief Mixing configuration
 */
struct AudioEffectPlayerConfig {
    /**
     * @locale zh
     * @brief 混音播放类型，详见 AudioMixingType{@link #AudioMixingType} 
     */ 
    /**
     * @locale en
     * @brief Mixing playback types. See AudioMixingType{@link #AudioMixingType}
     */
    AudioMixingType type = kAudioMixingTypePlayoutAndPublish;
    /**
     * @locale zh
     * @brief 混音播放次数<br>
     *       + play_count <= 0: 无限循环  <br>
     *       + play_count == 1: 播放一次（默认）  <br>
     *       + play_count > 1: 播放 play_count 次
     */
    /**
     * @locale en
     * @brief Mix playback times<br>
     *        + Play_count < = 0: Infinite loop <br>
     *        + Play_count == 1: Play once (default) <br>
     *        + Play_count > 1: Play play_count times
     */
    int play_count = 1;
    /**
     * @locale zh
     * @brief 与音乐文件原始音调相比的升高/降低值，取值范围为 `[-12，12]`，默认值为 0。每相邻两个值的音高距离相差半音，正值表示升调，负值表示降调。
     */
    /**
     * @locale en
     * @brief The increase or decrease value compared with the original pitch of the music file. The range is `[-12, 12]`. The default value is 0. The pitch distance between two adjacent values is half a step. A positive value indicates a rising pitch, and a negative value indicates a falling pitch.
     */
    int pitch = 0;
    /**
     * @locale zh
     * @brief 混音起始位置。默认值为 0，单位为毫秒。
     */
    /**
     * @locale en
     * @brief The starting position in ms. 0 by default.
     */
    int start_pos = 0;
};
/**
 * @locale zh
 * @type keytype
 * @brief 混音配置
 */
/**
 * @locale en
 * @type keytype
 * @brief Mixing configuration
 */
struct MediaPlayerConfig {
    /**
     * @locale zh
     * @brief 混音播放次数<br>
     *       + play_count <= 0: 无限循环  <br>
     *       + play_count == 1: 播放一次（默认）  <br>
     *       + play_count > 1: 播放 play_count 次
     */
    /**
     * @locale en
     * @brief Mix playback times<br>
     *        + Play_count < = 0: Infinite loop <br>
     *        + Play_count == 1: Play once (default) <br>
     *        + Play_count > 1: Play play_count times
     */
    int play_count = 1;
    /**
     * @locale zh
     * @brief 混音起始位置。默认值为 0，单位为毫秒。
     */
    /**
     * @locale en
     * @brief The starting position in ms. 0 by default.
     */
    int start_pos = 0;
    /**
     * @locale zh
     * @brief 设置音频文件混音时，收到 onMediaPlayerPlayingProgress{@link #IMediaPlayerEventHandler#onMediaPlayerPlayingProgress} 的间隔。单位毫秒。<br>
     *       + interval > 0 时，触发回调。实际间隔为 10 的倍数。如果输入数值不能被 10 整除，将自动向上取整。例如传入 `52`，实际间隔为 60 ms。<br>
     *       + interval <= 0 时，不会触发回调。
     */
     /**
     * @locale en
     * @brief Set the interval of the periodic callback onMediaPlayerPlayingProgress{@link #IMediaPlayerEventHandler#onMediaPlayerPlayingProgress} during audio mixing in ms.<br>
     *       + interval > 0: The callback is enabled. The actual interval is `10*(mod(10)+1)`.<br>
     *       + interval <= 0: The callback is disabled.
     */
    int64_t callback_on_progress_interval = 0;
    /**
     * @locale zh
     * @brief 在采集音频数据时，附带本地混音文件播放进度的时间戳。启用此功能会提升远端人声和音频文件混音播放时的同步效果。 <br>
     *        + 仅在单个音频文件混音时使用有效。<br>
     *        + `true` 时开启此功能，`false` 时关闭此功能，默认为关闭。
     */
    /**
     * @locale en
     * @brief Attach the process information of local audio file mixing to the captured audio data. Enable the function to enhance the synchronicity of the remote audio mixing. <br>
     *        + The function is effective when mixing a single audio file. <br>
     *        + Use `true` for enabling the function and `false` for disable the function. The default is `false`.
     */
    bool sync_progress_to_record_frame = false;
    /**
    * @locale zh
    * @brief 是否自动播放。如果不自动播放，调用 start{@link #IMediaPlayer#start} 播放音乐文件。
    */
    /**
    * @locale en
    * @brief Play the audio automatically. If not, call start{@link #IMediaPlayer#start} to play the audio.
    */
    bool auto_play = true;
    /**
     * @locale zh
     * @brief 混音播放类型，详见 AudioMixingType{@link #AudioMixingType}
     */
    /**
     * @locale en
     * @brief For mixing playback types. See AudioMixingType{@link #AudioMixingType}
     */
    AudioMixingType type = kAudioMixingTypePlayoutAndPublish;
};

/**
 * @locale zh
 * @type keytype
 * @brief 音量回调模式。
 */
/**
 * @locale en
 * @type keytype
 * @brief The volume callback modes.
 */
enum AudioReportMode {
    /**
     * @locale zh
     * @brief 默认始终开启音量回调。
     */
    /**
     * @locale en
     * @brief Always-on(Default).
     */
    kAudioReportModeNormal,
   /**
     * @locale zh
     * @brief 可见用户进房并停止推流后，关闭音量回调。
     */
    /**
     * @locale en
     * @brief After visibly joining a room and unpublish your streams, disable the volume callback.
     */
    kAudioReportModeDisconnect,
    /**
     * @locale zh
     * @brief 可见用户进房并停止推流后，开启音量回调，回调值重置为0。
     */
    /**
     * @locale en
     * @brief After visibly joining a room and unpublish your streams, enable the volume callback. The volume is reset to 0.
     */
    kAudioReportModeReset,
};

/**
 * @locale zh
 * @type keytype
 * @brief onLocalAudioPropertiesReport{@link #IRTCVideoEventHandler#onLocalAudioPropertiesReport} 中包含的音频信息的范围。
 */
/**
 * @locale en
 * @type keytype
 * @brief The audio info included in onLocalAudioPropertiesReport{@link #IRTCVideoEventHandler#onLocalAudioPropertiesReport}.
 */
enum AudioPropertiesMode {
    /**
     * @locale zh
     * @brief 仅包含本地麦克风采集的音频数据和本地屏幕音频采集数据。
     */
    /**
     * @locale en
     * @brief Only locally captured microphone audio info and locally captured screen audio info are included.
     */
    kAudioPropertiesModeMicrophone,
    /**
     * @locale zh
     * @brief 包含以下信息：<br>
     *        + 本地麦克风采集的音频数据和本地屏幕音频采集数据；<br>
     *        + 本地混音的音频数据。
     */
    /**
     * @locale en
     * @brief The following information are included:<br>
     *        + Locally captured microphone audio info and locally captured screen audio info;<br>
     *        + Locally audio mixing info.
     */
    kAudioPropertiesModeAudioMixing
};

/**
 * @locale zh
 * @type keytype
 * @brief 音频属性信息提示的相关配置。
 */
/**
 * @locale en
 * @type keytype
 * @brief Configuration for audio property prompt.
 */
struct AudioPropertiesConfig {
    /**
     * @locale zh
     * @brief 信息提示间隔，单位：ms <br>
     *       + `<= 0`: 关闭信息提示  <br>
     *       + `(0,100]`: 开启信息提示，不合法的 interval 值，SDK 自动设置为 100ms  <br>
     *       + `> 100`: 开启信息提示，并将信息提示间隔设置为此值  
     */
    /**
     * @locale en
     * @brief Prompt interval in ms <br>
     *        + `<= 0`: Turn off prompt <br>
     *        + `(0,100]`: Invalid interval value, and will be automatically reset to 100ms. <br>
     *        + `> 100`: the actual value of interval
     */
    int interval = 0;

    /**
     * @locale zh
     * @brief 是否开启音频频谱检测。
     */
    /**
     * @locale en
     * @brief Whether to enable audio spectrum detection.
     */
    bool enable_spectrum = false;

    /**
     * @locale zh
     * @brief 是否开启人声检测 (VAD)。
     */
    /**
     * @locale en
     * @brief Whether to enable Voice Activity Detection.
     */
    bool enable_vad = false;

    /**
     * @locale zh
     * @brief 音量回调配置模式。详见 AudioReportMode{@link #AudioReportMode}。
     */
    /**
     * @locale en
     * @brief The volume callback modes. See AudioReportMode{@link #AudioReportMode}.
     */
    AudioReportMode local_main_report_mode = kAudioReportModeNormal;

    /**
     * @locale zh
     * @brief 适用于音频属性信息提示的平滑系数。取值范围是 `(0.0, 1.0]`。<br>
     *        默认值为 `1.0`，不开启平滑效果；值越小，提示音量平滑效果越明显。如果要开启平滑效果，可以设置为 `0.3`。
     */
    /**
     * @locale en
     * @brief The smoothing coefficient for audio attribute information prompt. The range is `(0.0, 1.0]`. <br>
     *        The default value is `1.0`, which means the smoothing effect is off by default. Smaller the value, smoother the audio volume prompt. If you want to enable the smooth effect, the recommended value is `0.3`.
     */
    float smooth = 1.0f;   
        
    /**
     * @locale zh
     * @brief onLocalAudioPropertiesReport{@link #IRTCVideoEventHandler#onLocalAudioPropertiesReport} 中包含音频数据的范围。参看 AudioPropertiesMode{@link #AudioPropertiesMode}。<br>
     *        默认仅包含本地麦克风采集的音频数据和本地屏幕音频采集数据。
     */
    /**
     * @locale en
     * @brief The audio info included in onLocalAudioPropertiesReport{@link #IRTCVideoEventHandler#onLocalAudioPropertiesReport}. See AudioPropertiesMode{@link #AudioPropertiesMode}.<br>
     *        Locally captured microphone audio info and locally captured screen audio info are included by default.
     */
    AudioPropertiesMode audio_report_mode = kAudioPropertiesModeMicrophone;
    /**
     * @locale zh
     * @brief 是否回调本地用户的人声基频。
     */
    /**
     * @locale en
     * @brief Sets whether to return the vocal pitch of the local user. 
     */
    bool enable_voice_pitch = false;

    /** {zh}
     * @hidden internal use
     * @brief 是否回调设备采播延时。
     */
    /** {en}
     * @hidden internal use
     * @brief Sets whether to return the record and playout delay. 
     */
    bool enable_device_loop_delay = true;
};
/**
 * @locale zh
 * @type keytype
 * @brief 音频属性信息  
 */
/**
 * @locale en
 * @type keytype
 * @brief Audio properties   
 */
struct AudioPropertiesInfo {
    /**
     * @locale zh
     * @brief 线性音量，与原始音量呈线性关系，数值越大，音量越大。取值范围是：[0,255]。<br>
     *        - [0, 25]: 无声 <br>
     *        - [26, 75]: 低音量 <br>
     *        - [76, 204]: 中音量 <br>
     *        - [205, 255]: 高音量 
     */
    /**
     * @locale en
     * @brief linear volume. The value is in linear relation to the original volume. The higher the value, the higher the volume. The range is [0,255]. <br>
     *        - [0, 25]: Silence <br>
     *        - [26, 75]: Low volume <br>
     *        - [76, 204]: Medium volume <br>
     *        - [205, 255]: High volume 
     */
    int linear_volume = 0;
    /**
     * @locale zh
     * @brief 非线性音量。由原始音量的对数值转化而来，因此在中低音量时更灵敏，可以用作 Active Speaker（房间内最活跃用户）的识别。取值范围是：[-127，0]，单位 dB。 <br>
     *        - [-127, -60]: 无声 <br>
     *        - [-59, -40]: 低音量 <br>
     *        - [-39, -20]: 中音量 <br>
     *        - [-19, 0]: 高音量 
     */
    /**
     * @locale en
     * @brief non-linear volume in dB. The value is in proportion to the log value of the original volume. You can use the value to recognize the Active Speaker in the room. The range is [-127, 0]. <br>
     *        - [-127, -60]: Silence <br>
     *        - [-59, -40]: Low volume <br>
     *        - [-39, -20]: Medium volume <br>
     *        - [-19, 0]: High volume 
     */
    int nonlinear_volume = 0;
    /**
     * @locale zh
     * @brief 频谱数组。默认长度为 257。
     */
    /**
     * @locale en
     * @brief Spectrum array. The default length is 257.
     */
    float spectrum[SPECTRUM_SIZE] = {0};
    /**
     * @locale zh
     * @brief 人声检测（VAD）结果<br>
     *        + 1: 检测到人声。<br>
     *        + 0: 未检测到人声。<br>
     *        + -1: 未开启 VAD。
     */
    /**
     * @locale en
     * @brief Voice Activity Detection (VAD) result<br>
     *        + 1: Voice activity detected.<br>
     *        + 0: No voice activity detected.<br>
     *        + -1: VAD not activated.
     */
    int vad = -1;
    
    /**
     * @locale zh
     * @brief 本地用户的人声基频，单位为赫兹。 <br>
     *        同时满足以下两个条件时，返回的值为本地用户的人声基频：<br>
     *      + 调用 enableAudioPropertiesReport{@link #IRTCVideo#enableAudioPropertiesReport}，并设置参数 enable_voice_pitch 的值为 `true`。 <br>
     *      + 本地采集的音频中包含本地用户的人声。 <br>
     *        其他情况下返回 `0`。 
     */
    /**
     * @locale en
     * @brief The vocal pitch of the local user, in Hertz. The range is [50, 1600]. <br>
     *        When the following two conditions are met at the same time, the vocal pitch of the local user will be returned:<br>
     *      + Calls enableAudioPropertiesReport{@link #IRTCVideo#enableAudioPropertiesReport}, and sets the value of enable_voice_pitch to `true`. <br>
     *      + The local user's voice is included in the locally captured audio data. <br>
     *        In other situations, `0` will be returned. 
     */    
    double voice_pitch = 0;

    /** {zh}
     * @hidden internal use
     * @brief 设备采播延时，单位为毫秒。 <br>
     *        + -1: 未开启获取采播延时功能。<br>
     *        + >0: 具体采播延时数据。<br>
     */
    /** {en}
     * @hidden internal use
     * @brief Device record and playout delay, in milliscond. <br>
     *        + -1: Acquire record and playout delay function is not enabled.
     *        + >0: specific data of record and playout delay。<br>
     */  
    int device_loop_delay = -1;
};

/**
 * @locale zh
 * @type keytype
 * @brief 远端音频属性信息
 */
/**
 * @locale en
 * @type keytype
 * @brief Remote audio properties
 */
struct RemoteAudioPropertiesInfo {
    /**
     * @locale zh
     * @type keytype
     * @brief 远端流信息，详见 RemoteStreamKey{@link #RemoteStreamKey}
     */
    /**
     * @locale en
     * @type keytype
     * @brief Remote stream information. See RemoteStreamKey{@link #RemoteStreamKey}.
     */
    RemoteStreamKey stream_key;
    /**
     * @locale zh
     * @type keytype
     * @brief 音频属性信息，详见 AudioPropertiesInfo{@link #AudioPropertiesInfo}
     */
    /**
     * @locale en
     * @type keytype
     * @brief See AudioPropertiesInfo{@link #AudioPropertiesInfo}.
     */
    AudioPropertiesInfo audio_properties_info;
};

/**
 * @locale zh
 * @type keytype
 * @brief 本地音频属性信息
 */
/**
 * @locale en
 * @type keytype
 * @brief Local audio properties
 */
struct LocalAudioPropertiesInfo {
    /**
     * @locale zh
     * @brief 流属性，主流或屏幕流。参看 StreamIndex{@link #StreamIndex}
     */
    /**
     * @locale en
     * @brief See StreamIndex{@link #StreamIndex}.
     */
    StreamIndex stream_index = StreamIndex::kStreamIndexMain;
    /**
     * @locale zh
     * @type keytype
     * @brief 音频属性信息，详见 AudioPropertiesInfo{@link #AudioPropertiesInfo}
     */
    /**
     * @locale en
     * @type keytype
     * @brief See AudioPropertiesInfo{@link #AudioPropertiesInfo}.
     */
    AudioPropertiesInfo audio_properties_info;
};

/**
 * @locale zh
 * @type keytype
 * @brief 音质档位
 */
/**
 * @locale en
 * @type keytype
 * @brief  Sound quality
 */
enum AudioProfileType {
    /**
     * @locale zh
     * @brief 默认音质<br>
     *        服务器下发或客户端已设置的 RoomProfileType{@link #RoomProfileType} 的音质配置
     */
    /**
     * @locale en
     * @brief Default sound quality<br>
     *        The sound quality configuration of RoomProfileType{@link #RoomProfileType} set by the server or client.
     */
    kAudioProfileTypeDefault = 0,
    /**
     * @locale zh
     * @brief 流畅  <br>
     *        单声道，采样率为 16 kHz，编码码率为 32 Kbps。 <br>
     *        流畅优先、低功耗、低流量消耗，适用于大部分游戏场景，如小队语音、组队语音、国战语音等。
     */
    /**
     * @locale en
     * @brief Smooth  <br>
     *        Sample rate: 16 KHz<br>
     *        Mono-channel<br>
     *        Encoding bitrate: 32 Kpbs <br>
     *        Low resource consumption, and small network packets guarantees a smooth call. It is suitable for most game scenarios, such as team-wide voice chat, group-wide voice chat, nation-wide voice chat.
     */
    kAudioProfileTypeFluent = 1,
    /**
     * @locale zh
     * @brief 单声道标准音质。  <br>
     *        采样率为 24 kHz，编码码率为 48 Kbps。 <br>
     *        适用于对音质有一定要求的场景，同时延时、功耗和流量消耗相对适中，适合教育场景和狼人杀等游戏。
     */
    /**
     * @locale en
     * @brief Mono-channel standard  <br>
     *        Sample rate: 24 KHz<br>
     *        Encoding bitrate: 48 Kpbs<br>
     *        For scenarios requiring distinct voice, you can choose this mode, which achieves balanced latency, consumption, and network packets. It is suitable for educational Apps and the online Mafia Games.
     */
    kAudioProfileTypeStandard = 2,
    /**
     * @locale zh
     * @brief 双声道音乐音质  <br>
     *        采样率为 48 kHz，编码码率为 128 kbps。 <br>
     *        超高音质，同时延时、功耗和流量消耗相对较大，适用于连麦 PK 等音乐场景。 <br>
     *        游戏场景不建议使用。
     */
    /**
     * @locale en
     * @brief Dual-channel music  <br>
     *        Sample rate: 48 KHz<br>
     *        Encoding bitrate: 128 Kpbs<br>
     *        This mode provides high-resolution audio at a cost of high latency, consumption, and large network packets. It is suitable for music Apps such as co-hosting and online talent contests. <br>
     *        Not recommended for game Apps.
     */
    kAudioProfileTypeHD = 3,
    /**
     * @locale zh
     * @brief 双声道标准音质。采样率为 48 KHz，编码码率最大值为 80 Kbps
     */
    /**
     * @locale en
     * @brief Dual-channel standard  <br>
     *        Sample rate: 48 KHz<br>
     *        Encoding bitrate: 80 Kpbs
     */
    kAudioProfileTypeStandardStereo = 4,
    /**
     * @locale zh
     * @brief 单声道音乐音质。采样率为 48 kHz，编码码率最大值为 64 Kbps
     */
    /**
     * @locale en
     * @brief Mono-channel music  <br>
     *        Sample rate: 48 KHz<br>
     *        Encoding bitrate: 64 Kpbs
     */
    kAudioProfileTypeHDMono = 5,
};

/**
 * @locale zh
 * @type keytype
 * @brief 降噪模式。降噪算法受调用 joinRoom{@link #IRTCRoom#joinRoom} 时设置的房间模式影响。
 */
/**
 * @locale en
 * @type keytype
 * @brief ANC modes.The ANC algorithm is determined by the room profile you set when calling joinRoom{@link #IRTCRoom#joinRoom}.
 */
enum AnsMode {
    /**
     * @locale zh
     * @brief 禁用音频降噪。
     */
    /**
     * @locale en
     * @brief Disable ANC.
     */
    kAnsModeDisable = 0,
    /**
     * @locale zh
     * @brief 适用于微弱降噪。
     */
    /**
     * @locale en
     * @brief Cancel subtle background noise.
     */
    kAnsModeLow = 1,
    /**
     * @locale zh
     * @brief 适用于抑制中度平稳噪音，如空调声、风扇声。
     */
    /**
     * @locale en
     * @brief Cancel medium-level, continuous noise, such as the sound of fans or air conditioners.
     */
    kAnsModeMedium = 2,
    /**
     * @locale zh
     * @brief 适用于抑制嘈杂非平稳噪音，如键盘声、敲击声、碰撞声、动物叫声。
     */
    /**
     * @locale en
     * @brief Cancel loud, impulsive, and intermittent noise, such as keyboard clicking noise, a crash/clash, a bark, and chair scraping noise.
     */
    kAnsModeHigh = 3,
    /**
     * @locale zh
     * @brief 启用音频降噪能力。具体的降噪算法由 RTC 决定。
     */
    /**
     * @locale en
     * @brief Enable automatic ANC. The ANC algorithm is dynamically determined by RTC.
     */
    kAnsModeAutomatic = 4,
};

/**
 * @locale zh
 * @type keytype
 * @brief 本地用户在房间内的位置坐标，需自行建立空间直角坐标系
 */
/**
 * @locale en
 * @type keytype
 * @brief Coordinate value of the local user's position in the rectangular coordinate system in the RTC room.
 */
struct Position {
    /**
     * @locale zh
     * @brief x 坐标
     */
    /**
     * @locale en
     * @brief X-coordinate
     */
    float x;
    /**
     * @locale zh
     * @brief y 坐标
     */
    /**
     * @locale en
     * @brief Y-coordinate
     */
    float y;
    /**
     * @locale zh
     * @brief z 坐标
     */
    /**
     * @locale en
     * @brief Z-coordinate
     */
    float z;
    /**
     * @hidden constructor/destructor
     */
    bool isEqual(const Position& pos) const {
        return (fabs(x - pos.x) < 1e-2) &&
        (fabs(y - pos.y) < 1e-2) &&
        (fabs(z - pos.z) < 1e-2);
    }
};

/**
 * @locale zh
 * @type keytype
 * @brief 方向朝向信息
 */
/**
 * @locale en
 * @type keytype
 * @brief Direction Orientation Information
 */
struct Orientation {
    /**
     * @locale zh
     * @brief x 坐标
     */
    /**
     * @locale en
     * @brief X-coordinate
     */
    float x;
    /**
     * @locale zh
     * @brief y 坐标
     */
    /**
     * @locale en
     * @brief Y-coordinate
     */
    float y;
    /**
     * @locale zh
     * @brief z 坐标
     */
    /**
     * @locale en
     * @brief Z-coordinate
     */
    float z;
    /**
     * @hidden constructor/destructor
     */
    bool isEqual(const Orientation& orientation) const {
        return x == orientation.x && y == orientation.y && z == orientation.z;
    }
};

/**
 * @locale zh
 * @type keytype
 * @brief 三维朝向信息，三个向量需要两两垂直。参看 Orientation{@link #Orientation}。
 */
/**
 * @locale en
 * @type keytype
 * @brief Three-dimensional orientation information, each pair of vectors need to be perpendicular. See Orientation{@link #Orientation}.
 */
struct HumanOrientation {
    /**
     * @locale zh
     * @brief 正前方朝向，默认值为 {1,0,0}，即正前方朝向 x 轴正方向
     */
    /**
     * @locale en
     * @brief Forward orientation, the default value is {1,0,0}, i.e., the forward orientation is in the positive direction of x-axis.
     */
    Orientation forward =  { 1, 0, 0 };
    /**
     * @locale zh
     * @brief 正右方朝向，默认值为 {0,1,0}，即右手朝向 y 轴正方向
     */
    /**
     * @locale en
     * @brief Rightward orientation, the default value is {0,1,0}, i.e., the rightward orientation is in the positive direction of y-axis.
     */
    Orientation right = { 0, 1, 0 };
    /**
     * @locale zh
     * @brief 正上方朝向，默认值为 {0,0,1}，即头顶朝向 z 轴正方向
     */
    /**
     * @locale en
     * @brief Upward orientation, the default value is {0,0,1}, i.e., the upward orientation is in the positive direction of z-axis.
     */
    Orientation up = { 0, 0, 1 };
    /**
     * @hidden constructor/destructor
     */
    bool isEqual(const HumanOrientation& human_orientation) const {
        return forward.isEqual(human_orientation.forward) && right.isEqual(human_orientation.right) && up.isEqual(human_orientation.up);
    }
};

/**
 * @locale zh
 * @type keytype
 * @brief 音频音量是否可设置
 */
/**
 * @locale en
 * @type keytype
 * @brief Accessibility to volume setting
 */
enum AudioAbilityType {
    /**
     * @locale zh
     * @brief 未知
     */
    /**
     * @locale en
     * @brief Unknown
     */
    kAudioAbilityTypeUnknown = -1,
    /**
     * @locale zh
     * @brief 音量可设置
     */
    /**
     * @locale en
     * @brief The volume setting is accessible.
     */
    kAudioAbilityTypeAble = 0,
    /**
     * @locale zh
     * @brief 音量不可设置
     */
    /**
     * @locale en
     * @brief The volume setting is inaccessible.
     */
    kAudioAbilityTypeUnable = 1,
};
/**
 * @locale zh
 * @type keytype
 * @brief 远端音频流精准对齐模式
 */
/**
 * @locale en
 * @type keytype
 * @brief The alignment mode of remote audio streams
 */
enum AudioAlignmentMode {
    /**
     * @locale zh
     * @brief 不对齐
     */
    /**
     * @locale en
     * @brief Disabled
     */
    kAudioAlignmentModeOff,
    /**
     * @locale zh
     * @brief 远端音频流都对齐伴奏进度同步播放
     */
    /**
     * @locale en
     * @brief All subscribed audio streams are aligned based on the process of the background music.
     */
    kAudioAlignmentModeAudioMixing,
};

/**
 * @locale zh
 * @type keytype
 * @brief 音频设备信息
 */
/**
 * @locale en
 * @type keytype
 * @brief Audio device information
 */
struct AudioDeviceInfo {
    /**
     * @locale zh
     * @brief 设备 ID
     */
    /**
     * @locale en
     * @brief Device ID
     */
    char device_id[MAX_DEVICE_ID_LENGTH];
    /**
     * @locale zh
     * @brief 设备全称，包含设备类型与设备名称。例如 "扬声器 (XYZ Audio Adapter)"
     */
    /**
     * @locale en
     * @brief Friendly name of the audio adapter to which the endpoint device is attached. For example, "Speakers (XYZ Audio Adapter)"
     */
    char device_name[MAX_DEVICE_ID_LENGTH];
    /**
     * @locale zh
     * @brief 设备名称，不含设备类型。例如 "XYZ Audio Adapter"
     */
    /**
     * @locale en
     * @brief Friendly name of the endpoint device. For example, "XYZ Audio Adapter"
     */
    char device_short_name[MAX_DEVICE_ID_LENGTH];
    /**
     * @locale zh
     * @brief 设备所连接的声卡 ID，便于选择使用同一声卡的扬声器和麦克风。
     */
    /**
     * @locale en
     * @brief ID of the sound card connected to the audio device. With this variable, you can choose the speaker and microphone connected to the same sound card with ease.
     */
    char device_container_id[MAX_DEVICE_ID_LENGTH];
    /**
     * @locale zh
     * @brief 设备的厂商 ID
     */
    /**
     * @locale en
     * @brief ID of the device vendor
     */
    int64_t device_vid;
    /**
     * @locale zh
     * @brief 设备的产品编码
     */
    /**
     * @locale en
     * @brief Product number of the device
     */
    int64_t device_pid;
    /**
     * @locale zh
     * @brief 设备的传输方式
     */
    /**
     * @locale en
     * @brief Connection type of the device
     */
    DeviceTransportType transport_type;
    /**
     * @locale zh
     * @brief 是否支持设置音量
     */
    /**
     * @locale en
     * @brief Accessibility to the volume setting
     */
    AudioAbilityType volume_settable;
    /**
     * @locale zh
     * @brief 是否系统默认设备
     */
    /**
     * @locale en
     * @brief Whether the device is the default device
     */
    bool is_system_default;
    /**
     * @hidden constructor/destructor
     */
    AudioDeviceInfo() {
        memset(device_id, 0, MAX_DEVICE_ID_LENGTH);
        memset(device_name, 0, MAX_DEVICE_ID_LENGTH);
        memset(device_short_name, 0, MAX_DEVICE_ID_LENGTH);
        memset(device_container_id, 0, MAX_DEVICE_ID_LENGTH);
        this->device_vid = 0;
        this->device_pid = 0;
        this->transport_type = DeviceTransportType::kDeviceTransportTypeUnknown;
        this->volume_settable = AudioAbilityType::kAudioAbilityTypeUnknown;
        this->is_system_default = false;
    }
    /**
     * @hidden constructor/destructor
     */
    AudioDeviceInfo& operator=(const AudioDeviceInfo& src) {
        if (this != &src) {
            strncpy(device_id, src.device_id, MAX_DEVICE_ID_LENGTH - 1);
            strncpy(device_name, src.device_name, MAX_DEVICE_ID_LENGTH - 1);
            strncpy(device_short_name, src.device_short_name, MAX_DEVICE_ID_LENGTH - 1);
            strncpy(device_container_id, src.device_container_id, MAX_DEVICE_ID_LENGTH - 1);
            device_id[MAX_DEVICE_ID_LENGTH - 1] = '\0';
            device_name[MAX_DEVICE_ID_LENGTH - 1] = '\0';
            device_short_name[MAX_DEVICE_ID_LENGTH - 1] = '\0';
            device_container_id[MAX_DEVICE_ID_LENGTH - 1] = '\0';
            device_vid = src.device_vid;
            device_pid = src.device_pid;
            transport_type = src.transport_type;
            volume_settable = src.volume_settable;
            is_system_default = src.is_system_default;
        }

        return *this;
    }
};
/**
 * @locale zh
 * @type keytype
 * @brief 标准音高数据
 */
/**
 * @locale en
 * @type keytype
 * @brief Standard pitch data
 */
struct StandardPitchInfo {
    /**
     * @locale zh
     * @brief 开始时间，单位 ms。
     */
    /**
     * @locale en
     * @brief Starting time, unit: ms.
     */
    int start_time;
    /**
     * @locale zh
     * @brief 持续时间，单位 ms。
     */
    /**
     * @locale en
     * @brief Duration, unit: ms.
     */
    int duration;
    /**
     * @locale zh
     * @brief 音高。
     */
    /**
     * @locale en
     * @brief pitch.
     */
    int pitch;
};
/**
 * @locale zh
 * @type keytype
 * @brief K 歌打分维度。
 */
/**
 * @locale en
 * @type keytype
 * @brief Karaoke scoring mode.
 */
enum MulDimSingScoringMode {
    /**
     * @locale zh
     * @brief 按照音高进行评分。
     */
    /**
     * @locale en
     * @brief The score is provided based on the pitch.
     */
    kMulDimSingScoringModeNote = 0
};
/**
 * @locale zh
 * @type keytype
 * @brief K 歌评分配置。
 */
/**
 * @locale en
 * @type keytype
 * @brief Karaoke scoring configuration.
 */
struct SingScoringConfig {
    /**
     * @locale zh
     * @brief 音频采样率。仅支持 44100 Hz、48000 Hz。
     */
    /**
     * @locale en
     * @brief Sampling rate. Only 44,100 Hz and 48,000 Hz are supported.
     */
    AudioSampleRate sample_rate;
    /**
     * @locale zh
     * @brief 打分维度，详见 MulDimSingScoringMode{@link #MulDimSingScoringMode}。
     */
    /**
     * @locale en
     * @brief Scoring mode, see MulDimSingScoringMode{@link #MulDimSingScoringMode}.
     */
    MulDimSingScoringMode mode;
    /**
     * @locale zh
     * @brief 歌词文件路径。打分功能仅支持 KRC 歌词文件。
     */
    /**
     * @locale en
     * @brief The file path of the lyrics. The scoring feature only supports KRC lyrics file.
     */
    const char* lyrics_filepath;
    /**
     * @locale zh
     * @brief 歌曲 midi 文件路径。
     */
    /**
     * @locale en
     * @brief The path of the midi file.
     */
    const char* midi_filepath;
};
/**
 * @locale zh
 * @type keytype
 * @brief 实时评分信息。
 */
/**
 * @locale en
 * @type keytype
 * @brief Real-time scoring data.
 */
struct SingScoringRealtimeInfo {
    /**
     * @locale zh
     * @brief 当前播放进度。
     */
    /**
     * @locale en
     * @brief Current playback position.
     */
    int current_position;
    /**
     * @locale zh
     * @brief 演唱者的音高。
     */
    /**
     * @locale en
     * @brief The user's pitch.
     */
    int user_pitch;
    /**
     * @locale zh
     * @brief 标准音高。
     */
    /**
     * @locale en
     * @brief Standard pitch.
     */
    int standard_pitch;
    /**
     * @locale zh
     * @brief 歌词分句索引。
     */
    /**
     * @locale en
     * @brief Lyric index.
     */
    int sentence_index;
    /**
     * @locale zh
     * @brief 上一句歌词的评分。
     */
    /**
     * @locale en
     * @brief The score for the previous lyric.
     */
    int sentence_score;
    /**
     * @locale zh
     * @brief 当前演唱的累计分数。
     */
    /**
     * @locale en
     * @brief The total score for the user's current performance.
     */
    int total_score;
    /**
     * @locale zh
     * @brief 当前演唱的平均分数。
     */
    /**
     * @locale en
     * @brief The average score for the user's current performance.
     */
    int average_score;
};
/**
 * @locale zh
 * @type keytype
 * @brief 音频文件录制内容来源。
 */
/**
 * @locale en
 * @type keytype
 * @brief Audio file recording source type.
 */
enum AudioFrameSource {
    /**
     * @locale zh
     * @brief 本地麦克风采集的音频数据。
     */
    /**
     * @locale en
     * @brief The audio captured by the local microphone.
     */
    kAudioFrameSourceMic = 0,
    /**
     * @locale zh
     * @brief 远端所有用户混音后的数据
     */
    /**
     * @locale en
     * @brief The audio got by mixing all remote user's audio.
     */
    kAudioFrameSourcePlayback = 1,
    /**
     * @locale zh
     * @brief 本地麦克风和所有远端用户音频流的混音后的数据
     */
    /**
     * @locale en
     * @brief The audio got by mixing the local captured audio and all remote user's audio.
     */
    kAudioFrameSourceMixed = 2,
};
/**
 * @locale zh
 * @type keytype
 * @brief 音频质量。
 */
/**
 * @locale en
 * @type keytype
 * @brief Audio quality.
 */
enum AudioQuality {
    /**
     * @locale zh
     * @brief 低音质
     */
    /**
     * @locale en
     * @brief low quality
     */
    kAudioQualityLow = 0,
    /**
     * @locale zh
     * @brief 中音质
     */
    /**
     * @locale en
     * @brief medium quality
     */
    kAudioQualityMedium = 1,
    /**
     * @locale zh
     * @brief 高音质
     */
    /**
     * @locale en
     * @brief high quality
     */
    kAudioQualityHigh = 2,
    /**
     * @locale zh
     * @brief 超高音质
     */
    /**
     * @locale en
     * @brief ultra high quality
     */
    kAudioQualityUltraHigh = 3,
};
/**
 * @locale zh
 * @type keytype
 * @brief 录音配置
 */
/**
 * @locale en
 * @type keytype
 * @brief Audio recording config
 */
struct AudioRecordingConfig {
    /**
     * @hidden Constructor/Destructor
     */
    AudioRecordingConfig() {
        absolute_file_name = nullptr;
        frame_source = kAudioFrameSourceMixed;
        sample_rate = kAudioSampleRateAuto;
        channel = kAudioChannelAuto;
        quality = kAudioQualityMedium;
    }
    /**
     * @locale zh
     * @brief 录制文件路径。一个有读写权限的绝对路径，包含文件名和文件后缀。<br>
     * 录制文件的格式仅支持 .aac 和 .wav。
     */
    /**
     * @locale en
     * @brief Absolute path of the recorded file, file name included. The App must have the write and read permission of the path.<br>
     * The files format is restricted to .aac and .wav.
     */
    const char* absolute_file_name;
    /**
     * @locale zh
     * @brief 录音内容来源，参看 AudioFrameSource{@link #AudioFrameSource}。<br>
     * 默认为 kAudioFrameSourceMixed = 2。
     */
    /**
     * @locale en
     * @brief The source of the recording. See AudioFrameSource{@link #AudioFrameSource}.<br>
     * It is kAudioFrameSourceMixed = 2, by default.
     */
    AudioFrameSource frame_source;
    /**
     * @locale zh
     * @brief 录音采样率。参看 AudioSampleRate{@link #AudioSampleRate}。
     */
    /**
     * @locale en
     * @brief See AudioSampleRate{@link #AudioSampleRate}.
     */
    AudioSampleRate sample_rate;
    /**
     * @locale zh
     * @brief 录音音频声道。参看 AudioChannel{@link #AudioChannel}。<br>
     *        如果录制时设置的的音频声道数与采集时的音频声道数不同：<br>
     *        + 如果采集的声道数为 1，录制的声道数为 2，那么，录制的音频为经过单声道数据拷贝后的双声道数据，而不是立体声。<br>
     *        + 如果采集的声道数为 2，录制的声道数为 1，那么，录制的音频为经过双声道数据混合后的单声道数据。
     */
    /**
     * @locale en
     * @brief Number of audio channels. See AudioChannel{@link #AudioChannel}.<br>
     *        If number of audio channels of recording is different than that of audio capture, the behavior is: <br>
     *        + If the number of capture is 1, and the number of recording is 2, the recorded audio is two-channel data after copying mono-channel data. <br>
     *        + If the number of capture is 2, and the number of recording is 1, the recorded audio is recorded by mixing the audio of the two channels.
     */
    AudioChannel channel;
    /**
     * @locale zh
     * @brief 录音音质。仅在录制文件格式为 .aac 时可以设置。参看 AudioQuality{@link #AudioQuality}。<br>
     * 采样率为 32kHz 时，不同音质录制文件（时长为 10min）的大小分别是： <br>
     *        + 低音质：1.2MB；<br>
     *        + 【默认】中音质：2MB；<br>
     *        + 高音质：3.75MB；<br>
     *        + 超高音质：7.5MB。
     */
    /**
     * @locale en
     * @brief Recording quality. Only valid for .aac file. See AudioQuality{@link #AudioQuality}.<br>
     * When the sample rate is 32kHz, the file (10min) size for different qualities are: <br>
     *        + low: 1.2MB; <br>
     *        + [By Default] medium: 2MB; <br>
     *        + high: 3.75MB; <br>
     *        + ultra high: 7.5MB.
     */
    AudioQuality quality;
};
/**
 * @locale zh
 * @type keytype
 * @brief 录音配置
 */
/**
 * @locale en
 * @type keytype
 * @brief Audio recording config
 */
enum AudioRecordingState {
    /**
     * @locale zh
     * @brief 录制异常
     */
    /**
     * @locale en
     * @brief Recording exception
     */
    kAudioRecordingStateError = 0,
    /**
     * @locale zh
     * @brief 录制进行中
     */
    /**
     * @locale en
     * @brief Recording in progress
     */
    kAudioRecordingStateProcessing = 1,
    /**
     * @locale zh
     * @brief 已结束录制，并且录制文件保存成功。
     */
    /**
     * @locale en
     * @brief The recording task ends, and the file is saved.
     */    
    kAudioRecordingStateSuccess = 2,
};
/**
 * @locale zh
 * @type errorcode
 * @brief 音频文件录制的错误码
 */
/**
 * @locale en
 * @type errorcode
 * @brief Error code for audio recording.
 */
enum AudioRecordingErrorCode {
    /**
     * @locale zh
     * @brief 录制正常
     */
    /**
     * @locale en
     * @brief OK
     */
    kAudioRecordingErrorCodeOk = 0,
    /**
     * @locale zh
     * @brief 没有文件写权限
     */
    /**
     * @locale en
     * @brief No file write permissions.
     */
    kAudioRecordingErrorCodeNoPermission = -1,
    /**
     * @locale zh
     * @brief 没有进入房间
     */
    /**
     * @locale en
     * @brief Not in the room.
     */
    kAudioRecordingErrorCodeNotInRoom = -2,
    /**
     * @locale zh
     * @brief 录制已经开始
     */
    /**
     * @locale en
     * @brief Started.
     */
    kAudioRecordingErrorCodeAlreadyStarted = -3,
    /**
     * @locale zh
     * @brief 录制还未开始
     */
    /**
     * @locale en
     * @brief Not started.
     */
    kAudioRecordingErrorCodeNotStarted = -4,
    /**
     * @locale zh
     * @brief 录制失败。文件格式不支持。
     */
    /**
     * @locale en
     * @brief Failure. Invalid file format.
     */
    kAudioRecordingErrorCodeNotSupport = -5,
    /**
     * @locale zh
     * @brief 其他异常
     */
    /**
     * @locale en
     * @brief Other error.
     */
    kAudioRecordingErrorCodeOther = -6,
};
/**
 * @locale zh
 * @hidden(macOS, Windows, Linux)
 * @type keytype
 * @brief 蜂窝网络辅助增强应用的媒体模式
 */
/**
 * @locale en
 * @hidden(macOS, Windows, Linux)
 * @type keytype
 * @brief Media type for cellular assisted Enhancement
 */
struct AudioEnhancementConfig {
    /**
     * @locale zh
     * @brief 对信令消息，是否启用蜂窝网络辅助增强。默认不启用。
     */
    /**
     * @locale en
     * @brief Apply to signaling or not. Not by default.
     */
    bool enhance_signaling = false;
    /**
     * @locale zh
     * @brief 对音频，是否启用蜂窝网络辅助增强。默认不启用。
     */
    /**
     * @locale en
     * @brief Apply to audio stream or not. Not by default.
     */
    bool enhance_audio = false;
};

}  // namespace bytertc
