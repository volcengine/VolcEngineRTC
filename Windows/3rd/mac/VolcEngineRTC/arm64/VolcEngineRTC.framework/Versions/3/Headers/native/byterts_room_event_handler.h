/*
 * Copyright (c) 2022 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC Room Event Handler Interface
*/

#pragma once

namespace bytertc {
/** {zh}
 * @type callback
 * @brief 实时信令事件回调接口
 */
/** {en}
 * @type callback
 * @brief  Audio & video room event callback interface
 */
class IRTSRoomEventHandler {
public:
    /** {zh}
     * @hidden constructor/destructor
     * @brief 析构函数
     */
    /** {en}
     * @hidden constructor/destructor
     * @brief Destructor
     */
    virtual ~IRTSRoomEventHandler() {}

    /** {zh}
     * @type callback
     * @region 多房间
     * @brief 房间状态改变回调，加入房间、异常退出房间、发生房间相关的警告或错误时会收到此回调。
     * @param [in] room_id 房间 ID。
     * @param [in] uid 用户 ID。
     * @param [in] state 房间状态码。  <br>
     *              + 0: 加入房间成功。  <br>
     *              + !0: 加入房间失败、异常退房、发生房间相关的警告或错误。具体原因参看 ErrorCode{@link #ErrorCode} 及 WarningCode{@link #WarningCode}。
     * @param [in] extra_info 额外信息，如 `{"elapsed":1187,"join_type":0}`。
     *                  `join_type`表示加入房间的类型，`0`为首次进房，`1`为重连进房。
     *                  `elapsed`表示加入房间耗时，即本地用户从调用 joinRoom{@link #IRTSRoom#joinRoom} 到加入房间成功所经历的时间间隔，单位为 ms。
     */
    /** {en}
     * @type callback
     * @region Multi-room
     * @brief Callback on room state changes. Via this callback you get notified of room relating warnings,  errors and events. For example, the user joins the room, the user is removed from the room, and so on.
     * @param [in] room_id  Room ID.
     * @param [in] uid  User ID.
     * @param [in] state Room state code. <br>
     *              + 0: Join room success. <br>
     *              + !0: Failed to join a room, abnormal exit, room-related warnings or errors. See ErrorCode{@link #ErrorCode} and WarningCode{@link #WarningCode} for specific indications.
     * @param [in] extra_info Extra information.
     *                 `join_type` indicates the type of room the user joins. `0` means the user joins the room for the first time, and `1` means the user rejoins the room. <br>
     *                 `elapsed` indicates the time interval from calling joinRoom{@link #IRTSRoom#joinRoom} to successfully joining room, in ms.
     */
    virtual void onRoomStateChanged(const char* room_id, const char* uid,
            int state, const char* extra_info) {
        (void)room_id;
        (void)state;
        (void)extra_info;
    }

    /** {zh}
     * @type callback
     * @region 房间管理
     * @brief 离开房间回调。  <br>
     *        用户调用 leaveRoom{@link #IRTSRoom#leaveRoom} 方法后，SDK 会停止所有的发布订阅流，并在释放所有与通话相关的音频资源后，通过此回调通知用户离开房间成功。  <br>
     * @notes  <br>
     *       + 用户调用 leaveRoom{@link #IRTSRoom#leaveRoom} 方法离开房间后，如果立即调用 destroy{@link #IRTSRoom#destroy} 销毁房间实例或 destroyRTS{@link #destroyRTS} 方法销毁 RTS 引擎，则将无法收到此回调事件。  <br>
     *       + 离开房间后，如果 App 需要使用系统音频设备，则建议收到此回调后再初始化音频设备，否则可能由于 SDK 占用音频设备而导致初始化失败。  <br>
     */
    /** {en}
     * @type callback
     * @region Room management
     * @brief Leave the room callback.   <br>
     *        After the user calls the leaveRoom{@link #IRTSRoom#leaveRoom} method, the SDK stops all publishing subscription streams and notifies the user to leave the room successfully through this callback after releasing all audio & video resources related to the call. <br>
     * @notes   <br>
     *        + After the user calls the leaveRoom{@link #IRTSRoom#leaveRoom} method to leave the room, if destroy{@link #IRTSRoom#destroy} is called to destroy the room instance or destroyRTS{@link #destroyRTS} method is called to destroy the RTS engine immediately, this callback event will not be received. <br>
     *        + If the app needs to use the system audio & video device after leaving the room, it is recommended to initialize the audio & video device after receiving this callback, otherwise the initialization may fail due to the SDK occupying the audio & video device. <br>
     */
    virtual void onLeaveRoom() {
    }

    /** {zh}
     * @deprecated since 3.41 and will be deleted in 3.51, user onRoomStateChanged{@link #IRTSRoomEventHandler#onRoomStateChanged} instead.
     * @type callback
     * @region 房间管理
     * @brief SDK 发生警告回调。  <br>
     *        SDK 内部遇到可恢复错误时，在尝试自动恢复的同时，会通过此回调通知用户。此回调事件仅用作通知。  <br>
     * @param [in] warn 警告码，参看 WarningCode{@link #WarningCode}。  <br>
     */
    /** {en}
     * @deprecated since 3.45 and will be deleted in 3.51, use onRoomStateChanged{@link #IRTSRoomEventHandler#onRoomStateChanged} instead.
     * @type callback
     * @region Room Management
     * @brief SDK Warning callback occurred. When a recoverable error is encountered inside the <br>
     *        SDK, the user is notified via this callback while attempting automatic recovery. This callback event is only used as a notification. <br>
     * @param  [in] warn Code. See WarningCode{@link #WarningCode}. <br>
     */
    virtual void onRoomWarning(int warn) {
        (void)warn;
    }

    /** {zh}
     * @deprecated since 3.41 and will be deleted in 3.51, use onRoomStateChanged{@link #IRTSRoomEventHandler#onRoomStateChanged} instead.
     * @type callback
     * @region 房间管理
     * @brief SDK 发生错误回调。  <br>
     *        SDK 内部遇到不可恢复错误时，会通过此回调通知 App，需要 App 根据错误码进行操作或提示用户。  <br>
     * @param [in] err 错误码，参看 ErrorCode{@link #ErrorCode}。  <br>
     */
    /** {en}
     * @deprecated since 3.45 and will be deleted in 3.51, use onRoomStateChanged{@link #IRTSRoomEventHandler#onRoomStateChanged} instead.
     * @type callback
     * @region Room management
     * @brief SDK Error callback occurred. <br>
     *        SDK internal encountered an unrecoverable error, will notify the App through this callback, requires the App to operate according to the error code or prompt the user. <br>
     * @param  [in] err Error code. See ErrorCode{@link #ErrorCode}. <br>
     */
    virtual void onRoomError(int err) {
        (void)err;
    }

    /** {zh}
     * @type callback
     * @region 房间管理
     * @brief 远端用户加入房间的回调。
     * @param [in] uid 加入房间的用户 ID  <br>
     * @param [in] elapsed 此参数无意义
     */
    /** {en}
     * @type callback
     * @region Room management
     * @brief Callback about remote users joining the room.
     * @param [in] uid ID of the remote user who enters the room. <br>
     * @param [in] elapsed This parameter is meaningless.
     */
    virtual void onUserJoined(const char* uid, int elapsed) {
        (void)uid;
        (void)elapsed;
    }

    /** {zh}
     * @type callback
     * @brief 远端用户离开房间时，本地用户会收到此事件
     * @param [in] uid 离开房间的远端用户 ID。  <br>
     * @param [in] reason 用户离开房间的原因。参看 UserOfflineReason{@link #UserOfflineReason}。
     */
    /** {en}
     * @type callback
     * @brief This callback is triggered when a remote user is disconnected.
     * @param [in] uid ID of the user who leaves the room. <br>
     * @param [in] reason Reason to leave the room. See UserOfflineReason{@link #UserOfflineReason}.
     */
    virtual void onUserLeave(const char* uid, UserOfflineReason reason) {
        (void)uid;
        (void)reason;
    }

    /** {zh}
     * @type callback
     * @region 实时消息通信
     * @brief 接收到房间内广播消息的回调。
     * @param [in] uid  <br>
     *        消息发送者 ID
     * @param [in] message  <br>
     *        收到的消息内容
     * @notes 同一房间内其他用户调用 sendRoomMessage{@link #IRTSRoom#sendRoomMessage} 发送广播消息时会收到该回调。
     */
    /** {en}
     * @type callback
     * @region Real-time messaging
     * @brief Receives a callback for broadcast messages in the room.
     * @param  [in] uid <br>
     *         User ID of the message sender
     * @param  [in] message <br>
     *         Received message content
     * @notes Other users in the same room will receive this callback when they call sendRoomMessage{@link #IRTSRoom#sendRoomMessage} to send a broadcast message.
     */
    virtual void onRoomMessageReceived(const char* uid, const char* message) {
        (void)uid;
        (void)message;
    }

    /** {zh}
     * @type callback
     * @region 实时消息通信
     * @brief 接收到房间内二进制广播消息的回调。
     * @param [in] uid  <br>
     *        消息发送者 ID
     * @param [in] size <br>
     *        收到的二进制消息长度
     * @param [in] message <br>
     *        收到的二进制消息内容
     * @notes 同一房间内其他用户调用 sendRoomBinaryMessage{@link #IRTSRoom#sendRoomBinaryMessage} 发送二进制广播消息时会收到该回调。
     */
    /** {en}
     * @type callback
     * @region Real-time messaging
     * @brief Receives a callback to a binary broadcast message in the room.
     * @param  [in] uid <br>
     *         User ID of the message sender
     * @param  [in] size <br>
     *         Binary message length received
     * @param  [in] message <br>
     *        Binary message content received
     * @notes Other users in the same room call sendRoomBinaryMessage{@link #IRTSRoom#sendRoomBinaryMessage} Receive this callback when sending a binary broadcast message.
     */
    virtual void onRoomBinaryMessageReceived(const char* uid, int size, const uint8_t* message) {
        (void)uid;
        (void)size;
        (void)message;
    }

    /** {zh}
     * @type callback
     * @region 实时消息通信
     * @brief 当调用 sendRoomMessage{@link #IRTSRoom#sendRoomMessage} 函数发送消息后，回调此条消息的发送结果（反馈）。
     * @param [in] msgid  <br>
     *        本条消息的 ID
     * @param [in] error  <br>
     *        消息发送结果  <br>
     *        详见 RoomMessageSendResult{@link #RoomMessageSendResult}
     */
    /** {en}
     * @type callback
     * @region Real-time messaging
     * @brief When the sendRoomMessage{@link #IRTSRoom#sendRoomMessage} function is called to send a message, the sending result of this message (feedback) is called back.
     * @param [in] msgid <br>
     *         ID of this message
     * @param [in] error <br>
     *         Message sending result <br>
     *         See RoomMessageSendResult{@link #RoomMessageSendResult}
     */
    virtual void onRoomMessageSendResult(int64_t msgid, int error) {
        (void)msgid;
        (void)error;
    }
};

}  // namespace bytertc

