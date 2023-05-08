/*
 * Copyright (c) 2022 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief Objective-C VolcEngineRTC Audio Defines
*/

#import "ByteRTCMediaDefines.h"

/** 
 * @type keytype
 * @brief 音频场景类型。
 *        选择音频场景后，SDK 会自动根据客户端音频采集播放设备和状态，适用通话音量/媒体音量。
 *        如果以下音频场景类型无法满足你的业务需要，请联系技术支持人员。
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioScenarioType) {
    /** 
     * @brief （默认）音乐场景。
     *        此场景适用于对音乐表现力有要求的场景，如音乐直播等。
     *        音频采集播放设备和采集播放状态，到音量类型的映射如下：
     *        <table>
     *           <tr><th></th><th>不采集音频</th><th>采集音频</th><th>备注</th></tr>
     *           <tr><td>设备自带麦克风和扬声器</td><td>媒体音量</td><td>通话音量</td><td>/</td></tr>
     *           <tr><td>听筒</td><td>媒体音量</td><td>通话音量</td><td>/</td></tr>
     *           <tr><td>有线耳机/ USB 耳机/ 外置声卡</td><td>媒体音量</td><td>媒体音量</td><td>/</td></tr>
     *           <tr><td>蓝牙耳机</td><td>媒体音量</td><td>媒体音量</td><td>即使蓝牙耳机有麦克风，也只能使用设备自带麦克风进行本地音频采集。</td></tr>
     *        </table>
     */
    ByteRTCAudioScenarioMusic = 0,
    /** 
     * @brief 高质量通话场景。  <br>
     *        此场景适用于对音乐表现力有要求，但又希望能够使用蓝牙耳机上自带的麦克风进行音频采集的场景。  <br>
     *        此场景下，更倾向于使用媒体音量。由此，可能引起开关麦时音量突变。如不希望有此突变，请使用 `ByteRTCAudioScenarioHighqualityChat`。 <br>
     *        此场景可以兼顾外放/使用蓝牙耳机时的音频体验，并避免使用蓝牙耳机时音量类型切换导致的听感突变。  <br>
     *        音频采集播放设备和采集播放状态，到音量类型的映射如下：<br>
     *        <table>
     *           <tr><th></th><th>不采集音频</th><th>采集音频</th><th>备注</th></tr>
     *           <tr><td>设备自带麦克风和扬声器</td><td>媒体音量</td><td>通话音量</td><td>/</td></tr>
     *           <tr><td>听筒</td><td>媒体音量</td><td>通话音量</td><td>/</td></tr>
     *           <tr><td>有线耳机/ USB 耳机/ 外置声卡</td><td>媒体音量</td><td>媒体音量</td><td>/</td></tr>
     *           <tr><td>蓝牙耳机</td><td>通话音量</td><td>通话音量</td><td>能够使用蓝牙耳机上自带的麦克风进行音频采集。</td></tr>
     *        </table>
     */
    ByteRTCAudioScenarioHighqualityCommunication = 1,
    /** 
     * @brief 纯通话音量场景。
     *        此场景下，无论客户端音频路由情况和发布订阅状态，全程使用通话音量。
     *        适用于需要频繁上下麦的通话或会议场景。
     *        此场景可以保持统一的音频模式，不会有音量突变的听感；
     *        最大程度地消除回声，使通话清晰度达到最优；
     *        使用蓝牙耳机时，能够使用蓝牙耳机上自带的麦克风进行音频采集。
     *        但是，会压低使用媒体音量进行播放的其他音频的音量，且音质会变差。
     */
    ByteRTCAudioScenarioCommunication = 2,
    /** 
     * @brief 纯媒体场景。一般不建议使用。
     *        此场景下，无论客户端音频采集播放设备和采集播放状态，全程使用媒体音量。
     *        外放通话时，可能出现回声和啸叫，请联系技术支持人员。
     */
    ByteRTCAudioScenarioMedia = 3,
    /** 
     * @brief 游戏媒体场景。
     *        若外放通话且无游戏音效消除优化时音质不理想，请联系技术支持人员。
     *        音频采集播放设备和采集播放状态，到音量类型的映射如下：<br>
     *        <table>
     *           <tr><th></th><th>不采集音频</th><th>采集音频</th><th>备注</th></tr>
     *           <tr><td>设备自带麦克风和扬声器</td><td>媒体音量</td><td>媒体音量</td><td>/</td></tr>
     *           <tr><td>听筒</td><td>媒体音量</td><td>媒体音量</td><td>/</td></tr>
     *           <tr><td>有线耳机/ USB 耳机/ 外置声卡</td><td>媒体音量</td><td>媒体音量</td><td>/</td></tr>
     *           <tr><td>蓝牙耳机</td><td>通话音量</td><td>通话音量</td><td>能够使用蓝牙耳机上自带的麦克风进行音频采集。</td></tr>
     *        </table>
     */
    ByteRTCAudioScenarioGameStreaming = 4,
    /** 
     * @brief 高质量畅聊场景。  <br>
     *        此场景和 `ByteRTCAudioScenarioHighqualityCommunication` 高度类似，唯一的差异在于：此场景下，在使用设备自带的麦克风和扬声器/听筒进行通话时，开关麦始终采用通话音量，不会引起音量类型突变。 <br>
     *        音频采集播放设备和采集播放状态，到音量类型的映射如下：<br>
     *        <table>
     *           <tr><th></th><th>不采集音频</th><th>采集音频</th><th>备注</th></tr>
     *           <tr><td>设备自带麦克风和扬声器</td><td>通话音量</td><td>通话音量</td><td>/</td></tr>
     *           <tr><td>听筒</td><td>通话音量</td><td>通话音量</td><td>/</td></tr>
     *           <tr><td>有线耳机/ USB 耳机/ 外置声卡</td><td>媒体音量</td><td>媒体音量</td><td>/</td></tr>
     *           <tr><td>蓝牙耳机</td><td>通话音量</td><td>通话音量</td><td>能够使用蓝牙耳机上自带的麦克风进行音频采集。</td></tr>
     *        </table>
     */
    ByteRTCAudioScenarioHighqualityChat = 5,
};

/** 
 * @type keytype
 * @brief 变声特效类型
 */
typedef NS_ENUM(NSInteger, ByteRTCVoiceChangerType) {
    /** 
     * @brief 原声，不含特效
     */
    ByteRTCVoiceChangerOriginal = 0,
    /** 
     * @brief 巨人
     */
    ByteRTCVoiceChangerGiant = 1,
    /** 
     * @brief 花栗鼠
     */
    ByteRTCVoiceChangerChipmunk = 2,
    /** 
     * @brief 小黄人
     */
    ByteRTCVoiceChangerMinionst = 3,
    /** 
     * @brief 颤音
     */
    ByteRTCVoiceChangerVibrato = 4,
    /** 
     * @brief 机器人
     */
    ByteRTCVoiceChangerRobot = 5,
};

/** 
 * @type keytype
 * @brief 混响特效类型
 */
typedef NS_ENUM(NSInteger, ByteRTCVoiceReverbType) {
    /** 
     * @brief 原声，不含特效
     */
    ByteRTCVoiceReverbOriginal = 0,
    /** 
     * @brief 回声
     */
    ByteRTCVoiceReverbEcho = 1,
    /** 
     * @brief 演唱会
     */
    ByteRTCVoiceReverbConcert = 2,
    /** 
     * @brief 空灵
     */
    ByteRTCVoiceReverbEthereal = 3,
    /** 
     * @brief KTV
     */
    ByteRTCVoiceReverbKTV = 4,
    /** 
     * @brief 录音棚
     */
    ByteRTCVoiceReverbStudio = 5,
    /** 
     * @brief 虚拟立体声
     */
    ByteRTCVoiceReverbVirtualStereo = 6,
    /** 
     * @brief 空旷
     */
    ByteRTCVoiceReverbSpacious = 7,
    /** 
     * @brief 3D人声
     */
    ByteRTCVoiceReverb3D = 8,
    /** 
     * @hidden internal use
     * @brief 流行
     */
    ByteRTCVoiceReverbPop = 9,
    /** 
     * @hidden internal use
     * @brief 蹦迪
     */
    ByteRTCVoiceReverbDisco = 10,
    /** 
     * @hidden internal use
     * @brief 老唱片
     */
    ByteRTCVoiceReverbOldRecord = 11,
    /** 
     * @hidden internal use
     * @brief 和声
     */
    ByteRTCVoiceReverbHarmony = 12,
    /** 
     * @hidden internal use
     * @brief 摇滚
     */
    ByteRTCVoiceReverbRock = 13,
    /** 
     * @hidden internal use
     * @brief 蓝调
     */
    ByteRTCVoiceReverbBlues = 14,
    /** 
     * @hidden internal use
     * @brief 爵士
     */
    ByteRTCVoiceReverbJazz = 15,
    /** 
     * @hidden internal use
     * @brief 电子
     */
    ByteRTCVoiceReverbElectronic = 16,
    /** 
     * @hidden internal use
     * @brief 黑胶
     */
    ByteRTCVoiceReverbVinyl = 17,
    /** 
     * @hidden internal use
     * @brief 密室
     */
    ByteRTCVoiceReverbChamber = 18,
};
/** 
 * @type keytype
 * @brief 音频均衡效果。
 */
typedef NS_ENUM(NSInteger, ByteRTCBandFrequency) {
    /** 
     * @brief 中心频率为 31Hz 的频带。
     */
    ByteRTCBandFrequency31 = 0,
    /** 
     * @brief 中心频率为 62Hz 的频带。
     */
    ByteRTCBandFrequency62 = 1,
    /** 
     * @brief 中心频率为 125Hz 的频带。
     */
    ByteRTCBandFrequency125 = 2,
    /** 
     * @brief 中心频率为 250Hz 的频带。
     */
    ByteRTCBandFrequency250 = 3,
    /** 
     * @brief 中心频率为 500Hz 的频带。
     */
    ByteRTCBandFrequency500 = 4,
    /** 
     * @brief 中心频率为 1kHz 的频带。
     */
    ByteRTCBandFrequency1k = 5,
    /** 
     * @brief 中心频率为 2kHz 的频带。
     */
    ByteRTCBandFrequency2k = 6,
    /** 
     * @brief 中心频率为 4kHz 的频带。
     */
    ByteRTCBandFrequency4k = 7,
    /** 
     * @brief 中心频率为 8kHz 的频带。
     */
    ByteRTCBandFrequency8k = 8,
    /** 
     * @brief 中心频率为 16kHz 的频带。
     */
    ByteRTCBandFrequency16k = 9,
};
/** 
 * @type keytype
 * @brief 语音均衡效果。
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVoiceEqualizationConfig : NSObject
/** 
 * @brief 频带。参看 ByteRTCBandFrequency{@link #ByteRTCBandFrequency}。
 */
@property(assign, nonatomic) ByteRTCBandFrequency frequency;
/** 
 * @brief 频带增益（dB）。取值范围是 `[-15, 15]`。
 */
@property(assign, nonatomic) int gain;
@end

/** 
 * @type keytype
 * @brief 音频混响效果。
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVoiceReverbConfig : NSObject
/** 
 * @brief 混响模拟的房间大小，取值范围 `[0.0, 100.0]`。默认值为 `50.0f`。房间越大，混响越强。
 */
@property(assign, nonatomic) float roomSize;
/** 
 * @brief 混响的拖尾长度，取值范围 `[0.0, 100.0]`。默认值为 `50.0f`。
 */
@property(assign, nonatomic) float decayTime;
/** 
 * @brief 混响的衰减阻尼大小，取值范围 `[0.0, 100.0]`。默认值为 `50.0f`。
 */
@property(assign, nonatomic) float damping;
/** 
 * @brief 早期反射信号强度。取值范围 `[-20.0, 10.0]`，单位为 dB。默认值为 `0.0f`。
 */
@property(assign, nonatomic) float wetGain;
/** 
 * @brief 原始信号强度。取值范围 `[-20.0, 10.0]`，单位为 dB。默认值为 `0.0f`。
 */
@property(assign, nonatomic) float dryGain;
/** 
 * @brief 早期反射信号的延迟。取值范围 `[0.0, 200.0]`，单位为 ms。默认值为 `0.0f`。
 */
@property(assign, nonatomic) float preDelay;
@end

/** 
 * @type keytype
 * @brief 音质档位
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioProfileType) {
    /** 
     * @brief 默认音质<br>
     *        服务器下发或客户端已设置的 ByteRTCRoomProfile{@link #ByteRTCRoomProfile} 的音质配置
     */
    ByteRTCAudioProfileDefault = 0,
    /** 
     * @brief 流畅  <br>
     *        单声道，采样率为 16 kHz，编码码率为 32 Kbps。 <br>
     *        流畅优先、低功耗、低流量消耗，适用于大部分游戏场景，如小队语音、组队语音、国战语音等。
     */
    ByteRTCAudioProfileFluent = 1,
    /** 
     * @brief 单声道标准音质。  <br>
     *        采样率为 24 kHz，编码码率为 48 Kbps。 <br>
     *        适用于对音质有一定要求的场景，同时延时、功耗和流量消耗相对适中，适合教育场景和狼人杀等游戏。
     */
    ByteRTCAudioProfileStandard = 2,
    /** 
     * @brief 双声道音乐音质  <br>
     *        采样率为 48 kHz，编码码率为 128 kbps。 <br>
     *        超高音质，同时延时、功耗和流量消耗相对较大，适用于连麦 PK 等音乐场景。 <br>
     *        游戏场景不建议使用。
     */
    ByteRTCAudioProfileHD = 3,
    /** 
     * @brief 双声道标准音质。采样率为 48 KHz，编码码率最大值为 80 Kbps
     */
    ByteRTCAudioProfileStandardStereo = 4,
    /** 
     * @brief 单声道音乐音质。采样率为 48 kHz，编码码率最大值为 64 Kbps
     */
    ByteRTCAudioProfileHDMono = 5,
};

/** 
 * @type keytype
 * @brief 降噪模式。降噪算法受调用 joinRoomByToken:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoom:userInfo:roomConfig:} 时设置的房间模式影响。
 */
typedef NS_ENUM(NSInteger, ByteRTCAnsMode) {
    /** 
     * @brief 关闭所有音频降噪能力。
     */
    ByteRTCAnsModeDisable = 0,
   /** 
     * @brief 适用于微弱降噪。
     */
    ByteRTCAnsModeLow = 1,
    /** 
     * @brief 适用于抑制中度平稳噪声，如空调声和风扇声。
     */
    ByteRTCAnsModeMedium = 2,
     /** 
     * @brief 适用于抑制嘈杂非平稳噪声，如键盘声、敲击声、碰撞声、动物叫声。
     */
    ByteRTCAnsModeHigh = 3,
    /** 
     * @brief 启用音频降噪能力。具体的降噪算法由 RTC 智能决策。
     */
    ByteRTCAnsModeAutomatic = 4,
};

/** 
 * @hidden
 * @deprecated since 3.45 and will be deleted in 3.51.
 * @type keytype
 * @brief 语音通话模式，在小队语音里用这个接口设置自己的发送模式
 */
typedef NS_ENUM(NSUInteger, ByteRTCRangeAudioMode) {
    /** 
     * @brief 默认模式
     */
    ByteRTCRangeAudioModeUndefined = 0,
    /** 
     * @brief 小队模式
     */
    ByteRTCRangeAudioModeTeam = 1,
    /** 
     * @brief 世界模式
     */
    ByteRTCRangeAudioModeWorld = 2,
};

/** 
 * @type keytype
 * @brief 当前音频设备类型
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioDeviceType) {
    /** 
     * @brief 未知音频设备
     */
    ByteRTCAudioDeviceTypeUnknown = -1,
    /** 
     * @brief 音频渲染设备
     */
    ByteRTCAudioDeviceTypeRenderDevice = 0,
    /** 
     * @brief 音频采集设备
     */
    ByteRTCAudioDeviceTypeCaptureDevice = 1,
    /** 
     * @brief 屏幕流音频设备
     */
    ByteRTCAudioDeviceTypeScreenCaptureDevice = 2
};
/** 
 * @type keytype
 * @brief 音频采样率，单位为 Hz。
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioSampleRate) {
    /** 
     * @brief 默认设置。48000Hz。
     */
    ByteRTCAudioSampleRateAuto = -1,
    /** 
     * @brief 8000Hz
     */
    ByteRTCAudioSampleRate8000 = 8000,
    /** 
     * @brief 16000Hz
     */
    ByteRTCAudioSampleRate16000 = 16000,
    /** 
     * @brief 32000Hz
     */
    ByteRTCAudioSampleRate32000 = 32000,
    /** 
     * @brief 44100Hz
     */
    ByteRTCAudioSampleRate44100 = 44100,
    /** 
     * @brief 48000Hz
     */
    ByteRTCAudioSampleRate48000 = 48000
};
/** 
 * @type keytype
 * @brief 音频声道。
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioChannel) {
    /** 
     * @brief 默认设置。默认值为 `2`。
     */
    ByteRTCAudioChannelAuto = -1,
    /** 
     * @brief 单声道
     */
    ByteRTCAudioChannelMono = 1,
    /** 
     * @brief 双声道
     */
    ByteRTCAudioChannelStereo = 2,
};

/** 
 * @type keytype
 * @brief 音频编码类型。
 */
typedef NS_ENUM(NSInteger, ByteRTCTranscodingAudioCodec) {
    /** 
     * @type keytype
     * @brief AAC 格式。
     */
    ByteRTCTranscodingAudioCodecAAC = 0,
};

/** 
 * @type keytype
 * @brief AAC 编码规格。
 */
typedef NS_ENUM(NSInteger, ByteRTCAACProfile) {
    /** 
     * @brief AAC-LC 规格，默认值。
     */
    ByteRTCAACProfileLC   = 0,
    /** 
     * @brief HE-AAC v1 规格。
     */
    ByteRTCAACProfileHEv1 = 1,
    /** 
     * @brief HE-AAC v2 规格。
     */
    ByteRTCAACProfileHEv2 = 2,
};
/** 
 * @type keytype
 * @brief 音频播放路由
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioRoute) {
    /** 
     * @brief 默认设备。通过 `setDefaultAudioRoute:` 设置的音频路由。
     */
    ByteRTCAudioRouteDefault = -1,
    /** 
     * @brief 有线耳机
     */
    ByteRTCAudioRouteHeadset = 1,
    /** 
     * @brief 听筒。设备自带的，一般用于通话的播放硬件。
     */
    ByteRTCAudioRouteEarpiece = 2,
    /** 
     * @brief 扬声器。设备自带的，一般用于免提播放的硬件。
     */
    ByteRTCAudioRouteSpeakerphone = 3,
    /** 
     * @brief 蓝牙耳机
     */
    ByteRTCAudioRouteHeadsetBluetooth = 4,
    /** 
     * @brief USB设备
     */
    ByteRTCAudioRouteHeadsetUSB = 5,
};

/** 
 * @type keytype
 * @brief 音频播放设备 <br>
 *        音频设备变化时 SDK 通过 `rtcEngine:onAudioPlaybackDeviceChanged:` 回调当前音频播放设备。
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioPlaybackDevice) {
    /** 
     * @brief 有线耳机
     */
    ByteRTCAudioPlaybackDeviceHeadset = 1,
    /** 
     * @brief 听筒
     */
    ByteRTCAudioPlaybackDeviceEarpiece = 2,
    /** 
     * @brief 扬声器
     */
    ByteRTCAudioPlaybackDeviceSpeakerphone = 3,
    /** 
     * @brief 蓝牙耳机
     */
    ByteRTCAudioPlaybackDeviceHeadsetBluetooth = 4,
    /** 
     * @brief USB设备
     */
    ByteRTCAudioPlaybackDeviceHeadsetUSB = 5,
};

/** 
 * @type keytype
 * @brief 语音识别服务鉴权方式，详情请咨询语音识别服务相关人员
 */
typedef NS_ENUM(NSInteger, ByteRTCASRAuthorizationType) {
    /** 
     *  @brief 使用 token 不设置加密形式。  <br>
     */
    ByteRTCASRAuthorizationTypeToken = 0,
    /** 
     *  @brief 带有 token 额外使用 signature 加密，此种加密形式需要额外传递 secret token 。  <br>
     */
    ByteRTCASRAuthorizationTypeSignature = 1,
};

/** 
 * @type keytype
 * @brief 语音识别服务错误码。  <br>
 *        除网络原因导致的错误，语音识别服务内部会自行重试之外，其他错误都会停止服务，此时建议再次调用 `startASR:handler:` 重启语音识别功能。
 */
typedef NS_ENUM(NSInteger, ByteRTCASRErrorCode) {
    /** 
     * @brief 网络连接中断，服务不可用，内部会进行重连
     */
    ByteRTCASRErrorNetworkInterrupted = -1,
    /** 
     * @brief 用户已经调用过 `startASR:handler:`。  <br>
     *        开启语音识别服务后，你需要先调用 `stopASR` 停止语音识别服务，才能二次调用 `startASR:handler:` 再次开启服务。
     */
    ByteRTCASRErrorAlreadyStarted = -2,
    /** 
     * @brief 语音识别服务所需 token 为空
     */
    ByteRTCASRErrorTokenEmpty = -3,
    /** 
     * @brief Signature 鉴权模式下 secretKey 为空
     */
    ByteRTCErrorSignatureKeyEmpty = -4,
    /** 
     * @brief 用户 ID 为空
     */
    ByteRTCASRErrorUserIdNull = -5,
    /** 
     * @brief 应用 ID 为空
     */
    ByteRTCASRErrorAPPIDNull = -6,
    /** 
     * @brief 语音识别服务 cluster 为空
     */
    ByteRTCASRErrorClusterNull = -7,
    /** 
     * @brief 语音识别服务连接失败，该版本没有语音识别功能，请联系 RTC 技术支持。
     */
    ByteRTCASRErrorOperationDenied = -8
};

/** 
 * @type keytype
 * @brief 混音播放类型
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioMixingType) {
    /** 
     * @brief 仅本地播放
     */
    ByteRTCAudioMixingTypePlayout = 0,
    /** 
     * @brief 仅远端播放
     */
    ByteRTCAudioMixingTypePublish = 1,
    /** 
     * @brief 本地和远端同时播放
     */
    ByteRTCAudioMixingTypePlayoutAndPublish = 2
};

/** 
 * @type keytype
 * @brief 混音播放声道类型
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioMixingDualMonoMode) {
    /** 
     * @brief 和音频文件一致
     */
    ByteRTCAudioMixingDualMonoModeAuto = 0,
    /** 
     * @brief 只能听到音频文件中左声道的音频
     */
    ByteRTCAudioMixingDualMonoModeL = 1,
    /** 
     * @brief 只能听到音频文件中右声道的音频
     */
    ByteRTCAudioMixingDualMonoModeR = 2,
    /** 
     * @brief 能同时听到音频文件中左右声道的音频
     */
    ByteRTCAudioMixingDualMonoModeMix = 3
};

/** 
 * @type keytype
 * @brief 音频混音文件播放状态。
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioMixingState) {
    /** 
     * @brief 混音已加载
     */
    ByteRTCAudioMixingStatePreloaded = 0,
    /** 
     * @brief 混音正在播放
     */
    ByteRTCAudioMixingStatePlaying,
    /** 
     * @brief 混音暂停
     */
    ByteRTCAudioMixingStatePaused,
    /** 
     * @brief 混音停止
     */
    ByteRTCAudioMixingStateStopped,
    /** 
     * @brief 混音播放失败
     */
    ByteRTCAudioMixingStateFailed,
    /** 
     * @brief 混音播放结束
     */
    ByteRTCAudioMixingStateFinished,
    /** 
     * @brief 准备PCM混音
     */
    ByteRTCAudioMixingStatePCMEnabled,
    /** 
     * @brief PCM混音播放结束
     */
    ByteRTCAudioMixingStatePCMDisabled,
};
/** 
 * @type keytype
 * @brief 混音错误码。
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioMixingError) {
    /** 
     * @brief 正常
     */
    ByteRTCAudioMixingErrorOk = 0,
    /** 
     * @brief 预加载失败，找不到混音文件或者文件长度超出 20s
     */
    ByteRTCAudioMixingErrorPreloadFailed,
    /** 
     * @brief 混音开启失败，找不到混音文件或者混音文件打开失败
     */
    ByteRTCAudioMixingErrorStartFailed,
    /** 
     * @brief 混音 ID 异常
     */
    ByteRTCAudioMixingErrorIdNotFound,
    /** 
     * @brief 设置混音文件的播放位置出错
     */
    ByteRTCAudioMixingErrorSetPositionFailed,
    /** 
     * @brief 音量参数不合法，仅支持设置的音量值为[0, 400]
     */
    ByteRTCAudioMixingErrorInValidVolume,
    /** 
     * @brief 播放的文件与预加载的文件不一致。请先使用 unloadAudioMixing:{@link #ByteRTCAudioMixingManager#unloadAudioMixing:} 卸载此前的文件。
     */
    ByteRTCAudioMixingErrorLoadConflict,
    /** 
     * @brief 不支持此混音类型。
     */
    ByteRTCAudioMixingErrorIdTypeNotMatch,
    /** 
     * @brief 设置混音文件的音调不合法
     */
    ByteRTCAudioMixingErrorInValidPitch,
    /** 
     * @brief 设置混音文件的音轨不合法
     */
    ByteRTCAudioMixingErrorInValidAudioTrack,
    /** 
     * @brief 混音文件正在启动中
     */
    ByteRTCAudioMixingErrorIsStarting,
    /** 
     * @brief 设置混音文件的播放速度不合法
     */
    ByteRTCAudioMixingErrorInValidPlaybackSpeed,
};

/** 
 * @type keytype
 * @brief 音频输入源类型
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioSourceType) {
    /** 
     * @brief 自定义采集音频源
     */
    ByteRTCAudioSourceTypeExternal = 0,
    /** 
     * @brief RTC SDK 内部采集音频源
     */
    ByteRTCAudioSourceTypeInternal,
};

/** 
 * @type keytype
 * @brief 音频输出源类型
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioRenderType) {
    /** 
     * @brief 自定义渲染音频
     */
    ByteRTCAudioRenderTypeExternal = 0,
    /** 
     * @brief RTC SDK 内部渲染音频
     */
    ByteRTCAudioRenderTypeInternal,
};

/** 
 * @type keytype
 * @brief 开启/关闭耳返功能。
 */
typedef NS_ENUM(NSInteger, ByteRTCEarMonitorMode) {
    /** 
     * @brief 关闭耳返功能。
     */
    ByteRTCEarMonitorModeOff = 0,
    /** 
     * @brief 开启耳返功能。
     */
    ByteRTCEarMonitorModeOn = 1,
};

/** 
 * @type keytype
 * @brief 音频回调方法
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioFrameCallbackMethod) {
    /** 
     * @brief 本地麦克风录制的音频数据回调
     */
    ByteRTCAudioFrameCallbackRecord = 0,
    /** 
     * @brief 订阅的远端所有用户混音后的音频数据回调
     */
    ByteRTCAudioFrameCallbackPlayback = 1,
    /** 
     * @brief 本地麦克风录制和订阅的远端所有用户混音后的音频数据回调
     */
    ByteRTCAudioFrameCallbackMixed = 2,
    /** 
     * @brief 订阅的远端每个用户混音前的音频数据回调
     */
    ByteRTCAudioFrameCallbackRemoteUser = 3,
};
/** 
 * @type keytype
 * @brief 返回给音频处理器的音频类型。
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioFrameMethod) {
    /** 
     * @brief 本地采集的音频。
     */
    ByteRTCAudioFrameProcessorRecord = 0,
    /** 
     * @brief 远端音频流的混音音频。
     */
    ByteRTCAudioFrameProcessorPlayback = 1,
    /** 
     * @brief 各个远端音频流。
     */
    ByteRTCAudioFrameProcessorRemoteUser = 2,
    /** 
     * @hidden(macOS)
     * @brief 软件耳返音频。
     */
    ByteRTCAudioFrameProcessorEarMonitor = 3,
     /** 
     * @brief 屏幕共享音频。
     */
    ByteRTCAudioFrameProcessorScreen = 4,
};

/** 
 * @type keytype
 * @brief 音量回调模式。
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioReportMode) {
     /** 
     * @brief 默认始终开启音量回调。
     */
    ByteRTCAudioReportModeNormal = 0,
   /** 
     * @brief 可见用户进房并停止推流后，关闭音量回调。
     */
    ByteRTCAudioReportModeDisconnect = 1,
     /** 
     * @brief 可见用户进房并停止推流后，开启音量回调，回调值重置为0。
     */
    ByteRTCAudioReportModeReset = 2,
};

/** 
 * @type keytype
 * @brief 音频信息提示中是否包含本地混音音频数据。
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioPropertiesMode) {
    /** 
     * @brief 音频信息提示中，仅包含本地麦克风采集的音频数据和本地屏幕音频采集数据。
     */
    ByteRTCAudioPropertiesModeMicrohone = 0,
    /** 
     * @brief 音频信息提示中，除本地麦克风采集的音频数据和本地屏幕音频采集数据外，还包含本地混音的音频数据。
     */
    ByteRTCAudioPropertiesModeAudioMixing = 1
};

/** 
 * @type keytype
 * @brief 音频流来源的用户 ID, 及对应的音量。
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCAudioVolumeInfo : NSObject
/** 
 * @brief 音频流来源的用户 ID
 */
@property(copy, nonatomic) NSString * _Nonnull uid;
/** 
 * @brief 线性音量，取值范围为：[0,255]
 */
@property(assign, nonatomic) NSUInteger linearVolume;
/** 
 * @brief 非线性音量，取值范围为：[-127,0]
 */
@property(assign, nonatomic) NSUInteger nonlinearVolume;
@end

/** 
 * @type keytype
 * @brief 音频参数格式
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCAudioFormat : NSObject
/** 
 * @brief 音频采样率，详见 ByteRTCAudioSampleRate{@link #ByteRTCAudioSampleRate}
 */
@property(nonatomic, assign) ByteRTCAudioSampleRate sampleRate;
/** 
 * @brief 音频声道，详见 ByteRTCAudioChannel{@link #ByteRTCAudioChannel}
 */
@property(nonatomic, assign) ByteRTCAudioChannel channel;
@end

/** 
 * @type keytype
 * @brief PCM 音频帧
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCAudioFrame : NSObject
/** 
 * @brief PCM 数据
 */
@property(strong, nonatomic) NSData * _Nonnull buffer;
/** 
 * @brief 采样点个数
 */
@property(assign, nonatomic) int samples;
/** 
 * @brief 音频声道，参看 ByteRTCAudioChannel{@link #ByteRTCAudioChannel}。
 *        双声道的情况下，左右声道的音频帧数据以 LRLRLR 形式排布。
 */
@property(assign, nonatomic) ByteRTCAudioChannel channel;
/** 
 * @brief 采样率，参看 ByteRTCAudioSampleRate{@link #ByteRTCAudioSampleRate}。
 */
@property(assign, nonatomic) ByteRTCAudioSampleRate sampleRate;
@end

/** 
 *  @type callback
 *  @brief 音频数据回调观察者
 */
@protocol ByteRTCAudioFrameObserver <NSObject>
/** 
 * @type callback
 * @region 音频数据回调
 * @brief 返回麦克风录制的音频数据
 * @param audioFrame 音频数据, 详见： ByteRTCAudioFrame{@link #ByteRTCAudioFrame}
 */
- (void)onRecordAudioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;
/** 
 * @type callback
 * @region 音频数据回调
 * @brief 返回订阅的所有远端用户混音后的音频数据。
 * @param audioFrame 音频数据, 详见： ByteRTCAudioFrame{@link #ByteRTCAudioFrame}
 */
- (void)onPlaybackAudioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;
/** 
 * @type callback
 * @region 音频数据回调
 * @brief 返回远端单个用户的音频数据
 * @param streamKey 远端流信息，参看 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}。
 * @param audioFrame 音频数据，参看 ByteRTCAudioFrame{@link #ByteRTCAudioFrame}。
 * @notes 此回调在播放线程调用。不要在此回调中做任何耗时的事情，否则可能会影响整个音频播放链路。
 */
- (void)onRemoteUserAudioFrame:(ByteRTCRemoteStreamKey * _Nonnull)streamKey
                    audioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;
/** 
 * @type callback
 * @region 音频数据回调
 * @brief 返回本地麦克风录制和订阅的所有远端用户混音后的音频数据
 * @param audioFrame 音频数据, 详见： ByteRTCAudioFrame{@link #ByteRTCAudioFrame}
 */
- (void)onMixedAudioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;
@end

/** 
 * @type callback
 * @region 音频处理
 * @brief 自定义音频处理器
 */
@protocol ByteRTCAudioProcessor <NSObject>
/** 
 * @type callback
 * @region 音频处理
 * @brief 获取 RTC SDK 采集得到的音频帧，并进行自定义处理，最终将处理后的音频帧给到 RTC SDK 用于编码传输。
 * @param audioFrame RTC SDK 采集到的音频帧，自定义处理可直接对音频 buffer 中的数据进行修改。参看 ByteRTCAudioFrame{@link #ByteRTCAudioFrame}。
 * @return  <br>
 *        0: 未处理  <br>
 *        >0: 处理成功  <br>
 *        < 0: 处理失败
 * @notes 在进行音频自定义处理前，你需要调用 `registerLocalAudioProcessor` 设置音频自定义处理器。
 */
- (int)processAudioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;
@end

/** 
 * @type callback
 * @brief 自定义音频处理器
 */
@protocol ByteRTCAudioFrameProcessor <NSObject>
/** 
* @type callback
* @brief 回调本地采集的音频帧地址，供自定义音频处理。
* @param audioFrame 音频帧地址，参看 ByteRTCAudioFrame{@link #ByteRTCAudioFrame}。
* @notes <br>
*        + 完成自定义音频处理后，SDK 会对处理后的音频帧进行编码，并传输到远端。<br>
*        + 调用 enableAudioProcessor:audioFormat:{@link #ByteRTCVideo#enableAudioProcessor:audioFormat:}，并在参数中选择本地采集的音频时，收到此回调。
*/
- (int)onProcessRecordAudioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;
/** 
* @type callback
* @brief 回调远端音频混音的音频帧地址，供自定义音频处理。
* @param audioFrame 音频帧地址，参看 ByteRTCAudioFrame{@link #ByteRTCAudioFrame}
* @notes 调用 `enableAudioProcessor`,并在参数中选择远端音频流的的混音音频时，收到此回调。
*/
- (int)onProcessPlayBackAudioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;
/** 
* @type callback
* @brief 回调单个远端用户的音频帧地址，供自定义音频处理。
* @param stream_info 音频流信息，参看 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
* @param audioFrame 音频帧地址，参看 ByteRTCAudioFrame{@link #ByteRTCAudioFrame}
* @notes 调用 `enableAudioProcessor`,并在参数中选择各个远端音频流时，收到此回调。
*/
- (int)onProcessRemoteUserAudioFrame:(ByteRTCRemoteStreamKey * _Nonnull)stream_info  audioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;


/** 
 * @hidden(macOS)
 * @type callback
 * @region 音频处理
 * @brief 软件耳返音频数据的回调。你可根据此回调自定义处理音频。
 * @param audioFrame 音频帧地址，参看 ByteRTCAudioFrame{@link #ByteRTCAudioFrame}。
 * @notes <br>
 *        + 此数据处理只影响耳返音频数据。<br>
 *        + 调用 enableAudioProcessor:audioFormat:{@link #ByteRTCVideo#enableAudioProcessor:audioFormat:} 把返回给音频处理器的音频类型设置为耳返音频后，你将收到此回调。
 */
- (int)onProcessEarMonitorAudioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;

/** 
 * @type callback
 * @brief 回调屏幕共享的音频帧地址，供自定义音频处理。
 * @param audioFrame 音频帧地址，参看 ByteRTCAudioFrame{@link #ByteRTCAudioFrame}。
 * @notes 调用 `enableAudioProcessor:`，把返回给音频处理器的音频类型设置为屏幕共享音频后，你将收到此回调。
 */
- (int)onProcessScreenAudioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;
@end

#pragma mark - AudioDeviceManager

/** 
 * @hidden for internal use only
 * @type callback
 * @region 音频管理
 * @brief 音频设备事件回调
 */
BYTERTC_APPLE_EXPORT @protocol ByteRTCAudioDeviceEventHandler<NSObject>
/** 
 * @type callback
 * @region 音频管理
 * @brief 获得麦克风音量
 * @param volume 音量大小
 */
- (void)onRecordingAudioVolumeIndication:(int)volume;
@end

/** 
 * @type api
 * @hidden(iOS)
 * @brief 音频设备管理类
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCAudioDeviceManager : NSObject
/**
 * @hidden
 * @type api
 */
- (instancetype _Nonnull )initDeviceManager:(id<ByteRTCAudioDeviceEventHandler> _Nonnull)handler;
/** 
 * @type api
 * @region 音频设备管理
 * @brief 获取当前系统内音频播放设备列表。你可以在收到 rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:} 了解设备变更后，重新调用本接口以获得新的设备列表。
 * @return 所有音频播放设备的列表，参看 ByteRTCDeviceCollection{@link #ByteRTCDeviceCollection}。
 */
- (ByteRTCDeviceCollection * _Nonnull)enumerateAudioPlaybackDevices;
/** 
 * @type api
 * @region 音频设备管理
 * @brief 获取音频采集设备列表。如果后续设备有变更，你需要重新调用本接口以获得新的设备列表。
 * @return 音频采集设备列表。详见 ByteRTCDeviceCollection{@link #ByteRTCDeviceCollection}。
 */
- (ByteRTCDeviceCollection * _Nonnull)enumerateAudioCaptureDevices;
/** 
 * @type api
 * @region 音频设备管理
 * @brief 设置音频采集路由是否跟随系统。
 * @param followed <br>
 *        + true: 跟随。此时，调用 setAudioCaptureDevice:{@link #ByteRTCAudioDeviceManager#setAudioCaptureDevice:} 会失败。默认值。
 *        + false: 不跟随系统。此时，可以调用 setAudioCaptureDevice:{@link #ByteRTCAudioDeviceManager#setAudioCaptureDevice:} 进行设置。
 */
- (void)followSystemCaptureDevice:(BOOL)followed;
/** 
 * @type api
 * @region 音频设备管理
 * @brief 设置音频播放路由是否跟随系统。
 * @param followed <br>
 *        + true: 跟随。此时，调用 setAudioPlaybackDevice:{@link #ByteRTCAudioDeviceManager#setAudioPlaybackDevice:} 会失败。默认值。
 *        + false: 不跟随系统。此时，可以调用 setAudioPlaybackDevice:{@link #ByteRTCAudioDeviceManager#setAudioPlaybackDevice:} 进行设置。
 */
- (void)followSystemPlaybackDevice:(BOOL)followed;
/** 
 * @type api
 * @region 音频设备管理
 * @brief 设置音频播放设备。
 * @param deviceID 音频播放设备 ID，可通过 enumerateAudioPlaybackDevices{@link #ByteRTCAudioDeviceManager#enumerateAudioPlaybackDevices} 获取。
 * @return   <br>
 *        + 0：方法调用成功  <br>
 *        + < 0：方法调用失败  <br>
 * @notes 当你调用 followSystemPlaybackDevice:{@link #ByteRTCAudioDeviceManager#followSystemPlaybackDevice:} 设置音频播放设备跟随系统后，将无法调用此接口设置音频播放设备。
 */
- (int)setAudioPlaybackDevice:(NSString * _Nonnull)deviceID;
/** 
 * @type api
 * @region 音频设备管理
 * @brief 获取当前音频播放设备。
 * @param deviceID 设备 ID
 * @return  方法调用结果  <br>
 *        + 0：方法调用成功  <br>
 *        + < 0：方法调用失败  <br>
 */
- (int)getAudioPlaybackDevice:(NSString * _Nonnull * _Nonnull) deviceID;
/** 
 * @type api
 * @region 音频设备管理
 * @brief 设置音频采集设备。
 * @param deviceID 音频采集设备 ID。你可调用 enumerateAudioCaptureDevices{@link #ByteRTCAudioDeviceManager#EnumerateAudioCaptureDevices} 获取可用设备列表。
 * @return  方法调用结果  <br>
 *        + 0：方法调用成功  <br>
 *        + < 0：方法调用失败  <br>
 * @notes 当你调用 followSystemCaptureDevice:{@link #ByteRTCAudioDeviceManager#followSystemCaptureDevice:} 设置音频采集设备跟随系统后，将无法调用此接口设置音频采集设备。
 */
- (int)setAudioCaptureDevice:(NSString * _Nonnull)deviceID;
/** 
 * @type api
 * @region 音频设备管理
 * @brief 获取当前音频采集设备。
 * @param deviceID 音频采集设备 ID。
 * @return  方法调用结果  <br>
 *        + 0：方法调用成功  <br>
 *        + < 0：方法调用失败  <br>
 */
- (int)getAudioCaptureDevice:(NSString *_Nonnull * _Nonnull) deviceID;
/** 
 * @type api
 * @region 音频设备管理
 * @brief 设置当前音频采集设备静音状态，默认为非静音。
 * @param mute  <br>
 *       + true：静音  <br>
 *       + false：非静音  <br>
 * @return  方法调用结果  <br>
 *        + 0：方法调用成功  <br>
 *        + < 0：方法调用失败  <br>
 */
- (int) setAudioCaptureDeviceMute:(bool)mute;
/** 
 * @type api
 * @region 音频设备管理
 * @brief 获取当前音频采集设备是否静音的信息。
 * @param mute  <br>
 *       + true：静音  <br>
 *       + false：非静音  <br>
 * @return  方法调用结果  <br>
 *        + 0：方法调用成功  <br>
 *        + < 0：方法调用失败  <br>
 */
- (int) getAudioCaptureDeviceMute:(bool * _Nonnull)mute;
/** 
 * @type api
 * @region 音频设备管理
 * @brief 设置当前音频播放设备静音状态，默认为非静音。
 * @param mute  <br>
 *       + true：静音  <br>
 *       + false：非静音  <br>
 * @return  方法调用结果  <br>
 *        + 0：方法调用成功  <br>
 *        + < 0：方法调用失败  <br>
 */
- (int) setAudioPlaybackDeviceMute:(bool)mute;
/** 
 * @type api
 * @region 音频设备管理
 * @brief 获取当前音频播放设备是否静音的信息。
 * @param mute  <br>
 *       + true：静音  <br>
 *       + false：非静音  <br>
 * @return  方法调用结果  <br>
 *        + 0：方法调用成功  <br>
 *        + < 0：方法调用失败  <br>
 */
- (int) getAudioPlaybackDeviceMute:(bool * _Nonnull)mute;
/** 
 * @type api
 * @region 音频设备管理
 * @brief 设置当前音频采集设备音量
 * @param volume 音频采集设备音量，取值范围为 [0,255]。
 *       + [0,25] 接近无声；  <br>
 *       + [25,75] 为低音量；  <br>
 *       + [76,204] 为中音量；  <br>
 *       + [205,255] 为高音量。  <br>
 * @return  方法调用结果  <br>
 *        + 0：方法调用成功  <br>
 *        + < 0：方法调用失败  <br>
 */
- (int) setAudioCaptureDeviceVolume:(unsigned int)volume;
/** 
 * @type api
 * @region 音频设备管理
 * @brief 获取当前音频采集设备音量
 * @param volume 音频采集设备音量，取值范围是 [0,255]
 *       + [0,25] 接近无声；  <br>
 *       + [25,75] 为低音量；  <br>
 *       + [76,204] 为中音量；  <br>
 *       + [205,255] 为高音量。  <br>
 * @return  方法调用结果  <br>
 *        + 0：方法调用成功  <br>
 *        + < 0：方法调用失败  <br>
 */
- (int) getAudioCaptureDeviceVolume:(unsigned int * _Nonnull)volume;
/** 
 * @type api
 * @region 音频设备管理
 * @brief 设置当前音频播放设备音量
 * @param volume 音频播放设备音量，取值范围为 [0,255]
 *       + [0,25] 接近无声；  <br>
 *       + [25,75] 为低音量；  <br>
 *       + [76,204] 为中音量；  <br>
 *       + [205,255] 为高音量。  <br>
 * @return  方法调用结果  <br>
 *        + 0：方法调用成功  <br>
 *        + < 0：方法调用失败  <br>
 */
- (int) setAudioPlaybackDeviceVolume:(unsigned int)volume;
/** 
 * @type api
 * @region 音频设备管理
 * @brief 获取当前音频播放设备音量
 * @param volume 音频播放设备音量，取值范围是 [0,255] <br>
 *       + [0,25] 接近无声；  <br>
 *       + [25,75] 为低音量；  <br>
 *       + [76,204] 为中音量；  <br>
 *       + [205,255] 为高音量。  <br>
 * @return  方法调用结果  <br>
 *        + 0：方法调用成功  <br>
 *        + < 0：方法调用失败  <br>
 */
- (int) getAudioPlaybackDeviceVolume:(unsigned int * _Nonnull)volume;
/** 
 * @type api
 * @region 音频设备管理
 * @brief 启动音频播放设备测试。  <br>
 *        该方法测试播放设备是否能正常工作。SDK 播放指定的音频文件，测试者如果能听到声音，说明播放设备能正常工作。
 * @param testAudioFilePath 音频文件的绝对路径，路径字符串使用 UTF-8 编码格式，支持以下音频格式: mp3，aac，m4a，3gp，wav。
 * @param interval 音频设备播放测试音量回调的间隔
 * @return  方法调用结果  <br>
 *        + 0：方法调用成功  <br>
 *        + < 0：方法调用失败  <br>
 * @notes  <br>
 *       + 该方法必须在进房前调用，且不可与其它音频设备测试功能同时应用。  <br>
 *       + 调用 stopAudioPlaybackDeviceTest{@link #ByteRTCAudioDeviceManager#stopAudioPlaybackDeviceTest} 停止测试。  <br>
 */
- (int)startAudioPlaybackDeviceTest:(NSString *_Nonnull)testAudioFilePath interval:(int)interval;
/** 
 * @type api
 * @region 音频设备管理
 * @brief 停止音频播放设备测试。
 * @return  方法调用结果  <br>
 *        + 0：方法调用成功  <br>
 *        + < 0：方法调用失败  <br>
 * @notes  调用 startAudioPlaybackDeviceTest:interval:{@link #ByteRTCAudioDeviceManager#startAudioPlaybackDeviceTest:interval:} 后，需调用本方法停止测试。
 */
- (int)stopAudioPlaybackDeviceTest;
/** 
 * @type api
 * @region 音频设备管理
 * @brief 开始音频采集设备和音频播放设备测试。<br>
 * @param interval 测试中会收到 `rtcEngine:onLocalAudioPropertiesReport:` 回调，本参数指定了该周期回调的时间间隔，单位为毫秒。建议设置到大于 200 毫秒。最小不得少于 10 毫秒。
 * @return  方法调用结果  <br>
 *       + 0：方法调用成功  <br>
 *       + < 0：方法调用失败  <br>
 * @notes  <br>
 *       + 该方法在进房前后均可调用。且不可与其它音频设备测试功能同时应用。  <br>
 *       + 调用本接口 30 s 后，采集自动停止，并开始播放采集到的声音。录音播放完毕后，设备测试流程自动结束。你也可以在 30 s 内调用 stopAudioDeviceRecordAndPlayTest{@link #ByteRTCAudioDeviceManager#stopAudioDeviceRecordAndPlayTest}  来停止采集并开始播放此前采集到的声音。<br>
 *       + 调用 stopAudioDevicePlayTest{@link #ByteRTCAudioDeviceManager#stopAudioDevicePlayTest} 可以停止音频设备采集和播放测试。<br>
 *       + 你不应在测试过程中，调用 `enableAudioPropertiesReport:` 注册音量提示回调。
 *       + 该方法仅在本地进行音频设备测试，不涉及网络连接。  <br>
 */
- (int)startAudioDeviceRecordTest:(int)interval;
/** 
 * @type api
 * @region 音频设备管理
 * @brief 停止采集本地音频，并开始播放采集到的声音。录音播放完毕后，设备测试流程结束。<br>
 * 调用 startAudioDeviceRecordTest:{@link #ByteRTCAudioDeviceManager#startAudioDeviceRecordTest:} 30s 内调用本接口来停止采集并开始播放此前采集到的声音。
 * @return  方法调用结果  <br>
 *        + 0：方法调用成功  <br>
 *        + < 0：方法调用失败  <br>
 * @notes  <br>
 *        + 该方法依赖 rtc 引擎，只有通过成员方法getAudioDeviceManager{@link #ByteRTCVideo#getAudioDeviceManager}创建的ByteRTCAudioDeviceManager，该方法才是有效的 <br>
 *        + 调用本接口开始播放录音后，可以在播放过程中调用 stopAudioDevicePlayTest{@link #ByteRTCAudioDeviceManager#stopAudioDevicePlayTest} 停止播放。
 */
- (int)stopAudioDeviceRecordAndPlayTest;
/** 
 * @type api
 * @region 音频设备管理
 * @brief 停止由调用 startAudioDeviceRecordTest:{@link #ByteRTCAudioDeviceManager#startAudioDeviceRecordTest:} 开始的音频播放设备测试。<br>
 *        在音频播放设备测试自动结束前，可调用本接口停止音频采集与播放测试。
 * @return  方法调用结果  <br>
 *        + 0：方法调用成功  <br>
 *        + < 0：方法调用失败
 * @notes  <br>
 *        + 该方法依赖 rtc 引擎，只有通过成员方法getAudioDeviceManager{@link #ByteRTCVideo#getAudioDeviceManager}创建的ByteRTCAudioDeviceManager，该方法才是有效的 <br>
 */
- (int)stopAudioDevicePlayTest;
/** 
 * @type api
 * @region 音频设备管理
 * @brief 尝试初始化音频播放设备，以检测设备不存在、权限被拒绝/禁用等异常问题。
 * @param deviceID 设备索引号
 * @return 设备状态错误码 <br>
 *        + 0: 设备检测结果正常 <br>
 *        + -1: 接口调用失败 <br>
 *        + -2: 设备无权限，尝试初始化设备失败 <br>
 *        + -3: 设备不存在，当前没有设备或设备被移除时返回 <br>
 *        + -4: 设备音频格式不支持 <br>
 *        + -5: 其它原因错误 <br>
 * @notes  <br>
 *        + 该接口需在进房前调用；  <br>
 *        + 检测成功不代表设备一定可以启动成功，还可能因设备被其他应用进程独占，或 CPU/内存不足等原因导致启动失败。 <br>
 */
- (int)initAudioPlaybackDeviceForTest:(NSString * _Nonnull)deviceID;
/** 
 * @type api
 * @region 音频设备管理
 * @brief 尝试初始化音频采集设备，以检测设备不存在、权限被拒绝/禁用等异常问题。
 * @param deviceID 设备索引号
 * @return 设备状态错误码 <br>
 *        + 0: 设备检测结果正常 <br>
 *        + -1: 接口调用失败 <br>
 *        + -2: 设备无权限，尝试初始化设备失败 <br>
 *        + -3: 设备不存在，当前没有设备或设备被移除时返回 <br>
 *        + -4: 设备音频格式不支持 <br>
 *        + -5: 其它原因错误 <br>
 * @notes  <br>
 *        + 该接口需在进房前调用；  <br>
 *        + 检测成功不代表设备一定可以启动成功，还可能因设备被其他应用进程独占，或 CPU/内存不足等原因导致启动失败。 <br>
 */
- (int)initAudioCaptureDeviceForTest:(NSString * _Nonnull)deviceID;
/** 
 * @type api
 * @deprecated since 3.45 and will be deleted in 3.51.
 * @region 音频设备管理
 * @brief 切换音频播放到扬声器或者听筒，默认播放设备是扬声器
 * @param enable  <br>
 *       + true：切换至扬声器  <br>
 *       + false：切换至听筒  <br>
 * @notes 本方法只在移动设备上有效
 */
- (void)setEnableSpeakerphone:(bool)enable;

/** 
 * @type api
 * @region 音频设备管理
 * @brief 启动音频采集设备测试。  <br>
 *        该方法测试音频采集设备是否能正常工作。启动测试后，会收到 rtcEngine:onLocalAudioPropertiesReport:{@link #ByteRTCVideoDelegate#rtcEngine:onLocalAudioPropertiesReport:} 回调上报的音量信息。
 * @param indicationInterval 获取回调的时间间隔，单位为毫秒。建议设置到大于 200 毫秒。最小不得少于 10 毫秒。小于10 毫秒行为未定义。
 * @return  方法调用结果  <br>
 *        + 0：方法调用成功  <br>
 *        + < 0：方法调用失败  <br>
 * @notes  <br>
 *       + 该方法不依赖 rtc 引擎 <br>
 *       + 该方法必须在进房前调用，且不可与其它音频设备测试功能同时应用。  <br>
 *       + 你需调用 stopAudioRecordingDeviceTest{@link #ByteRTCAudioDeviceManager#stopAudioRecordingDeviceTest} 停止测试。  <br>
 */
- (int)startAudioRecordingDeviceTest:(unsigned int)indicationInterval;
/** 
 * @type api
 * @region 音频设备管理
 * @brief 停止音频采集设备测试。
 * @return  方法调用结果  <br>
 *        + 0：方法调用成功  <br>
 *        + < 0：方法调用失败  <br>
 * @notes  <br>
 *        + 该方法不依赖 rtc 引擎 <br>
 *        + 调用 startAudioRecordingDeviceTest:{@link #ByteRTCAudioDeviceManager#startAudioRecordingDeviceTest:} 后，需调用本方法停止测试。 <br>
 */
- (int)stopAudioRecordingDeviceTest;
/** 
 * @type api
 * @region 音频设备管理
 * @brief 开始音频设备回路测试。  <br>
 *        该方法测试音频采集设备和音频播放设备是否能正常工作。一旦测试开始，音频采集设备会采集本地声音并通过音频播放设备播放出来，同时会收到 rtcEngine:onLocalAudioPropertiesReport:{@link #ByteRTCVideoDelegate#rtcEngine:onLocalAudioPropertiesReport:}。
 * @param indicationInterval 收到回调的时间间隔，单位为 ms。建议设置到大于 200 ms。最小不得少于 10 ms。
 * @return  方法调用结果  <br>
 *        + 0：方法调用成功  <br>
 *        + < 0：方法调用失败  <br>
 * @notes  <br>
 *       + 该方法不依赖 rtc 引擎 <br>
 *       + 该方法必须在进房前调用。且不可与其它音频设备测试功能同时应用。  <br>
 *       + 你需调用 stopAudioDeviceLoopbackTest{@link #ByteRTCAudioDeviceManager#stopAudioDeviceLoopbackTest} 停止测试。  <br>
 *       + 该方法仅在本地进行音频设备测试，不涉及网络连接。  <br>
 */
- (int)startAudioDeviceLoopbackTest:(unsigned int)indicationInterval;
/** 
 * @type api
 * @region 音频设备管理
 * @brief 停止音频设备回路测试。
 * @return  方法调用结果  <br>
 *        + 0：方法调用成功  <br>
 *        + < 0：方法调用失败  <br>
 * @notes   <br>
 *        + 该方法不依赖 rtc 引擎 <br>
 *        + 调用 startAudioDeviceLoopbackTest:{@link #ByteRTCAudioDeviceManager#startAudioDeviceLoopbackTest:} 后，需调用本方法停止测试。<br>
 */
- (int)stopAudioDeviceLoopbackTest;
@end

/** 
 * @type keytype
 * @brief 使用自动语音识别服务所需校验信息
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCASRConfig : NSObject
/** 
 *  @brief 应用 ID
 */
@property(copy, nonatomic) NSString *_Nonnull appId;
/** 
 *  @brief 用户 ID
 */
@property(copy, nonatomic) NSString *_Nonnull userId;
/** 
 *  @brief 访问令牌
 */
@property(copy, nonatomic) NSString *_Nonnull accessToken;
/** 
 *  @brief 私钥。Signature 鉴权模式下不能为空，token 鉴权模式下为空。参看[关于鉴权](https://www.volcengine.com/docs/6561/107789)
 */
@property(copy, nonatomic) NSString *_Nonnull secretKey;
/** 
 *  @brief 场景信息，参看[业务集群](https://www.volcengine.com/docs/6561/80818#_3-2-2-%E5%8F%91%E9%80%81-full-client-request)
 */
@property(copy, nonatomic) NSString *_Nonnull cluster;
/** 
 *  @brief 鉴权模式，参看 ByteRTCASRAuthorizationType{@link #ByteRTCASRAuthorizationType}
 */
@property(assign, nonatomic) ByteRTCASRAuthorizationType authorizationType;
@end

#pragma mark - ByteASREventHandler

/** 
 * @hidden(macOS)
 * @type callback
 * @brief 语音识别服务使用状态回调
 */
BYTERTC_APPLE_EXPORT @protocol ByteRTCASREngineEventHandler<NSObject>
@required
/** 
 * @type callback
 * @brief 语音识别服务开启成功回调
 */
- (void)onSuccess;
@required
/** 
 * @type callback
 * @brief 语音转文字成功回调，该回调返回识别后的全量消息。
 * @param message 识别完成后得到的文字消息
 * @notes 若识别过程中发生了网络连接中断，则重连后回调的信息中只包含重连后识别的文字消息，不再包含上一次连接后识别的消息。
 */
- (void)onMessage:(NSString *_Nonnull)message;
@required
/** 
 * @type callback
 * @brief 当语音识别服务内部发生错误事件时触发该回调。
 * @param errorCode 错误码  <br>
 *        + < 0: 参数错误或 API 调用顺序错误，参看 ByteRTCASRErrorCode{@link #ByteRTCASRErrorCode}；  <br>
 *        + >0: 参看 [语音识别服务错误码](https://www.volcengine.com/docs/6561/80818#_3-3-%E9%94%99%E8%AF%AF%E7%A0%81)
 * @param errorMessage 错误原因说明
 */
- (void)onError:(NSInteger)errorCode withErrorMessage:(NSString *_Nonnull)errorMessage;
@end

/** 
 * @type keytype
 * @brief 混音配置
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCAudioMixingConfig : NSObject
/** 
 * @brief 混音播放类型，详见 ByteRTCAudioMixingType{@link #ByteRTCAudioMixingType}
 */
@property(assign, nonatomic) ByteRTCAudioMixingType type;
/** 
 * @brief 混音播放次数
 *       + play_count <= 0: 无限循环  <br>
 *       + play_count == 1: 播放一次（默认）  <br>
 *       + play_count > 1: 播放 play_count 次
 */
@property(assign, nonatomic) NSInteger playCount;
/** 
 * @brief 混音时音频文件播放进度条位置，参数为整数，单位为毫秒
 */
@property(assign, nonatomic) NSInteger position;
/** 
 * @brief 设置音频文件播放进度回调的时间间隔，参数为为大于 0 的 10 的倍数，单位为毫秒，设置后 SDK 将按照设置的值触发 `rtcEngine:onAudioMixingPlayingProgress:progress:` 回调，默认不回调。  <br>
 *        + 当传入的值不能被 10 整除时，则默认向上取整 10，如设为 52ms 时会默认调整为 60ms。  <br>
 *        + 当传入的值小于等于 0 时，不会触发进度回调。  <br>
 */
@property(assign, nonatomic) NSInteger callbackOnProgressInterval;
/** 
 * @brief 在采集音频数据时，附带本地混音文件播放进度的时间戳。启用此功能会提升远端人声和音频文件混音播放时的同步效果。
 * @notes <br>
 *        + 仅在单个音频文件混音时使用有效。<br>
 *        + `true` 时开启此功能，`false` 时关闭此功能，默认为关闭。
 */
@property(assign, nonatomic) BOOL syncProgressToRecordFrame;
@end

/** 
 * @type keytype
 * @brief 音频属性信息提示的相关配置。
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCAudioPropertiesConfig : NSObject
/** 
 * @brief 信息提示间隔，单位：ms <br>
 *       + `<= 0`: 关闭信息提示  <br>
 *       + `(0,100]`: 开启信息提示，不合法的 interval 值，SDK 自动设置为 100ms  <br>
 *       + `> 100`: 开启信息提示，并将信息提示间隔设置为此值  <br>
 */
@property(assign, nonatomic) NSInteger interval;
/** 
 * @brief 是否开启音频频谱检测。
 */
@property(assign, nonatomic) BOOL enable_spectrum;
/** 
 * @brief 是否开启人声检测 (VAD)。
 */
@property(assign, nonatomic) BOOL enable_vad;
/** 
 * @brief 音量回调模式。详见 ByteRTCAudioReportMode{@link #ByteRTCAudioReportMode}。
 */
@property(assign, nonatomic) ByteRTCAudioReportMode local_main_report_mode;
/** 
 * @brief 适用于音频属性信息提示的平滑系数。取值范围是 `(0.0, 1.0]`。<br>
 *        默认值为 `1.0`，不开启平滑效果；值越小，提示音量平滑效果越明显。如果要开启平滑效果，可以设置为 `0.3`。
 */
@property(nonatomic, assign) float smooth;

/** 
 * @type keytype
 * @brief 设置 `rtcEngine:onLocalAudioPropertiesReport:` 回调中是否包含本地混音音频数据。参看 ByteRTCAudioPropertiesMode{@link #ByteRTCAudioPropertiesMode}。<br>
 *        默认仅包含本地麦克风采集的音频数据和本地屏幕音频采集数据。
 */
@property(assign, nonatomic) ByteRTCAudioPropertiesMode audio_report_mode;
@end

/** 
 * @type keytype
 * @brief 音频属性信息  <br>
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCAudioPropertiesInfo : NSObject
/** 
 * @brief 线性音量，与原始音量呈线性关系，数值越大，音量越大。取值范围是：[0,255]。<br>
 *        - [0, 25]: 无声 <br>
 *        - [26, 75]: 低音量 <br>
 *        - [76, 204]: 中音量 <br>
 *        - [205, 255]: 高音量 <br>
 */
@property(assign, nonatomic) NSInteger linearVolume;
/** 
 * @brief 非线性音量。由原始音量的对数值转化而来，因此在中低音量时更灵敏，可以用作 Active Speaker（房间内最活跃用户）的识别。取值范围是：[-127，0]，单位 dB。 <br>
 *        - [-127, -60]: 无声 <br>
 *        - [-59, -40]: 低音量 <br>
 *        - [-39, -20]: 中音量 <br>
 *        - [-19, 0]: 高音量 <br>
 */
@property(assign, nonatomic) NSInteger nonlinearVolume;
/** 
 * @brief 人声检测（VAD）结果
 *        + 1: 检测到人声。<br>
 *        + 0: 未检测到人声。<br>
 *        + -1: 未开启 VAD。<br>
 */
@property(assign, nonatomic) NSInteger vad;
/** 
 * @brief 频谱数组。默认长度为 257。
 */
@property(copy, nonatomic) NSArray<NSNumber*> * _Nonnull spectrum;
@end

/** 
 * @type keytype
 * @brief 本地音频属性信息
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCLocalAudioPropertiesInfo : NSObject

/** 
 * @brief 流属性，包括主流、屏幕流。参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 */
@property(assign, nonatomic) ByteRTCStreamIndex streamIndex;
/** 
 * @type keytype
 * @brief 音频属性信息，详见 ByteRTCAudioPropertiesInfo{@link #ByteRTCAudioPropertiesInfo}
 */
@property(strong, nonatomic) ByteRTCAudioPropertiesInfo *_Nonnull audioPropertiesInfo;
@end

/** 
 * @type keytype
 * @brief 远端音频属性信息
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCRemoteAudioPropertiesInfo : NSObject
/** 
 * @type keytype
 * @brief 远端流信息，详见 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
 */
@property(strong, nonatomic) ByteRTCRemoteStreamKey *_Nonnull streamKey;
/** 
 * @type keytype
 * @brief 音频属性信息，详见 ByteRTCAudioPropertiesInfo{@link #ByteRTCAudioPropertiesInfo}
 */
@property(strong, nonatomic) ByteRTCAudioPropertiesInfo *_Nonnull audioPropertiesInfo;
@end

/** 
 * @type keytype
 * @brief 本地用户在房间内的位置坐标，需自行建立空间直角坐标系
 */
BYTERTC_APPLE_EXPORT @interface Position : NSObject
/** 
 * @brief x 坐标
 */
@property(nonatomic, assign) float x;
/** 
 * @brief y 坐标
 */
@property(nonatomic, assign) float y;
/** 
 * @brief z 坐标
 */
@property(nonatomic, assign) float z;
@end

/** 
 * @type keytype
 * @brief 方向朝向信息
 */
BYTERTC_APPLE_EXPORT @interface Orientation : NSObject
/** 
 * @brief x 坐标
 */
@property(nonatomic, assign) float x;
/** 
 * @brief y 坐标
 */
@property(nonatomic, assign) float y;
/** 
 * @brief z 坐标
 */
@property(nonatomic, assign) float z;
@end

/** 
 * @type keytype
 * @brief 三维朝向信息，三个向量需要两两垂直。参看 Orientation{@link #Orientation}。
 */
BYTERTC_APPLE_EXPORT @interface HumanOrientation : NSObject
/** 
 * @brief 正前方朝向，默认值为 {1,0,0}，即正前方朝向 x 轴正方向
 */
@property(nonatomic, strong) Orientation* _Nonnull forward;
/** 
 * @brief 正右方朝向，默认值为 {0,1,0}，即右手朝向 y 轴正方向
 */
@property(nonatomic, strong) Orientation* _Nonnull right;
/** 
 * @brief 正上方朝向，默认值为 {0,0,1}，即头顶朝向 z 轴正方向
 */
@property(nonatomic, strong) Orientation* _Nonnull up;
@end

/** 
 * @type keytype
 * @brief K 歌打分维度。
 */
typedef NS_ENUM(NSInteger, ByteRTCMulDimSingScoringMode) {
    /** 
     * @brief 按照音高进行评分。
     */
    ByteRTCMulDimSingScoringModeNote = 0
};
/** 
 * @type keytype
 * @brief 远端音频流精准对齐模式
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioAlignmentMode) {
    /** 
     * @brief 不对齐
     */
    ByteRTCAudioAlignmentModeOff = 0,
    /** 
     * @brief 远端音频流都对齐伴奏进度同步播放
     */
    ByteRTCAudioAlignmentModeAudioMixing = 1,
};

/** 
 * @type keytype
 * @brief 实时评分信息。
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCSingScoringRealtimeInfo : NSObject
 /** 
  * @brief 当前的播放进度。
  */
 @property(nonatomic, assign) int currentPosition;
 /** 
  * @brief 演唱者的音高。
  */
 @property(nonatomic, assign) int userPitch;
 /** 
  * @brief 标准音高。
  */
 @property(nonatomic, assign) int standardPitch;
 /** 
  * @brief 歌词分句索引。
  */
 @property(nonatomic, assign) int sentenceIndex;
 /** 
  * @brief 上一句歌词的评分。
  */
 @property(nonatomic, assign) int sentenceScore;
 /** 
  * @brief 当前演唱的累计分数。
  */
 @property(nonatomic, assign) int totalScore;
 /** 
  * @brief 当前演唱的平均分数。
  */
 @property(nonatomic, assign) int averageScore;
@end

/** 
 * @type keytype
 * @brief 标准音高数据组。
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCStandardPitchInfo : NSObject
 /** 
  * @brief 开始时间，单位 ms。
  */
 @property(nonatomic, assign) int startTime;
 /** 
  * @brief 持续时间，单位 ms。
  */
 @property(nonatomic, assign) int duration;
 /** 
  * @brief 音高。
  */
 @property(nonatomic, assign) int pitch;
@end

/** 
 * @type keytype
 * @brief K 歌评分配置。
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCSingScoringConfig : NSObject
 /** 
  * @brief 打分维度，详见 ByteRTCMulDimSingScoringMode{@link #ByteRTCMulDimSingScoringMode}。
  */
 @property(nonatomic, assign) ByteRTCMulDimSingScoringMode mode;
 /** 
  * @brief 音频采样率。仅支持 44100 Hz、48000 Hz。
  */
 @property(nonatomic, assign) ByteRTCAudioSampleRate sampleRate;
 /** 
  * @brief 歌词文件路径。打分功能仅支持 KRC 歌词文件。
  */
 @property(nonatomic, copy) NSString *_Nonnull lyricsFilepath;
 /** 
  * @brief 歌曲 midi 文件路径。
  */
 @property(nonatomic, copy) NSString *_Nonnull midiFilepath;
@end

/** 
 * @type keytype
 * @brief 音频文件录制内容来源。
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioFrameSource) {
    /** 
     * @brief 本地麦克风采集的音频数据。
     */
    ByteRTCAudioFrameSourceTypeMic = 0,
    /** 
     * @brief 远端所有用户混音后的数据
     */
    /**
     * {en}
     * @brief The audio got by mixing all remote user's audio.
     */
    ByteRTCAudioFrameSourceTypePlayback = 1,
    /** 
     * @brief 本地麦克风和所有远端用户音频流的混音后的数据
     */
    ByteRTCAudioFrameSourceTypeMixed = 2,
};
/** 
 * @type keytype
 * @brief 音频质量
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioQuality) {
    /** 
     * @brief 低音质
     */
    ByteRTCAudioQualityLow = 0,
    /** 
     * @brief 中音质
     */
    ByteRTCAudioQualityMedium = 1,
    /** 
     * @brief 高音质
     */
    ByteRTCAudioQualityHigh = 2,
    /** 
     * @brief 超高音质
     */
    ByteRTCAudioQualityUltraHigh = 3,
};
/** 
 * @type keytype
 * @brief 音频录制配置
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCAudioRecordingConfig : NSObject
/** 
 * @brief 录制文件路径。一个有读写权限的绝对路径，包含文件名和文件后缀。
 * @notes 录制文件的格式仅支持 .aac 和 .wav。
 */
@property(nonatomic, copy) NSString* _Nonnull absoluteFileName;
/** 
 * @brief 录音内容来源，参看 ByteRTCAudioFrameSource{@link #ByteRTCAudioFrameSource}。
 */
@property(nonatomic, assign) ByteRTCAudioFrameSource frameSource;
/** 
 * @brief 录音采样率。参看 ByteRTCAudioSampleRate{@link #ByteRTCAudioSampleRate}。
 */
@property(nonatomic, assign) ByteRTCAudioSampleRate sampleRate;
/** 
 * @brief 录音音频声道。参看 ByteRTCAudioChannel{@link #ByteRTCAudioChannel}。
 * @notes 如果录制时设置的的音频声道数与采集时的音频声道数不同：<br>
 *        + 如果采集的声道数为 1，录制的声道数为 2，那么，录制的音频为经过单声道数据拷贝后的双声道数据，而不是立体声。<br>
 *        + 如果采集的声道数为 2，录制的声道数为 1，那么，录制的音频为经过双声道数据混合后的单声道数据。
 */
@property(nonatomic, assign) ByteRTCAudioChannel channel;
/** 
 * @brief 录音音质。仅在录制文件格式为 .aac 时可以设置。参看 ByteRTCAudioQuality{@link #ByteRTCAudioQuality}。
 * @notes 采样率为 32kHz 时，不同音质录制文件（时长为 10min）的大小分别是： <br>
 *        + 低音质：1.2MB；<br>
 *        + 中音质：2MB；<br>
 *        + 高音质：3.75MB；<br>
 *        + 超高音质：7.5MB。
 */
@property(nonatomic, assign) ByteRTCAudioQuality quality;
@end

/** 
 * @type keytype
 * @brief 录音配置
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioRecordingState) {
    /** 
     * @brief 录制异常
     */
    ByteRTCAudioRecordingStateError = 0,
    /** 
     * @brief 录制进行中
     */
    ByteRTCAudioRecordingStateProcessing = 1,
    /** 
     * @brief 已结束录制，并且录制文件保存成功。
     */
    ByteRTCAudioRecordingStateSuccess = 2,
};
/** 
 * @type errorcode
 * @brief 音频文件录制的错误码
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioRecordingErrorCode) {
    /** 
     * @brief 录制正常
     */
    ByteRTCAudioRecordingErrorCodeOk = 0,
    /** 
     * @brief 没有文件写权限
     */
    ByteRTCAudioRecordingErrorCodeNoPermission = -1,
    /** 
     * @brief 没有进入房间
     */
    ByteRTCAudioRecordingErrorNotInRoom = -2,
    /** 
     * @brief 录制已经开始
     */
    ByteRTCAudioRecordingAlreadyStarted = -3,
    /** 
     * @brief 录制还未开始
     */
    ByteRTCAudioRecordingNotStarted = -4,
        /** 
     * @brief 录制失败。文件格式不支持。
     */
    ByteRTCAudioRecordingErrorCodeNotSupport = -5,
    /** 
     * @brief 其他异常
     */
    ByteRTCAudioRecordingErrorCodeOther = -6,
};
