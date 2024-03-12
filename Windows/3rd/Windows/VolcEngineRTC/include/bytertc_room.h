/*
 * Copyright (c) 2020 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC Room Interface
 */

#pragma once

#include "rtc/bytertc_video_effect_interface.h"  // NOLINT
#include "rtc/bytertc_defines.h"
#include "bytertc_room_event_handler.h"
#include "rtc/bytertc_transcoder_interface.h"
#include "rtc/bytertc_publicstream_interface.h"
#include "rtc/bytertc_range_audio_interface.h"
#include "rtc/bytertc_spatial_audio_interface.h"
#include "rtc/bytertc_panoramic_video_interface.h"
namespace bytertc {

/**
 * @locale zh
 * @type api
 * @brief 房间接口
 */
/**
 * @locale en
 * @type api
 * @brief  Room interface
 */
class IRTCRoom {
public:
    /**
     * @locale zh
     * @hidden constructor/destructor
     * @brief 析构函数
     */
    /**
     * @locale en
     * @hidden constructor/destructor
     * @brief Destructor
     */
    virtual ~IRTCRoom() {
    }

    /**
     * @locale zh
     * @type api
     * @region 多房间
     * @brief 退出并销毁调用 createRTCRoom{@link #IRTCVideo#createRTCRoom} 所创建的房间实例。
     */
    /**
     * @locale en
     * @type api
     * @region  multi-room
     * @brief  Leave and destroy the room instance created by calling createRTCRoom{@link #IRTCVideo#createRTCRoom}.
     */
    virtual void destroy() = 0;

    /**
     * @locale zh
     * @type api
     * @region 多房间
     * @brief 设置用户可见性。未调用该接口前，本地用户默认对他人可见。<br>
     *        默认情况下，一个 RTC 房间最多同时容纳 50 名可见用户，最多 30 人可同时上麦。更多信息参看[用户和媒体流上限](https://www.volcengine.com/docs/6348/257549)。
     * @param enable 设置用户是否对房间内其他用户可见：  <br>
     *        + true: 可见，用户可以在房间内发布音视频流，房间中的其他用户将收到用户的行为通知，例如进房、开启视频采集和退房。<br>
     *        + false: 不可见，用户不可以在房间内发布音视频流，房间中的其他用户不会收到用户的行为通知，例如进房、开启视频采集和退房。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0: 调用失败。参看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明。
     * @note  
     *       + 在加入房间前后，用户均可调用此方法设置用户可见性。<br>
     *       + 设置用户可见性，会收到设置成功/失败回调 onUserVisibilityChanged{@link #IRTCRoomEventHandler#onUserVisibilityChanged}。（v3.54 新增）<br>
     *   &#x0020;  • 在加入房间前设置用户可见性，若设置的可见性与默认值不同，将在加入房间时触发本回调。<br>
     *   &#x0020;  • 在加入房间后设置用户可见性，若可见性前后不同，会触发本回调。<br>
     *   &#x0020;  • 在断网重连后，若可见性发生改变，会触发本回调。<br>
     *       + 在房间内，调用此方法成功切换用户可见性后，房间内其他用户会收到相应的回调。<br>
     *   &#x0020;  • 从可见换至不可见时，房间内其他用户会收到 onUserLeave{@link #IRTCRoomEventHandler#onUserLeave}。<br>
     *   &#x0020;  • 从不可见切换至可见时，房间内其他用户会收到 onUserJoined{@link #IRTCRoomEventHandler#onUserJoined}。<br>
     *   &#x0020;  • 若调用该方法将可见性设为 `false`，此时尝试发布流会收到 `kWarningCodePublishStreamForbiden` 警告。
     */
    /**
     * @locale en
     * @type api
     * @region Room management
     * @brief Set the visibility of the user in the room. The local user is visible to others by default before calling this API.<br>
     *        An RTC room can accommodate a maximum of 50 visible users, and 30 media streams can be published simultaneously. For more information, see [Room Capacity](https://docs.byteplus.com/en/byteplus-rtc/docs/257549).
     * @param enable Visibility of the user in the room. <br>
     *        + true: The user can publish media streams. The other users in the room get informed of the behaviors of the user, such as joining room, starting video capture, and leaving room.<br>
     *        + false: The user cannot publish media streams. The other users in the room do not get informed of the behaviors of the user, such as joining room, starting video capture, or leaving room.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Failure. See ReturnStatus{@link #ReturnStatus}.
     * @note   
     *        + You can call this API whether the user is in a room or not.<br>
     *        + You will receive onUserVisibilityChanged{@link #IRTCRoomEventHandler#onUserVisibilityChanged} after calling this API. (Available since v3.54)<br>
     *   &#x0020;  • If you call this API before joining room, and the set value is different from the default value, you will receive the callback when you join the room.<br>
     *   &#x0020;  • If you call this API after joining room, and the current visibility is different from the previous value, you will receive the callback.<br>
     *   &#x0020;  • When reconnecting after losing internet connection, if the visibility changes, you will receive the callback. <br>
     *        + When you call this API while you are in the room, the other users in the room will be informed via the following callback.<br>
     *   &#x0020;  • When you switch from `false` to `true`, they will receive onUserJoined{@link #IRTCRoomEventHandler#onUserJoined}.<br>
     *   &#x0020;  • When you switch from `true` to `false`, they will receive onUserLeave{@link #IRTCRoomEventHandler#onUserLeave}.<br>
     *   &#x0020;  • The invisible user will receive the warning code, `kWarningCodePublishStreamForbiden`, when trying to publish media streams.
     */
    virtual int setUserVisibility(bool enable) = 0;

    /**
     * @locale zh
     * @type api
     * @region 多房间
     * @brief 通过设置 IRTCRoom{@link #IRTCRoom} 对象的事件句柄，监听此对象对应的回调事件。
     * @param room_event_handler 参见 IRTCRoomEventHandler{@link #IRTCRoomEventHandler}
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     */
    /**
     * @locale en
     * @type api
     * @region multiroom
     * @brief Listens for event callbacks related to the IRTCRoom{@link #IRTCRoom} instance by setting the event handler of this instance.
     * @param room_event_handler Refer to IRTCRoomEventHandler{@link #IRTCRoomEventHandler}.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     */
    virtual int setRTCRoomEventHandler(IRTCRoomEventHandler* room_event_handler) = 0;

    /**
     * @locale zh
     * @type api
     * @region 多房间
     * @brief 加入房间。<br>
     *        调用 createRTCRoom{@link #IRTCVideo#createRTCRoom} 创建房间后，调用此方法加入房间，同房间内其他用户进行音视频通话。  
     * @param token 动态密钥，用于对登录用户进行鉴权验证。  <br>
     *        进入房间需要携带 Token。测试时可使用控制台生成临时 Token，正式上线需要使用密钥 SDK 在您的服务端生成并下发 Token。Token 有效期及生成方式参看[使用 Token 完成鉴权](70121)。  <br>
     *       + 使用不同 App ID 的 App 是不能互通的。  <br>
     *       + 请务必保证生成 Token 使用的 App ID 和创建引擎时使用的 App ID 相同，否则会导致加入房间失败。
     * @param user_info 用户信息，参看 UserInfo{@link #UserInfo}。  
     * @param config 房间参数配置，设置房间模式以及是否自动发布或订阅流。具体配置模式参看 RTCRoomConfig{@link #RTCRoomConfig}。  
     * @return  
     *        +  0: 成功  <br>
     *        + -1：room_id / user_info.uid 包含了无效的参数。  <br>
     *        + -2：已经在房间内。接口调用成功后，只要收到返回值为 0 ，且未调用 leaveRoom:{@link #IRTCRoom#leaveRoom} 成功，则再次调用进房接口时，无论填写的房间 ID 和用户 ID 是否重复，均触发此返回值。  <br>
     *        调用失败时，具体失败原因会通过 onRoomStateChanged{@link #IRTCRoomEventHandler#onRoomStateChanged} 回调告知。  
     * @note  
     *       + 同一个 App ID 的同一个房间内，每个用户的用户 ID 必须是唯一的。如果两个用户的用户 ID 相同，则后进房的用户会将先进房的用户踢出房间，并且先进房的用户会收到 onRoomStateChanged{@link #IRTCRoomEventHandler#onRoomStateChanged} 回调通知，错误类型详见 ErrorCode{@link #ErrorCode} 中的 kErrorCodeDuplicateLogin。  <br>
     *       + 本地用户调用此方法加入房间成功后，会收到 onRoomStateChanged{@link #IRTCRoomEventHandler#onRoomStateChanged} 回调通知。若本地用户同时为可见用户，加入房间时远端用户会收到 onUserJoined{@link #IRTCRoomEventHandler#onUserJoined} 回调通知。<br>
     *       + 房间内不可见用户的容量远远大于可见用户，而且用户默认可见，因此对于不参与互动的用户，你需要在其进房后调用 setUserVisibility{@link #IRTCRoom#setUserVisibility 更改为不可见用户。从而避免因房间内用户达到数量上限所导致的进房失败。默认情况下，一个 RTC 房间最多同时容纳 50 名可见用户，其中最多 30 人可同时上麦，更多信息参看[用户和媒体流上限](https://www.volcengine.com/docs/6348/257549)。<br>
     *       + 用户加入房间成功后，在本地网络状况不佳的情况下，SDK 可能会与服务器失去连接，并触发 onConnectionStateChanged{@link #IRTCVideoEventHandler#onConnectionStateChanged} 回调。此时 SDK 会自动重试，直到成功重连。重连成功后，本地会收到 onRoomStateChanged{@link #IRTCRoomEventHandler#onRoomStateChanged} 回调通知。
     */
    /**
     * @locale en
     * @type api
     * @region Multi-room
     * @brief Join the room. <br>
     *        After creating a room by calling createRTCRoom{@link #IRTCVideo#createRTCRoom}, call this API to join the room and make audio & video calls with other users in the room. 
     * @param token Dynamic key for authenticating the logged-in user. <br>
     *         You need to bring Token to enter the room. When testing, you can use the console to generate temporary tokens. The official launch requires the use of the key SDK to generate and issue tokens at your server level. See [Authentication with Token](70121) for token validity and generation method. <br>
     *        + Apps with different App IDs cannot communicate with each other. <br>
     *        + Make sure that the App ID used to generate the Token is the same as the App ID used to create the engine, otherwise it will cause the join room to fail.
     * @param user_info User information. See UserInfo{@link #UserInfo}. 
     * @param config Room parameter configuration, set the room mode and whether to automatically publish or subscribe to the flow. See RTCRoomConfig{@link #RTCRoomConfig} for the specific configuration mode. 
     * @return   
     *         + 0: Success <br>
     *         + -1: Room_id/user_info.uid contains invalid parameters. <br>
     *         + -2: Already in the room. After the interface call is successful, as long as the return value of 0 is received and leaveRoom:{@link #IRTCRoom#leaveRoom} is not called successfully, this return value is triggered when the room entry interface is called again, regardless of whether the filled room ID and user ID are duplicated. <br>
     *         The reason for the failure will be communicated via the onRoomStateChanged{@link #IRTCRoomEventHandler#onRoomStateChanged} callback.
     * @note   
     *        + In the same room with the same App ID, the user ID of each user must be unique. If two users have the same user ID, the user who entered the room later will kick the user who entered the room out of the room, and the user who entered the room will receive the onRoomStateChanged{@link #IRTCRoomEventHandler#onRoomStateChanged} callback notification. For the error type. See kErrorCodeDuplicateLogin in ErrorCode{@link #ErrorCode}. <br>
     *        + Local users will receive onRoomStateChanged{@link #IRTCRoomEventHandler#onRoomStateChanged} callback notification after calling this method to join the room successfully. If the local user is also a visible user, the remote user will receive an onUserJoined{@link #IRTCRoomEventHandler#onUserJoined} callback notification when joining the room.<br>
     *        + By default, the user is visible in an RTC room. Joining fails when the number of users in an RTC room reaches the upper limit. To avoid this, call setUserVisibility{@link #IRTCRoom#setUserVisibility} to change the visibility of the audience users to `false` by considering the capacity for the invisible users is much larger than that for visible users. An RTC room can accommodate a maximum of 50 visible users, and 30 media streams can be published simultaneously. For more information, see [Capability of Users and Streams](https://docs.byteplus.com/en/byteplus-rtc/docs/257549). <br>
     *        + After the user successfully joins the room, the SDK may lose connection to the server in case of poor local network conditions. At this point, onConnectionStateChanged{@link #IRTCVideoEventHandler#onConnectionStateChanged} callback will be triggered and the SDK will automatically retry until it successfully reconnects to the server. After a successful reconnection, you will receive a local onRoomStateChanged{@link #IRTCRoomEventHandler#onRoomStateChanged} callback notification.
     */
    virtual int joinRoom(const char* token, const UserInfo& user_info, const RTCRoomConfig& config) = 0;

    /**
     * @locale zh
     * @type api
     * @region 多房间
     * @brief 离开房间。  <br>
     *        用户调用此方法离开房间，结束通话过程，释放所有通话相关的资源。  <br>
     *        加入房间后，必须调用此方法结束通话，否则无法开始下一次通话。无论当前是否在房间内，都可以调用此方法。重复调用此方法没有负面影响。  <br>
     *        此方法是异步操作，调用返回时并没有真正退出房间。真正退出房间后，本地会收到 onLeaveRoom{@link #IRTCRoomEventHandler#onLeaveRoom} 回调通知。  
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note  
     *       + 可见的用户离开房间后，房间内其他用户会收到 onUserLeave{@link #IRTCRoomEventHandler#onUserLeave} 回调通知。  <br>
     *       + 如果调用此方法后立即销毁引擎，SDK 将无法触发 onLeaveRoom{@link #IRTCRoomEventHandler#onLeaveRoom} 回调。  
     */
    /**
     * @locale en
     * @type api
     * @region  room management
     * @brief  Leave RTC room.   <br>
     *        The user calls this method to leave the RTC room, end the call process, and release all call-related resources. <br>
     *        It is an asynchronous operation, and the call returns without actually exiting the room. When actually exiting the room, you will receive onLeaveRoom{@link #IRTCRoomEventHandler#onLeaveRoom}.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note   
     *        + When visible users leave the room, others in the room will receive onUserLeave{@link #IRTCRoomEventHandler#onUserLeave}. <br>
     *        + If the engine is destroyed immediately after this method is called, you will not receive onLeaveRoom{@link #IRTCRoomEventHandler#onLeaveRoom}. 
     */
    virtual int leaveRoom() = 0;

    /**
     * @locale zh
     * @type api
     * @brief 更新 Token。<br>
     *        收到 onTokenWillExpire{@link #IRTCRoomEventHandler#onTokenWillExpire}，onPublishPrivilegeTokenWillExpire{@link #IRTCRoomEventHandler#onPublishPrivilegeTokenWillExpire}， 或 onSubscribePrivilegeTokenWillExpire{@link #IRTCRoomEventHandler#onSubscribePrivilegeTokenWillExpire} 时，你必须重新获取 Token，并调用此方法更新 Token，以保证通话的正常进行。
     * @param token 重新获取的有效 Token。<br>
     *        如果 Token 无效，你会收到 onRoomStateChanged{@link #IRTCRoomEventHandler#onRoomStateChanged}，错误码是 `-1010`。
     * @return 方法调用结果：<br>
     *        + 0：成功；<br>
     *        + <0：失败。具体失败原因参看 ReturnStatus{@link #ReturnStatus}。
     * @note 
     *      + 3.50（不含）以前的版本中，Token 中的发布和订阅权限为保留参数，无实际控制权限；3.50 及以后版本开放 Token 发布订阅控制权限，如需通过 Token 控制连麦权限，请联系技术支持团队开通白名单后支持。<br>
     *      + 请勿同时调用 updateToken{@link #IRTCRoom#updateToken} 和 joinRoom{@link #IRTCRoom#joinRoom} 方法更新 Token。若因 Token 过期或无效导致加入房间失败或已被移出房间，你应该在获取新的有效 Token 后调用 joinRoom{@link #IRTCRoom#joinRoom} 重新加入房间。
     */
    /**
     * @locale en
     * @type api
     * @brief Update Token. <br>
     *        You must call this API to update token to ensure the RTC call to continue when you receive onTokenWillExpire{@link #IRTCRoomEventHandler#onTokenWillExpire}, onPublishPrivilegeTokenWillExpire{@link #IRTCRoomEventHandler#onPublishPrivilegeTokenWillExpire}, or onSubscribePrivilegeTokenWillExpire{@link #IRTCRoomEventHandler#onSubscribePrivilegeTokenWillExpire}.
     * @param token  Valid token.<br>
     *        If the Token is invalid, you will receive onRoomStateChanged{@link #IRTCRoomEventHandler#onRoomStateChanged} with the error code of `-1010`.
     * @return API call result:<br>
     *        + 0: Success.<br>
     *        + <0: Failure. See ReturnStatus{@link #ReturnStatus} for specific reasons.
     * @note 
     *      + In versions before 3.50, the publish and subscribe privileges contained in the Token are reserved parameters with no actual control permissions. In version 3.50 and later, the publish/subscribe privileges will be effective for whitelisted users. Please contact the technical support team to include you in the whitelist if you need this function.<br>
     *      + Do not call both updateToken{@link #IRTCRoom#updateToken} and joinRoom{@link #IRTCRoom#joinRoom} to update the Token. If you fail to join the room or have been removed from the room due to an expired or invalid Token, call joinRoom{@link #IRTCRoom#joinRoom} with a valid token to rejoin the room.
     */
    virtual int updateToken(const char* token) = 0;

    /**
     * @locale zh
     * @type api
     * @region 多房间
     * @brief 给房间内指定的用户发送点对点文本消息（P2P）。
     * @param uid  <br>
     *        消息接收用户的 ID
     * @param message  <br>
     *        发送的文本消息内容。  <br>
     *        消息不超过 64 KB。
     * @param config 消息类型，参看 MessageConfig{@link #MessageConfig}。
     * @return 这次发送消息的编号，从 1 开始递增。
     * @note  
     *       + 在发送房间内文本消息前，必须先调用 joinRoom{@link #IRTCRoom#joinRoom} 加入房间。  <br>
     *       + 调用该函数后会收到一次 onUserMessageSendResult{@link #IRTCRoomEventHandler#onUserMessageSendResult} 回调，通知消息发送方发送成功或失败；  <br>
     *       + 若文本消息发送成功，则 uid 所指定的用户会收到 onUserMessageReceived{@link #IRTCRoomEventHandler#onUserMessageReceived} 回调。
     */
    /**
     * @locale en
     * @type api
     * @region Multi-room
     * @brief Send a text message (P2P) to the specified user in the room
     * @param uid User ID of the message receiver
     * @param message <br>
     *        Text message content sent. <br>
     *         Message does not exceed 64 KB.
     * @param config Message type, see MessageConfig{@link #MessageConfig}.
     * @return The number of the message sent this time is incremented from 1.
     * @note   
     *        + Before sending an in-room text message, you must call joinRoom{@link #IRTCRoom#joinRoom} to join the room. <br>
     *        + After calling this function, you will receive an onUserMessageSendResult{@link #IRTCRoomEventHandler#onUserMessageSendResult} callback to notify the message sender that the sending was successful or failed; <br>
     *        + If the text message is sent successfully, the user specified by uid will receive onUserMessageReceived{@link #IRTCRoomEventHandler#onUserMessageReceived} callback.
     */
    virtual int64_t sendUserMessage(const char* uid, const char* message, MessageConfig config = kMessageConfigReliableOrdered) = 0;

    /**
     * @locale zh
     * @type api
     * @region 多房间
     * @brief 给房间内指定的用户发送点对点二进制消息（P2P）。
     * @param uid  <br>
     *        消息接收用户的 ID
     * @param length   <br>
     *        二进制字符串的长度。
     * @param message   <br>
     *        二进制消息的内容。<br>
     *        消息不超过 46KB。
     * @param config 消息类型，参看 MessageConfig{@link #MessageConfig}。
     * @return 这次发送消息的编号，从 1 开始递增。
     * @note  
     *       + 在发送房间内二进制消息前，必须先调用 joinRoom{@link #IRTCRoom#joinRoom} 加入房间。  <br>
     *       + 调用该函数后会收到一次 onUserMessageSendResult{@link #IRTCRoomEventHandler#onUserMessageSendResult} 回调，通知消息发送方发送成功或失败；  <br>
     *       + 若二进制消息发送成功，则 uid 所指定的用户会收到 onUserBinaryMessageReceived{@link #IRTCRoomEventHandler#onUserBinaryMessageReceived} 回调。
     */
    /**
     * @locale en
     * @type api
     * @region multi-room
     * @brief Sends a binary message (P2P) to the specified user in the room
     * @param uid User ID of the message receiver
     * @param length <br>
     *        The length of the binary string.
     * @param message <br>
     *         The content of the binary message. The message does not exceed 46KB.<br>
     *         The number of the message sent this time is incremented from
     * @param config Message type, see MessageConfig{@link #MessageConfig}.
     * @return Serial number of the message, starting form 1.
     * @note   + Before sending in-room binary messages, you must call joinRoom{@link #IRTCRoom#joinRoom} to join the room. <br>
     *        + After calling this function, you will receive an onUserMessageSendResult{@link #IRTCRoomEventHandler#onUserMessageSendResult} callback to notify the sender of the success or failure of the message; <br>
     *        + If the binary message is sent successfully, the user specified by uid will receive the onUserBinaryMessageReceived{@link #IRTCRoomEventHandler#onUserBinaryMessageReceived} callback.
     */
    virtual int64_t sendUserBinaryMessage(const char* uid, int length, const uint8_t* message, MessageConfig config = kMessageConfigReliableOrdered) = 0;

    /**
     * @locale zh
     * @type api
     * @region 多房间
     * @brief 给房间内的所有其他用户群发文本消息。
     * @param message  <br>
     *        用户发送的广播消息  <br>
     *        消息不超过 64 KB。
     * @note  
     *       + 在发送房间内二进制消息前，必须先调用 joinRoom{@link #IRTCRoom#joinRoom} 加入房间。  <br>
     *       + 调用该函数后，会收到一次 onRoomMessageSendResult{@link #IRTCRoomEventHandler#onRoomMessageSendResult} 回调。  <br>
     *       + 同一房间内的其他用户会收到 onRoomMessageReceived{@link #IRTCRoomEventHandler#onRoomMessageReceived} 回调。
     */
    /**
     * @locale en
     * @type api
     * @region Multi-room
     * @brief Send broadcast messages to all other users in the room.
     * @param message <br>
     *        The broadcast message sent by the user <br>
     *        Message does not exceed 64 KB.
     * @note   
     *        + Before sending in-room binary messages, you must call joinRoom{@link #IRTCRoom#joinRoom} to join the room. <br>
     *        + After calling this function, you get an onRoomMessageSendResult{@link #IRTCRoomEventHandler#onRoomMessageSendResult} callback. <br>
     *        + Other users in the same room receive an onRoomMessageReceived{@link #IRTCRoomEventHandler#onRoomMessageReceived} callback.
     */
    virtual int64_t sendRoomMessage(const char* message) = 0;
    /**
     * @locale zh
     * @type api
     * @region 多房间
     * @brief 给房间内的所有其他用户群发二进制消息。
     * @param size  <br>
     *        发送的二进制消息长度
     * @param message  <br>
     *        用户发送的二进制广播消息  <br>
     *        消息不超过 46KB。
     * @return 这次发送消息的编号，从 1 开始递增。
     * @note  
     *       + 在发送房间内二进制消息前，必须先调用 joinRoom{@link #IRTCRoom#joinRoom} 加入房间。  <br>
     *       + 调用该函数后，会收到一次 onRoomMessageSendResult{@link #IRTCRoomEventHandler#onRoomMessageSendResult} 回调。  <br>
     *       + 同一房间内的其他用户会收到 onRoomBinaryMessageReceived{@link #IRTCRoomEventHandler#onRoomBinaryMessageReceived} 回调。
     */
    /**
     * @locale en
     * @type api
     * @region Multi-room
     * @brief Send broadcast messages to all other users in the room.
     * @param size <br>
     *        The length of the binary message sent
     * @param message <br>
     *        The binary broadcast message sent by the user <br>
     *        The message does not exceed 46KB.
     * @return The number of the message sent this time is incremented from 1.
     * @note   
     *        + Before sending in-room binary messages, you must call joinRoom{@link #IRTCRoom#joinRoom} to join the room. <br>
     *        + After calling this function, you get an onRoomMessageSendResult{@link #IRTCRoomEventHandler#onRoomMessageSendResult} callback. <br>
     *        + Other users in the same room receive an onRoomBinaryMessageReceived{@link #IRTCRoomEventHandler#onRoomBinaryMessageReceived} callback.
     */
    virtual int64_t sendRoomBinaryMessage(int size, const uint8_t* message) = 0;

    /**
     * @locale zh
     * @type api
     * @region 房间管理
     * @brief 在当前所在房间内发布本地通过摄像头/麦克风采集的媒体流
     * @param type 媒体流类型，用于指定发布音频/视频，参看 MediaStreamType{@link #MediaStreamType}
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note 
     *        + 如果你已经在用户进房时通过调用 joinRoom{@link #IRTCRoom#joinRoom} 成功选择了自动发布，则无需再调用本接口。<br>
     *        + 调用 setUserVisibility{@link #IRTCRoom#setUserVisibility} 方法将自身设置为不可见后无法调用该方法，需将自身切换至可见后方可调用该方法发布摄像头音视频流。 <br>
     *        + 如果你需要发布屏幕共享流，调用 publishScreen{@link #IRTCRoom#publishScreen}。(Linux 不适用)<br>
     *        + 如果你需要向多个房间发布流，调用 startForwardStreamToRooms{@link #IRTCRoom#startForwardStreamToRooms}。  <br>
     *        + 调用此方法后，房间中的所有远端用户会收到 onUserPublishStream{@link #IRTCRoomEventHandler#onUserPublishStream} 回调通知，其中成功收到了音频流的远端用户会收到 onFirstRemoteAudioFrame{@link #IRTCVideoEventHandler#onFirstRemoteAudioFrame} 回调，订阅了视频流的远端用户会收到 onFirstRemoteVideoFrameDecoded{@link #IRTCVideoEventHandler#onFirstRemoteVideoFrameDecoded} 回调。<br>
     *        + 调用 unpublishStream{@link #IRTCRoom#unpublishStream} 取消发布。
     */
    /**
     * @locale en
     * @type api
     * @region Room Management
     * @brief Publishes media streams captured by camera/microphone in the current room.
     * @param type Media stream type, used for specifying whether to publish audio stream or video stream. See MediaStreamType{@link #MediaStreamType}.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note  
     *        + You don't need to call this API if you set it to Auto-publish when calling joinRoom{@link #IRTCRoom#joinRoom}.   <br>
     *        + An invisible user cannot publish media streams. Call setUserVisibility{@link #IRTCRoom#setUserVisibility} to change your visibility in the room.  <br>
     *        + Call publishScreen{@link #IRTCRoom#publishScreen} to start screen sharing. Not available on Linux.  <br>
     *        + Call startForwardStreamToRooms{@link #IRTCRoom#startForwardStreamToRooms} to forward the published streams to the other rooms.  <br>
     *        + After you call this API, the other users in the room will receive onUserPublishStream{@link #IRTCRoomEventHandler#onUserPublishStream}. Those who successfully received your streams will receive onFirstRemoteAudioFrame{@link #IRTCVideoEventHandler#onFirstRemoteAudioFrame}/onFirstRemoteVideoFrameDecoded{@link #IRTCVideoEventHandler#onFirstRemoteVideoFrameDecoded} at the same time.  <br>
     *        + Call unpublishStream{@link #IRTCRoom#unpublishStream} to stop publishing streams.
     */
    virtual int publishStream(MediaStreamType type) = 0;

    /**
     * @locale zh
     * @type api
     * @region 房间管理
     * @brief 停止将本地摄像头/麦克风采集的媒体流发布到当前所在房间中
     * @param type 媒体流类型，用于指定停止发布音频/视频，参看 MediaStreamType{@link #MediaStreamType}
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note  
     *        + 调用 publishStream{@link #IRTCRoom#publishStream} 手动发布摄像头音视频流后，你需调用此接口停止发布。<br>
     *        + 调用此方法停止发布音视频流后，房间中的其他用户将会收到 onUserUnpublishStream{@link #IRTCRoomEventHandler#onUserUnpublishStream} 回调通知。
     */
    /**
     * @locale en
     * @type api
     * @region Room Management
     * @brief Stops publishing media streams captured by camera/microphone in the current room.
     * @param type Media stream type, used for specifying whether to stop publishing audio stream or video stream. See MediaStreamType{@link #MediaStreamType}.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note  
     *         + After calling publishStream{@link #IRTCRoom#publishStream}, call this API to stop publishing streams. <br>
     *         + After calling this API, the other users in the room will receive onUserUnpublishStream{@link #IRTCRoomEventHandler#onUserUnpublishStream}.
     */
    virtual int unpublishStream(MediaStreamType type) = 0;

    /**
     * @locale zh
     * @type api
     * @region 屏幕共享
     * @brief 在当前所在房间内手动发布本地屏幕共享音视频流。<br>
     *        如果你需要手动向多个房间发布屏幕共享流，可以使用同样的 uid 加入多个房间，并在每个房间调用该方法。同时，你可以在不同的房间发布不同的屏幕共享流类型。
     * @param type 媒体流类型，用于指定发布屏幕音频/视频，参看 MediaStreamType{@link #MediaStreamType}。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note 
     *        + 即使你已经在用户进房时通过调用 joinRoom{@link #IRTCRoom#joinRoom} 成功选择了自动发布，也需要调用本接口。<br>
     *        + 调用 setUserVisibility{@link #IRTCRoom#setUserVisibility} 方法将自身设置为不可见后无法调用该方法，需将自身切换至可见后方可调用该方法发布屏幕流。 <br>
     *        + 调用该方法后，房间中的所有远端用户会收到 onUserPublishScreen{@link #IRTCRoomEventHandler#onUserPublishScreen} 回调，其中成功收到音频流的远端用户会收到 onFirstRemoteAudioFrame{@link #IRTCVideoEventHandler#onFirstRemoteAudioFrame} 回调，订阅了视频流的远端用户会收到 onFirstRemoteVideoFrameDecoded{@link #IRTCVideoEventHandler#onFirstRemoteVideoFrameDecoded} 回调。<br>
     *        + 调用该方法后，本地用户会收到 onScreenVideoFrameSendStateChanged{@link #IRTCVideoEventHandler#onScreenVideoFrameSendStateChanged}。<br>
     *        + 调用 unpublishScreen{@link #IRTCRoom#unpublishScreen} 取消发布。 <br>
     *        + 对 Linux，仅支持发布视频流。<br>
     *        + 查看 [PC 端屏幕共享](https://www.volcengine.com/docs/6348/70144)，获取更多信息。
     */
    /**
     * @locale en
     * @type api
     * @region Screen Sharing
     * @brief Manually publishes local screen-sharing streams in the current room.<br>
     *        If you need to share your screen in multiple rooms, you can use the same uid to join multiple rooms and call this API in each room. Also, you can publish different types of screen-sharing streams in different rooms.
     * @param type Media stream type, used for specifying whether to publish audio stream or video stream. See MediaStreamType{@link #MediaStreamType}.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note  
     *        + You need to call this API to publish screen even if you set it to Auto-publish when calling joinRoom{@link #IRTCRoom#joinRoom}.   <br>
     *        + An invisible user cannot publish media streams. Call setUserVisibility{@link #IRTCRoom#setUserVisibility} to change your visibility in the room. <br>
     *        + After you called this API, the other users in the room will receive onUserPublishScreen{@link #IRTCRoomEventHandler#onUserPublishScreen}. Those who successfully received your streams will receive onFirstRemoteAudioFrame{@link #IRTCVideoEventHandler#onFirstRemoteAudioFrame}/onFirstRemoteVideoFrameDecoded{@link #IRTCVideoEventHandler#onFirstRemoteVideoFrameDecoded} at the same time.  <br>
     *        + After calling this API, you'll receive onScreenVideoFrameSendStateChanged{@link #IRTCVideoEventHandler#onScreenVideoFrameSendStateChanged}. <br>
     *        + Call unpublishScreen{@link #IRTCRoom#unpublishScreen} to stop publishing screen sharing streams. <br>
     *        + On Linux, you can only publish video streams.<br>
     *        + Refer to [Sharing Screen in PC](https://docs.byteplus.com/byteplus-rtc/docs/70144) for more information.
     */
    virtual int publishScreen(MediaStreamType type) = 0;

    /**
     * @locale zh
     * @type api
     * @region 屏幕共享
     * @brief 停止将本地屏幕共享音视频流发布到当前所在房间中
     * @param type 媒体流类型，用于指定停止发布屏幕音频/视频，参看 MediaStreamType{@link #MediaStreamType}
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note 
     *        + 调用 publishScreen{@link #IRTCRoom#publishScreen} 发布屏幕流后，你需调用此接口停止发布。 <br>
     *        + 调用此方法停止发布屏幕音视频流后，房间中的其他用户将会收到 onUserUnpublishScreen{@link #IRTCRoomEventHandler#onUserUnpublishScreen} 回调。
     */
    /**
     * @locale en
     * @type api
     * @region Screen Sharing
     * @brief Stops publishing local screen sharing streams in the current room.
     * @param type Media stream type, used for specifying whether to stop publishing audio stream or video stream. See MediaStreamType{@link #MediaStreamType}.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note  
     *         + After calling publishScreen{@link #IRTCRoom#publishScreen}, call this API to stop publishing streams. <br>
     *         + After calling this API, the other users in the room will receive onUserUnpublishScreen{@link #IRTCRoomEventHandler#onUserUnpublishScreen}.
     */
    virtual int unpublishScreen(MediaStreamType type) = 0;

    /**
     * @locale zh
     * @deprecated since 3.36 and will be deleted in 3.51, use subscribeStream{@link #IRTCRoom#subscribeStream}, unsubscribeStream{@link #IRTCRoom#unsubscribeStream}, subscribeScreen{@link #IRTCRoom#subscribeScreen} and unsubscribeScreen{@link #IRTCRoom#unsubscribeScreen} instead.
     * @type api
     * @region 多房间
     * @brief 订阅房间内指定的远端音视频流。  <br>
     *        无论是自动订阅还是手动订阅模式，你都可以调用此方法按需订阅房间中的音视频流。  <br>
     *        该方法也可用于更新已经订阅的流的属性、媒体类型等配置。 
     * @param user_id 指定订阅的远端发布音视频流的用户 ID。
     * @param stream_type 流属性，用于指定订阅主流/屏幕流，参看 StreamIndex{@link #StreamIndex}。
     * @param media_type 媒体类型，用于指定订阅音/视频，参看 SubscribeMediaType{@link #SubscribeMediaType}。
     * @param video_config 视频订阅配置，参看 SubscribeVideoConfig{@link #SubscribeVideoConfig}。
     * @note  
     *        + 若订阅失败，你会收到 onStreamStateChanged{@link #IRTCRoomEventHandler#onStreamStateChanged} 回调通知，具体失败原因参看 ErrorCode{@link #ErrorCode}。<br>
     *        + 若调用 pauseAllSubscribedStream{@link #IRTCRoom#pauseAllSubscribedStream} 暂停接收远端音视频流，此时仍可使用该方法对暂停接收的流进行设置，你会在调用 resumeAllSubscribedStream{@link #IRTCRoom#resumeAllSubscribedStream} 恢复接收流后收到修改设置后的流。  
     */
    /**
     * @locale en
     * @deprecated since 3.45 and will be deleted in 3.51, use subscribeStream{@link #IRTCRoom#subscribeStream}, unsubscribeStream{@link #IRTCRoom#unsubscribeStream}, subscribeScreen{@link #IRTCRoom#subscribeScreen} and unsubscribeScreen{@link #IRTCRoom#unsubscribeScreen} instead.
     * @type api
     * @region Multi-room
     * @brief Subscribe to media streams in the room.   <br>
     *        Call this API to subscribe to media streams in the room regardless of subscription mode, either Auto or Manual. <br>
     *        Call this API to update the properties and configurations of the stream you have already subscribed to. 
     * @param user_id User ID of the publisher of the subscribed media stream 
     * @param stream_type Mainstream or screen-sharing stream. Refer to StreamIndex{@link #StreamIndex} for details.
     * @param media_type Media stream type to be subscribed to. Refer to  SubscribeMediaType{@link #SubscribeMediaType} for details. 
     * @param video_config Subscription configuration of video streams. Refer to SubscribeVideoConfig{@link #SubscribeVideoConfig} for details. 
     * @note   
     *         + If the subscription fails, you will receive onStreamStateChanged{@link #IRTCRoomEventHandler#onStreamStateChanged}. Refer to ErrorCode{@link #ErrorCode} for the specific reason of failure.<br>
     *         + You can update the subscription configuration by calling the API even after calling pauseAllSubscribedStream{@link #IRTCRoom#pauseAllSubscribedStream} to pause streaming. Call resumeAllSubscribedStream{@link #IRTCRoom#resumeAllSubscribedStream} to resume streaming and apply the changes. 
     */
    BYTERTC_DEPRECATED virtual int subscribeUserStream(const char* user_id, StreamIndex stream_type, SubscribeMediaType media_type, const SubscribeVideoConfig& video_config) = 0;
    /**
     * @locale zh
     * @type api
     * @region 视频管理
     * @brief 设置期望订阅的远端视频流的参数。
     * @param user_id 期望配置订阅参数的远端视频流发布用户的 ID。
     * @param remote_video_config 期望配置的远端视频流参数，参看 RemoteVideoConfig{@link #RemoteVideoConfig}。
     * @return 方法调用结果：<br>
     *        + 0：成功；<br>
     *        + <0：失败。具体失败原因参看 ReturnStatus{@link #ReturnStatus}。
     * @note 
     *        + 若使用 342 及以前版本的 SDK，调用该方法前请联系技术支持人员开启按需订阅功能。  <br>
     *        + 该方法仅在发布端调用 enableSimulcastMode{@link #IRTCVideo#enableSimulcastMode} 开启了发送多路视频流的情况下生效，此时订阅端将收到来自发布端与期望设置的参数最相近的一路流；否则订阅端只会收到一路参数为分辨率 640px × 360px、帧率 15fps 的视频流。  <br>
     *        + 若发布端开启了推送多路流功能，但订阅端不对流参数进行设置，则默认接受发送端设置的分辨率最大的一路视频流。  <br>
     *        + 该方法需在进房后调用，若想进房前设置，你需调用 joinRoom{@link #IRTCRoom#joinRoom}，并对 `room_config` 中的 `remote_video_config` 进行设置。  <br>
     *        + SDK 会根据发布端和所有订阅端的设置灵活调整视频流的参数，具体调整策略详见[推送多路流](https://www.volcengine.com/docs/6348/70139)文档。
     */
    /**
     * @locale en
     * @type api
     * @region Video Management
     * @brief Sets your expected configuration of the remote video stream that you want to subscribe to or have subscribed to.
     * @param user_id ID of the remote video stream publisher you expect to configure subscription parameters for.
     * @param remote_video_config The parameters you expect to configure for the remote video stream, see RemoteVideoConfig{@link #RemoteVideoConfig}.
     * @return API call result:<br>
     *        + 0: Success.<br>
     *        + <0: Failure. See ReturnStatus{@link #ReturnStatus} for specific reasons.
     * @note 
     *        + This API only works after the publisher calls enableSimulcastMode{@link #IRTCVideo#enableSimulcastMode} to enable publishing multiple video streams, in which case the subscriber will receive the stream from the publisher that is closest to the set configuration;  otherwise the subscriber will only receive one video stream with a resolution of 640px × 360px and a frame rate of 15fps.  <br>
     *        + If you don't call this API after the publisher enables the function of publishing multiple streams, you will receive by default the video stream with the largest resolution set by the publisher.  <br>
     *        + You should call this API in the room. If you want to call it before entering the room, you should set the `remote_video_config` in the `room_config` when calling joinRoom{@link #IRTCRoom#joinRoom}.  <br>
     *        + SDK will automatically select the stream to be published or subscribed based on the settings of both sides.
     */
    virtual int setRemoteVideoConfig(const char *user_id,const RemoteVideoConfig &remote_video_config) = 0;

    /**
     * @locale zh
     * @type api
     * @region 房间管理
     * @brief 订阅房间内指定的通过摄像头/麦克风采集的媒体流，或更新对指定远端用户的订阅选项
     * @param user_id 指定订阅的远端发布音视频流的用户 ID。
     * @param type 媒体流类型，用于指定订阅音频/视频。参看 MediaStreamType{@link #MediaStreamType}。
     * @return 方法调用结果：<br>
     *        + 0：成功；<br>
     *        + <0：失败。具体失败原因参看 ReturnStatus{@link #ReturnStatus}。
     * @note  
     *        + 若当前用户在调用本接口时已经订阅该远端用户（手动订阅或自动订阅），则将根据本次传入的参数，更新订阅配置。<br>
     *        + 你必须先通过 onUserPublishStream{@link #IRTCRoomEventHandler#onUserPublishStream} 回调获取当前房间里的远端摄像头音视频流信息，然后调用本方法按需订阅。  <br>
     *        + 调用该方法后，你会收到 onStreamSubscribed{@link #IRTCRoomEventHandler#onStreamSubscribed} 通知方法调用结果。  <br>
     *        + 成功订阅远端用户的媒体流后，订阅关系将持续到调用 unsubscribeStream{@link #IRTCRoom#unsubscribeStream} 取消订阅或本端用户退房。 <br>
     *        + 关于其他调用异常，你会收到 onStreamStateChanged{@link #IRTCRoomEventHandler#onStreamStateChanged} 回调通知，具体异常原因参看 ErrorCode{@link #ErrorCode}。
     */
    /**
     * @locale en
     * @type api
     * @region Room Management
     * @brief Subscribes to specific remote media streams captured by camera/microphone.  Or update the subscribe options of the subscribed user.
     * @param user_id The ID of the remote user who published the target audio/video stream.
     * @param type Media stream type, used for specifying whether to subscribe to the audio stream or the video stream. See MediaStreamType{@link #MediaStreamType}.
     * @return API call result:<br>
     *        + 0: Success.<br>
     *        + <0: Failure. See ReturnStatus{@link #ReturnStatus} for specific reasons.
     * @note  
     *        + Calling this API to update the subscribe configuration when the user has subscribed the remote user either by calling this API or by auto-subscribe.  <br>
     *        + You must first get the remote stream information through onUserPublishStream{@link #IRTCRoomEventHandler#onUserPublishStream}} before calling this API to subscribe to streams accordingly.  <br>
     *        + After calling this API, you will be informed of the calling result with onStreamSubscribed{@link #IRTCRoomEventHandler#onStreamSubscribed}.  <br>
     *        + Once the local user subscribes to the stream of a remote user, the subscription to the remote user will sustain until the local user leaves the room or unsubscribe from it by calling unsubscribeStream{@link #IRTCRoom#unsubscribeStream}.<br>
     *        + Any other exceptions will be included in onStreamStateChanged{@link #IRTCRoomEventHandler#onStreamStateChanged}, see ErrorCode{@link #ErrorCode} for the reasons.
     */
    virtual int subscribeStream(const char *user_id,MediaStreamType type) = 0;
    /**
     * @locale zh
     * @type api
     * @region 房间管理
     * @brief 订阅房间内所有通过摄像头/麦克风采集的媒体流，或更新订阅选项。
     * @param type 媒体流类型，用于指定订阅音频/视频。参看 MediaStreamType{@link #MediaStreamType}。
     * @return  
     *        0: 方法调用成功  <br>
     *        !0: 方法调用失败  
     * @note  
     *        + 多次调用订阅接口时，将根据末次调用接口和传入的参数，更新订阅配置。<br>
     *        + 开启音频选路后，如果房间内的媒体流超过上限，建议通过调用 subscribeStream{@link #IRTCRoom#subscribeStream} 逐一指定需要订阅的媒体流。<br>
     *        + 调用该方法后，你会收到 onStreamSubscribed{@link #IRTCRoomEventHandler#onStreamSubscribed} 通知方法调用结果。  <br>
     *        + 成功订阅远端用户的媒体流后，订阅关系将持续到调用 unsubscribeStream{@link #IRTCRoom#unsubscribeStream} 取消订阅或本端用户退房。 <br>
     *        + 关于其他调用异常，你会收到 onStreamStateChanged{@link #IRTCRoomEventHandler#onStreamStateChanged} 回调通知，具体异常原因参看 ErrorCode{@link #ErrorCode}。
     */
     /**
     * @locale en
     * @type api
     * @region Room Management
     * @brief Subscribes to all remote media streams captured by camera/microphone. Or update the subscribe options of all subscribed user.
     * @param type Media stream type, used for specifying whether to subscribe to the audio stream or the video stream. See MediaStreamType{@link #MediaStreamType}.
     * @return API call result:  <br>
     *        + 0: Success  <br>
     *        + !0: Failure
     * @note  
     *        + If the subscription options conflict with the previous ones, they are subject to the configurations in the last call.<br>
     *        + With the Audio selection enabled, if the number of media streams exceeds the limit, we recommend you call subscribeStream{@link #IRTCRoom#subscribeStream} to subscribe each target media stream other than calling this API.<br>
     *        + After calling this API, you will be informed of the calling result with onStreamSubscribed{@link #IRTCRoomEventHandler#onStreamSubscribed}.  <br>
     *        + Once the local user subscribes to the stream of a remote user, the subscription to the remote user will sustain until the local user leaves the room or unsubscribe from it by calling unsubscribeStream{@link #IRTCRoom#unsubscribeStream}.<br>
     *        + Any other exceptions will be included in onStreamStateChanged{@link #IRTCRoomEventHandler#onStreamStateChanged}, see ErrorCode{@link #ErrorCode} for the reasons.
     */
    virtual int subscribeAllStreams(MediaStreamType type) = 0;

    /**
     * @locale zh
     * @type api
     * @region 房间管理
     * @brief 取消订阅房间内指定的通过摄像头/麦克风采集的媒体流。  <br>
     *        该方法对自动订阅和手动订阅模式均适用。
     * @param user_id 指定取消订阅的远端发布音视频流的用户 ID。
     * @param type 媒体流类型，用于指定取消订阅音频/视频。参看 MediaStreamType{@link #MediaStreamType}。
     * @return 方法调用结果：<br>
     *        + 0：成功；<br>
     *        + <0：失败。具体失败原因参看 ReturnStatus{@link #ReturnStatus}。
     * @note  
     *        + 调用该方法后，你会收到 onStreamSubscribed{@link #IRTCRoomEventHandler#onStreamSubscribed} 通知方法调用结果。  <br>
     *        + 关于其他调用异常，你会收到 onStreamStateChanged{@link #IRTCRoomEventHandler#onStreamStateChanged} 回调通知，具体失败原因参看 ErrorCode{@link #ErrorCode}。
     */
    /**
     * @locale en
     * @type api
     * @region Room Management
     * @brief Unsubscribes from specific remote media streams captured by camera/microphone.  <br>
     *        You can call this API in both automatic subscription mode and manual subscription mode.
     * @param user_id The ID of the remote user who published the target audio/video stream.
     * @param type Media stream type, used for specifying whether to unsubscribe from the audio stream or the video stream. See MediaStreamType{@link #MediaStreamType}.
     * @return API call result:<br>
     *        + 0: Success.<br>
     *        + <0: Failure. See ReturnStatus{@link #ReturnStatus} for specific reasons.
     * @note  
     *        + After calling this API, you will be informed of the calling result with onStreamSubscribed{@link #IRTCRoomEventHandler#onStreamSubscribed}.  <br>
     *        + Any other exceptions will be included in onStreamStateChanged{@link #IRTCRoomEventHandler#onStreamStateChanged}, see ErrorCode{@link #ErrorCode} for the reasons.
     */
    virtual int unsubscribeStream(const char *user_id,MediaStreamType type) = 0;
    /**
     * @locale zh
     * @type api
     * @region 房间管理
     * @brief 取消订阅房间内所有的通过摄像头/麦克风采集的媒体流。  <br>
     *        自动订阅和手动订阅的流都可以通过本方法取消订阅。
     * @param type 媒体流类型，用于指定取消订阅音频/视频。参看 MediaStreamType{@link #MediaStreamType}。
     * @return 方法调用结果：  <br>
     *        + 0：成功  <br>
     *        + !0：失败
     * @note  
     *        + 调用该方法后，你会收到 onStreamSubscribed{@link #IRTCRoomEventHandler#onStreamSubscribed} 通知方法调用结果。  <br>
     *        + 关于其他调用异常，你会收到 onStreamStateChanged{@link #IRTCRoomEventHandler#onStreamStateChanged} 回调通知，具体失败原因参看 ErrorCode{@link #ErrorCode}。
     */
    /**
     * @locale en
     * @type api
     * @region Room Management
     * @brief Unsubscribes from all remote media streams captured by camera/microphone.  <br>
     *        You can call this API to unsubscribe from streams that are subscribed to either automatically or manually.
     * @param type Media stream type, used for specifying whether to unsubscribe from the audio stream or the video stream. See MediaStreamType{@link #MediaStreamType}.
     * @return API call result:  <br>
     *        + 0: Success  <br>
     *        + !0: Failure
     * @note  
     *        + After calling this API, you will be informed of the calling result with onStreamSubscribed{@link #IRTCRoomEventHandler#onStreamSubscribed}.  <br>
     *        + Any other exceptions will be included in onStreamStateChanged{@link #IRTCRoomEventHandler#onStreamStateChanged}, see ErrorCode{@link #ErrorCode} for the reasons.
     */
    virtual int unsubscribeAllStreams(MediaStreamType type) = 0;
    /**
     * @locale zh
     * @type api
     * @region 房间管理
     * @brief 订阅房间内指定的远端屏幕共享音视频流，或更新对指定远端用户的订阅选项
     * @param user_id 指定订阅的远端发布屏幕流的用户 ID。
     * @param type 媒体流类型，用于指定订阅音频/视频。参看 MediaStreamType{@link #MediaStreamType}。
     * @return 方法调用结果：<br>
     *        + 0：成功；<br>
     *        + <0：失败。具体失败原因参看 ReturnStatus{@link #ReturnStatus}。
     * @note  
     *        + 若当前用户在调用本接口时已经订阅该远端用户（手动订阅或自动订阅），则将根据本次传入的参数，更新订阅配置。<br>
     *        + 你必须先通过 onUserPublishScreen{@link #IRTCRoomEventHandler#onUserPublishScreen}} 回调获取当前房间里的远端屏幕流信息，然后调用本方法按需订阅。  <br>
     *        + 调用该方法后，你会收到 onStreamSubscribed{@link #IRTCRoomEventHandler#onStreamSubscribed} 通知方法调用结果。  <br>
     *        + 成功订阅远端用户的媒体流后，订阅关系将持续到调用 unsubscribeScreen{@link #IRTCRoom#unsubscribeScreen} 取消订阅或本端用户退房。 <br>
     *        + 关于其他调用异常，你会收到 onStreamStateChanged{@link #IRTCRoomEventHandler#onStreamStateChanged} 回调通知，具体异常原因参看 ErrorCode{@link #ErrorCode}。
     */
    /**
     * @locale en
     * @type api
     * @region Room Management
     * @brief Subscribes to specific screen sharing media stream.   Or update the subscribe options of the subscribed user.
     * @param user_id The ID of the remote user who published the target screen audio/video stream.
     * @param type Media stream type, used for specifying whether to subscribe to the audio stream or the video stream. See MediaStreamType{@link #MediaStreamType}.
     * @return API call result:<br>
     *        + 0: Success.<br>
     *        + <0: Failure. See ReturnStatus{@link #ReturnStatus} for specific reasons.
     * @note  
     *        + Calling this API to update the subscribe configuration when the user has subscribed the remote user either by calling this API or by auto-subscribe.  <br>
     *        + You must first get the remote stream information through onUserPublishScreen{@link #IRTCRoomEventHandler#onUserPublishScreen}} before calling this API to subscribe to streams accordingly.  <br>
     *        + After calling this API, you will be informed of the calling result with onStreamSubscribed{@link #IRTCRoomEventHandler#onStreamSubscribed}.  <br>
     *        + Once the local user subscribes to the stream of a remote user, the subscription to the remote user will sustain until the local user leaves the room or unsubscribe from it by calling unsubscribeScreen{@link #IRTCRoom#unsubscribeScreen}.<br>
     *        + Any other exceptions will be included in onStreamStateChanged{@link #IRTCRoomEventHandler#onStreamStateChanged}, see ErrorCode{@link #ErrorCode} for the reasons.
     */
    virtual int subscribeScreen(const char *user_id,MediaStreamType type) = 0;

    /**
     * @locale zh
     * @type api
     * @region 房间管理
     * @brief 取消订阅房间内指定的远端屏幕共享音视频流。  <br>
     *        该方法对自动订阅和手动订阅模式均适用。
     * @param user_id 指定取消订阅的远端发布屏幕流的用户 ID。
     * @param type 媒体流类型，用于指定取消订阅音频/视频。参看 MediaStreamType{@link #MediaStreamType}。
     * @return 方法调用结果：<br>
     *        + 0：成功；<br>
     *        + <0：失败。具体失败原因参看 ReturnStatus{@link #ReturnStatus}。
     * @note  
     *        + 调用该方法后，你会收到 onStreamSubscribed{@link #IRTCRoomEventHandler#onStreamSubscribed} 通知方法调用结果。  <br>
     *        + 关于其他调用异常，你会收到 onStreamStateChanged{@link #IRTCRoomEventHandler#onStreamStateChanged} 回调通知，具体失败原因参看 ErrorCode{@link #ErrorCode}。
     */
    /**
     * @locale en
     * @type api
     * @region Room Management
     * @brief Unsubscribes from specific screen sharing media stream.  <br>
     *        You can call this API in both automatic subscription mode and manual subscription mode.
     * @param user_id The ID of the remote user who published the target screen audio/video stream.
     * @param type Media stream type, used for specifying whether to unsubscribe from the audio stream or the video stream. See MediaStreamType{@link #MediaStreamType}.
     * @return API call result:<br>
     *        + 0: Success.<br>
     *        + <0: Failure. See ReturnStatus{@link #ReturnStatus} for specific reasons.
     * @note  
     *        + After calling this API, you will be informed of the calling result with onStreamSubscribed{@link #IRTCRoomEventHandler#onStreamSubscribed}.  <br>
     *        + Any other exceptions will be included in onStreamStateChanged{@link #IRTCRoomEventHandler#onStreamStateChanged}, see ErrorCode{@link #ErrorCode} for the reasons.
     */
    virtual int unsubscribeScreen(const char *user_id,MediaStreamType type) = 0;

    /**
     * @hidden for internal use only.
     */
    virtual int enableSubscribeLocalStream(bool enable) = 0;

    /**
     * @locale zh
     * @type api
     * @region 多房间
     * @brief 暂停接收来自远端的媒体流。
     * @param media_type 媒体流类型，指定需要暂停接收音频还是视频流，参看 PauseResumeControlMediaType{@link #PauseResumeControlMediaType}。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note  
     *        + 该方法仅暂停远端流的接收，并不影响远端流的采集和发送；  <br>
     *        + 该方法不改变用户的订阅状态以及订阅流的属性。  <br>
     *        + 若想恢复接收远端流，需调用 resumeAllSubscribedStream{@link #IRTCRoom#resumeAllSubscribedStream}。 <br>
     *        + 多房间场景下，仅暂停接收发布在当前所在房间的流。
     */
    /**
     * @locale en
     * @type api
     * @region Multi-room
     * @brief Pause receiving remote media streams.
     * @param media_type Media stream type subscribed to. Refer to PauseResumeControlMediaType{@link #PauseResumeControlMediaType}.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note   
     *         + Calling this API does not change the capture state and the transmission state of the remote clients. <br>
     *         + Calling this API does not cancel the subscription or change any subscription configuration. <br>
     *         + To resume, call resumeAllSubscribedStream{@link #IRTCRoom#resumeAllSubscribedStream}. <br>
     *         + In a multi-room scenario, this API only pauses the reception of streams published in the current room.
     */
    virtual int pauseAllSubscribedStream(PauseResumeControlMediaType media_type) = 0;

    /**
     * @locale zh
     * @type api
     * @region 多房间
     * @brief 恢复接收来自远端的媒体流
     * @param media_type 媒体流类型，指定需要暂停接收音频还是视频流，参看 PauseResumeControlMediaType{@link #PauseResumeControlMediaType}
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note 
     *        + 该方法仅恢复远端流的接收，并不影响远端流的采集和发送；  <br>
     *        + 该方法不改变用户的订阅状态以及订阅流的属性。
     */
    /**
     * @locale en
     * @type api
     * @region  multi-room
     * @brief  Resume receiving remote media streams
     * @param media_type Media stream type subscribed to. Refer to PauseResumeControlMediaType{@link #PauseResumeControlMediaType}
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note  
     *         + Calling this API does not change the capture state and the transmission state of the remote clients.<br>
     *         + Calling this API does not change any subscription configuration.
     */
    virtual int resumeAllSubscribedStream(PauseResumeControlMediaType media_type) = 0;


    /**
     * @locale zh
     * @type api
     * @region 多房间
     * @brief 设置发流端音画同步。  <br>
     *        当同一用户同时使用两个通话设备分别采集发送音频和视频时，有可能会因两个设备所处的网络环境不一致而导致发布的流不同步，此时你可以在视频发送端调用该接口，SDK 会根据音频流的时间戳自动校准视频流，以保证接收端听到音频和看到视频在时间上的同步性。
     * @param audio_user_id 音频发送端的用户 ID，将该参数设为空则可解除当前音视频的同步关系。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note 
     *        + 该方法在进房前后均可调用。  <br>
     *        + 进行音画同步的音频发布用户 ID 和视频发布用户 ID 须在同一个 RTC 房间内。  <br>
     *        + 调用该接口后音画同步状态发生改变时，你会收到 onAVSyncStateChange{@link #IRTCRoomEventHandler#onAVSyncStateChange} 回调。  <br>
     *        + 同一 RTC 房间内允许存在多个音视频同步关系，但需注意单个音频源不支持与多个视频源同时同步。  <br>
     *        + 如需更换同步音频源，再次调用该接口传入新的 `audio_user_id` 即可；如需更换同步视频源，需先解除当前的同步关系，后在新视频源端开启同步。
     */
    /**
     * @locale en
     * @type api
     * @region Multi-room
     * @brief Synchronizes published audio and video.  <br>
     *        When the same user simultaneously uses separate devices to capture and publish audio and video, there is a possibility that the streams are out of sync due to the network disparity. In this case, you can call this API on the video publisher side and the SDK will automatically line the video stream up according to the timestamp of the audio stream, ensuring that the audio the receiver hears corresponds to the video the receiver watches.
     * @param audio_user_id The ID of audio publisher. You can stop the current A/V synchronization by setting this parameter to null.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note  
     *        + You can call this API anytime before or after entering the room.  <br>
     *        + The source user IDs of the audio and video stream to be synchronized must be in the same RTC room.  <br>
     *        + When the A/V synchronization state changes, you will receive onAVSyncStateChange{@link #IRTCRoomEventHandler#onAVSyncStateChange}.  <br>
     *        + More than one pair of audio and video can be synchronized simultaneously in the same RTC room, but you should note that one single audio source cannot be synchronized with multiple video sources at the same time.  <br>
     *        + If you want to change the audio source, call this API again with a new `audio_user_id`. If you want to change the video source, you need to stop the current synchronization first, then call this API on the new video publisher side.
     */
    virtual int setMultiDeviceAVSync(const char* audio_user_id) = 0;

    /**
     * @hidden for internal use only.
     */
    virtual int updateCloudRendering(const char* cloudrender_json_string) = 0;


    /**
     * @hidden for internal use only.
     */
    virtual int setCustomUserRole(const char* role) = 0;

    /**
     * @locale zh
     * @type api
     * @region 多房间
     * @brief 开始跨房间转发媒体流。<br>
     *        在调用 joinRoom{@link #IRTCRoom#joinRoom} 后调用本接口，实现向多个房间转发媒体流，适用于跨房间连麦等场景。
     * @param configuration 跨房间媒体流转发指定房间的信息。参看 ForwardStreamConfiguration{@link #ForwardStreamConfiguration}。
     * @return  
     *        0: 方法调用成功  <br>
     *        <0: 方法调用失败  
     * @note 
     *        + 调用本方法后，将在本端触发 onForwardStreamStateChanged{@link #IRTCRoomEventHandler#onForwardStreamStateChanged} 回调。<br>
     *        + 调用本方法后，你可以通过监听 onForwardStreamEvent{@link #IRTCRoomEventHandler#onForwardStreamEvent} 回调来获取各个目标房间在转发媒体流过程中的相关事件。<br>
     *        + 开始转发后，目标房间中的用户将接收到本地用户进房 onUserJoined{@link #IRTCRoomEventHandler#onUserJoined} 和发流 onUserPublishStream{@link #IRTCRoomEventHandler#onUserPublishStream}/onUserPublishScreen{@link #IRTCRoomEventHandler#onUserPublishScreen} 的回调。<br>
     *        + 调用本方法后，可以调用 updateForwardStreamToRooms{@link #IRTCRoom#updateForwardStreamToRooms} 更新目标房间信息，例如，增加或减少目标房间等。<br>
     *        + 调用本方法后，可以调用 stopForwardStreamToRooms{@link #IRTCRoom#stopForwardStreamToRooms} 停止向所有房间转发媒体流。<br>
     *        + 调用本方法后，可以调用 pauseForwardStreamToAllRooms{@link #IRTCRoom#pauseForwardStreamToAllRooms} 暂停向所有房间转发媒体流。
     */
    /**
     * @locale en
     * @type api
     * @region Multi-room
     * @brief Start relaying media stream across rooms. <br>
     *        After calling joinRoom{@link #IRTCRoom#joinRoom}, you can call this method to publish the media stream to multiple rooms that applies to scenarios such as anOnline talent contest and so on.
     * @param configuration Information of the rooms where you want to relay the media stream to. Refer to ForwardStreamConfiguration{@link #ForwardStreamConfiguration} for more information.
     * @return  
     *        0: Success<br>
     *        <0: Failure  
     * @note 
     *        + Call this method will trigger onForwardStreamStateChanged{@link #IRTCRoomEventHandler#onForwardStreamStateChanged}.<br>
     *        + After calling this method, listen the events from each room during the relaying by registering onForwardStreamEvent{@link #IRTCRoomEventHandler#onForwardStreamEvent}.<br>
     *        + Once the relaying begins, the other users in the room will receive callback of onUserJoined{@link #IRTCRoomEventHandler#onUserJoined} and onUserPublishStream{@link #IRTCRoomEventHandler#onUserPublishStream}/onUserPublishScreen{@link #IRTCRoomEventHandler#onUserPublishScreen}.<br>
     *        + Call updateForwardStreamToRooms{@link #IRTCRoom#updateForwardStreamToRooms} to add or remove the target room(s) after calling this method.<br>
     *        + Call stopForwardStreamToRooms{@link #IRTCRoom#stopForwardStreamToRooms} to stop relaying to all rooms after calling this method.<br>
     *        + Call pauseForwardStreamToAllRooms{@link #IRTCRoom#pauseForwardStreamToAllRooms} to pause relaying to all rooms after calling this method.
     */
    virtual int startForwardStreamToRooms(const ForwardStreamConfiguration& configuration) = 0;

    /**
     * @locale zh
     * @type api
     * @region 房间管理
     * @brief 更新跨房间媒体流转发信息。<br>
     *        通过 startForwardStreamToRooms{@link #IRTCRoom#startForwardStreamToRooms} 发起媒体流转发后，可调用本方法增加或者减少目标房间，或更新房间密钥。<br>
     *        调用本方法增加或删减房间后，将在本端触发 onForwardStreamStateChanged{@link #IRTCRoomEventHandler#onForwardStreamStateChanged} 回调，包含发生了变动的目标房间中媒体流转发状态。
     * @param configuration 跨房间媒体流转发目标房间信息。参看 ForwardStreamConfiguration{@link #ForwardStreamConfiguration}。
     * @return  
     *        + 0: 方法调用成功  <br>
     *        + <0: 方法调用失败
     * @note 
     *        + 增加目标房间后，新增目标房间中的用户将接收到本地用户进房 onUserJoined{@link #IRTCRoomEventHandler#onUserJoined} 和发布 onUserPublishStream{@link #IRTCRoomEventHandler#onUserPublishStream}/onUserPublishScreen{@link #IRTCRoomEventHandler#onUserPublishScreen} 的回调。<br>
     *        + 删减目标房间后，原目标房间中的用户将接收到本地用户停止发布 onUserUnpublishStream{@link #IRTCRoomEventHandler#onUserUnpublishStream}/onUserUnpublishScreen{@link #IRTCRoomEventHandler#onUserUnpublishScreen} 和退房 onUserLeave{@link #IRTCRoomEventHandler#onUserLeave} 的回调。
     */
    /**
     * @locale en
     * @type api
     * @region Multi-room
     * @brief Update information of the rooms where you want to relay the media stream to after calling startForwardStreamToRooms{@link #IRTCRoom#startForwardStreamToRooms}. <br>
     *        Adding and removing rooms by calling this method will trigger onForwardStreamStateChanged{@link #IRTCRoomEventHandler#onForwardStreamStateChanged} on the local.
     * @param configuration Information of the rooms where you want to relay the media stream to. Refer to ForwardStreamConfiguration{@link #ForwardStreamConfiguration} for more information.
     * @return  
     *         + 0: Success <br>
     *         + <0: Failure
     * @note 
     *        + Users in the room which is added by calling this method will receive onUserJoined{@link #IRTCRoomEventHandler#onUserJoined} and onUserPublishStream{@link #IRTCRoomEventHandler#onUserPublishStream}/onUserPublishScreen{@link #IRTCRoomEventHandler#onUserPublishScreen}.<br>
     *        + Users in the room which is removed by calling this method will receive onUserUnpublishStream{@link #IRTCRoomEventHandler#onUserUnpublishStream}/onUserUnpublishScreen{@link #IRTCRoomEventHandler#onUserUnpublishScreen} and onUserLeave{@link #IRTCRoomEventHandler#onUserLeave}.
     */
    virtual int updateForwardStreamToRooms(const ForwardStreamConfiguration& configuration) = 0;

    /**
     * @locale zh
     * @type api
     * @region 多房间
     * @brief 停止跨房间媒体流转发。<br>
     *        通过 startForwardStreamToRooms{@link #IRTCRoom#startForwardStreamToRooms} 发起媒体流转发后，可调用本方法停止向所有目标房间转发媒体流。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note 
     *        + 调用本方法后，将在本端触发 onForwardStreamStateChanged{@link #IRTCRoomEventHandler#onForwardStreamStateChanged} 回调。<br>
     *        + 调用本方法后，原目标房间中的用户将接收到本地用户停止发布 onUserUnpublishStream{@link #IRTCRoomEventHandler#onUserUnpublishStream}/onUserUnpublishScreen{@link #IRTCRoomEventHandler#onUserUnpublishScreen} 和退房 onUserLeave{@link #IRTCRoomEventHandler#onUserLeave} 的回调。<br>
     *        + 如果需要停止向指定的房间转发媒体流，请调用 updateForwardStreamToRooms{@link #IRTCRoom#updateForwardStreamToRooms} 更新房间信息。<br>
     *        + 如果需要暂停转发，请调用 pauseForwardStreamToAllRooms{@link #IRTCRoom#pauseForwardStreamToAllRooms}，并在之后随时调用 resumeForwardStreamToAllRooms{@link #IRTCRoom#resumeForwardStreamToAllRooms} 快速恢复转发。
     */
    /**
     * @locale en
     * @type api
     * @region Multi-room
     * @brief Call to this method to stop relaying media stream to all rooms after calling startForwardStreamToRooms{@link #IRTCRoom#startForwardStreamToRooms}. 
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note 
     *        + Call this method will trigger onForwardStreamStateChanged{@link #IRTCRoomEventHandler#onForwardStreamStateChanged}.<br>
     *        + The other users in the room will receive callback of onUserJoined{@link #IRTCRoomEventHandler#onUserJoined} and onUserPublishStream{@link #IRTCRoomEventHandler#onUserPublishStream}/onUserPublishScreen{@link #IRTCRoomEventHandler#onUserPublishScreen} when you stop relaying.<br>
     *        + To stop relaying media stream to specific rooms, call updateForwardStreamToRooms{@link #IRTCRoom#updateForwardStreamToRooms} instead.<br>
     *        + To resume the relaying in a short time, call pauseForwardStreamToAllRooms{@link #IRTCRoom#pauseForwardStreamToAllRooms} instead and then call resumeForwardStreamToAllRooms{@link #IRTCRoom#resumeForwardStreamToAllRooms} to recsume after that.
     */
    virtual int stopForwardStreamToRooms() = 0;

    /**
     * @locale zh
     * @type api
     * @region 多房间
     * @brief 暂停跨房间媒体流转发。<br>
     *        通过 startForwardStreamToRooms{@link #IRTCRoom#startForwardStreamToRooms} 发起媒体流转发后，可调用本方法暂停向所有目标房间转发媒体流。<br>
     *        调用本方法暂停向所有目标房间转发后，你可以随时调用 resumeForwardStreamToAllRooms{@link #IRTCRoom#resumeForwardStreamToAllRooms} 快速恢复转发。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note 调用本方法后，目标房间中的用户将接收到本地用户停止发布 onUserUnpublishStream{@link #IRTCRoomEventHandler#onUserUnpublishStream}/onUserUnpublishScreen{@link #IRTCRoomEventHandler#onUserUnpublishScreen} 和退房 onUserLeave{@link #IRTCRoomEventHandler#onUserLeave} 的回调。
     */
     /**
     * @locale en
     * @type api
     * @region Multi-room
     * @brief Call this method to pause relaying media stream to all rooms after calling startForwardStreamToRooms{@link #IRTCRoom#startForwardStreamToRooms}. <br>
     *        After that, call resumeForwardStreamToAllRooms{@link #IRTCRoom#resumeForwardStreamToAllRooms} to resume.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note The other users in the room will receive callback of onUserUnpublishStream{@link #IRTCRoomEventHandler#onUserUnpublishStream}/onUserUnpublishScreen{@link #IRTCRoomEventHandler#onUserUnpublishScreen} and onUserLeave{@link #IRTCRoomEventHandler#onUserLeave} when you pause relaying.
     */
    virtual int pauseForwardStreamToAllRooms() = 0;

    /**
     * @locale zh
     * @type api
     * @region 多房间
     * @brief 恢复跨房间媒体流转发。<br>
     *        调用 pauseForwardStreamToAllRooms{@link #IRTCRoom#pauseForwardStreamToAllRooms} 暂停转发之后，调用本方法恢复向所有目标房间转发媒体流。
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note 
     *        目标房间中的用户将接收到本地用户进房 onUserJoined{@link #IRTCRoomEventHandler#onUserJoined} 和发布 onUserPublishStream{@link #IRTCRoomEventHandler#onUserPublishStream}/onUserPublishScreen{@link #IRTCRoomEventHandler#onUserPublishScreen} 的回调。
     */
    /**
     * @locale en
     * @type api
     * @region Multi-room
     * @brief Call this method to resume relaying to all rooms from the pause by calling pauseForwardStreamToAllRooms{@link #IRTCRoom#pauseForwardStreamToAllRooms}.
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note The other users in the room will receive callback of onUserJoined{@link #IRTCRoomEventHandler#onUserJoined} and onUserPublishStream{@link #IRTCRoomEventHandler#onUserPublishStream}/onUserPublishScreen{@link #IRTCRoomEventHandler#onUserPublishScreen} when you resume relaying.
     */
    virtual int resumeForwardStreamToAllRooms() = 0;

    /**
     * @locale zh
     * @hidden(Linux)
     * @type api
     * @region 范围语音
     * @brief 获取范围语音接口实例。
     * @return 方法调用结果： <br>
     *        + IRangeAudio：成功，返回一个 IRangeAudio{@link #IRangeAudio} 实例。  <br>
     *        + nullptr：失败，当前 SDK 不支持范围语音功能。
     * @note 首次调用该方法须在创建房间后、加入房间前。范围语音相关 API 和调用时序详见[范围语音](https://www.volcengine.com/docs/6348/114727)。
     */
    /**
     * @locale en
     * @hidden(Linux)
     * @type api
     * @region Range Audio
     * @brief Gets range audio instance.
     * @return API call result:  <br>
     *        + IRangeAudio: Success. You will get an IRangeAudio{@link #IRangeAudio} returned from the SDK.  <br>
     *        + nullptr: Failure. The current SDK does not offer range audio function.
     * @note The first time this API is called must be between you create a room and you actually enter the room. Refer to [Range Voice](https://docs.byteplus.com/byteplus-rtc/docs/114727) for more information.
     */
    virtual IRangeAudio* getRangeAudio() = 0;

    /**
     * @locale zh
     * @hidden(Linux)
     * @type api
     * @region 空间音频
     * @brief 获取空间音频接口实例。
     * @return 方法调用结果：  <br>
     *        + ISpatialAudio：成功，返回一个 ISpatialAudio{@link #ISpatialAudio} 实例。  <br>
     *        + nullptr：失败，当前 SDK 不支持空间音频功能。
     * @note  
     *        + 首次调用该方法须在创建房间后、加入房间前。空间音频相关 API 和调用时序详见[空间音频](https://www.volcengine.com/docs/6348/93903)。 <br>
     *        + 只有在使用支持真双声道播放的设备时，才能开启空间音频效果；  <br>
     *        + 机型性能不足可能会导致音频卡顿，使用低端机时，不建议开启空间音频效果；  <br>
     *        + SDK 最多支持 30 个用户同时开启空间音频功能。
     */
    /**
     * @locale en
     * @hidden(Linux)
     * @type api
     * @region Spatial Audio
     * @brief Gets spatial audio instance.   
     * @return API call result:  <br>
     *        + ISpatialAudio: Success. You will get an ISpatialAudio{@link #ISpatialAudio} returned from the SDK.  <br>
     *        + nullptr: Failure. The current SDK does not offer spatial audio function.
     * @note   
     *        + The first time this API is called must be between you create a room and you actually enter the room.  Refer to [Spatial Audio](https://docs.byteplus.com/byteplus-rtc/docs/93903) for more information.<br>
     *        + Only using real dual-channel playback device can you actually enjoy spatial audio effect.  <br>
     *        + Low-end device may have audio stalling issues due to its poor performance, so it is not recommended to enable spatial audio function on such kind of devices. <br>
     *        + SDK currently supports up to 30 users publishing audio with spatial audio enabled at the same time in the same room.
     */
    virtual ISpatialAudio* getSpatialAudio() = 0;
    /**
     * @locale zh
     * @type api
     * @region 多房间
     * @brief 调节某个房间内所有远端用户的音频播放音量。
     * @param volume 音频播放音量值和原始音量的比值，范围是 [0, 400]，单位为 %，自带溢出保护。为保证更好的通话质量，建议将 volume 值设为 [0,100]。 <br>
     *              + 0: 静音  <br>
     *              + 100: 原始音量，默认值  <br>
     *              + 400: 最大可为原始音量的 4 倍(自带溢出保护)  
     * @return  
     *        + 0: 调用成功。<br>
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @note 假设某远端用户 A 始终在被调节的目标用户范围内，<br>
     *        + 当该方法与 setRemoteAudioPlaybackVolume{@link #IRTCVideo#setRemoteAudioPlaybackVolume} 共同使用时，本地收听用户 A 的音量为后调用的方法设置的音量；<br>
     *        + 当该方法与 setPlaybackVolume{@link #IRTCVideo#setPlaybackVolume} 方法共同使用时，本地收听用户 A 的音量将为两次设置的音量效果的叠加。
     */
    /**
     * @locale en
     * @type api
     * @region  multi-room
     * @brief Adjusts the audio playback volume from all the remote users in a room.
     * @param volume Ratio(%) of playback volume to original volume, in the range [0, 400], with overflow protection.  <br>
     *               To ensure the audio quality, we recommend setting the volume to `100`.  <br>
     *               + 0: mute <br>
     *               + 100: original volume. Default value. <br>
     *               + 400: Up to 4 times the original volume (with overflow protection) 
     * @return  
     *        + 0: Success.<br>
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @note Suppose a remote user A is always within the range of the target user whose playback volume will be adjusted,<br>
     *        + If you use both this method and setRemoteAudioPlaybackVolume{@link #IRTCVideo#setRemoteAudioPlaybackVolume}, the volume that the local user hears from user A is the volume set by the method called later.<br>
     *        + If you use both this method and setPlaybackVolume{@link #IRTCVideo#setPlaybackVolume}, the volume that the local user hears from user A is the overlay of both settings.
     */
    virtual int setRemoteRoomAudioPlaybackVolume(int volume) = 0;
    /**
     * @locale zh
     * @hidden for internal use only on Windows and Android
     * @type api
     * @region 视频管理
     * @brief 接收端调用本接口获取全景视频接口引擎。
     * @return 方法调用结果： <br>
     *        + IPanoramicVideo：成功，返回一个 IPanoramicVideo{@link #IPanoramicVideo} 实例。  <br>
     *        + null：失败，当前 SDK 不支持全景视频功能。
     * @note 
     *        + 接收端的调用时序为 createRTCVideo{@link #IRTCVideo#createRTCVideo} >  createRTCRoom{@link #IRTCVideo#createRTCRoom} > 本接口 > joinRoom{@link #IRTCRoom#joinRoom}。<br>
     *        + 获取 IPanoramicVideo 实例后，再调用 updateQuaternionf{@link #IPanoramicVideo#updateQuaternionf} 更新头位姿四元数。<br>
     *        + 你需要使用外部渲染器对接收到的全景视频进行渲染，参见 setRemoteVideoSink{@link #IRTCVideo#setRemoteVideoSink}。
     */
    /**
     * @locale en
     * @hidden for internal use only on Windows and Android
     * @type api
     * @brief Gets panoramic video engine.
     * @return API call result:  <br>
     *        + IPanoramicVideo: Success. You will get an IPanoramicVideo{@link #IPanoramicVideo} returned from the SDK.  <br>
     *        + null: Failure. The current SDK does not offer range audio function.
     * @note 
     *        + The API call sequence on the subscriber side is createRTCVideo{@link #IRTCVideo#createRTCVideo} > createRTCRoom{@link #IRTCVideo#createRTCRoom} > this API > joinRoom{@link #IRTCRoom#joinRoom}.<br>
     *        + After calling this API, you can call updateQuaternionf{@link #IPanoramicVideo#updateQuaternionf} to update the position of the head represented as a quaternion.<br>
     *        + Refer to setRemoteVideoSink{@link #IRTCVideo#setRemoteVideoSink} for details on how to render the panoramic video with an external renderer.
     */
    virtual IPanoramicVideo* getPanoramicVideo() = 0;

    /**
     * @locale zh
     * @valid since 3.52.
     * @type api
     * @region 房间管理
     * @brief 设置本端发布流在音频选路中的优先级。
     * @param audio_selection_priority 本端发布流在音频选路中的优先级，默认正常参与音频选路。参见 AudioSelectionPriority{@link #AudioSelectionPriority}。 
     * @note 
     *       + 在控制台上为本 appId 开启音频选路后，调用本接口才会生效。进房前后调用均可生效。更多信息参见[音频选路](https://www.volcengine.com/docs/6348/113547)。<br>
     *       + 如果本端用户同时加入不同房间，使用本接口进行的设置相互独立。<br>
     * 
     */
    /**
     * @locale en
     * @valid since 3.52.
     * @type api
     * @region Room Management
     * @brief Set the priority of the local audio stream to be published.
     * @param audio_selection_priority The priority of the local audio stream which defaults to be subscribable only up to the result of the Audio Selection. Refer to AudioSelectionPriority{@link #AudioSelectionPriority}.
     * @note 
     *       + You must enable Audio Selection in the RTC console before using this API. You can call this API whether the user has joined a room. Refer to [Audio Selection](https://docs.byteplus.com/byteplus-rtc/docs/113547).<br>
     *       + The setting is independent in each room that the user joins.
     */
    virtual int setAudioSelectionConfig(AudioSelectionPriority audio_selection_priority) = 0;

    /**
     * @locale zh
     * @valid since 3.52.
     * @type api
     * @region 房间管理
     * @brief 设置/更新房间附加信息，可用于标识房间状态或属性，或灵活实现各种业务逻辑。
     * @param key 房间附加信息键值，长度小于 10 字节。<br>
     *        同一房间内最多可存在 5 个 key，超出则会从第一个 key 起进行替换。
     * @param value 房间附加信息内容，长度小于 128 字节。
     * @return  
     *        + 0: 方法调用成功，返回本次调用的任务编号； <br>
     *        + <0: 方法调用失败，具体原因详见 SetRoomExtraInfoResult{@link #SetRoomExtraInfoResult}。  
     * @note  
     *       + 在设置房间附加信息前，必须先调用 joinRoom{@link #IRTCRoom#joinRoom} 加入房间。  <br>
     *       + 调用该方法后，会收到一次 onSetRoomExtraInfoResult{@link #IRTCRoomEventHandler#onSetRoomExtraInfoResult} 回调，提示设置结果。  <br>
     *       + 调用该方法成功设置附加信息后，同一房间内的其他用户会收到关于该信息的回调 onRoomExtraInfoUpdate{@link #IRTCRoomEventHandler#onRoomExtraInfoUpdate}。<br>
     *       + 新进房的用户会收到进房前房间内已有的全部附加信息通知。
     */
    /**
     * @locale en
     * @valid since 3.52.
     * @type api
     * @region Room Management
     * @brief Sets extra information about the room the local user joins.
     * @param key Key of the extra information, less than 10 bytes in length.<br>
     *        A maximum of 5 keys can exist in the same room, beyond which the first key will be replaced.
     * @param value Content of the extra information, less than 128 bytes in length.
     * @return API call result: <br>
     *        + 0: Success with a taskId returned.  <br>
     *        + <0: Failure. See SetRoomExtraInfoResult{@link #SetRoomExtraInfoResult} for the reasons.
     * @note  
     *        + Call joinRoom{@link #IRTCRoom#joinRoom} first before you call this API to set extra information. <br>
     *        + After calling this API, you will receive onSetRoomExtraInfoResult{@link #IRTCRoomEventHandler#onSetRoomExtraInfoResult} callback informing you the result of the setting. <br>
     *        + After the extra information is successfully set, other users in the same room will receive the information through onRoomExtraInfoUpdate{@link #IRTCRoomEventHandler#onRoomExtraInfoUpdate} callback.<br>
     *        + Users who join the room later will be notified of all extra information in the room set prior to entering.
     */
    virtual int64_t setRoomExtraInfo(const char*key,const char*value) = 0;

    /**
     * @locale zh
     * @valid since 3.52
     * @type api
     * @region 字幕翻译服务
     * @brief 识别或翻译房间内所有用户的语音，形成字幕。<br>
     *        调用该方法时，可以在 SubtitleMode{@link #SubtitleMode} 中选择语音识别或翻译模式。如果选择识别模式，语音识别文本会通过 onSubtitleMessageReceived{@link #IRTCRoomEventHandler#onSubtitleMessageReceived} 事件回调给你；<br>
     *        如果选择翻译模式，你会同时收到两个 onSubtitleMessageReceived{@link #IRTCRoomEventHandler#onSubtitleMessageReceived} 回调，分别包含字幕原文及字幕译文。<br>
     *        调用该方法后，用户会收到 onSubtitleStateChanged{@link #IRTCRoomEventHandler#onSubtitleStateChanged} 回调，通知字幕是否开启。
     * @param subtitle_config 字幕配置信息。参看 SubtitleConfig{@link #SubtitleConfig}。
     * @return  
     *        +  0: 调用成功。  <br>
     *        + !0: 调用失败。
     * @note 
     *        + 使用字幕功能前，你需要在 [RTC 控制台](https://console.volcengine.com/rtc/cloudRTC?tab=subtitle) 开启实时字幕功能。<br>
     *        + 如果你需要使用流式语音识别模式，你应在 [语音技术控制台](https://console.volcengine.com/speech/service/16) 创建流式语音识别应用。创建时，服务类型应选择 `流式语音识别`，而非 `音视频字幕生成`。创建后，在 [RTC 控制台](https://console.volcengine.com/rtc/cloudRTC?tab=subtitle) 上启动流式语音识别，并填写创建语音技术应用时获取的相关信息，包括：APP ID，Access Token，和 Cluster ID。<br>
     *        + 如果你需要使用实时语音翻译模式，你应开通机器翻译服务，参考 [开通服务](https://www.volcengine.com/docs/4640/130262)。完成开通后，在 [RTC 控制台](https://console.volcengine.com/rtc/cloudRTC?tab=subtitle) 上启用实时语音翻译模式。<br>
     *        + 此方法需要在进房后调用。  <br>
     *        + 如需指定源语言，你需要在调用 `joinRoom` 接口进房时，通过 extraInfo 参数传入格式为`"语种英文名": "语种代号"` JSON 字符串，例如设置源语言为英文时，传入 `"source_language": "en"`。如未指定源语言，SDK 会将系统语种设定为源语言。如果你的系统语种不是中文、英文和日文，此时 SDK 会自动将中文设为源语言。<br>
     *          + 识别模式下，你可以传入 [RTC 控制台](https://console.volcengine.com/rtc/cloudRTC?tab=subtitle)上预设或自定义的语种英文名和语种代号。识别模式下支持的语言参看[识别模式语种支持](https://www.volcengine.com/docs/6561/109880#%E8%AF%AD%E7%A7%8D%E6%94%AF%E6%8C%81)。<br>
     *          + 翻译模式下，你需要传入机器翻译规定的语种英文名和语种代号。翻译模式下支持的语言及对应的代号参看[翻译模式语言支持](https://www.volcengine.com/docs/4640/35107)。   
     */ 
    /**
     * @locale en
     * @hidden currently not available
     * @type api
     * @region Subtitle translation service
     * @brief Recognizes or translates the speech of all speakers in the room and converts the results into captions. <br>
     *        When calling this method, you can choose the subtitle mode in the SubtitleMode{@link #SubtitleMode}. If you choose the recognition mode, you will receive the onSubtitleMessageReceived{@link #IRTCRoomEventHandler#onSubtitleMessageReceived} callback which contains the transcribed text. <br>
     *        If you choose the translation mode, you will receive two onSubtitleMessageReceived{@link #IRTCRoomEventHandler#onSubtitleMessageReceived} callbacks simultaneously, one contains the transcribed text and the other contains the translated text. <br>
     *        After calling this method, you will receive the onSubtitleStateChanged{@link #IRTCRoomEventHandler#onSubtitleStateChanged} to inform you of whether subtitles are on. 
     * @param subtitle_config Subtitle configurations. Refer to SubtitleConfig{@link #SubtitleConfig} for details. 
     * @return  
     *        +  0: Success.  <br>
     *        + !0: Failure.  
     * @note 
     *        + Call this method after joining the room.  <br>
     *        + You can set your source language to Chinese by calling `joinRoom`  and importing a json formatted string `"source_language": "zh"` through the parameter of extraInfo, to English by importing `"source_language": "en"` , and to Japanese by importing `"source_language": "ja"` . If you don't set the source language, SDK will set the language of your system as the source language. If the language of your system is not Chinese, English or Japanese, SDK will set Chinese as the source language. 
     */
    virtual int startSubtitle(const SubtitleConfig& subtitle_config) = 0;
    /**
     * @locale zh
     * @valid since 3.52
     * @type api
     * @region 字幕翻译服务
     * @brief 关闭字幕。 <br>
     *        调用该方法后，用户会收到 onSubtitleStateChanged{@link #IRTCRoomEventHandler#onSubtitleStateChanged} 回调，通知字幕是否关闭。
     * @return  
     *        +  0: 调用成功。  <br>
     *        + !0: 调用失败。 
     */
    /**
     * @locale en
     * @hidden currently not available
     * @type api
     * @region Subtitle translation service
     * @brief Turns off subtitles. <br>
     *        After calling this method, you will receive the onSubtitleStateChanged{@link #IRTCRoomEventHandler#onSubtitleStateChanged} to inform you of whether subtitles are off. 
     * @return  
     *        +  0: Success.  <br>
     *        + !0: Failure.  
     */
    virtual int stopSubtitle() = 0;
    /**
     * @locale zh
     * @valid since 3.53
     * @type api
     * @brief 获取房间 ID。
     * @return 房间 ID。
     */
    /**
     * @locale en
     * @valid since 3.53
     * @type api
     * @brief Get room ID.
     * @return Room ID.
     */
    virtual const char* getRoomId() = 0;
};

} // namespace bytertc
