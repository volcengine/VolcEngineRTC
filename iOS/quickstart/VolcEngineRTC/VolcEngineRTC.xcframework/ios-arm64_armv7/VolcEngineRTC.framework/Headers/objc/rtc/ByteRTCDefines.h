/*
 * Copyright (c) 2020 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief Objective-C VolcEngineRTC RTC Defines
*/

#import <CoreMedia/CMTime.h>
#import <UIKit/UIKit.h>

/** 
 * @type keytype
 * @brief 视频渲染模式
 */
typedef NS_ENUM(NSUInteger, ByteRTCRenderMode) {
    /** 
     * @brief 视窗填满优先。<br>
     *        视频帧等比缩放，直至视窗被视频填满。如果视频帧长宽比例与视窗不同，视频帧的多出部分将无法显示。<br>
     *        缩放完成后，视频帧的一边长和视窗的对应边长一致，另一边长大于等于视窗对应边长。
     */
    ByteRTCRenderModeHidden = 1,
    /** 
     * @brief 视频帧内容全部显示优先。<br>
     *        视频帧等比缩放，直至视频帧能够在视窗上全部显示。如果视频帧长宽比例与视窗不同，视窗上未被视频帧填满区域将被涂黑。<br>
     *        缩放完成后，视频帧的一边长和视窗的对应边长一致，另一边长小于等于视窗对应边长。
     */
    ByteRTCRenderModeFit = 2,
    /** 
     *  @brief 视频帧自适应视窗
     *         视频帧非等比缩放，直至视窗被视频填满。如果视频帧长宽比例与视窗不同，视频帧的高或宽会被拉伸。
    */
   ByteRTCRenderModeAdaptive = 3,
};

/** 
 *  @type keytype
 *  @brief 用户离开房间的原因。  <br>
 */
typedef NS_ENUM(NSUInteger, ByteRTCUserOfflineReason) {
    /** 
     * @brief 远端用户调用 leaveRoom{@link #ByteRTCEngineKit#leaveRoom} 方法主动退出房间。  <br>
     */
    ByteRTCUserOfflineReasonQuit = 0,
    /** 
     * @brief 远端用户因网络等原因掉线，或切换至隐身状态。  <br>
     */
    ByteRTCUserOfflineReasonDropped = 1,
    /**
     * @hidden
     */
    ByteRTCUserOfflineReasonBecomeAudience = 2,
};

/** 
 * @type keytype
 * @brief 房间内远端流移除原因。  <br>
 */
typedef NS_ENUM(NSInteger, ByteRTCStreamRemoveReason) {
    /** 
     * @brief 远端用户停止发布流。  <br>
     */
    ByteRTCStreamRemoveReasonUnpublish = 0,
    /** 
     * @brief 远端用户发布流失败。  <br>
     */
    ByteRTCStreamRemoveReasonPublishFailed = 1,
    /** 
     * @brief 保活失败。  <br>
     */
    ByteRTCStreamRemoveReasonKeepLiveFailed = 2,
    /** 
     * @brief 远端用户断网。  <br>
     */
    ByteRTCStreamRemoveReasonClientDisconnected = 3,
    /** 
     * @brief 远端用户重新发布流。  <br>
     */
    ByteRTCStreamRemoveReasonRepublish = 4,
    /** 
     * @brief 其他原因。  <br>
     */
    ByteRTCStreamRemoveReasonOther = 5,
};

/** 
 * @type keytype
 * @brief 房间模式
 */
typedef NS_ENUM(NSInteger, ByteRTCRoomProfile) {
  /** 
    * @brief 普通音视频通话模式。<br>
    *        单声道，采样率为 48kHz
    *        你应在 1V1 音视频通话时，使用此设置。<br>
    *        此设置下，弱网抗性较好。
    */
   ByteRTCRoomProfileCommunication = 0,
    /** 
     * @brief 直播模式。<br>
     *        单声道，采样率为 48kHz
     *        当你对音视频通话的音质和画质要求较高时，应使用此设置。<br>
     *        此设置下，当用户使用蓝牙耳机收听时，蓝牙耳机使用媒体模式。
     */
    ByteRTCRoomProfileLiveBroadcasting = 1,
    /** 
     * @brief 游戏语音模式。<br>
     *        单声道，采样率为 16kHz
     *        低端机在此模式下运行时，进行了额外的性能优化：<br>
     *            + 采集播放采用 16kHz 单通道采样 <br>
     *            + 部分低端机型配置编码帧长 40/60 <br>
     *            + 部分低端机型关闭软件 3A 音频处理 <br>
     *        增强对 iOS 其他屏幕录制进行的兼容性，避免音频录制被 RTC 打断。
     */
    ByteRTCRoomProfileGame = 2,
    /** 
     * @brief 云游戏模式。<br>
     *        单声道，采样率为 48kHz
     *        如果你需要低延迟、高码率的设置时，你可以使用此设置。<br>
     *        此设置下，弱网抗性较差。
     */
    ByteRTCRoomProfileCloudGame = 3,
    /** 
     * @author wuxinyu.mrx
     * @brief 低时延模式。SDK 会使用低延时设置。  <br>
     *        当你的场景非游戏或云游戏场景，又需要极低延时的体验时，可以使用该模式。 <br>
     *        该模式下，音视频通话延时会明显降低，但同时，弱网抗性、通话音质等均会受到一定影响。  <br>
     *        在使用此模式前，强烈建议咨询技术支持同学。
     */
    ByteRTCRoomProfileLowLatency = 4,
};

/** 
 * @hidden
 * @type keytype
 * @brief 用户角色。  <br>
 */
typedef NS_ENUM(NSInteger, ByteRTCUserRoleType) {
    /** 
     * @brief 主播角色。该角色用户可在房间内发布和订阅音视频流，房间中的其他用户可以感知到该用户的存在。  <br>
     */
    ByteRTCUserRoleTypeBroadcaster = 1,
    /** 
     * @brief 隐身用户角色。此角色用户只可在房间内订阅音视频流，房间中的其他用户无法感知到该用户的存在。  <br>
     */
    ByteRTCUserRoleTypeSilentAudience = 2,
};

/** 
 * @type keytype
 * @brief 音频场景类型。  <br>
 *        选择音频场景后，RTC 会自动根据客户端音频采集播放设备和采集播放状态，适用通话音量/媒体音量。  <br>
 *        你可以调用 setAudioScenario:{@link #ByteRTCEngineKit #setAudioScenario:} 设置音频场景。  <br>
 *        如果以下音频场景类型无法满足你的业务需要，请联系技术支持同学进行定制。
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioScenarioType) {
    /** 
     * @brief 音乐场景。默认为此场景。  <br>
     *        此场景适用于对音乐表现力有要求的场景，如音乐直播等。  <br>
     *        音频采集播放设备和采集播放状态，到音量类型的映射如下：  <br>
     *        <table>
     *           <tr><th></th><th>仅采集音频，不播放音频</th><th>仅播放音频，不采集音频</th><th>采集并播放音频</th><th>备注</th></tr>
     *           <tr><td>设备自带麦克风和扬声器/听筒</td><td>媒体音量</td><td>媒体音量</td><td>通话音量</td><td>/</td></tr>
     *           <tr><td>有线耳机</td><td>媒体音量</td><td>媒体音量</td><td>媒体音量</td><td>/</td></tr>
     *           <tr><td>蓝牙耳机</td><td>媒体音量</td><td>媒体音量</td><td>媒体音量</td><td>即使蓝牙耳机有麦克风，也只能使用设备自带麦克风进行本地音频采集。</td></tr>
     *        </table>
     */
    ByteRTCAudioScenarioMusic = 0,
    /** 
     * @brief 高质量通话场景。  <br>
     *        此场景适用于对音乐表现力有要求，但又希望能够使用蓝牙耳机上自带的麦克风进行音频采集的场景。  <br>
     *        此场景可以兼顾外放/使用蓝牙耳机时的音频体验，并避免使用蓝牙耳机时音量类型切换导致的听感突变。  <br>
     *        音频采集播放设备和采集播放状态，到音量类型的映射如下：<br>
     *        <table>
     *           <tr><th></th><th>仅采集音频，不播放音频</th><th>仅播放音频，不采集音频</th><th>采集并播放音频</th> <th>备注</th> </tr>
     *           <tr><td>设备自带麦克风和扬声器/听筒</td><td>媒体音量</td><td>媒体音量</td><td>通话音量</td><td>/</td></tr>
     *           <tr><td>有线耳机</td><td>媒体音量</td><td>媒体音量</td><td>媒体音量</td><td>/</td></tr>
     *           <tr><td>蓝牙耳机</td><td>通话音量</td><td>通话音量</td><td>通话音量</td><td>使用蓝牙耳机上自带的麦克风进行音频采集。</td></tr>
     *        </table>
     */
    ByteRTCAudioScenarioHighqualityCommunication = 1,
    /** 
     * @brief 纯通话音量场景。<br>
     *        此场景下，无论客户端音频路由情况和发布订阅状态，全程使用通话音量。
     *        适用于需要频繁上下麦的通话或会议场景。  <br>
     *        此场景可以保持统一的音频模式，不会有音量突变的听感；
     *        最大程度地消除回声，使通话清晰度达到最优；
     *        使用蓝牙耳机时，能够使用蓝牙耳机上自带的麦克风进行音频采集。  <br>
     *        但是，会压低使用媒体音量进行播放的其他音频的音量，且音质会变差。
     */
    ByteRTCAudioScenarioCommunication = 2,
    /** 
     * @brief 纯媒体场景。一般不建议使用。  <br>
     *        此场景下，无论客户端音频采集播放设备和采集播放状态，全程使用媒体音量。  <br>
     *        外放通话时，极易出现回声和啸叫。
     */
    ByteRTCAudioScenarioMedia = 3,
    /** 
     * @brief 游戏媒体场景。仅适合游戏场景。  <br>
     *        此场景下，蓝牙耳机时使用通话音量，其它设备使用媒体音量。
     *        外放通话且无游戏音效消除优化时，极易出现回声和啸叫。
     */
    ByteRTCAudioScenarioGameStreaming = 4,
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
};

/** 
 * @type keytype
 * @brief 音质档位
 *        调用 setAudioProfile:{@link #ByteRTCEngineKit#setAudioProfile:} 设置的音质档位
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioProfileType) {
    /** 
     * @brief 默认音质
     *        服务器下发或客户端已设置的 ByteRTCRoomProfile{@link #ByteRTCRoomProfile} 的音质配置
     */
    ByteRTCAudioProfileDefault = 0,
    /** 
     * @brief 流畅音质。  <br>
     *        单声道，采样率为 16kHz，编码码率为 24kbps。 <br>
     *        流畅优先、低延迟、低功耗、低流量消耗，适用于大部分游戏场景，如 MMORPG、MOBA、FPS 等游戏中的小队语音、组队语音、国战语音等。
     */
    ByteRTCAudioProfileFluent = 1,
    /** 
     * @brief 标准音质。  <br>
     *        单声道，采样率为 48kHz，编码码率为 48kbps。 <br>
     *        适用于对音质有一定要求的场景，同时延时、功耗和流量消耗相对适中，适合教育场景和 Sirius 等狼人杀类游戏。
     */
    ByteRTCAudioProfileStandard = 2,
    /** 
     * @brief 高清音质  <br>
     *        双声道，采样率为 48kHz，编码码率为 128kbps。 <br>
     *        超高音质，同时延时、功耗和流量消耗相对较大，适用于连麦 PK 等音乐场景。 <br>
     *        游戏场景不建议使用。
     */
    ByteRTCAudioProfileHD = 3,
};

/** 
 * @type keytype
 * @brief SDK 与信令服务器连接状态。
 */
typedef NS_ENUM(NSInteger, ByteRTCConnectionState) {
    /** 
     * @brief 连接中断。
     */
    ByteRTCConnectionStateDisconnected = 1,
    /** 
     * @brief 首次连接，正在连接中。
     */
    ByteRTCConnectionStateConnecting = 2,
    /** 
     * @brief 首次连接成功。
     */
    ByteRTCConnectionStateConnected = 3,
    /** 
     * @brief 连接断开后重新连接中。
     */
    ByteRTCConnectionStateReconnecting = 4,
    /** 
     * @brief 连接断开后重连成功。
     */
    ByteRTCConnectionStateReconnected = 5,
    /** 
     * @brief 网络连接断开超过 10 秒，仍然会继续重连。
     */
    ByteRTCConnectionStateLost = 6,
};

/** 
 * @type keytype
 * @brief SDK 网络连接类型。
 */
typedef NS_ENUM(NSInteger, ByteRTCNetworkType) {
    /** 
     * @brief 网络连接类型未知。
     */
    ByteRTCNetworkTypeUnknown = -1,
    /** 
     * @brief 网络连接已断开。
     */
    ByteRTCNetworkTypeDisconnected = 0,
    /** 
     * @brief 网络连接类型为 LAN 。
     */
    ByteRTCNetworkTypeLAN = 1,
    /** 
     * @brief 网络连接类型为 Wi-Fi（包含热点）。
     */
    ByteRTCNetworkTypeWIFI = 2,
    /** 
     * @brief 网络连接类型为 2G 移动网络。
     */
    ByteRTCNetworkTypeMobile2G = 3,
    /** 
     * @brief 网络连接类型为 3G 移动网络。
     */
    ByteRTCNetworkTypeMobile3G = 4,
    /** 
     * @brief 网络连接类型为 4G 移动网络。
     */
    ByteRTCNetworkTypeMobile4G = 5,
    /** 
     * @brief 网络连接类型为 5G 移动网络。
     */
    ByteRTCNetworkTypeMobile5G = 6,
};

/** 
 * @type keytype
 * @brief 通话前探测的停止原因
 *        rtcEngine:onNetworkDetectionStopped:{@link #ByteRTCEngineDelegate#rtcEngine:onNetworkDetectionStopped:} 回调的参数类型
 */
typedef NS_ENUM(NSUInteger, ByteRTCNetworkDetectionStopReason) {
    /** 
     * @brief 用户主动停止。
     */
    ByteRTCNetworkDetectionStopReasonUser = 0,
    /** 
     * @brief 探测超过三分钟。
     */
    ByteRTCNetworkDetectionStopReasonTimeout = 1,
    /** 
     * @brief 探测网络连接断开。<br>
     *        当超过 12s 没有收到回复，SDK 将断开网络连接，并且不再尝试重连。
     */
    ByteRTCNetworkDetectionStopReasonConnectionLost = 2,
    /** 
     * @brief 本地开始推拉流，停止探测。
     */
    ByteRTCNetworkDetectionStopReasonStreaming = 3,
    /** 
     * @brief 网络探测失败，内部异常
     */
    ByteRTCNetworkDetectionStopReasonInnerErr = 4,
};

/** 
 * @type errorcode
 * @brief 开始探测的返回值
 *        startNetworkDetection:uplinkBandwidth:downlink:downlinkBandwidth:{@link #ByteRTCEngineKit#startNetworkDetection:uplinkBandwidth:downlink:downlinkBandwidth:} 返回对象类型
 */
typedef NS_ENUM(NSInteger, ByteRTCNetworkDetectionStartReturn) {
    /** 
     * @brief 成功开始探测。
     */
    ByteRTCNetworkDetectionStartReturnSuccess = 0,
    /** 
     * @brief 开始探测失败。参数错误，上下行探测均为 `false`，或期望带宽超过了范围 [100,10000]
     */
    ByteRTCNetworkDetectionStartReturnParamErr = 1,
    /** 
     * @brief 开始探测失败。失败原因为，本地已经开始推拉流
     */
    ByteRTCNetworkDetectionStartReturnStreaming = 2,
    /** 
     * @brief 已经开始探测，无需重复开启
     */
    ByteRTCNetworkDetectionStartReturnStarted = 3,
    /** 
     * @brief 不支持该功能
     */
    ByteRTCNNetworkDetectionStartReturnNotSupport = 4,
};

/** 
 * @type keytype
 * @brief 通话前探测链接的类型
 *        rtcEngine:onNetworkDetectionResult:quality:rtt:lostRate:bitrate:jitter:{@link #ByteRTCEngineDelegate#rtcEngine:onNetworkDetectionResult:quality:rtt:lostRate:bitrate:jitter:} 回调的参数类型
 */
typedef NS_ENUM(NSUInteger, ByteRTCNetworkDetectionLinkType) {
    /** 
     * @brief 上行网络探测。
     */
    ByteRTCNetworkDetectionLinkTypeUp = 0,
    /** 
     * @brief 下行网络探测。
     */
    ByteRTCNetworkDetectionLinkTypeDown = 1,
};

/** 
 * @type keytype
 * @brief 视频流类型
 *      目前C++ SDK 只支持 ByteRTCVideoStreamTypeHigh 类型
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoStreamType) {
    /** 
     * @brief 高分辨率视频流
     */
    ByteRTCVideoStreamTypeHigh = 0,
    /** 
     * @brief 低分辨率视频
     */
    ByteRTCVideoStreamTypeLow = 1,
};

/** 
 * @type keytype
 * @brief 媒体流网络质量。
 */
typedef NS_ENUM(NSUInteger, ByteRTCNetworkQuality) {
    /** 
     * @brief 网络质量未知。
     */
    ByteRTCNetworkQualityUnknown = 0,
    /** 
     * @brief 网络质量极好。
     */
    ByteRTCNetworkQualityExcellent = 1,
    /** 
     * @brief 主观感觉和 kNetworkQualityExcellent 差不多，但码率可能略低。
     */
    ByteRTCNetworkQualityGood = 2,
    /** 
     * @brief 主观感受有瑕疵但不影响沟通。
     */
    ByteRTCNetworkQualityPoor = 3,
    /** 
     * @brief 勉强能沟通但不顺畅。
     */
    ByteRTCNetworkQualityBad = 4,
    /** 
     * @brief 网络质量非常差，基本不能沟通。
     */
    ByteRTCNetworkQualityVeryBad = 5,
};

/** 
 * @type errorcode
 * @brief 回调错误码。
 *        SDK 内部遇到不可恢复的错误时，会通过 rtcEngine:onError:{@link #ByteRTCEngineDelegate#rtcEngine:onError:} 回调通知用户。
 */
typedef NS_ENUM(NSInteger, ByteRTCErrorCode) {
    /** 
     * @brief Token 无效。
     *        调用 joinRoomByKey:roomId:userInfo:rtcRoomConfig:{@link #ByteRTCEngineKit#joinRoomByKey:roomId:userInfo:rtcRoomConfig:} 方法时使用的 Token 无效或过期失效。需要用户重新获取 Token，并调用
     *        updateToken:{@link #ByteRTCEngineKit#updateToken:} 方法更新 Token。
     */
    ByteRTCErrorCodeInvalidToken               = -1000,
    /** 
     * @brief 加入房间错误。
     *        调用 joinRoomByKey:roomId:userInfo:rtcRoomConfig:{@link #ByteRTCEngineKit#joinRoomByKey:roomId:userInfo:rtcRoomConfig:} 方法时发生未知错误导致加入房间失败。需要用户重新加入房间。
     */
    ByteRTCErrorCodeJoinRoom             = -1001,
    /** 
     * @brief 没有发布音视频流权限。
     *        用户在所在房间中发布音视频流失败，失败原因为用户没有发布流的权限。
     */
    ByteRTCErrorCodeNoPublishPermission       = -1002,
    /** 
     * @brief 没有订阅音视频流权限。
     *        用户订阅所在房间中的音视频流失败，失败原因为用户没有订阅流的权限。
     */
    ByteRTCErrorCodeNoSubscribePermission     = -1003,
    /** 
     * @brief 用户被踢出房间：<br>
     *        + 本地用户所在房间中有相同用户 ID 的用户加入房间，导致前者被踢出房间；<br>
     *        + 因调用踢出用户的 OpenAPI，被踢出房间；<br>
     *        + 因调用解散房间的 OpenAPI，离开房间。
     */
    ByteRTCErrorCodeDuplicateLogin             = -1004,
    /** 
     * @brief 订阅音视频流失败，订阅音视频流总数超过上限。
     *        游戏场景下，为了保证音视频通话的性能和质量，服务器会限制用户订阅的音视频流总数。当用户订阅的音视频流总数已达上限时，继续订阅更多流时会失败，同时用户会收到此错误通知。
     */
    ByteRTCErrorCodeOverStreamSubscribeLimit        = -1070,
    /** 
     * @brief 发布流失败，发布流总数超过上限。
     *        RTC 系统会限制单个房间内发布的总流数，总流数包括视频流、音频流和屏幕流。如果房间内发布流数已达上限时，本地用户再向房间中发布流时会失败，同时会收到此错误通知。
     */
    ByteRTCErrorCodeOverStreamPublishLimit = -1080,
    /** 
     * @brief 发布屏幕流失败，发布流总数超过上限。
     *        RTC 系统会限制单个房间内发布的总流数，总流数包括视频流、音频流和屏幕流。如果房间内发布流数已达上限时，本地用户再向房间中发布流时会失败，同时会收到此错误通知。
     */
    ByteRTCErrorCodeOverScreenPublishLimit = -1081,
    /** 
     * @brief 发布视频流总数超过上限。
     *        RTC 系统会限制单个房间内发布的视频流数。如果房间内发布视频流数已达上限时，本地用户再向房间中发布视频流时会失败，同时会收到此错误通知。
     */
    ByteRTCErrorCodeOverVideoPublishLimit = -1082,
};

/**
 * @hidden
 */
typedef NS_ENUM(NSInteger, ByteRTCSubscribeState) {
    /** 
     * @brief 订阅流成功
     */
    ByteRTCSubscribeStateSuccess,
    /** 
     * @brief 还没有加入房间
     */
    ByteRTCSubscribeStateFailedNotInRoom,
    /** 
     * @brief 没有找到流
     */
    ByteRTCSubscribeStateFailedStreamNotFound,
    /** 
     * @brief 超过订阅流数上限
     */
    ByteRTCSubscribeStateFailedOverLimit,
};

/** 
 * @type keytype
 * @brief 设置本地视频属性的返回状态。
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoStreamState) {
    /** 
     * @brief 设置本地视频属性成功
    */
   ByteRTCVideoStreamStateSuccess                 = 0,
    /** 
     * @brief 本地视频属性参数不合法
    */
   ByteRTCVideoStreamStateInvalid                 = -2,
};

/** 
 * @type errorcode
 * @brief 回调警告码。
 *        警告码说明 SDK 内部遇到问题正在尝试恢复。警告码仅作通知。
 */
typedef NS_ENUM(NSInteger, ByteRTCWarningCode) {
    /**
     * @hidden
     */
    ByteRTCWarningCodeGetRoomFailed              = -2000,
    /** 
     * @brief 进房失败。  <br>
     *        初次进房或者由于网络状况不佳断网重连时，由于服务器错误导致进房失败。SDK 会自动重试进房。
     */
    ByteRTCWarningCodeJoinRoomFailed             = -2001,
    /** 
     * @brief 发布音视频流失败。
     *        当你在所在房间中发布音视频流时，由于服务器错误导致发布失败。SDK 会自动重试发布。
     */
    ByteRTCWarningCodePublishStreamFailed        = -2002,
    /** 
     * @brief 订阅音视频流失败。
     *        当前房间中找不到订阅的音视频流导致订阅失败。SDK 会自动重试订阅，若仍订阅失败则建议你退出重试。
     */
    ByteRTCWarningCodeSubscribeStreamFailed404  = -2003,
    /** 
     * @brief 订阅音视频流失败。
     *        当你订阅所在房间中的音视频流时，由于服务器错误导致订阅失败。SDK 会自动重试订阅。
     */
    ByteRTCWarningCodeSubscribeStreamFailed5xx  = -2004,
    /** 
     * @hidden
     * @brief 函数调用顺序错误，当前代码中未使用。
     */
    ByteRTCWarningCodeInvokeError = -2005,
    /** 
     * @hidden
     * @brief 调度异常，服务器返回的媒体服务器地址不可用。
     */
    ByteRTCWarningCodeInvalidExpectMediaServerAddress = -2007,
    /** 
     * @brief 当调用 setUserVisibility:{@link #ByteRTCEngineKit#setUserVisibility:} 将自身可见性设置为 false 后，再尝试发布流会触发此警告。  <br>
     */
    ByteRTCWarningCodePublishStreamForbiden = -2009,
    /** 
     * @hidden
     * @brief 自动订阅模式未关闭时，尝试开启手动订阅模式会触发此警告。  <br>
     *        你需在进房前调用 enableAutoSubscribe:videoMode:{@link #ByteRTCEngineKit#enableAutoSubscribe:videoMode:} 方法关闭自动订阅模式，再调用 subscribeStream:subscribeConfig:{@link #ByteRTCEngineKit#subscribeStream:subscribeConfig:} 方法手动订阅音视频流。
     */
    ByteRTCWarningCodeSubscribeStreamForbiden = -2010,
    /** 
     * @brief 发送自定义广播消息失败，当前你未在房间中。
     */
    ByteRTCWarningCodeSendCustomMessage = -2011,
    /** 
     * @brief 当房间内人数超过 500 人时，停止向房间内已有用户发送 rtcEngine:onUserJoined:elapsed:{@link #ByteRTCEngineDelegate#rtcEngine:onUserJoined:elapsed:} 和 rtcEngine:onUserLeave:reason:{@link #ByteRTCEngineDelegate#rtcEngine:onUserLeave:reason:} 回调，并通过广播提示房间内所有用户。
     */
    ByteRTCWarningCodeCodeUserNotifyStop = -2013,
    /** 
     * @brief 摄像头权限异常，当前应用没有获取摄像头权限
     */
    ByteRTCWarningCodeNoCameraPermission            = -5001,
    /** 
     * @brief 麦克风权限异常，当前应用没有获取麦克风权限
     * @deprecated since 333.1, use ByteRTCMediaDeviceWarning instead
     */
    ByteRTCWarningCodeNoMicrophonePermission        = -5002,
    /** 
     * @brief 音频采集设备启动失败。  <br>
     *        启动音频采集设备失败，当前设备可能被其他应用占用。
     * @deprecated since 333.1, use ByteRTCMediaDeviceWarning instead
     */
    ByteRTCWarningCodeAudioDeviceManagerRecordingStartFail     = -5003,
    /** 
     * @brief 音频播放设备启动失败警告。  <br>
     *        可能由于系统资源不足，或参数错误。
     * @deprecated since 333.1, use ByteRTCMediaDeviceWarning instead
     */
    ByteRTCWarningCodeAudioDeviceManagerPlayoutStartFail = -5004,
    /** 
     * @brief 无可用音频采集设备。  <br>
     *        启动音频采集设备失败，请插入可用的音频采集设备。
     * @deprecated since 333.1, use ByteRTCMediaDeviceWarning instead
     */
    ByteRTCWarningCodeNoRecordingDevice = -5005,
    /** 
     * @brief 无可用音频播放设备。  <br>
     *        启动音频播放设备失败，请插入可用的音频播放设备。
     * @deprecated since 333.1, use ByteRTCMediaDeviceWarning instead
     */
    ByteRTCWarningCodeNoPlayoutDevice = -5006,
    /** 
     * @brief 当前音频设备没有采集到有效的声音数据，请检查更换音频采集设备。
     * @deprecated since 333.1, use ByteRTCMediaDeviceWarning instead
     */
    ByteRTCWarningCodeRecordingSilence = -5007,
    /** 
     * @brief 媒体设备误操作警告。  <br>
     *        使用自定义采集时，不可调用内部采集开关，调用时触发此警告。
     * @deprecated since 333.1, use ByteRTCMediaDeviceWarning instead
     */
    ByteRTCWarningCodeMediaDeviceOperationDennied = -5008,
    /** 
     * @brief 不支持在 publishScreen{@link #ByteRTCEngineKit#publishScreen} 之后，通过 setScreenAudioSourceType:{@link #ByteRTCEngineKit#setScreenAudioSourceType:} 设置屏幕音频采集类型
     */
    ByteRTCWarningSetScreenAudioSourceTypeFailed = -5009,

    /** 
     * @brief 不支持在 publishScreen{@link #ByteRTCEngineKit#publishScreen} 之后，通过 setScreenAudioStreamIndex:{@link #ByteRTCEngineKit#setScreenAudioStreamIndex:} 设置屏幕音频混流类型
     */
    ByteRTCWarningSetScreenAudioStreamIndexFailed = -5010,
    /**  
     * @brief 设置语音音高不合法
     */
    ByteRTCWarningInvalidVoicePitch = -5011,
    /** 
     * @brief 指定的内部渲染画布句柄无效。  <br>
     *        当你调用 setLocalVideoCanvas:withCanvas:{@link #ByteRTCEngineKit#setLocalVideoCanvas:withCanvas:} 或 setRemoteVideoCanvas:withIndex:withCanvas:{@link #ByteRTCEngineKit#setRemoteVideoCanvas:withIndex:withCanvas:} 时指定了无效的画布句柄，触发此回调。
     */
    ByteRTCWarningCodeInvalidCanvasHandle = -6001
};

/** 
 * @type errorcode
 * @brief 转推直播功能错误码。
 */
typedef NS_ENUM(NSInteger, ByteRTCTranscodingError) {
    /** 
     * @brief 推流成功。
     */
    ByteRTCTranscodingErrorOK = 0,
    /** 
     * @brief 推流参数错误。你必须更新合流参数并重试。
     */
    ByteRTCTranscodingErrorInvalidArgument = 1,
    /** 
     * @brief 和 RTC 服务端建立连接失败。会自动重连
     */
    ByteRTCTranscodingErrorSubscribe = 2,
    /** 
     * @brief 合流服务中间过程存在错误，建议重试。
     */
    ByteRTCTranscodingErrorProcessing = 3,
    /** 
     * @brief 推流失败，可以等待服务端重新推流。
     */
    ByteRTCTranscodingErrorPublish = 4,
};

/** 
 * @type keytype
 * @brief 性能回退或者恢复的原因
 */
typedef NS_ENUM(NSInteger, ByteRTCPerformanceAlarmReason) {
    /** 
     * @brief 网络原因差，造成了发送性能回退。仅在开启发送性能回退时，会收到此原因。
     */
    ByteRTCPerformanceAlarmReasonBandwidthFallback = 0,
    /** 
     * @brief 网络性能恢复，发送性能回退恢复。仅在开启发送性能回退时，会收到此原因。
     */
    ByteRTCPerformanceAlarmReasonBandwidthResumed = 1,
    /** 
     * @brief 如果未开启发送性能回退，收到此告警时，意味着性能不足；<br>
     *        如果开启了发送性能回退，收到此告警时，意味着性能不足，且已发生发送性能回退。
     */
    ByteRTCPerformanceAlarmReasonFallback = 2,
    /** 
     * @brief 如果未开启发送性能回退，收到此告警时，意味着性能不足已恢复；<br>
     *        如果开启了发送性能回退，收到此告警时，意味着性能不足已恢复，且已发生发送性能回退恢复。
     */
    ByteRTCPerformanceAlarmReasonResumed = 3,
};

/** 
 * @type keytype
 * @brief 性能回退的模式
 */
typedef NS_ENUM(NSInteger, ByteRTCPerformanceAlarmMode) {
    /** 
     * @brief 未开启发布性能回退
     */
    ByteRTCPerformanceAlarmModeNormal = 0,
    /** 
     * @brief 已开启发布性能回退
     */
    ByteRTCPerformanceAlarmModeSimulcast = 1,
};

/** 
 * @type keytype
 * @brief 视频输出方向模式
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoOutputOrientationMode) {
    /** 
     * @brief 自适应布局
     */
    ByteRTCVideoOutputOrientationModeAdaptative = 0,
    /** 
     * @brief 横屏布局
     */
    ByteRTCVideoOutputOrientationModeFixedLandscape = 1,
    /** 
     * @brief 竖屏布局
     */
    ByteRTCVideoOutputOrientationModeFixedPortrait = 2,
};

/** 
 * @hidden
 * @type keytype
 * @deprecated since 329.1 use ByteRTCMirrorType instead
 * @brief 是否开启镜像模式
 */
typedef NS_ENUM(NSUInteger, ByteRTCMirrorMode) {
    /** 
     *  @brief 不开启
     */
    ByteRTCMirrorModeOff = 0,
    /** 
     *  @brief 开启
     */
    ByteRTCMirrorModeOn = 1,
};

/** 
 * @type keytype
 * @brief 设置镜像类型
 */
typedef NS_ENUM(NSUInteger, ByteRTCMirrorType) {
    /** 
     * @brief 本地渲染和编码传输时均无镜像效果
     */
    ByteRTCMirrorTypeNone = 0,
    /** 
     * @brief 本地渲染时有镜像效果，编码传输时无镜像效果
     */
    ByteRTCMirrorTypeRender = 1,
    /** 
     * @brief 本地渲染和编码传输时均有镜像效果
     */
    ByteRTCMirrorTypeRenderAndEncoder = 3,
};

/** 
 * @type keytype
 * @hidden
 * @brief 日志级别。
 */
typedef NS_ENUM(NSUInteger, ByteRTCLogLevel) {
    /** 
     * @hidden
     * @brief 打印 trace 级别及以上级别信息。
     */
    ByteRTCLogLevelTrace,
    /** 
     * @hidden
     * @brief 打印 debug 级别及以上级别信息。
     */
    ByteRTCLogLevelDebug,
    /** 
     * @hidden
     * @brief 打印 info 级别及以上级别信息。
     */
    ByteRTCLogLevelInfo,
    /** 
     * @hidden
     * @brief 打印 warning 级别及以上级别信息。
     */
    ByteRTCLogLevelWarning,
    /** 
     * @hidden
     * @brief 打印 error 级别信息。
     */
    ByteRTCLogLevelError,
};

/** 
 * @type keytype
 * @brief 视频旋转信息，枚举类型，定义了以 90 度为间隔的四种旋转模式。
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoRotation) {
    /** 
     * @brief 视频不做旋转
     */
    ByteRTCVideoRotation0 = 0,
    /** 
     * @brief 视频顺时针旋转 90 度
     */
    ByteRTCVideoRotation90 = 90,
    /** 
     * @brief 视频顺时针旋转 180 度
     */
    ByteRTCVideoRotation180 = 180,
    /** 
     * @brief 视频顺时针旋转 270 度
     */
    ByteRTCVideoRotation270 = 270,
};

/** 
 * @type keytype
 * @brief 视频帧缩放模式
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoStreamScaleMode) {
    /** 
     * @brief 自动缩放模式，默认设置为 ByteRTCVideoStreamScaleModeFitWithCropping。
     */
    ByteRTCVideoStreamScaleModeAuto            = 0,
    /** 
     * @brief 对视频帧进行缩放，直至充满和视窗分辨率一致为止。这一过程不保证等比缩放。
     */
    ByteRTCVideoStreamScaleModeStretch         = 1,
    /** 
     * @brief 视窗填满优先。  <br>
     *        视频帧等比缩放，直至视窗被视频填满。如果视频帧长宽比例与视窗不同，视频帧的多出部分将无法显示。<br>
     *        缩放完成后，视频帧的一边长和视窗的对应边长一致，另一边长大于等于视窗对应边长。
     */
    ByteRTCVideoStreamScaleModeFitWithCropping = 2,
    /** 
     * @brief 视频帧内容全部显示优先。  <br>
     *        视频帧等比缩放，直至视频帧能够在视窗上全部显示。如果视频帧长宽比例与视窗不同，视窗上未被视频帧填满区域将被涂黑。<br>
     *        缩放完成后，视频帧的一边长和视窗的对应边长一致，另一边长小于等于视窗对应边长。保持纵横比来缩放图像，填充短边
     */
    ByteRTCVideoStreamScaleModeFitWithFilling  = 3,
};

/** 
 * @hidden
 * @type keytype
 * @brief 视频编码模式
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoCodecMode) {
    /** 
     * @brief 自动选择
    */
   ByteRTCVideoCodecModeAuto     = 0,
    /** 
     * @brief 硬编码
    */
   ByteRTCVideoCodecModeHardware = 1,
    /** 
     * @brief 软编码
    */
   ByteRTCVideoCodecModeSoftware = 2
};

/** 
 * @type keytype
 * @brief 视频编码类型
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoCodecType) {
    /** 
     * @brief 未知类型
     */
    ByteRTCVideoCodecTypeUnknown = 0,
    /** 
     * @brief 标准 H264 编码器
     */
    ByteRTCVideoCodecTypeH264 = 1,
    /** 
     * @brief 标准 ByteVC1 编码器
     */
    ByteRTCVideoCodecTypeByteVC1 = 2,
};

/** 
 * @type keytype
 * @brief 编码帧类型
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoPictureType) {
    /** 
     * @brief 未知类型
     */
    ByteRTCVideoPictureTypeUnknown = 0,
    /** 
     * @brief I帧，关键帧，编解码不需要参考其他视频帧
     */
    ByteRTCVideoPictureTypeI = 1,
    /** 
     * @brief P帧，向前参考帧，编解码需要参考前一帧视频帧
     */
    ByteRTCVideoPictureTypeP = 2,
    /** 
     * @brief B帧，前后参考帧，编解码需要参考前后两帧视频帧
     */
    ByteRTCVideoPictureTypeB = 3,
};

/** 
 * @type keytype
 * @brief 网络不好时的视频编码降级策略
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoEncoderPreference) {
    /** 
     * @brief 不降级
     */
    ByteRTCVideoEncoderPreferenceDisabled          = 0,
    /** 
     * @brief 优先保证帧率，以保证视频流畅度
     */
    ByteRTCVideoEncoderPreferenceMaintainFramerate = 1,
    /** 
     * @brief 优先保证画质
     */
    ByteRTCVideoEncoderPreferenceMaintainQuality   = 2,
    /** 
     * @brief 平衡画质与帧率
     */
    ByteRTCVideoEncoderPreferenceBalance           = 3,
};


/** 
 * @type errorcode
 * @brief 登录结果  <br>
 *        调用 login:uid:{@link #ByteRTCEngineKit#login:uid:} 登录的结果，会通过 rtcEngine:onLoginResult:errorCode:elapsed:{@link #ByteRTCEngineDelegate#rtcEngine:onLoginResult:errorCode:elapsed:} 回调通知用户。
 */
typedef NS_ENUM(NSInteger, ByteRTCLoginErrorCode) {
    /** 
     * @brief 调用 login:uid:{@link #ByteRTCEngineKit#login:uid:} 方法登录成功。
     */
    ByteRTCLoginErrorCodeSuccess = 0,
    /** 
     * @brief 调用 login:uid:{@link #ByteRTCEngineKit#login:uid:} 方法时使用的 Token 无效或过期失效。需要用户重新获取 Token。
     */
    ByteRTCLoginErrorCodeInvalidToken = -1000,
    /** 
     * @brief 登录错误  <br>
     *        调用 login:uid:{@link #ByteRTCEngineKit#login:uid:} 方法时发生未知错误导致登录失败。需要用户重新登录。
     */
    ByteRTCLoginErrorCodeLoginFailed = -1001,
    /** 
     * @brief 调用 login:uid:{@link #ByteRTCEngineKit#login:uid:} 方法时传入的用户 ID 有问题。
     */
    ByteRTCLoginErrorCodeInvalidUserId = -1002,
    /** 
     * @brief 调用 login:uid:{@link #ByteRTCEngineKit#login:uid:} 登录时服务器错误。
     */
    ByteRTCLoginErrorCodeServerError = -1003,
};
/** 
 * @type keytype
 * @brief 消息发送结果。
 */
typedef NS_ENUM(NSInteger, ByteRTCUserMessageSendResult) {
    /** 
     * @brief 向房间内单个用户发送消息成功
     */
    ByteRTCUserMessageSendResultSuccess = 0,
    /** 
     * @brief 发送超时，没有发送。
     */
    ByteRTCUserMessageSendResultTimeout = 1,
    /** 
     * @brief 通道断开，没有发送
     */
    ByteRTCUserMessageSendResultBroken = 2,
    /** 
     * @brief 找不到接收方
     */
    ByteRTCUserMessageSendResultNoReceiver = 3,
    /** 
     * @brief 获取级联路径失败
     */
    ByteRTCUserMessageSendResultNoRelayPath = 4,
    /** 
     * @brief 消息发送方没有加入房间
     */
    ByteRTCUserMessageSendResultNotJoin = 100,
    /** 
     * @brief 连接未完成初始化
     */
    ByteRTCUserMessageSendResultInit = 101,
    /** 
     * @brief 没有可用的数据传输通道连接
     */
    ByteRTCUserMessageSendResultNoConnection = 102,
    /** 
     * @brief 消息超过最大长度，当前为64KB
     */
    ByteRTCUserMessageSendResultExceedMaxLength = 103,
    /** 
     * @brief 接收消息的单个用户 id 为空
     */
    ByteRTCUserMessageSendResultEmptyUser = 104,
    /** 
     * @brief 房间外或业务服务器消息发送方没有登录
     */
    ByteRTCUserMessageSendResultNotLogin = 105,
    /** 
     * @brief 发送消息给业务方服务器之前没有设置参数
     */
    ByteRTCUserMessageSendResultServerParamsNotSet = 106,
    /** 
     * @brief 失败，未知错误。
     */
    ByteRTCUserMessageSendResultUnknown = 1000,
};

/** 
 * @type keytype
 * @brief 用户在线状态
 */
typedef NS_ENUM(NSInteger, ByteRTCUserOnlineStatus) {
    /** 
     * @brief 对端用户离线
     *        对端用户已经调用 logout{@link #ByteRTCEngineKit#logout}，或者没有调用 login:uid:{@link #ByteRTCEngineKit#login:uid:} 进行登录
     */
    ByteRTCUserOnlineStatusOffline = 0,
    /** 
     * @brief 对端用户在线
     *        对端用户调用 login:uid:{@link #ByteRTCEngineKit#login:uid:} 登录，并且连接状态正常
     */
    ByteRTCUserOnlineStatusOnline = 1,
    /** 
     * @brief 无法获取对端用户在线状态
     *        发生级联错误、对端用户在线状态异常时返回
     */
    ByteRTCUserOnlineStatusUnreachable = 2,
};
/** 
 * @type keytype
 * @brief 广播消息发送结果。
 */
typedef NS_ENUM(NSInteger, ByteRTCRoomMessageSendResult) {
    /** 
     * @brief 向房间内所有用户发送消息成功
     */
    ByteRTCRoomMessageSendResultSuccess = 200,
    /** 
     * @brief 失败，没有加入房间。
     */
    ByteRTCRoomMessageSendResultNotJoin = 100,
    /** 
     * @brief 失败，连接未完成初始化。
     */
    ByteRTCRoomMessageSendResultInit = 101,
    /** 
     * @brief 失败，没有可用的连接。
     */
    ByteRTCRoomMessageSendResultNoConnection = 102,
    /** 
     * @brief 消息超过最大长度，当前为64KB
     */
    ByteRTCRoomMessageSendResultExceedMaxLength = 103,
    /** 
     * @brief 失败，未知错误。
     */
    ByteRTCRoomMessageSendResultUnknown = 1000,
};

/** 
 * @hidden
 * @type keytype
 * @brief SDK 的服务器环境。
 */
typedef NS_ENUM(NSInteger, ByteRTCEnv) {
    /** 
     * @hidden
     * @brief 线上环境。
     */
    ByteRTCEnvProduct = 0,
    /** 
     * @hidden
     * @brief BOE 环境。
     */
    ByteRTCEnvBOE = 1,
    /** 
     * @hidden
     * @brief 测试环境。
     */
    ByteRTCEnvTest = 2,
};

/** 
 * @hidden
 * @type keytype
 * @brief 设置引擎工作模式
 */
typedef NS_ENUM(NSUInteger, ByteRTCMode) {
    /** 
     * @brief 通用模式，该模式下只能进行普通会议模式的语音通话，开启自动发布订阅。
     */
    ByteRTCModeGeneral = 0,
    /** 
     * @brief 游戏语音模式，该模式下关闭自动发布订阅，会按照游戏业务的策略进行主动发布订阅语音。
     */
    ByteRTCModeLocalAudio = 1,
};

/** 
 * @hidden
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
 * @brief 本地发布的音视频流回退选项
 */
typedef NS_ENUM(NSUInteger, ByteRTCPublishFallbackOption) {
    /** 
     * @brief 关闭发送视频流时的性能回退功能，默认值
     */
    ByteRTCPublishFallbackOptionDisabled = 0,
    /** 
     * @brief 开启在网络情况不佳或设备性能不足时只发送小流的功能
     */
    ByteRTCPublishFallbackOptionSimulcast = 1,
};

/** 
 * @hidden
 * @type keytype
 * @brief 订阅模式选项。
 */
typedef NS_ENUM(NSUInteger, ByteRTCSubscribeMode) {
    /** 
     * @brief 自动订阅模式。SDK 会自动为你订阅房间中的每一路流。  <br>
     */
    ByteRTCSubscribeModeAuto = 0,
    /** 
     * @brief 手动订阅模式。SDK 不自动订阅房间内的音视频流。你应根据需要调用 subscribeUserStream:streamType:mediaType:videoConfig:{@link #ByteRTCEngineKit#subscribeUserStream:streamType:mediaType:videoConfig:} 方法手动订阅其他用户发布的音视频流。
     */
    ByteRTCSubscribeModeManual = 1
};

/** 
 * @type keytype
 * @brief 订阅回退选项
 */
typedef NS_ENUM(NSUInteger, ByteRTCSubscribeFallbackOption) {
    /** 
     * @brief 下行网络较弱时，关闭订阅音视频流时的性能回退功能，默认值
     */
    ByteRTCSubscribeFallbackOptionDisabled = 0,
    /** 
     * @brief 下行网络较弱时只接收视频小流
     */
    ByteRTCSubscribeFallbackOptionVideoStreamLow = 1,
    /** 
     * @brief 下行网络较弱时，先尝试只接收视频小流；如果网络环境无法显示视频，则再回退到只接收远端订阅的音频流
     */
    ByteRTCSubscribeFallbackOptionAudioOnly = 2,
};

/** 
 * @type keytype
 * @brief 远端用户优先级。在性能不足需要回退时，会先回退优先级低的用户的音视频流
 */
typedef NS_ENUM(NSUInteger, ByteRTCRemoteUserPriority) {
    /** 
     * @brief 用户优先级为低，默认值
     */
    ByteRTCRemoteUserPriorityLow = 0,
    /** 
     * @brief 用户优先级为正常
     */
    ByteRTCRemoteUserPriorityMedium = 100,
    /** 
     * @brief 用户优先级为高
     */
    ByteRTCRemoteUserPriorityHigh = 200,
};

/** 
 * @type keytype
 * @brief 本地用户订阅的远端流触发回退策略的原因。
 */
typedef NS_ENUM(NSInteger, ByteRTCFallbackOrRecoverReason) {
    /** 
     * @brief 其他原因，非带宽和性能原因引起的回退或恢复。默认值
     */
    ByteRTCFallbackOrRecoverReasonUnknown = -1,
    /** 
     * @brief 由带宽不足导致的订阅端音视频流回退。
     */
    ByteRTCFallbackOrRecoverReasonSubscribeFallbackByBandwidth = 0,
    /** 
     * @brief 由性能不足导致的订阅端音视频流回退。
     */
    ByteRTCFallbackOrRecoverReasonSubscribeFallbackByPerformance = 1,
    /** 
     * @brief 由带宽恢复导致的订阅端音视频流恢复。
     */
    ByteRTCFallbackOrRecoverReasonSubscribeRecoverByBandwidth = 2,
    /** 
     * @brief 由性能恢复导致的订阅端音视频流恢复。
     */
    ByteRTCFallbackOrRecoverReasonSubscribeRecoverByPerformance = 3,
    /** 
     * @brief 由带宽不足导致的发布端音视频流回退。
     */
    ByteRTCFallbackOrRecoverReasonPublishFallbackByBandwidth = 4,
    /** 
     * @brief 由性能不足导致的发布端音视频流回退。
     */
    ByteRTCFallbackOrRecoverReasonPublishFallbackByPerformance = 5,
    /** 
     * @brief 由带宽恢复导致的发布端音视频流恢复。
     */
    ByteRTCFallbackOrRecoverReasonPublishRecoverByBandwidth = 6,
    /** 
     * @brief 由性能恢复导致的发布端音视频流恢复。
     */
    ByteRTCFallbackOrRecoverReasonPublishRecoverByPerformance = 7,
};

/** 
 * @type keytype
 * @brief 本地音频流状态。  <br>
 *        SDK 通过 rtcEngine:onLocalAudioStateChanged:error:{@link #ByteRTCEngineDelegate#rtcEngine:onLocalAudioStateChanged:error:} 回调该状态。  <br>
 */
typedef NS_ENUM(NSInteger, ByteRTCLocalAudioStreamState) {
    /** 
     * @brief 本地音频默认初始状态。
     *        麦克风停止工作时回调该状态，对应错误码 ByteRTCLocalAudioStreamError{@link #ByteRTCLocalAudioStreamError} 中的 ByteRTCLocalAudioStreamErrorOk
     */
    ByteRTCLocalAudioStreamStateStopped = 0,
    /** 
     * @brief 本地音频录制设备启动成功。
     *        采集到音频首帧时回调该状态，对应错误码 ByteRTCLocalAudioStreamError{@link #ByteRTCLocalAudioStreamError} 中的 ByteRTCLocalAudioStreamErrorOk
     */
    ByteRTCLocalAudioStreamStateRecording = 1,
    /** 
     * @brief 本地音频首帧编码成功。
     *        音频首帧编码成功时回调该状态，对应错误码 ByteRTCLocalAudioStreamError{@link #ByteRTCLocalAudioStreamError} 中的 ByteRTCLocalAudioStreamErrorOk
     */
    ByteRTCLocalAudioStreamStateEncoding = 2,
    /** 
     * @brief  本地音频启动失败，在以下时机回调该状态：  <br>
     *       + 本地录音设备启动失败，对应错误码 ByteRTCLocalAudioStreamError{@link #ByteRTCLocalAudioStreamError} 中的 ByteRTCLocalAudioStreamErrorRecordFailure  <br>
     *       + 检测到没有录音设备权限，对应错误码 ByteRTCLocalAudioStreamError{@link #ByteRTCLocalAudioStreamError} 中的 ByteRTCLocalAudioStreamErrorDeviceNoPermission <br>
     *       + 音频编码失败，对应错误码 ByteRTCLocalAudioStreamError{@link #ByteRTCLocalAudioStreamError} 中的 ByteRTCLocalAudioStreamError <br>
     */
    ByteRTCLocalAudioStreamStateFailed = 3,
};

/** 
 * @type keytype
 * @brief 本地音频流状态改变时的错误码。
 *        SDK 通过 rtcEngine:onLocalAudioStateChanged:error:{@link #ByteRTCEngineDelegate#rtcEngine:onLocalAudioStateChanged:error:} 回调该错误码。
 */
typedef NS_ENUM(NSInteger, ByteRTCLocalAudioStreamError) {
    /** 
     * @brief 本地音频状态正常
     */
    ByteRTCLocalAudioStreamErrorOk = 0,
    /** 
     * @brief 本地音频出错原因未知
     */
    ByteRTCLocalAudioStreamErrorFailure = 1,
    /** 
     * @brief 没有权限启动本地音频录制设备
     */
    ByteRTCLocalAudioStreamErrorDeviceNoPermission = 2,
    /** 
     * @hidden
     * @brief 本地音频录制设备已经在使用中
     * @notes 该错误码暂未使用
     */
    ByteRTCLocalAudioStreamErrorDeviceBusy = 3,
    /** 
     * @brief 本地音频录制失败，建议你检查录制设备是否正常工作
     */
    ByteRTCLocalAudioStreamErrorRecordFailure = 4,
    /** 
     * @brief 本地音频编码失败
     */
    ByteRTCLocalAudioStreamErrorEncodeFailure = 5,
    /** 
     * @brief 没有可用的音频录制设备
     */
    ByteRTCLocalAudioStreamErrorNoRecordingDevice = 6
};

/** 
 * @type keytype
 * @brief 本地视频流状态
 */
typedef NS_ENUM(NSInteger, ByteRTCLocalVideoStreamState) {
    /** 
     * @brief 本地视频默认初始状态
     *        摄像头停止工作时回调该状态，对应错误码 ByteRTCLocalVideoStreamError{@link #ByteRTCLocalVideoStreamError} 中的 ByteRTCLocalVideoStreamErrorOk
     */
    ByteRTCLocalVideoStreamStateStopped = 0,
    /** 
     * @brief 本地视频录制设备启动成功
     *        采集到视频首帧时回调该状态，对应错误码 ByteRTCLocalVideoStreamError{@link #ByteRTCLocalVideoStreamError} 中的 ByteRTCLocalVideoStreamErrorOk
     */
    ByteRTCLocalVideoStreamStateRecording = 1,
    /** 
     * @brief 本地视频首帧编码成功
     *        本地视频首帧编码成功时回调该状态，对应错误码 ByteRTCLocalVideoStreamError{@link #ByteRTCLocalVideoStreamError} 中的 ByteRTCLocalVideoStreamErrorOk
     */
    ByteRTCLocalVideoStreamStateEncoding = 2,
    /** 
     * @brief  本地视频启动失败, 在以下时机回调该状态：  <br>
     *       + 本地采集设备启动失败，对应错误码 ByteRTCLocalVideoStreamError{@link #ByteRTCLocalVideoStreamError} 中的 ByteRTCLocalVideoStreamErrorCaptureFailure  <br>
     *       + 检测到没有摄像头权限，对应错误码 ByteRTCLocalVideoStreamError{@link #ByteRTCLocalVideoStreamError} 中的 ByteRTCLocalVideoStreamErrorDeviceNoPermission <br>
     *       + 视频编码失败，对应错误码 ByteRTCLocalVideoStreamError{@link #ByteRTCLocalVideoStreamError} 中的 ByteRTCLocalVideoStreamErrorEncodeFailure  <br>
     */
    ByteRTCLocalVideoStreamStateFailed = 3,
};

/** 
 * @type keytype
 * @brief 本地视频状态改变时的错误码
 */
typedef NS_ENUM(NSInteger, ByteRTCLocalVideoStreamError) {
    /** 
     * @brief 本地视频状态正常（本地视频状态改变正常时默认返回值）
     */
    ByteRTCLocalVideoStreamErrorOk = 0,
    /** 
     * @brief 本地视频流发布失败
     */
    ByteRTCLocalVideoStreamErrorFailure = 1,
    /** 
     * @brief 没有权限启动本地视频采集设备
     */
    ByteRTCLocalVideoStreamErrorDeviceNoPermission = 2,
    /** 
     * @brief 本地视频采集设备被占用
     */
    ByteRTCLocalVideoStreamErrorDeviceBusy = 3,
    /** 
     * @brief 本地视频采集设备不存在或已移除
     */
    ByteRTCLocalVideoStreamErrorDeviceNotFound = 4,
    /** 
     * @brief 本地视频采集失败，建议检查采集设备是否正常工作
     */
    ByteRTCLocalVideoStreamErrorCaptureFailure = 5,
    /** 
     * @brief 本地视频编码失败
     */
    ByteRTCLocalVideoStreamErrorEncodeFailure = 6,
};

/** 
 * @type keytype
 * @brief 用户订阅的远端音频流状态。  <br>
 *        SDK 通过 rtcEngine:onRemoteAudioStateChanged:state:reason:{@link #ByteRTCEngineDelegate#rtcEngine:onRemoteAudioStateChanged:state:reason:} 回调该状态。  <br>
 */
typedef NS_ENUM(NSInteger, ByteRTCRemoteAudioState) {
    /** 
     * @brief  远端音频流默认初始状态，在以下时机回调该状态：  <br>
     *       + 本地用户停止接收远端音频流，对应原因是 ByteRTCRemoteAudioStateChangeReason{@link #ByteRTCRemoteAudioStateChangeReason} 中的 `ByteRTCRemoteAudioStateChangeReasonLocalMuted`  <br>
     *       + 远端用户停止发送音频流，对应原因是 ByteRTCRemoteAudioStateChangeReason{@link #ByteRTCRemoteAudioStateChangeReason} 中的 `ByteRTCRemoteAudioStateChangeReasonRemoteMuted` <br>
     *       + 远端用户离开房间，对应原因是 ByteRTCRemoteAudioStateChangeReason{@link #ByteRTCRemoteAudioStateChangeReason} 中的 `ByteRTCRemoteAudioStateChangeReasonRemoteOffline` <br>
     */
    ByteRTCRemoteAudioStateStopped = 0,
    /** 
     * @brief 开始接收远端音频流首包。  <br>
     *        刚收到远端音频流首包时，会触发回调 rtcEngine:onRemoteAudioStateChanged:state:reason:{@link #ByteRTCEngineDelegate#rtcEngine:onRemoteAudioStateChanged:state:reason:}，
     *        对应原因是 ByteRTCRemoteAudioStateChangeReason{@link #ByteRTCRemoteAudioStateChangeReason} 中的 `ByteRTCRemoteAudioStateChangeReasonLocalUnmuted`
     */
    ByteRTCRemoteAudioStateStarting = 1,
    /** 
     * @brief  远端音频流正在解码，正常播放，在以下时机回调该状态：  <br>
     *       + 成功解码远端音频首帧，对应原因是 ByteRTCRemoteAudioStateChangeReason{@link #ByteRTCRemoteAudioStateChangeReason} 中的 `ByteRTCRemoteAudioStateChangeReasonLocalUnmuted` <br>
     *       + 网络由阻塞恢复正常，对应原因是 ByteRTCRemoteAudioStateChangeReason{@link #ByteRTCRemoteAudioStateChangeReason} 中的 `ByteRTCRemoteAudioStateChangeReasonNetworkRecovery` <br>
     *       + 本地用户恢复接收远端音频流，对应原因是 ByteRTCRemoteAudioStateChangeReason{@link #ByteRTCRemoteAudioStateChangeReason} 中的 `ByteRTCRemoteAudioStateChangeReasonLocalUnmuted` <br>
     *       + 远端用户恢复发送音频流，对应原因是 ByteRTCRemoteAudioStateChangeReason{@link #ByteRTCRemoteAudioStateChangeReason} 中的 `ByteRTCRemoteAudioStateChangeReasonRemoteUnmuted`<br>
     */
    ByteRTCRemoteAudioStateDecoding = 2,
    /** 
     * @brief 远端音频流卡顿。<br>
     *        网络阻塞导致丢包率大于 40% 时，会触发回调 rtcEngine:onRemoteAudioStateChanged:state:reason:{@link #ByteRTCEngineDelegate#rtcEngine:onRemoteAudioStateChanged:state:reason:}，
     *        对应原因是 ByteRTCRemoteAudioStateChangeReason{@link #ByteRTCRemoteAudioStateChangeReason} 中的 `ByteRTCRemoteAudioStateChangeReasonNetworkCongestion`
     */
    ByteRTCRemoteAudioStateFrozen = 3,
    /** 
     * @hidden
     * @brief 远端音频流播放失败
     * @notes 该错误码暂未使用
     */
    ByteRTCRemoteAudioStateFailed = 4,
};

/** 
 * @type keytype
 * @brief 接收远端音频流状态改变的原因。<br>
 *        用户可以通过 rtcEngine:onRemoteAudioStateChanged:state:reason:{@link #ByteRTCEngineDelegate#rtcEngine:onRemoteAudioStateChanged:state:reason:} 了解该状态。
 */
typedef NS_ENUM(NSInteger, ByteRTCRemoteAudioStateChangeReason) {
    /** 
     * @brief 内部原因
     */
    ByteRTCRemoteAudioStateChangeReasonInternal = 0,
    /** 
     * @brief 网络阻塞
     */
    ByteRTCRemoteAudioStateChangeReasonNetworkCongestion = 1,
    /** 
     * @brief 网络恢复正常
     */
    ByteRTCRemoteAudioStateChangeReasonNetworkRecovery = 2,
    /** 
     * @brief 本地用户停止接收远端音频流
     */
    ByteRTCRemoteAudioStateChangeReasonLocalMuted = 3,
    /** 
     * @brief 本地用户恢复接收远端音频流
     */
    ByteRTCRemoteAudioStateChangeReasonLocalUnmuted = 4,
    /** 
     * @brief 远端用户停止发送音频流
     */
    ByteRTCRemoteAudioStateChangeReasonRemoteMuted = 5,
    /** 
     * @brief 远端用户恢复发送音频流
     */
    ByteRTCRemoteAudioStateChangeReasonRemoteUnmuted = 6,
    /** 
     * @brief 远端用户离开房间
     */
    ByteRTCRemoteAudioStateChangeReasonRemoteOffline = 7,
};

/** 
 * @type keytype
 * @brief 远端视频流状态
 */
typedef NS_ENUM(NSInteger, ByteRTCRemoteVideoState) {
    /** 
     * @brief  远端视频流默认初始状态, 在以下时机回调该状态：  <br>
     *       + 本地用户停止接收远端视频流，对应错误码 ByteRTCRemoteVideoStateChangeReason{@link #ByteRTCRemoteVideoStateChangeReason} 中的 ByteRTCRemoteVideoStateChangeReasonLocalMuted  <br>
     *       + 远端用户停止发送视频流，对应错误码 ByteRTCRemoteVideoStateChangeReason{@link #ByteRTCRemoteVideoStateChangeReason} 中的 ByteRTCRemoteVideoStateChangeReasonRemoteMuted <br>
     *       + 远端用户离开房间，对应错误码 ByteRTCRemoteVideoStateChangeReason{@link #ByteRTCRemoteVideoStateChangeReason} 中的 ByteRTCRemoteVideoStateChangeReasonRemoteOffline  <br>
     */
    ByteRTCRemoteVideoStateStopped = 0,
    /** 
     * @brief 本地用户已接收远端视频首包 <br>
     *        收到远端视频首包时回调该状态，对应错误码 ByteRTCRemoteVideoStateChangeReason{@link #ByteRTCRemoteVideoStateChangeReason} 中的 ByteRTCRemoteVideoStateChangeReasonLocalUnmuted
     */
    ByteRTCRemoteVideoStateStarting = 1,
    /** 
     * @brief  远端视频流正在解码，正常播放, 在以下时机回调该状态：  <br>
     *       + 成功解码远端视频首帧，对应错误码 ByteRTCRemoteVideoStateChangeReason{@link #ByteRTCRemoteVideoStateChangeReason} 中的 ByteRTCRemoteVideoStateChangeReasonLocalUnmuted  <br>
     *       + 网络由阻塞恢复正常，对应错误码 ByteRTCRemoteVideoStateChangeReason{@link #ByteRTCRemoteVideoStateChangeReason} 中的 ByteRTCRemoteVideoStateChangeReasonNetworkRecovery <br>
     *       + 本地用户恢复接收远端视频流，对应错误码 ByteRTCRemoteVideoStateChangeReason{@link #ByteRTCRemoteVideoStateChangeReason} 中的 ByteRTCRemoteVideoStateChangeReasonLocalUnmuted <br>
     *       + 远端用户恢复发送视频流，对应错误码 ByteRTCRemoteVideoStateChangeReason{@link #ByteRTCRemoteVideoStateChangeReason} 中的 ByteRTCRemoteVideoStateChangeReasonRemoteUnmuted  <br>
     */
    ByteRTCRemoteVideoStateDecoding = 2,
    /** 
     * @brief 远端视频流卡顿 <br>
     *        网络阻塞、丢包率等原因造成视频卡顿流时会回报该状态，对应错误码 ByteRTCRemoteVideoStateChangeReason{@link #ByteRTCRemoteVideoStateChangeReason} 中的 ByteRTCRemoteVideoStateChangeReasonNetworkCongestion
     */
    ByteRTCRemoteVideoStateFrozen = 3,
     /** 
      * @brief 远端音频流播放失败 <br>
      * @notes 如果内部处理远端视频流失败，则会回调该方法， 对应错误码 ByteRTCRemoteVideoStateChangeReason{@link #ByteRTCRemoteVideoStateChangeReason} 中的 ByteRTCRemoteVideoStateChangeReasonInternal
      */
     ByteRTCRemoteVideoStateFailed = 4,
};

/** 
 * @type keytype
 * @brief 远端视频流状态改变的原因
 */
typedef NS_ENUM(NSInteger, ByteRTCRemoteVideoStateChangeReason) {
    /** 
     * @brief 内部原因
     */
    ByteRTCRemoteVideoStateChangeReasonInternal = 0,
    /** 
     * @brief 网络阻塞
     */
    ByteRTCRemoteVideoStateChangeReasonNetworkCongestion = 1,
    /** 
     * @brief 网络恢复正常
     */
    ByteRTCRemoteVideoStateChangeReasonNetworkRecovery = 2,
    /** 
     * @brief 本地用户停止接收远端视频流或本地用户禁用视频模块
     */
    ByteRTCRemoteVideoStateChangeReasonLocalMuted = 3,
    /** 
     * @brief 本地用户恢复接收远端视频流或本地用户启用视频模块
     */
    ByteRTCRemoteVideoStateChangeReasonLocalUnmuted = 4,
    /** 
     * @brief 远端用户停止发送视频流或远端用户禁用视频模块
     */
    ByteRTCRemoteVideoStateChangeReasonRemoteMuted = 5,
    /** 
     * @brief 远端用户恢复发送视频流或远端用户启用视频模块
     */
    ByteRTCRemoteVideoStateChangeReasonRemoteUnmuted = 6,
    /** 
     * @brief 远端用户离开房间
     */
    ByteRTCRemoteVideoStateChangeReasonRemoteOffline = 7,
};

/** 
 * @type keytype
 * @brief 当前媒体设备类型
 */
typedef NS_ENUM(NSInteger, ByteRTCMediaDeviceType) {
    /** 
     * @brief 未知音频设备
     */
    ByteRTCMediaDeviceTypeAudioUnknown = -1,
    /** 
     * @brief 音频渲染设备类型
     */
    ByteRTCMediaDeviceTypeAudioRenderDevice = 0,
    /** 
     * @brief 音频采集设备类型
     */
    ByteRTCMediaDeviceTypeAudioCaptureDevice = 1,
    /** 
     *@hidden
     *@brief 视频渲染设备类型，该类型暂无使用
     */
    ByteRTCMediaDeviceTypeVideoRenderDevice = 2,
    /** 
     *@brief 视频采集设备类型
     */
    ByteRTCMediaDeviceTypeVideoCaptureDevice = 3,
    /** 
     * @brief 屏幕流音频设备
     */
    ByteRTCMediaDeviceTypeScreenAudioCaptureDevice = 5
};

/** 
 * @type keytype
 * @brief 设备状态
 */
typedef NS_ENUM(NSInteger, ByteRTCMediaDeviceState) {
    /** 
     *@brief 设备已开启
     */
    ByteRTCMediaDeviceStateStarted = 1,
    /** 
     *@brief 设备已停止
     */
    ByteRTCMediaDeviceStateStopped = 2,
    /** 
     *@brief 设备运行时错误
     */
    ByteRTCMediaDeviceStateRuntimeError = 3,
    /** 
     *@brief 设备已插入
     */
    ByteRTCMediaDeviceStateAdded = 10,
    /** 
     *@brief 设备被移除
     */
    ByteRTCMediaDeviceStateRemoved = 11
};

/** 
 * @type keytype
 * @brief 媒体设备错误类型
 */
typedef NS_ENUM(NSInteger,  ByteRTCMediaDeviceError) {
    /** 
     *@brief 媒体设备正常
     */
    ByteRTCMediaDeviceErrorOK = 0,
    /** 
     *@brief 没有权限启动媒体设备
     */
    ByteRTCMediaDeviceErrorDeviceNoPermission = 1,
    /** 
     *@brief 媒体设备已经在使用中
     */
    ByteRTCMediaDeviceErrorDeviceBusy = 2,
    /** 
     *@brief 媒体设备错误
     */
    ByteRTCMediaDeviceErrorDeviceFailure = 3,
    /** 
     *@brief 未找到指定的媒体设备
     */
    ByteRTCMediaDeviceErrorDeviceNotFound = 4,
    /** 
     *@brief 媒体设备被移除
     */
    ByteRTCMediaDeviceErrorDeviceDisconnected = 5,
    /** 
     * @brief 设备没有数据回调
     */
    ByteRTCMediaDeviceErrorDeviceNoCallback = 6,
    /** 
     * @brief 设备采样率不支持
     */
    ByteRTCMediaDeviceErrorUNSupportFormat = 7
};

/** 
 * @type keytype
 * @brief 媒体设备警告
 */
typedef NS_ENUM(NSInteger, ByteRTCMediaDeviceWarning) {
    /** 
     * @brief 无警告
     */
    ByteRTCMediaDeviceWarningOK = 0,
    /** 
     * @brief 非法设备操作。在使用外部设备时，调用了 SDK 内部设备 API。
     */
    ByteRTCMediaDeviceWarningOperationDenied = 1,
    /** 
     * @brief 采集静音。
     */
    ByteRTCMediaDeviceWarningCaptureSilence = 2,
    // The following warning codes are only valid for meeting scenarios.
    /** 
     * @hidden
     * @brief 音量过大，超过设备采集范围。建议降低麦克风音量或者降低声源音量。
     */
    ByteRTCMediaDeviceWarningDetectClipping = 10,
    /** 
     * @hidden
     * @brief 回声泄露
     */
    ByteRTCMediaDeviceWarningDetectLeakEcho = 11,
    /** 
     * @hidden
     * @brief 低信噪比
     */
    ByteRTCMediaDeviceWarningDetectLowSNR = 12,
    /** 
     * @hidden
     * @brief 采集插零现象
     */
    ByteRTCMediaDeviceWarningDetectInsertSilence = 13,
    /** 
     * @hidden
     * @brief 设备采集静音
     */
    ByteRTCMediaDeviceWarningCaptureDetectSilence = 14,
    /** 
     * @hidden
     * @brief 设备采集静音消失
     */
    ByteRTCMediaDeviceWarningCaptureDetectSilenceDisappear = 15,
    /** 
     * @hidden
     * @brief 啸叫
     */
    ByteRTCMediaDeviceWarningCaptureDetectHowling = 16
};

/** 
 *  @type keytype
 *  @brief 音视频质量反馈问题类型
 */
typedef NS_OPTIONS(NSUInteger, ByteRTCProblemFeedbackOption){
    /** 
     * @brief 没有问题
     */
    ByteRTCProblemFeedbackOptionNone = 0,
    /** 
     * @brief 其他问题
     */
    ByteRTCProblemFeedbackOptionOtherMessage = (1 << 0),
    /** 
     * @brief 声音不清晰
     */
    ByteRTCProblemFeedbackOptionAudioNotClear = (1 << 1),
    /** 
     * @brief 视频不清晰
     */
    ByteRTCProblemFeedbackOptionVideoNotClear = (1 << 2),
    /** 
     * @brief 音视频不同步
     */
    ByteRTCProblemFeedbackOptionNotSync = (1 << 3),
    /** 
     * @brief 音频卡顿
     */
    ByteRTCProblemFeedbackOptionAudioLagging = (1 << 4),
    /** 
     * @brief 视频卡顿
     */
    ByteRTCProblemFeedbackOptionVideoLagging = (1 << 5),
    /** 
     * @brief 连接断开
     */
    ByteRTCProblemFeedbackOptionDisconnected = (1 << 6),
    /** 
     * @brief 无声音
     */
    ByteRTCProblemFeedbackOptionNoAudio = (1 << 7),
    /** 
     * @brief 无画面
     */
    ByteRTCProblemFeedbackOptionNoVideo = (1 << 8),
    /** 
     * @brief 声音过小
     */
    ByteRTCProblemFeedbackOptionAudioStrength = (1 << 9),
    /** 
     * @brief 回声噪音
     */
    ByteRTCProblemFeedbackOptionEcho = (1 << 10),
    /** 
     * @brief 耳返延迟大
     */
    ByteRTCFeedBackProblemTypeEarBackDelay = (1 << 11),
};

/** 
 * @hidden
 * @type keytype
 * @brief 背景模式设置。
 */
typedef NS_ENUM(NSUInteger, ByteRTCBackgroundMode) {
    /** 
     * @brief 无
     */
    ByteRTCBackgroundModeNone = 0,
    /** 
     * @brief 虚化
     */
    ByteRTCBackgroundModeBlur = 1,
    /** 
     * @brief 背景 1
     */
    ByteRTCBackgroundModeA = 2,
    /** 
     * @brief 背景 2
     */
    ByteRTCBackgroundModeB = 3,
};

/** 
 * @hidden
 * @type keytype
 * @brief 分割模型设置。
 */
typedef NS_ENUM(NSUInteger, ByteRTCDivideModel) {
    /** 
     * @brief 自研
     */
    ByteRTCDivideModelDefault = 0,
    /**
     * @brief effect
     */
    ByteRTCDivideModelEffect = 1,
};

/** 
 * @type keytype
 * @brief 首帧发送状态
 */
typedef NS_ENUM(NSUInteger, ByteRTCFirstFrameSendState) {
    /** 
     * @brief 发送中
     */
    ByteRTCFirstFrameSendStateSending = 0,
    /** 
     * @brief 发送成功
     */
    ByteRTCFirstFrameSendStateSent = 1,
    /** 
     * @brief 发送失败
     */
    ByteRTCFirstFrameSendStateEnd = 2,
};

/** 
 * @type keytype
 * @brief 首帧播放状态
 */
typedef NS_ENUM(NSUInteger, ByteRTCFirstFramePlayState) {
    /** 
     * 播放中
     */
    ByteRTCFirstFramePlayStatePlaying = 0,
    /** 
     * 播放成功
     */
    ByteRTCFirstFramePlayStatePlay = 1,
    /** 
     * 播放失败
     */
    ByteRTCFirstFramePlayStateEnd = 2,
};

/** 
 * @type keytype
 * @brief 自定义加密类型
 */
typedef NS_OPTIONS(NSUInteger, ByteRTCEncryptType) {
    /** 
     * @brief 不使用内置加密。默认值。
     */
    ByteRTCEncryptTypeCustomize = 0,
    /** 
     * @brief AES-128-CBC 加密算法
     */
    ByteRTCEncryptTypeAES128CBC = 1,
    /** 
     * @brief AES-256-CBC 加密算法
     */
    ByteRTCEncryptTypeAES256CBC = 2,
    /** 
     * @brief AES-128-ECB 加密算法
     */
    ByteRTCEncryptTypeAES128ECB = 3,
    /** 
     * @brief AES-256-ECB 加密算法
     */
    ByteRTCEncryptTypeAES256ECB = 4
};
/** 
 * @type keytype
 * @brief 数据类型
 */
typedef NS_ENUM(NSUInteger, ByteRTCDataFrameType) {
    /** 
     * @brief SEI 数据
     */
    ByteRTCDataFrameTypeSei = 0,
    /** 
     * @brief 人脸识别数据
     */
    ByteRTCDataFrameTypeRoi = 1,
    /** 
     * @brief 其他数据帧类型
     */
    ByteRTCDataFrameTypeOther = 2,
};

#define BYTERTC_APPLE_EXPORT __attribute__((visibility("default")))
/** 
 * @type keytype
 * @brief 画布信息和渲染模式。<br>
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVideoCanvas : NSObject
/** 
 * @brief 本地视图句柄
 */
@property (strong, nonatomic) UIView* _Nullable view;
/** 
 * @brief 渲染模式，参看 ByteRTCRenderMode{@link #ByteRTCRenderMode}
 */
@property (assign, nonatomic) ByteRTCRenderMode renderMode;
/** 
 * @brief 视图所在的房间 ID
 */
@property (strong, nonatomic) NSString* _Nullable roomId;
/** 
 * @brief 视图对应的用户 ID
 */
@property (strong, nonatomic) NSString* _Nullable uid;
@end

/** 
 * @type keytype
 * @brief 视频帧附加的数据,视频解码后获得的附加数据
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCFrameExtendedData : NSObject
/** 
 * @brief 数据类型，详见 ByteRTCDataFrameType{@link #ByteRTCDataFrameType}。
 */
@property (assign, nonatomic) ByteRTCDataFrameType frameType;
/** 
 * @brief 附加数据
 */
@property (strong, nonatomic) NSData * _Nullable extendedData;
/** 
 * @brief 附加数据长度
 */
@property (assign, nonatomic) NSInteger extendedDataLen;
@end

NS_ASSUME_NONNULL_BEGIN
/** 
 * @type keytype
 * @brief 视频参数
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVideoSolution: NSObject
/** 
 * @brief 视频分辨率
 */
@property (nonatomic, assign) CGSize videoSize;
/** 
 * @brief 视频预设帧率
 */
@property (nonatomic, assign) NSInteger frameRate;
/** 
 * @brief 最高编码码率（千比特每秒）  <br>
 *         建议使用预估值。
 */
@property (nonatomic, assign) NSInteger maxKbps;
/** 
 * @brief 视频帧缩放模式。你可以设置缩放以适应视窗，参见 ByteRTCVideoStreamScaleMode{@link #ByteRTCVideoStreamScaleMode}
 */
@property (nonatomic, assign) ByteRTCVideoStreamScaleMode mode;

/** 
 * @brief 视频编码质量策略，参见 ByteRTCVideoEncoderPreference{@link #ByteRTCVideoEncoderPreference}
 */
@property (nonatomic, assign) ByteRTCVideoEncoderPreference encoderPreference;
@end


/** 
 * @type keytype
 * @brief 视频采集参数
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVideoCaptureConfig: NSObject
/** 
 * @brief 视频采集分辨率。
 */
@property (nonatomic, assign) CGSize videoSize;
/** 
 * @brief 视频采集帧率，单位：fps。
 */
@property (nonatomic, assign) NSInteger frameRate;
@end

/** 
 * @type keytype
 * @brief 流属性。
 */
BYTERTC_APPLE_EXPORT @protocol ByteRTCStream <NSObject>
/** 
 * @brief 发布此流的用户 ID 。  <br>
 */
@property (nonatomic, copy, readonly) NSString * userId;
/** 
 * @brief 此流是否为共享屏幕流。  <br>
 */
@property (nonatomic, assign, readonly) BOOL isScreen;
/** 
 * @brief 此流是否包括视频流。  <br>
 */
@property (nonatomic, assign, readonly) BOOL hasVideo;
/** 
 * @brief 流是否包括音频流。  <br>
 */
@property (nonatomic, assign, readonly) BOOL hasAudio;
/** 
 * @brief 视频流的分辨率信息。  <br>
 *         当远端用户调用 setVideoEncoderConfig:config:{@link #ByteRTCEngineKit#setVideoEncoderConfig:config:} 方法发布多个配置的视频流时，此处会包含该用户发布的所有视频流的属性信息。  <br>
 *         参看 ByteRTCVideoSolution{@link #ByteRTCVideoSolution}。  <br>
 */
@property (nonatomic, copy, readonly) NSArray<ByteRTCVideoSolution *> * videoStreamDescriptions;
@end

/** 
 * @type keytype
 * @brief 订阅流的参数配置。用户手动订阅一路音视频流所使用的订阅配置参数。  <br>
 *         用户关闭自动订阅功能，使用手动订阅模式时，通过调用 subscribeUserStream:streamType:mediaType:videoConfig:{@link #ByteRTCEngineKit#subscribeUserStream:streamType:mediaType:videoConfig:} 方法订阅音视频流，调用时传入的参数即为此数据类型。  <br>
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCSubscribeConfig: NSObject
/** 
 * @brief 是否是屏幕流。  <br>
 *         用户通过设置此参数，订阅该远端用户发布的屏幕共享流或非屏幕共享流。 YES 为订阅屏幕共享流，NO 为订阅非屏幕共享流，默认值为 YES 。  <br>
 */
@property (nonatomic, assign) BOOL isScreen;
/** 
 * @brief 是否订阅视频。  <br>
 *         用户通过设置此参数，选择是否订阅远端流中的视频。 YES 为订阅视频，NO 为不订阅视频，默认值为 YES 。  <br>
 */
@property (nonatomic, assign) BOOL subscribeVideo;
/** 
 * @brief 是否订阅音频。  <br>
 *         用户通过设置此参数，选择是否订阅远端流中的音频。YES 为订阅音频，NO 为不订阅音频，默认值为 YES 。  <br>
 */
@property (nonatomic, assign) BOOL subscribeAudio;
/** 
 * @brief 订阅的视频流分辨率下标。  <br>
 *         用户可以通过调用 setVideoEncoderConfig:config:{@link #ByteRTCEngineKit#setVideoEncoderConfig:config:} 方法在一路流中发布多个不同分辨率的视频。因此订阅流时，需要指定订阅的具体分辨率。此参数即用于指定需订阅的分辨率的下标，默认值为 0 。  <br>
 */
@property (nonatomic, assign) NSInteger videoIndex;
@end
NS_ASSUME_NONNULL_END

/** 
 * @type keytype
 * @brief 视频帧类型
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoFrameType) {
    /** 
     * @brief 视频帧类型：内存数据
     */
    ByteRTCVideoFrameTypeRawMemory = 0,
    /** 
     * @brief 视频帧类型：CVPixelBuffer
     */
    ByteRTCVideoFrameTypePixelBuffer,
};
/** 
 * @type keytype
 * @brief 视频帧格式
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoPixelFormat) {
    /** 
     * @brief 未知格式
     */
    ByteRTCVideoPixelFormatUnknown = 0,
    /**
     * @brief I420
     */
    ByteRTCVideoPixelFormatI420 = 1,
    /**
     * @brief BGRA
     */
    ByteRTCVideoPixelFormatBGRA = 2,
    /**
     * @brief NV21
     */
    ByteRTCVideoPixelFormatNV21 = 3,
    /**
     * @brief RGBA
     */
    ByteRTCVideoPixelFormatRGBA = 4,
    /**
     * @brief IMC2
     */
    ByteRTCVideoPixelFormatIMC2 = 5,
    /**
     * @brief ARGB
     */
    ByteRTCVideoPixelFormatARGB = 7,
    /**
     * @brief NV12
     */
    ByteRTCVideoPixelFormatNV12 = 8,
    /** 
     * @brief Opengl Texture2D纹理
     */
    ByteRTCVideoPixelFormatGLTexture2D = 10,
    /** 
     * @brief Opengl OES纹理
     */
    ByteRTCVideoPixelFormatGLTextureOES = 11,
    /**
     * @brief CVPixelBuffer
     */
    ByteRTCVideoPixelFormatCVPixelBuffer = 12
};

/** 
 * @type keytype
 * @brief 视频帧编码格式
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoSinkPixelFormat) {
    /** 
     * @brief 原始视频帧格式
     */
    ByteRTCVideoSinkPixelFormatOriginal = 0,
    /** 
     * @brief YUV I420 格式
     */
    ByteRTCVideoSinkPixelFormatI420 = 1,
    /** 
     * @brief BGRA 格式
     */
    ByteRTCVideoSinkPixelFormatBGRA = 2,
    /** 
     * @brief YUV NV21 格式
     */
    ByteRTCVideoSinkPixelFormatNV12 = 8
};

/** 
 * @type keytype
 * @region 合流方式
 */
typedef NS_ENUM(NSUInteger, ByteRTCStreamMixingType) {
    /** 
     * @brief 通过服务端转推
     */
    StreamMixingTypeByServer = 0,
    /** 
     * @brief 端云一体转推
     */
    StreamMixingTypeByClient = 1,
};

/** 
 * @type keytype
 * @region 合流状态改变事件
 */
typedef NS_ENUM(NSUInteger, ByteRTCStreamMixingEvent) {
    /**
     * @hidden
     */
    StreamMixingBase = 0,
    /** 
     * @brief 合流开始
     */
    StreamMixingStart = 1,
    /** 
     * @brief 合流启动成功
     */
    StreamMixingStartSuccess = 2,
    /** 
     * @brief 合流启动失败
     */
    StreamMixingStartFailed = 3,
    /** 
     * @brief 合流结束
     */
    StreamMixingStop = 4,
    /** 
     * @brief 服务端合流/端云一体合流
     */
    StreamMixingChangeMixeType = 5,
    /** 
     * @brief 收到合流音频首帧
     */
    StreamMixingFirstAudioFrameByClientMixer = 6,
    /** 
     * @brief 收到合流视频首帧
     */
    StreamMixingFirstVideoFrameByClientMixer = 7,
    /** 
     * @brief 更新合流超时
     */
    StreamMixingUpdateTimeout = 8,
    /** 
     * @brief 开始合流超时
     */
    StreamMixingStartTimeout = 9,
};

/** 
 * @type keytype
 * @brief 待 SDK 编码的视频数据
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVideoFrame : NSObject
/** 
 * @brief 视频帧格式，参考 ByteRTCVideoPixelFormat {@link #ByteRTCVideoPixelFormat}
 */
@property (assign, nonatomic) int format;
/** 
 * @brief 当前帧的时间戳信息
 */
@property (assign, nonatomic) CMTime time;
/**
 * @hidden
 */
@property (assign, nonatomic) int stride DEPRECATED_MSG_ATTRIBUTE("use strideInPixels instead");
/** 
 * @brief 每一行像素占用的字节数
 */
@property (assign, nonatomic) int strideInPixels;
/** 
 * @brief 视频帧宽度
 */
@property (assign, nonatomic) int width;
/** 
 * @brief 视频帧高度
 */
@property (assign, nonatomic) int height;
/** 
 * @brief CVPixelBufferRef 类型的数据，当 format 为 kPixelFormatCVPixelBuffer 时有效
 */
@property (assign, nonatomic) CVPixelBufferRef _Nullable textureBuf;
/** 
 * @brief 视频帧内存块首地址
 */
@property (strong, nonatomic) NSData * _Nullable dataBuf;
/** 
 * @brief 视频帧左边裁剪的尺寸（像素）
 */
@property (assign, nonatomic) int cropLeft;
/** 
 * @brief 视频帧上部裁剪的尺寸（像素）
 */
@property (assign, nonatomic) int cropTop;
/** 
 * @brief 视频帧右边裁剪的尺寸（像素）
 */
@property (assign, nonatomic) int cropRight;
/** 
 * @brief 视频帧底部裁剪的尺寸（像素）
 */
@property (assign, nonatomic) int cropBottom;
/** 
 * @brief 视频帧旋转角度：0, 90, 180, 270
 */
@property (assign, nonatomic) ByteRTCVideoRotation rotation;
/** 
 * @hidden
 * @brief 视频镜像信息
 */
@property (assign, nonatomic) int flip;
/** 
 * @brief 视频帧附加的数据
 */
@property (strong, nonatomic) ByteRTCFrameExtendedData * _Nullable extendedData;
@end

/** 
 * @type keytype
 * @brief 视频帧信息
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCEncodedVideoFrame : NSObject
/** 
 * @brief 视频编码类型。参看 ByteRTCVideoCodecType{@link #ByteRTCVideoCodecType}
 */
@property (assign, nonatomic) ByteRTCVideoCodecType codecType;
/** 
 * @brief 视频编码帧类型。参看 ByteRTCVideoPictureType{@link #ByteRTCVideoPictureType}
 */
@property (assign, nonatomic) ByteRTCVideoPictureType pictureType;
/** 
 * @brief 视频采集时间戳，单位：微秒
 */
@property (assign, nonatomic) SInt64 timestampUs;
/** 
 * @brief 视频编码时间戳，单位：微秒
 */
@property (assign, nonatomic) SInt64 timestampDtsUs;
/** 
 * @brief 视频帧宽，单位：px
 */
@property (assign, nonatomic) int width;
/** 
 * @brief 视频帧高，单位：px
 */
@property (assign, nonatomic) int height;
/** 
 * @brief 视频帧旋转角度。参看 ByteRTCVideoRotation{@link #ByteRTCVideoRotation}
 */
@property (nonatomic, assign) ByteRTCVideoRotation rotation;
/** 
 * @brief 视频帧数据指针地址
 */
@property (strong, nonatomic) NSData * _Nonnull data;
@end

/** 
 * @type keytype
 * @brief 单个视频流在合流中的布局信息。  <br>
 *        开启转推直播功能后，在多路视频流合流时，你可以设置其中一路视频流在合流中的预设布局信息。
 * @notes  <br>
 *         + 视频流对应区域左上角的实际坐标是通过画面尺寸和归一化比例相乘，并四舍五入取整得到的。假如：Canvas.Width = 1920, Region.LocationX = 0.33，那么该画布左上角的横坐标为 634（1920*0.33=633.6，四舍五入取整）。  <br>
 *         + 视频流对应区域宽度和高度的像素值是通过画面尺寸和归一化比例相乘，四舍五入取整，并向上转换为偶数得到的。假如：Canvas.Width = 1920, Region.WidthProportion = 0.21，那么该画布横向宽度为 404px（1920*0.21=403.2，四舍五入取整后，再向上转换为偶数）。
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVideoCompositingRegion : NSObject
/** 
 * @brief 视频流发布用户的用户 ID 。
 */
@property (copy, nonatomic) NSString * _Nonnull uid;
/** 
 * @brief 视频流发布用户的房间 ID 。
 */
@property (copy, nonatomic) NSString * _Nonnull roomId;
/** 
 * @brief 视频流对应区域左上角的横坐标相对整体画面的归一化比例，取值的范围为 [0.0, 1.0)。
 */
@property (assign, nonatomic) CGFloat x;
/** 
 * @brief 视频流对应区域左上角的纵坐标相对整体画面的归一化比例，取值的范围为 [0.0, 1.0)。
 */
@property (assign, nonatomic) CGFloat y;
/** 
 * @brief 视频流对应区域宽度相对整体画面的归一化比例，取值的范围为 (0.0, 1.0]。
 */
@property (assign, nonatomic) CGFloat width;
/** 
 * @brief 视频流对应区域高度相对整体画面的归一化比例，取值的范围为 (0.0, 1.0]。
 */
@property (assign, nonatomic) CGFloat height;
/** 
 * @brief 用户视频布局在画布中的层级。0为底层，值越大越上层，范围为[0 - 100]。
 */
@property (assign, nonatomic) NSInteger zOrder;
/** 
 *  @brief 是否为本地用户
 */
@property (assign, nonatomic) BOOL localUser;
/** 
 *  @brief 是否为屏幕流，默认为NO
 */
@property (assign, nonatomic) BOOL screenStream;
/** 
 * @brief 透明度。范围为 [0.0, 1.0]。
 */
@property (assign, nonatomic) CGFloat alpha;
/** 
 * @brief 合流内容控制。默认值为 0 ，取值范围及含义如下:  <br>
 *        + 0: 输出的混流包含音视频  <br>
 *        + 1: 只包含音频  <br>
 *        + 2: 只包含视频
 */
@property (assign, nonatomic) NSInteger contentControl;
/** 
 * @brief 视频显示模式。详见 ByteRTCRenderMode{@link #ByteRTCRenderMode} 数据类型。  <br>
 */
@property (assign, nonatomic) ByteRTCRenderMode renderMode;
@end

/** 
 * @type keytype
 * @brief 视频流合流整体布局信息。  <br>
 *        开启转推直播功能后，你可以设置参与合流的每路视频流的预设布局信息和合流背景信息等。
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVideoCompositingLayout : NSObject
/** 
 * @brief 画布的背景颜色。格式为 RGB 定义下的 Hex 值，如 #FFB6C1 表示浅粉色。默认值 #000000，表示为黑色
 */
@property (copy, nonatomic) NSString *_Nonnull backgroundColor;
/** 
 * @brief 用户布局信息列表。每条流的具体布局详见 ByteRTCVideoCompositingRegion{@link #ByteRTCVideoCompositingRegion} 数据类型。
 */
@property (copy, nonatomic) NSArray<ByteRTCVideoCompositingRegion *> * _Nonnull regions;
/** 
 * @brief 透传的 App 数据。
 */
@property (copy, nonatomic) NSString *_Nonnull appData;
@end

/** 
 * @type keytype
 * @brief 视频转码配置参数。
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCTranscodingVideoConfig : NSObject
/** 
 * @brief 视频编码格式。H264 编码格式或自定义编码格式
 */
@property (copy, nonatomic) NSString * _Nonnull codec;
/** 
 * @brief 合流视频宽度。单位为 px，范围为 [2, 1920]，必须是偶数。默认值为 640。
 */
@property (assign, nonatomic) NSInteger width;
/** 
 * @brief 合流视频高度。单位为 px，范围为 [2, 1080]，必须是偶数。默认值为 480。
 */
@property (assign, nonatomic) NSInteger height;
/** 
 * @brief 合流视频帧率信息。
 */
@property (assign, nonatomic) NSInteger fps;
/** 
 * @brief 视频 I 帧间隔。
 */
@property (assign, nonatomic) NSInteger gop;
/** 
 * @brief 合流视频码率，单位为 kbps 。
 */
@property (assign, nonatomic) NSInteger kBitRate;
/** 
 * @brief 是否使用低延时特性。
 */
@property (assign, nonatomic) BOOL lowLatency;
@end

/** 
 * @type keytype
 * @brief AAC 编码类型。
 */
typedef NS_ENUM(NSInteger, ByteRTCAACProfile) {
    /** 
     * @brief LC（默认）
     */
    ByteRTCAACProfileLC   = 0,
    /**
     * @brief MAIN
     */
    ByteRTCAACProfileMain = 1,
    /**
     * @brief HEv1
     */
    ByteRTCAACProfileHEv1 = 2,
    /**
     * @brief HEv2
     */
    ByteRTCAACProfileHEv2 = 3,
};

/** 
 * @type keytype
 * @brief 音频转码配置参数。
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCTranscodingAudioConfig : NSObject
/** 
 * @brief 音频编码格式。使用 AAC 编码格式。
 */
@property (copy, nonatomic) NSString * _Nonnull codec;
/** 
 * @brief 音频采样率。单位为 kHz。可选取值：16, 32, 44.1, 48。
 */
@property (assign, nonatomic) NSInteger sampleRate;
/** 
 * @brief 声道数，可取 1 或 2。
 */
@property (assign, nonatomic) NSInteger channels;
/** 
 * @brief 音频码率。单位为 kbps。可选取值：16, 32, 64。
 */
@property (assign, nonatomic) NSInteger kBitRate;
/** 
 * @brief AAC 等级，详见 ByteRTCAACProfile{@link #ByteRTCAACProfile}
 */
@property (assign, nonatomic) ByteRTCAACProfile profile;
/**
 * @hidden
 */
+ (NSString* _Nonnull) toStringWithProfile:(ByteRTCAACProfile) aacProfile;
@end

/** 
 * @type keytype
 * @brief 转推直播配置参数。
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCLiveTranscoding : NSObject

/** 
 * @brief 合流类型，详见 ByteRTCStreamMixingType{@link #ByteRTCStreamMixingType} 数据类型。
 */
@property (assign, nonatomic) ByteRTCStreamMixingType expectedMixingType;
/** 
 * @brief 视频流合流整体布局信息。  <br>
 *        开启转推直播功能后，你可以设置参与合流的每路视频流的预设布局信息和合流背景信息等。详见 ByteRTCVideoCompositingLayout{@link #ByteRTCVideoCompositingLayout} 数据类型。
 */
@property (strong, nonatomic) ByteRTCVideoCompositingLayout * _Nonnull layout;
/** 
 * @brief 视频转码配置参数。详见 ByteRTCTranscodingVideoConfig{@link #ByteRTCTranscodingVideoConfig} 数据类型。
 */
@property (strong, nonatomic) ByteRTCTranscodingVideoConfig * _Nonnull video;
/** 
 * @brief 音频转码配置参数。详见 ByteRTCTranscodingAudioConfig{@link #ByteRTCTranscodingAudioConfig} 数据类型。
 */
@property (strong, nonatomic) ByteRTCTranscodingAudioConfig * _Nonnull audio;
/** 
 * @hidden
 * @brief 动态扩展自定义参数。
 */
@property (strong, nonatomic) NSMutableDictionary *  _Nullable advancedConfig;
/** 
 * @brief 业务透传鉴权信息
 */
@property (strong, nonatomic) NSMutableDictionary *  _Nullable authInfo;
/** 
 * @brief 推流 CDN 地址。
 */
@property (copy, nonatomic) NSString * _Nullable url;
/** 
 * @brief 推流 房间ID。
 */
@property (copy, nonatomic) NSString * _Nullable roomId;
/** 
 * @brief 推流 用户ID。
 */
@property (copy, nonatomic) NSString * _Nullable userId;
/** 
 * @brief 获取默认合流参数。
 */
+ (instancetype _Nonnull)defaultTranscoding;
@end

/** 
 *  @type keytype
 *  @brief 用户信息。  <br>
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCUserInfo : NSObject
/** 
 * @brief 用户 ID，长度在 128 字节以内的非空字符串。支持以下字符集范围:  <br>
 *            1. 26 个大写字母 A ~ Z  <br>
 *            2. 26 个小写字母 a ~ z  <br>
 *            3. 10 个数字 0 ~ 9  <br>
 *            4. 下划线 "_"，at 符 "@"，减 号 "-"
 */
@property (copy, nonatomic) NSString *_Nonnull userId;
/** 
 * @brief 用户需要透传的额外的信息，字符长度限制为 200 字节。会在 rtcEngine:onUserJoined:elapsed:{@link #ByteRTCEngineDelegate#rtcEngine:onUserJoined:elapsed:} 中回调给远端用户。
 */
@property (copy, nonatomic) NSString *_Nonnull extraInfo;
@end

/** 
 * @type keytype
 * @author shenpengliang
 * @brief 房间参数配置
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCRoomConfig : NSObject
/** 
 * @brief 房间模式，参看 ByteRTCRoomProfile{@link #ByteRTCRoomProfile}，默认为普通音视频通话模式，进房后不可更改。
 */
@property(nonatomic) ByteRTCRoomProfile profile;
/** 
 * @brief 是否自动发布音视频流。 <br>
 *        若调用 setUserVisibility:{@link #ByteRTCEngineKit#setUserVisibility:} 将自身可见性设为 false，无论是默认的自动发布流还是手动设置的自动发布流都不会进行发布，你需要将自身可见性设为 true 后方可发布。
 */
@property (assign, nonatomic) BOOL isAutoPublish;
/** 
 * @brief 是否自动订阅音频流，进房后不可更改。  <br>
 *        进房后，你可以调用 subscribeUserStream:streamType:mediaType:videoConfig:{@link #ByteRTCEngineKit#subscribeUserStream:streamType:mediaType:videoConfig:} 修改订阅设置。
 */
@property (assign, nonatomic) BOOL isAutoSubscribeAudio;
/** 
 * @brief 是否自动订阅主视频流。  <br>
 *        进房后，你可以调用 subscribeUserStream:streamType:mediaType:videoConfig:{@link #ByteRTCEngineKit#subscribeUserStream:streamType:mediaType:videoConfig:} 修改订阅设置。  <br>
 *        屏幕流始终自动订阅，不受该方法影响。
 */
@property (assign, nonatomic) BOOL isAutoSubscribeVideo;
@end

/** 
 * @type keytype
 * @author shenpengliang
 * @brief 多房间参数配置
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCMultiRoomConfig : NSObject
/** 
 * @brief 房间模式，参看 ByteRTCRoomProfile{@link #ByteRTCRoomProfile}，默认为普通音视频通话模式，进房后不可更改。
 */
@property(nonatomic) ByteRTCRoomProfile profile;
/** 
 * @brief 是否自动订阅音频流。  <br>
 *        进房后，你可以调用 subscribeUserStream:streamType:mediaType:videoConfig:{@link #ByteRTCRoom#subscribeUserStream:streamType:mediaType:videoConfig:} 修改订阅设置。
 */
@property (assign, nonatomic) BOOL isAutoSubscribeAudio;
/** 
 * @brief 是否自动订阅主视频流。  <br>
 *        进房后，你可以调用 subscribeUserStream:streamType:mediaType:videoConfig:{@link #ByteRTCRoom#subscribeUserStream:streamType:mediaType:videoConfig:} 修改订阅设置。  <br>
 *        屏幕流始终自动订阅，不受该方法影响。
 */
@property (assign, nonatomic) BOOL isAutoSubscribeVideo;
@end

/** 
 * @type keytype
 * @brief 视频订阅配置信息
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCSubscribeVideoConfig : NSObject
/** 
 * @brief 订阅的视频流分辨率下标。  <br>
 *        当远端用户通过调用 setVideoEncoderConfig:config:{@link #ByteRTCEngineKit#setVideoEncoderConfig:config:} 方法启动发布多路不同分辨率的视频流时，本地用户需通过此参数指定希望订阅的流。  <br>
 *        默认值为 0，即订阅第一路流。  <br>
 *        如果不想更改之前的设置，可以输入 -1。  <br>
 */
@property (assign, nonatomic) NSInteger videoIndex;
/** 
 * @brief 远端用户优先级，参看 ByteRTCRemoteUserPriority{@link #ByteRTCRemoteUserPriority}，默认值为 0。
 */
@property (assign, nonatomic) NSInteger priority;
@end
/** 
 * @type keytype
 * @brief 房间通话统计数据，统计周期为 2s 。  <br>
 *        用户进房成功后，SDK 会周期性地通过 rtcEngine:onRoomStats:{@link #ByteRTCEngineDelegate#rtcEngine:onRoomStats:}
 *        通知用户当前房间内的汇总统计信息。此数据结构即为回调给用户的参数类型。  <br>
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCRoomStats : NSObject
/** 
 * @brief 用户进房开始通话后的总时长，单位为 s ，累计值
 */
@property (assign, nonatomic) NSInteger duration;
/** 
 * @brief 本地用户的总发送字节数 (bytes)，累计值
 */
@property (assign, nonatomic) NSInteger txBytes;
/** 
 * @brief 本地用户的总接收字节数 (bytes)，累计值
 */
@property (assign, nonatomic) NSInteger rxBytes;
/** 
 * @brief 本地用户的音频发送码率 (kbps)，瞬时值
 */
@property (assign, nonatomic) NSInteger txAudioKBitrate;
/** 
 * @brief 本地用户的音频接收码率 (kbps)，瞬时值
 */
@property (assign, nonatomic) NSInteger rxAudioKBitrate;
/** 
 * @brief 本地用户的视频发送码率 (kbps)，瞬时值
 */
@property (assign, nonatomic) NSInteger txVideoKBitrate;
/** 
 * @brief 本地用户的视频接收码率 (kbps)，瞬时值
 */
@property (assign, nonatomic) NSInteger rxVideoKBitrate;
/** 
 * @brief 当前房间内的用户人数，包括本地用户自身
 */
@property (assign, nonatomic) NSInteger userCount;
/** 
 * @brief App 现在的下行丢包率
 */
@property (assign, nonatomic) float rxLostrate;
/** 
 * @brief App 现在的上行丢包率
 */
@property (assign, nonatomic) float txLostrate;
/** 
 * @brief 客户端到服务端的往返时延
 */
@property (assign, nonatomic) NSInteger rtt;
/** 
 * @brief 当前 App 的 CPU 使用率
 */
//@property (assign, nonatomic) double cpuAppUsage;
/** 
 * @brief 当前设备的总 CPU 使用率
 */
//@property (assign, nonatomic) double cpuTotalUsage;
@end

/** 
 * @type keytype
 * @brief App 使用的 cpu 和 memory 信息  <br>
 *        信息由 SDK 周期性（2s）地通过 rtcEngine:reportSysStats:{@link #ByteRTCEngineDelegate#rtcEngine:reportSysStats:} 回调事件通知给用户。
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCSysStats : NSObject
/** 
 * @brief 当前系统 cpu 核数
 */
@property (assign, nonatomic) unsigned int cpu_cores;
/** 
 * @brief 当前应用的 CPU 使用率，取值范围为 [0, 1]。
 */
@property (assign, nonatomic) double cpu_app_usage;
/** 
 * @brief 当前系统的 CPU 使用率，取值范围为 [0, 1]。
 */
@property (assign, nonatomic) double cpu_total_usage;
/** 
 * @brief 当前App的内存使用（单位 MB）
 */
@property (assign, nonatomic) double memory_usage;
/** 
 * @brief 全量内存（单位字节）
 */
@property (assign, nonatomic) unsigned long long full_memory;
/** 
 * @brief 系统已使用内存（单位字节）
 */
@property (assign, nonatomic) unsigned long long total_memory_usage;
/** 
 * @brief 空闲可分配内存（单位字节）
 */
@property (assign, nonatomic) unsigned long long free_memory;
/** 
 * @brief 当前应用的内存使用率（单位 %）
 */
@property (assign, nonatomic) double memory_ratio;
/** 
 * @brief 系统内存使用率（单位 %）
 */
@property (assign, nonatomic) double total_memory_ratio;
@end

/** 
 * @type keytype
 * @brief 本地视频流统计信息，统计周期为 2s 。  <br>
 *        本地用户发布视频流成功后，SDK 会周期性地通过 rtcEngine:onLocalStreamStats:{@link #ByteRTCEngineDelegate#rtcEngine:onLocalStreamStats:}
 *        通知本地用户发布的视频流在此次统计周期内的发送状况。此数据结构即为回调给本地用户的参数类型。  <br>
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCLocalVideoStats : NSObject
/** 
 * @brief 发送的码率。此次统计周期内的视频发送码率，单位为 kbps 。  <br>
 */
@property (assign, nonatomic) float sentKBitrate;
/** 
 * @brief 采集帧率。此次统计周期内的视频采集帧率，单位为 fps 。
 */
@property (assign, nonatomic) NSInteger inputFrameRate;
/** 
 * @brief 发送帧率。此次统计周期内的视频发送帧率，单位为 fps 。
 */
@property (assign, nonatomic) NSInteger sentFrameRate;
/** 
 * @brief 编码器输出帧率。当前编码器在此次统计周期内的输出帧率，单位为 fps 。
 */
@property (assign, nonatomic) NSInteger encoderOutputFrameRate;
/** 
 * @brief 本地渲染帧率。此次统计周期内的本地视频渲染帧率，单位为 fps 。
 */
@property (assign, nonatomic) NSInteger rendererOutputFrameRate;
/** 
 * @brief 目标发送码率。此次统计周期内的视频目标发送码率，单位为 kbps 。
 */
@property (assign, nonatomic) NSInteger sentTargetKBitrate;
/** 
 * @brief 目标发送帧率。当前编码器在此次统计周期内的目标发送帧率，单位为 fps 。
 */
@property (assign, nonatomic) NSInteger sentTargetFrameRate;
/** 
 * @brief 统计间隔，单位为 ms 。
 * @notes 此字段用于设置回调的统计周期，默认设置为 2s 。
 */
@property (assign, nonatomic) NSInteger statsInterval;
/** 
 * @brief 视频丢包率。统计周期内的视频上行丢包率，取值范围为 [0, 1] 。  <br>
 */
@property (assign, nonatomic) float videoLossRate;
/** 
 * @brief 往返时延。单位为 ms 。  <br>
 */
@property (assign, nonatomic) NSInteger rtt;
/** 
 * @brief 视频编码码率。此次统计周期内的视频编码码率，单位为 kbps 。
 */
@property(assign, nonatomic) NSInteger encodedBitrate;
/** 
 * @brief 视频编码宽度，单位为 px 。
 */
@property(assign, nonatomic) NSInteger encodedFrameWidth;
/** 
 * @brief 视频编码高度，单位为 px 。
 */
@property(assign, nonatomic) NSInteger encodedFrameHeight;
/** 
 * @brief 此次统计周期内发送的视频帧总数。
 */
@property(assign, nonatomic) NSInteger encodedFrameCount;
/** 
 * @brief 编码类型。参看 ByteRTCVideoCodecType{@link #ByteRTCVideoCodecType} 类型。  <br>
 */
@property(nonatomic) ByteRTCVideoCodecType codecType;
/** 
 * @brief 所属用户的媒体流是否为屏幕流。你可以知道当前统计数据来自主流还是屏幕流。
 */
@property (assign, nonatomic) BOOL isScreen;
/** 
 * @brief 视频上行网络抖动，单位为 ms。  <br>
 */
@property(assign, nonatomic) NSInteger jitter;
@end

/** 
 * @type keytype
 * @brief 远端音频流统计信息，统计周期为 2s 。  <br>
 *        本地用户订阅远端音频流成功后，SDK 会周期性地通过 rtcEngine:onRemoteStreamStats:{@link #ByteRTCEngineDelegate#rtcEngine:onRemoteStreamStats:}
 *        通知本地用户订阅的远端视频流在此次统计周期内的接收状况。此数据结构即为回调给本地用户的参数类型。  <br>
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCRemoteVideoStats : NSObject
/** 
 * @brief 远端视频宽度。  <br>
 */
@property (assign, nonatomic) NSInteger width;
/** 
 * @brief 远端视频高度。  <br>
 */
@property (assign, nonatomic) NSInteger height;
/** 
 * @brief 远端视频丢包率。统计周期内的视频下行丢包率，取值范围为 [0, 1] 。  <br>
 */
@property (assign, nonatomic) float videoLossRate;
/** 
 * @brief 接收码率。统计周期内的视频接收码率，单位为 kbps 。  <br>
 */
@property (assign, nonatomic) float receivedKBitrate;
/** 
 * @brief 远端视频接收帧率。  <br>
 */
@property (assign, nonatomic) NSInteger receivedFrameRate;
/** 
 * @brief 远端视频解码输出帧率。  <br>
 */
@property (assign, nonatomic) NSInteger decoderOutputFrameRate;
/** 
 * @brief 远端视频渲染输出帧率。  <br>
 */
@property (assign, nonatomic) NSInteger renderOutputFrameRate;
/** 
 * @brief 远端视频卡顿次数。  <br>
 */
@property (assign, nonatomic) NSInteger stallCount;
/** 
 * @brief 远端视频卡顿时长，单位为 ms 。  <br>
 */
@property (assign, nonatomic) NSInteger stallDuration;
/** 
 * @brief 用户体验级别的端到端延时。从发送端采集完成编码开始到接收端解码完成渲染开始的延时，单位为 ms 。  <br>
 */
@property (assign, nonatomic) NSInteger e2eDelay;
/** 
 * @brief 远端视频流是否是屏幕共享流。你可以知道当前数据来自主流还是屏幕流。
 */
@property (assign, nonatomic) BOOL isScreen;
/** 
 * @brief 统计间隔，此次统计周期的间隔，单位为 ms 。  <br>
 * @notes 此字段用于设置回调的统计周期，目前设置为 2s 。
 */
@property (assign, nonatomic) NSInteger statsInterval;
/** 
 * @brief 往返时延。单位为 ms 。  <br>
 */
@property (assign, nonatomic) NSInteger rtt;
/** 
 * @brief 远端用户在进房后发生视频卡顿的累计时长占视频总有效时长的百分比（%）。视频有效时长是指远端用户进房发布视频流后，除停止发送视频流和禁用视频模块之外的视频时长。
 */
@property(assign, nonatomic) NSInteger frozenRate;
/** 
 * @brief SDK 订阅的远端视频流的分辨率下标。  <br>
 */
@property (assign, nonatomic) NSInteger videoIndex;
/** 
 * @brief 视频下行网络抖动，单位为 ms。  <br>
 */
@property(assign, nonatomic) NSInteger jitter;
@end

/** 
 * @type keytype
 * @brief 本地音频流统计信息，统计周期为 2s 。  <br>
 *        本地用户发布音频流成功后，SDK 会周期性地通过 rtcEngine:onLocalStreamStats:{@link #ByteRTCEngineDelegate#rtcEngine:onLocalStreamStats:}
 *        通知本地用户发布的音频流在此次统计周期内的发送状况。此数据结构即为回调给本地用户的参数类型。  <br>
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCLocalAudioStats : NSObject
/** 
 * @brief 音频丢包率。此次统计周期内的音频上行丢包率，取值范围为 [0, 1] 。  <br>
 */
@property (assign, nonatomic) float audioLossRate;
/** 
 * @brief 发送的码率。此次统计周期内的音频发送码率，单位为 kbps 。  <br>
 */
@property (assign, nonatomic) float sentKBitrate;
/** 
 * @brief 采集采样率。此次统计周期内的音频采集采样率信息，单位为 Hz 。  <br>
 */
@property (assign, nonatomic) NSInteger recordSampleRate;
/** 
 * @brief 统计间隔。此次统计周期的间隔，单位为 ms 。  <br>
 * @notes 此字段用于设置回调的统计周期，默认设置为 2s 。
 */
@property (assign, nonatomic) NSInteger statsInterval;
/** 
 * @brief 往返时延。单位为 ms 。  <br>
 */
@property (assign, nonatomic) NSInteger rtt;
/** 
 * @brief 音频声道数。  <br>
 */
@property(assign, nonatomic) NSInteger numChannels;
/** 
 * @brief 音频发送采样率。此次统计周期内的音频发送采样率信息，单位为 Hz 。  <br>
 */
@property(assign, nonatomic) NSInteger sentSampleRate;
/** 
 * @brief 音频上行网络抖动，单位为 ms。  <br>
 */
@property(assign, nonatomic) NSInteger jitter;
@end

/** 
 * @type keytype
 * @brief 远端音频流统计信息，统计周期为 2s 。  <br>
 *        本地用户订阅远端音频流成功后，SDK 会周期性地通过 rtcEngine:onRemoteStreamStats:{@link #ByteRTCEngineDelegate#rtcEngine:onRemoteStreamStats:}
 *        通知本地用户订阅的音频流在此次统计周期内的接收状况。此数据结构即为回调给本地用户的参数类型。  <br>
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCRemoteAudioStats : NSObject
/** 
 * @brief 音频丢包率。统计周期内的音频下行丢包率，取值范围为 [0, 1] 。  <br>
 */
@property (assign, nonatomic) float audioLossRate;
/** 
 * @brief 接收码率。统计周期内的音频接收码率，单位为 kbps 。  <br>
 */
@property (assign, nonatomic) float receivedKBitrate;
/** 
 * @brief 音频卡顿次数。统计周期内的卡顿次数。  <br>
 */
@property (assign, nonatomic) NSInteger stallCount;
/** 
 * @brief 音频卡顿时长。统计周期内的卡顿时长，单位为 ms 。  <br>
 */
@property (assign, nonatomic) NSInteger stallDuration;
/** 
 * @brief 播放采样率。统计周期内的音频播放采样率信息，单位为 Hz 。  <br>
 */
@property (assign, nonatomic) NSInteger playoutSampleRate;
/** 
 * @brief 用户体验级别的端到端延时。从发送端采集完成编码开始到接收端解码完成渲染开始的延时，单位为 ms 。  <br>
 */
@property (assign, nonatomic) NSInteger e2eDelay;
/** 
 * @brief 统计间隔。此次统计周期的间隔，单位为 ms 。  <br>
 */
@property (assign, nonatomic) NSInteger statsInterval;
/** 
 * @brief 客户端到服务端数据传输的往返时延，单位为 ms。  <br>
 */
@property (assign, nonatomic) NSInteger rtt;
/** 
 * @brief 发送端——服务端——接收端全链路数据传输往返时延。单位为 ms 。  <br>
 */
@property (assign, nonatomic) NSInteger total_rtt;
/** 
 * @brief 远端用户发送的音频流质量。值含义参考 ByteRTCNetworkQuality{@link #ByteRTCNetworkQuality} 。  <br>
 */
@property(assign, nonatomic) NSInteger quality;
/** 
 * @brief 因引入 jitter buffer 机制导致的延时。单位为 ms 。  <br>
 */
@property(assign, nonatomic) NSInteger jitterBufferDelay;
/** 
 * @brief 音频声道数。  <br>
 */
@property(assign, nonatomic) NSInteger numChannels;
/** 
 * @brief 音频接收采样率。统计周期内接收到的远端音频采样率信息，单位为 Hz 。  <br>
 */
@property(assign, nonatomic) NSInteger receivedSampleRate;
/** 
 * @brief 远端用户在加入房间后发生音频卡顿的累计时长占音频总有效时长的百分比。音频有效时长是指远端用户进房发布音频流后，除停止发送音频流和禁用音频模块之外的音频时长。
 */
@property(assign, nonatomic) NSInteger frozenRate;
/** 
 * @brief 音频 PLC 样点总个数。  <br>
 */
@property(assign, nonatomic) NSInteger concealedSamples;
/** 
 * @brief 音频丢包补偿(PLC) 累计次数。  <br>
 */
@property(assign, nonatomic) NSInteger concealmentEvent;
/** 
 * @brief 音频解码采样率。统计周期内的音频解码采样率信息，单位为 Hz 。  <br>
 */
@property(assign, nonatomic) NSInteger decSampleRate;
/** 
 * @brief 解码时长。对此次统计周期内接收的远端音频流进行解码的总耗时，单位为 s 。  <br>
 */
@property(assign, nonatomic) NSInteger decDuration;
/** 
 * @brief 视频下行网络抖动，单位为 ms。  <br>
 */
@property(assign, nonatomic) NSInteger jitter;
@end

/** 
 * @type keytype
 * @brief 音频流来源的用户 ID, 及对应的音量。
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCAudioVolumeInfo : NSObject
/** 
 * @brief 音频流来源的用户 ID
 */
@property (copy, nonatomic) NSString * _Nonnull uid;
/** 
 * @brief 音量，取值范围为：[0,255]
 */
@property (assign, nonatomic) NSUInteger volume;
@end

/** 
 * @type keytype
 * @brief 性能回退相关数据
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCSourceWantedData : NSObject
/** 
 * @brief 推荐视频输入宽
 */
@property (nonatomic, assign) NSInteger width;
/** 
 * @brief 推荐视频输入高
 */
@property (nonatomic, assign) NSInteger height;
/** 
 * @brief 推荐视频输入帧率
 */
@property (nonatomic, assign) NSInteger frameRate;
@end

/** 
 * @type keytype
 * @brief 流切换信息。本地用户订阅的远端流触发回退策略时的流切换信息。
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCRemoteStreamSwitchEvent : NSObject
/** 
 * @brief 订阅的音视频流的发布者的用户 ID。
 */
@property (nonatomic, copy) NSString * _Nonnull uid;
/** 
 * @brief 流是否是屏幕流
 */
@property (nonatomic, assign) BOOL isScreen;
/** 
 * @brief 流切换前订阅视频流的分辨率对应的索引
 */
@property (nonatomic, assign) NSInteger beforeVideoIndex;
/** 
 * @brief 流切换后订阅视频流的分辨率对应的索引
 */
@property (nonatomic, assign) NSInteger afterVideoIndex;
/** 
 * @brief 流切换前是否有视频流
 */
@property (nonatomic, assign) BOOL beforeVideoEnabled;
/** 
 * @brief 流切换后是否有视频流
 */
@property (nonatomic, assign) BOOL afterVideoEnabled;
/** 
 * @brief 流切换原因，详见 ByteRTCFallbackOrRecoverReason{@link #ByteRTCFallbackOrRecoverReason}。
 */
@property (nonatomic, assign) ByteRTCFallbackOrRecoverReason reason;
@end

/** 
 * @hidden
 * @deprecated Please use ByteVideoSinkDelegate
 * @type callback
 * @brief 自定义的视频渲染
 */
DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCVideoSinkDelegate")
BYTERTC_APPLE_EXPORT @protocol ByteRTCVideoSinkProtocol <NSObject>
@required
/** 
 * @hidden
 * @type callback
 * @brief 初始化渲染器
 * @return  <br>
 *         + YES: 自定义的渲染器初始化完成  <br>
 *         + NO: 自定义的渲染器初始化失败，不继续往下运行  <br>
 * @notes 初始化渲染器的时候会回调这个方法
 */
- (BOOL)shouldInitialize DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCVideoSinkDelegate");;

/** 
 * @hidden
 * @type callback
 * @brief 启动渲染器
 * @notes 在开启渲染功能的时候会回调这个方法
 */
- (void)shouldStart DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCVideoSinkDelegate");

/** 
 * @hidden
 * @type callback
 * @brief 停止渲染器
 * @notes 在停止渲染功能的时候会回调这个方法
 */
- (void)shouldStop DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCVideoSinkDelegate");

/** 
 * @hidden
 * @type callback
 * @brief 释放渲染器
 * @notes 渲染器即将被废弃的时候会回调这个方法
 */
- (void)shouldDispose DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCVideoSinkDelegate");

/** 
 * @hidden
 * @type callback
 * @brief 获取PixelFormat格式
 * @return Buffer 类型，{@link #ByteRTCVideoSinkPixelFormat}
 * @notes 通过该方法的返回值，告知 SDK PixelFormat 的格式
 */
- (ByteRTCVideoPixelFormat)pixelFormat DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCVideoSinkDelegate");

/** 
 * @hidden
 * @type callback
 * @brief 输出视频的 PixelBuffer
 * @param pixelBuffer 视频的 PixelBuffer
 * @param rotation 视频旋转角度，{@link #ByteRTCVideoRotation}
 * @param extendedData 视频帧附加的数据,视频解码后获得的附加数据
 * @notes 通过该方法获取视频的 PixelBuffer
 */
- (void)renderPixelBuffer:(CVPixelBufferRef _Nonnull)pixelBuffer
                 rotation:(ByteRTCVideoRotation)rotation
             extendedData:(NSData * _Nullable)extendedData DEPRECATED_MSG_ATTRIBUTE("Please use ByteVideoSinkDelegate");

/**
 * @hidden
 */
- (int)getRenderElapse;
@end

/** 
 * @type keytype
 * @brief 自定义视频渲染器
 */
BYTERTC_APPLE_EXPORT @protocol ByteRTCVideoSinkDelegate <NSObject>
@required
/** 
 * @type api
 * @brief 输出视频的 PixelBuffer
 * @param pixelBuffer 视频的 PixelBuffer
 * @param rotation 视频旋转角度，参看 ByteRTCVideoRotation{@link #ByteRTCVideoRotation}
 * @param extendedData 视频解码后获得的附加数据
 */
- (void)renderPixelBuffer:(CVPixelBufferRef _Nonnull)pixelBuffer
                 rotation:(ByteRTCVideoRotation)rotation
             extendedData:(NSData * _Nullable)extendedData;
/**
 * @hidden
 */
- (int)getRenderElapse;
@end

/** 
 * @hidden
 * @type callback
 * @brief 外部渲染数据的消费接口
 */
@protocol ByteRTCVideoFrameConsumerObserver <NSObject>
/** 
 * @brief 输出 yuv420 数据
 * @param ocFrame 数据 Buffer
 * @param width 视频宽度
 * @param rotation 视频旋转角度
 * @param timestamp 时间戳
 */
- (void)consumeYUV420Buffer:(CVPixelBufferRef _Nullable)ocFrame width:(NSInteger)width rotation:(NSInteger)rotation timestamp:(long)timestamp;
/** 
 * @brief 输出 RGBA 数据
 * @param pixelBuffer 数据 Buffer
 * @param width 视频宽度
 * @param rotation 视频旋转角度
 * @param timestamp 时间戳
 */
- (void)consumeRGBABuffer:(CVPixelBufferRef _Nullable)ocFrame width:(NSInteger)width rotation:(NSInteger)rotation timestamp:(long)timestamp;
@end

/** 
 * @type callback
 * @region 视频管理
 */
BYTERTC_APPLE_EXPORT @protocol ByteRTCVideoFrameObserver <NSObject>
/** 
 * @brief 本地屏幕流的视频帧数据回调
 * @param frame 本地屏幕视频帧数据，参考: ByteRTCVideoFrame{@link #ByteRTCVideoFrame}
 */
- (void)onLocalScreenFrame:(ByteRTCVideoFrame * _Nonnull)frame;
/** 
 * @brief 本地视频流的视频帧数据回调
 * @param frame 本地视频流的视频帧数据，参考: ByteRTCVideoFrame{@link #ByteRTCVideoFrame}
 */
- (void)onLocalVideoFrame:(ByteRTCVideoFrame * _Nonnull)frame;

/** 
 * @brief 远端屏幕流的视频帧数据回调
 * @param frame 远端屏幕的视频帧数据，参考: ByteRTCVideoFrame{@link #ByteRTCVideoFrame}
 * @param uid 远端屏幕共享用户ID
 * @param room 对应流的房间 id
 */
- (void)onRemoteScreenFrame:(ByteRTCVideoFrame * _Nonnull)frame user:(NSString * _Nullable)uid room:(NSString * _Nullable)room;
/** 
 * @brief 远端视频流的视频帧数据回调
 * @param frame 远端视频流的视频帧数据，参考: ByteRTCVideoFrame{@link #ByteRTCVideoFrame}
 * @param uid 远端屏幕共享用户ID
 * @param room 对应流的房间 id
 */
- (void)onRemoteVideoFrame:(ByteRTCVideoFrame * _Nonnull)frame user:(NSString * _Nullable)uid room:(NSString * _Nullable)room;

/**
 * @hidden
 */
- (void)OnMergeFrame:(ByteRTCVideoFrame * _Nonnull)frame user:(NSString * _Nullable)uid room:(NSString * _Nullable)room;

@end


/** 
 * @type keytype
 * @brief 视频处理配置参数
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVideoPreprocessorConfig : NSObject
/** 
 * @brief 视频帧的像素格式，参看 ByteRTCVideoPixelFormat{@link #ByteRTCVideoPixelFormat}。
 */
@property (nonatomic, assign) ByteRTCVideoPixelFormat required_pixel_format;

@end


/** 
  * @type callback
  * @region 视频处理
  */
 BYTERTC_APPLE_EXPORT @protocol ByteRTCVideoProcessorDelegate <NSObject>

/** 
 * @type api
 * @region 视频处理
 * @author zhushufan.ref
 * @brief 获取 RTC SDK 采集得到的视频帧，根据 registerLocalVideoProcessor:withConfig:{@link #ByteRTCEngineKit#registerLocalVideoProcessor:withConfig:} 设置的视频前处理器，进行视频前处理，最终将处理后的视频帧给到 RTC SDK 用于编码传输。
 * @param src_frame RTC SDK 采集得到的视频帧，参考: ByteRTCVideoFrame{@link #ByteRTCVideoFrame}
 * @return 经过视频前处理后的视频帧，返回给 RTC SDK 供编码和传输，参考: ByteRTCVideoFrame{@link #ByteRTCVideoFrame}
 * @notes 如果需要取消视频前处理，可以将视频前处理器设置为 nullptr。
 */
- (ByteRTCVideoFrame* _Nullable) processVideoFrame:(ByteRTCVideoFrame* _Nonnull)src_frame;

@end

/** 
 * @type keytype
 * @brief 流信息
 */
@interface ByteRTCStreamEx : NSObject <ByteRTCStream>
/** 
 * @brief 用户ID
 */
@property (nonatomic, copy, nullable) NSString *userId;
/** 
 * @brief 流是否为共享屏幕流。
 */
@property (nonatomic, assign) BOOL isScreen;
/** 
 * @brief 该路流中是否包含视频
 */
@property (nonatomic, assign) BOOL hasVideo;
/** 
 * @brief 该路流中是否包含音频
 */
@property (nonatomic, assign) BOOL hasAudio;
/** 
 * @brief 视频流的分辨率信息，详见 ByteRTCVideoSolution{@link #ByteRTCVideoSolution} 类。
 *         用户可以通过调用 setVideoEncoderConfig:config:{@link #ByteRTCEngineKit#setVideoEncoderConfig:config:} 方法在一路流中发布多个不同的视频分辨率。此参数即为流中所有分辨率的相关信息。
 */
@property (nonatomic, copy, nullable) NSArray<ByteRTCVideoSolution *> *videoStreamDescriptions;
@end

/** 
 * @type keytype
 * @region 视频管理
 * @brief 屏幕采集设置参数
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCScreenCaptureParam : NSObject
/** 
 * @brief 屏幕采集宽度
 */
@property (nonatomic, assign) NSInteger width;
/** 
 * @brief 屏幕采集高度
 */
@property (nonatomic, assign) NSInteger height;
/** 
 * @brief 屏幕采集帧率，单位 fps
 */
@property (nonatomic, assign) NSInteger frameRate;
/** 
 * @brief 发送屏幕采集码率，单位 kbps
 */
@property (nonatomic, assign) NSInteger bitrate;
/** 
 * @brief 是否采集鼠标
 */
@property (nonatomic, assign) BOOL captureMouseCursor;
@end

/** 
 * @type keytype
 * @region 视频管理
 * @brief 屏幕采集设置参数
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCScreenParam : NSObject
/** 
 * @brief 编码帧率,单位为 fps
 */
@property (nonatomic, assign) NSInteger frameRate;
/** 
 * @brief 编码码率，小于 0 时 SDK 会根据高宽自适应码率, 单位 kbps
 */
@property (nonatomic, assign) NSInteger bitrate;
@end

/** 
 * @type keytype
 * @brief 用户信息
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCUser : NSObject
/** 
 * @brief 用户 ID
 */
@property (nonatomic, copy, nullable) NSString *userId;
/** 
 * @brief 元信息
 */
@property (nonatomic, copy, nullable) NSString *metaData;
@end

/** 
 * @type keytype
 * @brief 本地音/视频流统计信息以及网络状况，统计周期为 2s 。  <br>
 *        本地用户发布音/视频流成功后，SDK 会周期性地通过 rtcEngine:onLocalStreamStats:{@link #ByteRTCEngineDelegate#rtcEngine:onLocalStreamStats:}
 *        通知本地用户发布的音/视频流在此次统计周期内的发送状况。此数据结构即为回调给用户的参数类型。  <br>
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCLocalStreamStats : NSObject
/** 
 * @brief 本地设备发送音频流的统计信息，详见 ByteRTCLocalAudioStats{@link #ByteRTCLocalAudioStats}
 */
@property (strong, nonatomic) ByteRTCLocalAudioStats *_Nonnull audio_stats;
/** 
 * @brief 本地设备发送视频流的统计信息，详见 ByteRTCLocalVideoStats{@link #ByteRTCLocalVideoStats}
 */
@property (strong, nonatomic) ByteRTCLocalVideoStats *_Nonnull video_stats;
/** 
 * @brief 所属用户的媒体流上行网络质量，详见 ByteRTCNetworkQuality{@link #ByteRTCNetworkQuality}
 */
@property (assign, nonatomic) ByteRTCNetworkQuality tx_quality;
/** 
 * @brief 所属用户的媒体流下行网络质量，详见 ByteRTCNetworkQuality{@link #ByteRTCNetworkQuality}
 */
@property (assign, nonatomic) ByteRTCNetworkQuality rx_quality;
/** 
 * @brief 所属用户的媒体流是否为屏幕流。你可以知道当前统计数据来自主流还是屏幕流。
 */
@property (nonatomic, assign) BOOL is_screen;

@end

/** 
 * @type keytype
 * @brief 用户订阅的远端音/视频流统计信息以及网络状况，统计周期为 2s 。  <br>
 *        订阅远端用户发布音/视频流成功后，SDK 会周期性地通过 rtcEngine:onRemoteStreamStats:{@link #ByteRTCEngineDelegate#rtcEngine:onRemoteStreamStats:}
 *        通知本地用户订阅的远端音/视频流在此次统计周期内的接收状况。此数据结构即为回调给本地用户的参数类型。  <br>
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCRemoteStreamStats : NSObject
/** 
 * @brief 用户 ID 。音频来源的用户 ID 。  <br>
 */
@property (copy, nonatomic) NSString *_Nonnull uid;
/** 
 * @brief 远端音频流的统计信息，详见 ByteRTCRemoteAudioStats{@link #ByteRTCRemoteAudioStats}
 */
@property (strong, nonatomic) ByteRTCRemoteAudioStats *_Nonnull audio_stats;
/** 
 * @brief 远端视频流的统计信息，详见 ByteRTCRemoteVideoStats{@link #ByteRTCRemoteVideoStats}
 */
@property (strong, nonatomic) ByteRTCRemoteVideoStats *_Nonnull video_stats;
/** 
 * @brief 所属用户的媒体流上行网络质量，详见 ByteRTCNetworkQuality{@link #ByteRTCNetworkQuality}
 */
@property (assign, nonatomic) ByteRTCNetworkQuality tx_quality;
/** 
 * @brief 所属用户的媒体流下行网络质量，详见 ByteRTCNetworkQuality{@link #ByteRTCNetworkQuality}
 */
@property (assign, nonatomic) ByteRTCNetworkQuality rx_quality;
/** 
 * @brief 所属用户的媒体流是否为屏幕流。你可以知道当前统计数据来自主流还是屏幕流。
 */
@property (nonatomic, assign) BOOL is_screen;

@end

/** 
 * @type keytype
 * @brief 音视频流发送/接收状态。
 */
typedef NS_ENUM(NSInteger, ByteRTCMuteState) {
    /** 
     * @brief 启动发送/接收音视频流的状态
     */
    ByteRTCMuteStateOff = 0,
    /** 
     * @brief 停止发送/接收音视频流的状态
     */
    ByteRTCMuteStateOn = 1,
};

/** 
 * @type keytype
 * @brief 订阅媒体的类型
 */
typedef NS_ENUM(NSInteger, ByteRTCSubscribeMediaType) {
    /** 
     * @brief 既不订阅音频，也不订阅视频
     */
    ByteRTCSubscribeMediaTypeNone = 0,
    /** 
     * @brief 只订阅音频，不订阅视频
     */
    ByteRTCSubscribeMediaTypeAudioOnly = 1,
    /** 
     * @brief 只订阅视频，不订阅音频
     */
    ByteRTCSubscribeMediaTypeVideoOnly = 2,
    /** 
     * @brief 同时订阅音频和视频
     */
    ByteRTCSubscribeMediaTypeAudioAndVideo = 3,
};

/** 
 * @type keytype
 * @brief 暂停/恢复接收远端的媒体流类型。
 */
typedef NS_ENUM(NSInteger, ByteRTCPauseResumControlMediaType) {
    /** 
     * @brief 只控制音频，不影响视频
     */
    ByteRTCControlMediaTypeAudio = 0,
    /** 
     * @brief 只控制视频，不影响音频
     */
    ByteRtcControlMediaTypeVideo = 1,
    /** 
     * @brief 同时控制音频和视频
     */
    ByteRtcControlMediaTypeAudioAndVideo = 2,
};
/** 
 * @type keytype
 * @brief 流属性
 */
typedef NS_ENUM(NSInteger, ByteRTCStreamIndex) {
    /** 
     * @brief 主流。包括：<br>
     *        + 通过默认摄像头/麦克风采集到的视频/音频; <br>
     *        + 通过自定义设备采集到的视频/音频。
     */
    ByteRTCStreamIndexMain = 0,
    /** 
     * @brief 屏幕流。屏幕共享时共享的视频流，或来自声卡的本地播放音频流。
     */
    ByteRTCStreamIndexScreen = 1
};

/** 
 * @hidden
 * @deprecated
 * @type keytype
 * @brief 视频输入类型
 */
typedef NS_ENUM(NSInteger, ByteRTCMediaInputType) {
    /** 
     * @brief 自定义采集。  <br>
     *        设置完成后方可直接向 SDK 推送视频帧。
     */
    ByteRTCMediaInputTypeExternal = 0,
    /** 
     * @brief 内部 SDK 采集。  <br>
     *        此设置仅切换至内部采集，你需继续调用 startVideoCapture{@link #ByteRTCEngineKit#startVideoCapture} 开启内部采集。
     */
    ByteRTCMediaInputTypeInternal = 1
};


/** 
 * @type keytype
 * @brief 视频输入源类型
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoSourceType) {
    /** 
     * @brief 自定义采集视频源
     */
    ByteRTCVideoSourceTypeExternal = 0,
    /** 
     * @brief SDK 内部采集视频源
     */
    ByteRTCVideoSourceTypeInternal = 1,
    /** 
     * @brief 自定义编码视频源。  <br>
     *        SDK 不会自动生成多路流，你需要自行生成并推送多路流
     */
    ByteRTCVideoSourceTypeEncodedManualSimulcast = 2,
    /** 
     * @brief 自定义编码视频源。  <br>
     *        你仅需推送分辨率最大的一路编码后视频流，SDK 将自动转码生成多路小流
     */
    ByteRTCVideoSourceTypeEncodedAutoSimulcast = 3
};


/** 
 * @type keytype
 * @brief 视频解码方式
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoDecoderConfig) {
    /** 
     * @brief 开启 SDK 内部解码，只回调解码后的数据
     */
    ByteRTCVideoDecoderConfigRaw = 0,
    /** 
     * @brief 开启自定义解码，只回调解码前数据
     */
    ByteRTCVideoDecoderConfigEncode = 1,
    /** 
     * @brief 开启 SDK 内部解码，同时回调解码前和解码后的数据
     */
    ByteRTCVideoDecoderConfigBoth = 2
};


/** 
 * @type keytype
 * @region 房间管理
 * @brief 用户信息
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCRemoteStreamKey : NSObject
/** 
 * @brief 用户 ID
 */
@property (nonatomic, copy, nullable) NSString *userId;
/** 
 * @brief 房间 ID
 */
@property (nonatomic, copy, nullable) NSString *roomId;
/** 
 * @brief 流属性，包括主流、屏幕流。参看 ByteRTCStreamIndex:{@link #ByteRTCStreamIndex}
 */
@property (nonatomic, assign) ByteRTCStreamIndex streamIndex;
@end

/** 
 * @type keytype
 * @brief 虚拟背景类型。
 */
typedef NS_ENUM(NSInteger, ByteRTCVirtualBackgroundSourceType){
    /** 
     * @brief 使用纯色背景替换视频原有背景。
     */
    ByteRTCVirtualBackgroundSourceTypeColor = 0,
    /** 
     * @brief 使用自定义图片背景替换视频原有背景。
     */
    ByteRTCVirtualBackgroundSourceTypeImage = 1
};

/** 
 * @type keytype
 * @brief 虚拟背景对象。
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVirtualBackgroundSource: NSObject
/** 
 * @brief 虚拟背景类型，详见 ByteRTCVirtualBackgroundSourceType{@link #ByteRTCVirtualBackgroundSourceType} 。
 */
@property (nonatomic, assign) ByteRTCVirtualBackgroundSourceType sourceType;
/** 
 * @brief 纯色背景使用的颜色。<br>
 *        格式为 0xAARRGGBB 。
 */
@property int sourceColor;
/** 
 * @brief 自定义图片背景使用的图片的绝对路径。
 * @notes  <br>
 *       + 支持的格式为 jpg、jpeg、和 png。<br>
 *       + 分辨率超过 1080P 时，图片会被等比缩放。背景图片和视频分辨率不一致时，图片会被裁剪缩放。<br>
 */
@property (nonatomic) NSString* sourcePath;
@end

/** 
 * @type keytype
 * @brief 音频采样率，单位为 Hz。
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioSampleRate) {
    /** 
     * @brief 默认设置。
     */
    ByteRTCAudioSampleRateAuto = -1,
    /** 
     * @brief 8000 Hz
     */
    ByteRTCAudioSampleRate8000 = 8000,
    /** 
     * @brief 16000 Hz
     */
    ByteRTCAudioSampleRate16000 = 16000,
    /** 
     * @brief 32000 Hz
     */
    ByteRTCAudioSampleRate32000 = 32000,
    /** 
     * @brief 44100 Hz
     */
    ByteRTCAudioSampleRate44100 = 44100,
    /** 
     * @brief 48000 Hz
     */
    ByteRTCAudioSampleRate48000 = 48000
};

/** 
 * @type keytype
 * @brief 音频声道。
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioChannel) {
    /** 
     * @brief 默认设置。
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
 * @brief 音频播放设备类型。  <br>
 *        SDK 通过 rtcEngine:onAudioPlaybackDeviceChanged:{@link #ByteRTCEngineDelegate#rtcEngine:onAudioPlaybackDeviceChanged:} 回调当前音频设备播放类型。
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioPlaybackDevice) {
    /** 
     * @brief 扬声器
     */
    ByteRTCAudioPlaybackDeviceSpeakerphone = 1,
    /** 
     * @brief 听筒
     */
    ByteRTCAudioPlaybackDeviceEarpiece = 2,
    /** 
     * @brief 有线耳机
     */
    ByteRTCAudioPlaybackDeviceHeadset = 3,
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
 * @type callback
 * @region 视频数据回调
 * @brief 本地视频帧监测器
 */
BYTERTC_APPLE_EXPORT @protocol ByteRTCLocalEncodedVideoFrameObserver<NSObject>
 @optional
/** 
 * @type callback
 * @region 视频数据回调
 * @brief 调用 registerLocalEncodedVideoFrameObserver:{@link #ByteRTCEngineKit#registerLocalEncodedVideoFrameObserver:} 后，SDK 收到本地视频帧信息时，回调该事件
 * @param streamIndex 本地视频帧类型，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param frame 本地视频帧信息，参看 ByteRTCEncodedVideoFrame{@link #ByteRTCEncodedVideoFrame}
 */
- (void)onLocalEncodedVideoFrame:(ByteRTCStreamIndex) streamIndex Frame:(ByteRTCEncodedVideoFrame * _Null_unspecified)frame;
@end

#pragma mark - ByteRTCEngineExternalVideoEncoderEventHandler
/** 
 * @type callback
 * @brief 自定义编码帧回调类
 */
BYTERTC_APPLE_EXPORT @protocol ByteRTCExternalVideoEncoderEventHandler<NSObject>
@required
/** 
 * @type callback
 * @region 视频管理
 * @author wangzhanqiang
 * @brief 提示自定义编码帧可以开始推送的回调。  <br>
 *        收到该回调后，你即可调用 pushExternalEncodedVideoFrame:withVideoIndex:withEncodedVideoFrame:{@link #ByteRTCEngineKit#pushExternalEncodedVideoFrame:withVideoIndex:withEncodedVideoFrame:} 向 SDK 推送自定义编码视频帧
 * @param streamIndex 可以推送的编码流的属性，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 */
- (void)onStart:(ByteRTCStreamIndex)streamIndex;
@required
/** 
 * @type callback
 * @region 视频管理
 * @author wangzhanqiang
 * @brief 当收到该回调时，你需停止向 SDK 推送自定义编码视频帧
 * @param streamIndex 需停止推送的编码流的属性，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 */
- (void)onStop:(ByteRTCStreamIndex)streamIndex;
@required
/** 
 * @type callback
 * @region 视频管理
 * @author wangzhanqiang
 * @brief 当自定义编码流的帧率或码率发生变化时，触发该回调
 * @param streamIndex 发生变化的编码流的属性，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param videoIndex 对应编码流的下标
 * @param fps 变化后的帧率，单位：fps
 * @param bitRateKps 变化后的码率，单位：kbps
 */
- (void)onRateUpdate:(ByteRTCStreamIndex)streamIndex
      withVideoIndex:(NSInteger)videoIndex
             withFps:(NSInteger)fps
         withBitRate:(NSInteger)bitRateKps;
@required
/** 
 * @type callback
 * @region 视频管理
 * @author wangzhanqiang
 * @brief 调用 requestRemoteVideoKeyFrame:{@link #ByteRTCEngineKit#requestRemoteVideoKeyFrame:} 请求远端关键帧时，会触发该回调
 * @param streamIndex 远端编码流的属性，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param videoIndex 对应编码流的下标
 */
- (void)onRequestKeyFrame:(ByteRTCStreamIndex)streamIndex
           withVideoIndex:(NSInteger)videoIndex;
@end

#pragma mark - ByteRTCEngineRemoteEncodedVideoFrameObserver
/** 
 * @type callback
 * @region 视频管理
 * @brief 远端编码后视频数据监测器
 */
BYTERTC_APPLE_EXPORT @protocol ByteRTCRemoteEncodedVideoFrameObserver<NSObject>
@required
/** 
 * @type callback
 * @region 视频数据回调
 * @author wangzhanqiang
 * @brief 调用 registerRemoteEncodedVideoFrameObserver:{@link #ByteRTCEngineKit#registerRemoteEncodedVideoFrameObserver:} 后，SDK 监测到远端编码后视频数据时，触发该回调
 * @param streamKey 收到的远端流信息，参看 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
 * @param videoFrame 收到的远端视频帧信息，参看 ByteRTCEncodedVideoFrame{@link #ByteRTCEncodedVideoFrame}
 */
- (void)onRemoteEncodedVideoFrame:(ByteRTCRemoteStreamKey * _Nonnull)streamKey
                   withEncodedVideoFrame:(ByteRTCEncodedVideoFrame* _Nonnull)videoFrame;
@end

/** 
 * @type keytype
 * @brief 音频参数格式
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCAudioFormat : NSObject
/** 
 * @brief 音频采样率，详见 ByteRTCAudioSampleRate{@link #ByteRTCAudioSampleRate}
 */
@property (nonatomic, assign) ByteRTCAudioSampleRate sampleRate;
/** 
 * @brief 音频声道，详见 ByteRTCAudioChannel{@link #ByteRTCAudioChannel}
 */
@property (nonatomic, assign) ByteRTCAudioChannel channel;
@end

/** 
 * @type keytype
 * @region 音频管理
 * @brief PCM 音频帧
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCAudioFrame : NSObject
/** 
 * @brief PCM 数据
 */
@property (strong, nonatomic) NSData * _Nonnull buffer;
/** 
 * @brief 采样点个数
 */
@property (assign, nonatomic) int samples;
/** 
 * @brief 音频声道，参看 ByteRTCAudioChannel{@link #ByteRTCAudioChannel}。
 */
@property (assign, nonatomic) ByteRTCAudioChannel channel;
/** 
 * @brief 采样率，参看 ByteRTCAudioSampleRate{@link #ByteRTCAudioSampleRate}。
 */
@property (assign, nonatomic) ByteRTCAudioSampleRate sampleRate;
@end

/** 
 * @type keytype
 * @brief 视频帧基础信息
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVideoFrameInfo : NSObject
/** 
 * @brief 视频帧的宽度（像素）
 */
@property (nonatomic, assign) NSInteger width;
/** 
 * @brief 视频帧的高度（像素）
 */
@property (nonatomic, assign) NSInteger height;
/** 
 * @brief 视频帧顺时针旋转角度。参看 ByteRTCVideoRotation{@link #ByteRTCVideoRotation}。
 */
@property (nonatomic, assign) ByteRTCVideoRotation rotation;
@end

/** 
 * @type keytype
 * @brief 移动端摄像头
 */
typedef NS_ENUM(NSInteger, ByteRTCCameraID) {
    /** 
     * @brief 前置摄像头
     */
    ByteRTCCameraIDFront = 0,
    /** 
     * @brief 后置摄像头
     */
    ByteRTCCameraIDBack = 1,
};

/** 
 * @type keytype
 * @brief 语音识别服务鉴权方式，详情请咨询语音识别服务服务相关同学
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
 *        除网络原因导致的错误，语音识别服务内部会自行重试之外，其他错误都会停止服务，此时建议再次调用 startASR:handler:{@link #ByteRTCEngineKit#startASR:handler:} 重启语音识别功能。
 */
typedef NS_ENUM(NSInteger, ByteRTCASRErrorCode) {
    /** 
     * @brief 网络连接中断，服务不可用，内部会进行重连
     */
    ByteRTCASRErrorNetworkInterrupted = -1,
    /** 
     * @brief 用户已经调用过 startASR:handler:{@link #ByteRTCEngineKit#startASR:handler:}。  <br>
     *        开启语音识别服务后，你需要先调用 stopASR{@link #ByteRTCEngineKit#stopASR} 停止语音识别服务，才能二次调用 startASR:handler:{@link #ByteRTCEngineKit#startASR:handler:} 再次开启服务。
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
 * @brief 使用自动语音识别服务所需校验信息
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCASRConfig : NSObject
/** 
 *  @brief 应用 ID
 */
@property (copy, nonatomic) NSString *_Nonnull appId;
/** 
 *  @brief 用户 ID
 */
@property (copy, nonatomic) NSString *_Nonnull userId;
/** 
 *  @brief 访问令牌
 */
@property (copy, nonatomic) NSString *_Nonnull accessToken;
/** 
 *  @brief 私钥。Signature 鉴权模式下不能为空，token 鉴权模式下为空。参看[关于鉴权](https://bytedance.feishu.cn/docs/doccnMx9153dZEpfLX2I6BkFsMg#uh8x72)
 */
@property (copy, nonatomic) NSString *_Nonnull secretKey;
/** 
 *  @brief 场景信息，参看[业务集群](https://bytedance.feishu.cn/docs/doccnMx9153dZEpfLX2I6BkFsMg#aI4WCt)
 */
@property (copy, nonatomic) NSString *_Nonnull cluster;
/** 
 *  @brief 鉴权模式，参看 ByteRTCASRAuthorizationType{@link #ByteRTCASRAuthorizationType}
 */
@property (assign, nonatomic) ByteRTCASRAuthorizationType authorizationType;

@end


#pragma mark - LiveTranscodingDelegate
/** 
 * @type errorcode
 * @brief 转推直播功能错误码。
 */
typedef NS_ENUM(NSInteger, ByteRtcTranscoderErrorCode) {
    /** 
     * @brief 推流成功。
     */
    TranscoderErrorOK = 0,
    /**
     * @hidden
     */
    TranscoderErrorBase = 1090,
    /** 
     * @brief 推流参数无效，检查合流参数合法性。
     */
    TranscoderErrorInvalidParam = 1091,
    /** 
     * @brief 状态错误，需要在状态机正常状态下发起操作
     */
    TranscoderErrorInvalidState = 1092,
    /** 
     * @brief 无效操作
     */
    TranscoderErrorInvalidOperator = 1093,
    /** 
     * @brief 超时，请检查网络状态并重试
     */
    TranscoderErrorTimeOut = 1094,
    /**
     * @hidden
     */
    TranscoderErrorMax = 1099,
};

/** 
 * @type callback
 * @region 转推直播
 * @brief 转推直播观察者。  <br>
 */
@protocol LiveTranscodingDelegate <NSObject>
/** 
 * @type callback
 * @region 转推直播
 * @brief 是否具有推流能力。  <br>
 *       + false：不具备推流能力（默认值）  <br>
 *       + true：具备推流能力
 * @notes  <br>
 *         + 如果需要开启端云一体转推直播功能，你必须确保你的 App 包含 librtmp，具有推流能力。此时，设置该回调为 true。
 */
- (BOOL)isSupportClientPushStream;
/** 
 * @type keytype
 * @brief 转推直播状态回调
 * @param event 合流状态，详见 ByteRTCStreamMixingEvent {@link #ByteRTCStreamMixingEvent}。
 * @param msg 事件参数，包含事件的状态信息
 * @param Code 转推直播错误码，详见枚举类 ByteRtcTranscoderErrorCode {@link #ByteRtcTranscoderErrorCode}
 * @param mixType 合流类型，详见 ByteRTCStreamMixingType {@link #ByteRTCStreamMixingType}
 */
- (void)onStreamMixingEvent:(ByteRTCStreamMixingEvent)event
                  eventData:(NSString *_Nonnull)msg
                      error:(ByteRtcTranscoderErrorCode)Code
                    mixType:(ByteRTCStreamMixingType)mixType;

@optional
/** 
 * @type callback
 * @region 转推直播
 * @brief 端云一体合流音频 PCM 回调
 * @param audioFrame PCM 合流音频数据帧，详见 ByteRTCAudioFrame {@link #ByteRTCAudioFrame}
 * @notes  <br>
 *         + 收到该回调的周期为每 10 毫秒一次，并且每次的音频数据量为 10 毫秒数据量。
 */
- (void)onMixingAudioFrame:(ByteRTCAudioFrame *_Nonnull)audioFrame;
/** 
 * @type callback
 * @region 转推直播
 * @brief 端云一体合流视频 YUV 回调
 * @param videoFrame YUV 合流视频数据帧，详见 ByteRTCVideoFrame {@link #ByteRTCVideoFrame}
 * @notes  <br>
 *         + 收到该回调的周期取决于视频的帧率。
 */
- (void)onMixingVideoFrame:(ByteRTCVideoFrame *_Nonnull)videoFrame;
/** 
 * @type callback
 * @region 转推直播
 * @brief 端云一体合流视频 SEI 数据
 * @param dataFrame SEI 数据，详见 ByteRTCFrameExtendedData {@link #ByteRTCFrameExtendedData}
 */
- (void)onMixingDataFrame:(ByteRTCFrameExtendedData *_Nonnull)dataFrame;

@end

#pragma mark - FileRecording
/** 
 * @type keytype
 * @brief 本地录制的状态
 */
typedef NS_ENUM(NSInteger, ByteRTCRecordingState) {
    /** 
     * @brief 录制异常
     */
    RecordingStateError = 0,
    /** 
     * @brief 录制进行中
     */
    RecordingStateProcessing = 1,
    /** 
     * @brief 录制文件保存成功，调用 stopFileRecording:{@link #ByteRTCEngineKit#stopFileRecording:} 结束录制之后才会收到该状态码。
     */
    RecordingStateSuccess = 2,
};

/** 
 * @type keytype
 * @brief 本地录制错误码
 */
typedef NS_ENUM(NSInteger, ByteRTCRecordingErrorCode) {
    /** 
     * @brief 录制正常
     */
    RecordingErrorCodeOk = 0,
    /** 
     * @brief 没有文件写权限
     */
    RecordingErrorCodeNoPermission = -1,
    /** 
     * @brief 当前版本 SDK 不支持本地录制功能，请联系技术支持人员
     */
    RecordingErrorCodeNotSupport = -2,
    /** 
     * @brief 其他异常
     */
    RecordingErrorCodeOther = -3,
};

/** 
 * @type keytype
 * @brief 本地录制文件的存储格式
 */
typedef NS_ENUM(NSInteger, ByteRTCRecordingFileType) {
    /** 
     * @brief aac 格式文件
     */
    RecordingFileTypeAAC = 0,
    /** 
     * @brief mp4 格式文件
     */
    RecordingFileTypeMP4 = 1,
};

/** 
 * @type keytype
 * @brief 本地录制的媒体类型
 */
typedef NS_ENUM(NSInteger, ByteRTCRecordingType) {
    /** 
     * @brief 只录制音频
     */
    RecordAudioOnly = 0,
    /** 
     * @brief 只录制视频
     */
    RecordVideoOnly = 1,
    /** 
     * @brief 同时录制音频和视频
     */
    RecordVideoAndAudio = 2,
};

/** 
 * @type keytype
 * @brief 本地录制进度
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCRecordingProgress : NSObject
/** 
 * @brief 当前文件的累计录制时长，单位：毫秒
 */
@property (assign, nonatomic) unsigned long long duration;
/** 
 * @brief 当前录制文件的大小，单位：byte
 */
@property (assign, nonatomic) unsigned long long fileSize;
@end

/** 
 * @type keytype
 * @brief 本地录制的详细信息
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCRecordingInfo : NSObject
/** 
 * @brief 录制文件的绝对路径，包含文件名和文件后缀
 */
@property (strong, nonatomic) NSString* _Nullable filePath;
/** 
 * @brief 录制文件的视频编码类型，参看 ByteRTCVideoCodecType{@link #ByteRTCVideoCodecType}
 */
@property (assign, nonatomic) ByteRTCVideoCodecType codecType;
/** 
 * @brief 录制视频的宽，单位：像素。纯音频录制请忽略该字段
 */
@property (nonatomic, assign) NSInteger width;
/** 
 * @brief 录制视频的高，单位：像素。纯音频录制请忽略该字段
 */
@property (nonatomic, assign) NSInteger height;
@end

/** 
 * @type keytype
 * @brief 本地录制参数配置
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCRecordingConfig : NSObject
/** 
 * @brief 录制文件保存的绝对路径。你需要指定一个有读写权限的合法路径。
 */
@property (strong, nonatomic) NSString* _Nullable dirPath;
/** 
 * @brief 录制存储文件格式，参看 ByteRTCRecordingFileType{@link #ByteRTCRecordingFileType}
 */
@property (assign, nonatomic) ByteRTCRecordingFileType recordingFileType;
/** 
 * @brief 录制媒体类型，参看 ByteRTCRecordingType{@link #ByteRTCRecordingType}
 */
@property (assign, nonatomic) ByteRTCRecordingType recordingType;
@end

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
     * @brief 仅发送到远端
     */
    ByteRTCAudioMixingTypePublish = 1,
    /** 
     * @brief 在本地播放并发送到远端
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
 * @brief 音频混音文件播放错误码。
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioMixingError) {
    /** 
     * @brief 混音错误码，正常
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
     * @brief 音量参数不合法，仅支持设置的音量值为[0 400]
     */
    ByteRTCAudioMixingErrorInValidVolume,
    /** 
     * @brief 混音 ID 类型不匹配，当前操作接口不支持该 ID 代表的音频流类型
     */
    ByteRTCAudioMixingErrorIdTypeNotMatch,
    /** 
     * @brief 播放的文件与预加载的文件不一致，请先使用 unloadAudioMixing:{@link #ByteRTCAudioMixingManager#unloadAudioMixing:} 卸载文件。
     */
    ByteRTCAudioMixingErrorLoadConflict,
    /**  
     * @brief 设置混音文件的音调不合法
     */
    ByteRTCAudioMixingErrorInValidPitch,
    /** 
     * @brief 设置混音文件的音轨不合法
     */
    ByteRTCAudioMixingErrorInValidAudioTrack,
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
 * @brief 开启/关闭耳返功能
 */
typedef NS_ENUM(NSInteger, ByteRTCEarMonitorMode) {
    /** 
     * @brief 不开启耳返功能
     */
    ByteRTCEarMonitorModeOff = 0,
    /** 
     * @brief 开启耳返功能
     */
    ByteRTCEarMonitorModeOn = 1,
};
/** 
 * @type keytype
 * @brief 混音配置
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCAudioMixingConfig : NSObject
/** 
 * @brief 混音播放类型，详见 ByteRTCAudioMixingType{@link #ByteRTCAudioMixingType}
 */
@property (assign, nonatomic) ByteRTCAudioMixingType type;
/** 
 * @brief 混音播放次数
 * @notes  <br>
 *       + play_count <= 0: 无限循环  <br>
 *       + play_count == 1: 播放一次（默认）  <br>
 *       + play_count > 1: 播放 play_count 次
 */
@property (assign, nonatomic) NSInteger playCount;
/** 
 * @brief 混音时音频文件播放进度条位置，参数为整数，单位为毫秒
 */
@property (assign, nonatomic) NSInteger position;
/** 
 * @brief 设置音频文件播放进度回调的时间间隔，单位毫秒，并按照设置的值触发 rtcEngine:onAudioMixingPlayingProgress:progress:{@link #ByteRTCEngineDelegate#rtcEngine:onAudioMixingPlayingProgress:progress:} 回调，默认不回调。  <br>
 *        + 该值应为大于 0 的 10 的倍数，当传入的值不能被 10 整除时，则默认向上取整 10，如设为 52ms 时会默认调整为 60ms。  <br>
 *        + 传入的值小于等于 0 时，不会触发进度回调。  <br>
 */
@property (assign, nonatomic) NSInteger callbackOnProgressInterval;

@end

/** 
 * @type keytype
 * @brief 音频属性信息提示的相关配置  <br>
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCAudioPropertiesConfig : NSObject
/** 
 * @brief 信息提示间隔，单位：ms
 * @notes  <br>
 *       + <= 0: 关闭信息提示  <br>
 *       + >0 && <=100: 开启信息提示，不合法的 interval 值，SDK 自动设置为 100ms  <br>
 *       + > 100: 开启信息提示，并将信息提示间隔设置为此值  <br>
 */
@property (assign, nonatomic) NSInteger interval;
/** 
 * @brief 是否开启音频频谱检测
 */
@property (assign, nonatomic) BOOL enable_spectrum;
/** 
 * @brief 是否开启人声检测 (VAD)
 */
@property (assign, nonatomic) BOOL enable_vad;
@end
/** 
 * @type keytype
 * @brief 音频属性信息  <br>
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCAudioPropertiesInfo : NSObject
/** 
 * @brief 音量，取值范围为：[0,255]
 */
@property (assign, nonatomic) NSInteger volume;
/** 
 * @brief 人声检测（VAD）结果
 * @notes <br>
 *        + 1: 检测到人声。<br>
 *        + 0: 未检测到人声。<br>
 *        + -1: 未开启 VAD。<br>
 */
@property (assign, nonatomic) NSInteger vad;
/** 
 * @brief 频谱数组。默认长度为 257。
 */
@property (copy, nonatomic) NSArray<NSNumber*> * _Nonnull spectrum;

@end

/** 
 * @type keytype
 * @brief 本地音频属性信息
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCLocalAudioPropertiesInfo : NSObject

/** 
 * @brief 流属性，包括主流、屏幕流。参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 */
@property (assign, nonatomic) ByteRTCStreamIndex streamIndex;
/** 
 * @type keytype
 * @brief 音频属性信息，详见 ByteRTCAudioPropertiesInfo{@link #ByteRTCAudioPropertiesInfo}
 */
@property (strong, nonatomic) ByteRTCAudioPropertiesInfo *_Nonnull audioPropertiesInfo;

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
@property (strong, nonatomic) ByteRTCRemoteStreamKey *_Nonnull streamKey;
/** 
 * @type keytype
 * @brief 音频属性信息，详见 ByteRTCAudioPropertiesInfo{@link #ByteRTCAudioPropertiesInfo}
 */
@property (strong, nonatomic) ByteRTCAudioPropertiesInfo *_Nonnull audioPropertiesInfo;

@end

/** 
 * @type keytype
 * @brief 使用范围语音功能时，语音的接收范围
 */
BYTERTC_APPLE_EXPORT @interface ReceiveRange : NSObject
/** 
 * @brief 收听声音无衰减的最小范围值。<br>
 *        当收听者和声源距离小于 min 的时候，收听到的声音完全无衰减。
 */
@property (nonatomic, assign) int min;
/** 
 *  @brief 能够收听到声音的最大范围。<br>
 *        当收听者和声源距离大于 max 的时候，无法收听到声音。<br>
 *        当收听者和声源距离处于 [min, max) 之间时，收听到的音量根据距离有衰减。
 */
@property (nonatomic, assign) int max;

@end

/** 
 * @type keytype
 * @brief 用户的位置信息
 */
BYTERTC_APPLE_EXPORT @interface Position : NSObject
/** 
 * @brief x 坐标
 */
@property (nonatomic, assign) int x;
/** 
 * @brief y 坐标
 */
@property (nonatomic, assign) int y;
/** 
 * @brief z 坐标
 */
@property (nonatomic, assign) int z;

@end


/** 
 * @type keytype
 * @brief 方向朝向信息
 */
BYTERTC_APPLE_EXPORT @interface Orientation : NSObject
/** 
 * @brief x 方向向量
 */
@property (nonatomic, assign) float x;
/** 
 * @brief y 方向向量
 */
@property (nonatomic, assign) float y;
/** 
 * @brief z 方向向量
 */
@property (nonatomic, assign) float z;

@end


/** 
 * @type keytype
 * @brief 用户的三维方向朝向信息，三个向量需要两两垂直
 */
BYTERTC_APPLE_EXPORT @interface HumanOrientation : NSObject
/** 
 * @brief 正前方朝向向量
 */
@property (nonatomic, strong) Orientation* _Nonnull forward;
/** 
 * @brief 正右方朝向向量
 */
@property (nonatomic, strong) Orientation* _Nonnull right;
/** 
 * @brief 正上方朝向向量
 */
@property (nonatomic, strong) Orientation* _Nonnull up;

@end

/** 
 * @type keytype
 * @brief 媒体流信息同步的流类型
 */
typedef NS_ENUM(NSInteger, ByteRTCSyncInfoStreamType) {
    /** 
     * @brief 音频流
     */
    ByteRTCSyncInfoStreamTypeAudio = 0
};

/** 
 * @type keytype
 * @brief 相机补光灯状态
 */
typedef NS_ENUM(NSInteger, ByteRTCTorchState) {
    /** 
     * @brief 相机补光灯关闭
     */
    ByteRTCTorchStateOff = 0,
    /** 
     * @brief 相机补光灯打开
     */
    ByteRTCTorchStateOn = 1,
};

/** 
 * @type keytype
 * @brief 媒体流信息同步的相关配置
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCStreamSycnInfoConfig : NSObject

/** 
 * @brief 流属性，主流或屏幕流。见 ByteRTCStreamIndex{@link #ByteRTCStreamIndex} 。
 */
@property (assign, nonatomic) ByteRTCStreamIndex streamIndex;
/** 
 * @brief 消息发送的重复次数，取值范围是 [0,25]，建议设置为 [3,5]。
 */
@property (assign, nonatomic) int repeatCount;
/** 
 * @brief 媒体流信息同步的流类型，见 ByteRTCSyncInfoStreamType{@link #ByteRTCSyncInfoStreamType} 。
 */
@property (assign, nonatomic) ByteRTCSyncInfoStreamType streamType;

@end

/** 
 * @type keytype
 * @brief 媒体流跨房间转发状态
 */
typedef NS_ENUM(NSInteger, ByteRTCForwardStreamState) {
    /** 
     * @brief 空闲状态
     *        + 成功调用 stopForwardStreamToRooms{@link #ByteRTCRoom#stopForwardStreamToRooms} 后，所有目标房间为空闲状态。
     *        + 成功调用 updateForwardStreamToRooms:{@link #ByteRTCRoom#updateForwardStreamToRooms:} 减少目标房间后，本次减少的目标房间为空闲状态。
     */
    ByteRTCForwardStreamStateIdle = 0,
    /** 
     * @brief 开始转发
     *        + 调用 startForwardStreamToRooms:{@link #ByteRTCRoom#startForwardStreamToRooms:} 成功向所有房间开始转发媒体流后，返回此状态。
     *        + 调用 updateForwardStreamToRooms:{@link #ByteRTCRoom#updateForwardStreamToRooms:} 后，成功向新增目标房间开始转发媒体流后，返回此状态。
     */
    ByteRTCForwardStreamStateSuccess = 1,
    /** 
     * @brief 转发失败，失败详情参考 ByteRTCForwardStreamError{@link #ByteRTCForwardStreamError}
     *        调用 startForwardStreamToRooms:{@link #ByteRTCRoom#startForwardStreamToRooms:} 或 updateForwardStreamToRooms:{@link #ByteRTCRoom#updateForwardStreamToRooms:} 后，如遇转发失败，返回此状态。
     */
    ByteRTCForwardStreamStateFailure = 2,
};

/** 
 * @type keytype
 * @brief 媒体流跨房间转发过程中抛出的错误码
 */
typedef NS_ENUM(NSInteger, ByteRTCForwardStreamError) {
    /** 
     * @brief 正常
     */
    ByteRTCForwardStreamErrorOK = 0,
    /** 
     * @brief 参数异常
     */
    ByteRTCForwardStreamErrorInvalidArgument = 1201,
    /** 
     * @brief Token 错误
     */
    ByteRTCForwardStreamErrorInvalidToken = 1202,
    /** 
     * @brief 服务端异常
     */
    ByteRTCForwardStreamErrorResponse = 1203,
    /** 
     * @brief 目标房间有相同 user id 的用户加入，转发中断
     */
    ByteRTCForwardStreamErrorRemoteKicked = 1204,
    /** 
     * @brief 服务端不支持转发功能
     */
    ByteRTCForwardStreamErrorNotSupport = 1205,
};

/** 
 * @type keytype
 * @brief 媒体流跨房间转发事件
 */
typedef NS_ENUM(NSInteger, ByteRTCForwardStreamEvent) {
    /** 
     * @brief 本端与服务器网络连接断开，暂停转发。
     */
    ByteRTCForwardStreamEventDisconnected = 0,
    /** 
     * @brief 本端与服务器网络连接恢复，转发服务连接成功。
     */
    ByteRTCForwardStreamEventConnected = 1,
    /** 
     * @brief 转发中断。转发过程中，如果相同 user_id 的用户进入目标房间，转发中断。
     */
    ByteRTCForwardStreamEventInterrupt = 2,
    /** 
     * @brief 目标房间已更新，由 updateForwardStreamToRooms:{@link #ByteRTCRoom#updateForwardStreamToRooms:} 触发。
     */
    ByteRTCForwardStreamEventDstRoomUpdated = 3,
    /** 
     * @brief API 调用时序错误。例如，在调用 startForwardStreamToRooms:{@link #ByteRTCRoom#startForwardStreamToRooms:} 之前调用 updateForwardStreamToRooms:{@link #ByteRTCRoom#updateForwardStreamToRooms:} 。
     */
    ByteRTCForwardStreamEventUnExpectAPICall = 4,
};


/** 
 * @type keytype
 * @brief 媒体流跨房间转发的目标房间的相关信息
 */
BYTERTC_APPLE_EXPORT @interface ForwardStreamConfiguration: NSObject
    /** 
     * @brief 跨间转发媒体流过程中目标房间 ID<br>
     */
    @property (strong, nonatomic) NSString* _Nullable roomId;
    /** 
     * @brief 用于向该房间转发媒体流的 Token。<br>
     *        如果 Token 无效，转发失败。
     */
    @property (strong, nonatomic) NSString* _Nullable token;
@end

/** 
 * @type keytype
 * @brief 跨房间转发媒体流过程中的不同目标房间的状态和错误信息
 */
BYTERTC_APPLE_EXPORT @interface ForwardStreamStateInfo: NSObject
    /** 
     * @brief 跨房间转发媒体流过程中目标房间 ID<br>
     *        空字符串代表所有目标房间
     */
    @property (strong, nonatomic) NSString* _Nullable roomId;
    /** 
     * @brief 跨房间转发媒体流过程中该目标房间的状态，参看 ByteRTCForwardStreamState{@link #ByteRTCForwardStreamState}
     */
    @property (assign, nonatomic) ByteRTCForwardStreamState state;
    /** 
     * @brief 跨房间转发媒体流过程中该目标房间抛出的错误码，参看 ByteRTCForwardStreamError{@link #ByteRTCForwardStreamError}
     */
    @property (assign, nonatomic) ByteRTCForwardStreamError error;
@end

/** 
 * @type keytype
 * @brief 跨房间转发媒体流过程中的不同目标房间发生的事件
 */
BYTERTC_APPLE_EXPORT @interface ForwardStreamEventInfo: NSObject
    /** 
     * @brief 跨房间转发媒体流过程中的发生该事件的目标房间 ID<br>
     *        空字符串代表所有目标房间
     */
    @property (strong, nonatomic) NSString* _Nullable roomId;
    /** 
     * @brief 跨房间转发媒体流过程中该目标房间发生的事件，参看 ByteRTCForwardStreamEvent{@link #ByteRTCForwardStreamEvent}
     */
    @property (assign, nonatomic) ByteRTCForwardStreamEvent event;
@end
