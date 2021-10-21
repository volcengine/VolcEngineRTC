/*
 * Copyright (c) 2020 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngine Room Event Handler Interface
*/

#pragma once

#ifndef BYTE_RTC_ROOM_EVENT_HANDLER_INTERFACE_H__
#define BYTE_RTC_ROOM_EVENT_HANDLER_INTERFACE_H__

namespace bytertc {
/**
 * @type callback
 * @brief 音视频房间事件回调接口
 */
class IRTCRoomEventHandler {
public:

    /**
     * @hidden
     * @brief 析构函数
     */
    virtual ~IRTCRoomEventHandler() {
    }

    /**
     * @type callback
     * @region 房间管理
     * @author shenpengliang
     * @brief 首次加入房间/重连加入房间的回调。此回调表示用户调用 JoinRoom{@link #JoinRoom} 的结果，根据错误码判断成功/失败以及区别是否为重连。  <br>
     * @param [in] room_id 房间 ID。  <br>
     * @param [in] uid 用户 ID。  <br>
     * @param [in] error_code 用户加入房间回调的状态码，参看 ErrorCode{@link #ErrorCode} 以及 WarningCode{@link #WarningCode}。  <br>
     * @return  <br>
     *        + 0: 成功  <br>
     *        + <0: 失败  <br>
     * @param [in] join_type 用户加入房间的类型，标识用户第一次加入或断网重连加入。参看 JoinRoomType{@link #JoinRoomType}。  <br>
     * @param [in] elapsed  重连耗时。本地用户从连接断开到重连成功所经历的时间间隔，单位为 ms，加入房间失败为 -1  <br>
     */
    virtual void OnJoinRoomResult(
            const char* room_id, const char* uid, int error_code, JoinRoomType join_type, int elapsed) {
        (void)room_id;
        (void)error_code;
        (void)join_type;
        (void)elapsed;
    }

    /**
     * @type callback
     * @region 房间管理
     * @author shenpengliang
     * @brief 离开房间回调。  <br>
     *        用户调用 LeaveRoom{@link #LeaveRoom} 方法后，SDK 会停止所有的发布订阅流，并在释放所有与通话相关的音视频资源后，通过此回调通知用户离开房间成功。  <br>
     *        离开房间后，如果 App 需要使用系统音视频设备，则建议收到此回调后再初始化音视频设备，否则可能由于 SDK 占用音视频设备而导致初始化失败。  <br>
     * @param [in] stats 本次通话的统计数据，参看 RtcRoomStats{@link #RtcRoomStats} 。  <br>
     * @notes  <br>
     *       + 用户调用 LeaveRoom{@link #LeaveRoom} 方法离开房间后，若立即调用 DestroyRtcEngine{@link #DestroyRtcEngine} 方法销毁 RTC 引擎，则将无法收到此回调事件。  <br>
     */
    virtual void OnLeaveRoom(const RtcRoomStats& stats) {
        (void)stats;
    }

    /**
     * @type callback
     * @region 房间管理
     * @author shenpengliang
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
     * @author shenpengliang
     * @brief SDK 发生错误回调。  <br>
     *        SDK 内部遇到不可恢复错误时，会通过此回调通知 App，需要 App 根据错误码进行操作或提示用户。  <br>
     * @param [in] err 错误码，参看 ErrorCode{@link #ErrorCode}。  <br>
     */
    virtual void OnRoomError(int err) {
        (void)err;
    }

    /**
     * @type callback
     * @region 音频事件回调
     * @author wangjunzheng
     * @brief 提示房间内所有用户发送音量的回调。
     * @param [in] speakers 本地用户和订阅的远端用户的 ID 和音量。
     *                      参见：AudioVolumeInfo{@link #AudioVolumeInfo}。
     * @param [in] speaker_number speakers 数组长度。
     * @param [in] total_remote_volume speakers 中包含的所有音频音量之和，取值范围是：[0,255]
     * @notes
     *        + 对于本地用户：只要进行本地音频采集，回调内就会包含本地音频流的音量信息。<br>
     *        + 对于远端用户：本地必须订阅某远端用户的音频流，回调内才会包含其发送的音频流的音量信息。
     */
    virtual void OnAudioVolumeIndication(const AudioVolumeInfo* speakers, unsigned int speaker_number, int total_remote_volume) {
        (void)speakers;
        (void)speaker_number;
        (void)total_remote_volume;
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
     * @author liuzhiqiang.avcoder
     * @brief 反映通话中本地设备发送音/视频流的统计信息以及网络状况的回调，每 2s 触发一次。
     * @param [in] stats 当前 RtcEngine 统计数据，详见 LocalStreamStats{@link #LocalStreamStats}
     */
    virtual void OnLocalStreamStats(const LocalStreamStats& stats) {
        (void)stats;
    }
    /**
     * @type callback
     * @region 数据统计
     * @author liuzhiqiang.avcoder
     * @brief 通话中本地设备接收订阅的远端音/视频流的统计信息以及网络状况，每 2s 触发一次。
     * @param [in] stats 当前 RtcEngine 统计数据，详见 RemoteStreamStats{@link #RemoteStreamStats}
     */
    virtual void OnRemoteStreamStats(const RemoteStreamStats& stats) {
        (void)stats;
    }

    /**
     * @type callback
     * @region 房间管理
     * @author shenpengliang
     * @brief 远端主播角色用户加入房间回调。  <br>
     *        1.远端主播角色用户调用 JoinRoom{@link #JoinRoom} 方法加入房间时，房间内其他用户将收到该事件。  <br>
     *        2.远端主播角色用户断网后重新连入房间时，房间内其他用户将收到该事件。  <br>
     *        3.远端静默观众角色用户调用 SetUserRole{@link #SetUserRole} 方法将角色切换至主播时，房间内其他用户将收到该事件。  <br>
     *        4.新进房用户会收到进房前已在房内的主播角色用户的进房回调通知。  <br>
     * @param [in] user_info 用户信息，详见 UserInfo{@link #UserInfo}  <br>
     *                     + 已在房间中的用户会收到新进房的远端主播角色用户 ID 以及在房间内需要透传的信息；  <br>
     *                     + 新进房用户会收到已在房间中的远端主播角色用户 ID 以及在房间内需要透传的信息
     * @param [in] elapsed 此参数无意义
     */
    virtual void OnUserJoined(const UserInfo& user_info, int elapsed) {
        (void)user_info;
        (void)elapsed;
    }

    /**
     * @type callback
     * @region 房间管理
     * @author shenpengliang
     * @brief 远端主播角色用户离开房间回调。  <br>
     *        发生以下情形时，房间内其他用户会收到此事件：  <br>
     *        1.远端主播角色用户调用 LeaveRoom{@link #LeaveRoom} 方法离开房间时。  <br>
     *        2.远端主播角色用户调用 SetUserRole{@link #SetUserRole} 方法将角色切换至静默观众。  <br>
     *        3.远端主播角色用户断网，且一直未恢复。  <br>
     * @param [in] uid 离开房间的远端用户 ID。  <br>
     * @param [in] reason 用户离开房间的原因，参看 UserOfflineReason{@link #UserOfflineReason} 。  <br>
     */
    virtual void OnUserLeave(const char* uid, UserOfflineReason reason) {
        (void)uid;
        (void)reason;
    }

    /**
     * @type callback
     * @region 音频事件回调
     * @author wangjunzheng
     * @brief 当房间内用户调用 MuteAllRemoteAudio{@link #IRtcRoom#MuteAllRemoteAudio}，
     *        改变接收所有远端音频流的状态时, 房间内其他用户收到这个回调。
     * @param [in] user_id 改变接收状态的用户 ID
     * @param [in] mute_state 接收状态，详见：MuteState{@link #MuteState}
     */
    virtual void OnMuteAllRemoteAudio(const char* user_id, MuteState mute_state) {
        (void)user_id;
        (void)mute_state;
    }


    /**
     * @type callback
     * @region 视频管理
     * @brief 房间内用户暂停/恢复接收所有视频流时，房间内其他用户收到此回调。参看 MuteAllRemoteVideo{@link #MuteAllRemoteVideo}。
     * @param [in] uid 暂停/恢复接收视频流的用户 ID。
     * @param  [in] mute 暂停/恢复接收视频流的状态。参看 MuteState{@link #MuteState}。
     */
    virtual void OnMuteAllRemoteVideo(const char* uid, MuteState mute) {
        (void)uid;
        (void)mute;
    }


    /**
     * @type callback
     * @region 音频事件回调
     * @author wangjunzheng
     * @brief 房间内某用户调用 MuteLocalAudio{@link #MuteLocalAudio}
     *        改变本地音频发送状态时，房间内其他用户会收到此回调。
     * @param [in] user_id 改变本地音频发送状态的用户 ID
     * @param [in] mute_state 发送状态，参看 MuteState{@link #MuteState}
     */
    virtual void OnUserMuteAudio(const char* user_id, MuteState mute_state) {
        (void)user_id;
        (void)mute_state;
    }


    /**
     * @deprecated
     * @type callback
     * @region 音频事件回调
     * @author wangjunzheng
     * @brief 远端用户开启/关闭音频设备采集时，房间内其他人会收到这个回调。
     *        该回调由远端用户调用 StartAudioCapture{@link #IRtcEngineLite#StartAudioCapture} 方法触发。
     * @param [in] uid 远端用户ID
     * @param [in] enabled 该用户是否开启了音频设备采集  <br>
     *       + true: 该用户开启了音频设备采集  <br>
     *       + false: 该用户关闭了音频设备采集  <br>
     *       + 该接口已废弃，请使用 OnUserStartAudioCapture{@link #OnUserStartAudioCapture} 以及 OnUserStopAudioCapture{@link #OnUserStopAudioCapture} <br>
     */
    virtual void OnUserEnableLocalAudio(const char* uid, bool enabled) {
        (void)uid;
        (void)enabled;
    }

    /**
     * @type callback
     * @region 音频事件回调
     * @author wangjunzheng
     * @brief 房间内的用户调用 StartAudioCapture{@link #StartAudioCapture} 开启音频采集时，房间内其他用户会收到此回调。
     * @param [in] user_id 开启音频采集的远端用户 ID
     */
    virtual void OnUserStartAudioCapture(const char* user_id) {
        (void)user_id;
    }

    /**
     * @type callback
     * @region 音频事件回调
     * @author wangjunzheng
     * @brief 房间内的用户调用 StopAudioCapture{@link #StopAudioCapture} 关闭音频采集时，房间内其他用户会收到此回调。
     * @param [in] user_id 关闭音频采集的远端用户 ID
     */
    virtual void OnUserStopAudioCapture(const char* user_id) {
        (void)user_id;
    }

    /**
     * @type callback
     * @region 音频事件回调
     * @author wangjunzheng
     * @brief 本地采集到第一帧音频帧时，收到该回调
     * @param [in] index 音频流属性, 参看 StreamIndex{@link #StreamIndex}
     */
    virtual void OnFirstLocalAudioFrame(StreamIndex index) {
        (void)index;
    }


    /**
     * @type callback
     * @region 音频事件回调
     * @author wangjunzheng
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
     * @author shenpengliang
     * @brief 房间内的远端用户停止发布音视频流时，本地用户会收到此回调。
     * @param [in] stream 流的属性。参看 MediaStreamInfo{@link #MediaStreamInfo} 。
     * @param [in] reason 远端流移除的原因。参看 StreamRemoveReason{@link #StreamRemoveReason} 。
     */
    virtual void OnStreamRemove(const MediaStreamInfo& stream, StreamRemoveReason reason) {
        (void)stream;
    }


    /**
     * @type callback
     * @region 房间管理
     * @author shenpengliang
     * @brief 房间内的用户发布新的音视频流时，房间内的其他用户会收到此回调。包括移除后又重新发布的流。  <br>
     * @param [in] stream 流属性，参看 MediaStreamInfo{@link #MediaStreamInfo} 。  <br>
     */
    virtual void OnStreamAdd(const MediaStreamInfo& stream) {
        (void)stream;
    }


    /**
     * @hidden
     * @type callback
     * @region 房间管理
     * @author shenpengliang
     * @brief 当订阅一个流成功的时候回调该事件
     *        当成功更新流的内容时，如增加或者减少音视频流时，也会回调该事件。
     * @param [in] state_code 订阅流的结果。参看 SubscribeState{@link #SubscribeState}。  <br>
     * @param [in] user_id 用户 ID。
     * @param [in] info 订阅流的参数配置。参看 SubscribeConfig{@link #SubscribeConfig}。  <br>
     */
    virtual void OnStreamSubscribed(SubscribeState state_code, const char* user_id, const SubscribeConfig& info) {
        (void)state_code;
        (void)user_id;
        (void)info;
    }

    /**
     * @type callback
     * @region 音视频回退
     * @author panjian.fishing
     * @brief 因发布/订阅性能回退或退出回退状态，订阅的音视频流，发生流的切换时，收到该回调。
     * @param [in] event 流切换信息。详见 RemoteStreamSwitch{@link #RemoteStreamSwitch}。
     * @notes  <br>
     *        + 你必须先通过 API 或控制台设置音视频流订阅回退功能时，你才能收到此回调。
     */
    virtual void OnSimulcastSubscribeFallback(const RemoteStreamSwitch& event) {
        (void)event;
    }

    /**
     * @hidden
     * @type callback
     * @region 房间管理
     * @author shenpengliang
     * @brief 当发布流成功的时候回调该事件。
     * @param [in] user_id 发布流的用户 ID。
     * @param [in] is_screen 该流是否为屏幕流。  <br>
     *             + Ture: 屏幕流；  <br>
     *             + False: 非屏幕流。  <br>
     */
    virtual void OnStreamPublishSuccess(const char* user_id, bool is_screen) {
        (void)is_screen;
    }

    /**
     * @type callback
     * @region 流消息
     * @brief 接收到房间内广播消息的回调。
     * @param [in] uid 消息发送者 ID
     * @param [in] message 收到的消息内容
     * @notes
     *        1.同一房间内其他用户调用 SendRoomMessage{@link #IRtcRoom#SendRoomMessage} 发送广播消息时会收到该回调。
     */
    virtual void OnRoomMessageReceived(const char* uid, const char* message) {
        (void)uid;
        (void)message;
    }

    /**
     * @hidden
     * @type callback
     * @region 房间管理
     * @brief 直播推流转码错误回调。
     *        用户调用 EnableLiveTranscoding{@link #EnableLiveTranscoding}
     * 接口启动直播推流转码功能后，启动结果和推流过程中 的错误均会通过此回调方法通知用户。
     * @param [in] url
     *        推流地址的 URL。
     * @param [in] error
     *        直播推流转码功能错误码，详见枚举类型 TransCodingError{@link #TransCodingError}。
     */
    virtual void OnLiveTranscodingResult(const char* url, int error) {
        (void)url;
        (void)error;
    }

    /**
     * @type callback
     * @region 流消息
     * @brief 接收到房间内二进制广播消息的回调。
     * @param [in] uid 消息发送者 ID
     * @param [in] size 收到的二进制消息长度
     * @param [in] message 收到的二进制消息内容
     * @notes
     *        1.同一房间内其他用户调用 SendRoomBinaryMessage{@link #IRtcRoom#SendRoomBinaryMessage} 发送二进制广播消息时会收到该回调。
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
     *        + 你必须先调用 SendUserMessage{@link #SendUserMessage} 方法，才能收到该回调。
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
     *        + 同一房间内其他用户调用 SendUserBinaryMessage{@link #SendUserBinaryMessage} 发送二进制消息给本地用户时，本地用户会收到该回调。
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
     *        + 你必须先调用 SendUserMessage{@link #SendUserMessage} 或 SendUserBinaryMessage{@link #SendUserBinaryMessage} 接口，才能收到此回调。
     */
    virtual void OnUserMessageSendResult(int64_t msgid, int error) {
        (void)msgid;
        (void)error;
    }

    /**
     * @type callback
     * @region 流消息
     * @brief 当调用 SendRoomMessage{@link #IRtcRoom#SendRoomMessage} 函数发送消息后，回调此条消息的发送结果（反馈）。
     * @param [in] msgid 本条消息的 ID
     * @param [in] error 消息发送结果，详见 RoomMessageSendResult{@link #RoomMessageSendResult}
     */
    virtual void OnRoomMessageSendResult(int64_t msgid, int error) {
        (void)msgid;
        (void)error;
    }

#ifndef ByteRTC_AUDIO_ONLY
    /**
     * @type callback
     * @region 视频管理
     * @brief 第一帧本地采集的视频/屏幕共享画面在本地视图渲染完成时，收到此回调。
     * @param [in] index 流属性。参看 StreamIndex{@link #StreamIndex}。
     * @param [in] info 视频信息。参看 VideoFrameInfo{@link #VideoFrameInfo}。
     */
    virtual void OnFirstLocalVideoFrameCaptured(StreamIndex index, VideoFrameInfo info) {
        (void)index;
        (void)info;
    }


    /**
     * @type callback
     * @region 视频管理
     * @brief 本地视频大小或旋转配置发生改变时，收到此回调。
     * @param [in] index 流属性。参看 StreamIndex{@link #StreamIndex}。
     * @param [in] info 视频帧信息。参看 VideoFrameInfo{@link #VideoFrameInfo}。
     */
    virtual void OnLocalVideoSizeChanged(StreamIndex index, const VideoFrameInfo& info) {
        (void)index;
        (void)info;
    }


    /**
     * @type callback
     * @region 视频管理
     * @brief 远端视频大小或旋转配置发生改变时，房间内订阅此视频流的用户会收到此回调。
     * @param [in] key 远端流信息。参看 RemoteStreamKey{@link #RemoteStreamKey}。
     * @param [in] info 视频帧信息。参看 VideoFrameInfo{@link #VideoFrameInfo}。
     */
    virtual void OnRemoteVideoSizeChanged(RemoteStreamKey key, const VideoFrameInfo& info) {
        (void)key;
        (void)info;
    }


    /**
     * @type callback
     * @region 视频管理
     * @brief 第一帧远端视频流在视图上渲染成功后，收到此回调。
     * @param [in] key 远端流信息。参看 RemoteStreamKey{@link #RemoteStreamKey}。
     * @param [in] info 视频帧信息。参看 VideoFrameInfo{@link #VideoFrameInfo}。
     */
    virtual void OnFirstRemoteVideoFrameRendered(const RemoteStreamKey key, const VideoFrameInfo& info) {
        (void)key;
        (void)info;
    }


    /**
     * @type callback
     * @region 视频管理
     * @brief 房间内用户暂停/恢复发送视频流时，房间内其他用户会收到此回调。参看 MuteLocalVideo{@link #MuteLocalVideo}。
     * @param [in] uid 暂停/恢复发送视频流的用户 ID。
     * @param  [in] mute 暂停/恢复发送视频流的状态。参看 MuteState{@link #MuteState}。
     */
    virtual void OnUserMuteVideo(const char* uid, MuteState mute) {
        (void)uid;
        (void)mute;
    }


    /**
     * @deprecated
     * @type callback
     * @region 视频管理
     * @brief 远端用户开启/关闭本地视频采集时回调该事件，当远端用户调用 EnableLocalVideo 时，其他用户会触发此回调。
     * @param [in] uid 用户ID，提示是哪个用户的视频流。
     * @param  [in] enabled 是否启用本地视频功能。  <br>
     *       + true：该用户已启用本地视频功能。启用后，其他用户可以接收到该用户的视频流。  <br>
     *       + false：该用户已关闭视频功能。关闭后，该用户仍然可以接收其他用户的视频流，但其他用户接收不到该用户的视频流。  <br>
     * @notes 提示有其他用户启用/关闭了本地视频功能。
     *       + 该接口已废弃，请使用 OnUserStartVideoCapture{@link #OnUserStartVideoCapture} 以及 OnUserStopVideoCapture{@link #OnUserStopVideoCapture} <br>
     */
    virtual void OnUserEnableLocalVideo(const char* uid, bool enabled) {
        (void)uid;
        (void)enabled;
    }

    /**
     * @type callback
     * @region 视频事件回调
     * @author liyi.000
     * @brief 房间内的用户调用 StartVideoCapture{@link #StartVideoCapture} 开启视频采集时，房间内其他用户会收到此回调。
     * @param [in] user_id 开启视频采集的远端用户 ID
     */
    virtual void OnUserStartVideoCapture(const char* user_id) {
        (void)user_id;
    }

    /**
     * @type callback
     * @region 视频事件回调
     * @author liyi.000
     * @brief 房间内的用户调用 StopVideoCapture{@link #StopVideoCapture} 关闭视频采集时，房间内其他用户会收到此回调。
     * @param [in] user_id 关闭视频采集的远端用户ID
     */
    virtual void OnUserStopVideoCapture(const char* user_id) {
        (void)user_id;
    }

    /**
     * @type callback
     * @region 音频事件回调
     * @author wangjunzheng
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
     * @author wangjunzheng
     * @brief 用户订阅来自远端的音频流状态发生改变时，会收到此回调，了解当前的远端音频流状态。
     * @param [in] key 远端流信息, 参看 RemoteStreamKey{@link #RemoteStreamKey}
     * @param [in] state 远端音频流状态，参看 RemoteAudioState{@link #RemoteAudioState}
     * @param [in] reason 远端音频流状态改变的原因，参看 RemoteAudioStateChangeReason{@link #RemoteAudioStateChangeReason}
     */
    virtual void OnRemoteAudioStateChanged(
            const RemoteStreamKey& key, RemoteAudioState state, RemoteAudioStateChangeReason reason) {
        (void)key;
        (void)state;
        (void)reason;
    }

    /**
     * @type callback
     * @region 视频管理
     * @brief 本地视频流的状态发生改变时，收到该事件。
     * @param [in] index 音/视频属性，参看 StreamIndex{@link #StreamIndex}
     * @param [in] state 本地视频流状态，参看 LocalVideoStreamState{@link #LocalVideoStreamState}
     * @param [in] error 本地视频状态改变时的错误码，参看 LocalVideoStreamError{@link #LocalVideoStreamError}
     */
    virtual void OnLocalVideoStateChanged(StreamIndex index, LocalVideoStreamState state, LocalVideoStreamError error) {
        (void)index;
        (void)state;
        (void)error;
    }


    /**
     * @type callback
     * @region 视频管理
     * @brief 远端视频流的状态发生改变时，房间内订阅此流的用户会收到该事件。
     * @param [in] key 远端视频流的信息，房间、用户 ID、流属性等。参看 RemoteStreamKey{@link #RemoteStreamKey}。
     * @param [in] state 远端视频流状态，参看 RemoteVideoState{@link #RemoteVideoState}。
     * @param [in] reason 远端视频流状态改变的原因，参看 RemoteVideoStateChangeReason{@link #RemoteVideoStateChangeReason}。
     */
    virtual void OnRemoteVideoStateChanged(
            RemoteStreamKey key, RemoteVideoState state, RemoteVideoStateChangeReason reason) {
        (void)key;
        (void)state;
        (void)reason;
    }


    /**
     * @hidden
     * @type callback
     * @region 视频管理
     * @brief 当订阅远端用户的时候触发此回调
     * @param [in] user_id 远端用户的 ID
     * @param [in] is_reconnect 是否为重连
     */
    virtual void OnSubscribe(const char* user_id, bool is_reconnect) {
        (void)user_id;
        (void)is_reconnect;
    }

    /**
     * @hidden
     * @type callback
     * @region 视频管理
     * @brief 当取消订阅远端用户的时候触发此回调
     * @param [in] user_id 远端用户的 ID
     * @param [in] is_reconnect 是否为重连
     */
    virtual void OnUnSubscribe(const char* user_id, bool is_reconnect) {
        (void)user_id;
        (void)is_reconnect;
    }

    /**
     * @type callback
     * @region 房间管理
     * @author shenpengliang
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
     * @author shenpengliang
     * @brief 视频首帧发送状态改变回调
     * @param [in] user 本地用户信息，详见 RtcUser{@link #RtcUser}
     * @param [in] state 首帧发送状态，详见 FirstFrameSendState{@link #FirstFrameSendState}
     */
    virtual void OnVideoFrameSendStateChanged(const RtcUser& user, FirstFrameSendState state) {
        (void)user;
        (void)state;
    }

    /**
     * @type callback
     * @region 房间管理
     * @author shenpengliang
     * @brief 屏幕共享流视频首帧发送状态改变回调
     * @param [in] user 本地用户信息，详见 RtcUser{@link #RtcUser}
     * @param [in] state 首帧发送状态，详见 FirstFrameSendState{@link #FirstFrameSendState}
     */
    virtual void OnScreenVideoFrameSendStateChanged(const RtcUser& user, FirstFrameSendState state) {
        (void)user;
        (void)state;
    }

    /**
     * @type callback
     * @region 房间管理
     * @author shenpengliang
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
     * @region 房间管理
     * @author shenpengliang
     * @brief 视频首帧播放状态改变回调
     * @param [in] user 远端用户信息，详见 RtcUser{@link #RtcUser}
     * @param [in] state 首帧播放状态，详见 FirstFramePlayState{@link #FirstFramePlayState}
     */
    virtual void OnVideoFramePlayStateChanged(const RtcUser& user, FirstFramePlayState state) {
        (void)user;
        (void)state;
    }

    /**
     * @type callback
     * @region 房间管理
     * @author shenpengliang
     * @brief 屏幕共享流视频首帧播放状态改变回调
     * @param [in] user 远端用户信息，详见 RtcUser{@link #RtcUser}
     * @param [in] state 首帧播放状态，详见 FirstFramePlayState{@link #FirstFramePlayState}
     */
    virtual void OnScreenVideoFramePlayStateChanged(const RtcUser& user, FirstFramePlayState state) {
        (void)user;
        (void)state;
    }

#endif  // ByteRTC_AUDIO_ONLY
};

} // namespace bytertc

#endif // BYTE_RTC_ROOM_EVENT_HANDLER_INTERFACE_H__
