/*
 * Copyright (c) 2022 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief Objective-C VolcEngineRTC Common Defines
*/

#import "ByteRTCRtsDefines.h"
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
typedef NS_ENUM(NSInteger, ByteRTCReturnStatus) {
    /**
     * @locale zh
     * @brief 成功。
     */
    /**
     * @locale en
     * @brief Success.
     */
    ByteRTCReturnStatusSuccess = 0,
    /**
     * @locale zh
     * @brief 失败。
     */
    /**
     * @locale en
     * @brief Failure.
     */
    ByteRTCReturnStatusFailure = -1,
    /**
     * @locale zh
     * @brief 参数错误。
     */
    /**
     * @locale en
     * @brief Invalid parameter.
     */
    ByteRTCReturnStatusParameterErr = -2,
    /**
     * @locale zh
     * @brief 接口状态错误。
     */
    /**
     * @locale en
     * @brief API status error.
     */
    ByteRTCReturnStatusWrongState = -3,
    /**
     * @locale zh
     * @brief 失败，用户已在房间内。
     */
    /**
     * @locale en
     * @brief Failure. The user is already in the room.
     */
    ByteRTCReturnStatusHasInRoom = -4,
    /**
     * @locale zh
     * @brief 失败，用户已登录。
     */
    /**
     * @locale en
     * @brief Failure. The user has already logged in.
     */
    ByteRTCReturnStatusHasInLogin = -5,
    /**
     * @locale zh
     * @brief 失败，用户已经在进行通话回路测试中。
     */
    /**
     * @locale en
     * @brief Failure. The user is already in a pre-call test.
     */
    ByteRTCReturnStatusHasInEchoTest = -6,
    /**
     * @locale zh
     * @brief 失败，音视频均未采集。
     */
    /**
     * @locale en
     * @brief Failure. Neither video nor audio is captured.
     */
    ByteRTCReturnStatusNeitherVideoNorAudio = -7,
    /**
     * @locale zh
     * @brief 失败，该 roomId 已被使用。
     */
    /**
     * @locale en
     * @brief Failure. The roomId is already in use.
     */
    ByteRTCReturnStatusRoomIdInUse = -8,
    /**
     * @locale zh
     * @brief 失败，屏幕流不支持。
     */
    /**
     * @locale en
     * @brief Failure. Screen stream is not supported.
     */
    ByteRTCReturnStatusScreenNotSupport = -9,
    /**
     * @locale zh
     * @brief 失败，不支持该操作。
     */
    /**
     * @locale en
     * @brief Failure. Not supported.
     */
    ByteRTCReturnStatusNotSupport = -10,
    /**
     * @locale zh
     * @brief 失败，资源已占用。
     */
    /**
     * @locale en
     * @brief Failure. resource overflow.
     */
    ByteRTCReturnStatusResourceOverflow = -11,
    /**
     * @locale zh
     * @brief 失败，没有音频帧。
     */
    /**
     * @locale en
     * @brief Failure. No audio frame.
     */
    ByteRTCReturnStatusAudioNoFrame = -101,
    /**
     * @locale zh
     * @brief 失败，未实现。
     */
    /**
     * @locale en
     * @brief Failure. No implemented.
     */
    ByteRTCReturnStatusAudioNotImplemented = -102,
    /**
     * @locale zh
     * @brief 失败，采集设备无麦克风权限，尝试初始化设备失败。
     */
    /**
     * @locale en
     * @brief Failure. The audio capture device does not have microphone use permission, and the initialization of the device failed.
     */
    ByteRTCReturnStatusAudioNoPermission = -103,
    /**
     * @locale zh
     * @brief 失败，设备不存在。当前没有设备或设备被移除时返回该值。
     */
    /**
     * @locale en
     * @brief Failure. The device does not exist. This value is returned if there is currently no device or if the device has been removed.
     */
    ByteRTCReturnStatusAudioDeviceNotExists = -104,
    /**
     * @locale zh
     * @brief 失败，设备音频格式不支持。
     */
    /**
     * @locale en
     * @brief Failure. The device audio format is not supported.
     */
    ByteRTCReturnStatusAudioDeviceFormatNotSupport = -105,
    /**
     * @locale zh
     * @brief 失败，系统无可用设备。
     */
    /**
     * @locale en
     * @brief Failure. No device in system.
     */
    ByteRTCReturnStatusAudioDeviceNoDevice = -106,
    /**
     * @locale zh
     * @brief 失败，当前设备不可用，需更换设备。
     */
    /**
     * @locale en
     * @brief Failure. The current device is not available and need to be replaced.
     */
    ByteRTCReturnStatusAudioDeviceCannotUse = -107,
    /**
     * @locale zh
     * @brief 系统错误，设备初始化失败。
     */
    /**
     * @locale en
     * @brief Device initialization failed due to a system error.
     */
    ByteRTCReturnStatusAudioDeviceInitFailed = -108,
    /**
     * @locale zh
     * @brief 系统错误，设备开启失败。
     */
    /**
     * @locale en
     * @brief Device start-up failed due to a system error.
     */
    ByteRTCReturnStatusAudioDeviceStartFailed = -109,
    /**
     * @locale zh
     * @brief 失败。底层未初始化，engine 无效。
     */
    /**
     * @locale en
     * @brief Failure. The native layer is not initialized and the engine is invalid.
     */
    ByteRTCReturnStatusNativeInValid = -201,
};

/**
 * @locale zh
 * @type keytype
 * @brief 房间内远端流移除原因。  
 */
/**
 * @locale en
 * @type keytype
 * @brief The reason for the removal of the remote flow in the room.   
 */
typedef NS_ENUM(NSInteger, ByteRTCStreamRemoveReason) {
    /**
     * @locale zh
     * @brief 远端用户停止发布流。  
     */
    /**
     * @locale en
     * @brief The remote user stops publishing the flow.   
     */
    ByteRTCStreamRemoveReasonUnpublish = 0,
    /**
     * @locale zh
     * @brief 远端用户发布流失败。  
     */
    /**
     * @locale en
     * @brief The remote user failed to publish the flow.   
     */
    ByteRTCStreamRemoveReasonPublishFailed = 1,
    /**
     * @locale zh
     * @brief 媒体服务器 10s 没收到客户端的媒体数据。
     */
    /**
     * @locale en
     * @brief Media server failed to receive media data from the client for 10 seconds.
     */
    ByteRTCStreamRemoveReasonKeepLiveFailed = 2,
    /**
     * @locale zh
     * @brief 远端用户断网。  
     */
    /**
     * @locale en
     * @brief The remote user is disconnected.   
     */
    ByteRTCStreamRemoveReasonClientDisconnected = 3,
    /**
     * @locale zh
     * @brief 远端用户重新发布流。  
     */
    /**
     * @locale en
     * @brief The remote user republishes the flow.   
     */
    ByteRTCStreamRemoveReasonRepublish = 4,
    /**
     * @locale zh
     * @brief 其他原因。  
     */
    /**
     * @locale en
     * @brief Other reasons.   
     */
    ByteRTCStreamRemoveReasonOther = 5,
    /**
     * @locale zh
     * @brief 远端用户 Token 发布权限过期。
     */
    /**
     * @locale en
     * @brief The remote user's publishing privilege of the Token is expired.
     */
    ByteRTCStreamRemoveReasonPublishPrivilegeExpired = 6,
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
typedef NS_ENUM(NSInteger, ByteRTCRoomProfile) {
    /**
     * @locale zh
     * @brief 默认场景，通用模式<br>
     *        与 `ByteRTCRoomProfileMeeting = 16` 配置相同。<br>
     *        你可以联系技术支持更换默认配置参数。
     */
    /**
     * @locale en
     * @brief General mode by default<br>
     *        It equals to `ByteRTCRoomProfileMeeting = 16`.<br>
     *        Contact us to alter the default settings.
     */
    ByteRTCRoomProfileCommunication = 0,
    /**
     * @locale zh
     * @deprecated since 3.42 and will be deleted in 3.51, use ByteRTCRoomProfileInteractivePodcast instead.
     * @brief 直播模式。<br>
     *        当你对音视频通话的音质和画质要求较高时，应使用此设置。<br>
     *        此设置下，当用户使用蓝牙耳机收听时，蓝牙耳机使用媒体模式。
     */
    /**
     * @locale en
     * @deprecated since 3.45 and will be deleted in 3.51, use ByteRTCRoomProfileInteractivePodcast instead.
     * @hidden
     * @brief Live broadcasting mode. <br>
     *        Use this mode for high quality of the media. <br>
     *        In this mode, audio plays in media mode for Bluetooth earphones.
     */
    ByteRTCRoomProfileLiveBroadcasting = 1,
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
    ByteRTCRoomProfileGame = 2,
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
    ByteRTCRoomProfileCloudGame = 3,
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
    ByteRTCRoomProfileLowLatency = 4,
    /**
     * @locale zh
     * @brief 适用于 1 vs 1 音视频通话
     */
    /**
     * @locale en
     * @brief For 1 vs 1 video and audio calls
     */
    ByteRTCRoomProfileChat = 5,
    /**
     * @locale zh
     * @brief 适用于 3 人及以上纯语音通话。<br>
     *        通话中，闭麦时为是媒体模式，上麦后切换为通话模式。
     */
    /**
     * @locale en
     * @brief For video and audio chat rooms of 3 or more people
     */
    ByteRTCRoomProfileChatRoom = 6,
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
    ByteRTCRoomProfileLwTogether = 7,
    /**
     * @locale zh
     * @brief 适用于对音质要求较高的游戏场景，优化音频 3A 策略，只通过媒体模式播放音频
     */
    /**
     * @locale en
     * @brief For the game apps demanding high-resolution audio. In this mode, RTC plays audio using the media mode only.
     */
    ByteRTCRoomProfileGameHD = 8,
    /**
     * @locale zh
     * @brief 适用于直播中主播之间连麦的业务场景。<br>
     *        该场景中，直播时通过 CDN，发起连麦 PK 时使用 RTC。
     */
    /**
     * @locale en
     * @brief For the events of co-hosting in the live-streaming<br>
     *        During a livestreaming using a CDN network, the host can invite another host to join the co-hosting event using RTC.
     */
    ByteRTCRoomProfileCoHost = 9,
    /**
     * @locale zh
     * @brief 适用于单主播和观众进行音视频互动的直播。通话模式，上下麦不会有模式切换，避免音量突变现象
     */
    /**
     * @locale en
     * @brief For interactive podcasts that the host can have video and audio interactions with the audience. The voice mode is set to communication mode to avoid volume spiking and dipping acutely.
     */
    ByteRTCRoomProfileInteractivePodcast = 10,
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
    ByteRTCRoomProfileKTV = 11,
    /**
     * @locale zh
     * @brief 适合在线实时合唱场景，高音质，超低延迟。使用本配置前请联系技术支持进行协助完成其他配置。
     */
    /**
     * @locale en
     * @brief For the online-chorusing scenarios requiring high-quality audio and low latency. Contact our technical specialists before you apply it to your App.
     */
    ByteRTCRoomProfileChorus = 12,
    /**
     * @locale zh
     * @brief 适用于 VR 场景。支持最高 192 KHz 音频采样率，可开启球形立体声。345之后支持
     */
    /**
     * @locale en
     * @brief For VR chat with support for 192 KHz audio sample rate and feature of 360 Reality AudioAudio
     */
    ByteRTCRoomProfileVRChat = 13,
    /**
     * @locale zh
     * @brief 适用于 1 vs 1 游戏串流，支持公网或局域网。
     */
    /**
     * @locale en
     * @brief For scenarios of streaming live videos to only one client on the LAN. It can be applied to devices on the Internet or LAN.
     */
    ByteRTCRoomProfileGameStreaming = 14,
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
    ByteRTCRoomProfileLanLiveStreaming = 15,
    /**
     * @locale zh
     * @brief 适用于云端会议中的个人设备
     */
    /**
     * @locale en
     * @brief For meeting Apps installed on personal devices
     */
    ByteRTCRoomProfileMeeting = 16,
    /**
     * @locale zh
     * @brief 适用于云端会议中的会议室终端设备，例如 Rooms，投屏盒子等。
     */
    /**
     * @locale en
     * @brief For meeting Apps installed on terminals of meeting rooms, such as Rooms.
     */
    ByteRTCRoomProfileMeetingRoom = 17,
    /**
     * @locale zh
     * @brief 适用于课堂互动，房间内所有成员都可以进行音视频互动<br>
     *        当你的场景中需要同时互动的成员超过 10人时使用此模式
     */
    /**
     * @locale en
     * @brief For the online classrooms and lectures that over 10 participants in the room are allowed to join the video chat.
     */
    ByteRTCRoomProfileClassroom = 18,
};

/**
 * @locale zh
 * @hidden
 * @deprecated since 3.45 and will be delted in 3.51.
 * @type keytype
 * @brief 用户角色。  
 */
/**
 * @locale en
 * @hidden
 * @deprecated since 3.45 and will be delted in 3.51.
 * @type keytype
 * @brief User persona.   
 */
typedef NS_ENUM(NSInteger, ByteRTCUserRoleType) {
    /**
     * @locale zh
     * @brief 主播角色。该角色用户可在房间内发布和订阅音视频流，房间中的其他用户可以感知到该用户的存在。  
     */
    /**
     * @locale en
     * @brief Live streaming host role. This role user can publish and subscribe to audio & video streams in the room, and other users in the room can perceive the presence of this user.   
     */
    ByteRTCUserRoleTypeBroadcaster = 1,
    /**
     * @locale zh
     * @brief 隐身用户角色。此角色用户只可在房间内订阅音视频流，房间中的其他用户无法感知到该用户的存在。  
     */
    /**
     * @locale en
     * @brief Stealth user persona. This role user can only subscribe to audio & video streams in the room, and other users in the room cannot perceive the presence of this user.   
     */
    ByteRTCUserRoleTypeSilentAudience = 2,
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
 typedef NS_ENUM(NSInteger, ByteRTCUserVisibilityChangeError) {
    /**
     * @locale zh
     * @brief 成功。
     */
    /**
     * @locale en
     * @brief Success.
     */
    ByteRTCUserVisibilityChangeErrorOk = 0,
    /**
     * @locale zh
     * @brief 未知错误。
     */
    /**
     * @locale en
     * @brief Unknown error.
     */
    ByteRTCUserVisibilityChangeErrorUnknown = 1,
    /**
     * @locale zh
     * @brief 房间内可见用户达到上限。
     */
    /**
     * @locale en
     * @brief Visible users in the room have reached the upper limit.
     */
    ByteRTCUserVisibilityChangeErrorTooManyVisibleUser = 2,
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
typedef NS_ENUM(NSInteger, ByteRTCDataMessageSourceType) {
    /**
     * @locale zh
     * @brief 通过客户端或服务端的插入的自定义消息。
     */
    /**
     * @locale en
     * @brief Customized messages inserted by calling API in the server or SDK.
     */
    ByteRTCDataMessageSourceTypeDefault = 0,
    /**
     * @locale zh
     * @brief 系统数据，包含音量指示信息。
     */
    /**
     * @locale en
     * @brief System notification such as volume indication.
     */
    ByteRTCDataMessageSourceTypeSystem = 1,
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
typedef NS_ENUM(NSInteger,  ByteRTCSEICountPerFrame) {
    /**
     * @locale zh
     * @brief 单发模式。即在 1 帧间隔内多次发送 SEI 数据时，多个 SEI 按队列逐帧发送。
     */
    /**
     * @locale en
     * @brief Single-SEI mode. When you send multiple SEI messages in 1 frame, they will be sent frame by frame in a queue.
     */
    ByteRTCSEICountPerFrameSingle = 0,
    /**
     * @locale zh
     * @brief 多发模式。即在 1 帧间隔内多次发送 SEI 数据时，多个 SEI 随下个视频帧同时发送。
     */
    /**
     * @locale en
     * @brief Multi-SEI mode. When you send multiple SEI messages in 1 frame, they will be sent together in the next frame.
     */
    ByteRTCSEICountPerFrameMulti = 1,
};

/**
 * @locale zh
 * @type errorcode
 * @brief 回调错误码。<br>
 *        SDK 内部遇到不可恢复的错误时，会通过 `rtcEngine:onError:` 回调通知用户。
 */
/**
 * @locale en
 * @type errorcode
 * @brief  Callback error code. When an unrecoverable error is encountered internally in the<br>
 *        SDK, the user is notified via an `rtcEngine:onError:` callback.
 */
typedef NS_ENUM(NSInteger, ByteRTCErrorCode) {
    /**
     * @locale zh
     * @brief Token 无效。<br>
     *        调用 joinRoom:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoom:userInfo:roomConfig:} 进房时使用的 Token 参数有误或过期失效。需要重新获取 Token，并调用 updateToken:{@link #ByteRTCRoom#updateToken:} 方法更新 Token。
     */
    /**
     * @locale en
     * @brief Token  is invalid.<br>
     *        The Token used when calling joinRoom:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoom:userInfo:roomConfig:} is invalid or expired. The user is required to retrieve the token and call the updateToken:{@link #ByteRTCRoom#updateToken:} to update the token.
     */
    ByteRTCErrorCodeInvalidToken               = -1000,
    /**
     * @locale zh
     * @brief 加入房间错误。<br>
     *        进房时发生未知错误导致加入房间失败。需要用户重新加入房间。
     */
    /**
     * @locale en
     * @brief Join room error.<br>
     *        An unknown error occurred when joining the room, which caused the room to fail to join. Users are required to rejoin the room.
     */
    ByteRTCErrorCodeJoinRoom             = -1001,
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
    ByteRTCErrorCodeNoPublishPermission       = -1002,
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
    ByteRTCErrorCodeNoSubscribePermission     = -1003,
    /**
     * @locale zh
     * @brief 相同用户 ID 的用户加入本房间，当前用户被踢出房间
     */
    /**
     * @locale en
     * @brief The current user is removed from the room because another with the same user ID joins the room.
     */
    ByteRTCErrorCodeDuplicateLogin             = -1004,

    /**
     * @locale zh
     * @brief 服务端调用 OpenAPI 将当前用户踢出房间
     */
    /**
     * @locale en
     * @brief The user has been removed from the room by the administrator via a OpenAPI call.
     */
    ByteRTCErrorCodeKickedOut = -1006,

    /**
     * @locale zh
     * @brief 当调用 `createRtcRoom:` ，如果 roomId 非法，会返回 null，并抛出该错误
     */
    /**
     * @locale en
     * @brief When calling `createRtcRoom:`, if the roomId is illegal, it will return null and throw the error
     */
    ByteRTCErrorCodeRoomIdIllegal = -1007,
    /**
     * @locale zh
     * @brief Token 过期。加入房间后 Token 过期时，返回此错误码。需使用新的 Token 重新加入房间。
     */
    /**
     * @locale en
     * @brief Token expired. This error code is returned when the user's token expires in the room.<br>
     *        Call joinRoom:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoom:userInfo:roomConfig:} to rejoin the room with a new required Token.
     */
    ByteRTCErrorCodeTokenExpired            = -1009,
        /**
     * @locale zh
     * @brief 调用 `updateToken:` 传入的 Token 无效
     */
    /**
     * @locale en
     * @brief The Token you provided when calling `updateToken:` is invalid.
     */
    ByteRTCErrorCodeUpdateTokenWithInvalidToken     = -1010,

    /**
     * @locale zh
     * @brief 服务端调用 OpenAPI 解散房间，所有用户被移出房间。
     */
    /**
     * @locale en
     * @brief Users have been removed from the room because the administrator dismissed the room by calling OpenAPI.
     */
    ByteRTCErrorCodeRoomDismiss = -1011,

    /**
     * @locale zh
     * @hidden internal use only
     * @brief 加入房间错误。  <br>
     *        调用 `joinRoom:userInfo:roomConfig:` 方法时, LICENSE 计费账号未使用 LICENSE_AUTHENTICATE SDK，加入房间错误。
     */
    /**
     * @locale en
     * @hidden internal use only
     * @brief Join room error. <br>
     *        The LICENSE billing account does not use the LICENSE_AUTHENTICATE SDK while calling `joinRoom:userInfo:roomConfig:`, which caused the joining room to fail.
     */
    ByteRTCJoinRoomWithoutLicenseAuthenticateSDK = -1012,

    /**
     * @locale zh
     * @brief 通话回路检测已经存在同样 roomId 的房间了
     */
    /**
     * @locale en
     * @brief there is a room with the same roomId，whose room id is the same with echo test
     */
    ByteRTCRoomAlreadyExist = -1013,

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
    ByteRTCUserIDDifferent = -1014,
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
    ByteRTCErrorCodeJoinRoomServerLicenseExpired = -1017,
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
    ByteRTCErrorCodeJoinRoomExceedsTheUpperLimit = -1018,
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
    ByteRTCErrorCodeJoinRoomLicenseParameterError = -1019,
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
    ByteRTCErrorCodeJoinRoomLicenseFilePathError = -1020,
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
    ByteRTCErrorCodeJoinRoomLicenseIllegal = -1021,
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
    ByteRTCErrorCodeJoinRoomLicenseExpired = -1022,
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
    ByteRTCErrorCodeJoinRoomLicenseInformationNotMatch = -1023,
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
    ByteRTCErrorCodeJoinRoomLicenseNotMatchWithCache = -1024,
    /**
     * @locale zh
     * @brief 房间被封禁。 
     */
    /**
     * @locale en
     * @brief The room has banned before the user calls `joinRoom`.
     */
    ByteRTCErrorCodeJoinRoomRoomForbidden = -1025,
    /**
     * @locale zh
     * @brief 用户被封禁。 
     */
    /**
     * @locale en
     * @brief The user has banned before calling `joinRoom`.
     */
    ByteRTCErrorCodeJoinRoomUserForbidden = -1026,
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
    ByteRTCErrorCodeOverStreamSubscribeLimit        = -1070,
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
    ByteRTCErrorCodeOverStreamPublishLimit = -1080,
    /**
     * @locale zh
     * @deprecated since 3.52, use ByteRTCErrorCodeOverStreamPublishLimit-1080）instead
     * @brief 发布屏幕流失败，发布流总数超过上限。<br>
     *        RTC 系统会限制单个房间内发布的总流数，总流数包括视频流、音频流和屏幕流。如果房间内发布流数已达上限时，本地用户再向房间中发布流时会失败，同时会收到此错误通知。
     */
    /**
     * @locale en
     * @deprecated since 3.52, use ByteRTCErrorCodeOverStreamPublishLimit-1080）instead
     * @brief Publishing the screen stream failed, and the total number of publishing streams exceeded the upper limit. The<br>
     *        RTC system limits the total number of streams published in a single room, including video streams, audio streams, and screen streams. Local users will fail to publish streams to the room when the maximum number of published streams in the room has been reached, and will receive this error notification.
     */
    ByteRTCErrorCodeOverScreenPublishLimit = -1081,
    /**
     * @locale zh
     * @deprecated since 3.52, use ByteRTCErrorCodeOverStreamPublishLimit-1080）instead
     * @brief 发布视频流总数超过上限。<br>
     *        RTC 系统会限制单个房间内发布的视频流数。如果房间内发布视频流数已达上限时，本地用户再向房间中发布视频流时会失败，同时会收到此错误通知。
     */
    /**
     * @locale en
     * @deprecated since 3.52, use ByteRTCErrorCodeOverStreamPublishLimit-1080）instead
     * @brief The total number of published video streams exceeds the upper limit.<br>
     *        The RTC system limits the number of video streams posted in a single room. If the maximum number of video streams posted in the room has been reached, local users will fail to post video streams to the room again and will receive this error notification.
     */
    ByteRTCErrorCodeOverVideoPublishLimit = -1082,
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
    ByteRTCErrorCodInvalidAudioSyncUidRepeated = -1083,
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
    ByteRTCErrorCodeAbnormalServerStatus = -1084,
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
    ByteRTCErrorCodeMultiRoomUnpublishFailed = -1085,
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
    ByteRTCErrorCodeWrongAreaCode = -1086,
    /**
     * @hidden for internal use only
     * @brief notify deadlock
     */
    ByteRTCErrorCodeDeadLockNotify = -1111,
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
typedef NS_ENUM(NSInteger, ByteRTCSubscribeState) {
    /**
     * @locale zh
     * @brief 订阅/取消订阅流成功
     */
    /**
     * @locale en
     * @brief Successfully changed the subscription status
     */
    ByteRTCSubscribeStateSuccess,
    /**
     * @locale zh
     * @brief 订阅/取消订阅流失败，本地用户未在房间中
     */
    /**
     * @locale en
     * @brief Failed to change the subscription status, because you were not in the room.
     */
    ByteRTCSubscribeStateFailedNotInRoom,
    /**
     * @locale zh
     * @brief 订阅/取消订阅流失败，房间内未找到指定的音视频流
     */
    /**
     * @locale en
     * @brief Failed to change the subscription status, because the target audio/video stream was not found.
     */
    ByteRTCSubscribeStateFailedStreamNotFound,
    /**
     * @locale zh
     * @brief 超过订阅流数上限
     */
    /**
     * @locale en
     * @brief Failed to change the subscription status, because the number of streams you have subscribed to has exceeded the limit.
     */
    ByteRTCSubscribeStateFailedOverLimit,
};

/**
 * @locale zh
 * @type errorcode
 * @brief 回调警告码。<br>
 *        警告码说明 SDK 内部遇到问题正在尝试恢复。警告码仅作通知。
 */
/**
 * @locale en
 * @type errorcode
 * @brief  Callback warning code. The warning code indicates that there is a problem within the SDK and is trying to recover. Warning codes are for notification only.
 */
typedef NS_ENUM(NSInteger, ByteRTCWarningCode) {
    /**
     * @locale zh
     * @deprecated since 3.45 and will be delted in 3.51.
     */
    /**
     * @locale en
     * @deprecated since 3.45 and will be delted in 3.51.
     */
    ByteRTCWarningCodeGetRoomFailed              = -2000,
    /**
     * @locale zh
     * @brief 进房失败。  <br>
     *        初次进房或者由于网络状况不佳断网重连时，由于服务器错误导致进房失败。SDK 会自动重试进房。
     */
    /**
     * @locale en
     * @brief Failed to enter the room.   <br>
     *        When entering the room for the first time or when the network is disconnected and reconnected due to poor network conditions, entering the room failed due to a server error. The SDK automatically retries the room.
     */
    ByteRTCWarningCodeJoinRoomFailed             = -2001,
    /**
     * @locale zh
     * @brief 发布音视频流失败。<br>
     *        当你在所在房间中发布音视频流时，由于服务器错误导致发布失败。SDK 会自动重试发布。
     */
    /**
     * @locale en
     * @brief Release audio & video stream failed.<br>
     *        When you publish audio & video streams in your room, the release fails due to a server error. The SDK automatically retries the release.
     */
    ByteRTCWarningCodePublishStreamFailed        = -2002,
    /**
     * @locale zh
     * @brief 订阅音视频流失败。<br>
     *        当前房间中找不到订阅的音视频流导致订阅失败。SDK 会自动重试订阅，若仍订阅失败则建议你退出重试。
     */
    /**
     * @locale en
     * @brief Subscription to audio & video stream failed.<br>
     *        The subscription failed because the audio & video stream for the subscription was not found in the current room. The SDK will automatically retry the subscription. If the subscription fails, it is recommended that you exit the retry.
     */
    ByteRTCWarningCodeSubscribeStreamFailed404  = -2003,
    /**
     * @locale zh
     * @brief 订阅音视频流失败。<br>
     *        当你订阅所在房间中的音视频流时，由于服务器错误导致订阅失败。SDK 会自动重试订阅。
     */
    /**
     * @locale en
     * @brief Subscription to audio & video stream failed.<br>
     *        When you subscribe to audio & video streams in your room, the subscription fails due to a server error. The SDK automatically retries the subscription.
     */
    ByteRTCWarningCodeSubscribeStreamFailed5xx  = -2004,
    /**
     * @locale zh
     * @hidden currently not available
     * @brief 函数调用顺序错误，当前代码中未使用。
     */
    /**
     * @locale en
     * @hidden currently not available
     * @brief  Function call order is wrong and is not used in the current code.
     */
    ByteRTCWarningCodeInvokeError = -2005,
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
    ByteRTCWarningCodeInvalidExpectMediaServerAddress = -2007,
    /**
     * @locale zh
     * @brief 当调用 `setUserVisibility:` 将自身可见性设置为 false 后，再尝试发布流会触发此警告。  
     */
    /**
     * @locale en
     * @brief This warning is triggered when you call `setUserVisibility:`to set yourself unvisible to others before attempting to publish the flow. 
     */
    ByteRTCWarningCodePublishStreamForbiden = -2009,
    /**
     * @locale zh
     * @deprecated since 3.45 and will be delted in 3.51.
     * @brief 自动订阅模式未关闭时，尝试开启手动订阅模式会触发此警告。  <br>
     *        你需在进房前关闭自动订阅模式，再调用 subscribeStream:mediaStreamType:{@link #ByteRTCRoom#subscribeStream:mediaStreamType:} 方法手动订阅音视频流。
     */
    /**
     * @locale en
     * @deprecated since 3.45 and will be delted in 3.51.
     * @brief When automatic subscription mode is not turned off, trying to turn on manual subscription mode will trigger this warning.   <br>
     *        You need to turn off the automatic subscription mode before entering the room, and then call the subscribeStream:mediaStreamType:{@link #ByteRTCRoom#subscribeStream:mediaStreamType:} method to manually subscribe to the audio & video stream.
     */
    ByteRTCWarningCodeSubscribeStreamForbiden = -2010,
    /**
     * @locale zh
     * @brief 发送自定义广播消息失败，当前你未在房间中。
     */
    /**
     * @locale en
     * @brief Sending a custom broadcast message failed, you are not currently in the room.
     */
    ByteRTCWarningCodeSendCustomMessage = -2011,
    /**
     * @locale zh
     * @brief 当房间内人数超过 500 人时，停止向房间内已有用户发送 `rtcEngine:onUserJoined:elapsed:` 和 `rtcEngine:onUserLeave:reason:` 回调，并通过广播提示房间内所有用户。
     */
    /**
     * @locale en
     * @brief When the number of people in the room exceeds 500, stop sending `rtcEngine:onUserJoined:elapsed:` and `rtcEngine:onUserLeave:reason:` callbacks to existing users in the room, and prompt all users in the room via broadcast.
     */
    ByteRTCWarningCodeCodeUserNotifyStop = -2013,
    /**
     * @locale zh
     * @brief 用户已经在其他房间发布过流，或者用户正在发布公共流。
     */
    /**
     * @locale en
     * @brief User had published in other room.
     */
    ByteRTCWarningCodeUserInPublish = -2014,
    /**
     * @locale zh
     * @deprecated since 3.45 and will be delted in 3.51.
     * @brief 同样roomid的房间已经存在了
     */
    /**
     * @locale en
     * @deprecated since 3.45 and will be delted in 3.51.
     * @brief there is a room with the same roomId
     */
    ByteRTCWarningCodeRoomAlreadyExist = -2015,

    /**
     * @locale zh
     * @brief 已存在相同 roomId 的房间，新创建的房间实例已替换旧房间实例。
     */
    /**
     * @locale en
     * @brief A room with the same roomId already exists. The newly created room instance has replaced the old one.
     */
    ByteRTCWarningCodeOldRoomBeenReplaced = -2016,

    /**
     * @locale zh
     * @brief 当前正在进行回路测试，该接口调用无效
     */
    /**
     * @locale en
     * @brief this inteface has been banned for the engine is in echo testing mode
     */
    ByteRTCWarningCodeInEchoTestMode = -2017,
    /**
     * @locale zh
     * @brief 摄像头权限异常，当前应用没有获取摄像头权限
     */
    /**
     * @locale en
     * @brief The camera permission is abnormal, the current application does not get the camera permission
     */
    ByteRTCWarningCodeNoCameraPermission            = -5001,
    /**
     * @locale zh
     * @brief 已在 3.33 版本中废弃，使用 ByteRTCMediaDeviceError{@link #ByteRTCMediaDeviceError}.ByteRTCMediaDeviceErrorDeviceNoPermission 代替。<br>
     *        麦克风权限异常，当前应用没有获取麦克风权限。
     * @deprecated since 3.33 and will be delted in 3.51, use ByteRTCMediaDeviceError{@link #ByteRTCMediaDeviceError}.ByteRTCMediaDeviceErrorDeviceNoPermission instead.
     */
    /**
     * @locale en
     * @brief Deprecated since 3.45. Please use ByteRTCMediaDeviceError{@link #ByteRTCMediaDeviceError}.ByteRTCMediaDeviceErrorDeviceNoPermission instead.<br>
     *        The microphone permission is abnormal, the current application does not get microphone permission.
     * @deprecated since 3.45 and will be delted in 3.51, use ByteRTCMediaDeviceError{@link #ByteRTCMediaDeviceError}.ByteRTCMediaDeviceErrorDeviceNoPermission instead.
     */
    ByteRTCWarningCodeNoMicrophonePermission        = -5002,
    /**
     * @locale zh
     * @brief 已在 3.33 版本中废弃，使用 ByteRTCMediaDeviceError{@link #ByteRTCMediaDeviceError}.ByteRTCMediaDeviceErrorDeviceFailure 代替。<br>
     *        音频采集设备启动失败。  <br>
     *        启动音频采集设备失败，当前设备可能被其他应用占用。
     * @deprecated since 3.33 and will be delted in 3.51, use ByteRTCMediaDeviceError{@link #ByteRTCMediaDeviceError}.ByteRTCMediaDeviceErrorDeviceFailure instead.
     */
    /**
     * @locale en
     * @brief Deprecated since 3.45. Please use ByteRTCMediaDeviceError{@link #ByteRTCMediaDeviceError}.ByteRTCMediaDeviceErrorDeviceFailure instead.<br>
     *        The audio capture device failed to start.   <br>
     *        Failed to start the audio capture device, the current device may be occupied by other applications.
     * @deprecated since 3.45 and will be delted in 3.51, use ByteRTCMediaDeviceError{@link #ByteRTCMediaDeviceError}.ByteRTCMediaDeviceErrorDeviceFailure instead.
     */
    ByteRTCWarningCodeAudioDeviceManagerRecordingStartFail     = -5003,
    /**
     * @locale zh
     * @brief 已在 3.33 版本中废弃，使用 ByteRTCMediaDeviceError{@link #ByteRTCMediaDeviceError}.ByteRTCMediaDeviceErrorDeviceFailure 代替.<br>
     *        音频播放设备启动失败警告。  <br>
     *        可能由于系统资源不足，或参数错误。
     * @deprecated since 3.33 and will be delted in 3.51, use ByteRTCMediaDeviceError{@link #ByteRTCMediaDeviceError}.ByteRTCMediaDeviceErrorDeviceFailure instead.
     */
    /**
     * @locale en
     * @brief Deprecated since 3.45. Please use ByteRTCMediaDeviceError{@link #ByteRTCMediaDeviceError}.ByteRTCMediaDeviceErrorDeviceFailure instead.<br>
     *        Audio playback device startup failure warning.   <br>
     *        It may be due to insufficient system resources or wrong parameters.
     * @deprecated since 3.45 and will be delted in 3.51, use ByteRTCMediaDeviceError{@link #ByteRTCMediaDeviceError}.ByteRTCMediaDeviceErrorDeviceFailure instead.
     */
    ByteRTCWarningCodeAudioDeviceManagerPlayoutStartFail = -5004,
    /**
     * @locale zh
     * @brief 已在 3.33 版本中废弃，使用 ByteRTCMediaDeviceError{@link #ByteRTCMediaDeviceError}.ByteRTCMediaDeviceErrorDeviceNotFound 代替。<br>
     *        无可用音频采集设备。  <br>
     *        启动音频采集设备失败，请插入可用的音频采集设备。
     * @deprecated since 3.33 and will be delted in 3.51, use ByteRTCMediaDeviceError{@link #ByteRTCMediaDeviceError}.ByteRTCMediaDeviceErrorDeviceNotFound instead.
     */
    /**
     * @locale en
     * @brief Deprecated since 3.45. Please use ByteRTCMediaDeviceError{@link #ByteRTCMediaDeviceError}.ByteRTCMediaDeviceErrorDeviceNotFound instead.<br>
     *        No audio acquisition equipment available.   <br>
     *        Failed to start the audio capture device, please insert the available audio capture device.
     * @deprecated since 3.45 and will be delted in 3.51, use ByteRTCMediaDeviceError{@link #ByteRTCMediaDeviceError}.ByteRTCMediaDeviceErrorDeviceNotFound instead.
     */
    ByteRTCWarningCodeNoRecordingDevice = -5005,
    /**
     * @locale zh
     * @brief 已在 3.33 版本中废弃，使用 ByteRTCMediaDeviceError{@link #ByteRTCMediaDeviceError}.ByteRTCMediaDeviceErrorDeviceNotFound 代替。<br>
     *        无可用音频播放设备。  <br>
     *        启动音频播放设备失败，请插入可用的音频播放设备。
     * @deprecated since 3.33 and will be delted in 3.51, use ByteRTCMediaDeviceError{@link #ByteRTCMediaDeviceError}.ByteRTCMediaDeviceErrorDeviceNotFound instead.
     */
    /**
     * @locale en
     * @brief Deprecated since 3.45. Please use ByteRTCMediaDeviceError{@link #ByteRTCMediaDeviceError}.ByteRTCMediaDeviceErrorDeviceNotFound instead.<br>
     *        No audio playback device available.   <br>
     *        Failed to start the audio playback device, please insert the available audio playback device.
     * @deprecated since 3.45 and will be delted in 3.51, use ByteRTCMediaDeviceError{@link #ByteRTCMediaDeviceError}.ByteRTCMediaDeviceErrorDeviceNotFound instead.
     */
    ByteRTCWarningCodeNoPlayoutDevice = -5006,
    /**
     * @locale zh
     * @brief 已在 3.33 版本中废弃，使用 ByteRTCMediaDeviceWarning{@link #ByteRTCMediaDeviceWarning}.ByteRTCMediaDeviceWarningCaptureSilence 代替。<br>
     *        当前音频设备没有采集到有效的声音数据，请检查更换音频采集设备。
     * @deprecated since 3.33 and will be delted in 3.51, use ByteRTCMediaDeviceWarning{@link #ByteRTCMediaDeviceWarning}.ByteRTCMediaDeviceWarningCaptureSilence instead.
     */
    /**
     * @locale en
     * @brief Deprecated since 3.45. Please use ByteRTCMediaDeviceWarning{@link #ByteRTCMediaDeviceWarning}.ByteRTCMediaDeviceWarningCaptureSilence instead.<br>
     *        The current audio equipment has not collected valid sound data, please check and replace the audio acquisition equipment.
     * @deprecated since 3.45 and will be delted in 3.51, use ByteRTCMediaDeviceWarning{@link #ByteRTCMediaDeviceWarning}.ByteRTCMediaDeviceWarningCaptureSilence instead.
     */
    ByteRTCWarningCodeRecordingSilence = -5007,
    /**
     * @locale zh
     * @brief 已在 3.33 版本中废弃，使用 ByteRTCMediaDeviceWarning{@link #ByteRTCMediaDeviceWarning}.ByteRTCMediaDeviceWarningOperationDenied 代替。<br>
     *        媒体设备误操作警告。  <br>
     *        使用自定义采集时，不可调用内部采集开关，调用时触发此警告。
     * @deprecated since 3.33 and will be delted in 3.51, use ByteRTCMediaDeviceWarning{@link #ByteRTCMediaDeviceWarning}.ByteRTCMediaDeviceWarningOperationDenied instead.
     */
    /**
     * @locale en
     * @brief Deprecated since 3.45. Please use ByteRTCMediaDeviceWarning{@link #ByteRTCMediaDeviceWarning}.ByteRTCMediaDeviceWarningOperationDenied instead.<br>
     *        Media device misoperation warning.   <br>
     *        When using custom acquisition, the internal acquisition switch cannot be called, and this warning is triggered when called.
     * @deprecated since 3.45 and will be delted in 3.51, use ByteRTCMediaDeviceWarning{@link #ByteRTCMediaDeviceWarning}.ByteRTCMediaDeviceWarningOperationDenied instead.
     */
    ByteRTCWarningCodeMediaDeviceOperationDennied = -5008,
    /**
     * @locale zh
     * @brief 不支持在 `publishScreen` 之后，通过 `setScreenAudioSourceType` 设置屏幕音频采集类型
     */
    /**
     * @locale en
     * @brief Setting the screen audio capture type via `setScreenAudioSourceType` after `publishScreen` is not supported
     */
    ByteRTCWarningSetScreenAudioSourceTypeFailed = -5009,

    /**
     * @locale zh
     * @brief 不支持在 `publishScreen` 之后，通过 `setScreenAudioStreamIndex` 设置屏幕音频混流类型
     */
    /**
     * @locale en
     * @brief Setting the screen audio mix type via `setScreenAudioStreamIndex` after `publishScreen` is not supported
     */
    ByteRTCWarningSetScreenAudioStreamIndexFailed = -5010,
    /**
     * @locale zh
     * @brief 设置语音音高不合法
     */
    /**
     * @locale en
     * @brief Invalid pitch value setting
     */
    ByteRTCWarningInvalidVoicePitch = -5011,
    /**
     * @locale zh
     * @brief 外部音频源新旧接口混用
     */
    /**
     * @locale en
     * @brief Mixed use of old and new interfaces for external audio sources
     */
    ByteRTCWarningInvalidCallForExtAudio = -5013,
    /**
     * @locale zh
     * @brief 指定的内部渲染画布句柄无效。  <br>
     *        当你调用 setLocalVideoCanvas:withCanvas:{@link #ByteRTCVideo#setLocalVideoCanvas:withCanvas:} 或 setRemoteVideoCanvas:withCanvas:{@link #ByteRTCVideo#setRemoteVideoCanvas:withCanvas:} 时指定了无效的画布句柄，触发此回调。
     */
    /**
     * @locale en
     * @brief The specified internal rendering canvas handle is invalid.   <br>
     *        An invalid canvas handle is specified when you call setLocalVideoCanvas:withCanvas:{@link #ByteRTCVideo#setLocalVideoCanvas:withCanvas:} or setRemoteVideoCanvas:withCanvas:{@link #ByteRTCVideo#setRemoteVideoCanvas:withCanvas:}, triggering this callback.
     */
    ByteRTCWarningCodeInvalidCanvasHandle = -6001,

    /**
     * @locale zh
     * @brief [音频技术](https://www.volcengine.com/docs/6489/71986) SDK 鉴权失效。联系技术支持人员。
     */
    /**
     * @locale en
     * @brief Authorization failure for [BytePlus Audio SDK](https://go.byteplus.com/audio-sdk). Contact the technical supporters.
     */
    ByteRTCWarningCodeInvaildSamiAppkeyORToken = -7002,

    /**
     * @locale zh
     * @brief [音频技术](https://www.volcengine.com/docs/6489/71986) 资源加载失败。传入正确的 DAT 路径，或联系技术支持人员。
     */
    /**
     * @locale en
     * @brief Failure to get the resource for [BytePlus Audio SDK](https://go.byteplus.com/audio-sdk). Input the right DAT path or contact the technical supporters.
     */
    ByteRTCWarningCodeInvaildSamiResourcePath = -7003,

    /**
     * @locale zh
     * @brief [音频技术](https://www.volcengine.com/docs/6489/71986) 库加载失败。使用正确的库，或联系技术支持人员。
     */
    /**
     * @locale en
     * @brief Failure to load the library for [BytePlus Audio SDK](https://go.byteplus.com/audio-sdk). Use right library or contact the technical supporters.
     */
    ByteRTCWarningCodeLoadSamiLibraryFailed = -7004,

    /**
     * @locale zh
     * @brief [音频技术](https://www.volcengine.com/docs/6489/71986) 不支持此音效。联系技术支持人员。
     */
    /**
     * @locale en
     * @brief The audio effect is not supported by [BytePlus Audio SDK](https://go.byteplus.com/audio-sdk). Contact the technical supporters.
     */
    ByteRTCWarningCodeInvaildSamiEffectType = -7005
};

/**
 * @locale zh
 * @type keytype
 * @brief 性能相关告警的原因
 */
/**
 * @locale en
 * @type keytype
 * @brief Reasons for performance-related alarms
 */
typedef NS_ENUM(NSInteger, ByteRTCPerformanceAlarmReason) {
    /**
     * @locale zh
     * @brief 网络原因差，造成了发送性能回退。仅在开启发送性能回退时，会收到此原因。
     */
    /**
     * @locale en
     * @brief The poor network causes the transmission performance to fall back. This reason is only received when sending performance fallback is turned on.
     */
    ByteRTCPerformanceAlarmReasonBandwidthFallback = 0,
    /**
     * @locale zh
     * @brief 网络性能恢复，发送性能回退恢复。仅在开启发送性能回退时，会收到此原因。
     */
    /**
     * @locale en
     * @brief Network performance recovery, transmission performance rollback recovery. This reason is only received when sending performance fallback is turned on.
     */
    ByteRTCPerformanceAlarmReasonBandwidthResumed = 1,
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
    ByteRTCPerformanceAlarmReasonFallback = 2,
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
    ByteRTCPerformanceAlarmReasonResumed = 3,
};

/**
 * @locale zh
 * @type keytype
 * @brief 性能回退的模式
 */
/**
 * @locale en
 * @type keytype
 * @brief  Mode of performance fallback
 */
typedef NS_ENUM(NSInteger, ByteRTCPerformanceAlarmMode) {
    /**
     * @locale zh
     * @brief 未开启发布性能回退
     */
    /**
     * @locale en
     * @brief Not enabled Release performance fallback
     */
    ByteRTCPerformanceAlarmModeNormal = 0,
    /**
     * @locale zh
     * @brief 已开启发布性能回退
     */
    /**
     * @locale en
     * @brief Open Release Performance Rollback
     */
    ByteRTCPerformanceAlarmModeSimulcast = 1,
};

/**
 * @locale zh
 * @hidden
 * @deprecated since 3.45 and will be deleted in 3.51.
 * @type keytype
 * @brief 设置引擎工作模式
 */
/**
 * @locale en
 * @hidden
 * @deprecated since 3.45 and will be deleted in 3.51.
 * @type keytype
 * @brief  Set engine working mode
 */
typedef NS_ENUM(NSUInteger, ByteRTCMode) {
    /**
     * @locale zh
     * @brief 通用模式，该模式下只能进行普通会议模式的语音通话，开启自动发布订阅。
     */
    /**
     * @locale en
     * @brief General mode, in which only voice calls in normal meeting mode can be made and automatic subscription publishing can be started.
     */
    ByteRTCModeGeneral = 0,
    /**
     * @locale zh
     * @brief 游戏语音模式，该模式下关闭自动发布订阅，会按照游戏业务的策略进行主动发布订阅语音。
     */
    /**
     * @locale en
     * @brief The game voice mode, in which automatic subscription publishing is turned off, will actively publish subscription voice according to the strategy of the game business.
     */
    ByteRTCModeLocalAudio = 1,
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
typedef NS_ENUM(NSUInteger, ByteRTCPublishFallbackOption) {
    /**
     * @locale zh
     * @brief 上行网络不佳或设备性能不足时，不对音视频流作回退处理。默认设置。
     */
    /**
     * @locale en
     * @brief Default setting. No fallback is allowed under limited network conditions.
     */
    ByteRTCPublishFallbackOptionDisabled = 0,
    /**
     * @locale zh
     * @brief 上行网络不佳或设备性能不足时，发布的视频流会从大流到小流依次降级，直到与当前网络性能匹配，具体降级规则参看[性能回退](https://www.volcengine.com/docs/6348/70137)文档。
     */
    /**
     * @locale en
     * @brief Under limited network conditions, the video streams that you published will degrade sequentially from the highest-quality stream to the lowest-quality stream until it can match current network conditions.
     */
    ByteRTCPublishFallbackOptionSimulcast = 1,
};

/**
 * @locale zh
 * @hidden
 * @deprecated since 3.26 and will be deleted in 3.51, use RoomConfig in joinRoom API instead.
 * @type keytype
 * @brief 订阅模式选项。
 */
/**
 * @locale en
 * @hidden
 * @deprecated since 3.45 and will be deleted in 3.51, use RoomConfig in joinRoom API instead.
 * @type keytype
 * @brief  Subscription mode option.
 */
typedef NS_ENUM(NSUInteger, ByteRTCSubscribeMode) {
    /**
     * @locale zh
     * @brief 自动订阅模式。SDK 会自动为你订阅房间中的每一路流。  
     */
    /**
     * @locale en
     * @brief Automatic subscription mode. The SDK  automatically subscribes to every stream in the room for you. 
     */
    ByteRTCSubscribeModeAuto = 0,
    /**
     * @locale zh
     * @brief 手动订阅模式。SDK 不自动订阅房间内的音视频流。你应根据需要调用 `subscribeStream` 方法手动订阅其他用户发布的音视频流。
     */
    /**
     * @locale en
     * @brief Manual subscription mode. The SDK  does not automatically subscribe to in-room audio & video streams. You should call the `subscribeStream` to manually subscribe to audio & video streams posted by other users as needed.
     */
    ByteRTCSubscribeModeManual = 1
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
typedef NS_ENUM(NSUInteger, ByteRTCSubscribeFallbackOption) {
    /**
     * @locale zh
     * @brief 下行网络不佳或设备性能不足时，不对音视频流作回退处理。默认设置。
     */
    /**
     * @locale en
     * @brief Default setting. No fallback is allowed under limited network conditions.
     */
    ByteRTCSubscribeFallbackOptionDisabled = 0,
    /**
     * @locale zh
     * @brief 下行网络不佳或设备性能不足时，对视频流做降级处理，具体降级规则参看[音视频流回退](70137)。 <br>
     *        该设置仅对发布端调用 `enableSimulcastMode:` 开启发送多路流功能的情况生效。
     */
    /**
     * @locale en
     * @brief The resolution of currently subscribed video stream will be reduced under limited network conditions, see [Stream Fallback](70137) for details.  <br>
     *        You can only select this setting after the stream publisher calls `enableSimulcastMode:` to enable the mode of publishing multiple streams, otherwise no fallback will occur.
     */
    ByteRTCSubscribeFallbackOptionVideoStreamLow = 1,
    /**
     * @locale zh
     * @brief 下行网络不佳或设备性能不足时，先对视频流做回退处理。当网络状况不满足接收弱流时，则自动取消接收视频，仅接收音频。<br>
     *        该设置仅对发布端调用 `enableSimulcastMode:` 开启发送多路流功能的情况生效。
     */
    /**
     * @locale en
     * @brief The resolution of currently subscribed video stream will be reduced first under limited network conditions. When the network condition is not sufficient to receive the minimum resolution stream, the video is automatically cancelled and only the audio is received. <br>
     *        You can only select this setting after the stream publisher calls `enableSimulcastMode:` to enable the mode of publishing multiple streams, otherwise no fallback will occur.
     */
    ByteRTCSubscribeFallbackOptionAudioOnly = 2,
};

/**
 * @locale zh
 * @type keytype
 * @brief 远端用户优先级。在性能不足需要回退时，会先回退优先级低的用户的音视频流
 */
/**
 * @locale en
 * @type keytype
 * @brief Priority of the publisher. When a user encounters performance insufficiency of either the network or the device, the media stream  will fall back in the ascending order of `RemoteUserPriority`.
 */
typedef NS_ENUM(NSUInteger, ByteRTCRemoteUserPriority) {
    /**
     * @locale zh
     * @brief 用户优先级为低，默认值
     */
    /**
     * @locale en
     * @brief Low, the default
     */
    ByteRTCRemoteUserPriorityLow = 0,
    /**
     * @locale zh
     * @brief 用户优先级为正常
     */
    /**
     * @locale en
     * @brief Medium
     */
    ByteRTCRemoteUserPriorityMedium = 100,
    /**
     * @locale zh
     * @brief 用户优先级为高
     */
    /**
     * @locale en
     * @brief High
     */
    ByteRTCRemoteUserPriorityHigh = 200,
};

/**
 * @locale zh
 * @type keytype
 * @brief 本地用户订阅的远端流触发回退策略的原因。
 */
/**
 * @locale en
 * @type keytype
 * @brief Reason of the Fallback or reverting from a Fallback of the subscribed stream or the publishing stream
 */
typedef NS_ENUM(NSInteger, ByteRTCFallbackOrRecoverReason) {
    /**
     * @locale zh
     * @brief 其他原因，非带宽和性能原因引起的回退或恢复。默认值
     */
    /**
     * @locale en
     * @brief The default: Fallback due to an unknown reason that is neither infufficienclt bandwidth of the network nor poor-performance of the device
     */
    ByteRTCFallbackOrRecoverReasonUnknown = -1,
    /**
     * @locale zh
     * @brief 由带宽不足导致的订阅端音视频流回退。
     */
    /**
     * @locale en
     * @brief Fallback of the subscribed stream due to insufficient bandwidth of the network
     */
    ByteRTCFallbackOrRecoverReasonSubscribeFallbackByBandwidth = 0,
    /**
     * @locale zh
     * @brief 由性能不足导致的订阅端音视频流回退。
     */
    /**
     * @locale en
     * @brief Fallback of the subscribed stream for poor-performance of the device
     */
    ByteRTCFallbackOrRecoverReasonSubscribeFallbackByPerformance = 1,
    /**
     * @locale zh
     * @brief 由带宽恢复导致的订阅端音视频流恢复。
     */
    /**
     * @locale en
     * @brief Reverting from a Fallback of the subscribed stream due to the recovery of the network bandwidth
     */
    ByteRTCFallbackOrRecoverReasonSubscribeRecoverByBandwidth = 2,
    /**
     * @locale zh
     * @brief 由性能恢复导致的订阅端音视频流恢复。
     */
    /**
     * @locale en
     * @brief Reverting from a Fallback of the subscribed stream due to the amelioration of the device performance
     */
    ByteRTCFallbackOrRecoverReasonSubscribeRecoverByPerformance = 3,
    /**
     * @locale zh
     * @brief 由带宽不足导致的发布端音视频流回退。
     */
    /**
     * @locale en
     * @brief Fallback of the publishing stream due to Insufficient bandwidth of the network
     */
    ByteRTCFallbackOrRecoverReasonPublishFallbackByBandwidth = 4,
    /**
     * @locale zh
     * @brief 由性能不足导致的发布端音视频流回退。
     */
    /**
     * @locale en
     * @brief Fallback of the publishing stream due to poor-performance of the device
     */
    ByteRTCFallbackOrRecoverReasonPublishFallbackByPerformance = 5,
    /**
     * @locale zh
     * @brief 由带宽恢复导致的发布端音视频流恢复。
     */
    /**
     * @locale en
     * @brief Reverting from a Fallback of the publishing stream due to the recovery of the network bandwidth
     */
    ByteRTCFallbackOrRecoverReasonPublishRecoverByBandwidth = 6,
    /**
     * @locale zh
     * @brief 由性能恢复导致的发布端音视频流恢复。
     */
    /**
     * @locale en
     * @brief Reverting from a Fallback of the publishing stream due to the amelioration of the device performance
     */
    ByteRTCFallbackOrRecoverReasonPublishRecoverByPerformance = 7,
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
typedef NS_ENUM(NSInteger, ByteRTCLocalAudioStreamState) {
    /**
     * @locale zh
     * @brief 本地音频默认初始状态。<br>
     *        麦克风停止工作时回调该状态，对应错误码 ByteRTCLocalAudioStreamError{@link #ByteRTCLocalAudioStreamError} 中的 ByteRTCLocalAudioStreamErrorOk
     */
    /**
     * @locale en
     * @brief The default initial state of the local audio.<br>
     *         Callback to this state when the microphone stops working, corresponding to the error code ByteRTCLocalAudioStreamError{@link #ByteRTCLocalAudioStreamError} in ByteRTCLocalAudioStreamErrorOk
     */
    ByteRTCLocalAudioStreamStateStopped = 0,
    /**
     * @locale zh
     * @brief 本地音频录制设备启动成功。<br>
     *        采集到音频首帧时回调该状态，对应错误码 ByteRTCLocalAudioStreamError{@link #ByteRTCLocalAudioStreamError} 中的 ByteRTCLocalAudioStreamErrorOk
     */
    /**
     * @locale en
     * @brief The local audio recording device started successfully.<br>
     *         Callback to this state when the first audio frame is collected, corresponding to the error code ByteRTCLocalAudioStreamError{@link #ByteRTCLocalAudioStreamError} in ByteRTCLocalAudioStreamErrorOk
     */
    ByteRTCLocalAudioStreamStateRecording = 1,
    /**
     * @locale zh
     * @brief 本地音频首帧编码成功。<br>
     *        音频首帧编码成功时回调该状态，对应错误码 ByteRTCLocalAudioStreamError{@link #ByteRTCLocalAudioStreamError} 中的 ByteRTCLocalAudioStreamErrorOk
     */
    /**
     * @locale en
     * @brief The first frame of the local audio was successfully encoded.<br>
     *         Callback to this state when the audio first frame encoding is successful, corresponding to the error code ByteRTCLocalAudioStreamError{@link #ByteRTCLocalAudioStreamError} in ByteRTCLocalAudioStreamErrorOk
     */
    ByteRTCLocalAudioStreamStateEncoding = 2,
    /**
     * @locale zh
     * @brief  本地音频启动失败，在以下时机回调该状态：  <br>
     *       + 本地录音设备启动失败，对应错误码 ByteRTCLocalAudioStreamError{@link #ByteRTCLocalAudioStreamError} 中的 ByteRTCLocalAudioStreamErrorRecordFailure  <br>
     *       + 检测到没有录音设备权限，对应错误码 ByteRTCLocalAudioStreamError{@link #ByteRTCLocalAudioStreamError} 中的 ByteRTCLocalAudioStreamErrorDeviceNoPermission <br>
     *       + 音频编码失败，对应错误码 ByteRTCLocalAudioStreamError{@link #ByteRTCLocalAudioStreamError} 中的 ByteRTCLocalAudioStreamError 
     */
    /**
     * @locale en
     * @brief  The local audio startup failed, and the status is called back at the following times:   <br>
     *        + The local recording device failed to start, corresponding to the error code ByteRTCLocalAudioStreamError{@link #ByteRTCLocalAudioStreamError} ByteRTCLocalAudioStreamErrorRecordFailure <br>
     *        + No recording device permission was detected, corresponding to the error code ByteRTCLocalAudioStreamError{@link #ByteRTCLocalAudioStreamError} ByteRTCLocalAudioStreamErrorDeviceNoPermission <br>
     *        + The audio encoding failed, corresponding to the error code ByteRTCLocalAudioStreamError{@link #ByteRTCLocalAudioStreamError} in ByteRTCLocalAudioStreamError 
     */
    ByteRTCLocalAudioStreamStateFailed = 3,
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
typedef NS_ENUM(NSInteger, ByteRTCLocalAudioStreamError) {
    /**
     * @locale zh
     * @brief 本地音频状态正常
     */
    /**
     * @locale en
     * @brief Local audio status is normal
     */
    ByteRTCLocalAudioStreamErrorOk = 0,
    /**
     * @locale zh
     * @brief 本地音频出错原因未知
     */
    /**
     * @locale en
     * @brief Local audio error cause unknown
     */
    ByteRTCLocalAudioStreamErrorFailure = 1,
    /**
     * @locale zh
     * @brief 没有权限启动本地音频录制设备
     */
    /**
     * @locale en
     * @brief No permission to start local audio recording device
     */
    ByteRTCLocalAudioStreamErrorDeviceNoPermission = 2,
    /**
     * @locale zh
     * @hidden currently not available
     * @brief 本地音频录制设备已经在使用中
     * @note 该错误码暂未使用
     */
    /**
     * @locale en
     * @hidden currently not available
     * @brief The local audio recording device is already in use
     * @note The error code is not yet in use
     */
    ByteRTCLocalAudioStreamErrorDeviceBusy = 3,
    /**
     * @locale zh
     * @brief 本地音频录制失败，建议你检查录制设备是否正常工作
     */
    /**
     * @locale en
     * @brief Local audio recording failed, it is recommended that you check whether the recording device is working properly
     */
    ByteRTCLocalAudioStreamErrorRecordFailure = 4,
    /**
     * @locale zh
     * @brief 本地音频编码失败
     */
    /**
     * @locale en
     * @brief Local audio encoding failed
     */
    ByteRTCLocalAudioStreamErrorEncodeFailure = 5,
    /**
     * @locale zh
     * @brief 没有可用的音频录制设备
     */
    /**
     * @locale en
     * @brief No audio recording equipment available
     */
    ByteRTCLocalAudioStreamErrorNoRecordingDevice = 6
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
typedef NS_ENUM(NSInteger, ByteRTCLocalVideoStreamState) {
    /**
     * @locale zh
     * @brief 本地视频默认初始状态<br>
     *        摄像头停止工作时回调该状态，对应错误码 ByteRTCLocalVideoStreamError{@link #ByteRTCLocalVideoStreamError} 中的 ByteRTCLocalVideoStreamErrorOk
     */
    /**
     * @locale en
     * @brief Local video default initial state<br>
     *         Callback the state when the camera stops working, corresponding to the error code ByteRTCLocalVideoStreamError{@link #ByteRTCLocalVideoStreamError} ByteRTCLocalVideoStreamErrorOk
     */
    ByteRTCLocalVideoStreamStateStopped = 0,
    /**
     * @locale zh
     * @brief 本地视频录制设备启动成功<br>
     *        采集到视频首帧时回调该状态，对应错误码 ByteRTCLocalVideoStreamError{@link #ByteRTCLocalVideoStreamError} 中的 ByteRTCLocalVideoStreamErrorOk
     */
    /**
     * @locale en
     * @brief The local video recording device starts successfully<br>
     *         Callback the state when the first frame of the video is collected, corresponding to the error code ByteRTCLocalVideoStreamError{@link #ByteRTCLocalVideoStreamError} ByteRTCLocalVideoStreamErrorOk
     */
    ByteRTCLocalVideoStreamStateRecording = 1,
    /**
     * @locale zh
     * @brief 本地视频首帧编码成功<br>
     *        本地视频首帧编码成功时回调该状态，对应错误码 ByteRTCLocalVideoStreamError{@link #ByteRTCLocalVideoStreamError} 中的 ByteRTCLocalVideoStreamErrorOk
     */
    /**
     * @locale en
     * @brief Local video first frame encoding success<br>
     *         Local video first frame encoding success callback to the state, corresponding to the error code ByteRTCLocalVideoStreamError{@link #ByteRTCLocalVideoStreamError} in ByteRTCLocalVideoStreamErrorOk
     */
    ByteRTCLocalVideoStreamStateEncoding = 2,
    /**
     * @locale zh
     * @brief  本地视频启动失败, 在以下时机回调该状态：  <br>
     *       + 本地采集设备启动失败，对应错误码 ByteRTCLocalVideoStreamError{@link #ByteRTCLocalVideoStreamError} 中的 ByteRTCLocalVideoStreamErrorCaptureFailure  <br>
     *       + 检测到没有摄像头权限，对应错误码 ByteRTCLocalVideoStreamError{@link #ByteRTCLocalVideoStreamError} 中的 ByteRTCLocalVideoStreamErrorDeviceNoPermission <br>
     *       + 视频编码失败，对应错误码 ByteRTCLocalVideoStreamError{@link #ByteRTCLocalVideoStreamError} 中的 ByteRTCLocalVideoStreamErrorEncodeFailure  
     */
    /**
     * @locale en
     * @brief  Local video startup failed,  the status is called back at the following times: <br>
     *        + The local acquisition device failed to start, corresponding to the error code ByteRTCLocalVideoStreamError{@link #ByteRTCLocalVideoStreamError} ByteRTCLocalVideoStreamErrorCaptureFailure <br>
     *        + No camera permission was detected, corresponding to the error code ByteRTCLocalVideoStreamError{@link #ByteRTCLocalVideoStreamError} ByteRTCLocalVideoStreamErrorDeviceNoPermission <br>
     *        + The video encoding failed, corresponding to the error code ByteRTCLocalVideoStreamError{@link #ByteRTCLocalVideoStreamError} in ByteRTCLocalVideoStreamErrorEncodeFailure 
     */
    ByteRTCLocalVideoStreamStateFailed = 3,
};

/**
 * @locale zh
 * @type keytype
 * @brief 本地视频状态改变时的错误码
 */
/**
 * @locale en
 * @type keytype
 * @brief  Error code when the local video state changes
 */
typedef NS_ENUM(NSInteger, ByteRTCLocalVideoStreamError) {
    /**
     * @locale zh
     * @brief 本地视频状态正常（本地视频状态改变正常时默认返回值）
     */
    /**
     * @locale en
     * @brief Local video status is normal (the default return value when the local video status changes to normal)
     */
    ByteRTCLocalVideoStreamErrorOk = 0,
    /**
     * @locale zh
     * @brief 本地视频流发布失败
     */
    /**
     * @locale en
     * @brief Local video stream publishing failed
     */
    ByteRTCLocalVideoStreamErrorFailure = 1,
    /**
     * @locale zh
     * @brief 没有权限启动本地视频采集设备
     */
    /**
     * @locale en
     * @brief No access to the local video capture device
     */
    ByteRTCLocalVideoStreamErrorDeviceNoPermission = 2,
    /**
     * @locale zh
     * @brief 本地视频采集设备已被占用
     */
    /**
     * @locale en
     * @brief Local video capture equipment is occupied
     */
    ByteRTCLocalVideoStreamErrorDeviceBusy = 3,
    /**
     * @locale zh
     * @brief 本地视频采集设备不存在或已移除
     */
    /**
     * @locale en
     * @brief The local video capture device does not exist or has been removed
     */
    ByteRTCLocalVideoStreamErrorDeviceNotFound = 4,
    /**
     * @locale zh
     * @brief 本地视频采集失败，建议检查采集设备是否正常工作
     */
    /**
     * @locale en
     * @brief Local video capture failed, it is recommended to check whether the acquisition device is working properly
     */
    ByteRTCLocalVideoStreamErrorCaptureFailure = 5,
    /**
     * @locale zh
     * @brief 本地视频编码失败
     */
    /**
     * @locale en
     * @brief Local video encoding failed
     */
    ByteRTCLocalVideoStreamErrorEncodeFailure = 6,
    /**
     * @locale zh
     * @brief 通话过程中本地视频采集设备被其他程序抢占，导致设备连接中断
     */
    /**
     * @locale en
     * @brief The local video capture device is disconnected. It is occupied by other programs during the call.
     */
    ByteRTCLocalVideoStreamErrorDeviceDisconnected = 7,
};

/**
 * @locale zh
 * @type keytype
 * @brief 用户订阅的远端音频流状态。
 */
/**
 * @locale en
 * @type keytype
 * @brief  The remote audio stream state of the user subscription.
 */
typedef NS_ENUM(NSInteger, ByteRTCRemoteAudioState) {
    /**
     * @locale zh
     * @brief  远端音频流默认初始状态，在以下时机回调该状态：  <br>
     *       + 本地用户停止接收远端音频流，对应原因是 ByteRTCRemoteAudioStateChangeReason{@link #ByteRTCRemoteAudioStateChangeReason} 中的 `ByteRTCRemoteAudioStateChangeReasonLocalMuted`  <br>
     *       + 远端用户停止发送音频流，对应原因是 ByteRTCRemoteAudioStateChangeReason{@link #ByteRTCRemoteAudioStateChangeReason} 中的 `ByteRTCRemoteAudioStateChangeReasonRemoteMuted` <br>
     *       + 远端用户离开房间，对应原因是 ByteRTCRemoteAudioStateChangeReason{@link #ByteRTCRemoteAudioStateChangeReason} 中的 `ByteRTCRemoteAudioStateChangeReasonRemoteOffline` 
     */
    /**
     * @locale en
     * @brief  The default initial state of the remote audio stream is called back at the following time:   <br>
     *        + Local users stop receiving the remote audio stream, the corresponding reason is `ByteRTCRemoteAudioStateChangeReasonLocalMuted` in ByteRTCRemoteAudioStateChangeReason{@link #ByteRTCRemoteAudioStateChangeReason} <br>
     *        + The remote user stopped sending the audio stream, the corresponding reason is `ByteRTCRemoteAudioStateChangeReasonRemoteMuted` in ByteRTCRemoteAudioStateChangeReason{@link #ByteRTCRemoteAudioStateChangeReason} <br>
     *        + The remote user left the room, the corresponding reason is `ByteRTCRemoteAudioStateChangeReasonRemoteOffline` in ByteRTCRemoteAudioStateChangeReason{@link #ByteRTCRemoteAudioStateChangeReason} 
     */
    ByteRTCRemoteAudioStateStopped = 0,
    /**
     * @locale zh
     * @brief 开始接收远端音频流首包。
     */
    /**
     * @locale en
     * @brief Start receiving the remote audio stream header.
     */
    ByteRTCRemoteAudioStateStarting = 1,
    /**
     * @locale zh
     * @brief  远端音频流正在解码，正常播放，在以下时机回调该状态：  <br>
     *       + 成功解码远端音频首帧，对应原因是 ByteRTCRemoteAudioStateChangeReason{@link #ByteRTCRemoteAudioStateChangeReason} 中的 `ByteRTCRemoteAudioStateChangeReasonLocalUnmuted` <br>
     *       + 网络由阻塞恢复正常，对应原因是 ByteRTCRemoteAudioStateChangeReason{@link #ByteRTCRemoteAudioStateChangeReason} 中的 `ByteRTCRemoteAudioStateChangeReasonNetworkRecovery` <br>
     *       + 本地用户恢复接收远端音频流，对应原因是 ByteRTCRemoteAudioStateChangeReason{@link #ByteRTCRemoteAudioStateChangeReason} 中的 `ByteRTCRemoteAudioStateChangeReasonLocalUnmuted` <br>
     *       + 远端用户恢复发送音频流，对应原因是 ByteRTCRemoteAudioStateChangeReason{@link #ByteRTCRemoteAudioStateChangeReason} 中的 `ByteRTCRemoteAudioStateChangeReasonRemoteUnmuted`
     */
    /**
     * @locale en
     * @brief  The remote audio stream is decoding and playing normally. The state will be called back at the following time:   <br>
     *        + The first frame of the remote audio is successfully decoded, and the corresponding reason is ByteRTCRemoteAudioStateChangeReason in ByteRTCRemoteAudioStateChangeReason{@link #ByteRTCRemoteAudioStateChangeReason} <br>
     *        + The network returned to normal from blocking, and the corresponding reason is ByteRTCRemoteAudioStateChangeReason in ByteRTCRemoteAudioStateChangeReason{@link #ByteRTCRemoteAudioStateChangeReason} <br>
     *        + Local users recover receiving remote audio streams due to ByteRTCRemoteAudioStateChangeReason in ByteRTCRemoteAudioStateChangeReason{@link #ByteRTCRemoteAudioStateChangeReason} <br>
     *        + The remote user resumes sending audio streams, the corresponding reason is ByteRTCRemoteAudioStateChangeReason in ByteRTCRemoteAudioStateChangeReason{@link #ByteRTCRemoteAudioStateChangeReason} 
     */
    ByteRTCRemoteAudioStateDecoding = 2,
    /**
     * @locale zh
     * @brief 远端音频流卡顿。
     */
    /**
     * @locale en
     * @brief Remote audio streaming card.
     */
    ByteRTCRemoteAudioStateFrozen = 3,
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
    ByteRTCRemoteAudioStateFailed = 4,
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
typedef NS_ENUM(NSInteger, ByteRTCRemoteAudioStateChangeReason) {
    /**
     * @locale zh
     * @brief 内部原因
     */
    /**
     * @locale en
     * @brief Internal reasons
     */
    ByteRTCRemoteAudioStateChangeReasonInternal = 0,
    /**
     * @locale zh
     * @brief 网络阻塞
     */
    /**
     * @locale en
     * @brief Network blocking
     */
    ByteRTCRemoteAudioStateChangeReasonNetworkCongestion = 1,
    /**
     * @locale zh
     * @brief 网络恢复正常
     */
    /**
     * @locale en
     * @brief Network back to normal
     */
    ByteRTCRemoteAudioStateChangeReasonNetworkRecovery = 2,
    /**
     * @locale zh
     * @brief 本地用户停止接收远端音频流
     */
    /**
     * @locale en
     * @brief Local user stops receiving remote audio stream
     */
    ByteRTCRemoteAudioStateChangeReasonLocalMuted = 3,
    /**
     * @locale zh
     * @brief 本地用户恢复接收远端音频流
     */
    /**
     * @locale en
     * @brief Local users resume receiving remote audio streams
     */
    ByteRTCRemoteAudioStateChangeReasonLocalUnmuted = 4,
    /**
     * @locale zh
     * @brief 远端用户停止发送音频流
     */
    /**
     * @locale en
     * @brief Remote user stops sending audio stream
     */
    ByteRTCRemoteAudioStateChangeReasonRemoteMuted = 5,
    /**
     * @locale zh
     * @brief 远端用户恢复发送音频流
     */
    /**
     * @locale en
     * @brief Remote user resumes sending audio stream
     */
    ByteRTCRemoteAudioStateChangeReasonRemoteUnmuted = 6,
    /**
     * @locale zh
     * @brief 远端用户离开房间
     */
    /**
     * @locale en
     * @brief Remote user leaves room
     */
    ByteRTCRemoteAudioStateChangeReasonRemoteOffline = 7,
};

/**
 * @locale zh
 * @type keytype
 * @brief 远端视频流状态
 */
/**
 * @locale en
 * @type keytype
 * @brief  Remote video stream status
 */
typedef NS_ENUM(NSInteger, ByteRTCRemoteVideoState) {
    /**
     * @locale zh
     * @brief  远端视频流默认初始状态, 在以下时机回调该状态：  <br>
     *       + 本地用户停止接收远端视频流，对应错误码 ByteRTCRemoteVideoStateChangeReason{@link #ByteRTCRemoteVideoStateChangeReason} 中的 ByteRTCRemoteVideoStateChangeReasonLocalMuted  <br>
     *       + 远端用户停止发送视频流，对应错误码 ByteRTCRemoteVideoStateChangeReason{@link #ByteRTCRemoteVideoStateChangeReason} 中的 ByteRTCRemoteVideoStateChangeReasonRemoteMuted <br>
     *       + 远端用户离开房间，对应错误码 ByteRTCRemoteVideoStateChangeReason{@link #ByteRTCRemoteVideoStateChangeReason} 中的 ByteRTCRemoteVideoStateChangeReasonRemoteOffline  
     */
    /**
     * @locale en
     * @brief  The default initial state of the remote video stream,  callback the state at the following times: <br>
     *        + The local user stops receiving the remote video stream, corresponding to the error code ByteRTCRemoteVideoStateChangeReason{@link #ByteRTCRemoteVideoStateChangeReason} ByteRTCRemoteVideoStateChangeReasonLocalMuted <br>
     *        + The remote user stops sending the video stream, corresponding to the error code ByteRTCRemoteVideoStateChangeReasonRemoteMuted <br>
     *        + The remote user leaves the room, corresponding to Error code ByteRTCRemoteVideoStateChangeReason{@link #ByteRTCRemoteVideoStateChangeReason} in ByteRTCRemoteVideoStateChangeReasonRemoteOffline 
     */
    ByteRTCRemoteVideoStateStopped = 0,
    /**
     * @locale zh
     * @brief 本地用户已接收远端视频首包 <br>
     *        收到远端视频首包时回调该状态，对应错误码 ByteRTCRemoteVideoStateChangeReason{@link #ByteRTCRemoteVideoStateChangeReason} 中的 ByteRTCRemoteVideoStateChangeReasonLocalUnmuted
     */
    /**
     * @locale en
     * @brief Local users have received the remote video header package  <br>
     *         Callback this state when the remote video header package is received, corresponding to the error code ByteRTCRemoteVideoStateChangeReason{@link #ByteRTCRemoteVideoStateChangeReason} ByteRTCRemoteVideoStateChangeReasonLocalUnmuted
     */
    ByteRTCRemoteVideoStateStarting = 1,
    /**
     * @locale zh
     * @brief  远端视频流正在解码，正常播放, 在以下时机回调该状态：  <br>
     *       + 成功解码远端视频首帧，对应错误码 ByteRTCRemoteVideoStateChangeReason{@link #ByteRTCRemoteVideoStateChangeReason} 中的 ByteRTCRemoteVideoStateChangeReasonLocalUnmuted  <br>
     *       + 网络由阻塞恢复正常，对应错误码 ByteRTCRemoteVideoStateChangeReason{@link #ByteRTCRemoteVideoStateChangeReason} 中的 ByteRTCRemoteVideoStateChangeReasonNetworkRecovery <br>
     *       + 本地用户恢复接收远端视频流，对应错误码 ByteRTCRemoteVideoStateChangeReason{@link #ByteRTCRemoteVideoStateChangeReason} 中的 ByteRTCRemoteVideoStateChangeReasonLocalUnmuted <br>
     *       + 远端用户恢复发送视频流，对应错误码 ByteRTCRemoteVideoStateChangeReason{@link #ByteRTCRemoteVideoStateChangeReason} 中的 ByteRTCRemoteVideoStateChangeReasonRemoteUnmuted  
     */
    /**
     * @locale en
     * @brief  The remote video stream is decoding and playing normally,  callback the status at the following times: <br>
     *        + ByteRTCRemoteVideoStateChangeReason{@link #ByteRTCRemoteVideoStateChangeReason} ByteRTCRemoteVideoStateChangeReasonLocalUnmuted <br>
     *        + The network returned to normal from blocking, corresponding to the error code ByteRTCRemoteVideoStateChangeReasonNetworkRecovery <br>
     *        + The local user recovers the received remote video Stream, corresponding to the error code ByteRTCRemoteVideoStateChangeReason{@link #ByteRTCRemoteVideoStateChangeReason} ByteRTCRemoteVideoStateChangeReasonLocalUnmuted <br>
     *        + The remote user resumes sending the video stream, corresponding to the error code in ByteRTCRemoteVideoStateChangeReason{@link #ByteRTCRemoteVideoStateChangeReason} 
     */
    ByteRTCRemoteVideoStateDecoding = 2,
    /**
     * @locale zh
     * @brief 远端视频流卡顿 <br>
     *        网络阻塞、丢包率等原因造成视频卡顿流时会回报该状态，对应错误码 ByteRTCRemoteVideoStateChangeReason{@link #ByteRTCRemoteVideoStateChangeReason} 中的 ByteRTCRemoteVideoStateChangeReasonNetworkCongestion
     */
    /**
     * @locale en
     * @brief Remote video streaming card  <br>
     *         Network blocking, packet loss rate and other reasons will report the status of the video card stream, corresponding to the error code ByteRTCRemoteVideoStateChangeReason{@link #ByteRTCRemoteVideoStateChangeReason} ByteRTCRemoteVideoStateChangeReasonNetworkCongestion
     */
    ByteRTCRemoteVideoStateFrozen = 3,
     /**
      * @locale zh
      * @brief 远端视频流播放失败 <br>
      *        如果内部处理远端视频流失败，则会回调该方法， 对应错误码 ByteRTCRemoteVideoStateChangeReason{@link #ByteRTCRemoteVideoStateChangeReason} 中的 ByteRTCRemoteVideoStateChangeReasonInternal
      */
     /**
      * @locale en
      * @brief The remote video stream failed to play  <br>
      *        If the internal processing of the remote video stream fails, the method will be called back,  corresponding to the error code ByteRTCRemoteVideoStateChangeReason{@link #ByteRTCRemoteVideoStateChangeReason} ByteRTCRemoteVideoStateChangeReasonInternal
      */
    ByteRTCRemoteVideoStateFailed = 4,
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
typedef NS_ENUM(NSInteger, ByteRTCRemoteVideoStateChangeReason) {
    /**
     * @locale zh
     * @brief 内部原因
     */
    /**
     * @locale en
     * @brief Internal reasons
     */
    ByteRTCRemoteVideoStateChangeReasonInternal = 0,
    /**
     * @locale zh
     * @brief 网络阻塞
     */
    /**
     * @locale en
     * @brief Network blocking
     */
    ByteRTCRemoteVideoStateChangeReasonNetworkCongestion = 1,
    /**
     * @locale zh
     * @brief 网络恢复正常
     */
    /**
     * @locale en
     * @brief Network back to normal
     */
    ByteRTCRemoteVideoStateChangeReasonNetworkRecovery = 2,
    /**
     * @locale zh
     * @brief 本地用户停止接收远端视频流或本地用户禁用视频模块
     */
    /**
     * @locale en
     * @brief Local user stops receiving remote video stream or local user disables video module
     */
    ByteRTCRemoteVideoStateChangeReasonLocalMuted = 3,
    /**
     * @locale zh
     * @brief 本地用户恢复接收远端视频流或本地用户启用视频模块
     */
    /**
     * @locale en
     * @brief Local user resumes receiving remote video streams or local user enables video modules
     */
    ByteRTCRemoteVideoStateChangeReasonLocalUnmuted = 4,
    /**
     * @locale zh
     * @brief 远端用户停止发送视频流或远端用户禁用视频模块
     */
    /**
     * @locale en
     * @brief The remote user stops sending the video stream or the remote user disables the video module
     */
    ByteRTCRemoteVideoStateChangeReasonRemoteMuted = 5,
    /**
     * @locale zh
     * @brief 远端用户恢复发送视频流或远端用户启用视频模块
     */
    /**
     * @locale en
     * @brief Remote user resumes sending video stream or remote user enables video module
     */
    ByteRTCRemoteVideoStateChangeReasonRemoteUnmuted = 6,
    /**
     * @locale zh
     * @brief 远端用户离开房间
     */
    /**
     * @locale en
     * @brief Remote user leaves room
     */
    ByteRTCRemoteVideoStateChangeReasonRemoteOffline = 7,
};

/**
 * @locale zh
 * @type keytype
 * @brief 当前媒体设备类型
 */
/**
 * @locale en
 * @type keytype
 * @brief Type of media device
 */
typedef NS_ENUM(NSInteger, ByteRTCMediaDeviceType) {
    /**
     * @locale zh
     * @brief 未知音频设备
     */
    /**
     * @locale en
     * @brief Unknow device
     */
    ByteRTCMediaDeviceTypeAudioUnknown = -1,
    /**
     * @locale zh
     * @brief 音频渲染设备类型
     */
    /**
     * @locale en
     * @brief Screen audio recorder
     */
    ByteRTCMediaDeviceTypeAudioRenderDevice = 0,
    /**
     * @locale zh
     * @brief 音频采集设备类型
     */
    /**
     * @locale en
     * @brief Microphone
     */
    ByteRTCMediaDeviceTypeAudioCaptureDevice = 1,
    /**
     * @locale zh
     *@hidden currently not available
     *@brief 视频渲染设备类型，该类型暂无使用
     */
    /**
     * @locale en
     *@hidden currently not available
     *@brief  Video rendering device type, this type is not used yet
     */
    ByteRTCMediaDeviceTypeVideoRenderDevice = 2,
    /**
     * @locale zh
     *@brief 视频采集设备类型
     */
    /**
     * @locale en
     *@brief Video capture device
     */
    ByteRTCMediaDeviceTypeVideoCaptureDevice = 3,
    /**
     * @locale zh
     * @brief 屏幕流视频设备
     */
    /**
     * @locale en
     *@brief Screen video capture device
     */
    ByteRTCMediaDeviceTypeScreenVideoCaptureDevice = 4,
    /**
     * @locale zh
     * @brief 屏幕流音频设备
     */
    /**
     * @locale en
     *@brief Screen audio recorder
     */
    ByteRTCMediaDeviceTypeScreenAudioCaptureDevice = 5
};

/**
 * @locale zh
 * @type keytype
 * @brief 媒体设备状态<br>
 *        通过 `rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:` 或 `rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:` 回调设备状态。
 */
/**
 * @locale en
 * @type keytype
 * @brief Media device state<br>
 *        You will be informed of device state by `rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:` or `rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:`.
 */
typedef NS_ENUM(NSInteger, ByteRTCMediaDeviceState) {
    /**
     * @locale zh
     * @brief 设备已开启
     */
    /**
     * @locale en
     * @brief On
     */
    ByteRTCMediaDeviceStateStarted = 1,
    /**
     * @locale zh
     * @brief 设备已停止
     */
    /**
     * @locale en
     * @brief Off
     */
    ByteRTCMediaDeviceStateStopped = 2,
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
    ByteRTCMediaDeviceStateRuntimeError = 3,
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
    ByteRTCMediaDeviceStateAdded = 10,
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
    ByteRTCMediaDeviceStateRemoved = 11,
    /**
     * @locale zh
     * @brief 系统通话，锁屏或第三方应用打断了音视频通话。将在通话结束或第三方应用结束占用后自动恢复。
     */
    /**
     * @locale en
     * @brief Phone calls, locking screen or the other Apps interrupted the RTC call. RTC call will resume once the call ends or the other Apps release the media devices.
     */
    ByteRTCMediaDeviceStateInterruptionBegan = 12,
    /**
     * @locale zh
     * @brief 音视频通话已从系统电话或第三方应用打断中恢复
     */
    /**
     * @locale en
     * @brief RTC call resumed from the interruption caused by the phone calls or the other Apps.
     */
    ByteRTCMediaDeviceStateInterruptionEnded = 13,
    /**
     * @locale zh
     * @hidden(iOS)
     * @brief 获取设备列表超时后，收到设备列表通知。<br>
     * 再次调用获取设备接口更新设备列表。
     */
    /**
     * @locale en
     * @hidden(iOS)
     * @brief Notification of receiving the device list after time-out. <br>
     * Call enumerate-device api to update the device list when you get this notification.
     */
    ByteRTCMediaDeviceListUpdated = 16,

};

/**
 * @locale zh
 * @type keytype
 * @brief 媒体设备错误类型
 */
/**
 * @locale en
 * @type keytype
 * @brief  Media device error
 */
typedef NS_ENUM(NSInteger, ByteRTCMediaDeviceError) {
    /**
     * @locale zh
     *@brief 媒体设备正常
     */
    /**
     * @locale en
     *@brief Normal
     */
    ByteRTCMediaDeviceErrorOK = 0,
    /**
     * @locale zh
     *@brief 没有权限启动媒体设备
     */
    /**
     * @locale en
     *@brief No permission
     */
    ByteRTCMediaDeviceErrorDeviceNoPermission = 1,
    /**
     * @locale zh
     *@brief 媒体设备已经在使用中
     */
    /**
     * @locale en
     *@brief Occupied by the other application
     */
    ByteRTCMediaDeviceErrorDeviceBusy = 2,
    /**
     * @locale zh
     *@brief 媒体设备错误
     */
    /**
     * @locale en
     *@brief Error
     */
    ByteRTCMediaDeviceErrorDeviceFailure = 3,
    /**
     * @locale zh
     *@brief 未找到指定的媒体设备
     */
    /**
     * @locale en
     *@brief Not found
     */
    ByteRTCMediaDeviceErrorDeviceNotFound = 4,
    /**
     * @locale zh
     *@brief 媒体设备被移除
     */
    /**
     * @locale en
     *@brief Disconnected
     */
    ByteRTCMediaDeviceErrorDeviceDisconnected = 5,
    /**
     * @locale zh
     * @brief 无采集数据。当媒体设备的预期行为是正常采集，但没有收到采集数据时，将收到该错误。
     */
    /**
     * @locale en
     * @brief No data callback from the capture devices. <br>
     *        RTC emits this error when the media device is expected to be working but no data is received.
     */
    ByteRTCMediaDeviceErrorDeviceNoCallback = 6,
    /**
     * @locale zh
     * @brief 设备采样率不支持
     */
    /**
     * @locale en
     *@brief Not supported sample rate
     */
    ByteRTCMediaDeviceErrorUNSupportFormat = 7,
    /**
     * @locale zh
     * @hidden(macOS)
     * @brief iOS 屏幕采集没有 group Id 参数
     */
    /**
     * @locale en
     * @hidden(macOS)
     * @brief iOS screen capture not find group id parameter
     */
    ByteRTCMediaDeviceErrorNotFindGroupId = 8,
   /**
    * @locale zh
    * @hidden(macOS)
    * @brief 视频采集中断：因用户使用系统相机，应用切换到后台运行，导致采集中断。
    */
   /**
    * @locale en
    * @hidden(macOS)
    * @brief An interruption caused by the app being sent to the background as the user starts the system camera app.
    */
    ByteRTCMediaDeviceErrorNotAvailableInBackground = 9,
   /**
    * @locale zh
    * @hidden(macOS)
    * @brief 视频采集中断：可能由于其他应用占用系统相机，导致视频设备暂时不可用，从而造成采集中断。
    */
   /**
    * @locale en
    * @hidden(macOS)
    * @brief An interruption caused by the video device temporarily being unavailable (for example, when used by another app).
    */
    ByteRTCMediaDeviceErrorVideoInUseByAnotherClient = 10,
   /**
    * @locale zh
    * @hidden(macOS)
    * @brief 视频采集中断：当前应用处于侧拉、分屏或者画中画模式时，导致采集中断。
    */
   /**
    * @locale en
    * @hidden(macOS)
    * @brief An interruption caused when your app is running in Slide Over, Split View, or Picture in Picture mode on iPad.
    */
    ByteRTCMediaDeviceErrorNotAvailableWithMultipleForegroundApps = 11,
   /**
    * @locale zh
    * @hidden(macOS)
    * @brief 视频采集中断：由于系统性能不足导致中断，比如设备过热。
    */
   /**
    * @locale en
    * @hidden(macOS)
    * @brief An interruption due to system pressure, such as overheating.
    */
    ByteRTCMediaDeviceErrorNotAvailableDueToSystemPressure = 12
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
typedef NS_ENUM(NSInteger, ByteRTCMediaDeviceWarning) {
    /**
     * @locale zh
     * @brief 无警告
     */
    /**
     * @locale en
     * @brief No warning
     */
    ByteRTCMediaDeviceWarningOK = 0,
    /**
     * @locale zh
     * @brief 非法设备操作。在使用外部设备时，调用了 SDK 内部设备 API。
     */
    /**
     * @locale en
     * @brief Illegal device operation. Calls the API for internal device when using the external device.
     */
    ByteRTCMediaDeviceWarningOperationDenied = 1,
    /**
     * @locale zh
     * @brief 采集到的数据为静音帧。
     */
    /**
     * @locale en
     * @brief The media device is capturing silent frames.
     */
    ByteRTCMediaDeviceWarningCaptureSilence = 2,
    // The following warning codes are only valid for meeting scenarios.
    /**
     * @locale zh
     * @hidden for internal use only
     * @brief 音量过大，超过设备采集范围。建议降低麦克风音量或者降低声源音量。
     */
    /**
     * @locale en
     * @hidden for internal use only
     * @brief The volume is too loud and exceeds the acquisition range of the device. Lower the microphone volume or lower the volume of the audio source.
     */
    ByteRTCMediaDeviceWarningDetectClipping = 10,
    /**
     * @locale zh
     * @brief 通话中出现回声现象。<br>
     *        当 ByteRTCRoomProfile{@link #ByteRTCRoomProfile} 为 `ByteRTCRoomProfileMeeting` 和 `ByteRTCRoomProfileMeetingRoom` ，且 AEC 关闭时，SDK 自动启动回声检测，如果检测到回声问题，将通过 `rtcEngine:onAudioDeviceWarning:deviceType:deviceWarning:` 返回本枚举值。
     */
    /**
     * @locale en
     * @brief Echos between mics and speakers are detected during a call.<br>
     *        `rtcEngine:onAudioDeviceWarning:deviceType:deviceWarning:` notifies you with this enum of echo issue. During a call, SDK will detect echo issue only when ByteRTCRoomProfile{@link #ByteRTCRoomProfile} is set to `ByteRTCRoomProfileMeeting` or `ByteRTCRoomProfileMeetingRoom` and AEC is disabled.
     */
    ByteRTCMediaDeviceWarningDetectLeakEcho = 11,
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
    ByteRTCMediaDeviceWarningDetectLowSNR = 12,
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
    ByteRTCMediaDeviceWarningDetectInsertSilence = 13,
    /**
     * @locale zh
     * @hidden for internal use only
     * @brief 设备采集静音
     */
    /**
     * @locale en
     * @hidden for internal use only
     * @brief Silence during capture.
     */
    ByteRTCMediaDeviceWarningCaptureDetectSilence = 14,
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
    ByteRTCMediaDeviceWarningCaptureDetectSilenceDisappear = 15,
    /**
     * @locale zh
     * @brief 啸叫。触发该回调的情况如下：1）不支持啸叫抑制的房间模式下，检测到啸叫；2）支持啸叫抑制的房间模式下，检测到未被抑制的啸叫。<br>
     *        仅 ByteRTCRoomProfileCommunication、ByteRTCRoomProfileMeeting、ByteRTCRoomProfileMeetingRoom 三种房间模式支持啸叫抑制。<br>
     *        建议提醒用户检查客户端的距离或将麦克风和扬声器调至静音。
     */
    /**
     * @locale en
     * @brief Howling detected.<br>
     *        You will receive this callback in the following scenarios: 1) Howling is detected under the room profiles that do not support howling suppression; 2) Detect howling that is not suppressed under the room profiles that support howling suppression.<br>
     *        You can only enable howling suppression by calling calling joinRoom:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoom:userInfo:roomConfig:} to set your room profile as ByteRTCRoomProfileCommunication, ByteRTCRoomProfileMeeting, and ByteRTCRoomProfileMeetingRoom.<br>
     *        We recommend that you remind your users to adjust the physical distance between two devices or disable all unused devices except the connecting one.
     */
    ByteRTCMediaDeviceWarningCaptureDetectHowling = 16,
    /**
     * @locale zh
     * @hidden(macOS)
     * @brief 当前 AudioScenario 不支持更改音频路由，设置音频路由失败
     */
    /**
     * @locale en
     * @hidden(macOS)
     * @brief Setting audio route failed because the audio route can not be changed in the current Audio Scenario.
     */
    ByteRTCMediaDeviceWarningSetAudioRouteInvalidScenario = 20,
    /**
     * @locale zh
     * @hidden(macOS)
     * @brief 音频设备不存在，设置音频路由失败
     */
    /**
     * @locale en
     * @hidden(macOS)
     * @brief Setting audio route failed because the routing device did not exist.
     */
    ByteRTCMediaDeviceWarningSetAudioRouteNotExists = 21,
    /**
     * @locale zh
     * @hidden(macOS)
     * @brief 音频路由被系统或其他应用占用，设置音频路由失败
     */
    /**
     * @locale en
     * @hidden(macOS)
     * @brief Setting audio route failed because the audio route was occupied by the system or the other Apps.
     */
    ByteRTCMediaDeviceWarningSetAudioRouteFailedByPriority = 22,
    /**
     * @locale zh
     * @hidden(macOS)
     * @brief 当前非通话模式 ByteRTCAudioScenarioCommunication，不支持设置音频路由
     */
    /**
     * @locale en
     * @hidden(macOS)
     * @brief Setting audio route failed because the audio route can only be changed in ByteRTCAudioScenarioCommunication mode.
     */
    ByteRTCMediaDeviceWarningSetAudioRouteNotVoipMode = 23,
    /**
     * @locale zh
     * @hidden(macOS)
     * @brief 音频设备未启动，设置音频路由失败
     */
    /**
     * @locale en
     * @hidden(macOS)
     * @brief Setting audio route failed because the audio route did not initiate.
     */
    ByteRTCMediaDeviceWarningSetAudioRouteDeviceNotStart = 24,
    /**
     * @locale zh
     * @hidden(macOS)
     * @brief 非纯媒体音频场景，此时不支持切换蓝牙传输协议。待切换至纯媒体音频场景后生效。
     */
    /**
     * @locale en
     * @hidden(macOS)
     * @brief The media volume is not set in all scenarios. You cannot change the Bluetooth profile until you set the media volume in all scenarios.
     */
    ByteRTCMediaDeviceWarningSetBluetoothModeScenarioUnsupport = 25,
    /**
     * @locale zh
     * @hidden(macOS)
     * @brief 当前不支持设置 HFP。
     */
     /**
     * @locale en
     * @hidden(macOS)
     * @brief You cannot change the Bluetooth profile to HFP.
     */
    ByteRTCMediaDeviceWarningSetBluetoothModeUnsupport = 26
};

/**
 * @locale zh
 *  @type keytype
 *  @brief 音视频质量反馈问题类型
 */
/**
 * @locale en
 *  @type keytype
 *  @brief  Audio & video quality feedback problem type
 */
typedef NS_OPTIONS(uint64_t, ByteRTCProblemFeedbackOption) {
    /**
     * @locale zh
     * @brief 没有问题
     */
    /**
     * @locale en
     * @brief No problem
     */
    ByteRTCProblemFeedbackOptionNone = 0,
    /**
     * @locale zh
     * @brief 其他问题
     */
    /**
     * @locale en
     * @brief Other issues
     */
    ByteRTCProblemFeedbackOptionOtherMessage = (1ULL << 0),
    /**
     * @locale zh
     * @brief 连接失败
     */
    /**
     * @locale en
     * @brief Connection failed
     */
    ByteRTCProblemFeedbackOptionDisconnected = (1ULL << 1),
    /**
     * @locale zh
     * @brief 耳返延迟大
     */
    /**
     * @locale en
     * @brief High latency for the ear monitor
     */
    ByteRTCProblemFeedbackOptionEarBackDelay = (1ULL << 2),
    /**
     * @locale zh
     * @brief 本端有杂音
     */
    /**
     * @locale en
     * @brief Noise on the local end
     */
    ByteRTCProblemFeedbackOptionLocalNoise = (1ULL << 10),
    /**
     * @locale zh
     * @brief 本端声音卡顿
     */
    /**
     * @locale en
     * @brief Audio stall on the local end
     */
    ByteRTCProblemFeedbackOptionLocalAudioLagging = (1ULL << 11),
    /**
     * @locale zh
     * @brief 本端无声音
     */
    /**
     * @locale en
     * @brief No sound on the local end
     */
    ByteRTCProblemFeedbackOptionLocalNoAudio = (1ULL << 12),
    /**
     * @locale zh
     * @brief 本端声音大/小
     */
    /**
     * @locale en
     * @brief Too little/loud sound on the local end
     */
    ByteRTCProblemFeedbackOptionLocalAudioStrength = (1ULL << 13),
    /**
     * @locale zh
     * @brief 本端有回声
     */
    /**
     * @locale en
     * @brief Echo noise on the local end
     */
    ByteRTCProblemFeedbackOptionLocalEcho = (1ULL << 14),
    /**
     * @locale zh
     * @brief 本端视频模糊
     */
    /**
     * @locale en
     * @brief Unclear video on the local end
     */
    ByteRTCProblemFeedbackOptionLocalVideoFuzzy = (1ULL << 24),
    /**
     * @locale zh
     * @brief 本端音视频不同步
     */
    /**
     * @locale en
     * @brief Audio & video out of sync on the local end
     */
    ByteRTCProblemFeedbackOptionLocalNotSync = (1ULL << 25),
    /**
     * @locale zh
     * @brief 本端视频卡顿
     */
    /**
     * @locale en
     * @brief Video stall on the local end
     */
    ByteRTCProblemFeedbackOptionLocalVideoLagging = (1ULL << 26),
    /**
     * @locale zh
     * @brief 本端无画面
     */
    /**
     * @locale en
     * @brief No picture on the local end
     */
    ByteRTCProblemFeedbackOptionLocalNoVideo = (1ULL << 27),
    /**
     * @locale zh
     * @brief 远端有杂音
     */
    /**
     * @locale en
     * @brief Noise on the remote end
     */
    ByteRTCProblemFeedbackOptionRemoteNoise = (1ULL << 37),
    /**
     * @locale zh
     * @brief 远端声音卡顿
     */
    /**
     * @locale en
     * @brief Audio stall on the remote end
     */
    ByteRTCProblemFeedbackOptionRemoteAudioLagging = (1ULL << 38),
    /**
     * @locale zh
     * @brief 远端无声音
     */
    /**
     * @locale en
     * @brief No sound on the remote end
     */
    ByteRTCProblemFeedbackOptionRemoteNoAudio = (1ULL << 39),
    /**
     * @locale zh
     * @brief 远端声音大/小
     */
    /**
     * @locale en
     * @brief Too little/loud sound on the remote end
     */
    ByteRTCProblemFeedbackOptionRemoteAudioStrength = (1ULL << 40),
    /**
     * @locale zh
     * @brief 远端有回声
     */
    /**
     * @locale en
     * @brief Echo noise on the remote end
     */
    ByteRTCProblemFeedbackOptionRemoteEcho = (1ULL << 41),
    /**
     * @locale zh
     * @brief 远端视频模糊
     */
    /**
     * @locale en
     * @brief Unclear video on the remote end
     */
    ByteRTCProblemFeedbackOptionRemoteVideoFuzzy = (1ULL << 51),
    /**
     * @locale zh
     * @brief 远端音视频不同步
     */
    /**
     * @locale en
     * @brief Audio & video out of sync on the remote end
     */
    ByteRTCProblemFeedbackOptionRemoteNotSync = (1ULL << 52),
    /**
     * @locale zh
     * @brief 远端视频卡顿
     */
    /**
     * @locale en
     * @brief Video stall on the remote end
     */
    ByteRTCProblemFeedbackOptionRemoteVideoLagging = (1ULL << 53),
    /**
     * @locale zh
     * @brief 远端无画面
     */
    /**
     * @locale en
     * @brief No picture on the remote end
     */
    ByteRTCProblemFeedbackOptionRemoteNoVideo = (1ULL << 54)
};

/**
 * @locale zh
 * @type keytype
 * @brief 通话质量反馈房间信息
 */
/**
 * @locale en
 * @type keytype
 * @brief Video call quality feedback preset room infomation.
 */
BYTERTC_APPLE_EXPORT  @interface ByteRTCProblemFeedbackRoomInfo: NSObject
    /**
     * @locale zh
     * @brief 通话质量反馈的房间ID
     */
    /**
     * @locale en
     * @brief Room ID.
     */
    @property(nonatomic, copy) NSString * _Nonnull roomId;

    /**
     * @locale zh
     * @brief 通话质量反馈的用户ID
     */
    /**
     * @locale en
     * @brief User ID.
     */
    @property(nonatomic, copy) NSString * _Nonnull userId;
@end

/**
 * @locale zh
 * @type keytype
 * @brief 通话质量反馈信息
 */
/**
 * @locale en
 * @type keytype
 * @brief Video call quality feedback preset infomation.
 */
BYTERTC_APPLE_EXPORT  @interface ByteRTCProblemFeedbackInfo: NSObject
    /**
     * @locale zh
     * @brief 通话质量反馈的文字描述
     */
    /**
     * @locale en
     * @brief Text description corresponding to the feedback.
     */
    @property(nonatomic, copy) NSString * _Nonnull problemDesc;

    /**
     * @locale zh
     * @brief 通话质量反馈的房间信息。参看 ByteRTCProblemFeedbackRoomInfo{@link #ByteRTCProblemFeedbackRoomInfo}。
     */
    /**
     * @locale en
     * @brief Text description corresponding to the feedback room information. See ByteRTCProblemFeedbackRoomInfo{@link #ByteRTCProblemFeedbackRoomInfo}.
     */
    @property(nonatomic, strong) NSArray<ByteRTCProblemFeedbackRoomInfo *> * _Nullable roomInfo;

@end

/**
 * @locale zh
 * @type keytype
 * @brief 首帧发送状态
 */
/**
 * @locale en
 * @type keytype
 * @brief  First frame sending status
 */
typedef NS_ENUM(NSUInteger, ByteRTCFirstFrameSendState) {
    /**
     * @locale zh
     * @brief 发送中
     */
    /**
     * @locale en
     * @brief Sending
     */
    ByteRTCFirstFrameSendStateSending = 0,
    /**
     * @locale zh
     * @brief 发送成功
     */
    /**
     * @locale en
     * @brief Sent successfully
     */
    ByteRTCFirstFrameSendStateSent = 1,
    /**
     * @locale zh
     * @brief 发送失败
     */
    /**
     * @locale en
     * @brief Send failed
     */
    ByteRTCFirstFrameSendStateEnd = 2,
};

/**
 * @locale zh
 * @type keytype
 * @brief 首帧播放状态
 */
/**
 * @locale en
 * @type keytype
 * @brief  First frame playback status
 */
typedef NS_ENUM(NSUInteger, ByteRTCFirstFramePlayState) {
    /**
     * @locale zh
     * @brief 播放中
     */
    /**
     * @locale en
     * @brief Playing
     */
    ByteRTCFirstFramePlayStatePlaying = 0,
    /**
     * @locale zh
     * @brief 播放成功
     */
    /**
     * @locale en
     * @brief Play success
     */
    ByteRTCFirstFramePlayStatePlay = 1,
    /**
     * @locale zh
     * @brief 播放失败
     */
    /**
     * @locale en
     * @brief Play failed
     */
    ByteRTCFirstFramePlayStateEnd = 2,
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
typedef NS_OPTIONS(NSUInteger, ByteRTCEncryptType) {
    /**
     * @locale zh
     * @brief 不使用内置加密。默认值。
     */
    /**
     * @locale en
     * @brief Built-in encryption is not used. Default value.
     */
    ByteRTCEncryptTypeCustomize = 0,
    /**
     * @locale zh
     * @brief AES-128-CBC 加密算法
     */
    /**
     * @locale en
     * @brief AES-128-CBC  encryption algorithm
     */
    ByteRTCEncryptTypeAES128CBC = 1,
    /**
     * @locale zh
     * @brief AES-256-CBC 加密算法
     */
    /**
     * @locale en
     * @brief AES-256-CBC  encryption algorithm
     */
    ByteRTCEncryptTypeAES256CBC = 2,
    /**
     * @locale zh
     * @brief AES-128-ECB 加密算法
     */
    /**
     * @locale en
     * @brief AES-128-ECB  encryption algorithm
     */
    ByteRTCEncryptTypeAES128ECB = 3,
    /**
     * @locale zh
     * @brief AES-256-ECB 加密算法
     */
    /**
     * @locale en
     * @brief AES-256-ECB  encryption algorithm
     */
    ByteRTCEncryptTypeAES256ECB = 4
};

/**
 * @locale zh
 * @type keytype
 * @brief 视频编码类型
 */
/**
 * @locale en
 * @type keytype
 * @brief Video encoding type
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoCodecType) {
    /**
     * @locale zh
     * @brief 未知类型
     */
    /**
     * @locale en
     * @brief Unknown type
     */
    ByteRTCVideoCodecTypeUnknown = 0,
    /**
     * @locale zh
     * @brief 标准 H264 编码格式
     */
    /**
     * @locale en
     * @brief H.264 format
     */
    ByteRTCVideoCodecTypeH264 = 1,
    /**
     * @locale zh
     * @brief ByteVC1 编码器
     */
    /**
     * @locale en
     * @brief ByteVC1 format
     */
    ByteRTCVideoCodecTypeByteVC1 = 2,
};

/**
 * @locale zh
 * @hidden(macOS)
 * @type keytype
 * @brief 超分模式。
 */
/**
 * @locale en
 * @hidden not available
 * @type keytype
 * @brief Super-resolution mode.
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoSuperResolutionMode) {
    /**
     * @locale zh
     * @brief 关闭超分。
     */
    /**
     * @locale en
     * @brief Turn off super-resolution mode.
     */
    ByteRTCVideoSuperResolutionModeOff = 0,
    /**
     * @locale zh
     * @brief 开启超分。
     */
    /**
     * @locale en
     * @brief Turn on super-resolution mode.
     */
    ByteRTCVideoSuperResolutionModeOn = 1,
};

/**
 * @locale zh
 * @hidden(macOS)
 * @type keytype
 * @brief 视频降噪模式。
 */
/**
 * @locale en
 * @hidden not available
 * @type keytype
 * @brief Video noise reduction mode.
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoDenoiseMode) {
    /**
     * @locale zh
     * @brief 视频降噪关闭。
     */
    /**
     * @locale en
     * @brief Video noise reduction turned off.
     */
    ByteRTCVideoDenoiseModeOff = 0,
    /**
     * @locale zh
     * @brief 视频降噪开启，由 ByteRTC 后台配置视频降噪算法。
     */
    /**
     * @locale en
     * @brief Video noise reduction turned on. The algorithm is configured by ByteRTC..
     */
    ByteRTCVideoDenoiseModeAuto = 1,
};

/**
 * @locale zh
 * @type keytype
 * @brief 音视频流的发送/播放状态
 */
/**
 * @locale en
 * @type keytype
 * @brief  Transmission/Playback state of the media stream
 */
typedef NS_ENUM(NSInteger, ByteRTCMuteState) {
    /**
     * @locale zh
     * @brief 发送
     */
    /**
     * @locale en
     * @brief Enable
     */
    ByteRTCMuteStateOff = 0,
    /**
     * @locale zh
     * @brief 停止发送
     */
    /**
     * @locale en
     * @brief Disable
     */
    ByteRTCMuteStateOn = 1,
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
typedef NS_ENUM(NSInteger,  ByteRTCSEIStreamEventType) {
    /**
     * @locale zh
     * @brief 远端用户发布黑帧视频流。  <br>
     *        纯语音通话场景下，远端用户调用 sendSEIMessage:andMessage:andRepeatCount:andCountPerFrame:{@link #ByteRTCVideo#sendSEIMessage:andMessage:andRepeatCount:andCountPerFrame:} 发送 SEI 数据时，SDK 会自动发布一路黑帧视频流，并触发该回调。
     */
    /**
     * @locale en
     * @brief A black frame video stream is published from the remote user.  <br>
     *        In a voice call, when the remote user calls sendSEIMessage:andMessage:andRepeatCount:andCountPerFrame:{@link #ByteRTCVideo#sendSEIMessage:andMessage:andRepeatCount:andCountPerFrame:} to send SEI data, SDK will automatically publish a black frame video stream, and trigger this callback.
     */
    ByteRTCSEIStreamEventTypeStreamAdd = 0,
    /**
     * @locale zh
     * @brief 远端黑帧视频流移除。该回调的触发时机包括：  <br>
     *        + 远端用户开启摄像头采集，由语音通话切换至视频通话，黑帧视频流停止发布；  <br>
     *        + 远端用户调用 sendSEIMessage:andMessage:andRepeatCount:andCountPerFrame:{@link #ByteRTCVideo#sendSEIMessage:andMessage:andRepeatCount:andCountPerFrame:} 后 1min 内未有 SEI 数据发送，黑帧视频流停止发布；  <br>
     *        + 远端用户调用 setVideoSourceType:WithStreamIndex:{@link #ByteRTCVideo#setVideoSourceType:WithStreamIndex:} 切换至自定义视频采集时，黑帧视频流停止发布。
     */
     /**
     * @locale en
     * @brief The black frame video stream is removed. The timing this callback will be triggered is as following:  <br>
     *        + The remote user turns on their camera, switching from a voice call to a video call.  <br>
     *        + No SEI data is sent within 1min after the remote user calls sendSEIMessage:andMessage:andRepeatCount:andCountPerFrame:{@link #ByteRTCVideo#sendSEIMessage:andMessage:andRepeatCount:andCountPerFrame:}.  <br>
     *        + The black frame video stream stops when the remote user calls setVideoSourceType:WithStreamIndex:{@link #ByteRTCVideo#setVideoSourceType:WithStreamIndex:} to switch to custom video capture.
     */
    ByteRTCSEIStreamEventTypeStreamRemove = 1,
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
typedef NS_ENUM(NSInteger, ByteRTCStreamIndex) {
    /**
     * @locale zh
     * @brief 主流。包括：<br>
     *        + 由摄像头/麦克风通过内部采集机制，采集到的视频/音频; <br>
     *        + 通过自定义采集，采集到的视频/音频。
     */
    /**
     * @locale en
     * @brief  Mainstream, including: <br>
     *       + Video/audio captured by the the camera/microphone using internal capturing; <br>
     *       + Video/audio captured by custom method.
     */
    ByteRTCStreamIndexMain = 0,
    /**
     * @locale zh
     * @brief 屏幕流。屏幕共享时共享的视频流，或来自声卡的本地播放音频流。
     */
    /**
     * @locale en
     * @brief Screen-sharing stream. Video/Audio streams for screen sharing.
     */
    ByteRTCStreamIndexScreen = 1,
    /**
     * @hidden for internal use only
     */
    ByteRTCStreamIndex3rd,
    /**
     * @hidden for internal use only
     */
    ByteRTCStreamIndex4th,
    /**
     * @hidden for internal use only
     */
    ByteRTCStreamIndex5th,
    /**
     * @hidden for internal use only
     */
    ByteRTCStreamIndex6th,
    /**
     * @hidden for internal use only
     */
    ByteRTCStreamIndex7th,
    /**
     * @hidden for internal use only
     */
    ByteRTCStreamIndexMax,
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

typedef NS_ENUM(NSInteger, ByteRTCAggregationOption) {
    /**
     * @locale zh
     * @brief 流聚合向下取值  （默认策略）
     */
    /**
     * @locale en
     * @brief Stream Aggregation with the lowest resolution.(Default Strategy)
     */
    ByteRTCAggregationOptionMin = 0,
    /**
     * @locale zh
     * @brief 流聚合向上取值
     */
    /**
     * @locale en
     * @brief Stream Aggregation with the highest resolution.
     */
    ByteRTCAggregationOptionMax = 1,
    /**
     * @locale zh
     * @brief 流聚合按比例取值，比例相同时，向下取值
     */
    /**
     * @locale en
     * @brief Stream Aggregation according to the proportions, and when the proportions are the same, it takes the lowest resolution.
     */
    ByteRTCAggregationOptionMajority = 2
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
typedef NS_ENUM(NSInteger, ByteRTCSyncInfoStreamType) {
    /**
     * @locale zh
     * @brief 音频流
     */
    /**
     * @locale en
     * @brief Audio stream
     */
    ByteRTCSyncInfoStreamTypeAudio = 0
};

/**
 * @locale zh
 * @type keytype
 * @brief 颜色空间
 */
/**
 * @locale en
 * @type keytype
 * @brief ColorSpace
 */
typedef NS_ENUM(NSInteger, ByteRTCColorSpace) {
    /**
     * @locale zh<br>
     * 未知的颜色空间，默认使用kColorSpaceYCbCrBT601LimitedRange颜色空间
     */
    /**
     * @locale en<br>
     * Unknown color space, default kColorSpaceYCbCrBT601LimitedRange color space
     */
    ByteRTCColorSpaceUnknown = 0,
    /**
     * @locale zh
     * @brief BT.601数字编码标准，颜色空间[16-235]
     */
    /**
     * @locale en
     * @brief BT.601 Digital Coding Standard, Color Space [16-235]
     */
    ByteRTCColorSpaceYCbCrBT601LimitedRange = 1,
    /**
     * @locale zh
     *  @brief BT.601数字编码标准，颜色空间[0-255]
     */
    /**
     * @locale en
     *  @brief BT.601 Digital Coding Standard, Color Space [0-255]
     */
    ByteRTCColorSpaceYCbCrBT601FullRange = 2,
    /**
     * @locale zh
     * @brief BT.7091数字编码标准，颜色空间[16-235]
     */
    /**
     * @locale en
     * @brief BT.7091 Digital Coding Standard, Color Space [16-235]
     */
    ByteRTCColorSpaceYCbCrBT709LimitedRange = 3,
    /**
     * @locale zh
     * @brief BT.7091数字编码标准，颜色空间[0-255]
     */
    /**
     * @locale en
     * @brief BT.7091 Digital Coding Standard, Color Space [0-255]
     */
    ByteRTCColorSpaceYCbCrBT709FullRange = 4
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
typedef NS_ENUM(NSInteger, ByteRTCForwardStreamState) {
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
    ByteRTCForwardStreamStateIdle = 0,
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
    ByteRTCForwardStreamStateSuccess = 1,
    /**
     * @locale zh
     * @brief 转发失败，失败详情参考 ByteRTCForwardStreamError{@link #ByteRTCForwardStreamError}<br>
     *        调用 `startForwardStreamToRooms` 或 `updateForwardStreamToRooms` 后，如遇转发失败，返回此状态。
     */
    /**
     * @locale en
     * @brief Relay fails. Refer to ByteRTCForwardStreamError{@link #ByteRTCForwardStreamError} for more information for more information.<br>
     *        Once the relaying fails, state of the room turns to this state after calling `startForwardStreamToRooms` or `updateForwardStreamToRooms`.
     */
    ByteRTCForwardStreamStateFailure = 2,
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
typedef NS_ENUM(NSInteger, ByteRTCForwardStreamError) {
    /**
     * @locale zh
     * @brief 正常
     */
    /**
     * @locale en
     * @brief Normal
     */
    ByteRTCForwardStreamErrorOK = 0,
    /**
     * @locale zh
     * @brief 参数异常
     */
    /**
     * @locale en
     * @brief Invalid argument
     */
    ByteRTCForwardStreamErrorInvalidArgument = 1201,
    /**
     * @locale zh
     * @brief Token 错误
     */
    /**
     * @locale en
     * @brief Invalid token
     */
    ByteRTCForwardStreamErrorInvalidToken = 1202,
    /**
     * @locale zh
     * @brief 服务端异常
     */
    /**
     * @locale en
     * @brief Error returning from server
     */
    ByteRTCForwardStreamErrorResponse = 1203,
    /**
     * @locale zh
     * @brief 目标房间有相同 user id 的用户加入，转发中断
     */
    /**
     * @locale en
     * @brief Relaying aborts for the reason of that a User with the same user ID as that of the publisher joins.
     */
    ByteRTCForwardStreamErrorRemoteKicked = 1204,
    /**
     * @locale zh
     * @brief 服务端不支持转发功能
     */
    /**
     * @locale en
     * @brief Server denies.
     */
    ByteRTCForwardStreamErrorNotSupport = 1205,
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
typedef NS_ENUM(NSInteger, ByteRTCForwardStreamEvent) {
    /**
     * @locale zh
     * @brief 本端与服务器网络连接断开，暂停转发。
     */
    /**
     * @locale en
     * @brief Relaying pauses for the reason of network disconnecting.
     */
    ByteRTCForwardStreamEventDisconnected = 0,
    /**
     * @locale zh
     * @brief 本端与服务器网络连接恢复，转发服务连接成功。
     */
    /**
     * @locale en
     * @brief Relaying recovers from the disconnecting.
     */
    ByteRTCForwardStreamEventConnected = 1,
    /**
     * @locale zh
     * @brief 转发中断。转发过程中，如果相同 user_id 的用户进入目标房间，转发中断。
     */
    /**
     * @locale en
     * @brief Relaying aborts for the reason of that a User with the same user ID as that of the publisher joins.
     */
    ByteRTCForwardStreamEventInterrupt = 2,
    /**
     * @locale zh
     * @brief 目标房间已更新，由 `updateForwardStreamToRooms` 触发。
     */
    /**
     * @locale en
     * @brief designated room list updates after you call `updateForwardStreamToRooms`.
     */
    ByteRTCForwardStreamEventDstRoomUpdated = 3,
    /**
     * @locale zh
     * @brief API 调用时序错误。例如，在调用 `startForwardStreamToRooms` 之前调用 `updateForwardStreamToRooms` 。
     */
    /**
     * @locale en
     * @brief Wrong API-calling order. For example, call `updateForwardStreamToRooms` before calling `startForwardStreamToRooms`.
     */
    ByteRTCForwardStreamEventUnExpectAPICall = 4,
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
typedef NS_ENUM(NSInteger, ByteRTCRecordingState) {
    /**
     * @locale zh
     * @brief 录制异常
     */
    /**
     * @locale en
     * @brief Recording exception
     */
    ByteRTCRecordingStateError = 0,
    /**
     * @locale zh
     * @brief 录制进行中
     */
    /**
     * @locale en
     * @brief Recording in progress
     */
    ByteRTCRecordingStateProcessing = 1,
    /**
     * @locale zh
     * @brief 录制文件保存成功，调用 `stopFileRecording:` 结束录制之后才会收到该状态码。
     */
    /**
     * @locale en
     * @brief If the recording file is saved successfully, call `stopFileRecording:` to end the recording before receiving the status code.
     */
    ByteRTCRecordingStateSuccess = 2,
};

/**
 * @locale zh
 * @type keytype
 * @brief 本地录制错误码
 */
/**
 * @locale en
 * @type keytype
 * @brief  Local recording error code
 */
typedef NS_ENUM(NSInteger, ByteRTCRecordingErrorCode) {
    /**
     * @locale zh
     * @brief 录制正常
     */
    /**
     * @locale en
     * @brief Recording normal
     */
    ByteRTCRecordingErrorCodeOk = 0,
    /**
     * @locale zh
     * @brief 没有文件写权限
     */
    /**
     * @locale en
     * @brief No file write permissions
     */
    ByteRTCRecordingErrorCodeNoPermission = -1,
    /**
     * @locale zh
     * @brief 当前版本 SDK 不支持本地录制功能，请联系技术支持人员
     */
    /**
     * @locale en
     * @brief The current version SDK does not support local recording, please contact technical support
     */
    ByteRTCRecordingErrorCodeNotSupport = -2,
    /**
     * @locale zh
     * @brief 其他异常
     */
    /**
     * @locale en
     * @brief Other anomalies
     */
    ByteRTCRecordingErrorCodeOther = -3,
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
typedef NS_ENUM(NSInteger, ByteRTCRecordingFileType) {
    /**
     * @locale zh
     * @brief aac 格式文件
     */
    /**
     * @locale en
     * @brief Aac  format file
     */
    ByteRTCRecordingFileTypeAAC = 0,
    /**
     * @locale zh
     * @brief mp4 格式文件
     */
    /**
     * @locale en
     * @brief Mp4  format file
     */
    ByteRTCRecordingFileTypeMP4 = 1,
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
typedef NS_ENUM(NSInteger, ByteRTCAVSyncState) {
    /**
     * @locale zh
     * @brief 音视频开始同步
     */
    /**
     * @locale en
     * @brief A/V synchronization begins.
     */
    ByteRTCAVSyncStateAVStreamSyncBegin = 0,
    /**
     * @locale zh
     * @brief 音视频同步过程中音频移除，但不影响当前的同步关系
     */
    /**
     * @locale en
     * @brief The publisher stops publishing audio stream during the synchronization, which does not affect the sync relationship.
     */
    ByteRTCAVSyncStateAudioStreamRemove = 1,
    /**
     * @locale zh
     * @brief 音视频同步过程中视频移除，但不影响当前的同步关系
     */
    /**
     * @locale en
     * @brief The publisher stops publishing audio stream during the synchronization, which does not affect the sync relationship.
     */
    ByteRTCAVSyncStateVideoStreamRemove = 2,
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
    ByteRTCAVSyncStateSetAVSyncStreamId = 3,
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
typedef NS_ENUM(NSInteger, ByteRTCEchoTestResult) {
    /**
     * @locale zh
     * @brief 接收到采集的音视频的回放，通话回路检测成功
     */
    /**
     * @locale en
     * @brief The playback of captured audio/video is received, test succeeds.
     */
    ByteRTCEchoTestResultSuccess = 0,
    /**
     * @locale zh
     * @brief 测试超过 60s 仍未完成，已自动停止
     */
    /**
     * @locale en
     * @brief Test is not completed after 60 seconds and has been stopped automatically.
     */
    ByteRTCEchoTestResultTimeout = 1,
    /**
     * @locale zh
     * @brief 上一次测试结束和下一次测试开始之间的时间间隔少于 5s
     */
    /**
     * @locale en
     * @brief Less than 5s between the end of the last test and the start of the next test.
     */
    ByteRTCEchoTestResultIntervalShort = 2,
    /**
     * @locale zh
     * @brief 音频采集异常
     */
    /**
     * @locale en
     * @brief Audio capture error
     */
    ByteRTCEchoTestResultAudioDeviceError = 3,
    /**
     * @locale zh
     * @brief 视频采集异常
     */
    /**
     * @locale en
     * @brief Video capture error
     */
    ByteRTCEchoTestResultVideoDeviceError = 4,
    /**
     * @locale zh
     * @brief 音频接收异常
     */
    /**
     * @locale en
     * @brief Audio reception error
     */
    ByteRTCEchoTestResultAudioReceiveError = 5,
    /**
     * @locale zh
     * @brief 视频接收异常
     */
    /**
     * @locale en
     * @brief Video reception error
     */
    ByteRTCEchoTestResultVideoReceiveError = 6,
    /**
     * @locale zh
     * @brief 内部错误，不可恢复
     */
    /**
     * @locale en
     * @brief Unrecoverable internal error
     */
    ByteRTCEchoTestResultInternalError = 7
};

/**
 * @locale zh
 * @type errorcode
 * @brief 公共流状态码
 */
/**
 * @locale en
 * @hidden currently not available
 * @type errorcode
 * @brief State and errors for publishing or subscribing public streams
 */
typedef NS_ENUM(NSInteger, ByteRTCPublicStreamErrorCode) {
    /**
     * @locale zh
     * @brief 发布或订阅成功。
     */
    /**
     * @locale en
     * @brief Published or subscribed successfully.
     */
    ByteRTCPublicStreamErrorCodeSuccess = 0,
    /**
     * @locale zh
     * @brief 公共流的参数异常，请修改参数后重试。
     */
    /**
     * @locale en
     * @brief Invalid parameter(s). Please revise the paramter(s) and retry.
     */
    ByteRTCPublicStreamErrorCodePushParamError = 1191,
    /**
     * @locale zh
     * @brief 服务端状态异常，将自动重试。
     */
    /**
     * @locale en
     * @brief Error for the task at the server side. The server will retry upon the failure.
     */
    ByteRTCPublicStreamErrorCodePushStatusError = 1192,
    /**
     * @locale zh
     * @brief 内部错误，不可恢复，请重试。
     */
    /**
     * @locale en
     * @brief Unrecoverable error of publishing the public stream. Please start the task again.
     */
    ByteRTCPublicStreamErrorCodePushInternalError = 1193,
    /**
     * @locale zh
     * @brief 发布失败，将自动重试，请关注重试结果。
     */
    /**
     * @locale en
     * @brief Failed to publish. The SDK will retry upon the failure. We recommend to keep listening to the publishing result.
     */
    ByteRTCPublicStreamErrorCodePushError = 1195,
    /**
     * @locale zh
     * @brief 发布失败，10 s 后会重试，重试 3 次后自动停止。
     */
    /**
     * @locale en
     * @brief Failed to publish the public stream for time-out error. The SDK will retry 10 s after the timeout. The maximum number of retry attempts is 3.
     */
    ByteRTCPublicStreamErrorCodePushTimeOut = 1196,
    /**
     * @locale zh
     * @brief 订阅失败，发布端未开始发布流。
     */
    /**
     * @locale en
     * @brief Failed to play a public stream because the publisher has not started publishing.
     */
    ByteRTCPublicStreamErrorCodePullNoPushStream = 1300,
};
/**
 * @locale zh
 * @type keytype
 * @brief 蓝牙传输协议。
 */
/**
 * @locale en
 * @type keytype
 * @brief The Bluetooth profiles.
 */
typedef NS_ENUM(NSInteger, ByteRTCBluetoothMode) {
     /**
      * @locale zh
      * @brief  默认采用 auto 模式，具体如下：<br>
      * <table>
      * <tr>
      *   <th>场景</th>
      *   <th> HFP </th>
      *   <th> A2DP </th>
      * </tr>
      * <tr>
      *   <th>纯通话场景</th>
      *   <th> 蓝牙设备支持 HFP </th>
      *   <th> 蓝牙设备不支持 HFP </th>
      * </tr>
      * <tr>
      *   <th>纯媒体场景</th>
      *   <th> 使用蓝牙设备采集播放音频 </th>
      *   <th> 使用 iOS 设备采集音频，蓝牙设备播放音频 </th>
      * </tr>
      * </table>
      */
     /**
      * @locale en
      * @brief The default mode：<br>
      * <table>
      * <tr>
      *   <th> Scenario </th>
      *   <th> HFP </th>
      *   <th> A2DP </th>
      * </tr>
      * <tr>
      *   <th> The in-call volume is set in all scenarios. </th>
      *   <th> HFP is supported by your Bluetooth device. </th>
      *   <th> HFP is not supported by your Bluetooth device. </th>
      * </tr>
      * <tr>
      *   <th> The media volume is set in all scenarios.</th>
      *   <th> Audio is captured and played by your Bluetooth device. </th>
      *   <th> Audio is captured by your iOS device and played by your Bluetooth device. </th>
      * </tr>
      * </table>
      */
     ByteRTCBluetoothModeAuto = 0,

     /**
      * @locale zh
      * @brief 高级音频分配配置文件（A2DP）。立体声、高音质。采用 iOS 设备进行音频采集，蓝牙设备进行播放。
      */
     /**
      * @locale en
      * @brief Advanced Audio Distribution Profile(A2DP). This profile defines how high-quality audio (stereo or mono) can be streamed from one device to another over a Bluetooth connection. Audio is captured by your iOS device and played by your Bluetooth device.
      */
     ByteRTCBluetoothModeA2DP = 1,

    /**
     * @locale zh
     * @brief 免提配置文件（HFP）。单声道、普通音质。音频采集和播放设备都使用蓝牙设备。
     */
    /**
     * @locale en
     * @brief Hands-Free Profile(HFP). This profile defines how voice-quality, mono audio can be streamed from one device to another. Audio is captured and played by your Bluetooth device.
     */
     ByteRTCBluetoothModeHFP = 2
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
BYTERTC_APPLE_EXPORT @interface ByteRTCEchoTestConfig : NSObject
/**
 * @locale zh
 * @brief 用于渲染接收到的视频的视图
 */
/**
 * @locale en
 * @brief View for rendering received video
 */
@property(strong, nonatomic) ByteRTCView* _Nullable view;
/**
 * @locale zh
 * @brief 测试用户加入的房间 ID。  
 */
/**
 * @locale en
 * @brief ID of the room that the tested user will join.  
 */
@property(copy, nonatomic) NSString *_Nonnull roomId;
/**
 * @locale zh
 * @brief 进行音视频通话回路测试的用户 ID
 */
/**
 * @locale en
 * @brief User ID for testing
 */
@property(copy, nonatomic) NSString *_Nonnull userId;
/**
 * @locale zh
 * @brief 对用户进房时进行鉴权验证的动态密钥，用于保证音视频通话回路测试的安全性。
 */
/**
 * @locale en
 * @brief Token used for authenticating users when they enter the room.
 */
@property(copy, nonatomic) NSString *_Nonnull token;
/**
 * @locale zh
 * @brief 是否检测音频。检测设备为系统默认音频设备。  <br>
 *        + true：是  <br>
 *            - 若使用 SDK 内部采集，此时设备麦克风会自动开启，并在 audioReportInterval 值大于 0 时触发 `onLocalAudioPropertiesReport` 回调，你可以根据该回调判断麦克风的工作状态  <br>
 *            - 若使用自定义采集，此时你需调用 pushExternalAudioFrame:{@link #ByteRTCVideo#pushExternalAudioFrame:} 将采集到的音频推送给 SDK  <br>
 *        + false：否  
 */
/**
 * @locale en
 * @brief Whether to test audio. The device to be tested is the default audio device.  <br>
 *        + true: Yes  <br>
 *            - If you use internal capture, the device microphone will automatically turn on and `onLocalAudioPropertiesReport` will be triggered when the value of audioReportInterval is set to greater than 0, from which you can judge the working status of the microphone.  <br>
 *            - If you choose custom capture, you also need to call pushExternalAudioFrame:{@link #ByteRTCVideo#pushExternalAudioFrame:} to push the captured audio to the SDK.  <br>
 *        + false: No  
 */
@property(assign, nonatomic) BOOL enableAudio;
/**
 * @locale zh
 * @brief 是否检测视频。PC 端默认检测列表中第一个视频设备。  <br>
 *        + true：是  <br>
 *            - 若使用 SDK 内部采集，此时设备摄像头会自动开启  <br>
 *            - 若使用自定义采集，此时你需调用 pushExternalVideoFrame:{@link #ByteRTCVideo#pushExternalVideoFrame:} 将采集到的视频推送给 SDK  <br>
 *        + false：否  <br>
 *        视频的发布参数固定为：分辨率 640px × 360px，帧率 15fps。
 */
/**
 * @locale en
 * @brief Whether to test video. If you are using a desktop PC, the device to be tested is by default the first video device in the list.  <br>
 *        + true: Yes  <br>
 *            - If you use internal capture, the device camera will automatically turn on.  <br>
 *            - If you choose custom capture, you also need to call pushExternalVideoFrame:{@link #ByteRTCVideo#pushExternalVideoFrame:} to push the captured video to the SDK.  <br>
 *        + false: No  <br>
 *        The video is published with fixed parameters: resolution 640px × 360px, frame rate 15fps.
 */
@property(assign, nonatomic) BOOL enableVideo;
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
@property(assign, nonatomic) NSInteger audioReportInterval;
@end

/**
 * @locale zh
 * @type keytype
 * @brief 用户信息。  
 */
/**
 * @locale en
 * @type keytype
 * @brief  User information.   
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCUserInfo : NSObject
/**
 * @locale zh
 * @brief 用户 ID。该字符串符合正则表达式：`[a-zA-Z0-9_@\-\.]{1,128}`。
 */
/**
 * @locale en
 * @brief User ID. The string matches the regular expression: `[a-zA-Z0-9_@\-\.]{1,128}`.
 */
@property(copy, nonatomic) NSString *_Nonnull userId;
/**
 * @locale zh
 * @brief 用户需要透传的额外的信息，字符长度限制为 200 字节。会在 `rtcEngine:onUserJoined:elapsed:` 中回调给远端用户。
 */
 /**
  * @locale en
  * @brief Additional information of the user. The string is no more than 200 bytes. <br>
  *        The remote users will receive the info with `rtcEngine:onUserJoined:elapsed:`.
  */
@property(copy, nonatomic) NSString *_Nonnull extraInfo;
@end

/**
 * @locale zh
 * @type keytype
 * @brief 房间通话统计数据，统计周期为 2s 。  <br>
 *        用户进房成功后，SDK 会周期性地通过 `onRoomStats` 回调通知用户当前房间内的汇总统计信息。此数据结构即为回调给用户的参数类型。  
 */
/**
 * @locale en
 * @type keytype
 * @brief Room call statistics, reference period is 2s. <br>
 *        After the user enters the room successfully, the SDK will periodically notify the user through `onRoomStats` callback statistics in the current room. This data structure is the type of parameter that is called back to the user. 
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCRoomStats : NSObject
/**
 * @locale zh
 * @brief 用户进房开始通话后的总时长，单位为 s ，累计值
 */
/**
 * @locale en
 * @brief The total time after the user enters the room and starts the call, in s, the cumulative value
 */
@property(assign, nonatomic) NSInteger duration;
/**
 * @locale zh
 * @brief 本地用户的总发送字节数 (bytes)，累计值
 */
/**
 * @locale en
 * @brief The total number of bytes sent by the local user  (bytes), the cumulative value
 */
@property(assign, nonatomic) NSInteger txBytes;
/**
 * @locale zh
 * @brief 本地用户的总接收字节数 (bytes)，累计值
 */
/**
 * @locale en
 * @brief The total number of bytes received by the local user  (bytes), the cumulative value
 */
@property(assign, nonatomic) NSInteger rxBytes;
/**
 * @locale zh
 * @brief 发送码率（kbps），获取该数据时的瞬时值
 */
/**
 * @locale en
 * @brief The instantaneous value of Tx bitrate in kbps
 */
@property(assign, nonatomic) NSInteger txKbitrate;
/**
 * @locale zh
 * @brief 接收码率（kbps），获取该数据时的瞬时值
 */
/**
 * @locale en
 * @brief The instantaneous value of Rx bitrate in kbps
 */
@property(assign, nonatomic) NSInteger rxKbitrate;
/**
 * @locale zh
 * @brief 本地用户的音频发送码率 (kbps)，瞬时值
 */
/**
 * @locale en
 * @brief Local user's audio transmission bit rate  (kbps), instantaneous value
 */
@property(assign, nonatomic) NSInteger txAudioKBitrate;
/**
 * @locale zh
 * @brief 本地用户的音频接收码率 (kbps)，瞬时值
 */
/**
 * @locale en
 * @brief Local user's audio receiving bit rate  (kbps), instantaneous value
 */
@property(assign, nonatomic) NSInteger rxAudioKBitrate;
/**
 * @locale zh
 * @brief 本地用户的视频发送码率 (kbps)，瞬时值
 */
/**
 * @locale en
 * @brief Local user's video transmission bit rate  (kbps), instantaneous value
 */
@property(assign, nonatomic) NSInteger txVideoKBitrate;
/**
 * @locale zh
 * @brief 本地用户的视频接收码率 (kbps)，瞬时值
 */
/**
 * @locale en
 * @brief Local user's video receiving bit rate  (kbps), instantaneous value
 */
@property(assign, nonatomic) NSInteger rxVideoKBitrate;
/**
 * @locale zh
 * @brief 屏幕接收码率，获取该数据时的瞬时值，单位为 Kbps
 */
/**
 * @locale en
 * @brief The instantaneous RX bitrate of screen-sharing video in Kbps
 */
@property(assign, nonatomic) NSInteger txScreenKBitrate;
/**
 * @locale zh
 * @brief 屏幕发送码率，获取该数据时的瞬时值，单位为 Kbps
 */
/**
 * @locale en
 * @brief The instantaneous TX bitrate of screen-sharing video in Kbps
 */
@property(assign, nonatomic) NSInteger rxScreenKBitrate;
/**
 * @locale zh
 * @brief 当前房间内的可见用户人数，包括本地用户自身
 */
/**
 * @locale en
 * @brief Number of visible users in the current room, including local users themselves
 */
@property(assign, nonatomic) NSInteger userCount;
/**
 * @locale zh
 * @brief App 现在的下行丢包率
 */
/**
 * @locale en
 * @brief App  Current downlink packet loss rate
 */
@property(assign, nonatomic) float rxLostrate;
/**
 * @locale zh
 * @brief App 现在的上行丢包率
 */
/**
 * @locale en
 * @brief App  current uplink packet loss rate
 */
@property(assign, nonatomic) float txLostrate;
/**
 * @locale zh
 * @brief 客户端到服务端的往返时延
 */
/**
 * @locale en
 * @brief Client side round-trip time
 */
@property(assign, nonatomic) NSInteger rtt;
/**
 * @locale zh
 * @brief 当前 App 的 CPU 使用率
 */
/**
 * @locale en
 * @brief Current App CPU usage
 */
// @property(assign, nonatomic) double cpuAppUsage;
/**
 * @locale zh
 * @brief 当前设备的总 CPU 使用率
 */
/**
 * @locale en
 * @brief Total CPU usage of the current device
 */
// @property(assign, nonatomic) double cpuTotalUsage;

/**
 * @locale zh
 * @hidden currently not available
 * @brief 系统上行网络抖动（ms）
 */
/**
 * @locale en
 * @hidden currently not available
 * @brief The system downlink network jitter(ms)
 */
@property(assign, nonatomic) NSInteger txJitter;
/**
 * @locale zh
 * @hidden currently not available
 * @brief 系统下行网络抖动（ms）
 */
/**
 * @locale en
 * @hidden currently not available
 * @brief The system downlink network jitter(ms)
 */
@property(assign, nonatomic) NSInteger rxJitter;
/**
 * @locale zh
 * @brief 蜂窝路径发送的码率 (kbps)，为获取该数据时的瞬时值
 */
/**
 * @locale en
 * @brief Cellular Link Send bit rate  (kbps), get the instantaneous value of the data
 */
@property(assign, nonatomic) NSInteger txCellularKBitrate;
/**
 * @locale zh
 * @brief 蜂窝路径接收码率 (kbps)，为获取该数据时的瞬时值
 */
/**
 * @locale en
 * @brief Cellular Link Receive bit rate  (kbps), get the instantaneous value of the data
 */
@property(assign, nonatomic) NSInteger rxCellularKBitrate;
@end

/**
 * @locale zh
 * @type keytype
 * @brief 本地视频流统计信息，统计周期为 2s 。  <br>
 *        本地用户发布视频流成功后，SDK 会周期性地通过 `onLocalStreamStats`<br>
 *        通知本地用户发布的视频流在此次统计周期内的发送状况。此数据结构即为回调给本地用户的参数类型。  
 */
/**
 * @locale en
 * @type keytype
 * @brief Local video stream statistics, reference period 2s. <br>
 *        After the local user publishes the video stream successfully, the SDK will periodically notify the local user through `onLocalStreamStats`<br>
 *        The delivery status of the published video stream during this reference period. This data structure is the type of parameter that is called back to the local user. 
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCLocalVideoStats : NSObject
/**
 * @locale zh
 * @brief 发送码率。此次统计周期内实际发送的分辨率最大的视频流的发送码率，单位为 Kbps
 */
/**
 * @locale en
 * @brief TX bitrate in Kbps of the video stream with the highest resolution within the reference period
 */
@property(assign, nonatomic) float sentKBitrate;
/**
 * @locale zh
 * @brief 采集帧率。此次统计周期内的视频采集帧率，单位为 fps 。
 */
/**
 * @locale en
 * @brief Sampling frame rate in fps of video capture during this reference period
 */
@property(assign, nonatomic) NSInteger inputFrameRate;
/**
 * @locale zh
 * @brief 发送帧率。此次统计周期内实际发送的分辨率最大的视频流的视频发送帧率，单位为 fps 。
 */
/**
 * @locale en
 * @brief TX frame rate in fps of the video stream with the highest resolution within the reference period
 */
@property(assign, nonatomic) NSInteger sentFrameRate;
/**
 * @locale zh
 * @brief 编码器输出帧率。当前编码器在此次统计周期内实际发送的分辨率最大的视频流的输出帧率，单位为 fps 。
 */
/**
 * @locale en
 * @brief Encoder-output frame rate in fps of the video stream with the highest resolution within the reference period
 */
@property(assign, nonatomic) NSInteger encoderOutputFrameRate;
/**
 * @locale zh
 * @brief 本地渲染帧率。此次统计周期内的本地视频渲染帧率，单位为 fps 。
 */
/**
 * @locale en
 * @brief Local-rendering frame rate in fps during this reference period
 */
@property(assign, nonatomic) NSInteger rendererOutputFrameRate;
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
@property(assign, nonatomic) NSInteger statsInterval;
/**
 * @locale zh
 * @brief 视频丢包率。统计周期内的视频上行丢包率，取值范围为 [0, 1] 。  
 */
/**
 * @locale en
 * @brief Video packet loss rate. The video uplink packet loss rate in the reference period, the value range is  [0,1]. 
 */
@property(assign, nonatomic) float videoLossRate;
/**
 * @locale zh
 * @brief 往返时延。单位为 ms 。  
 */
/**
 * @locale en
 * @brief Round-trip time. The unit is ms. 
 */
@property(assign, nonatomic) NSInteger rtt;
/**
 * @locale zh
 * @brief 视频编码码率。此次统计周期内的实际发送的分辨率最大的视频流视频编码码率，单位为 Kbps 。
 */
/**
 * @locale en
 * @brief Video encoding bitrate in Kbps of the video stream with the highest resolution within the reference period.
 */
@property(assign, nonatomic) NSInteger encodedBitrate;
/**
 * @locale zh
 * @brief 实际发送的分辨率最大的视频流的视频编码宽度，单位为 px 。
 */
/**
 * @locale en
 * @brief Video encoding width in px of the video stream with the highest resolution within the reference period
 */
@property(assign, nonatomic) NSInteger encodedFrameWidth;
/**
 * @locale zh
 * @brief 实际发送的分辨率最大的视频流的视频编码高度，单位为 px 。
 */
/**
 * @locale en
 * @brief Video encoding height in px of the video stream with the highest resolution within the reference period
 */
@property(assign, nonatomic) NSInteger encodedFrameHeight;
/**
 * @locale zh
 * @brief 此次统计周期内实际发送的分辨率最大的视频流的发送的视频帧总数。
 */
/**
 * @locale en
 * @brief The total number of the video stream with the highest resolution within the reference period sent in the reference period.
 */
@property(assign, nonatomic) NSInteger encodedFrameCount;
/**
 * @locale zh
 * @brief 编码类型。参看 ByteRTCVideoCodecType{@link #ByteRTCVideoCodecType} 类型。  
 */
/**
 * @locale en
 * @brief Encoding type. See ByteRTCVideoCodecType{@link #ByteRTCVideoCodecType} type. 
 */
@property(nonatomic) ByteRTCVideoCodecType codecType;
/**
 * @locale zh
 * @brief 所属用户的媒体流是否为屏幕流。你可以知道当前统计数据来自主流还是屏幕流。
 */
/**
 * @locale en
 * @brief Whether the media stream belongs to the user is a screen stream. You can know whether the current statistics come from mainstream or screen stream.
 */
@property(assign, nonatomic) BOOL isScreen;
/**
 * @locale zh
 * @brief 视频上行网络抖动，单位为 ms。  
 */
/**
 * @locale en
 * @brief Video uplink network jitter in ms. 
 */
@property(assign, nonatomic) NSInteger jitter;
/**
 * @locale zh
 * @hidden(macOS)
 * @brief 视频降噪模式。具体参看 ByteRTCVideoDenoiseMode{@link #ByteRTCVideoDenoiseMode} 。
 */
/**
 * @locale en
 * @hidden(macOS)
 * @brief Video noise reduction mode. Refer to ByteRTCVideoDenoiseMode{@link #ByteRTCVideoDenoiseMode} for more details.
 */
@property(assign, nonatomic) ByteRTCVideoDenoiseMode videoDenoiseMode;
@end

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
 *         After the remote user subscribes to the remote video stream successfully, the SDK will periodically notify the remote user of the reception status of the subscribed remote video stream during this reference period through `onRemoteStreamStats`<br>
 *        . This data structure is the type of parameter that is called back to the local user. 
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCRemoteVideoStats : NSObject
/**
 * @locale zh
 * @brief 远端视频宽度。  
 */
/**
 * @locale en
 * @brief Distal video width.   
 */
@property(assign, nonatomic) NSInteger width;
/**
 * @locale zh
 * @brief 远端视频高度。  
 */
/**
 * @locale en
 * @brief Remote video height.   
 */
@property(assign, nonatomic) NSInteger height;
/**
 * @locale zh
 * @brief 远端视频丢包率。统计周期内的视频下行丢包率，取值范围为 [0, 1] 。  
 */
/**
 * @locale en
 * @brief Remote video packet loss rate. The video downlink packet loss rate in the reference period, the value range is  [0,1]. 
 */
@property(assign, nonatomic) float videoLossRate;
/**
 * @locale zh
 * @brief 接收码率。统计周期内的视频接收码率，单位为 kbps 。  
 */
/**
 * @locale en
 * @brief Receiving bit rate. Video reception rate within the reference period, in kbps. 
 */
@property(assign, nonatomic) float receivedKBitrate;
/**
 * @locale zh
 * @brief 远端视频接收帧率。  
 */
/**
 * @locale en
 * @brief Remote video receiving frame rate.   
 */
@property(assign, nonatomic) NSInteger receivedFrameRate;
/**
 * @locale zh
 * @brief 远端视频解码输出帧率。  
 */
/**
 * @locale en
 * @brief Remote video decoding output frame rate.   
 */
@property(assign, nonatomic) NSInteger decoderOutputFrameRate;
/**
 * @locale zh
 * @brief 远端视频渲染输出帧率。  
 */
/**
 * @locale en
 * @brief Remote video rendering output frame rate.   
 */
@property(assign, nonatomic) NSInteger renderOutputFrameRate;
/**
 * @locale zh
 * @brief 远端视频卡顿次数。  
 */
/**
 * @locale en
 * @brief The number of remote video cards.   
 */
@property(assign, nonatomic) NSInteger stallCount;
/**
 * @locale zh
 * @brief 远端视频卡顿时长，单位为 ms 。  
 */
/**
 * @locale en
 * @brief Distal video lag duration, in ms. 
 */
@property(assign, nonatomic) NSInteger stallDuration;
/**
 * @locale zh
 * @brief 用户体验级别的端到端延时。从发送端采集完成编码开始到接收端解码完成渲染开始的延时，单位为 ms 。  
 */
/**
 * @locale en
 * @brief End-to-end latency at the user experience level. The delay from the completion of encoding at the transmitting end to the completion of decoding at the receiving end, in units of ms. 
 */
@property(assign, nonatomic) NSInteger e2eDelay;
/**
 * @locale zh
 * @brief 远端视频流是否是屏幕共享流。你可以知道当前数据来自主流还是屏幕流。
 */
/**
 * @locale en
 * @brief Whether the remote video stream is a screen share stream. You can know whether the current data comes from mainstream or screen stream.
 */
@property(assign, nonatomic) BOOL isScreen;
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
@property(assign, nonatomic) NSInteger statsInterval;
/**
 * @locale zh
 * @brief 往返时延。单位为 ms 。  
 */
/**
 * @locale en
 * @brief Round-trip time. The unit is ms. 
 */
@property(assign, nonatomic) NSInteger rtt;
/**
 * @locale zh
 * @brief 远端用户在进房后发生视频卡顿的累计时长占视频总有效时长的百分比（%）。视频有效时长是指远端用户进房发布视频流后，除停止发送视频流和禁用视频模块之外的视频时长。
 */
/**
 * @locale en
 * @brief The cumulative duration of the video card of the remote user accounts for the percentage (%) of the total effective duration of the video after entering the room. The effective duration of the video refers to the duration of the video other than stopping sending the video stream and disabling the video module after the remote user enters the room to publish the video stream.
 */
@property(assign, nonatomic) NSInteger frozenRate;
/**
 * @locale zh
 * @brief 编码类型。参看 ByteRTCVideoCodecType{@link #ByteRTCVideoCodecType} 类型。
 */
/**
 * @locale en
 * @brief For the encoding type of the video, please refer to ByteRTCVideoCodecType{@link #ByteRTCVideoCodecType}.
 */
@property(nonatomic) ByteRTCVideoCodecType codecType;
/**
 * @locale zh
 * @brief SDK 订阅的远端视频流的分辨率下标。  
 */
/**
 * @locale en
 * @brief The resolution subscript of the SDK  subscribed remote video stream. 
 */
@property(assign, nonatomic) NSInteger videoIndex;
/**
 * @locale zh
 * @brief 视频下行网络抖动，单位为 ms。  
 */
/**
 * @locale en
 * @brief Video downlink network jitter in ms. 
 */
@property(assign, nonatomic) NSInteger jitter;
/**
 * @locale zh
 * @hidden(macOS)
 * @brief 远端视频超分模式，参看 ByteRTCVideoSuperResolutionMode{@link #ByteRTCVideoSuperResolutionMode}。
 */
/**
 * @locale en
 * @hidden(macOS)
 * @brief Super-resolution mode. See ByteRTCVideoSuperResolutionMode{@link #ByteRTCVideoSuperResolutionMode}.
 */
@property(assign, nonatomic) ByteRTCVideoSuperResolutionMode superResolutionMode;
@end

/**
 * @locale zh
 * @type keytype
 * @brief 本地音频流统计信息，统计周期为 2s 。  <br>
 *        本地用户发布音频流成功后，SDK 会周期性地通过 `onLocalStreamStats`<br>
 *        通知本地用户发布的音频流在此次统计周期内的发送状况。此数据结构即为回调给本地用户的参数类型。  
 */
/**
 * @locale en
 * @type keytype
 * @brief Local audio stream statistics, reference period 2s. <br>
 *        After the local user publishes the audio stream successfully, the SDK will periodically notify the local user through `onLocalStreamStats`<br>
 *        The sending status of the published audio stream during this reference period. This data structure is the type of parameter that is called back to the local user. 
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCLocalAudioStats : NSObject
/**
 * @locale zh
 * @brief 音频丢包率。此次统计周期内的音频上行丢包率，取值范围为 [0, 1] 。  
 */
/**
 * @locale en
 * @brief Audio packet loss rate. The audio uplink packet loss rate in this reference period is in the range of  [0,1]. 
 */
@property(assign, nonatomic) float audioLossRate;
/**
 * @locale zh
 * @brief 发送的码率。此次统计周期内的音频发送码率，单位为 kbps 。  
 */
/**
 * @locale en
 * @brief The bit rate of transmission. The audio transmission rate in the reference period is kbps. 
 */
@property(assign, nonatomic) float sentKBitrate;
/**
 * @locale zh
 * @brief 采集采样率。此次统计周期内的音频采集采样率信息，单位为 Hz 。  
 */
/**
 * @locale en
 * @brief Acquisition sampling rate. Audio sampling rate information collected in the reference period, in units of Hz. 
 */
@property(assign, nonatomic) NSInteger recordSampleRate;
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
@property(assign, nonatomic) NSInteger statsInterval;
/**
 * @locale zh
 * @brief 往返时延。单位为 ms 。  
 */
/**
 * @locale en
 * @brief Round-trip time. The unit is ms. 
 */
@property(assign, nonatomic) NSInteger rtt;
/**
 * @locale zh
 * @brief 音频声道数。  
 */
/**
 * @locale en
 * @brief Number of audio channels.   
 */
@property(assign, nonatomic) NSInteger numChannels;
/**
 * @locale zh
 * @brief 音频发送采样率。此次统计周期内的音频发送采样率信息，单位为 Hz 。  
 */
/**
 * @locale en
 * @brief Audio transmission sampling rate. Audio transmission sampling rate information in the reference period, in Hz. 
 */
@property(assign, nonatomic) NSInteger sentSampleRate;
/**
 * @locale zh
 * @brief 音频上行网络抖动，单位为 ms。  
 */
/**
 * @locale en
 * @brief Audio uplink network jitter in ms. 
 */
@property(assign, nonatomic) NSInteger jitter;
@end

/**
 * @locale zh
 * @type keytype
 * @brief 远端音频流统计信息，统计周期为 2s 。  <br>
 *        本地用户订阅远端音频流成功后，SDK 会周期性地通过 `onRemoteStreamStats`<br>
 *        通知本地用户订阅的音频流在此次统计周期内的接收状况。此数据结构即为回调给本地用户的参数类型。  
 */
/**
 * @locale en
 * @type keytype
 * @brief Remote audio stream statistics, reference period 2s. <br>
 *         After the remote audio stream subscription is successful, the SDK will periodically notify the local user of the reception status of the subscribed audio stream during this reference period through `onRemoteStreamStats`<br>
 *        . This data structure is the type of parameter that is called back to the local user. 
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCRemoteAudioStats : NSObject
/**
 * @locale zh
 * @brief 音频丢包率。统计周期内的音频下行丢包率，取值范围为 [0, 1] 。  
 */
/**
 * @locale en
 * @brief Audio packet loss rate. The audio downlink packet loss rate in the reference period, the value range is  [0,1]. 
 */
@property(assign, nonatomic) float audioLossRate;
/**
 * @locale zh
 * @brief 接收码率。统计周期内的音频接收码率，单位为 kbps 。  
 */
/**
 * @locale en
 * @brief Receiving bit rate. The audio reception rate in the reference period in kbps. 
 */
@property(assign, nonatomic) float receivedKBitrate;
/**
 * @locale zh
 * @brief 音频卡顿次数。统计周期内的卡顿次数。  
 */
/**
 * @locale en
 * @brief Number of audio cards. Number of cards in the reference period.   
 */
@property(assign, nonatomic) NSInteger stallCount;
/**
 * @locale zh
 * @brief 音频卡顿时长。统计周期内的卡顿时长，单位为 ms 。  
 */
/**
 * @locale en
 * @brief Audio Catton Duration. Catton duration in the reference period in ms. 
 */
@property(assign, nonatomic) NSInteger stallDuration;
/**
 * @locale zh
 * @brief 播放采样率。统计周期内的音频播放采样率信息，单位为 Hz 。  
 */
/**
 * @locale en
 * @brief Play sample rate. Audio playback sample rate information within the reference period in Hz. 
 */
@property(assign, nonatomic) NSInteger playoutSampleRate;
/**
 * @locale zh
 * @brief 用户体验级别的端到端延时。从发送端采集完成编码开始到接收端解码完成渲染开始的延时，单位为 ms 。  
 */
/**
 * @locale en
 * @brief End-to-end latency at the user experience level. The delay from the completion of encoding at the transmitting end to the completion of decoding at the receiving end, in units of ms. 
 */
@property(assign, nonatomic) NSInteger e2eDelay;
/**
 * @locale zh
 * @brief 统计间隔。此次统计周期的间隔，单位为 ms 。  
 */
/**
 * @locale en
 * @brief Statistical interval. The interval of this reference period is in ms. 
 */
@property(assign, nonatomic) NSInteger statsInterval;
/**
 * @locale zh
 * @brief 客户端到服务端数据传输的往返时延，单位为 ms。  
 */
/**
 * @locale en
 * @brief Round-trip time for client side to server level data transfer in ms. 
 */
@property(assign, nonatomic) NSInteger rtt;
/**
 * @locale zh
 * @brief 发送端——服务端——接收端全链路数据传输往返时延。单位为 ms 。  
 */
/**
 * @locale en
 * @brief The sender-server level-the receiver-link data transmission round-trip time. The unit is ms. 
 */
@property(assign, nonatomic) NSInteger totalRtt;
/**
 * @locale zh
 * @brief 远端用户发送的音频流质量。值含义参考 ByteRTCNetworkQuality{@link #ByteRTCNetworkQuality} 。  
 */
/**
 * @locale en
 * @brief The quality of the audio stream sent by the remote user. Value meaning reference ByteRTCNetworkQuality{@link #ByteRTCNetworkQuality}. 
 */
@property(assign, nonatomic) NSInteger quality;
/**
 * @locale zh
 * @brief 因引入 jitter buffer 机制导致的延时。单位为 ms 。  
 */
/**
 * @locale en
 * @brief The delay caused by the introduction of the jitter buffer mechanism. The unit is ms. 
 */
@property(assign, nonatomic) NSInteger jitterBufferDelay;
/**
 * @locale zh
 * @brief 音频声道数。  
 */
/**
 * @locale en
 * @brief Number of audio channels.   
 */
@property(assign, nonatomic) NSInteger numChannels;
/**
 * @locale zh
 * @brief 音频接收采样率。统计周期内接收到的远端音频采样率信息，单位为 Hz 。  
 */
/**
 * @locale en
 * @brief Audio reception sampling rate. Remote audio sample rate information received within the reference period, in Hz. 
 */
@property(assign, nonatomic) NSInteger receivedSampleRate;
/**
 * @locale zh
 * @brief 远端用户在加入房间后发生音频卡顿的累计时长占音频总有效时长的百分比。音频有效时长是指远端用户进房发布音频流后，除停止发送音频流和禁用音频模块之外的音频时长。
 */
/**
 * @locale en
 * @brief The accumulated length of the audio card occurs after the remote user joins the room as a percentage of the total effective length of the audio. The effective duration of audio refers to the duration of audio other than stopping sending audio streams and disabling audio modules after remote users enter the room to publish audio streams.
 */
@property(assign, nonatomic) NSInteger frozenRate;
/**
 * @locale zh
 * @brief 音频 PLC 样点总个数。  
 */
/**
 * @locale en
 * @brief Audio PLC Total number of sample points. 
 */
@property(assign, nonatomic) NSInteger concealedSamples;
/**
 * @locale zh
 * @brief 音频丢包补偿(PLC) 累计次数。  
 */
/**
 * @locale en
 * @brief PLC  cumulative times. 
 */
@property(assign, nonatomic) NSInteger concealmentEvent;
/**
 * @locale zh
 * @brief 音频解码采样率。统计周期内的音频解码采样率信息，单位为 Hz 。  
 */
/**
 * @locale en
 * @brief Audio decoding sample rate. Audio decoding sample rate information in the reference period in Hz. 
 */
@property(assign, nonatomic) NSInteger decSampleRate;
/**
 * @locale zh
 * @brief 此次订阅中，对远端音频流进行解码的累计耗时。单位为 s。
 */
/**
 * @locale en
 * @brief Cumulative decoding time in seconds of the remote audio stream in this subscription.
 */
@property(assign, nonatomic) NSInteger decDuration;
/**
 * @locale zh
 * @brief 视频下行网络抖动，单位为 ms。  
 */
/**
 * @locale en
 * @brief Video downlink network jitter in ms. 
 */
@property(assign, nonatomic) NSInteger jitter;
@end

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
BYTERTC_APPLE_EXPORT @interface ByteRTCLocalStreamStats : NSObject
/**
 * @locale zh
 * @brief 本地设备发送音频流的统计信息，详见 ByteRTCLocalAudioStats{@link #ByteRTCLocalAudioStats}
 */
/**
 * @locale en
 * @brief For statistics on audio streams sent by local devices. See ByteRTCLocalAudioStats{@link #ByteRTCLocalAudioStats}
 */
@property(strong, nonatomic) ByteRTCLocalAudioStats *_Nonnull audioStats;
/**
 * @locale zh
 * @brief 本地设备发送视频流的统计信息，详见 ByteRTCLocalVideoStats{@link #ByteRTCLocalVideoStats}
 */
/**
 * @locale en
 * @brief For statistics on video streams sent by local devices. See ByteRTCLocalVideoStats{@link #ByteRTCLocalVideoStats}
 */
@property(strong, nonatomic) ByteRTCLocalVideoStats *_Nonnull videoStats;
/**
 * @locale zh
 * @brief 所属用户的媒体流上行网络质量，详见 ByteRTCNetworkQuality{@link #ByteRTCNetworkQuality}
 * @deprecated since 3.36 and will be deleted in 3.51, use rtcRoom:onNetworkQuality:remoteQualities:{@link #ByteRTCRoomDelegate#rtcRoom:onNetworkQuality:remoteQualities:} instead
 */
/**
 * @locale en
 * @brief For the uplink network quality of the media stream of the user you belong to. See ByteRTCNetworkQuality{@link #ByteRTCNetworkQuality}
 * @deprecated since 3.45 and will be deleted in 3.51, use rtcRoom:onNetworkQuality:remoteQualities:{@link #ByteRTCRoomDelegate#rtcRoom:onNetworkQuality:remoteQualities:} instead
 */
@property(assign, nonatomic) ByteRTCNetworkQuality txQuality;
/**
 * @locale zh
 * @brief 所属用户的媒体流下行网络质量，详见 ByteRTCNetworkQuality{@link #ByteRTCNetworkQuality}
 * @deprecated since 3.36 and will be deleted in 3.51, use rtcRoom:onNetworkQuality:remoteQualities:{@link #ByteRTCRoomDelegate#rtcRoom:onNetworkQuality:remoteQualities:} instead
 */
/**
 * @locale en
 * @brief The downlink network quality of the media stream belongs to the user. See ByteRTCNetworkQuality{@link #ByteRTCNetworkQuality}
 * @deprecated since 3.45 and will be deleted in 3.51, use rtcRoom:onNetworkQuality:remoteQualities:{@link #ByteRTCRoomDelegate#rtcRoom:onNetworkQuality:remoteQualities:} instead
 */
@property(assign, nonatomic) ByteRTCNetworkQuality rxQuality;
/**
 * @locale zh
 * @brief 所属用户的媒体流是否为屏幕流。你可以知道当前统计数据来自主流还是屏幕流。
 */
/**
 * @locale en
 * @brief Whether the media stream belongs to the user is a screen stream. You can know whether the current statistics come from mainstream or screen stream.
 */
@property(nonatomic, assign) BOOL isScreen;
@end

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
 *         After the remote user subscribed to successfully publish the audio/video stream, the SDK will periodically notify the remote user of the reception status of the subscribed audio/video stream during this reference period through `onRemoteStreamStats`<br>
 *        . This data structure is the type of parameter that is called back to the local user. 
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCRemoteStreamStats : NSObject
/**
 * @locale zh
 * @brief 用户 ID 。音频来源的用户 ID 。  
 */
/**
 * @locale en
 * @brief User ID. The user ID of the audio source. 
 */
@property(copy, nonatomic) NSString *_Nonnull uid;
/**
 * @locale zh
 * @brief 远端音频流的统计信息，详见 ByteRTCRemoteAudioStats{@link #ByteRTCRemoteAudioStats}
 */
/**
 * @locale en
 * @brief For statistics on remote audio streams. See ByteRTCRemoteAudioStats{@link #ByteRTCRemoteAudioStats}
 */
@property(strong, nonatomic) ByteRTCRemoteAudioStats *_Nonnull audioStats;
/**
 * @locale zh
 * @brief 远端视频流的统计信息，详见 ByteRTCRemoteVideoStats{@link #ByteRTCRemoteVideoStats}
 */
/**
 * @locale en
 * @brief For statistics on remote video streams. See ByteRTCRemoteVideoStats{@link #ByteRTCRemoteVideoStats}
 */
@property(strong, nonatomic) ByteRTCRemoteVideoStats *_Nonnull videoStats;
/**
 * @locale zh
 * @brief 所属用户的媒体流上行网络质量，详见 ByteRTCNetworkQuality{@link #ByteRTCNetworkQuality}
 * @deprecated since 3.36 and will be deleted in 3.51, use rtcRoom:onNetworkQuality:remoteQualities:{@link #ByteRTCRoomDelegate#rtcRoom:onNetworkQuality:remoteQualities:} instead
 */
/**
 * @locale en
 * @hidden
 * @brief For the uplink network quality of the media stream of the user you belong to. See ByteRTCNetworkQuality{@link #ByteRTCNetworkQuality}
 * @deprecated since 3.45 and will be deleted in 3.51, use rtcRoom:onNetworkQuality:remoteQualities:{@link #ByteRTCRoomDelegate#rtcRoom:onNetworkQuality:remoteQualities:} instead
 */
@property(assign, nonatomic) ByteRTCNetworkQuality txQuality;
/**
 * @locale zh
 * @brief 所属用户的媒体流下行网络质量，详见 ByteRTCNetworkQuality{@link #ByteRTCNetworkQuality}
 * @deprecated since 3.36 and will be deleted in 3.51, use rtcRoom:onNetworkQuality:remoteQualities:{@link #ByteRTCRoomDelegate#rtcRoom:onNetworkQuality:remoteQualities:} instead
 */
/**
 * @locale en
 * @brief The downlink network quality of the media stream belongs to the user. See ByteRTCNetworkQuality{@link #ByteRTCNetworkQuality}
 * @deprecated since 3.45 and will be deleted in 3.51, use rtcRoom:onNetworkQuality:remoteQualities:{@link #ByteRTCRoomDelegate#rtcRoom:onNetworkQuality:remoteQualities:} instead
 */
@property(assign, nonatomic) ByteRTCNetworkQuality rxQuality;
/**
 * @locale zh
 * @brief 所属用户的媒体流是否为屏幕流。你可以知道当前统计数据来自主流还是屏幕流。
 */
/**
 * @locale en
 * @brief Whether the media stream belongs to the user is a screen stream. You can know whether the current statistics come from mainstream or screen stream.
 */
@property(nonatomic, assign) BOOL isScreen;
@end

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
BYTERTC_APPLE_EXPORT @interface ByteRTCUser : NSObject
/**
 * @locale zh
 * @brief 用户 ID
 */
/**
 * @locale en
 * @brief User ID
 */
@property(nonatomic, copy, nullable) NSString *userId;
/**
 * @locale zh
 * @brief 元信息
 */
/**
 * @locale en
 * @brief Meta information
 */
@property(nonatomic, copy, nullable) NSString *metaData;
@end

/**
 * @locale zh
 * @type keytype
 * @brief 用户信息
 */
/**
 * @locale en
 * @type keytype
 * @brief Information about the remote stream
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCRemoteStreamKey : NSObject
/**
 * @locale zh
 * @brief 用户 ID
 */
/**
 * @locale en
 * @brief The ID of the user who published the stream.
 */
@property(nonatomic, copy, nullable) NSString *userId;
/**
 * @locale zh
 * @brief 房间 ID
 */
/**
 * @locale en
 * @brief The ID of the room from which the stream was published.
 */
@property(nonatomic, copy, nullable) NSString *roomId;
/**
 * @locale zh
 * @brief 流属性，包括主流、屏幕流。参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 */
/**
 * @locale en
 * @brief Stream type. See ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 */
@property(nonatomic, assign) ByteRTCStreamIndex streamIndex;
@end

#pragma mark - EncryptHandler
/**
 * @locale zh
 * @type callback
 * @region 加密
 * @brief 自定义加密接口<br>
 * 注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。
 */
/**
 * @locale en
 * @type callback
 * @region  encryption
 * @brief  Custom encryption interface<br>
 * Note: Callback functions are thrown synchronously in a non-UI thread within the SDK. Therefore, you must not perform any time-consuming operations or direct UI operations within the callback function, as this may cause the app to crash.
 */
@protocol ByteRTCEncryptHandler <NSObject>

@required
/**
 * @locale zh
 * @type api
 * @region 加密
 * @brief 自定义加密。  <br>
 *        使用设定的自定义加密方式，对编码后传输前的音视频帧数据进行加密。<br>
 *        暂不支持对原始音视频帧进行加密。
 * @param rawData 原始音视频帧数据
 * @return 加密后的数据  <br>
 *        + 非空，表示加密后的数据  <br>
 *        + 为空，表示数据被丢弃
 * @note 
 *        + 使用此接口进行自定义加密前，你必须先设置自定义加密方式，参看 `setCustomizeEncryptHandler:`。<br>
 *        + 使用 onDecryptData:{@link #ByteRTCEncryptHandler#onDecryptData:} 对已加密的音视频帧数据进行解密。<br>
 *        + 返回的数据大小应控制在原始数据的 90% ~ 120% 范围以内，不然将被丢弃。
 */
/**
 * @locale en
 * @type api
 * @region Encryption
 * @brief Custom encryption.   <br>
 *        Encrypts audio & video frame data before transmission using the custom encryption method set.<br>
 *        Encryption of the original audio and video frames is currently not available.
 * @param rawData Original audio & video frame data
 * @return Encrypted data   <br>
 *         + Non-empty, indicating that the encrypted data <br>
 *         + Is empty, indicating that the data has been discarded
 * @note  
 *         + Before using this interface for custom encryption, you must first set the custom encryption method. See `setCustomizeEncryptHandler:`.<br>
 *         + Use onDecryptData:{@link #ByteRTCEncryptHandler#onDecryptData:} to decrypt encrypted audio & video frame data.<br>
 *         + The returned data size should be controlled within 90%~ 120% of the original data source, otherwise it will be discarded.
 */
- (NSData * _Nonnull) onEncryptData:(NSData * _Nonnull)rawData;

@required
/**
 * @locale zh
 * @type api
 * @region 加密
 * @brief 自定义解密。  <br>
 *        对自定义加密后的音视频帧数据进行解密。关于自定义加密，参看 onEncryptData:{@link #ByteRTCEncryptHandler#onEncryptData:}。
 * @param rawData 收到的已加密的音视频帧数据
 * @return 解密后的数据  <br>
 *        + 非空，表示解密后的数据  <br>
 *        + 为空，表示丢弃该帧
 * @note 
 *        + 使用此接口进行解密前，你必须先设定解密方式，参看 `setCustomizeEncryptHandler:`。<br>
 *        + 返回的数据大小应控制在原始数据的 90% ~ 120% 范围以内，不然将被丢弃。
 */
/**
 * @locale en
 * @type api
 * @region  encryption
 * @brief  Custom decryption.   <br>
 *         Decrypts custom encrypted audio & video frame data. For custom encryption, see onEncryptData:{@link #ByteRTCEncryptHandler#onEncryptData:}.
 * @param rawData  Received encrypted audio & video frame data
 * @return  Decrypted data   <br>
 *         + Non-empty, indicating that the decrypted data <br>
 *         + Is empty, indicating that the frame is discarded
 * @note  
 *         + Before using this interface to decrypt, you must first set the decryption method. See `setCustomizeEncryptHandler:`.<br>
 *         + The returned data size should be controlled within 90%~ 120% of the original data source, otherwise it will be discarded.
 */
- (NSData * _Nonnull) onDecryptData:(NSData * _Nonnull)rawData;
@end

#pragma mark - FileRecording

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
BYTERTC_APPLE_EXPORT @interface ByteRTCRecordingConfig : NSObject
/**
 * @locale zh
 * @brief 录制文件保存的绝对路径，需精确到文件夹，文件名由 RTC 自动生成。你需要确保对该路径具有读写权限。
 */
/**
 * @locale en
 * @brief The absolute folder path to save the recording file.The filename will be generated by RTC. You need to ensure that you have read and write permissions to this path.
 */
@property(strong, nonatomic) NSString* _Nullable dirPath;
/**
 * @locale zh
 * @brief 录制存储文件格式，参看 ByteRTCRecordingFileType{@link #ByteRTCRecordingFileType}
 */
/**
 * @locale en
 * @brief Record the stored file format. See ByteRTCRecordingFileType{@link #ByteRTCRecordingFileType}
 */
@property(assign, nonatomic) ByteRTCRecordingFileType recordingFileType;
@end

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
BYTERTC_APPLE_EXPORT @interface ByteRTCRecordingProgress : NSObject
/**
 * @locale zh
 * @brief 当前文件的累计录制时长，单位：毫秒
 */
/**
 * @locale en
 * @brief The cumulative recording time of the current file, in milliseconds
 */
@property(assign, nonatomic) unsigned long long duration;
/**
 * @locale zh
 * @brief 当前录制文件的大小，单位：byte
 */
/**
 * @locale en
 * @brief The size of the currently recorded file in bytes
 */
@property(assign, nonatomic) unsigned long long fileSize;
@end

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
BYTERTC_APPLE_EXPORT @interface ByteRTCRecordingInfo : NSObject
/**
 * @locale zh
 * @brief 录制文件的绝对路径，包含文件名和文件后缀
 */
/**
 * @locale en
 * @brief The absolute path of the recorded file, including the file name and file suffix
 */
@property(strong, nonatomic) NSString* _Nullable filePath;
/**
 * @locale zh
 * @brief 录制文件的视频编码类型，参看 ByteRTCVideoCodecType{@link #ByteRTCVideoCodecType}
 */
/**
 * @locale en
 * @brief For the video encoding type of the recorded file. See ByteRTCVideoCodecType{@link #ByteRTCVideoCodecType}
 */
@property(assign, nonatomic) ByteRTCVideoCodecType codecType;
/**
 * @locale zh
 * @brief 录制视频的宽，单位：像素。纯音频录制请忽略该字段
 */
/**
 * @locale en
 * @brief The width of the recorded video, in pixels. Please ignore this field for audio-only recording
 */
@property(nonatomic, assign) NSInteger width;
/**
 * @locale zh
 * @brief 录制视频的高，单位：像素。纯音频录制请忽略该字段
 */
/**
 * @locale en
 * @brief The height of the recorded video, the unit: pixels. Please ignore this field for audio-only recording
 */
@property(nonatomic, assign) NSInteger height;
@end

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
BYTERTC_APPLE_EXPORT @interface ByteRTCStreamSycnInfoConfig : NSObject

/**
 * @locale zh
 * @brief 流属性，主流或屏幕流。见 ByteRTCStreamIndex{@link #ByteRTCStreamIndex} 。
 */
/**
 * @locale en
 * @brief Stream properties, mainstream or screen streams. See ByteRTCStreamIndex{@link #ByteRTCStreamIndex}.
 */
@property(assign, nonatomic) ByteRTCStreamIndex streamIndex;
/**
 * @locale zh
 * @brief 消息发送的重复次数，取值范围是 [0,25]，建议设置为 [3,5]。
 */
/**
 * @locale en
 * @brief The number of duplicates sent by the message, the value range is  [0,25], it is recommended to set it to [3,5].
 */
@property(assign, nonatomic) int repeatCount;
/**
 * @locale zh
 * @brief 媒体流信息同步的流类型，见 ByteRTCSyncInfoStreamType{@link #ByteRTCSyncInfoStreamType} 。
 */
/**
 * @locale en
 * @brief For the stream type for media stream information synchronization. See ByteRTCSyncInfoStreamType{@link #ByteRTCSyncInfoStreamType}.
 */
@property(assign, nonatomic) ByteRTCSyncInfoStreamType streamType;
@end

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
BYTERTC_APPLE_EXPORT @interface ByteRTCForwardStreamConfiguration: NSObject
    /**
     * @locale zh
     * @brief 跨房间转发媒体流过程中目标房间 ID
     */
    /**
     * @locale en
     * @brief ID of the room where the media stream aims to relay to
     */
@property(strong, nonatomic) NSString* _Nullable roomId;
    /**
     * @locale zh
     * @brief 使用转发目标房间 RoomID 和 UserID 生成 Token。<br>
     *        测试时可使用控制台生成临时 Token，正式上线需要使用密钥 SDK 在你的服务端生成并下发 Token。<br>
     *        如果 Token 无效，转发失败。
     */
    /**
     * @locale en
     * @brief RoomId and UserId are required to generate the Token to forward media streams to the room.<br>
     *        During developing and testing, you can use temporary tokens generated on the console. At the production stage, Tokens are generated by the token generating application deployed on your server.<br>
     *        Forwarding will fail if the token is invalid.
     */
@property(strong, nonatomic) NSString* _Nullable token;
@end

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
BYTERTC_APPLE_EXPORT @interface ByteRTCForwardStreamStateInfo: NSObject
    /**
     * @locale zh
     * @brief 跨房间转发媒体流过程中目标房间 ID<br>
     *        空字符串代表所有目标房间
     */
    /**
     * @locale en
     * @brief ID of the room where the media stream aims to relay to<br>
     *        An Empty string is for all rooms.
     */
@property(strong, nonatomic) NSString* _Nullable roomId;
    /**
     * @locale zh
     * @brief 跨房间转发媒体流过程中该目标房间的状态，参看 ByteRTCForwardStreamState{@link #ByteRTCForwardStreamState}
     */
    /**
     * @locale en
     * @brief State of the room during relaying. Refer to ByteRTCForwardStreamState{@link #ByteRTCForwardStreamState} for more information.
     */
@property(assign, nonatomic) ByteRTCForwardStreamState state;
    /**
     * @locale zh
     * @brief 跨房间转发媒体流过程中该目标房间抛出的错误码，参看 ByteRTCForwardStreamError{@link #ByteRTCForwardStreamError}
     */
    /**
     * @locale en
     * @brief Error code from the room during relaying. Refer to ByteRTCForwardStreamError{@link #ByteRTCForwardStreamError} for more information.
     */
@property(assign, nonatomic) ByteRTCForwardStreamError error;
@end

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
BYTERTC_APPLE_EXPORT @interface ByteRTCForwardStreamEventInfo: NSObject
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
@property(strong, nonatomic) NSString* _Nullable roomId;
    /**
     * @locale zh
     * @brief 跨房间转发媒体流过程中该目标房间发生的事件，参看 ByteRTCForwardStreamEvent{@link #ByteRTCForwardStreamEvent}
     */
    /**
     * @locale en
     * @brief Event from the room during relaying. Refer to ByteRTCForwardStreamEvent{@link #ByteRTCForwardStreamEvent} for more information.
     */
@property(assign, nonatomic) ByteRTCForwardStreamEvent event;
@end

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
BYTERTC_APPLE_EXPORT @interface ByteRTCNetworkQualityStats: NSObject
/**
 * @locale zh
 * @brief 用户 ID
 */
/**
 * @locale en
 * @brief User ID
 */
@property(strong, nonatomic) NSString* _Nonnull uid;
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
@property(assign, nonatomic) double lossRatio;
/**
 * @locale zh
 * @brief 当 `uid` 为本地用户时有效，客户端到服务端的往返延时（RTT），单位：ms
 */
/**
 * @locale en
 * @brief Round-trip time (RTT) from client to server. Effective for the local user. Unit: ms
 */
@property(assign, nonatomic) int rtt;
/**
 * @locale zh
 * @brief 本端的音视频 RTP 包 2 秒内的平均传输速率，单位：bps<br>
 *        当 `uid` 为本地用户时，代表发送速率。<br>
 *        当 `uid` 为远端用户时，代表所有订阅流的接收速率。
 */
/**
 * @locale en
 * @brief Average transmission rate of the media RTP packages in 2s. unit: bps<br>
 *        For a local user, it is the packet-sending speed.<br>
 *        For a more user, it is the speed of receiving all the subscribed medias.
 */
@property(assign, nonatomic) int totalBandwidth;
/**
 * @locale zh
 * @brief 上行网络质量评分，详见 ByteRTCNetworkQuality{@link #ByteRTCNetworkQuality}。
 */
/**
 * @locale en
 * @brief Tx network quality grade. Refer to ByteRTCNetworkQuality{@link #ByteRTCNetworkQuality} for details.
 */
@property(assign, nonatomic) ByteRTCNetworkQuality txQuality;
/**
 * @locale zh
 * @brief 下行网络质量评分，详见 ByteRTCNetworkQuality{@link #ByteRTCNetworkQuality}。
 */
/**
 * @locale en
 * @brief Rx network quality grade. Refer to ByteRTCNetworkQuality{@link #ByteRTCNetworkQuality} for details.
 */
@property(assign, nonatomic) ByteRTCNetworkQuality rxQuality;
@end

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
BYTERTC_APPLE_EXPORT @interface ByteRTCNetworkTimeInfo: NSObject
/**
 * @locale zh
 * @brief 网络时间，单位：ms
 */
/**
 * @locale en
 * @brief Network time. Unit: ms
 */
@property(assign, nonatomic) int64_t timestamp;
@end

#pragma mark - ByteRTCDeviceCollection
/**
 * @locale zh
 * @type api
 * @hidden(iOS)
 * @brief 音视频设备相关的信息
 */
/**
 * @locale en
 * @type api
 * @hidden(iOS)
 * @brief Media Device Info
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCDeviceCollection : NSObject
/**
 * @locale zh
 * @type api
 * @region 引擎管理
 * @brief 获取当前音视频设备数量
 * @return 音视频设备数量
 */
/**
 * @locale en
 * @type api
 * @region engine management
 * @brief Get the number of media devices
 * @return Number of media devices
 */
- (int)getCount;
/**
 * @locale zh
 * @type api
 * @region 引擎管理
 * @brief 根据索引号，获取设备信息
 * @param index 设备索引号，从 0 开始，注意需小于 getCount{@link #ByteRTCDeviceCollection#getCount} 返回值。
 * @param deviceName 设备名称
 * @param deviceID 设备 ID
 * @return  
 *        + 0：方法调用成功  <br>
 *        + !0：方法调用失败  
 */
/**
 * @locale en
 * @type api
 * @region Engine management
 * @brief Get the information of the specific device
 * @param  index Device index number, starting from 0. The index must be less than the return value of getCount{@link #ByteRTCDeviceCollection#getCount}.
 * @param  deviceName device name
 * @param  deviceID device ID
 * @return   
 *         + 0: Success. <br>
 *         + !0: failure 
 */
- (int)getDevice:(int)index DeviceName:(NSString * _Nonnull * _Nonnull)deviceName DeviceID:(NSString * _Nonnull * _Nonnull) deviceID;
@end

/**
 * @locale zh
 * @type keytype
 * @brief 音频dump状态。  
 */
/**
 * @locale en
 * @type keytype
 * @brief  audio dump statue.   
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioDumpStatus){
    /**
     * @locale zh
     * @brief 音频dump启动失败
     */
    /**
     * @locale en
     * @brief audio dump start failure
     */
    ByteRTCAudioDumpStartFailure = 0,
    /**
     * @locale zh
     * @brief 音频dump启动成功
     */
    /**
     * @locale en
     * @brief audio dump start success
     */
    ByteRTCAudioDumpStartSuccess = 1,
    /**
     * @locale zh
     * @brief 音频dump停止失败
     */
    /**
     * @locale en
     * @brief audio dump stop failure
     */
    ByteRTCAudioDumpStopFailure = 2,
    /**
     * @locale zh
     * @brief 音频dump停止成功
     */
    /**
     * @locale en
     * @brief audio dump stop success
     */
    ByteRTCAudioDumpStopSuccess = 3,
    /**
     * @locale zh
     * @brief 音频dump运行失败
     */
    /**
     * @locale en
     * @brief audio dump running failure
     */
    ByteRTCAudioDumpRunningFailure = 4,
    /**
     * @locale zh
     * @brief 音频dump运行成功
     */
    /**
     * @locale en
     * @brief audio dump ruinning success
     */
    ByteRTCAudioDumpRunningSuccess = 5,
};


/**
 * @locale zh
 * @type keytype
 * @brief 通话前探测的停止原因<br>
 *        `rtcEngine:onNetworkDetectionStopped:` 回调的参数类型
 */
/**
 * @locale en
 * @type keytype
 * @brief  Reason for stopping pre-call detection
 */
typedef NS_ENUM(NSUInteger, ByteRTCNetworkDetectionStopReason) {
    /**
     * @locale zh
     * @brief 用户主动停止。
     */
    /**
     * @locale en
     * @brief The user actively stops.
     */
    ByteRTCNetworkDetectionStopReasonUser = 0,
    /**
     * @locale zh
     * @brief 探测超过三分钟。
     */
    /**
     * @locale en
     * @brief Detection takes more than three minutes.
     */
    ByteRTCNetworkDetectionStopReasonTimeout = 1,
    /**
     * @locale zh
     * @brief 探测网络连接断开。<br>
     *        当超过 12s 没有收到回复，SDK 将断开网络连接，并且不再尝试重连。
     */
    /**
     * @locale en
     * @brief Probe network connection disconnected.
     */
    ByteRTCNetworkDetectionStopReasonConnectionLost = 2,
    /**
     * @locale zh
     * @brief 本地开始推拉流，停止探测。
     */
    /**
     * @locale en
     * @brief Begin push-pull flow and stop probing.
     */
    ByteRTCNetworkDetectionStopReasonStreaming = 3,
    /**
     * @locale zh
     * @brief 网络探测失败，内部异常
     */
    /**
     * @locale en
     * @brief Network probe failure, internal anomaly
     */
    ByteRTCNetworkDetectionStopReasonInnerErr = 4,
};

/**
 * @locale zh
 * @type errorcode
 * @brief 开始探测的返回值<br>
 *        `startNetworkDetection:uplinkBandwidth:downlink:downlinkBandwidth:` 返回对象类型
 */
/**
 * @locale en
 * @type errorcode
 * @brief  Return value to start probing
 */
typedef NS_ENUM(NSInteger, ByteRTCNetworkDetectionStartReturn) {
    /**
     * @locale zh
     * @brief 成功开始探测。
     */
    /**
     * @locale en
     * @brief Successfully initiated detection.
     */
    ByteRTCNetworkDetectionStartReturnSuccess = 0,
    /**
     * @locale zh
     * @brief 开始探测失败。参数错误，上下行探测均为 `false`，或期望带宽超过了范围 [100,10000]
     */
    /**
     * @locale en
     * @brief Failed to start probing. Parameter error, both uplink and downlink probes are false, or the expected bandwidth exceeds the range [100,10000]
     */
    ByteRTCNetworkDetectionStartReturnParamErr = 1,
    /**
     * @locale zh
     * @brief 开始探测失败。失败原因为，本地已经开始推拉流
     */
    /**
     * @locale en
     * @brief Failed to start probing. Push-pull flow has begun
     */
    ByteRTCNetworkDetectionStartReturnStreaming = 2,
    /**
     * @locale zh
     * @brief 已经开始探测，无需重复开启
     */
    /**
     * @locale en
     * @brief Has begun to detect
     */
    ByteRTCNetworkDetectionStartReturnStarted = 3,
    /**
     * @locale zh
     * @brief 不支持该功能
     */
    /**
     * @locale en
     * @brief Not Support
     */
    ByteRTCNNetworkDetectionStartReturnNotSupport = 4,
};

/**
 * @locale zh
 * @type keytype
 * @brief 通话前探测链接的类型<br>
 *        `rtcEngine:onNetworkDetectionResult:quality:rtt:lostRate:bitrate:jitter:` 回调的参数类型
 */
/**
 * @locale en
 * @type keytype
 * @brief The type of probe link before the call.
 */
typedef NS_ENUM(NSUInteger, ByteRTCNetworkDetectionLinkType) {
    /**
     * @locale zh
     * @brief 上行网络探测。
     */
    /**
     * @locale en
     * @brief Uplink network probing.
     */
    ByteRTCNetworkDetectionLinkTypeUp = 0,
    /**
     * @locale zh
     * @brief 下行网络探测。
     */
    /**
     * @locale en
     * @brief Downlink network probing.
     */
    ByteRTCNetworkDetectionLinkTypeDown = 1,
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
typedef NS_ENUM(NSUInteger, ByteRTCHardwareEchoDetectionResult) {
    /**
     * @locale zh
     * @brief 主动调用 `stopHardwareEchoDetection` 结束流程时，未有回声检测结果。
     */
    /**
     * @locale en
     * @brief Detection is stopped by the call of `stopHardwareEchoDetection` before the SDK reports the detection result.
     */
    ByteRTCHardwareEchoDetectionCanceled = 0,
    /**
     * @locale zh
     * @brief 未检测出结果。建议重试，如果仍然失败请联系技术支持协助排查。
     */
    /**
     * @locale en
     * @brief Unknown state<br>
     *        Contact us if you retry several times but keep failing.
     */
    ByteRTCHardwareEchoDetectionUnknown = 1,
    /**
     * @locale zh
     * @brief 无回声
     */
    /**
     * @locale en
     * @brief Excellent <br>
     *        No echo issue is detected.
     */
    ByteRTCHardwareEchoDetectionNormal = 2,
    /**
     * @locale zh
     * @brief 有回声。可通过 UI 建议用户使用耳机设备入会。
     */
    /**
     * @locale en
     * @brief Echo <br>
     *        Echo issue is detected. Recommend the user join the call with a headset through the interface.
     */
    ByteRTCHardwareEchoDetectionPoor = 3,
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
typedef NS_ENUM(NSUInteger, ByteRTCAudioSelectionPriority) {
    /**
     * @locale zh
     * @brief 正常，参加音频选路
     */
    /**
     * @locale en
     * @brief Normal whether the stream can be subscribed is determined by the result of audio selection.
     */
    ByteRTCAudioSelectionPriorityNormal = 0,
    /**
     * @locale zh
     * @brief 高优先级，跳过音频选路
     */
    /**
     * @locale en
     * @brief Hight priority with which the stream can skip the audio selection and always be subscribable.
     */
    ByteRTCAudioSelectionPriorityHigh = 1
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
typedef NS_ENUM(NSInteger,ByteRTCSetRoomExtraInfoResult) {
    /**
     * @locale zh
     * @brief 设置房间附加信息成功
     */
    /**
     * @locale en
     * @brief Success.
     */
    ByteRTCSetRoomExtraInfoResultSuccess = 0,
    /**
     * @locale zh
     * @brief 设置失败，尚未加入房间
     */
    /**
     * @locale en
     * @brief Failure. You are not in the room.
     */
    ByteRTCSetRoomExtraInfoResultNotJoinRoom = -1,
    /**
     * @locale zh
     * @brief 设置失败，key 指针为空
     */
    /**
     * @locale en
     * @brief Failure. The key pointer is null.
     */
    ByteRTCSetRoomExtraInfoResultKeyIsNull = -2,
    /**
     * @locale zh
     * @brief 设置失败，value 指针为空
     */
    /**
     * @locale en
     * @brief Failure. The value pointer is null.
     */
    ByteRTCSetRoomExtraInfoResultValueIsNull = -3,
    /**
     * @locale zh
     * @brief 设置失败，未知错误
     */
    /**
     * @locale en
     * @brief Failure. Unknown error.
     */
    ByteRTCSetRoomExtraInfoResultUnknow = -99,
    /**
     * @locale zh
     * @brief 设置失败，key 长度为 0
     */
    /**
     * @locale en
     * @brief Failure. The key length is 0.
     */
    ByteRTCSetRoomExtraInfoResultKeyIsEmpty = -400,
    /**
     * @locale zh
     * @brief 调用 `setRoomExtraInfo` 过于频繁，建议不超过 10 次/秒。
     */
    /**
     * @locale en
     * @brief Failure. Excessively frequent setting. 10 times per second is preferable.
     */
    ByteRTCSetRoomExtraInfoResultTooOften = -406,
    /**
     * @locale zh
     * @brief 设置失败，用户已调用 `setUserVisibility` 将自身设为隐身状态。
     */
    /**
     * @locale en
     * @brief Failure. Invisible users are not allowed to call `setRoomExtraInfo`.
     */
    ByteRTCSetRoomExtraInfoResultSilentUser = -412,
    /**
     * @locale zh
     * @brief 设置失败，Key 长度超过 10 字节
     */
    /**
     * @locale en
     * @brief Failure. Key length exceeds 10 bytes.
     */
    ByteRTCSetRoomExtraInfoResultKeyTooLong = -413,
    /**
     * @locale zh
     * @brief 设置失败，value 长度超过 128 字节
     */
    /**
     * @locale en
     * @brief Failure. Value length exceeds 128 bytes.
     */
    ByteRTCSetRoomExtraInfoResultValueTooLong = -414,
    /**
     * @locale zh
     * @brief 设置失败，服务器错误
     */
    /**
     * @locale en
     * @brief Failure. Server error.
     */
    ByteRTCSetRoomExtraInfoResultServerError = -500
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
typedef NS_ENUM(NSInteger, ByteRTCEffectErrorType) {
    /**
     * @locale zh
     * @hidden 仅用于会议
     * @brief 虚拟背景设置错误。
     */
    /**
     * @locale en
     * @brief Failed to set virtual background.
     */
    ByteRTCEffectErrorVirtualBackgroundFailure = 1,
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
    ByteRTCEffectErrorChildProcTerminate = 2
};

#pragma mark - ByteRTCSubtitle
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
typedef NS_ENUM(NSInteger, ByteRTCSubtitleState) {
    /**
     * @locale zh
     * @brief 开启字幕。
     */
    /**
     * @locale en
     * @brief Subtitles are on. 
     */
    ByteRTCSubtitleStateStarted = 0,
    /**
     * @locale zh
     * @brief 关闭字幕。
     */
    /**
     * @locale en
     * @brief Subtitles are off.
     */
    ByteRTCSubtitleStateStoped = 1,
    /**
     * @locale zh
     * @brief 字幕任务出现错误。
     */
    /**
     * @locale en
     * @brief Errors occurred in the subtitling task. 
     */
    ByteRTCSubtitleStateError = 2
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
typedef NS_ENUM(NSInteger, ByteRTCSubtitleMode) {
    /**
     * @locale zh
     * @brief 识别模式。在此模式下，房间内用户语音会被转为文字。
     */
    /**
     * @locale en
     * @brief The recognition mode. In this mode, the speech of a users in the room will be recognized and converted into captions.
     */
    ByteRTCSubtitleModeRecognition = 0,
    /**
     * @locale zh
     * @brief 翻译模式。在此模式下，房间内用户语音会先被转为文字，再被翻译为目标语言。
     */
    /**
     * @locale en
     * @brief The translation mode. In this mode, the speech of a users in the room will be converted into captions and then translated.
     */
    ByteRTCSubtitleModeTranslation = 1
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
typedef NS_ENUM(NSInteger, ByteRTCSubtitleErrorCode) {
    /**
     * @locale zh
     * @brief 客户端无法识别云端媒体处理发送的错误码。 
     */
    /**
     * @locale en
     * @brief The client side failed to identity error codes sent by cloud media processing.
     */
    ByteRTCSubtitleErrorCodeUnknow = -1,
    /**
     * @locale zh
     * @brief 字幕已开启。
     */
    /**
     * @locale en
     * @brief Subtitles are turned on. 
     */
    ByteRTCSubtitleErrorCodeSuccess = 0,
    /**
     * @locale zh
     * @brief 云端媒体处理内部出现错误，请联系技术支持。
     */
    /**
     * @locale en
     * @brief Errors occurred concerning cloud media processing. Please contact the technical support.
     */
    ByteRTCSubtitleErrorCodePostProcessError = 1,
    /**
     * @locale zh
     * @brief 第三方服务连接失败，请联系技术支持。
     */
    /**
     * @locale en
     * @brief Failed to connect to the third-party service. Please contact the technical support.
     */
    ByteRTCSubtitleErrorCodeASRConnectionError = 2,
    /**
     * @locale zh
     * @brief 第三方服务内部出现错误，请联系技术支持。
     */
    /**
     * @locale en
     * @brief Errors occurred concerning the third-party service. Please contact the technical support.
     */
    ByteRTCSubtitleErrorCodeASRServiceError = 3,
    /**
     * @locale zh
     * @brief 未进房导致调用`startSubtitle`失败。请加入房间后再调用此方法。
     */
    /**
     * @locale en
     * @brief Failed to call `startSubtitle`. Please join the room first. 
     */
    ByteRTCSubtitleErrorCodeBeforeJoinRoom = 4,
    /**
     * @locale zh
     * @brief 字幕已开启，无需重复调用 `startSubtitle`。
     */
    /**
     * @locale en
     * @brief Subtitles are already on. There is no need to call `startSubtitle` again. 
     */
    ByteRTCSubtitleErrorCodeAlreadyOn = 5,
    /**
     * @locale zh
     * @brief 用户选择的目标语言目前暂不支持。
     */
    /**
     * @locale en
     * @brief The target language you chose is not Unsupported.
     */
    ByteRTCSubtitleErrorCodeUnsupportedLanguage = 6,
    /**
     * @locale zh
     * @brief 云端媒体处理超时未响应，请联系技术支持。
     */
    /**
     * @locale en
     * @brief Cloud media processing is timeout. Please contact the technical support.
     */
    ByteRTCSubtitleErrorCodePostProcessTimeout = 7
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
BYTERTC_APPLE_EXPORT @interface ByteRTCSubtitleConfig : NSObject
/**
 * @locale zh
 * @brief 字幕模式。可以根据需要选择识别和翻译两种模式。开启识别模式，会将识别后的用户语音转化成文字；开启翻译模式，会在语音识别后进行翻译。参看 ByteRTCSubtitleMode{@link #ByteRTCSubtitleMode}。
 */
/**
 * @locale en
 * @brief Subtitle mode. You can choose between the recognition and translation modes based on your needs. In the recognition mode, the speech of the speaker in the room will be recognized and converted into captions. In the translation mode, the transcribed text will be translated. Refer to ByteRTCSubtitleMode{@link #ByteRTCSubtitleMode} for more details.
 */
@property(assign, nonatomic) ByteRTCSubtitleMode mode;
/**
 * @locale zh
 * @brief 目标翻译语言。可点击 [语言支持](https://www.volcengine.com/docs/4640/35107#%F0%9F%93%A2%E5%AE%9E%E6%97%B6%E8%AF%AD%E9%9F%B3%E7%BF%BB%E8%AF%91) 查看翻译服务最新支持的语种信息。
 */
/**
 * @locale en
 * @brief Target language. 
 */
@property(copy, nonatomic) NSString *_Nonnull targetLanguage;
@end
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
BYTERTC_APPLE_EXPORT @interface ByteRTCSubtitleMessage : NSObject
/**
 * @locale zh
 * @brief 说话者的用户ID。
 */
/**
 * @locale en
 * @brief The speaker's ID.
 */
@property(copy, nonatomic) NSString *_Nonnull userId;
/**
 * @locale zh
 * @brief 语音识别或翻译后的文本, 采用 UTF-8 编码。
 */
/**
 * @locale en
 * @brief Transcribed or translated texts of the speaker's speech, encoded in UTF-8 format.
 */
@property(copy, nonatomic) NSString *_Nonnull text;
/**
 * @locale zh
 * @brief 字幕语种，根据字幕模式为原文或译文对应的语种。
 */
/**
 * @locale en
 * @brief The language of the transcribed or translated text according to the subtitle mode.
 */
@property(copy, nonatomic) NSString *_Nonnull language;
/**
 * @locale zh
 * @brief 字幕模式，参看 ByteRTCSubtitleMode{@link #ByteRTCSubtitleMode}。
 */
/**
 * @locale en
 * @brief The subtitle mode. Refer to ByteRTCSubtitleMode{@link #ByteRTCSubtitleMode} for more details. 
 */
@property(assign, nonatomic) NSInteger mode;
/**
 * @locale zh
 * @brief 语音识别或翻译后形成的文本的序列号，同一发言人的完整发言和不完整发言会按递增顺序单独分别编号。
 */
/**
 * @locale en
 * @brief Incremental sequence numbers assigned to transcribed or translated texts of the speaker's speech. Complete and incomplete sentences are numbered individually.
 */
@property(assign, nonatomic) NSInteger sequence;
/**
 * @locale zh
 * @brief 语音识别出的文本是否为一段完整的一句话。 True 代表是, False 代表不是。
 */
/**
 * @locale en
 * @brief Whether transcribed texts are complete sentences. True means yes and False means no.
 */
@property(assign, nonatomic) BOOL definite;
@end

BYTERTC_APPLE_EXPORT @interface ByteRTCDeadLockMsg : NSObject
@property (nonatomic, strong) NSString* _Nonnull threadName;
@property(nonatomic) NSInteger lastingTimes;
@end
