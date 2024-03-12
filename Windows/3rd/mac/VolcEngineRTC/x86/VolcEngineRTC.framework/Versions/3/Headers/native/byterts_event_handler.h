/*
 * Copyright (c) 2020 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC Event Handler Lite
*/

#pragma once

#include "rtc/bytertc_rts_defines.h"

namespace bytertc {
/** {zh}
 * @type callback
 * @brief 实时信令事件回调接口
 */
/** {en}
 * @type callback
 * @brief Audio & video engine event callback interface
 */
class IRTSEventHandler {
public:

    /**
     * @hidden constructor/destructor
     */
    virtual ~IRTSEventHandler() {
    }

    /** {zh}
     * @type callback
     * @region 警告码
     * @brief 当内部发生警告事件时触发该回调
     * @param [in] warn
     *        警告标识码，详见:WarningCode{@link #WarningCode}
     */
    /** {en}
     * @type callback
     * @region Warning code
     * @brief This callback informs you of a warning message.
     * @param  [in] warn
     *        Warning identification code, see: WarningCode{@link #WarningCode}
     */
    virtual void onWarning(int warn) {
        (void)warn;
    }

    /** {zh}
     * @type callback
     * @region 错误码
     * @brief 当 SDK 内部发生不可逆转错误时触发该回调。
     * @param [in] err 错误标识码，参看 ErrorCode{@link #ErrorCode}
     */
    /** {en}
     * @type callback
     * @region Error code
     * @brief This callback informs you of an error message.
     * @param  [in] err Error code. See ErrorCode{@link #ErrorCode}
     */
    virtual void onError(int err) {
        (void)err;
    }

    /** {zh}
    * @valid since 3.52
    * @type callback
    * @brief 当访问插件失败时，收到此回调。
    *        RTC SDK 将一些功能封装成插件。当使用这些功能时，如果插件不存在，功能将无法使用。
    * @param [in] extension_name 插件名字
    * @param [in] msg 失败说明
    */
    /**
    * {en}
    * @valid since 3.52
    * @type callback
    * @brief Failed to access the extension.
    *        RTC SDK provides some features with extensions. Without implementing the extension, you cannot use the corresponding feature.
    * @param [in] extension_name The name of extension.
    * @param [in] msg Error message.
    */
     void onExtensionAccessError(const char* extension_name, const char* msg) {
        (void)extension_name;
        (void)msg;
     }

    /** {zh}
     * @type callback
     * @region 引擎管理
     * @brief 端监控日志回调。当产生一个端监控事件时触发该回调。
     * @param [in] log_type  <br>
     *        事件类型。目前类型固定为 "live_webrtc_monitor_log"。
     * @param [in] log_content  <br>
     *        端监控日志内容。
     */
    /** {en}
     * @type callback
     * @region  engine management
     * @brief  Terminal monitoring log callback. The callback is triggered when a terminal monitoring event is generated.
     * @param  [in] log_type <br>
     *         Event type. The current type is fixed to "live_webrtc_monitor_log".
     * @param  [in] log_content <br>
     *         Terminal monitoring log content.
     */
    virtual void onLogReport(const char* log_type, const char* log_content) {
        (void)log_type;
        (void)log_content;
    }

    /** {zh}
     * @type callback
     * @region 引擎管理
     * @brief SDK 与信令服务器连接状态改变回调。连接状态改变时触发。
     * @param [in] state 当前 SDK 与信令服务器的连接状态，详见 ConnectionState{@link #ConnectionState}。
     * @notes 更多信息参见 [连接状态提示](https://www.volcengine.com/docs/6348/95376)。
     */
    /** {en}
     * @type callback
     * @region  engine management
     * @brief SDK  connection state change callback with signaling server. Triggered when the connection state changes.
     * @param  [in] state The current connection status between the SDK and the signaling server. See ConnectionState{@link #ConnectionState}.
     * @notes Refer to [Getting Connection Status](https://docs.byteplus.com/byteplus-rtc/docs/95376) for more details.
     */
    virtual void onConnectionStateChanged(bytertc::ConnectionState state) {
    }

    /** {zh}
     * @type callback
     * @region 引擎管理
     * @brief SDK 当前网络连接类型改变回调。当 SDK 的当前网络连接类型发生改变时回调该事件。
     * @param [in] type  <br>
     *        SDK 当前的网络连接类型，详见：NetworkType{@link #NetworkType} 。
     */
    /** {en}
     * @type callback
     * @region Engine management
     * @brief SDK Current network connection type change callback. Callbacks the event when the current network connection type of the SDK changes.
     * @param  [in] type <br>
     *        SDK The current network connection type, see: NetworkType{@link #NetworkType}.
     */
    virtual void onNetworkTypeChanged(bytertc::NetworkType type) {
    }

    /** {zh}
     * @type callback
     * @region 引擎管理
     * @brief 周期性（2s）地发出回调，报告当前cpu与memory使用率
     * @param [in] stats 返回包含当前系统状态信息的结构体，详见 SysStats{@link #SysStats}
     */
    /** {en}
     * @type callback
     * @region  engine management
     * @brief  Periodically (2s) issue callbacks to report the current cpu and memory usage
     * @param  [in] stats Return the current system state information. See SysStats{@link #SysStats}
     */
    virtual void onSysStats(const bytertc::SysStats& stats) {
    }

    /** {zh}
     * @type callback
     * @region 引擎管理
     * @brief 创建房间失败回调。
     * @param room_id 房间 ID。
     * @param error_code 创建房间错误码，具体原因参看 ErrorCode{@link #ErrorCode}。
     */
    /** {en}
     * @type callback
     * @region Engine Management
     * @brief Callback on create room failure.
     * @param room_id  Room ID.
     * @param error_code Create room error code. See ErrorCode{@link #ErrorCode} for specific indications.
     */
    virtual void onCreateRoomStateChanged(const char* room_id, int error_code) {
        (void)room_id;
        (void)error_code;
    }

    /** {zh}
     * @type callback
     * @deprecated 在3.52及之后废弃，将在3.57删除，使用 onLocalProxyStateChanged{@link #IRTSEventHandler#onLocalProxyStateChanged} 替换
     * @region 代理回调
     * @brief HTTP 代理连接状态改变时，收到该回调。
     * @param [in] state 当前 HTTP 代理连接状态，详见 HttpProxyState{@link #HttpProxyState}
     */
    /** {en}
     * @type callback
     * @deprecated since 3.52, will be deleted at 3.57, use onLocalProxyStateChanged{@link #IRTSEventHandler#onLocalProxyStateChanged} instead
     * @region Proxy callback
     * @brief HTTP Receive the callback when the proxy connection state changes.
     * @param  [in] state The current HTTP proxy connection status. See HttpProxyState{@link #HttpProxyState}
     */
        virtual void onHttpProxyState(int state) {
    }

    /** {zh}
     * @type callback
     * @deprecated 在3.52及之后废弃，将在3.57删除，使用 onLocalProxyStateChanged{@link #IRTSEventHandler#onLocalProxyStateChanged} 替换
     * @region 代理回调
     * @brief HTTPS 代理连接状态改变时，收到该回调。
     * @param  [out] state 当前 HTTPS 代理连接状态，详见 HttpProxyState{@link #HttpProxyState}
     */
    /** {en}
     * @type callback
     * @deprecated since 3.52, will be deleted at 3.57, use onLocalProxyStateChanged{@link #IRTSEventHandler#onLocalProxyStateChanged} instead
     * @region Proxy callback
     * @brief HTTPS Receive the callback when the proxy connection state changes.
     * @param   [out] State the current HTTPS proxy connection status. See HttpProxyState{@link #HttpProxyState}
     */
    virtual void onHttpsProxyState(int state) {
    }

    /** {zh}
     * @type callback
     * @deprecated 在3.52及之后废弃，将在3.57删除，使用 onLocalProxyStateChanged{@link #IRTSEventHandler#onLocalProxyStateChanged} 替换
     * @region 代理回调
     * @brief Socks5 代理状态改变时，收到该回调。
     * @param [out] state SOCKS5 代理连接状态，详见 Socks5ProxyState{@link #Socks5ProxyState}
     * @param [out] cmd 代理连接的每一步操作命令
     * @param [out] proxy_address 代理地址信息
     * @param [out] local_address 当前连接使用的本地地址
     * @param [out] remote_address 远端的连接地址
     */
    /** {en}
     * @type callback
     * @deprecated since 3.52, will be deleted at 3.57, use onLocalProxyStateChanged{@link #IRTSEventHandler#onLocalProxyStateChanged} instead
     * @region Proxy callback
     * @brief Socks5 Receive the callback when the proxy state changes.
     * @param  [out] State SOCKS5 proxy connection status. See Socks5ProxyState{@link #Socks5ProxyState}
     * @param  [out] Cmd every step of the proxy connection operating command
     * @param  [out] Proxy_address proxy address information
     * @param  [out] Local_address the local address used by the current connection
     * @param  [out] Remote_address the remote connection address
     */
    virtual void onSocks5ProxyState(int state,
        const char* cmd,
        const char* proxy_address,
        const char* local_address,
        const char* remote_address) {
    }

    /** {zh}
     * @type callback
     * @region 实时消息通信
     * @brief 登录结果回调
     * @param [in] uid  <br>
     *        登录用户 ID
     * @param [in] error_code  <br>
     *        登录结果  <br>
     *        详见 LoginErrorCode{@link #LoginErrorCode}。
     * @param [in] elapsed  <br>
     *        从调用 login{@link #IRTS#login} 接口开始到返回结果所用时长  <br>
     *        单位为 ms。
     * @notes 调用 login{@link #IRTS#login} 后，会收到此回调。
     */
    /** {en}
     * @type callback
     * @region Real-time messaging
     * @brief login result callback
     * @param  [in] uid <br>
     *        Login user ID
     * @param  [in] error_code <br>
     *        Login result <br>
     *        See LoginErrorCode{@link #LoginErrorCode}.
     * @param  [in] elapsed <br>
     *         The time taken from the call to the login{@link #IRTS#login} interface to return the result is <br>
     *         In ms. This callback is received after
     * @notes login{@link #IRTS#login} is called. login{@link #IRTS#login}
     */
    virtual void onLoginResult(const char* uid, int error_code, int elapsed) {
        (void)uid;
        (void)error_code;
        (void)elapsed;
    }
    /** {zh}
     * @type callback
     * @region 实时消息通信
     * @brief 登出结果回调
     * @param reason 用户登出的原因，参看 LogoutReason{@link #LogoutReason}
     * @notes 在以下两种情况下会收到此回调：调用 logout{@link #IRTS#logout} 接口主动退出；或其他用户以相同 UserId 进行 `login` 导致本地用户被动登出。
     */
    /** {en}
     * @type callback
     * @region Real-time messaging
     * @brief Callback of logout result
     * @param reason It describes the reason why users log out. See LogoutReason{@link #LogoutReason}
     * @notes You will receive this callback when calling logout{@link #IRTS#logout} or when the local user is kicked out because another user logs in with the same UserId.
     */
    virtual void onLogout(LogoutReason reason) {
    }
    /** {zh}
     * @type callback
     * @region 实时消息通信
     * @brief 设置应用服务器参数的返回结果
     * @param [in] error <br>
     *        设置结果  <br>
     *        + 返回 200，设置成功  <br>
     *        + 返回其他，设置失败
     * @notes 调用 setServerParams{@link #IRTS#setServerParams} 后，会收到此回调。
     */
    /** {en}
     * @type callback
     * @region Real-time messaging
     * @brief Set the return result of the application server parameter
     * @param  [in] error <br>
     *         + 200, set successfully <br>
     *         + Return other, set failed
     * @notes Receive this callback after calling setServerParams{@link #IRTS#setServerParams}.
     */
    virtual void onServerParamsSetResult(int error) {
        (void)error;
    }
    /** {zh}
     * @type callback
     * @region 实时消息通信
     * @brief 查询对端或本端用户登录状态的返回结果
     * @param [in] peer_user_id  <br>
     *        需要查询的用户 ID
     * @param [in] status  <br>
     *        查询的用户登录状态  <br>
     *        详见 UserOnlineStatus{@link #UserOnlineStatus}.
     * @notes 必须先调用 getPeerOnlineStatus{@link #IRTS#getPeerOnlineStatus}，才能收到此回调。
     */
    /** {en}
     * @type callback
     * @region Real-time messaging
     * @brief The return result of querying the login status of the peer or local user
     * @param  [in] peer_user_id User ID
     * @param  [in] status <br>
     *        The user login status of the query <br>
     *        See UserOnlineStatus{@link #UserOnlineStatus}.
     * @notes You must first call getPeerOnlineStatus{@link #IRTS#getPeerOnlineStatus} to receive this callback.
     */
    virtual void onGetPeerOnlineStatus(const char* peer_user_id, int status) {
        (void)peer_user_id;
        (void)status;
    }
    /** {zh}
     * @type callback
     * @region 实时消息通信
     * @brief 收到房间外用户调用 sendMessage{@link #IRTS#sendMessage} 发来的文本消息时，会收到此回调
     * @param [in] uid  <br>
     *        消息发送者 ID
     * @param [in] message  <br>
     *        收到的文本消息内容
     */
    /** {en}
     * @type callback
     * @region Real-time messaging
     * @brief Receive this callback when you receive a text message from an out-of-room user calling sendMessage{@link #IRTS#sendMessage}
     * @param  [in] uid <br>
     *        User ID of the message sender
     * @param  [in] message <br>
     *        Received text message content
     */
    virtual void onMessageReceived(const char* uid, const char* message) {
        (void)uid;
        (void)message;
    }
    /** {zh}
     * @type callback
     * @region 实时消息通信
     * @brief 收到房间外用户调用 sendBinaryMessage{@link #IRTS#sendBinaryMessage} 发来的二进制消息时，会收到此回调
     * @param [in] uid  <br>
     *        消息发送者 ID
     * @param [in] size  <br>
     *        二进制消息长度
     * @param [in] message  <br>
     *        收到的二进制消息内容
     */
    /** {en}
     * @type callback
     * @region Real-time messaging
     * @brief Receive this callback when you receive a binary message from an out-of-room user calling sendBinaryMessage{@link #IRTS#sendBinaryMessage}
     * @param  [in] uid <br>
     *        User ID of the message sender
     * @param  [in] size <br>
     *        Binary message length
     * @param  [in] message <br>
     *         Binary message content received
     */
    virtual void onBinaryMessageReceived(const char* uid, int size, const uint8_t* message) {
        (void)uid;
        (void)size;
        (void)message;
    }
    /** {zh}
     * @type callback
     * @region 实时消息通信
     * @brief 给房间外指定的用户发送消息的回调
     * @param [in] msgid  <br>
     *        本条消息的 ID  <br>
     *        所有的 P2P 和 P2Server 消息共用一个 ID 序列。
     * @param [in] error  <br>
     *        消息发送结果  <br>
     *        详见 UserMessageSendResult{@link #UserMessageSendResult}。
     * @notes 当调用 sendMessage{@link #IRTS#sendMessage} 或 sendBinaryMessage{@link #IRTS#sendBinaryMessage} 发送消息后，会收到此回调。
     */
    /** {en}
     * @type callback
     * @region Real-time messaging
     * @brief A callback that sends a message to a specified user outside the room
     * @param  [in] msgid <br>
     *        The ID of this message <br>
     *        All P2P and P2Server messages share a single ID sequence.
     * @param  [in] error <br>
     *         Message sending result <br>
     *         See UserMessageSendResult{@link #UserMessageSendResult}.
     * @notes Receive this callback when a message is sent by calling sendMessage{@link #IRTS#sendMessage} or sendBinaryMessage{@link #IRTS#sendBinaryMessage}.
     */
    virtual void onMessageSendResult(int64_t msgid, int error) {
        (void)msgid;
        (void)error;
    }

    /** {zh}
     * @type callback
     * @region 实时消息通信
     * @brief 给应用服务器发送消息的回调
     * @param [in] msgid 本条消息的 ID  <br>
     *        所有的 P2P 和 P2Server 消息共用一个 ID 序列。
     * @param [in] error 消息发送结果，详见 UserMessageSendResult{@link #UserMessageSendResult}。
     * @param [in] message 应用服务器收到 HTTP 请求后，在 ACK 中返回的信息。
     * @notes 当调用 sendServerMessage{@link #IRTS#sendServerMessage} 或 sendServerBinaryMessage{@link #IRTS#sendServerBinaryMessage} 发送消息后，会收到此回调。
     */
    /** {en}
     * @type callback
     * @region Real-time messaging
     * @brief Callback to send a message to the application server
     * @param [in] msgid The ID of this message <br>
     *        All P2P and P2Server messages share a single ID sequence.
     * @param [in] error Message Sending Results. See UserMessageSendResult{@link #UserMessageSendResult}.
     * @param message The message returned in ACK when the application server receives HTTP request.
     * @notes Receive this callback when you call sendServerMessage{@link #IRTS#sendServerMessage} or sendServerBinaryMessage{@link #IRTS#sendServerBinaryMessage} to send a message to your application server.
     */
    virtual void onServerMessageSendResult(int64_t msgid, int error, const bytertc::ServerACKMsg& msg) {
        (void)msgid;
        (void)error;
        (void)msg;
    }

    /** {zh}
     * @type callback
     * @brief 调用 StartCloudProxy{@link #IRtcEngineLite#StartCloudProxy} 开启云代理，SDK 首次成功连接云代理服务器时，回调此事件。
     * @param [in] interval 从开启云代理到连接成功经过的时间，单位为 ms
     */
    /** {en}
     * @type callback
     * @brief Receives the callback when you call StartCloudProxy{@link #IRtcEngineLite#StartCloudProxy} to start cloud proxy, and the SDK connects the proxy server successfully.
     * @param [in] interval The interval in ms between starting cloud proxy and connects the cloud proxy server successfully.
     */
    virtual void onCloudProxyConnected(int interval) {
        (void)interval;
    }

    /** {zh}
     * @type callback
     * @brief 调用 setLocalProxy{@link #IRTS#setLocalProxy} 设置本地代理，SDK对代理连接的状态
     * 回调此接口。
     * @param [in] local_proxy_type 本地代理类型：sock5 或 httptunnel
     * @param [in] local_proxy_state 本地代理状态。参看 LocalProxyState{@link #LocalProxyState}。  <br>
     * @param [in] local_proxy_error 本地代理错误。参看 LocalProxyError{@link #LocalProxyError}。  <br>
     */
    /** {en}
     * @type callback
     * @brief Receives the callback when you call setLocalProxy{@link #IRTS#setLocalProxy} to set proxy, and the SDK connects the proxy server and call with state
     * @param [in] local_proxy_type local proxy type: socks5 or httptunnel
     * @param [in] local_proxy_state The states of local proxy connection. Refer to LocalProxyState{@link #LocalProxyState} for details.  <br>
     * @param [in] local_proxy_error The errors of local proxy connection. Refer to LocalProxyError{@link #LocalProxyError} for details.
     */
    virtual void onLocalProxyStateChanged(LocalProxyType local_proxy_type, LocalProxyState local_proxy_state, LocalProxyError local_proxy_error) {
        (void)local_proxy_type;
        (void)local_proxy_state;
        (void)local_proxy_error;
    }
};

} // namespace bytertc

