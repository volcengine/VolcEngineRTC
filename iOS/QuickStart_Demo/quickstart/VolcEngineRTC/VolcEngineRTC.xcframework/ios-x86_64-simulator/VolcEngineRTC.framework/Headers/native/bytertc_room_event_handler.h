/*
 * Copyright (c) 2020 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC Room Event Handler Interface
*/

#pragma once

#ifndef BYTE_RTC_ROOM_EVENT_HANDLER_INTERFACE_H__
#define BYTE_RTC_ROOM_EVENT_HANDLER_INTERFACE_H__

#include "rtc/bytertc_defines.h"

namespace bytertc {
/** 
 * @type callback
 * @brief 音视频房间事件回调接口
 */
class IRTCRoomEventHandler {
public:

    /**
     * @hidden constructor/destructor
     */
    virtual ~IRTCRoomEventHandler() {
    }

    /** 
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
     *                  `elapsed`表示加入房间耗时，即本地用户从调用 joinRoom{@link #IRTCRoom#joinRoom} 到加入房间成功所经历的时间间隔，单位为 ms。
     */
    virtual void onRoomStateChanged(
            const char* room_id, const char* uid, int state, const char* extra_info) {
        (void)room_id;
        (void)state;
        (void)extra_info;
    }

    /** 
     * @type callback
     * @region 房间管理
     * @brief 流状态改变回调，发生流相关的警告或错误时会收到此回调。
     * @param [in] room_id 房间 ID。
     * @param [in] uid 用户 ID。
     * @param [in] state 流状态码，参看 ErrorCode{@link #ErrorCode} 及 WarningCode{@link #WarningCode}。
     * @param [in] extra_info 附加信息，目前为空。
     */
    virtual void onStreamStateChanged(
            const char* room_id, const char* uid, int state, const char* extra_info) {
        (void)room_id;
        (void)uid;
        (void)state;
        (void)extra_info;
    }

    /** 
     * @type callback
     * @region 房间管理
     * @brief 离开房间成功回调。  <br>
     *        用户调用 leaveRoom{@link #IRTCRoom#leaveRoom} 方法后，SDK 会停止所有的发布订阅流，并在释放所有与通话相关的音视频资源后，通过此回调通知用户离开房间成功。  <br>
     * @param [in] stats 保留参数，目前为空。
     * @notes  <br>
     *       + 用户调用 leaveRoom{@link #IRTCRoom#leaveRoom} 方法离开房间后，若立即调用 destroyRTCVideo{@link #destroyRTCVideo} 方法销毁 RTC 引擎，则将无法收到此回调事件。  <br>
     *       + 离开房间后，如果 App 需要使用系统音视频设备，则建议收到此回调后再初始化音视频设备，否则可能由于 SDK 占用音视频设备而导致初始化失败。  <br>
     */
     virtual void onLeaveRoom(const RtcRoomStats& stats) {
        (void)stats;
    }

    /** 
     * @deprecated since 3.41 and will be deleted in 3.51, use onRoomStateChanged{@link #IRTCRoomEventHandler#onRoomStateChanged} and onStreamStateChanged{@link #IRTCRoomEventHandler#onStreamStateChanged} instead.
     * @type callback
     * @region 房间管理
     * @brief SDK 发生警告回调。  <br>
     *        SDK 内部遇到可恢复错误时，在尝试自动恢复的同时，会通过此回调通知用户。此回调事件仅用作通知。  <br>
     * @param [in] warn 警告码，参看 WarningCode{@link #WarningCode}。  <br>
     */
    BYTERTC_DEPRECATED virtual void onRoomWarning(int warn) {
        (void)warn;
    }

    /** 
     * @deprecated since 3.41 and will be deleted in 3.51, use onRoomStateChanged{@link #IRTCRoomEventHandler#onRoomStateChanged} and onStreamStateChanged{@link #IRTCRoomEventHandler#onStreamStateChanged} instead.
     * @type callback
     * @region 房间管理
     * @brief SDK 发生错误回调。  <br>
     *        SDK 内部遇到不可恢复错误时，会通过此回调通知 App，需要 App 根据错误码进行操作或提示用户。  <br>
     * @param [in] err 错误码，参看 ErrorCode{@link #ErrorCode}。  <br>
     */
    virtual void onRoomError(int err) {
        (void)err;
    }
    /** 
     * @type callback
     * @brief Token 进房权限过期前 30 秒将触发该回调。<br>
     *        收到该回调后，你需调用 updateToken{@link #IRTCRoom#updateToken} 更新 Token 进房权限。
     * @notes 若未能及时更新 Token 进房权限导致其过期实效： <br>
     *        + 用户此时尝试进房会收到 onRoomStateChanged{@link #IRTCRoomEventHandler#onRoomStateChanged} 回调，提示错误码为 `-1000` Token 过期； <br>
     *        + 用户已在房间内则会被移出房间，本地用户会收到 onRoomStateChanged{@link #IRTCRoomEventHandler#onRoomStateChanged} 回调，提示错误码为 `-1009` Token 过期，同时远端用户会收到 onUserLeave{@link #IRTCRoomEventHandler#onUserLeave} 回调，提示原因为 `2` Token 进房权限过期。
     */
     virtual void onTokenWillExpire() {

    }
    /** 
     * @type callback
     * @brief Token 发布权限过期前 30 秒将触发该回调。<br>
     *        收到该回调后，你需调用 updateToken{@link #IRTCRoom#updateToken} 更新 Token 发布权限。
     * @notes 若收到该回调后未及时更新 Token，Token 发布权限过期后： <br>
     *        + 此时尝试发布流会收到 onStreamStateChanged{@link #IRTCRoomEventHandler#onStreamStateChanged} 回调，提示错误码为 `-1002` 没有发布权限； <br>
     *        + 已在发布中的流会停止发布，发布端会收到 onStreamStateChanged{@link #IRTCRoomEventHandler#onStreamStateChanged} 回调，提示错误码为 `-1002` 没有发布权限，同时远端用户会收到 onUserUnpublishStream{@link #IRTCRoomEventHandler#onUserUnpublishStream}/onUserUnpublishScreen{@link #IRTCRoomEventHandler#onUserUnpublishScreen} 回调，提示原因为 `6` 发流端发布权限过期。
     */
    virtual void onPublishPrivilegeTokenWillExpire() {

    }
    /** 
     * @type callback
     * @brief Token 订阅权限过期前 30 秒将触发该回调。<br>
     *        收到该回调后，你需调用 updateToken{@link #IRTCRoom#updateToken} 更新 Token 订阅权限有效期。
     * @notes 若收到该回调后未及时更新 Token，Token 订阅权限过期后，尝试新订阅流会失败，已订阅的流会取消订阅，并且会收到 onStreamStateChanged{@link #IRTCRoomEventHandler#onStreamStateChanged} 回调，提示错误码为 `-1003` 没有订阅权限。
     */
    virtual void onSubscribePrivilegeTokenWillExpire() {

    }

    /** 
     * @type callback
     * @region 数据统计
     * @brief 房间内通话统计信息回调。  <br>
     *        用户进房开始通话后，每 2s 收到一次本回调。
     * @param [in] stats 当前 RtcEngine 统计数据，详见 RtcRoomStats{@link #RtcRoomStats}
     */
    virtual void onRoomStats(const RtcRoomStats& stats) {
        (void)stats;
    }
    /** 
     * @hidden(Linux)
     * @type callback
     * @region 数据统计
     * @brief 本地流数据统计以及网络质量回调。  <br>
     *        本地用户发布流成功后，SDK 会周期性（2s）的通过此回调事件通知用户发布的流在此次统计周期内的质量统计信息。  <br>
     *        统计信息通过 LocalStreamStats{@link #LocalStreamStats} 类型的回调参数传递给用户，其中包括发送音视频比特率、发送帧率、编码帧率，网络质量等。
     * @param [in] stats 当前 RtcEngine 统计数据，详见 LocalStreamStats{@link #LocalStreamStats}。
     */
    virtual void onLocalStreamStats(const LocalStreamStats& stats) {
        (void)stats;
    }
    /** 
     * @type callback
     * @region 数据统计
     * @brief 本地订阅的远端音/视频流数据统计以及网络质量回调。  <br>
     *        本地用户订阅流成功后，SDK 会周期性（2s）的通过此回调事件通知用户订阅的流在此次统计周期内的质量统计信息，包括：发送音视频比特率、发送帧率、编码帧率，网络质量等。
     * @param [in] stats 当前 RtcEngine 统计数据，详见 RemoteStreamStats{@link #RemoteStreamStats}
     */
    virtual void onRemoteStreamStats(const RemoteStreamStats& stats) {
        (void)stats;
    }

    /** 
     * @type callback
     * @region 房间管理
     * @brief 远端可见用户加入房间，或房内隐身用户切换为可见的回调。<br>
     *        1. 远端用户调用 setUserVisibility{@link #IRTCRoom#setUserVisibility} 方法将自身设为可见后加入房间时，房间内其他用户将收到该事件。  <br>
     *        2. 远端可见用户断网后重新连入房间时，房间内其他用户将收到该事件。  <br>
     *        3. 房间内隐身远端用户调用 setUserVisibility{@link #IRTCRoom#setUserVisibility} 方法切换至可见时，房间内其他用户将收到该事件。  <br>
     *        4. 新进房用户会收到进房前已在房内的可见用户的进房回调通知。  <br>
     * @param [in] user_info 用户信息，详见 UserInfo{@link #UserInfo}  <br>
     * @param [in] elapsed 保留字段，无意义。
     */
     virtual void onUserJoined(const UserInfo& user_info, int elapsed) {
        (void)user_info;
        (void)elapsed;
    }

    /** 
     * @type callback
     * @brief 远端用户离开房间，或切至不可见时，本地用户会收到此事件
     * @param uid 离开房间，或切至不可见的的远端用户 ID。  <br>
     * @param reason 用户离开房间的原因，详见 UserOfflineReason{@link #UserOfflineReason}。 <br>
     *              + 0: 远端用户调用 leaveRoom{@link #IRTCRoom#leaveRoom} 主动退出房间。  <br>
     *              + 1: 远端用户因 Token 过期或网络原因等掉线。 详细信息请参看[连接状态提示](https://www.volcengine.com/docs/6348/95376)<br>
     *              + 2: 远端用户调用 setUserVisibility{@link #IRTCRoom#setUserVisibility} 切换至不可见状态。 <br>
     *              + 3: 服务端调用 OpenAPI 将远端用户踢出房间。
     */
    virtual void onUserLeave(const char* uid, UserOfflineReason reason) {
        (void)uid;
        (void)reason;
    }
    /** 
     * @deprecated since 3.36 and will be deleted in 3.51, use onUserUnpublishStream{@link #IRTCRoomEventHandler#onUserUnpublishStream} and onUserUnpublishScreen{@link #IRTCRoomEventHandler#onUserUnpublishScreen} instead.
     * @type callback
     * @region 房间管理
     * @brief 房间内的远端用户停止发布音视频流时，本地用户会收到此回调。
     * @param [in] stream 流的属性。参看 MediaStreamInfo{@link #MediaStreamInfo} 。
     * @param [in] reason 远端流移除的原因。参看 StreamRemoveReason{@link #StreamRemoveReason} 。
     */
    BYTERTC_DEPRECATED virtual void onStreamRemove(const MediaStreamInfo& stream, StreamRemoveReason reason) {
        (void)stream;
    }

    /** 
     * @deprecated since 3.36 and will be deleted in 3.51, use onUserPublishStream{@link #IRTCRoomEventHandler#onUserPublishStream} and onUserPublishScreen{@link #IRTCRoomEventHandler#onUserPublishScreen} instead.
     * @type callback
     * @region 房间管理
     * @brief 房间内的用户发布新的音视频流时，房间内的其他用户会收到此回调。包括移除后又重新发布的流。  <br>
     * @param [in] stream 流属性，参看 MediaStreamInfo{@link #MediaStreamInfo} 。  <br>
     */
    BYTERTC_DEPRECATED virtual void onStreamAdd(const MediaStreamInfo& stream) {
        (void)stream;
    }
    /** 
     * @type callback
     * @region 房间管理
     * @brief 房间内新增远端摄像头/麦克风采集的媒体流的回调。
     * @param [in] uid 远端流发布用户的用户 ID。
     * @param [in] type 远端媒体流的类型，参看 MediaStreamType{@link #MediaStreamType}。
     * @notes 当房间内的远端用户调用 publishStream{@link #IRTCRoom#publishStream} 成功发布由摄像头/麦克风采集的媒体流时，本地用户会收到该回调，此时本地用户可以自行选择是否调用 subscribeStream{@link #IRTCRoom#subscribeStream} 订阅此流。
     */
    virtual void onUserPublishStream(const char* uid, MediaStreamType type) {
        (void)uid;
        (void)type;
    }
    /** 
     * @type callback
     * @region 房间管理
     * @brief 房间内远端摄像头/麦克风采集的媒体流移除的回调。
     * @param [in] uid 移除的远端流发布用户的用户 ID。  <br>
     * @param [in] type 移除的远端流类型，参看 MediaStreamType{@link #MediaStreamType}。  <br>
     * @param [in] reason 远端流移除的原因，参看 StreamRemoveReason{@link #StreamRemoveReason}。
     * @notes 收到该回调通知后，你可以自行选择是否调用 unsubscribeStream{@link #IRTCRoom#unsubscribeStream} 取消订阅此流。
     */
    virtual void onUserUnpublishStream(const char* uid, MediaStreamType type,StreamRemoveReason reason) {
        (void)uid;
        (void)type;
        (void)reason;
    }
    /** 
     * @type callback
     * @region 房间管理
     * @brief 房间内新增远端屏幕共享音视频流的回调。
     * @param [in] uid 远端流发布用户的用户 ID。
     * @param [in] type 远端媒体流的类型，参看 MediaStreamType{@link #MediaStreamType}。
     * @notes 当房间内的远端用户调用 publishScreen{@link #IRTCRoom#publishScreen} 成功发布来自屏幕共享的音视频流时，本地用户会收到该回调，此时本地用户可以自行选择是否调用 subscribeScreen{@link #IRTCRoom#subscribeScreen} 订阅此流。（Linux 不支持）
     */
    virtual void onUserPublishScreen(const char* uid, MediaStreamType type) {
        (void)uid;
        (void)type;
    }
    /** 
     * @type callback
     * @region 房间管理
     * @brief 房间内远端屏幕共享音视频流移除的回调。
     * @param [in] uid 移除的远端流发布用户的用户 ID。  <br>
     * @param [in] type 移除的远端流类型，参看 MediaStreamType{@link #MediaStreamType}。  <br>
     * @param [in] reason 远端流移除的原因，参看 StreamRemoveReason{@link #StreamRemoveReason}。
     * @notes 收到该回调通知后，你可以自行选择是否调用 unsubscribeScreen{@link #IRTCRoom#unsubscribeScreen} 取消订阅此流。
     */
    virtual void onUserUnpublishScreen(const char* uid, MediaStreamType type,StreamRemoveReason reason) {
        (void)uid;
        (void)type;
        (void)reason;
    }

    /** 
     * @type callback
     * @region 房间管理
     * @brief 关于订阅媒体流状态改变的回调
     * @param [in] state_code 订阅媒体流状态，参看 SubscribeState{@link #SubscribeState}
     * @param [in] user_id 流发布用户的用户 ID
     * @param [in] info 流的属性，参看 SubscribeConfig{@link #SubscribeConfig}
     * @notes <br>
     *        本地用户收到该回调的时机包括：  <br>
     *        + 调用 subscribeStream{@link #IRTCRoom#subscribeStream} 或 unsubscribeStream{@link #IRTCRoom#unsubscribeStream} 订阅/取消订阅指定远端摄像头音视频流后；  <br>
     *        + 调用 subscribeScreen{@link #IRTCRoom#subscribeScreen} 或 unsubscribeScreen{@link #IRTCRoom#unsubscribeScreen} 订阅/取消订阅指定远端屏幕共享流后。
     */
    virtual void onStreamSubscribed(SubscribeState state_code, const char* user_id, const SubscribeConfig& info) {
        (void)state_code;
        (void)user_id;
        (void)info;
    }

    /** 
     * @hidden for internal use only
     * @type callback
     * @region 房间管理
     * @brief 当发布流成功的时候回调该事件。
     * @param [in] user_id 发布流的用户 ID。
     * @param [in] is_screen 该流是否为屏幕流。  <br>
     *             + Ture: 屏幕流；  <br>
     *             + False: 非屏幕流。  <br>
     */
    virtual void onStreamPublishSuccess(const char* user_id, bool is_screen) {
        (void)is_screen;
    }

    /** 
     * @type callback
     * @region 实时消息通信
     * @brief 接收到房间内广播消息的回调。
     * @param [in] uid  <br>
     *        消息发送者 ID
     * @param [in] message  <br>
     *        收到的消息内容
     * @notes 同一房间内其他用户调用 sendRoomMessage{@link #IRTCRoom#sendRoomMessage} 发送广播消息时会收到该回调。
     */
    virtual void onRoomMessageReceived(const char* uid, const char* message) {
        (void)uid;
        (void)message;
    }

    /** 
     * @type callback
     * @region 实时消息通信
     * @brief 收到房间内广播二进制消息的回调。<br>
     *        房间内其他用户调用 sendRoomBinaryMessage{@link #IRTCRoom#sendRoomBinaryMessage} 发送广播二进制消息时，收到此回调。
     * @param [in] uid  <br>
     *        消息发送者 ID
     * @param [in] size <br>
     *        收到的二进制消息长度
     * @param [in] message <br>
     *        收到的二进制消息内容
     * @notes 同一房间内其他用户调用 sendRoomBinaryMessage{@link #IRTCRoom#sendRoomBinaryMessage} 发送二进制广播消息时会收到该回调。
     */
    virtual void onRoomBinaryMessageReceived(const char* uid, int size, const uint8_t* message) {
        (void)uid;
        (void)size;
        (void)message;
    }
    /** 
     * @type callback
     * @region 实时消息通信
     * @brief 收到来自房间中其他用户通过 sendUserMessage{@link #IRTCRoom#sendUserMessage} 发来的点对点文本消息时，会收到此回调。
     * @param [in] uid  <br>
     *        消息发送者 ID 。
     * @param [in] message  <br>
     *        收到的文本消息内容。
     * @notes  <br>
     *        + 你必须先调用 sendUserMessage{@link #IRTCRoom#sendUserMessage} 方法，才能收到该回调。
     */
    virtual void onUserMessageReceived(const char* uid, const char* message) {
        (void)uid;
        (void)message;
    }

    /** 
     * @type callback
     * @region 实时消息通信
     * @brief 收到来自房间中其他用户通过 sendUserBinaryMessage{@link #IRTCRoom#sendUserBinaryMessage} 发来的点对点二进制消息时，会收到此回调。
     * @param [in] uid 消息发送者 ID 。
     * @param [in] size 消息长度 
     * @param [in] message 收到的二进制消息内容。
     */
    virtual void onUserBinaryMessageReceived(const char* uid, int size, const uint8_t* message) {
        (void)uid;
        (void)size;
        (void)message;
    }

    /** 
     * @type callback
     * @region 实时消息通信
     * @brief 向房间内单个用户发送文本或二进制消息后（P2P），消息发送方会收到该消息发送结果回调。
     * @param [in] msgid  <br>
     *            本条消息的 ID。
     * @param [in] error  <br>
     *            文本或二进制消息发送结果，详见 UserMessageSendResult{@link #UserMessageSendResult}
     * @notes  <br>
     *        + 你必须先调用 sendUserMessage{@link #IRTCRoom#sendUserMessage} 或 sendUserBinaryMessage{@link #IRTCRoom#sendUserBinaryMessage} 接口，才能收到此回调。
     */
    virtual void onUserMessageSendResult(int64_t msgid, int error) {
        (void)msgid;
        (void)error;
    }

    /** 
     * @type callback
     * @region 实时消息通信
     * @brief 调用 sendRoomMessage{@link #IRTCRoom#sendRoomMessage} 或 sendRoomBinaryMessage{@link #IRTCRoom#sendRoomBinaryMessage} 向房间内群发文本或二进制消息后，消息发送方会收到该消息发送结果回调。
     * @param [in] msgid  <br>
     *        本条消息的 ID
     * @param [in] error  <br>
     *        消息发送结果  <br>
     *        详见 RoomMessageSendResult{@link #RoomMessageSendResult}
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

#ifndef ByteRTC_AUDIO_ONLY
    /**
     * @hidden for internal use only
     * @brief callback when the maximum screen share fps is changed
     * @param [in] fps maximum screen share fps
     */
    virtual void onMaximumScreenShareFpsUpdated(int fps) {
        (void)fps;
    }

    /** 
     * @hidden for internal use only
     * @brief 最大屏幕共享帧率改变时的回调
     * @param [in] screenPixels 为了保持帧率而推荐的最大视频宽度×高度的值。
     */
    virtual void onMaximumScreenSharePixelsUpdated(int screenPixels) {
        (void)screenPixels;
    }

    /** 
     * @type callback
     * @region 视频管理
     * @brief 通过调用服务端 BanUserStream/UnbanUserStream 方法禁用/解禁指定房间内指定用户视频流的发送时，触发此回调。
     * @param [in] uid 被禁用/解禁的视频流用户 ID
     * @param [in] banned 视频流发送状态 <br>
     *        + true: 视频流发送被禁用 <br>
     *        + false: 视频流发送被解禁
     * @notes  <br>
     *        + 房间内指定用户被禁止/解禁视频流发送时，房间内所有用户都会收到该回调。  <br>
     *        + 若被封禁用户断网或退房后再进房，则依然是封禁状态，且房间内所有人会再次收到该回调。  <br>
     *        + 指定用户被封禁后，房间内其他用户退房后再进房，会再次收到该回调。  <br>
     *        + 同一房间解散后再次创建，房间内状态清空。
     */
    virtual void onVideoStreamBanned(const char* uid, bool banned) {
        (void)uid;
        (void)banned;
    }

    /** 
     * @type callback
     * @region 多房间
     * @brief 发布端调用 setMultiDeviceAVSync{@link #IRTCRoom#setMultiDeviceAVSync} 后音视频同步状态发生改变时，会收到此回调。
     * @param state 音视频同步状态，参看 AVSyncState{@link #AVSyncState}。
     */
    virtual void onAVSyncStateChange(AVSyncState state) {
        (void)state;
    }

#endif  // ByteRTC_AUDIO_ONLY
    /** 
     * @type callback
     * @region 音频事件回调
     * @brief 通过调用服务端 BanUserStream/UnbanUserStream 方法禁用/解禁指定房间内指定用户音频流的发送时，触发此回调。
     * @param [in] uid 被禁用/解禁的音频流用户 ID
     * @param [in] banned 音频流发送状态 <br>
     *        + true: 音频流发送被禁用 <br>
     *        + false: 音频流发送被解禁
     * @notes  <br>
     *        + 房间内指定用户被禁止/解禁音频流发送时，房间内所有用户都会收到该回调。  <br>
     *        + 若被封禁用户断网或退房后再进房，则依然是封禁状态，且房间内所有人会再次收到该回调。  <br>
     *        + 指定用户被封禁后，房间内其他用户退房后再进房，会再次收到该回调。  <br>
     *        + 在控制台开启大会模式后，只有被封禁/解禁用户会收到该回调。   <br>
     *        + 同一房间解散后再次创建，房间内状态清空。
     */
    virtual void onAudioStreamBanned(const char* uid, bool banned) {
        (void)uid;
        (void)banned;
    }

    /** 
     * @type callback
     * @region 多房间
     * @brief 跨房间媒体流转发状态和错误回调
     * @param [in] infos 跨房间媒体流转发目标房间信息数组，详见 ForwardStreamStateInfo{@link #ForwardStreamStateInfo}
     * @param [in] info_count 数组长度，代表目标房间数
     */
    virtual void onForwardStreamStateChanged(ForwardStreamStateInfo* infos, int info_count) {
    }

    /** 
     * @type callback
     * @region 多房间
     * @brief 跨房间媒体流转发事件回调
     * @param [in] infos 跨房间媒体流转发目标房间事件数组，详见 ForwardStreamEventInfo{@link #ForwardStreamEventInfo}
     * @param [in] info_count 数组长度，代表目标房间数
     */
    virtual void onForwardStreamEvent(ForwardStreamEventInfo* infos, int info_count) {
    }

    /** 
     * @type callback
     * @brief 加入房间并发布或订阅流后， 以每 2 秒一次的频率，报告本地用户和已订阅的远端用户的上下行网络质量信息。
     * @param [in] localQuality 本端网络质量，详见 NetworkQualityStats{@link #NetworkQualityStats}。
     * @param [in] remoteQualities 已订阅用户的网络质量，详见 NetworkQualityStats{@link #NetworkQualityStats}。
     * @param [in] remoteQualityNum `remoteQualities` 数组长度
     * @notes 更多通话中的监测接口，详见[通话中质量监测](https://www.volcengine.com/docs/6348/106866)。
     */
    virtual void onNetworkQuality(const NetworkQualityStats& localQuality, const NetworkQualityStats* remoteQualities, int remoteQualityNum) {
    }

    /** 
     * @valid since 3.52.
     * @type callback
     * @region 房间管理
     * @brief 调用 setRoomExtraInfo{@link #IRTCRoom#setRoomExtraInfo} 设置房间附加信息结果的回调。
     * @param [in] taskId 调用 setRoomExtraInfo 的任务编号。
     * @param [in] errCode 设置房间附加信息的结果，详见 SetRoomExtraInfoResult{@link #SetRoomExtraInfoResult}
     */
    virtual void onSetRoomExtraInfoResult(int64_t taskId, SetRoomExtraInfoResult errCode) {
        (void)taskId;
        (void)errCode;
    }

    /** 
     * @valid since 3.52.
     * @type callback
     * @region 房间管理
     * @brief 接收同一房间内，其他用户调用 setRoomExtraInfo{@link #IRTCRoom#setRoomExtraInfo} 设置的房间附加信息的回调。
     * @param [in] key 房间附加信息的键值
     * @param [in] value 房间附加信息的内容
     * @param [in] lastUpdateUserId 最后更新本条信息的用户 ID。
     * @param [in] lastUpdateTimeMs 最后更新本条信息的 Unix 时间，单位：毫秒。
     * @notes 新进房的用户会收到进房前房间内已有的全部附加信息通知。
     */
    virtual void onRoomExtraInfoUpdate(const char*key,const char* value,const char* lastUpdateUserId,int64_t lastUpdateTimeMs) {
        (void)key;
        (void)value;
        (void)lastUpdateUserId;
        (void)lastUpdateTimeMs;
    }

    /**  
     * @type callback
     * @region 字幕翻译服务
     * @brief  字幕状态发生改变回调。 <br>
     *         当用户调用 startSubtitle{@link #IRTCRoom#startSubtitle} 和 stopSubtitle{@link #IRTCRoom#stopSubtitle} 使字幕状态发生改变或出现错误时，触发该回调。  
     * @param [in] state 字幕状态。参看 SubtitleState{@link #SubtitleState}。
     * @param [in] errorCode  字幕任务错误码。参看 SubtitleErrorCode{@link #SubtitleErrorCode}。
     * @param [in] errorMessage  与第三方服务有关的错误信息。
     */
    virtual void onSubtitleStateChanged(SubtitleState state, SubtitleErrorCode error_code, const char* error_message) {
    }

    /**  
     * @type callback
     * @region 字幕翻译服务
     * @brief  字幕相关内容回调。 <br>
     *         当用户调用 startSubtitle{@link #IRTCRoom#startSubtitle} 后会收到此回调，通知字幕的相关信息。
     * @param [in] subtitles  字幕消息内容。参看 SubtitleMessage{@link #SubtitleMessage}。
     * @param [in] cnt  字幕消息个数。
     */
    virtual void onSubtitleMessageReceived(const SubtitleMessage* subtitles, int cnt) {
    }
};

} // namespace bytertc

#endif // BYTE_RTC_ROOM_EVENT_HANDLER_INTERFACE_H__
