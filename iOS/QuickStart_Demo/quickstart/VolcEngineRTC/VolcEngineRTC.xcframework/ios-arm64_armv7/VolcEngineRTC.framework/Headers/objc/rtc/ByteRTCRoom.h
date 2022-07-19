/*
 * Copyright (c) 2020 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC Room
*/

#import <CoreMedia/CMTime.h>
#import "ByteRTCDefines.h"
#import "ByteRTCRangeAudio.h"
#import "ByteRTCSpatialAudio.h"

@class RTCRoom;

/** 
 * @type callback
 * @brief 房间事件回调接口
 */
@protocol RTCRoomDelegate <NSObject>
@optional

 /** 
  * @type callback
  * @region 多房间
  * @author shenpengliang
  * @brief 房间状态改变回调，加入房间、离开房间、发生房间相关的警告或错误时会收到此回调。
  * @param roomId 房间 ID。
  * @param uid 用户 ID。
  * @param state 房间状态码。  <br>
  *              + 0: 成功。  <br>
  *              + !0: 失败，具体原因参看 ByteRTCErrorCode{@link #ByteRTCErrorCode} 及 ByteRTCWarningCode{@link #ByteRTCWarningCode}。
  * @param extraInfo 额外信息。
  *                  `joinType`表示加入房间的类型，`0`为首次进房，`1`为重连进房。
  *                  `elapsed`表示加入房间耗时，即本地用户从调用 joinRoomByToken:userInfo:roomConfig:{@link #RTCRoom#joinRoomByToken:userInfo:roomConfig:} 到加入房间成功所经历的时间间隔，单位为 ms。
  */
 - (void)rtcRoom:(RTCRoom *_Nonnull)rtcRoom
    onRoomStateChanged:(NSString *_Nonnull)roomId
             withUid:(nonnull NSString *)uid
           state:(NSInteger)state
           extraInfo:(NSString *_Nonnull)extraInfo;

/** 
 * @type callback
 * @region 多房间
 * @author shenpengliang
 * @brief 流状态改变回调，发生流相关的警告或错误时会收到此回调。
 * @param roomId 房间 ID。
 * @param uid 用户 ID。
 * @param state 流状态码，参看 ByteRTCErrorCode{@link #ByteRTCErrorCode} 及 ByteRTCWarningCode{@link #ByteRTCWarningCode}。
 * @param extraInfo 附加信息，目前为空。
 */
- (void)rtcRoom:(RTCRoom *_Nonnull)rtcRoom
   onStreamStateChanged:(NSString *_Nonnull)roomId
            withUid:(nonnull NSString *)uid
          state:(NSInteger)state
          extraInfo:(NSString *_Nonnull)extraInfo;

/** 
 * @hidden
 * @type callback
 * @region 多房间
 * @author shenpengliang
 * @brief 离开房间成功回调。  <br>
 *        用户调用 leaveRoom{@link #RTCRoom#leaveRoom} 方法后，SDK 会停止所有的发布订阅流，并释放所有通话相关的音视频资源。SDK 完成所有的资源释放后通过此回调通知用户。  <br>
 * @param rtcRoom  RTCRoom 对象。  <br>
 * @param stats 本次通话的统计数据，详见数据结构 ByteRTCRoomStats{@link #ByteRTCRoomStats} 。  <br>
 * @notes  <br>
 *       + 用户调用 leaveRoom{@link #RTCRoom#leaveRoom} 方法离开房间后，如果立即调用 destroyEngine{@link #destroyEngine} 方法销毁 RTC 引擎，则将无法收到此回调事件。  <br>
 *       + 离开房间结束通话后，如果 App 需要使用系统音视频设备，则建议在收到此回调后再初始化音视频设备，否则可能由于 SDK 占用了导致 App 初始化音视频设备失败。  <br>
 */
- (void)rtcRoom:( RTCRoom *_Nonnull)rtcRoom onLeaveRoomWithStats:(ByteRTCRoomStats *_Nonnull)stats;

 /** 
  * @hidden
  * @deprecated since 341.1 by onRoomStateChanged and onStreamStateChanged
  * @type callback
  * @region 多房间
  * @author shenpengliang
  * @brief 发生警告回调。  <br>
  *        SDK 运行时出现了警告。SDK 通常会自动恢复，警告信息可以忽略。
  * @param rtcRoom RTCRoom 对象。
  * @param warningCode 警告码，详见枚举类型 ByteRTCWarningCode{@link #ByteRTCWarningCode} 。
  */
 - (void)rtcRoom:( RTCRoom *_Nonnull)rtcRoom onRoomWarning:(ByteRTCWarningCode)warningCode;

/** 
 * @hidden
 * @deprecated since 341.1 by onRoomStateChanged and onStreamStateChanged
 * @type callback
 * @region 多房间
 * @author shenpengliang
 * @brief 发生错误回调。  <br>
 *        SDK 运行时出现了错误。SDK 通常无法自动恢复，应用需要采取行动。
 * @param rtcRoom  RTCRoom 对象。
 * @param errorCode 错误码，详见枚举类型 ByteRTCErrorCode{@link #ByteRTCErrorCode} 。
 */
- (void)rtcRoom:( RTCRoom *_Nonnull)rtcRoom onRoomError:(ByteRTCErrorCode)errorCode;

/** 
 * @type callback
 * @region 多房间
 * @brief 发布端调用 setMultiDeviceAVSync:{@link #RTCRoom#setMultiDeviceAVSync:} 后音视频同步状态发生改变时，会收到此回调。
 * @param rtcRoom ByteRTCRoom 实例
 * @param state 音视频同步状态，参看 ByteRTCAVSyncState{@link #ByteRTCAVSyncState}。
 */
- (void)rtcRoom:( RTCRoom *_Nonnull)rtcRoom onAVSyncStateChange:(ByteRTCAVSyncState)state;

/** 
 * @type callback
 * @region 多房间
 * @author liuzhiqiang.avcoder
 * @brief 房间内通话统计信息回调。   <br>
 *        用户进房开始通话后，每 2s 收到一次本回调。
 * @param rtcRoom  RTCRoom 对象。
 * @param stats 当前 RTCRoom 统计数据，详见：ByteRTCRoomStats{@link #ByteRTCRoomStats}
 */
- (void)rtcRoom:( RTCRoom *_Nonnull)rtcRoom onRoomStats:(ByteRTCRoomStats *_Nonnull)stats;

/** 
 * @type callback
 * @region 多房间
 * @author liuzhiqiang.avcoder
 * @brief 本地流数据统计以及网络质量回调。  <br>
 *        本地用户发布流成功后，SDK 会周期性（2s）的通过此回调事件通知用户发布的流在此次统计周期内的质量统计信息。  <br>
 *        统计信息通过 ByteRTCLocalStreamStats{@link #ByteRTCLocalStreamStats} 类型的回调参数传递给用户，其中包括发送音视频比特率、发送帧率、编码帧率，网络质量等。  <br>
 * @param rtcRoom  RTCRoom 对象。  <br>
 * @param stats  当前房间本地流数据统计。详见：ByteRTCLocalStreamStats{@link #ByteRTCLocalStreamStats} <br>
 */
- (void)rtcRoom:( RTCRoom *_Nonnull)rtcRoom onLocalStreamStats:(ByteRTCLocalStreamStats *_Nonnull)stats;

/** 
 * @type callback
 * @region 多房间
 * @author liuzhiqiang.avcoder
 * @brief 本地订阅的远端音/视频流数据统计以及网络质量回调。  <br>
 *        本地用户订阅流成功后，SDK 会周期性（2s）的通过此回调事件通知用户订阅的流在此次统计周期内的质量统计信息，包括：发送音视频比特率、发送帧率、编码帧率，网络质量等。
 * @param rtcRoom  RTCRoom 对象。
 * @param stats  当前房间本地流数据统计。 详见：ByteRTCRemoteStreamStats{@link #ByteRTCRemoteStreamStats}
 */
- (void)rtcRoom:( RTCRoom *_Nonnull)rtcRoom onRemoteStreamStats:(ByteRTCRemoteStreamStats *_Nonnull)stats;

/** 
 * @type callback
 * @region 多房间
 * @author shenpengliang
 * @brief 远端可见用户加入房间，或房内隐身用户切换为可见的回调。<br>
 *        1. 远端用户调用 setUserVisibility:{@link #RTCRoom#setUserVisibility:} 方法将自身设为可见后加入房间时，房间内其他用户将收到该事件。  <br>
 *        2. 远端可见用户断网后重新连入房间时，房间内其他用户将收到该事件。  <br>
 *        3. 房间内隐身远端用户调用 setUserVisibility:{@link #RTCRoom#setUserVisibility:} 方法切换至可见时，房间内其他用户将收到该事件。  <br>
 *        4. 新进房用户会收到进房前已在房内的主播角色用户的进房回调通知。  <br>
 * @param rtcRoom RTCRoom 对象。  <br>
 * @param userInfo 用户信息，参看 ByteRTCUserInfo{@link #ByteRTCUserInfo}。  <br>
 * @param elapsed 保留字段，无意义
 */
- (void)rtcRoom:( RTCRoom *_Nonnull)rtcRoom onUserJoined:(ByteRTCUserInfo *_Nonnull)userInfo elapsed:(NSInteger)elapsed;

    /** 
     * @type callback
     * @author shenpengliang
     * @brief 远端用户离开房间，或切至不可见时，本地用户会收到此事件
     * @param uid 离开房间，或切至不可见的的远端用户 ID。  <br>
     * @param reason 用户离开房间的原因：  <br>
     *              + 0: 远端用户调用 leaveRoom{@link #RTCRoom#leaveRoom} 主动退出房间。  <br>
     *              + 1: 远端用户因 Token 过期或网络原因等掉线。 <br>
     *              + 2: 远端用户调用 setUserVisibility:{@link #RTCRoom#setUserVisibility:} 切换至不可见状态。 <br>
     *              + 3: 服务端调用 OpenAPI 将远端用户踢出房间。
     */
    - (void)rtcRoom:( RTCRoom *_Nonnull)rtcRoom onUserLeave:(NSString *_Nonnull)uid reason:(ByteRTCUserOfflineReason)reason;
    /** 
     * @type callback
     * @brief Token 过期前 30 秒将触发该回调。<br>
     *        调用 updateToken:{@link #ByteRTCEngineKit#updateToken:} 更新 Token。否则 Token 过期后，用户将被移出房间无法继续进行音视频通话。
     */
     - (void)onTokenWillExpire:( RTCRoom *_Nonnull)rtcRoom;

/** 
 * @hidden
 * @type callback
 * @region 多房间
 * @author shenpengliang
 * @brief 当房间内用户调用 MuteAllRemoteAudio{@link #MuteAllRemoteAudio}，
 *        改变接收所有远端音频流的状态时, 房间内其他用户收到这个回调。
 * @param rtcRoom  RTCRoom 对象。  <br>
 * @param uid 改变接收状态的用户 ID
 * @param muteState 接收状态，详见：ByteRTCMuteState{@link #ByteRTCMuteState}
 */
- (void)rtcRoom:( RTCRoom *_Nonnull)rtcRoom onMuteAllRemoteAudio:(NSString *_Nonnull)uid muteState:(ByteRTCMuteState)muteState;

/** 
 * @hidden
 * @type callback
 * @region 多房间
 * @brief 房间内用户暂停/恢复接收所有视频流时，房间内其他用户收到此回调。参看 MuteAllRemoteVideo{@link #MuteAllRemoteVideo}。
 * @param rtcRoom  RTCRoom 对象。  <br>
 * @param uid 暂停/恢复接收视频流的用户 ID。
 * @param muteState 暂停/恢复接收视频流。参看 ByteRTCMuteState{@link #ByteRTCMuteState}。
 */
- (void)rtcRoom:( RTCRoom *_Nonnull)rtcRoom onMuteAllRemoteVideo:(NSString *_Nonnull)uid withMuteState:(ByteRTCMuteState)muteState;

 /** 
  * @hidden
  * @deprecated since 336.1, use onUserPublishStream and onUserPublishScreen instead.
  * @type callback
  * @region 多房间
  * @author shenpengliang
  * @brief 以下情况会触发此回调：<br>
  *        + 房间内的用户发布新的音视频流时，房间内的其他用户会收到此回调通知。  <br>
  *        + 房间内的用户原音视频流被移出后，又重新发布音视频流时，房间内的其他用户会收到此回调通知。  <br>
  *        + 用户刚加入房间时，会收到此回调，包含房间中所有已发布的流。
  * @param rtcRoom  RTCRoom 对象。  <br>
  * @param stream 流属性，参看 ByteRTCStream{@link #ByteRTCStream} 。  <br>
  */
 - (void)rtcRoom:( RTCRoom *_Nonnull)rtcRoom onStreamAdd:(id<ByteRTCStream> _Nonnull)stream;

 /** 
  * @hidden
  * @deprecated since 336.1, use onUserUnPublishStream and onUserUnPublishScreen instead.
  * @type callback
  * @region 多房间
  * @author shenpengliang
  * @brief 房间内的远端用户停止发布音视频流时，本地用户会收到此回调通知。  <br>
  * @param rtcRoom RTCRoom 对象
  * @param uid 远端流来源的用户 ID 。  <br>
  * @param stream 流的属性，参看 ByteRTCStream{@link #ByteRTCStream}。  <br>
  * @param reason 远端流移除的原因，参看 ByteRTCStreamRemoveReason{@link #ByteRTCStreamRemoveReason} 。  <br>
  */
 - (void)rtcRoom:( RTCRoom *_Nonnull)rtcRoom
    didStreamRemoved:(NSString *_Nonnull)uid
              stream:(id<ByteRTCStream> _Nonnull)stream
              reason:(ByteRTCStreamRemoveReason)reason;
/** 
 * @type callback
 * @region 房间管理
 * @author shenpengliang
 * @brief 房间内新增远端摄像头/麦克风采集的媒体流流的回调。
 * @param rtcRoom RTCRoom 实例
 * @param userId 远端流发布用户的用户 ID。
 * @param type 远端媒体流的类型，参看 ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}。
 * @notes 当房间内的远端用户调用 publishStream:{@link #RTCRoom#publishStream:} 成功发布由摄像头/麦克风采集的媒体流时，本地用户会收到该回调，此时本地用户可以自行选择是否调用 subscribeStream:mediaStreamType:{@link #RTCRoom#subscribeStream:mediaStreamType:} 订阅此流。
 */
- (void)rtcRoom:( RTCRoom * _Nonnull)rtcRoom onUserPublishStream:(NSString *_Nonnull)userId            type:(ByteRTCMediaStreamType)type;
/** 
 * @type callback
 * @region 房间管理
 * @author shenpengliang
 * @brief 房间内远端摄像头/麦克风采集的媒体流移除的回调。
 * @param rtcRoom RTCRoom 实例
 * @param userId 移除的远端流发布用户的用户 ID。  <br>
 * @param type 移除的远端流类型，参看 ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}。  <br>
 * @param reason 远端流移除的原因，参看 ByteRTCStreamRemoveReason{@link #ByteRTCStreamRemoveReason}。
 * @notes 收到该回调通知后，你可以自行选择是否调用 unSubscribeStream:mediaStreamType:{@link #RTCRoom#unSubscribeStream:mediaStreamType:} 取消订阅此流。
 */
- (void)rtcRoom:( RTCRoom * _Nonnull)rtcRoom onUserUnPublishStream:(NSString *_Nonnull)userId            type:(ByteRTCMediaStreamType)type
           reason:(ByteRTCStreamRemoveReason)reason;
/** 
 * @type callback
 * @region 房间管理
 * @author shenpengliang
 * @brief 房间内新增远端屏幕共享音视频流的回调。
 * @param rtcRoom ByteRTCRoom实例
 * @param userId 远端流发布用户的用户 ID。
 * @param type 远端媒体流的类型，参看 ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}。
 * @notes 当房间内的远端用户调用 publishScreen:{@link #RTCRoom#publishScreen:} 成功发布来自屏幕共享的音视频流时，本地用户会收到该回调，此时本地用户可以自行选择是否调用 subscribeScreen:mediaStreamType:{@link #RTCRoom#subscribeScreen:mediaStreamType:} 订阅此流。
 */
- (void)rtcRoom:( RTCRoom * _Nonnull)rtcRoom onUserPublishScreen:(NSString *_Nonnull)userId   type:(ByteRTCMediaStreamType)type;
/** 
 * @type callback
 * @region 房间管理
 * @author shenpengliang
 * @brief 房间内远端屏幕共享音视频流移除的回调。
 * @param rtcRoom RTCRoom 实例
 * @param userId 移除的远端流发布用户的用户 ID。  <br>
 * @param type 移除的远端流类型，参看 ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}。  <br>
 * @param reason 远端流移除的原因，参看 ByteRTCStreamRemoveReason{@link #ByteRTCStreamRemoveReason}。
 * @notes 收到该回调通知后，你可以自行选择是否调用 unSubscribeScreen:mediaStreamType:{@link #RTCRoom#unSubscribeScreen:mediaStreamType:} 取消订阅此流。
 */
- (void)rtcRoom:( RTCRoom * _Nonnull)rtcRoom onUserUnPublishScreen:(NSString *_Nonnull)userId type:(ByteRTCMediaStreamType)type
           reason:(ByteRTCStreamRemoveReason)reason;
/** 
 * @type callback
 * @region 房间管理
 * @author shenpengliang
 * @brief 关于订阅媒体流状态改变的回调
 * @param rtcRoom RTCRoom 对象
 * @param state 订阅媒体流状态，参看 ByteRTCSubscribeState{@link #ByteRTCSubscribeState}
 * @param userId 流发布用户的用户 ID
 * @param info 流的属性，参看 ByteRTCSubscribeConfig{@link #ByteRTCSubscribeConfig}
 * @notes 本地用户收到该回调的时机包括：  <br>
 *        + 调用 subscribeStream:mediaStreamType:{@link #RTCRoom#subscribeStream:mediaStreamType:} 或 unSubscribeStream:mediaStreamType:{@link #RTCRoom#unSubscribeStream:mediaStreamType:} 订阅/取消订阅指定远端摄像头音视频流后；  <br>
 *        + 调用 subscribeScreen:mediaStreamType:{@link #RTCRoom#subscribeScreen:mediaStreamType:} 或 unSubscribeScreen:mediaStreamType:{@link #RTCRoom#unSubscribeScreen:mediaStreamType:} 订阅/取消订阅指定远端屏幕共享流后。
 */
- (void)rtcRoom:( RTCRoom *_Nonnull)rtcRoom
    onStreamSubscribed:(ByteRTCSubscribeState)state
                userId:(NSString *_Nonnull)userId
       subscribeConfig:(ByteRTCSubscribeConfig *_Nonnull)info;

/** 
 * @hidden
 * @type callback
 * @region 多房间
 * @author shenpengliang
 * @brief 当发布流成功的时候回调该事件
 * @param rtcRoom  RTCRoom 对象。  <br>
 * @param userId 用户ID
 * @param isScreen 该流是否是屏幕流
 *
 */
- (void)rtcRoom:( RTCRoom *_Nonnull)rtcRoom onStreamPublishSuccess:(NSString *_Nonnull)userId isScreen:(BOOL)isScreen;

 /** 
  * @type callback
  * @region 多房间
  * @author hanchenchen.c
  * @brief 收到房间中调用 sendRoomMessage:{@link #ByteRTCEngineKit#sendRoomMessage:} 发送的广播文本消息时，收到此回调。
  * @param rtcRoom RTCRoom 对象
  * @param uid 消息发送者 ID 。
  * @param message 收到的文本消息内容。
  */
 - (void)rtcRoom:( RTCRoom *_Nonnull)rtcRoom onRoomMessageReceived:(NSString *_Nonnull)uid
        message:(NSString *_Nonnull)message;

 /** 
  * @type callback
  * @region 多房间
  * @author hanchenchen.c
  * @brief 收到房间中调用 sendRoomBinaryMessage:{@link #RTCRoom#sendRoomBinaryMessage:} 发送的广播二进制消息时，收到此回调。
  * @param rtcRoom RTCRoom 对象
  * @param uid 消息发送者 ID 。
  * @param message 收到的二进制消息内容。
  */
 - (void)rtcRoom:( RTCRoom *_Nonnull)rtcRoom onRoomBinaryMessageReceived:(NSString *_Nonnull)uid
        message:(NSData *_Nonnull)message;

 /** 
  * @type callback
  * @region 多房间
  * @author hanchenchen.c
  * @brief 收到来自房间中其他用户通过 sendUserMessage:message:{@link #RTCRoom#sendUserMessage:message:} 发来的文本消息时（P2P），会收到此回调。
  * @param rtcRoom RTCRoom 对象
  * @param uid 消息发送者的用户 ID 。
  * @param message 收到的文本消息内容。
  */
 - (void)rtcRoom:( RTCRoom *_Nonnull)rtcRoom
    onUserMessageReceived:(NSString *_Nonnull)uid
               message:(NSString *_Nonnull)message;

 /** 
 * @type callback
 * @region 多房间
 * @author hanchenchen.c
 * @brief 收到来自房间中其他用户通过 sendUserBinaryMessage:message:{@link #RTCRoom#sendUserBinaryMessage:message:} 发来的二进制消息时，会收到此回调。
 * @param rtcRoom RTCRoom 对象
 * @param uid 消息发送者的用户 ID 。
 * @param message 收到的二进制消息内容。
 */
- (void)rtcRoom:( RTCRoom *_Nonnull)rtcRoom
    onUserBinaryMessageReceived:(NSString *_Nonnull)uid
               message:(NSData *_Nonnull)message;

 /** 
  * @type callback
  * @region 多房间
  * @author hanchenchen.c
  * @brief 向房间内单个用户发送文本或二进制消息后（P2P），消息发送方会收到该消息发送结果回调。
  * @param rtcRoom RTCRoom 对象。
  * @param msgid 本条消息的 ID。
  * @param error 消息发送结果，详见 ByteRTCUserMessageSendResult{@link #ByteRTCUserMessageSendResult}
  * @notes  <br>
  *        + 你应调用 sendUserMessage:message:{@link #RTCRoom#sendUserMessage:message:} 向房间内单个用户发送文本消息 <br>
  *        + 你应调用 sendUserBinaryMessage:message:{@link #RTCRoom#sendUserBinaryMessage:message:} 向房间内单个用户发送二进制消息
  */
 - (void)rtcRoom:( RTCRoom *_Nonnull)rtcRoom onUserMessageSendResult:(int64_t)msgid error:(ByteRTCUserMessageSendResult)error;

 /** 
  * @type callback
  * @region 多房间
  * @author hanchenchen.c
  * @brief 向房间内所有用户群发文本或二进制消息后，消息发送方会收到该消息发送结果回调。
  * @param rtcRoom RTCRoom 对象。
  * @param msgid 本条消息的 ID。
  * @param error 消息发送结果，详见 ByteRTCRoomMessageSendResult{@link #ByteRTCRoomMessageSendResult}
  * @notes  <br>
  *        + 你应调用 sendRoomMessage:{@link #RTCRoom#sendRoomMessage:} 向房间内群发文本消息 <br>
  *        + 你应调用 sendRoomBinaryMessage:{@link #RTCRoom#sendRoomBinaryMessage:} 向房间内群发二进制消息
  */
 - (void)rtcRoom:( RTCRoom *_Nonnull)rtcRoom onRoomMessageSendResult:(int64_t)msgid error:(ByteRTCRoomMessageSendResult)error;


/** 
 * @type callback
 * @region 视频管理
 * @author qipengxiang
 * @brief 通过调用服务端 MuteUser/UnmuteUser 方法禁用/解禁指定房间内指定用户视频流的发送时，触发此回调。
 * @param uid 被禁用/解禁的视频流用户 ID
 * @param banned 视频流发送状态 <br>
 *        + true: 视频流发送被禁用 <br>
 *        + false: 视频流发送被解禁
 * @notes  <br>
 *        + 房间内指定用户被禁止/解禁视频流发送时，房间内所有用户都会收到该回调。  <br>
 *        + 若被封禁用户退房后再进房，则依然是封禁状态，且房间内所有人会再次收到该回调。  <br>
 *        + 若被封禁用户断网后重连进房，则依然是封禁状态，且只有本人会再次收到该回调。  <br>
 *        + 指定用户被封禁后，房间内其他用户退房后再进房，会再次收到该回调。  <br>
 *        + 通话人数超过 5 人时，只有被封禁/解禁用户会收到该回调。
 */
- (void)rtcRoom:( RTCRoom *_Nonnull)rtcRoom onVideoStreamBanned:(NSString *_Nonnull)uid isBanned:(BOOL)banned;

/** 
 * @type callback
 * @region 音频事件回调
 * @author qipengxiang
 * @brief 通过调用服务端 MuteUser/UnmuteUser 方法禁用/解禁指定房间内指定用户视音频流的发送时，触发此回调。
 * @param uid 被禁用/解禁的音频流用户 ID
 * @param banned 音频流发送状态 <br>
 *        + true: 音频流发送被禁用 <br>
 *        + false: 音频流发送被解禁
 * @notes  <br>
 *        + 房间内指定用户被禁止/解禁音频流发送时，房间内所有用户都会收到该回调。  <br>
 *        + 若被封禁用户退房后再进房，则依然是封禁状态，且房间内所有人会再次收到该回调。  <br>
 *        + 若被封禁用户断网后重连进房，则依然是封禁状态，且只有本人会再次收到该回调。  <br>
 *        + 指定用户被封禁后，房间内其他用户退房后再进房，会再次收到该回调。  <br>
 *        + 通话人数超过 5 人时，只有被封禁/解禁用户会收到该回调。
 */
- (void)rtcRoom:( RTCRoom *_Nonnull)rtcRoom onAudioStreamBanned:(NSString *_Nonnull)uid isBanned:(BOOL)banned;

#pragma mark ForwardStream related callback
    /** 
     * @type callback
     * @region 多房间
     * @brief 跨房间媒体流转发状态和错误回调
     * @param rtcRoom RTCRoom 对象
     * @param infos 跨房间媒体流转发目标房间信息数组，详见 ForwardStreamStateInfo{@link #ForwardStreamStateInfo}
     */
    - (void)rtcRoom:( RTCRoom *_Nonnull)rtcRoom onForwardStreamStateChanged:(NSArray<ForwardStreamStateInfo *> * _Nonnull)infos;
    /** 
     * @type callback
     * @region 多房间
     * @brief 跨房间媒体流转发事件回调
     * @param rtcRoom RTCRoom 对象
     * @param infos 跨房间媒体流转发目标房间事件数组，详见 ForwardStreamEventInfo{@link #ForwardStreamEventInfo}
     */
    - (void)rtcRoom:( RTCRoom * _Nonnull)rtcRoom onForwardStreamEvent:(NSArray<ForwardStreamEventInfo *> * _Nonnull)infos;
@end

/**
 * @type api
 */
BYTERTC_APPLE_EXPORT @interface RTCRoom : NSObject

@property(nonatomic, weak) id<RTCRoomDelegate> _Nullable delegate;

#pragma mark - Core Methods

/** 
 * @type api
 * @region 多房间
 * @author shenpengliang
 * @brief 销毁房间
 * @notes 退出并销毁调用 createRtcRoom:{@link #ByteRTCEngineKit#createRtcRoom:} 所创建的房间。
 */
- (void)destroy;

/** 
 * @hidden
 * @type api
 * @region 多房间
 * @author shenpengliang
 * @brief 获取房间 ID
 */
- (NSString *_Nullable)getRoomId;

/** 
 * @type api
 * @region 多房间
 * @author shenpengliang
 * @brief 通过设置 RTCRoomDelegate{@link #RTCRoomDelegate} 代理，可以监听此 `RTCRoom` 对象对应的回调事件。
 * @param roomDelegate 参见 RTCRoomDelegate{@link #RTCRoomDelegate}。
 */
- (void)setRtcRoomDelegate:(id<RTCRoomDelegate> _Nullable)roomDelegate;

/** 
 * @type api
 * @region 多房间
 * @author shenpengliang
 * @brief 加入房间。<br>
 *        调用 createRtcRoom:{@link #ByteRTCEngineKit#createRtcRoom:} 创建房间后，调用此方法加入房间，同房间内其他用户进行音视频通话。  <br>
 * @param token 动态密钥，用于对进房用户进行鉴权验证。  <br>
 *        进入房间需要携带 Token。测试时可使用控制台生成临时 Token，正式上线需要使用密钥 SDK 在你的服务端生成并下发 Token。  <br>
 *        使用不同 AppID 的 App 是不能互通的。  <br>
 *        请务必保证生成 Token 使用的 AppID 和创建引擎时使用的 AppID 相同，否则会导致加入房间失败。  <br>
 * @param userInfo 用户 ID。参看 ByteRTCUserInfo{@link #ByteRTCUserInfo}。  <br>
 * @param roomConfig 房间参数配置，设置房间模式以及是否自动发布或订阅流。具体配置模式参看 ByteRTCRoomConfig{@link #ByteRTCRoomConfig}。  <br>
 * @return 方法调用结果。  <br>
 *        +  0: 成功  <br>
 *        + -1: 参数无效  <br>
 *        + -2: 已经在房间内。接口调用成功后，只要收到返回值为 0 ，且未调用 leaveRoom{@link #RTCRoom#leaveRoom} 成功，则再次调用进房接口时，无论填写的房间 ID 和用户 ID 是否重复，均触发此返回值。  <br>
 *        + -3: room 为空 <br>
 * @notes  <br>
 *        + 同一个 AppID 的同一个房间内，每个用户的用户 ID 必须是唯一的。如果两个用户的用户 ID 相同，则后加入房间的用户会将先加入房间的用户踢出房间，并且先加入房间的用户会收到 rtcEngine:onError:{@link #ByteRTCEngineDelegate#rtcEngine:onError:} 回调通知，错误类型为重复登录 BRERR_DUPLICATE_LOGIN。  <br>
 *        + 本地用户调用此方法加入房间成功后，会收到 rtcRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #RTCRoomDelegate#rtcRoom:onRoomStateChanged:withUid:state:extraInfo:} 回调通知。  <br>
 *        + 本地用户调用 setUserVisibility:{@link #RTCRoom#setUserVisibility:} 将自身设为可见后加入房间，远端用户会收到 rtcRoom:onUserJoined:elapsed:{@link #RTCRoomDelegate#rtcRoom:onUserJoined:elapsed:} 回调通知。  <br>
 *        + 用户加入房间成功后，在本地网络状况不佳的情况下，SDK 可能会与服务器失去连接，此时 SDK 将会自动重连。重连成功后，本地会收到 rtcRoom:onUserJoined:elapsed:{@link #RTCRoomDelegate#rtcRoom:onUserJoined:elapsed:} 回调通知。  <br>
 */
- (int)joinRoomByToken:(NSString *_Nullable)token userInfo:(ByteRTCUserInfo *_Nonnull)userInfo roomConfig:(ByteRTCRoomConfig *_Nonnull)roomConfig;

/** 
 * @type api
 * @region 多房间
 * @author liuzhiqiang
 * @brief 设置用户可见性。默认可见。  <br>
 * @param enable 设置用户是否对房间内其他用户可见：  <br>
 *        + true: 可以在房间内发布音视频流，房间中的其他用户将收到用户的行为通知，例如进房、开启视频采集和退房。  <br>
 *        + false: 不可以在房间内发布音视频流，房间中的其他用户不会收到用户的行为通知，例如进房、开启视频采集和退房。
 * @return  <br>
 *         + 0: 方法调用成功  <br>
 *         + < 0: 方法调用失败  <br>
 * @notes  <br>
 *       + 该方法在加入房间前后均可调用。 <br>
 *       + 在房间内调用此方法，房间内其他用户会收到相应的回调通知：<br>
 *            - 从 false 切换至 true 时，房间内其他用户会收到 rtcRoom:onUserJoined:elapsed:{@link #RTCRoomDelegate#rtcRoom:onUserJoined:elapsed:} 回调通知；  <br>
 *            - 从 true 切换至 false 时，房间内其他用户会收到 rtcRoom:onUserLeave:reason:{@link #RTCRoomDelegate#rtcRoom:onUserLeave:reason:} 回调通知。  <br>
 *       + 若调用该方法将可见性设为 false，此时尝试发布流会收到 `ByteRTCWarningCodeSubscribeStreamForbiden` 警告。
 */
- (BOOL)setUserVisibility:(BOOL)enable;

/** 
 * @hidden
 * @type api
 * @region 多房间
 * @author shenpengliang
 * @brief 获取当前用户角色。  <br>
 * @return 当前用户角色，详见 ByteRTCUserRoleType{@link #ByteRTCUserRoleType} 枚举类型。  <br>
 */
- (ByteRTCUserRoleType)clientRole;

/** 
 * @type api
 * @region 多房间
 * @author wangzhanqiang
 * @brief 设置发流端音画同步。  <br>
 *        当同一用户同时使用两个通话设备分别采集发送音频和视频时，有可能会因两个设备所处的网络环境不一致而导致发布的流不同步，此时你可以在视频发送端调用该接口，SDK 会根据音频流的时间戳自动校准视频流，以保证接收端听到音频和看到视频在时间上的同步性。
 * @param audioUserId 音频发送端的用户 ID，将该参数设为空则可解除当前音视频的同步关系。
 * @return 方法调用结果：  <br>
 *        + True：成功  <br>
 *        + False：失败
 * @notes <br>
 *        + 该方法在进房前后均可调用。  <br>
 *        + 进行音画同步的音频发布用户 ID 和视频发布用户 ID 须在同一个 RTC 房间内。  <br>
 *        + 调用该接口后音画同步状态发生改变时，你会收到 rtcRoom:onAVSyncStateChange:{@link #RTCRoomDelegate#rtcRoom:onAVSyncStateChange:} 回调。  <br>
 *        + 同一 RTC 房间内允许存在多个音视频同步关系，但需注意单个音频源不支持与多个视频源同时同步。  <br>
 *        + 如需更换同步音频源，再次调用该接口传入新的 `audioUserId` 即可；如需更换同步视频源，需先解除当前的同步关系，后在新视频源端开启同步。
 */
- (BOOL)setMultiDeviceAVSync:(NSString* _Nullable) audioUserId;

/** 
 *  @type api
 *  @region 房间管理
 *  @author shenpengliang
 *  @brief 离开房间。  <br>
 *         用户调用此方法离开房间，结束通话过程，释放所有通话相关的资源。  <br>
 *  @return 方法调用结果。  <br>
 *         +  0: 方法调用成功  <br>
 *         + < 0: 方法调用失败  <br>
 *  @notes  <br>
 *        + 用户离开房间后，本地会收到 onLeaveRoomWithStats:{@link #RTCRoomDelegate#rtcRoom:onLeaveRoomWithStats:} 的回调；  <br>
 *        + 调用 setUserVisibility:{@link #RTCRoom#setUserVisibility:} 方法将自身设为可见的用户离开房间后，房间内其他用户会收到 rtcRoom:onUserLeave:reason:{@link #RTCRoomDelegate#rtcRoom:onUserLeave:reason:} 回调通知。  <br>
 *        + 调用 joinRoomByToken:userInfo:roomConfig:{@link #RTCRoom#joinRoomByToken:userInfo:roomConfig:} 方法加入房间后，必须调用此方法离开房间，否则无法进入下一个房间。无论当前是否在房间内，都可以调用此方法。重复调用此方法没有负面影响。  <br>
 */
- (int)leaveRoom;


/** 
 * @type api
 * @region 多房间
 * @author shenpengliang
 * @brief 更新 Token。  <br>
 *        用户调用 joinRoomByToken:userInfo:roomConfig:{@link #RTCRoom#joinRoomByToken:userInfo:roomConfig:} 方法加入房间时，
 *        如果使用了过期的 Token 将导致加入房间失败，并会收到 rtcRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #RTCRoomDelegate#rtcRoom:onRoomStateChanged:withUid:state:extraInfo:} 回调，
 *        回调错误码为 ByteRTCErrorCode{@link #ByteRTCErrorCode} 中的 ByteRTCErrorCodeInvalidToken。
 *        此时需要重新获取 Token，并调用此方法更新 Token。更新 Token 后，SDK 会自动加入房间。 <br>
 * @param token 更新的动态密钥。
 * @return 方法调用结果。  <br>
 *         +  0: 方法调用成功。  <br>
 *         + < 0: 方法调用失败。  <br>
 * @notes Token 过期时，如果已经加入房间成功，则不会受到影响。Token 过期的错误会在下一次使用过期的 Token 加入房间时，或因本地网络状况不佳导致断网重新连入房间时通知用户。
 */
- (int)renewToken:(NSString *_Nullable)token;
/** 
 * @type api
 * @region 视频管理
 * @author zhaomingliang
 * @brief 设置期望订阅的远端视频流的参数。
 * @param userId 期望订阅的远端视频流发布用户的 ID。
 * @param remoteVideoConfig 期望订阅的远端视频流参数，参看 ByteRTCRemoteVideoConfig{@link #ByteRTCRemoteVideoConfig}。
 * @notes <br>
 *        + 该方法仅在发布端调用 enableSimulcastMode:{@link #ByteRTCEngineKit#enableSimulcastMode:} 开启了发送多路视频流的情况下生效，此时订阅端将收到来自发布端与期望设置的参数最相近的一路流；否则订阅端只会收到一路参数为分辨率 640px × 360px、帧率 15fps 的视频流。  <br>
 *        + 若发布端开启了推送多路流功能，但订阅端不对流参数进行设置，则默认接受发送端设置的分辨率最大的一路视频流。  <br>
 *        + 该方法需在进房后调用，若想进房前设置，你需调用 joinRoomByToken:userInfo:roomConfig:{@link #RTCRoom#joinRoomByToken:userInfo:roomConfig:}，并对 `roomConfig` 中的 `remoteVideoConfig` 进行设置。  <br>
 *        + 该方法在订阅前后都可调用，订阅后的设置会在重新订阅该流时生效。 <br>
 *        + SDK 会根据发布端和所有订阅端的设置灵活调整视频流的参数，具体调整策略详见[推送多路流](https://www.volcengine.com/docs/6348/70139)文档。
 */
- (int) setRemoteVideoConfig:(NSString * _Nonnull) userId remoteVideoConfig:(ByteRTCRemoteVideoConfig *_Nonnull) remoteVideoConfig;

/** 
 * @type api
 * @region 房间管理
 * @author shenpengliang
 * @brief 在当前所在房间内发布本地通过摄像头/麦克风采集的媒体流
 * @param type 媒体流类型，用于指定发布音频/视频，参看 ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}
 * @return 方法调用结果： <br>
 *        + 0: 发布成功  <br>
 *        + -1: 发布失败
 * @notes <br>
 *        + 调用 setUserVisibility:{@link #RTCRoom#setUserVisibility:} 方法将自身设置为不可见后无法调用该方法，需将自身切换至可见后方可调用该方法发布摄像头音视频流。 <br>
 *        + 如果你需要发布屏幕共享流，调用 publishScreen:{@link #RTCRoom#publishScreen:}。<br>
 *        + 如果你需要向多个房间发布流，调用 startForwardStreamToRooms:{@link #RTCRoom#startForwardStreamToRooms:}。  <br>
 *        + 调用此方法后，房间中的所有远端用户会收到 rtcRoom:onUserPublishStream:type:{@link #RTCRoomDelegate#rtcRoom:onUserPublishStream:type:} 回调通知，其中成功收到了音频流的远端用户会收到 rtcEngine:onFirstRemoteAudioFrame:{@link #ByteRTCEngineDelegate#rtcEngine:onFirstRemoteAudioFrame:} 回调，订阅了视频流的远端用户会收到 rtcEngine:onFirstRemoteVideoFrameDecoded:withFrameInfo:{@link #ByteRTCEngineDelegate#rtcEngine:onFirstRemoteVideoFrameDecoded:withFrameInfo:} 回调。<br>
 *        + 调用 unpublishStream:{@link #RTCRoom#unpublishStream:} 取消发布。
 */
- (int)publishStream:(ByteRTCMediaStreamType)type;
/** 
 * @type api
 * @region 房间管理
 * @author shenpengliang
 * @brief 停止将本地摄像头/麦克风采集的媒体流发布到当前所在房间中
 * @param type 媒体流类型，用于指定停止发布音频/视频，参看 ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}
 * @return  <br>
 *        + 0: 停止发布成功  <br>
 *        + -1: 停止发布失败
 * @notes  <br>
 *        + 调用 publishStream:{@link #RTCRoom#publishStream:} 手动发布摄像头音视频流后，你需调用此接口停止发布。<br>
 *        + 调用此方法停止发布音视频流后，房间中的其他用户将会收到 rtcRoom:onUserUnPublishStream:type:reason: {@link #RTCRoomDelegate#rtcRoom:onUserUnPublishStream:type:reason:} 回调通知。
 */
- (int)unpublishStream:(ByteRTCMediaStreamType)type;

/** 
 * @type api
 * @region 屏幕共享
 * @author liyi.000
 * @brief 在当前所在房间内发布本地屏幕共享音视频流
 * @param type 媒体流类型，用于指定发布屏幕音频/视频，参看 ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}。
 * @return  <br>
 *       + 0: 发布成功 <br>
 *       + -1: 发布失败
 * @notes <br>
 *        + 调用 setUserVisibility:{@link #RTCRoom#setUserVisibility:} 方法将自身设置为不可见后无法调用该方法，需将自身切换至可见后方可调用该方法发布屏幕流。 <br>
 *        + 调用该方法后，房间中的所有远端用户会收到 rtcRoom:onUserPublishScreen:type:{@link #RTCRoomDelegate#rtcRoom:onUserPublishScreen:type:} 回调，其中成功收到音频流的远端用户会收到 rtcEngine:onFirstRemoteAudioFrame:{@link #ByteRTCEngineDelegate#rtcEngine:onFirstRemoteAudioFrame:} 回调，订阅了视频流的远端用户会收到 rtcEngine:onFirstRemoteVideoFrameDecoded:withFrameInfo:{@link #ByteRTCEngineDelegate#rtcEngine:onFirstRemoteVideoFrameDecoded:withFrameInfo:} 回调。<br>
 *        + 如果你需要向多个房间发布流，调用 startForwardStreamToRooms:{@link #RTCRoom#startForwardStreamToRooms:}。  <br>
 *        + 调用 unpublishScreen:{@link #RTCRoom#unpublishScreen:} 取消发布。
 */
- (int)publishScreen:(ByteRTCMediaStreamType)type;
/** 
 * @type api
 * @region 屏幕共享
 * @author liyi.000
 * @brief 停止将本地屏幕共享音视频流发布到当前所在房间中
 * @param type 媒体流类型，用于指定停止发布屏幕音频/视频，参看 ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}
 * @return <br>
 *      + 0: 停止发布成功 <br>
 *      + -1: 停止发布失败
 * @notes <br>
 *        + 调用 publishScreen:{@link #RTCRoom#publishScreen:} 发布屏幕流后，你需调用此接口停止发布。 <br>
 *        + 调用此方法停止发布屏幕音视频流后，房间中的其他用户将会收到 rtcRoom:onUserUnPublishScreen:type:reason:{@link #RTCRoomDelegate#rtcRoom:onUserUnPublishScreen:type:reason:} 回调。
 */
- (int)unpublishScreen:(ByteRTCMediaStreamType)type;

/** 
 * @hidden
 * @deprecated since 336.1, use subscribeStream, unsubscribeStream, subscribeScreen and unsubscribeScreen instead.
 * @type api
 * @region 多房间
 * @author shenpengliang
 * @brief 订阅房间内指定的远端音视频流。  <br>
 *        无论是自动订阅还是手动订阅模式，你都可以调用此方法按需订阅房间中的音视频流。  <br>
 *        该方法也可用于更新已经订阅的流的属性、媒体类型等配置。
 * @param userId 指定订阅的远端发布音视频流的用户 ID 。  <br>
 * @param streamType 流属性，用于指定订阅主流/屏幕流，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex} 。  <br>
 * @param mediaType 媒体类型，用于指定订阅音/视频，参看 ByteRTCSubscribeMediaType{@link #ByteRTCSubscribeMediaType}。<br>
 * @param videoConfig 视频订阅配置，参看 ByteRTCSubscribeVideoConfig{@link #ByteRTCSubscribeVideoConfig}。<br>
 * @notes <br>
 *        + 你必须通过 rtcRoom:onStreamAdd:{@link #RTCRoomDelegate#rtcRoom:onStreamAdd:} 和 rtcRoom:didStreamRemoved:stream:reason:{@link #RTCRoomDelegate#rtcRoom:didStreamRemoved:stream:reason:} 两个回调获取当前房间里的音视频流信息，并调用本方法按需订阅流或修改订阅配置。  <br>
 *        + 若订阅失败，你会收到 rtcEngine:onError:{@link #ByteRTCEngineDelegate#rtcEngine:onError:} 回调通知，具体失败原因参看 ByteRTCErrorCode{@link #ByteRTCErrorCode}。
 *        + 若调用 pauseAllSubscribedStream:{@link #RTCRoom#pauseAllSubscribedStream:} 暂停接收远端音视频流，此时仍可使用该方法对暂停接收的流进行设置，你会在调用 resumeAllSubscribedStream:{@link #RTCRoom#resumeAllSubscribedStream:} 恢复接收流后收到修改设置后的流。  <br>
 */
- (void)subscribeUserStream:(NSString *_Nonnull)userId streamType:(ByteRTCStreamIndex)streamType mediaType:(ByteRTCSubscribeMediaType)mediaType videoConfig:(ByteRTCSubscribeVideoConfig *_Nonnull)videoConfig;
/** 
 * @type api
 * @region 房间管理
 * @author liuzhiqiang
 * @brief 订阅房间内指定的通过摄像头/麦克风采集的媒体流。  <br>
 *        该方法对自动订阅和手动订阅模式均适用。
 * @param userId 指定订阅的远端发布音视频流的用户 ID。
 * @param mediaStreamType 媒体流类型，用于指定订阅音频/视频。参看 ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}。
 * @notes  <br>
 *        + 你必须先通过 rtcRoom:onUserPublishStream:type:{@link #RTCRoomDelegate#rtcRoom:onUserPublishStream:type:} 回调获取当前房间里的远端摄像头音视频流信息，然后调用本方法按需订阅。  <br>
 *        + 调用该方法后，你会收到 rtcRoom:onStreamSubscribed:userId:subscribeConfig:{@link #RTCRoomDelegate#rtcRoom:onStreamSubscribed:userId:subscribeConfig:} 通知方法调用结果。  <br>
 *        + 关于其他调用异常，你会收到 rtcRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #RTCRoomDelegate#rtcRoom:onStreamStateChanged:withUid:state:extraInfo:} 回调通知，具体异常原因参看 ByteRTCErrorCode{@link #ByteRTCErrorCode}。
 */
- (void)subscribeStream:(NSString *_Nonnull)userId mediaStreamType:(ByteRTCMediaStreamType)mediaStreamType;
/** 
 * @type api
 * @region 房间管理
 * @author liuzhiqiang
 * @brief 取消订阅房间内指定的通过摄像头/麦克风采集的媒体流。  <br>
 *        该方法对自动订阅和手动订阅模式均适用。
 * @param userId 指定取消订阅的远端发布音视频流的用户 ID。
 * @param mediaStreamType 媒体流类型，用于指定取消订阅音频/视频。参看 ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}。
 * @notes  <br>
 *        + 调用该方法后，你会收到 rtcRoom:onStreamSubscribed:userId:subscribeConfig:{@link #RTCRoomDelegate#rtcRoom:onStreamSubscribed:userId:subscribeConfig:} 通知流的退订结果。  <br>
 *        + 关于其他调用异常，你会收到 rtcRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #RTCRoomDelegate#rtcRoom:onStreamStateChanged:withUid:state:extraInfo:} 回调通知，具体失败原因参看 ByteRTCErrorCode{@link #ByteRTCErrorCode}。
 */
- (void)unSubscribeStream:(NSString *_Nonnull)userId mediaStreamType:(ByteRTCMediaStreamType)mediaStreamType;
/** 
 * @type api
 * @region 房间管理
 * @author liuzhiqiang
 * @brief 订阅房间内指定的远端屏幕共享音视频流。  <br>
 *        该方法对自动订阅和手动订阅模式均适用。
 * @param userId 指定订阅的远端发布屏幕流的用户 ID。
 * @param mediaStreamType 媒体流类型，用于指定订阅音频/视频。参看 ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}。
 * @notes  <br>
 *        + 你必须先通过 rtcRoom:onUserPublishScreen:type:{@link #RTCRoomDelegate#rtcRoom:onUserPublishScreen:type:} 回调获取当前房间里的远端屏幕流信息，然后调用本方法按需订阅。  <br>
 *        + 调用该方法后，你会收到 rtcRoom:onStreamSubscribed:userId:subscribeConfig:{@link #RTCRoomDelegate#rtcRoom:onStreamSubscribed:userId:subscribeConfig:} 通知流的订阅结果。  <br>
 *        + 关于其他调用异常，你会收到 rtcRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #RTCRoomDelegate#rtcRoom:onStreamStateChanged:withUid:state:extraInfo:} 回调通知，具体异常原因参看 ByteRTCErrorCode{@link #ByteRTCErrorCode}。
 */
- (void)subscribeScreen:(NSString *_Nonnull)userId mediaStreamType:(ByteRTCMediaStreamType)mediaStreamType;
/** 
 * @type api
 * @region 房间管理
 * @author liuzhiqiang
 * @brief 取消订阅房间内指定的远端屏幕共享音视频流。  <br>
 *        该方法对自动订阅和手动订阅模式均适用。
 * @param userId 指定取消订阅的远端发布屏幕流的用户 ID。
 * @param mediaStreamType 媒体流类型，用于指定取消订阅音频/视频。参看 ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}。
 * @notes  <br>
 *        + 调用该方法后，你会收到 rtcRoom:onStreamSubscribed:userId:subscribeConfig:{@link #RTCRoomDelegate#rtcRoom:onStreamSubscribed:userId:subscribeConfig:} 通知流的退订结果。  <br>
 *        + 关于其他调用异常，你会收到 rtcRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #RTCRoomDelegate#rtcRoom:onStreamStateChanged:withUid:state:extraInfo:} 回调通知，具体失败原因参看 ByteRTCErrorCode{@link #ByteRTCErrorCode}。
 */
- (void)unSubscribeScreen:(NSString *_Nonnull)userId mediaStreamType:(ByteRTCMediaStreamType)mediaStreamType;

/** 
 * @type api
 * @region 多房间
 * @author shenpengliang
 * @brief 暂停接收来自远端的媒体流
 * @param mediaType 媒体流类型，指定需要暂停接收音频还是视频流，参看 ByteRTCPauseResumControlMediaType{@link #ByteRTCPauseResumControlMediaType}
 * @notes <br>
 *        + 该方法仅暂停远端流的接收，并不影响远端流的采集和发送；  <br>
 *        + 该方法不改变用户的订阅状态以及订阅流的属性。  <br>
 *        + 若想恢复接收远端流，需调用 resumeAllSubscribedStream:{@link #RTCRoom#resumeAllSubscribedStream:}。
 */
- (void)pauseAllSubscribedStream:(ByteRTCPauseResumControlMediaType) mediaType;

/** 
 * @type api
 * @region 多房间
 * @author shenpengliang
 * @brief 恢复接收来自远端的媒体流
 * @param mediaType 媒体流类型，指定需要暂停接收音频还是视频流，参看 ByteRTCPauseResumControlMediaType{@link #ByteRTCPauseResumControlMediaType}
 * @notes <br>
 *        + 该方法仅恢复远端流的接收，并不影响远端流的采集和发送；  <br>
 *        + 该方法不改变用户的订阅状态以及订阅流的属性。
 */
- (void)resumeAllSubscribedStream:(ByteRTCPauseResumControlMediaType) mediaType;
 /** 
  * @type api
  * @region 多房间
  * @author hanchenchen.c
  * @brief 给房间内指定的用户发送文本消息（P2P）。
  * @param userId  <br>
  *        消息接收用户的 ID
  * @param message  <br>
  *        发送的文本消息内容。  <br>
  *        消息不超过 62KB。
  * @return 这次发送消息的编号，从 1 开始递增。
  * @notes  <br>
  *      + 在发送房间内文本消息前，必须先调用 joinRoomByToken:userInfo:roomConfig:{@link #RTCRoom#joinRoomByToken:userInfo:roomConfig:} 加入房间。  <br>
  *      + 调用该函数后会收到一次 rtcRoom:onUserMessageSendResult:error:{@link #RTCRoomDelegate#rtcRoom:onUserMessageSendResult:error:} 回调，通知消息发送方发送成功或失败。  <br>
  *      + 若文本消息发送成功，则 uid 所指定的用户会收到 rtcRoom:onUserMessageReceived:message:{@link #RTCRoomDelegate#rtcRoom:onUserMessageReceived:message:} 回调。
  */
 - (int64_t)sendUserMessage:(NSString *_Nonnull)userId message:(NSString *_Nonnull)message;

 /** 
  * @type api
  * @region 多房间
  * @author hanchenchen.c
  * @brief 给房间内指定的用户发送二进制消息（P2P）。
  * @param uid  <br>
  *        消息接收用户的 ID
  * @param message  <br>
  *        发送的二进制消息内容  <br>
  *        消息不超过 46KB。
  * @return 这次发送消息的编号，从 1 开始递增。
  * @notes  <br>
  *      + 在发送房间内二进制消息前，必须先调用 joinRoomByToken:userInfo:roomConfig:{@link #RTCRoom#joinRoomByToken:userInfo:roomConfig:} 加入房间。  <br>
  *      + 调用该函数后会收到一次 rtcRoom:onUserMessageSendResult:error:{@link #RTCRoomDelegate#rtcRoom:onUserMessageSendResult:error:} 回调，通知消息发送方发送成功或失败；  <br>
  *      + 若二进制消息发送成功，则 uid 所指定的用户会收到 rtcRoom:onUserBinaryMessageReceived:message:{@link #RTCRoomDelegate#rtcRoom:onUserBinaryMessageReceived:message:} 回调。
  */
 - (int64_t)sendUserBinaryMessage:(NSString * _Nonnull)uid message:(NSData * _Nonnull)message;

 /** 
  * @type api
  * @region 多房间
  * @author hanchenchen.c
  * @brief 给房间内的所有其他用户发送文本消息。
  * @param message  <br>
  *        发送的文本消息内容。  <br>
  *        消息不超过 62KB。
  * @return 这次发送消息的编号，从 1 开始递增。
  * @notes  <br>
  *      + 在发送房间内文本消息前，必须先调用 joinRoomByToken:userInfo:roomConfig:{@link #RTCRoom#joinRoomByToken:userInfo:roomConfig:} 加入房间。  <br>
  *      + 调用该函数后会收到一次 rtcRoom:onRoomMessageSendResult:error:{@link #RTCRoomDelegate#rtcRoom:onRoomMessageSendResult:error:} 回调，通知消息发送方发送成功或失败；  <br>
  *      + 若文本消息发送成功，则房间内所有远端用户会收到 rtcRoom:onRoomMessageReceived:message:{@link #RTCRoomDelegate#rtcRoom:onRoomMessageReceived:message:} 回调。
  */
 - (int64_t)sendRoomMessage:(NSString *_Nonnull)message;

 /** 
  * @type api
  * @region 多房间
  * @author hanchenchen.c
  * @brief 给房间内的所有其他用户发送二进制消息。
  * @param message  <br>
  *        用户发送的二进制广播消息  <br>
  *        消息不超过 46KB。
  * @return 这次发送消息的编号，从 1 开始递增。
  * @notes  <br>
  *      + 在房间内广播二进制消息前，必须先调用 joinRoomByToken:userInfo:roomConfig:{@link #RTCRoom#joinRoomByToken:userInfo:roomConfig:} 加入房间。  <br>
  *      + 调用该函数后会收到一次 rtcRoom:onRoomMessageSendResult:error:{@link #RTCRoomDelegate#rtcRoom:onRoomMessageSendResult:error:} 回调，通知消息发送方发送成功或失败；  <br>
  *      + 若二进制消息发送成功，则房间内所有用户会收到 rtcRoom:onRoomBinaryMessageReceived:message:{@link #RTCRoomDelegate#rtcRoom:onRoomBinaryMessageReceived:message:} 回调。
  */
 - (int64_t)sendRoomBinaryMessage:(NSData *  _Nonnull)message;

#pragma mark ForwardStream
    /** 
     * @type api
     * @region 多房间
     * @author wunailiang
     * @brief 开始跨房间转发媒体流。
     *        在用户进入房间后调用本接口，实现向多个房间转发媒体流，适用于跨房间连麦等场景。<br>
     * @param configurations 跨房间媒体流转发指定房间的信息。参看 ForwardStreamConfiguration{@link #ForwardStreamConfiguration}。
     * @return  <br>
     *        0: 方法调用成功
     *        <0: 方法调用失败  <br>
     * @notes <br>
     *        + 调用本方法后，将在本端触发 rtcRoom:onForwardStreamStateChanged:{@link #RTCRoomDelegate#rtcRoom:onForwardStreamStateChanged:} 回调。
     *        + 调用本方法后，你可以通过监听 rtcRoom:onForwardStreamEvent:{@link #RTCRoomDelegate#rtcRoom:onForwardStreamEvent:} 回调来获取各个目标房间在转发媒体流过程中的相关事件。
     *        + 开始转发后，目标房间中的用户将接收到本地用户进房 rtcRoom:onUserJoined:elapsed:{@link #RTCRoomDelegate#rtcRoom:onUserJoined:elapsed:} 和发流 rtcRoom:onUserJoined:elapsed:{@link #RTCRoomDelegate#rtcRoom:onUserJoined:elapsed:} 的回调。
     *        + 调用本方法后，可以调用 updateForwardStreamToRooms:{@link #RTCRoom#updateForwardStreamToRooms:} 更新目标房间信息，例如，增加或减少目标房间等。
     *        + 调用本方法后，可以调用 stopForwardStreamToRooms{@link #RTCRoom#stopForwardStreamToRooms} 停止向所有房间转发媒体流。
     *        + 调用本方法后，可以调用 pauseForwardStreamToAllRooms{@link #RTCRoom#pauseForwardStreamToAllRooms} 暂停向所有房间转发媒体流。
     */
    - (int)startForwardStreamToRooms:(NSArray <ForwardStreamConfiguration *> * _Nullable)configurations;
    /** 
     * @type api
     * @region 多房间
     * @author wunailiang
     * @brief 更新跨房间媒体流转发信息。<br>
     *        通过 startForwardStreamToRooms:{@link #RTCRoom#startForwardStreamToRooms:} 发起媒体流转发后，可调用本方法增加或者减少目标房间，或更新房间密钥。
     *        调用本方法增加或删减房间后，将在本端触发 rtcRoom:onForwardStreamStateChanged:{@link #RTCRoomDelegate#rtcRoom:onForwardStreamStateChanged:} 回调，包含发生了变动的目标房间中媒体流转发状态。
     * @param configurations 跨房间媒体流转发目标房间信息。参看 ForwardStreamConfiguration{@link #ForwardStreamConfiguration}。
     * @return  <br>
     *        0: 方法调用成功  <br>
     *        <0: 方法调用失败  <br>
     * @notes <br>
     *        + 增加目标房间后，新增目标房间中的用户将接收到本地用户进房 rtcRoom:onUserJoined:elapsed:{@link #RTCRoomDelegate#rtcRoom:onUserJoined:elapsed:} 和发布 rtcRoom:onUserJoined:elapsed:{@link #RTCRoomDelegate#rtcRoom:onUserJoined:elapsed:} 的回调。
     *        + 删减目标房间后，原目标房间中的用户将接收到本地用户停止发布 rtcRoom:onUserUnPublishStream:type:reason: {@link #RTCRoomDelegate#rtcRoom:onUserUnPublishStream:type:reason:} 和退房 rtcRoom:onUserLeave:reason:{@link #RTCRoomDelegate#rtcRoom:onUserLeave:reason:} 的回调。
     */
    - (int)updateForwardStreamToRooms:(NSArray <ForwardStreamConfiguration *> * _Nullable)configurations;
    /** 
     * @type api
     * @region 多房间
     * @author wunailiang
     * @brief 停止跨房间媒体流转发。
     *        通过 startForwardStreamToRooms:{@link #RTCRoom#startForwardStreamToRooms:} 发起媒体流转发后，可调用本方法停止向所有目标房间转发媒体流。
     * @notes <br>
     *        + 调用本方法后，将在本端触发 rtcRoom:onForwardStreamStateChanged:{@link #RTCRoomDelegate#rtcRoom:onForwardStreamStateChanged:} 回调。
     *        + 调用本方法后，原目标房间中的用户将接收到本地用户停止发布 rtcRoom:onUserUnPublishStream:type:reason: {@link #RTCRoomDelegate#rtcRoom:onUserUnPublishStream:type:reason:} 和退房 rtcRoom:onUserLeave:reason:{@link #RTCRoomDelegate#rtcRoom:onUserLeave:reason:} 的回调。
     *        + 如果需要停止向指定的房间转发媒体流，请调用 updateForwardStreamToRooms:{@link #RTCRoom#updateForwardStreamToRooms:} 更新房间信息。
     *        + 如果需要暂停转发，请调用 pauseForwardStreamToAllRooms{@link #RTCRoom#pauseForwardStreamToAllRooms}，并在之后随时调用 resumeForwardStreamToAllRooms{@link #RTCRoom#resumeForwardStreamToAllRooms} 快速恢复转发。
     */
    - (void)stopForwardStreamToRooms;
    /** 
     * @type api
     * @region 多房间
     * @author wunailiang
     * @brief 暂停跨房间媒体流转发。
     *        通过 startForwardStreamToRooms:{@link #RTCRoom#startForwardStreamToRooms:} 发起媒体流转发后，可调用本方法暂停向所有目标房间转发媒体流。
     *        调用本方法暂停向所有目标房间转发后，你可以随时调用 resumeForwardStreamToAllRooms{@link #RTCRoom#resumeForwardStreamToAllRooms} 快速恢复转发。
     * @notes 调用本方法后，目标房间中的用户将接收到本地用户停止发布 rtcRoom:onUserUnPublishStream:type:reason: {@link #RTCRoomDelegate#rtcRoom:onUserUnPublishStream:type:reason:} 和退房 rtcRoom:onUserLeave:reason:{@link #RTCRoomDelegate#rtcRoom:onUserLeave:reason:} 的回调。
     */
     - (void)pauseForwardStreamToAllRooms;
    /** 
     * @type api
     * @region 多房间
     * @author wunailiang
     * @brief 恢复跨房间媒体流转发。
     *        调用 pauseForwardStreamToAllRooms{@link #RTCRoom#pauseForwardStreamToAllRooms} 暂停转发之后，调用本方法恢复向所有目标房间转发媒体流。
     * @notes <br>
     *        目标房间中的用户将接收到本地用户进房 rtcRoom:onUserJoined:elapsed:{@link #RTCRoomDelegate#rtcRoom:onUserJoined:elapsed:} 和发布 rtcRoom:onUserJoined:elapsed:{@link #RTCRoomDelegate#rtcRoom:onUserJoined:elapsed:} 的回调。
     */
    - (void)resumeForwardStreamToAllRooms;


/** 
 * @type api
 * @region 范围语音
 * @author chuzhongtao
 * @brief 获取范围语音接口实例。
 * @return 方法调用结果： <br>
 *        + ByteRTCRangeAudio：成功，返回一个 ByteRTCRangeAudio{@link #ByteRTCRangeAudio} 实例。  <br>
 *        + NULL：失败，当前 SDK 不支持范围语音功能。
 * @notes 首次调用该方法须在创建房间后、加入房间前。
 */
- (ByteRTCRangeAudio *_Nullable)getRangeAudio;

/** 
 * @type api
 * @region 空间音频
 * @author majun.lvhiei
 * @brief 获取空间音频接口实例。  <br>
 * @return 方法调用结果：  <br>
 *        + ByteRTCSpatialAudio：成功，返回一个 ByteRTCSpatialAudio{@link #ByteRTCSpatialAudio} 实例。  <br>
 *        + NULL：失败，当前 SDK 不支持空间音频功能。
 * @notes  <br>
 *        + 首次调用该方法须在创建房间后、加入房间前。 空间音频相关 API 和调用时序详见[空间音频](https://www.volcengine.com/docs/6348/93903)。 <br>
 *        + 只有在使用支持真双声道播放的设备时，才能开启空间音频效果；  <br>
 *        + 机型性能不足可能会导致音频卡顿，使用低端机时，不建议开启空间音频效果；  <br>
 *        + SDK 最多支持 30 个用户同时开启空间音频功能。
 */
- (ByteRTCSpatialAudio *_Nullable)getSpatialAudio;

/** 
 * @type api
 * @region 云端渲染
 * @author wuxinyu.mrx
 * @brief 按照传入的布局信息开启云端渲染。 <br>
 * @param rendingInfo 渲染功能相关参数。 <br>
 * @return 方法调用结果。  <br>
 *         +  0: 方法调用成功  <br>
 *         +  < 0: 方法调用失败  <br>
 */
- (int)enableCloudRending:(NSString *_Nonnull)rendingInfo;

/** 
 * @type api
 * @region 云端渲染
 * @author wuxinyu.mrx
 * @brief 按照传入的布局信息更新云端渲染。 <br>
 * @param rendingInfo 渲染功能相关参数。 <br>
 * @return 方法调用结果。  <br>
 *         +  0: 方法调用成功  <br>
 *         + < 0: 方法调用失败  <br>
 */
- (int)updateCloudRending:(NSString *_Nonnull)rendingInfo;

/** 
 * @type api
 * @region 云端渲染
 * @author wuxinyu.mrx
 * @brief 停止云端渲染。 <br>
 * @return 方法调用结果。  <br>
 *         +  0: 方法调用成功  <br>
 *         + < 0: 方法调用失败  <br>
 */
- (int)disableCloudRending;
@end
