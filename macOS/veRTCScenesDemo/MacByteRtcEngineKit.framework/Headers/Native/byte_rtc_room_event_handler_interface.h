//
//  byte_rtc_room_event_handler_interface.h
//  bytertc
//
//  Created by xiewei on 2020/6/22.
//

#pragma once
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
     * @hidden
     * @type callback
     * @region 房间管理
     * @brief 加入房间成功时返回当前房间内正在发布的流
     * @param [in] error_code 状态码，0:成功，其它:失败
     * @param [in] list_streams 房间流列表
     * @param [in] stream_number 流数目
     */
    virtual void OnLoginCompletion(int error_code, const ByteStream* list_streams, int stream_number) {
        (void)error_code;
        (void)list_streams;
        (void)stream_number;
    }

    /**
     * @type callback
     * @region 房间管理
     * @brief 加入房间成功回调。此回调事件表示本地用户成功加入了指定的房间。  <br>
     *        用户调用 JoinChannel{@link #JoinChannel} 方法加入房间，首次加入房间成功后 SDK 通过此回调事件通知用户加入房间成功。此回调事件在用户调用 JoinChannel{@link #JoinChannel} 方法加入房间到用户调用 LeaveChannel{@link #LeaveChannel} 方法离开房间期间至多回调一次。  <br>
     * @param [in] room_id 房间ID 。本地用户加入的房间的房间 ID 。  <br>
     * @param [in] uid 用户ID 。本地用户的用户ID 。  <br>
     * @param [in] elapsed 加入房间耗时。本地用户从调用 JoinChannel{@link #JoinChannel} 方法到加入房间成功所经历的时间间隔，单位为 ms 。  <br>
     */
    virtual void OnJoinChannelSuccess(const char* room_id, const char* uid, int elapsed) {
        (void)room_id;
        (void)uid;
        (void)elapsed;
    }

    /**
     * @type callback
     * @region 房间管理
     * @brief 重新加入房间成功回调。此回调事件表示本地用户成功重连入房间。  <br>
     *        本地用户加入房间成功后，在本地网络状况不佳的情况下，SDK 可能会与服务器失去连接。此时 SDK 将会自动重连，并在重连成功通过此回调事件通知用户重连成功。  <br>
     * @param [in] room_id 房间 ID 。本地用户加入的房间的房间 ID 。  <br>
     * @param [in] uid 用户ID 。本地用户的用户ID 。  <br>
     * @param [in] elapsed  重连耗时。本地用户从连接断开到重连成功所经历的时间间隔，单位为 ms 。  <br>
     */
    virtual void OnRejoinChannelSuccess(const char* room_id, const char* uid, int elapsed) {
        (void)room_id;
        (void)uid;
        (void)elapsed;
    }

    /**
     * @type callback
     * @region 房间管理
     * @brief 离开房间成功回调。  <br>
     *        用户调用 LeaveChannel{@link #LeaveChannel} 方法后，SDK 会停止所有的发布订阅流，并释放所有通话相关的音视频资源。SDK 完成所有的资源释放后通过此回调通知用户。  <br>
     *        离开房间结束通话后，如果 App 需要使用系统音视频设备，则建议在收到此回调后再初始化音视频设备，否则可能由于 SDK 占用了导致 App 初始化音视频设备失败。  <br>
     * @param [in] stats 本次通话的统计数据，详见数据结构 RtcStats{@link #RtcStats} 。  <br>
     * @notes  <br>
     *       + 用户调用 LeaveChannel{@link #LeaveChannel} 方法离开房间后，如果立即调用 DestroyByteRtcEngine{@link #DestroyByteRtcEngine} 方法销毁 RTC 引擎，则将无法收到此回调事件。  <br>
     */
    virtual void OnLeaveChannel(const RtcStats& stats) {
        (void)stats;
    }

    /**
     * @type callback
     * @region 房间管理
     * @brief SDK 发生警告回调。  <br>
     *        SDK 内部遇到可恢复错误时，在尝试自动恢复的同时，会通过此回调通知用户。此回调事件仅用做通知。  <br>
     * @param [in] warn 警告码，详见枚举类型 RTC_WARN_CODE{@link #RTC_WARN_CODE} 。  <br>
     */
    virtual void OnChannelWarning(int warn) {
        (void)warn;
    }

    /**
     * @type callback
     * @region 房间管理
     * @brief SDK 发生错误回调。  <br>
     *        SDK 内部遇到不可恢复错误时，会通过此回调通知 App，需要 App 根据错误码进行操作或提示用户。  <br>
     * @param [in] err 错误码，详见枚举类型 RTC_ERROR_CODE{@link #RTC_ERROR_CODE} 。  <br>
     */
    virtual void OnChannelError(int err) {
        (void)err;
    }

    /**
     * @type callback
     * @region 音频管理
     * @brief 当收到音频质量信息的时候回调该事件
     * @param [in] uid
     *        对端用户标识
     * @param [in] quality
     *        该用户音频质量
     * @param [in] delay
     *        音频包到达的平均延迟
     * @param [in] lost
     *        该用户的音频丢包率
     */
    virtual void OnAudioQuality(const char* uid, int quality, unsigned short delay, unsigned short lost) {
        (void)uid;
        (void)quality;
        (void)delay;
        (void)lost;
    }

    /**
     * @type callback
     * @region 音频事件回调
     * @brief 提示房间内所有用户发送音量的回调。
     * @param [in] speakers
     *        房间内所有用户 ID, 以及对应的发送音量。参见：AudioVolumeInfo{@link #AudioVolumeInfo}。
     * @param [in] speaker_number 房间内用户数量
     * @param [in] total_remote_volume 房间内所有音频流的总音量，取值范围是：[0,255]
     * @notes 本回调默认不开启。你可以通过调用 SetAudioVolumeIndicationInterval{@link #IRtcRoom#SetAudioVolumeIndicationInterval} 开启。  <br>
     */
    virtual void OnAudioVolumeIndication(const AudioVolumeInfo* speakers, unsigned int speaker_number, int total_remote_volume) {
        (void)speakers;
        (void)speaker_number;
        (void)total_remote_volume;
    }

    /**
     * @type callback
     * @region 视频管理
     * @brief 用户加入房间成功后，每 2s 会收到一次房间内统计信息的回调。
     * @param [in] stats 当前 RtcEngine 统计数据，详见：RtcStats{@link #RtcStats}
     */
    virtual void OnRtcStats(const RtcStats& stats) {
        (void)stats;
    }

    /**
     * @type callback
     * @region 引擎管理
     * @brief 通话中用户的媒体流网络上下行质量报告回调。加入房间成功后，每隔 2 秒会触发此回调，通知房间内用户与媒体服务器之间数据交互的网络质量。
     * @param [in] uid  <br>
     *        回调的网络质量报告所属用户的用户 ID 。
     * @param [in] tx_quality  <br>
     *        uid 所属用户的媒体流上行网络质量。
     * @param [in] rx_quality  <br>
     *        uid 所属用户的媒体流下行网络质量。
     * @notes  <br>
     *        + 当 uid 为本地用户 ID 时，tx_quality 为该用户的上行网络质量，rx_quality 为该用户的下行网络质量。  <br>
     *        + 当 uid 为远端用户 ID 时，目前仅支持获取该用户的上行网络质量 tx_quality ，下行网络质量 rx_quality 为 kNetworkQualityUnknown 。  <br>
     *        + NetworkQuality 的定义详见：{@link #NetworkQuality} 。
     */
    virtual void OnNetworkQuality(const char* uid, NetworkQuality tx_quality, NetworkQuality rx_quality) {
        (void)uid;
        (void)tx_quality;
        (void)rx_quality;
    }

    /**
     * @type callback
     * @region 房间管理
     * @brief 远端用户加入房间回调。  <br>
     *        此回调用于提示房间中有新用户加入。如果本地用户已经在房间中，有新的远端用户加入时，SDK 通过此回调方法通知房间中有新用户加入；如果用户加入房间前，房间中已有其他用户，加入房间后用户也会收到这些已在房间中的远端用户的加入房间回调。  <br>
     *        回调的具体触发时机如下：  <br>
     *        1.远端的房间模式为通信模式的用户或房间模式为其他模式的主播、观众角色的用户，调用 JoinChannel{@link #JoinChannel} 方法加入房间。  <br>
     *        2.远端的房间模式为通信模式的用户或房间模式为其他模式的主播、观众角色的用户，在断网后重连入房间。  <br>
     *        3.远端已在房间中的房间模式为直播、游戏或云游戏模式的静默观众角色的用户，调用 SetClientRole{@link #SetClientRole} 方法将用户角色切换至主播或观众。  <br>
     *        4.本地用户加入房间时，会收到已在房间中的远端的房间模式为通信模式的用户或房间模式为其他模式的主播、观众角色的用户的加入房间回调。  <br>
     * @param [in] uid 用户ID 。新加入的远端用户的用户ID 。  <br>
     * @param [in] team_id 预留参数。  <br>
     * @param [in] send_mode 预留参数。  <br>
     * @param [in] elapsed 本地用户调用 JoinChannel{@link #JoinChannel} 加入房间到收到该事件经历的时间，单位为 ms 。  <br>
     */
    virtual void OnUserJoined(const char* uid, const char* team_id, const RangeAudioMode send_mode, int elapsed) {
        (void)uid;
        (void)team_id;
        (void)send_mode;
        (void)elapsed;
    }

    /**
     * @type callback
     * @region 房间管理
     * @brief 远端用户离开房间回调。  <br>
     *        此回调用于提示房间中有远端用户离开。用户离开房间的原因有两个，即用户主动调用 LeaveChannel{@link #LeaveChannel} 方法离开房间和超时掉线。  <br>
     *        回调的具体触发时机如下：  <br>
     *        1.远端的房间模式为通信模式的用户或房间模式为其他模式的主播、观众角色的用户，调用 LeaveChannel{@link #LeaveChannel} 方法离开房间。用户离开的原因为 USER_OFFLINE_QUIT{@link #USER_OFFLINE_QUIT}。  <br>
     *        2.远端已在房间中的房间模式为直播、游戏或云游戏模式的主播、观众角色的用户调用 SetClientRole{@link #SetClientRole} 方法将用户角色切换至静默观众。用户离开的原因为 USER_OFFLINE_QUIT{@link #USER_OFFLINE_QUIT}。  <br>
     *        3.远端的房间模式为通信模式的用户或房间模式为其他模式的主播、观众角色的用户，断网且一直未恢复。用户离开的原因为 USER_OFFLINE_DROPPED{@link #USER_OFFLINE_DROPPED}。  <br>
     * @param [in] uid 用户ID 。离开房间的远端用户的用户ID 。  <br>
     * @param [in] reason 用户离开的原因，详见枚举类型 USER_OFFLINE_REASON_TYPE{@link #USER_OFFLINE_REASON_TYPE} 。  <br>
     */
    virtual void OnUserOffline(const char* uid, USER_OFFLINE_REASON_TYPE reason) {
        (void)uid;
        (void)reason;
    }

    /**
     * @hidden
     * @type callback
     * @region 游戏接口
     * @brief 游戏场景中，当房间用户的的 sendmode 被修改的时候回调该事件，发送模式只有三种，分别是：静音、向小队发送、向世界发送。
     * @param [in] uid  <br>
     *        远端用户 id 。
     * @param [in] range_audio_mode  <br>
     *        远端用户的发送模式，详见: RangeAudioMode{@link #RangeAudioMode} 。
     */
    virtual void OnUserAudioSendModeChange(const char* uid, RangeAudioMode range_audio_mode) {
        (void)uid;
        (void)range_audio_mode;
    }

    /**
     * @hidden
     * @type callback
     * @region 游戏接口
     *@brief 游戏场景中，当房间用户的的 recvmode 被修改的时候回调该事件，收听模式只有三种，分别是：静音、收听小队、收听世界。
     *@param [in] uid  <br>
     *       远端用户 id 。
     *@param [in] range_audio_mode  <br>
     *       远端用户的接收模式，详见: RangeAudioMode{@link #RangeAudioMode} 。
     */
    virtual void OnUserAudioRecvModeChange(const char* uid, RangeAudioMode range_audio_mode) {
        (void)uid;
        (void)range_audio_mode;
    }

    /**
     * @type callback
     * @region 音频事件回调
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
     * @param  [in] mute 暂停/恢复接收视频流。参看 MuteState{@link #MuteState}。
     */
    virtual void OnMuteAllRemoteVideo(const char* uid, MuteState mute) {
        (void)uid;
        (void)mute;
    }

    /**
     * @type callback
     * @region 音频事件回调
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
     * @type callback
     * @region 音频事件回调
     * @brief 远端用户开启/关闭音频设备采集时，房间内其他人会收到这个回调。
     *        该回调由远端用户调用 EnableLocalAudio{@link #IRtcEngineLite#EnableLocalAudio} 方法触发。
     * @param [in] uid 远端用户ID
     * @param [in] enabled 该用户是否开启了音频设备采集  <br>
     *       + true: 该用户开启了音频设备采集  <br>
     *       + false: 该用户关闭了音频设备采集  <br>
     */
    virtual void OnUserEnableLocalAudio(const char* uid, bool enabled) {
        (void)uid;
        (void)enabled;
    }

    /**
     * @type callback
     * @region 数据统计
     * @brief 通话中本地音频流的统计信息回调。
     *        该回调描述本地设备发送音频流的统计信息，每 2 秒触发一次。
     * @param [in] stats 本地音频统计数据，详细定义见：LocalAudioStats{@link #LocalAudioStats}
     */
    virtual void OnLocalAudioStats(const LocalAudioStats& stats) {
        (void)stats;
    }

    /**
     * @region 数据统计
     * @brief 通话中远端音频流的统计信息回调。
     *        该回调描述远端用户在通话中端到端的音频流状态，针对每个远端用户/主播每 2 秒触发一次。如果远端同时存在多个用户/主播，该回调每 2 秒会被触发多次。
     * @param [in] stats 远端音频统计数据，详细定义见：RemoteAudioStats{@link #RemoteAudioStats}
     */
    virtual void OnRemoteAudioStats(const RemoteAudioStats& stats) {
        (void)stats;
    }

    /**
     * @type callback
     * @region 音频事件回调
     * @brief 本地采集到第一帧音频帧时，收到该回调
     * @param [in] index 音频流属性, 参看 StreamIndex{@link #StreamIndex}
     */
    virtual void OnFirstLocalAudioFrame(StreamIndex index) {
        (void)index;
    }


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
     * @brief 房间内的远端用户停止发布音视频流时，本地用户会收到此回调。
     * @param [in] stream 流的属性。参看 ByteStream{@link #ByteStream} 。
     * @param [in] reason 远端流移除的原因。参看 RtcStreamRemoveReason{@link #RtcStreamRemoveReason} 。
     */
    virtual void OnStreamRemove(const ByteStream& stream, RtcStreamRemoveReason reason) {
        (void)stream;
    }

    /**
     * @type callback
     * @region 房间管理
     * @brief 用户加入房间时，会收到此回调，包含房间中所有已发布的流。 <br>
     *        房间内的用户发布新的音视频流时，房间内的其他用户会收到此回调。  <br>
     * @param [in] stream 流属性，参看 ByteStream{@link #ByteStream} 。  <br>
     */
    virtual void OnStreamAdd(const ByteStream& stream) {
        (void)stream;
    }

    /**
     * @hidden
     * @type callback
     * @region 房间管理
     * @brief 当订阅一个流成功的时候回调该事件
     *       当更新流的内容时比如增加或者减少音视频流成功更新时也会回调该事件
     * @param [in] state_code
     *       订阅流的结果，详见：{@link #SUBSCRIBE_STATE}
     * @param [in] user_id
     *       用户的标识
     * @param [in] info
     *       流的属性，详见：{@link #SubscribeConfig}
     */
    virtual void OnStreamSubscribed(SUBSCRIBE_STATE state_code, const char* user_id, const SubscribeConfig& info) {
        (void)state_code;
        (void)user_id;
        (void)info;
    }

    /**
     * @type callback
     * @region 音视频回退
     * @brief 收到远端流回退或恢复时回调该事件。
     * @param [in] event 远端流回退或恢复数据。详见 RemoteStreamSwitch{@link #RemoteStreamSwitch}。
     */
    virtual void OnRemoteStreamSwitch(const RemoteStreamSwitch& event) {
        (void)event;
    }

    /**
     * @hidden
     * @type callback
     * @region 房间管理
     * @brief 当发布流成功的时候回调该事件
     * @param [in] user_id 用户ID
     * @param [in] is_screen 该流是否是屏幕流
     *
     */
    virtual void OnStreamPublishSucceed(const char* user_id, bool is_screen) {
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
     * @region 流消息
     * @brief 点对点消息回调。接收到同一房间内 uid 所属用户发来消息时触发。
     * @param [in] uid  <br>
     *        消息发送者 ID 。
     * @param [in] message  <br>
     *        收到的消息内容。
     * @notes  <br>
     *        + 同一房间内其他用户调用 SendUserMessage{@link #IRtcRoom#SendUserMessage} 发送消息给本地用户时会收到该回调。
     */
    virtual void OnUserMessageReceived(const char* uid, const char* message) {
        (void)uid;
        (void)message;
    }

    /**
     * @type callback
     * @region 流消息
     * @brief 接收到同一房间内 uid 所属用户发来二进制消息的回调。
     * @param [in] uid 消息发送者 ID
     * @param [in] size 二进制消息长度
     * @param [in] message 收到的二进制消息内容
     * @notes  <br>
     *        + 同一房间内其他用户调用 SendUserBinaryMessage{@link #IRtcRoom#SendUserBinaryMessage} 发送消息给本地用户时会收到该回调。
     */
    virtual void OnUserBinaryMessageReceived(const char* uid, int size, const uint8_t* message) {
        (void)uid;
        (void)size;
        (void)message;
    }

    /**
     * @type callback
     * @region 流消息
     * @brief 当调用 SendUserMessage{@link #IRtcRoom#SendUserMessage} 函数发送消息后，回调此条消息的发送结果（反馈）。
     * @param [in] msgid 本条消息的 ID
     * @param [in] error 消息发送结果，详见 MESSAGE_SEND_RESULT_CODE{@link #MESSAGE_SEND_RESULT_CODE}
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
     * @param [in] error 消息发送结果，详见 MESSAGE_SEND_RESULT_CODE{@link #MESSAGE_SEND_RESULT_CODE}
     */
    virtual void OnRoomMessageSendResult(int64_t msgid, int error) {
        (void)msgid;
        (void)error;
    }

    /**
     * @hidden
     * @type callback
     * @region 房间管理
     * @brief 直播推流转码错误回调。
     *        用户调用 EnableLiveTranscoding{@link #EnableLiveTranscoding} 接口启动直播推流转码功能后，启动结果和推流过程中
     *        的错误均会通过此回调方法通知用户。
     * @param [in] url
     *        推流地址的 URL。
     * @param [in] error
     *        直播推流转码功能错误码，详见枚举类型 RTC_TRANSCODING_ERROR_CODE{@link #RTC_TRANSCODING_ERROR_CODE}。
     */
    virtual void OnTranscodingError(const char* url, int error) {
        (void)url;
        (void)error;
    }

#ifndef BYTERTC_AUDIO_ONLY
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
     * @brief 房间内用户暂停/恢复发送视频流时，房间内其他用户()收到此回调。参看 MuteLocalVideoStream{@link #MuteLocalVideoStream}。
     * @param [in] uid 暂停/恢复发送视频流的用户 ID。
     * @param  [in] mute 暂停/恢复发送视频流。参看 MuteState{@link #MuteState}。
     */
    virtual void OnUserMuteVideo(const char* uid, MuteState mute) {
        (void)uid;
        (void)mute;
    }

    /**
     * @type callback
     * @region 视频管理
     * @brief 远端用户开启/关闭本地视频采集时回调该事件，当远端用户调用 EnableLocalVideo{@link #EnableLocalVideo} 时，其他用户会触发此回调。
     * @param [in] uid 用户ID，提示是哪个用户的视频流。
     * @param  [in] enabled 是否启用本地视频功能。  <br>
     *       + true：该用户已启用本地视频功能。启用后，其他用户可以接收到该用户的视频流。  <br>
     *       + false：该用户已关闭视频功能。关闭后，该用户仍然可以接收其他用户的视频流，但其他用户接收不到该用户的视频流。  <br>
     * @notes 提示有其他用户启用/关闭了本地视频功能。
     */
    virtual void OnUserEnableLocalVideo(const char* uid, bool enabled) {
        (void)uid;
        (void)enabled;
    }

    /**
     * @type callback
     * @region 视频管理
     * @brief 通话中本地视频流的统计信息回调。
     * @param [in] stats 本地视频统计数据，详见 LocalVideoStats{@link #LocalVideoStats}。
     * @notes 该回调描述本地设备发送视频流的统计信息，每2秒触发一次。
     */
    virtual void OnLocalVideoStats(const LocalVideoStats& stats) {
        (void)stats;
    }

    /**
     * @type callback
     * @region 视频管理
     * @brief 通话中远端视频流的统计信息回调。
     * @param [in] stats 远端视频统计数据，详见 RemoteVideoStats{@link #RemoteVideoStats}。
     * @notes
     *      该回调描述远端用户在通话中端到端的视频流状态，针对每个远端用户/主播每2秒触发一次。如果远端同时存在多个用户/主播，该回调每2秒会被触发多次。
     */
    virtual void OnRemoteVideoStats(const RemoteVideoStats& stats) {
        (void)stats;
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
     * @param [in] reason 远端音频流状态改变的原因，参看 RemoteAudioStateReason{@link #RemoteAudioStateReason}
     */
    virtual void OnRemoteAudioStateChanged(
            const RemoteStreamKey& key, RemoteAudioState state, RemoteAudioStateReason reason) {
        (void)key;
        (void)state;
        (void)reason;
    }

    /**
     * @type callback
     * @region 视频管理
     * @brief 本地视频流的状态发生改变时，收到该事件。
     * @param [in] index 音视频属性, 参看 StreamIndex{@link #StreamIndex}
     * @param [in] state 本地视频流状态，详见 LocalVideoStreamState{@link #LocalVideoStreamState}
     * @param [in] error 本地视频状态改变时的错误码，详见 LocalVideoStreamError{@link #LocalVideoStreamError}
     */
    virtual void OnLocalVideoStateChanged(StreamIndex index, LocalVideoStreamState state, LocalVideoStreamError error) {
        (void)index;
        (void)state;
        (void)error;
    }

    /**
     * @type callback
     * @region 视频管理
     * @brief 远端视频流的状态发生改变时，房间内的用户会收到该事件。
     * @param [in] key 远端视频流的信息，房间，用户 ID，流属性等。参看 RemoteStreamKey{@link #RemoteStreamKey}。
     * @param [in] state 远端视频流状态，参看 RemoteVideoState{@link #RemoteVideoState}。
     * @param [in] reason 远端视频流状态改变的原因，参看 RemoteVideoStateReason{@link #RemoteVideoStateReason}。
     */
    virtual void OnRemoteVideoStateChanged(
            RemoteStreamKey key, RemoteVideoState state, RemoteVideoStateReason reason) {
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
     * @brief 屏幕共享流视频首帧播放状态改变回调
     * @param [in] user 远端用户信息，详见 RtcUser{@link #RtcUser}
     * @param [in] state 首帧播放状态，详见 FirstFramePlayState{@link #FirstFramePlayState}
     */
    virtual void OnScreenVideoFramePlayStateChanged(const RtcUser& user, FirstFramePlayState state) {
        (void)user;
        (void)state;
    }

#endif  // BYTERTC_AUDIO_ONLY
};

}
