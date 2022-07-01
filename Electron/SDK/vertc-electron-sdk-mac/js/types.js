"use strict";
//
//  types.ts
Object.defineProperty(exports, "__esModule", { value: true });
//////////////////////////////////////////////////////////////////////////
// VRTCEngine here
var RenderMode;
(function (RenderMode) {
    RenderMode[RenderMode["FIT"] = 1] = "FIT";
    RenderMode[RenderMode["HIDDEN"] = 2] = "HIDDEN";
})(RenderMode = exports.RenderMode || (exports.RenderMode = {}));
/**
 * @type keytype
 * @brief 用户角色。
 *        房间模式为直播、游戏、云游戏模式时的用户角色。
 */
var ClientRoleType;
(function (ClientRoleType) {
    /**
     * @brief 主播角色，用户既可以发布流到房间中，也可以从房间中订阅流。
     */
    ClientRoleType[ClientRoleType["CLIENT_ROLE_BROADCASTER"] = 1] = "CLIENT_ROLE_BROADCASTER";
    /**
     * @brief 观众角色，用户只能从房间中订阅流，不能向房间中发布流，房间中的其他用户可以感知到该用户在房间中。
     */
    ClientRoleType[ClientRoleType["CLIENT_ROLE_AUDIENCE"] = 2] = "CLIENT_ROLE_AUDIENCE";
    /**
     * @brief
     * 静默观众模式，除了满足观众角色的限制外，房间中的其他用户无法感知到该用户在房间中，即该用户加入退出房间和更新用户属性等行为不会通知给房间中的其他用户。
     */
    ClientRoleType[ClientRoleType["CLIENT_ROLE_SILENT_AUDIENCE"] = 3] = "CLIENT_ROLE_SILENT_AUDIENCE";
})(ClientRoleType = exports.ClientRoleType || (exports.ClientRoleType = {}));
;
/**
 * @type keytype
 * @brief 房间模式
 *        房间使用的场景模式。
 */
var ChannelProfileType;
(function (ChannelProfileType) {
    /**
     * @brief 通信模式。该房间模式下，房间内所有用户都可以发布和订阅流。适用于 IM 场景。
     */
    ChannelProfileType[ChannelProfileType["CHANNEL_PROFILE_COMMUNICATION"] = 0] = "CHANNEL_PROFILE_COMMUNICATION";
    /**
     * @brief 直播模式。该房间模式下，用户有主播、观众、静默观众三种可选角色，可以通过调用方法 setClientRole{@link 85532#SetClientRole} 设置。主播可以发布和订阅流，观众和静默观众只能订阅流。适用于直播、教育大班课等场景。
     */
    ChannelProfileType[ChannelProfileType["CHANNEL_PROFILE_LIVE_BROADCASTING"] = 1] = "CHANNEL_PROFILE_LIVE_BROADCASTING";
    /**
     * @brief 游戏模式。该房间模式下，用户角色同直播模式。适用于游戏场景。
     */
    ChannelProfileType[ChannelProfileType["CHANNEL_PROFILE_GAME"] = 2] = "CHANNEL_PROFILE_GAME";
    /**
     * @brief 云游戏模式。该房间模式下，用户角色同直播模式。同时 SDK 会开启 DataChannel （详见方法 sendDataChannnelMessage{@link 85532#SendDataChannnelMessage} ）功能并使用低延时设置。适用于云游戏场景。
     */
    ChannelProfileType[ChannelProfileType["CHANNEL_PROFILE_CLOUD_GAME"] = 3] = "CHANNEL_PROFILE_CLOUD_GAME";
})(ChannelProfileType = exports.ChannelProfileType || (exports.ChannelProfileType = {}));
;
/**
 * @hidden
 */
var SubscribeState;
(function (SubscribeState) {
    /**
     * @brief 订阅流成功
     */
    SubscribeState[SubscribeState["SUB_STATE_SUCCESS"] = 0] = "SUB_STATE_SUCCESS";
    /**
     * @hidden
     */
    SubscribeState[SubscribeState["SUB_STATE_FAILED_NOT_IN_ROOM"] = 1] = "SUB_STATE_FAILED_NOT_IN_ROOM";
    /**
     * @brief 没有找到流
     */
    SubscribeState[SubscribeState["SUB_STATE_FAILED_STREAM_NOT_FOUND"] = 2] = "SUB_STATE_FAILED_STREAM_NOT_FOUND";
})(SubscribeState = exports.SubscribeState || (exports.SubscribeState = {}));
;
;
;
;
var ScaleMode;
(function (ScaleMode) {
    /**
     * @brief 自由模式，默认使用FitWithCropping模式
     */
    ScaleMode[ScaleMode["Auto"] = 0] = "Auto";
    /**
     * @brief 视频尺寸进行缩放和拉伸以充满显示视窗
     */
    ScaleMode[ScaleMode["Stretch"] = 1] = "Stretch";
    /**
     * @brief
     * 优先保证视窗被填满。视频尺寸等比缩放，直至整个视窗被视频填满。如果视频长宽与显示窗口不同，多出的视频将被截掉
     */
    ScaleMode[ScaleMode["FitWithCropping"] = 2] = "FitWithCropping";
    /**
     * @brief
     * 优先保证视频内容全部显示。视频尺寸等比缩放，直至视频窗口的一边与视窗边框对齐。如果视频长宽与显示窗口不同，视窗上未被填满的区域将被涂黑
     */
    ScaleMode[ScaleMode["FitWithFilling"] = 3] = "FitWithFilling";
})(ScaleMode = exports.ScaleMode || (exports.ScaleMode = {}));
/**
 * @type keytype
 * @brief 视频的编码类型
 */
var VideoCodecType;
(function (VideoCodecType) {
    /**
     * @brief 未知类型
     */
    VideoCodecType[VideoCodecType["kVideoCodecUnknown"] = 0] = "kVideoCodecUnknown";
    /**
     * @brief 标准H264
     */
    VideoCodecType[VideoCodecType["kVideoCodecH264"] = 1] = "kVideoCodecH264";
    /**
     * @brief 标准ByteVC1
     */
    VideoCodecType[VideoCodecType["kVideoCodecByteVC1"] = 2] = "kVideoCodecByteVC1";
})(VideoCodecType = exports.VideoCodecType || (exports.VideoCodecType = {}));
;
/**
 * @type keytype
 * @brief 视频编码模式
 */
var CodecMode;
(function (CodecMode) {
    /**
     * @brief 自动选择
     */
    CodecMode[CodecMode["AutoMode"] = 0] = "AutoMode";
    /**
     * @brief 硬编码
     */
    CodecMode[CodecMode["HardwareMode"] = 1] = "HardwareMode";
    /**
     * @brief 软编码
     */
    CodecMode[CodecMode["SoftwareMode"] = 2] = "SoftwareMode";
})(CodecMode = exports.CodecMode || (exports.CodecMode = {}));
;
/**
 * @type keytype
 * @brief 视频编码质量偏好
 *      网络不好时的编码策略
 */
var EncodePreference;
(function (EncodePreference) {
    /**
     * @brief 关闭
     */
    EncodePreference[EncodePreference["EncodePreferenceDisabled"] = 0] = "EncodePreferenceDisabled";
    /**
     * @brief 保持帧率
     */
    EncodePreference[EncodePreference["EncodePreferenceFramerate"] = 1] = "EncodePreferenceFramerate";
    /**
     * @brief 保持画质
     */
    EncodePreference[EncodePreference["EncodePreferenceQuality"] = 2] = "EncodePreferenceQuality";
    /**
     * @brief 平衡模式
     */
    EncodePreference[EncodePreference["EncodePreferenceBalance"] = 3] = "EncodePreferenceBalance";
})(EncodePreference = exports.EncodePreference || (exports.EncodePreference = {}));
;
exports.SEND_KBPS_AUTO_CALCULATE = -1;
exports.SEND_KBPS_DISABLE_VIDEO_SEND = 0;
;
;
;
;
/**
 * @type keytype
 * @region 音频管理
 * @brief 音频帧类型
 */
var AudioFrameType;
(function (AudioFrameType) {
    /**
     * @brief PCM 16bit
     */
    AudioFrameType[AudioFrameType["kFrameTypePCM16"] = 0] = "kFrameTypePCM16";
})(AudioFrameType = exports.AudioFrameType || (exports.AudioFrameType = {}));
;
/**
* @type keytype
* @brief 音频声道。
*/
var AudioChannel;
(function (AudioChannel) {
    /**
     * @brief 自动声道，适用于从 SDK 获取音频数据，使用 SDK 内部处理的声道，不经过 resample。  <br>
     *        当你需要从 SDK 获取音频数据时，若对声道没有强依赖，建议设置成该值，可以通过避免 resample 带来一些性能优化。
     */
    AudioChannel[AudioChannel["kAudioChannelAuto"] = -1] = "kAudioChannelAuto";
    /**
     * @brief 单声道
     */
    AudioChannel[AudioChannel["kAudioChannelMono"] = 1] = "kAudioChannelMono";
    /**
     * @brief 双声道
     */
    AudioChannel[AudioChannel["kAudioChannelStereo"] = 2] = "kAudioChannelStereo";
})(AudioChannel = exports.AudioChannel || (exports.AudioChannel = {}));
;
/**
 * @type keytype
 * @brief 音频采样率，单位为 HZ。 <br>
 */
var AudioSampleRate;
(function (AudioSampleRate) {
    /**
     * @brief 自动采样率，适用于从 SDK 获取音频数据，使用 SDK 内部处理的采样率，不经过 resample。  <br>
     *        当你需要从 SDK 获取音频数据时，若对采样率没有强依赖，建议设置成该值，可以通过避免 resample 带来一些性能优化。
     */
    AudioSampleRate[AudioSampleRate["kAudioSampleRateAuto"] = -1] = "kAudioSampleRateAuto";
    /**
     * @brief 8000 采样率
     */
    AudioSampleRate[AudioSampleRate["kAudioSampleRate8000"] = 8000] = "kAudioSampleRate8000";
    /**
     * @brief 16000 采样率
     */
    AudioSampleRate[AudioSampleRate["kAudioSampleRate16000"] = 16000] = "kAudioSampleRate16000";
    /**
     * @brief 32000 采样率
     */
    AudioSampleRate[AudioSampleRate["kAudioSampleRate32000"] = 32000] = "kAudioSampleRate32000";
    /**
     * @brief 44100 采样率
     */
    AudioSampleRate[AudioSampleRate["kAudioSampleRate44100"] = 44100] = "kAudioSampleRate44100";
    /**
     * @brief 48000 采样率
     */
    AudioSampleRate[AudioSampleRate["kAudioSampleRate48000"] = 48000] = "kAudioSampleRate48000";
})(AudioSampleRate = exports.AudioSampleRate || (exports.AudioSampleRate = {}));
;
/**
 * @type keytype
 * @brief SDK 与信令服务器连接状态。
 */
var ConnectionState;
(function (ConnectionState) {
    /**
     * @brief 连接断开。
     */
    ConnectionState[ConnectionState["kConnectionStateDisconnected"] = 1] = "kConnectionStateDisconnected";
    /**
     * @brief 首次连接，正在连接中。
     */
    ConnectionState[ConnectionState["kConnectionStateConnecting"] = 2] = "kConnectionStateConnecting";
    /**
     * @brief 首次连接成功。
     */
    ConnectionState[ConnectionState["kConnectionStateConnected"] = 3] = "kConnectionStateConnected";
    /**
     * @brief 连接断开后重新连接中。
     */
    ConnectionState[ConnectionState["kConnectionStateReconnecting"] = 4] = "kConnectionStateReconnecting";
    /**
     * @brief 连接断开后重连成功。
     */
    ConnectionState[ConnectionState["kConnectionStateReconnected"] = 5] = "kConnectionStateReconnected";
    /**
     * @brief 网络连接断开超过 10 秒，仍然会继续重连。
     */
    ConnectionState[ConnectionState["kConnectionStateLost"] = 6] = "kConnectionStateLost";
})(ConnectionState = exports.ConnectionState || (exports.ConnectionState = {}));
;
/**
 * @hidden
 * @type keytype
 * @brief 用户离线原因。<br>
 *        房间内的远端用户离开房间时，本端用户会收到 OnUserOffline{@link #OnUserOffline} 回调通知，此枚举类型为回调的用户离线原因。
 */
var UserOfflineReasonType;
(function (UserOfflineReasonType) {
    /**
     * @brief 用户主动离开。
     */
    UserOfflineReasonType[UserOfflineReasonType["USER_OFFLINE_QUIT"] = 0] = "USER_OFFLINE_QUIT";
    /**
     * @brief 用户掉线。
     */
    UserOfflineReasonType[UserOfflineReasonType["USER_OFFLINE_DROPPED"] = 1] = "USER_OFFLINE_DROPPED";
    /**
     * @hidden
     */
    UserOfflineReasonType[UserOfflineReasonType["USER_OFFLINE_BECOME_AUDIENCE"] = 2] = "USER_OFFLINE_BECOME_AUDIENCE";
})(UserOfflineReasonType = exports.UserOfflineReasonType || (exports.UserOfflineReasonType = {}));
;
/**
 * @type keytype
 * @brief 当前媒体设备类型
 */
var MediaDeviceType;
(function (MediaDeviceType) {
    /**
     * @brief 音频渲染设备类型
     */
    MediaDeviceType[MediaDeviceType["kMediaDeviceTypeAudioRenderDevice"] = 0] = "kMediaDeviceTypeAudioRenderDevice";
    /**
     * @brief 音频采集设备类型
     */
    MediaDeviceType[MediaDeviceType["kMediaDeviceTypeAudioCaptureDevice"] = 1] = "kMediaDeviceTypeAudioCaptureDevice";
    /**
     *@hidden
     *@brief 视频渲染设备类型，该类型暂无使用
     */
    MediaDeviceType[MediaDeviceType["kMediaDeviceTypeVideoRenderDevice"] = 2] = "kMediaDeviceTypeVideoRenderDevice";
    /**
     *@brief 视频采集设备类型
     */
    MediaDeviceType[MediaDeviceType["kMediaDeviceTypeVideoCaptureDevice"] = 3] = "kMediaDeviceTypeVideoCaptureDevice";
})(MediaDeviceType = exports.MediaDeviceType || (exports.MediaDeviceType = {}));
;
/**
 * @type keytype
 * @brief 媒体设备事件类型
 */
var MediaDeviceNotification;
(function (MediaDeviceNotification) {
    /**
     *@brief 设备已就绪
     */
    MediaDeviceNotification[MediaDeviceNotification["kMediaDeviceNotificationActive"] = 1] = "kMediaDeviceNotificationActive";
    /**
     *@brief 设备被禁用
     */
    MediaDeviceNotification[MediaDeviceNotification["kMediaDeviceNotificationDisabled"] = 2] = "kMediaDeviceNotificationDisabled";
    /**
     *@brief 没有此设备
     */
    MediaDeviceNotification[MediaDeviceNotification["kMediaDeviceNotificationNotPresent"] = 4] = "kMediaDeviceNotificationNotPresent";
    /**
     *@brief 设备被拔出
     */
    MediaDeviceNotification[MediaDeviceNotification["kMediaDeviceNotificationUnplugged"] = 8] = "kMediaDeviceNotificationUnplugged";
})(MediaDeviceNotification = exports.MediaDeviceNotification || (exports.MediaDeviceNotification = {}));
;
/**
 * @type keytype
 * @brief 媒体设备状态类型
 */
var MediaDeviceState;
(function (MediaDeviceState) {
    /**
     *@brief 设备已开启
     */
    MediaDeviceState[MediaDeviceState["kMediaDeviceStateStarted"] = 1] = "kMediaDeviceStateStarted";
    /**
     *@brief 设备已停止
     */
    MediaDeviceState[MediaDeviceState["kMediaDeviceStateStopped"] = 2] = "kMediaDeviceStateStopped";
    /**
     *@brief 设备运行时错误
     */
    MediaDeviceState[MediaDeviceState["kMediaDeviceStateRuntimeError"] = 3] = "kMediaDeviceStateRuntimeError";
    /**
     *@brief 设备已插入
     */
    MediaDeviceState[MediaDeviceState["kMediaDeviceStateAdded"] = 10] = "kMediaDeviceStateAdded";
    /**
     *@brief 设备被移除
     */
    MediaDeviceState[MediaDeviceState["kMediaDeviceStateRemoved"] = 11] = "kMediaDeviceStateRemoved";
})(MediaDeviceState = exports.MediaDeviceState || (exports.MediaDeviceState = {}));
;
/**
 * @type keytype
 * @brief 屏幕采集对象的类型
 */
var ScreenCaptureSourceType;
(function (ScreenCaptureSourceType) {
    /**
     * @brief 类型未知
     */
    ScreenCaptureSourceType[ScreenCaptureSourceType["kScreenCaptureSourceTypeUnknown"] = 0] = "kScreenCaptureSourceTypeUnknown";
    /**
     * @brief 应用程序的窗口
     */
    ScreenCaptureSourceType[ScreenCaptureSourceType["kScreenCaptureSourceTypeWindow"] = 1] = "kScreenCaptureSourceTypeWindow";
    /**
     * @brief 桌面
     */
    ScreenCaptureSourceType[ScreenCaptureSourceType["kScreenCaptureSourceTypeScreen"] = 2] = "kScreenCaptureSourceTypeScreen";
})(ScreenCaptureSourceType = exports.ScreenCaptureSourceType || (exports.ScreenCaptureSourceType = {}));
;
var RemoteUserPriority;
(function (RemoteUserPriority) {
    /**
       * @brief 用户优先级为低（默认值）
       */
    RemoteUserPriority[RemoteUserPriority["kRemoteUserPriorityLow"] = 0] = "kRemoteUserPriorityLow";
    /**
     * @brief 用户优先级为正常
     */
    RemoteUserPriority[RemoteUserPriority["kRemoteUserPriorityMedium"] = 100] = "kRemoteUserPriorityMedium";
    /**
     * @brief 用户优先级为高
     */
    RemoteUserPriority[RemoteUserPriority["kRemoteUserPriorityHigh"] = 200] = "kRemoteUserPriorityHigh";
})(RemoteUserPriority = exports.RemoteUserPriority || (exports.RemoteUserPriority = {}));
;
/**
 * @brief 转推直播媒体类型
 */
var TranscoderContentControlType;
(function (TranscoderContentControlType) {
    /**
     * @brief 音视频
     */
    TranscoderContentControlType[TranscoderContentControlType["kHasAudioAndVideo"] = 0] = "kHasAudioAndVideo";
    /**
     * @brief 音频
     */
    TranscoderContentControlType[TranscoderContentControlType["kHasAudioOnly"] = 1] = "kHasAudioOnly";
    /**
     * @brief 视频
     */
    TranscoderContentControlType[TranscoderContentControlType["kHasVideoOnly"] = 2] = "kHasVideoOnly";
})(TranscoderContentControlType = exports.TranscoderContentControlType || (exports.TranscoderContentControlType = {}));
;
/**
 * @brief 转推直播视频编码参数
 */
var TranscoderVideoCodecProfile;
(function (TranscoderVideoCodecProfile) {
    /**
     * @brief H264 格式基本规格编码
     */
    TranscoderVideoCodecProfile[TranscoderVideoCodecProfile["kByteH264ProfileBaseline"] = 0] = "kByteH264ProfileBaseline";
    /**
     * @brief H264 格式主流规格编码
     */
    TranscoderVideoCodecProfile[TranscoderVideoCodecProfile["kByteH264ProfileMain"] = 1] = "kByteH264ProfileMain";
    /**
     * @brief H264 格式高规格编码
     */
    TranscoderVideoCodecProfile[TranscoderVideoCodecProfile["kByteH264ProfileHigh"] = 2] = "kByteH264ProfileHigh";
    /**
     * @brief ByteVC1 格式基本规格编码
     */
    TranscoderVideoCodecProfile[TranscoderVideoCodecProfile["kByteVC1ProfileBaseline"] = 3] = "kByteVC1ProfileBaseline";
    /**
     * @brief ByteVC1 格式主流规格编码
     */
    TranscoderVideoCodecProfile[TranscoderVideoCodecProfile["kByteVC1ProfileMain"] = 4] = "kByteVC1ProfileMain";
    /**
     * @brief ByteVC1 格式高规格编码
     */
    TranscoderVideoCodecProfile[TranscoderVideoCodecProfile["kByteVC1ProfileHigh"] = 5] = "kByteVC1ProfileHigh";
})(TranscoderVideoCodecProfile = exports.TranscoderVideoCodecProfile || (exports.TranscoderVideoCodecProfile = {}));
/**
 *@brief 转推直播音频编码 AAC 等级
 */
var TranscoderAudioCodecProfile;
(function (TranscoderAudioCodecProfile) {
    /**
     * @brief AAC-LC
     */
    TranscoderAudioCodecProfile[TranscoderAudioCodecProfile["kByteAACProfileLC"] = 0] = "kByteAACProfileLC";
    /**
     * @brief AAC-MAIN
     */
    TranscoderAudioCodecProfile[TranscoderAudioCodecProfile["kByteAACProfileMain"] = 1] = "kByteAACProfileMain";
    /**
     * @brief HE-AAC v1
     */
    TranscoderAudioCodecProfile[TranscoderAudioCodecProfile["kByteAACProfileHEv1"] = 2] = "kByteAACProfileHEv1";
    /**
     * @brief HE-AAC v2
     */
    TranscoderAudioCodecProfile[TranscoderAudioCodecProfile["kByteAACProfileHEv2"] = 3] = "kByteAACProfileHEv2";
})(TranscoderAudioCodecProfile = exports.TranscoderAudioCodecProfile || (exports.TranscoderAudioCodecProfile = {}));
;
/**
 *@brief 转推直播视频渲染模式
 */
var TranscoderRenderMode;
(function (TranscoderRenderMode) {
    /**
     * @hidden
     * TODO(LIYL): remove
     */
    TranscoderRenderMode[TranscoderRenderMode["kRenderUnknown"] = 0] = "kRenderUnknown";
    /**
     *  @brief 视频尺寸等比缩放，优先保证窗口被填满。当视频尺寸与显示窗口尺寸不一致时，多出的视频将被截掉。
     */
    TranscoderRenderMode[TranscoderRenderMode["kRenderHidden"] = 1] = "kRenderHidden";
    /**
     *  @brief
     * 视频尺寸等比缩放，优先保证视频内容全部显示。当视频尺寸与显示窗口尺寸不一致时，会把窗口未被填满的区域填充成黑色。
     */
    TranscoderRenderMode[TranscoderRenderMode["kRenderFit"] = 2] = "kRenderFit";
    /**
     *  @brief 视频尺寸非等比例缩放，把窗口充满。当视频尺寸与显示窗口尺寸不一致时，视频高或宽方向会被拉伸。
     */
    TranscoderRenderMode[TranscoderRenderMode["kRenderAdaptive"] = 3] = "kRenderAdaptive";
})(TranscoderRenderMode = exports.TranscoderRenderMode || (exports.TranscoderRenderMode = {}));
;
/**
 * @type keytype
 * @brief 媒体流网络质量。
 */
var NetworkQuality;
(function (NetworkQuality) {
    /**
     * @brief 网络质量未知。
     */
    NetworkQuality[NetworkQuality["kNetworkQualityUnknown"] = 0] = "kNetworkQualityUnknown";
    /**
     * @brief 网络质量极好。
     */
    NetworkQuality[NetworkQuality["kNetworkQualityExcellent"] = 1] = "kNetworkQualityExcellent";
    /**
     * @brief 主观感觉和 kNetworkQualityExcellent 差不多，但码率可能略低。
     */
    NetworkQuality[NetworkQuality["kNetworkQualityGood"] = 2] = "kNetworkQualityGood";
    /**
     * @brief 主观感受有瑕疵但不影响沟通。
     */
    NetworkQuality[NetworkQuality["kNetworkQualityPoor"] = 3] = "kNetworkQualityPoor";
    /**
     * @brief 勉强能沟通但不顺畅。
     */
    NetworkQuality[NetworkQuality["kNetworkQualityBad"] = 4] = "kNetworkQualityBad";
    /**
     * @brief 网络质量非常差，基本不能沟通。
     */
    NetworkQuality[NetworkQuality["kNetworkQualityVbad"] = 5] = "kNetworkQualityVbad";
})(NetworkQuality = exports.NetworkQuality || (exports.NetworkQuality = {}));
;
/**
 * @type keytype
 * @brief 发送用户消息或者房间消息的结果
 */
var MessageSendResultCode;
(function (MessageSendResultCode) {
    /**
     * @brief 用户P2P消息发送成功
     */
    MessageSendResultCode[MessageSendResultCode["MESSAGE_CODE_SUCCESS"] = 0] = "MESSAGE_CODE_SUCCESS";
    /**
     * @brief 房间Broadcast消息发送成功
     */
    MessageSendResultCode[MessageSendResultCode["MESSAGE_CODE_ROOM_SUCCESS"] = 200] = "MESSAGE_CODE_ROOM_SUCCESS";
    /**
     * @brief 发送超时，没有发送
     */
    MessageSendResultCode[MessageSendResultCode["MESSAGE_CODE_ERROR_TIMEOUT"] = 1] = "MESSAGE_CODE_ERROR_TIMEOUT";
    /**
     * @brief 通道断开，没有发送
     */
    MessageSendResultCode[MessageSendResultCode["MESSAGE_CODE_ERROR_BROKEN"] = 2] = "MESSAGE_CODE_ERROR_BROKEN";
    /**
     * @brief 找不到接收方
     */
    MessageSendResultCode[MessageSendResultCode["MESSAGE_CODE_ERROR_NOT_RECEIVER"] = 3] = "MESSAGE_CODE_ERROR_NOT_RECEIVER";
    /**
     * @brief 没有加入房间
     */
    MessageSendResultCode[MessageSendResultCode["MESSAGE_CODE_ERROR_NOT_JOIN"] = 100] = "MESSAGE_CODE_ERROR_NOT_JOIN";
    /**
     * @brief 没有可用的数据传输通道连接
     */
    MessageSendResultCode[MessageSendResultCode["MESSAGE_CODE_ERROR_NO_CONNECTION"] = 102] = "MESSAGE_CODE_ERROR_NO_CONNECTION";
    /**
     * @brief 消息超过最大长度，当前为64KB
     */
    MessageSendResultCode[MessageSendResultCode["MESSAGE_CODE_ERROR_EXCEED_MAX_LENGTH"] = 103] = "MESSAGE_CODE_ERROR_EXCEED_MAX_LENGTH";
    /**
     * @brief 用户id为空
     */
    MessageSendResultCode[MessageSendResultCode["MESSAGE_CODE_ERROR_EMPTY_USER"] = 104] = "MESSAGE_CODE_ERROR_EMPTY_USER";
    /**
     * @brief 未知错误
     */
    MessageSendResultCode[MessageSendResultCode["MESSAGE_CODE_ERROR_UNKNOWN"] = 1000] = "MESSAGE_CODE_ERROR_UNKNOWN";
})(MessageSendResultCode = exports.MessageSendResultCode || (exports.MessageSendResultCode = {}));
;
/**
 * @type keytype
 * @brief 音频混音文件播放状态。
 */
var AudioMixingState;
(function (AudioMixingState) {
    /**
     * @brief 混音已加载
     */
    AudioMixingState[AudioMixingState["kAudioMixingStatePreloaded"] = 0] = "kAudioMixingStatePreloaded";
    /**
     * @brief 混音正在播放
     */
    AudioMixingState[AudioMixingState["kAudioMixingStatePlaying"] = 1] = "kAudioMixingStatePlaying";
    /**
     * @brief 混音暂停
     */
    AudioMixingState[AudioMixingState["kAudioMixingStatePaused"] = 2] = "kAudioMixingStatePaused";
    /**
     * @brief 混音停止
     */
    AudioMixingState[AudioMixingState["kAudioMixingStateStopped"] = 3] = "kAudioMixingStateStopped";
    /**
     * @brief 混音播放失败
     */
    AudioMixingState[AudioMixingState["kAudioMixingStateFailed"] = 4] = "kAudioMixingStateFailed";
    /**
     * @brief 混音播放结束
     */
    AudioMixingState[AudioMixingState["kAudioMixingStateFinished"] = 5] = "kAudioMixingStateFinished";
})(AudioMixingState = exports.AudioMixingState || (exports.AudioMixingState = {}));
;
/**
 * @type keytype
 * @brief 音频混音文件播放错误码。
 */
var AudioMixingError;
(function (AudioMixingError) {
    /**
     * @brief 混音错误码，正常
     */
    AudioMixingError[AudioMixingError["kAudioMixingErrorOk"] = 0] = "kAudioMixingErrorOk";
    /**
     * @brief 预加载失败，找不到混音文件或者文件长度超出 20s
     */
    AudioMixingError[AudioMixingError["kAudioMixingErrorPreloadFailed"] = 1] = "kAudioMixingErrorPreloadFailed";
    /**
     * @brief 混音开启失败，找不到混音文件或者混音文件打开失败
     */
    AudioMixingError[AudioMixingError["kAudioMixingErrorStartFailed"] = 2] = "kAudioMixingErrorStartFailed";
    /**
     * @brief 混音 ID 异常
     */
    AudioMixingError[AudioMixingError["kAudioMixingErrorIdNotFound"] = 3] = "kAudioMixingErrorIdNotFound";
    /**
     * @brief 设置混音文件的播放位置出错
     */
    AudioMixingError[AudioMixingError["kAudioMixingErrorSetPositionFailed"] = 4] = "kAudioMixingErrorSetPositionFailed";
    /**
     * @brief 音量参数不合法，仅支持设置的音量值为[0 400]
     */
    AudioMixingError[AudioMixingError["kAudioMixingErrorInValidVolume"] = 5] = "kAudioMixingErrorInValidVolume";
    /**
     * @brief 播放的文件与预加载的文件不一致，请先使用 UnloadAudioMixing{@link #UnloadAudioMixing} 卸载文件
     */
    AudioMixingError[AudioMixingError["kAudioMixingErrorLoadConflict"] = 6] = "kAudioMixingErrorLoadConflict";
    /**
     * @hidden
     * @deprecated
     * @brief 混音错误码，失败，已废弃
     */
    AudioMixingError[AudioMixingError["kAudioMixingErrorCanNotOpen"] = 701] = "kAudioMixingErrorCanNotOpen";
})(AudioMixingError = exports.AudioMixingError || (exports.AudioMixingError = {}));
;
/** {zh}
 * @detail 85534
 * @brief 回调警告码。警告码说明 SDK 内部遇到问题正在尝试恢复。警告码仅起通知作用。
 */
var WarningCode;
(function (WarningCode) {
    /**
       * @hidden
       */
    WarningCode[WarningCode["kWarningCodeGetRoomFailed"] = -2000] = "kWarningCodeGetRoomFailed";
    /**
    * @brief 进房失败。  <br>
    *        当你调用初次加入房间或者由于网络状况不佳断网重连时，由于服务器错误导致进房失败。SDK 会自动重试进房。
    */
    WarningCode[WarningCode["kWarningCodeJoinRoomFailed"] = -2001] = "kWarningCodeJoinRoomFailed";
    /**
    * @brief 发布音视频流失败。  <br>
    *        当你在所在房间中发布音视频流时，由于服务器错误导致发布失败。SDK 会自动重试发布。
    */
    WarningCode[WarningCode["kWarningCodePublishStreamFailed"] = -2002] = "kWarningCodePublishStreamFailed";
    /**
    * @brief 订阅音视频流失败。  <br>
    *        当前房间中找不到订阅的音视频流导致订阅失败。SDK 会自动重试订阅，若仍订阅失败则建议你退出重试。
    */
    WarningCode[WarningCode["kWarningCodeSubscribeStreamFailed404"] = -2003] = "kWarningCodeSubscribeStreamFailed404";
    /**
    * @brief 订阅音视频流失败。  <br>
    *        当你订阅所在房间中的音视频流时，由于服务器错误导致订阅失败。SDK 会自动重试订阅。
    */
    WarningCode[WarningCode["kWarningCodeSubscribeStreamFailed5xx"] = -2004] = "kWarningCodeSubscribeStreamFailed5xx";
    /**
    * @hidden
    * @brief 函数调用顺序错误。
    */
    WarningCode[WarningCode["kWarningCodeInvokeError"] = -2005] = "kWarningCodeInvokeError";
    /**
    * @hidden
    * @brief 调度异常，服务器返回的媒体服务器地址不可用。
    */
    WarningCode[WarningCode["kWarningCodeInvalidExpectMediaServerAddress"] = -2007] = "kWarningCodeInvalidExpectMediaServerAddress";
    /**
     * @brief 当调用 SetUserVisibility{@link 85532#SetUserVisibility} 将自身可见性设置为 false 后，再尝试发布流会触发此警告。
     */
    WarningCode[WarningCode["kWarningCodePublishStreamForbiden"] = -2009] = "kWarningCodePublishStreamForbiden";
    /**
     * @hidden
     * @brief 自动订阅模式未关闭时，尝试开启手动订阅模式会触发此警告。  <br>你需在进房时关闭自动订阅模式，再调用 SubscribeStream{@link 85532#SubscribeStream} 方法手动订阅音视频流。
     */
    WarningCode[WarningCode["kWarningCodeSubscribeStreamForbiden"] = -2010] = "kWarningCodeSubscribeStreamForbiden";
    /**
    * @brief 发送自定义广播消息失败，当前你未在房间中。
    */
    WarningCode[WarningCode["kWarningCodeSendCustomMessage"] = -2011] = "kWarningCodeSendCustomMessage";
    /**
    * @brief 当房间内人数超过 500 人时，停止向房间内已有用户发送 OnUserJoined{@link #IRTCRoomEventHandler#OnUserJoined} 和 OnUserLeave{@link #IRTCRoomEventHandler#OnUserLeave} 回调，并通过广播提示房间内所有用户。
    */
    WarningCode[WarningCode["kWarningCodeUserNotifyStop"] = -2013] = "kWarningCodeUserNotifyStop";
    /**
    * @brief 摄像头权限异常，当前应用没有获取摄像头权限。
    */
    WarningCode[WarningCode["kWarningCodeNoCameraPermission"] = -5001] = "kWarningCodeNoCameraPermission";
    /**
    * @brief 麦克风权限异常，当前应用没有获取麦克风权限。
    */
    WarningCode[WarningCode["kWarningCodeNoMicrophonePermission"] = -5002] = "kWarningCodeNoMicrophonePermission";
    /**
      * @brief 音频采集设备启动失败，当前设备可能被其他应用占用。
      */
    WarningCode[WarningCode["kWarningCodeRecodingDeviceStartFailed"] = -5003] = "kWarningCodeRecodingDeviceStartFailed";
    /**
    * @brief 音频播放设备启动失败警告，可能由于系统资源不足，或参数错误。
    */
    WarningCode[WarningCode["kWarningCodePlayoutDeviceStartFailed"] = -5004] = "kWarningCodePlayoutDeviceStartFailed";
    /**
    * @brief 无可用音频采集设备，请插入可用的音频采集设备。
    */
    WarningCode[WarningCode["kWarningCodeNoRecordingDevice"] = -5005] = "kWarningCodeNoRecordingDevice";
    /**
    * @brief 无可用音频播放设备，请插入可用的音频播放设备。
    */
    WarningCode[WarningCode["kWarningCodeNoPlayoutDevice"] = -5006] = "kWarningCodeNoPlayoutDevice";
    /**
    * @brief 当前音频设备没有采集到有效的声音数据，请检查更换音频采集设备。
    */
    WarningCode[WarningCode["kWarningCodeRecordingSilence"] = -5007] = "kWarningCodeRecordingSilence";
    /**
    * @brief 媒体设备误操作警告。  <br>
    *        使用自定义采集时，不可调用内部采集开关，调用时将触发此警告。
    */
    WarningCode[WarningCode["kWarningCodeMediaDeviceOperationDenied"] = -5008] = "kWarningCodeMediaDeviceOperationDenied";
    /**
     * @hidden
     * @brief 不支持在 publishScreen{@link 85532#PublishScreen} 之后设置屏幕音频采集类型
     *        setScreenAudioSourceType{@link 85532#SetScreenAudioSourceType}，请在 PublishScreen 之前设置
     */
    WarningCode[WarningCode["kWarningCodeSetScreenAudioSourceTypeFailed"] = -5009] = "kWarningCodeSetScreenAudioSourceTypeFailed";
    /**
     * @brief 不支持在 publishScreen{@link 85532#PublishScreen} 之后，
     *        通过 setScreenAudioStreamIndex{@link 85532#SetScreenAudioStreamIndex} 设置屏幕共享时的音频采集方式。
     */
    WarningCode[WarningCode["kWarningCodeSetScreenAudioStreamIndexFailed"] = -5010] = "kWarningCodeSetScreenAudioStreamIndexFailed";
    /**
    * @brief 指定的内部渲染画布句柄无效。  <br> 当你调用 setupLocalVideo{@link 85532#setupLocalVideo} 或 setupRemoteVideo{@link 85532#setupRemoteVideo} 时指定了无效的画布句柄，触发此回调。
    */
    WarningCode[WarningCode["kWarningCodeInvalidCanvasHandle"] = -6001] = "kWarningCodeInvalidCanvasHandle";
})(WarningCode = exports.WarningCode || (exports.WarningCode = {}));
;
;
/**
 * @detail 85534
 * @brief 回调错误码。  <br>SDK 内部遇到不可恢复的错误时，会通过 OnError{@link 85533#OnError} 回调通知用户。
 */
var ErrorCode;
(function (ErrorCode) {
    /**
     * @brief Token 无效。<br>调用 joinRoom{@link 85532#JoinRoom} 方法时使用的 Token 无效或过期失效。需要用户重新获取 Token，并调用 UpdateToken{@link #UpdateToken} 方法更新 Token。
     */
    ErrorCode[ErrorCode["kErrorCodeInvalidToken"] = -1000] = "kErrorCodeInvalidToken";
    /**
     * @brief 加入房间错误。<br>调用 joinRoom{@link 85532#JoinRoom} 方法时发生未知错误导致加入房间失败。需要用户重新加入房间。
     */
    ErrorCode[ErrorCode["kErrorCodeJoinRoom"] = -1001] = "kErrorCodeJoinRoom";
    /**
     * @brief 没有发布音视频流权限。<br>用户在所在房间中发布音视频流失败，失败原因为用户没有发布流的权限。
     */
    ErrorCode[ErrorCode["kErrorCodeNoPublishPermission"] = -1002] = "kErrorCodeNoPublishPermission";
    /**
     * @brief 没有订阅音视频流权限。<br>用户订阅所在房间中的音视频流失败，失败原因为用户没有订阅流的权限。
     */
    ErrorCode[ErrorCode["kErrorCodeNoSubscribePermission"] = -1003] = "kErrorCodeNoSubscribePermission";
    /**
     * @brief 用户重复登录。<br>本地用户所在房间中有相同用户 ID 的用户加入房间，导致本地用户被踢出房间。
     */
    ErrorCode[ErrorCode["kErrorCodeDuplicateLogin"] = -1004] = "kErrorCodeDuplicateLogin";
    /**
     * @brief 用户被踢出房间。<br> 本端用户被主动踢出所在房间时，回调此错误。
     */
    ErrorCode[ErrorCode["kBrerrKickedOut"] = -1006] = "kBrerrKickedOut";
    /**
     * @brief 订阅音视频流失败，订阅音视频流总数超过上限。<br>游戏场景下，为了保证音视频通话的性能和质量，服务器会限制用户订阅的音视频流总数。当用户订阅的音视频流总数已达上限时，继续订阅更多流时会失败，同时用户会收到此错误通知。
     */
    ErrorCode[ErrorCode["kErrorCodeOverStreamSubscribeLimit"] = -1070] = "kErrorCodeOverStreamSubscribeLimit";
    /**
     * @brief 发布流失败，发布流总数超过上限。<br> RTC 系统会限制单个房间内发布的总流数，总流数包括视频流、音频流和屏幕流。如果房间内发布流数已达上限时，本地用户再向房间中发布流时会失败，同时会收到此错误通知。
     */
    ErrorCode[ErrorCode["kErrorCodeOverStreamPublishLimit"] = -1080] = "kErrorCodeOverStreamPublishLimit";
    /**
     * @brief 发布屏幕流失败，发布流总数超过上限。<br>RTC 系统会限制单个房间内发布的总流数，总流数包括视频流、音频流和屏幕流。如果房间内发布流数已达上限时，本地用户再向房间中发布流时会失败，同时会收到此错误通知。
     */
    ErrorCode[ErrorCode["kErrorCodeOverScreenPublishLimit"] = -1081] = "kErrorCodeOverScreenPublishLimit";
    /**
     * @brief 发布视频流总数超过上限。<br>RTC 系统会限制单个房间内发布的视频流数。如果房间内发布视频流数已达上限时，本地用户再向房间中发布视频流时会失败，同时会收到此错误通知。
     */
    ErrorCode[ErrorCode["kErrorCodeOverVideoPublishLimit"] = -1082] = "kErrorCodeOverVideoPublishLimit";
})(ErrorCode = exports.ErrorCode || (exports.ErrorCode = {}));
;
/** {zh}
 * @type keytype
 * @brief SDK 网络连接类型。
 */
var NetworkType;
(function (NetworkType) {
    /**
     * @brief 网络连接类型未知。
     */
    NetworkType[NetworkType["kNetworkTypeUnknown"] = -1] = "kNetworkTypeUnknown";
    /**
     * @brief 网络连接已断开。
     */
    NetworkType[NetworkType["kNetworkTypeDisconnected"] = 0] = "kNetworkTypeDisconnected";
    /**
     * @brief 网络连接类型为 LAN 。
     */
    NetworkType[NetworkType["kNetworkTypeLAN"] = 1] = "kNetworkTypeLAN";
    /**
     * @brief 网络连接类型为 Wi-Fi（包含热点）。
     */
    NetworkType[NetworkType["kNetworkTypeWIFI"] = 2] = "kNetworkTypeWIFI";
    /**
     * @brief 网络连接类型为 2G 移动网络。
     */
    NetworkType[NetworkType["kNetworkTypeMobile2G"] = 3] = "kNetworkTypeMobile2G";
    /**
     * @brief 网络连接类型为 3G 移动网络。
     */
    NetworkType[NetworkType["kNetworkTypeMobile3G"] = 4] = "kNetworkTypeMobile3G";
    /**
     * @brief 网络连接类型为 4G 移动网络。
     */
    NetworkType[NetworkType["kNetworkTypeMobile4G"] = 5] = "kNetworkTypeMobile4G";
    /**
     * @brief 网络连接类型为 5G 移动网络。
     */
    NetworkType[NetworkType["kNetworkTypeMobile5G"] = 6] = "kNetworkTypeMobile5G";
})(NetworkType = exports.NetworkType || (exports.NetworkType = {}));
;
/**
 * @type keytype
 * @brief 是否开启发布性能回退
 */
var PerformanceAlarmMode;
(function (PerformanceAlarmMode) {
    /**
     * @brief 未开启发布性能回退
     */
    PerformanceAlarmMode[PerformanceAlarmMode["kPerformanceAlarmModeNormal"] = 0] = "kPerformanceAlarmModeNormal";
    /**
     * @brief 已开启发布性能回退
     */
    PerformanceAlarmMode[PerformanceAlarmMode["kPerformanceAlarmModeSimulcast"] = 1] = "kPerformanceAlarmModeSimulcast";
})(PerformanceAlarmMode = exports.PerformanceAlarmMode || (exports.PerformanceAlarmMode = {}));
;
/** {zh}
 * @type keytype
 * @brief OnPerformanceAlarms{@link 85533#OnPerformanceAlarms} 告警的原因
 */
var PerformanceAlarmReason;
(function (PerformanceAlarmReason) {
    /**
     * @brief 网络原因差，造成了发送性能回退。仅在开启发送性能回退时，会收到此原因。
     */
    PerformanceAlarmReason[PerformanceAlarmReason["kPerformanceAlarmReasonBandwidthFallbacked"] = 0] = "kPerformanceAlarmReasonBandwidthFallbacked";
    /**
     * @brief 网络性能恢复，发送性能回退恢复。仅在开启发送性能回退时，会收到此原因。
     */
    PerformanceAlarmReason[PerformanceAlarmReason["kPerformanceAlarmReasonBandwidthResumed"] = 1] = "kPerformanceAlarmReasonBandwidthResumed";
    /**
     * @brief 如果未开启发送性能回退，收到此告警时，意味着性能不足；<br>如果开启了发送性能回退，收到此告警时，意味着性能不足，且已发生发送性能回退。
     */
    PerformanceAlarmReason[PerformanceAlarmReason["kPerformanceAlarmReasonPerformanceFallbacked"] = 2] = "kPerformanceAlarmReasonPerformanceFallbacked";
    /**
     * @brief 如果未开启发送性能回退，收到此告警时，意味着性能不足已恢复；<br> 如果开启了发送性能回退，收到此告警时，意味着性能不足已恢复，且已发生发送性能回退恢复。
     */
    PerformanceAlarmReason[PerformanceAlarmReason["kPerformanceAlarmReasonPerformanceResumed"] = 3] = "kPerformanceAlarmReasonPerformanceResumed";
})(PerformanceAlarmReason = exports.PerformanceAlarmReason || (exports.PerformanceAlarmReason = {}));
;
/**
 * @type keytype
 * @brief 媒体设备错误类型
 */
var MediaDeviceError;
(function (MediaDeviceError) {
    /**
     *@brief 媒体设备正常
     */
    MediaDeviceError[MediaDeviceError["kMediaDeviceErrorOK"] = 0] = "kMediaDeviceErrorOK";
    /**
     *@brief 没有权限启动媒体设备
     */
    MediaDeviceError[MediaDeviceError["kMediaDeviceErrorDeviceNoPermission"] = 1] = "kMediaDeviceErrorDeviceNoPermission";
    /**
     *@brief 媒体设备已经在使用中
     */
    MediaDeviceError[MediaDeviceError["kMediaDeviceErrorDeviceBusy"] = 2] = "kMediaDeviceErrorDeviceBusy";
    /**
     *@brief 媒体设备错误
     */
    MediaDeviceError[MediaDeviceError["kMediaDeviceErrorDeviceFailure"] = 3] = "kMediaDeviceErrorDeviceFailure";
    /**
     *@brief 未找到指定的媒体设备
     */
    MediaDeviceError[MediaDeviceError["kMediaDeviceErrorDeviceNotFound"] = 4] = "kMediaDeviceErrorDeviceNotFound";
    /**
     *@brief 媒体设备被移除
     */
    MediaDeviceError[MediaDeviceError["kMediaDeviceErrorDeviceDisconnected"] = 5] = "kMediaDeviceErrorDeviceDisconnected";
})(MediaDeviceError = exports.MediaDeviceError || (exports.MediaDeviceError = {}));
;
/**
 * @type keytype
 * @brief 用户加入房间的类型。
 */
var JoinRoomType;
(function (JoinRoomType) {
    /**
     * @brief 首次加入房间。用户手动调用 joinRoom{@link 85532#JoinRoom}，收到加入成功。
     */
    JoinRoomType[JoinRoomType["kJoinRoomTypeFirst"] = 0] = "kJoinRoomTypeFirst";
    /**
     * @brief 重新加入房间。用户网络较差，失去与服务器的连接，进行重连时收到加入成功。
     */
    JoinRoomType[JoinRoomType["kJoinRoomTypeReconnected"] = 1] = "kJoinRoomTypeReconnected";
})(JoinRoomType = exports.JoinRoomType || (exports.JoinRoomType = {}));
;
;
;
;
;
;
;
/**
 * @type keytype
 * @brief 停止/启动发送音/视频流的状态
 */
var MuteState;
(function (MuteState) {
    /**
     * @brief 启动发送音/视频流的状态
     */
    MuteState[MuteState["kMuteStateOff"] = 0] = "kMuteStateOff";
    /**
     * @brief 停止发送音/视频流的状态
     */
    MuteState[MuteState["kMuteStateOn"] = 1] = "kMuteStateOn";
})(MuteState = exports.MuteState || (exports.MuteState = {}));
;
/**
 * @type keytype
 * @brief 流属性
 */
var StreamIndex;
(function (StreamIndex) {
    /**
     * @brief 主流。<br>
     *        包括：<br>
     *        + 通过默认摄像头/麦克风采集到的视频/音频; <br>
     *        + 通过自定义设备采集到的视频/音频。
     */
    StreamIndex[StreamIndex["kStreamIndexMain"] = 0] = "kStreamIndexMain";
    /**
     * @brief 屏幕流。 <br>
     *        屏幕共享时共享的视频流，或来自声卡的本地播放音频流。
     */
    StreamIndex[StreamIndex["kStreamIndexScreen"] = 1] = "kStreamIndexScreen";
})(StreamIndex = exports.StreamIndex || (exports.StreamIndex = {}));
;
/**
 *@brief 合流事件事件类型
 */
var StreamMixingEvent;
(function (StreamMixingEvent) {
    /**
     * @hidden
     */
    StreamMixingEvent[StreamMixingEvent["kStreamMixingBase"] = 0] = "kStreamMixingBase";
    /**
     * @brief 合流开始
     */
    StreamMixingEvent[StreamMixingEvent["kStreamMixingStart"] = 1] = "kStreamMixingStart";
    /**
     * @brief 合流启动成功
     */
    StreamMixingEvent[StreamMixingEvent["kStreamMixingStartSuccess"] = 2] = "kStreamMixingStartSuccess";
    /**
     * @brief 合流启动失败
     */
    StreamMixingEvent[StreamMixingEvent["kStreamMixingStartFailed"] = 3] = "kStreamMixingStartFailed";
    /**
     * @brief 更新合流
     */
    StreamMixingEvent[StreamMixingEvent["kStreamMixingUpdate"] = 4] = "kStreamMixingUpdate";
    /**
     * @brief 合流结束
     */
    StreamMixingEvent[StreamMixingEvent["kStreamMixingStop"] = 5] = "kStreamMixingStop";
    /**
     * @brief 服务端合流/端云一体合流
     */
    StreamMixingEvent[StreamMixingEvent["kStreamMixingChangeMixType"] = 6] = "kStreamMixingChangeMixType";
    /**
     * @brief 收到客户端合流音频首帧
     */
    StreamMixingEvent[StreamMixingEvent["kStreamMixingFirstAudioFrameByClientMix"] = 7] = "kStreamMixingFirstAudioFrameByClientMix";
    /**
     * @brief 收到客户端合流视频首帧
     */
    StreamMixingEvent[StreamMixingEvent["kStreamMixingFirstVideoFrameByClientMix"] = 8] = "kStreamMixingFirstVideoFrameByClientMix";
    /**
     * @brief 停止服务端合流超时
     */
    StreamMixingEvent[StreamMixingEvent["kStreamMixingStopTimeoutByServer"] = 9] = "kStreamMixingStopTimeoutByServer";
    /**
     * @brief 更新合流超时
     */
    StreamMixingEvent[StreamMixingEvent["kStreamMixingUpdateTimeout"] = 10] = "kStreamMixingUpdateTimeout";
    /**
    * @brief 合流布局参数错误
    */
    StreamMixingEvent[StreamMixingEvent["kStreamMixingRequestParamError"] = 11] = "kStreamMixingRequestParamError";
    /**
     * @hidden
     */
    StreamMixingEvent[StreamMixingEvent["kStreamMixingMax"] = 15] = "kStreamMixingMax";
})(StreamMixingEvent = exports.StreamMixingEvent || (exports.StreamMixingEvent = {}));
;
/**
 *@brief 合流类型
 */
var StreamMixingType;
(function (StreamMixingType) {
    /**
     * @brief 服务端合流
     */
    StreamMixingType[StreamMixingType["kStreamMixingTypeByServer"] = 0] = "kStreamMixingTypeByServer";
    /**
     * @brief 客户端合流
     */
    StreamMixingType[StreamMixingType["kStreamMixingTypeByClient"] = 1] = "kStreamMixingTypeByClient";
})(StreamMixingType = exports.StreamMixingType || (exports.StreamMixingType = {}));
;
;
;
;
/**
 * @type keytype
 * @brief 房间内远端流被移除的原因。
 */
var StreamRemoveReason;
(function (StreamRemoveReason) {
    /**
     * @brief 远端用户停止发布流。
     */
    StreamRemoveReason[StreamRemoveReason["kStreamRemoveReasonUnpublish"] = 0] = "kStreamRemoveReasonUnpublish";
    /**
     * @brief 远端用户发布流失败。
     */
    StreamRemoveReason[StreamRemoveReason["kStreamRemoveReasonPublishFailed"] = 1] = "kStreamRemoveReasonPublishFailed";
    /**
     * @brief 保活失败。
     */
    StreamRemoveReason[StreamRemoveReason["kStreamRemoveReasonKeepLiveFailed"] = 2] = "kStreamRemoveReasonKeepLiveFailed";
    /**
     * @brief 远端用户断网。
     */
    StreamRemoveReason[StreamRemoveReason["kStreamRemoveReasonClientDisconnected"] = 3] = "kStreamRemoveReasonClientDisconnected";
    /**
     * @brief 远端用户重新发布流。
     */
    StreamRemoveReason[StreamRemoveReason["kStreamRemoveReasonRepublish"] = 4] = "kStreamRemoveReasonRepublish";
    /**
     * @brief 其他原因。
     */
    StreamRemoveReason[StreamRemoveReason["kStreamRemoveReasonOther"] = 5] = "kStreamRemoveReasonOther";
})(StreamRemoveReason = exports.StreamRemoveReason || (exports.StreamRemoveReason = {}));
;
/**
 * @type keytype
 * @brief 远端订阅流发生回退或恢复的原因
 */
var FallbackOrRecoverReason;
(function (FallbackOrRecoverReason) {
    /**
     * @brief 其他原因，非带宽和性能原因引起的回退或恢复。默认值
     */
    FallbackOrRecoverReason[FallbackOrRecoverReason["kFallbackOrRecoverReasonUnknown"] = -1] = "kFallbackOrRecoverReasonUnknown";
    /**
     * @brief 由带宽不足导致的订阅端音视频流回退。
     */
    FallbackOrRecoverReason[FallbackOrRecoverReason["kFallbackOrRecoverReasonSubscribeFallbackByBandwidth"] = 0] = "kFallbackOrRecoverReasonSubscribeFallbackByBandwidth";
    /**
     * @brief 由性能不足导致的订阅端音视频流回退。
     */
    FallbackOrRecoverReason[FallbackOrRecoverReason["kFallbackOrRecoverReasonSubscribeFallbackByPerformance"] = 1] = "kFallbackOrRecoverReasonSubscribeFallbackByPerformance";
    /**
     * @brief 由带宽恢复导致的订阅端音视频流恢复。
     */
    FallbackOrRecoverReason[FallbackOrRecoverReason["kFallbackOrRecoverReasonSubscribeRecoverByBandwidth"] = 2] = "kFallbackOrRecoverReasonSubscribeRecoverByBandwidth";
    /**
     * @brief 由性能恢复导致的订阅端音视频流恢复。
     */
    FallbackOrRecoverReason[FallbackOrRecoverReason["kFallbackOrRecoverReasonSubscribeRecoverByPerformance"] = 3] = "kFallbackOrRecoverReasonSubscribeRecoverByPerformance";
    /**
     * @brief 由带宽不足导致的发布端音视频流回退。
     */
    FallbackOrRecoverReason[FallbackOrRecoverReason["kFallbackOrRecoverReasonPublishFallbackByBandwidth"] = 4] = "kFallbackOrRecoverReasonPublishFallbackByBandwidth";
    /**
     * @brief 由性能不足导致的发布端音视频流回退。
     */
    FallbackOrRecoverReason[FallbackOrRecoverReason["kFallbackOrRecoverReasonPublishFallbackByPerformance"] = 5] = "kFallbackOrRecoverReasonPublishFallbackByPerformance";
    /**
     * @brief 由带宽恢复导致的发布端音视频流恢复。
     */
    FallbackOrRecoverReason[FallbackOrRecoverReason["kFallbackOrRecoverReasonPublishRecoverByBandwidth"] = 6] = "kFallbackOrRecoverReasonPublishRecoverByBandwidth";
    /**
     * @brief 由性能恢复导致的发布端音视频流恢复。
     */
    FallbackOrRecoverReason[FallbackOrRecoverReason["kFallbackOrRecoverReasonPublishRecoverByPerformance"] = 7] = "kFallbackOrRecoverReasonPublishRecoverByPerformance";
})(FallbackOrRecoverReason = exports.FallbackOrRecoverReason || (exports.FallbackOrRecoverReason = {}));
;
;
/**
* @type keytype
* @brief 视频帧旋转角度
*/
var VideoRotation;
(function (VideoRotation) {
    /**
     * @brief 顺时针旋转 0 度
    */
    VideoRotation[VideoRotation["kVideoRotation0"] = 0] = "kVideoRotation0";
    /**
     * @brief 顺时针旋转 90 度
    */
    VideoRotation[VideoRotation["kVideoRotation90"] = 90] = "kVideoRotation90";
    /**
     * @brief 顺时针旋转 180 度
    */
    VideoRotation[VideoRotation["kVideoRotation180"] = 180] = "kVideoRotation180";
    /**
     * @brief 顺时针旋转 270 度
    */
    VideoRotation[VideoRotation["kVideoRotation270"] = 270] = "kVideoRotation270";
})(VideoRotation = exports.VideoRotation || (exports.VideoRotation = {}));
;
;
/** {zh}
 * @type keytype
 * @brief 本地音频流状态。<br>
 *        SDK 通过 OnLocalAudioStateChanged{@link 85533#OnLocalAudioStateChanged} 回调本地音频流状态
 */
var LocalAudioStreamState;
(function (LocalAudioStreamState) {
    /**
     * @brief 本地音频默认初始状态。
     *        麦克风停止工作时回调该状态，对应错误码 kLocalAudioStreamErrorOk
     */
    LocalAudioStreamState[LocalAudioStreamState["kLocalAudioStreamStateStopped"] = 0] = "kLocalAudioStreamStateStopped";
    /**
     * @brief 本地音频录制设备启动成功。
     *        采集到音频首帧时回调该状态，对应错误码 kLocalAudioStreamErrorOk
     */
    LocalAudioStreamState[LocalAudioStreamState["kLocalAudioStreamStateRecording"] = 1] = "kLocalAudioStreamStateRecording";
    /**
     * @brief 本地音频首帧编码成功。
     *        音频首帧编码成功时回调该状态，对应错误码 kLocalAudioStreamErrorOk
     */
    LocalAudioStreamState[LocalAudioStreamState["kLocalAudioStreamStateEncoding"] = 2] = "kLocalAudioStreamStateEncoding";
    /**
     * @brief  本地音频启动失败，在以下时机回调该状态：  <br>
     *       + 本地录音设备启动失败，对应错误码 kLocalAudioStreamErrorRecordFailure <br>
     *       + 检测到没有录音设备权限，对应错误码 kLocalAudioStreamErrorDeviceNoPermission  <br>
     *       + 音频编码失败，对应错误码 kLocalAudioStreamErrorEncodeFailure
     */
    LocalAudioStreamState[LocalAudioStreamState["kLocalAudioStreamStateFailed"] = 3] = "kLocalAudioStreamStateFailed";
})(LocalAudioStreamState = exports.LocalAudioStreamState || (exports.LocalAudioStreamState = {}));
;
/**
 * @detail 85534
 * @brief 本地音频流状态改变时的错误码。
 *        SDK 通过 OnLocalAudioStateChanged{@link 85533#OnLocalAudioStateChanged} 回调该错误码。
 */
var LocalAudioStreamError;
(function (LocalAudioStreamError) {
    /**
     * @brief 本地音频状态正常
     */
    LocalAudioStreamError[LocalAudioStreamError["kLocalAudioStreamErrorOk"] = 0] = "kLocalAudioStreamErrorOk";
    /**
     * @brief 本地音频出错原因未知
     */
    LocalAudioStreamError[LocalAudioStreamError["kLocalAudioStreamErrorFailure"] = 1] = "kLocalAudioStreamErrorFailure";
    /**
     * @brief 没有权限启动本地音频录制设备
     */
    LocalAudioStreamError[LocalAudioStreamError["kLocalAudioStreamErrorDeviceNoPermission"] = 2] = "kLocalAudioStreamErrorDeviceNoPermission";
    /**
     * @brief 本地音频录制设备已经在使用中
     * @notes 该错误码暂未使用
     */
    LocalAudioStreamError[LocalAudioStreamError["kLocalAudioStreamErrorDeviceBusy"] = 3] = "kLocalAudioStreamErrorDeviceBusy";
    /**
     * @brief 本地音频录制失败，建议你检查录制设备是否正常工作
     */
    LocalAudioStreamError[LocalAudioStreamError["kLocalAudioStreamErrorRecordFailure"] = 4] = "kLocalAudioStreamErrorRecordFailure";
    /**
     * @brief 本地音频编码失败
     */
    LocalAudioStreamError[LocalAudioStreamError["kLocalAudioStreamErrorEncodeFailure"] = 5] = "kLocalAudioStreamErrorEncodeFailure";
    /**
     *@brief 没有可用的音频录制设备
     */
    LocalAudioStreamError[LocalAudioStreamError["kLocalAudioStreamErrorNoRecordingDevice"] = 6] = "kLocalAudioStreamErrorNoRecordingDevice";
})(LocalAudioStreamError = exports.LocalAudioStreamError || (exports.LocalAudioStreamError = {}));
;
/**
 * @type keytype
 * @brief 远端音频流状态。<br>
 *        用户可以通过 OnRemoteAudioStateChanged{@link 85533#OnRemoteAudioStateChanged} 了解该状态。
 */
var RemoteAudioState;
(function (RemoteAudioState) {
    /**
     * @brief  不接收远端音频流。 <br>
     *         以下情况下会触发回调 OnRemoteAudioStateChanged{@link 85533#OnRemoteAudioStateChanged}：  <br>
     *       + 本地用户停止接收远端音频流，对应原因是： kRemoteAudioStateChangeReasonLocalMuted  <br>
     *       + 远端用户停止发送音频流，对应原因是： kRemoteAudioStateChangeReasonRemoteMuted  <br>
     *       + 远端用户离开房间，对应原因是： kRemoteAudioStateChangeReasonRemoteOffline  <br>
     */
    RemoteAudioState[RemoteAudioState["kRemoteAudioStateStopped"] = 0] = "kRemoteAudioStateStopped";
    /**
     * @brief 开始接收远端音频流首包。<br>
     *        刚收到远端音频流首包会触发回调 OnRemoteAudioStateChanged{@link 85533#OnRemoteAudioStateChanged}，
     *        对应原因是： kRemoteAudioStateChangeReasonLocalUnmuted。
     */
    RemoteAudioState[RemoteAudioState["kRemoteAudioStateStarting"] = 1] = "kRemoteAudioStateStarting";
    /**
     * @brief  远端音频流正在解码，正常播放。 <br>
     *         以下情况下会触发回调 OnRemoteAudioStateChanged{@link 85533#OnRemoteAudioStateChanged}：  <br>
     *       + 成功解码远端音频首帧，对应原因是： kRemoteAudioStateChangeReasonLocalUnmuted
     *       + 网络由阻塞恢复正常，对应原因是： kRemoteAudioStateChangeReasonNetworkRecovery
     *       + 本地用户恢复接收远端音频流，对应原因是： kRemoteAudioStateChangeReasonLocalUnmuted
     *       + 远端用户恢复发送音频流，对应原因是： kRemoteAudioStateChangeReasonRemoteUnmuted
     */
    RemoteAudioState[RemoteAudioState["kRemoteAudioStateDecoding"] = 2] = "kRemoteAudioStateDecoding";
    /**
     * @brief 远端音频流卡顿。<br>
     *        网络阻塞、丢包率大于 40% 时，会触发回调 OnRemoteAudioStateChanged{@link 85533#OnRemoteAudioStateChanged}，
     *        对应原因是： kRemoteAudioStateChangeReasonNetworkCongestion
     */
    RemoteAudioState[RemoteAudioState["kRemoteAudioStateFrozen"] = 3] = "kRemoteAudioStateFrozen";
    /**
     * @hidden
     * @brief 远端音频流播放失败
     * @notes 该错误码暂未使用
     */
    RemoteAudioState[RemoteAudioState["kRemoteAudioStateFailed"] = 4] = "kRemoteAudioStateFailed";
})(RemoteAudioState = exports.RemoteAudioState || (exports.RemoteAudioState = {}));
;
/**
* @type keytype
* @brief 接收远端音频流状态改变的原因。  <br>
*        用户可以通过 OnRemoteAudioStateChanged{@link 85533#OnRemoteAudioStateChanged} 了解该原因。
*/
var RemoteAudioStateChangeReason;
(function (RemoteAudioStateChangeReason) {
    /**
     * @brief 内部原因
     */
    RemoteAudioStateChangeReason[RemoteAudioStateChangeReason["kRemoteAudioStateChangeReasonInternal"] = 0] = "kRemoteAudioStateChangeReasonInternal";
    /**
     * @brief 网络阻塞
     */
    RemoteAudioStateChangeReason[RemoteAudioStateChangeReason["kRemoteAudioStateChangeReasonNetworkCongestion"] = 1] = "kRemoteAudioStateChangeReasonNetworkCongestion";
    /**
     * @brief 网络恢复正常
     */
    RemoteAudioStateChangeReason[RemoteAudioStateChangeReason["kRemoteAudioStateChangeReasonNetworkRecovery"] = 2] = "kRemoteAudioStateChangeReasonNetworkRecovery";
    /**
     * @brief 本地用户停止接收远端音频流
     */
    RemoteAudioStateChangeReason[RemoteAudioStateChangeReason["kRemoteAudioStateChangeReasonLocalMuted"] = 3] = "kRemoteAudioStateChangeReasonLocalMuted";
    /**
     * @brief 本地用户恢复接收远端音频流
     */
    RemoteAudioStateChangeReason[RemoteAudioStateChangeReason["kRemoteAudioStateChangeReasonLocalUnmuted"] = 4] = "kRemoteAudioStateChangeReasonLocalUnmuted";
    /**
     * @brief 远端用户停止发送音频流
     */
    RemoteAudioStateChangeReason[RemoteAudioStateChangeReason["kRemoteAudioStateChangeReasonRemoteMuted"] = 5] = "kRemoteAudioStateChangeReasonRemoteMuted";
    /**
     * @brief 远端用户恢复发送音频流
     */
    RemoteAudioStateChangeReason[RemoteAudioStateChangeReason["kRemoteAudioStateChangeReasonRemoteUnmuted"] = 6] = "kRemoteAudioStateChangeReasonRemoteUnmuted";
    /**
     * @brief 远端用户离开房间
     */
    RemoteAudioStateChangeReason[RemoteAudioStateChangeReason["kRemoteAudioStateChangeReasonRemoteOffline"] = 7] = "kRemoteAudioStateChangeReasonRemoteOffline";
})(RemoteAudioStateChangeReason = exports.RemoteAudioStateChangeReason || (exports.RemoteAudioStateChangeReason = {}));
;
/**
 * @type keytype
 * @brief 本地视频流状态
 */
var LocalVideoStreamState;
(function (LocalVideoStreamState) {
    /**
     * @brief 本地视频采集停止状态
     */
    LocalVideoStreamState[LocalVideoStreamState["kLocalVideoStreamStateStopped"] = 0] = "kLocalVideoStreamStateStopped";
    /**
     * @brief 本地视频采集设备启动成功
     */
    LocalVideoStreamState[LocalVideoStreamState["kLocalVideoStreamStateRecording"] = 1] = "kLocalVideoStreamStateRecording";
    /**
     * @brief 本地视频采集后，首帧编码成功
     */
    LocalVideoStreamState[LocalVideoStreamState["kLocalVideoStreamStateEncoding"] = 2] = "kLocalVideoStreamStateEncoding";
    /**
     * @brief 本地视频采集设备启动失败
     */
    LocalVideoStreamState[LocalVideoStreamState["kLocalVideoStreamStateFailed"] = 3] = "kLocalVideoStreamStateFailed";
})(LocalVideoStreamState = exports.LocalVideoStreamState || (exports.LocalVideoStreamState = {}));
;
/**
* @errorcodes
* @brief 本地视频状态改变时的错误码
*/
/** {en}
* @errorcodes
* @brief Error Codes for the local video state changed
*/
var LocalVideoStreamError;
(function (LocalVideoStreamError) {
    /**
     * @brief 状态正常
     */
    /** {en}
     * @brief Normal
     */
    LocalVideoStreamError[LocalVideoStreamError["kLocalVideoStreamErrorOk"] = 0] = "kLocalVideoStreamErrorOk";
    /**
     * @brief 本地视频流发布失败
     */
    LocalVideoStreamError[LocalVideoStreamError["kLocalVideoStreamErrorFailure"] = 1] = "kLocalVideoStreamErrorFailure";
    /**
     * @brief 没有权限启动本地视频采集设备
     */
    LocalVideoStreamError[LocalVideoStreamError["kLocalVideoStreamErrorDeviceNoPermission"] = 2] = "kLocalVideoStreamErrorDeviceNoPermission";
    /**
     * @brief 本地视频采集设备被占用
     */
    LocalVideoStreamError[LocalVideoStreamError["kLocalVideoStreamErrorDeviceBusy"] = 3] = "kLocalVideoStreamErrorDeviceBusy";
    /**
     * @brief 本地视频采集设备不存在
     */
    LocalVideoStreamError[LocalVideoStreamError["kLocalVideoStreamErrorDeviceNotFound"] = 4] = "kLocalVideoStreamErrorDeviceNotFound";
    /**
     * @brief 本地视频采集失败，建议检查采集设备是否正常工作
     */
    LocalVideoStreamError[LocalVideoStreamError["kLocalVideoStreamErrorCaptureFailure"] = 5] = "kLocalVideoStreamErrorCaptureFailure";
    /**
     * @brief 本地视频编码失败
     */
    LocalVideoStreamError[LocalVideoStreamError["kLocalVideoStreamErrorEncodeFailure"] = 6] = "kLocalVideoStreamErrorEncodeFailure";
    /**
     * @brief 本地视频采集设备被移除
     */
    LocalVideoStreamError[LocalVideoStreamError["kLocalVideoStreamErrorDeviceDisconnected"] = 7] = "kLocalVideoStreamErrorDeviceDisconnected";
})(LocalVideoStreamError = exports.LocalVideoStreamError || (exports.LocalVideoStreamError = {}));
;
/**
 * @type keytype
 * @brief 远端视频流状态。状态改变时，会收到回调： OnRemoteVideoStateChanged{@link 85533#OnRemoteVideoStateChanged}
 */
var RemoteVideoState;
(function (RemoteVideoState) {
    /**
     * @brief 远端视频流默认初始状态，视频尚未开始播放。
     */
    RemoteVideoState[RemoteVideoState["kRemoteVideoStateStopped"] = 0] = "kRemoteVideoStateStopped";
    /**
     * @brief 本地用户已接收远端视频流首包。
     */
    RemoteVideoState[RemoteVideoState["kRemoteVideoStateStarting"] = 1] = "kRemoteVideoStateStarting";
    /**
     * @brief 远端视频流正在解码，正常播放。
     */
    RemoteVideoState[RemoteVideoState["kRemoteVideoStateDecoding"] = 2] = "kRemoteVideoStateDecoding";
    /**
     * @brief 远端视频流卡顿，可能有网络等原因。
     */
    RemoteVideoState[RemoteVideoState["kRemoteVideoStateFrozen"] = 3] = "kRemoteVideoStateFrozen";
    /**
     * @brief 远端视频流播放失败。
     */
    RemoteVideoState[RemoteVideoState["kRemoteVideoStateFailed"] = 4] = "kRemoteVideoStateFailed";
})(RemoteVideoState = exports.RemoteVideoState || (exports.RemoteVideoState = {}));
;
/**
* @type keytype
* @brief 远端视频流状态改变的原因
*/
var RemoteVideoStateChangeReason;
(function (RemoteVideoStateChangeReason) {
    /**
     * @brief 内部原因
     */
    RemoteVideoStateChangeReason[RemoteVideoStateChangeReason["kRemoteVideoStateChangeReasonInternal"] = 0] = "kRemoteVideoStateChangeReasonInternal";
    /**
     * @brief 网络阻塞
     */
    RemoteVideoStateChangeReason[RemoteVideoStateChangeReason["kRemoteVideoStateChangeReasonNetworkCongestion"] = 1] = "kRemoteVideoStateChangeReasonNetworkCongestion";
    /**
     * @brief 网络恢复正常
     */
    RemoteVideoStateChangeReason[RemoteVideoStateChangeReason["kRemoteVideoStateChangeReasonNetworkRecovery"] = 2] = "kRemoteVideoStateChangeReasonNetworkRecovery";
    /**
     * @brief 本地用户停止接收远端视频流或本地用户禁用视频模块
     */
    RemoteVideoStateChangeReason[RemoteVideoStateChangeReason["kRemoteVideoStateChangeReasonLocalMuted"] = 3] = "kRemoteVideoStateChangeReasonLocalMuted";
    /**
     * @brief 本地用户恢复接收远端视频流或本地用户启用视频模块
     */
    RemoteVideoStateChangeReason[RemoteVideoStateChangeReason["kRemoteVideoStateChangeReasonLocalUnmuted"] = 4] = "kRemoteVideoStateChangeReasonLocalUnmuted";
    /**
     * @brief 远端用户停止发送视频流或远端用户禁用视频模块
     */
    RemoteVideoStateChangeReason[RemoteVideoStateChangeReason["kRemoteVideoStateChangeReasonRemoteMuted"] = 5] = "kRemoteVideoStateChangeReasonRemoteMuted";
    /**
     * @brief 远端用户恢复发送视频流或远端用户启用视频模块
     */
    RemoteVideoStateChangeReason[RemoteVideoStateChangeReason["kRemoteVideoStateChangeReasonRemoteUnmuted"] = 6] = "kRemoteVideoStateChangeReasonRemoteUnmuted";
    /**
     * @brief 远端用户离开频道。
     *        状态转换参考 OnStreamRemove{@link 85533#OnStreamRemove}
     */
    RemoteVideoStateChangeReason[RemoteVideoStateChangeReason["kRemoteVideoStateChangeReasonRemoteOffline"] = 7] = "kRemoteVideoStateChangeReasonRemoteOffline";
})(RemoteVideoStateChangeReason = exports.RemoteVideoStateChangeReason || (exports.RemoteVideoStateChangeReason = {}));
;
;
;
;
/**
 * @type keytype
 * @region 房间管理
 * @brief 首帧发送状态
 */
var FirstFrameSendState;
(function (FirstFrameSendState) {
    /**
     * @brief 发送中
     */
    FirstFrameSendState[FirstFrameSendState["kFirstFrameSendStateSending"] = 0] = "kFirstFrameSendStateSending";
    /**
     * @brief 发送成功
     */
    FirstFrameSendState[FirstFrameSendState["kFirstFrameSendStateSent"] = 1] = "kFirstFrameSendStateSent";
    /**
     * @brief 发送失败
     */
    FirstFrameSendState[FirstFrameSendState["kFirstFrameSendStateEnd"] = 2] = "kFirstFrameSendStateEnd";
})(FirstFrameSendState = exports.FirstFrameSendState || (exports.FirstFrameSendState = {}));
;
/**
* @type keytype
* @region 房间管理
* @brief 首帧播放状态
*/
var FirstFramePlayState;
(function (FirstFramePlayState) {
    /**
     * @brief 播放中
     */
    FirstFramePlayState[FirstFramePlayState["kFirstFramePlayStatePlaying"] = 0] = "kFirstFramePlayStatePlaying";
    /**
     * @brief 播放成功
     */
    FirstFramePlayState[FirstFramePlayState["kFirstFramePlayStatePlayed"] = 1] = "kFirstFramePlayStatePlayed";
    /**
     * @brief 播放失败
     */
    FirstFramePlayState[FirstFramePlayState["kFirstFramePlayStateEnd"] = 2] = "kFirstFramePlayStateEnd";
})(FirstFramePlayState = exports.FirstFramePlayState || (exports.FirstFramePlayState = {}));
;
/**
 * @brief 混音播放类型
 */
var AudioMixingType;
(function (AudioMixingType) {
    /**
     * @brief 仅本地播放
     */
    AudioMixingType[AudioMixingType["kAudioMixingTypePlayout"] = 0] = "kAudioMixingTypePlayout";
    /**
     * @brief 仅远端播放
     */
    AudioMixingType[AudioMixingType["kAudioMixingTypePublish"] = 1] = "kAudioMixingTypePublish";
    /**
     * @brief 本地和远端同时播放
     */
    AudioMixingType[AudioMixingType["kAudioMixingTypePlayoutAndPublish"] = 2] = "kAudioMixingTypePlayoutAndPublish";
})(AudioMixingType = exports.AudioMixingType || (exports.AudioMixingType = {}));
;
var PublishFallbackOption;
(function (PublishFallbackOption) {
    /**
     * @brief 关闭发送视频流时的性能回退功能，默认值
     */
    PublishFallbackOption[PublishFallbackOption["kPublishFallbackOptionDisabled"] = 0] = "kPublishFallbackOptionDisabled";
    /**
     * @brief 开启在网络情况不佳或设备性能不足时只发送小流的功能
     */
    PublishFallbackOption[PublishFallbackOption["kPublishFallbackOptionSimulcast"] = 1] = "kPublishFallbackOptionSimulcast";
})(PublishFallbackOption = exports.PublishFallbackOption || (exports.PublishFallbackOption = {}));
;
/**
 * @type keytype
 * @brief 房间模式
 */
var RoomProfileType;
(function (RoomProfileType) {
    /**
     * @brief 普通音视频通话模式。<br>
     *        你应在 1V1 音视频通话时，使用此设置。<br>
     *        此设置下，弱网抗性较好。
     */
    RoomProfileType[RoomProfileType["kRoomProfileTypeCommunication"] = 0] = "kRoomProfileTypeCommunication";
    /**
     * @brief 直播模式。<br>
     *        当你对音视频通话的音质和画质要求较高时，应使用此设置。<br>
     *        此设置下，当用户使用蓝牙耳机收听时，蓝牙耳机使用媒体模式。
     */
    RoomProfileType[RoomProfileType["kRoomProfileTypeLiveBroadcasting"] = 1] = "kRoomProfileTypeLiveBroadcasting";
    /**
     * @brief 游戏语音模式。此模式下延时较低。<br>
     *        低端机在此模式下运行时，进行了额外的性能优化：<br>
     *            + 采集播放采用 16kHz 单通道采样 <br>
     *            + 部分低端机型配置编码帧长 40/60 <br>
     *            + 部分低端机型关闭软件 3A 音频处理 <br>
     *        增强对 iOS 其他屏幕录制进行的兼容性，避免音频录制被 RTC 打断。
     */
    RoomProfileType[RoomProfileType["kRoomProfileTypeGame"] = 2] = "kRoomProfileTypeGame";
    /**
     * @brief 云游戏模式。<br>
     *        如果你需要低延迟、高码率的设置时，你可以使用此设置。<br>
     *        此设置下，弱网抗性较差。
     */
    RoomProfileType[RoomProfileType["kRoomProfileTypeCloudGame"] = 3] = "kRoomProfileTypeCloudGame";
    /**
     * @brief 低时延模式。SDK 会使用低延时设置。  <br>
     *        当你的场景非游戏或云游戏场景，又需要极低延时的体验时，可以使用该模式。 <br>
     *        该模式下，音视频通话延时会明显降低，但同时弱网抗性、通话音质等均会受到一定影响。  <br>
     *        在使用此模式前，强烈建议咨询技术支持同学。
     */
    RoomProfileType[RoomProfileType["kRoomProfileTypeLowLatency"] = 4] = "kRoomProfileTypeLowLatency";
})(RoomProfileType = exports.RoomProfileType || (exports.RoomProfileType = {}));
;
/**
 * @type keytype
 * @brief 订阅回退选项
 */
var SubscribeFallbackOption;
(function (SubscribeFallbackOption) {
    /**
     * @brief 下行网络较弱时，关闭订阅音视频流时的性能回退功能，默认值
     */
    SubscribeFallbackOption[SubscribeFallbackOption["kSubscribeFallbackOptionDisable"] = 0] = "kSubscribeFallbackOptionDisable";
    /**
     * @brief 下行网络较弱时，只接收视频小流
     */
    SubscribeFallbackOption[SubscribeFallbackOption["kSubscribeFallbackOptionVideoStreamLow"] = 1] = "kSubscribeFallbackOptionVideoStreamLow";
    /**
     * @brief 下行网络较弱时，先尝试只接收视频小流；如果网络环境无法显示视频，则再回退到只接收远端订阅的音频流
     */
    SubscribeFallbackOption[SubscribeFallbackOption["kSubscribeFallbackOptionAudioOnly"] = 2] = "kSubscribeFallbackOptionAudioOnly";
})(SubscribeFallbackOption = exports.SubscribeFallbackOption || (exports.SubscribeFallbackOption = {}));
;
;
;
/**
 * @type keytype
 * @brief 是否开启镜像模式
 */
var MirrorMode;
(function (MirrorMode) {
    /**
     * @brief 不开启
     */
    MirrorMode[MirrorMode["kMirrorModeOff"] = 0] = "kMirrorModeOff";
    /**
     * @brief 开启
     */
    MirrorMode[MirrorMode["kMirrorModeOn"] = 1] = "kMirrorModeOn";
})(MirrorMode = exports.MirrorMode || (exports.MirrorMode = {}));
;
/**
 * @type keytype
 * @brief 暂停/恢复接收远端的媒体流类型。
 */
var PauseResumeControlMediaType;
(function (PauseResumeControlMediaType) {
    /**
     * @brief 只控制音频，不影响视频
     */
    PauseResumeControlMediaType[PauseResumeControlMediaType["kRTCPauseResumeControlMediaTypeAudio"] = 0] = "kRTCPauseResumeControlMediaTypeAudio";
    /**
     * @brief 只控制视频，不影响音频
     */
    PauseResumeControlMediaType[PauseResumeControlMediaType["kRTCPauseResumeControlMediaTypeVideo"] = 1] = "kRTCPauseResumeControlMediaTypeVideo";
    /**
     * @brief 同时控制音频和视频
     */
    PauseResumeControlMediaType[PauseResumeControlMediaType["kRTCPauseResumeControlMediaTypeVideoAndAudio"] = 2] = "kRTCPauseResumeControlMediaTypeVideoAndAudio";
})(PauseResumeControlMediaType = exports.PauseResumeControlMediaType || (exports.PauseResumeControlMediaType = {}));
;
;
/**
 * @type keytype
 * @region 屏幕共享
 * @brief 内部采集屏幕视频流时，是否采集鼠标信息
 */
var MouseCursorCaptureState;
(function (MouseCursorCaptureState) {
    /**
     * @brief 采集鼠标信息
     */
    MouseCursorCaptureState[MouseCursorCaptureState["kMouseCursorCaptureStateOn"] = 0] = "kMouseCursorCaptureStateOn";
    /**
     * @brief 不采集鼠标信息
     */
    MouseCursorCaptureState[MouseCursorCaptureState["kMouseCursorCaptureStateOff"] = 1] = "kMouseCursorCaptureStateOff";
})(MouseCursorCaptureState = exports.MouseCursorCaptureState || (exports.MouseCursorCaptureState = {}));
;
;
//# sourceMappingURL=types.js.map