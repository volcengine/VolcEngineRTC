/*
 * Copyright (c) 2020 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngine Defines
*/

#import <CoreMedia/CMTime.h>
#import <AppKit/AppKit.h>

/**
 * @type keytype
 * @brief 视频显示模式
*/
typedef NS_ENUM(NSUInteger, ByteRTCRenderMode) {
    /**
     * @brief 视频尺寸等比缩放，优先保证窗口被填满。当视频尺寸与显示窗口尺寸不一致时，多出的视频将被截掉。
    */
    ByteRTCRenderModeHidden = 1,

    /**
     * @brief 视频尺寸等比缩放，优先保证视频内容全部显示。当视频尺寸与显示窗口尺寸不一致时，会把窗口未被填满的区域填充成黑色。
    */
    ByteRTCRenderModeFit = 2,

    /**
     * @brief (已经废弃，不再兼容该模式）视频尺寸非等比例缩放，把窗口充满。当视频尺寸与显示窗口尺寸不一致时，视频高或宽方向会被拉伸。(已经废弃，不再兼容该模式）
    */
    ByteRTCRenderModeAdaptive = 3,
};

/**
 * @type keytype
 * @brief 用户离线原因。
 *         房间内远端用户离开时，本端用户会收到 rtcEngine:onUserLeave:reason:{@link #rtcEngine:onUserLeave:reason:}  回调通知，此枚举类型为回调的用户离线原因。
 */
typedef NS_ENUM(NSUInteger, ByteRTCUserOfflineReason) {
    /**
     * @brief 用户主动离开。
     */
    ByteRTCUserOfflineReasonQuit = 0,
    /**
     * @brief 用户掉线。
     */
    ByteRTCUserOfflineReasonDropped = 1,
    /**
     * @hidden
     */
    ByteRTCUserOfflineReasonBecomeAudience = 2,
};

/*
 * @type keytype
 * @brief 订阅模式选项。业务方在加入房间前，调用 enableAutoSubscribe:videoMode:{@link #ByteRTCEngineKit#enableAutoSubscribe:videoMode:} 接口设置订阅模式。  <br>
 */
typedef NS_ENUM(NSUInteger, ByteRTCSubscribeMode) {
    /**
     * @brief 自动订阅模式。SDK 会自动为用户订阅房间中的每一路流。  <br>
     */
    ByteRTCSubscribeModeAuto = 0,
    /**
     * @brief 手动订阅模式。SDK 不为自动订阅流。用户需要自己手动调用 subscribeStream:subscribeConfig:{@link #ByteRTCEngineKit#subscribeStream:subscribeConfig:} 接口去订阅远端流。
     */
    ByteRTCSubscribeModeManual = 1
};

/**
 * @type keytype
 * @brief 房间内远端流移除原因。  <br>
 *        房间内远端音视频流移除时，SDK 会通过 rtcEngine:didStreamRemoved:reason:{@link #ByteRTCEngineDelegate#rtcEngine:didStreamRemoved:reason:} 回调通知用户。此枚举类型即为通知的远端流移除的原因。  <br>
 */
typedef NS_ENUM(NSInteger, VEStreamRemoveReason) {
    /**
     * @brief 远端用户停止发布流。  <br>
     */
    ByteRTCStreamRemoveUnpublish = 0,
    /**
     * @brief 远端用户发布流失败。  <br>
     */
    ByteRTCStreamRemovePublishFailed = 1,
    /**
     * @brief 保活失败。  <br>
     */
    ByteRTCStreamRemoveKeepLiveFailed = 2,
    /**
     * @brief 远端用户断网。  <br>
     */
    ByteRTCStreamRemoveClientDisconnected = 3,
    /**
     * @brief 远端用户重新发布流。  <br>
     */
    ByteRTCStreamRemoveRepublish = 4,
    /**
     * @brief 其他原因。  <br>
     */
    ByteRTCStreamRemoveOtherReason = 5,
};

/**
 * @type keytype
 * @brief 房间模式。
 *         房间使用的场景模式。
 */
typedef NS_ENUM(NSInteger, ByteRTCRoomProfile) {
    /**
     * @brief 通信模式。该房间模式下，房间内所有用户都可以发布和订阅流。适用于 IM 场景。
     */
    ByteRTCRoomProfileCommunication = 0,
    /**
     * @brief 直播模式。该房间模式下，用户有主播、静默观众三种可选角色，可以通过调用方法 setUserRole:withKey:{@link #setUserRole:withKey:}
     *         设置。主播可以发布和订阅流，静默观众只能订阅流。适用于直播、教育大班课等场景。
     */
    ByteRTCRoomProfileLiveBroadcasting = 1,
    /**
     * @brief 游戏模式。该房间模式下，用户角色同直播模式。适用于游戏场景。
     * @author shazhou
     */
    ByteRTCRoomProfileGame = 2,
    /**
     * @brief 云游戏模式。该房间模式下，用户角色同直播模式。适用于云游戏场景。
     * @author wuxinyu.mrx
     */
    ByteRTCRoomProfileCloudGame = 3,
};

/**
 * @type keytype
 * @brief 用户角色。
 *         房间模式为直播、游戏、云游戏模式时的用户角色。
 */
typedef NS_ENUM(NSInteger, ByteRTCUserRoleType) {
    /**
     * @brief 主播角色，用户既可以发布流到房间中，也可以从房间中订阅流。
     */
    ByteRTCUserRoleTypeBroadcaster = 1,
    /**
     * @brief
     * 静默观众模式，除了满足观众角色限制外，房间中的其他用户无法感知到该用户在房间中，即该用户加入退出房间和更新用户属性等行为不会通知给房间中的其他用户。
     */
    ByteRTCUserRoleTypeAudience = 2,
};

/**
 * @type keytype
 * @brief 视频流类型
 *      目前C++ sdk 只支持 kVideoStreamTypeHigh类型
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
 * @brief SDK 网络连接类型
 */
typedef NS_ENUM(NSInteger, ByteRTCNetworkType) {
    /**
     * @brief 网络连接类型未知
     */
    ByteRTCNetworkTypeUnknown = -1,
    /**
     * @brief 网络连接已断开
     */
    ByteRTCNetworkTypeDisconnected = 0,
    /**
     * @brief 网络连接类型为 LAN
     */
    ByteRTCNetworkTypeLAN = 1,
    /**
     * @brief 网络连接类型为 Wi-Fi（包含热点）
     */
    ByteRTCNetworkTypeWIFI = 2,
    /**
     * @brief 网络连接类型为 2G 移动网络
     */
    ByteRTCNetworkTypeMobile2G = 3,
    /**
     * @brief 网络连接类型为 3G 移动网络
     */
    ByteRTCNetworkTypeMobile3G = 4,
    /**
     * @brief 网络连接类型为 4G 移动网络
     */
    ByteRTCNetworkTypeMobile4G = 5,
    /**
     * @brief 网络连接类型为 5G 移动网络
     */
    ByteRTCNetworkTypeMobile5G = 6,
};

/**
 * @type keytype
 * @brief 媒体流网络质量
*/
typedef NS_ENUM(NSUInteger, ByteRTCNetworkQuality) {
    /**
     * @brief 网络质量未知
     */
    ByteRTCNetworkQualityUnknown = 0,
    /**
     * @brief 网络质量极好
     */
    ByteRTCNetworkQualityExcellent = 1,
    /**
     * @brief 网络质量好
     */
    ByteRTCNetworkQualityGood = 2,
    /**
     * @brief 网络质量较差但不影响沟通
     */
    ByteRTCNetworkQualityPoor = 3,
    /**
     * @brief 网络质量差沟通不顺畅
     */
    ByteRTCNetworkQualityBad = 4,
    /**
     * @brief 网络质量非常差
     */
    ByteRTCNetworkQualityVBad = 5,
};

/**
 * @type errorcode
 * @brief 回调错误码。
 *         SDK 内部遇到不可恢复的错误时，会通过 rtcEngine:didOccurError:{@link #rtcEngine:didOccurError:} 回调通知用户。
 */
typedef NS_ENUM(NSInteger, ByteRTCErrorCode) {
    /**
     * @brief Token 无效。
     *         调用 joinChannelByKey:channelName:info:uid:{@link #joinChannelByKey:channelName:info:uid:} 方法时使用的 Token 无效或过期失效。需要用户重新获取 Token，并调用
     *         renewChannelKey:{@link #renewChannelKey:} 方法更新 Token。
     */
    ByteRTCErrorCodeInvalidToken               = -1000,
    /**
     * @brief 加入房间错误。
     *         调用 joinChannelByKey:channelName:info:uid:{@link #joinChannelByKey:channelName:info:uid:} 方法时发生未知错误导致加入房间失败。需要用户重新加入房间。
     */
    ByteRTCErrorCodeJoinRoom             = -1001,
    /**
     * @brief 没有发布音视频流权限。
     *         用户在所在房间中发布音视频流失败，失败原因为用户没有发布流的权限。
     */
    ByteRTCErrorCodeNoPublishPermission       = -1002,
    /**
     * @brief 没有订阅音视频流权限。
     *         用户订阅所在房间中的音视频流失败，失败原因为用户没有订阅流的权限。
     */
    ByteRTCErrorCodeNoSubscribePermission     = -1003,
    /**
     * @brief 用户重复登录。
     *         本端用户所在房间中有相同用户 ID 的用户登录，导致本端用户被踢出房间。
     */
    ByteRTCErrorCodeDuplicateLogin             = -1004,
    /**
     * @brief 订阅音视频流总数超过上限。
     *         游戏场景下为了保证音视频通话的性能和质量，服务器会限制用户订阅的音视频流的总数。当用户订阅的音视频流总数已达上限时，继续订阅更多流时会失败
     *         同时通知用户订阅音视频流总数超过上限。
     */
    ByteRTCErrorCodeOverSubscribeLimit        = -1070,
    /**
     * @brief 发布流失败，发布流总数超过上限。
     *        RTC 系统会限制单个房间内发布的总流数，总流数包括视频流、音频流和屏幕流。如果房间内发布流数已达上限时，本地用户尝试向房间中发布流时会失败，SDK通过回调此错误通知用户。
     */
    ByteRTCErrorCodeOverStreamPublishLimit = -1080,
    /**
     * @brief 发布屏幕流失败，发布流总数超过上限。
     *        RTC 系统会限制单个房间内发布的总流数，总流数包括视频流、音频流和屏幕流。如果房间内发布流数已达上限时，本地用户尝试向房间中发布流时会失败，SDK通过回调此错误通知用户。
     */
    ByteRTCErrorCodeOverScreenPublishLimit = -1081,
    /**
     * @brief 发布视频流总数超过上限。
     *        RTC 系统会限制单个房间内发布的视频流数。如果房间内发布视频流数已达上限时，本地用户尝试向房间中发布视频流时会失败，SDK通过回调此错误通知用户。
     */
    ByteRTCErrorCodeOverVideoPublishLimit = -1082,
};

/**
 * @type keytype
 * @brief 订阅流状态
 *      该结构表示在订阅流或者更新流后获取的结果
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
    ByteRTCSubscribeStateFailedOverLimit
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
     * @brief 加入房间失败。
     *        用户调用 joinChannelByKey:channelName:info:uid:{@link #joinChannelByKey:channelName:info:uid:} 加入房间或由于网络状况不佳断网重连时，由于服务器错误导致用户加入房间失败。SDK 会自动重试加入房间。
     */
    ByteRTCWarningCodeJoinRoomFailed             = -2001,
    /**
     * @brief 发布音视频流失败。
     *         用户在所在房间中发布音视频流时，由于服务器错误导致发布失败。SDK 会自动重试发布。
     */
    ByteRTCWarningCodePublishStreamFailed        = -2002,
    /**
     * @brief 订阅音视频流失败。
     *         当前房间中找不到订阅的音视频流导致订阅失败。建议用户退出重试。
     */
    ByteRTCWarningCodeSubscribeStreamFailed404  = -2003,
    /**
     * @brief 订阅音视频流失败。
     *        用户订阅所在房间中的音视频流时，由于服务器错误导致订阅失败。SDK 会自动重试订阅。
     */
    ByteRTCWarningCodeSubscribeStreamFailed5xx  = -2004,
    /**
     * @hidden
     * @brief 用户加入房间后设置分辨率错误，当前代码中未使用
     */
    ByteRTCWarningCodeInvokeError = -2005,
    /**
     * @hidden
     * @brief 调度异常，server返回的媒体服务器地址不可用。
     */
    ByteRTCWarningCodeInvalidExpectMediaServerAddress = -2007,
    /**
     * @brief 用户手动订阅音视频流错误。
     *         自动订阅功能开启时，用户调用 subscribeStream: {@link #subscribeStream:} 方法手动订阅音视频流时触发此警告。
     */
    ByteRTCWarningCodeSubscribeStreamForbiden = -2010,
    /**
     * @brief 发送自定义广播消息失败，当前用户未在房间中。
     */
    ByteRTCWarningCodeSendCustomMessage = -2011,
    /**
     * @brief 没有相机权限。
     *         当前 App 没有相机权限。
     */
    ByteRTCWarningCodeNoCameraPermission            = -5001,
    /**
     * @brief 没有麦克风权限。
     *         当前 App 没有麦克风权限。
     */
    ByteRTCWarningCodeNoMicrophonePermission        = -5002,
    /**
     * @brief 录音设备启动失败。
     *        启动录音设备失败，当前录音设备可能被其他应用占用。
     */
    ByteRTCWarningCodeAudioDeviceManagerRecordingStartFail     = -5003,
    /**
     * @brief 播放设备启动失败警告
     *      可能由于系统资源不足，或参数错误
     */
    ByteRTCWarningCodeAudioDeviceManagerPlayoutStartFail = -5004,
	/**
     * @brief 无可用录音设备
     *        启动录音设备失败，请插入可用的录音设备
     */
    ByteRTCWarningCodeNoRecordingDevice = -5005,

    /**
     * @brief 无可用播放设备
     *        启动播放设备失败，请插入可用的播放设备
     */
    ByteRTCWarningCodeNoPlayoutDevice = -5006,

    /**
     * @brief 音频采集静音警告
     *        当前音频设备采集静音，请检查更换音频设备
     */
    ByteRTCWarningCodeRecordingSilence = -5007,
    
    /**
     * @brief 媒体设备误操作警告
     *        不支持外部源场景下，通过 SDK 进行媒体设备的开启、停止操作
     */
    ByteRTCWarningCodeMediaDeviceOperationDenied = -5008
};

/**
 * @type errorcode
 * @brief 直播推流转码功能错误码。
 *         用户调用 enableLiveTranscoding{@link #enableLiveTranscoding} 方法启动直播推流转码功能后，后处理服务器返回的执行结果。
 */
typedef NS_ENUM(NSInteger, ByteRTCTranscodingError) {
    /**
     * @brief 推流成功。
     */
    ByteRTCTranscodingErrorOK = 0,
    /**
     * @brief 推流参数错误。
     */
    ByteRTCTranscodingErrorInvalidArgument = 1,
    /**
     * @brief 后处理订阅流失败。
     */
    ByteRTCTranscodingErrorSubscribe = 2,
    /**
     * @brief 合流服务中间过程存在错误。
     */
    ByteRTCTranscodingErrorProcessing = 3,
    /**
     * @brief 推 CDN 失败。
     */
    ByteRTCTranscodingErrorPublish = 4,
};

/**
 * @type keytype
 * @brief 视频镜像模式。
*/
typedef NS_ENUM(NSUInteger, ByteRTCMirrorMode) {
    /**
     * @brief 关闭本地视频镜像
    */
    ByteRTCMirrorModeOff = 0,
    /**
     * @brief 开启本地视频镜像
    */
    ByteRTCMirrorModeOn = 1,
};

/**
 * @type keytype
 * @brief 日志级别
 */
typedef NS_ENUM(NSUInteger, ByteRTCLogLevel){
    /**
     * @brief 打印trace级别及以上级别信息
    */
    ByteRTCLogLevelTrace,
    /**
     * @brief 打印debug级别及以上级别信息
    */
    ByteRTCLogLevelDebug,
    /**
     * @brief 打印info级别及以上级别信息
    */
    ByteRTCLogLevelInfo,
    /**
     * @brief 打印warning级别及以上级别信息
    */
    ByteRTCLogLevelWarning,
    /**
     * @brief 打印error级别信息
    */
    ByteRTCLogLevelError
};

/**
 * @type keytype
 * @brief 视频帧类型
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoSinkPixelFormat) {
    /**
     * @brief YUV image with i420 layout, also known as yuv420p
     */
    ByteRTCVideoPixelFormatI420 = 1,
    /**
     * @brief BGRA image
     */
    ByteRTCVideoPixelFormatBGRA = 2,
    /**
     * @brief YUV image with NV12 layout
     */
    ByteRTCVideoPixelFormatNV12 = 8,
};

/**
 * @type keytype
 * @brief 视频旋转信息，枚举类型，定义了90度为间隔的四种旋转模式。
*/
typedef NS_ENUM(NSInteger, ByteRTCVideoRotation) {
    /**
     * @brief 视频不做旋转
    */
    ByteRTCVideoRotation0 = 0,
    /**
     * @brief 视频旋转90度
    */
    ByteRTCVideoRotation90 = 90,
    /**
     * @brief 视频旋转180度
    */
    ByteRTCVideoRotation180 = 180,
    /**
     * @brief 视频旋转270度
    */
    ByteRTCVideoRotation270 = 270,
};

/**
 * @type keytype
 * @brief 视频缩放模式
*/
typedef NS_ENUM(NSInteger, ByteRTCVideoStreamScaleMode) {
    /**
     * @brief 自动缩放模式，当前等价于ByteRTCVideoStreamScaleModeFitWithCropping
    */
    ByteRTCVideoStreamScaleModeAuto            = 0,
    /**
     * @brief 缩放以适配宽高比
    */
    ByteRTCVideoStreamScaleModeStretch         = 1,
    /**
     * @brief 保持纵横比来缩放图像，裁剪长边
    */
    ByteRTCVideoStreamScaleModeFitWithCropping = 2,
    /**
     * @brief 保持纵横比来缩放图像，填充短边
    */
    ByteRTCVideoStreamScaleModeFitWithFilling  = 3,
};


/**
 * @type keytype
 * @brief 编码质量偏好
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoEncoderPreference) {
    /**
     * @brief 关闭
    */
    ByteRTCVideoEncoderPreferenceDisabled          = 0,
    /**
     * @brief 保持帧率
    */
    ByteRTCVideoEncoderPreferenceMaintainFramerate = 1,
    /**
     * @brief 保持画质
    */
    ByteRTCVideoEncoderPreferenceMaintainQuality   = 2,
    /**
     * @brief 平衡模式
    */
    ByteRTCVideoEncoderPreferenceBalance           = 3,
};

/**
 * @type errorcode
 * @brief 登录结果
 */
typedef NS_ENUM(NSInteger, ByteRTCLoginErrorCode) {
    /**
     * @brief 登录成功。
     *        调用 Login{@link #Login} 方法登录成功。
     */
    ByteRTCLoginErrorCodeSuccess = 0,
    /**
     * @brief Token 无效。
     *        调用 Login{@link #Login} 方法时使用的 Token 无效或过期失效。需要用户重新获取 Token。
     */
    ByteRTCLoginErrorCodeInvalidToken = -1000,
    /**
     * @brief 加入房间错误。
     *        调用 Login{@link #Login} 方法时发生未知错误导致登录失败。需要用户重新登录。
     */
    ByteRTCLoginErrorCodeLoginFailed = -1001,
    /**
     * @brief UserId非法。
     *        调用 Login{@link #Login} 方法时传入的UserId有问题。
     */
    ByteRTCLoginErrorCodeInvalidUserId = -1002,
    /**
     * @brief 服务端错误。
     *        调用 Login{@link #Login} 登录时服务器错误。
     */
    ByteRTCLoginErrorCodeServerError = -1003,
};

/**
 * @type errorcode
 * @brief 消息发送结果
 */
typedef NS_ENUM(NSInteger, ByteRTCUserMessageSendResult) {
    /**
     * @brief 成功
    */
    ByteRTCUserMessageSendResultSuccess = 0,
    /**
     * @brief 超时,未能发送出去
    */
    ByteRTCUserMessageSendResultTimeout = 1,
    /**
     * @brief 通道中断导致没有发送出去
    */
    ByteRTCUserMessageSendResultBroken = 2,
    /**
     * @brief 没有找到对应的接收者
    */
    ByteRTCUserMessageSendResultNoReceiver = 3,
    /**
     * @brief 失败，获取级联路径失败
     */
    ByteRTCUserMessageSendResultNoRelayPath = 4,
    /**
     * @brief 没有加入房间
    */
    ByteRTCUserMessageSendResultNotJoin = 100,
    /**
     * @brief 没有调用init
    */
    ByteRTCUserMessageSendResultInit = 101,
    /**
     * @brief 没有可用的datachannel连接
    */
    ByteRTCUserMessageSendResultNoConnection = 102,
    /**
     * @brief 消息超过最大长度，当前为64KB
     */
    ByteRTCUserMessageSendResultExceedMaxLength = 103,
    /**
     * @brief 用户id为空
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
     * @brief 未知错误
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
     *        对端用户已经调用Logout，或者没有调用Login进行登录
     */
    ByteRTCUserOnlineStatusOffline = 0,
    /**
     * @brief 对端用户在线
     *        对端用户调用Login登录，并且连接状态正常
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
 * @brief 设置sdk的环境
*/
typedef NS_ENUM(NSInteger, ByteRTCEnv) {
    /**
     * @brief 线上环境
    */
    ByteRTCEnvProduct = 0,     ///<线上环境
    /**
     * @brief BOE环境
    */
    ByteRTCEnvBOE = 1,         ///<BOE环境
    /**
     * @brief 测试环境
    */
    ByteRTCEnvTest = 2,        ///<测试环境
};

/**
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
 * @brief 语音通话模式
 *         在小队语音里用这个接口设置自己的发送模式
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
     * @brief 上行网络较弱或性能不佳时，不对音视频流作回退处理，默认值
     */
    ByteRTCPublishFallbackOptionDisabled = 0,
    /**
     * @brief 上行网络较弱或性能不佳时，只发送视频小流。
     */
    ByteRTCPublishFallbackOptionSimulcast = 1,
};

/**
 * @type keytype
 * @brief 设置订阅的音视频流回退选项
*/
typedef NS_ENUM(NSUInteger, ByteRTCSubscribeFallbackOption) {
    /**
     * @brief 下行网络较弱时，不对音视频流作回退处理，默认值。
    */
    ByteRTCSubscribeFallbackOptionDisable = 0,
    /**
     * @brief 下行网络较弱时，只接收视频小流。
    */
    ByteRTCSubscribeFallbackOptionVideoStreamLow = 1,
    /**
     * @brief 下行网络较弱时，先尝试只接收视频小流；如果网络环境无法显示视频，则再回退到只接收远端订阅的音频流。
    */
    ByteRTCSubscribeFallbackOptionAudioOnly = 2,
};

/**
 * @hidden
 * @type keytype
 * @brief 背景模式
 *      开启背景替换功能时生效，详见 replaceBackground:withDivideModel:{@link #replaceBackground:withDivideModel:}。
 */
typedef NS_ENUM(NSUInteger, ByteRTCBackgroundMode) {
    /**
     *@brief 无
     */
    ByteRTCBackgroundModeNone = 0,
    /**
     *@brief 虚化
     */
    ByteRTCBackgroundModeBlur = 1,
    /**
     *@brief 背景1
     */
    ByteRTCBackgroundModeA = 2,
    /**
     *@brief 背景2
     */
    ByteRTCBackgroundModeB = 3,
};

/**
 * @hidden
 * @type keytype
 * @brief 分割模型
 *      开启背景替换功能时生效，详见 replaceBackground:withDivideModel:{@link #replaceBackground:withDivideModel:}。
 */
typedef NS_ENUM(NSUInteger, ByteRTCDivideModel) {
    /**
     *@brief 自研
     */
    ByteRTCDivideModelDefault = 0,
    /**
     *@brief effect
     */
    ByteRTCDivideModelEffect = 1,
};

/**
 * @type keytype
 * @brief 屏幕分享时共享对象的类型
 */
typedef NS_ENUM(NSUInteger, ByteRTCScreenCaptureSourceType) {
    /**
     *@brief 类型未知
     */
    ByteRTCScreenCaptureSourceTypeUnknown = 0,
    /**
     *@brief 应用程序的窗口
     */
    ByteRTCScreenCaptureSourceTypeWindow = 1,
    /**
     *@brief 桌面
     */
    ByteRTCScreenCaptureSourceTypeScreen = 2
};

#define BYTERTC_APPLE_EXPORT __attribute__((visibility("default")))
/**
 * @type keytype
 * @brief 视频渲染图层结构。app通过该结构将要渲染的窗口和视频流进行绑定
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVideoCanvas : NSObject
/**
 * @brief 渲染窗口句柄
 */
@property (strong, nonatomic) NSView* _Nullable view;
/**
 * @brief 设置渲染模式，暂时设置无效
 */
@property (assign, nonatomic) ByteRTCRenderMode renderMode;
/**
 * @brief 房间的RoomID
 */
@property (strong, nonatomic) NSString* _Nullable roomId;
/**
 * @brief 设置渲染流的用户标识
 */
@property (strong, nonatomic) NSString* _Nullable uid;
@end

/**
 * @type keytype
 * @brief 视频帧附加的数据,视频解码后获得的附加数据
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCFrameExtendedData : NSObject
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
 * @brief 视频流描述
*/
BYTERTC_APPLE_EXPORT @interface ByteRTCVideoStreamDescription: NSObject
/**
 * @brief 视频分辨率
*/
@property (nonatomic, assign) CGSize videoSize;
/**
 * @brief 视频预设帧率
*/
@property (nonatomic, assign) NSInteger frameRate;
/**
 * @brief 视频预设最大码率(Kbps)
*/
@property (nonatomic, assign) NSInteger maxKbps;
/**
 * @brief 视频伸展模式，详见类型 ByteRTCVideoStreamScaleMode{@link #ByteRTCVideoStreamScaleMode}
*/
@property (nonatomic, assign) ByteRTCVideoStreamScaleMode mode;
/**
 * @brief 视频编码质量偏好，详见类型 ByteRTCVideoEncoderPreference{@link #ByteRTCVideoEncoderPreference}
*/
@property (nonatomic, assign) ByteRTCVideoEncoderPreference encoderPreference;
@end

/**
 * @type keytype
 * @brief 音视频流属性
 *         发布到房间中的音视频流的流属性。用户加入房间成功后，房间中所有已发布和未来发布的音视频流和流的相关属性，都会通过
 *         rtcEngine:didStreamAdded:{@link #rtcEngine:didStreamAdded:} 回调通知用户。
 */
BYTERTC_APPLE_EXPORT @protocol ByteRTCStream <NSObject>
/**
 * @brief 发布此流的用户的 ID。
 */
@property (nonatomic, copy, readonly) NSString * userId;
/**
 * @brief 流是否为共享屏幕流。
 */
@property (nonatomic, assign, readonly) BOOL isScreen;
/**
 * @brief 流是否包括视频。
 */
@property (nonatomic, assign, readonly) BOOL hasVideo;
/**
 * @brief 流是否包括音频。
 */
@property (nonatomic, assign, readonly) BOOL hasAudio;
/**
 * @brief 视频流的分辨率信息，详见 ByteRTCVideoStreamDescription{@link #ByteRTCVideoStreamDescription} 类。
 *         用户可以通过调用 setVideoProfiles{@link #setVideoProfiles:} 方法在一路流中发布多个不同的视频分辨率。此参数即为流中
 *         所有分辨率的相关信息。
 */
@property (nonatomic, copy, readonly) NSArray<ByteRTCVideoStreamDescription *> * videoStreamDescriptions;
@end

NS_ASSUME_NONNULL_END

/**
 * @hidden
 * @type keytype
 * @brief RTC布局信息
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVideoCompositingRegion : NSObject
/**
 * @brief 用户ID
 */
@property (copy, nonatomic) NSString * _Nonnull uid;
/**
 * @brief 用户视频布局相对画布左侧的偏移量， 相对值。范围[0.0 - 1.0]
 */
@property (assign, nonatomic) CGFloat x;
/**
 * @brief 用户视频布局相对画布顶端的偏移量， 相对值。范围[0.0 - 1.0]
 */
@property (assign, nonatomic) CGFloat y;
/**
 * @brief 用户视频宽度相对用户原始视频宽度的比例，相对值。范围[0.0 - 1.0]
 */
@property (assign, nonatomic) CGFloat width;
/**
 * @brief 用户视频高度相对用户原始视频高度的比例，相对值。范围[0.0 - 1.0]
 */
@property (assign, nonatomic) CGFloat height;
/**
 * @brief 用户视频布局在画布中的层级，0为底层，值越大越上层。范围[0 - 100]
 */
@property (assign, nonatomic) NSInteger zOrder;
/**
 * @brief 透明度，范围[0 - 255]
 */
@property (assign, nonatomic) CGFloat alpha;
/**
 * @brief 推流内容控制。默认为0。
 *      0: 输出的混流包含音视频
 *      1: 只包含音频
 *      2: 表示只包含视频
 */
@property (assign, nonatomic) NSInteger contentControl;
/**
 * @brief 视频显示模式
 */
@property (assign, nonatomic) ByteRTCRenderMode renderMode;
@end

/**
 * @hidden
 * @type keytype
 * @brief 用户布局信息
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVideoCompositingLayout : NSObject
/**
 * @brief 背景颜色
 */
@property (copy, nonatomic) NSString *_Nonnull backgroundColor;
/**
 * @brief 用户布局信息列表
 */
@property (copy, nonatomic) NSArray<ByteRTCVideoCompositingRegion *> * _Nonnull regions;
/**
 * @brief 透传的app数据
 */
@property (copy, nonatomic) NSString *_Nonnull appData;
@end

/**
 * @hidden
 * @type keytype
 * @brief 视频参数
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCTranscodingVideoConfig : NSObject
/**
 * @brief 视频编码格式
 */
@property (copy, nonatomic) NSString * _Nonnull codec;
/**
 * @brief 合流视频宽度
 */
@property (assign, nonatomic) NSInteger width;
/**
 * @brief 合流视频高度
 */
@property (assign, nonatomic) NSInteger height;
/**
 * @brief 合流视频帧率信息
 */
@property (assign, nonatomic) NSInteger fps;
/**
 * @brief 视频I帧间隔
 */
@property (assign, nonatomic) NSInteger gop;
/**
 * @brief 合流视频码率(kbps)
 */
@property (assign, nonatomic) NSInteger bitRate;
/**
 * @brief 是否使用低延时特性
 */
@property (assign, nonatomic) BOOL lowLatency;
@end

/**
 * @type keytype
 * @brief AAC编码类型
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
 * @brief 编码类型
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoCodecType) {
    /**
     * @brief 视频编码类型：未知类型
     */
    ByteRTCVideoCodecTypeUnknown = 0,
    /**
     * @brief 视频编码类型：标准 H264
     */
    ByteRTCVideoCodecTypeH264 = 1,
    /**
     * @brief 视频编码类型：标准 ByteVC1
     */
    ByteRTCVideoCodecTypeByteVC1 = 2,
};

/**
 * @type keytype
 * @brief 编码类型
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoPictureType) {
    /**
     * @brief 视频编码类型：未知类型
     */
    ByteRTCVideoPictureTypeUnknown = 0,
    /**
     * @brief I帧，视频关键帧，编解码不需要参考其他视频帧
     */
    ByteRTCVideoPictureTypeI = 1,
    /**
     * @brief P帧，视频参考帧，编解码需要参考前一帧视频帧
     */
    ByteRTCVideoPictureTypeP = 2,
    /**
     * @brief B帧，视频参考帧，编解码需要参考两个视频帧
     */
    ByteRTCVideoPictureTypeB = 3
};

/**
 * @hidden
 * @type keytype
 * @brief 音频参数
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCTranscodingAudioConfig : NSObject
/**
 * @brief 音频编码格式
 */
@property (copy, nonatomic) NSString * _Nonnull codec;
/**
 * @brief 音频采样率；  16k, 32k, 44.1k, 48k
 */
@property (assign, nonatomic) NSInteger sampleRate;
/**
 * @brief 声道数
 */
@property (assign, nonatomic) NSInteger channels;
/**
 * @brief 音频码率(kbps); 16kbsp, 32kbps, 64kbps
 */
@property (assign, nonatomic) NSInteger bitRate;
/**
 * @brief AAC 等级
 */
@property (assign, nonatomic) ByteRTCAACProfile profile;
/**
 * @hidden
 */
+ (NSString* _Nonnull) toStringWithProfile:(ByteRTCAACProfile) aacProfile;
@end

/**
 * @hidden
 * @type keytype
 * @brief 转推直播参数
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCLiveTranscoding : NSObject
/**
 * @brief 用户布局信息
 */
@property (strong, nonatomic) ByteRTCVideoCompositingLayout * _Nonnull layout;
/**
 * @brief 视频参数
 */
@property (strong, nonatomic) ByteRTCTranscodingVideoConfig * _Nonnull video;
/**
 * @brief 音频参数
 */
@property (strong, nonatomic) ByteRTCTranscodingAudioConfig * _Nonnull audio;
/**
 * @brief 动态扩展自定义参数
 */
@property (strong, nonatomic) NSMutableDictionary *  _Nullable advancedConfig;
/**
 * @brief 转推直播地址
 */
@property (copy, nonatomic) NSString * _Nullable url;
/**
 * @brief 获取默认合流参数
 */
+ (instancetype _Nonnull)defaultTranscoding;
@end

/**
 * @type keytype
 * @brief 统计信息
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCRoomStats : NSObject
/**
 * @brief 用户在房间中的总时长(s)
 */
@property (assign, nonatomic) NSInteger duration;
/**
 * @brief 用户在通话过程中发送媒体数据总量(bytes)
 */
@property (assign, nonatomic) NSInteger txBytes;
/**
 * @brief 用户在通话过程中接收媒体数据总量(bytes)
 */
@property (assign, nonatomic) NSInteger rxBytes;
/**
 * @brief 当前总发送音频码率(kbps)
 */
@property (assign, nonatomic) NSInteger txAudioKBitrate;
/**
 * @brief 当前总接收音频码率(kbps)
 */
@property (assign, nonatomic) NSInteger rxAudioKBitrate;
/**
 * @brief 当前总发送视频码率(kbps)
 */
@property (assign, nonatomic) NSInteger txVideoKBitrate;
/**
 * @brief 当前总接收视频码率(kbps)
 */
@property (assign, nonatomic) NSInteger rxVideoKBitrate;
/**
 * @brief 往返时延，单位为毫秒
 */
@property (assign, nonatomic) NSInteger lastmileDelay;
/**
 * @brief 当前房间内用户总数
 */
@property (assign, nonatomic) NSInteger userCount;

@property (assign, nonatomic) float rxLostrate;
@property (assign, nonatomic) float txLostrate;
@property (assign, nonatomic) NSInteger rtt;
/**
 * @brief 当前 App 的 CPU 使用率
 */
@property (assign, nonatomic) double cpuAppUsage;
/**
 * @brief 当前设备的总 CPU 使用率
 */
@property (assign, nonatomic) double cpuTotalUsage;
@end

/**
 * @type keytype
 * @brief App使用的cpu和memory信息  <br>
 *        SDK 周期性（2s）的通过rtcEngine:reportSysStats:{@link
 * #ByteRTCEngineDelegate#rtcEngine:reportSysStats:}回调事件通知用户当前App的cpu与memory使用信息。回调的统计信息即为此数据类型。 <br>
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCSysStats : NSObject
/**
 * @brief 当前系统cpu核数
 */
@property (assign, nonatomic) unsigned int cpu_cores;

/**
 * @brief 当前App的CPU 使用率
 */
@property (assign, nonatomic) double cpu_app_usage;

/**
 * @brief 当前设备的总CPU使用率
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
 * @brief app 内存使用率（100%）
 */
@property (assign, nonatomic) double memory_ratio;

/**
 * @brief 系统内存使用率（100%）
 */
@property (assign, nonatomic) double total_memory_ratio;
@end

/**
 * @type keytype
 * @brief 本地视频流统计信息。  <br>
 *        本地用户发布视频流成功后，SDK 会周期性（2s）的通过 rtcEngine:localVideoStats:{@link #ByteRTCEngineDelegate#rtcEngine:localVideoStats:} 回调事件通知用户发布的视频流在此次统计周期内的状况。此数据结构即为回调给用户的参数类型。  <br>
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCLocalVideoStats : NSObject
/**
 * @brief 发送的码率。此次统计周期内的视频发送码率，单位为 kbps 。  <br>
 */
@property (assign, nonatomic) float sentKBitrate;
/**
 * @brief 输入帧率。此次统计周期内的本地视频输入帧率 。  <br>
 */
@property (assign, nonatomic) NSInteger inputFrameRate;
/**
 * @brief 发送帧率。此次统计周期内的本地视频发送帧率 。  <br>
 */
@property (assign, nonatomic) NSInteger sentFrameRate;
/**
 * @brief 本地视频目标编码帧率。  <br>
 */
@property (assign, nonatomic) NSInteger encoderOutputFrameRate;
/**
 * @brief 本地视频目标渲染输出帧率。  <br>
 */
@property (assign, nonatomic) NSInteger rendererOutputFrameRate;
/**
 * @brief 本地视频目标发送码率。单位为 kbps 。  <br>
 */
@property (assign, nonatomic) NSInteger sentTargetKBitrate;
/**
 * @brief 本地视频目标发送帧率。  <br>
 */
@property (assign, nonatomic) NSInteger sentTargetFrameRate;
/**
 * @brief 统计间隔。此次统计周期的间隔，单位为 ms 。  <br>
 */
@property (assign, nonatomic) NSInteger statsInterval;
/**
 * @brief 音频丢包率。统计周期内的视频上行丢包率，取值范围为 [0, 1] 。  <br>
 */
@property (assign, nonatomic) float videoLossRate;
/**
 * @brief 往返时延。单位为 ms 。  <br>
 */
@property (assign, nonatomic) NSInteger rtt;
/**
 * @brief 编码率。  <br>
 */
@property(assign, nonatomic) NSInteger encodedBitrate;
/**
 * @brief 编码帧宽度。  <br>
 */
@property(assign, nonatomic) NSInteger encodedFrameWidth;
/**
 * @brief 编码帧高度。  <br>
 */
@property(assign, nonatomic) NSInteger encodedFrameHeight;
/**
 * @brief 编码帧数。此次统计周期内编码的帧数。  <br>
 */
@property(assign, nonatomic) NSInteger encodedFrameCount;
/**
 * @brief 编码类型。详见 ByteRTCVideoCodecType{@link #ByteRTCVideoCodecType} 类型。  <br>
 */
@property(nonatomic) ByteRTCVideoCodecType codecType;
@end

/**
 * @type keytype
 * @brief 远端视频流统计信息。  <br>
 *         本地用户订阅远端视频流成功后，SDK 会周期性（2s）的通过 rtcEngine:remoteVideoStats:{@link #ByteRTCEngineDelegate#rtcEngine:remoteVideoStats:} 回调事件通知用户订阅的视频流在此次统计周期内的状况。此数据结构即为回调给用户的参数类型。  <br>
*/
BYTERTC_APPLE_EXPORT @interface ByteRTCRemoteVideoStats : NSObject
/**
 * @brief 用户ID 。远端视频流发布用户的用户ID 。  <br>
 */
@property (copy, nonatomic) NSString * _Nonnull uid;
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
 * @brief 远端视频流是否是屏幕共享流。  <br>
 */
@property (assign, nonatomic) BOOL isScreen;
/**
 * @brief 统计间隔。此次统计周期的间隔，单位为 ms 。  <br>
 */
@property (assign, nonatomic) NSInteger statsInterval;
/**
 * @brief 往返时延。单位为 ms 。  <br>
 */
@property (assign, nonatomic) NSInteger rtt;
/**
 * @brief 远端用户在加入房间后发生视频卡顿的累计时长占音频总有效时长的百分比。  <br>
 */
@property(assign, nonatomic) NSInteger frozenRate;
/**
 * @brief SDK 订阅的远端视频流的分辨率下标。  <br>
 */
@property (assign, nonatomic) NSInteger videoIndex;
@end

/**
 * @type keytype
 * @brief 本地音频流统计信息。  <br>
 *        本地用户发布音频流成功后，SDK 会周期性（2s）的通过 rtcEngine:localAudioStats:{@link #ByteRTCEngineDelegate#rtcEngine:localAudioStats:} 回调事件通知用户发布的音频流在此次统计周期内的状况。此数据结构即为回调给用户的参数类型。  <br>
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
 * @brief 采集采样率。音频采集采样率信息，单位为 Hz 。  <br>
 */
@property (assign, nonatomic) NSInteger recordSampleRate;
/**
 * @brief 统计间隔。此次统计周期的间隔，单位为 ms 。  <br>
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
 * @brief 发送采样率。音频发送采样率信息，单位为 Hz 。  <br>
 */
@property(assign, nonatomic) NSInteger sentSampleRate;
@end

/**
 * @type keytype
 * @brief 远端音频流统计信息。  <br>
 *        本地用户订阅远端音频流成功后，SDK 会周期性（2s）的通过 rtcEngine:remoteAudioStats:{@link #ByteRTCEngineDelegate#rtcEngine:remoteAudioStats:} 回调事件通知用户订阅的音频流在此次统计周期内的状况。此数据结构即为回调给用户的参数类型。  <br>
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCRemoteAudioStats : NSObject
/**
 * @brief 用户ID 。远端音频流发布用户的用户ID 。  <br>
 */
@property (copy, nonatomic) NSString * _Nonnull uid;
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
 * @brief 往返时延。单位为 ms 。  <br>
 */
@property (assign, nonatomic) NSInteger rtt;
/**
 * @brief 远端用户发送的音频流质量。值含义参考 ByteRTCNetworkQuality{@link #ByteRTCNetworkQuality} 。  <br>
 */
@property(assign, nonatomic) NSInteger quality;
/**
 * @brief 音频发送端到接收端的网络延迟。单位为 ms 。  <br>
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
 * @brief 远端用户在加入房间后发生音频卡顿的累计时长占音频总有效时长的百分比。  <br>
 */
@property(assign, nonatomic) NSInteger frozenRate;
/**
 * @brief 音频 PLC 样点总个数。  <br>
 */
@property(assign, nonatomic) NSInteger concealedSamples;
/**
 * @brief PLC 累计次数。  <br>
 */
@property(assign, nonatomic) NSInteger concealmentEvent;
/**
 * @brief 音频解码采样率。统计周期内的音频解码采样率信息，单位为 Hz 。  <br>
 */
@property(assign, nonatomic) NSInteger decSampleRate;
/**
 * @brief 解码时长。单位为 s 。  <br>
 */
@property(assign, nonatomic) NSInteger decDuration;
@end

/**
 * @type keytype
 * @brief 音量信息
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCAudioVolumeInfo : NSObject
/**
 * @brief 音量信息所属用户的用户 id
 */
@property (copy, nonatomic) NSString * _Nonnull uid;
/**
 * @brief 用户音量大小信息，音量取值范围为 [0, 255]
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
 * @type api
 * @brief 视频外部渲染接口
 */
BYTERTC_APPLE_EXPORT @protocol ByteRTCVideoSinkProtocol <NSObject>
@required
/**
 * @type api
 * @brief 通知外部渲染器实现，当前需要进行渲染器初始化工作
 */
- (BOOL)shouldInitialize;
/**
 * @type api
 * @brief 通知外部渲染器实现，当前需要准备开始渲染
 */
- (void)shouldStart;
/**
 * @type api
 * @brief 通知外部渲染器实现，当前需要准备停止渲染
 */
- (void)shouldStop;
/**
 * @type api
 * @brief 通知外部渲染器实现，当前需要进行渲染器销毁工作
 */
- (void)shouldDispose;
/**
 * @type api
 * @brief 指定外部渲染器接收的视频帧格式类型
 * @return 指定的返回格式类型，类型含义详见 ByteRTCVideoSinkPixelFormat{@link #ByteRTCVideoSinkPixelFormat}
 */
- (ByteRTCVideoSinkPixelFormat)pixelFormat;
/**
 * @type api
 * @brief 外部渲染视频帧数据回调接口
 * @param pixelBuffer 视频帧数据
 * @param rotation 视频帧的旋转角度 关于枚举，详见 ByteRTCVideoRotation{@link #ByteRTCVideoRotation}
 * @param extendedData 视频帧所携带的额外SEI数据
 */
- (void)renderPixelBuffer:(CVPixelBufferRef _Nonnull)pixelBuffer
                 rotation:(ByteRTCVideoRotation)rotation
             extendedData:(NSData * _Nullable)extendedData;
@end

/**
 * @hidden
 * @type keytype
 * @brief 流信息
*/
@interface ByteRTCStreamEx : NSObject <ByteRTCStream>
/**
 * @brief 发布该流的用户的用户ID
*/
@property (nonatomic, copy, nullable) NSString *userId;
/**
 * @brief 该流是否为屏幕流
*/
@property (nonatomic, assign) BOOL isScreen;
/**
 * @brief 该流是否有视频
*/
@property (nonatomic, assign) BOOL hasVideo;
/**
 * @brief 该流是否有音频
*/
@property (nonatomic, assign) BOOL hasAudio;
/**
 * @brief 视频流描述信息，详见类型VideoStreamDescription{@link #ByteRTCVideoStreamDescription}
*/
@property (nonatomic, copy, nullable) NSArray<ByteRTCVideoStreamDescription *> *videoStreamDescriptions;
@end


/**
 * @type keytype
 * @brief 视频缩放模式
*/
typedef NS_ENUM(NSInteger, ByteRTCVideoScaleMode){
    /**
     * @brief 自动缩放模式，当前等价于FitWithCropping
    */
    ByteRTCVideoScaleModeAuto = 0,
    
    /**
     * @brief 缩放以适配宽高比
    */
    ByteRTCVideoScaleModeStretch = 1,
    
    /**
     * @brief 保持纵横比来缩放图像，裁剪长边
    */
    ByteRTCVideoScaleModeFitWithCropping = 2,
    
    /**
     * @brief 保持纵横比来缩放图像，填充短边
    */
    ByteRTCVideoScaleModeFitWithFilling = 3,
};

/**
 * @type keytype
 * @brief 视频属性
*/
BYTERTC_APPLE_EXPORT @interface ByteRTCVideoSolution : NSObject
/**
 * @brief 视频宽度
*/
@property (assign, nonatomic) NSInteger width;
/**
 * @brief 视频高度
*/
@property (assign, nonatomic) NSInteger height;
/**
 * @brief 视频预设帧率
*/
@property (assign, nonatomic) NSInteger frameRate;
/**
 * @brief 视频预设最大码率(Kbps)
*/
@property (assign, nonatomic) NSInteger maxKbps;
/**
 * @brief 视频伸展模式，详见类型 ByteRTCVideoScaleMode{@link #ByteRTCVideoScaleMode}
*/
@property (assign, nonatomic) ByteRTCVideoScaleMode scaleMode;
/**
 * @brief 视频编码质量偏好，详见类型 ByteRTCVideoEncoderPreference{@link #ByteRTCVideoEncoderPreference}
*/
@property (assign, nonatomic) ByteRTCVideoEncoderPreference encoderPreference;
@end

/**
 * @type keytype
 * @brief 音视频流属性
 *         发布到房间中的音视频流的流属性。用户加入房间成功后，房间中所有已发布和未来发布的音视频流和流的相关属性，都会通过
 *         rtcEngine:didStreamAdded:{@link #rtcEngine:didStreamAdded:} 回调通知用户。
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCStreamInfo : NSObject
/**
 * @brief 发布此流的用户的 ID。
 */
@property (copy, nonatomic) NSString * _Nonnull uid;
/**
 * @brief 流是否为共享屏幕流。
 */
@property (assign, nonatomic) BOOL isScreen;
/**
 * @brief 流是否包括视频。
 */
@property (assign, nonatomic) BOOL hasVideo;
/**
 * @brief 流是否包括音频。
 */
@property (assign, nonatomic) BOOL hasAudio;
/**
 * @brief 视频流的分辨率信息，详见 ByteRTCVideoSolution{@link #ByteRTCVideoSolution} 类。
 *         用户可以通过调用 setVideoProfiles{@link #setVideoProfiles:} 方法在一路流中发布多个不同的视频分辨率。此参数即为流中
 *         所有分辨率的相关信息。
 */
@property (copy, nonatomic) NSArray<ByteRTCVideoSolution *> * _Nullable streamProfiles;
@end

/**
 * @type keytype
 * @brief 订阅流配置参数。
 *         用户调用 subscribeStream:info:{@link #subscribeStream:info:} 方法手动订阅音视频流或更新订阅参数时，传入订阅流配置参数。
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCSubscribeConfig : NSObject
/**
 * @brief 订阅的流是否是屏幕共享流。
 */
@property (assign, nonatomic) BOOL isScreen;
/**
 * @brief 是否订阅视频。
 */
@property (assign, nonatomic) BOOL subVideo;
/**
 * @brief 是否订阅音频。
 */
@property (assign, nonatomic) BOOL subAudio;
/**
 * @brief 订阅的视频流分辨率索引号。
 *         视频流中含多个分辨率的情况下，标识订阅第几个的视频分辨率。如果视频流中仅含一个分辨率，则为0。
 */
@property (assign, nonatomic) NSInteger videoIndex;
@end

/**
 * @type keytype
 * @brief 音频帧类型
*/
typedef NS_ENUM(NSInteger, ByteRTCAudioFrameType) {
    /**
     * @brief PCM16
    */
    ByteRTCAudioFrameTypePCM16 = 0, //PCM 16bit little endian
};

/**
 * @type keytype
 * @brief 性能回退或者恢复的原因
 */
typedef NS_ENUM(NSInteger, ByteRTCPerformanceAlarmReason) {
    /*
     * 因为网络原因回退 仅开启simulcast 模式 回调中包含此原因
     */
    ByteRTCPerformanceAlarmReasonBandwidthFallback = 0,
    /**
     * 因为网络原因恢复 仅开启simulcast 模式 回调中包含此原因
     */
    ByteRTCPerformanceAlarmReasonBandwidthResumed = 1,
    /*
     * 因为性能不足回退
     */
    ByteRTCPerformanceAlarmReasonFallback = 2,
    /**
     * 因为性能原因恢复
     */
    ByteRTCPerformanceAlarmReasonResumed = 3,
};

/**
 * @type keytype
 * @brief 性能回退的模式
 */
typedef NS_ENUM(NSInteger, ByteRTCPerformanceAlarmMode) {
    /**
     * 性能回退以及恢复，正常模式，只包括性能原因，通知需要外部采集的用户更新版采集的分辨率、帧率
     */
    ByteRTCPerformanceAlarmModeNormal = 0,
    /**
     * 性能回退以及恢复，大小流模式，包含性能原因以及网络原因，此模式仅为通知双流模式状态变
     */
    ByteRTCPerformanceAlarmModeSimulcast = 1,
};

/**
 * @type keytype
 * @brief 视频帧类型
*/
typedef NS_ENUM(NSInteger, ByteRTCVideoFrameType) {
    /**
     * @brief unknown
     */
    FRAME_TYPE_UNKNOWN,
    /**
     * @brief ARGB image
     */
    FRAME_TYPE_ARGB,
    /**
     * @brief BGRA image
     */
    FRAME_TYPE_BGRA,
    /**
     * @brief RGBA image
     */
    FRAME_TYPE_RGBA,
    /**
     * @brief YUV image with i420 layout, also known as yuv420p
     */
    FRAME_TYPE_I420,
    /**
     * @brief YUV image with NV12 layout
     */
    FRAME_TYPE_NV12,
    /**
     * @brief YUV image with NV21 layout
     */
    FRAME_TYPE_NV21,
    /**
     * @brief 24 bit RGB image
     */
    FRAME_TYPE_RGB24,
};

/**
 * @type keytype
 * @brief 问题反馈列表
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
     * @brief 无法连接
     */
    ByteRTCProblemFeedbackOptionConnectionFailed = (1 << 6),
    /**
     * @brief 音频延迟
     */
    ByteRTCProblemFeedbackOptionAudioDelay = (1 << 7),
    /**
     * @brief 视频延迟
     */
    ByteRTCProblemFeedbackOptionVideoDelay = (1 << 8),
    /**
     * @brief 连接断开
     */
    ByteRTCProblemFeedbackOptionDisconnected = (1 << 9),
    /**
     * @brief 无声音
     */
    ByteRTCProblemFeedbackOptionNoAudio = (1 << 10),
    /**
     * @brief 无画面
     */
    ByteRTCProblemFeedbackOptionNoVideo = (1 << 11),
    /**
     * @brief 声音过大或过小
     */
    ByteRTCProblemFeedbackOptionAudioStrength = (1 << 12),
    /**
     * @brief 回声噪音
     */
    ByteRTCProblemFeedbackOptionEcho = (1 << 13),
};

/**
 * @type keytype
 * @region 加密
 * @brief 加密类型
*/
typedef NS_OPTIONS(NSUInteger, ByteRTCEncryptType) {
    /**
     * @brief 使用自定义加密或不加密  <br>
     */
    ByteRTCEncryptTypeCustomize = 0,
    /**
     * @brief 使用AES-128-CBC进行传输加密  <br>
    */
    ByteRTCEncryptTypeAES128CBC = 1,
    /**
     * @brief 使用AES-256-CBC进行传输加密  <br>
    */
    ByteRTCEncryptTypeAES256CBC = 2,
    /**
     * @brief 使用AES-128-ECB进行传输加密  <br>
    */
    ByteRTCEncryptTypeAES128ECB = 3,
    /**
     * @brief 使用AES-256-ECB进行传输加密  <br>
    */
    ByteRTCEncryptTypeAES256ECB = 4
};

/**
 * @type keytype
 * @brief 音频帧数据
*/
BYTERTC_APPLE_EXPORT @interface ByteRTCAudioFrameData : NSObject
/**
 * @brief 音频帧类型。详见类型 ByteRTCAudioFrameType{@link #ByteRTCAudioFrameType}
*/
@property (assign, nonatomic) ByteRTCAudioFrameType type;
/**
 * @brief 音频帧时间戳
*/
@property (assign, nonatomic) SInt64 timestampMs; // time for this frame.
/**
 * @brief 每个声道音频帧的采样数
*/
@property (assign, nonatomic) int samples; //number of audio samples (per channel) described by this frame
/**
 * @brief 音频声道数
*/
@property (assign, nonatomic) int channels; //number of channels
/**
 * @brief 音频数据的采样率
*/
@property (assign, nonatomic) int sampleRate; //Sample rate of the audio data
/**
 * @brief 数据缓冲
*/
@property (assign, nonatomic) UInt8 * _Nonnull buffer; //data buffer
@end

/**
 * @type keytype
 * @brief 视频帧数据
*/
BYTERTC_APPLE_EXPORT @interface ByteRTCVideoFrame : NSObject
/**
 * @brief 视频帧类型。详见类型 ByteRTCVideoFrameType{@link #ByteRTCVideoFrameType}
*/
@property (assign, nonatomic) ByteRTCVideoFrameType type;
/**
 * @brief 视频帧时间戳
*/
@property (assign, nonatomic) SInt64 timestampMs; // time for this frame.
/**
 * @brief 视频帧宽
*/
@property (assign, nonatomic) int width; //width of video frame
/**
 * @brief 视频帧高
*/
@property (assign, nonatomic) int height; //height of video frame
/**
 * @brief 视频帧y分量stride
*/
@property (assign, nonatomic) int yStride; //stride of Y data buffer
/**
 * @brief 视频帧u分量stride
*/
@property (assign, nonatomic) int uStride; //stride of U data buffer
/**
 * @brief 视频帧v分量stride
*/
@property (assign, nonatomic) int vStride; //stride of V data buffer
/**
 * @brief 视频帧y分量数据缓冲
*/
@property (assign, nonatomic) UInt8 * _Nonnull yBuffer; //Y data buffer
/**
 * @brief 视频帧u分量数据缓冲
*/
@property (assign, nonatomic) UInt8 * _Nonnull uBuffer; //U data buffer
/**
 * @brief 视频帧v分量数据缓冲
*/
@property (assign, nonatomic) UInt8 * _Nonnull vBuffer; //V data buffer
/**
 * @brief 视频帧选择度数
*/
@property (assign, nonatomic) int rotation;   // 0, 90, 180, 270. See document for rotation calculation
@end

/**
 * @type keytype
 * @brief 压缩视频帧数据
*/
BYTERTC_APPLE_EXPORT @interface ByteRTCEncodedVideoFrame : NSObject
/**
 * @brief 视频编码类型。详见类型 ByteRTCVideoCodecType{@link #ByteRTCVideoCodecType}
*/
@property (assign, nonatomic) ByteRTCVideoCodecType codecType;

/**
 * @brief 编码视频帧类型。详见类型 ByteRTCVideoPictureType{@link #ByteRTCVideoPictureType}
*/
@property (assign, nonatomic) ByteRTCVideoPictureType pictureType;

/**
 * @brief 视频采集时间戳
*/
@property (assign, nonatomic) SInt64 timestampUs; // time for this frame.
/**
 * @brief 视频显示时间戳
 */
@property (assign, nonatomic) SInt64 timestampPts; // pts time for this frame.
/**
 * @brief 视频解码时间戳
 */
@property (assign, nonatomic) SInt64 timestampDts; // dts time for this frame.
/**
 * @brief 时间基分子
 */
@property (assign, nonatomic) int timebaseNum;
/**
 * @brief 时间基分母
 */
@property (assign, nonatomic) int timebaseDen;
/**
 * @brief 视频帧宽
*/
@property (assign, nonatomic) int width; //width of video frame
/**
 * @brief 视频帧高
*/
@property (assign, nonatomic) int height; //height of video frame
/**
 * @brief 视频帧选择度数
*/
@property (assign, nonatomic) int rotation;   // 0, 90, 180, 270. See document for rotation calculation
/**
 * @brief 视频数据指针地址
*/
@property (strong, nonatomic) NSData * _Nonnull data; // data buffer
@end

/**
 * @type keytype
 * @brief 包信息
*/
BYTERTC_APPLE_EXPORT @interface ByteRTCPacket : NSObject
/**
 * @brief 数据缓存大小
*/
@property (assign, nonatomic) UInt size; //size of buffer
/**
 * @brief 包数据缓存地址
*/
@property (assign, nonatomic) const UInt8 * _Nonnull buffer; //data buffer
@end

/**
 * @type keytype
 * @brief 用户信息。  <br>
 *         用户调用 joinRoomByToken:{@link #ByteRTCEngineKit#joinRoomByKey:} 加入房间的时候传入，传入用户信息的参数。  <br>
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCUserInfo : NSObject
/**
 * @brief 用户ID
 */
@property (copy, nonatomic) NSString *_Nonnull userId;
/**
 * @brief 用户需要透传的额外的信息，字符长度限制为200字节
 */
@property (copy, nonatomic) NSString *_Nonnull extraInfo;
@end

/**
 * @type keytype
 * @brief 屏幕分享时的高亮边框
*/
BYTERTC_APPLE_EXPORT @interface ByteRTCHighlightConfig: NSObject

/**
 * @brief 是否显示高亮边框
 * 推荐值 YES
 */
@property (assign, nonatomic) BOOL enableHighlight;
/**
 * @brief 边框的颜色, 颜色格式为十六进制 ARGB:  0xAARRGGBB
 * 推荐值 0xFF29CCA3
 */
@property (assign, nonatomic) uint32_t borderColor;
/**
 * @brief 边框的宽度
 * 推荐值 4
 */
@property (assign, nonatomic) int borderWidth;

@end

/**
 * @type keytype
 * @brief 屏幕共享的编码参数配置
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCScreenCaptureParameters : NSObject

/**
 * @brief 屏幕采集编码最大宽度
 */
@property (assign, nonatomic) int maxWidth;
/**
 * @brief 屏幕采集编码最大高度
 */
@property (assign, nonatomic) int maxHeight;
/**
 * @brief 屏幕采集编码帧率, 单位 fps
 */
@property (assign, nonatomic) int frameRate;
/**
 * @brief 屏幕采集编码码率, -1 为自动码率, SDK 会根据宽高信息选择合适的码率，单位 kbps
 */
@property (assign, nonatomic) int bitrate;
/**
 * @brief 是否捕获鼠标光标
 */
@property (assign, nonatomic) BOOL captureMouseCursor;
/**
 * @brief 抓取屏幕时排除窗口列表。这个参数仅在抓取屏幕时生效。
 */
@property (strong, nonatomic) NSArray<NSNumber *> * _Nullable excludedWindowList;
/**
 * @brief 高亮边框的配置
 */
@property (strong, nonatomic) ByteRTCHighlightConfig * _Nonnull highlightConfig;

@end

/**
 * @type keytype
 * @brief 屏幕分享时共享对象的信息
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCScreenCaptureSourceInfo : NSObject
/**
 * @brief 屏幕分享时共享对象的类型。
 */
@property (assign, nonatomic) ByteRTCScreenCaptureSourceType sourceType;
/**
 * @brief 屏幕分享时共享对象的 ID。
 */
@property (assign, nonatomic) intptr_t sourceId;
/**
 * @brief 屏幕分享时共享对象的名称。
 */
@property (copy, nonatomic) NSString * _Nullable sourceName;

@end

/**
 * @type keytype
 * @brief 静音状态
 */
typedef NS_ENUM(NSInteger, ByteRTCMuteState) {
    /**
     * @brief 关闭静音
     */
    ByteRTCMuteStateOff = 0,
    /**
     * @brief 开启静音
     */
    ByteRTCMuteStateOn = 1,
};

/**
 * @type keytype
 * @brief 流属性
 */
typedef NS_ENUM(NSInteger, ByteRTCStreamIndex) {
    /**
     * @brief 主流，默认是麦克风和摄像头内容
     */
    ByteRTCStreamIndexMain = 0,
    /**
     * @brief 屏幕流，默认是屏幕采集的视频，后续会添加屏幕共享音频
     */
    ByteRTCStreamIndexScreen = 1
};

/**
 * @type keytype
 * @region 房间管理
 * @brief 用户信息
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCRemoteStreamKey : NSObject
/**
 * @brief 用户 id
 */
@property (nonatomic, copy, nullable) NSString *userId;
/**
 * @brief 房间 id
 */
@property (nonatomic, copy, nullable) NSString *roomId;
/**
 * @brief 流类型索引，包括主流、屏幕流
 */
@property (nonatomic, assign) ByteRTCStreamIndex streamIndex;
@end

/**
 * @type keytype
 * @brief 音频采样率
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioSampleRate) {
    /**
     * @brief 8000 采样率
     */
    ByteRTCAudioSampleRate8000 = 8000,
    /**
     * @brief 16000 采样率
     */
    ByteRTCAudioSampleRate16000 = 16000,
    /**
     * @brief 32000 采样率
     */
    ByteRTCAudioSampleRate32000 = 32000,
    /**
     * @brief 44100 采样率
     */
    ByteRTCAudioSampleRate44100 = 44100,
    /**
     * @brief 48000 采样率
     */
    ByteRTCAudioSampleRate48000 = 48000
};

/**
 * @type keytype
 * @brief 音频声道
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioChannel) {
    /**
     * @brief 单声道
    */
    ByteRTCAudioChannelMono = 1,
    /**
     * @brief 双声道
    */
    ByteRTCAudioChannelStereo = 2
};
/**
 * @type keytype
 * @brief 音频设备类型
 *        音频设备变化时 SDK 通过 rtcEngine:onAudioPlaybackDeviceChanged:{@link #rtcEngine:onAudioPlaybackDeviceChanged:} 回调该错误码
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
};

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
 * @brief 音频帧
*/
BYTERTC_APPLE_EXPORT @interface ByteRTCAudioFrame : NSObject
/**
 * @brief 音频帧数据
*/
@property (strong, nonatomic) NSData * _Nonnull buffer;
/**
 * @brief 此音频帧描述的样点数
*/
@property (assign, nonatomic) int samples;
/**
 * @brief 音频声道，详见 ByteRTCAudioChannel{@link #ByteRTCAudioChannel}
*/
@property (assign, nonatomic) ByteRTCAudioChannel channel;
/**
 * @brief 音频采样率，详见 ByteRTCAudioSampleRate{@link #ByteRTCAudioSampleRate}
*/
@property (assign, nonatomic) ByteRTCAudioSampleRate sampleRate;
@end

/**
 * @type keytype
 * @brief 本地音频流状态。
 *        SDK 通过 rtcEngine:localAudioStateChanged:error:{@link #rtcEngine:localAudioStateChanged:error:} 回调本地音频流状态
 */
typedef NS_ENUM(NSInteger, ByteRTCLocalAudioStreamState) {
    /**
    * @brief 本地音频默认初始状态。
    *        麦克风停止工作时回调该状态，对应错误码 ByteRTCLocalAudioStreamErrorOk{@link #ByteRTCLocalAudioStreamErrorOk}
    */
    ByteRTCLocalAudioStreamStateStopped = 0,

    /**
    * @brief 本地音频录制设备启动成功。
    *        采集到音频首帧时回调该状态，对应错误码 ByteRTCLocalAudioStreamErrorOk{@link #ByteRTCLocalAudioStreamErrorOk}
    */
    ByteRTCLocalAudioStreamStateRecording = 1,

    /**
    * @brief 本地音频首帧编码成功。
    *        音频首帧编码成功时回调该状态，对应错误码 ByteRTCLocalAudioStreamErrorOk{@link #ByteRTCLocalAudioStreamErrorOk}
    */
    ByteRTCLocalAudioStreamStateEncoding = 2,

    /**
    * @brief  本地音频启动失败，在以下时机回调该状态：  <br>
    *       + 本地录音设备启动失败，对应错误码 ByteRTCLocalAudioStreamErrorRecordFailure{@link #ByteRTCLocalAudioStreamErrorRecordFailure}  <br>
    *       + 检测到没有录音设备权限，对应错误码 ByteRTCLocalAudioStreamErrorDeviceNoPermission{@link #ByteRTCLocalAudioStreamErrorDeviceNoPermission}  <br>
    *       + 音频编码失败，对应错误码 ByteRTCLocalAudioStreamError{@link #ByteRTCLocalAudioStreamError}  <br>
    */
    ByteRTCLocalAudioStreamStateFailed = 3,
};

/**
 * @type keytype
 * @brief 本地音频流状态改变时的错误码
 *        SDK 通过 rtcEngine:localAudioStateChanged:error:{@link #rtcEngine:localAudioStateChanged:error:} 回调该错误码
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
 * @brief 远端音频流状态
 *        SDK 通过 rtcEngine:remoteAudioStateChanged:state:reason:elapsed:{@link #rtcEngine:remoteAudioStateChanged:state:reason:elapsed:} 回调该状态
 */
typedef NS_ENUM(NSInteger, ByteRTCRemoteAudioState) {
    /**
     * @brief  远端音频流默认初始状态，在以下时机回调该状态：  <br>
     *       + 本地用户停止接收远端音频流，对应错误码 ByteRTCRemoteAudioReasonLocalMuted{@link #ByteRTCRemoteAudioReasonLocalMuted}  <br>
     *       + 远端用户停止发送音频流，对应错误码 ByteRTCRemoteAudioReasonRemoteMuted{@link #ByteRTCRemoteAudioReasonRemoteMuted}  <br>
     *       + 远端用户离开房间，对应错误码 ByteRTCRemoteAudioReasonRemoteOffline{@link #ByteRTCRemoteAudioReasonRemoteOffline}  <br>
     */
    ByteRTCRemoteAudioStateStopped = 0,

    /**
     * @brief 本地用户已接收远端音频首包。
     *        收到远端音频首包时回调该状态，对应错误码 ByteRTCRemoteAudioReasonLocalUnmuted{@link #ByteRTCRemoteAudioReasonLocalUnmuted}
     */
    ByteRTCRemoteAudioStateStarting = 1,

    /**
     * @brief  远端音频流正在解码，正常播放，在以下时机回调该状态：  <br>
     *       + 成功解码远端音频首帧，对应错误码 ByteRTCRemoteAudioReasonLocalUnmuted{@link #ByteRTCRemoteAudioReasonLocalUnmuted}  <br>
     *       + 网络由阻塞恢复正常，对应错误码 ByteRTCRemoteAudioReasonNetworkRecovery{@link #ByteRTCRemoteAudioReasonNetworkRecovery}  <br>
     *       + 本地用户恢复接收远端音频流，对应错误码 ByteRTCRemoteAudioReasonLocalUnmuted{@link #ByteRTCRemoteAudioReasonLocalUnmuted}  <br>
     *       + 远端用户恢复发送音频流，对应错误码 ByteRTCRemoteAudioReasonRemoteUnmuted{@link #ByteRTCRemoteAudioReasonRemoteUnmuted}  <br>
     */
    ByteRTCRemoteAudioStateDecoding = 2,

    /**
     * @brief 远端视频流卡顿。
     *        网络阻塞、丢包率大于40%时回调该状态，对应错误码 ByteRTCRemoteAudioReasonNetworkCongestion{@link #ByteRTCRemoteAudioReasonNetworkCongestion}
     */
    ByteRTCRemoteAudioStateFrozen = 3,

    /**
     * @brief 远端视频流播放失败
     * @notes 该错误码暂未使用
     */
    ByteRTCRemoteAudioStateFailed = 4,
};

/**
 * @type keytype
 * @brief 远端音频流状态改变的原因。
 *        SDK 通过 rtcEngine:remoteAudioStateChanged:state:reason:elapsed:{@link #rtcEngine:remoteAudioStateChanged:state:reason:elapsed:} 回调该错误码
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
 * @brief 流统计信息以及网络质量  <br>
 *        SDK 周期性（2s）的通过rtcEngine:onLocalStreamStats:{@link
 * #ByteRTCEngineDelegate#rtcEngine::onLocalStreamStats:}回调事件通知用户本地流信息以及网络质量。回调的统计信息即为此数据类型。 <br>
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCLocalStreamStats : NSObject
/**
 * @brief 本地音频流统计信息
 */
@property (strong, nonatomic) ByteRTCLocalAudioStats *_Nonnull audio_stats;
/**
 * @brief 本地音频流统计信息
 */
@property (strong, nonatomic) ByteRTCLocalVideoStats *_Nonnull video_stats;
/**
 * @brief 所属用户的媒体流上行网络质量
 */
@property (assign, nonatomic) ByteRTCNetworkQuality tx_quality;
/**
 * @brief 所属用户的媒体流下行网络质量
 */
@property (assign, nonatomic) ByteRTCNetworkQuality rx_quality;
/**
 * @brief 所属用户的媒体流是否为屏幕流
 */
@property (nonatomic, assign) BOOL is_screen;

@end

/**
 * @type keytype
 * @brief 流统计信息以及网络质量  <br>
 *        SDK 周期性（2s）的通过rtcEngine:onRemoteStreamStats:{@link
 * #ByteRTCEngineDelegate#rtcEngine::onRemoteStreamStats:}回调事件通知用户当前该路远端流的流信息以及网络质量。回调的统计信息即为此数据类型。 <br>
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCRemoteStreamStats : NSObject
/**
 * @brief 用户ID 。远端发布用户的用户ID 。  <br>
 */
@property (copy, nonatomic) NSString *_Nonnull uid;
/**
 * @brief 本地音频流统计信息
 */
@property (strong, nonatomic) ByteRTCRemoteAudioStats *_Nonnull audio_stats;
/**
 * @brief 本地音频流统计信息
 */
@property (strong, nonatomic) ByteRTCRemoteVideoStats *_Nonnull video_stats;
/**
 * @brief 所属用户的媒体流上行网络质量
 */
@property (assign, nonatomic) ByteRTCNetworkQuality tx_quality;
/**
 * @brief 所属用户的媒体流下行网络质量
 */
@property (assign, nonatomic) ByteRTCNetworkQuality rx_quality;
/**
 * @brief 所属用户的媒体流是否为屏幕流
 */
@property (nonatomic, assign) BOOL is_screen;

@end
