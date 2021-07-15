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
#import <UIKit/UIKit.h>

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
     *  @brief 视频尺寸非等比例缩放，把窗口充满。当视频尺寸与显示窗口尺寸不一致时，视频高或宽方向会被拉伸。
    */
    ByteRtc_Render_Adaptive = 3,
};

/**
 *  @type keytype
 *  @brief 用户离线原因。  <br>
 *         房间内的远端用户离开房间时，本地用户会收到 rtcEngine:didOfflineOfUid:reason:{@link #ByteRtcEngineDelegate#rtcEngine:didOfflineOfUid:reason:} 回调通知，此枚举类型为回调的用户离线原因。  <br>
 */
typedef NS_ENUM(NSUInteger, ByteRtcUserOfflineReason) {
    /**
     *  @brief 用户主动离开。如远端用户调用 leaveChannel:{@link #ByteRtcEngineKit#leaveChannel:} 方法退出房间。  <br>
     */
    ByteRtc_UserOffline_Quit = 0,
    /**
     *  @brief 用户掉线。远端用户因为网络等原因掉线。  <br>
     */
    ByteRtc_UserOffline_Dropped = 1,
    /**
     *  @hidden
     */
    ByteRtc_UserOffline_BecomeAudience = 2,
};

/**
 * @type keytype
 * @brief 房间内远端流移除原因。  <br>
 *        房间内远端音视频流移除时，SDK 会通过 rtcEngine:didStreamRemoved:stream:reason:{@link #ByteRtcEngineDelegate#rtcEngine:didStreamRemoved:stream:reason:} 回调通知用户。此枚举类型即为通知的远端流移除的原因。  <br>
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
 *  @brief 房间模式。房间使用的场景模式。  <br>
 *         通过设置房间模式，用户可以选择应用 SDK 针对不同房间模式场景的优化策略。设置房间模式参考 setChannelProfile:{@link #ByteRtcEngineKit#setChannelProfile:} 方法。  <br>
 */
typedef NS_ENUM(NSInteger, ByteChannelProfile) {
    /**
     *  @brief 通信模式。通信模式下，无用户角色区分。适用于 IM 场景。  <br>
     */
    ByteChannelProfileCommunication = 0,
    /**
     *  @brief 直播模式。直播模式下，有用户角色区分（用户角色参考 ByteRtcClientRole{@link #ByteRtcClientRole}）。适用于直播、教育大班课等场景。  <br>
     */
    ByteChannelProfileLiveBroadcasting = 1,
    /**
     *  @brief 游戏模式。游戏模式下，有用户角色区分。 SDK 会使用低延时设置。适用于游戏场景。  <br>
     */
    ByteChannelProfileGame = 2,
    /**
     *  @brief 云游戏模式。云游戏模式下，有用户角色区分。 SDK 会使用低延时设置。适用于云游戏场景。  <br>
     */
    ByteChannelProfileCloudGame = 3,
};

/**
 *  @type keytype
 *  @brief 用户角色。房间模式为直播、游戏、云游戏模式时的可选用户角色。  <br>
 *         用户可通过设置用户角色控制：1.发布/取消发布音视频流；2.用户自身是否在房间中隐身。设置用户角色参考 setClientRole:{@link #ByteRtcEngineKit#setClientRole:} 方法。  <br>
 */
typedef NS_ENUM(NSInteger, ByteRtcClientRole) {
    /**
     *  @brief 主播角色。主播角色的用户既可以发布流到房间中，也可以从房间中订阅流，房间中的其他用户可以感知到该用户在房间中。  <br>
     */
    ByteRtc_ClientRole_Broadcaster = 1,
    /**
     *  @hidden
     */
    ByteRtc_ClientRole_PSTNCaller = 3,
    /**
     *  @brief 静默观众角色。静默观众角色的用户只能从房间中订阅流，不能向房间中发布流，房间中的其他用户无法感知到该用户在房间中。该用户加入退出房间等行为不会通知给房间中的其他用户。  <br>
     */
    ByteRtc_ClientRole_Silent_Audience = 4,
};

    /**
    * @type keytype
    * @brief 音频场景类型。<br>
    *        选择音频场景后，RTC 会自动根据客户端音频路由和发布订阅状态，适用通话音量/媒体音量。<br>
    *        你可以调用 setAudioScenario:{@link #setAudioScenario:} 设置音频场景。<br>
    *        如果以下音频场景类型无法满足你的业务需要，请联系技术支持同学进行定制。
    */
typedef NS_ENUM(NSInteger, ByteRtcAudioScenarioType) {
    /**
     * @brief 音乐场景。默认为此场景。<br>
     *        此场景适用于对音乐表现力有要求的场景。如音乐直播等。<br>
     *        音频路由和发布订阅状态，到音量类型的映射如下：<br>
     *        <table>
     *           <tr><th></th><th>仅发布音视频流</th><th>仅订阅音视频流</th><th>发布并订阅音视频流</th><th>备注</th></tr>
     *           <tr><td>设备自带麦克风和扬声器/听筒</td><td>媒体音量</td><td>媒体音量</td><td>通话音量</td><td>/</td></tr>
     *           <tr><td>有线耳机</td><td>媒体音量</td><td>媒体音量</td><td>媒体音量</td><td>/</td></tr>
     *           <tr><td>蓝牙耳机</td><td>媒体音量</td><td>媒体音量</td><td>媒体音量</td><td>使用蓝牙耳机上自带的麦克风进行音频采集。</td></tr>
     *        </table>
     */
    ByteAudioScenarioMusic = 0,
    /**
     * @brief 高质量通话场景。<br>
     *        此场景适用于对音乐表现力有要求的场景。
     *        此场景可以兼顾外放/使用蓝牙耳机时的音频体验。<br>
     *        音频路由和发布订阅状态，到音量类型的映射如下：<br>
     *        <table>
     *           <tr><th></th><th>仅发布音视频流</th><th>仅订阅音视频流</th><th>发布并订阅音视频流</th> <th>备注</th> </tr>
     *           <tr><td>设备自带麦克风和扬声器/听筒</td><td>媒体音量</td><td>媒体音量</td><td>通话音量</td><td>/</td></tr>
     *           <tr><td>有线耳机</td><td>媒体音量</td><td>媒体音量</td><td>媒体音量</td><td>/</td></tr>
     *           <tr><td>蓝牙耳机</td><td>通话音量</td><td>通话音量</td><td>通话音量</td><td>使用蓝牙耳机上自带的麦克风进行音频采集。</td></tr>
     *        </table>
     */
    ByteAudioScenarioHighqualityCommunication = 1,
    /**
     * @brief 纯通话音量场景。<br>
     *        此场景下，无论客户端音频路由情况和发布订阅状态，全程使用通话音量。
     *        适用于需要频繁上下麦的通话或会议场景。<br>
     *        此场景可以保持统一的音频模式，不会有音量突变的听感；
     *        最大程度上的消除回声，使通话清晰度达到最优；
     *        使用蓝牙耳机时，能够使用蓝牙耳机上自带的麦克风进行音频采集。<br>
     *        但是，使用媒体音量进行播放的其他音频的音量会被压低，且音质会变差。
     */
    ByteAudioScenarioCommunication = 2,
    /**
     * @brief 纯媒体场景。一般不建议使用。<br>
     *        此场景下，无论客户端音频路由情况和发布订阅状态，全程使用媒体音量。
     *        外放通话时，极易出现回声和啸叫。
     */
    ByteAudioScenarioMedia = 3,
};







/**
 * @type keytype
 * @brief SDK 与 RTC 服务器连接状态。
 */
typedef NS_ENUM(NSInteger, ByteRtcConnectionState) {
    /**
     * @brief 连接断开。
     */
    ByteRtc_ConnectionState_Disconnected = 1,
    /**
     * @brief 首次连接，正在连接中。
     */
    ByteRtc_ConnectionState_Connecting = 2,
    /**
     * @brief 首次连接成功。
     */
    ByteRtc_ConnectionState_Connected = 3,
    /**
     * @brief 连接断开后，重新连接中。
     */
    ByteRtc_ConnectionState_Reconnecting = 4,
    /**
     * @brief 连接断开后，重连成功。
     */
    ByteRtc_ConnectionState_Reconnected = 5,
    /**
     * @brief 网络连接断开超过 10 秒。SDK 仍然会继续尝试重连。
     */
    ByteRtc_ConnectionState_Lost = 6,
};


/**
 * @type keytype
 * @brief SDK 网络连接类型。
 */
typedef NS_ENUM(NSInteger, ByteRtcNetworkType) {
    /**
     * @brief 网络连接类型未知。
     */
    ByteRtcNetworkTypeUnknown = -1,
    /**
     * @brief 网络连接已断开。
     */
    ByteRtcNetworkTypeDisconnected = 0,
    /**
     * @brief 网络连接类型为 LAN 。
     */
    ByteRtcNetworkTypeLAN = 1,
    /**
     * @brief 网络连接类型为 Wi-Fi（包含热点）。
     */
    ByteRtcNetworkTypeWIFI = 2,
    /**
     * @brief 网络连接类型为 2G 移动网络。
     */
    ByteRtcNetworkTypeMobile2G = 3,
    /**
     * @brief 网络连接类型为 3G 移动网络。
     */
    ByteRtcNetworkTypeMobile3G = 4,
    /**
     * @brief 网络连接类型为 4G 移动网络。
     */
    ByteRtcNetworkTypeMobile4G = 5,
    /**
     * @brief 网络连接类型为 5G 移动网络。
     */
    ByteRtcNetworkTypeMobile5G = 6,
};

/**
 *  @type keytype
 *  @brief 视频流类型
 *      目前C++ SDK 只支持 ByteRtc_VideoStream_High 类型
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
 * @brief 媒体流网络质量。
 */
typedef NS_ENUM(NSUInteger, ByteNetworkQuality) {
    /**
     * @brief 网络质量未知。
     */
    ByteRtcNetworkQualityUnknown = 0,
    /**
     * @brief 网络质量极好。
     */
    ByteRtcNetworkQualityExcellent = 1,
    /**
     * @brief 网络质量好。
     */
    ByteRtcNetworkQualityGood = 2,
    /**
     * @brief 网络质量较差但不影响沟通。
     */
    ByteRtcNetworkQualityPoor = 3,
    /**
     * @brief 网络质量差沟通不顺畅。
     */
    ByteRtcNetworkQualityBad = 4,
    /**
     * @brief 网络质量非常差。
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
 *         SDK 内部遇到不可恢复的错误时，会通过 rtcEngine:didOccurError:{@link #ByteRtcEngineDelegate#rtcEngine:didOccurError:} 回调通知用户。
 */
typedef NS_ENUM(NSInteger, ByteRtcErrorCode) {
    /**
     *  @brief Token 无效。
     *         调用joinChannelByKey:channelName:info:uid:{@link #ByteRtcEngineKit#joinChannelByKey:channelName:info:uid:} 方法时使用的 Token 无效或过期失效。需要用户重新获取 Token，并调用
     *         renewChannelKey:{@link #ByteRtcEngineKit#renewChannelKey:} 方法更新 Token。
     */
    BRERR_INVALID_TOKEN               = -1000,
    /**
     *  @brief 加入房间错误。
     *         调用 joinChannelByKey:channelName:info:uid:{@link #ByteRtcEngineKit#joinChannelByKey:channelName:info:uid:} 方法时发生未知错误导致加入房间失败。需要用户重新加入房间。
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
 *  @hidden
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
    /**
     * @brief 超过订阅流数上限
     */
    SUBSCRIBE_STATE_FAILED_OVER_LIMIT,
};

/**
 *  @type keytype
 *  @brief 设置本地视频属性的返回状态。
 */
typedef NS_ENUM(NSInteger, VideoStreamState) {
    /**
     *  @brief 设置本地视频属性成功
    */
    VIDEO_STREAM_SUCCESS                 = 0,
    /**
     *  @brief 本地视频属性参数不合法
    */
    VIDEO_STREAM_INVALID                 = -2,
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
     *        用户调用 joinChannelByKey:channelName:info:uid:{@link #ByteRtcEngineKit#joinChannelByKey:channelName:info:uid:} 加入房间或由于网络状况不佳断网重连时，由于服务器错误导致用户加入房间失败。SDK 会自动重试加入房间。
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
     *  @brief 调度异常，服务器返回的媒体服务器地址不可用。
    */
    BRWARN_INVALID_EXPECT_MS_ADDR = -2007,
    /**
     * @brief 发送自定义广播消息失败，当前用户未在房间中。
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
    /**
     * @brief 播放设备启动失败警告
     *      可能由于系统资源不足，或参数错误
     */
    BRWARN_ADM_PLAYOUT_START_FAIL = -5004
};

/**
 *  @type errorcode
 *  @brief 直播推流转码状态码。  <br>
 *         用户调用 enableLiveTranscoding:{@link #ByteRtcEngineKit#enableLiveTranscoding:} 方法启动直播推流转码功能后，SDK 通过 rtcEngine:TransCodingWithUrl:errorCode:{@link #ByteRtcEngineDelegate#rtcEngine:TransCodingWithUrl:errorCode:} 回调通知用户直播推流转码功能启动成功或失败、推流发生错误等状态事件。回调给用户的直播推流转码功能状态码即为此枚举类型。
 */
typedef NS_ENUM(NSInteger, ByteRtcTransCodeingErrorCode) {
    /**
     *  @brief 推流成功。  <br>
     */
    TRANSCODING_ERR_OK = 0,
    /**
     *  @brief 推流参数错误。需要用户更新合流参数并重试。  <br>
     */
    TRANSCODING_ERR_INVALID_ARGUMENT = 1,
    /**
     *  @brief 后处理订阅流失败。  <br>
     */
    TRANSCODING_ERR_SUBSCRIBE_FAILED = 2,
    /**
     *  @brief 合流服务中间过程存在错误。  <br>
     */
    TRANSCODING_ERR_PROCESSING = 3,
    /**
     *  @brief 推 CDN 失败。  <br>
     */
    TRANSCODING_ERR_PUBLISH_STREAM_CDN_ERROR = 4,
};

/**
 * @hidden
 * @type keytype
 * @brief 音频采集编码属性。每一项代表一组特定的采样率、编码码率、通道数、编码场景。
 * @notes 暂时不支持该参数的设置。
 */
typedef NS_ENUM(NSInteger, ByteRtcAudioProfile) {
    /**
     * @brief 默认设置，通信场景下，该选项代表指定 32 kHz 采样率，语音编码，单声道，编码码率最大值为 18 Kbps
     * 直播场景下，该选项代表指定 48 kHz 采样率，音乐编码，单声道，编码码率最大值为 64 Kbps
     */
    ByteRtc_AudioProfile_Default = 0,
    /**
     * @brief 指定 32 kHz 采样率，语音编码, 单声道，编码码率最大值为 18 Kbps
     */
    ByteRtc_AudioProfile_SpeechStandard = 1,
    /**
     * @brief 指定 48 kHz 采样率，音乐编码, 单声道，编码码率最大值为 50 Kbps
     */
    ByteRtc_AudioProfile_MusicStandard = 2,
    /**
     * @brief 指定 48 kHz采样率，音乐编码, 双声道，编码码率最大值为 50 Kbps
     */
    ByteRtc_AudioProfile_MusicStandardStereo = 3,
    /**
     * @brief 指定 48 kHz 采样率，音乐编码, 单声道，编码码率最大值为 128 Kbps
     */
    ByteRtc_AudioProfile_MusicHighQuality = 4,
    /**
     * @brief 指定 48 kHz 采样率，音乐编码, 双声道，编码码率最大值为 192 Kbps
     */
    ByteRtc_AudioProfile_MusicHighQualityStereo = 5,
};

/**
 *  @type keytype
 *  @brief 视频输出方向模式
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
 * @type keytype
 * @hidden
 * @brief 日志级别。
 */
typedef enum {
    /**
     * @hidden
     * @brief 打印 trace 级别及以上级别信息。
     */
    RTC_LOG_LEVEL_TRACE,
    /**
     * @hidden
     * @brief 打印 debug 级别及以上级别信息。
     */
    RTC_LOG_LEVEL_DEBUG,
    /**
     * @hidden
     * @brief 打印 info 级别及以上级别信息。
     */
    RTC_LOG_LEVEL_INFO,
    /**
     * @hidden
     * @brief 打印 warning 级别及以上级别信息。
     */
    RTC_LOG_LEVEL_WARNING,
    /**
     * @hidden
     * @brief 打印 error 级别信息。
     */
    RTC_LOG_LEVEL_ERROR
} ByteRtcLogLevel;

/**
 *  @type keytype
 *  @brief 日志类型。
 */
typedef enum {
    /**
     * @brief 平台层日志。
     */
    BYTE_RTC_LOG,
    /**
     * @brief Native 层日志。
     */
    ORIGIN_RTC_LOG,
} RtcLogType;

/**
 *  @type keytype
 *  @brief 音频输出路由
 *         音频路由变化时 SDK 通过 rtcEngine:didAudioRouteChanged:{@link #rtcEngine:didAudioRouteChanged:} 回调该错误码
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
     *  @brief 从蓝牙设备输出
    */
    ByteAudioOutputRoutingHeadsetBluetooth = 5
};

/**
 *  @hidden
 *  @type keytype
 * @brief 视频帧类型
 */
typedef NS_ENUM(NSInteger, ByteVideoPixelFormat) {
    /**
     * @hidden
     * @brief YUV image with i420 layout, also known as yuv420p
     */
    ByteVideoPixelFormatI420 = 1,
    /**
     * @hidden
     * @brief BGRA image
     */
    ByteVideoPixelFormatBGRA = 2,
    /**
     * @hidden
     * @brief YUV image with NV21 layout
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
     *  @brief 自动缩放模式，当前等价于 ByteVideoStreamScaleModeFitWithCropping
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
 *  @type keytype
 *  @brief 视频编码算法
*/
typedef NS_ENUM(NSInteger, ByteVideoCodecName) {
    /**
     *  @brief 自动选择
    */
    ByteVideoCodecAuto         = 0,
    /**
     *  @brief H264
    */
    ByteVideoCodecH264         = 1,
    /**
     *  @brief ByteVC1
    */
    ByteVideoCodecByteVC1         = 2,
};

/**
 *  @type keytype
 *  @brief 视频编码模式
*/
typedef NS_ENUM(NSInteger, ByteVideoCodecMode) {
    /**
     *  @brief 自动选择
    */
    ByteVideoCodecAutoMode     = 0,
    /**
     *  @brief 硬编码
    */
    ByteVideoCodecHardwareMode = 1,
    /**
     *  @brief 软编码
    */
    ByteVideoCodecSoftwareMode = 2,
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
 * @type keytype
 * @brief 消息发送结果。
 */
typedef NS_ENUM(NSInteger, UserMessageCode) {
    /**
     * @brief 成功。
     */
    USER_MESSAGE_SUCCESS = 0,
    /**
     * @brief 失败，超时。
     */
    USER_MESSAGE_ERROR_TIMEOUT = 1,
    /**
     * @brief 失败，连接中断。
     */
    USER_MESSAGE_ERROR_BROKEN = 2,
    /**
     * @brief 失败，没有找到对应的接收者。
     */
    USER_MESSAGE_ERROR_NO_RECEIVER = 3,
    /**
     * @brief 失败，获取级联路径失败
     */
    USER_MESSAGE_ERROR_NO_REALY_PATH = 4,
    /**
     * @brief 失败，没有加入房间。
     */
    USER_MESSAGE_ERROR_NOT_JOIN = 100,
    /**
     * @brief 失败，连接未完成初始化。
     */
    USER_MESSAGE_ERROR_INIT = 101,
    /**
     * @brief 失败，没有可用的连接。
     */
    USER_MESSAGE_ERROR_NO_CONNECTION = 102,
    /**
     * @brief 消息超过最大长度，当前为64KB
     */
    USER_MESSAGE_ERROR_EXCEED_MAX_LENGTH = 103,
    /**
     * @brief 用户id为空
     */
    USER_MESSAGE_ERROR_EMPTY_USER = 104,
    /**
     * @brief 失败，未知错误。
     */
    USER_MESSAGE_ERROR_UNKNOWN = 1000,
};

/**
 * @type keytype
 * @brief 消息发送结果。
 */
typedef NS_ENUM(NSInteger, RoomMessageCode) {
    /**
     * @brief 成功。
     */
    ROOM_MESSAGE_SUCCESS = 200,
    /**
     * @brief 失败，没有加入房间。
     */
    ROOM_MESSAGE_ERROR_NOT_JOIN = 100,
    /**
     * @brief 失败，连接未完成初始化。
     */
    ROOM_MESSAGE_ERROR_INIT = 101,
    /**
     * @brief 失败，没有可用的连接。
     */
    ROOM_MESSAGE_ERROR_NO_CONNECTION = 102,
    /**
     * @brief 消息超过最大长度，当前为64KB
     */
    ROOM_MESSAGE_ERROR_EXCEED_MAX_LENGTH = 103,
    /**
     * @brief 失败，未知错误。
     */
    ROOM_MESSAGE_ERROR_UNKNOWN = 1000,
};

/**
 * @hidden
 * @type keytype
 * @brief SDK 的服务器环境。
 */
typedef NS_ENUM(NSInteger, ByteRtcEnv) {
    /**
     * @hidden
     * @brief 线上环境。
     */
    kByteRtcEnvProduct = 0,
    /**
     * @hidden
     * @brief BOE 环境。
     */
    kByteRtcEnvBOE = 1,
    /**
     * @hidden
     * @brief 测试环境。
     */
    kByteRtcEnvTest = 2,
};

/**
 *  @hidden
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
 *  @hidden
 *  @type keytype
 *  @brief 语音通话模式，在小队语音里用这个接口设置自己的发送模式
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
* @type keytype
* @brief 用户机型等级信息。
*        在部分应用场景下，需要关注用户机型的配置高低，根据不同的配置，选择不同复杂度的音频处理算法，在能耗、用户体验上进行折中。
*/
typedef NS_ENUM(NSUInteger, AudioPerfProfile) {
    /**
    * @brief 自动策略，SDK 会在加入房间时上传机型信息。服务端根据机型信息判断性能级别，下发对应配置。
    */
    AUDIO_PERF_PROFILE_AUTO = 0,
    /**
    * @brief 低配策略，关闭 AEC、ANS、AGC 算法，播放 sample rate 为 16000。
    *        策略内容可以定制，联系销售咨询具体方案
    */
    AUDIO_PERF_PROFILE_LOW = 1,
    /**
    * @brief 中配策略，开启 AEC、ANS、AGC 算法，播放 sample rate 为 16000。
    *        策略内容可以定制，联系销售咨询具体方案
    */
    AUDIO_PERF_PROFILE_MID = 2,
    /**
    * @brief 高配策略，开启 AEC、ANS、AGC 算法，播放 sample rate 为 48000。
    *        策略内容可以定制，联系销售咨询具体方案
    */
    AUDIO_PERF_PROFILE_HIGH = 3,
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
 *  @type keytype
 *  @brief 订阅回退选项
 */
typedef NS_ENUM(NSUInteger, ByteSubscribeFallbackOption) {
    /**
     *  @brief 下行网络较弱时，不对音视频流作回退处理，默认值
    */
  ByteSubscribeFallbackOptionDisabled = 0,
    /**
     *  @brief 下行网络较弱时只接收视频小流
    */
  ByteSubscribeFallbackOptionVideoStreamLow = 1,
    /**
     *  @brief 下行网络较弱时，先尝试只接收视频小流；如果网络环境无法显示视频，则再回退到只接收远端订阅的音频流
    */
  ByteSubscribeFallbackOptionAudioOnly = 2,
};

/**
 * @type keytype
 * @brief 远端用户优先级，在性能不足需要回退时，会优先回退优先级低的用户的音视频流
 */
typedef NS_ENUM(NSUInteger, ByteUserPriority) {
    /**
     * @brief 用户优先级为低，默认值
     */
    ByteUserPriorityLow = 0,
    /**
     * @brief 用户优先级为正常
     */
    ByteUserPriorityMedium = 100,
    /**
     * @brief 用户优先级为高
     */
    ByteUserPriorityHigh = 200,
};

/**
 *  @type keytype
 *  @brief 远端订阅流发生回退或恢复的原因
 */
typedef NS_ENUM(NSInteger, ByteFallbackOrRecoverReason) {
    /**
     * @brief 其他原因，非带宽和性能原因引起的回退或恢复。默认值
     */
    ByteFallbackReasonUnknown = -1,
    /**
     * @brief 由带宽不足导致的订阅端音视频流回退。
     */
    ByteSubscribeFallbackByBandwidth = 0,
    /**
     * @brief 由性能不足导致的订阅端音视频流回退。
     */
    ByteSubscribeFallbackByPerformance = 1,
    /**
     * @brief 由带宽恢复导致的订阅端音视频流恢复。
     */
    ByteSubscribeRecoverByBandwidth = 2,
    /**
     * @brief 由性能恢复导致的订阅端音视频流恢复。
     */
    ByteSubscribeRecoverByPerformance = 3,
    /**
     * @brief 由带宽不足导致的发布端音视频流回退。
     */
    BytePublishFallbackByBandwidth = 4,
    /**
     * @brief 由性能不足导致的发布端音视频流回退。
     */
    BytePublishFallbackByPerformance = 5,
    /**
     * @brief 由带宽恢复导致的发布端音视频流恢复。
     */
    BytePublishRecoverByBandwidth = 6,
    /**
     * @brief 由性能恢复导致的发布端音视频流恢复。
     */
    BytePublishRecoverByPerformance = 7,

};

/**
 * @type keytype
 * @brief 本地音频流状态。
 *        SDK 通过 rtcEngine:localAudioStateChanged:error:{@link #rtcEngine:localAudioStateChanged:error:} 回调本地音频流状态
 */
typedef NS_ENUM(NSInteger, ByteLocalAudioStreamState) {
    /**
    * @brief 本地音频默认初始状态。
    *        麦克风停止工作时回调该状态，对应错误码 ByteLocalAudioStreamErrorOk{@link #ByteLocalAudioStreamErrorOk}
    */
    ByteLocalAudioStreamStateStopped = 0,

    /**
    * @brief 本地音频录制设备启动成功。
    *        采集到音频首帧时回调该状态，对应错误码 ByteLocalAudioStreamErrorOk{@link #ByteLocalAudioStreamErrorOk}
    */
    ByteLocalAudioStreamStateRecording = 1,

    /**
    * @brief 本地音频首帧编码成功。
    *        音频首帧编码成功时回调该状态，对应错误码 ByteLocalAudioStreamErrorOk{@link #ByteLocalAudioStreamErrorOk}
    */
    ByteLocalAudioStreamStateEncoding = 2,

    /**
    * @brief  本地音频启动失败，在以下时机回调该状态：  <br>
    *       + 本地录音设备启动失败，对应错误码 ByteLocalAudioStreamErrorRecordFailure{@link #ByteLocalAudioStreamErrorRecordFailure}  <br>
    *       + 检测到没有录音设备权限，对应错误码 ByteLocalAudioStreamErrorDeviceNoPermission{@link #ByteLocalAudioStreamErrorDeviceNoPermission}  <br>
    *       + 音频编码失败，对应错误码 ByteLocalAudioStreamErrorEncodeFailure{@link #ByteLocalAudioStreamErrorEncodeFailure}  <br>
    */
    ByteLocalAudioStreamStateFailed = 3,
};

/**
 * @type keytype
 * @brief 本地音频流状态改变时的错误码
 *        SDK 通过 rtcEngine:localAudioStateChanged:error:{@link #rtcEngine:localAudioStateChanged:error:} 回调该错误码
 */
typedef NS_ENUM(NSInteger, ByteLocalAudioStreamError) {
    /**
     * @brief 本地音频状态正常
     */
    ByteLocalAudioStreamErrorOk = 0,

    /**
     * @brief 本地音频出错原因未知
     */
    ByteLocalAudioStreamErrorFailure = 1,

    /**
     * @brief 没有权限启动本地音频录制设备
     */
    ByteLocalAudioStreamErrorDeviceNoPermission = 2,

    /**
     * @brief 本地音频录制设备已经在使用中
     * @notes 该错误码暂未使用
     */

    ByteLocalAudioStreamErrorDeviceBusy = 3,

    /**
     * @brief 本地音频录制失败，建议你检查录制设备是否正常工作
     */
    ByteLocalAudioStreamErrorRecordFailure = 4,

    /**
     * @brief 本地音频编码失败
     */
    ByteLocalAudioStreamErrorEncodeFailure = 5,
};

/**
 *  @type keytype
 *  @brief 本地视频流状态
 */
typedef NS_ENUM(NSInteger, ByteLocalVideoStreamState) {
  /**
   * @brief 本地视频默认初始状态
   *        摄像头停止工作时回调该状态，对应错误码 ByteLocalVideoStreamErrorOk{@link #ByteLocalVideoStreamErrorOk}
   */
  ByteLocalVideoStreamStopped = 0,
  /**
   * @brief 本地视频录制设备启动成功
   *        采集到视频首帧时回调该状态，对应错误码 ByteLocalVideoStreamErrorOk{@link #ByteLocalVideoStreamErrorOk}
   */
  ByteLocalVideoStreamRecording = 1,
  /**
   * @brief 本地视频首帧编码成功
   *        本地视频首帧编码成功时回调该状态，对应错误码 ByteLocalVideoStreamErrorOk{@link #ByteLocalVideoStreamErrorOk}
   */
  ByteLocalVideoStreamEncoding = 2,
  /**
   * @brief  本地视频启动失败, 在以下时机回调该状态：  <br>
   *       + 本地采集设备启动失败，对应错误码 ByteLocalVideoStreamErrorRecordFailure{@link #ByteLocalVideoStreamErrorRecordFailure}  <br>
   *       + 检测到没有摄像头权限，对应错误码 ByteLocalVideoStreamErrorDeviceNoPermission{@link #ByteVideoStreamErrorDeviceNoPermission}  <br>
   *       + 视频编码失败，对应错误码 ByteLocalVideoStreamErrorEncodeFailure{@link #ByteLocalVideoStreamErrorEncodeFailure}  <br>
   */
  ByteLocalVideoStreamFailed = 3,
};

/**
 *  @type keytype
 *  @brief 本地视频状态改变时的错误码
 */
typedef NS_ENUM(NSInteger, ByteLocalVideoStreamError) {
  /**
   * @brief 本地视频状态正常
   */
  ByteLocalVideoStreamErrorOk = 0,
  /**
   * @brief 视频流发布失败
   */
  ByteLocalVideoStreamErrorFailure = 1,
  /**
   * @brief 没有权限启动本地视频录制设备
   */
  ByteLocalVideoStreamErrorDeviceNoPermission = 2,
  /**
   * @brief 本地视频录制设备已经在使用中
   */
  ByteLocalVideoStreamErrorDeviceBusy = 3,
  /**
   * @brief 本地视频录制失败，建议检查录制设备是否正常工作
   */
  ByteLocalVideoStreamErrorRecordFailure = 4,
  /**
   * @brief 本地视频编码失败
   */
  ByteLocalVideoStreamErrorEncodeFailure = 5,
};

/**
 * @type keytype
 * @brief 远端音频流状态
 *        SDK 通过 rtcEngine:remoteAudioStateChanged:state:reason:elapsed:{@link #rtcEngine:remoteAudioStateChanged:state:reason:elapsed:} 回调该状态
 */
typedef NS_ENUM(NSInteger, ByteRemoteAudioState) {
    /**
     * @brief  远端音频流默认初始状态，在以下时机回调该状态：  <br>
     *       + 本地用户停止接收远端音频流，对应错误码 ByteRemoteAudioReasonLocalMuted{@link #ByteRemoteAudioReasonLocalMuted}  <br>
     *       + 远端用户停止发送音频流，对应错误码 ByteRemoteAudioReasonRemoteMuted{@link #ByteRemoteAudioReasonRemoteMuted}  <br>
     *       + 远端用户离开房间，对应错误码 ByteRemoteAudioReasonRemoteOffline{@link #ByteRemoteAudioReasonRemoteOffline}  <br>
     */
    ByteRemoteAudioStateStopped = 0,

    /**
     * @brief 本地用户已接收远端音频首包。
     *        收到远端音频首包时回调该状态，对应错误码 ByteRemoteAudioReasonLocalUnmuted{@link #ByteRemoteAudioReasonLocalUnmuted}
     */
    ByteRemoteAudioStateStarting = 1,

    /**
     * @brief  远端音频流正在解码，正常播放，在以下时机回调该状态：  <br>
     *       + 成功解码远端音频首帧，对应错误码 ByteRemoteAudioReasonLocalUnmuted{@link #ByteRemoteAudioReasonLocalUnmuted}  <br>
     *       + 网络由阻塞恢复正常，对应错误码 ByteRemoteAudioReasonNetworkRecovery{@link #ByteRemoteAudioReasonNetworkRecovery}  <br>
     *       + 本地用户恢复接收远端音频流，对应错误码 ByteRemoteAudioReasonLocalUnmuted{@link #ByteRemoteAudioReasonLocalUnmuted}  <br>
     *       + 远端用户恢复发送音频流，对应错误码 ByteRemoteAudioReasonRemoteUnmuted{@link #ByteRemoteAudioReasonRemoteUnmuted}  <br>
     */
    ByteRemoteAudioStateDecoding = 2,

    /**
     * @brief 远端音频流卡顿。
     *        网络阻塞、丢包率大于40%时回调该状态，对应错误码 ByteRemoteAudioReasonNetworkCongestion{@link #ByteRemoteAudioReasonNetworkCongestion}
     */
    ByteRemoteAudioStateFrozen = 3,

    /**
     * @brief 远端音频流播放失败
     * @notes 该错误码暂未使用
     */
    ByteRemoteAudioStateFailed = 4,
};

/**
 * @type keytype
 * @brief 远端音频流状态改变的原因。
 *        SDK 通过 rtcEngine:remoteAudioStateChanged:state:reason:elapsed:{@link #rtcEngine:remoteAudioStateChanged:state:reason:elapsed:} 回调该错误码
 */
typedef NS_ENUM(NSInteger, ByteRemoteAudioReason) {
    /**
     * @brief 内部原因
     */
    ByteRemoteAudioReasonInternal = 0,

    /**
     * @brief 网络阻塞
     */
    ByteRemoteAudioReasonNetworkCongestion = 1,

    /**
     * @brief 网络恢复正常
     */
    ByteRemoteAudioReasonNetworkRecovery = 2,

    /**
     * @brief 本地用户停止接收远端音频流
     */
    ByteRemoteAudioReasonLocalMuted = 3,

    /**
     * @brief 本地用户恢复接收远端音频流
     */
    ByteRemoteAudioReasonLocalUnmuted = 4,

    /**
     * @brief 远端用户停止发送音频流
     */
    ByteRemoteAudioReasonRemoteMuted = 5,

    /**
     * @brief 远端用户恢复发送音频流
     */
    ByteRemoteAudioReasonRemoteUnmuted = 6,

    /**
     * @brief 远端用户离开房间
     */
    ByteRemoteAudioReasonRemoteOffline = 7,
};

/**
 *  @type keytype
 *  @brief 远端视频流状态
 */
typedef NS_ENUM(NSInteger, ByteRemoteVideoState) {
    /**
     * @brief  远端视频流默认初始状态, 在以下时机回调该状态：  <br>
     *       + 本地用户停止接收远端视频流，对应错误码 ByteRemoteVideoReasonLocalMuted{@link #ByteRemoteVideoReasonLocalMuted}  <br>
     *       + 远端用户停止发送视频流，对应错误码 ByteRemoteVideoReasonRemoteMuted{@link #ByteRemoteVideoReasonRemoteMuted}  <br>
     *       + 远端用户离开房间，对应错误码 ByteRemoteVideoReasonRemoteOffline{@link #ByteRemoteVideoReasonRemoteOffline}  <br>
     */
    ByteRemoteVideoStateStopped = 0,
    /**
     * @brief 本地用户已接收远端视频首包
     *        收到远端视频首包时回调该状态，对应错误码 ByteRemoteVideoReasonLocalUnmuted{@link #ByteRemoteVideoReasonLocalUnmuted}
     */
    ByteRemoteVideoStateStarting = 1,
    /**
     * @brief  远端视频流正在解码，正常播放, 在以下时机回调该状态：  <br>
     *       + 成功解码远端视频首帧，对应错误码 ByteRemoteVideoReasonLocalUnmuted{@link #ByteRemoteVideoReasonLocalUnmuted}  <br>
     *       + 网络由阻塞恢复正常，对应错误码 ByteRemoteVideoReasonNetworkRecovery{@link #ByteRemoteVideoReasonNetworkRecovery}  <br>
     *       + 本地用户恢复接收远端视频流，对应错误码 ByteRemoteVideoReasonLocalUnmuted{@link #ByteRemoteVideoReasonLocalUnmuted}  <br>
     *       + 远端用户恢复发送视频流，对应错误码 ByteRemoteVideoReasonRemoteUnmuted{@link #ByteRemoteVideoReasonRemoteUnmuted}  <br>
     */
    ByteRemoteVideoStateDecoding = 2,
    /**
     * @brief 远端视频流卡顿
     *        网络阻塞、丢包率等原因造成视频卡顿流时会回报该状态，对应错误码 ByteRemoteVideoReasonNetworkCongestion{@link #ByteRemoteVideoReasonNetworkCongestion}
     */
    ByteRemoteVideoStateFrozen = 3,
     /**
      * @brief 远端音频流播放失败
      * @notes 如果内部处理远端视频流失败，则会回调该方法， 对应错误码 ByteRemoteVideoReasonInternal{@link #ByteRemoteVideoReasonInternal}
      */
    ByteRemoteVideoStateFailed = 4,
};

/**
 *  @type keytype
 *  @brief 远端视频流状态改变的原因
 */
typedef NS_ENUM(NSInteger, ByteRemoteVideoReason) {
    /**
     * @brief 内部原因
     */
    ByteRemoteVideoReasonInternal = 0,
    /**
     * @brief 网络阻塞
     */
    ByteRemoteVideoReasonNetworkCongestion = 1,
    /**
     * @brief 网络恢复正常
     */
    ByteRemoteVideoReasonNetworkRecovery = 2,
    /**
     * @brief 本地用户停止接收远端视频流或本地用户禁用视频模块
     */
    ByteRemoteVideoReasonLocalMuted = 3,
    /**
     * @brief 本地用户恢复接收远端视频流或本地用户启用视频模块
     */
    ByteRemoteVideoReasonLocalUnmuted = 4,
    /**
     * @brief 远端用户停止发送视频流或远端用户禁用视频模块
     */
    ByteRemoteVideoReasonRemoteMuted = 5,
    /**
     * @brief 远端用户恢复发送视频流或远端用户启用视频模块
     */
    ByteRemoteVideoReasonRemoteUnmuted = 6,
    /**
     * @brief 远端用户离开频道
     */
    ByteRemoteVideoReasonRemoteOffline = 7,
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
 *  @type keytype
 *  @brief 设备类型
 */
typedef NS_ENUM(NSInteger, ByteMediaDeviceType) {
   /**
    * @brief 音频播放设备类型
    */
   kByteAudioPlayoutDevice = 0,
   /**
    * @brief 音频录制设备类型
    */
   kByteAudioRecordingDevice = 1,
   /**
    *@brief 视频渲染设备类型，该类型暂无使用
    */
   kByteVideoRenderDevice = 2,
   /**
    *@brief 视频采集设备类型
    */
   kByteVideoCaptureDevice = 3
};

/**
 *  @type keytype
 *  @brief 设备状态
 */
typedef NS_ENUM(NSInteger, ByteMediaDeviceState) {
   /**
    *@brief 设备已开启
    */
   kByteMediaDeviceStateStarted = 0,
   /**
    *@brief 设备开启失败
    */
   kByteMediaDeviceStateStartFailed = 1,
   /**
    *@brief 设备已停止
    */
   kByteMediaDeviceStateStopped = 2,
   /**
    *@brief 设备停止失败
    */
   kByteMediaDeviceStateStopFailed = 3
};

/**
 *  @type keytype
 *  @brief 音视频质量反馈问题类型
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
 * @brief 背景模式
 *      开启背景替换功能时生效，详见 replaceBackground:withDivideModel:{@link #replaceBackground:withDivideModel:}。
 */
typedef NS_ENUM(NSUInteger, BackgroundMode) {
    /**
     * @brief 背景1
     */
    BACKGROUND_A = 0,
    /**
     * @brief 背景2
     */
    BACKGROUND_B = 1,
    /**
     * @brief 虚化
     */
    BLUR = 2,
    /**
     * @brief 无
     */
    NONE = 3,
};

/**
 * @type keytype
 * @brief 分割模型
 *      开启背景替换功能时生效，详见 replaceBackground:withDivideModel:{@link #replaceBackground:withDivideModel:}。
 */
typedef NS_ENUM(NSUInteger, DivideModel) {
    /**
     * @brief effect
     */
    EFFECT = 0,
    /**
     * @brief 自研
     */
    DEFAULT = 1,
};

/**
 * @type keytype
 * @region 房间管理
 * @brief 首帧发送状态
 */
typedef NS_ENUM(NSUInteger, FirstFrameSendState) {
    /**
     * 发送中
     */
    kFirstFrameSendStateSending = 0,
    /**
     * 发送成功
     */
    kFirstFrameSendStateSent = 1,
    /**
     * 发送失败
     */
    kFirstFrameSendStateEnd = 2,
};

/**
 * @type keytype
 * @region 房间管理
 * @brief 首帧播放状态
 */
typedef NS_ENUM(NSUInteger, FirstFramePlayState) {
    /**
     * 播放中
     */
    kFirstFramePlayStatePlaying = 0,
    /**
     * 播放成功
     */
    kFirstFramePlayStatePlay = 1,
    /**
     * 播放失败
     */
    kFirstFramePlayStateEnd = 2,
};

/**
 * @type keytype
 * @region 加密
 * @brief 加密类型  <br>
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

#define BYTE_RTC_EXPORT __attribute__((visibility("default")))
/**
 *  @type keytype
 *  @brief 视频渲染图层结构。app 通过该结构将要渲染的窗口和视频流进行绑定
 */
BYTE_RTC_EXPORT @interface ByteRtcVideoCanvas : NSObject
/**
 *  @brief 渲染窗口句柄
 */
@property (strong, nonatomic) UIView* _Nullable view;
/**
 *  @brief 设置渲染模式，暂时设置无效
 */
@property (assign, nonatomic) ByteRtcRenderMode renderMode;
/**
 *  @brief 房间ID
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
 *  @brief 视频拉伸模式，详见类型ByteVideoStreamScaleMode{@link #ByteVideoStreamScaleMode}
*/
@property (nonatomic, assign) ByteVideoStreamScaleMode mode;

/**
 *  @brief 视频编码质量偏好，详见类型ByteVideoEncoderPreference{@link #ByteVideoEncoderPreference}
*/
@property (nonatomic, assign) ByteVideoEncoderPreference encoderPreference;
@end

/**
 *  @type keytype
 *  @brief 流属性。房间中的远端流的流属性。  <br>
 *         用户加入房间成功后，房间中所有已发布和未来发布的流和流的相关属性，都会通过 rtcEngine:onStreamAdd:{@link #ByteRtcEngineDelegate#rtcEngine:onStreamAdd:} 回调时间通知用户。此数据结构即为回调给用户的参数类型。  <br>
 */
BYTE_RTC_EXPORT @protocol ByteStream <NSObject>
/**
 *  @brief 用户ID 。此流的发布用户的用户ID 。  <br>
 */
@property (nonatomic, copy, readonly) NSString * userId;
/**
 *  @brief 此流是否为共享屏幕流。  <br>
 */
@property (nonatomic, assign, readonly) BOOL isScreen;
/**
 *  @brief 此流是否包括视频流。  <br>
 */
@property (nonatomic, assign, readonly) BOOL hasVideo;
/**
 *  @brief 流是否包括音频流。  <br>
 */
@property (nonatomic, assign, readonly) BOOL hasAudio;
/**
 *  @brief 视频流的分辨率信息。  <br>
 *         用户可以通过调用 setVideoProfiles{@link #ByteRtcEngineKit#setVideoProfiles:} 方法在一路流中发布多个不同分辨率的视频。此参数即为流中所有视频的分辨率等相关信息。视频流的分辨率信息，详见 VideoStreamDescription{@link #VideoStreamDescription} 类型。  <br>
 */
@property (nonatomic, copy, readonly) NSArray<VideoStreamDescription *> * videoStreamDescriptions;
@end

/**
 *  @type keytype
 *  @brief 订阅流的参数配置。用户手动订阅一路音视频流所使用的订阅配置参数。  <br>
 *         用户关闭自动订阅功能，使用手动订阅模式时，通过调用 subscribeStream:subscribeConfig:{@link #ByteRtcEngineKit#subscribeStream:subscribeConfig:} 方法订阅音视频流，调用时传入的参数即为此数据类型。  <br>
 */
BYTE_RTC_EXPORT @interface SubscribeConfig: NSObject
/**
 *  @brief 是否是屏幕流。  <br>
 *         用户通过设置此参数，订阅该远端用户发布的屏幕共享流或非屏幕共享流。 YES 为订阅屏幕共享流，NO 为订阅非屏幕共享流，默认值为 YES 。  <br>
 */
@property (nonatomic, assign) BOOL isScreen;
/**
 *  @brief 是否订阅视频。  <br>
 *         用户通过设置此参数，选择是否订阅远端流中的视频。 YES 为订阅视频，NO 为不订阅视频，默认值为 YES 。  <br>
 */
@property (nonatomic, assign) BOOL subscribeVideo;
/**
 *  @brief 是否订阅音频。  <br>
 *         用户通过设置此参数，选择是否订阅远端流中的音频。YES 为订阅音频，NO 为不订阅音频，默认值为 YES 。  <br>
 */
@property (nonatomic, assign) BOOL subscribeAudio;
/**
 *  @brief 订阅的视频流分辨率下标。  <br>
 *         用户可以通过调用 setVideoProfiles{@link #ByteRtcEngineKit#setVideoProfiles:} 方法在一路流中发布多个不同分辨率的视频。因此订阅流时，需要指定订阅的具体分辨率。此参数即用于指定需订阅的分辨率的下标，默认值为 0 。  <br>
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
 *  @brief 每个采样点占据的内存大小，s16 为 2 byte
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
typedef NS_ENUM(NSInteger, VideoFrameType) {
    /**
     * @brief 视频帧类型：内存数据
     */
    kFrameTypeRawMemory = 0,
    /**
     * @brief 视频帧类型：CVPixelBuffer
     */
    kFrameTypePixelBuffer,
};

/**
 *  @type keytype
 *  @brief 视频帧格式
 */
typedef NS_ENUM(NSInteger, VideoPixelFormat) {
    /**
     * @brief 未知格式
     */
    kPixelFormatUnknown = 0,
    /**
     * @brief I420
     */
    kPixelFormatI420 = 1,
    /**
     * @brief BGRA
     */
    kPixelFormatBGRA = 2,
    /**
     * @brief NV21
     */
    kPixelFormatNV21 = 3,
    /**
     * @brief RGBA
     */
    kPixelFormatRGBA = 4,
    /**
     * @brief IMC2
     */
    kPixelFormatIMC2 = 5,
    /**
     * @brief ARGB
     */
    kPixelFormatARGB = 7,
    /**
     * @brief NV12
     */
    kPixelFormatNV12 = 8,
    /**
     * @brief Opengl Texture2D纹理
     */
    kPixelFormatGLTexture2D = 10,
    /**
     * @brief Opengl OES纹理
     */
    kPixelFormatGLTextureOES = 11,
    /**
     * @brief CVPixelBuffer
     */
    kPixelFormatCVPixelBuffer = 12,
};

/**
 *  @type keytype
 */
BYTE_RTC_EXPORT @interface ByteVideoFrame : NSObject
/**
 *  @brief 视频帧类型，参考 VideoPixelFormat {@link #VideoPixelFormat}
 */
@property (assign, nonatomic) NSInteger format;
/**
 *  @brief 当前帧的时间戳信息
 */
@property (assign, nonatomic) CMTime time;
/**
 *  @hidden
 */
@property (assign, nonatomic) int stride DEPRECATED_MSG_ATTRIBUTE("use strideInPixels instead");
/**
 *  @brief 每一行像素占用的字节数
 */
@property (assign, nonatomic) int strideInPixels;
/**
 *  @brief 视频帧宽度
 */
@property (assign, nonatomic) int width;
/**
 *  @brief 视频帧高度
 */
@property (assign, nonatomic) int height;
/**
 *  @brief CVPixelBufferRef 类型的数据，当 format 为 kPixelFormatCVPixelBuffer 时有效
 */
@property (assign, nonatomic) CVPixelBufferRef _Nullable textureBuf;
/**
 *  @brief 视频帧内存块首地址
 */
@property (strong, nonatomic) NSData * _Nullable dataBuf;
/**
 *  @brief 视频帧左边裁剪的尺寸（像素）
 */
@property (assign, nonatomic) int cropLeft;
/**
 *  @brief 视频帧上部裁剪的尺寸（像素）
 */
@property (assign, nonatomic) int cropTop;
/**
 *  @brief 视频帧右边裁剪的尺寸（像素）
 */
@property (assign, nonatomic) int cropRight;
/**
 *  @brief 视频帧底部裁剪的尺寸（像素）
 */
@property (assign, nonatomic) int cropBottom;
/**
 *  @brief 视频帧旋转角度：0, 90, 180, 270
 */
@property (assign, nonatomic) ByteVideoRotation rotation;
/**
 *  @brief 视频帧附加的数据
 */
@property (strong, nonatomic) ByteRtcFrameExtendedData *extendedData;
@end

/**
 *  @type keytype
 *  @brief 单个视频流在合流中的布局信息。  <br>
 *         此数据类型为，开启直播推流转码功能，多路视频流合流时，其中一路视频流在合流中的预设布局信息。  <br>
 */
BYTE_RTC_EXPORT @interface ByteRtcVideoCompositingRegion : NSObject
/**
 *  @brief 用户ID 。视频流发布用户的用户ID 。  <br>
 */
@property (copy, nonatomic) NSString * _Nonnull uid;
/**
 *  @brief 用户视频布局相对画布左侧的偏移量。相对值，范围为[0.0 - 1.0]。  <br>
 */
@property (assign, nonatomic) CGFloat x;
/**
 *  @brief 用户视频布局相对画布顶端的偏移量。相对值，范围为[0.0 - 1.0]。  <br>
 */
@property (assign, nonatomic) CGFloat y;
/**
 *  @brief 用户视频宽度相对用户原始视频宽度的比例。相对值，范围为[0.0 - 1.0]。  <br>
 */
@property (assign, nonatomic) CGFloat width;
/**
 *  @brief 用户视频高度相对用户原始视频高度的比例。相对值，范围为[0.0 - 1.0]。  <br>
 */
@property (assign, nonatomic) CGFloat height;
/**
 *  @brief 用户视频布局在画布中的层级。0为底层，值越大越上层，范围为[0 - 100]。  <br>
 */
@property (assign, nonatomic) NSInteger zOrder;
/**
 *  @brief 透明度。范围为[0 - 255]。  <br>
 */
@property (assign, nonatomic) CGFloat alpha;
/**
 *  @brief 合流内容控制。默认值为 0 ，取值范围及含义如下:  <br>
 *        + 0: 输出的混流包含音视频  <br>
 *        + 1: 只包含音频  <br>
 *        + 2: 表示只包含视频  <br>
 */
@property (assign, nonatomic) NSInteger contentControl;
/**
 *  @brief 视频显示模式。详见 ByteRtcRenderMode{@link #ByteRtcRenderMode} 数据类型。  <br>
 */
@property (assign, nonatomic) ByteRtcRenderMode renderMode;
@end

/**
 *  @type keytype
 *  @brief 视频流合流整体布局信息。  <br>
 *         此数据类型为，开启直播推流转码功能，视频合流的完整信息。包括了参与合流的每路视频流的预设布局信息和合流背景信息等。  <br>
 */
BYTE_RTC_EXPORT @interface ByteRtcVideoCompositingLayout : NSObject
/**
 *  @brief 画布的背景颜色。  <br>
 */
@property (copy, nonatomic) NSString *_Nonnull backgroundColor;
/**
 *  @brief 用户布局信息列表。每条流的具体布局详见 ByteRtcVideoCompositingRegion{@link #ByteRtcVideoCompositingRegion} 数据类型。  <br>
 */
@property (copy, nonatomic) NSArray<ByteRtcVideoCompositingRegion *> * _Nonnull regions;
/**
 *  @brief 透传的 App 数据。  <br>
 */
@property (copy, nonatomic) NSString *_Nonnull appData;
@end

/**
 *  @type keytype
 *  @brief 视频转码配置参数。  <br>
 */
BYTE_RTC_EXPORT @interface ByteRtcTranscodingVideoConfig : NSObject
/**
 *  @brief 视频编码格式。  <br>
 */
@property (copy, nonatomic) NSString * _Nonnull codec;
/**
 *  @brief 合流视频宽度。  <br>
 */
@property (assign, nonatomic) NSInteger width;
/**
 *  @brief 合流视频高度。  <br>
 */
@property (assign, nonatomic) NSInteger height;
/**
 *  @brief 合流视频帧率信息。  <br>
 */
@property (assign, nonatomic) NSInteger fps;
/**
 *  @brief 视频I帧间隔。  <br>
 */
@property (assign, nonatomic) NSInteger gop;
/**
 *  @brief 合流视频码率，单位为 kbps 。  <br>
 */
@property (assign, nonatomic) NSInteger kBitRate;
/**
 *  @brief 是否使用低延时特性。  <br>
 */
@property (assign, nonatomic) BOOL lowLatency;
@end

/**
 *  @type keytype
 *  @brief AAC编码类型。  <br>
 */
typedef NS_ENUM(NSInteger, ByteAACProfile) {
    /**
    *  @brief LC（默认）  <br>
    */
    ByteAACProfileLC   = 0,
    /**
    *  @brief MAIN  <br>
    */
    ByteAACProfileMain = 1,
    /**
    *  @brief HEv1  <br>
    */
    ByteAACProfileHEv1 = 2,
    /**
    *  @brief HEv2  <br>
    */
    ByteAACProfileHEv2 = 3,
};

/**
 *  @type keytype
 *  @brief 音频转码配置参数。
 */
BYTE_RTC_EXPORT @interface ByteRtcTranscodingAudioConfig : NSObject
/**
 *  @brief 音频编码格式。  <br>
 */
@property (copy, nonatomic) NSString * _Nonnull codec;
/**
 *  @brief 音频采样率。单位为 kHz。可选取值：16, 32, 44.1, 48。  <br>
 */
@property (assign, nonatomic) NSInteger sampleRate;
/**
 *  @brief 声道数。  <br>
 */
@property (assign, nonatomic) NSInteger channels;
/**
 *  @brief 音频码率。单位为 kbps。可选取值：16, 32, 64。  <br>
 */
@property (assign, nonatomic) NSInteger kBitRate;
/**
 *  @brief AAC 等级。  <br>
 */
@property (assign, nonatomic) ByteAACProfile profile;
/**
 *  @hidden
 */
+ (NSString* _Nonnull) toStringWithProfile:(ByteAACProfile) aacProfile;
@end

/**
 *  @type keytype
 *  @brief 直播推流转码配置参数。  <br>
 *         用户调用 enableLiveTranscoding:{@link #ByteRtcEngineKit#enableLiveTranscoding:} 方法开启直播推流转码功能时，传入的合流转码配置参数。  <br>
 */
BYTE_RTC_EXPORT @interface ByteRtcLiveTranscoding : NSObject
/**
 *  @brief 视频合流布局信息。详见 ByteRtcVideoCompositingLayout{@link #ByteRtcVideoCompositingLayout} 数据类型。  <br>
 */
@property (strong, nonatomic) ByteRtcVideoCompositingLayout * _Nonnull layout;
/**
 *  @brief 视频转码参数。详见 ByteRtcTranscodingVideoConfig{@link #ByteRtcTranscodingVideoConfig} 数据类型。  <br>
 */
@property (strong, nonatomic) ByteRtcTranscodingVideoConfig * _Nonnull video;
/**
 *  @brief 音频转码参数。详见 ByteRtcTranscodingAudioConfig{@link #ByteRtcTranscodingAudioConfig} 数据类型。  <br>
 */
@property (strong, nonatomic) ByteRtcTranscodingAudioConfig * _Nonnull audio;
/**
 *  @brief 动态扩展自定义参数。  <br>
 */
@property (strong, nonatomic) NSMutableDictionary *  _Nullable advancedConfig;
/**
 *  @brief 推流 CDN 地址。  <br>
 */
@property (copy, nonatomic) NSString * _Nullable url;
/**
 *  @brief 获取默认合流参数。  <br>
 */
+ (instancetype _Nonnull)defaultTranscoding;
@end

/**
 * @type keytype
 * @brief 房间通话统计数据。  <br>
 *        用户加入当前房间成功后，SDK 会周期性（2s）的通过rtcEngine:reportRtcStats:{@link #ByteRtcEngineDelegate#rtcEngine:reportRtcStats:}回调事件通知用户当前房间内的汇总统计信息。回调的统计信息即为此数据类型。  <br>
 */
BYTE_RTC_EXPORT @interface ByteRtcStats : NSObject
/**
 * @brief 用户在房间中的总时长。单位为 s 。  <br>
 */
@property (assign, nonatomic) NSInteger duration;
/**
 * @brief 用户在通话过程中发送媒体数据总量。单位为 bytes 。  <br>
 */
@property (assign, nonatomic) NSInteger txBytes;
/**
 * @brief 用户在通话过程中接收媒体数据总量。单位为 bytes 。  <br>
 */
@property (assign, nonatomic) NSInteger rxBytes;
/**
 * @brief 发送音频码率。此次统计周期内总发送音频码率，单位为 kbps 。  <br>
 */
@property (assign, nonatomic) NSInteger txAudioKBitrate;
/**
 * @brief 接收音频码率。此次统计周期内总接收音频码率，单位为 kbps 。  <br>
 */
@property (assign, nonatomic) NSInteger rxAudioKBitrate;
/**
 * @brief 发送视频码率。此次统计周期内总发送视频码率，单位为 kbps 。  <br>
 */
@property (assign, nonatomic) NSInteger txVideoKBitrate;
/**
 * @brief 接收视频码率。此次统计周期内总接收视频码率，单位为 kbps 。  <br>
 */
@property (assign, nonatomic) NSInteger rxVideoKBitrate;
/**
 * @brief 当前房间内用户总数。回调时房间内的用户总数，包括本地用户自身。  <br>
 */
@property (assign, nonatomic) NSInteger userCount;
/**
 * @brief 当前 App 的 CPU 使用率
 */
//@property (assign, nonatomic) double cpuAppUsage;
/**
 * @brief 当前设备的总 CPU 使用率
 */
//@property (assign, nonatomic) double cpuTotalUsage;
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
/**
 * @brief 是否是屏幕流。
 */
@property (assign, nonatomic) BOOL isScreen;
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
 * @brief 音量信息所属用户的用户ID
 */
@property (copy, nonatomic) NSString * _Nonnull uid;
/**
 * @brief 用户音量大小信息，音量取值范围为 [0, 255]
 */
@property (assign, nonatomic) NSUInteger volume;
@end

/**
 * @hidden
 * @type keytype
 * @brief 网络质量。
 */
BYTE_RTC_EXPORT @interface ByteRtcNetworkQuality : NSObject
/**
 * @hidden
 * @brief 网络状况信息所属用户的用户 ID 。
 */
@property (nonatomic, strong) NSString * _Nonnull uid;
/**
 * @hidden
 * @brief 该用户的上行网络状态。类型含义详见 ByteNetworkQuality{@link #ByteNetworkQuality} 。
 */
@property (nonatomic) ByteNetworkQuality txQuality;
/**
 * @hidden
 * @brief 该用户的下行网络状态。类型含义详见 ByteNetworkQuality{@link #ByteNetworkQuality} 。
 */
@property (nonatomic) ByteNetworkQuality rxQuality;
@end

/**
 *  @type keytype
 *  @brief 性能回退相关数据
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
 *  @type api
 *  @brief 远端用户流切换的信息
 */
BYTE_RTC_EXPORT @interface ByteRemoteStreamSwitchEvent : NSObject
/**
 *@brief 远端用户ID
 */
@property (nonatomic, copy) NSString * _Nonnull uid;
/**
 *@brief 流是否是屏幕流
 */
@property (nonatomic, assign) BOOL isScreen;
/**
 *@brief 流切换前订阅视频流的分辨率对应的索引
 */
@property (nonatomic, assign) NSInteger beforeVideoIndex;
/**
 *@brief 流切换后订阅视频流的分辨率对应的索引
 */
@property (nonatomic, assign) NSInteger afterVideoIndex;
/**
 *@brief 流切换前是否有视频流
 */
@property (nonatomic, assign) BOOL beforeVideoEnabled;
/**
 *@brief 流切换后是否有视频流
 */
@property (nonatomic, assign) BOOL afterVideoEnabled;
/**
 *@brief 流切换原因
 */
@property (nonatomic, assign) ByteFallbackOrRecoverReason reason;
@end

/**
 *  @type callback
 *  @brief 自定义的视频渲染
 */
BYTE_RTC_EXPORT @protocol ByteVideoSinkProtocol <NSObject>
@required
/**
 *  @brief 初始化渲染器
 *  @return  <br>
 *         + YES: 自定义的渲染器初始化完成  <br>
 *         + NO: 自定义的渲染器初始化失败，不继续往下运行  <br>
 *  @notes 初始化渲染器的时候会回调这个方法
 */
- (BOOL)shouldInitialize;

/**
 *  @brief 启动渲染器
 *  @notes 在开启渲染功能的时候会回调这个方法
 */
- (void)shouldStart;

/**
 *  @brief 停止渲染器
 *  @notes 在停止渲染功能的时候会回调这个方法
 */
- (void)shouldStop;

/**
 *  @brief 释放渲染器
 *  @notes 渲染器即将被废弃的时候会回调这个方法
 */
- (void)shouldDispose;

/**
 *  @brief 获取PixelFormat格式
 *  @return Buffer 类型，{@link #ByteVideoPixelFormat}
 *  @notes 通过该方法的返回值，告知 SDK PixelFormat 的格式
 */
- (ByteVideoPixelFormat)pixelFormat;

/**
 *  @brief 输出视频的 PixelBuffer
 *  @param pixelBuffer 视频的 PixelBuffer
 *  @param rotation 视频旋转角度，{@link #ByteVideoRotation}
 *  @param extendedData 视频帧附加的数据,视频解码后获得的附加数据
 *  @notes 通过该方法获取视频的 PixelBuffer
 */
- (void)renderPixelBuffer:(CVPixelBufferRef _Nonnull)pixelBuffer
                 rotation:(ByteVideoRotation)rotation
             extendedData:(NSData * _Nullable)extendedData;
@end

/**
 *  @hidden
 *  @type callback
 *  @brief 外部渲染数据的消费接口
 */
@protocol ByteVideoFrameConsumerObserver <NSObject>
/**
 *  @brief 输出 yuv420 数据
 *  @param ocFrame 数据 Buffer
 *  @param width 视频宽度
 *  @param rotation 视频旋转角度
 *  @param timestamp 时间戳
 */
- (void)consumeYUV420Buffer:(CVPixelBufferRef _Nullable)ocFrame width:(NSInteger)width rotation:(NSInteger)rotation timestamp:(long)timestamp;
/**
 *  @brief 输出 RGBA 数据
 *  @param pixelBuffer 数据 Buffer
 *  @param width 视频宽度
 *  @param rotation 视频旋转角度
 *  @param timestamp 时间戳
 */
- (void)consumeRGBABuffer:(CVPixelBufferRef _Nullable)ocFrame width:(NSInteger)width rotation:(NSInteger)rotation timestamp:(long)timestamp;
@end

/**
*  @type callback
*  @region 视频管理
*/
BYTE_RTC_EXPORT @protocol ByteVideoFrameObserver <NSObject>
/**
 *  @brief 本地屏幕流的视频帧数据回调
 *  @param frame 本地屏幕视频帧数据，参考: ByteVideoFrame{@link #ByteVideoFrame}
 */
- (void)onLocalScreenFrame:(ByteVideoFrame * _Nonnull)frame;
/**
 *  @brief 本地视频流的视频帧数据回调
 *  @param frame 本地视频流的视频帧数据，参考: ByteVideoFrame{@link #ByteVideoFrame}
 */
- (void)onLocalVideoFrame:(ByteVideoFrame * _Nonnull)frame;

/**
 *  @brief 远端屏幕流的视频帧数据回调
 *  @param frame 远端屏幕的视频帧数据，参考: ByteVideoFrame{@link #ByteVideoFrame}
 *  @param uid 远端屏幕共享用户ID
 *  @param room 对应流的房间 id
 */
- (void)onRemoteScreenFrame:(ByteVideoFrame * _Nonnull)frame user:(NSString * _Nullable)uid room:(NSString * _Nullable)room;
/**
 *  @brief 远端视频流的视频帧数据回调
 *  @param frame 远端视频流的视频帧数据，参考: ByteVideoFrame{@link #ByteVideoFrame}
 *  @param uid 远端屏幕共享用户ID
 *  @param room 对应流的房间 id
 */
- (void)onRemoteVideoFrame:(ByteVideoFrame * _Nonnull)frame user:(NSString * _Nullable)uid room:(NSString * _Nullable)room;

@end

/**
 *  @type keytype
 *  @brief 流信息
*/
@interface ByteRtcStreamOC : NSObject <ByteStream>
/**
 *  @brief 用户ID
*/
@property (nonatomic, copy, nullable) NSString *userId;
/**
 *  @brief 流是否为共享屏幕流。
 */
@property (nonatomic, assign) BOOL isScreen;
/**
 *  @brief 该路流中是否包含视频
*/
@property (nonatomic, assign) BOOL hasVideo;
/**
 *  @brief 该路流中是否包含音频
*/
@property (nonatomic, assign) BOOL hasAudio;
/**
 *  @brief 视频流的分辨率信息，详见 VideoStreamDescription{@link #VideoStreamDescription} 类。
 *         用户可以通过调用 setVideoProfiles{@link #setVideoProfiles:} 方法在一路流中发布多个不同的视频分辨率。此参数即为流中所有分辨率的相关信息。
 */
@property (nonatomic, copy, nullable) NSArray<VideoStreamDescription *> *videoStreamDescriptions;
@end

/**
 *  @type keytype
 *  @region 视频管理
 *  @brief 屏幕采集设置参数
 */
BYTE_RTC_EXPORT @interface ScreenCaptureParam : NSObject
/**
 *  @brief 屏幕采集宽度
 */
@property (nonatomic, assign) NSInteger width;
/**
 *  @brief 屏幕采集高度
 */
@property (nonatomic, assign) NSInteger height;
/**
 *  @brief 屏幕采集帧率，单位 fps
 */
@property (nonatomic, assign) NSInteger frameRate;
/**
 *  @brief 发送屏幕采集码率，单位 kbps
 */
@property (nonatomic, assign) NSInteger bitrate;
/**
 *  @brief 是否采集鼠标
 */
@property (nonatomic, assign) BOOL captureMouseCursor;
@end

/**
 *  @type keytype
 *  @region 视频管理
 *  @brief 屏幕采集设置参数
 */
BYTE_RTC_EXPORT @interface ScreenParam : NSObject
/**
 * @brief 编码帧率,单位为 fps
 */
@property (nonatomic, assign) NSInteger frameRate;
/**
 * @brief 编码码率，小于 0 时 SDK 会根据高宽自适应码率, 单位 kbps
 */
@property (nonatomic, assign) NSInteger bitrate;
@end

/**
 * @type keytype
 * @region 房间管理
 * @brief 用户信息
 */
BYTE_RTC_EXPORT @interface ByteRtcUser : NSObject
/**
 * @brief 用户 id
 */
@property (nonatomic, copy, nullable) NSString *userId;
/**
 * @brief 元信息
 */
@property (nonatomic, copy, nullable) NSString *metaData;
@end

#endif /* Header_h */
