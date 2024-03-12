/*
 * Copyright (c) 2020 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC Interface
 */

#pragma once

#include <stddef.h>
#include <stdio.h>
#include <stdarg.h>
#include <memory>
#include "rtc/bytertc_rts_defines.h"
#include "byterts_event_handler.h"
#include "byterts_room.h"

namespace bytertc {

class IRTSRoomEventHandler;
/** {zh}
 * @type api
 * @brief 引擎API
 *      IRtcEngine用IRTSEventHandler 注册接口类方法向应用程序发送回调通知
 */
/** {en}
 * @type api
 * @brief Engine API
 *      IRtcEngine uses IRtcEngineering EventHandler to register interface class methods to send callback notifications to applications
 */
class IRTS {
public:

    /** {zh}
     * @hidden constructor/destructor
     * @brief 析构函数
     */
    /** {en}
     * @hidden constructor/destructor
     * @brief Destructor
     */
    virtual ~IRTS() {
    }

    /** {zh}
     * @type api
     * @region 引擎管理
     * @brief 设置业务标识参数  <br>
     *        可通过 businessId 区分不同的业务场景。businessId 由客户自定义，相当于一个“标签”，可以分担和细化现在 AppId 的逻辑划分的功能，但不需要鉴权。
     * @param [in] business_id  <br>
     *        用户设置的自己的 businessId 值
     *        businessId 只是一个标签，颗粒度需要用户自定义。
     * @return  <br>
     *        + 0： 成功  <br>
     *        + < 0： 失败，具体原因参照 BusinessCheckCode{@link #BusinessCheckCode} 。  <br>
     *        + -6001： 用户已经在房间中。  <br>
     *        + -6002： 输入非法，合法字符包括所有小写字母、大写字母和数字，除此外还包括四个独立字符，分别是：英文句号，短横线，下划线和 @ 。
     * @notes  <br>
     *        + 需要在进房之前调用，进房之后调用该方法无效。
     */
    /** {en}
     * @type api
     * @region Engine management
     * @brief  Sets the business ID   <br>
     *         You can use businessId to distinguish different business scenarios. You can customize your businessId to serve as a sub AppId, which can share and refine the function of the AppId, but it does not need authentication.
     * @param  [in] business_id <br>
     *         Your customized businessId
     *         BusinessId is a tag, and you can customize its granularity.
     * @return   <br>
     *         + 0: Success <br>
     *         + < 0: Failure. See BusinessCheckCode{@link #BusinessCheckCode} for specific reasons. <br>
     *         + -6001: The user is already in the room. <br>
     *         + -6002: The input is invalid. Legal characters include all lowercase letters, uppercase letters, numbers, and four other symbols, including '.', '-','_', and '@'.
     * @notes   <br>
     *         + You must call this API before joining a room, otherwise it will be invalid.
     */
    virtual int setBusinessId(const char* business_id) = 0;

    /** {zh}
     * @type api
     * @region 实时消息通信
     * @brief 登录 RTS 服务器。
     *        必须先登录，才能发送点对点消息和向应用服务器发送消息<br>
     *        在调用本接口登录后，如果想要登出，需要调用 logout{@link #IRTS#logout}。  <br>
     * @param [in]token  用户登录必须携带的 Token，用于鉴权验证。
     *               测试时可使用[控制台](https://console.volcengine.com/rtc/listRTC)生成临时 Token，`roomId` 填任意值。
     *               正式上线需要使用密钥 SDK 在你的服务端生成并下发 Token，`roomId` 置空，Token 有效期及生成方式参看[使用 Token 完成鉴权](70121)。
     * @param [in] uid  <br>
     *        用户 ID  <br>
     *        用户 ID 在 appid 的维度下是唯一的。
     * @return <br>
     *        + `0`：成功<br>
     *        + `-1`：失败。无效参数<br>
     *        + `-2`：无效调用。用户已经登录。成功登录后再次调用本接口将收到此返回值 <br>
     * @notes 本地用户调用此方法登录后，会收到 onLoginResult{@link #IRTSEventHandler#onLoginResult} 回调通知登录结果，远端用户不会收到通知。
     */
    /** {en}
     * @type api
     * @region Real-time messaging
     * @brief Log in to send P2P messages or send messages to a server.<br>
     *        To log out, call logout{@link #IRTS#logout}. <br>
     * @param  [in] token <br>
     *        Token is required during login for authentication. <br>
     *        This Token is different from that required by calling joinRoom. You can assign any value even null to `roomId` to generate a login token. During developing and testing, you can use temporary tokens generated on the console. Deploy the token generating application on your server.
     * @param  [in] uid <br>
     *        User ID <br>
     *        User ID is unique within one appid.
     * @return <br>
     *        + `0`: Success<br>
     *        + `-1`: Failure due to invalid parameter<br>
     *        + `-2`: Invalid call. RTC will return this value when you call this API after the user has been logged in to the server. <br>
     * @notes  You will receive onLoginResult{@link #IRTSEventHandler#onLoginResult} after calling this API and log in successfully. But remote users will not receive notification about that.
     */
    virtual int login(const char* token, const char* uid) = 0;

    /** {zh}
     * @type api
     * @region 实时消息通信
     * @brief 调用本接口登出后，无法调用房间外消息以及端到服务器消息相关的方法或收到相关回调。
     * @return  <br>
     *        + 0: 调用成功。
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @notes  <br>
     *       + 调用本接口登出前，必须先调用 login{@link #IRTS#login} 登录。  <br>
     *       + 本地用户调用此方法登出后，会收到 onLogout{@link #IRTSEventHandler#onLogout} 回调通知结果，远端用户不会收到通知。
     */
    /** {en}
     * @type After api
     * @region  real-time messaging
     * @brief  Calls this interface to log out, it is impossible to call methods related to out-of-room messages and end-to-server messages or receive related callbacks.
     * @return  <br>
     *        + 0: Success.
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @notes   <br>
     *        + Before calling this interface to log out, you must call login{@link #IRTS#login} to log in. <br>
     *        + After local users call this method to log out, they will receive the result of the onLogout{@link #IRTSEventHandler#onLogout} callback notification, and remote users will not receive the notification.
     */
    virtual int logout() = 0;

    /** {zh}
     * @type api
     * @region 实时消息通信
     * @brief 更新用户用于登录的 Token  <br>
     *        Token 有一定的有效期，当 Token 过期时，需调用此方法更新登录的 Token 信息。  <br>
     *        调用 login{@link #IRTS#login} 方法登录时，如果使用了过期的 Token 将导致登录失败，并会收到 onLoginResult{@link #IRTSEventHandler#onLoginResult} 回调通知，错误码为 kLoginErrorCodeInvalidToken。此时需要重新获取 Token，并调用此方法更新 Token。
     * @param [in] token  <br>
     *        更新的动态密钥
     * @return  <br>
     *        + 0: 调用成功。
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @notes  <br>
     *       + 如果 Token 无效导致登录失败，则调用此方法更新 Token 后，SDK 会自动重新登录，而用户不需要自己调用 login{@link #IRTS#login} 方法。  <br>
     *       + Token 过期时，如果已经成功登录，则不会受到影响。Token 过期的错误会在下一次使用过期 Token 登录时，或因本地网络状况不佳导致断网重新登录时通知给用户。
     */
    /** {en}
     * @type api
     * @region Real-time messaging
     * @brief Update the Token <br>
     *        Token used by the user to log in has a certain valid period. When the Token expires, you need to call this method to update the login Token information. <br>
     *         When calling the login{@link #IRTS#login} method to log in, if an expired token is used, the login will fail and you will receive an onLoginResult{@link #IRTSEventHandler#onLoginResult} callback notification with an error code of kLoginErrorCodeInvalidToken. You need to reacquire the token and call this method to update the token.
     * @param  [in] token <br>
     *        Updated dynamic key
     * @return  <br>
     *        + 0: Success.
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @notes   <br>
     *        + If the token is invalid and the login fails, call this method. After updating the token, the SDK will automatically log back in, and the user does not need to call the login{@link #IRTS#login} method. <br>
     *        + Token expires, if you have successfully logged in, it will not be affected. An expired Token error will be notified to the user the next time you log in with an expired Token, or when you log in again due to a disconnection due to poor local network conditions.
     */
    virtual int updateLoginToken(const char* token) = 0;

    /** {zh}
     * @type api
     * @region 实时消息通信
     * @brief 设置应用服务器参数  <br>
     *        客户端调用 sendServerMessage{@link #IRTS#sendServerMessage} 或 sendServerBinaryMessage{@link #IRTS#sendServerBinaryMessage} 发送消息给业务服务器之前，必须设置有效签名和业务服务器地址。
     * @param [in] signature 动态签名，应用服务器可使用该签名验证消息来源。<br>
     *        签名需自行定义，可传入任意非空字符串，建议将 uid 等信息编码为签名。<br>
     *        设置的签名会以 post 形式发送至通过本方法中 url 参数设置的应用服务器地址。
     * @param [in] url 应用服务器的地址
     * @return  <br>
     *        + 0: 调用成功。
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @notes  <br>
     *       + 用户必须调用 login{@link #IRTS#login} 登录后，才能调用本接口。  <br>
     *       + 调用本接口后，SDK 会使用 onServerParamsSetResult{@link #IRTSEventHandler#onServerParamsSetResult} 返回相应结果。
     */
    /** {en}
     * @type api
     * @region Real-time messaging
     * @brief Set application server parameters   <br>
     *        Client side calls sendServerMessage{@link #IRTS#sendServerMessage} or sendServerBinaryMessage{@link #IRTS#sendServerBinaryMessage} Before sending a message to the business server, a valid signature and business server address must be set.
     * @param [in] signature Dynamic signature. The App server may use the signature to verify the source of messages.<br>
     *         You need to define the signature yourself. It can be any non-empty string. It is recommended to encode information such as UID into the signature.<br>
     *         The signature will be sent to the address set through the "url" parameter in the form of a POST request.
     * @param [in] url The address of the application server
     * @return  <br>
     *        + 0: Success.
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @notes   <br>
     *        + The user must call login{@link #IRTS#login} to log in before calling this interface. <br>
     *        + After calling this interface, the SDK will use onServerParamsSetResult{@link #IRTSEventHandler#onServerParamsSetResult} to return the corresponding result.
     */
    virtual int setServerParams(const char* signature, const char* url) = 0;

    /** {zh}
     * @type api
     * @region 实时消息通信
     * @brief 查询对端用户或本端用户的登录状态
     * @param [in] peer_user_id  <br>
     *        需要查询的用户 ID
     * @return  <br>
     *        + 0: 调用成功。
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @notes  <br>
     *       + 必须调用 login{@link #IRTS#login} 登录后，才能调用本接口。  <br>
     *       + 调用本接口后，SDK 会使用 onGetPeerOnlineStatus{@link #IRTSEventHandler#onGetPeerOnlineStatus} 回调通知查询结果。  <br>
     *       + 在发送房间外消息之前，用户可以通过本接口了解对端用户是否登录，从而决定是否发送消息。也可以通过本接口查询自己查看自己的登录状态。
     */
    /** {en}
     * @type api
     * @region Real-time messaging
     * @brief Query the login status of the opposite or local user
     * @param  [in] peer_user_id <br>
     *        User ID to be queried
     * @return  <br>
     *        + 0: Success.
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @notes   <br>
     *        + login{@link #IRTS#login} must be called before this interface can be called. <br>
     *        + After calling this interface, the SDK notifies the query result using the onGetPeerOnlineStatus{@link #IRTSEventHandler#onGetPeerOnlineStatus} callback. <br>
     *        + Before sending an out-of-room message, the user can know whether the peer user is logged in through this interface to decide whether to send a message. You can also check your login status through this interface.
     */
    virtual int getPeerOnlineStatus(const char* peer_user_id) = 0;

    /** {zh}
     * @type api
     * @region 实时消息通信
     * @brief 给房间外指定的用户发送文本消息（P2P）
     * @param [in] uid  <br>
     *        消息接收用户的 ID
     * @param [in] message  <br>
     *        发送的文本消息内容  <br>
     *        消息不超过 62KB。
     * @return  <br>
     *        + >0：发送成功，返回这次发送消息的编号，从 1 开始递增  <br>
     *        + -1：发送失败，RtcEngine 实例未创建  <br>
     *        + -2：发送失败，uid 为空
     * @notes  <br>
     *       + 在发送点对点文本消息，必须先调用 login{@link #IRTS#login} 完成登录。  <br>
     *       + 用户调用本接口发送文本信息后，会收到一次 onMessageSendResult{@link #IRTSEventHandler#onMessageSendResult} 回调，得知消息是否成功发送。  <br>
     *       + 若文本消息发送成功，则 uid 所指定的用户会通过 onMessageReceived{@link #IRTSEventHandler#onMessageReceived} 回调收到该消息。
     */
    /** {en}
     * @type api
     * @region Real-time messaging
     * @brief Send a text message (P2P) to a specified user outside the room
     * @param  [in] uid User ID of the message receiver
     * @param  [in] message <br>
     *        Text message content sent <br>
     *        Message does not exceed 62KB.
     * @return   <br>
     *         + > 0: Sent successfully, return the number of the sent message, increment from 1 <br>
     *         + -1: Sent failed, RtcEngine instance not created <br>
     *         + -2: Sent failed, uid is empty
     * @notes   <br>
     *        + You must call login{@link #IRTS#login} to complete the login before you can send a message in a foreign text of the room. <br>
     *        + After the user calls this interface to send a text message, he will receive an onMessageSendResult{@link #IRTSEventHandler#onMessageSendResult} callback to know whether the message was successfully sent. <br>
     *        + If the text message is sent successfully, the user specified by uid receives the message via the onMessageReceived{@link #IRTSEventHandler#onMessageReceived} callback.
     */
    virtual int64_t sendMessage(const char* uid, const char* message, MessageConfig config) = 0;
    /** {zh}
     * @type api
     * @region 实时消息通信
     * @brief 给房间外指定的用户发送二进制消息（P2P）
     * @param [in] uid  <br>
     *        消息接收用户的 ID
     * @param [in] length <br>
     *        二进制字符串的长度
     * @param [in] message  <br>
     *        发送的二进制消息内容  <br>
     *        消息不超过 46KB。
     * @return  <br>
     *        + >0：发送成功，返回这次发送消息的编号，从 1 开始递增  <br>
     *        + -1：发送失败，RtcEngine 实例未创建  <br>
     *        + -2：发送失败，uid 为空
     * @notes  <br>
     *       + 在发送点对点二进制消息前，必须先调用 login{@link #IRTS#login} 完成登录。  <br>
     *       + 用户调用本接口发送二进制消息后，会收到一次 onMessageSendResult{@link #IRTSEventHandler#onMessageSendResult} 回调，通知消息是否发送成功。  <br>
     *       + 若二进制消息发送成功，则 uid 所指定的用户会通过 onBinaryMessageReceived{@link #IRTSEventHandler#onBinaryMessageReceived} 回调收到该条消息。
     */
    /** {en}
     * @type api
     * @region Real-time messaging
     * @brief Send binary messages (P2P) to a specified user outside the room
     * @param  [in] uid <br>
     *        ID of the user receiving the message
     * @param  [in] length <br>
     *        Length of the binary string
     * @param  [in] message <br>
     *        Content of the binary message sent <br>
     *        Message does not exceed 46KB.
     * @return   <br>
     *         + > 0: sent successfully, return the number of the sent message, increment from 1 <br>
     *         + -1: Sent failed, RtcEngine instance not created <br>
     *         + -2: Sent failed, uid is empty
     * @notes   <br>
     *        + You must call this API after login by calling login{@link #IRTS#login}. <br>
     *        + After the user calls this interface to send a binary message, he will receive an onMessageSendResult{@link #IRTSEventHandler#onMessageSendResult} callback to notify whether the message was sent successfully. <br>
     *        + If the binary message is sent successfully, the user specified by uid will receive the message through the onBinaryMessageReceived{@link #IRTSEventHandler#onBinaryMessageReceived} callback.
     */
    virtual int64_t sendBinaryMessage(const char* uid, int length, const uint8_t* message, MessageConfig config) = 0;
    /** {zh}
     * @type api
     * @region 实时消息通信
     * @brief 客户端给应用服务器发送文本消息（P2Server）
     * @param [in] message  <br>
     *        发送的文本消息内容  <br>
     *        消息不超过 62KB。
     * @return  <br>
     *        + >0：发送成功，返回这次发送消息的编号，从 1 开始递增  <br>
     *        + -1：发送失败，RtcEngine 实例未创建
     * @notes  <br>
     *       + 在向业务服务器发送文本消息前，必须先调用 login{@link #IRTS#login} 完成登录，随后调用 setServerParams{@link #IRTS#setServerParams} 设置业务服务器。  <br>
     *       + 调用本接口后，会收到一次 onServerMessageSendResult{@link #IRTSEventHandler#onServerMessageSendResult} 回调，通知消息发送方是否发送成功。  <br>
     *       + 若文本消息发送成功，则之前调用 setServerParams{@link #IRTS#setServerParams} 设置的业务服务器会收到该条消息。
     */
    /** {en}
     * @type api
     * @region Real-time messaging
     * @brief The client side sends a text message to the application server (P2Server)
     * @param  [in] message <br>
     *        The content of the text message sent <br>
     *        The message does not exceed 62KB.
     * @return   <br>
     *         + > 0: Sent successfully, return the number of the sent message, increment from 1 <br>
     *         + -1: Sent failed, RtcEngine instance not created
     * @notes   <br>
     *        + Before sending a text message to the business server, you must first call login{@link #IRTS#login} to complete the login, and then call setServerParams{@link #IRTS#setServerParams} to set up the business server. <br>
     *        + After calling this interface, you will receive an onServerMessageSendResult{@link #IRTSEventHandler#onServerMessageSendResult} callback to inform the message sender whether the message was sent successfully. <br>
     *        + If the text message is sent successfully, the business server that previously called setServerParams{@link #IRTS#setServerParams} will receive the message.
     */
    virtual int64_t sendServerMessage(const char* message) = 0;
    /** {zh}
     * @type api
     * @region 实时消息通信
     * @brief 客户端给应用服务器发送二进制消息（P2Server）
     * @param [in] length <br>
     *        二进制字符串的长度
     * @param [in] message  <br>
     *        发送的二进制消息内容  <br>
     *        消息不超过 46KB。
     * @return  <br>
     *        + >0：发送成功，返回这次发送消息的编号，从 1 开始递增  <br>
     *        + -1：发送失败，RtcEngine 实例未创建
     * @notes  <br>
     *       + 在向业务服务器发送二进制消息前，必须先调用 login{@link #IRTS#login} 完成登录，随后调用 setServerParams{@link #IRTS#setServerParams} 设置业务服务器。  <br>
     *       + 调用本接口后，会收到一次 onServerMessageSendResult{@link #IRTSEventHandler#onServerMessageSendResult} 回调，通知消息发送方发送成功或失败。  <br>
     *       + 若二进制消息发送成功，则之前调用 setServerParams{@link #IRTS#setServerParams} 设置的业务服务器会收到该条消息。
     */
    /** {en}
     * @type api
     * @region Real-time messaging
     * @brief Client side sends binary messages to the application server (P2Server)
     * @param  [in] length <br>
     *        Length of binary string
     * @param  [in] message <br>
     *        Binary message content sent <br>
     *        Message does not exceed 46KB.
     * @return   <br>
     *         + > 0: Sent successfully, return the number of the sent message, increment from 1 <br>
     *         + -1: Sent failed, RtcEngine instance not created
     * @notes   <br>
     *        + Before sending a binary message to the business server, you must first call login{@link #IRTS#login} to complete the login, and then call setServerParams{@link #IRTS#setServerParams} Set up the business server. <br>
     *        + After calling this interface, you will receive an onServerMessageSendResult{@link #IRTSEventHandler#onServerMessageSendResult} callback to inform the message sender that the sending succeeded or failed. <br>
     *        + If the binary message is sent successfully, the business server that previously called setServerParams{@link #IRTS#setServerParams} will receive the message.
     */
    virtual int64_t sendServerBinaryMessage(int length, const uint8_t* message) = 0;

    /** {zh}
     * @type api
     * @region 房间管理
     * @brief 创建房间实例。
     *        调用此方法仅返回一个房间实例，你仍需调用 joinRoom{@link #IRTSRoom#joinRoom} 才能真正地创建/加入房间。
     *        多次调用此方法以创建多个 IRTSRoom{@link #IRTSRoom} 实例。分别调用各 IRTSRoom 实例中的 joinRoom{@link #IRTSRoom#joinRoom} 方法，同时加入多个房间。
     *        多房间模式下，用户可以同时订阅各房间的音视频流。
     * @param [in] room_id 标识通话房间的房间 ID。该字符串符合正则表达式：`[a-zA-Z0-9_@\-\.]{1,128}`。
     * @return 创建的 IRTSRoom{@link #IRTSRoom} 房间实例。
     * @notes <br>
     *        + 如果需要加入的房间已存在，你仍需先调用本方法来获取 IRTSRoom 实例，再调用 joinRoom{@link #IRTSRoom#joinRoom} 加入房间。
     *        + 多房间模式下，创建多个房间实例需要使用不同的 room_id，否则会导致创建房间失败。
     */
    /** {en}
     * @type api
     * @region Room Management
     * @brief Create a room instance.
     *        This API only returns a room instance. You still need to call joinRoom{@link #IRTSRoom#joinRoom} to actually create/join the room.
     *        Each call of this API creates one IRTSRoom{@link #IRTSRoom} instance. Call this API as many times as the number of rooms you need, and then call joinRoom{@link #IRTSRoom#joinRoom} of each IRTSRoom instance to join multiple rooms at the same time.
     *        In multi-room mode, a user can subscribe to media streams in the joined rooms at the same time.
     * @param [in] room_id The string matches the regular expression: `[a-zA-Z0-9_@\-\.]{1,128}`.
     * @return IRTSRoom{@link #IRTSRoom} instance.
     * @notes <br>
     *       + If the room that you wish to join already exists, you still need to call this API first to create the IRTSRoom instance, and then call joinRoom{@link #IRTSRoom#joinRoom}.
     *       + In multi-room mode, you need to use different room_id to create multiple rooms.
     */
    virtual IRTSRoom* createRoom(const char* room_id) = 0;

    /** {zh}
     * @type api
     * @region 引擎管理
     * @brief 设置运行时的参数
     * @param [in] json_string  json 序列化之后的字符串
     * @return  <br>
     *        + 0: 调用成功。
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @notes
     */
    /** {en}
     * @type api
     * @region Engine management
     * @brief Set runtime parameters
     * @param  [in] json_string String after json serialization
     * @return  <br>
     *        + 0: Success.
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @notes
     */
    virtual int setRuntimeParameters(const char * json_string) = 0;

    /** {zh}
     * @hidden(macOS, Windows, Linux)
     * @type api
     * @brief 启用蜂窝网络辅助增强，改善通话质量。
     * @param [in] enhance 是否开启。默认不开启。
     * @return 方法调用结果：  <br>
     *        + 0: 成功。<br>
     *        + -1：失败，内部错误。 <br>
     */
    /** {en}
     * @hidden(macOS, Windows, Linux)
     * @type api
     * @brief Enable cellular network assisted communication to improve call quality.
     * @param [in] enhance Enable or not. Off by default.
     * @return Method call result:   <br>
     *        + 0: Success. <br>
     *        + -1: Failure, internal error. <br>
     */
    virtual int setCellularEnhancement(bool enhance) = 0;

    /** {zh}
     * @type api
     * @region 代理
     * @brief 设置本地代理
     * @notes 要设置本地代理，调用 setLocalProxy{@link #IRTS#setLocalProxy}。
     */
    /** {en}
     * @type api
     * @region   proxy
     * @brief  set local proxy
     * @notes To set local proxy, call setLocalProxy{@link #IRTS#setLocalProxy}.
     */
    virtual int setLocalProxy(
        const LocalProxyConfiguration* configurations,
        int configuration_num) = 0;
};

/** {zh}
 * @type api
 * @region 引擎管理
 * @brief 创建 RTCEngine 实例。  <br>
 *        如果当前线程中未创建引擎实例，那么你必须先使用此方法，以使用 RTC 提供的各种音视频能力。  <br>
 *        如果当前线程中已创建了引擎实例，再次调用此方法时，会创建另一个独立的引擎实例。
 * @param [in] app_id 每个应用的唯一标识符。只有使用相同的 app_id 生成的实例，才能够进行音视频通信。
 * @param [in] event_handler SDK 回调给应用层的 Callback 对象，详见 IRTSEventHandler{@link #IRTSEventHandler} 。
 * @param [in] parameters 用以覆盖默认参数的本引擎实例参数。JSON 字符串格式。
 * @return  <br>
 *        + IRTS：创建成功。返回一个可用的 IRTS{@link #IRTS} 实例  <br>
 *        + Null：创建失败。
 * @notes  <br>
 *        + 如果你在同一个线程中创建了多个引擎实例，这些实例必须分别调用 destroyRTS{@link #destroyRTS} 销毁。
 *        + 在 Linux 平台上创建引擎实例的数量取决于系统的硬件性能。
 */
/** {en}
 * @type api
 * @region Engine Management
 * @brief Create an engine instance.   <br>
 *        This is the very first API that you must call if you want to use all the RTC capabilities.  <br>
 *        If there is no engine instance in current thread, calling this API will create one. If an engine instance has been created, calling this API again will create another instance.
 * @param [in] app_id A unique identifier for each App, randomly generated by the RTC console. Only instances created with the same app_id are able to communicate with each other.
 * @param [in] event_handler Handler sent from SDK to App. See IRTSEventHandler{@link #IRTSEventHandler}.
 * @param [in] parameters Reserved parameter, in JSON string.
 * @return  <br>
 *        + IRTS：A successfully created engine instance  <br>
 *        + Null：Creation failed
 * @notes   <br>
 *         + If you create multiple engine instances in the same thread, you must destroy each of these instances by calling destroyRTS{@link #destroyRTS}.
 *         + The number of engine instances created on a Linux platform depends on the hardware performance of the system.
 */
BYTERTC_API bytertc::IRTS* createRTS(const char* app_id,
        bytertc::IRTSEventHandler* event_handler, const char* parameters);

/** {zh}
 * @type api
 * @region 引擎管理
 * @brief 销毁由 createRTS{@link #createRTS} 创建的 RTCEngine 实例，并释放所有相关资源。
 * @param [in] engine createRTS{@link #createRTS} 时，返回的实例。
 * @notes  <br>
 *        + 请确保和需要销毁的 IRTS{@link #IRTS} 实例相关的业务场景全部结束后，才调用此方法。  <br>
 *        + 该方法在调用之后，会销毁所有和此 IRTS{@link #IRTS} 实例相关的内存，并且停止与媒体服务器的任何交互。  <br>
 *        + 调用本方法会启动 SDK 退出逻辑。引擎线程会保留，直到退出逻辑完成。因此，不要在回调线程中直接调用此 API，会导致死锁。同时此方法是耗时操作，不建议在主线程调用本方法，避免主线程阻塞。
 */
/** {en}
 * @type api
 * @region Engine Management
 * @brief Destroy the engine instance created by createRTS{@link #createRTS}, and release all related resources.
 * @param [in] engine The engine instance created by createRTS{@link #createRTS}.
 * @notes  <br>
 *         + Call this API after all business scenarios related to the engine instance are destroyed.  <br>
 *         + When the API is called, RTC SDK destroys all memory associated with the engine instance and stops any interaction with the media server.  <br>
 *         + Calling this API will start the SDK exit logic. The engine thread is held until the exit logic is complete. The engine thread is retained until the exit logic is complete. Therefore, do not call this API directly in the callback thread, or it will cause a deadlock. This function takes a long time to execute, so it's not recommended to call this API in the main thread, or the main thread may be blocked.
 */
BYTERTC_API void destroyRTS();

/** {zh}
 * @type api
 * @region 错误码
 * @brief 获取错误码的描述
 * @param [in] code 需要获取描述的错误码
 * @return 错误码的描述
 * @notes  该接口是通用功能，调用时不需要依赖引擎对象。
 */
/** {en}
 * @type api
 * @region  error code
 * @brief  Get the description of the error code
 * @param  [in] code Needs to get the description of the error code
 * @return  The description of the error code
 * @notes  This interface is a general function and does not need to rely on the engine object when calling.
 */
BYTERTC_API const char* getErrorDescription(int code);

/** {zh}
 * @type api
 * @region 引擎管理
 * @brief 获取当前 SDK 版本信息。
 * @return 当前 SDK 版本信息。
 */
/** {en}
 * @type api
 * @region  engine management
 * @brief  Get the current SDK version information.
 * @return Current SDK version information.
 */
BYTERTC_API const char* getSDKVersion();

/** {zh}
 * @type api
 * @region 引擎管理
 * @brief 配置 SDK 本地日志参数，包括日志级别、存储路径、日志文件最大占用的总空间、日志文件名前缀。
 * @param [in] log_config 本地日志参数，参看 LogConfig{@link #LogConfig}。
 * @return <br>
 *        + 0：成功。
 *        + –1：失败，本方法必须在创建引擎前调用。
 *        + –2：失败，参数填写错误。
 * @notes 本方法必须在调用 createRTS{@link #createRTS} 之前调用。
 */
/** {en}
 * @type api
 * @region Engine Management
 * @brief Configures the local log parameters of RTC SDK, including the logging level, directory, and the limits for total log file size.
 * @param [in] log_config Local log parameters. See LogConfig{@link #LogConfig}.
 * @return <br>
 *        + 0: Success.
 *        + –1: Failure. This API must be called before creating engine.
 *        + –2: Failure. Invalid parameters.
 * @notes This API must be called before createRTS{@link #createRTS}.
 */
BYTERTC_API int setLogConfig(const LogConfig& log_config);

}    // namespace bytertc

