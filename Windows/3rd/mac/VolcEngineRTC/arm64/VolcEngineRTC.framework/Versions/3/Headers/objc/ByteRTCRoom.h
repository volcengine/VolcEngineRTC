/*
 * Copyright (c) 2020 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC Room
*/

#import <CoreMedia/CMTime.h>
#import "rtc/ByteRTCDefines.h"
#import "rtc/ByteRTCRangeAudio.h"
#import "rtc/ByteRTCSpatialAudio.h"

@class ByteRTCRoom;

/** 
 * @type callback
 * @brief 房间事件回调接口
 * 注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。
 */
@protocol ByteRTCRoomDelegate <NSObject>
@optional

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
  * @param extraInfo 额外信息，如 `{"elapsed":1187,"join_type":0}`。
  *                  `join_type`表示加入房间的类型，`0`为首次进房，`1`为重连进房。
  *                  `elapsed`表示加入房间耗时，即本地用户从调用 joinRoom:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoom:userInfo:roomConfig:} 到加入房间成功所经历的时间间隔，单位为 ms。
  */
 - (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onRoomStateChanged:(NSString *_Nonnull)roomId
             withUid:(nonnull NSString *)uid
           state:(NSInteger)state
           extraInfo:(NSString *_Nonnull)extraInfo;

/** 
 * @type callback
 * @region 多房间
 * @brief 流状态改变回调，发生流相关的警告或错误时会收到此回调。
 * @param roomId 房间 ID。
 * @param uid 用户 ID。
 * @param state 流状态码，参看 ByteRTCErrorCode{@link #ByteRTCErrorCode} 及 ByteRTCWarningCode{@link #ByteRTCWarningCode}。
 * @param extraInfo 附加信息，目前为空。
 */
- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onStreamStateChanged:(NSString *_Nonnull)roomId
            withUid:(nonnull NSString *)uid
          state:(NSInteger)state
          extraInfo:(NSString *_Nonnull)extraInfo;

/** 
 * @type callback
 * @region 多房间
 * @brief 离开房间成功回调。  <br>
 *        用户调用 leaveRoom{@link #ByteRTCRoom#leaveRoom} 方法后，SDK 会停止所有的发布订阅流，并释放所有通话相关的音视频资源。SDK 完成所有的资源释放后通过此回调通知用户。  <br>
 * @param rtcRoom  ByteRTCRoom 对象。  <br>
 * @param stats 保留参数，目前为空。
 * @notes  <br>
 *       + 用户调用 leaveRoom{@link #ByteRTCRoom#leaveRoom} 方法离开房间后，如果立即调用 destroyRTCVideo{@link #ByteRTCVideo#destroyRTCVideo} 方法销毁 RTC 引擎，则将无法收到此回调事件。  <br>
 *       + 离开房间结束通话后，如果 App 需要使用系统音视频设备，则建议在收到此回调后再初始化音视频设备，否则可能由于 SDK 占用了导致 App 初始化音视频设备失败。  <br>
 */
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onLeaveRoom:(ByteRTCRoomStats *_Nonnull)stats;

 /** 
  * @deprecated since 3.41 and will be deleted in 3.51, use rtcRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onRoomStateChanged:withUid:state:extraInfo:} and rtcRoom:onStreamStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamStateChanged:withUid:state:extraInfo:} instead.
  * @type callback
  * @region 多房间
  * @brief 发生警告回调。  <br>
  *        SDK 运行时出现了警告。SDK 通常会自动恢复，警告信息可以忽略。
  * @param rtcRoom ByteRTCRoom 对象。
  * @param warningCode 警告码，详见枚举类型 ByteRTCWarningCode{@link #ByteRTCWarningCode} 。
  */
 - (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onRoomWarning:(ByteRTCWarningCode)warningCode __deprecated_msg("Will be removed in new version");

/** 
 * @deprecated since 3.41 and will be deleted in 3.51, use rtcRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onRoomStateChanged:withUid:state:extraInfo:} and rtcRoom:onStreamStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamStateChanged:withUid:state:extraInfo:} instead.
 * @type callback
 * @region 多房间
 * @brief 发生错误回调。  <br>
 *        SDK 运行时出现了错误。SDK 通常无法自动恢复，应用需要采取行动。
 * @param rtcRoom  ByteRTCRoom 对象。
 * @param errorCode 错误码，详见枚举类型 ByteRTCErrorCode{@link #ByteRTCErrorCode} 。
 */
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onRoomError:(ByteRTCErrorCode)errorCode __deprecated_msg("Will be removed in new version");

/** 
 * @type callback
 * @region 多房间
 * @brief 发布端调用 setMultiDeviceAVSync:{@link #ByteRTCRoom#setMultiDeviceAVSync:} 后音视频同步状态发生改变时，会收到此回调。
 * @param rtcRoom ByteRTCRoom 实例
 * @param state 音视频同步状态，参看 ByteRTCAVSyncState{@link #ByteRTCAVSyncState}。
 */
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onAVSyncStateChange:(ByteRTCAVSyncState)state;

/** 
 * @type callback
 * @region 多房间
 * @brief 房间内通话统计信息回调。   <br>
 *        用户进房开始通话后，每 2s 收到一次本回调。
 * @param rtcRoom  ByteRTCRoom 对象。
 * @param stats 当前 ByteRTCRoom 统计数据，详见：ByteRTCRoomStats{@link #ByteRTCRoomStats}
 */
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onRoomStats:(ByteRTCRoomStats *_Nonnull)stats NS_SWIFT_NAME(rtcRoom(_:onRoomStats:));

/** 
 * @type callback
 * @region 多房间
 * @brief 本地流数据统计以及网络质量回调。  <br>
 *        本地用户发布流成功后，SDK 会周期性（2s）的通过此回调事件通知用户发布的流在此次统计周期内的质量统计信息。  <br>
 *        统计信息通过 ByteRTCLocalStreamStats{@link #ByteRTCLocalStreamStats} 类型的回调参数传递给用户，其中包括发送音视频比特率、发送帧率、编码帧率，网络质量等。
 * @param rtcRoom  ByteRTCRoom 对象。  <br>
 * @param stats  当前房间本地流数据统计。详见：ByteRTCLocalStreamStats{@link #ByteRTCLocalStreamStats} <br>
 */
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onLocalStreamStats:(ByteRTCLocalStreamStats *_Nonnull)stats NS_SWIFT_NAME(rtcRoom(_:onLocalStreamStats:));

/** 
 * @type callback
 * @region 多房间
 * @brief 本地订阅的远端音/视频流数据统计以及网络质量回调。  <br>
 *        本地用户订阅流成功后，SDK 会周期性（2s）的通过此回调事件通知用户订阅的流在此次统计周期内的质量统计信息，包括：发送音视频比特率、发送帧率、编码帧率，网络质量等。
 * @param rtcRoom  ByteRTCRoom 对象。
 * @param stats  当前房间本地流数据统计。 详见：ByteRTCRemoteStreamStats{@link #ByteRTCRemoteStreamStats}
 */
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onRemoteStreamStats:(ByteRTCRemoteStreamStats *_Nonnull)stats NS_SWIFT_NAME(rtcRoom(_:onRemoteStreamStats:));

/** 
 * @type callback
 * @region 多房间
 * @brief 远端可见用户加入房间，或房内隐身用户切换为可见的回调。<br>
 *        1. 远端用户调用 setUserVisibility:{@link #ByteRTCRoom#setUserVisibility:} 方法将自身设为可见后加入房间时，房间内其他用户将收到该事件。  <br>
 *        2. 远端可见用户断网后重新连入房间时，房间内其他用户将收到该事件。  <br>
 *        3. 房间内隐身远端用户调用 setUserVisibility:{@link #ByteRTCRoom#setUserVisibility:} 方法切换至可见时，房间内其他用户将收到该事件。  <br>
 *        4. 新进房用户会收到进房前已在房内的可见用户的进房回调通知。  <br>
 * @param rtcRoom ByteRTCRoom 对象。  <br>
 * @param userInfo 用户信息，参看 ByteRTCUserInfo{@link #ByteRTCUserInfo}。  <br>
 * @param elapsed 保留字段，无意义
 */
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onUserJoined:(ByteRTCUserInfo *_Nonnull)userInfo elapsed:(NSInteger)elapsed;

/** 
 * @type callback
 * @brief 远端用户离开房间，或切至不可见时，本地用户会收到此事件
 * @param uid 离开房间，或切至不可见的的远端用户 ID。  <br>
 * @param reason 用户离开房间的原因：  <br>
 *              + 0: 远端用户调用 leaveRoom{@link #ByteRTCRoom#leaveRoom} 主动退出房间。  <br>
 *              + 1: 远端用户因 Token 过期或网络原因等掉线。详细信息请参看[连接状态提示](https://www.volcengine.com/docs/6348/95376) <br>
 *              + 2: 远端用户调用 setUserVisibility:{@link #ByteRTCRoom#setUserVisibility:} 切换至不可见状态。 <br>
 *              + 3: 服务端调用 OpenAPI 将远端用户踢出房间。
 */
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onUserLeave:(NSString *_Nonnull)uid reason:(ByteRTCUserOfflineReason)reason;
/** 
 * @type callback
 * @brief Token 进房权限过期前 30 秒将触发该回调。<br>
 *        收到该回调后，你需调用 updateToken:{@link #ByteRTCRoom#updateToken:} 更新 Token 进房权限。
 * @notes 若 Token 进房权限过期且未及时更新： <br>
 *        + 用户此时尝试进房会收到 rtcRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onRoomStateChanged:withUid:state:extraInfo:} 回调，提示错误码为 `-1000` Token 无效； <br>
 *        + 用户已在房间内则会被移出房间，本地用户会收到 rtcRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onRoomStateChanged:withUid:state:extraInfo:} 回调，提示错误码为 `-1009` Token 过期，同时远端用户会收到 rtcRoom:onUserLeave:reason:{@link #ByteRTCRoomDelegate#rtcRoom:onUserLeave:reason:} 回调，提示原因为 `2` Token 进房权限过期。
 */
 - (void)onTokenWillExpire:( ByteRTCRoom *_Nonnull)rtcRoom;
/** 
 * @type callback
 * @brief Token 发布权限过期前 30 秒将触发该回调。<br>
 *        收到该回调后，你需调用 updateToken:{@link #ByteRTCRoom#updateToken:} 更新 Token 发布权限。
 * @notes 若收到该回调后未及时更新 Token，Token 发布权限过期后： <br>
 *        + 此时尝试发布流会收到 rtcRoom:onStreamStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamStateChanged:withUid:state:extraInfo:} 回调，提示错误码为 `-1002` 没有发布权限； <br>
 *        + 已在发布中的流会停止发布，发布端会收到 rtcRoom:onStreamStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamStateChanged:withUid:state:extraInfo:} 回调，提示错误码为 `-1002` 没有发布权限，同时远端用户会收到 rtcRoom:onUserUnpublishStream:type:reason:{@link #ByteRTCRoomDelegate#rtcRoom:onUserUnpublishStream:type:reason:}/rtcRoom:onUserUnpublishScreen:type:reason:{@link #ByteRTCRoomDelegate#rtcRoom:onUserUnpublishScreen:type:reason:} 回调，提示原因为 `6` 发流端发布权限过期。
 */
- (void)onPublishPrivilegeTokenWillExpire:( ByteRTCRoom *_Nonnull)rtcRoom;
/** 
 * @type callback
 * @brief Token 订阅权限过期前 30 秒将触发该回调。<br>
 *        收到该回调后，你需调用 updateToken:{@link #ByteRTCRoom#updateToken:} 更新 Token 订阅权限有效期。
 * @notes 若收到该回调后未及时更新 Token，Token 订阅权限过期后，尝试新订阅流会失败，已订阅的流会取消订阅，并且会收到 rtcRoom:onStreamStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamStateChanged:withUid:state:extraInfo:} 回调，提示错误码为 `-1003` 没有订阅权限。
 */
- (void)onSubscribePrivilegeTokenWillExpire:( ByteRTCRoom *_Nonnull)rtcRoom;
 /** 
  * @deprecated since 3.36 and will be deleted in 3.51, use rtcRoom:onUserPublishStream:type:{@link #ByteRTCRoomDelegate#rtcRoom:onUserPublishStream:type:} and rtcRoom:onUserPublishScreen:type:{@link #ByteRTCRoomDelegate#rtcRoom:onUserPublishScreen:type:} instead.
  * @type callback
  * @region 多房间
  * @brief 以下情况会触发此回调：<br>
  *        + 房间内的用户发布新的音视频流时，房间内的其他用户会收到此回调通知。  <br>
  *        + 房间内的用户原音视频流被移出后，又重新发布音视频流时，房间内的其他用户会收到此回调通知。  <br>
  *        + 用户刚加入房间时，会收到此回调，包含房间中所有已发布的流。
  * @param rtcRoom  ByteRTCRoom 对象。  <br>
  * @param stream 流属性，参看 ByteRTCStream{@link #ByteRTCStream} 。  <br>
  */
 - (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onStreamAdd:(id<ByteRTCStream> _Nonnull)stream __deprecated_msg("Will be removed in new version");

 /** 
  * @deprecated since 3.36 and will be deleted in 3.51, use rtcRoom:onUserUnpublishStream:type:reason:{@link #ByteRTCRoomDelegate#rtcRoom:onUserUnpublishStream:type:reason:} and rtcRoom:onUserUnpublishScreen:type:reason:{@link #ByteRTCRoomDelegate#rtcRoom:onUserUnpublishScreen:type:reason:} instead.
  * @type callback
  * @region 多房间
  * @brief 房间内的远端用户停止发布音视频流时，本地用户会收到此回调通知。  <br>
  * @param rtcRoom ByteRTCRoom 对象
  * @param uid 远端流来源的用户 ID 。  <br>
  * @param stream 流的属性，参看 ByteRTCStream{@link #ByteRTCStream}。  <br>
  * @param reason 远端流移除的原因，参看 ByteRTCStreamRemoveReason{@link #ByteRTCStreamRemoveReason} 。  <br>
  */
 - (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onStreamRemove:(NSString *_Nonnull)uid
              stream:(id<ByteRTCStream> _Nonnull)stream
              reason:(ByteRTCStreamRemoveReason)reason
              __deprecated_msg("Will be removed in new version");
/** 
 * @type callback
 * @region 房间管理
 * @brief 房间内新增远端摄像头/麦克风采集的媒体流的回调。
 * @param rtcRoom ByteRTCRoom 实例
 * @param userId 远端流发布用户的用户 ID。
 * @param type 远端媒体流的类型，参看 ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}。
 * @notes 当房间内的远端用户调用 publishStream:{@link #ByteRTCRoom#publishStream:} 成功发布由摄像头/麦克风采集的媒体流时，本地用户会收到该回调，此时本地用户可以自行选择是否调用 subscribeStream:mediaStreamType:{@link #ByteRTCRoom#subscribeStream:mediaStreamType:} 订阅此流。
 */
- (void)rtcRoom:( ByteRTCRoom * _Nonnull)rtcRoom onUserPublishStream:(NSString *_Nonnull)userId type:(ByteRTCMediaStreamType)type;
/** 
 * @type callback
 * @region 房间管理
 * @brief 房间内远端摄像头/麦克风采集的媒体流移除的回调。
 * @param rtcRoom ByteRTCRoom 实例
 * @param userId 移除的远端流发布用户的用户 ID。  <br>
 * @param type 移除的远端流类型，参看 ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}。  <br>
 * @param reason 远端流移除的原因，参看 ByteRTCStreamRemoveReason{@link #ByteRTCStreamRemoveReason}。
 * @notes 收到该回调通知后，你可以自行选择是否调用 unsubscribeStream:mediaStreamType:{@link #ByteRTCRoom#unsubscribeStream:mediaStreamType:} 取消订阅此流。
 */
- (void)rtcRoom:( ByteRTCRoom * _Nonnull)rtcRoom onUserUnpublishStream:(NSString *_Nonnull)userId type:(ByteRTCMediaStreamType)type
           reason:(ByteRTCStreamRemoveReason)reason;
/** 
 * @type callback
 * @region 房间管理
 * @brief 房间内新增远端屏幕共享音视频流的回调。
 * @param rtcRoom ByteRTCRoom实例
 * @param userId 远端流发布用户的用户 ID。
 * @param type 远端媒体流的类型，参看 ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}。
 * @notes 当房间内的远端用户调用 publishScreen:{@link #ByteRTCRoom#publishScreen:} 成功发布来自屏幕共享的音视频流时，本地用户会收到该回调，此时本地用户可以自行选择是否调用 subscribeScreen:mediaStreamType:{@link #ByteRTCRoom#subscribeScreen:mediaStreamType:} 订阅此流。
 */
- (void)rtcRoom:( ByteRTCRoom * _Nonnull)rtcRoom onUserPublishScreen:(NSString *_Nonnull)userId type:(ByteRTCMediaStreamType)type;
/** 
 * @type callback
 * @region 房间管理
 * @brief 房间内远端屏幕共享音视频流移除的回调。
 * @param rtcRoom ByteRTCRoom 实例
 * @param userId 移除的远端流发布用户的用户 ID。  <br>
 * @param type 移除的远端流类型，参看 ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}。  <br>
 * @param reason 远端流移除的原因，参看 ByteRTCStreamRemoveReason{@link #ByteRTCStreamRemoveReason}。
 * @notes 收到该回调通知后，你可以自行选择是否调用 unsubscribeScreen:mediaStreamType:{@link #ByteRTCRoom#unsubscribeScreen:mediaStreamType:} 取消订阅此流。
 */
- (void)rtcRoom:( ByteRTCRoom * _Nonnull)rtcRoom onUserUnpublishScreen:(NSString *_Nonnull)userId type:(ByteRTCMediaStreamType)type
           reason:(ByteRTCStreamRemoveReason)reason;
/** 
 * @type callback
 * @region 房间管理
 * @brief 关于订阅媒体流状态改变的回调
 * @param rtcRoom ByteRTCRoom 对象
 * @param state 订阅媒体流状态，参看 ByteRTCSubscribeState{@link #ByteRTCSubscribeState}
 * @param userId 流发布用户的用户 ID
 * @param info 流的属性，参看 ByteRTCSubscribeConfig{@link #ByteRTCSubscribeConfig}
 * @notes 本地用户收到该回调的时机包括：  <br>
 *        + 调用 subscribeStream:mediaStreamType:{@link #ByteRTCRoom#subscribeStream:mediaStreamType:} 或 unsubscribeStream:mediaStreamType:{@link #ByteRTCRoom#unsubscribeStream:mediaStreamType:} 订阅/取消订阅指定远端摄像头音视频流后；  <br>
 *        + 调用 subscribeScreen:mediaStreamType:{@link #ByteRTCRoom#subscribeScreen:mediaStreamType:} 或 unsubscribeScreen:mediaStreamType:{@link #ByteRTCRoom#unsubscribeScreen:mediaStreamType:} 订阅/取消订阅指定远端屏幕共享流后。
 */
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onStreamSubscribed:(ByteRTCSubscribeState)state
                userId:(NSString *_Nonnull)userId
       subscribeConfig:(ByteRTCSubscribeConfig *_Nonnull)info;

/** 
 * @hidden for internal use only
 * @type callback
 * @region 多房间
 * @brief 当发布流成功的时候回调该事件
 * @param rtcRoom  ByteRTCRoom 对象。  <br>
 * @param userId 用户ID
 * @param isScreen 该流是否是屏幕流
 *
 */
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onStreamPublishSuccess:(NSString *_Nonnull)userId isScreen:(BOOL)isScreen;

 /** 
  * @type callback
  * @region 多房间
  * @brief 收到房间中调用 sendRoomMessage:{@link #ByteRTCRoom#sendRoomMessage:} 发送的广播文本消息时，收到此回调。
  * @param rtcRoom ByteRTCRoom 对象
  * @param uid 消息发送者 ID 。
  * @param message 收到的文本消息内容。
  */
 - (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onRoomMessageReceived:(NSString *_Nonnull)uid
        message:(NSString *_Nonnull)message;

 /** 
  * @type callback
  * @region 多房间
  * @brief 收到房间内广播二进制消息的回调。<br>
  *        房间内其他用户调用 sendRoomBinaryMessage:{@link #ByteRTCRoom#sendRoomBinaryMessage:} 发送的广播二进制消息时，收到此回调。
  * @param rtcRoom ByteRTCRoom 对象
  * @param uid 消息发送者 ID 。
  * @param message 收到的二进制消息内容。
  */
 - (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onRoomBinaryMessageReceived:(NSString *_Nonnull)uid
        message:(NSData *_Nonnull)message;

 /** 
  * @type callback
  * @region 多房间
  * @brief 收到来自房间中其他用户通过 sendUserMessage:message:config:{@link #ByteRTCRoom#sendUserMessage:message:config:} 发来的点对点文本消息时，会收到此回调。
  * @param rtcRoom ByteRTCRoom 对象
  * @param uid 消息发送者的用户 ID 。
  * @param message 收到的文本消息内容。
  */
 - (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onUserMessageReceived:(NSString *_Nonnull)uid
               message:(NSString *_Nonnull)message;

 /** 
 * @type callback
 * @region 多房间
 * @brief 收到来自房间中其他用户通过 sendUserBinaryMessage:message:config:{@link #ByteRTCRoom#sendUserBinaryMessage:message:config:} 发来的点对点二进制消息时，会收到此回调。
 * @param rtcRoom ByteRTCRoom 对象
 * @param uid 消息发送者的用户 ID 。
 * @param message 收到的二进制消息内容。
 */
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onUserBinaryMessageReceived:(NSString *_Nonnull)uid
               message:(NSData *_Nonnull)message;

 /** 
  * @type callback
  * @region 多房间
  * @brief 向房间内单个用户发送文本或二进制消息后（P2P），消息发送方会收到该消息发送结果回调。
  * @param rtcRoom ByteRTCRoom 对象。
  * @param msgid 本条消息的 ID。
  * @param error 消息发送结果，详见 ByteRTCUserMessageSendResult{@link #ByteRTCUserMessageSendResult}
  * @notes  <br>
  *        + 你应调用 sendUserMessage:message:config:{@link #ByteRTCRoom#sendUserMessage:message:config:} 向房间内单个用户发送文本消息 <br>
  *        + 你应调用 sendUserBinaryMessage:message:config:{@link #ByteRTCRoom#sendUserBinaryMessage:message:config:} 向房间内单个用户发送二进制消息
  */
 - (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onUserMessageSendResult:(NSInteger)msgid error:(ByteRTCUserMessageSendResult)error;

 /** 
  * @type callback
  * @region 多房间
  * @brief 调用 sendRoomMessage:{@link #ByteRTCRoom#sendRoomMessage:} 或 sendRoomBinaryMessage:{@link #ByteRTCRoom#sendRoomBinaryMessage:} 向房间内群发文本或二进制消息后，消息发送方会收到该消息发送结果回调。
  * @param rtcRoom ByteRTCRoom 对象。
  * @param msgid 本条消息的 ID。
  * @param error 消息发送结果，详见 ByteRTCRoomMessageSendResult{@link #ByteRTCRoomMessageSendResult}
  */
 - (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onRoomMessageSendResult:(NSInteger)msgid error:(ByteRTCRoomMessageSendResult)error;

/** 
 * @valid since 3.52.
 * @type callback
 * @region 多房间
 * @brief 调用 setRoomExtraInfo:value:{@link #ByteRTCRoom#setRoomExtraInfo:value:} 结果回调。
 * @param rtcRoom ByteRTCRoom 对象。
 * @param taskId 本次调用的任务编号。
 * @param error 设置房间附加信息结果，详见 ByteRTCSetRoomExtraInfoResult{@link #ByteRTCSetRoomExtraInfoResult}
 */
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onSetRoomExtraInfoResult:(NSInteger)taskId error:(ByteRTCSetRoomExtraInfoResult)error;

/** 
 * @valid since 3.52.
 * @type callback
 * @region 多房间
 * @brief 接收到房间附加信息的回调。<br>
 *        房间内其他用户调用 setRoomExtraInfo:value:{@link #ByteRTCRoom#setRoomExtraInfo:value:} 设置房间附加信息，收到此回调。<br>
 *        另外用户加入房间成功后会收到这个房间全量附加信息
 * @param rtcRoom ByteRTCRoom 对象。
 * @param key 附加信息的键值
 * @param value 附加信息的内容
 * @param lastUpdateUserId 最后更新这条附加信息的用户编号
 * @param lastUpdateTimeMs 最后更新这条附加信息的Unix时间，时间精度是毫秒
 */
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onRoomExtraInfoUpdate:(NSString *_Nonnull)key value:(NSString *_Nonnull)value lastUpdateUserId:(NSString *_Nonnull)lastUpdateUserId 
                 lastUpdateTimeMs:(NSInteger)lastUpdateTimeMs;

/** 
 * @valid since 3.54
 * @type callback
 * @region 房间管理
 * @brief 用户调用 setUserVisibility:{@link #ByteRTCRoom#setUserVisibility:} 设置用户可见性的回调。
 * @param currentUserVisibility 当前用户的可见性。  <br>
 *        + YES: 可见，用户可以在房间内发布音视频流，房间中的其他用户将收到用户的行为通知，例如进房、开启视频采集和退房。
 *        + NO: 不可见，用户不可以在房间内发布音视频流，房间中的其他用户不会收到用户的行为通知，例如进房、开启视频采集和退房。
 * @param errorCode 设置用户可见性错误码，参看 ByteRTCUserVisibilityChangeError{@link #ByteRTCUserVisibilityChangeError}。
 */
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onUserVisibilityChanged:(BOOL)currentUserVisibility errorCode:(ByteRTCUserVisibilityChangeError)errorCode;

/** 
 * @type callback
 * @region 视频管理
 * @brief 通过调用服务端 BanUserStream/UnbanUserStream 方法禁用/解禁指定房间内指定用户视频流的发送时，触发此回调。
 * @param uid 被禁用/解禁的视频流用户 ID
 * @param banned 视频流发送状态 <br>
 *        + true: 视频流发送被禁用 <br>
 *        + false: 视频流发送被解禁
 * @notes  <br>
 *        + 房间内指定用户被禁止/解禁视频流发送时，房间内所有用户都会收到该回调。  <br>
 *        + 若被封禁用户断网或退房后再进房，则依然是封禁状态，且房间内所有人会再次收到该回调。  <br>
 *        + 指定用户被封禁后，房间内其他用户退房后再进房，会再次收到该回调。  <br>
 *        + 同一房间解散后再次创建，房间内状态清空。
 */
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onVideoStreamBanned:(NSString *_Nonnull)uid isBanned:(BOOL)banned;

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
 *        + 在控制台开启音频选路后，只有被封禁/解禁用户会收到该回调。<br>
 *        + 同一房间解散后再次创建，房间内状态清空。
 */
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onAudioStreamBanned:(NSString *_Nonnull)uid isBanned:(BOOL)banned;

#pragma mark ForwardStream related callback
    /** 
     * @type callback
     * @region 多房间
     * @brief 跨房间媒体流转发状态和错误回调
     * @param rtcRoom ByteRTCRoom 对象
     * @param infos 跨房间媒体流转发目标房间信息数组，详见 ForwardStreamStateInfo{@link #ForwardStreamStateInfo}
     */
    - (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onForwardStreamStateChanged:(NSArray<ForwardStreamStateInfo *> * _Nonnull)infos;
    /** 
     * @type callback
     * @region 多房间
     * @brief 跨房间媒体流转发事件回调
     * @param rtcRoom ByteRTCRoom 对象
     * @param infos 跨房间媒体流转发目标房间事件数组，详见 ForwardStreamEventInfo{@link #ForwardStreamEventInfo}
     */
    - (void)rtcRoom:( ByteRTCRoom * _Nonnull)rtcRoom onForwardStreamEvent:(NSArray<ForwardStreamEventInfo *> * _Nonnull)infos;

/** 
 * @type callback
 * @brief 加入房间并发布或订阅流后， 以每 2 秒一次的频率，报告本地用户和已订阅的远端用户的上下行网络质量信息。
 * @param rtcRoom ByteRTCRoom 对象
 * @param localQuality 本端网络质量，详见 ByteRTCNetworkQualityStats{@link #ByteRTCNetworkQualityStats}。
 * @param remoteQualities 已订阅用户的网络质量，详见 ByteRTCNetworkQualityStats{@link #ByteRTCNetworkQualityStats}。
 * @notes 更多通话中的监测接口，详见[通话中质量监测](https://www.volcengine.com/docs/6348/106866)。
 */
- (void)rtcRoom:(ByteRTCRoom * _Nonnull)rtcRoom onNetworkQuality:(ByteRTCNetworkQualityStats *_Nonnull)localQuality remoteQualities:(NSArray<ByteRTCNetworkQualityStats*> *_Nonnull)remoteQualities;

/**  
 * @type callback
 * @region 字幕翻译服务
 * @brief  字幕状态发生改变回调。 <br>
 *         当用户调用 startSubtitle:{@link #ByteRTCRoom#startSubtitle:} 和 stopSubtitle{@link #ByteRTCRoom#stopSubtitle} 使字幕状态发生改变或出现错误时，触发该回调。 
 * @param rtcRoom ByteRTCRoom 实例。
 * @param state 字幕状态。参看 ByteRTCSubtitleState{@link #ByteRTCSubtitleState}。
 * @param errorCode   字幕任务错误码。参看 ByteRTCSubtitleErrorCode{@link #ByteRTCSubtitleErrorCode}。
 * @param errorMessage  第三方服务出现的错误。当因第三方服务出现错误，导致字幕状态改变时，用户可通过此参数获取具体的错误信息。如果不是因为第三方服务导致字幕状态改变，该字段为空。
 */
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onSubtitleStateChanged:(ByteRTCSubtitleState)state
                                                             errorCode:(ByteRTCSubtitleErrorCode)errorCode
                                                          errorMessage:(NSString *_Nonnull)errorMessage;
                                                          
/**  
 * @type callback
 * @region 字幕翻译服务
 * @brief  字幕相关内容回调。 <br>
 *         当用户调用 startSubtitle:{@link #ByteRTCRoom#startSubtitle:} 后会收到此回调，通知字幕的相关信息。
 * @param rtcRoom ByteRTCRoom 实例。
 * @param subtitles  字幕消息内容。参看 ByteRTCSubtitleMessage{@link #ByteRTCSubtitleMessage}。
 */
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onSubtitleMessageReceived:(NSArray<ByteRTCSubtitleMessage*> * _Nonnull)subtitles;
@end

/**
 * @type api
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCRoom : NSObject
/**
 * @type callback
 */
@property(nonatomic, weak) id<ByteRTCRoomDelegate> _Nullable delegate;

#pragma mark - Core Methods

/** 
 * @type api
 * @region 多房间
 * @brief 退出并销毁调用 createRTCRoom:{@link #ByteRTCVideo#createRTCRoom:} 所创建的房间实例。
 */
- (void)destroy;

/** 
 * @type api
 * @valid since 3.53
 * @brief 获取房间 ID。
 * @return 房间 ID。
 */
- (NSString *_Nonnull)getRoomId;

/** 
 * @type api
 * @region 多房间
 * @brief 通过设置 ByteRTCRoom{@link #ByteRTCRoom} 对象的事件句柄，监听此对象对应的回调事件。
 * @param roomDelegate 参见 ByteRTCRoomDelegate{@link #ByteRTCRoomDelegate}。
 * @return  <br>
 *        + 0: 调用成功。
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 */
- (int)setRTCRoomDelegate:(id<ByteRTCRoomDelegate> _Nullable)roomDelegate;

/** 
 * @type api
 * @region 多房间
 * @brief 加入房间。<br>
 *        调用 createRTCRoom:{@link #ByteRTCVideo#createRTCRoom:} 创建房间后，调用此方法加入房间，同房间内其他用户进行音视频通话。  <br>
 * @param token 动态密钥，用于对进房用户进行鉴权验证。  <br>
 *        进入房间需要携带 Token。测试时可使用控制台生成临时 Token，正式上线需要使用密钥 SDK 在你的服务端生成并下发 Token。Token 有效期及生成方式参看[使用 Token 完成鉴权](70121)。  <br>
 *        使用不同 AppID 的 App 是不能互通的。  <br>
 *        请务必保证生成 Token 使用的 AppID 和创建引擎时使用的 AppID 相同，否则会导致加入房间失败。具体失败原因会通过 rtcRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onRoomStateChanged:withUid:state:extraInfo:} 回调告知。  <br>
 * @param userInfo 用户信息。参看 ByteRTCUserInfo{@link #ByteRTCUserInfo}。  <br>
 * @param roomConfig 房间参数配置，设置房间模式以及是否自动发布或订阅流。具体配置模式参看 ByteRTCRoomConfig{@link #ByteRTCRoomConfig}。  <br>
 * @return 方法调用结果。  <br>
 *        +  0: 成功  <br>
 *        + -1: 参数无效  <br>
 *        + -2: 已经在房间内。接口调用成功后，只要收到返回值为 0 ，且未调用 leaveRoom{@link #ByteRTCRoom#leaveRoom} 成功，则再次调用进房接口时，无论填写的房间 ID 和用户 ID 是否重复，均触发此返回值。  <br>
 *        + -3: room 为空 <br>
 * @notes  <br>
 *        + 同一个 AppID 的同一个房间内，每个用户的用户 ID 必须是唯一的。如果两个用户的用户 ID 相同，则后加入房间的用户会将先加入房间的用户踢出房间，并且先加入房间的用户会收到 rtcRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onRoomStateChanged:withUid:state:extraInfo:} 回调通知，错误类型为重复登录 ByteRTCErrorCodeDuplicateLogin。  <br>
 *        + 本地用户调用此方法加入房间成功后，会收到 rtcRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onRoomStateChanged:withUid:state:extraInfo:} 回调通知。若本地用户同时为可见用户，加入房间时远端用户会收到 rtcRoom:onUserJoined:elapsed:{@link #ByteRTCRoomDelegate#rtcRoom:onUserJoined:elapsed:} 回调通知。关于可见性设置参看 setUserVisibility:{@link #ByteRTCRoom#setUserVisibility:}。  <br>
 *        + 用户加入房间成功后，在本地网络状况不佳的情况下，SDK 可能会与服务器失去连接，并触发 rtcEngine:onConnectionStateChanged:{@link #ByteRTCVideoDelegate#rtcEngine:onConnectionStateChanged:} 回调。此时 SDK 会自动重试，直到成功重连。重连成功后，本地会收到 rtcRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onRoomStateChanged:withUid:state:extraInfo:}。
 */
- (int)joinRoom:(NSString *_Nullable)token userInfo:(ByteRTCUserInfo *_Nonnull)userInfo roomConfig:(ByteRTCRoomConfig *_Nonnull)roomConfig NS_SWIFT_NAME(joinRoom(_:userInfo:roomConfig:));

/** 
 * @type api
 * @region 多房间
 * @brief 设置用户可见性。未调用该接口前，本地用户默认对他人可见。
 * @param enable 设置用户是否对房间内其他用户可见：  <br>
 *        + YES: 可见，用户可以在房间内发布音视频流，房间中的其他用户将收到用户的行为通知，例如进房、开启视频采集和退房。
 *        + NO: 不可见，用户不可以在房间内发布音视频流，房间中的其他用户不会收到用户的行为通知，例如进房、开启视频采集和退房。
 * @return  <br>
 *        + 0: 调用成功。
 *        + < 0: 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明。
 * @notes  <br>
 *       + 在加入房间前后，用户均可调用此方法设置用户可见性。
 *       + 设置用户可见性，会收到设置成功/失败回调 rtcRoom:onUserVisibilityChanged:errorCode:{@link #ByteRTCRoomDelegate#rtcRoom:onUserVisibilityChanged:errorCode:}。（v3.54 新增）
 *   &#x0020;  • 在加入房间前设置用户可见性，若设置的可见性与默认值不同，将在加入房间时触发本回调。
 *   &#x0020;  • 在加入房间后设置用户可见性，若可见性前后不同，会触发本回调。
 *   &#x0020;  • 在断网重连后，若可见性发生改变，会触发本回调。
 *       + 在房间内，调用此方法成功切换用户可见性后，房间内其他用户会收到相应的回调。
 *   &#x0020;  • 从可见换至不可见时，房间内其他用户会收到 rtcRoom:onUserLeave:reason:{@link #ByteRTCRoomDelegate#rtcRoom:onUserLeave:reason:}。
 *   &#x0020;  • 从不可见切换至可见时，房间内其他用户会收到 rtcRoom:onUserJoined:elapsed:{@link #ByteRTCRoomDelegate#rtcRoom:onUserJoined:elapsed:}。
 *   &#x0020;  • 若调用该方法将可见性设为 `false`，此时尝试发布流会收到 `ByteRTCWarningCodeSubscribeStreamForbiden` 警告。
 */
- (int)setUserVisibility:(BOOL)enable;

/** 
 * @type api
 * @region 多房间
 * @brief 设置发流端音画同步。  <br>
 *        当同一用户同时使用两个通话设备分别采集发送音频和视频时，有可能会因两个设备所处的网络环境不一致而导致发布的流不同步，此时你可以在视频发送端调用该接口，SDK 会根据音频流的时间戳自动校准视频流，以保证接收端听到音频和看到视频在时间上的同步性。
 * @param audioUserId 音频发送端的用户 ID，将该参数设为空则可解除当前音视频的同步关系。
 * @return  <br>
 *        + 0: 调用成功。
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @notes <br>
 *        + 该方法在进房前后均可调用。  <br>
 *        + 进行音画同步的音频发布用户 ID 和视频发布用户 ID 须在同一个 RTC 房间内。  <br>
 *        + 调用该接口后音画同步状态发生改变时，你会收到 rtcRoom:onAVSyncStateChange:{@link #ByteRTCRoomDelegate#rtcRoom:onAVSyncStateChange:} 回调。  <br>
 *        + 同一 RTC 房间内允许存在多个音视频同步关系，但需注意单个音频源不支持与多个视频源同时同步。  <br>
 *        + 如需更换同步音频源，再次调用该接口传入新的 `audioUserId` 即可；如需更换同步视频源，需先解除当前的同步关系，后在新视频源端开启同步。
 */
- (int)setMultiDeviceAVSync:(NSString* _Nullable) audioUserId;

/** 
 *  @type api
 *  @region 房间管理
 *  @brief 离开房间。  <br>
 *         用户调用此方法离开房间，结束通话过程，释放所有通话相关的资源。
 * @return  <br>
 *        + 0: 调用成功。
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 *  @notes  <br>
 *        + 用户离开房间后，本地会收到 rtcRoom:onLeaveRoom:{@link #ByteRTCRoomDelegate#rtcRoom:onLeaveRoom:} 的回调；  <br>
 *        + 调用 setUserVisibility:{@link #ByteRTCRoom#setUserVisibility:} 方法将自身设为可见的用户离开房间后，房间内其他用户会收到 rtcRoom:onUserLeave:reason:{@link #ByteRTCRoomDelegate#rtcRoom:onUserLeave:reason:} 回调通知。  <br>
 */
- (int)leaveRoom NS_SWIFT_NAME(leaveRoom());


/** 
 * @type api
 * @brief 更新 Token。
 *        Token 中同时包含进房、发布和订阅权限，各权限有一定的有效期，并且到期前 30 秒会触发回调，提示用户更新 Token 相关权限。此时需要重新获取 Token，并调用此方法更新 Token，以保证通话的正常进行。
 * @param token 重新获取的有效 Token。
 *        如果传入的 Token 无效，回调错误码为 ByteRTCErrorCode{@link #ByteRTCErrorCode} 中的 `-1010` 提示传入的 Token 无效。
 * @return <br>
 *        + 0：成功；
 *        + !0：失败。
 * @notes 请勿同时调用 updateToken:{@link #ByteRTCRoom#updateToken:} 和 joinRoom:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoom:userInfo:roomConfig:} 重新加入房间。
 */
- (int)updateToken:(NSString *_Nullable)token;
/** 
 * @type api
 * @region 视频管理
 * @brief 设置期望订阅的远端视频流的参数。
 * @param userId 期望配置订阅参数的远端视频流发布用户的 ID。
 * @param remoteVideoConfig 期望配置的远端视频流参数，参看 ByteRTCRemoteVideoConfig{@link #ByteRTCRemoteVideoConfig}。
 * @return 方法调用结果： <br>
 *        + 0：成功；<br>
 *        + !0：失败。
 * @notes <br>
 *        + 若使用 342 及以前版本的 SDK，调用该方法前请联系技术支持人员开启按需订阅功能。  <br>
 *        + 该方法仅在发布端调用 enableSimulcastMode:{@link #ByteRTCVideo#enableSimulcastMode:} 开启了发送多路视频流的情况下生效，此时订阅端将收到来自发布端与期望设置的参数最相近的一路流；否则订阅端只会收到一路参数为分辨率 640px × 360px、帧率 15fps 的视频流。  <br>
 *        + 若发布端开启了推送多路流功能，但订阅端不对流参数进行设置，则默认接受发送端设置的分辨率最大的一路视频流。  <br>
 *        + 该方法需在进房后调用，若想进房前设置，你需调用 joinRoom:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoom:userInfo:roomConfig:}，并对 `roomConfig` 中的 `remoteVideoConfig` 进行设置。  <br>
 *        + SDK 会根据发布端和所有订阅端的设置灵活调整视频流的参数，具体调整策略详见[推送多路流](https://www.volcengine.com/docs/6348/70139)文档。
 */
- (int) setRemoteVideoConfig:(NSString * _Nonnull) userId remoteVideoConfig:(ByteRTCRemoteVideoConfig *_Nonnull) remoteVideoConfig;
/** 
 * @type api
 * @region 房间管理
 * @brief 在当前所在房间内发布本地通过摄像头/麦克风采集的媒体流
 * @param type 媒体流类型，用于指定发布音频/视频，参看 ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}
 * @return  <br>
 *        + 0: 调用成功。
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @notes <br>
 *        + 如果你已经在用户进房时通过调用 joinRoom:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoom:userInfo:roomConfig:} 成功选择了自动发布，则无需再调用本接口。<br>
 *        + 调用 setUserVisibility:{@link #ByteRTCRoom#setUserVisibility:} 方法将自身设置为不可见后无法调用该方法，需将自身切换至可见后方可调用该方法发布摄像头音视频流。 <br>
 *        + 如果你需要发布屏幕共享流，调用 publishScreen:{@link #ByteRTCRoom#publishScreen:}。<br>
 *        + 如果你需要向多个房间发布流，调用 startForwardStreamToRooms:{@link #ByteRTCRoom#startForwardStreamToRooms:}。  <br>
 *        + 调用此方法后，房间中的所有远端用户会收到 rtcRoom:onUserPublishStream:type:{@link #ByteRTCRoomDelegate#rtcRoom:onUserPublishStream:type:} 回调通知，其中成功收到了音频流的远端用户会收到 rtcEngine:onFirstRemoteAudioFrame:{@link #ByteRTCVideoDelegate#rtcEngine:onFirstRemoteAudioFrame:} 回调，订阅了视频流的远端用户会收到 rtcEngine:onFirstRemoteVideoFrameDecoded:withFrameInfo:{@link #ByteRTCVideoDelegate#rtcEngine:onFirstRemoteVideoFrameDecoded:withFrameInfo:} 回调。<br>
 *        + 调用 unpublishStream:{@link #ByteRTCRoom#unpublishStream:} 取消发布。
 */
- (int)publishStream:(ByteRTCMediaStreamType)type;
/** 
 * @type api
 * @region 房间管理
 * @brief 停止将本地摄像头/麦克风采集的媒体流发布到当前所在房间中
 * @param type 媒体流类型，用于指定停止发布音频/视频，参看 ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}
 * @return  <br>
 *        + 0: 调用成功。
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @notes  <br>
 *        + 调用 publishStream:{@link #ByteRTCRoom#publishStream:} 手动发布摄像头音视频流后，你需调用此接口停止发布。<br>
 *        + 调用此方法停止发布音视频流后，房间中的其他用户将会收到 rtcRoom:onUserUnpublishStream:type:reason: {@link #ByteRTCRoomDelegate#rtcRoom:onUserUnpublishStream:type:reason:} 回调通知。
 */
- (int)unpublishStream:(ByteRTCMediaStreamType)type;
/** 
 * @type api
 * @region 屏幕共享
 * @brief 在当前所在房间内发布本地屏幕共享音视频流
 * @param type 媒体流类型，用于指定发布屏幕音频/视频，参看 ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}。
 * @return  <br>
 *        + 0: 调用成功。
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @notes <br>
 *        + 如果你已经在用户进房时通过调用 joinRoom:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoom:userInfo:roomConfig:} 成功选择了自动发布，则无需再调用本接口。<br>
 *        + 调用 setUserVisibility:{@link #ByteRTCRoom#setUserVisibility:} 方法将自身设置为不可见后无法调用该方法，需将自身切换至可见后方可调用该方法发布屏幕流。 <br>
 *        + 调用该方法后，房间中的所有远端用户会收到 rtcRoom:onUserPublishScreen:type:{@link #ByteRTCRoomDelegate#rtcRoom:onUserPublishScreen:type:} 回调，其中成功收到音频流的远端用户会收到 rtcEngine:onFirstRemoteAudioFrame:{@link #ByteRTCVideoDelegate#rtcEngine:onFirstRemoteAudioFrame:} 回调，订阅了视频流的远端用户会收到 rtcEngine:onFirstRemoteVideoFrameDecoded:withFrameInfo:{@link #ByteRTCVideoDelegate#rtcEngine:onFirstRemoteVideoFrameDecoded:withFrameInfo:} 回调。<br>
 *        + 调用该方法后，本地用户会收到 rtcEngine:onScreenVideoFrameSendStateChanged:rtcUser:state:{@link #ByteRTCVideoDelegate#rtcEngine:onScreenVideoFrameSendStateChanged:rtcUser:state:}。<br>
 *        + 如果你需要向多个房间发布流，调用 startForwardStreamToRooms:{@link #ByteRTCRoom#startForwardStreamToRooms:}。  <br>
 *        + 调用 unpublishScreen:{@link #ByteRTCRoom#unpublishScreen:} 取消发布。<br>
 *        + 查看 [屏幕共享](https://www.volcengine.com/docs/6348/80225)，获取更多信息。
 */
- (int)publishScreen:(ByteRTCMediaStreamType)type;
/** 
 * @type api
 * @region 屏幕共享
 * @brief 停止将本地屏幕共享音视频流发布到当前所在房间中
 * @param type 媒体流类型，用于指定停止发布屏幕音频/视频，参看 ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}
 * @return  <br>
 *        + 0: 调用成功。
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @notes <br>
 *        + 调用 publishScreen:{@link #ByteRTCRoom#publishScreen:} 发布屏幕流后，你需调用此接口停止发布。 <br>
 *        + 调用此方法停止发布屏幕音视频流后，房间中的其他用户将会收到 rtcRoom:onUserUnpublishScreen:type:reason:{@link #ByteRTCRoomDelegate#rtcRoom:onUserUnpublishScreen:type:reason:} 回调。
 */
- (int)unpublishScreen:(ByteRTCMediaStreamType)type;

/** 
 * @deprecated since 3.36 and will be deleted in 3.51, use subscribeStream:mediaStreamType:{@link #ByteRTCRoom#subscribeStream:mediaStreamType:}, unsubscribeStream:mediaStreamType:{@link #ByteRTCRoom#unsubscribeStream:mediaStreamType:}, subscribeScreen:mediaStreamType:{@link #ByteRTCRoom#subscribeScreen:mediaStreamType:} and unsubscribeScreen:mediaStreamType:{@link #ByteRTCRoom#unsubscribeScreen:mediaStreamType:} instead.
 * @type api
 * @region 多房间
 * @brief 订阅房间内指定的远端音视频流。  <br>
 *        无论是自动订阅还是手动订阅模式，你都可以调用此方法按需订阅房间中的音视频流。  <br>
 *        该方法也可用于更新已经订阅的流的属性、媒体类型等配置。
 * @param userId 指定订阅的远端发布音视频流的用户 ID 。  <br>
 * @param streamType 流属性，用于指定订阅主流/屏幕流，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex} 。  <br>
 * @param mediaType 媒体类型，用于指定订阅音/视频，参看 ByteRTCSubscribeMediaType{@link #ByteRTCSubscribeMediaType}。<br>
 * @param videoConfig 视频订阅配置，参看 ByteRTCSubscribeVideoConfig{@link #ByteRTCSubscribeVideoConfig}。<br>
 * @notes <br>
 *        + 你必须通过 rtcRoom:onStreamAdd:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamAdd:} 和 rtcRoom:onStreamRemove:stream:reason:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamRemove:stream:reason:} 两个回调获取当前房间里的音视频流信息，并调用本方法按需订阅流或修改订阅配置。  <br>
 *        + 若订阅失败，你会收到 rtcEngine:onError:{@link #ByteRTCVideoDelegate#rtcEngine:onError:} 回调通知，具体失败原因参看 ByteRTCErrorCode{@link #ByteRTCErrorCode}。
 *        + 若调用 pauseAllSubscribedStream:{@link #ByteRTCRoom#pauseAllSubscribedStream:} 暂停接收远端音视频流，此时仍可使用该方法对暂停接收的流进行设置，你会在调用 resumeAllSubscribedStream:{@link #ByteRTCRoom#resumeAllSubscribedStream:} 恢复接收流后收到修改设置后的流。  <br>
 */
- (int)subscribeUserStream:(NSString *_Nonnull)userId streamType:(ByteRTCStreamIndex)streamType mediaType:(ByteRTCSubscribeMediaType)mediaType videoConfig:(ByteRTCSubscribeVideoConfig *_Nonnull)videoConfig __deprecated_msg("Will be removed in new version");
/** 
 * @type api
 * @region 房间管理
 * @brief 订阅房间内指定的通过摄像头/麦克风采集的媒体流，或更新对指定远端用户的订阅选项
 * @param userId 指定订阅的远端发布音视频流的用户 ID。
 * @param mediaStreamType 媒体流类型，用于指定订阅音频/视频。参看 ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}。
 * @return 方法调用结果：
 *        + 0：成功；
 *        + <0：失败。具体失败原因参看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus}。
 * @notes  <br>
 *        + 当调用本接口时，当前用户已经订阅该远端用户，不论是通过手动订阅还是自动订阅，都将根据本次传入的参数，更新订阅配置。<br>
 *        + 你必须先通过 rtcRoom:onUserPublishStream:type:{@link #ByteRTCRoomDelegate#rtcRoom:onUserPublishStream:type:} 回调获取当前房间里的远端摄像头音视频流信息，然后调用本方法按需订阅。  <br>
 *        + 调用该方法后，你会收到 rtcRoom:onStreamSubscribed:userId:subscribeConfig:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamSubscribed:userId:subscribeConfig:} 通知方法调用结果。  <br>
 *        + 成功订阅远端用户的媒体流后，订阅关系将持续到调用 unsubscribeStream:mediaStreamType:{@link #ByteRTCRoom#unsubscribeStream:mediaStreamType:} 取消订阅或本端用户退房。 <br>
 *        + 关于其他调用异常，你会收到 rtcRoom:onStreamStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamStateChanged:withUid:state:extraInfo:} 回调通知，具体异常原因参看 ByteRTCErrorCode{@link #ByteRTCErrorCode}。
 */
- (int)subscribeStream:(NSString *_Nonnull)userId mediaStreamType:(ByteRTCMediaStreamType)mediaStreamType;
/** 
 * @type api
 * @region 房间管理
 * @brief 订阅房间内所有通过摄像头/麦克风采集的媒体流，或更新订阅选项。
 * @param mediaStreamType 媒体流类型，用于指定订阅音频/视频。参看 ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}。
 * @return  <br>
 *        0: 方法调用成功  <br>
 *        !0: 方法调用失败  <br>
 * @notes  <br>
 *        + 多次调用订阅接口时，将根据末次调用接口和传入的参数，更新订阅配置。<br>
 *        + 开启音频选路后，如果房间内的媒体流超过上限，建议通过调用 subscribeStream:mediaStreamType:{@link #ByteRTCRoom#subscribeStream:mediaStreamType:} 逐一指定需要订阅的媒体流。<br>
 *        + 调用该方法后，你会收到 rtcRoom:onStreamSubscribed:userId:subscribeConfig:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamSubscribed:userId:subscribeConfig:} 通知方法调用结果。  <br>
 *        + 成功调用本接口后，订阅关系将持续到调用 unsubscribeStream:mediaStreamType:{@link #ByteRTCRoom#unsubscribeStream:mediaStreamType:} 或 unsubscribeAllStreamsWithMediaStreamType:{@link #ByteRTCRoom#unsubscribeAllStreamsWithMediaStreamType:} 取消订阅或本端用户退房。 <br>
 *        + 关于其他调用异常，你会收到 rtcRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onRoomStateChanged:withUid:state:extraInfo:} 回调通知，具体异常原因参看 ByteRTCErrorCode{@link #ByteRTCErrorCode}。
 */
- (int)subscribeAllStreamsWithMediaStreamType:(ByteRTCMediaStreamType)mediaStreamType;

/** 
 * @type api
 * @region 房间管理
 * @brief 取消订阅房间内指定的通过摄像头/麦克风采集的媒体流。  <br>
 *        该方法对自动订阅和手动订阅模式均适用。
 * @param userId 指定取消订阅的远端发布音视频流的用户 ID。
 * @param mediaStreamType 媒体流类型，用于指定取消订阅音频/视频。参看 ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}。
 * @return 方法调用结果： <br>
 *        + 0：成功；<br>
 *        + !0：失败。
 * @notes  <br>
 *        + 调用该方法后，你会收到 rtcRoom:onStreamSubscribed:userId:subscribeConfig:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamSubscribed:userId:subscribeConfig:} 通知方法调用结果。  <br>
 *        + 关于其他调用异常，你会收到 rtcRoom:onStreamStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamStateChanged:withUid:state:extraInfo:} 回调通知，具体失败原因参看 ByteRTCErrorCode{@link #ByteRTCErrorCode}。
 */
- (int)unsubscribeStream:(NSString *_Nonnull)userId mediaStreamType:(ByteRTCMediaStreamType)mediaStreamType;
/** 
 * @type api
 * @region 房间管理
 * @brief 取消订阅房间内所有的通过摄像头/麦克风采集的媒体流。  <br>
 *        自动订阅和手动订阅的流都可以通过本方法取消订阅。
 * @param mediaStreamType 媒体流类型，用于指定取消订阅音频/视频。参看 ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}。
 * @return 方法调用结果：  <br>
 *        + 0：成功  <br>
 *        + !0：失败
 * @notes  <br>
 *        + 调用该方法后，你会收到 rtcRoom:onStreamSubscribed:userId:subscribeConfig:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamSubscribed:userId:subscribeConfig:} 通知方法调用结果。  <br>
 *        + 关于其他调用异常，你会收到 rtcRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onRoomStateChanged:withUid:state:extraInfo:} 回调通知，具体失败原因参看 ByteRTCErrorCode{@link #ByteRTCErrorCode}。
 */
- (int)unsubscribeAllStreamsWithMediaStreamType:(ByteRTCMediaStreamType)mediaStreamType;
/** 
 * @type api
 * @region 房间管理
 * @brief 订阅房间内指定的远端屏幕共享音视频流，或更新对指定远端用户的订阅选项
 * @param userId 指定订阅的远端发布屏幕流的用户 ID。
 * @param mediaStreamType 媒体流类型，用于指定订阅音频/视频。参看 ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}。
 * @return 方法调用结果：
 *        + 0：成功；
 *        + <0：失败。具体失败原因参看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus}。
 * @notes  <br>
 *        + 当调用本接口时，当前用户已经订阅该远端用户，不论是通过手动订阅还是自动订阅，都将根据本次传入的参数，更新订阅配置。<br>
 *        + 你必须先通过 rtcRoom:onUserPublishScreen:type:{@link #ByteRTCRoomDelegate#rtcRoom:onUserPublishScreen:type:} 回调获取当前房间里的远端屏幕流信息，然后调用本方法按需订阅。  <br>
 *        + 调用该方法后，你会收到 rtcRoom:onStreamSubscribed:userId:subscribeConfig:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamSubscribed:userId:subscribeConfig:} 通知方法调用结果。  <br>
 *        + 成功订阅远端用户的媒体流后，订阅关系将持续到调用 unsubscribeScreen:mediaStreamType:{@link #ByteRTCRoom#unsubscribeScreen:mediaStreamType:} 取消订阅或本端用户退房。 <br>
 *        + 关于其他调用异常，你会收到 rtcRoom:onStreamStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamStateChanged:withUid:state:extraInfo:} 回调通知，具体异常原因参看 ByteRTCErrorCode{@link #ByteRTCErrorCode}。
 */
- (int)subscribeScreen:(NSString *_Nonnull)userId mediaStreamType:(ByteRTCMediaStreamType)mediaStreamType;
/** 
 * @type api
 * @region 房间管理
 * @brief 取消订阅房间内指定的远端屏幕共享音视频流。  <br>
 *        该方法对自动订阅和手动订阅模式均适用。
 * @param userId 指定取消订阅的远端发布屏幕流的用户 ID。
 * @param mediaStreamType 媒体流类型，用于指定取消订阅音频/视频。参看 ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}。
 * @return 方法调用结果： <br>
 *        + 0：成功；<br>
 *        + !0：失败。
 * @notes  <br>
 *        + 调用该方法后，你会收到 rtcRoom:onStreamSubscribed:userId:subscribeConfig:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamSubscribed:userId:subscribeConfig:} 通知方法调用结果。  <br>
 *        + 关于其他调用异常，你会收到 rtcRoom:onStreamStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamStateChanged:withUid:state:extraInfo:} 回调通知，具体失败原因参看 ByteRTCErrorCode{@link #ByteRTCErrorCode}。
 */
- (int)unsubscribeScreen:(NSString *_Nonnull)userId mediaStreamType:(ByteRTCMediaStreamType)mediaStreamType;

/** 
 * @type api
 * @region 多房间
 * @brief 暂停接收来自远端的媒体流
 * @param mediaType 媒体流类型，指定需要暂停接收音频还是视频流，参看 ByteRTCPauseResumControlMediaType{@link #ByteRTCPauseResumControlMediaType}
 * @return  <br>
 *        + 0: 调用成功。
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @notes <br>
 *        + 该方法仅暂停远端流的接收，并不影响远端流的采集和发送；  <br>
 *        + 该方法不改变用户的订阅状态以及订阅流的属性。  <br>
 *        + 若想恢复接收远端流，需调用 resumeAllSubscribedStream:{@link #ByteRTCRoom#resumeAllSubscribedStream:}。 <br>
 *        + 多房间场景下，仅暂停接收发布在当前所在房间的流。
 */
- (int)pauseAllSubscribedStream:(ByteRTCPauseResumControlMediaType) mediaType;

/** 
 * @type api
 * @region 多房间
 * @brief 恢复接收来自远端的媒体流
 * @param mediaType 媒体流类型，指定需要暂停接收音频还是视频流，参看 ByteRTCPauseResumControlMediaType{@link #ByteRTCPauseResumControlMediaType}
 * @return  <br>
 *        + 0: 调用成功。
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @notes <br>
 *        + 该方法仅恢复远端流的接收，并不影响远端流的采集和发送；  <br>
 *        + 该方法不改变用户的订阅状态以及订阅流的属性。
 */
- (int)resumeAllSubscribedStream:(ByteRTCPauseResumControlMediaType) mediaType;
 /** 
  * @type api
  * @region 多房间
  * @brief 给房间内指定的用户发送点对点文本消息（P2P）。
  * @param userId  <br>
  *        消息接收用户的 ID
  * @param message  <br>
  *        发送的文本消息内容。  <br>
  *        消息不超过 64 KB。
  * @param config   <br>
  *        消息发送的可靠/有序类型，参看 ByteRTCMessageConfig{@link #ByteRTCMessageConfig}  <br>
  * @return 这次发送消息的编号，从 1 开始递增。
  * @notes  <br>
  *      + 在发送房间内文本消息前，必须先调用 joinRoom:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoom:userInfo:roomConfig:} 加入房间。  <br>
  *      + 调用该函数后会收到一次 rtcRoom:onUserMessageSendResult:error:{@link #ByteRTCRoomDelegate#rtcRoom:onUserMessageSendResult:error:} 回调，通知消息发送方发送成功或失败。  <br>
  *      + 若文本消息发送成功，则 uid 所指定的用户会收到 rtcRoom:onUserMessageReceived:message:{@link #ByteRTCRoomDelegate#rtcRoom:onUserMessageReceived:message:} 回调。
  */
 - (NSInteger)sendUserMessage:(NSString *_Nonnull)userId message:(NSString *_Nonnull)message config:(ByteRTCMessageConfig)config;

 /** 
  * @type api
  * @region 多房间
  * @brief 给房间内指定的用户发送点对点二进制消息（P2P）。
  * @param uid  <br>
  *        消息接收用户的 ID
  * @param message  <br>
  *        发送的二进制消息内容  <br>
  *        消息不超过 46KB。
  * @param config   <br>
  *        消息发送的可靠/有序类型，参看 ByteRTCMessageConfig{@link #ByteRTCMessageConfig}。  <br>
  * @return 这次发送消息的编号，从 1 开始递增。
  * @notes  <br>
  *      + 在发送房间内二进制消息前，必须先调用 joinRoom:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoom:userInfo:roomConfig:} 加入房间。  <br>
  *      + 调用该函数后会收到一次 rtcRoom:onUserMessageSendResult:error:{@link #ByteRTCRoomDelegate#rtcRoom:onUserMessageSendResult:error:} 回调，通知消息发送方发送成功或失败；  <br>
  *      + 若二进制消息发送成功，则 uid 所指定的用户会收到 rtcRoom:onUserBinaryMessageReceived:message:{@link #ByteRTCRoomDelegate#rtcRoom:onUserBinaryMessageReceived:message:} 回调。
  */
 - (NSInteger)sendUserBinaryMessage:(NSString * _Nonnull)uid message:(NSData * _Nonnull)message config:(ByteRTCMessageConfig)config;

 /** 
  * @type api
  * @region 多房间
  * @brief 给房间内的所有其他用户群发文本消息。
  * @param message  <br>
  *        发送的文本消息内容。  <br>
  *        消息不超过 64 KB。
  * @return 这次发送消息的编号，从 1 开始递增。
  * @notes  <br>
  *      + 在发送房间内文本消息前，必须先调用 joinRoom:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoom:userInfo:roomConfig:} 加入房间。  <br>
  *      + 调用该函数后会收到一次 rtcRoom:onRoomMessageSendResult:error:{@link #ByteRTCRoomDelegate#rtcRoom:onRoomMessageSendResult:error:} 回调，通知消息发送方发送成功或失败；  <br>
  *      + 若文本消息发送成功，则房间内所有远端用户会收到 rtcRoom:onRoomMessageReceived:message:{@link #ByteRTCRoomDelegate#rtcRoom:onRoomMessageReceived:message:} 回调。
  */
 - (NSInteger)sendRoomMessage:(NSString *_Nonnull)message NS_SWIFT_NAME(sendRoomMessage(_:));

 /** 
  * @type api
  * @region 多房间
  * @brief 给房间内的所有其他用户群发二进制消息。
  * @param message  <br>
  *        用户发送的二进制广播消息  <br>
  *        消息不超过 46KB。
  * @return 这次发送消息的编号，从 1 开始递增。
  * @notes  <br>
  *      + 在房间内广播二进制消息前，必须先调用 joinRoom:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoom:userInfo:roomConfig:} 加入房间。  <br>
  *      + 调用该函数后会收到一次 rtcRoom:onRoomMessageSendResult:error:{@link #ByteRTCRoomDelegate#rtcRoom:onRoomMessageSendResult:error:} 回调，通知消息发送方发送成功或失败；  <br>
  *      + 若二进制消息发送成功，则房间内所有用户会收到 rtcRoom:onRoomBinaryMessageReceived:message:{@link #ByteRTCRoomDelegate#rtcRoom:onRoomBinaryMessageReceived:message:} 回调。
  */
 - (NSInteger)sendRoomBinaryMessage:(NSData *  _Nonnull)message NS_SWIFT_NAME(sendRoomBinaryMessage(_:));

#pragma mark ForwardStream
    /** 
     * @type api
     * @region 多房间
     * @brief 开始跨房间转发媒体流。
     *        在调用 joinRoom:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoom:userInfo:roomConfig:} 后调用本接口，实现向多个房间转发媒体流，适用于跨房间连麦等场景。<br>
     * @param configurations 跨房间媒体流转发指定房间的信息。参看 ForwardStreamConfiguration{@link #ForwardStreamConfiguration}。
     * @return  <br>
     *        0: 方法调用成功
     *        <0: 方法调用失败  <br>
     * @notes <br>
     *        + 调用本方法后，将在本端触发 rtcRoom:onForwardStreamStateChanged:{@link #ByteRTCRoomDelegate#rtcRoom:onForwardStreamStateChanged:} 回调。
     *        + 调用本方法后，你可以通过监听 rtcRoom:onForwardStreamEvent:{@link #ByteRTCRoomDelegate#rtcRoom:onForwardStreamEvent:} 回调来获取各个目标房间在转发媒体流过程中的相关事件。
     *        + 开始转发后，目标房间中的用户将接收到本地用户进房 rtcRoom:onUserJoined:elapsed:{@link #ByteRTCRoomDelegate#rtcRoom:onUserJoined:elapsed:} 和发流 rtcRoom:onUserPublishStream:type:{@link #ByteRTCRoomDelegate#rtcRoom:onUserPublishStream:type:}/rtcRoom:onUserPublishScreen:type:{@link #ByteRTCRoomDelegate#rtcRoom:onUserPublishScreen:type:} 的回调。
     *        + 调用本方法后，可以调用 updateForwardStreamToRooms:{@link #ByteRTCRoom#updateForwardStreamToRooms:} 更新目标房间信息，例如，增加或减少目标房间等。
     *        + 调用本方法后，可以调用 stopForwardStreamToRooms{@link #ByteRTCRoom#stopForwardStreamToRooms} 停止向所有房间转发媒体流。
     *        + 调用本方法后，可以调用 pauseForwardStreamToAllRooms{@link #ByteRTCRoom#pauseForwardStreamToAllRooms} 暂停向所有房间转发媒体流。
     */
    - (int)startForwardStreamToRooms:(NSArray <ForwardStreamConfiguration *> * _Nullable)configurations NS_SWIFT_NAME(startForwardStreamToRooms(_:));
    /** 
     * @type api
     * @region 多房间
     * @brief 更新跨房间媒体流转发信息。<br>
     *        通过 startForwardStreamToRooms:{@link #ByteRTCRoom#startForwardStreamToRooms:} 发起媒体流转发后，可调用本方法增加或者减少目标房间，或更新房间密钥。
     *        调用本方法增加或删减房间后，将在本端触发 rtcRoom:onForwardStreamStateChanged:{@link #ByteRTCRoomDelegate#rtcRoom:onForwardStreamStateChanged:} 回调，包含发生了变动的目标房间中媒体流转发状态。
     * @param configurations 跨房间媒体流转发目标房间信息。参看 ForwardStreamConfiguration{@link #ForwardStreamConfiguration}。
     * @return  <br>
     *        + 0: 方法调用成功  <br>
     * @notes <br>
     *        + 增加目标房间后，新增目标房间中的用户将接收到本地用户进房 rtcRoom:onUserJoined:elapsed:{@link #ByteRTCRoomDelegate#rtcRoom:onUserJoined:elapsed:} 和发布 rtcRoom:onUserJoined:elapsed:{@link #ByteRTCRoomDelegate#rtcRoom:onUserJoined:elapsed:} 的回调。
     *        + 删减目标房间后，原目标房间中的用户将接收到本地用户停止发布 rtcRoom:onUserUnpublishStream:type:reason: {@link #ByteRTCRoomDelegate#rtcRoom:onUserUnpublishStream:type:reason:} 和退房 rtcRoom:onUserLeave:reason:{@link #ByteRTCRoomDelegate#rtcRoom:onUserLeave:reason:} 的回调。
     */
    - (int)updateForwardStreamToRooms:(NSArray <ForwardStreamConfiguration *> * _Nullable)configurations NS_SWIFT_NAME(updateForwardStreamToRooms(_:));
/** 
 * @type api
 * @region 多房间
 * @brief 停止跨房间媒体流转发。
 *        通过 startForwardStreamToRooms:{@link #ByteRTCRoom#startForwardStreamToRooms:} 发起媒体流转发后，可调用本方法停止向所有目标房间转发媒体流。
 * @return  <br>
 *        + 0: 调用成功。
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @notes <br>
 *        + 调用本方法后，将在本端触发 rtcRoom:onForwardStreamStateChanged:{@link #ByteRTCRoomDelegate#rtcRoom:onForwardStreamStateChanged:} 回调。
 *        + 调用本方法后，原目标房间中的用户将接收到本地用户停止发布 rtcRoom:onUserUnpublishStream:type:reason: {@link #ByteRTCRoomDelegate#rtcRoom:onUserUnpublishStream:type:reason:} 和退房 rtcRoom:onUserLeave:reason:{@link #ByteRTCRoomDelegate#rtcRoom:onUserLeave:reason:} 的回调。
 *        + 如果需要更改目标房间，请调用 updateForwardStreamToRooms:{@link #ByteRTCRoom#updateForwardStreamToRooms:} 更新房间信息。
 *        + 如果需要暂停转发，请调用 pauseForwardStreamToAllRooms{@link #ByteRTCRoom#pauseForwardStreamToAllRooms}，并在之后随时调用 resumeForwardStreamToAllRooms{@link #ByteRTCRoom#resumeForwardStreamToAllRooms} 快速恢复转发。
 */
- (int)stopForwardStreamToRooms;
/** 
 * @type api
 * @region 多房间
 * @brief 暂停跨房间媒体流转发。
 *        通过 startForwardStreamToRooms:{@link #ByteRTCRoom#startForwardStreamToRooms:} 发起媒体流转发后，可调用本方法暂停向所有目标房间转发媒体流。
 *        调用本方法暂停向所有目标房间转发后，你可以随时调用 resumeForwardStreamToAllRooms{@link #ByteRTCRoom#resumeForwardStreamToAllRooms} 快速恢复转发。
 * @return  <br>
 *        + 0: 调用成功。
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @notes 调用本方法后，目标房间中的用户将接收到本地用户停止发布 rtcRoom:onUserUnpublishStream:type:reason: {@link #ByteRTCRoomDelegate#rtcRoom:onUserUnpublishStream:type:reason:} 和退房 rtcRoom:onUserLeave:reason:{@link #ByteRTCRoomDelegate#rtcRoom:onUserLeave:reason:} 的回调。
 */
  - (int)pauseForwardStreamToAllRooms;
/** 
 * @type api
 * @region 多房间
 * @brief 恢复跨房间媒体流转发。
 *        调用 pauseForwardStreamToAllRooms{@link #ByteRTCRoom#pauseForwardStreamToAllRooms} 暂停转发之后，调用本方法恢复向所有目标房间转发媒体流。
 * @return  <br>
 *        + 0: 调用成功。
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @notes <br>
 *        目标房间中的用户将接收到本地用户进房 rtcRoom:onUserJoined:elapsed:{@link #ByteRTCRoomDelegate#rtcRoom:onUserJoined:elapsed:} 和发布 rtcRoom:onUserJoined:elapsed:{@link #ByteRTCRoomDelegate#rtcRoom:onUserJoined:elapsed:} 的回调。
 */
- (int)resumeForwardStreamToAllRooms;


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
 * @brief 获取空间音频接口实例。
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
 * @return  <br>
 *        + 0: 调用成功。
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @notes 假设某远端用户 A 始终在被调节的目标用户范围内，<br>
 *        + 当该方法与 setRemoteAudioPlaybackVolume:remoteUid:playVolume:{@link #ByteRTCVideo#setRemoteAudioPlaybackVolume:remoteUid:playVolume:} 共同使用时，本地收听用户 A 的音量为后调用的方法设置的音量；<br>
 *        + 当该方法与 setPlaybackVolume:{@link #ByteRTCVideo#setPlaybackVolume:} 方法共同使用时，本地收听用户 A 的音量将为两次设置的音量效果的叠加。
 */
- (int)setRemoteRoomAudioPlaybackVolume:(NSInteger)volume;

/** 
 * @hidden for internal use only.
 * @type api
 * @region 云端渲染
 * @brief 按照传入的布局信息开启云端渲染。
 * @param rendingInfo 渲染功能相关参数。
 * @return  <br>
 *        + 0: 调用成功。
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 */
- (int)startCloudRendering:(NSString *_Nonnull)rendingInfo;

/** 
 * @hidden for internal use only.
 * @type api
 * @region 云端渲染
 * @brief 按照传入的布局信息更新云端渲染。
 * @param rendingInfo 渲染功能相关参数。
 * @return  <br>
 *        + 0: 调用成功。
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 */
- (int)updateCloudRendering:(NSString *_Nonnull)rendingInfo;

/** 
 * @hidden for internal use only.
 * @type api
 * @region 云端渲染
 * @brief 停止云端渲染。
 * @return  <br>
 *        + 0: 调用成功。
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 */
- (int)stopCloudRendering;

/** 
 * @valid since 3.52.
 * @type api
 * @region 房间管理
 * @brief 设置本端发布流在音频选路中的优先级。
 * @param audioSelectionPriority 本端发布流在音频选路中的优先级，默认正常参与音频选路。参见 ByteRTCAudioSelectionPriority{@link #ByteRTCAudioSelectionPriority}。 
 * @notes 
 * 在控制台上为本 appId 开启音频选路后，调用本接口才会生效。进房前后调用均可生效。更多信息参见[音频选路](https://www.volcengine.com/docs/6348/113547)。
 * 如果本端用户同时加入不同房间，使用本接口进行的设置相互独立。
 * 
 */
- (int)setAudioSelectionConfig:(ByteRTCAudioSelectionPriority)audioSelectionPriority;

/** 
 * @valid since 3.52.
 * @type api
 * @region 房间管理
 * @brief 设置/更新房间附加信息，可用于标识房间状态或属性，或灵活实现各种业务逻辑。
 * @param key 房间附加信息键值，长度小于 10 字节。<br>
 *        同一房间内最多可存在 5 个 key，超出则会从第一个 key 起进行替换。
 * @param value 房间附加信息内容，长度小于 128 字节。
 * @return  <br>
 *        + 0: 方法调用成功，返回本次调用的任务编号； <br>
 *        + <0: 方法调用失败，具体原因详见 ByteRTCSetRoomExtraInfoResult{@link #ByteRTCSetRoomExtraInfoResult}。  
 * @notes  <br>
 *       + 在设置房间附加信息前，必须先调用 joinRoom:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoom:userInfo:roomConfig:} 加入房间。  <br>
 *       + 调用该方法后，会收到一次 rtcRoom:onSetRoomExtraInfoResult:error:{@link #ByteRTCRoomDelegate#rtcRoom:onSetRoomExtraInfoResult:error:} 回调，提示设置结果。  <br>
 *       + 调用该方法成功设置附加信息后，同一房间内的其他用户会收到关于该信息的回调 rtcRoom:onRoomExtraInfoUpdate:value:lastUpdateUserId:lastUpdateTimeMs:{@link #ByteRTCRoomDelegate#rtcRoom:onRoomExtraInfoUpdate:value:lastUpdateUserId:lastUpdateTimeMs:}。<br>
 *       + 新进房的用户会收到进房前房间内已有的全部附加信息通知。
 */
- (NSInteger)setRoomExtraInfo:(NSString *_Nonnull)key value:(NSString *_Nonnull)value;


/** 
 * @type api
 * @region 字幕翻译服务
 * @brief 识别或翻译房间内所有用户的语音，形成字幕。<br>
 *        语音识别或翻译的结果会通过 rtcRoom:onSubtitleMessageReceived:{@link #ByteRTCRoomDelegate#rtcRoom:onSubtitleMessageReceived:} 事件回调给你。<br>
 *        调用该方法后，用户会收到 rtcRoom:onSubtitleStateChanged:errorCode:errorMessage:{@link #ByteRTCRoomDelegate#rtcRoom:onSubtitleStateChanged:errorCode:errorMessage:} 回调，通知字幕是否开启。
 * @param subtitleConfig 字幕配置信息。参看 ByteRTCSubtitleConfig{@link #ByteRTCSubtitleConfig}。
 * @return  <br>
 *        +  0: 调用成功。  <br>
 *        + !0: 调用失败。 
 * @notes <br>
 *         此方法需要在进房后调用。  <br> 
 *         如果想要指定源语言，你需要在进房前调用 `joinRoom` 接口，通过 extraInfo 参数传入 `"source_language": "zh"` JSON 字符串，设置源语言为中文；传入 `"source_language": "en"`JSON 字符串，设置源语言为英文；传入 `"source_language": "ja"` JSON 字符串，设置源语言为日文。如果你未指定源语言，SDK 会将系统语种设定为源语言。如果你的系统语种不是中文、英文和日文，此时 SDK 会自动将中文设为源语言。  <br> 
 *         调用此方法前，你还需要前往[控制台](https://console.volcengine.com/rtc/cloudRTC?tab=subtitle)，在功能配置页面开启字幕功能。
 */
- (int)startSubtitle:(ByteRTCSubtitleConfig *_Nonnull)subtitleConfig;

/** 
 * @type api
 * @region 字幕翻译服务
 * @brief 关闭字幕。 <br>
 *        调用该方法后，用户会收到 rtcRoom:onSubtitleStateChanged:errorCode:errorMessage:{@link  #ByteRTCRoomDelegate#rtcRoom:onSubtitleStateChanged:errorCode:errorMessage:}  回调，通知字幕是否关闭。
 * @return  <br>
 *        +  0: 调用成功。  <br>
 *        + !0: 调用失败。 
 */
- (int)stopSubtitle;
@end
