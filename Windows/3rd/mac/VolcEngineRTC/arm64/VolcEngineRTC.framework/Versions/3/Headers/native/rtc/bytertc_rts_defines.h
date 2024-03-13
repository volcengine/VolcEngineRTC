/*
 * Copyright (c) 2022 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC Common Defines
 */

#pragma once

#ifdef WIN32
#define BYTERTC_API extern "C" __declspec(dllexport)
#elif defined(__APPLE__)
#include <TargetConditionals.h>
#if TARGET_OS_MAC && !(TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
#define BYTERTC_API __attribute__((__visibility__("default"))) extern "C"
#else
#define BYTERTC_API __attribute__((__visibility__("default")))
#endif
#else
#define BYTERTC_API __attribute__((__visibility__("default")))
#endif

#ifdef __GNUC__
#    define GCC_VERSION_AT_LEAST(x,y) (__GNUC__ > (x) || __GNUC__ == (x) && __GNUC_MINOR__ >= (y))
#else
#    define GCC_VERSION_AT_LEAST(x,y) 0
#endif

#if GCC_VERSION_AT_LEAST(3,1)
#    define BYTERTC_DEPRECATED __attribute__((deprecated))
#elif defined(_MSC_VER)
#    define BYTERTC_DEPRECATED __declspec(deprecated)
#else
#    define BYTERTC_DEPRECATED
#endif

#include <stdint.h>
#include <stddef.h>

namespace bytertc {


/**
 * @hidden currently not available
 */
enum RtsReturnStatus {

    kRtsReturnStatusSuccess = 0,

    kRtsReturnStatusFailure = -1,

    kRtsReturnStatusParameterErr = -2,

    kRtsReturnStatusWrongState = -3,

    kRtsReturnStatusHasInRoom = -4,

    kRtsReturnStatusHasInLogin = -5,

    kRtsReturnStatusRoomIdInUse = -8,

};

/**
 * @locale zh
 * @type keytype
 * @brief 用户离开房间的原因。  
 */
/**
 * @locale en
 * @type keytype
 * @brief  The reason why the user left the room.   
 */
enum UserOfflineReason {
    /**
     * @locale zh
     * @brief 远端用户调用 `leaveRoom` 方法退出房间。  
     */
    /**
     * @locale en
     * @brief The remote user calls `leaveRoom` to exit the room. 
     */
    kUserOfflineReasonQuit = 0,
    /**
     * @locale zh
     * @brief 远端用户因网络等原因掉线。  
     */
    /**
     * @locale en
     * @brief The remote user is offline.   
     */
    kUserOfflineReasonDropped = 1,
    /**
     * @locale zh
     * @brief 远端用户切换至隐身状态。  
     */
    /**
     * @locale en
     * @brief The remote user switches to invisible.   
     */
    kUserOfflineReasonSwitchToInvisible = 2,
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
    kUserOfflineReasonKickedByAdmin = 3,
};

/**
 * @locale zh
 * @type keytype
 * @brief 用户加入房间的类型。  
 */
/**
 * @locale en
 * @type keytype
 * @brief The type of joining the room.   
 */
enum JoinRoomType {
    /**
     * @locale zh
     * @brief 首次加入房间。用户手动调用 `joinRoom` 加入房间。  
     */
    /**
     * @locale en
     * @brief Join the room for the first time. The user calls `joinRoom` to join the room. 
     */
    kJoinRoomTypeFirst = 0,
    /**
     * @locale zh
     * @brief 重新加入房间。用户网络较差，失去与服务器的连接，进行重连时收到加入成功。  
     */
    /**
     * @locale en
     * @brief Rejoin the room. The user loses connection to the server due to poor network, and rejoins the room successfully.   
     */
    kJoinRoomTypeReconnected = 1,
};

/**
 * @locale zh
 * @type keytype
 * @brief 用户登录的类型
 */
/**
 * @locale en
 * @type keytype
 * @brief  The type of user login
 */
enum LoginType {
    /**
     * @locale zh
     * @brief 首次登录。用户手动调用 `login`，收到登录成功。
     */
    /**
     * @locale en
     * @brief login for the first time. The user manually called `login` and received a successful login.
     */
    kLoginTypeFirst = 0,
    /**
     * @locale zh
     * @brief 重连。用户网络较差，失去与服务器的连接，SDK 自动重连登录成功。
     */
    /**
     * @locale en
     * @brief Reconnect. User network is poor, lost connection with the server, SDK  automatically reconnect login success.
     */
    kLoginTypeReconnected = 1,
};

/**
 * @locale zh
 * @type errorcode
 * @brief 登录结果  <br>
 *        调用 `login` 登录的结果，会通过 `onLoginResult` 回调通知用户。
 */
/**
 * @locale en
 * @type errorcode
 * @brief login result   <br>
 *        The result of calling `login` will notify the user through the `onLoginResult` callback.
 */
enum LoginErrorCode {
    /**
     * @locale zh
     * @brief 调用 `login` 方法登录成功
     */
    /**
     * @locale en
     * @brief Call the `login` method to log in successfully
     */
    kLoginErrorCodeSuccess = 0,
    /**
     * @locale zh
     * @brief 调用 `login` 方法时使用的 Token 无效或过期失效，需要用户重新获取 Token。
     */
    /**
     * @locale en
     * @brief The Token used when calling the `login` method is invalid or expired, requiring the user to reacquire the Token.
     */
    kLoginErrorCodeInvalidToken = -1000,
    /**
     * @locale zh
     * @brief 登录错误  <br>
     *        调用 `login` 方法时发生未知错误导致登录失败，需要重新登录。
     */
    /**
     * @locale en
     * @brief login error   <br>
     *        An unknown error occurred when calling the `login` method, which caused the login to fail and requires re-login.
     */
    kLoginErrorCodeLoginFailed = -1001,
    /**
     * @locale zh
     * @brief 调用 `login` 方法时传入的用户 ID 有问题。
     */
    /**
     * @locale en
     * @brief There was a problem with the user ID passed in when the `login` method was called.
     */
    kLoginErrorCodeInvalidUserId = -1002,
    /**
     * @locale zh
     * @brief 调用 `login` 登录时服务端出错。
     */
    /**
     * @locale en
     * @brief An error occurred at the server level when calling `login` to log in.
     */
    kLoginErrorCodeServerError = -1003,
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
enum LogoutReason {
    /**
     * @locale zh
     * @brief 用户主动退出<br>
     *        用户调用 `logout` 接口登出，或者销毁引擎登出。
     */
    /**
     * @locale en
     * @brief Users choose to logout by calling the `logout` to log out or terminating the engine to log out.
     */
    kLogoutReasonLogout = 0,
    /**
     * @locale zh
     * @brief 用户被动退出<br>
     *        另一个用户以相同 UserId 进行了 `login`，导致本端用户被踢出。
     */
    /**
     * @locale en
     * @brief The current user is kicked out as another user logs in with the same UserId.
     */
    kLogoutReasonDuplicateLogin = 1,
};

/**
 * @locale zh
 * @type keytype
 * @brief 用户在线状态。
 */
/**
 * @locale en
 * @type keytype
 * @brief User online status.
 */
enum UserOnlineStatus {
    /**
     * @locale zh
     * @brief 对端用户离线  <br>
     *        对端用户已调用 `logout`，或者没有调用 `login` 进行登录。
     */
    /**
     * @locale en
     * @brief The peer user is offline   <br>
     *         The peer user has called `logout`, or has not called `login` to log in.
     */
    kUserOnlineStatusOffline = 0,
    /**
     * @locale zh
     * @brief 对端用户在线  <br>
     *        对端用户调用 `login` 登录，并且连接状态正常。
     */
    /**
     * @locale en
     * @brief The peer user is online   <br>
     *         The peer user calls `login` to log in, and the connection status is normal.
     */
    kUserOnlineStatusOnline = 1,
    /**
     * @locale zh
     * @brief 无法获取对端用户在线状态  <br>
     *        发生级联错误、对端用户在线状态异常时返回。
     */
    /**
     * @locale en
     * @brief Unable to get the online state of the peer user   <br>
     *        Returned when a cascade error occurs and the online state of the peer user is abnormal.
     */
    kUserOnlineStatusUnreachable = 2,
};

/**
 * @locale zh
 * @type keytype
 * @brief 服务端消息发送结果回调内容
 */
/**
 * @locale en
 * @type keytype
 * @brief  Server message send result content
 */
struct ServerACKMsg {
    /**
     * @locale zh
     * @brief 回调消息长度
     */
    /**
     * @locale en
     * @brief length
     */
    int length;
    /**
     * @locale zh
     * @brief 回调消息内容
     */
    /**
     * @locale en
     * @brief content of the message
     */
    char* ack_msg;
};

/**
 * @locale zh
 * @type keytype
 * @brief 消息类型
 */
/**
 * @locale en
 * @type keytype
 * @brief Message type
 */
enum MessageConfig {
    /**
     * @locale zh
     * @brief 低延时可靠有序消息
     */
    /**
     * @locale en
     * @brief Low latency reliable and orderly message
     */
    kMessageConfigReliableOrdered = 0,
    /**
     * @locale zh
     * @brief 超低延时有序消息
     */
    /**
     * @locale en
     * @brief Ultra-low latency ordered message
     */
    kMessageConfigUnreliableOrdered = 1,
    /**
     * @locale zh
     * @brief 超低延时无序消息
     */
    /**
     * @locale en
     * @brief Ultra-low latency unordered message
     */
    kMessageConfigUnreliableUnordered = 2
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
enum UserMessageSendResult {
    /**
     * @locale zh
     * @brief 发送消息成功
     */
    /**
     * @locale en
     * @brief The message has been sent successfully.
     */
    kUserMessageSendResultSuccess = 0,
    /**
     * @locale zh
     * @brief 发送超时，没有发送成功
     */
    /**
     * @locale en
     * @brief Failure. Sending timeout.
     */
    kUserMessageSendResultTimeout = 1,
    /**
     * @locale zh
     * @brief 通道断开，没有发送
     */
    /**
     * @locale en
     * @brief Failure. Channel disconnected.
     */
    kUserMessageSendResultNetworkDisconnected = 2,
    /**
     * @locale zh
     * @brief 找不到接收方
     */
    /**
     * @locale en
     * @brief Failure. Recipient not found.
     */
    kUserMessageSendResultNoReceiver = 3,
    /**
     * @locale zh
     * @brief 远端用户没有登录或进房
     */
    /**
     * @locale en
     * @brief Failure. The remote user did not logged in or joining the room.
     */
    kUserMessageSendResultNoRelayPath = 4,
    /**
     * @locale zh
     * @brief 超过 QPS 限制
     */
    /**
     * @locale en
     * @brief Failure. Exceeds QPS limit.
     */
    kUserMessageSendResultExceedQPS = 5,
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
    kUserMessageSendResultE2BSSendFailed = 17,
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
    kUserMessageSendResultE2BSReturnFailed = 18,
    /**
     * @locale zh
     * @brief 消息发送方没有加入房间
     */
    /**
     * @locale en
     * @brief Failure. The sender of the message did not join the room
     */
    kUserMessageSendResultNotJoin = 100,
    /**
     * @locale zh
     * @brief 连接未完成初始化,没有可用的数据传输通道连接
     */
    /**
     * @locale en
     * @brief Failure. Connection initialization not completed
     */
    kUserMessageSendResultInit = 101,
    /**
     * @locale zh
     * @brief 没有可用的数据传输通道连接
     */
    /**
     * @locale en
     * @brief Failure. No data transmission channel connection available
     */
    kUserMessageSendResultNoConnection = 102,
    /**
     * @locale zh
     * @brief 消息超过最大长度，当前为 64 KB
     */
    /**
     * @locale en
     * @brief Failure. Message exceeds the range of the permitted size, 64 KB.
     */
    kUserMessageSendResultExceedMaxLength = 103,
    /**
     * @locale zh
     * @brief 接收消息的单个用户 id 为空
     */
    /**
     * @locale en
     * @brief Failure. The id of the recipient is empty
     */
    kUserMessageSendResultEmptyUser = 104,
    /**
     * @locale zh
     * @brief 房间外或应用服务器消息发送方没有登录
     */
    /**
     * @locale en
     * @brief Failure. The sender of the message did not log in.
     */
    kUserMessageSendResultNotLogin = 105,
    /**
     * @locale zh
     * @brief 发送消息给业务方服务器之前没有设置参数
     */
    /**
     * @locale en
     * @brief Failure. No parameters were set before sending the message to the server
     */
    kUserMessageSendResultServerParamsNotSet = 106,
    /**
     * @locale zh
     * @brief 未知错误
     */
    /**
     * @locale en
     * @brief Failure. Unknown error
     */
    kUserMessageSendResultUnknown = 1000,
};

/**
 * @locale zh
 * @type keytype
 * @brief 房间内广播消息发送结果
 */
/**
 * @locale en
 * @type keytype
 * @brief Result of broadcasting messages in the room
 */
enum RoomMessageSendResult {
    /**
     * @locale zh
     * @brief 消息发送成功
     */
    /**
     * @locale en
     * @brief Message sent successfully.
     */
    kRoomMessageSendResultSuccess = 200,
    /**
     * @locale zh
     * @brief 发送超时，没有发送
     */
    /**
     * @locale en
     * @brief Failure. Sending timeout.
     */
    kRoomMessageSendResultTimeout = 1,
    /**
     * @locale zh
     * @brief 通道断开，没有发送
     */
    /**
     * @locale en
     * @brief Failure. Channel disconnected.
     */
    kRoomMessageSendResultNetworkDisconnected = 2,
    /**
     * @locale zh
     * @brief 超过 QPS 限制
     */
    /**
     * @locale en
     * @brief Failure. Exceeds QPS limit.
     */
    kRoomMessageSendResultExceedQPS = 5,
    /**
     * @locale zh
     * @brief 失败，发送方未加入房间
     */
    /**
     * @locale en
     * @brief Failure. The sender has not joined a room.
     */
    kRoomMessageSendResultNotJoin = 100,
    /**
     * @locale zh
     * @brief 失败，没有可用的数据传输通道连接
     */
    /**
     * @locale en
     * @brief Failure. No data transmission channel connection available
     */
    kRoomMessageSendResultNoConnection = 102,
    /**
     * @locale zh
     * @brief 失败，消息超过最大长度，当前为 64KB
     */
    /**
     * @locale en
     * @brief Failure. Message exceeds the range of the permitted size, 64 KB.
     */
    kRoomMessageSendResultExceedMaxLength = 103,
    /**
     * @locale zh
     * @brief 失败，未知错误
     */
    /**
     * @locale en
     * @brief Failure. Unknown error
     */
    kRoomMessageSendResultUnknown = 1000,
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
enum ConnectionState {
    /**
     * @locale zh
     * @brief 连接断开超过 12s，此时 SDK 会尝试自动重连。
     */
    /**
     * @locale en
     * @brief Disconnected for 12s, SDK will try to reconnect automatically.
     */
    kConnectionStateDisconnected = 1,
    /**
     * @locale zh
     * @brief 首次请求建立连接，正在连接中。
     */
    /**
     * @locale en
     * @brief The first request to connect to the server. Connecting.
     */
    kConnectionStateConnecting = 2,
    /**
     * @locale zh
     * @brief 首次连接成功。
     */
    /**
     * @locale en
     * @brief The first connection was successful.
     */
    kConnectionStateConnected = 3,
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
    kConnectionStateReconnecting = 4,
    /**
     * @locale zh
     * @brief 连接断开后，重连成功。
     */
    /**
     * @locale en
     * @brief Successful reconnection after disconnection.
     */
    kConnectionStateReconnected = 5,
    /**
     * @locale zh
     * @brief 处于 `kConnectionStateDisconnected` 状态超过 10 秒，且期间重连未成功。SDK 仍将继续尝试重连。
     */
    /**
     * @locale en
     * @brief In status `kConnectionStateDisconnected` for more than 10s without a successful reconnection. SDK will still continue to try to reconnect.
     */
    kConnectionStateLost = 6,
    /**
     * @locale zh
     * @brief 连接失败，服务端状态异常。SDK 不会自动重连，请重新进房，或联系技术支持。
     */
    /**
     * @locale en
     * @brief Connection failure caused by abnormal state of the server. SDK will not automatically reconnect, please re-enter the room or contact technical support.
     */
    kConnectionStateFailed = 7,
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
enum NetworkQuality {
    /**
     * @locale zh
     * @brief 网络质量未知。
     */
    /**
     * @locale en
     * @brief Network quality unknown.
     */
    kNetworkQualityUnknown = 0,
    /**
     * @locale zh
     * @brief 网络质量极好。
     */
    /**
     * @locale en
     * @brief The network quality is excellent.
     */
    kNetworkQualityExcellent,
    /**
     * @locale zh
     * @brief 主观感觉和 kNetworkQualityExcellent 差不多，但码率可能略低。
     */
    /**
     * @locale en
     * @brief The subjective feeling is similar to kNetworkQualityExcellent, but the bit rate may be slightly lower.
     */
    kNetworkQualityGood,
    /**
     * @locale zh
     * @brief 主观感受有瑕疵但不影响沟通。
     */
    /**
     * @locale en
     * @brief Subjective feelings are flawed but do not affect communication.
     */
    kNetworkQualityPoor,
    /**
     * @locale zh
     * @brief 勉强能沟通但不顺畅。
     */
    /**
     * @locale en
     * @brief Can barely communicate but not smoothly.
     */
    kNetworkQualityBad,
    /**
     * @locale zh
     * @brief 网络质量非常差，基本不能沟通。
     */
    /**
     * @locale en
     * @brief The quality of the network is very poor and communication is basically impossible.
     */
    kNetworkQualityVbad,
    /**
     * @locale zh
     * @brief 网络连接断开，无法通话。网络可能由于 12s 内无应答、开启飞行模式、拔掉网线等原因断开。<br>
     *        更多网络状态信息参见 [连接状态提示](https://www.volcengine.com/docs/6348/95376)。
     */
    /**
     * @locale en
     * @brief The network is down. It may be down due to no answer within 12s, airplane mode on, disconnected cable, etc.<br>
     *        Refer to [Get connection state](https://docs.byteplus.com/byteplus-rtc/docs/95376) for more details about getting connection state.
     */
    kNetworkQualityDown,
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
enum NetworkType {
    /**
     * @locale zh
     * @brief 网络连接类型未知。
     */
    /**
     * @locale en
     * @brief Network connection type unknown.
     */
    kNetworkTypeUnknown = -1,
    /**
     * @locale zh
     * @brief 网络连接已断开。
     */
    /**
     * @locale en
     * @brief The network connection has been disconnected.
     */
    kNetworkTypeDisconnected = 0,
    /**
     * @locale zh
     * @brief 网络连接类型为 LAN 。
     */
    /**
     * @locale en
     * @brief The network connection type is LAN.
     */
    kNetworkTypeLAN = 1,
    /**
     * @locale zh
     * @brief 网络连接类型为 Wi-Fi（包含热点）。
     */
    /**
     * @locale en
     * @brief The network connection type is Wi-Fi (including hotspots).
     */
    kNetworkTypeWIFI = 2,
    /**
     * @locale zh
     * @brief 网络连接类型为 2G 移动网络。
     */
    /**
     * @locale en
     * @brief The network connection type is 2G mobile network.
     */
    kNetworkTypeMobile2G = 3,
    /**
     * @locale zh
     * @brief 网络连接类型为 3G 移动网络。
     */
    /**
     * @locale en
     * @brief The network connection type is 3G mobile network.
     */
    kNetworkTypeMobile3G = 4,
    /**
     * @locale zh
     * @brief 网络连接类型为 4G 移动网络。
     */
    /**
     * @locale en
     * @brief The network connection type is 4G mobile network.
     */
    kNetworkTypeMobile4G = 5,
    /**
     * @locale zh
     * @brief 网络连接类型为 5G 移动网络。
     */
    /**
     * @locale en
     * @brief The network connection type is 5G mobile network.
     */
    kNetworkTypeMobile5G = 6,
};

/**
 * @locale zh
 * @type errorcode
 * @brief 回调错误码。  <br>
 *        SDK 内部遇到不可恢复的错误时，会通过 `onError` 回调通知用户。
 */
/**
 * @locale en
 * @type errorcode
 * @brief Callback error code.   <br>
 *        When an unrecoverable error is encountered inside the SDK, the user is notified via the `onError` callback.
 */
enum RtsErrorCode {
    /**
     * @locale zh
     * @brief Token 无效。<br>
     *        进房时使用的 Token 无效或过期失效。需要用户重新获取 Token，并调用 `updateToken` 方法更新 Token。
     */
    /**
     * @locale en
     * @brief Token  is invalid.<br>
     *        The Token used when joining the room is invalid or expired. The user is required to retrieve the token and call the `updateToken` to update the token.
     */
    kRtsErrorCodeInvalidToken = -1000,
    /**
     * @locale zh
     * @brief 加入房间错误。<br>
     *        进房时发生未知错误导致加入房间失败。需要用户重新加入房间。
     */
    /**
     * @locale en
     * @brief Join room error.<br>
     *        An unknown error occurred while joining the room, which caused the joining room to fail. Users are required to rejoin the room.
     */
    kRtsErrorCodeJoinRoom = -1001,
    /**
     * @locale zh
     * @brief 相同用户 ID 的用户加入本房间，当前用户被踢出房间
     */
    /**
     * @locale en
     * @brief The user has been removed from the room because the same user joined the room on the other client.
     */
    kRtsErrorCodeDuplicateLogin = -1004,
    /**
     * @locale zh
     * @brief 服务端调用 OpenAPI 将当前用户踢出房间
     */
    /**
     * @locale en
     * @brief The user has been removed from the room by the administrator via a OpenAPI call.
     */
    kRtsErrorCodeKickedOut = -1006,
    /**
     * @locale zh
     * @brief 当调用 `createRTCRoom` ，如果roomid 非法，会返回null，并抛出该error
     */
    /**
     * @locale en
     * @brief When calling `createRTCRoom`, if the roomid is illegal, it will return null and throw the error
     */
    kRtsRoomErrorCodeRoomIdIllegal = -1007,
    /**
     * @locale zh
     * @brief Token 过期。调用 `joinRoom` 使用新的 Token 重新加入房间。
     */
    /**
     * @locale en
     * @brief Token expired. Call `joinRoom` to rejoin with a valid Token.
     */
    kRtsRoomErrorTokenExpired = -1009,
    /**
     * @locale zh
     * @brief 调用 `updateToken` 传入的 Token 无效
     */
    /**
     * @locale en
     * @brief The Token you provided when calling `updateToken` is invalid.
     */
    kRtsRoomErrorUpdateTokenWithInvalidToken = -1010,
    /**
     * @locale zh
     * @brief 服务端调用 OpenAPI 解散房间，所有用户被移出房间。
     */
    /**
     * @locale en
     * @brief Users have been removed from the room because the administrator dismissed the room by calling OpenAPI.
     */
    kRtsErrorCodeRoomDismiss = -1011,
    /**
     * @locale zh
     * @brief 通话回路检测已经存在同样 roomId 的房间了
     */
    /**
     * @locale en
     * @brief there is a room with the same roomId，whose room id is the same with echo test
     */
    kRtsErrorCodeRoomAlreadyExist = -1013,
    /**
     * @locale zh
     * @brief 同一个引擎实例在进入多个房间时设置的用户名必须相同
     */
    /**
     * @locale en
     * @brief The user name set by the same engine instance when entering multiple rooms must be the same
     */
    kRtsErrorCodeUserIDDifferent = -1014,
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
    kRtsErrorCodeAbnormalServerStatus = -1084,
    /**
     * @hidden for internal use only
     */
    kRtsErrorCodeInternalDeadLockNotify = -1111,
};

/**
 * @locale zh
 * @type errorcode
 * @brief 回调警告码。<br>
 *        警告码说明 SDK 内部遇到问题正在尝试恢复。警告码仅起通知作用。
 */
/**
 * @locale en
 * @type errorcode
 * @brief Callback warning code. The warning code indicates that there is a problem within the SDK and is trying to recover. Warning codes only serve as notifications.
 */
enum RtsWarningCode {
    /**
     * @locale zh
     * @hidden
     * @deprecated since 3.46 and will be deleted in 3.51.
     */
    /**
     * @locale en
     * @hidden
     * @deprecated since 3.46 and will be deleted in 3.51.
     */
    kRtsWarningCodeGetRoomFailed = -2000,
    /**
     * @locale zh
     * @brief 进房失败。  <br>
     *        当你调用初次加入房间或者由于网络状况不佳断网重连时，由于服务器错误导致进房失败。SDK 会自动重试进房。
     */
    /**
     * @locale en
     * @brief Failed to enter the room.   <br>
     *        When you call the first time to join the room or disconnect and reconnect due to poor network conditions, the room entry fails due to a server error. The SDK automatically retries the room.
     */
    kRtsWarningCodeJoinRoomFailed = -2001,
    /**
     * @locale zh
     * @brief 发布音视频流失败。  <br>
     *        当你在所在房间中发布音视频流时，由于服务器错误导致发布失败。SDK 会自动重试发布。
     */
    /**
     * @locale en
     * @brief Release audio & video stream failed.   <br>
     *        When you publish audio & video streams in your room, the publication fails due to a server error. The SDK automatically retries the release.
     */
    kRtsWarningCodePublishStreamFailed = -2002,
    /**
     * @locale zh
     * @hidden currently not available
     * @brief 函数调用顺序错误。
     */
    /**
     * @locale en
     * @hidden currently not available
     * @brief  The function call order is wrong.
     */
    kRtsWarningCodeInvokeError = -2005,
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
    kRtsWarningCodeInvalidExpectMediaServerAddress = -2007,
    /**
     * @locale zh
     * @brief 发送自定义广播消息失败，当前你未在房间中。
     */
    /**
     * @locale en
     * @brief Sending a custom broadcast message failed, you are not currently in the room.
     */
    kRtsWarningCodeSendCustomMessage = -2011,
    /**
     * @locale zh
     * @brief 当房间内人数超过 500 人时，停止向房间内已有用户发送 `onUserJoined` 和 `onUserLeave` 回调，并通过广播提示房间内所有用户。
     */
    /**
     * @locale en
     * @brief When the number of people in the room exceeds 500, stop sending `onUserJoined` and `onUserLeave` callbacks to existing users in the room, and prompt all users in the room via broadcast.
     */
    kRtsWarningCodeUserNotifyStop = -2013,


    /**
     * @locale zh
     * @brief 新生成的房间已经替换了同样roomId的旧房间
     */
    /**
     * @locale en
     * @brief The old room has been replaced by new room with the same roomId
     */
    kRtsWarningCodeOldRoomBeenReplaced = -2016
};

/**
 * @locale zh
 * @type keytype
 * @brief 事务检查码  <br>
 *        用户调用 `setBusinessId` 方法设置业务标识参数的返回错误码。  
 */
/**
 * @locale en
 * @type keytype
 * @brief  Business check code   <br>
 *         The error code that the API `setBusinessId` sends back. 
 */
enum BusinessCheckCode {
    /**
     * @locale zh
     * @brief 用户已经在房间中。  <br>
     *        业务标识需要在加入房间之前设置，加入后设置无效。  
     */
    /**
     * @locale en
     * @brief The user is already in the room.   <br>
     *        You must set the Business Id before joining room, otherwise it will be invalid. 
     */
    kBusinessCheckCodeAlreadyInRoom = -6001,

    /**
     * @locale zh
     * @brief 输入参数非法。  <br>
     *        用户传入的业务标识参数非法，参数合法性参考 `setBusinessId` 方法的参数说明。  
     */
    /**
     * @locale en
     * @brief  The input is invalid.   <br>
     *         For the legal characters, see `setBusinessId`. 
     */
    kBusinessCheckCodeInputInvalidate = -6002,
};

/**
 * @locale zh
 * @type keytype
 * @brief App 使用的 CPU 和内存信息。  <br>
 *        该信息由 SDK 周期性（2s）通过 `onSysStats` 回调通知给用户。
 */
/**
 * @locale en
 * @type keytype
 * @brief The CPU and memory information used by App. <br>
 *        You will periodically(2s) receive `onSysStats` of the information.
 */
struct SysStats {
    /**
     * @locale zh
     * @brief 当前系统 CPU 核数。
     */
    /**
     * @locale en
     * @brief The CPU cores of your system.
     */
    unsigned int cpu_cores;
    /**
     * @locale zh
     * @brief 当前应用的 CPU 使用率，取值范围为 [0, 1]。
     */
    /**
     * @locale en
     * @brief The CPU usage rate of the current application. The value range is [0,1].
     */
    double cpu_app_usage;
    /**
     * @locale zh
     * @hidden currently not available
     * @brief 当前系统的 cpu 使用率，取值范围为 [0, 1]。
     */
    /**
     * @locale en
     * @hidden currently not available
     * @brief The cpu usage rate of the current system, the value range is [0,1].
     */
    double cpu_total_usage;
    /**
     * @locale zh
     * @brief 当前应用的内存使用量（单位 MB）。
     */
    /**
     * @locale en
     * @brief The memory usage of the current application(/MB).
     */
    double memory_usage;
    /**
     * @locale zh
     * @brief 全量内存（单位MB）。
     */
    /**
     * @locale en
     * @brief Total memory(/MB).
     */
    unsigned long long full_memory;
    /**
     * @locale zh
     * @brief 系统已使用内存（单位MB）。
     */
    /**
     * @locale en
     * @brief Used system memory(/MB).
     */
    unsigned long long total_memory_usage;
    /**
     * @locale zh
     * @brief 空闲可分配内存（单位MB）。
     */
    /**
     * @locale en
     * @brief Free system memory(/MB).
     */
    unsigned long long free_memory;
    /**
     * @locale zh
     * @brief 当前应用的内存使用率（单位 %）。
     */
    /**
     * @locale en
     * @brief The memory usage rate of the current application(/%).
     */
    double memory_ratio;
    /**
     * @locale zh
     * @brief 系统内存使用率（单位 %）。
     */
    /**
     * @locale en
     * @brief The system memory usage rate(/%).
     */
    double total_memory_ratio;
};

/**
 * @locale zh
 * @type keytype
 * @brief HTTP/HTTPS 代理状态
 */
/**
 * @locale en
 * @type keytype
 * @brief HTTP/HTTPS  proxy status
 */
enum HttpProxyState {
    /**
     * @locale zh
     * @brief HTTP/HTTPS 初始化状态
     */
    /**
     * @locale en
     * @brief HTTP/HTTPS  initialization state
     */
    kHttpProxyStateInit,
    /**
     * @locale zh
     * @brief HTTP/HTTPS 连接成功
     */
    /**
     * @locale en
     * @brief HTTP/HTTPS  Connection successful
     */
    kHttpProxyStateConnected,
    /**
     * @locale zh
     * @brief HTTP/HTTPS 连接失败
     */
    /**
     * @locale en
     * @brief HTTP/HTTPS  connection failed
     */
    kHttpProxyStateError
};

/**
 * @locale zh
 * @type keytype
 * @brief SOCKS5 代理连接状态
 */
/**
 * @locale en
 * @type keytype
 * @brief SOCKS5  proxy connection status
 */
enum Socks5ProxyState {
    /**
     * @locale zh
     * @brief SOCKS5 连接初始化
     */
    /**
     * @locale en
     * @brief SOCKS5  connection initialization
     */
    kSocks5Init,
    /**
     * @locale zh
     * @brief SOCKS5 连接成功
     */
    /**
     * @locale en
     * @brief SOCKS5  Connection successful
     */
    kSocks5Connected,
    /**
     * @locale zh
     * @brief SOCKS5 连接错误
     */
    /**
     * @locale en
     * @brief SOCKS5  connection error
     */
    kSocks5Error,
    /**
     * @locale zh
     * @brief TCP 连接失败
     */
    /**
     * @locale en
     * @brief TCP  connection failed
     */
    kSocks5TcpConnectFail,
    /**
     * @locale zh
     * @brief TCP 连接关闭
     */
    /**
     * @locale en
     * @brief TCP  connection closed
     */
    kSocks5TcpClose,
    /**
     * @locale zh
     * @brief SOCKS 协议 TCP 协商阶段失败
     */
    /**
     * @locale en
     * @brief SOCKS  protocol TCP negotiation phase failed
     */
    kSocks5ProtocolTcpFail,
    /**
     * @locale zh
     * @brief UDP 连接失败
     */
    /**
     * @locale en
     * @brief UDP  connection failed
     */
    kSocks5ProtocolUdpFail,
    /**
     * @locale zh
     * @brief 授权失败
     */
    /**
     * @locale en
     * @brief Authorization failed
     */
    kSocks5AuthFail,
    /**
     * @locale zh
     * @brief 未知状态
     */
    /**
     * @locale en
     * @brief Unknown state
     */
    kSocks5Unknown
};

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
struct CloudProxyInfo {
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
    const char* cloud_proxy_ip;
    /**
     * @locale zh
     * @type keytype
     * @brief 云代理服务器端口
     */
    /**
     * @locale en
     * @type keytype
     * @brief Cloud Proxy Port
     */
    int cloud_proxy_port;
};

/**
 * @locale zh
 * @type keytype
 * @brief 云代理相关信息
 */
/**
 * @locale en
 * @type keytype
 * @brief Configuration of Cloud Proxy
 */
struct CloudProxyConfiguration {
    /**
     * @locale zh
     * @brief 云代理信息。
     */
    /**
     * @locale en
     * @brief Information of cloud proxy.
     */
    CloudProxyInfo* cloud_proxies = nullptr;
    /**
     * @locale zh
     * @brief 云代理数量。
     */
    /**
     * @locale en
     * @brief Number of cloud proxy.
     */
    int cloud_proxy_count = 0;
};

/**
 * @locale zh
 * @type keytype
 * @brief ID 最大长度
 */
/**
 * @locale en
 * @type keytype
 * @brief The maximum length of an ID.
 */
const unsigned int MAX_DEVICE_ID_LENGTH = 512;

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
enum LocalProxyType {
    /**
     * @locale zh
     * @brief Socks5 代理。选用此代理服务器，需满足 Socks5 协议标准文档的要求。
     */
    /**
     * @locale en
     * @brief Socks5 proxy. If you chose Socks5 as the local proxy, you need to make sure all requirements listed in the Socks5 document are satisfied. 
     */
    kLocalProxyTypeSocks5 = 1,
    /**
     * @locale zh
     * @brief Http 隧道代理。
     */
    /**
     * @locale en
     * @brief Http tunnel proxy.
     */
    kLocalProxyTypeHttpTunnel = 2
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
struct LocalProxyConfiguration {
    /**
     * @locale zh
     * @brief 本地代理类型，参看 LocalProxyType{@link #LocalProxyType}。
     */
    /**
     * @locale en
     * @brief Types of local proxies. Refer to LocalProxyType{@link #LocalProxyType} for details.
     */
    LocalProxyType local_proxy_type;
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
    const char* local_proxy_ip;
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
    int local_proxy_port;
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
    const char* local_proxy_username;
    /**
     * @locale zh
     * @type keytype
     * @brief 本地代理密码。
     */
    /**
     * @locale en
     * @type keytype
     * @brief The password of the local proxy.
     */
    const char* local_proxy_password;
};

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
enum LocalProxyState {
    /**
     * @locale zh
     * @brief TCP 代理服务器连接成功。
     */
    /**
     * @locale en
     * @brief TCP proxy server is connected.
     */
    kLocalProxyStateInited = 0,

    /**
     * @locale zh
     * @brief 本地代理连接成功。
     */
    /**
     * @locale en
     * @brief The local proxy is connected.
     */
    kLocalProxyStateConnected = 1,

    /**
     * @locale zh
     * @brief 本地代理连接出现错误。
     */
    /**
     * @locale en
     * @brief Errors occurred when connecting to the local proxy.  
     */
    kLocalProxyStateError = 2,
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
enum LocalProxyError {
    /**
     * @locale zh
     * @brief 本地代理服务器无错误。
     */
    /**
     * @locale en
     * @brief There are no errors in local proxies. 
     */
    kLocalProxyErrorOK = 0,

    /**
     * @locale zh
     * @brief 代理服务器回复的版本号不符合 Socks5 协议标准文档的规定，导致 Socks5 代理连接失败。请检查代理服务器是否存在异常。
     */
    /**
     * @locale en
     * @brief The connection to Socks5 proxy failed because the proxy server replies wrong version numbers which don't accord with the Socks5 document. Please check the proxy server. 
     */
    kLocalProxyErrorSocks5VersionError = 1,

    /**
     * @locale zh
     * @brief 代理服务器回复的格式错误不符合 Socks5 协议标准文档的规定，导致 Socks5 代理连接失败。请检查代理服务器是否存在异常。
     */
    /**
     * @locale en
     * @brief The connection to Socks5 proxy failed because the format of the proxy's replies doesn't accord with the Socks5 document. Please check the proxy server. 
     */
    kLocalProxyErrorSocks5FormatError = 2,

    /**
     * @locale zh
     * @brief 代理服务器回复的字段值不符合 Socks5 协议标准文档的规定，导致 Socks5 代理连接失败。请检查代理服务器是否存在异常。
     */
    /**
     * @locale en
     * @brief The connection to Socks5 proxy failed because the proxy replies wrong information which doesn't accord with the Socks5 document. Please check the proxy server. 
     */
    kLocalProxyErrorSocks5InvalidValue = 3,

    /**
     * @locale zh
     * @brief 未提供代理服务器的用户名及密码，导致 Socks5 代理连接失败。请重新调用 `setLocalProxy`，在设置本地代理时填入用户名和密码。
     */
    /**
     * @locale en
     * @brief The connection to Socks5 proxy failed because the username and password of the local proxy are not provided. Please call `setLocalProxy` and enter your username and password. 
     */
    kLocalProxyErrorSocks5UserPassNotGiven = 4,

    /**
     * @locale zh
     * @brief TCP 关闭，导致 Socks5 代理连接失败。请检查网络或者代理服务器是否存在异常。
     */
    /**
     * @locale en
     * @brief The connection to Socks5 proxy failed because TCP is closed. Please check the proxy server and your network connection status.
     */
    kLocalProxyErrorSocks5TcpClosed = 5,

    /**
     * @locale zh
     * @brief Http 隧道代理错误。请检查 Http 隧道代理服务器或者网络是否存在异常。
     */
    /**
     * @locale en
     * @brief Errors in Http tunnel proxy. Please check Http tunnel proxy and your network connection status.
     */
    kLocalProxyErrorHttpTunnelFailed = 6,
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
enum class LocalLogLevel {
    /**
     * @locale zh
     * @brief 信息级别。
     */
    /**
     * @locale en
     * @brief Info level.
     */
    kInfo     = 0,
    /**
     * @locale zh
     * @brief （默认值）警告级别。
     */
    /**
     * @locale en
     * @brief (Default) Warning level.
     */
    kWarning  = 1,
    /**
     * @locale zh
     * @brief 错误级别。
     */
    /**
     * @locale en
     * @brief Error level.
     */
    kError    = 2,
    /**
     * @locale zh
     * @brief 关闭日志。
     */
    /**
     * @locale en
     * @brief Turn off logging.
     */
    kNone     = 3
};
 
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
struct LogConfig {
    /**
     * @locale zh
     * @brief 日志存储路径，必填。
     */
    /**
     * @locale en
     * @brief (Required) Local log directory.
     */
    const char* log_path = nullptr;
    /**
     * @locale zh
     * @brief 日志等级，参看 LocalLogLevel{@link #LocalLogLevel}，默认为警告级别，选填。
     */
    /**
     * @locale en
     * @brief (Optional) The logging level. See LocalLogLevel{@link #LocalLogLevel}. The default is warning level.
     */
    LocalLogLevel log_level = LocalLogLevel::kWarning;

    /**
     * @locale zh
     * @brief 日志文件最大占用的总空间，单位为 MB，选填。取值范围为 1～100 MB，默认值为 10 MB。<br>
     *        若 `log_file_size` < 1，取 1 MB。若 `log_file_size` > 100，取 100 MB。<br>
     *        其中，单个日志文件最大为 2 MB：<br>
     *        <ul><li> 若 1 ≤ <code>log_file_size</code> ≤ 2，则会生成一个日志文件。</li><li>若 <code>log_file_size</code> > 2，假设 <code>log_file_size/2</code> 的整数部分为 N，则前 N 个文件，每个文件会写满 2 MB，第 N+1 个文件大小不超过 <code>log_file_size mod 2</code>，否则会删除最老的文件，以此类推。</li></ul>
     */
    /**
     * @locale en
     * @brief (Optional) The limits for total log file size in MB. The range is 1 to 100 MB, and the default value is 10 MB.<br>
     *        If `log_file_size` < 1, it will be set to 1 MB. If `log_file_size` > 100, it will be set to 100 MB. <br>
     *        The maximum size for a single log file is 2 MB.<br>
     *        If 1 ≤ `log_file_size` ≤ 2, one log file will be generated. If `log_file_size` > 2, the first `⌊log_file_size/2⌋` files will be filled with 2 MB each, the `⌊log_file_size/2⌋+1` fill will be filled with `log_file_size mod 2`.<br>
     *        If the size exceeds the remaining space, the oldest file will be deleted.
     */
    uint32_t log_file_size = 10;

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
    const char* log_filename_prefix = nullptr;
};

}  // namespace bytertc
