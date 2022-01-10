/*
 * Copyright (c) 2020 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngine Common Defines
 */

#pragma once

#ifndef BYTE_RTC_DEFINES_H__
#define BYTE_RTC_DEFINES_H__

#ifdef WIN32
#define BYTERTC_API extern "C" __declspec(dllexport)
#elif __APPLE__
#include <TargetConditionals.h>
#if TARGET_OS_MAC && !(TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
#define BYTERTC_API __attribute__((__visibility__("default"))) extern "C"
#else
#define BYTERTC_API __attribute__((__visibility__("default")))
#endif
#else
#define BYTERTC_API __attribute__((__visibility__("default")))
#endif

#include "bytertc_video_frame.h"
namespace bytertc {
/**
 * @type keytype
 * @brief 渲染模式
 */
enum RenderMode {
    /**
     * @brief 视窗填满优先。<br>
     *        视频帧等比缩放，直至视窗被视频填满。如果视频帧长宽比例与视窗不同，视频帧的多出部分将无法显示。<br>
     *        缩放完成后，视频帧的一边长和视窗的对应边长一致，另一边长大于等于视窗对应边长。
     */
    kRenderModeHidden = 1,
    /**
     * @brief 视频帧内容全部显示优先。<br>
     *        视频帧等比缩放，直至视频帧能够在视窗上全部显示。如果视频帧长宽比例与视窗不同，视窗上未被视频帧填满区域将被涂黑。<br>
     *        缩放完成后，视频帧的一边长和视窗的对应边长一致，另一边长小于等于视窗对应边长。
     */
    kRenderModeFit = 2,
    /**
     * @hidden
     * @brief 暂时不支持设置为该值
     */
    kRenderModeAdaptive = 3,
};

/**
 * @type keytype
 * @brief 用户离开房间的原因。  <br>
 */
enum UserOfflineReason {
    /**
     * @brief 远端用户调用 LeaveRoom{@link #IRtcRoom#LeaveRoom} 方法主动退出房间，或切换为不可见。  <br>
     */
    kUserOfflineReasonQuit = 0,
    /**
     * @brief 远端用户因网络等原因掉线，或切换至隐身状态。  <br>
     */
    kUserOfflineReasonDropped = 1,
    /**
     * @hidden
     */
    kUserOfflineReasonBecomeAudience = 2,
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
};

/**
 * @type keytype
 * @brief 用户角色。  <br>
 */
enum UserRoleType {
    /**
     * @brief 主播角色。该角色用户可在房间内发布和订阅音视频流，房间中的其他用户可以感知到该用户的存在。  <br>
     */
    kUserRoleTypeBroadcaster = 1,
    /**
     * @brief 静默观众角色。该众角色用户只可在房间内订阅音视频流，房间中的其他用户无法感知到该用户的存在。  <br>
     */
    kUserRoleTypeSilentAudience = 2,
};

/**
 * @type keytype
 * @brief 用户加入房间的类型。  <br>
 */
enum JoinRoomType {
    /**
     * @brief 首次加入房间。用户手动调用 JoinRoom{@link #IRtcRoom#JoinRoom}，收到加入成功。  <br>
     */
    kJoinRoomTypeFirst = 0,
    /**
     * @brief 重新加入房间。用户网络较差，失去与服务器的连接，进行重连时收到加入成功。  <br>
     */
    kJoinRoomTypeReconnected = 1,
};

/**
 * @type keytype
 * @brief 用户登录的类型
 */
enum LoginType {
    /**
     * @brief 首次登录。用户手动调用 Login{@link #IRtcEngineLite#Login}，收到登录成功。
     */
    kLoginTypeFirst = 0,
    /**
     * @brief 重连。用户网络较差，失去与服务器的连接，SDK 自动重连登录成功。
     */
    kLoginTypeReconnected = 1,
};
/**
 * @type errorcode
 * @brief 向房间内单个用户发送消息（P2P）的结果
 */
enum UserMessageSendResult {
    /**
     * @brief 向房间内单个用户发送消息成功
     */
    kUserMessageSendResultSuccess = 0,
    /**
     * @brief 发送超时，没有发送
     */
    kUserMessageSendResultTimeout = 1,
    /**
     * @brief 通道断开，没有发送
     */
    kUserMessageSendResultBroken = 2,
    /**
     * @brief 找不到接收方
     */
    kUserMessageSendResultNoReceiver = 3,
    /**
     * @brief 获取级联路径失败
     */
    kUserMessageSendResultNoRelayPath = 4,
    /**
     * @brief 消息发送方没有加入房间
     */
    kUserMessageSendResultNotJoin = 100,
    /**
     * @brief 连接未完成初始化
     */
    kUserMessageSendResultInit = 101,
    /**
     * @brief 没有可用的数据传输通道连接
     */
    kUserMessageSendResultNoConnection = 102,
    /**
     * @brief 消息超过最大长度，当前为 64 KB
     */
    kUserMessageSendResultExceedMaxLength = 103,
    /**
     * @brief 接收消息的单个用户 id 为空
     */
    kUserMessageSendResultEmptyUser = 104,
    /**
     * @brief 房间外或业务服务器消息发送方没有登录
     */
    kUserMessageSendResultNotLogin = 105,
    /**
     * @brief 发送消息给业务方服务器之前没有设置参数
     */
    kUserMessageSendResultServerParamsNotSet = 106,
    /**
     * @brief 未知错误
     */
    kUserMessageSendResultUnknown = 1000,
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
    kRoomMessageSendResultNotJoin = 100,
    /**
     * @brief 没有可用的数据传输通道连接
     */
    kRoomMessageSendResultNoConnection = 102,
    /**
     * @brief 消息超过最大长度，当前为64KB
     */
    kRoomMessageSendResultExceedMaxLength = 103,
    /**
     * @brief 未知错误
     */
    kRoomMessageSendResultUnknown = 1000,
};

/**
 * @type keytype
 * @brief SDK 与信令服务器连接状态。
 */
enum ConnectionState {
    /**
     * @brief 连接断开。
     */
    kConnectionStateDisconnected = 1,
    /**
     * @brief 首次连接，正在连接中。
     */
    kConnectionStateConnecting = 2,
    /**
     * @brief 首次连接成功。
     */
    kConnectionStateConnected = 3,
    /**
     * @brief 连接断开后重新连接中。
     */
    kConnectionStateReconnecting = 4,
    /**
     * @brief 连接断开后重连成功。
     */
    kConnectionStateReconnected = 5,
    /**
     * @brief 网络连接断开超过 10 秒，仍然会继续重连。
     */
    kConnectionStateLost = 6,
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
 * @brief 用户维度媒体流网络质量。
 */
struct UserNetworkQualityMsg {
    /**
     * @brief 自己或者远端用户的 uid。
     */
    const char* uid;
    /**
     * @brief 端到端的丢包，取值 （0~1）
     */
    double fraction_lost;
    /**
     * @brief 端到端的往返延时，单位：ms
     */
    int rtt;
    /**
     * @brief rtp包的传输总量，单位：bps
     */
    int total_bandwidth;
    /**
     * @brief 上行质量分，取值见 NetworkQuality
     */
    int tx_quality;
    /**
     * @brief 下行质量分，取值见 NetworkQuality
     */
    int rx_quality;
    UserNetworkQualityMsg() : uid(""), fraction_lost(0.), rtt(0), total_bandwidth(0), tx_quality(0), rx_quality(0) {
    }
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
 * @brief 性能回退
 */
enum PublishFallbackOption {
    /**
     * @brief 关闭发送视频流时的性能回退功能，默认值
     */
    kPublishFallbackOptionDisabled = 0,
    /**
     * @brief 开启在网络情况不佳或设备性能不足时只发送小流的功能
     */
    kPublishFallbackOptionSimulcast = 1,
};

/**
 * @hidden
 * @deprecated
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
 * @brief 房间模式
 */
enum RoomProfileType {
    /**
     * @brief 普通音视频通话模式。<br>
     *        你应在 1V1 音视频通话时，使用此设置。<br>
     *        此设置下，弱网抗性较好。
     */
    kRoomProfileTypeCommunication = 0,
    /**
     * @brief 直播模式。<br>
     *        当你对音视频通话的音质和画质要求较高时，应使用此设置。<br>
     *        此设置下，当用户使用蓝牙耳机收听时，蓝牙耳机使用媒体模式。
     */
    kRoomProfileTypeLiveBroadcasting = 1,
    /**
     * @brief 游戏语音模式。此模式下延时较低。<br>
     *        低端机在此模式下运行时，进行了额外的性能优化：<br>
     *            + 采集播放采用 16kHz 单通道采样 <br>
     *            + 部分低端机型配置编码帧长 40/60 <br>
     *            + 部分低端机型关闭软件 3A 音频处理 <br>
     *        增强对 iOS 其他屏幕录制进行的兼容性，避免音频录制被 RTC 打断。
     */
    kRoomProfileTypeGame = 2,
    /**
     * @brief 云游戏模式。<br>
     *        如果你需要低延迟、高码率的设置时，你可以使用此设置。<br>
     *        此设置下，弱网抗性较差。
     */
    kRoomProfileTypeCloudGame = 3,
    /**
     * @brief 低时延模式。SDK 会使用低延时设置。  <br>
     *        当你的场景非游戏或云游戏场景，又需要极低延时的体验时，可以使用该模式。 <br>
     *        该模式下，音视频通话延时会明显降低，但同时弱网抗性、通话音质等均会受到一定影响。  <br>
     *        在使用此模式前，强烈建议咨询技术支持同学。
     */
    kRoomProfileTypeLowLatency = 4,
};

/**
 * @type keytype
 * @brief 房间参数配置
 */
struct RTCRoomConfig {
    /**
     * @brief 房间模式，参看 RoomProfileType{@link #RoomProfileType}，默认为普通音视频通话模式，进房后不可更改。
     */
    RoomProfileType room_profile_type = kRoomProfileTypeCommunication;
    /**
     * @brief 是否自动发布音视频流，默认为自动发布。 <br>
     *        若调用 SetUserVisibility{@link #IRtcRoom#SetUserVisibility} 将自身可见性设为 false，无论是默认的自动发布流还是手动设置的自动发布流都不会进行发布，你需要将自身可见性设为 true 后方可发布。
     */
    bool is_auto_publish = true;
    /**
     * @brief 是否自动订阅音频流，默认为自动订阅。  <br>
     *        进房后，你可以调用 SubscribeUserStream{@link #IRtcRoom#SubscribeUserStream} 修改订阅设置。
     */
    bool is_auto_subscribe_audio = true;
    /**
     * @brief 是否自动订阅主视频流，默认为自动订阅。  <br>
     *        进房后，你可以调用 SubscribeUserStream{@link #IRtcRoom#SubscribeUserStream} 修改订阅设置。  <br>
     *        屏幕流始终自动订阅，不受该方法影响。
     */
    bool is_auto_subscribe_video = true;
};
/**
 * @type keytype
 * @brief 多房间参数配置
 */
struct MultiRoomConfig {
    /**
     * @brief 房间模式，参看 RoomProfileType{@link #RoomProfileType}，默认为普通音视频通话模式，进房后不可更改。
     */
    RoomProfileType room_profile_type = kRoomProfileTypeCommunication;
    /**
     * @brief 是否自动订阅音频流，默认为自动订阅
     */
    bool is_auto_subscribe_audio = true;
    /**
     * @brief 是否自动订阅视频流，默认为自动订阅
     */
    bool is_auto_subscribe_video = true;
};

/**
 * @type keytype
 * @brief 当前媒体设备类型
 */
enum MediaDeviceType {
    /**
     * @brief 音频渲染设备类型
     */
    kMediaDeviceTypeAudioRenderDevice = 0,
    /**
     * @brief 音频采集设备类型
     */
    kMediaDeviceTypeAudioCaptureDevice = 1,
    /**
     *@hidden
     *@brief 视频渲染设备类型，该类型暂无使用
     */
    kMediaDeviceTypeVideoRenderDevice = 2,
    /**
     *@brief 视频采集设备类型
     */
    kMediaDeviceTypeVideoCaptureDevice = 3
};

/**
 * @type keytype
 * @brief 媒体设备状态类型
 */
enum MediaDeviceState {
    /**
     *@brief 设备已开启
     */
    kMediaDeviceStateStarted = 1,
    /**
     *@brief 设备已停止
     */
    kMediaDeviceStateStopped = 2,
    /**
     *@brief 设备运行时错误
     */
    kMediaDeviceStateRuntimeError = 3,
    /**
     *@brief 设备已插入
     */
    kMediaDeviceStateAdded = 10,
    /**
     *@brief 设备被移除
     */
    kMediaDeviceStateRemoved = 11
};

/**
 * @type keytype
 * @brief 媒体设备错误类型
 */
enum MediaDeviceError {
    /**
     *@brief 媒体设备正常
     */
    kMediaDeviceErrorOK = 0,
    /**
     *@brief 没有权限启动媒体设备
     */
    kMediaDeviceErrorDeviceNoPermission = 1,
    /**
     *@brief 媒体设备已经在使用中
     */
    kMediaDeviceErrorDeviceBusy = 2,
    /**
     *@brief 媒体设备错误
     */
    kMediaDeviceErrorDeviceFailure = 3,
    /**
     *@brief 未找到指定的媒体设备
     */
    kMediaDeviceErrorDeviceNotFound = 4,
    /**
     *@brief 媒体设备被移除
     */
    kMediaDeviceErrorDeviceDisconnected = 5,
};

/**
 * @type keytype
 * @brief 移动端摄像头。
 */
enum CameraID {
    /**
     *@brief 前置摄像头
     */
    kCameraIDFront = 0,
    /**
     *@brief 后置摄像头
     */
    kCameraIDBack = 1
};

/**
 * @type keytype
 * @brief 音频播放设备类型
 */
enum AudioPlaybackDevice {
    /**
     * @brief 有线耳机
     */
    kAudioPlaybackDeviceHeadset = 1,
    /**
     * @brief 听筒
     */
    kAudioPlaybackDeviceEarpiece = 2,
    /**
     * @brief 扬声器
     */
    kAudioPlaybackDeviceSpeakerphone = 3,
    /**
     * @brief 蓝牙耳机
     */
    kAudioPlaybackDeviceHeadsetBluetooth = 4
};

/**
 * @hidden(macOS,Windows)
 * @type keytype
 * @brief 音频场景类型。<br>
 *        选择音频场景后，RTC 会自动根据客户端音频采集播放设备和采集播放状态，适用通话音量/媒体音量。<br>
 *        你可以调用 SetAudioScenario{@link #SetAudioScenario} 设置音频场景。<br>
 *        如果预设的音频场景类型无法满足你的业务需要，请联系技术支持同学进行定制。
 */
enum AudioScenarioType {
    /**
     * @brief 音乐场景。默认为此场景。<br>
     *        此场景适用于对音乐表现力有要求的场景。如音乐直播等。<br>
     *        音频采集播放设备和采集播放状态，到音量类型的映射如下：<br>
     *        <table>
     *           <tr><th></th><th>仅采集音频，不播放音频</th><th>仅播放音频，不采集音频</th><th>采集并播放音频</th><th>备注</th></tr>
     *           <tr><td>设备自带麦克风和扬声器/听筒</td><td>媒体音量</td><td>媒体音量</td><td>通话音量</td><td>/</td></tr>
     *           <tr><td>有线耳机</td><td>媒体音量</td><td>媒体音量</td><td>媒体音量</td><td>/</td></tr>
     *           <tr><td>蓝牙耳机</td><td>媒体音量</td><td>媒体音量</td><td>媒体音量</td><td>即使蓝牙耳机有麦克风，也只能使用设备自带麦克风进行本地音频采集。</td></tr>
     *        </table>
     */
    kAudioScenarioTypeMusic = 0,
    /**
     * @brief 高质量通话场景。<br>
     *        此场景适用于对音乐表现力有要求的场景。但又希望能够使用蓝牙耳机上自带的麦克风进行音频采集的场景。
     *        此场景可以兼顾外放/使用蓝牙耳机时的音频体验；并尽可能避免使用蓝牙耳机时音量类型切换导致的听感突变。<br>
     *        音频采集播放设备和采集播放状态，到音量类型的映射如下：<br>
     *        <table>
     *           <tr><th></th><th>仅采集音频，不播放音频</th><th>仅播放音频，不采集音频</th><th>采集并播放音频</th> <th>备注</th> </tr>
     *           <tr><td>设备自带麦克风和扬声器/听筒</td><td>媒体音量</td><td>媒体音量</td><td>通话音量</td><td>/</td></tr>
     *           <tr><td>有线耳机</td><td>媒体音量</td><td>媒体音量</td><td>媒体音量</td><td>/</td></tr>
     *           <tr><td>蓝牙耳机</td><td>通话音量</td><td>通话音量</td><td>通话音量</td><td>能够使用蓝牙耳机上自带的麦克风进行音频采集。</td></tr>
     *        </table>
     */
    kAudioScenarioTypeHighQualityCommunication = 1,
    /**
     * @brief 纯通话音量场景。<br>
     *        此场景下，无论客户端音频采集播放设备和采集播放状态，全程使用通话音量。
     *        适用于需要频繁上下麦的通话或会议场景。<br>
     *        此场景可以保持统一的音频模式，不会有音量突变的听感；
     *        最大程度上的消除回声，使通话清晰度达到最优；
     *        使用蓝牙耳机时，能够使用蓝牙耳机上自带的麦克风进行音频采集。<br>
     *        但是，使用媒体音量进行播放的其他音频的音量会被压低，且音质会变差。
     */
    kAudioScenarioTypeCommunication = 2,
    /**
     * @brief 纯媒体场景。一般不建议使用。<br>
     *        此场景下，无论客户端音频采集播放设备和采集播放状态，全程使用媒体音量。
     *        外放通话时，极易出现回声和啸叫。
     */
    kAudioScenarioTypeMedia = 3,
    /**
     * @brief 游戏媒体场景。仅适合游戏场景。  <br>
     *        此场景下，蓝牙耳机时使用通话音量，其它设备使用媒体音量。
     *        外放通话且无游戏音效消除优化时，极易出现回声和啸叫。
     */
    kAudioScenarioTypeGameStreaming = 4,
};

/**
 * @hidden
 * @type keytype
 * @brief 订阅流的结果
 */
enum SubscribeState {
    /**
     * @brief 订阅流成功
     */
    kSubscribeStateSuccess,
    /**
     * @hidden
     */
    kSubscribeStateFailedNotInRoom,
    /**
     * @brief 没有找到流
     */
    kSubscribeStateFailedStreamNotFound,
    /**
     * @brief 超过订阅流上限
     */
    kSubscribeStateFailedOverLimit,
};

/**
 * @type keytype
 * @brief 订阅回退选项
 */
enum SubscribeFallbackOption {
    /**
     * @brief 下行网络较弱时，关闭订阅音视频流时的性能回退功能，默认值
     */
    kSubscribeFallbackOptionDisable = 0,
    /**
     * @brief 下行网络较弱时，只接收视频小流
     */
    kSubscribeFallbackOptionVideoStreamLow = 1,
    /**
     * @brief 下行网络较弱时，先尝试只接收视频小流；如果网络环境无法显示视频，则再回退到只接收远端订阅的音频流
     */
    kSubscribeFallbackOptionAudioOnly = 2,
};

/*
 * @hidden
 * @type keytype
 * @brief 订阅模式选项。业务方在加入房间前，调用 EnableAutoSubscribe{@link #IRtcRoom#EnableAutoSubscribe} 接口设置订阅模式。 <br>
 */
enum SubscribeMode {
    /**
     * @brief 自动订阅模式。SDK 会自动为你订阅房间中的每一路流。  <br>
     */
    kSubscribeModeAuto = 0,
    /**
     * @brief 手动订阅模式。SDK 不会自动订阅房间内的音视频流，你应根据根据需要调用 SubscribeUserStream{@link #IRtcRoom#SubscribeUserStream} 方法手动订阅其他用户发布的音视频流。  <br>
     */
    kSubscribeModeManual = 1
};

/**
 * @type keytype
 * @brief 订阅媒体的类型
 */
enum SubscribeMediaType {
    /**
     * @brief 既不订阅音频，也不订阅视频
     */
    kRTCSubscribeMediaTypeNone = 0,
    /**
     * @brief 只订阅音频，不订阅视频
     */
    kRTCSubscribeMediaTypeAudioOnly,
    /**
     * @brief 只订阅视频，不订阅音频
     */
    kRTCSubscribeMediaTypeVideoOnly,
    /**
     * @brief 同时订阅音频和视频
     */
    kRTCSubscribeMediaTypeVideoAndAudio
};

/**
 * @type keytype
 * @brief 暂停/恢复接收远端的媒体流类型。
 */
enum PauseResumeControlMediaType {
    /**
     * @brief 只控制音频，不影响视频
     */
    kRTCPauseResumeControlMediaTypeAudio = 0,
    /**
     * @brief 只控制视频，不影响音频
     */
    kRTCPauseResumeControlMediaTypeVideo = 1,
    /**
     * @brief 同时控制音频和视频
     */
    kRTCPauseResumeControlMediaTypeVideoAndAudio = 2
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
 * @brief 时域分层定义
 */
enum SVCLayer {
    /**
    * @brief 不指定分层(默认值）
    */
    kSVCLayerDefault = 0,
    /**
     * @brief T0层
     */
    kSVCLayerBase = 1,
    /**
     * @brief T0+T1层
     */
    kSVCLayerMain = 2,
    /**
     * @brief T0+T1+T2层
     */
    kSVCLayerHigh = 3,
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
 * @brief 流切换信息。本地用户订阅的远端流触发回退策略时的流切换信息。
 */
struct RemoteStreamSwitch {
    /**
     * @brief 订阅的音视频流的发布者的用户 ID。
     */
    const char* uid;
    /**
     * @brief 是否是屏幕流。
     */
    bool is_screen;
    /**
     * @brief 流切换前本地用户订阅的视频流的分辨率对应的索引。
     */
    int before_video_index;
    /**
     * @brief 流切换后本地用户订阅的视频流的分辨率对应的索引。
     */
    int after_video_index;
    /**
     * @brief 流切换前是否有视频流。
     */
    bool before_enable;
    /**
     * @brief 流切换后是否有视频流。
     */
    bool after_enable;
    /**
     * @brief 触发流回退的原因，详见类型 FallbackOrRecoverReason{@link #FallbackOrRecoverReason} 。
     */
    FallbackOrRecoverReason reason;
};
/**
 * @type errorcode
 * @brief 登录结果  <br>
 *        调用 Login{@link #IRtcEngineLite#Login} 登录的结果，会通过 OnLoginResult{@link #IRtcEngineLiteEventHandler#OnLoginResult} 回调通知用户。
 */
enum LoginErrorCode {
    /**
     * @brief 调用 Login{@link #IRtcEngineLite#Login} 方法登录成功
     */
    kLoginErrorCodeSuccess = 0,
    /**
     * @brief 调用 Login{@link #IRtcEngineLite#Login} 方法时使用的 Token 无效或过期失效，需要用户重新获取 Token。
     */
    kLoginErrorCodeInvalidToken = -1000,
    /**
     * @brief 登录错误  <br>
     *        调用 Login{@link #IRtcEngineLite#Login} 方法时发生未知错误导致登录失败，需要重新登录。
     */
    kLoginErrorCodeLoginFailed = -1001,
    /**
     * @brief 调用 Login{@link #IRtcEngineLite#Login} 方法时传入的用户 ID 有问题。
     */
    kLoginErrorCodeInvalidUserId = -1002,
    /**
     * @brief 调用 Login{@link #IRtcEngineLite#Login} 登录时服务端出错。
     */
    kLoginErrorCodeServerError = -1003,
};
/**
 * @type keytype
 * @brief 用户在线状态。
 */
enum USER_ONLINE_STATUS {
    /**
     * @brief 对端用户离线  <br>
     *        对端用户已调用 Logout{@link #IRtcEngineLite#Logout}，或者没有调用 Login{@link #IRtcEngineLite#Login} 进行登录。
     */
    kUserOnlineStatusOffline = 0,
    /**
     * @brief 对端用户在线  <br>
     *        对端用户调用 Login{@link #IRtcEngineLite#Login} 登录，并且连接状态正常。
     */
    kUserOnlineStatusOnline = 1,
    /**
     * @brief 无法获取对端用户在线状态  <br>
     *        发生级联错误、对端用户在线状态异常时返回。
     */
    kUserOnlineStatusUnreachable = 2,
};
/**
 * @type errorcode
 * @brief 回调错误码。  <br>
 *        SDK 内部遇到不可恢复的错误时，会通过 OnError{@link #IRtcEngineLiteEventHandler#OnError} 回调通知用户。
 */
enum ErrorCode {
    /**
     * @brief Token 无效。
     *        调用 JoinRoom{@link #JoinRoom} 方法时使用的 Token 无效或过期失效。需要用户重新获取 Token，并调用 UpdateToken{@link #UpdateToken} 方法更新 Token。
     */
    kErrorCodeInvalidToken = -1000,
    /**
     * @brief 加入房间错误。
     *        调用 JoinRoom{@link #JoinRoom} 方法时发生未知错误导致加入房间失败。需要用户重新加入房间。
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
     * @brief 用户被踢出房间：<br>
     *        + 本地用户所在房间中有相同用户 ID 的用户加入房间，导致前者被踢出房间；<br>
     *        + 因调用踢出用户的 OpenAPI，被踢出房间；<br>
     *        + 因调用解散房间的 OpenAPI，离开房间。
     */
    kErrorCodeDuplicateLogin = -1004,

    /*
     * @brief 用户被踢出房间。
     *        本端用户被主动踢出所在房间时，回调此错误。
     */
    kBrerrKickedOut = -1006,


    /**
     * @brief 当调用CreateRtcRoom{@link #IRtcEngineLite#CreateRtcRoom} ，如果roomid 非法，会返回null，并抛出该error
     */
    kRoomErrorCodeRoomIdIllegal = -1007,

    /**
     * @brief 当调用CreateRtcRoom{@link #IRtcEngineLite#CreateRtcRoom} ，如果已经存在了相同的房间，会返回null，并抛出该error
     */
    kRoomErrorCodeUserIsInRoom = -1008,


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
     * @brief 发布视频流总数超过上限。
     *        RTC 系统会限制单个房间内发布的视频流数。如果房间内发布视频流数已达上限时，本地用户再向房间中发布视频流时会失败，同时会收到此错误通知。
     */
    kErrorCodeOverVideoPublishLimit = -1082,
};

/**
 * @type errorcode
 * @brief 回调警告码。
 *        警告码说明 SDK 内部遇到问题正在尝试恢复。警告码仅起通知作用。
 */
enum WarningCode {
    /**
     * @hidden
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
     * @hidden
     * @brief 函数调用顺序错误。
     */
    kWarningCodeInvokeError = -2005,
    /**
     * @hidden
     * @brief 调度异常，服务器返回的媒体服务器地址不可用。
     */
    kWarningCodeInvalidExpectMediaServerAddress = -2007,
    /**
     * @brief 当调用 SetUserVisibility{@link #IRtcRoom#SetUserVisibility} 将自身可见性设置为 false 后，再尝试发布流会触发此警告。  <br>
     */
    kWarningCodePublishStreamForbiden = -2009,
    /**
     * @hidden
     * @brief 自动订阅模式未关闭时，尝试开启手动订阅模式会触发此警告。  <br>
     *        你需在进房前调用 EnableAutoSubscribe{@link #IRtcRoom#EnableAutoSubscribe} 方法关闭自动订阅模式，再调用 SubscribeStream{@link #IRtcRoom#SubscribeStream} 方法手动订阅音视频流。
     */
    kWarningCodeSubscribeStreamForbiden = -2010,
    /**
     * @brief 发送自定义广播消息失败，当前你未在房间中。
     */
    kWarningCodeSendCustomMessage = -2011,
    /**
     * @brief 当房间内人数超过 500 人时，停止向房间内已有用户发送 OnUserJoined{@link #IRTCRoomEventHandler#OnUserJoined} 和 OnUserLeave{@link #IRTCRoomEventHandler#OnUserLeave} 回调，并通过广播提示房间内所有用户。
     */
    kWarningCodeUserNotifyStop = -2013,

    /**
     * @brief 摄像头权限异常，当前应用没有获取摄像头权限。
     */
    kWarningCodeNoCameraPermission = -5001,
    /**
     * @brief 麦克风权限异常，当前应用没有获取麦克风权限。
     */
    kWarningCodeNoMicrophonePermission = -5002,
   /**
     * @brief 音频采集设备启动失败，当前设备可能被其他应用占用。
     */
    kWarningCodeRecodingDeviceStartFailed = -5003,
    /**
     * @brief 音频播放设备启动失败警告，可能由于系统资源不足，或参数错误。
     */
    kWarningCodePlayoutDeviceStartFailed = -5004,
    /**
     * @brief 无可用音频采集设备，请插入可用的音频采集设备。
     */
    kWarningCodeNoRecordingDevice = -5005,
    /**
     * @brief 无可用音频播放设备，请插入可用的音频播放设备。
     */
    kWarningCodeNoPlayoutDevice = -5006,
    /**
     * @brief 当前音频设备没有采集到有效的声音数据，请检查更换音频采集设备。
     */
    kWarningCodeRecordingSilence = -5007,
    /**
     * @brief 媒体设备误操作警告。  <br>
     *        使用自定义采集时，不可调用内部采集开关，调用时将触发此警告。
     */
    kWarningCodeMediaDeviceOperationDenied = -5008,

    /**
     * @brief 不支持在 PublishScreen{@link #PublishScreen} 之后设置屏幕音频采集类型
     *        SetScreenAudioSourceType{@link #SetScreenAudioSourceType}，请在 PublishScreen 之前设置
     */
    kWarningCodeSetScreenAudioSourceTypeFailed = -5009,

    /**
     * @brief 不支持在 PublishScreen{@link #IRtcRoom#PublishScreen} 之后，
     *        通过 SetScreenAudioStreamIndex{@link #IRtcEngineLite#SetScreenAudioStreamIndex} 设置屏幕共享时的音频采集方式。
     */
    kWarningCodeSetScreenAudioStreamIndexFailed = -5010,


    /**
     * @brief 指定的内部渲染画布句柄无效。  <br>
     *        当你调用 SetLocalVideoCanvas{@link #IRtcEngineLite#SetLocalVideoCanvas} 时指定了无效的画布句柄，触发此回调。
     */
    kWarningCodeInvalidCanvasHandle = -6001
};

/**
 * @type keytype
 * @brief 直播推流转码功能错误码。
 *        用户调用 StartLiveTranscoding{@link #StartLiveTranscoding} 方法启动直播推流转码功能后，服务端返回的执行结果。
 */
enum TransCodingError {
    /**
     * @brief 推流成功。
     */
    kTransCodingErrorOK = 0,
    /**
     * @brief 推流参数错误。
     */
    kTransCodingErrorInvalidArgument = 1,
    /**
     * @brief 后处理订阅流失败。
     */
    kTransCodingErrorSubscribe = 2,
    /**
     * @brief 合流服务中间过程存在错误。
     */
    kTransCodingErrorProcessing = 3,
    /**
     * @brief 推 CDN 失败。
     */
    kTransCodingErrorPublish = 4,
};

/**
 * @type keytype
 * @brief 事务检查码。  <br>
 *        用户调用 SetBusinessId{@link #IRtcEngineLite#SetBusinessId} 方法设置业务标识参数的返回错误码。  <br>
 */
enum BusinessCheckCode {
    /**
     * @brief 用户已经在房间中。  <br>
     *        业务标识需要在加入房间之前设置，加入后设置无效。  <br>
     */
    ERROR_ALREADY_IN_ROOM = -6001,

    /**
     * @brief 输入参数非法。  <br>
     *        用户传入的业务标识参数非法，参数合法性参考 SetBusinessId{@link #IRtcEngineLite#SetBusinessId} 方法的参数说明。  <br>
     */
    ERROR_INPUT_INVALIDATE = -6002,
};

/**
 * @type keytype
 * @brief 本地音频流状态。
 *        SDK 通过 OnLocalAudioStateChanged{@link #IRTCRoomEventHandler#OnLocalAudioStateChanged} 回调本地音频流状态
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
     * <br>
     */
    kLocalAudioStreamStateFailed,

    /**
     * @brief 本地音频静音成功后回调该状态。
     *        调用 MuteLocalAudioStream 成功后回调，对应错误码 LocalAudioStreamError{@link #LocalAudioStreamError} 中的 kLocalAudioStreamErrorOk 。  <br>
     */
    kLocalAudioStreamMute,

    /**
     * @brief 本地音频解除静音成功后回调该状态。
     *        调用 MuteLocalAudioStream 成功后回调，对应错误码 LocalAudioStreamError{@link #LocalAudioStreamError} 中的 kLocalAudioStreamErrorOk 。  <br>
     */
    kLocalAudioStreamUnmute
};

/**
 * @type keytype
 * @brief 本地音频流状态改变时的错误码。
 *        SDK 通过 OnLocalAudioStateChanged{@link #IRTCRoomEventHandler#OnLocalAudioStateChanged} 回调该错误码。
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
     * @brief 本地视频采集设备被占用
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
     * @brief 本地视频采集设备被移除
     */
    kLocalVideoStreamErrorDeviceDisconnected
};

/**
 * @type keytype
 * @brief 远端音频流状态。<br>
 *        用户可以通过 OnRemoteAudioStateChanged{@link #IRTCRoomEventHandler#OnRemoteAudioStateChanged} 了解该状态。
 */
enum RemoteAudioState {
    /**
     * @brief  不接收远端音频流。 <br>
     *         以下情况下会触发回调 OnRemoteAudioStateChanged{@link #IRTCRoomEventHandler#OnRemoteAudioStateChanged}：  <br>
     *       + 本地用户停止接收远端音频流，对应原因是：kRemoteAudioStateChangeReasonLocalMuted{@link
     * #RemoteAudioStateChangeReason}  <br>
     *       + 远端用户停止发送音频流，对应原因是：kRemoteAudioStateChangeReasonRemoteMuted{@link
     * #RemoteAudioStateChangeReason}  <br>
     *       + 远端用户离开房间，对应原因是：kRemoteAudioStateChangeReasonRemoteOffline{@link
     * #RemoteAudioStateChangeReason}  <br>
     */
    kRemoteAudioStateStopped = 0,
    /**
     * @brief 开始接收远端音频流首包。<br>
     *        刚收到远端音频流首包会触发回调 OnRemoteAudioStateChanged{@link #IRTCRoomEventHandler#OnRemoteAudioStateChanged}，
     *        对应原因是： kRemoteAudioStateChangeReasonLocalUnmuted{@link #RemoteAudioStateChangeReason}。
     */
    kRemoteAudioStateStarting,
    /**
     * @brief  远端音频流正在解码，正常播放。 <br>
     *         以下情况下会触发回调 OnRemoteAudioStateChanged{@link #IRTCRoomEventHandler#OnRemoteAudioStateChanged}：  <br>
     *       + 成功解码远端音频首帧，对应原因是：kRemoteAudioStateChangeReasonLocalUnmuted{@link
     * #RemoteAudioStateChangeReason}  <br>
     *       + 网络由阻塞恢复正常，对应原因是：kRemoteAudioStateChangeReasonNetworkRecovery{@link
     * #RemoteAudioStateChangeReason}  <br>
     *       + 本地用户恢复接收远端音频流，对应原因是：kRemoteAudioStateChangeReasonLocalUnmuted{@link
     * #RemoteAudioStateChangeReason}  <br>
     *       + 远端用户恢复发送音频流，对应原因是：kRemoteAudioStateChangeReasonRemoteUnmuted{@link
     * #RemoteAudioStateChangeReason}  <br>
     */
    kRemoteAudioStateDecoding,
    /**
     * @brief 远端音频流卡顿。<br>
     *        网络阻塞、丢包率大于 40% 时，会触发回调 OnRemoteAudioStateChanged{@link #IRTCRoomEventHandler#OnRemoteAudioStateChanged}，
     *        对应原因是：kRemoteAudioStateChangeReasonNetworkCongestion{@link #RemoteAudioStateChangeReason}
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
 * @brief 接收远端音频流状态改变的原因。  <br>
 *        用户可以通过 OnRemoteAudioStateChanged{@link #IRTCRoomEventHandler#OnRemoteAudioStateChanged} 了解该原因。
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
 * @brief 远端视频流状态。状态改变时，会收到回调：OnRemoteVideoStateChanged{@link #IRTCRoomEventHandler#OnRemoteVideoStateChanged}
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
     * @brief 远端用户离开频道。
     *        状态转换参考 OnStreamRemove{@link #IRTCRoomEventHandler#OnStreamRemove}
     */
    kRemoteVideoStateChangeReasonRemoteOffline,
};

/**
 * @hidden
 * @type keytype
 * @brief 背景模式
 */
enum BackgroundMode {
    /**
     *@brief 无
     */
    kBackgroundModeNone = 0,
    /**
     *@brief 虚化
     */
    kBackgroundModeBlur = 1,
    /**
     *@brief 背景 1
     */
    kBackgroundModeA = 2,
    /**
     *@brief 背景 2
     */
    kBackgroundModeB = 3,
};

/**
 * @hidden
 * @type keytype
 * @brief 分割模型
 */
enum DivideMode {
    /**
     *@brief 自研
     */
    kDivideModeNone = 0,
    /**
     *@brief effect
     */
    kDivideModeEffect = 1,
};

/**
 * @type keytype
 * @brief 音频流来源的用户 ID 及对应的音量。
 */
struct AudioVolumeInfo {
    /**
     * @brief 音量，取值范围为：[0,255]
     */
    int volume;
    /**
     * @brief 音频流来源的用户 ID
     */
    const char* uid;
};
/**
 * @type keytype
 * @brief OnPerformanceAlarms{@link #IRtcEngineLiteEventHandler#OnPerformanceAlarms} 告警的原因
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
     * @brief 用户 ID，长度在 128 字节以内的非空字符串。支持以下字符集范围:  <br>
     *            1. 26 个大写字母 A ~ Z  <br>
     *            2. 26 个小写字母 a ~ z  <br>
     *            3. 10 个数字 0 ~ 9  <br>
     *            4. 下划线 "_"，at 符 "@"，减 号 "-"
     */
    const char* uid = nullptr;
    /**
     * @brief 用户传递的额外信息，最大长度为 200 字节。会在 onUserJoined{@link #OnUserJoined} 中回调给远端用户。
     */
    const char* extra_info = nullptr;
};

/**
 * @type keytype
 * @brief 通话相关的统计信息
 */
struct RtcRoomStats {
    /**
     * @brief 当前应用的上行丢包率，取值范围为 [0, 1]。
     */
    float txLostrate;
    /**
     * @brief 当前应用的下行丢包率，取值范围为 [0, 1]。
     */
    float rxLostrate;
    /**
     * @brief 客户端到服务端数据传输的往返时延（单位 ms）
     */
    int rtt;
    /**
     * @brief 通话时长，单位为秒，累计值
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
     * @brief 发送码率 (kbps)，获取该数据时的瞬时值
     */
    unsigned short tx_kbitrate;
    /**
     * @brief 接收码率 (kbps)，获取该数据时的瞬时值
     */
    unsigned short rx_kbitrate;
    /**
     * @brief 音频接收码率 (kbps)，获取该数据时的瞬时值
     */
    unsigned short rx_audio_kbitrate;
    /**
     * @brief 音频发送码率 (kbps)，获取该数据时的瞬时值
     */
    unsigned short tx_audio_kbitrate;
    /**
     * @brief 视频接收码率 (kbps)，获取该数据时的瞬时值
     */
    unsigned short rx_video_kbitrate;
    /**
     * @brief 视频发送码率 (kbps)，获取该数据时的瞬时值
     */
    unsigned short tx_video_kbitrate;
    /**
     * @brief 当前房间内的用户人数
     */
    unsigned int user_count;
    /**
     * @hidden
     * @brief 当前应用程序的 CPU 使用率（%），暂未被使用
     */
    double cpu_app_usage;
    /**
     * @hidden
     * @brief 当前系统的 CPU 使用率（%），暂未被使用
     */
    double cpu_total_usage;
};

/**
 * @type keytype
 * @brief 远端音频流统计信息，统计周期为 2s。  <br>
 *        本地用户订阅远端音频流成功后，SDK 会周期性地通过 OnRemoteStreamStats{@link #IRTCRoomEventHandler#OnRemoteStreamStats} 通知本地用户订阅的音频流在此次统计周期内的接收状况。此数据结构即为回调给本地用户的参数类型。  <br>
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
     * @brief 客户端到服务端数据传输的往返时延，单位为 ms。 <br>
     */
    int rtt;
    /**
     * @brief 发送端——服务端——接收端全链路数据传输往返时延。单位为 ms 。  <br>
     */
    int total_rtt;
    /**
     * @brief 远端用户发送的音频流质量。值含义参考 NetworkQuality{@link #NetworkQuality} 。  <br>
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
     * @brief 解码时长。对此次统计周期内接收的远端音频流进行解码的总耗时，单位为 s 。  <br>
     */
    int dec_duration;
    /**
     * @brief 音频下行网络抖动，单位为 ms 。  <br>
     */
    int jitter;
};

/**
 * @type keytype
 * @brief 本地音频流统计信息，统计周期为 2s 。  <br>
 *        本地用户发布音频流成功后，SDK 会周期性地通过 OnLocalStreamStats{@link #IRTCRoomEventHandler#OnLocalStreamStats}
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
     * @notes 此字段用于设置回调的统计周期，默认设置为 2s 。
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
 * @brief 流属性。  <br>
 */
struct MediaStreamInfo {
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
     *        当远端用户调用 SetVideoEncoderConfig{@link #IRtcEngineLite#SetVideoEncoderConfig} 方法发布多个配置的视频流时，此处会包含该用户发布的所有视频流的属性信息。
     *        参看 VideoSolutionDescription{@link #VideoSolutionDescription}。
     */
    VideoSolutionDescription* profiles;
    /**
     * @brief 不同配置流的个数。  <br>
     *        当远端用户调用 SetVideoEncoderConfig{@link #IRtcEngineLite#SetVideoEncoderConfig} 方法发布多个配置的视频流时，此处会包含该用户发布的视频流的数目。
     */
    int profile_count;
};

/**
 * @type keytype
 * @brief 视频订阅配置信息
 */
struct SubscribeVideoConfig {
    /**
     * @brief 订阅的视频流分辨率下标。  <br>
     *        当远端用户通过调用 SetVideoEncoderConfig{@link #IRtcEngineLite#SetVideoEncoderConfig} 方法启动发布多路不同分辨率的视频流时，本地用户需通过此参数指定希望订阅的流。  <br>
     *        默认值为 0，即订阅第一路流。  <br>
     *        如果不想更改之前的设置，可以输入 -1。  <br>
     */
    int video_index = 0;
    /**
     * @brief 远端用户优先级，参看 RemoteUserPriority{@link #RemoteUserPriority}，默认值为 0。
     */
    int priority = 0;
    /**
     * @hidden
     * @brief 构造函数
     */
    SubscribeVideoConfig() : video_index(0), priority(0) {
    }
    /**
     * @hidden
     */
    bool operator==(const SubscribeVideoConfig& config) const {
        bool result = video_index == config.video_index && priority == config.priority;
        ;
        return result;
    }
    /**
     * @hidden
     */
    bool operator!=(const SubscribeVideoConfig& config) const {
        bool result = (*this == config);
        return !result;
    }
};

/**
 * @type keytype
 * @brief 手动订阅流的配置信息。  <br>
 */
struct SubscribeConfig {
    /**
     * @brief 是否是屏幕流（默认为否）。  <br>
     */
    bool is_screen = false;
    /**
     * @brief 是否订阅视频。  <br>
     */
    bool sub_video;
    /**
     * @brief 是否订阅音频。  <br>
     */
    bool sub_audio;
    /**
     * @brief 订阅的视频流分辨率下标。  <br>
     *        用户可以通过调用 SetVideoEncoderConfig{@link #IRtcEngineLite#SetVideoEncoderConfig} 方法在一路流中发布多个不同分辨率的视频。因此订阅流时，需要指定订阅的具体分辨率。此参数即用于指定需订阅的分辨率的下标，默认值为 0 。  <br>
     */
    int video_index;
    /**
     * @brief 远端用户的需求优先级，参看 RemoteUserPriority{@link #RemoteUserPriority}，默认值为 0 。  <br>
     *        当开启了订阅流回退选项功能（详见 SetSubscribeFallbackOption{@link #IRtcEngineLite#SetSubscribeFallbackOption} 方法），弱网或性能不足时会优先保证收到的高优先级用户的流的质量。  <br>
     */
    int priority = 0;

    /**
     * @brief 远端用户的时域分层，参看 SVCLayer{@link #SVCLayer}，默认值为 0 。  <br>
     *        仅码流支持SVC特性时可以生效。  <br>
     */
    int svc_layer = 0;

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
                      video_index == config.video_index && priority == config.priority && svc_layer == config.svc_layer;
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

/**
 * @type keytype
 * @brief 音视频质量反馈问题类型
 */
enum ProblemFeedbackOption {
    /**
     * @brief 没有问题
     */
    kProblemFeedbackOptionNone = 0,
    /**
     * @brief 其他问题
     */
    kProblemFeedbackOptionOtherMessage = (1 << 0),
    /**
     * @brief 声音不清晰
     */
    kProblemFeedbackOptionAudioNotClear = (1 << 1),
    /**
     * @brief 视频不清晰
     */
    kProblemFeedbackOptionVideoNotClear = (1 << 2),
    /**
     * @brief 音视频不同步
     */
    kProblemFeedbackOptionNotSync = (1 << 3),
    /**
     * @brief 音频卡顿
     */
    kProblemFeedbackOptionAudioLagging = (1 << 4),
    /**
     * @brief 视频卡顿
     */
    kProblemFeedbackOptionVideoLagging = (1 << 5),
    /**
     * @brief 连接失败
     */
    kProblemFeedbackOptionDisconnected = (1 << 6),
    /**
     * @brief 无声音
     */
    kProblemFeedbackOptionNoAudio = (1 << 7),
    /**
     * @brief 无画面
     */
    kProblemFeedbackOptionNoVideo = (1 << 8),
    /**
     * @brief 声音过小
     */
    kProblemFeedbackOptionAudioStrength = (1 << 9),
    /**
     * @brief 回声噪音
     */
    kProblemFeedbackOptionEcho = (1 << 10),
    /**
     * @brief 耳返延迟大
     */
    KFeedbackOptionEarBackDelay = (1 << 11),
};

/**
 * @type keytype
 * @brief 远端视频类型
 *      目前C++ sdk 只支持 kVideoStreamTypeHigh 类型
 */
enum VideoStreamType {
    /**
     * @brief 高分辨率视频流
     */
    kVideoStreamTypeHigh = 0,
    /**
     * @brief 低分辨率视频
     */
    kVideoStreamTypeLow = 1,
};

/**
 * @type keytype
 * @brief 画布信息和渲染模式。<br>
 *        你应使用 SetLocalVideoCanvas{@link #IRtcEngineLite#SetLocalVideoCanvas} 将视频流绑定到本地视图。
 */
struct VideoCanvas {
    /**
     * @brief 本地视图句柄
     */
    void* view;
    /**
     * @brief 渲染模式，参看 RenderMode{@link #RenderMode}
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
    VideoCanvas() : view(NULL), render_mode(kRenderModeHidden), uid(0), priv(NULL) {
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
 * @brief 远端音频流统计信息，统计周期为 2s 。  <br>
 *        本地用户订阅远端音频流成功后，SDK 会周期性地通过 OnRemoteStreamStats{@link #IRTCRoomEventHandler#OnRemoteStreamStats}
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
     * @notes 此字段用于设置回调的统计周期，目前设置为 2s 。
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
     * @brief 对应多种分辨率的流的下标，详见 VideoSolutionDescription{@link #VideoSolutionDescription}
     */
    int video_index;
    /**
     * @brief 视频下行网络抖动，单位为 ms 。  <br>
     */
    int jitter;
};

/**
 * @type keytype
 * @brief 本地视频流统计信息，统计周期为 2s 。  <br>
 *        本地用户发布视频流成功后，SDK 会周期性地通过 OnLocalStreamStats{@link #IRTCRoomEventHandler#OnLocalStreamStats}
 *        通知用户发布的视频流在此次统计周期内的发送状况。此数据结构即为回调给用户的参数类型。  <br>
 */
struct LocalVideoStats {
    /**
     * @brief 发送码率。此次统计周期内的视频发送码率，单位为 kbps 。
     */
    int sent_kbitrate;
    /**
     * @brief 采集帧率。此次统计周期内的视频采集帧率，单位为 fps 。
     */
    int input_frame_rate;
    /**
     * @brief 发送帧率。此次统计周期内的视频发送帧率，单位为 fps 。
     */
    int sent_frame_rate;
    /**
     * @brief 编码器输出帧率。当前编码器在此次统计周期内的输出帧率，单位为 fps 。
     */
    int encoder_output_frame_rate;
    /**
     * @brief 本地渲染帧率。此次统计周期内的本地视频渲染帧率，单位为 fps 。
     */
    int renderer_output_frame_rate;
    /**
     * @brief 目标发送码率。此次统计周期内的视频目标发送码率，单位为 kbps 。
     */
    int target_kbitrate;
    /**
     * @brief 目标发送帧率。当前编码器在此次统计周期内的目标发送帧率，单位为 fps 。
     */
    int target_frame_rate;
    /**
     * @brief 统计间隔，单位为 ms 。
     * @notes 此字段用于设置回调的统计周期，默认设置为 2s 。
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
     * @brief 视频编码码率。此次统计周期内的视频编码码率，单位为 kbps 。
     */
    int encoded_bitrate;
    /**
     * @brief 视频编码宽度，单位为 px 。
     */
    int encoded_frame_width;
    /**
     * @brief 视频编码高度，单位为 px 。
     */
    int encoded_frame_height;
    /**
     * @brief 此次统计周期内发送的视频帧总数。
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
};

/**
 * @type keytype
 * @brief 本地音/视频流统计信息以及网络状况，统计周期为 2s 。  <br>
 *        本地用户发布音/视频流成功后，SDK 会周期性地通过 OnLocalStreamStats{@link #IRTCRoomEventHandler#OnLocalStreamStats}
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
     */
    NetworkQuality local_tx_quality;
    /**
     * @brief 所属用户的媒体流下行网络质量，详见 NetworkQuality{@link #NetworkQuality}
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
 *        订阅远端用户发布音/视频流成功后，SDK 会周期性地通过 OnRemoteStreamStats{@link #IRTCRoomEventHandler#OnRemoteStreamStats}
 *        通知本地用户订阅的远端音/视频流在此次统计周期内的接收状况。此数据结构即为回调给本地用户的参数类型。  <br>
 */
struct RemoteStreamStats {
    /**
     * @brief 用户 ID 。音频来源的远端用户 ID 。  <br>
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
     */
    NetworkQuality remote_tx_quality;
    /**
     * @brief 所属用户的媒体流下行网络质量，详见 NetworkQuality{@link #NetworkQuality}
     */
    NetworkQuality remote_rx_quality;
    /**
     * @brief 所属用户的媒体流是否为屏幕流。你可以知道当前统计数据来自主流还是屏幕流。
     */
    bool is_screen;
};

/**
 * @type keytype
 * @brief App 使用的 cpu 和内存信息。  <br>
 *        信息由 SDK 周期性（2s）地通过 OnSysStats{@link #IRtcEngineLiteEventHandler#OnSysStats} 回调通知给用户。
 */
struct SysStats {
    /**
     * @brief 当前系统 CPU 核数
     */
    unsigned int cpu_cores;
    /**
     * @brief 当前应用的 cpu 使用率，取值范围为 [0, 1]。
     */
    double cpu_app_usage;
    /**
     * @brief 当前系统的 cpu 使用率，取值范围为 [0, 1]。
     */
    double cpu_total_usage;
    /**
     * @brief 当前应用的内存使用量（单位 MB）
     */
    double memory_usage;
    /**
     * @brief 全量内存（单位字节）
     */
    unsigned long long full_memory;
    /**
     * @brief 系统已使用内存（单位字节）
     */
    unsigned long long total_memory_usage;
    /**
     * @brief 空闲可分配内存（单位字节）
     */
    unsigned long long free_memory;
    /**
     * @brief 当前应用的内存使用率（单位 %）
     */
    double memory_ratio;
    /**
     * @brief 系统内存使用率（单位 %）
     */
    double total_memory_ratio;
};

/**
 * @type keytype
 * @brief windows 窗口 id, windows 平台下传 windows 窗口句柄
 */
typedef void* view_t;

/**
 * @type keytype
 * @brief 矩形，用于屏幕共享指定区域, 默认值表示抓取整个屏幕
 */
struct Rectangle {
    /**
     * @brief 矩形区域左上角的 x 坐标
     */
    int x = 0;
    /**
     * @brief 矩形区域左上角的 y 坐标
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
 * @brief 屏幕共享时的边框高亮设置
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
     * @brief 边框的宽度，单位：像素
     */
    int border_width = 4;
};

/**
 * @type keytype
 * @brief 抓取屏幕时排除指定窗口，默认不排除任何窗体
 */
struct ScreenFilterConfig {
    /**
     * @brief 抓取屏幕时排除窗口列表。这个参数仅在抓取屏幕时生效。
     */
    view_t* excluded_window_list = nullptr;
    /**
     * @brief 排除窗口的数量。
     */
    int excluded_window_num = 0;
};

/**
 * @type keytype
 * @region 屏幕共享
 * @brief 内部采集屏幕视频流时，是否采集鼠标信息
 */
enum MouseCursorCaptureState {
    /**
     * @brief 采集鼠标信息
     */
    kMouseCursorCaptureStateOn,
    /**
     * @brief 不采集鼠标信息
     */
    kMouseCursorCaptureStateOff,
};

/**
 * @type keytype
 * @brief 屏幕共享时，内部采集参数配置
 */
struct ScreenCaptureParameters {
    /**
     * @brief 采集区域，参看 Rectangle{@link #Rectangle}
     */
    Rectangle region_rect;
    /**
     * @brief 是否采集鼠标状态，参看 MouseCursorCaptureState{@link #MouseCursorCaptureState}
     */
    MouseCursorCaptureState capture_mouse_cursor;
    /**
     * @brief 屏幕过滤设置，参看 ScreenFilterConfig{@link #ScreenFilterConfig}
     */
    ScreenFilterConfig filter_config;
    /**
     * @brief 采集区域的边框高亮设置，参看 HighlightConfig{@link #HighlightConfig}
     */
    HighlightConfig highlight_config;
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
    view_t* excluded_window_list = nullptr;
    /**
     * @brief 抓取屏幕时排除的窗口数量。
     */
    int excluded_window_num = 0;
    /**
     * @brief 高亮边框的配置
     */
    HighlightConfig highlight_config;
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
 * @type api
 * @brief 加密/解密处理函数
 */
class IEncryptHandler {
public:
    /**
     * @hidden
     * @brief 析构函数
     */
    virtual ~IEncryptHandler() {
    }
    /**
     * @type api
     * @region 加密
     * @brief 自定义加密。  <br>
     *        使用设定的自定义加密方式，对传输前的音视频帧数据进行加密。
     * @param data 原始音视频帧数据
     * @param length 原始音视频帧数据的长度
     * @param buf 可供写入的加密后数据缓冲区
     * @param buf_len 可供写入的加密后数据缓冲区大小
     * @return 加密后的数据  <br>
     *        + ≥ 0：加密后实际写入缓冲区的数据大小  <br>
     *        + 0：丢弃该帧  <br>
     * @notes <br>
     *        + 使用此接口进行自定义加密前，你必须先设置自定义加密方式，参看 SetCustomizeEncryptHandler{@link #SetCustomizeEncryptHandler}。
     *        + 使用 OnDecryptData{@link #OnDecryptData} 对已加密的音视频帧数据进行解密。
     *        + 返回的数据大小应控制在原始数据的 90% ~ 120% 范围以内，不然将被丢弃。
     */
    virtual unsigned int OnEncryptData(
            const unsigned char* data, unsigned int length, unsigned char* buf, unsigned int buf_len) = 0;

    /**
     * @type api
     * @region 加密
     * @brief 自定义解密。  <br>
     *        对自定义加密后的音视频帧数据进行解密。关于自定义加密，参看 OnEncryptData{@link #OnEncryptData}。
     * @param data 原始音视频帧数据
     * @param length 原始音视频帧数据的长度
     * @param buf 可供写入的加密后数据缓冲区
     * @param buf_len 可供写入的加密后数据缓冲区大小
     * @return 加密后的数据  <br>
     *        + ≥ 0：加密后实际写入缓冲区的数据大小  <br>
     *        + 0：丢弃该帧  <br>
     * @notes <br>
     *        + 使用此接口进行解密前，你必须先设定解密方式，参看 SetCustomizeEncryptHandler{@link #SetCustomizeEncryptHandler}。
     *        + 返回的数据大小应控制在原始数据的 90% ~ 120% 范围以内，不然将被丢弃。
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
     * @brief 混音已加载
     */
    kAudioMixingStatePreloaded = 0,
    /**
     * @brief 混音正在播放
     */
    kAudioMixingStatePlaying,
    /**
     * @brief 混音暂停
     */
    kAudioMixingStatePaused,
    /**
     * @brief 混音停止
     */
    kAudioMixingStateStopped,
    /**
     * @brief 混音播放失败
     */
    kAudioMixingStateFailed,
    /**
     * @brief 混音播放结束
     */
    kAudioMixingStateFinished
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
     * @brief 预加载失败，找不到混音文件或者文件长度超出 20s
     */
    kAudioMixingErrorPreloadFailed,
    /**
     * @brief 混音开启失败，找不到混音文件或者混音文件打开失败
     */
    kAudioMixingErrorStartFailed,
    /**
     * @brief 混音 ID 异常
     */
    kAudioMixingErrorIdNotFound,
    /**
     * @brief 设置混音文件的播放位置出错
     */
    kAudioMixingErrorSetPositionFailed,
    /**
     * @brief 音量参数不合法，仅支持设置的音量值为[0 400]
     */
    kAudioMixingErrorInValidVolume,
    /**
     * @brief 播放的文件与预加载的文件不一致，请先使用 UnloadAudioMixing{@link #IAudioMixingManager#UnloadAudioMixing} 卸载文件
     */
    kAudioMixingErrorLoadConflict,
    /**
     * @hidden
     * @deprecated
     * @brief 混音错误码，失败，已废弃
     */
    kAudioMixingErrorCanNotOpen = 701,
};

/**
 * @type keytype
 * @brief 自定义视频渲染器
 */
class IVideoSink {
public:
/**
 * @type keytype
 * @brief 视频帧编码格式
 */
enum PixelFormat {
    /**
     * @brief YUV I420 格式
     */
    kI420 = VideoPixelFormat::kVideoPixelFormatI420,
    /**
     * @brief 原始视频帧格式
     */
    kOriginal = VideoPixelFormat::kVideoPixelFormatUnknown,
};
    /**
     * @type callback
     * @brief 视频帧回调
     * @param [out] videoFrame 视频帧结构类，参看 IVideoFrame{@link #IVideoFrame}
     * @return 返回值暂未使用
     */
    virtual bool OnFrame(IVideoFrame* videoFrame) = 0;
    /**
     * @hidden
     * @type callback
     * @region 房间管理
     * @brief 获取外部渲染耗时。
     * @notes 获取外部渲染耗时进行上报。开发者需要自己计算平均渲染耗时。
     */
    virtual int GetRenderElapse() = 0;
    /**
     * @type callback
     * @brief 释放渲染器。
     * @notes 通知开发者渲染器即将被废弃。收到该返回通知后即可释放资源。
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
 * @deprecated from 329.1, use MirrorType instead
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
 * @hidden(Windows)
 * @brief 是否开启耳返功能
 */
enum EarMonitorMode{
    /**
     * @brief 不开启
     */
    kEarMonitorModeOff = 0,
    /**
     * @brief 开启
     */
    kEarMonitorModeOn = 1,
};

/**
 * @type keytype
 * @brief 镜像类型
 */
enum MirrorType {
    /**
     * @brief 本地渲染和编码传输时均无镜像效果
     */
    kMirrorTypeNone = 0,
    /**
     * @brief 本地渲染时有镜像效果，编码传输时无镜像效果
     */
    kMirrorTypeRender = 1,
    /**
     * @brief 本地渲染和编码传输时均有镜像效果
     */
    kMirrorTypeRenderAndEncoder = 3,
};

/**
 * @hidden
 * @type keytype
 * @brief 转推直播包含内容。
 */
enum LiveTranscodingContentControl {
    /**
     * @brief 输出的混流包含音频和视频
     */
    kVideoAndAudio = 0,
    /**
     * @brief 输出的混流只包含音频
     */
    kAudioOnly,
    /**
     * @brief 输出的混流只包含视频
     */
    kVideoOnly,
};

/**
 * @hidden
 * @type keytype
 * @brief 转推直播视频编码器格式。
 */
enum LiveTranscodingVideoCodec {
    /**
     * @brief 使用 H264 编码格式
     */
    kLiveTranscondingH264,
    /**
     * @brief 自定义编码器
     */
    kLiveTranscodingByteVC1,
};
/**
 * @hidden
 * @type keytype
 * @brief 转推直播音频编码格式。
 */
enum LiveTranscodingAudioCodec {
    /**
     * @brief 使用 AAC 编码格式
     */
    kLiveTranscodingAAC,
};
/**
 * @hidden
 * @type keytype
 * @brief AAC 编码等级。
 */
enum LiveTranscodingAudioProfile {
    /**
     * @brief 编码等级 AAC-LC （默认）
     */
    kLiveTranscodingAACLC,
    /**
     * @brief 编码等级 AAC-MAIN
     */
    kLiveTranscodingAACMAIN,
    /**
     * @brief 编码等级 HE-AAC v1
     */
    kLiveTranscodingHEV1,
    /**
     * @brief 编码等级 HE-AAC v2
     */
    KLiveTranscodingHEV2,
};
/**
 * @hidden
 * @type keytype
 * @brief 转推视频配置。
 */
struct LiveTranscodingVideoConfig {
    /**
     * @brief 转推直播视频编码器格式。详见 LiveTranscodingVideoCodec{@link #LiveTranscodingVideoCodec}
     */
    LiveTranscodingVideoCodec codec;
    /**
     * @brief 合流视频帧率信息
     */
    int fps;
    /**
     * @brief 视频 I 帧间隔。
     */
    int gop;
    /**
     * @brief 是否使用低延时特性。取值含义如下:  <br>
     *        + true: 使用低延时特性  <br>
     *        + false: 不使用低延时特性
     */
    bool low_latency;
    /**
     *  @brief 合流视频码率，单位为 bps 。
     */
    int bitrate;
    /**
     * @brief 宽（像素）
     */
    int width;
    /**
     * @brief 高（像素）
     */
    int height;
};
/**
 * @hidden
 * @type keytype
 * @brief 转推音频配置。
 */
struct LiveTranscodingAudioConfig {
    /**
     * @brief 转推直播音频编码器格式。详见 LiveTranscodingAudioCodec{@link #LiveTranscodingAudioCodec}
     */
    LiveTranscodingAudioCodec codec = kLiveTranscodingAAC;
    /**
     * @brief 合流音频码率，单位为 bps 。
     */
    int bitrate;
    /**
     * @brief 音频帧采样率，单位 HZ。目前支持的采样率有：8000HZ， 16000HZ， 32000HZ， 44100HZ，48000HZ。
     */
    int sample_rate;
    /**
     * @brief 声道数，可取 1 或 2。
     */
    int channels;
    /**
     * @brief AAC 编码等级。详见 LiveTranscodingAudioProfile{@link #LiveTranscodingAudioProfile}
     */
    LiveTranscodingAudioProfile aac_profile = kLiveTranscodingAACLC;
};
/**
 * @hidden
 * @type keytype
 * @brief 单个视频流在合流中的布局信息。
 */
struct LiveTranscodingRegion {
    /**
     * @brief 视频流发布用户的用户 ID 。
     */
    const char* uid = nullptr;
    /**
     * @brief 视频流发布用户的房间 ID 。
     */
    const char* roomId = nullptr;
    /**
     * @brief 用户视频布局相对画布左侧的偏移量。相对值，范围为[0.0, 1.0]。
     */
    double x;
    /**
     * @brief 用户视频布局相对画布顶端的偏移量。相对值，范围为[0.0, 1.0]。
     */
    double y;
    /**
     * @brief 用户视频宽度相对用户原始视频宽度的比例。相对值，范围为[0.0, 1.0]。
     */
    double w;
    /**
     * @brief 用户视频高度相对用户原始视频高度的比例。相对值，范围为[0.0, 1.0]。
     */
    double h;
    /**
     * @brief 用户视频布局在画布中的层级。0为底层，值越大越上层，范围为[0, 100]。
     */
    int zorder;
    /**
     * @brief 透明度。范围为 [0.0, 1.0]。
     */
    double alpha;
    /**
     * @brief 转推直播包含内容。详见 LiveTranscodingContentControl{@link #LiveTranscodingContentControl}
     */
    LiveTranscodingContentControl content_control = kVideoAndAudio;
    /**
     * @brief 渲染模式
     */
    RenderMode render_mode = kRenderModeHidden;
};
/**
 * @hidden
 * @type keytype
 * @brief 转推流布局设置。
 */
struct LiveTranscodingLayout {
    /**
     * @brief SEI 信息，长度不得超 4096 bytes
     */
    const char* app_data = nullptr;
    /**
     * @brief 视频的背景颜色。格式为 RGB 定义下的 Hex 值，如 #FFB6C1 表示浅粉色。默认值 #000000，表示为黑色
     */
    const char* background_color = nullptr;
    /**
     * @brief 转推直播布局信息。详见 LiveTranscodingRegion{@link #LiveTranscodingRegion}
     */
    LiveTranscodingRegion* regions = nullptr;
    /**
     * @brief 合流的数量
     */
    int regions_num = 0;
};
/**
 * @hidden
 * @type keytype
 * @brief 转推直播配置信息。
 */
struct LiveTranscodingConfig {
    /**
     * @brief 设置推流地址。
     */
    const char* url = nullptr;
    /**
     * @brief 转推视频配置。详见 LiveTranscodingVideoConfig{@link #LiveTranscodingVideoConfig}
     */
    LiveTranscodingVideoConfig video_config;
    /**
     * @brief 转推音频配置。详见 LiveTranscodingAudioConfig{@link #LiveTranscodingAudioConfig}
     */
    LiveTranscodingAudioConfig audio_config;
    /**
     * @brief 转推流布局设置。详见 LiveTranscodingLayout{@link #LiveTranscodingLayout}
     */
    LiveTranscodingLayout layout;
    /**
     * @hidden
     * @brief 设置动态扩展自定义参数。
     */
    const char* advanced_config = nullptr;
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
 * @brief 流属性
 */
enum StreamIndex {
    /**
     * @brief 主流。包括：<br>
     *        + 通过默认摄像头/麦克风采集到的视频/音频; <br>
     *        + 通过自定义设备采集到的视频/音频。
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
     * @brief 房间 ID
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
 * @brief 音频输入源类型
 */
enum AudioSourceType {
    /**
     *  自定义采集音频源
     */
    kAudioSourceTypeExternal = 0,
    /**
     *  RTC SDK 内部采集音频源
     */
    kAudioSourceTypeInternal ,
};

/**
 * @type keytype
 * @brief 视频输入源类型
 */
enum VideoSourceType {
    /**
     * @brief 自定义采集视频源
     */
    VideoSourceTypeExternal = 0,
    /**
     * @brief SDK 内部采集视频源
     */
    VideoSourceTypeInternal = 1,
    /**
     * @brief 自定义编码视频源。  <br>
     *        你仅需推送分辨率最大的一路编码后视频流，SDK 将自动转码生成多路小流
     */
    VideoSourceTypeEncodedWithAutoSimulcast = 2,
    /**
     * @brief 自定义编码视频源。  <br>
     *        SDK 不会自动生成多路流，你需要自行生成并推送多路流
     */
    VideoSourceTypeEncodedWithoutAutoSimulcast = 3,
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
    VideoRotation rotation = VideoRotation::kVideoRotation0;
};

/**
 * @type keytype
 * @brief 音频采样率，单位为 HZ。 <br>
 */
enum AudioSampleRate {
    /**
     * @brief 自动采样率，适用于从 SDK 获取音频数据，使用 SDK 内部处理的采样率，不经过 resample。  <br>
     *        当你需要从 SDK 获取音频数据时，若对采样率没有强依赖，建议设置成该值，可以通过避免 resample 带来一些性能优化。
     */
    kAudioSampleRateAuto = -1,
    /**
     * @brief 8000 采样率
     */
    kAudioSampleRate8000 = 8000,
    /**
     * @brief 16000 采样率
     */
    kAudioSampleRate16000 = 16000,
    /**
     * @brief 32000 采样率
     */
    kAudioSampleRate32000 = 32000,
    /**
     * @brief 44100 采样率
     */
    kAudioSampleRate44100 = 44100,
    /**
     * @brief 48000 采样率
     */
    kAudioSampleRate48000 = 48000
};

/**
 * @type keytype
 * @brief 音频声道。
 */
enum AudioChannel {
    /**
     * @brief 自动声道，适用于从 SDK 获取音频数据，使用 SDK 内部处理的声道，不经过 resample。  <br>
     *        当你需要从 SDK 获取音频数据时，若对声道没有强依赖，建议设置成该值，可以通过避免 resample 带来一些性能优化。
     */
    kAudioChannelAuto = -1,
    /**
     * @brief 单声道
     */
    kAudioChannelMono = 1,
    /**
     * @brief 双声道
     */
    kAudioChannelStereo = 2
};

/**
 * @type keytype
 * @brief 音频参数格式
 */
struct AudioFormat {
    /**
     * @brief 音频采样率，详见 AudioSampleRate{@link #AudioSampleRate}
     */
    AudioSampleRate sample_rate;
    /**
     * @brief 音频声道，详见 AudioChannel{@link #AudioChannel}
     */
    AudioChannel channel;
};

/**
 * @type keytype
 * @brief HTTP/HTTPS 代理状态
 */
enum HttpProxyState {
    /**
     * @brief HTTP/HTTPS 初始化状态
     */
    kHttpInit,
    /**
     * @brief HTTP/HTTPS 连接成功
     */
    kHttpConnected,
    /**
     * @brief HTTP/HTTPS 连接失败
     */
    kHttpError
};

/**
 * @type keytype
 * @brief SOCKS5 代理连接状态
 */
enum Socks5ProxyState {
    /**
     * @brief SOCKS5 连接初始化
     */
    kSocks5Init,
    /**
     * @brief SOCKS5 连接成功
     */
    kSocks5Connected,
    /**
     * @brief SOCKS5 连接错误
     */
    kSocks5Error,
    /**
     * @brief TCP 连接失败
     */
    kSocks5TcpConnectFail,
    /**
     * @brief TCP 连接关闭
     */
    kSocks5TcpClose,
    /**
     * @brief SOCKS 协议 TCP 协商阶段失败
     */
    kSocks5ProtocolTcpFail,
    /**
     * @brief UDP 连接失败
     */
    kSocks5ProtocolUdpFail,
    /**
     * @brief 授权失败
     */
    kSocks5AuthFail,
    /**
     * @brief 未知状态
     */
    kSocks5Unknown
};

/**
 * @type keytype
 * @brief 语音识别服务鉴权方式，详情请咨询语音识别服务服务相关同学
 */
enum ASRAuthorizationType {
    /**
     * @brief Token 鉴权
     */
    kASRAuthorizationTypeToken = 0,
    /**
     * @brief Signature 鉴权
     */
    kASRAuthorizationTypeSignature = 1,
};

/**
 * @type keytype
 * @brief 使用自动语音识别服务所需校验信息
 */
struct RTCASRConfig {
    /**
     * @brief 应用 ID
     */
    const char* app_id;
    /**
     * @brief 用户 ID
     */
    const char* user_id;
    /**
     * @brief 鉴权方式，参看 ASRAuthorizationType{@link #ASRAuthorizationType}
     */
    ASRAuthorizationType authorization_type;
    /**
     * @brief 访问令牌
     */
    const char* access_token;
    /**
     * @brief 私钥。Signature 鉴权模式下不能为空，token 鉴权模式下为空。参看[关于鉴权](https://bytedance.feishu.cn/docs/doccnMx9153dZEpfLX2I6BkFsMg#uh8x72)
     */
    const char* secret_key;
    /**
     * @brief 场景信息，参看[业务集群](https://bytedance.feishu.cn/docs/doccnMx9153dZEpfLX2I6BkFsMg#aI4WCt)
     */
    const char* cluster;
};

/**
 * @type keytype
 * @brief 语音识别服务错误码。  <br>
 *        除网络原因导致的错误，语音识别服务内部会自行重试之外，其他错误都会停止服务，此时建议再次调用 StartASR{@link #IRtcEngineLite#StartASR} 重启语音识别功能。
 */
enum RTCASRErrorCode {
    /**
     * @brief 网络连接中断，服务不可用，内部会进行重连
     */
    kRTCASRErrorNetworkInterrupted = -1,
    /**
     * @brief 重复调用 StartASR{@link #IRtcEngineLite#StartASR}。开启语音识别服务后，你需要先调用 StopASR{@link #IRtcEngineLite#StopASR} 停止语音识别服务，才能二次调用 StartASR{@link #IRtcEngineLite#StartASR} 再次开启服务。
     */
    kRTCASRErrorAlreadyStarted = -2,
    /**
     * @brief 语音识别服务所需 token 为空
     */
    kRTCASRErrorTokenEmpty = -3,
    /**
     * @brief Signature 鉴权模式下 secret_key 为空
     */
    kRTCErrorSignatureKeyEmpty = -4,
    /**
     * @brief 用户 ID 为空
     */
    kRTCASRErrorUserIdNull = -5,
    /**
     * @brief 应用 ID 为空
     */
    kRTCASRErrorAPPIDNull = -6,
    /**
     * @brief 语音识别服务 cluster 为空
     */
    kRTCASRErrorClusterNull = -7,
    /**
     * @brief 语音识别服务连接失败，该版本没有语音识别功能，请联系 RTC 技术支持。
     */
    kRTCASRErrorOperationDenied = -8
};

/**
 * @type keytype
 * @brief 本地录制的媒体类型
 */
enum RecordingType {
    /**
     * @brief 只录制音频
     */
    kRecordAudioOnly = 0,
    /**
     * @brief 只录制视频
     */
    kRecordVideoOnly = 1,
    /**
     * @brief 同时录制音频和视频
     */
    kRecordVideoAndAudio = 2,
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
     * @brief 录制文件保存成功，调用 StopFileRecording{@link #IRtcEngineLite#StopFileRecording} 结束录制之后才会收到该状态码。
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
     * @brief 录制文件保存的绝对路径。你需要指定一个有读写权限的合法路径。
     */
    const char* dir_path;
    /**
     * @brief 录制存储文件格式，参看 RecordingFileType{@link #RecordingFileType}
     */
    RecordingFileType file_type;
    /**
     * @brief 录制媒体类型，参看 RecordingType{@link #RecordingType}
     */
    RecordingType recording_type;
};

/**
 * @type keytype
 * @brief 混音播放类型
 */
enum AudioMixingType {
    /**
     * @brief 仅本地播放
     */
    kAudioMixingTypePlayout,
    /**
     * @brief 仅远端播放
     */
    kAudioMixingTypePublish,
    /**
     * @brief 本地和远端同时播放
     */
    kAudioMixingTypePlayoutAndPublish
};

/**
 * @type keytype
 * @brief 混音配置
 */
struct AudioMixingConfig {
    /**
     * @brief 混音播放类型，详见 AudioMixingType{@link #AudioMixingType}
     */
    AudioMixingType type;
    /**
     * @brief 混音播放次数，
     * @notes  <br>
     *       + play_count <= 0: 无限循环  <br>
     *       + play_count == 1: 播放一次（默认）  <br>
     *       + play_count > 1: 播放 play_count 次
     */
    int play_count;
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
};

/**
 * @type keytype
 * @brief 视频前处理配置参数。<br>
 */
struct VideoPreprocessorConfig {
    /**
     * @brief 视频帧像素格式，参看 VideoPixelFormat{@link #VideoPixelFormat}
     */
    VideoPixelFormat required_pixel_format = kVideoPixelFormatUnknown;
};

/**
 * @type keytype
 * @brief 自定义编码流信息
 */
struct VideoRateInfo {
    /**
     * @brief 帧率，单位 fps
     */
    int fps;
    /**
     * @brief 码率，单位 kbps
     */
    int bitrate_kbps;
};

/**
 * @type keytype
 * @brief 视频解码方式
 */
enum VideoDecoderConfig {
    /**
     * @brief 开启 SDK 内部解码，只回调解码后的数据
     */
    kVideoDecoderConfigRaw,
    /**
     * @brief 开启自定义解码，只回调解码前数据
     */
    kVideoDecoderConfigEncode,
    /**
     * @brief 开启 SDK 内部解码，同时回调解码前和解码后的数据
     */
    kVideoDecoderConfigBoth,
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
 * @brief 视频采集配置参数。<br>
 */
struct VideoCaptureConfig {

    /**
     * @brief 视频采集分辨率的宽度，单位：px。
     */
    int width = 0;
    /**
     * @brief 视频采集分辨率的高度，单位：px。
     */
    int height = 0;
    /**
     * @brief 视频采集帧率，单位：fps。
    */
    int frameRate = 0;

};

/**
 * @type keytype
 * @brief 音频属性信息提示的相关配置  <br>
 */
struct AudioPropertiesConfig {
    /**
     * @brief 信息提示间隔；
     * @notes  <br>
     *       + <= 0: 关闭信息提示  <br>
     *       + >0 && <=100: 不合法的 interval 值，SDK 自动设置为 100ms  <br>
     *       + > 100: 信息提示间隔为 interval 实际值
     */
    int interval;
};

/**
 * @type keytype
 * @brief 音频属性信息  <br>
 */
struct AudioPropertiesInfo {
    /**
     * @brief 音量，取值范围为：[0, 255]
     */
    int volume;
};

/**
 * @type keytype
 * @brief 远端音频属性信息
 */
struct RemoteAudioPropertiesInfo {
    /**
     * @type keytype
     * @brief 远端流信息，详见 RemoteStreamKey{@link #RemoteStreamKey}
     */
    RemoteStreamKey stream_key;
    /**
     * @type keytype
     * @brief 音频属性信息，详见 AudioPropertiesInfo{@link #AudioPropertiesInfo}
     */
    AudioPropertiesInfo audio_properties_info;
};

/**
 * @type keytype
 * @brief 本地音频属性信息
 */
struct LocalAudioPropertiesInfo {
    /**
     * @brief 流属性，主流或屏幕流。参看 StreamIndex{@link #StreamIndex}
     */
    StreamIndex stream_index;
    /**
     * @type keytype
     * @brief 音频属性信息，详见 AudioPropertiesInfo{@link #AudioPropertiesInfo}
     */
    AudioPropertiesInfo audio_properties_info;
};

/**
 * @type keytype
 * @brief 音质档位
 */
enum AudioProfileType {
    /**
     * @brief 默认音质
     */
    kAudioProfileTypeDefault = 0,
    /**
     * @brief 流畅音质。  <br>
     *        流畅优先、低延迟、低功耗、低流量消耗，适用于大部分游戏场景，如 MMORPG、MOBA、FPS等游戏中的小队语音、组队语音、国战语音等。
     */
    kAudioProfileTypeFluent = 1,
    /**
     * @brief 标准音质。  <br>
     *        适用于对音质有一定要求的场景，同时延时、功耗和流量消耗相对适中，适合 Sirius 等狼人杀类游戏。
     */
    kAudioProfileTypeStandard = 2,
    /**
     * @brief 高清音质  <br>
     *        超高音质，同时延时、功耗和流量消耗相对较大，适用于连麦 PK、在线教育等场景。 <br>
     *        游戏场景不建议使用。
     */
    kAudioProfileTypeHD = 3,
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

}  // namespace bytertc

#endif  // BYTE_RTC_DEFINES_H__
