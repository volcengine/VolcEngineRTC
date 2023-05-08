/*
 * Copyright (c) 2022 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief ByteRTCAudioRoom
*/

#import <UIKit/UIKit.h>
#import "rtc/ByteRTCRtsDefines.h"
#import "rtc/ByteRTCAudioDefines.h"
#import "rtc/ByteRTCRangeAudio.h"
#import "rtc/ByteRTCSpatialAudio.h"

@class ByteRTCAudioRoom;

#pragma mark - ByteRTCAudioRoomDelegate
/** 
 * @type callback
 * @brief 语音房间事件回调接口
 */
@protocol ByteRTCAudioRoomDelegate <NSObject>
@optional

#pragma mark - Core Delegate Methods
 /** 
  * @type callback
  * @region 多房间
  * @brief 房间状态改变回调，加入房间、异常退出房间、发生房间相关的警告或错误时会收到此回调。
  * @param rtcRoom ByteRTCAudioRoom 实例
  * @param roomId 房间 ID。
  * @param uid 用户 ID。
  * @param state 房间状态码。  <br>
  *              + 0: 加入房间成功。  <br>
  *              + !0: 加入房间失败、异常退房、发生房间相关的警告或错误。具体原因参看 ByteRTCErrorCode{@link #ByteRTCErrorCode} 及 ByteRTCWarningCode{@link #ByteRTCWarningCode}。
  * @param extraInfo 额外信息。
  *                  `join_type`表示加入房间的类型，`0`为首次进房，`1`为重连进房。
  *                  `elapsed`表示加入房间耗时，即本地用户从调用 joinRoom:userInfo:roomConfig:{@link #ByteRTCAudioRoom#joinRoom:userInfo:roomConfig:} 到加入房间成功所经历的时间间隔，单位为 ms。
  */
 - (void)rtcRoom:(ByteRTCAudioRoom * _Nonnull)rtcRoom onRoomStateChanged:(NSString * _Nonnull)roomId
        withUid:(nonnull NSString *)uid state:(NSInteger)state
       extraInfo:(nonnull NSString *)extraInfo;

/** 
 * @type callback
 * @region 多房间
 * @brief 流状态改变回调，发生流相关的警告或错误时会收到此回调。
 * @param roomId 房间 ID。
 * @param uid 用户 ID。
 * @param state 流状态码，参看 ByteRTCErrorCode{@link #ByteRTCErrorCode} 及 ByteRTCWarningCode{@link #ByteRTCWarningCode}。
 * @param extraInfo 附加信息，目前为空。
 */
- (void)rtcRoom:(ByteRTCAudioRoom * _Nonnull)rtcRoom onStreamStateChanged:(NSString * _Nonnull)roomId
        withUid:(nonnull NSString *)uid state:(NSInteger)state
       extraInfo:(nonnull NSString *)extraInfo;

 /** 
 * @type callback
 * @region 多房间
 * @brief 离开房间成功回调。  <br>
 *        用户调用 leaveRoom{@link #ByteRTCAudioRoom#leaveRoom} 方法后，SDK 会停止所有的发布订阅流，并释放所有通话相关的音频资源。SDK 完成所有的资源释放后通过此回调通知用户。  <br>
 * @param rtcRoom  RTCRoom 对象。  <br>
 * @param stats 保留参数，目前为空。
 * @notes  <br>
 *       + 用户调用 leaveRoom{@link #ByteRTCAudioRoom#leaveRoom} 方法离开房间后，如果立即销毁 RTC 引擎，则将无法收到此回调事件。  <br>
 *       + 离开房间结束通话后，如果 App 需要使用系统音频设备，则建议在收到此回调后再初始化音频设备，否则可能由于 SDK 占用了导致 App 初始化音频设备失败。  <br>
 */
- (void)rtcRoom:(ByteRTCAudioRoom *_Nonnull)rtcRoom onLeaveRoom:(ByteRTCRoomStats * _Nonnull)stats;

/** 
 * @type callback
 * @brief Token 进房权限过期前 30 秒将触发该回调。<br>
 *        收到该回调后，你需调用 updateToken:{@link #ByteRTCAudioRoom#updateToken:} 更新 Token 进房权限。
 * @notes 若 Token 进房权限过期且未及时更新： <br>
 *        + 用户此时尝试进房会收到 rtcRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #ByteRTCAudioRoomDelegate#rtcRoom:onRoomStateChanged:withUid:state:extraInfo:} 回调，提示错误码为 `-1000` Token 无效； <br>
 *        + 用户已在房间内则会被移出房间，本地用户会收到 rtcRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #ByteRTCAudioRoomDelegate#rtcRoom:onRoomStateChanged:withUid:state:extraInfo:} 回调，提示错误码为 `-1009` Token 过期，同时远端用户会收到 rtcRoom:onUserLeave:reason:{@link #ByteRTCAudioRoomDelegate#rtcRoom:onUserLeave:reason:} 回调，提示原因为 `2` Token 进房权限过期。
 */
- (void)onTokenWillExpire:(ByteRTCAudioRoom *_Nonnull)rtcRoom;
/** 
 * @type callback
 * @brief Token 发布权限过期前 30 秒将触发该回调。<br>
 *        收到该回调后，你需调用 updateToken:{@link #ByteRTCAudioRoom#updateToken:} 更新 Token 发布权限。
 * @notes 若收到该回调后未及时更新 Token，Token 发布权限过期后： <br>
 *        + 此时尝试发布流会收到 rtcRoom:onStreamStateChanged:withUid:state:extraInfo:{@link #ByteRTCAudioRoomDelegate#rtcRoom:onStreamStateChanged:withUid:state:extraInfo:} 回调，提示错误码为 `-1002` 没有发布权限； <br>
 *        + 已在发布中的流会停止发布，发布端会收到 rtcRoom:onStreamStateChanged:withUid:state:extraInfo:{@link #ByteRTCAudioRoomDelegate#rtcRoom:onStreamStateChanged:withUid:state:extraInfo:} 回调，提示错误码为 `-1002` 没有发布权限，同时远端用户会收到 rtcRoom:onUserUnPublishStream:reason:{@link #ByteRTCAudioRoomDelegate#rtcRoom:onUserUnPublishStream:reason:} 回调，提示原因为 `6` 发流端发布权限过期。
 */
- (void)onPublishPrivilegeTokenWillExpire:(ByteRTCAudioRoom *_Nonnull)rtcRoom;
/** 
 * @type callback
 * @brief Token 订阅权限过期前 30 秒将触发该回调。<br>
 *        收到该回调后，你需调用 updateToken:{@link #ByteRTCAudioRoom#updateToken:} 更新 Token 订阅权限有效期。
 * @notes 若收到该回调后未及时更新 Token，Token 订阅权限过期后，尝试新订阅流会失败，已订阅的流会取消订阅，并且会收到 rtcRoom:onStreamStateChanged:withUid:state:extraInfo:{@link #ByteRTCAudioRoomDelegate#rtcRoom:onStreamStateChanged:withUid:state:extraInfo:} 回调，提示错误码为 `-1003` 没有订阅权限。
 */
- (void)onSubscribePrivilegeTokenWillExpire:(ByteRTCAudioRoom *_Nonnull)rtcRoom;

/** 
 * @type callback
 * @region 多房间
 * @brief 房间内通话统计信息回调。   <br>
 *        用户进房开始通话后，每 2s 收到一次本回调。
 * @param rtcRoom ByteRTCAudioRoom 对象。
 * @param stats 当前 RTCRoom 统计数据，详见：ByteRTCRoomStats{@link #ByteRTCRoomStats}
 */
- (void)rtcRoom:(ByteRTCAudioRoom * _Nonnull)rtcRoom onRoomStats:(ByteRTCRoomStats * _Nonnull)stats;
/** 
 * @type callback
 * @region 多房间
 * @brief 远端可见用户加入房间，或房内隐身用户切换为可见的回调。<br>
 *        1. 远端用户调用 setUserVisibility:{@link #ByteRTCAudioRoom#setUserVisibility:} 方法将自身设为可见后加入房间时，房间内其他用户将收到该事件。  <br>
 *        2. 远端可见用户断网后重新连入房间时，房间内其他用户将收到该事件。  <br>
 *        3. 房间内隐身远端用户调用 setUserVisibility:{@link #ByteRTCAudioRoom#setUserVisibility:} 方法切换至可见时，房间内其他用户将收到该事件。  <br>
 *        4. 新进房用户会收到进房前已在房内的可见用户的进房回调通知。  <br>
 * @param rtcRoom ByteRTCAudioRoom 对象。  <br>
 * @param userInfo 用户信息，参看 ByteRTCUserInfo{@link #ByteRTCUserInfo}。  <br>
 * @param elapsed 保留字段，无意义
 */
- (void)rtcRoom:(ByteRTCAudioRoom * _Nonnull)rtcRoom onUserJoined:(ByteRTCUserInfo * _Nonnull)userInfo
        elapsed:(NSInteger)elapsed;
/** 
 * @type callback
 * @brief 远端用户离开房间，或切至不可见时，本地用户会收到此事件
 * @param rtcRoom ByteRTCAudioRoom 对象。  <br>
 * @param uid 离开房间，或切至隐身的远端用户 ID 。  <br>
 * @param reason 用户离开房间的原因，参看 ByteRTCUserOfflineReason{@link #ByteRTCUserOfflineReason}。  <br>
 *        + 0: 远端用户调用 leaveRoom{@link #ByteRTCAudioRoom#leaveRoom} 主动退出房间。  <br>
 *        + 1: 远端用户因 Token 过期或网络原因等掉线。 详细信息请参看[连接状态提示](https://www.volcengine.com/docs/6348/95376)<br>
 *        + 2: 远端用户调用 setUserVisibility:{@link #ByteRTCAudioRoom#setUserVisibility:} 切换至不可见状态。 <br>
 *        + 3: 服务端调用 OpenAPI 将远端用户踢出房间。
 */
- (void)rtcRoom:(ByteRTCAudioRoom * _Nonnull)rtcRoom onUserLeave:(NSString * _Nonnull)uid
         reason:(ByteRTCUserOfflineReason)reason;

/** 
 * @type callback
 * @brief 加入房间并发布或订阅流后， 以每 2 秒一次的频率，报告本地用户和已订阅的远端用户的上下行网络质量信息。
 * @param rtcRoom ByteRTCRoom 对象
 * @param localQuality 本端网络质量，详见 ByteRTCNetworkQualityStats{@link #ByteRTCNetworkQualityStats}。
 * @param remoteQualities 已订阅用户的网络质量，详见 ByteRTCNetworkQualityStats{@link #ByteRTCNetworkQualityStats}。
 * @notes 更多通话中的监测接口，详见[通话中质量监测](https://www.volcengine.com/docs/6348/106866)。
 */
- (void)rtcRoom:(ByteRTCAudioRoom * _Nonnull)rtcRoom onNetworkQuality:(ByteRTCNetworkQualityStats *_Nonnull)localQuality remoteQualities:(NSArray<ByteRTCNetworkQualityStats*> *_Nonnull)remoteQualities;

#pragma mark - Stream Delegate Methods
/** 
 * @type callback
 * @region 房间管理
 * @brief 房间内新增远端麦克风采集的音频流的回调。
 * @param rtcRoom ByteRTCAudioRoom 实例
 * @param userId 远端流发布用户的用户 ID。
 * @notes 当房间内的远端用户调用 publishStream{@link #ByteRTCAudioRoom#publishStream} 成功发布由麦克风采集的音频流时，本地用户会收到该回调，此时本地用户可以自行选择是否调用 subscribeStream:{@link #ByteRTCAudioRoom#subscribeStream:} 订阅此流。
 */
- (void)rtcRoom:(ByteRTCAudioRoom * _Nonnull)rtcRoom onUserPublishStream:(NSString *_Nonnull)userId;
/** 
 * @type callback
 * @region 房间管理
 * @brief 房间内远端麦克风采集的音频流移除的回调。
 * @param rtcRoom ByteRTCAudioRoom 实例
 * @param userId 移除的远端流发布用户的用户 ID。  <br>
 * @param reason 远端流移除的原因，参看 ByteRTCStreamRemoveReason{@link #ByteRTCStreamRemoveReason}。
 * @notes 收到该回调通知后，你可以自行选择是否调用 unsubscribeStream:{@link #ByteRTCAudioRoom#unsubscribeStream:} 取消订阅此流。
 */
- (void)rtcRoom:(ByteRTCAudioRoom * _Nonnull)rtcRoom onUserUnPublishStream:(NSString *_Nonnull)userId
         reason:(ByteRTCStreamRemoveReason)reason;
/** 
 * @type callback
 * @region 多房间
 * @brief 本地流数据统计以及网络质量回调。  <br>
 *        本地用户发布流成功后，SDK 会周期性（2s）的通过此回调事件通知用户发布的流在此次统计周期内的质量统计信息。  <br>
 *        统计信息通过 ByteRTCLocalStreamStats{@link #ByteRTCLocalStreamStats} 类型的回调参数传递给用户，其中包括发送音频比特率、发送帧率、编码帧率，网络质量等。  <br>
 * @param rtcRoom ByteRTCAudioRoom 对象。  <br>
 * @param stats  当前房间本地流数据统计。详见：ByteRTCLocalStreamStats{@link #ByteRTCLocalStreamStats} <br>
 */
- (void)rtcRoom:(ByteRTCAudioRoom * _Nonnull)rtcRoom onLocalStreamStats:(ByteRTCLocalStreamStats * _Nonnull)stats;
/** 
 * @type callback
 * @region 多房间
 * @brief 本地订阅的远端音频流数据统计以及网络质量回调。  <br>
 *        本地用户订阅流成功后，SDK 会周期性（2s）的通过此回调事件通知用户订阅的流在此次统计周期内的质量统计信息，包括：发送音频比特率、发送帧率、编码帧率，网络质量等。
 * @param rtcRoom ByteRTCAudioRoom 对象。
 * @param stats 当前房间本地流数据统计。 详见：ByteRTCRemoteStreamStats{@link #ByteRTCRemoteStreamStats}
 */
- (void)rtcRoom:(ByteRTCAudioRoom * _Nonnull)rtcRoom onRemoteStreamStats:(ByteRTCRemoteStreamStats * _Nonnull)stats;
/** 
 * @type callback
 * @region 音频事件回调
 * @brief 通过调用服务端 BanUserStream/UnbanUserStream 方法禁用/解禁指定房间内指定用户音频流的发送时，触发此回调。
 * @param uid 被禁用/解禁的音频流用户 ID
 * @param banned 音频流发送状态 <br>
 *        + true: 音频流发送被禁用 <br>
 *        + false: 音频流发送被解禁
 * @notes  <br>
 *        + 房间内指定用户被禁止/解禁音频流发送时，房间内所有用户都会收到该回调。  <br>
 *        + 若被封禁用户断网或退房后再进房，则依然是封禁状态，且房间内所有人会再次收到该回调。  <br>
 *        + 指定用户被封禁后，房间内其他用户退房后再进房，会再次收到该回调。  <br>
 *        + 在控制台开启大会模式后，只有被封禁/解禁用户会收到该回调。
 */
- (void)rtcRoom:(ByteRTCAudioRoom * _Nonnull)rtcRoom
        onAudioStreamBanned:(NSString * _Nonnull)uid isBanned:(BOOL)banned;
#pragma mark - Message Delegate Methods
 /** 
  * @type callback
  * @region 多房间
  * @brief 收到房间中调用 sendRoomMessage:{@link #ByteRTCAudioRoom#sendRoomMessage:} 发送的广播文本消息时，收到此回调。
  * @param rtcRoom ByteRTCAudioRoom 对象
  * @param uid 消息发送者 ID 。
  * @param message 收到的文本消息内容。
  */
 - (void)rtcRoom:(ByteRTCAudioRoom * _Nonnull)rtcRoom onRoomMessageReceived:(NSString * _Nonnull)uid
        message:(NSString * _Nonnull)message;
 /** 
  * @type callback
  * @region 多房间
  * @brief 收到房间中调用 sendRoomBinaryMessage:{@link #ByteRTCAudioRoom#sendRoomBinaryMessage:} 发送的广播二进制消息时，收到此回调。
  * @param rtcRoom ByteRTCAudioRoom 对象
  * @param uid 消息发送者 ID 。
  * @param message 收到的二进制消息内容。
  */
 - (void)rtcRoom:(ByteRTCAudioRoom * _Nonnull)rtcRoom onRoomBinaryMessageReceived:(NSString * _Nonnull)uid
        message:(NSData * _Nonnull)message;
 /** 
  * @type callback
  * @region 多房间
  * @brief 收到来自房间中其他用户通过 sendUserMessage:message:config:{@link #ByteRTCAudioRoom#sendUserMessage:message:config:} 发来的文本消息时（P2P），会收到此回调。
  * @param rtcRoom ByteRTCAudioRoom 对象
  * @param uid 消息发送者的用户 ID 。
  * @param message 收到的文本消息内容。
  */
 - (void)rtcRoom:(ByteRTCAudioRoom * _Nonnull)rtcRoom onUserMessageReceived:(NSString * _Nonnull)uid
        message:(NSString * _Nonnull)message;
/** 
 * @type callback
 * @region 多房间
 * @brief 收到来自房间中其他用户通过 sendUserBinaryMessage:message:config:{@link #ByteRTCAudioRoom#sendUserBinaryMessage:message:config:} 发来的二进制消息时，会收到此回调。
 * @param rtcRoom ByteRTCAudioRoom 对象
 * @param uid 消息发送者的用户 ID 。
 * @param message 收到的二进制消息内容。
 */
- (void)rtcRoom:(ByteRTCAudioRoom * _Nonnull)rtcRoom onUserBinaryMessageReceived:(NSString * _Nonnull)uid
        message:(NSData * _Nonnull)message;
 /** 
  * @type callback
  * @region 多房间
  * @brief 向房间内单个用户发送文本或二进制消息后（P2P），消息发送方会收到该消息发送结果回调。
  * @param rtcRoom ByteRTCAudioRoom 对象。
  * @param msgid 本条消息的 ID。
  * @param error 消息发送结果，详见 ByteRTCUserMessageSendResult{@link #ByteRTCUserMessageSendResult}
  * @notes  <br>
  *        + 你应调用 sendUserMessage:message:config:{@link #ByteRTCAudioRoom#sendUserMessage:message:config:} 向房间内单个用户发送文本消息 <br>
  *        + 你应调用 sendUserBinaryMessage:message:config:{@link #ByteRTCAudioRoom#sendUserBinaryMessage:message:config:} 向房间内单个用户发送二进制消息
  */
 - (void)rtcRoom:(ByteRTCAudioRoom * _Nonnull)rtcRoom onUserMessageSendResult:(int64_t)msgid
          error:(ByteRTCUserMessageSendResult)error;
 /** 
  * @type callback
  * @region 多房间
  * @brief 向房间内所有用户群发文本或二进制消息后，消息发送方会收到该消息发送结果回调。
  * @param rtcRoom ByteRTCAudioRoom 对象。
  * @param msgid 本条消息的 ID。
  * @param error 消息发送结果，详见 ByteRTCRoomMessageSendResult{@link #ByteRTCRoomMessageSendResult}
  * @notes  <br>
  *        + 你应调用 sendRoomMessage:{@link #ByteRTCAudioRoom#sendRoomMessage:} 向房间内群发文本消息 <br>
  *        + 你应调用 sendRoomBinaryMessage:{@link #ByteRTCAudioRoom#sendRoomBinaryMessage:} 向房间内群发二进制消息
  */
 - (void)rtcRoom:(ByteRTCAudioRoom * _Nonnull)rtcRoom onRoomMessageSendResult:(int64_t)msgid
          error:(ByteRTCRoomMessageSendResult)error;

#pragma mark - ForwardStream Delegate Methods
/** 
 * @type callback
 * @region 多房间
 * @brief 跨房间音频流转发状态和错误回调
 * @param rtcRoom ByteRTCAudioRoom 对象
 * @param infos 跨房间音频流转发目标房间信息数组，详见 ForwardStreamStateInfo{@link #ForwardStreamStateInfo}
 */
- (void)rtcRoom:(ByteRTCAudioRoom * _Nonnull)rtcRoom
        onForwardStreamStateChanged:(NSArray<ForwardStreamStateInfo *> * _Nonnull)infos;
/** 
 * @type callback
 * @region 多房间
 * @brief 跨房间音频流转发事件回调
 * @param rtcRoom ByteRTCAudioRoom 对象
 * @param infos 跨房间音频流转发目标房间事件数组，详见 ForwardStreamEventInfo{@link #ForwardStreamEventInfo}
 */
- (void)rtcRoom:(ByteRTCAudioRoom * _Nonnull)rtcRoom
        onForwardStreamEvent:(NSArray<ForwardStreamEventInfo *> * _Nonnull)infos;
@end

#pragma mark - Other
/** 
 * @type keytype
 * @brief 多房间参数配置
 */
BYTERTC_APPLE_EXPORT @interface AudioRoomConfig : NSObject
/** 
 * @brief 房间模式，参看 ByteRTCRoomProfile{@link #ByteRTCRoomProfile}，默认为 `ByteRTCRoomProfileCommunication`，进房后不可更改。
 */
@property(nonatomic) ByteRTCRoomProfile profile;
/** 
 * @brief 是否自动订阅音频流，默认为自动订阅。
 */
@property(assign, nonatomic) BOOL isAutoSubscribeAudio;
/** 
 * @brief 是否自动发布音频流，默认为自动发布。 <br>
 *        若调用 setUserVisibility:{@link #ByteRTCAudioRoom#setUserVisibility:} 将自身可见性设为 false，无论是默认的自动发布流还是手动设置的自动发布流都不会进行发布，你需要将自身可见性设为 true 后方可发布。  <br>
 *        多房间场景下，若已在其中一个房间成功设置了自动发布，其他房间的自动发布设置均不会生效。若每个房间均不做设置，则默认在第一个加入的房间内自动发布流。
 */
@property(assign, nonatomic) BOOL isAutoPubAudio;
@end

#pragma mark - ByteRTCAudioRoom
/**
 * @type api
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCAudioRoom : NSObject
/**
 * @hidden
 */
@property(nonatomic, weak) id<ByteRTCAudioRoomDelegate> _Nullable delegate;

#pragma mark - Core Methods
/** 
 * @type api
 * @region 多房间
 * @brief 退出并销毁调用 createRTCRoom:{@link #ByteRTCAudio#createRTCRoom:} 所创建的房间实例。
 */
- (void)destroy;
/** 
 * @hidden
 * @deprecated
 * @type api
 * @region 多房间
 * @brief 获取房间 ID
 */
- (NSString *_Nullable)getRoomId;
/** 
 * @type api
 * @region 多房间
 * @brief 通过设置 ByteRTCAudioRoomDelegate{@link #ByteRTCAudioRoomDelegate} 代理，可以监听此 `ByteRTCAudioRoom` 对象对应的回调事件。
 * @param roomDelegate 参见 ByteRTCAudioRoomDelegate{@link #ByteRTCAudioRoomDelegate}。
 */
- (void)setRTCRoomDelegate:(id<ByteRTCAudioRoomDelegate> _Nullable)roomDelegate;
/** 
 * @type api
 * @region 多房间
 * @brief 加入房间。<br>
 *        调用 createRTCRoom:{@link #ByteRTCAudio#createRTCRoom:} 创建房间后，调用此方法加入房间，同房间内其他用户进行音频通话。  <br>
 * @param token 动态密钥，用于对进房用户进行鉴权验证。  <br>
 *        进入房间需要携带 Token。测试时可使用控制台生成临时 Token，正式上线需要使用密钥 SDK 在你的服务端生成并下发 Token。Token 有效期及生成方式参看[使用 Token 完成鉴权](70121)。  <br>
 *        使用不同 AppID 的 App 是不能互通的。  <br>
 *        请务必保证生成 Token 使用的 AppID 和创建引擎时使用的 AppID 相同，否则会导致加入房间失败。具体失败原因会通过 rtcRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #ByteRTCAudioRoomDelegate#rtcRoom:onRoomStateChanged:withUid:state:extraInfo:} 回调告知。  <br>
 * @param userInfo 用户信息。参看 ByteRTCUserInfo{@link #ByteRTCUserInfo}。  <br>
 * @param roomConfig 房间参数配置，设置房间模式以及是否自动发布或订阅流。具体配置模式参看 AudioRoomConfig{@link #AudioRoomConfig}。  <br>
 * @return 方法调用结果。  <br>
 *        +  0: 成功  <br>
 *        + -1: 参数无效  <br>
 *        + -2: 已经在房间内。接口调用成功后，只要收到返回值为 0 ，且未调用 leaveRoom{@link #ByteRTCAudioRoom#leaveRoom} 成功，则再次调用进房接口时，无论填写的房间 ID 和用户 ID 是否重复，均触发此返回值。  <br>
 *        + -3: room 为空 <br>
 * @notes  <br>
 *        + 同一个 AppID 的同一个房间内，每个用户的用户 ID 必须是唯一的。如果两个用户的用户 ID 相同，则后加入房间的用户会将先加入房间的用户踢出房间，并且先加入房间的用户会收到 rtcRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #ByteRTCAudioRoomDelegate#rtcRoom:onRoomStateChanged:withUid:state:extraInfo:} 回调通知，错误类型为重复登录 ByteRTCErrorCodeDuplicateLogin。  <br>
 *        + 本地用户调用此方法加入房间成功后，会收到 rtcRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #ByteRTCAudioRoomDelegate#rtcRoom:onRoomStateChanged:withUid:state:extraInfo:} 回调通知。若本地用户同时为可见用户，加入房间时远端用户会收到 rtcRoom:onUserJoined:elapsed:{@link #ByteRTCAudioRoomDelegate#rtcRoom:onUserJoined:elapsed:} 回调通知。关于可见性设置参看 setUserVisibility:{@link #ByteRTCAudioRoom#setUserVisibility:}。  <br>
 *        + 用户加入房间成功后，在本地网络状况不佳的情况下，SDK 可能会与服务器失去连接，并触发 rtcEngine:onConnectionStateChanged:{@link #ByteRTCAudioDelegate#rtcEngine:onConnectionStateChanged:} 回调。此时 SDK 会自动重试，直到成功重连。重连成功后，本地会收到 rtcRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #ByteRTCAudioRoomDelegate#rtcRoom:onRoomStateChanged:withUid:state:extraInfo:} 回调通知。
 */
- (int)joinRoom:(NSString *_Nullable)token userInfo:(ByteRTCUserInfo * _Nonnull)userInfo
            roomConfig:(AudioRoomConfig * _Nonnull)roomConfig;

/** 
 * @type api
 * @region 多房间
 * @brief 设置用户可见性。未调用该接口前，本地用户默认对他人可见。  <br>
 * @param enable 设置用户是否对房间内其他用户可见：  <br>
 *        + true: 可以在房间内发布音频流，房间中的其他用户将收到用户的行为通知，例如进房、开启音频采集和退房。  <br>
 *        + false: 不可以在房间内发布音频流，房间中的其他用户不会收到用户的行为通知，例如进房、开启音频采集和退房。
 * @notes  <br>
 *       + 该方法在加入房间前后均可调用。 <br>
 *       + 在房间内调用此方法，房间内其他用户会收到相应的回调通知：<br>
 *            - 从 false 切换至 true 时，房间内其他用户会收到 rtcRoom:onUserJoined:elapsed:{@link #ByteRTCAudioRoomDelegate#rtcRoom:onUserJoined:elapsed:} 回调通知；  <br>
 *            - 从 true 切换至 false 时，房间内其他用户会收到 rtcRoom:onUserLeave:reason:{@link #ByteRTCAudioRoomDelegate#rtcRoom:onUserLeave:reason:} 回调通知。  <br>
 *       + 若调用该方法将可见性设为 false，此时尝试发布流会收到 `ByteRTCWarningCodeSubscribeStreamForbiden` 警告。
 */
- (void)setUserVisibility:(BOOL)enable;
/** 
 * @type api
 * @region 房间管理
 * @brief 离开房间。 <br>
 *        用户调用此方法离开房间，结束通话过程，释放所有通话相关的资源。
 * @notes 可见的用户离开房间后，房间内其他用户会收到 rtcRoom:onUserLeave:reason:{@link #ByteRTCAudioRoomDelegate#rtcRoom:onUserLeave:reason:} 回调通知；  <br>
 */
- (void)leaveRoom;
/** 
 * @type api
 * @brief 更新 Token。
 *        Token 中同时包含进房、发布和订阅权限，各权限有一定的有效期，并且到期前 30 秒会触发回调，提示用户更新 Token 相关权限。此时需要重新获取 Token，并调用此方法更新 Token，以保证通话的正常进行。
 * @param token 重新获取的有效 Token。
 *        如果传入的 Token 无效，回调错误码为 ByteRTCErrorCode{@link #ByteRTCErrorCode} 中的 `-1010` 提示传入的 Token 无效。
 * @return <br>
 *        + 0：成功；
 *        + !0：失败。
 * @notes 请勿同时调用 updateToken:{@link #ByteRTCAudioRoom#updateToken:} 和 joinRoom:userInfo:roomConfig:{@link #ByteRTCAudioRoom#joinRoom:userInfo:roomConfig:} 方法更新 Token。若因 Token 过期或无效导致加入房间失败或已被移出房间，你应该在获取新的有效 Token 后调用 joinRoom:userInfo:roomConfig:{@link #ByteRTCAudioRoom#joinRoom:userInfo:roomConfig:} 重新加入房间。
 */
- (int)updateToken:(NSString *_Nullable)token;

#pragma mark - Stream Methods
/** 
 * @type api
 * @region 房间管理
 * @brief 在当前所在房间内发布本地通过麦克风采集的音频流
 * @notes <br>
 *        + 如果你已经在用户进房时通过调用 joinRoom:userInfo:roomConfig:{@link #ByteRTCAudioRoom#joinRoom:userInfo:roomConfig:} 成功选择了自动发布，则无需再调用本接口。<br>
 *        + 调用 setUserVisibility:{@link #ByteRTCAudioRoom#setUserVisibility:} 方法将自身设置为不可见后无法调用该方法，需将自身切换至可见后方可调用该方法发布音频流。 <br>
 *        + 如果你需要向多个房间发布流，调用 startForwardStreamToRooms:{@link #ByteRTCAudioRoom#startForwardStreamToRooms:}。  <br>
 *        + 调用此方法后，房间中的所有远端用户会收到 rtcRoom:onUserPublishStream:{@link #ByteRTCAudioRoomDelegate#rtcRoom:onUserPublishStream:} 回调通知，其中成功收到了音频流的远端用户会收到 rtcEngine:onFirstRemoteAudioFrame:{@link #ByteRTCAudioDelegate#rtcEngine:onFirstRemoteAudioFrame:} 回调。<br>
 *        + 调用 unpublishStream{@link #ByteRTCAudioRoom#unpublishStream} 取消发布。
 */
- (void)publishStream;
/** 
 * @type api
 * @region 房间管理
 * @brief 停止将本地麦克风采集的音频流发布到当前所在房间中
 * @notes  <br>
 *        + 调用 publishStream{@link #ByteRTCAudioRoom#publishStream} 手动发布麦克风音频流后，你需调用此接口停止发布。<br>
 *        + 调用此方法停止发布音频流后，房间中的其他用户将会收到 rtcRoom:onUserUnPublishStream:reason: {@link #ByteRTCAudioRoomDelegate#rtcRoom:onUserUnPublishStream:reason:} 回调通知。
 */
- (void)unpublishStream;
/** 
 * @type api
 * @region 房间管理
 * @brief 订阅房间内指定的通过麦克风采集的音频流。  <br>
 *        该方法对自动订阅和手动订阅模式均适用。
 * @param userId 指定订阅的远端发布音频流的用户 ID。
 * @notes  <br>
 *        + 你必须先通过 rtcRoom:onUserPublishStream:{@link #ByteRTCAudioRoomDelegate#rtcRoom:onUserPublishStream:} 回调获取当前房间里的远端摄像头音频流信息，然后调用本方法按需订阅。  <br>
 *        + 成功订阅远端用户的媒体流后，订阅关系将持续到调用 unsubscribeStream:{@link #ByteRTCAudioRoom#unsubscribeStream:} 取消订阅或本端用户退房。 <br>
 *        + 关于其他调用异常，你会收到 rtcRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #ByteRTCAudioRoom#rtcRoom:onRoomStateChanged:withUid:state:xtraInfo:} 回调通知，具体异常原因参看 ByteRTCErrorCode{@link #ByteRTCErrorCode}。
 */
- (int)subscribeStream:(NSString *_Nonnull)userId;
/** 
 * @type api
 * @region 房间管理
 * @brief 取消订阅房间内指定的通过麦克风采集的音频流。  <br>
 *        该方法对自动订阅和手动订阅模式均适用。
 * @param userId 指定取消订阅的远端发布音频流的用户 ID。
 * @notes  <br>
 *        + 关于其他调用异常，你会收到 rtcRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #ByteRTCAudioRoom#rtcRoom:onRoomStateChanged:withUid:state:xtraInfo:} 回调通知，具体失败原因参看 ByteRTCErrorCode{@link #ByteRTCErrorCode}。
 */
- (int)unsubscribeStream:(NSString *_Nonnull)userId;
/** 
 * @type api
 * @region 多房间
 * @brief 暂停接收来自远端的音频流
 * @notes <br>
 *        + 该方法仅暂停远端流的接收，并不影响远端流的采集和发送；  <br>
 *        + 该方法不改变用户的订阅状态以及订阅流的属性。  <br>
 *        + 若想恢复接收远端流，需调用 resumeAllSubscribedStream{@link #ByteRTCAudioRoom#resumeAllSubscribedStream}。 <br>
 *        + 多房间场景下，仅暂停接收发布在当前所在房间的流。
 */
- (void)pauseAllSubscribedStream;
/** 
 * @type api
 * @region 多房间
 * @brief 恢复接收来自远端的音频流
 * @notes <br>
 *        + 该方法仅恢复远端流的接收，并不影响远端流的采集和发送；  <br>
 *        + 该方法不改变用户的订阅状态以及订阅流的属性。
 */
- (void)resumeAllSubscribedStream;

#pragma mark - Message Methods
 /** 
  * @type api
  * @region 多房间
  * @brief 给房间内指定的用户发送文本消息（P2P）。
  * @param userId  <br>
  *        消息接收用户的 ID
  * @param message  <br>
  *        发送的文本消息内容。  <br>
  *        消息不超过 64 KB。
  * @param config   <br>
  *        消息发送的可靠/有序类型，参看 ByteRTCMessageConfig{@link #ByteRTCMessageConfig}  <br>
  * @notes  <br>
  * @return 这次发送消息的编号，从 1 开始递增。
  * @notes  <br>
  *      + 在发送房间内文本消息前，必须先调用 joinRoom:userInfo:roomConfig:{@link #ByteRTCAudioRoom#joinRoom:userInfo:roomConfig:} 加入房间。  <br>
  *      + 调用该函数后会收到一次 rtcRoom:onUserMessageSendResult:error:{@link #ByteRTCAudioRoomDelegate#rtcRoom:onUserMessageSendResult:error:} 回调，通知消息发送方发送成功或失败。  <br>
  *      + 若文本消息发送成功，则 uid 所指定的用户会收到 rtcRoom:onUserMessageReceived:message:{@link #ByteRTCAudioRoomDelegate#rtcRoom:onUserMessageReceived:message:} 回调。
  */
 - (int64_t)sendUserMessage:(NSString * _Nonnull)userId message:(NSString * _Nonnull)message config:(ByteRTCMessageConfig)config;
 /** 
  * @type api
  * @region 多房间
  * @brief 给房间内指定的用户发送二进制消息（P2P）。
  * @param uid 消息接收用户的 ID
  * @param message 发送的二进制消息内容。消息不超过 46KB。
  * @param config 消息发送的可靠/有序类型，参看 ByteRTCMessageConfig{@link #ByteRTCMessageConfig}  <br>
  * @return 这次发送消息的编号，从 1 开始递增。
  * @notes  <br>
  *      + 在发送房间内二进制消息前，必须先调用 joinRoom:userInfo:roomConfig:{@link #ByteRTCAudioRoom#joinRoom:userInfo:roomConfig:} 加入房间。  <br>
  *      + 调用该函数后会收到一次 rtcRoom:onUserMessageSendResult:error:{@link #ByteRTCAudioRoomDelegate#rtcRoom:onUserMessageSendResult:error:} 回调，通知消息发送方发送成功或失败；  <br>
  *      + 若二进制消息发送成功，则 uid 所指定的用户会收到 rtcRoom:onUserBinaryMessageReceived:message:{@link #ByteRTCAudioRoomDelegate#rtcRoom:onUserBinaryMessageReceived:message:} 回调。
  */
 - (int64_t)sendUserBinaryMessage:(NSString * _Nonnull)uid message:(NSData * _Nonnull)message config:(ByteRTCMessageConfig)config;
 /** 
  * @type api
  * @region 多房间
  * @brief 给房间内的所有其他用户发送文本消息。
  * @param message  <br>
  *        发送的文本消息内容。  <br>
  *        消息不超过 64 KB。
  * @return 这次发送消息的编号，从 1 开始递增。
  * @notes  <br>
  *      + 在发送房间内文本消息前，必须先调用 joinRoom:userInfo:roomConfig:{@link #ByteRTCAudioRoom#joinRoom:userInfo:roomConfig:} 加入房间。  <br>
  *      + 调用该函数后会收到一次 rtcRoom:onRoomMessageSendResult:error:{@link #ByteRTCAudioRoomDelegate#rtcRoom:onRoomMessageSendResult:error:} 回调，通知消息发送方发送成功或失败；  <br>
  *      + 若文本消息发送成功，则房间内远端用户会收到 rtcRoom:onRoomMessageReceived:message:{@link #ByteRTCAudioRoomDelegate#rtcRoom:onRoomMessageReceived:message:} 回调。
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
  *      + 在房间内广播二进制消息前，必须先调用 joinRoom:userInfo:roomConfig:{@link #ByteRTCAudioRoom#joinRoom:userInfo:roomConfig:} 加入房间。  <br>
  *      + 调用该函数后会收到一次 rtcRoom:onRoomMessageSendResult:error:{@link #ByteRTCAudioRoomDelegate#rtcRoom:onRoomMessageSendResult:error:} 回调，通知消息发送方发送成功或失败；  <br>
  *      + 若二进制消息发送成功，则房间内所有用户会收到 rtcRoom:onRoomBinaryMessageReceived:message:{@link #ByteRTCAudioRoomDelegate#rtcRoom:onRoomBinaryMessageReceived:message:} 回调。
  */
 - (int64_t)sendRoomBinaryMessage:(NSData *  _Nonnull)message;

#pragma mark - ForwardStream Methods
/** 
 * @type api
 * @region 多房间
 * @brief 开始跨房间转发音频流。
 *        在用户进入房间后调用本接口，实现向多个房间转发音频流，适用于跨房间连麦等场景。<br>
 * @param configurations 跨房间音频流转发指定房间的信息。参看 ForwardStreamConfiguration{@link #ForwardStreamConfiguration}。
 * @return  <br>
 *        0: 方法调用成功
 *        <0: 方法调用失败  <br>
 * @notes <br>
 *        + 调用本方法后，将在本端触发 rtcRoom:onForwardStreamStateChanged:{@link #ByteRTCAudioRoomDelegate#rtcRoom:onForwardStreamStateChanged:} 回调。
 *        + 调用本方法后，你可以通过监听 rtcRoom:onForwardStreamEvent:{@link #ByteRTCAudioRoomDelegate#rtcRoom:onForwardStreamEvent:} 回调来获取各个目标房间在转发音频流过程中的相关事件。
 *        + 开始转发后，目标房间中的用户将接收到本地用户进房 rtcRoom:onUserJoined:elapsed:{@link #ByteRTCAudioRoomDelegate#rtcRoom:onUserJoined:elapsed:} 和发流 rtcRoom:onUserPublishStream:{@link #ByteRTCAudioRoomDelegate#rtcRoom:onUserPublishStream:} 的回调。
 *        + 调用本方法后，可以调用 updateForwardStreamToRooms:{@link #ByteRTCAudioRoom#updateForwardStreamToRooms:} 更新目标房间信息，例如，增加或减少目标房间等。
 *        + 调用本方法后，可以调用 stopForwardStreamToRooms{@link #ByteRTCAudioRoom#stopForwardStreamToRooms} 停止向所有房间转发音频流。
 *        + 调用本方法后，可以调用 pauseForwardStreamToAllRooms{@link #ByteRTCAudioRoom#pauseForwardStreamToAllRooms} 暂停向所有房间转发音频流。
 */
- (int)startForwardStreamToRooms:(NSArray <ForwardStreamConfiguration *> * _Nullable)configurations;
/** 
 * @type api
 * @region 多房间
 * @brief 更新跨房间音频流转发信息。<br>
 *        通过 startForwardStreamToRooms:{@link #ByteRTCAudioRoom#startForwardStreamToRooms:} 发起音频流转发后，可调用本方法增加或者减少目标房间，或更新房间密钥。
 *        调用本方法增加或删减房间后，将在本端触发 rtcRoom:onForwardStreamStateChanged:{@link #ByteRTCAudioRoomDelegate#rtcRoom:onForwardStreamStateChanged:} 回调，包含发生了变动的目标房间中音频流转发状态。
 * @param configurations 跨房间音频流转发目标房间信息。参看 ForwardStreamConfiguration{@link #ForwardStreamConfiguration}。
 * @return  <br>
 *        + 0: 方法调用成功  <br>
 *        + <0: 方法调用失败
 * @notes <br>
 *        + 增加目标房间后，新增目标房间中的用户将接收到本地用户进房 rtcRoom:onUserJoined:elapsed:{@link #ByteRTCAudioRoomDelegate#rtcRoom:onUserJoined:elapsed:} 和发布 rtcRoom:onUserJoined:elapsed:{@link #ByteRTCAudioRoomDelegate#rtcRoom:onUserJoined:elapsed:} 的回调。
 *        + 删减目标房间后，原目标房间中的用户将接收到本地用户停止发布 rtcRoom:onUserUnPublishStream:reason:{@link #ByteRTCAudioRoomDelegate#rtcRoom:onUserUnPublishStream:reason:} 和退房 rtcRoom:onUserLeave:reason:{@link #ByteRTCAudioRoomDelegate#rtcRoom:onUserLeave:reason:} 的回调。
 */
- (int)updateForwardStreamToRooms:(NSArray <ForwardStreamConfiguration *> * _Nullable)configurations;
/** 
 * @type api
 * @region 多房间
 * @brief 停止跨房间音频流转发。
 *        通过 startForwardStreamToRooms:{@link #ByteRTCAudioRoom#startForwardStreamToRooms:} 发起音频流转发后，可调用本方法停止向所有目标房间转发音频流。
 * @notes <br>
 *        + 调用本方法后，将在本端触发 rtcRoom:onForwardStreamStateChanged:{@link #ByteRTCAudioRoomDelegate#rtcRoom:onForwardStreamStateChanged:} 回调。
 *        + 调用本方法后，原目标房间中的用户将接收到本地用户停止发布 rtcRoom:onUserUnPublishStream:reason:{@link #ByteRTCAudioRoomDelegate#rtcRoom:onUserUnPublishStream:reason:} 和退房 rtcRoom:onUserLeave:reason:{@link #ByteRTCAudioRoomDelegate#rtcRoom:onUserLeave:reason:} 的回调。
 *        + 如果需要停止向指定的房间转发音频流，请调用 updateForwardStreamToRooms:{@link #ByteRTCAudioRoom#updateForwardStreamToRooms:} 更新房间信息。
 *        + 如果需要暂停转发，请调用 pauseForwardStreamToAllRooms{@link #ByteRTCAudioRoom#pauseForwardStreamToAllRooms}，并在之后随时调用 resumeForwardStreamToAllRooms{@link #ByteRTCAudioRoom#resumeForwardStreamToAllRooms} 快速恢复转发。
 */
- (void)stopForwardStreamToRooms;
/** 
 * @type api
 * @region 多房间
 * @brief 暂停跨房间音频流转发。
 *        通过 startForwardStreamToRooms:{@link #ByteRTCAudioRoom#startForwardStreamToRooms:} 发起音频流转发后，可调用本方法暂停向所有目标房间转发音频流。
 *        调用本方法暂停向所有目标房间转发后，你可以随时调用 resumeForwardStreamToAllRooms{@link #ByteRTCAudioRoom#resumeForwardStreamToAllRooms} 快速恢复转发。
 * @notes 调用本方法后，目标房间中的用户将接收到本地用户停止发布 rtcRoom:onUserUnPublishStream:reason:{@link #ByteRTCAudioRoomDelegate#rtcRoom:onUserUnPublishStream:reason:} 和退房 rtcRoom:onUserLeave:reason:{@link #ByteRTCAudioRoomDelegate#rtcRoom:onUserLeave:reason:} 的回调。
 */
- (void)pauseForwardStreamToAllRooms;
/** 
 * @type api
 * @region 多房间
 * @brief 恢复跨房间音频流转发。
 *        调用 pauseForwardStreamToAllRooms{@link #ByteRTCAudioRoom#pauseForwardStreamToAllRooms} 暂停转发之后，调用本方法恢复向所有目标房间转发音频流。
 * @notes <br>
 *        目标房间中的用户将接收到本地用户进房 rtcRoom:onUserJoined:elapsed:{@link #ByteRTCAudioRoomDelegate#rtcRoom:onUserJoined:elapsed:} 和发布 rtcRoom:onUserJoined:elapsed:{@link #ByteRTCAudioRoomDelegate#rtcRoom:onUserJoined:elapsed:} 的回调。
 */
- (void)resumeForwardStreamToAllRooms;

/** 
 * @type api
 * @region 范围语音
 * @brief 获取范围语音接口实例。
 * @return 方法调用结果： <br>
 *        + ByteRTCRangeAudio：成功，返回一个 ByteRTCRangeAudio{@link #ByteRTCRangeAudio} 实例。  <br>
 *        + NULL：失败，当前 SDK 不支持范围语音功能。
 * @notes 首次调用该方法须在创建房间后、加入房间前。范围语音相关 API 和调用时序详见[范围语音](https://www.volcengine.com/docs/6348/114727)。 
 */
- (ByteRTCRangeAudio *_Nullable)getRangeAudio;

/** 
 * @type api
 * @region 空间音频
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
 * @region 多房间
 * @brief 调节某个房间内所有远端用户的音频播放音量。
 * @param volume 音频播放音量值和原始音量的比值，范围是 [0, 400]，单位为 %，自带溢出保护。为保证更好的通话质量，建议将 volume 值设为 [0,100]。 <br>
 *              + 0: 静音  <br>
 *              + 100: 原始音量，默认值  <br>
 *              + 400: 最大可为原始音量的 4 倍(自带溢出保护)  <br>
 * @notes 假设某远端用户 A 始终在被调节的目标用户范围内，<br>
 *        + 当该方法与 setRemoteAudioPlaybackVolume:remoteUid:playVolume:{@link #ByteRTCAudio#setRemoteAudioPlaybackVolume:remoteUid:playVolume:} 共同使用时，本地收听用户 A 的音量为后调用的方法设置的音量；<br>
 *        + 当该方法与 setPlaybackVolume:{@link #ByteRTCAudio#setPlaybackVolume:} 方法共同使用时，本地收听用户 A 的音量将为两次设置的音量效果的叠加。
 */
- (void)setRemoteRoomAudioPlaybackVolume:(NSInteger)volume;
@end
