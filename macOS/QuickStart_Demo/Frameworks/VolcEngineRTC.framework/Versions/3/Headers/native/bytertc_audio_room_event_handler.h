/*
 * Copyright (c) 2022 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC Room Event Handler Interface
*/

#pragma once

#include "rtc/bytertc_audio_defines.h"

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
     * @region 多房间
     * @brief 房间状态改变回调，加入房间、异常退出房间、发生房间相关的警告或错误时会收到此回调。
     * @param [in] room_id 房间 ID。
     * @param [in] uid 用户 ID。
     * @param [in] state 房间状态码。  <br>
     *              + 0: 加入房间成功。  <br>
     *              + !0: 加入房间失败、异常退房、发生房间相关的警告或错误。具体原因参看 ErrorCode{@link #ErrorCode} 及 WarningCode{@link #WarningCode}。
     * @param [in] extra_info 额外信息。
     *                  `join_type`表示加入房间的类型，`0`为首次进房，`1`为重连进房。
     *                  `elapsed`表示加入房间耗时，即本地用户从调用 joinRoom{@link #IRTCRoom#joinRoom} 到加入房间成功所经历的时间间隔，单位为 ms。
     */
    virtual void onRoomStateChanged(const char* room_id, const char* uid,
            int state, const char* extra_info) {
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
    virtual void onStreamStateChanged(const char* room_id, const char* uid,
            int state, const char* extra_info) {
        (void)room_id;
        (void)state;
        (void)extra_info;
    }

    /** 
     * @type callback
     * @region 房间管理
     * @brief 离开房间回调。  <br>
     *        用户调用 leaveRoom{@link #IRTCAudioRoom#leaveRoom} 方法后，SDK 会停止所有的发布订阅流，并在释放所有与通话相关的音频资源后，通过此回调通知用户离开房间成功。  <br>
     * @param [in] stats 保留参数，目前为空。
     * @notes  <br>
     *       + 用户调用 leaveRoom{@link #IRTCAudioRoom#leaveRoom} 方法离开房间后，若立即调用 destroyRTCAudio{@link #destroyRTCAudio} 方法销毁 RTC 引擎，则将无法收到此回调事件。  <br>
     *       + 离开房间后，如果 App 需要使用系统音频设备，则建议收到此回调后再初始化音频设备，否则可能由于 SDK 占用音频设备而导致初始化失败。  <br>
     */
    virtual void onLeaveRoom(const RtcRoomStats& stats) {
        (void)stats;
    }

    /** 
     * @type callback
     * @brief Token 进房权限过期前 30 秒将触发该回调。<br>
     *        收到该回调后，你需调用 updateToken{@link #IRTCAudioRoom#updateToken} 更新 Token 进房权限。
     * @notes 若 Token 进房权限过期且未及时更新： <br>
     *        + 用户此时尝试进房会收到 onRoomStateChanged{@link #IRTCAudioRoomEventHandler#onRoomStateChanged} 回调，提示错误码为 `-1000` Token 无效； <br>
     *        + 用户已在房间内则会被移出房间，本地用户会收到 onRoomStateChanged{@link #IRTCAudioRoomEventHandler#onRoomStateChanged} 回调，提示错误码为 `-1009` Token 过期，同时远端用户会收到 onUserLeave{@link #IRTCAudioRoomEventHandler#onUserLeave} 回调，提示原因为 `2` Token 进房权限过期。
     */
     virtual void onTokenWillExpire() {

    }
    /** 
     * @type callback
     * @brief Token 发布权限过期前 30 秒将触发该回调。<br>
     *        收到该回调后，你需调用 updateToken{@link #IRTCAudioRoom#updateToken} 更新 Token 发布权限。
     * @notes 若收到该回调后未及时更新 Token，Token 发布权限过期后： <br>
     *        + 此时尝试发布流会收到 onStreamStateChanged{@link #IRTCAudioRoomEventHandler#onStreamStateChanged} 回调，提示错误码为 `-1002` 没有发布权限； <br>
     *        + 已在发布中的流会停止发布，发布端会收到 onStreamStateChanged{@link #IRTCAudioRoomEventHandler#onStreamStateChanged} 回调，提示错误码为 `-1002` 没有发布权限，同时远端用户会收到 onUserUnPublishStream{@link #IRTCAudioRoomEventHandler#onUserUnPublishStream} 回调，提示原因为 `6` 发流端发布权限过期。
     */
    virtual void onPublishPrivilegeTokenWillExpire() {

    }
    /** 
     * @type callback
     * @brief Token 订阅权限过期前 30 秒将触发该回调。<br>
     *        收到该回调后，你需调用 updateToken{@link #IRTCAudioRoom#updateToken} 更新 Token 订阅权限有效期。
     * @notes 若收到该回调后未及时更新 Token，Token 订阅权限过期后，尝试新订阅流会失败，已订阅的流会取消订阅，并且会收到 onStreamStateChanged{@link #IRTCAudioRoomEventHandler#onStreamStateChanged} 回调，提示错误码为 `-1003` 没有订阅权限。
     */
    virtual void onSubscribePrivilegeTokenWillExpire() {

    }
    /** 
     * @type callback
     * @region 数据统计
     * @brief 房间内通话统计信息回调。   <br>
     *        用户进房开始通话后，每 2s 收到一次本回调。
     * @param [in] stats 当前 RtcEngine 统计数据，详见 RtcRoomStats{@link #RtcRoomStats}
     */
    virtual void onRoomStats(const RtcRoomStats& stats) {
        (void)stats;
    }

    /** 
     * @type callback
     * @region 数据统计
     * @brief 发布流成功后，每隔 2s 收到此回调，了解发布的流在此周期内的网络质量信息。
     * @param [in] stats 当前 RtcEngine 统计数据，详见 LocalStreamStats{@link #LocalStreamStats}
     */
    virtual void onLocalStreamStats(const LocalStreamStats& stats) {
        (void)stats;
    }
    /** 
     * @type callback
     * @region 数据统计
     * @brief 每隔 2s 收到此回调，了解订阅的远端用户发布的流在此周期内的网络质量信息。
     * @param [in] stats 当前 RtcEngine 统计数据，详见 RemoteStreamStats{@link #RemoteStreamStats}
     */
    virtual void onRemoteStreamStats(const RemoteStreamStats& stats) {
        (void)stats;
    }

    /** 
     * @type callback
     * @region 房间管理
     * @brief 远端可见用户加入房间，或房内隐身用户切换为可见的回调。<br>
     *        1. 远端用户调用 setUserVisibility{@link #IRTCAudioRoom#setUserVisibility} 方法将自身设为可见后加入房间时，房间内其他用户将收到该事件。  <br>
     *        2. 远端可见用户断网后重新连入房间时，房间内其他用户将收到该事件。  <br>
     *        3. 房间内隐身远端用户调用 setUserVisibility{@link #IRTCAudioRoom#setUserVisibility} 方法切换至可见时，房间内其他用户将收到该事件。  <br>
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
     *              + 0: 远端用户调用 leaveRoom{@link #IRTCAudioRoom#leaveRoom} 主动退出房间。  <br>
     *              + 1: 远端用户因 Token 过期或网络原因等掉线。详细信息请参看[连接状态提示](https://www.volcengine.com/docs/6348/95376) <br>
     *              + 2: 远端用户调用 setUserVisibility{@link #IRTCAudioRoom#setUserVisibility} 切换至不可见状态。 <br>
     *              + 3: 服务端调用 OpenAPI 将远端用户踢出房间。
     */
    virtual void onUserLeave(const char* uid, UserOfflineReason reason) {
        (void)uid;
        (void)reason;
    }
    /** 
     * @type callback
     * @region 房间管理
     * @brief 房间内新增远端音频流的回调。
     * @param [in] uid 远端流发布用户的用户 ID。
     * @notes 当房间内的远端用户调用 publishStream{@link #IRTCAudioRoom#publishStream} 成功发布音频流时，本地用户会收到该回调，此时本地用户可以自行选择是否调用 subscribeStream{@link #IRTCAudioRoom#subscribeStream} 订阅此流。
     */
    virtual void onUserPublishStream(const char* uid) {
        (void)uid;
    }
    /** 
     * @type callback
     * @region 房间管理
     * @brief 房间内远端音频流移除的回调。
     * @param [in] uid 移除的远端流发布用户的用户 ID。  <br>
     * @param [in] reason 远端流移除的原因，参看 StreamRemoveReason{@link #StreamRemoveReason}。
     * @notes 收到该回调通知后，你可以自行选择是否调用 unsubscribeStream{@link #IRTCAudioRoom#unsubscribeStream} 取消订阅此流。
     */
    virtual void onUserUnPublishStream(const char* uid, StreamRemoveReason reason) {
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
     * @notes 同一房间内其他用户调用 sendRoomMessage{@link #IRTCAudioRoom#sendRoomMessage} 发送广播消息时会收到该回调。
     */
    virtual void onRoomMessageReceived(const char* uid, const char* message) {
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
     * @notes 同一房间内其他用户调用 sendRoomBinaryMessage{@link #IRTCAudioRoom#sendRoomBinaryMessage} 发送二进制广播消息时会收到该回调。
     */
    virtual void onRoomBinaryMessageReceived(const char* uid, int size, const uint8_t* message) {
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
     *        + 你必须先调用 sendUserMessage{@link #IRTCAudioRoom#sendUserMessage} 方法，才能收到该回调。
     */
    virtual void onUserMessageReceived(const char* uid, const char* message) {
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
     *        + 同一房间内其他用户调用 sendUserBinaryMessage{@link #IRTCAudioRoom#sendUserBinaryMessage} 发送二进制消息给本地用户时，本地用户会收到该回调。
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
     *        + 你必须先调用 sendUserMessage{@link #IRTCAudioRoom#sendUserMessage} 或 sendUserBinaryMessage{@link #IRTCAudioRoom#sendUserBinaryMessage} 接口，才能收到此回调。
     */
    virtual void onUserMessageSendResult(int64_t msgid, int error) {
        (void)msgid;
        (void)error;
    }

    /** 
     * @type callback
     * @region 实时消息通信
     * @brief 当调用 sendRoomMessage{@link #IRTCAudioRoom#sendRoomMessage} 函数发送消息后，回调此条消息的发送结果（反馈）。
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
     * @brief 跨房间音频流转发状态和错误回调
     * @param [in] infos 跨房间音频流转发目标房间信息数组，详见 ForwardStreamStateInfo{@link #ForwardStreamStateInfo}
     * @param [in] info_count 数组长度，代表目标房间数
     */
    virtual void onForwardStreamStateChanged(ForwardStreamStateInfo* infos, int info_count) {
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
    virtual void onForwardStreamEvent(ForwardStreamEventInfo* infos, int info_count) {
        (void)infos;
        (void)info_count;
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
        (void)localQuality;
        (void)remoteQualities;
        (void)remoteQualityNum;
    }
};

}  // namespace bytertc

