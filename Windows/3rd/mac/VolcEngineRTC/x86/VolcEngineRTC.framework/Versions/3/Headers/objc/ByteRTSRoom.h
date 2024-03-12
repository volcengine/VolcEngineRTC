/*
 * Copyright (c) 2022 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief RTSRoom
*/

#import <CoreMedia/CMTime.h>
#import "rtc/ByteRTCRtsDefines.h"

@class RTSRoom;

#pragma mark - RTSRoomDelegate
/** {zh}
 * @type callback
 * @brief 语音房间事件回调接口
 */
/** {en}
 * @type callback
 * @brief Audio room event callback interface
 */
@protocol RTSRoomDelegate <NSObject>
@optional

#pragma mark - Core Delegate Methods
 /** {zh}
  * @type callback
  * @region 多房间
  * @brief 房间状态改变回调，加入房间、异常退出房间、发生房间相关的警告或错误时会收到此回调。
  * @param roomId 房间 ID。
  * @param uid 用户 ID。
  * @param state 房间状态码。  <br>
  *              + 0: 加入房间成功。  <br>
  *              + !0: 加入房间失败、异常退房、发生房间相关的警告或错误。
  * @param extraInfo 额外信息，如 `{"elapsed":1187,"join_type":0}`。
  *                  `join_type`表示加入房间的类型，`0`为首次进房，`1`为重连进房。
  *                  `elapsed`表示加入房间耗时，即本地用户从调用 joinRoom{@link #RTSRoom#joinRoom} 到加入房间成功所经历的时间间隔，单位为 ms。
  */
 /** {en}
  * @type callback
  * @region Multi-room
  * @brief Callback on room state changes. Via this callback you get notified of room relating warnings,  errors and events. For example, the user joins the room, the user is removed from the room, and so on.
  * @param roomId  Room ID.
  * @param uid  User ID.
  * @param state Room state code. <br>
  *              + 0: Join room success. <br>
  *              + !0: Failed to join a room, abnormal exit, room-related warnings or errors.
  * @param extraInfo Extra information.
  *                 `join_type` indicates the type of room the user joins. `0` means the user joins the room for the first time, and `1` means the user rejoins the room. <br>
  *                 `elapsed` indicates the time interval from calling joinRoom{@link #RTSRoom#joinRoom} to successfully joining room, in ms.
  */
- (void)rtsRoom:(RTSRoom * _Nonnull)rtcRoom onRoomStateChanged:(NSString * _Nonnull)roomId
        withUid:(nonnull NSString *)uid state:(NSInteger)state
       extraInfo:(nonnull NSString *)extraInfo;

/** {zh}
 * @type callback
 * @region 多房间
 * @brief 离开房间成功回调。  <br>
 *        用户调用 leaveRoom{@link #RTSRoom#leaveRoom} 方法后，SDK 会停止房间内消息的收发，并在释放所有相关资源后，通过此回调通知用户离开房间成功。  <br>
 * @param rtsRoom rtsRoom 对象。  <br>
 * @notes
 *       + 用户调用 leaveRoom{@link #RTSRoom#leaveRoom} 方法离开房间后，如果立即调用 destroy{@link #RTSRoom#destroy} 销毁房间实例或 destroyRTS{@link #RTS#destroyRTS} 方法销毁 RTS 引擎，则将无法收到此回调事件。  <br>
 *       + 离开房间结束通话后，如果 App 需要使用系统音视频设备，则建议在收到此回调后再初始化音视频设备，否则可能由于 SDK 占用了导致 App 初始化音视频设备失败。  <br>
 */
/** {en}
 * @type callback
 * @region Multiple rooms
 * @brief Leave the room successfully callback.   <br>
 *        After the user call leaveRoom{@link #RTSRoom#leaveRoom}, the SDK will stop sending/receiving broadcast messages in the room and, after releasing all relevant resources, notify the user via this callback that leaving the room was successful.<br>
 * @param rtsRoom rtsRoom object. <br>
 * @notes
 *        + After the user calls the leaveRoom{@link #RTSRoom#leaveRoom} method to leave the room, if destroy{@link #RTSRoom#destroy} is called to destroy the room instance or destroyRTS{@link #RTS#destroyRTS} method is called to destroy the RTS engine immediately, this callback event will not be received. <br>
 *        + If the app needs to use the system audio & video device after leaving the room, it is recommended to initialize the audio & video device after receiving this callback, otherwise the initialization may fail due to the SDK occupying the audio & video device. <br>
 */
 - (void)rtsRoomOnLeaveRoom:(RTSRoom *_Nonnull)rtsRoom;

/** {zh}
 * @hidden
 * @deprecated since 3.46 and will be deleted in 3.52, use rtsRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #RTSRoomDelegate#rtsRoom:onRoomStateChanged:withUid:state:extraInfo:} instead.
 * @type callback
 * @region 多房间
 * @brief 发生错误回调。  <br>
 *        SDK 运行时出现了错误。SDK 通常无法自动恢复，应用需要采取行动。
 * @param rtcRoom RTSRoom 对象。
 * @param errorCode 错误码，详见枚举类型 ByteRTCErrorCode{@link #ByteRTCErrorCode} 。
 */
/** {en}
 * @hidden
 * @deprecated since 3.46 and will be deleted in 3.52, use rtsRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #RTSRoomDelegate#rtsRoom:onRoomStateChanged:withUid:state:extraInfo:} instead.
 * @type callback
 * @region Multiple rooms
 * @brief Error callback occurred.   <br>
 *        An error occurred during the SDK runtime. The SDK usually does not recover automatically, and the app needs to take action.
 * @param rtcRoom RTSRoom object.
 * @param errorCode Error code. See enumeration type ByteRTCErrorCode{@link #ByteRTCErrorCode}.
 */
- (void)rtsRoom:(RTSRoom * _Nonnull)rtcRoom onRoomError:(ByteRTSErrorCode)errorCode __deprecated_msg("Will be removed in new version");
/** {zh}
 * @type callback
 * @region 多房间
 * @brief 远端用户首次进房，或断网后重新连入房间时，房间内其他用户将收到该事件。
 * @param rtcRoom RTSRoom 对象。  <br>
 * @param uid 加入房间的用户 ID。  <br>
 * @param elapsed 保留字段，无意义
 */
/** {en}
 * @type callback
 * @region Multi-room
 * @brief When the remote user enters the room for the first time, or reconnects to the room after being disconnected, the other users in the room will receive this callback.
 * @param rtcRoom RTSRoom object. <br>
 * @param uid ID of the remote user who enters the room.
 * @param elapsed Reserved field, meaningless
 */
- (void)rtsRoom:(RTSRoom * _Nonnull)rtcRoom onUserJoined:(NSString * _Nonnull)uid
        elapsed:(NSInteger)elapsed;
/** {zh}
 * @type callback
 * @brief 远端用户离开房间时，本地用户会收到此事件
 * @param rtcRoom RTSRoom 对象。  <br>
 * @param uid 离开房间的远端用户 ID 。  <br>
 * @param reason 用户离开房间的原因，参看 ByteRTCUserOfflineReason{@link #ByteRTCUserOfflineReason}。
 */
/** {en}
 * @type callback
 * @brief This callback is triggered when a remote user is disconnected or turns invisible.
 * @param rtcRoom RTSRoom object. <br>
 * @param uid ID of the user who leaves the room, or switches to invisible. <br>
 * @param reason Reason to leave the room. See ByteRTCUserOfflineReason{@link #ByteRTCUserOfflineReason}.
 */
- (void)rtsRoom:(RTSRoom * _Nonnull)rtcRoom onUserLeave:(NSString * _Nonnull)uid
         reason:(ByteRTCUserOfflineReason)reason;

#pragma mark - Message Delegate Methods
 /** {zh}
  * @type callback
  * @region 多房间
  * @brief 收到房间中调用 sendRoomMessage:{@link #RTSRoom#sendRoomMessage:} 发送的广播文本消息时，收到此回调。
  * @param rtcRoom RTSRoom 对象
  * @param uid 消息发送者 ID 。
  * @param message 收到的文本消息内容。
  */
 /** {en}
  * @type callback
  * @region Multi-room
  * @brief Receive this callback when you receive a broadcast text message from the room called sendRoomMessage:{@link #RTSRoom#sendRoomMessage:}.
  * @param rtcRoom RTSRoom object
  * @param uid Message sender ID.
  * @param message The content of the received text message.
  */
- (void)rtsRoom:(RTSRoom * _Nonnull)rtcRoom onRoomMessageReceived:(NSString * _Nonnull)uid
        message:(NSString * _Nonnull)message;
 /** {zh}
  * @type callback
  * @region 多房间
  * @brief 收到房间中调用 sendRoomBinaryMessage:{@link #RTSRoom#sendRoomBinaryMessage:} 发送的广播二进制消息时，收到此回调。
  * @param rtcRoom RTSRoom 对象
  * @param uid 消息发送者 ID 。
  * @param message 收到的二进制消息内容。
  */
 /** {en}
  * @type callback
  * @region Multi-room
  * @brief Receive this callback when you receive a broadcast binary message sent by the room call sendRoomBinaryMessage:{@link #RTSRoom#sendRoomBinaryMessage:}.
  * @param rtcRoom RTSRoom object
  * @param uid Message sender ID.
  * @param message The binary message content received.
  */
- (void)rtsRoom:(RTSRoom * _Nonnull)rtcRoom onRoomBinaryMessageReceived:(NSString * _Nonnull)uid
        message:(NSData * _Nonnull)message;
 /** {zh}
  * @type callback
  * @region 多房间
  * @brief 向房间内所有用户群发文本或二进制消息后，消息发送方会收到该消息发送结果回调。
  * @param rtcRoom RTSRoom 对象。
  * @param msgid 本条消息的 ID。
  * @param error 消息发送结果，详见 ByteRTCRoomMessageSendResult{@link #ByteRTCRoomMessageSendResult}
  * @notes  <br>
  *        + 你应调用 sendRoomMessage:{@link #RTSRoom#sendRoomMessage:} 向房间内群发文本消息 <br>
  *        + 你应调用 sendRoomBinaryMessage:{@link #RTSRoom#sendRoomBinaryMessage:} 向房间内群发二进制消息
  */
 /** {en}
  * @type callback
  * @region Multi-room
  * @brief After sending a text or binary message to all users in the room, the message sender will receive a callback with the result of the message.
  * @param rtcRoom RTSRoom object.
  * @param msgid The ID of this message.
  * @param error  Message sending results. See ByteRTCRoomMessageSendResult{@link #ByteRTCRoomMessageSendResult}
  * @notes   <br>
  *         + You should call sendRoomMessage:{@link #RTSRoom#sendRoomMessage:} Send a mass text message to the room <br>
  *         + You should call sendRoomBinaryMessage:{@link #RTSRoom#sendRoomBinaryMessage:} Send a mass binary message to the room
  */
- (void)rtsRoom:(RTSRoom * _Nonnull)rtcRoom onRoomMessageSendResult:(int64_t)msgid
          error:(ByteRTCRoomMessageSendResult)error;

@end

#pragma mark - RTSRoom
/**
 * @type api
 */
BYTERTC_APPLE_EXPORT @interface RTSRoom : NSObject
/**
 * @type callback
 */
@property(nonatomic, weak) id<RTSRoomDelegate> _Nullable delegate;

#pragma mark - Core Methods
/** {zh}
 * @type api
 * @region 多房间
 * @brief 退出并销毁调用 createRoom:{@link #RTS#createRoom:} 所创建的房间实例。
 */
/** {en}
 * @type api
 * @region multi-room
 * @brief Leaves and destroy the room instance created by calling createRoom:{@link #RTS#createRoom:}.
 */
- (void)destroy;
/** {zh}
 * @hidden
 * @deprecated since 3.46 and will be deleted in 3.52.
 * @type api
 * @region 多房间
 * @brief 获取房间 ID
 */
/** {en}
 * @hidden
 * @deprecated since 3.46 and will be deleted in 3.52.
 * @type api
 * @region multiple rooms
 * @brief Get room ID
 */
- (NSString *_Nullable)getRoomId __deprecated_msg("Will be removed in new version");
/** {zh}
 * @type api
 * @region 多房间
 * @brief 通过设置 RTSRoomDelegate{@link #RTSRoomDelegate} 代理，可以监听此 `RTSRoom` 对象对应的回调事件。
 * @param roomDelegate 参见 RTSRoomDelegate{@link #RTSRoomDelegate}。
 * @return  <br>
 *        + 0: 调用成功。
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 */
/** {en}
 * @type api
 * @region Multi-room
 * @brief By setting RTSRoomDelegate{@link #RTSRoomDelegate}, you can get infromed of events realted to this `RTSRoom` object.
 * @param roomDelegate Refer to RTSRoomDelegate{@link #RTSRoomDelegate}.
 * @return  <br>
 *        + 0: Success.
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 */
- (int)setRTSRoomDelegate:(id<RTSRoomDelegate> _Nullable)roomDelegate;

/** {zh}
 * @type api
 * @region 多房间
 * @brief 加入房间。<br>
 *        调用 createRoom:{@link #RTS#createRoom:} 创建房间后，可调用该方法进房，在房间内收发广播消息。
 * @return 方法调用结果：  <br>
 *        +  0: 成功  <br>
 *        + -2: 已经在房间内。接口调用成功后，只要收到返回值为 0 ，且未调用 leaveRoom{@link #RTSRoom#leaveRoom} 成功，则再次调用进房接口时，无论填写的房间 ID 和用户 ID 是否重复，均触发此返回值。  <br>
 *        + -3: room 为空 <br>
 * @notes  <br>
 *        + 你需在调用 login:uid:{@link #RTS#login:uid:} 登陆 RTS 服务器后再加入房间。  <br>
 *        + 本地用户调用此方法加入房间成功后，会收到 rtsRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #RTSRoomDelegate#rtsRoom:onRoomStateChanged:withUid:state:extraInfo:} 回调通知。  <br>
 *        + 用户加入房间成功后，在本地网络状况不佳的情况下，SDK 可能会与服务器失去连接，此时 SDK 将会自动重连。重连成功后，本地会收到 rtsRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #RTSRoomDelegate#rtsRoom:onRoomStateChanged:withUid:state:extraInfo:} 回调通知。如果加入房间的用户可见，远端用户会收到 rtsRoom:onUserJoined:elapsed:{@link #RTSRoomDelegate#rtsRoom:onUserJoined:elapsed:}。
 */
/** {en}
 * @type api
 * @region Multiple rooms
 * @brief Join the room. <br>
 *         After calling createRoom{@link #RTS#createRoom} to create an RTS room, you can call this API to enter the room and send/receive broadcast messages in the room.
 * @return  Method call result:  <br>
 *         + 0: Success <br>
 *         + -2: Already in the room. <br>
 *         + -3: No room is created.
 * @notes   <br>
 *         + You should first call login{@link #RTS#login} to log in to the RTS system and then join the room. <br>
 *         + Local users will receive rtsRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #RTSRoomDelegate#rtsRoom:onRoomStateChanged:withUid:state:extraInfo:} callback notification after calling this method to join the room successfully. <br>
 *         + After the user successfully joins the room, the SDK may lose connection to the server in case of poor local network conditions, and the SDK will automatically reconnect at this time. After successful reconnection, you will receive a callback notification from rtsRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #RTSRoomDelegate#rtsRoom:onRoomStateChanged:withUid:state:extraInfo:} locally. If the user is set to visiable, the remote user will receive rtsRoom:onUserJoined:elapsed:{@link #RTSRoomDelegate#rtsRoom:onUserJoined:elapsed:} callback notification. 
 */
- (int)joinRoom;

/** {zh}
 * @type api
 * @region 房间管理
 * @brief 离开房间。 <br>
 *        用户调用此方法离开房间，结束实时消息通信，释放所有通信相关的资源。
 * @return 方法调用结果。 <br>
 *        + 0: 方法调用成功 <br>
 *        + < 0: 方法调用失败 <br>
 * @notes <br>
 *       + 可见的用户离开房间后，房间内其他用户会收到 rtsRoom:onUserLeave:reason:{@link #RTSRoomDelegate#rtsRoom:onUserLeave:reason:} 回调通知；  <br>
 *       + 此方法是异步操作，调用返回时并没有真正退出房间。真正退出房间后，本地会收到 rtsRoomOnLeaveRoom:{@link #RTSRoomDelegate#rtsRoomOnLeaveRoom:} 回调通知。  <br>
 *       + 如果调用此方法后立即销毁引擎，SDK 将无法触发 rtsRoomOnLeaveRoom:{@link #RTSRoomDelegate#rtsRoomOnLeaveRoom:} 回调
 */
 /** {en}
  * @type api
  * @region  room management
  * @brief Leave RTC room.   <br>
  *        The user calls this method to leave the room, ending real-time message communication and releasing all communication-related resources. <br>
  * @return   <br>
  *         + 0: Success <br>
  *         + < 0: Failure <br>
  * @notes   <br>
  *        + When a visible user leaves the room, others in the room will receive rtsRoom:onUserLeave:reason:{@link #RTSRoomDelegate#rtsRoom:onUserLeave:reason:}. <br>
  *        + This method is an asynchronous operation, and the call returns without actually exiting the room. After you actually exit the room, you will receive a callback notification from rtsRoomOnLeaveRoom:{@link #RTSRoomDelegate#rtsRoomOnLeaveRoom:} locally. <br>
  *        + If the engine is destroyed immediately after this method is called, the SDK will not be able to trigger the rtsRoomOnLeaveRoom:{@link #RTSRoomDelegate#rtsRoomOnLeaveRoom:} callback. <br>
  */
- (int)leaveRoom;

#pragma mark - Message Methods

 /** {zh}
  * @type api
  * @region 多房间
  * @brief 给房间内的所有其他用户发送文本消息。
  * @param message  <br>
  *        发送的文本消息内容。  <br>
  *        消息不超过 64KB。
  * @return 这次发送消息的编号，从 1 开始递增。
  * @notes  <br>
  *      + 在发送房间内文本消息前，必须先调用 joinRoom{@link #RTSRoom#joinRoom} 加入房间。  <br>
  *      + 调用该函数后会收到一次 rtsRoom:onRoomMessageSendResult:error:{@link #RTSRoomDelegate#rtsRoom:onRoomMessageSendResult:error:} 回调，通知消息发送方发送成功或失败；  <br>
  *      + 若文本消息发送成功，则房间内远端用户会收到 rtsRoom:onRoomMessageReceived:message:{@link #RTSRoomDelegate#rtsRoom:onRoomMessageReceived:message:} 回调。
  */
 /** {en}
  * @type api
  * @region Multi-room
  * @brief Send text messages to all other users in the room.
  * @param message   <br>
  *        The content of the text message sent. <br>
  *         Message does not exceed 62KB.
  * @return The number of the message sent this time is incremented from 1.
  * @notes   <br>
  *       + Before sending an in-room text message, you must call joinRoom{@link #RTSRoom#joinRoom} to join the room. <br>
  *       + After calling this function, you will receive an rtsRoom:onRoomMessageSendResult:error:{@link #RTSRoomDelegate#rtsRoom:onRoomMessageSendResult:error:} callback to notify the sender of the success or failure of the message; <br>
  *       + If the text message is sent successfully, all remote users in the room will receive rtsRoom:onRoomMessageReceived:message:{@link #RTSRoomDelegate#rtsRoom:onRoomMessageReceived:message:} callback.
  */
- (int64_t)sendRoomMessage:(NSString * _Nonnull)message;
 /** {zh}
  * @type api
  * @region 多房间
  * @brief 给房间内的所有其他用户发送二进制消息。
  * @param message  <br>
  *        用户发送的二进制广播消息  <br>
  *        消息不超过 46KB。
  * @return 这次发送消息的编号，从 1 开始递增。
  * @notes  <br>
  *      + 在房间内广播二进制消息前，必须先调用 joinRoom{@link #RTSRoom#joinRoom} 加入房间。  <br>
  *      + 调用该函数后会收到一次 rtsRoom:onRoomMessageSendResult:error:{@link #RTSRoomDelegate#rtsRoom:onRoomMessageSendResult:error:} 回调，通知消息发送方发送成功或失败；  <br>
  *      + 若二进制消息发送成功，则房间内所有用户会收到 rtsRoom:onRoomBinaryMessageReceived:message:{@link #RTSRoomDelegate#rtsRoom:onRoomBinaryMessageReceived:message:} 回调。
  */
 /** {en}
  * @type api
  * @region multiroom
  * @brief Sends binary messages to all other users in the room.
  * @param message   <br>
  *        The binary broadcast message sent by the user <br>
  *        The message does not exceed 46KB.
  * @return The number of the message sent this time is incremented from 1.
  * @notes   <br>
  *       + Before broadcasting binary messages in the room, you must call joinRoom{@link #RTSRoom#joinRoom} to join the room. <br>
  *       + After calling this function, you will receive an rtsRoom:onRoomMessageSendResult:error:{@link #RTSRoomDelegate#rtsRoom:onRoomMessageSendResult:error:} callback to notify the sender of the success or failure of the message; <br>
  *       + If the binary message is successfully sent, all users in the room will receive rtsRoom:onRoomBinaryMessageReceived:message:{@link #RTSRoomDelegate#rtsRoom:onRoomBinaryMessageReceived:message:} callback.
  */
- (int64_t)sendRoomBinaryMessage:(NSData *  _Nonnull)message;

@end
