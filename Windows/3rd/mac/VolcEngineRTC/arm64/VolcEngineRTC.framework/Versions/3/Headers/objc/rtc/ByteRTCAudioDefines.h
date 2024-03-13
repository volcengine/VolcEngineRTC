/*
 * Copyright (c) 2022 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief Objective-C VolcEngineRTC Audio Defines
*/

#import "ByteRTCMediaDefines.h"

/**
 * @locale zh
 * @type keytype
 * @brief 音频场景类型。<br>
 *        选择音频场景后，SDK 会自动根据客户端音频采集播放设备和状态，适用通话音量/媒体音量。<br>
 *        如果以下音频场景类型无法满足你的业务需要，请联系技术支持人员。
 */
/**
 * @locale en
 * @type keytype
 * @brief  Audio scenarios   <br>
 *        After selecting the audio scenario, SDK will automatically select the call/media volume, according to the client-side audio device and status. <br>
 *        If the following audio scenarios cannot meet your business needs, please contact our technical support team for customization.
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioScenarioType) {
    /**
     * @locale zh
     * @brief （默认）音乐场景。<br>
     *        此场景适用于对音乐表现力有要求的场景，如音乐直播等。<br>
     *        注意：在此场景下，使用内置扬声器/听筒时，开关麦可能发生音量突变。<br>
     *        不同音频设备，开麦和闭麦状态下的使用的音量类型：<br>
     *        <table>
     *           <tr><th></th><th>闭麦</th><th>开麦</th></tr>
     *           <tr><td>内置扬声器</td><td>媒体音量</td><td>通话音量</td></tr>
     *           <tr><td>内置听筒</td><td>媒体音量</td><td>通话音量</td></tr>
     *           <tr><td>有线耳机/ USB 耳机/ 外置声卡</td><td>媒体音量</td><td>媒体音量</td></tr>
     *           <tr><td>蓝牙耳机</td><td>媒体音量</td><td>媒体音量</td></tr>
     *        </table>
     */
    /**
     * @locale en
     * @brief (Default) Music scenario.<br>
     *        This scenario is suitable for scenes that require musical expression, such as music live.<br>
     *         For different audio device and status, the selected volume type is as follows:<br>
     *         <table>
     *            <tr><th></th><th>Mic Off</th><th>Mic On</th><th>Remarks</th><tr>
     *            <tr><td>Build-in microphone and speaker</td><td>Media volume</td><td>Call volume</td><td>/</td></tr>
     *            <tr><td>Earpiece</td><td>Media volume</td><td>Call volume</td><td>/</td></tr>
     *            <tr><td>Wired headset/ USB headset/ external sound card</td><td>Media volume</td><td> Media Volume</td><td>/</td></tr>
     *            <tr><td>Bluetooth Headset</td><td>Media Volume</td><td>Media Volume</td><td>Even if the Bluetooth headset has a microphone, you can only use the build-in microphone for local audio capture.</td></tr>
     *         </table>
     */
    ByteRTCAudioScenarioMusic = 0,
    /**
     * @locale zh
     * @brief 高质量通话场景。兼顾外放/蓝牙耳机时的音频体验。<br>
     *        注意：在此场景下，使用内置扬声器/听筒时，开关麦可能发生音量突变。使用 `ByteRTCAudioScenarioHighqualityChat` 可以避免此种情况。<br>
     *        不同音频设备，开麦和闭麦状态下的使用的音量类型：<br>
     *        <table>
     *           <tr><th></th><th>闭麦</th><th>开麦</th></tr>
     *           <tr><td>内置扬声器</td><td>媒体音量</td><td>通话音量</td></tr>
     *           <tr><td>内置听筒</td><td>媒体音量</td><td>通话音量</td></tr>
     *           <tr><td>有线耳机/ USB 耳机/ 外置声卡</td><td>媒体音量</td><td>媒体音量</td></tr>
     *           <tr><td>蓝牙耳机</td><td>通话音量</td><td>通话音量</td></tr>
     *        </table>
     */
    /**
     * @locale en
     * @brief High-quality communication scenario <br>
     *        This scenario is suitable for scenes that require musical expression, but also want to use the microphone on the bluetooth headphones for audio capturing. <br>
     *        Media volume is perferred in this scenario. The preference may introduce switch of volume type when you switch on/off the microphone. To avoid the switch, use `ByteRTCAudioScenarioHighqualityChat`. <br>
     *        This scenario can provide decent audio performance using the speaker/bluetooth earphones. It can also avoid sudden changes of volume type when switching to bluetooth earphones. <br>
     *        For different audio device and status, the selected volume type is as follows:<br>
     *         <table>
     *            <tr><th></th><th>Mic Off</th><th>Mic On</th><th>Remarks</th><tr>
     *            <tr><td>Build-in microphone and speaker</td><td> Media volume </td><td> call volume </td><td>/</td></tr>
     *            <tr><td>Earpiece</td><td> Media volume </td><td> call volume </td><td>/</td></tr>
     *            <tr><td>Wired headset/ USB headset/ external sound card</td><td> Media volume </td><td> Media Volume </td><td>/</td></tr>
     *            <tr><td>Bluetooth Headset </td><td> Call Volume </td><td> Call Volume </td><td> Ability to use the microphone included in the Bluetooth headset for audio capture. </td></tr>
     *         </table>
     */
    ByteRTCAudioScenarioHighqualityCommunication = 1,
    /**
     * @locale zh
     * @brief 纯通话音量场景。<br>
     *        可以最大程度地消除回声，使通话清晰度达到最优。全程使用通话音量，不会有音量突变的听感。<br>
     *        适用于需要频繁上下麦的通话或会议场景。<br>
     *        但是，会压低使用媒体音量进行播放的其他音频的音量，且音质会变差。
     */
    /**
     * @locale en
     * @brief  Call volume scenario.<br>
     *         This scenario uses the call volume regardless of the client-side audio device or status.<br>
     *         This scenario is suitable for calls or meetings that require turning on and off the microphone frequently.<br>
     *         Call volume is used the whole time and there will not be sudden changes in volume.<br>
     *         This scenario maximizes the elimination of echoes and has optimal call clarity.<br>
     *         You can use the microphone on the bluetooth earphones for audio capturing.<br>
     *         However, the volume of other audio played using media volume will be lowered, and the audio quality is worse.
     */
    ByteRTCAudioScenarioCommunication = 2,
    /**
     * @locale zh
     * @brief 纯媒体场景。<br>
     *        全程使用媒体音量，不会有音量突变的听感。<br>
     *        外放通话时，可能出现回声和啸叫，请联系技术支持人员。
     */
    /**
     * @locale en
     * @brief Media volume scenario.<br>
     *        This scenario uses the media volume regardless of the client-side audio device or status.<br>
     *        If the audio quality is unsatisfactory when you put on speaker, please contact our technical support team.
     */
    ByteRTCAudioScenarioMedia = 3,
    /**
     * @locale zh
     * @brief 游戏媒体场景。<br>
     *        若外放通话且无游戏音效消除优化时音质不理想，请联系技术支持人员。<br>
     *        不同音频设备，开麦和闭麦状态下的使用的音量类型：<br>
     *        <table>
     *           <tr><th></th><th>不采集音频</th><th>采集音频</th><th>备注</th></tr>
     *           <tr><td>设备自带麦克风和扬声器</td><td>媒体音量</td><td>媒体音量</td><td>/</td></tr>
     *           <tr><td>听筒</td><td>媒体音量</td><td>媒体音量</td><td>/</td></tr>
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
     *            <tr><td>Build-in microphone and speaker</td><td> Media volume </td><td> Media volume </td><td>/</td></tr>
     *            <tr><td>Earpiece</td><td> Media volume </td><td> Media volume </td><td>/</td></tr>
     *            <tr><td>Wired headset/ USB headset/ external sound card</td><td> Media volume </td><td> Media Volume </td><td>/</td></tr>
     *            <tr><td> Bluetooth Headset </td><td> Call Volume </td><td> Call Volume </td><td> Ability to use the microphone included in the Bluetooth headset for audio capture. </td></tr>
     *         </table>
     */
    ByteRTCAudioScenarioGameStreaming = 4,
    /**
     * @locale zh
     * @brief 高质量畅聊场景。  <br>
     *        此场景和 `ByteRTCAudioScenarioHighqualityCommunication` 高度类似，唯一的差异在于：此场景下，在使用设备自带的麦克风和扬声器/听筒进行通话时，开关麦始终采用通话音量，不会引起音量类型突变。 <br>
     *        不同音频设备，开麦和闭麦状态下的使用的音量类型：<br>
     *        <table>
     *           <tr><th></th><th>闭麦</th><th>开麦</th></tr>
     *           <tr><td>内置扬声器</td><td>通话音量</td><td>通话音量</td></tr>
     *           <tr><td>听筒</td><td>通话音量</td><td>通话音量</td></tr>
     *           <tr><td>有线耳机/ USB 耳机/ 外置声卡</td><td>媒体音量</td><td>媒体音量</td></tr>
     *           <tr><td>蓝牙耳机</td><td>通话音量</td><td>通话音量</td></tr>
     *        </table>
     */
    /**
     * @locale en
     * @brief High-quality chatting scenario <br>
     *        This scenario is the same as `ByteRTCAudioScenarioHighqualityCommunication`, but in one case: in this scenario, switching on/off the microphone does not change the volume type. When you talk with the built-in microphone and speaker/earpiece, the call volume is used all the time. <br>
     *        For different audio device and status, the selected volume type is as follows:<br>
     *         <table>
     *            <tr><th></th><th>Mic Off</th><th>Mic On</th><th>Remarks</th><tr>
     *            <tr><td>Build-in microphone and speaker</td><td> Call volume </td><td> call volume </td><td>/</td></tr>
     *            <tr><td>Earpiece</td><td> Call volume </td><td> call volume </td><td>/</td></tr>
     *            <tr><td>Wired headset/ USB headset/ external sound card</td><td> Media volume </td><td> Media Volume </td><td>/</td></tr>
     *            <tr><td> Bluetooth Headset </td><td> Call Volume </td><td> Call Volume </td><td> Ability to use the microphone included in the Bluetooth headset for audio capture. </td></tr>
     *         </table>
     */
    ByteRTCAudioScenarioHighqualityChat = 5,
};
 /**
    * @locale zh
    * @type keytype
    * @brief 如果以下音频场景类型无法满足你的业务需要，请联系技术支持人员。
    */
 /**
    * @locale en
    * @type keytype
    * @brief If the following audio scenarios cannot meet your business needs, please contact our technical support team.
    */
typedef NS_ENUM(NSInteger, ByteRTCAudioSceneType) {
/**
     * @locale zh
     * @brief 默认场景 <br>
     *        此场景适用于对音乐表现力有要求的场景，如音乐直播等。 <br>
     *        不同音频设备，开麦和闭麦状态下的使用的音量类型：<br>
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
    ByteRTCAudioSceneDefault = 0,
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
    ByteRTCAudioSceneChatRoom = 1,
/**
     * @locale zh
     * @brief 高音质语聊场景 <br>
     *        此场景下，无论客户端音频采集播放设备和采集播放状态，全程使用媒体音量。<br>
     *        外放通话时，可能出现回声和啸叫，请联系技术支持人员。<br>
     *        此场景可以提供立体声高音质，强保证音频原声音质。
     */
/**
     * @locale en
     * @brief High-quality chat scenarios <br>
     *        This scenario uses the media volume regardless of the client-side audio device or status. <br>
     *        If the audio quality is unsatisfactory when you put on speaker, please contact the technical support.     
*/
    ByteRTCAudioSceneHighQualityChatRoom = 2,
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
    ByteRTCAudioSceneLowLatency = 3,
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
typedef NS_ENUM(NSInteger, ByteRTCVoiceChangerType) {
    /**
     * @locale zh
     * @brief 原声，不含特效
     */
    /**
     * @locale en
     * @brief Acoustic, no special effects
     */
    ByteRTCVoiceChangerOriginal = 0,
    /**
     * @locale zh
     * @brief 巨人
     */
    /**
     * @locale en
     * @brief Giant
     */
    ByteRTCVoiceChangerGiant = 1,
    /**
     * @locale zh
     * @brief 花栗鼠
     */
    /**
     * @locale en
     * @brief Chipmunk
     */
    ByteRTCVoiceChangerChipmunk = 2,
    /**
     * @locale zh
     * @brief 小黄人
     */
    /**
     * @locale en
     * @brief Little yellow man
     */
    ByteRTCVoiceChangerMinionst = 3,
    /**
     * @locale zh
     * @brief 颤音
     */
    /**
     * @locale en
     * @brief Trill
     */
    ByteRTCVoiceChangerVibrato = 4,
    /**
     * @locale zh
     * @brief 机器人
     */
    /**
     * @locale en
     * @brief Robot
     */
    ByteRTCVoiceChangerRobot = 5,
};

/**
 * @locale zh
 * @type keytype
 * @brief 混响特效类型
 */
/**
 * @locale en
 * @type keytype
 * @brief  Reverb effect type
 */
typedef NS_ENUM(NSInteger, ByteRTCVoiceReverbType) {
    /**
     * @locale zh
     * @brief 原声，不含特效
     */
    /**
     * @locale en
     * @brief Acoustic, no special effects
     */
    ByteRTCVoiceReverbOriginal = 0,
    /**
     * @locale zh
     * @brief 回声
     */
    /**
     * @locale en
     * @brief Echo
     */
    ByteRTCVoiceReverbEcho = 1,
    /**
     * @locale zh
     * @brief 演唱会
     */
    /**
     * @locale en
     * @brief Concert
     */
    ByteRTCVoiceReverbConcert = 2,
    /**
     * @locale zh
     * @brief 空灵
     */
    /**
     * @locale en
     * @brief Ethereal
     */
    ByteRTCVoiceReverbEthereal = 3,
    /**
     * @locale zh
     * @brief KTV
     */
    /**
     * @locale en
     * @brief Karaoke
     */
    ByteRTCVoiceReverbKTV = 4,
    /**
     * @locale zh
     * @brief 录音棚
     */
    /**
     * @locale en
     * @brief Recording studio
     */
    ByteRTCVoiceReverbStudio = 5,
    /**
     * @locale zh
     * @brief 虚拟立体声
     */
    /**
     * @locale en
     * @brief Virtual Stereo
     */
    ByteRTCVoiceReverbVirtualStereo = 6,
    /**
     * @locale zh
     * @brief 空旷
     */
    /**
     * @locale en
     * @brief Spacious
     */
    ByteRTCVoiceReverbSpacious = 7,
    /**
     * @locale zh
     * @brief 3D人声
     */
    /**
     * @locale en
     * @brief 3D vocal
     */
    ByteRTCVoiceReverb3D = 8,
    /**
     * @locale zh
     * @hidden internal use
     * @brief 流行
     */
    /**
     * @locale en
     * @hidden internal use
     * @brief Pop
     */
    ByteRTCVoiceReverbPop = 9,
    /**
     * @locale zh
     * @hidden internal use
     * @brief 蹦迪
     */
    /**
     * @locale en
     * @hidden internal use
     * @brief Disco
     */
    ByteRTCVoiceReverbDisco = 10,
    /**
     * @locale zh
     * @hidden internal use
     * @brief 老唱片
     */
    /**
     * @locale en
     * @hidden internal use
     * @brief Old Record
     */
    ByteRTCVoiceReverbOldRecord = 11,
    /**
     * @locale zh
     * @hidden internal use
     * @brief 和声
     */
    /**
     * @locale en
     * @hidden internal use
     * @brief Harmony
     */
    ByteRTCVoiceReverbHarmony = 12,
    /**
     * @locale zh
     * @hidden internal use
     * @brief 摇滚
     */
    /**
     * @locale en
     * @hidden internal use
     * @brief Rock
     */
    ByteRTCVoiceReverbRock = 13,
    /**
     * @locale zh
     * @hidden internal use
     * @brief 蓝调
     */
    /**
     * @locale en
     * @hidden internal use
     * @brief Blues
     */
    ByteRTCVoiceReverbBlues = 14,
    /**
     * @locale zh
     * @hidden internal use
     * @brief 爵士
     */
    /**
     * @locale en
     * @hidden internal use
     * @brief Jazz
     */
    ByteRTCVoiceReverbJazz = 15,
    /**
     * @locale zh
     * @hidden internal use
     * @brief 电子
     */
    /**
     * @locale en
     * @hidden internal use
     * @brief Electronic
     */
    ByteRTCVoiceReverbElectronic = 16,
    /**
     * @locale zh
     * @hidden internal use
     * @brief 黑胶
     */
    /**
     * @locale en
     * @hidden internal use
     * @brief Vinyl
     */
    ByteRTCVoiceReverbVinyl = 17,
    /**
     * @locale zh
     * @hidden internal use
     * @brief 密室
     */
    /**
     * @locale en
     * @hidden internal use
     * @brief Chamber
     */
    ByteRTCVoiceReverbChamber = 18,
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
typedef NS_ENUM(NSInteger, ByteRTCBandFrequency) {
    /**
     * @locale zh
     * @brief 中心频率为 31Hz 的频带。
     */
    /**
     * @locale en
     * @brief The frequency band with a center frequency of 31Hz.
     */
    ByteRTCBandFrequency31 = 0,
    /**
     * @locale zh
     * @brief 中心频率为 62Hz 的频带。
     */
    /**
     * @locale en
     * @brief The frequency band with a center frequency of 62Hz.
     */
    ByteRTCBandFrequency62 = 1,
    /**
     * @locale zh
     * @brief 中心频率为 125Hz 的频带。
     */
    /**
     * @locale en
     * @brief The frequency band with a center frequency of 125Hz.
     */
    ByteRTCBandFrequency125 = 2,
    /**
     * @locale zh
     * @brief 中心频率为 250Hz 的频带。
     */
    /**
     * @locale en
     * @brief The frequency band with a center frequency of 250Hz.
     */
    ByteRTCBandFrequency250 = 3,
    /**
     * @locale zh
     * @brief 中心频率为 500Hz 的频带。
     */
    /**
     * @locale en
     * @brief The frequency band with a center frequency of 500Hz.
     */
    ByteRTCBandFrequency500 = 4,
    /**
     * @locale zh
     * @brief 中心频率为 1kHz 的频带。
     */
    /**
     * @locale en
     * @brief The frequency band with a center frequency of 1kHz.
     */
    ByteRTCBandFrequency1k = 5,
    /**
     * @locale zh
     * @brief 中心频率为 2kHz 的频带。
     */
    /**
     * @locale en
     * @brief The frequency band with a center frequency of 2kHz.
     */
    ByteRTCBandFrequency2k = 6,
    /**
     * @locale zh
     * @brief 中心频率为 4kHz 的频带。
     */
    /**
     * @locale en
     * @brief The frequency band with a center frequency of 4kHz.
     */
    ByteRTCBandFrequency4k = 7,
    /**
     * @locale zh
     * @brief 中心频率为 8kHz 的频带。
     */
    /**
     * @locale en
     * @brief The frequency band with a center frequency of 8kHz.
     */
    ByteRTCBandFrequency8k = 8,
    /**
     * @locale zh
     * @brief 中心频率为 16kHz 的频带。
     */
    /**
     * @locale en
     * @brief The frequency band with a center frequency of 16kHz.
     */
    ByteRTCBandFrequency16k = 9,
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
BYTERTC_APPLE_EXPORT @interface ByteRTCVoiceEqualizationConfig : NSObject
/**
 * @locale zh
 * @brief 频带。参看 ByteRTCBandFrequency{@link #ByteRTCBandFrequency}。
 */
/**
 * @locale en
 * @brief Frequency band. See ByteRTCBandFrequency{@link #ByteRTCBandFrequency}.
 */
@property(assign, nonatomic) ByteRTCBandFrequency frequency;
/**
 * @locale zh
 * @brief 频带增益（dB）。取值范围是 `[-15, 15]`。
 */
/**
 * @locale en
 * @brief Gain of the frequency band in dB. The range is `[-15, 15]`.
 */
@property(assign, nonatomic) int gain;
@end

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
BYTERTC_APPLE_EXPORT @interface ByteRTCVoiceReverbConfig : NSObject
/**
 * @locale zh
 * @brief 混响模拟的房间大小，取值范围 `[0.0, 100.0]`。默认值为 `50.0f`。房间越大，混响越强。
 */
/**
 * @locale en
 * @brief The room size for reverb simulation. The range is `[0.0, 100.0]`. The default value is `50.0f`. The larger the room, the stronger the reverberation.
 */
@property(assign, nonatomic) float roomSize;
/**
 * @locale zh
 * @brief 混响的拖尾长度，取值范围 `[0.0, 100.0]`。默认值为 `50.0f`。
 */
/**
 * @locale en
 * @brief The decay time of the reverb effect. The range is `[0.0, 100.0]`. The default value is `50.0f`.
 */
@property(assign, nonatomic) float decayTime;
/**
 * @locale zh
 * @brief 混响的衰减阻尼大小，取值范围 `[0.0, 100.0]`。默认值为 `50.0f`。
 */
/**
 * @locale en
 * @brief The damping index of the reverb effect. The range is `[0.0, 100.0]`. The default value is `50.0f`.
 */
@property(assign, nonatomic) float damping;
/**
 * @locale zh
 * @brief 早期反射信号强度。取值范围 `[-20.0, 10.0]`，单位为 dB。默认值为 `0.0f`。
 */
/**
 * @locale en
 * @brief The Intensity of the wet signal in dB. The range is `[-20.0, 10.0]`. The default value is `0.0f`.
 */
@property(assign, nonatomic) float wetGain;
/**
 * @locale zh
 * @brief 原始信号强度。取值范围 `[-20.0, 10.0]`，单位为 dB。默认值为 `0.0f`。
 */
/**
 * @locale en
 * @brief The Intensity of the dry signal in dB. The range is `[-20.0, 10.0]`. The default value is `0.0f`.
 */
@property(assign, nonatomic) float dryGain;
/**
 * @locale zh
 * @brief 早期反射信号的延迟。取值范围 `[0.0, 200.0]`，单位为 ms。默认值为 `0.0f`。
 */
/**
 * @locale en
 * @brief The delay of the wet signal in ms. The range is `[0.0, 200.0]`. The default value is `0.0f`.
 */
@property(assign, nonatomic) float preDelay;
@end

/**
 * @locale zh
 * @type keytype
 * @brief 音质档位
 */
/**
 * @locale en
 * @type keytype
 * @brief Sound quality
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioProfileType) {
    /**
     * @locale zh
     * @brief 默认音质<br>
     *        服务器下发或客户端已设置的 ByteRTCRoomProfile{@link #ByteRTCRoomProfile} 的音质配置
     */
    /**
     * @locale en
     * @brief Default sound quality<br>
     *        The sound quality configuration of ByteRTCRoomProfile{@link #ByteRTCRoomProfile} set by the server or client.
     */
    ByteRTCAudioProfileDefault = 0,
    /**
     * @locale zh
     * @brief 流畅  <br>
     *        单声道，采样率为 16 kHz，编码码率为 32 Kbps。 <br>
     *        流畅优先、低功耗、低流量消耗，适用于大部分游戏场景，如小队语音、组队语音、国战语音等。
     */
    /**
     * @locale en
     * @brief Fluent  <br>
     *        Sample rate: 16 KHz<br>
     *        Mono-channel<br>
     *        Encoding bitrate: 32 Kpbs <br>
     *        Low resource consumption, and small network packets guarantees a smooth call. It is suitable for most game scenarios, such as team-wide voice chat, group-wide voice chat, nation-wide voice chat.
     */
    ByteRTCAudioProfileFluent = 1,
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
    ByteRTCAudioProfileStandard = 2,
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
    ByteRTCAudioProfileHD = 3,
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
    ByteRTCAudioProfileStandardStereo = 4,
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
    ByteRTCAudioProfileHDMono = 5,
};

/**
 * @locale zh
 * @type keytype
 * @brief 降噪模式。降噪算法受调用 joinRoom:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoom:userInfo:roomConfig:} 时设置的房间模式影响。
 */
/**
 * @locale en
 * @type keytype
 * @brief ANC modes. The ANC algorithm is determined by the room profile you set when calling joinRoom:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoom:userInfo:roomConfig:}.
 */
typedef NS_ENUM(NSInteger, ByteRTCAnsMode) {
    /**
     * @locale zh
     * @brief 关闭所有音频降噪能力。
     */
    /**
     * @locale en
     * @brief Disable ANC.
     */
    ByteRTCAnsModeDisable = 0,
   /**
     * @locale zh
     * @brief 适用于微弱降噪。
     */
    /**
     * @locale en
     * @brief Cancel subtle background noise.
     */
    ByteRTCAnsModeLow = 1,
    /**
     * @locale zh
     * @brief 适用于抑制中度平稳噪声，如空调声和风扇声。
     */
    /**
     * @locale en
     * @brief Cancel medium-level, continuous noise, such as the sound of fans or air conditioners.
     */
    ByteRTCAnsModeMedium = 2,
     /**
     * @locale zh
     * @brief 适用于抑制嘈杂非平稳噪声，如键盘声、敲击声、碰撞声、动物叫声。
     */
    /**
     * @locale en
     * @brief Cancel loud, impulsive, and intermittent noise, such as keyboard clicking noise, a crash/clash, a bark, and chair scraping noise.
     */
    ByteRTCAnsModeHigh = 3,
    /**
     * @locale zh
     * @brief 启用音频降噪能力。具体的降噪算法由 RTC 智能决策。
     */
    /**
     * @locale en
     * @brief Enable automatic ANC. The ANC algorithm is dynamically determined by RTC.
     */
    ByteRTCAnsModeAutomatic = 4,
};

/**
 * @locale zh
 * @hidden
 * @deprecated since 3.45 and will be deleted in 3.51.
 * @type keytype
 * @brief 语音通话模式，在小队语音里用这个接口设置自己的发送模式
 */
/**
 * @locale en
 * @hidden
 * @deprecated since 3.45 and will be deleted in 3.51.
 * @type keytype
 * @brief Voice call mode, use this interface to set your own sending mode in team voice
 */
typedef NS_ENUM(NSUInteger, ByteRTCRangeAudioMode) {
    /**
     * @locale zh
     * @brief 默认模式
     */
    /**
     * @locale en
     * @brief Default mode
     */
    ByteRTCRangeAudioModeUndefined = 0,
    /**
     * @locale zh
     * @brief 小队模式
     */
    /**
     * @locale en
     * @brief Squad mode
     */
    ByteRTCRangeAudioModeTeam = 1,
    /**
     * @locale zh
     * @brief 世界模式
     */
    /**
     * @locale en
     * @brief World mode
     */
    ByteRTCRangeAudioModeWorld = 2,
};

/**
 * @locale zh
 * @type keytype
 * @brief 当前音频设备类型
 */
/**
 * @locale en
 * @type keytype
 * @brief Type of audio device
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioDeviceType) {
    /**
     * @locale zh
     * @brief 未知音频设备
     */
    /**
     * @locale en
     * @brief Unknown device
     */
    ByteRTCAudioDeviceTypeUnknown = -1,
    /**
     * @locale zh
     * @brief 音频渲染设备
     */
    /**
     * @locale en
     * @brief Screen audio recorder
     */
    ByteRTCAudioDeviceTypeRenderDevice = 0,
    /**
     * @locale zh
     * @brief 音频采集设备
     */
    /**
     * @locale en
     * @brief Microphone
     */
    ByteRTCAudioDeviceTypeCaptureDevice = 1,
    /**
     * @locale zh
     * @brief 屏幕流音频设备
     */
    /**
     * @locale en
     *@brief Screen audio recorder
     */
    ByteRTCAudioDeviceTypeScreenCaptureDevice = 2
};
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
typedef NS_ENUM(NSInteger, ByteRTCAudioSampleRate) {
    /**
     * @locale zh
     * @brief 默认设置。48000Hz。
     */
    /**
     * @locale en
     * @brief Default value. 48000Hz.
     */
    ByteRTCAudioSampleRateAuto = -1,
    /**
     * @locale zh
     * @brief 8000Hz
     */
    /**
     * @locale en
     * @brief 8000Hz
     */
    ByteRTCAudioSampleRate8000 = 8000,
    /**
     * @locale zh
     * @brief 16000Hz
     */
    /**
     * @locale en
     * @brief 16000Hz
     */
    ByteRTCAudioSampleRate16000 = 16000,
    /**
     * @locale zh
     * @brief 32000Hz
     */
    /**
     * @locale en
     * @brief 32000Hz
     */
    ByteRTCAudioSampleRate32000 = 32000,
    /**
     * @locale zh
     * @brief 44100Hz
     */
    /**
     * @locale en
     * @brief 44100Hz
     */
    ByteRTCAudioSampleRate44100 = 44100,
    /**
     * @locale zh
     * @brief 48000Hz
     */
    /**
     * @locale en
     * @brief 48000Hz
     */
    ByteRTCAudioSampleRate48000 = 48000
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
typedef NS_ENUM(NSInteger, ByteRTCAudioChannel) {
    /**
     * @locale zh
     * @brief 默认设置。默认值为 `2`。
     */
    /**
     * @locale en
     * @brief Default value. `2` by default.
     */
    ByteRTCAudioChannelAuto = -1,
    /**
     * @locale zh
     * @brief 单声道
     */
    /**
     * @locale en
     * @brief Mono channel.
     */
    ByteRTCAudioChannelMono = 1,
    /**
     * @locale zh
     * @brief 双声道
     */
    /**
     * @locale en
     * @brief Dual channels.
     */
    ByteRTCAudioChannelStereo = 2,
};

/**
 * @locale zh
 * @deprecated since 3.52, use ByteRTCMixedStreamAudioCodecType{@link #ByteRTCMixedStreamAudioCodecType} instead.
 * @type keytype
 * @brief 音频编码类型。
 */
/**
 * @locale en
 * @deprecated since 3.52, use ByteRTCMixedStreamAudioCodecType{@link #ByteRTCMixedStreamAudioCodecType} instead.
 * @type keytype
 * @brief The audio codec.
 */
typedef NS_ENUM(NSInteger, ByteRTCTranscodingAudioCodec) {
    /**
     * @locale zh
     * @type keytype
     * @brief AAC 格式。
     */
    /**
     * @locale en
     * @type keytype
     * @brief AAC format.
     */
    ByteRTCTranscodingAudioCodecAAC = 0,
};

/**
 * @locale zh
 * @type keytype
 * @brief 音频编码类型。(新)
 */
/**
 * @locale en
 * @type keytype
 * @brief The audio codec.(New)
 */
typedef NS_ENUM(NSInteger, ByteRTCMixedStreamAudioCodecType) {
    /**
     * @locale zh
     * @type keytype
     * @brief AAC 格式。
     */
    /**
     * @locale en
     * @type keytype
     * @brief AAC format.
     */
    ByteRTCMixedStreamAudioCodecTypeAAC = 0,
};

/**
 * @locale zh
 * @type keytype
 * @brief AAC 编码规格。
 */
/**
 * @locale en
 * @type keytype
 * @brief Advanced Audio Coding (AAC) profile.
 */
typedef NS_ENUM(NSInteger, ByteRTCMixedStreamAudioProfile) {
    /**
     * @locale zh
     * @brief AAC-LC 规格，默认值。
     */
    /**
     * @locale en
     * @brief (Default) AAC Low-Complexity profile (AAC-LC).
     */
    ByteRTCMixedStreamAudioProfileLC   = 0,
    /**
     * @locale zh
     * @brief HE-AAC v1 规格。
     */
    /**
     * @locale en
     * @brief HE-AAC v1 profile (AAC LC with SBR).
     */
    ByteRTCMixedStreamAudioProfileHEv1 = 1,
    /**
     * @locale zh
     * @brief HE-AAC v2 规格。
     */
    /**
     * @locale en
     * @brief HE-AAC v2 profile (AAC LC with SBR and Parametric Stereo).
     */
    ByteRTCMixedStreamAudioProfileHEv2 = 2,
};

/**
 * @locale zh
 * @deprecated since 3.52, use ByteRTCMixedStreamAudioProfile{@link #ByteRTCMixedStreamAudioProfile} instead.
 * @type keytype
 * @brief AAC 编码规格。
 */
/**
 * @locale en
 * @deprecated since 3.52, use ByteRTCMixedStreamAudioProfile{@link #ByteRTCMixedStreamAudioProfile} instead.
 * @type keytype
 * @brief Advanced Audio Coding (AAC) profile.
 */
typedef NS_ENUM(NSInteger, ByteRTCAACProfile) {
    /**
     * @locale zh
     * @brief AAC-LC 规格，默认值。
     */
    /**
     * @locale en
     * @brief (Default) AAC Low-Complexity profile (AAC-LC).
     */
    ByteRTCAACProfileLC   = 0,
    /**
     * @locale zh
     * @brief HE-AAC v1 规格。
     */
    /**
     * @locale en
     * @brief HE-AAC v1 profile (AAC LC with SBR).
     */
    ByteRTCAACProfileHEv1 = 1,
    /**
     * @locale zh
     * @brief HE-AAC v2 规格。
     */
    /**
     * @locale en
     * @brief HE-AAC v2 profile (AAC LC with SBR and Parametric Stereo).
     */
    ByteRTCAACProfileHEv2 = 2,
};
/**
 * @locale zh
 * @type keytype
 * @brief 音频播放路由
 */
/**
 * @locale en
 * @type keytype
 * @brief Audio playback device
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioRoute) {
    /**
     * @locale zh
     * @brief 通过 `setDefaultAudioRoute:` 设置的音频路由，或通过 AirPlay 连接的音频播放设备
     */
    /**
     * @locale en
     * @brief Default devices. The audio route set by `setDefaultAudioRoute:`.
     */
    ByteRTCAudioRouteDefault = -1,
    /**
     * @locale zh
     * @brief 有线耳机
     */
    /**
     * @locale en
     * @brief Wired earphones
     */
    ByteRTCAudioRouteHeadset = 1,
    /**
     * @locale zh
     * @brief 听筒。设备自带的，一般用于通话的播放硬件。
     */
    /**
     * @locale en
     * @brief Earpiece. Built-in device for calling
     */
    ByteRTCAudioRouteEarpiece = 2,
    /**
     * @locale zh
     * @brief 扬声器。设备自带的，一般用于免提播放的硬件。
     */
    /**
     * @locale en
     * @brief Speaker. Built-in device for hands-free audio playing
     */
    ByteRTCAudioRouteSpeakerphone = 3,
    /**
     * @locale zh
     * @brief 蓝牙耳机
     */
    /**
     * @locale en
     * @brief Bluetooth earphones
     */
    ByteRTCAudioRouteHeadsetBluetooth = 4,
    /**
     * @locale zh
     * @brief USB 设备或通过 Lightning 转接器连接的 3.5mm 耳机
     * 其中，仅在客户端为 iOS 16 及以上版本时可识别出 3.5mm 耳机
     */
    /**
     * @locale en
     * @brief USB Device
     */
    ByteRTCAudioRouteHeadsetUSB = 5,
};

/**
 * @locale zh
 * @type keytype
 * @brief 音频播放设备 <br>
 *        音频设备变化时 SDK 通过 `rtcEngine:onAudioPlaybackDeviceChanged:` 回调当前音频播放设备。
 */
/**
 * @locale en
 * @type keytype
 * @brief  Audio playback device   <br>
 *        When the audio playback device changes, you will receive the `rtcEngine:onAudioPlaybackDeviceChanged:` callback.
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioPlaybackDevice) {
    /**
     * @locale zh
     * @brief 有线耳机
     */
    /**
     * @locale en
     * @brief Wired earphones
     */
    ByteRTCAudioPlaybackDeviceHeadset = 1,
    /**
     * @locale zh
     * @brief 听筒
     */
    /**
     * @locale en
     * @brief Earpiece
     */
    ByteRTCAudioPlaybackDeviceEarpiece = 2,
    /**
     * @locale zh
     * @brief 扬声器
     */
    /**
     * @locale en
     * @brief Speaker
     */
    ByteRTCAudioPlaybackDeviceSpeakerphone = 3,
    /**
     * @locale zh
     * @brief 蓝牙耳机
     */
    /**
     * @locale en
     * @brief Bluetooth earphones
     */
    ByteRTCAudioPlaybackDeviceHeadsetBluetooth = 4,
    /**
     * @locale zh
     * @brief USB设备
     */
    /**
     * @locale en
     * @brief USB Device
     */
    ByteRTCAudioPlaybackDeviceHeadsetUSB = 5,
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
typedef NS_ENUM(NSInteger, ByteRTCASRAuthorizationType) {
    /**
     * @locale zh
     *  @brief 使用 token 不设置加密形式。  
     */
    /**
     * @locale en
     *  @brief Use token without setting the encrypted form. 
     */
    ByteRTCASRAuthorizationTypeToken = 0,
    /**
     * @locale zh
     *  @brief 带有 token 额外使用 signature 加密，此种加密形式需要额外传递 secret token 。  
     */
    /**
     * @locale en
     *  @brief With token additional use of signature encryption, this form of encryption requires additional pass secret token. 
     */
    ByteRTCASRAuthorizationTypeSignature = 1,
};

/**
 * @locale zh
 * @type keytype
 * @brief 语音识别服务错误码。  <br>
 *        除网络原因导致的错误，语音识别服务内部会自行重试之外，其他错误都会停止服务，此时建议再次调用 `startASR:handler:` 重启语音识别功能。
 */
/**
 * @locale en
 * @type keytype
 * @brief Speech recognition service error code.   <br>
 *        Except for errors caused by network reasons, the speech recognition service will retry itself, other errors will stop the service. At this time, it is recommended to call `startASR:handler:` to restart the speech recognition function.
 */
typedef NS_ENUM(NSInteger, ByteRTCASRErrorCode) {
    /**
     * @locale zh
     * @brief 网络连接中断，服务不可用，内部会进行重连
     */
    /**
     * @locale en
     * @brief The network connection is broken, the service is unavailable, and internal reconnection will be carried out
     */
    ByteRTCASRErrorNetworkInterrupted = -1,
    /**
     * @locale zh
     * @brief 用户已经调用过 `startASR:handler:`。  <br>
     *        开启语音识别服务后，你需要先调用 `stopASR` 停止语音识别服务，才能二次调用 `startASR:handler:` 再次开启服务。
     */
    /**
     * @locale en
     * @brief The user has called `startASR:handler:`. <br>
     *         After starting the speech recognition service, you need to call `stopASR` to stop the speech recognition service before starting the service again.
     */
    ByteRTCASRErrorAlreadyStarted = -2,
    /**
     * @locale zh
     * @brief 语音识别服务所需 token 为空
     */
    /**
     * @locale en
     * @brief The token required by the speech recognition service is empty
     */
    ByteRTCASRErrorTokenEmpty = -3,
    /**
     * @locale zh
     * @brief Signature 鉴权模式下 secretKey 为空
     */
    /**
     * @locale en
     * @brief Signature  The secretKey is empty in authentication mode
     */
    ByteRTCErrorSignatureKeyEmpty = -4,
    /**
     * @locale zh
     * @brief 用户 ID 为空
     */
    /**
     * @locale en
     * @brief User ID is empty
     */
    ByteRTCASRErrorUserIdNull = -5,
    /**
     * @locale zh
     * @brief 应用 ID 为空
     */
    /**
     * @locale en
     * @brief Application ID is empty
     */
    ByteRTCASRErrorAPPIDNull = -6,
    /**
     * @locale zh
     * @brief 语音识别服务 cluster 为空
     */
    /**
     * @locale en
     * @brief Speech recognition service cluster is empty
     */
    ByteRTCASRErrorClusterNull = -7,
    /**
     * @locale zh
     * @brief 语音识别服务连接失败，该版本没有语音识别功能，请联系 RTC 技术支持。
     */
    /**
     * @locale en
     * @brief The speech recognition service connection failed, this version does not have speech recognition function, please contact RTC technical support.
     */
    ByteRTCASRErrorOperationDenied = -8
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
typedef NS_ENUM(NSInteger, ByteRTCAudioMixingType) {
    /**
     * @locale zh
     * @brief 仅本地播放
     */
    /**
     * @locale en
     * @brief Played at the local device only
     */
    ByteRTCAudioMixingTypePlayout = 0,
    /**
     * @locale zh
     * @brief 仅远端播放
     */
    /**
     * @locale en
     * @brief Sent to the remote devices only
     */
    ByteRTCAudioMixingTypePublish = 1,
    /**
     * @locale zh
     * @brief 本地和远端同时播放
     */
    /**
     * @locale en
     * @brief Played at the local device and sent to the remote devices.
     */
    ByteRTCAudioMixingTypePlayoutAndPublish = 2
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
typedef NS_ENUM(NSInteger, ByteRTCAudioMixingDualMonoMode) {
    /**
     * @locale zh
     * @brief 和音频文件一致
     */
    /**
     * @locale en
     * @brief Consistent with audio files
     */
    ByteRTCAudioMixingDualMonoModeAuto = 0,
    /**
     * @locale zh
     * @brief 只能听到音频文件中左声道的音频
     */
    /**
     * @locale en
     * @brief Only the left channel audio in the audio file can be heard
     */
    ByteRTCAudioMixingDualMonoModeL = 1,
    /**
     * @locale zh
     * @brief 只能听到音频文件中右声道的音频
     */
    /**
     * @locale en
     * @brief Only the right channel audio in the audio file can be heard
     */
    ByteRTCAudioMixingDualMonoModeR = 2,
    /**
     * @locale zh
     * @brief 能同时听到音频文件中左右声道的音频
     */
    /**
     * @locale en
     * @brief Both the left and right channel audio in the file can be heard at the same time
     */
    ByteRTCAudioMixingDualMonoModeMix = 3
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
typedef NS_ENUM(NSInteger, ByteRTCAudioMixingState) {
    /**
     * @locale zh
     * @brief 混音已加载
     */
    /**
     * @locale en
     * @brief Mix loaded
     */
    ByteRTCAudioMixingStatePreloaded = 0,
    /**
     * @locale zh
     * @brief 混音正在播放
     */
    /**
     * @locale en
     * @brief Mix is playing
     */
    ByteRTCAudioMixingStatePlaying,
    /**
     * @locale zh
     * @brief 混音暂停
     */
    /**
     * @locale en
     * @brief Mix Pause
     */
    ByteRTCAudioMixingStatePaused,
    /**
     * @locale zh
     * @brief 混音停止
     */
    /**
     * @locale en
     * @brief Mixing stopped
     */
    ByteRTCAudioMixingStateStopped,
    /**
     * @locale zh
     * @brief 混音播放失败
     */
    /**
     * @locale en
     * @brief Mix playback failed
     */
    ByteRTCAudioMixingStateFailed,
    /**
     * @locale zh
     * @brief 混音播放结束
     */
    /**
     * @locale en
     * @brief End of mixing
     */
    ByteRTCAudioMixingStateFinished,
    /**
     * @locale zh
     * @brief 准备PCM混音
     */
    /**
     * @locale en
     * @brief PCM mixing enabled
     */
    ByteRTCAudioMixingStatePCMEnabled,
    /**
     * @locale zh
     * @brief PCM混音播放结束
     */
    /**
     * @locale en
     * @brief PCM mixing disabled
     */
    ByteRTCAudioMixingStatePCMDisabled,
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
typedef NS_ENUM(NSInteger, ByteRTCAudioMixingError) {
    /**
     * @locale zh
     * @brief 正常
     */
    /**
     * @locale en
     * @brief OK
     */
    ByteRTCAudioMixingErrorOk = 0,
    /**
     * @locale zh
     * @brief 预加载失败，找不到混音文件或者文件长度超出 20s
     */
    /**
     * @locale en
     * @brief Preload failed. Invalid path or the length exceeds 20s.
     */
    ByteRTCAudioMixingErrorPreloadFailed,
    /**
     * @locale zh
     * @brief 混音开启失败，找不到混音文件或者混音文件打开失败
     */
    /**
     * @locale en
     * @brief Mixing failed. Invalid path or fail to open the file.
     */
    ByteRTCAudioMixingErrorStartFailed,
    /**
     * @locale zh
     * @brief 混音 ID 异常
     */
    /**
     * @locale en
     * @brief Invalid mixID
     */
    ByteRTCAudioMixingErrorIdNotFound,
    /**
     * @locale zh
     * @brief 设置混音文件的播放位置出错
     */
    /**
     * @locale en
     * @brief Invalid position
     */
    ByteRTCAudioMixingErrorSetPositionFailed,
    /**
     * @locale zh
     * @brief 音量参数不合法，仅支持设置的音量值为[0, 400]
     */
    /**
     * @locale en
     * @brief Invalid volume. The range is [0, 400].
     */
    ByteRTCAudioMixingErrorInValidVolume,
    /**
     * @locale zh
     * @brief 播放的文件与预加载的文件不一致。请先使用 unloadAudioMixing:{@link #ByteRTCAudioMixingManager#unloadAudioMixing:} 卸载此前的文件。
     */
    /**
     * @locale en
     * @brief Another file was preloaded for mixing. Call unloadAudioMixing:{@link #ByteRTCAudioMixingManager#unloadAudioMixing:} first.
     */
    ByteRTCAudioMixingErrorLoadConflict,
    /**
     * @locale zh
     * @brief 不支持此混音类型。
     */
    /**
     * @locale en
     * @brief Invalid mix type.
     */
    ByteRTCAudioMixingErrorIdTypeNotMatch,
    /**
     * @locale zh
     * @brief 设置混音文件的音调不合法
     */
    /**
     * @locale en
     * @brief Invalid pitch value.
     */
    ByteRTCAudioMixingErrorInValidPitch,
    /**
     * @locale zh
     * @brief 设置混音文件的音轨不合法
     */
    /**
     * @locale en
     * @brief Invalid audio track.
     */
    ByteRTCAudioMixingErrorInValidAudioTrack,
    /**
     * @locale zh
     * @brief 混音文件正在启动中
     */
    /**
     * @locale en
     * @brief Mixing starting.
     */
    ByteRTCAudioMixingErrorIsStarting,
    /**
     * @locale zh
     * @brief 设置混音文件的播放速度不合法
     */
    /**
     * @locale en
     * @brief Invalid playback speed
     */
    ByteRTCAudioMixingErrorInValidPlaybackSpeed,
};
/**
 * @locale zh
 * @type keytype
 * @brief 自定义音频源模式
 */
/**
 * @locale en
 * @type keytype
 * @brief Custom audio source mode
 */
typedef NS_ENUM(NSInteger, ByteRTCMediaPlayerCustomSourceMode) {
    /**
     * @locale zh
     * @brief 当播放来自本地的 PCM 数据时，使用此选项。
     */
    /**
     * @locale en
     * @brief When you use the local PCM data, use this mode.
     */
    ByteRTCMediaPlayerCustomSourceModePush = 0,
    /**
     * @locale zh
     * @brief 当播放来自内存的音频数据时，使用此选项。
     */
    /**
     * @locale en
     * @brief When you use the audio data from local memory, use this mode.
     */
    ByteRTCMediaPlayerCustomSourceModePull,
};
/**
 * @locale zh
 * @type keytype
 * @brief 自定义音频流类型
 */
/**
 * @locale en
 * @type keytype
 * @brief Custom audio source stream type
 */
typedef NS_ENUM(NSInteger, ByteRTCMediaPlayerCustomSourceStreamType) {
    /**
     * @locale zh
     * @brief 当播放来自本地的 PCM 数据时，使用此选项。
     */
    /**
     * @locale en
     * @brief When you use the local PCM data, use this type.
     */
    ByteRTCMediaPlayerCustomSourceStreamTypeRaw = 0,
    /**
     * @locale zh
     * @brief 当播放来自内存的音频数据时，使用此选项。
     */
    /**
     * @locale en
     * @brief When you use the audio data from local memory, use this type.
     */
    ByteRTCMediaPlayerCustomSourceStreamTypeEncoded,
};
/**
 * @locale zh
 * @type keytype
 * @brief 音频数据的起始读取位置。
 */
/**
 * @locale en
 * @type keytype
 * @brief The starting position where audio data seeking begins. 
 */
typedef NS_ENUM(NSInteger, ByteRTCMediaPlayerCustomSourceSeekWhence) {
    /**
     * @locale zh
     * @brief 从音频数据的头开始读取，读取后的位置为参数 offset 的值。
     */
    /**
     * @locale en
     * @brief Seeks from the head of the audio data and the position of actual data offset after seeking is offset.
     */
    ByteRTCMediaPlayerCustomSourceSeekWhenceSet = 0,
    /**
     * @locale zh
     * @brief 从音频数据的某一位置开始读取，读取后的位置为音频数据当前的读取位置加上参数 offset 的值。 
     */
    /**
     * @locale en
     * @brief Seeks from a specific position of the audio data stream, and the actual data offset after seeking is the current position plus offset.
     */
    ByteRTCMediaPlayerCustomSourceSeekWhenceCur = 1,
    /**
     * @locale zh
     * @brief 从音频数据的尾开始读取，读取后的位置为用户传入的音频数据大小加上参数 offset 的值。 
     */
    /**
     * @locale en
     * @brief Seeks from the end of the audio data, and the actual data offset after seeking is the whole data length plus offset.
     */
    ByteRTCMediaPlayerCustomSourceSeekWhenceEnd = 2,
    /**
     * @locale zh
     * @brief 返回音频数据的大小。
     */
    /**
     * @locale en
     * @brief Returns the size of audio data.
     */
    ByteRTCMediaPlayerCustomSourceSeekWhenceSize = 3,
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
typedef NS_ENUM(NSInteger, ByteRTCPlayerState) {
    /**
     * @locale zh
     * @brief 播放未启动
     */
    /**
     * @locale en
     * @brief Not started.
     */
    ByteRTCPlayerStateIdle = 0,
    /**
     * @locale zh
     * @brief 已加载
     */
    /**
     * @locale en
     * @brief Preloaded.
     */
    ByteRTCPlayerStatePreloaded,
    /**
     * @locale zh
     * @brief 已打开
     */
    /**
     * @locale en
     * @brief Opened.
     */
    ByteRTCPlayerStateOpened,
    /**
     * @locale zh
     * @brief 正在播放
     */
    /**
     * @locale en
     * @brief Playing.
     */
    ByteRTCPlayerStatePlaying,
    /**
     * @locale zh
     * @brief 播放已暂停
     */
    /**
     * @locale en
     * @brief Paused.
     */
    ByteRTCPlayerStatePaused,
    /**
     * @locale zh
     * @brief 播放已停止
     */
    /**
     * @locale en
     * @brief Stopped.
     */
    ByteRTCPlayerStateStopped,
    /**
     * @locale zh
     * @brief 播放失败
     */
    /**
     * @locale en
     * @brief Failed.
     */
    ByteRTCPlayerStateFailed,
    /** {zh}
     * @brief 播放已结束
     */
    /** {en}
     * @brief Finished.
     */
    ByteRTCPlayerStateFinished,
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
typedef NS_ENUM(NSInteger, ByteRTCPlayerError) {
    /**
     * @locale zh
     * @brief 正常
     */
    /**
     * @locale en
     * @brief OK
     */
    ByteRTCPlayerErrorOK = 0,
    /**
     * @locale zh
     * @brief 不支持此类型
     */
    /**
     * @locale en
     * @brief Format not supported.
     */
    ByteRTCPlayerErrorFormatNotSupport,
    /**
     * @locale zh
     * @brief 无效的播放路径
     */
    /**
     * @locale en
     * @brief Invalid file path.
     */
    ByteRTCPlayerErrorInvalidPath,
    /**
     * @locale zh
     * @brief 未满足前序接口调用的要求。请查看具体接口文档。
     */
    /**
     * @locale en
     * @brief The prerequisite is not met. Check the specific API doc.
     */
    ByteRTCPlayerErrorInvalidState,
    /**
     * @locale zh
     * @brief 设置播放位置出错。
     */
    /**
     * @locale en
     * @brief Invalid position.
     */
    ByteRTCPlayerErrorInvalidPosition,
    /**
     * @locale zh
     * @brief 音量参数不合法。
     */
    /**
     * @locale en
     * @brief Invalid volume.
     */
    ByteRTCPlayerErrorInvalidVolume,
    /**
     * @locale zh
     * @brief 音调参数设置不合法。
     */
    /**
     * @locale en
     * @brief Invalid pitch value.
     */
    ByteRTCPlayerErrorInvalidPitch,
    /**
     * @locale zh
     * @brief 音轨参数设置不合法。
     */
    /**
     * @locale en
     * @brief Invalid audio track.
     */
    ByteRTCPlayerErrorInvalidAudioTrackIndex,
    /**
     * @locale zh
     * @brief 播放速度参数设置不合法
     */
    /**
     * @locale en
     * @brief Invalid playback speed.
     */
    ByteRTCPlayerErrorInvalidPlaybackSpeed,
    /**
     * @locale zh
     * @brief 音效 ID 异常。还未加载或播放文件，就调用其他 API。
     */
    /**
     * @locale en
     * @brief Invalid effect ID. Receive this error code when you call other APIs before the audio file is preloaded or opened.
     */
    ByteRTCPlayerErrorInvalidEffectId,
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
typedef NS_ENUM(NSInteger, ByteRTCAudioSourceType) {
    /**
     * @locale zh
     * @brief 自定义采集音频源
     */
    /**
     * @locale en
     * @brief Custom Capture Audio Source
     */
    ByteRTCAudioSourceTypeExternal = 0,
    /**
     * @locale zh
     * @brief RTC SDK 内部采集音频源
     */
    /**
     * @locale en
     * @brief RTC SDK internal acquisition audio source
     */
    ByteRTCAudioSourceTypeInternal,
};

/**
 * @locale zh
 * @type keytype
 * @brief 音频输出源类型
 */
/**
 * @locale en
 * @type keytype
 * @brief  Audio output type
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioRenderType) {
    /**
     * @locale zh
     * @brief 自定义渲染音频
     */
    /**
     * @locale en
     * @brief Custom render Audio
     */
    ByteRTCAudioRenderTypeExternal = 0,
    /**
     * @locale zh
     * @brief RTC SDK 内部渲染音频
     */
    /**
     * @locale en
     * @brief RTC SDK internal render audio
     */
    ByteRTCAudioRenderTypeInternal,
};

/**
 * @locale zh
 * @type keytype
 * @brief 开启/关闭耳返功能。
 */
/**
 * @locale en
 * @type keytype
 * @brief Enables/disables in-ear monitoring.
 */
typedef NS_ENUM(NSInteger, ByteRTCEarMonitorMode) {
    /**
     * @locale zh
     * @brief 关闭耳返功能。
     */
    /**
     * @locale en
     * @brief Disable in-ear monitoring.
     */
    ByteRTCEarMonitorModeOff = 0,
    /**
     * @locale zh
     * @brief 开启耳返功能。
     */
    /**
     * @locale en
     * @brief Enable in-ear monitoring.
     */
    ByteRTCEarMonitorModeOn = 1,
};

/**
 * @locale zh
 * @type keytype
 * @brief 音频回调方法
 */
/**
 * @locale en
 * @type keytype
 * @brief Audio data callback method
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioFrameCallbackMethod) {
    /**
     * @locale zh
     * @brief 本地麦克风录制的音频数据回调
     */
    /**
     * @locale en
     * @brief The callback of the audio data recorded by local microphone.
     */
    ByteRTCAudioFrameCallbackRecord = 0,
    /**
     * @locale zh
     * @brief 订阅的远端所有用户混音后的音频数据回调
     */
    /**
     * @locale en
     * @brief The callback of the mixed audio data of all remote users subscribed by the local user.
     */
    ByteRTCAudioFrameCallbackPlayback = 1,
    /**
     * @locale zh
     * @brief 本地麦克风录制和订阅的远端所有用户混音后的音频数据回调
     */
    /**
     * @locale en
     * @brief The callback of the mixed audio data including the data recorded by local microphone and that of all remote users subscribed by the local user.
     */
    ByteRTCAudioFrameCallbackMixed = 2,
    /**
     * @locale zh
     * @brief 订阅的远端每个用户混音前的音频数据回调
     */
    /**
     * @locale en
     * @brief The callback of the audio data before mixing of each remote user subscribed by the local user.
     */
    ByteRTCAudioFrameCallbackRemoteUser = 3,
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
typedef NS_ENUM(NSInteger, ByteRTCAudioFrameMethod) {
    /**
     * @locale zh
     * @brief 本地采集的音频。
     */
    /**
     * @locale en
     * @brief Locally captured audio frame.
     */
    ByteRTCAudioFrameProcessorRecord = 0,
    /**
     * @locale zh
     * @brief 远端音频流的混音音频。
     */
    /**
     * @locale en
     * @brief The mixed remote audio.
     */
    ByteRTCAudioFrameProcessorPlayback = 1,
    /**
     * @locale zh
     * @brief 各个远端音频流。
     */
    /**
     * @locale en
     * @brief The audio streams from remote users.
     */
    ByteRTCAudioFrameProcessorRemoteUser = 2,
    /**
     * @locale zh
     * @hidden(macOS)
     * @brief 软件耳返音频。
     */
    /**
     * @locale en
     * @hidden(macOS)
     * @brief The SDK-level in-ear monitoring.
     */
    ByteRTCAudioFrameProcessorEarMonitor = 3,
     /**
     * @locale zh
     * @brief 屏幕共享音频。
     */
    /**
     * @locale en
     * @brief The shared-screen audio.
     */
    ByteRTCAudioFrameProcessorScreen = 4,
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
typedef NS_ENUM(NSInteger, ByteRTCAudioReportMode) {
     /**
     * @locale zh
     * @brief 默认始终开启音量回调。
     */
    /**
     * @locale en
     * @brief Always-on(Default).
     */
    ByteRTCAudioReportModeNormal = 0,
   /**
     * @locale zh
     * @brief 可见用户进房并停止推流后，关闭音量回调。
     */
    /**
     * @locale en
     * @brief After visibly joining a room and unpublish your streams, disable the volume callback.
     */
    ByteRTCAudioReportModeDisconnect = 1,
     /**
     * @locale zh
     * @brief 可见用户进房并停止推流后，开启音量回调，回调值重置为0。
     */
    /**
     * @locale en
     * @brief After visibly joining a room and unpublish your streams, enable the volume callback. The volume is reset to 0.
     */
    ByteRTCAudioReportModeReset = 2,
};

/**
 * @locale zh
 * @type keytype
 * @brief rtcEngine:onLocalAudioPropertiesReport:{@link #ByteRTCVideoDelegate#rtcEngine:onLocalAudioPropertiesReport:} 中包含的音频信息的范围。
 */
/**
 * @locale en
 * @type keytype
 * @brief The audio info included in rtcEngine:onLocalAudioPropertiesReport:{@link #ByteRTCVideoDelegate#rtcEngine:onLocalAudioPropertiesReport:}.
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioPropertiesMode) {
    /**
     * @locale zh
     * @brief 仅包含本地麦克风采集的音频数据和本地屏幕音频采集数据。
     */
    /**
     * @locale en
     * @brief Only locally captured microphone audio info and locally captured screen audio info are included.
     */
    ByteRTCAudioPropertiesModeMicrohone = 0,
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
    ByteRTCAudioPropertiesModeAudioMixing = 1
};

/**
 * @locale zh
 * @type keytype
 * @brief 音频流来源的用户 ID, 及对应的音量。
 */
/**
 * @locale en
 * @type keytype
 * @brief User ID of the source of the audio stream, and the corresponding volume.
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCAudioVolumeInfo : NSObject
/**
 * @locale zh
 * @brief 音频流来源的用户 ID
 */
/**
 * @locale en
 * @brief User of the audio stream source ID
 */
@property(copy, nonatomic) NSString * _Nonnull uid;
/**
 * @locale zh
 * @brief 线性音量，取值范围为：[0,255]
 */
/**
 * @locale en
 * @brief LinearVolume, range: [0,255]
 */
@property(assign, nonatomic) NSUInteger linearVolume;
/**
 * @locale zh
 * @brief 非线性音量，取值范围为：[-127,0]
 */
/**
 * @locale en
 * @brief NonlinearVolume, range: [-127,0]
 */
@property(assign, nonatomic) NSUInteger nonlinearVolume;
@end

/**
 * @locale zh
 * @type keytype
 * @brief 音频参数格式
 */
/**
 * @locale en
 * @type keytype
 * @brief Audio parameters format
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCAudioFormat : NSObject
/**
 * @locale zh
 * @brief 音频采样率，详见 ByteRTCAudioSampleRate{@link #ByteRTCAudioSampleRate}
 */
/**
 * @locale en
 * @brief Audio sampling rate. See ByteRTCAudioSampleRate{@link #ByteRTCAudioSampleRate}
 */
@property(nonatomic, assign) ByteRTCAudioSampleRate sampleRate;
/**
 * @locale zh
 * @brief 音频声道，详见 ByteRTCAudioChannel{@link #ByteRTCAudioChannel}
 */
/**
 * @locale en
 * @brief For audio channels. See ByteRTCAudioChannel{@link #ByteRTCAudioChannel}
 */
@property(nonatomic, assign) ByteRTCAudioChannel channel;
/**
 * @locale zh
 * @brief 单次回调的音频帧中包含的采样点数。默认值为 `0`，此时，采样点数取最小值。<br>
 *        最小值为回调间隔是 0.01s 时的值，即 `sampleRate * channel * 0.01s`。<br>
 *        最大值是 `2048`。超出取值范围时，采样点数取默认值。<br>
 *        该参数仅在设置读写回调时生效，调用 enableAudioFrameCallback:format:{@link #ByteRTCVideo#enableAudioFrameCallback:format:} 开启只读模式回调时设置该参数不生效。
 */
/**
 * @locale en
 * @brief Samples per audio frame returned by callback. `0` by default. The default samples per callback is the minimum value.<br>
 *        The minimum value is `sampleRate * channel * 0.01s`, the value when the callback interval is 0.01s.<br>
 *        The maximum value is `2048`. If the value is invalid, the samples per callback uses the default value.<br>
 *        This parameter only takes effect when setting the read-write callback. It does not take effect when calling enableAudioFrameCallback:format:{@link #ByteRTCVideo#enableAudioFrameCallback:format:} to enable read-only callback.
 */
@property(nonatomic, assign) int samplesPerCall;
@end

/**
 * @locale zh
 * @type keytype
 * @brief PCM 音频帧
 */
/**
 * @locale en
 * @type keytype
 * @brief Audio frame in PCM
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCAudioFrame : NSObject
/**
 * @locale zh
 * @brief PCM 数据
 */
/**
 * @locale en
 * @brief PCM data
 */
@property(strong, nonatomic) NSData * _Nonnull buffer;
/**
 * @locale zh
 * @brief 采样点个数
 */
/**
 * @locale en
 * @brief Total sampling number
 */
@property(assign, nonatomic) int samples;
/**
 * @locale zh
 * @brief 音频声道，参看 ByteRTCAudioChannel{@link #ByteRTCAudioChannel}。<br>
 *        双声道的情况下，左右声道的音频帧数据以 LRLRLR 形式排布。
 */
/**
 * @locale en
 * @brief Audio channel. See ByteRTCAudioChannel{@link #ByteRTCAudioChannel}.<br>
 *        For dual channels, the audio frames are interleaved.
 */
@property(assign, nonatomic) ByteRTCAudioChannel channel;
/**
 * @locale zh
 * @brief 采样率，参看 ByteRTCAudioSampleRate{@link #ByteRTCAudioSampleRate}。
 */
/**
 * @locale en
 * @brief Sample rate. See ByteRTCAudioSampleRate{@link #ByteRTCAudioSampleRate}.
 */
@property(assign, nonatomic) ByteRTCAudioSampleRate sampleRate;
@end

/**
 * @locale zh
 *  @type callback
 *  @brief 音频数据回调观察者<br>
 * 注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。<br>
 * 本接口类中的回调周期均为 20 ms。
 */
/**
 * @locale en
 *  @type callback
 *  @brief Audio data callback observer<br>
 * Note: Callback functions are thrown synchronously in a non-UI thread within the SDK. Therefore, you must not perform any time-consuming operations or direct UI operations within the callback function, as this may cause the app to crash.<br>
 * The time interval for all callback functions in this interface is 20 ms.
 */
@protocol ByteRTCAudioFrameObserver <NSObject>
/**
 * @locale zh
 * @type callback
 * @region 音频数据回调
 * @brief 返回麦克风录制的音频数据
 * @param audioFrame 音频数据, 详见： ByteRTCAudioFrame{@link #ByteRTCAudioFrame}
 */
/**
 * @locale en
 * @type callback
 * @region Audio Data Callback
 * @brief Returns audio data recorded by microphone
 * @param audioFrame Audio data recorded by microphone, see ByteRTCAudioFrame{@link #ByteRTCAudioFrame}
 */
- (void)onRecordAudioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;
/**
 * @locale zh
 * @type callback
 * @region 音频数据回调
 * @brief 返回订阅的所有远端用户混音后的音频数据。
 * @param audioFrame 音频数据, 详见： ByteRTCAudioFrame{@link #ByteRTCAudioFrame}
 */
/**
 * @locale en
 * @type callback
 * @region Audio Data Callback
 * @brief Returns the mixed audio data of all subscribed remote users
 * @param audioFrame Mixed audio data, see ByteRTCAudioFrame{@link #ByteRTCAudioFrame}
 */
- (void)onPlaybackAudioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;
/**
 * @locale zh
 * @type callback
 * @region 音频数据回调
 * @brief 返回远端单个用户的音频数据
 * @param streamKey 远端流信息，参看 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}。
 * @param audioFrame 音频数据，参看 ByteRTCAudioFrame{@link #ByteRTCAudioFrame}。
 * @note 此回调在播放线程调用。不要在此回调中做任何耗时的事情，否则可能会影响整个音频播放链路。
 */
/**
 * @locale en
 * @type callback
 * @region Audio Data Callback
 * @brief Returns the audio data of one remote user.
 * @param streamKey Remote stream information. See ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}.
 * @param audioFrame Audio data. See ByteRTCAudioFrame{@link #ByteRTCAudioFrame}.
 * @note This callback works on the playback thread. Don't do anything time-consuming in this callback, or it may affect the entire audio playback chain.
 */
- (void)onRemoteUserAudioFrame:(ByteRTCRemoteStreamKey * _Nonnull)streamKey
                    audioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;
/**
 * @locale zh
 * @type callback
 * @region 音频数据回调
 * @brief 返回本地麦克风录制和订阅的所有远端用户混音后的音频数据
 * @param audioFrame 音频数据, 详见： ByteRTCAudioFrame{@link #ByteRTCAudioFrame}
 */
/**
 * @locale en
 * @type callback
 * @region Audio Data Callback
 * @brief Returns mixed audio data including both data recorded by the local microphone and data from all subscribed remote users
 * @param audioFrame Mixed audio data, see ByteRTCAudioFrame{@link #ByteRTCAudioFrame}
 */
- (void)onMixedAudioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;
@end

/**
 * @locale zh
 * @type callback
 * @brief 自定义音频处理器<br>
 * 注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。
 */
/**
 * @locale en
 * @type callback
 * @brief  Custom audio processor<br>
 * Note: Callback functions are thrown synchronously in a non-UI thread within the SDK. Therefore, you must not perform any time-consuming operations or direct UI operations within the callback function, as this may cause the app to crash.
 */
@protocol ByteRTCAudioFrameProcessor <NSObject>
/**
 * @locale zh
 * @type callback
 * @brief 回调本地采集的音频帧地址，供自定义音频处理。
 * @param audioFrame 音频帧地址，参看 ByteRTCAudioFrame{@link #ByteRTCAudioFrame}。
 * @note 
 *        + 完成自定义音频处理后，SDK 会对处理后的音频帧进行编码，并传输到远端。此音频处理不会影响软件耳返音频数据。<br>
 *        + 要启用此回调，必须调用 `enableAudioProcessor`，并在参数中选择本地采集的音频，每 10 ms 收到此回调。
 * @return  
 *        + 0： 成功。  <br>
 *        + < 0： 失败。  
 */
/**
 * @locale en
 * @type callback
 * @brief Returns the address of the locally captured audio frame for custom processing.
 * @param audioFrame The address of the audio frame. See ByteRTCAudioFrame{@link #ByteRTCAudioFrame}.
 * @note 
 *        + After custom processing, SDK will encode the processed audio frames and transmit to the remote user. The processing does not affect the SDK-level ear-monitoring audio. <br>
 *        + To enable this callback, call `enableAudioProcessor`. You will receive this callback every 10 ms.
 * @return  
 *        + 0: Success. <br>
 *        + <0: Failure.  
 */
- (int)onProcessRecordAudioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;
/**
* @locale zh
* @type callback
* @brief 回调远端音频混音的音频帧地址，供自定义音频处理。
* @param audioFrame 音频帧地址，参看 ByteRTCAudioFrame{@link #ByteRTCAudioFrame}
* @note 调用 `enableAudioProcessor`,并在参数中选择远端音频流的的混音音频时，每 10 ms 收到此回调。
*/
/**
* @locale en
* @type callback
* @brief Returns the address of the locally captured audio frame for custom processing.
* @param audioFrame The address of the audio frame. See ByteRTCAudioFrame{@link #ByteRTCAudioFrame}
* @note After calling `enableAudioProcessor` with mixed remote audio, you will receive this callback every 10 ms.
*/
- (int)onProcessPlayBackAudioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;
/**
* @locale zh
* @type callback
* @brief 回调单个远端用户的音频帧地址，供自定义音频处理。
* @param streamKey 音频流信息，参看 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
* @param audioFrame 音频帧地址，参看 ByteRTCAudioFrame{@link #ByteRTCAudioFrame}
* @note 调用 `enableAudioProcessor`,并在参数中选择各个远端音频流时，每 10 ms 收到此回调。
*/
/**
* @locale en
* @type callback
* @brief Returns the address of the locally captured audio frame for custom processing.
* @param streamKey Information of the audio stream. See ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
* @param audioFrame The address of the audio frame. See ByteRTCAudioFrame{@link #ByteRTCAudioFrame}
* @note After calling `enableAudioProcessor`, with audio streams of the remote users, you will receive this callback every 10 ms.
*/
- (int)onProcessRemoteUserAudioFrame:(ByteRTCRemoteStreamKey * _Nonnull)streamKey  audioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;
/**
 * @locale zh
 * @valid since 3.50
 * @hidden(macOS)
 * @type callback
 * @brief 软件耳返音频数据的回调。你可根据此回调自定义处理音频。<br>
 *        软件耳返音频中包含通过调用 `setVoiceReverbType:` 和 `setVoiceChangerType:` 设置的音频特效。
 * @param audioFrame 音频帧地址。参看 ByteRTCAudioFrame{@link #ByteRTCAudioFrame}。
 * @note  
 *        + 此数据处理只影响软件耳返音频数据。  <br>
 *        + 要启用此回调，必须调用 enableAudioProcessor:audioFormat:{@link #ByteRTCVideo#enableAudioProcessor:audioFormat:}，并选择耳返音频。每 10 ms 收到此回调。
 * @return  
 *        + 0： 成功。  <br>
 *        + < 0： 失败。  
 */
/**
 * @locale en
 * @valid since 3.50
 * @hidden(macOS)
 * @type callback
 * @brief You will receive the address of SDK-level in-ear monitoring audio frames for custom processing.<br>
 *        The audio effects set by `setVoiceReverbType:` and `setVoiceChangerType:` are included.
 * @param  audioFrame The address of the in-ear monitoring audio frames. See ByteRTCAudioFrame{@link #ByteRTCAudioFrame}.
 * @note 
 *        + Modifying the data affects only SDK-level in-ear monitoring audio.  <br>
 *        + To enable this callback, call enableAudioProcessor:audioFormat:{@link #ByteRTCVideo#enableAudioProcessor:audioFormat:}. You will receive this callback every 10 ms.
 * @return  
 *        + 0: Success. <br>
 *        + <0: Failure.  
 */
- (int)onProcessEarMonitorAudioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;

/**
 * @locale zh
 * @type callback
 * @brief 回调屏幕共享的音频帧地址，供自定义音频处理。
 * @param audioFrame 音频帧地址，参看 ByteRTCAudioFrame{@link #ByteRTCAudioFrame}。
 * @note 调用 `enableAudioProcessor:`，把返回给音频处理器的音频类型设置为屏幕共享音频后，每 10 ms 收到此回调。
 */
/**
 * @locale en
 * @type callback
 * @brief Returns the address of the shared-screen audio frames for custom processing.
 * @param audioFrame The address of audio frames. See ByteRTCAudioFrame{@link #ByteRTCAudioFrame}.
 * @note After calling `enableAudioProcessor:` to set the audio input to the shared-screen audio, you will receive this callback every 10 ms.
 */
- (int)onProcessScreenAudioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;
@end

#pragma mark - AudioDeviceManager

/**
 * @locale zh
 * @hidden for internal use only
 * @type callback
 * @region 音频管理
 * @brief 音频设备事件回调
 */
/**
 * @locale en
 * @hidden for internal use only
 * @type callback
 * @region audio management
 * @brief Audio device event callback
 */
BYTERTC_APPLE_EXPORT @protocol ByteRTCAudioDeviceEventHandler<NSObject>
/**
 * @locale zh
 * @type callback
 * @region 音频管理
 * @brief 获得麦克风音量
 * @param volume 音量大小
 */
/**
 * @locale en
 * @type callback
 * @region audio management
 * @brief Get microphone volume
 * @param volume Volume size
 */
- (void)onRecordingAudioVolumeIndication:(int)volume;
@end

/**
 * @locale zh
 * @type api
 * @hidden(iOS)
 * @brief 音频设备管理类
 */
/**
 * @locale en
 * @type api
 * @hidden(iOS)
 * @brief Audio Device Management
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCAudioDeviceManager : NSObject
/**
 * @hidden
 * @type api
 */
- (instancetype _Nonnull )initDeviceManager:(id<ByteRTCAudioDeviceEventHandler> _Nonnull)handler;
/**
 * @locale zh
 * @type api
 * @region 音频设备管理
 * @brief 获取当前系统内音频播放设备列表。
 * @return 所有音频播放设备的列表，参看 ByteRTCDeviceCollection{@link #ByteRTCDeviceCollection}。<br>
 * 等待超时后会返回空列表。超时时间默认为 10 s。建议通过 rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:} 监听到 `ByteRTCMediaDeviceListUpdated` 后，再次调用本接口获取。
 * @note 你可以在收到 rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:} 了解设备变更后，重新调用本接口以获得新的设备列表。<br>

 */
/**
 * @locale en
 * @type api
 * @region  Audio device management
 * @brief  Gets the list of the audio playback devices.
 * @return  The list of all audio playback devices. See ByteRTCDeviceCollection{@link #ByteRTCDeviceCollection}.<br>
 * If a time-out occurs, it returns an empty list. By default, the time-out duration is set to 10 seconds. We recommend to call this API once you get notification of `ByteRTCMediaDeviceListUpdated` via rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:}.
 * @note When receiving rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:} for audio playback device change, you can call this API to get the latest list of audio playback devices.<br>

 */
- (ByteRTCDeviceCollection * _Nonnull)enumerateAudioPlaybackDevices;
/**
 * @locale zh
 * @type api
 * @region 音频设备管理
 * @brief 获取音频采集设备列表。
 * @return 音频采集设备列表。详见 ByteRTCDeviceCollection{@link #ByteRTCDeviceCollection}。<br>
 * 等待超时后会返回空列表。超时时间默认为 10 s。建议通过 rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:} 监听到 `ByteRTCMediaDeviceListUpdated` 后，再次调用本接口获取。
 * @note 你可以在收到 rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:} 了解设备变更后，重新调用本接口以获得新的设备列表。
 */
/**
 * @locale en
 * @type api
 * @region  Audio Device Management
 * @brief  Get the list of audio capture devices. 
 * @return The list of audio capture devices.. See ByteRTCDeviceCollection{@link #ByteRTCDeviceCollection}.<br>
 * If a time-out occurs, it returns an empty list. By default, the time-out duration is set to 10 seconds. We recommend to call this API once you get notification of `ByteRTCMediaDeviceListUpdated` via rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:}.
 * @note When receiving rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:} for device change, you can call this API to get the latest list of audio playback devices.
 */
- (ByteRTCDeviceCollection * _Nonnull)enumerateAudioCaptureDevices;
/**
 * @locale zh
 * @type api
 * @region 音频设备管理
 * @brief 设置音频采集路由是否跟随系统。
 * @param followed <br>
 *        + true: 跟随。此时，调用 setAudioCaptureDevice:{@link #ByteRTCAudioDeviceManager#setAudioCaptureDevice:} 会失败。默认值。<br>
 *        + false: 不跟随系统。此时，可以调用 setAudioCaptureDevice:{@link #ByteRTCAudioDeviceManager#setAudioCaptureDevice:} 进行设置。
 */
/**
 * @locale en
 * @type api
 * @region Audio Facility Management
 * @brief Set the audio capture device to follow the OS default setting or not.
 * @param followed<br>
 *        + true: follow the OS setting. You can not call setAudioCaptureDevice:{@link #ByteRTCAudioDeviceManager#setAudioCaptureDevice:} at the same time. The default value.<br>
 *        + false: do not follow the OS setting. You can call setAudioCaptureDevice:{@link #ByteRTCAudioDeviceManager#setAudioCaptureDevice:} to set the audio capture device.
 */
- (void)followSystemCaptureDevice:(BOOL)followed;
/**
 * @locale zh
 * @type api
 * @region 音频设备管理
 * @brief 设置音频播放路由是否跟随系统。
 * @param followed <br>
 *        + true: 跟随。此时，调用 setAudioPlaybackDevice:{@link #ByteRTCAudioDeviceManager#setAudioPlaybackDevice:} 会失败。默认值。<br>
 *        + false: 不跟随系统。此时，可以调用 setAudioPlaybackDevice:{@link #ByteRTCAudioDeviceManager#setAudioPlaybackDevice:} 进行设置。
 */
/**
 * @locale en
 * @type api
 * @region Audio Facility Management
 * @brief Set the audio playback device to follow the OS default setting or not.
 * @param followed <br>
 *        + true: follow the OS setting. You can not call setAudioPlaybackDevice:{@link #ByteRTCAudioDeviceManager#setAudioPlaybackDevice:} at the same time. The default value.<br>
 *        + false: do not follow the OS setting. You can call setAudioPlaybackDevice:{@link #ByteRTCAudioDeviceManager#setAudioPlaybackDevice:} to set the audio playback device.
 */
- (void)followSystemPlaybackDevice:(BOOL)followed;
/**
 * @locale zh
 * @type api
 * @region 音频设备管理
 * @brief 设置音频播放设备。
 * @param deviceID 音频播放设备 ID，可通过 enumerateAudioPlaybackDevices{@link #ByteRTCAudioDeviceManager#enumerateAudioPlaybackDevices} 获取。
 * @return   
 *        + 0：方法调用成功  <br>
 *        + < 0：方法调用失败  
 * @note 当你调用 followSystemPlaybackDevice:{@link #ByteRTCAudioDeviceManager#followSystemPlaybackDevice:} 设置音频播放设备跟随系统后，将无法调用此接口设置音频播放设备。
 */
/**
 * @locale en
 * @type api
 * @region Audio device management
 * @brief Sets the audio playback device.
 * @param  deviceID Device ID. You can get the ID by calling EnumerateAudioPlaybackDevices{@link #ByteRTCAudioDeviceManager#EnumerateAudioPlaybackDevices}.
 * @return    
 *         + 0: Success <br>
 *         + < 0: Failure 
 * @note After you call followSystemPlaybackDevice:{@link #ByteRTCAudioDeviceManager#followSystemPlaybackDevice:} to set the audio playback device to follow the system setting, you cannot call this API to set the audio playback device.
 */
- (int)setAudioPlaybackDevice:(NSString * _Nonnull)deviceID;
/**
 * @locale zh
 * @type api
 * @region 音频设备管理
 * @brief 获取当前音频播放设备。
 * @param deviceID 设备 ID
 * @return  方法调用结果  <br>
 *        + 0：方法调用成功  <br>
 *        + < 0：方法调用失败  
 */
/**
 * @locale en
 * @type api
 * @region Audio Device Management
 * @brief Gets the current audio playback device.
 * @param  deviceID audio playback device ID
 * @return   Method call result   <br>
 *         + 0: Success. <br>
 *         + < 0: failure 
 */
- (int)getAudioPlaybackDevice:(NSString * _Nonnull * _Nonnull) deviceID;
/**
 * @locale zh
 * @type api
 * @region 音频设备管理
 * @brief 设置音频采集设备。
 * @param deviceID 音频采集设备 ID。你可调用 enumerateAudioCaptureDevices{@link #ByteRTCAudioDeviceManager#EnumerateAudioCaptureDevices} 获取可用设备列表。
 * @return  方法调用结果  <br>
 *        + 0：方法调用成功  <br>
 *        + < 0：方法调用失败  
 * @note 当你调用 followSystemCaptureDevice:{@link #ByteRTCAudioDeviceManager#followSystemCaptureDevice:} 设置音频采集设备跟随系统后，将无法调用此接口设置音频采集设备。
 */
/**
 * @locale en
 * @type api
 * @region Audio Device Management
 * @brief Set the audio capture devices.
 * @param  deviceID Audio capture device ID. You can get the device list by calling enumerateAudioCaptureDevices{@link #ByteRTCAudioDeviceManager#EnumerateAudioCaptureDevices}.
 * @return   Method call result   <br>
 *         + 0: Success. <br>
 *         + < 0: failure 
 * @note After you call followSystemCaptureDevice:{@link #ByteRTCAudioDeviceManager#followSystemCaptureDevice:} to set the audio playback device to follow the system setting, you cannot call this API to set the audio capture device.
 */
- (int)setAudioCaptureDevice:(NSString * _Nonnull)deviceID;
/**
 * @locale zh
 * @type api
 * @region 音频设备管理
 * @brief 获取当前音频采集设备。
 * @param deviceID 音频采集设备 ID。
 * @return  方法调用结果  <br>
 *        + 0：方法调用成功  <br>
 *        + < 0：方法调用失败  
 */
/**
 * @locale en
 * @type api
 * @region Audio Device Management
 * @brief Gets the current audio capture device.
 * @param deviceID audio capture device ID.
 * @return  Method call result   <br>
 *         + 0: Success. <br>
 *         + < 0: failure 
 */
- (int)getAudioCaptureDevice:(NSString *_Nonnull * _Nonnull) deviceID;
/**
 * @locale zh
 * @type api
 * @region 音频设备管理
 * @brief 设置当前音频采集设备静音状态，默认为非静音。
 * @param mute  <br>
 *       + true：静音  <br>
 *       + false：非静音  
 * @return  方法调用结果  <br>
 *        + 0：方法调用成功  <br>
 *        + < 0：方法调用失败  
 */
/**
 * @locale en
 * @type api
 * @region Audio Device Management
 * @brief Set the mute state of the current audio capture device. It's not mute by default.
 * @param  mute <br>
 *        + true: Mute <br>
 *        + false: Speaking
 * @return   Method call result   <br>
 *         + 0: Success. <br>
 *         + < 0: failure 
 */
- (int) setAudioCaptureDeviceMute:(bool)mute;
/**
 * @locale zh
 * @type api
 * @region 音频设备管理
 * @brief 获取当前音频采集设备是否静音的信息。
 * @param mute  <br>
 *       + true：静音  <br>
 *       + false：非静音  
 * @return  方法调用结果  <br>
 *        + 0：方法调用成功  <br>
 *        + < 0：方法调用失败  
 */
/**
 * @locale en
 * @type api
 * @region Audio Device Management
 * @brief Gets information about the mute state of the current audio capture device.
 * @param  mute <br>
 *        + true: Mute <br>
 *        + false: Speaking
 * @return   Method call result   <br>
 *         + 0: Success. <br>
 *         + < 0: failure 
 */
- (int) getAudioCaptureDeviceMute:(bool * _Nonnull)mute;
/**
 * @locale zh
 * @type api
 * @region 音频设备管理
 * @brief 设置当前音频播放设备静音状态，默认为非静音。
 * @param mute  <br>
 *       + true：静音  <br>
 *       + false：非静音  
 * @return  方法调用结果  <br>
 *        + 0：方法调用成功  <br>
 *        + < 0：方法调用失败  
 */
/**
 * @locale en
 * @type api
 * @region Audio Device Management
 * @brief Set the mute state of the current audio playback device. It's not mute by default.
 * @param  mute <br>
 *        + true: Mute <br>
 *        + false: Speaking
 * @return   Method call result   <br>
 *         + 0: Success. <br>
 *         + < 0: failure 
 */
- (int) setAudioPlaybackDeviceMute:(bool)mute;
/**
 * @locale zh
 * @type api
 * @region 音频设备管理
 * @brief 获取当前音频播放设备是否静音的信息。
 * @param mute  <br>
 *       + true：静音  <br>
 *       + false：非静音  
 * @return  方法调用结果  <br>
 *        + 0：方法调用成功  <br>
 *        + < 0：方法调用失败  
 */
/**
 * @locale en
 * @type api
 * @region Audio Device Management
 * @brief Get the mute state of the current audio playback device.
 * @param  mute <br>
 *        + true: Mute <br>
 *        + false: Speaking
 * @return   Method call result   <br>
 *         + 0: Success. <br>
 *         + < 0: failure 
 */
- (int) getAudioPlaybackDeviceMute:(bool * _Nonnull)mute;
/**
 * @locale zh
 * @type api
 * @region 音频设备管理
 * @brief 设置当前音频采集设备音量
 * @param volume 音频采集设备音量，取值范围为 [0,255]。<br>
 *       + [0,25] 接近无声；  <br>
 *       + [25,75] 为低音量；  <br>
 *       + [76,204] 为中音量；  <br>
 *       + [205,255] 为高音量。  
 * @return  方法调用结果  <br>
 *        + 0：方法调用成功  <br>
 *        + < 0：方法调用失败  
 */
/**
 * @locale en
 * @type api
 * @region  Audio Device Management
 * @brief Set the current audio capture device volume
 * @param  volume Audio capture device volume. The range is [0,255]. <br>
 *        + [0,25]: nearly silent; <br>
 *        + [25,75]: low volume; <br>
 *        + [76,204]: medium volume; <br>
 *        + [205,255]: high volume. 
 * @return   Method call result   <br>
 *         + 0: Success. <br>
 *         + < 0: failure 
 */
- (int) setAudioCaptureDeviceVolume:(unsigned int)volume;
/**
 * @locale zh
 * @type api
 * @region 音频设备管理
 * @brief 获取当前音频采集设备音量
 * @param volume 音频采集设备音量，取值范围是 [0,255]<br>
 *       + [0,25] 接近无声；  <br>
 *       + [25,75] 为低音量；  <br>
 *       + [76,204] 为中音量；  <br>
 *       + [205,255] 为高音量。  
 * @return  方法调用结果  <br>
 *        + 0：方法调用成功  <br>
 *        + < 0：方法调用失败  
 */
/**
 * @locale en
 * @type api
 * @region Audio Device Management
 * @brief Get the current audio capture device volume.
 * @param  volume Audio capture device volume. The range is [0,255]. <br>
 *        + [0,25]: nearly silent; <br>
 *        + [25,75]: low volume; <br>
 *        + [76,204]: medium volume; <br>
 *        + [205,255]: high volume. 
 * @return   Method call result   <br>
 *         + 0: Success. <br>
 *         + < 0: failure 
 */
- (int) getAudioCaptureDeviceVolume:(unsigned int * _Nonnull)volume;
/**
 * @locale zh
 * @type api
 * @region 音频设备管理
 * @brief 设置当前音频播放设备音量
 * @param volume 音频播放设备音量，取值范围为 [0,255]<br>
 *       + [0,25] 接近无声；  <br>
 *       + [25,75] 为低音量；  <br>
 *       + [76,204] 为中音量；  <br>
 *       + [205,255] 为高音量。  
 * @return  方法调用结果  <br>
 *        + 0：方法调用成功  <br>
 *        + < 0：方法调用失败  
 */
/**
 * @locale en
 * @type api
 * @region Audio Device Management
 * @brief Set the current audio playback device volume.
 * @param  volume Audio playback device volume. The range is [0,255]. <br>
 *        + [0,25]: nearly silent; <br>
 *        + [25,75]: low volume; <br>
 *        + [76,204]: medium volume; <br>
 *        + [205,255]: high volume. 
 * @return   Method call result   <br>
 *         + 0: Success. <br>
 *         + < 0: failure 
 */
- (int) setAudioPlaybackDeviceVolume:(unsigned int)volume;
/**
 * @locale zh
 * @type api
 * @region 音频设备管理
 * @brief 获取当前音频播放设备音量
 * @param volume 音频播放设备音量，取值范围是 [0,255] <br>
 *       + [0,25] 接近无声；  <br>
 *       + [25,75] 为低音量；  <br>
 *       + [76,204] 为中音量；  <br>
 *       + [205,255] 为高音量。  
 * @return  方法调用结果  <br>
 *        + 0：方法调用成功  <br>
 *        + < 0：方法调用失败  
 */
/**
 * @locale en
 * @type api
 * @region Audio Device Management
 * @brief Get the current audio playback device volume.
 * @param  volume Audio playback device volume. The range is [0,255]. <br>
 *        + [0,25]: nearly silent; <br>
 *        + [25,75]: low volume; <br>
 *        + [76,204]: medium volume; <br>
 *        + [205,255]: high volume. 
 * @return   Method call result   <br>
 *         + 0: Success. <br>
 *         + < 0: failure 
 */
- (int) getAudioPlaybackDeviceVolume:(unsigned int * _Nonnull)volume;
/**
 * @locale zh
 * @type api
 * @region 音频设备管理
 * @brief 启动音频播放设备测试。  <br>
 *        该方法测试播放设备是否能正常工作。SDK 播放指定的音频文件，测试者如果能听到声音，说明播放设备能正常工作。
 * @param testAudioFilePath 音频文件的绝对路径，路径字符串使用 UTF-8 编码格式，支持以下音频格式: mp3，aac，m4a，3gp，wav。
 * @param interval 音频设备播放测试音量回调的间隔
 * @return  方法调用结果  <br>
 *        + 0：方法调用成功  <br>
 *        + < 0：方法调用失败  
 * @note  
 *       + 该方法必须在进房前调用，且不可与其它音频设备测试功能同时应用。  <br>
 *       + 调用 stopAudioPlaybackDeviceTest{@link #ByteRTCAudioDeviceManager#stopAudioPlaybackDeviceTest} 停止测试。  
 */
/**
 * @locale en
 * @type api
 * @region Audio Device Management
 * @brief Start the audio playback device test.   <br>
 *        This method tests whether the playback device works properly. The SDK plays the specified audio file. If the tester can hear the sound, the playback device can work normally.
 * @param  testAudioFilePath The absolute path of the audio file. The path string uses UTF-8 encoding format and supports the following audio formats: mp3, aac, m4a, 3gp, wav.
 * @param  interval playback device test volume callback interval
 * @return  Method call result   <br>
 *         + 0: Success. <br>
 *         + < 0: failure 
 * @note   
 *        + This method must be called before joining the room and cannot be applied at the same time as other audio device testing functions. <br>
 *        + Call stopAudioPlaybackDeviceTest{@link #ByteRTCAudioDeviceManager#stopAudioPlaybackDeviceTest} to stop the test. 
 */
- (int)startAudioPlaybackDeviceTest:(NSString *_Nonnull)testAudioFilePath interval:(int)interval;
/**
 * @locale zh
 * @type api
 * @region 音频设备管理
 * @brief 停止音频播放设备测试。
 * @return  方法调用结果  <br>
 *        + 0：方法调用成功  <br>
 *        + < 0：方法调用失败  
 * @note  调用 startAudioPlaybackDeviceTest:interval:{@link #ByteRTCAudioDeviceManager#startAudioPlaybackDeviceTest:interval:} 后，需调用本方法停止测试。
 */
/**
 * @locale en
 * @type api
 * @region Audio Device Management
 * @brief Stop audio playback device testing.
 * @return  Method call result   <br>
 *         + 0: Success. <br>
 *         + < 0: failure 
 * @note  After calling startAudioPlaybackDeviceTest:interval:{@link #ByteRTCAudioDeviceManager#startAudioPlaybackDeviceTest:interval:}, call this method to stop the test.
 */
- (int)stopAudioPlaybackDeviceTest;
/**
 * @locale zh
 * @hidden(iOS)
 * @type api
 * @region 音频设备管理
 * @brief 开始音频采集设备和音频播放设备测试。
 * @param interval 测试中会收到 `rtcEngine:onLocalAudioPropertiesReport:` 回调，本参数指定了该周期回调的时间间隔，单位为毫秒。建议设置到大于 200 毫秒。最小不得少于 10 毫秒。
 * @return  方法调用结果  <br>
 *       + 0：方法调用成功  <br>
 *       + < 0：方法调用失败  
 * @note  
 *       + 该方法在进房前后均可调用。且不可与其它音频设备测试功能同时应用。  <br>
 *       + 调用本接口 30 s 后，采集自动停止，并开始播放采集到的声音。录音播放完毕后，设备测试流程自动结束。你也可以在 30 s 内调用 stopAudioDeviceRecordAndPlayTest{@link #ByteRTCAudioDeviceManager#stopAudioDeviceRecordAndPlayTest}  来停止采集并开始播放此前采集到的声音。<br>
 *       + 调用 stopAudioDevicePlayTest{@link #ByteRTCAudioDeviceManager#stopAudioDevicePlayTest} 可以停止音频设备采集和播放测试。<br>
 *       + 你不应在测试过程中，调用 `enableAudioPropertiesReport:` 注册音量提示回调。<br>
 *       + 该方法仅在本地进行音频设备测试，不涉及网络连接。  
 */
/**
 * @locale en
 * @hidden(iOS)
 * @type api
 * @region Audio Facility Management
 * @brief Start the capture and playback test for local audio devices.
 * @param interval During the test, you'll receive `rtcEngine:onLocalAudioPropertiesReport:` periodically. Set the period in ms with this parameter. Recommended value is 200 ms; the minimal value is 10 ms.
 * @return  result<br>
 *         + 0: success  <br>
 *         + < 0: failure  
 * @note  
 *       + The audio capturing stops in 30s after calling this API and begins to play the recording audio. Before that, you can call stopAudioDeviceRecordAndPlayTest{@link #ByteRTCAudioDeviceManager#stopAudioDeviceRecordAndPlayTest} to stop audio capturing and start playing the recording audio. <br>
 *       + Call stopAudioDevicePlayTest{@link #ByteRTCAudioDeviceManager#stopAudioDevicePlayTest} to stop the test, including capturing and playing the recording. <br>
 *       + You must stop the test before starting another test for audio devices. <br>
 *       + You must stop the test before calling `enableAudioPropertiesReport:`. <br>
 *       + This test performs locally and does not involve network connection testing. 
 */
- (int)startAudioDeviceRecordTest:(int)interval;
/**
 * @locale zh
 * @hidden(iOS)
 * @type api
 * @region 音频设备管理
 * @brief 停止采集本地音频，并开始播放采集到的声音。录音播放完毕后，设备测试流程结束。<br>
 * 调用 startAudioDeviceRecordTest:{@link #ByteRTCAudioDeviceManager#startAudioDeviceRecordTest:} 30s 内调用本接口来停止采集并开始播放此前采集到的声音。
 * @return  方法调用结果  <br>
 *        + 0：方法调用成功  <br>
 *        + < 0：方法调用失败  
 * @note  
 *        + 该方法依赖 rtc 引擎，只有通过成员方法getAudioDeviceManager{@link #ByteRTCVideo#getAudioDeviceManager}创建的ByteRTCAudioDeviceManager，该方法才是有效的 <br>
 *        + 调用本接口开始播放录音后，可以在播放过程中调用 stopAudioDevicePlayTest{@link #ByteRTCAudioDeviceManager#stopAudioDevicePlayTest} 停止播放。
 */
/**
 * @locale en
 * @hidden(iOS)
 * @type api
 * @region Audio Facility Management
 * @brief Call this API to stop recording in the test and start to play the recording in 30 s after calling startAudioDeviceRecordTest:{@link #ByteRTCAudioDeviceManager#startAudioDeviceRecordTest:}.
 * @return result<br>
 *         + 0: success  <br>
 *         + < 0: failure  
 * @note     
 *         + This method do rely on rtcEngine, this method only will be Effective when ByteRTCAudioDeviceManager created by getAudioDeviceManager{@link #ByteRTCVideo#getAudioDeviceManager} <br>
 *         + After calling this API, the recording starts playing during which you can call stopAudioDevicePlayTest{@link #ByteRTCAudioDeviceManager#stopAudioDevicePlayTest} to stop playing.
 */
- (int)stopAudioDeviceRecordAndPlayTest;
/**
 * @locale zh
 * @hidden(iOS)
 * @type api
 * @region 音频设备管理
 * @brief 停止由调用 startAudioDeviceRecordTest:{@link #ByteRTCAudioDeviceManager#startAudioDeviceRecordTest:} 开始的音频播放设备测试。<br>
 *        在音频播放设备测试自动结束前，可调用本接口停止音频采集与播放测试。
 * @return  方法调用结果  <br>
 *        + 0：方法调用成功  <br>
 *        + < 0：方法调用失败
 * @note  
 *        + 该方法依赖 rtc 引擎，只有通过成员方法getAudioDeviceManager{@link #ByteRTCVideo#getAudioDeviceManager}创建的ByteRTCAudioDeviceManager，该方法才是有效的 
 */
/**
 * @locale en
 * @hidden(iOS)
 * @type api
 * @region Audio Facility Management
 * @brief Stop the capture and playback test for local audio devices which is started by calling startAudioDeviceRecordTest:{@link #ByteRTCAudioDeviceManager#startAudioDeviceRecordTest:}.<br>
 * Before the test ends by itself, you can call this API to stop the recording or playing.
 * @return 
 *         + 0: success  <br>
 *         + < 0: failure
 * @note     
 *         + This method do rely on rtcEngine, this method only will be Effective when ByteRTCAudioDeviceManager created by getAudioDeviceManager{@link #ByteRTCVideo#getAudioDeviceManager} 
 */
- (int)stopAudioDevicePlayTest;
/**
 * @locale zh
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
 *        + -5: 其它原因错误 
 * @note  
 *        + 该接口需在进房前调用；  <br>
 *        + 检测成功不代表设备一定可以启动成功，还可能因设备被其他应用进程独占，或 CPU/内存不足等原因导致启动失败。 
 */
/**
 * @locale en
 * @type api
 * @region Audio Device Management
 * @brief Try to initialize the audio playback device for device test.
 * @param deviceID Device ID
 * @return Device status error code: <br>
 *         + 0: Status normal.  <br>
 *         + -1: Test not executed. <br>
 *         + -2: Init failed due to lack of permission. <br>
 *         + -3: The device does not exist. No device or device removed. <br>
 *         + -4: The audio format is not supported. <br>
 *         + -5: Error for other reasons
 * @note  
 *        + Call this API before the user joins the room. <br>
 *        + You may still fail to enable the device even you passed the test. Occupation by other application or shortage of CPU / memory may cause the failure.
 */
- (int)initAudioPlaybackDeviceForTest:(NSString * _Nonnull)deviceID;
/**
 * @locale zh
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
 *        + -5: 其它原因错误 
 * @note  
 *        + 该接口需在进房前调用；  <br>
 *        + 检测成功不代表设备一定可以启动成功，还可能因设备被其他应用进程独占，或 CPU/内存不足等原因导致启动失败。 
 */
/**
 * @locale en
 * @type api
 * @region Audio Device Management
 * @brief Try to initialize the audio capture device for device test.
 * @param deviceID device ID
 * @return Device status error code: <br>
 *         + 0: Status normal.  <br>
 *         + -1: Test not executed. <br>
 *         + -2: Init failed due to lack of permission. <br>
 *         + -3: The device does not exist. No device or device removed. <br>
 *         + -4: The audio format is not supported. <br>
 *         + -5: Error for other reasons
 * @note  
 *        + Call this API before joining the room; <br>
 *        + You may still fail to enable the device even you passed the test. Occupation by other application or shortage of CPU / memory may cause the failure.
 */
- (int)initAudioCaptureDeviceForTest:(NSString * _Nonnull)deviceID;
/**
 * @locale zh
 * @type api
 * @deprecated since 3.45 and will be deleted in 3.51.
 * @region 音频设备管理
 * @brief 切换音频播放到扬声器或者听筒，默认播放设备是扬声器
 * @param enable  <br>
 *       + true：切换至扬声器  <br>
 *       + false：切换至听筒  
 * @note 本方法只在移动设备上有效
 */
/**
 * @locale en
 * @type api
 * @deprecated since 3.45 and will be deleted in 3.51.
 * @region Audio Device Management
 * @brief Switch audio playback device to the speaker or the earpiece. The default playback device is the speaker.
 * @param  enable <br>
 *        + true: switch to the speaker <br>
 *        + false: switch to the earpiece 
 * @note This method is only valid on mobile devices.
 */
- (void)setEnableSpeakerphone:(bool)enable;

/**
 * @locale zh
 * @type api
 * @region 音频设备管理
 * @brief 启动音频采集设备测试。  <br>
 *        该方法测试音频采集设备是否能正常工作。启动测试后，会收到 rtcEngine:onLocalAudioPropertiesReport:{@link #ByteRTCVideoDelegate#rtcEngine:onLocalAudioPropertiesReport:} 回调上报的音量信息。
 * @param indicationInterval 获取回调的时间间隔，单位为毫秒。建议设置到大于 200 毫秒。最小不得少于 10 毫秒。小于10 毫秒行为未定义。
 * @return  方法调用结果  <br>
 *        + 0：方法调用成功  <br>
 *        + < 0：方法调用失败  
 * @note  
 *       + 该方法不依赖 rtc 引擎 <br>
 *       + 该方法必须在进房前调用，且不可与其它音频设备测试功能同时应用。  <br>
 *       + 你需调用 stopAudioRecordingDeviceTest{@link #ByteRTCAudioDeviceManager#stopAudioRecordingDeviceTest} 停止测试。  
 */
/**
 * @locale en
 * @type api
 * @region Audio Device Management
 * @brief Start the audio capture device test.   <br>
 *        This method tests whether the audio capture device can work properly. After starting the test, you will receive the volume information reported by rtcEngine:onLocalAudioPropertiesReport:{@link #ByteRTCVideoDelegate#rtcEngine:onLocalAudioPropertiesReport:}.
 * @param  indicationInterval The interval of receiving callbacks. It is recommended to set to no less than 200 ms. The minimum is 10 ms.
 * @return  Method call result   <br>
 *         + 0: Success. <br>
 *         + < 0: failure 
 * @note   
 *        + This method do not rely on rtcEngine <br>
 *        + This method must be called before joining the room and cannot be applied at the same time as other audio device testing functions. <br>
 *        + You need to call stopAudioRecordingDeviceTest{@link #ByteRTCAudioDeviceManager#stopAudioRecordingDeviceTest} to stop the test. 
 */
- (int)startAudioRecordingDeviceTest:(unsigned int)indicationInterval;
/**
 * @locale zh
 * @type api
 * @region 音频设备管理
 * @brief 停止音频采集设备测试。
 * @return  方法调用结果  <br>
 *        + 0：方法调用成功  <br>
 *        + < 0：方法调用失败  
 * @note  
 *        + 该方法不依赖 rtc 引擎 <br>
 *        + 调用 startAudioRecordingDeviceTest:{@link #ByteRTCAudioDeviceManager#startAudioRecordingDeviceTest:} 后，需调用本方法停止测试。 
 */
/**
 * @locale en
 * @type api
 * @region Audio Device Management
 * @brief Stop audio capture device testing.
 * @return  Method call result   <br>
 *         + 0: Success. <br>
 *         + < 0: failure 
 * @note  
 *         + This method do not rely on rtcEngine <br>
 *         +After calling startAudioRecordingDeviceTest:{@link #ByteRTCAudioDeviceManager#startAudioRecordingDeviceTest:}, you must call this method to stop the test. 
 */
- (int)stopAudioRecordingDeviceTest;
/**
 * @locale zh
 * @type api
 * @region 音频设备管理
 * @brief 开始音频设备回路测试。  <br>
 *        该方法测试音频采集设备和音频播放设备是否能正常工作。一旦测试开始，音频采集设备会采集本地声音并通过音频播放设备播放出来，同时会收到 rtcEngine:onLocalAudioPropertiesReport:{@link #ByteRTCVideoDelegate#rtcEngine:onLocalAudioPropertiesReport:}。
 * @param indicationInterval 收到回调的时间间隔，单位为 ms。建议设置到大于 200 ms。最小不得少于 10 ms。
 * @return  方法调用结果  <br>
 *        + 0：方法调用成功  <br>
 *        + < 0：方法调用失败  
 * @note  
 *       + 该方法不依赖 rtc 引擎 <br>
 *       + 该方法必须在进房前调用。且不可与其它音频设备测试功能同时应用。  <br>
 *       + 你需调用 stopAudioDeviceLoopbackTest{@link #ByteRTCAudioDeviceManager#stopAudioDeviceLoopbackTest} 停止测试。  <br>
 *       + 该方法仅在本地进行音频设备测试，不涉及网络连接。  
 */
/**
 * @locale en
 * @type api
 * @region Audio Device Management
 * @brief Begins audio device loop testing.   <br>
 *        This method tests whether the audio capture device and the audio playback device can work normally. Once the test starts, the audio capture device will capture the local sound<br>
 *         And play it out through the audio playback device, and the user App will receive the volume information reported by the `OnLocalAudioPropertiesReport` callback.
 * @param  indicationInterval The time interval of receiving callbacks in ms. It is recommended to set to no less than 200 ms. The minimum is 10 ms.
 * @return   Method call result   <br>
 *         + 0: Success. <br>
 *         + < 0: failure 
 * @note   
 *        + This method do not rely on rtcEngine  <br>
 *        + This method must be called before joining the room. And cannot be applied at the same time as other audio equipment test functions. <br>
 *        + You need to call stopAudioDeviceLoopbackTest{@link #ByteRTCAudioDeviceManager#stopAudioDeviceLoopbackTest} to stop the test. <br>
 *        + This method only tests audio equipment locally and does not involve network connection. 
 */
- (int)startAudioDeviceLoopbackTest:(unsigned int)indicationInterval;
/**
 * @locale zh
 * @type api
 * @region 音频设备管理
 * @brief 停止音频设备回路测试。
 * @return  方法调用结果  <br>
 *        + 0：方法调用成功  <br>
 *        + < 0：方法调用失败  
 * @note   
 *        + 该方法不依赖 rtc 引擎 <br>
 *        + 调用 startAudioDeviceLoopbackTest:{@link #ByteRTCAudioDeviceManager#startAudioDeviceLoopbackTest:} 后，需调用本方法停止测试。
 */
/**
 * @locale en
 * @type api
 * @region Audio Device Management
 * @brief Stop audio device loop testing.
 * @return  Method call result   <br>
 *         + 0: Success. <br>
 *         + < 0: failure 
 * @note     
 *         + This method do not rely on rtcEngine  <br>
 *         + After calling startAudioDeviceLoopbackTest:{@link #ByteRTCAudioDeviceManager#startAudioDeviceLoopbackTest:}, you need to call this method to stop the test. 
 */
- (int)stopAudioDeviceLoopbackTest;
@end

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
BYTERTC_APPLE_EXPORT @interface ByteRTCASRConfig : NSObject
/**
 * @locale zh
 *  @brief 应用 ID
 */
/**
 * @locale en
 *  @brief Application ID
 */
@property(copy, nonatomic) NSString *_Nonnull appId;
/**
 * @locale zh
 *  @brief 用户 ID
 */
/**
 * @locale en
 *  @brief User ID
 */
@property(copy, nonatomic) NSString *_Nonnull userId;
/**
 * @locale zh
 *  @brief 访问令牌
 */
/**
 * @locale en
 *  @brief Access token
 */
@property(copy, nonatomic) NSString *_Nonnull accessToken;
/**
 * @locale zh
 *  @brief 私钥。Signature 鉴权模式下不能为空，token 鉴权模式下为空。参看[关于鉴权](https://www.volcengine.com/docs/6561/107789)
 */
/**
 * @locale en
 * @brief Private key. Signature  cannot be empty in authentication mode, and it is empty in token authentication mode. See [Authentication Method](https://docs.byteplus.com/speech/docs/authentication-method).
 */
@property(copy, nonatomic) NSString *_Nonnull secretKey;
/**
 * @locale zh
 *  @brief 场景信息，参看[业务集群](https://www.volcengine.com/docs/6561/80818#_3-2-2-%E5%8F%91%E9%80%81-full-client-request)
 */
/**
 * @locale en
 *  @brief For scenario information. See Business Clusters (https://docs.byteplus.com/en/speech/docs/real-time-speech-recog)
 */
@property(copy, nonatomic) NSString *_Nonnull cluster;
/**
 * @locale zh
 *  @brief 鉴权模式，参看 ByteRTCASRAuthorizationType{@link #ByteRTCASRAuthorizationType}
 */
/**
 * @locale en
 *  @brief Authentication mode. See ByteRTCASRAuthorizationType{@link #ByteRTCASRAuthorizationType}
 */
@property(assign, nonatomic) ByteRTCASRAuthorizationType authorizationType;
@end

#pragma mark - ByteASREventHandler

/**
 * @locale zh
 * @hidden(macOS)
 * @type callback
 * @brief 语音识别服务使用状态回调<br>
 * 注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。
 */
/**
 * @locale en
 * @hidden currently not available
 * @type callback
 * @brief Speech recognition service usage status callback<br>
 * Note: Callback functions are thrown synchronously in a non-UI thread within the SDK. Therefore, you must not perform any time-consuming operations or direct UI operations within the callback function, as this may cause the app to crash.
 */
BYTERTC_APPLE_EXPORT @protocol ByteRTCASREngineEventHandler<NSObject>
@required
/**
 * @locale zh
 * @type callback
 * @brief 语音识别服务开启成功回调
 */
/**
 * @locale en
 * @type callback
 * @brief  Speech recognition service starts successful callback
 */
- (void)onSuccess;
@required
/**
 * @locale zh
 * @type callback
 * @brief 语音转文字成功回调，该回调返回识别后的全量消息。
 * @param message 识别完成后得到的文字消息
 * @note 若识别过程中发生了网络连接中断，则重连后回调的信息中只包含重连后识别的文字消息，不再包含上一次连接后识别的消息。
 */
/**
 * @locale en
 * @type callback
 * @brief The voice-to-text callback is successful, and the callback returns the full amount of messages after recognition.
 * @param message Text message obtained after the recognition is completed
 * @note If the network connection is interrupted during the recognition process, the callback information after reconnection contains only the text message recognized after reconnection, and no longer contains the message recognized after the last connection.
 */
- (void)onMessage:(NSString *_Nonnull)message;
@required
/**
 * @locale zh
 * @type callback
 * @brief 当语音识别服务内部发生错误事件时触发该回调。
 * @param errorCode 错误码  <br>
 *        + < 0: 参数错误或 API 调用顺序错误，参看 ByteRTCASRErrorCode{@link #ByteRTCASRErrorCode}；  <br>
 *        + >0: 参看 [语音识别服务错误码](https://www.volcengine.com/docs/6561/80818#_3-3-%E9%94%99%E8%AF%AF%E7%A0%81)
 * @param errorMessage 错误原因说明
 */
/**
 * @locale en
 * @type callback
 * @brief This callback is triggered when an error event occurs within the speech recognition service.
 * @param errorCode Error code <br>
 *         + < 0: Parameter error or API call order error. See ByteRTCASRErrorCode{@link #ByteRTCASRErrorCode}; <br>
 *         + > 0: See [speech recognition service error code](https://docs.byteplus.com/en/speech/docs/real-time-speech-recog#bbbf89f6)
 * @param errorMessage Error reason description
 */
- (void)onError:(NSInteger)errorCode withErrorMessage:(NSString *_Nonnull)errorMessage;
@end

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
BYTERTC_APPLE_EXPORT @interface ByteRTCAudioMixingConfig : NSObject
/**
 * @locale zh
 * @brief 混音播放类型，详见 ByteRTCAudioMixingType{@link #ByteRTCAudioMixingType}
 */
/**
 * @locale en
 * @brief Mix playback type. See ByteRTCAudioMixingType{@link #ByteRTCAudioMixingType}
 */
@property(assign, nonatomic) ByteRTCAudioMixingType type;
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
@property(assign, nonatomic) NSInteger playCount;
/**
 * @locale zh
 * @brief 混音时音频文件播放进度条位置，参数为整数，单位为毫秒
 */
/**
 * @locale en
 * @brief The position of the audio file playback progress bar during audio mixing, the parameter should be an integer, in milliseconds.
 */
@property(assign, nonatomic) NSInteger position;
/**
 * @locale zh
 * @brief 设置音频文件播放进度回调的时间间隔，参数为为大于 0 的 10 的倍数，单位为毫秒，设置后 SDK 将按照设置的值触发 `rtcEngine:onAudioMixingPlayingProgress:progress:` 回调，默认不回调。  <br>
 *        + 当传入的值不能被 10 整除时，则默认向上取整 10，如设为 52ms 时会默认调整为 60ms。  <br>
 *        + 当传入的值小于等于 0 时，不会触发进度回调。  
 */
/**
 * @locale en
 * @brief Set the time interval (ms) for the audio file playing progress callback. The `rtcEngine:onAudioMixingPlayingProgress:progress:` callback then will be triggered according to the set value, no callback by default.  <br>
 *       + The value of interval is a multiple of 10 greater than 0. When the value set is not divisible by 10, the default is rounded up by 10. For example, if the value is set to 52ms, it will be automatically adjusted to 60ms.  <br>
 *       + If the value is less than or equals to 0, the callback will not be triggered.  
 */
@property(assign, nonatomic) NSInteger callbackOnProgressInterval;
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
@property(assign, nonatomic) BOOL syncProgressToRecordFrame;
@end
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
BYTERTC_APPLE_EXPORT @interface ByteRTCAudioEffectPlayerConfig : NSObject
/**
 * @locale zh
 * @brief 混音播放类型，详见 ByteRTCAudioMixingType{@link #ByteRTCAudioMixingType} 
 */ 
/**
 * @locale en
 * @brief Mixing playback types. See ByteRTCAudioMixingType{@link #ByteRTCAudioMixingType}
 */
@property(assign, nonatomic) ByteRTCAudioMixingType type;
/**
 * @locale zh
 * @brief 与音乐文件原始音调相比的升高/降低值，取值范围为 `[-12，12]`，默认值为 0。每相邻两个值的音高距离相差半音，正值表示升调，负值表示降调。
 */
/**
 * @locale en
 * @brief The increase or decrease value compared with the original pitch of the music file. The range is `[-12, 12]`. The default value is 0. The pitch distance between two adjacent values is half a step. A positive value indicates a rising pitch, and a negative value indicates a falling pitch.
*/
@property(assign, nonatomic) NSInteger pitch;
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
@property(assign, nonatomic) NSInteger playCount;
/**
 * @locale zh
 * @brief 混音起始位置。默认值为 0，单位为毫秒。
 */
/**
 * @locale en
 * @brief The starting position in ms. 0 by default.
 */
@property(assign, nonatomic) NSInteger startPos;
@end
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
BYTERTC_APPLE_EXPORT @interface ByteRTCMediaPlayerConfig : NSObject
/**
 * @locale zh
 * @brief 混音播放类型，详见 ByteRTCAudioMixingType{@link #ByteRTCAudioMixingType}
 */
/**
 * @locale en
 * @brief For mixing playback types. See ByteRTCAudioMixingType{@link #ByteRTCAudioMixingType}
 */
@property(assign, nonatomic) ByteRTCAudioMixingType type;
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
@property(assign, nonatomic) NSInteger playCount;
/**
 * @locale zh
 * @brief 混音起始位置。默认值为 0，单位为毫秒。
 */
/**
 * @locale en
 * @brief The starting position in ms. 0 by default.
 */
@property(assign, nonatomic) NSInteger startPos;
/**
 * @locale zh
 * @brief 设置音频文件混音时，收到 onMediaPlayerPlayingProgress:progress:{@link #ByteRTCMediaPlayerEventHandler#onMediaPlayerPlayingProgress:progress:} 的间隔。单位毫秒。<br>
 *       + interval > 0 时，触发回调。实际间隔为 10 的倍数。如果输入数值不能被 10 整除，将自动向上取整。例如传入 `52`，实际间隔为 60 ms。<br>
 *       + interval <= 0 时，不会触发回调。
 */
 /**
 * @locale en
 * @brief Set the interval of the periodic callback onMediaPlayerPlayingProgress:progress:{@link #ByteRTCMediaPlayerEventHandler#onMediaPlayerPlayingProgress:progress:} during audio mixing in ms.<br>
 *       + interval > 0: The callback is enabled. The actual interval is `10*(mod(10)+1)`.<br>
 *       + interval <= 0: The callback is disabled.
 */
@property(assign, nonatomic) NSInteger callbackOnProgressInterval;
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
@property(assign, nonatomic) BOOL syncProgressToRecordFrame;
/**
* @locale zh
* @brief 是否自动播放。如果不自动播放，调用 start{@link #ByteRTCMediaPlayer#start} 播放音乐文件。默认为 True。
*/
/**
* @locale en
* @brief Play the audio automatically. If not, call start{@link #ByteRTCMediaPlayer#start} to play the audio. True by default.
*/
@property(assign, nonatomic) BOOL autoPlay;
@end
/**
 * @locale zh
 * @type callback
 * @brief 内存播放数据源回调
 */
/**
 * @locale en
 * @type callback
 * @brief  In-memory audio data playing callback interface
 */
BYTERTC_APPLE_EXPORT @protocol ByteRTCMediaPlayerCustomSourceProvider <NSObject>
/**
 * @locale zh
 * @valid since 3.53
 * @type callback
 * @region 音乐播放器
 * @brief 调用 openWithCustomSource:config:{@link #ByteRTCMediaPlayer#openWithCustomSource:config:} 接口播放用户传入的内存音频数据时，会触发此回调，用户需要写入音频数据。
 * @param buffer 内存地址。在该地址中写入音频数据，写入音频数据的大小不超过 bufferSize 中填入的数值。支持的音频数据格式有: mp3，aac，m4a，3gp，wav。
 * @param bufferSize 音频数据大小，单位为字节。如果你想停止播放内存音频数据，可在 bufferSize 中填入小于或等于 0 的数，此时 SDK 会停止调用此接口。 
 * @return 返回实际读取的音频数据大小。
 * @note 若 openWithCustomSource:config:{@link #ByteRTCMediaPlayer#openWithCustomSource:config:} 接口调用失败，请在 buffer 和 bufferSize 两个参数中填入 0。 此时 SDK 会停止调用此接口。
 */
/**
 * @locale en
 * @valid since 3.53
 * @type callback
 * @region Music player
 * @brief Callback of getting the path and size of the audio data you input. <br>
 *         When you call openWithCustomSource:config:{@link #ByteRTCMediaPlayer#openWithCustomSource:config:} API to play the in-memory audio data you input, this callback will be triggered and you need to enter the path and size of the audio data. 
 * @param buffer The path of the audio data you input. The size of audio data should be equal to or less than the value of bufferSize. The supported formats are: mp3, aac, m4a, 3gp, wav.
 * @param bufferSize  The size of the audio data, in bytes. If you want to stop audio playing, you can enter a figure less than or equal to zero into bufferSize and then SDK will stop calling this callback. 
 * @return Returns the size of the audio data that are actually read. 
 * @note If calling openWithCustomSource:config:{@link #ByteRTCMediaPlayer#openWithCustomSource:config:} API failed, please enter 0 into buffer and bufferSize. In this situation, SDK will stop calling this callback.  
 */
-(int)onReadData:(uint8_t*_Nonnull) buffer bufferSize:(int)bufferSize;
/**
 * @locale zh
 * @valid since 3.53
 * @type callback
 * @region 音乐播放器
 * @brief 根据设置好的内存音频数据的读取位置和读取偏移量对音频数据进行偏移，以便 SDK 读取和分析音频数据。 <br>
 *        在调用 openWithCustomSource:config:{@link #ByteRTCMediaPlayer#openWithCustomSource:config:} 接口传入内存音频数据，或者调用 setPosition:position:{@link #ByteRTCAudioEffectPlayer#setPosition:position:} 设置了音频数据的起始播放位置后，SDK 会对音频数据进行读取和分析，此时会触发该回调，你需要根据参数中设置的起始读取位置和偏移量进行操作。
 * @param offset 音频数据读取偏移量，单位为字节，取值可正可负。  
 * @param whence 音频数据的起始读取位置。参看 ByteRTCMediaPlayerCustomSourceSeekWhence{@link #ByteRTCMediaPlayerCustomSourceSeekWhence}
 * @return 
 *         定位成功，返回偏移后的位置信息，或返回音频数据的大小。<br>
 *         定位失败，返回 -1。         
 */
/**
 * @locale en
 * @valid since 3.53
 * @type callback
 * @region Music player
 * @brief Seeking the audio data based on the set starting position and offset to help SDK read and analyze data. <br>
 *        When you call openWithCustomSource:config:{@link #ByteRTCMediaPlayer#openWithCustomSource:config:} API to play the in-memory audio data you input, or when you call setPosition:position:{@link #ByteRTCAudioEffectPlayer#setPosition:position:} to set the starting position of audio playing, this callback will be trigerred and you need to seek the audio data accorring to the value of offset and whence.  
 * @param offset The offset of the target position relative to the starting position, in bytes. The value can be positive or negative.  
 * @param whence The starting position of the seeking.  Refer to ByteRTCMediaPlayerCustomSourceSeekWhence{@link #ByteRTCMediaPlayerCustomSourceSeekWhence} for more details. 
 * @return 
 *         If the seeking succeeded, the information on the final adjusted play position after seeking or the size of the audio data will be returned.<br>
 *         If the seeking failed, -1 will be returned.  
 */
-(int64_t)onSeek:(int64_t)offset whence:(ByteRTCMediaPlayerCustomSourceSeekWhence)whence;
@end
/**
 * @locale zh
 * @type keytype
 * @brief 音频源
 */
/**
 * @locale en
 * @type keytype
 * @brief The audio source for media player.
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCMediaPlayerCustomSource : NSObject
@property(weak, nonatomic) id<ByteRTCMediaPlayerCustomSourceProvider> _Nullable provider;
/**
 * @locale zh
 * @type keytype
 * @brief 数据源模式，详见 ByteRTCMediaPlayerCustomSourceMode{@link #ByteRTCMediaPlayerCustomSourceMode}。默认为 `push`。
 */
/**
 * @locale en
 * @type keytype
 * @brief See ByteRTCMediaPlayerCustomSourceMode{@link #ByteRTCMediaPlayerCustomSourceMode}. `push` by default.
 */
@property(assign, nonatomic) ByteRTCMediaPlayerCustomSourceMode mode;
/**
 * @locale zh
 * @type keytype
 * @brief 数据源类型，详见 ByteRTCMediaPlayerCustomSourceStreamType{@link #ByteRTCMediaPlayerCustomSourceStreamType}。默认为 `raw`。
 */
/**
 * @locale en
 * @type keytype
 * @brief See ByteRTCMediaPlayerCustomSourceStreamType{@link #ByteRTCMediaPlayerCustomSourceStreamType}. `raw` by default.
 */
@property(assign, nonatomic) ByteRTCMediaPlayerCustomSourceStreamType type;

@end
/**
 * @locale zh
 * @type keytype
 * @brief 音频属性信息提示的相关配置。
 */
/**
 * @locale en
 * @type keytype
 * @brief Configuration related to audio attribute information prompt.
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCAudioPropertiesConfig : NSObject
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
@property(assign, nonatomic) NSInteger interval;
/**
 * @locale zh
 * @brief 是否开启音频频谱检测。
 */
/**
 * @locale en
 * @brief Whether to enable audio spectrum detection.
 */
@property(assign, nonatomic) BOOL enableSpectrum;
/**
 * @locale zh
 * @brief 是否开启人声检测 (VAD)。
 */
/**
 * @locale en
 * @brief Whether to enable Voice Activity Detection.
 */
@property(assign, nonatomic) BOOL enableVad;
/**
 * @locale zh
 * @brief 音量回调模式。详见 ByteRTCAudioReportMode{@link #ByteRTCAudioReportMode}。
 */
/**
 * @locale en
 * @brief The volume callback modes. See ByteRTCAudioReportMode{@link #ByteRTCAudioReportMode}.
  */
@property(assign, nonatomic) ByteRTCAudioReportMode localMainReportMode;
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
@property(nonatomic, assign) float smooth;

/**
 * @locale zh
 * @brief rtcEngine:onLocalAudioPropertiesReport:{@link #ByteRTCVideoDelegate#rtcEngine:onLocalAudioPropertiesReport:} 中包含音频数据的范围。参看 ByteRTCAudioPropertiesMode{@link #ByteRTCAudioPropertiesMode}。<br>
 *        默认仅包含本地麦克风采集的音频数据和本地屏幕音频采集数据。
 */
/**
 * @locale en
 * @brief The audio info included in rtcEngine:onLocalAudioPropertiesReport:{@link #ByteRTCVideoDelegate#rtcEngine:onLocalAudioPropertiesReport:}. See ByteRTCAudioPropertiesMode{@link #ByteRTCAudioPropertiesMode}.<br>
 *        Locally captured microphone audio info and locally captured screen audio info are included by default.
 */
@property(assign, nonatomic) ByteRTCAudioPropertiesMode audioReportMode;

/**
 * @locale zh
 * @brief 是否回调本地用户的人声基频。
 */
/**
 * @locale en
 * @brief Sets whether to return the vocal pitch of the local user. 
 */
@property(assign, nonatomic) BOOL enableVoicePitch;
/** {zh}
 * @hidden internal use
 * @brief 是否回调设备采播延时。
 */
/** {en}
 * @hidden internal use
 * @brief Sets whether to return the device record and playout delay.
 */
@property(assign, nonatomic) BOOL enableDeviceLoopDelay;
@end

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
BYTERTC_APPLE_EXPORT @interface ByteRTCAudioPropertiesInfo : NSObject
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
@property(assign, nonatomic) NSInteger linearVolume;
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
@property(assign, nonatomic) NSInteger nonlinearVolume;
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
@property(assign, nonatomic) NSInteger vad;
/**
 * @locale zh
 * @brief 频谱数组。默认长度为 257。
 */
/**
 * @locale en
 * @brief Spectrum array. The default length is 257.
 */
@property(copy, nonatomic) NSArray<NSNumber*> * _Nonnull spectrum;
/**
 * @locale zh
 * @brief 本地用户的人声基频，单位为赫兹。 <br>
 *        同时满足以下两个条件时，返回的值为本地用户的人声基频：<br>
 *      + 调用 enableAudioPropertiesReport:{@link #ByteRTCVideo#enableAudioPropertiesReport:}，并设置参数 enableVoicePitch 的值为 `true`。 <br>
 *      + 本地采集的音频中包含本地用户的人声。 <br>
 *        其他情况下返回 `0`。 
 */
/**
 * @locale en
 * @brief The vocal pitch of the local user, in Hertz. <br>
 *        When the following two conditions are met at the same time, the vocal pitch of the local user will be returned:<br>
 *      + Calls enableAudioPropertiesReport{@link #ByteRTCVideo#enableAudioPropertiesReport}, and sets the value of enableVoicePitch to `true`. <br>
 *      + The local user's voice is included in the locally captured audio data. <br>
 *        In other situations, `0` will be returned. 
 */    
@property(assign, nonatomic) NSInteger voicePitch;
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
@property(assign, nonatomic) NSInteger deviceLoopDelay;
@end

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
BYTERTC_APPLE_EXPORT @interface ByteRTCLocalAudioPropertiesInfo : NSObject

/**
 * @locale zh
 * @brief 流属性，包括主流、屏幕流。参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 */
/**
 * @locale en
 * @brief See ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 */
@property(assign, nonatomic) ByteRTCStreamIndex streamIndex;
/**
 * @locale zh
 * @type keytype
 * @brief 音频属性信息，详见 ByteRTCAudioPropertiesInfo{@link #ByteRTCAudioPropertiesInfo}
 */
/**
 * @locale en
 * @type keytype
 * @brief See ByteRTCAudioPropertiesInfo{@link #ByteRTCAudioPropertiesInfo}
 */
@property(strong, nonatomic) ByteRTCAudioPropertiesInfo *_Nonnull audioPropertiesInfo;
@end

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
BYTERTC_APPLE_EXPORT @interface ByteRTCRemoteAudioPropertiesInfo : NSObject
/**
 * @locale zh
 * @type keytype
 * @brief 远端流信息，详见 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
 */
/**
 * @locale en
 * @type keytype
 * @brief See ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
 */
@property(strong, nonatomic) ByteRTCRemoteStreamKey *_Nonnull streamKey;
/**
 * @locale zh
 * @type keytype
 * @brief 音频属性信息，详见 ByteRTCAudioPropertiesInfo{@link #ByteRTCAudioPropertiesInfo}
 */
/**
 * @locale en
 * @type keytype
 * @brief See ByteRTCAudioPropertiesInfo{@link #ByteRTCAudioPropertiesInfo}
 */
@property(strong, nonatomic) ByteRTCAudioPropertiesInfo *_Nonnull audioPropertiesInfo;
@end

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
BYTERTC_APPLE_EXPORT @interface ByteRTCPosition : NSObject
/**
 * @locale zh
 * @brief x 坐标
 */
/**
 * @locale en
 * @brief X-coordinate
 */
@property(nonatomic, assign) float x;
/**
 * @locale zh
 * @brief y 坐标
 */
/**
 * @locale en
 * @brief Y-coordinate
 */
@property(nonatomic, assign) float y;
/**
 * @locale zh
 * @brief z 坐标
 */
/**
 * @locale en
 * @brief Z-coordinate
 */
@property(nonatomic, assign) float z;
@end

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
BYTERTC_APPLE_EXPORT @interface ByteRTCOrientation : NSObject
/**
 * @locale zh
 * @brief x 坐标
 */
/**
 * @locale en
 * @brief X-coordinate
 */
@property(nonatomic, assign) float x;
/**
 * @locale zh
 * @brief y 坐标
 */
/**
 * @locale en
 * @brief Y-coordinate
 */
@property(nonatomic, assign) float y;
/**
 * @locale zh
 * @brief z 坐标
 */
/**
 * @locale en
 * @brief Z-coordinate
 */
@property(nonatomic, assign) float z;
@end

/**
 * @locale zh
 * @type keytype
 * @brief 三维朝向信息，三个向量需要两两垂直。参看 ByteRTCOrientation{@link #ByteRTCOrientation}。
 */
/**
 * @locale en
 * @type keytype
 * @brief Three-dimensional orientation information, each pair of vectors need to be perpendicular. See ByteRTCOrientation{@link #ByteRTCOrientation}.
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCHumanOrientation : NSObject
/**
 * @locale zh
 * @brief 正前方朝向，默认值为 {1,0,0}，即正前方朝向 x 轴正方向
 */
/**
 * @locale en
 * @brief Forward orientation, the default value is {1,0,0}, i.e., the forward orientation is in the positive direction of x-axis.
 */
@property(nonatomic, strong) ByteRTCOrientation* _Nonnull forward;
/**
 * @locale zh
 * @brief 正右方朝向，默认值为 {0,1,0}，即右手朝向 y 轴正方向
 */
/**
 * @locale en
 * @brief Rightward orientation, the default value is {0,1,0}, i.e., the rightward orientation is in the positive direction of y-axis.
 */
@property(nonatomic, strong) ByteRTCOrientation* _Nonnull right;
/**
 * @locale zh
 * @brief 正上方朝向，默认值为 {0,0,1}，即头顶朝向 z 轴正方向
 */
/**
 * @locale en
 * @brief Upward orientation, the default value is {0,0,1}, i.e., the upward orientation is in the positive direction of z-axis.
 */
@property(nonatomic, strong) ByteRTCOrientation* _Nonnull up;
@end

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
typedef NS_ENUM(NSInteger, ByteRTCMulDimSingScoringMode) {
    /**
     * @locale zh
     * @brief 按照音高进行评分。
     */
    /**
     * @locale en
     * @brief The score is provided based on the pitch.
     */
    ByteRTCMulDimSingScoringModeNote = 0
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
typedef NS_ENUM(NSInteger, ByteRTCAudioAlignmentMode) {
    /**
     * @locale zh
     * @brief 不对齐
     */
    /**
     * @locale en
     * @brief Disabled
     */
    ByteRTCAudioAlignmentModeOff = 0,
    /**
     * @locale zh
     * @brief 远端音频流都对齐伴奏进度同步播放
     */
    /**
     * @locale en
     * @brief All subscribed audio streams are aligned based on the process of the background music.
     */
    ByteRTCAudioAlignmentModeAudioMixing = 1,
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
BYTERTC_APPLE_EXPORT @interface ByteRTCSingScoringRealtimeInfo : NSObject
 /**
  * @locale zh
  * @brief 当前的播放进度。
  */
 /**
  * @locale en
  * @brief Current playback position.
  */
@property(nonatomic, assign) int currentPosition;
 /**
  * @locale zh
  * @brief 演唱者的音高。
  */
 /**
  * @locale en
  * @brief The user's pitch.
  */
@property(nonatomic, assign) int userPitch;
 /**
  * @locale zh
  * @brief 标准音高。
  */
 /**
  * @locale en
  * @brief Standard pitch.
  */
@property(nonatomic, assign) int standardPitch;
 /**
  * @locale zh
  * @brief 歌词分句索引。
  */
 /**
  * @locale en
  * @brief Lyric index.
  */
@property(nonatomic, assign) int sentenceIndex;
 /**
  * @locale zh
  * @brief 上一句歌词的评分。
  */
 /**
  * @locale en
  * @brief The score for the previous lyric.
  */
@property(nonatomic, assign) int sentenceScore;
 /**
  * @locale zh
  * @brief 当前演唱的累计分数。
  */
 /**
  * @locale en
  * @brief The total score for the user's current performance.
  */
@property(nonatomic, assign) int totalScore;
 /**
  * @locale zh
  * @brief 当前演唱的平均分数。
  */
 /**
  * @locale en
  * @brief The average score for the user's current performance.
  */
@property(nonatomic, assign) int averageScore;
@end

/**
 * @locale zh
 * @type keytype
 * @brief 标准音高数据组。
 */
/**
 * @locale en
 * @type keytype
 * @brief Standard Pitch Data.
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCStandardPitchInfo : NSObject
 /**
  * @locale zh
  * @brief 开始时间，单位 ms。
  */
 /**
  * @locale en
  * @brief Starting time, unit: ms.
  */
@property(nonatomic, assign) int startTime;
 /**
  * @locale zh
  * @brief 持续时间，单位 ms。
  */
 /**
  * @locale en
  * @brief Duration, unit: ms.
  */
@property(nonatomic, assign) int duration;
 /**
  * @locale zh
  * @brief 音高。
  */
 /**
  * @locale en
  * @brief pitch.
  */
@property(nonatomic, assign) int pitch;
@end

/**
 * @locale zh
 * @type keytype
 * @brief K 歌评分配置。
 */
/**
 * @locale en
 * @type keytype
 * @brief The configuration of the karaoke scoring feature.
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCSingScoringConfig : NSObject
 /**
  * @locale zh
  * @brief 打分维度，详见 ByteRTCMulDimSingScoringMode{@link #ByteRTCMulDimSingScoringMode}。
  */
 /**
  * @locale en
  * @brief Scoring mode, see ByteRTCMulDimSingScoringMode{@link #ByteRTCMulDimSingScoringMode}.
  */
@property(nonatomic, assign) ByteRTCMulDimSingScoringMode mode;
 /**
  * @locale zh
  * @brief 音频采样率。仅支持 44100 Hz、48000 Hz。
  */
 /**
  * @locale en
  * @brief Sampling rate. Only 44,100 Hz and 48,000 Hz are supported.
  */
@property(nonatomic, assign) ByteRTCAudioSampleRate sampleRate;
 /**
  * @locale zh
  * @brief 歌词文件路径。打分功能仅支持 KRC 歌词文件。
  */
 /**
  * @locale en
  * @brief The file path of the lyrics. The scoring feature only supports KRC lyrics file.
  */
@property(nonatomic, copy) NSString *_Nonnull lyricsFilepath;
 /**
  * @locale zh
  * @brief 歌曲 midi 文件路径。
  */
 /**
  * @locale en
  * @brief The path of the midi file.
  */
@property(nonatomic, copy) NSString *_Nonnull midiFilepath;
@end

/**
 * @locale zh
 * @type keytype
 * @brief 音频文件录制内容来源。
 */
/**
 * @locale en
 * @type keytype
 * @brief Audio file recording source type
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioFrameSource) {
    /**
     * @locale zh
     * @brief 本地麦克风采集的音频数据。
     */
    /**
     * @locale en
     * @brief The audio captured by the local microphone.
     */
    ByteRTCAudioFrameSourceTypeMic = 0,
    /**
     * @locale zh
     * @brief 远端所有用户混音后的数据
     */
    /**
     * {en}
     * @brief The audio got by mixing all remote user's audio.
     */
    ByteRTCAudioFrameSourceTypePlayback = 1,
    /**
     * @locale zh
     * @brief 本地麦克风和所有远端用户音频流的混音后的数据
     */
    /**
     * @locale en
     * @brief The audio got by mixing the local captured audio and all remote user's audio.
     */
    ByteRTCAudioFrameSourceTypeMixed = 2,
};
/**
 * @locale zh
 * @type keytype
 * @brief 音频质量
 */
/**
 * @locale en
 * @type keytype
 * @brief Audio quality
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioQuality) {
    /**
     * @locale zh
     * @brief 低音质
     */
    /**
     * @locale en
     * @brief low quality
     */
    ByteRTCAudioQualityLow = 0,
    /**
     * @locale zh
     * @brief 中音质
     */
    /**
     * @locale en
     * @brief medium quality
     */
    ByteRTCAudioQualityMedium = 1,
    /**
     * @locale zh
     * @brief 高音质
     */
    /**
     * @locale en
     * @brief high quality
     */
    ByteRTCAudioQualityHigh = 2,
    /**
     * @locale zh
     * @brief 超高音质
     */
    /**
     * @locale en
     * @brief ultra high quality
     */
    ByteRTCAudioQualityUltraHigh = 3,
};
/**
 * @locale zh
 * @type keytype
 * @brief 音频录制配置
 */
/**
 * @locale en
 * @type keytype
 * @brief Audio recording configuration
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCAudioRecordingConfig : NSObject
/**
 * @locale zh
 * @brief 录制文件路径。一个有读写权限的绝对路径，包含文件名和文件后缀。
 * @note 录制文件的格式仅支持 .aac 和 .wav。
 */
/**
 * @locale en
 * @brief Absolute path of the recorded file, file name included. The App must have the write and read permission of the path.
 * @note The files format is restricted to .aac and .wav.
 */
@property(nonatomic, copy) NSString* _Nonnull absoluteFileName;
/**
 * @locale zh
 * @brief 录音内容来源，参看 ByteRTCAudioFrameSource{@link #ByteRTCAudioFrameSource}。<br>
 * 默认为 ByteRTCAudioFrameSourceTypeMixed = 2。
 */
/**
 * @locale en
 * @brief The source of the recording. See ByteRTCAudioFrameSource{@link #ByteRTCAudioFrameSource}.<br>
 * It is ByteRTCAudioFrameSourceTypeMixed = 2 by default.
 */
@property(nonatomic, assign) ByteRTCAudioFrameSource frameSource;
/**
 * @locale zh
 * @brief 录音采样率。参看 ByteRTCAudioSampleRate{@link #ByteRTCAudioSampleRate}。
 */
/**
 * @locale en
 * @brief See ByteRTCAudioSampleRate{@link #ByteRTCAudioSampleRate}.
 */
@property(nonatomic, assign) ByteRTCAudioSampleRate sampleRate;
/**
 * @locale zh
 * @brief 录音音频声道。参看 ByteRTCAudioChannel{@link #ByteRTCAudioChannel}。<br>
 *       如果录制时设置的的音频声道数与采集时的音频声道数不同：<br>
 *        + 如果采集的声道数为 1，录制的声道数为 2，那么，录制的音频为经过单声道数据拷贝后的双声道数据，而不是立体声。<br>
 *        + 如果采集的声道数为 2，录制的声道数为 1，那么，录制的音频为经过双声道数据混合后的单声道数据。
 */
/**
 * @locale en
 * @brief Number of audio channels. See ByteRTCAudioChannel{@link #ByteRTCAudioChannel}.<br>
 *        If number of audio channels of recording is different than that of audio capture, the behavior is: <br>
 *        + If the number of capture is 1, and the number of recording is 2, the recorded audio is two-channel data after copying mono-channel data. <br>
 *        + If the number of capture is 2, and the number of recording is 1, the recorded audio is recorded by mixing the audio of the two channels.
 */
@property(nonatomic, assign) ByteRTCAudioChannel channel;
/**
 * @locale zh
 * @brief 录音音质。仅在录制文件格式为 .aac 时可以设置。参看 ByteRTCAudioQuality{@link #ByteRTCAudioQuality}。<br>
 * 采样率为 32kHz 时，不同音质录制文件（时长为 10min）的大小分别是： <br>
 *        + 低音质：1.2MB；<br>
 *        + 【默认】中音质：2MB；<br>
 *        + 高音质：3.75MB；<br>
 *        + 超高音质：7.5MB。
 */
/**
 * @locale en
 * @brief Recording quality. Only valid for .aac file. See ByteRTCAudioQuality{@link #ByteRTCAudioQuality}.<br>
 * When the sample rate is 32kHz, the file (10min) size for different qualities are: <br>
 *        + low: 1.2MB; <br>
 *        + [By Default] medium: 2MB; <br>
 *        + high: 3.75MB; <br>
 *        + ultra high: 7.5MB.
 */
@property(nonatomic, assign) ByteRTCAudioQuality quality;
@end

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
typedef NS_ENUM(NSInteger, ByteRTCAudioRecordingState) {
    /**
     * @locale zh
     * @brief 录制异常
     */
    /**
     * @locale en
     * @brief Recording exception
     */
    ByteRTCAudioRecordingStateError = 0,
    /**
     * @locale zh
     * @brief 录制进行中
     */
    /**
     * @locale en
     * @brief Recording in progress
     */
    ByteRTCAudioRecordingStateProcessing = 1,
    /**
     * @locale zh
     * @brief 已结束录制，并且录制文件保存成功。
     */
    /**
     * @locale en
     * @brief The recording task ends, and the file is saved.
     */
    ByteRTCAudioRecordingStateSuccess = 2,
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
typedef NS_ENUM(NSInteger, ByteRTCAudioRecordingErrorCode) {
    /**
     * @locale zh
     * @brief 录制正常
     */
    /**
     * @locale en
     * @brief OK
     */
    ByteRTCAudioRecordingErrorCodeOk = 0,
    /**
     * @locale zh
     * @brief 没有文件写权限
     */
    /**
     * @locale en
     * @brief No file write permissions.
     */
    ByteRTCAudioRecordingErrorCodeNoPermission = -1,
    /**
     * @locale zh
     * @brief 没有进入房间
     */
    /**
     * @locale en
     * @brief Not in the room.
     */
    ByteRTCAudioRecordingErrorNotInRoom = -2,
    /**
     * @locale zh
     * @brief 录制已经开始
     */
    /**
     * @locale en
     * @brief Started.
     */
    ByteRTCAudioRecordingAlreadyStarted = -3,
    /**
     * @locale zh
     * @brief 录制还未开始
     */
    /**
     * @locale en
     * @brief Not started.
     */
    ByteRTCAudioRecordingNotStarted = -4,
        /**
     * @locale zh
     * @brief 录制失败。文件格式不支持。
     */
    /**
     * @locale en
     * @brief Failure. Invalid file format.
     */
    ByteRTCAudioRecordingErrorCodeNotSupport = -5,
    /**
     * @locale zh
     * @brief 其他异常
     */
    /**
     * @locale en
     * @brief Other error.
     */
    ByteRTCAudioRecordingErrorCodeOther = -6,
};
/**
 * @locale zh
 * @type keytype
 * @brief 蜂窝网络辅助增强应用的媒体模式
 */
/**
 * @locale en
 * @type keytype
 * @brief Media type for cellular assisted Enhancement
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCAudioEnhancementConfig: NSObject
/**
 * @locale zh
 * @brief 对信令消息，是否启用蜂窝网络辅助增强。默认不启用。
 */
/**
 * @locale en
 * @brief Apply to signaling or not. Not by default.
 */
@property (assign, nonatomic) BOOL enhanceSignaling;
/**
 * @locale zh
 * @brief 对音频，是否启用蜂窝网络辅助增强。默认不启用。
 */
/**
 * @locale en
 * @brief Apply to audio stream or not. Not by default.
 */
@property (assign, nonatomic) BOOL enhanceAudio;
@end
/**
 * @locale zh
 * @type keytype
 * @brief 用户在空间音频坐标系里的位置信息。
 */
/**
 * @locale en
 * @type keytype
 * @brief Information on the user's position in the rectangular coordinate system for the spatial audio.
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCPositionInfo : NSObject
/**
 * @locale zh
 * @brief 用户在空间音频坐标系里的位置，需自行建立空间直角坐标系。参看 ByteRTCPosition{@link #ByteRTCPosition}。
 */
/**
 * @locale en
 * @brief 3D coordinate values of the user's position in the rectangular coordinate system for the spatial audio. You need to build your own rectangular coordinate system. Refer to ByteRTCPosition{@link #ByteRTCPosition} for details.
 */
@property(strong, nonatomic) ByteRTCPosition *_Nonnull position;
/**
 * @locale zh
 * @brief 用户在空间音频坐标系里的三维朝向信息。三个向量需要两两垂直。参看 ByteRTCHumanOrientation{@link #ByteRTCHumanOrientation}。
 */
/**
 * @locale en
 * @brief Information on the three-dimensional orientation of the user in the rectangular coordinate system for the spatial audio. Any two of the 3D coordinate vectors of the user's position need to be perpendicular to each other. Refer to ByteRTCHumanOrientation{@link #ByteRTCHumanOrientation} for details.
 */
@property(strong, nonatomic) ByteRTCHumanOrientation *_Nonnull orientation;
@end
