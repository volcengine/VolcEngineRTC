/*
 * Copyright (c) 2022 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief Objective-C VolcEngineRTC Common Defines
*/

#import <CoreMedia/CMTime.h>
#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
#import <UIKit/UIKit.h>
typedef UIView   ByteRTCView;
typedef UIImage  ByteRTCImage;
#elif TARGET_OS_MAC
#import <AppKit/AppKit.h>
typedef NSView   ByteRTCView;
typedef NSImage  ByteRTCImage;
#endif

#ifdef __APPLE__
#define _BYTERTC_PLATFORM_APPLE 1
#include <TargetConditionals.h>
#if TARGET_OS_IPHONE
#define _BYTERTC_PLATFORM_MAC 0
#define _BYTERTC_PLATFORM_IOS 1
#elif TARGET_IPHONE_SIMULATOR
#define _BYTERTC_PLATFORM_MAC 0
#define _BYTERTC_PLATFORM_IOS 1
#elif TARGET_OS_MAC
#define _BYTERTC_PLATFORM_MAC 1
#define _BYTERTC_PLATFORM_IOS 0
#else
#error "Unknown Apple platform"
#endif
#endif

#define BYTERTC_TARGET_MAC (_BYTERTC_PLATFORM_MAC == 1)
#define BYTERTC_TARGET_IOS (_BYTERTC_PLATFORM_IOS == 1)

#define BYTERTC_APPLE_EXPORT __attribute__((visibility("default")))


/**
 * @hidden currently not available
 */
typedef NS_ENUM(NSInteger, ByteRTSReturnStatus) {

    ByteRTSReturnStatusSuccess = 0,

    ByteRTSReturnStatusFailure = -1,

    ByteRTSReturnStatusParameterErr = -2,

    ByteRTSReturnStatusWrongState = -3,

    ByteRTSReturnStatusHasInRoom = -4,

    ByteRTSReturnStatusHasInLogin = -5,

    ByteRTSReturnStatusRoomIdInUse = -8,
};


/**
 * @locale zh
 *  @type keytype
 *  @brief 远端用户离开房间的原因。  
 */
/**
 * @locale en
 *  @type keytype
 *  @brief  The reason why the user leaves the room.   
 */
typedef NS_ENUM(NSUInteger, ByteRTCUserOfflineReason) {
    /**
     * @locale zh
     * @brief 远端用户调用 `leaveRoom` 方法主动退出房间。  
     */
    /**
     * @locale en
     * @brief The remote user calls `leaveRoom` and leaves the room. 
     */
    ByteRTCUserOfflineReasonQuit = 0,
    /**
     * @locale zh
     * @brief 远端用户因网络等原因掉线。  
     */
    /**
     * @locale en
     * @brief The remote user is offline.   
     */
    ByteRTCUserOfflineReasonDropped = 1,
    /**
     * @locale zh
     * @brief 远端用户切换至隐身状态。  
     */
     /**
      * @locale en
      * @brief The remote user switches to invisible.   
      */
    ByteRTCUserOfflineReasonSwitchToInvisible = 2,
    /**
     * @locale zh
     * @brief 远端用户被踢出出房间。<br>
     *        因调用踢出用户的 OpenAPI，远端用户被踢出房间。
     */
    /**
     * @locale en
     * @brief The remote user is kicked out of the room.<br>
     *        Is kicked out of the room due to calling the kicked out user's OpenAPI.
     */
    ByteRTCUserOfflineReasonKickedByAdmin = 3,
};

/**
 * @locale zh
 * @type keytype
 * @brief SDK 与信令服务器连接状态。
 */
/**
 * @locale en
 * @type keytype
 * @brief SDK  Connection status with the signaling server.
 */
typedef NS_ENUM(NSInteger, ByteRTCConnectionState) {
    /**
     * @locale zh
     * @brief 连接断开超过 12s，此时 SDK 会尝试自动重连。
     */
    /**
     * @locale en
     * @brief Disconnected for 12s, SDK will try to reconnect automatically.
     */
    ByteRTCConnectionStateDisconnected = 1,
    /**
     * @locale zh
     * @brief 首次请求建立连接，正在连接中。
     */
    /**
     * @locale en
     * @brief The first request to connect to the server. Connecting.
     */
    ByteRTCConnectionStateConnecting = 2,
    /**
     * @locale zh
     * @brief 首次连接成功。
     */
    /**
     * @locale en
     * @brief The first connection was successful.
     */
    ByteRTCConnectionStateConnected = 3,
    /**
     * @locale zh
     * @brief 涵盖了以下情况：<br>
     *        + 首次连接时，10秒连接不成功; <br>
     *        + 连接成功后，断连 10 秒。自动重连中。
     */
    /**
     * @locale en
     * @brief The code includes the following status: <br>
     *        + The first connection is not successful for 10s. <br>
     *        + The connection has been lost for 10s. Auto reconnecting.
     */
    ByteRTCConnectionStateReconnecting = 4,
    /**
     * @locale zh
     * @brief 连接断开后，重连成功。
     */
    /**
     * @locale en
     * @brief Successful reconnection after disconnection.
     */
    ByteRTCConnectionStateReconnected = 5,
    /**
     * @locale zh
     * @brief 处于 `ByteRTCConnectionStateDisconnected` 状态超过 10 秒，且期间重连未成功。SDK 仍将继续尝试重连。
     */
    /**
     * @locale en
     * @brief In status `ByteRTCConnectionStateDisconnected` for more than 10s without a successful reconnection. SDK will still continue to try to reconnect.
     */
    ByteRTCConnectionStateLost = 6,
    /**
     * @locale zh
     * @brief 连接失败，服务端状态异常。SDK 不会自动重连，请重新进房，或联系技术支持。
     */
    /**
     * @locale en
     * @brief Connection failure caused by abnormal state of the server. SDK will not automatically reconnect, please re-enter the room or contact technical support.
     */
    ByteRTCConnectionStateFailed = 7,
};

/**
 * @locale zh
 * @type keytype
 * @brief SDK 网络连接类型。
 */
/**
 * @locale en
 * @type keytype
 * @brief SDK  Network connection type.
 */
typedef NS_ENUM(NSInteger, ByteRTCNetworkType) {
    /**
     * @locale zh
     * @brief 网络连接类型未知。
     */
    /**
     * @locale en
     * @brief Network connection type unknown.
     */
    ByteRTCNetworkTypeUnknown = -1,
    /**
     * @locale zh
     * @brief 网络连接已断开。
     */
    /**
     * @locale en
     * @brief The network connection has been disconnected.
     */
    ByteRTCNetworkTypeDisconnected = 0,
    /**
     * @locale zh
     * @brief 网络连接类型为 LAN 。
     */
    /**
     * @locale en
     * @brief The network connection type is LAN.
     */
    ByteRTCNetworkTypeLAN = 1,
    /**
     * @locale zh
     * @brief 网络连接类型为 Wi-Fi（包含热点）。
     */
    /**
     * @locale en
     * @brief The network connection type is Wi-Fi (including hotspots).
     */
    ByteRTCNetworkTypeWIFI = 2,
    /**
     * @locale zh
     * @brief 网络连接类型为 2G 移动网络。
     */
    /**
     * @locale en
     * @brief The network connection type is 2G mobile network.
     */
    ByteRTCNetworkTypeMobile2G = 3,
    /**
     * @locale zh
     * @brief 网络连接类型为 3G 移动网络。
     */
    /**
     * @locale en
     * @brief The network connection type is 3G mobile network.
     */
    ByteRTCNetworkTypeMobile3G = 4,
    /**
     * @locale zh
     * @brief 网络连接类型为 4G 移动网络。
     */
    /**
     * @locale en
     * @brief The network connection type is 4G mobile network.
     */
    ByteRTCNetworkTypeMobile4G = 5,
    /**
     * @locale zh
     * @brief 网络连接类型为 5G 移动网络。
     */
    /**
     * @locale en
     * @brief The network connection type is 5G mobile network.
     */
    ByteRTCNetworkTypeMobile5G = 6,
};

/**
 * @locale zh
 * @type keytype
 * @brief 媒体流网络质量。
 */
/**
 * @locale en
 * @type keytype
 * @brief Media streaming network quality.
 */
typedef NS_ENUM(NSUInteger, ByteRTCNetworkQuality) {
    /**
     * @locale zh
     * @brief 网络质量未知。
     */
    /**
     * @locale en
     * @brief Network quality unknown.
     */
    ByteRTCNetworkQualityUnknown = 0,
    /**
     * @locale zh
     * @brief 网络质量极好。
     */
    /**
     * @locale en
     * @brief The network quality is excellent.
     */
    ByteRTCNetworkQualityExcellent = 1,
    /**
     * @locale zh
     * @brief 主观感觉和 kNetworkQualityExcellent 差不多，但码率可能略低。
     */
    /**
     * @locale en
     * @brief The subjective feeling is similar to kNetworkQualityExcellent, but the bit rate may be slightly lower.
     */
    ByteRTCNetworkQualityGood = 2,
    /**
     * @locale zh
     * @brief 主观感受有瑕疵但不影响沟通。
     */
    /**
     * @locale en
     * @brief Subjective feelings are flawed but do not affect communication.
     */
    ByteRTCNetworkQualityPoor = 3,
    /**
     * @locale zh
     * @brief 勉强能沟通但不顺畅。
     */
    /**
     * @locale en
     * @brief Can barely communicate but not smoothly.
     */
    ByteRTCNetworkQualityBad = 4,
    /**
     * @locale zh
     * @brief 网络质量非常差，基本不能沟通。
     */
    /**
     * @locale en
     * @brief The quality of the network is very poor and communication is basically impossible.
     */
    ByteRTCNetworkQualityVeryBad = 5,
    /**
     * @locale zh
     * @brief 网络连接断开，无法通话。网络可能由于 12s 内无应答、开启飞行模式、拔掉网线等原因断开。<br>
     *        更多网络状态信息参见 [连接状态提示](https://www.volcengine.com/docs/6348/95376)。
     */
    /**
     * @locale en
     * @brief The network is down. It may be down due to no answer within 12s, airplane mode on, disconnected cable, etc.<br>
     *        Refer to [Get connection state](https://docs.byteplus.com/byteplus-rtc/docs/95376) for more details.
     */
    ByteRTCNetworkQualityDown = 6,
};

/**
 * @locale zh
 * @type errorcode
 * @brief 回调错误码。<br>
 *        SDK 内部遇到不可恢复的错误时，会通过 `rtcEngine:onError:` 回调通知用户。
 */
/**
 * @locale en
 * @type errorcode
 * @brief  Callback error code. When an unrecoverable error is encountered internally in the<br>
 *        SDK, the user is notified via an `rtcEngine:onError:` callback.
 */
typedef NS_ENUM(NSInteger, ByteRTSErrorCode) {
    /**
     * @locale zh
     * @brief Token 无效。<br>
     *        进房时使用的 Token 无效或过期失效。需要用户重新获取 Token，并调用<br>
     *        `updateToken:` 方法更新 Token。
     */
    /**
     * @locale en
     * @brief Token  is invalid.<br>
     *         The token used when joining the room is invalid or expired. The user is required to retrieve the token and update it by calling `updateToken:`.
     */
    ByteRTSErrorCodeInvalidToken               = -1000,
    /**
     * @locale zh
     * @brief 加入房间错误。<br>
     *        进房时发生未知错误导致加入房间失败。需要用户重新加入房间。
     */
    /**
     * @locale en
     * @brief Join room error.<br>
     *        An unknown error occurred when joining the room, which caused the room to fail to join. Users are required to rejoin the room.
     */
    ByteRTSErrorCodeJoinRoom             = -1001,
    /**
     * @locale zh
     * @brief 相同用户 ID 的用户加入本房间，当前用户被踢出房间
     */
    /**
     * @locale en
     * @brief The user has been removed from the room because the same user joined the room on the other client.
     */
    ByteRTSErrorCodeDuplicateLogin             = -1004,

    /**
     * @locale zh
     * @brief 服务端调用 OpenAPI 将当前用户踢出房间
     */
    /**
     * @locale en
     * @brief The user has been removed from the room by the administrator via a OpenAPI call.
     */
    ByteRTSErrorCodeKickedOut = -1006,

    /**
     * @locale zh
     * @brief 当调用 `createRtcRoom:` ，如果 roomId 非法，会返回 null，并抛出该错误
     */
    /**
     * @locale en
     * @brief When calling `createRtcRoom:`, if the roomId is illegal, it will return null and throw the error
     */
    ByteRTSErrorCodeRoomIdIllegal = -1007,

    /**
     * @locale zh
     * @brief Token 过期。调用 `joinRoomByKey:roomId:userInfo:rtcRoomConfig:` 使用新的 Token 重新加入房间。
     */
    /**
     * @locale en
     * @brief Token expired. Call `joinRoomByKey:roomId:userInfo:rtcRoomConfig:` to rejoin with a valid Token.
     */
    ByteRTSErrorCodeTokenExpired            = -1009,
        /**
     * @locale zh
     * @brief 调用 `updateToken:` 传入的 Token 无效
     */
    /**
     * @locale en
     * @brief The Token you provided when calling `updateToken:` is invalid.
     */
    ByteRTSErrorCodeUpdateTokenWithInvalidToken     = -1010,

    /**
     * @locale zh
     * @brief 服务端调用 OpenAPI 解散房间，所有用户被移出房间。
     */
    /**
     * @locale en
     * @brief Users have been removed from the room because the administrator dismissed the room by calling OpenAPI.
     */
    ByteRTSErrorCodeRoomDismiss = -1011,

    /**
     * @locale zh
     * @brief 通话回路检测已经存在同样 roomId 的房间了
     */
    /**
     * @locale en
     * @brief there is a room with the same roomId，whose room id is the same with echo test
     */
    ByteRTSErrorRoomAlreadyExist = -1013,

    /**
     * @locale zh
     * @brief 加入多个房间时使用了不同的 uid。<br>
     *        同一个引擎实例中，用户需使用同一个 uid 加入不同的房间。
     */
    /**
     * @locale en
     * @brief The local user joins multiple rooms with different uid.<br>
     *        In the same engine instance, users need to use the same uid to join different rooms.
     */
    ByteRTSErrorUserIDDifferent = -1014,

    /**
     * @locale zh
     * @brief 服务端异常状态导致退出房间。  <br>
     *        SDK与信令服务器断开，并不再自动重连，可联系技术支持。  
     */
    /**
     * @locale en
     * @brief The user has been removed from the room due to the abnormal status of server. <br>
     *        SDK  is disconnected with the signaling server. It will not reconnect automatically. Please contact technical support.
     */
    ByteRTSErrorCodeAbnormalServerStatus = -1084,
};

/**
 * @locale zh
 * @type errorcode
 * @brief 回调警告码。<br>
 *        警告码说明 SDK 内部遇到问题正在尝试恢复。警告码仅作通知。
 */
/**
 * @locale en
 * @type errorcode
 * @brief  Callback warning code. The warning code indicates that there is a problem within the SDK and is trying to recover. Warning codes are for notification only.
 */
typedef NS_ENUM(NSInteger, ByteRTSWarningCode) {
    /**
     * @locale zh
     * @hidden
     * @deprecated since 3.46 and will be deleted in 3.52.
     */
    /**
     * @locale en
     * @hidden
     * @deprecated since 3.46 and will be deleted in 3.52.
     */
    ByteRTSWarningCodeGetRoomFailed              = -2000,
    /**
     * @locale zh
     * @brief 进房失败。  <br>
     *        初次进房或者由于网络状况不佳断网重连时，由于服务器错误导致进房失败。SDK 会自动重试进房。
     */
    /**
     * @locale en
     * @brief Failed to enter the room.   <br>
     *        When entering the room for the first time or when the network is disconnected and reconnected due to poor network conditions, entering the room failed due to a server error. The SDK automatically retries the room.
     */
    ByteRTSWarningCodeJoinRoomFailed             = -2001,
    /**
     * @locale zh
     * @brief 发布音视频流失败。<br>
     *        当你在所在房间中发布音视频流时，由于服务器错误导致发布失败。SDK 会自动重试发布。
     */
    /**
     * @locale en
     * @brief Release audio & video stream failed.<br>
     *        When you publish audio & video streams in your room, the release fails due to a server error. The SDK automatically retries the release.
     */
    ByteRTSWarningCodePublishStreamFailed        = -2002,
    /**
     * @locale zh
     * @hidden currently not available
     * @brief 函数调用顺序错误，当前代码中未使用。
     */
    /**
     * @locale en
     * @hidden currently not available
     * @brief  Function call order is wrong and is not used in the current code.
     */
    ByteRTSWarningCodeInvokeError = -2005,
    /**
     * @locale zh
     * @hidden for internal use only
     * @brief 调度异常，服务器返回的媒体服务器地址不可用。
     */
    /**
     * @locale en
     * @hidden for internal use only
     * @brief Scheduling exception, the media server address returned by the server is unavailable.
     */
    ByteRTSWarningCodeInvalidExpectMediaServerAddress = -2007,
    /**
     * @locale zh
     * @brief 发送自定义广播消息失败，当前你未在房间中。
     */
    /**
     * @locale en
     * @brief Sending a custom broadcast message failed, you are not currently in the room.
     */
    ByteRTSWarningCodeSendCustomMessage = -2011,
    /**
     * @locale zh
     * @hidden
     * @deprecated since 3.46 and will be deleted in 3.52.
     * @brief 同样roomid的房间已经存在了
     */
    /**
     * @locale en
     * @hidden
     * @deprecated since 3.46 and will be deleted in 3.52.
     * @brief there is a room with the same roomId
     */
    ByteRTSWarningCodeRoomAlreadyExist = -2015,

    /**
     * @locale zh
     * @brief 新生成的房间已经替换了同样roomId的旧房间
     */
    /**
     * @locale en
     * @brief The old room has been replaced by new room with the same roomId
     */
    ByteRTSWarningCodeOldRoomBeenReplaced = -2016
};

/**
 * @locale zh
 * @type keytype
 * @brief 日志级别。
 */
/**
 * @locale en
 * @type keytype
 * @brief Log level.
 */
typedef NS_ENUM(NSUInteger, ByteRTCLogLevel) {
    /**
     * @locale zh
     * @brief 打印 trace 级别及以上级别信息。
     */
    /**
     * @locale en
     * @brief Print trace level and above information.
     */
    ByteRTCLogLevelTrace,
    /**
     * @locale zh
     * @brief 打印 debug 级别及以上级别信息。
     */
    /**
     * @locale en
     * @brief  Print debug level and above information.
     */
    ByteRTCLogLevelDebug,
    /**
     * @locale zh
     * @brief 打印 info 级别及以上级别信息。
     */
    /**
     * @locale en
     * @brief  Print info level and above information.
     */
    ByteRTCLogLevelInfo,
    /**
     * @locale zh
     * @brief 打印 warning 级别及以上级别信息。
     */
    /**
     * @locale en
     * @brief  Print warning level and above information.
     */
    ByteRTCLogLevelWarning,
    /**
     * @locale zh
     * @brief 打印 error 级别信息。
     */
    /**
     * @locale en
     * @brief  Print error level information.
     */
    ByteRTCLogLevelError,
};

/**
 * @locale zh
 * @type errorcode
 * @brief 登录结果  <br>
 *        调用 `login:uid:` 登录的结果，会通过 `rtcEngine:onLoginResult:errorCode:elapsed:` 回调通知用户。
 */
/**
 * @locale en
 * @type errorcode
 * @brief  Login result   <br>
 *        The result of calling `login:uid:` will notify the user through `rtcEngine:onLoginResult:errorCode:elapsed:` callback.
 */
typedef NS_ENUM(NSInteger, ByteRTCLoginErrorCode) {
    /**
     * @locale zh
     * @brief 调用 `login:uid:` 方法登录成功。
     */
    /**
     * @locale en
     * @brief Call the `login:uid:` method to log in successfully.
     */
    ByteRTCLoginErrorCodeSuccess = 0,
    /**
     * @locale zh
     * @brief 调用 `login:uid:` 方法时使用的 Token 无效或过期失效。需要用户重新获取 Token。
     */
    /**
     * @locale en
     * @brief The token used when calling the `login:uid:` method is invalid or expired. The user is required to re-acquire the token.
     */
    ByteRTCLoginErrorCodeInvalidToken = -1000,
    /**
     * @locale zh
     * @brief 登录错误  <br>
     *        调用 `login:uid:` 方法时发生未知错误导致登录失败。需要用户重新登录。
     */
    /**
     * @locale en
     * @brief Login error   <br>
     *        An unknown error occurred when calling the `login:uid:` method, which caused the login to fail. The user is required to log in again.
     */
    ByteRTCLoginErrorCodeLoginFailed = -1001,
    /**
     * @locale zh
     * @brief 调用 `login:uid:` 方法时传入的用户 ID 有问题。
     */
    /**
     * @locale en
     * @brief There was a problem with the incoming user ID when the `login:uid:` method was called.
     */
    ByteRTCLoginErrorCodeInvalidUserId = -1002,
    /**
     * @locale zh
     * @brief 调用 `login:uid:` 登录时服务器错误。
     */
    /**
     * @locale en
     * @brief Call `login:uid:` server error while logging in.
     */
    ByteRTCLoginErrorCodeServerError = -1003,
};

/**
 * @locale zh
 * @type keytype
 * @brief 用户登出的原因
 */
/**
 * @locale en
 * @type keytype
 * @brief The reason why users log out
 */
typedef NS_ENUM(NSUInteger, ByteRTCLogoutReason) {
    /**
     * @locale zh
     * @brief 用户主动退出<br>
     *        用户调用 `logout` 接口登出，或者销毁引擎登出。
     */
    /**
     * @locale en
     * @brief Users choose to logout by calling the `logout` to log out or terminating the engine to log out.
     */
    ByteRTCLogoutReasonLogout = 0,
    /**
     * @locale zh
     * @brief 用户被动退出<br>
     *        另一个用户以相同 UserId 进行了 `login`，导致本端用户被踢出。
     */
    /**
     * @locale en
     * @brief The current user is kicked out as another user logs in with the same UserId.
     */
    ByteRTCLogoutReasonDuplicateLogin = 1,
};

/**
 * @locale zh
 * @type keytype
 * @brief 发送消息的可靠有序类型
 */
/**
 * @locale en
 * @type keytype
 * @brief Reliable orderliness of sent messages
 */
typedef NS_ENUM(NSInteger, ByteRTCMessageConfig) {
    /**
     * @locale zh
     * @brief 低延时可靠有序消息
     */
    /**
     * @locale en
     * @brief Low latency reliable and orderly message
     */
    ByteRTCMessageConfigReliableOrdered = 0,
    /**
     * @locale zh
     * @brief 超低延时有序消息
     */
    /**
     * @locale en
     * @brief Ultra-low latency ordered message
     */
    ByteRTCMessageConfigUnreliableOrdered = 1,
    /**
     * @locale zh
     * @brief 超低延时无序消息
     */
    /**
     * @locale en
     * @brief Ultra-low latency unordered message
     */
    ByteRTCMessageConfigUnreliableUnordered = 2,
};

/**
 * @locale zh
 * @type errorcode
 * @brief 发送消息结果，成功或失败，及失败原因
 */
/**
 * @locale en
 * @type errorcode
 * @brief Result of sending messages and the reason of failure if it fails.
 */
typedef NS_ENUM(NSInteger, ByteRTCUserMessageSendResult) {
    /**
     * @locale zh
     * @brief 发送消息成功
     */
    /**
     * @locale en
     * @brief The message has been sent successfully.
     */
    ByteRTCUserMessageSendResultSuccess = 0,
    /**
     * @locale zh
     * @brief 发送超时，没有发送。
     */
    /**
     * @locale en
     * @brief Failure. Sending timeout.
     */
    ByteRTCUserMessageSendResultTimeout = 1,
    /**
     * @locale zh
     * @brief 通道断开，没有发送
     */
    /**
     * @locale en
     * @brief Failure. Channel disconnected.
     */
    ByteRTCUserMessageSendResultNetworkDisconnected = 2,
    /**
     * @locale zh
     * @brief 找不到接收方
     */
    /**
     * @locale en
     * @brief Failure. Recipient not found.
     */
    ByteRTCUserMessageSendResultNoReceiver = 3,
    /**
     * @locale zh
     * @brief 远端用户没有登录或进房
     */
    /**
     * @locale en
     * @brief Failure. The remote user did not logged in or joining the room.
     */
    ByteRTCUserMessageSendResultNoRelayPath = 4,
    /**
     * @locale zh
     * @brief 超过 QPS 限制
     */
    /**
     * @locale en
     * @brief Failure. Exceeds QPS limit.
     */
    ByteRTCUserMessageSendResultExceedQPS = 5,
    /**
     * @locale zh
     * @brief 消息发送失败。应用服务器未收到客户端发送的消息。<br>
     *        由 `sendServerMessage`/`sendServerBinaryMessage` 触发，通过 `onServerMessageSendResult` 回调。
     */
    /**
     * @locale en
     * @brief Failure. The app server failed to receive the message sent by the client.<br>
     *        Triggered by calling `sendServerMessage` or `sendServerBinaryMessage`, and carried by `onServerMessageSendResult` callback.
     */
    ByteRTCUserMessageSendResultE2BSSendFailed = 17,
    /**
     * @locale zh
     * @brief 消息发送失败。应用服务器接收到了客户端发送的消息，但响应失败。<br>
     *        由 `sendServerMessage`/`sendServerBinaryMessage` 触发，通过 `onServerMessageSendResult` 回调。
     */
    /**
     * @locale en
     * @brief Failure. The app server received the message sent by the client, but failed to response.<br>
     *        Triggered by calling `sendServerMessage` or `sendServerBinaryMessage`, and carried by `onServerMessageSendResult` callback.
     */
    ByteRTCUserMessageSendResultE2BSReturnFailed = 18,
    /**
     * @locale zh
     * @brief 消息发送方没有加入房间
     */
    /**
     * @locale en
     * @brief Failure. The sender of the message did not join the room
     */
    ByteRTCUserMessageSendResultNotJoin = 100,
    /**
     * @locale zh
     * @brief 连接未完成初始化
     */
    /**
     * @locale en
     * @brief Failure. Connection initialization not completed
     */
    ByteRTCUserMessageSendResultInit = 101,
    /**
     * @locale zh
     * @brief 没有可用的数据传输通道连接
     */
    /**
     * @locale en
     * @brief Failure. No data transmission channel connection available
     */
    ByteRTCUserMessageSendResultNoConnection = 102,
    /**
     * @locale zh
     * @brief 消息超过最大长度，当前为64KB
     */
    /**
     * @locale en
     * @brief Failure. Message exceeds the range of the permitted size, 64 KB.
     */
    ByteRTCUserMessageSendResultExceedMaxLength = 103,
    /**
     * @locale zh
     * @brief 接收消息的单个用户 id 为空
     */
    /**
     * @locale en
     * @brief Failure. The id of the recipient is empty
     */
    ByteRTCUserMessageSendResultEmptyUser = 104,
    /**
     * @locale zh
     * @brief 房间外或应用服务器消息发送方没有登录
     */
    /**
     * @locale en
     * @brief Failure. The sender of the message did not log in.
     */
    ByteRTCUserMessageSendResultNotLogin = 105,
    /**
     * @locale zh
     * @brief 发送消息给业务方服务器之前没有设置参数
     */
    /**
     * @locale en
     * @brief Failure. No parameters were set before sending the message to the server
     */
    ByteRTCUserMessageSendResultServerParamsNotSet = 106,
    /**
     * @locale zh
     * @brief 失败，未知错误。
     */
    /**
     * @locale en
     * @brief Failure. Unknown error.
     */
    ByteRTCUserMessageSendResultUnknown = 1000,
};

/**
 * @locale zh
 * @type keytype
 * @brief 用户在线状态
 */
/**
 * @locale en
 * @type keytype
 * @brief  User online status
 */
typedef NS_ENUM(NSInteger, ByteRTCUserOnlineStatus) {
    /**
     * @locale zh
     * @brief 对端用户离线<br>
     *        对端用户已经调用 `logout`，或者没有调用 `login:uid:` 进行登录
     */
    /**
     * @locale en
     * @brief The peer user is offline<br>
     *        The peer user has called `logout`, or has not called `login:uid:` to log in
     */
    ByteRTCUserOnlineStatusOffline = 0,
    /**
     * @locale zh
     * @brief 对端用户在线<br>
     *        对端用户调用 `login:uid:` 登录，并且连接状态正常
     */
    /**
     * @locale en
     * @brief The peer user is online<br>
     *        The peer user calls `login:uid:` to log in and the connection status is normal
     */
    ByteRTCUserOnlineStatusOnline = 1,
    /**
     * @locale zh
     * @brief 无法获取对端用户在线状态<br>
     *        发生级联错误、对端用户在线状态异常时返回
     */
    /**
     * @locale en
     * @brief Unable to get the online state of the peer user<br>
     *        Returned when a cascade error occurs and the online state of the peer user is abnormal
     */
    ByteRTCUserOnlineStatusUnreachable = 2,
};

/**
 * @locale zh
 * @type errorcode
 * @brief 房间内广播消息发送结果
 */
/**
 * @locale en
 * @type errorcode
 * @brief Result of broadcasting messages in the room
 */
typedef NS_ENUM(NSInteger, ByteRTCRoomMessageSendResult) {
    /**
     * @locale zh
     * @brief 消息发送成功
     */
    /**
     * @locale en
     * @brief The message sent successfully.
     */
    ByteRTCRoomMessageSendResultSuccess = 200,
    /**
     * @locale zh
     * @brief 发送超时，没有发送
     */
    /**
     * @locale en
     * @brief Failure. Sending timeout.
     */
    ByteRTCRoomMessageSendResultTimeout = 1,
    /**
     * @locale zh
     * @brief 通道断开，没有发送
     */
    /**
     * @locale en
     * @brief Failure. Channel disconnected.
     */
    ByteRTCRoomMessageSendResultNetworkDisconnected = 2,
    /**
     * @locale zh
     * @brief 超过 QPS 限制
     */
    /**
     * @locale en
     * @brief Failure. Exceeds QPS limit.
     */
    ByteRTCRoomMessageSendResultExceedQPS = 5,
    /**
     * @locale zh
     * @brief 失败，发送方未加入房间
     */
    /**
     * @locale en
     * @brief Failure. The sender has not joined a room.
     */
    ByteRTCRoomMessageSendResultNotJoin = 100,
    /**
     * @locale zh
     * @brief 失败，连接未完成初始化。
     */
    /**
     * @locale en
     * @brief Failure. The connection has not completed initialization.
     */
    ByteRTCRoomMessageSendResultInit = 101,
    /**
     * @locale zh
     * @brief 失败，没有可用的连接。
     */
    /**
     * @locale en
     * @brief Failure. No connection available.
     */
    ByteRTCRoomMessageSendResultNoConnection = 102,
    /**
     * @locale zh
     * @brief 消息超过最大长度，当前为 64KB
     */
    /**
     * @locale en
     * @brief Failure. Message exceeds the range of the permitted size, 64 KB.
     */
    ByteRTCRoomMessageSendResultExceedMaxLength = 103,
    /**
     * @locale zh
     * @brief 失败，未知错误。
     */
    /**
     * @locale en
     * @brief Failure. Unknown error.
     */
    ByteRTCRoomMessageSendResultUnknown = 1000,
};

/**
 * @locale zh
 * @hidden for internal use only
 * @type keytype
 * @brief SDK 的服务器环境。
 */
/**
 * @locale en
 * @hidden for internal use only
 * @type keytype
 * @brief SDK server environment.
 */
typedef NS_ENUM(NSInteger, ByteRTCEnv) {
    /**
     * @locale zh
     * @brief 线上环境。
     */
    /**
     * @locale en
     * @brief Online environment.
     */
    ByteRTCEnvProduct = 0,
    /**
     * @locale zh
     * @brief BOE 环境。
     */
    /**
     * @locale en
     * @brief BOE environment.
     */
    ByteRTCEnvBOE = 1,
    /**
     * @locale zh
     * @brief 测试环境。
     */
    /**
     * @locale en
     * @brief Test environment.
     */
    ByteRTCEnvTest = 2,
};

/**
 * @locale zh
 * @type keytype
 * @brief 本地日志输出等级。
 */
/**
 * @locale en
 * @type keytype
 * @brief Local log parameters.
 */
typedef NS_ENUM(NSUInteger, ByteRTCLocalLogLevel) {
    /**
     * @locale zh
     * @brief 信息级别。
     */
    /**
     * @locale en
     * @brief Info level.
     */
    ByteRTCLocalLogLevelInfo = 0,
    /**
     * @locale zh
     * @brief （默认值）警告级别。
     */
    /**
     * @locale en
     * @brief (Default) Warning level.
     */
    ByteRTCLocalLogLevelWarning = 1,
    /**
     * @locale zh
     * @brief 错误级别。
     */
    /**
     * @locale en
     * @brief Error level.
     */
    ByteRTCLocalLogLevelError = 2,
    /**
     * @locale zh
     * @brief 关闭日志。
     */
    /**
     * @locale en
     * @brief Turn off logging.
     */
    ByteRTCLocalLogLevelNone = 3
};

/**
 * @locale zh
 * @type keytype
 * @brief App 使用的 cpu 和 memory 信息  <br>
 *        信息由 SDK 周期性（2s）地通过 `reportSysStats` 回调事件通知给用户。
 */
/**
 * @locale en
 * @type keytype
 * @brief The cpu and memory information used by App  <br>
 *         Information is periodically (2s) notified to the user by the SDK via the `reportSysStats` callback event.
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCSysStats : NSObject
/**
 * @locale zh
 * @brief 当前系统 cpu 核数
 */
/**
 * @locale en
 * @brief Current system cpu number
 */
@property(assign, nonatomic) unsigned int cpuCores;
/**
 * @locale zh
 * @brief 当前应用的 CPU 使用率，取值范围为 [0, 1]。
 */
/**
 * @locale en
 * @brief The CPU usage of the current application, the value range is [0,1].
 */
@property(assign, nonatomic) double cpuAppUsage;
/**
 * @locale zh
 * @hidden currently not available
 * @brief 当前系统的 CPU 使用率，取值范围为 [0, 1]。
 */
/**
 * @locale en
 * @hidden currently not available
 * @brief The current system CPU usage, the value range is [0,1].
 */
@property(assign, nonatomic) double cpuTotalUsage;
/**
 * @locale zh
 * @brief 当前App的内存使用（单位 MB）
 */
/**
 * @locale en
 * @brief Memory usage of the current app (in MB)
 */
@property(assign, nonatomic) double memoryUsage;
/**
 * @locale zh
 * @brief 全量内存（单位MB）
 */
/**
 * @locale en
 * @brief Full memory (in MB)
 */
@property(assign, nonatomic) unsigned long long fullMemory;
/**
 * @locale zh
 * @brief 系统已使用内存（单位MB）
 */
/**
 * @locale en
 * @brief System used memory (in MB)
 */
@property(assign, nonatomic) unsigned long long totalMemoryUsage;
/**
 * @locale zh
 * @brief 空闲可分配内存（单位MB）
 */
/**
 * @locale en
 * @brief Free allocable memory (in MB)
 */
@property(assign, nonatomic) unsigned long long freeMemory;
/**
 * @locale zh
 * @brief 当前应用的内存使用率（单位 %）
 */
/**
 * @locale en
 * @brief Memory usage of the current application (in %)
 */
@property(assign, nonatomic) double memoryRatio;
/**
 * @locale zh
 * @brief 系统内存使用率（单位 %）
 */
/**
 * @locale en
 * @brief System memory usage (in %)
 */
@property(assign, nonatomic) double totalMemoryRatio;
@end

/**
 * @locale zh
 * @type keytype
 * @brief 本地日志参数。
 */
/**
 * @locale en
 * @type keytype
 * @brief Local log parameters.
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCLogConfig : NSObject
/**
 * @locale zh
 * @brief 日志存储路径，必填。
 */
/**
 * @locale en
 * @brief (Required) Local log directory.
 */
@property(copy, nonatomic) NSString *_Nonnull logPath;

/**
 * @locale zh
 * @brief 日志等级，参看 ByteRTCLocalLogLevel{@link #ByteRTCLocalLogLevel}，默认为警告级别，选填。
 */
/**
 * @locale en
 * @brief (Optional) The logging level. See ByteRTCLocalLogLevel{@link #ByteRTCLocalLogLevel}. The default is warning level.
 */
@property(assign, nonatomic) ByteRTCLocalLogLevel logLevel;

/**
 * @locale zh
 * @brief 日志文件最大占用的总空间，单位为 MB，选填。取值范围为 1～100 MB，默认值为 10 MB。<br>
 *        若 `logFileSize` < 1，取 1 MB。若 `logFileSize` > 100，取 100 MB。<br>
 *        其中，单个日志文件最大为 2 MB：<br>
 *        <ul><li> 若 1 ≤ <code>logFileSize</code> ≤ 2，则会生成一个日志文件。</li><li>若 <code>logFileSize</code> > 2，假设 <code>logFileSize/2</code> 的整数部分为 N，则前 N 个文件，每个文件会写满 2 MB，第 N+1 个文件大小不超过 <code>logFileSize mod 2</code>，否则会删除最老的文件，以此类推。</li></ul>
 */
/**
 * @locale en
 * @brief (Optional) The limits for total log file size in MB. The range is 1 to 100 MB, and the default value is 10 MB.<br>
 *        If `logFileSize` < 1, it will be set to 1 MB. If `logFileSize` > 100, it will be set to 100 MB. <br>
 *        The maximum size for a single log file is 2 MB.<br>
 *        If 1 ≤ `logFileSize` ≤ 2, one log file will be generated. If `logFileSize` > 2, the first `⌊logFileSize/2⌋` files will be filled with 2 MB each, the `⌊logFileSize/2⌋+1` fill will be filled with `logFileSize mod 2`.<br>
 *        If the size exceeds the remaining space, the oldest file will be deleted.
 */
@property(assign, nonatomic) int logFileSize;

/**
 * @locale zh
 * @brief 日志文件名前缀，选填。该字符串必须符合正则表达式：[a-zA-Z0-9_@\-\.]{1,128}。<br>
 *        最终的日志文件名为`前缀 + "_" + 文件创建时间 + "_rtclog".log`，如 `logPrefix_2023-05-25_172324_rtclog.log`。
 */
/**
 * @locale en
 * @brief (Optional) Local log file name prefix. It should follow the regular expression pattern of `[a-zA-Z0-9_@-.]{1,128}`.<br>
 *        The final file name will be the prefix followed by "_" and the file creation time, and "_rtclog.log" at the end. For example, `logPrefix_2023-05-25_172324_rtclog.log`.
 */
@property(copy, nonatomic) NSString *_Nonnull logFilenamePrefix;
@end

/**
 * @locale zh
 * @hidden for internal use only
 * @type callback
 * @region 监控
 * @brief 非业务相关的监控事件回调
 */
/**
 * @locale en
 * @hidden for internal use only
 * @type callback
 * @region  monitoring
 * @brief  Non-business related monitoring event callback
 */
@protocol ByteRTCMonitorDelegate <NSObject>
@optional
/**
 * @locale zh
 * @type callback
 * @region 监控
 * @brief 埋点日志回调  
 * @param data  <br>
 *        具体的埋点内容  
 * @param type  <br>
 *        埋点的类型
 */
/**
 * @locale en
 * @type callback
 * @region monitoring
 * @brief Event tracking log callback   
 * @param data   <br>
 *        Specific event tracking content 
 * @param type   <br>
 *        Event tracking type
 */
- (void)onMonitorLog:(NSDictionary * _Nullable)data withType:(NSString * _Nullable)type;

/**
 * @locale zh
 * @type api
 * @region 监控
 * @brief 是否进行控制台输出
 * @return
 *        返回是否进行控制台输出  <br>
 *        + YES 输出所有的日志到控制台  <br>
 *        + NO 不输出任何控制台信息
 */
/**
 * @locale en
 * @type api
 * @region  monitor
 * @brief  Whether to output from the console
 * @return
 *         Return whether to output from the console <br>
 *         + YES output all logs to the console <br>
 *         + NO output no console information
 */
- (BOOL)isConsole;

/**
 * @locale zh
 * @type callback
 * @region 监控
 * @brief 输出更多的调试信息
 */
/**
 * @locale en
 * @type callback
 * @region  monitor
 * @brief  Output more debugging information
 */
- (void)onVerboseLogWithLevel:(ByteRTCLogLevel)level
                     filename:(NSString * _Nonnull)filename
                          tag:(NSString * _Nonnull)tag
                         line:(int)line
                 functionName:(NSString * _Nonnull)funcName
                       format:(NSString * _Nonnull)format;
@end

/**
 * @locale zh
 * @type keytype
 * @brief 云代理信息
 */
/**
 * @locale en
 * @type keytype
 * @brief Cloud Proxy Information
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCCloudProxyInfo: NSObject
/**
 * @locale zh
 * @type keytype
 * @brief 云代理服务器 IP
 */
/**
 * @locale en
 * @type keytype
 * @brief Cloud proxy IP
 */
@property(strong, nonatomic) NSString* _Nonnull cloudProxyIp;
/**
 * @locale zh
 * @type keytype
 * @brief 云代理服务器端口
 */
/**
 * @locale en
 * @type keytype
 * @brief Cloud proxy Port
 */
@property(assign, nonatomic) int cloudProxyPort;
@end

/**
 * @locale zh
 * @type keytype
 * @brief 本地代理的类型。
 */
/**
 * @locale en
 * @type keytype
 * @brief Types of local proxies.
 */
typedef NS_ENUM(NSUInteger, ByteRTCLocalProxyType) {
    /**
     * @locale zh
     * @brief Socks5 代理。选用此代理服务器，需满足 Socks5 协议标准文档的要求。
     */
    /**
     * @locale en
     * @brief Socks5 proxy. If you chose Socks5 as the local proxy, you need to make sure all requirements listed in the Socks5 document are satisfied. 
     */
    ByteRTCLocalProxyTypeSocks5 = 1,
    /**
     * @locale zh
     * @brief Http 隧道代理。
     */
    /**
     * @locale en
     * @brief Http tunnel proxy.
     */
    ByteRTCLocalProxyTypeHttpTunnel = 2,
};

/**
 * @locale zh
 * @type keytype
 * @brief 本地代理配置详细信息。
 */
/**
 * @locale en
 * @type keytype
 * @brief Detailed information of local proxy configurations.
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCLocalProxyInfo : NSObject
/**
 * @locale zh
 * @brief 本地代理的类型，参看 ByteRTCLocalProxyType{@link #ByteRTCLocalProxyType}。
 */
/**
 * @locale en
 * @brief Types of the local proxies. Refer to ByteRTCLocalProxyType{@link #ByteRTCLocalProxyType} for details.
 */
@property(assign, nonatomic) ByteRTCLocalProxyType localProxyType;
/**
 * @locale zh
 * @type keytype
 * @brief 本地代理服务器 IP。
 */
/**
 * @locale en
 * @type keytype
 * @brief Local proxy IP.
 */
@property(copy, nonatomic) NSString * _Nullable localProxyIp;
/**
 * @locale zh
 * @type keytype
 * @brief 本地代理服务器端口。
 */
/**
 * @locale en
 * @type keytype
 * @brief Local proxy port.
 */
@property(assign, nonatomic) int localProxyPort;
 /**
  * @locale zh
  * @type keytype
  * @brief 本地代理用户名。
  */
 /**
  * @locale en
  * @type keytype
  * @brief The username of the local proxy.
  */
@property(copy, nonatomic) NSString * _Nullable localProxyUsername;
 /**
  * @locale zh
  * @brief 本地代理密码。
  */
 /**
  * @locale en
  * @brief The password of the local proxy.
  */
@property(copy, nonatomic) NSString * _Nullable localProxyPassword;
@end

/**
 * @locale zh
 * @type keytype
 * @brief 本地代理连接状态。
 */
/**
 * @locale en
 * @type keytype
 * @brief The states of local proxy connection.
 */
typedef NS_ENUM(NSUInteger, ByteRTCLocalProxyState) {
    /**
     * @locale zh
     * @brief TCP 代理服务器连接成功。
     */
    /**
     * @locale en
     * @brief TCP proxy server is connected.
     */
    ByteRTCLocalProxyStateInited = 0,

    /**
     * @locale zh
     * @brief 本地代理连接成功。
     */
    /**
     * @locale en
     * @brief The local proxy is connected.
     */
    ByteRTCLocalProxyStateConnected = 1,

    /**
     * @locale zh
     * @brief 本地代理连接出现错误。
     */
    /**
     * @locale en
     * @brief Errors occurred when connecting to the local proxy.  
     */
    ByteRTCLocalProxyStateError = 2,
};

/**
 * @locale zh
 * @type keytype
 * @brief 本地代理错误。
 */
/**
 * @locale en
 * @type keytype
 * @brief The errors of local proxy connection.
 */
typedef NS_ENUM(NSUInteger, ByteRTCLocalProxyError) {
    /**
     * @locale zh
     * @brief 本地代理服务器无错误。
     */
    /**
     * @locale en
     * @brief There are no errors in local proxies. 
     */
    ByteRTCLocalProxyErrorOK = 0,

    /**
     * @locale zh
     * @brief 代理服务器回复的版本号不符合 Socks5 协议标准文档的规定，导致 Socks5 代理连接失败。请检查代理服务器是否存在异常。
     */
    /**
     * @locale en
     * @brief The connection to Socks5 proxy failed because the proxy server replies wrong version numbers which don't accord with the Socks5 document. Please check the proxy server. 
     */
    ByteRTCLocalProxyErrorSocks5VersionError = 1,

    /**
     * @locale zh
     * @brief 代理服务器回复的格式错误不符合 Socks5 协议标准文档的规定，导致 Socks5 代理连接失败。请检查代理服务器是否存在异常。
     */
    /**
     * @locale en
     * @brief The connection to Socks5 proxy failed because the format of the proxy's replies doesn't accord with the Socks5 document. Please check the proxy server. 
     */
    ByteRTCLocalProxyErrorSocks5FormatError = 2,

    /**
     * @locale zh
     * @brief 代理服务器回复的字段值不符合 Socks5 协议标准文档的规定，导致 Socks5 代理连接失败。请检查代理服务器是否存在异常。
     */
    /**
     * @locale en
     * @brief The connection to Socks5 proxy failed because the proxy replies wrong information which doesn't accord with the Socks5 document. Please check the proxy server. 
     */
    ByteRTCLocalProxyErrorSocks5InvalidValue = 3,

    /**
     * @locale zh
     * @brief 未提供代理服务器的用户名及密码，导致 Socks5 代理连接失败。请重新调用 `setLocalProxy`，在设置本地代理时填入用户名和密码。
     */
    /**
     * @locale en
     * @brief The connection to Socks5 proxy failed because the username and password of the local proxy are not provided. Please call `setLocalProxy` and enter your username and password. 
     */
    ByteRTCLocalProxyErrorSocks5UserPassNotGiven = 4,

    /**
     * @locale zh
     * @brief TCP 关闭，导致 Socks5 代理连接失败。请检查网络或者代理服务器是否存在异常。
     */
    /**
     * @locale en
     * @brief The connection to Socks5 proxy failed because TCP is closed. Please check the proxy server and your network connection status.
     */
    ByteRTCLocalProxyErrorSocks5TcpClosed = 5,

    /**
     * @locale zh
     * @brief Http 隧道代理错误。请检查 Http 隧道代理服务器或者网络是否存在异常。
     */
    /**
     * @locale en
     * @brief Errors in Http tunnel proxy. Please check Http tunnel proxy and your network connection status.
     */
    ByteRTCLocalProxyErrorHttpTunnelFailed = 6,
};

