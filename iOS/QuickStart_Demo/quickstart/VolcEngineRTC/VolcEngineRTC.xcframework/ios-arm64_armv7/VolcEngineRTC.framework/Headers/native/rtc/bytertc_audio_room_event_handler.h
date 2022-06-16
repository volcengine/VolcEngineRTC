/*
 * Copyright (c) 2022 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC Room Event Handler Interface
*/

#pragma once

#include "bytertc_audio_defines.h"

namespace bytertc {
/** 
 * @type callback
 * @brief 音频房间事件回调接口
 */
class IRTCAudioRoomEventHandler {
public:
    /** 
     * @hidden
     * @brief 析构函数
     */
    virtual ~IRTCAudioRoomEventHandler() {}

    /** 
     * @type callback
     * @region 房间管理
     * @brief 首次加入房间/重连加入房间的回调。此回调表示用户调用 JoinRoom{@link #IRTCAudioRoom#JoinRoom} 的结果，根据错误码判断成功/失败以及区别是否为重连。  <br>
     * @param [in] room_id 房间 ID。  <br>
     * @param [in] uid 用户 ID。  <br>
     * @param [in] error_code 用户加入房间回调的状态码。  <br>
     *        + 0: 加入房间成功；  <br>
     *        + 非 0: 加入房间失败，具体原因参看 ErrorCode{@link #ErrorCode} 以及 WarningCode{@link #WarningCode}。  <br>
     * @param [in] join_type 用户加入房间的类型，标识用户第一次加入或断网重连加入。参看 JoinRoomType{@link #JoinRoomType}。  <br>
     * @param [in] elapsed  重连耗时。本地用户从连接断开到重连成功所经历的时间间隔，单位为 ms，加入房间失败为 -1  <br>
     */
    virtual void OnJoinRoomResult(const char* room_id, const char* uid,
            int error_code, JoinRoomType join_type, int elapsed) {
        (void)room_id;
        (void)error_code;
        (void)join_type;
        (void)elapsed;
    }

    /** 
     * @type callback
     * @region 房间管理
     * @brief 离开房间回调。  <br>
     *        用户调用 LeaveRoom{@link #IRTCAudioRoom#LeaveRoom} 方法后，SDK 会停止所有的发布订阅流，并在释放所有与通话相关的音频资源后，通过此回调通知用户离开房间成功。  <br>
     * @param [in] stats 本次通话的统计数据，参看 RtcRoomStats{@link #RtcRoomStats} 。  <br>
     * @notes  <br>
     *       + 用户调用 LeaveRoom{@link #IRTCAudioRoom#LeaveRoom} 方法离开房间后，若立即调用 DestroyRTCAudioEngine{@link #DestroyRTCAudioEngine} 方法销毁 RTC 引擎，则将无法收到此回调事件。  <br>
     *       + 离开房间后，如果 App 需要使用系统音频设备，则建议收到此回调后再初始化音频设备，否则可能由于 SDK 占用音频设备而导致初始化失败。  <br>
     */
    virtual void OnLeaveRoom(const RtcRoomStats& stats) {
        (void)stats;
    }

    /** 
     * @type callback
     * @region 房间管理
     * @brief SDK 发生警告回调。  <br>
     *        SDK 内部遇到可恢复错误时，在尝试自动恢复的同时，会通过此回调通知用户。此回调事件仅用作通知。  <br>
     * @param [in] warn 警告码，参看 WarningCode{@link #WarningCode}。  <br>
     */
    virtual void OnRoomWarning(int warn) {
        (void)warn;
    }

    /** 
     * @type callback
     * @region 房间管理
     * @brief SDK 发生错误回调。  <br>
     *        SDK 内部遇到不可恢复错误时，会通过此回调通知 App，需要 App 根据错误码进行操作或提示用户。  <br>
     * @param [in] err 错误码，参看 ErrorCode{@link #ErrorCode}。  <br>
     */
    virtual void OnRoomError(int err) {
        (void)err;
    }
    /** 
     * @type callback
     * @brief Token 过期前 30 秒将触发该回调。<br>
     *        调用 UpdateToken{@link #IRTCAudioRoom#UpdateToken} 更新 Token。否则 Token 过期后，用户将被移出房间无法继续进行语音通话。
     */
     virtual void OnTokenWillExpire() {

    }
    /** 
     * @type callback
     * @region 数据统计
     * @brief 房间内通话统计信息回调。   <br>
     *        用户进房开始通话后，每 2s 收到一次本回调。
     * @param [in] stats 当前 RtcEngine 统计数据，详见 RtcRoomStats{@link #RtcRoomStats}
     */
    virtual void OnRoomStats(const RtcRoomStats& stats) {
        (void)stats;
    }

    /** 
     * @type callback
     * @region 数据统计
     * @brief 发布流成功后，每隔 2s 收到此回调，了解发布的流在此周期内的网络质量信息。
     * @param [in] stats 当前 RtcEngine 统计数据，详见 LocalStreamStats{@link #LocalStreamStats}
     */
    virtual void OnLocalStreamStats(const LocalStreamStats& stats) {
        (void)stats;
    }
    /** 
     * @type callback
     * @region 数据统计
     * @brief 每隔 2s 收到此回调，了解订阅的远端用户发布的流在此周期内的网络质量信息。
     * @param [in] stats 当前 RtcEngine 统计数据，详见 RemoteStreamStats{@link #RemoteStreamStats}
     */
    virtual void OnRemoteStreamStats(const RemoteStreamStats& stats) {
        (void)stats;
    }

    /** 
     * @type callback
     * @region 房间管理
     * @brief 远端可见用户加入房间，或房内隐身用户切换为可见的回调。<br>
     *        1. 远端用户调用 SetUserVisibility{@link #IRTCAudioRoom#SetUserVisibility} 方法将自身设为可见后加入房间时，房间内其他用户将收到该事件。  <br>
     *        2. 远端可见用户断网后重新连入房间时，房间内其他用户将收到该事件。  <br>
     *        3. 房间内隐身远端用户调用 SetUserVisibility{@link #IRTCAudioRoom#SetUserVisibility} 方法切换至可见时，房间内其他用户将收到该事件。  <br>
     *        4. 新进房用户会收到进房前已在房内的可见用户的进房回调通知。  <br>
     * @param [in] user_info 用户信息，详见 UserInfo{@link #UserInfo}  <br>
     * @param [in] elapsed 此参数无意义
     */
    virtual void OnUserJoined(const UserInfo& user_info, int elapsed) {
        (void)user_info;
        (void)elapsed;
    }

    /** 
     * @type callback
     * @brief 远端用户离开房间，或切至不可见时，本地用户会收到此事件
     * @param uid 离开房间，或切至不可见的的远端用户 ID。  <br>
     * @param reason 用户离开房间的原因：  <br>
     *              + 0: 远端用户调用 LeaveRoom{@link #IRTCAudioRoom#LeaveRoom} 主动退出房间。  <br>
     *              + 1: 远端用户因 Token 过期或网络原因等掉线。 <br>
     *              + 2: 远端用户调用 SetUserVisibility{@link #IRTCAudioRoom#SetUserVisibility} 切换至不可见状态。 <br>
     *              + 3: 服务端调用 OpenAPI 将远端用户踢出房间。
     */
    virtual void OnUserLeave(const char* uid, UserOfflineReason reason) {
        (void)uid;
        (void)reason;
    }

    /** 
     * @type callback
     * @region 音频事件回调
     * @brief 房间内的用户调用 StartAudioCapture{@link #IRTCAudioEngine#StartAudioCapture} 开启音频采集时，房间内其他用户会收到此回调。
     * @param [in] user_id 开启音频采集的远端用户 ID
     */
    virtual void OnUserStartAudioCapture(const char* user_id) {
        (void)user_id;
    }

    /** 
     * @type callback
     * @region 音频事件回调
     * @brief 房间内的用户调用 StopAudioCapture{@link #IRTCAudioEngine#StopAudioCapture} 关闭音频采集时，房间内其他用户会收到此回调。
     * @param [in] user_id 关闭音频采集的远端用户 ID
     */
    virtual void OnUserStopAudioCapture(const char* user_id) {
        (void)user_id;
    }

    /** 
     * @type callback
     * @region 音频事件回调
     * @brief 本地采集到第一帧音频帧时，收到该回调
     */
    virtual void OnFirstLocalAudioFrame() {}

    /** 
     * @type callback
     * @region 音频事件回调
     * @brief 接收到来自远端某音频流的第一帧时，收到该回调。
     * @param [in] key 远端音频流信息, 详见 RemoteStreamKey{@link #RemoteStreamKey}
     * @notes 用户刚收到房间内每一路音频流时，都会收到该回调。
     */
    virtual void OnFirstRemoteAudioFrame(const RemoteStreamKey& key) {
        (void)key;
    }
    /** 
     * @type callback
     * @region 房间管理
     * @brief 房间内新增远端音频流的回调。
     * @param [in] uid 远端流发布用户的用户 ID。
     * @notes 当房间内的远端用户调用 PublishStream{@link #IRTCAudioRoom#PublishStream} 成功发布音频流时，本地用户会收到该回调，此时本地用户可以自行选择是否调用 SubscribeStream{@link #IRTCAudioRoom#SubscribeStream} 订阅此流。
     */
    virtual void OnUserPublishStream(const char* uid) {
        (void)uid;
    }
    /** 
     * @type callback
     * @region 房间管理
     * @brief 房间内远端音频流移除的回调。
     * @param [in] uid 移除的远端流发布用户的用户 ID。  <br>
     * @param [in] reason 远端流移除的原因，参看 StreamRemoveReason{@link #StreamRemoveReason}。
     * @notes 收到该回调通知后，你可以自行选择是否调用 UnsubscribeStream{@link #IRTCAudioRoom#UnsubscribeStream} 取消订阅此流。
     */
    virtual void OnUserUnPublishStream(const char* uid, StreamRemoveReason reason) {
        (void)uid;
        (void)reason;
    }

    /** 
     * @type callback
     * @region 实时消息通信
     * @brief 接收到房间内广播消息的回调。
     * @param [in] uid  <br>
     *        消息发送者 ID
     * @param [in] message  <br>
     *        收到的消息内容
     * @notes 同一房间内其他用户调用 SendRoomMessage{@link #IRTCAudioRoom#SendRoomMessage} 发送广播消息时会收到该回调。
     */
    virtual void OnRoomMessageReceived(const char* uid, const char* message) {
        (void)uid;
        (void)message;
    }

    /** 
     * @type callback
     * @region 实时消息通信
     * @brief 接收到房间内二进制广播消息的回调。
     * @param [in] uid  <br>
     *        消息发送者 ID
     * @param [in] size <br>
     *        收到的二进制消息长度
     * @param [in] message <br>
     *        收到的二进制消息内容
     * @notes 同一房间内其他用户调用 SendRoomBinaryMessage{@link #IRTCAudioRoom#SendRoomBinaryMessage} 发送二进制广播消息时会收到该回调。
     */
    virtual void OnRoomBinaryMessageReceived(const char* uid, int size, const uint8_t* message) {
        (void)uid;
        (void)size;
        (void)message;
    }

    /** 
     * @type callback
     * @region 实时消息通信
     * @brief 收到来自房间中其他用户发来的文本消息时（P2P），会收到此回调。
     * @param [in] uid  <br>
     *        消息发送者 ID 。
     * @param [in] message  <br>
     *        收到的文本消息内容。
     * @notes  <br>
     *        + 你必须先调用 SendUserMessage{@link #IRTCAudioRoom#SendUserMessage} 方法，才能收到该回调。
     */
    virtual void OnUserMessageReceived(const char* uid, const char* message) {
        (void)uid;
        (void)message;
    }

    /** 
     * @type callback
     * @region 实时消息通信
     * @brief 单个用户接收到同一房间内其他 uid 所属用户发来二进制消息的回调（P2P）。
     * @param [in] uid  <br>
     *        消息发送者 ID 。
     * @param [in] message  <br>
     *        收到的二进制消息内容。
     * @notes  <br>
     *        + 同一房间内其他用户调用 SendUserBinaryMessage{@link #IRTCAudioRoom#SendUserBinaryMessage} 发送二进制消息给本地用户时，本地用户会收到该回调。
     */
    virtual void OnUserBinaryMessageReceived(const char* uid, int size, const uint8_t* message) {
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
     *        + 你必须先调用 SendUserMessage{@link #IRTCAudioRoom#SendUserMessage} 或 SendUserBinaryMessage{@link #IRTCAudioRoom#SendUserBinaryMessage} 接口，才能收到此回调。
     */
    virtual void OnUserMessageSendResult(int64_t msgid, int error) {
        (void)msgid;
        (void)error;
    }

    /** 
     * @type callback
     * @region 实时消息通信
     * @brief 当调用 SendRoomMessage{@link #IRTCAudioRoom#SendRoomMessage} 函数发送消息后，回调此条消息的发送结果（反馈）。
     * @param [in] msgid  <br>
     *        本条消息的 ID
     * @param [in] error  <br>
     *        消息发送结果  <br>
     *        详见 RoomMessageSendResult{@link #RoomMessageSendResult}
     */
    virtual void OnRoomMessageSendResult(int64_t msgid, int error) {
        (void)msgid;
        (void)error;
    }

    /** 
     * @type callback
     * @region 音频事件回调
     * @brief 本地音频的状态发生改变时，该回调通知当前的本地音频状态。
     * @param [in] state 本地音频设备的状态，详见： LocalAudioStreamState{@link #LocalAudioStreamState}
     * @param [in] error 本地音频状态改变时的错误码，详见：LocalAudioStreamError{@link #LocalAudioStreamError}
     */
    virtual void OnLocalAudioStateChanged(LocalAudioStreamState state, LocalAudioStreamError error) {
        (void)state;
        (void)error;
    }

    /** 
     * @type callback
     * @region 音频事件回调
     * @brief 用户订阅来自远端的音频流状态发生改变时，会收到此回调，了解当前的远端音频流状态。
     * @param [in] key 远端流信息, 参看 RemoteStreamKey{@link #RemoteStreamKey}
     * @param [in] state 远端音频流状态，参看 RemoteAudioState{@link #RemoteAudioState}
     * @param [in] reason 远端音频流状态改变的原因，参看 RemoteAudioStateChangeReason{@link #RemoteAudioStateChangeReason}
     */
    virtual void OnRemoteAudioStateChanged(const RemoteStreamKey& key, RemoteAudioState state,
            RemoteAudioStateChangeReason reason) {
        (void)key;
        (void)state;
        (void)reason;
    }

    /** 
     * @type callback
     * @region 房间管理
     * @brief 音频首帧发送状态改变回调
     * @param [in] user 本地用户信息，详见 RtcUser{@link #RtcUser}
     * @param [in] state 首帧发送状态，详见 FirstFrameSendState{@link #FirstFrameSendState}
     */
    virtual void OnAudioFrameSendStateChanged(const RtcUser& user, FirstFrameSendState state) {
        (void)user;
        (void)state;
    }

    /** 
     * @type callback
     * @region 房间管理
     * @brief 音频首帧播放状态改变回调
     * @param [in] user 远端用户信息，详见 RtcUser{@link #RtcUser}
     * @param [in] state 首帧播放状态，详见 FirstFramePlayState{@link #FirstFramePlayState}
     */
    virtual void OnAudioFramePlayStateChanged(const RtcUser& user, FirstFramePlayState state) {
        (void)user;
        (void)state;
    }

    /** 
     * @type callback
     * @region 音频事件回调
     * @brief 通过调用服务端 MuteUser/UnmuteUser 方法禁用/解禁指定房间内指定用户音频流的发送时，触发此回调。
     * @param [in] uid 被禁用/解禁的音频流用户 ID
     * @param [in] banned 音频流发送状态 <br>
     *        + true: 音频流发送被禁用 <br>
     *        + false: 音频流发送被解禁
     * @notes  <br>
     *        + 房间内指定用户被禁止/解禁音频流发送时，房间内所有用户都会收到该回调。  <br>
     *        + 若被封禁用户退房后再进房，则依然是封禁状态，且房间内所有人会再次收到该回调。  <br>
     *        + 若被封禁用户断网后重连进房，则依然是封禁状态，且只有本人会再次收到该回调。  <br>
     *        + 指定用户被封禁后，房间内其他用户退房后再进房，会再次收到该回调。  <br>
     *        + 通话人数超过 5 人时，只有被封禁/解禁用户会收到该回调。   <br>
     *        + 同一房间解散后再次创建，房间内状态清空。
     */
    virtual void OnAudioStreamBanned(const char* uid, bool banned) {
        (void)uid;
        (void)banned;
    }

    /** 
     * @type callback
     * @region 多房间
     * @brief 跨房间音频流转发状态和错误回调
     * @param [in] infos 跨房间音频流转发目标房间信息数组，详见 ForwardStreamStateInfo{@link #ForwardStreamStateInfo}
     * @param [in] info_count 数组长度，代表目标房间数
     */
    virtual void OnForwardStreamStateChanged(ForwardStreamStateInfo* infos, int info_count) {
        (void)infos;
        (void)info_count;
    }

    /** 
     * @type callback
     * @region 多房间
     * @brief 跨房间音频流转发事件回调
     * @param [in] infos 跨房间音频流转发目标房间事件数组，详见 ForwardStreamEventInfo{@link #ForwardStreamEventInfo}
     * @param [in] info_count 数组长度，代表目标房间数
     */
    virtual void OnForwardStreamEvent(ForwardStreamEventInfo* infos, int info_count) {
        (void)infos;
        (void)info_count;
    }
};

}  // namespace bytertc

