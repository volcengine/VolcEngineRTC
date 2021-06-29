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
     * @brief 提示房间内谁正在说话以及说话者音量的回调
     * @param [in] speakers
     *        房间内所有用户ID, 以及每个用户对应的音量，包括发送流和接收流。详见：AudioVolumeInfo{@link #AudioVolumeInfo}。
     * @param [in] speaker_number
     *        音频源数量，包括发送流与接收流
     * @param [in] total_volume
     *        音频源总音量，只包含接收流
     * @notes  <br>
     *       + 该回调提示房间内所有用户的用户ID及他们的音量。默认禁用。  <br>
     *       + 可以通过启用说话者音量提示 EnableAudioVolumeIndication{@link #IRtcRoom#EnableAudioVolumeIndication} 方法开启。  <br>
     *       + 开启后，无论房间内是否有人说话，都会按方法中设置的时间间隔返回提示音量。  <br>
     */
    virtual void OnAudioVolumeIndication(const AudioVolumeInfo* speakers, unsigned int speaker_number, int total_volume) {
        (void)speakers;
        (void)speaker_number;
        (void)total_volume;
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
     * @hidden
     * @type callback
     * @region 音频事件回调
     * @brief 当某个用户静音远端所有用户音频时, 房间内其他人收到这个回调。
     *        该回调由远端用户调用 MuteAllRemoteAudioStreams{@link #IRtcRoom#MuteAllRemoteAudioStreams} 或 UnmuteAllRemoteAudioStreams{@link #IRtcRoom#UnmuteAllRemoteAudioStreams} 触发。
     * @param [in] uid 远端用户ID
     * @param [in] muted  是否静音所有远端音频流  <br>
     *            + true: 该用户静音所有远端音频流  <br>
     *            + false: 该用户取消静音了所有远端音频流  <br>
     */
    virtual void OnMuteAllRemoteAudio(const char* uid, bool muted) {
        (void)uid;
        (void)muted;
    }

    /**
     * @type callback
     * @region 视频管理
     * @brief 当某个用户开启/关闭远端所有用户视频时回调该事件。
     * @param [in] uid 远端用户标识。
     * @param  [in] muted 是否被关闭视频。  <br>
     *       + true: 远端用户关闭所有用户视频数据；  <br>
     *       + false: 远端用户开启所有用户视频数据。  <br>
     */
    virtual void OnMuteAllRemoteVideo(const char* uid, bool muted) {
        (void)uid;
        (void)muted;
    }

    /**
     * @type callback
     * @region 音频事件回调
     * @brief 远端用户将其本地音频流静音时，房间内其他人会收到这个回调。
     *        该回调由远端用户调用 MuteLocalAudioStream{@link #IRtcEngineLite#MuteLocalAudioStream} 方法触发。
     * @param [in] uid 远端用户ID
     * @param [in] muted 该用户是否已将其本地音频流静音  <br>
     *       + true: 该用户已将其本地音频流静音  <br>
     *       + false: 该用户已将其本地音频流取消了静音  <br>
     */
    virtual void OnUserMuteAudio(const char* uid, bool muted) {
        (void)uid;
        (void)muted;
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
     * @region 引擎管理
     * @brief SDK 与信令服务器连接断开回调。当 SDK 与信令服务器的网络连接断开超过 10 秒时回调该事件。
     * @notes  <br>
     *        + 除非主动调用 LeaveChannel{@link #LeaveChannel} ，否则 SDK 会一直尝试重连。
     */
    virtual void OnConnectionLost() {
    }

    /**
     * @type callback
     * @region 引擎管理
     * @brief SDK 与信令服务器连接中断回调。当 SDK 检测到与信令服务器的网络连接中断时回调该事件。
     * @notes  <br>
     *        + 除非主动调用 LeaveChannel{@link #LeaveChannel} ，否则 SDK 会一直尝试重连。
     */
    virtual void OnConnectionInterrupted() {
    }

    /**
     * @type callback
     * @region 音频事件回调
     * @brief 当收到本地第一帧音频的时候上报该事件
     * @param [in] elapsed
     *        从开始发布音频流到收到该事件经历的时间（毫秒单位）
     */
    virtual void OnFirstLocalAudioFrame(int elapsed) {
        (void)elapsed;
    }

    /**
     * @type callback
     * @region 音频事件回调
     * @brief 当收到远端流的第一帧音频的时候上报该事件
     * @param [in] uid
     *        远端用户ID
     * @param [in] elapsed
     *        从开始订阅音频流到收到该事件经历的时间（毫秒单位）
     */
    virtual void OnFirstRemoteAudioFrame(const char* uid, int elapsed) {
        (void)uid;
        (void)elapsed;
    }

    /**
     * @type callback
     * @region 房间管理
     * @brief 房间内远端流移除回调。  <br>
     *        房间内的远端用户停止发布音视频流时，本地用户会收到此回调通知。  <br>
     * @param [in] stream 流的属性，详见数据结构 ByteStream{@link #ByteStream} 。  <br>
     * @param [in] reason 远端流移除的原因，详见枚举类型 RtcStreamRemoveReason{@link #RtcStreamRemoveReason} 。  <br>
     */
    virtual void OnStreamRemove(const ByteStream& stream, RtcStreamRemoveReason reason) {
        (void)stream;
    }

    /**
     * @type callback
     * @region 房间管理
     * @brief 房间内新流发布回调。  <br>
     *        房间内的远端用户发布新的音视频流时，本地用户会收到此回调通知。  <br>
     * @param [in] stream 流的属性，详见数据结构 ByteStream{@link #ByteStream} 。  <br>
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
     * @param [in] message 收到的消息内容
     * @notes
     *        1.同一房间内其他用户调用 SendRoomMessage{@link #IRtcRoom#SendRoomMessage} 发送广播消息时会收到该回调。
     */
    virtual void OnRoomMessageReceived(const char* user_id, const char* message) {
        (void)message;
    }
    
    /**
     * @type callback
     * @region 流消息
     * @brief 接收到房间内二进制广播消息的回调。
     * @param [in] size 收到的二进制消息长度
     * @param [in] message 收到的二进制消息内容
     * @notes
     *        1.同一房间内其他用户调用 SendRoomBinaryMessage{@link #IRtcRoom#SendRoomBinaryMessage} 发送二进制广播消息时会收到该回调。
     */
    virtual void OnRoomBinaryMessageReceived(const char* user_id, int size, const uint8_t* message) {
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
     * @brief 收到第一帧本地视频画面时回调该事件。
     * @param [in] width 视频流宽（像素）。
     * @param [in] height 视频流高（像素）。
     * @param [in] elapsed 从调用 JoinChannel{@link #IRtcEngine#JoinChannel} 方法直至该回调被触发的延迟（毫秒），如果在 JoinChannel{@link #IRtcEngine#JoinChannel} 之前调用了 StartPreview{@link #IRtcEngineLite#StartPreview}，则返回的是从调用 StartPreview{@link #IRtcEngineLite#StartPreview} 直至该回调被触发的延迟（毫秒）。
     * @notes 第一帧本地视频显示在视图上时，触发此回调。
     */
    virtual void OnFirstLocalVideoFrame(int width, int height, int elapsed) {
        (void)width;
        (void)height;
        (void)elapsed;
    }

    /**
     * @type callback
     * @region 视频管理
     * @brief 当收到本地屏幕共享流第一帧时回调该事件。
     * @param [in] width 视频流宽（像素）。
     * @param [in] height 视频流高（像素）。
     * @param [in] elapsed 从加入频道开始到现在经历的时间(毫秒单位)。
     * @notes 第一帧本地视频显示在视图上时，触发此回调。
     */
    virtual void OnFirstLocalScreenFrame(int width, int height, int elapsed) {
        (void)width;
        (void)height;
        (void)elapsed;
    }

    /**
     * @type callback
     * @region 视频管理
     * @brief 当远端视频第一帧视频被解码时回调该事件。
     * @param [in] uid 远端用户 UserId。
     * @param [in] width 视频流宽（像素）。
     * @param [in] height 视频流高（像素）。
     * @param [in] elapsed 从调用 JoinChannel{@link #IRtcEngine#JoinChannel} 方法直至该回调被触发的延迟（毫秒）。
     * @notes 收到第一帧远端视频流并解码成功时，触发此调用。应用可以在此回调中设置该用户的 View。
     */
    virtual void OnFirstRemoteVideoDecoded(const char* uid, int width, int height, int elapsed) {
        (void)uid;
        (void)width;
        (void)height;
        (void)elapsed;
    }

    /**
     * @type callback
     * @region 视频管理
     * @brief 本地或远端视频大小或旋转信息发生改变回调。
     * @param [in] uid 图像尺寸和旋转信息发生变化的用户ID。如果返回的 uid 为空，则表示本地用户。
     * @param [in] width 视频流的宽度（像素）。
     * @param [in] height 视频流的高度（像素）。
     * @param [in] rotation 旋转角度[0，360]。
     */
    virtual void OnVideoSizeChanged(const char* uid, int width, int height, int rotation) {
        (void)uid;
        (void)width;
        (void)height;
        (void)rotation;
    }

    /**
     * @type callback
     * @region 视频管理
     * @brief 收到远端流后解码第一帧时回调该事件。
     * @param [in] uid 远端用户 UserId。
     * @param [in] width 视频流宽（像素）。
     * @param [in] height 视频流高（像素）。
     * @param [in] elapsed 从调用 JoinChannel{@link #IRtcEngine#JoinChannel} 加入频道开始到发生此事件过去的时间（毫秒）。
     * @notes 第一帧远端视频显示在视图上时，触发此调用。应用可在此调用中获知出图时间（elapsed）。出图时间指从订阅视频流到第一个视频帧刷出来的间隔。
     */
    virtual void OnFirstRemoteVideoFrame(const char* uid, int width, int height, int elapsed) {
        (void)uid;
        (void)width;
        (void)height;
        (void)elapsed;
    }

    /**
     * @type callback
     * @region 视频管理
     * @brief 收到远端屏幕共享流后解码第一帧时回调该事件。
     * @param [in] uid 用户ID，指定是哪个用户的屏幕共享流。
     * @param [in] width 视频流宽（像素）。
     * @param [in] height 视频流高（像素）。
     * @param [in] elapsed 从调用 JoinChannel{@link #IRtcEngine#JoinChannel} 加入频道开始到发生此事件过去的时间（毫秒）。
     */
    virtual void OnFirstRemoteScreenFrame(const char* uid, int width, int height, int elapsed) {
        (void)uid;
        (void)width;
        (void)height;
        (void)elapsed;
    }

    /**
     * @type callback
     * @region 视频管理
     * @brief 远端用户暂停/恢复发送视频流时回调该事件，当远端用户调用 MuteLocalVideoStream{@link #MuteLocalVideoStream} 时，其他用户会触发此回调。
     * @param [in] uid 用户ID，提示是哪个用户的视频流。
     * @param  [in] muted 是否发送视频流。  <br>
     *       + true：该用户已暂停发送视频流。  <br>
     *       + false：该用户已恢复发送视频流。  <br>
     * @notes 提示有其他用户暂停/恢复了视频流的发送。
     */
    virtual void OnUserMuteVideo(const char* uid, bool muted) {
        (void)uid;
        (void)muted;
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
     * @brief 远端用户音频状态发生改变时，该回调通知当前的远端音频流状态。
     * @param [in] uid 该远端流的用户ID
     * @param [in] state 远端音频流状态，详见：RemoteAudioState{@link #RemoteAudioState}
     * @param [in] reason 远端音频流状态改变的原因，详见：RemoteAudioStateReason{@link #RemoteAudioStateReason}
     * @param [in] elapsed 耗时，从加入房间到该事件发生经历的时间（毫秒单位）
     */
    virtual void OnRemoteAudioStateChanged(
            const char* uid, RemoteAudioState state, RemoteAudioStateReason reason, int elapsed) {
        (void)uid;
        (void)state;
        (void)reason;
        (void)elapsed;
    }
    
    /**
     * @type callback
     * @region 视频管理
     * @brief 本地视频的状态发生改变时，该回调返回当前的本地视频状态。
     * @param [in] state 本地视频状态，详见 LocalVideoStreamState{@link #LocalVideoStreamState}。
     * @param [in] error 本地视频状态改变时的错误码，详见 LocalVideoStreamError{@link #LocalVideoStreamError}。
     */
    virtual void OnLocalVideoStateChanged(LocalVideoStreamState state, LocalVideoStreamError error) {
        (void)state;
        (void)error;
    }

    /**
     * @type callback
     * @region 视频管理
     * @brief 远端用户视频状态发生改变时，该回调报告当前的远端视频流状态。
     * @param [in] uid 该远端流的用户 id。
     * @param [in] state 远端视频流状态，详见 RemoteVideoState{@link #RemoteVideoState}。
     * @param [in] reason 远端视频流状态改变的原因，详见 RemoteVideoStateReason{@link #RemoteVideoStateReason}。
     * @param [in] elapsed 耗时，暂未实现。
     */
    virtual void OnRemoteVideoStateChanged(
            const char* uid, RemoteVideoState state, RemoteVideoStateReason reason, int elapsed) {
        (void)uid;
        (void)state;
        (void)reason;
        (void)elapsed;
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
