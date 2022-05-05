/*
 * Copyright (c) 2022 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief Objective-C VolcEngineRTC Common Defines
*/

#import <CoreMedia/CMTime.h>
#import <UIKit/UIKit.h>

#define BYTERTC_APPLE_EXPORT __attribute__((visibility("default")))

/** 
 *  @type keytype
 *  @brief 用户离开房间的原因。  <br>
 */
typedef NS_ENUM(NSUInteger, ByteRTCUserOfflineReason) {
    /** 
     * @brief 远端用户调用 `leaveRoom` 方法主动退出房间。  <br>
     */
    ByteRTCUserOfflineReasonQuit = 0,
    /** 
     * @brief 远端用户因网络等原因掉线。  <br>
     */
    ByteRTCUserOfflineReasonDropped = 1,
    /** 
     * @brief 远端用户切换至隐身状态。  <br>
     */
     ByteRTCUserOfflineReasonSwitchToInvisible = 2,
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
     *        单声道，采样率为 48kHz。 <br>
     *        当你对音视频通话的音质和画质要求较高时，应使用此设置。<br>
     *        此设置下，当用户使用蓝牙耳机收听时，蓝牙耳机使用媒体模式。
     */
    ByteRTCRoomProfileLiveBroadcasting = 1,
    /** 
    * @brief 游戏语音模式。<br>
    *        单声道，采样率为 16kHz。 <br>
    *        低端机在此模式下运行时，进行了额外的性能优化：<br>
    *            + 部分低端机型配置编码帧长 40/60 <br>
    *            + 部分低端机型关闭软件 3A 音频处理 <br>
    *        增强对 iOS 其他屏幕录制进行的兼容性，避免音频录制被 RTC 打断。
    */
    ByteRTCRoomProfileGame = 2,
    /** 
     * @brief 云游戏模式。<br>
     *        单声道，采样率为 48kHz。 <br>
     *        如果你需要低延迟、高码率的设置时，你可以使用此设置。<br>
     *        此设置下，弱网抗性较差。
     */
    ByteRTCRoomProfileCloudGame = 3,
    /** 
     * @brief 低时延模式。SDK 会使用低延时设置。  <br>
     *        当你的场景非游戏或云游戏场景，又需要极低延时的体验时，可以使用该模式。 <br>
     *        该模式下，音视频通话延时会明显降低，但同时弱网抗性、通话音质等均会受到一定影响。  <br>
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
 *        `rtcEngine:onNetworkDetectionStopped:` 回调的参数类型
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
 *        `startNetworkDetection:uplinkBandwidth:downlink:downlinkBandwidth:` 返回对象类型
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
 *        `rtcEngine:onNetworkDetectionResult:quality:rtt:lostRate:bitrate:jitter:` 回调的参数类型
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
 *        SDK 内部遇到不可恢复的错误时，会通过 `rtcEngine:onError:` 回调通知用户。
 */
typedef NS_ENUM(NSInteger, ByteRTCErrorCode) {
    /** 
     * @brief Token 无效。
     *        进房时使用的 Token 无效或过期失效。需要用户重新获取 Token，并调用
     *        `updateToken:` 方法更新 Token。
     */
    ByteRTCErrorCodeInvalidToken               = -1000,
    /** 
     * @brief 加入房间错误。
     *        进房时发生未知错误导致加入房间失败。需要用户重新加入房间。
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
 * @type keytype
 * @brief 订阅媒体流状态
 */
typedef NS_ENUM(NSInteger, ByteRTCSubscribeState) {
    /** 
     * @brief 订阅/取消订阅流成功
     */
    ByteRTCSubscribeStateSuccess,
    /** 
     * @brief 订阅/取消订阅流失败，本地用户未在房间中
     */
    ByteRTCSubscribeStateFailedNotInRoom,
    /** 
     * @brief 订阅/取消订阅流失败，房间内未找到指定的音视频流
     */
    ByteRTCSubscribeStateFailedStreamNotFound,
    /** 
     * @brief 超过订阅流数上限
     */
    ByteRTCSubscribeStateFailedOverLimit,
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
     * @brief 当调用 `setUserVisibility:` 将自身可见性设置为 false 后，再尝试发布流会触发此警告。  <br>
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
     * @brief 当房间内人数超过 500 人时，停止向房间内已有用户发送 `rtcEngine:onUserJoined:elapsed:` 和 `rtcEngine:onUserLeave:reason:` 回调，并通过广播提示房间内所有用户。
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
     * @brief 不支持在 `publishScreen` 之后，通过 `setScreenAudioSourceType` 设置屏幕音频采集类型
     */
    ByteRTCWarningSetScreenAudioSourceTypeFailed = -5009,

    /** 
     * @brief 不支持在 `publishScreen` 之后，通过 `setScreenAudioStreamIndex` 设置屏幕音频混流类型
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
 * @type errorcode
 * @brief 登录结果  <br>
 *        调用 `login:uid:` 登录的结果，会通过 `rtcEngine:onLoginResult:errorCode:elapsed:` 回调通知用户。
 */
typedef NS_ENUM(NSInteger, ByteRTCLoginErrorCode) {
    /** 
     * @brief 调用 `login:uid:` 方法登录成功。
     */
    ByteRTCLoginErrorCodeSuccess = 0,
    /** 
     * @brief 调用 `login:uid:` 方法时使用的 Token 无效或过期失效。需要用户重新获取 Token。
     */
    ByteRTCLoginErrorCodeInvalidToken = -1000,
    /** 
     * @brief 登录错误  <br>
     *        调用 `login:uid:` 方法时发生未知错误导致登录失败。需要用户重新登录。
     */
    ByteRTCLoginErrorCodeLoginFailed = -1001,
    /** 
     * @brief 调用 `login:uid:` 方法时传入的用户 ID 有问题。
     */
    ByteRTCLoginErrorCodeInvalidUserId = -1002,
    /** 
     * @brief 调用 `login:uid:` 登录时服务器错误。
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
     *        对端用户已经调用 `logout`，或者没有调用 `login:uid:` 进行登录
     */
    ByteRTCUserOnlineStatusOffline = 0,
    /** 
     * @brief 对端用户在线
     *        对端用户调用 `login:uid:` 登录，并且连接状态正常
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
 * @type keytype
 * @brief 发布端音视频流回退选项
 */
typedef NS_ENUM(NSUInteger, ByteRTCPublishFallbackOption) {
    /** 
     * @brief 上行网络不佳或设备性能不足时，不对音视频流作回退处理。默认设置。
     */
    ByteRTCPublishFallbackOptionDisabled = 0,
    /** 
     * @brief 上行网络不佳或设备性能不足时，发布的视频流会从大流到小流依次降级，直到与当前网络性能匹配从大流开始做降级处理，具体降级规则参看[性能回退](70137)文档。
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
     * @brief 手动订阅模式。SDK 不自动订阅房间内的音视频流。你应根据需要调用 `subscribeStream` 方法手动订阅其他用户发布的音视频流。
     */
    ByteRTCSubscribeModeManual = 1
};
/** 
 * @type keytype
 * @brief 订阅端音视频流回退选项。
 */
typedef NS_ENUM(NSUInteger, ByteRTCSubscribeFallbackOption) {
    /** 
     * @brief 下行网络不佳或设备性能不足时，不对音视频流作回退处理。默认设置。
     */
    ByteRTCSubscribeFallbackOptionDisabled = 0,
    /** 
     * @brief 下行网络不佳或设备性能不足时，对视频流做降级处理，具体降级规则参看性能回退文档。 <br>
     *        该设置仅对发布端调用 enableSimulcastMode:{@link #ByteRTCEngineKit#enableSimulcastMode:} 开启发送多路流功能的情况生效。
     */
    ByteRTCSubscribeFallbackOptionVideoStreamLow = 1,
    /** 
     * @brief 下行网络不佳或设备性能不足时，取消接收视频，仅接收音频。
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
 *        SDK 通过 `onLocalAudioStateChanged` 回调该状态。  <br>
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
 *        SDK 通过 `onLocalAudioStateChanged` 回调该错误码。
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
    /** 
     * @brief 本地视频采集设备被移除
     */
    ByteRTCLocalVideoStreamErrorDeviceDisconnected = 7,
};

/** 
 * @type keytype
 * @brief 用户订阅的远端音频流状态。  <br>
 *        SDK 通过 `onRemoteAudioStateChanged` 回调该状态。  <br>
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
     *        刚收到远端音频流首包时，会触发回调 `onRemoteAudioStateChanged`，
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
     *        网络阻塞导致丢包率大于 40% 时，会触发回调 `onRemoteAudioStateChanged`，
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
 *        用户可以通过 `onRemoteAudioStateChanged` 了解该状态。
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
     * @brief 屏幕流视频设备
     */
    ByteRTCMediaDeviceTypeScreenVideoCaptureDevice = 4,
    /** 
     * @brief 屏幕流音频设备
     */
    ByteRTCMediaDeviceTypeScreenAudioCaptureDevice = 5
};

/** 
 * @type keytype
 * @brief 媒体设备状态
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
typedef NS_ENUM(NSInteger, ByteRTCMediaDeviceError) {
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
    ByteRTCMediaDeviceErrorUNSupportFormat = 7,
    /** 
     * @brief ios 屏幕采集没有 group id 参数
     */
    ByteRTCMediaDeviceErrorNotFindGroupId = 8
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
 * @brief 音视频流的发送/播放状态
 */
typedef NS_ENUM(NSInteger, ByteRTCMuteState) {
    /** 
     * @brief 发送
     */
    ByteRTCMuteStateOff = 0,
    /** 
     * @brief 停止发送
     */
    ByteRTCMuteStateOn = 1,
};

/** 
 * @type keytype
 * @brief 流属性
 */
typedef NS_ENUM(NSInteger, ByteRTCStreamIndex) {
    /** 
     * @brief 主流。包括：<br>
     *        + 由摄像头/麦克风通过内部采集机制，采集到的视频/音频; <br>
     *        + 通过自定义采集，采集到的视频/音频。
     */
    ByteRTCStreamIndexMain = 0,
    /** 
     * @brief 屏幕流。屏幕共享时共享的视频流，或来自声卡的本地播放音频流。
     */
    ByteRTCStreamIndexScreen = 1
};

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
 * @brief 媒体流跨房间转发状态
 */
typedef NS_ENUM(NSInteger, ByteRTCForwardStreamState) {
    /** 
     * @brief 空闲状态
     *        + 成功调用 `stopForwardStreamToRooms` 后，所有目标房间为空闲状态。
     *        + 成功调用 `updateForwardStreamToRooms` 减少目标房间后，本次减少的目标房间为空闲状态。
     */
    ByteRTCForwardStreamStateIdle = 0,
    /** 
     * @brief 开始转发
     *        + 调用 `startForwardStreamToRooms` 成功向所有房间开始转发媒体流后，返回此状态。
     *        + 调用 `updateForwardStreamToRooms` 后，成功向新增目标房间开始转发媒体流后，返回此状态。
     */
    ByteRTCForwardStreamStateSuccess = 1,
    /** 
     * @brief 转发失败，失败详情参考 ByteRTCForwardStreamError{@link #ByteRTCForwardStreamError}
     *        调用 `startForwardStreamToRooms` 或 `updateForwardStreamToRooms` 后，如遇转发失败，返回此状态。
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
     * @brief 目标房间已更新，由 `updateForwardStreamToRooms` 触发。
     */
    ByteRTCForwardStreamEventDstRoomUpdated = 3,
    /** 
     * @brief API 调用时序错误。例如，在调用 `startForwardStreamToRooms` 之前调用 `updateForwardStreamToRooms` 。
     */
    ByteRTCForwardStreamEventUnExpectAPICall = 4,
};

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
     * @brief 录制文件保存成功，调用 `stopFileRecording:` 结束录制之后才会收到该状态码。
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
 *  @type keytype
 *  @brief 用户信息。  <br>
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCUserInfo : NSObject
/** 
 * @brief 用户 ID。该字符串符合正则表达式：`[a-zA-Z0-9_@\-]{1,128}`。
 */
@property(copy, nonatomic) NSString *_Nonnull userId;
/** 
 * @brief 用户需要透传的额外的信息，字符长度限制为 200 字节。会在 `rtcEngine:onUserJoined:elapsed:` 中回调给远端用户。
 */
 @property(copy, nonatomic) NSString *_Nonnull extraInfo;
@end

/** 
 * @type keytype
 * @brief 房间通话统计数据，统计周期为 2s 。  <br>
 *        用户进房成功后，SDK 会周期性地通过 `onRoomStats` 回调通知用户当前房间内的汇总统计信息。此数据结构即为回调给用户的参数类型。  <br>
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCRoomStats : NSObject
/** 
 * @brief 用户进房开始通话后的总时长，单位为 s ，累计值
 */
@property(assign, nonatomic) NSInteger duration;
/** 
 * @brief 本地用户的总发送字节数 (bytes)，累计值
 */
@property(assign, nonatomic) NSInteger txBytes;
/** 
 * @brief 本地用户的总接收字节数 (bytes)，累计值
 */
@property(assign, nonatomic) NSInteger rxBytes;
/** 
 * @brief 本地用户的音频发送码率 (kbps)，瞬时值
 */
@property(assign, nonatomic) NSInteger txAudioKBitrate;
/** 
 * @brief 本地用户的音频接收码率 (kbps)，瞬时值
 */
@property(assign, nonatomic) NSInteger rxAudioKBitrate;
/** 
 * @brief 本地用户的视频发送码率 (kbps)，瞬时值
 */
@property(assign, nonatomic) NSInteger txVideoKBitrate;
/** 
 * @brief 本地用户的视频接收码率 (kbps)，瞬时值
 */
@property(assign, nonatomic) NSInteger rxVideoKBitrate;
/** 
 * @brief 当前房间内的用户人数，包括本地用户自身
 */
@property(assign, nonatomic) NSInteger userCount;
/** 
 * @brief App 现在的下行丢包率
 */
@property(assign, nonatomic) float rxLostrate;
/** 
 * @brief App 现在的上行丢包率
 */
@property(assign, nonatomic) float txLostrate;
/** 
 * @brief 客户端到服务端的往返时延
 */
@property(assign, nonatomic) NSInteger rtt;
/** 
 * @brief 当前 App 的 CPU 使用率
 */
// @property(assign, nonatomic) double cpuAppUsage;
/** 
 * @brief 当前设备的总 CPU 使用率
 */
// @property(assign, nonatomic) double cpuTotalUsage;


/** 
 * @brief 系统上行网络抖动（ms）
 */
@property(assign, nonatomic) NSInteger txJitter;
/** 
 * @brief 系统下行网络抖动（ms）
 */
@property(assign, nonatomic) NSInteger rxJitter;
@end

/** 
 * @type keytype
 * @brief App 使用的 cpu 和 memory 信息  <br>
 *        信息由 SDK 周期性（2s）地通过 `reportSysStats` 回调事件通知给用户。
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCSysStats : NSObject
/** 
 * @brief 当前系统 cpu 核数
 */
@property(assign, nonatomic) unsigned int cpu_cores;
/** 
 * @brief 当前应用的 CPU 使用率，取值范围为 [0, 1]。
 */
@property(assign, nonatomic) double cpu_app_usage;
/** 
 * @brief 当前系统的 CPU 使用率，取值范围为 [0, 1]。
 */
@property(assign, nonatomic) double cpu_total_usage;
/** 
 * @brief 当前App的内存使用（单位 MB）
 */
@property(assign, nonatomic) double memory_usage;
/** 
 * @brief 全量内存（单位MB）
 */
@property(assign, nonatomic) unsigned long long full_memory;
/** 
 * @brief 系统已使用内存（单位MB）
 */
@property(assign, nonatomic) unsigned long long total_memory_usage;
/** 
 * @brief 空闲可分配内存（单位MB）
 */
@property(assign, nonatomic) unsigned long long free_memory;
/** 
 * @brief 当前应用的内存使用率（单位 %）
 */
@property(assign, nonatomic) double memory_ratio;
/** 
 * @brief 系统内存使用率（单位 %）
 */
@property(assign, nonatomic) double total_memory_ratio;
@end

/** 
 * @type keytype
 * @brief 本地视频流统计信息，统计周期为 2s 。  <br>
 *        本地用户发布视频流成功后，SDK 会周期性地通过 `onLocalStreamStats`
 *        通知本地用户发布的视频流在此次统计周期内的发送状况。此数据结构即为回调给本地用户的参数类型。  <br>
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCLocalVideoStats : NSObject
/** 
 * @brief 发送的码率。此次统计周期内的视频发送码率，单位为 kbps 。  <br>
 */
@property(assign, nonatomic) float sentKBitrate;
/** 
 * @brief 采集帧率。此次统计周期内的视频采集帧率，单位为 fps 。
 */
@property(assign, nonatomic) NSInteger inputFrameRate;
/** 
 * @brief 发送帧率。此次统计周期内的视频发送帧率，单位为 fps 。
 */
@property(assign, nonatomic) NSInteger sentFrameRate;
/** 
 * @brief 编码器输出帧率。当前编码器在此次统计周期内的输出帧率，单位为 fps 。
 */
@property(assign, nonatomic) NSInteger encoderOutputFrameRate;
/** 
 * @brief 本地渲染帧率。此次统计周期内的本地视频渲染帧率，单位为 fps 。
 */
@property(assign, nonatomic) NSInteger rendererOutputFrameRate;
/** 
 * @brief 目标发送码率。此次统计周期内的视频目标发送码率，单位为 kbps 。
 */
@property(assign, nonatomic) NSInteger sentTargetKBitrate;
/** 
 * @brief 目标发送帧率。当前编码器在此次统计周期内的目标发送帧率，单位为 fps 。
 */
@property(assign, nonatomic) NSInteger sentTargetFrameRate;
/** 
 * @brief 统计间隔，单位为 ms 。
 * @notes 此字段用于设置回调的统计周期，默认设置为 2s 。
 */
@property(assign, nonatomic) NSInteger statsInterval;
/** 
 * @brief 视频丢包率。统计周期内的视频上行丢包率，取值范围为 [0, 1] 。  <br>
 */
@property(assign, nonatomic) float videoLossRate;
/** 
 * @brief 往返时延。单位为 ms 。  <br>
 */
@property(assign, nonatomic) NSInteger rtt;
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
@property(assign, nonatomic) BOOL isScreen;
/** 
 * @brief 视频上行网络抖动，单位为 ms。  <br>
 */
@property(assign, nonatomic) NSInteger jitter;
@end

/** 
 * @type keytype
 * @brief 远端音频流统计信息，统计周期为 2s 。  <br>
 *        本地用户订阅远端音频流成功后，SDK 会周期性地通过 `onRemoteStreamStats`
 *        通知本地用户订阅的远端视频流在此次统计周期内的接收状况。此数据结构即为回调给本地用户的参数类型。  <br>
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCRemoteVideoStats : NSObject
/** 
 * @brief 远端视频宽度。  <br>
 */
@property(assign, nonatomic) NSInteger width;
/** 
 * @brief 远端视频高度。  <br>
 */
@property(assign, nonatomic) NSInteger height;
/** 
 * @brief 远端视频丢包率。统计周期内的视频下行丢包率，取值范围为 [0, 1] 。  <br>
 */
@property(assign, nonatomic) float videoLossRate;
/** 
 * @brief 接收码率。统计周期内的视频接收码率，单位为 kbps 。  <br>
 */
@property(assign, nonatomic) float receivedKBitrate;
/** 
 * @brief 远端视频接收帧率。  <br>
 */
@property(assign, nonatomic) NSInteger receivedFrameRate;
/** 
 * @brief 远端视频解码输出帧率。  <br>
 */
@property(assign, nonatomic) NSInteger decoderOutputFrameRate;
/** 
 * @brief 远端视频渲染输出帧率。  <br>
 */
@property(assign, nonatomic) NSInteger renderOutputFrameRate;
/** 
 * @brief 远端视频卡顿次数。  <br>
 */
@property(assign, nonatomic) NSInteger stallCount;
/** 
 * @brief 远端视频卡顿时长，单位为 ms 。  <br>
 */
@property(assign, nonatomic) NSInteger stallDuration;
/** 
 * @brief 用户体验级别的端到端延时。从发送端采集完成编码开始到接收端解码完成渲染开始的延时，单位为 ms 。  <br>
 */
@property(assign, nonatomic) NSInteger e2eDelay;
/** 
 * @brief 远端视频流是否是屏幕共享流。你可以知道当前数据来自主流还是屏幕流。
 */
@property(assign, nonatomic) BOOL isScreen;
/** 
 * @brief 统计间隔，此次统计周期的间隔，单位为 ms 。  <br>
 * @notes 此字段用于设置回调的统计周期，目前设置为 2s 。
 */
@property(assign, nonatomic) NSInteger statsInterval;
/** 
 * @brief 往返时延。单位为 ms 。  <br>
 */
@property(assign, nonatomic) NSInteger rtt;
/** 
 * @brief 远端用户在进房后发生视频卡顿的累计时长占视频总有效时长的百分比（%）。视频有效时长是指远端用户进房发布视频流后，除停止发送视频流和禁用视频模块之外的视频时长。
 */
@property(assign, nonatomic) NSInteger frozenRate;
/** 
 * @brief SDK 订阅的远端视频流的分辨率下标。  <br>
 */
@property(assign, nonatomic) NSInteger videoIndex;
/** 
 * @brief 视频下行网络抖动，单位为 ms。  <br>
 */
@property(assign, nonatomic) NSInteger jitter;
@end

/** 
 * @type keytype
 * @brief 本地音频流统计信息，统计周期为 2s 。  <br>
 *        本地用户发布音频流成功后，SDK 会周期性地通过 `onLocalStreamStats`
 *        通知本地用户发布的音频流在此次统计周期内的发送状况。此数据结构即为回调给本地用户的参数类型。  <br>
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCLocalAudioStats : NSObject
/** 
 * @brief 音频丢包率。此次统计周期内的音频上行丢包率，取值范围为 [0, 1] 。  <br>
 */
@property(assign, nonatomic) float audioLossRate;
/** 
 * @brief 发送的码率。此次统计周期内的音频发送码率，单位为 kbps 。  <br>
 */
@property(assign, nonatomic) float sentKBitrate;
/** 
 * @brief 采集采样率。此次统计周期内的音频采集采样率信息，单位为 Hz 。  <br>
 */
@property(assign, nonatomic) NSInteger recordSampleRate;
/** 
 * @brief 统计间隔。此次统计周期的间隔，单位为 ms 。  <br>
 * @notes 此字段用于设置回调的统计周期，默认设置为 2s 。
 */
@property(assign, nonatomic) NSInteger statsInterval;
/** 
 * @brief 往返时延。单位为 ms 。  <br>
 */
@property(assign, nonatomic) NSInteger rtt;
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
 *        本地用户订阅远端音频流成功后，SDK 会周期性地通过 `onRemoteStreamStats`
 *        通知本地用户订阅的音频流在此次统计周期内的接收状况。此数据结构即为回调给本地用户的参数类型。  <br>
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCRemoteAudioStats : NSObject
/** 
 * @brief 音频丢包率。统计周期内的音频下行丢包率，取值范围为 [0, 1] 。  <br>
 */
@property(assign, nonatomic) float audioLossRate;
/** 
 * @brief 接收码率。统计周期内的音频接收码率，单位为 kbps 。  <br>
 */
@property(assign, nonatomic) float receivedKBitrate;
/** 
 * @brief 音频卡顿次数。统计周期内的卡顿次数。  <br>
 */
@property(assign, nonatomic) NSInteger stallCount;
/** 
 * @brief 音频卡顿时长。统计周期内的卡顿时长，单位为 ms 。  <br>
 */
@property(assign, nonatomic) NSInteger stallDuration;
/** 
 * @brief 播放采样率。统计周期内的音频播放采样率信息，单位为 Hz 。  <br>
 */
@property(assign, nonatomic) NSInteger playoutSampleRate;
/** 
 * @brief 用户体验级别的端到端延时。从发送端采集完成编码开始到接收端解码完成渲染开始的延时，单位为 ms 。  <br>
 */
@property(assign, nonatomic) NSInteger e2eDelay;
/** 
 * @brief 统计间隔。此次统计周期的间隔，单位为 ms 。  <br>
 */
@property(assign, nonatomic) NSInteger statsInterval;
/** 
 * @brief 客户端到服务端数据传输的往返时延，单位为 ms。  <br>
 */
@property(assign, nonatomic) NSInteger rtt;
/** 
 * @brief 发送端——服务端——接收端全链路数据传输往返时延。单位为 ms 。  <br>
 */
@property(assign, nonatomic) NSInteger total_rtt;
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
 * @brief 本地音/视频流统计信息以及网络状况，统计周期为 2s 。  <br>
 *        本地用户发布音/视频流成功后，SDK 会周期性地通过 `onLocalStreamStats`
 *        通知本地用户发布的音/视频流在此次统计周期内的发送状况。此数据结构即为回调给用户的参数类型。  <br>
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCLocalStreamStats : NSObject
/** 
 * @brief 本地设备发送音频流的统计信息，详见 ByteRTCLocalAudioStats{@link #ByteRTCLocalAudioStats}
 */
@property(strong, nonatomic) ByteRTCLocalAudioStats *_Nonnull audio_stats;
/** 
 * @brief 本地设备发送视频流的统计信息，详见 ByteRTCLocalVideoStats{@link #ByteRTCLocalVideoStats}
 */
@property(strong, nonatomic) ByteRTCLocalVideoStats *_Nonnull video_stats;
/** 
 * @hidden
 * @brief 所属用户的媒体流上行网络质量，详见 ByteRTCNetworkQuality{@link #ByteRTCNetworkQuality}
 * @deprecated since 336.1, use rtcEngine:onNetworkQuality:remoteQualities:{@link #ByteRTCEngineDelegate#rtcEngine:onNetworkQuality:remoteQualities:} instead
 */
@property(assign, nonatomic) ByteRTCNetworkQuality tx_quality;
/** 
 * @hidden
 * @brief 所属用户的媒体流下行网络质量，详见 ByteRTCNetworkQuality{@link #ByteRTCNetworkQuality}
 * @deprecated since 336.1, use rtcEngine:onNetworkQuality:remoteQualities:{@link #ByteRTCEngineDelegate#rtcEngine:onNetworkQuality:remoteQualities:} instead
 */
@property(assign, nonatomic) ByteRTCNetworkQuality rx_quality;
/** 
 * @brief 所属用户的媒体流是否为屏幕流。你可以知道当前统计数据来自主流还是屏幕流。
 */
@property(nonatomic, assign) BOOL is_screen;

@end

/** 
 * @type keytype
 * @brief 用户订阅的远端音/视频流统计信息以及网络状况，统计周期为 2s 。  <br>
 *        订阅远端用户发布音/视频流成功后，SDK 会周期性地通过 `onRemoteStreamStats`
 *        通知本地用户订阅的远端音/视频流在此次统计周期内的接收状况。此数据结构即为回调给本地用户的参数类型。  <br>
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCRemoteStreamStats : NSObject
/** 
 * @brief 用户 ID 。音频来源的用户 ID 。  <br>
 */
@property(copy, nonatomic) NSString *_Nonnull uid;
/** 
 * @brief 远端音频流的统计信息，详见 ByteRTCRemoteAudioStats{@link #ByteRTCRemoteAudioStats}
 */
@property(strong, nonatomic) ByteRTCRemoteAudioStats *_Nonnull audio_stats;
/** 
 * @brief 远端视频流的统计信息，详见 ByteRTCRemoteVideoStats{@link #ByteRTCRemoteVideoStats}
 */
@property(strong, nonatomic) ByteRTCRemoteVideoStats *_Nonnull video_stats;
/** 
 * @hidden
 * @brief 所属用户的媒体流上行网络质量，详见 ByteRTCNetworkQuality{@link #ByteRTCNetworkQuality}
 * @deprecated since 336.1, use rtcEngine:onNetworkQuality:remoteQualities:{@link #ByteRTCEngineDelegate#rtcEngine:onNetworkQuality:remoteQualities:} instead
 */
@property(assign, nonatomic) ByteRTCNetworkQuality tx_quality;
/** 
 * @hidden
 * @brief 所属用户的媒体流下行网络质量，详见 ByteRTCNetworkQuality{@link #ByteRTCNetworkQuality}
 * @deprecated since 336.1, use rtcEngine:onNetworkQuality:remoteQualities:{@link #ByteRTCEngineDelegate#rtcEngine:onNetworkQuality:remoteQualities:} instead
 */
@property(assign, nonatomic) ByteRTCNetworkQuality rx_quality;
/** 
 * @brief 所属用户的媒体流是否为屏幕流。你可以知道当前统计数据来自主流还是屏幕流。
 */
@property(nonatomic, assign) BOOL is_screen;

@end

/** 
 * @type keytype
 * @brief 用户信息
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCUser : NSObject
/** 
 * @brief 用户 ID
 */
@property(nonatomic, copy, nullable) NSString *userId;
/** 
 * @brief 元信息
 */
@property(nonatomic, copy, nullable) NSString *metaData;
@end

/** 
 * @type keytype
 * @brief 用户信息
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCRemoteStreamKey : NSObject
/** 
 * @brief 用户 ID
 */
@property(nonatomic, copy, nullable) NSString *userId;
/** 
 * @brief 房间 ID
 */
@property(nonatomic, copy, nullable) NSString *roomId;
/** 
 * @brief 流属性，包括主流、屏幕流。参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 */
@property(nonatomic, assign) ByteRTCStreamIndex streamIndex;
@end

#pragma mark - EncryptHandler
/** 
 * @type callback
 * @region 加密
 * @author wangjunlin.3182
 * @brief 自定义加密接口
 */
@protocol ByteRTCEncryptHandler <NSObject>

@required
/** 
 * @type api
 * @region 加密
 * @author wangjunlin.3182
 * @brief 自定义加密。  <br>
 *        使用设定的自定义加密方式，对传输前的音视频帧数据进行加密。
 * @param rawData 原始音视频帧数据
 * @return 加密后的数据  <br>
 *        + 非空，表示加密后的数据  <br>
 *        + 为空，表示数据被丢弃
 * @notes <br>
 *        + 使用此接口进行自定义加密前，你必须先设置自定义加密方式，参看 `setCustomizeEncryptHandler:`。
 *        + 使用 ByteRTCDecryptRawData:{@link #ByteRTCEncryptHandler#ByteRTCDecryptRawData:} 对已加密的音视频帧数据进行解密。
 *        + 返回的数据大小应控制在原始数据的 90% ~ 120% 范围以内，不然将被丢弃。
 */
- (NSData * _Nonnull) ByteRTCEncryptRawData:(NSData * _Nonnull)rawData;

@required
/** 
 * @type api
 * @region 加密
 * @author wangjunlin.3182
 * @brief 自定义解密。  <br>
 *        对自定义加密后的音视频帧数据进行解密。关于自定义加密，参看 ByteRTCEncryptRawData:{@link #ByteRTCEncryptHandler#ByteRTCEncryptRawData:}。
 * @param rawData 收到的已加密的音视频帧数据
 * @return 解密后的数据  <br>
 *        + 非空，表示解密后的数据  <br>
 *        + 为空，表示丢弃该帧
 * @notes <br>
 *        + 使用此接口进行解密前，你必须先设定解密方式，参看 `setCustomizeEncryptHandler:`。
 *        + 返回的数据大小应控制在原始数据的 90% ~ 120% 范围以内，不然将被丢弃。
 */
- (NSData * _Nonnull) ByteRTCDecryptRawData:(NSData * _Nonnull)rawData;
@end

__attribute((deprecated("Will be removed in new version")))
/** 
 * @type callback
 * @region 监控
 * @brief 非业务相关的监控事件回调
 */
@protocol ByteRTCMonitorDelegate <NSObject>

@optional

/** 
 * @type callback
 * @region 监控
 * @brief 埋点日志回调  <br>
 * @param data  <br>
 *        具体的埋点内容  <br>
 * @param type  <br>
 *        埋点的类型
 */
- (void)onMonitorLog:(NSDictionary * _Nullable)data withType:(NSString * _Nullable)type;

/** 
 * @type api
 * @region 监控
 * @brief 是否进行控制台输出
 * @return
 *        返回是否进行控制台输出  <br>
 *        + YES 输出所有的日志到控制台  <br>
 *        + NO 不输出任何控制台信息
 */
- (BOOL)isConsole;

/** 
 * @type callback
 * @region 监控
 * @brief 输出更多的调试信息
 */
- (void)onVerboseLogWithLevel:(ByteRTCLogLevel)level
                     filename:(NSString * _Nonnull)filename
                          tag:(NSString * _Nonnull)tag
                         line:(int)line
                 functionName:(NSString * _Nonnull)funcName
                       format:(NSString * _Nonnull)format;

@end

#pragma mark - FileRecording

/** 
 * @type keytype
 * @brief 本地录制参数配置
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCRecordingConfig : NSObject
/** 
 * @brief 录制文件保存的绝对路径。你需要指定一个有读写权限的合法路径。
 */
@property(strong, nonatomic) NSString* _Nullable dirPath;
/** 
 * @brief 录制存储文件格式，参看 ByteRTCRecordingFileType{@link #ByteRTCRecordingFileType}
 */
@property(assign, nonatomic) ByteRTCRecordingFileType recordingFileType;
@end

/** 
 * @type keytype
 * @brief 本地录制进度
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCRecordingProgress : NSObject
/** 
 * @brief 当前文件的累计录制时长，单位：毫秒
 */
@property(assign, nonatomic) unsigned long long duration;
/** 
 * @brief 当前录制文件的大小，单位：byte
 */
@property(assign, nonatomic) unsigned long long fileSize;
@end

/** 
 * @type keytype
 * @brief 本地录制的详细信息
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCRecordingInfo : NSObject
/** 
 * @brief 录制文件的绝对路径，包含文件名和文件后缀
 */
@property(strong, nonatomic) NSString* _Nullable filePath;
/** 
 * @brief 录制文件的视频编码类型，参看 ByteRTCVideoCodecType{@link #ByteRTCVideoCodecType}
 */
@property(assign, nonatomic) ByteRTCVideoCodecType codecType;
/** 
 * @brief 录制视频的宽，单位：像素。纯音频录制请忽略该字段
 */
@property(nonatomic, assign) NSInteger width;
/** 
 * @brief 录制视频的高，单位：像素。纯音频录制请忽略该字段
 */
@property(nonatomic, assign) NSInteger height;
@end

/** 
 * @type keytype
 * @brief 媒体流信息同步的相关配置
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCStreamSycnInfoConfig : NSObject

/** 
 * @brief 流属性，主流或屏幕流。见 ByteRTCStreamIndex{@link #ByteRTCStreamIndex} 。
 */
@property(assign, nonatomic) ByteRTCStreamIndex streamIndex;
/** 
 * @brief 消息发送的重复次数，取值范围是 [0,25]，建议设置为 [3,5]。
 */
@property(assign, nonatomic) int repeatCount;
/** 
 * @brief 媒体流信息同步的流类型，见 ByteRTCSyncInfoStreamType{@link #ByteRTCSyncInfoStreamType} 。
 */
@property(assign, nonatomic) ByteRTCSyncInfoStreamType streamType;

@end

/** 
 * @type keytype
 * @brief 媒体流跨房间转发的目标房间的相关信息
 */
BYTERTC_APPLE_EXPORT @interface ForwardStreamConfiguration: NSObject
    /** 
     * @brief 跨间转发媒体流过程中目标房间 ID<br>
     */
    @property(strong, nonatomic) NSString* _Nullable roomId;
    /** 
     * @brief 用于向该房间转发媒体流的 Token。<br>
     *        如果 Token 无效，转发失败。
     */
    @property(strong, nonatomic) NSString* _Nullable token;
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
    @property(strong, nonatomic) NSString* _Nullable roomId;
    /** 
     * @brief 跨房间转发媒体流过程中该目标房间的状态，参看 ByteRTCForwardStreamState{@link #ByteRTCForwardStreamState}
     */
    @property(assign, nonatomic) ByteRTCForwardStreamState state;
    /** 
     * @brief 跨房间转发媒体流过程中该目标房间抛出的错误码，参看 ByteRTCForwardStreamError{@link #ByteRTCForwardStreamError}
     */
    @property(assign, nonatomic) ByteRTCForwardStreamError error;
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
    @property(strong, nonatomic) NSString* _Nullable roomId;
    /** 
     * @brief 跨房间转发媒体流过程中该目标房间发生的事件，参看 ByteRTCForwardStreamEvent{@link #ByteRTCForwardStreamEvent}
     */
    @property(assign, nonatomic) ByteRTCForwardStreamEvent event;
@end

/** 
 * @type keytype
 * @brief 上行/下行网络质量
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCNetworkQualityStats: NSObject
/** 
 * @brief 用户 ID
 */
@property(strong, nonatomic) NSString* _Nonnull uid;
/** 
 * @brief 本端的上行/下行的丢包率，范围 [0.0,1.0]
 *        当 `uid` 为本地用户时，代表发布流的上行丢包率。
 *        当 `uid` 为远端用户时，代表接收所有订阅流的下行丢包率。
 */
@property(assign, nonatomic) double lossRatio;
/** 
 * @brief 当 `uid` 为本地用户时有效，客户端到服务端的往返延时（RTT），单位：ms
 */
@property(assign, nonatomic) int rtt;
/** 
 * @brief 本端的音视频 RTP 包 2 秒内的平均传输速率，单位：bps
 *        当 `uid` 为本地用户时，代表发送速率。
 *        当 `uid` 为远端用户时，代表所有订阅流的接收速率。
 */
@property(assign, nonatomic) int totalBandwidth;
/** 
 * @brief 上行网络质量评分，详见 ByteRTCNetworkQuality{@link #ByteRTCNetworkQuality}。
 */
@property(assign, nonatomic) ByteRTCNetworkQuality txQuality;
/** 
 * @brief 下行网络质量评分，详见 ByteRTCNetworkQuality{@link #ByteRTCNetworkQuality}。
 */
@property(assign, nonatomic) ByteRTCNetworkQuality rxQuality;
@end
