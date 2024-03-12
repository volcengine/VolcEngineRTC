/*
 * Copyright (c) 2022 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief RTS
*/

#import <UIKit/UIKit.h>
#import "rtc/ByteRTCRtsDefines.h"

@class RTS;
@class RTSRoom;

#pragma mark - RTSDelegate
/** {zh}
 * @type callback
 * @brief RTSDelegate 协议包含了SDK提供的回调方法，SDK通过代理向应用程序上报一些运行时事件
 */
/** {en}
 * @type callback
 * @brief RTSDelegate protocol contains the callback method provided by the SDK, which reports some run-time events to the application through a proxy
 */
@protocol RTSDelegate <NSObject>
@optional

#pragma mark - Engine Management Delegate Methods
/** {zh}
 * @type callback
 * @region 引擎管理
 * @brief SDK 与信令服务器连接状态改变回调。连接状态改变时触发。
 * @param engine RTS 对象。
 * @param state 当前 SDK 与信令服务器连接状态。详细定义参见 ByteRTCConnectionState{@link #ByteRTCConnectionState} <br>
 * @notes 更多信息参见 [连接状态提示](https://www.volcengine.com/docs/6348/95376)。
 */
/** {en}
 * @type callback
 * @region engine management
 * @brief Callback about the status change of the SDK's network connection to the signaling server.
 * @param engine RTS object
 * @param state The current connection status between the SDK and the signaling server. See ByteRTCConnectionState{@link #ByteRTCConnectionState}.
 * @notes Refer to [Getting Connection Status](https://docs.byteplus.com/byteplus-rtc/docs/95376) for more details.
 */
- (void)rtsEngine:(RTS * _Nonnull)engine onConnectionStateChanged:(ByteRTCConnectionState)state;
/** {zh}
 * @type callback
 * @region 引擎管理
 * @brief SDK 当前网络连接类型改变回调。当 SDK 的当前网络连接类型发生改变时回调该事件。
 * @param engine RTS 对象。
 * @param type SDK 当前的网络连接类型。参看 ByteRTCNetworkType{@link #ByteRTCNetworkType}。
 */
/** {en}
 * @type callback
 * @region Engine management
 * @brief Callback for the current network connection type change.
 * @param engine RTS object.
 * @param type The current network connection type. See ByteRTCNetworkType{@link #ByteRTCNetworkType}.
 */
- (void)rtsEngine:(RTS * _Nonnull)engine onNetworkTypeChanged:(ByteRTCNetworkType)type;

/** {zh}
 * @type callback
 * @region 引擎管理
 * @brief 创建房间失败回调。
 * @param engine RTS 对象。
 * @param roomId 房间 ID。
 * @param errorCode 创建房间错误码：<br>
 *        + -1007：无效 roomId； <br>
 *        + -1013：相同 roomId 的房间已存在。
 */
/** {en}
 * @type callback
 * @region Engine Management
 * @brief Callback for failed room creation.
 * @param engine RTS object.
 * @param roomId Room ID.
 * @param errorCode Create room error code: <br>
 *        + -1007: Invalid roomId. <br>
 *        + -1013: A room with the same roomId already exists.
 */
- (void)rtsEngine:(RTS *_Nonnull)engine onCreateRoomStateChanged:(NSString * _Nonnull)roomId errorCode:(NSInteger)errorCode;


/** {zh}
 * @type callback
 * @region proxy
 * @brief 本地代理状态发生改变回调。调用 setLocalProxy:{@link #RTS#setLocalProxy:} 设置本地代理后，SDK 会触发此回调，返回代理连接的状态。  <br>
 * @param type 本地代理类型。参看 ByteRTCLocalProxyType{@link #ByteRTCLocalProxyType} 。  <br>
 * @param state 本地代理状态。参看 ByteRTCLocalProxyState{@link #ByteRTCLocalProxyState}。  <br>
 * @param error 本地代理错误。参看 ByteRTCLocalProxyError{@link #ByteRTCLocalProxyError}。
 */
/** {en}
 * @type callback
 * @region proxy
 * @brief Callback on local proxy connection. After calling setLocalProxy:{@link #RTS#setLocalProxy:} to set local proxies, you will receive this callback that informs you of the states of local proxy connection. 
 * @param type The types of local proxies. Refer to ByteRTCLocalProxyType{@link #ByteRTCLocalProxyType} for details.  <br>
 * @param state The states of local proxy connection. Refer to ByteRTCLocalProxyState{@link #ByteRTCLocalProxyState} for details.  <br>
 * @param error The errors of local proxy connection. Refer to ByteRTCLocalProxyError{@link #ByteRTCLocalProxyError} for details.
 */
- (void)rtsEngine:(RTS * _Nonnull)engine onLocalProxyStateChanged:(ByteRTCLocalProxyType)type withProxyState:(ByteRTCLocalProxyState)state 
        withProxyError:(ByteRTCLocalProxyError)error;

#pragma mark - Data Statistics Delegate Methods
/** {zh}
 * @type callback
 * @region 引擎管理
 * @brief 周期性（2s）地发出回调，报告当前 cpu 与内存的使用率
 * @param engine RTS 对象
 * @param stats 返回包含当前系统状态信息的结构体，详见 ByteRTCSysStats{@link #ByteRTCSysStats}
 */
/** {en}
 * @type callback
 * @region engine management
 * @brief Callback triggered every 2 seconds about the usage of CPU and memory.
 * @param engine RTS object
 * @param stats Usage of CPU and memory. See ByteRTCSysStats{@link #ByteRTCSysStats}.
 */
- (void)rtsEngine:(RTS * _Nonnull)engine onSysStats:(const ByteRTCSysStats * _Nonnull)stats;

#pragma mark - Real-time Messaging Delegate Methods
/** {zh}
 * @type callback
 * @region 实时消息通信
 * @brief 登录 RTS 服务器结果回调。
 * @param engine RTS 对象
 * @param uid 登录用户 ID
 * @param errorCode 登录结果，详见 ByteRTCLoginErrorCode{@link #ByteRTCLoginErrorCode}。
 * @param elapsed 从调用 login:uid:{@link #RTS#login:uid:} 接口开始到返回结果所用时长，单位为 ms。
 * @notes 调用 login:uid:{@link #RTS#login:uid:} 后，会收到此回调。
 */
/** {en}
 * @type callback
 * @region Real-time messaging
 * @brief Login result callback
 * @param engine RTS object
 * @param uid Login user ID
 * @param errorCode Login result. See ByteRTCLoginErrorCode{@link #ByteRTCLoginErrorCode}.
 * @param elapsed The time in ms it takes from calling login{@link #RTS#login} to the result returned.
 * @notes This callback is received after login{@link #RTS#login} is called.
 */
- (void)rtsEngine:(RTS * _Nonnull)engine onLoginResult:(NSString * _Nonnull)uid
        errorCode:(ByteRTCLoginErrorCode)errorCode elapsed:(NSInteger)elapsed;
/** {zh}
 * @type callback
 * @region 实时消息通信
 * @brief 登出结果回调
 * @param engine RTS 对象
 * @param reason 用户登出的原因，参看 ByteRTCLogoutReason{@link #ByteRTCLogoutReason} 
 * @notes 在以下两种情况下会收到此回调：调用 logout{@link #RTS#logout} 接口主动退出；或其他用户以相同 UserId 进行 `login` 导致本地用户被动登出。
 */
/** {en}
 * @type callback
 * @region Real-time messaging
 * @brief Callback of logout result
 * @param engine RTS object
 * @param reason It describes the reason why users log out. See ByteRTCLogoutReason{@link #ByteRTCLogoutReason} 
 * @notes You will receive this callback when calling logout{@link #RTS#logout} or when the local user is kicked out because another user logs in with the same UserId.
 */
- (void)rtsEngine:(RTS * _Nonnull)engine onLogout:(ByteRTCLogoutReason)reason;
/** {zh}
 * @type callback
 * @region 实时消息通信
 * @brief 设置应用服务器参数的返回结果
 * @param engine RTS 对象
 * @param errorCode 设置结果：
 *        + 返回 200，设置成功  <br>
 *        + 返回其他，设置失败
 * @notes 调用 setServerParams:url:{@link #RTS#setServerParams:url:} 后，会收到此回调。
 */
/** {en}
 * @type callback
 * @region Real-time messaging
 * @brief Callback for the result of setting application server parameters.
 * @param engine RTS object
 * @param errorCode  <br>
 *         + 200, set successfully <br>
 *         + Return other, set failed
 * @notes This callback is received after setServerParams:url:{@link #RTS#setServerParams:url:} is called.
 */
- (void)rtsEngine:(RTS * _Nonnull)engine onServerParamsSetResult:(NSInteger)errorCode;
/** {zh}
 * @type callback
 * @region 实时消息通信
 * @brief 查询对端或本端用户登录状态的返回结果
 * @param engine RTS 对象
 * @param peerUserId 需要查询的用户 ID
 * @param status 查询的用户登录状态，详见 ByteRTCUserOnlineStatus{@link #ByteRTCUserOnlineStatus}.
 * @notes 必须先调用 getPeerOnlineStatus:{@link #RTS#getPeerOnlineStatus:}，才能收到此回调。
 */
/** {en}
 * @type callback
 * @region Real-time messaging
 * @brief Callback for the result of querying the login status of the remote or local user.
 * @param engine RTS object.
 * @param peerUserId ID of the user to be queried.
 * @param status The login status of the user queried. See ByteRTCUserOnlineStatus{@link #ByteRTCUserOnlineStatus}.
 * @notes You must first call getPeerOnlineStatus:{@link #RTS#getPeerOnlineStatus:} to receive this callback.
 */
- (void)rtsEngine:(RTS * _Nonnull)engine onGetPeerOnlineStatus:(NSString * _Nonnull)peerUserId
           status:(ByteRTCUserOnlineStatus)status;
/** {zh}
 * @type callback
 * @region 实时消息通信
 * @brief 收到远端用户调用 sendMessage:message:config:{@link #RTS#sendMessage:message:config:} 发来的文本消息时，会收到此回调。
 * @param engine RTS 对象
 * @param uid 消息发送者 ID
 * @param message 收到的文本消息内容
 */
/** {en}
 * @type callback
 * @region Real-time messaging
 * @brief The local user receives the text message from a remote user calling sendMessage:message:config:{@link #RTS#sendMessage:message:config:} through this callback.
 * @param engine RTS object
 * @param uid User ID of the message sender.
 * @param message Received text message content.
 */
- (void)rtsEngine:(RTS * _Nonnull)engine onMessageReceived:(NSString * _Nonnull)uid
          message:(NSString * _Nonnull)message;
/** {zh}
 * @type callback
 * @region 实时消息通信
 * @brief 收到房间外用户调用 sendBinaryMessage:message:config:{@link #RTS#sendBinaryMessage:message:config:} 发来的二进制消息时，会收到此回调。
 * @param engine RTS 对象
 * @param uid 消息发送者 ID
 * @param message 收到的二进制消息内容
 */
/** {en}
 * @type callback
 * @region Real-time messaging
 * @brief The local user receives the binary message from a remote user calling sendBinaryMessage:message:config:{@link #RTS#sendBinaryMessage:message:config:} through this callback.
 * @param engine RTS object.
 * @param uid User ID of the message sender.
 * @param message Received binary message content.
 */
- (void)rtsEngine:(RTS * _Nonnull)engine onBinaryMessageReceived:(NSString * _Nonnull)uid
          message:(NSData * _Nonnull)message;
/** {zh}
 * @type callback
 * @region 实时消息通信
 * @brief 发送 p2p 消息的结果回调。
 * @param engine RTS 对象
 * @param msgid 本条消息的 ID。所有的 P2P 和 P2Server 消息共用一个 ID 序列。
 * @param error 消息发送结果，详见 ByteRTCUserMessageSendResult{@link #ByteRTCUserMessageSendResult}。
 * @notes 当调用 sendMessage:message:config:{@link #RTS#sendMessage:message:config:} 或 sendBinaryMessage:message:config:{@link #RTS#sendBinaryMessage:message:config:} 发送消息后，会收到此回调。
 */
/** {en}
 * @type callback
 * @region Real-time messaging
 * @brief Callback about the sending result of a p2p message.
 * @param engine RTS object
 * @param msgid The ID of this message. All P2P and P2Server messages share a single ID sequence.
 * @param error Message sending result, see ByteRTCUserMessageSendResult{@link #ByteRTCUserMessageSendResult}.
 * @notes The local user will receive this callback when a message is sent by calling sendMessage:message:config:{@link #RTS#sendMessage:message:config:} or sendBinaryMessage:message:config:{@link #RTS#sendBinaryMessage:message:config:}.
 */
- (void)rtsEngine:(RTS * _Nonnull)engine onMessageSendResult:(int64_t)msgid
            error:(ByteRTCUserMessageSendResult)error;
/** {zh}
 * @type callback
 * @region 实时消息通信
 * @brief 发送 p2server 消息的结果回调。
 * @param engine RTS 对象
 * @param msgid 本条消息的 ID。所有的 P2P 和 P2Server 消息共用一个 ID 序列。
 * @param error 消息发送结果。详见 ByteRTCUserMessageSendResult{@link #ByteRTCUserMessageSendResult}。
 * @notes 当调用 sendServerMessage:{@link #RTS#sendServerMessage:} 或 sendServerBinaryMessage:{@link #RTS#sendServerBinaryMessage:} 接口发送消息后，会收到此回调。
 */
/** {en}
 * @type callback
 * @region Real-time messaging
 * @brief Callback about the sending result of a p2server message.
 * @param engine RTS object
 * @param msgid The ID of this message. All P2P and P2Server messages share a single ID sequence.
 * @param error Message sending result, see ByteRTCUserMessageSendResult{@link #ByteRTCUserMessageSendResult}.
 * @notes The local user will receive this callback when a message is sent by calling sendServerMessage:{@link #RTS#sendServerMessage:} or sendServerBinaryMessage:{@link #RTS#sendServerBinaryMessage:}.
 */
- (void)rtsEngine:(RTS * _Nonnull)engine onServerMessageSendResult:(int64_t)msgid
            error:(ByteRTCUserMessageSendResult)error message:(NSData * _Nonnull)message;

@end

#pragma mark - RTS
/**
 * @type api
 */
BYTERTC_APPLE_EXPORT @interface RTS : NSObject
/**
 * @type callback
 */
@property(nonatomic, weak) id<RTSDelegate> _Nullable delegate;

#pragma mark - Engine Management Methods
/** {zh}
 * @type api
 * @region 引擎管理
 * @brief 创建引擎对象  <br>
 *        如果当前进程中未创建引擎实例，那么你必须先使用此方法，以使用 RTS 提供的各种消息能力。  <br>
 *        如果当前进程中已创建了引擎实例，再次调用此方法时，会创建另一个独立的引擎实例。
 * @param appId 每个应用的唯一标识符，由控制台随机生成的。不同的 AppId 生成的实例完全独立，无法互通。
 * @param delegate SDK 回调给应用层的 delegate，详见 RTSDelegate{@link #RTSDelegate}
 * @param parameters 用以覆盖默认参数的本引擎实例参数。JSON 字符串格式。
 * @return 可用的 RTSDelegate{@link #RTSDelegate} 实例。
 */
/** {en}
 * @type api
 * @region Engine Management
 * @brief Creates an engine instance.   <br>
 *        This is the very first API that you must call if you want to use all the RTS capabilities.  <br>
 *        If there is no engine instance in current thread, calling this API will create one. If an engine instance has been created, calling this API again will create another instance.
 * @param appId A unique identifier for each App, randomly generated by the RTC console. Engine instances created with different AppIds cannot communicate with each other.
 * @param delegate Delegate sent from SDK to App. See RTSDelegate{@link #RTSDelegate}.
 * @param parameters Reserved parameter, in JSON string.
 * @return A RTSDelegate{@link #RTSDelegate} instance.
 */
+ (RTS * _Nullable)createRTS:(NSString * _Nonnull)appId
                    delegate:(id<RTSDelegate> _Nullable)delegate
                  parameters:(NSDictionary* _Nullable)parameters;
/** {zh}
 * @type api
 * @region 引擎管理
 * @brief 销毁引擎实例对象。
 * @notes  <br>
 *      + 请确保和需要销毁的 RTS 实例相关的业务场景全部结束后，才调用此方法。  <br>
 *      + 该方法在调用之后，会销毁所有和此 RTS 实例相关的内存，并且停止与媒体服务器的任何交互。  <br>
 *      + 调用本方法会启动 SDK 退出逻辑。引擎线程会保留，直到退出逻辑完成。因此，不要在回调线程中直接调用此 API，会导致死锁。同时此方法是耗时操作，不建议在主线程调用本方法，避免主线程阻塞。  <br>
 *      + 可以通过 Objective-C 的ARC机制，在 dealloc 时自动触发销毁逻辑。
 */
/** {en}
 * @type api
 * @region Engine Management
 * @brief Destroys the engine instance.
 * @notes  <br>
 *       + Call this API after all business scenarios related to the engine instance are destroyed.  <br>
 *       + When the API is called, RTC SDK destroys all memory associated with the engine instance and stops any interaction with the media server.  <br>
 *       + Calling this API will start the SDK exit logic. The engine thread is held until the exit logic is complete. The engine thread is retained until the exit logic is complete. Therefore, do not call this API directly in the callback thread, or it will cause a deadlock. This function takes a long time to execute, so it's not recommended to call this API in the main thread, or the main thread may be blocked.
 *       + You can enable ARC for Objective-C, to automatically trigger the destruction logic when the dealloc method is called.
 */
+ (void)destroyRTS;

/** {zh}
 * @type api
 * @region 引擎管理
 * @brief 获取 SDK 当前的版本号。
 * @return SDK 当前的版本号。
 */
/** {en}
 * @type api
 * @region  engine management
 * @brief Gets the current version number of the SDK.
 * @return The current version number.
 */
+ (NSString * _Nonnull)getSdkVersion;

/** {zh}
 * @type api
 * @region 引擎管理
 * @brief 配置 SDK 本地日志参数，包括日志级别、存储路径、日志文件最大占用的总空间、日志文件名前缀。
 * @param logConfig 本地日志参数，参看 ByteRTCLogConfig{@link #ByteRTCLogConfig}。
 * @return <br>
 *        + 0：成功。
 *        + –1：失败，本方法必须在创建引擎前调用。
 *        + –2：失败，参数填写错误。
 * @notes 本方法必须在调用 createRTS:delegate:parameters:{@link #RTS#createRTS:delegate:parameters:} 之前调用。
 */
/** {en}
 * @type api
 * @region Engine Management
 * @brief Configures the local log parameters of RTC SDK, including the logging level, directory, and the limits for total log file size.
 * @param logConfig Local log parameters. See ByteRTCLogConfig{@link #ByteRTCLogConfig}.
 * @return <br>
 *        + 0: Success.
 *        + –1: Failure. This API must be called before creating engine.
 *        + –2: Failure. Invalid parameters.
 * @notes This API must be called before createRTS:delegate:parameters:{@link #RTS#createRTS:delegate:parameters:}.
 */
+ (int) setLogConfig:(ByteRTCLogConfig *_Nonnull) logConfig;

/** {zh}
 * @type api
 * @region 引擎管理
 * @brief 设置业务标识参数  <br>
 *        可通过 businessId 区分不同的业务场景。businessId 由客户自定义，相当于一个“标签”，可以分担和细化现在 AppId 的逻辑划分的功能，但不需要鉴权。
 * @param businessId 用户设置的自己的 businessId 值。businessId 只是一个标签，颗粒度需要用户自定义。
 * @return  <br>
 *        + 0： 成功  <br>
 *        + < 0： 失败  <br>
 *        + -6001： 用户已经在房间中。  <br>
 *        + -6002： 输入非法，合法字符包括所有小写字母、大写字母和数字，除此外还包括四个独立字符分别是：英文句号，短横线，下划线和 @ 。
 * @notes 需要在调用 joinRoom{@link #RTSRoom#joinRoom} 之前调用，joinRoom{@link #RTSRoom#joinRoom}之后调用该方法无效。
 */
/** {en}
 * @type api
 * @region Engine management
 * @brief Sets the business ID.   <br>
 *        You can use businessId to distinguish different business scenarios. You can customize your businessId to serve as a sub AppId, which can share and refine the function of the AppId, but it does not need authentication.
 * @param businessId Your customized businessId. BusinessId is a tag, and you can customize its granularity.
 * @return  <br>
 *         + 0: Success <br>
 *         + < 0: Failure <br>
 *         + -6001: The user is already in the room. <br>
 *         + -6002: The input is invalid. Legal characters include all lowercase letters, uppercase letters, numbers, and four other symbols, including '.', '-','_', and '@'.
 * @notes You must call this API before the joinRoom{@link #RTSRoom#joinRoom} API, otherwise it will be invalid.
 */
- (int)setBusinessId:(NSString* _Nullable)businessId;
/** {zh}
 * @type api
 * @brief 设置运行时的参数
 * @param parameters 保留参数
 * @return  <br>
 *        + 0: 调用成功。
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 */
/** {en}
 * @type api
 * @brief Sets runtime parameters/
 * @param parameters Reserved parameters.
 * @return  <br>
 *        + 0: Success.
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 */
- (int)setRuntimeParameters:(NSDictionary * _Nullable)parameters;

#pragma mark - Multi-room Methods
/** {zh}
 * @type api
 * @region 房间管理
 * @brief 创建房间实例。
 *        调用此方法仅返回一个房间实例，你仍需调用 joinRoom{@link #RTSRoom#joinRoom} 才能真正地创建/加入房间。
 *        多次调用此方法以创建多个 RTSRoom{@link #RTSRoom} 实例。分别调用各 RTSRoom 实例中的 joinRoom{@link #RTSRoom#joinRoom} 方法，同时加入多个房间。
 *        多房间模式下，用户可以同时订阅各房间的音视频流。
 * @param roomId 标识通话房间的房间 ID。该字符串符合正则表达式：`[a-zA-Z0-9_@\-\.]{1,128}`。
 * @return 创建的 RTSRoom{@link #RTSRoom} 房间实例。
 * @notes <br>
 *        + 如果需要加入的房间已存在，你仍需先调用本方法来获取 RTSRoom 实例，再调用 joinRoom{@link #RTSRoom#joinRoom} 加入房间。
 *        + 多房间模式下，创建多个房间实例需要使用不同的 roomId，否则会导致创建房间失败。
 */
/** {en}
 * @type api
 * @region Room Management
 * @brief Create a room instance.
 *        This API only returns a room instance. You still need to call joinRoom{@link #RTSRoom#joinRoom} to actually create/join the room.
 *        Each call of this API creates one RTSRoom{@link #RTSRoom} instance. Call this API as many times as the number of rooms you need, and then call joinRoom{@link #RTSRoom#joinRoom} of each RTSRoom instance to join multiple rooms at the same time.
 *        In multi-room mode, a user can subscribe to media streams in the joined rooms at the same time.
 * @param roomId The string matches the regular expression: `[a-zA-Z0-9_@\-\.]{1,128}`.
 * @return RTSRoom{@link #RTSRoom} instance.
 * @notes <br>
 *       + If the room that you wish to join already exists, you still need to call this API first to create the RTSRoom instance, and then call joinRoom{@link #RTSRoom#joinRoom}.
 *       + In multi-room mode, you need to use different roomId to create multiple rooms.
 */
- (RTSRoom * _Nullable)createRoom:(NSString * _Nonnull)roomId;

#pragma mark - Real-time Messaging Methods
/** {zh}
 * @type api
 * @region 实时消息通信
 * @brief 登录 RTS 服务器。 <br>
 *        必须先登录，才能收发消息。<br>
 *        在调用本接口登录后，如果想要登出，需要调用 logout{@link #RTS#logout}
 * @param token  用户登录必须携带的 Token，用于鉴权验证。
 *               测试时可使用[控制台](https://console.volcengine.com/rtc/listRTC)生成临时 Token，`roomId` 填任意值。
 *               正式上线需要使用密钥 SDK 在你的服务端生成并下发 Token，`roomId` 置空，Token 有效期及生成方式参看[使用 Token 完成鉴权](70121)。
 * @param uid 用户 ID， 在 appid 的维度下唯一。
 * @return 方法调用结果：<br>
 *        + `0`：成功<br>
 *        + `-1`：失败。无效参数<br>
 *        + `-2`：无效调用。用户已经登录。成功登录后再次调用本接口将收到此返回值 <br>
 *        + `-3`：失败。Engine 为空。
 * @notes  本地用户调用此方法登录后，会收到 rtsEngine:onLoginResult:errorCode:elapsed:{@link #RTSDelegate#rtsEngine:onLoginResult:errorCode:elapsed:} 回调通知登录结果。
 */
/** {en}
 * @type api
 * @region Real-time messaging
 * @brief Logs in to the RTS system. <br>
 *        Login is necessary for sending and receiving messages.<br>
 *        To log out, call logout{@link #RTS#logout}.
 * @param token Dynamic key which is required during login for authentication. <br>
 *        This Token is different from that required by calling joinRoom. You can generate a temporary token on the console when testing. When the application goes live, you need to use the key SDK to generate and issue Token on your server side.
 * @param uid User ID, which needs to be unique within one appid.
 * @return API call result: <br>
 *        + `0`: Success<br>
 *        + `-1`: Failure due to invalid parameter<br>
 *        + `-2`: Invalid call. RTC will return this value when you call this API after the user has been logged in to the server. <br>
 *        + `-3`: Failure. There is no created engine instance.
 * @notes You will receive rtsEngine:onLoginResult:errorCode:elapsed:{@link #RTSDelegate#rtsEngine:onLoginResult:errorCode:elapsed:} after calling this API and log in successfully.
 */
- (int)login:(NSString * _Nonnull)token uid:(NSString * _Nonnull)uid;
/** {zh}
 * @type api
 * @region 实时消息通信
 * @brief 登出 RTS 服务器。 <br>
 *        调用本接口登出后，无法再调用消息相关的方法或收到相关回调。
 * @return  <br>
 *        + 0: 调用成功。
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @notes 本地用户调用此方法登出后，会收到 rtcEngineOnLogout:{@link #RTSDelegate#rtsEngineOnLogout:} 回调通知结果，远端用户不会收到通知。
 */
/** {en}
 * @type After api
 * @region real-time messaging
 * @brief Logs out of the RTS system. <br>
 *        After calling this API, it is impossible to call messsage-related APIs or receive related callbacks.
 * @return  <br>
 *        + 0: Success.
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @notes After this API is called to log out, local users will receive rtcEngineOnLogout:{@link #RTSDelegate#rtsEngineOnLogout:} notifying the result, and remote users will not receive any notifications.
 */
- (int)logout;
/** {zh}
 * @type api
 * @region 实时消息通信
 * @brief 更新用户用于登录的 Token  <br>
 *        Token 有一定的有效期，当 Token 过期时，需调用此方法更新登录的 Token 信息。  <br>
 *        调用 login:uid:{@link #RTS#login:uid:} 方法登录时，如果使用了过期的 Token 将导致登录失败，并会收到 rtsEngine:onLoginResult:errorCode:elapsed:{@link #RTSDelegate#rtsEngine:onLoginResult:errorCode:elapsed:} 回调通知，错误码为 ByteRTCLoginErrorCodeInvalidToken。此时需要重新获取 Token，并调用此方法更新 Token。
 * @param token  <br>
 *        更新的动态密钥  <br>
 * @return  <br>
 *        + 0: 调用成功。
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @notes  <br>
 *       + 如果 Token 无效导致登录失败，则调用此方法更新 Token 后，SDK 会自动重新登录，而用户不需要自己调用 login:uid:{@link #RTS#login:uid:} 方法。  <br>
 *       + Token 过期时，如果已经成功登录，则不会受到影响。Token 过期的错误会在下一次使用过期 Token 登录时，或因本地网络状况不佳导致断网重新登录时通知给用户。
 */
/** {en}
 * @type api
 * @region Real-time messaging
 * @brief Update the Token <br>
 *        Token used by the user to log in has a certain valid period. When the Token expires, you need to call this method to update the login Token information. <br>
 *        If login:uid:{@link #RTS#login:uid:} is called with an expired token, the login will fail and you will receive rtsEngine:onLoginResult:errorCode:elapsed:{@link #RTSDelegate#rtsEngine:onLoginResult:errorCode:elapsed:} with an error code of `ByteRTCLoginErrorCodeInvalidToken`. You need to reacquire the token and call this method to update the token.
 * @param token Updated token. <br>
 * @return  <br>
 *        + 0: Success.
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @notes  <br>
 *        + If the token is invalid and the login fails, call this method to update the token, and the SDK will automatically log in again. The user does not need to call the login:uid:{@link #RTS#login:uid:} method. <br>
 *        + Token expires, if you have successfully logged in, it will not be affected. An expired Token error will be notified to the user the next time you log in with an expired Token, or when you log in again due to a disconnection due to poor local network conditions.
 */
- (int)updateLoginToken:(NSString * _Nonnull)token;
/** {zh}
 * @type api
 * @region 实时消息通信
 * @brief 设置应用服务器参数  <br>
 *        客户端调用 sendServerMessage:{@link #RTS#sendServerMessage:} 或 sendServerBinaryMessage:{@link #RTS#sendServerBinaryMessage:} 发送消息给应用服务器之前，必须需要设置有效签名和应用服务器地址。
 * @param signature 动态签名，应用服务器可使用该签名验证消息来源。<br>
 *        签名需自行定义，可传入任意非空字符串，建议将 uid 等信息编码为签名。<br>
 *        设置的签名会以 post 形式发送至通过本方法中 url 参数设置的应用服务器地址。
 * @return  <br>
 *        + 0: 调用成功。
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @notes  <br>
 *       + 用户必须调用 login:uid:{@link #RTS#login:uid:} 登录后，才能调用本接口。  <br>
 *       + 调用本接口后，SDK 会使用 rtsEngine:onServerParamsSetResult:{@link #RTSDelegate#rtsEngine:onServerParamsSetResult:} 返回相应结果。
 */
/** {en}
 * @type api
 * @region Real-time messaging
 * @brief Set application server parameters   <br>
 *        Client side calls sendServerMessage:{@link #RTS#sendServerMessage:} or sendServerBinaryMessage:{@link #RTS#sendServerBinaryMessage:} Before sending a message to the application server, you must set a valid signature and application server address.
 * @param signature Dynamic signature. The App server may use the signature to verify the source of messages.<br>
 *        You need to define the signature yourself. It can be any non-empty string. It is recommended to encode information such as UID into the signature.<br>
 *        The signature will be sent to the address set through the "url" parameter in the form of a POST request.
 * @param url The address of the application server.
 * @return  <br>
 *        + 0: Success.
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @notes  <br>
 *        + The user must call login:uid:{@link #RTS#login:uid:} before logging in to call this API. <br>
 *        + After calling this API, the SDK will use rtsEngine:onServerParamsSetResult:{@link #RTSDelegate#rtsEngine:onServerParamsSetResult:} to return the corresponding result.
 */
- (int)setServerParams:(NSString * _Nonnull)signature url:(NSString * _Nonnull)url;
/** {zh}
 * @type api
 * @region 实时消息通信
 * @brief 查询本地/远端用户的登录状态。<br>
 *        在发送消息之前，用户可以通过本接口了解对端用户是否登录，从而决定是否发送消息。也可以通过本接口查询自己查看自己的登录状态。
 * @param peerUserId  需要查询的用户 ID
 * @return  <br>
 *        + 0: 调用成功。
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @notes  <br>
 *       + 必须调用 login:uid:{@link #RTS#login:uid:} 登录后，才能调用本接口。  <br>
 *       + 调用本接口后，SDK 会使用 rtsEngine:onGetPeerOnlineStatus:status:{@link #RTSDelegate#rtsEngine:onGetPeerOnlineStatus:status:} 回调通知查询结果。  <br>
 */
/** {en}
 * @type api
 * @region Real-time messaging
 * @brief Queries the login status of local/remote users.<br>
 *        Before sending a message, you can know whether the peer user is logged in through this API to decide whether to send a message. You can also check your login status through this API.
 * @param peerUserId ID of the user to be queried.
 * @return  <br>
 *        + 0: Success.
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @notes  <br>
 *        + You must call login:uid:{@link #RTS#login:uid:} After logging in, you can call this API. <br>
 *        + After calling this API, the SDK will use rtsEngine:onGetPeerOnlineStatus:status:{@link #RTSDelegate#rtsEngine:onGetPeerOnlineStatus:status:} callback to notify the query result. <br>
 */
- (int)getPeerOnlineStatus:(NSString * _Nonnull)peerUserId;
/** {zh}
 * @type api
 * @region 实时消息通信
 * @brief 给指定的用户发送点对点文本消息（p2p）
 * @param userId 消息接收用户的 ID
 * @param messageStr 发送的文本消息内容，消息不超过 64KB。
 * @return 方法调用结果： <br>
 *        + >0：发送成功，返回这次发送消息的编号，从 1 开始递增  <br>
 *        + -1：发送失败，RTS 引擎实例未创建  <br>
 *        + -2：发送失败，userId 为空
 * @notes  <br>
 *       + 在发送点对点文本消息前，必须先调用 login:uid:{@link #RTS#login:uid:} 完成登录。  <br>
 *       + 用户调用本接口发送文本信息后，会收到一次 rtsEngine:onMessageSendResult:error:{@link #RTSDelegate#rtsEngine:onMessageSendResult:error:} 回调，得知消息是否成功发送。<br>
 *       + 若文本消息发送成功，则 userId 所指定的用户会通过 rtsEngine:onMessageReceived:message:{@link #RTSDelegate#rtsEngine:onMessageReceived:message:} 回调收到该消息。
 */
/** {en}
 * @type api
 * @region Real-time messaging
 * @brief Sends a text message to a specified user (p2p).
 * @param userId Message receiver's user ID.
 * @param messageStr Message content, not exceeding 64KB.
 * @return  API call result: <br>
 *         + > 0: Sent successfully, return the number of the sent message, increment from 1 <br>
 *         + -1: Sent failed, there is no created engine instance <br>
 *         + -2: Sent failed, userId is empty
 * @notes  <br>
 *        + Before sending a p2p text message, you should call login:uid:{@link #RTS#login:uid:} to complete login. <br>
 *        + After the user calls this API to send a text message, he will receive an rtsEngine:onUserMessageSendResultOutsideRoom:error:{@link #RTSDelegate#rtsEngine:onUserMessageSendResultOutsideRoom:error:} callback to know whether the message was sent successfully. <br>
 *        + If the text message is sent successfully, the user specified by the userId will receive the message through rtsEngine:onUserMessageReceivedOutsideRoom:message:{@link #RTSDelegate#rtsEngine:onUserMessageReceivedOutsideRoom:message:} callback.
 */
- (int64_t)sendMessage:(NSString * _Nonnull)userId message:(NSString * _Nonnull)messageStr config:(int)config;
/** {zh}
 * @type api
 * @region 实时消息通信
 * @brief 给指定的用户发送点对点二进制消息（P2P）。
 * @param userId 消息接收用户的 ID
 * @param messageStr 发送的二进制消息内容，不超过 46KB。
 * @return 方法调用结果： <br>
 *        + >0：发送成功，返回这次发送消息的编号，从 1 开始递增  <br>
 *        + -1：发送失败，RTS 引擎实例未创建  <br>
 *        + -2：发送失败，userId 为空
 * @notes <br>
 *       + 在发送点对点二进制消息前，必须先调用 login:uid:{@link #RTS#login:uid:} 完成登录。  <br>
 *       + 用户调用本接口发送二进制消息后，会收到一次 rtsEngine:onMessageSendResult:error:{@link #RTSDelegate#rtsEngine:onMessageSendResult:error:} 回调，通知消息是否发送成功。<br>
 *       + 若二进制消息发送成功，则 userId 所指定的用户会通过 rtsEngine:onBinaryMessageReceived:message:{@link #RTSDelegate#rtsEngine:onBinaryMessageReceived:message:}  回调收到该条消息。
 */
/** {en}
 * @type api
 * @region Real-time messaging
 * @brief Sends binary messages to the specified user outside the room (P2P).
 * @param userId Message receiver's user ID.
 * @param messageStr Message content, not exceeding 46KB.
 * @return API call result: <br>
 *         + > 0: Sent successfully, return the number of the sent message, increment from 1 <br>
 *         + -1: Sent failed, there is no created engine instance <br>
 *         + -2: Sent failed, userId is empty
 * @notes  <br>
 *        + Before sending a p2p binary message, you must call login:uid:{@link #RTS#login:uid:} to complete login. <br>
 *        + After the user calls this API to send a binary message, he will receive an rtsEngine:onUserMessageSendResultOutsideRoom:error:{@link #RTSDelegate#rtsEngine:onUserMessageSendResultOutsideRoom:error:} callback to notify whether the message was sent successfully. <br>
 *        + If the binary message is sent successfully, the user specified by the userId will use rtsEngine:onBinaryMessageReceived:message:{@link #RTSDelegate#rtsEngine:onBinaryMessageReceived:message:} callback Receive the message.
 */
- (int64_t)sendBinaryMessage:(NSString * _Nonnull)userId message:(NSData * _Nonnull)messageStr config:(int)config;
/** {zh}
 * @type api
 * @region 实时消息通信
 * @brief 客户端给应用服务器发送文本消息（P2Server）。
 * @param messageStr 发送的文本消息内容，不超过 64KB。
 * @return 方法调用结果： <br>
 *        + >0：发送成功，返回这次发送消息的编号，从 1 开始递增  <br>
 *        + -1：发送失败，RTS 引擎实例未创建
 * @notes  <br>
 *       + 在向应用服务器发送文本消息前，必须先调用 login:uid:{@link #RTS#login:uid:} 完成登录，随后调用 setServerParams:url:{@link #RTS#setServerParams:url:} 设置应用服务器。  <br>
 *       + 调用本接口后，会收到一次 rtsEngine:onServerMessageSendResult:error:message:{@link #RTSDelegate#rtsEngine:onServerMessageSendResult:error:message:} 回调，通知消息发送方是否发送成功。  <br>
 *       + 若文本消息发送成功，则之前调用 setServerParams:url:{@link #RTS#setServerParams:url:} 设置的应用服务器会收到该条消息。
 */
/** {en}
 * @type api
 * @region Real-time messaging
 * @brief Sends a text message to the application server (P2Server).
 * @param messageStr Message content, not exceeding 64KB.
 * @return API call result: <br>
 *         + > 0: Sent successfully, return the number of the sent message, increment from 1 <br>
 *         + -1: Sent failed, there is no created engine instance
 * @notes  <br>
 *        + Before sending a text message to the application server, you must first call login:uid:{@link #RTS#login:uid:} to complete the login, and then call setServerParams:url:{@link #RTS#setServerParams:url:} Set up the application server. <br>
 *        + After calling this API, you will receive an rtsEngine:onServerMessageSendResult:error:message:{@link #RTSDelegate#rtsEngine:onServerMessageSendResult:error:message:} callback to inform the message sender whether the message was sent successfully. <br>
 *        + If the text message is sent successfully, the application server that previously called setServerParams:url:{@link #RTS#setServerParams:url:} will receive the message.
 */
- (int64_t)sendServerMessage:(NSString * _Nonnull)messageStr;
/** {zh}
 * @type api
 * @region 实时消息通信
 * @brief 客户端给应用服务器发送二进制消息（P2Server）。
 * @param messageStr 发送的二进制消息内容，消息不超过 46KB。
 * @return 方法调用结果： <br>
 *        + >0：发送成功，返回这次发送消息的编号，从 1 开始递增  <br>
 *        + -1：发送失败，RTS 引擎实例未创建
 * @notes  <br>
 *       + 在向应用服务器发送二进制消息前，先调用 login:uid:{@link #RTS#login:uid:} 完成登录，随后调用 setServerParams:url:{@link #RTS#setServerParams:url:} 设置应用服务器。  <br>
 *       + 调用本接口后，会收到一次 rtsEngine:onServerMessageSendResult:error:message:{@link #RTSDelegate#rtsEngine:onServerMessageSendResult:error:message:} 回调，通知消息发送方发送成功或失败；  <br>
 *       + 若二进制消息发送成功，则之前调用 setServerParams:url:{@link #RTS#setServerParams:url:} 设置的应用服务器会收到该条消息。
 */
/** {en}
 * @type api
 * @region Real-time messaging
 * @brief Sends binary messages to the application server (P2Server).
 * @param messageStr Message content, not exceedingå 46KB.
 * @return API call result: <br>
 *         + > 0: Send successfully, return the number of the sent message, increment from 1 <br>
 *         + -1: Send failed, there is no created engine instance
 * @notes  <br>
 *        + Before sending a binary message to the application server, call login:uid:{@link #RTS#login:uid:} to complete the login, then call setServerParams:url:{@link #RTS#setServerParams:url:} Set up the application server. <br>
 *        + After calling this API, you will receive an rtsEngine:onServerMessageSendResult:error:message:{@link #RTSDelegate#rtsEngine:onServerMessageSendResult:error:message:} callback to inform the message sender that the sending succeeded or failed; <br>
 *        + If the binary message is sent successfully, the application server that previously called setServerParams:url:{@link #RTS#setServerParams:url:} will receive the message.
 */
- (int64_t)sendServerBinaryMessage:(NSData *_Nonnull)messageStr;
/** {zh}
 * @type api
 * @brief 启用蜂窝网络辅助增强，改善通话质量。
 * @param enhance 是否开启。默认不开启。
 * @return 方法调用结果：  <br>
 *        + 0: 成功。<br>
 *        + -1：失败，内部错误。 <br>
 */
/** {en}
 * @type api
 * @brief Enable cellular network assisted communication to improve call quality.
 * @param enhance Enable or not. Off by default.
 * @return Method call result:   <br>
 *        + 0: Success. <br>
 *        + -1: Failure, internal error. <br>
 */
- (int)setCellularEnhancement:(BOOL)enhance;

/** {zh}
 * @type api
 * @region 代理
 * @brief 设置本地代理。
 * @param configurations 本地代理配置参数。参看 ByteRTCLocalProxyInfo{@link #ByteRTCLocalProxyInfo}。 <br>
 *        你可以根据自己的需要选择同时设置 Http 隧道 和 Socks5 两类代理，或者单独设置其中一类代理。如果你同时设置了 Http 隧道 和 Socks5 两类代理，此时，媒体和信令采用 Socks5 代理， Http 请求采用 Http 隧道代理；如果只设置 Http 隧道 或 Socks5 一类代理，媒体、信令和 Http 请求均采用已设置的代理。 <br>
 *        调用此接口设置本地代理后，若想清空当前已有的代理设置，可再次调用此接口，选择不设置任何代理即可清空。
 * @notes <br>
 *       + 该方法需要在进房前调用。<br>
 *       + 调用该方法设置本地代理后，SDK 会触发 rtsEngine:onLocalProxyStateChanged:withProxyState:withProxyError:{@link #RTSDelegate#rtsEngine:onLocalProxyStateChanged:withProxyState:withProxyError:} ，返回代理连接的状态。
 */
/** {en}
 * @type api
 * @region proxy
 * @brief Sets local proxy.
 * @param configurations Local proxy configurations. Refer to ByteRTCLocalProxyInfo{@link #ByteRTCLocalProxyInfo} for details. <br>
 *         You can set both Http tunnel and Socks5 as your local proxies, or only set one of them based on your needs. If you set both Http tunnel and Socks5 as your local proxies, then media traffic and signaling are routed through Socks5 proxy and Http requests through Http tunnel proxy. If you set either Http tunnel or Socks5 as your local proxy, then media traffic, signaling and Http requests are all routed through the proxy you chose. <br>
 *         If you want to remove the existing local proxy configurations, you can call this API with the parameter set to null. 
 * @notes <br>
 *       + You must call this API before joining the room.  <br>
 *       + After calling this API, you will receive rtcEngine:onLocalProxyStateChanged:withProxyState:withProxyError:{@link #RTSDelegate#rtcEngine:onLocalProxyStateChanged:withProxyState:withProxyError:withProxyError:} callback that informs you of the states of local proxy connection. 
 */
- (int)setLocalProxy:(NSArray <ByteRTCLocalProxyInfo *> * _Nonnull)configurations;

@end
