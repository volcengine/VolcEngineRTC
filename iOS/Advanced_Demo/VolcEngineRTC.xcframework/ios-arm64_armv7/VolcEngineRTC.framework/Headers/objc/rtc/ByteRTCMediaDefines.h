/*
 * Copyright (c) 2022 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief Objective-C VolcEngineRTC Common Defines
*/

#import "ByteRTCRtsDefines.h"
/** 
 * @type keytype
 * @brief 方法调用结果。
 */
typedef NS_ENUM(NSInteger, ByteRTCReturnStatus) {
    /** 
     * @brief 成功。
     */
    ByteRTCReturnStatusSuccess = 0,
    /** 
     * @brief 失败。
     */
    ByteRTCReturnStatusFailure = -1,
    /** 
     * @brief 参数错误。
     */
    ByteRTCReturnStatusParameterErr = -2,
    /** 
     * @brief 接口状态错误。
     */
    ByteRTCReturnStatusWrongState = -3,
    /** 
     * @brief 失败，用户已在房间内。
     */
    ByteRTCReturnStatusHasInRoom = -4,
    /** 
     * @brief 失败，用户已登录。
     */
    ByteRTCReturnStatusHasInLogin = -5,
    /** 
     * @brief 失败，用户已经在进行通话回路测试中。
     */
    ByteRTCReturnStatusHasInEchoTest = -6,
    /** 
     * @brief 失败，音视频均未采集。
     */
    ByteRTCReturnStatusNeitherVideoNorAudio = -7,
    /** 
     * @brief 失败，该 roomId 已被使用。
     */
    ByteRTCReturnStatusRoomIdInUse = -8,
    /** 
     * @brief 失败，屏幕流不支持。
     */
    ByteRTCReturnStatusScreenNotSupport = -9,
    /** 
     * @brief 失败，没有音频帧。
     */
    ByteRTCReturnStatusAudioNoFrame = -101,
    /** 
     * @brief 失败，未实现。
     */
    ByteRTCReturnStatusAudioNotImplemented = -102,
    /** 
     * @brief 失败，采集设备无麦克风权限，尝试初始化设备失败。
     */
    ByteRTCReturnStatusAudioNoPermission = -103,
    /** 
     * @brief 失败，设备不存在。当前没有设备或设备被移除时返回该值。
     */
    ByteRTCReturnStatusAudioDeviceNotExists = -104,
    /** 
     * @brief 失败，设备音频格式不支持。
     */
    ByteRTCReturnStatusAudioDeviceFormatNotSupport = -105,
    /** 
     * @brief 失败，系统无可用设备。
     */
    ByteRTCReturnStatusAudioDeviceNoDevice = -106,
    /** 
     * @brief 失败，当前设备不可用，需更换设备。
     */
    ByteRTCReturnStatusAudioDeviceCannotUse = -107,
    /** 
     * @brief 系统错误，设备初始化失败。
     */
    ByteRTCReturnStatusAudioDeviceInitFailed = -108,
    /** 
     * @brief 系统错误，设备开启失败。
     */
    ByteRTCReturnStatusAudioDeviceStartFailed = -109,
    /** 
     * @brief 失败。底层未初始化，engine 无效。
     */
    ByteRTCReturnStatusNativeInValid = -201,
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
    /** 
     * @brief 远端用户 Token 发布权限过期。
     */
    ByteRTCStreamRemoveReasonPublishPrivilegeExpired = 6,
};

/** 
 * @type keytype
 * @brief 房间模式<br>
 *        根据所需场景，选择合适的房间模式，应用不同的音视频算法、视频参数和网络配置 <br>
 *        调用 `setAudioProfile` 改变音频参数配置
 */
typedef NS_ENUM(NSInteger, ByteRTCRoomProfile) {
    /** 
     * @brief 默认场景，通用模式<br>
     *        与 `ByteRTCRoomProfileMeeting = 16` 配置相同。
     */
    ByteRTCRoomProfileCommunication = 0,
    /** 
     * @deprecated since 3.42 and will be deleted in 3.51, use ByteRTCRoomProfileInteractivePodcast instead.
     * @brief 直播模式。<br>
     *        当你对音视频通话的音质和画质要求较高时，应使用此设置。<br>
     *        此设置下，当用户使用蓝牙耳机收听时，蓝牙耳机使用媒体模式。
     */
    ByteRTCRoomProfileLiveBroadcasting = 1,
    /** 
     * @brief 游戏语音模式，低功耗、低流量消耗。<br>
     *        低端机在此模式下运行时，进行了额外的性能优化：<br>
     *            + 部分低端机型配置编码帧长 40/60 <br>
     *            + 部分低端机型关闭软件 3A 音频处理 <br>
     *        增强对 iOS 其他屏幕录制进行的兼容性，避免音频录制被 RTC 打断。
     */
    ByteRTCRoomProfileGame = 2,
    /** 
     * @brief 云游戏模式。<br>
     *        如果你的游戏场景需要低延迟的配置，使用此设置。<br>
     *        此设置下，弱网抗性较差。
     */
    ByteRTCRoomProfileCloudGame = 3,
    /** 
     * @brief 云渲染模式。超低延时配置。  <br>
     *        如果你的应用并非游戏但又对延时要求较高时，选用此模式 <br>
     *        该模式下，音视频通话延时会明显降低，但同时弱网抗性、通话音质等均会受到一定影响。  <br>
     */
    ByteRTCRoomProfileLowLatency = 4,
    /** 
     * @brief 适用于 1 vs 1 音视频通话
     */
    ByteRTCRoomProfileChat = 5,
    /** 
     * @brief 适用于 3 人及以上纯语音通话。<br>
     *        通话中，闭麦时为是媒体模式，上麦后切换为通话模式。
     */
    ByteRTCRoomProfileChatRoom = 6,
    /** 
     * @brief 实现多端同步播放音视频，适用于 “一起看” 或 “一起听” 场景。<br>
     *        该场景中，使用 RTC 信令同步播放进度，共享的音频内容不通过 RTC 进行传输。
     */
    ByteRTCRoomProfileLwTogether = 7,
    /** 
     * @brief 适用于对音质要求较高的游戏场景，优化音频 3A 策略，只通过媒体模式播放音频
     */
    ByteRTCRoomProfileGameHD = 8,
    /** 
     * @brief 适用于直播中主播之间连麦的业务场景。<br>
     *        该场景中，直播时通过 CDN，发起连麦 PK 时使用 RTC。
     */
    ByteRTCRoomProfileCoHost = 9,
    /** 
     * @brief 适用于单主播和观众进行音视频互动的直播。通话模式，上下麦不会有模式切换，避免音量突变现象
     */
    ByteRTCRoomProfileInteractivePodcast = 10,
    /** 
     * @brief 线上 KTV 场景，音乐音质，低延迟<br>
     *        使用 RTC 传输伴奏音乐，混音后的歌声，适合独唱或单通合唱
     */
    ByteRTCRoomProfileKTV = 11,
    /** 
     * @brief 适合在线实时合唱场景，高音质，超低延迟。使用本配置前请联系技术支持进行协助完成其他配置。
     */
    ByteRTCRoomProfileChorus = 12,
    /** 
     * @brief 适用于 VR 场景。支持最高 192 KHz 音频采样率，可开启球形立体声。345之后支持
     */
    ByteRTCRoomProfileVRChat = 13,
    /** 
     * @brief 适用于 1 vs 1 游戏串流，支持公网或局域网。
     */
    ByteRTCRoomProfileGameStreaming = 14,
    /** 
     * @brief 适用于局域网的 1 对多视频直播，最高支持 8K， 60 帧/秒， 100 Mbps 码率<br>
     *        需要在局域网配置私有化部署媒体服务器。
     */
    ByteRTCRoomProfileLanLiveStreaming = 15,
    /** 
     * @brief 适用于云端会议中的个人设备
     */
    ByteRTCRoomProfileMeeting = 16,
    /** 
     * @brief 适用于云端会议中的会议室终端设备，例如 Rooms，投屏盒子等。
     */
    ByteRTCRoomProfileMeetingRoom = 17,
    /** 
     * @brief 适用于课堂互动，房间内所有成员都可以进行音视频互动<br>
     *        当你的场景中需要同时互动的成员超过 10人时使用此模式
     */
    ByteRTCRoomProfileClassroom = 18,
};

/** 
 * @hidden
 * @deprecated since 3.45 and will be delted in 3.51.
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
 * @brief SEI 信息来源。
 */
typedef NS_ENUM(NSInteger, ByteRTCSEIMessageSourceType) {
    /** 
     * @brief （默认值）用户自定义。
     */
    ByteRTCSEIMessageSourceTypeDefault = 0,
    /** 
     * @brief 系统定义，包含音量指示信息。
     */
    ByteRTCSEIMessageSourceTypeSystem = 1,
};

/** 
 * @type keytype
 * @brief SEI 发送模式。
 */
typedef NS_ENUM(NSInteger,  ByteRTCSEICountPerFrame) {
    /** 
     * @brief 单发模式。即在 1 帧间隔内多次发送 SEI 数据时，多个 SEI 按队列逐帧发送。
     */
    kSingleSEIPerFrame = 0,
    /** 
     * @brief 多发模式。即在 1 帧间隔内多次发送 SEI 数据时，多个 SEI 随下个视频帧同时发送。
     */
    kMultiSEIPerFrame = 1,
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
     * @brief 相同用户 ID 的用户加入本房间，当前用户被踢出房间
     */
    ByteRTCErrorCodeDuplicateLogin             = -1004,

    /** 
     * @brief 服务端调用 OpenAPI 将当前用户踢出房间
     */
    ByteRTCErrorCodeKickedOut = -1006,

    /** 
     * @brief 当调用 `createRtcRoom:` ，如果 roomId 非法，会返回 null，并抛出该错误
     */
    ByteRTCErrorCodeRoomIdIllegal = -1007,


    /** 
     * @brief Token 过期。调用 `joinRoomByKey:roomId:userInfo:rtcRoomConfig:` 使用新的 Token 重新加入房间。
     */
    ByteRTCErrorCodeTokenExpired            = -1009,
        /** 
     * @brief 调用 `updateToken:` 传入的 Token 无效
     */
    ByteRTCErrorCodeUpdateTokenWithInvalidToken     = -1010,

    /** 
     * @brief 服务端调用 OpenAPI 解散房间，所有用户被移出房间。
     */
    ByteRTCErrorCodeRoomDismiss = -1011,

    /** 
     * @brief 加入房间错误。  <br>
     *        调用 `joinRoom:userInfo:roomConfig:` 方法时, LICENSE 计费账号未使用 LICENSE_AUTHENTICATE SDK，加入房间错误。
     */
    ByteRTCJoinRoomWithoutLicenseAuthenticateSDK = -1012,

    /** 
     * @brief 通话回路检测已经存在同样 roomId 的房间了
     */
    ByteRTCRoomAlreadyExist = -1013,

    /** 
     * @brief 加入多个房间时使用了不同的 uid。<br>
     *        同一个引擎实例中，用户需使用同一个 uid 加入不同的房间。
     */
    ByteRTCUserIDDifferent = -1014,
    /** 
     * @brief 服务端license过期，拒绝进房。 <br>
     */
    ByteRTCErrorCodeJoinRoomServerLicenseExpired = -1017,
    /** 
     * @brief 超过服务端license许可的并发量上限，拒绝进房。 <br>
     */
    ByteRTCErrorCodeJoinRoomExceedsTheUpperLimit = -1018,
    /** 
     * @brief license参数错误，拒绝进房。 <br>
     */
    ByteRTCErrorCodeJoinRoomLicenseParameterError = -1019,
    /** 
     * @brief license证书路径错误。 <br>
     */
    ByteRTCErrorCodeJoinRoomLicenseFilePathError = -1020,
    /** 
     * @brief license证书不合法。 <br>
     */
    ByteRTCErrorCodeJoinRoomLicenseIllegal = -1021,
    /** 
     * @brief license证书已经过期，拒绝进房。 <br>
     */
    ByteRTCErrorCodeJoinRoomLicenseExpired = -1022,
    /** 
     * @brief license证书内容不匹配。 <br>
     */
    ByteRTCErrorCodeJoinRoomLicenseInformationNotMatch = -1023,
    /** 
     * @brief license当前证书与缓存证书不匹配。 <br>
     */
    ByteRTCErrorCodeJoinRoomLicenseNotMatchWithCache = -1024,
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
    /** 
     * @brief 音视频同步失败。  <br>
     *        当前音频源已与其他视频源关联同步关系。  <br>
     *        单个音频源不支持与多个视频源同时同步。
     */
    ByteRTCErrorCodInvalidAudioSyncUidRepeated = -1083,
    /** 
     * @brief 服务端异常状态导致退出房间。  <br>
     *        SDK与信令服务器断开，并不再自动重连，可联系技术支持。  <br>
     */
    ByteRTCErrorCodeAbnormalServerStatus = -1084,
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
     * @deprecated since 3.45 and will be delted in 3.51.
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
     * @hidden currently not available
     * @brief 函数调用顺序错误，当前代码中未使用。
     */
    ByteRTCWarningCodeInvokeError = -2005,
    /** 
     * @hidden for internal use only
     * @brief 调度异常，服务器返回的媒体服务器地址不可用。
     */
    ByteRTCWarningCodeInvalidExpectMediaServerAddress = -2007,
    /** 
     * @brief 当调用 `setUserVisibility:` 将自身可见性设置为 false 后，再尝试发布流会触发此警告。  <br>
     */
    ByteRTCWarningCodePublishStreamForbiden = -2009,
    /** 
     * @deprecated since 3.45 and will be delted in 3.51.
     * @brief 自动订阅模式未关闭时，尝试开启手动订阅模式会触发此警告。  <br>
     *        你需在进房前关闭自动订阅模式，再调用 subscribeStream:mediaStreamType:{@link #ByteRTCRoom#subscribeStream:mediaStreamType:} 方法手动订阅音视频流。
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
     * @brief 用户已经在其他房间发布过流，或者用户正在发布公共流。
     */
    ByteRTCWarningCodeUserInPublish = -2014,
    /** 
     * @deprecated since 3.45 and will be delted in 3.51.
     * @brief 同样roomid的房间已经存在了
     */
    ByteRTCWarningCodeRoomAlreadyExist = -2015,

    /** 
     * @brief 已存在相同 roomId 的房间，新创建的房间实例已替换旧房间实例。
     */
    ByteRTCWarningCodeOldRoomBeenReplaced = -2016,

    /** 
     * @brief 当前正在进行回路测试，该接口调用无效
     */
    ByteRTCWarningCodeInEchoTestMode = -2017,
    /** 
     * @brief 摄像头权限异常，当前应用没有获取摄像头权限
     */
    ByteRTCWarningCodeNoCameraPermission            = -5001,
    /** 
     * @brief 麦克风权限异常，当前应用没有获取麦克风权限
     * @deprecated since 3.33 and will be delted in 3.51, use ByteRTCMediaDeviceWarning{@link #ByteRTCMediaDeviceWarning} instead.
     */
    ByteRTCWarningCodeNoMicrophonePermission        = -5002,
    /** 
     * @brief 音频采集设备启动失败。  <br>
     *        启动音频采集设备失败，当前设备可能被其他应用占用。
     * @deprecated since 3.33 and will be delted in 3.51, use ByteRTCMediaDeviceWarning{@link #ByteRTCMediaDeviceWarning} instead.
     */
    ByteRTCWarningCodeAudioDeviceManagerRecordingStartFail     = -5003,
    /** 
     * @brief 音频播放设备启动失败警告。  <br>
     *        可能由于系统资源不足，或参数错误。
     * @deprecated since 3.33 and will be delted in 3.51, use ByteRTCMediaDeviceWarning{@link #ByteRTCMediaDeviceWarning} instead.
     */
    ByteRTCWarningCodeAudioDeviceManagerPlayoutStartFail = -5004,
    /** 
     * @brief 无可用音频采集设备。  <br>
     *        启动音频采集设备失败，请插入可用的音频采集设备。
     * @deprecated since 3.33 and will be delted in 3.51, use ByteRTCMediaDeviceWarning{@link #ByteRTCMediaDeviceWarning} instead.
     */
    ByteRTCWarningCodeNoRecordingDevice = -5005,
    /** 
     * @brief 无可用音频播放设备。  <br>
     *        启动音频播放设备失败，请插入可用的音频播放设备。
     * @deprecated since 3.33 and will be delted in 3.51, use ByteRTCMediaDeviceWarning{@link #ByteRTCMediaDeviceWarning} instead.
     */
    ByteRTCWarningCodeNoPlayoutDevice = -5006,
    /** 
     * @brief 当前音频设备没有采集到有效的声音数据，请检查更换音频采集设备。
     * @deprecated since 3.33 and will be delted in 3.51, use ByteRTCMediaDeviceWarning{@link #ByteRTCMediaDeviceWarning} instead.
     */
    ByteRTCWarningCodeRecordingSilence = -5007,
    /** 
     * @brief 媒体设备误操作警告。  <br>
     *        使用自定义采集时，不可调用内部采集开关，调用时触发此警告。
     * @deprecated since 3.33 and will be delted in 3.51, use ByteRTCMediaDeviceWarning{@link #ByteRTCMediaDeviceWarning} instead.
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
     * @brief 外部音频源新旧接口混用
     */
    ByteRTCWarningInvalidCallForExtAudio = -5013,
    /** 
     * @brief 指定的内部渲染画布句柄无效。  <br>
     *        当你调用 setLocalVideoCanvas:withCanvas:{@link #ByteRTCVideo#setLocalVideoCanvas:withCanvas:} 或 setRemoteVideoCanvas:withCanvas:{@link #ByteRTCVideo#setRemoteVideoCanvas:withCanvas:} 时指定了无效的画布句柄，触发此回调。
     */
    ByteRTCWarningCodeInvalidCanvasHandle = -6001,

    /**
     * @hidden for internal use only
     */
    ByteRTCWarningCodeInvaildSamiAppkeyORToken = -7002,

    /**
     * @hidden for internal use only
     */
    ByteRTCWarningCodeInvaildSamiResourcePath = -7003,

    /**
     * @hidden for internal use only
     */
    ByteRTCWarningCodeLoadSamiLibraryFailed = -7004,

    /**
     * @hidden for internal use only
     */
    ByteRTCWarningCodeInvaildSamiEffectType = -7005
};

/** 
 * @type keytype
 * @brief 性能相关告警的原因
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
 * @hidden
 * @deprecated since 3.45 and will be deleted in 3.51.
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
     * @brief 上行网络不佳或设备性能不足时，发布的视频流会从大流到小流依次降级，直到与当前网络性能匹配，具体降级规则参看[性能回退](https://www.volcengine.com/docs/6348/70137)文档。
     */
    ByteRTCPublishFallbackOptionSimulcast = 1,
};

/** 
 * @hidden
 * @deprecated since 3.26 and will be deleted in 3.51, use RoomConfig in joinRoom API instead.
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
     * @brief 下行网络不佳或设备性能不足时，对视频流做降级处理，具体降级规则参看[音视频流回退](70137)。 <br>
     *        该设置仅对发布端调用 `enableSimulcastMode:` 开启发送多路流功能的情况生效。
     */
    ByteRTCSubscribeFallbackOptionVideoStreamLow = 1,
    /** 
     * @brief 下行网络不佳或设备性能不足时，先对视频流做回退处理。当网络状况不满足接收弱流时，则自动取消接收视频，仅接收音频。<br>
     *        该设置仅对发布端调用 `enableSimulcastMode:` 开启发送多路流功能的情况生效。
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
 * @brief 本地音频流状态。
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
     * @hidden currently not available
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
     * @brief 本地视频采集设备已被占用
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
     * @brief 通话过程中本地视频采集设备被其他程序抢占，导致设备连接中断
     */
    ByteRTCLocalVideoStreamErrorDeviceDisconnected = 7,
};

/** 
 * @type keytype
 * @brief 用户订阅的远端音频流状态。
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
     * @brief 开始接收远端音频流首包。
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
     * @brief 远端音频流卡顿。
     */
    ByteRTCRemoteAudioStateFrozen = 3,
    /** 
     * @hidden currently not available
     * @brief 远端音频流播放失败
     * @notes 该错误码暂未使用
     */
    ByteRTCRemoteAudioStateFailed = 4,
};

/** 
 * @type keytype
 * @brief 接收远端音频流状态改变的原因。
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
     *@hidden currently not available
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
 * @brief 媒体设备状态<br>
 *        通过 `rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:` 或 `rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:` 回调设备状态。
 */
typedef NS_ENUM(NSInteger, ByteRTCMediaDeviceState) {
    /** 
     * @brief 设备已开启
     */
    ByteRTCMediaDeviceStateStarted = 1,
    /** 
     * @brief 设备已停止
     */
    ByteRTCMediaDeviceStateStopped = 2,
    /** 
     * @brief 设备运行时错误<br>
     *       例如，当媒体设备的预期行为是正常采集，但没有收到采集数据时，将回调该状态。
     */
    ByteRTCMediaDeviceStateRuntimeError = 3,
    /** 
     * @brief 设备已插入
     */
    ByteRTCMediaDeviceStateAdded = 10,
    /** 
     * @brief 设备被移除
     */
    ByteRTCMediaDeviceStateRemoved = 11,
    /** 
     * @brief 系统通话，锁屏或第三方应用打断了音视频通话。将在通话结束或第三方应用结束占用后自动恢复。
     */
    ByteRTCMediaDeviceStateInterruptionBegan = 12,
    /** 
     * @brief 音视频通话已从系统电话或第三方应用打断中恢复
     */
    ByteRTCMediaDeviceStateInterruptionEnded = 13
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
     * @brief 无采集数据。当媒体设备的预期行为是正常采集，但没有收到采集数据时，将收到该错误。
     */
    ByteRTCMediaDeviceErrorDeviceNoCallback = 6,
    /** 
     * @brief 设备采样率不支持
     */
    ByteRTCMediaDeviceErrorUNSupportFormat = 7,
    /** 
     * @hidden(macOS)
     * @brief iOS 屏幕采集没有 group Id 参数
     */
    ByteRTCMediaDeviceErrorNotFindGroupId = 8,
   /** 
    * @hidden(macOS)
    * @brief 视频采集中断：因用户使用系统相机，应用切换到后台运行，导致采集中断。
    */
   ByteRTCMediaDeviceErrorNotAvailableInBackground = 9,
   /** 
    * @hidden(macOS)
    * @brief 视频采集中断：可能由于其他应用占用系统相机，导致视频设备暂时不可用，从而造成采集中断。
    */
   ByteRTCMediaDeviceErrorVideoInUseByAnotherClient = 10,
   /** 
    * @hidden(macOS)
    * @brief 视频采集中断：当前应用处于侧拉、分屏或者画中画模式时，导致采集中断。
    */
   ByteRTCMediaDeviceErrorNotAvailableWithMultipleForegroundApps = 11,
   /** 
    * @hidden(macOS)
    * @brief 视频采集中断：由于系统性能不足导致中断，比如设备过热。
    */
   ByteRTCMediaDeviceErrorNotAvailableDueToSystemPressure = 12
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
     * @brief 采集到的数据为静音帧。
     */
    ByteRTCMediaDeviceWarningCaptureSilence = 2,
    // The following warning codes are only valid for meeting scenarios.
    /** 
     * @hidden for internal use only
     * @brief 音量过大，超过设备采集范围。建议降低麦克风音量或者降低声源音量。
     */
    ByteRTCMediaDeviceWarningDetectClipping = 10,
    /** 
     * @hidden for internal use only
     * @brief 回声泄露
     */
    ByteRTCMediaDeviceWarningDetectLeakEcho = 11,
    /** 
     * @hidden for internal use only
     * @brief 低信噪比
     */
    ByteRTCMediaDeviceWarningDetectLowSNR = 12,
    /** 
     * @hidden for internal use only
     * @brief 采集插零现象
     */
    ByteRTCMediaDeviceWarningDetectInsertSilence = 13,
    /** 
     * @hidden for internal use only
     * @brief 设备采集静音
     */
    ByteRTCMediaDeviceWarningCaptureDetectSilence = 14,
    /** 
     * @hidden for internal use only
     * @brief 设备采集静音消失
     */
    ByteRTCMediaDeviceWarningCaptureDetectSilenceDisappear = 15,
    /** 
     * @brief 啸叫。触发该回调的情况如下：1）不支持啸叫抑制的房间模式下，检测到啸叫；2）支持啸叫抑制的房间模式下，检测到未被抑制的啸叫。
     *        仅 ByteRTCRoomProfileCommunication、ByteRTCRoomProfileMeeting、ByteRTCRoomProfileMeetingRoom 三种房间模式支持啸叫抑制。
     *        建议提醒用户检查客户端的距离或将麦克风和扬声器调至静音。
     */
    ByteRTCMediaDeviceWarningCaptureDetectHowling = 16,
    /** 
     * @hidden(macOS)
     * @brief 当前 AudioScenario 不支持更改音频路由，设置音频路由失败
     */
    ByteRTCMediaDeviceWarningSetAudioRouteInvalidScenario = 20,
    /** 
     * @hidden(macOS)
     * @brief 音频设备不存在，设置音频路由失败
     */
    ByteRTCMediaDeviceWarningSetAudioRouteNotExists = 21,
    /** 
     * @hidden(macOS)
     * @brief 音频路由被系统或其他应用占用，设置音频路由失败
     */
    ByteRTCMediaDeviceWarningSetAudioRouteFailedByPriority = 22,
    /** 
     * @hidden(macOS)
     * @brief 当前非通话模式 ByteRTCAudioScenarioCommunication，不支持设置音频路由
     */
    ByteRTCMediaDeviceWarningSetAudioRouteNotVoipMode = 23,
    /** 
     * @hidden(macOS)
     * @brief 音频设备未启动，设置音频路由失败
     */
    ByteRTCMediaDeviceWarningSetAudioRouteDeviceNotStart = 24,
    /** 
     * @hidden(macOS)
     * @brief 非纯媒体音频场景，此时不支持切换蓝牙传输协议。待切换至纯媒体音频场景后生效。
     */
    ByteRTCMediaDeviceWarningSetBluetoothModeScenarioUnsupport = 25,
    /** 
     * @hidden(macOS)
     * @brief 当前不支持设置 HFP。
     */
     ByteRTCMediaDeviceWarningSetBluetoothModeUnsupport = 26
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
 * @brief 通话质量反馈预设问题列表
 */
BYTERTC_APPLE_EXPORT  @interface ByteRTCProblemOption: NSObject
/** 
 * @brief 初始化 ByteRTCProblemOption
 */
- (instancetype _Nonnull)initWithOption:(ByteRTCProblemFeedbackOption)option;
/** 
 * @brief 读取音视频质量反馈问题类型，参看 ByteRTCProblemFeedbackOption{@link #ByteRTCProblemFeedbackOption}。
 */
@property(nonatomic, assign, readonly) ByteRTCProblemFeedbackOption option;
/** 
 * @brief 读取 ByteRTCProblemOption 类对应的文字描述
 */
@property(nonatomic, copy, readonly) NSString * _Nonnull desc;
@end


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
     * @brief 播放中
     */
    ByteRTCFirstFramePlayStatePlaying = 0,
    /** 
     * @brief 播放成功
     */
    ByteRTCFirstFramePlayStatePlay = 1,
    /** 
     * @brief 播放失败
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
     * @brief 标准 H264 编码格式
     */
    ByteRTCVideoCodecTypeH264 = 1,
    /** 
     * @brief ByteVC1 编码器
     */
    ByteRTCVideoCodecTypeByteVC1 = 2,
};

/** 
 * @type keytype
 * @hidden for internal use only
 * @brief 超分模式。
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoSuperResolutionMode) {
    /** 
     * @brief 关闭超分。
     */
    ByteRTCVideoSuperResolutionModeOff = 0,
    /** 
     * @brief 开启超分。
     */
    ByteRTCVideoSuperResolutionModeOn = 1,
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
 * @brief 黑帧视频流状态
 */
typedef NS_ENUM(NSInteger,  ByteSEIStreamEventType) {
    /** 
     * @brief 远端用户发布黑帧视频流。  <br>
     *        纯语音通话场景下，远端用户调用 sendSEIMessage:andMessage:andRepeatCount:andCountPerFrame:{@link #ByteRTCVideo#sendSEIMessage:andMessage:andRepeatCount:andCountPerFrame:} 发送 SEI 数据时，SDK 会自动发布一路黑帧视频流，并触发该回调。
     */
    ByteSEIStreamEventTypeStreamAdd = 0,
    /** 
     * @brief 远端黑帧视频流移除。该回调的触发时机包括：  <br>
     *        + 远端用户开启摄像头采集，由语音通话切换至视频通话，黑帧视频流停止发布；  <br>
     *        + 远端用户调用 sendSEIMessage:andMessage:andRepeatCount:andCountPerFrame:{@link #ByteRTCVideo#sendSEIMessage:andMessage:andRepeatCount:andCountPerFrame:} 后 1min 内未有 SEI 数据发送，黑帧视频流停止发布；  <br>
     *        + 远端用户调用 setVideoSourceType:WithStreamIndex:{@link #ByteRTCVideo#setVideoSourceType:WithStreamIndex:} 切换至自定义视频采集时，黑帧视频流停止发布。
     */
     ByteSEIStreamEventTypeStreamRemove = 1,
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
 * @brief 颜色空间
 */
typedef NS_ENUM(NSInteger, ByteRTCColorSpace) {
    /** 
     * 未知的颜色空间，默认使用kColorSpaceYCbCrBT601LimitedRange颜色空间
     */
    ByteRTCColorSpaceUnknown = 0,
    /** 
     * @brief BT.601数字编码标准，颜色空间[16-235]
     */
    ByteRTCColorSpaceYCbCrBT601LimitedRange = 1,
    /** 
     *  @brief BT.601数字编码标准，颜色空间[0-255]
     */
    ByteRTCColorSpaceYCbCrBT601FullRange = 2,
    /** 
     * @brief BT.7091数字编码标准，颜色空间[16-235]
     */
    ByteRTCColorSpaceYCbCrBT709LimitedRange = 3,
    /** 
     * @brief BT.7091数字编码标准，颜色空间[0-255]
     */
    ByteRTCColorSpaceYCbCrBT709FullRange = 4
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
 * @type keytype
 * @brief 音视频同步状态
 */
typedef NS_ENUM(NSInteger, ByteRTCAVSyncState) {
    /** 
     * @brief 音视频开始同步
     */
    AVSyncStateAVStreamSyncBegin = 0,
    /** 
     * @brief 音视频同步过程中音频移除，但不影响当前的同步关系
     */
    AVSyncStateAudioStreamRemove = 1,
    /** 
     * @brief 音视频同步过程中视频移除，但不影响当前的同步关系
     */
    AVSyncStateVdieoStreamRemove = 2,
    /** 
     * @hidden for internal use only
     * @brief 订阅端设置同步  <br>
     */
    AVSyncStateSetAVSyncStreamId = 3,
};
/** 
 * @type keytype
 * @brief 音视频回路测试结果
 */
typedef NS_ENUM(NSInteger, ByteRTCEchoTestResult) {
    /** 
     * @brief 接收到采集的音视频的回放，通话回路检测成功
     */
    EchoTestSuccess = 0,
    /** 
     * @brief 测试超过 60s 仍未完成，已自动停止
     */
    EchoTestTimeout = 1,
    /** 
     * @brief 上一次测试结束和下一次测试开始之间的时间间隔少于 5s
     */
    EchoTestIntervalShort = 2,
    /** 
     * @brief 音频采集异常
     */
    EchoTestAudioDeviceError = 3,
    /** 
     * @brief 视频采集异常
     */
    EchoTestVideoDeviceError = 4,
    /** 
     * @brief 音频接收异常
     */
    EchoTestAudioReceiveError = 5,
    /** 
     * @brief 视频接收异常
     */
    EchoTestVideoReceiveError = 6,
    /** 
     * @brief 内部错误，不可恢复
     */
    EchoTestInternalError = 7
};

/** 
 * @type errorcode
 * @brief 公共流状态码
 */
typedef NS_ENUM(NSInteger, ByteRTCPublicStreamErrorCode) {
    /** 
     * @brief 发布或订阅成功
     */
    ByteRTCPublicStreamErrorCodeSuccess = 0,
    /** 
     * @brief 公共流的参数异常，请修改参数后重试
     */
    ByteRTCPublicStreamErrorCodeParamError = 1191,
    /** 
     * @brief 服务端状态异常，将自动重试
     */
    ByteRTCPublicStreamErrorCodeStatusError = 1192,
    /** 
     * @brief 内部错误，不可恢复，请重试。
     */
    ByteRTCPublicStreamErrorCodeInternalError = 1193,
    /** 
     * @brief 推流失败，将自动重试，用户不需要处理
     */
    ByteRTCPublicStreamErrorCodePushError = 1195,
    /** 
     * @brief 推流失败，10 s 后会重试，重试 3 次后停止重试
     */
    ByteRTCPublicStreamErrorCodeTimeOut = 1196
};
/** 
 * @type keytype
 * @brief 蓝牙传输协议。
 */
typedef NS_ENUM(NSInteger, ByteRTCBluetoothMode) {
     /** 
      * @brief  默认采用 auto 模式，具体如下：
      * <table>
      * <tr>
      *   <th>场景</th>
      *   <th> HFP </th>
      *   <th> A2DP </th>
      * </tr>
      * <tr>
      *   <th>纯通话场景</th>
      *   <th> 蓝牙设备支持 HFP </th>
      *   <th> 蓝牙设备不支持 HFP </th>
      * </tr>
      * <tr>
      *   <th>纯媒体场景</th>
      *   <th> 使用蓝牙设备采集播放音频 </th>
      *   <th> 使用 iOS 设备采集音频，蓝牙设备播放音频 </th>
      * </tr>
      * </table>
      */
     ByteRTCBluetoothModeAuto = 0,

     /** 
      * @brief 高级音频分配配置文件（A2DP）。立体声、高音质。采用 iOS 设备进行音频采集，蓝牙设备进行播放。
      */
     ByteRTCBluetoothModeA2DP = 1,

    /** 
     * @brief 免提配置文件（HFP）。单声道、普通音质。音频采集和播放设备都使用蓝牙设备。
     */
    ByteRTCBluetoothModeHFP = 2
};
/** 
 * @type keytype
 * @brief 音视频回路测试参数
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCEchoTestConfig : NSObject
/** 
 * @brief 用于渲染接收到的视频的视图
 */
@property(strong, nonatomic) ByteRTCView* _Nullable view;
/** 
 * @brief 测试用户加入的房间 ID。  <br>
 */
@property(copy, nonatomic) NSString *_Nonnull roomId;
/** 
 * @brief 进行音视频通话回路测试的用户 ID
 */
@property(copy, nonatomic) NSString *_Nonnull userId;
/** 
 * @brief 对用户进房时进行鉴权验证的动态密钥，用于保证音视频通话回路测试的安全性。
 */
@property(copy, nonatomic) NSString *_Nonnull token;
/** 
 * @brief 是否检测音频。检测设备为系统默认音频设备。  <br>
 *        + true：是  <br>
 *            - 若使用 SDK 内部采集，此时设备麦克风会自动开启，并在 audioReportInterval 值大于 0 时触发 `onLocalAudioPropertiesReport` 回调，你可以根据该回调判断麦克风的工作状态  <br>
 *            - 若使用自定义采集，此时你需调用 pushExternalAudioFrame:{@link #ByteRTCVideo#pushExternalAudioFrame:} 将采集到的音频推送给 SDK  <br>
 *        + flase：否  <br>
 */
@property(assign, nonatomic) BOOL enableAudio;
/** 
 * @brief 是否检测视频。PC 端默认检测列表中第一个视频设备。  <br>
 *        + true：是  <br>
 *            - 若使用 SDK 内部采集，此时设备摄像头会自动开启  <br>
 *            - 若使用自定义采集，此时你需调用 pushExternalVideoFrame:{@link #ByteRTCVideo#pushExternalVideoFrame:} 将采集到的视频推送给 SDK  <br>
 *        + flase：否  <br>
 * @notes 视频的发布参数固定为：分辨率 640px × 360px，帧率 15fps。
 */
@property(assign, nonatomic) BOOL enableVideo;
/** 
 * @brief 音量信息提示间隔，单位：ms，默认为 100ms <br>
 *       + `<= 0`: 关闭信息提示  <br>
 *       + `(0,100]`: 开启信息提示，不合法的 interval 值，SDK 自动设置为 100ms  <br>
 *       + `> 100`: 开启信息提示，并将信息提示间隔设置为此值  <br>
 */
@property(assign, nonatomic) NSInteger audioReportInterval;
@end

/** 
 * @type keytype
 * @brief 用户信息。  <br>
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCUserInfo : NSObject
/** 
 * @brief 用户 ID。该字符串符合正则表达式：`[a-zA-Z0-9_@\-\.]{1,128}`。
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
 * @brief 发送码率（kbps），获取该数据时的瞬时值
 */
@property(assign, nonatomic) NSInteger txKbitrate;
/** 
 * @brief 接收码率（kbps），获取该数据时的瞬时值
 */
@property(assign, nonatomic) NSInteger rxKbitrate;
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
 * @brief 屏幕接收码率，获取该数据时的瞬时值，单位为 Kbps
 */
@property(assign, nonatomic) NSInteger txScreenKBitrate;
/** 
 * @brief 屏幕发送码率，获取该数据时的瞬时值，单位为 Kbps
 */
@property(assign, nonatomic) NSInteger rxScreenKBitrate;
/** 
 * @brief 当前房间内的可见用户人数，包括本地用户自身
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
/** 
 * @brief 蜂窝路径发送的码率 (kbps)，为获取该数据时的瞬时值
 */
@property(assign, nonatomic) NSInteger tx_cellular_kbitrate;
/** 
 * @brief 蜂窝路径接收码率 (kbps)，为获取该数据时的瞬时值
 */
@property(assign, nonatomic) NSInteger rx_cellular_kbitrate;
@end

/** 
 * @type keytype
 * @brief 本地视频流统计信息，统计周期为 2s 。  <br>
 *        本地用户发布视频流成功后，SDK 会周期性地通过 `onLocalStreamStats`
 *        通知本地用户发布的视频流在此次统计周期内的发送状况。此数据结构即为回调给本地用户的参数类型。  <br>
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCLocalVideoStats : NSObject
/** 
 * @brief 发送码率。此次统计周期内实际发送的分辨率最大的视频流的发送码率，单位为 Kbps
 */
@property(assign, nonatomic) float sentKBitrate;
/** 
 * @brief 采集帧率。此次统计周期内的视频采集帧率，单位为 fps 。
 */
@property(assign, nonatomic) NSInteger inputFrameRate;
/** 
 * @brief 发送帧率。此次统计周期内实际发送的分辨率最大的视频流的视频发送帧率，单位为 fps 。
 */
@property(assign, nonatomic) NSInteger sentFrameRate;
/** 
 * @brief 编码器输出帧率。当前编码器在此次统计周期内实际发送的分辨率最大的视频流的输出帧率，单位为 fps 。
 */
@property(assign, nonatomic) NSInteger encoderOutputFrameRate;
/** 
 * @brief 本地渲染帧率。此次统计周期内的本地视频渲染帧率，单位为 fps 。
 */
@property(assign, nonatomic) NSInteger rendererOutputFrameRate;
/** 
 * @brief 统计间隔，单位为 ms 。
 *        此字段用于设置回调的统计周期，默认设置为 2s 。
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
 * @brief 视频编码码率。此次统计周期内的实际发送的分辨率最大的视频流视频编码码率，单位为 Kbps 。
 */
@property(assign, nonatomic) NSInteger encodedBitrate;
/** 
 * @brief 实际发送的分辨率最大的视频流的视频编码宽度，单位为 px 。
 */
@property(assign, nonatomic) NSInteger encodedFrameWidth;
/** 
 * @brief 实际发送的分辨率最大的视频流的视频编码高度，单位为 px 。
 */
@property(assign, nonatomic) NSInteger encodedFrameHeight;
/** 
 * @brief 此次统计周期内实际发送的分辨率最大的视频流的发送的视频帧总数。
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
 * @brief 远端视频流统计信息，统计周期为 2s 。  <br>
 *        本地用户订阅远端视频流成功后，SDK 会周期性地通过 `onRemoteStreamStats`
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
 *        此字段用于设置回调的统计周期，目前设置为 2s 。
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
 * @brief 编码类型。参看 ByteRTCVideoCodecType{@link #ByteRTCVideoCodecType} 类型。
 */
@property(nonatomic) ByteRTCVideoCodecType codecType;
/** 
 * @brief SDK 订阅的远端视频流的分辨率下标。  <br>
 */
@property(assign, nonatomic) NSInteger videoIndex;
/** 
 * @brief 视频下行网络抖动，单位为 ms。  <br>
 */
@property(assign, nonatomic) NSInteger jitter;
/** 
 * @hidden for internal use only
 * @brief 远端视频超分模式，参看 ByteRTCVideoSuperResolutionMode{@link #ByteRTCVideoSuperResolutionMode}。
 */
@property(assign, nonatomic) ByteRTCVideoSuperResolutionMode superResolutionMode;
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
 *        此字段用于设置回调的统计周期，默认设置为 2s 。
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
 * @brief 此次订阅中，对远端音频流进行解码的累计耗时。单位为 s。
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
 * @brief 所属用户的媒体流上行网络质量，详见 ByteRTCNetworkQuality{@link #ByteRTCNetworkQuality}
 * @deprecated since 3.36 and will be deleted in 3.51, use rtcRoom:onNetworkQuality:remoteQualities:{@link #ByteRTCRoomDelegate#rtcRoom:onNetworkQuality:remoteQualities:} instead
 */
@property(assign, nonatomic) ByteRTCNetworkQuality tx_quality;
/** 
 * @brief 所属用户的媒体流下行网络质量，详见 ByteRTCNetworkQuality{@link #ByteRTCNetworkQuality}
 * @deprecated since 3.36 and will be deleted in 3.51, use rtcRoom:onNetworkQuality:remoteQualities:{@link #ByteRTCRoomDelegate#rtcRoom:onNetworkQuality:remoteQualities:} instead
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
 * @brief 所属用户的媒体流上行网络质量，详见 ByteRTCNetworkQuality{@link #ByteRTCNetworkQuality}
 * @deprecated since 3.36 and will be deleted in 3.51, use rtcRoom:onNetworkQuality:remoteQualities:{@link #ByteRTCRoomDelegate#rtcRoom:onNetworkQuality:remoteQualities:} instead
 */
@property(assign, nonatomic) ByteRTCNetworkQuality tx_quality;
/** 
 * @brief 所属用户的媒体流下行网络质量，详见 ByteRTCNetworkQuality{@link #ByteRTCNetworkQuality}
 * @deprecated since 3.36 and will be deleted in 3.51, use rtcRoom:onNetworkQuality:remoteQualities:{@link #ByteRTCRoomDelegate#rtcRoom:onNetworkQuality:remoteQualities:} instead
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
 * @brief 自定义加密接口
 */
@protocol ByteRTCEncryptHandler <NSObject>

@required
/** 
 * @type api
 * @region 加密
 * @brief 自定义加密。  <br>
 *        使用设定的自定义加密方式，对编码后传输前的音视频帧数据进行加密。<br>
 *        暂不支持对原始音视频帧进行加密。
 * @param rawData 原始音视频帧数据
 * @return 加密后的数据  <br>
 *        + 非空，表示加密后的数据  <br>
 *        + 为空，表示数据被丢弃
 * @notes <br>
 *        + 使用此接口进行自定义加密前，你必须先设置自定义加密方式，参看 `setCustomizeEncryptHandler:`。
 *        + 使用 onDecryptData:{@link #ByteRTCEncryptHandler#onDecryptData:} 对已加密的音视频帧数据进行解密。
 *        + 返回的数据大小应控制在原始数据的 90% ~ 120% 范围以内，不然将被丢弃。
 */
- (NSData * _Nonnull) onEncryptData:(NSData * _Nonnull)rawData;

@required
/** 
 * @type api
 * @region 加密
 * @brief 自定义解密。  <br>
 *        对自定义加密后的音视频帧数据进行解密。关于自定义加密，参看 onEncryptData:{@link #ByteRTCEncryptHandler#onEncryptData:}。
 * @param rawData 收到的已加密的音视频帧数据
 * @return 解密后的数据  <br>
 *        + 非空，表示解密后的数据  <br>
 *        + 为空，表示丢弃该帧
 * @notes <br>
 *        + 使用此接口进行解密前，你必须先设定解密方式，参看 `setCustomizeEncryptHandler:`。
 *        + 返回的数据大小应控制在原始数据的 90% ~ 120% 范围以内，不然将被丢弃。
 */
- (NSData * _Nonnull) onDecryptData:(NSData * _Nonnull)rawData;
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
     * @brief 跨房间转发媒体流过程中目标房间 ID<br>
     */
    @property(strong, nonatomic) NSString* _Nullable roomId;
    /** 
     * @brief 使用转发目标房间 RoomID 和 UserID 生成 Token。<br>
     *        测试时可使用控制台生成临时 Token，正式上线需要使用密钥 SDK 在你的服务端生成并下发 Token。<br>
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

/** 
 * @type keytype
 * @brief 网络时间信息
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCNetworkTimeInfo: NSObject
/** 
 * @brief 网络时间，单位：ms
 */
@property(assign, nonatomic) int64_t timestamp;
@end

#pragma mark - ByteRTCDeviceCollection
/** 
 * @type api
 * @hidden(iOS)
 * @brief 音视频设备相关的信息
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCDeviceCollection : NSObject
/** 
 * @type api
 * @region 引擎管理
 * @brief 获取当前音视频设备数量
 * @return 音视频设备数量
 */
- (int)getCount;
/** 
 * @type api
 * @region 引擎管理
 * @brief 根据索引号，获取设备信息
 * @param index 设备索引号，从 0 开始，注意需小于 getCount{@link #ByteRTCDeviceCollection#getCount} 返回值。
 * @param deviceName 设备名称
 * @param deviceID 设备 ID
 * @return  <br>
 *        + 0：方法调用成功  <br>
 *        + !0：方法调用失败  <br>
 */
- (int)getDevice:(int)index DeviceName:(NSString * _Nonnull * _Nonnull)deviceName DeviceID:(NSString * _Nonnull * _Nonnull) deviceID;
@end

/** 
 * @type keytype
 * @brief 音频dump状态。  <br>
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioDumpStatus){
    /** 
     * @brief 音频dump启动失败
     */
    ByteRTCAudioDumpStartFailure = 0,
    /** 
     * @brief 音频dump启动成功
     */
    ByteRTCAudioDumpStartSuccess = 1,
    /** 
     * @brief 音频dump停止失败
     */
    ByteRTCAudioDumpStopFailure = 2,
    /** 
     * @brief 音频dump停止成功
     */
    ByteRTCAudioDumpStopSuccess = 3,
    /** 
     * @brief 音频dump运行失败
     */
    ByteRTCAudioDumpRunningFailure = 4,
    /** 
     * @brief 音频dump运行成功
     */
    ByteRTCAudioDumpRunningSuccess = 5,
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
