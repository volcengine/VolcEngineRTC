/*
 * Copyright (c) 2022 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief RTS
*/

#import <UIKit/UIKit.h>
#import "rtc/ByteRTCRtsDefines.h"

@class RTS;
@class RTSRoom;

#pragma mark - RTSDelegate
/** 
 * @type callback
 * @brief RTSDelegate 协议包含了SDK提供的回调方法，SDK通过代理向应用程序上报一些运行时事件
 */
@protocol RTSDelegate <NSObject>
@optional

#pragma mark - Engine Management Delegate Methods
/** 
 * @type callback
 * @region 引擎管理
 * @brief SDK 与信令服务器连接状态改变回调。连接状态改变时触发。
 * @param engine RTS 对象。
 * @param state 当前 SDK 与信令服务器连接状态。详细定义参见 ByteRTCConnectionState{@link #ByteRTCConnectionState} <br>
 * @notes 更多信息参见 [连接状态提示](https://www.volcengine.com/docs/6348/95376)。
 */
- (void)rtsEngine:(RTS * _Nonnull)engine onConnectionStateChanged:(ByteRTCConnectionState)state;
/** 
 * @type callback
 * @region 引擎管理
 * @brief SDK 当前网络连接类型改变回调。当 SDK 的当前网络连接类型发生改变时回调该事件。
 * @param engine RTS 对象。
 * @param type SDK 当前的网络连接类型。参看 ByteRTCNetworkType{@link #ByteRTCNetworkType}。
 */
- (void)rtsEngine:(RTS * _Nonnull)engine onNetworkTypeChanged:(ByteRTCNetworkType)type;

/** 
 * @type callback
 * @region 引擎管理
 * @brief 创建房间失败回调。
 * @param engine RTS 对象。
 * @param roomId 房间 ID。
 * @param errorCode 创建房间错误码：<br>
 *        + -1007：无效 roomId； <br>
 *        + -1013：相同 roomId 的房间已存在。
 */
- (void)rtsEngine:(RTS *_Nonnull)engine onCreateRoomStateChanged:(NSString * _Nonnull)roomId errorCode:(NSInteger)errorCode;

#pragma mark - Data Statistics Delegate Methods
/** 
 * @type callback
 * @region 引擎管理
 * @brief 周期性（2s）地发出回调，报告当前 cpu 与内存的使用率
 * @param engine RTS 对象
 * @param stats 返回包含当前系统状态信息的结构体，详见 ByteRTCSysStats{@link #ByteRTCSysStats}
 */
- (void)rtsEngine:(RTS * _Nonnull)engine onSysStats:(const ByteRTCSysStats * _Nonnull)stats;

#pragma mark - Real-time Messaging Delegate Methods
/** 
 * @type callback
 * @region 实时消息通信
 * @brief 登录 RTS 服务器结果回调。
 * @param engine RTS 对象
 * @param uid 登录用户 ID
 * @param errorCode 登录结果，详见 ByteRTCLoginErrorCode{@link #ByteRTCLoginErrorCode}。
 * @param elapsed 从调用 login:uid:{@link #RTS#login:uid:} 接口开始到返回结果所用时长，单位为 ms。
 * @notes 调用 login:uid:{@link #RTS#login:uid:} 后，会收到此回调。
 */
- (void)rtsEngine:(RTS * _Nonnull)engine onLoginResult:(NSString * _Nonnull)uid
        errorCode:(ByteRTCLoginErrorCode)errorCode elapsed:(NSInteger)elapsed;
/** 
 * @type callback
 * @region 实时消息通信
 * @brief 登出结果回调
 * @param engine RTS 对象
 * @notes 调用 logout{@link #RTS#logout} 后，会收到此回调。
 */
- (void)rtsEngineOnLogout:(RTS * _Nonnull)engine;
/** 
 * @type callback
 * @region 实时消息通信
 * @brief 设置应用服务器参数的返回结果
 * @param engine RTS 对象
 * @param errorCode 设置结果：
 *        + 返回 200，设置成功  <br>
 *        + 返回其他，设置失败
 * @notes 调用 setServerParams:url:{@link #RTS#setServerParams:url:} 后，会收到此回调。
 */
- (void)rtsEngine:(RTS * _Nonnull)engine onServerParamsSetResult:(NSInteger)errorCode;
/** 
 * @type callback
 * @region 实时消息通信
 * @brief 查询对端或本端用户登录状态的返回结果
 * @param engine RTS 对象
 * @param peerUserId 需要查询的用户 ID
 * @param status 查询的用户登录状态，详见 ByteRTCUserOnlineStatus{@link #ByteRTCUserOnlineStatus}.
 * @notes 必须先调用 getPeerOnlineStatus:{@link #RTS#getPeerOnlineStatus:}，才能收到此回调。
 */
- (void)rtsEngine:(RTS * _Nonnull)engine onGetPeerOnlineStatus:(NSString * _Nonnull)peerUserId
           status:(ByteRTCUserOnlineStatus)status;
/** 
 * @type callback
 * @region 实时消息通信
 * @brief 收到远端用户调用 sendMessage:message:config:{@link #RTS#sendMessage:message:config:} 发来的文本消息时，会收到此回调。
 * @param engine RTS 对象
 * @param uid 消息发送者 ID
 * @param message 收到的文本消息内容
 */
- (void)rtsEngine:(RTS * _Nonnull)engine onMessageReceived:(NSString * _Nonnull)uid
          message:(NSString * _Nonnull)message;
/** 
 * @type callback
 * @region 实时消息通信
 * @brief 收到房间外用户调用 sendBinaryMessage:message:config:{@link #RTS#sendBinaryMessage:message:config:} 发来的二进制消息时，会收到此回调。
 * @param engine RTS 对象
 * @param uid 消息发送者 ID
 * @param message 收到的二进制消息内容
 */
- (void)rtsEngine:(RTS * _Nonnull)engine onBinaryMessageReceived:(NSString * _Nonnull)uid
          message:(NSData * _Nonnull)message;
/** 
 * @type callback
 * @region 实时消息通信
 * @brief 发送 p2p 消息的结果回调。
 * @param engine RTS 对象
 * @param msgid 本条消息的 ID。所有的 P2P 和 P2Server 消息共用一个 ID 序列。
 * @param error 消息发送结果，详见 ByteRTCUserMessageSendResult{@link #ByteRTCUserMessageSendResult}。
 * @notes 当调用 sendMessage:message:config:{@link #RTS#sendMessage:message:config:} 或 sendBinaryMessage:message:config:{@link #RTS#sendBinaryMessage:message:config:} 发送消息后，会收到此回调。
 */
- (void)rtsEngine:(RTS * _Nonnull)engine onMessageSendResult:(int64_t)msgid
            error:(ByteRTCUserMessageSendResult)error;
/** 
 * @type callback
 * @region 实时消息通信
 * @brief 发送 p2server 消息的结果回调。
 * @param engine RTS 对象
 * @param msgid 本条消息的 ID。所有的 P2P 和 P2Server 消息共用一个 ID 序列。
 * @param error 消息发送结果。详见 ByteRTCUserMessageSendResult{@link #ByteRTCUserMessageSendResult}。
 * @notes 当调用 sendServerMessage:{@link #RTS#sendServerMessage:} 或 sendServerBinaryMessage:{@link #RTS#sendServerBinaryMessage:} 接口发送消息后，会收到此回调。
 */
- (void)rtsEngine:(RTS * _Nonnull)engine onServerMessageSendResult:(int64_t)msgid
            error:(ByteRTCUserMessageSendResult)error message:(NSData * _Nonnull)message;

@end

#pragma mark - RTS
/** 
 * @type api
 * @region 引擎管理
 * @brief SDK 回调给应用层的 delegate 对象
 */
BYTERTC_APPLE_EXPORT @interface RTS : NSObject

@property(nonatomic, weak) id<RTSDelegate> _Nullable delegate;

#pragma mark - Engine Management Methods
/** 
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
+ (RTS * _Nullable)createRTS:(NSString * _Nonnull)appId
                    delegate:(id<RTSDelegate> _Nullable)delegate
                  parameters:(NSDictionary* _Nullable)parameters;
/** 
 * @type api
 * @region 引擎管理
 * @brief 销毁引擎实例对象。
 * @notes  <br>
 *      + 请确保和需要销毁的 RTS 实例相关的业务场景全部结束后，才调用此方法。  <br>
 *      + 该方法在调用之后，会销毁所有和此 RTS 实例相关的内存，并且停止与媒体服务器的任何交互。  <br>
 *      + 调用本方法会启动 SDK 退出逻辑。引擎线程会保留，直到退出逻辑完成。因此，不要在回调线程中直接调用此 API，也不要在回调中等待主线程的执行，并同时在主线程调用本方法。不然会造成死锁。  <br>
 *      + 可以通过 Objective-C 的ARC机制，在 dealloc 时自动触发销毁逻辑。
 */
+ (void)destroyRTS;

/** 
 * @type api
 * @region 引擎管理
 * @brief 获取 SDK 当前的版本号。
 * @return SDK 当前的版本号。
 */
+ (NSString * _Nonnull)getSdkVersion;
/** 
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
- (int)setBusinessId:(NSString* _Nullable)businessId;
/** 
 * @type api
 * @brief 设置运行时的参数
 * @param parameters 保留参数
 */
- (void)setRuntimeParameters:(NSDictionary * _Nullable)parameters;

#pragma mark - Multi-room Methods
/** 
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
- (RTSRoom * _Nullable)createRoom:(NSString * _Nonnull)roomId;

#pragma mark - Real-time Messaging Methods
/** 
 * @type api
 * @region 实时消息通信
 * @brief 登录 RTS 服务器。 <br>
 *        必须先登录，才能收发消息。<br>
 *        在调用本接口登录后，如果想要登出，需要调用 logout{@link #RTS#logout}
 * @param token 用户登录必须携带的动态密钥，用于鉴权验证。  <br>
 *        登录 Token 与加入房间时必须携带的 Token 不同。测试时可使用控制台生成临时 Token，正式上线需要使用密钥 SDK 在你的服务端生成并下发 Token。
 * @param uid 用户 ID， 在 appid 的维度下唯一。
 * @return 方法调用结果：<br>
 *        + `0`：成功<br>
 *        + `-1`：失败。无效参数<br>
 *        + `-2`：无效调用。用户已经登录。成功登录后再次调用本接口将收到此返回值 <br>
 *        + `-3`：失败。Engine 为空。
 * @notes  本地用户调用此方法登录后，会收到 rtcEngine:onLoginResult:errorCode:elapsed:{@link #RTSDelegate#rtsEngine:onLoginResult:errorCode:elapsed:} 回调通知登录结果。
 */
- (int64_t)login:(NSString * _Nonnull)token uid:(NSString * _Nonnull)uid;
/** 
 * @type api
 * @region 实时消息通信
 * @brief 登出 RTS 服务器。 <br>
 *        调用本接口登出后，无法再调用消息相关的方法或收到相关回调。
 * @notes 本地用户调用此方法登出后，会收到 rtcEngineOnLogout:{@link #RTSDelegate#rtsEngineOnLogout:}  回调通知结果，远端用户不会收到通知。
 */
- (void)logout;
/** 
 * @type api
 * @region 实时消息通信
 * @brief 更新用户用于登录的 Token  <br>
 *        Token 有一定的有效期，当 Token 过期时，需调用此方法更新登录的 Token 信息。  <br>
 *        调用 login:uid:{@link #RTS#login:uid:} 方法登录时，如果使用了过期的 Token 将导致登录失败，并会收到 rtcEngine:onLoginResult:errorCode:elapsed:{@link #RTSDelegate#rtsEngine:onLoginResult:errorCode:elapsed:} 回调通知，错误码为 ByteRTCLoginErrorCodeInvalidToken。此时需要重新获取 Token，并调用此方法更新 Token。
 * @param token  <br>
 *        更新的动态密钥  <br>
 * @notes  <br>
 *       + 如果 Token 无效导致登录失败，则调用此方法更新 Token 后，SDK 会自动重新登录，而用户不需要自己调用 login:uid:{@link #RTS#login:uid:} 方法。  <br>
 *       + Token 过期时，如果已经成功登录，则不会受到影响。Token 过期的错误会在下一次使用过期 Token 登录时，或因本地网络状况不佳导致断网重新登录时通知给用户。
 */
- (void)updateLoginToken:(NSString * _Nonnull)token;
/** 
 * @type api
 * @region 实时消息通信
 * @brief 设置应用服务器参数  <br>
 *        客户端调用 sendServerMessage:{@link #RTS#sendServerMessage:} 或 sendServerBinaryMessage:{@link #RTS#sendServerBinaryMessage:} 发送消息给应用服务器之前，必须需要设置有效签名和应用服务器地址。
 * @param signature 动态签名  <br>
 *        应用服务器会使用该签名对请求进行鉴权验证。  <br>
 * @param url 应用服务器的地址
 * @notes  <br>
 *       + 用户必须调用 login:uid:{@link #RTS#login:uid:} 登录后，才能调用本接口。  <br>
 *       + 调用本接口后，SDK 会使用 rtcEngine:onServerParamsSetResult:{@link #RTSDelegate#rtsEngine:onServerParamsSetResult:} 返回相应结果。
 */
- (void)setServerParams:(NSString * _Nonnull)signature url:(NSString * _Nonnull)url;
/** 
 * @type api
 * @region 实时消息通信
 * @brief 查询本地/远端用户的登录状态。<br>
 *        在发送消息之前，用户可以通过本接口了解对端用户是否登录，从而决定是否发送消息。也可以通过本接口查询自己查看自己的登录状态。
 * @param peerUserId  需要查询的用户 ID
 * @notes  <br>
 *       + 必须调用 login:uid:{@link #RTS#login:uid:} 登录后，才能调用本接口。  <br>
 *       + 调用本接口后，SDK 会使用 rtcEngine:onGetPeerOnlineStatus:status:{@link #RTSDelegate#rtsEngine:onGetPeerOnlineStatus:status:} 回调通知查询结果。  <br>
 */
- (void)getPeerOnlineStatus:(NSString * _Nonnull)peerUserId;
/** 
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
 *       + 用户调用本接口发送文本信息后，会收到一次 rtcEngine:onUserMessageSendResultOutsideRoom:error:{@link #RTSDelegate#rtsEngine:onUserMessageSendResultOutsideRoom:error:} 回调，得知消息是否成功发送；  <br>
 *       + 若文本消息发送成功，则 userId 所指定的用户会通过 rtcEngine:onUserMessageReceivedOutsideRoom:message:{@link #RTSDelegate#rtsEngine:onUserMessageReceivedOutsideRoom:message:} 回调收到该消息。
 */
- (int64_t)sendMessage:(NSString * _Nonnull)userId message:(NSString * _Nonnull)messageStr config:(int)config;
/** 
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
 *       + 用户调用本接口发送二进制消息后，会收到一次 rtcEngine:onUserMessageSendResultOutsideRoom:error:{@link #RTSDelegate#rtsEngine:onUserMessageSendResultOutsideRoom:error:} 回调，通知消息是否发送成功；  <br>
 *       + 若二进制消息发送成功，则 userId 所指定的用户会通过 rtcEngine:onUserBinaryMessageReceivedOutsideRoom:message:{@link #RTSDelegate#rtsEngine:onUserBinaryMessageReceivedOutsideRoom:message:}  回调收到该条消息。
 */
- (int64_t)sendBinaryMessage:(NSString * _Nonnull)userId message:(NSData * _Nonnull)messageStr config:(int)config;
/** 
 * @type api
 * @region 实时消息通信
 * @brief 客户端给应用服务器发送文本消息（P2Server）。
 * @param messageStr 发送的文本消息内容，不超过 64KB。
 * @return 方法调用结果： <br>
 *        + >0：发送成功，返回这次发送消息的编号，从 1 开始递增  <br>
 *        + -1：发送失败，RTS 引擎实例未创建
 * @notes  <br>
 *       + 在向应用服务器发送文本消息前，必须先调用 login:uid:{@link #RTS#login:uid:} 完成登录，随后调用 setServerParams:url:{@link #RTS#setServerParams:url:} 设置应用服务器。  <br>
 *       + 调用本接口后，会收到一次 rtcEngine:onServerMessageSendResult:error:message:{@link #RTSDelegate#rtsEngine:onServerMessageSendResult:error:message:} 回调，通知消息发送方是否发送成功。  <br>
 *       + 若文本消息发送成功，则之前调用 setServerParams:url:{@link #RTS#setServerParams:url:} 设置的应用服务器会收到该条消息。
 */
- (int64_t)sendServerMessage:(NSString * _Nonnull)messageStr;
/** 
 * @type api
 * @region 实时消息通信
 * @brief 客户端给应用服务器发送二进制消息（P2Server）。
 * @param messageStr 发送的二进制消息内容，消息不超过 46KB。
 * @return 方法调用结果： <br>
 *        + >0：发送成功，返回这次发送消息的编号，从 1 开始递增  <br>
 *        + -1：发送失败，RTS 引擎实例未创建
 * @notes  <br>
 *       + 在向应用服务器发送二进制消息前，先调用 login:uid:{@link #RTS#login:uid:} 完成登录，随后调用 setServerParams:url:{@link #RTS#setServerParams:url:} 设置应用服务器。  <br>
 *       + 调用本接口后，会收到一次 rtcEngine:onServerMessageSendResult:error:message:{@link #RTSDelegate#rtsEngine:onServerMessageSendResult:error:message:} 回调，通知消息发送方发送成功或失败；  <br>
 *       + 若二进制消息发送成功，则之前调用 setServerParams:url:{@link #RTS#setServerParams:url:} 设置的应用服务器会收到该条消息。
 */
- (int64_t)sendServerBinaryMessage:(NSData * _Nonnull)messageStr;

@end
