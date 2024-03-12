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
 * @locale zh
 * @type keytype
 * @brief 方法调用结果。
 */
/**
 * @locale en
 * @type keytype
 * @brief API call result.
 */
enum ReturnStatus {
    /**
     * @locale zh
     * @brief 成功。
     */
    /**
     * @locale en
     * @brief Success.
     */
    kReturnStatusSuccess = 0,
    /**
     * @locale zh
     * @brief 失败。
     */
    /**
     * @locale en
     * @brief Failure.
     */
    kReturnStatusFailure = -1,
    /**
     * @locale zh
     * @brief 参数错误。
     */
    /**
     * @locale en
     * @brief Invalid parameter.
     */
    kReturnStatusParameterErr = -2,
    /**
     * @locale zh
     * @brief 接口状态错误。
     */
    /**
     * @locale en
     * @brief API status error.
     */
    kReturnStatusWrongState = -3,
    /**
     * @locale zh
     * @brief 失败，用户已在房间内。
     */
    /**
     * @locale en
     * @brief Failure. The user is already in the room.
     */
    kReturnStatusHasInRoom = -4,
    /**
     * @locale zh
     * @brief 失败，用户已登录。
     */
    /**
     * @locale en
     * @brief Failure. The user has already logged in.
     */
    kReturnStatusHasInLogin = -5,
    /**
     * @locale zh
     * @brief 失败，用户已经在进行通话回路测试中。
     */
    /**
     * @locale en
     * @brief Failure. The user is already in a pre-call test.
     */
    kReturnStatusHasInEchoTest = -6,
    /**
     * @locale zh
     * @brief 失败，音视频均未采集。
     */
    /**
     * @locale en
     * @brief Failure. Neither video nor audio is captured.
     */
    kReturnStatusNeitherVideoNorAudio = -7,
    /**
     * @locale zh
     * @brief 失败，该 roomId 已被使用。
     */
    /**
     * @locale en
     * @brief Failure. The roomId is already in use.
     */
    kReturnStatusRoomIdInUse = -8,
    /**
     * @locale zh
     * @brief 失败，屏幕流不支持。
     */
    /**
     * @locale en
     * @brief Failure. Screen stream is not supported.
     */
    kReturnStatusScreenNotSupport = -9,
    /**
     * @locale zh
     * @brief 失败，不支持该操作。
     */
    /**
     * @locale en
     * @brief Failure. Not supported.
     */
    kReturnStatusNotSupport = -10,
    /**
     * @locale zh
     * @brief 失败，资源已占用。
     */
    /**
     * @locale en
     * @brief Failure. resource overflow.
     */
    kReturnStatusResourceOverflow = -11,
    /**
     * @locale zh
     * @brief 失败，不支持视频接口调用。
     */
    /**
     * @locale en
     * @brief Failure. Not supported.
     */
    kReturnStatusVideoNotSupport = -12,
    /**
     * @locale zh
     * @brief 失败，没有音频帧。
     */
    /**
     * @locale en
     * @brief Failure. No audio frame.
     */
    kReturnStatusAudioNoFrame = -101,
    /**
     * @locale zh
     * @brief 失败，未实现。
     */
    /**
     * @locale en
     * @brief Failure. No implemented.
     */
    kReturnStatusAudioNotImplemented = -102,
    /**
     * @locale zh
     * @brief 失败，采集设备无麦克风权限，尝试初始化设备失败。
     */
    /**
     * @locale en
     * @brief Failure. The audio capture device does not have microphone use permission, and the initialization of the device failed.
     */
    kReturnStatusAudioNoPermission = -103,
    /**
     * @locale zh
     * @brief 失败，设备不存在。当前没有设备或设备被移除时返回该值。
     */
    /**
     * @locale en
     * @brief Failure. The device does not exist. This value is returned if there is currently no device or if the device has been removed.
     */
    kReturnStatusAudioDeviceNotExists = -104,
    /**
     * @locale zh
     * @brief 失败，设备音频格式不支持。
     */
    /**
     * @locale en
     * @brief Failure. The device audio format is not supported.
     */
    kReturnStatusAudioDeviceFormatNotSupport = -105,
    /**
     * @locale zh
     * @brief 失败，系统无可用设备。
     */
    /**
     * @locale en
     * @brief Failure. No device in system.
     */
    kReturnStatusAudioDeviceNoDevice = -106,
    /**
     * @locale zh
     * @brief 失败，当前设备不可用，需更换设备。
     */
    /**
     * @locale en
     * @brief Failure. The current device is not available and need to be replaced.
     */
    kReturnStatusAudioDeviceCannotUse = -107,
    /**
     * @locale zh
     * @brief 系统错误，设备初始化失败。
     */
    /**
     * @locale en
     * @brief Device initialization failed due to a system error.
     */
    kReturnStatusAudioDeviceInitFailed = -108,
    /**
     * @locale zh
     * @brief 系统错误，设备开启失败。
     */
    /**
     * @locale en
     * @brief Device start-up failed due to a system error.
     */
    kReturnStatusAudioDeviceStartFailed = -109,
    /**
     * @locale zh
     * @brief 失败，无效对象。
     */
    /**
     * @locale en
     * @brief Failure. invalid object.
     */
    kReturnStatusNativeInvalid = -201,
    /**
     * @locale zh
     * @brief 警告。推送视频帧到 RTC SDK 时，相邻视频帧的时间戳差异应当和推帧操作的间隔相同。如果不同，会收到此警告。
     */
    /**
     * @locale en
     * @brief Warning. When pushing a video frame to the RTC SDK, the timing difference of subsequent video frames should be the same as the interval of the frame push operation. If not, you will receive this warning.
     */
    kReturnStatusVideoTimeStampWarning = -202,
};

/**
 * @locale zh
 * @type keytype
 * @brief 房间内远端流被移除的原因。  
 */
/**
 * @locale en
 * @type keytype
 * @brief The reason why the remote flow in the room was removed.   
 */
enum StreamRemoveReason {
    /**
     * @locale zh
     * @brief 远端用户停止发布流。  
     */
    /**
     * @locale en
     * @brief The remote user stops publishing the flow.   
     */
    kStreamRemoveReasonUnpublish = 0,
    /**
     * @locale zh
     * @brief 远端用户发布流失败。  
     */
    /**
     * @locale en
     * @brief The remote user failed to publish the flow.   
     */
    kStreamRemoveReasonPublishFailed = 1,
    /**
     * @locale zh
     * @brief 媒体服务器 10s 没收到客户端的媒体数据。
     */
    /**
     * @locale en
     * @brief Media server failed to receive media data from the client for 10 seconds.
     */
    kStreamRemoveReasonKeepLiveFailed = 2,
    /**
     * @locale zh
     * @brief 远端用户断网。  
     */
    /**
     * @locale en
     * @brief The remote user is disconnected.   
     */
    kStreamRemoveReasonClientDisconnected = 3,
    /**
     * @locale zh
     * @brief 远端用户重新发布流。  
     */
    /**
     * @locale en
     * @brief The remote user republishes the flow.   
     */
    kStreamRemoveReasonRepublish = 4,
    /**
     * @locale zh
     * @brief 其他原因。  
     */
    /**
     * @locale en
     * @brief Other reasons.   
     */
    kStreamRemoveReasonOther = 5,
    /**
     * @locale zh
     * @brief 远端用户 Token 发布权限过期。
     */
    /**
     * @locale en
     * @brief The remote user's publishing privilege of the Token is expired.
     */
    kStreamRemoveReasonPrivilegeTokenExpired = 6,
};

/**
 * @locale zh
 * @hidden
 * @deprecated since 3.45 and will be deleted in 3.51.
 * @type keytype
 * @brief 用户角色。  
 */
/**
 * @locale en
 * @hidden
 * @deprecated since 3.45 and will be deleted in 3.51.
 * @type keytype
 * @brief User role.   
 */
enum UserRoleType {
    /**
     * @locale zh
     * @brief 主播角色。该角色用户可在房间内发布和订阅音视频流，房间中的其他用户可以感知到该用户的存在。  
     */
    /**
     * @locale en
     * @brief Live streaming host role. This role user can publish and subscribe to audio & video streams in the room, and other users in the room can perceive the presence of this user.   
     */
    kUserRoleTypeBroadcaster = 1,
    /**
     * @locale zh
     * @brief 隐身用户角色。此角色用户只可在房间内订阅音视频流，房间中的其他用户无法感知到该用户的存在。  
     */
    /**
     * @locale en
     * @brief Stealth user persona. This role user can only subscribe to audio & video streams in the room, and other users in the room cannot perceive the presence of this user.   
     */
    kUserRoleTypeSilentAudience = 2,
};

/**
 * @locale zh
 * @type keytype
 * @brief 用户可见性状态改变错误码。
 */
/**
 * @locale en
 * @type keytype
 * @brief User visibility state change error.
 */
enum UserVisibilityChangeError {
    /**
     * @locale zh
     * @brief 成功。
     */
    /**
     * @locale en
     * @brief Success.
     */
    kUserVisibilityChangeErrorOk = 0,
    /**
     * @locale zh
     * @brief 未知错误。
     */
    /**
     * @locale en
     * @brief Unknown error.
     */
    kUserVisibilityChangeErrorUnknown = 1,
    /**
     * @locale zh
     * @brief 房间内可见用户达到上限。
     */
    /**
     * @locale en
     * @brief Visible users in the room have reached the upper limit.
     */
    kUserVisibilityChangeErrorTooManyVisibleUser = 2,
};

/**
 * @locale zh
 * @type keytype
 * @brief 数据消息来源
 */
/**
 * @locale en
 * @hidden currently not available
 * @type keytype
 * @brief Message source
 */
enum DataMessageSourceType {
    /**
     * @locale zh
     * @brief 通过客户端或服务端的插入的自定义消息。
     */
    /**
     * @locale en
     * @brief Customized messages inserted by calling API in the server or SDK.
     */
    kDataMessageSourceTypeDefault = 0,
    /**
     * @locale zh
     * @brief 系统数据，包含音量指示信息。
     */
    /**
     * @locale en
     * @brief System notification such as volume indication.
     */
    kDataMessageSourceTypeSystem,
};

/**
 * @locale zh
 * @type keytype
 * @brief SEI 发送模式。
 */
/**
 * @locale en
 * @type keytype
 * @brief SEI sending mode.
 */
enum SEICountPerFrame {
    /**
     * @locale zh
     * @brief 单发模式。即在 1 帧间隔内多次发送 SEI 数据时，多个 SEI 按队列逐帧发送。
     */
    /**
     * @locale en
     * @brief Single-SEI mode. When you send multiple SEI messages in 1 frame, they will be sent frame by frame in a queue.
     */
    kSEICountPerFrameSingle = 0,
    /**
     * @locale zh
     * @brief 多发模式。即在 1 帧间隔内多次发送 SEI 数据时，多个 SEI 随下个视频帧同时发送。
     */
    /**
     * @locale en
     * @brief Multi-SEI mode. When you send multiple SEI messages in 1 frame, they will be sent together in the next frame.
     */
    kSEICountPerFrameMulti,
};

/**
 * @locale zh
 * @type keytype
 * @brief 上行/下行网络质量
 */
/**
 * @locale en
 * @type keytype
 * @brief Tx/Rx network quality
 */
struct NetworkQualityStats {
    /**
     * @locale zh
     * @brief 用户 ID
     */
    /**
     * @locale en
     * @brief User ID
     */
    const char* uid;
    /**
     * @locale zh
     * @brief 本端的上行/下行的丢包率，范围 [0.0,1.0]<br>
     *        当 `uid` 为本地用户时，代表发布流的上行丢包率。<br>
     *        当 `uid` 为远端用户时，代表接收所有订阅流的下行丢包率。
     */
    /**
     * @locale en
     * @brief Packet loss ratio of the local client, ranging [0.0,1.0]<br>
     *        For a local user, it is the sent-packet loss ratio.<br>
     *        For a remote user, it is the loss ratio of all the packets received.
     */
    double fraction_lost;
    /**
     * @locale zh
     * @brief 当 `uid` 为本地用户时有效，客户端到服务端的往返延时（RTT），单位：ms
     */
    /**
     * @locale en
     * @brief Round-trip time (RTT) from client to server. Effective for the local user. Unit: ms
     */
    int rtt;
    /**
     * @locale zh
     * @brief 本端的音视频 RTP 包 2 秒内的平均传输速率，单位：bps<br>
     *        当 `uid` 为本地用户时，代表发送速率。<br>
     *        当 `uid` 为远端用户时，代表所有订阅流的接收速率。
     */
    /**
     * @locale en
     * @brief Average transmission rate of the media RTP packages in 2s. unit: bps<br>
     *        For a local user, it is the packet-transmitting speed.<br>
     *        For a more user, it is the speed of receiving all the subscribed media.
     */
    int total_bandwidth;
    /**
     * @locale zh
     * @brief 上行网络质量评分，详见 NetworkQuality{@link #NetworkQuality}。
     */
    /**
     * @locale en
     * @brief Tx network quality grade. Refer to NetworkQuality{@link #NetworkQuality} for details.
     */
    NetworkQuality tx_quality;
    /**
     * @locale zh
     * @brief 下行网络质量评分，详见 NetworkQuality{@link #NetworkQuality}。
     */
    /**
     * @locale en
     * @brief Rx network quality grade. Refer to NetworkQuality{@link #NetworkQuality} for details.
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
 * @locale zh
 * @type keytype
 * @brief 房间模式<br>
 *        根据所需场景，选择合适的房间模式，应用不同的音视频算法、视频参数和网络配置 <br>
 *        调用 `setAudioProfile` 改变音频参数配置
 */
/**
 * @locale en
 * @type keytype
 * @brief  Room profile<br>
 *        Choose an appropriate room-profile option to meet the requirement of the scenario for media encoding algorithm, video profiles, and network configurations.<br>
 *        Call `setAudioProfile` to apply another audio quality option.
 */
enum RoomProfileType : int {
    /**
     * @locale zh
     * @brief 默认场景，通用模式<br>
     *        与 `kRoomProfileTypeMeeting = 16` 配置相同。<br>
     *        你可以联系技术支持更换默认配置参数。
     */
    /**
     * @locale en
     * @brief General mode by default <br>
     *        It equals to `kRoomProfileTypeMeeting = 16`.<br>
     *        Contact us to alter the default settings.
     */
    kRoomProfileTypeCommunication = 0,
    /**
     * @locale zh
     * @deprecated since 3.42 and will be deleted in 3.51, use kRoomProfileTypeInteractivePodcast instead.
     * @brief 直播模式。<br>
     *        当你对音视频通话的音质和画质要求较高时，应使用此设置。<br>
     *        此设置下，当用户使用蓝牙耳机收听时，蓝牙耳机使用媒体模式。
     */
    /**
     * @locale en
     * @deprecated since 3.45 and will be deleted in 3.51, use kRoomProfileTypeInteractivePodcast instead.
     * @brief Live broadcasting mode. <br>
     *        Use this mode for high quality of the media. <br>
     *        In this mode, audio plays in media mode for Bluetooth earphones.
     */
    kRoomProfileTypeLiveBroadcasting = 1,
    /**
     * @locale zh
     * @brief 游戏语音模式，低功耗、低流量消耗。<br>
     *        低端机在此模式下运行时，进行了额外的性能优化：<br>
     *            + 部分低端机型配置编码帧长 40/60 <br>
     *            + 部分低端机型关闭软件 3A 音频处理 <br>
     *        增强对 iOS 其他屏幕录制进行的兼容性，避免音频录制被 RTC 打断。
     */
    /**
     * @locale en
     * @brief Game voice mode. Low consumption of computing resources and network data<br>
     *        Additional performance optimizations have been made for low-end devices: <br>
     *             + Encodes frame length 40/60 for some low-end models. <br>
     *             + Disables software 3A audio processing for some low-end models.<br>
     *        Enhance iOS Compatibility with other screen recordings to avoid audio recordings being interrupted by RTC.
     */
    kRoomProfileTypeGame = 2,
    /**
     * @locale zh
     * @brief 云游戏模式。<br>
     *        如果你的游戏场景需要低延迟的配置，使用此设置。<br>
     *        此设置下，弱网抗性较差。
     */
    /**
     * @locale en
     * @brief Cloud game mode. <br>
     *        Use this mode for game App requiring low latency. <br>
     *        During poor network connection, communication experiences get worse with this mode.
     */
    kRoomProfileTypeCloudGame = 3,
    /**
     * @locale zh
     * @brief 云渲染模式。超低延时配置。  <br>
     *        如果你的应用并非游戏但又对延时要求较高时，选用此模式 <br>
     *        该模式下，音视频通话延时会明显降低，但同时弱网抗性、通话音质等均会受到一定影响。  
     */
    /**
     * @locale en
     * @brief Cloud render mode featuring extra-low latency. <br>
     *        Choose this mode if it is not a game App yet requires low latency. <br>
     *        In this mode, latency will significantly decrease at the cost of lower audio quality as well as the bad performance with weak network signal.
     */
    kRoomProfileTypeLowLatency = 4,
    /**
     * @locale zh
     * @brief 适用于 1 vs 1 音视频通话
     */
    /**
     * @locale en
     * @brief For 1 vs 1 video and audio calls
     */
    kRoomProfileTypeChat = 5,
    /**
     * @locale zh
     * @brief 适用于 3 人及以上纯语音通话。<br>
     *        通话中，闭麦时为是媒体模式，上麦后切换为通话模式。
     */
    /**
     * @locale en
     * @brief For video and audio chat rooms of 3 or more people
     */
    kRoomProfileTypeChatRoom = 6,
    /**
     * @locale zh
     * @brief 实现多端同步播放音视频，适用于 “一起看” 或 “一起听” 场景。<br>
     *        该场景中，使用 RTC 信令同步播放进度，共享的音频内容不通过 RTC 进行传输。
     */
    /**
     * @locale en
     * @brief For scenarios such as "Watch together." and "Listen together." Multiple clients are capable of playing the same videos and audios synchronically.<br>
     *        In these scenarios, RTC does not involve the transportation of the sharing media but only synchronizes video/music playback across multiple clients via signaling.
     */
    kRoomProfileTypeLwTogether = 7,
    /**
     * @locale zh
     * @brief 适用于对音质要求较高的游戏场景，优化音频 3A 策略，只通过媒体模式播放音频
     */
    /**
     * @locale en
     * @brief For the game apps demanding high-resolution audio. In this mode, RTC plays audio using the media mode only.
     */
    kRoomProfileTypeGameHD = 8,
    /**
     * @locale zh
     * @brief 适用于直播中主播之间连麦的业务场景。<br>
     *        直播时通过 CDN，发起连麦 PK 时使用 RTC。
     */
    /**
     * @locale en
     * @brief For the events of co-hosting in the live-streaming<br>
     *        During a livestreaming using a CDN network, the host can invite another host to join the co-hosting event using RTC.
     */
    kRoomProfileTypeCoHost = 9,
    /**
     * @locale zh
     * @brief 适用于单主播和观众进行音视频互动的直播。通话模式，上下麦不会有模式切换，避免音量突变现象
     */
    /**
     * @locale en
     * @brief For interactive podcasts that the host can have video and audio interactions with the audience. The voice mode is set to communication mode to avoid volume spiking and dipping acutely.
     */
    kRoomProfileTypeInteractivePodcast = 10,
    /**
     * @locale zh
     * @brief 线上 KTV 场景，音乐音质，低延迟<br>
     *        使用 RTC 传输伴奏音乐，混音后的歌声，适合独唱或单通合唱
     */
    /**
     * @locale en
     * @brief For the online karaoke with high-quality audio and low latency<br>
     *        In these scenarios, RTC transports the accompaniment and mixed audio, such as solo and non-realtime chorus.
     */
    kRoomProfileTypeKTV = 11,
    /**
     * @locale zh
     * @brief 适合在线实时合唱场景，高音质，超低延迟。使用本配置前请联系技术支持进行协助完成其他配置。
     */
    /**
     * @locale en
     * @brief For the online-chorusing scenarios requiring high-quality audio and low latency. Contact our technical specialists before you apply it to your App.
     */
    kRoomProfileTypeChorus = 12,
    /**
     * @locale zh
     * @valid since 3.45
     * @brief 适用于 VR 场景。支持最高 192 KHz 音频采样率，可开启球形立体声。
     */
    /**
     * @locale en
     * @valid since 3.45
     * @brief For VR chat with support for 192 KHz audio sample rate and feature of 360 Reality AudioAudio
     */
    kRoomProfileTypeVRChat = 13,
    /**
     * @locale zh
     * @brief 适用于 1 vs 1 游戏串流，支持公网或局域网。
     */
    /**
     * @locale en
     * @brief For scenarios of streaming live videos to only one client on the LAN. It can be applied to devices on the Internet or LAN.
     */
    kRoomProfileTypeGameStreaming = 14,
    /**
     * @locale zh
     * @brief 适用于局域网的 1 对多视频直播，最高支持 8K， 60 帧/秒， 100 Mbps 码率<br>
     *        需要在局域网配置私有化部署媒体服务器。
     */
    /**
     * @locale en
     * @brief For scenarios of streaming live videos to multiple clients within the LAN with the support of 60fps @8K video stream with the bitrate of 100 Mbps<br>
     * A private media server is expected to be ready on the LAN.
     */
    kRoomProfileTypeLanLiveStreaming = 15,
    /**
     * @locale zh
     * @brief 适用于云端会议中的个人设备
     */
    /**
     * @locale en
     * @brief For meeting Apps installed on personal devices
     */
    kRoomProfileTypeMeeting = 16,
    /**
     * @locale zh
     * @brief 适用于云端会议中的会议室终端设备，例如 Rooms，投屏盒子等。
     */
    /**
     * @locale en
     * @brief For meeting Apps installed on terminals of meeting rooms, such as Rooms.
     */
    kRoomProfileTypeMeetingRoom = 17,
    /**
     * @locale zh
     * @brief 适用于课堂互动，房间内所有成员都可以进行音视频互动<br>
     *        当你的场景中需要同时互动的成员超过 10人时使用此模式
     */
    /**
     * @locale en
     * @brief For the online classrooms and lectures that over 10 participants in the room are allowed to join the video chat.
     */
    kRoomProfileTypeClassroom = 18,
};
/**
 * @locale zh
 * @type keytype
 * @brief 多房间参数配置
 */
/**
 * @locale en
 * @type keytype
 * @brief  Multi-room parameter configuration
 */
struct AudioRoomConfig {
    /**
     * @locale zh
     * @brief 房间模式，参看 RoomProfileType{@link #RoomProfileType}，默认为 `kRoomProfileTypeCommunication`，进房后不可更改。
     */
    /**
     * @locale en
     * @brief Room profile. See RoomProfileType{@link #RoomProfileType}. The default is `kRoomProfileTypeCommunication`. The setting cannot be changed after joining the room.
     */
    RoomProfileType room_profile_type = kRoomProfileTypeCommunication;
    /**
     * @locale zh
     * @brief 是否自动订阅音频流，默认为自动订阅。
     */
    /**
     * @locale en
     * @brief Whether to automatically subscribe to the audio stream. The default is automatic subscription.
     */
    bool is_auto_subscribe_audio = true;
    /**
     * @locale zh
     * @brief 是否自动发布音视频流，默认为自动发布。 <br>
     *        若调用 `setUserVisibility` 将自身可见性设为 false，无论是默认的自动发布流还是手动设置的自动发布流都不会进行发布，你需要将自身可见性设为 true 后方可发布。  <br>
     *        多房间场景下，若已在其中一个房间成功设置了自动发布，其他房间的自动发布设置均不会生效。若每个房间均不做设置，则默认在第一个加入的房间内自动发布流。
     */
    /**
     * @locale en
     * @brief Whether to publish media streams automatically. The default is automatic publishing.  <br>
     *        If you call `setUserVisibility` to set your own visibility to false, you will not publish media streams regardless of the value of `is_auto_publish`.  <br>
     *        In multi-room scenario, if you have already set automatic publishing in one room, you will not be able to automatically publishing streams in the other rooms. If no settings are made in each room, the stream is automatically published in the first room joined by default.
     */
    bool is_auto_publish_audio = true;
};

/**
 * @locale zh
 * @type keytype
 * @brief 媒体设备类型
 */
/**
 * @locale en
 * @type keytype
 * @brief Type of media device
 */
enum MediaDeviceType {
    /**
     * @locale zh
     * @brief 未知设备
     */
    /**
     * @locale en
     * @brief Unknown device
     */
    kMediaDeviceTypeAudioUnknown = -1,
    /**
     * @locale zh
     * @brief 音频渲染设备
     */
    /**
     * @locale en
     * @brief Speaker or headphone
     */
    kMediaDeviceTypeAudioRenderDevice = 0,
    /**
     * @locale zh
     * @brief 音频采集设备
     */
    /**
     * @locale en
     * @brief Microphone
     */
    kMediaDeviceTypeAudioCaptureDevice = 1,
    /**
     * @locale zh
     * @hidden currently not available
     *@brief 视频渲染设备类型，该类型暂无使用
     */
    /**
     * @locale en
     * @hidden currently not available
     *@brief Video rendering device type, this type is not used yet
     */
    kMediaDeviceTypeVideoRenderDevice = 2,
    /**
     * @locale zh
     *@brief 视频采集设备
     */
    /**
     * @locale en
     *@brief Video capture device
     */
    kMediaDeviceTypeVideoCaptureDevice = 3,
    /**
     * @locale zh
     *@brief 屏幕流视频设备
     */
    /**
     * @locale en
     * @brief Screen capture device
     */
    kMediaDeviceTypeScreenVideoCaptureDevice = 4,
    /**
     * @locale zh
     * @brief 屏幕流音频设备
     */
    /**
     * @locale en
     * @brief Screen audio capture device
     */
    kMediaDeviceTypeScreenAudioCaptureDevice = 5,
};

/**
 * @locale zh
 * @type keytype
 * @brief 媒体设备状态。
 */
/**
 * @locale en
 * @type keytype
 * @brief  Media device state.
 */
enum MediaDeviceState {
    /**
     * @locale zh
     * @brief 设备已开启
     */
    /**
     * @locale en
     * @brief On
     */
    kMediaDeviceStateStarted = 1,
    /**
     * @locale zh
     * @brief 设备已停止
     */
    /**
     * @locale en
     * @brief Off
     */
    kMediaDeviceStateStopped = 2,
    /**
     * @locale zh
     * @brief 设备运行时错误<br>
     *       例如，当媒体设备的预期行为是正常采集，但没有收到采集数据时，将回调该状态。
     */
    /**
     * @locale en
     * @brief Runtime error<br>
     *        For example, when the media device is expected to be working but no data is received.
     */
    kMediaDeviceStateRuntimeError = 3,
    /**
     * @locale zh
     * @brief 设备已暂停。包括：<br>
     *        + 采集过程中，目标应用窗体最小化到任务栏。<br>
     *        + 开启采集或采集过程中，目标应用窗体被隐藏。<br>
     *        + 采集过程中，目标应用窗体正在被拉伸。<br>
     *        + 采集过程中，目标应用窗体正在被拖动。
     */
    /**
     * @locale en
     * @brief Device paused. Including: <br>
     *         + During screen capturing, the target application window is minimized in the taskbar. <br>
     *         + Before or during screen capturing, the target application window is hidden. <br>
     *         + During screen capturing, the target application window is being stretched. <br>
     *         + During screen capturing, the target application window is being dragged. 
     */
    kMediaDeviceStatePaused = 4,
    /**
     * @locale zh
     * @brief 设备已恢复
     */
    /**
     * @locale en
     * @brief Device resumed
     */
    kMediaDeviceStateResumed = 5,
    /**
     * @locale zh
     * @brief 设备已插入<br>
     * 你可以调用获取设备接口更新设备列表。
     */
    /**
     * @locale en
     * @brief Added<br>
     * Call enumerate-device api to update the device list when you get this notification.
     */
    kMediaDeviceStateAdded = 10,
    /**
     * @locale zh
     * @brief 设备被移除<br>
     * 你可以调用获取设备接口更新设备列表。
     */
    /**
     * @locale en
     * @brief Removed<br>
     * Call enumerate-device api to update the device list when you get this notification.
     */
    kMediaDeviceStateRemoved = 11,
    /**
     * @locale zh
     * @brief 用户合盖打断了视频通话。如果系统未休眠或关机，将在开盖后自动恢复视频通话。
     */
    /**
     * @locale en
     * @brief Closing the laptop interrupted the RTC call. RTC call will resume once the laptop is opened.
     */
    kMediaDeviceStateInterruptionBegan = 12,
    /**
     * @locale zh
     * @brief 视频通话已从合盖打断中恢复
     */
    /**
     * @locale en
     * @brief RTC call resumed from the interruption caused by Closing the laptop.
     */
    kMediaDeviceStateInterruptionEnded = 13,
    /**
     * @locale zh
     * @brief 设备成为系统默认
     */
    /**
     * @locale en
     * @brief The device just became the default device.
     */
    kMediaDeviceStateBecomeSystemDefault = 14,
    /**
     * @locale zh
     * @brief 设备不再是系统默认
     */
    /**
     * @locale en
     * @brief The device is no longer the default device.
     */
    kMediaDeviceStateResignSystemDefault = 15,

    /**
     * @locale zh
     * @brief 获取设备列表超时后，收到设备列表通知。<br>
     * 再次调用获取设备接口更新设备列表。
     */
    /**
     * @locale en
     * @brief Notification of receiving the device list after time-out. <br>
     * Call enumerate-device api to update the device list when you get this notification.
     */
    kMediaDeviceStateListUpdated = 16,
};

/**
 * @locale zh
 * @type keytype
 * @brief 媒体设备错误类型
 */
/**
 * @locale en
 * @type keytype
 * @brief Media device error type
 */
enum MediaDeviceError {
    /**
     * @locale zh
     * @brief 媒体设备正常
     */
    /**
     * @locale en
     * @brief Media equipment is normal
     */
    kMediaDeviceErrorOK = 0,
    /**
     * @locale zh
     * @brief 没有权限启动媒体设备
     */
    /**
     * @locale en
     * @brief No permission to start media device
     */
    kMediaDeviceErrorDeviceNoPermission = 1,
    /**
     * @locale zh
     * @brief 媒体设备已经在使用中
     */
    /**
     * @locale en
     * @brief Media devices are already in use
     */
    kMediaDeviceErrorDeviceBusy = 2,
    /**
     * @locale zh
     * @brief 媒体设备错误
     */
    /**
     * @locale en
     * @brief Media device error
     */
    kMediaDeviceErrorDeviceFailure = 3,
    /**
     * @locale zh
     * @brief 未找到指定的媒体设备
     */
    /**
     * @locale en
     * @brief The specified media device was not found.
     */
    kMediaDeviceErrorDeviceNotFound = 4,
    /**
     * @locale zh
     * @brief 媒体设备被移除。<br>
     *        对象为采集屏幕流时，表明窗体被关闭或显示器被移除。
     */
    /**
     * @locale en
     * @brief Media device, window or monitor removed.
     */
    kMediaDeviceErrorDeviceDisconnected = 5,
    /**
     * @locale zh
     * @brief 设备没有数据回调
     */
    /**
     * @locale en
     * @brief Device has no data callback.
     */
    kMediaDeviceErrorDeviceNoCallback = 6,
    /**
     * @locale zh
     * @brief 设备采样率不支持
     */
    /**
     * @locale en
     * @brief Device sample rate not supported.
     */
    kMediaDeviceErrorDeviceUNSupportFormat = 7,
    /**
     * @locale zh
     * @hidden(Android,macOS,Windows,Linux)
     * @brief ios 屏幕采集没有 group id 参数
     */
    /**
     * @locale en
     * @hidden(Android,Windows,Linux)
     * @brief ios screen capture not find group id parameter
     */
    kMediaDeviceErrorDeviceNotFindGroupId = 8,
    /**
     * @locale zh
     * @hidden(Android,Windows,Linux)
     * @brief 打断类型：使用camera过程中被送到后台
     */
    /**
     * @locale en
     * @hidden(Android,Windows,Linux)
     * @brief An interruption caused by the app being sent to the background while using a camera.
     */
    kMediaDeviceErrorDeviceNotAvailableInBackground = 9,
    /**
     * @locale zh
     * @hidden(Android,Windows,Linux)
     * @brief 打断类型：被其他客户端打断，比如一个正在使用capture session的app
     */
    /**
     * @locale en
     * @hidden(Android,Windows,Linux)
     * @brief An interruption caused by the video device temporarily being made unavailable (for example, when used by another capture session).
     */
    kMediaDeviceErrorDeviceVideoInUseByAnotherClient = 10,
    /**
     * @locale zh
     * @hidden(Android,Windows,Linux)
     * @brief 打断类型：使用Slide Over,、Split View 或者 PIP时被中断，比如台前调度，画中画
     */
    /**
     * @locale en
     * @hidden(Android,Windows,Linux)
     * @brief An interruption caused when your app is running in Slide Over, Split View, or Picture in Picture mode on iPad.
     */
    kMediaDeviceErrorDeviceNotAvailableWithMultipleForegroundApps = 11,
    /**
     * @locale zh
     * @hidden(Android,Windows,Linux)
     * @brief 打断类型：系统压力，比如过热
     */
    /**
     * @locale en
     * @hidden(Android,Windows,Linux)
     * @brief An interruption due to system pressure, such as thermal duress.
     */
    kMediaDeviceErrorDeviceNotAvailableDueToSystemPressure = 12,
};

/**
 * @locale zh
 * @type keytype
 * @brief 媒体设备警告
 */
/**
 * @locale en
 * @type keytype
 * @brief Media device warning
 */
enum MediaDeviceWarning {
    /**
     * @locale zh
     * @brief 无警告
     */
    /**
     * @locale en
     * @brief No warning
     */
    kMediaDeviceWarningOK = 0,
    /**
     * @locale zh
     * @brief 非法设备操作。在使用外部设备时，调用了 SDK 内部设备 API。
     */
    /**
     * @locale en
     * @brief Illegal device operation. Calls the API for internal device when using the external device.
     */
    kMediaDeviceWarningOperationDenied = 1,
    /**
     * @locale zh
     * @brief 采集静音。
     */
    /**
     * @locale en
     * @brief No audio is captured.
     */
    kMediaDeviceWarningCaptureSilence = 2,
    /**
     * @locale zh
     * @hidden(iOS,macOS,Windows,Linux)
     * @brief Android 特有的静音，系统层面的静音上报
     */
    /**
     * @locale en
     * @hidden(iOS,macOS,Windows,Linux)
     * @brief Silence warning by Android system.
     */
    kMediaDeviceWarningAndroidSysSilence = 3,
    /**
     * @locale zh
     * @hidden(iOS,macOS,Windows,Linux)
     * @brief Android 特有的静音消失
     */
    /**
     * @locale en
     * @hidden(iOS,macOS,Windows,Linux)
     * @brief Silence disappearing warning by Android system.
     */
    kMediaDeviceWarningAndroidSysSilenceDisappear = 4,
    // The following warning codes are only valid for meeting scenarios.
    /**
     * @locale zh
     * @hidden for internal use only
     * @brief 音量过大，超过设备采集范围。建议降低麦克风音量或者降低声源音量。
     */
    /**
     * @locale en
     * @hidden for internal use only
     * @brief The volume is too loud and exceeds the acquisition range of the device. Lower the microphone volume or<br>
     * lower the volume of the audio source.
     */
    kMediaDeviceWarningDetectClipping = 10,
    /**
     * @locale zh
     * @brief 通话中出现回声现象。<br>
     *        当 RoomProfileType{@link #RoomProfileType} 为 `kRoomProfileTypeMeeting` 和<br>
     * `kRoomProfileTypeMeetingRoom`，且 AEC 关闭时，SDK 自动启动回声检测，如果检测到回声问题，将通过<br>
     * `onAudioDeviceWarning` 返回本枚举值。
     */
    /**
     * @locale en
     * @brief Echos between mics and speakers are detected during a call.<br>
     *        `onAudioDeviceWarning` notifies you with this enum of echo issue. During a call, SDK will detect echo<br>
     * issue only when RoomProfileType{@link #RoomProfileType} is set to `kRoomProfileTypeMeeting` or<br>
     * `kRoomProfileTypeMeetingRoom` and AEC is disabled.
     */
    kMediaDeviceWarningDetectLeakEcho = 11,
    /**
     * @locale zh
     * @hidden for internal use only
     * @brief 低信噪比
     */
    /**
     * @locale en
     * @hidden for internal use only
     * @brief Low SNR.
     */
    kMediaDeviceWarningDetectLowSNR = 12,
    /**
     * @locale zh
     * @hidden for internal use only
     * @brief 采集插零现象
     */
    /**
     * @locale en
     * @hidden for internal use only
     * @brief Silence inserted during capture.
     */
    kMediaDeviceWarningDetectInsertSilence = 13,
    /**
     * @locale zh
     * @hidden for internal use only
     * @brief 设备采集静音（算法层）
     */
    /**
     * @locale en
     * @hidden for internal use only
     * @brief Silence during capture.
     */
    kMediaDeviceWarningCaptureDetectSilence = 14,
    /**
     * @locale zh
     * @hidden for internal use only
     * @brief 设备采集静音消失
     */
    /**
     * @locale en
     * @hidden for internal use only
     * @brief Silence disappears during capture.
     */
    kMediaDeviceWarningCaptureDetectSilenceDisappear = 15,
    /**
     * @locale zh
     * @hidden(Linux)
     * @brief 啸叫。<br>
     *        触发该回调的情况如下：1）不支持啸叫抑制的房间模式下，检测到啸叫；2）支持啸叫抑制的房间模式下，检测到未被抑制的啸叫。仅 kRoomProfileTypeCommunication、kRoomProfileTypeMeeting、kRoomProfileTypeMeetingRoom 三种房间模式支持啸叫抑制。 建议提醒用户检查客户端的距离或将麦克风和扬声器调至静音。
     */
    /**
     * @locale en
     * @hidden(Linux)
     * @brief Howling detected.<br>
     *        You will receive this callback in the following scenarios: 1) Howling is detected under the room profiles that do not support howling suppression; 2) Detect howling that is not suppressed under the room profiles that support howling suppression. You can only enable howling suppression by calling joinRoom{@link #IRTCRoom#joinRoom}to set your room profile as kRoomProfileTypeCommunication, kRoomProfileTypeMeeting, and kRoomProfileTypeMeetingRoom. We recommend that you remind your users to adjust the physical distance between two devices or disable all unused devices except the connecting one.
     */
    kMediaDeviceWarningCaptureDetectHowling = 16,

    /**
     * @hidden for internal use only
     * @brief sudden impluse noise detected
     */
    kMediaDeviceWarningSuddenImpluseDetected = 17,

    /**
     * @hidden for internal use only
     * @brief sudden impluse noise detected
     */
    kMediaDeviceWarningSquareWavSoundDetected = 18,

    /**
     * @locale zh
     * @hidden(Windows,macOS,Linux)
     * @brief setAudioRoute结果回调, 该scenario下不支持设置
     */
    /**
     * @locale en
     * @hidden(Windows,macOS,Linux)
     * @brief result of api setAudioRoute callback, not support called to setAudioRoute in this scenario
     */
    kMediaDeviceWarningSetAudioRouteInvalidScenario = 20,
    /**
     * @locale zh
     * @hidden(Windows,macOS,Linux)
     * @brief setAudioRoute结果回调, routing device 不存在 (Android)
     */
    /**
     * @locale en
     * @hidden(Windows,macOS,Linux)
     * @brief result of api setAudioRoute callback, routing device not exists (Andorid)
     */
    kMediaDeviceWarningSetAudioRouteNotExists = 21,
    /**
     * @locale zh
     * @hidden(Windows,macOS,Linux)
     * @brief setAudioRoute结果回调, 系统高优先级路由占用 (IOS)
     */
    /**
     * @locale en
     * @hidden(Windows,macOS,Linux)
     * @brief result of api setAudioRoute callback, failed by higher priority
     */
    kMediaDeviceWarningSetAudioRouteFailedByPriority = 22,
    /**
     * @locale zh
     * @hidden(Windows,macOS,Linux)
     * @brief 当前非通话模式 kAudioScenarioTypeCommunication，不支持设置音频路由
     */
    /**
     * @locale en
     * @hidden(Windows,macOS,Linux)
     * @brief Setting audio route failed because the audio route can only be changed in kAudioScenarioTypeCommunication<br>
     * mode.
     */
    kMediaDeviceWarningSetAudioRouteNotVoipMode = 23,
    /**
     * @locale zh
     * @hidden(Windows,macOS,Linux)
     * @brief setAudioRoute结果回调, 设备没有启动
     */
    /**
     * @locale en
     * @hidden(Windows,macOS,Linux)
     * @brief result of api setAudioRoute callback, no any play or capture started
     */
    kMediaDeviceWarningSetAudioRouteDeviceNotStart = 24,
    /**
     * @locale zh
     * @hidden(macOS,Windows,Linux,Android)
     * @brief setBluetoothMode结果回调, 当前场景不会立即生效
     */
    /**
     * @locale en
     * @hidden(macOS,Windows,Linux,Android)
     * @brief Result of calling `setBluetoothMode`. The setting will not take effect immediately in the current<br>
     * scenario.
     */
    kMediaDeviceWarningSetBluetoothModeScenarioUnsupport = 25,
    /**
     * @locale zh
     * @hidden(macOS,Windows,Linux,Android)
     * @brief setBluetoothMode 结果回调, 当前不支持设置蓝牙模式
     */
    /**
     * @locale en
     * @hidden(macOS,Windows,Linux,Android)
     * @brief Result of calling `setBluetoothMode`. The setting request is denied.
     */
    kMediaDeviceWarningSetBluetoothModeUnsupport = 26,
    /**
     * @locale zh
     * @hidden currently not available
     * @brief 使用无声的采集设备
     */
    /**
     * @locale en
     * @hidden currently not available
     * @brief use silent record device
     */
    kMediaDeviceWarningRecordingUseSilentDevice = 27,
    /**
     * @locale zh
     * @hidden(Linux)
     * @brief 使用无声的播放设备
     */
    /**
     * @locale en
     * @hidden(Linux)
     * @brief use silent playout device
     */
    kMediaDeviceWarningPlayoutUseSilentDevice = 28,
};

/**
 * @locale zh
 * @type keytype
 * @brief 订阅媒体流状态
 */
/**
 * @locale en
 * @type keytype
 * @brief Subscription status of media streams
 */
enum SubscribeState {
    /**
     * @locale zh
     * @brief 订阅/取消订阅流成功
     */
    /**
     * @locale en
     * @brief Successfully changed the subscription status
     */
    kSubscribeStateSuccess,
    /**
     * @locale zh
     * @brief 订阅/取消订阅流失败，本地用户未在房间中
     */
    /**
     * @locale en
     * @brief Failed to change the subscription status, because you were not in the room.
     */
    kSubscribeStateFailedNotInRoom,
    /**
     * @locale zh
     * @brief 订阅/取消订阅流失败，房间内未找到指定的音视频流
     */
    /**
     * @locale en
     * @brief Failed to change the subscription status, because the target audio/video stream was not found.
     */
    kSubscribeStateFailedStreamNotFound,
    /**
     * @locale zh
     * @brief 超过订阅流数上限
     */
    /**
     * @locale en
     * @brief Failed to change the subscription status, because the number of streams you have subscribed to has exceeded the limit.
     */
    kSubscribeStateFailedOverLimit,
};

/**
 * @locale zh
 * @hidden
 * @deprecated since 3.26 and will be deleted in 3.51, use RoomConfig in joinRoom{@link #IRTCRoom#joinRoom} instead.
 * @type keytype
 * @brief 订阅模式选项。
 */
/**
 * @locale en
 * @hidden
 * @deprecated since 3.45 and will be deleted in 3.51, use RoomConfig in joinRoom{@link #IRTCRoom#joinRoom} instead.
 * @type keytype
 * @brief Subscription mode option.
 */
enum SubscribeMode {
    /**
     * @locale zh
     * @brief 自动订阅模式。SDK 会自动为你订阅房间中的每一路流。  
     */
    /**
     * @locale en
     * @brief Automatic subscription mode. The SDK  automatically subscribes to every stream in the room for you. 
     */
    kSubscribeModeAuto = 0,
    /**
     * @locale zh
     * @brief 手动订阅模式。SDK 不会自动订阅房间内的音视频流，你应根据根据需要调用 subscribeUserStream{@link #IRTCRoom#subscribeUserStream} 方法手动订阅其他用户发布的音视频流。  
     */
    /**
     * @locale en
     * @brief Manual subscription mode. The SDK  does not automatically subscribe to audio & video streams in the room. You should call the subscribeUserStream{@link #IRTCRoom#subscribeUserStream} method to manually subscribe to audio & video streams published by other users as needed. 
     */
    kSubscribeModeManual = 1
};

/**
 * @locale zh
 * @type keytype
 * @brief 远端用户优先级，在性能不足需要回退时，会优先回退优先级低的用户的音视频流
 */
/**
 * @locale en
 * @type keytype
 * @brief Priority of the publisher. When a user encounters performance insufficiency of either the network or the device, the media stream  will fall back in the ascending order of `RemoteUserPriority`.
 */
enum RemoteUserPriority {
    /**
     * @locale zh
     * @brief 用户优先级为低（默认值）
     */
    /**
     * @locale en
     * @brief Low, the default
     */
    kRemoteUserPriorityLow = 0,
    /**
     * @locale zh
     * @brief 用户优先级为正常
     */
    /**
     * @locale en
     * @brief Medium
     */
    kRemoteUserPriorityMedium = 100,
    /**
     * @locale zh
     * @brief 用户优先级为高
     */
    /**
     * @locale en
     * @brief High
     */
    kRemoteUserPriorityHigh = 200,
};
/**
 * @locale zh
 * @type keytype
 * @brief 发布端音视频流回退选项
 */
/**
 * @locale en
 * @type keytype
 * @brief Stream fallback options of publisher
 */
enum PublishFallbackOption {
    /**
     * @locale zh
     * @brief 上行网络不佳或设备性能不足时，不对音视频流作回退处理。默认设置。
     */
    /**
     * @locale en
     * @brief Default setting. No fallback is allowed under limited network conditions.
     */
    kPublishFallbackOptionDisabled = 0,
    /**
     * @locale zh
     * @brief 上行网络不佳或设备性能不足时，发布的视频流会从大流到小流依次降级，直到与当前网络性能匹配，具体降级规则参看[性能回退](https://www.volcengine.com/docs/6348/70137)文档。
     */
    /**
     * @locale en
     * @brief Under limited network conditions, the video streams that you published will degrade sequentially from the highest-quality stream to the lowest-quality stream until it can match current network conditions.
     */
    kPublishFallbackOptionSimulcast = 1,
};
/**
 * @locale zh
 * @type keytype
 * @brief 订阅端音视频流回退选项。
 */
/**
 * @locale en
 * @type keytype
 * @brief Stream fallback options of subscriber
 */
enum SubscribeFallbackOption {
    /**
     * @locale zh
     * @brief 下行网络不佳或设备性能不足时，不对音视频流作回退处理。默认设置。
     */
    /**
     * @locale en
     * @brief Default setting. No fallback is allowed under limited network conditions.
     */
    kSubscribeFallbackOptionDisable = 0,
    /**
     * @locale zh
     * @brief 下行网络不佳或设备性能不足时，对视频流做降级处理，具体降级规则参看[音视频流回退](70137)。 <br>
     *        该设置仅对发布端调用 enableSimulcastMode{@link #IRTCVideo#enableSimulcastMode} 开启发送多路流功能的情况生效。
     */
    /**
     * @locale en
     * @brief The resolution of currently subscribed video stream will be reduced under limited network conditions, see [Stream Fallback](70137) for details.  <br>
     *        You can only select this setting after the stream publisher calls enableSimulcastMode{@link #IRTCVideo#enableSimulcastMode} to enable the mode of publishing multiple streams, otherwise no fallback will occur.
     */
    kSubscribeFallbackOptionVideoStreamLow = 1,
    /**
     * @locale zh
     * @brief 下行网络不佳或设备性能不足时，先对视频流做回退处理。当网络状况不满足接收弱流时，则自动取消接收视频，仅接收音频。<br>
     *        该设置仅对发布端调用 enableSimulcastMode{@link #IRTCVideo#enableSimulcastMode} 开启发送多路流功能的情况生效。
     */
    /**
     * @locale en
     * @brief The resolution of currently subscribed video stream will be reduced first under limited network conditions. When the network condition is not sufficient to receive the minimum resolution stream, the video is automatically cancelled and only the audio is received. <br>
     *        You can only select this setting after the stream publisher calls enableSimulcastMode{@link #IRTCVideo#enableSimulcastMode} to enable the mode of publishing multiple streams, otherwise no fallback will occur.
     */
    kSubscribeFallbackOptionAudioOnly = 2,
};

/**
 * @locale zh
 * @type keytype
 * @brief 远端订阅流发生回退或恢复的原因
 */
/**
 * @locale en
 * @type keytype
 * @brief Reason of the Fallback or reverting from a Fallback of the subscribed stream or the publishing stream
 */
enum FallbackOrRecoverReason {
    /**
     * @locale zh
     * @brief 其他原因，非带宽和性能原因引起的回退或恢复。默认值
     */
    /**
     * @locale en
     * @brief The default: Fallback due to an unknown reason that is neither infufficienclt bandwidth of the network nor poor-performance of the device
     */
    kFallbackOrRecoverReasonUnknown = -1,
    /**
     * @locale zh
     * @brief 由带宽不足导致的订阅端音视频流回退。
     */
    /**
     * @locale en
     * @brief Fallback of the subscribed stream due to insufficient bandwidth of the network
     */
    kFallbackOrRecoverReasonSubscribeFallbackByBandwidth = 0,
    /**
     * @locale zh
     * @brief 由性能不足导致的订阅端音视频流回退。
     */
    /**
     * @locale en
     * @brief Fallback of the subscribed stream for poor-performance of the device
     */
    kFallbackOrRecoverReasonSubscribeFallbackByPerformance = 1,
    /**
     * @locale zh
     * @brief 由带宽恢复导致的订阅端音视频流恢复。
     */
    /**
     * @locale en
     * @brief Reverting from a Fallback of the subscribed stream due to the recovery of the network bandwidth
     */
    kFallbackOrRecoverReasonSubscribeRecoverByBandwidth = 2,
    /**
     * @locale zh
     * @brief 由性能恢复导致的订阅端音视频流恢复。
     */
    /**
     * @locale en
     * @brief Reverting from a Fallback of the subscribed stream due to the amelioration of the device performance
     */
    kFallbackOrRecoverReasonSubscribeRecoverByPerformance = 3,
    /**
     * @locale zh
     * @brief 由带宽不足导致的发布端音视频流回退。
     */
    /**
     * @locale en
     * @brief Fallback of the publishing stream due to Insufficient bandwidth of the network
     */
    kFallbackOrRecoverReasonPublishFallbackByBandwidth = 4,
    /**
     * @locale zh
     * @brief 由性能不足导致的发布端音视频流回退。
     */
    /**
     * @locale en
     * @brief Fallback of the publishing stream due to poor-performance of the device
     */
    kFallbackOrRecoverReasonPublishFallbackByPerformance = 5,
    /**
     * @locale zh
     * @brief 由带宽恢复导致的发布端音视频流恢复。
     */
    /**
     * @locale en
     * @brief Reverting from a Fallback of the publishing stream due to the recovery of the network bandwidth
     */
    kFallbackOrRecoverReasonPublishRecoverByBandwidth = 6,
    /**
     * @locale zh
     * @brief 由性能恢复导致的发布端音视频流恢复。
     */
    /**
     * @locale en
     * @brief Reverting from a Fallback of the publishing stream due to the amelioration of the device performance
     */
    kFallbackOrRecoverReasonPublishRecoverByPerformance = 7,
};

/**
 * @locale zh
 * @type keytype
 * @brief 性能相关告警的原因
 */
/**
 * @locale en
 * @type keytype
 * @brief Reasons of performance-related alarms
 */
enum PerformanceAlarmReason {
    /**
     * @locale zh
     * @brief 网络原因差，造成了发送性能回退。仅在开启发送性能回退时，会收到此原因。
     */
    /**
     * @locale en
     * @brief The poor network causes the transmission performance to fall back. This reason is only received when sending performance fallback is turned on.
     */
    kPerformanceAlarmReasonBandwidthFallbacked = 0,
    /**
     * @locale zh
     * @brief 网络性能恢复，发送性能回退恢复。仅在开启发送性能回退时，会收到此原因。
     */
    /**
     * @locale en
     * @brief Network performance recovery, transmission performance rollback recovery. This reason is only received when sending performance fallback is turned on.
     */
    kPerformanceAlarmReasonBandwidthResumed = 1,
    /**
     * @locale zh
     * @brief 如果未开启发送性能回退，收到此告警时，意味着性能不足；<br>
     *        如果开启了发送性能回退，收到此告警时，意味着性能不足，且已发生发送性能回退。
     */
    /**
     * @locale en
     * @brief If the send performance fallback is not turned on, when receiving this alarm, it means that the performance is insufficient; <br>
     *        If the send performance fallback is turned on, when receiving this alarm, it means that the performance is insufficient and the send performance fallback has occurred.
     */
    kPerformanceAlarmReasonPerformanceFallbacked = 2,
    /**
     * @locale zh
     * @brief 如果未开启发送性能回退，收到此告警时，意味着性能不足已恢复；<br>
     *        如果开启了发送性能回退，收到此告警时，意味着性能不足已恢复，且已发生发送性能回退恢复。
     */
    /**
     * @locale en
     * @brief If the send performance fallback is not turned on, when receiving this alarm, it means that the performance shortage has been restored; <br>
     *         If the send performance fallback is turned on, when receiving this alarm, it means that the performance shortage has been restored and the send performance fallback has occurred. Recovery.
     */
    kPerformanceAlarmReasonPerformanceResumed = 3,
};

/**
 * @locale zh
 * @type keytype
 * @brief 是否开启发布性能回退
 */
/**
 * @locale en
 * @type keytype
 * @brief  Whether to turn on release performance fallback
 */
enum PerformanceAlarmMode {
    /**
     * @locale zh
     * @brief 未开启发布性能回退
     */
    /**
     * @locale en
     * @brief Not enabled Release performance fallback
     */
    kPerformanceAlarmModeNormal = 0,
    /**
     * @locale zh
     * @brief 已开启发布性能回退
     */
    /**
     * @locale en
     * @brief Open Release Performance Rollback
     */
    kPerformanceAlarmModeSimulcast = 1,
};

/**
 * @locale zh
 * @type errorcode
 * @brief 回调错误码。  <br>
 *        SDK 内部遇到不可恢复的错误时，会通过 `onError` 回调通知用户。
 */
/**
 * @locale en
 * @type errorcode
 * @brief Callback error code.   <br>
 *        When an unrecoverable error is encountered inside the SDK, the user is notified via the `onError` callback.
 */
enum ErrorCode {
    /**
     * @locale zh
     * @brief Token 无效。<br>
     *        调用 joinRoom{@link #IRTCRoom#joinRoom} 进房时使用的 Token 参数有误或过期失效。需要重新获取 Token，并调用 updateToken{@link #IRTCRoom#updateToken} 方法更新 Token。
     */
    /**
     * @locale en
     * @brief Token  is invalid.<br>
     *        The Token used when calling joinRoom{@link #IRTCRoom#joinRoom} is invalid or expired. The user is required to retrieve the token and call the updateToken{@link #IRTCRoom#updateToken} to update the token.
     */
    kErrorCodeInvalidToken = -1000,
    /**
     * @locale zh
     * @brief 加入房间错误。<br>
     *        进房时发生未知错误导致加入房间失败。需要用户重新加入房间。
     */
    /**
     * @locale en
     * @brief Join room error.<br>
     *        An unknown error occurred while joining the room, which caused the joining room to fail. Users are required to rejoin the room.
     */
    kErrorCodeJoinRoom = -1001,
    /**
     * @locale zh
     * @brief 没有发布音视频流权限。<br>
     *        用户在所在房间中发布音视频流失败，失败原因为用户没有发布流的权限。
     */
    /**
     * @locale en
     * @brief No permission to publish audio & video streams.<br>
     *        The user failed to publish the audio & video stream in the room. The reason for the failure is that the user does not have permission to publish the stream.
     */
    kErrorCodeNoPublishPermission = -1002,
    /**
     * @locale zh
     * @brief 没有订阅音视频流权限。<br>
     *        用户订阅所在房间中的音视频流失败，失败原因为用户没有订阅流的权限。
     */
    /**
     * @locale en
     * @brief No subscription permissions for audio & video streams.<br>
     *        The user failed to subscribe to the audio & video stream in the room where the user is located. The reason for the failure is that the user does not have permission to subscribe to the stream.
     */
    kErrorCodeNoSubscribePermission = -1003,
    /**
     * @locale zh
     * @brief 相同用户 ID 的用户加入本房间，当前用户被踢出房间
     */
    /**
     * @locale en
     * @brief The user has been removed from the room because the same user joined the room on the other client.
     */
    kErrorCodeDuplicateLogin = -1004,
    /**
     * @locale zh
     * @brief 服务端调用 OpenAPI 将当前用户踢出房间
     */
    /**
     * @locale en
     * @brief The user has been removed from the room by the administrator via a OpenAPI call.
     */
    kErrorCodeKickedOut = -1006,
    /**
     * @locale zh
     * @brief 当调用 `createRTCRoom` ，如果roomid 非法，会返回null，并抛出该error
     */
    /**
     * @locale en
     * @brief When calling `createRTCRoom`, if the roomid is illegal, it will return null and throw the error
     */
    kRoomErrorCodeRoomIdIllegal = -1007,
    /**
     * @locale zh
     * @brief Token 过期。加入房间后 Token 过期时，返回此错误码。需使用新的 Token 重新加入房间。
     */
    /**
     * @locale en
     * @brief Token expired. This error code is returned when the user's token expires in the room.<br>
     *        Call joinRoom{@link #IRTCRoom#joinRoom} to rejoin the room with a new required Token.
     */
    kRoomErrorTokenExpired = -1009,
    /**
     * @locale zh
     * @brief 调用 `updateToken` 传入的 Token 无效
     */
    /**
     * @locale en
     * @brief The Token you provided when calling `updateToken` is invalid.
     */
    kRoomErrorUpdateTokenWithInvalidToken = -1010,
    /**
     * @locale zh
     * @brief 服务端调用 OpenAPI 解散房间，所有用户被移出房间。
     */
    /**
     * @locale en
     * @brief Users have been removed from the room because the administrator dismissed the room by calling OpenAPI.
     */
    kErrorCodeRoomDismiss = -1011,
    /**
     * @locale zh
     * @hidden internal use only
     * @brief 加入房间错误。 <br>
     *        进房时, LICENSE 计费账号未使用 LICENSE_AUTHENTICATE SDK，加入房间错误。
     */
    /**
     * @locale en
     * @hidden internal use only
     * @brief Join room error. <br>
     *        The LICENSE billing account does not use the LICENSE_AUTHENTICATE SDK while entering the room, which caused the joining room to fail.
     */
    kErrorCodeJoinRoomWithoutLicenseAuthenticateSDK = -1012,
    /**
     * @locale zh
     * @brief 通话回路检测已经存在同样 roomId 的房间了
     */
    /**
     * @locale en
     * @brief there is a room with the same roomId，whose room id is the same with echo test
     */
    kErrorCodeRoomAlreadyExist = -1013,
    /**
     * @locale zh
     * @brief 加入多个房间时使用了不同的 uid。<br>
     *        同一个引擎实例中，用户需使用同一个 uid 加入不同的房间。
     */
    /**
     * @locale en
     * @brief The local user joins multiple rooms with different uid.<br>
     *        In the same engine instance, users need to use the same uid to join different rooms.
     */
    kErrorCodeUserIDDifferent = -1014,
    /**
     * @locale zh
     * @hidden internal use only
     * @brief 服务端license过期，拒绝进房。 
     */
    /**
     * @locale en
     * @hidden internal use only
     * @brief Server license expired, refused to enter the room. 
     */
    kErrorCodeJoinRoomServerLicenseExpired = -1017,
    /**
     * @locale zh
     * @hidden internal use only
     * @brief 超过服务端license许可的并发量上限，拒绝进房。 
     */
    /**
     * @locale en
     * @hidden internal use only
     * @brief Exceeds the upper limit of the concurrency allowed by the server license, and refuses to enter the room. 
     */
    kErrorCodeJoinRoomExceedsTheUpperLimit = -1018,
    /**
     * @locale zh
     * @hidden internal use only
     * @brief license参数错误，拒绝进房。 
     */
    /**
     * @locale en
     * @hidden internal use only
     * @brief The license parameter is wrong and refuses to enter the room. 
     */
    kErrorCodeJoinRoomLicenseParameterError = -1019,
    /**
     * @locale zh
     * @hidden internal use only
     * @brief license证书路径错误。 
     */
    /**
     * @locale en
     * @hidden internal use only
     * @brief wrong license certificate path. 
     */
    kErrorCodeJoinRoomLicenseFilePathError = -1020,
    /**
     * @locale zh
     * @hidden internal use only
     * @brief license证书不合法。 
     */
    /**
     * @locale en
     * @hidden internal use only
     * @brief The license certificate is illegal, refuse to enter the room. 
     */
    kErrorCodeJoinRoomLicenseIllegal = -1021,
    /**
     * @locale zh
     * @hidden internal use only
     * @brief license证书已经过期，拒绝进房。 
     */
    /**
     * @locale en
     * @hidden internal use only
     * @brief License certificate has expired, refused to enter the room. 
     */
    kErrorCodeJoinRoomLicenseExpired = -1022,
    /**
     * @locale zh
     * @hidden internal use only
     * @brief license证书内容不匹配。 
     */
    /**
     * @locale en
     * @hidden internal use only
     * @brief The content of the license certificate does not match. 
     */
    kErrorCodeJoinRoomLicenseInformationNotMatch = -1023,
    /**
     * @locale zh
     * @hidden internal use only
     * @brief license当前证书与缓存证书不匹配。 
     */
    /**
     * @locale en
     * @hidden internal use only
     * @brief licenseThe current certificate does not match the cached certificate. 
     */
    kErrorCodeJoinRoomLicenseNotMatchWithCache = -1024,
    /**
     * @locale zh
     * @brief 房间被封禁。 
     */
    /**
     * @locale en
     * @brief The room has banned before the user calls `joinRoom`.
     */
    kErrorCodeJoinRoomRoomForbidden = -1025,
    /**
     * @locale zh
     * @brief 用户被封禁。 
     */
    /**
     * @locale en
     * @brief The user has banned before calling `joinRoom`.
     */
    kErrorCodeJoinRoomUserForbidden = -1026,
    /**
     * @locale zh
     * @hidden internal use only
     * @brief license 计费方法没有加载成功。可能是因为 license 相关插件未正确集成。
     */
    /**
     * @locale en
     * @hidden internal use only
     * @brief The license method did not load successfully. Check the corresponding extension.
     */
    kErrorCodeJoinRoomLicenseFunctionNotFound = -1027,
    /**
     * @locale zh
     * @brief 订阅音视频流失败，订阅音视频流总数超过上限。<br>
     *        游戏场景下，为了保证音视频通话的性能和质量，服务器会限制用户订阅的音视频流总数。当用户订阅的音视频流总数已达上限时，继续订阅更多流时会失败，同时用户会收到此错误通知。
     */
    /**
     * @locale en
     * @brief Subscription to audio & video stream failed, the total number of subscribed audio & video streams exceeded the upper limit.<br>
     *        In the game scenario, in order to ensure the performance and quality of audio & video calls, the server will limit the total number of audio & video streams subscribed by the user. When the total number of audio & video streams subscribed by the user has reached the maximum, continuing to subscribe to more streams will fail, and the user will receive this error notification.
     */
    kErrorCodeOverStreamSubscribeLimit = -1070,
    /**
     * @locale zh
     * @brief 发布流失败，发布流总数超过上限。<br>
     *        RTC 系统会限制单个房间内发布的总流数，总流数包括视频流、音频流和屏幕流。如果房间内发布流数已达上限时，本地用户再向房间中发布流时会失败，同时会收到此错误通知。
     */
    /**
     * @locale en
     * @brief Publishing flow failed, the total number of publishing flows exceeds the upper limit. The<br>
     *        RTC system limits the total number of streams published in a single room, including video streams, audio streams, and screen streams. Local users will fail to publish streams to the room when the maximum number of published streams in the room has been reached, and will receive this error notification.
     */
    kErrorCodeOverStreamPublishLimit = -1080,
    /**
     * @locale zh
     * @deprecated since 3.52, use kErrorCodeOverStreamPublishLimit（-1080）instead
     * @brief 发布屏幕流失败，发布流总数超过上限。<br>
     *        RTC 系统会限制单个房间内发布的总流数，总流数包括视频流、音频流和屏幕流。如果房间内发布流数已达上限时，本地用户再向房间中发布流时会失败，同时会收到此错误通知。
     */
    /**
     * @locale en
     * @deprecated since 3.52, use kErrorCodeOverStreamPublishLimit（-1080）instead
     * @brief Publishing the screen stream failed, and the total number of publishing streams exceeded the upper limit. The<br>
     *        RTC system limits the total number of streams published in a single room, including video streams, audio streams, and screen streams. Local users will fail to publish streams to the room when the maximum number of published streams in the room has been reached, and will receive this error notification.
     */
    kErrorCodeOverScreenPublishLimit = -1081,
    /**
     * @locale zh
     * @deprecated since 3.52, use kErrorCodeOverStreamPublishLimit（-1080）instead
     * @brief 发布视频流总数超过上限。<br>
     *        RTC 系统会限制单个房间内发布的视频流数。如果房间内发布视频流数已达上限时，本地用户再向房间中发布视频流时会失败，同时会收到此错误通知。
     */
    /**
     * @locale en
     * @deprecated since 3.52, use kErrorCodeOverStreamPublishLimit（-1080）instead
     * @brief The total number of published video streams exceeds the upper limit.<br>
     *        The RTC system limits the number of video streams posted in a single room. If the maximum number of video streams posted in the room has been reached, local users will fail to post video streams to the room again and will receive this error notification.
     */
    kErrorCodeOverVideoPublishLimit = -1082,
    /**
     * @locale zh
     * @brief 音视频同步失败。  <br>
     *        当前音频源已与其他视频源关联同步关系。  <br>
     *        单个音频源不支持与多个视频源同时同步。
     */
    /**
     * @locale en
     * @brief A/V synchronization failed.  <br>
     *        Current source audio ID has been set by other video publishers in the same room.  <br>
     *        One single audio source cannot be synchronized with multiple video sources at the same time.
     */
    kErrorCodeInvalidAudioSyncUidRepeated = -1083,
    /**
     * @locale zh
     * @brief 服务端异常状态导致退出房间。  <br>
     *        SDK与信令服务器断开，并不再自动重连，可联系技术支持。  
     */
    /**
     * @locale en
     * @brief The user has been removed from the room due to the abnormal status of server. <br>
     *        SDK  is disconnected with the signaling server. It will not reconnect automatically. Please contact technical support.
     */
    kErrorCodeAbnormalServerStatus = -1084,
    /**
     * @locale zh
     * @hidden for internal use only
     * @brief 在一路流推多房间的场景下，在至少有两个房间在发布同一路流时，其中一个房间取消发布失败，此时需要业务方重试或者由业务方通知用户重试取消发布。 
     */
    /**
     * @locale en
     * @hidden for internal use only
     * @brief In the scenario of one stream publish to multiple rooms, when at least two rooms are publishing the same stream, one of the rooms fails to unpublish. At this time, the business party needs to retry or notify the user to retry unpublish. 
     */
    kErrorCodeMultiRoomUnpublishFailed = -1085,
    /**
     * @locale zh
     * @hidden for internal use only
     * @brief 指定服务区域时传入错误参数。
     */
    /**
     * @locale en
     * @hidden for internal use only
     * @brief The area codes are wrong when specifying service area. 
     */
    kErrorCodeWrongAreaCode = -1086,
    /**
     * @hidden for internal use only
     */
    kErrorCodeInternalDeadLockNotify = -1111,
};

/**
 * @locale zh
 * @type errorcode
 * @brief 回调警告码。<br>
 *        警告码说明 SDK 内部遇到问题正在尝试恢复。警告码仅起通知作用。
 */
/**
 * @locale en
 * @type errorcode
 * @brief Callback warning code. The warning code indicates that there is a problem within the SDK and is trying to recover. Warning codes only serve as notifications.
 */
enum WarningCode {
    /**
     * @locale zh
     * @deprecated since 3.45 and will be deleted in 3.51.
     */
    /**
     * @locale en
     * @deprecated since 3.45 and will be deleted in 3.51.
     */
    kWarningCodeGetRoomFailed = -2000,
    /**
     * @locale zh
     * @brief 进房失败。  <br>
     *        当你调用初次加入房间或者由于网络状况不佳断网重连时，由于服务器错误导致进房失败。SDK 会自动重试进房。
     */
    /**
     * @locale en
     * @brief Failed to enter the room.   <br>
     *        When you call the first time to join the room or disconnect and reconnect due to poor network conditions, the room entry fails due to a server error. The SDK automatically retries the room.
     */
    kWarningCodeJoinRoomFailed = -2001,
    /**
     * @locale zh
     * @brief 发布音视频流失败。  <br>
     *        当你在所在房间中发布音视频流时，由于服务器错误导致发布失败。SDK 会自动重试发布。
     */
    /**
     * @locale en
     * @brief Release audio & video stream failed.   <br>
     *        When you publish audio & video streams in your room, the publication fails due to a server error. The SDK automatically retries the release.
     */
    kWarningCodePublishStreamFailed = -2002,
    /**
     * @locale zh
     * @brief 订阅音视频流失败。  <br>
     *        当前房间中找不到订阅的音视频流导致订阅失败。SDK 会自动重试订阅，若仍订阅失败则建议你退出重试。
     */
    /**
     * @locale en
     * @brief Subscription to audio & video stream failed.   <br>
     *         The subscription failed because the audio & video stream for the subscription could not be found in the current room. The SDK will automatically retry the subscription. If the subscription fails, it is recommended that you exit the retry.
     */
    kWarningCodeSubscribeStreamFailed404 = -2003,
    /**
     * @locale zh
     * @brief 订阅音视频流失败。  <br>
     *        当你订阅所在房间中的音视频流时，由于服务器错误导致订阅失败。SDK 会自动重试订阅。
     */
    /**
     * @locale en
     * @brief Subscription to audio & video stream failed.   <br>
     *        When you subscribe to audio & video streams in your room, the subscription fails due to a server error. The SDK automatically retries the subscription.
     */
    kWarningCodeSubscribeStreamFailed5xx = -2004,
    /**
     * @locale zh
     * @hidden currently not available
     * @brief 函数调用顺序错误。
     */
    /**
     * @locale en
     * @hidden currently not available
     * @brief  The function call order is wrong.
     */
    kWarningCodeInvokeError = -2005,
    /**
     * @locale zh
     * @hidden for internal use only
     * @brief 调度异常，服务器返回的媒体服务器地址不可用。
     */
    /**
     * @locale en
     * @hidden for internal use only
     * @brief Scheduling exception, the media server address returned by the server is unavailable.
     */
    kWarningCodeInvalidExpectMediaServerAddress = -2007,
    /**
     * @locale zh
     * @brief 当调用 `setUserVisibility` 将自身可见性设置为 false 后，再尝试发布流会触发此警告。  
     */
    /**
     * @locale en
     * @brief This warning is triggered when you call `setUserVisibility` to set yourself unvisible to others and then try to publish the flow. 
     */
    kWarningCodePublishStreamForbiden = -2009,
    /**
     * @locale zh
     * @deprecated since 3.45 and will be deleted in 3.51.
     * @brief 自动订阅模式未关闭时，尝试开启手动订阅模式会触发此警告。  <br>
     *        你需在进房前关闭自动订阅模式，再调用 subscribeStream{@link #IRTCRoom#subscribeStream} 方法手动订阅音视频流。
     */
    /**
     * @locale en
     * @deprecated since 3.45 and will be deleted in 3.51.
     * @brief When automatic subscription mode is not turned off, trying to turn on manual subscription mode will trigger this warning.   <br>
     *        You need to turn off the automatic subscription mode before entering the room, and then call the subscribeStream{@link #IRTCRoom#subscribeStream} method to manually subscribe to the audio & video stream.
     */
    kWarningCodeSubscribeStreamForbiden = -2010,
    /**
     * @locale zh
     * @brief 发送自定义广播消息失败，当前你未在房间中。
     */
    /**
     * @locale en
     * @brief Sending a custom broadcast message failed, you are not currently in the room.
     */
    kWarningCodeSendCustomMessage = -2011,
    /**
     * @locale zh
     * @brief 当房间内人数超过 500 人时，停止向房间内已有用户发送 `onUserJoined` 和 `onUserLeave` 回调，并通过广播提示房间内所有用户。
     */
    /**
     * @locale en
     * @brief When the number of people in the room exceeds 500, stop sending `onUserJoined` and `onUserLeave` callbacks to existing users in the room, and prompt all users in the room via broadcast.
     */
    kWarningCodeUserNotifyStop = -2013,

    /**
     * @locale zh
     * @brief 用户已经在其他房间发布过流，或者用户正在发布公共流。
     */
    /**
     * @locale en
     * @brief User had published in other room.
     */
    kWarningCodeUserInPublish = -2014,

    /**
     * @locale zh
     * @brief 已存在相同 roomId 的房间，新创建的房间实例已替换旧房间实例。
     */
    /**
     * @locale en
     * @brief A room with the same roomId already exists. The newly created room instance has replaced the old one.
     */
    kWarningCodeOldRoomBeenReplaced = -2016,

    /**
     * @locale zh
     * @brief 当前正在进行回路测试，该接口调用无效
     */
    /**
     * @locale en
     * @brief this inteface has been banned for the engine is in echo testing mode
     */
    kWarningCodeInEchoTestMode = -2017,

    /**
     * @locale zh
     * @brief 摄像头权限异常，当前应用没有获取摄像头权限。
     */
    /**
     * @locale en
     * @brief The camera permission is abnormal, and the current application does not obtain the camera permission.
     */
    kWarningCodeNoCameraPermission = -5001,
    /**
     * @locale zh
     * @brief 已在 3.33 版本中废弃，使用 MediaDeviceError{@link #MediaDeviceError}.kMediaDeviceErrorDeviceNoPermission 代替。<br>
     *        麦克风权限异常，当前应用没有获取麦克风权限。
     */
    /**
     * @locale en
     * @brief Deprecated since 3.45. Please use MediaDeviceError{@link #MediaDeviceError}.kMediaDeviceErrorDeviceNoPermission instead.<br>
     *        The microphone permission is abnormal, and the current application does not obtain microphone permission.
     */
    kWarningCodeNoMicrophonePermission = -5002,
    /**
     * @locale zh
     * @brief 已在 3.33 版本中废弃，使用 MediaDeviceError{@link #MediaDeviceError}.kMediaDeviceErrorDeviceFailure 代替。<br>
     *        音频采集设备启动失败，当前设备可能被其他应用占用。
     */
    /**
     * @locale en
     * @brief Deprecated since 3.45. Please use MediaDeviceError{@link #MediaDeviceError}.kMediaDeviceErrorDeviceFailure instead.<br>
     *        The audio capture device failed to start, and the current device may be occupied by other applications.
     */
    kWarningCodeRecodingDeviceStartFailed = -5003,
    /**
     * @locale zh
     * @brief 已在 3.33 版本中废弃，使用 use MediaDeviceError{@link #MediaDeviceError}.kMediaDeviceErrorDeviceFailure 代替。<br>
     *        音频播放设备启动失败警告，可能由于系统资源不足，或参数错误。
     */
    /**
     * @locale en
     * @brief Deprecated since 3.45. Please use MediaDeviceError{@link #MediaDeviceError}.kMediaDeviceErrorDeviceFailure instead.<br>
     *        The audio playback device failed to start warning, which may be due to insufficient system resources or wrong parameters.
     */
    kWarningCodePlayoutDeviceStartFailed = -5004,
    /**
     * @locale zh
     * @brief 已在 3.33 版本中废弃，使用 MediaDeviceError{@link #MediaDeviceError}.kMediaDeviceErrorDeviceNotFound 代替。<br>
     *        无可用音频采集设备，请插入可用的音频采集设备。
     */
    /**
     * @locale en
     * @brief Deprecated since 3.45. Please use MediaDeviceError{@link #MediaDeviceError}.kMediaDeviceErrorDeviceNotFound instead.<br>
     *        No audio acquisition device is available, please insert the available audio acquisition device.
     */
    kWarningCodeNoRecordingDevice = -5005,
    /**
     * @locale zh
     * @brief 已在 3.33 版本中废弃，使用 MediaDeviceError{@link #MediaDeviceError}.kMediaDeviceErrorDeviceNotFound 代替。<br>
     *        无可用音频播放设备，请插入可用的音频播放设备。
     */
    /**
     * @locale en
     * @brief Deprecated since 3.45. Please use MediaDeviceError{@link #MediaDeviceError}.kMediaDeviceErrorDeviceNotFound instead.<br>
     *        No audio playback device is available, please insert an available audio playback device.
     */
    kWarningCodeNoPlayoutDevice = -5006,
    /**
     * @locale zh
     * @brief 已在 3.33 版本中废弃，使用 MediaDeviceWarning{@link #MediaDeviceWarning}.kMediaDeviceWarningCaptureSilence 代替。<br>
     *        当前音频设备没有采集到有效的声音数据，请检查更换音频采集设备。
     */
    /**
     * @locale en
     * @brief Deprecated since 3.45. Please use MediaDeviceWarning{@link #MediaDeviceWarning}.kMediaDeviceWarningCaptureSilence instead.<br>
     *        The current audio equipment has not collected valid sound data, please check and replace the audio acquisition equipment.
     */
    kWarningCodeRecordingSilence = -5007,
    /**
     * @locale zh
     * @brief 已在 3.33 版本中废弃，使用 MediaDeviceWarning{@link #MediaDeviceWarning}.kMediaDeviceWarningOperationDenied 代替。<br>
     *        媒体设备误操作警告。  <br>
     *        使用自定义采集时，不可调用内部采集开关，调用时将触发此警告。
     */
    /**
     * @locale en
     * @brief Deprecated since 3.45. Please use MediaDeviceWarning{@link #MediaDeviceWarning}.kMediaDeviceWarningOperationDenied instead.<br>
     *        Media device misoperation warning.   <br>
     *        When using custom acquisition, the internal acquisition switch cannot be called, and this warning will be triggered when called.
     */
    kWarningCodeMediaDeviceOperationDenied = -5008,

    /**
     * @locale zh
     * @brief 不支持在 `publishScreen` 之后调用 `setScreenAudioSourceType` 设置屏幕音频采集类型，请在 publishScreen 之前设置
     */
    /**
     * @locale en
     * @brief Setting the screen audio capture type with `setScreenAudioSourceType` after calling `publishScreen` is not supported, please set before `publishScreen`.
     */
    kWarningCodeSetScreenAudioSourceTypeFailed = -5009,

    /**
     * @locale zh
     * @brief 不支持在 `publishScreen` 之后， 通过 `setScreenAudioStreamIndex` 设置屏幕共享时的音频采集方式。
     */
    /**
     * @locale en
     * @brief Setting the audio capture method for screen sharing via `setScreenAudioStreamIndex` after calling `publishScreen` is not supported.
     */
    kWarningCodeSetScreenAudioStreamIndexFailed = -5010,
    /**
     * @locale zh
     * @brief 设置语音音高不合法
     */
    /**
     * @locale en
     * @brief Invalid pitch value setting
     */
    kWarningCodeInvalidVoicePitch = -5011,
    /**
     * @locale zh
     * @brief 设置音频格式不合法
     */
    /**
     * @locale en
     * @brief Invalid audio format setting
     */
    kWarningCodeInvalidAudioFormat = -5012,
    /**
     * @locale zh
     * @brief 外部音频源新旧接口混用
     */
    /**
     * @locale en
     * @brief Mixed use of old and new interfaces for external audio sources
     */
    kWarningCodeInvalidCallForExtAudio = -5013,
    /**
     * @locale zh
     * @brief 非法的远端流索引
     */
    /**
     * @locale en
     * @brief Invalid remote streamKey
     */
    kWarningCodeInvalidRemoteStreamKey = -5014,
    /**
     * @locale zh
     * @brief 指定的内部渲染画布句柄无效。  <br>
     *        当你调用 setLocalVideoCanvas{@link #IRTCVideo#setLocalVideoCanvas} 时指定了无效的画布句柄，触发此回调。
     */
    /**
     * @locale en
     * @brief The specified internal rendering canvas handle is invalid.   <br>
     *        This callback is triggered when you specify an invalid canvas handle when you call setLocalVideoCanvas{@link #IRTCVideo#setLocalVideoCanvas}.
     */
    kWarningCodeInvalidCanvasHandle = -6001,
    /**
     * @locale zh
     * @brief 鉴权文件失效，当检查鉴权文件状态时，本地文件与远端文件不一致会触发次警告。  
     */
    /**
     * @locale en
     * @brief The authentication file is invalid. When checking the status of the authentication file, if the local file is inconsistent with the remote file, a<br>
     *        second warning will be triggered.   
     */
    kWarningLicenseFileExpired = -7001,

    /**
     * @locale zh
     * @brief [音频技术](https://www.volcengine.com/docs/6489/71986) SDK 鉴权失效。联系技术支持人员。
     */
    /**
     * @locale en
     * @brief Authorization failure for [BytePlus Audio SDK](https://go.byteplus.com/audio-sdk). Contact the technical supporters.
     */
    kWarningInvaildSamiAppkeyORToken = -7002,

    /**
     * @locale zh
     * @brief [音频技术](https://www.volcengine.com/docs/6489/71986) 资源加载失败。传入正确的 DAT 路径，或联系技术支持人员。
     */
    /**
     * @locale en
     * @brief Failure to get the resource for [BytePlus Audio SDK](https://go.byteplus.com/audio-sdk). Input the right DAT path or contact the technical supporters.
     */
    kWarningInvaildSamiResourcePath = -7003,

    /**
     * @locale zh
     * @brief [音频技术](https://www.volcengine.com/docs/6489/71986) 库加载失败。使用正确的库，或联系技术支持人员。
     */
    /**
     * @locale en
     * @brief Failure to load the library for [BytePlus Audio SDK](https://go.byteplus.com/audio-sdk). Use right library or contact the technical supporters.
     */
    kWarningLoadSamiLibraryFailed = -7004,

    /**
     * @locale zh
     * @brief [音频技术](https://www.volcengine.com/docs/6489/71986) 不支持此音效。联系技术支持人员。
     */
    /**
     * @locale en
     * @brief The audio effect is not supported by [BytePlus Audio SDK](https://go.byteplus.com/audio-sdk). Contact the technical supporters.
     */
    kWarningInvaildSamiEffectType = -7005,
};

/**
 * @locale zh
 * @type keytype
 * @brief 本地音频流状态。
 */
/**
 * @locale en
 * @type keytype
 * @brief  Local audio stream status.
 */
enum LocalAudioStreamState {
    /**
     * @locale zh
     * @brief 本地音频默认初始状态。<br>
     *        麦克风停止工作时回调该状态，对应错误码 kLocalAudioStreamErrorOk
     */
    /**
     * @locale en
     * @brief The default initial state of the local audio.<br>
     *         Callback to this state when the microphone stops working, corresponding to the error code kLocalAudioStreamErrorOk
     */
    kLocalAudioStreamStateStopped = 0,

    /**
     * @locale zh
     * @brief 本地音频录制设备启动成功。<br>
     *        采集到音频首帧时回调该状态，对应错误码 kLocalAudioStreamErrorOk
     */
    /**
     * @locale en
     * @brief The local audio recording device started successfully.<br>
     *         Callback to the state when the first frame of audio is collected, corresponding to the error code kLocalAudioStreamErrorOk
     */
    kLocalAudioStreamStateRecording,

    /**
     * @locale zh
     * @brief 本地音频首帧编码成功。<br>
     *        音频首帧编码成功时回调该状态，对应错误码 kLocalAudioStreamErrorOk
     */
    /**
     * @locale en
     * @brief The first frame of the local audio was successfully encoded.<br>
     *         Callback to the state when the audio first frame encoding is successful, corresponding to the error code kLocalAudioStreamErrorOk
     */
    kLocalAudioStreamStateEncoding,

    /**
     * @locale zh
     * @brief  本地音频启动失败，在以下时机回调该状态：  <br>
     *       + 本地录音设备启动失败，对应错误码 kLocalAudioStreamErrorRecordFailure <br>
     *       + 检测到没有录音设备权限，对应错误码 kLocalAudioStreamErrorDeviceNoPermission <br>
     *       + 音频编码失败，对应错误码 kLocalAudioStreamErrorEncodeFailure
     */
    /**
     * @locale en
     * @brief  The local audio startup failed, and the status is called back at the following times:   <br>
     *        + The local recording device failed to start, corresponding to the error code kLocalAudioStreamErrorRecordFailure <br>
     *        + No recording device permission was detected, corresponding to the error code kLocalAudioStreamErrorDeviceNoPermission <br>
     *        + The audio encoding failed, corresponding to the error code kLocalAudioStreamErrorEncodeFailure
     */
    kLocalAudioStreamStateFailed,

    /**
     * @locale zh
     * @brief 本地音频静音成功后回调该状态。<br>
     *        调用 setAudioCaptureDeviceMute{@link #IAudioDeviceManager#setAudioCaptureDeviceMute} 成功后回调，对应错误码 LocalAudioStreamError{@link #LocalAudioStreamError} 中的 kLocalAudioStreamErrorOk 。  
     */
    /**
     * @locale en
     * @brief Callback the state after the local audio is successfully muted.<br>
     *         Callback after successful setAudioCaptureDeviceMute{@link #IAudioDeviceManager#setAudioCaptureDeviceMute} call, corresponding to kLocalAudioStreamErrorOk in the error code LocalAudioStreamError{@link #LocalAudioStreamError}. 
     */
    kLocalAudioStreamStateMute,

    /**
     * @locale zh
     * @brief 本地音频解除静音成功后回调该状态。<br>
     *        调用 setAudioCaptureDeviceMute{@link #IAudioDeviceManager#setAudioCaptureDeviceMute} 成功后回调，对应错误码 LocalAudioStreamError{@link #LocalAudioStreamError} 中的 kLocalAudioStreamErrorOk 。  
     */
    /**
     * @locale en
     * @brief Callback the state after the local audio is successfully unmuted.<br>
     *         Callback after successful setAudioCaptureDeviceMute{@link #IAudioDeviceManager#setAudioCaptureDeviceMute} call, corresponding to kLocalAudioStreamErrorOk in the error code LocalAudioStreamError{@link #LocalAudioStreamError}. 
     */
    kLocalAudioStreamStateUnmute
};

/**
 * @locale zh
 * @type keytype
 * @brief 本地音频流状态改变时的错误码。
 */
/**
 * @locale en
 * @type keytype
 * @brief Error code when the state of the local audio stream changes.
 */
enum LocalAudioStreamError {
    /**
     * @locale zh
     * @brief 本地音频状态正常
     */
    /**
     * @locale en
     * @brief Local audio status is normal
     */
    kLocalAudioStreamErrorOk = 0,
    /**
     * @locale zh
     * @brief 本地音频出错原因未知
     */
    /**
     * @locale en
     * @brief Local audio error cause unknown
     */
    kLocalAudioStreamErrorFailure,
    /**
     * @locale zh
     * @brief 没有权限启动本地音频录制设备
     */
    /**
     * @locale en
     * @brief No permission to start local audio recording device
     */
    kLocalAudioStreamErrorDeviceNoPermission,
    /**
     * @locale zh
     * @hidden currently not available
     * @brief 本地音频录制设备已经在使用中
     * @note 该错误码暂未使用
     */
    /**
     * @locale en
     * @hidden currently not available
     * @brief The local audio recording device is already in use<br>
     * The error code is not yet in use
     */
    kLocalAudioStreamErrorDeviceBusy,
    /**
     * @locale zh
     * @brief 本地音频录制失败，建议你检查录制设备是否正常工作
     */
    /**
     * @locale en
     * @brief Local audio recording failed, it is recommended that you check whether the recording device is working properly
     */
    kLocalAudioStreamErrorRecordFailure,
    /**
     * @locale zh
     * @brief 本地音频编码失败
     */
    /**
     * @locale en
     * @brief Local audio encoding failed
     */
    kLocalAudioStreamErrorEncodeFailure,
    /**
     * @locale zh
     *@brief 没有可用的音频录制设备
     */
    /**
     * @locale en
     * @brief No audio recording equipment available
     */
    kLocalAudioStreamErrorNoRecordingDevice
};

/**
 * @locale zh
 * @type keytype
 * @brief 本地视频流状态
 */
/**
 * @locale en
 * @type keytype
 * @brief  Local video stream status
 */
enum LocalVideoStreamState {
    /**
     * @locale zh
     * @brief 本地视频采集停止状态
     */
    /**
     * @locale en
     * @brief Local video capture stop state
     */
    kLocalVideoStreamStateStopped = 0,
    /**
     * @locale zh
     * @brief 本地视频采集设备启动成功
     */
    /**
     * @locale en
     * @brief Local video capture device activated
     */
    kLocalVideoStreamStateRecording,
    /**
     * @locale zh
     * @brief 本地视频采集后，首帧编码成功
     */
    /**
     * @locale en
     * @brief After local video capture, the first frame is encoded successfully
     */
    kLocalVideoStreamStateEncoding,
    /**
     * @locale zh
     * @brief 本地视频采集设备启动失败
     */
    /**
     * @locale en
     * @brief Local video capture device failed to start
     */
    kLocalVideoStreamStateFailed,
};

/**
 * @locale zh
 * @type errorcode
 * @brief 本地视频状态改变时的错误码
 */
/**
 * @locale en
 * @type errorcode
 * @brief Error code when the local video state changes
 */
enum LocalVideoStreamError {
    /**
     * @locale zh
     * @brief 状态正常
     */
    /**
     * @locale en
     * @brief Normal condition
     */
    kLocalVideoStreamErrorOk = 0,
    /**
     * @locale zh
     * @brief 本地视频流发布失败
     */
    /**
     * @locale en
     * @brief Local video stream publishing failed
     */
    kLocalVideoStreamErrorFailure,
    /**
     * @locale zh
     * @brief 没有权限启动本地视频采集设备
     */
    /**
     * @locale en
     * @brief No access to the local video capture device
     */
    kLocalVideoStreamErrorDeviceNoPermission,
    /**
     * @locale zh
     * @brief 本地视频采集设备已被占用
     */
    /**
     * @locale en
     * @brief Local video capture equipment is occupied
     */
    kLocalVideoStreamErrorDeviceBusy,
    /**
     * @locale zh
     * @brief 本地视频采集设备不存在
     */
    /**
     * @locale en
     * @brief Local video capture device does not exist
     */
    kLocalVideoStreamErrorDeviceNotFound,
    /**
     * @locale zh
     * @brief 本地视频采集失败，建议检查采集设备是否正常工作
     */
    /**
     * @locale en
     * @brief Local video capture failed, it is recommended to check whether the acquisition device is working properly
     */
    kLocalVideoStreamErrorCaptureFailure,
    /**
     * @locale zh
     * @brief 本地视频编码失败
     */
    /**
     * @locale en
     * @brief Local video encoding failed
     */
    kLocalVideoStreamErrorEncodeFailure,
    /**
     * @locale zh
     * @brief 通话过程中本地视频采集设备被其他程序抢占，导致设备连接中断
     */
    /**
     * @locale en
     * @brief The local video capture device is disconnected. It is occupied by other programs during the call.
     */
    kLocalVideoStreamErrorDeviceDisconnected
};

/**
 * @locale zh
 * @type keytype
 * @brief 远端音频流状态。
 */
/**
 * @locale en
 * @type keytype
 * @brief  Remote audio stream state. 
 */
enum RemoteAudioState {
    /**
     * @locale zh
     * @brief  不接收远端音频流。
     */
    /**
     * @locale en
     * @brief  The remote audio stream is not received.
     */
    kRemoteAudioStateStopped = 0,
    /**
     * @locale zh
     * @brief 开始接收远端音频流首包。
     */
    /**
     * @locale en
     * @brief Start receiving the remote audio stream header.
     */
    kRemoteAudioStateStarting,
    /**
     * @locale zh
     * @brief  远端音频流正在解码，正常播放。
     */
    /**
     * @locale en
     * @brief  The remote audio stream is decoding and playing normally.
     */
    kRemoteAudioStateDecoding,
    /**
     * @locale zh
     * @brief 远端音频流卡顿。
     */
    /**
     * @locale en
     * @brief Remote audio streaming card.
     */
    kRemoteAudioStateFrozen,
    /**
     * @locale zh
     * @hidden currently not available
     * @brief 远端音频流播放失败
     * @note 该错误码暂未使用
     */
    /**
     * @locale en
     * @hidden currently not available
     * @brief  The remote audio stream failed to play
     * @note  The error code is not yet used
     */
    kRemoteAudioStateFailed,
};

/**
 * @locale zh
 * @type keytype
 * @brief 接收远端音频流状态改变的原因。
 */
/**
 * @locale en
 * @type keytype
 * @brief  Receives the cause of the remote audio stream state change.
 */
enum RemoteAudioStateChangeReason {
    /**
     * @locale zh
     * @brief 内部原因
     */
    /**
     * @locale en
     * @brief Internal reasons
     */
    kRemoteAudioStateChangeReasonInternal = 0,
    /**
     * @locale zh
     * @brief 网络阻塞
     */
    /**
     * @locale en
     * @brief Network blocking
     */
    kRemoteAudioStateChangeReasonNetworkCongestion,
    /**
     * @locale zh
     * @brief 网络恢复正常
     */
    /**
     * @locale en
     * @brief Network back to normal
     */
    kRemoteAudioStateChangeReasonNetworkRecovery,
    /**
     * @locale zh
     * @brief 本地用户停止接收远端音频流
     */
    /**
     * @locale en
     * @brief Local user stops receiving remote audio stream
     */
    kRemoteAudioStateChangeReasonLocalMuted,
    /**
     * @locale zh
     * @brief 本地用户恢复接收远端音频流
     */
    /**
     * @locale en
     * @brief Local users resume receiving remote audio streams
     */
    kRemoteAudioStateChangeReasonLocalUnmuted,
    /**
     * @locale zh
     * @brief 远端用户停止发送音频流
     */
    /**
     * @locale en
     * @brief Remote user stops sending audio stream
     */
    kRemoteAudioStateChangeReasonRemoteMuted,
    /**
     * @locale zh
     * @brief 远端用户恢复发送音频流
     */
    /**
     * @locale en
     * @brief Remote user resumes sending audio stream
     */
    kRemoteAudioStateChangeReasonRemoteUnmuted,
    /**
     * @locale zh
     * @brief 远端用户离开房间
     */
    /**
     * @locale en
     * @brief Remote user leaves room
     */
    kRemoteAudioStateChangeReasonRemoteOffline,
};

/**
 * @locale zh
 * @type keytype
 * @brief 远端视频流状态。状态改变时，会收到 `onRemoteVideoStateChanged` 回调
 */
/**
 * @locale en
 * @type keytype
 * @brief  Remote video stream status. You will receive `onRemoteVideoStateChanged` callback when the state changes.
 */
enum RemoteVideoState {
    /**
     * @locale zh
     * @brief 远端视频流默认初始状态，视频尚未开始播放。
     */
    /**
     * @locale en
     * @brief The remote video stream defaults to the initial state, and the video has not yet started playing.
     */
    kRemoteVideoStateStopped = 0,
    /**
     * @locale zh
     * @brief 本地用户已接收远端视频流首包。
     */
    /**
     * @locale en
     * @brief Local user has received remote video stream header packet.
     */
    kRemoteVideoStateStarting,
    /**
     * @locale zh
     * @brief 远端视频流正在解码，正常播放。
     */
    /**
     * @locale en
     * @brief The remote video stream is decoding and playing normally.
     */
    kRemoteVideoStateDecoding,
    /**
     * @locale zh
     * @brief 远端视频流卡顿，可能有网络等原因。
     */
    /**
     * @locale en
     * @brief Remote video streaming card, there may be network and other reasons.
     */
    kRemoteVideoStateFrozen,
    /**
     * @locale zh
     * @brief 远端视频流播放失败。
     */
    /**
     * @locale en
     * @brief The remote video stream failed to play.
     */
    kRemoteVideoStateFailed,
};

/**
 * @locale zh
 * @type keytype
 * @brief 远端视频流状态改变的原因
 */
/**
 * @locale en
 * @type keytype
 * @brief  Cause of remote video stream state change
 */
enum RemoteVideoStateChangeReason {
    /**
     * @locale zh
     * @brief 内部原因
     */
    /**
     * @locale en
     * @brief Internal reasons
     */
    kRemoteVideoStateChangeReasonInternal = 0,
    /**
     * @locale zh
     * @brief 网络阻塞
     */
    /**
     * @locale en
     * @brief Network blocking
     */
    kRemoteVideoStateChangeReasonNetworkCongestion,
    /**
     * @locale zh
     * @brief 网络恢复正常
     */
    /**
     * @locale en
     * @brief Network back to normal
     */
    kRemoteVideoStateChangeReasonNetworkRecovery,
    /**
     * @locale zh
     * @brief 本地用户停止接收远端视频流或本地用户禁用视频模块
     */
    /**
     * @locale en
     * @brief Local user stops receiving remote video stream or local user disables video module
     */
    kRemoteVideoStateChangeReasonLocalMuted,
    /**
     * @locale zh
     * @brief 本地用户恢复接收远端视频流或本地用户启用视频模块
     */
    /**
     * @locale en
     * @brief Local user resumes receiving remote video streams or local user enables video modules
     */
    kRemoteVideoStateChangeReasonLocalUnmuted,
    /**
     * @locale zh
     * @brief 远端用户停止发送视频流或远端用户禁用视频模块
     */
    /**
     * @locale en
     * @brief The remote user stops sending the video stream or the remote user disables the video module
     */
    kRemoteVideoStateChangeReasonRemoteMuted,
    /**
     * @locale zh
     * @brief 远端用户恢复发送视频流或远端用户启用视频模块
     */
    /**
     * @locale en
     * @brief Remote user resumes sending video stream or remote user enables video module
     */
    kRemoteVideoStateChangeReasonRemoteUnmuted,
    /**
     * @locale zh
     * @brief 远端用户离开频道。状态转换参考 `onUserUnPublishStream`。
     */
    /**
     * @locale en
     * @brief The remote user leaves the channel. State transition see `onUserUnPublishStream`.
     */
    kRemoteVideoStateChangeReasonRemoteOffline,
};

/**
 * @locale zh
 * @type keytype
 * @brief 黑帧视频流状态
 */
/**
 * @locale en
 * @type keytype
 * @brief State of the black frame video stream
 */
enum SEIStreamEventType {
    /**
     * @locale zh
     * @brief 远端用户发布黑帧视频流。  <br>
     *        纯语音通话场景下，远端用户调用 sendSEIMessage{@link #IRTCVideo#sendSEIMessage} 发送 SEI 数据时，SDK 会自动发布一路黑帧视频流，并触发该回调。
     */
    /**
     * @locale en
     * @brief A black frame video stream is published from the remote user.  <br>
     *        In a voice call, when the remote user calls sendSEIMessage{@link #IRTCVideo#sendSEIMessage} to send SEI data, SDK will automatically publish a black frame video stream, and trigger this callback.
     */
    kSEIStreamEventTypeStreamAdd = 0,
    /**
     * @locale zh
     * @brief 远端黑帧视频流移除。该回调的触发时机包括：  <br>
     *        + 远端用户开启摄像头采集，由语音通话切换至视频通话，黑帧视频流停止发布；  <br>
     *        + 远端用户调用 sendSEIMessage{@link #IRTCVideo#sendSEIMessage} 后 1min 内未有 SEI 数据发送，黑帧视频流停止发布；  <br>
     *        + 远端用户调用 setVideoSourceType{@link #IRTCVideo#setVideoSourceType} 切换至自定义视频采集时，黑帧视频流停止发布。
     */
     /**
     * @locale en
     * @brief The black frame video stream is removed. The timing this callback will be triggered is as following:  <br>
     *        + The black frame video stream stops when the remote user turns on their camera, switching from a voice call to a video call.  <br>
     *        + No SEI data is sent within 1min after the remote user calls sendSEIMessage{@link #IRTCVideo#sendSEIMessage}.  <br>
     *        + The remote user calls setVideoSourceType{@link #IRTCVideo#setVideoSourceType} to switch to custom video capture.
     */
    kSEIStreamEventTypeStreamRemove,
};

/**
 * @locale zh
 * @type keytype
 * @brief 性能回退相关数据
 */
/**
 * @locale en
 * @type keytype
 * @brief  Performance fallback related data
 */
struct SourceWantedData {
    /**
     * @locale zh
     * @brief  
     * 未开启发布回退时，此值表示推荐的视频输入宽度，当回退模式为大小流模式时，表示当前推流的最大宽度
     * @brief 如果未开启发送性能回退，此值表示推荐的视频输入宽度；  <br>
     *        如果开启了发送性能回退，此值表示当前推流的最大宽度。
     */
    /**
     * @locale en
     * @brief  
     * When the release rollback is not turned on, this value represents the recommended video input width. When the rollback mode is the large and small stream mode, it represents the maximum width of the current push stream
     * @brief If the send performance rollback is not turned on, this value represents the recommended Video input width;   <br>
     *        If the send performance rollback is turned on, this value represents the maximum width of the current push stream.
     */
    int width;
    /**
     * @locale zh
     * @brief 如果未开启发送性能回退，此值表示推荐的视频输入高度；<br>
     *        如果开启了发送性能回退，此值表示当前推流的最大高度。
     */
    /**
     * @locale en
     * @brief If send performance fallback is not turned on, this value represents the recommended video input height; <br>
     *         If send performance fallback is turned on, this value represents the maximum height of the current push stream.
     */
    int height;
    /**
     * @locale zh
     * @brief 如果未开启发送性能回退，此值表示推荐的视频输入帧率，单位 fps；<br>
     *        如果开启了发送性能回退，此值表示当前推流的最大帧率，单位 fps。
     */
    /**
     * @locale en
     * @brief If send performance fallback is not turned on, this value represents the recommended video input frame rate in fps; <br>
     *         If send performance fallback is turned on, this value represents the maximum frame rate of the current push stream in fps.
     */
    int frame_rate;
};
/**
 * @locale zh
 * @type keytype
 * @brief 用户信息
 */
/**
 * @locale en
 * @type keytype
 * @brief  User information
 */
struct UserInfo {
    /**
     * @locale zh
     * @brief 用户 ID。该字符串符合正则表达式：`[a-zA-Z0-9_@\-\.]{1,128}`。
     */
    /**
     * @locale en
     * @brief User ID. The string matches the regular expression: `[a-zA-Z0-9_@\-\.]{1,128}`.
     */
    const char* uid = nullptr;
    /**
     * @locale zh
     * @brief 用户的额外信息，最大长度为 200 字节。会在 `onUserJoined` 中回调给远端用户。
     */
    /**
     * @locale en
     * @brief Additional information of the user. The maximum length is 200 bytes. The remote user will receive the info in `onUserJoined`.
     */
    const char* extra_info = nullptr;
};

/**
 * @locale zh
 * @type keytype
 * @brief 通话相关的统计信息
 */
/**
 * @locale en
 * @type keytype
 * @brief  Call related statistics
 */
struct RtcRoomStats {
    /**
     * @locale zh
     * @brief 当前应用的上行丢包率，取值范围为 [0, 1]
     */
    /**
     * @locale en
     * @brief Current Tx packet loss rate. The range is [0,1].
     */
    float tx_lostrate;
    /**
     * @locale zh
     * @brief 当前应用的下行丢包率，取值范围为 [0, 1]
     */
    /**
     * @locale en
     * @brief Current Rx packet loss rate. The range is [0,1].
     */
    float rx_lostrate;
    /**
     * @locale zh
     * @brief 客户端到服务端数据传输的往返时延（单位 ms）
     */
    /**
     * @locale en
     * @brief Round-trip time (in ms) from client side to server side
     */
    int rtt;
    /**
     * @locale zh
     * @brief 进房到退房之间累计时长，单位为 s
     */
    /**
     * @locale en
     * @brief Cumulative time between the user joining the room and leaving the room in seconds.
     */
    unsigned int duration;
    /**
     * @locale zh
     * @brief 本地用户的总发送字节数 (bytes)，累计值
     */
    /**
     * @locale en
     * @brief Cumulative data sent by the user in bytes.
     */
    unsigned int tx_bytes;
    /**
     * @locale zh
     * @brief 本地用户的总接收字节数 (bytes)，累计值
     */
    /**
     * @locale en
     * @brief Cumulative data received by the user in bytes.
     */
    unsigned int rx_bytes;
    /**
     * @locale zh
     * @brief 发送码率（kbps），获取该数据时的瞬时值
     */
    /**
     * @locale en
     * @brief The instantaneous value of Tx bitrate in kbps
     */
    unsigned short tx_kbitrate;
    /**
     * @locale zh
     * @brief 接收码率（kbps），获取该数据时的瞬时值
     */
    /**
     * @locale en
     * @brief The instantaneous value of Rx bitrate in kbps
     */
    unsigned short rx_kbitrate;
    /**
     * @locale zh
     * @brief 音频接收码率（kbps），获取该数据时的瞬时值
     */
    /**
     * @locale en
     * @brief The instantaneous value of audio Rx bitrate in kbps
     */
    unsigned short rx_audio_kbitrate;
    /**
     * @locale zh
     * @brief 音频包的发送码率（kbps），获取该数据时的瞬时值
     */
    /**
     * @locale en
     * @brief The instantaneous value of audio Tx bitrate in kbps
     */
    unsigned short tx_audio_kbitrate;
    /**
     * @locale zh
     * @brief 视频接收码率（kbps），获取该数据时的瞬时值
     */
    /**
     * @locale en
     * @brief The instantaneous value of video Rx bitrate in kbps
     */
    unsigned short rx_video_kbitrate;
    /**
     * @locale zh
     * @brief 视频发送码率（kbps），获取该数据时的瞬时值
     */
    /**
     * @locale en
     * @brief The instantaneous value of video Tx bitrate in kbps
     */
    unsigned short tx_video_kbitrate;
    /**
     * @locale zh
     * @brief 屏幕接收码率，获取该数据时的瞬时值，单位为 Kbps
     */
    /**
     * @locale en
     * @brief The instantaneous RX bitrate of screen-sharing video in Kbps
     */
    unsigned short rx_screen_kbitrate;
    /**
     * @locale zh
     * @brief 屏幕发送码率，获取该数据时的瞬时值，单位为 Kbps
     */
    /**
     * @locale en
     * @brief The instantaneous TX bitrate of screen-sharing video in Kbps
     */
    unsigned short tx_screen_kbitrate;
    /**
     * @locale zh
     * @brief 当前房间内的可见用户人数
     */
    /**
     * @locale en
     * @brief Number of visible users in the current room
     */
    unsigned int user_count;
    /**
     * @locale zh
     * @brief 当前应用的 CPU 使用率 (%)
     */
    /**
     * @locale en
     * @brief CPU usage (%) of the application
     */
    double cpu_app_usage;
    /**
     * @locale zh
     * @hidden currently not available
     * @brief 当前系统的 CPU 使用率 (%)
     */
    /**
     * @locale en
     * @hidden currently not available
     * @brief Current CPU usage (%)
     */
    double cpu_total_usage;
    /**
     * @locale zh
     * @hidden currently not available
     * @brief 系统上行网络抖动（ms）
     */
    /**
     * @locale en
     * @hidden currently not available
     * @brief Tx jitter(ms)
     */
    int tx_jitter;
    /**
     * @locale zh
     * @hidden currently not available
     * @brief 系统下行网络抖动（ms）
     */
    /**
     * @locale en
     * @hidden currently not available
     * @brief Rx jitter(ms)
     */
    int rx_jitter;
    /**
     * @locale zh
     * @brief 蜂窝路径发送的码率 (kbps)，为获取该数据时的瞬时值
     */
    /**
     * @locale en
     * @brief Cellular Link Send bit rate  (kbps), get the instantaneous value of the data
     */
    unsigned short tx_cellular_kbitrate;
    /**
     * @locale zh
     * @brief 蜂窝路径接收码率 (kbps)，为获取该数据时的瞬时值
     */
    /**
     * @locale en
     * @brief Cellular Link Receive bit rate  (kbps), get the instantaneous value of the data
     */
    unsigned short rx_cellular_kbitrate;
};

/**
 * @locale zh
 * @type keytype
 * @brief 视频的编码类型
 */
/**
 * @locale en
 * @type keytype
 * @brief Video encoding type
 */
enum VideoCodecType {
    /**
     * @locale zh
     * @brief 未知类型
     */
    /**
     * @locale en
     * @brief  Unknown type
     */
    kVideoCodecTypeUnknown = 0,
    /**
     * @locale zh
     * @brief 标准 H264 编码格式
     */
    /**
     * @locale en
     * @brief H.264 format
     */
    kVideoCodecTypeH264 = 1,
    /**
     * @locale zh
     * @brief ByteVC1 编码格式
     */
    /**
     * @locale en
     * @brief ByteVC1 format
     */
    kVideoCodecTypeByteVC1 = 2,
};


/**
 * @locale zh
 * @hidden(Windows, Linux, macOS)
 * @type keytype
 * @brief 超分模式。
 */
/**
 * @locale en
 * @hidden not available
 * @type keytype
 * @brief Super-resolution mode.
 */
enum VideoSuperResolutionMode {
    /**
     * @locale zh
     * @brief 关闭超分。
     */
    /**
     * @locale en
     * @brief Turn off super-resolution mode.
     */
    kVideoSuperResolutionModeOff = 0,
    /**
     * @locale zh
     * @brief 开启超分。
     */
    /**
     * @locale en
     * @brief Turn on super-resolution mode.
     */
    kVideoSuperResolutionModeOn = 1,
};

/**
 * @locale zh
 * @hidden(Windows, Linux, macOS)
 * @type keytype
 * @brief 视频降噪模式。
 */
/**
 * @locale en
 * @hidden not available
 * @type keytype
 * @brief Video noise reduction mode.
 */
enum VideoDenoiseMode {
    /**
     * @locale zh
     * @brief 视频降噪关闭。
     */
    /**
     * @locale en
     * @brief Video noise reduction is turned off.
     */
    kVideoDenoiseModeOff = 0,
    /**
     * @locale zh
     * @brief 视频降噪开启，由 ByteRTC 后台配置视频降噪算法。
     */
    /**
     * @locale en
     * @brief Video noise reduction mode is turned on. The algorithm is configured by ByteRTC.
     */
    kVideoDenoiseModeAuto = 1,
};

/**
 * @locale zh
 * @type keytype
 * @brief 本地音频流统计信息，统计周期为 2s 。  <br>
 *        本地用户发布音频流成功后，SDK 会周期性地通过 `onLocalStreamStats`<br>
 *        通知用户发布的音频流在此次统计周期内的发送状况。此数据结构即为回调给用户的参数类型。  
 */
/**
 * @locale en
 * @type keytype
 * @brief Local audio stream statistics, reference period 2s. <br>
 *         After the local user publishes the audio stream successfully, the SDK will periodically notify the user through `onLocalStreamStats`<br>
 *         The transmission status of the published audio stream during this reference period. This data structure is the type of parameter that is called back to the user. 
 */
struct LocalAudioStats {
    /**
     * @locale zh
     * @brief 音频丢包率。此次统计周期内的音频上行丢包率，取值范围为 [0, 1]。  
     */
    /**
     * @locale en
     * @brief Audio packet loss rate. The audio uplink packet loss rate in this reference period is % and the value range is [0,1]. 
     */
    float audio_loss_rate;
    /**
     * @locale zh
     * @brief 发送码率。此次统计周期内的音频发送码率，单位为 kbps 。  
     */
    /**
     * @locale en
     * @brief Send rate. The audio transmission rate in the reference period is kbps. 
     */
    int send_kbitrate;
    /**
     * @locale zh
     * @brief 采集采样率。此次统计周期内的音频采集采样率信息，单位为 Hz 。  
     */
    /**
     * @locale en
     * @brief Acquisition sampling rate. Audio sampling rate information collected in the reference period, in units of Hz. 
     */
    int record_sample_rate;
    /**
     * @locale zh
     * @brief 统计间隔。此次统计周期的间隔，单位为 ms 。  <br>
     *        此字段用于设置回调的统计周期，默认设置为 2s 。
     */
    /**
     * @locale en
     * @brief Statistical interval. The interval of this reference period is in ms. <br>
     *        This field is used to set the reference period for the callback. The default setting is 2s.
     */
    int stats_interval;
    /**
     * @locale zh
     * @brief 往返时延。单位为 ms 。  
     */
    /**
     * @locale en
     * @brief Round-trip time. The unit is ms. 
     */
    int rtt;
    /**
     * @locale zh
     * @brief 音频声道数。  
     */
    /**
     * @locale en
     * @brief Number of audio channels.   
     */
    int num_channels;
    /**
     * @locale zh
     * @brief 音频发送采样率。此次统计周期内的音频发送采样率信息，单位为 Hz 。  
     */
    /**
     * @locale en
     * @brief Audio transmission sampling rate. Audio transmission sampling rate information in the reference period, in Hz. 
     */
    int sent_sample_rate;
    /**
     * @locale zh
     * @brief 音频上行网络抖动，单位为 ms 。  
     */
    /**
     * @locale en
     * @brief Audio uplink network jitter in ms. 
     */
    int jitter;
};

/**
 * @locale zh
 * @type keytype
 * @brief 远端音频流统计信息，统计周期为 2s。  <br>
 *        本地用户订阅远端音频流成功后，SDK 会周期性地通过 `onRemoteStreamStats` 通知本地用户订阅的音频流在此次统计周期内的接收状况。此数据结构即为回调给本地用户的参数类型。  
 */
/**
 * @locale en
 * @type keytype
 * @brief Remote audio stream statistics, reference period 2s. <br>
 *        After a local user subscribes to a remote audio stream successfully, the SDK periodically notifies the local user of the reception status of the subscribed audio stream during this reference period through `onRemoteStreamStats`. This data structure is the type of parameter that is called back to the local user. 
 */
struct RemoteAudioStats {
    /**
     * @locale zh
     * @brief 音频丢包率。统计周期内的音频下行丢包率，取值范围为 [0, 1] 。  
     */
    /**
     * @locale en
     * @brief Audio packet loss rate. The audio downlink packet loss rate in the reference period, the value range is  [0,1]. 
     */
    float audio_loss_rate;
    /**
     * @locale zh
     * @brief 接收码率。统计周期内的音频接收码率，单位为 kbps 。  
     */
    /**
     * @locale en
     * @brief Receiving bit rate. The audio reception rate in the reference period in kbps. 
     */
    int received_kbitrate;
    /**
     * @locale zh
     * @brief 音频卡顿次数。统计周期内的卡顿次数。  
     */
    /**
     * @locale en
     * @brief Number of audio stalls. Number of stalls in the reference period.
     */
    int stall_count;
    /**
     * @locale zh
     * @brief 音频卡顿时长。统计周期内的卡顿时长，单位为 ms 。  
     */
    /**
     * @locale en
     * @brief Audio stall Duration. Stall duration in the reference period in ms. 
     */
    int stall_duration;
    /**
     * @locale zh
     * @brief 用户体验级别的端到端延时。从发送端采集完成编码开始到接收端解码完成渲染开始的延时，单位为 ms 。  
     */
    /**
     * @locale en
     * @brief End-to-end latency at the user experience level. The delay from the start of encoding at the sending end to the start of decoding at the receiving end, in units of ms. 
     */
    long e2e_delay;
    /**
     * @locale zh
     * @brief 播放采样率。统计周期内的音频播放采样率信息，单位为 Hz 。  
     */
    /**
     * @locale en
     * @brief Play sample rate. Audio playback sample rate information within the reference period in Hz. 
     */
    int playout_sample_rate;
    /**
     * @locale zh
     * @brief 统计间隔。此次统计周期的间隔，单位为 ms 。  
     */
    /**
     * @locale en
     * @brief Statistical interval. The interval of this reference period is in ms. 
     */
    int stats_interval;
    /**
     * @locale zh
     * @brief 客户端到服务端数据传输的往返时延，单位为 ms。 
     */
    /**
     * @locale en
     * @brief Round-trip time for client side to server level data transfer in ms. 
     */
    int rtt;
    /**
     * @locale zh
     * @brief 发送端——服务端——接收端全链路数据传输往返时延。单位为 ms 。  
     */
    /**
     * @locale en
     * @brief The sender-server level-the receiver-link data transmission round-trip time. The unit is ms. 
     */
    int total_rtt;
    /**
     * @locale zh
     * @brief 远端用户发送的音频流质量。远端用户发送的音频流质量。值含义参考 NetworkQuality{@link #NetworkQuality}。
     */
    /**
     * @locale en
     * @brief The quality of the audio stream sent by the remote user. Value meaning reference NetworkQuality{@link #NetworkQuality}. 
     */
    int quality;
    /**
     * @locale zh
     * @brief 因引入 jitter buffer 机制导致的延时。单位为 ms 。  
     */
    /**
     * @locale en
     * @brief The delay caused by the introduction of the jitter buffer mechanism. The unit is ms. 
     */
    int jitter_buffer_delay;
    /**
     * @locale zh
     * @brief 音频声道数。  
     */
    /**
     * @locale en
     * @brief Number of audio channels.   
     */
    int num_channels;
    /**
     * @locale zh
     * @brief 音频接收采样率。统计周期内接收到的远端音频采样率信息，单位为 Hz 。  
     */
    /**
     * @locale en
     * @brief Audio reception sampling rate. Remote audio sampling rate information received within the reference period, in Hz. 
     */
    int received_sample_rate;
    /**
     * @locale zh
     * @brief 远端用户在加入房间后发生音频卡顿的累计时长占音频总有效时长的百分比。音频有效时长是指远端用户进房发布音频流后，除停止发送音频流和禁用音频模块之外的音频时长。
     */
    /**
     * @locale en
     * @brief The accumulated length of the audio card occurs after the remote user joins the room as a percentage of the total effective length of the audio. The effective duration of audio refers to the duration of audio other than stopping sending audio streams and disabling audio modules after remote users enter the room to publish audio streams.
     */
    int frozen_rate;
    /**
     * @locale zh
     * @brief 音频丢包补偿(PLC) 样点总个数。  
     */
    /**
     * @locale en
     * @brief Audio packet loss compensation (PLC)  total number of sample points. 
     */
    int concealed_samples;
    /**
     * @locale zh
     * @brief 音频丢包补偿(PLC) 累计次数。  
     */
    /**
     * @locale en
     * @brief Audio packet loss compensation (PLC)  cumulative times. 
     */
    int concealment_event;
    /**
     * @locale zh
     * @brief 音频解码采样率。统计周期内的音频解码采样率信息，单位为 Hz 。  
     */
    /**
     * @locale en
     * @brief Audio decoding sample rate. Audio decoding sample rate information in the reference period in Hz. 
     */
    int dec_sample_rate;
    /**
     * @locale zh
     * @brief 此次订阅中，对远端音频流进行解码的累计耗时。单位为 s。
     */
    /**
     * @locale en
     * @brief Cumulative decoding time in seconds of the remote audio stream in this subscription.
     */
    int dec_duration;
    /**
     * @locale zh
     * @brief 音频下行网络抖动，单位为 ms 。  
     */
    /**
     * @locale en
     * @brief Audio downlink network jitter in ms. 
     */
    int jitter;
};

/**
 * @locale zh
 * @type keytype
 * @brief 本地视频流统计信息，统计周期为 2s 。  <br>
 *        本地用户发布视频流成功后，SDK 会周期性地通过 `onLocalStreamStats`<br>
 *        通知用户发布的视频流在此次统计周期内的发送状况。此数据结构即为回调给用户的参数类型。  
 */
/**
 * @locale en
 * @type keytype
 * @brief Local video stream statistics, reference period 2s. <br>
 *        After a local user publishes a video stream successfully, the SDK will periodically notify the user through `onLocalStreamStats`<br>
 *        The delivery status of the published video stream during this reference period. This data structure is the type of parameter that is called back to the user. 
 */
struct LocalVideoStats {
    /**
     * @locale zh
     * @brief 发送码率。此次统计周期内实际发送的分辨率最大的视频流的发送码率，单位为 Kbps
     */
    /**
     * @locale en
     * @brief TX bitrate in Kbps of the video stream with the highest resolution within the reference period
     */
    int sent_kbitrate;
    /**
     * @locale zh
     * @brief 采集帧率。此次统计周期内的视频采集帧率，单位为 fps 。
     */
    /**
     * @locale en
     * @brief Sampling frame rate in fps of video capture during this reference period
     */
    int input_frame_rate;
    /**
     * @locale zh
     * @brief 发送帧率。此次统计周期内实际发送的分辨率最大的视频流的视频发送帧率，单位为 fps 。
     */
    /**
     * @locale en
     * @brief TX frame rate in fps of the video stream with the highest resolution within the reference period
     */
    int sent_frame_rate;
    /**
     * @locale zh
     * @brief 编码器输出帧率。当前编码器在此次统计周期内实际发送的分辨率最大的视频流的输出帧率，单位为 fps 。
     */
    /**
     * @locale en
     * @brief Encoder-output frame rate in fps of the video stream with the highest resolution within the reference period
     */
    int encoder_output_frame_rate;
    /**
     * @locale zh
     * @brief 本地渲染帧率。此次统计周期内的本地视频渲染帧率，单位为 fps 。
     */
    /**
     * @locale en
     * @brief Local-rendering frame rate in fps during this reference period
     */
    int renderer_output_frame_rate;
    /**
     * @locale zh
     * @brief 统计间隔，单位为 ms 。<br>
     *        此字段用于设置回调的统计周期，默认设置为 2s 。
     */
    /**
     * @locale en
     * @brief Reference period in ms.<br>
     *        This field is used to set the reference period for the callback, which is 2 s by default.
     */
    int stats_interval;
    /**
     * @locale zh
     * @brief 视频丢包率。此次统计周期内的视频上行丢包率，取值范围为 [0，1] 。
     */
    /**
     * @locale en
     * @brief Video packet loss rate. The video uplink packet loss rate in this reference period ranges from  [0,1].
     */
    float video_loss_rate;
    /**
     * @locale zh
     * @brief 往返时延，单位为 ms 。
     */
    /**
     * @locale en
     * @brief Round-trip time in ms.
     */
    int rtt;
    /**
     * @locale zh
     * @brief 视频编码码率。此次统计周期内的实际发送的分辨率最大的视频流视频编码码率，单位为 Kbps 。
     */
    /**
     * @locale en
     * @brief Video encoding bitrate in Kbps of the video stream with the highest resolution within the reference period.
     */
    int encoded_bitrate;
    /**
     * @locale zh
     * @brief 实际发送的分辨率最大的视频流的视频编码宽度，单位为 px 。
     */
    /**
     * @locale en
     * @brief Video encoding width in px of the video stream with the highest resolution within the reference period
     */
    int encoded_frame_width;
    /**
     * @locale zh
     * @brief 实际发送的分辨率最大的视频流的视频编码高度，单位为 px 。
     */
    /**
     * @locale en
     * @brief Video encoding height in px of the video stream with the highest resolution within the reference period
     */
    int encoded_frame_height;
    /**
     * @locale zh
     * @brief 此次统计周期内实际发送的分辨率最大的视频流的发送的视频帧总数。
     */
    /**
     * @locale en
     * @brief The total number of the video stream with the highest resolution within the reference period sent in the reference period.
     */
    int encoded_frame_count;
    /**
     * @locale zh
     * @brief 视频的编码类型，具体参考 VideoCodecType{@link #VideoCodecType} 。
     */
    /**
     * @locale en
     * @brief For the encoding type of the video, please refer to VideoCodecType{@link #VideoCodecType}.
     */
    VideoCodecType codec_type;
    /**
     * @locale zh
     * @brief 所属用户的媒体流是否为屏幕流。你可以知道当前统计数据来自主流还是屏幕流。
     */
    /**
     * @locale en
     * @brief Whether the media stream belongs to the user is a screen stream. You can know whether the current statistics come from mainstream or screen stream.
     */
    bool is_screen;
    /**
     * @locale zh
     * @brief 视频上行网络抖动，单位为 ms 。  
     */
    /**
     * @locale en
     * @brief Video uplink network jitter in ms. 
     */
    int jitter;
    /**
     * @locale zh
     * @hidden(Windows, Linux, macOS)
     * @brief 视频降噪模式。具体参看 VideoDenoiseMode{@link #VideoDenoiseMode} 。
     */
    /**
     * @locale en
     * @hidden(Windows, Linux, macOS)
     * @brief Video noise reduction mode. Refer to VideoDenoiseMode{@link #VideoDenoiseMode} for more details.
     */
    VideoDenoiseMode video_denoise_mode;
    /**
     * @locale zh
     * @brief 视频编码平均耗时，单位ms。
     */
    /**
     * @locale en
     * @brief Average time spent on video encoding in ms.
     */
    int codec_elapse_per_frame;

};

/**
 * @locale zh
 * @type keytype
 * @brief 远端视频流统计信息，统计周期为 2s 。  <br>
 *        本地用户订阅远端视频流成功后，SDK 会周期性地通过 `onRemoteStreamStats`<br>
 *        通知本地用户订阅的远端视频流在此次统计周期内的接收状况。此数据结构即为回调给本地用户的参数类型。  
 */
/**
 * @locale en
 * @type keytype
 * @brief Remote video stream statistics, reference period 2s. <br>
 *         After the local user subscribes to the remote video stream successfully, the SDK will periodically notify the local user of the reception status of the remote video stream subscribed to during this reference period through `onRemoteStreamStats`<br>
 *        . This data structure is the type of parameter that is called back to the local user. 
 */
struct RemoteVideoStats {
    /**
     * @locale zh
     * @brief 视频宽度
     */
    /**
     * @locale en
     * @brief Video Width
     */
    int width;
    /**
     * @locale zh
     * @brief 视频高度
     */
    /**
     * @locale en
     * @brief Video height
     */
    int height;
    /**
     * @locale zh
     * @brief 视频丢包率。统计周期内的视频下行丢包率，取值范围：[0，1] 。
     */
    /**
     * @locale en
     * @brief Video packet loss rate. Video downlink packet loss rate in the reference period, in units of %, and in the range of [0,1].
     */
    float video_loss_rate;
    /**
     * @locale zh
     * @brief 接收码率。统计周期内的视频接收码率，单位为 kbps 。
     */
    /**
     * @locale en
     * @brief Receiving bit rate. Video reception rate within the reference period, in kbps.
     */
    int received_kbitrate;
    /**
     * @locale zh
     * @brief 解码器输出帧率。统计周期内的视频解码器输出帧率，单位 fps 。
     */
    /**
     * @locale en
     * @brief The decoder outputs the frame rate. Video decoder output frame rate within the reference period, in fps.
     */
    int decoder_output_frame_rate;
    /**
     * @locale zh
     * @brief 渲染帧率。统计周期内的视频渲染帧率，单位 fps 。
     */
    /**
     * @locale en
     * @brief Render frame rate. The video rendering frame rate in the reference period, in fps.
     */
    int renderer_output_frame_rate;
    /**
     * @locale zh
     * @brief 卡顿次数。统计周期内的卡顿次数。
     */
    /**
     * @locale en
     * @brief Number of stalls. Number of stalls in the reference period.
     */
    int stall_count;
    /**
     * @locale zh
     * @brief 卡顿时长。统计周期内的视频卡顿总时长。单位 ms 。
     */
    /**
     * @locale en
     * @brief Stall duration. The total duration of the video stall in the reference period. Unit ms.
     */
    int stall_duration;
    /**
     * @locale zh
     * @brief 用户体验级别的端到端延时。从发送端采集完成编码开始到接收端解码完成渲染开始的延时，单位为 ms 。
     */
    /**
     * @locale en
     * @brief End-to-end latency at the user experience level. The delay from the start of encoding at the sending end to the start of decoding at the receiving end, in units of ms.
     */
    long e2e_delay;
    /**
     * @locale zh
     * @brief 所属用户的媒体流是否为屏幕流。你可以知道当前数据来自主流还是屏幕流。
     */
    /**
     * @locale en
     * @brief Whether the media stream belongs to the user is a screen stream. You can know whether the current data comes from mainstream or screen stream.
     */
    bool is_screen;
    /**
     * @locale zh
     * @brief 统计间隔，此次统计周期的间隔，单位为 ms 。  <br>
     *        此字段用于设置回调的统计周期，目前设置为 2s 。
     */
    /**
     * @locale en
     * @brief Statistical interval, the interval of this reference period, in ms. <br>
     *        This field is used to set the reference period for the callback, currently set to 2s.
     */
    int stats_interval;
    /**
     * @locale zh
     * @brief 往返时延，单位为 ms 。
     */
    /**
     * @locale en
     * @brief Round-trip time in ms.
     */
    int rtt;
    /**
     * @locale zh
     * @brief 远端用户在进房后发生视频卡顿的累计时长占视频总有效时长的百分比（%）。视频有效时长是指远端用户进房发布视频流后，除停止发送视频流和禁用视频模块之外的视频时长。
     */
    /**
     * @locale en
     * @brief The cumulative duration of the video card of the remote user accounts for the percentage (%) of the total effective duration of the video after entering the room. The effective duration of the video refers to the duration of the video other than stopping sending the video stream and disabling the video module after the remote user enters the room to publish the video stream.
     */
    int frozen_rate;
    /**
     * @locale zh
     * @brief 视频的编码类型，具体参考 VideoCodecType{@link #VideoCodecType} 。
     */
    /**
     * @locale en
     * @brief For the encoding type of the video, please refer to VideoCodecType{@link #VideoCodecType}.
     */
    VideoCodecType codec_type;
    /**
     * @locale zh
     * @brief 对应多种分辨率的流的下标。
     */
    /**
     * @locale en
     * @brief For subscripts of streams with multiple resolutions.
     */
    int video_index;
    /**
     * @locale zh
     * @brief 视频下行网络抖动，单位为 ms。  
     */
    /**
     * @locale en
     * @brief Video downlink network jitter in ms. 
     */
    int jitter;
    /**
     * @locale zh
     * @hidden(Windows, Linux, macOS)
     * @brief 远端视频超分模式，参看 VideoSuperResolutionMode{@link #VideoSuperResolutionMode}。
     */
    /**
     * @locale en
     * @hidden(Windows, Linux, macOS)
     * @brief Super-resolution mode. See VideoSuperResolutionMode{@link #VideoSuperResolutionMode}.
     */
    VideoSuperResolutionMode super_resolution_mode;
    /**
     * @locale zh
     * @brief 视频解码平均耗时，单位ms。
     */
    /**
     * @locale en
     * @brief Average time spent on video decoding in ms.
     */
    int codec_elapse_per_frame;
};

/**
 * @locale zh
 * @type keytype
 * @brief 本地音/视频流统计信息以及网络状况，统计周期为 2s 。  <br>
 *        本地用户发布音/视频流成功后，SDK 会周期性地通过 `onLocalStreamStats`<br>
 *        通知本地用户发布的音/视频流在此次统计周期内的发送状况。此数据结构即为回调给用户的参数类型。  
 */
/**
 * @locale en
 * @type keytype
 * @brief Local audio/video stream statistics and network status, the reference period is 2s. <br>
 *        After the local user publishes the audio/video stream successfully, the SDK will periodically notify the local user through `onLocalStreamStats`<br>
 *        The transmission status of the published audio/video stream during this reference period. This data structure is the type of parameter that is called back to the user. 
 */
struct LocalStreamStats {
    /**
     * @locale zh
     * @brief 本地设备发送音频流的统计信息，详见 LocalAudioStats{@link #LocalAudioStats}
     */
    /**
     * @locale en
     * @brief For statistics on audio streams sent by local devices. See LocalAudioStats{@link #LocalAudioStats}
     */
    LocalAudioStats audio_stats;
    /**
     * @locale zh
     * @brief 本地设备发送视频流的统计信息，详见 LocalVideoStats{@link #LocalVideoStats}
     */
    /**
     * @locale en
     * @brief For statistics on video streams sent by local devices. See LocalVideoStats{@link #LocalVideoStats}
     */
    LocalVideoStats video_stats;
    /**
     * @locale zh
     * @brief 所属用户的媒体流上行网络质量，详见 NetworkQuality{@link #NetworkQuality}
     * @deprecated since 3.36 and will be deleted in 3.51, use onNetworkQuality{@link #IRTCRoomEventHandler#onNetworkQuality} instead.
     */
    /**
     * @locale en
     * @brief For the media stream uplink network quality of the user you belong to. See NetworkQuality{@link #NetworkQuality}
     * @deprecated since 3.45 and will be deleted in 3.51, use onNetworkQuality{@link #IRTCRoomEventHandler#onNetworkQuality} instead.
     */
    NetworkQuality local_tx_quality;
    /**
     * @locale zh
     * @brief 所属用户的媒体流下行网络质量，详见 NetworkQuality{@link #NetworkQuality}
     * @deprecated since 3.36 and will be deleted in 3.51, use onNetworkQuality{@link #IRTCRoomEventHandler#onNetworkQuality} instead.
     */
    /**
     * @locale en
     * @brief The downlink network quality of the media stream belongs to the user. See NetworkQuality{@link #NetworkQuality}
     * @deprecated since 3.45 and will be deleted in 3.51, use onNetworkQuality{@link #IRTCRoomEventHandler#onNetworkQuality} instead.
     */
    NetworkQuality local_rx_quality;
    /**
     * @locale zh
     * @brief 所属用户的媒体流是否为屏幕流。你可以知道当前统计数据来自主流还是屏幕流。
     */
    /**
     * @locale en
     * @brief Whether the media stream belongs to the user is a screen stream. You can know whether the current statistics come from mainstream or screen stream.
     */
    bool is_screen;
};

/**
 * @locale zh
 * @type keytype
 * @brief 用户订阅的远端音/视频流统计信息以及网络状况，统计周期为 2s 。  <br>
 *        订阅远端用户发布音/视频流成功后，SDK 会周期性地通过 `onRemoteStreamStats`<br>
 *        通知本地用户订阅的远端音/视频流在此次统计周期内的接收状况。此数据结构即为回调给本地用户的参数类型。  
 */
/**
 * @locale en
 * @type keytype
 * @brief The remote audio/video stream statistics and network status subscribed by the user, with a reference period of 2s. <br>
 *         After the remote user subscribed to successfully publish the audio/video stream, the SDK will periodically notify local users through `onRemoteStreamStats`<br>
 *         The reception status of the remote audio/video stream subscribed during this reference period. This data structure is the type of parameter that is called back to the local user. 
 */
struct RemoteStreamStats {
    /**
     * @locale zh
     * @brief 用户 ID 。音/视频来源的远端用户 ID 。  
     */
    /**
     * @locale en
     * @brief User ID. The remote user ID of the audio source. 
     */
    const char* uid;
    /**
     * @locale zh
     * @brief 远端音频流的统计信息，详见 RemoteAudioStats{@link #RemoteAudioStats}
     */
    /**
     * @locale en
     * @brief For statistics on remote audio streams. See RemoteAudioStats{@link #RemoteAudioStats}
     */
    RemoteAudioStats audio_stats;
    /**
     * @locale zh
     * @brief 远端视频流的统计信息，详见 RemoteVideoStats{@link #RemoteVideoStats}
     */
    /**
     * @locale en
     * @brief For statistics on remote video streams. See RemoteVideoStats{@link #RemoteVideoStats}
     */
    RemoteVideoStats video_stats;
    /**
     * @locale zh
     * @brief 所属用户的媒体流上行网络质量，详见 NetworkQuality{@link #NetworkQuality}
     * @deprecated since 3.36 and will be deleted in 3.51, use onNetworkQuality{@link #IRTCRoomEventHandler#onNetworkQuality} instead.
     */
    /**
     * @locale en
     * @brief For the media stream uplink network quality of the user you belong to. See NetworkQuality{@link #NetworkQuality}
     * @deprecated since 3.45 and will be deleted in 3.51, use onNetworkQuality{@link #IRTCRoomEventHandler#onNetworkQuality} instead.
     */
    NetworkQuality remote_tx_quality;
    /**
     * @locale zh
     * @brief 所属用户的媒体流下行网络质量，详见 NetworkQuality{@link #NetworkQuality}
     * @deprecated since 3.36 and will be deleted in 3.51, use onNetworkQuality{@link #IRTCRoomEventHandler#onNetworkQuality} instead.
     */
    /**
     * @locale en
     * @brief The downlink network quality of the media stream belongs to the user. See NetworkQuality{@link #NetworkQuality}
     * @deprecated since 3.45 and will be deleted in 3.51, use onNetworkQuality{@link #IRTCRoomEventHandler#onNetworkQuality} instead.
     */
    NetworkQuality remote_rx_quality;
    /**
     * @locale zh
     * @brief 所属用户的媒体流是否为屏幕流。你可以知道当前统计数据来自主流还是屏幕流。
     */
    /**
     * @locale en
     * @brief Whether the media stream belongs to the user is a screen stream. You can know whether the current statistics come from mainstream or screen stream.
     */
    bool is_screen;
};

/**
 * @locale zh
 * @type keytype
 * @brief 音视频质量反馈问题类型
 */
/**
 * @locale en
 * @type keytype
 * @brief  Audio & video quality feedback problem
 */
enum ProblemFeedbackOption : uint64_t {
    /**
     * @locale zh
     * @brief 没有问题
     */
    /**
     * @locale en
     * @brief Every thing is OK.
     */
    kProblemFeedbackOptionNone = 0,
    /**
     * @locale zh
     * @brief 其他问题
     */
    /**
     * @locale en
     * @brief Issues not included in the list
     */
    kProblemFeedbackOptionOtherMessage = (1ULL << 0),
    /**
     * @locale zh
     * @brief 连接失败
     */
    /**
     * @locale en
     * @brief Connection failed
     */
    kProblemFeedbackOptionDisconnected = (1ULL << 1),
    /**
     * @locale zh
     * @brief 耳返延迟大
     */
    /**
     * @locale en
     * @brief High latency for the ear monitor
     */
    kProblemFeedbackOptionEarBackDelay = (1ULL << 2),

    /**
     * @locale zh
     * @brief 本端有杂音
     */
    /**
     * @locale en
     * @brief Noise on the local end
     */
    kProblemFeedbackOptionLocalNoise = (1ULL << 10),
    /**
     * @locale zh
     * @brief 本端声音卡顿
     */
    /**
     * @locale en
     * @brief Audio stall on the local end
     */
    kProblemFeedbackOptionLocalAudioLagging = (1ULL << 11),
    /**
     * @locale zh
     * @brief 本端无声音
     */
    /**
     * @locale en
     * @brief No sound on the local end
     */
    kProblemFeedbackOptionLocalNoAudio = (1ULL << 12),
    /**
     * @locale zh
     * @brief 本端声音大/小
     */
    /**
     * @locale en
     * @brief Too little/loud sound on the local end
     */
    kProblemFeedbackOptionLocalAudioStrength = (1ULL << 13),
    /**
     * @locale zh
     * @brief 本端有回声
     */
    /**
     * @locale en
     * @brief Echo noise on the local end
     */
    kProblemFeedbackOptionLocalEcho = (1ULL << 14),
    /**
     * @locale zh
     * @brief 本端视频模糊
     */
    /**
     * @locale en
     * @brief Unclear video on the local end
     */
    kProblemFeedbackOptionLocalVideoFuzzy = (1ULL << 24),
    /**
     * @locale zh
     * @brief 本端音视频不同步
     */
    /**
     * @locale en
     * @brief Audio & video out of sync on the local end
     */
    kProblemFeedbackOptionLocalNotSync = (1ULL << 25),
    /**
     * @locale zh
     * @brief 本端视频卡顿
     */
    /**
     * @locale en
     * @brief Video stall on the local end
     */
    kProblemFeedbackOptionLocalVideoLagging = (1ULL << 26),
    /**
     * @locale zh
     * @brief 本端无画面
     */
    /**
     * @locale en
     * @brief No picture on the local end
     */
    kProblemFeedbackOptionLocalNoVideo = (1ULL << 27),

    /**
     * @locale zh
     * @brief 远端有杂音
     */
    /**
     * @locale en
     * @brief Noise on the remote end
     */
    kProblemFeedbackOptionRemoteNoise = (1ULL << 37),
    /**
     * @locale zh
     * @brief 远端声音卡顿
     */
    /**
     * @locale en
     * @brief Audio stall on the remote end
     */
    kProblemFeedbackOptionRemoteAudioLagging = (1ULL << 38),
    /**
     * @locale zh
     * @brief 远端无声音
     */
    /**
     * @locale en
     * @brief No sound on the remote end
     */
    kProblemFeedbackOptionRemoteNoAudio = (1ULL << 39),
    /**
     * @locale zh
     * @brief 远端声音大/小
     */
    /**
     * @locale en
     * @brief Too little/loud sound on the remote end
     */
    kProblemFeedbackOptionRemoteAudioStrength = (1ULL << 40),
    /**
     * @locale zh
     * @brief 远端有回声
     */
    /**
     * @locale en
     * @brief Echo noise on the remote end
     */
    kProblemFeedbackOptionRemoteEcho = (1ULL << 41),

    /**
     * @locale zh
     * @brief 远端视频模糊
     */
    /**
     * @locale en
     * @brief Unclear video on the remote end
     */
    kProblemFeedbackOptionRemoteVideoFuzzy = (1ULL << 51),
    /**
     * @locale zh
     * @brief 远端音视频不同步
     */
    /**
     * @locale en
     * @brief Audio & video out of sync on the remote end
     */
    kProblemFeedbackOptionRemoteNotSync = (1ULL << 52),
    /**
     * @locale zh
     * @brief 远端视频卡顿
     */
    /**
     * @locale en
     * @brief Video stall on the remote end
     */
    kProblemFeedbackOptionRemoteVideoLagging = (1ULL << 53),
    /**
     * @locale zh
     * @brief 远端无画面
     */
    /**
     * @locale en
     * @brief No picture on the remote end
     */
    kProblemFeedbackOptionRemoteNoVideo = (1ULL << 54),
};

/**
 * @locale zh
 * @type keytype
 * @brief 音视频质量反馈的房间信息
 */
/**
 * @locale en
 * @type keytype
 * @brief Room information for audio & video quality feedback
 */
struct ProblemFeedbackRoomInfo {
    /**
     * @locale zh
     * @brief 房间 ID。
     */
    /**
     * @locale en
     * @brief Room ID.
     */
    const char* room_id = nullptr;

    /**
     * @locale zh
     * @brief 本地用户 ID。
     */
    /**
     * @locale en
     * @brief The ID of the  local user.
     */
    const char* user_id = nullptr;
};

/**
 * @locale zh
 * @type keytype
 * @brief 音视频质量反馈的信息
 */
/**
 * @locale en
 * @type keytype
 * @brief Information for audio & video quality feedback
 */
struct ProblemFeedbackInfo {
    /**
     * @locale zh
     * @brief 预设问题以外的其他问题的具体描述。
     */
    /**
     * @locale en
     * @brief Specific description of problems other than the preset problem.
     */
    const char* problem_desc = nullptr;

    /**
     * @locale zh
     * @type keytype
     * @brief 音视频质量反馈的房间信息。查看 ProblemFeedbackRoomInfo{@link #ProblemFeedbackRoomInfo}。
     */
    /**
     * @locale en
     * @type keytype
     * @brief Room information for audio & video quality feedback. See ProblemFeedbackRoomInfo{@link #ProblemFeedbackRoomInfo}.
     */
    ProblemFeedbackRoomInfo* room_info = nullptr;
    /**
     * @locale zh
     * @type keytype
     * @brief `FeedbackRoomInfo` 的数组长度。
     */
    /**
     * @locale en
     * @type keytype
     * @brief The length of `FeedbackRoomInfo`.
     */
    int room_info_count = 0;
};

/**
 * @locale zh
 * @type keytype
 * @brief 自定义加密类型  
 */
/**
 * @locale en
 * @type keytype
 * @brief  Custom encryption type   
 */
enum EncryptType {
    /**
     * @locale zh
     * @brief 不使用内置加密。默认值。
     */
    /**
     * @locale en
     * @brief Built-in encryption is not used. Default value.
     */
    kEncryptTypeCustomize = 0,
    /**
     * @locale zh
     * @brief AES-128-CBC 加密算法  
     */
    /**
     * @locale en
     * @brief AES-128-CBC  encryption algorithm 
     */
    kEncryptTypeAES128CBC = 1,
    /**
     * @locale zh
     * @brief AES-256-CBC 加密算法  
     */
    /**
     * @locale en
     * @brief AES-256-CBC  encryption algorithm 
     */
    kEncryptTypeAES256CBC = 2,
    /**
     * @locale zh
     * @brief AES-128-ECB 加密算法  
     */
    /**
     * @locale en
     * @brief AES-128-ECB  encryption algorithm 
     */
    kEncryptTypeAES128ECB = 3,
    /**
     * @locale zh
     * @brief AES-256-ECB 加密算法  
     */
    /**
     * @locale en
     * @brief AES-256-ECB  encryption algorithm 
     */
    kEncryptTypeAES256ECB = 4
};

/**
 * @locale zh
 * @type callback
 * @brief 加密/解密处理函数<br>
 * 注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。
 */
/**
 * @locale en
 * @type callback
 * @brief  Encryption/decryption handler<br>
 * Note: Callback functions are thrown synchronously in a non-UI thread within the SDK. Therefore, you must not perform any time-consuming operations or direct UI operations within the callback function, as this may cause the app to crash.
 */
class IEncryptHandler {
public:
    /**
     * @locale zh
     * @hidden constructor/destructor
     * @brief 析构函数
     */
    /**
     * @locale en
     * @hidden constructor/destructor
     * @brief  Destructor
     */
    virtual ~IEncryptHandler() {
    }
    /**
     * @locale zh
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
     *        + 0：丢弃该帧  
     * @note 
     *        + 使用此接口进行自定义加密前，你必须先设置自定义加密方式，参看 `setCustomizeEncryptHandler`。<br>
     *        + 使用 onDecryptData{@link #onDecryptData} 对已加密的音视频帧数据进行解密。<br>
     *        + 返回的数据大小应控制在原始数据的 90% ~ 120% 范围以内，不然将被丢弃。
     */
    /**
     * @locale en
     * @type api
     * @region  encryption
     * @brief Custom encryption.   <br>
     *        Encrypts audio & video frame data before transmission using the custom encryption method set.<br>
     *        Encryption of the original audio and video frames is currently not available.
     * @param data Raw audio & video frame data
     * @param length Length of raw audio & video frame data
     * @param buf Encrypted data buffer available for writing
     * @param buf_len Size of encrypted data buffer available for writing
     * @return Encrypted data   <br>
     *         + ≥ 0: size of data actually written to the buffer after encryption <br>
     *         + 0: Discard the frame 
     * @note  
     *         + Before using this interface for custom encryption, you must first set the custom encryption method. See `setCustomizeEncryptHandler`.<br>
     *         + Use onDecryptData{@link #onDecryptData} to decrypt encrypted audio & video frame data.<br>
     *         + The returned data size should be controlled within 90%~ 120% of the original data source, otherwise it will be discarded.
     */
    virtual unsigned int onEncryptData(
            const unsigned char* data, unsigned int length, unsigned char* buf, unsigned int buf_len) = 0;

    /**
     * @locale zh
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
     *        + 0：丢弃该帧  
     * @note 
     *        + 使用此接口进行解密前，你必须先设定解密方式，参看 `setCustomizeEncryptHandler`。<br>
     *        + 返回的数据大小应控制在原始数据的 90% ~ 120% 范围以内，不然将被丢弃。
    */
   /**
     * @locale en
     * @type api
     * @region  encryption
     * @brief Custom decryption.   <br>
     *         Decrypts custom encrypted audio & video frame data. For custom encryption, see onEncryptData{@link #IEncryptHandler#onEncryptData}.
     * @param data Raw audio & video frame data
     * @param length Length of raw audio & video frame data
     * @param buf Encrypted data buffer available for writing
     * @param buf_len Size of encrypted data buffer available for writing
     * @return Encrypted data   <br>
     *         + ≥ 0: size of data actually written to the buffer after encryption <br>
     *         + 0: Discard the frame 
     * @note  
     *         + Before using this interface to decrypt, you must first set the decryption method. See `setCustomizeEncryptHandler`.<br>
     *         + The returned data size should be controlled within 90%~ 120% of the original data source, otherwise it will be discarded.
    */
    virtual unsigned int onDecryptData(
            const unsigned char* data, unsigned int length, unsigned char* buf, unsigned int buf_len) = 0;
};

/**
 * @locale zh
 * @type keytype
 * @region 房间管理
 * @brief 用户信息
 */
/**
 * @locale en
 * @type keytype
 * @region  room management
 * @brief  User information
 */
struct RtcUser {
    /**
     * @locale zh<br>
     * 用户 id
     */
    /**
     * @locale en<br>
     * User id
     */
    const char* user_id;
    /**
     * @locale zh<br>
     * 元数据
     */
    /**
     * @locale en<br>
     * Metadata
     */
    const char* meta_data;
};

/**
 * @locale zh
 * @type keytype
 * @region 房间管理
 * @brief 首帧发送状态
 */
/**
 * @locale en
 * @type keytype
 * @region  room management
 * @brief  First frame sending status
 */
enum FirstFrameSendState {
    /**
     * @locale zh
     * @brief 发送中
     */
    /**
     * @locale en
     * @brief Sending
     */
    kFirstFrameSendStateSending = 0,
    /**
     * @locale zh
     * @brief 发送成功
     */
    /**
     * @locale en
     * @brief Sent successfully
     */
    kFirstFrameSendStateSent = 1,
    /**
     * @locale zh
     * @brief 发送失败
     */
    /**
     * @locale en
     * @brief Send failed
     */
    kFirstFrameSendStateEnd = 2,
};

/**
 * @locale zh
 * @type keytype
 * @region 房间管理
 * @brief 首帧播放状态
 */
/**
 * @locale en
 * @type keytype
 * @region  room management
 * @brief  First frame playback status
 */
enum FirstFramePlayState {
    /**
     * @locale zh
     * @brief 播放中
     */
    /**
     * @locale en
     * @brief Playing
     */
    kFirstFramePlayStatePlaying = 0,
    /**
     * @locale zh
     * @brief 播放成功
     */
    /**
     * @locale en
     * @brief Play success
     */
    kFirstFramePlayStatePlayed = 1,
    /**
     * @locale zh
     * @brief 播放失败
     */
    /**
     * @locale en
     * @brief Play failed
     */
    kFirstFramePlayStateEnd = 2,
};

/**
 * @locale zh
 * @type keytype
 * @brief 音视频流的发送/播放状态
 */
/**
 * @locale en
 * @type keytype
 * @brief Transmission/Playback state of the media stream
 */
enum MuteState {
    /**
     * @locale zh
     * @brief 发送
     */
    /**
     * @locale en
     * @brief Enable
     */
    kMuteStateOff = 0,
    /**
     * @locale zh
     * @brief 停止发送
     */
    /**
     * @locale en
     * @brief Disable
     */
    kMuteStateOn = 1,
};

/**
 * @locale zh
 * @type keytype
 * @brief 流属性
 */
/**
 * @locale en
 * @type keytype
 * @brief Stream type
 */
enum StreamIndex {
    /**
     * @locale zh
     * @brief 主流。包括：<br>
     *        + 由摄像头/麦克风通过内部采集机制，采集到的视频/音频; <br>
     *        + 通过自定义采集，采集到的视频/音频。
     */
    /**
     * @locale en
     * @brief Mainstream, including: <br>
     *       + Video/audio captured by the the camera/microphone using internal capturing; <br>
     *       + Video/audio captured by custom method.
     */
    kStreamIndexMain = 0,
    /**
     * @locale zh
     * @brief 屏幕流。屏幕共享时共享的视频流，或来自声卡的本地播放音频流。
     */
    /**
     * @locale en
     * @brief Screen-sharing stream. Video/Audio streams for screen sharing.
     */
    kStreamIndexScreen = 1,
    /**
     * @hidden for internal use only
     */
    kStreamIndex3rd,
    /**
     * @hidden for internal use only
     */
    kStreamIndex4th,
    /**
     * @hidden for internal use only
     */
    kStreamIndex5th,
    /**
     * @hidden for internal use only
     */
    kStreamIndex6th,
    /**
     * @hidden for internal use only
     */
    kStreamIndex7th,
    /**
     * @hidden for internal use only
     */
    kStreamIndexMax,
};

/**
 * @locale zh
 *  @valid since 3.56
 *  @type keytype
 *  @brief 流聚合策略
 */
/**
 * @locale en
 *  @valid since 3.56
 *  @type keytype
 *  @brief stream aggregation strategy
 */
enum AggregationOption {
    /**
   * @locale zh
   * @brief 流聚合向下取值  （默认策略）
   */
    /**
   * @locale en
   * @brief Stream aggregation with the lowest resolution.(Default Strategy)
   */
    kAggregationOptionMin = 0,
    /**
   * @locale zh
   * @brief 流聚合向上取值
   */
    /**
   * @locale en
   * @brief Stream aggregation with the highest resolution.
   */
    kAggregationOptionMax = 1,
    /**
   * @locale zh
   * @brief 流聚合按比例取值，比例相同时，向下取值
   */
    /**
   * @locale en
   * @brief Stream aggregation according to the proportions, and when the proportions are the same, it takes the lowest resolution.
   */
    kAggregationOptionMajority = 2,

};

/**
 * @locale zh
 * @type keytype
 * @brief 远端流信息
 */
/**
 * @locale en
 * @type keytype
 * @brief Information about the remote stream
 */
struct RemoteStreamKey {
   /**
     * @locale zh
     * @brief 媒体流所在房间的房间 ID。<br>
     *        如果此媒体流是通过 `startForwardStreamToRooms` 转发到你所在房间的媒体流时，你应将房间 ID 设置为你所在的房间 ID。
     */
    /**
     * @locale en
     * @brief The room ID of the media stream. <br>
     *        If the media stream is the stream forwarded by `startForwardStreamToRooms`, you must set the roomID to the room ID of the target room.
     */
    const char* room_id;
    /**
     * @locale zh
     * @brief 用户 ID
     */
    /**
     * @locale en
     * @brief The ID of the user who published the stream.
     */
    const char* user_id;
    /**
     * @locale zh
     * @brief 流属性，主流或屏幕流。参看 StreamIndex{@link #StreamIndex}
     */
    /**
     * @locale en
     * @brief Stream type. See StreamIndex{@link #StreamIndex}
     */
    StreamIndex stream_index;
};

/**
 * @locale zh
 * @type keytype
 * @brief 本地录制文件的存储格式
 */
/**
 * @locale en
 * @type keytype
 * @brief  Storage format of locally recorded files
 */
enum RecordingFileType {
    /**
     * @locale zh
     * @brief aac 格式文件
     */
    /**
     * @locale en
     * @brief Aac  format file
     */
    kRecordingFileTypeAAC = 0,
    /**
     * @locale zh
     * @brief mp4 格式文件
     */
    /**
     * @locale en
     * @brief Mp4  format file
     */
    kRecordingFileTypeMP4 = 1,
};

/**
 * @locale zh
 * @type keytype
 * @brief 本地录制的状态
 */
/**
 * @locale en
 * @type keytype
 * @brief  Status of local recording
 */
enum RecordingState {
    /**
     * @locale zh
     * @brief 录制异常
     */
    /**
     * @locale en
     * @brief Recording exception
     */
    kRecordingStateError = 0,
    /**
     * @locale zh
     * @brief 录制进行中
     */
    /**
     * @locale en
     * @brief Recording in progress
     */
    kRecordingStateProcessing = 1,
    /**
     * @locale zh
     * @brief 录制文件保存成功，调用 `stopFileRecording` 结束录制之后才会收到该状态码。
     */
    /**
     * @locale en
     * @brief If the recording file is saved successfully, you will not receive the status code until you call `stopFileRecording` to end the recording.
     */
    kRecordingStateSuccess = 2,
};

/**
 * @locale zh
 * @type keytype
 * @brief 本地录制的错误码
 */
/**
 * @locale en
 * @type keytype
 * @brief  Error code for local recording
 */
enum RecordingErrorCode {
    /**
     * @locale zh
     * @brief 录制正常
     */
    /**
     * @locale en
     * @brief Recording normal
     */
    kRecordingErrorCodeOk = 0,
    /**
     * @locale zh
     * @brief 没有文件写权限
     */
    /**
     * @locale en
     * @brief No file write permissions
     */
    kRecordingErrorCodeNoPermission = -1,
    /**
     * @locale zh
     * @brief 当前版本 SDK 不支持本地录制功能，请联系技术支持人员
     */
    /**
     * @locale en
     * @brief The current version SDK does not support local recording, please contact technical support
     */
    kRecordingErrorCodeNotSupport = -2,
    /**
     * @locale zh
     * @brief 其他异常
     */
    /**
     * @locale en
     * @brief Other anomalies
     */
    kRecordingErrorCodeOther = -3,
};

/**
 * @locale zh
 * @type keytype
 * @brief 本地录制进度
 */
/**
 * @locale en
 * @type keytype
 * @brief  Local recording progress
 */
struct RecordingProgress {
    /**
     * @locale zh
     * @brief 当前文件的累计录制时长，单位：毫秒
     */
    /**
     * @locale en
     * @brief The cumulative recording time of the current file, in milliseconds
     */
    unsigned long long duration;
    /**
     * @locale zh
     * @brief 当前录制文件的大小，单位：byte
     */
    /**
     * @locale en
     * @brief The size of the currently recorded file in bytes
     */
    unsigned long long file_size;
};

/**
 * @locale zh
 * @type keytype
 * @brief 本地录制的详细信息
 */
/**
 * @locale en
 * @type keytype
 * @brief  Details of local recording
 */
struct RecordingInfo {
    /**
     * @locale zh
     * @brief 录制文件的绝对路径，包含文件名和文件后缀
     */
    /**
     * @locale en
     * @brief The absolute path of the recorded file, including the file name and file suffix
     */
    const char* file_path;
    /**
     * @locale zh
     * @brief 录制文件的视频编码类型，参看 VideoCodecType{@link #VideoCodecType}
     */
    /**
     * @locale en
     * @brief For the video encoding type of the recorded file. See VideoCodecType{@link #VideoCodecType}
     */
    VideoCodecType video_codec_type;
    /**
     * @locale zh
     * @brief 录制视频的宽，单位：像素。纯音频录制请忽略该字段
     */
    /**
     * @locale en
     * @brief The width of the recorded video, in pixels. Please ignore this field for audio-only recording
     */
    int width;
    /**
     * @locale zh
     * @brief 录制视频的高，单位：像素。纯音频录制请忽略该字段
     */
    /**
     * @locale en
     * @brief The height of the recorded video, the unit: pixels. Please ignore this field for audio-only recording
     */
    int height;
};

/**
 * @locale zh
 * @type keytype
 * @brief 本地录制参数配置
 */
/**
 * @locale en
 * @type keytype
 * @brief  Local recording parameter configuration
 */
struct RecordingConfig {
    /**
     * @locale zh
     * @brief 录制文件保存的绝对路径，需精确到文件夹，文件名由 RTC 自动生成。你需要确保对该路径具有读写权限。
     */
    /**
     * @locale en
     * @brief The absolute folder path to save the recording file.The filename will be generated by RTC. You need to ensure that you have read and write permissions to this path.
     */
    const char* dir_path;
    /**
     * @locale zh
     * @brief 录制存储文件格式，参看 RecordingFileType{@link #RecordingFileType}
     */
    /**
     * @locale en
     * @brief Recording stored file format. See RecordingFileType{@link #RecordingFileType}
     */
    RecordingFileType file_type;
};

/**
 * @locale zh
 * @type keytype
 * @brief 定义linux用户的用户功能  
 */
/**
 * @locale en
 * @type keytype
 * @brief Define user functions for linux users   
 */
enum UserWorkerType {
    /**
     * @locale zh
     * @brief 正常用户，没有任何特殊属性  
     */
    /**
     * @locale en
     * @brief Normal user, no special attributes   
     */
    kUserWorkerTypeNormal = 0,
    /**
     * @locale zh
     * @brief 用户支持SIP流，信令只下发SIP流  
     */
    /**
     * @locale en
     * @brief User supports SIP flow, signaling only sends SIP flow   
     */
    kUserWorkerTypeSupportSip = (1 << 0),
    /**
     * @locale zh
     * @brief 用户支持屏幕流的bytevc1到H264转码  
     */
    /**
     * @locale en
     * @brief User supports bytevc1 to H264 transcoding of screen streams   
     */
    kUserWorkerTypeByteVc1Transcoder = (1 << 1),
    /**
     * @locale zh
     * @brief 用户需要信令服务器下发全量的用户列表和回调函数  
     */
    /**
     * @locale en
     * @brief The user needs the signaling server to send a full number of user lists and callback functions   
     */
    kUserWorkerTypeNeedUserListAndCb = (1 << 2),
    /**
     * @locale zh
     * @brief 用户需要在房间进入多人模式时获取房间内所有流的相关回调  
     */
    /**
     * @locale en
     * @brief The user needs to get relevant callbacks for all streams in the room when the room enters multiplayer mode   
     */
    kUserWorkerTypeNeedStreamCallBack = (1 << 3),
    /**
     * @locale zh
     * @brief 用户选择设置不支持音频选路功能  
     */
    /**
     * @locale en
     * @brief User sets not support audioselection   
     */
    kUserWorkerTypeAudioSelectionExemption = (1 << 4),
};

/**
 * @locale zh
 * @type keytype
 * @brief 音视频同步状态
 */
/**
 * @locale en
 * @type keytype
 * @brief A/V synchronization states
 */
enum AVSyncState {
    /**
     * @locale zh
     * @brief 音视频开始同步
     */
    /**
     * @locale en
     * @brief A/V synchronization begins.
     */
    kAVSyncStateAVStreamSyncBegin = 0,
    /**
     * @locale zh
     * @brief 音视频同步过程中音频移除，但不影响当前的同步关系
     */
    /**
     * @locale en
     * @brief The publisher stops publishing audio stream during the synchronization, which does not affect the sync relationship.
     */
    kAVSyncStateAudioStreamRemove,
    /**
     * @locale zh
     * @brief 音视频同步过程中视频移除，但不影响当前的同步关系
     */
    /**
     * @locale en
     * @brief The publisher stops publishing audio stream during the synchronization, which does not affect the sync relationship.
     */
    kAVSyncStateVdieoStreamRemove,
    /**
     * @locale zh
     * @hidden for internal use only
     * @brief 订阅端设置同步  
     */
    /**
     * @locale en
     * @hidden for internal use only
     * @brief subscriber settings synchronization  
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
 * @locale zh
 * @type keytype
 * @brief 媒体流信息同步的流类型
 */
/**
 * @locale en
 * @type keytype
 * @brief  Stream type for media stream information synchronization
 */
enum SyncInfoStreamType {
    /**
     * @locale zh
     * @brief 音频流
     */
    /**
     * @locale en
     * @brief Audio stream
     */
    kSyncInfoStreamTypeAudio = 0
};

/**
 * @locale zh
 * @type keytype
 * @brief 媒体流信息同步的相关配置
 */
/**
 * @locale en
 * @type keytype
 * @brief  Configuration related to media stream information synchronization
 */
struct StreamSycnInfoConfig {
    /**
     * @locale zh
     * @brief 流属性，主流或屏幕流。见 StreamIndex{@link #StreamIndex}
     */
    /**
     * @locale en
     * @brief Stream properties, mainstream or screen streams. See StreamIndex{@link #StreamIndex}
     */
    StreamIndex stream_index;
    /**
     * @locale zh
     * @brief 消息发送的重复次数，取值范围是 [0,25]，建议设置为 [3,5]。
     */
    /**
     * @locale en
     * @brief The number of duplicates sent by the message, the value range is  [0,25], it is recommended to set it to [3,5].
     */
    int repeat_count;
    /**
     * @locale zh
     * @brief 媒体流信息同步的流类型，见 SyncInfoStreamType{@link #SyncInfoStreamType}
     */
    /**
     * @locale en
     * @brief Stream types for media stream information synchronization. See SyncInfoStreamType{@link #SyncInfoStreamType}
     */
    SyncInfoStreamType stream_type;
};

/**
 * @locale zh
 * @type keytype
 * @brief 媒体流跨房间转发的目标房间的相关信息
 */
/**
 * @locale en
 * @type keytype
 * @brief Information of the rooms where you want to relay the media stream to
 */
struct ForwardStreamInfo {
    /**
     * @locale zh
     * @brief 使用转发目标房间 roomID 和 UserID 生成 Token。<br>
     *        测试时可使用控制台生成临时 Token，正式上线需要使用密钥 SDK 在你的服务端生成并下发 Token。<br>
     *        如果 Token 无效，转发失败。
     */
    /**
     * @locale en
     * @brief RoomId and UserId are required to generate the Token to forward media streams to the room.<br>
     *        During developing and testing, you can use temporary tokens generated on the console. At the production stage, Tokens are generated by the token generating application deployed on your server.<br>
     *        Forwarding will fail if the token is invalid.
     */
    const char* token;
    /**
     * @locale zh
     * @brief 跨间转发媒体流过程中目标房间 ID
     */
    /**
     * @locale en
     * @brief ID of the room where the media stream aims to relay to
     */
    const char* room_id;
};

/**
 * @locale zh
 * @type keytype
 * @brief 媒体流跨房间转发的目标房间的相关信息
 */
/**
 * @locale en
 * @type keytype
 * @brief Information of the rooms where you want to relay the media stream to
 */
struct ForwardStreamConfiguration {
    /**
     * @locale zh
     * @brief 目标房间信息，数组中的每个元素包含一个房间的信息。
     */
    /**
     * @locale en
     * @brief Information of the rooms where you want to relay the media stream to
     */
    ForwardStreamInfo* forward_stream_dests = nullptr;
    /**
     * @locale zh
     * @brief 目标房间数量。媒体流同时转发的目标房间数量建议小于等于 4 个。
     */
    /**
     * @locale en
     * @brief Number of the rooms where you want to relay the media stream<br>
     *        We recommend that the number is not higher than 4.
     */
    int dest_count = 0;
};

/**
 * @locale zh
 * @type keytype
 * @brief 媒体流跨房间转发状态
 */
/**
 * @locale en
 * @type keytype
 * @brief The state of the relaying for each room
 */
enum ForwardStreamState {
    /**
     * @locale zh
     * @brief 空闲状态<br>
     *        + 成功调用 `stopForwardStreamToRooms` 后，所有目标房间为空闲状态。<br>
     *        + 成功调用 `updateForwardStreamToRooms` 减少目标房间后，本次减少的目标房间为空闲状态。
     */
    /**
     * @locale en
     * @brief Idle<br>
     *        + States of all the rooms turns to idle after you call `stopForwardStreamToRooms`.<br>
     *        + States of the rooms turns to idle that you call `updateForwardStreamToRooms` to remove.
     */
    kForwardStreamStateIdle = 0,
    /**
     * @locale zh
     * @brief 开始转发<br>
     *        + 调用 `startForwardStreamToRooms` 成功向所有房间开始转发媒体流后，返回此状态。<br>
     *        + 调用 `updateForwardStreamToRooms` 后，成功向新增目标房间开始转发媒体流后，返回此状态。
     */
    /**
     * @locale en
     * @brief Start relaying.<br>
     *        + State of the rooms turn to this state after the relaying starts successfully by calling `startForwardStreamToRooms`.<br>
     *        + State of the rooms added by calling `updateForwardStreamToRooms` turn to this state after the relaying start successfully.
     */
    kForwardStreamStateSuccess = 1,
    /**
     * @locale zh
     * @brief 转发失败，失败详情参考 ForwardStreamError{@link #ForwardStreamError}<br>
     *        调用 `startForwardStreamToRooms` 或 `updateForwardStreamToRooms` 后，如遇转发失败，返回此状态。
     */
    /**
     * @locale en
     * @brief Relay fails. Refer to ForwardStreamError{@link #ForwardStreamError} for more information for more information.<br>
     *        Once the relaying fails, state of the room turns to this state after calling `startForwardStreamToRooms` or `updateForwardStreamToRooms`.
     */
    kForwardStreamStateFailure = 2,
};

/**
 * @locale zh
 * @type keytype
 * @brief 媒体流跨房间转发过程中抛出的错误码
 */
/**
 * @locale en
 * @type keytype
 * @brief Error codes during the relaying
 */
enum ForwardStreamError {
    /**
     * @locale zh
     * @brief 正常
     */
    /**
     * @locale en
     * @brief Normal
     */
    kForwardStreamErrorOK = 0,
    /**
     * @locale zh
     * @brief 参数异常
     */
    /**
     * @locale en
     * @brief Invalid argument
     */
    kForwardStreamErrorInvalidArgument = 1201,
    /**
     * @locale zh
     * @brief token 错误
     */
    /**
     * @locale en
     * @brief Invalid token
     */
    kForwardStreamErrorInvalidToken = 1202,
    /**
     * @locale zh
     * @brief 服务端异常
     */
    /**
     * @locale en
     * @brief Error returning from server
     */
    kForwardStreamErrorResponse = 1203,
    /**
     * @locale zh
     * @brief 目标房间有相同 user id 的用户加入，转发中断
     */
    /**
     * @locale en
     * @brief Relaying aborts for the reason of that a User with the same user ID as that of the publisher joins.
     */
    kForwardStreamErrorRemoteKicked = 1204,
    /**
     * @locale zh
     * @brief 服务端不支持转发功能
     */
    /**
     * @locale en
     * @brief Server denies.
     */
    kForwardStreamErrorNotSupport = 1205,
};

/**
 * @locale zh
 * @type keytype
 * @brief 媒体流跨房间转发事件
 */
/**
 * @locale en
 * @type keytype
 * @brief Events during the relaying
 */
enum ForwardStreamEvent {
    /**
     * @locale zh
     * @brief 本端与服务器网络连接断开，暂停转发。
     */
    /**
     * @locale en
     * @brief Relaying pauses for the reason of network disconnecting.
     */
    kForwardStreamEventDisconnected = 0,
    /**
     * @locale zh
     * @brief 本端与服务器网络连接恢复，转发服务连接成功。
     */
    /**
     * @locale en
     * @brief Relaying recovers from the disconnecting.
     */
    kForwardStreamEventConnected = 1,
    /**
     * @locale zh
     * @brief 转发中断。转发过程中，如果相同 user_id 的用户进入目标房间，转发中断。
     */
    /**
     * @locale en
     * @brief Relaying aborts for the reason of that a User with the same user ID as that of the publisher joins.
     */
    kForwardStreamEventInterrupt = 2,
    /**
     * @locale zh
     * @brief 目标房间已更新，由 `updateForwardStreamToRooms` 触发。
     */
    /**
     * @locale en
     * @brief Target room list updates after you call `updateForwardStreamToRooms`.
     */
    kForwardStreamEventDstRoomUpdated = 3,
    /**
     * @locale zh
     * @brief API 调用时序错误。例如，在调用 `startForwardStreamToRooms` 之前调用 `updateForwardStreamToRooms` 。
     */
    /**
     * @locale en
     * @brief Wrong API-calling order. For example, call `updateForwardStreamToRooms` before calling `startForwardStreamToRooms`.
     */
    kForwardStreamEventUnExpectAPICall = 4,
};

/**
 * @locale zh
 * @type keytype
 * @brief 跨房间转发媒体流过程中的不同目标房间的状态和错误信息
 */
/**
 * @locale en
 * @type keytype
 * @brief State and error for each room during relaying
 */
struct ForwardStreamStateInfo {
    /**
     * @locale zh
     * @brief 跨间转发媒体流过程中目标房间 ID
     */
    /**
     * @locale en
     * @brief ID of the room where the media stream aims to relay to
     */
    const char* room_id;
    /**
     * @locale zh
     * @brief 跨房间转发媒体流过程中该目标房间的状态，参看 ForwardStreamState{@link #ForwardStreamState}
     */
    /**
     * @locale en
     * @brief State of the room during relaying. Refer to ForwardStreamState{@link #ForwardStreamState} for more information.
     */
    ForwardStreamState state;
    /**
     * @locale zh
     * @brief 跨房间转发媒体流过程中该目标房间抛出的错误码，参看 ForwardStreamError{@link #ForwardStreamError}
     */
    /**
     * @locale en
     * @brief Error code from the room during relaying. Refer to ForwardStreamError{@link #ForwardStreamError} for more information.
     */
    ForwardStreamError error;
};

/**
 * @locale zh
 * @type keytype
 * @brief 跨房间转发媒体流过程中的不同目标房间发生的事件
 */
/**
 * @locale en
 * @type keytype
 * @brief Event from each room during relaying
 */
struct ForwardStreamEventInfo {
    /**
     * @locale zh
     * @brief 跨房间转发媒体流过程中的发生该事件的目标房间 ID<br>
     *        空字符串代表所有目标房间
     */
    /**
     * @locale en
     * @brief ID of the room where the media stream aims to relay to<br>
     *        An Empty string is for all rooms.
     */
    const char* room_id;
    /**
     * @locale zh
     * @brief 跨房间转发媒体流过程中该目标房间发生的事件，参看 ForwardStreamEvent{@link #ForwardStreamEvent}
     */
    /**
     * @locale en
     * @brief Event from the room during relaying. Refer to ForwardStreamEvent{@link #ForwardStreamEvent} for more information.
     */
    ForwardStreamEvent event;
};

/**
 * @locale zh
 * @type keytype
 * @brief 水印图片相对视频流的位置和大小。
 */
/**
 * @locale en
 * @type keytype
 * @brief Watermark's scaled coordinates and size, relative to the video stream.
 */
struct ByteWatermark {
    /**
     * @hidden currently not available
     */
    const char* url = nullptr;
    /**
     * @locale zh
     * @brief 水印图片相对视频流左上角的横向偏移与视频流宽度的比值，取值范围为 [0,1)。
     */
    /**
     * @locale en
     * @brief The watermark's horizontal offset from the upper left corner of the video stream to the video stream's width in range of [0,1).
     */
    float x;
    /**
     * @locale zh
     * @brief 水印图片相对视频流左上角的纵向偏移与视频流高度的比值，取值范围为 [0,1)。
     */
    /**
     * @locale en
     * @brief The watermark's vertical offset from the upper left corner of the video stream to the video stream's height in range of [0,1).
     */
    float y;
    /**
     * @locale zh
     * @brief 水印图片宽度与视频流宽度的比值，取值范围 [0,1)。
     */
    /**
     * @locale en
     * @brief The watermark's width to the video stream's width in range of [0,1).
     */
    float width;
    /**
     * @locale zh
     * @brief 水印图片高度与视频流高度的比值，取值范围为 [0,1)。
     */
    /**
     * @locale en
     * @brief The watermark height to the video stream's height in range of [0,1).
     */
    float height;
};

/**
 * @locale zh
 * @type keytype
 * @brief 水印参数
 */
/**
 * @locale en
 * @type keytype
 * @brief Watermark configurations
 */
struct RTCWatermarkConfig {
    /**
     * @locale zh
     * @type keytype
     * @brief 水印是否在视频预览中可见，默认可见。
     */
    /**
     * @locale en
     * @type keytype
     * @brief Whether the watermark is visible in preview. Its default value is `true`.
     */
    bool visible_in_preview = true;
    /**
     * @locale zh
     * @type keytype
     * @brief 横屏时的水印位置和大小，参看 ByteWatermark{@link #ByteWatermark}。
     */
    /**
     * @locale en
     * @type keytype
     * @brief Watermark's coordinates and size in landscape mode. See ByteWatermark{@link #ByteWatermark}.
     */
    ByteWatermark position_in_landscape_mode;
    /**
     * @locale zh
     * @type keytype
     * @brief 视频编码的方向模式为竖屏时的水印位置和大小，参看 ByteWatermark{@link #ByteWatermark}。
     */
    /**
     * @locale en
     * @type keytype
     * @brief Watermark's coordinates and size in portrait mode. See ByteWatermark{@link #ByteWatermark}.
     */
    ByteWatermark position_in_portrait_mode;
};

/**
 * @locale zh
 * @type keytype
 * @brief 设备的传输方式
 */
/**
 * @locale en
 * @type keytype
 * @brief Connection type of the audio device
 */
enum DeviceTransportType {
    /**
     * @locale zh
     * @brief 未知类型
     */
    /**
     * @locale en
     * @brief Unknown
     */
    kDeviceTransportTypeUnknown = 0,
    /**
     * @locale zh
     * @brief 系统内置
     */
    /**
     * @locale en
     * @brief Built-in device
     */
    kDeviceTransportTypeBuiltIn = 1,
    /**
     * @locale zh
     * @brief 未知模式蓝牙
     */
    /**
     * @locale en
     * @brief Unknown profile via a Bluetooth connection
     */
    kDeviceTransportTypeBlueToothUnknownMode = 2,
    /**
     * @locale zh
     * @brief 免提模式蓝牙
     */
    /**
     * @locale en
     * @brief Handsfree Profile(HFP) via a Bluetooth connection
     */
    kDeviceTransportTypeBlueToothHandsFreeMode = 3,
    /**
     * @locale zh
     * @brief 立体声模式蓝牙
     */
    /**
     * @locale en
     * @brief Advanced Audio Distribution Profile(A2DP) via a Bluetooth connection
     */
    kDeviceTransportTypeBlueToothStereoMode = 4,
    /**
     * @locale zh
     * @brief 显示器/电视机音频设备
     */
    /**
     * @locale en
     * @brief Speaker of the display or television
     */
    kDeviceTransportTypeDisplayAudio = 5,
    /**
     * @locale zh
     * @brief 虚拟设备
     */
    /**
     * @locale en
     * @brief Virtual sound card
     */
    kDeviceTransportTypeVirtual = 6,
    /**
     * @locale zh
     * @brief USB设备
     */
    /**
     * @locale en
     * @brief USB device
     */
    kDeviceTransportTypeUSB = 7,
    /**
     * @locale zh
     * @brief PCI设备
     */
    /**
     * @locale en
     * @brief PCI device
     */
    kDeviceTransportTypePCI = 8,
    /**
     * @locale zh
     * @brief AirPlay设备
     */
    /**
     * @locale en
     * @brief AirPlay device
     */
    kDeviceTransportTypeAirPlay = 9,
    /**
     * @locale zh
     * @brief 连续互通相机
     */
    /**
     * @locale en
     * @brief Continuity Camera (external iPhone camera)
     */
    kDeviceTransportTypeContinuityCamera = 100,
};

/**
 * @locale zh
 * @type keytype
 * @brief 音视频回路测试结果
 */
/**
 * @locale en
 * @type keytype
 * @brief Call test result
 */
enum class EchoTestResult {
    /**
     * @locale zh
     * @brief 接收到采集的音视频的回放，通话回路检测成功
     */
    /**
     * @locale en
     * @brief The playback of captured audio/video is received, test succeeds.
     */
    kTestSuccess = 0,
    /**
     * @locale zh
     * @brief 测试超过 60s 仍未完成，已自动停止
     */
    /**
     * @locale en
     * @brief Test is not completed after 60 seconds and has been stopped automatically.
     */
    kTestTimeout,
    /**
     * @locale zh
     * @brief 上一次测试结束和下一次测试开始之间的时间间隔少于 5s
     */
    /**
     * @locale en
     * @brief Less than 5s between the end of the last test and the start of the next test.
     */
    kTestIntervalShort,
    /**
     * @locale zh
     * @brief 音频采集异常
     */
    /**
     * @locale en
     * @brief Audio capture error
     */
    kAudioDeviceError,
    /**
     * @locale zh
     * @brief 视频采集异常
     */
    /**
     * @locale en
     * @brief Video capture error
     */
    kVideoDeviceError,
    /**
     * @locale zh
     * @brief 音频接收异常
     */
    /**
     * @locale en
     * @brief Audio reception error
     */
    kAudioReceiveError,
    /**
     * @locale zh
     * @brief 视频接收异常
     */
    /**
     * @locale en
     * @brief Video reception error
     */
    kVideoReceiveError,
    /**
     * @locale zh
     * @brief 内部错误，不可恢复
     */
    /**
     * @locale en
     * @brief Unrecoverable internal error
     */
    kInternalError
};

/**
 * @locale zh
 * @type keytype
 * @brief 音视频回路测试参数
 */
/**
 * @locale en
 * @type keytype
 * @brief Video/audio call test configurations
 */
struct EchoTestConfig {
    /**
     * @locale zh
     * @brief 用于渲染接收到的视频的视图
     */
    /**
     * @locale en
     * @brief View for rendering received video
     */
    void* view;
    /**
     * @locale zh
     * @brief 是否检测音频。检测设备为系统默认音频设备。  <br>
     *        + true：是  <br>
     *            - 若使用 SDK 内部采集，此时设备麦克风会自动开启，并在 audioPropertiesReportInterval 值大于 0 时触发 `onLocalAudioPropertiesReport` 回调，你可以根据该回调判断麦克风的工作状态  <br>
     *            - 若使用自定义采集，此时你需调用 pushExternalAudioFrame{@link #IRTCVideo#pushExternalAudioFrame} 将采集到的音频推送给 SDK  <br>
     *        + false：否  
     */
    /**
     * @locale en
     * @brief Whether to test audio. The device to be tested is the default audio device.  <br>
     *        + true: Yes  <br>
     *            - If you use internal capture, the device microphone will automatically turn on and `onLocalAudioPropertiesReport` will be triggered when the value of audioPropertiesReportInterval is set to greater than 0, from which you can judge the working status of the microphone.  <br>
     *            - If you choose custom capture, you also need to call pushExternalAudioFrame{@link #IRTCVideo#pushExternalAudioFrame} to push the captured audio to the SDK.  <br>
     *        + false: No  
     */
    bool enable_audio;
    /**
     * @locale zh
     * @brief 是否检测视频。PC 端默认检测列表中第一个视频设备。  <br>
     *        + true：是  <br>
     *            - 若使用 SDK 内部采集，此时设备摄像头会自动开启  <br>
     *            - 若使用自定义采集，此时你需调用 pushExternalVideoFrame{@link #IRTCVideo#pushExternalVideoFrame} 将采集到的视频推送给 SDK  <br>
     *        + false：否  
     * @note 视频的发布参数固定为：分辨率 640px × 360px，帧率 15fps。
     */
    /**
     * @locale en
     * @brief Whether to test video. If you are using a desktop PC, the device to be tested is by default the first video device in the list.  <br>
     *        + true: Yes  <br>
     *            - If you use internal capture, the device camera will automatically turn on.  <br>
     *            - If you choose custom capture, you also need to call pushExternalVideoFrame{@link #IRTCVideo#pushExternalVideoFrame} to push the captured video to the SDK.  <br>
     *        + false: No  
     * @note The video is published with fixed parameters: resolution 640px × 360px, frame rate 15fps.
     */
    bool enable_video;
    /**
     * @locale zh
     * @brief 音量信息提示间隔，单位：ms，默认为 100ms <br>
     *       + `<= 0`: 关闭信息提示  <br>
     *       + `(0,100]`: 开启信息提示，不合法的 interval 值，SDK 自动设置为 100ms  <br>
     *       + `> 100`: 开启信息提示，并将信息提示间隔设置为此值  
     */
    /**
     * @locale en
     * @brief Volume prompt interval in ms, the default value is 100. <br>
     *        + `<= 0`: Turn off prompt <br>
     *        + `(0,100]` Invalid interval value, and will be automatically reset to 100ms. <br>
     *        + `> 100`: the actual value of interval
     */
    int audio_properties_report_interval;
    /**
     * @locale zh
     * @brief 进行音视频通话回路测试的用户 ID
     */
    /**
     * @locale en
     * @brief User ID for testing
     */
    const char* uid;
    /**
     * @locale zh
     * @brief 测试用户加入的房间 ID。  
     */
    /**
     * @locale en
     * @brief ID of the room that the tested user will join.  
     */
    const char* room_id;
    /**
     * @locale zh
     * @brief 对用户进房时进行鉴权验证的动态密钥，用于保证音视频通话回路测试的安全性。
     */
    /**
     * @locale en
     * @brief Token used for authenticating users when they enter the room.
     */
    const char* token;
};

/**
 * @locale zh
 * @type keytype
 * @brief 音频dump状态。  
 */
/**
 * @locale en
 * @type keytype
 * @brief Audio dump status.   
 */
enum AudioDumpStatus {
    /**
     * @locale zh
     * @brief 音频dump启动失败
     */
     /**
      * @locale en
      * @brief audio dump start failure
      */
    kAudioDumpStatusStartFailure = 0,
    /**
     * @locale zh
     * @brief 音频dump启动成功
     */
    /**
     * @locale en
     * @brief audio dump start success
     */
    kAudioDumpStatusStartSuccess = 1,
    /**
     * @locale zh
     * @brief 音频dump停止失败
     */
    /**
     * @locale en
     * @brief audio dump stop failure
     */
    kAudioDumpStatusStopFailure = 2,
    /**
     * @locale zh
     * @brief 音频dump停止成功
     */
    /**
     * @locale en
     * @brief audio dump stop success
     */
    kAudioDumpStatusStopSuccess = 3,
    /**
     * @locale zh
     * @brief 音频dump运行失败
     */
    /**
     * @locale en
     * @brief audio dump running failure
     */
    kAudioDumpStatusRunningFailure = 4,
    /**
     * @locale zh
     * @brief 音频dump运行成功
     */
    /**
     * @locale en
     * @brief audio dump ruinning success
     */
    kAudioDumpStatusRunningSuccess = 5,
};

/**
 * @locale zh
 * @type errorcode
 * @brief 开始探测的返回值<br>
 *        `startNetworkDetection` 返回对象类型
 */
/**
 * @locale en
 * @type errorcode
 * @brief Return value to start probing<br>
 *        `startNetworkDetection` Return object type
 */
enum NetworkDetectionStartReturn {
    /**
     * @locale zh
     * @brief 成功开启网络探测。
     */
    /**
     * @locale en
     * @brief Network probing enabled successfully.
     */
    kNetworkDetectionStartReturnSuccess = 0,
    /**
     * @locale zh
     * @brief 开始探测失败。参数错误，上下行探测均为 `false`，或期望带宽超过了范围 [100,10000]
     */
    /**
     * @locale en
     * @brief Failed to start probing. Parameter error, both uplink and downlink probes are 'false ', or the expected bandwidth exceeds the range [100,10000]
     */
    kNetworkDetectionStartReturnParamErr = 1,
    /**
     * @locale zh
     * @brief 开始探测失败。失败原因为，本地已经开始推拉流
     */
    /**
     * @locale en
     * @brief Failed to start probing. The reason for the failure is that the local push-pull flow has started
     */
    kNetworkDetectionStartReturnStreaming = 2,
    /**
     * @locale zh
     * @brief 已经开始探测，无需重复开启
     */
    /**
     * @locale en
     * @brief Detection has started, no need to open it again
     */
    kNetworkDetectionStartReturnStarted = 3,
    /**
     * @locale zh
     * @brief 不支持该功能
     */
    /**
     * @locale en
     * @brief Do not support this function
     */
    kNetworkDetectionStartReturnNotSupport = 4,
};

/**
 * @locale zh
 * @type keytype
 * @brief 通话前探测的停止原因<br>
 *        `onNetworkDetectionStopped` 回调的参数类型
 */
/**
 * @locale en
 * @type keytype
 * @brief The reason why the probe stopped before the call<br>
 *        `onNetworkDetectionStopped` The parameter type of the callback
 */
enum NetworkDetectionStopReason {
    /**
     * @locale zh
     * @brief 用户主动停止
     */
    /**
     * @locale en
     * @brief User actively stops
     */
    kNetworkDetectionStopReasonUser,
    /**
     * @locale zh
     * @brief 探测超过三分钟
     */
    /**
     * @locale en
     * @brief Detection over three minutes
     */
    kNetworkDetectionStopReasonTimeout,
    /**
     * @locale zh
     * @brief 探测网络连接断开。<br>当超过 12s 没有收到回复，SDK 将断开网络连接，并且不再尝试重连。
     */
    /**
     * @locale en
     * @brief Probe network connection disconnected. <br> When no reply is received beyond 12s, the SDK will disconnect the network and will not try to reconnect.
     */
    kNetworkDetectionStopReasonConnectionLost,
    /**
     * @locale zh
     * @brief 本地开始推拉流，停止探测
     */
    /**
     * @locale en
     * @brief Local start push-pull flow, stop detection
     */
    kNetworkDetectionStopReasonStreaming,
    /**
     * @locale zh
     * @brief 网络探测失败，内部异常
     */
    /**
     * @locale en
     * @brief Network probe failure, internal anomaly
     */
    kNetworkDetectionStopReasonInnerErr,
};

/**
 * @locale zh
 * @type keytype
 * @brief 通话前探测链接的类型。<br>
 *        `onNetworkDetectionResult` 回调的参数类型
 */
/**
 * @locale en
 * @type keytype
 * @brief The type of probe link before the call.<br>
 *        `onNetworkDetectionResult` The parameter type for the callback
 */
enum NetworkDetectionLinkType {
    /**
     * @locale zh
     * @brief 上行网络探测
     */
    /**
     * @locale en
     * @brief Uplink network sounding
     */
    kNetworkDetectionLinkTypeUp = 0,
    /**
     * @locale zh
     * @brief 下行网络探测
     */
    /**
     * @locale en
     * @brief Downlink network detection
     */
    kNetworkDetectionLinkTypeDown,
};

/**
 * @locale zh
 * @type keytype
 * @brief 网络时间信息
 */
/**
 * @locale en
 * @type keytype
 * @brief network time info
 */
struct NetworkTimeInfo {
    /**
     * @locale zh
     * @brief 网络时间，单位：ms
     */
    /**
     * @locale en
     * @brief Network time. Unit: ms
     */
    int64_t timestamp;
    /**
     * @hidden constructor/destructor
     */
    explicit NetworkTimeInfo(int64_t ts): timestamp(ts) {
    }
};

/**
 * @locale zh
 * @type keytype
 * @brief 通话前回声检测结果
 */
/**
 * @locale en
 * @type keytype
 * @brief Result of the detection inited before joining a room
 */
enum HardwareEchoDetectionResult{
    /**
     * @locale zh
     * @brief 主动调用 `stopHardwareEchoDetection` 结束流程时，未有回声检测结果。
     */
    /**
     * @locale en
     * @brief Detection is stopped by the call of `stopHardwareEchoDetection` before the SDK reports the detection result.
     */
    kHardwareEchoDetectionResultCanceled = 0,
    /**
     * @locale zh
     * @brief 未检测出结果。建议重试，如果仍然失败请联系技术支持协助排查。
     */
    /**
     * @locale en
     * @brief Unknown state<br>
     *        Contact us if you retry several times but keep failing.
     */
    kHardwareEchoDetectionResultUnknown = 1,
    /**
     * @locale zh
     * @brief 无回声
     */
    /**
     * @locale en
     * @brief Excellent <br>
     *        No echo issue is detected.
     */
    kHardwareEchoDetectionResultNormal = 2,
    /**
     * @locale zh
     * @brief 有回声。可通过 UI 建议用户使用耳机设备入会。
     */
    /**
     * @locale en
     * @brief Echo <br>
     *        Echo issue is detected. Recommend the user join the call with a headset through the interface.
     */
    kHardwareEchoDetectionResultPoor = 3,
};

/**
 * @locale zh
 * @type keytype
 * @brief 音频选路优先级设置
 */
/**
 * @locale en
 * @type keytype
 * @brief User priority in the audio selection
 */
enum AudioSelectionPriority {
    /**
     * @locale zh
     * @brief 正常，参加音频选路
     */
    /**
     * @locale en
     * @brief Normal whether the stream can be subscribed is determined by the result of audio selection.
     */
    kAudioSelectionPriorityNormal = 0,
    /**
     * @locale zh
     * @brief 高优先级，跳过音频选路
     */
    /**
     * @locale en
     * @brief Hight priority with which the stream can skip the audio selection and always be subscribable.
     */
    kAudioSelectionPriorityHigh = 1
};

/**
 * @locale zh
 * @type keytype
 * @brief 设置房间附加消息结果。
 */
/**
 * @locale en
 * @type keytype
 * @brief Extra information setting result.
 */
enum SetRoomExtraInfoResult {
    /**
     * @locale zh
     * @brief 设置房间附加信息成功
     */
    /**
     * @locale en
     * @brief Success.
     */
    kSetRoomExtraInfoResultSuccess = 0,
    /**
     * @locale zh
     * @brief 设置失败，尚未加入房间
     */
    /**
     * @locale en
     * @brief Failure. You are not in the room.
     */
    kSetRoomExtraInfoResultErrorNotJoinRoom = -1,
    /**
     * @locale zh
     * @brief 设置失败，key 指针为空
     */
    /**
     * @locale en
     * @brief Failure. The key pointer is null.
     */
    kSetRoomExtraInfoResultErrorKeyIsNull = -2,
    /**
     * @locale zh
     * @brief 设置失败，value 指针为空
     */
    /**
     * @locale en
     * @brief Failure. The value pointer is null.
     */
    kSetRoomExtraInfoResultErrorValueIsNull = -3,
    /**
     * @locale zh
     * @brief 设置失败，未知错误
     */
    /**
     * @locale en
     * @brief Failure. Unknown error.
     */
    kSetRoomExtraInfoResultResultUnknow = -99,
    /**
     * @locale zh
     * @brief 设置失败，key 长度为 0
     */
    /**
     * @locale en
     * @brief Failure. The key length is 0.
     */
    kSetRoomExtraInfoResultErrorKeyIsEmpty = -400,
    /**
     * @locale zh
     * @brief 调用 `setRoomExtraInfo` 过于频繁，建议不超过 10 次/秒。
     */
    /**
     * @locale en
     * @brief Failure. Excessively frequent setting. 10 times per second is preferable.
     */
    kSetRoomExtraInfoResultErrorTooOften = -406,
    /**
     * @locale zh
     * @brief 设置失败，用户已调用 `setUserVisibility` 将自身设为隐身状态。
     */
    /**
     * @locale en
     * @brief Failure. Invisible users are not allowed to call `setRoomExtraInfo`.
     */
    kSetRoomExtraInfoResultErrorSilentUser = -412,
    /**
     * @locale zh
     * @brief 设置失败，Key 长度超过 10 字节
     */
    /**
     * @locale en
     * @brief Failure. Key length exceeds 10 bytes.
     */
    kSetRoomExtraInfoResultErrorKeyTooLong = -413,
    /**
     * @locale zh
     * @brief 设置失败，value 长度超过 128 字节
     */
    /**
     * @locale en
     * @brief Failure. Value length exceeds 128 bytes.
     */
    kSetRoomExtraInfoResultErrorValueTooLong = -414,
    /**
     * @locale zh
     * @brief 设置失败，服务器错误
     */
    /**
     * @locale en
     * @brief Failure. Server error.
     */
    kSetRoomExtraInfoResultErrorServer = -500
};
/**
 * @locale zh
 * @type keytype
 * @brief 字幕任务状态。
 */
/**
 * @locale en
 * @hidden currently not available 
 * @type keytype
 * @brief The states of the subtitling task.
 */
enum SubtitleState {
    /**
     * @locale zh
     * @brief 开启字幕。
     */
    /**
     * @locale en
     * @brief Subtitles are on. 
     */
    kSubtitleStateStarted,
    /**
     * @locale zh
     * @brief 关闭字幕。
     */
    /**
     * @locale en
     * @brief Subtitles are off.
     */
    kSubtitleStateStoped,
    /**
     * @locale zh
     * @brief 字幕任务出现错误。
     */
    /**
     * @locale en
     * @brief Errors occurred in the subtitling task. 
     */
    kSubtitleStateError
};
/**
 * @locale zh
 * @type keytype
 * @brief 字幕模式。
 */
/**
 * @locale en
 * @hidden currently not available
 * @type keytype
 * @brief Subtitle modes.
 */
enum SubtitleMode {
    /**
     * @locale zh
     * @brief 识别模式。在此模式下，房间内用户语音会被转为文字。
     */
    /**
     * @locale en
     * @brief The recognition mode. In this mode, the speech of a users in the room will be recognized and converted into captions.
     */
    kSubtitleModeRecognition = 0,
    /**
     * @locale zh
     * @brief 翻译模式。在此模式下，房间内用户语音会先被转为文字，再被翻译为目标语言。
     */
    /**
     * @locale en
     * @brief The translation mode. In this mode, the speech of a users in the room will be converted into captions and then translated.
     */
    kSubtitleModeTranslation
};
/**
 * @locale zh
 * @type errorcode
 * @brief 字幕任务错误码。
 */
/**
 * @locale en
 * @hidden currently not available 
 * @type errorcode
 * @brief Error codes of the subtitling task.
 */
enum SubtitleErrorCode {
    /**
     * @locale zh
     * @brief 客户端无法识别云端媒体处理发送的错误码。请联系技术支持。 
     */
    /**
     * @locale en
     * @brief The client side failed to identity error codes sent by cloud media processing. Please contact the technical support. 
     */
    kSubtitleErrorCodeUnknow = -1,
    /**
     * @locale zh
     * @brief 字幕已开启。
     */
    /**
     * @locale en
     * @brief Subtitles are turned on. 
     */
    kSubtitleErrorCodeSuccess,
    /**
     * @locale zh
     * @brief 云端媒体处理内部出现错误，请联系技术支持。
     */
    /**
     * @locale en
     * @brief Errors occurred concerning cloud media processing. Please contact the technical support.
     */
    kSubtitleErrorCodePostProcessError,
    /**
     * @locale zh
     * @brief 第三方服务连接失败，请联系技术支持。
     */
    /**
     * @locale en
     * @brief Failed to connect to the third-party service. Please contact the technical support.
     */
    kSubtitleErrorCodeASRConnectionError,
    /**
     * @locale zh
     * @brief 第三方服务内部出现错误，请联系技术支持。
     */
    /**
     * @locale en
     * @brief Errors occurred concerning the third-party service. Please contact the technical support.
     */
    kSubtitleErrorCodeASRServiceError,
    /**
     * @locale zh
     * @brief 未进房导致调用`startSubtitle`失败。请加入房间后再调用此方法。
     */
    /**
     * @locale en
     * @brief Failed to call `startSubtitle`. Please join the room first. 
     */
    kSubtitleErrorCodeBeforeJoinRoom,
    /**
     * @locale zh
     * @brief 重复调用 `startSubtitle`。
     */
    /**
     * @locale en
     * @brief You has already called `startSubtitle`. 
     */
    kSubtitleErrorCodeAlreadyOn,
    /**
     * @locale zh
     * @brief 用户选择的目标语言目前暂不支持。
     */
    /**
     * @locale en
     * @brief The target language you chose is not Unsupported.
     */
    kSubtitleErrorCodeUnsupportedLanguage,
    /**
     * @locale zh
     * @brief 云端媒体处理超时未响应，请联系技术支持。
     */
    /**
     * @locale en
     * @brief Cloud media processing is timeout. Please contact the technical support.
     */
    kSubtitleErrorCodePostProcessTimeout
};
/**
 * @locale zh
 * @type keytype
 * @brief 字幕配置信息。
 */
/**
 * @locale en
 * @hidden currently not available 
 * @type keytype
 * @brief Subtitle configurations.
 */
struct SubtitleConfig {
    /**
     * @locale zh
     * @brief 字幕模式。可以根据需要选择识别和翻译两种模式。开启识别模式，会将识别后的用户语音转化成文字；开启翻译模式，会在语音识别后进行翻译。参看 SubtitleMode{@link #SubtitleMode}。
     */
    /**
     * @locale en
     * @brief Subtitle mode. You can choose between the recognition and translation modes based on your needs. In the recognition mode, the speech of the speaker in the room will be recognized and converted into captions. In the translation mode, the transcribed text will be translated. Refer to SubtitleMode{@link #SubtitleMode} for more details.
     */
    SubtitleMode mode = kSubtitleModeRecognition;
    /**
     * @locale zh
     * @brief 目标翻译语言。可点击 [语言支持](https://www.volcengine.com/docs/4640/35107#%F0%9F%93%A2%E5%AE%9E%E6%97%B6%E8%AF%AD%E9%9F%B3%E7%BF%BB%E8%AF%91) 查看翻译服务最新支持的语种信息。
     */
    /**
     * @locale en
     * @brief Target language. 
     */
    const char* target_language = "";
};
/**
 * @locale zh
 * @type keytype
 * @brief 字幕具体内容。
 */
/**
 * @locale en
 * @hidden currently not available
 * @type keytype
 * @brief Related information about subtitles.
 */
struct SubtitleMessage {
    /**
     * @locale zh
     * @brief 说话者的用户ID。
     */
    /**
     * @locale en
     * @brief The speaker's ID.
     */
    const char* user_id;
    /**
     * @locale zh
     * @brief 字幕文本, 采用 UTF-8 编码。
     */
    /**
     * @locale en
     * @brief Speaker's speech text, encoded in UTF-8 format.
     */
    const char* text;
    /**
     * @locale zh
     * @brief 字幕语种，根据字幕模式为原文或译文对应的语种。
     */
    /**
     * @locale en
     * @brief The language of the transcribed or translated text according to the subtitle mode.
     */
    const char* language;
    /**
     * @locale zh
     * @brief 字幕模式，参看 SubtitleMode{@link #SubtitleMode}。
     */
    /**
     * @locale en
     * @brief Speaker's speech text subtitle mode. Refer to SubtitleMode{@link #SubtitleMode} for more details.
     */
    SubtitleMode mode;
    /**
     * @locale zh
     * @brief 字幕文本序列号，同一发言人的完整发言和不完整发言会按递增顺序单独分别编号。
     */
    /**
     * @locale en
     * @brief Incremental sequence numbers of the speaker's speech. Complete and incomplete sentences are numbered individually.
     */
    int sequence;
    /**
     * @locale zh
     * @brief 语音识别出的文本是否为一段完整的一句话。 True 代表是, False 代表不是。
     */
    /**
     * @locale en
     * @brief Whether transcribed texts are complete sentences. True means yes and False means no.
     */
    bool definite;
};
/**
 * @locale zh
 * @type keytype
 * @hidden internal use only
 * @brief 特效错误类型。
 */
/**
 * @locale en
 * @type keytype
 * @hidden internal use only
 * @brief Effect error type.
 */
enum EffectErrorType {
    /**
     * @locale zh
     * @hidden 仅用于会议
     * @brief 虚拟背景设置错误。
     */
    /**
     * @locale en
     * @hidden internal use only
     * @brief Failed to set virtual background.
     */
    kEffectErrorVirtualBackgroundFailure = 1,
    /**
     * @locale zh
     * @hidden 仅用于会议
     * @brief 特效独立进程崩溃。
     */
    /**
     * @locale en
     * @hidden for internal use only
     * @brief Effect independent process crash.
     */
    kEffectErrorChildProcTerminate,
};

/**
 * @locale zh
 * @type render error code
 * @hidden for internal use only 
 * @brief 渲染错误码。
 */
/**
 * @locale en
 * @hidden for internal use only 
 * @type error code
 * @brief render error code.
 */
enum RenderError {
    /**
     * @locale zh
     * @brief 渲染正常
     */
    /**
     * @locale en
     * @brief Render normal
     */
    kRenderErrorOk = 0,
    /**
     * @locale zh
     * @brief Android 外部直显时使用了内部 surface
     */
    /**
     * @locale en
     * @brief Using internal surface in Android direct decode and render
     */
    kRenderErrorUsingInternalSurface = -1,
    /**
     * @locale zh
     * @brief 设置 Android 外部直显时使用软解
     */
    /**
     * @locale en
     * @brief Using software decoder in Android direct decode and render
     */
    kRenderErrorUsingSoftwareDecoder = -2,

};

/**
 * @brief 线程block信息,包含线程名和线程block的次数
 * @hidden
 * 
 */
struct DeadLockMsg {
    const char* task_name;
    int lasting_times;
};

}  // namespace bytertc
