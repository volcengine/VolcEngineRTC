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
 * @locale zh
 * @type callback
 * @brief 房间事件回调接口<br>
 * 注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。
 */
/**
 * @locale en
 * @type callback
 * @brief  Room event callback interface<br>
 * Note: Callback functions are thrown synchronously in a non-UI thread within the SDK. Therefore, you must not perform any time-consuming operations or direct UI operations within the callback function, as this may cause the app to crash.
 */
@protocol ByteRTCRoomDelegate <NSObject>
@optional

 /**
  * @locale zh
  * @type callback
  * @region 多房间
  * @brief 房间状态改变回调，加入房间、异常退出房间、发生房间相关的警告或错误时会收到此回调。
  * @param rtcRoom ByteRTCAudioRoom 实例
  * @param roomId 房间 ID。
  * @param uid 用户 ID。
  * @param state 房间状态码。  <br>
  *              + 0: 加入房间成功。  <br>
  *              + !0: 加入房间失败、异常退房、发生房间相关的警告或错误。具体原因参看 ByteRTCErrorCode{@link #ByteRTCErrorCode} 及 ByteRTCWarningCode{@link #ByteRTCWarningCode}。
  * @param extraInfo 额外信息，如 `{"elapsed":1187,"join_type":0}`。<br>
  *                  `join_type`表示加入房间的类型，`0`为首次进房，`1`为重连进房。<br>
  *                  `elapsed`表示加入房间耗时，即本地用户从调用 joinRoom:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoom:userInfo:roomConfig:} 到加入房间成功所经历的时间间隔，单位为 ms。
  */
 /**
  * @locale en
  * @type callback
  * @region Multi-room
  * @brief Callback on room state changes. Via this callback you get notified of room relating warnings,  errors and events. For example, the user joins the room, the user is removed from the room, and so on.
  * @param rtcRoom ByteRTCAudioRoom instance
  * @param roomId  Room ID.
  * @param uid  User ID.
  * @param state Room state code. <br>
  *              + 0: Join room success. <br>
  *              + !0: Failed to join a room, abnormal exit, room-related warnings or errors. See ByteRTCErrorCode{@link #ByteRTCErrorCode} and ByteRTCWarningCode{@link #ByteRTCWarningCode} for specific indications.
  * @param extraInfo Extra information.<br>
  *                 `join_type` indicates the type of room the user joins. `0` means the user joins the room for the first time, and `1` means the user rejoins the room. <br>
  *                 `elapsed` indicates the time interval from calling joinRoom:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoom:userInfo:roomConfig:} to successfully joining room, in ms.
  */
- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onRoomStateChanged:(NSString *_Nonnull)roomId
             withUid:(nonnull NSString *)uid
           state:(NSInteger)state
           extraInfo:(NSString *_Nonnull)extraInfo;

/**
 * @locale zh
 * @type callback
 * @region 多房间
 * @brief 流状态改变回调，发生流相关的警告或错误时会收到此回调。
 * @param roomId 房间 ID。
 * @param uid 用户 ID。
 * @param state 流状态码，参看 ByteRTCErrorCode{@link #ByteRTCErrorCode} 及 ByteRTCWarningCode{@link #ByteRTCWarningCode}。
 * @param extraInfo 附加信息，目前为空。
 */
/**
 * @locale en
 * @type callback
 * @region Multi-room
 * @brief Callback on stream state changes. The user will receive this callback when they receive stream relating warnings and errors.
 * @param roomId  Room ID.
 * @param uid  User ID.
 * @param state Room state code. See ByteRTCErrorCode{@link #ByteRTCErrorCode} and ByteRTCWarningCode{@link #ByteRTCWarningCode} for specific indications.
 * @param extraInfo Extra information. Currently unavailable.
 */
- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onStreamStateChanged:(NSString *_Nonnull)roomId
            withUid:(nonnull NSString *)uid
          state:(NSInteger)state
          extraInfo:(NSString *_Nonnull)extraInfo;

/**
 * @locale zh
 * @type callback
 * @region 多房间
 * @brief 离开房间成功回调。  <br>
 *        用户调用 leaveRoom{@link #ByteRTCRoom#leaveRoom} 方法后，SDK 会停止所有的发布订阅流，并释放所有通话相关的音视频资源。SDK 完成所有的资源释放后通过此回调通知用户。  
 * @param rtcRoom  ByteRTCRoom 对象。  
 * @param stats 保留参数，目前为空。
 * @note  
 *       + 用户调用 leaveRoom{@link #ByteRTCRoom#leaveRoom} 方法离开房间后，如果立即调用 destroy{@link #ByteRTCRoom#destroy} 销毁房间实例或 destroyRTCVideo{@link #ByteRTCVideo#destroyRTCVideo} 方法销毁 RTC 引擎，则将无法收到此回调事件。  <br>
 *       + 离开房间结束通话后，如果 App 需要使用系统音视频设备，则建议在收到此回调后再初始化音视频设备，否则可能由于 SDK 占用了导致 App 初始化音视频设备失败。  
 */
/**
 * @locale en
 * @type callback
 * @region Multiple rooms
 * @brief Leave the room successfully callback.   <br>
 *        When the user calls the leaveRoom{@link #ByteRTCRoom#leaveRoom} method, the SDK stops all publish subscription streams and releases all call-related audio & video resources. This callback notifies the user when the SDK completes all resource releases. 
 * @param rtcRoom  ByteRTCRoom object. 
 * @param stats Reserved parameter.
 * @note   
 *        + After the user calls the leaveRoom{@link #ByteRTCRoom#leaveRoom} method to leave the room, if destroy{@link #ByteRTCRoom#destroy} is called to destroy the room instance or destroyRTCVideo{@link #ByteRTCVideo#destroyRTCVideo} method is called to destroy the RTC engine immediately, this callback event will not be received. <br>
 *        + If the app needs to use the system audio & video device after leaving the room, it is recommended to initialize the audio & video device after receiving this callback, otherwise the initialization may fail due to the SDK occupying the audio & video device. 
 */
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onLeaveRoom:(ByteRTCRoomStats *_Nonnull)stats;

 /**
  * @locale zh
  * @deprecated since 3.41 and will be deleted in 3.51, use rtcRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onRoomStateChanged:withUid:state:extraInfo:} and rtcRoom:onStreamStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamStateChanged:withUid:state:extraInfo:} instead.
  * @type callback
  * @region 多房间
  * @brief 发生警告回调。  <br>
  *        SDK 运行时出现了警告。SDK 通常会自动恢复，警告信息可以忽略。
  * @param rtcRoom ByteRTCRoom 对象。
  * @param warningCode 警告码，详见枚举类型 ByteRTCWarningCode{@link #ByteRTCWarningCode} 。
  */
 /**
  * @locale en
  * @deprecated since 3.45 and will be deleted in 3.51, use rtcRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onRoomStateChanged:withUid:state:extraInfo:} and rtcRoom:onStreamStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamStateChanged:withUid:state:extraInfo:} instead.
  * @type callback
  * @region Multiple rooms
  * @brief Warning callback occurred.   <br>
  *        A warning occurred during the SDK runtime. The SDK usually recovers automatically and warnings can be ignored.
  * @param rtcRoom ByteRTCRoom object.
  * @param warningCode Warning code. See enumeration type ByteRTCWarningCode{@link #ByteRTCWarningCode}.
  */
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onRoomWarning:(ByteRTCWarningCode)warningCode __deprecated_msg("Will be removed in new version");

/**
 * @locale zh
 * @deprecated since 3.41 and will be deleted in 3.51, use rtcRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onRoomStateChanged:withUid:state:extraInfo:} and rtcRoom:onStreamStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamStateChanged:withUid:state:extraInfo:} instead.
 * @type callback
 * @region 多房间
 * @brief 发生错误回调。  <br>
 *        SDK 运行时出现了错误。SDK 通常无法自动恢复，应用需要采取行动。
 * @param rtcRoom  ByteRTCRoom 对象。
 * @param errorCode 错误码，详见枚举类型 ByteRTCErrorCode{@link #ByteRTCErrorCode} 。
 */
/**
 * @locale en
 * @deprecated since 3.45 and will be deleted in 3.51, use rtcRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onRoomStateChanged:withUid:state:extraInfo:} and rtcRoom:onStreamStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamStateChanged:withUid:state:extraInfo:} instead.
 * @type callback
 * @region Multiple rooms
 * @brief Error callback occurred.   <br>
 *        An error occurred during the SDK runtime. The SDK usually does not recover automatically, and the app needs to take action.
 * @param rtcRoom  ByteRTCRoom object.
 * @param errorCode  Error code. See enumeration type ByteRTCErrorCode{@link #ByteRTCErrorCode}.
 */
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onRoomError:(ByteRTCErrorCode)errorCode __deprecated_msg("Will be removed in new version");

/**
 * @locale zh
 * @type callback
 * @region 多房间
 * @brief 发布端调用 setMultiDeviceAVSync:{@link #ByteRTCRoom#setMultiDeviceAVSync:} 后音视频同步状态发生改变时，会收到此回调。
 * @param rtcRoom ByteRTCRoom 实例
 * @param state 音视频同步状态，参看 ByteRTCAVSyncState{@link #ByteRTCAVSyncState}。
 */
/**
 * @locale en
 * @type callback
 * @region Multi-Room
 * @brief Stream publisher will receive this callback when the A/V synchronization state changes after setMultiDeviceAVSync:{@link #ByteRTCRoom#setMultiDeviceAVSync:} is called.
 * @param rtcRoom The ByteRTCRoom instance.
 * @param state A/V synchronization state, see ByteRTCAVSyncState{@link #ByteRTCAVSyncState}.
 */
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onAVSyncStateChange:(ByteRTCAVSyncState)state;

/**
 * @locale zh
 * @type callback
 * @region 多房间
 * @brief 房间内通话统计信息回调。   <br>
 *        用户进房开始通话后，每 2s 收到一次本回调。
 * @param rtcRoom  ByteRTCRoom 对象。
 * @param stats 当前 ByteRTCRoom 统计数据，详见：ByteRTCRoomStats{@link #ByteRTCRoomStats}
 */
/**
 * @locale en
 * @type callback
 * @region Multiple rooms
 * @brief In-room call statistics callback.    <br>
 *        After the user enters the room and starts the call, he receives this callback every 2s.
 * @param rtcRoom  ByteRTCRoom object.
 * @param stats Current ByteRTCRoom statistics, see: ByteRTCRoomStats{@link #ByteRTCRoomStats}
 */
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onRoomStats:(ByteRTCRoomStats *_Nonnull)stats NS_SWIFT_NAME(rtcRoom(_:onRoomStats:));

/**
 * @locale zh
 * @type callback
 * @region 多房间
 * @brief 本地流数据统计以及网络质量回调。  <br>
 *        本地用户发布流成功后，SDK 会周期性（2s）的通过此回调事件通知用户发布的流在此次统计周期内的质量统计信息。  <br>
 *        统计信息通过 ByteRTCLocalStreamStats{@link #ByteRTCLocalStreamStats} 类型的回调参数传递给用户，其中包括发送音视频比特率、发送帧率、编码帧率，网络质量等。
 * @param rtcRoom  ByteRTCRoom 对象。  
 * @param stats  当前房间本地流数据统计。详见：ByteRTCLocalStreamStats{@link #ByteRTCLocalStreamStats} 
 */
/**
 * @locale en
 * @type callback
 * @region Multi-room
 * @brief Local stream data statistics and network quality callback.   <br>
 *        After the local user publishes the flow successfully, the SDK will periodically (2s) notify the user through this callback event of the quality statistics of the published flow during this reference period. <br>
 *        Statistics are passed to the user through the callback parameters of the ByteRTCLocalStreamStats{@link #ByteRTCLocalStreamStats} type, including the sent audio & video bit rate, sent frame rate, encoded frame rate, network quality, etc. 
 * @param rtcRoom  ByteRTCRoom object. 
 * @param stats   Current room local stream data statistics. See: ByteRTCLocalStreamStats{@link #ByteRTCLocalStreamStats} 
 */
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onLocalStreamStats:(ByteRTCLocalStreamStats *_Nonnull)stats NS_SWIFT_NAME(rtcRoom(_:onLocalStreamStats:));

/**
 * @locale zh
 * @type callback
 * @region 多房间
 * @brief 本地订阅的远端音/视频流数据统计以及网络质量回调。  <br>
 *        本地用户订阅流成功后，SDK 会周期性（2s）的通过此回调事件通知用户订阅的流在此次统计周期内的质量统计信息，包括：发送音视频比特率、发送帧率、编码帧率，网络质量等。
 * @param rtcRoom  ByteRTCRoom 对象。
 * @param stats  当前房间本地流数据统计。 详见：ByteRTCRemoteStreamStats{@link #ByteRTCRemoteStreamStats}
 */
/**
 * @locale en
 * @type callback
 * @region Multi-room
 * @brief Remote audio/video stream statistics and network quality callbacks for local subscriptions.   <br>
 *        After the local user subscribes to the stream successfully, the SDK will periodically (2s) notify the user through this callback event of the quality statistics of the subscribed stream during this reference period, including: sending audio & video bit rate, sending frame rate, encoded frame rate, network quality, etc.
 * @param rtcRoom  ByteRTCRoom object.
 * @param stats  Current room local stream statistics. See: ByteRTCRemoteStreamStats{@link #ByteRTCRemoteStreamStats}
 */
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onRemoteStreamStats:(ByteRTCRemoteStreamStats *_Nonnull)stats NS_SWIFT_NAME(rtcRoom(_:onRemoteStreamStats:));

/**
 * @locale zh
 * @type callback
 * @region 多房间
 * @brief 远端可见用户加入房间，或房内隐身用户切换为可见的回调。<br>
 *        1. 远端用户调用 setUserVisibility:{@link #ByteRTCRoom#setUserVisibility:} 方法将自身设为可见后加入房间时，房间内其他用户将收到该事件。  <br>
 *        2. 远端可见用户断网后重新连入房间时，房间内其他用户将收到该事件。  <br>
 *        3. 房间内隐身远端用户调用 setUserVisibility:{@link #ByteRTCRoom#setUserVisibility:} 方法切换至可见时，房间内其他用户将收到该事件。  <br>
 *        4. 新进房用户会收到进房前已在房内的可见用户的进房回调通知。  
 * @param rtcRoom ByteRTCRoom 对象。  
 * @param userInfo 用户信息，参看 ByteRTCUserInfo{@link #ByteRTCUserInfo}。  
 * @param elapsed 保留字段，无意义
 */
/**
 * @locale en
 * @type callback
 * @region Multi-room
 * @brief You will receive this callback in following cases: <br>
 *        + The remote user calls setUserVisibility:{@link #ByteRTCRoom#setUserVisibility:} turns visible and joins your room. <br>
 *        + The remote visible user is disconnected and then reconnected to your room. <br>
 *        + The invisible remote user in your room calls setUserVisibility:{@link #ByteRTCRoom#setUserVisibility:} and turns visible. <br>
 *        + You join the room when there are visible users in the room.Callback about remote visible users join the room, or invisible users in the room switch to visible.
 * @param rtcRoom ByteRTCRoom object. 
 * @param userInfo  For user information. See ByteRTCUserInfo{@link #ByteRTCUserInfo}. 
 * @param elapsed  Reserved field, meaningless
 */
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onUserJoined:(ByteRTCUserInfo *_Nonnull)userInfo elapsed:(NSInteger)elapsed;

/**
 * @locale zh
 * @type callback
 * @brief 远端用户离开房间，或切至不可见时，本地用户会收到此事件
 * @param uid 离开房间，或切至不可见的的远端用户 ID。  
 * @param reason 用户离开房间的原因：  <br>
 *              + 0: 远端用户调用 leaveRoom{@link #ByteRTCRoom#leaveRoom} 主动退出房间。  <br>
 *              + 1: 远端用户因 Token 过期或网络原因等掉线。详细信息请参看[连接状态提示](https://www.volcengine.com/docs/6348/95376) <br>
 *              + 2: 远端用户调用 setUserVisibility:{@link #ByteRTCRoom#setUserVisibility:} 切换至不可见状态。 <br>
 *              + 3: 服务端调用 OpenAPI 将远端用户踢出房间。
 */
/**
 * @locale en
 * @type callback
 * @brief This callback is triggered when a remote user is disconnected or turns invisible.
 * @param uid ID of the user who leaves the room, or switches to invisible. 
 * @param reason Reason to leave the room: <br>
 *               + 0: The remote client calls leaveRoom{@link #ByteRTCRoom#leaveRoom} to leave the room. <br>
 *               + 1: The remote client is disconnected because of poor network connection or expired Token. <br>
 *               + 2: The remote client calls setUserVisibility:{@link #ByteRTCRoom#setUserVisibility:} to turn invisible. <br>
 *               + 3: The remote user has been removed from the room by the administrator via a OpenAPI call.
 */
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onUserLeave:(NSString *_Nonnull)uid reason:(ByteRTCUserOfflineReason)reason;
/**
 * @locale zh
 * @type callback
 * @brief Token 进房权限过期前 30 秒将触发该回调。<br>
 *        收到该回调后，你需调用 updateToken:{@link #ByteRTCRoom#updateToken:} 更新 Token 进房权限。
 * @note 若 Token 进房权限过期且未及时更新： <br>
 *        + 用户此时尝试进房会收到 rtcRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onRoomStateChanged:withUid:state:extraInfo:} 回调，提示错误码为 `-1000` Token 无效； <br>
 *        + 用户已在房间内则会被移出房间，本地用户会收到 rtcRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onRoomStateChanged:withUid:state:extraInfo:} 回调，提示错误码为 `-1009` Token 过期，同时远端用户会收到 rtcRoom:onUserLeave:reason:{@link #ByteRTCRoomDelegate#rtcRoom:onUserLeave:reason:} 回调，提示原因为 `2` Token 进房权限过期。
 * @list 引擎管理
 * @order 10
 */
 /**
 * @locale en
 * @type callback
 * @brief Callback triggered 30s before the joining room privilege of the Token expires. <br>
 *        After receiving this callback, you must call updateToken:{@link #ByteRTCRoom#updateToken:} to update the joining room privilege Token.
 * @note After a user's joining room privilege expires:<br>
 *        + When attempting to join a room, the user will receive rtcRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onRoomStateChanged:withUid:state:extraInfo:} with the error code "-1000" indicating that the Token is invalid.<br>
 *        + If the user is already in the room, he/she will be removed from the room and receive rtcRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onRoomStateChanged:withUid:state:extraInfo:} with the error code "-1009" indicating that the Token is expired. Remote users in the room will receive rtcRoom:onUserLeave:reason:{@link #ByteRTCRoomDelegate#rtcRoom:onUserLeave:reason:} with the reason "2" indicating that the Token is invalid.
 * @list Engine Management
 * @order 10
 */
- (void)onTokenWillExpire:( ByteRTCRoom *_Nonnull)rtcRoom;
/**
 * @locale zh
 * @type callback
 * @brief Token 发布权限过期前 30 秒将触发该回调。<br>
 *        收到该回调后，你需调用 updateToken:{@link #ByteRTCRoom#updateToken:} 更新 Token 发布权限。
 * @note 若收到该回调后未及时更新 Token，Token 发布权限过期后： <br>
 *        + 此时尝试发布流会收到 rtcRoom:onStreamStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamStateChanged:withUid:state:extraInfo:} 回调，提示错误码为 `-1002` 没有发布权限； <br>
 *        + 已在发布中的流会停止发布，发布端会收到 rtcRoom:onStreamStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamStateChanged:withUid:state:extraInfo:} 回调，提示错误码为 `-1002` 没有发布权限，同时远端用户会收到 rtcRoom:onUserUnpublishStream:type:reason:{@link #ByteRTCRoomDelegate#rtcRoom:onUserUnpublishStream:type:reason:}/rtcRoom:onUserUnpublishScreen:type:reason:{@link #ByteRTCRoomDelegate#rtcRoom:onUserUnpublishScreen:type:reason:} 回调，提示原因为 `6` 发流端发布权限过期。
 * @list 引擎管理
 * @order 15
 */
/**
 * @locale en
 * @type callback
 * @brief Callback triggered 30s before the publishing privilege of the Token expires. <br>
 *        After receiving this callback, you must call updateToken:{@link #ByteRTCRoom#updateToken:} to update the publishing privilege Token.
 * @note After a user's publishing privilege expires:<br>
 *        + When attempting to publish a stream, the user will receive rtcRoom:onStreamStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamStateChanged:withUid:state:extraInfo:} with the error code "-1002" indicating no permission to publish streams.<br>
 *        + The published streams of the user will be removed, and he/she will receive rtcRoom:onStreamStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamStateChanged:withUid:state:extraInfo:} with the error code "-1002" indicating no permission to publish streams. Remote users in the room will receive rtcRoom:onUserUnpublishStream:type:reason:{@link #ByteRTCRoomDelegate#rtcRoom:onUserUnpublishStream:type:reason:}/rtcRoom:onUserUnpublishScreen:type:reason:{@link #ByteRTCRoomDelegate#rtcRoom:onUserUnpublishScreen:type:reason:} with the reason "6" indicating that the publishing privilege of the remote user has expired.
 * @list Engine Management
 * @order 15
 */
- (void)onPublishPrivilegeTokenWillExpire:( ByteRTCRoom *_Nonnull)rtcRoom;
/**
 * @locale zh
 * @type callback
 * @brief Token 订阅权限过期前 30 秒将触发该回调。<br>
 *        收到该回调后，你需调用 updateToken:{@link #ByteRTCRoom#updateToken:} 更新 Token 订阅权限有效期。
 * @note 若收到该回调后未及时更新 Token，Token 订阅权限过期后，尝试新订阅流会失败，已订阅的流会取消订阅，并且会收到 rtcRoom:onStreamStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamStateChanged:withUid:state:extraInfo:} 回调，提示错误码为 `-1003` 没有订阅权限。
 * @list 引擎管理
 * @order 16
 */
/**
 * @locale en
 * @type callback
 * @brief Callback triggered 30s before the subscribing privilege of the Token expires. <br>
 *        After receiving this callback, you must call updateToken:{@link #ByteRTCRoom#updateToken:} to update the subscribing privilege Token.
 * @note After a user's subscribing privilege expires, the user will fail to subscribe to new streams, or the subscribed streams will be removed, and he/she will receive rtcRoom:onStreamStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamStateChanged:withUid:state:extraInfo:} with error code "-1003" indicating no permission to subscribe to streams.
 * @list Engine Management
 * @order 16
 */
- (void)onSubscribePrivilegeTokenWillExpire:( ByteRTCRoom *_Nonnull)rtcRoom;
 /**
  * @locale zh
  * @deprecated since 3.36 and will be deleted in 3.51, use rtcRoom:onUserPublishStream:type:{@link #ByteRTCRoomDelegate#rtcRoom:onUserPublishStream:type:} and rtcRoom:onUserPublishScreen:type:{@link #ByteRTCRoomDelegate#rtcRoom:onUserPublishScreen:type:} instead.
  * @type callback
  * @region 多房间
  * @brief 以下情况会触发此回调：<br>
  *        + 房间内的用户发布新的音视频流时，房间内的其他用户会收到此回调通知。  <br>
  *        + 房间内的用户原音视频流被移出后，又重新发布音视频流时，房间内的其他用户会收到此回调通知。  <br>
  *        + 用户刚加入房间时，会收到此回调，包含房间中所有已发布的流。
  * @param rtcRoom  ByteRTCRoom 对象。  
  * @param stream 流属性，参看 ByteRTCStream{@link #ByteRTCStream} 。  
  */
 /**
  * @locale en
  * @deprecated since 3.45 and will be deleted in 3.51, use rtcRoom:onUserPublishStream:type:{@link #ByteRTCRoomDelegate#rtcRoom:onUserPublishStream:type:} and rtcRoom:onUserPublishScreen:type:{@link #ByteRTCRoomDelegate#rtcRoom:onUserPublishScreen:type:} instead.
  * @type callback
  * @region Multiple rooms
  * @brief The following conditions trigger this callback: <br>
  *         + When users in the room post a new audio & video stream, other users in the room will receive this callback notification. <br>
  *         + When the user's original audio and video stream in the room is removed and the audio & video stream is republished, other users in the room will receive this callback notification. <br>
  *         + When the user first joins the room, he receives this callback, including all published streams in the room.
  * @param rtcRoom   ByteRTCRoom object. 
  * @param stream  Stream property. See ByteRTCStream{@link #ByteRTCStream}. 
  */
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onStreamAdd:(id<ByteRTCStream> _Nonnull)stream __deprecated_msg("Will be removed in new version");

 /**
  * @locale zh
  * @deprecated since 3.36 and will be deleted in 3.51, use rtcRoom:onUserUnpublishStream:type:reason:{@link #ByteRTCRoomDelegate#rtcRoom:onUserUnpublishStream:type:reason:} and rtcRoom:onUserUnpublishScreen:type:reason:{@link #ByteRTCRoomDelegate#rtcRoom:onUserUnpublishScreen:type:reason:} instead.
  * @type callback
  * @region 多房间
  * @brief 房间内的远端用户停止发布音视频流时，本地用户会收到此回调通知。  
  * @param rtcRoom ByteRTCRoom 对象
  * @param uid 远端流来源的用户 ID 。  
  * @param stream 流的属性，参看 ByteRTCStream{@link #ByteRTCStream}。  
  * @param reason 远端流移除的原因，参看 ByteRTCStreamRemoveReason{@link #ByteRTCStreamRemoveReason} 。  
  */
 /**
  * @locale en
  * @deprecated since 3.45 and will be deleted in 3.51, use rtcRoom:onUserUnpublishStream:type:reason:{@link #ByteRTCRoomDelegate#rtcRoom:onUserUnpublishStream:type:reason:} and rtcRoom:onUserUnpublishScreen:type:reason:{@link #ByteRTCRoomDelegate#rtcRoom:onUserUnpublishScreen:type:reason:} instead.
  * @type callback
  * @region Multi-room
  * @brief When a remote user in the room stops publishing audio & video streams, local users will receive this callback notification.   
  * @param rtcRoom ByteRTCRoom object
  * @param uid User ID of the remote stream source. 
  * @param stream  The properties of the stream. See ByteRTCStream{@link #ByteRTCStream}. 
  * @param reason  For reasons of remote stream removal. See ByteRTCStreamRemoveReason{@link #ByteRTCStreamRemoveReason}. 
  */
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onStreamRemove:(NSString *_Nonnull)uid
              stream:(id<ByteRTCStream> _Nonnull)stream
              reason:(ByteRTCStreamRemoveReason)reason
              __deprecated_msg("Will be removed in new version");
/**
 * @locale zh
 * @type callback
 * @region 房间管理
 * @brief 房间内新增远端摄像头/麦克风采集的媒体流的回调。
 * @param rtcRoom ByteRTCRoom 实例
 * @param userId 远端流发布用户的用户 ID。
 * @param type 远端媒体流的类型，参看 ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}。
 * @note 当房间内的远端用户调用 publishStream:{@link #ByteRTCRoom#publishStream:} 成功发布由摄像头/麦克风采集的媒体流时，本地用户会收到该回调，此时本地用户可以自行选择是否调用 subscribeStream:mediaStreamType:{@link #ByteRTCRoom#subscribeStream:mediaStreamType:} 订阅此流。
 */
/**
 * @locale en
 * @type callback
 * @region Room management
 * @brief Callback on new media streams captured by camera/microphone in the room.
 * @param rtcRoom The rtcRoom instance.
 * @param userId The ID of the remote user who published the stream.
 * @param type Media stream type. See ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}.
 * @note The local user will receive this callback after a remote user successfully published media streams captured by camera/microphone in the room with publishStream:{@link #ByteRTCRoom#publishStream:}. Then you can choose whether to call subscribeStream:mediaStreamType:{@link #ByteRTCRoom#subscribeStream:mediaStreamType:} to subscribe to the streams or not.
 */
- (void)rtcRoom:( ByteRTCRoom * _Nonnull)rtcRoom onUserPublishStream:(NSString *_Nonnull)userId type:(ByteRTCMediaStreamType)type;
/**
 * @locale zh
 * @type callback
 * @region 房间管理
 * @brief 房间内远端摄像头/麦克风采集的媒体流移除的回调。
 * @param rtcRoom ByteRTCRoom 实例
 * @param userId 移除的远端流发布用户的用户 ID。  
 * @param type 移除的远端流类型，参看 ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}。  
 * @param reason 远端流移除的原因，参看 ByteRTCStreamRemoveReason{@link #ByteRTCStreamRemoveReason}。
 * @note 收到该回调通知后，你可以自行选择是否调用 unsubscribeStream:mediaStreamType:{@link #ByteRTCRoom#unsubscribeStream:mediaStreamType:} 取消订阅此流。
 */
/**
 * @locale en
 * @type callback
 * @region Room management
 * @brief Callback on removal of remote media stream captured by camera/microphone.
 * @param rtcRoom The rtcRoom instance.
 * @param userId The ID of the remote user who removed the stream.
 * @param type Media stream type. See ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}.
 * @param reason The reason for the removal, see ByteRTCStreamRemoveReason{@link #ByteRTCStreamRemoveReason}.
 * @note After receiving this callback, the local user can choose whether to call unsubscribeStream:mediaStreamType:{@link #ByteRTCRoom#unsubscribeStream:mediaStreamType:} to unsubscribe from the streams or not.
 */
- (void)rtcRoom:( ByteRTCRoom * _Nonnull)rtcRoom onUserUnpublishStream:(NSString *_Nonnull)userId type:(ByteRTCMediaStreamType)type
           reason:(ByteRTCStreamRemoveReason)reason;
/**
 * @locale zh
 * @type callback
 * @region 房间管理
 * @brief 房间内新增远端屏幕共享音视频流的回调。
 * @param rtcRoom ByteRTCRoom实例
 * @param userId 远端流发布用户的用户 ID。
 * @param type 远端媒体流的类型，参看 ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}。
 * @note 当房间内的远端用户调用 publishScreen:{@link #ByteRTCRoom#publishScreen:} 成功发布来自屏幕共享的音视频流时，本地用户会收到该回调，此时本地用户可以自行选择是否调用 subscribeScreen:mediaStreamType:{@link #ByteRTCRoom#subscribeScreen:mediaStreamType:} 订阅此流。
 */
/**
 * @locale en
 * @type callback
 * @region Room management
 * @brief Callback on new screen sharing media streams from remote users in the room.
 * @param rtcRoom The rtcRoom instance.
 * @param userId The ID of the remote user who published the stream.
 * @param type Media stream type. See ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}.
 * @note The local user will receive this callback after a remote user successfully publishes screen sharing streams in the room with publishScreen:{@link #ByteRTCRoom#publishScreen:}. Then the local user can choose whether to call subscribeScreen:mediaStreamType:{@link #ByteRTCRoom#subscribeScreen:mediaStreamType:} to subscribe to the streams or not.
 */
- (void)rtcRoom:( ByteRTCRoom * _Nonnull)rtcRoom onUserPublishScreen:(NSString *_Nonnull)userId type:(ByteRTCMediaStreamType)type;
/**
 * @locale zh
 * @type callback
 * @region 房间管理
 * @brief 房间内远端屏幕共享音视频流移除的回调。
 * @param rtcRoom ByteRTCRoom 实例
 * @param userId 移除的远端流发布用户的用户 ID。  
 * @param type 移除的远端流类型，参看 ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}。  
 * @param reason 远端流移除的原因，参看 ByteRTCStreamRemoveReason{@link #ByteRTCStreamRemoveReason}。
 * @note 收到该回调通知后，你可以自行选择是否调用 unsubscribeScreen:mediaStreamType:{@link #ByteRTCRoom#unsubscribeScreen:mediaStreamType:} 取消订阅此流。
 */
/**
 * @locale en
 * @type callback
 * @region Room management
 * @brief Callback on removal of screen sharing media streams from remote users in the room.
 * @param rtcRoom The rtcRoom instance.
 * @param userId The ID of the remote user who removed the stream.
 * @param type Media stream type. See ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}.
 * @param reason The reason for the removal, see ByteRTCStreamRemoveReason{@link #ByteRTCStreamRemoveReason}.
 * @note After receiving this callback, the local can choose whether to call unsubscribeScreen:mediaStreamType:{@link #ByteRTCRoom#unsubscribeScreen:mediaStreamType:} to unsubscribe from the streams or not.
 */
- (void)rtcRoom:( ByteRTCRoom * _Nonnull)rtcRoom onUserUnpublishScreen:(NSString *_Nonnull)userId type:(ByteRTCMediaStreamType)type
           reason:(ByteRTCStreamRemoveReason)reason;
/**
 * @locale zh
 * @type callback
 * @region 房间管理
 * @brief 关于订阅媒体流状态改变的回调
 * @param rtcRoom ByteRTCRoom 对象
 * @param state 订阅媒体流状态，参看 ByteRTCSubscribeState{@link #ByteRTCSubscribeState}
 * @param userId 流发布用户的用户 ID
 * @param info 流的属性，参看 ByteRTCSubscribeConfig{@link #ByteRTCSubscribeConfig}
 * @note 本地用户收到该回调的时机包括：  <br>
 *        + 调用 subscribeStream:mediaStreamType:{@link #ByteRTCRoom#subscribeStream:mediaStreamType:} 或 unsubscribeStream:mediaStreamType:{@link #ByteRTCRoom#unsubscribeStream:mediaStreamType:} 订阅/取消订阅指定远端摄像头音视频流后；  <br>
 *        + 调用 subscribeScreen:mediaStreamType:{@link #ByteRTCRoom#subscribeScreen:mediaStreamType:} 或 unsubscribeScreen:mediaStreamType:{@link #ByteRTCRoom#unsubscribeScreen:mediaStreamType:} 订阅/取消订阅指定远端屏幕共享流后。
 */
/**
 * @locale en
 * @type callback
 * @region Room management
 * @brief Callback on subscription status of media streams
 * @param rtcRoom The r rtcRoom instance.
 * @param state Subscription status of media streams, see ByteRTCSubscribeState{@link #ByteRTCSubscribeState}.
 * @param userId The ID of the user who published the stream.
 * @param info Configurations of stream subscription, see ByteRTCSubscribeConfig{@link #ByteRTCSubscribeConfig}.
 * @note Local users will receive this callback:  <br>
 *        + After calling subscribeStream:mediaStreamType:{@link #ByteRTCRoom#subscribeStream:mediaStreamType:}/unsubscribeStream:mediaStreamType:{@link #ByteRTCRoom#unsubscribeStream:mediaStreamType:} to change the subscription status of remote media streams captured by camera/microphone.  <br>
 *        + After calling subscribeScreen:mediaStreamType:{@link #ByteRTCRoom#subscribeScreen:mediaStreamType:}/unsubscribeScreen:mediaStreamType:{@link #ByteRTCRoom#unsubscribeScreen:mediaStreamType:} to change the subscription status of remote screen sharing streams.
 */
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onStreamSubscribed:(ByteRTCSubscribeState)state
                userId:(NSString *_Nonnull)userId
       subscribeConfig:(ByteRTCSubscribeConfig *_Nonnull)info;

/**
 * @locale zh
 * @hidden for internal use only
 * @type callback
 * @region 多房间
 * @brief 当发布流成功的时候回调该事件
 * @param rtcRoom  ByteRTCRoom 对象。  
 * @param userId 用户ID
 * @param isScreen 该流是否是屏幕流<br>
 *
 */
/**
 * @locale en
 * @hidden for internal use only
 * @type callback
 * @region multiroom
 * @brief Callback the event
 * @param rtcRoom  ByteRTCRoom object when the release stream is successful. 
 * @param userId  User ID
 * @param isScreen  Whether the stream is a screen stream<br>
 *
 */

- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onStreamPublishSuccess:(NSString *_Nonnull)userId isScreen:(BOOL)isScreen;

 /**
  * @locale zh
  * @type callback
  * @region 多房间
  * @brief 收到房间中调用 sendRoomMessage:{@link #ByteRTCRoom#sendRoomMessage:} 发送的广播文本消息时，收到此回调。
  * @param rtcRoom ByteRTCRoom 对象
  * @param uid 消息发送者 ID 。
  * @param message 收到的文本消息内容。
  */
 /**
  * @locale en
  * @type callback
  * @region Multi-room
  * @brief Receive this callback when you receive a broadcast text message from the room called sendRoomMessage:{@link #ByteRTCRoom#sendRoomMessage:}.
  * @param rtcRoom ByteRTCRoom object
  * @param uid User ID of the message sender.
  * @param message The content of the received text message.
  */
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onRoomMessageReceived:(NSString *_Nonnull)uid
        message:(NSString *_Nonnull)message;

 /**
  * @locale zh
  * @type callback
  * @region 多房间
  * @brief 收到房间内广播二进制消息的回调。<br>
  *        房间内其他用户调用 sendRoomBinaryMessage:{@link #ByteRTCRoom#sendRoomBinaryMessage:} 发送的广播二进制消息时，收到此回调。
  * @param rtcRoom ByteRTCRoom 对象
  * @param uid 消息发送者 ID 。
  * @param message 收到的二进制消息内容。
  */
 /**
  * @locale en
  * @type callback
  * @region Multi-room
  * @brief Receive this callback when you receive a broadcast binary message sent by the room call sendRoomBinaryMessage:{@link #ByteRTCRoom#sendRoomBinaryMessage:}.
  * @param rtcRoom ByteRTCRoom object
  * @param uid User ID of the message sender.
  * @param message The binary message content received.
  */
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onRoomBinaryMessageReceived:(NSString *_Nonnull)uid
        message:(NSData *_Nonnull)message;

 /**
  * @locale zh
  * @type callback
  * @region 多房间
  * @brief 收到来自房间中其他用户通过 sendUserMessage:message:config:{@link #ByteRTCRoom#sendUserMessage:message:config:} 发来的点对点文本消息时，会收到此回调。
  * @param rtcRoom ByteRTCRoom 对象
  * @param uid 消息发送者的用户 ID 。
  * @param message 收到的文本消息内容。
  */
 /**
  * @locale en
  * @type callback
  * @region Multi-room
  * @brief Receive text messages (P2P) from other users in the room via sendUserMessage:message:config:{@link #ByteRTCRoom#sendUserMessage:message:config:}.
  * @param rtcRoom ByteRTCRoom object
  * @param uid The user ID of the sender of the message.
  * @param message The content of the received text message.
  */
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onUserMessageReceived:(NSString *_Nonnull)uid
               message:(NSString *_Nonnull)message;

 /**
 * @locale zh
 * @type callback
 * @region 多房间
 * @brief 收到来自房间中其他用户通过 sendUserBinaryMessage:message:config:{@link #ByteRTCRoom#sendUserBinaryMessage:message:config:} 发来的点对点二进制消息时，会收到此回调。
 * @param rtcRoom ByteRTCRoom 对象
 * @param uid 消息发送者的用户 ID 。
 * @param message 收到的二进制消息内容。
 */
/**
 * @locale en
 * @type callback
 * @region Multi-room
 * @brief Receive a binary message from another user in the room via sendUserBinaryMessage:message:config:{@link #ByteRTCRoom#sendUserBinaryMessage:message:config:} Receive this callback.
 * @param rtcRoom ByteRTCRoom object
 * @param uid The user ID of the sender of the message.
 * @param message The binary message content received.
 */
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onUserBinaryMessageReceived:(NSString *_Nonnull)uid
               message:(NSData *_Nonnull)message;

 /**
  * @locale zh
  * @type callback
  * @region 多房间
  * @brief 向房间内单个用户发送文本或二进制消息后（P2P），消息发送方会收到该消息发送结果回调。
  * @param rtcRoom ByteRTCRoom 对象。
  * @param msgid 本条消息的 ID。
  * @param error 消息发送结果，详见 ByteRTCUserMessageSendResult{@link #ByteRTCUserMessageSendResult}
  * @note  
  *        + 你应调用 sendUserMessage:message:config:{@link #ByteRTCRoom#sendUserMessage:message:config:} 向房间内单个用户发送文本消息 <br>
  *        + 你应调用 sendUserBinaryMessage:message:config:{@link #ByteRTCRoom#sendUserBinaryMessage:message:config:} 向房间内单个用户发送二进制消息
  */
 /**
  * @locale en
  * @type callback
  * @region Multi-room
  * @brief After sending a text or binary message (P2P) to a single user in the room, the message sender will receive a callback with the result of the message.
  * @param rtcRoom ByteRTCRoom object.
  * @param msgid The ID of this message.
  * @param error Message result. See ByteRTCUserMessageSendResult{@link #ByteRTCUserMessageSendResult}
  * @note   
  *         + You should call sendUserMessage:message:config:{@link #ByteRTCRoom#sendUserMessage:message:config:} to send a text message to a single user in the room <br>
  *         + You should call sendUserBinaryMessage:message:config:{@link #ByteRTCRoom#sendUserBinaryMessage:message:config:} to send a binary message to a single user in the room
  */
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onUserMessageSendResult:(NSInteger)msgid error:(ByteRTCUserMessageSendResult)error;

 /**
  * @locale zh
  * @type callback
  * @region 多房间
  * @brief 调用 sendRoomMessage:{@link #ByteRTCRoom#sendRoomMessage:} 或 sendRoomBinaryMessage:{@link #ByteRTCRoom#sendRoomBinaryMessage:} 向房间内群发文本或二进制消息后，消息发送方会收到该消息发送结果回调。
  * @param rtcRoom ByteRTCRoom 对象。
  * @param msgid 本条消息的 ID。
  * @param error 消息发送结果，详见 ByteRTCRoomMessageSendResult{@link #ByteRTCRoomMessageSendResult}
  */
 /**
  * @locale en
  * @type callback
  * @region Multi-room
  * @brief Receives this callback after sending a text message or a binary message to a room with sendRoomMessage:{@link #ByteRTCRoom#sendRoomMessage:} or sendRoomBinaryMessage:{@link #ByteRTCRoom#sendRoomBinaryMessage:}.
  * @param rtcRoom ByteRTCRoom object.
  * @param msgid The ID of this message.
  * @param error  Message sending results. See ByteRTCRoomMessageSendResult{@link #ByteRTCRoomMessageSendResult}
  * @note   
  *         + You should call sendRoomMessage:{@link #ByteRTCRoom#sendRoomMessage:} Send a mass text message to the room <br>
  *         + You should call sendRoomBinaryMessage:{@link #ByteRTCRoom#sendRoomBinaryMessage:} Send a mass binary message to the room
  */
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onRoomMessageSendResult:(NSInteger)msgid error:(ByteRTCRoomMessageSendResult)error;

/**
 * @locale zh
 * @valid since 3.52.
 * @type callback
 * @region 多房间
 * @brief 调用 setRoomExtraInfo:value:{@link #ByteRTCRoom#setRoomExtraInfo:value:} 结果回调。
 * @param rtcRoom ByteRTCRoom 对象。
 * @param taskId 本次调用的任务编号。
 * @param error 设置房间附加信息结果，详见 ByteRTCSetRoomExtraInfoResult{@link #ByteRTCSetRoomExtraInfoResult}
 */
/**
 * @locale en
 * @valid since 3.52.
 * @type callback
 * @region Multi-room
 * @brief Receives this callback after invoke setRoomExtraInfo:value:{@link #ByteRTCRoom#setRoomExtraInfo:value:}.
 * @param rtcRoom ByteRTCRoom object.
 * @param taskId The ID of this setRoomExtraInfo invoke.
 * @param error setRoomExtraInfo result. See ByteRTCSetRoomExtraInfoResult{@link #ByteRTCSetRoomExtraInfoResult}
 */
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onSetRoomExtraInfoResult:(NSInteger)taskId error:(ByteRTCSetRoomExtraInfoResult)error;

/**
 * @locale zh
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
/**
 * @locale en
 * @valid since 3.52.
 * @type callback
 * @region Multi-room
 * @brief Receive a callback when other user invoke setRoomExtraInfo:value:{@link #ByteRTCRoom#setRoomExtraInfo:value:} . <br>
 *        or when user joinRoom success and this room has room extra info.
 * @param rtcRoom ByteRTCRoom object.
 * @param key Key of room attribute
 * @param value Key of room attribute
 * @param lastUpdateUserId The userId that last updated this attribute
 * @param lastUpdateTimeMs The last time this attribute was updated, in milliseconds，unixtime style  
 */
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onRoomExtraInfoUpdate:(NSString *_Nonnull)key value:(NSString *_Nonnull)value lastUpdateUserId:(NSString *_Nonnull)lastUpdateUserId 
                 lastUpdateTimeMs:(NSInteger)lastUpdateTimeMs;

/**
 * @locale zh
 * @valid since 3.54
 * @type callback
 * @region 房间管理
 * @brief 用户调用 setUserVisibility:{@link #ByteRTCRoom#setUserVisibility:} 设置用户可见性的回调。
 * @param currentUserVisibility 当前用户的可见性。  <br>
 *        + YES: 可见，用户可以在房间内发布音视频流，房间中的其他用户将收到用户的行为通知，例如进房、开启视频采集和退房。<br>
 *        + NO: 不可见，用户不可以在房间内发布音视频流，房间中的其他用户不会收到用户的行为通知，例如进房、开启视频采集和退房。
 * @param errorCode 设置用户可见性错误码，参看 ByteRTCUserVisibilityChangeError{@link #ByteRTCUserVisibilityChangeError}。
 */
/**
 * @locale en
 * @valid since 3.54
 * @type callback
 * @region Room Management
 * @brief Callback for user to set user visibility by calling setUserVisibility:{@link #ByteRTCRoom#setUserVisibility:}.
 * @param currentUserVisibility Visibility of the current user.<br>
 *        + YES: Visible. The user can publish media streams. The other users in the room get informed of the behaviors of the user, such as joining room, starting video capture, and leaving room.<br>
 *        + NO: Invisible. The user cannot publish media streams. The other users in the room do not get informed of the behaviors of the user, such as joining room, starting video capture, or leaving room.
 * @param errorCode Error code for setting user visibility. See ByteRTCUserVisibilityChangeError{@link #ByteRTCUserVisibilityChangeError}.
 */
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onUserVisibilityChanged:(BOOL)currentUserVisibility errorCode:(ByteRTCUserVisibilityChangeError)errorCode;

/**
 * @locale zh
 * @type callback
 * @region 视频管理
 * @brief 通过调用服务端 BanUserStream/UnbanUserStream 方法禁用/解禁指定房间内指定用户视频流的发送时，触发此回调。
 * @param uid 被禁用/解禁的视频流用户 ID
 * @param banned 视频流发送状态 <br>
 *        + true: 视频流发送被禁用 <br>
 *        + false: 视频流发送被解禁
 * @note  
 *        + 房间内指定用户被禁止/解禁视频流发送时，房间内所有用户都会收到该回调。  <br>
 *        + 若被封禁用户断网或退房后再进房，则依然是封禁状态，且房间内所有人会再次收到该回调。  <br>
 *        + 指定用户被封禁后，房间内其他用户退房后再进房，会再次收到该回调。  <br>
 *        + 同一房间解散后再次创建，房间内状态清空。
 */
/**
 * @locale en
 * @type callback
 * @region Video management
 * @brief All the users in the room will get informed via this callback when a user is banned or the ban of the user has been lifted by calling BanUserStream/UnbanUserStream on the server side.
 * @param uid Disabled/unbanned video stream user ID
 * @param banned Video stream sending status <br>
 *         + true: Video stream sending is disabled <br>
 *         + false: Video stream sending is unbanned
 * @note   
 *         + When the specified user in the room is banned/unbanned video stream sending, all users in the room will receive the callback. <br>
 *         + If the banned user leaves or disconnects and then rejoins the room, the user is still banned from publishing audio stream, and all users in the room will be informed via the callback. <br>
 *         + After the specified user is banned, other users in the room will check out and enter the room again, and will receive the callback again. <br>
 *         + After the same room is disbanded and created again, the status in the room is cleared.
 */
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onVideoStreamBanned:(NSString *_Nonnull)uid isBanned:(BOOL)banned;

/**
 * @locale zh
 * @type callback
 * @region 音频事件回调
 * @brief 通过调用服务端 BanUserStream/UnbanUserStream 方法禁用/解禁指定房间内指定用户音频流的发送时，触发此回调。
 * @param uid 被禁用/解禁的音频流用户 ID
 * @param banned 音频流发送状态 <br>
 *        + true: 音频流发送被禁用 <br>
 *        + false: 音频流发送被解禁
 * @note  
 *        + 房间内指定用户被禁止/解禁音频流发送时，房间内所有用户都会收到该回调。  <br>
 *        + 若被封禁用户断网或退房后再进房，则依然是封禁状态，且房间内所有人会再次收到该回调。  <br>
 *        + 指定用户被封禁后，房间内其他用户退房后再进房，会再次收到该回调。  <br>
 *        + 在控制台开启音频选路后，只有被封禁/解禁用户会收到该回调。<br>
 *        + 同一房间解散后再次创建，房间内状态清空。
 */
/**
 * @locale en
 * @type callback
 * @region Audio event callback
 * @brief All the users in the room will get informed via this callback when a user is banned or the ban of the user has been lifted by calling BanUserStream/UnbanUserStream on the server side.
 * @param uid Disabled/unbanned audio stream user ID
 * @param banned Audio stream sending status <br>
 *         + true: Audio stream sending is disabled <br>
 *         + false: Audio stream sending is unbanned
 * @note   
 *         + When the specified user in the room is disabled/unbanned audio stream sending, all users in the room will receive the callback. <br>
 *        + If the banned user leaves or disconnects and then rejoins the room, the user is still banned from publishing audio stream, and all users in the room will be informed via the callback. <br>
 *         + After the specified user is banned, other users in the room will check out and enter the room again, and will receive the callback again. <br>
 *         + After the same room is disbanded and created again, the status in the room is cleared. <br>
 *         + If the Audio selection is enabled in the console, only the user whose stream is banned will receive this callback.
 */
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onAudioStreamBanned:(NSString *_Nonnull)uid isBanned:(BOOL)banned;

#pragma mark ForwardStream related callback
    /**
     * @locale zh
     * @type callback
     * @region 多房间
     * @brief 跨房间媒体流转发状态和错误回调
     * @param rtcRoom ByteRTCRoom 对象
     * @param infos 跨房间媒体流转发目标房间信息数组，详见 ByteRTCForwardStreamStateInfo{@link #ByteRTCForwardStreamStateInfo}
     */
    /**
     * @locale en
     * @type callback
     * @region Multi-room
     * @brief Callback returning the state and errors during relaying the media stream to each of the rooms
     * @param rtcRoom ByteRTCRoom object
     * @param infos Array of the state and errors of each designated room. Refer to ByteRTCForwardStreamStateInfo{@link #ByteRTCForwardStreamStateInfo} for more information.
     */
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onForwardStreamStateChanged:(NSArray<ByteRTCForwardStreamStateInfo *> * _Nonnull)infos;
    /**
     * @locale zh
     * @type callback
     * @region 多房间
     * @brief 跨房间媒体流转发事件回调
     * @param rtcRoom ByteRTCRoom 对象
     * @param infos 跨房间媒体流转发目标房间事件数组，详见 ByteRTCForwardStreamEventInfo{@link #ByteRTCForwardStreamEventInfo}
     */
    /**
     * @locale en
     * @type callback
     * @region Multi-room
     * @brief Callback returning the events during relaying the media stream to each room
     * @param rtcRoom RTCRoom object
     * @param infos Array of the event of each designated room. Refer to ByteRTCForwardStreamEventInfo{@link #ByteRTCForwardStreamEventInfo} for more information.
     */
- (void)rtcRoom:( ByteRTCRoom * _Nonnull)rtcRoom onForwardStreamEvent:(NSArray<ByteRTCForwardStreamEventInfo *> * _Nonnull)infos;

/**
 * @locale zh
 * @type callback
 * @brief 加入房间并发布或订阅流后， 以每 2 秒一次的频率，报告本地用户和已订阅的远端用户的上下行网络质量信息。
 * @param rtcRoom ByteRTCRoom 对象
 * @param localQuality 本端网络质量，详见 ByteRTCNetworkQualityStats{@link #ByteRTCNetworkQualityStats}。
 * @param remoteQualities 已订阅用户的网络质量，详见 ByteRTCNetworkQualityStats{@link #ByteRTCNetworkQualityStats}。
 * @note 更多通话中的监测接口，详见[通话中质量监测](https://www.volcengine.com/docs/6348/106866)。
 */
/**
 * @locale en
 * @type callback
 * @brief Report the network quality of the users every 2s after the local user joins the room and starts publishing or subscribing to a stream.
 * @param rtcRoom ByteRTCRoom object
 * @param localQuality Local network quality. Refer to ByteRTCNetworkQualityStats{@link #ByteRTCNetworkQualityStats}.
 * @param remoteQualities Network quality of the subscribed users. Refer to ByteRTCNetworkQualityStats{@link #ByteRTCNetworkQualityStats} for details.
 * @note See [In-call Stats](106866) for more information.
 */
- (void)rtcRoom:(ByteRTCRoom * _Nonnull)rtcRoom onNetworkQuality:(ByteRTCNetworkQualityStats *_Nonnull)localQuality remoteQualities:(NSArray<ByteRTCNetworkQualityStats*> *_Nonnull)remoteQualities;

/**
 * @locale zh
 * @type callback
 * @region 字幕翻译服务
 * @brief  字幕状态发生改变回调。 <br>
 *         当用户调用 startSubtitle:{@link #ByteRTCRoom#startSubtitle:} 和 stopSubtitle{@link #ByteRTCRoom#stopSubtitle} 使字幕状态发生改变或出现错误时，触发该回调。 
 * @param rtcRoom ByteRTCRoom 实例。
 * @param state 字幕状态。参看 ByteRTCSubtitleState{@link #ByteRTCSubtitleState}。
 * @param errorCode   字幕任务错误码。参看 ByteRTCSubtitleErrorCode{@link #ByteRTCSubtitleErrorCode}。
 * @param errorMessage  第三方服务出现的错误。当因第三方服务出现错误，导致字幕状态改变时，用户可通过此参数获取具体的错误信息。如果不是因为第三方服务导致字幕状态改变，该字段为空。
 */
/**
 * @locale en
 * @hidden currently not available 
 * @type callback
 * @region Subtitle translation service
 * @brief  Callback on subtitle states. <br>
 *         After you call startSubtitle:{@link #ByteRTCRoom#startSubtitle:} and stopSubtitle{@link #ByteRTCRoom#stopSubtitle}, you will receive this callback which informs you of the states and error codes of the subtitling task, as well as detailed information on the third party services' errors. 
 * @param rtcRoom ByteRTCRoom instance.
 * @param state The states of subtitles. Refer to ByteRTCSubtitleState{@link #ByteRTCSubtitleState} for details.
 * @param errorCode  Error codes of the subtitling task. Refer to  ByteRTCSubtitleErrorCode{@link #ByteRTCSubtitleErrorCode} for details.
 * @param errorMessage  Detailed information on the third party services' errors. If the states of subtitles are changed due to the third party services, you will receive this parameter which informs you of the detailed information on the third party services' errors.
 */
- (void)rtcRoom:( ByteRTCRoom *_Nonnull)rtcRoom onSubtitleStateChanged:(ByteRTCSubtitleState)state
                                                             errorCode:(ByteRTCSubtitleErrorCode)errorCode
                                                          errorMessage:(NSString *_Nonnull)errorMessage;
                                                          
/**
 * @locale zh
 * @type callback
 * @region 字幕翻译服务
 * @brief  字幕相关内容回调。 <br>
 *         当用户调用 startSubtitle:{@link #ByteRTCRoom#startSubtitle:} 后会收到此回调，通知字幕的相关信息。
 * @param rtcRoom ByteRTCRoom 实例。
 * @param subtitles  字幕消息内容。参看 ByteRTCSubtitleMessage{@link #ByteRTCSubtitleMessage}。
 */
/**
 * @locale en
 * @hidden currently not available 
 * @type callback
 * @region Subtitle translation service
 * @brief Callback on subtitle messages.  <br>
 *        After calling startSubtitle:{@link #ByteRTCRoom#startSubtitle:}, you will receive this callback which informs you of the related information on subtitles. 
 * @param rtcRoom ByteRTCRoom instance.
 * @param subtitles  Subtitle messages. Refer to ByteRTCSubtitleMessage{@link #ByteRTCSubtitleMessage} for details. 
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
 * @locale zh
 * @type api
 * @region 多房间
 * @brief 退出并销毁调用 createRTCRoom:{@link #ByteRTCVideo#createRTCRoom:} 所创建的房间实例。
 */
/**
 * @locale en
 * @type api
 * @region multi-room
 * @brief Leave and destroy the room instance created by calling createRTCRoom:{@link #ByteRTCVideo#createRTCRoom:}.
 */
- (void)destroy;

/**
 * @locale zh
 * @type api
 * @valid since 3.53
 * @brief 获取房间 ID。
 * @return 房间 ID。
 */
/**
 * @locale en
 * @type api
 * @brief Get room ID.
 * @return Room ID.
 */
- (NSString *_Nonnull)getRoomId;

/**
 * @locale zh
 * @type api
 * @region 多房间
 * @brief 通过设置 ByteRTCRoom{@link #ByteRTCRoom} 对象的事件句柄，监听此对象对应的回调事件。
 * @param roomDelegate 参见 ByteRTCRoomDelegate{@link #ByteRTCRoomDelegate}。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 */
/**
 * @locale en
 * @type api
 * @region Multi-room
 * @brief Listens for event callbacks related to the ByteRTCRoom{@link #ByteRTCRoom} instance by setting the event handler of this instance.
 * @param roomDelegate Refer to ByteRTCRoomDelegate{@link #ByteRTCRoomDelegate}.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 */

- (int)setRTCRoomDelegate:(id<ByteRTCRoomDelegate> _Nullable)roomDelegate;

/**
 * @locale zh
 * @type api
 * @region 多房间
 * @brief 加入房间。<br>
 *        调用 createRTCRoom:{@link #ByteRTCVideo#createRTCRoom:} 创建房间后，调用此方法加入房间，同房间内其他用户进行音视频通话。  
 * @param token 动态密钥，用于对进房用户进行鉴权验证。  <br>
 *        进入房间需要携带 Token。测试时可使用控制台生成临时 Token，正式上线需要使用密钥 SDK 在你的服务端生成并下发 Token。Token 有效期及生成方式参看[使用 Token 完成鉴权](70121)。  <br>
 *        使用不同 AppID 的 App 是不能互通的。  <br>
 *        请务必保证生成 Token 使用的 AppID 和创建引擎时使用的 AppID 相同，否则会导致加入房间失败。
 * @param userInfo 用户信息。参看 ByteRTCUserInfo{@link #ByteRTCUserInfo}。  
 * @param roomConfig 房间参数配置，设置房间模式以及是否自动发布或订阅流。具体配置模式参看 ByteRTCRoomConfig{@link #ByteRTCRoomConfig}。  
 * @return 方法调用结果。  <br>
 *        +  0: 成功  <br>
 *        + -1: 参数无效  <br>
 *        + -2: 已经在房间内。接口调用成功后，只要收到返回值为 0 ，且未调用 leaveRoom{@link #ByteRTCRoom#leaveRoom} 成功，则再次调用进房接口时，无论填写的房间 ID 和用户 ID 是否重复，均触发此返回值。  <br>
 *        调用失败时，具体失败原因会通过 rtcRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onRoomStateChanged:withUid:state:extraInfo:} 回调告知。  
 * @note  
 *        + 同一个 AppID 的同一个房间内，每个用户的用户 ID 必须是唯一的。如果两个用户的用户 ID 相同，则后加入房间的用户会将先加入房间的用户踢出房间，并且先加入房间的用户会收到 rtcRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onRoomStateChanged:withUid:state:extraInfo:} 回调通知，错误类型为重复登录 ByteRTCErrorCodeDuplicateLogin。  <br>
 *        + 本地用户调用此方法加入房间成功后，会收到 rtcRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onRoomStateChanged:withUid:state:extraInfo:} 回调通知。若本地用户同时为可见用户，加入房间时远端用户会收到 rtcRoom:onUserJoined:elapsed:{@link #ByteRTCRoomDelegate#rtcRoom:onUserJoined:elapsed:} 回调通知。<br>
 *        + 房间内不可见用户的容量远远大于可见用户，而且用户默认可见，因此对于不参与互动的用户，你需要调用 setUserVisibility:{@link #ByteRTCRoom#setUserVisibility:} 更改为不可见用户。从而避免因房间内用户达到数量上限所导致的进房失败。默认情况下，一个 RTC 房间最多同时容纳 50 名可见用户，其中最多 30 人可同时上麦，更多信息参看[用户和媒体流上限](https://www.volcengine.com/docs/6348/257549)。<br>
 *        + 用户加入房间成功后，在本地网络状况不佳的情况下，SDK 可能会与服务器失去连接，并触发 rtcEngine:onConnectionStateChanged:{@link #ByteRTCVideoDelegate#rtcEngine:onConnectionStateChanged:} 回调。此时 SDK 会自动重试，直到成功重连。重连成功后，本地会收到 rtcRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onRoomStateChanged:withUid:state:extraInfo:}。
 */
/**
 * @locale en
 * @type api
 * @region Multiple rooms
 * @brief Join the room. <br>
 *        After creating a room by calling createRTCRoom:{@link #ByteRTCVideo#createRTCRoom:}, call this API to join the room and make audio & video calls with other users in the room. 
 * @param token Dynamic key for authentication and verification of users entering the room. <br>
 *         You need to bring Token to enter the room. When testing, you can use the console to generate temporary tokens. The official launch requires the use of the key SDK to generate and issue tokens at your server level. See [Authentication with Token](70121) for token validity and generation method. <br>
 *         Apps with different AppIDs are not interoperable. <br>
 *         Make sure that the AppID used to generate the Token is the same as the AppID used to create the engine, otherwise it will cause the join room to fail.
 * @param userInfo User information. See ByteRTCUserInfo{@link #ByteRTCUserInfo}. 
 * @param roomConfig Room parameter configuration, set the room mode and whether to automatically publish or subscribe to the flow. See ByteRTCRoomConfig{@link #ByteRTCRoomConfig} for the specific configuration mode. 
 * @return  Method call result.   <br>
 *         + 0: Success <br>
 *         + -1: Invalid parameter <br>
 *         + -2: Already in the room. After the interface call is successful, as long as the return value of 0 is received and leaveRoom{@link #ByteRTCRoom#leaveRoom} is not called successfully, this return value will be triggered when the room entry interface is called again, regardless of whether the filled room ID and user ID are duplicated. <br>
 *         The reason for the failure will be communicated via the rtcRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onRoomStateChanged:withUid:state:extraInfo:} callback.
 * @note   
 *         + In the same room with the same AppID, the user ID of each user must be unique. If two users have the same user ID, the user who joined the room later will kick the user who joined the room first out of the room, and the user who joined the room first will receive rtcRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onRoomStateChanged:withUid:state:extraInfo:} callback notification, the error type is duplicate login ByteRTCErrorCodeDuplicateLogin。. <br>
 *         + Local users will receive rtcRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onRoomStateChanged:withUid:state:extraInfo:} callback notification after calling this method to join the room successfully. If the local user is also a visible user, the remote user will receive an rtcRoom:onUserJoined:elapsed:{@link #ByteRTCRoomDelegate#rtcRoom:onUserJoined:elapsed:} callback notification when joining the room.<br>
 *         + By default, the user is visible in an RTC room. Joining fails when the number of users in an RTC room reaches its upper limit. To avoid this, call setUserVisibility:{@link #ByteRTCRoom#setUserVisibility:} to change the visibility of the audience users to `false` by considering the capacity for the invisible users is much larger than that for visible users. An RTC room can accommodate a maximum of 50 visible users, and 30 media streams can be published simultaneously. For more information, see [Capability of Users and Streams](https://docs.byteplus.com/en/byteplus-rtc/docs/257549). <br>
 *         + After the user successfully joins the room, the SDK may lose connection to the server in case of poor local network conditions. At this time rtcEngine:onConnectionStateChanged:{@link #ByteRTCVideoDelegate#rtcEngine:onConnectionStateChanged:} callback will be triggered and the SDK will automatically retry until it successfully reconnects to the server. After successful reconnection, you will receive a callback notification from rtcRoom:onUserJoined:elapsed:{@link #ByteRTCRoomDelegate#rtcRoom:onUserJoined:elapsed:} locally.
 */
- (int)joinRoom:(NSString *_Nullable)token userInfo:(ByteRTCUserInfo *_Nonnull)userInfo roomConfig:(ByteRTCRoomConfig *_Nonnull)roomConfig NS_SWIFT_NAME(joinRoom(_:userInfo:roomConfig:));

/**
 * @locale zh
 * @type api
 * @region 多房间
 * @brief 设置用户可见性。未调用该接口前，本地用户默认对他人可见。<br>
 *        默认情况下，一个 RTC 房间最多同时容纳 50 名可见用户，最多 30 人可同时上麦。更多信息参看[用户和媒体流上限](https://www.volcengine.com/docs/6348/257549)。
 * @param enable 设置用户是否对房间内其他用户可见：  <br>
 *        + YES: 可见，用户可以在房间内发布音视频流，房间中的其他用户将收到用户的行为通知，例如进房、开启视频采集和退房。<br>
 *        + NO: 不可见，用户不可以在房间内发布音视频流，房间中的其他用户不会收到用户的行为通知，例如进房、开启视频采集和退房。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0: 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明。
 * @note  
 *       + 在加入房间前后，用户均可调用此方法设置用户可见性。<br>
 *       + 设置用户可见性，会收到设置成功/失败回调 rtcRoom:onUserVisibilityChanged:errorCode:{@link #ByteRTCRoomDelegate#rtcRoom:onUserVisibilityChanged:errorCode:}。（v3.54 新增）<br>
 *   &#x0020;  • 在加入房间前设置用户可见性，若设置的可见性与默认值不同，将在加入房间时触发本回调。<br>
 *   &#x0020;  • 在加入房间后设置用户可见性，若可见性前后不同，会触发本回调。<br>
 *   &#x0020;  • 在断网重连后，若可见性发生改变，会触发本回调。<br>
 *       + 在房间内，调用此方法成功切换用户可见性后，房间内其他用户会收到相应的回调。<br>
 *   &#x0020;  • 从可见换至不可见时，房间内其他用户会收到 rtcRoom:onUserLeave:reason:{@link #ByteRTCRoomDelegate#rtcRoom:onUserLeave:reason:}。<br>
 *   &#x0020;  • 从不可见切换至可见时，房间内其他用户会收到 rtcRoom:onUserJoined:elapsed:{@link #ByteRTCRoomDelegate#rtcRoom:onUserJoined:elapsed:}。<br>
 *   &#x0020;  • 若调用该方法将可见性设为 `false`，此时尝试发布流会收到 `ByteRTCWarningCodeSubscribeStreamForbiden` 警告。
 */
/**
 * @locale en
 * @type api
 * @region Room management
 * @brief Set the visibility of the user in the room. The local user is visible to others by default before calling this API.<br>
 *        An RTC room can accommodate a maximum of 50 visible users, and 30 media streams can be published simultaneously. For more information, see [Room Capacity](https://docs.byteplus.com/en/byteplus-rtc/docs/257549).
 * @param enable Visibility of the user in the room. <br>
 *        + YES: The user can publish media streams. The other users in the room get informed of the behaviors of the user, such as joining room, starting video capture, and leaving room.<br>
 *        + NO: The user cannot publish media streams. The other users in the room do not get informed of the behaviors of the user, such as joining room, starting video capture, or leaving room.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details.
 * @note   
 *        + You can call this API whether the user is in a room or not.<br>
 *        + You will receive rtcRoom:onUserVisibilityChanged:errorCode:{@link #ByteRTCRoomDelegate#rtcRoom:onUserVisibilityChanged:errorCode:} after calling this API. (Available since v3.54)<br>
 *   &#x0020;  • If you call this API before joining room, and the set value is different from the default value, you will receive the callback when you join the room.<br>
 *   &#x0020;  • If you call this API after joining room, and the current visibility is different from the previous value, you will receive the callback.<br>
 *   &#x0020;  • When reconnecting after losing internet connection, if the visibility changes, you will receive the callback. <br>
 *        + When you call this API while you are in the room, the other users in the room will be informed via the following callback.<br>
 *   &#x0020;  • When you switch from `false` to `true`, they will receive rtcRoom:onUserJoined:elapsed:{@link #ByteRTCRoomDelegate#rtcRoom:onUserJoined:elapsed:}.<br>
 *   &#x0020;  • When you switch from `true` to `false`, they will receive rtcRoom:onUserLeave:reason:{@link #ByteRTCRoomDelegate#rtcRoom:onUserLeave:reason:}.<br>
 *   &#x0020;  • The invisible user will receive the warning code, `ByteRTCWarningCodeSubscribeStreamForbiden`, when trying to publish media streams.
 */
- (int)setUserVisibility:(BOOL)enable;

/**
 * @locale zh
 * @type api
 * @region 多房间
 * @brief 设置发流端音画同步。  <br>
 *        当同一用户同时使用两个通话设备分别采集发送音频和视频时，有可能会因两个设备所处的网络环境不一致而导致发布的流不同步，此时你可以在视频发送端调用该接口，SDK 会根据音频流的时间戳自动校准视频流，以保证接收端听到音频和看到视频在时间上的同步性。
 * @param audioUserId 音频发送端的用户 ID，将该参数设为空则可解除当前音视频的同步关系。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note 
 *        + 该方法在进房前后均可调用。  <br>
 *        + 进行音画同步的音频发布用户 ID 和视频发布用户 ID 须在同一个 RTC 房间内。  <br>
 *        + 调用该接口后音画同步状态发生改变时，你会收到 rtcRoom:onAVSyncStateChange:{@link #ByteRTCRoomDelegate#rtcRoom:onAVSyncStateChange:} 回调。  <br>
 *        + 同一 RTC 房间内允许存在多个音视频同步关系，但需注意单个音频源不支持与多个视频源同时同步。  <br>
 *        + 如需更换同步音频源，再次调用该接口传入新的 `audioUserId` 即可；如需更换同步视频源，需先解除当前的同步关系，后在新视频源端开启同步。
 */
/**
 * @locale en
 * @type api
 * @region Multi-room
 * @brief Synchronizes published audio and video.  <br>
 *        When the same user simultaneously uses separate devices to capture and publish audio and video, there is a possibility that the streams are out of sync due to the network disparity. In this case, you can call this API on the video publisher side and the SDK will automatically line the video stream up according to the timestamp of the audio stream, ensuring that the audio the receiver hears corresponds to the video the receiver watches.
 * @param audioUserId The ID of audio publisher. You can stop the current A/V synchronization by setting this parameter to null.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note  
 *        + You can call this API anytime before or after entering the room.  <br>
 *        + The source user IDs of the audio and video stream to be synchronized must be in the same RTC room.  <br>
 *        + When the A/V synchronization state changes, you will receive rtcRoom:onAVSyncStateChange:{@link #ByteRTCRoomDelegate#rtcRoom:onAVSyncStateChange:}.  <br>
 *        + More than one pair of audio and video can be synchronized simultaneously in the same RTC room, but you should note that one single audio source cannot be synchronized with multiple video sources at the same time.  <br>
 *        + If you want to change the audio source, call this API again with a new `audioUserId`. If you want to change the video source, you need to stop the current synchronization first, then call this API on the new video publisher side.
 */
- (int)setMultiDeviceAVSync:(NSString* _Nullable) audioUserId;

/**
 * @locale zh
 *  @type api
 *  @region 房间管理
 *  @brief 离开房间。  <br>
 *         用户调用此方法离开房间，结束通话过程，释放所有通话相关的资源。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note  
 *        + 用户离开房间后，本地会收到 rtcRoom:onLeaveRoom:{@link #ByteRTCRoomDelegate#rtcRoom:onLeaveRoom:} 的回调；  <br>
 *        + 调用 setUserVisibility:{@link #ByteRTCRoom#setUserVisibility:} 方法将自身设为可见的用户离开房间后，房间内其他用户会收到 rtcRoom:onUserLeave:reason:{@link #ByteRTCRoomDelegate#rtcRoom:onUserLeave:reason:} 回调通知。  
 */
/**
 * @locale en
 *  @type api
 *  @region room management
 *  @brief Leaves the room.   <br>
 *         The user calls this method to leave the room, end the call process, and release all call-related resources.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note   
 *         + After the user leaves the room, the local will receive a callback for rtcRoom:onLeaveRoom:{@link #ByteRTCRoomDelegate#rtcRoom:onLeaveRoom:}; <br>
 *         + Call setUserVisibility:{@link #ByteRTCRoom#setUserVisibility:} method sets itself to be visible. After the user leaves the room, other users in the room will receive rtcRoom:onUserLeave:reason:{@link #ByteRTCRoomDelegate#rtcRoom:onUserLeave:reason:} callback notification. 
 */
- (int)leaveRoom NS_SWIFT_NAME(leaveRoom());


/**
 * @locale zh
 * @type api
 * @brief 更新 Token。<br>
 *        收到 onTokenWillExpire:{@link #ByteRTCRoomDelegate#onTokenWillExpire:}，onPublishPrivilegeTokenWillExpire:{@link #ByteRTCRoomDelegate#onPublishPrivilegeTokenWillExpire:}，或 onSubscribePrivilegeTokenWillExpire:{@link #ByteRTCRoomDelegate#onSubscribePrivilegeTokenWillExpire:} 时，你必须重新获取 Token，并调用此方法更新 Token，以保证通话的正常进行。
 * @param token 重新获取的有效 Token。<br>
 *        如果 Token 无效，你会收到 rtcRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onRoomStateChanged:withUid:state:extraInfo:}，错误码是 `-1010`。
 * @return 
 *        + 0：成功；<br>
 *        + !0：失败。
 * @note 请勿同时调用 updateToken:{@link #ByteRTCRoom#updateToken:} 和 joinRoom:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoom:userInfo:roomConfig:} 重新加入房间。
 */
/**
 * @locale en
 * @type api
 * @brief Update Token. <br>
 *        You must call this API to update token to ensure the RTC call to continue when you receive onTokenWillExpire:{@link #ByteRTCRoomDelegate#onTokenWillExpire:}, onPublishPrivilegeTokenWillExpire:{@link #ByteRTCRoomDelegate#onPublishPrivilegeTokenWillExpire:}, or onSubscribePrivilegeTokenWillExpire:{@link #ByteRTCRoomDelegate#onSubscribePrivilegeTokenWillExpire:}.
 * @param token  Valid token.<br>
 *        If the Token is invalid, you will receive rtcRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onRoomStateChanged:withUid:state:extraInfo:} with the error code of `-1010`.
 * @return  
 *        + 0: Success <br>
 *        + !0: Failure
 * @note 
 *      + In versions before 3.50, the publish and subscribe privileges contained in the Token are reserved parameters with no actual control permissions. In version 3.50 and later, the publish/subscribe privileges will be effective for whitelisted users. Please contact the technical support team to include you in the whitelist if you need this function.<br>
 *      + Do not call both updateToken:{@link #ByteRTCRoom#updateToken:} and joinRoom:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoom:userInfo:roomConfig:} to update the Token. If you fail to join the room or have been removed from the room due to an expired or invalid Token, call joinRoom:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoom:userInfo:roomConfig:} with a valid token to rejoin the room.
 */
- (int)updateToken:(NSString *_Nullable)token;
/**
 * @locale zh
 * @type api
 * @region 视频管理
 * @brief 设置期望订阅的远端视频流的参数。
 * @param userId 期望配置订阅参数的远端视频流发布用户的 ID。
 * @param remoteVideoConfig 期望配置的远端视频流参数，参看 ByteRTCRemoteVideoConfig{@link #ByteRTCRemoteVideoConfig}。
 * @return 方法调用结果： <br>
 *        + 0：成功；<br>
 *        + !0：失败。
 * @note 
 *        + 若使用 342 及以前版本的 SDK，调用该方法前请联系技术支持人员开启按需订阅功能。  <br>
 *        + 该方法仅在发布端调用 enableSimulcastMode:{@link #ByteRTCVideo#enableSimulcastMode:} 开启了发送多路视频流的情况下生效，此时订阅端将收到来自发布端与期望设置的参数最相近的一路流；否则订阅端只会收到一路参数为分辨率 640px × 360px、帧率 15fps 的视频流。  <br>
 *        + 若发布端开启了推送多路流功能，但订阅端不对流参数进行设置，则默认接受发送端设置的分辨率最大的一路视频流。  <br>
 *        + 该方法需在进房后调用，若想进房前设置，你需调用 joinRoom:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoom:userInfo:roomConfig:}，并对 `roomConfig` 中的 `remoteVideoConfig` 进行设置。  <br>
 *        + SDK 会根据发布端和所有订阅端的设置灵活调整视频流的参数，具体调整策略详见[推送多路流](https://www.volcengine.com/docs/6348/70139)文档。
 */
/**
 * @locale en
 * @type api
 * @region Video Management
 * @brief Sets your expected configuration of the remote video stream that you want to subscribe to or have subscribed to.
 * @param userId ID of the remote video stream publisher you expect to configure subscription parameters for.
 * @param remoteVideoConfig The parameters you expect to configure for the remote video stream, see ByteRTCRemoteVideoConfig{@link #ByteRTCRemoteVideoConfig}.
 * @return API call result: <br>
 *        + 0: Success <br>
 *        + !0: Failure
 * @note 
 *        + This API only works after the publisher calls enableSimulcastMode:{@link #ByteRTCVideo#enableSimulcastMode:} to enable publishing multiple video streams, in which case the subscriber will receive the stream from the publisher that is closest to the set configuration;  otherwise the subscriber will only receive one video stream with a resolution of 640px × 360px and a frame rate of 15fps.  <br>
 *        + If you don't call this API after the publisher enables the function of publishing multiple streams, you will receive by default the video stream with the largest resolution set by the publisher.  <br>
 *        + You should call this API in the room. If you want to call it before entering the room, you should set the `remoteVideoConfig` in the `roomConfig ` when calling joinRoom:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoom:userInfo:roomConfig:}.  <br>
 *        + SDK will automatically select the stream to be published or subcribed based on the settings of both sides. See [Simulcasting](https://docs.byteplus.com/byteplus-rtc/docs/70139) for more details.
 */
- (int) setRemoteVideoConfig:(NSString * _Nonnull) userId remoteVideoConfig:(ByteRTCRemoteVideoConfig *_Nonnull) remoteVideoConfig;
/**
 * @locale zh
 * @type api
 * @region 房间管理
 * @brief 在当前所在房间内发布本地通过摄像头/麦克风采集的媒体流
 * @param type 媒体流类型，用于指定发布音频/视频，参看 ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note 
 *        + 如果你已经在用户进房时通过调用 joinRoom:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoom:userInfo:roomConfig:} 成功选择了自动发布，则无需再调用本接口。<br>
 *        + 调用 setUserVisibility:{@link #ByteRTCRoom#setUserVisibility:} 方法将自身设置为不可见后无法调用该方法，需将自身切换至可见后方可调用该方法发布摄像头音视频流。 <br>
 *        + 如果你需要发布屏幕共享流，调用 publishScreen:{@link #ByteRTCRoom#publishScreen:}。<br>
 *        + 如果你需要向多个房间发布流，调用 startForwardStreamToRooms:{@link #ByteRTCRoom#startForwardStreamToRooms:}。  <br>
 *        + 调用此方法后，房间中的所有远端用户会收到 rtcRoom:onUserPublishStream:type:{@link #ByteRTCRoomDelegate#rtcRoom:onUserPublishStream:type:} 回调通知，其中成功收到了音频流的远端用户会收到 rtcEngine:onFirstRemoteAudioFrame:{@link #ByteRTCVideoDelegate#rtcEngine:onFirstRemoteAudioFrame:} 回调，订阅了视频流的远端用户会收到 rtcEngine:onFirstRemoteVideoFrameDecoded:withFrameInfo:{@link #ByteRTCVideoDelegate#rtcEngine:onFirstRemoteVideoFrameDecoded:withFrameInfo:} 回调。<br>
 *        + 调用 unpublishStream:{@link #ByteRTCRoom#unpublishStream:} 取消发布。
 */
/**
 * @locale en
 * @type api
 * @region Room Management
 * @brief Publishes media streams captured by camera/microphone in the current room.
 * @param type Media stream type, used for specifying whether to publish audio stream or video stream. See ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note  
 *        + You don't need to call this API if you set it to Auto-publish when calling joinRoom:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoom:userInfo:roomConfig:}.   <br>
 *        + An invisible user cannot publish media streams. Call setUserVisibility:{@link #ByteRTCRoom#setUserVisibility:} to change your visibility in the room.  <br>
 *        + Call publishScreen:{@link #ByteRTCRoom#publishScreen:} to start screen sharing.  <br>
 *        + Call startForwardStreamToRooms:{@link #ByteRTCRoom#startForwardStreamToRooms:} to forward the published streams to the other rooms.  <br>
 *        + After you call this API, the other users in the room will receive rtcRoom:onUserPublishStream:type:{@link #ByteRTCRoomDelegate#rtcRoom:onUserPublishStream:type:}. Those who successfully received your streams will receive rtcEngine:onFirstRemoteAudioFrame:{@link #ByteRTCVideoDelegate#rtcEngine:onFirstRemoteAudioFrame:}/rtcEngine:onFirstRemoteVideoFrameDecoded:withFrameInfo:{@link #ByteRTCVideoDelegate#rtcEngine:onFirstRemoteVideoFrameDecoded:withFrameInfo:} at the same time.  <br>
 *        + Call unpublishStream:{@link #ByteRTCRoom#unpublishStream:} to stop publishing streams.
 */
- (int)publishStream:(ByteRTCMediaStreamType)type;
/**
 * @locale zh
 * @type api
 * @region 房间管理
 * @brief 停止将本地摄像头/麦克风采集的媒体流发布到当前所在房间中
 * @param type 媒体流类型，用于指定停止发布音频/视频，参看 ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note  
 *        + 调用 publishStream:{@link #ByteRTCRoom#publishStream:} 手动发布摄像头音视频流后，你需调用此接口停止发布。<br>
 *        + 调用此方法停止发布音视频流后，房间中的其他用户将会收到 rtcRoom:onUserUnpublishStream:type:reason: {@link #ByteRTCRoomDelegate#rtcRoom:onUserUnpublishStream:type:reason:} 回调通知。
 */
/**
 * @locale en
 * @type api
 * @region Room Management
 * @brief Stops publishing media streams captured by camera/microphone in the current room.
 * @param type Media stream type, used for specifying whether to stop publishing audio stream or video stream. See ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note  
 *         + After calling publishStream:{@link #ByteRTCRoom#publishStream:}, call this API to stop publishing streams. <br>
 *         + After calling this API, the other users in the room will receive rtcRoom:onUserUnpublishStream:type:reason: {@link #ByteRTCRoomDelegate#rtcRoom:onUserUnpublishStream:type:reason:}.
 */
- (int)unpublishStream:(ByteRTCMediaStreamType)type;
/**
 * @locale zh
 * @type api
 * @region 屏幕共享
 * @brief 在当前所在房间内发布本地屏幕共享音视频流
 * @param type 媒体流类型，用于指定发布屏幕音频/视频，参看 ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note 
 *        + 如果你已经在用户进房时通过调用 joinRoom:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoom:userInfo:roomConfig:} 成功选择了自动发布，则无需再调用本接口。<br>
 *        + 调用 setUserVisibility:{@link #ByteRTCRoom#setUserVisibility:} 方法将自身设置为不可见后无法调用该方法，需将自身切换至可见后方可调用该方法发布屏幕流。 <br>
 *        + 调用该方法后，房间中的所有远端用户会收到 rtcRoom:onUserPublishScreen:type:{@link #ByteRTCRoomDelegate#rtcRoom:onUserPublishScreen:type:} 回调，其中成功收到音频流的远端用户会收到 rtcEngine:onFirstRemoteAudioFrame:{@link #ByteRTCVideoDelegate#rtcEngine:onFirstRemoteAudioFrame:} 回调，订阅了视频流的远端用户会收到 rtcEngine:onFirstRemoteVideoFrameDecoded:withFrameInfo:{@link #ByteRTCVideoDelegate#rtcEngine:onFirstRemoteVideoFrameDecoded:withFrameInfo:} 回调。<br>
 *        + 调用该方法后，本地用户会收到 rtcEngine:onScreenVideoFrameSendStateChanged:rtcUser:state:{@link #ByteRTCVideoDelegate#rtcEngine:onScreenVideoFrameSendStateChanged:rtcUser:state:}。<br>
 *        + 如果你需要向多个房间发布流，调用 startForwardStreamToRooms:{@link #ByteRTCRoom#startForwardStreamToRooms:}。  <br>
 *        + 调用 unpublishScreen:{@link #ByteRTCRoom#unpublishScreen:} 取消发布。<br>
 *        + 查看 [屏幕共享](https://www.volcengine.com/docs/6348/80225)，获取更多信息。
 */
/**
 * @locale en
 * @type api
 * @region Screen Sharing
 * @brief Publishes local screen sharing streams in the current room.
 * @param type Media stream type, used for specifying whether to publish audio stream or video stream. See ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note  
 *        + You need to call this API to publish screen even if you have selected Auto-publish when calling joinRoom:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoom:userInfo:roomConfig:}.   <br>
 *        + An invisible user cannot publish media streams. Call setUserVisibility:{@link #ByteRTCRoom#setUserVisibility:} to change your visibility in the room. <br>
 *        + After you called this API, the other users in the room will receive rtcRoom:onUserPublishScreen:type:{@link #ByteRTCRoomDelegate#rtcRoom:onUserPublishScreen:type:}. Those who successfully received your streams will receive rtcEngine:onFirstRemoteAudioFrame:{@link #ByteRTCVideoDelegate#rtcEngine:onFirstRemoteAudioFrame:}/rtcEngine:onFirstRemoteVideoFrameDecoded:withFrameInfo:{@link #ByteRTCVideoDelegate#rtcEngine:onFirstRemoteVideoFrameDecoded:withFrameInfo:} at the same time.  <br>
 *        + After calling this API, you'll receive rtcEngine:onScreenVideoFrameSendStateChanged:rtcUser:state:{@link #ByteRTCVideoDelegate#rtcEngine:onScreenVideoFrameSendStateChanged:rtcUser:state:}. <br>
 *        + Call startForwardStreamToRooms:{@link #ByteRTCRoom#startForwardStreamToRooms:} to forward the published streams to the other rooms.  <br>
 *        + Call unpublishScreen:{@link #ByteRTCRoom#unpublishScreen:} to stop publishing screen sharing streams.<br>
 *        + Refer to [Sharing Screen in iOS](https://docs.byteplus.com/byteplus-rtc/docs/124177) and [Sharing Screen in Mac](https://docs.byteplus.com/byteplus-rtc/docs/70144)for more information.
 */
- (int)publishScreen:(ByteRTCMediaStreamType)type;
/**
 * @locale zh
 * @type api
 * @region 屏幕共享
 * @brief 停止将本地屏幕共享音视频流发布到当前所在房间中
 * @param type 媒体流类型，用于指定停止发布屏幕音频/视频，参看 ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note 
 *        + 调用 publishScreen:{@link #ByteRTCRoom#publishScreen:} 发布屏幕流后，你需调用此接口停止发布。 <br>
 *        + 调用此方法停止发布屏幕音视频流后，房间中的其他用户将会收到 rtcRoom:onUserUnpublishScreen:type:reason:{@link #ByteRTCRoomDelegate#rtcRoom:onUserUnpublishScreen:type:reason:} 回调。
 */
/**
 * @locale en
 * @type api
 * @region Screen Sharing
 * @brief Stops publishing local screen sharing streams in the current room.
 * @param type Media stream type, used for specifying whether to stop publishing audio stream or video stream. See ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note  
 *         + After calling publishScreen:{@link #ByteRTCRoom#publishScreen:}, call this API to stop publishing streams. <br>
 *         + After calling this API, the other users in the room will receive rtcRoom:onUserUnpublishScreen:type:reason:{@link #ByteRTCRoomDelegate#rtcRoom:onUserUnpublishScreen:type:reason:}.
 */
- (int)unpublishScreen:(ByteRTCMediaStreamType)type;

/**
 * @locale zh
 * @deprecated since 3.36 and will be deleted in 3.51, use subscribeStream:mediaStreamType:{@link #ByteRTCRoom#subscribeStream:mediaStreamType:}, unsubscribeStream:mediaStreamType:{@link #ByteRTCRoom#unsubscribeStream:mediaStreamType:}, subscribeScreen:mediaStreamType:{@link #ByteRTCRoom#subscribeScreen:mediaStreamType:} and unsubscribeScreen:mediaStreamType:{@link #ByteRTCRoom#unsubscribeScreen:mediaStreamType:} instead.
 * @type api
 * @region 多房间
 * @brief 订阅房间内指定的远端音视频流。  <br>
 *        无论是自动订阅还是手动订阅模式，你都可以调用此方法按需订阅房间中的音视频流。  <br>
 *        该方法也可用于更新已经订阅的流的属性、媒体类型等配置。
 * @param userId 指定订阅的远端发布音视频流的用户 ID 。  
 * @param streamType 流属性，用于指定订阅主流/屏幕流，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex} 。  
 * @param mediaType 媒体类型，用于指定订阅音/视频，参看 ByteRTCSubscribeMediaType{@link #ByteRTCSubscribeMediaType}。
 * @param videoConfig 视频订阅配置，参看 ByteRTCSubscribeVideoConfig{@link #ByteRTCSubscribeVideoConfig}。
 * @note 
 *        + 你必须通过 rtcRoom:onStreamAdd:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamAdd:} 和 rtcRoom:onStreamRemove:stream:reason:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamRemove:stream:reason:} 两个回调获取当前房间里的音视频流信息，并调用本方法按需订阅流或修改订阅配置。  <br>
 *        + 若订阅失败，你会收到 rtcEngine:onError:{@link #ByteRTCVideoDelegate#rtcEngine:onError:} 回调通知，具体失败原因参看 ByteRTCErrorCode{@link #ByteRTCErrorCode}。<br>
 *        + 若调用 pauseAllSubscribedStream:{@link #ByteRTCRoom#pauseAllSubscribedStream:} 暂停接收远端音视频流，此时仍可使用该方法对暂停接收的流进行设置，你会在调用 resumeAllSubscribedStream:{@link #ByteRTCRoom#resumeAllSubscribedStream:} 恢复接收流后收到修改设置后的流。  
 */
/**
 * @locale en
 * @deprecated since 3.45 and will be deleted in 3.51, use subscribeStream:mediaStreamType:{@link #ByteRTCRoom#subscribeStream:mediaStreamType:}, unsubscribeStream:mediaStreamType:{@link #ByteRTCRoom#unsubscribeStream:mediaStreamType:}, subscribeScreen:mediaStreamType:{@link #ByteRTCRoom#subscribeScreen:mediaStreamType:} and unsubscribeScreen:mediaStreamType:{@link #ByteRTCRoom#unsubscribeScreen:mediaStreamType:} instead.
 * @type api
 * @region Multi-room
 * @brief Subscribe to media streams in the room.   <br>
 *        Call this API to subscribe to media streams in the room regardless of subscription mode, either Auto or Manual. <br>
 *        Call this API to update the properties and configurations of the stream you have already subscribed to. 
 * @param userId User ID of the publisher of the subscribed media stream 
 * @param streamType Mainstream or screen-sharing stream. Refer to  ByteRTCStreamIndex{@link #ByteRTCStreamIndex} for details. 
 * @param mediaType Media stream type to be subscribed to. Refer to ByteRTCSubscribeMediaType{@link #ByteRTCSubscribeMediaType} for details. 
 * @param videoConfig Subscription configuration of video streams. Refer to ByteRTCSubscribeVideoConfig{@link #ByteRTCSubscribeVideoConfig} for details. 
 * @note  
 *         + Get the media stream information in the room from  rtcRoom:onStreamAdd:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamAdd:} and rtcRoom:onStreamRemove:stream:reason:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamRemove:stream:reason:}. <br>
 *         + If the subscription fails, you will receive rtcEngine:onError:{@link #ByteRTCVideoDelegate#rtcEngine:onError:}. Refer to  ByteRTCErrorCode{@link #ByteRTCErrorCode} for the specific reason of the failure.<br>
 *         + You can update the subscription configuration by calling the API even after calling pauseAllSubscribedStream:{@link #ByteRTCRoom#pauseAllSubscribedStream:} to pause  streaming. Call  resumeAllSubscribedStream:{@link #ByteRTCRoom#resumeAllSubscribedStream:} to resume streaming and apply the changes. 
 */
- (int)subscribeUserStream:(NSString *_Nonnull)userId streamType:(ByteRTCStreamIndex)streamType mediaType:(ByteRTCSubscribeMediaType)mediaType videoConfig:(ByteRTCSubscribeVideoConfig *_Nonnull)videoConfig __deprecated_msg("Will be removed in new version");
/**
 * @locale zh
 * @type api
 * @region 房间管理
 * @brief 订阅房间内指定的通过摄像头/麦克风采集的媒体流，或更新对指定远端用户的订阅选项
 * @param userId 指定订阅的远端发布音视频流的用户 ID。
 * @param mediaStreamType 媒体流类型，用于指定订阅音频/视频。参看 ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}。
 * @return 方法调用结果：<br>
 *        + 0：成功；<br>
 *        + <0：失败。具体失败原因参看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus}。
 * @note  
 *        + 若当前用户在调用本接口时已经订阅该远端用户（手动订阅或自动订阅），则将根据本次传入的参数，更新订阅配置。<br>
 *        + 你必须先通过 rtcRoom:onUserPublishStream:type:{@link #ByteRTCRoomDelegate#rtcRoom:onUserPublishStream:type:} 回调获取当前房间里的远端摄像头音视频流信息，然后调用本方法按需订阅。  <br>
 *        + 调用该方法后，你会收到 rtcRoom:onStreamSubscribed:userId:subscribeConfig:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamSubscribed:userId:subscribeConfig:} 通知方法调用结果。  <br>
 *        + 成功订阅远端用户的媒体流后，订阅关系将持续到调用 unsubscribeStream:mediaStreamType:{@link #ByteRTCRoom#unsubscribeStream:mediaStreamType:} 取消订阅或本端用户退房。 <br>
 *        + 关于其他调用异常，你会收到 rtcRoom:onStreamStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamStateChanged:withUid:state:extraInfo:} 回调通知，具体异常原因参看 ByteRTCErrorCode{@link #ByteRTCErrorCode}。
 */
/**
 * @locale en
 * @type api
 * @region Room Management
 * @brief Subscribes to specific remote media streams captured by camera/microphone, or update subscription options.
 * @param userId The ID of the remote user who published the target audio/video stream.
 * @param mediaStreamType Media stream type, used for specifying whether to subscribe to the audio stream or the video stream. See ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}.
 * @return API call result:<br>
 *        + 0: Success.<br>
 *        + <0: Failure. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for specific reasons.
 * @note  
 *        + This method can be used to subscribe to a remote user for the first time, or to update the media stream type of an already subscribed remote user. <br>
 *        + You must first get the remote stream information through rtcRoom:onUserPublishStream:type:{@link #ByteRTCRoomDelegate#rtcRoom:onUserPublishStream:type:} before calling this API to subscribe to streams as needed.  <br>
 *        + After calling this API, you will be informed of the calling result with rtcRoom:onStreamSubscribed:userId:subscribeConfig:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamSubscribed:userId:subscribeConfig:}.  <br>
 *        + Once the local user subscribes to the stream of a remote user, the subscription to the remote user will sustain until the local user leaves the room or unsubscribe from it by calling unsubscribeStream:mediaStreamType:{@link #ByteRTCRoom#unsubscribeStream:mediaStreamType:}.<br>
 *        + Any other exceptions will be included in rtcRoom:onStreamStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamStateChanged:withUid:state:extraInfo:}, see ByteRTCErrorCode{@link #ByteRTCErrorCode} for the reasons.
 */
- (int)subscribeStream:(NSString *_Nonnull)userId mediaStreamType:(ByteRTCMediaStreamType)mediaStreamType;
/**
 * @locale zh
 * @type api
 * @region 房间管理
 * @brief 订阅房间内所有通过摄像头/麦克风采集的媒体流，或更新订阅选项。
 * @param mediaStreamType 媒体流类型，用于指定订阅音频/视频。参看 ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}。
 * @return  
 *        0: 方法调用成功  <br>
 *        !0: 方法调用失败  
 * @note  
 *        + 多次调用订阅接口时，将根据末次调用接口和传入的参数，更新订阅配置。<br>
 *        + 开启音频选路后，如果房间内的媒体流超过上限，建议通过调用 subscribeStream:mediaStreamType:{@link #ByteRTCRoom#subscribeStream:mediaStreamType:} 逐一指定需要订阅的媒体流。<br>
 *        + 调用该方法后，你会收到 rtcRoom:onStreamSubscribed:userId:subscribeConfig:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamSubscribed:userId:subscribeConfig:} 通知方法调用结果。  <br>
 *        + 成功调用本接口后，订阅关系将持续到调用 unsubscribeStream:mediaStreamType:{@link #ByteRTCRoom#unsubscribeStream:mediaStreamType:} 或 unsubscribeAllStreamsWithMediaStreamType:{@link #ByteRTCRoom#unsubscribeAllStreamsWithMediaStreamType:} 取消订阅或本端用户退房。 <br>
 *        + 关于其他调用异常，你会收到 rtcRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onRoomStateChanged:withUid:state:extraInfo:} 回调通知，具体异常原因参看 ByteRTCErrorCode{@link #ByteRTCErrorCode}。
 */
/**
 * @locale en
 * @type api
 * @region Room Management
 * @brief Subscribes to all remote media streams captured by camera/microphone. Or update the subscribe options of all subscribed user.
 * @param mediaStreamType Media stream type, used for specifying whether to subscribe to the audio stream or the video stream. See ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}.
 * @return API call result:  <br>
 *        + 0: Success  <br>
 *        + !0: Failure
 * @note  
 *        + If the subscription options conflict with the previous ones, they are subject to the configurations in the last call.<br>
 *        + In the Audio selection, if the number of media streams exceeds the limit, we recommend you call subscribeStream:mediaStreamType:{@link #ByteRTCRoom#subscribeStream:mediaStreamType:} to subscribe each target media stream other than calling this API.<br>
 *        + After calling this API, you will be informed of the calling result with rtcRoom:onStreamSubscribed:userId:subscribeConfig:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamSubscribed:userId:subscribeConfig:}.  <br>
 *        + Once the local user subscribes to the stream of a remote user, the subscription to the remote user will sustain until the local user leaves the room or unsubscribe from it by calling unsubscribeStream:mediaStreamType:{@link #ByteRTCRoom#unsubscribeStream:mediaStreamType:} or unsubscribeAllStreamsWithMediaStreamType:{@link #ByteRTCRoom#unsubscribeAllStreamsWithMediaStreamType:}.<br>
 *        + Any other exceptions will be included in rtcRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onRoomStateChanged:withUid:state:extraInfo:}, see ByteRTCErrorCode{@link #ByteRTCErrorCode} for the reasons.
 */
- (int)subscribeAllStreamsWithMediaStreamType:(ByteRTCMediaStreamType)mediaStreamType;

/**
 * @locale zh
 * @type api
 * @region 房间管理
 * @brief 取消订阅房间内指定的通过摄像头/麦克风采集的媒体流。  <br>
 *        该方法对自动订阅和手动订阅模式均适用。
 * @param userId 指定取消订阅的远端发布音视频流的用户 ID。
 * @param mediaStreamType 媒体流类型，用于指定取消订阅音频/视频。参看 ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}。
 * @return 方法调用结果： <br>
 *        + 0：成功；<br>
 *        + !0：失败。
 * @note  
 *        + 调用该方法后，你会收到 rtcRoom:onStreamSubscribed:userId:subscribeConfig:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamSubscribed:userId:subscribeConfig:} 通知方法调用结果。  <br>
 *        + 关于其他调用异常，你会收到 rtcRoom:onStreamStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamStateChanged:withUid:state:extraInfo:} 回调通知，具体失败原因参看 ByteRTCErrorCode{@link #ByteRTCErrorCode}。
 */
/**
 * @locale en
 * @type api
 * @region Room Management
 * @brief Unsubscribes from specific remote media streams captured by camera/microphone.  <br>
 *        You can call this API in both automatic subscription mode and manual subscription mode.
 * @param userId ID of the remote user of which you have subscribed to the stream.
 * @param mediaStreamType Media stream type, used for specifying whether to unsubscribe from the audio stream or the video stream. See ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}.
 * @return API call result: <br>
 *        + 0: Success <br>
 *        + !0: Failure
 * @note  
 *        + After calling this API, you will be informed of the calling result with rtcRoom:onStreamSubscribed:userId:subscribeConfig:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamSubscribed:userId:subscribeConfig:}.  <br>
 *        + Any other exceptions will be included in rtcRoom:onStreamStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamStateChanged:withUid:state:extraInfo:}, see ByteRTCErrorCode{@link #ByteRTCErrorCode} for the reasons.
 */
- (int)unsubscribeStream:(NSString *_Nonnull)userId mediaStreamType:(ByteRTCMediaStreamType)mediaStreamType;
/**
 * @locale zh
 * @type api
 * @region 房间管理
 * @brief 取消订阅房间内所有的通过摄像头/麦克风采集的媒体流。  <br>
 *        自动订阅和手动订阅的流都可以通过本方法取消订阅。
 * @param mediaStreamType 媒体流类型，用于指定取消订阅音频/视频。参看 ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}。
 * @return 方法调用结果：  <br>
 *        + 0：成功  <br>
 *        + !0：失败
 * @note  
 *        + 调用该方法后，你会收到 rtcRoom:onStreamSubscribed:userId:subscribeConfig:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamSubscribed:userId:subscribeConfig:} 通知方法调用结果。  <br>
 *        + 关于其他调用异常，你会收到 rtcRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onRoomStateChanged:withUid:state:extraInfo:} 回调通知，具体失败原因参看 ByteRTCErrorCode{@link #ByteRTCErrorCode}。
 */
/**
 * @locale en
 * @type api
 * @region Room Management
 * @brief Unsubscribes from all remote media streams captured by camera/microphone.  <br>
 *        You can call this API to unsubscribe from streams that are subscribed to either automatically or manually.
 * @param mediaStreamType Media stream type, used for specifying whether to unsubscribe from the audio stream or the video stream. See ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}.
 * @return API call result:  <br>
 *        + 0: Success  <br>
 *        + !0: Failure
 * @note  
 *        + After calling this API, you will be informed of the calling result with rtcRoom:onStreamSubscribed:userId:subscribeConfig:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamSubscribed:userId:subscribeConfig:}.  <br>
 *        + Any other exceptions will be included in rtcRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onRoomStateChanged:withUid:state:extraInfo:}, see ByteRTCErrorCode{@link #ByteRTCErrorCode} for the reasons.
 */
- (int)unsubscribeAllStreamsWithMediaStreamType:(ByteRTCMediaStreamType)mediaStreamType;
/**
 * @locale zh
 * @type api
 * @region 房间管理
 * @brief 订阅房间内指定的远端屏幕共享音视频流，或更新对指定远端用户的订阅选项
 * @param userId 指定订阅的远端发布屏幕流的用户 ID。
 * @param mediaStreamType 媒体流类型，用于指定订阅音频/视频。参看 ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}。
 * @return 方法调用结果：<br>
 *        + 0：成功；<br>
 *        + <0：失败。具体失败原因参看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus}。
 * @note  
 *        + 若当前用户在调用本接口时已经订阅该远端用户（手动订阅或自动订阅），则将根据本次传入的参数，更新订阅配置。<br>
 *        + 你必须先通过 rtcRoom:onUserPublishScreen:type:{@link #ByteRTCRoomDelegate#rtcRoom:onUserPublishScreen:type:} 回调获取当前房间里的远端屏幕流信息，然后调用本方法按需订阅。  <br>
 *        + 调用该方法后，你会收到 rtcRoom:onStreamSubscribed:userId:subscribeConfig:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamSubscribed:userId:subscribeConfig:} 通知方法调用结果。  <br>
 *        + 成功订阅远端用户的媒体流后，订阅关系将持续到调用 unsubscribeScreen:mediaStreamType:{@link #ByteRTCRoom#unsubscribeScreen:mediaStreamType:} 取消订阅或本端用户退房。 <br>
 *        + 关于其他调用异常，你会收到 rtcRoom:onStreamStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamStateChanged:withUid:state:extraInfo:} 回调通知，具体异常原因参看 ByteRTCErrorCode{@link #ByteRTCErrorCode}。
 */
/**
 * @locale en
 * @type api
 * @region Room Management
 * @brief Subscribes to specific screen sharing media stream, or update subscription options.
 * @param userId The ID of the remote user who published the target screen audio/video stream.
 * @param mediaStreamType Media stream type, used for specifying whether to subscribe to the audio stream or the video stream. See ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}.
 * @return API call result:<br>
 *        + 0: Success.<br>
 *        + <0: Failure. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for specific reasons.
 * @note  
 *        + Calling this API to update the subscribe configuration when the user has subscribed the remote user either by calling this API or by auto-subscribe.  <br>
 *        + You must first get the remote stream information through rtcRoom:onUserPublishScreen:type:{@link #ByteRTCRoomDelegate#rtcRoom:onUserPublishScreen:type:} before calling this API to subscribe to streams accordingly.  <br>
 *        + After calling this API, you will be informed of the calling result with rtcRoom:onStreamSubscribed:userId:subscribeConfig:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamSubscribed:userId:subscribeConfig:}.  <br>
 *        + Once the local user subscribes to the stream of a remote user, the subscription to the remote user will sustain until the local user leaves the room or unsubscribe from it by calling unsubscribeScreen:mediaStreamType:{@link #ByteRTCRoom#unsubscribeScreen:mediaStreamType:}.<br>
 *        + Any other exceptions will be included in rtcRoom:onStreamStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamStateChanged:withUid:state:extraInfo:}, see ByteRTCErrorCode{@link #ByteRTCErrorCode} for the reasons.
 */
- (int)subscribeScreen:(NSString *_Nonnull)userId mediaStreamType:(ByteRTCMediaStreamType)mediaStreamType;
/**
 * @locale zh
 * @type api
 * @region 房间管理
 * @brief 取消订阅房间内指定的远端屏幕共享音视频流。  <br>
 *        该方法对自动订阅和手动订阅模式均适用。
 * @param userId 指定取消订阅的远端发布屏幕流的用户 ID。
 * @param mediaStreamType 媒体流类型，用于指定取消订阅音频/视频。参看 ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}。
 * @return 方法调用结果： <br>
 *        + 0：成功；<br>
 *        + !0：失败。
 * @note  
 *        + 调用该方法后，你会收到 rtcRoom:onStreamSubscribed:userId:subscribeConfig:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamSubscribed:userId:subscribeConfig:} 通知方法调用结果。  <br>
 *        + 关于其他调用异常，你会收到 rtcRoom:onStreamStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamStateChanged:withUid:state:extraInfo:} 回调通知，具体失败原因参看 ByteRTCErrorCode{@link #ByteRTCErrorCode}。
 */
/**
 * @locale en
 * @type api
 * @region Room Management
 * @brief Unsubscribes from specific screen sharing media stream.  <br>
 *        You can call this API in both automatic subscription mode and manual subscription mode.
 * @param userId ID of the remote user of which you have subscribed to the stream.
 * @param mediaStreamType Media stream type, used for specifying whether to unsubscribe from the audio stream or the video stream. See ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}.
 * @return API call result: <br>
 *        + 0: Success <br>
 *        + !0: Failure
 * @note  
 *        + After calling this API, you will be informed of the calling result with rtcRoom:onStreamSubscribed:userId:subscribeConfig:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamSubscribed:userId:subscribeConfig:}.  <br>
 *        + Any other exceptions will be included in rtcRoom:onStreamStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamStateChanged:withUid:state:extraInfo:}, see ByteRTCErrorCode{@link #ByteRTCErrorCode} for the reasons.
 */
- (int)unsubscribeScreen:(NSString *_Nonnull)userId mediaStreamType:(ByteRTCMediaStreamType)mediaStreamType;

/**
 * @locale zh
 * @type api
 * @region 多房间
 * @brief 暂停接收来自远端的媒体流
 * @param mediaType 媒体流类型，指定需要暂停接收音频还是视频流，参看 ByteRTCPauseResumControlMediaType{@link #ByteRTCPauseResumControlMediaType}
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note 
 *        + 该方法仅暂停远端流的接收，并不影响远端流的采集和发送；  <br>
 *        + 该方法不改变用户的订阅状态以及订阅流的属性。  <br>
 *        + 若想恢复接收远端流，需调用 resumeAllSubscribedStream:{@link #ByteRTCRoom#resumeAllSubscribedStream:}。 <br>
 *        + 多房间场景下，仅暂停接收发布在当前所在房间的流。
 */
/**
 * @locale en
 * @type api
 * @region Multi-room
 * @brief Pauses receiving remote media streams.
 * @param mediaType Media stream type subscribed to. Refer to ByteRTCPauseResumControlMediaType{@link #ByteRTCPauseResumControlMediaType} for more details.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note  
 *         + Calling this API does not change the capture and transmission state of the remote stream.<br>
 *         + Calling this API does not cancel the subscription or change any subscription configuration. <br>
 *         + To resume receiving streams,  call resumeAllSubscribedStream:{@link #ByteRTCRoom#resumeAllSubscribedStream:}. <br>
 *         + In a multi-room scenario, this API only pauses the reception of streams published in the current room.
 */
- (int)pauseAllSubscribedStream:(ByteRTCPauseResumControlMediaType) mediaType;

/**
 * @locale zh
 * @type api
 * @region 多房间
 * @brief 恢复接收来自远端的媒体流
 * @param mediaType 媒体流类型，指定需要暂停接收音频还是视频流，参看 ByteRTCPauseResumControlMediaType{@link #ByteRTCPauseResumControlMediaType}
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note 
 *        + 该方法仅恢复远端流的接收，并不影响远端流的采集和发送；  <br>
 *        + 该方法不改变用户的订阅状态以及订阅流的属性。
 */
/**
 * @locale en
 * @type api
 * @region Multi-room
 * @brief Resumes receiving remote media streams.
 * @param mediaType Media stream type subscribed to. Refer to ByteRTCPauseResumControlMediaType{@link #ByteRTCPauseResumControlMediaType} for more details.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note  
 *         + Calling this API does not change the capture and transmission state of the remote stream.<br>
 *         + Calling this API does not change any subscription configuration.
 */
- (int)resumeAllSubscribedStream:(ByteRTCPauseResumControlMediaType) mediaType;
 /**
  * @locale zh
  * @type api
  * @region 多房间
  * @brief 给房间内指定的用户发送点对点文本消息（P2P）。
  * @param userId  <br>
  *        消息接收用户的 ID
  * @param message  <br>
  *        发送的文本消息内容。  <br>
  *        消息不超过 64 KB。
  * @param config   <br>
  *        消息发送的可靠/有序类型，参看 ByteRTCMessageConfig{@link #ByteRTCMessageConfig}  
  * @return 这次发送消息的编号，从 1 开始递增。
  * @note  
  *      + 在发送房间内文本消息前，必须先调用 joinRoom:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoom:userInfo:roomConfig:} 加入房间。  <br>
  *      + 调用该函数后会收到一次 rtcRoom:onUserMessageSendResult:error:{@link #ByteRTCRoomDelegate#rtcRoom:onUserMessageSendResult:error:} 回调，通知消息发送方发送成功或失败。  <br>
  *      + 若文本消息发送成功，则 uid 所指定的用户会收到 rtcRoom:onUserMessageReceived:message:{@link #ByteRTCRoomDelegate#rtcRoom:onUserMessageReceived:message:} 回调。
  */
 /**
  * @locale en
  * @type api
  * @region Multi-room
  * @brief Sends a text message (P2P) to the specified user in the room.
  * @param userId ID of the user receiving the message
  * @param message Message content of which the length must not exceed 64 KB.
  * @param config Reliability of the message.
  * @return The number of the message sent this time is incremented from 1.
  * @note  
  *       + Before sending an in-room text message, you must call joinRoom:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoom:userInfo:roomConfig:} to join the room. <br>
  *       + After calling this API, you will receive an rtcRoom:onUserMessageSendResult:error:{@link #ByteRTCRoomDelegate#rtcRoom:onUserMessageSendResult:error:} callback to notify the sender of the success or failure of the message. <br>
  *       + If the text message is sent successfully, the user specified by uid will receive an rtcRoom:onUserMessageReceived:message:{@link #ByteRTCRoomDelegate#rtcRoom:onUserMessageReceived:message:} callback.
  */
- (NSInteger)sendUserMessage:(NSString *_Nonnull)userId message:(NSString *_Nonnull)message config:(ByteRTCMessageConfig)config;

 /**
  * @locale zh
  * @type api
  * @region 多房间
  * @brief 给房间内指定的用户发送点对点二进制消息（P2P）。
  * @param uid  <br>
  *        消息接收用户的 ID
  * @param message  <br>
  *        发送的二进制消息内容  <br>
  *        消息不超过 46KB。
  * @param config   <br>
  *        消息发送的可靠/有序类型，参看 ByteRTCMessageConfig{@link #ByteRTCMessageConfig}。  
  * @return 这次发送消息的编号，从 1 开始递增。
  * @note  
  *      + 在发送房间内二进制消息前，必须先调用 joinRoom:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoom:userInfo:roomConfig:} 加入房间。  <br>
  *      + 调用该函数后会收到一次 rtcRoom:onUserMessageSendResult:error:{@link #ByteRTCRoomDelegate#rtcRoom:onUserMessageSendResult:error:} 回调，通知消息发送方发送成功或失败；  <br>
  *      + 若二进制消息发送成功，则 uid 所指定的用户会收到 rtcRoom:onUserBinaryMessageReceived:message:{@link #ByteRTCRoomDelegate#rtcRoom:onUserBinaryMessageReceived:message:} 回调。
  */
 /**
  * @locale en
  * @type The api
  * @region multiroom
  * @brief Sends a binary message (P2P) to the specified user in the room.
  * @param uid   <br>
  *        Message Receiving user's ID
  * @param message   <br>
  *        Binary message content sent <br>
  *        Message does not exceed 46KB.
  * @param config See ByteRTCMessageConfig{@link #ByteRTCMessageConfig}.
  * @return The number of the message sent this time is incremented from 1.
  * @note   
  *       + Before sending the in-room binary message, you must call joinRoom:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoom:userInfo:roomConfig:} to join the room. <br>
  *       + After calling this function, you will receive an rtcRoom:onUserMessageSendResult:error:{@link #ByteRTCRoomDelegate#rtcRoom:onUserMessageSendResult:error:} callback to notify the sender of the success or failure of the message; <br>
  *       + If the binary message is sent successfully, the user specified by uid will receive rtcRoom:onUserBinaryMessageReceived:message:{@link #ByteRTCRoomDelegate#rtcRoom:onUserBinaryMessageReceived:message:} callback.
  */
- (NSInteger)sendUserBinaryMessage:(NSString * _Nonnull)uid message:(NSData * _Nonnull)message config:(ByteRTCMessageConfig)config;

 /**
  * @locale zh
  * @type api
  * @region 多房间
  * @brief 给房间内的所有其他用户群发文本消息。
  * @param message  <br>
  *        发送的文本消息内容。  <br>
  *        消息不超过 64 KB。
  * @return 这次发送消息的编号，从 1 开始递增。
  * @note  
  *      + 在发送房间内文本消息前，必须先调用 joinRoom:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoom:userInfo:roomConfig:} 加入房间。  <br>
  *      + 调用该函数后会收到一次 rtcRoom:onRoomMessageSendResult:error:{@link #ByteRTCRoomDelegate#rtcRoom:onRoomMessageSendResult:error:} 回调，通知消息发送方发送成功或失败；  <br>
  *      + 若文本消息发送成功，则房间内所有远端用户会收到 rtcRoom:onRoomMessageReceived:message:{@link #ByteRTCRoomDelegate#rtcRoom:onRoomMessageReceived:message:} 回调。
  */
 /**
  * @locale en
  * @type api
  * @region Multi-room
  * @brief Sends text messages to all other users in the room.
  * @param message   <br>
  *        The content of the text message sent. <br>
  *         Message does not exceed 64 KB.
  * @return The number of the message sent this time is incremented from 1.
  * @note   
  *       + Before sending an in-room text message, you must call joinRoom:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoom:userInfo:roomConfig:} to join the room. <br>
  *       + After calling this function, you will receive an rtcRoom:onRoomMessageSendResult:error:{@link #ByteRTCRoomDelegate#rtcRoom:onRoomMessageSendResult:error:} callback to notify the sender of the success or failure of the message; <br>
  *       + If the text message is sent successfully, all remote users in the room will receive rtcRoom:onRoomMessageReceived:message:{@link #ByteRTCRoomDelegate#rtcRoom:onRoomMessageReceived:message:} callback.
  */
- (NSInteger)sendRoomMessage:(NSString *_Nonnull)message NS_SWIFT_NAME(sendRoomMessage(_:));

 /**
  * @locale zh
  * @type api
  * @region 多房间
  * @brief 给房间内的所有其他用户群发二进制消息。
  * @param message  <br>
  *        用户发送的二进制广播消息  <br>
  *        消息不超过 46KB。
  * @return 这次发送消息的编号，从 1 开始递增。
  * @note  
  *      + 在房间内广播二进制消息前，必须先调用 joinRoom:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoom:userInfo:roomConfig:} 加入房间。  <br>
  *      + 调用该函数后会收到一次 rtcRoom:onRoomMessageSendResult:error:{@link #ByteRTCRoomDelegate#rtcRoom:onRoomMessageSendResult:error:} 回调，通知消息发送方发送成功或失败；  <br>
  *      + 若二进制消息发送成功，则房间内所有用户会收到 rtcRoom:onRoomBinaryMessageReceived:message:{@link #ByteRTCRoomDelegate#rtcRoom:onRoomBinaryMessageReceived:message:} 回调。
  */
 /**
  * @locale en
  * @type api
  * @region multiroom
  * @brief Sends binary messages to all other users in the room.
  * @param message   <br>
  *        The binary broadcast message sent by the user <br>
  *        The message does not exceed 46KB.
  * @return The number of the message sent this time is incremented from 1.
  * @note   
  *       + Before broadcasting binary messages in the room, you must call joinRoom:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoom:userInfo:roomConfig:} to join the room. <br>
  *       + After calling this function, you will receive an rtcRoom:onRoomMessageSendResult:error:{@link #ByteRTCRoomDelegate#rtcRoom:onRoomMessageSendResult:error:} callback to notify the sender of the success or failure of the message; <br>
  *       + If the binary message is successfully sent, all users in the room will receive rtcRoom:onRoomBinaryMessageReceived:message:{@link #ByteRTCRoomDelegate#rtcRoom:onRoomBinaryMessageReceived:message:} callback.
  */
- (NSInteger)sendRoomBinaryMessage:(NSData *  _Nonnull)message NS_SWIFT_NAME(sendRoomBinaryMessage(_:));

#pragma mark ForwardStream
    /**
     * @locale zh
     * @type api
     * @region 多房间
     * @brief 开始跨房间转发媒体流。<br>
     *        在调用 joinRoom:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoom:userInfo:roomConfig:} 后调用本接口，实现向多个房间转发媒体流，适用于跨房间连麦等场景。
     * @param configurations 跨房间媒体流转发指定房间的信息。参看 ByteRTCForwardStreamConfiguration{@link #ByteRTCForwardStreamConfiguration}。
     * @return  
     *        0: 方法调用成功<br>
     *        <0: 方法调用失败  
     * @note 
     *        + 调用本方法后，将在本端触发 rtcRoom:onForwardStreamStateChanged:{@link #ByteRTCRoomDelegate#rtcRoom:onForwardStreamStateChanged:} 回调。<br>
     *        + 调用本方法后，你可以通过监听 rtcRoom:onForwardStreamEvent:{@link #ByteRTCRoomDelegate#rtcRoom:onForwardStreamEvent:} 回调来获取各个目标房间在转发媒体流过程中的相关事件。<br>
     *        + 开始转发后，目标房间中的用户将接收到本地用户进房 rtcRoom:onUserJoined:elapsed:{@link #ByteRTCRoomDelegate#rtcRoom:onUserJoined:elapsed:} 和发流 rtcRoom:onUserPublishStream:type:{@link #ByteRTCRoomDelegate#rtcRoom:onUserPublishStream:type:}/rtcRoom:onUserPublishScreen:type:{@link #ByteRTCRoomDelegate#rtcRoom:onUserPublishScreen:type:} 的回调。<br>
     *        + 调用本方法后，可以调用 updateForwardStreamToRooms:{@link #ByteRTCRoom#updateForwardStreamToRooms:} 更新目标房间信息，例如，增加或减少目标房间等。<br>
     *        + 调用本方法后，可以调用 stopForwardStreamToRooms{@link #ByteRTCRoom#stopForwardStreamToRooms} 停止向所有房间转发媒体流。<br>
     *        + 调用本方法后，可以调用 pauseForwardStreamToAllRooms{@link #ByteRTCRoom#pauseForwardStreamToAllRooms} 暂停向所有房间转发媒体流。
     */
    /**
     * @locale en
     * @type api
     * @region Multi-room
     * @brief Starts relaying media stream across rooms. <br>
     *        After calling joinRoom:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoom:userInfo:roomConfig:}, call this API to achieve the relaying of media streams to multiple rooms, which applies to cross-room concatenation and other scenarios.
     * @param configurations Information of the rooms where you want to relay the media stream to. Refer to ByteRTCForwardStreamConfiguration{@link #ByteRTCForwardStreamConfiguration} for more inforamtion.
     * @return  
     *        0: Success<br>
     *        <0: Failure  
     * @note 
     *        + Calling this method will trigger rtcRoom:onForwardStreamStateChanged:{@link #ByteRTCRoomDelegate#rtcRoom:onForwardStreamStateChanged:}.<br>
     *        + After calling this method, listen the events from each room during the relaying by registering rtcRoom:onForwardStreamEvent:{@link #ByteRTCRoomDelegate#rtcRoom:onForwardStreamEvent:}.<br>
     *        + Once the relaying begins, the other users in the room will receive callback of rtcRoom:onUserJoined:elapsed:{@link #ByteRTCRoomDelegate#rtcRoom:onUserJoined:elapsed:} and rtcRoom:onUserPublishStream:type:{@link #ByteRTCRoomDelegate#rtcRoom:onUserPublishStream:type:}/rtcRoom:onUserPublishScreen:type:{@link #ByteRTCRoomDelegate#rtcRoom:onUserPublishScreen:type:}.<br>
     *        + Call updateForwardStreamToRooms:{@link #ByteRTCRoom#updateForwardStreamToRooms:} to add or remove the designated room(s) after calling this method.<br>
     *        + Call stopForwardStreamToRooms{@link #ByteRTCRoom#stopForwardStreamToRooms} to stop relaying to all rooms after calling this method.<br>
     *        + Call pauseForwardStreamToAllRooms{@link #ByteRTCRoom#pauseForwardStreamToAllRooms} to pause relaying to all rooms after calling this method.
     */
- (int)startForwardStreamToRooms:(NSArray <ByteRTCForwardStreamConfiguration *> * _Nullable)configurations NS_SWIFT_NAME(startForwardStreamToRooms(_:));
    /**
     * @locale zh
     * @type api
     * @region 多房间
     * @brief 更新跨房间媒体流转发信息。<br>
     *        通过 startForwardStreamToRooms:{@link #ByteRTCRoom#startForwardStreamToRooms:} 发起媒体流转发后，可调用本方法增加或者减少目标房间，或更新房间密钥。<br>
     *        调用本方法增加或删减房间后，将在本端触发 rtcRoom:onForwardStreamStateChanged:{@link #ByteRTCRoomDelegate#rtcRoom:onForwardStreamStateChanged:} 回调，包含发生了变动的目标房间中媒体流转发状态。
     * @param configurations 跨房间媒体流转发目标房间信息。参看 ByteRTCForwardStreamConfiguration{@link #ByteRTCForwardStreamConfiguration}。
     * @return  
     *        + 0: 方法调用成功  
     * @note 
     *        + 增加目标房间后，新增目标房间中的用户将接收到本地用户进房 rtcRoom:onUserJoined:elapsed:{@link #ByteRTCRoomDelegate#rtcRoom:onUserJoined:elapsed:} 和发布 rtcRoom:onUserJoined:elapsed:{@link #ByteRTCRoomDelegate#rtcRoom:onUserJoined:elapsed:} 的回调。<br>
     *        + 删减目标房间后，原目标房间中的用户将接收到本地用户停止发布 rtcRoom:onUserUnpublishStream:type:reason: {@link #ByteRTCRoomDelegate#rtcRoom:onUserUnpublishStream:type:reason:} 和退房 rtcRoom:onUserLeave:reason:{@link #ByteRTCRoomDelegate#rtcRoom:onUserLeave:reason:} 的回调。
     */
    /**
     * @locale en
     * @type api
     * @region Multi-room
     * @brief Updates information of the rooms where you want to relay the media stream to after calling startForwardStreamToRooms:{@link #ByteRTCRoom#startForwardStreamToRooms:}. <br>
     *        Adding and removing rooms by calling this method will trigger rtcRoom:onForwardStreamStateChanged:{@link #ByteRTCRoomDelegate#rtcRoom:onForwardStreamStateChanged:} on the local.
     * @param configurations Information of the rooms where you want to relay the media stream to. Refer to ByteRTCForwardStreamConfiguration{@link #ByteRTCForwardStreamConfiguration} for more information.
     * @return  
     *         + 0: Success  <br>
     *         + <0: Failure
     * @note 
     *        + Users in the room which is added by calling this method will receive rtcRoom:onUserJoined:elapsed:{@link #ByteRTCRoomDelegate#rtcRoom:onUserJoined:elapsed:} and rtcRoom:onUserJoined:elapsed:{@link #ByteRTCRoomDelegate#rtcRoom:onUserJoined:elapsed:}.<br>
     *        + Users in the room which is removed by calling this method will receive rtcRoom:onUserUnpublishStream:type:reason: {@link #ByteRTCRoomDelegate#rtcRoom:onUserUnpublishStream:type:reason:} and rtcRoom:onUserLeave:reason:{@link #ByteRTCRoomDelegate#rtcRoom:onUserLeave:reason:}.
     */
- (int)updateForwardStreamToRooms:(NSArray <ByteRTCForwardStreamConfiguration *> * _Nullable)configurations NS_SWIFT_NAME(updateForwardStreamToRooms(_:));
/**
 * @locale zh
 * @type api
 * @region 多房间
 * @brief 停止跨房间媒体流转发。<br>
 *        通过 startForwardStreamToRooms:{@link #ByteRTCRoom#startForwardStreamToRooms:} 发起媒体流转发后，可调用本方法停止向所有目标房间转发媒体流。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note 
 *        + 调用本方法后，将在本端触发 rtcRoom:onForwardStreamStateChanged:{@link #ByteRTCRoomDelegate#rtcRoom:onForwardStreamStateChanged:} 回调。<br>
 *        + 调用本方法后，原目标房间中的用户将接收到本地用户停止发布 rtcRoom:onUserUnpublishStream:type:reason: {@link #ByteRTCRoomDelegate#rtcRoom:onUserUnpublishStream:type:reason:} 和退房 rtcRoom:onUserLeave:reason:{@link #ByteRTCRoomDelegate#rtcRoom:onUserLeave:reason:} 的回调。<br>
 *        + 如果需要更改目标房间，请调用 updateForwardStreamToRooms:{@link #ByteRTCRoom#updateForwardStreamToRooms:} 更新房间信息。<br>
 *        + 如果需要暂停转发，请调用 pauseForwardStreamToAllRooms{@link #ByteRTCRoom#pauseForwardStreamToAllRooms}，并在之后随时调用 resumeForwardStreamToAllRooms{@link #ByteRTCRoom#resumeForwardStreamToAllRooms} 快速恢复转发。
 */
/**
 * @locale en
 * @type api
 * @region Multi-room
 * @brief Stops relaying media stream to all rooms after calling startForwardStreamToRooms{@link #ByteRTCRoom#startForwardStreamToRooms:}. 
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note 
 *        + Calling this method will trigger rtcRoom:onForwardStreamStateChanged:{@link #ByteRTCRoomDelegate#rtcRoom:onForwardStreamStateChanged:}.<br>
 *        + The other users in the room will receive callback of rtcRoom:onUserJoined:elapsed:{@link #ByteRTCRoomDelegate#rtcRoom:onUserJoined:elapsed:} and rtcRoom:onUserJoined:elapsed:{@link #ByteRTCRoomDelegate#rtcRoom:onUserJoined:elapsed:} when you stop relaying.<br>
 *        + To stop relaying media stream to specific rooms, call updateForwardStreamToRooms:{@link #ByteRTCRoom#updateForwardStreamToRooms:} instead.<br>
 *        + To pause the relaying for a short time, call pauseForwardStreamToAllRooms{@link #ByteRTCRoom#pauseForwardStreamToAllRooms}, and then call resumeForwardStreamToAllRooms{@link #ByteRTCRoom#resumeForwardStreamToAllRooms} to recsume after that.
 */
- (int)stopForwardStreamToRooms;
/**
 * @locale zh
 * @type api
 * @region 多房间
 * @brief 暂停跨房间媒体流转发。<br>
 *        通过 startForwardStreamToRooms:{@link #ByteRTCRoom#startForwardStreamToRooms:} 发起媒体流转发后，可调用本方法暂停向所有目标房间转发媒体流。<br>
 *        调用本方法暂停向所有目标房间转发后，你可以随时调用 resumeForwardStreamToAllRooms{@link #ByteRTCRoom#resumeForwardStreamToAllRooms} 快速恢复转发。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note 调用本方法后，目标房间中的用户将接收到本地用户停止发布 rtcRoom:onUserUnpublishStream:type:reason: {@link #ByteRTCRoomDelegate#rtcRoom:onUserUnpublishStream:type:reason:} 和退房 rtcRoom:onUserLeave:reason:{@link #ByteRTCRoomDelegate#rtcRoom:onUserLeave:reason:} 的回调。
 */
  /**
 * @locale en
 * @type api
 * @region Multi-room
 * @brief Pauses relaying media stream to all rooms after calling startForwardStreamToRooms{@link #ByteRTCRoom#startForwardStreamToRooms:}. <br>
 *        After that, call resumeForwardStreamToAllRooms{@link #ByteRTCRoom#resumeForwardStreamToAllRooms} to resume.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note The other users in the room will receive callback of rtcRoom:onUserUnpublishStream:type:reason: {@link #ByteRTCRoomDelegate#rtcRoom:onUserUnpublishStream:type:reason:} and rtcRoom:onUserLeave:reason:{@link #ByteRTCRoomDelegate#rtcRoom:onUserLeave:reason:} when you pause relaying.
 */
- (int)pauseForwardStreamToAllRooms;
/**
 * @locale zh
 * @type api
 * @region 多房间
 * @brief 恢复跨房间媒体流转发。<br>
 *        调用 pauseForwardStreamToAllRooms{@link #ByteRTCRoom#pauseForwardStreamToAllRooms} 暂停转发之后，调用本方法恢复向所有目标房间转发媒体流。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note 
 *        目标房间中的用户将接收到本地用户进房 rtcRoom:onUserJoined:elapsed:{@link #ByteRTCRoomDelegate#rtcRoom:onUserJoined:elapsed:} 和发布 rtcRoom:onUserJoined:elapsed:{@link #ByteRTCRoomDelegate#rtcRoom:onUserJoined:elapsed:} 的回调。
 */
/**
 * @locale en
 * @type api
 * @region Multi-room
 * @brief Resumes relaying media streams paused by calling pauseForwardStreamToAllRooms{@link #ByteRTCRoom#pauseForwardStreamToAllRooms} to all rooms.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note The other users in the room will receive callback of rtcRoom:onUserJoined:elapsed:{@link #ByteRTCRoomDelegate#rtcRoom:onUserJoined:elapsed:} and rtcRoom:onUserJoined:elapsed:{@link #ByteRTCRoomDelegate#rtcRoom:onUserJoined:elapsed:} when you resume relaying.
 */
- (int)resumeForwardStreamToAllRooms;


/**
 * @locale zh
 * @type api
 * @region 范围语音
 * @brief 获取范围语音接口实例。
 * @return 方法调用结果： <br>
 *        + ByteRTCRangeAudio：成功，返回一个 ByteRTCRangeAudio{@link #ByteRTCRangeAudio} 实例。  <br>
 *        + NULL：失败，当前 SDK 不支持范围语音功能。
 * @note 首次调用该方法须在创建房间后、加入房间前。范围语音相关 API 和调用时序详见[范围语音](https://www.volcengine.com/docs/6348/114727)。
 */
/**
 * @locale en
 * @type api
 * @region Range Audio
 * @brief Gets range audio instance.
 * @return API call result:  <br>
 *        + ByteRTCRangeAudio: Success. You will get a ByteRTCRangeAudio{@link #ByteRTCRangeAudio} returned from the SDK.  <br>
 *        + NULL: Failure. The current SDK does not offer range audio function.
 * @note The first time this API is called must be between creating a room and actually entering the room.  Refer to [Range Voice](https://docs.byteplus.com/byteplus-rtc/docs/114727) for more information.
 */
- (ByteRTCRangeAudio *_Nullable)getRangeAudio;

/**
 * @locale zh
 * @type api
 * @region 空间音频
 * @brief 获取空间音频接口实例。
 * @return 方法调用结果：  <br>
 *        + ByteRTCSpatialAudio：成功，返回一个 ByteRTCSpatialAudio{@link #ByteRTCSpatialAudio} 实例。  <br>
 *        + NULL：失败，当前 SDK 不支持空间音频功能。
 * @note  
 *        + 首次调用该方法须在创建房间后、加入房间前。 空间音频相关 API 和调用时序详见[空间音频](https://www.volcengine.com/docs/6348/93903)。 <br>
 *        + 只有在使用支持真双声道播放的设备时，才能开启空间音频效果；  <br>
 *        + 机型性能不足可能会导致音频卡顿，使用低端机时，不建议开启空间音频效果；  <br>
 *        + SDK 最多支持 30 个用户同时开启空间音频功能。
 */
/**
 * @locale en
 * @type api
 * @region Spatial Audio
 * @brief Gets spatial audio instance.   
 * @return API call result:  <br>
 *        + ISpatialAudio: Success. You will get a ByteRTCSpatialAudio{@link #ByteRTCSpatialAudio} returned from the SDK.  <br>
 *        + NULL: Failure. The current SDK does not offer spatial audio function.
 * @note   
 *        + The first time this API is called must be between you create a room and you actually enter the room.  Refer to [Spatial Audio](https://docs.byteplus.com/byteplus-rtc/docs/93903) for more information.<br>
 *        + Only using real dual-channel playback device can users actually enjoy spatial audio effect.  <br>
 *        + Low-end device may have audio stalling issues due to its poor performance, so it is not recommended to enable spatial audio function on such kind of devices. <br>
 *        + SDK currently supports up to 30 users publishing audio with spatial audio enabled at the same time in the same room.
 */
- (ByteRTCSpatialAudio *_Nullable)getSpatialAudio;
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
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note 假设某远端用户 A 始终在被调节的目标用户范围内，<br>
 *        + 当该方法与 setRemoteAudioPlaybackVolume:remoteUid:playVolume:{@link #ByteRTCVideo#setRemoteAudioPlaybackVolume:remoteUid:playVolume:} 共同使用时，本地收听用户 A 的音量为后调用的方法设置的音量；<br>
 *        + 当该方法与 setPlaybackVolume:{@link #ByteRTCVideo#setPlaybackVolume:} 方法共同使用时，本地收听用户 A 的音量将为两次设置的音量效果的叠加。
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
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note Suppose a remote user A is always within the range of the target user whose playback volume will be adjusted,<br>
 *        + If you use both this method and setRemoteAudioPlaybackVolume:remoteUid:playVolume:{@link #ByteRTCVideo#setRemoteAudioPlaybackVolume:remoteUid:playVolume:}, the volume that the local user hears from user A is the volume set by the method called later.<br>
 *        + If you use both this method and setPlaybackVolume:{@link #ByteRTCVideo#setPlaybackVolume:}, the volume that the local user hears from user A is the overlay of both settings.
 */
- (int)setRemoteRoomAudioPlaybackVolume:(NSInteger)volume;

/**
 * @locale zh
 * @hidden for internal use only.
 * @type api
 * @region 云端渲染
 * @brief 按照传入的布局信息开启云端渲染。
 * @param rendingInfo 渲染功能相关参数。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 */
/**
 * @locale en
 * @hidden for internal use only.
 * @type api
 * @region Cloud Rendering
 * @brief Enable cloud rendering according to the incoming layout information.
 * @param rendingInfo  Rendering function related, parameters.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 */
- (int)startCloudRendering:(NSString *_Nonnull)rendingInfo;

/**
 * @locale zh
 * @hidden for internal use only.
 * @type api
 * @region 云端渲染
 * @brief 按照传入的布局信息更新云端渲染。
 * @param rendingInfo 渲染功能相关参数。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 */
/**
 * @locale en
 * @hidden for internal use only.
 * @type api
 * @region Cloud Render
 * @brief Update the cloud rendering with the layout information passed in.
 * @param rendingInfo  Rendering function related, parameters.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 */
- (int)updateCloudRendering:(NSString *_Nonnull)rendingInfo;

/**
 * @locale zh
 * @hidden for internal use only.
 * @type api
 * @region 云端渲染
 * @brief 停止云端渲染。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 */
/**
 * @locale en
 * @hidden for internal use only.
 * @type api
 * @region  cloud rendering
 * @brief  Stop cloud rendering.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 */
- (int)stopCloudRendering;

/**
 * @locale zh
 * @valid since 3.52.
 * @type api
 * @region 房间管理
 * @brief 设置本端发布流在音频选路中的优先级。
 * @param audioSelectionPriority 本端发布流在音频选路中的优先级，默认正常参与音频选路。参见 ByteRTCAudioSelectionPriority{@link #ByteRTCAudioSelectionPriority}。 
 * @note 
 * 在控制台上为本 appId 开启音频选路后，调用本接口才会生效。进房前后调用均可生效。更多信息参见[音频选路](https://www.volcengine.com/docs/6348/113547)。<br>
 * 如果本端用户同时加入不同房间，使用本接口进行的设置相互独立。<br>
 * 
 */
/**
 * @locale en
 * @valid since 3.52.
 * @type api
 * @region Room Management
 * @brief Set the priority of the local audio stream to be published.
 * @param audioSelectionPriority The priority of the local audio stream which defaults to be subscribable only up to the result of the Audio Selection. Refer to ByteRTCAudioSelectionPriority{@link #ByteRTCAudioSelectionPriority}.
 * @note 
 * You must enable Audio Selection in the RTC console before using this API. You can call this API whether the user has joined a room. Refer to [Audio Selection](https://docs.byteplus.com/byteplus-rtc/docs/113547).<br>
 * The setting is independent in each room that the user joins.
 */
- (int)setAudioSelectionConfig:(ByteRTCAudioSelectionPriority)audioSelectionPriority;

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
 *        + <0: 方法调用失败，具体原因详见 ByteRTCSetRoomExtraInfoResult{@link #ByteRTCSetRoomExtraInfoResult}。  
 * @note  
 *       + 在设置房间附加信息前，必须先调用 joinRoom:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoom:userInfo:roomConfig:} 加入房间。  <br>
 *       + 调用该方法后，会收到一次 rtcRoom:onSetRoomExtraInfoResult:error:{@link #ByteRTCRoomDelegate#rtcRoom:onSetRoomExtraInfoResult:error:} 回调，提示设置结果。  <br>
 *       + 调用该方法成功设置附加信息后，同一房间内的其他用户会收到关于该信息的回调 rtcRoom:onRoomExtraInfoUpdate:value:lastUpdateUserId:lastUpdateTimeMs:{@link #ByteRTCRoomDelegate#rtcRoom:onRoomExtraInfoUpdate:value:lastUpdateUserId:lastUpdateTimeMs:}。<br>
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
 *        + <0: Failure. See ByteRTCSetRoomExtraInfoResult{@link #ByteRTCSetRoomExtraInfoResult} for the reasons.
 * @note  
 *        + Call joinRoom:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoom:userInfo:roomConfig:} first before you call this API to set extra information. <br>
 *        + After calling this API, you will receive rtcRoom:onSetRoomExtraInfoResult:error:{@link #ByteRTCRoomDelegate#rtcRoom:onSetRoomExtraInfoResult:error:} callback informing you the result of the setting. <br>
 *        + After the extra information is successfully set, other users in the same room will receive the information through rtcRoom:onRoomExtraInfoUpdate:value:lastUpdateUserId:lastUpdateTimeMs:{@link #ByteRTCRoomDelegate#rtcRoom:onRoomExtraInfoUpdate:value:lastUpdateUserId:lastUpdateTimeMs:} callback.<br>
 *        + Users who join the room later will be notified of all extra information in the room set prior to entering.
 */
- (NSInteger)setRoomExtraInfo:(NSString *_Nonnull)key value:(NSString *_Nonnull)value;


/**
 * @locale zh
 * @valid since 3.52
 * @type api
 * @region 字幕翻译服务
 * @brief 识别或翻译房间内所有用户的语音，形成字幕。<br>
 *        调用该方法时，可以在 ByteRTCSubtitleMode{@link #ByteRTCSubtitleMode} 中选择语音识别或翻译模式。如果选择识别模式，语音识别文本会通过 rtcRoom:onSubtitleMessageReceived:{@link #ByteRTCRoomDelegate#rtcRoom:onSubtitleMessageReceived:} 事件回调给你；<br>
 *        如果选择翻译模式，你会同时收到两个 rtcRoom:onSubtitleMessageReceived:{@link #ByteRTCRoomDelegate#rtcRoom:onSubtitleMessageReceived:} 回调，分别包含字幕原文及字幕译文。<br>
 *        调用该方法后，用户会收到 rtcRoom:onSubtitleStateChanged:errorCode:errorMessage:{@link #ByteRTCRoomDelegate#rtcRoom:onSubtitleStateChanged:errorCode:errorMessage:} 回调，通知字幕是否开启。
 * @param subtitleConfig 字幕配置信息。参看 ByteRTCSubtitleConfig{@link #ByteRTCSubtitleConfig}。
 * @return  
 *        +  0: 调用成功。  <br>
 *        + !0: 调用失败。 
 * @note 
 *        + 使用字幕功能前，你需要在 [RTC 控制台](https://console.volcengine.com/rtc/cloudRTC?tab=subtitle) 开启实时字幕功能。<br>
 *        + 如果你需要使用流式语音识别模式，你应在 [语音技术控制台](https://console.volcengine.com/speech/service/16) 创建流式语音识别应用。创建时，服务类型应选择 `流式语音识别`，而非 `音视频字幕生成`。创建后，在 [RTC 控制台](https://console.volcengine.com/rtc/cloudRTC?tab=subtitle) 上启动流式语音识别，并填写创建语音技术应用时获取的相关信息，包括：APP ID，Access Token，和 Cluster ID。<br>
 *        + 如果你需要使用实时语音翻译模式，你应开通机器翻译服务，参考 [开通服务](https://www.volcengine.com/docs/4640/130262)。完成开通后，在 [RTC 控制台](https://console.volcengine.com/rtc/cloudRTC?tab=subtitle) 上启用实时语音翻译模式。<br> *        + 此方法需要在进房后调用。  <br>
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
 *        When calling this method, you can choose the subtitle mode in the ByteRTCSubtitleMode{@link #ByteRTCSubtitleMode}. If you choose the recognition mode, you will receive the rtcRoom:onSubtitleMessageReceived:{@link #ByteRTCRoomDelegate#rtcRoom:onSubtitleMessageReceived:} callback which contains the transcribed text. <br>
 *        If you choose the translation mode, you will receive two rtcRoom:onSubtitleMessageReceived:{@link #ByteRTCRoomDelegate#rtcRoom:onSubtitleMessageReceived:} callbacks simultaneously, one contains the transcribed text and the other contains the translated text. <br>
 *        After calling this method, you will receive the rtcRoom:onSubtitleStateChanged:errorCode:errorMessage:{@link #ByteRTCRoomDelegate#rtcRoom:onSubtitleStateChanged:errorCode:errorMessage:} to inform you of whether subtitles are on. 
 * @param subtitleConfig Subtitle configurations. Refer to ByteRTCSubtitleConfig{@link #ByteRTCSubtitleConfig} for details. 
 * @return  
 *        +  0: Success.  <br>
 *        + !0: Failure.  
 * @note 
 *        + Call this method after joining the room.  <br>
 *        + You can set your source language to Chinese by calling `joinRoom` and importing a json formatted string `"source_language": "zh"` through the parameter of extraInfo, to English by importing `"source_language": "en"` , and to Japanese by importing `"source_language": "ja"` . If you don't set the source language, SDK will set the language of your system as the source language. If the language of your system is not Chinese, English or Japanese, SDK will set Chinese as the source language.
 */
- (int)startSubtitle:(ByteRTCSubtitleConfig *_Nonnull)subtitleConfig;

/**
 * @locale zh
 * @valid since 3.52
 * @type api
 * @region 字幕翻译服务
 * @brief 关闭字幕。 <br>
 *        调用该方法后，用户会收到 rtcRoom:onSubtitleStateChanged:errorCode:errorMessage:{@link #ByteRTCRoomDelegate#rtcRoom:onSubtitleStateChanged:errorCode:errorMessage:}  回调，通知字幕是否关闭。
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
 *        After calling this method, you will receive the rtcRoom:onSubtitleStateChanged:errorCode:errorMessage:{@link #ByteRTCRoomDelegate#rtcRoom:onSubtitleStateChanged:errorCode:errorMessage:} to inform you of whether subtitles are off. 
 * @return  
 *        +  0: Success.  <br>
 *        + !0: Failure.  
 */
- (int)stopSubtitle;
@end
