//
//  ByteRtcEngineKitDefines.h
//  ByteRtcEngineKit
//
//  Created by xiewei on 2018/12/3.
//  Copyright © 2018年 xiewei. All rights reserved.
//

#ifndef ByteRtcEngineKitDefines_h
#define ByteRtcEngineKitDefines_h

#import <CoreMedia/CMTime.h>
#import <AppKit/AppKit.h>

/**
 *  @type keytype
 *  @brief 视频显示模式
*/
typedef NS_ENUM(NSUInteger, ByteRtcRenderMode) {
    /**
     *  @brief 视频尺寸等比缩放，优先保证窗口被填满。当视频尺寸与显示窗口尺寸不一致时，多出的视频将被截掉。
    */
    ByteRtc_Render_Hidden = 1,

    /**
     *  @brief 视频尺寸等比缩放，优先保证视频内容全部显示。当视频尺寸与显示窗口尺寸不一致时，会把窗口未被填满的区域填充成黑色。
    */
    ByteRtc_Render_Fit = 2,

    /**
     *  @brief (已经废弃，不再兼容该模式）视频尺寸非等比例缩放，把窗口充满。当视频尺寸与显示窗口尺寸不一致时，视频高或宽方向会被拉伸。(已经废弃，不再兼容该模式）
    */
    ByteRtc_Render_Adaptive = 3,
};

/**
 *  @type keytype
 *  @brief 用户离线原因。
 *         房间内远端用户离开时，本端用户会收到 rtcEngine:didOfflineOfUid:reason:{@link #rtcEngine:didOfflineOfUid:reason:}  回调通知，此枚举类型为回调的用户离线原因。
 */
typedef NS_ENUM(NSUInteger, ByteRtcUserOfflineReason) {
    /**
     *  @brief 用户主动离开。
     */
    ByteRtc_UserOffline_Quit = 0,
    /**
     *  @brief 用户掉线。
     */
    ByteRtc_UserOffline_Dropped = 1,
    /**
     *  @hidden
     */
    ByteRtc_UserOffline_BecomeAudience = 2,
};

/*
 * @type keytype
 * @brief 订阅模式选项。业务方在加入房间前，调用 enableAutoSubscribe:videoMode:{@link #ByteRtcEngineKit#enableAutoSubscribe:videoMode:} 接口设置订阅模式。  <br>
 */
typedef NS_ENUM(NSUInteger, ByteSubscribeMode) {
    /**
     * @brief 自动订阅模式。SDK 会自动为用户订阅房间中的每一路流。  <br>
     */
    kByteAutoSubscribeMode = 0,
    /**
     * @brief 手动订阅模式。SDK 不为自动订阅流。用户需要自己手动调用 subscribeStream:subscribeConfig:{@link #ByteRtcEngineKit#subscribeStream:subscribeConfig:} 接口去订阅远端流。
     */
    kByteManualSubscribeMode = 1
};

/**
 * @type keytype
 * @brief 房间内远端流移除原因。  <br>
 *        房间内远端音视频流移除时，SDK 会通过 rtcEngine:didStreamRemoved:reason:{@link #ByteRtcEngineDelegate#rtcEngine:didStreamRemoved:reason:} 回调通知用户。此枚举类型即为通知的远端流移除的原因。  <br>
 */
typedef NS_ENUM(NSInteger, RtcStreamRemoveReason) {
    /**
     * @brief 远端用户停止发布流。  <br>
     */
    RtcStreamRemoveUnpublish = 0,
    /**
     * @brief 远端用户发布流失败。  <br>
     */
    RtcStreamRemovePublishFailed = 1,
    /**
     * @brief 保活失败。  <br>
     */
    RtcStreamRemoveKeepLiveFailed = 2,
    /**
     * @brief 远端用户断网。  <br>
     */
    RtcStreamRemoveClientDisconnected = 3,
    /**
     * @brief 远端用户重新发布流。  <br>
     */
    RtcStreamRemoveRepublish = 4,
    /**
     * @brief 其他原因。  <br>
     */
    RtcStreamRemoveOtherReason = 5,
};

/**
 *  @type keytype
 *  @brief 房间模式。
 *         房间使用的场景模式。
 */
typedef NS_ENUM(NSInteger, ByteChannelProfile) {
    /**
     *  @brief 通信模式。该房间模式下，房间内所有用户都可以发布和订阅流。适用于 IM 场景。
     */
    ByteChannelProfileCommunication = 0,
    /**
     *  @brief 直播模式。该房间模式下，用户有主播、观众、静默观众三种可选角色，可以通过调用方法 setClientRole:withKey:{@link #setClientRole:withKey:}
     *         设置。主播可以发布和订阅流，观众和静默观众只能订阅流。适用于直播、教育大班课等场景。
     */
    ByteChannelProfileLiveBroadcasting = 1,
    /**
     *  @brief 游戏模式。该房间模式下，用户角色同直播模式。适用于游戏场景。
     */
    ByteChannelProfileGame = 2,
    /**
     *  @brief 云游戏模式。该房间模式下，用户角色同直播模式。适用于云游戏场景。
     */
    ByteChannelProfileCloudGame = 3,
};

/**
 *  @type keytype
 *  @brief 用户角色。
 *         房间模式为直播、游戏、云游戏模式时的用户角色。
 */
typedef NS_ENUM(NSInteger, ByteRtcClientRole) {
    /**
     *  @brief 主播角色，用户既可以发布流到房间中，也可以从房间中订阅流。
     */
    ByteRtc_ClientRole_Broadcaster = 1,
    /**
     *  @hidden
     */
    ByteRtc_ClientRole_PSTNCaller = 3,
    /**
     *  @brief 静默观众模式，除了满足观众角色限制外，房间中的其他用户无法感知到该用户在房间中，即该用户加入退出房间和更新用户属性等行为不会通知给房间中的其他用户。
     */
    ByteRtc_ClientRole_Silent_Audience = 4,
};

/**
 *  @type keytype
 *  @brief 视频流类型
 *      目前C++ sdk 只支持 REMOTE_VIDEO_STREAM_HIGH类型
 */
typedef NS_ENUM(NSInteger, ByteRtcVideoStreamType) {
    /**
     * @brief 高分辨率视频流
     */
    ByteRtc_VideoStream_High = 0,
    /**
     * @brief 低分辨率视频
     */
    ByteRtc_VideoStream_Low = 1,
};

/**
 * @type keytype
 * @brief SDK 网络连接类型
 */
typedef NS_ENUM(NSInteger, ByteRtcNetworkType) {
    /**
     * @brief 网络连接类型未知
     */
    ByteRtcNetworkTypeUnknown = -1,
    /**
     * @brief 网络连接已断开
     */
    ByteRtcNetworkTypeDisconnected = 0,
    /**
     * @brief 网络连接类型为 LAN
     */
    ByteRtcNetworkTypeLAN = 1,
    /**
     * @brief 网络连接类型为 Wi-Fi（包含热点）
     */
    ByteRtcNetworkTypeWIFI = 2,
    /**
     * @brief 网络连接类型为 2G 移动网络
     */
    ByteRtcNetworkTypeMobile2G = 3,
    /**
     * @brief 网络连接类型为 3G 移动网络
     */
    ByteRtcNetworkTypeMobile3G = 4,
    /**
     * @brief 网络连接类型为 4G 移动网络
     */
    ByteRtcNetworkTypeMobile4G = 5,
    /**
     * @brief 网络连接类型为 5G 移动网络
     */
    ByteRtcNetworkTypeMobile5G = 6,
};

/**
 *  @type keytype
 *  @brief 媒体流网络质量
*/
typedef NS_ENUM(NSUInteger, ByteNetworkQuality) {
    /**
     *  @brief 网络质量未知
    */
    ByteRtcNetworkQualityUnknown = 0,
    /**
     *  @brief 网络质量极好
    */
    ByteRtcNetworkQualityExcellent = 1,
    /**
     *  @brief 网络质量好
    */
    ByteRtcNetworkQualityGood = 2,
    /**
     *  @brief 网络质量较差但不影响沟通
    */
    ByteRtcNetworkQualityPoor = 3,
    /**
     *  @brief 网络质量差沟通不顺畅
    */
    ByteRtcNetworkQualityBad = 4,
    /**
     *  @brief 网络质量非常差
    */
    ByteRtcNetworkQualityVBad = 5,
};

/**
 *  @type keytype
 *  @brief 远端视频流状态
*/
typedef NS_ENUM(NSUInteger, ByteVideoRemoteState) {
    /**
     *  @brief 远端视频流停止状态
    */
    ByteVideoRemoteStateStopped = 0,
    /**
     *  @brief 远端视频流运行状态
    */
    ByteVideoRemoteStateRunning = 1,
    /**
     *  @brief 远端视频流冻结状态
    */
    ByteVideoRemoteStateFrozen = 2,
};

/**
 *  @type errorcode
 *  @brief 回调错误码。
 *         SDK 内部遇到不可恢复的错误时，会通过 rtcEngine:didOccurError:{@link #rtcEngine:didOccurError:} 回调通知用户。
 */
typedef NS_ENUM(NSInteger, ByteRtcErrorCode) {
    /**
     *  @brief Token 无效。
     *         调用 joinChannelByKey:channelName:info:uid:{@link #joinChannelByKey:channelName:info:uid:} 方法时使用的 Token 无效或过期失效。需要用户重新获取 Token，并调用
     *         renewChannelKey:{@link #renewChannelKey:} 方法更新 Token。
     */
    BRERR_INVALID_TOKEN               = -1000,
    /**
     *  @brief 加入房间错误。
     *         调用 joinChannelByKey:channelName:info:uid:{@link #joinChannelByKey:channelName:info:uid:} 方法时发生未知错误导致加入房间失败。需要用户重新加入房间。
     */
    BRERR_JOIN_ROOM_ERROR             = -1001,
    /**
     *  @brief 没有发布音视频流权限。
     *         用户在所在房间中发布音视频流失败，失败原因为用户没有发布流的权限。
     */
    BRERR_NO_PUBLISH_PERMISSION       = -1002,
    /**
     *  @brief 没有订阅音视频流权限。
     *         用户订阅所在房间中的音视频流失败，失败原因为用户没有订阅流的权限。
     */
    BRERR_NO_SUBSCRIBE_PERMISSION     = -1003,
    /**
     *  @brief 用户重复登录。
     *         本端用户所在房间中有相同用户 ID 的用户登录，导致本端用户被踢出房间。
     */
    BRERR_DUPLICATE_LOGIN             = -1004,
    /**
     *  @brief 订阅音视频流总数超过上限。
     *         游戏场景下为了保证音视频通话的性能和质量，服务器会限制用户订阅的音视频流的总数。当用户订阅的音视频流总数已达上限时，继续订阅更多流时会失败
     *         同时通知用户订阅音视频流总数超过上限。
     */
    BRERR_OVER_SUBSCRIBE_LIMIT        = -1070,
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
 * @type keytype
 * @brief 订阅流状态
 *      该结构表示在订阅流或者更新流后获取的结果
 */
typedef NS_ENUM(NSInteger, SubscribeState) {
    /**
     * @brief 订阅流成功
     */
    SUBSCRIBE_STATE_SUCCESS,
    /**
     * @brief 还没有加入房间
     */
    SUBSCRIBE_STATE_FAILED_NOT_IN_ROOM,
    /**
     * @brief 没有找到流
     */
    SUBSCRIBE_STATE_FAILED_STREAM_NOT_FOUND,
    /**
     * @hidden
     */
    SUBSCRIBE_STATE_FAILED_AUTO_MODE,
    /**
     * @hidden
     */
    SUBSCRIBE_STATE_FAILED_SIGNAL,
};

/**
 *  @type errorcode
 *  @brief 回调警告码。
 *        警告码说明 SDK 内部遇到问题正在尝试恢复。警告码仅作通知。
 */
typedef NS_ENUM(NSInteger, ByteRtcWarningCode) {
    /**
     *  @hidden
     */
    BRWARN_GET_ROOM_FAILED              = -2000,
    /**
     *  @brief 加入房间失败。
     *        用户调用 joinChannelByKey:channelName:info:uid:{@link #joinChannelByKey:channelName:info:uid:} 加入房间或由于网络状况不佳断网重连时，由于服务器错误导致用户加入房间失败。SDK 会自动重试加入房间。
     */
    BRWARN_JOIN_ROOM_FAILED             = -2001,
    /**
     *  @brief 发布音视频流失败。
     *         用户在所在房间中发布音视频流时，由于服务器错误导致发布失败。SDK 会自动重试发布。
     */
    BRWARN_PUBLISH_STREAM_FAILED        = -2002,
    /**
     *  @brief 订阅音视频流失败。
     *         当前房间中找不到订阅的音视频流导致订阅失败。建议用户退出重试。
     */
    BRWARN_SUBSCRIBE_STREAM_FAILED_404  = -2003,
    /**
     *  @brief 订阅音视频流失败。
     *        用户订阅所在房间中的音视频流时，由于服务器错误导致订阅失败。SDK 会自动重试订阅。
     */
    BRWARN_SUBSCRIBE_STREAM_FAILED_5xx  = -2004,
    /**
     *  @hidden
     *  @brief 用户加入房间后设置分辨率错误，当前代码中未使用
     */
    BRWARN_SET_VIDEO_RESOLUTIONS_AFTER_JOIN = -2005,
    /**
     *  @hidden
     *  @brief 调度异常，server返回的媒体服务器地址不可用。
     */
    BRWARN_INVALID_EXPECT_MS_ADDR = -2007,
    /**
     *  @brief 发送自定义广播消息失败，当前用户未在房间中。
     */
    BRWARN_SEND_CUSTOM_MESSAGE = -2011,
    /**
     *  @brief 没有相机权限。
     *         当前 App 没有相机权限。
     */
    BRWARN_PERMISSION_CAMERA            = -5001,
    /**
     *  @brief 没有麦克风权限。
     *         当前 App 没有麦克风权限。
     */
    BRWARN_PERMISSION_MICROPHONE        = -5002,
    /**
     *  @brief 录音设备启动失败。
     *        启动录音设备失败，当前录音设备可能被其他应用占用。
     */
    BRWARN_ADM_RECORDING_START_FAIL     = -5003,
};

/**
 *  @type errorcode
 *  @brief 直播推流转码功能错误码。
 *         用户调用 enableLiveTranscoding{@link #enableLiveTranscoding} 方法启动直播推流转码功能后，后处理服务器返回的执行结果。
 */
typedef NS_ENUM(NSInteger, ByteRtcTransCodeingErrorCode) {
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
 *  @type keytype
 *  @brief 音频采集编码属性
 *      每一项代表一组特定的采样率、编码码率、通道数、编码场景
 *      暂时不支持该参数的设置
 */
typedef NS_ENUM(NSInteger, ByteRtcAudioProfile) {
    /**
     * @brief 用户默认设置
     */
    ByteRtc_AudioProfile_Default = 0,
    /**
     * @brief 32Khz, 18kbps, mono, speech
     */
    ByteRtc_AudioProfile_SpeechStandard = 1,
    /**
     * @brief 48Khz, 50kbps, mono, music
     */
    ByteRtc_AudioProfile_MusicStandard = 2,
    /**
     * @brief 48Khz, 50kbps, stereo, music
     */
    ByteRtc_AudioProfile_MusicStandardStereo = 3,
    /**
     * @brief 48Khz, 128kbps, mono, music
     */
    ByteRtc_AudioProfile_MusicHighQuality = 4,
    /**
     * @brief 48Khz, 192kbps, stereo, music
     */
    ByteRtc_AudioProfile_MusicHighQualityStereo = 5,
};

/**
 *  @type keytype
 *  视频输出方向模式
 */
typedef NS_ENUM(NSInteger, ByteVideoOutputOrientationMode) {
    /**
     * @brief 自适应布局
     */
    ByteVideoOutputOrientationModeAdaptative = 0,
    /**
     * @brief 横屏布局
     */
    ByteVideoOutputOrientationModeFixedLandscape = 1,
    /**
     * @brief 竖屏布局
     */
    ByteVideoOutputOrientationModeFixedPortrait = 2,
};

/**
 *  @type keytype
 *  @brief 视频镜像模式。
*/
typedef NS_ENUM(NSUInteger, ByteVideoMirrorMode) {
    /**
     *  @brief 开启本地视频镜像
    */
    ByteVideoMirrorModeEnabled = 1,
    /**
     *  @brief 关闭本地视频镜像
    */
    ByteVideoMirrorModeDisabled = 2,
};

/**
 *  @type keytype
 *  @brief 日志级别
 */
typedef enum {
    /**
     * @brief 打印trace级别及以上级别信息
    */
    RTC_LOG_LEVEL_TRACE,
    /**
     * @brief 打印debug级别及以上级别信息
    */
    RTC_LOG_LEVEL_DEBUG,
    /**
     * @brief 打印info级别及以上级别信息
    */
    RTC_LOG_LEVEL_INFO,
    /**
     * @brief 打印warning级别及以上级别信息
    */
    RTC_LOG_LEVEL_WARNING,
    /**
     * @brief 打印error级别信息
    */
    RTC_LOG_LEVEL_ERROR
} ByteRtcLogLevel;

/**
 *  @type keytype
 *  @brief 日志类型
 */
typedef enum {
    /**
     * @brief 平台层日志
    */
    BYTE_RTC_LOG,
    /**
     * @brief Native层日志
    */
    ORIGIN_RTC_LOG,
} RtcLogType;

/**
 *  @type keytype
 *  @brief 音频输出路由
*/
typedef NS_ENUM(NSInteger, ByteAudioOutputRouting) {
    /**
     *  @brief 默认输出路径
    */
    ByteAudioOutputRoutingDefault = -1,
    /**
     *  @brief 从耳机输出
    */
    ByteAudioOutputRoutingHeadset = 0,
    /**
     *  @brief 从听筒输出
    */
    ByteAudioOutputRoutingEarpiece = 1,
    /**
     *  @brief 从扬声器输出
    */
    ByteAudioOutputRoutingSpeakerphone = 3,
    /**
     *  @hidden
    */
    ByteAudioOutputRoutingLoudspeaker = 4,
    /**
     *  @brief 从蓝牙设备输出
    */
    ByteAudioOutputRoutingHeadsetBluetooth = 5
};

/**
 *  @type keytype
 *  @brief 视频帧类型
 */
typedef NS_ENUM(NSInteger, ByteVideoPixelFormat) {
    /**
     * @brief YUV image with i420 layout, also known as yuv420p
     */
    ByteVideoPixelFormatI420 = 1,
    /**
     * @brief BGRA image
     */
    ByteVideoPixelFormatBGRA = 2,
    /**
     * @brief YUV image with NV12 layout
     */
    ByteVideoPixelFormatNV12 = 8,
};

/**
 *  @type keytype
 *  @brief 视频旋转信息，枚举类型，定义了90度为间隔的四种旋转模式。
*/
typedef NS_ENUM(NSInteger, ByteVideoRotation) {
    /**
     *  @brief 视频不做旋转
    */
    ByteVideoRotationNone = 0,
    /**
     *  @brief 视频旋转90度
    */
    ByteVideoRotation90 = 1,
    /**
     *  @brief 视频旋转180度
    */
    ByteVideoRotation180 = 2,
    /**
     *  @brief 视频旋转270度
    */
    ByteVideoRotation270 = 3,
};

/**
 *  @type keytype
 *  @brief 视频缩放模式
*/
typedef NS_ENUM(NSInteger, ByteVideoStreamScaleMode) {
    /**
     *  @brief 自动缩放模式，当前等价于ByteVideoStreamScaleModeFitWithCropping
    */
    ByteVideoStreamScaleModeAuto            = 0,
    /**
     *  @brief 缩放以适配宽高比
    */
    ByteVideoStreamScaleModeStretch         = 1,
    /**
     *  @brief 保持纵横比来缩放图像，裁剪长边
    */
    ByteVideoStreamScaleModeFitWithCropping = 2,
    /**
     *  @brief 保持纵横比来缩放图像，填充短边
    */
    ByteVideoStreamScaleModeFitWithFilling  = 3,
};


/**
 * @type keytype
 * @brief 编码质量偏好
 */
typedef NS_ENUM(NSInteger, ByteVideoEncoderPreference) {
    /**
     *  @brief 关闭
    */
    ByteVideoEncoderPreferDisabled          = 0,
    /**
     *  @brief 保持帧率
    */
    ByteVideoEncoderPreferMaintainFramerate = 1,
    /**
     *  @brief 保持画质
    */
    ByteVideoEncoderPreferMaintainQuality   = 2,
    /**
     *  @brief 平衡模式
    */
    ByteVideoEncoderPreferBalance           = 3,
};

/**
 *  @hidden
 */
typedef NS_ENUM(NSInteger, ByteProviderEvent) {
    /**
     *  @brief 连麦SDK调用api joinChannel
    */
    rtc_joinchannel     = 1,
    /**
     *  @brief Provider SDK收到新的远端流
    */
    rtc_add_stream      = 2,
    /**
     *  @brief Provider SDK发送发布或订阅信令
    */
    rtc_start_pubOrSub  = 3,
    /**
     *  @brief Provider SDK收到answer sdp
    */
    rtc_recv_answer     = 4,
    /**
     *  @brief Provider SDK的发布订阅过程的ice连接建立
    */
    rtc_ice_complete    = 5,
};

/**
 *  @type errorcode
 *  @brief 消息发送结果
 */
typedef NS_ENUM(NSInteger, MessageCode) {
    /**
     *  @brief 成功
    */
    MESSAGE_SUCCESS = 0,
    /**
     *  @brief 超时,未能发送出去
    */
    MESSAGE_ERROR_TIMEOUT = 1,
    /**
     *  @brief 通道中断导致没有发送出去
    */
    MESSAGE_ERROR_BROKEN = 2,
    /**
     *  @brief 没有找到对应的接收者
    */
    MESSAGE_ERROR_NO_RECEIVER = 3,
    /**
     *  @brief 没有加入房间
    */
    MESSAGE_ERROR_NOT_JOIN = 100,
    /**
     *  @brief 没有调用init
    */
    MESSAGE_ERROR_INIT = 101,
    /**
     *  @brief 没有可用的datachannel连接
    */
    MESSAGE_ERROR_NO_CONNECTION = 102,
    /**
     *  @brief 未知错误
    */
    MESSAGE_ERROR_UNKNOWN = 1000,
};

/**
 *  @type keytype
 *  @brief 设置sdk的环境
*/
typedef NS_ENUM(NSInteger, ByteRtcEnv) {
    /**
     *  @brief 线上环境
    */
    kByteRtcEnvProduct = 0,     ///<线上环境
    /**
     *  @brief BOE环境
    */
    kByteRtcEnvBOE = 1,         ///<BOE环境
    /**
     *  @brief 测试环境
    */
    kByteRtcEnvTest = 2,        ///<测试环境
};

/**
 *  @type keytype
 *  @brief 设置引擎工作模式
 */
typedef NS_ENUM(NSUInteger, RtcMode) {
    /**
     *  @brief 通用模式，该模式下只能进行普通会议模式的语音通话，开启自动发布订阅。
     */
    RTC_MODE_GENERAL = 0,
    /**
     *  @brief 游戏语音模式，该模式下关闭自动发布订阅，会按照游戏业务的策略进行主动发布订阅语音。
     */
    RTC_MODE_LOCAL_AUDIO = 1,
};

/**
 *  @type keytype
 *  @brief 语音通话模式
 *         在小队语音里用这个接口设置自己的发送模式
 */
typedef NS_ENUM(NSUInteger, RangeAudioMode) {
    /**
     *  @brief 默认模式
     */
    RANGE_AUDIO_MODE_UNDEFINED = 0,
    /**
     *  @brief 小队模式
     */
    RANGE_AUDIO_MODE_TEAM = 1,
    /**
     *  @brief 世界模式
     */
    RANGE_AUDIO_MODE_WORLD = 2,
};

/**
 *  @type keytype
 *  @brief 本地发布的音视频流回退选项
*/
typedef NS_ENUM(NSUInteger, BytePublishFallbackOption) {
    /**
     *  @brief 上行网络较弱或性能不佳时，不对音视频流作回退处理，默认值
    */
    BytePublishFallbackOptionDisabled = 0,
    /**
     *  @brief 上行网络较弱或性能不佳时，只发送视频小流。
    */
    BytePublishFallbackOptionVideoStreamLow = 1,
};

/**
 *  @type keytype
 *  @brief 设置订阅的音视频流回退选项
*/
typedef NS_ENUM(NSUInteger, ByteSubscribeFallbackOptions) {
    /**
     *  @brief 下行网络较弱时，不对音视频流作回退处理，默认值。
    */
    ByteSubscribeFallbackOptionsDisable = 0,
    /**
     *  @brief 下行网络较弱时，只接收视频小流。
    */
    ByteSubscribeFallbackOptionsVideoStreamLow = 1,
    /**
     *  @brief 下行网络较弱时，先尝试只接收视频小流；如果网络环境无法显示视频，则再回退到只接收远端订阅的音频流。
    */
    ByteSubscribeFallbackOptionsAudioOnly = 2,
};

/**
 * @type keytype
 * @brief 背景模式
 *      开启背景替换功能时生效，详见 replaceBackground:withDivideModel:{@link #replaceBackground:withDivideModel:}。
 */
typedef NS_ENUM(NSUInteger, BackgroundMode) {
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
 *      开启背景替换功能时生效，详见 replaceBackground:withDivideModel:{@link #replaceBackground:withDivideModel:}。
 */
typedef NS_ENUM(NSUInteger, DivideModel) {
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
 * @brief 屏幕分享时共享对象的类型
 */
typedef NS_ENUM(NSUInteger, ByteScreenCaptureSourceType) {
    /**
     *@brief 类型未知
     */
    ByteScreenCaptureSourceTypeUnknown = 0,
    /**
     *@brief 应用程序的窗口
     */
    ByteScreenCaptureSourceTypeWindow = 1,
    /**
     *@brief 桌面
     */
    ByteScreenCaptureSourceTypeScreen = 2
};

#define BYTE_RTC_EXPORT __attribute__((visibility("default")))
/**
 *  @type keytype
 *  @brief 视频渲染图层结构。app通过该结构将要渲染的窗口和视频流进行绑定
 */
BYTE_RTC_EXPORT @interface ByteRtcVideoCanvas : NSObject
/**
 *  @brief 渲染窗口句柄
 */
@property (strong, nonatomic) NSView* _Nullable view;
/**
 *  @brief 设置渲染模式，暂时设置无效
 */
@property (assign, nonatomic) ByteRtcRenderMode renderMode;
/**
 *  @brief 房间的RoomID
 */
@property (strong, nonatomic) NSString* _Nullable roomId;
/**
 *  @brief 设置渲染流的用户标识
 */
@property (strong, nonatomic) NSString* _Nullable uid;
@end

/**
 *  @type keytype
 *  @brief 视频帧附加的数据,视频解码后获得的附加数据
 */
BYTE_RTC_EXPORT @interface ByteRtcFrameExtendedData : NSObject
/**
 *  @brief 附加数据
 */
@property (strong, nonatomic) NSData * _Nullable extendedData;
/**
 *  @brief 附加数据长度
 */
@property (assign, nonatomic) NSInteger extendedDataLen;
@end

NS_ASSUME_NONNULL_BEGIN
/**
 *  @type keytype
 *  @brief 视频流描述
*/
BYTE_RTC_EXPORT @interface VideoStreamDescription: NSObject
/**
 *  @brief 视频分辨率
*/
@property (nonatomic, assign) CGSize videoSize;
/**
 *  @brief 视频预设帧率
*/
@property (nonatomic, assign) NSInteger frameRate;
/**
 *  @brief 视频预设最大码率(Kbps)
*/
@property (nonatomic, assign) NSInteger maxKbps;
/**
 *  @brief 视频伸展模式，详见类型ByteVideoStreamScaleMode{@link #ByteVideoStreamScaleMode}
*/
@property (nonatomic, assign) ByteVideoStreamScaleMode mode;
/**
 *  @brief 视频编码质量偏好，详见类型ByteVideoEncoderPreference{@link #ByteVideoEncoderPreference}
*/
@property (nonatomic, assign) ByteVideoEncoderPreference encoderPreference;
@end

/**
 *  @type keytype
 *  @brief 音视频流属性
 *         发布到房间中的音视频流的流属性。用户加入房间成功后，房间中所有已发布和未来发布的音视频流和流的相关属性，都会通过
 *         rtcEngine:didStreamAdded:{@link #rtcEngine:didStreamAdded:} 回调通知用户。
 */
BYTE_RTC_EXPORT @protocol ByteStream <NSObject>
/**
 *  @brief 发布此流的用户的 ID。
 */
@property (nonatomic, copy, readonly) NSString * userId;
/**
 *  @brief 流是否为共享屏幕流。
 */
@property (nonatomic, assign, readonly) BOOL isScreen;
/**
 *  @brief 流是否包括视频。
 */
@property (nonatomic, assign, readonly) BOOL hasVideo;
/**
 *  @brief 流是否包括音频。
 */
@property (nonatomic, assign, readonly) BOOL hasAudio;
/**
 *  @brief 视频流的分辨率信息，详见 VideoStreamDescription{@link #VideoStreamDescription} 类。
 *         用户可以通过调用 setVideoProfiles{@link #setVideoProfiles:} 方法在一路流中发布多个不同的视频分辨率。此参数即为流中
 *         所有分辨率的相关信息。
 */
@property (nonatomic, copy, readonly) NSArray<VideoStreamDescription *> * videoStreamDescriptions;
@end

/**
 *  @hidden
 *  @type keytype
 *  @brief 订阅流配置参数。
 *         用户调用 subscribeStream:info:{@link #subscribeStream:info:} 方法手动订阅音视频流或更新订阅参数时，传入订阅流配置参数。
 */
BYTE_RTC_EXPORT @interface SubscribeConfig: NSObject
/**
 *  @brief 订阅的流是否是屏幕共享流。
 */
@property (nonatomic, assign) BOOL isScreen;
/**
 *  @brief 是否订阅视频。
 */
@property (nonatomic, assign) BOOL subscribeVideo;
/**
 *  @brief 是否订阅音频。
 */
@property (nonatomic, assign) BOOL subscribeAudio;
/**
 *  @brief 订阅的视频流分辨率下标。
 *         视频流中含多个分辨率的情况下，标识订阅第几个的视频分辨率。如果视频流中仅含一个分辨率，则为0。
 */
@property (nonatomic, assign) NSInteger videoIndex;
@end
NS_ASSUME_NONNULL_END

/**
 *  @type keytype
 *  @brief 音频帧
*/
BYTE_RTC_EXPORT @interface ByteAudioFrame : NSObject
/**
 *  @brief 音频帧数据
*/
@property (strong, nonatomic) NSData * _Nonnull samples;
/**
 *  @brief 此音频帧描述的样点数
*/
@property (assign, nonatomic) int numOfSamples;
/**
 *  @brief 样点平均大小（Bytes）
*/
@property (assign, nonatomic) int bytesPerSample;
/**
 *  @brief 音频通道数
*/
@property (assign, nonatomic) int channels;
/**
 *  @brief 音频采样率
*/
@property (assign, nonatomic) int samplesPerSec;
@end

/**
 *  @type keytype
 *  @brief 视频帧类型
 */
BYTE_RTC_EXPORT @interface ByteVideoFrame : NSObject
/**
 *  @brief 视频帧类型，1: I420、2: BGRA、3: NV21、4: RGBA、5: IMC2、6: BGRA (same as 2)、7: ARGB、8: NV12、
 *         10: android texture (GL_TEXTURE_2D)、11: android texture (OES, typically from camera)、12: ios texture (CVPixelBufferRef)
 *  @notes  only support NV12 and "ios texture"
 */
@property (assign, nonatomic) NSInteger format;
/**
 *  @hidden
 */
@property (assign, nonatomic) int stride DEPRECATED_MSG_ATTRIBUTE("use strideInPixels instead");
/**
 *  @brief time for this frame.
 */
@property (assign, nonatomic) CMTime time;
/**
 *  @brief how many pixels between 2 consecutive rows. Note: in pixel, not byte.
 */
@property (assign, nonatomic) int strideInPixels;
/**
 *  @brief how many rows of pixels, in case of ios texture, it is not used
 */
@property (assign, nonatomic) int height;
/**
 *  @brief texture Buffer
 */
@property (assign, nonatomic) CVPixelBufferRef _Nullable textureBuf;
/**
 *  @brief raw data buffer. in case of ios texture, it is not used
 */
@property (strong, nonatomic) NSData * _Nullable dataBuf;
/**
 *  @brief how many pixels to crop on the left boundary
 */
@property (assign, nonatomic) int cropLeft;
/**
 *  @brief how many pixels to crop on the top boundary
 */
@property (assign, nonatomic) int cropTop;
/**
 *  @brief how many pixels to crop on the right boundary
 */
@property (assign, nonatomic) int cropRight;
/**
 *  @brief how many pixels to crop on the bottom boundary
 */
@property (assign, nonatomic) int cropBottom;
/**
 *  @brief 0, 90, 180, 270. See document for rotation calculation
 */
@property (assign, nonatomic) ByteVideoRotation rotation;
/**
 *  @brief 视频帧附加的数据,视频解码后获得的附加数据
 */
@property (assign, nonatomic) ByteRtcFrameExtendedData * _Nullable extendedData;
/* Note
 * 1. strideInPixels
 *    Stride is in unit of pixel, not byte
 * 2. About frame width and height
 *    No field defined for width. However, it can be deduced by:
 *       croppedWidth = (strideInPixels - cropLeft - cropRight)
 *    And
 *       croppedHeight = (height - cropTop - cropBottom)
 * 3. About crop
 *    _________________________________________________________________.....
 *    |                        ^                                      |  ^
 *    |                        |                                      |  |
 *    |                     cropTop                                   |  |
 *    |                        |                                      |  |
 *    |                        v                                      |  |
 *    |                ________________________________               |  |
 *    |                |                              |               |  |
 *    |                |                              |               |  |
 *    |<-- cropLeft -->|          valid region        |<- cropRight ->|
 *    |                |                              |               | height
 *    |                |                              |               |
 *    |                |_____________________________ |               |  |
 *    |                        ^                                      |  |
 *    |                        |                                      |  |
 *    |                     cropBottom                                |  |
 *    |                        |                                      |  |
 *    |                        v                                      |  v
 *    _________________________________________________________________......
 *    |                                                               |
 *    |<---------------- strideInPixels ----------------------------->|
 *
 *    If your buffer contains garbage data, you can crop them. E.g. frame size is
 *    360 x 640, often the buffer stride is 368, i.e. there extra 8 pixels on the
 *    right are for padding, and should be removed. In this case, you can set:
 *    strideInPixels = 368;
 *    height = 640;
 *    cropRight = 8;
 *    // cropLeft, cropTop, cropBottom are default to 0
 */
@end

/**
 *  @hidden
 *  @type keytype
 *  @brief RTC布局信息
 */
BYTE_RTC_EXPORT @interface ByteRtcVideoCompositingRegion : NSObject
/**
 *  @brief 用户ID
 */
@property (copy, nonatomic) NSString * _Nonnull uid;
/**
 *  @brief 用户视频布局相对画布左侧的偏移量， 相对值。范围[0.0 - 1.0]
 */
@property (assign, nonatomic) CGFloat x;
/**
 *  @brief 用户视频布局相对画布顶端的偏移量， 相对值。范围[0.0 - 1.0]
 */
@property (assign, nonatomic) CGFloat y;
/**
 *  @brief 用户视频宽度相对用户原始视频宽度的比例，相对值。范围[0.0 - 1.0]
 */
@property (assign, nonatomic) CGFloat width;
/**
 *  @brief 用户视频高度相对用户原始视频高度的比例，相对值。范围[0.0 - 1.0]
 */
@property (assign, nonatomic) CGFloat height;
/**
 *  @brief 用户视频布局在画布中的层级，0为底层，值越大越上层。范围[0 - 100]
 */
@property (assign, nonatomic) NSInteger zOrder;
/**
 *  @brief 透明度，范围[0 - 255]
 */
@property (assign, nonatomic) CGFloat alpha;
/**
 *  @brief 推流内容控制。默认为0。
 *      0: 输出的混流包含音视频
 *      1: 只包含音频
 *      2: 表示只包含视频
 */
@property (assign, nonatomic) NSInteger contentControl;
/**
 *  @brief 视频显示模式
 */
@property (assign, nonatomic) ByteRtcRenderMode renderMode;
@end

/**
 *  @hidden
 *  @type keytype
 *  @brief 用户布局信息
 */
BYTE_RTC_EXPORT @interface ByteRtcVideoCompositingLayout : NSObject
/**
 *  @brief 背景颜色
 */
@property (copy, nonatomic) NSString *_Nonnull backgroundColor;
/**
 *  @brief 用户布局信息列表
 */
@property (copy, nonatomic) NSArray<ByteRtcVideoCompositingRegion *> * _Nonnull regions;
/**
 *  @brief 透传的app数据
 */
@property (copy, nonatomic) NSString *_Nonnull appData;
@end

/**
 *  @hidden
 *  @type keytype
 *  @brief 视频参数
 */
BYTE_RTC_EXPORT @interface ByteRtcTranscodingVideoConfig : NSObject
/**
 *  @brief 视频编码格式
 */
@property (copy, nonatomic) NSString * _Nonnull codec;
/**
 *  @brief 合流视频宽度
 */
@property (assign, nonatomic) NSInteger width;
/**
 *  @brief 合流视频高度
 */
@property (assign, nonatomic) NSInteger height;
/**
 *  @brief 合流视频帧率信息
 */
@property (assign, nonatomic) NSInteger fps;
/**
 *  @brief 视频I帧间隔
 */
@property (assign, nonatomic) NSInteger gop;
/**
 *  @brief 合流视频码率(kbps)
 */
@property (assign, nonatomic) NSInteger bitRate;
/**
 *  @brief 是否使用低延时特性
 */
@property (assign, nonatomic) BOOL lowLatency;
@end

/**
 *  @type keytype
 *  @brief AAC编码类型
 */
typedef NS_ENUM(NSInteger, ByteAACProfile) {
    /**
    *  @brief LC（默认）
    */
    ByteAACProfileLC   = 0,
    /**
    *  @brief MAIN
    */
    ByteAACProfileMain = 1,
    /**
    *  @brief HEv1
    */
    ByteAACProfileHEv1 = 2,
    /**
    *  @brief HEv2
    */
    ByteAACProfileHEv2 = 3,
};

/**
 *  @type keytype
 *  @brief 编码类型
 */
typedef NS_ENUM(NSInteger, ByteVideoCodecType) {
    /**
     * @brief 视频编码类型：未知类型
     */
    kByteVideoCodecUnknown = 0,
    /**
     * @brief 视频编码类型：标准 H264
     */
    kByteVideoCodecH264 = 1,
    /**
     * @brief 视频编码类型：标准 ByteVC1
     */
    kByteVideoCodecByteVC1 = 2,
};

/**
 *  @hidden
 *  @type keytype
 *  @brief 音频参数
 */
BYTE_RTC_EXPORT @interface ByteRtcTranscodingAudioConfig : NSObject
/**
 *  @brief 音频编码格式
 */
@property (copy, nonatomic) NSString * _Nonnull codec;
/**
 *  @brief 音频采样率；  16k, 32k, 44.1k, 48k
 */
@property (assign, nonatomic) NSInteger sampleRate;
/**
 *  @brief 声道数
 */
@property (assign, nonatomic) NSInteger channels;
/**
 *  @brief 音频码率(kbps); 16kbsp, 32kbps, 64kbps
 */
@property (assign, nonatomic) NSInteger bitRate;
/**
 *  @brief AAC 等级
 */
@property (assign, nonatomic) ByteAACProfile profile;
/**
 *  @hidden
 */
+ (NSString* _Nonnull) toStringWithProfile:(ByteAACProfile) aacProfile;
@end

/**
 *  @hidden
 *  @type keytype
 *  @brief 合流转推参数
 */
BYTE_RTC_EXPORT @interface ByteRtcLiveTranscoding : NSObject
/**
 *  @brief 用户布局信息
 */
@property (strong, nonatomic) ByteRtcVideoCompositingLayout * _Nonnull layout;
/**
 *  @brief 视频参数
 */
@property (strong, nonatomic) ByteRtcTranscodingVideoConfig * _Nonnull video;
/**
 *  @brief 音频参数
 */
@property (strong, nonatomic) ByteRtcTranscodingAudioConfig * _Nonnull audio;
/**
 *  @brief 动态扩展自定义参数
 */
@property (strong, nonatomic) NSMutableDictionary *  _Nullable advancedConfig;
/**
 *  @brief 合流转推地址
 */
@property (copy, nonatomic) NSString * _Nullable url;
/**
 *  @brief 获取默认合流参数
 */
+ (instancetype _Nonnull)defaultTranscoding;
@end

/**
 * @type keytype
 * @brief 统计信息
 */
BYTE_RTC_EXPORT @interface ByteRtcStats : NSObject
/**
 * @brief 用户在房间中的总时长(s)
 */
@property (assign, nonatomic) NSInteger duration;
/**
 * @brief 用户在通话过程中发送媒体数据总量(bytes)
 */
@property (assign, nonatomic) NSInteger txBytes;
/**
 * @brief 用户在通话过程中接收媒体数据总量(bytes)
 */
@property (assign, nonatomic) NSInteger rxBytes;
/**
 * @brief 当前总发送音频码率(kbps)
 */
@property (assign, nonatomic) NSInteger txAudioKBitrate;
/**
 * @brief 当前总接收音频码率(kbps)
 */
@property (assign, nonatomic) NSInteger rxAudioKBitrate;
/**
 * @brief 当前总发送视频码率(kbps)
 */
@property (assign, nonatomic) NSInteger txVideoKBitrate;
/**
 * @brief 当前总接收视频码率(kbps)
 */
@property (assign, nonatomic) NSInteger rxVideoKBitrate;
/**
 * @brief 往返时延，单位为毫秒
 */
@property (assign, nonatomic) NSInteger lastmileDelay;
/**
 * @brief 当前房间内用户总数
 */
@property (assign, nonatomic) NSInteger userCount;
/**
 * @brief 当前 App 的 CPU 使用率
 */
@property (assign, nonatomic) double cpuAppUsage;
/**
 * @brief 当前设备的总 CPU 使用率
 */
@property (assign, nonatomic) double cpuTotalUsage;
@end

/**
 * @type keytype 
 * @brief App使用的cpu和memory信息  <br>
 *        SDK 周期性（2s）的通过rtcEngine:reportSysStats:{@link #ByteRtcEngineDelegate#rtcEngine:reportSysStats:}回调事件通知用户当前App的cpu与memory使用信息。回调的统计信息即为此数据类型。 <br>
 */
BYTE_RTC_EXPORT @interface ByteRtcSysStats : NSObject
/**
 * @brief 当前App的CPU 使用率
 */
@property (assign, nonatomic) double cpu_app_usage;
/**
 * @brief 当前设备的总CPU使用率
 */
@property (assign, nonatomic) double cpu_total_usage;
/**
 * @brief 当前App的CPU使用率
 */
@property (assign, nonatomic) double memory_usage;
@end

/**
 * @type keytype
 * @brief 本地视频流统计信息。  <br>
 *        本地用户发布视频流成功后，SDK 会周期性（2s）的通过 rtcEngine:localVideoStats:{@link #ByteRtcEngineDelegate#rtcEngine:localVideoStats:} 回调事件通知用户发布的视频流在此次统计周期内的状况。此数据结构即为回调给用户的参数类型。  <br>
 */
BYTE_RTC_EXPORT @interface ByteRtcLocalVideoStats : NSObject
/**
 * @brief 发送的码率。此次统计周期内的视频发送码率，单位为 kbps 。  <br>
 */
@property (assign, nonatomic) float sentKBitrate;
/**
 * @brief 输入帧率。此次统计周期内的本地视频输入帧率 。  <br>
 */
@property (assign, nonatomic) NSInteger inputFrameRate;
/**
 * @brief 发送帧率。此次统计周期内的本地视频发送帧率 。  <br>
 */
@property (assign, nonatomic) NSInteger sentFrameRate;
/**
 * @brief 本地视频目标编码帧率。  <br>
 */
@property (assign, nonatomic) NSInteger encoderOutputFrameRate;
/**
 * @brief 本地视频目标渲染输出帧率。  <br>
 */
@property (assign, nonatomic) NSInteger rendererOutputFrameRate;
/**
 * @brief 本地视频目标发送码率。单位为 kbps 。  <br>
 */
@property (assign, nonatomic) NSInteger sentTargetKBitrate;
/**
 * @brief 本地视频目标发送帧率。  <br>
 */
@property (assign, nonatomic) NSInteger sentTargetFrameRate;
/**
 * @brief 统计间隔。此次统计周期的间隔，单位为 ms 。  <br>
 */
@property (assign, nonatomic) NSInteger statsInterval;
/**
 * @brief 音频丢包率。统计周期内的视频上行丢包率，取值范围为 [0, 1] 。  <br>
 */
@property (assign, nonatomic) float videoLossRate;
/**
 * @brief 往返时延。单位为 ms 。  <br>
 */
@property (assign, nonatomic) NSInteger rtt;
/**
 * @brief 编码率。  <br>
 */
@property(assign, nonatomic) NSInteger encodedBitrate;
/**
 * @brief 编码帧宽度。  <br>
 */
@property(assign, nonatomic) NSInteger encodedFrameWidth;
/**
 * @brief 编码帧高度。  <br>
 */
@property(assign, nonatomic) NSInteger encodedFrameHeight;
/**
 * @brief 编码帧数。此次统计周期内编码的帧数。  <br>
 */
@property(assign, nonatomic) NSInteger encodedFrameCount;
/**
 * @brief 编码类型。详见 ByteVideoCodecType{@link #ByteVideoCodecType} 类型。  <br>
 */
@property(nonatomic) ByteVideoCodecType codecType;
@end

/**
 *  @type keytype
 *  @brief 远端视频流统计信息。  <br>
 *         本地用户订阅远端视频流成功后，SDK 会周期性（2s）的通过 rtcEngine:remoteVideoStats:{@link #ByteRtcEngineDelegate#rtcEngine:remoteVideoStats:} 回调事件通知用户订阅的视频流在此次统计周期内的状况。此数据结构即为回调给用户的参数类型。  <br>
*/
BYTE_RTC_EXPORT @interface ByteRtcRemoteVideoStats : NSObject
/**
 * @brief 用户ID 。远端视频流发布用户的用户ID 。  <br>
 */
@property (copy, nonatomic) NSString * _Nonnull uid;
/**
 * @brief 远端视频宽度。  <br>
 */
@property (assign, nonatomic) NSInteger width;
/**
 * @brief 远端视频高度。  <br>
 */
@property (assign, nonatomic) NSInteger height;
/**
 * @brief 远端视频丢包率。统计周期内的视频下行丢包率，取值范围为 [0, 1] 。  <br>
 */
@property (assign, nonatomic) float videoLossRate;
/**
 * @brief 接收码率。统计周期内的视频接收码率，单位为 kbps 。  <br>
 */
@property (assign, nonatomic) float receivedKBitrate;
/**
 * @brief 远端视频接收帧率。  <br>
 */
@property (assign, nonatomic) NSInteger receivedFrameRate;
/**
 * @brief 远端视频解码输出帧率。  <br>
 */
@property (assign, nonatomic) NSInteger decoderOutputFrameRate;
/**
 * @brief 远端视频渲染输出帧率。  <br>
 */
@property (assign, nonatomic) NSInteger renderOutputFrameRate;
/**
 * @brief 远端视频卡顿次数。  <br>
 */
@property (assign, nonatomic) NSInteger stallCount;
/**
 * @brief 远端视频卡顿时长，单位为 ms 。  <br>
 */
@property (assign, nonatomic) NSInteger stallDuration;
/**
 * @brief 用户体验级别的端到端延时。从发送端采集完成编码开始到接收端解码完成渲染开始的延时，单位为 ms 。  <br>
 */
@property (assign, nonatomic) NSInteger e2eDelay;
/**
 * @brief 远端视频流是否是屏幕共享流。  <br>
 */
@property (assign, nonatomic) BOOL isScreen;
/**
 * @brief 统计间隔。此次统计周期的间隔，单位为 ms 。  <br>
 */
@property (assign, nonatomic) NSInteger statsInterval;
/**
 * @brief 往返时延。单位为 ms 。  <br>
 */
@property (assign, nonatomic) NSInteger rtt;
/**
 * @brief 远端用户在加入房间后发生视频卡顿的累计时长占音频总有效时长的百分比。  <br>
 */
@property(assign, nonatomic) NSInteger frozenRate;
/**
 * @brief SDK 订阅的远端视频流的分辨率下标。  <br>
 */
@property (assign, nonatomic) NSInteger videoIndex;
@end

/**
 * @type keytype
 * @brief 本地音频流统计信息。  <br>
 *        本地用户发布音频流成功后，SDK 会周期性（2s）的通过 rtcEngine:localAudioStats:{@link #ByteRtcEngineDelegate#rtcEngine:localAudioStats:} 回调事件通知用户发布的音频流在此次统计周期内的状况。此数据结构即为回调给用户的参数类型。  <br>
 */
BYTE_RTC_EXPORT @interface ByteRtcLocalAudioStats : NSObject
/**
 * @brief 音频丢包率。此次统计周期内的音频上行丢包率，取值范围为 [0, 1] 。  <br>
 */
@property (assign, nonatomic) float audioLossRate;
/**
 * @brief 发送的码率。此次统计周期内的音频发送码率，单位为 kbps 。  <br>
 */
@property (assign, nonatomic) float sentKBitrate;
/**
 * @brief 采集采样率。音频采集采样率信息，单位为 Hz 。  <br>
 */
@property (assign, nonatomic) NSInteger recordSampleRate;
/**
 * @brief 统计间隔。此次统计周期的间隔，单位为 ms 。  <br>
 */
@property (assign, nonatomic) NSInteger statsInterval;
/**
 * @brief 往返时延。单位为 ms 。  <br>
 */
@property (assign, nonatomic) NSInteger rtt;
/**
 * @brief 音频声道数。  <br>
 */
@property(assign, nonatomic) NSInteger numChannels;
/**
 * @brief 发送采样率。音频发送采样率信息，单位为 Hz 。  <br>
 */
@property(assign, nonatomic) NSInteger sentSampleRate;
@end

/**
 * @type keytype
 * @brief 远端音频流统计信息。  <br>
 *        本地用户订阅远端音频流成功后，SDK 会周期性（2s）的通过 rtcEngine:remoteAudioStats:{@link #ByteRtcEngineDelegate#rtcEngine:remoteAudioStats:} 回调事件通知用户订阅的音频流在此次统计周期内的状况。此数据结构即为回调给用户的参数类型。  <br>
 */
BYTE_RTC_EXPORT @interface ByteRtcRemoteAudioStats : NSObject
/**
 * @brief 用户ID 。远端音频流发布用户的用户ID 。  <br>
 */
@property (copy, nonatomic) NSString * _Nonnull uid;
/**
 * @brief 音频丢包率。统计周期内的音频下行丢包率，取值范围为 [0, 1] 。  <br>
 */
@property (assign, nonatomic) float audioLossRate;
/**
 * @brief 接收码率。统计周期内的音频接收码率，单位为 kbps 。  <br>
 */
@property (assign, nonatomic) float receivedKBitrate;
/**
 * @brief 音频卡顿次数。统计周期内的卡顿次数。  <br>
 */
@property (assign, nonatomic) NSInteger stallCount;
/**
 * @brief 音频卡顿时长。统计周期内的卡顿时长，单位为 ms 。  <br>
 */
@property (assign, nonatomic) NSInteger stallDuration;
/**
 * @brief 播放采样率。统计周期内的音频播放采样率信息，单位为 Hz 。  <br>
 */
@property (assign, nonatomic) NSInteger playoutSampleRate;
/**
 * @brief 用户体验级别的端到端延时。从发送端采集完成编码开始到接收端解码完成渲染开始的延时，单位为 ms 。  <br>
 */
@property (assign, nonatomic) NSInteger e2eDelay;
/**
 * @brief 统计间隔。此次统计周期的间隔，单位为 ms 。  <br>
 */
@property (assign, nonatomic) NSInteger statsInterval;
/**
 * @brief 往返时延。单位为 ms 。  <br>
 */
@property (assign, nonatomic) NSInteger rtt;
/**
 * @brief 远端用户发送的音频流质量。值含义参考 ByteNetworkQuality{@link #ByteNetworkQuality} 。  <br>
 */
@property(assign, nonatomic) NSInteger quality;
/**
 * @brief 音频发送端到接收端的网络延迟。单位为 ms 。  <br>
 */
@property(assign, nonatomic) NSInteger jitterBufferDelay;
/**
 * @brief 音频声道数。  <br>
 */
@property(assign, nonatomic) NSInteger numChannels;
/**
 * @brief 音频接收采样率。统计周期内接收到的远端音频采样率信息，单位为 Hz 。  <br>
 */
@property(assign, nonatomic) NSInteger receivedSampleRate;
/**
 * @brief 远端用户在加入房间后发生音频卡顿的累计时长占音频总有效时长的百分比。  <br>
 */
@property(assign, nonatomic) NSInteger frozenRate;
/**
 * @brief 音频 PLC 样点总个数。  <br>
 */
@property(assign, nonatomic) NSInteger concealedSamples;
/**
 * @brief PLC 累计次数。  <br>
 */
@property(assign, nonatomic) NSInteger concealmentEvent;
/**
 * @brief 音频解码采样率。统计周期内的音频解码采样率信息，单位为 Hz 。  <br>
 */
@property(assign, nonatomic) NSInteger decSampleRate;
/**
 * @brief 解码时长。单位为 s 。  <br>
 */
@property(assign, nonatomic) NSInteger decDuration;
@end

/**
 * @type keytype
 * @brief 音量信息
 */
BYTE_RTC_EXPORT @interface ByteRtcAudioVolumeInfo : NSObject
/**
 * @brief 音量信息所属用户的用户 id
 */
@property (copy, nonatomic) NSString * _Nonnull uid;
/**
 * @brief 用户音量大小信息，音量取值范围为 [0, 255]
 */
@property (assign, nonatomic) NSUInteger volume;
@end

/**
 *  @hidden
 *  @type keytype
 */
BYTE_RTC_EXPORT @interface ByteRtcOneClickHelplOption : NSObject
/**
 * @hidden
 * @brief 频道名称
 */
@property (nonatomic, strong) NSString * _Nonnull cname;
/**
 * @hidden
 * @brief 老师的id
 */
@property (nonatomic, strong) NSString * _Nonnull teacher_uid;
/**
 * @hidden
 * @brief 操作者的id
 */
@property (nonatomic, strong) NSString * _Nonnull action_uid;
/**
 * @hidden
 * @brief 问题类型（值由业务方自己定义）
 */
@property (nonatomic, strong) NSNumber * _Nonnull type;
/**
 * @hidden
 * @brief 问题发生的时间，Unix时间戳，单位为秒
 */
@property (nonatomic, strong) NSNumber * _Nullable ts;
/**
 * @hidden
 * @brief (可选)备注 可简单描述问题
 */
@property (nonatomic, strong) NSString * _Nullable comments;
@end

/**
 *  @type keytype
 *  @brief 网络质量
*/
BYTE_RTC_EXPORT @interface ByteRtcNetworkQuality : NSObject
/**
 *  @brief 网络状况信息所属用户的用户ID
*/
@property (nonatomic, strong) NSString * _Nonnull uid;
/**
 *  @brief 该用户的上行网络状态。如果该用户为远端用户，则为默认值ByteRtcNetworkQualityUnknown。类型含义详见ByteNetworkQuality{@link #ByteNetworkQuality}
*/
@property (nonatomic) ByteNetworkQuality txQuality;
/**
 *  @brief 该用户的下行网络状态。如果该用户为本地用户，则为默认值ByteRtcNetworkQualityUnknown。类型含义详见ByteNetworkQuality{@link #ByteNetworkQuality}
*/
@property (nonatomic) ByteNetworkQuality rxQuality;
@end

/**
 * @type keytype
 * @brief 性能回退相关数据
 */
BYTE_RTC_EXPORT @interface ByteSourceWantedData : NSObject
/**
 * @brief 推荐视频输入宽
 */
@property (nonatomic, assign) NSInteger width;
/**
 * @brief 推荐视频输入高
 */
@property (nonatomic, assign) NSInteger height;
/**
 * @brief 推荐视频输入帧率
 */
@property (nonatomic, assign) NSInteger frameRate;
@end

/**
 * @type api
 * @brief 视频外部渲染接口
 */
BYTE_RTC_EXPORT @protocol ByteVideoSinkProtocol <NSObject>
@required
/**
 * @type api
 * @brief 通知外部渲染器实现，当前需要进行渲染器初始化工作
 */
- (BOOL)shouldInitialize;
/**
 * @type api
 * @brief 通知外部渲染器实现，当前需要准备开始渲染
 */
- (void)shouldStart;
/**
 * @type api
 * @brief 通知外部渲染器实现，当前需要准备停止渲染
 */
- (void)shouldStop;
/**
 * @type api
 * @brief 通知外部渲染器实现，当前需要进行渲染器销毁工作
 */
- (void)shouldDispose;
/**
 * @type api
 * @brief 指定外部渲染器接收的视频帧格式类型
 * @return 指定的返回格式类型，类型含义详见ByteVideoPixelFormat{@link #ByteVideoPixelFormat}
 */
- (ByteVideoPixelFormat)pixelFormat;
/**
 * @type api
 * @brief 外部渲染视频帧数据回调接口
 * @param pixelBuffer 视频帧数据
 * @param rotation 视频帧的旋转角度 关于枚举，详见ByteVideoRotation{@link #ByteVideoRotation}
 * @param extendedData 视频帧所携带的额外SEI数据
 */
- (void)renderPixelBuffer:(CVPixelBufferRef _Nonnull)pixelBuffer
                 rotation:(ByteVideoRotation)rotation
             extendedData:(NSData * _Nullable)extendedData;
@end

/**
 * @hidden
 * @type api
 */
@protocol ByteVideoFrameConsumerObserver <NSObject>
/**
 * @hidden
 */
- (void)consumeYUV420Buffer:(CVPixelBufferRef _Nullable)ocFrame width:(NSInteger)width rotation:(NSInteger)rotation timestamp:(long)timestamp;
/**
 * @hidden
 */
- (void)consumeRGBABuffer:(CVPixelBufferRef _Nullable)ocFrame width:(NSInteger)width rotation:(NSInteger)rotation timestamp:(long)timestamp;
@end

/**
 *  @hidden
 *  @type keytype
 *  @brief 流信息
*/
@interface ByteRtcStreamOC : NSObject <ByteStream>
/**
 *  @brief 发布该流的用户的用户ID
*/
@property (nonatomic, copy, nullable) NSString *userId;
/**
 *  @brief 该流是否为屏幕流
*/
@property (nonatomic, assign) BOOL isScreen;
/**
 *  @brief 该流是否有视频
*/
@property (nonatomic, assign) BOOL hasVideo;
/**
 *  @brief 该流是否有音频
*/
@property (nonatomic, assign) BOOL hasAudio;
/**
 *  @brief 视频流描述信息，详见类型VideoStreamDescription{@link #VideoStreamDescription}
*/
@property (nonatomic, copy, nullable) NSArray<VideoStreamDescription *> *videoStreamDescriptions;
@end


/**
 *  @type keytype
 *  @brief 视频缩放模式
*/
typedef NS_ENUM(NSInteger,ByteVideoScaleMode){
    /**
     *  @brief 自动缩放模式，当前等价于FitWithCropping
    */
    Auto = 0,
    
    /**
     *  @brief 缩放以适配宽高比
    */
    Stretch = 1,
    
    /**
     *  @brief 保持纵横比来缩放图像，裁剪长边
    */
    FitWithCropping = 2,
    
    /**
     *  @brief 保持纵横比来缩放图像，填充短边
    */
    FitWithFilling = 3,
};

/**
 *  @type keytype
 *  @brief 视频属性
*/
BYTE_RTC_EXPORT @interface ByteVideoSolution : NSObject
/**
 *  @brief 视频宽度
*/
@property (assign, nonatomic) NSInteger width;
/**
 *  @brief 视频高度
*/
@property (assign, nonatomic) NSInteger height;
/**
 *  @brief 视频预设帧率
*/
@property (assign, nonatomic) NSInteger frameRate;
/**
 *  @brief 视频预设最大码率(Kbps)
*/
@property (assign, nonatomic) NSInteger maxKbps;
/**
 *  @brief 视频伸展模式，详见类型ByteVideoScaleMode{@link #ByteVideoScaleMode}
*/
@property (assign, nonatomic) ByteVideoScaleMode scaleMode;
/**
 *  @brief 视频编码质量偏好，详见类型ByteVideoEncoderPreference{@link #ByteVideoEncoderPreference}
*/
@property (assign, nonatomic) ByteVideoEncoderPreference encoderPreference;
@end

/**
 *  @type keytype
 *  @brief 音视频流属性
 *         发布到房间中的音视频流的流属性。用户加入房间成功后，房间中所有已发布和未来发布的音视频流和流的相关属性，都会通过
 *         rtcEngine:didStreamAdded:{@link #rtcEngine:didStreamAdded:} 回调通知用户。
 */
BYTE_RTC_EXPORT @interface ByteRtcByteStream : NSObject
/**
 *  @brief 发布此流的用户的 ID。
 */
@property (copy, nonatomic) NSString * _Nonnull uid;
/**
 *  @brief 流是否为共享屏幕流。
 */
@property (assign, nonatomic) BOOL isScreen;
/**
 *  @brief 流是否包括视频。
 */
@property (assign, nonatomic) BOOL hasVideo;
/**
 *  @brief 流是否包括音频。
 */
@property (assign, nonatomic) BOOL hasAudio;
/**
 *  @brief 视频流的分辨率信息，详见 ByteVideoSolution{@link #ByteVideoSolution} 类。
 *         用户可以通过调用 setVideoProfiles{@link #setVideoProfiles:} 方法在一路流中发布多个不同的视频分辨率。此参数即为流中
 *         所有分辨率的相关信息。
 */
@property (copy, nonatomic) NSArray<ByteVideoSolution *> * _Nullable streamProfiles;
@end

/**
 *  @type keytype
 *  @brief 订阅流配置参数。
 *         用户调用 subscribeStream:info:{@link #subscribeStream:info:} 方法手动订阅音视频流或更新订阅参数时，传入订阅流配置参数。
 */
BYTE_RTC_EXPORT @interface ByteSubscribeConfig : NSObject
/**
 *  @brief 订阅的流是否是屏幕共享流。
 */
@property (assign, nonatomic) BOOL isScreen;
/**
 *  @brief 是否订阅视频。
 */
@property (assign, nonatomic) BOOL subVideo;
/**
 *  @brief 是否订阅音频。
 */
@property (assign, nonatomic) BOOL subAudio;
/**
 *  @brief 订阅的视频流分辨率索引号。
 *         视频流中含多个分辨率的情况下，标识订阅第几个的视频分辨率。如果视频流中仅含一个分辨率，则为0。
 */
@property (assign, nonatomic) NSInteger videoIndex;
@end

/**
 *  @hidden
 *  @type keytype
 *  @brief 订阅状态码
 */
typedef NS_ENUM(NSInteger, ByteSubscribeState) {
    /**
     *  @brief 订阅成功
    */
    SUB_STATE_SUCCESS = 0,                  // 成功
    /**
     *  @brief 订阅失败，还未加入房间
    */
    SUB_STATE_FAILED_NOT_IN_ROOM = 1,       // 还没有加入房间
    /**
     *  @brief 订阅失败，没有找到流
    */
    SUB_STATE_FAILED_STREAM_NOT_FOUND = 2,  // 没有找到流
};

/**
 *  @type keytype
 *  @brief 音频帧类型
*/
typedef NS_ENUM(NSInteger, ByteRtcAudioFrameType) {
    /**
     *  @brief PCM16
    */
    FRAME_TYPE_PCM16 = 0, //PCM 16bit little endian
};

/**
 *  @type keytype
 *  @brief 视频帧类型
*/
typedef NS_ENUM(NSInteger, ByteRtcVideoFrameType) {
    /**
     * @brief unknown
     */
    FRAME_TYPE_UNKNOWN,
    /**
     * @brief ARGB image
     */
    FRAME_TYPE_ARGB,
    /**
     * @brief BGRA image
     */
    FRAME_TYPE_BGRA,
    /**
     * @brief RGBA image
     */
    FRAME_TYPE_RGBA,
    /**
     * @brief YUV image with i420 layout, also known as yuv420p
     */
    FRAME_TYPE_I420,
    /**
     * @brief YUV image with NV12 layout
     */
    FRAME_TYPE_NV12,
    /**
     * @brief YUV image with NV21 layout
     */
    FRAME_TYPE_NV21,
    /**
     * @brief 24 bit RGB image
     */
    FRAME_TYPE_RGB24,
};

/**
 *  @type keytype
 *  @brief 问题反馈列表
 */
typedef NS_OPTIONS(NSUInteger, ProblemFeedback){
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
 * @region 加密
 * @brief 加密类型
*/
typedef NS_OPTIONS(NSUInteger, ByteEncryptType) {
    /**
     * @brief 使用AES-128-CBC进行传输加密  <br>
    */
    ByteEncryptTypeAES128CBC = 1,
    /**
     * @brief 使用AES-256-CBC进行传输加密  <br>
    */
    ByteEncryptTypeAES256CBC = 2,
    /**
     * @brief 使用AES-128-ECB进行传输加密  <br>
    */
    ByteEncryptTypeAES128ECB = 3,
    /**
     * @brief 使用AES-256-ECB进行传输加密  <br>
    */
    ByteEncryptTypeAES256ECB = 4
};

/**
 *  @type keytype
 *  @brief 音频帧数据
*/
BYTE_RTC_EXPORT @interface ByteRtcAudioFrameData : NSObject
/**
 *  @brief 音频帧类型。详见类型ByteRtcAudioFrameType{@link #ByteRtcAudioFrameType}
*/
@property (assign, nonatomic) ByteRtcAudioFrameType type;
/**
 *  @brief 音频帧时间戳
*/
@property (assign, nonatomic) SInt64 timestampMs; // time for this frame.
/**
 *  @brief 每个声道音频帧的采样数
*/
@property (assign, nonatomic) int samples; //number of audio samples (per channel) described by this frame
/**
 *  @brief 音频声道数
*/
@property (assign, nonatomic) int channels; //number of channels
/**
 *  @brief 音频数据的采样率
*/
@property (assign, nonatomic) int sampleRate; //Sample rate of the audio data
/**
 *  @brief 数据缓冲
*/
@property (assign, nonatomic) UInt8 * _Nonnull buffer; //data buffer
@end

/**
 *  @type keytype
 *  @brief 视频帧数据
*/
BYTE_RTC_EXPORT @interface ByteRtcVideoFrameData : NSObject
/**
 *  @brief 视频帧类型。详见类型ByteRtcVideoFrameType{@link #ByteRtcVideoFrameType}
*/
@property (assign, nonatomic) ByteRtcVideoFrameType type;
/**
 *  @brief 视频帧时间戳
*/
@property (assign, nonatomic) SInt64 timestampMs; // time for this frame.
/**
 *  @brief 视频帧宽
*/
@property (assign, nonatomic) int width; //width of video frame
/**
 *  @brief 视频帧高
*/
@property (assign, nonatomic) int height; //height of video frame
/**
 *  @brief 视频帧y分量stride
*/
@property (assign, nonatomic) int yStride; //stride of Y data buffer
/**
 *  @brief 视频帧u分量stride
*/
@property (assign, nonatomic) int uStride; //stride of U data buffer
/**
 *  @brief 视频帧v分量stride
*/
@property (assign, nonatomic) int vStride; //stride of V data buffer
/**
 *  @brief 视频帧y分量数据缓冲
*/
@property (assign, nonatomic) UInt8 * _Nonnull yBuffer; //Y data buffer
/**
 *  @brief 视频帧u分量数据缓冲
*/
@property (assign, nonatomic) UInt8 * _Nonnull uBuffer; //U data buffer
/**
 *  @brief 视频帧v分量数据缓冲
*/
@property (assign, nonatomic) UInt8 * _Nonnull vBuffer; //V data buffer
/**
 *  @brief 视频帧选择度数
*/
@property (assign, nonatomic) int rotation;   // 0, 90, 180, 270. See document for rotation calculation
@end

/**
 *  @type keytype
 *  @brief 包信息
*/
BYTE_RTC_EXPORT @interface ByteRtcPacket : NSObject
/**
 *  @brief 数据缓存大小
*/
@property (assign, nonatomic) UInt size; //size of buffer
/**
 *  @brief 包数据缓存地址
*/
@property (assign, nonatomic) const UInt8 * _Nonnull buffer; //data buffer
@end

/**
 *  @type keytype
 *  @brief 屏幕分享时的高亮边框
*/
BYTE_RTC_EXPORT @interface ByteRtcHighlightConfig: NSObject

/**
 * @brief 是否显示高亮边框
 * 推荐值 YES
 */
@property (assign, nonatomic) BOOL enableHighlight;
/**
 * @brief 边框的颜色, 颜色格式为十六进制 ARGB:  0xAARRGGBB
 * 推荐值 0xFF29CCA3
 */
@property (assign, nonatomic) uint32_t borderColor;
/**
 * @brief 边框的宽度
 * 推荐值 4
 */
@property (assign, nonatomic) int borderWidth;

@end

/**
 * @type keytype
 * @brief 屏幕共享的编码参数配置
 */
BYTE_RTC_EXPORT @interface ByteRtcScreenCaptureParameters : NSObject

/**
 * @brief 屏幕采集编码最大宽度
 */
@property (assign, nonatomic) int maxWidth;
/**
 * @brief 屏幕采集编码最大高度
 */
@property (assign, nonatomic) int maxHeight;
/**
 * @brief 屏幕采集编码帧率, 单位 fps
 */
@property (assign, nonatomic) int frameRate;
/**
 * @brief 屏幕采集编码码率, -1 为自动码率, SDK 会根据宽高信息选择合适的码率，单位 kbps
 */
@property (assign, nonatomic) int bitrate;
/**
 * @brief 是否捕获鼠标光标
 */
@property (assign, nonatomic) BOOL captureMouseCursor;
/**
 * @brief 抓取屏幕时排除窗口列表。这个参数仅在抓取屏幕时生效。
 */
@property (strong, nonatomic) NSArray<NSNumber *> * _Nullable excludedWindowList;
/**
 * @brief 高亮边框的配置
 */
@property (strong, nonatomic) ByteRtcHighlightConfig * _Nonnull highlightConfig;

@end

/**
 *  @type keytype
 *  @brief 屏幕分享时共享对象的信息
 */
BYTE_RTC_EXPORT @interface ByteRtcScreenCaptureSourceInfo : NSObject
/**
 * @brief 屏幕分享时共享对象的类型。
 */
@property (assign, nonatomic) ByteScreenCaptureSourceType sourceType;
/**
 * @brief 屏幕分享时共享对象的 ID。
 */
@property (assign, nonatomic) intptr_t sourceId;
/**
 * @brief 屏幕分享时共享对象的名称。
 */
@property (copy, nonatomic) NSString * _Nullable sourceName;

@end

/**
 * @type keytype
 * @brief 用户机型等级信息。
 *        在部分应用场景下，需要关注用户机型的配置高低，根据不同的配置，选择不同复杂度的音频处理算法，在能耗、用户体验上进行折中。
*/
typedef NS_ENUM(NSUInteger, ByteAudioPerformanceProfile) {
    /**
     * @brief 自动策略，SDK 会在加入房间时上传机型信息。服务端根据机型信息判断性能级别，下发对应配置。
    */
    kByteAudioPerformanceProfileAuto = 0,
    /**
     * @brief 低配策略，关闭 AEC、ANS、AGC 算法，播放 sample rate 为 16000。
     *        策略内容可以定制，联系销售咨询具体方案
    */
    kByteAudioPerformanceProfileLow = 1,
    /**
     * @brief 中配策略，开启 AEC、ANS、AGC 算法，播放 sample rate 为 16000。
     *        策略内容可以定制，联系销售咨询具体方案
    */
    kByteAudioPerformanceProfileMid = 2,
    /**
     * @brief 高配策略，开启 AEC、ANS、AGC 算法，播放 sample rate 为 48000。
     *        策略内容可以定制，联系销售咨询具体方案
    */
    kByteAudioPerformanceProfileHigh = 3
};

#endif /* Header_h */
