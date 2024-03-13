/*
 * Copyright (c) 2022 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC Room Interface
 */

#pragma once

#include "rtc/bytertc_rts_defines.h"
#include "byterts_room_event_handler.h"

namespace bytertc {

/** {zh}
 * @type api
 * @brief 房间接口
 */
/** {en}
 * @type api
 * @brief  Room interface
 */
class IRTSRoom {
public:
    /** {zh}
     * @hidden constructor/destructor
     * @brief 析构函数
     */
    /** {en}
     * @hidden constructor/destructor
     * @brief  Destructor
     */
    virtual ~IRTSRoom() {
    }

    /** {zh}
     * @type api
     * @region 多房间
     * @brief 退出并销毁调用 createRoom{@link #IRTS#createRoom} 所创建的房间实例。
     */
    /** {en}
     * @type api
     * @region  multi-room
     * @brief  Leave and destroy the room instance created by calling createRoom{@link #IRTS#createRoom}.
     */
    virtual void destroy() = 0;

    /** {zh}
     * @type api
     * @region 多房间
     * @brief 创建/加入房间：房间不存在时即创建房间；房间存在时，未加入房间的用户可加入这个房间。  <br>
     *        同一房间内的用户间可以相互通话。  <br>
     *        进房后重复调用无效，用户必须调用 `leaveRoom` 退出当前房间后，才能加入下一个房间。
     * @return  <br>
     *        +  0: 成功  <br>
     *        + -1：room_id / user_info.uid 包含了无效的参数。  <br>
     *        + -2：已经在房间内。
     * @notes  <br>
     *       + 同一个 App ID 的同一个房间内，每个用户的用户 ID 必须是唯一的。如果两个用户的用户 ID 相同，则后进房的用户会将先进房的用户踢出房间，并且先进房的用户会收到 OnError{@link #IRTCAudioEventHandler#OnError} 回调通知，错误类型详见 ErrorCode{@link #ErrorCode} 中的 kErrorCodeDuplicateLogin。  <br>
     *       + 本地用户调用此方法加入房间成功后，会收到 onRoomStateChanged{@link #IRTSRoomEventHandler#onRoomStateChanged} 回调通知。  <br>
     *       + 用户加入房间成功后，在本地网络状况不佳的情况下，SDK 可能会与服务器失去连接，此时 SDK 将会自动重连。重连成功后，本地会收到 onRoomStateChanged{@link #IRTSRoomEventHandler#onRoomStateChanged} 回调通知。如果加入房间的用户可见，远端用户会收到 onUserJoined{@link #IRTSRoomEventHandler#onUserJoined}。
     */
    /** {en}
     * @type api
     * @region Multi-room
     * @brief Create/join a room: create a room when the room does not exist; when the room exists, users who have not joined the room can join the room.   <br>
     *        Users in the same room can talk to each other. <br>
     *         Repeated calls after entering the room are invalid. The user must call `leaveRoom` to exit the current room before joining the next room.
     * @return   <br>
     *         + 0: Success <br>
     *         + -1: Room_id/user_info.uid contains invalid parameters. <br>
     *         + -2: Already in the room. 
     * @notes   <br>
     *        + In the same room with the same App ID, the user ID of each user must be unique. If two users have the same user ID, the user who entered the room later will kick the user who entered the room out of the room, and the user who entered the room will receive the OnError{@link #IRTCAudioEventHandler#OnError} callback notification. For the error type. See kErrorCodeDuplicateLogin in ErrorCode{@link #ErrorCode}. <br>
     *        + Local users will receive onRoomStateChanged{@link #IRTSRoomEventHandler#onRoomStateChanged} callback notification after calling this method to join the room successfully. <br>
     *        + After the user successfully joins the room, the SDK may lose connection to the server in case of poor local network conditions, and the SDK will automatically reconnect at this time. After a successful reconnection, you will receive a local onRoomStateChanged{@link #IRTSRoomEventHandler#onRoomStateChanged} callback notification. If the user is set to visiable, the remote user will receive onUserJoined{@link #IRTSRoomEventHandler#onUserJoined} callback notification. 
     */
    virtual int joinRoom() = 0;

    /** {zh}
     * @type api
     * @region 多房间
     * @brief 离开房间。  <br>
     *        用户调用此方法离开房间，结束通话过程，释放所有通话相关的资源。  <br>
     * @return  <br>
     *        + 0: 调用成功。
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @notes  <br>
     *       + 此方法是异步操作，调用返回时并没有真正退出房间。真正退出房间后，本地会收到 onLeaveRoom{@link #IRTSRoomEventHandler#onLeaveRoom} 回调通知。  <br>
     *       + 可见的用户离开房间后，房间内其他用户会收到 onUserLeave{@link #IRTSRoomEventHandler#onUserLeave} 回调通知。  <br>
     *       + 如果调用此方法后立即销毁引擎，SDK 将无法触发 onLeaveRoom{@link #IRTSRoomEventHandler#onLeaveRoom} 回调。  <br>
     *       + 调用 joinRoom{@link #IRTSRoom#joinRoom} 方法加入房间后，必须调用此方法离开房间，否则无法进入下一个房间。无论当前是否在房间内，都可以调用此方法。重复调用此方法没有负面影响。  <br>
     */
    /** {en}
     * @type api
     * @region Multiple rooms
     * @brief Leave the room.   <br>
     *        The user calls this method to leave the room, end the call process, and release all call-related resources. <br>
     * @return  <br>
     *        + 0: Success.
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     * @notes   <br>
     *        + This method is an asynchronous operation and does not really exit the room when the call returns. After you actually exit the room, you will receive a callback notification from onLeaveRoom{@link #IRTSRoomEventHandler#onLeaveRoom} locally. <br>
     *        + After the visible user leaves the room, other users in the room will receive an onUserLeave{@link #IRTSRoomEventHandler#onUserLeave} callback notification. <br>
     *        + If the engine is destroyed immediately after this method is called, the SDK will not be able to trigger the onLeaveRoom{@link #IRTSRoomEventHandler#onLeaveRoom} callback. <br>
     *        + After calling the joinRoom{@link #IRTSRoom#joinRoom} method to join the room, you must call this method to leave the room, otherwise you cannot enter the next room. This method can be called regardless of whether it is currently in the room. Repeated calls to this method have no negative impact. <br>
     */
    virtual int leaveRoom() = 0;

    /** {zh}
     * @type api
     * @region 多房间
     * @brief 设置 IRTSRoom{@link #IRTSRoom} 对象的事件句柄。
     *        通过设置事件句柄可以监听此 IRTSRoom{@link #IRTSRoom} 对象对应的房间的回调事件。
     * @param [in] room_event_handler 回调处理器，详见 IRTSRoomEventHandler{@link #IRTSRoomEventHandler}
     * @return  <br>
     *        + 0: 调用成功。
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     */
    /** {en}
     * @type api
     * @region multiroom
     * @brief Set the event handle of the IRTSRoom{@link #IRTSRoom} object.
     *         You can listen for callback events for the room corresponding to this IRTSRoom{@link #IRTSRoom} object by setting the event handle.
     * @param  [in] room_event_handler Callback processor. See IRTSRoomEventHandler{@link #IRTSRoomEventHandler}.
     * @return  <br>
     *        + 0: Success.
     *        + < 0 : Fail. See ReturnStatus{@link #ReturnStatus} for more details
     */
    virtual int setRTSRoomEventHandler(IRTSRoomEventHandler* room_event_handler) = 0;

    /** {zh}
     * @type api
     * @region 多房间
     * @brief 给房间内的所有其他用户发送广播消息。
     * @param [in] message  <br>
     *        用户发送的广播消息  <br>
     *        消息不超过 62KB。
     * @return 这次发送消息的编号，从 1 开始递增。
     * @notes  <br>
     *       + 在发送房间内二进制消息前，必须先调用 joinRoom{@link #IRTSRoom#joinRoom} 加入房间。  <br>
     *       + 调用该函数后，会收到一次 onRoomMessageSendResult{@link #IRTSRoomEventHandler#onRoomMessageSendResult} 回调。  <br>
     *       + 同一房间内的其他用户会收到 onRoomMessageReceived{@link #IRTSRoomEventHandler#onRoomMessageReceived} 回调。
     */
    /** {en}
     * @type api
     * @region Multi-room
     * @brief Send broadcast messages to all other users in the room.
     * @param  [in] message <br>
     *        The broadcast message sent by the user <br>
     *        Message does not exceed 62KB.
     * @return The number of the message sent this time is incremented from 1.
     * @notes   <br>
     *        + Before sending in-room binary messages, you must call joinRoom{@link #IRTSRoom#joinRoom} to join the room. <br>
     *        + After calling this function, you get an onRoomMessageSendResult{@link #IRTSRoomEventHandler#onRoomMessageSendResult} callback. <br>
     *        + Other users in the same room receive an onRoomMessageReceived{@link #IRTSRoomEventHandler#onRoomMessageReceived} callback.
     */
    virtual int64_t sendRoomMessage(const char* message) = 0;
    /** {zh}
     * @type api
     * @region 多房间
     * @brief 给房间内的所有其他用户发送广播消息。
     * @param [in] size  <br>
     *        发送的二进制消息长度
     * @param [in] message  <br>
     *        用户发送的二进制广播消息  <br>
     *        消息不超过 46KB。
     * @return 这次发送消息的编号，从 1 开始递增。
     * @notes  <br>
     *       + 在发送房间内二进制消息前，必须先调用 joinRoom{@link #IRTSRoom#joinRoom} 加入房间。  <br>
     *       + 调用该函数后，会收到一次 onRoomMessageSendResult{@link #IRTSRoomEventHandler#onRoomMessageSendResult} 回调。  <br>
     *       + 同一房间内的其他用户会收到 onRoomBinaryMessageReceived{@link #IRTSRoomEventHandler#onRoomBinaryMessageReceived} 回调。
     */
    /** {en}
     * @type api
     * @region Multi-room
     * @brief Send broadcast messages to all other users in the room.
     * @param  [in] size <br>
     *        The length of the binary message sent
     * @param  [in] message <br>
     *        The binary broadcast message sent by the user <br>
     *        The message does not exceed 46KB.
     * @return The number of the message sent this time is incremented from 1.
     * @notes   <br>
     *        + Before sending in-room binary messages, you must call joinRoom{@link #IRTSRoom#joinRoom} to join the room. <br>
     *        + After calling this function, you get an onRoomMessageSendResult{@link #IRTSRoomEventHandler#onRoomMessageSendResult} callback. <br>
     *        + Other users in the same room receive an onRoomBinaryMessageReceived{@link #IRTSRoomEventHandler#onRoomBinaryMessageReceived} callback.
     */
    virtual int64_t sendRoomBinaryMessage(int size, const uint8_t* message) = 0;
};

}  // namespace bytertc
