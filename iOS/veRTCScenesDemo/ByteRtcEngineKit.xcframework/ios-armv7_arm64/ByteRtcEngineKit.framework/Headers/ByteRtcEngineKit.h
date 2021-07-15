//
//  RtcEngineKit.h
//  RtcEngineKit
//
//  Created by gaosiyu on 2018/2/28.
//  Copyright © 2018年 gaosiyu. All rights reserved.
//
#import <CoreMedia/CMTime.h>
#import <UIKit/UIKit.h>
#import "ByteRtcEngineKitDefines.h"
#import "ByteRtcHttpClientProtocol.h"

@class ByteRtcEngineKit;
@class ByteRtcRoom;
/**
 *  @type api
 */
@protocol ByteRtcHttpClientProtocol;

#pragma mark - ByteRtcEngineDelegate
/**
 * @type callback
 * ByteRtcEngineDelegate 协议包含了SDK提供的回调方法，SDK通过代理向应用程序上报一些运行时事件
 */
@protocol ByteRtcEngineDelegate <NSObject>
@optional

#pragma mark - Core Delegate Methods
/**
 *  -----------------------------------------------------------------------------
 *  @name 核心事件回调
 *  -----------------------------------------------------------------------------
 */

/**
 * @type callback
 * @region 警告码
 * @brief 发生警告回调。
 * @notes 该回调方法表示SDK运行时出现了（网络或媒体相关的）警告。通常情况下，SDK 上报的警告信息 App 可以忽略，SDK 会自动恢复。
 * @param engine 当前 RTCEngine 对象
 * @param Code 警告代码，详情定义见: ByteRtcWarningCode{@link #ByteRtcWarningCode}
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine didOccurWarning:(ByteRtcWarningCode)Code;

/**
 * @type callback
 * @region 错误码
 * @brief 发生错误回调。
 * @notes 表示SDK运行时出现了（网络或媒体相关的）错误。通常情况下，SDK 上报的错误意味着 SDK 无法自动恢复，需要 App 干预或提示用户。
 * @param engine 当前 RTCEngine 对象
 * @param errorCode 错误代码，详情定义见: ByteRtcErrorCode{@link #ByteRtcErrorCode}
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine didOccurError:(ByteRtcErrorCode)errorCode;

/**
 * @type callback
 * @region 引擎管理
 * @brief SDK 与 RTC 服务器的网络连接状态改变时，会收到此回调。
 * @param [in] engine 当前 RTCEngine 实例。
 * @param [in] state 发生改变后的连接状态，参看 ByteRtcConnectionState{@link #ByteRtcConnectionState} 。
 */
- (void) rtcEngine:(ByteRtcEngineKit * _Nonnull)engine connectionChangedToState:(ByteRtcConnectionState) state;


/**
 * @type callback
 * @region 引擎管理
 * @brief SDK 当前网络连接类型改变回调。当 SDK 的当前网络连接类型发生改变时回调该事件。
 * @param engine  <br>
 *        当前 RTCEngine 实例。
 * @param type  <br>
 *        SDK 当前的网络连接类型，详见：ByteRtcNetworkType{@link #ByteRtcNetworkType} 。
 */
- (void) rtcEngine:(ByteRtcEngineKit * _Nonnull)engine networkTypeChangedToType:(ByteRtcNetworkType) type;

/**
 *  @type callback
 *  @region 房间管理
 *  @brief 加入房间成功回调。此回调事件表示本地用户成功加入了指定的房间。  <br>
 *         用户调用 joinChannelByKey:channelName:info:uid:{@link #ByteRtcEngineKit#joinChannelByKey:channelName:info:uid:} 方法加入房间，首次加入房间成功后 SDK 通过此回调事件通知用户加入房间成功。此回调事件在用户调用 joinChannelByKey:channelName:info:uid:{@link #ByteRtcEngineKit#joinChannelByKey:channelName:info:uid:} 方法加入房间到用户调用 leaveChannel:{@link #leaveChannel:} 方法离开房间期间至多回调一次。  <br>
 *  @param engine ByteRtcEngineKit 对象。  <br>
 *  @param channel 房间ID 。本地用户加入的房间的房间 ID 。  <br>
 *  @param uid 用户ID 。本地用户的用户ID 。  <br>
 *  @param elapsed 加入房间耗时。本地用户从调用 joinChannelByKey:channelName:info:uid:{@link #ByteRtcEngineKit#joinChannelByKey:channelName:info:uid:} 方法到加入房间成功所经历的时间间隔，单位为 ms 。  <br>
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine didJoinChannel:(NSString * _Nonnull)channel withUid:(nonnull NSString*)uid elapsed:(NSInteger) elapsed;

/**
 *  @type callback
 *  @region 房间管理
 *  @brief 重新加入房间成功回调。此回调事件表示本地用户成功重连入房间。  <br>
 *         本地用户加入房间成功后，在本地网络状况不佳的情况下，SDK 可能会与服务器失去连接。此时 SDK 将会自动重连，并在重连成功通过此回调事件通知用户重连成功。  <br>
 *  @param engine ByteRtcEngineKit 对象。  <br>
 *  @param channel 房间ID 。本地用户加入的房间的房间ID 。  <br>
 *  @param uid 用户ID 。本地用户的用户ID 。  <br>
 *  @param elapsed 重连耗时。本地用户从连接断开到重连成功所经历的时间间隔，单位为 ms 。  <br>
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine didRejoinChannel:(NSString * _Nonnull)channel withUid:(nonnull NSString*)uid elapsed:(NSInteger) elapsed;

/**
 *  @type callback
 *  @region 房间管理
 *  @brief 远端用户加入房间回调。  <br>
 *         此回调用于提示房间中有新用户加入。如果本地用户已经在房间中，有新的远端用户加入时，SDK 通过此回调方法通知房间中有新用户加入；如果用户加入房间前，房间中已有其他用户，加入房间后用户也会收到这些已在房间中的远端用户的加入房间回调。  <br>
 *         回调的具体触发时机如下：  <br>
 *         1.远端的房间模式为通信模式的用户或房间模式为其他模式的主播、观众角色的用户，调用 joinChannelByKey:channelName:info:uid:{@link #ByteRtcEngineKit#joinChannelByKey:channelName:info:uid:} 方法加入房间。  <br>
 *         2.远端的房间模式为通信模式的用户或房间模式为其他模式的主播、观众角色的用户，在断网后重连入房间。  <br>
 *         3.远端已在房间中的房间模式为直播、游戏或云游戏模式的静默观众角色的用户，调用 setClientRole:{@link #setClientRole:} 方法将用户角色切换至主播或观众。  <br>
 *         4.本地用户加入房间时，会收到已在房间中的远端的房间模式为通信模式的用户或房间模式为其他模式的主播、观众角色的用户的加入房间回调。  <br>
 *  @param engine ByteRtcEngineKit 对象。  <br>
 *  @param uid 用户ID 。新加入的远端用户的用户ID 。  <br>
 *  @param elapsed 本地用户调用 joinChannelByKey:channelName:info:uid:{@link #ByteRtcEngineKit#joinChannelByKey:channelName:info:uid:} 加入房间到收到该事件经历的时间，单位为 ms 。  <br>
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine didJoinedOfUid:(nonnull NSString*)uid elapsed:(NSInteger)elapsed;

/**
 *  @type callback
 *  @region 房间管理
 *  @brief 远端用户离开房间回调。  <br>
 *         此回调用于提示房间中有远端用户离开。用户离开房间的原因有两个，即用户主动调用 leaveChannel:{@link #leaveChannel:} 方法离开房间和超时掉线。  <br>
 *         回调的具体触发时机如下：  <br>
 *         1.远端的房间模式为通信模式的用户或房间模式为其他模式的主播、观众角色的用户，调用 leaveChannel:{@link #leaveChannel:} 方法离开房间。用户离开的原因为 ByteRtc_UserOffline_Quit{@link #ByteRtc_UserOffline_Quit}。  <br>
 *         2.远端已在房间中的房间模式为直播、游戏或云游戏模式的主播、观众角色的用户调用 setClientRole:{@link #setClientRole:} 方法将用户角色切换至静默观众。用户离开的原因为 ByteRtc_UserOffline_Quit{@link #ByteRtc_UserOffline_Quit}。  <br>
 *         3.远端的房间模式为通信模式的用户或房间模式为其他模式的主播、观众角色的用户，断网且一直未恢复。用户离开的原因为 ByteRtc_UserOffline_Dropped{@link #ByteRtc_UserOffline_Dropped}。  <br>
 *  @param engine ByteRtcEngineKit 对象。  <br>
 *  @param uid 用户ID 。离开房间的远端用户的用户ID 。  <br>
 *  @param reason 用户离开的原因，详见枚举类型 ByteRtcUserOfflineReason{@link #ByteRtcUserOfflineReason} 。  <br>
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine didOfflineOfUid:(NSString* _Nonnull )uid reason:(ByteRtcUserOfflineReason)reason;

/**
 *  @hidden
 *  @type callback
 *  @region 频道管理
 *  @brief 发布成功回调。调用 joinChannelByKey:channelName:info:uid:{@link #ByteRtcEngineKit#joinChannelByKey:channelName:info:uid:}  成功后，如果用户为主播角色，会发布本地音/视频流。服务器通知SDK发布过程成功时，回调此事件。
 *   @param engine 当前RTC SDK对象
 *   @param userId 流发布用户的用户ID
 *   @param isScreen 发布成功的流是否是屏幕流
 */
- (void)rtcEngine:(ByteRtcEngineKit *_Nonnull)engine didPublishSucceedOfStream:(NSString *_Nonnull)userId isScreen:(BOOL)isScreen;

#pragma mark - Core Audio Delegate Methods
/**
 *  -----------------------------------------------------------------------------
 *  @name 核心音频事件回调
 *  -----------------------------------------------------------------------------
 */

/**
 * @hidden
 * @type callback
 * @region 音频事件回调
 * @brief  远端用户静音/取消静音所有远端音频流时回调。  <br>
 *       + 提示该远端用户对房间内其他所有用户静音/取消静音了音频流。  <br>
 *       + 该回调由远端用户调用 muteAllRemoteAudioStreams:{@link #muteAllRemoteAudioStreams:} 触发
 * @param uid 远端用户ID
 * @param muted  YES: 该用户静音所有远端音频流；NO: 该用户取消静音了所有远端音频流
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine didAllRemoteAudioMuted:(BOOL)muted byUid:(NSString * _Nonnull)uid;

/**
 *  @hidden
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine didAllRemoteVideoMuted:(BOOL)muted byUid:(NSString * _Nonnull)uid;

/**
 * @type callback
 * @region 音频事件回调
 * @brief 远端用户将其本地音频流静音时，房间内其他人会收到这个回调。
 *        该回调由远端用户调用 muteLocalAudioStream{@link #muteLocalAudioStream:} 方法触发。
 * @param engine ByteRtcEngineKit对象
 * @param muted  该用户是否已将其本地音频流静音  <br>
 *             + YES: 该用户已将其本地音频流静音  <br>
 *             + NO: 该用户已将其本地音频流取消了静音
 * @param uid 远端用户 ID
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine didAudioMuted:(BOOL)muted byUid:(NSString * _Nonnull)uid;

/**
 *  @type callback
 *  @region 音频事件回调
 *  @brief 远端用户开启/关闭音频设备采集回调
 *         提示有远端用户已开启/关闭音频设备采集，该回调由远端用户调用 enableLocalAudio:{@link #enableLocalAudio:} 方法触发
 *  @param engine ByteRtcEngineKit对象
 *  @param enabled YES: 该用户开启了音频设备采集；NO: 该用户关闭了音频设备采集
 *  @param uid 远端用户ID
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine didLocalAudioEnabled:(BOOL)enabled byUid:(NSString * _Nonnull)uid;

/**
 *  @type callback
 *  @region 音频事件回调
 *  @brief 当收到远端流的第一帧音频的时候上报该事件
 *  @param engine ByteRtcEngineKit 对象
 *  @param uid 远端用户ID
 *  @param elapsed 从开始订阅音频流到收到该事件经历的时间（毫秒单位）
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine firstRemoteAudioFrameOfUid:(NSString * _Nonnull)uid elapsed:(NSInteger)elapsed;

/**
 * @type callback
 * @region 音频事件回调
 * @brief 通话音量提示的回调。回调当前房间内每个用户的音量、总音量。
 * @param engine RtcEngine 实例
 * @param speakers 房间内用户的音量信息的数组，每个用户音量信息详见类型 ByteRtcAudioVolumeInfo{@link #ByteRtcAudioVolumeInfo}，包括发送流与接收流
 * @param totalVolume 房间内的总音量大小，只包括接收流
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine reportAudioVolumeIndicationOfSpeakers:(NSArray<ByteRtcAudioVolumeInfo *> * _Nonnull)speakers totalVolume:(NSInteger)totalVolume;

#pragma mark - Core Video Delegate Methods
/**
 *  -----------------------------------------------------------------------------
 *  @name 核心视频事件回调
 *  -----------------------------------------------------------------------------
 */

/**
 *  @type callback
 *  @region 视频管理
 *  @brief 远端用户暂停/重新发送视频回调。房间中远端用户调用 muteLocalVideoStream:{@link #muteLocalVideoStream:} 时，本地用户将会收到该回调。
 *  @param engine ByteRtcEngineKit 对象
 *  @param muted YES:远端用户恢复发送视频流；NO:远端用户暂停发送视频流
 *  @param uid 调用 muteLocalVideoStream:{@link #muteLocalVideoStream:} 接口的远端用户ID
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine didVideoMuted:(BOOL)muted byUid:(NSString * _Nonnull)uid;

/**
 *  @type callback
 *  @region 视频管理
 *  @brief 远端用户启用/关闭本地视频回调。房间中远端用户调用 enableLocalVideo:{@link #enableLocalVideo:} 时，本地用户将会收到该回调。
 *  @param engine ByteRtcEngineKit 对象
 *  @param enabled YES: 远端用户启动了本地视频；NO: 远端用户关闭了本地视频
 *  @param uid 调用 enableLocalVideo:{@link #enableLocalVideo:} 接口的远端用户ID
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine didLocalVideoEnabled:(BOOL)enabled byUid:(NSString * _Nonnull)uid;

/**
 *  @type callback
 *  @region 视频管理
 *  @brief 本地首帧视频数据渲染事件回调。调用 joinChannelByKey:channelName:info:uid:{@link #ByteRtcEngineKit#joinChannelByKey:channelName:info:uid:} 后，渲染本地首帧视频数据前的事件。
 *  @param engine ByteRtcEngineKit 对象
 *  @param size 视频的宽高尺寸
 *  @param elapsed 从调用 joinChannelByKey:channelName:info:uid:{@link #ByteRtcEngineKit#joinChannelByKey:channelName:info:uid:} 到渲染本地首帧视频数据前的总耗时(ms)
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine firstLocalVideoFrameWithSize:(CGSize)size elapsed:(NSInteger)elapsed;

/**
 *  @type callback
 *  @region 视频管理
 *  @brief 远端首帧视频数据渲染事件回调。
 *  @param engine ByteRtcEngineKit 对象
 *  @param uid 发送当前帧的远端用户的用户ID
 *  @param size 视频的宽高尺寸
 *  @param elapsed 从开始订阅远端流到开始渲染远端首帧视频数据事件的总耗时(ms)
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine firstRemoteVideoFrameOfUid:(NSString* _Nonnull )uid size:(CGSize)size elapsed:(NSInteger)elapsed;

/**
 *  @type callback
 *  @region 视频管理
 *  @deprecated
 *  @brief 远端视频数据size变化事件。调用 joinChannelByKey:channelName:info:uid:{@link #ByteRtcEngineKit#joinChannelByKey:channelName:info:uid:} 后，远端视频尺寸变化事件。
 *  @param engine ByteRtcEngineKit 对象
 *  @param uid 当前帧所属的用户ID
 *  @param size 视频的宽高尺寸
 */
- (void)rtcEngine:(ByteRtcEngineKit *_Nonnull)engine videoSizeChangedOfUid:(NSString * _Nonnull)uid size:(CGSize)size __attribute__((deprecated("Deprecated, please use a new interface")));


/**
 *  @type callback
 *  @region 视频管理
 *  @brief 远端视频数据 size 变化事件。调用 joinChannelByKey:channelName:info:uid:{@link #ByteRtcEngineKit#joinChannelByKey:channelName:info:uid:} 后，远端视频数据尺寸变化事件。
 *  @param engine ByteRtcEngineKit 对象
 *  @param uid 图像尺寸和旋转信息发生变化的用户的用户ID
 *  @param size 视频的宽高尺寸
 *  @param rotation 视频旋转信息，详见类型 ByteVideoRotation{@link #ByteVideoRotation}
 */
- (void)rtcEngine:(ByteRtcEngineKit *_Nonnull)engine videoSizeChangedOfUid:(NSString * _Nonnull)uid size:(CGSize)size rotation:(ByteVideoRotation)rotation;

/**
 *  @type callback
 *  @region 视频管理
 *  @brief 远端首帧视频数据解码事件回调。
 *  @param engine ByteRtcEngineKit 对象
 *  @param uid 发送当前帧的远端用户的用户ID
 *  @param size 视频的宽高尺寸
 *  @param elapsed 从开始订阅远端流到远端视频首帧解码事件的总耗时(ms)
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine firstRemoteVideoDecodedOfUid:( NSString* _Nonnull )uid size:(CGSize)size elapsed:(NSInteger)elapsed;

/**
 *  @type callback
 *  @region 视频管理
 *  @brief 远端首帧屏幕数据渲染事件回调。
 *  @param engine
 *         ByteRtcEngineKit 对象，参考: ByteRtcEngineKit{@link #ByteRtcEngineKit}
 *  @param uid
 *         发送当前帧的远端用户的用户ID
 *  @param size
 *         视频的宽高尺寸
 *  @param elapsed
 *         从开始订阅远端流到开始渲染远端首帧屏幕数据事件的总耗时 (ms)
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine firstRemoteScreenFrameOfUid:(NSString* _Nonnull )uid size:(CGSize)size elapsed:(NSInteger)elapsed;
/**
 *  @type callback
 *  @region 视频管理
 *  @brief 远端首帧屏幕数据解码事件回调。
 *  @param engine
 *         ByteRtcEngineKit 对象，参考: ByteRtcEngineKit{@link #ByteRtcEngineKit}
 *  @param uid
 *         发送当前帧的远端用户的用户ID
 *  @param size
 *         视频的宽高尺寸
 *  @param elapsed
 *         从开始订阅远端流到远端屏幕首帧解码事件的总耗时 (ms)
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine firstRemoteScreenDecodedOfUid:( NSString* _Nonnull )uid size:(CGSize)size elapsed:(NSInteger)elapsed;

/**
 *  @type callback
 *  @region 视频管理
 *  @brief 远端视频流状态发生改变回调。
 *  @param engine ByteRtcEngineKit 对象，参考: ByteRtcEngineKit{@link #ByteRtcEngineKit}
 *  @param uid 发生视频流状态改变的远端用户的用户ID
 *  @param state 变更后的远端视频流状态，详见类型 ByteVideoRemoteState{@link #ByteVideoRemoteState}
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine remoteVideoStateChangedOfUid:(NSString * _Nonnull)uid state:(ByteVideoRemoteState)state;

/**
 *  @type callback
 *  @region 视频管理
 *  @brief 本地视频镜像状态发生改变回调。
 *  @param engine ByteRtcEngineKit 对象
 *  @param  mirrored 当前是否开启镜像 <br>
 *        + true：当前本地视频状态为开启镜像  <br>
 *        + false：当前本地视频状态为关闭镜像  <br>
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine didMirrorStateChanged:(BOOL)mirrored;

/**
 * @type callback
 * @region 引擎管理
 * @brief 设备开启、停止状态通知
 * @param device_type 设备类型，详见 ByteMediaDeviceType{@link #ByteMediaDeviceType}
 * @param device_state 设备状态，详见 ByteMediaDeviceState{@link #ByteMediaDeviceState}
 * @notes 当前正在使用中的设备开启成功/失败，停止成功/失败时回调该事件，目前仅支持音频录制设备和播放设备。
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine didMediaDeviceStateChanged:(ByteMediaDeviceType)device_type device_state:(ByteMediaDeviceState)device_state;

/**
 * @type callback
 * @region 房间管理
 * @brief 音频首帧发送状态改变回调
 * @param user 本地用户信息，详见 ByteRtcUser{@link #ByteRtcUser}
 * @param state 首帧发送状态，详见 FirstFrameSendState{@link #FirstFrameSendState}
 */
- (void)rtcEngine:(ByteRtcEngineKit *_Nonnull)engine onAudioFrameSendStateChanged:(ByteRtcUser *_Nonnull)user state:(FirstFrameSendState)state;

/**
 * @type callback
 * @region 房间管理
 * @brief 视频首帧发送状态改变回调
 * @param user 本地用户信息，详见 ByteRtcUser{@link #ByteRtcUser}
 * @param state 首帧发送状态，详见 FirstFrameSendState{@link #FirstFrameSendState}
 */
- (void)rtcEngine:(ByteRtcEngineKit *_Nonnull)engine onVideoFrameSendStateChanged:(ByteRtcUser *_Nonnull)user state:(FirstFrameSendState)state;

/**
 * @type callback
 * @region 房间管理
 * @brief 屏幕共享流视频首帧发送状态改变回调
 * @param user 本地用户信息，详见 ByteRtcUser{@link #ByteRtcUser}
 * @param state 首帧发送状态，详见 FirstFrameSendState{@link #FirstFrameSendState}
 */
- (void)rtcEngine:(ByteRtcEngineKit *_Nonnull)engine onScreenVideoFrameSendStateChanged:(ByteRtcUser *_Nonnull)user state:(FirstFrameSendState)state;

/**
 * @type callback
 * @region 房间管理
 * @brief 音频首帧播放状态改变回调
 * @param user 远端用户信息，详见 ByteRtcUser{@link #ByteRtcUser}
 * @param state 首帧播放状态，详见 FirstFramePlayState{@link #FirstFramePlayState}
 */
- (void)rtcEngine:(ByteRtcEngineKit *_Nonnull)engine onAudioFramePlayStateChanged:(ByteRtcUser *_Nonnull)user state:(FirstFramePlayState)state;

/**
 * @type callback
 * @region 房间管理
 * @brief 视频首帧播放状态改变回调
 * @param user 远端用户信息，详见 ByteRtcUser{@link #ByteRtcUser}
 * @param state 首帧播放状态，详见 FirstFramePlayState{@link #FirstFramePlayState}
 */
- (void)rtcEngine:(ByteRtcEngineKit *_Nonnull)engine onVideoFramePlayStateChanged:(ByteRtcUser *_Nonnull)user state:(FirstFramePlayState)state;

/**
 * @type callback
 * @region 房间管理
 * @brief 屏幕共享流视频首帧播放状态改变回调
 * @param user 远端用户信息，详见 ByteRtcUser{@link #ByteRtcUser}
 * @param state 首帧播放状态，详见 FirstFramePlayState{@link #FirstFramePlayState}
 */
- (void)rtcEngine:(ByteRtcEngineKit *_Nonnull)engine onScreenVideoFramePlayStateChanged:(ByteRtcUser *_Nonnull)user state:(FirstFramePlayState)state;

#pragma mark - Media Stream Delegate Methods
/**
 *  -----------------------------------------------------------------------------
 *  @name 媒体数据事件回调
 *  -----------------------------------------------------------------------------
 */

/**
 *  @type callback
 *  @region 音频事件回调
 *  @brief 当收到本地第一帧音频的时候上报该事件
 *  @param engine ByteRtcEngineKit 对象
 *  @param elapsed 从开始发布音频流到收到该事件经历的时间（毫秒单位）
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine firstLocalAudioFrame:(NSInteger)elapsed;

/**
 *  @type callback
 *  @region 房间管理
 *  @brief 房间内新流发布回调。  <br>
 *         房间内的远端用户发布新的音视频流时，本地用户会收到此回调通知。  <br>
 *  @param engine ByteRtcEngineKit 对象。  <br>
 *  @param stream 流的属性，详见 ByteStream{@link #ByteStream} 数据类型。  <br>
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine onStreamAdd:(id <ByteStream> _Nonnull)stream;

/**
 *  @hidden
 *  @type callback
 *  @region 媒体事件回调
 *  @brief 加入房间时房间内的流。调用 joinChannelByKey:channelName:info:uid:{@link #ByteRtcEngineKit#joinChannelByKey:channelName:info:uid:} 加入房间成功后，加入房间时房间内的流
 *  @param engine ByteRtcEngineKit 对象
 *  @param streams 流的属性信息，详见类型ByteStream{@link #ByteStream}
 *  @param errorcode 错误码，0为成功
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine onLoginCompletion:(NSArray<id<ByteStream>>* _Nullable)streams errorCode:(NSInteger)errorcode;

/**
 *  @hidden
 *  @type callback
 *  @region 媒体事件回调
 *  @brief 房间内流数据订阅状态。用户启用自定义订阅时，通知用户对特定流的订阅状态
 *  @param engine ByteRtcEngineKit 对象
 *  @param state 流数据的订阅状态
 *  @param userId 用户ID
 *  @param info 自定义订阅配置，详见类型ByteSubscribeConfig{@link #ByteSubscribeConfig}
 */
- (void)rtcEngine:(ByteRtcEngineKit *_Nonnull)engine
    onStreamSubscribed:(SubscribeState)state
                userId:(NSString *_Nonnull)userId
       subscribeConfig:(SubscribeConfig *_Nonnull)info;

/**
 *  @type callback
 *  @region 房间管理
 *  @brief 房间内远端流移除回调。  <br>
 *         房间内的远端用户停止发布音视频流时，本地用户会收到此回调通知。  <br>
 *  @param engine ByteRtcEngineKit 对象。  <br>
 *  @param uid 用户ID 。远端流的发布用户的用户ID 。  <br>
 *  @param stream 流的属性，详见 ByteStream{@link #ByteStream} 数据类型。  <br>
 *  @param reason 远端流移除的原因，详见枚举类型 RtcStreamRemoveReason{@link #RtcStreamRemoveReason} 。  <br>
 */
- (void)rtcEngine:(ByteRtcEngineKit *_Nonnull)engine
    didStreamRemoved:(NSString *_Nonnull)uid
              stream:(id<ByteStream> _Nonnull)stream
              reason:(RtcStreamRemoveReason)reason;

/**
 *  @hidden
 *  @type callback
 *  @region 音频管理
 *  @brief 游戏场景中，当房间用户的的 sendmode 被修改的时候回调该事件，发送模式只有三种，分别是：静音、向小队发送、向世界发送
 *  @param [in] uid
 *         远端用户id
 *  @param [in] mode
 *         远端用户的发送模式
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine didUserAudioSendModeChange:(NSString* _Nonnull )uid mode:(RangeAudioMode)mode;

/**
 *  @hidden
 *  @type callback
 *  @region 音频管理
 *  @brief 游戏场景中，当房间用户的的 recvmode 被修改的时候回调该事件，收听模式只有三种，分别是：静音、收听小队、收听世界
 *  @param [in] uid
 *       远端用户id
 *  @param [in] mode
 *       远端用户的接收模式
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine didUserAudioRecvModeChange:(NSString* _Nonnull )uid mode:(RangeAudioMode)mode;

#pragma mark - Media Device Delegate Methods
/**
 *  -----------------------------------------------------------------------------
 *  @name 媒体设备事件回调
 *  -----------------------------------------------------------------------------
 */

/**
 *  @type callback
 *  @region 音频事件回调
 *  @brief 音频路由变化时回调该事件
 *  @param engine ByteRtcEngineKit 对象
 *  @param routing 新的音频路由，详见 ByteAudioOutputRouting{@link #ByteAudioOutputRouting}
 *  @notes 音频路由设置与音频路由策略详见 setEnableSpeakerphone{@link #setEnableSpeakerphone:}
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine didAudioRouteChanged:(ByteAudioOutputRouting)routing;


#pragma mark custom message Delegate Methods
/**-----------------------------------------------------------------------------
 *  @name 发送消息回调
 * -----------------------------------------------------------------------------
 */

/**
 *  @type callback
 *  @region 流消息
 *  @brief 接收到房间内广播消息的回调。
 *  @param engine ByteRtcEngineKit 对象
 *  @param uid 消息发送者 ID
 *  @param message 收到的消息内容
 *  @notes
 *        1.同一房间内其他用户调用 sendRoomMessage:{@link #sendRoomMessage:} 发送广播消息时会收到该回调。
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine onRoomMessageReceived:(NSString * _Nonnull)uid message:(NSString * _Nonnull)message;

/**
 *  @type callback
 *  @region 流消息
 *  @brief 接收到房间内广播二进制消息的回调。
 *  @param engine ByteRtcEngineKit 对象
 *  @param uid 消息发送者 ID
 *  @param message 收到的二进制消息内容
 *  @notes
 *        1.同一房间内其他用户调用 sendRoomBinaryMessage:{@link #sendRoomBinaryMessage:} 发送广播消息时会收到该回调。
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine onRoomBinaryMessageReceived:(NSString * _Nonnull)uid message:(NSData * _Nonnull)message;

#pragma mark - Statistics Delegate Methods
/**
 *  -----------------------------------------------------------------------------
 *  @name 数据统计回调
 *  -----------------------------------------------------------------------------
 */

/**
 * @type callback
 * @region 数据统计
 * @brief 房间通话数据回调。  <br>
 *        用户加入当前房间成功后，SDK 会周期性（2s）的通过此回调事件通知用户当前房间内的汇总统计信息。  <br>
 * @param engine ByteRtcEngineKit 对象。  <br>
 * @param stats 房间内的汇总统计数据，详见 ByteRtcStats{@link #ByteRtcStats} 数据类型。  <br>
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine reportRtcStats:(ByteRtcStats * _Nonnull)stats;

/**
 * @type callback
 * @region 数据统计
 * @brief 周期性回调，报告当前cpu与memory使用率
 * @param engine ByteRtcEngineKit 对象。  <br>
 * @param stats cpu和memory使用率信息，详见 ByteRtcSysStats{@link #ByteRtcSysStats} 数据类型。  <br>
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine reportSysStats:(const ByteRtcSysStats * _Nonnull)stats;

/**
 * @type callback
 * @region 引擎管理
 * @brief 通话中用户的媒体流网络上下行质量报告回调。加入房间成功后，每隔 2 秒会触发此回调，通知房间内用户与媒体服务器之间数据交互的网络质量。
 * @param engine  <br>
 *        当前 RTCEngine 实例。
 * @param uid  <br>
 *        回调的网络质量报告所属用户的用户 ID 。
 * @param txQuality  <br>
 *        uid 所属用户的媒体流上行网络质量。
 * @param rxQuality  <br>
 *        uid 所属用户的媒体流下行网络质量。
 * @notes  <br>
 *        + 当 uid 为本地用户 ID 时，txQuality 为该用户的上行网络质量，rxQuality 为该用户的下行网络质量。  <br>
 *        + 当 uid 为远端用户 ID 时，目前仅支持获取该用户的上行网络质量 txQuality ，下行网络质量 rxQuality 为 ByteRtcNetworkQualityUnknown。  <br>
 *        + ByteNetworkQuality 的定义详见： ByteNetworkQuality{@link #ByteNetworkQuality} 。
 */
- (void)rtcEngine:(ByteRtcEngineKit *_Nonnull)engine networkQuality:(NSString*_Nonnull)uid txQuality:(ByteNetworkQuality)txQuality rxQuality:(ByteNetworkQuality)rxQuality;

/**
 *  @type callback
 *  @region 数据统计
 *  @brief 发布视频流数据统计回调。  <br>
 *         本地用户发布视频流成功后，SDK 会周期性（2s）的通过此回调事件通知用户发布的视频流在此次统计周期内的质量统计信息。统计信息通过 ByteRtcLocalVideoStats{@link #ByteRtcLocalVideoStats} 类型的回调参数传递给用户，其中包括发送视频比特率、发送帧率、编码帧率等。  <br>
 *  @param engine ByteRtcEngineKit 对象。  <br>
 *  @param stats 发布视频流质量统计数据，详见 ByteRtcLocalVideoStats{@link #ByteRtcLocalVideoStats} 数据类型。  <br>
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine localVideoStats:(ByteRtcLocalVideoStats * _Nonnull)stats;

/**
 *  @type callback
 *  @region 数据统计
 *  @brief 订阅视频流数据统计回调。  <br>
 *         本地用户订阅视频流成功后，SDK 会周期性（2s）的通过此回调事件通知用户订阅的视频流在此次统计周期内的质量统计信息。统计信息通过 ByteRtcRemoteVideoStats{@link #ByteRtcRemoteVideoStats} 类型的回调参数传递给用户，其中包括视频宽高、接收带宽、帧率及卡顿等信息。  <br>
 *  @param engine ByteRtcEngineKit 对象。  <br>
 *  @param stats 订阅视频流质量统计数据，详见 ByteRtcRemoteVideoStats{@link #ByteRtcRemoteVideoStats} 数据类型。  <br>
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine remoteVideoStats:(ByteRtcRemoteVideoStats * _Nonnull)stats;

/**
 * @type callback
 * @region 数据统计
 * @brief 通话中订阅音频流质量报告回调。包括发送音频比特率，音频丢包率等
 * @param engine RtcEngine 实例
 * @param stats 发布音频流质量，参见 ByteRtcLocalAudioStats{@link #ByteRtcLocalAudioStats}
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine localAudioStats:(ByteRtcLocalAudioStats * _Nonnull)stats;

/**
 * @type callback
 * @region 数据统计
 * @brief 通话中订阅音频流质量报告回调。包括订阅音频流的发布者的 uid、接收音频比特率、音频丢包率及卡顿信息。
 * @param engine RtcEngine 实例
 * @param stats 订阅音频流质量，参见 ByteRtcRemoteAudioStats{@link #ByteRtcRemoteAudioStats}
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine remoteAudioStats:(ByteRtcRemoteAudioStats * _Nonnull)stats;

/**
 *  @type callback
 *  @region 音频事件回调
 *  @brief 本地音频的状态发生改变时，该回调通知当前的本地音频状态。
 *  @param engine ByteRtcEngineKit 对象
 *  @param state  本地音频设备的状态，详见： ByteLocalAudioStreamState{@link #ByteLocalAudioStreamState}
 *  @param error  本地音频状态改变时的错误码，详见：ByteLocalAudioStreamError{@link #ByteLocalAudioStreamError}
*/
- (void)rtcEngine:(ByteRtcEngineKit *_Nonnull)engine
    localAudioStateChanged:(ByteLocalAudioStreamState)state
                     error:(ByteLocalAudioStreamError)error;

/**
 *  @type callback
 *  @region 音频事件回调
 *  @brief 远端用户音频状态发生改变时，该回调通知当前的远端音频流状态。
 *  @param engine ByteRtcEngineKit 对象
 *  @param uid 该远端流的用户id
 *  @param state 远端音频流状态，详见：ByteRemoteAudioState{@link #ByteRemoteAudioState}
 *  @param reason 远端音频流状态改变的原因，详见：ByteRemoteAudioReason{@link #ByteRemoteAudioReason}
 *  @param elapsed 耗时，从加入房间到该事件发生经历的时间
*/
- (void)rtcEngine:(ByteRtcEngineKit *_Nonnull)engine
    remoteAudioStateChanged:(NSString *_Nonnull)uid
                      state:(ByteRemoteAudioState)state
                     reason:(ByteRemoteAudioReason)reason
                    elapsed:(NSInteger)elapsed;

/**
 *  @type callback
 *  @region 频道管理
 *  @brief 本地视频的状态发生改变时，该回调返回当前的本地视频状态。
 *  @param engine ByteRtcEngineKit 对象
 *  @param state 本地视频状态
 *  @param error 本地音频状态改变时的错误码
 */

- (void)rtcEngine:(ByteRtcEngineKit *_Nonnull)engine
    localVideoStateChanged:(ByteLocalVideoStreamState)state
                     error:(ByteLocalVideoStreamError)error;

/**
 *  @type callback
 *  @region 频道管理
 *  @brief 远端用户视频状态发生改变时，该回调报告当前的远端视频流状态。
 *  @param engine ByteRtcEngineKit 对象
 *  @param uid   该远端流的用户ID
 *  @param state   远端视频流状态
 *  @param reason   远端视频流状态改变的原因
 *  @param elapsed    耗时，暂未实现
*/

- (void)rtcEngine:(ByteRtcEngineKit *_Nonnull)engine
    remoteVideoStateChanged:(NSString *_Nonnull)uid
                      state:(ByteRemoteVideoState)state
                     reason:(ByteRemoteVideoReason)reason
                    elapsed:(NSInteger)elapsed;

#pragma mark - Message Delegate Methods
/**
 * @type callback
 * @region 流消息
 * @brief 点对点消息回调。接收到同一房间内 uid 所属用户发来消息时触发。
 * @param engine  <br>
 *        当前 RTCEngine 实例。
 * @param uid  <br>
 *        消息发送者 ID 。
 * @param message  <br>
 *        收到的消息内容。
 * @notes  <br>
 *        + 同一房间内其他用户调用 sendUserMessage:message:{@link #sendUserMessage:message:} 发送消息给本地用户时会收到该回调。
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine onUserMessageReceived:(NSString * _Nonnull)uid message:(NSString * _Nonnull)message;

/**
 *  @type callback
 *  @region 流消息
 *  @brief 接收到同一房间内 uid 所属用户发来二进制消息的回调。
 *  @param engine ByteRtcEngineKit 对象
 *  @param uid 消息发送者 ID
 *  @param message 收到的二进制消息内容
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine onUserBinaryMessageReceived:(NSString * _Nonnull)uid message:(NSData * _Nonnull)message;

/**
 *  @type callback
 *  @region 流消息
 *  @brief 当调用 sendUserMessage:message:{@link #sendUserMessage:message:} 函数发送消息后，回调此条消息的发送结果（反馈）。
 *  @param engine ByteRtcEngineKit 对象
 *  @param msgid 本条消息的 ID
 *  @param error 消息发送结果，详见枚举类型 MessageCode{@link #MessageCode}
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine onUserMessageSendResult:(int64_t)msgid error:(UserMessageCode)error;

/**
 *  @type callback
 *  @region 流消息
 *  @brief 当调用 sendRoomMessage:{@link #sendRoomMessage:} 函数发送消息后，回调此条消息的发送结果（反馈）。
 *  @param engine ByteRtcEngineKit 对象
 *  @param msgid 本条消息的 ID
 *  @param error 消息发送结果，详见枚举类型 MessageCode{@link #MessageCode}
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine onRoomMessageSendResult:(int64_t)msgid error:(RoomMessageCode)error;

#pragma mark - Subscribe Delegate Methods

/**
 *  @hidden
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine
     didSubscribe:(NSString * _Nonnull)uid isReconnect:(BOOL)isReconnect;

/**
 *  @hidden
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine
   didUnSubscribe:(NSString * _Nonnull)uid isReconnect:(BOOL)isReconnect;

#pragma mark - Log Delegate Methods
/**
 *  -----------------------------------------------------------------------------
 *  @name 日志相关回调
 *  -----------------------------------------------------------------------------
 */

/**
 * @type callback
 * @region 引擎管理
 * @brief SDK 内部日志回调。  <br>
 *        SDK 内部运行时，会把日志回调给业务方，方便排查问题。
 * @param engine  <br>
 *        ByteRtcEngineKit 对象。
 * @param dict  <br>
 *        日志内容。
 */
- (void)rtcEngine:(ByteRtcEngineKit* _Nonnull)engine log:(NSDictionary* _Nonnull)dict;

#pragma mark Unimplemented Delegate Methods
/**-----------------------------------------------------------------------------
 *  @name 未实现回调
 * -----------------------------------------------------------------------------
 */

/**
 * @type callback
 * @region 数据统计
 * @brief 音频质量通知。通知业务方，当前通话中的音频质量。
 * @param engine 当前 RtcEngine
 * @param uid 当前帧所属的用户 id
 * @param quality 质量等级，参见 ByteNetworkQuality{@link #ByteNetworkQuality}
 * @param delay 音频包从发送端到接收端的延迟（毫秒）。包括声音采样前处理、网络传输、网络抖动缓冲引起的延迟
 * @param lost 音频包从发送端到接收端的丢包率（%）
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine audioQualityOfUid:(NSString* _Nonnull )uid quality:(ByteNetworkQuality)quality delay:(NSUInteger)delay lost:(NSUInteger)lost;


#pragma mark Audio Mix Delegate Methods
/**-----------------------------------------------------------------------------
 *  @name 音频混音回调
 * -----------------------------------------------------------------------------
 */

/**
 *  @type callback
 *  @region 混音
 *  @brief 音乐文件混音结束回调。SDK通过此回调通知应用层音乐文件混音结束。
 *  @param engine 当前RTC SDK对象
 */
- (void)rtcEngineLocalAudioMixingDidFinish:(ByteRtcEngineKit *_Nonnull)engine;

/**
 *  @type callback
 *  @region 混音
 *  @brief 音效文件混音结束回调。SDK通过此回调通知应用层音效文件混音结束
 *  @param engine 当前RTC SDK对象
 *  @param soundId 音效ID
 */
- (void)rtcEngineDidAudioEffectFinish:(ByteRtcEngineKit *_Nonnull)engine soundId:(NSInteger)soundId;

#pragma mark transcoding Delegate Methods
/**-----------------------------------------------------------------------------
 *  @name 合流转推状态回调
 * -----------------------------------------------------------------------------
 */

/**
 *  @type callback
 *  @region CDN 推流
 *  @brief 直播推流转码状态回调。  <br>
 *         用户调用 enableLiveTranscoding:{@link #enableLiveTranscoding:} 方法启动直播推流转码功能后，直播推流转码功能启动成功或失败时、推流过程中发生错误时，SDK 通过此回调通知用户对应的状态事件。  <br>
 *         回调事件为错误状态事件时，App 需根据功能状态码的处理建议做对应的处理，如通知用户或重试等。  <br>
 *  @param engine ByteRtcEngineKit 对象。  <br>
 *  @param url 推流地址。直播推流的地址，为 URL 地址。  <br>
 *  @param errorCode 直播推流转码功能状态码，详见枚举类型 ByteRtcTransCodeingErrorCode{@link #ByteRtcTransCodeingErrorCode} 。  <br>
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine TransCodingWithUrl:(NSString * _Nonnull)url errorCode:(ByteRtcTransCodeingErrorCode)errorCode;


#pragma mark Performance Delegate Methods
/**-----------------------------------------------------------------------------
 * @name 性能相关的回调
 *  -----------------------------------------------------------------------------
 */

/**
 *  @hidden
 *  @type callback
 *  @region 音视频回退
 *  @brief 当检测到设备性能不足时，回调性能告警。可通过调整 effect 等级等，降低性能消耗。
 *  @param engine 当前RTCEngine 实例
 *  @param level 告警等级。目前可能无法区分告警的等级。
 *         初期 level 值可以只包含 0 和 1，1 为性能告警，0 则为解除告警。
 *  @param data 性能回退相关数据，详见 ByteSourceWantedData{@link #ByteSourceWantedData}。
 */
- (void)rtcEngine:(ByteRtcEngineKit *_Nonnull)engine onPerformanceAlarmsWithLevel:(NSInteger)level sourceWantedData:(ByteSourceWantedData *_Nonnull)data;

/**
 * @type callback
 * @region 音视频回退
 * @brief 收到远端流回退或恢复时回调该事件。
 * @param engine 当前RTCEngine 实例
 * @param event 远端流回退或恢复数据。详见 ByteRemoteStreamSwitchEvent{@link #ByteRemoteStreamSwitchEvent}。
 */
- (void)rtcEngine:(ByteRtcEngineKit *_Nonnull)engine OnRemoteStreamSwitch:(ByteRemoteStreamSwitchEvent *_Nonnull)event;

@end

/**
 * @type callback
 * @region 自定义音频采集渲染
 * @brief 音频外部设备事件监听，只用于自定义音频采集渲染的情况
 *      SDK内部需要控制外部设备时，通过这个事件监听类通知上层应用
 */
@protocol ByteAudioDeviceObserver <NSObject>

/**
 * @type callback
 * @region 自定义音频采集渲染
 * @brief 通知上层应用开启音频采集设备
 */
- (void)onAudioDeviceRecordStart;

/**
 * @type callback
 * @region 自定义音频采集渲染
 * @brief 通知上层应用关闭音频采集设备
 */
- (void)onAudioDeviceRecordStop;

/**
 * @type callback
 * @region 自定义音频采集渲染
 * @brief 通知上层应用开启音频播放设备
 */
- (void)onAudioDevicePlayoutStart;

/**
 * @type callback
 * @region 自定义音频采集渲染
 * @brief 通知上层应用关闭音频播放设备
 */
- (void)onAudioDevicePlayoutStop;
@end

/**
 *  @type callback
 *  @brief 音频数据代理
 */
@protocol ByteAudioFrameObserver <NSObject>

/**
 * @type callback
 * @region 音频数据回调
 * @brief 返回麦克风录制的音频数据
 * @param audioFrame 麦克风录制的音频数据, 详见：ByteAudioFrame{@link #ByteAudioFrame}
 */
- (void)onRecordAudioFrame:(ByteAudioFrame * _Nonnull)audioFrame;

/**
 * @type callback
 * @region 音频数据回调
 * @brief 返回远端所有用户混音后的音频数据
 * @param audioFrame 远端所有用户混音后的音频数据, 详见：ByteAudioFrame{@link #ByteAudioFrame}
 */
- (void)onPlaybackAudioFrame:(ByteAudioFrame * _Nonnull)audioFrame;

/**
 * @hidden
 * @region 音频数据回调
 * @notes 该接口未实现
 */
- (void)onPlaybackAudioFrameBeforeMixing:(NSString* _Nonnull )uid
                      audioFrame:(ByteAudioFrame * _Nonnull)audioFrame;

/**
 * @type callback
 * @region 音频数据回调
 * @brief 返回本地麦克风录制和远端所有用户混音后的音频数据
 * @param audioFrame  本地麦克风录制和远端所有用户混音后的音频数据, 详见：ByteAudioFrame{@link #ByteAudioFrame}
 */
- (void)onMixedAudioFrame:(ByteAudioFrame * _Nonnull)audioFrame;
@end

#pragma mark - ByteRtcEngineMediaMetadataObserver
/**
*  @type callback
*  @brief 使用内部源视频采集时,配置和获取附加数据接口
*/
BYTE_RTC_EXPORT @protocol ByteRtcEngineMediaMetadataObserver <NSObject>
@required
/**
 * @type callback
 * @region 视频数据回调
 * @brief 当 SDK 准备发送一个视频帧时，会回调该接口，以确定是否需要在该视频帧中添加 metadata
 * @param timestamp 待添加 metadata 视频帧的时间戳，单位微秒
 * @return 待发送的数据，大小不能超过 1024bytes
 * @notes  <br>
 *       + 返回 null 代表不需要添加 metadata  <br>
 *       + 回调中不能做长时间逻辑处理，以免影响视频卡顿  <br>
 */
- (NSData *_Nullable)videoFrameMediaMetaDataAtTime:(NSTimeInterval)timestamp;

@optional
/**
 * @type callback
 * @region 视频数据回调
 * @brief 当 SDK 收到的视频帧包含 medatada 时，会回调该接口
 * @param uid 当前帧所属的用户ID
 * @param extendedData metadata
 * @param timestamp 包含 metadata 视频帧的时间戳，单位为微秒
 * @notes 回调中不能做长时间逻辑处理，以免影响视频卡顿
 */
- (void)receiveVideoFrameFromUID:(NSString * _Nonnull)uid withExtendedData:(NSData* _Nullable)extendedData atTimestamp:(NSTimeInterval)timestamp;
@end

#pragma mark - ByteEncryptHandler
/**
 * @type callback
 * @region 加密
 * @brief 自定义加密接口
 */
@protocol ByteEncryptHandler <NSObject>

@required
/**
 * @type callback
 * @region 加密
 * @brief 自定义加密的方法接口  <br>
 *        通过继承并实现该方法，可以扩展传输过程中的加密方法，
 *        详见 setCustomizeEncryptHandler:{@link #setCustomizeEncryptHandler:}  <br>
 * @param rawData  <br>
 *        原始音视频帧数据  <br>
 * @return
 *        返回加密后的数据  <br>
 *        + 非空，表示加密后的数据  <br>
 *        + 为空，表示丢弃该帧  <br>
 * @notes
 *        返回的数据大小应控制在原始数据的90%~120%范围以内，不然将被丢弃  <br>
*/
- (NSData * _Nonnull)ByteEngineEncryptRawData:(NSData * _Nonnull)rawData;

@required
/**
 * @type callback
 * @region 加密
 * @brief 自定义解密的方法接口  <br>
 *        通过继承并实现该方法，可以扩展传输过程中的解密方法，
 *        详见 setCustomizeEncryptHandler:{@link #setCustomizeEncryptHandler:}  <br>
 * @param rawData  <br>
 *        原始音视频帧数据  <br>
 * @return
 *        返回解密后的数据  <br>
 *        + 非空，表示解密后的数据  <br>
 *        + 为空，表示丢弃该帧  <br>
 * @notes
 *        返回的数据大小应控制在原始数据的90%~120%范围以内，不然将被丢弃  <br>
*/
- (NSData * _Nonnull)ByteEngineDecryptRawData:(NSData * _Nonnull)rawData;
@end

#pragma mark - ByteRtcAudioDeviceManager
/**
 * @hidden
 * @type callback
 * @region 音频管理
 * @brief 音频设备事件回调
 */
BYTE_RTC_EXPORT @protocol ByteAudioDeviceEventHandler<NSObject>
/**
 * @hidden
 * @type callback
 * @region 音频管理
 *  @brief 获得麦克风音量
 *  @param volume 音量大小
 */
- (void)onRecordingAudioVolumeIndication:(int)volume;
@end

/**
 * @hidden
 * @type api
 */
BYTE_RTC_EXPORT @interface ByteRtcAudioDeviceManager : NSObject
/**
 * @hidden
 * @type api
 */
- (int)startPlaybackDeviceTest:(NSString *_Nonnull)testAudioFilePath;
/**
 * @hidden
 * @type api
 */
- (int)stopPlaybackDeviceTest;
/**
 * @hidden
 * @type api
 */
- (int)startAudioRecordingDeviceTest:(unsigned int)indicationInterval;
/**
 * @hidden
 * @type api
 */
- (int)stopAudioRecordingDeviceTest;
/**
 * @hidden
 * @type api
 */
- (void)setEnableSpeakerphone:(bool)enable;
@end

/**
 * @type callback
 * @region 监控
 * @brief 非业务相关的监控事件回调
 */
@protocol ByteRtcMonitorDelegate <NSObject>

@optional

/**
 * @type callback
 * @region 监控
 * @brief 埋点日志回调  <br>
 * @param data  <br>
 *        具体的埋点内容  <br>
 * @param type  <br>
 *        埋点的类型
*/
- (void)onMonitorLog:(NSDictionary * _Nullable)data withType:(NSString * _Nullable)type;

/**
 * @type api
 * @region 监控
 * @brief 是否进行控制台输出
 * @return
 *        返回是否进行控制台输出  <br>
 *        + YES 输出所有的日志到控制台  <br>
 *        + NO 不输出任何控制台信息
 */
- (BOOL)isConsole;

/**
 * @type callback
 * @region 监控
 * @brief 输出更多的调试信息
 */
- (void)onVerboseLogWithLevel:(ByteRtcLogLevel)level
                     filename:(NSString * _Nonnull)filename
                          tag:(NSString * _Nonnull)tag
                         line:(int)line
                 functionName:(NSString * _Nonnull)funcName
                       format:(NSString * _Nonnull)format;

@end

#pragma mark - ByteRtcEngineKit
/**
 * @type api
 * @region 引擎管理
 * @brief SDK回调给应用层的delegate对象，详见 ByteRtcEngineDelegate{@link #ByteRtcEngineDelegate}
 */
BYTE_RTC_EXPORT @interface ByteRtcEngineKit : NSObject
/**
 * @hidden
 */
@property (nonatomic, weak) id<ByteRtcEngineDelegate> _Nullable delegate;

/**
 * @hidden
 */
@property (nonatomic, weak) id<ByteRtcMonitorDelegate> _Nullable monitorDelegate;

#pragma mark Core Methods
/**
 *  -----------------------------------------------------------------------------
 *  @name 核心方法
 *  -----------------------------------------------------------------------------
 */

/**
 * @type api
 * @region 引擎管理
 * @brief 创建 RTCEngine 实例。  <br>
 *        此方法应该作为正常 SDK 流程中的第一步操作，通过创建一个 RTCEngine 实例，来使用 SDK 的其他能力。
 * @param appId  <br>
 *        每个应用的唯一标识符，由 VRTC 控制台随机生成的。不同的 AppId 生成的实例在 VRTC 中进行音视频通话完全独立，无法互通。
 * @param delegate  <br>
 *        SDK 回调给应用层的 delegate，详见 ByteRtcEngineDelegate{@link #ByteRtcEngineDelegate}
 * @return 可用的 ByteRtcEngineKit{@link #ByteRtcEngineKit} 实例。
 * @notes  <br>
 *        + 该方法在第一次调用时初始化一个 RTCEngine 单例，除非调用 destroy{@link #destroy} 方法，否则后续的所有调用均
 *          返回同一个内部实例。  <br>
 *        + 连续多次调用该方法不会创建不同的 ByteRtcEngineKit{@link #ByteRtcEngineKit}，该方法应该与 destroy{@link #destroy}
 *          成对使用  <br>
 *        + 必须使用相同的App ID，App 间才能进行通话。  <br>
 *        + 在调用 destroy{@link #destroy} 之后会销毁 ByteRtcEngineKit{@link #ByteRtcEngineKit} 实例，再次调用
 *          sharedEngineWithAppId:delegate:{@link #sharedEngineWithAppId:delegate:} 方法则会重新创建一个全新的
 *          ByteRtcEngineKit{@link #ByteRtcEngineKit} 实例。
 */
+ (instancetype _Nonnull)sharedEngineWithAppId:(NSString * _Nonnull)appId
                                      delegate:(id<ByteRtcEngineDelegate> _Nullable)delegate;
/**
 * @type api
 * @region 引擎管理
 * @brief 创建 RTCEngine 实例。  <br>
 *        此方法应该作为正常 SDK 流程中的第一步操作，通过创建一个 RTCEngine 实例，来使用 SDK 的其他能力。
 * @param appId  <br>
 *        每个应用的唯一标识符，由 VRTC 控制台随机生成的。不同的 AppId 生成的实例在 VRTC 中进行音视频通话完全独立，无法互通。
 * @param delegate  <br>
 *        SDK 回调给应用层的 delegate，详见 ByteRtcEngineDelegate{@link #ByteRtcEngineDelegate}
 * @param monitorDelegate  <br>
 *        监控信息的回调 delegate, 详见 ByteRtcMonitorDelegate{@link #ByteRtcMonitorDelegate}
 * @return 可用的 ByteRtcEngineKit{@link #ByteRtcEngineKit} 实例。
 * @notes  <br>
 *        + 该方法在第一次调用时初始化一个 RTCEngine 单例，除非调用 destroy{@link #destroy} 方法，否则后续的所有调用均
 *          返回同一个内部实例。  <br>
 *        + 连续多次调用该方法不会创建不同的 ByteRtcEngineKit{@link #ByteRtcEngineKit}，该方法应该与 destroy{@link #destroy}
 *          成对使用  <br>
 *        + 必须使用相同的App ID，App 间才能进行通话。  <br>
 *        + 在调用 destroy{@link #destroy} 之后会销毁 ByteRtcEngineKit{@link #ByteRtcEngineKit} 实例，再次调用
 *          sharedEngineWithAppId:delegate:{@link #sharedEngineWithAppId:delegate:} 方法则会重新创建一个全新的
 *          ByteRtcEngineKit{@link #ByteRtcEngineKit} 实例。
 */
+ (instancetype _Nonnull)sharedEngineWithAppId:(NSString * _Nonnull)appId
                                      delegate:(id<ByteRtcEngineDelegate> _Nullable)delegate
                               monitorDelegate:(id<ByteRtcMonitorDelegate> _Nullable)monitorDelegate;

/**
 * @type api
 * @region 引擎管理
 * @brief 获取 ByteRtcEngineKit{@link #ByteRtcEngineKit} 单例对象。
 * @return 由 sharedEngineWithAppId:delegate:{@link #sharedEngineWithAppId:delegate:} 创建的 ByteRtcEngineKit{@link #ByteRtcEngineKit} 对象。
 * @notes  <br>
 *        + 如果未调用 sharedEngineWithAppId:delegate:{@link #sharedEngineWithAppId:delegate:}
 *          或在调用 destroy{@link #destroy} 之后调用该方法，则会返回 nil 。
 */
+ (ByteRtcEngineKit * _Nullable) sharedInstance;

/**
 * @type api
 * @region 引擎管理
 * @brief 创建引擎对象，此方法应该作为正常 SDK 流程中的第一步操作，通过创建一个引擎实例，来使用 SDK 的其他能力
 * @param appId 每个应用的唯一标识符，由 VRTC 控制台随机生成的。不同的 AppId 生成的实例在 VRTC
 *              中进行音视频通话完全独立，无法互通。
 * @param delegate SDK 回调给应用层的 delegate，详见 ByteRtcEngineDelegate{@link #ByteRtcEngineDelegate}
 * @param parameters 用以覆盖全局参数，详情可见 setParameters{@link #setParameters}
 * @return 可用的 ByteRtcEngineKit{@link #ByteRtcEngineKit} 实例
 * @notes
 *      1. 连续多次调用该方法会创建不同的 ByteRtcEngineKit{@link #ByteRtcEngineKit}
 *      2. 必须使用相同的App ID，App间才能进行通话
 */
- (id _Nonnull)initWithAppId:(NSString * _Nonnull)appId
                    delegate:(id<ByteRtcEngineDelegate> _Nullable)delegate
                  parameters:(NSDictionary* _Nullable)parameters;

/**
 * @type api
 * @region 引擎管理
 * @brief 创建引擎对象，此方法应该作为正常 SDK 流程中的第一步操作，通过创建一个引擎实例，来使用 SDK 的其他能力
 * @param appId 每个应用的唯一标识符，由 VRTC 控制台随机生成的。不同的 AppId 生成的实例在 VRTC
 *              中进行音视频通话完全独立，无法互通。
 * @param delegate SDK 回调给应用层的 delegate，详见 ByteRtcEngineDelegate{@link #ByteRtcEngineDelegate}
 * @param parameters 用以覆盖全局参数，详情可见 setParameters{@link #setParameters}
 * @param monitorDelegate  <br>
 *        监控信息的回调 delegate, 详见 ByteRtcMonitorDelegate{@link #ByteRtcMonitorDelegate}
 * @return 可用的 ByteRtcEngineKit{@link #ByteRtcEngineKit} 实例
 * @notes
 *      1. 连续多次调用该方法会创建不同的 ByteRtcEngineKit{@link #ByteRtcEngineKit}
 *      2. 必须使用相同的App ID，App间才能进行通话
 */
- (id _Nonnull)initWithAppId:(NSString * _Nonnull)appId
                    delegate:(id<ByteRtcEngineDelegate> _Nullable)delegate
             monitorDelegate:(id<ByteRtcMonitorDelegate> _Nullable)monitorDelegate
                  parameters:(NSDictionary* _Nullable)parameters;

/**
 * @type api
 * @region 引擎管理
 * @brief 手动销毁引擎实例对象，如果当前的引擎对象是通过 sharedEngineWithAppId:delegate:{@link #sharedEngineWithAppId:delegate:}
 *      所创建的，则行为与 destroy{@link #destroy} 保持一致
 * @notes
 *      1. 请确保一定是在所有业务场景的最后阶段才调用该方法
 *      2. 该方法在调用之后，会销毁所有SDK相关的内存，并且停止与媒体服务器的任何交互
 *      3. 本方法为阻塞调用，会阻塞当前线程直到SDK彻底完成退出逻辑，因而需要注意不要在回调线程中
 *      直接调用本方法，也需要注意不要在回调方法中等待主线程的执行，而同时在主线程调用本方法，从而
 *      造成死锁
 *      4. 可以通过 Objective-C 的ARC机制，在 dealloc 时自动触发销毁逻辑
 */
- (void)destroyEngine;
/**
 * @type api
 * @region 引擎管理
 * @brief 销毁由 sharedEngineWithAppId:delegate:{@link #sharedEngineWithAppId:delegate:} 创建的引擎实例，并释放所有相关资源。
 * @notes  <br>
 *        + 请确保一定是在所有业务场景的最后阶段才调用该方法。  <br>
 *        + 该方法在调用之后，会销毁所有 SDK 相关的内存，并且停止与媒体服务器的任何交互。  <br>
 *        + 在上一次 sharedEngineWithAppId:delegate:{@link #sharedEngineWithAppId:delegate:} 调用之后对SDK进行的任何设置，
 *          将在下一次有效执行 sharedEngineWithAppId:delegate:{@link #sharedEngineWithAppId:delegate:} 时生效。  <br>
 *        + 本方法为阻塞调用，会阻塞当前线程直到 SDK 彻底完成退出逻辑，因而需要注意不要在回调线程中直接调用本方法，
 *          也需要注意不要在回调方法中等待主线程的执行而同时在主线程调用本方法，从而造成死锁。
 */
+ (void)destroy;

/**
 * @type api
 * @region 引擎管理
 * @brief 获取 SDK 当前的版本号。
 * @return SDK 当前的版本号。
 */
+ (NSString * _Nonnull)getSdkVersion;

/**
 * @type api
 * @hidden
 * @region 引擎管理
 * @brief 设置 JSON 格式的字符串参数，配置 RTC 引擎参数。
 * @param parameters  <br>
 *        JSON 格式的字符串参数。
 * @return  <br>
 *        + 0： 成功。  <br>
 *        + <0： 失败。
 * @notes  <br>
 *        + 需要在引擎初始化之前调用。
 */
+ (int)setParameters:(NSString* _Nullable)parameters;

/**
 *  @type api
 *  @region 房间管理
 *  @brief 设置房间模式。  <br>
 *         通过设置房间模式，用户可以选择应用 SDK 针对不同房间模式场景的优化策略。  <br>
 *         默认的房间模式为通信模式 ByteChannelProfileCommunication{@link #ByteChannelProfileCommunication} 。  <br>
 *         房间模式必须在调用 joinChannelByKey:channelName:info:uid:{@link #joinChannelByKey:channelName:info:uid:} 加入房间前设置，加入房间后设置不生效。设置用户角色（通过方法 setClientRole:{@link #setClientRole:} ）建议在设置完房间模式后。  <br>
 *  @param profile 房间模式，详见 ByteChannelProfile{@link #ByteChannelProfile} 枚举类型。  <br>
 *  @return 方法调用结果。  <br>
 *         +  0: 方法调用成功  <br>
 *         + <0: 方法调用失败  <br>
 *  @notes  <br>
 *        + 为保证音视频质量和实时性，建议相同房间内的用户使用相同的房间模式。  <br>
 */
- (int)setChannelProfile:(ByteChannelProfile)profile;

/**
 *  @type api
 *  @region 房间管理
 *  @brief 设置用户角色。  <br>
 *         用户可通过设置用户角色，控制：1.是否发布音视频流；2.用户自身是否在房间中隐身。用户角色详见 ByteRtcClientRole{@link #ByteRtcClientRole} 枚举类型。  <br>
 *         默认用户角色为主播角色 ByteRtc_ClientRole_Broadcaster{@link #ByteRtc_ClientRole_Broadcaster} 。  <br>
 *         房间模式（通过调用接口 setChannelProfile:{@link #setChannelProfile:} 可设置房间模式）为直播模式、游戏模式、云游戏模式时，设置用户角色生效。房间模式为通信模式时不区分用户角色。  <br>
 *  @param role 用户角色，详见 ByteRtcClientRole{@link #ByteRtcClientRole} 枚举类型。  <br>
 *  @return 方法调用结果。  <br>
 *         + YES: 方法调用成功  <br>
 *         +  NO: 方法调用失败  <br>
 *  @notes  <br>
 *        + 在加入房间前，用户可调用此方法设置用户角色。加入房间后，用户也可通过此方法切换用户角色。  <br>
 *        + 用户在加入房间成功后调用该方法切换用户角色，调用成功后，远端用户会收到相应的回调通知：1.本地用户角色从静默观众切换至观众或主播时，远端用户会收到 rtcEngine:didJoinedOfUid:elapsed:{@link #ByteRtcEngineDelegate#rtcEngine:didJoinedOfUid:elapsed:} 回调通知；2.本地用户角色从观众或主播切换至静默观众时，远端用户会收到 rtcEngine:didOfflineOfUid:reason:{@link #ByteRtcEngineDelegate#rtcEngine:didOfflineOfUid:reason:} 回调通知。  <br>
 */
- (BOOL)setClientRole:(ByteRtcClientRole)role;

/**
 *  @type api
 *  @region 房间管理
 *  @brief 获取当前用户角色。  <br>
 *  @return 当前用户角色，详见 ByteRtcClientRole{@link #ByteRtcClientRole} 枚举类型。  <br>
 */
- (ByteRtcClientRole)clientRole;

/**
 *  @type api
 *  @region 房间管理
 *  @brief 加入房间。用户调用此方法加入房间，在一个房间内的用户间可以相互通话。  <br>
 *         用户调用 sharedEngineWithAppId:delegate:{@link #sharedEngineWithAppId:delegate:} 创建 RTC 引擎后，需调用此方法加入房间实现同其他用户进行音视频通话。如果用户调用此方法加入房间，则后续重复调用此方法均会失败，用户必须调用 leaveChannel:{@link #leaveChannel:} 退出当前房间后，才能加入下一个房间。  <br>
 *         用户调用此方法加入房间成功后，会收到 rtcEngine:didJoinedOfUid:elapsed:{@link #ByteRtcEngineDelegate#rtcEngine:didJoinedOfUid:elapsed:} 回调通知。  <br>
 *  @param token 动态密钥，用于对登录用户进行鉴权验证。  <br>
 *         进入房间需要携带 Token。测试时可使用控制台生成临时 Token ，正式上线需要使用密钥 SDK 在您的服务端生成并下发 Token 。  <br>
 *  @param roomId 房间ID ，用户调用此接口加入的房间的房间ID 。  <br>
 *         房间ID 为最大长度为128字节的非空字符串，支持的字符集范围为:  <br>
 *             1. 26个大写字母 A ~ Z 。  <br>
 *             2. 26个小写字母 a ~ z 。  <br>
 *             3. 10个数字 0 ~ 9 。  <br>
 *             4. 下划线"_", at符"@", 减号"-"。  <br>
 *  @param info 预留参数。  <br>
 *  @param userId 用户ID ，用户调用此接口加入的房间时使用的用户ID 。  <br>
 *         用户ID 为最大长度为128字节的非空字符串，支持的字符集范围为:  <br>
 *             1. 26个大写字母 A ~ Z 。  <br>
 *             2. 26个小写字母 a ~ z 。  <br>
 *             3. 10个数字 0 ~ 9 。  <br>
 *             4. 下划线"_", at符"@", 减号"-"。  <br>
 *  @return 方法调用结果。  <br>
 *         +  0: 成功  <br>
 *         + -1: roomId 为空，失败  <br>
 *         + -2: userId 为空，失败  <br>
 *  @notes  <br>
 *        + 使用不同 App ID 的 App 是不能互通的。  <br>
 *        + 请务必保证生成 Token 使用的 App ID 和创建引擎时使用的 App ID 相同，否则会导致加入房间失败。  <br>
 *        + 用户加入房间成功后，在本地网络状况不佳的情况下，SDK 可能会与服务器失去连接，此时 SDK 将会自动重连。重连成功后，本地会收到 rtcEngine:didRejoinChannel:withUid:elapsed:{@link #ByteRtcEngineDelegate#rtcEngine:didRejoinChannel:withUid:elapsed:} 回调通知。  <br>
 *        + 房间模式（房间模式参考 setChannelProfile:{@link #setChannelProfile:} ）为通话模式下的用户或直播、游戏、云游戏模式下用户角色（用户角色参考 setClientRole:{@link #setClientRole:} ）为主播、观众的用户加入房间成功后，远端用户会收到 rtcEngine:didJoinChannel:withUid:elapsed:{@link #ByteRtcEngineDelegate#rtcEngine:didJoinChannel:withUid:elapsed:} 回调通知。  <br>
 *        + 同一个 App ID 的同一个房间内，每个用户的用户ID 必须是唯一的。如果两个用户的用户ID 相同，则后加入房间的用户会将先加入房间的用户踢出房间，并且先加入房间的用户会收到 rtcEngine:didOccurError:{@link #ByteRtcEngineDelegate#rtcEngine:didOccurError:} 回调通知，错误类型为重复登录 BRERR_DUPLICATE_LOGIN{@link #BRERR_DUPLICATE_LOGIN} 。  <br>
 */
- (int)joinChannelByKey:(NSString * _Nullable)token channelName:(NSString * _Nonnull)roomId info:(NSString * _Nullable)info uid:(NSString * _Nonnull)userId;

/**
 *  @hidden
 *  @type api
 *  @region 频道管理
 *  @brief 加入频道。
 *  @param channelKey 用户对应的key。测试环境下可设置为nil
 *  @param channelName 加入的频道的名称
 *  @param info 合流转推信息，不需要此功能时，置为nil
 *  @param uid 用户ID。在一个Channel中用户ID必须唯一
 *  @param traceid 额外的用户标记（仅用于事件中区分用户）
 *  @return 0：方法调用成功；
 *          <0: 方法调用失败
 *  @notes 该方法让用户加入通话频道，在同一个频道内的用户可以互相通话，多个用户加入同一个频道，可以群聊。
 *       使用不同App ID的应用程序是不能互通的。如果已在通话中，用户必须调用 leaveChannel:{@link #leaveChannel:} 退出当前通话，才能进入下一个频道。
 *       SDK在通话中使用iOS系统的AVAudioSession共享对象进行录音和播放，应用程序对该对象的操作可能会影响SDK的音频相关功能。
 *       加入房间成功后，会触发 rtcEngine:didJoinChannel:withUid:elapsed:{@link #ByteRtcEngineDelegate#rtcEngine:didJoinChannel:withUid:elapsed:} 回调。
 */
- (int)joinChannelByKey:(NSString * _Nullable)channelKey
            channelName:(NSString * _Nonnull)channelName
                   info:(NSString * _Nullable)info
                    uid:(NSString * _Nonnull)uid
                traceid:(NSString * _Nonnull)traceid;

/**
 *  @type api
 *  @region 房间管理
 *  @brief 离开房间。  <br>
 *         用户调用此方法离开房间，结束通话过程，释放所有通话相关的资源。  <br>
 *         调用 joinChannelByKey:channelName:info:uid:{@link #joinChannelByKey:channelName:info:uid:} 方法加入房间后，在通话结束时必须调用此方法结束通话，否则无法开始下一次通话。无论当前是否在房间中，都可以调用此方法。重复调用此方法不会有负面影响。  <br>
 *         此方法是异步操作，调用返回时并没有真正退出房间。真正退出房间后，SDK 会执行调用此方法时传入的 Block 块。  <br>
 *  @param leaveChannelBlock 离开房间完成后执行的 Block 块。Block 的输入参数为加入房间到离开房间过程间的统计信息，详见 ByteRtcStats{@link #ByteRtcStats} 类型。  <br>
 *  @return 方法调用结果。  <br>
 *         +  0: 方法调用成功  <br>
 *         + <0: 方法调用失败  <br>
 *  @notes  <br>
 *        + 通信模式下的用户和其他房间模式下的主播、 观众角色的用户离开房间后，远端用户会收到 rtcEngine:didOfflineOfUid:reason:{@link #ByteRtcEngineDelegate#rtcEngine:didOfflineOfUid:reason:} 回调通知。  <br>
 *        + 如果调用 leaveChannel 后立即调用销毁引擎，SDK 将无法执行作为参数传入的 Block 块。  <br>
 */
- (int)leaveChannel:(void(^ _Nullable)(ByteRtcStats * _Nonnull stat))leaveChannelBlock;

/**
 *  @type api
 *  @region 房间管理
 *  @brief 更新 Token。  <br>
 *         Token 有一定的有效期，当 Token 过期时，用户需调用此方法更新房间的 Token 信息。  <br>
 *         用户调用 joinChannelByKey:channelName:info:uid:{@link #joinChannelByKey:channelName:info:uid:} 方法加入房间时，如果使用了过期的 Token 将导致加入房间失败，并会收到 rtcEngine:didOccurError:{@link #ByteRtcEngineDelegate#rtcEngine:didOccurError:} 回调通知，回调错误码为 BRERR_INVALID_TOKEN{@link #BRERR_INVALID_TOKEN} 。此时需要重新获取 Token ，并调用此方法更新 Token。  <br>
 *  @param token 更新的动态密钥。Token 用于对登录用户进行鉴权验证。  <br>
 *  @return 方法调用结果。  <br>
 *         +  0: 方法调用成功。  <br>
 *         + <0: 方法调用失败。  <br>
 *  @notes <br>
 *        + 如果用户因 Token 过期导致加入房间失败，则调用此方法更新 Token 后 SDK 会自动重新加入房间，而不需要用户自己调用 joinChannelByKey:channelName:info:uid:{@link #joinChannelByKey:channelName:info:uid:} 方法。  <br>
 *        + Token过期时，如果已经加入房间成功，则不会受到影响。Token 过期的错误会在下一次使用过期的 Token 加入房间或由于本地网络状况不佳导致断网重连入房间时通知给用户。  <br>
 */
- (int)renewChannelKey:(NSString * _Nonnull)token;

/**
 * @type api
 * @region 引擎管理
 * @brief 获取 SDK 内各种错误码、警告码的描述文字。
 * @param code  <br>
 *        通过 rtcEngine:didOccurWarning:{@link #rtcEngine:didOccurWarning:} 和 rtcEngine:didOccurError:{@link #rtcEngine:didOccurError:} 回调获得的值，
 *        具体可以参考 ByteRtcWarningCode{@link #ByteRtcWarningCode} 和 ByteRtcErrorCode{@link #ByteRtcErrorCode} 。
 * @return 描述文字。
 */
+ (NSString * _Nonnull)getErrorDescription:(NSInteger)code;

#pragma mark Core Audio Methods
/**
 *  -----------------------------------------------------------------------------
 *  @name 音频核心方法
 *  -----------------------------------------------------------------------------
 */

/**
 * @type api
 * @region 音频管理
 * @brief 开启/关闭本地音频采集。  <br>
 *        调用该方法后，房间中的其他用户会收到 rtcEngine:didLocalAudioEnabled:byUid:{@link #rtcEngine:didLocalAudioEnabled:byUid:} 事件回调。
 * @param enabled YES:开启本地音频采集（默认）; NO:关闭本地音频采集
 * @return  方法调用结果  <br>
 *        + 0：方法调用成功  <br>
 *        + <0：方法调用失败  <br>
 * @notes  <br>
 *       + 关闭本地音频采集后，依然会编码发送静音包，因此依然会有少量 CPU 和网络带宽开销。  <br>
 *       + 该方法在 joinChannelByKey:channelName:info:uid:{@link #joinChannelByKey:channelName:info:uid:} 前可以调用。  <br>
 *       + 该方法设置的是内部引擎为启用或禁用状态，在 leaveChannel:{@link #leaveChannel:} 后仍然有效。  <br>
 */
- (int)enableLocalAudio:(BOOL)enabled;

 /**
 * @type api
 * @region 音频管理
 * @brief 设置音频场景类型。<br>
 *        你可以根据你的应用所在场景，选择合适的音频场景类型。
 *        选择音频场景后，RTC 会自动根据客户端音频路由和发布订阅状态，适用通话音量/媒体音量。<br>
 *        在进房前和进房后设置均可生效。
 * @param [in] audioScenario 音频场景类型，
 *        参见 ByteRtcAudioScenarioType{@link #ByteRtcAudioScenarioType}
 * @notes 
 *        + 通话音量更适合通话，会议等对信息准确度更高的场景。通话音量会激活系统硬件信号处理，使通话声音会更清晰。同时，音量无法降低到 0。<br>
 *        + 媒体音量更适合娱乐场景，因其声音的表现力会更强。媒体音量下，音量最低可以降低到 0。
 */
- (void)setAudioScenario:(ByteRtcAudioScenarioType)audioScenario;







/**
 * @type api
 * @region 音频管理
 * @brief 静音本地音频流
 * @param mute YES: 静音本地音频流；NO: 关闭静音本地音频流（默认）
 * @return  方法调用结果  <br>
 *        + 0：方法调用成功  <br>
 *        + <0：方法调用失败  <br>
 * @notes  <br>
 *       + 该方法静音本地音频流。调用该方法后，房间中的其他用户会收到 rtcEngine:didAudioMuted:byUid:{@link #rtcEngine:didAudioMuted:byUid:} 的回调。  <br>
 *       + 本方法只是静音本地流，并未关闭本地音频采集设备。
 */
- (int)muteLocalAudioStream:(BOOL)mute;


/**
 * @type api
 * @region 音频管理
 * @brief 静音/取消静音指定用户的音频流。
 * @param uid 指定远端用户的ID
 * @param mute YES:静音指定用户音频流；NO:取消对指定用户音频流的静音
 * @return  方法调用结果  <br>
 *        + 0：方法调用成功  <br>
 *        + <0：方法调用失败  <br>
 */
- (int)muteRemoteAudioStream:(NSString * _Nonnull)uid mute:(BOOL)mute;

/**
 * @type api
 * @region 音频管理
 * @brief 静音/取消静音所有音频流
 * @param mute YES: 静音所有音频流；NO: 取消静音所有音频流
 * @return  方法调用结果  <br>
 *        + 0：方法调用成功  <br>
 *        + <0：方法调用失败  <br>
 * @notes 本方法只控制本地是否静音远端音频流，并不能控制远端音频设备的采集发送功能
 */
- (int)muteAllRemoteAudioStreams:(BOOL)mute;

/**
 * @type api
 * @region 音频管理
 * @brief 设置是否默认静音所有远端音频流
 * @param mute YES: 默认静音所有远端音频流；NO: 默认取消静音所有远端音频流（默认）
 * @notes  <br>
 *       + 如果在加入房间前调用此 API，进房后对所有远端用户音频流生效  <br>
 *       + 如果在加入房间后调用此 API，则只对在调用 API 之后进房的远端用户的音频流生效  <br>
 *       + 对于已静音的远端用户音频流，如果想要取消静音，请参考 muteRemoteAudioStream{@link #muteRemoteAudioStream:mute:}
 */
- (void)setDefaultMuteAllRemoteAudioStreams:(BOOL)mute;

/**
 * @type api
 * @region 音频管理
 * @brief 开启/关闭发言者音量提示。
 * @param interval 指定音量提示的时间间隔; <=0: 禁用音量提示功能；>0 : 提示间隔，单位为毫秒(ms)。建议设置到大于 200 毫秒。少于 10 毫秒时，行为未定义。
 * @param smooth 该参数未使用
 * @return  方法调用结果  <br>
 *        + 0：方法调用成功  <br>
 *        + <0：方法调用失败  <br>
 * @notes 开启或禁用发言者音量提示功能。功能开启时以一定时间间隔通过音量提示回调 tcEngine:reportAudioVolumeIndicationOfSpeakers:totalVolume:{@link #rtcEngine:reportAudioVolumeIndicationOfSpeakers:totalVolume:} 通知房间内用户的音量。
 */
- (int)enableAudioVolumeIndication:(NSInteger)interval
                            smooth:(NSInteger)smooth;

/**
 * @type api
 * @region 音频管理
 * @brief 调节录音音量。
 * @param volume 录音音量，可在 0~400 范围内进行调节  <br>
 *              + 0：静音  <br>
 *              + 100：原始音量  <br>
 *              + 400: 最大可为原始音量的 4 倍(自带溢出保护)  <br>
 * @return  方法调用结果  <br>
 *        + 0：方法调用成功  <br>
 *        + <0：方法调用失败  <br>
 * @notes 为保证更好的通话质量，建议将 volume 值设为 [0,100]
 */
- (int)adjustRecordingSignalVolume:(NSInteger)volume;

/**
 * @type api
 * @region 音频管理
 * @brief 调节本地播放的所有远端用户音量
 * @param volume 播放音量，可在 0~400 范围内进行调节  <br>
 *              + 0：静音  <br>
 *              + 100：原始音量  <br>
 *              + 400: 最大可为原始音量的 4 倍(自带溢出保护)
 * @return  方法调用结果  <br>
 *        + 0：方法调用成功  <br>
 *        + <0：方法调用失败  <br>
 * @notes  <br>
 *       + 该方法调节的是本地播放的所有远端用户混音后的音量  <br>
 *       + 为保证更好的通话质量，建议将 volume 值设为 [0,100]
 */
- (int)adjustPlaybackSignalVolume:(NSInteger)volume;

#pragma mark Core Video Methods
/**-----------------------------------------------------------------------------
 *  @name 视频核心方法
 * -----------------------------------------------------------------------------
 */

/**
 *  @type api
 *  @region 自定义视频采集渲染
 *  @brief 设置本地视频外部渲染器。
 *  @param videoRenderer 外部渲染器，具体参照 ByteVideoSinkProtocol{@link #ByteVideoSinkProtocol}
 *  @return  <br>
 *         + 0：方法调用成功  <br>
 *         + <0：方法调用失败  <br>
 */
- (int)setLocalVideoRenderer:(id<ByteVideoSinkProtocol> _Nullable)videoRenderer;

/**
 *  @type api
 *  @region 自定义视频采集渲染
 *  @brief 设置本地视频外部渲染器。
 *  @param videoRenderer 外部渲染器，具体参照 ByteVideoSinkProtocol{@link #ByteVideoSinkProtocol}
 *  @param roomId 房间ID
 *  @param userId 用户ID
 *  @return  <br>
 *         + 0：方法调用成功  <br>
 *         + <0：方法调用失败  <br>
 */
- (int)setLocalVideoRenderer:(id<ByteVideoSinkProtocol> _Nullable)videoRenderer
                   forRoomId:(NSString * _Nonnull)roomId
                   forUserId:(NSString * _Nonnull)userId;


/**
 *  @type api
 *  @region 自定义视频采集渲染
 *  @brief 设置特定远端用户的外部渲染器。
 *  @param videoRenderer 外部渲染器，具体参照 ByteVideoSinkProtocol{@link #ByteVideoSinkProtocol}
 *  @param roomId 房间ID
 *  @param userId 用户ID
 *  @return  <br>
 *         + 0：方法调用成功  <br>
 *         + <0：方法调用失败  <br>
 */
- (int)setRemoteVideoRenderer:(id<ByteVideoSinkProtocol> _Nullable)videoRenderer
                    forRoomId:(NSString * _Nonnull)roomId
                    forUserId:(NSString * _Nonnull)userId;

/**
 *  @type api
 *  @region 自定义视频采集渲染
 *  @brief 设置特定远端用户的外部渲染器。
 *  @param videoRenderer 外部渲染器，具体参照 ByteVideoSinkProtocol{@link #ByteVideoSinkProtocol}
 *  @param userId 用户ID
 *  @return  <br>
 *         + 0：方法调用成功  <br>
 *         + <0：方法调用失败  <br>
 */
- (int)setRemoteVideoRenderer:(id<ByteVideoSinkProtocol> _Nullable)videoRenderer
                    forUserId:(NSString * _Nonnull)userId;

/**
 *  @type api
 *  @region 自定义视频采集渲染
 *  @brief 设置远端屏幕共享的外部渲染器。
 *  @param screenRenderer
 *         外部渲染器，具体参照 ByteVideoSinkProtocol{@link #ByteVideoSinkProtocol}
 *  @param roomId
 *         房间ID
 *  @param userId
 *         用户ID
 *  @return  <br>
 *         + 0：方法调用成功  <br>
 *         + -1：方法调用失败  <br>
 *  @notes
 *         在应用开发中，通常在应用收到 rtcEngine:firstRemoteScreenFrameOfUid:size:elapsed:{@link #ByteRtcEngineDelegate#rtcEngine:firstRemoteScreenFrameOfUid:size:elapsed:} 事件后调用该方法进行远端视频设置。
 */
- (int)setupRemoteScreenRenderer:(id<ByteVideoSinkProtocol> _Nullable)screenRenderer
                       forRoomId:(NSString * _Nonnull)roomId
                       forUserId:(NSString * _Nonnull)userId;

/**
 *  @type api
 *  @region 自定义视频采集渲染
 *  @brief 设置远端屏幕共享的外部渲染器。
 *  @param screenRenderer
 *         外部渲染器，具体参照 ByteVideoSinkProtocol{@link #ByteVideoSinkProtocol}
 *  @param userId
 *         用户ID
 *  @return  <br>
 *         + 0：方法调用成功  <br>
 *         + -1：方法调用失败  <br>
 *  @notes
 *         在应用开发中，通常在应用收到 firstRemoteScreenFrameOfUid{@link #ByteRtcEngineDelegate#rtcEngine:firstRemoteScreenFrameOfUid:size:elapsed:} 事件后调用该方法进行远端视频设置
 */
- (int)setupRemoteScreenRenderer:(id<ByteVideoSinkProtocol> _Nullable)screenRenderer
                       forUserId:(NSString * _Nonnull)userId;

/**
 *  @type api
 *  @region 视频管理
 *  @brief 设置本地视频属性。
 *  @param  videoStreamDescriptions 设置的视频尺寸，视频帧率，视频码率，详见 VideoStreamDescription{@link #VideoStreamDescription}。  <br>
 *        + 若选取的帧率为 5 FPS，则推算码率为<视频属性 (Profile) 参考表>推荐码率除以 2  <br>
 *        + 若选取的帧率为 15 FPS，则推算码率为<视频属性 (Profile) 参考表>推荐码率
 *        + 若选取的帧率为 30 FPS，则推算码率为<视频属性 (Profile) 参考表>码率乘以 1.5  <br>
 *        + 若选取其余帧率，等比例推算即可  <br>
 *        + 若设置的视频码率超出合理范围，SDK 会自动按照合理区间处理码率  <br>
 *  @return  <br>
 *         + 0：方法调用成功  <br>
 *         + <0：方法调用失败  <br>
 */
- (VideoStreamState)setVideoProfiles:(NSArray <VideoStreamDescription *> * _Nullable)videoStreamDescriptions;

/**
 *  @type api
 *  @region 视频管理
 *  @brief 设置本地视频属性。
 *  @param videoStreamDescriptions 设置的视频尺寸，视频帧率，视频码率，详见 VideoStreamDescription{@link #VideoStreamDescription}。
 *  @param mode 旋转模式，具体参照 ByteVideoOutputOrientationMode{@link #ByteVideoOutputOrientationMode} 定义 （目前仅支持ByteVideoOutputOrientationModeAdaptative）
 *  @return  <br>
 *         + 0：方法调用成功  <br>
 *         + <0：方法调用失败  <br>
 */

- (VideoStreamState)setVideoProfiles:(NSArray <VideoStreamDescription *> * _Nullable)videoStreamDescriptions orientationMode:(ByteVideoOutputOrientationMode)mode;

/**
 *  @type api
 *  @region 视频管理
 *  @brief 该方法设置本地视频显示信息。
 *  @param local 视频属性
 *  @return  <br>
 *         + 0：方法调用成功  <br>
 *         + <0：方法调用失败  <br>
 *  @notes 应用程序通过调用此接口绑定本地视频流的显示视窗 (view)，并设置视频显示模式。在应用程序开发中，通常在初始化后调用该方法进行本地视频设置，然后再加入频道。
 *       退出频道后，绑定仍然有效，如果需要解除绑定，可以指定空 (NULL) View 调用 setupLocalVideo {@link #setupLocalVideo:}。
 */
- (int)setupLocalVideo:(ByteRtcVideoCanvas * _Nullable)local;

/**
 *  @type api
 *  @region 视频管理
 *  @brief 设置远端视频显示属性。
 *  @param remote 视频属性
 *  @return  <br>
 *         + 0：方法调用成功  <br>
 *         + <0：方法调用失败  <br>
 *  @notes 该方法绑定远程用户和显示视图，即设定 uid 指定的用户用哪个视图显示。调用该接口时需要指定远程视频的 uid，一般可以在进频道前提前设置好。
 *       如果应用程序不能事先知道对方的 uid，可以在 APP 收到 rtcEngine:didJoinedOfUid:elapsed:{@link #rtcEngine:didJoinedOfUid:elapsed:} 事件时设置。
 *       如果启用了视频录制功能，视频录制服务会做为一个哑客户端加入频道，因此其他客户端也会收到它的 rtcEngine:didJoinedOfUid:elapsed:{@link #rtcEngine:didJoinedOfUid:elapsed:} 事件。
 *       APP 不应给它绑定视图（因为它不会发送视频流），如果 APP 不能识别哑客户端，可以在 firstRemoteVideoFrameOfUid{@link #ByteRtcEngineDelegate#rtcEngine:firstRemoteVideoFrameOfUid:size:elapsed:} 事件时再绑定视图。解除某个用户的绑定视图可以把 view 设置为空。
 *       退出频道后，SDK 会把远程用户的绑定关系清除掉。
 */
- (int)setupRemoteVideo:(ByteRtcVideoCanvas * _Nonnull)remote;

/**
 *  @type api
 *  @region 视频管理
 *  @brief 设置远端屏幕共享视图，即用户ID指定的用户用的屏幕视图显示。调用该接口时需要指定远程共享屏幕流的用户ID，一般可以在进频道前提前设置好。
 *  @param screen
 *         视频属性
 *  @return  <br>
 *         + 0：方法调用成功  <br>
 *         + -1：方法调用失败  <br>
 *  @notes
 *         在应用开发中，通常在应用收到 firstRemoteScreenFrameOfUid{@link #ByteRtcEngineDelegate#rtcEngine:firstRemoteScreenFrameOfUid:size:elapsed:} 事件后调用该方法进行远端视频设置
 */
- (int)setupRemoteScreen:(ByteRtcVideoCanvas * _Nonnull)screen;

/**
 * @type api
 * @region 视频管理
 * @brief 开启视频预览，视频预览默认为关闭状态。
 * @return  <br>
 *        + 0：方法调用成功  <br>
 *        + <0：方法调用失败  <br>
 * @notes  <br>
 *       + 只有同时调用 enableLocalVideo:{@link #enableLocalVideo:}(true) 与 startPreview{@link #startPreview} 才会打开视频采集设备。  <br>
 *       + 只要调用 enableLocalVideo:{@link #enableLocalVideo:}(false) 或 stopPreview{@link #stopPreview} 的任意一个就会关闭视频采集设备。  <br>
 *       + 该方法在 joinChannelByKey:channelName:info:uid:{@link #joinChannelByKey:channelName:info:uid:} 前可以调用。  <br>
 *       + 该方法设置的视频预览状态，在 leaveChannel:{@link #leaveChannel:} 后仍然有效。  <br>
 *       + 调用 leaveChannel:{@link #leaveChannel:} 退出频道，并不会关闭视频预览。如需关闭视频预览，请调用 stopPreview{@link #stopPreview}  <br>
 */
- (int)startPreview;

/**
 * @type api
 * @region 视频管理
 * @brief 关闭视频预览，视频预览默认为关闭状态。
 * @return  <br>
 *        + 0：方法调用成功  <br>
 *        + <0：方法调用失败  <br>
 * @notes  <br>
 *       + 只有同时调用 enableLocalVideo:{@link #enableLocalVideo:}(true) 与 startPreview{@link #startPreview} 才会打开视频采集设备。  <br>
 *       + 只要调用 enableLocalVideo:{@link #enableLocalVideo:}(false) 或 stopPreview{@link #stopPreview} 的任意一个就会关闭视频采集设备。  <br>
 *       + 该方法在 joinChannelByKey:channelName:info:uid:{@link #joinChannelByKey:channelName:info:uid:} 前可以调用。  <br>
 *       + 该方法设置的视频预览状态，在 leaveChannel:{@link #leaveChannel:} 后仍然有效。  <br>
 */
- (int)stopPreview;

/**
 * @type api
 * @region 视频管理
 * @brief 该方法开启或关闭本地视频采集。默认为开启状态。  <br>
 *        调用该方法后，房间中的其他用户会收到 rtcEngine:didLocalVideoEnabled:byUid:{@link #rtcEngine:didLocalVideoEnabled:byUid:} 的回调。
 *  @param  enabled 是否开启本地视频采集  <br>
 *        + YES：开启本地视频采集  <br>
 *        + NO：关闭本地视频采集  <br>
 * @return  <br>
 *        + 0：方法调用成功  <br>
 *        + <0：方法调用失败  <br>
 * @notes  <br>
 *       + 关闭本地视频采集后，不会编码发送视频数据。  <br>
 *       + 只有同时调用 enableLocalVideo:{@link #enableLocalVideo:}(true) 与 startPreview{@link #startPreview} 才会打开视频采集设备。  <br>
 *       + 只要调用 enableLocalVideo:{@link #enableLocalVideo:}(false) 或 stopPreview{@link #stopPreview} 的任意一个就会关闭视频采集设备。  <br>
 *       + 该方法在 joinChannelByKey:channelName:info:uid:{@link #joinChannelByKey:channelName:info:uid:} 前可以调用。  <br>
 *       + 该方法设置的是内部引擎为启用或禁用状态，在 leaveChannel:{@link #leaveChannel:} 后仍然有效。  <br>
 */
- (int)enableLocalVideo:(BOOL)enabled;

/**
 *  @type api
 *  @region 视频管理
 *  @brief 停止/开启本地视频流发送。调用该方法后，房间中的其他用户会收到rtcEngine:didVideoMuted:byUid:{@link #rtcEngine:didVideoMuted:byUid:} 回调
 *  @param mute YES:开启本地视频发送；NO:关闭本地视频发送
 *  @return  <br>
 *         + 0：方法调用成功  <br>
 *         + <0：方法调用失败  <br>
 */
- (int)muteLocalVideoStream:(BOOL)mute;

/**
 *  @type api
 *  @region 视频管理
 *  @brief 停止/开启接收指定远端用户的视频流。
 *  @param uid 指定用户的用户ID
 *  @param mute YES:停止指定的远端视频流；NO:开启指定的远端视频流
 *  @return  <br>
 *         + 0：方法调用成功  <br>
 *         + <0：方法调用失败  <br>
 */
- (int)muteRemoteVideoStream:(NSString * _Nonnull)uid
                        mute:(BOOL)mute;

/**
 *  @type api
 *  @region 视频管理
 *  @brief 停止/开启接收所有远端用户的视频流。
 *  @param mute YES:停止接收远端视频流；NO:开启接收远端视频流
 *  @return  <br>
 *         + 0：方法调用成功  <br>
 *         + <0：方法调用失败  <br>
 */
- (int)muteAllRemoteVideoStreams:(BOOL)mute;

/**
 *  @type api
 *  @region 视频管理
 *  @brief 设置默认禁止/开启远端用户的视频流。
 *  @param mute YES:默认禁止远端用户的视频流；NO:默认开启远端用户的视频流
 *  @notes 设置的默认静音仅影响未来到达的视频流，对已订阅的远端流无影响
 */
- (void)setDefaultMuteAllRemoteVideoStreams:(BOOL)mute;

/**
 *  @type api
 *  @region 视频管理
 *  @brief 设置本地视频镜像.该方法用于开启或关闭本地视频镜像，默认值为关闭（ByteVideoMirrorModeDisabled）。
 *  @param mode 视频镜像模式，类型为枚举类型 ByteVideoMirrorMode{@link #ByteVideoMirrorMode}
 *  @return  <br>
 *         + 0：方法调用成功  <br>
 *         + <0：方法调用失败  <br>
 */
- (int)setLocalVideoMirrorMode:(ByteVideoMirrorMode) mode;

/**
 *  @type api
 *  @region 视频管理
 *  @brief 获取本地视频镜像状态
 *  @return  当前镜像状态  <br>
 *         + true：镜像为打开状态  <br>
 *         + false：镜像为关闭状态  <br>
 */
- (bool)isLocalVideoMirrorOn;

/**
 *  @type api
 *  @region 视频管理
 *  @brief 切换摄像头。
 *  @return  <br>
 *         + 0：方法调用成功  <br>
 *         + <0：方法调用失败  <br>
 */
- (int)switchCamera;

/**
 * @type api
 * @region 视频管理
 * @brief 视频图像分割，替换背景
 * @param mode 背景模式，用于设置预制背景，是否虚化等 详见 BackgroundMode{@link #BackgroundMode}
 * @param divideModel 选择使用哪种分割模型， 分割模型类型详见 DivideModel{@link #DivideModel}
 * @return  <br>
 *        + 0：方法调用成功  <br>
 *        + <0：方法调用失败  <br>
 */
- (int) replaceBackground:(BackgroundMode)mode
          withDivideModel:(DivideModel)divideModel;

/**
 * @type api
 * @region 视频管理
 * @brief 检查当前版本是否支持视频特效
 * @return:
 *       0: 不支持
 *       >0: 支持视频特效
 */
- (int) checkVideoEffectSupport;

/**
 * @type api
 * @region 视频管理
 * @brief 视频特效许可证检查
 * @param licenseFile 许可证文件绝对路径
 * @return
 *      0: 许可证验证成功
 *      !0: 许可证验证验证失败
 * @notes enableVideoEffect{@link #enableVideoEffect:}开始使用视频特效前，需要先调用这个方法进行许可证验证
 */
- (int) checkVideoEffectLicense:(NSString * _Nonnull)licenseFile;

/**
 * @type api
 * @region 视频管理
 * @brief 开启关闭视频特效
 * @param enabled 是否开启特效，true: 开启，false: 关闭
 * @return
 *      0: 成功
 *      !0: 失败。
 * @notes checkVideoEffectLicense{@link #checkVideoEffectLicense:}setVideoEffectAlgoModelPath{@link #setVideoEffectAlgoModelPath:}后调用此方法
 */
- (int) enableVideoEffect:(BOOL)enabled;

/**
 * @type api
 * @region 视频管理
 * @brief 设置视频特效算法模型路径
 * @param modelPath 模型路径
 */
- (void) setVideoEffectAlgoModelPath:(NSString * _Nonnull)modelPath;

/**
 * @type api
 * @region 视频管理
 * @brief 设置特效包，支持同时设置多个特效包
 * @param effectNodePaths 特效包路径数组
 */
- (void) setVideoEffectNodes:(NSArray <NSString *> *_Nonnull)effectNodePaths;

/**
 * @type api
 * @region 视频管理
 * @brief 增加特效包，支持同时增加多个特效包
 * @param effectNodePaths 要追加的特效包路径数组
 */
- (void) addVideoEffectNodes:(NSArray <NSString *> *_Nonnull)effectNodePaths;

/**
 * @type api
 * @region 视频管理
 * @brief 移除特效包，支持同时移除多个特效包
 * @param effectNodePaths  要移除的特效包路径数组
 */
- (void) removeVideoEffectNodes:(NSArray <NSString *> *_Nonnull)effectNodePaths;

/**
 * @type api
 * @region 视频管理
 * @brief 设置特效强度
 * @param nodePath  特效包路径
 * @param nodeKey  需要设置的键名称
 * @param nodeValue  要设置的强度值。取值范围[0,1] ，超出范围时设置无效
 * @notes nodeKey 的取值请参考特效包的参数说明文件
*/
- (void) updateVideoEffectNode:(NSString * _Nonnull)nodePath nodeKey:(NSString * _Nonnull)nodeKey  nodeValue:(float) nodeValue;

/**
 * @type api
 * @region  视频管理
 * @brief 设置颜色滤镜
 * @param resPath  滤镜资源包绝对路径
 */
- (void) setVideoEffectColorFilter:(NSString * _Nonnull)resPath;

/**
 * @type api
 * @region 视频管理
 * @brief 设置颜色滤镜强度
 * @param intensity  滤镜强度。取值范围[0,1] ，超出范围时设置无效
 */
- (void) setVideoEffectColorFilterIntensity:(float) intensity;


#pragma mark - MediaMetadataData InnerVideoSource
/**
 * @type api
 * @region 视频数据回调
 * @brief 注册 metadata 观察者，用于接收或发送 metadata，底层通过在视频帧中添加 SEI 数据实现该功能。  <br>
 *        注册观察者后，发送的视频帧里面没有 SEI 信息， 会触发 videoFrameMediaMetaDataAtTime:{@link #videoFrameMediaMetaDataAtTime:} 回调。  <br>
 *        注册观察者后，接收的视频帧里面有 SEI 信息，会触发接收 receiveVideoFrameFromUID:withExtendedData:atTimestamp:{@link #receiveVideoFrameFromUID:withExtendedData:atTimestamp:} 回调。  <br>
 * @param [in] metadataObserver metadata 观察者，详见： ByteRtcEngineMediaMetadataObserver{@link #ByteRtcEngineMediaMetadataObserver}
 * @return  <br>
 *         + YES: 设置成功  <br>
 *         + NO: 设置失败  <br>
 * @notes  <br>
 *      + 使用视频自定义采集与渲染时，可以直接在视频帧中添加与获取 metadata，不建议使用本接口。
 *      + 本接口支持动态取消注册，将参数设置为 nullptr 取消注册。  <br>
 */
- (BOOL)setMediaMetadataObserver:(_Nullable id<ByteRtcEngineMediaMetadataObserver>) metadataObserver;

#pragma mark - VideoFrameObserver InnerVideoSource
/**
 * @hidden
 * @type api
 * @region 视频数据回调
 * @brief 注册视频数据回调观察者
 * @param frameObserver 视频数据回调的观察者对象，详见： ByteVideoFrameObserver{@link #ByteVideoFrameObserver} 。
 *        将参数设置为 nullptr 取消注册。
 * @return  <br>
 *        + YES： 设置成功
 *        + NO： 设置失败
 * @notes  <br>
 *       + 该方法可以在任意时间调用，建议在 joinChannelByKey:channelName:info:uid:{@link #joinChannelByKey:channelName:info:uid:} 前。
 *       + 将参数设置为 nullptr 取消注册。  <br>
*/
- (BOOL)setVideoFrameObserver:(_Nullable id<ByteVideoFrameObserver>) frameObserver;

#pragma mark Subscribe Controller Methods
/**-----------------------------------------------------------------------------
 *  @name 自定义订阅方法
 * -----------------------------------------------------------------------------
 */

/**
 *  @type api
 *  @region 房间管理
 *  @brief 开启/关闭自动订阅功能。  <br>
 *         用户调用此方法设置房间中是否开启自动订阅功能。SDK 默认开启自动订阅功能。<br>
 *         如需关闭自动订阅功能，建议在调用 joinChannelByKey:channelName:info:uid:{@link #joinChannelByKey:channelName:info:uid:} 方法加入房间前设置完成。  <br>
 *  @param audioMode 开启/关闭音频自动订阅功能。详见枚举类型 ByteSubscribeMode{@link #ByteSubscribeMode} 。  <br>
 *  @param videoMode 开启/关闭视频自动订阅功能。详见枚举类型 ByteSubscribeMode{@link #ByteSubscribeMode} 。  <br>
 *  @return 方法执行结果。  <br>
 *         + YES: 方法调用成功。  <br>
 *         +  NO: 方法调用失败。  <br>
 *  @notes <br>
 *        + SDK 提供两种订阅模式：1.自动订阅模式，开启自动订阅功能时，SDK 自动帮助用户订阅房间中所有其他用户发布的音视频流；2.手动订阅模式，关闭自动订阅功能时，SDK不会自动订阅房间内的音视频流，只通过 rtcEngine:onStreamAdd:{@link #ByteRtcEngineDelegate#rtcEngine:onStreamAdd:} 和 rtcEngine:didStreamRemoved:stream:reason:{@link #ByteRtcEngineDelegate#rtcEngine:didStreamRemoved:stream:reason:} 回调通知用户当前所在房间中有哪些音视频流，由用户根据自己的需要调用 subscribeStream:subscribeConfig:{@link #subscribeStream:subscribeConfig:} 方法手动订阅其他用户发布的音视频流。  <br>
 *        + SDK 可以分别对音频/视频设置订阅模式。  <br>
 */
- (BOOL)enableAutoSubscribe:(ByteSubscribeMode)audioMode videoMode:(ByteSubscribeMode)videoMode;

/**
 *  @type api
 *  @region 房间管理
 *  @brief 订阅指定的房间内远端音视频流。  <br>
 *         关闭自动订阅功能，使用手动订阅模式时用户调用此方法按需订阅房间中的音视频流。  <br>
 *         此方法仅在关闭自动订阅功能时生效。用户需在加入房间前调用 enableAutoSubscribe:{@link #enableAutoSubscribe:} 方法关闭自动订阅功能以使用手动订阅模式。  <br>
 *         订阅流失败时，SDK 会按失败原因回调 rtcEngine:didOccurError:{@link #ByteRtcEngineDelegate#rtcEngine:didOccurError:} 通知用户，具体错误可参考错误码 ByteRtcErrorCode{@link #ByteRtcErrorCode} 描述。  <br>
 *  @param userId 指定订阅的远端音视频流的发布用户的用户ID 。  <br>
 *  @param info 选择订阅配置，详见数据结构 SubscribeConfig{@link #SubscribeConfig} 。  <br>
 *  @notes <br>
 *        + 此方法仅支持订阅当前房间中的远端音视频流。如果指定的流在当前房间内不曾存在，则 SDK 不会订阅。  <br>
 *        + 用户调用 joinChannelByKey:channelName:info:uid:{@link #joinChannelByKey:channelName:info:uid:} 方法加入房间后：1.当房间内有新的音视频流发布时，本地会收到 rtcEngine:onStreamAdd:{@link #ByteRtcEngineDelegate#rtcEngine:onStreamAdd:} 回调通知；2.当房间内音视频流停止发布时，本地会收到 rtcEngine:didStreamRemoved:stream:reason:{@link #ByteRtcEngineDelegate#rtcEngine:didStreamRemoved:stream:reason:} 回调通知。通过这两个回调用户可以获得当前房间中的音视频流信息，并在需要时调用此方法订阅指定音视频流。  <br>
 */
- (void)subscribeStream:(NSString *_Nonnull)userId subscribeConfig:(SubscribeConfig *_Nonnull)info;

/**
 *  @type api
 *  @region 房间管理
 *  @brief 停止订阅指定的房间内远端音视频流。  <br>
 *         关闭自动订阅功能，使用手动订阅模式时用户调用此方法停止订阅已订阅的音视频流。  <br>
 *         此方法仅在关闭自动订阅功能时生效。用户需在加入房间前调用 enableAutoSubscribe:{@link #enableAutoSubscribe:} 方法关闭自动订阅功能以使用手动订阅模式。  <br>
 *  @param userId 指定订阅的远端音视频流的发布用户的用户ID。  <br>
 *  @param isScreen 订阅的流是否是屏幕共享流。  <br>
 *  @notes  <br>
 *        + 不管是否订阅了指定的远端音视频流，都可以调用此方法停止订阅。停止订阅的 streamId 无效或未订阅时，SDK不会做任何处理，没有负面影响。  <br>
 */
- (void)unSubscribeStream:(NSString *_Nonnull)userId isScreen:(BOOL)isScreen;

#pragma mark Audio Routing Controller
/**-----------------------------------------------------------------------------
 *  @name 音频播放路由
 * -----------------------------------------------------------------------------
 */

/**
 * @type api
 * @region 音频管理
 * @brief 设置音频播放设备为扬声器或者听筒，默认使用扬声器。
 *        音频播放设备发生变化时，会收到 rtcEngine:didAudioRouteChanged:{@link #rtcEngine:didAudioRouteChanged:} 回调。
 * @param enable  是否切换语音路由到扬声器。  <br>
 *              + true: 没有连接耳机或者蓝牙设备时，音频播放切换到扬声器。  <br>
 *              + false: 没有连接耳机或者蓝牙设备时，音频播放切换到听筒。  <br>
 * @return 方法调用结果  <br>
 *        + 0: 方法调用成功  <br>
 *        + <0: 方法调用失败  <br>
 * @notes  <br>
 *       + 该 API 适用于移动设备  <br>
 *       + 听筒是手机自带的音频播放设备，一般位于手机顶部，用于打电话。扬声器是手机自带的音频播放设备，一般用于外放。
 *       + 连接有线或者蓝牙音频播放设备时，音频从有线或者蓝牙音频播放设备播放。没有连接有线或者蓝牙音频播放设备时，音频才会从扬声器或者听筒播放。  <br>
 *       + 在通话过程中连接有线或者蓝牙音频播放设备时，会自动切换到有线或者蓝牙音频播放设备。  <br>
 *       + 在通话过程中移除有线或者蓝牙音频播放设备时，会根据本接口设置，自动切换到听筒或者扬声器。  <br>
 *       + 支持在通话前提前设置音频播放设备，也支持在通话过程中切换音频播放设备。  <br>
 */
- (int)setEnableSpeakerphone:(BOOL)enableSpeaker;

/**
 * @type api
 * @region 音频管理
 * @brief 查询扬声器启用状态
 * @return  扬声器开启状态  <br>
 *        + YES: 扬声器已开启，语音会输出到扬声器  <br>
 *        + NO: 扬声器未开启，语音会输出到非扬声器（听筒，耳机等）
 */
- (BOOL)isSpeakerphoneEnabled;

#pragma mark Combined to Push
/**-----------------------------------------------------------------------------
 *  @name 合流转推
 * -----------------------------------------------------------------------------
 */

/**
 *  @type api
 *  @region CDN 推流
 *  @brief 开启直播推流转码功能。  <br>
 *         此方法用于开启直播推流转码功能，并设置旁路推流的视频视图布局及音频属性等。  <br>
 *         直播推流转码功能开启时，会根据设置的视频视图布局和音频属性进行合流转码转成 rtmp 流并推送到设置的 CDN 。  <br>
 *         直播推流转码功能启动成功或失败时、推流过程中发生错误时，SDK 通过 rtcEngine:TransCodingWithUrl:errorCode:{@link #ByteRtcEngineDelegate#rtcEngine:TransCodingWithUrl:errorCode:} 回调事件通知用户对应的状态事件。  <br>
 *  @param transcoding 推流转码配置属性，详见 ByteRtcLiveTranscoding{@link #ByteRtcLiveTranscoding} 类型。  <br>
 *  @return 方法调用结果。  <br>
 *         +  0：方法调用成功  <br>
 *         + <0：方法调用失败  <br>
 *  @notes  <br>
 *        + 只有房间模式为直播模式，且用户角色为主播的用户才能调用此方法。  <br>
 */
- (int)enableLiveTranscoding:(ByteRtcLiveTranscoding * _Nonnull)transcoding;

/**
 *  @type api
 *  @region CDN 推流
 *  @brief 关闭直播推流转码功能。  <br>
 *  @return 方法调用结果。  <br>
 *         +  0：方法调用成功  <br>
 *         + <0：方法调用失败  <br>
 */
- (int)disableLiveTranscoding;


/**
 *  @type api
 *  @region CDN 推流
 *  @brief 设置视频流合流布局。  <br>
 *         此方法用于在直播推流转码功能开启时，更新旁路推流的视频合流布局属性。调用此方法前，用户需通过调用 enableLiveTranscoding:{@link #enableLiveTranscoding:} 方法开启直播推流转码功能。如果未开启直播推流转码功能，则调用此方法不生效。  <br>
 *  @param layout 视频合流布局属性，详见 ByteRtcLiveTranscoding{@link #ByteRtcLiveTranscoding} 类型。  <br>
 *  @return 方法调用结果。  <br>
 *         +  0：方法调用成功  <br>
 *         + <0：方法调用失败  <br>
 */
- (int)setVideoCompositingLayout:(ByteRtcVideoCompositingLayout * _Nonnull)layout;

/**
 *  @type api
 *  @region 云端渲染
 *  @brief 按照传入的布局信息开启云端渲染。 <br>
 *  @param rendingInfo 渲染功能相关参数。 <br>
 *  @return 方法调用结果。  <br>
 *         +  0: 方法调用成功  <br>
 *         + <0: 方法调用失败  <br>
*/
- (int)enableCloudRending:(NSString *_Nonnull)rendingInfo;

/**
 *  @type api
 *  @region 云端渲染
 *  @brief 按照传入的布局信息更新云端渲染。 <br>
 *  @param rendingInfo 渲染功能相关参数。 <br>
 *  @return 方法调用结果。  <br>
 *         +  0: 方法调用成功  <br>
 *         + <0: 方法调用失败  <br>
*/
- (int)updateCloudRending:(NSString *_Nonnull)rendingInfo;

/**
 *  @type api
 *  @region 云端渲染
 *  @brief 停止云端渲染。 <br>
 *  @return 方法调用结果。  <br>
 *         +  0: 方法调用成功  <br>
 *         + <0: 方法调用失败  <br>
*/
- (int)disableCloudRending;

#pragma mark External Video Data
/**-----------------------------------------------------------------------------
 *  @name 视频自采集
 * -----------------------------------------------------------------------------
 */

/**
 *  @type api
 *  @region 外部视频
 *  @brief 配置外部视频源。
 *  @param enable 是否使用外部源。YES: 使用外部源；NO: 不使用外部源(默认)
 *  @param useTexture 是否使用 Texture 作为输入。YES:使用 Texture 作为输入; NO:不适用 Texture 作为输入
 *  @param pushMode 外部视频源是否需要调用 pushExternalVideoFrame{@link #pushExternalVideoFrame:} 将视频帧主动推送给 SDK。YES:使用 push 模式; NO:不使用 push 模式
 *  @notes 如果使用了外部源，请在调用 startPreview{@link #startPreview} 之前调用此 API。
 */
- (void)setExternalVideoSource:(BOOL)enable useTexture:(BOOL)useTexture pushMode:(BOOL)pushMode;

/**
 *  @type api
 *  @region 自定义视频采集渲染
 *  @brief 推送外部视频帧。
 *  @param frame 该视频帧包含待 SDK 编码的视频数据
 *  @param pts CMTime
 *  @return  <br>
 *         + YES 推送成功  <br>
 *         + NO 推送失败  <br>
 *  @notes 使用外部推送视频帧，调用 setExternalVideoSource 开启外部视频源功能，详见setExternalVideoSource:useTexture:pushMode:{@link #setExternalVideoSource:useTexture:pushMode:}
 */
- (BOOL)pushExternalVideoFrame:(CVPixelBufferRef _Nonnull )frame time:(CMTime)pts;

/**
 *  @type api
 *  @region 自定义视频采集渲染
 *  @brief 推送外部视频帧。
 *  @param frame 该视频帧包含待 SDK 编码的视频数据
 *  @param pts CMTime
 *  @param rotation 当前视频角度
 *  @return  <br>
 *         + YES 推送成功  <br>
 *         + NO 推送失败  <br>
 *  @notes 使用外部推送视频帧，调用 setExternalVideoSource 开启外部视频源功能，详见setExternalVideoSource:useTexture:pushMode:{@link #setExternalVideoSource:useTexture:pushMode:}
 */
- (BOOL)pushExternalVideoFrame:(CVPixelBufferRef _Nonnull )frame time:(CMTime)pts rotation:(ByteVideoRotation)rotation;

/**
 *  @type api
 *  @region 自定义视频采集渲染
 *  @brief 推送外部视频帧。
 *  @param frame 该视频帧包含待 SDK 编码的视频数据
 *  @param pts CMTime
 *  @param rotation 当前视频角度
 *  @param extendedData 当前帧的扩展数据，没有的话就传空
 *  @param supplementoryInfo 附加信息，比如人脸位置等等
 *  @return  <br>
 *         + YES 推送成功  <br>
 *         + NO 推送失败  <br>
 */
- (BOOL)pushExternalVideoFrame:(CVPixelBufferRef _Nonnull )frame time:(CMTime)pts
                                                             rotation:(ByteVideoRotation)rotation
                                                         extendedData:(NSData* _Nullable)extendedData
                                                    supplementaryInfo:(NSData* _Nullable)supplementoryInfo;


/**
 *  @type api
 *  @region 自定义视频采集渲染
 *  @brief 推送外部视频帧，使用 ByteVideoFrame 进行封装。
 *  @param frame 该视频帧包含待SDK编码的视频数据，参考 ByteVideoFrame{@link #ByteVideoFrame}
 *  @return  <br>
 *         + YES 推送成功  <br>
 *         + NO 推送失败  <br>
 */
- (BOOL)pushExternalByteVideoFrame:(ByteVideoFrame * _Nonnull)frame;

#pragma mark External Audio Data
/**-----------------------------------------------------------------------------
 *  @name 音频自采集及渲染
 * -----------------------------------------------------------------------------
 */

/**
 * @type api
 * @region 自定义音频采集渲染
 * @brief 设置是否启用外部音频采集渲染。
 * @param  enable  <br>
 *       + YES: 启用自定义音频采集渲染
 *       + NO: 不启用自定义音频采集渲染
 * @param sampleRate  <br>
 *        音频采样率（单位HZ），可以设置的值有 8000，16000，32000，44100，48000
 * @param recordChannelNum 外部音频采集通道数，支持单通道（1）和双通道（2）
 * @param playoutChannelNum 外部音频渲染通道数，支持单通道（1）和双通道（2）
 * @return  方法调用结果  <br>
 *        + YES: 方法调用成功  <br>
 *        + NO: 方法调用失败  <br>
 * @notes  <br>
 *      + 该方法应该在 joinChannelByKey:channelName:info:uid:{@link #ByteRtcEngineKit#joinChannelByKey:channelName:info:uid:} 前使用。  <br>
 *      + 启用自定义音频采集渲染后，使用 pushExternalAudioFrame:frameNum:{@link #pushExternalAudioFrame:frameNum:} 推送音频数据。  <br>
 *      + 启用自定义音频采集渲染后，使用 pullExternalAudioFrame:frameNum:{@link #pullExternalAudioFrame:frameNum:} 拉取音频数据。  <br>
 */
- (BOOL)setExternalAudioDevice:(BOOL) enable
                    sampleRate:(int) sampleRate
              recordChannelNum:(int) recordChannelNum
             playoutChannelNum:(int) playoutChannelNum;

 /**
  * @type api
  * @region 混音
  * @brief 启动/停止外部音频流混音， 并设置混音数据格式
  * @param enable  <br>
  *       + YES: 启用外部音频流混音。  <br>
  *       + NO: 停止外部音频流混音。
  * @param sampleRate  <br>
  *        音频采样率，单位HZ。目前支持的采样率有：8000HZ， 16000HZ， 32000HZ， 44100HZ，48000HZ。
  * @param channelNum  <br>
  *        音频声道个数。目前支持单通道(1)，双通道(2)
  * @return  <br>
  *      + YES:成功   <br>
  *      + NO:失败
  * @notes  <br>
  *      + 调用该方法设置外部音频混音的PCM格式，即 pushAudioMixingStreamData:frameNum:{@link #pushAudioMixingStreamData:frameNum:} 的 audioFrame 的音频数据格式。  <br>
  *      + 调用该方法混音的数据来源外部缓存，且音频格式为PCM； startAudioMixing:loopback:replace:cycle:{@link #startAudioMixing:loopback:replace:cycle:}  方法混音数据来源外部文件，且支持的文件格式有: mp3，aac，m4a，3gp，wav。这两种混音方式可以共存。  <br>
  *      + enable 为 NO 时，停止外部音频流混音。 或者引擎释放时，SDK内部会停止混音。  <br>
  *      + 该方法启动的外部音频流混音不支持音量调节，暂停，暂停恢复操作。
  */
- (BOOL)setAudioPlayoutMixStream:(BOOL) enable
                    sampleRate:(int) sampleRate
                    channelNum:(int) channelNum;

 /**
 * @type api
 * @region 混音
 * @brief 获取SDK当前缓冲数据
 * @return  <br>
 *       + >0: 成功，缓冲的音频采样点个数。  <br>
 *       + 0: 失败
 * @notes
 *      调用该方法可以实时获取缓存数据量，并以此数据为基准调整数据推送节奏来避免内存溢出
 */
- (int)getAudioMixingStreamCachedFrameNum;

 /**
  * @type api
  * @region 混音
  * @brief 向SDK推送混音的音频数据
  * @param audioFrame  <br>
  *        PCM音频数据，其格式与 setAudioPlayoutMixStream:sampleRate:channelNum:{@link #setAudioPlayoutMixStream:sampleRate:channelNum:} 保持一致。
  * @param frameNum  <br>
  *        采样点数。若音频采样率为 48000HZ，则单个声道每秒的数据量为 48000 个采样点，10 毫秒的音频数据对应的采样点数为 480 个采样点。
  * @return  <br>
  *       + YES: 成功  <br>
  *       + NO: 失败
  * @notes
  *      + 调用该方法前，必须通过 setAudioPlayoutMixStream:sampleRate:channelNum:{@link #setAudioPlayoutMixStream:sampleRate:channelNum:} 方法设置 audioFrame 的数据格式。  <br>
  *      + 调用该方法前，先通过 getAudioMixingStreamCachedFrameNum{@link #getAudioMixingStreamCachedFrameNum} 获取缓存的数据量，并调整推送数据的节奏以避免内部缓溢出导致推送失败。  <br>
  *      + 使用参考建议：首次推送数据，请在应用侧先缓存一定数据（如 200 毫秒）， 然后一次性推送过去；此后的推送操作定时 10 毫秒一次，并且每次的音频数据量为 10 毫秒数据量。
  */
- (BOOL)pushAudioMixingStreamData:(void* _Nonnull)audioFrame
                         frameNum:(int)frameNum;


/**
 * @type api
 * @region 自定义音频采集渲染
 * @brief 启动音频外部源采集渲染时，添加音频外部设备事件监控
 * @param audioDeviceObserver
 *        音频设备事件监控，详见：ByteAudioDeviceObserver{@link #ByteAudioDeviceObserver}
 * @return  方法调用结果  <br>
 *        + YES: 方法调用成功  <br>
 *        + NO: 方法调用失败
 */
- (BOOL)setAudioDeviceObserver:(_Nullable id<ByteAudioDeviceObserver>) audioDeviceObserver;

/**
 * @type api
 * @region 音频数据回调
 * @brief 设置本地麦克风录制的音频数据回调参数
 * @param samplesPerSec 音频采样率（单位HZ），可以设置的值有 8000，16000，32000，44100，48000
 * @param channels 音频通道数，支持单声道（1）和双声道（2）
 * @return  方法调用结果  <br>
 *        + YES: 方法调用成功  <br>
 *        + NO: 方法调用失败
 * @notes 使用本方法设置参数，并使用setAudioFrameObserver{@link #setAudioFrameObserver:}注册数据观察者，
 *        之后可以在ByteAudioFrameObserver{@link #ByteAudioFrameObserver}的
 *        onRecordAudioFrame{@link #ByteAudioFrameObserver#onRecordAudioFrame:}收到数据
 */
- (BOOL)setRecordingAudioFrameParameters:(NSInteger)samplesPerSec
                            channels:(NSInteger)channels;

/**
 * @type api
 * @region 音频数据回调
 * @brief 设置远端所有用户音频数据混音后的音频数据回调参数
 * @param samplesPerSec 音频采样率（单位HZ），可以设置的值有 8000，16000，32000，44100，48000
 * @param channels 音频通道数，支持单声道（1）和双声道（2）
 * @return  方法调用结果  <br>
 *        + YES: 方法调用成功  <br>
 *        + NO: 方法调用失败
 * @notes 使用本方法设置参数，并使用setAudioFrameObserver{@link #setAudioFrameObserver:}注册数据观察者，
 *        之后可以在ByteAudioFrameObserver{@link #ByteAudioFrameObserver}的
 *        onPlaybackAudioFrame{@link #ByteAudioFrameObserver#onPlaybackAudioFrame:}收到数据
 */
- (BOOL)setPlaybackAudioFrameParameters:(NSInteger)samplesPerSec
                            channels:(NSInteger)channels;

/**
 * @type api
 * @region 音频数据回调
 * @brief 设置本地麦克风录制音频数据和远端所有用户音频数据混音后的音频数据回调参数
 * @param samplesPerSec 音频采样率（单位HZ），可以设置的值有 8000，16000，32000，44100，48000
 * @param channels 音频通道数，支持单声道（1）和双声道（2）
 * @return  方法调用结果  <br>
 *        + YES: 方法调用成功  <br>
 *        + NO: 方法调用失败
 * @notes 使用本方法设置参数，并使用setAudioFrameObserver{@link #setAudioFrameObserver:}注册数据观察者，
 *        之后可以在ByteAudioFrameObserver{@link #ByteAudioFrameObserver}的
 *        onMixedAudioFrame{@link #ByteAudioFrameObserver#onMixedAudioFrame:}收到数据
 */
- (BOOL)setMixedAudioFrameParameters:(NSInteger)samplesPerSec
                            channels:(NSInteger)channels;

/**
 * @type api
 * @region 音频数据回调
 * @brief 设置音频数据回调观察者
 * @param audioFrameObserver 音频数据回调的观察者对象，详见：ByteAudioFrameObserver{@link #ByteAudioFrameObserver}
 * @return  方法调用结果  <br>
 *        + YES: 方法调用成功  <br>
 *        + NO: 方法调用失败
 * @notes 本方法需要与下面3个方法配合使用：
 *        setRecordingAudioFrameParameters:channels:{@link #setRecordingAudioFrameParameters:channels:}、
 *        setPlaybackAudioFrameParameters:channels:{@link #setPlaybackAudioFrameParameters:channels:}、
 *        setMixedAudioFrameParameters:channels:{@link #setMixedAudioFrameParameters:channels:}
 */
- (BOOL)setAudioFrameObserver:(_Nullable id<ByteAudioFrameObserver>) audioFrameObserver;

/**
 * @type api
 * @region 自定义音频采集渲染
 * @brief 推送外部音频数据。使用
 *        setExternalAudioDevice:sampleRate:recordChannelNum:playoutChannelNum:{@link #setExternalAudioDevice:sampleRate:recordChannelNum:playoutChannelNum:}
 *        启用自定义音频采集渲染后，可以使用本方法推送外部音频数据。
 * @param audioFrame
 *        pcm 数据，内存大小应该为 frameNum * recordChannelNum * 2。
 * @param frameNum
 *        采样点数量，应该为 setExternalAudioDevice:sampleRate:recordChannelNum:playoutChannelNum:{@link #setExternalAudioDevice:sampleRate:recordChannelNum:playoutChannelNum:} 中设置的 SampleRate / 100。
 *        当设置采样率为48000时， 每次应该推送480个采样点
 * @return  方法调用结果  <br>
 *        + YES: 方法调用成功  <br>
 *        + NO: 方法调用失败
 * @notes  <br>
 *       + 必须是pcm数据，推送间隔是10ms，音频采样格式为s16。  <br>
 *       + 该函数运行在用户调用线程内
 */
- (BOOL)pushExternalAudioFrame:(void* _Nonnull)audioFrame
                      frameNum:(int)frameNum;

/**
 * @type api
 * @region 自定义音频采集渲染
 * @brief 拉取远端音频数据。使用
 *        setExternalAudioDevice:sampleRate:recordChannelNum:playoutChannelNum:{@link #setExternalAudioDevice:sampleRate:recordChannelNum:playoutChannelNum:}
 *        启用自定义音频采集渲染后，可以使用本方法拉取远端音频数据。
 * @param audioFrame
 *        pcm 数据，内存大小应该为 frameNum * playoutChannelNum * 2。
 * @param frameNum
 *        采样点数量，应该为 setExternalAudioDevice:sampleRate:recordChannelNum:playoutChannelNum:{@link #setExternalAudioDevice:sampleRate:recordChannelNum:playoutChannelNum:} 中设置的 SampleRate / 100。
 *        当设置采样率为48000时， 每次应该推送480个采样点
 * @return  方法调用结果  <br>
 *        + YES: 方法调用成功  <br>
 *        + NO: 方法调用失败
 * @notes  <br>
 *       + 必须是pcm数据，拉取间隔是10ms，音频采样格式为s16。  <br>
 *       + 该函数运行在用户调用线程内
 */
- (BOOL)pullExternalAudioFrame:(void* _Nonnull)audioFrame
                      frameNum:(int)frameNum;

#pragma mark Message Related
/**
 *  @type api
 *  @region 流消息
 *  @brief 给房间内的所有其他用户发送广播消息。
 *  @param msg 用户发送的广播消息
 *  @notes
 *        1.同一房间内的其他用户会收到 onRoomMessageReceived:message:{@link #rtcEngine:onRoomMessageReceived:message:} 回调。
 */
- (int)sendRoomMessage:(NSString *  _Nonnull)msg;

/**
 *  @type api
 *  @region 流消息
 *  @brief 给房间内的所有其他用户发送广播消息。
 *  @param msg 用户发送的广播消息
 *  @notes
 *        1.同一房间内的其他用户会收到 onRoomBinaryMessageReceived:message:{@link #rtcEngine:onRoomBinaryMessageReceived:message:} 回调。
 */
- (int)sendRoomBinaryMessage:(NSData *  _Nonnull)msg;

#pragma mark Game Audio Related
/**
 *  @hidden
 *  @type api
 *  @region 游戏接口
 *  @brief 设置引擎的工作模式，默认为通用模式。进房前调用。
 *  @param mode 模式选择，通用模式或者游戏语音模式。详见 RtcMode{@link #RtcMode}。
 *  @return 方法调用结果  <br>
 *         + 0: 调用成功  <br>
 *         + <0: 调用失败  <br>
 */
- (int)setRtcMode:(RtcMode)mode;

/**
 *  @hidden
 *  @type api
 *  @region 游戏接口
 *  @brief 向小队或世界发音频，在创建 RtcEngine 实例后调用。
 *  @param mode 模式选择，向小队发送或者向世界发送。详见 RangeAudioMode{@link #RangeAudioMode}。
 *  @return 方法调用结果  <br>
 *         + 0: 调用成功  <br>
 *         + <0: 调用失败  <br>
 */
- (int)setAudioSendMode:(RangeAudioMode)mode;

/**
 *  @hidden
 *  @type api
 *  @region 游戏接口
 *  @brief 收听小队或世界音频，在创建 RtcEngine 实例后调用。
 *  @param mode 模式选择，收听小队或者世界音频。详见 RangeAudioMode{@link #RangeAudioMode}。
 *  @return 方法调用结果  <br>
 *         + 0: 调用成功  <br>
 *         + <0: 调用失败  <br>
 */
- (int)setAudioRecvMode:(RangeAudioMode)mode;

/**
 *  @hidden
 *  @type api
 *  @region 游戏接口
 *  @brief 设置 teamId，必须在加入房间前调用，不支持设置后修改。如果不设置 teamId 并且为游戏语音模式，则加入房间失败。如果不设置 teamId 并且为通用模式，该方法无效。
 *  @param teamId 队伍 ID。
 *  @return 方法调用结果  <br>
 *         + 0: 调用成功  <br>
 *         + <0: 调用失败  <br>
 */
- (int)setTeamId:(NSString* _Nonnull)teamId;

/**
 * @hidden
 * @type api
 * @region 游戏接口
 * @brief 设置自己可听见的范围，在游戏语音中使用
 * @param minRange
 *         最小的开始衰减的距离，即超过这个距离，音量开始随着距离的增大而衰减
 * @param maxRange
 *         最大衰减距离，即超过这个距离，听不见声音
 * @return 方法调用结果  <br>
 *        + 0： 调用成功  <br>
 *        + <0： 调用失败  <br>
 * @notes  <br>
 *       + (0, minRange)时，音量不衰减。  <br>
 *       + (minRange, maxRange)时，按距离增大衰减  <br>
 *       + 大于maxRange，听不到声音  <br>
 */
- (int)updateAudioRecvRange:(int)minRange
    maxRange:(int)maxRange;

/**
 * @hidden
 * @type api
 * @region 游戏接口
 * @brief 更新自己的位置，在游戏语音中使用。在游戏语音中，角色拥有自己的三维坐标，可根据距离来动态调整音量
 * @param x: x轴坐标
 * @param y: y轴坐标
 * @param z: z轴坐标
 * @return 方法调用结果  <br>
 *        + 0：调用成功  <br>
 *        + <0：调用失败  <br>
 * @notes 只有开启区域语音 enableRangeAudio{@link #enableRangeAudio:}，非队友用户在收发世界时才会调整音量
 */
- (int)updateSelfPosition:(int)x
                        y:(int)y
                        z:(int)z;

/**
 * @hidden
 * @type api
 * @region 游戏接口
 * @brief 游戏语音场景下，是否开启区域语音，默认开启区域语音
 * @param enable
 *         1. true 表示开启
 *         2. false 表示关闭
 * @return 方法调用结果  <br>
 *        + 0：调用成功  <br>
 *        + <0：调用失败  <br>
 * @notes
 *         如果开启区域语音，非队友之间在收发世界模式下语音会根据用户之间的距离衰减，超过收听范围就听不到，如果关闭区域语音，非队友之间在收发世界模式下，语音不会随距离衰减
 */
- (int)enableRangeAudio:(BOOL) enable;

/**
 * @type api
 * @region 音频管理
 * @brief 设置音频处理复杂度。对于希望性能占用较低，可设置较低的音频处理复杂度，如果更在意通话质量，可选择设置更高的音频处理复杂度。
 *        加入房间时，会携带本接口传入的机型等级，然后从服务端拉起相应音频配置。如果传入的是 auto，服务端会查询数据库，获得机型等级，再下发配置。
 *        不同复杂度会开关AEC、ANS、AGC算法，调整播放sample rate等, 进行性能和质量的控制。
 *        默认为AUDIO_PERF_PROFILE_AUTO{@link #AUDIO_PERF_PROFILE_AUTO}
 * @param profile 机型等级, 详见枚举类 AudioPerfProfile{@link #AudioPerfProfile}
 * @notes  <br>
 *       + 需要在进房之前调用。  <br>
 *       + 本次进房时下发的配置，需要下次进房发布才会应用。  <br>
 *       + 支持自定义配置，详细操作方式请联系技术支持人员。
*/
- (void)setAudioPerfProfile:(AudioPerfProfile) profile;

/**
 * @type api
 * @region 引擎管理
 * @brief 设置业务标识参数。  <br>
 *        可通过 businessId 区分不同的业务场景（角色/策略等）。businessId 由客户自定义，相当于一个“标签”，可以分担和细化现在 AppId 的逻辑划分的功能。
 * @param businessId  <br>
 *        用户设置的自己的 businessId 值。businessId 相当于一个 sub AppId，可以分担和细化现在 AppId 的逻辑划分的功能，但不需要鉴权。
 *        businessId 只是一个标签，颗粒度需要用户自定义。
 * @return  <br>
 *        + 0： 成功。  <br>
 *        + <0： 失败。  <br>
 *        + -6001： 用户已经在房间中。  <br>
 *        + -6002： 输入非法，合法字符包括所有小写字母、大写字母和数字，除此外还包括四个独立字符分别是：英文句号，短横线，下划线和 @ 。
 * @notes  <br>
 *        + 需要在调用 joinChannelByKey:channelName:info:uid:{@link #ByteRtcEngineKit#joinChannelByKey:channelName:info:uid:} 之前调用，
 *           joinChannelByKey:channelName:info:uid:{@link #ByteRtcEngineKit#joinChannelByKey:channelName:info:uid:} 之后调用该方法无效。
 */
- (int)setBusinessId:(NSString* _Nullable)businessId;

/**
/**
 * @type api
 * @region 其他
 * @brief 通话结束，用户反馈上报 <br>
 * @param grade 打分 1～5分  <br>
 * @param type 问题列表  <br>
 * @param desc 其他问题  <br>
 * @return  0: 成功  <br>
 *         -1: 还没加入过房间，上报失败 <br>
 *         -2: 数据解析错误  <br>
 *         -3: 字段缺失  <br>
 *         -4: grade不合法  <br>
 */
+ (int)feedbackGrade:(NSInteger)grade type:(NSInteger)type desc:(NSString* _Nullable)desc;

#pragma mark Monitor Related
/**-----------------------------------------------------------------------------
 *  @name 监控相关
 * -----------------------------------------------------------------------------
 */

/**
 * @type api
 * @hidden
 * @region 引擎管理
 * @brief 设置设备 ID 。  <br>
 *        监控时可以根据设置的 deviceID 来查找相关信息。必须在 sharedEngineWithAppId:delegate:{@link #sharedEngineWithAppId:delegate:} 前调用。
 * @param deviceID  <br>
 *        设备 ID 。
 */
+ (void)setDeviceId:(NSString* _Nonnull) deviceID;


/**
 * @hidden
 * @type api
 * @region 引擎管理
 * @brief 设置 SDK 当前使用的服务器环境。
 * @param env  <br>
 *        SDK 使用的服务器环境参数，详见：ByteRtcEnv{@link #ByteRtcEnv} 。
 * @return  <br>
 *        + 0： 成功。  <br>
 *        + <0： 失败。  <br>
 *        + -1： 引擎已创建。
 * @notes  <br>
 *        + 本函数是可选函数，默认使用正式环境。  <br>
 *        + 本函数必须在创建 RtcEngine 实例 sharedEngineWithAppId:delegate:{@link #sharedEngineWithAppId:delegate:} 前调用。
 */
+ (int)setEnv:(ByteRtcEnv)env;

/**
 * @hidden
 * @type api
 * @region 引擎管理
 * @brief 设置自定义的 HttpClient 实现。提供给 SDK 进行网络请求。
 * @param client  <br>
 *        自定义的 HttpClient 。
 * @notes  <br>
 *        + SDK 支持使用自定义的 HttpClient ，需要实现 ByteRtcHttpClientProtocol{@link #ByteRtcHttpClientProtocol} 协议。  <br>
 *        + 必须在创建 RtcEngine 实例 sharedEngineWithAppId:delegate:{@link #sharedEngineWithAppId:delegate:} 前设置。  <br>
 *        + 不设置则默认使用 SDK 内部实现的 HttpClient 。
 */
+ (void)setHttpClient:(id<ByteRtcHttpClientProtocol> _Nonnull)client;

/**
 * @hidden
 * @type api
 * @region 引擎管理
 * @brief 获取自定义的 HttpClient 实现。
 * @return HttpClient 的实现。
 */
+ (id<ByteRtcHttpClientProtocol> _Nonnull)getHttpClient;

/**
 * @hidden
 * @type api
 * @region 引擎管理
 * @brief 是否已经设置自定义的 HttpClient 。
 * @return  <br>
 *        + true： 已设置。
 *        + false： 未设置。
 */
+ (bool)isHttpClientSet;

#pragma mark message related
/**
 *  @type api
 *  @region 流消息
 *  @brief 给房间内指定的用户发送消息，返回这次发送消息的编号。
 *  @param uid 指定用户 ID
 *  @param message 发送的消息内容
 *  @return
 *       返回这次发送消息的编号，从 1 开始递增
 *  @notes
 *       1.调用该函数后会收到一次 onUserMessageSendResult:error:{@link #rtcEngine:onUserMessageSendResult:error:} 回调；
 *       2.若消息发送成功，则 uid 所指定的用户会收到 onUserMessageReceived:message:{@link #rtcEngine:onUserMessageReceived:message:} 回调。
 */
- (int64_t)sendUserMessage:(NSString * _Nonnull)uid message:(NSString * _Nonnull)message;

/**
 *  @type api
 *  @region 流消息
 *  @brief 给房间内指定的用户发送二进制消息，返回这次发送消息的编号。
 *  @param uid 指定用户 ID
 *  @param message 发送的二进制消息内容
 *  @return
 *       返回这次发送消息的编号，从 1 开始递增
 *  @notes
 *       1.调用该函数后会收到一次 onUserMessageSendResult:error:{@link #rtcEngine:onUserMessageSendResult:error:} 回调；
 *       2.若消息发送成功，则 uid 所指定的用户会收到 onUserBinaryMessageReceived:message:{@link #rtcEngine:onUserBinaryMessageReceived:message:} 回调。
 */
- (int64_t)sendUserBinaryMessage:(NSString * _Nonnull)uid message:(NSData * _Nonnull)message;

#pragma mark Others
/**-----------------------------------------------------------------------------
 *  @name 其他设置
 * -----------------------------------------------------------------------------
 */

/**
 * @type api
 * @region 音频管理
 * @brief 调节远端用户音量，默认值为100
 * @param volume  播放音量，可在 0~400 范围内进行调节  <br>
 *              + 0: 静音  <br>
 *              + 100: 原始音量  <br>
 *              + 400: 最大可为原始音量的 4 倍(自带溢出保护)  <br>
 * @param uid 远端用户ID
 * @return  方法调用结果  <br>
 *        + 0：方法调用成功  <br>
 *        + <0：方法调用失败  <br>
 */
- (int)adjustRemoteAudioVolume:(int)volume ofUid:(NSString* _Nonnull)uid;

#pragma mark audio mix related
/**
 * @type api
 * @region 混音
 * @brief 获取音乐文件时长
 * @return  <br>
 *       + >0: 成功, 音乐文件时长，单位为毫秒。  <br>
 *       + <0: 失败
 * @notes <br>
 *       请在房间内调用该方法。
 */
- (int)getAudioMixingDuration;

/**
 * @type api
 * @region 混音
 * @brief 获取音乐文件播放进度
 * @return  <br>
 *       + >0: 成功, 音乐文件播放进度，单位为毫秒。  <br>
 *       + <0: 失败
 * @notes <br>
 *       请在房间内调用该方法。
 */
- (int)getAudioMixingCurrentPosition;


/**
 * @type api
 * @region 混音
 * @brief 停止播放音乐文件及混音
 * @return  <br>
 *       + 0：成功
 *       + <0：失败
 * @notes  <br>
 *      + 调用 startAudioMixing:loopback:replace:cycle:{@link #startAudioMixing:loopback:replace:cycle:} 方法开始播放音乐文件及混音后，调用该方法可以停止播放音乐文件及混音。  <br>
 *      + 请在房间内调用该方法。
 */
- (int)stopAudioMixing;

/**
 * @type api
 * @region 混音
 * @brief 暂停播放音乐文件
 * @return  <br>
 *        + 0: 成功  <br>
 *        + <0: 失败
 * @notes  <br>
 *      + 调用 startAudioMixing:loopback:replace:cycle:{@link #startAudioMixing:loopback:replace:cycle:} 方法开始播放音乐文件及混音后，可以通过调用该方法暂停播放音乐文件。  <br>
 *      + 调用该方法暂停播放音乐文件后，可调用 resumeAudioMixing{@link #resumeAudioMixing} 方法恢复播放。  <br>
 *      + 请在房间内调用该方法。
 */
- (int)pauseAudioMixing;

/**
 * @type api
 * @region 混音
 * @brief 恢复播放音乐文件
 * @return  <br>
 *       + 0: 成功  <br>
 *       + <0: 失败
 * @notes  <br>
 *      + 调用 pauseAudioMixing{@link #pauseAudioMixing}  方法暂停播放音乐文件后，可以通过调用该方法恢复播放。  <br>
 *      + 请在房间内调用该方法
 */
- (int)resumeAudioMixing;

/**
 * @type api
 * @region 混音
 * @brief 调节音乐文件的文件音量。为保证更好的音质，建议将 volume 值设为 [0,100]。
 * @param volume 音乐文件播放音量范围为 0~400。  <br>
 *       + 0：静音  <br>
 *       + 100：原始音量  <br>
 *       + 400: 最大可调音量 (自带溢出保护)
 * @return  <br>
 *       + 0: 成功  <br>
 *       + <0: 失败
 * @notes  <br>
 *      + 调用该方法可同时调节的是本地和远端播放音量。仅调节本端音量可使用 adjustAudioMixingPlayoutVolume:{@link #adjustAudioMixingPlayoutVolume:} ， 仅调节远端音量可使用 adjustAudioMixingPublishVolume:{@link #adjustAudioMixingPublishVolume:} 。  <br>
 *      + 该方法对 adjustAudioMixingPlayoutVolume:{@link #adjustAudioMixingPlayoutVolume:} 和 adjustAudioMixingPublishVolume:{@link #adjustAudioMixingPublishVolume:} 的音量调节影响是乘积关系  <br>
 *      + 请在房间内调用该方法。
 */
- (int)adjustAudioMixingVolume:(NSInteger)volume;

/**
 * @type api
 * @region 混音
 * @brief 开始播放音乐文件及混音。
 * @param  filePath  <br>
 *        指定需要混音的本地文件的绝对路径。支持音频文件格式有: mp3，aac，m4a，3gp，wav。
 * @param  loopback  <br>
 *        YES: 只有本地可以听到混音或替换后的音频流。  <br>
 *        NO: 本地和对方都可以听到混音或替换后的音频流
 * @param  replace  <br>
 *        YES: 只推送设置的本地音频文件，不传输麦克风采集的音频。  <br>
 *        NO: 音频文件内容将会和麦克风采集的音频流进行混音。
 * @param cycle 指定音频文件循环播放的次数。  <br>
 *       + >0: 循环的次数。  <br>
 *       + -1: 无限循环
 * @return
 *       + 0：成功
 *       + <0：失败
 * @notes <br>
 *      + 该方法指定本地和麦克风采集的音频流进行混音或替换。替换是指用音频文件替换麦克风采集的音频流。  <br>
 *      + 该方法可以选择是否让对方听到本地播放的音频，并指定循环播放的次数。 调用本方法播放音乐文件及混音结束后，应用会收到 rtcEngineLocalAudioMixingDidFinish:{@link #rtcEngineLocalAudioMixingDidFinish:} 回调。  <br>
 *      + 开始播放音乐文件及混音后，可以调用 stopAudioMixing{@link #stopAudioMixing} 方法停止播放音乐文件。  <br>
 *      + 该方法混音数据来源外部文件，且支持的文件格式有: mp3，aac，m4a，3gp，wav；而 setAudioPlayoutMixStream:sampleRate:channelNum:{@link #setAudioPlayoutMixStream:sampleRate:channelNum:} 混音的数据来源外部缓存且音频格式为PCM；这两种混音方式可以共存。  <br>
 *      + 单个房间只支持一路音乐文件的播放，多次调用该函数后，只有最后一次调用会生效。  <br>
 *      + 请在房间内调用该方法。
 */
- (int)startAudioMixing:(NSString *  _Nonnull)filePath
               loopback:(BOOL)loopback
                replace:(BOOL)replace
                  cycle:(NSInteger)cycle;

/**
 * @type api
 * @region 混音
 * @brief 设置音频文件的播放位置
 * @param pos
 *        整数。进度条位置，单位为毫秒。
 * @return  <br>
 *       + 0: 成功  <br>
 *       + <0: 失败
 * @notes  <br>
 *       该方法可以设置音频文件的播放位置，这样你可以根据实际情况从指定的位置播放音乐文件，无需从头到尾完整播放一个音乐文件。
 */
- (int)setAudioMixingPosition:(NSInteger)pos;

/**
 * @type api
 * @region 混音
 * @brief 调节音乐文件的本地播放音量。为保证更好的音质，建议将 volume 值设为 [0,100]。
 * @param volume 音乐文件播放音量范围为 0~400。  <br>
 *       + 0：静音  <br>
 *       + 100：原始音量  <br>
 *       + 400: 最大可调音量 (自带溢出保护)
 * @return  <br>
 *       + 0: 成功  <br>
 *       + <0: 失败
 * @notes  <br>
 *      + 调用该方法可以调节混音的音乐文件在本地播放的音量大小。如果需要同时调节本地和远端播放音量可使用 adjustAudioMixingVolume:{@link #adjustAudioMixingVolume:} 方法。  <br>
 *      + 请在房间内调用该方法。
 */
- (int)adjustAudioMixingPlayoutVolume:(NSInteger)volume;

/**
 * @type api
 * @region 混音
 * @brief 调节音乐文件的远端播放音量。为保证更好的音质，建议将 volume 值设为 [0,100]。
 * @param volume 音乐文件播放音量范围为 0~400。  <br>
 *       + 0：静音  <br>
 *       + 100：原始音量  <br>
 *       + 400: 最大可调音量 (自带溢出保护)
 * @return  <br>
 *       + 0: 成功  <br>
 *       + <0: 失败
 * @notes  <br>
 *      + 该方法调节混音的音乐文件在远端播放的音量大小。如果需要同时调节本地和远端播放音量可使用 adjustAudioMixingVolume:{@link #adjustAudioMixingVolume} 方法。  <br>
 *      + 请在房间内调用该方法。
 */
- (int)adjustAudioMixingPublishVolume:(NSInteger)volume;

/**
 * @type api
 * @region 混音
 * @brief 调节指定音效文件的文件音量
 * @param soundId  <br>
 *        音效ID，应用调用者维护，请保证唯一性。确保此处的 soundId 与  playEffect:filePath:loopback:cycle:withVolume:{@link #playEffect:filePath:loopback:cycle:withVolume:} 设置的 soundId 相同。
 * @param volume  <br>
 *        音乐文件播放音量范围为 0~400。默认 100 为原始文件音量
 * @return  <br>
 *       + 0: 成功  <br>
 *       + <0: 失败
 * @notes
 *       + 该方法调节音效文件在本地和远端播放的音量大小。  <br>
 *       + 请在房间内调用该方法。
 */
- (int)setVolumeOfEffect:(NSInteger)soundId
              withVolume:(NSInteger)volume;

/**
 * @type api
 * @region 混音
 * @brief 获取指定音效文件的文件音量
 * @param soundId  <br>
 *        音效ID，应用调用者维护，请保证唯一性。确保此处的 soundId 与  playEffect:filePath:loopback:cycle:withVolume:{@link #playEffect:filePath:loopback:cycle:withVolume:} 设置的 soundId 相同。
 * @return  <br>
 *       + >0: 成功，文件音量，音量范围为 0~400。  <br>
 *       + <0: 失败
 * @notes  <br>
 *       请在房间内调用该方法。
 */
- (int)getEffectVolume:(NSInteger)soundId;

/**
 * @type api
 * @region 混音
 * @brief 开始播放指定音效文件。你可以在该方法中设置音效文件的播放次数、音量大小，以及远端用户是否能听到该音效。
 * @param soundId  <br>
 *        音效ID，应用调用者维护，请保证唯一性。如果已经通过 preloadEffect:filePath:{@link #preloadEffect:filePath:}  将音效加载至内存，确保此处的 soundId 与 preloadEffect:filePath:{@link #preloadEffect:filePath:} 设置的 soundId 相同。
 * @param filePath  <br>
 *        指定需要混音的音频文件名和文件路径名。支持以下音频格式: mp3，aac，m4a，3gp，wav
 * @param loopback  <br>
 *        + YES: 只有本地可以听到该音效；  <br>
 *        + NO: 本地和远端用户都可以听到该音效
 * @param  cycle 指定音频文件循环播放的次数。  <br>
  *       + >0：循环的次数。  <br>
 *        + -1：无限循环，直至调用 stopEffect:{@link #stopEffect:} 或 stopAllEffects{@link #stopAllEffects} 后停止。
 * @param volume  <br>
 *        音效文件播放音量范围为 0~400。默认 100 为原始文件音量。
 * @return  <br>
 *       + 0: 成功  <br>
 *       + <0: 失败
 * @notes  <br>
 *      + 调用该方法播放音效结束后，应用会收到 rtcEngineLocalAudioMixingDidFinish:{@link #rtcEngineLocalAudioMixingDidFinish:} 回调。
 *      + 可以多次调用该方法，通过传入不同的音效文件的 soundId 和 filePath，以实现同时播放多个音效文件，实现音效叠加。
 *      + 可以通过 stopEffect:{@link #stopEffect:} 方法停止播放指定音效文件。
 *      + 请在房间内调用该方法。
 */
- (int)playEffect:(NSInteger)soundId
         filePath:(NSString * _Nullable)filePath
         loopback:(BOOL)loopback
            cycle:(NSInteger)cycle
       withVolume:(NSInteger)volume;

/**
 * @type api
 * @region 混音
 * @brief 预加载指定音效文件
 * @param soundId  <br>
 *        音效ID，应用调用者维护，请保证唯一性。
 * @param filePath  <br>
 *        指定需要混音的音频文件名和文件路径名。支持以下音频格式: mp3，aac，m4a，3gp，wav。
 * @return  <br>
 *        + 0: 成功  <br>
 *        + <0: 失败
 * @notes  <br>
 *       + 调用该方法预加载播放指定音效文件。预加载操作可以在进房间之前完成（所有混音相关接口，如果没有标注请在房间内调用都可在没有进入房间的时候调用）。如果音效文件很长，加载操作可能会耗时较长，建议应用开发者将预加载操作放在子线程进行。
 *       + 该方法只是预加载播放指定音效文件，只有通过 playEffect:filePath:loopback:cycle:withVolume:{@link #playEffect:filePath:loopback:cycle:withVolume:} 才开始播放指定音效文件。
 *       + 该方法预加载指定音效文件可以通过 unloadEffect:{@link #unloadEffect:} 来卸载。
 */
- (int)preloadEffect:(NSInteger)soundId filePath:(NSString * _Nullable)filePath;

/**
 * @type api
 * @region 混音
 * @brief 卸载指定音效文件
 * @param soundId  <br>
 *        音效ID，应用调用者维护，请保证唯一性。
 * @return  <br>
 *       + 0: 成功  <br>
 *       + <0: 失败
 * @notes  <br>
 *       + 该方法卸载指定音效文件。
 *       + 如果调用 stopEffect:{@link #stopEffect:} 方法时音效文件没有被卸载，SDK会自动调用该方法卸载音效文件。
 */
- (int)unloadEffect:(NSInteger)soundId;

/**
 * @type api
 * @region 混音
 * @brief 暂停播放指定音效文件
 * @param soundId  <br>
 *        音效ID，应用调用者维护，请保证唯一性
 * @return  <br>
 *       + 0: 成功  <br>
 *       + <0: 失败
 * @notes  <br>
 *       调用该方法暂停播放指定音效文件，可以调用 resumeEffect:{@link #resumeEffect:} 方法恢复播放。
 */
- (int)pauseEffect:(NSInteger)soundId;

/**
 * @type api
 * @region 混音
 * @brief 恢复播放指定音效文件
 * @param soundId  <br>
 *        音效ID，应用调用者维护，请保证唯一性。
 * @return  <br>
 *       + 0: 成功  <br>
 *       + <0: 失败
 * @notes
 *      + 调用 pauseEffect:{@link #pauseEffect:} 方法暂停播放指定音效文件后， 可以通过该方法恢复播放。  <br>
 *      + 调用 pauseAllEffects{@link #pauseAllEffects} 方法暂停所有音效文件的播放后，也可以通过该方法恢复单个音效文件播放。
 */
- (int)resumeEffect:(NSInteger)soundId;

/**
 * @type api
 * @region 混音
 * @brief 停止播放指定音效文件
 * @param soundId  <br>
 *        音效ID，应用调用者维护，请保证唯一性。如果已经通过 preloadEffect:filePath:{@link #preloadEffect:filePath:}  将音效加载至内存，确保此处的 soundId 与  preloadEffect:filePath:{@link #preloadEffect:filePath:} 设置的 soundId 相同。
 * @return  <br>
 *       + 0: 成功  <br>
 *       + <0: 失败
 * @notes  <br>
 *       + 调用该方法停止播放指定音效文件。  <br>
 *       + 该方法内部会主动调用 unloadEffect:{@link #unloadEffect:} 来卸载指定音效文。
 */
- (int)stopEffect:(NSInteger)soundId;

/**
* @type api
* @region 混音
* @brief 调节所有音效文件的文件音量
* @param volume  <br>
*        音乐文件播放音量范围为 0~400。默认 100 为原始文件音量。
* @return  <br>
*       + 0: 成功
*       + <0: 失败
* @notes  <br>
*       + 该方法调节混音的所有音效文件在本地和远端播放的音量大小。  <br>
*       + 请在房间内调用该方法。
*/
- (int)setEffectsVolume:(NSInteger)volume;

/**
 * @type api
 * @region 混音
 * @brief 卸载所有音效文件
 * @return  <br>
 *       + 0: 成功  <br>
 *       + <0: 失败
 * @notes  <br>
 *       + 调用该方法卸载所有音效文件。如果引擎被销毁时有音效文件没有被卸载，SDK会自动调用该方法卸载所有音效文件。  <br>
 *       + 调用 leaveChannel:{@link #leaveChannel:} 离开房间后，不会自动调用该方法卸载所有音效文件。如果需要在离开房间后卸载所有音效文件，需要应用主动调用该方法。
 */
- (int)unloadAllEffects;


/**
 * @type api
 * @region 混音
 * @brief 暂停所有音效文件的播放
 * @return  <br>
 *       + 0: 成功  <br>
 *       + <0: 失败
 * @notes  <br>
 *      该方法暂停所有音效文件的播放，可调用 resumeAllEffects{@link #resumeAllEffects} 方法恢复播放。
 */
- (int)pauseAllEffects;

/**
* @type api
* @region 混音
* @brief 恢复所有音效文件的播放
* @return  <br>
*       + 0: 成功  <br>
*       + <0: 失败
* @notes  <br>
*       + 调用该方法恢复所有音效文件的播放。在调用 pauseAllEffects{@link #pauseAllEffects} 暂停所有音效文件的播放后，可以调用该方法可恢复所有音效文件的播放。  <br>
*       + 调用 pauseEffect:{@link #pauseEffect:} 方法暂停单个指定音效文件的播放后，也可以调用该方法恢复播放，但是效率太低，不推荐这么使用。
*/
- (int)resumeAllEffects;

 /**
 * @type api
 * @region 混音
 * @brief 停止所有音效文件的播放
 * @return  <br>
 *       + 0: 成功  <br>
 *       + <0: 失败
 * @notes  <br>
 *      该方法停止所有音效文件的播放。
 */
- (int)stopAllEffects;

#pragma mark Fallback Related
/**
 * @type api
 * @region 音视频回退
 * @brief 设置发布的音视频流回退选项
 * @param option 本地发布的音视频流回退选项，详见枚举类型 BytePublishFallbackOption{@link #BytePublishFallbackOption}
 * @return  <br>
 *        + 0；方法调用成功；  <br>
 *        + -1：方法调用失败；  <br>
 * @notes  <br>
 *       + 1. 在网络情况不理想、设备性能不足时，实时音视频的质量会下降。通过这个接口来设置网络情况不佳或性能不足时只发送小流，以保证通话质量。  <br>
 *       + 2. 这个方法只在设置了发送多个流的情况下有效。  <br>
 *       + 3. 必须在进房前设置，进房后设置或更改设置无效。  <br>
 *       + 4. 设置回退选项后，本端发布的音视频流发生回退或从回退中恢复时，对端会收到 rtcEngine:OnRemoteStreamSwitch:{@link #rtcEngine:OnRemoteStreamSwitch:} 回调通知。  <br>
 */
- (int)setPublishFallbackOption:(BytePublishFallbackOption)option;

/**
 *  @type api
 *  @region 音视频回退
 *  @brief 设置订阅的音视频流回退选项
 *  @param option 远端订阅的流回退处理选项，详见枚举类型 ByteSubscribeFallbackOption{@link #ByteSubscribeFallbackOption}
 *  @return
 *         + 0：方法调用成功  <br>
 *         + <0：方法调用失败  <br>
 *  @notes  <br>
 *        + 在网络情况不理想、设备性能不足时，实时音视频的质量会下降。通过这个接口来设置网络情况不佳或性能不足时只订阅小流或音频流，以保证通话质量。  <br>
 *        + 必须在进房前设置，进房后设置或更改设置无效。  <br>
 *        + 设置回退选项后，本端订阅的音视频流发生回退或从回退中恢复时,会收到 rtcEngine: OnRemoteStreamSwitch:{@link #rtcEngine:OnRemoteStreamSwitch:} 回调通知。  <br>
 *        + 设置回退选项后，本端订阅的视频流因为回退分辨率发生变化时,会收到 rtcEngine:videoSizeChangedOfUid:size:{@link #rtcEngine:videoSizeChangedOfUid:size:} 回调通知。
 */
- (int)setSubscribeFallbackOption:(ByteSubscribeFallbackOption)option;

/**
 *  @type api
 *  @region 音视频回退
 *  @brief 设置用户优先级
 *  @param priority 远端用户的优先级, 详见枚举类型ByteUserPriority{@link #ByteUserPriority}
 *  @param uid 远端用户的 ID
 *  @return + 0：方法调用成功  <br>
 *         + <0：方法调用失败  <br>
 *  @notes  <br>
 *        + 该方法与 setSubscribeFallbackOption:{@link #setSubscribeFallbackOption:}  搭配使用。  <br>
 *        + 如果开启了订阅流回退选项，弱网或性能不足时会优先保证收到的高优先级用户的流的质量。  <br>
 *        + 该方法在进房前后都可以使用，可以修改远端用户的优先级。
 */
- (int)setRemoteUserPriority:(ByteUserPriority)priority
                         uid:(NSString *_Nonnull)uid;

#pragma mark AES Related

/**
 * @type api
 * @region 加密
 * @brief 设置AES加密算法和加密密钥  <br>
 *        有四种内置的加密算法，详见 ByteEncryptType{@link #ByteEncryptType}  <br>
 * @param encrypt_type  <br>
 *        加密类型，详见 ByteEncryptType{@link #ByteEncryptType}  <br>
 * @param key  <br>
 *        加密密钥，长度限制为36位，超出部分将会被截断  <br>
 * @notes
 *       + 该方法与 setCustomizeEncryptHandler:{@link #setCustomizeEncryptHandler:} 为互斥关系,
 *         即按照调用顺序，最后一个调用的方法为最终生效的版本。  <br>
 *       + 该方法必须在调用 joinChannelByKey:channelName:info:uid:{@link #joinChannelByKey:channelName:info:uid:} 之前调用，可重复调用，以最后调用的参数作为生效参数  <br>
 *       + AES加密算法限制，超过36位的key会被截断，仅取前36位  <br>
 */
- (void)setEncryptType:(ByteEncryptType)encrypt_type key:(NSString * _Nonnull)key;

/**
 * @type api
 * @region 加密
 * @brief 设置自定义加密和解密方式
 *        需要实现对应的加密和解密方法。详情参考 ByteEncryptHandler{@link #ByteEncryptHandler}  <br>
 * @param handler  <br>
 *        自定义加密 handler，需要实现里面的加密和解密方法  <br>
 * @notes
 *       + 该方法与 setEncryptType:key:{@link #setEncryptType:key:} 为互斥关系,
 *         即按照调用顺序，最后一个调用的方法为最终生效的版本  <br>
 *       + 该方法必须在调用 joinChannelByKey:channelName:info:uid:{@link #joinChannelByKey:channelName:info:uid:} 之前调用，可重复调用，以最后调用的参数作为生效参数  <br>
 *       + 无论加密或者解密，其对原始数据的长度修改，需要控制在90%-120%之间，即如果输入数据为100字节，则处理完成后的数据必须在
 *         90至120字节之间，如果加密或解密结果超出该长度限制，则该音视频桢会被丢弃  <br>
 *       + 数据加密/解密为串行执行，因而视实现方式不同，可能会影响到最终渲染效率，是否使用该方法，需要由使用方谨慎评估  <br>
 */
- (void)setCustomizeEncryptHandler:(id<ByteEncryptHandler> _Nullable)handler;

#pragma mark - Extention Methods

/**
 *  @hidden
 *  @type api
 *  @region 房间管理
 *  @brief 创建并获取一个 ByteRtcRoom{@link #ByteRtcRoom} 对象
 *  @param [in] roomId
 *         标识通话房间的房间 ID，最大长度为128字节的非空字符串。支持的字符集范围为:
 *             1. 26个大写字母 A ~ Z
 *             2. 26个小写字母 a ~ z
 *             3. 10个数字 0 ~ 9
 *             4. 下划线"_", at符"@", 减号"-"
 *  @notes
 *         1.参数roomId没有默认值，请确保对该参数正确赋值。
 *         2.请勿给参数roomId赋空字符串""或者空指针，否则将无法正确的创建房间对象。
 *         3.用户可以多次调用此方法创建多个 ByteRtcRoom{@link #ByteRtcRoom} 对象，再分别调用各 ByteRtcRoom{@link #ByteRtcRoom} 对象的
 *           joinRoomByToken{@link #joinRoomByToken} 方法，实现同时加入多个房间。
 *         4.加入多个房间后，用户可以同时订阅各房间的音视频流，但是目前仅支持同一时间在一个房间内发布一路音视频流。
 */
- (ByteRtcRoom * _Nullable)createRtcRoom:(NSString * _Nonnull)roomId;


#pragma mark - ScreenCapture
/**
 * @type api
 * @region 视频管理
 * @brief 配置外部屏幕采集
 * @param enable YES :开启;
 *               NO :不开启;
 * @param rect 采集区域
 * @param param 采集参数 ScreenCaptureParam{@link #ScreenCaptureParam}
 * @return 0 :成功;
 *        -1 :失败;
 * @notes
 *        1.屏幕采集分为内部采集和外部采集，本方法属于外部采集。
 *        内部采集：由 SDK 进行屏幕采集和后续所有流程
 *        外部采集：用户负责采集屏幕数据帧，通过接口提供给 SDK
 *        2.调用此方法发布本端屏幕共享流后，用户还需要通过设置定时任务周期性调用 pushScreenCaptureFrame:time:rotation:{@link #pushScreenCaptureFrame:time:rotation:} 方法，将需要发送的屏幕数据推送给 SDK。
 *        3.调用该接口后远端能收到 rtcEngine:firstRemoteScreenFrameOfUid:size:elapsed:{@link #ByteRtcEngineDelegate#rtcEngine:firstRemoteScreenFrameOfUid:size:elapsed:} 和 rtcEngine:onStreamAdd:{@link #rtcEngine:onStreamAdd:} 事件。
 */
- (int)setScreenCapture:(BOOL)enable Rect:(CGRect)rect screenCaptureParam:(ScreenCaptureParam * _Nonnull)param;

/**
 * @type api
 * @region 视频管理
 * @brief 推送外部屏幕采集帧
 * @param frame 该视频帧包含待 SDK 编码的视频数据
 * @param pts 每一帧的时间戳，单位 ms
 * @param rotation 帧的旋转角度包含: 0, 90, 180, 270
 * @notes
 *        1.屏幕采集分为内部采集和外部采集，本方法属于外部采集。
 */
- (void)pushScreenCaptureFrame:(CVPixelBufferRef _Nonnull )frame time:(CMTime)pts rotation:(int)rotation;

/**
 * @type api
 * @region 视频管理
 * @brief 开始内部屏幕采集
 * @param preferredExtension 传入 Broadcast Upload Extension 的 Bundle Id，用于在设置中优先展示 Extension
 * @param param 采集参数 ScreenCaptureParam{@link #ScreenCaptureParam}
 * @param groupId App 和 Extension 应该归属于同一个 App Group，此处需要传入 Group Id。
 * @return 0 :成功;
 *        -1 :失败;
 * @notes
 *        1.屏幕采集分为内部采集和外部采集，本方法属于内部采集。
 *        内部采集：由 SDK 进行屏幕采集和后续所有流程
 *        外部采集：用户负责采集屏幕数据帧，通过接口提供给 SDK
 *        2.调用该接口后远端能收到 rtcEngine:firstRemoteScreenFrameOfUid:size:elapsed:{@link #ByteRtcEngineDelegate#rtcEngine:firstRemoteScreenFrameOfUid:size:elapsed:} 和 rtcEngine:onStreamAdd:{@link #rtcEngine:onStreamAdd:} 事件。
 *        3.内部采集时，外部不需要屏幕采集帧。
 */
- (int)startScreenSharingWithParam:(ScreenCaptureParam *_Nonnull)param preferredExtension:(NSString *_Nullable)extension groupId:(NSString *_Nonnull)groupId API_AVAILABLE(ios(12));

/**
 * @type api
 * @region 视频管理
 * @brief 停止内部屏幕采集
 * @return 0 :成功;
 *        -1 :失败;
 * @notes
 *        屏幕采集分为内部采集和外部采集，本方法属于内部采集。
 */
- (void)stopScreenSharing API_AVAILABLE(ios(12));



/**
 * @hidden
 * @type api
 */
+ (ByteRtcAudioDeviceManager *_Null_unspecified)createAudioDeviceManager:(id<ByteAudioDeviceEventHandler> _Nonnull)handler;

/**
 * @hidden
 * @type api
 * @brief 设置运行时的参数
 * @param [in] parameters 用以覆盖全局参数，详情可见 setParameters{@link #setParameters}，业务方传入
 */
- (void)setRuntimeParameters:(NSDictionary * _Nullable)parameters;

@end
