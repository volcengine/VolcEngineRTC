/*
 * Copyright (c) 2020 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC Room Event Handler Interface
*/

#pragma once

#include "rtc/bytertc_defines.h"

namespace bytertc {
/**
 * @locale zh
 * @type callback
 * @brief 音视频房间事件回调接口<br>
 * 注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。
 */
/**
 * @locale en
 * @type callback
 * @brief  Audio & video room event callback interface<br>
 * Note: Callback functions are thrown synchronously in a non-UI thread within the SDK. Therefore, you must not perform any time-consuming operations or direct UI operations within the callback function, as this may cause the app to crash.
 */
class IRTCRoomEventHandler {
public:

    /**
     * @hidden constructor/destructor
     */
    virtual ~IRTCRoomEventHandler() {
    }

    /**
     * @locale zh
     * @type callback
     * @region 多房间
     * @brief 房间状态改变回调，加入房间、异常退出房间、发生房间相关的警告或错误时会收到此回调。
     * @param room_id 房间 ID。
     * @param uid 用户 ID。
     * @param state 房间状态码。  <br>
     *              + 0: 加入房间成功。  <br>
     *              + !0: 加入房间失败、异常退房、发生房间相关的警告或错误。具体原因参看 ErrorCode{@link #ErrorCode} 及 WarningCode{@link #WarningCode}。
     * @param extra_info 额外信息，如 `{"elapsed":1187,"join_type":0}`。<br>
     *                  `join_type`表示加入房间的类型，`0`为首次进房，`1`为重连进房。<br>
     *                  `elapsed`表示加入房间耗时，即本地用户从调用 joinRoom{@link #IRTCRoom#joinRoom} 到加入房间成功所经历的时间间隔，单位为 ms。
     */
    /**
     * @locale en
     * @type callback
     * @region Multi-room
     * @brief Callback on room state changes. Via this callback you get notified of room relating warnings,  errors and events. For example, the user joins the room, the user is removed from the room, and so on.
     * @param room_id  Room ID.
     * @param uid  User ID.
     * @param state Room state code. <br>
     *              + 0: Join room success. <br>
     *              + !0: Failed to join a room, abnormal exit, room-related warnings or errors. See ErrorCode{@link #ErrorCode} and WarningCode{@link #WarningCode} for specific indications.
     * @param extra_info Extra information.<br>
     *                 `join_type` indicates the type of room the user joins. `0` means the user joins the room for the first time, and `1` means the user rejoins the room. <br>
     *                 `elapsed` indicates the time interval from calling joinRoom{@link #IRTCRoom#joinRoom} to successfully joining room, in ms.
     */
    virtual void onRoomStateChanged(
            const char* room_id, const char* uid, int state, const char* extra_info) {
        (void)room_id;
        (void)state;
        (void)extra_info;
    }

    /**
     * @locale zh
     * @type callback
     * @region 房间管理
     * @brief 流状态改变回调，发生流相关的警告或错误时会收到此回调。
     * @param room_id 房间 ID。
     * @param uid 用户 ID。
     * @param state 流状态码，参看 ErrorCode{@link #ErrorCode} 及 WarningCode{@link #WarningCode}。
     * @param extra_info 附加信息，目前为空。
     */
    /**
     * @locale en
     * @type callback
     * @region Room management
     * @brief Callback on stream state changes. You will receive this callback when you receive stream relating warnings and errors.
     * @param room_id  Room ID.
     * @param uid  User ID.
     * @param state Room state code. See ErrorCode{@link #ErrorCode} and WarningCode{@link #WarningCode} for specific indications.
     * @param extra_info Extra information. Currently unavailable.
     */
    virtual void onStreamStateChanged(
            const char* room_id, const char* uid, int state, const char* extra_info) {
        (void)room_id;
        (void)uid;
        (void)state;
        (void)extra_info;
    }

    /**
     * @locale zh
     * @type callback
     * @region 房间管理
     * @brief 离开房间成功回调。  <br>
     *        用户调用 leaveRoom{@link #IRTCRoom#leaveRoom} 方法后，SDK 会停止所有的发布订阅流，并在释放所有与通话相关的音视频资源后，通过此回调通知用户离开房间成功。  
     * @param stats 保留参数，目前为空。
     * @note  
     *       + 用户调用 leaveRoom{@link #IRTCRoom#leaveRoom} 方法离开房间后，如果立即调用 destroy{@link #IRTCRoom#destroy} 销毁房间实例或 destroyRTCVideo{@link #destroyRTCVideo} 方法销毁 RTC 引擎，则将无法收到此回调事件。  <br>
     *       + 离开房间后，如果 App 需要使用系统音视频设备，则建议收到此回调后再初始化音视频设备，否则可能由于 SDK 占用音视频设备而导致初始化失败。  
     */
     /**
      * @locale en
      * @type callback
      * @region Room management
      * @brief After leaving the room successfully, receives the callback.   <br>
      *        When the user calls the leaveRoom{@link #IRTCRoom#leaveRoom}, the SDK will stop all publishing subscription streams and release all call-related media resources. After that, the user receives this callback . 
      * @param stats Reserved parameter.
      * @note   
      *        + After the user calls the leaveRoom{@link #IRTCRoom#leaveRoom} method to leave the room, if destroy{@link #IRTCRoom#destroy} is called to destroy the room instance or destroyRTCVideo{@link #destroyRTCVideo} method is called to destroy the RTC engine immediately, this callback event will not be received. <br>
      *        + If the app needs to use the system audio & video device after leaving the room, it is recommended to initialize the audio & video device after receiving this callback, otherwise the initialization may fail due to the SDK occupying the audio & video device. 
      */
    virtual void onLeaveRoom(const RtcRoomStats& stats) {
        (void)stats;
    }

    /**
     * @locale zh
     * @deprecated since 3.41 and will be deleted in 3.51, use onRoomStateChanged{@link #IRTCRoomEventHandler#onRoomStateChanged} and onStreamStateChanged{@link #IRTCRoomEventHandler#onStreamStateChanged} instead.
     * @type callback
     * @region 房间管理
     * @brief SDK 发生警告回调。  <br>
     *        SDK 内部遇到可恢复错误时，在尝试自动恢复的同时，会通过此回调通知用户。此回调事件仅用作通知。  
     * @param warn 警告码，参看 WarningCode{@link #WarningCode}。  
     */
    /**
     * @locale en
     * @deprecated since 3.45 and will be deleted in 3.51, use onRoomStateChanged{@link #IRTCRoomEventHandler#onRoomStateChanged} and onStreamStateChanged{@link #IRTCRoomEventHandler#onStreamStateChanged} instead.
     * @type callback
     * @region Room Management
     * @brief SDK Warning callback occurred. When a recoverable error is encountered inside the <br>
     *        SDK, the user is notified via this callback while attempting automatic recovery. This callback event is only used as a notification. 
     * @param warn Code. See WarningCode{@link #WarningCode}. 
     */
    BYTERTC_DEPRECATED virtual void onRoomWarning(int warn) {
        (void)warn;
    }

    /**
     * @locale zh
     * @deprecated since 3.41 and will be deleted in 3.51, use onRoomStateChanged{@link #IRTCRoomEventHandler#onRoomStateChanged} and onStreamStateChanged{@link #IRTCRoomEventHandler#onStreamStateChanged} instead.
     * @type callback
     * @region 房间管理
     * @brief SDK 发生错误回调。  <br>
     *        SDK 内部遇到不可恢复错误时，会通过此回调通知 App，需要 App 根据错误码进行操作或提示用户。  
     * @param err 错误码，参看 ErrorCode{@link #ErrorCode}。  
     */
    /**
     * @locale en
     * @deprecated since 3.45 and will be deleted in 3.51, use onRoomStateChanged{@link #IRTCRoomEventHandler#onRoomStateChanged} and onStreamStateChanged{@link #IRTCRoomEventHandler#onStreamStateChanged} instead.
     * @type callback
     * @region Room management
     * @brief SDK Error callback occurred. <br>
     *        SDK internal encountered an unrecoverable error, will notify the App through this callback, requires the App to operate according to the error code or prompt the user. 
     * @param err Error code. See ErrorCode{@link #ErrorCode}. 
     */
    virtual void onRoomError(int err) {
        (void)err;
    }
    /**
     * @locale zh
     * @type callback
     * @brief Token 进房权限过期前 30 秒将触发该回调。<br>
     *        收到该回调后，你需调用 updateToken{@link #IRTCRoom#updateToken} 更新 Token 进房权限。
     * @note 若未能及时更新 Token 进房权限导致其过期实效： <br>
     *        + 用户此时尝试进房会收到 onRoomStateChanged{@link #IRTCRoomEventHandler#onRoomStateChanged} 回调，提示错误码为 `-1000` Token 过期； <br>
     *        + 用户已在房间内则会被移出房间，本地用户会收到 onRoomStateChanged{@link #IRTCRoomEventHandler#onRoomStateChanged} 回调，提示错误码为 `-1009` Token 过期，同时远端用户会收到 onUserLeave{@link #IRTCRoomEventHandler#onUserLeave} 回调，提示原因为 `2` Token 进房权限过期。
     * @list 引擎管理
     * @order 10
     */
     /**
     * @locale en
     * @type callback
     * @brief Callback triggered 30s before the joining room privilege of the Token expires. <br>
     *        After receiving this callback, you must call updateToken{@link #IRTCRoom#updateToken} to update the joining room privilege Token.
     * @note After a user's joining room privilege expires:<br>
     *        + When attempting to join a room, the user will receive onRoomStateChanged{@link #IRTCRoomEventHandler#onRoomStateChanged} with the error code "-1000" indicating that the Token is invalid.<br>
     *        + If the user is already in the room, he/she will be removed from the room and receive onRoomStateChanged{@link #IRTCRoomEventHandler#onRoomStateChanged} with the error code "-1009" indicating that the Token is expired. Remote users in the room will receive onUserLeave{@link #IRTCRoomEventHandler#onUserLeave} with the reason "2" indicating that the Token is invalid.
     * @list Engine Management
     * @order 10
     */
    virtual void onTokenWillExpire() {

    }
    /**
     * @locale zh
     * @type callback
     * @brief Token 发布权限过期前 30 秒将触发该回调。<br>
     *        收到该回调后，你需调用 updateToken{@link #IRTCRoom#updateToken} 更新 Token 发布权限。
     * @note 若收到该回调后未及时更新 Token，Token 发布权限过期后： <br>
     *        + 此时尝试发布流会收到 onStreamStateChanged{@link #IRTCRoomEventHandler#onStreamStateChanged} 回调，提示错误码为 `-1002` 没有发布权限； <br>
     *        + 已在发布中的流会停止发布，发布端会收到 onStreamStateChanged{@link #IRTCRoomEventHandler#onStreamStateChanged} 回调，提示错误码为 `-1002` 没有发布权限，同时远端用户会收到 onUserUnpublishStream{@link #IRTCRoomEventHandler#onUserUnpublishStream}/onUserUnpublishScreen{@link #IRTCRoomEventHandler#onUserUnpublishScreen} 回调，提示原因为 `6` 发流端发布权限过期。
     * @list 引擎管理
     * @order 15
     */
    /**
     * @locale en
     * @type callback
     * @brief Callback triggered 30s before the publishing privilege of the Token expires. <br>
     *        After receiving this callback, you must call updateToken{@link #IRTCRoom#updateToken} to update the publishing privilege Token.
     * @note After a user's publishing privilege expires:<br>
     *        + When attempting to publish a stream, the user will receive onStreamStateChanged{@link #IRTCRoomEventHandler#onStreamStateChanged} with the error code "-1002" indicating no permission to publish streams.<br>
     *        + The published streams of the user will be removed, and he/she will receive onStreamStateChanged{@link #IRTCRoomEventHandler#onStreamStateChanged} with the error code "-1002" indicating no permission to publish streams. Remote users in the room will receive onUserUnpublishStream{@link #IRTCRoomEventHandler#onUserUnpublishStream}/onUserUnpublishScreen{@link #IRTCRoomEventHandler#onUserUnpublishScreen} with the reason "6" indicating that the publishing privilege of the remote user has expired.
     * @list Engine Management
     * @order 15
     */
    virtual void onPublishPrivilegeTokenWillExpire() {

    }
    /**
     * @locale zh
     * @type callback
     * @brief Token 订阅权限过期前 30 秒将触发该回调。<br>
     *        收到该回调后，你需调用 updateToken{@link #IRTCRoom#updateToken} 更新 Token 订阅权限有效期。
     * @note 若收到该回调后未及时更新 Token，Token 订阅权限过期后，尝试新订阅流会失败，已订阅的流会取消订阅，并且会收到 onStreamStateChanged{@link #IRTCRoomEventHandler#onStreamStateChanged} 回调，提示错误码为 `-1003` 没有订阅权限。
     * @list 引擎管理
     * @order 16
     */
    /**
     * @locale en
     * @type callback
     * @brief Callback triggered 30s before the subscribing privilege of the Token expires. <br>
     *        After receiving this callback, you must call updateToken{@link #IRTCRoom#updateToken} to update the subscribing privilege Token.
     * @note After a user's subscribing privilege expires, the user will fail to subscribe to new streams, or the subscribed streams will be removed, and he/she will receive onStreamStateChanged{@link #IRTCRoomEventHandler#onStreamStateChanged} with error code "-1003" indicating no permission to subscribe to streams.
     * @list Engine Management
     * @order 16
     */
    virtual void onSubscribePrivilegeTokenWillExpire() {

    }

    /**
     * @locale zh
     * @type callback
     * @region 数据统计
     * @brief 房间内通话统计信息回调。  <br>
     *        用户进房开始通话后，每 2s 收到一次本回调。
     * @param stats 当前 RtcEngine 统计数据，详见 RtcRoomStats{@link #RtcRoomStats}
     */
    /**
     * @locale en
     * @type callback
     * @region  data statistics
     * @brief  In-room call statistics callback.    <br>
     *        After the user enters the room and starts the call, he receives this callback every 2s.
     * @param stats Current RtcEngine statistics. See RtcRoomStats{@link #RtcRoomStats}
     */
    virtual void onRoomStats(const RtcRoomStats& stats) {
        (void)stats;
    }
    /**
     * @locale zh
     * @hidden(Linux)
     * @type callback
     * @region 数据统计
     * @brief 本地流数据统计以及网络质量回调。  <br>
     *        本地用户发布流成功后，SDK 会周期性（2s）的通过此回调事件通知用户发布的流在此次统计周期内的质量统计信息。  <br>
     *        统计信息通过 LocalStreamStats{@link #LocalStreamStats} 类型的回调参数传递给用户，其中包括发送音视频比特率、发送帧率、编码帧率，网络质量等。
     * @param stats 当前 RtcEngine 统计数据，详见 LocalStreamStats{@link #LocalStreamStats}。
     */
    /**
     * @locale en
     * @hidden(Linux)
     * @type callback
     * @region Statistics
     * @brief Local stream data statistics and network quality callback.   <br>
     *        After the local user publishes the flow successfully, the SDK will periodically (2s) notify the user through this callback event of the quality statistics of the published flow during this reference period. <br>
     *        Statistics are passed to the user through the callback parameters of the LocalStreamStats{@link #LocalStreamStats} type, including the sent audio & video bit rate, sent frame rate, encoded frame rate, network quality, etc. 
     * @param stats Current RtcEngine statistics. See LocalStreamStats{@link #LocalStreamStats}
     */
    virtual void onLocalStreamStats(const LocalStreamStats& stats) {
        (void)stats;
    }
    /**
     * @locale zh
     * @type callback
     * @region 数据统计
     * @brief 本地订阅的远端音/视频流数据统计以及网络质量回调。  <br>
     *        本地用户订阅流成功后，SDK 会周期性（2s）的通过此回调事件通知用户订阅的流在此次统计周期内的质量统计信息，包括：发送音视频比特率、发送帧率、编码帧率，网络质量等。
     * @param stats 当前 RtcEngine 统计数据，详见 RemoteStreamStats{@link #RemoteStreamStats}
     */
    /**
     * @locale en
     * @type callback
     * @region Statistics
     * @brief Remote audio/video stream statistics and network quality callbacks for local subscriptions.   <br>
     *        After the local user subscribes to the stream successfully, the SDK will periodically (2s) notify the user through this callback event of the quality statistics of the subscribed stream during this reference period, including: sending audio & video bit rate, sending frame rate, encoded frame rate, network quality, etc.
     * @param stats Current RtcEngine statistics. See RemoteStreamStats{@link #RemoteStreamStats}
     */
    virtual void onRemoteStreamStats(const RemoteStreamStats& stats) {
        (void)stats;
    }

    /**
     * @locale zh
     * @type callback
     * @region 房间管理
     * @brief 远端可见用户加入房间，或房内隐身用户切换为可见的回调。<br>
     *        1. 远端用户调用 setUserVisibility{@link #IRTCRoom#setUserVisibility} 方法将自身设为可见后加入房间时，房间内其他用户将收到该事件。  <br>
     *        2. 远端可见用户断网后重新连入房间时，房间内其他用户将收到该事件。  <br>
     *        3. 房间内隐身远端用户调用 setUserVisibility{@link #IRTCRoom#setUserVisibility} 方法切换至可见时，房间内其他用户将收到该事件。  <br>
     *        4. 新进房用户会收到进房前已在房内的可见用户的进房回调通知。  
     * @param user_info 用户信息，详见 UserInfo{@link #UserInfo}  
     * @param elapsed 保留字段，无意义。
     */
     /**
      * @locale en
      * @type callback
      * @region Room management
      * @brief You will receive this callback in following cases: <br>
      *        + The remote user calls setUserVisibility{@link #IRTCRoom#setUserVisibility} turns visible and joins your room. <br>
      *        + The remote visible user is disconnected and then reconnected to your room. <br>
      *        + The invisible remote user in your room calls setUserVisibility{@link #IRTCRoom#setUserVisibility} and turns visible. <br>
      *        + You join the room when there are visible users in the room.
      * @param user_info See UserInfo{@link #UserInfo}. 
      * @param elapsed Reserved parameter.
      */
    virtual void onUserJoined(const UserInfo& user_info, int elapsed) {
        (void)user_info;
        (void)elapsed;
    }

    /**
     * @locale zh
     * @type callback
     * @brief 远端用户离开房间，或切至不可见时，本地用户会收到此事件
     * @param uid 离开房间，或切至不可见的的远端用户 ID。  
     * @param reason 用户离开房间的原因，详见 UserOfflineReason{@link #UserOfflineReason}。 <br>
     *              + 0: 远端用户调用 leaveRoom{@link #IRTCRoom#leaveRoom} 主动退出房间。  <br>
     *              + 1: 远端用户因 Token 过期或网络原因等掉线。 详细信息请参看[连接状态提示](https://www.volcengine.com/docs/6348/95376)<br>
     *              + 2: 远端用户调用 setUserVisibility{@link #IRTCRoom#setUserVisibility} 切换至不可见状态。 <br>
     *              + 3: 服务端调用 OpenAPI 将远端用户踢出房间。
     */
    /**
     * @locale en
     * @type callback
     * @brief This callback is triggered when a remote user is disconnected or turns invisible.
     * @param uid ID of the user who leaves the room, or switches to invisible. 
     * @param reason Reason to leave the room. Refer to UserOfflineReason{@link #UserOfflineReason}.<br>
     *               + 0: The remote client calls leaveRoom{@link #IRTCRoom#leaveRoom} to leave the room. <br>
     *               + 1: The remote client is disconnected because of poor network connection or expired Token. <br>
     *               + 2: The remote client calls setUserVisibility{@link #IRTCRoom#setUserVisibility} to turn invisible. <br>
     *               + 3: The remote user has been removed from the room by the administrator via a OpenAPI call.
     */
    virtual void onUserLeave(const char* uid, UserOfflineReason reason) {
        (void)uid;
        (void)reason;
    }
    /**
     * @locale zh
     * @deprecated since 3.36 and will be deleted in 3.51, use onUserUnpublishStream{@link #IRTCRoomEventHandler#onUserUnpublishStream} and onUserUnpublishScreen{@link #IRTCRoomEventHandler#onUserUnpublishScreen} instead.
     * @type callback
     * @region 房间管理
     * @brief 房间内的远端用户停止发布音视频流时，本地用户会收到此回调。
     * @param stream 流的属性。参看 MediaStreamInfo{@link #MediaStreamInfo} 。
     * @param reason 远端流移除的原因。参看 StreamRemoveReason{@link #StreamRemoveReason} 。
     */
    /**
     * @locale en
     * @deprecated since 3.45 and will be deleted in 3.51, use onUserUnpublishStream{@link #IRTCRoomEventHandler#onUserUnpublishStream} and onUserUnpublishScreen{@link #IRTCRoomEventHandler#onUserUnpublishScreen} instead.
     * @type callback
     * @region Room Management
     * @brief Local users will receive this callback when a remote user in the room stops publishing audio & video streams. Properties of the
     * @param stream Stream. See MediaStreamInfo{@link #MediaStreamInfo}.
     * @param reason The reason for the removal of the remote stream. See StreamRemoveReason{@link #StreamRemoveReason}.
     */
    BYTERTC_DEPRECATED virtual void onStreamRemove(const MediaStreamInfo& stream, StreamRemoveReason reason) {
        (void)stream;
    }

    /**
     * @locale zh
     * @deprecated since 3.36 and will be deleted in 3.51, use onUserPublishStream{@link #IRTCRoomEventHandler#onUserPublishStream} and onUserPublishScreen{@link #IRTCRoomEventHandler#onUserPublishScreen} instead.
     * @type callback
     * @region 房间管理
     * @brief 房间内的用户发布新的音视频流时，房间内的其他用户会收到此回调。包括移除后又重新发布的流。  
     * @param stream 流属性，参看 MediaStreamInfo{@link #MediaStreamInfo} 。  
     */
    /**
     * @locale en
     * @deprecated since 3.45 and will be deleted in 3.51, use onUserPublishStream{@link #IRTCRoomEventHandler#onUserPublishStream} and onUserPublishScreen{@link #IRTCRoomEventHandler#onUserPublishScreen} instead.
     * @type callback
     * @region Room Management
     * @brief When users in the room post a new audio & video stream, other users in the room will receive this callback. Includes streams that are removed and republished.   
     * @param stream Stream properties. See MediaStreamInfo{@link #MediaStreamInfo}. 
     */
    BYTERTC_DEPRECATED virtual void onStreamAdd(const MediaStreamInfo& stream) {
        (void)stream;
    }
    /**
     * @locale zh
     * @type callback
     * @region 房间管理
     * @brief 房间内新增远端摄像头/麦克风采集的媒体流的回调。
     * @param uid 远端流发布用户的用户 ID。
     * @param type 远端媒体流的类型，参看 MediaStreamType{@link #MediaStreamType}。
     * @note 当房间内的远端用户调用 publishStream{@link #IRTCRoom#publishStream} 成功发布由摄像头/麦克风采集的媒体流时，本地用户会收到该回调，此时本地用户可以自行选择是否调用 subscribeStream{@link #IRTCRoom#subscribeStream} 订阅此流。
     */
    /**
     * @locale en
     * @type callback
     * @region Room management
     * @brief Callback on new media streams captured by camera/microphone in the room.
     * @param uid The ID of the remote user who published the stream.
     * @param type Media stream type. See MediaStreamType{@link #MediaStreamType}.
     * @note You will receive this callback after a remote user successfully published media streams captured by camera/microphone in the room with publishStream{@link #IRTCRoom#publishStream}. Then you can choose whether to call subscribeStream{@link #IRTCRoom#subscribeStream} to subscribe to the streams or not.
     */
    virtual void onUserPublishStream(const char* uid, MediaStreamType type) {
        (void)uid;
        (void)type;
    }
    /**
     * @locale zh
     * @type callback
     * @region 房间管理
     * @brief 房间内远端摄像头/麦克风采集的媒体流移除的回调。
     * @param uid 移除的远端流发布用户的用户 ID。  
     * @param type 移除的远端流类型，参看 MediaStreamType{@link #MediaStreamType}。  
     * @param reason 远端流移除的原因，参看 StreamRemoveReason{@link #StreamRemoveReason}。
     * @note 收到该回调通知后，你可以自行选择是否调用 unsubscribeStream{@link #IRTCRoom#unsubscribeStream} 取消订阅此流。
     */
    /**
     * @locale en
     * @type callback
     * @region Room management
     * @brief Callback on removal of remote media stream captured by camera/microphone.
     * @param uid The ID of the remote user who removed the stream.
     * @param type Media stream type. See MediaStreamType{@link #MediaStreamType}.
     * @param reason The reason for the removal, see StreamRemoveReason{@link #StreamRemoveReason}.
     * @note After receiving this callback, you can choose whether to call unsubscribeStream{@link #IRTCRoom#unsubscribeStream} to unsubscribe from the streams or not.
     */
    virtual void onUserUnpublishStream(const char* uid, MediaStreamType type,StreamRemoveReason reason) {
        (void)uid;
        (void)type;
        (void)reason;
    }
    /**
     * @locale zh
     * @type callback
     * @region 房间管理
     * @brief 房间内新增远端屏幕共享音视频流的回调。
     * @param uid 远端流发布用户的用户 ID。
     * @param type 远端媒体流的类型，参看 MediaStreamType{@link #MediaStreamType}。
     * @note 当房间内的远端用户调用 publishScreen{@link #IRTCRoom#publishScreen} 成功发布来自屏幕共享的音视频流时，本地用户会收到该回调，此时本地用户可以自行选择是否调用 subscribeScreen{@link #IRTCRoom#subscribeScreen} 订阅此流。（Linux 不支持）
     */
    /**
     * @locale en
     * @type callback
     * @region Room management
     * @brief Callback on new screen sharing media streams from remote users in the room.
     * @param uid The ID of the remote user who published the stream.
     * @param type Media stream type. See MediaStreamType{@link #MediaStreamType}.
     * @note You will receive this callback after a remote user successfully published screen sharing streams in the room with publishScreen{@link #IRTCRoom#publishScreen}. Then you can choose whether to call subscribeScreen{@link #IRTCRoom#subscribeScreen} to subscribe to the streams or not.
     */
    virtual void onUserPublishScreen(const char* uid, MediaStreamType type) {
        (void)uid;
        (void)type;
    }
    /**
     * @locale zh
     * @type callback
     * @region 房间管理
     * @brief 房间内远端屏幕共享音视频流移除的回调。
     * @param uid 移除的远端流发布用户的用户 ID。  
     * @param type 移除的远端流类型，参看 MediaStreamType{@link #MediaStreamType}。  
     * @param reason 远端流移除的原因，参看 StreamRemoveReason{@link #StreamRemoveReason}。
     * @note 收到该回调通知后，你可以自行选择是否调用 unsubscribeScreen{@link #IRTCRoom#unsubscribeScreen} 取消订阅此流。
     */
    /**
     * @locale en
     * @type callback
     * @region Room management
     * @brief Callback on removal of screen sharing media streams from remote users in the room.
     * @param uid The ID of the remote user who removed the stream.
     * @param type Media stream type. See MediaStreamType{@link #MediaStreamType}.
     * @param reason The reason for the removal, see StreamRemoveReason{@link #StreamRemoveReason}.
     * @note After receiving this callback, you can choose whether to call unsubscribeScreen{@link #IRTCRoom#unsubscribeScreen} to unsubscribe from the streams or not.
     */
    virtual void onUserUnpublishScreen(const char* uid, MediaStreamType type,StreamRemoveReason reason) {
        (void)uid;
        (void)type;
        (void)reason;
    }

    /**
     * @locale zh
     * @type callback
     * @region 房间管理
     * @brief 关于订阅媒体流状态改变的回调
     * @param state_code 订阅媒体流状态，参看 SubscribeState{@link #SubscribeState}
     * @param user_id 流发布用户的用户 ID
     * @param info 流的属性，参看 SubscribeConfig{@link #SubscribeConfig}
     * @note 
     *        本地用户收到该回调的时机包括：  <br>
     *        + 调用 subscribeStream{@link #IRTCRoom#subscribeStream} 或 unsubscribeStream{@link #IRTCRoom#unsubscribeStream} 订阅/取消订阅指定远端摄像头音视频流后；  <br>
     *        + 调用 subscribeScreen{@link #IRTCRoom#subscribeScreen} 或 unsubscribeScreen{@link #IRTCRoom#unsubscribeScreen} 订阅/取消订阅指定远端屏幕共享流后。
     */
    /**
     * @locale en
     * @type callback
     * @region Room management
     * @brief Callback on subscription status of media streams
     * @param state_code Subscription status of media streams, see SubscribeState{@link #SubscribeState}.
     * @param user_id The ID of the user who published the stream.
     * @param info Configurations of stream subscription, see SubscribeConfig{@link #SubscribeConfig}.
     * @note  
     *        Local users will receive this callback:  <br>
     *        + After calling subscribeStream{@link #IRTCRoom#subscribeStream}/unsubscribeStream{@link #IRTCRoom#unsubscribeStream} to change the subscription status of remote media streams captured by camera/microphone.  <br>
     *        + After calling subscribeScreen{@link #IRTCRoom#subscribeScreen}/unsubscribeScreen{@link #IRTCRoom#unsubscribeScreen} to change the subscription status of remote screen sharing streams.
     */
    virtual void onStreamSubscribed(SubscribeState state_code, const char* user_id, const SubscribeConfig& info) {
        (void)state_code;
        (void)user_id;
        (void)info;
    }

    /**
     * @locale zh
     * @hidden for internal use only
     * @type callback
     * @region 房间管理
     * @brief 当发布流成功的时候回调该事件。
     * @param user_id 发布流的用户 ID。
     * @param is_screen 该流是否为屏幕流。  <br>
     *             + Ture: 屏幕流；  <br>
     *             + False: 非屏幕流。  
     */
    /**
     * @locale en
     * @hidden for internal use only
     * @type callback
     * @region Room management
     * @brief Callback the event when the release flow is successful.
     * @param user_id The user ID of the published stream.
     * @param is_screen Whether the stream is a screen stream. <br>
     *              + Ture: Screen stream; <br>
     *              + False: Non-screen stream. 
     */
    virtual void onStreamPublishSuccess(const char* user_id, bool is_screen) {
        (void)is_screen;
    }

    /**
     * @locale zh
     * @type callback
     * @region 实时消息通信
     * @brief 接收到房间内广播消息的回调。
     * @param uid  <br>
     *        消息发送者 ID
     * @param message  <br>
     *        收到的消息内容
     * @note 同一房间内其他用户调用 sendRoomMessage{@link #IRTCRoom#sendRoomMessage} 发送广播消息时会收到该回调。
     */
    /**
     * @locale en
     * @type callback
     * @region Real-time messaging
     * @brief Receives a callback for broadcast messages in the room.
     * @param uid <br>
     *         User ID of the message sender
     * @param message <br>
     *         Received message content
     * @note Other users in the same room will receive this callback when they call sendRoomMessage{@link #IRTCRoom#sendRoomMessage} to send a broadcast message.
     */
    virtual void onRoomMessageReceived(const char* uid, const char* message) {
        (void)uid;
        (void)message;
    }

    /**
     * @locale zh
     * @type callback
     * @region 实时消息通信
     * @brief 收到房间内广播二进制消息的回调。<br>
     *        房间内其他用户调用 sendRoomBinaryMessage{@link #IRTCRoom#sendRoomBinaryMessage} 发送广播二进制消息时，收到此回调。
     * @param uid  <br>
     *        消息发送者 ID
     * @param size <br>
     *        收到的二进制消息长度
     * @param message <br>
     *        收到的二进制消息内容
     * @note 同一房间内其他用户调用 sendRoomBinaryMessage{@link #IRTCRoom#sendRoomBinaryMessage} 发送二进制广播消息时会收到该回调。
     */
    /**
     * @locale en
     * @type callback
     * @region Real-time messaging
     * @brief Receives a callback to a binary broadcast message in the room.
     * @param uid <br>
     *         User ID of the message sender
     * @param size <br>
     *         Length of the received binary message
     * @param message <br>
     *        Binary message content received
     * @note Other users in the same room call sendRoomBinaryMessage{@link #IRTCRoom#sendRoomBinaryMessage} Receive this callback when sending a binary broadcast message.
     */
    virtual void onRoomBinaryMessageReceived(const char* uid, int size, const uint8_t* message) {
        (void)uid;
        (void)size;
        (void)message;
    }
    /**
     * @locale zh
     * @type callback
     * @region 实时消息通信
     * @brief 收到来自房间中其他用户通过 sendUserMessage{@link #IRTCRoom#sendUserMessage} 发来的点对点文本消息时，会收到此回调。
     * @param uid  <br>
     *        消息发送者 ID 。
     * @param message  <br>
     *        收到的文本消息内容。
     * @note  
     *        + 你必须先调用 sendUserMessage{@link #IRTCRoom#sendUserMessage} 方法，才能收到该回调。
     */
    /**
     * @locale en
     * @type callback
     * @region Real-time messaging
     * @brief Receive this callback when you receive a text message (P2P) from another user in the room.
     * @param uid <br>
     *         User ID of the message sender.
     * @param message <br>
     *         The content of the received text message.
     * @note   
     *         + You must call the sendUserMessage{@link #IRTCRoom#sendUserMessage} method before you can receive the callback.
     */
    virtual void onUserMessageReceived(const char* uid, const char* message) {
        (void)uid;
        (void)message;
    }

    /**
     * @locale zh
     * @type callback
     * @region 实时消息通信
     * @brief 收到来自房间中其他用户通过 sendUserBinaryMessage{@link #IRTCRoom#sendUserBinaryMessage} 发来的点对点二进制消息时，会收到此回调。
     * @param uid 消息发送者 ID 。
     * @param size 消息长度 
     * @param message 收到的二进制消息内容。
     */
    /**
     * @locale en
     * @type callback
     * @region Real-time Message Communication
     * @brief A single user receives a callback (P2P) of binary messages from other uid-owned users in the same room.
     * @param uid User ID of the message sender.
     * @param size Message length.
     * @param message The content of the received binary message.
     */
    virtual void onUserBinaryMessageReceived(const char* uid, int size, const uint8_t* message) {
        (void)uid;
        (void)size;
        (void)message;
    }

    /**
     * @locale zh
     * @type callback
     * @region 实时消息通信
     * @brief 向房间内单个用户发送文本或二进制消息后（P2P），消息发送方会收到该消息发送结果回调。
     * @param msgid  <br>
     *            本条消息的 ID。
     * @param error  <br>
     *            文本或二进制消息发送结果，详见 UserMessageSendResult{@link #UserMessageSendResult}
     * @note  
     *        + 你必须先调用 sendUserMessage{@link #IRTCRoom#sendUserMessage} 或 sendUserBinaryMessage{@link #IRTCRoom#sendUserBinaryMessage} 接口，才能收到此回调。
     */
    /**
     * @locale en
     * @type callback
     * @region Real-time messaging
     * @brief After sending a text or binary message (P2P) to a single user in the room, the message sender receives a callback with the result of the message.
     * @param msgid <br>
     *             The ID of this message.
     * @param error <br>
     *             Text or binary message sending results. See UserMessageSendResult{@link #UserMessageSendResult}
     * @note   
     *         + You must first call the sendUserMessage{@link #IRTCRoom#sendUserMessage} or sendUserBinaryMessage{@link #IRTCRoom#sendUserBinaryMessage} interface to receive this callback.
     */
    virtual void onUserMessageSendResult(int64_t msgid, int error) {
        (void)msgid;
        (void)error;
    }

    /**
     * @locale zh
     * @type callback
     * @region 实时消息通信
     * @brief 调用 sendRoomMessage{@link #IRTCRoom#sendRoomMessage} 或 sendRoomBinaryMessage{@link #IRTCRoom#sendRoomBinaryMessage} 向房间内群发文本或二进制消息后，消息发送方会收到该消息发送结果回调。
     * @param msgid  <br>
     *        本条消息的 ID
     * @param error  <br>
     *        消息发送结果  <br>
     *        详见 RoomMessageSendResult{@link #RoomMessageSendResult}
     */
    /**
     * @locale en
     * @type callback
     * @region Real-time messaging
     * @brief When the sendRoomMessage{@link #IRTCRoom#sendRoomMessage} function is called to send a message, the sending result of this message (feedback) is called back.
     * @param msgid <br>
     *         ID of this message
     * @param error <br>
     *         Message sending result <br>
     *         See RoomMessageSendResult{@link #RoomMessageSendResult}
     */
    virtual void onRoomMessageSendResult(int64_t msgid, int error) {
        (void)msgid;
        (void)error;
    }

    /**
     * @hidden for internal use only
     */
    virtual void onRoomModeChanged(RtcRoomMode mode) {
        (void)mode;
    }

    /**
     * @hidden for internal use only
     * @brief callback when the maximum screen share fps is changed
     * @param fps maximum screen share fps
     */
    virtual void onMaximumScreenShareFpsUpdated(int fps) {
        (void)fps;
    }

    /**
     * @locale zh
     * @hidden for internal use only
     * @brief 最大屏幕共享帧率改变时的回调
     * @param screen_pixels 为了保持帧率而推荐的最大视频宽度×高度的值。
     */
    /**
     * @locale en
     * @hidden for internal use only
     * @brief Callback when the maximum screen shared pixels (resolution) is chang
     * @param screenPixels The recommended maximum video width × height value to maintain the frame rate.
     */
    virtual void onMaximumScreenSharePixelsUpdated(int screen_pixels) {
        (void)screen_pixels;
    }

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
     * @param uid User ID of the video stream that was disabled/unbanned
     * @param banned Video stream sending status <br>
     *         + true: Video stream sending was disabled <br>
     *         + false: Video stream sending was unbanned
     * @note   
     *         + When the specified user in the room is disabled/unbanned Video stream sending, all users in the room will receive the callback. <br>
     *        + If the banned user leaves or disconnects and then rejoins the room, the user is still banned from publishing audio stream, and all users in the room will be informed via the callback. <br>
     *         + After the specified user is banned, other users in the room will check out and enter the room again, and will receive the callback again. <br>
     *         + If the Audio selection is enabled in the console, only the user whose stream is banned will receive this callback.
     */
    virtual void onVideoStreamBanned(const char* uid, bool banned) {
        (void)uid;
        (void)banned;
    }

    /**
     * @locale zh
     * @type callback
     * @region 多房间
     * @brief 发布端调用 setMultiDeviceAVSync{@link #IRTCRoom#setMultiDeviceAVSync} 后音视频同步状态发生改变时，会收到此回调。
     * @param state 音视频同步状态，参看 AVSyncState{@link #AVSyncState}。
     */
    /**
     * @locale en
     * @type callback
     * @region Multi-Room
     * @brief Stream publisher will receive this callback when the A/V synchronization state changes after setMultiDeviceAVSync{@link #IRTCRoom#setMultiDeviceAVSync} is called.
     * @param state A/V synchronization state, see AVSyncState{@link #AVSyncState}.
     */
    virtual void onAVSyncStateChange(AVSyncState state) {
        (void)state;
    }

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
     *        + 在控制台开启音频选路后，只有被封禁/解禁用户会收到该回调。   <br>
     *        + 同一房间解散后再次创建，房间内状态清空。
     */
    /**
     * @locale en
     * @type callback
     * @region Audio event callback
     * @brief All the users in the room will get informed via this callback when a user is banned or the ban of the user has been lifted by calling BanUserStream/UnbanUserStream on the server side.
     * @param uid Disabled/unbanned audio stream user ID
     * @param banned Audio stream sending status <br>
     *         + true: audio stream sending is disabled <br>
     *         + false: audio stream sending is unbanned
     * @note   
     *         + Specified users in the room are prohibited/all users in the room when audio stream sending is unbanned Will receive the callback. <br>
     *        + If the banned user leaves or disconnects and then rejoins the room, the user is still banned from publishing audio stream, and all users in the room will be informed via the callback. <br>
     *         + After the specified user is banned, other users in the room will check out and enter the room again, and will receive the callback again. <br>
     *         + The same room is created again after dissolution, and the state in the room is empty.  <br>
     *         + If the Audio selection is enabled in the console, only the user whose stream is banned will receive this callback.
     */
    virtual void onAudioStreamBanned(const char* uid, bool banned) {
        (void)uid;
        (void)banned;
    }

    /**
     * @locale zh
     * @type callback
     * @region 多房间
     * @brief 跨房间媒体流转发状态和错误回调
     * @param infos 跨房间媒体流转发目标房间信息数组，详见 ForwardStreamStateInfo{@link #ForwardStreamStateInfo}
     * @param info_count 数组长度，代表目标房间数
     */
    /**
     * @locale en
     * @type callback
     * @region Multi-room
     * @brief Callback returning the state and errors during relaying the media stream to each of the rooms
     * @param infos Array of the state and errors of each target room. Refer to ForwardStreamStateInfo{@link #ForwardStreamStateInfo} for more information.
     * @param info_count The number of the target rooms
     */
    virtual void onForwardStreamStateChanged(ForwardStreamStateInfo* infos, int info_count) {
    }

    /**
     * @locale zh
     * @type callback
     * @region 多房间
     * @brief 跨房间媒体流转发事件回调
     * @param infos 跨房间媒体流转发目标房间事件数组，详见 ForwardStreamEventInfo{@link #ForwardStreamEventInfo}
     * @param info_count 数组长度，代表目标房间数
     */
    /**
     * @locale en
     * @type callback
     * @region Multi-room
     * @brief Callback returning the events during relaying the media stream to each room
     * @param infos Array of the event of each target room. Refer to ForwardStreamEventInfo{@link #ForwardStreamEventInfo} for more information.
     * @param info_count The number of the target rooms
     */
    virtual void onForwardStreamEvent(ForwardStreamEventInfo* infos, int info_count) {
    }

    /**
     * @locale zh
     * @type callback
     * @brief 加入房间并发布或订阅流后， 以每 2 秒一次的频率，报告本地用户和已订阅的远端用户的上下行网络质量信息。
     * @param local_quality 本端网络质量，详见 NetworkQualityStats{@link #NetworkQualityStats}。
     * @param remote_qualities 已订阅用户的网络质量，详见 NetworkQualityStats{@link #NetworkQualityStats}。
     * @param remote_quality_num `remoteQualities` 数组长度
     * @note 更多通话中的监测接口，详见[通话中质量监测](https://www.volcengine.com/docs/6348/106866)。
     */
    /**
     * @locale en
     * @type callback
     * @brief Report the network quality of the users every 2s after the local user joins the room and starts publishing or subscribing to a stream.
     * @param local_quality Local network quality. Refer to NetworkQualityStats{@link #NetworkQualityStats} for details.
     * @param remote_qualities Network quality of the subscribed users. Refer to NetworkQualityStats{@link #NetworkQualityStats} for details.
     * @param remote_quality_num Array length of `remoteQualities`
     * @note See [In-call Stats](106866) for more information.
     */
    virtual void onNetworkQuality(const NetworkQualityStats& local_quality, const NetworkQualityStats* remote_qualities, int remote_quality_num) {
    }

    /**
     * @locale zh
     * @valid since 3.52.
     * @type callback
     * @region 房间管理
     * @brief 调用 setRoomExtraInfo{@link #IRTCRoom#setRoomExtraInfo} 设置房间附加信息结果的回调。
     * @param task_id 调用 setRoomExtraInfo 的任务编号。
     * @param error_code 设置房间附加信息的结果，详见 SetRoomExtraInfoResult{@link #SetRoomExtraInfoResult}
     */
    /**
     * @locale en
     * @valid since 3.52.
     * @type callback
     * @region Room Management
     * @brief Callback on the result of calling setRoomExtraInfo{@link #IRTCRoom#setRoomExtraInfo} to set extra information about the room.
     * @param task_id The task ID of the API call.
     * @param error_code See SetRoomExtraInfoResult{@link #SetRoomExtraInfoResult} for the setting results and reasons.
     */
    virtual void onSetRoomExtraInfoResult(int64_t task_id, SetRoomExtraInfoResult error_code) {
        (void)task_id;
        (void)error_code;
    }

    /**
     * @locale zh
     * @valid since 3.52.
     * @type callback
     * @region 房间管理
     * @brief 接收同一房间内，其他用户调用 setRoomExtraInfo{@link #IRTCRoom#setRoomExtraInfo} 设置的房间附加信息的回调。
     * @param key 房间附加信息的键值
     * @param value 房间附加信息的内容
     * @param last_update_user_id 最后更新本条信息的用户 ID。
     * @param last_update_time_ms 最后更新本条信息的 Unix 时间，单位：毫秒。
     * @note 新进房的用户会收到进房前房间内已有的全部附加信息通知。
     */
    /**
     * @locale en
     * @valid since 3.52.
     * @type callback
     * @region Room Management
     * @brief Callback used to receive the extra information set by the other users in the same room with setRoomExtraInfo{@link #IRTCRoom#setRoomExtraInfo}.
     * @param key Key of the extra information.
     * @param value Content of the extra information.
     * @param last_update_user_id The ID of the last user who updated this information.
     * @param last_update_time_ms The Unix time in ms when this information was last updated. 
     */
    virtual void onRoomExtraInfoUpdate(const char*key, const char* value, const char* last_update_user_id, int64_t last_update_time_ms) {
        (void)key;
        (void)value;
        (void)last_update_user_id;
        (void)last_update_time_ms;
    }

    /**
     * @locale zh
     * @valid since 3.54
     * @type callback
     * @region 房间管理
     * @brief 用户调用 setUserVisibility{@link #IRTCRoom#setUserVisibility} 设置用户可见性的回调。
     * @param current_user_visibility 当前用户的可见性。  <br>
     *        + true: 可见，用户可以在房间内发布音视频流，房间中的其他用户将收到用户的行为通知，例如进房、开启视频采集和退房。<br>
     *        + false: 不可见，用户不可以在房间内发布音视频流，房间中的其他用户不会收到用户的行为通知，例如进房、开启视频采集和退房。
     * @param error_code 设置用户可见性错误码，参看 UserVisibilityChangeError{@link #UserVisibilityChangeError}。
     */
    /**
     * @locale en
     * @valid since 3.54
     * @type callback
     * @region Room Management
     * @brief Callback for user to set user visibility by calling setUserVisibility{@link #IRTCRoom#setUserVisibility}.
     * @param current_user_visibility Visibility of the current user.<br>
     *        + true: Visible. The user can publish media streams. The other users in the room get informed of the behaviors of the user, such as joining room, starting video capture, and leaving room.<br>
     *        + false: Invisible. The user cannot publish media streams. The other users in the room do not get informed of the behaviors of the user, such as joining room, starting video capture, or leaving room.
     * @param error_code Error code for setting user visibility. See UserVisibilityChangeError{@link #UserVisibilityChangeError}.
     */
    virtual void onUserVisibilityChanged(bool current_user_visibility, UserVisibilityChangeError error_code) {
        (void)current_user_visibility;
        (void)error_code;
    }

    /**
     * @locale zh
     * @type callback
     * @region 字幕翻译服务
     * @brief  字幕状态发生改变回调。 <br>
     *         当用户调用 startSubtitle{@link #IRTCRoom#startSubtitle} 和 stopSubtitle{@link #IRTCRoom#stopSubtitle} 使字幕状态发生改变或出现错误时，触发该回调。  
     * @param state 字幕状态。参看 SubtitleState{@link #SubtitleState}。
     * @param error_code 字幕任务错误码。参看 SubtitleErrorCode{@link #SubtitleErrorCode}。
     * @param error_message 与第三方服务有关的错误信息。
     */
    /**
     * @locale en
     * @hidden currently not available 
     * @type callback
     * @region Subtitle translation service
     * @brief  Callback on subtitle states. <br>
     *         After you call startSubtitle{@link #IRTCRoom#startSubtitle} and stopSubtitle{@link #IRTCRoom#stopSubtitle}, you will receive this callback which informs you of the states and error codes of the subtitling task, as well as detailed information on the third party services' errors. 
     * @param state The states of subtitles. Refer to SubtitleState{@link #SubtitleState} for details. 
     * @param error_code  Error codes of the subtitling task. Refer to SubtitleErrorCode{@link #SubtitleErrorCode}.
     * @param error_message Detailed information on the third party services' errors. 
     */
    virtual void onSubtitleStateChanged(SubtitleState state, SubtitleErrorCode error_code, const char* error_message) {
    }

    /**
     * @locale zh
     * @type callback
     * @region 字幕翻译服务
     * @brief  字幕相关内容回调。 <br>
     *         当用户调用 startSubtitle{@link #IRTCRoom#startSubtitle} 后会收到此回调，通知字幕的相关信息。
     * @param subtitles 字幕消息内容。参看 SubtitleMessage{@link #SubtitleMessage}。
     * @param cnt 字幕消息个数。
     */
    /**
     * @locale en
     * @hidden currently not available 
     * @type callback
     * @region Subtitle translation service
     * @brief  Callback on subtitle messages.  <br>
     *         After calling startSubtitle{@link #IRTCRoom#startSubtitle}, you will receive this callback which informs you of the related information on subtitles. 
     * @param subtitles Subtitle messages. Refer to SubtitleMessage{@link #SubtitleMessage} for details. 
     * @param cnt The number of subtitle messages.
     */
    virtual void onSubtitleMessageReceived(const SubtitleMessage* subtitles, int cnt) {
    }
};

} // namespace bytertc

