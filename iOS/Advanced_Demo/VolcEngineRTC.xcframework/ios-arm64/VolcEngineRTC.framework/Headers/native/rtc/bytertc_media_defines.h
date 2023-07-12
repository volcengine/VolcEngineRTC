/*
 * Copyright (c) 2022 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC Stream Defines
 */

#pragma once

#include <stdint.h>
#include <stddef.h>

#include "bytertc_rts_defines.h"

namespace bytertc {
/** 
 * @type keytype
 * @brief 方法调用结果。
 */
enum ReturnStatus {
    /** 
     * @brief 成功。
     */
    kReturnStatusSuccess = 0,
    /** 
     * @brief 失败。
     */
    kReturnStatusFailure = -1,
    /** 
     * @brief 参数错误。
     */
    kReturnStatusParameterErr = -2,
    /** 
     * @brief 接口状态错误。
     */
    kReturnStatusWrongState = -3,
    /** 
     * @brief 失败，用户已在房间内。
     */
    kReturnStatusHasInRoom = -4,
    /** 
     * @brief 失败，用户已登录。
     */
    kReturnStatusHasInLogin = -5,
    /** 
     * @brief 失败，用户已经在进行通话回路测试中。
     */
    kReturnStatusHasInEchoTest = -6,
    /** 
     * @brief 失败，音视频均未采集。
     */
    kReturnStatusNeitherVideoNorAudio = -7,
    /** 
     * @brief 失败，该 roomId 已被使用。
     */
    kReturnStatusRoomIdInUse = -8,
    /** 
     * @brief 失败，屏幕流不支持。
     */
    kReturnStatusScreenNotSupport = -9,
    /** 
     * @brief 失败，没有音频帧。
     */
    kReturnStatusAudioNoFrame = -101,
    /** 
     * @brief 失败，未实现。
     */
    kReturnStatusAudioNotImplemented = -102,
    /** 
     * @brief 失败，采集设备无麦克风权限，尝试初始化设备失败。
     */
    kReturnStatusAudioNoPermission = -103,
    /** 
     * @brief 失败，设备不存在。当前没有设备或设备被移除时返回该值。
     */
    kReturnStatusAudioDeviceNotExists = -104,
    /** 
     * @brief 失败，设备音频格式不支持。
     */
    kReturnStatusAudioDeviceFormatNotSupport = -105,
    /** 
     * @brief 失败，系统无可用设备。
     */
    kReturnStatusAudioDeviceNoDevice = -106,
    /** 
     * @brief 失败，当前设备不可用，需更换设备。
     */
    kReturnStatusAudioDeviceCannotUse = -107,
    /** 
     * @brief 系统错误，设备初始化失败。
     */
    kReturnStatusAudioDeviceInitFailed = -108,
    /** 
     * @brief 系统错误，设备开启失败。
     */
    kReturnStatusAudioDeviceStartFailed = -109,
};

/** 
 * @type keytype
 * @brief 房间内远端流被移除的原因。  <br>
 */
enum StreamRemoveReason {
    /** 
     * @brief 远端用户停止发布流。  <br>
     */
    kStreamRemoveReasonUnpublish = 0,
    /** 
     * @brief 远端用户发布流失败。  <br>
     */
    kStreamRemoveReasonPublishFailed = 1,
    /** 
     * @brief 保活失败。  <br>
     */
    kStreamRemoveReasonKeepLiveFailed = 2,
    /** 
     * @brief 远端用户断网。  <br>
     */
    kStreamRemoveReasonClientDisconnected = 3,
    /** 
     * @brief 远端用户重新发布流。  <br>
     */
    kStreamRemoveReasonRepublish = 4,
    /** 
     * @brief 其他原因。  <br>
     */
    kStreamRemoveReasonOther = 5,
    /** 
     * @brief 远端用户 Token 发布权限过期。
     */
    kStreamRemoveReasonPrivilegeTokenExpired = 6,
};

/** 
 * @hidden
 * @deprecated since 3.45 and will be deleted in 3.51.
 * @type keytype
 * @brief 用户角色。  <br>
 */
enum UserRoleType {
    /** 
     * @brief 主播角色。该角色用户可在房间内发布和订阅音视频流，房间中的其他用户可以感知到该用户的存在。  <br>
     */
    kUserRoleTypeBroadcaster = 1,
    /** 
     * @brief 隐身用户角色。此角色用户只可在房间内订阅音视频流，房间中的其他用户无法感知到该用户的存在。  <br>
     */
    kUserRoleTypeSilentAudience = 2,
};

/** 
 * @type keytype
 * @brief 数据消息来源
 */
enum DataMessageSourceType {
    /** 
     * @brief 通过客户端或服务端的插入的自定义消息。
     */
    kDataMessageSourceTypeDefault = 0,
    /** 
     * @brief 系统数据，包含音量指示信息。
     */
    kDataMessageSourceTypeSystem,
};

/** 
 * @type keytype
 * @brief SEI 发送模式。
 */
enum SEICountPerFrame {
    /** 
     * @brief 单发模式。即在 1 帧间隔内多次发送 SEI 数据时，多个 SEI 按队列逐帧发送。
     */
    kSingleSEIPerFrame = 0,
    /** 
     * @brief 多发模式。即在 1 帧间隔内多次发送 SEI 数据时，多个 SEI 随下个视频帧同时发送。
     */
    kMultiSEIPerFrame,
};

/** 
 * @type keytype
 * @brief 上行/下行网络质量
 */
struct NetworkQualityStats {
    /** 
     * @brief 用户 ID
     */
    const char* uid;
    /** 
     * @brief 本端的上行/下行的丢包率，范围 [0.0,1.0]
     *        当 `uid` 为本地用户时，代表发布流的上行丢包率。
     *        当 `uid` 为远端用户时，代表接收所有订阅流的下行丢包率。
     */
    double fraction_lost;
    /** 
     * @brief 当 `uid` 为本地用户时有效，客户端到服务端的往返延时（RTT），单位：ms
     */
    int rtt;
    /** 
     * @brief 本端的音视频 RTP 包 2 秒内的平均传输速率，单位：bps
     *        当 `uid` 为本地用户时，代表发送速率。
     *        当 `uid` 为远端用户时，代表所有订阅流的接收速率。
     */
    int total_bandwidth;
    /** 
     * @brief 上行网络质量评分，详见 NetworkQuality{@link #NetworkQuality}。
     */
    NetworkQuality tx_quality;
    /** 
     * @brief 下行网络质量评分，详见 NetworkQuality{@link #NetworkQuality}。
     */
    NetworkQuality rx_quality;
    /**
     * @hidden constructor/destructor
     */
    NetworkQualityStats() : uid(""), fraction_lost(0.), rtt(0), total_bandwidth(0),
        tx_quality(kNetworkQualityUnknown), rx_quality(kNetworkQualityUnknown) {
    }
};

/** 
 * @type keytype
 * @brief 房间模式<br>
 *        根据所需场景，选择合适的房间模式，应用不同的音视频算法、视频参数和网络配置 <br>
 *        调用 `setAudioProfile` 改变音频参数配置
 */
enum RoomProfileType {
    /** 
     * @brief 默认场景，通用模式<br>
     *        与 `kRoomProfileTypeMeeting = 16` 配置相同。<br>
     *        你可以联系技术支持更换默认配置参数。
     */
    kRoomProfileTypeCommunication = 0,
    /** 
     * @deprecated since 3.42 and will be deleted in 3.51, use kRoomProfileTypeInteractivePodcast instead.
     * @brief 直播模式。<br>
     *        当你对音视频通话的音质和画质要求较高时，应使用此设置。<br>
     *        此设置下，当用户使用蓝牙耳机收听时，蓝牙耳机使用媒体模式。
     */
    kRoomProfileTypeLiveBroadcasting = 1,
    /** 
     * @brief 游戏语音模式，低功耗、低流量消耗。<br>
     *        低端机在此模式下运行时，进行了额外的性能优化：<br>
     *            + 部分低端机型配置编码帧长 40/60 <br>
     *            + 部分低端机型关闭软件 3A 音频处理 <br>
     *        增强对 iOS 其他屏幕录制进行的兼容性，避免音频录制被 RTC 打断。
     */
    kRoomProfileTypeGame = 2,
    /** 
     * @brief 云游戏模式。<br>
     *        如果你的游戏场景需要低延迟的配置，使用此设置。<br>
     *        此设置下，弱网抗性较差。
     */
    kRoomProfileTypeCloudGame = 3,
    /** 
     * @brief 云渲染模式。超低延时配置。  <br>
     *        如果你的应用并非游戏但又对延时要求较高时，选用此模式 <br>
     *        该模式下，音视频通话延时会明显降低，但同时弱网抗性、通话音质等均会受到一定影响。  <br>
     */
    kRoomProfileTypeLowLatency = 4,
    /** 
     * @brief 适用于 1 vs 1 音视频通话
     */
    kRoomProfileTypeChat = 5,
    /** 
     * @brief 适用于 3 人及以上纯语音通话。<br>
     *        通话中，闭麦时为是媒体模式，上麦后切换为通话模式。
     */
    kRoomProfileTypeChatRoom = 6,
    /** 
     * @brief 实现多端同步播放音视频，适用于 “一起看” 或 “一起听” 场景。<br>
     *        该场景中，使用 RTC 信令同步播放进度，共享的音频内容不通过 RTC 进行传输。
     */
    kRoomProfileTypeLwTogether = 7,
    /** 
     * @brief 适用于对音质要求较高的游戏场景，优化音频 3A 策略，只通过媒体模式播放音频
     */
    kRoomProfileTypeGameHD = 8,
    /** 
     * @brief 适用于直播中主播之间连麦的业务场景。<br>
     *        直播时通过 CDN，发起连麦 PK 时使用 RTC。
     */
    kRoomProfileTypeCoHost = 9,
    /** 
     * @brief 适用于单主播和观众进行音视频互动的直播。通话模式，上下麦不会有模式切换，避免音量突变现象
     */
    kRoomProfileTypeInteractivePodcast = 10,
    /** 
     * @brief 线上 KTV 场景，音乐音质，低延迟<br>
     *        使用 RTC 传输伴奏音乐，混音后的歌声，适合独唱或单通合唱
     */
    kRoomProfileTypeKTV = 11,
    /** 
     * @brief 适合在线实时合唱场景，高音质，超低延迟。使用本配置前请联系技术支持进行协助完成其他配置。
     */
    kRoomProfileTypeChorus = 12,
    /** 
     * @brief 适用于 VR 场景。支持最高 192 KHz 音频采样率，可开启球形立体声。
     */
    kRoomProfileTypeVRChat = 13,
    /** 
     * @brief 适用于 1 vs 1 游戏串流，支持公网或局域网。
     */
    kRoomProfileTypeGameStreaming = 14,
    /** 
     * @brief 适用于局域网的 1 对多视频直播，最高支持 8K， 60 帧/秒， 100 Mbps 码率<br>
     *        需要在局域网配置私有化部署媒体服务器。
     */
    kRoomProfileTypeLanLiveStreaming = 15,
    /** 
     * @brief 适用于云端会议中的个人设备
     */
    kRoomProfileTypeMeeting = 16,
    /** 
     * @brief 适用于云端会议中的会议室终端设备，例如 Rooms，投屏盒子等。
     */
    kRoomProfileTypeMeetingRoom = 17,
    /** 
     * @brief 适用于课堂互动，房间内所有成员都可以进行音视频互动<br>
     *        当你的场景中需要同时互动的成员超过 10人时使用此模式
     */
    kRoomProfileTypeClassroom = 18,
};
/** 
 * @type keytype
 * @brief 多房间参数配置
 */
struct AudioRoomConfig {
    /** 
     * @brief 房间模式，参看 RoomProfileType{@link #RoomProfileType}，默认为 `kRoomProfileTypeCommunication`，进房后不可更改。
     */
    RoomProfileType room_profile_type = kRoomProfileTypeCommunication;
    /** 
     * @brief 是否自动订阅音频流，默认为自动订阅。
     */
    bool is_auto_subscribe_audio = true;
    /** 
     * @brief 是否自动发布音视频流，默认为自动发布。 <br>
     *        若调用 `setUserVisibility` 将自身可见性设为 false，无论是默认的自动发布流还是手动设置的自动发布流都不会进行发布，你需要将自身可见性设为 true 后方可发布。  <br>
     *        多房间场景下，若已在其中一个房间成功设置了自动发布，其他房间的自动发布设置均不会生效。若每个房间均不做设置，则默认在第一个加入的房间内自动发布流。
     */
    bool is_auto_publish_audio = true;
};

/** 
 * @type keytype
 * @brief 媒体设备类型
 */
enum MediaDeviceType {
    /** 
     * @brief 未知设备
     */
    kMediaDeviceTypeAudioUnknown = -1,
    /** 
     * @brief 音频渲染设备
     */
    kMediaDeviceTypeAudioRenderDevice = 0,
    /** 
     * @brief 音频采集设备
     */
    kMediaDeviceTypeAudioCaptureDevice = 1,
    /** 
     * @hidden currently not available
     *@brief 视频渲染设备类型，该类型暂无使用
     */
    kMediaDeviceTypeVideoRenderDevice = 2,
    /** 
     *@brief 视频采集设备
     */
    kMediaDeviceTypeVideoCaptureDevice = 3,
    /** 
     *@brief 屏幕流视频设备
     */
    kMediaDeviceTypeScreenVideoCaptureDevice = 4,
    /** 
     * @brief 屏幕流音频设备
     */
    kMediaDeviceTypeScreenAudioCaptureDevice = 5,
};

/** 
 * @type keytype
 * @brief 媒体设备状态。
 */
enum MediaDeviceState {
    /** 
     * @brief 设备已开启
     */
    kMediaDeviceStateStarted = 1,
    /** 
     * @brief 设备已停止
     */
    kMediaDeviceStateStopped = 2,
    /** 
     * @brief 设备运行时错误<br>
     *       例如，当媒体设备的预期行为是正常采集，但没有收到采集数据时，将回调该状态。
     */
    kMediaDeviceStateRuntimeError = 3,
    /** 
     * @brief 设备已暂停。包括：
     *        + 采集过程中，目标应用窗体最小化到任务栏。
     *        + 开启采集或采集过程中，目标应用窗体被隐藏。
     *        + 采集过程中，目标应用窗体正在被拉伸。
     *        + 采集过程中，目标应用窗体正在被拖动。
     */
    kMediaDeviceStatePaused = 4,
    /** 
     * @brief 设备已恢复
     */
    kMediaDeviceStateResumed = 5,
    /** 
     * @brief 设备已插入
     */
    kMediaDeviceStateAdded = 10,
    /** 
     * @brief 设备被移除
     */
    kMediaDeviceStateRemoved = 11,
    /** 
     * @brief 用户合盖打断了视频通话。如果系统未休眠或关机，将在开盖后自动恢复视频通话。
     */
    kMediaDeviceInterruptionBegan = 12,
    /** 
     * @brief 视频通话已从合盖打断中恢复
     */
    kMediaDeviceInterruptionEnded = 13,
    /** 
     * @brief 设备成为系统默认
     */
    kMediaDeviceBecomeSystemDefault = 14,
    /** 
     * @brief 设备不再是系统默认
     */
    kMediaDeviceResignSystemDefault = 15
};

/** 
 * @type keytype
 * @brief 媒体设备错误类型
 */
enum MediaDeviceError {
    /** 
     * @brief 媒体设备正常
     */
    kMediaDeviceErrorOK = 0,
    /** 
     * @brief 没有权限启动媒体设备
     */
    kMediaDeviceErrorDeviceNoPermission = 1,
    /** 
     * @brief 媒体设备已经在使用中
     */
    kMediaDeviceErrorDeviceBusy = 2,
    /** 
     * @brief 媒体设备错误
     */
    kMediaDeviceErrorDeviceFailure = 3,
    /** 
     * @brief 未找到指定的媒体设备
     */
    kMediaDeviceErrorDeviceNotFound = 4,
    /** 
     * @brief 媒体设备被移除。<br>
     *        对象为采集屏幕流时，表明窗体被关闭或显示器被移除。
     */
    kMediaDeviceErrorDeviceDisconnected = 5,
    /** 
     * @brief 设备没有数据回调
     */
    kMediaDeviceErrorDeviceNoCallback = 6,
    /** 
     * @brief 设备采样率不支持
     */
    kMediaDeviceErrorDeviceUNSupportFormat = 7,
    /** 
     * @hidden(Android,macOS,Windows,Linux)
     * @brief ios 屏幕采集没有 group id 参数
     */
    kMediaDeviceErrorDeviceNotFindGroupId = 8,
    /** 
     * @hidden(Android,Windows,Linux)
     * @brief 打断类型：使用camera过程中被送到后台
     */
    kMediaDeviceErrorDeviceNotAvailableInBackground = 9,
    /** 
     * @hidden(Android,Windows,Linux)
     * @brief 打断类型：被其他客户端打断，比如一个正在使用capture session的app
     */
    kMediaDeviceErrorDeviceVideoInUseByAnotherClient = 10,
    /** 
     * @hidden(Android,Windows,Linux)
     * @brief 打断类型：使用Slide Over,、Split View 或者 PIP时被中断，比如台前调度，画中画
     */
    kMediaDeviceErrorDeviceNotAvailableWithMultipleForegroundApps = 11,
    /** 
     * @hidden(Android,Windows,Linux)
     * @brief 打断类型：系统压力，比如过热
     */
    kMediaDeviceErrorDeviceNotAvailableDueToSystemPressure = 12,
};

/** 
 * @type keytype
 * @brief 媒体设备警告
 */
enum MediaDeviceWarning {
    /** 
     * @brief 无警告
     */
    kMediaDeviceWarningOK = 0,
    /** 
     * @brief 非法设备操作。在使用外部设备时，调用了 SDK 内部设备 API。
     */
    kMediaDeviceWarningOperationDenied = 1,
    /** 
     * @brief 采集静音。
     */
    kMediaDeviceWarningCaptureSilence = 2,
    /** 
     * @hidden(iOS,macOS,Windows,Linux)
     * @brief Android 特有的静音，系统层面的静音上报
     */
    kMediaDeviceWarningAndroidSysSilence = 3,
    /** 
     * @hidden(iOS,macOS,Windows,Linux)
     * @brief Android 特有的静音消失
     */
    kMediaDeviceWarningAndroidSysSilenceDisappear = 4,
    // The following warning codes are only valid for meeting scenarios.
    /** 
     * @hidden for internal use only
     * @brief 音量过大，超过设备采集范围。建议降低麦克风音量或者降低声源音量。
     */
    kMediaDeviceWarningDetectClipping = 10,
    /** 
     * @brief 通话中出现回声现象。<br>
     *        当 RoomProfileType{@link #RoomProfileType} 为 `kRoomProfileTypeMeeting` 和 `kRoomProfileTypeMeetingRoom`，且 AEC 关闭时，SDK 自动启动回声检测，如果检测到回声问题，将通过 `onAudioDeviceWarning` 返回本枚举值。
     */
    kMediaDeviceWarningDetectLeakEcho = 11,
    /** 
     * @hidden for internal use only
     * @brief 低信噪比
     */
    kMediaDeviceWarningDetectLowSNR = 12,
    /** 
     * @hidden for internal use only
     * @brief 采集插零现象
     */
    kMediaDeviceWarningDetectInsertSilence = 13,
    /** 
     * @hidden for internal use only
     * @brief 设备采集静音（算法层）
     */
    kMediaDeviceWarningCaptureDetectSilence = 14,
    /** 
     * @hidden for internal use only
     * @brief 设备采集静音消失
     */
    kMediaDeviceWarningCaptureDetectSilenceDisappear = 15,
    /** 
     * @hidden(Linux)
      * @brief 啸叫。触发该回调的情况如下：1）不支持啸叫抑制的房间模式下，检测到啸叫；2）支持啸叫抑制的房间模式下，检测到未被抑制的啸叫。
     *        仅 kRoomProfileTypeCommunication、kRoomProfileTypeMeeting、kRoomProfileTypeMeetingRoom 三种房间模式支持啸叫抑制。
     *        建议提醒用户检查客户端的距离或将麦克风和扬声器调至静音。
     */
    kMediaDeviceWarningCaptureDetectHowling = 16,
    /** 
     * @hidden(Windows,macOS,Linux)
     * @brief setAudioRoute结果回调, 该scenario下不支持设置
     */
    kMediaDeviceWarningSetAudioRouteInvalidScenario = 20,
    /** 
     * @hidden(Windows,macOS,Linux)
     * @brief setAudioRoute结果回调, routing device 不存在 (Android)
     */
    kMediaDeviceWarningSetAudioRouteNotExists = 21,
    /** 
     * @hidden(Windows,macOS,Linux)
     * @brief setAudioRoute结果回调, 系统高优先级路由占用 (IOS)
     */
    kMediaDeviceWarningSetAudioRouteFailedByPriority = 22,
    /** 
     * @hidden(Windows,macOS,Linux)
     * @brief 当前非通话模式 kAudioScenarioTypeCommunication，不支持设置音频路由
     */
    kMediaDeviceWarningSetAudioRouteNotVoipMode = 23,
    /** 
     * @hidden(Windows,macOS,Linux)
     * @brief setAudioRoute结果回调, 设备没有启动
     */
    kMediaDeviceWarningSetAudioRouteDeviceNotStart = 24,
    /** 
     * @hidden(macOS,Windows,Linux,Android)
     * @brief setBluetoothMode结果回调, 当前场景不会立即生效
     */
    kMediaDeviceWarningSetBluetoothModeScenarioUnsupport = 25,
    /** 
     * @hidden(macOS,Windows,Linux,Android)
     * @brief setBluetoothMode 结果回调, 当前不支持设置蓝牙模式
     */
    kMediaDeviceWarningSetBluetoothModeUnsupport = 26,
    /** 
     * @hidden currently not available
     * @brief 使用无声的采集设备
     */
    kMediaDeviceWarningRecordingUseSilentDevice = 27,
    /** 
     * @hidden(Linux)
     * @brief 使用无声的播放设备
     */
    kMediaDeviceWarningPlayoutUseSilentDevice = 28,
};

/** 
 * @type keytype
 * @brief 订阅媒体流状态
 */
enum SubscribeState {
    /** 
     * @brief 订阅/取消订阅流成功
     */
    kSubscribeStateSuccess,
    /** 
     * @brief 订阅/取消订阅流失败，本地用户未在房间中
     */
    kSubscribeStateFailedNotInRoom,
    /** 
     * @brief 订阅/取消订阅流失败，房间内未找到指定的音视频流
     */
    kSubscribeStateFailedStreamNotFound,
    /** 
     * @brief 超过订阅流数上限
     */
    kSubscribeStateFailedOverLimit,
};

/** 
 * @hidden
 * @deprecated since 3.26 and will be deleted in 3.51, use RoomConfig in joinRoom{@link #IRTCRoom#joinRoom} instead.
 * @type keytype
 * @brief 订阅模式选项。
 */
enum SubscribeMode {
    /** 
     * @brief 自动订阅模式。SDK 会自动为你订阅房间中的每一路流。  <br>
     */
    kSubscribeModeAuto = 0,
    /** 
     * @brief 手动订阅模式。SDK 不会自动订阅房间内的音视频流，你应根据根据需要调用 subscribeUserStream{@link #IRTCRoom#subscribeUserStream} 方法手动订阅其他用户发布的音视频流。  <br>
     */
    kSubscribeModeManual = 1
};

/** 
 * @type keytype
 * @brief 远端用户优先级，在性能不足需要回退时，会优先回退优先级低的用户的音视频流
 */
enum RemoteUserPriority {
    /** 
     * @brief 用户优先级为低（默认值）
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
 * @brief 发布端音视频流回退选项
 */
enum PublishFallbackOption {
    /** 
     * @brief 上行网络不佳或设备性能不足时，不对音视频流作回退处理。默认设置。
     */
    kPublishFallbackOptionDisabled = 0,
    /** 
     * @brief 上行网络不佳或设备性能不足时，发布的视频流会从大流到小流依次降级，直到与当前网络性能匹配，具体降级规则参看[性能回退](https://www.volcengine.com/docs/6348/70137)文档。
     */
    kPublishFallbackOptionSimulcast = 1,
};
/** 
 * @type keytype
 * @brief 订阅端音视频流回退选项。
 */
enum SubscribeFallbackOption {
    /** 
     * @brief 下行网络不佳或设备性能不足时，不对音视频流作回退处理。默认设置。
     */
    kSubscribeFallbackOptionDisable = 0,
    /** 
     * @brief 下行网络不佳或设备性能不足时，对视频流做降级处理，具体降级规则参看[音视频流回退](70137)。 <br>
     *        该设置仅对发布端调用 enableSimulcastMode{@link #IRTCVideo#enableSimulcastMode} 开启发送多路流功能的情况生效。
     */
    kSubscribeFallbackOptionVideoStreamLow = 1,
    /** 
     * @brief 下行网络不佳或设备性能不足时，先对视频流做回退处理。当网络状况不满足接收弱流时，则自动取消接收视频，仅接收音频。<br>
     *        该设置仅对发布端调用 enableSimulcastMode{@link #IRTCVideo#enableSimulcastMode} 开启发送多路流功能的情况生效。
     */
    kSubscribeFallbackOptionAudioOnly = 2,
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
 * @brief 性能相关告警的原因
 */
enum PerformanceAlarmReason {
    /** 
     * @brief 网络原因差，造成了发送性能回退。仅在开启发送性能回退时，会收到此原因。
     */
    kPerformanceAlarmReasonBandwidthFallbacked = 0,
    /** 
     * @brief 网络性能恢复，发送性能回退恢复。仅在开启发送性能回退时，会收到此原因。
     */
    kPerformanceAlarmReasonBandwidthResumed = 1,
    /** 
     * @brief 如果未开启发送性能回退，收到此告警时，意味着性能不足；<br>
     *        如果开启了发送性能回退，收到此告警时，意味着性能不足，且已发生发送性能回退。
     */
    kPerformanceAlarmReasonPerformanceFallbacked = 2,
    /** 
     * @brief 如果未开启发送性能回退，收到此告警时，意味着性能不足已恢复；<br>
     *        如果开启了发送性能回退，收到此告警时，意味着性能不足已恢复，且已发生发送性能回退恢复。
     */
    kPerformanceAlarmReasonPerformanceResumed = 3,
};

/** 
 * @type keytype
 * @brief 是否开启发布性能回退
 */
enum PerformanceAlarmMode {
    /** 
     * @brief 未开启发布性能回退
     */
    kPerformanceAlarmModeNormal = 0,
    /** 
     * @brief 已开启发布性能回退
     */
    kPerformanceAlarmModeSimulcast = 1,
};

/** 
 * @type errorcode
 * @brief 回调错误码。  <br>
 *        SDK 内部遇到不可恢复的错误时，会通过 `onError` 回调通知用户。
 */
enum ErrorCode {
    /** 
     * @brief Token 无效。
     *        进房时使用的 Token 无效或过期失效。需要用户重新获取 Token，并调用 `updateToken` 方法更新 Token。
     */
    kErrorCodeInvalidToken = -1000,
    /** 
     * @brief 加入房间错误。
     *        进房时发生未知错误导致加入房间失败。需要用户重新加入房间。
     */
    kErrorCodeJoinRoom = -1001,
    /** 
     * @brief 没有发布音视频流权限。
     *        用户在所在房间中发布音视频流失败，失败原因为用户没有发布流的权限。
     */
    kErrorCodeNoPublishPermission = -1002,
    /** 
     * @brief 没有订阅音视频流权限。
     *        用户订阅所在房间中的音视频流失败，失败原因为用户没有订阅流的权限。
     */
    kErrorCodeNoSubscribePermission = -1003,
    /** 
     * @brief 相同用户 ID 的用户加入本房间，当前用户被踢出房间
     */
    kErrorCodeDuplicateLogin = -1004,
    /** 
     * @brief 服务端调用 OpenAPI 将当前用户踢出房间
     */
    kErrorCodeKickedOut = -1006,
    /** 
     * @brief 当调用 `createRTCRoom` ，如果roomid 非法，会返回null，并抛出该error
     */
    kRoomErrorCodeRoomIdIllegal = -1007,
    /** 
     * @brief Token 过期。调用 `joinRoom` 使用新的 Token 重新加入房间。
     */
    kRoomErrorTokenExpired = -1009,
    /** 
     * @brief 调用 `updateToken` 传入的 Token 无效
     */
    kRoomErrorUpdateTokenWithInvalidToken = -1010,
    /** 
     * @brief 服务端调用 OpenAPI 解散房间，所有用户被移出房间。
     */
    kErrorCodeRoomDismiss = -1011,
    /** 
     * @brief 加入房间错误。 <br>
     *        进房时, LICENSE 计费账号未使用 LICENSE_AUTHENTICATE SDK，加入房间错误。
     */
    kErrorCodeJoinRoomWithoutLicenseAuthenticateSDK = -1012,
    /** 
     * @brief 通话回路检测已经存在同样 roomId 的房间了
     */
    kErrorCodeRoomAlreadyExist = -1013,
    /** 
     * @brief 加入多个房间时使用了不同的 uid。<br>
     *        同一个引擎实例中，用户需使用同一个 uid 加入不同的房间。
     */
    kErrorCodeUserIDDifferent = -1014,
    /** 
     * @brief 服务端license过期，拒绝进房。 <br>
     */
    kErrorCodeJoinRoomServerLicenseExpired = -1017,
    /** 
     * @brief 超过服务端license许可的并发量上限，拒绝进房。 <br>
     */
    kErrorCodeJoinRoomExceedsTheUpperLimit = -1018,
    /** 
     * @brief license参数错误，拒绝进房。 <br>
     */
    kErrorCodeJoinRoomLicenseParameterError = -1019,
    /** 
     * @brief license证书路径错误。 <br>
     */
    kErrorCodeJoinRoomLicenseFilePathError = -1020,
    /** 
     * @brief license证书不合法。 <br>
     */
    kErrorCodeJoinRoomLicenseIllegal = -1021,
    /** 
     * @brief license证书已经过期，拒绝进房。 <br>
     */
    kErrorCodeJoinRoomLicenseExpired = -1022,
    /** 
     * @brief license证书内容不匹配。 <br>
     */
    kErrorCodeJoinRoomLicenseInformationNotMatch = -1023,
    /** 
     * @brief license当前证书与缓存证书不匹配。 <br>
     */
    kErrorCodeJoinRoomLicenseNotMatchWithCache = -1024,
    /** 
     * @brief 房间被封禁。 <br>
     */
    kErrorCodeJoinRoomRoomForbidden = -1025,
    /** 
     * @brief 用户被封禁。 <br>
     */
    kErrorCodeJoinRoomUserForbidden = -1026,
    /** 
     * @brief license 计费方法没有加载成功。可能是因为 license 相关插件未正确集成。<br>
     */
    kErrorCodeJoinRoomLicenseFunctionNotFound = -1027,
    /** 
     * @brief 订阅音视频流失败，订阅音视频流总数超过上限。
     *        游戏场景下，为了保证音视频通话的性能和质量，服务器会限制用户订阅的音视频流总数。当用户订阅的音视频流总数已达上限时，继续订阅更多流时会失败，同时用户会收到此错误通知。
     */
    kErrorCodeOverStreamSubscribeLimit = -1070,
    /** 
     * @brief 发布流失败，发布流总数超过上限。
     *        RTC 系统会限制单个房间内发布的总流数，总流数包括视频流、音频流和屏幕流。如果房间内发布流数已达上限时，本地用户再向房间中发布流时会失败，同时会收到此错误通知。
     */
    kErrorCodeOverStreamPublishLimit = -1080,
    /** 
     * @brief 发布屏幕流失败，发布流总数超过上限。
     *        RTC 系统会限制单个房间内发布的总流数，总流数包括视频流、音频流和屏幕流。如果房间内发布流数已达上限时，本地用户再向房间中发布流时会失败，同时会收到此错误通知。
     */
    kErrorCodeOverScreenPublishLimit = -1081,
    /** 
     * @deprecated since 3.52, use kErrorCodeOverStreamPublishLimit（-1080）instead
     * @brief 发布视频流总数超过上限。
     *        RTC 系统会限制单个房间内发布的视频流数。如果房间内发布视频流数已达上限时，本地用户再向房间中发布视频流时会失败，同时会收到此错误通知。
     */
    kErrorCodeOverVideoPublishLimit = -1082,
    /** 
     * @brief 音视频同步失败。  <br>
     *        当前音频源已与其他视频源关联同步关系。  <br>
     *        单个音频源不支持与多个视频源同时同步。
     */
    kErrorCodeInvalidAudioSyncUidRepeated = -1083,
    /** 
     * @brief 服务端异常状态导致退出房间。  <br>
     *        SDK与信令服务器断开，并不再自动重连，可联系技术支持。  <br>
     */
    kErrorCodeAbnormalServerStatus = -1084,
    /** 
     * @hidden for internal use only
     * @brief 在一路流推多房间的场景下，在至少有两个房间在发布同一路流时，其中一个房间取消发布失败，此时需要业务方重试或者由业务方通知用户重试取消发布。 <br>
     */
    kErrorCodeMultiRoomUnpublishFailed = -1085,
    /**
     * @hidden for internal use only
     */
    kErrorCodeInternalDeadLockNotify = -1111,
};

/** 
 * @type errorcode
 * @brief 回调警告码。
 *        警告码说明 SDK 内部遇到问题正在尝试恢复。警告码仅起通知作用。
 */
enum WarningCode {
    /** 
     * @deprecated since 3.45 and will be deleted in 3.51.
     */
    kWarningCodeGetRoomFailed = -2000,
    /** 
     * @brief 进房失败。  <br>
     *        当你调用初次加入房间或者由于网络状况不佳断网重连时，由于服务器错误导致进房失败。SDK 会自动重试进房。
     */
    kWarningCodeJoinRoomFailed = -2001,
    /** 
     * @brief 发布音视频流失败。  <br>
     *        当你在所在房间中发布音视频流时，由于服务器错误导致发布失败。SDK 会自动重试发布。
     */
    kWarningCodePublishStreamFailed = -2002,
    /** 
     * @brief 订阅音视频流失败。  <br>
     *        当前房间中找不到订阅的音视频流导致订阅失败。SDK 会自动重试订阅，若仍订阅失败则建议你退出重试。
     */
    kWarningCodeSubscribeStreamFailed404 = -2003,
    /** 
     * @brief 订阅音视频流失败。  <br>
     *        当你订阅所在房间中的音视频流时，由于服务器错误导致订阅失败。SDK 会自动重试订阅。
     */
    kWarningCodeSubscribeStreamFailed5xx = -2004,
    /** 
     * @hidden currently not available
     * @brief 函数调用顺序错误。
     */
    kWarningCodeInvokeError = -2005,
    /** 
     * @hidden for internal use only
     * @brief 调度异常，服务器返回的媒体服务器地址不可用。
     */
    kWarningCodeInvalidExpectMediaServerAddress = -2007,
    /** 
     * @brief 当调用 `setUserVisibility` 将自身可见性设置为 false 后，再尝试发布流会触发此警告。  <br>
     */
    kWarningCodePublishStreamForbiden = -2009,
    /** 
     * @deprecated since 3.45 and will be deleted in 3.51.
     * @brief 自动订阅模式未关闭时，尝试开启手动订阅模式会触发此警告。  <br>
     *        你需在进房前关闭自动订阅模式，再调用 subscribeStream{@link #IRTCRoom#subscribeStream} 方法手动订阅音视频流。
     */
    kWarningCodeSubscribeStreamForbiden = -2010,
    /** 
     * @brief 发送自定义广播消息失败，当前你未在房间中。
     */
    kWarningCodeSendCustomMessage = -2011,
    /** 
     * @brief 当房间内人数超过 500 人时，停止向房间内已有用户发送 `onUserJoined` 和 `onUserLeave` 回调，并通过广播提示房间内所有用户。
     */
    kWarningCodeUserNotifyStop = -2013,

    /** 
     * @brief 用户已经在其他房间发布过流，或者用户正在发布公共流。
     */
    kWarningCodeUserInPublish = -2014,

    /** 
     * @brief 已存在相同 roomId 的房间，新创建的房间实例已替换旧房间实例。
     */
    kWarningCodeOldRoomBeenReplaced = -2016,

    /** 
     * @brief 当前正在进行回路测试，该接口调用无效
     */
    kWarningCodeInEchoTestMode = -2017,

    /** 
     * @brief 摄像头权限异常，当前应用没有获取摄像头权限。
     */
    kWarningCodeNoCameraPermission = -5001,
    /** 
     * @brief 麦克风权限异常，当前应用没有获取麦克风权限。
     * @deprecated since 3.33 and will be deleted in 3.51, use MediaDeviceWarning{@link #MediaDeviceWarning} instead.
     */
    kWarningCodeNoMicrophonePermission = -5002,
    /** 
     * @brief 音频采集设备启动失败，当前设备可能被其他应用占用。
     * @deprecated since 3.33 and will be deleted in 3.51, use MediaDeviceWarning{@link #MediaDeviceWarning} instead.
     */
    kWarningCodeRecodingDeviceStartFailed = -5003,
    /** 
     * @brief 音频播放设备启动失败警告，可能由于系统资源不足，或参数错误。
     * @deprecated since 3.33 and will be deleted in 3.51, use MediaDeviceWarning{@link #MediaDeviceWarning} instead.
     */
    kWarningCodePlayoutDeviceStartFailed = -5004,
    /** 
     * @brief 无可用音频采集设备，请插入可用的音频采集设备。
     * @deprecated since 3.33 and will be deleted in 3.51, use MediaDeviceWarning{@link #MediaDeviceWarning} instead.
     */
    kWarningCodeNoRecordingDevice = -5005,
    /** 
     * @brief 无可用音频播放设备，请插入可用的音频播放设备。
     * @deprecated since 3.33 and will be deleted in 3.51, use MediaDeviceWarning{@link #MediaDeviceWarning} instead.
     */
    kWarningCodeNoPlayoutDevice = -5006,
    /** 
     * @brief 当前音频设备没有采集到有效的声音数据，请检查更换音频采集设备。
     * @deprecated since 3.33 and will be deleted in 3.51, use MediaDeviceWarning{@link #MediaDeviceWarning} instead.
     */
    kWarningCodeRecordingSilence = -5007,
    /** 
     * @brief 媒体设备误操作警告。  <br>
     *        使用自定义采集时，不可调用内部采集开关，调用时将触发此警告。
     * @deprecated since 3.33 and will be deleted in 3.51, use MediaDeviceWarning{@link #MediaDeviceWarning} instead.
     */
    kWarningCodeMediaDeviceOperationDenied = -5008,

    /** 
     * @brief 不支持在 `publishScreen` 之后调用 `setScreenAudioSourceType` 设置屏幕音频采集类型，请在 publishScreen 之前设置
     */
    kWarningCodeSetScreenAudioSourceTypeFailed = -5009,

    /** 
     * @brief 不支持在 `publishScreen` 之后， 通过 `setScreenAudioStreamIndex` 设置屏幕共享时的音频采集方式。
     */
    kWarningCodeSetScreenAudioStreamIndexFailed = -5010,
    /** 
     * @brief 设置语音音高不合法
     */
    kWarningCodeInvalidVoicePitch = -5011,
    /** 
     * @brief 设置音频格式不合法
     */
    kWarningCodeInvalidAudioFormat = -5012,
    /** 
     * @brief 外部音频源新旧接口混用
     */
    kWarningCodeInvalidCallForExtAudio = -5013,
    /** 
     * @brief 非法的远端流索引
     */
    kWarningCodeInvalidRemoteStreamKey = -5014,

    /** 
     * @brief 指定的内部渲染画布句柄无效。  <br>
     *        当你调用 setLocalVideoCanvas{@link #IRTCVideo#setLocalVideoCanvas} 时指定了无效的画布句柄，触发此回调。
     */
    kWarningCodeInvalidCanvasHandle = -6001,
    /** 
     * @brief 鉴权文件失效，当检查鉴权文件状态时，本地文件与远端文件不一致会触发次警告。  <br>
     */
    kWarningLicenseFileExpired = -7001,

    /**
     * @hidden for internal use only
     */
    kWarningInvaildSamiAppkeyORToken = -7002,

    /**
     * @hidden for internal use only
     */
    kWarningInvaildSamiResourcePath = -7003,

    /**
     * @hidden for internal use only
     */
    kWarningLoadSamiLibraryFailed = -7004,

    /**
     * @hidden for internal use only
     */
    kWarningInvaildSamiEffectType = -7005,
};

/** 
 * @type keytype
 * @brief 本地音频流状态。
 */
enum LocalAudioStreamState {
    /** 
     * @brief 本地音频默认初始状态。
     *        麦克风停止工作时回调该状态，对应错误码 kLocalAudioStreamErrorOk
     */
    kLocalAudioStreamStateStopped = 0,

    /** 
     * @brief 本地音频录制设备启动成功。
     *        采集到音频首帧时回调该状态，对应错误码 kLocalAudioStreamErrorOk
     */
    kLocalAudioStreamStateRecording,

    /** 
     * @brief 本地音频首帧编码成功。
     *        音频首帧编码成功时回调该状态，对应错误码 kLocalAudioStreamErrorOk
     */
    kLocalAudioStreamStateEncoding,

    /** 
     * @brief  本地音频启动失败，在以下时机回调该状态：  <br>
     *       + 本地录音设备启动失败，对应错误码 kLocalAudioStreamErrorRecordFailure <br>
     *       + 检测到没有录音设备权限，对应错误码 kLocalAudioStreamErrorDeviceNoPermission <br>
     *       + 音频编码失败，对应错误码 kLocalAudioStreamErrorEncodeFailure
     */
    kLocalAudioStreamStateFailed,

    /** 
     * @brief 本地音频静音成功后回调该状态。
     *        调用 setAudioCaptureDeviceMute{@link #IAudioDeviceManager#setAudioCaptureDeviceMute} 成功后回调，对应错误码 LocalAudioStreamError{@link #LocalAudioStreamError} 中的 kLocalAudioStreamErrorOk 。  <br>
     */
    kLocalAudioStreamMute,

    /** 
     * @brief 本地音频解除静音成功后回调该状态。
     *        调用 setAudioCaptureDeviceMute{@link #IAudioDeviceManager#setAudioCaptureDeviceMute} 成功后回调，对应错误码 LocalAudioStreamError{@link #LocalAudioStreamError} 中的 kLocalAudioStreamErrorOk 。  <br>
     */
    kLocalAudioStreamUnmute
};

/** 
 * @type keytype
 * @brief 本地音频流状态改变时的错误码。
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
     * @hidden currently not available
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
     * @brief 本地视频采集设备启动失败
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
     * @brief 本地视频采集设备已被占用
     */
    kLocalVideoStreamErrorDeviceBusy,
    /** 
     * @brief 本地视频采集设备不存在
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
    /** 
     * @brief 通话过程中本地视频采集设备被其他程序抢占，导致设备连接中断
     */
    kLocalVideoStreamErrorDeviceDisconnected
};

/** 
 * @type keytype
 * @brief 远端音频流状态。<br>
 */
enum RemoteAudioState {
    /** 
     * @brief  不接收远端音频流。
     */
    kRemoteAudioStateStopped = 0,
    /** 
     * @brief 开始接收远端音频流首包。
     */
    kRemoteAudioStateStarting,
    /** 
     * @brief  远端音频流正在解码，正常播放。
     */
    kRemoteAudioStateDecoding,
    /** 
     * @brief 远端音频流卡顿。
     */
    kRemoteAudioStateFrozen,
    /** 
     * @hidden currently not available
     * @brief 远端音频流播放失败
     * @notes 该错误码暂未使用
     */
    kRemoteAudioStateFailed,
};

/** 
 * @type keytype
 * @brief 接收远端音频流状态改变的原因。
 */
enum RemoteAudioStateChangeReason {
    /** 
     * @brief 内部原因
     */
    kRemoteAudioStateChangeReasonInternal = 0,
    /** 
     * @brief 网络阻塞
     */
    kRemoteAudioStateChangeReasonNetworkCongestion,
    /** 
     * @brief 网络恢复正常
     */
    kRemoteAudioStateChangeReasonNetworkRecovery,
    /** 
     * @brief 本地用户停止接收远端音频流
     */
    kRemoteAudioStateChangeReasonLocalMuted,
    /** 
     * @brief 本地用户恢复接收远端音频流
     */
    kRemoteAudioStateChangeReasonLocalUnmuted,
    /** 
     * @brief 远端用户停止发送音频流
     */
    kRemoteAudioStateChangeReasonRemoteMuted,
    /** 
     * @brief 远端用户恢复发送音频流
     */
    kRemoteAudioStateChangeReasonRemoteUnmuted,
    /** 
     * @brief 远端用户离开房间
     */
    kRemoteAudioStateChangeReasonRemoteOffline,
};

/** 
 * @type keytype
 * @brief 远端视频流状态。状态改变时，会收到 `onRemoteVideoStateChanged` 回调
 */
enum RemoteVideoState {
    /** 
     * @brief 远端视频流默认初始状态，视频尚未开始播放。
     */
    kRemoteVideoStateStopped = 0,
    /** 
     * @brief 本地用户已接收远端视频流首包。
     */
    kRemoteVideoStateStarting,
    /** 
     * @brief 远端视频流正在解码，正常播放。
     */
    kRemoteVideoStateDecoding,
    /** 
     * @brief 远端视频流卡顿，可能有网络等原因。
     */
    kRemoteVideoStateFrozen,
    /** 
     * @brief 远端视频流播放失败。
     */
    kRemoteVideoStateFailed,
};

/** 
 * @type keytype
 * @brief 远端视频流状态改变的原因
 */
enum RemoteVideoStateChangeReason {
    /** 
     * @brief 内部原因
     */
    kRemoteVideoStateChangeReasonInternal = 0,
    /** 
     * @brief 网络阻塞
     */
    kRemoteVideoStateChangeReasonNetworkCongestion,
    /** 
     * @brief 网络恢复正常
     */
    kRemoteVideoStateChangeReasonNetworkRecovery,
    /** 
     * @brief 本地用户停止接收远端视频流或本地用户禁用视频模块
     */
    kRemoteVideoStateChangeReasonLocalMuted,
    /** 
     * @brief 本地用户恢复接收远端视频流或本地用户启用视频模块
     */
    kRemoteVideoStateChangeReasonLocalUnmuted,
    /** 
     * @brief 远端用户停止发送视频流或远端用户禁用视频模块
     */
    kRemoteVideoStateChangeReasonRemoteMuted,
    /** 
     * @brief 远端用户恢复发送视频流或远端用户启用视频模块
     */
    kRemoteVideoStateChangeReasonRemoteUnmuted,
    /** 
     * @brief 远端用户离开频道。状态转换参考 `onUserUnPublishStream`。
     */
    kRemoteVideoStateChangeReasonRemoteOffline,
};

/** 
 * @type keytype
 * @brief 黑帧视频流状态
 */
enum SEIStreamEventType {
    /** 
     * @brief 远端用户发布黑帧视频流。  <br>
     *        纯语音通话场景下，远端用户调用 sendSEIMessage{@link #IRTCVideo#sendSEIMessage} 发送 SEI 数据时，SDK 会自动发布一路黑帧视频流，并触发该回调。
     */
    kSEIStreamEventTypeStreamAdd = 0,
    /** 
     * @brief 远端黑帧视频流移除。该回调的触发时机包括：  <br>
     *        + 远端用户开启摄像头采集，由语音通话切换至视频通话，黑帧视频流停止发布；  <br>
     *        + 远端用户调用 sendSEIMessage{@link #IRTCVideo#sendSEIMessage} 后 1min 内未有 SEI 数据发送，黑帧视频流停止发布；  <br>
     *        + 远端用户调用 setVideoSourceType{@link #IRTCVideo#setVideoSourceType} 切换至自定义视频采集时，黑帧视频流停止发布。
     */
     kSEIStreamEventTypeStreamRemove,
};

/** 
 * @type keytype
 * @brief 性能回退相关数据
 */
struct SourceWantedData {
    /** 
     * @brief  <br>
     * 未开启发布回退时，此值表示推荐的视频输入宽度，当回退模式为大小流模式时，表示当前推流的最大宽度
     * @brief 如果未开启发送性能回退，此值表示推荐的视频输入宽度；  <br>
     *        如果开启了发送性能回退，此值表示当前推流的最大宽度。
     */
    int width;
    /** 
     * @brief 如果未开启发送性能回退，此值表示推荐的视频输入高度；<br>
     *        如果开启了发送性能回退，此值表示当前推流的最大高度。
     */
    int height;
    /** 
     * @brief 如果未开启发送性能回退，此值表示推荐的视频输入帧率，单位 fps；<br>
     *        如果开启了发送性能回退，此值表示当前推流的最大帧率，单位 fps。
     */
    int frame_rate;
};
/** 
 * @type keytype
 * @brief 用户信息
 */
struct UserInfo {
    /** 
     * @brief 用户 ID。该字符串符合正则表达式：`[a-zA-Z0-9_@\-\.]{1,128}`。
     */
    const char* uid = nullptr;
    /** 
     * @brief 用户的额外信息，最大长度为 200 字节。会在 `onUserJoined` 中回调给远端用户。
     */
    const char* extra_info = nullptr;
};

/** 
 * @type keytype
 * @brief 通话相关的统计信息
 */
struct RtcRoomStats {
    /** 
     * @brief 当前应用的上行丢包率，取值范围为 [0, 1]
     */
    float txLostrate;
    /** 
     * @brief 当前应用的下行丢包率，取值范围为 [0, 1]
     */
    float rxLostrate;
    /** 
     * @brief 客户端到服务端数据传输的往返时延（单位 ms）
     */
    int rtt;
    /** 
     * @brief 进房到退房之间累计时长，单位为 s
     */
    unsigned int duration;
    /** 
     * @brief 本地用户的总发送字节数 (bytes)，累计值
     */
    unsigned int tx_bytes;
    /** 
     * @brief 本地用户的总接收字节数 (bytes)，累计值
     */
    unsigned int rx_bytes;
    /** 
     * @brief 发送码率（kbps），获取该数据时的瞬时值
     */
    unsigned short tx_kbitrate;
    /** 
     * @brief 接收码率（kbps），获取该数据时的瞬时值
     */
    unsigned short rx_kbitrate;
    /** 
     * @brief 音频接收码率（kbps），获取该数据时的瞬时值
     */
    unsigned short rx_audio_kbitrate;
    /** 
     * @brief 音频包的发送码率（kbps），获取该数据时的瞬时值
     */
    unsigned short tx_audio_kbitrate;
    /** 
     * @brief 视频接收码率（kbps），获取该数据时的瞬时值
     */
    unsigned short rx_video_kbitrate;
    /** 
     * @brief 视频发送码率（kbps），获取该数据时的瞬时值
     */
    unsigned short tx_video_kbitrate;
    /** 
     * @brief 屏幕接收码率，获取该数据时的瞬时值，单位为 Kbps
     */
    unsigned short rx_screen_kbitrate;
    /** 
     * @brief 屏幕发送码率，获取该数据时的瞬时值，单位为 Kbps
     */
    unsigned short tx_screen_kbitrate;
    /** 
     * @brief 当前房间内的可见用户人数
     */
    unsigned int user_count;
    /** 
     * @brief 当前应用的 CPU 使用率 (%)
     */
    double cpu_app_usage;
    /** 
     * @hidden currently not available
     * @brief 当前系统的 CPU 使用率 (%)
     */
    double cpu_total_usage;
    /** 
     * @brief 系统上行网络抖动（ms）
     */
    int tx_jitter;
    /** 
     * @brief 系统下行网络抖动（ms）
     */
    int rx_jitter;
    /** 
     * @brief 蜂窝路径发送的码率 (kbps)，为获取该数据时的瞬时值
     */
    unsigned short tx_cellular_kbitrate;
    /** 
     * @brief 蜂窝路径接收码率 (kbps)，为获取该数据时的瞬时值
     */
    unsigned short rx_cellular_kbitrate;
};

/** 
 * @type keytype
 * @brief 视频的编码类型
 */
enum VideoCodecType {
    /** 
     * @brief 未知类型
     */
    kVideoCodecTypeUnknown = 0,
    /** 
     * @brief 标准 H264 编码格式
     */
    kVideoCodecTypeH264 = 1,
    /** 
     * @brief ByteVC1 编码格式
     */
    kVideoCodecTypeByteVC1 = 2,
};


/** 
 * @type keytype
 * @hidden for internal use only
 * @brief 超分模式。
 */
enum VideoSuperResolutionMode {
    /** 
     * @brief 关闭超分。
     */
    kVideoSuperResolutionModeOff = 0,
    /** 
     * @brief 开启超分。
     */
    kVideoSuperResolutionModeOn = 1,
};

/** 
 * @type keytype
 * @brief 视频降噪模式。
 */
enum VideoDenoiseMode {
    /** 
     * @brief 视频降噪关闭。
     */
    kVideoDenoiseModeOff = 0,
    /** 
     * @brief 视频降噪开启，由 ByteRTC 后台配置视频降噪算法。
     */
    kVideoDenoiseModeAuto = 1,
};

/** 
 * @type keytype
 * @brief 本地音频流统计信息，统计周期为 2s 。  <br>
 *        本地用户发布音频流成功后，SDK 会周期性地通过 `onLocalStreamStats`
 *        通知用户发布的音频流在此次统计周期内的发送状况。此数据结构即为回调给用户的参数类型。  <br>
 */
struct LocalAudioStats {
    /** 
     * @brief 音频丢包率。此次统计周期内的音频上行丢包率，单位为 % ，取值范围为 [0, 1]。  <br>
     */
    float audio_loss_rate;
    /** 
     * @brief 发送码率。此次统计周期内的音频发送码率，单位为 kbps 。  <br>
     */
    int send_kbitrate;
    /** 
     * @brief 采集采样率。此次统计周期内的音频采集采样率信息，单位为 Hz 。  <br>
     */
    int record_sample_rate;
    /** 
     * @brief 统计间隔。此次统计周期的间隔，单位为 ms 。  <br>
     *        此字段用于设置回调的统计周期，默认设置为 2s 。
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
     * @brief 音频发送采样率。此次统计周期内的音频发送采样率信息，单位为 Hz 。  <br>
     */
    int sent_sample_rate;
    /** 
     * @brief 音频上行网络抖动，单位为 ms 。  <br>
     */
    int jitter;
};

/** 
 * @type keytype
 * @brief 远端音频流统计信息，统计周期为 2s。  <br>
 *        本地用户订阅远端音频流成功后，SDK 会周期性地通过 `onRemoteStreamStats` 通知本地用户订阅的音频流在此次统计周期内的接收状况。此数据结构即为回调给本地用户的参数类型。  <br>
 */
struct RemoteAudioStats {
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
     * @brief 用户体验级别的端到端延时。从发送端采集完成编码开始到接收端解码完成渲染开始的延时，单位为 ms 。  <br>
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
     * @brief 客户端到服务端数据传输的往返时延，单位为 ms。 <br>
     */
    int rtt;
    /** 
     * @brief 发送端——服务端——接收端全链路数据传输往返时延。单位为 ms 。  <br>
     */
    int total_rtt;
    /** 
     * @brief 远端用户发送的音频流质量。远端用户发送的音频流质量。值含义参考 NetworkQuality{@link #NetworkQuality}。
     */
    int quality;
    /** 
     * @brief 因引入 jitter buffer 机制导致的延时。单位为 ms 。  <br>
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
     * @brief 远端用户在加入房间后发生音频卡顿的累计时长占音频总有效时长的百分比。音频有效时长是指远端用户进房发布音频流后，除停止发送音频流和禁用音频模块之外的音频时长。
     */
    int frozen_rate;
    /** 
     * @brief 音频丢包补偿(PLC) 样点总个数。  <br>
     */
    int concealed_samples;
    /** 
     * @brief 音频丢包补偿(PLC) 累计次数。  <br>
     */
    int concealment_event;
    /** 
     * @brief 音频解码采样率。统计周期内的音频解码采样率信息，单位为 Hz 。  <br>
     */
    int dec_sample_rate;
    /** 
     * @brief 此次订阅中，对远端音频流进行解码的累计耗时。单位为 s。
     */
    int dec_duration;
    /** 
     * @brief 音频下行网络抖动，单位为 ms 。  <br>
     */
    int jitter;
};

/** 
 * @type keytype
 * @brief 本地视频流统计信息，统计周期为 2s 。  <br>
 *        本地用户发布视频流成功后，SDK 会周期性地通过 `onLocalStreamStats`
 *        通知用户发布的视频流在此次统计周期内的发送状况。此数据结构即为回调给用户的参数类型。  <br>
 */
struct LocalVideoStats {
    /** 
     * @brief 发送码率。此次统计周期内实际发送的分辨率最大的视频流的发送码率，单位为 Kbps
     */
    int sent_kbitrate;
    /** 
     * @brief 采集帧率。此次统计周期内的视频采集帧率，单位为 fps 。
     */
    int input_frame_rate;
    /** 
     * @brief 发送帧率。此次统计周期内实际发送的分辨率最大的视频流的视频发送帧率，单位为 fps 。
     */
    int sent_frame_rate;
    /** 
     * @brief 编码器输出帧率。当前编码器在此次统计周期内实际发送的分辨率最大的视频流的输出帧率，单位为 fps 。
     */
    int encoder_output_frame_rate;
    /** 
     * @brief 本地渲染帧率。此次统计周期内的本地视频渲染帧率，单位为 fps 。
     */
    int renderer_output_frame_rate;
    /** 
     * @brief 统计间隔，单位为 ms 。
     *        此字段用于设置回调的统计周期，默认设置为 2s 。
     */
    int stats_interval;
    /** 
     * @brief 视频丢包率。此次统计周期内的视频上行丢包率，取值范围为 [0，1] 。
     */
    float video_loss_rate;
    /** 
     * @brief 往返时延，单位为 ms 。
     */
    int rtt;
    /** 
     * @brief 视频编码码率。此次统计周期内的实际发送的分辨率最大的视频流视频编码码率，单位为 Kbps 。
     */
    int encoded_bitrate;
    /** 
     * @brief 实际发送的分辨率最大的视频流的视频编码宽度，单位为 px 。
     */
    int encoded_frame_width;
    /** 
     * @brief 实际发送的分辨率最大的视频流的视频编码高度，单位为 px 。
     */
    int encoded_frame_height;
    /** 
     * @brief 此次统计周期内实际发送的分辨率最大的视频流的发送的视频帧总数。
     */
    int encoded_frame_count;
    /** 
     * @brief 视频的编码类型，具体参考 VideoCodecType{@link #VideoCodecType} 。
     */
    VideoCodecType codec_type;
    /** 
     * @brief 所属用户的媒体流是否为屏幕流。你可以知道当前统计数据来自主流还是屏幕流。
     */
    bool is_screen;
    /** 
     * @brief 视频上行网络抖动，单位为 ms 。  <br>
     */
    int jitter;
    /** 
     * @brief 视频降噪模式。具体参看 VideoDenoiseMode{@link #VideoDenoiseMode} 。
     */
    VideoDenoiseMode video_denoise_mode;
};

/** 
 * @type keytype
 * @brief 远端视频流统计信息，统计周期为 2s 。  <br>
 *        本地用户订阅远端视频流成功后，SDK 会周期性地通过 `onRemoteStreamStats`
 *        通知本地用户订阅的远端视频流在此次统计周期内的接收状况。此数据结构即为回调给本地用户的参数类型。  <br>
 */
struct RemoteVideoStats {
    /** 
     * @brief 视频宽度
     */
    int width;
    /** 
     * @brief 视频高度
     */
    int height;
    /** 
     * @brief 视频丢包率。统计周期内的视频下行丢包率，单位为 % ，取值范围：[0，1] 。
     */
    float video_loss_rate;
    /** 
     * @brief 接收码率。统计周期内的视频接收码率，单位为 kbps 。
     */
    int received_kbitrate;
    /** 
     * @brief 解码器输出帧率。统计周期内的视频解码器输出帧率，单位 fps 。
     */
    int decoder_output_frame_rate;
    /** 
     * @brief 渲染帧率。统计周期内的视频渲染帧率，单位 fps 。
     */
    int renderer_output_frame_rate;
    /** 
     * @brief 卡顿次数。统计周期内的卡顿次数。
     */
    int stall_count;
    /** 
     * @brief 卡顿时长。统计周期内的视频卡顿总时长。单位 ms 。
     */
    int stall_duration;
    /** 
     * @brief 用户体验级别的端到端延时。从发送端采集完成编码开始到接收端解码完成渲染开始的延时，单位为 ms 。
     */
    long e2e_delay;
    /** 
     * @brief 所属用户的媒体流是否为屏幕流。你可以知道当前数据来自主流还是屏幕流。
     */
    bool is_screen;
    /** 
     * @brief 统计间隔，此次统计周期的间隔，单位为 ms 。  <br>
     *        此字段用于设置回调的统计周期，目前设置为 2s 。
     */
    int stats_interval;
    /** 
     * @brief 往返时延，单位为 ms 。
     */
    int rtt;
    /** 
     * @brief 远端用户在进房后发生视频卡顿的累计时长占视频总有效时长的百分比（%）。视频有效时长是指远端用户进房发布视频流后，除停止发送视频流和禁用视频模块之外的视频时长。
     */
    int frozen_rate;
    /** 
     * @brief 视频的编码类型，具体参考 VideoCodecType{@link #VideoCodecType} 。
     */
    VideoCodecType codec_type;
    /** 
     * @brief 对应多种分辨率的流的下标。
     */
    int video_index;
    /** 
     * @brief 视频下行网络抖动，单位为 ms。  <br>
     */
    int jitter;
    /** 
     * @hidden for internal use only
     * @brief 远端视频超分模式，参看 VideoSuperResolutionMode{@link #VideoSuperResolutionMode}。
     */
    VideoSuperResolutionMode super_resolution_mode;
};

/** 
 * @type keytype
 * @brief 本地音/视频流统计信息以及网络状况，统计周期为 2s 。  <br>
 *        本地用户发布音/视频流成功后，SDK 会周期性地通过 `onLocalStreamStats`
 *        通知本地用户发布的音/视频流在此次统计周期内的发送状况。此数据结构即为回调给用户的参数类型。  <br>
 */
struct LocalStreamStats {
    /** 
     * @brief 本地设备发送音频流的统计信息，详见 LocalAudioStats{@link #LocalAudioStats}
     */
    LocalAudioStats audio_stats;
    /** 
     * @brief 本地设备发送视频流的统计信息，详见 LocalVideoStats{@link #LocalVideoStats}
     */
    LocalVideoStats video_stats;
    /** 
     * @brief 所属用户的媒体流上行网络质量，详见 NetworkQuality{@link #NetworkQuality}
     * @deprecated since 3.36 and will be deleted in 3.51, use onNetworkQuality{@link #IRTCRoomEventHandler#onNetworkQuality} instead.
     */
    NetworkQuality local_tx_quality;
    /** 
     * @brief 所属用户的媒体流下行网络质量，详见 NetworkQuality{@link #NetworkQuality}
     * @deprecated since 3.36 and will be deleted in 3.51, use onNetworkQuality{@link #IRTCRoomEventHandler#onNetworkQuality} instead.
     */
    NetworkQuality local_rx_quality;
    /** 
     * @brief 所属用户的媒体流是否为屏幕流。你可以知道当前统计数据来自主流还是屏幕流。
     */
    bool is_screen;
};

/** 
 * @type keytype
 * @brief 用户订阅的远端音/视频流统计信息以及网络状况，统计周期为 2s 。  <br>
 *        订阅远端用户发布音/视频流成功后，SDK 会周期性地通过 `onRemoteStreamStats`
 *        通知本地用户订阅的远端音/视频流在此次统计周期内的接收状况。此数据结构即为回调给本地用户的参数类型。  <br>
 */
struct RemoteStreamStats {
    /** 
     * @brief 用户 ID 。音/视频来源的远端用户 ID 。  <br>
     */
    const char* uid;
    /** 
     * @brief 远端音频流的统计信息，详见 RemoteAudioStats{@link #RemoteAudioStats}
     */
    RemoteAudioStats audio_stats;
    /** 
     * @brief 远端视频流的统计信息，详见 RemoteVideoStats{@link #RemoteVideoStats}
     */
    RemoteVideoStats video_stats;
    /** 
     * @brief 所属用户的媒体流上行网络质量，详见 NetworkQuality{@link #NetworkQuality}
     * @deprecated since 3.36 and will be deleted in 3.51, use onNetworkQuality{@link #IRTCRoomEventHandler#onNetworkQuality} instead.
     */
    NetworkQuality remote_tx_quality;
    /** 
     * @brief 所属用户的媒体流下行网络质量，详见 NetworkQuality{@link #NetworkQuality}
     * @deprecated since 3.36 and will be deleted in 3.51, use onNetworkQuality{@link #IRTCRoomEventHandler#onNetworkQuality} instead.
     */
    NetworkQuality remote_rx_quality;
    /** 
     * @brief 所属用户的媒体流是否为屏幕流。你可以知道当前统计数据来自主流还是屏幕流。
     */
    bool is_screen;
};

/** 
 * @type keytype
 * @brief 音视频质量反馈问题类型
 */
enum ProblemFeedbackOption : uint64_t {
    /** 
     * @brief 没有问题
     */
    kProblemFeedbackOptionNone = 0,
    /** 
     * @brief 其他问题
     */
    kProblemFeedbackOptionOtherMessage = (1ULL << 0),
    /** 
     * @brief 连接失败
     */
    kProblemFeedbackOptionDisconnected = (1ULL << 1),
    /** 
     * @brief 耳返延迟大
     */
    kProblemFeedbackOptionEarBackDelay = (1ULL << 2),

    /** 
     * @brief 本端有杂音
     */
    kProblemFeedbackOptionLocalNoise = (1ULL << 10),
    /** 
     * @brief 本端声音卡顿
     */
    kProblemFeedbackOptionLocalAudioLagging = (1ULL << 11),
    /** 
     * @brief 本端无声音
     */
    kProblemFeedbackOptionLocalNoAudio = (1ULL << 12),
    /** 
     * @brief 本端声音大/小
     */
    kProblemFeedbackOptionLocalAudioStrength = (1ULL << 13),
    /** 
     * @brief 本端有回声
     */
    kProblemFeedbackOptionLocalEcho = (1ULL << 14),
    /** 
     * @brief 本端视频模糊
     */
    kProblemFeedbackOptionLocalVideoFuzzy = (1ULL << 24),
    /** 
     * @brief 本端音视频不同步
     */
    kProblemFeedbackOptionLocalNotSync = (1ULL << 25),
    /** 
     * @brief 本端视频卡顿
     */
    kProblemFeedbackOptionLocalVideoLagging = (1ULL << 26),
    /** 
     * @brief 本端无画面
     */
    kProblemFeedbackOptionLocalNoVideo = (1ULL << 27),

    /** 
     * @brief 远端有杂音
     */
    kProblemFeedbackOptionRemoteNoise = (1ULL << 37),
    /** 
     * @brief 远端声音卡顿
     */
    kProblemFeedbackOptionRemoteAudioLagging = (1ULL << 38),
    /** 
     * @brief 远端无声音
     */
    kProblemFeedbackOptionRemoteNoAudio = (1ULL << 39),
    /** 
     * @brief 远端声音大/小
     */
    kProblemFeedbackOptionRemoteAudioStrength = (1ULL << 40),
    /** 
     * @brief 远端有回声
     */
    kProblemFeedbackOptionRemoteEcho = (1ULL << 41),

    /** 
     * @brief 远端视频模糊
     */
    kProblemFeedbackOptionRemoteVideoFuzzy = (1ULL << 51),
    /** 
     * @brief 远端音视频不同步
     */
    kProblemFeedbackOptionRemoteNotSync = (1ULL << 52),
    /** 
     * @brief 远端视频卡顿
     */
    kProblemFeedbackOptionRemoteVideoLagging = (1ULL << 53),
    /** 
     * @brief 远端无画面
     */
    kProblemFeedbackOptionRemoteNoVideo = (1ULL << 54),
};

/** 
 * @type keytype
 * @brief 音视频质量反馈的房间信息
 */
struct ProblemFeedbackRoomInfo {
    /** 
     * @brief 房间 ID。
     */
    const char* room_id = nullptr;

    /** 
     * @brief 本地用户 ID。
     */
    const char* user_id = nullptr;
};

/** 
 * @type keytype
 * @brief 音视频质量反馈的信息
 */
struct ProblemFeedbackInfo {
    /** 
     * @brief 预设问题以外的其他问题的具体描述。
     */
    const char* problem_desc = nullptr;

    /** 
     * @type keytype
     * @brief 音视频质量反馈的房间信息。查看 ProblemFeedbackRoomInfo{@link #ProblemFeedbackRoomInfo}。
     */
    ProblemFeedbackRoomInfo* room_info = nullptr;
    /** 
     * @type keytype
     * @brief `FeedbackRoomInfo` 的数组长度。
     */
    int room_info_count = 0;
};

/** 
 * @type keytype
 * @brief 自定义加密类型  <br>
 */
enum EncryptType {
    /** 
     * @brief 不使用内置加密。默认值。
     */
    kEncryptTypeCustomize = 0,
    /** 
     * @brief AES-128-CBC 加密算法  <br>
     */
    kEncryptTypeAES128CBC = 1,
    /** 
     * @brief AES-256-CBC 加密算法  <br>
     */
    kEncryptTypeAES256CBC = 2,
    /** 
     * @brief AES-128-ECB 加密算法  <br>
     */
    kEncryptTypeAES128ECB = 3,
    /** 
     * @brief AES-256-ECB 加密算法  <br>
     */
    kEncryptTypeAES256ECB = 4
};

/** 
 * @type callback
 * @brief 加密/解密处理函数
 */
class IEncryptHandler {
public:
    /** 
     * @hidden constructor/destructor
     * @brief 析构函数
     */
    virtual ~IEncryptHandler() {
    }
    /** 
     * @type api
     * @region 加密
     * @brief 自定义加密。  <br>
     *        使用设定的自定义加密方式，对编码后传输前的音视频帧数据进行加密。<br>
     *        暂不支持对原始音视频帧进行加密。
     * @param data 原始音视频帧数据
     * @param length 原始音视频帧数据的长度
     * @param buf 可供写入的加密后数据缓冲区
     * @param buf_len 可供写入的加密后数据缓冲区大小
     * @return 加密后的数据  <br>
     *        + ≥ 0：加密后实际写入缓冲区的数据大小  <br>
     *        + 0：丢弃该帧  <br>
     * @notes <br>
     *        + 使用此接口进行自定义加密前，你必须先设置自定义加密方式，参看 `setCustomizeEncryptHandler`。
     *        + 使用 onDecryptData{@link #onDecryptData} 对已加密的音视频帧数据进行解密。
     *        + 返回的数据大小应控制在原始数据的 90% ~ 120% 范围以内，不然将被丢弃。
     */
    virtual unsigned int onEncryptData(
            const unsigned char* data, unsigned int length, unsigned char* buf, unsigned int buf_len) = 0;

    /** 
     * @type api
     * @region 加密
     * @brief 自定义解密。  <br>
     *        对自定义加密后的音视频帧数据进行解密。关于自定义加密，参看 onEncryptData{@link #IEncryptHandler#onEncryptData}。
     * @param data 原始音视频帧数据
     * @param length 原始音视频帧数据的长度
     * @param buf 可供写入的加密后数据缓冲区
     * @param buf_len 可供写入的加密后数据缓冲区大小
     * @return 加密后的数据  <br>
     *        + ≥ 0：加密后实际写入缓冲区的数据大小  <br>
     *        + 0：丢弃该帧  <br>
     * @notes <br>
     *        + 使用此接口进行解密前，你必须先设定解密方式，参看 `setCustomizeEncryptHandler`。
     *        + 返回的数据大小应控制在原始数据的 90% ~ 120% 范围以内，不然将被丢弃。
    */
   virtual unsigned int onDecryptData(
            const unsigned char* data, unsigned int length, unsigned char* buf, unsigned int buf_len) = 0;
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
 * @brief 音视频流的发送/播放状态
 */
enum MuteState {
    /** 
     * @brief 发送
     */
    kMuteStateOff = 0,
    /** 
     * @brief 停止发送
     */
    kMuteStateOn = 1,
};

/** 
 * @type keytype
 * @brief 流属性
 */
enum StreamIndex {
    /** 
     * @brief 主流。包括：<br>
     *        + 由摄像头/麦克风通过内部采集机制，采集到的视频/音频; <br>
     *        + 通过自定义采集，采集到的视频/音频。
     */
    kStreamIndexMain = 0,
    /** 
     * @brief 屏幕流。屏幕共享时共享的视频流，或来自声卡的本地播放音频流。
     */
    kStreamIndexScreen = 1,
};

/** 
 * @type keytype
 * @brief 远端流信息
 */
struct RemoteStreamKey {
   /** 
     * @brief 媒体流所在房间的房间 ID。<br>
     *        如果此媒体流是通过 `startForwardStreamToRooms` 转发到你所在房间的媒体流时，你应将房间 ID 设置为你所在的房间 ID。
     */
    const char* room_id;
    /** 
     * @brief 用户 ID
     */
    const char* user_id;
    /** 
     * @brief 流属性，主流或屏幕流。参看 StreamIndex{@link #StreamIndex}
     */
    StreamIndex stream_index;
};

/** 
 * @type keytype
 * @brief 本地录制文件的存储格式
 */
enum RecordingFileType {
    /** 
     * @brief aac 格式文件
     */
    kRecordingFileTypeAAC = 0,
    /** 
     * @brief mp4 格式文件
     */
    kRecordingFileTypeMP4 = 1,
};

/** 
 * @type keytype
 * @brief 本地录制的状态
 */
enum RecordingState {
    /** 
     * @brief 录制异常
     */
    kRecordingStateError = 0,
    /** 
     * @brief 录制进行中
     */
    kRecordingStateProcessing = 1,
    /** 
     * @brief 录制文件保存成功，调用 `stopFileRecording` 结束录制之后才会收到该状态码。
     */
    kRecordingStateSuccess = 2,
};

/** 
 * @type keytype
 * @brief 本地录制的错误码
 */
enum RecordingErrorCode {
    /** 
     * @brief 录制正常
     */
    kRecordingErrorCodeOk = 0,
    /** 
     * @brief 没有文件写权限
     */
    kRecordingErrorCodeNoPermission = -1,
    /** 
     * @brief 当前版本 SDK 不支持本地录制功能，请联系技术支持人员
     */
    kRecordingErrorCodeNotSupport = -2,
    /** 
     * @brief 其他异常
     */
    kRecordingErrorCodeOther = -3,
};

/** 
 * @type keytype
 * @brief 本地录制进度
 */
struct RecordingProgress {
    /** 
     * @brief 当前文件的累计录制时长，单位：毫秒
     */
    unsigned long long duration;
    /** 
     * @brief 当前录制文件的大小，单位：byte
     */
    unsigned long long file_size;
};

/** 
 * @type keytype
 * @brief 本地录制的详细信息
 */
struct RecordingInfo {
    /** 
     * @brief 录制文件的绝对路径，包含文件名和文件后缀
     */
    const char* file_path;
    /** 
     * @brief 录制文件的视频编码类型，参看 VideoCodecType{@link #VideoCodecType}
     */
    VideoCodecType video_codec_type;
    /** 
     * @brief 录制视频的宽，单位：像素。纯音频录制请忽略该字段
     */
    int width;
    /** 
     * @brief 录制视频的高，单位：像素。纯音频录制请忽略该字段
     */
    int height;
};

/** 
 * @type keytype
 * @brief 本地录制参数配置
 */
struct RecordingConfig {
    /** 
     * @brief 录制文件保存的绝对路径，需精确到文件夹，文件名由 RTC 自动生成。你需要确保对该路径具有读写权限。
     */
    const char* dir_path;
    /** 
     * @brief 录制存储文件格式，参看 RecordingFileType{@link #RecordingFileType}
     */
    RecordingFileType file_type;
};

/** 
 * @type keytype
 * @brief 定义linux用户的用户功能  <br>
 */
enum UserWorkerType {
    /** 
     * @brief 正常用户，没有任何特殊属性  <br>
     */
    UserWorkerNormal = 0,
    /** 
     * @brief 用户支持SIP流，信令只下发SIP流  <br>
     */
    UserWorkerSupportSip = (1 << 0),
    /** 
     * @brief 用户支持屏幕流的bytevc1到H264转码  <br>
     */
    UserWorkerByteVc1Transcoder = (1 << 1),
    /** 
     * @brief 用户需要信令服务器下发全量的用户列表和回调函数  <br>
     */
    UserWorkerNeedUserListAndCb = (1 << 2),
    /** 
     * @brief 用户需要在房间进入多人模式时获取房间内所有流的相关回调  <br>
     */
    UserWorkerNeedStreamCallBack = (1 << 3),
    /** 
     * @brief 用户选择设置不支持音频选路功能  <br>
     */
    UserWorkerAudioSelectionExemption = (1 << 4),
};

/** 
 * @type keytype
 * @brief 音视频同步状态
 */
enum AVSyncState {
    /** 
     * @brief 音视频开始同步
     */
    kAVSyncStateAVStreamSyncBegin = 0,
    /** 
     * @brief 音视频同步过程中音频移除，但不影响当前的同步关系
     */
    kAVSyncStateAudioStreamRemove,
    /** 
     * @brief 音视频同步过程中视频移除，但不影响当前的同步关系
     */
    kAVSyncStateVdieoStreamRemove,
    /** 
     * @hidden for internal use only
     * @brief 订阅端设置同步  <br>
     */
    kAVSyncStateSetAVSyncStreamId,
};

/**
 * @hidden
 * @deprecated
 * @type keytype
 */
enum RtcRoomMode {
    kRtcRoomNormalMode = 0,
    kRtcRoomAudioSelectionMode = 1,
};

/** 
 * @type keytype
 * @brief 媒体流信息同步的流类型
 */
enum SyncInfoStreamType {
    /** 
     * @brief 音频流
     */
    kSyncInfoStreamTypeAudio = 0
};

/** 
 * @type keytype
 * @brief 媒体流信息同步的相关配置
 */
struct StreamSycnInfoConfig {
    /** 
     * @brief 流属性，主流或屏幕流。见 StreamIndex{@link #StreamIndex}
     */
    StreamIndex stream_index;
    /** 
     * @brief 消息发送的重复次数，取值范围是 [0,25]，建议设置为 [3,5]。
     */
    int repeat_count;
    /** 
     * @brief 媒体流信息同步的流类型，见 SyncInfoStreamType{@link #SyncInfoStreamType}
     */
    SyncInfoStreamType stream_type;
};

/** 
 * @type keytype
 * @brief 媒体流跨房间转发的目标房间的相关信息
 */
struct ForwardStreamInfo {
    /** 
     * @brief 使用转发目标房间 roomID 和 UserID 生成 Token。<br>
     *        测试时可使用控制台生成临时 Token，正式上线需要使用密钥 SDK 在你的服务端生成并下发 Token。<br>
     *        如果 Token 无效，转发失败。
     */
    const char* token;
    /** 
     * @brief 跨间转发媒体流过程中目标房间 ID<br>
     */
    const char* room_id;
};

/** 
 * @type keytype
 * @brief 媒体流跨房间转发的目标房间的相关信息
 */
struct ForwardStreamConfiguration {
    /** 
     * @brief 目标房间信息，数组中的每个元素包含一个房间的信息。
     */
    ForwardStreamInfo* forward_stream_dests = nullptr;
    /** 
     * @brief 目标房间数量。媒体流同时转发的目标房间数量建议小于等于 4 个。
     */
    int dest_count = 0;
};

/** 
 * @type keytype
 * @brief 媒体流跨房间转发状态
 */
enum ForwardStreamState {
    /** 
     * @brief 空闲状态
     *        + 成功调用 `stopForwardStreamToRooms` 后，所有目标房间为空闲状态。
     *        + 成功调用 `updateForwardStreamToRooms` 减少目标房间后，本次减少的目标房间为空闲状态。
     */
    kForwardStreamStateIdle = 0,
    /** 
     * @brief 开始转发
     *        + 调用 `startForwardStreamToRooms` 成功向所有房间开始转发媒体流后，返回此状态。
     *        + 调用 `updateForwardStreamToRooms` 后，成功向新增目标房间开始转发媒体流后，返回此状态。
     */
    kForwardStreamStateSuccess = 1,
    /** 
     * @brief 转发失败，失败详情参考 ForwardStreamError{@link #ForwardStreamError}
     *        调用 `startForwardStreamToRooms` 或 `updateForwardStreamToRooms` 后，如遇转发失败，返回此状态。
     */
    kForwardStreamStateFailure = 2,
};

/** 
 * @type keytype
 * @brief 媒体流跨房间转发过程中抛出的错误码
 */
enum ForwardStreamError {
    /** 
     * @brief 正常
     */
    kForwardStreamErrorOK = 0,
    /** 
     * @brief 参数异常
     */
    kForwardStreamErrorInvalidArgument = 1201,
    /** 
     * @brief token 错误
     */
    kForwardStreamErrorInvalidToken = 1202,
    /** 
     * @brief 服务端异常
     */
    kForwardStreamErrorResponse = 1203,
    /** 
     * @brief 目标房间有相同 user id 的用户加入，转发中断
     */
    kForwardStreamErrorRemoteKicked = 1204,
    /** 
     * @brief 服务端不支持转发功能
     */
    kForwardStreamErrorNotSupport = 1205,
};

/** 
 * @type keytype
 * @brief 媒体流跨房间转发事件
 */
enum ForwardStreamEvent {
    /** 
     * @brief 本端与服务器网络连接断开，暂停转发。
     */
    kForwardStreamEventDisconnected = 0,
    /** 
     * @brief 本端与服务器网络连接恢复，转发服务连接成功。
     */
    kForwardStreamEventConnected = 1,
    /** 
     * @brief 转发中断。转发过程中，如果相同 user_id 的用户进入目标房间，转发中断。
     */
    kForwardStreamEventInterrupt = 2,
    /** 
     * @brief 目标房间已更新，由 `updateForwardStreamToRooms` 触发。
     */
    kForwardStreamEventDstRoomUpdated = 3,
    /** 
     * @brief API 调用时序错误。例如，在调用 `startForwardStreamToRooms` 之前调用 `updateForwardStreamToRooms` 。
     */
    kForwardStreamEventUnExpectAPICall = 4,
};

/** 
 * @type keytype
 * @brief 跨房间转发媒体流过程中的不同目标房间的状态和错误信息
 */
struct ForwardStreamStateInfo {
    /** 
     * @brief 跨间转发媒体流过程中目标房间 ID<br>
     */
    const char* room_id;
    /** 
     * @brief 跨房间转发媒体流过程中该目标房间的状态，参看 ForwardStreamState{@link #ForwardStreamState}
     */
    ForwardStreamState state;
    /** 
     * @brief 跨房间转发媒体流过程中该目标房间抛出的错误码，参看 ForwardStreamError{@link #ForwardStreamError}
     */
    ForwardStreamError error;
};

/** 
 * @type keytype
 * @brief 跨房间转发媒体流过程中的不同目标房间发生的事件
 */
struct ForwardStreamEventInfo {
    /** 
     * @brief 跨房间转发媒体流过程中的发生该事件的目标房间 ID<br>
     *        空字符串代表所有目标房间
     */
    const char* room_id;
    /** 
     * @brief 跨房间转发媒体流过程中该目标房间发生的事件，参看 ForwardStreamEvent{@link #ForwardStreamEvent}
     */
    ForwardStreamEvent event;
};

/** 
 * @type keytype
 * @brief 水印图片相对视频流的位置和大小。
 */
struct ByteWatermark {
    /**
     * @hidden currently not available
     */
    const char* url = nullptr;
    /** 
     * @brief 水印图片相对视频流左上角的横向偏移与视频流宽度的比值，取值范围为 [0,1)。
     */
    float x;
    /** 
     * @brief 水印图片相对视频流左上角的纵向偏移与视频流高度的比值，取值范围为 [0,1)。
     */
    float y;
    /** 
     * @brief 水印图片宽度与视频流宽度的比值，取值范围 [0,1)。
     */
    float width;
    /** 
     * @brief 水印图片高度与视频流高度的比值，取值范围为 [0,1)。
     */
    float height;
};

/** 
 * @type keytype
 * @brief 水印参数
 */
struct RTCWatermarkConfig {
    /** 
     * @type keytype
     * @brief 水印是否在视频预览中可见，默认可见。
     */
    bool visibleInPreview = true;
    /** 
     * @type keytype
     * @brief 横屏时的水印位置和大小，参看 ByteWatermark{@link #ByteWatermark}。
     */
    ByteWatermark positionInLandscapeMode;
    /** 
     * @type keytype
     * @brief 视频编码的方向模式为竖屏时的水印位置和大小，参看 ByteWatermark{@link #ByteWatermark}。
     */
    ByteWatermark positionInPortraitMode;
};

/** 
 * @type keytype
 * @brief 设备的传输方式
 */
enum DeviceTransportType {
    /** 
     * @brief 未知类型
     */
    kDeviceTransportTypeUnknown = 0,
    /** 
     * @brief 系统内置
     */
    kDeviceTransportTypeBuiltIn = 1,
    /** 
     * @brief 未知模式蓝牙
     */
    kDeviceTransportTypeBlueToothUnknownMode = 2,
    /** 
     * @brief 免提模式蓝牙
     */
    kDeviceTransportTypeBlueToothHandsFreeMode = 3,
    /** 
     * @brief 立体声模式蓝牙
     */
    kDeviceTransportTypeBlueToothStereoMode = 4,
    /** 
     * @brief 显示器/电视机音频设备
     */
    kDeviceTransportTypeDisplayAudio = 5,
    /** 
     * @brief 虚拟设备
     */
    kDeviceTransportTypeVirtual = 6,
    /** 
     * @brief USB设备
     */
    kDeviceTransportTypeUSB = 7,
    /** 
     * @brief PCI设备
     */
    kDeviceTransportTypePCI = 8,
    /** 
     * @brief AirPlay设备
     */
    kDeviceTransportTypeAirPlay = 9,
    /** 
     * @brief 连续互通相机
     */
    kDeviceTransportTypeContinuityCamera = 100,
};

/** 
 * @type keytype
 * @brief 音视频回路测试结果
 */
enum class EchoTestResult {
    /** 
     * @brief 接收到采集的音视频的回放，通话回路检测成功
     */
    kTestSuccess = 0,
    /** 
     * @brief 测试超过 60s 仍未完成，已自动停止
     */
    kTestTimeout,
    /** 
     * @brief 上一次测试结束和下一次测试开始之间的时间间隔少于 5s
     */
    kTestIntervalShort,
    /** 
     * @brief 音频采集异常
     */
    kAudioDeviceError,
    /** 
     * @brief 视频采集异常
     */
    kVideoDeviceError,
    /** 
     * @brief 音频接收异常
     */
    kAudioReceiveError,
    /** 
     * @brief 视频接收异常
     */
    kVideoReceiveError,
    /** 
     * @brief 内部错误，不可恢复
     */
    kInternalError
};

/** 
 * @type keytype
 * @brief 音视频回路测试参数
 */
struct EchoTestConfig {
    /** 
     * @brief 用于渲染接收到的视频的视图
     */
    void* view;
    /** 
     * @brief 是否检测音频。检测设备为系统默认音频设备。  <br>
     *        + true：是  <br>
     *            - 若使用 SDK 内部采集，此时设备麦克风会自动开启，并在 audioPropertiesReportInterval 值大于 0 时触发 `onLocalAudioPropertiesReport` 回调，你可以根据该回调判断麦克风的工作状态  <br>
     *            - 若使用自定义采集，此时你需调用 pushExternalAudioFrame{@link #IRTCVideo#pushExternalAudioFrame} 将采集到的音频推送给 SDK  <br>
     *        + flase：否  <br>
     */
    bool enableAudio;
    /** 
     * @brief 是否检测视频。PC 端默认检测列表中第一个视频设备。  <br>
     *        + true：是  <br>
     *            - 若使用 SDK 内部采集，此时设备摄像头会自动开启  <br>
     *            - 若使用自定义采集，此时你需调用 pushExternalVideoFrame{@link #IRTCVideo#pushExternalVideoFrame} 将采集到的视频推送给 SDK  <br>
     *        + flase：否  <br>
     * @notes 视频的发布参数固定为：分辨率 640px × 360px，帧率 15fps。
     */
    bool enableVideo;
    /** 
     * @brief 音量信息提示间隔，单位：ms，默认为 100ms <br>
     *       + `<= 0`: 关闭信息提示  <br>
     *       + `(0,100]`: 开启信息提示，不合法的 interval 值，SDK 自动设置为 100ms  <br>
     *       + `> 100`: 开启信息提示，并将信息提示间隔设置为此值  <br>
     */
    int audioPropertiesReportInterval;
    /** 
     * @brief 进行音视频通话回路测试的用户 ID
     */
    const char* uid;
    /** 
     * @brief 测试用户加入的房间 ID。  <br>
     */
    const char* roomId;
    /** 
     * @brief 对用户进房时进行鉴权验证的动态密钥，用于保证音视频通话回路测试的安全性。
     */
    const char* token;
};

/** 
 * @type keytype
 * @brief 音频dump状态。  <br>
 */
enum AudioDumpStatus {
    /** 
     * @brief 音频dump启动失败
     */
     kAudioDumpStartFailure = 0,
    /** 
     * @brief 音频dump启动成功
     */
    kAudioDumpStartSuccess = 1,
    /** 
     * @brief 音频dump停止失败
     */
    kAudioDumpStopFailure = 2,
    /** 
     * @brief 音频dump停止成功
     */
    kAudioDumpStopSuccess = 3,
    /** 
     * @brief 音频dump运行失败
     */
    kAudioDumpRunningFailure = 4,
    /** 
     * @brief 音频dump运行成功
     */
    kAudioDumpRunningSuccess = 5,
};

/** 
 * @type errorcode
 * @brief 开始探测的返回值
 *        `startNetworkDetection` 返回对象类型
 */
enum NetworkDetectionStartReturn {
    /** 
     * @brief 成功开启网络探测。
     */
    kNetworkDetectionStartReturnSuccess = 0,
    /** 
     * @brief 开始探测失败。参数错误，上下行探测均为 `false`，或期望带宽超过了范围 [100,10000]
     */
    kNetworkDetectionStartReturnParamErr = 1,
    /** 
     * @brief 开始探测失败。失败原因为，本地已经开始推拉流
     */
    kNetworkDetectionStartReturnStreaming = 2,
    /** 
     * @brief 已经开始探测，无需重复开启
     */
    kNetworkDetectionStartReturnStarted = 3,
    /** 
     * @brief 不支持该功能
     */
    kNetworkDetectionStartReturnNotSupport = 4,
};

/** 
 * @type keytype
 * @brief 通话前探测的停止原因
 *        `onNetworkDetectionStopped` 回调的参数类型
 */
enum NetworkDetectionStopReason {
    /** 
     * @brief 用户主动停止
     */
    kNetworkDetectionStopReasonUser,
    /** 
     * @brief 探测超过三分钟
     */
    kNetworkDetectionStopReasonTimeout,
    /** 
     * @brief 探测网络连接断开。<br>当超过 12s 没有收到回复，SDK 将断开网络连接，并且不再尝试重连。
     */
    kNetworkDetectionStopReasonConnectionLost,
    /** 
     * @brief 本地开始推拉流，停止探测
     */
    kNetworkDetectionStopReasonStreaming,
    /** 
     * @brief 网络探测失败，内部异常
     */
    kNetworkDetectionStopReasonInnerErr,
};

/** 
 * @type keytype
 * @brief 通话前探测链接的类型。
 *        `onNetworkDetectionResult` 回调的参数类型
 */
enum NetworkDetectionLinkType {
    /** 
     * @brief 上行网络探测
     */
    kNetworkDetectionLinkTypeUp = 0,
    /** 
     * @brief 下行网络探测
     */
    kNetworkDetectionLinkTypeDown,
};

/** 
 * @type keytype
 * @brief 网络时间信息
 */
struct NetworkTimeInfo {
    /** 
     * @brief 网络时间，单位：ms
     */
    int64_t timestamp;
    /**
     * @hidden constructor/destructor
     */
    explicit NetworkTimeInfo(int64_t ts): timestamp(ts) {
    }
};

/** 
 * @type keytype
 * @brief 通话前回声检测结果
 */
enum HardwareEchoDetectionResult{
    /** 
     * @brief 主动调用 `stopHardwareEchoDetection` 结束流程时，未有回声检测结果。
     */
    kHardwareEchoDetectionCanceled = 0,
    /** 
     * @brief 未检测出结果。建议重试，如果仍然失败请联系技术支持协助排查。
     */
    kHardwareEchoDetectionUnknown = 1,
    /** 
     * @brief 无回声
     */
    kHardwareEchoDetectionNormal = 2,
    /** 
     * @brief 有回声。可通过 UI 建议用户使用耳机设备入会。
     */
    kHardwareEchoDetectionPoor = 3,
};

/** 
 * @type keytype
 * @brief 音频选路优先级设置
 */
enum AudioSelectionPriority {
    /** 
     * @brief 正常，参加音频选路
     */
    kAudioSelectionPriorityNormal = 0,
    /** 
     * @brief 高优先级，跳过音频选路
     */
    kAudioSelectionPriorityHigh = 1
};

/** 
 * @type keytype
 * @brief 设置房间附加消息结果。
 */
enum SetRoomExtraInfoResult {
    /** 
     * @brief 设置房间附加信息成功
     */
    kSetRoomExtraInfoSuccess = 0,
    /** 
     * @brief 设置失败，尚未加入房间
     */
    kSetRoomExtraInfoErrorNotJoinRoom = -1,
    /** 
     * @brief 设置失败，key 指针为空
     */
    kSetRoomExtraInfoErrorKeyIsNull = -2,
    /** 
     * @brief 设置失败，value 指针为空
     */
    kSetRoomExtraInfoErrorValueIsNull = -3,
    /** 
     * @brief 设置失败，未知错误
     */
    kSetRoomExtraInfoResultUnknow = -99,
    /** 
     * @brief 设置失败，key 长度为 0
     */
    kSetRoomExtraInfoErrorKeyIsEmpty = -400,
    /** 
     * @brief 调用 `setRoomExtraInfo` 过于频繁，建议不超过 10 次/秒。
     */
    kSetRoomExtraInfoErrorTooOften = -406,
    /** 
     * @brief 设置失败，用户已调用 `setUserVisibility` 将自身设为隐身状态。
     */
    kSetRoomExtraInfoErrorSilentUser = -412,
    /** 
     * @brief 设置失败，Key 长度超过 10 字节
     */
    kSetRoomExtraInfoErrorKeyTooLong = -413,
    /** 
     * @brief 设置失败，value 长度超过 128 字节
     */
    kSetRoomExtraInfoErrorValueTooLong = -414,
    /** 
     * @brief 设置失败，服务器错误
     */
    kSetRoomExtraInfoErrorServer = -500
};
/**  
 * @type keytype
 * @brief 字幕任务状态。
 */
enum SubtitleState {
    /** 
     * @brief 开启字幕。
     */
    kSubtitleStateStarted,
    /** 
     * @brief 关闭字幕。
     */
    kSubtitleStateStoped,
    /** 
     * @brief 字幕任务出现错误。
     */
    kSubtitleStateError
};
/**  
 * @type keytype
 * @brief 字幕模式。
 */
enum SubtitleMode {
    /** 
     * @brief 识别模式。在此模式下，房间内用户语音会被转为文字。
     */
    kSubtitleModeRecognition = 0,
    /** 
     * @brief 翻译模式。在此模式下，房间内用户语音会先被转为文字，再被翻译为目标语言。
     */
    kSubtitleModeTranslation
};
/**  
 * @type keytype
 * @brief 字幕任务错误码。
 */
enum SubtitleErrorCode {
    /** 
     * @brief 客户端无法识别云端媒体处理发送的错误码。请联系技术支持。 
     */
    kSubtitleErrorCodeUnknow = -1,
    /** 
     * @brief 字幕已开启。
     */
    kSubtitleErrorCodeSuccess,
    /** 
     * @brief 云端媒体处理内部出现错误，请联系技术支持。
     */
    kSubtitleErrorCodePostProcessError,
    /** 
     * @brief 第三方服务连接失败，请联系技术支持。
     */
    kSubtitleErrorCodeASRConnectionError,
    /** 
     * @brief 第三方服务内部出现错误，请联系技术支持。
     */
    kSubtitleErrorCodeASRServiceError,
    /** 
     * @brief 未进房导致调用`startSubtitle`失败。请加入房间后再调用此方法。
     */
    kSubtitleErrorCodeBeforeJoinRoom,
    /** 
     * @brief 重复调用 `startSubtitle`。
     */
    kSubtitleErrorCodeAlreadyOn,
    /** 
     * @brief 用户选择的目标语言目前暂不支持。
     */
    kSubtitleErrorCodeUnsupportedLanguage,
    /** 
     * @brief 云端媒体处理超时未响应，请联系技术支持。
     */
    kSubtitleErrorCodePostProcessTimeout
};
/**  
 * @type keytype
 * @brief 字幕配置信息。
 */
struct SubtitleConfig {
   /** 
    * @brief 字幕模式。可以根据需要选择识别和翻译两种模式。开启识别模式，会将识别后的用户语音转化成文字；开启翻译模式，会在语音识别后进行翻译。参看 SubtitleMode{@link #SubtitleMode}。
    */
   SubtitleMode mode;
   /** 
    * @brief 目标翻译语言。可点击 [语言支持](https://www.volcengine.com/docs/4640/35107#%E7%9B%AE%E6%A0%87%E8%AF%AD%E8%A8%80-2) 查看翻译服务最新支持的语种信息。
    */
   const char* target_language = "";
};
/**  
 * @type keytype
 * @brief 字幕具体内容。
 */
struct SubtitleMessage {
    /** 
     * @brief 说话者的用户ID。
     */
    const char* user_id;
    /** 
     * @brief 语音识别或翻译后的文本, 采用 UTF-8 编码。
     */
    const char* text;
    /** 
     * @brief 语音识别或翻译后形成的文本的序列号，同一发言人的完整发言和不完整发言会按递增顺序单独分别编号。
     */
    int sequence;
    /** 
     * @brief 语音识别出的文本是否为一段完整的一句话。 True 代表是, False 代表不是。
     */
    bool definite;
};

}  // namespace bytertc
