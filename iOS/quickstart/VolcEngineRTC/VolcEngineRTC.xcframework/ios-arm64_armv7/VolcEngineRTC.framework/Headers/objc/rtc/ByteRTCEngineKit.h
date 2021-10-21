/*
 * Copyright (c) 2020 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngine
*/

#import <CoreMedia/CMTime.h>
#import <UIKit/UIKit.h>
#import "ByteRTCDefines.h"
#import "ByteRTCHttpClientProtocol.h"

@class ByteRTCEngineKit;
@class ByteRTCRoom;
/**
 * @type api
 */
@protocol ByteRTCHttpClientProtocol;

#pragma mark - ByteRTCEngineDelegate
/**
 * @type callback
 * ByteRTCEngineDelegate 协议包含了SDK提供的回调方法，SDK通过代理向应用程序上报一些运行时事件
 */
@protocol ByteRTCEngineDelegate <NSObject>
@optional

#pragma mark - Core Delegate Methods
/**
 *  -----------------------------------------------------------------------------
 * @name 核心事件回调
 *  -----------------------------------------------------------------------------
 */

/**
 * @type callback
 * @region 警告码
 * @brief 发生警告回调。  <br>
 *        SDK 内部遇到可恢复错误时，在尝试自动恢复的同时，会通过此回调通知用户。此回调事件仅用作通知。  <br>
 * @param engine ByteRTCEngineKit 对象。  <br>
 * @param Code 警告代码，参看 ByteRTCWarningCode{@link #ByteRTCWarningCode}。  <br>
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine onWarning:(ByteRTCWarningCode)Code;

/**
 * @type callback
 * @region 错误码
 * @brief 发生错误回调。
 *        SDK 运行时出现了网络或媒体相关的错误，且无法自动恢复时触发此回调。
 * @param engine ByteRTCEngineKit 对象。  <br>
 * @param errorCode 错误代码，参看 ByteRTCErrorCode{@link #ByteRTCErrorCode}。  <br>
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine onError:(ByteRTCErrorCode)errorCode;

/**
 * @type callback
 * @region 引擎管理
 * @author hanchenchen.c
 * @brief SDK 与信令服务器连接状态改变回调。连接状态改变时触发。
 * @param engine ByteRTCEngineKit 对象
 * @param state 当前 SDK 与信令服务器的连接状态，详见 ByteRTCConnectionState{@link #ByteRTCConnectionState}
 */
- (void) rtcEngine:(ByteRTCEngineKit * _Nonnull)engine connectionChangedToState:(ByteRTCConnectionState) state;

/**
 * @type callback
 * @region 引擎管理
 * @author hanchenchen.c
 * @brief SDK 当前网络连接类型改变回调。
 * @param engine ByteRTCEngineKit 对象
 * @param type SDK 当前的网络连接类型，详见 ByteRTCNetworkType{@link #ByteRTCNetworkType}
 */
- (void) rtcEngine:(ByteRTCEngineKit * _Nonnull)engine networkTypeChangedToType:(ByteRTCNetworkType) type;

/**
 * @type callback
 * @region 房间管理
 * @author shenpengliang
 * @brief 首次加入房间/重连加入房间的回调，表示用户调用 joinRoomByKey:roomId:roomProfile:userInfo:{@link #joinRoomByKey:roomId:roomProfile:userInfo:}
 * 的结果，根据错误码判断成功/失败以及区别是否为重连。  <br>
 * @param engine ByteRTCEngineKit 对象。  <br>
 * @param roomId 房间 ID。  <br>
 * @param uid 用户 ID。  <br>
 * @param errorCode 用户加入房间回调的状态码。参看 ByteRTCErrorCode{@link #ByteRTCErrorCode} 以及 ByteRTCWarningCode{@link #ByteRTCWarningCode}。  <br>
 * @return  <br>
 *        + 0: 成功  <br>
 *        + <0: 失败  <br>
 * @param joinType 加入房间的类型。  <br>
 * @return  <br>
 *        + 0: 首次加入房间。用户手动调用 joinRoomByKey:roomId:roomProfile:userInfo:{@link #joinRoomByKey:roomId:roomProfile:userInfo:}，收到加入成功。  <br>
 *        + 1: 重新加入房间。用户网络较差，失去与服务器的连接，进行重连时收到加入成功。  <br>
 * @param elapsed 重连耗时。本地用户从连接断开到重连成功所经历的时间间隔，单位为 ms 。  <br>
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine
    onJoinRoomResult:(NSString *_Nonnull)roomId
             withUid:(nonnull NSString *)uid
           errorCode:(NSInteger)errorCode
            joinType:(NSInteger)joinType
             elapsed:(NSInteger)elapsed;
/**
 * @type callback
 * @region 房间管理
 * @author shenpengliang
 * @brief 远端主播角色用户加入房间回调。  <br>
 *        1.远端主播角色用户调用 joinRoomByKey:roomId:roomProfile:userInfo:{@link #ByteRTCEngineKit#joinRoomByKey:roomId:roomProfile:userInfo:} 方法加入房间时，房间内其他用户将收到该事件。  <br>
 *        2.远端主播角色用户断网后重新连入房间时，房间内其他用户将收到该事件。  <br>
 *        3.远端静默观众角色用户调用 setUserRole:{@link #ByteRTCEngineKit#setUserRole:} 方法将角色切换至主播时，房间内其他用户将收到该事件。  <br>
 *        4.新进房用户会收到进房前已在房内的主播角色用户的进房回调通知。  <br>
 * @param engine ByteRTCEngineKit 对象。  <br>
 * @param userInfo 用户信息。参看 ByteRTCUserInfo{@link #ByteRTCUserInfo}。  <br>
 * @param elapsed  保留字段   <br>
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine onUserJoined:(nonnull ByteRTCUserInfo *)userInfo elapsed:(NSInteger)elapsed;

/**
 * @type callback
 * @region 房间管理
 * @author shenpengliang
 * @brief 远端主播角色用户离开房间回调。  <br>
 *        发生以下情形时，房间内其他用户会收到此事件：  <br>
 *        1.远端主播角色用户调用 leaveRoom:{@link #ByteRTCEngineKit#leaveRoom:} 方法离开房间时。  <br>
 *        2.远端主播角色用户调用 setUserRole:{@link #ByteRTCEngineKit#setUserRole:} 方法将角色切换至静默观众。  <br>
 *        3.远端主播角色用户断网，且一直未恢复。  <br>
 * @param engine ByteRTCEngineKit 对象。  <br>
 * @param uid 离开房间的远端用户 ID 。  <br>
 * @param reason 用户离开房间的原因，参看 ByteRTCUserOfflineReason{@link #ByteRTCUserOfflineReason}。  <br>
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine onUserLeave:(NSString *_Nonnull)uid reason:(ByteRTCUserOfflineReason)reason;

/**
 * @hidden
 * @type callback
 * @region 房间管理
 * @author shenpengliang
 * @brief 当发布流成功的时候回调该事件。
 * @param engine ByteRTCEngineKit 对象。  <br>
 * @param userId 发布流的用户 ID。  <br>
 * @param isScreen 发布成功的流是否是屏幕流
 *        + Ture: 屏幕流；  <br>
 *        + False: 非屏幕流。  <br>
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine onStreamPublishSuccess:(NSString *_Nonnull)userId isScreen:(BOOL)isScreen;

#pragma mark - Core Audio Delegate Methods
/**
 *  -----------------------------------------------------------------------------
 * @name 核心音频事件回调
 *  -----------------------------------------------------------------------------
 */

/**
 * @hidden
 * @type callback
 * @region 视频管理
 * @author wangjunzheng
 * @brief 当房间内用户调用 muteAllRemoteAudio:{@link #muteAllRemoteAudio:}，
 *        改变接收所有远端音频流的状态时, 房间内其他用户收到这个回调。
 * @param engine ByteRTCEngineKit 对象
 * @param uid 改变接收状态的用户 ID
 * @param muteState 接收状态，详见 ByteRTCMuteState{@link #ByteRTCMuteState}
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onMuteAllRemoteAudio:(NSString * _Nonnull)uid muteState:(ByteRTCMuteState)muteState;

/**
 * @hidden
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onMuteAllRemoteVideo:(NSString * _Nonnull)uid withMuteState:(ByteRTCMuteState)muteState;

/**
 * @type callback
 * @region 音频事件回调
 * @author wangjunzheng
 * @brief 房间内某用户调用 muteLocalAudio:{@link #muteLocalAudio:}
 *        改变本地音频发送状态时，房间内其他用户会收到此回调。
 * @param engine ByteRTCEngineKit 对象
 * @param uid 改变本地音频发送状态的用户 ID
 * @param muteState 发送状态，详见 ByteRTCMuteState{@link #ByteRTCMuteState}
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onUserMuteAudio:(NSString * _Nonnull)uid muteState:(ByteRTCMuteState)muteState;

/**
 * @deprecated
 * @type callback
 * @region 音频事件回调
 * @author wangjunzheng
 * @brief 远端用户开启/关闭音频设备采集回调
 *         提示有远端用户已开启/关闭音频设备采集，该回调由远端用户调用 startAudioCapture{@link #startAudioCapture} 方法触发
 * @param engine ByteRTCEngineKit对象
 * @param enabled YES: 该用户开启了音频设备采集；NO: 该用户关闭了音频设备采集
 * @param uid 远端用户ID
 *       + 该接口已废弃，请使用 rtcEngine:onUserStartAudioCapture:{@link #ByteRTCEngineDelegate#rtcEngine:onUserStartAudioCapture:} 以及 rtcEngine:onUserStopAudioCapture:{@link #ByteRTCEngineDelegate#rtcEngine:onUserStopAudioCapture:} <br>
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine didLocalAudioEnabled:(BOOL)enabled byUid:(NSString * _Nonnull)uid;

/**
 * @type callback
 * @region 音频事件回调
 * @author wangjunzheng
 * @brief 房间内的用户调用 startAudioCapture{@link #ByteRTCEngineKit#startAudioCapture} 开启音频采集时，房间内其他用户会收到此回调。
 * @param engine ByteRTCEngineKit 对象
 * @param userId 开启音频采集的远端用户 ID
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onUserStartAudioCapture:(NSString *_Nonnull)userId;

/**
 * @type callback
 * @region 音频事件回调
 * @author wangjunzheng
 * @brief 房间内的用户调用 stopAudioCapture{@link #ByteRTCEngineKit#stopAudioCapture} 关闭音频采集时，房间内其他用户会收到此回调。
 * @param engine ByteRTCEngineKit 对象
 * @param userId 关闭音频采集的远端用户 ID
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onUserStopAudioCapture:(NSString *_Nonnull)userId;

/**
 * @type callback
 * @region 音频事件回调
 * @author wangjunzheng
 * @brief 当收到远端流的第一帧音频的时候上报该事件
 * @param engine ByteRTCEngineKit 对象
 * @param key 远端流信息, 详见 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
 *  @notes 用户刚收到房间内每一路音频流时，都会收到该回调。
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onFirstRemoteAudioFrame:(ByteRTCRemoteStreamKey * _Nonnull)key;

/**
 * @type callback
 * @region 音频事件回调
 * @author wangjunzheng
 * @brief 提示本地采集的音量信息和在房间内订阅的远端用户的音量信息。<br>
 *        本回调默认不开启。你可以通过调用 setAudioVolumeIndicationInterval:{@link #ByteRTCEngineKit#setAudioVolumeIndicationInterval:} 开启。  <br>
 * @param engine ByteRTCEngineKit 对象
 * @param [in] speakers 本地用户和订阅的远端用户的 ID 和音量。
 *                      参看 ByteRTCAudioVolumeInfo{@link #ByteRTCAudioVolumeInfo}。
 * @param totalRemoteVolume speakers 中包含的所有音频音量之和，取值范围是 [0,255]。
 * @notes
 *        + 对于本地用户：只要进行本地音频采集，回调内就会包含本地音频流的音量信息。<br>
 *        + 对于远端用户：本地必须订阅某远端用户的音频流，回调内才会包含其发送的音频流的音量信息。
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onAudioVolumeIndication:(NSArray<ByteRTCAudioVolumeInfo *> * _Nonnull)speakers totalRemoteVolume:(NSInteger)totalRemoteVolume;

#pragma mark - Core Video Delegate Methods
/**
 *  -----------------------------------------------------------------------------
 * @name 核心视频事件回调
 *  -----------------------------------------------------------------------------
 */

/**
 * @type callback
 * @region 视频管理
 * @author liyi.000
 * @brief 房间内用户暂停/恢复发送视频流时，房间内其他用户会收到此回调。参看 muteLocalVideo:{@link #ByteRTCEngineKit#muteLocalVideo:}。
 * @param engine ByteRTCEngineKit 对象
 * @param uid 暂停/恢复发送视频流的用户 ID。
 * @param muteState 暂停/恢复发送视频流。参看 ByteRTCMuteState{@link #ByteRTCMuteState}
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onUserMuteVideo:(NSString * _Nonnull)uid withMuteState:(ByteRTCMuteState)muteState;

/**
 * @type callback
 * @region 视频管理
 * @author liyi.000
 * @brief 远端用户启用本地视频回调。房间中远端用户调用 startVideoCapture{@link #startVideoCapture} 时，本地用户将会收到该回调。
 * @param engine ByteRTCEngineKit 对象
 * @param userId 调用 startVideoCapture{@link #startVideoCapture} 接口的远端用户ID
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onUserStartVideoCapture:(NSString *_Nonnull)userId;

/**
 * @type callback
 * @region 视频管理
 * @author liyi.000
 * @brief 远端用户关闭本地视频回调。房间中远端用户调用 stopVideoCapture{@link #stopVideoCapture} 时，本地用户将会收到该回调。
 * @param engine ByteRTCEngineKit 对象
 * @param userId 调用 stopVideoCapture{@link #stopVideoCapture} 接口的远端用户ID
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onUserStopVideoCapture:(NSString *_Nonnull)userId;

/**
 * @type callback
 * @region 视频管理
 * @author liyi.000
 * @brief 第一帧本地采集的视频/屏幕共享画面在本地视图渲染完成时，收到此回调。
 * @param engine ByteRTCEngineKit 对象
 * @param streamIndex 流属性，参看 ByteRTCStreamIndex:{@link #ByteRTCStreamIndex}
 * @param frameInfo 视频帧信息，参看 ByteRTCVideoFrameInfo: {@link #ByteRTCVideoFrameInfo}
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onFirstLocalVideoFrameCaptured:(ByteRTCStreamIndex)streamIndex withFrameInfo:(ByteRTCVideoFrameInfo * _Nonnull)frameInfo;

/**
 * @type callback
 * @region 视频管理
 * @author liyi.000
 * @brief 第一帧远端视频流在视图上渲染成功后，收到此回调。
 * @param engine ByteRTCEngineKit 对象
 * @param streamKey 远端流信息，参看 ByteRTCRemoteStreamKey:{@link #ByteRTCRemoteStreamKey}
 * @param frameInfo 视频帧信息，参看 ByteRTCVideoFrameInfo:{@link #ByteRTCVideoFrameInfo}
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onFirstRemoteVideoFrameRendered:(ByteRTCRemoteStreamKey * _Nonnull)streamKey withFrameInfo:(ByteRTCVideoFrameInfo * _Nonnull)frameInfo;

/**
 * @type callback
 * @region 视频管理
 * @author liyi.000
 * @brief 远端视频大小或旋转信息发生变化时，收到此回调。
 * @param engine ByteRTCEngineKit 对象
 * @param streamKey 流属性，参看 ByteRTCRemoteStreamKey:{@link #ByteRTCRemoteStreamKey}
 * @param frameInfo 视频帧信息，参看 ByteRTCVideoFrameInfo:{@link #ByteRTCVideoFrameInfo}
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine onRemoteVideoSizeChanged:(ByteRTCRemoteStreamKey *_Nonnull)streamKey withFrameInfo:(ByteRTCVideoFrameInfo *_Nonnull)frameInfo;

/**
 * @type callback
 * @region 视频管理
 * @author liyi.000
 * @brief 本地视频大小或旋转信息发生变化时，收到此回调。
 * @param engine ByteRTCEngineKit 对象
 * @param streamIndex 流属性，参看 ByteRTCStreamIndex:{@link #ByteRTCStreamIndex}
 * @param frameInfo 视频帧信息，参看 ByteRTCVideoFrameInfo:{@link #ByteRTCStreamIndex}
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine onLocalVideoSizeChanged:(ByteRTCStreamIndex)streamIndex withFrameInfo:(ByteRTCVideoFrameInfo *_Nonnull)frameInfo;

/**
 * @type callback
 * @region 视频管理
 * @author liyi.000
 * @brief 远端视频流状态发生改变回调。
 * @param engine ByteRTCEngineKit 对象，参考: ByteRTCEngineKit{@link #ByteRTCEngineKit}
 * @param uid 发生视频流状态改变的远端用户的用户ID
 * @param state 变更后的远端视频流状态，详见类型 ByteRTCRemoteVideoState{@link #ByteRTCRemoteVideoState}
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine remoteVideoStateChangedOfUid:(NSString * _Nonnull)uid state:(ByteRTCRemoteVideoState)state;

/**
 * @type callback
 * @region 视频管理
 * @author liyi.000
 * @brief 本地视频镜像状态发生改变回调。
 * @param engine ByteRTCEngineKit 对象
 * @param  mirrored 当前是否开启镜像 <br>
 *        + true：当前本地视频状态为开启镜像  <br>
 *        + false：当前本地视频状态为关闭镜像  <br>
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine didMirrorStateChanged:(BOOL)mirrored;

/**
 * @type callback
 * @region 引擎管理
 * @author panjian.fishing
 * @brief 媒体设备状态回调。媒体设备包括音频采集设备、音频渲染设备、视频采集设备三种类型。
 * @param engine ByteRTCEngineKit 对象
 * @param device_id 设备 ID
 * @param device_type 设备类型，参看 ByteRTCMediaDeviceType{@link #ByteRTCMediaDeviceType}
 * @param device_state 设备状态，参看 ByteRTCMediaDeviceState{@link #ByteRTCMediaDeviceState}
 * @param device_error 设备错误类型，参看 ByteRTCMediaDeviceError{@link #ByteRTCMediaDeviceError}
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onMediaDeviceStateChanged:(NSString*_Nonnull)device_id device_type:(ByteRTCMediaDeviceType)device_type device_state:(ByteRTCMediaDeviceState)device_state device_error:(ByteRTCMediaDeviceError)device_error;

/**
 * @type callback
 * @region 房间管理
 * @author shenpengliang
 * @brief 音频首帧发送状态改变回调。
 * @param engine ByteRTCEngineKit 对象
 * @param user 本地用户信息，详见 ByteRTCUser{@link #ByteRTCUser}
 * @param state 首帧发送状态，详见 ByteRTCFirstFrameSendState{@link #ByteRTCFirstFrameSendState}
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine onAudioFrameSendStateChanged:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFrameSendState)state;

/**
 * @type callback
 * @region 房间管理
 * @author shenpengliang
 * @brief 视频首帧发送状态改变回调
 * @param user 本地用户信息，详见 ByteRTCUser{@link #ByteRTCUser}
 * @param state 首帧发送状态，详见 ByteRTCFirstFrameSendState{@link #ByteRTCFirstFrameSendState}
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine onVideoFrameSendStateChanged:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFrameSendState)state;

/**
 * @type callback
 * @region 房间管理
 * @author shenpengliang
 * @brief 屏幕共享流视频首帧发送状态改变回调
 * @param engine ByteRTCEngineKit 对象。  <br>
 * @param user 本地用户信息，参看 ByteRTCUser{@link #ByteRTCUser}
 * @param state 首帧发送状态，参看 ByteRTCFirstFrameSendState{@link #ByteRTCFirstFrameSendState}
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine onScreenVideoFrameSendStateChanged:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFrameSendState)state;

/**
 * @type callback
 * @region 房间管理
 * @author shenpengliang
 * @brief 音频首帧播放状态改变回调
 * @param engine ByteRTCEngineKit 对象。  <br>
 * @param user 远端用户信息，参看 ByteRTCUser{@link #ByteRTCUser}
 * @param state 首帧播放状态，参看 ByteRTCFirstFramePlayState{@link #ByteRTCFirstFramePlayState}
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine onAudioFramePlayStateChanged:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFramePlayState)state;

/**
 * @type callback
 * @region 房间管理
 * @author shenpengliang
 * @brief 视频首帧播放状态改变回调
 * @param user 远端用户信息，参看 ByteRTCUser{@link #ByteRTCUser}
 * @param state 首帧播放状态，参看 ByteRTCFirstFramePlayState{@link #ByteRTCFirstFramePlayState}
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine onVideoFramePlayStateChanged:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFramePlayState)state;

/**
 * @type callback
 * @region 房间管理
 * @author shenpengliang
 * @brief 屏幕共享流视频首帧播放状态改变回调
 * @param user 远端用户信息，参看 ByteRTCUser{@link #ByteRTCUser}
 * @param state 首帧播放状态，参看 ByteRTCFirstFramePlayState{@link #ByteRTCFirstFramePlayState}
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine onScreenVideoFramePlayStateChanged:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFramePlayState)state;

#pragma mark - Media Stream Delegate Methods
/**
 *  -----------------------------------------------------------------------------
 * @name 媒体数据事件回调
 *  -----------------------------------------------------------------------------
 */

/**
 *  @type callback
 *  @region 音频事件回调
 *  @author wangjunzheng
 *  @brief 本地采集到第一帧音频帧时，收到该回调。
 *  @param engine ByteRTCEngineKit 对象
 *  @param streamIndex 音频流属性, 详见 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onFirstLocalAudioFrame:(ByteRTCStreamIndex) streamIndex;

/**
 * @type callback
 * @region 房间管理
 * @author shenpengliang
 * @brief 房间内的用户发布新的音视频流时，房间内的其他用户会收到此回调通知。包括移除后又重新发布的流。  <br>
 * @param engine ByteRTCEngineKit 对象。  <br>
 * @param stream 流的属性，参看 ByteRTCStream{@link #ByteRTCStream} 数据类型。  <br>
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onStreamAdd:(id <ByteRTCStream> _Nonnull)stream;

/**
 * @hidden
 * @type callback
 * @region 媒体事件回调
 * @brief 房间内流数据订阅状态。用户启用自定义订阅时，通知用户对特定流的订阅状态
 * @param engine ByteRTCEngineKit 对象
 * @param state 流数据的订阅状态
 * @param userId 用户ID
 * @param info 自定义订阅配置，详见类型 ByteRTCSubscribeConfig{@link #ByteRTCSubscribeConfig}
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine
    onStreamSubscribed:(ByteRTCSubscribeState)state
                userId:(NSString *_Nonnull)userId
       subscribeConfig:(ByteRTCSubscribeConfig *_Nonnull)info;

/**
 * @type callback
 * @region 房间管理
 * @author shenpengliang
 * @brief 房间内的远端用户停止发布音视频流时，本地用户会收到此回调通知。  <br>
 * @param engine ByteRTCEngineKit 对象。  <br>
 * @param uid 远端流来源的用户 ID 。  <br>
 * @param stream 流的属性，参看 ByteRTCStream{@link #ByteRTCStream}。  <br>
 * @param reason 远端流移除的原因，参看 ByteRTCStreamRemoveReason{@link #ByteRTCStreamRemoveReason} 。  <br>
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine
    didStreamRemoved:(NSString *_Nonnull)uid
              stream:(id<ByteRTCStream> _Nonnull)stream
              reason:(ByteRTCStreamRemoveReason)reason;

/**
 *  @hidden
 *  @type callback
 *  @region 音频管理
 *  @author wangjunzheng
 *  @brief 游戏场景中，当房间内远端用户的音频发送模式变化时回调该事件，发送模式只有三种，分别是：静音、向小队发送、向世界发送。
 *  @param engine  ByteRTCEngineKit 对象
 *  @param uid  远端用户 ID
 *  @param mode  远端用户的音频发送模式
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine didUserAudioSendModeChange:(NSString* _Nonnull )uid mode:(ByteRTCRangeAudioMode)mode;

/**
 *  @hidden
 *  @type callback
 *  @region 音频管理
 *  @author wangjunzheng
 *  @brief 游戏场景中，当房间内远端用户的音频收听模式变化时回调该事件，收听模式只有三种，分别是：静音、收听小队、收听世界。
 *  @param engine  ByteRTCEngineKit 对象
 *  @param  uid  远端用户 ID
 *  @param  mode  远端用户的音频收听模式
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine didUserAudioRecvModeChange:(NSString* _Nonnull )uid mode:(ByteRTCRangeAudioMode)mode;

#pragma mark - Media Device Delegate Methods
/**
 *  -----------------------------------------------------------------------------
 * @name 媒体设备事件回调
 *  -----------------------------------------------------------------------------
 */

/**
 *  @type callback
 *  @region 音频事件回调
 *  @author wangjunzheng
 *  @brief 音频播放设备变化时，收到该回调。
 *  @param engine ByteRTCEngineKit 对象
 *  @param device 新的音频设备，详见 ByteRTCAudioPlaybackDevice{@link #ByteRTCAudioPlaybackDevice}
 *  @notes 音频设备设置与音频路由策略，详见 setAudioPlaybackDevice:{@link #setAudioPlaybackDevice:}
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onAudioPlaybackDeviceChanged:(ByteRTCAudioPlaybackDevice)device;


#pragma mark custom message Delegate Methods
/**-----------------------------------------------------------------------------
 * @name 发送消息回调
 * -----------------------------------------------------------------------------
 */

/**
 * @type callback
 * @region 实时消息通信
 * @author hanchenchen.c
 * @brief 收到房间中广播文本消息时（Broadcast），会收到此回调。
 * @param engine  <br>
 *        当前 RTCEngine 实例。
 * @param uid  <br>
 *        消息发送者 ID 。
 * @param message  <br>
 *        收到的文本消息内容。
 * @notes  <br>
 *        + 你必须先调用 sendRoomMessage:{@link #ByteRTCEngineKit#sendRoomMessage:} 方法，才能收到该回调。
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onRoomMessageReceived:(NSString * _Nonnull)uid message:(NSString * _Nonnull)message;

/**
 * @type callback
 * @region 实时消息通信
 * @author hanchenchen.c
 * @brief 房间内所有用户接收到广播二进制消息的回调。（Broadcast）。
 * @param engine ByteRTCEngineKit 对象
 * @param uid  <br>
 *        消息发送者 ID 。
 * @param message  <br>
 *        收到的广播二进制消息内容。
 * @notes  <br>
 *        + 同一房间内其他用户调用 sendRoomBinaryMessage:{@link #ByteRTCEngineKit#sendRoomBinaryMessage:} 发送广播二进制消息给房间内所有用户时，所有用户会收到该回调。
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onRoomBinaryMessageReceived:(NSString * _Nonnull)uid message:(NSData * _Nonnull)message;

#pragma mark - Statistics Delegate Methods
/**
 *  -----------------------------------------------------------------------------
 * @name 数据统计回调
 *  -----------------------------------------------------------------------------
 */

/**
 * @type callback
 * @region 数据统计
 * @author liuzhiqiang.avcoder
 * @brief 房间内通话统计信息回调。   <br>
 *        用户进房开始通话后，每 2s 收到一次本回调。
 * @param engine ByteRTCEngineKit 对象
 * @param stats 当前 RtcEngine 统计数据，详见 ByteRTCRoomStats{@link #ByteRTCRoomStats}
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine onRoomStats:(ByteRTCRoomStats *_Nonnull)stats;

/**
 * @type callback
 * @region 数据统计
 * @author liuzhiqiang.avcoder
 * @brief 报告当前设备 cpu 与 memory 使用率，每 2s 触发一次。
 * @param engine ByteRTCEngineKit 对象
 * @param stats cpu 和 memory 使用率信息，详见 ByteRTCSysStats{@link #ByteRTCSysStats} 数据类型
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine reportSysStats:(const ByteRTCSysStats * _Nonnull)stats;

/**
 * @type callback
 * @region 数据统计
 * @author liuzhiqiang.avcoder
 * @brief 本地流数据统计以及网络质量回调。  <br>
 *        本地用户发布流成功后，SDK 会周期性（2s）的通过此回调事件通知用户发布的流在此次统计周期内的质量统计信息。  <br>
 *        统计信息通过 ByteRTCLocalStreamStats{@link #ByteRTCLocalStreamStats} 类型的回调参数传递给用户，其中包括发送音视频比特率、发送帧率、编码帧率，网络质量等。  <br>
 * @param engine ByteRTCEngineKit 对象。  <br>
 * @param stats 发布音/视频流质量以及本地网络质量统计数据，参看 ByteRTCLocalStreamStats{@link #ByteRTCLocalStreamStats} 数据类型。  <br>
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine onLocalStreamStats:(const ByteRTCLocalStreamStats *_Nonnull)stats;

/**
 * @type callback
 * @region 数据统计
 * @author liuzhiqiang.avcoder
 * @brief 通话中本地设备接收订阅的远端音/视频流的统计信息以及网络状况，每 2s 触发一次。
 * @param engine ByteRTCEngineKit 对象
 * @param stats 当前 RtcEngine 统计数据，详见 ByteRTCRemoteStreamStats{@link #ByteRTCRemoteStreamStats}
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine onRemoteStreamStats:(const ByteRTCRemoteStreamStats *_Nonnull)stats;

/**
 * @type callback
 * @region 音频事件回调
 * @author wangjunzheng
 * @brief 本地音频流的状态发生改变时，该回调通知当前的本地音频状态。
 * @param engine ByteRTCEngineKit 对象
 * @param state 本地音频设备的状态，详见 ByteRTCLocalAudioStreamState{@link #ByteRTCLocalAudioStreamState}
 * @param error 本地音频流状态改变时的错误码，详见 ByteRTCLocalAudioStreamError{@link #ByteRTCLocalAudioStreamError}
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine
    onLocalAudioStateChanged:(ByteRTCLocalAudioStreamState)state
                     error:(ByteRTCLocalAudioStreamError)error;

/**
 *  @type callback
 *  @region 音频事件回调
 *  @author wangjunzheng
 *  @brief 用户订阅来自远端的音频流状态发生改变时，会收到此回调，了解当前的远端音频流状态。
 *  @param engine ByteRTCEngineKit 对象
 *  @param key 远端流信息, 详见 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
 *  @param state 远端音频流状态，详见 ByteRTCRemoteAudioState{@link #ByteRTCRemoteAudioState}
 *  @param reason 远端音频流状态改变的原因，详见 ByteRTCRemoteAudioStateChangeReason{@link #ByteRTCRemoteAudioStateChangeReason}
*/
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine
    onRemoteAudioStateChanged:(ByteRTCRemoteStreamKey * _Nonnull)key
                      state:(ByteRTCRemoteAudioState)state
                      reason:(ByteRTCRemoteAudioStateChangeReason)reason;

/**
 * @type callback
 * @region 视频管理
 * @author shenpengliang
 * @brief 本地视频流的状态发生改变时，收到该事件。
 * @param engine ByteRTCEngineKit 对象
 * @param streamIndex 流属性，参看 ByteRTCStreamIndex:{@link #ByteRTCStreamIndex}
 * @param state 本地视频流状态，参看 ByteRTCLocalVideoStreamState:{@link #ByteRTCLocalVideoStreamState}
 * @param error 本地视频状态改变时的错误码，参看 ByteRTCLocalVideoStreamError:{@link #ByteRTCLocalVideoStreamError}
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine
    onLocalVideoStateChanged:(ByteRTCStreamIndex)streamIndex
             withStreamState:(ByteRTCLocalVideoStreamState)state
             withStreamError:(ByteRTCLocalVideoStreamError)error;

/**
 * @type callback
 * @region 视频管理
 * @author shenpengliang
 * @brief 远端视频流的状态发生改变时，房间内订阅此流的用户会收到该事件。
 * @param engine ByteRTCEngineKit 对象
 * @param streamKey 远端视频流信息，房间、用户 ID、流属性等，参看 ByteRTCRemoteStreamKey:{@link #ByteRTCRemoteStreamKey}
 * @param state 远端视频流状态，参看 ByteRTCRemoteVideoState:{@link #ByteRTCRemoteStreamKey}
 * @param reason 远端视频流状态改变的原因，参看 ByteRTCRemoteVideoStateChangeReason:{@link #ByteRTCRemoteVideoStateChangeReason}
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine
    onRemoteVideoStateChanged:(ByteRTCRemoteStreamKey*_Nonnull)streamKey
               withVideoState:(ByteRTCRemoteVideoState)state
withVideoStateReason:(ByteRTCRemoteVideoStateChangeReason)reason;

#pragma mark - Message Delegate Methods
/**
 * @type callback
 * @region 实时消息通信
 * @author hanchenchen.c
 * @brief 收到来自房间中其他用户发来的文本消息时（P2P），会收到此回调。
 * @param engine  <br>
 *        当前 RTCEngine 实例。
 * @param uid  <br>
 *        消息发送者 ID 。
 * @param message  <br>
 *        收到的文本消息内容。
 * @notes  <br>
 *        + 你必须先调用 sendUserMessage:message:{@link #ByteRTCEngineKit#sendUserMessage:message:} 方法，才能收到该回调。
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onUserMessageReceived:(NSString * _Nonnull)uid message:(NSString * _Nonnull)message;

/**
 * @type callback
 * @region 实时消息通信
 * @author hanchenchen.c
 * @brief 单个用户接收到同一房间内其他 uid 所属用户发来二进制消息的回调（P2P）。
 * @param engine ByteRTCEngineKit 对象
 * @param uid  <br>
 *        消息发送者 ID 。
 * @param message  <br>
 *        收到的二进制消息内容。
 * @notes  <br>
 *        + 同一房间内其他用户调用 sendUserBinaryMessage:message:{@link #ByteRTCEngineKit#sendUserBinaryMessage:message:} 发送二进制消息给本地用户时，本地用户会收到该回调。
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onUserBinaryMessageReceived:(NSString * _Nonnull)uid message:(NSData * _Nonnull)message;

/**
 * @type callback
 * @region 实时消息通信
 * @author hanchenchen.c
 * @brief 向房间内单个用户发送文本或二进制消息后（P2P），消息发送方会收到该消息发送结果回调。
 * @param engine ByteRTCEngineKit 对象
 * @param msgid  <br>
 *            本条消息的 ID。
 * @param error  <br>
 *            文本或二进制消息发送结果，详见 ByteRTCUserMessageSendResult{@link #ByteRTCUserMessageSendResult}
 * @notes  <br>
 *        + 你必须先调用 sendUserMessage:message:{@link #ByteRTCEngineKit#sendUserMessage:message:} 或 sendUserBinaryMessage:message:{@link #ByteRTCEngineKit#sendUserBinaryMessage:message:} 接口，才能收到此回调。
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onUserMessageSendResult:(int64_t)msgid error:(ByteRTCUserMessageSendResult)error;

/**
 * @type callback
 * @region 实时消息通信
 * @author hanchenchen.c
 * @brief 向房间内所有用户发送文本或二进制消息后（Broadcast），消息发送方会收到该消息发送结果回调。
 * @param engine ByteRTCEngineKit 对象
 * @param msgid  <br>
 *        本条消息的 ID。
 * @param error  <br>
 *        文本或二进制消息发送结果，详见 ByteRTCRoomMessageSendResult{@link #ByteRTCRoomMessageSendResult}
 * @notes  <br>
 *        + 你必须先调用 sendRoomMessage:{@link #ByteRTCEngineKit#sendRoomMessage:} 或 sendRoomBinaryMessage:{@link #ByteRTCEngineKit#sendRoomBinaryMessage:} 接口，才能收到此回调。
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onRoomMessageSendResult:(int64_t)msgid error:(ByteRTCRoomMessageSendResult)error;

#pragma mark - Subscribe Delegate Methods

/**
 * @hidden
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine
     didSubscribe:(NSString * _Nonnull)uid isReconnect:(BOOL)isReconnect;

/**
 * @hidden
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine
   didUnSubscribe:(NSString * _Nonnull)uid isReconnect:(BOOL)isReconnect;

#pragma mark - Log Delegate Methods
/**
 *  -----------------------------------------------------------------------------
 * @name 日志相关回调
 *  -----------------------------------------------------------------------------
 */

/**
 * @type callback
 * @region 引擎管理
 * @author chenweiming.push
 * @brief SDK 内部日志回调。  <br>
 *        SDK 内部运行时，会把日志回调给业务方，方便排查问题。
 * @param engine  <br>
 *        ByteRTCEngineKit 对象。
 * @param dict  <br>
 *        日志内容。
 */
- (void)rtcEngine:(ByteRTCEngineKit* _Nonnull)engine log:(NSDictionary* _Nonnull)dict
    __attribute((deprecated("Will be removed in new version")));

#pragma mark Audio Mix Delegate Methods
/**-----------------------------------------------------------------------------
 * @name 音频混音回调
 * -----------------------------------------------------------------------------
 */

/**
 * @type callback
 * @region 混音
 * @author wangjunzheng
 * @brief 音乐文件混音结束回调。SDK通过此回调通知应用层音乐文件混音结束。
 * @param engine 当前RTC SDK对象
 */
- (void)rtcEngineLocalAudioMixingDidFinish:(ByteRTCEngineKit *_Nonnull)engine;

/**
 * @type callback
 * @region 混音
 * @author wangjunzheng
 * @brief 音效文件混音结束回调。SDK通过此回调通知应用层音效文件混音结束
 * @param engine 当前RTC SDK对象
 * @param soundId 音效ID
 */
- (void)rtcEngineDidAudioEffectFinish:(ByteRTCEngineKit *_Nonnull)engine soundId:(NSInteger)soundId;

#pragma mark transcoding Delegate Methods
/**-----------------------------------------------------------------------------
 * @name 合流转推状态回调
 * -----------------------------------------------------------------------------
 */

/**
 * @type callback
 * @region CDN 推流
 * @author shenpengliang
 * @brief 合流转推错误回调。  <br>
 *        调用 startLiveTranscoding:observer:{@link #ByteRTCEngineKit#startLiveTranscoding:observer:} 接口或直接在服务端启动合流转推功能后，你会通过此回调收到启动结果和推流过程中的错误。
 * @param engine engine 实例
 * @param url 推流地址的 URL。
 * @param errorCode
 *        合流转推功能错误码，详见枚举类型 ByteRTCTranscodingError{@link #ByteRTCTranscodingError}。
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine onLiveTranscodingResult:(NSString *_Nonnull)url errorCode:(ByteRTCTranscodingError)errorCode;
#pragma mark Performance Delegate Methods
/**-----------------------------------------------------------------------------
 * @name 性能相关的回调
 *  -----------------------------------------------------------------------------
 */

/**
 * @type callback
 * @region 音视频回退
 * @author panjian.fishing
 * @brief 本地未开启发布性能回退，检测到设备性能不足时，收到此回调。  <br>
 *        本地开启发布性能回退，因设备性能/网络原因，造成发布性能回退/恢复时，收到此回调。  <br>
 * @param mode 指示本地是否开启发布回退功能。参看 ByteRTCPerformanceAlarmMode{@link #ByteRTCPerformanceAlarmMode}  <br>
 *             + 当发布端未开启发布性能回退时，mode 值为 ByteRTCPerformanceAlarmModeNormal。  <br>
 *             + 当发布端开启发布性能回退时，mode 值为 ByteRTCPerformanceAlarmModeSimulcast。
 * @param roomId  <br>
 *                + 未开启发布性能回退时，roomId 为空  <br>
 *                + 开启发布性能回退时，roomId 是告警影响的房间 ID。
 * @param reason 告警原因，参看 ByteRTCPerformanceAlarmReason{@link #ByteRTCPerformanceAlarmReason}
 * @param data 性能回退相关数据，详见 ByteRTCSourceWantedData{@link #ByteRTCSourceWantedData}。
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine
    onPerformanceAlarmsWithMode:(ByteRTCPerformanceAlarmMode)mode
                         roomId:(NSString *_Nonnull)roomId
                         reason:(ByteRTCPerformanceAlarmReason)reason
               sourceWantedData:(ByteRTCSourceWantedData *_Nonnull)data;

/**
 * @type callback
 * @region 音视频回退
 * @author panjian.fishing
 * @brief 因发布/订阅性能回退或退出回退状态，订阅的音视频流，发生流的切换时，收到该回调。
 * @param engine 当前 RTCEngine 实例
 * @param event 流切换信息。详见 ByteRTCRemoteStreamSwitchEvent{@link #ByteRTCRemoteStreamSwitchEvent}。
 * @notes  <br>
 *        + 你必须先通过 API 或控制台设置音视频流订阅回退功能时，你才能收到此回调。
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine OnSimulcastSubscribeFallback:(ByteRTCRemoteStreamSwitchEvent *_Nonnull)event;

#pragma mark Proxy Delegate Methods
/**-----------------------------------------------------------------------------
 * @name Socks5和HTTP代理回调
 * -----------------------------------------------------------------------------
 */

/**
 * @type callback
 * @region 网络代理
 * @brief HTTP 代理连接状态改变时，收到该回调。
 * @param engine ByteRTCEngineKit 对象
 * @param state 当前 HTTP 代理连接状态
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine onHttpProxyState:(NSInteger)state;

/**
 * @type callback
 * @region 网络代理
 * @brief HTTPS 代理连接状态改变时，收到该回调。
 * @param engine ByteRTCEngineKit 对象
 * @param state 当前 HTTPS 代理连接状态
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine onHttpsProxyState:(NSInteger)state;

/**
 * @type callback
 * @region 网络代理
 * @brief SOCKS5 代理状态改变时，收到该回调。
 * @param engine ByteRTCEngineKit 对象
 * @param state SOCKS5 代理连接状态
 * @param cmd 代理连接的每一步操作命令
 * @param proxy_address 代理地址信息
 * @param local_address 当前连接使用的本地地址
 * @param remote_address 远端的连接地址
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine
    onSocks5ProxyState:(NSInteger)state
                   cmd:(NSString *_Nonnull)cmd
         proxy_address:(NSString *_Nonnull)proxy_address
         local_address:(NSString *_Nonnull)local_address
        remote_address:(NSString *_Nonnull)remote_address;

@end

/**
 *  @type callback
 *  @brief 音频数据代理
 */
@protocol ByteRTCAudioFrameObserver <NSObject>
/**
 * @type callback
 * @region 音频数据回调
 * @author wangjunzheng
 * @brief 返回麦克风录制的音频数据
 * @param audioFrame 麦克风录制的音频数据, 详见： ByteRTCAudioFrame{@link #ByteRTCAudioFrame}
 */
- (void)onRecordAudioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;
/**
 * @type callback
 * @region 音频数据回调
 * @author wangjunzheng
 * @brief 返回远端所有用户混音后的音频数据
 * @param audioFrame 远端所有用户混音后的音频数据, 详见： ByteRTCAudioFrame{@link #ByteRTCAudioFrame}
 */
- (void)onPlaybackAudioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;
/**
 * @hidden
 * @region 音频数据回调
 * @author wangjunzheng
 * @notes 该接口未实现
 */
- (void)onPlaybackAudioFrameBeforeMixing:(NSString* _Nonnull )uid
                      audioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;
/**
 * @type callback
 * @region 音频数据回调
 * @author wangjunzheng
 * @brief 返回本地麦克风录制和远端所有用户混音后的音频数据
 * @param audioFrame  本地麦克风录制和远端所有用户混音后的音频数据, 详见： ByteRTCAudioFrame{@link #ByteRTCAudioFrame}
 */
- (void)onMixedAudioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;
@end

#pragma mark - ByteRTCEngineMediaMetadataObserver
/**
* @type callback
* @brief 使用内部源视频采集时,配置和获取附加数据接口
*/
BYTERTC_APPLE_EXPORT @protocol ByteRTCMediaMetadataObserver <NSObject>
@required
/**
 * @type callback
 * @region 视频数据回调
 * @author sunhang.io
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
 * @author sunhang.io
 * @brief 当 SDK 收到的视频帧包含 medatada 时，会回调该接口
 * @param uid 当前帧所属的用户ID
 * @param extendedData metadata
 * @param timestamp 包含 metadata 视频帧的时间戳，单位为微秒
 * @notes 回调中不能做长时间逻辑处理，以免影响视频卡顿
 */
- (void)receiveVideoFrameFromUID:(NSString * _Nonnull)uid withExtendedData:(NSData* _Nullable)extendedData atTimestamp:(NSTimeInterval)timestamp;
@end

#pragma mark - EncryptHandler
/**
 * @type callback
 * @region 加密
 * @author sunhang.io
 * @brief 自定义加密接口
 */
@protocol ByteRTCEncryptHandler <NSObject>

@required
/**
 * @type api
 * @region 加密
 * @author sunhang.io
 * @brief 自定义加密。  <br>
 *        使用设定的自定义加密方式，对传输前的音视频帧数据进行加密。
 * @param rawData 原始音视频帧数据
 * @return 加密后的数据  <br>
 *        + 非空，表示加密后的数据  <br>
 *        + 为空，表示数据被丢弃
 * @notes <br>
 *        + 使用此接口进行自定义加密前，你必须先设置自定义加密方式，参看 setCustomizeEncryptHandler:{@link #ByteRTCEngineKit#setCustomizeEncryptHandler:}。
 *        + 使用 ByteRTCDecryptRawData:{@link #ByteRTCEncryptHandler#ByteRTCDecryptRawData:} 对已加密的音视频帧数据进行解密。
 *        + 返回的数据大小应控制在原始数据的 90% ~ 120% 范围以内，不然将被丢弃。
 */
- (NSData * _Nonnull) ByteRTCEncryptRawData:(NSData * _Nonnull)rawData;

@required
/**
 * @type api
 * @region 加密
 * @author sunhang.io
 * @brief 自定义解密。  <br>
 *        对自定义加密后的音视频帧数据进行解密。关于自定义加密，参看 ByteRTCEncryptRawData:{@link #ByteRTCEncryptHandler#ByteRTCEncryptRawData:}。
 * @param rawData 收到的已加密的音视频帧数据
 * @return 解密后的数据  <br>
 *        + 非空，表示解密后的数据  <br>
 *        + 为空，表示丢弃该帧
 * @notes <br>
 *        + 使用此接口进行解密前，你必须先设定解密方式，参看 setCustomizeEncryptHandler:{@link #ByteRTCEngineKit#setCustomizeEncryptHandler:}。
 *        + 返回的数据大小应控制在原始数据的 90% ~ 120% 范围以内，不然将被丢弃。
 */
- (NSData * _Nonnull) ByteRTCDecryptRawData:(NSData * _Nonnull)rawData;
@end

#pragma mark - AudioDeviceManager
/**
 * @hidden
 * @type callback
 * @region 音频管理
 * @author wangjunzheng
 * @brief 音频设备事件回调
 */
BYTERTC_APPLE_EXPORT @protocol ByteRTCAudioDeviceEventHandler<NSObject>
/**
 * @hidden
 * @type callback
 * @region 音频管理
 * @author wangjunzheng
 * @brief 获得麦克风音量
 * @param volume 音量大小
 */
- (void)onRecordingAudioVolumeIndication:(int)volume;
@end

/**
 * @hidden
 * @type api
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCAudioDeviceManager : NSObject
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

__attribute((deprecated("Will be removed in new version")))
/**
 * @type callback
 * @region 监控
 * @brief 非业务相关的监控事件回调
 */
@protocol ByteRTCMonitorDelegate <NSObject>

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
- (void)onVerboseLogWithLevel:(ByteRTCLogLevel)level
                     filename:(NSString * _Nonnull)filename
                          tag:(NSString * _Nonnull)tag
                         line:(int)line
                 functionName:(NSString * _Nonnull)funcName
                       format:(NSString * _Nonnull)format;

@end

#pragma mark - ByteRTCEngineKit
/**
 * @type api
 * @region 引擎管理
 * @author chenweiming.push
 * @brief SDK 回调给应用层的 delegate 对象，详见 ByteRTCEngineDelegate{@link #ByteRTCEngineDelegate}
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCEngineKit : NSObject
/**
 * @hidden
 */
@property (nonatomic, weak) id<ByteRTCEngineDelegate> _Nullable delegate;

/**
 * @hidden
 */
@property (nonatomic, weak) id<ByteRTCMonitorDelegate> _Nullable monitorDelegate
    __deprecated_msg("Will be removed in new version");

#pragma mark Core Methods
/**
 *  -----------------------------------------------------------------------------
 * @name 核心方法
 *  -----------------------------------------------------------------------------
 */

/**
 * @type api
 * @region 引擎管理
 * @author chenweiming.push
 * @brief 创建 RTCEngine 实例。  <br>
 *        此方法应该作为正常 SDK 流程中的第一步操作，通过创建一个 RTCEngine 实例，来使用 SDK 的其他能力。
 * @param appId  <br>
 *        每个应用的唯一标识符，由 VRTC 控制台随机生成的。不同的 AppId 生成的实例在 VRTC 中进行音视频通话完全独立，无法互通。
 * @param delegate  <br>
 *        SDK 回调给应用层的 delegate，详见 ByteRTCEngineDelegate{@link #ByteRTCEngineDelegate}
 * @return 可用的 ByteRTCEngineKit{@link #ByteRTCEngineKit} 实例。
 * @notes  <br>
 *        + 该方法在第一次调用时初始化一个 RTCEngine 单例，除非调用 destroy{@link #destroy} 方法，否则后续的所有调用均
 *          返回同一个内部实例。  <br>
 *        + 连续多次调用该方法不会创建不同的 ByteRTCEngineKit{@link #ByteRTCEngineKit}，该方法应该与 destroy{@link #destroy}
 *          成对使用  <br>
 *        + 必须使用相同的App ID，App 间才能进行通话。  <br>
 *        + 在调用 destroy{@link #destroy} 之后会销毁 ByteRTCEngineKit{@link #ByteRTCEngineKit} 实例，再次调用
 *          sharedEngineWithAppId:delegate:{@link #sharedEngineWithAppId:delegate:} 方法则会重新创建一个全新的
 *          ByteRTCEngineKit{@link #ByteRTCEngineKit} 实例。
 */
+ (instancetype _Nonnull)sharedEngineWithAppId:(NSString * _Nonnull)appId
                                      delegate:(id<ByteRTCEngineDelegate> _Nullable)delegate
                                      __deprecated_msg("Will be removed in new version");
/**
 * @type api
 * @region 引擎管理
 * @author chenweiming.push
 * @brief 创建 RTCEngine 实例。  <br>
 *        此方法应该作为正常 SDK 流程中的第一步操作，通过创建一个 RTCEngine 实例，来使用 SDK 的其他能力。
 * @param appId  <br>
 *        每个应用的唯一标识符，由 VRTC 控制台随机生成的。不同的 AppId 生成的实例在 VRTC 中进行音视频通话完全独立，无法互通。
 * @param delegate  <br>
 *        SDK 回调给应用层的 delegate，详见 ByteRTCEngineDelegate{@link #ByteRTCEngineDelegate}
 * @param monitorDelegate  <br>
 *        监控信息的回调 delegate, 详见 ByteRTCMonitorDelegate{@link #ByteRTCMonitorDelegate}
 * @return 可用的 ByteRTCEngineKit{@link #ByteRTCEngineKit} 实例。
 * @notes  <br>
 *        + 该方法在第一次调用时初始化一个 RTCEngine 单例，除非调用 destroy{@link #destroy} 方法，否则后续的所有调用均
 *          返回同一个内部实例。  <br>
 *        + 连续多次调用该方法不会创建不同的 ByteRTCEngineKit{@link #ByteRTCEngineKit}，该方法应该与 destroy{@link #destroy}
 *          成对使用  <br>
 *        + 必须使用相同的App ID，App 间才能进行通话。  <br>
 *        + 在调用 destroy{@link #destroy} 之后会销毁 ByteRTCEngineKit{@link #ByteRTCEngineKit} 实例，再次调用
 *          sharedEngineWithAppId:delegate:{@link #sharedEngineWithAppId:delegate:} 方法则会重新创建一个全新的
 *          ByteRTCEngineKit{@link #ByteRTCEngineKit} 实例。
 */
+ (instancetype _Nonnull)sharedEngineWithAppId:(NSString * _Nonnull)appId
                                      delegate:(id<ByteRTCEngineDelegate> _Nullable)delegate
                               monitorDelegate:(id<ByteRTCMonitorDelegate> _Nullable)monitorDelegate
                               __deprecated_msg("Will be removed in new version");

/**
 * @type api
 * @region 引擎管理
 * @author chenweiming.push
 * @brief 获取 ByteRTCEngineKit{@link #ByteRTCEngineKit} 单例对象。
 * @return 由 sharedEngineWithAppId:delegate:{@link #sharedEngineWithAppId:delegate:} 创建的 ByteRTCEngineKit{@link #ByteRTCEngineKit} 对象。
 * @notes  <br>
 *        + 如果未调用 sharedEngineWithAppId:delegate:{@link #sharedEngineWithAppId:delegate:}
 *          或在调用 destroy{@link #destroy} 之后调用该方法，则会返回 nil 。
 */
+ (ByteRTCEngineKit * _Nullable) sharedInstance;

/**
 * @type api
 * @region 引擎管理
 * @author chenweiming.push
 * @brief 创建引擎对象。<br>
 *        如果当前线程中未创建引擎实例，那么你必须先使用此方法，以使用 RTC 提供的各种音视频能力。  <br>
 *        如果当前线程中已创建了引擎实例，再次调用此方法时，会创建另一个独立的引擎实例。
 * @param appId 每个应用的唯一标识符，由 RTC 控制台随机生成的。
 *              不同的 AppId 生成的实例在 RTC 中进行音视频通话完全独立，无法互通。
 * @param delegate SDK 回调给应用层的 delegate，详见 ByteRTCEngineDelegate{@link #ByteRTCEngineDelegate}
 * @param parameters 用以覆盖默认参数的本引擎实例参数。JSON 字符串格式。
 * @return 可用的 ByteRTCEngineKit{@link #ByteRTCEngineKit} 实例
 * @notes 通常不建议在移动端设备上创建多于 2 个引擎实例。
 */
- (id _Nonnull)initWithAppId:(NSString * _Nonnull)appId
                    delegate:(id<ByteRTCEngineDelegate> _Nullable)delegate
                  parameters:(NSDictionary* _Nullable)parameters;

/**
 * @type api
 * @region 引擎管理
 * @author chenweiming.push
 * @brief 创建引擎对象，此方法应该作为正常 SDK 流程中的第一步操作，通过创建一个引擎实例，来使用 SDK 的其他能力
 * @param appId 每个应用的唯一标识符，由 VRTC 控制台随机生成的。不同的 AppId 生成的实例在 VRTC
 *              中进行音视频通话完全独立，无法互通。
 * @param delegate SDK 回调给应用层的 delegate，详见 ByteRTCEngineDelegate{@link #ByteRTCEngineDelegate}
 * @param parameters 保留参数
 * @param monitorDelegate  <br>
 *        监控信息的回调 delegate, 详见 ByteRTCMonitorDelegate{@link #ByteRTCMonitorDelegate}
 * @return 可用的 ByteRTCEngineKit{@link #ByteRTCEngineKit} 实例
 * @notes
 *      1. 连续多次调用该方法会创建不同的 ByteRTCEngineKit{@link #ByteRTCEngineKit}
 *      2. 必须使用相同的App ID，App间才能进行通话
 */
- (id _Nonnull)initWithAppId:(NSString * _Nonnull)appId
                    delegate:(id<ByteRTCEngineDelegate> _Nullable)delegate
             monitorDelegate:(id<ByteRTCMonitorDelegate> _Nullable)monitorDelegate
                  parameters:(NSDictionary* _Nullable)parameters
                  __deprecated_msg("Will be removed in new version");

/**
 * @type api
 * @region 引擎管理
 * @author chenweiming.push
 * @brief 手动销毁引擎实例对象，如果当前的引擎对象是通过 sharedEngineWithAppId:delegate:{@link #sharedEngineWithAppId:delegate:}
 *      所创建的，则行为与 destroy{@link #destroy} 保持一致
 * @notes
 *      + 请确保和需要销毁的 ByteRTCEngineKit{@link #ByteRTCEngineKit} 实例相关的业务场景全部结束后，才调用此方法  <br>
 *      + 该方法在调用之后，会销毁所有和此 ByteRTCEngineKit{@link #ByteRTCEngineKit} 实例相关的内存，并且停止与媒体服务器的任何交互  <br>
 *      3. 本方法为阻塞调用，会阻塞当前线程直到SDK彻底完成退出逻辑，因而需要注意不要在回调线程中
 *      直接调用本方法，也需要注意不要在回调方法中等待主线程的执行，而同时在主线程调用本方法，从而
 *      造成死锁
 *      4. 可以通过 Objective-C 的ARC机制，在 dealloc 时自动触发销毁逻辑
 */
- (void)destroyEngine;
/**
 * @type api
 * @region 引擎管理
 * @author chenweiming.push
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
 * @author chenweiming.push
 * @brief 获取 SDK 当前的版本号。
 * @return SDK 当前的版本号。
 */
+ (NSString * _Nonnull)getSdkVersion;

/**
 * @type api
 * @hidden
 * @deprecated
 * @region 引擎管理
 * @author chenweiming.push
 * @brief 设置 JSON 格式的字符串参数，配置 RTC 引擎参数。
 * @param parameters  <br>
 *        JSON 格式的字符串参数。
 * @return  <br>
 *        + 0： 成功。  <br>
 *        + <0： 失败。
 * @notes  <br>
 *        + 需要在引擎初始化之前调用。
 */
+ (int)setParameters:(NSString* _Nullable)parameters
    __deprecated_msg("Will be removed in new version");

/**
 * @type api
 * @region 房间管理
 * @author shenpengliang
 * @brief 设置用户角色。  <br>
 *        通过设置不同的用户角色，可以控制用户在房间内的行为：<br>
 *        + 能否发布音视频流；<br>
 *        + 用户自身是否在房间中隐身。<br>
 * @param role 用户角色，参看 ByteRTCUserRoleType{@link #ByteRTCUserRoleType}。  <br>
 * @return 方法调用结果。  <br>
 *         + YES: 方法调用成功  <br>
 *         + NO: 方法调用失败  <br>
 * @notes  <br>
 *        + 在加入房间前后，用户均可调用此方法设置用户角色。 <br>
 *        + 在房间内，调用此方法成功切换角色后，房间内其他用户会收到相应的回调通知：<br>
 *            - 从静默观众切换至主播时，房间内其他用户会收到 rtcEngine:onUserJoined:elapsed:{@link #rtcEngine:onUserJoined:elapsed:}；  <br>
 *            - 从主播切换至静默观众时，房间内其他用户会收到 rtcEngine:onUserLeave:reason:{@link #rtcEngine:onUserLeave:reason:} 。
 */
- (BOOL)setUserRole:(ByteRTCUserRoleType)role;

/**
 * @type api
 * @region 房间管理
 * @author shenpengliang
 * @brief 获取当前用户角色。  <br>
 * @return 当前用户角色，详见 ByteRTCUserRoleType{@link #ByteRTCUserRoleType} 枚举类型。  <br>
 */
- (ByteRTCUserRoleType)clientRole;

/**
 * @type api
 * @region 房间管理
 * @author shenpengliang
 * @brief 创建/加入房间：房间不存在时即创建房间；房间存在时即加入这个房间。
 *        同一房间内的用户间可以相互通话。  <br>
 *        用户调用 sharedEngineWithAppId:delegate:{@link #ByteRTCEngineKit#sharedEngineWithAppId:delegate:} 创建 RTC 引擎后，需调用此方法加入房间实现同其他用户进行音视频通话。  <br>
 *        如果用户调用此方法加入房间，则后续重复调用此方法均会失败，用户必须调用 leaveRoom:{@link #ByteRTCEngineKit#leaveRoom:} 退出当前房间后，才能加入下一个房间。  <br>
 *        本地用户调用此方法加入房间成功后，会收到 rtcEngine:onUserJoined:elapsed:{@link #ByteRTCEngineDelegate#rtcEngine:onUserJoined:elapsed:} 回调通知，远端用户会收到 rtcEngine:onUserJoined:elapsed:{@link #ByteRTCEngineDelegate#rtcEngine:onUserJoined:elapsed:} 回调通知。  <br>
 * @param token 动态密钥，用于对登录用户进行鉴权验证。  <br>
 *         进入房间需要携带 Token。测试时可使用控制台生成临时 Token ，正式上线需要使用密钥 SDK 在您的服务端生成并下发 Token 。  <br>
 * @param roomId 加入的房间 ID。  <br>
 *        房间 ID 为长度在 128 字节以内的非空字符串，支持以下字符集范围:  <br>
 *             1. 26 个大写字母 A ~ Z 。  <br>
 *             2. 26 个小写字母 a ~ z 。  <br>
 *             3. 10 个数字 0 ~ 9 。  <br>
 *             4. 下划线 "_"，at 符 "@"，减号 "-"。  <br>
 * @param roomProfile 房间模式。  <br>
 *        你应该根据业务需要，选择合适的房间模式。  <br>
 *        你必须在进房前设置房间模式，并且进房后不可更改。  <br>
 *        房间模式参看 ByteRTCRoomProfile{@link #ByteRTCRoomProfile}。
 * @param userInfo 用户信息，参看 ByteRTCUserInfo{@link #ByteRTCUserInfo}。  <br>
 * @return 方法调用结果。  <br>
 *         +  0: 成功  <br>
 *         + -1: roomId 为空，失败  <br>
 *         + -2: userId 为空，失败  <br>
 * @notes  <br>
 *        + 使用不同 App ID 的 App 是不能互通的。  <br>
 *        + 请务必保证生成 Token 使用的 App ID 和创建引擎时使用的 App ID 相同，否则会导致加入房间失败。  <br>
 *        + 用户加入房间成功后，在本地网络状况不佳的情况下，SDK 可能会与服务器失去连接，此时 SDK 将会自动重连。重连成功后，本地会收到 rtcEngine:onUserJoined:elapsed:{@link #ByteRTCEngineDelegate#rtcEngine:onUserJoined:elapsed:} 回调通知。  <br>
 *        + 同一个 App ID 的同一个房间内，每个用户的用户 ID 必须是唯一的。如果两个用户的用户 ID 相同，则后加入房间的用户会将先加入房间的用户踢出房间，并且先加入房间的用户会收到 rtcEngine:onError:{@link #ByteRTCEngineDelegate#rtcEngine:onError:} 回调通知，错误类型为重复登录 BRERR_DUPLICATE_LOGIN。  <br>
 */
- (int)joinRoomByKey:(NSString *_Nullable)token
              roomId:(NSString *_Nonnull)roomId
         roomProfile:(ByteRTCRoomProfile)roomProfile
            userInfo:(ByteRTCUserInfo *_Nonnull)userInfo;
/**
 *  @type api
 *  @region 房间管理
 *  @author shenpengliang
 *  @brief 离开房间。  <br>
 *         用户调用此方法离开房间，结束通话过程，释放所有通话相关的资源。  <br>
 *         调用 joinRoomByKey:roomId:roomProfile:userInfo:{@link #ByteRTCEngineKit#joinRoomByKey:roomId:roomProfile:userInfo:}
 *         方法加入房间后，必须调用此方法离开房间，否则无法进入下一个房间。无论当前是否在房间内，都可以调用此方法。重复调用此方法没有负面影响。  <br>
 *         此方法是异步操作，调用返回时并没有真正退出房间。真正退出房间后，SDK 会执行调用此方法时传入的 Block 块。  <br>
 *  @param leaveRoomBlock 离开房间完成后执行的 Block 块。Block 的输入参数为加入房间到离开房间过程间的统计信息，详见 ByteRTCRoomStats{@link #ByteRTCRoomStats}。  <br>
 *  @return 方法调用结果。  <br>
 *         +  0: 方法调用成功  <br>
 *         + <0: 方法调用失败  <br>
 *  @notes  <br>
 *        + 主播角色用户离开房间后，房间内其他用户会收到 rtcEngine:onUserLeave:reason:{@link #ByteRTCEngineDelegate#rtcEngine:onUserLeave:reason:} 回调通知。  <br>
 *        + 如果调用此方法后立即销毁引擎，SDK 将无法执行作为参数传入的 Block 块。  <br>
 */
- (int)leaveRoom:(void (^_Nullable)(ByteRTCRoomStats *_Nonnull stat))leaveRoomBlock;

/**
 * @type api
 * @region 房间管理
 * @author shenpengliang
 * @brief 更新 Token。  <br>
 *        Token 有一定的有效期，当 Token 过期时，用户需调用此方法更新房间的 Token 信息。  <br>
 *        用户调用 joinRoomByKey:roomId:roomProfile:userInfo:{@link #joinRoomByKey:roomId:roomProfile:userInfo:} 方法加入房间时，如果使用了过期的 Token 将导致加入房间失败，并会收到 rtcEngine:onJoinRoomResult:withUid:errorCode:joinType:elapsed:{@link #rtcEngine:onJoinRoomResult:withUid:errorCode:joinType:elapsed:} 回调通知，回调错误码为 ByteRtcErrorCode.ByteRTCErrorCodeInvalidToken{@link #ByteRtcErrorCode}。此时需要重新获取 Token，并调用此方法更新 Token。  <br>
 * @param token 更新的动态密钥。  <br>
 * @return 方法调用结果。  <br>
 *         +  0: 方法调用成功。  <br>
 *         + <0: 方法调用失败。  <br>
 * @notes  <br>
 *        + 如果用户因 Token 过期导致加入房间失败，则调用此方法更新 Token 后，SDK 会自动重新加入房间，而不需要用户自己调用 joinRoomByKey:roomId:roomProfile:userInfo:{@link #joinRoomByKey:roomId:roomProfile:userInfo:} 方法。  <br>
 *        + Token 过期时，如果已经加入房间成功，则不会受到影响。Token 过期的错误会在下一次使用过期的 Token 加入房间时，或因本地网络状况不佳导致断网重新连入房间时通知给用户。  <br>
 */
- (int)updateToken:(NSString *_Nonnull)token;

/**
 * @type api
 * @region 引擎管理
 * @author chenweiming.push
 * @brief 获取 SDK 内各种错误码、警告码的描述文字。
 * @param code  <br>
 *        通过 rtcEngine:onWarning:{@link #rtcEngine:onWarning:} 和 rtcEngine:onError:{@link #rtcEngine:onError:} 回调获得的值，
 *        具体可以参考 ByteRTCWarningCode{@link #ByteRTCWarningCode} 和 ByteRTCErrorCode{@link #ByteRTCErrorCode} 。
 * @return 描述文字。
 */
+ (NSString * _Nonnull)getErrorDescription:(NSInteger)code;

#pragma mark Core Audio Methods
/**
 *  -----------------------------------------------------------------------------
 * @name 音频核心方法
 *  -----------------------------------------------------------------------------
 */

/**
 * @type api
 * @region 音频管理
 * @author wangjunzheng
 * @brief 开启内部音频采集。默认为关闭状态。  <br>
 *        进房前调用该方法，本地用户会收到 rtcEngine:onMediaDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCEngineDelegate#rtcEngine:onMediaDeviceStateChanged:device_type:device_state:device_error} 的回调。  <br>
 *        进房后调用该方法，房间中的其他用户会收到 rtcEngine:onUserStartAudioCapture:{@link #ByteRTCEngineDelegate#rtcEngine:onUserStartAudioCapture:} 的回调。
 * @notes  <br>
 *       + 调用 stopAudioCapture{@link #stopAudioCapture} 可以关闭音频采集设备，否则，SDK 只会在销毁引擎的时候自动关闭设备。  <br>
 *       + 无论是否发布音频数据，你都可以调用该方法开启音频采集，并且调用后方可发布音频。  <br>
 *       + 尚未进房并且已使用自定义采集时，关闭自定义采集后并不会自动开启内部采集。你需调用此方法手动开启内部采集。
 */
- (void)startAudioCapture;

 /**
  * @type api
  * @region 音频管理
  * @author wangjunzheng
  * @brief 关闭内部音频采集。默认为关闭状态。  <br>
  *        进房前调用该方法，本地用户会收到 rtcEngine:onMediaDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCEngineDelegate#rtcEngine:onMediaDeviceStateChanged:device_type:device_state:device_error} 的回调。  <br>
  *        进房后调用该方法，房间中的其他用户会收到 rtcEngine:onUserStopAudioCapture:{@link #ByteRTCEngineDelegate#rtcEngine:onUserStopAudioCapture:} 的回调。
  * @notes  <br>
  *       + 调用 startAudioCapture{@link #startAudioCapture} 可以开启音频采集设备。  <br>
  *       + 设备开启后若一直未调用该方法关闭，则 SDK 会在销毁引擎的时候自动关闭音频采集设备。  <br>
  */
- (void)stopAudioCapture;

/**
 * @type api
 * @region 音频管理
 * @author wangjunzheng
 * @brief 设置音频场景类型。  <br>
 *        你可以根据你的应用所在场景，选择合适的音频场景类型。  <br>
 *        选择音频场景后，RTC 会自动根据客户端音频路由和发布订阅状态，适用通话音量/媒体音量。  <br>
 *        本方法在进房前和进房后设置均可生效。
 * @param audioScenario 音频场景类型，适用通话音量/媒体音量
 *        详见 ByteRTCAudioScenarioType{@link #ByteRTCAudioScenarioType}
 * @notes  <br>
 *        + 通话音量更适合通话、会议等对信息准确度更高的场景。通话音量会激活系统硬件信号处理，使通话声音更清晰。同时，音量无法降低到 0。  <br>
 *        + 媒体音量更适合娱乐场景，因其声音的表现力会更强。媒体音量下，最低音量可以为 0。
 */
- (void)setAudioScenario:(ByteRTCAudioScenarioType)audioScenario;

/**
 * @type api
 * @region 音频管理
 * @author wangjunzheng
 * @brief 控制本地音频流的发送状态：发送/不发送。  <br>
 *        使用此方法后，房间中的其他用户会收到回调 rtcEngine:onUserMuteAudio:muteState:{@link #ByteRTCEngineDelegate#rtcEngine:onUserMuteAudio:muteState:}。  <br>
 * @param muteState 发送状态，标识是否发送本地音频流，详见 ByteRTCMuteState{@link #ByteRTCMuteState}
 * @return 方法调用结果  <br>
 *         + 0：方法调用成功  <br>
 *        + <0：方法调用失败  <br>
 * @notes 本方法仅控制本地音频流的发送状态，并不影响本地音频采集状态。
 */
- (void)muteLocalAudio:(ByteRTCMuteState)muteState;


/**
 * @type api
 * @region 音频管理
 * @author wangjunzheng
 * @brief 设置对来自指定远端用户的音频流的接收状态。默认为接收。
 * @param uid 指定远端用户的 ID
 * @param muteState 接收状态，标识是否接收远端音频流，详见 ByteRTCMuteState{@link #ByteRTCMuteState}
 */
- (void)muteRemoteAudio:(NSString * _Nonnull)uid muteState:(ByteRTCMuteState)muteState;

/**
 * @type api
 * @region 音频管理
 * @author wangjunzheng
 * @brief 设置对来自远端的所有音频流的接收状态。默认为接收。
 * @param muteState 接收状态，标识是否接收远端音频流，详见 ByteRTCMuteState{@link #ByteRTCMuteState}
 * @notes 本方法只影响本地是否接收远端音频流，并不影响远端音频设备的采集发送功能。
 */
- (void)muteAllRemoteAudio:(ByteRTCMuteState)muteState;

/**
 * @type api
 * @region 音频管理
 * @author wangjunzheng
 * @brief 开启/关闭音量提示。默认关闭。<br>
 *        开启音量提示后，将按设置的时间间隔收到本地采集音量或订阅的远端用户的音量信息回调。
 *        关于回调的具体信息，参看 rtcEngine:onAudioVolumeIndication:totalRemoteVolume:{@link #ByteRTCEngineDelegate#rtcEngine:onAudioVolumeIndication:totalRemoteVolume:}。
 * @param interval 收到音量提示回调的时间间隔  <br>
 *                + ≤ 0：禁用音量提示功能。  <br>
 *                + > 0：启用音量提示功能，并设置收到音量提示回调的时间间隔。单位为毫秒。<br>
 *                建议设置为大于等于 200 毫秒；小于 10 毫秒时，行为未定义。
 */
- (void)setAudioVolumeIndicationInterval:(NSInteger)interval;

/**
 * @type api
 * @region 音频管理
 * @author wangjunzheng
 * @brief 调节音频采集音量。
 * @param volume 音频采集音量，取值范围： [0,400]  <br>
 *       + 0: 静音  <br>
 *       + 100: 原始音量  <br>
 *       + 400: 最大可为原始音量的 4 倍(自带溢出保护)  <br>
 * @notes 为保证更好的通话质量，建议将 volume 值设为 [0,100]。
 */
- (void)setRecordingVolume:(NSInteger)volume;

/**
 * @type api
 * @region 音频管理
 * @author wangjunzheng
 * @brief 调节本地播放的所有远端用户混音后的音量。
 * @param volume 音频播放音量，取值范围：[0,400]  <br>
 *       + 0: 静音  <br>
 *       + 100: 原始音量  <br>
 *       + 400: 最大可为原始音量的 4 倍(自带溢出保护)  <br>
 * @notes 为保证更好的通话质量，建议将 volume 值设为 [0,100]。
 */
- (void)setPlaybackVolume:(NSInteger)volume;

#pragma mark Core Video Methods
/**-----------------------------------------------------------------------------
 * @name 视频核心方法
 * -----------------------------------------------------------------------------
 */

/**
 * @type api
 * @region 自定义视频采集渲染
 * @author sunhang.io
 * @brief 设置本地视频外部渲染器。
 * @param videoRenderer 外部渲染器，具体参照 ByteRTCVideoSinkProtocol{@link #ByteRTCVideoSinkProtocol}
 * @return  <br>
 *         + 0：方法调用成功  <br>
 *         + <0：方法调用失败  <br>
 */
- (int)setLocalVideoRenderer:(id<ByteRTCVideoSinkProtocol> _Nullable)videoRenderer;

/**
 * @type api
 * @region 自定义视频采集渲染
 * @author sunhang.io
 * @brief 设置本地视频外部渲染器。
 * @param videoRenderer 外部渲染器，具体参照 ByteRTCVideoSinkProtocol{@link #ByteRTCVideoSinkProtocol}
 * @param roomId 房间ID
 * @param userId 用户ID
 * @return  <br>
 *         + 0：方法调用成功  <br>
 *         + <0：方法调用失败  <br>
 */
- (int)setLocalVideoRenderer:(id<ByteRTCVideoSinkProtocol> _Nullable)videoRenderer
                   forRoomId:(NSString * _Nonnull)roomId
                   forUserId:(NSString * _Nonnull)userId;


/**
 * @type api
 * @region 自定义视频采集渲染
 * @author sunhang.io
 * @brief 设置特定远端用户的外部渲染器。
 * @param videoRenderer 外部渲染器，具体参照 ByteRTCVideoSinkProtocol{@link #ByteRTCVideoSinkProtocol}
 * @param roomId 房间ID
 * @param userId 用户ID
 * @return  <br>
 *         + 0：方法调用成功  <br>
 *         + <0：方法调用失败  <br>
 */
- (int)setRemoteVideoRenderer:(id<ByteRTCVideoSinkProtocol> _Nullable)videoRenderer
                    forRoomId:(NSString * _Nonnull)roomId
                    forUserId:(NSString * _Nonnull)userId;

/**
 * @type api
 * @region 自定义视频采集渲染
 * @author sunhang.io
 * @brief 设置特定远端用户的外部渲染器。
 * @param videoRenderer 外部渲染器，具体参照 ByteRTCVideoSinkProtocol{@link #ByteRTCVideoSinkProtocol}
 * @param userId 用户ID
 * @return  <br>
 *         + 0：方法调用成功  <br>
 *         + <0：方法调用失败  <br>
 */
- (int)setRemoteVideoRenderer:(id<ByteRTCVideoSinkProtocol> _Nullable)videoRenderer
                    forUserId:(NSString * _Nonnull)userId;

/**
 * @type api
 * @region 自定义视频采集渲染
 * @author sunhang.io
 * @brief 设置远端屏幕共享的外部渲染器。
 * @param screenRenderer
 *         外部渲染器，具体参照 ByteRTCVideoSinkProtocol{@link #ByteRTCVideoSinkProtocol}
 * @param roomId
 *         房间ID
 * @param userId
 *         用户ID
 * @return  <br>
 *         + 0：方法调用成功  <br>
 *         + -1：方法调用失败  <br>
 * @notes
 *         在应用开发中，通常在应用收到 rtcEngine:onFirstRemoteVideoFrameRendered:withFrameInfo:{@link #rtcEngine:onFirstRemoteVideoFrameRendered:withFrameInfo:} 事件后调用该方法进行远端视频设置。
 */
- (int)setupRemoteScreenRenderer:(id<ByteRTCVideoSinkProtocol> _Nullable)screenRenderer
                       forRoomId:(NSString * _Nonnull)roomId
                       forUserId:(NSString * _Nonnull)userId;

/**
 * @type api
 * @region 自定义视频采集渲染
 * @author sunhang.io
 * @brief 设置远端屏幕共享的外部渲染器。
 * @param screenRenderer
 *         外部渲染器，具体参照 ByteRTCVideoSinkProtocol{@link #ByteRTCVideoSinkProtocol}
 * @param userId
 *         用户ID
 * @return  <br>
 *         + 0：方法调用成功  <br>
 *         + -1：方法调用失败  <br>
 * @notes
 *         在应用开发中，通常在应用收到 rtcEngine:onFirstRemoteVideoFrameRendered:withFrameInfo:{@link #rtcEngine:onFirstRemoteVideoFrameRendered:withFrameInfo:} 事件后调用该方法进行远端视频设置
 */
- (int)setupRemoteScreenRenderer:(id<ByteRTCVideoSinkProtocol> _Nullable)screenRenderer
                       forUserId:(NSString * _Nonnull)userId;

/**
 * @type api
 * @region 视频管理
 * @author liyi.000
 * @brief 启动推送多路视频流，设置推送多路流时的各路视频参数，
 *        包括分辨率、帧率、码率、缩放模式、网络不佳时的回退策略等。
 * @param videoSolutions 视频参数数组首地址，参看 ByteRTCVideoSolution{@link #ByteRTCVideoSolution}。  <br>
 *        + 若选取的帧率为 5 FPS，则推算码率为<视频属性 (Profile) 参考表>推荐码率除以 2  <br>
 *        + 若选取的帧率为 15 FPS，则推算码率为<视频属性 (Profile) 参考表>推荐码率
 *        + 若选取的帧率为 30 FPS，则推算码率为<视频属性 (Profile) 参考表>码率乘以 1.5  <br>
 *        + 若选取其余帧率，等比例推算即可  <br>
 *        + 若设置的视频码率超出合理范围，SDK 会自动按照合理区间处理码率  <br>
 * @return  <br>
 *         + 0：方法调用成功  <br>
 *         + <0：方法调用失败  <br>
 */
- (int)setVideoEncoderConfig:(NSArray <ByteRTCVideoSolution *> * _Nullable)videoSolutions;

/**
 * @type api
 * @region 视频管理
 * @author liyi.000
 * @brief 设置本地视频渲染时，使用的视图，并设置渲染模式。  <br>
 *        你应在加入房间前，绑定本地视图。退出房间后，此设置仍然有效。
 *        如果需要解除绑定，你可以调用本方法绑定空视图。
 * @param streamIndex 流属性，参看 ByteRTCStreamIndex:{@link #ByteRTCStreamIndex}
 * @param canvas 视图信息和渲染模式，参看 ByteRTCVideoCanvas:{@link #ByteRTCVideoCanvas}
 * @return  <br>
 *         + 0：方法调用成功  <br>
 *         + <0：方法调用失败  <br>
 */
- (int)setLocalVideoCanvas:(ByteRTCStreamIndex)streamIndex
                withCanvas:(ByteRTCVideoCanvas * _Nullable)canvas;
/**
 * @type api
 * @region 视频管理
 * @author liyi.000
 * @brief 设置来自指定远端用户 user_id 的视频渲染时，使用的视图，并设置渲染模式。  <br>
 *        如果需要解除某个用户的绑定视图，你可以把 view 设置为空。
 * @notes  <br>
 *       + 实际使用时，你可以在收到回调 rtcEngine:onUserJoined:elapsed:{@link #rtcEngine:onUserJoined:elapsed:} 或 onFirstRemoteVideoFrame{@link #onfirstremotevideoframe} 时获得远端用户 user_id。
 *         这两个回调的差别是：如果启用了视频录制功能，视频录制服务会作为一个哑客户端加入房间，因此其他客户端会收到对应的 rtcEngine:onUserJoined:elapsed:{@link #rtcEngine:onUserJoined:elapsed:} 回调；
 *         而不会收到 onFirstRemoteVideoFrame{@link #onfirstremotevideoframe} 回调。你不应给录制的亚客户端绑定视图（因为它不会发送视频流）。
 *       + 你应在加入房间后，绑定视图。退出房间后，此设置失效。
 * @param uid 视频来源的远端用户 ID
 * @param streamIndex 视频流属性，参看 ByteRTCStreamIndex:{@link #ByteRTCStreamIndex}
 * @param canvas 视图信息和渲染模式，参看 ByteRTCVideoCanvas:{@link #ByteRTCVideoCanvas}
 * @return  <br>
 *         + 0：方法调用成功  <br>
 *         + <0：方法调用失败  <br>
 */
- (int)setRemoteVideoCanvas:(NSString * _Nonnull)uid
                  withIndex:(ByteRTCStreamIndex)streamIndex
             withCanvas:(ByteRTCVideoCanvas * _Nullable)canvas;

 /**
  * @type api
  * @region 视频管理
  * @author liyi.000
  * @brief 开启内部视频采集。默认为关闭状态。  <br>
  *        进房前调用该方法，本地用户会收到 rtcEngine:onMediaDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCEngineDelegate#rtcEngine:onMediaDeviceStateChanged:device_type:device_state:device_error} 的回调。  <br>
  *        进房后调用该方法，房间中的其他用户会收到 rtcEngine:onUserStartVideoCapture:{@link #ByteRTCEngineDelegate#rtcEngine:onUserStartVideoCapture:} 的回调。
  * @notes  <br>
  *       + 调用 stopVideoCapture{@link #stopVideoCapture} 可以关闭视频采集设备，否则，SDK 只会在销毁引擎的时候自动关闭设备。  <br>
  *       + 无论是否发布视频数据，你都可以调用该方法开启视频采集，并且调用后方可发布视频。  <br>
  *       + 已使用自定义采集时，关闭自定义采集后并不会自动开启内部采集。你需调用此方法手动开启内部采集。
  */
- (void)startVideoCapture;

 /**
  * @type api
  * @region 视频管理
  * @author liyi.000
  * @brief 关闭内部视频采集。默认为关闭状态。  <br>
  *        进房前调用该方法，本地用户会收到 rtcEngine:onMediaDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCEngineDelegate#rtcEngine:onMediaDeviceStateChanged:device_type:device_state:device_error} 的回调。  <br>
  *        进房后调用该方法，房间中的其他用户会收到 rtcEngine:onUserStopVideoCapture:{@link #ByteRTCEngineDelegate#rtcEngine:onUserStopVideoCapture:} 的回调。
  * @notes  <br>
  *       + 调用 startVideoCapture{@link #startVideoCapture} 可以开启视频采集设备。  <br>
  *       + 设备开启后若一直未调用该方法关闭，则 SDK 会在销毁引擎的时候自动关闭音频采集设备。  <br>
  */
- (void)stopVideoCapture;

/**
 * @type api
 * @region 视频管理
 * @author liyi.000
 * @brief 停止/启动发送本地视频流，默认不发送。<br>
 *        无论你使用 SDK 的视频采集编码功能，还是使用自定义采集功能，你都应使用此接口启动发送本地视频流。<br>
 *        调用该方法后，房间中的其他用户会收到 rtcEngine:onUserMuteVideo:withMuteState:{@link #rtcEngine:onUserMuteVideo:withMuteState:} 的回调。
 * @param mute_state 发送状态，标识是否发送本地视频流，参看 ByteRTCMuteState{@link #ByteRTCMMuteState}
 * @notes 本方法只是停止/启动本地视频流的发送，不影响视频采集状态。
 */
- (void)muteLocalVideo:(ByteRTCMuteState)mute_state;

/**
 * @type api
 * @region 视频管理
 * @author liyi.000
 * @brief 设置是否播放远端视频流
 * @param uid 视频来源的远端用户 ID
 * @param muteState 播放状态，标识是否播放远端视频流，参看 ByteRTCMuteState{@link #ByteRTCMuteState}
 * @return  <br>
 *         + 0：方法调用成功  <br>
 *         + <0：方法调用失败  <br>
 */
- (int)muteRemoteVideo:(NSString * _Nonnull)uid
                        withMuteState:(ByteRTCMuteState)muteState;

/**
 * @type api
 * @region 视频管理
 * @author liyi.000
 * @brief 设置是否播放所有远端视频流
 * @param muteState 播放状态，标识是否播放远端视频流，参看 ByteRTCMuteState{@link #ByteRTCMuteState}
 * @return  <br>
 *         + 0：方法调用成功  <br>
 *         + <0：方法调用失败  <br>
 */
- (int)muteAllRemoteVideo:(ByteRTCMuteState)muteState;

/**
 * @type api
 * @region 视频管理
 * @author zhangzhenyu.samuel
 * @brief 设置采用前置摄像头采集时，是否开启镜像模式。默认为关闭状态。 <br>
 *        调用后，你会收到回调：rtcEngine:didMirrorStateChanged:{@link #rtcEngine:didMirrorStateChanged:}
 * @param mode 是否开启镜像模式，参看 ByteRTCMirrorMode{@link #ByteRTCMirrorMode}
 * @return  <br>
 *         + 0：成功  <br>
 *         + <0：失败  <br>
 */
- (int)setLocalVideoMirrorMode:(ByteRTCMirrorMode) mode;

/**
 * @type api
 * @region 视频管理
 * @author liyi.000
 * @brief 获取本地视频镜像状态
 * @return  当前镜像状态  <br>
 *         + true：镜像为打开状态  <br>
 *         + false：镜像为关闭状态  <br>
 */
- (bool)isLocalVideoMirrorOn;

/**
 * @type api
 * @region 视频管理
 * @author liyi.000
 * @brief 切换移动端前置/后置摄像头
 * @param cameraId 移动端摄像头 ID，参看 ByteRTCCameraID{@link #ByteRTCCameraID}。  <br>
 * @return  <br>
 *         + 0：方法调用成功  <br>
 *         + <0：方法调用失败  <br>
 */
- (int)switchCamera:(ByteRTCCameraID) cameraId;

/**
 * @type api
 * @region 视频管理
 * @author zhangzhenyu.samuel
 * @brief 视频图像分割，替换背景
 * @param mode 背景模式，用于设置预制背景、是否虚化等。参看 ByteRTCBackgroundMode{@link #ByteRTCBackgroundMode}
 * @param divideModel 选择使用哪种分割模型。参看 ByteRTCDivideModel{@link #ByteRTCDivideModel}
 * @return  <br>
 *        + 0：方法调用成功  <br>
 *        + <0：方法调用失败  <br>
 */
- (int)replaceBackground:(ByteRTCBackgroundMode)mode
          withDivideModel:(ByteRTCDivideModel)divideModel;


/**
 * @type api
 * @region 视频特效
 * @author zhangzhenyu.samuel
 * @brief 视频特效许可证检查
 * @param licenseFile  <br>
 *        许可证文件绝对路径
 * @return  <br>
 *      + 0: 许可证验证成功  <br>
 *      + !0: 许可证验证失败
 * @notes enableVideoEffect:{@link #ByteRTCEngineKit#enableVideoEffect:} 开始使用视频特效前，需要先调用这个方法进行许可证验证
 */
- (int)checkVideoEffectLicense:(NSString * _Nonnull)licenseFile;

/**
 * @type api
 * @region 视频特效
 * @author zhangzhenyu.samuel
 * @brief 创建/销毁视频特效引擎
 * @param enabled  <br>
 *        是否创建视频特效引擎  <br>
 *       + true: 创建  <br>
 *       + false: 销毁
 * @return 方法调用结果  <br>
 *        + 0: 成功  <br>
 *        + !0: 失败
 * @notes  <br>
 *       + 该方法须在调用 checkVideoEffectLicense:{@link #ByteRTCEngineKit#checkVideoEffectLicense:} 和 setVideoEffectAlgoModelPath:{@link #ByteRTCEngineKit#setVideoEffectAlgoModelPath:} 后调用。  <br>
 *       + 该方法不直接开启/关闭视频特效，你须在调用该方法后，调用 setVideoEffectNodes:{@link #ByteRTCEngineKit#setVideoEffectNodes:} 开启视频特效。  <br>
 *       + 通用场景下，特效引擎会随 RTC 引擎销毁而销毁。当你对性能有较高要求时，可在不使用特效相关功能时调用该方法中 false 单独销毁特效引擎。
 */
- (int)enableVideoEffect:(BOOL)enabled;

/**
 * @type api
 * @region 视频特效
 * @author zhangzhenyu.samuel
 * @brief 设置视频特效算法模型路径
 * @param modelPath  <br>
 *        模型路径
 */
- (void)setVideoEffectAlgoModelPath:(NSString * _Nonnull)modelPath;

/**
 * @type api
 * @region 视频特效
 * @author zhangzhenyu.samuel
 * @brief 设置视频特效素材包，支持同时设置多个素材包
 * @param effectNodePaths  <br>
 *        特效素材包路径数组
 * @return  <br>
 *      + 0: 调用成功  <br>
 *      + 1000: 未集成 CV SDK  <br>
 *      + 1001: 本 RTC 版本不支持 CV 功能  <br>
 *      + <0: 调用失败，具体错误码，请参考 <a href="http://ailab-cv-sdk.bytedance.com/docs/2036/99783/">CV SDK 文档 </a>。
 * @notes 在调用这个方法之前，你须先调用 enableVideoEffect:{@link #ByteRTCEngineKit#enableVideoEffect:} 。
 */
- (int) setVideoEffectNodes:(NSArray <NSString *> *_Nonnull)effectNodePaths;

/**
 * @type api
 * @region 视频特效
 * @author zhangzhenyu.samuel
 * @brief 设置特效强度
 * @param nodePath  <br>
 *        特效素材包路径。
 * @param nodeKey  <br>
 *        需要设置的素材 key 名称。参看 <a href="http://ailab-cv-sdk.bytedance.com/docs/2036/99769/"> 素材key对应说明</a>。
 * @param nodeValue  <br>
 *        需要设置的强度值。取值范围为 [0,1]，超出该范围设置无效。
 * @return  <br>
 *      + 0: 调用成功  <br>
 *      + 1000: 未集成 CV SDK  <br>
 *      + 1001: 本 RTC 版本不支持 CV 功能  <br>
 *      + <0: 调用失败，具体错误码，请参考 <a href="http://ailab-cv-sdk.bytedance.com/docs/2036/99783/">CV SDK 文档 </a>。
 * @notes 该接口仅适用于同时含有上述三个参数的特效资源，对于如大部分贴纸类等没有强度参数的特效，该接口调用无效。
 */
- (int) updateVideoEffectNode:(NSString * _Nonnull)nodePath nodeKey:(NSString * _Nonnull)nodeKey  nodeValue:(float) nodeValue;

/**
 * @type api
 * @region 视频特效
 * @author zhangzhenyu.samuel
 * @brief 设置颜色滤镜
 * @param resPath  <br>
 *        滤镜资源包绝对路径
 * @return  <br>
 *      + 0: 调用成功  <br>
 *      + 1000: 未集成 CV SDK  <br>
 *      + 1001: 本 RTC 版本不支持 CV 功能  <br>
 *      + <0: 调用失败，具体错误码，请参考<a href="http://ailab-cv-sdk.bytedance.com/docs/2036/99783/">CV SDK文档 </a>。
 */
- (int) setVideoEffectColorFilter:(NSString * _Nonnull)resPath;

/**
 * @type api
 * @region 视频特效
 * @author zhangzhenyu.samuel
 * @brief 设置已启用的颜色滤镜强度
 * @param intensity  <br>
 *        滤镜强度  <br>
 *        取值范围 [0,1]，超出范围时设置无效
 * @return  <br>
 *      + 0: 调用成功  <br>
 *      + 1000: 未集成 CV SDK  <br>
 *      + 1001: 本 RTC 版本不支持 CV 功能  <br>
 *      + <0: 调用失败，具体错误码，请参考 <a href="http://ailab-cv-sdk.bytedance.com/docs/2036/99783/">CV SDK 文档 </a>。
 */
- (int) setVideoEffectColorFilterIntensity:(float) intensity;


#pragma mark - MediaMetadataData InnerVideoSource
/**
 * @type api
 * @region 视频数据回调
 * @author sunhang.io
 * @brief 注册 metadata 观察者，用于接收或发送 metadata，底层通过在视频帧中添加 SEI 数据实现该功能。  <br>
 *        注册观察者后，发送的视频帧里面没有 SEI 信息， 会触发 videoFrameMediaMetaDataAtTime:{@link #videoFrameMediaMetaDataAtTime:} 回调。  <br>
 *        注册观察者后，接收的视频帧里面有 SEI 信息，会触发接收 receiveVideoFrameFromUID:withExtendedData:atTimestamp:{@link #receiveVideoFrameFromUID:withExtendedData:atTimestamp:} 回调。  <br>
 * @param [in] metadataObserver metadata 观察者，详见： ByteRTCMediaMetadataObserver{@link #ByteRTCMediaMetadataObserver}
 * @return  <br>
 *         + YES: 设置成功  <br>
 *         + NO: 设置失败  <br>
 * @notes  <br>
 *      + 使用视频自定义采集与渲染时，可以直接在视频帧中添加与获取 metadata，不建议使用本接口。
 *      + 本接口支持动态取消注册，将参数设置为 nullptr 取消注册。  <br>
 */
- (BOOL)setMediaMetadataObserver:(_Nullable id<ByteRTCMediaMetadataObserver>) metadataObserver;

#pragma mark - VideoFrameObserver InnerVideoSource
/**
 * @hidden
 * @type api
 * @region 视频数据回调
 * @author sunhang.io
 * @brief 注册视频数据回调观察者
 * @param frameObserver 视频数据回调的观察者对象，详见： ByteRTCVideoFrameObserver{@link #ByteRTCVideoFrameObserver} 。
 *        将参数设置为 nullptr 取消注册。
 * @return  <br>
 *        + YES： 设置成功
 *        + NO： 设置失败
 * @notes  <br>
 *       + 该方法可以在任意时间调用，建议在 joinRoomByKey:roomId:roomProfile:userInfo:{@link #joinRoomByKey:roomId:roomProfile:userInfo:} 前。
 *       + 将参数设置为 nullptr 取消注册。  <br>
 */
- (BOOL)setVideoFrameObserver:(_Nullable id<ByteRTCVideoFrameObserver>) frameObserver;

#pragma mark - LocalEncodedVideoFrameObserver
/**
 * @type api
 * @region 视频数据回调
 * @author sunhang.io
 * @brief 注册本地视频帧监测器。  <br>
 *        无论使用内部采集还是自定义采集，调用该方法后，SDK 每监测到一帧本地视频帧时，都会将视频帧信息通过 onLocalEncodedVideoFrame:Frame:{@link #onLocalEncodedVideoFrame:Frame:} 回调给用户
 * @param frameObserver 本地视频帧监测器，参看 ByteRTCLocalEncodedVideoFrameObserver{@link #ByteRTCLocalEncodedVideoFrameObserver}。将参数设置为 nullptr 则取消注册。
 * @notes 该方法可在进房前后任意时间调用，在进房前调用可保证尽可能早地监测视频帧并触发回调
 */
- (void)registerLocalEncodedVideoFrameObserver:(_Nullable id<ByteRTCLocalEncodedVideoFrameObserver>) frameObserver;

#pragma mark Subscribe Controller Methods
/**-----------------------------------------------------------------------------
 * @name 自定义订阅方法
 * -----------------------------------------------------------------------------
 */

/**
 * @type api
 * @region 房间管理
 * @author shenpengliang
 * @brief 设置订阅模式。  <br>
 *        用户调用此方法设置房间中是音视频流的订阅模式。默认自动订阅。  <br>
 *        如需开启手动订阅功能，建议在调用 joinRoomByKey:roomId:roomProfile:userInfo:{@link #joinRoomByKey:roomId:roomProfile:userInfo:}方法加入房间前完成设置。  <br>
 * @param audioMode 音频流的订阅模式。参看 ByteRTCSubscribeMode{@link #ByteRTCSubscribeMode} 。  <br>
 * @param videoMode 视频流的订阅模式。参看 ByteRTCSubscribeMode{@link #ByteRTCSubscribeMode} 。  <br>
 * @return 方法执行结果。  <br>
 *         + YES: 方法调用成功。  <br>
 *         + NO: 方法调用失败。  <br>
 */
- (BOOL)enableAutoSubscribe:(ByteRTCSubscribeMode)audioMode videoMode:(ByteRTCSubscribeMode)videoMode;

/**
 * @type api
 * @region 房间管理
 * @author shenpengliang
 * @brief 订阅指定的房间内远端音视频流。  <br>
 *         关闭自动订阅功能，使用手动订阅模式时用户调用此方法按需订阅房间中的音视频流。  <br>
 *         此方法仅在关闭自动订阅功能时生效。用户需在加入房间前调用 enableAutoSubscribe:videoMode:{@link #enableAutoSubscribe:videoMode:} 方法关闭自动订阅功能以使用手动订阅模式。
 * <br> 订阅流失败时，SDK 会按失败原因回调 rtcEngine:onError:{@link #ByteRTCEngineDelegate#rtcEngine:onError:} 通知用户，具体错误可参考错误码
 * ByteRTCErrorCode{@link #ByteRTCErrorCode} 描述。  <br>
 * @param userId 指定订阅的远端音视频流的发布用户的用户ID 。  <br>
 * @param info 选择订阅配置，详见数据结构 ByteRTCSubscribeConfig{@link #ByteRTCSubscribeConfig} 。  <br>
 * @notes <br>
 *        + 此方法仅支持订阅当前房间中的远端音视频流。如果指定的流在当前房间内不曾存在，则 SDK 不会订阅。  <br>
 *        + 用户调用 joinRoomByKey:token roomId:roomProfile:userInfo:{@link #joinRoomByKey:token
 * roomId:roomProfile:userInfo:}方法加入房间后：1.当房间内有新的音视频流发布时，本地会收到 rtcEngine:onStreamAdd:{@link
 * #ByteRTCEngineDelegate#rtcEngine:onStreamAdd:} 回调通知；2.当房间内音视频流停止发布时，本地会收到 rtcEngine:didStreamRemoved:stream:reason:{@link
 * #ByteRTCEngineDelegate#rtcEngine:didStreamRemoved:stream:reason:}
 * 回调通知。通过这两个回调用户可以获得当前房间中的音视频流信息，并在需要时调用此方法订阅指定音视频流。  <br>
 */
- (void)subscribeStream:(NSString *_Nonnull)userId subscribeConfig:(ByteRTCSubscribeConfig *_Nonnull)info;

/**
 * @type api
 * @region 房间管理
 * @author shenpengliang
 * @brief 停止订阅指定的房间内远端音视频流。  <br>
 *         关闭自动订阅功能，使用手动订阅模式时用户调用此方法停止订阅已订阅的音视频流。  <br>
 *         此方法仅在关闭自动订阅功能时生效。用户需在加入房间前调用 enableAutoSubscribe:videoMode:{@link #enableAutoSubscribe:videoMode::} 方法关闭自动订阅功能以使用手动订阅模式。  <br>
 * @param userId 指定订阅的远端音视频流的发布用户的用户ID。  <br>
 * @param isScreen 订阅的流是否是屏幕共享流。  <br>
 * @notes  <br>
 *        + 不管是否订阅了指定的远端音视频流，都可以调用此方法停止订阅。停止订阅的 streamId 无效或未订阅时，SDK不会做任何处理，没有负面影响。  <br>
 */
- (void)unSubscribeStream:(NSString *_Nonnull)userId isScreen:(BOOL)isScreen;

#pragma mark Audio Routing Controller
/**-----------------------------------------------------------------------------
 * @name 音频播放路由
 * -----------------------------------------------------------------------------
 */

/**
 * @type api
 * @region 音频管理
 * @author wangjunzheng
 * @brief 设置音频播放设备为扬声器或者听筒，默认使用扬声器。  <br>
 *        音频播放设备发生变化时，会收到 rtcEngine:onAudioPlaybackDeviceChanged:{@link #rtcEngine:onAudioPlaybackDeviceChanged:} 回调。  <br>
 * @param audioPlaybackDevice 音频播放设备（扬声器或者听筒），详见 ByteRTCAudioPlaybackDevice{@link #ByteRTCAudioPlaybackDevice}。  <br>
 * @return  方法调用结果  <br>
 *        + 0: 方法调用成功  <br>
 *        + <0: 方法调用失败  <br>
 * @notes  <br>
 *       + 该方法适用于手机等移动设备。  <br>
 *       + 听筒和扬声器为移动设备自带的音频播放设备。听筒一般用于通话，扬声器一般用于外放。  <br>
 *       + 连接有线或者蓝牙音频播放设备后，音频路由将切换至有线耳机或者蓝牙耳机。不同音频场景中，音频路由和发布订阅状态到音量类型的映射关系详见 ByteRTCAudioScenarioType{@link #ByteRTCAudioScenarioType} 。  <br>
 *       + 进房前和进房后，均可调用此方法设置音频播放设备。  <br>
 */
- (int)setAudioPlaybackDevice:(ByteRTCAudioPlaybackDevice)audioPlaybackDevice;

#pragma mark Combined to Push
/**
 * @type api
 * @region CDN 推流
 * @author wanghaoxu
 * @brief 开启合流转推，并设置合流的视频视图布局和音频属性。
 * @param transcoding observer
 *        合流转推配置参数，详见 ByteRTCLiveTranscoding{@link #ByteRTCLiveTranscoding}
 * @param observer  端云一体合流转推观察者。  <br>
 *       + 合流转推的状态和方式会通过回调上报 RTC Engine。  <br>
 *       + 只有房间模式为直播模式，且用户角色为主播的用户才能调用此方法。  <br>
 *       + 启用端云一体合流转推时，回调合流完成的音视频流和 SEI 信息给 App。详见 LiveTranscodingDelegate{@link #LiveTranscodingDelegate} 数据类型。
 * @notes  <br>
 *       + 启用服务端转推时，设置 observer 为 null。  <br>
 *       + 调用该方法后，启动结果和推流过程中的错误均会通过回调 rtcEngine:onLiveTranscodingResult:errorCode:{@link #ByteRTCEngineDelegate#rtcEngine:onLiveTranscodingResult:errorCode:} 通知用户。
 */
- (int)startLiveTranscoding:(ByteRTCLiveTranscoding *_Nonnull)transcoding observer:(id<LiveTranscodingDelegate> _Nonnull)observer;

/**
 * @type api
 * @region CDN 推流
 * @brief 停止合流转推。
 * @return 方法调用结果。  <br>
 *         +  0：方法调用成功  <br>
 *         + <0：方法调用失败
 */
- (int)stopLiveTranscoding;

/**
 * @type api
 * @region CDN 推流
 * @brief 更新合流转推参数。  <br>
 *        启用合流转推功能后，你可以使用此方法更新合流转推功能配置参数。
 * @param transcoding
 *        视频合流配置参数，详见 ByteRTCLiveTranscoding{@link
 *     #ByteRTCLiveTranscoding} 类型。
 * @return 方法调用结果。  <br>
 *         +  0：方法调用成功  <br>
 *         + <0：方法调用失败
 */
- (int)updateLiveTranscoding:(ByteRTCLiveTranscoding *_Nonnull)transcoding;

/**
 * @type api
 * @region 云端渲染
 * @author wuxinyu.mrx
 * @brief 按照传入的布局信息开启云端渲染。 <br>
 * @param rendingInfo 渲染功能相关参数。 <br>
 * @return 方法调用结果。  <br>
 *         +  0: 方法调用成功  <br>
 *         +  <0: 方法调用失败  <br>
 */

- (int)enableCloudRending:(NSString *_Nonnull)rendingInfo;

/**
 * @type api
 * @region 云端渲染
 * @author wuxinyu.mrx
 * @brief 按照传入的布局信息更新云端渲染。 <br>
 * @param rendingInfo 渲染功能相关参数。 <br>
 * @return 方法调用结果。  <br>
 *         +  0: 方法调用成功  <br>
 *         + <0: 方法调用失败  <br>
*/
- (int)updateCloudRending:(NSString *_Nonnull)rendingInfo;

/**
 * @type api
 * @region 云端渲染
 * @author wuxinyu.mrx
 * @brief 停止云端渲染。 <br>
 * @return 方法调用结果。  <br>
 *         +  0: 方法调用成功  <br>
 *         + <0: 方法调用失败  <br>
*/
- (int)disableCloudRending;

#pragma mark External Video Data
/**-----------------------------------------------------------------------------
 * @name 视频自采集
 * -----------------------------------------------------------------------------
 */

/**
 * @deprecated 使用 setVideoSourceType 替代
 * @type api
 * @region 视频管理
 * @brief 配置视频采集源。
 * @param type 视频输入类型，参看 ByteRTCMediaInputType{@link #ByteRTCMediaInputType}。
 * @notes  <br>
 *       + 1. 该方法在进房前后均可以调用。  <br>
 *       + 2. 当你已调用 startVideoCapture{@link #ByteRTCEngineKit#startVideoCapture} 开启内部采集后，再调用此方法切换至自定义采集时，SDK 会自动关闭内部采集。  <br>
 *       + 3. 当你已开启自定义采集后，想要切换至内部采集，你必须先调用此方法指定使用内部采集，然后调用 startVideoCapture{@link #ByteRTCEngineKit#startVideoCapture} 手动开启内部采集。
 */
- (void)setVideoInputType:(ByteRTCMediaInputType)type;

/**
* @type api
* @region 视频管理
* @brief 切换视频输入源（自定义采集/内部采集）
* @param type 视频输入源类型，参看 ByteRTCVideoSourceType{@link #ByteRTCVideoSourceType}
* @notes  <br>
*       + 1. 该方法进房前后均可调用。  <br>
*       + 2. 当你已调用 startVideoCapture{@link #ByteRTCEngineKit#startVideoCapture} 开启内部采集后，再调用此方法切换至自定义采集时，SDK 会自动关闭内部采集。  <br>
*       + 3. 当你调用此方法开启自定义采集后，想要切换至内部采集，你必须先调用此方法关闭自定义采集，然后调用 startVideoCapture{@link #ByteRTCEngineKit#startVideoCapture} 手动开启内部采集。
*/
- (void)setVideoSourceType:(ByteRTCVideoSourceType)type;

/**
 * @type api
 * @region 自定义视频采集渲染
 * @author sunhang.io
 * @brief 推送外部视频帧。
 * @param frame 该视频帧包含待 SDK 编码的视频数据
 * @param pts CMTime
 * @return  <br>
 *         + YES 推送成功  <br>
 *         + NO 推送失败  <br>
 * @notes 使用外部推送视频帧，调用 setVideoInputType 开启外部视频源功能，详见 setVideoInputType:{@link #setVideoInputType:}
 */
- (BOOL)pushExternalVideoFrame:(CVPixelBufferRef _Nonnull )frame time:(CMTime)pts;

/**
 * @type api
 * @region 自定义视频采集渲染
 * @author sunhang.io
 * @brief 推送外部视频帧。
 * @param frame 该视频帧包含待 SDK 编码的视频数据
 * @param pts CMTime
 * @param rotation 当前视频角度
 * @return  <br>
 *         + YES 推送成功  <br>
 *         + NO 推送失败  <br>
 * @notes 使用外部推送视频帧，调用 setVideoInputType: 开启外部视频源功能，详见 setVideoInputType:{@link #setVideoInputType:}
 */
- (BOOL)pushExternalVideoFrame:(CVPixelBufferRef _Nonnull )frame time:(CMTime)pts rotation:(ByteRTCVideoRotation)rotation;

/**
 * @type api
 * @region 自定义视频采集渲染
 * @author sunhang.io
 * @brief 推送外部视频帧。
 * @param frame 该视频帧包含待 SDK 编码的视频数据
 * @param pts CMTime
 * @param rotation 当前视频角度
 * @param extendedData 当前帧的扩展数据，没有的话就传空
 * @param supplementoryInfo 附加信息，比如人脸位置等等
 * @return  <br>
 *         + YES 推送成功  <br>
 *         + NO 推送失败  <br>
 */
- (BOOL)pushExternalVideoFrame:(CVPixelBufferRef _Nonnull )frame time:(CMTime)pts
                                                             rotation:(ByteRTCVideoRotation)rotation
                                                         extendedData:(NSData* _Nullable)extendedData
                                                    supplementaryInfo:(NSData* _Nullable)supplementoryInfo;


/**
 * @type api
 * @region 自定义视频采集渲染
 * @author sunhang.io
 * @brief 推送外部视频帧，使用 ByteRTCVideoFrame 进行封装。
 * @param frame 该视频帧包含待 SDK 编码的视频数据，参考 ByteRTCVideoFrame{@link #ByteRTCVideoFrame}
 * @return  <br>
 *         + YES 推送成功  <br>
 *         + NO 推送失败  <br>
 */
- (BOOL)pushExternalByteVideoFrame:(ByteRTCVideoFrame * _Nonnull)frame;

#pragma mark External Audio Data
/**-----------------------------------------------------------------------------
 * @name 音频自采集及渲染
 * -----------------------------------------------------------------------------
 */

/**
 * @type api
 * @region 自定义音频采集渲染
 * @author wangjunzheng
 * @brief 启用自定义音频采集渲染
 * @param recordingFormat 自定义音频数据采集格式，详见 ByteRTCAudioFormat{@link #ByteRTCAudioFormat}
 * @param playbackFormat 自定义音频数据渲染格式，详见 ByteRTCAudioFormat{@link #ByteRTCAudioFormat}
 * @notes  <br>
 *      + 此方法需要在进房前调用。  <br>
 *      + 启用自定义音频采集渲染的状态在离开房间后仍然有效，会一直持续到调用 disableExternalAudioDevice{@link #ByteRTCEngineKit#disableExternalAudioDevice} 关闭自定义音频采集渲染为止。  <br>
 *      + 启用自定义音频采集渲染后，仍需要使用 pushExternalAudioFrame:{@link #ByteRTCEngineKit#pushExternalAudioFrame:}，推送外部音频数据，再使用 pullExternalAudioFrame:{@link #ByteRTCEngineKit#pullExternalAudioFrame:} 拉取外部音频数据。  <br>
 *      + 使用该方法启用自定义音频采集渲染后，SDK 会自动关闭内部采集使用的音频设备。  <br>
 *      + 当你已调用 startAudioCapture{@link #ByteRTCEngineKit#startAudioCapture} 开启内部采集后，再调用此方法切换至自定义采集时，SDK 会自动关闭内部采集。  <br>
 *      + 当你调用此方法开启自定义采集后，想要切换至内部采集，你必须先调用 disableExternalAudioDevice{@link #ByteRTCEngineKit#disableExternalAudioDevice} 关闭自定义采集，然后调用 startVideoCapture{@link #ByteRTCEngineKit#startVideoCapture} 手动开启内部采集。
 */
- (void)enableExternalAudioDevice:(ByteRTCAudioFormat * _Nonnull) recordingFormat playbackFormat:(ByteRTCAudioFormat * _Nonnull) playbackFormat;

/**
 * @type api
 * @region 自定义音频采集渲染
 * @author wangjunzheng
 * @brief 禁用已开启的自定义音频采集渲染，将音频采集渲染由自定义模块切换至内部模块。
 * @notes  <br>
 *      + 如果你已开启自定义音频采集渲染，你可以在进房前，使用本接口将音频采集渲染由自定义模块切换至内部模块。  <br>
 *      + 使用该 API 禁用自定义音频采集渲染后， SDK 不会自动开启内部的音频采集，需要开启 SDK 内部采集请使用 startAudioCapture{@link #startAudioCapture}。  <br>
 *      + 启用自定义音频采集渲染请使用 enableExternalAudioDevice:playbackFormat:{@link #enableExternalAudioDevice:playbackFormat:}。此方法需要在进房前调用。  <br>
 */
- (void)disableExternalAudioDevice;
 /**
  * @type api
  * @region 混音
 * @author wangjunzheng
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
 * @author wangjunzheng
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
 * @author wangjunzheng
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
 * @region 音频数据回调
 * @author wangjunzheng
 * @brief 设置本地麦克风录制的音频数据回调参数
 * @param samplesPerSec 音频采样率（单位HZ），可以设置的值有 8000，16000，32000，44100，48000
 * @param channels 音频通道数，支持单声道（1）和双声道（2）
 * @return  方法调用结果  <br>
 *        + YES: 方法调用成功  <br>
 *        + NO: 方法调用失败
 * @notes 使用本方法设置参数，并使用setAudioFrameObserver{@link #setAudioFrameObserver:}注册数据观察者，
 *        之后可以在 ByteRTCAudioFrameObserver{@link #ByteRTCAudioFrameObserver}的
 *        onRecordAudioFrame{@link #ByteRTCAudioFrameObserver#onRecordAudioFrame:}收到数据
 */
- (BOOL)setRecordingAudioFrameParameters:(NSInteger)samplesPerSec
                            channels:(NSInteger)channels;

/**
 * @type api
 * @region 音频数据回调
 * @author wangjunzheng
 * @brief 设置远端所有用户音频数据混音后的音频数据回调参数
 * @param samplesPerSec 音频采样率（单位HZ），可以设置的值有 8000，16000，32000，44100，48000
 * @param channels 音频通道数，支持单声道（1）和双声道（2）
 * @return  方法调用结果  <br>
 *        + YES: 方法调用成功  <br>
 *        + NO: 方法调用失败
 * @notes 使用本方法设置参数，并使用setAudioFrameObserver{@link #setAudioFrameObserver:}注册数据观察者，
 *        之后可以在 ByteRTCAudioFrameObserver{@link #ByteRTCAudioFrameObserver}的
 *        onPlaybackAudioFrame{@link #ByteRTCAudioFrameObserver#onPlaybackAudioFrame:}收到数据
 */
- (BOOL)setPlaybackAudioFrameParameters:(NSInteger)samplesPerSec
                            channels:(NSInteger)channels;

/**
 * @type api
 * @region 音频数据回调
 * @author wangjunzheng
 * @brief 设置本地麦克风录制音频数据和远端所有用户音频数据混音后的音频数据回调参数
 * @param samplesPerSec 音频采样率（单位HZ），可以设置的值有 8000，16000，32000，44100，48000
 * @param channels 音频通道数，支持单声道（1）和双声道（2）
 * @return  方法调用结果  <br>
 *        + YES: 方法调用成功  <br>
 *        + NO: 方法调用失败
 * @notes 使用本方法设置参数，并使用setAudioFrameObserver{@link #setAudioFrameObserver:}注册数据观察者，
 *        之后可以在 ByteRTCAudioFrameObserver{@link #ByteRTCAudioFrameObserver}的
 *        onMixedAudioFrame{@link #ByteRTCAudioFrameObserver#onMixedAudioFrame:}收到数据
 */
- (BOOL)setMixedAudioFrameParameters:(NSInteger)samplesPerSec
                            channels:(NSInteger)channels;

/**
 * @type api
 * @region 音频数据回调
 * @author wangjunzheng
 * @brief 设置音频数据回调观察者
 * @param audioFrameObserver 音频数据回调的观察者对象，详见： ByteRTCAudioFrameObserver{@link #ByteRTCAudioFrameObserver}
 * @return  方法调用结果  <br>
 *        + YES: 方法调用成功  <br>
 *        + NO: 方法调用失败
 * @notes 本方法需要与下面3个方法配合使用：
 *        setRecordingAudioFrameParameters:channels:{@link #setRecordingAudioFrameParameters:channels:}、
 *        setPlaybackAudioFrameParameters:channels:{@link #setPlaybackAudioFrameParameters:channels:}、
 *        setMixedAudioFrameParameters:channels:{@link #setMixedAudioFrameParameters:channels:}
 */
- (BOOL)setAudioFrameObserver:(_Nullable id<ByteRTCAudioFrameObserver>) audioFrameObserver;

/**
 * @type api
 * @region 自定义音频采集渲染
 * @author wangjunzheng
 * @brief 推送外部音频数据。
 * @param audioFrame 音频数据帧，详见 ByteRTCAudioFrame{@link #ByteRTCAudioFrame}
 * @return  方法调用结果  <br>
 *          + 0: 设置成功  <br>
 *          + <0: 设置失败  <br>
 * @notes  <br>
 *       + 推送外部音频数据前，必须开启自定义采集。  <br>
 *       + 本方法中设置的 sampleRate（音频采样率） 和 channel（音频声道） 必须与 enableExternalAudioDevice:playbackFormat:{@link #enableExternalAudioDevice:playbackFormat:} 中设置的 sampleRate 和 channel 保持一致。  <br>
 *       + 此方法推送音频数据的间隔为 10 毫秒。 samples (音频采样点个数）应该为 audioFrame.sampleRate / 100，
 *         如设置采样率为 48000 时， 每次应该推送 480 个采样点。  <br>
 *       + 音频采样格式为 S16。音频缓冲区内的数据格式必须为 PCM 数据，其容量大小应该为 audioFrame.samples * audioFrame.channel * 2。  <br>
 *       + 该函数运行在用户级线程内。若同时运行其他进程，将导致本进程中断。  <br>
 */
- (int)pushExternalAudioFrame:(ByteRTCAudioFrame * _Nonnull) audioFrame;

/**
 * @type api
 * @region 自定义音频采集渲染
 * @author wangjunzheng
 * @brief 拉取外部音频数据。
 * @param audioFrame 音频数据帧，详见 ByteRTCAudioFrame{@link #ByteRTCAudioFrame}
 * @return  方法调用结果  <br>
 *        + 0: 设置成功  <br>
 *        + <0: 设置失败  <br>
 * @notes  <br>
 *       + 拉取外部音频数据前，必须开启自定义采集。  <br>
 *       + 本方法中设置的 sampleRate（音频采样率） 和 channel（音频声道） 必须与 enableExternalAudioDevice:playbackFormat:{@link #enableExternalAudioDevice:playbackFormat:} 中设置的 sampleRate 和 channel 保持一致。  <br>
 *       + 此方法拉取音频数据的间隔为 10 毫秒，音频采样格式为 S16。 samples (音频采样点个数）应该为 audioFrame.sampleRate / 100，
 *         如设置采样率为 48000 时， 每次应该拉取 480 个采样点。  <br>
 *       + 音频采样格式为 S16。音频缓冲区内的数据格式必须为 PCM 数据，其容量大小应该为 audioFrame.samples * audioFrame.channel * 2。  <br>
 *       + 该函数运行在用户级线程内。若同时运行其他进程，将导致本进程中断。  <br>
 */
- (int)pullExternalAudioFrame:(ByteRTCAudioFrame * _Nonnull) audioFrame;

#pragma mark Message Related
/**
 * @type api
 * @region 实时消息通信
 * @author hanchenchen.c
 * @brief 给房间内的所有其他用户发送广播文本消息。（Broadcast），返回这次发送消息的编号。
 * @param msg  <br>
 *        用户发送的广播文本消息
 * @return 这次发送消息的编号，从 1 开始递增。
 * @notes  <br>
 *      1. 调用该函数后会收到一次 rtcEngine:onRoomMessageSendResult:error:{@link #ByteRTCEngineDelegate#rtcEngine:onRoomMessageSendResult:error:} 回调，通知消息发送方发送成功或失败；  <br>
 *      2. 若文本消息发送成功，则房间内所有用户会收到
 * rtcEngine:onRoomMessageReceived:message:{@link #ByteRTCEngineDelegate#rtcEngine: onRoomMessageReceived:message:} 回调。
 */
- (int)sendRoomMessage:(NSString *  _Nonnull)msg;

/**
 * @type api
 * @region 实时消息通信
 * @author hanchenchen.c
 * @brief 给房间内的所有其他用户发送广播二进制消息（Broadcast），返回这次发送消息的编号。
 * @param msg   <br>
 *        广播二进制消息的内容。
 * @return 这次发送消息的编号，从 1 开始递增。
 * @notes  <br>
 *      1. 调用该函数后会收到一次 rtcEngine:onRoomMessageSendResult:error:{@link #ByteRTCEngineDelegate#rtcEngine:onRoomMessageSendResult:error:}回调，通知消息发送方发送成功或失败；  <br>
 *      2. 若二进制消息发送成功，则 房间内所有用户会收到
 * rtcEngine:onRoomBinaryMessageReceived:message:{@link #ByteRTCEngineDelegate#rtcEngine:onRoomBinaryMessageReceived:message:} 回调。
 */
- (int)sendRoomBinaryMessage:(NSData *  _Nonnull)msg;

#pragma mark Game Audio Related
/**
 * @hidden
 * @type api
 * @region 游戏接口
 * @author shazhou
 * @brief 设置引擎的工作模式，默认为通用模式。进房前调用。
 * @param mode 模式选择，通用模式或者游戏语音模式。详见 RtcMode{@link #RtcMode}。
 * @return 方法调用结果  <br>
 *         + 0: 调用成功  <br>
 *         + <0: 调用失败  <br>
 */
- (int)setRtcMode:(ByteRTCMode)mode;

/**
 * @hidden
 * @type api
 * @region 游戏接口
 * @author shazhou
 * @brief 向小队或世界发音频，在创建 RtcEngine 实例后调用。
 * @param mode 模式选择，向小队发送或者向世界发送。详见 RangeAudioMode{@link #RangeAudioMode}。
 * @return 方法调用结果  <br>
 *         + 0: 调用成功  <br>
 *         + <0: 调用失败  <br>
 */
- (int)setAudioSendMode:(ByteRTCRangeAudioMode)mode;

/**
 * @hidden
 * @type api
 * @region 游戏接口
 * @author shazhou
 * @brief 收听小队或世界音频，在创建 RtcEngine 实例后调用。
 * @param mode 模式选择，收听小队或者世界音频。详见 RangeAudioMode{@link #RangeAudioMode}。
 * @return 方法调用结果  <br>
 *         + 0: 调用成功  <br>
 *         + <0: 调用失败  <br>
 */
- (int)setAudioRecvMode:(ByteRTCRangeAudioMode)mode;

/**
 * @hidden
 * @type api
 * @region 游戏接口
 * @author shazhou
 * @brief 设置 teamId，必须在加入房间前调用，不支持设置后修改。如果不设置 teamId 并且为游戏语音模式，则加入房间失败。如果不设置 teamId 并且为通用模式，该方法无效。
 * @param teamId 队伍 ID。
 * @return 方法调用结果  <br>
 *         + 0: 调用成功  <br>
 *         + <0: 调用失败  <br>
 */
- (int)setTeamId:(NSString* _Nonnull)teamId;

/**
 * @hidden
 * @type api
 * @region 游戏接口
 * @author shazhou
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
 * @author shazhou
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
 * @author shazhou
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
 * @region 引擎管理
 * @author chenweiming.push
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
 *        + 需要在调用 joinRoomByKey:roomId:roomProfile:userInfo:{@link #joinRoomByKey:roomId:roomProfile:userInfo:} 之前调用，
 *           joinRoomByKey:roomId:roomProfile:userInfo:{@link #joinRoomByKey:roomId:roomProfile:userInfo:}之后调用该方法无效。
 */
- (int)setBusinessId:(NSString* _Nullable)businessId;

/**
 * @type api
 * @region 引擎管理
 * @author chenweiming.push
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
 * @name 监控相关
 * -----------------------------------------------------------------------------
 */

/**
 * @type api
 * @hidden
 * @deprecated
 * @region 引擎管理
 * @author chenweiming.push
 * @brief 设置设备 ID 。  <br>
 *        监控时可以根据设置的 deviceID 来查找相关信息。必须在 sharedEngineWithAppId:delegate:{@link #sharedEngineWithAppId:delegate:} 前调用。
 * @param deviceID  <br>
 *        设备 ID 。
 */
+ (void)setDeviceId:(NSString* _Nonnull) deviceID
    __deprecated_msg("Will be removed in new version");

/**
 * @hidden
 * @type api
 * @deprecated
 * @region 引擎管理
 * @author chenweiming.push
 * @brief 设置 SDK 当前使用的服务器环境。
 * @param env  <br>
 *        SDK 使用的服务器环境参数，详见：Env{@link #Env} 。
 * @return  <br>
 *        + 0： 成功。  <br>
 *        + <0： 失败。  <br>
 *        + -1： 引擎已创建。
 * @notes  <br>
 *        + 本函数是可选函数，默认使用正式环境。  <br>
 *        + 本函数必须在创建 RtcEngine 实例 sharedEngineWithAppId:delegate:{@link #sharedEngineWithAppId:delegate:} 前调用。
 */
+ (int)setEnv:(ByteRTCEnv)env
    __deprecated_msg("Will be removed in new version");

/**
 * @hidden
 * @type api
 * @region 引擎管理
 * @author weirongbin
 * @brief 设置自定义的 HttpClient 实现。提供给 SDK 进行网络请求。
 * @param client  <br>
 *        自定义的 HttpClient 。
 * @notes  <br>
 *        + SDK 支持使用自定义的 HttpClient ，需要实现 ByteRTCHttpClientProtocol{@link #ByteRTCHttpClientProtocol} 协议。  <br>
 *        + 必须在创建 RtcEngine 实例 sharedEngineWithAppId:delegate:{@link #sharedEngineWithAppId:delegate:} 前设置。  <br>
 *        + 不设置则默认使用 SDK 内部实现的 HttpClient 。
 */
+ (void)setHttpClient:(id<ByteRTCHttpClientProtocol> _Nonnull)client;

/**
 * @hidden
 * @type api
 * @region 引擎管理
 * @author chenweiming.push
 * @brief 获取自定义的 HttpClient 实现。
 * @return HttpClient 的实现。
 */
+ (id<ByteRTCHttpClientProtocol> _Nonnull)getHttpClient;

/**
 * @hidden
 * @type api
 * @region 引擎管理
 * @author weirongbin
 * @brief 是否已经设置自定义的 HttpClient 。
 * @return  <br>
 *        + true： 已设置。
 *        + false： 未设置。
 */
+ (bool)isHttpClientSet;

#pragma mark message related
/**
 * @type api
 * @region 实时消息通信
 * @author hanchenchen.c
 * @brief 给房间内指定的用户发送文本消息（P2P），返回这次发送消息的编号。
 * @param uid  <br>
 *        指定用户 ID 。
 * @param message  <br>
 *        发送的文本消息内容。
 * @return 这次发送消息的编号，从 1 开始递增。
 * @notes  <br>
 *      1. 调用该函数后会收到一次 rtcEngine:onUserMessageSendResult:error:{@link #ByteRTCEngineDelegate#rtcEngine:onUserMessageSendResult:error:} 回调，通知消息发送方发送成功或失败；  <br>
 *      2. 若文本消息发送成功，则 uid 所指定的用户会收到
 * rtcEngine:onUserMessageReceived:message:{@link #ByteRTCEngineDelegate#rtcEngine:onUserMessageReceived:message:} 回调。
 */
- (int64_t)sendUserMessage:(NSString * _Nonnull)uid message:(NSString * _Nonnull)message;

/**
 * @type api
 * @region 实时消息通信
 * @author hanchenchen.c
 * @brief 给房间内指定的用户发送二进制消息（P2P），返回这次发送消息的编号。
 * @param uid  <br>
 *        指定用户 ID。
 * @param message   <br>
 *        二进制消息的内容。
 * @return 这次发送消息的编号，从 1 开始递增。
 * @notes  <br>
 *      1. 调用该函数后会收到一次 rtcEngine:onUserMessageSendResult:error:{@link #ByteRTCEngineDelegate#rtcEngine:onUserMessageSendResult:error:}回调，通知消息发送方发送成功或失败；  <br>
 *      2. 若二进制消息发送成功，则 uid 所指定的用户会收到
 * rtcEngine: onUserBinaryMessageReceived:message:{@link #ByteRTCEngineDelegate#rtcEngine:onUserBinaryMessageReceived:message:}回调。
 */
- (int64_t)sendUserBinaryMessage:(NSString * _Nonnull)uid message:(NSData * _Nonnull)message;

#pragma mark Others
/**-----------------------------------------------------------------------------
 * @name 其他设置
 * -----------------------------------------------------------------------------
 */

/**
 * @type api
 * @region 音频管理
 * @author wangjunzheng
 * @brief 调节来自指定远端用户的音频播放音量，默认为 100。
 * @param uid 音频来源的远端用户 ID
 * @param volume 播放音量，调节范围：[0,400]  <br>
 *              + 0: 静音  <br>
 *              + 100: 原始音量  <br>
 *              + 400: 最大可为原始音量的 4 倍(自带溢出保护)  <br>
 */
- (void)setRemoteAudioPlaybackVolume:(NSString* _Nonnull)uid volume:(int)volume;

#pragma mark audio mix related
/**
 * @type api
 * @region 混音
 * @author wangjunzheng
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
 * @author wangjunzheng
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
 * @author wangjunzheng
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
 * @author wangjunzheng
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
 * @author wangjunzheng
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
 * @author wangjunzheng
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
 * @author wangjunzheng
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
 * @author wangjunzheng
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
 * @author wangjunzheng
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
 * @author wangjunzheng
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
 * @author wangjunzheng
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
 * @author wangjunzheng
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
 * @author wangjunzheng
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
 * @author wangjunzheng
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
 * @author wangjunzheng
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
 * @author wangjunzheng
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
 * @author wangjunzheng
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
 * @author wangjunzheng
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
 * @author wangjunzheng
 * @brief 卸载所有音效文件
 * @return  <br>
 *       + 0: 成功  <br>
 *       + <0: 失败
 * @notes  <br>
 *       + 调用该方法卸载所有音效文件。如果引擎被销毁时有音效文件没有被卸载，SDK会自动调用该方法卸载所有音效文件。  <br>
 *       + 调用 leaveRoom:{@link #leaveRoom:} 离开房间后，不会自动调用该方法卸载所有音效文件。如果需要在离开房间后卸载所有音效文件，需要应用主动调用该方法。
 */
- (int)unloadAllEffects;


/**
 * @type api
 * @region 混音
 * @author wangjunzheng
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
 * @author wangjunzheng
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
 * @author panjian.fishing
 * @brief 设置发布的音视频流回退选项
 * @param option 本地发布的音视频流回退选项，详见枚举类型 ByteRTCPublishFallbackOption{@link #ByteRTCPublishFallbackOption}
 * @return  <br>
 *        + 0；方法调用成功；  <br>
 *        + -1：方法调用失败；  <br>
 * @notes  <br>
 *       + 1. 在网络情况不理想、设备性能不足时，实时音视频的质量会下降。通过这个接口来设置网络情况不佳或性能不足时只发送小流，以保证通话质量。  <br>
 *       + 2. 这个方法只在设置了发送多个流的情况下有效。  <br>
 *       + 3. 必须在进房前设置，进房后设置或更改设置无效。  <br>
 *       + 4. 设置回退选项后，本端发布的音视频流发生回退或从回退中恢复时，对端会收到 rtcEngine:OnSimulcastSubscribeFallback:{@link
 * #rtcEngine:OnSimulcastSubscribeFallback:} 回调通知。  <br>
 */
- (int)setPublishFallbackOption:(ByteRTCPublishFallbackOption)option;

/**
 * @type api
 * @region 音视频回退
 * @author panjian.fishing
 * @brief 设置订阅的音视频流回退选项
 * @param option 远端订阅的流回退处理选项，详见枚举类型 ByteRTCSubscribeFallbackOption{@link #ByteRTCSubscribeFallbackOption}
 * @return
 *         + 0：方法调用成功  <br>
 *         + <0：方法调用失败  <br>
 * @notes  <br>
 *        + 在网络情况不理想、设备性能不足时，实时音视频的质量会下降。通过这个接口来设置网络情况不佳或性能不足时只订阅小流或音频流，以保证通话质量。  <br>
 *        + 必须在进房前设置，进房后设置或更改设置无效。  <br>
 *        + 设置回退选项后，本端订阅的音视频流发生回退或从回退中恢复时,会收到 rtcEngine: OnSimulcastSubscribeFallback:{@link
 * #rtcEngine:OnSimulcastSubscribeFallback:} 回调通知。  <br>
 *        + 设置回退选项后，本端订阅的视频流因为回退分辨率发生变化时,会收到 rtcEngine:onRemoteVideoSizeChanged:withFrameInfo:{@link #rtcEngine:onRemoteVideoSizeChanged:withFrameInfo:}
 * 回调通知。
 */
- (int)setSubscribeFallbackOption:(ByteRTCSubscribeFallbackOption)option;

/**
 * @type api
 * @region 音视频回退
 * @author panjian.fishing
 * @brief 设置用户优先级
 * @param priority 远端用户的优先级, 详见枚举类型 ByteRTCRemoteUserPriority{@link #ByteRTCRemoteUserPriority}
 * @param uid 远端用户的 ID
 * @return + 0：方法调用成功  <br>
 *         + <0：方法调用失败  <br>
 * @notes  <br>
 *        + 该方法与 setSubscribeFallbackOption:{@link #setSubscribeFallbackOption:}  搭配使用。  <br>
 *        + 如果开启了订阅流回退选项，弱网或性能不足时会优先保证收到的高优先级用户的流的质量。  <br>
 *        + 该方法在进房前后都可以使用，可以修改远端用户的优先级。
 */
- (int)setRemoteUserPriority:(ByteRTCRemoteUserPriority)priority
                         uid:(NSString *_Nonnull)uid;

#pragma mark AES Related

/**
 * @type api
 * @region 加密
 * @author sunhang.io
 * @brief 设置传输时使用内置加密的方式 <br>
 * @param encrypt_type 内置加密算法，详见 ByteRTCEncryptType{@link #ByteRTCEncryptType}
 * @param key 加密密钥，长度限制为 36 位，超出部分将会被截断
 * @notes  <br>
 *       + 使用传输时内置加密时，使用此方法；如果需要使用传输时自定义加密，参看 ByteRTCEncryptRawData:{@link #ByteRTCEncryptHandler#ByteRTCEncryptRawData:}。
 *         内置加密和自定义加密互斥，根据最后一个调用的方法确定传输加密的方案。  <br>
 *       + 该方法必须在进房之前调用，可重复调用，以最后调用的参数作为生效参数。  <br>
 */
- (void)setEncryptType:(ByteRTCEncryptType)encrypt_type key:(NSString * _Nonnull)key;

/**
 * @type api
 * @region 加密
 * @author sunhang.io
 * @brief 设置自定义加密和解密方式
 *        需要实现对应的加密和解密方法。详情参考 ByteRTCEncryptHandler{@link #ByteRTCEncryptHandler}  <br>
 * @param handler  <br>
 *        自定义加密 handler，需要实现里面的加密和解密方法  <br>
 * @notes
 *       + 该方法与 setEncryptType:key:{@link #setEncryptType:key:} 为互斥关系,
 *         即按照调用顺序，最后一个调用的方法为最终生效的版本  <br>
 *       + 该方法必须在调用 joinRoomByKey:roomId:roomProfile:userInfo:{@link #joinRoomByKey:roomId:roomProfile:userInfo:}
 * 之前调用，可重复调用，以最后调用的参数作为生效参数  <br>
 *       + 无论加密或者解密，其对原始数据的长度修改，需要控制在90%-120%之间，即如果输入数据为100字节，则处理完成后的数据必须在
 *         90至120字节之间，如果加密或解密结果超出该长度限制，则该音视频桢会被丢弃  <br>
 *       + 数据加密/解密为串行执行，因而视实现方式不同，可能会影响到最终渲染效率，是否使用该方法，需要由使用方谨慎评估  <br>
 */
- (void)setCustomizeEncryptHandler:(id<ByteRTCEncryptHandler> _Nullable)handler;

#pragma mark - Extention Methods

/**
 * @hidden
 * @type api
 * @region 房间管理
 * @author shenpengliang
 * @brief 创建并获取一个 ByteRTCRoom{@link #ByteRTCRoom} 对象
 * @param [in] roomId
 *         标识通话房间的房间 ID，最大长度为128字节的非空字符串。支持的字符集范围为:
 *             1. 26个大写字母 A ~ Z
 *             2. 26个小写字母 a ~ z
 *             3. 10个数字 0 ~ 9
 *             4. 下划线"_", at符"@", 减号"-"
 * @notes
 *         1.参数roomId没有默认值，请确保对该参数正确赋值。
 *         2.请勿给参数roomId赋空字符串""或者空指针，否则将无法正确的创建房间对象。
 *         3.用户可以多次调用此方法创建多个 ByteRTCRoom{@link #ByteRTCRoom} 对象，再分别调用各 ByteRTCRoom{@link #ByteRTCRoom} 对象的
 *           joinRoomByToken{@link #joinRoomByToken} 方法，实现同时加入多个房间。
 *         4.加入多个房间后，用户可以同时订阅各房间的音视频流，但是目前仅支持同一时间在一个房间内发布一路音视频流。
 */
- (ByteRTCRoom * _Nullable)createRtcRoom:(NSString * _Nonnull)roomId;


#pragma mark - ScreenCapture
/**
 * @type api
 * @region 屏幕共享
 * @author zhangzhenyu.samuel
 * @brief 配置外部屏幕采集
 * @param enable YES :开启;
 *               NO :不开启;
 * @param rect 采集区域
 * @param param 采集参数 ByteRTCScreenCaptureParam{@link #ByteRTCScreenCaptureParam}
 * @return 0 :成功;
 *        -1 :失败;
 * @notes
 *        1.屏幕采集分为内部采集和外部采集，本方法属于外部采集。
 *        内部采集：由 SDK 进行屏幕采集和后续所有流程
 *        外部采集：用户负责采集屏幕数据帧，通过接口提供给 SDK
 *        2.调用此方法发布本端屏幕共享流后，用户还需要通过设置定时任务周期性调用 pushScreenCaptureFrame:time:rotation:{@link #pushScreenCaptureFrame:time:rotation:} 方法，将需要发送的屏幕数据推送给 SDK。
 *        3.调用该接口后远端能收到 rtcEngine:onFirstRemoteVideoFrameRendered:withFrameInfo:{@link #rtcEngine:onFirstRemoteVideoFrameRendered:withFrameInfo:} 和 rtcEngine:onStreamAdd:{@link #rtcEngine:onStreamAdd:} 事件。
 */
- (int)setScreenCapture:(BOOL)enable Rect:(CGRect)rect screenCaptureParam:(ByteRTCScreenCaptureParam * _Nonnull)param;

/**
 * @type api
 * @region 屏幕共享
 * @author zhangzhenyu.samuel
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
 * @region 屏幕共享
 * @author zhangzhenyu.samuel
 * @brief 开始内部屏幕采集
 * @param param 采集参数 ByteRTCScreenCaptureParam{@link #ByteRTCScreenCaptureParam}
 * @param extension 传入 Broadcast Upload Extension 的 Bundle Id，用于在设置中优先展示 Extension
 * @param groupId App 和 Extension 应该归属于同一个 App Group，此处需要传入 Group Id。
 * @return 0 :成功;
 *        -1 :失败;
 * @notes
 *        1.屏幕采集分为内部采集和外部采集，本方法属于内部采集。
 *        内部采集：由 SDK 进行屏幕采集和后续所有流程
 *        外部采集：用户负责采集屏幕数据帧，通过接口提供给 SDK
 *        2.调用该接口后远端能收到 rtcEngine:onFirstRemoteVideoFrameRendered:withFrameInfo:{@link #rtcEngine:onFirstRemoteVideoFrameRendered:withFrameInfo:} 和 rtcEngine:onStreamAdd:{@link #rtcEngine:onStreamAdd:} 事件。
 *        3.内部采集时，外部不需要屏幕采集帧。
 */
- (int)startScreenSharingWithParam:(ByteRTCScreenCaptureParam *_Nonnull)param preferredExtension:(NSString *_Nullable)extension groupId:(NSString *_Nonnull)groupId API_AVAILABLE(ios(12));

/**
 * @type api
 * @region 屏幕共享
 * @author zhangzhenyu.samuel
 * @brief 停止内部屏幕采集
 * @notes
 *        屏幕采集分为内部采集和外部采集，本方法属于内部采集。
 */
- (void)stopScreenSharing API_AVAILABLE(ios(12));

/**
 * @hidden
 * @type api
 */
+ (ByteRTCAudioDeviceManager *_Null_unspecified)createAudioDeviceManager:(id<ByteRTCAudioDeviceEventHandler> _Nonnull)handler;

/**
 * @hidden
 * @type api
 * @brief 设置运行时的参数
 * @param [in] parameters 保留参数
 */
- (void)setRuntimeParameters:(NSDictionary * _Nullable)parameters;

@end
