/*
 * Copyright (c) 2022 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief RTSRoom
*/

#import <CoreMedia/CMTime.h>
#import "rtc/ByteRTCRtsDefines.h"

@class RTSRoom;

#pragma mark - RTSRoomDelegate
/** 
 * @type callback
 * @brief 语音房间事件回调接口
 */
@protocol RTSRoomDelegate <NSObject>
@optional

#pragma mark - Core Delegate Methods
 /** 
  * @type callback
  * @region 多房间
  * @brief 房间状态改变回调，加入房间、异常退出房间、发生房间相关的警告或错误时会收到此回调。
  * @param rtcRoom rtsRoom 对象。
  * @param roomId 房间 ID。
  * @param uid 用户 ID。
  * @param state 房间状态码。  <br>
  *              + 0: 成功。  <br>
  *              + !0: 失败或异常退出房间，具体原因包括<br>
  *               - -1004：相同 ID 用户在其他端进房； <br>
  *               - -1006：用户被踢出当前房间； <br>
  *               - -1007：无效 roomId； <br>
  *               - -1013：相同 roomId 的房间已存在； <br>
  *               - -2001：初次进房或者由于网络状况不佳断网重连时，由于服务器错误导致进房失败，SDK 会自动重试进房； <br>
  *               - -2016：新生成的房间已经替换了同样roomId的旧房间。
  * @param extraInfo 额外信息。
  *                  `joinType`表示加入房间的类型，`0`为首次进房，`1`为重连进房。
  *                  `elapsed`表示加入房间耗时，即本地用户从调用 joinRoom{@link #RTSRoom#joinRoom} 到加入房间成功所经历的时间间隔，单位为 ms。
  */
 - (void)rtsRoom:(RTSRoom * _Nonnull)rtcRoom onRoomStateChanged:(NSString * _Nonnull)roomId
        withUid:(nonnull NSString *)uid state:(NSInteger)state
       extraInfo:(nonnull NSString *)extraInfo;

/** 
 * @type callback
 * @region 多房间
 * @brief 离开房间成功回调。  <br>
 *        用户调用 leaveRoom{@link #RTSRoom#leaveRoom} 方法后，SDK 会停止房间内消息的收发，并在释放所有相关资源后，通过此回调通知用户离开房间成功。  <br>
 * @param rtsRoom rtsRoom 对象。  <br>
 * @notes 用户调用 leaveRoom{@link #RTSRoom#leaveRoom} 方法离开房间后，如果立即销毁 RTC 引擎，则将无法收到此回调事件。  <br>
 */
- (void)rtsRoomOnLeaveRoom:(RTSRoom *_Nonnull)rtsRoom;

/** 
 * @deprecated since 3.46 and will be deleted in 3.52, use rtsRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #RTSRoomDelegate#rtsRoom:onRoomStateChanged:withUid:state:extraInfo:} instead.
 * @type callback
 * @region 多房间
 * @brief 发生错误回调。  <br>
 *        SDK 运行时出现了错误。SDK 通常无法自动恢复，应用需要采取行动。
 * @param rtcRoom RTSRoom 对象。
 * @param errorCode 错误码，详见枚举类型 ByteRTCErrorCode{@link #ByteRTCErrorCode} 。
 */
- (void)rtsRoom:(RTSRoom * _Nonnull)rtcRoom onRoomError:(ByteRTSErrorCode)errorCode;
/** 
 * @type callback
 * @region 多房间
 * @brief 远端用户首次进房，或断网后重新连入房间时，房间内其他用户将收到该事件。
 * @param rtcRoom RTSRoom 对象。  <br>
 * @param uid 加入房间的用户 ID。  <br>
 * @param elapsed 保留字段，无意义
 */
- (void)rtsRoom:(RTSRoom * _Nonnull)rtcRoom onUserJoined:(NSString * _Nonnull)uid
        elapsed:(NSInteger)elapsed;
/** 
 * @type callback
 * @brief 远端用户离开房间时，本地用户会收到此事件
 * @param rtcRoom RTSRoom 对象。  <br>
 * @param uid 离开房间的远端用户 ID 。  <br>
 * @param reason 用户离开房间的原因，参看 ByteRTCUserOfflineReason{@link #ByteRTCUserOfflineReason}。
 */
- (void)rtsRoom:(RTSRoom * _Nonnull)rtcRoom onUserLeave:(NSString * _Nonnull)uid
         reason:(ByteRTCUserOfflineReason)reason;

#pragma mark - Message Delegate Methods
 /** 
  * @type callback
  * @region 多房间
  * @brief 收到房间中调用 sendRoomMessage:{@link #RTSRoom#sendRoomMessage:} 发送的广播文本消息时，收到此回调。
  * @param rtcRoom RTSRoom 对象
  * @param uid 消息发送者 ID 。
  * @param message 收到的文本消息内容。
  */
 - (void)rtsRoom:(RTSRoom * _Nonnull)rtcRoom onRoomMessageReceived:(NSString * _Nonnull)uid
        message:(NSString * _Nonnull)message;
 /** 
  * @type callback
  * @region 多房间
  * @brief 收到房间中调用 sendRoomBinaryMessage:{@link #RTSRoom#sendRoomBinaryMessage:} 发送的广播二进制消息时，收到此回调。
  * @param rtcRoom RTSRoom 对象
  * @param uid 消息发送者 ID 。
  * @param message 收到的二进制消息内容。
  */
 - (void)rtsRoom:(RTSRoom * _Nonnull)rtcRoom onRoomBinaryMessageReceived:(NSString * _Nonnull)uid
        message:(NSData * _Nonnull)message;
 /** 
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
 - (void)rtsRoom:(RTSRoom * _Nonnull)rtcRoom onRoomMessageSendResult:(int64_t)msgid
          error:(ByteRTCRoomMessageSendResult)error;

@end

#pragma mark - RTSRoom
/**
 * @type api
 */
BYTERTC_APPLE_EXPORT @interface RTSRoom : NSObject

@property(nonatomic, weak) id<RTSRoomDelegate> _Nullable delegate;

#pragma mark - Core Methods
/** 
 * @type api
 * @region 多房间
 * @brief 退出并销毁调用 createRoom:{@link #RTS#createRoom:} 所创建的房间实例。
 */
- (void)destroy;
/** 
 * @deprecated since 3.46 and will be deleted in 3.52.
 * @type api
 * @region 多房间
 * @brief 获取房间 ID
 */
- (NSString *_Nullable)getRoomId;
/** 
 * @type api
 * @region 多房间
 * @brief 通过设置 RTSRoomDelegate{@link #RTSRoomDelegate} 代理，可以监听此 `RTSRoom` 对象对应的回调事件。
 * @param roomDelegate 参见 RTSRoomDelegate{@link #RTSRoomDelegate}。
 */
- (void)setRTSRoomDelegate:(id<RTSRoomDelegate> _Nullable)roomDelegate;

/** 
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
 *        + 用户加入房间成功后，在本地网络状况不佳的情况下，SDK 可能会与服务器失去连接，此时 SDK 将会自动重连。重连成功后，本地会收到 rtsRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #RTSRoomDelegate#rtsRoom:onRoomStateChanged:withUid:state:extraInfo:} 回调通知。如果加入房间的用户可见，远端用户会收到 rtcRoom:onUserJoined:elapsed:{@link #ByteRTCAudioRoomDelegate#rtcRoom:onUserJoined:elapsed:}。
 */
- (int)joinRoom;

/** 
 * @type api
 * @region 房间管理
 * @brief 离开房间。 <br>
 *        用户调用此方法离开房间，结束实时消息通信，释放所有通信相关的资源。
 * @return 方法调用结果。 <br>
 *        + 0: 方法调用成功 <br>
 *        + < 0: 方法调用失败 <br>
 * @notes <br>
 *       + 可见的用户离开房间后，房间内其他用户会收到 rtcRoom:onUserLeave:reason:{@link #RTSRoomDelegate#rtsRoom:onUserLeave:reason:} 回调通知；  <br>
 *       + 此方法是异步操作，调用返回时并没有真正退出房间。真正退出房间后，本地会收到 rtsRoomOnLeaveRoom:{@link #RTSRoomDelegate#rtsRoomOnLeaveRoom:} 回调通知。  <br>
 *       + 如果调用此方法后立即销毁引擎，SDK 将无法触发 rtsRoomOnLeaveRoom:{@link #RTSRoomDelegate#rtsRoomOnLeaveRoom:} 回调
 */
 - (int)leaveRoom;

#pragma mark - Message Methods

 /** 
  * @type api
  * @region 多房间
  * @brief 给房间内的所有其他用户发送文本消息。
  * @param message  <br>
  *        发送的文本消息内容。  <br>
  *        消息不超过 64KB。
  * @return 这次发送消息的编号，从 1 开始递增。
  * @notes  <br>
  *      + 在发送房间内文本消息前，必须先调用 joinRoom{@link #RTSRoom#joinRoom} 加入房间。  <br>
  *      + 调用该函数后会收到一次 rtcRoom:onRoomMessageSendResult:error:{@link #RTSRoomDelegate#rtsRoom:onRoomMessageSendResult:error:} 回调，通知消息发送方发送成功或失败；  <br>
  *      + 若文本消息发送成功，则房间内远端用户会收到 rtcRoom:onRoomMessageReceived:message:{@link #RTSRoomDelegate#rtsRoom:onRoomMessageReceived:message:} 回调。
  */
 - (int64_t)sendRoomMessage:(NSString * _Nonnull)message;
 /** 
  * @type api
  * @region 多房间
  * @brief 给房间内的所有其他用户发送二进制消息。
  * @param message  <br>
  *        用户发送的二进制广播消息  <br>
  *        消息不超过 46KB。
  * @return 这次发送消息的编号，从 1 开始递增。
  * @notes  <br>
  *      + 在房间内广播二进制消息前，必须先调用 joinRoom{@link #RTSRoom#joinRoom} 加入房间。  <br>
  *      + 调用该函数后会收到一次 rtcRoom:onRoomMessageSendResult:error:{@link #RTSRoomDelegate#rtsRoom:onRoomMessageSendResult:error:} 回调，通知消息发送方发送成功或失败；  <br>
  *      + 若二进制消息发送成功，则房间内所有用户会收到 rtcRoom:onRoomBinaryMessageReceived:message:{@link #RTSRoomDelegate#rtsRoom:onRoomBinaryMessageReceived:message:} 回调。
  */
 - (int64_t)sendRoomBinaryMessage:(NSData *  _Nonnull)message;

@end
