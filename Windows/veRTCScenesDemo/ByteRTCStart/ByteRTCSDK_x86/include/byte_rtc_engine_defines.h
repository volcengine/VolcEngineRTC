//
//  byte_rtc_engine_defines.h
//  Pods
//
//  Created by xiewei on 2020/6/22.
//

#pragma once
#include "byte_rtc_video_frame.h"
namespace bytertc {
/**
 * @hidden
 * @type keytype
 * @brief 游戏引擎工作模式
 */
enum RtcMode {
    /**
     * @brief 通用模式，该模式下只能进行普通会议模式的语音通话，开启自动发布订阅。
     */
    RTC_MODE_GENERAL = 0,
    /**
     * @brief 游戏语音模式，该模式下关闭自动发布订阅，会按照游戏业务的策略进行主动发布订阅语音。
     */
    RTC_MODE_LOCAL_AUDIO
};

/**
 * @hidden
 * @type keytype
 * @brief 游戏语音收发模式，接收方和发布方可选的模式范围一致，只有发布方和接收方设置的模式匹配时，才可能进行通话
 */
enum RangeAudioMode {
    /**
     * @brief 默认模式，发送方将发送模式设置为该模式，表示发送方针对该房间关闭麦克风，接收方设置接收模式为该模式，表示接收方不收听该房间的语音
     */
    RANGE_AUDIO_MODE_UNDEFINED = 0,
    /**
     * @brief 小队模式，发送方将发送模式设置为该模式，表示只向同小队的成员发布语音，接收方设置接收模式为该模式，表示只收听同小队成员的语音
     */
    RANGE_AUDIO_MODE_TEAM,
    /**
     * @brief 世界模式，发送方将发送模式设置为该模式，表示发布的语音可以让小队成员收听，非小队成员在满足收听条件（接收世界模式  <br>
     *       + 开启区域语音衰减时，距离足够近；关闭区域语音衰减时，可以直接听到）时也可收听；接收方将接收模式设置为该模式表示收  <br>
     *       + 听小队成员的声音和非队友在世界模式下发送的声音  <br>
     */
    RANGE_AUDIO_MODE_WORLD
};

/**
 * @type keytype
 * @brief 渲染模式
 */
enum RENDER_MODE_TYPE {
     /**
     * @brief 视窗填满优先。<br>
     *        视频帧等比缩放，直至视窗被视频填满。如果视频帧长宽比例与视窗不同，视频帧的多出部分将无法显示。<br>
     *        缩放完成后，视频帧的一边长和视窗的对应边长一致，另一边长大于等于视窗对应边长。
     */
    RENDER_MODE_HIDDEN = 1,
     /**
     * @brief 视频帧内容全部显示优先。<br>
     *        视频帧等比缩放，直至视频帧能够在视窗上全部显示。如果视频帧长宽比例与视窗不同，视窗上未被视频帧填满区域将被涂黑。<br>
     *        缩放完成后，视频帧的一边长和视窗的对应边长一致，另一边长小于等于视窗对应边长。
     */
    RENDER_MODE_FIT = 2,
    /**
     * @hidden
     * @brief 暂时不支持设置为该值
     */
    RENDER_MODE_ADAPTIVE = 3,
};

/**
 * @type keytype
 * @brief 用户离线原因。  <br>
 *        房间内的远端用户离开房间时，本地用户会收到 OnUserOffline{@link #OnUserOffline} 回调通知，此枚举类型为回调的用户离线原因。  <br>
 */
enum USER_OFFLINE_REASON_TYPE {
    /**
     * @brief 用户主动离开。即远端用户调用 LeaveChannel{@link #LeaveChannel} 方法退出房间。  <br>
     */
    USER_OFFLINE_QUIT = 0,
    /**
     * @brief 用户掉线。远端用户因为网络等原因掉线。  <br>
     */
    USER_OFFLINE_DROPPED = 1,
    /**
     * @hidden
     */
    USER_OFFLINE_BECOME_AUDIENCE = 2,
};

/**
 * @type keytype
 * @brief 房间内远端流被移除的原因。  <br>
 */
enum RtcStreamRemoveReason {
    /**
     * @brief 远端用户停止发布流。  <br>
     */
    kRtcStreamRemoveUnpublish = 0,
    /**
     * @brief 远端用户发布流失败。  <br>
     */
    kRtcStreamRemovePublishFailed = 1,
    /**
     * @brief 保活失败。  <br>
     */
    kRtcStreamRemoveKeepLiveFailed = 2,
    /**
     * @brief 远端用户断网。  <br>
     */
    kRtcStreamRemoveClientDisconnected = 3,
    /**
     * @brief 远端用户重新发布流。  <br>
     */
    kRtcStreamRemoveRepublish = 4,
    /**
     * @brief 其他原因。  <br>
     */
    kRtcStreamRemoveOtherReason = 5,
};

/**
 * @type keytype
 * @brief 用户角色。房间模式为直播、游戏、云游戏模式时的可选用户角色。  <br>
 *        用户可通过设置用户角色控制：1.发布/取消发布音视频流；2.用户自身是否在房间中隐身。设置用户角色参考 SetClientRole{@link #SetClientRole} 方法。  <br>
 */
enum CLIENT_ROLE_TYPE {
    /**
     * @brief 主播角色。主播角色的用户既可以发布流到房间中，也可以从房间中订阅流，房间中的其他用户可以感知到该用户在房间中。  <br>
     */
    CLIENT_ROLE_BROADCASTER = 1,
    /**
     * @brief 静默观众角色。静默观众角色的用户只能从房间中订阅流，不能向房间中发布流，房间中的其他用户无法感知到该用户在房间中。该用户加入退出房间等行为不会通知给房间中的其他用户。  <br>
     */
    CLIENT_ROLE_SILENT_AUDIENCE = 3,
};

/**
 * @type keytype
 * @brief 发送消息给用户的结果
 */
enum UserMessageSendResult {
    /**
     * @brief 用户P2P消息发送成功
     */
    kUserMessageSendResultSuccess = 0,
    /**
     * @brief 发送超时，没有发送
     */
    kUserMessageSendResultErrorTimeout = 1,
    /**
     * @brief 通道断开，没有发送
     */
    kUserMessageSendResultErrorBroken = 2,
    /**
     * @brief 找不到接收方
     */
    kUserMessageSendResultErrorNotReceiver = 3,
    /**
     * @brief 获取级联路径失败
     */
    kUserMessageSendResultErrorNoRelayPath = 4,
    /**
     * @brief 没有加入房间
     */
    kUserMessageSendResultErrorNotJoin = 100,
    /**
     * @brief 没有可用的数据传输通道连接
     */
    kUserMessageSendResultErrorNoConnection = 102,
    /**
     * @brief 消息超过最大长度，当前为64KB
     */
    kUserMessageSendResultErrorExceedMaxLength = 103,
    /**
     * @brief 用户id为空
     */
    kUserMessageSendResultErrorEmptyUser = 104,
    /**
     * @brief 未知错误
     */
    kUserMessageSendResultErrorUnknown = 1000,
};

/**
 * @type keytype
 * @brief 发送消息给房间的结果
 */
enum RoomMessageSendResult {
    /**
     * @brief 房间Broadcast消息发送成功
     */
    kRoomMessageSendResultSuccess = 200,
    /**
     * @brief 没有加入房间
     */
    kRoomMessageSendResultErrorNotJoin = 100,
    /**
     * @brief 没有可用的数据传输通道连接
     */
    kRoomMessageSendResultErrorNoConnection = 102,
    /**
     * @brief 消息超过最大长度，当前为64KB
     */
    kRoomMessageSendResultErrorExceedMaxLength = 103,
    /**
     * @brief 未知错误
     */
    kRoomMessageSendResultErrorUnknown = 1000,
};


/**
 * @type keytype
 * @brief SDK 与 RTC 服务器连接状态。
 */
enum CONNECTION_STATE {
    /**
     * @brief 连接断开。
     */
    CONNECTION_STATE_DISCONNECTED = 1,
    /**
     * @brief 首次连接，正在连接中。
     */
    CONNECTION_STATE_CONNECTING = 2,
    /**
     * @brief 首次连接成功。
     */
    CONNECTION_STATE_CONNECTED = 3,
    /**
     * @brief 连接断开后，重新连接中。
     */
    CONNECTION_STATE_RECONNECTING = 4,
    /**
     * @brief 连接断开后，重连成功。
     */
    CONNECTION_STATE_RECONNECTED = 5,
    /**
     * @brief 网络连接断开超过 10 秒。SDK 仍然会继续尝试重连。
     */
    CONNECTION_STATE_LOST = 6,
};


/**
 * @type keytype
 * @brief 媒体流网络质量。
 */
enum NetworkQuality {
    /**
     * @brief 网络质量未知。
     */
    kNetworkQualityUnknown = 0,
    /**
     * @brief 网络质量极好。
     */
    kNetworkQualityExcellent,
    /**
     * @brief 主观感觉和 kNetworkQualityExcellent 差不多，但码率可能略低。
     */
    kNetworkQualityGood,
    /**
     * @brief 主观感受有瑕疵但不影响沟通。
     */
    kNetworkQualityPoor,
    /**
     * @brief 勉强能沟通但不顺畅。
     */
    kNetworkQualityBad,
    /**
     * @brief 网络质量非常差，基本不能沟通。
     */
    kNetworkQualityVbad,
};

/**
 * @type keytype
 * @brief SDK 网络连接类型。
 */
enum NetworkType {
    /**
     * @brief 网络连接类型未知。
     */
    kNetworkTypeUnknown = -1,
    /**
     * @brief 网络连接已断开。
     */
    kNetworkTypeDisconnected = 0,
    /**
     * @brief 网络连接类型为 LAN 。
     */
    kNetworkTypeLAN = 1,
    /**
     * @brief 网络连接类型为 Wi-Fi（包含热点）。
     */
    kNetworkTypeWIFI = 2,
    /**
     * @brief 网络连接类型为 2G 移动网络。
     */
    kNetworkTypeMobile2G = 3,
    /**
     * @brief 网络连接类型为 3G 移动网络。
     */
    kNetworkTypeMobile3G = 4,
    /**
     * @brief 网络连接类型为 4G 移动网络。
     */
    kNetworkTypeMobile4G = 5,
    /**
     * @brief 网络连接类型为 5G 移动网络。
     */
    kNetworkTypeMobile5G = 6,
};

/**
 * @type keytype
 * @brief 屏幕共享参数
 */
struct ScreenParameters {
    /**
     * @brief 编码帧率,单位为 fps
     */
    int frame_rate = 15;
    /**
     * @brief 编码码率，小于 0 时 SDK 会根据高宽自适应码率, 单位 kbps
     */
    int kbitrate = -1;
};

/**
 * @type keytype
 * @brief 房间模式。房间使用的场景模式。  <br>
 *        通过设置房间模式，用户可以选择应用 SDK 针对不同房间模式场景的优化策略。设置房间模式参考 SetChannelProfile{@link #SetChannelProfile} 方法。  <br>
 */
enum CHANNEL_PROFILE_TYPE {
    /**
     * @brief 通信模式。通信模式下，无用户角色区分。适用于 IM 场景。  <br>
     */
    CHANNEL_PROFILE_COMMUNICATION = 0,
    /**
     * @brief 直播模式。直播模式下，有用户角色区分（用户角色参考 CLIENT_ROLE_TYPE{@link #CLIENT_ROLE_TYPE}）。适用于直播、教育大班课等场景。  <br>
     */
    CHANNEL_PROFILE_LIVE_BROADCASTING = 1,
    /**
     * @brief 游戏模式。游戏模式下，有用户角色区分。 SDK 会使用低延时设置。适用于游戏场景。  <br>
     */
    CHANNEL_PROFILE_GAME = 2,
    /**
     * @brief 云游戏模式。云游戏模式下，有用户角色区分。 SDK 会使用低延时设置。适用于云游戏场景。  <br>
     */
    CHANNEL_PROFILE_CLOUD_GAME = 3,
};

/**
 * @type keytype
 * @brief 媒体设备类型
 */
enum MediaDeviceType {
    /**
     * @brief 音频播放设备类型
     */
    kAudioPlayoutDevice = 0,
    /**
     * @brief 音频录制设备类型
     */
    kAudioRecordingDevice = 1,
    /**
     *@brief 视频渲染设备类型，该类型暂无使用
     */
    kVideoRenderDevice = 2,
    /**
     *@brief 视频采集设备类型
     */
    kVideoCaptureDevice = 3
};

/**
 * @type keytype
 * @brief 媒体设备事件类型
 */
enum MediaDeviceNotification {
    /**
     *@brief 设备已就绪
     */
    kMediaDeviceNotificationActive = 1,
    /**
     *@brief 设备被禁用
     */
    kMediaDeviceNotificationDisabled = 2,
    /**
     *@brief 没有此设备
     */
    kMediaDeviceNotificationNotPresent = 4,
    /**
     *@brief 设备被拔出
     */
    kMediaDeviceNotificationUnplugged = 8
};

/**
 * @type keytype
 * @brief 媒体设备状态类型
 */
enum MediaDeviceState {
    /**
     *@brief 设备已开启
     */
    kMediaDeviceStateStarted = 0,
    /**
     *@brief 设备开启失败
     */
    kMediaDeviceStateStartFailed = 1,
    /**
     *@brief 设备已停止
     */
    kMediaDeviceStateStopped = 2,
    /**
     *@brief 设备停止失败
     */
    kMediaDeviceStateStopFailed = 3
};

/**
* @hidden(macOS,Windows)
* @type keytype
* @brief 音频场景类型。<br>
*        选择音频场景后，RTC 会自动根据客户端音频路由和发布订阅状态，适用通话音量/媒体音量。<br>
*        你可以调用 SetAudioScenario{@link #SetAudioScenario} 设置音频场景。<br>
*        如果以下音频场景类型无法满足你的业务需要，请联系技术支持同学进行定制。
*/
enum AudioScenarioType {
    /**
     * @brief 音乐场景。默认为此场景。<br>
     *        此场景适用于对音乐表现力有要求的场景。如音乐直播等。<br>
     *        音频路由和发布订阅状态，到音量类型的映射如下：<br>
     *        <table>
     *           <tr><th></th><th>仅发布音视频流</th><th>仅订阅音视频流</th><th>发布并订阅音视频流</th><th>备注</th></tr>
     *           <tr><td>设备自带麦克风和扬声器/听筒</td><td>媒体音量</td><td>媒体音量</td><td>通话音量</td><td>/</td></tr>
     *           <tr><td>有线耳机</td><td>媒体音量</td><td>媒体音量</td><td>媒体音量</td><td>/</td></tr>
     *           <tr><td>蓝牙耳机</td><td>媒体音量</td><td>媒体音量</td><td>媒体音量</td><td>即使蓝牙耳机有麦克风，也只能使用设备自带麦克风进行本地音频采集。</td></tr>
     *        </table>
     */
    kAudioScenarioMusic = 0,
    /**
     * @brief 高质量通话场景。<br>
     *        此场景适用于对音乐表现力有要求的场景。但又希望能够使用蓝牙耳机上自带的麦克风进行音频采集的场景。
     *        此场景可以兼顾外放/使用蓝牙耳机时的音频体验；并尽可能避免使用蓝牙耳机时音量类型切换导致的听感突变。<br>
     *        音频路由和发布订阅状态，到音量类型的映射如下：<br>
     *        <table>
     *           <tr><th></th><th>仅发布音视频流</th><th>仅订阅音视频流</th><th>发布并订阅音视频流</th> <th>备注</th> </tr>
     *           <tr><td>设备自带麦克风和扬声器/听筒</td><td>媒体音量</td><td>媒体音量</td><td>通话音量</td><td>/</td></tr>
     *           <tr><td>有线耳机</td><td>媒体音量</td><td>媒体音量</td><td>媒体音量</td><td>/</td></tr>
     *           <tr><td>蓝牙耳机</td><td>通话音量</td><td>通话音量</td><td>通话音量</td><td>能够使用蓝牙耳机上自带的麦克风进行音频采集。</td></tr>
     *        </table>
     */
    kAudioScenarioHighQualityCommunication = 1,
    /**
     * @brief 纯通话音量场景。<br>
     *        此场景下，无论客户端音频路由情况和发布订阅状态，全程使用通话音量。
     *        适用于需要频繁上下麦的通话或会议场景。<br>
     *        此场景可以保持统一的音频模式，不会有音量突变的听感；
     *        最大程度上的消除回声，使通话清晰度达到最优；
     *        使用蓝牙耳机时，能够使用蓝牙耳机上自带的麦克风进行音频采集。<br>
     *        但是，使用媒体音量进行播放的其他音频的音量会被压低，且音质会变差。
     */
    kAudioScenarioCommunication = 2,
    /**
     * @brief 纯媒体场景。一般不建议使用。<br>
     *        此场景下，无论客户端音频路由情况和发布订阅状态，全程使用媒体音量。
     *        外放通话时，极易出现回声和啸叫。
     */
    kAudioScenarioMedia = 3,
};







/**
 * @hidden
 */
enum SUBSCRIBE_STATE {
    /**
     * @brief 订阅流成功
     */
    SUB_STATE_SUCCESS,
    /**
     * @hidden
     */
    SUB_STATE_FAILED_NOT_IN_ROOM,
    /**
     * @brief 没有找到流
     */
    SUB_STATE_FAILED_STREAM_NOT_FOUND,
    /**
     * @brief 超过订阅流上限
     */
    SUB_STATE_FAILED_OVER_LIMIT,
};

/**
 * @type keytype
 * @brief 订阅回退选项
 */
enum SubscribeFallbackOptions {
    /**
     * @brief 下行网络较弱时，不对音视频流作回退处理，默认值
     */
    kSubscribeFallbackOptionDisable = 0,
    /**
     * @brief 下行网络较弱时，只接收视频小流
     */
    kStreamFallbackOptionVideoStreamLow = 1,
    /**
     * @brief 下行网络较弱时，先尝试只接收视频小流；如果网络环境无法显示视频，则再回退到只接收远端订阅的音频流
     */
    kStreamFallbackOptionAudioOnly = 2,
};

/*
 * @type keytype
 * @brief 订阅模式选项。业务方在加入房间前，调用 EnableAutoSubscribe{@link #EnableAutoSubscribe} 接口设置订阅模式。  <br>
 */
enum SubscribeMode {
    /**
     * @brief 自动订阅模式。SDK 会自动为用户订阅房间中的每一路流。  <br>
     */
    kAutoSubscribeMode = 0,
    /**
     * @brief 手动订阅模式。SDK 不为自动订阅流。用户需要自己手动调用 SubscribeStream{@link #SubscribeStream} 接口去订阅远端流。
     */
    kManualSubscribeMode = 1
};

/**
 * @type keytype
 * @brief 远端用户优先级，在性能不足需要回退时，会优先回退优先级低的用户的音视频流
 */
enum RemoteUserPriority {
    /**
     * @brief 用户优先级为低，默认值
     */
    kRemoteUserPriorityLow = 0,
    /**
     * @brief 用户优先级为正常
     */
    kRemoteUserPriorityMedium = 100,
    /**
     * @brief 用户优先级为高
     */
    kRemoteUserPriorityHigh = 200,
};

/**
 * @type keytype
 * @brief 远端订阅流发生回退或恢复的原因
 */
enum FallbackOrRecoverReason {
    /**
     * @brief 其他原因，非带宽和性能原因引起的回退或恢复。默认值
     */
    kFallbackOrRecoverReasonUnknown = -1,
    /**
     * @brief 由带宽不足导致的订阅端音视频流回退。
     */
    kFallbackOrRecoverReasonSubscribeFallbackByBandwidth = 0,
    /**
     * @brief 由性能不足导致的订阅端音视频流回退。
     */
    kFallbackOrRecoverReasonSubscribeFallbackByPerformance = 1,
    /**
     * @brief 由带宽恢复导致的订阅端音视频流恢复。
     */
    kFallbackOrRecoverReasonSubscribeRecoverByBandwidth = 2,
    /**
     * @brief 由性能恢复导致的订阅端音视频流恢复。
     */
    kFallbackOrRecoverReasonSubscribeRecoverByPerformance = 3,
    /**
     * @brief 由带宽不足导致的发布端音视频流回退。
     */
    kFallbackOrRecoverReasonPublishFallbackByBandwidth = 4,
    /**
     * @brief 由性能不足导致的发布端音视频流回退。
     */
    kFallbackOrRecoverReasonPublishFallbackByPerformance = 5,
    /**
     * @brief 由带宽恢复导致的发布端音视频流恢复。
     */
    kFallbackOrRecoverReasonPublishRecoverByBandwidth = 6,
    /**
     * @brief 由性能恢复导致的发布端音视频流恢复。
     */
    kFallbackOrRecoverReasonPublishRecoverByPerformance = 7,
};

/**
 * @type keytype
 * @brief 流切换信息。本地用户订阅的远端流触发回退策略时的流切换信息。  <br>
 *        用户通过调用 SetPublishFallbackOption{@link #SetPublishFallbackOption} 方法/ SetSubscribeFallbackOption{@link #SetSubscribeFallbackOption} 方法设置发布/订阅流回退策略。而当本地用户订阅的音视频流发生回退时，SDK 会通过 OnRemoteStreamSwitch{@link #OnRemoteStreamSwitch} 回调事件通知用户。回调参数为回退的流切换信息。  <br>
 */
struct RemoteStreamSwitch {
    /**
     *@brief 远端用户ID 。远端流发布者的用户ID 。  <br>
     */
    const char* uid;
    /**
     *@brief 是否是屏幕流 。  <br>
     */
     bool is_screen;
    /**
     *@brief 流切换前本地用户订阅的视频流的分辨率对应的索引。  <br>
     */
    int before_video_index;
    /**
     *@brief 流切换后本地用户订阅的视频流的分辨率对应的索引。  <br>
     */
    int after_video_index;
    /**
     *@brief 流切换前是否有视频流。  <br>
     */
    bool before_enable;
    /**
     *@brief 流切换后是否有视频流。  <br>
     */
    bool after_enable;
    /**
     *@brief 触发流回退的原因，详见类型 FallbackOrRecoverReason{@link #FallbackOrRecoverReason} 。  <br>
     */
    FallbackOrRecoverReason reason;
};

/**
 * @type errorcode
 * @brief 回调错误码。
 *        SDK 内部遇到不可恢复的错误时，会通过 OnError{@link #OnError} 回调通知用户。
 */
enum RTC_ERROR_CODE {

    /**
     * @brief Token 无效。
     *        调用 JoinChannel{@link #JoinChannel} 方法时使用的 Token 无效或过期失效。需要用户重新获取 Token，并调用
     *        RenewToken{@link #RenewToken} 方法更新 Token。
     */
    BRERR_INVALID_TOKEN = -1000,

    /**
     * @brief 加入房间错误。
     *        调用 JoinChannel{@link #JoinChannel} 方法时发生未知错误导致加入房间失败。需要用户重新加入房间。
     */
    BRERR_JOIN_ROOM_ERROR = -1001,

    /**
     * @brief 没有发布音视频流权限。
     *        用户在所在房间中发布音视频流失败，失败原因为用户没有发布流的权限。
     */
    BRERR_NO_PUBLISH_PERMISSION = -1002,

    /**
     * @brief 没有订阅音视频流权限。
     *        用户订阅所在房间中的音视频流失败，失败原因为用户没有订阅流的权限。
     */
    BRERR_NO_SUBSCRIBE_PERMISSION = -1003,

    /**
     * @brief 用户重复登录。
     *        本端用户所在房间中有相同用户ID的用户登录，导致本端用户被踢出房间。
     */
    BRERR_DUPLICATE_LOGIN = -1004,

    /**
     * @brief 订阅音视频流总数超过上限。
     *        游戏场景下为了保证音视频通话的性能和质量，服务器会限制用户订阅的音视频流的总数。当用户订阅的音视频流总数已达上限时，继续订阅更多流时会失败，同时通知用户订阅音视频流总数超过上限。
     */
    BRERR_OVER_SUBSCRIBE_LIMIT = -1070,

    /**
     * @brief 发布流失败，发布流总数超过上限。
     *        RTC 系统会限制单个房间内发布的总流数，总流数包括视频流、音频流和屏幕流。如果房间内发布流数已达上限时，本地用户尝试向房间中发布流时会失败，SDK通过回调此错误通知用户。
     */
    BRERR_OVER_STREAM_PUBLISH_LIMIT = -1080,

    /**
     * @brief 发布屏幕流失败，发布流总数超过上限。
     *        RTC 系统会限制单个房间内发布的总流数，总流数包括视频流、音频流和屏幕流。如果房间内发布流数已达上限时，本地用户尝试向房间中发布流时会失败，SDK通过回调此错误通知用户。
     */
    BRERR_OVER_SCREEN_PUBLISH_LIMIT = -1081,

    /**
     * @brief 发布视频流总数超过上限。
     *        RTC 系统会限制单个房间内发布的视频流数。如果房间内发布视频流数已达上限时，本地用户尝试向房间中发布视频流时会失败，SDK通过回调此错误通知用户。
     */
    BRERR_OVER_VIDEO_PUBLISH_LIMIT = -1082,
};

/**
 * @type errorcode
 * @brief 回调警告码。
 *        警告码说明 SDK 内部遇到问题正在尝试恢复。警告码仅作通知。
 */
enum RTC_WARN_CODE {
    /**
     * @hidden
     */
    BRWARN_GET_ROOM_FAILED = -2000,

    /**
     * @brief 加入房间失败。
     *        用户调用 JoinChannel{@link #JoinChannel}
     * 加入房间或由于网络状况不佳断网重连时，由于服务器错误导致用户加入房间失败。SDK 会自动重试加入房间。
     */
    BRWARN_JOIN_ROOM_FAILED = -2001,

    /**
     * @brief 发布音视频流失败。
     *        用户在所在房间中发布音视频流时，由于服务器错误导致发布失败。SDK 会自动重试发布。
     */
    BRWARN_PUBLISH_STREAM_FAILED = -2002,

    /**
     * @brief 订阅音视频流失败。
     *        当前房间中找不到订阅的音视频流导致订阅失败。建议用户退出重试。
     */
    BRWARN_SUBSCRIBE_STREAM_FAILED_404 = -2003,

    /**
     * @brief 订阅音视频流失败。
     *        用户订阅所在房间中的音视频流时，由于服务器错误导致订阅失败。SDK 会自动重试订阅。
     */
    BRWARN_SUBSCRIBE_STREAM_FAILED_5xx = -2004,

    /**
     * @hidden
     * @brief 函数调用顺序错误。
     */
    BRWARN_INVOKE_ERROR = -2005,

    /**
     * @hidden
     * @brief 调度异常，服务器返回的媒体服务器地址不可用。
     */
    BRWARN_INVALID_EXPECT_MS_ADDR = -2007,

    /**
     * @brief 用户手动订阅音视频流错误。
     *        自动订阅功能开启时，用户调用 SubscribeStream{@link #SubscribeStream} 方法手动订阅音视频流时触发此警告。
     */
    BRWARN_SUBSCRIBE_STREAM_FORBIDEN = -2010,

    /**
     * @brief 发送自定义广播消息失败，当前用户未在房间中。
     */
    BRWARN_SEND_CUSTOM_MESSAGE = -2011,

    /**
     * @brief 摄像头权限异常，当前应用没有获取摄像头权限
     */
    BRWARN_PERMISSION_CAMERA = -5001,

    /**
     * @brief 麦克风权限异常，当前应用没有获取麦克风权限
     */
    BRWARN_PERMISSION_MICROPHONE = -5002,

    /**
     * @brief 录音设备启动失败。
     *        启动录音设备失败，当前录音设备可能被其他应用占用。
     */
    BRWARN_ADM_RECORDING_START_FAIL = -5003,

    /**
     * @brief 播放设备启动失败警告
     *      可能由于系统资源不足，或参数错误
     */
    BRWARN_ADM_PLAYOUT_START_FAIL = -5004,

	/**
     * @brief 无可用录音设备
     *        启动录音设备失败，请插入可用的录音设备
     */
    BRWARN_ADM_NO_RECORDING_DEVICE = -5005,

    /**
     * @brief 无可用播放设备
     *        启动播放设备失败，请插入可用的播放设备
     */
    BRWARN_ADM_NO_PLAYOUT_DEVICE = -5006
};

/**
 * @hidden
 * @type keytype
 * @brief 直播推流转码功能错误码。
 *        用户调用 EnableLiveTranscoding{@link #EnableLiveTranscoding}
 * 方法启动直播推流转码功能后，服务端返回的执行结果。
 */
enum RTC_TRANSCODING_ERROR_CODE {
    /**
     *  @brief 推流成功。
     */
    TRANSCODING_ERR_OK = 0,
    /**
     *  @brief 推流参数错误。
     */
    TRANSCODING_ERR_INVALID_ARGUMENT = 1,
    /**
     *  @brief 后处理订阅流失败。
     */
    TRANSCODING_ERR_SUBSCRIBE_FAILED = 2,
    /**
     *  @brief 合流服务中间过程存在错误。
     */
    TRANSCODING_ERR_PROCESSING = 3,
    /**
     *  @brief 推 CDN 失败。
     */
    TRANSCODING_ERR_PUBLISH_STREAM_CDN_ERROR = 4,
};

/**
 * @type keytype
 * @brief 事务检查码。  <br>
 *        用户调用 SetBusinessId{@link #SetBusinessId} 方法设置业务标识参数的返回错误码。  <br>
 */
enum BusinessCheckCode {
    /**
     * @brief 用户已经在房间中。  <br>
     *        业务标识需要在加入房间之前设置，加入后设置无效。  <br>
     */
    ERROR_ALREADY_IN_ROOM = -6001,

    /**
     * @brief 输入参数非法。  <br>
     *        用户传入的业务标识参数非法，参数合法性参考 SetBusinessId{@link #SetBusinessId} 方法的参数说明。  <br>
     */
    ERROR_INPUT_INVALIDATE = -6002,
};

/**
 * @type keytype
 * @brief 本地音频流状态。
 *        SDK 通过 OnLocalAudioStateChanged{@link #OnLocalAudioStateChanged} 回调本地音频流状态
 */
enum LocalAudioStreamState {
    /**
     * @brief 本地音频默认初始状态。
     *        麦克风停止工作时回调该状态，对应错误码 kLocalAudioStreamErrorOk{@link #kLocalAudioStreamErrorOk}
     */
    kLocalAudioStreamStateStopped = 0,

    /**
     * @brief 本地音频录制设备启动成功。
     *        采集到音频首帧时回调该状态，对应错误码 kLocalAudioStreamErrorOk{@link #kLocalAudioStreamErrorOk}
     */
    kLocalAudioStreamStateRecording,

    /**
     * @brief 本地音频首帧编码成功。
     *        音频首帧编码成功时回调该状态，对应错误码 kLocalAudioStreamErrorOk{@link #kLocalAudioStreamErrorOk}
     */
    kLocalAudioStreamStateEncoding,

    /**
     * @brief  本地音频启动失败，在以下时机回调该状态：  <br>
     *       + 本地录音设备启动失败，对应错误码 kLocalAudioStreamErrorRecordFailure{@link #kLocalAudioStreamErrorRecordFailure}  <br>
     *       + 检测到没有录音设备权限，对应错误码 kLocalAudioStreamErrorDeviceNoPermission{@link #kLocalAudioStreamErrorDeviceNoPermission}  <br>
     *       + 音频编码失败，对应错误码 kLocalAudioStreamErrorEncodeFailure{@link #kLocalAudioStreamErrorEncodeFailure}  <br>
     */
    kLocalAudioStreamStateFailed,
};

/**
 * @type keytype
 * @brief 本地音频流状态改变时的错误码。
 *        SDK 通过 OnLocalAudioStateChanged{@link #OnLocalAudioStateChanged} 回调该错误码。
 */
enum LocalAudioStreamError {
    /**
     * @brief 本地音频状态正常
     */
    kLocalAudioStreamErrorOk = 0,
    /**
     * @brief 本地音频出错原因未知
     */
    kLocalAudioStreamErrorFailure,
    /**
     * @brief 没有权限启动本地音频录制设备
     */
    kLocalAudioStreamErrorDeviceNoPermission,
    /**
     * @brief 本地音频录制设备已经在使用中
     * @notes 该错误码暂未使用
     */
    kLocalAudioStreamErrorDeviceBusy,
    /**
     * @brief 本地音频录制失败，建议你检查录制设备是否正常工作
     */
    kLocalAudioStreamErrorRecordFailure,
    /**
     * @brief 本地音频编码失败
     */
    kLocalAudioStreamErrorEncodeFailure,
    /**
     *@brief 没有可用的音频录制设备
     */
    kLocalAudioStreamErrorNoRecordingDevice
};

/**
 * @type keytype
 * @brief 本地视频流状态
 */
enum LocalVideoStreamState {

    /**
     * @brief 本地视频采集停止状态
     */
    kLocalVideoStreamStateStopped = 0,

    /**
     * @brief 本地视频采集设备启动成功
     */
    kLocalVideoStreamStateRecording,
    /**
     * @brief 本地视频采集后，首帧编码成功
     */
    kLocalVideoStreamStateEncoding,
    /**
     * @brief 本地视频启动失败
     */
    kLocalVideoStreamStateFailed,
};

/**
 * @type errorcode
 * @brief 本地视频状态改变时的错误码
 */
enum LocalVideoStreamError {
    /**
     * @brief 状态正常
     */
    kLocalVideoStreamErrorOk = 0,

    /**
     * @brief 本地视频流发布失败
     */
    kLocalVideoStreamErrorFailure,

    /**
     * @brief 没有权限启动本地视频采集设备
     */
    kLocalVideoStreamErrorDeviceNoPermission,

    /**
     * @brief 本地视频采集设备被占用
     */
    kLocalVideoStreamErrorDeviceBusy,

    /**
     * @brief 本地视频采集设备不存在或已移除
     */
    kLocalVideoStreamErrorDeviceNotFound,

    /**
     * @brief 本地视频采集失败，建议检查采集设备是否正常工作
     */
    kLocalVideoStreamErrorCaptureFailure,

    /**
     * @brief 本地视频编码失败
     */
    kLocalVideoStreamErrorEncodeFailure,
};

/**
 * @type keytype
 * @brief 远端音频流状态。<br>
 *        用户可以通过 OnRemoteAudioStateChanged{@link #OnRemoteAudioStateChanged} 了解该状态。
 */
enum RemoteAudioState {

    /**
     * @brief  不接收远端音频流。 <br>
     *         以下情况下会触发回调 OnRemoteAudioStateChanged{@link #OnRemoteAudioStateChanged}：  <br>
     *       + 本地用户停止接收远端音频流，对应原因是：kRemoteAudioReasonLocalMuted{@link #RemoteAudioStateReason}  <br>
     *       + 远端用户停止发送音频流，对应原因是：kRemoteAudioReasonRemoteMuted{@link #RemoteAudioStateReason}  <br>
     *       + 远端用户离开房间，对应原因是：kRemoteAudioReasonRemoteOffline{@link #RemoteAudioStateReason}  <br>
     */
    kRemoteAudioStateStopped = 0,
    /**
     * @brief 开始接收远端音频流首包。<br>
     *        刚收到远端音频流首包会触发回调 OnRemoteAudioStateChanged{@link #OnRemoteAudioStateChanged}，
     *        对应原因是： kRemoteAudioReasonLocalUnmuted{@link #RemoteAudioStateReason}。
     */
    kRemoteAudioStateStarting,

    /**
     * @brief  远端音频流正在解码，正常播放。 <br>
     *         以下情况下会触发回调 OnRemoteAudioStateChanged{@link #OnRemoteAudioStateChanged}：  <br>
     *       + 成功解码远端音频首帧，对应原因是：kRemoteAudioReasonLocalUnmuted{@link #RemoteAudioStateReason}  <br>
     *       + 网络由阻塞恢复正常，对应原因是：kRemoteAudioReasonNetworkRecovery{@link #RemoteAudioStateReason}  <br>
     *       + 本地用户恢复接收远端音频流，对应原因是：kRemoteAudioReasonLocalUnmuted{@link #RemoteAudioStateReason}  <br>
     *       + 远端用户恢复发送音频流，对应原因是：kRemoteAudioReasonRemoteUnmuted{@link #RemoteAudioStateReason}  <br>
     */
    kRemoteAudioStateDecoding,

    /**
     * @brief 远端音频流卡顿。<br>
     *        网络阻塞、丢包率大于 40% 时，会触发回调 OnRemoteAudioStateChanged{@link #OnRemoteAudioStateChanged}，
     *        对应原因是：kRemoteAudioReasonNetworkCongestion{@link #RemoteAudioStateReason}
     */
    kRemoteAudioStateFrozen,

    /**
     * @hidden
     * @brief 远端音频流播放失败
     * @notes 该错误码暂未使用
     */
    kRemoteAudioStateFailed,
};

/**
 * @type keytype
 * @brief 接收远端音频流状态改变的原因。<br>
 *        用户可以通过 OnRemoteAudioStateChanged{@link #OnRemoteAudioStateChanged} 了解该原因。
 */
enum RemoteAudioStateReason {
    /**
     * @brief 内部原因
     */
    kRemoteAudioReasonInternal = 0,
    /**
     * @brief 网络阻塞
     */
    kRemoteAudioReasonNetworkCongestion,
    /**
     * @brief 网络恢复正常
     */
    kRemoteAudioReasonNetworkRecovery,
    /**
     * @brief 本地用户停止接收远端音频流
     */
    kRemoteAudioReasonLocalMuted,
    /**
     * @brief 本地用户恢复接收远端音频流
     */
    kRemoteAudioReasonLocalUnmuted,
    /**
     * @brief 远端用户停止发送音频流
     */
    kRemoteAudioReasonRemoteMuted,
    /**
     * @brief 远端用户恢复发送音频流
     */
    kRemoteAudioReasonRemoteUnmuted,
    /**
     * @brief 远端用户离开房间
     */
    kRemoteAudioReasonRemoteOffline,
};

/**
 * @type keytype
 * @brief 远端视频流状态
 */
enum RemoteVideoState {
    /**
     * @brief 远端视频流默认初始状态，视频尚未开始播放。
     */
    kRemoteVideoStateStopped = 0,
    /**
     * @brief 本地用户已接收远端视频流首包。状态改变时，会收到回调：OnRemoteVideoStateChanged{@link #OnRemoteVideoStateChanged}
     */
    kRemoteVideoStateStarting,
    /**
     * @brief 远端视频流正在解码，正常播放。状态改变时，会收到回调：OnRemoteVideoStateChanged{@link #OnRemoteVideoStateChanged}
     */
    kRemoteVideoStateDecoding,
    /**
     * @brief 远端视频流卡顿，可能有网络等原因。状态改变时，会收到回调：OnRemoteVideoStateChanged{@link #OnRemoteVideoStateChanged}
     */
    kRemoteVideoStateFrozen,
    /**
     * @brief 远端视频流播放失败。状态改变时，会收到回调：OnRemoteVideoStateChanged{@link #OnRemoteVideoStateChanged}
     */
    kRemoteVideoStateFailed,
};

/**
 * @type keytype
 * @brief 远端视频流状态改变的原因
 */
enum RemoteVideoStateReason {
    /**
     * @brief 内部原因
     */
    kRemoteVideoReasonInternal = 0,
    /**
     * @brief 网络阻塞
     */
    kRemoteVideoReasonNetworkCongestion,
    /**
     * @brief 网络恢复正常
     */
    kRemoteVideoReasonNetworkRecovery,
    /**
     * @brief 本地用户停止接收远端视频流或本地用户禁用视频模块
     */
    kRemoteVideoReasonLocalMuted,
    /**
     * @brief 本地用户恢复接收远端视频流或本地用户启用视频模块
     */
    kRemoteVideoReasonLocalUnmuted,
    /**
     * @brief 远端用户停止发送视频流或远端用户禁用视频模块
     */
    kRemoteVideoSReasonRemoteMuted,
    /**
     * @brief 远端用户恢复发送视频流或远端用户启用视频模块
     */
    kRemoteVideoReasonRemoteUnmuted,
    /**
     * @brief 远端用户离开频道。
     *        状态转换参考 OnStreamRemove{@link #OnStreamRemove}
     */
    kRemoteVideoReasonRemoteOffline,
};

/**
 * @type keytype
 * @brief 背景模式
 *      开启背景替换功能时生效，详见ReplaceBackground{@link #ReplaceBackground}。
 */
enum BACKGROUND_MODE {
    /**
     *@brief 无
     */
    NONE = 0,
    /**
     *@brief 虚化
     */
    BLUR = 1,
    /**
     *@brief 背景1
     */
    BACKGROUND_A = 2,
    /**
     *@brief 背景2
     */
    BACKGROUND_B = 3,
};

/**
 * @type keytype
 * @brief 分割模型
 *      开启背景替换功能时生效，详见ReplaceBackground{@link #ReplaceBackground}。
 */
enum DIVIDE_MODEL {
    /**
     *@brief 自研
     */
    DEFAULT = 0,
    /**
     *@brief effect
     */
    EFFECT = 1,
};

/**
 * @type keytype
 * @brief 房间内的用户 ID, 及其在房间内发送音量。
 */
struct AudioVolumeInfo {
    /**
     * @brief 该用户在房间内发送音频的音量大小，取值范围为：[0,255]
     */
    unsigned int volume;
    /**
     * @brief 用户 ID
     */
    const char* uid;
};

/**
 * @type keytype
 * @brief 性能回退相关数据
 */
struct SourceWantedData {
    /**
     * @brief 推荐视频输入宽
     */
    int width;
    /**
     * @brief 推荐视频输入高
     */
    int height;
    /**
     * @brief 推荐视频输入帧率，单位 fps
     */
    int frame_rate;
};

/**
 * @type keytype
 * @brief 通话相关的统计信息
 */
struct RtcStats {
    /**
     * @brief 通话时长，单位为秒，累计值
     */
    unsigned int duration;
    /**
     * @brief 发送字节数 (bytes)，累计值
     */
    unsigned int tx_bytes;
    /**
     * @brief 接收字节数 (bytes)，累计值
     */
    unsigned int rx_bytes;
    /**
     * @brief 发送码率 (kbps)，瞬时值
     */
    unsigned short tx_kbitrate;
    /**
     * @brief 接收码率 (kbps)，瞬时值
     */
    unsigned short rx_kbitrate;
    /**
     * @brief 音频接收码率 (kbps)，瞬时值
     */
    unsigned short rx_audio_kbitrate;
    /**
     * @brief 音频发送码率 (kbps)，瞬时值
     */
    unsigned short tx_audio_kbitrate;
    /**
     * @brief 视频接收码率 (kbps)，瞬时值
     */
    unsigned short rx_video_kbitrate;
    /**
     * @brief 视频发送码率 (kbps)，瞬时值
     */
    unsigned short tx_video_kbitrate;
    /**
     * @brief 当前房间内的用户人数
     */
    unsigned int user_count;
    /**
     * @brief 当前应用程序的 CPU 使用率，暂未被使用
     */
    double cpu_app_usage;
    /**
     * @brief 当前系统的 CPU 使用率 (%)，暂未被使用
     */
    double cpu_total_usage;
};

/**
 * @type keytype
 * @brief 远端音频流统计信息。  <br>
 *        本地用户订阅远端音频流成功后，SDK 会周期性（2s）的通过 OnRemoteAudioStats{@link #OnRemoteAudioStats} 回调事件通知用户订阅的音频流在此次统计周期内的状况。此数据结构即为回调给用户的参数类型。  <br>
 */
struct RemoteAudioStats {
    /**
     * @brief 用户ID 。远端音频流发布用户的用户ID 。  <br>
     */
    const char* uid;
    /**
     * @brief 音频丢包率。统计周期内的音频下行丢包率，取值范围为 [0, 1] 。  <br>
     */
    float audio_loss_rate;
    /**
     * @brief 接收码率。统计周期内的音频接收码率，单位为 kbps 。  <br>
     */
    int received_kbitrate;
    /**
     * @brief 音频卡顿次数。统计周期内的卡顿次数。  <br>
     */
    int stall_count;
    /**
     * @brief 音频卡顿时长。统计周期内的卡顿时长，单位为 ms 。  <br>
     */
    int stall_duration;
    /**
     *@brief 用户体验级别的端到端延时。从发送端采集完成编码开始到接收端解码完成渲染开始的延时，单位为 ms 。  <br>
     */
    long e2e_delay;
    /**
     * @brief 播放采样率。统计周期内的音频播放采样率信息，单位为 Hz 。  <br>
     */
    int playout_sample_rate;
    /**
     * @brief 统计间隔。此次统计周期的间隔，单位为 ms 。  <br>
     */
    int stats_interval;
    /**
     * @brief 往返时延。单位为 ms 。  <br>
     */
    int rtt;
    /**
     * @brief 远端用户发送的音频流质量。值含义参考 NetworkQuality{@link #NetworkQuality} 。  <br>
     */
    int quality;
    /**
     * @brief 音频发送端到接收端的网络延迟。单位为 ms 。  <br>
     */
    int jitter_buffer_delay;
    /**
     * @brief 音频声道数。  <br>
     */
    int num_channels;
    /**
     * @brief 音频接收采样率。统计周期内接收到的远端音频采样率信息，单位为 Hz 。  <br>
     */
    int received_sample_rate;
    /**
     * @brief 远端用户在加入房间后发生音频卡顿的累计时长占音频总有效时长的百分比。  <br>
     */
    int frozen_rate;
    /**
     * @brief 音频 PLC 样点总个数。  <br>
     */
    int concealed_samples;
    /**
     * @brief PLC 累计次数。  <br>
     */
    int concealment_event;
    /**
     * @brief 音频解码采样率。统计周期内的音频解码采样率信息，单位为 Hz 。  <br>
     */
    int dec_sample_rate;
    /**
     * @brief 解码时长。单位为 s 。  <br>
     */
    int dec_duration;
};

/**
 * @type keytype
 * @brief 本地音频流统计信息。  <br>
 *        本地用户发布音频流成功后，SDK 会周期性（2s）的通过 OnLocalAudioStats{@link #OnLocalAudioStats} 回调事件通知用户发布的音频流在此次统计周期内的状况。此数据结构即为回调给用户的参数类型。  <br>
 */
struct LocalAudioStats {
    /**
     * @brief 音频丢包率。此次统计周期内的音频上行丢包率，取值范围为 [0, 1] 。  <br>
     */
    float audio_loss_rate;
    /**
     * @brief 发送的码率。此次统计周期内的音频发送码率，单位为 kbps 。  <br>
     */
    int send_kbitrate;
    /**
     * @brief 采集采样率。音频采集采样率信息，单位为 Hz 。  <br>
     */
    int record_sample_rate;
    /**
     * @brief 统计间隔。此次统计周期的间隔，单位为 ms 。  <br>
     */
    int stats_interval;
    /**
     * @brief 往返时延。单位为 ms 。  <br>
     */
    int rtt;
    /**
     * @brief 音频声道数。  <br>
     */
    int num_channels;
    /**
     * @brief 发送采样率。音频发送采样率信息，单位为 Hz 。  <br>
     */
    int sent_sample_rate;
};

/**
 * @type keytype
 * @brief 流属性。房间中的远端流的流属性。  <br>
 */
struct ByteStream {
    /**
     * @brief 发布此流的用户 ID 。
     */
    const char* user_id;
    /**
     * @brief 此流是否为共享屏幕流。
     */
    bool is_screen;
    /**
     * @brief 此流是否包括视频流。
     */
    bool has_video;
    /**
     * @brief 流是否包括音频流。
     */
    bool has_audio;
    /**
     * @brief 视频流的属性。  <br>
     *        当远端用户调用 SetVideoProfiles{@link #SetVideoProfiles} 方法发布多个配置的视频流时，此处会包含这个用户发布的所有视频流的属性信息。
     *        参看 VideoSolutionDescription{@link #VideoSolutionDescription}。
     */
    VideoSolutionDescription* profiles;
    /**
     * @brief 不同配置流的个数。  <br>
     *        当远端用户调用 SetVideoProfiles{@link #SetVideoProfiles} 方法发布多个配置的视频流时，此处会包含这个用户发布的视频流的数目。
     */
    int profile_count;
};

/**
 * @type keytype
 * @brief 订阅流的参数配置。用户手动订阅一路音视频流所使用的订阅配置参数。  <br>
 *        用户开启手动订阅功能时，通过调用 SubscribeStream{@link #SubscribeStream} 方法订阅音视频流，调用时传入的参数即为此数据类型。  <br>
 */
struct SubscribeConfig {
    /**
     * @brief 是否是屏幕流。  <br>
     *        用户通过设置此参数，选择是否订阅远端流中的视频。true 为订阅视频，false 为不订阅视频，默认值为 true 。  <br>
     */
    bool is_screen = false;
    /**
     * @brief 是否订阅视频。  <br>
     *        用户通过设置此参数，选择是否订阅远端流中的视频。true 为订阅视频，false 为不订阅视频，默认值为 true 。  <br>
     */
    bool sub_video;
    /**
     * @brief 是否订阅音频。  <br>
     *        用户通过设置此参数，选择是否订阅远端流中的音频。true 为订阅音频，false 为不订阅音频，默认值为 true 。  <br>
     */
    bool sub_audio;
    /**
     * @brief 订阅的视频流分辨率下标。  <br>
     *        用户可以通过调用 SetVideoProfiles{@link #SetVideoProfiles} 方法在一路流中发布多个不同分辨率的视频。因此订阅流时，需要指定订阅的具体分辨率。此参数即用于指定需订阅的分辨率的下标，默认值为 0 。  <br>
     */
    int video_index;
    /**
     * @brief 远端用户的需求优先级，取值详见枚举类型 RemoteUserPriority{@link #RemoteUserPriority} ，默认值为 0 。  <br>
     *        用户通过此参数设置远端用户的需求优先级。当开启了订阅流回退选项功能（详见 SetSubscribeFallbackOption{@link #SetSubscribeFallbackOption} 方法），弱网或性能不足时会优先保证收到的高优先级用户的流的质量。  <br>
     */
    int priority = 0;

public:
    /**
     * @hidden
     * @brief 构造函数
     */
    SubscribeConfig() : is_screen(false), sub_video(true), sub_audio(true), video_index(0), priority(0) {
    }

    /**
     * @hidden
     * @brief 构造函数
     */
    SubscribeConfig(bool is_screen, bool subvideo, bool subaudio, int videoindex)
            : is_screen(is_screen), sub_video(subvideo), sub_audio(subaudio), video_index(videoindex) {
    }

    /**
     * @hidden
     * @brief 构造函数
     */
    SubscribeConfig(bool is_screen, bool subvideo, bool subaudio, int videoindex, int priority)
            : is_screen(is_screen),
              sub_video(subvideo),
              sub_audio(subaudio),
              video_index(videoindex),
              priority(priority) {
    }

    /**
     * @hidden
     */
    bool operator==(const SubscribeConfig& config) const {
        bool result = is_screen == config.is_screen && sub_video == config.sub_video && sub_audio == config.sub_audio &&
                      video_index == config.video_index && priority == config.priority;
        ;
        return result;
    }

    /**
     * @hidden
     */
    bool operator!=(const SubscribeConfig& config) const {
        bool result = (*this == config);
        return !result;
    }
};

#ifndef BYTERTC_AUDIO_ONLY
/**
 * @type keytype
 * @brief 音视频质量反馈问题类型
 */
enum PROBLEM_FEEDBACK {
    /**
     * @brief 没有问题
     */
    PROBLEM_NONE = 0,
    /**
     * @brief 其他问题
     */
    PROBLEM_OTHER_MSG = (1 << 0),
    /**
     * @brief 声音不清晰
     */
    PROBLEM_AUDIO_NOT_CLEAR = (1 << 1),
    /**
     * @brief 视频不清晰
     */
    PROBLEM_VIDEO_NOT_CLEAR = (1 << 2),
    /**
     * @brief 音视频不同步
     */
    PROBLEM_SYNC = (1 << 3),
    /**
     * @brief 音频卡顿
     */
    PROBLEM_AUDIO_LAGGING = (1 << 4),
    /**
     * @brief 视频卡顿
     */
    PROBLEM_VIDEO_LAGGING = (1 << 5),
    /**
     * @brief 无法连接
     */
    PROBLEM_CONNECT_FAILED = (1 << 6),
    /**
     * @brief 音频延迟
     */
    PROBLEM_AUDIO_DELAY = (1 << 7),
    /**
     * @brief 视频延迟
     */
    PROBLEM_VIDEO_DELAY = (1 << 8),
    /**
     * @brief 连接断开
     */
    PROBLEM_DISCONNECT = (1 << 9),
    /**
     * @brief 无声音
     */
    PROBLEM_NO_AUDIO = (1 << 10),
    /**
     * @brief 无画面
     */
    PROBLEM_NO_VIDEO = (1 << 11),
    /**
     * @brief 声音过大或过小
     */
    PROBLEM_AUDIO_STRENGTH = (1 << 12),
    /**
     * @brief 回声噪音
     */
    PROBLEM_ECHO = (1 << 13),
};

/**
 * @type keytype
 * @brief 远端视频类型
 *      目前C++ sdk 只支持 REMOTE_VIDEO_STREAM_HIGH 类型
 */
enum REMOTE_VIDEO_STREAM_TYPE {
    /**
     * @brief 高分辨率视频流
     */
    REMOTE_VIDEO_STREAM_HIGH = 0,
    /**
     * @brief 低分辨率视频
     */
    REMOTE_VIDEO_STREAM_LOW = 1,
};

/**
 * @type keytype
 * @brief 画布信息和渲染模式。<br>
 *        你应使用 SetLocalVideoCanvas{@link #SetLocalVideoCanvas} 将视频流绑定到本地视图。
 */
struct VideoCanvas {
    /**
     * @brief 本地视图句柄
     */
    void* view;
    /**
     * @brief 渲染模式，参见 RENDER_MODE_TYPE{@link #RENDER_MODE_TYPE}
     */
    int render_mode;
    /**
     * @brief 视图对应的用户 ID
     */
    const char* uid;
    /**
     * @brief 你的自定义数据，SDK 透传该数据。
     */
    void* priv;
    /**
     * @hidden
     * @brief 构造函数
     */
    VideoCanvas() : view(NULL), render_mode(RENDER_MODE_HIDDEN), uid(0), priv(NULL) {
    }
    /**
     * @hidden
     * @brief 构造函数
     */
    VideoCanvas(void* v, int m, const char* u) : view(v), render_mode(m), uid(u), priv(NULL) {
    }
};

/**
 * @type keytype
 * @brief 远端用户通话视频相关的统计信息
 */
struct RemoteVideoStats {
    /**
     * @brief 用户 id
     */
    const char* uid;
    /**
     * @brief 视频宽度
     */
    int width;
    /**
     * @brief 视频高度
     */
    int height;
    /**
     * @brief 视频丢包率，百分比
     */
    float video_loss_rate;
    /**
     * @brief 接收码率，单位为 kbps
     */
    int received_kbitrate;
    /**
     * @brief 解码器输出帧率，单位 fps
     */
    int decoder_output_frame_rate;
    /**
     * @brief 渲染帧率，单位 fps
     */
    int renderer_output_frame_rate;
    /**
     * @brief 卡顿次数
     */
    int stall_count;
    /**
     * @brief 卡顿时长，单位毫秒
     */
    int stall_duration;
    /**
     * @brief 用户体验级别的端到端延时，从发送端采集完成编码开始到接收端解码完成渲染开始的延时，单位为毫秒
     */
    long e2e_delay;
    /**
     * @brief 是否是屏幕流
     */
    bool is_screen;
    /**
     * @brief 统计间隔，单位为毫秒
     */
    int stats_interval;
    /**
     * @brief 往返时延，单位为毫秒
     */
    int rtt;
    /**
     * @brief 远端用户在加入房间后发生视频卡顿的累计时长占视频总有效时长的百分比 (%)。
     */
    int frozen_rate;
    /**
     * @brief 对应多种分辨率的流的下标，详见 VideoSolutionDescription{@link #VideoSolutionDescription}
     */
    int video_index;
};

/**
 * @type keytype
 * @brief 本地视频相关的统计信息
 */
struct LocalVideoStats {
    /**
     * @brief 发送码率，单位为 kbps
     */
    int sent_kbitrate;
    /**
     * @brief 采集帧率，单位 fps
     */
    int input_frame_rate;
    /**
     * @brief 发送帧率，单位 fps
     */
    int sent_frame_rate;
    /**
     * @brief 编码器输出帧率，单位 fps
     */
    int encoder_output_frame_rate;
    /**
     * @brief 本地渲染帧率，单位 fps
     */
    int renderer_output_frame_rate;
    /**
     * @brief 目标发送码率（kbps）
     */
    int target_kbitrate;
    /**
     * @brief 目标发送帧率，单位 fps
     */
    int target_frame_rate;
    /**
     * @brief 统计间隔，单位毫秒
     */
    int stats_interval;
    /**
     * @brief 视频丢包率，单位百分比
     */
    float video_loss_rate;
    /**
     * @brief 往返时延，单位为毫秒
     */
    int rtt;
    /**
     * @brief 视频编码码率（kbps）
     */
    int encoded_bitrate;
    /**
     * @brief 视频编码宽度（px)
     */
    int encoded_frame_width;
    /**
     * @brief 视频编码高度（px）
     */
    int encoded_frame_height;
    /**
     * @brief 视频发送的帧数，累计值
     */
    int encoded_frame_count;
    /**
     * @brief 视频的编码类型，具体参考 VideoCodecType{@link #VideoCodecType}
     */
    VideoCodecType codec_type;
    /**
     * @brief 本地流是否是屏幕流
     */
    bool is_screen;
};

#endif  // BYTERTC_AUDIO_ONLY

/**
 * @type keytype
 * @brief cpu和memory使用率信息
 */
struct SysStats {
    /**
     * @brief 当前系统的cpu使用率
     */
    double cpu_total_usage;
    /**
     * @brief 当前本app占用的cpu使用率
     */
    double cpu_app_usage;
    /**
     * @brief 当前本app占用的内存大小
     */
    double memory_usage;
};

/**
 * @type keytype
 * @brief windows 窗口 id, windows 平台下传 windows 窗口句柄
 */
typedef void* view_t;

/**
 * @type keytype
 * @brief 矩形，用于屏幕共享指定区域
 */
struct Rectangle {
    /**
     * @brief 矩形左上角x坐标
     */
    int x = 0;
    /**
     * @brief 矩形左上角y坐标
     */
    int y = 0;
    /**
     * @brief 矩形宽度
     */
    int width = 0;
    /**
     * @brief 矩形高度
     */
    int height = 0;
};

/**
 * @type keytype
 * @brief 高亮边框标识屏幕共享指定区域
 */
struct HighlightConfig {
    /**
     * @brief 是否显示高亮边框，默认显示。
     */
    bool enable_highlight = true;
    /**
     * @brief 边框的颜色, 颜色格式为十六进制 ARGB:  0xAARRGGBB
     */
    uint32_t border_color = 0xFF29CCA3;
    /**
     * @brief 边框的宽度
     */
    int border_width = 4;
};

/**
 * @type keytype
 * @brief 屏幕共享的编码参数配置
 */
struct DesktopCaptureParameters {
    /**
     * @brief 屏幕采集编码最大宽度
     */
    int max_width = 1920;
    /**
     * @brief 屏幕采集编码最大高度
     */
    int max_height = 1080;
    /**
     * @brief 屏幕采集编码帧率, 单位 fps
     */
    int frame_rate = 15;
    /**
     * @brief 屏幕采集编码码率, -1 为自动码率, SDK 会根据宽高信息选择合适的码率，单位 kbps
     */
    int bitrate = -1;
    /**
     * @brief 是否捕获鼠标光标
     */
    bool capture_mouse_cursor = true;
    /**
     * @brief 抓取屏幕时排除窗口列表。这个参数仅在抓取屏幕时生效。
     */
    view_t * excluded_window_list = nullptr;
    int excluded_window_num = 0;
    /**
     * @brief 高亮边框的配置
     */
    HighlightConfig highlight_config;
};

/**
 * @type keytype
 * @region 视频管理
 * @brief 视频流类型
 */
enum ByteStreamType {
    /**
     * @brief 视频流类型为相机流
     */
    kByteStreamTypeCamera,
    /**
     * @brief 视频流类型为屏幕流
     */
    kByteStreamTypeScreen
};

/**
 * @type keytype
 * @region 视频管理
 * @brief 视频流信息
 */
struct ByteStreamInfo {
    /**
     * @brief 房间id，每个房间的唯一标识符。相同 AppId 并且进入同一个房间内的用户，可以进行相互音视频通话
     */
    const char* room_id;
    /**
     * @brief 用户id，每个用户的唯一标识符。同一个房间，不允许两个相同 UserId 存在，后进房者会踢出前者。
     */
    const char* user_id;
    /**
     * @brief 视频流类型，详见ByteStreamType{@link #ByteStreamType}
     */
    ByteStreamType stream_type;
};

/**
* @type keytype
* @brief 音频处理策略等级。 <br>
*        你可以设置音频处理策略等级。参看 SetAudioPerformanceProfile{@link #SetAudioPerformanceProfile}。
* @notes 如果以下策略无法满足需求，请联系技术支持人员实现自定义配置。
*/
enum class AudioPerformanceProfile {
    /**
     * @brief 自动策略。根据应用所在机型等级，自动适配音频处理策略。
    */
    kAudioPerformanceProfileAuto = 0,
    /**
     * @brief 低配策略。关闭 AEC、ANS、AGC 算法，音频采样率设置为 16000。
    */
    kAudioPerformanceProfileLow = 1,
    /**
     * @brief 中配策略。开启 AEC、ANS、AGC 算法，音频采样率设置为 16000。
    */
    kAudioPerformanceProfileMid = 2,
    /**
     * @brief 高配策略。开启 AEC、ANS、AGC 算法，音频采样率设置为 48000。
    */
    kAudioPerformanceProfileHigh = 3,
};


/**
 * @type keytype
 * @brief 自定义加密类型  <br>
 */
enum ByteEngineEncryptType {
    /**
     * @brief 使用自定义加密或不加密  <br>
     */
    ByteEngineEncryptTypeCustomize = 0,
    /**
     * @brief 使用AES-128-CBC加密  <br>
     */
    ByteEngineEncryptTypeAES128CBC = 1,
    /**
     * @brief 使用AES-256-CBC加密  <br>
     */
    ByteEngineEncryptTypeAES256CBC = 2,
    /**
     * @brief 使用AES-128-ECB加密  <br>
     */
    ByteEngineEncryptTypeAES128ECB = 3,
    /**
     * @brief 使用AES-256-ECB加密  <br>
     */
    ByteEngineEncryptTypeAES256ECB = 4
};

/**
 * @type callback
 * @brief 加密/解密处理函数
 */
class IByteEngineEncryptHandler {
public:
    /**
     * @hidden
     * @brief 析构函数
     */
    virtual ~IByteEngineEncryptHandler() {
    }

    /**
     * @type callback
     * @region 加密
     * @brief 自定义加密的方法接口  <br>
     *        通过继承并实现该方法，可以扩展传输过程中的加密方法，详见 SetCustomizeEncryptHandler{@link #SetCustomizeEncryptHandler}  <br>
     * @param [in] data  <br>
     *        原始音视频帧数据  <br>
     * @param [in] length  <br>
     *        原始音视频帧数据的长度  <br>
     * @param [out] buf  <br>
     *        可供写入的加密后数据缓冲区  <br>
     * @param [out] buf_len  <br>
     *        buf_len 数据缓冲区的大小  <br>
     * @return
     *        加密后实际写入缓冲区的数据大小，0表示丢弃该帧  <br>
     * @notes
     *        返回的数据大小应控制在原始数据的90%~120%范围以内，不然将被丢弃  <br>
     */
    virtual unsigned int OnEncryptData(
            const unsigned char* data, unsigned int length, unsigned char* buf, unsigned int buf_len) = 0;

    /**
     * @type callback
     * @region 加密
     * @brief 自定义解密的方法接口  <br>
     *        通过继承并实现该方法，可以扩展传输过程中的解密方法，详见 SetCustomizeEncryptHandler{@link #SetCustomizeEncryptHandler}  <br>
     * @param [in] data  <br>
     *        加密过的音视频帧数据  <br>
     * @param [in] length  <br>
     *        加密过的音视频帧数据的长度  <br>
     * @param [out] buf  <br>
     *        可供写入的解密后数据缓冲区  <br>
     * @param [out] buf_len  <br>
     *        数据缓冲区的大小  <br>
     * @return
     *        解密后实际写入缓冲区的数据大小，0表示丢弃该帧  <br>
     * @notes
     *        返回的数据大小应控制在原始数据的90%~120%范围以内，不然将被丢弃  <br>
     */
    virtual unsigned int OnDecryptData(
            const unsigned char* data, unsigned int length, unsigned char* buf, unsigned int buf_len) = 0;
};

/**
 * @type keytype
 * @brief 音频混音文件播放状态。
 */
enum AudioMixingState {
    /**
     * @brief 混音播放状态，混音开始
     */
    kAudioMixingStatePlaying = 710,
    /**
     * @brief 混音播放状态，混音暂停
     */
    kAudioMixingStatePaused = 711,
    /**
     * @brief 混音播放状态，混音停止/播放结束
     */
    kAudioMixingStateStoped = 713,
    /**
     * @brief 混音播放状态，混音播放失败
     */
    kAudioMixingStateFailed = 714
};

/**
 * @type keytype
 * @brief 音频混音文件播放错误码。
 */
enum AudioMixingError {
    /**
     * @brief 混音错误码，正常
     */
    kAudioMixingErrorOk = 0,
    /**
     * @brief 混音错误码，失败
     */
    kAudioMixingErrorCanNotOpen = 701,
};

/**
 * @type callback
 * @region 视频管理
 * @brief 视频数据回调接口
 */
class IVideoSink {
public:
    /**
     * @type callback
     * @region 频道管理
     * @brief 启动渲染器。
     * @notes 在开启渲染功能的时候会回调这个方法。开发者可以在这个方法中启动渲染器。
     */
    virtual void OnStart() = 0;
    /**
     * @type callback
     * @region 视频管理
     * @brief 视频帧回调
     * @param IByteVideoFrame
     *        视频帧结构类，详见IByteVideoFrame{@link #IByteVideoFrame}
     * @return 返回值暂未使用
     */
    virtual bool OnFrame(IByteVideoFrame* videoFrame) = 0;
    /**
     * @type callback
     * @region 频道管理
     * @brief 停止渲染器。
     * @notes 在停止渲染功能的时候会回调这个方法。开发者可以在这个方法中停止渲染。
     */
    virtual void OnStop() = 0;
    /**
     * @type callback
     * @region 频道管理
     * @brief 释放渲染器。
     * @notes 通知开发者渲染器即将被废弃。在Release()返回之后，开发者就可以释放掉资源了。
     */
    virtual void Release() {
    }

    /**
     * @hidden
     * @brief 析构函数
     */
    virtual ~IVideoSink() = default;
};

/**
 * @type keytype
 * @region 房间管理
 * @brief 用户信息
 */
struct RtcUser {
    /**
     * 用户 id
     */
    const char* user_id;
    /**
     * 元数据
     */
    const char* meta_data;
};

/**
 * @type keytype
 * @region 房间管理
 * @brief 首帧发送状态
 */
enum FirstFrameSendState {
    /**
     * @brief 发送中
     */
    kFirstFrameSendStateSending = 0,
    /**
     * @brief 发送成功
     */
    kFirstFrameSendStateSent = 1,
    /**
     * @brief 发送失败
     */
    kFirstFrameSendStateEnd = 2,
};

/**
 * @type keytype
 * @region 房间管理
 * @brief 首帧播放状态
 */
enum FirstFramePlayState {
    /**
     * @brief 播放中
     */
    kFirstFramePlayStatePlaying = 0,
    /**
     * @brief 播放成功
     */
    kFirstFramePlayStatePlayed = 1,
    /**
     * @brief 播放失败
     */
    kFirstFramePlayStateEnd = 2,
};

/**
 * @type keytype
 * @brief 是否开启镜像模式
 */
enum MirrorMode {
    /**
     * @brief 不开启
     */
    kMirrorModeOff = 0,
    /**
     * @brief 开启
     */
    kMirrorModeOn = 1,
};

/**
 * @type keytype
 * @brief 停止/启动发送音/视频流的状态
 */
enum MuteState {
    /**
     * @brief 启动发送音/视频流的状态
     */
    kMuteStateOff = 0,
    /**
     * @brief 停止发送音/视频流的状态
     */
    kMuteStateOn = 1,
};

/**
 * @type keytype
 * @region 房间管理
 * @brief 流属性
 */
enum StreamIndex {
    /**
     * @brief 主流。<br>
     *        包括：<br>
     *        + 通过默认摄像头/麦克风采集到的视频/音频; <br>
     *        + 通过自定义设备采集到的视频/音频。
     */
    kStreamIndexMain = 0,
    /**
     * @brief 屏幕流。 <br>
     *        屏幕共享时共享的视频流，或来自声卡的本地播放音频流。
     */
    kStreamIndexScreen = 1,
};

/**
 * @type keytype
 * @brief 远端流信息
 */
struct RemoteStreamKey {
    /**
     * @brief 房间 ID
     */
    const char *room_id;
    /**
     * @brief 用户 ID
     */
    const char *user_id;
    /**
     * @brief 流属性，主流或屏幕流。参看 StreamIndex{@link #StreamIndex}
     */
    StreamIndex stream_index;
};

/**
 * @type keytype
 * @brief 视频帧信息
 */
struct VideoFrameInfo {
    /**
     * @brief 宽（像素）
     */
    int width = 0;
    /**
     * @brief 高（像素）
     */
    int height = 0;
    /**
     * @brief 视频帧顺时针旋转角度。参看 VideoRotation{@link #VideoRotation}。
     */
    VideoRotation rotation = VideoRotation::VideoRotation_0;
};
}  // namespace bytertc
