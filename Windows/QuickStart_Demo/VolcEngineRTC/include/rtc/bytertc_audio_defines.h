/*
 * Copyright (c) 2022 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC Audio Defines
 */

#pragma once

#include "bytertc_common_defines.h"
#include <string.h>
// use fft size 512 to calculate spectrum, so spectrum size is 512 / 2 + 1 = 257
#define SPECTRUM_SIZE 257

namespace bytertc {

/** 
 * @type keytype
 * @brief 音频采样率，单位为 Hz。
 */
enum AudioSampleRate {
    /** 
     * @brief 默认设置。
     */
    kAudioSampleRateAuto = -1,
    /** 
     * @brief 8000 Hz
     */
    kAudioSampleRate8000 = 8000,
    /** 
     * @brief 16000 Hz
     */
    kAudioSampleRate16000 = 16000,
    /** 
     * @brief 32000 Hz
     */
    kAudioSampleRate32000 = 32000,
    /** 
     * @brief 44100 Hz
     */
    kAudioSampleRate44100 = 44100,
    /** 
     * @brief 48000 Hz
     */
    kAudioSampleRate48000 = 48000
};

/** 
 * @type keytype
 * @brief 音频声道。
 */
enum AudioChannel {
    /** 
     * @brief 默认设置。
     */
    kAudioChannelAuto = -1,
    /** 
     * @brief 单声道
     */
    kAudioChannelMono = 1,
    /** 
     * @brief 双声道
     */
    kAudioChannelStereo = 2
};

/** 
 * @type keytype
 * @brief 音频格式
 */
struct AudioFormat {
    /** 
     * @brief 音频采样率，详见 AudioSampleRate{@link #AudioSampleRate}
     */
    AudioSampleRate sample_rate;
    /** 
     * @brief 音频声道，详见 AudioChannel{@link #AudioChannel}
     */
    AudioChannel channel;
};
/** 
 * @type keytype
 * @brief 返回给音频处理器的音频类型。
 */
enum AudioProcessorMethod{
    /** 
     * @brief 本地采集的音频。
     */
    kAudioFrameProcessorRecord = 0,
    /** 
     * @brief 远端音频流的混音音频。
     */
    kAudioFrameProcessorPlayback = 1,
    /** 
     * @brief 各个远端音频流。
     */
    kAudioFrameProcessorRemoteUser = 2,
    /** 
     * @hidden(Windows,Linux)
     * @brief 耳返音频。
     */
    kAudioFrameProcessorEarMonitor = 3,
    /** 
     * @hidden(Linux)
     * @brief 屏幕共享音频。
     */
    kAudioFrameProcessorScreen = 4,
};
/** 
 * @type keytype
 * @brief 音频设备类型
 */
enum RTCAudioDeviceType {
    /** 
     * @brief 未知设备类型
     */
    kRTCAudioDeviceTypeUnknown = -1,
    /** 
     * @brief 音频渲染设备
     */
    kRTCAudioDeviceTypeRenderDevice = 0,
    /** 
     * @brief 音频采集设备
     */
    kRTCAudioDeviceTypeCaptureDevice = 1,
    /** 
     * @brief 屏幕流音频设备
     */
    kRTCAudioDeviceTypeScreenCaptureDevice = 2,
};

/** 
 * @type keytype
 * @brief 音频播放设备
 */
enum AudioRoute {
    /** 
     * @brief 未知设备
     */
    kAudioRouteUnknown = -1,
    /** 
     * @brief 有线耳机
     */
    kAudioRouteHeadset = 1,
    /** 
     * @brief 听筒
     */
    kAudioRouteEarpiece = 2,
    /** 
     * @brief 扬声器
     */
    kAudioRouteSpeakerphone = 3,
    /** 
     * @brief 蓝牙耳机
     */
    kAudioRouteHeadsetBluetooth = 4,
    /** 
     * @brief USB设备
     */
    kAudioRouteHeadsetUSB = 5
};

/** 
 * @type keytype
 * @brief 音频播放设备
 */
enum AudioPlaybackDevice {
    /** 
     * @brief 有线耳机
     */
    kAudioPlaybackDeviceHeadset = 1,
    /** 
     * @brief 听筒
     */
    kAudioPlaybackDeviceEarpiece = 2,
    /** 
     * @brief 扬声器
     */
    kAudioPlaybackDeviceSpeakerphone = 3,
    /** 
     * @brief 蓝牙耳机
     */
    kAudioPlaybackDeviceHeadsetBluetooth = 4,
    /** 
     * @brief USB设备
     */
    kAudioPlaybackDeviceHeadsetUSB = 5
};

/** 
 * @hidden(macOS,Windows)
 * @type keytype
 * @brief 音频场景类型。<br>
 *        选择音频场景后，RTC 会自动根据客户端音频采集播放设备和采集播放状态，适用通话音量/媒体音量。<br>
 *        如果预设的音频场景类型无法满足你的业务需要，请联系技术支持同学进行定制。
 */
enum AudioScenarioType {
    /** 
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
    kAudioScenarioTypeMusic = 0,
    /** 
     * @brief 高质量通话场景。<br>
     *        此场景适用于对音乐表现力有要求，但又希望能够使用蓝牙耳机上自带的麦克风进行音频采集的场景。
     *        此场景下，更倾向于使用媒体音量。由此，可能引起开关麦时音量突变。如不希望有此突变，请使用 `kAudioScenarioTypeHighQualityChat`。
     *        此场景可以兼顾外放/使用蓝牙耳机时的音频体验；并尽可能避免使用蓝牙耳机时音量类型切换导致的听感突变。<br>
     *        音频采集播放设备和采集播放状态，到音量类型的映射如下：<br>
     *        <table>
     *           <tr><th></th><th>不采集音频</th><th>采集音频</th><th>备注</th></tr>
     *           <tr><td>设备自带麦克风和扬声器/听筒</td><td>媒体音量</td><td>通话音量</td><td>/</td></tr>
     *           <tr><td>有线耳机/ USB 耳机/ 外置声卡</td><td>媒体音量</td><td>媒体音量</td><td>/</td></tr>
     *           <tr><td>蓝牙耳机</td><td>通话音量</td><td>通话音量</td><td>能够使用蓝牙耳机上自带的麦克风进行音频采集。</td></tr>
     *        </table>
     */
    kAudioScenarioTypeHighQualityCommunication = 1,
    /** 
     * @brief 纯通话音量场景。<br>
     *        此场景下，无论客户端音频采集播放设备和采集播放状态，全程使用通话音量。
     *        适用于需要频繁上下麦的通话或会议场景。<br>
     *        此场景可以保持统一的音频模式，不会有音量突变的听感；
     *        最大程度上的消除回声，使通话清晰度达到最优；
     *        使用蓝牙耳机时，能够使用蓝牙耳机上自带的麦克风进行音频采集。<br>
     *        但是，使用媒体音量进行播放的其他音频的音量会被压低，且音质会变差。
     */
    kAudioScenarioTypeCommunication = 2,
    /** 
     * @brief 纯媒体场景。一般不建议使用。
     *        此场景下，无论客户端音频采集播放设备和采集播放状态，全程使用媒体音量。
     *        外放通话时，可能出现回声和啸叫，请联系技术支持人员。
     */
    kAudioScenarioTypeMedia = 3,
    /** 
     * @brief 游戏媒体场景。仅适合游戏场景。
     *        此场景下，蓝牙耳机时使用通话音量，其它设备使用媒体音量。
     *        若外放通话且无游戏音效消除优化时音质不理想，请联系技术支持人员。
     */
    kAudioScenarioTypeGameStreaming = 4,
    /** 
     * @brief 高质量畅聊场景。  <br>
     *        此场景和 `kAudioScenarioTypeHighQualityCommunication` 高度类似，唯一的差异在于：此场景下，在使用设备自带的麦克风和扬声器/听筒进行通话时，开关麦始终采用通话音量，不会引起音量类型突变。 <br>
     *        音频采集播放设备和采集播放状态，到音量类型的映射如下：<br>
     *        <table>
     *           <tr><th></th><th>不采集音频</th><th>采集音频</th><th>备注</th></tr>
     *           <tr><td>设备自带麦克风和扬声器/听筒</td><td>通话音量</td><td>通话音量</td><td>/</td></tr>
     *           <tr><td>有线耳机/USB 耳机</td><td>媒体音量</td><td>媒体音量</td><td>/</td></tr>
     *           <tr><td>蓝牙耳机</td><td>通话音量</td><td>通话音量</td><td>能够使用蓝牙耳机上自带的麦克风进行音频采集。</td></tr>
     *        </table>
     */
    kAudioScenarioTypeHighQualityChat = 5,
};

/** 
 * @hidden(Linux)
 * @type keytype
 * @brief Private method. 变声特效类型
 */
enum VoiceChangerType {
    /** 
     * @brief 原声，不含特效
     */
    kVoiceChangerTypeOriginal = 0,
    /** 
     * @brief 巨人
     */
    kVoiceChangerTypeGiant = 1,
    /** 
     * @brief 花栗鼠
     */
    kVoiceChangerTypeChipmunk = 2,
    /** 
     * @brief 小黄人
     */
    kVoiceChangerTypeMinionst = 3,
    /** 
     * @brief 颤音
     */
    kVoiceChangerTypeVibrato = 4,
    /** 
     * @brief 机器人
     */
    kVoiceChangerTypeRobot = 5,
};

/** 
 * @hidden(Linux)
 * @type keytype
 * @brief Private method. 混响特效类型
 */
enum VoiceReverbType {
    /** 
     * @brief 原声，不含特效
     */
    kVoiceReverbTypeOriginal = 0,
    /** 
     * @brief 回声
     */
    kVoiceReverbTypeEcho = 1,
    /** 
     * @brief 演唱会
     */
    kVoiceReverbTypeConcert = 2,
    /** 
     * @brief 空灵
     */
    kVoiceReverbTypeEthereal = 3,
    /**
     * @brief KTV
     */
    kVoiceReverbTypeKTV = 4,
    /** 
     * @brief 录音棚
     */
    kVoiceReverbTypeStudio = 5,
};

/** 
 * @type keytype
 * @brief 音频流来源的用户 ID 及对应的音量。
 */
struct AudioVolumeInfo {
    /** 
     * @brief 线性音量，取值范围是：[0,255]，与原始音量呈线性关系，数值越大，音量越大。
     * 无声为25以下（绝对无声为0，25以下基本已经无声音了，可以视为无声），低音量为25~76，中音量为76~204，高音量为204以上
     */
    int linear_volume;
    /** 
     * @brief 非线性音量，取值范围是：[-127，0]，单位dB。此音量范围是将原始音量进行对数转化，在中低音量时分辨更为灵敏，适用于作为Active Speaker（房间内最活跃用户）的识别。
     * 高音量为0~-20dB，中音量为-20~-40dB，低音量为-40~-60dB，若低于-60dB，则为无声。
     */
    int nonlinear_volume;
    /** 
     * @brief 音频流来源的用户 ID
     */
    const char* uid;
};

/** 
 * @type keytype
 * @brief 音频混音文件播放状态。
 */
enum AudioMixingState {
    /** 
     * @brief 混音已加载
     */
    kAudioMixingStatePreloaded = 0,
    /** 
     * @brief 混音正在播放
     */
    kAudioMixingStatePlaying,
    /** 
     * @brief 混音暂停
     */
    kAudioMixingStatePaused,
    /** 
     * @brief 混音停止
     */
    kAudioMixingStateStopped,
    /** 
     * @brief 混音播放失败
     */
    kAudioMixingStateFailed,
    /** 
     * @brief 混音播放结束
     */
    kAudioMixingStateFinished,
    /** 
     * @brief 准备PCM混音
     */
    kAudioMixingStatePCMEnabled,
    /** 
     * @brief PCM混音播放结束
     */
    kAudioMixingStatePCMDisabled,
};
/** 
 * @type keytype
 * @brief 混音错误码。
 */
enum AudioMixingError {
    /** 
     * @brief 正常
     */
    kAudioMixingErrorOk = 0,
    /** 
     * @brief 预加载失败。找不到混音文件或者文件长度超出 20s
     */
    kAudioMixingErrorPreloadFailed,
    /** 
     * @brief 混音开启失败。找不到混音文件或者混音文件打开失败
     */
    kAudioMixingErrorStartFailed,
    /** 
     * @brief 混音 ID 异常
     */
    kAudioMixingErrorIdNotFound,
    /** 
     * @brief 设置混音文件的播放位置出错
     */
    kAudioMixingErrorSetPositionFailed,
    /** 
     * @brief 音量参数不合法，仅支持设置的音量值为[0, 400]
     */
    kAudioMixingErrorInValidVolume,
    /** 
     * @brief 播放的文件与预加载的文件不一致。请先使用 unloadAudioMixing{@link #IAudioMixingManager#unloadAudioMixing} 卸载此前的文件。
     */
    kAudioMixingErrorLoadConflict,
    /** 
     * @brief 不支持此混音类型。
     */
    kAudioMixingErrorIdTypeNotMatch,
    /** 
     * @brief 设置混音文件的音调不合法
     */
    kAudioMixingErrorInValidPitch,
    /** 
     * @brief 设置混音文件的音轨不合法
     */
    kAudioMixingErrorInValidAudioTrack,
    /** 
     * @brief 混音文件正在启动中
     */
    kAudioMixingErrorIsStarting,
    /** 
     * @brief 设置混音文件的播放速度不合法
     */
    kAudioMixingErrorInValidPlaybackSpeed,
    /** 
     * @hidden
     * @deprecated since 325.1
     * @brief 混音错误码，失败，已废弃
     */
    kAudioMixingErrorCanNotOpen = 701,
};

/** 
 * @type keytype
 * @hidden(Windows)
 * @brief 是否开启耳返功能
 */
enum EarMonitorMode {
    /** 
     * @brief 不开启
     */
    kEarMonitorModeOff = 0,
    /** 
     * @brief 开启
     */
    kEarMonitorModeOn = 1,
};

/** 
 * @type keytype
 * @brief 音频输入源类型
 */
enum AudioSourceType {
    /** 
     *  自定义采集音频源
     */
    kAudioSourceTypeExternal = 0,
    /** 
     *  RTC SDK 内部采集音频源
     */
    kAudioSourceTypeInternal,
};

/** 
 * @type keytype
 * @brief 音频输出类型
 */
enum AudioRenderType {
    /** 
     *  自定义渲染
     */
    kAudioRenderTypeExternal = 0,
    /** 
     *  RTC SDK 内部渲染
     */
    kAudioRenderTypeInternal,
};

/** 
 * @type keytype
 * @brief 语音识别服务鉴权方式，详情请咨询语音识别服务相关人员
 */
enum ASRAuthorizationType {
    /** 
     * @brief Token 鉴权
     */
    kASRAuthorizationTypeToken = 0,
    /** 
     * @brief Signature 鉴权
     */
    kASRAuthorizationTypeSignature = 1,
};

/** 
 * @type keytype
 * @brief 使用自动语音识别服务所需校验信息
 */
struct RTCASRConfig {
    /** 
     * @brief 应用 ID
     */
    const char* app_id;
    /** 
     * @brief 用户 ID
     */
    const char* user_id;
    /** 
     * @brief 鉴权方式，参看 ASRAuthorizationType{@link #ASRAuthorizationType}
     */
    ASRAuthorizationType authorization_type;
    /** 
     * @brief 访问令牌
     */
    const char* access_token;
    /** 
     * @brief 私钥。Signature 鉴权模式下不能为空，token 鉴权模式下为空。参看[关于鉴权](https://www.volcengine.com/docs/6561/107789)
     */
    const char* secret_key;
    /** 
     * @brief 场景信息，参看[业务集群](https://www.volcengine.com/docs/6561/80818#_3-2-2-%E5%8F%91%E9%80%81-full-client-request)
     */
    const char* cluster;
};

/** 
 * @type keytype
 * @brief 语音识别服务错误码。  <br>
 *        除网络原因导致的错误，语音识别服务内部会自行重试之外，其他错误都会停止服务，此时建议再次调用 `startASR` 重启语音识别功能。
 */
enum RTCASRErrorCode {
    /** 
     * @brief 网络连接中断，服务不可用，内部会进行重连
     */
    kRTCASRErrorNetworkInterrupted = -1,
    /** 
     * @brief 重复调用 `startASR`。开启语音识别服务后，你需要先调用 `stopASR` 停止语音识别服务，才能二次调用 `startASR` 再次开启服务。
     */
    kRTCASRErrorAlreadyStarted = -2,
    /** 
     * @brief 语音识别服务所需 token 为空
     */
    kRTCASRErrorTokenEmpty = -3,
    /** 
     * @brief Signature 鉴权模式下 secret_key 为空
     */
    kRTCErrorSignatureKeyEmpty = -4,
    /** 
     * @brief 用户 ID 为空
     */
    kRTCASRErrorUserIdNull = -5,
    /** 
     * @brief 应用 ID 为空
     */
    kRTCASRErrorAPPIDNull = -6,
    /** 
     * @brief 语音识别服务 cluster 为空
     */
    kRTCASRErrorClusterNull = -7,
    /** 
     * @brief 语音识别服务连接失败，该版本没有语音识别功能，请联系 RTC 技术支持。
     */
    kRTCASRErrorOperationDenied = -8
};

/** 
 * @type keytype
 * @brief 混音播放类型
 */
enum AudioMixingType {
    /** 
     * @brief 仅本地播放
     */
    kAudioMixingTypePlayout,
    /** 
     * @brief 仅远端播放
     */
    kAudioMixingTypePublish,
    /** 
     * @brief 本地和远端同时播放
     */
    kAudioMixingTypePlayoutAndPublish
};

/** 
 * @type keytype
 * @brief 混音配置
 */
struct AudioMixingConfig {
    /** 
     * @brief 混音播放类型，详见 AudioMixingType{@link #AudioMixingType}
     */
    AudioMixingType type;
    /** 
     * @brief 混音播放次数，
     *       + play_count <= 0: 无限循环  <br>
     *       + play_count == 1: 播放一次（默认）  <br>
     *       + play_count > 1: 播放 play_count 次
     */
    int play_count;
     /** 
      * @brief 混音时音频文件播放进度条位置，参数为整数，单位为毫秒
      */
     int position;
     /** 
      * @brief 设置音频文件播放进度回调的时间间隔，参数为大于 0 的 10 的倍数，单位为毫秒，设置后 SDK 将按照设置的值触发 `onAudioMixingPlayingProgress` 回调，默认不回调。  <br>
      *        + 当传入的值不能被 10 整除时，则默认向上取整 10，如设为 52ms 时会默认调整为 60ms。  <br>
      *        + 当传入的值小于等于 0 时，不会触发进度回调。  <br>
      */
     int64_t callback_on_progress_interval = 0;
};

/** 
 * @type keytype
 * @brief 混音播放声道类型
 */
enum AudioMixingDualMonoMode{
    /** 
     * @brief 和音频文件一致
     */
    kAudioMixingDualMonoModeAuto,
    /** 
     * @brief 只能听到音频文件中左声道的音频
     */
    kAudioMixingDualMonoModeL,
    /** 
     * @brief 只能听到音频文件中右声道的音频
     */
    kAudioMixingDualMonoModeR,
    /** 
     * @brief 能同时听到音频文件中左右声道的音频
     */
    kAudioMixingDualMonoModeMix
};

/** 
 * @type keytype
 * @brief 音量回调模式。
 */
enum AudioReportMode {
    /** 
     * @brief 默认始终开启音量回调。
     */
    kAudioReportModeNormal,
    /** 
     * @brief 可见用户进房并停止推流后，关闭音量回调。
     */
    kAudioReportModeDisconnect,
    /** 
     * @brief 可见用户进房并停止推流后，开启音量回调，回调值重置为0。
     */
    kAudioReportModeReset,
};

/** 
 * @type keytype
 * @brief 音频信息提示中是否包含本地混音音频数据。
 */
enum AudioPropertiesMode {
    /** 
     * @brief 音频信息提示中，仅包含本地麦克风采集的音频数据和本地屏幕音频采集数据。
     */
    kAudioPropertiesModeMicrophone,
    /** 
     * @brief 音频信息提示中，除本地麦克风采集的音频数据和本地屏幕音频采集数据外，还包含本地混音的音频数据。
     */
    kAudioPropertiesModeAudioMixing
};

/** 
 * @type keytype
 * @brief 音频属性信息提示的相关配置。
 */
struct AudioPropertiesConfig {
    /** 
     * @brief 信息提示间隔，单位：ms <br>
     *       + `<= 0`: 关闭信息提示  <br>
     *       + `(0,100]`: 开启信息提示，不合法的 interval 值，SDK 自动设置为 100ms  <br>
     *       + `> 100`: 开启信息提示，并将信息提示间隔设置为此值  <br>
     */
    int interval;

    /** 
     * @brief 是否开启音频频谱检测。
     */
    bool enable_spectrum = false;

    /** 
     * @brief 是否开启人声检测 (VAD)。
     */
    bool enable_vad = false;

    /** 
     * @brief 音量回调配置模式。详见 AudioReportMode{@link #AudioReportMode}。
     */
    AudioReportMode local_main_report_mode = kAudioReportModeNormal;    
        
    /** 
     * @brief 音频信息提示中是否包含本地混音音频数据。参看 AudioPropertiesMode{@link #AudioPropertiesMode}。<br>
     *        默认仅包含本地麦克风采集的音频数据和本地屏幕音频采集数据。
     */
    AudioPropertiesMode audio_report_mode = kAudioPropertiesModeMicrophone;
};
/** 
 * @type keytype
 * @brief 音频属性信息  <br>
 */
struct AudioPropertiesInfo {
    /** 
     * @brief 线性音量，与原始音量呈线性关系，数值越大，音量越大。取值范围是：[0,255]。<br>
     *        - [0, 25]: 无声 <br>
     *        - [26, 75]: 低音量 <br>
     *        - [76, 204]: 中音量 <br>
     *        - [205, 255]: 高音量 <br>
     */
    int linear_volume;
    /** 
     * @brief 非线性音量。由原始音量的对数值转化而来，因此在中低音量时更灵敏，可以用作 Active Speaker（房间内最活跃用户）的识别。取值范围是：[-127，0]，单位 dB。 <br>
     *        - [-127, -60]: 无声 <br>
     *        - [-59, -40]: 低音量 <br>
     *        - [-39, -20]: 中音量 <br>
     *        - [-19, 0]: 高音量 <br>
     */
    int nonlinear_volume;
    /** 
     * @brief 频谱数组。默认长度为 257。
     */
    float spectrum[SPECTRUM_SIZE] = {0};
    /** 
     * @brief 人声检测（VAD）结果
     *        + 1: 检测到人声。<br>
     *        + 0: 未检测到人声。<br>
     *        + -1: 未开启 VAD。<br>
     */
    int vad = -1;
};

/** 
 * @type keytype
 * @brief 远端音频属性信息
 */
struct RemoteAudioPropertiesInfo {
    /** 
     * @type keytype
     * @brief 远端流信息，详见 RemoteStreamKey{@link #RemoteStreamKey}
     */
    RemoteStreamKey stream_key;
    /** 
     * @type keytype
     * @brief 音频属性信息，详见 AudioPropertiesInfo{@link #AudioPropertiesInfo}
     */
    AudioPropertiesInfo audio_properties_info;
};

/** 
 * @type keytype
 * @brief 本地音频属性信息
 */
struct LocalAudioPropertiesInfo {
    /** 
     * @brief 流属性，主流或屏幕流。参看 StreamIndex{@link #StreamIndex}
     */
    StreamIndex stream_index;
    /** 
     * @type keytype
     * @brief 音频属性信息，详见 AudioPropertiesInfo{@link #AudioPropertiesInfo}
     */
    AudioPropertiesInfo audio_properties_info;
};

/** 
 * @type keytype
 * @brief 音质档位
 */
enum AudioProfileType {
    /** 
     * @brief 默认音质<br>
     *        服务器下发或客户端已设置的 RoomProfileType{@link #RoomProfileType} 的音质配置
     */
    kAudioProfileTypeDefault = 0,
    /** 
     * @brief 流畅  <br>
     *        单声道，采样率为 16 kHz，编码码率为 32 Kbps。 <br>
     *        流畅优先、低功耗、低流量消耗，适用于大部分游戏场景，如小队语音、组队语音、国战语音等。
     */
    kAudioProfileTypeFluent = 1,
    /** 
     * @brief 单声道标准音质。  <br>
     *        采样率为 24 kHz，编码码率为 48 Kbps。 <br>
     *        适用于对音质有一定要求的场景，同时延时、功耗和流量消耗相对适中，适合教育场景和狼人杀等游戏。
     */
    kAudioProfileTypeStandard = 2,
    /** 
     * @brief 双声道音乐音质  <br>
     *        采样率为 48 kHz，编码码率为 128 kbps。 <br>
     *        超高音质，同时延时、功耗和流量消耗相对较大，适用于连麦 PK 等音乐场景。 <br>
     *        游戏场景不建议使用。
     */
    kAudioProfileTypeHD = 3,
    /** 
     * @brief 双声道标准音质。采样率为 48 KHz，编码码率最大值为 80 Kbps
     */
    kAudioProfileTypeStandardStereo = 4,
    /** 
     * @brief 单声道音乐音质。采样率为 48 kHz，编码码率最大值为 64 Kbps
     */
    kAudioProfileTypeHDMono = 5,
};

/** 
 * @type keytype
 * @brief 本地用户在房间内的位置坐标，需自行建立空间直角坐标系
 */
struct Position {
    /** 
     * @brief x 坐标
     */
    int x;
    /** 
     * @brief y 坐标
     */
    int y;
    /** 
     * @brief z 坐标
     */
    int z;
    /**
     * @hidden
     */
    bool isEqual(const Position& pos) const {
        return x == pos.x && y == pos.y && z == pos.z;
    }
};

/** 
 * @hidden(Linux)
 * @type keytype
 * @brief 音频音量是否可设置
 */
enum AudioAbilityType {
    /** 
     * @brief 未知
     */
    kAudioAbilityTypeUnknown = -1,
    /** 
     * @brief 音量可设置
     */
    kAudioAbilityAble = 0,
    /** 
     * @brief 音量不可设置
     */
    kAudioAbilityUnable = 1,
};

/** 
 * @type keytype
 * @brief 音频设备信息
 */
struct AudioDeviceInfo {
    /** 
     * @brief 设备 ID
     */
    char device_id[MAX_DEVICE_ID_LENGTH];
    /** 
     * @brief 设备名称
     */
    char device_name[MAX_DEVICE_ID_LENGTH];
    /** 
     * @brief 设备所连接的声卡 ID，便于选择使用同一声卡的扬声器和麦克风。
     */
    char device_container_id[MAX_DEVICE_ID_LENGTH];
    /** 
     * @brief 设备的厂商 ID
     */
    int64_t device_vid;
    /** 
     * @brief 设备的产品编码
     */
    int64_t device_pid;
    /** 
     * @brief 设备的传输方式
     */
    DeviceTransportType transport_type;
    /** 
     * @brief 是否支持设置音量
     */
    AudioAbilityType volume_settable;
    /** 
     * @brief 是否系统默认设备
     */
    bool is_system_default;
    /**
     * @hidden
     */
    AudioDeviceInfo() {
        memset(device_id, 0, MAX_DEVICE_ID_LENGTH);
        memset(device_name, 0, MAX_DEVICE_ID_LENGTH);
        memset(device_container_id, 0, MAX_DEVICE_ID_LENGTH);
        this->device_vid = 0;
        this->device_pid = 0;
        this->transport_type = DeviceTransportType::kDeviceTransportTypeUnknown;
        this->volume_settable = AudioAbilityType::kAudioAbilityTypeUnknown;
        this->is_system_default = false;
    }

    /** 
     * @hidden
     * @brief 342需求，缺注释，需补齐
     */
    AudioDeviceInfo& operator=(const AudioDeviceInfo& src) {
        if (this != &src) {
            strncpy(device_id, src.device_id, MAX_DEVICE_ID_LENGTH - 1);
            strncpy(device_name, src.device_name, MAX_DEVICE_ID_LENGTH - 1);
            strncpy(device_container_id, src.device_container_id, MAX_DEVICE_ID_LENGTH - 1);
            device_id[MAX_DEVICE_ID_LENGTH - 1] = '\0';
            device_name[MAX_DEVICE_ID_LENGTH - 1] = '\0';
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
 * @hidden(Linux)
 * @type keytype
 * @brief 标准音高数据
 */
struct StandardPitchInfo {
/** 
 * @brief 开始时间，单位 ms。
 */
int start_time;
/** 
 * @brief 持续时间，单位 ms。
 */
int duration;
/** 
 * @brief 音高。
 */
int pitch;
};
/** 
 * @hidden(Linux)
 * @type keytype
 * @brief K 歌打分维度。
 */
enum MulDimSingScoringMode {
    /** 
     * @brief 按照音高进行评分。
     */
    kMulDimSingScoringModeNote = 0
};
/** 
 * @hidden(Linux)
 * @type keytype
 * @brief K 歌评分配置。
 */
struct SingScoringConfig {
/** 
 * @brief 音频采样率。仅支持 44100 Hz、48000 Hz。
 */
AudioSampleRate sample_rate;
/** 
 * @brief 打分维度，详见 MulDimSingScoringMode{@link #MulDimSingScoringMode}。
 */
MulDimSingScoringMode mode;
/** 
 * @brief 歌词文件路径。打分功能仅支持 KRC 歌词文件。
 */
const char* lyrics_filepath;
/** 
 * @brief 歌曲 midi 文件路径。
 */
const char* midi_filepath;
};
/** 
 * @hidden(Linux)
 * @type keytype
 * @brief 实时评分信息。
 */
struct SingScoringRealtimeInfo {
/** 
 * @brief 当前播放进度。
 */
int current_position;
/** 
 * @brief 演唱者的音高。
 */
int user_pitch;
/** 
 * @brief 标准音高。
 */
int standard_pitch;
/** 
 * @brief 歌词分句索引。
 */
int sentence_index;
/** 
 * @brief 上一句歌词的评分。
 */
int sentence_score;
/** 
 * @brief 当前演唱的累计分数。
 */
int total_score;
/** 
 * @brief 当前演唱的平均分数。
 */
int average_score;
};


}  // namespace bytertc
