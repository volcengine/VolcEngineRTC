/*
 * Copyright (c) 2020 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngine
*/

#import <CoreMedia/CMTime.h>
#import <UIKit/UIKit.h>
#import "ByteRTCDefines.h"
#import "ByteRTCHttpClientProtocol.h"
#import "ByteRTCAudioMixingManager.h"
#import "ByteRTCPositionAudioRender.h"

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
 *        SDK 运行时出现了警告。SDK 通常会自动恢复，警告信息可以忽略。
 * @param engine ByteRTCEngineKit 对象。
 * @param Code 警告代码，参看 ByteRTCWarningCode{@link #ByteRTCWarningCode}。
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine onWarning:(ByteRTCWarningCode)Code;

/**
 * @type callback
 * @region 错误码
 * @brief 发生错误回调。<br>
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
 * @brief 首次加入房间/重连加入房间的回调，表示用户调用 joinRoomByKey:roomId:userInfo:rtcRoomConfig:{@link #ByteRTCEngineKit#joinRoomByKey:roomId:userInfo:rtcRoomConfig:}
 * 的结果，根据错误码判断成功/失败以及区别是否为重连。  <br>
 * @param engine ByteRTCEngineKit 对象。  <br>
 * @param roomId 房间 ID。  <br>
 * @param uid 用户 ID。  <br>
 * @param errorCode 用户加入房间回调的状态码。 <br>
 *        + 0: 加入房间成功；  <br>
 *        + 非 0: 加入房间失败，具体原因参看 ByteRTCErrorCode{@link #ByteRTCErrorCode} 以及 ByteRTCWarningCode{@link #ByteRTCWarningCode}。  <br>
 * @param joinType 加入房间的类型。  <br>
 *        + 0: 首次加入房间。用户手动调用 joinRoomByKey:roomId:userInfo:rtcRoomConfig:{@link #ByteRTCEngineKit#joinRoomByKey:roomId:userInfo:rtcRoomConfig:}，收到加入成功。  <br>
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
 * @author shenpengliang
 * @brief 离开房间成功回调。  <br>
 *        用户调用 leaveRoom{@link #leaveRoom} 方法后，SDK 会停止所有的发布订阅流，并释放所有通话相关的音视频资源。SDK 完成所有的资源释放后通过此回调通知用户。  <br>
 * @param engine  ByteRTCRoom 对象。  <br>
 * @param stats 本次通话的统计数据，详见数据结构 ByteRTCRoomStats{@link #ByteRTCRoomStats} 。  <br>
 * @notes  <br>
 *       + 用户调用 leaveRoom{@link #leaveRoom} 方法离开房间后，如果立即调用 destroyEngine{@link #destroyEngine} 方法销毁 RTC 引擎，则将无法收到此回调事件。  <br>
 *       + 离开房间结束通话后，如果 App 需要使用系统音视频设备，则建议在收到此回调后再初始化音视频设备，否则可能由于 SDK 占用了导致 App 初始化音视频设备失败。  <br>
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine onLeaveRoomWithStats:(ByteRTCRoomStats *_Nonnull)stats;

/**
 * @type callback
 * @region 房间管理
 * @author shenpengliang
 * @brief 远端可见用户加入房间，或房内隐身用户切换为可见的回调。<br>
 *        1. 远端用户调用 setUserVisibility:{@link #ByteRTCEngineKit#setUserVisibility:} 方法将自身设为可见后加入房间时，房间内其他用户将收到该事件。  <br>
 *        2. 远端可见用户断网后重新连入房间时，房间内其他用户将收到该事件。  <br>
 *        3. 房间内隐身远端用户调用 setUserVisibility:{@link #ByteRTCEngineKit#setUserVisibility:} 方法切换至可见时，房间内其他用户将收到该事件。  <br>
 *        4. 新进房用户会收到进房前已在房内的主播角色用户的进房回调通知。  <br>
 * @param engine ByteRTCEngineKit 对象。  <br>
 * @param userInfo 用户信息，参看 ByteRTCUserInfo{@link #ByteRTCUserInfo}。  <br>
 * @param elapsed 保留字段，无意义
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine onUserJoined:(nonnull ByteRTCUserInfo *)userInfo elapsed:(NSInteger)elapsed;

/**
 * @type callback
 * @region 房间管理
 * @author shenpengliang
 * @brief 远端可见用户离开房间，或从可见切换为隐身的回调。  <br>
 *        发生以下情形时，房间内其他用户会收到此事件：  <br>
 *        1.远端可见用户调用 leaveRoom:{@link #ByteRTCEngineKit#leaveRoom:} 方法离开房间时；  <br>
 *        2.远端可见用户调用 setUserVisibility:{@link #ByteRTCEngineKit#setUserVisibility:} 方法切换至隐身；  <br>
 *        3.远端可见用户断网，且一直未恢复。  <br>
 * @param engine ByteRTCEngineKit 对象。  <br>
 * @param uid 离开房间，或切至隐身的远端用户 ID 。  <br>
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
 * @region 媒体流管理
 * @author shenpengliang
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
 * @region 媒体流管理
 * @author shenpengliang
 * @brief 房间内某用户调用 muteLocalAudio:{@link #muteLocalAudio:}
 *        改变本地音频发送状态时，房间内其他用户会收到此回调。
 * @param engine ByteRTCEngineKit 对象
 * @param uid 改变本地音频发送状态的用户 ID
 * @param muteState 发送状态，详见 ByteRTCMuteState{@link #ByteRTCMuteState}
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onUserMuteAudio:(NSString * _Nonnull)uid muteState:(ByteRTCMuteState)muteState;

/**
 * @hidden
 * @deprecated from 323.1, use onUserStartAudioCapture instead
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
 * @brief 房间内的用户调用 startAudioCapture{@link #startAudioCapture} 开启音频采集时，房间内其他用户会收到此回调。
 * @param engine ByteRTCEngineKit 对象
 * @param userId 开启音频采集的远端用户 ID
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onUserStartAudioCapture:(NSString *_Nonnull)userId;

/**
 * @type callback
 * @region 音频事件回调
 * @author wangjunzheng
 * @brief 房间内的用户调用 stopAudioCapture{@link #stopAudioCapture} 关闭音频采集时，房间内其他用户会收到此回调。
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
 * @notes 用户刚收到房间内每一路音频流时，都会收到该回调。
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onFirstRemoteAudioFrame:(ByteRTCRemoteStreamKey * _Nonnull)key;

/**
 * @deprecated from 329.1, use onLocalAudioPropertiesReport/onRemoteAudioPropertiesReport instead
 * @type callback
 * @region 音频事件回调
 * @author wangjunzheng
 * @brief 提示本地采集的音量信息和在房间内订阅的远端用户的音量信息。<br>
 *        本回调默认不开启。你可以通过调用 setAudioVolumeIndicationInterval:{@link #setAudioVolumeIndicationInterval:} 开启。  <br>
 * @param engine ByteRTCEngineKit 对象
 * @param speakers 本地用户和订阅的远端用户的 ID 和音量。
 *                      参看 ByteRTCAudioVolumeInfo{@link #ByteRTCAudioVolumeInfo}。
 * @param totalRemoteVolume speakers 中包含的所有音频音量之和，取值范围是 [0,255]。
 * @notes <br>
 *        + 对于本地用户：只要进行本地音频采集，回调内就会包含本地音频流的音量信息。<br>
 *        + 对于远端用户：本地必须订阅某远端用户的音频流，回调内才会包含其发送的音频流的音量信息。
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onAudioVolumeIndication:(NSArray<ByteRTCAudioVolumeInfo *> * _Nonnull)speakers totalRemoteVolume:(NSInteger)totalRemoteVolume;

/**
 * @type callback
 * @region 音频管理
 * @author wangjunzheng
 * @brief 调用 enableAudioPropertiesReport:{@link #ByteRTCEngineKit#enableAudioPropertiesReport:} 后，可能会周期性收到此回调，获取本地音量信息。<br>
 * @param engine
 * @param audioPropertiesInfos 本地音频信息，详见 ByteRTCLocalAudioPropertiesInfo{@link #ByteRTCLocalAudioPropertiesInfo} 。
 * @notes <br>
 *       1. 使用 RTC SDK 内部机制采集麦克风音频时，回调麦克风的音量；  <br>
 *       2. 使用 RTC SDK 内部机制采集屏幕音频时，回调屏幕音频的音量。  <br>
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onLocalAudioPropertiesReport:(NSArray<ByteRTCLocalAudioPropertiesInfo *> * _Nonnull)audioPropertiesInfos;

/**
 * @type callback
 * @region 音频管理
 * @author wangjunzheng
 * @brief 调用 enableAudioPropertiesReport:{@link #ByteRTCEngineKit#enableAudioPropertiesReport:} 后，可能会周期性收到此回调，获取订阅的远端用户的音量信息。  <br>
 * @param audioPropertiesInfos 远端音频信息，其中包含音频流属性、房间 ID、用户 ID ，详见 ByteRTCRemoteAudioPropertiesInfo{@link #ByteRTCRemoteAudioPropertiesInfo}。  <br>
 * @param totalRemoteVolume 所有订阅的远端流的总音量，范围是 [0,255]。  <br>
 *       + [0,25] 接近无声；  <br>
 *       + [25,75] 为低音量；  <br>
 *       + [76,204] 为中音量；  <br>
 *       + [205,255] 为高音量。  <br>
 * @notes 要获取接收的来自远端的音频音量信息时，不限定音频采集方式，RTC SDK 内部采集机制和自定义采集都可以。
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onRemoteAudioPropertiesReport:(NSArray<ByteRTCRemoteAudioPropertiesInfo *> * _Nonnull)audioPropertiesInfos totalRemoteVolume:(NSInteger)totalRemoteVolume;


#pragma mark - Core Video Delegate Methods
/**
 *  -----------------------------------------------------------------------------
 * @name 核心视频事件回调
 *  -----------------------------------------------------------------------------
 */

/**
 * @type callback
 * @region 视频管理
 * @author shenpengliang
 * @brief 房间内用户调用 muteLocalVideo:{@link #muteLocalVideo:} 暂停/恢复发送视频流时，房间内其他用户会收到此回调。
 * @param engine ByteRTCEngineKit 对象
 * @param uid 暂停/恢复发送视频流的用户 ID。
 * @param muteState 暂停/恢复发送视频流。参看 ByteRTCMuteState{@link #ByteRTCMuteState}
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onUserMuteVideo:(NSString * _Nonnull)uid withMuteState:(ByteRTCMuteState)muteState;

/**
 * @type callback
 * @region 视频管理
 * @author zhushufan.ref
 * @brief 房间中用户调用 startVideoCapture{@link #startVideoCapture} 时，房间中其他用户会收到此回调。
 * @param engine ByteRTCEngineKit 对象
 * @param userId 调用 startVideoCapture{@link #startVideoCapture} 接口的远端用户 ID
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onUserStartVideoCapture:(NSString *_Nonnull)userId;

/**
 * @type callback
 * @region 视频管理
 * @author zhushufan.ref
 * @brief 房间中远端用户调用 stopVideoCapture{@link #stopVideoCapture} 时，本地用户将会收到该回调。
 * @param engine ByteRTCEngineKit 对象
 * @param userId 调用 stopVideoCapture{@link #stopVideoCapture} 接口的远端用户 ID
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onUserStopVideoCapture:(NSString *_Nonnull)userId;

/**
 * @type callback
 * @region 视频管理
 * @author zhangzhenyu.samuel
 * @brief 第一帧本地采集的视频/屏幕共享画面在本地视图渲染完成时，收到此回调。
 * @param engine ByteRTCEngineKit 对象
 * @param streamIndex 流属性，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param frameInfo 视频帧信息，参看 ByteRTCVideoFrameInfo{@link #ByteRTCVideoFrameInfo}
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onFirstLocalVideoFrameCaptured:(ByteRTCStreamIndex)streamIndex withFrameInfo:(ByteRTCVideoFrameInfo * _Nonnull)frameInfo;

/**
 * @type callback
 * @region 视频管理
 * @author zhushufan.ref
 * @brief 第一帧远端视频流在视图上渲染成功后，收到此回调。
 * @param engine ByteRTCEngineKit 对象
 * @param streamKey 远端流信息，参看 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
 * @param frameInfo 视频帧信息，参看 ByteRTCVideoFrameInfo{@link #ByteRTCVideoFrameInfo}
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onFirstRemoteVideoFrameRendered:(ByteRTCRemoteStreamKey * _Nonnull)streamKey withFrameInfo:(ByteRTCVideoFrameInfo * _Nonnull)frameInfo;

/**
 * @type callback
 * @region 视频管理
 * @author zhushufan.ref
 * @brief 远端视频大小或旋转信息发生变化时，房间内订阅此视频流的用户会收到此回调。
 * @param engine ByteRTCEngineKit 对象
 * @param streamKey 流属性，参看 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
 * @param frameInfo 视频帧信息，参看 ByteRTCVideoFrameInfo{@link #ByteRTCVideoFrameInfo}
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine onRemoteVideoSizeChanged:(ByteRTCRemoteStreamKey *_Nonnull)streamKey withFrameInfo:(ByteRTCVideoFrameInfo *_Nonnull)frameInfo;

/**
 * @type callback
 * @region 视频管理
 * @author zhushufan.ref
 * @brief 本地视频大小或旋转信息发生变化时，收到此回调。
 * @param engine ByteRTCEngineKit 对象
 * @param streamIndex 流属性，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param frameInfo 视频帧信息，参看 ByteRTCVideoFrameInfo:{@link #ByteRTCStreamIndex}
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine onLocalVideoSizeChanged:(ByteRTCStreamIndex)streamIndex withFrameInfo:(ByteRTCVideoFrameInfo *_Nonnull)frameInfo;

/**
 * @type callback
 * @region 视频管理
 * @author zhushufan.ref
 * @brief 远端视频流状态发生改变回调。
 * @param engine ByteRTCEngineKit 对象，参考: ByteRTCEngineKit{@link #ByteRTCEngineKit}
 * @param uid 发生视频流状态改变的远端用户的用户ID
 * @param state 变更后的远端视频流状态，详见类型 ByteRTCRemoteVideoState{@link #ByteRTCRemoteVideoState}
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine remoteVideoStateChangedOfUid:(NSString * _Nonnull)uid state:(ByteRTCRemoteVideoState)state;

/**
 * @type callback
 * @region 引擎管理
 * @author zhangzhenyu.samuel
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
 * @brief 音频首帧发送状态改变时，收到此回调。
 * @param engine ByteRTCEngineKit 对象
 * @param user 本地用户信息，详见 ByteRTCUser{@link #ByteRTCUser}
 * @param state 首帧发送状态，详见 ByteRTCFirstFrameSendState{@link #ByteRTCFirstFrameSendState}
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine onAudioFrameSendStateChanged:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFrameSendState)state;

/**
 * @type callback
 * @region 房间管理
 * @author shenpengliang
 * @brief 视频首帧发送状态改变时，收到此回调
 * @param engine ByteRTCEngineKit 对象
 * @param user 本地用户信息，详见 ByteRTCUser{@link #ByteRTCUser}
 * @param state 首帧发送状态，详见 ByteRTCFirstFrameSendState{@link #ByteRTCFirstFrameSendState}
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine onVideoFrameSendStateChanged:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFrameSendState)state;

/**
 * @type callback
 * @region 房间管理
 * @author shenpengliang
 * @brief 屏幕共享流视频首帧发送状态改变时，收到此回调
 * @param engine ByteRTCEngineKit 对象。  <br>
 * @param user 本地用户信息，参看 ByteRTCUser{@link #ByteRTCUser}
 * @param state 首帧发送状态，参看 ByteRTCFirstFrameSendState{@link #ByteRTCFirstFrameSendState}
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine onScreenVideoFrameSendStateChanged:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFrameSendState)state;

/**
 * @type callback
 * @region 房间管理
 * @author shenpengliang
 * @brief 音频首帧播放状态改变时，收到此回调
 * @param engine ByteRTCEngineKit 对象。  <br>
 * @param user 音频流来源的用户信息，参看 ByteRTCUser{@link #ByteRTCUser}
 * @param state 首帧播放状态，参看 ByteRTCFirstFramePlayState{@link #ByteRTCFirstFramePlayState}
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine onAudioFramePlayStateChanged:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFramePlayState)state;

/**
 * @type callback
 * @region 房间管理
 * @author shenpengliang
 * @brief 视频首帧播放状态改变时，收到此回调
 * @param user 视频流来源的用户信息，参看 ByteRTCUser{@link #ByteRTCUser}
 * @param state 首帧播放状态，参看 ByteRTCFirstFramePlayState{@link #ByteRTCFirstFramePlayState}
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine onVideoFramePlayStateChanged:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFramePlayState)state;

/**
 * @type callback
 * @region 房间管理
 * @author shenpengliang
 * @brief 屏幕共享流视频首帧播放状态改变时，收到此回调
 * @param engine ByteRTCEngineKit 对象。  <br>
 * @param user 屏幕共享流来源的用户信息，参看 ByteRTCUser{@link #ByteRTCUser}
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
 * @brief 以下情况会触发此回调：<br>
 *        + 房间内的用户发布新的音视频流时，房间内的其他用户会收到此回调通知。  <br>
 *        + 房间内的用户原音视频流被移出后，又重新发布音视频流时，房间内的其他用户会收到此回调通知。  <br>
 *        + 用户刚加入房间时，会收到此回调，包含房间中所有已发布的流。
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

/**
 * @type callback
 * @region 视频管理
 * @brief 通过调用服务端 MuteUser/UnmuteUser 方法禁用/解禁指定房间内指定用户视频流的发送时，触发此回调。
 * @param uid 被禁用/解禁的视频流用户 ID
 * @param banned 视频流发送状态 <br>
 *        + true: 视频流发送被禁用 <br>
 *        + false: 视频流发送被解禁
 * @notes  <br>
 *        + 房间内指定用户被禁止/解禁视频流发送时，房间内所有用户都会收到该回调。  <br>
 *        + 若被封禁用户退房后再进房，则依然是封禁状态，且房间内所有人会再次收到该回调。  <br>
 *        + 若被封禁用户断网后重连进房，则依然是封禁状态，且只有本人会再次收到该回调。  <br>
 *        + 指定用户被封禁后，房间内其他用户退房后再进房，会再次收到该回调。  <br>
 *        + 通话人数超过 5 人时，只有被封禁/解禁用户会收到该回调。  <br>
 *        + 同一房间解散后再次创建，房间内状态清空。
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onVideoStreamBanned:(NSString* _Nonnull)uid isBanned:(BOOL)banned;
/**
 * @type callback
 * @region 音频事件回调
 * @brief 通过调用服务端 MuteUser/UnmuteUser 方法禁用/解禁指定房间内指定用户视音频流的发送时，触发此回调。
 * @param uid 被禁用/解禁的音频流用户 ID
 * @param banned 音频流发送状态 <br>
 *        + true: 音频流发送被禁用 <br>
 *        + false: 音频流发送被解禁
 * @notes  <br>
 *        + 房间内指定用户被禁止/解禁音频流发送时，房间内所有用户都会收到该回调。  <br>
 *        + 若被封禁用户退房后再进房，则依然是封禁状态，且房间内所有人会再次收到该回调。  <br>
 *        + 若被封禁用户断网后重连进房，则依然是封禁状态，且只有本人会再次收到该回调。  <br>
 *        + 指定用户被封禁后，房间内其他用户退房后再进房，会再次收到该回调。  <br>
 *        + 通话人数超过 5 人时，只有被封禁/解禁用户会收到该回调。  <br>
 *        + 同一房间解散后再次创建，房间内状态清空。
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onAudioStreamBanned:(NSString* _Nonnull)uid isBanned:(BOOL)banned;

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
 * @brief 收到房间中调用 sendRoomMessage:{@link #sendRoomMessage:} 发送的广播文本消息时，收到此回调。
 * @param engine 当前 RTCEngine 实例。
 * @param uid 消息发送者 ID 。
 * @param message 收到的文本消息内容。
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onRoomMessageReceived:(NSString * _Nonnull)uid message:(NSString * _Nonnull)message;

/**
 * @type callback
 * @region 实时消息通信
 * @author hanchenchen.c
 * @brief 收到房间中调用 sendRoomBinaryMessage:{@link #sendRoomBinaryMessage:} 发送的广播二进制消息时，收到此回调。
 * @param engine 当前 RTCEngine 实例。
 * @param uid 消息发送者 ID 。
 * @param message 收到的二进制消息内容。
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onRoomBinaryMessageReceived:(NSString * _Nonnull)uid message:(NSData * _Nonnull)message;

/**
 * @type callback
 * @region 视频管理
 * @author wangjunlin.3182
 * @brief 收到通过调用 sendSEIMessage:andMessage:andRepeatCount:{@link #ByteRTCEngineKit#sendSEIMessage:andMessage:andRepeatCount:} 带有 SEI 消息的视频帧时，收到此回调
 * @param engine 当前 RTCEngine 实例。
 * @param remoteStreamKey 包含 SEI 发送者的用户名，所在的房间名和媒体流，参看 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
 * @param message 收到的 SEI 消息内容
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onSEIMessageReceived:(ByteRTCRemoteStreamKey* _Nonnull)remoteStreamKey andMessage:(NSData* _Nonnull)message;

/**
 * @type api
 * @region 音频管理
 * @author wangjunzheng
 * @brief 音频流同步信息回调。可以通过此回调，在远端用户调用 sendStreamSyncInfo:config:{@link #ByteRTCEngineKit#sendStreamSyncInfo:config:} 发送音频流同步消息后，收到远端发送的音频流同步信息。  <br>
 * @param engine 当前 RTCEngine 实例。
 * @param remoteStreamKey 远端流信息，详见 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey} 。
 * @param streamType 媒体流类型，目前仅支持用麦克风采集到的音频流，详见 ByteRTCSyncInfoStreamType{@link #ByteRTCSyncInfoStreamType} 。
 * @param data 消息内容。
 */  
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onStreamSyncInfoReceived:(ByteRTCRemoteStreamKey* _Nonnull)remoteStreamKey streamType:(ByteRTCSyncInfoStreamType)streamType data:(NSData* _Nonnull)data;

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
 * @brief 本地订阅的远端音/视频流数据统计以及网络质量回调。  <br>
 *        本地用户订阅流成功后，SDK 会周期性（2s）的通过此回调事件通知用户订阅的流在此次统计周期内的质量统计信息，包括：发送音视频比特率、发送帧率、编码帧率，网络质量等。
 * @param engine ByteRTCEngineKit 对象
 * @param stats 当前 RtcEngine 统计数据，详见 ByteRTCRemoteStreamStats{@link #ByteRTCRemoteStreamStats}
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine onRemoteStreamStats:(const ByteRTCRemoteStreamStats *_Nonnull)stats;

/**
 * @type callback
 * @region 音频事件回调
 * @author wangjunzheng
 * @brief 本地音频流的状态发生改变时，收到此回调。
 * @param engine ByteRTCEngineKit 对象
 * @param state 本地音频设备的当前状态，详见 ByteRTCLocalAudioStreamState{@link #ByteRTCLocalAudioStreamState}
 * @param error 本地音频流状态改变时的错误码，详见 ByteRTCLocalAudioStreamError{@link #ByteRTCLocalAudioStreamError}
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine
    onLocalAudioStateChanged:(ByteRTCLocalAudioStreamState)state
                     error:(ByteRTCLocalAudioStreamError)error;

/**
 *  @type callback
 *  @region 音频事件回调
 *  @author wangjunzheng
 *  @brief 订阅的远端音频流状态发生改变时，收到此回调。
 *  @param engine ByteRTCEngineKit 对象
 *  @param key 远端流信息, 详见 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
 *  @param state 远端音频流的当前状态，详见 ByteRTCRemoteAudioState{@link #ByteRTCRemoteAudioState}
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
 * @param streamIndex 流属性，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param state 本地视频流的当前状态，参看 ByteRTCLocalVideoStreamState{@link #ByteRTCLocalVideoStreamState}
 * @param error 本地视频状态改变时的错误码，参看 ByteRTCLocalVideoStreamError{@link #ByteRTCLocalVideoStreamError}
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
 * @param streamKey 远端视频流信息，房间、用户 ID、流属性等，参看 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
 * @param state 远端视频流的当前状态，参看 ByteRTCRemoteVideoState{@link #ByteRTCRemoteVideoState}
 * @param reason 远端视频流状态改变的原因，参看 ByteRTCRemoteVideoStateChangeReason{@link #ByteRTCRemoteVideoStateChangeReason}
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
 * @brief 收到来自房间中其他用户通过 sendUserMessage:message:{@link #sendUserMessage:message:} 发来的文本消息时（P2P），会收到此回调。
 * @param engine 当前 RTCEngine 实例。
 * @param uid 消息发送者的用户 ID 。
 * @param message 收到的文本消息内容。
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onUserMessageReceived:(NSString * _Nonnull)uid message:(NSString * _Nonnull)message;

/**
* @type callback
* @region 实时消息通信
* @author hanchenchen.c
* @brief 收到来自房间中其他用户通过 sendUserBinaryMessage:message:{@link #sendUserBinaryMessage:message:} 发来的二进制消息时，会收到此回调。
* @param engine 当前 RTCEngine 实例。
* @param uid 消息发送者的用户 ID 。
* @param message 收到的二进制消息内容。
*/
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onUserBinaryMessageReceived:(NSString * _Nonnull)uid message:(NSData * _Nonnull)message;

/**
 * @type callback
 * @region 实时消息通信
 * @author hanchenchen.c
 * @brief 向房间内单个用户发送文本或二进制消息后（P2P），消息发送方会收到该消息发送结果回调。
 * @param engine ByteRTCEngineKit 对象
 * @param msgid 本条消息的 ID。
 * @param error 消息发送结果，详见 ByteRTCUserMessageSendResult{@link #ByteRTCUserMessageSendResult}
 * @notes  <br>
 *        + 你应调用 sendUserMessage:message:{@link #sendUserMessage:message:} 向房间内单个用户发送文本消息 <br>
 *        + 你应调用 sendUserBinaryMessage:message:{@link #sendUserBinaryMessage:message:} 向房间内单个用户发送二进制消息
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onUserMessageSendResult:(int64_t)msgid error:(ByteRTCUserMessageSendResult)error;

 /**
  * @type callback
  * @region 实时消息通信
  * @author hanchenchen.c
  * @brief 向房间内所有用户群发文本或二进制消息后，消息发送方会收到该消息发送结果回调。
  * @param engine ByteRTCEngineKit 对象
  * @param msgid 本条消息的 ID。
  * @param error 消息发送结果，详见 ByteRTCRoomMessageSendResult{@link #ByteRTCRoomMessageSendResult}
  * @notes  <br>
  *        + 你应调用 sendRoomMessage:{@link #sendRoomMessage:} 向房间内群发文本消息 <br>
  *        + 你应调用 sendRoomBinaryMessage:{@link #sendRoomBinaryMessage:} 向房间内群发二进制消息
  */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onRoomMessageSendResult:(int64_t)msgid error:(ByteRTCRoomMessageSendResult)error;

#pragma mark - Rtm
/**
 * @type callback
 * @region 实时消息通信
 * @author hanchenchen.c
 * @brief 登录结果回调
 * @param uid  <br>
 *        登录用户 ID
 * @param errorCode  <br>
 *        登录结果  <br>
 *        详见 ByteRTCLoginErrorCode{@link #ByteRTCLoginErrorCode}。
 * @param elapsed  <br>
 *        从调用 login:uid:{@link #ByteRTCEngineKit#login:uid:} 接口开始到返回结果所用时长。  <br>
 *        单位为 ms。
 * @notes 调用 login:uid:{@link #ByteRTCEngineKit#login:uid:} 后，会收到此回调。
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onLoginResult:(NSString * _Nonnull)uid errorCode:(ByteRTCLoginErrorCode)errorCode elapsed:(NSInteger)elapsed;
/**
 * @type callback
 * @region 实时消息通信
 * @author hanchenchen.c
 * @brief 登出结果回调
 * @param engine ByteRTCEngineKit 对象
 * @notes 调用 logout{@link #ByteRTCEngineKit#logout} 后，会收到此回调。
 */
- (void)rtcEngineOnLogout:(ByteRTCEngineKit * _Nonnull)engine;
/**
 * @type callback
 * @region 实时消息通信
 * @author hanchenchen.c
 * @brief 设置业务服务器参数的返回结果
 * @param errorCode <br>
 *        设置结果  <br>
 *        + 返回 200，设置成功  <br>
 *        + 返回其他，设置失败
 * @notes 调用 setServerParams:url:{@link #ByteRTCEngineKit#setServerParams:url:} 后，会收到此回调。
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onServerParamsSetResult:(NSInteger)errorCode;
/**
 * @type callback
 * @region 实时消息通信
 * @author hanchenchen.c
 * @brief 查询对端或本端用户登录状态的返回结果
 * @param peerUserId  <br>
 *        需要查询的用户 ID
 * @param status  <br>
 *        查询的用户登录状态  <br>
 *        详见 ByteRTCUserOnlineStatus{@link #ByteRTCUserOnlineStatus}.
 * @notes 必须先调用 getPeerOnlineStatus:{@link #ByteRTCEngineKit#getPeerOnlineStatus:}，才能收到此回调。
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onGetPeerOnlineStatus:(NSString * _Nonnull)peerUserId status:(ByteRTCUserOnlineStatus)status;
/**
 * @type callback
 * @region 实时消息通信
 * @author hanchenchen.c
 * @brief 收到房间外用户调用 sendUserMessageOutsideRoom:message:{@link #ByteRTCEngineKit#sendUserMessageOutsideRoom:message:} 发来的文本消息时，会收到此回调
 * @param uid  <br>
 *        消息发送者 ID
 * @param message  <br>
 *        收到的文本消息内容
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onUserMessageReceivedOutsideRoom:(NSString * _Nonnull)uid message:(NSString * _Nonnull)message;
/**
 * @type callback
 * @region 实时消息通信
 * @author hanchenchen.c
 * @brief 收到房间外用户调用 sendUserBinaryMessageOutsideRoom:message:{@link #ByteRTCEngineKit#sendUserBinaryMessageOutsideRoom:message:} 发来的二进制消息时，会收到此回调。
 * @param  uid  <br>
 *         消息发送者 ID
 * @param  message  <br>
 *         收到的二进制消息内容
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onUserBinaryMessageReceivedOutsideRoom:(NSString * _Nonnull)uid message:(NSData * _Nonnull)message;
/**
 * @type callback
 * @region 实时消息通信
 * @author hanchenchen.c
 * @brief 给房间外指定的用户发送消息的回调
 * @param msgid  <br>
 *        本条消息的 ID  <br>
 *        所有的 P2P 和 P2Server 消息共用一个 ID 序列。
 * @param error  <br>
 *        消息发送结果  <br>
 *        详见 ByteRTCUserMessageSendResult{@link #ByteRTCUserMessageSendResult}。
 * @notes 当调用 sendUserMessageOutsideRoom:message:{@link #ByteRTCEngineKit#sendUserMessageOutsideRoom:message:} 或 sendUserBinaryMessageOutsideRoom:message:{@link #ByteRTCEngineKit#sendUserBinaryMessageOutsideRoom:message:} 发送消息后，会收到此回调。
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onUserMessageSendResultOutsideRoom:(int64_t)msgid error:(ByteRTCUserMessageSendResult)error;

/**
 * @type callback
 * @region 实时消息通信
 * @author hanchenchen.c
 * @brief 给业务服务器发送消息的回调
 * @param msgid  <br>
 *        本条消息的 ID  <br>
 *        所有的 P2P 和 P2Server 消息共用一个 ID 序列。
 * @param error  <br>
 *        消息发送结果  <br>
 *        详见 ByteRTCUserMessageSendResult{@link #ByteRTCUserMessageSendResult}。
 * @notes 当调用 sendServerMessage:{@link #ByteRTCEngineKit#sendServerMessage:} 或 sendServerBinaryMessage:{@link #ByteRTCEngineKit#sendServerBinaryMessage:} 接口发送消息后，会收到此回调。
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onServerMessageSendResult:(int64_t)msgid error:(ByteRTCUserMessageSendResult)error;
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
 * @hidden
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
 * @deprecated from 325.1, use ByteRTCAudioMixingManager instead
 * @type callback
 * @region 混音
 * @author wangjunzheng
 * @brief 音乐文件混音结束回调。SDK通过此回调通知应用层音乐文件混音结束。
 * @param engine 当前RTC SDK对象
 */
- (void)rtcEngineLocalAudioMixingDidFinish:(ByteRTCEngineKit *_Nonnull)engine;

/**
 * @deprecated from 325.1, use ByteRTCAudioMixingManager instead
 * @type callback
 * @region 混音
 * @author wangjunzheng
 * @brief 音效文件混音结束回调。SDK通过此回调通知应用层音效文件混音结束
 * @param engine 当前RTC SDK对象
 * @param soundId 音效ID
 */
- (void)rtcEngineDidAudioEffectFinish:(ByteRTCEngineKit *_Nonnull)engine soundId:(NSInteger)soundId;

/**
 * @type callback
 * @region 混音
 * @author wangjunzheng
 * @brief 音频混音文件播放状态改变时回调
 * @param id  <br>
 *        混音 ID  <br>
 *        使用 ByteRTCAudioMixingManager{@link #ByteRTCAudioMixingManager} 相关接口时传入的唯一 ID。
 * @param state  <br>
 *        混音状态  <br>
 *        其混音状态可参考：ByteRTCAudioMixingState{@link #ByteRTCAudioMixingState}。
 * @param error  <br>
 *        错误码  <br>
 *        详见 ByteRTCAudioMixingError{@link #ByteRTCAudioMixingError}。
 * @notes  <br>
 *       + 此回调会被触发的时机汇总如下：  <br>
 *       + 当调用 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} 方法成功后，会触发 state 值为 ByteRTCAudioMixingStatePlaying 回调；否则触发 state 值为 ByteRTCAudioMixingStateFailed 的回调。  <br>
 *       + 当使用相同的 ID 重复调用 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} 后，后一次会覆盖前一次，且本回调会以 ByteRTCAudioMixingStateStopped 通知前一次混音已停止。  <br>
 *       + 当调用 pauseAudioMixing:{@link #ByteRTCAudioMixingManager#pauseAudioMixing:} 方法暂停播放成功后，会触发 state 值为 ByteRTCAudioMixingStatePaused 回调；否则触发 state 值为 ByteRTCAudioMixingStateFailed 的回调。  <br>
 *       + 当调用 resumeAudioMixing:{@link #ByteRTCAudioMixingManager#resumeAudioMixing:} 方法恢复播放成功后，会触发 state 值为 ByteRTCAudioMixingStatePlaying 回调；否则触发 state 值为 ByteRTCAudioMixingStateFailed 的回调。  <br>
 *       + 当调用 stopAudioMixing:{@link #ByteRTCAudioMixingManager#stopAudioMixing:} 方法停止播放成功后，会触发 state 值为 ByteRTCAudioMixingStateStopped 回调；否则触发 state 值为 ByteRTCAudioMixingStateFailed 的回调。  <br>
 *       + 播放结束会触发 state 值为 ByteRTCAudioMixingStateFinished 回调。
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine
   onAudioMixingStateChanged:(NSInteger)id state:(ByteRTCAudioMixingState)state error:(ByteRTCAudioMixingError)error;

#pragma mark transcoding Delegate Methods
/**-----------------------------------------------------------------------------
 * @name 转推直播状态回调
 * -----------------------------------------------------------------------------
 */

/**
 * @type callback
 * @region 转推直播
 * @author liyunlong.zx
 * @brief 转推直播错误回调。  <br>
 *        调用 startLiveTranscoding:observer:{@link #ByteRTCEngineKit#startLiveTranscoding:observer:} 接口或直接在服务端启动转推直播功能后，你会通过此回调收到启动结果和推流过程中的错误。
 * @param engine engine 实例
 * @param url 推流地址的 URL。
 * @param errorCode 转推直播功能错误码，详见枚举类型 ByteRTCTranscodingError{@link #ByteRTCTranscodingError}。
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

#pragma mark FileRecording related callback
/**
 * @type callback
 * @region 本地录制
 * @brief 获取本地录制状态回调。  <br>
 *        该回调由 startFileRecording:withRecordingConfig:{@link #ByteRTCEngineKit#startFileRecording:withRecordingConfig:} 或 stopFileRecording:{@link #ByteRTCEngineKit#stopFileRecording:} 触发。
 * @param engine ByteRTCEngineKit 对象
 * @param type 录制流的流属性，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param state 录制状态，参看 ByteRTCRecordingState{@link #ByteRTCRecordingState}
 * @param error_code 录制错误码，参看 ByteRTCRecordingErrorCode{@link #ByteRTCRecordingErrorCode}
 * @param recording_info 录制文件的详细信息，参看 ByteRTCRecordingInfo{@link #ByteRTCRecordingInfo}
 */
- (void)rtcEngine:(ByteRTCEngineKit* _Nonnull)engine
        onRecordingStateUpdate:(ByteRTCStreamIndex)type
                         state:(ByteRTCRecordingState)state
                    error_code:(ByteRTCRecordingErrorCode)error_code
                recording_info:(ByteRTCRecordingInfo* _Nonnull)recording_info;

/**
 * @type callback
 * @region 本地录制
 * @brief 本地录制进度回调。  <br>
 *        该回调由 startFileRecording:withRecordingConfig:{@link #ByteRTCEngineKit#startFileRecording:withRecordingConfig:} 触发，录制状态正常时，系统每秒钟都会通过该回调提示录制进度。
 * @param engine ByteRTCEngineKit 对象
 * @param type 录制流的流属性，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param process 录制进度，参看 ByteRTCRecordingProgress{@link #ByteRTCRecordingProgress}
 * @param recording_info 录制文件的详细信息，参看 ByteRTCRecordingInfo{@link #ByteRTCRecordingInfo}
 */
- (void)rtcEngine:(ByteRTCEngineKit* _Nonnull)engine
        onRecordingProgressUpdate:(ByteRTCStreamIndex)type
                          process:(ByteRTCRecordingProgress* _Nonnull)process
                   recording_info:(ByteRTCRecordingInfo* _Nonnull)recording_info;
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

/**
 * @type keytype
 * @author majun.lvhiei
 * @region 音频处理
 * @brief 自定义音频处理器
 */
@protocol ByteRTCAudioProcessor <NSObject>
/**
 * @type callback
 * @region 音频处理
 * @brief 获取 RTC SDK 采集得到的音频帧，并进行自定义处理，最终将处理后的音频帧给到 RTC SDK 用于编码传输。
 * @param audioFrame RTC SDK 采集到的音频帧，自定义处理可直接对音频 buffer 中的数据进行修改。参看 ByteRTCAudioFrame{@link #ByteRTCAudioFrame}。
 * @return  <br>
 *        0: 未处理  <br>
 *        >0: 处理成功  <br>
 *        <0: 处理失败
 * @notes 在进行音频自定义处理前，你需要调用 registerLocalAudioProcessor:format:{@link #ByteRTCEngineKit#registerLocalAudioProcessor:format:} 设置音频自定义处理器。
 */
- (int)processAudioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;

@end

#pragma mark - ByteRTCEngineMediaMetadataObserver
/**
 * @hidden
 * @deprecated
 * @type callback
 * @brief 使用内部源视频采集时,配置和获取附加数据接口
 */
BYTERTC_APPLE_EXPORT @protocol ByteRTCMediaMetadataObserver <NSObject>
@required
/**
 * @type callback
 * @region 视频数据回调
 * @author wangjunlin.3182
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
 * @author wangjunlin.3182
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
 * @author wangjunlin.3182
 * @brief 自定义加密接口
 */
@protocol ByteRTCEncryptHandler <NSObject>

@required
/**
 * @type api
 * @region 加密
 * @author wangjunlin.3182
 * @brief 自定义加密。  <br>
 *        使用设定的自定义加密方式，对传输前的音视频帧数据进行加密。
 * @param rawData 原始音视频帧数据
 * @return 加密后的数据  <br>
 *        + 非空，表示加密后的数据  <br>
 *        + 为空，表示数据被丢弃
 * @notes <br>
 *        + 使用此接口进行自定义加密前，你必须先设置自定义加密方式，参看 setCustomizeEncryptHandler:{@link #setCustomizeEncryptHandler:}。
 *        + 使用 ByteRTCDecryptRawData:{@link #ByteRTCEncryptHandler#ByteRTCDecryptRawData:} 对已加密的音视频帧数据进行解密。
 *        + 返回的数据大小应控制在原始数据的 90% ~ 120% 范围以内，不然将被丢弃。
 */
- (NSData * _Nonnull) ByteRTCEncryptRawData:(NSData * _Nonnull)rawData;

@required
/**
 * @type api
 * @region 加密
 * @author wangjunlin.3182
 * @brief 自定义解密。  <br>
 *        对自定义加密后的音视频帧数据进行解密。关于自定义加密，参看 ByteRTCEncryptRawData:{@link #ByteRTCEncryptHandler#ByteRTCEncryptRawData:}。
 * @param rawData 收到的已加密的音视频帧数据
 * @return 解密后的数据  <br>
 *        + 非空，表示解密后的数据  <br>
 *        + 为空，表示丢弃该帧
 * @notes <br>
 *        + 使用此接口进行解密前，你必须先设定解密方式，参看 setCustomizeEncryptHandler:{@link #setCustomizeEncryptHandler:}。
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

#pragma mark - ByteASREventHandler
/**
 * @type keytype
 * @brief 语音识别服务使用状态回调
 */
BYTERTC_APPLE_EXPORT @protocol ByteRTCASREngineEventHandler<NSObject>
@required
/**
 * @type callback
 * @brief 语音识别服务开启成功回调
 */
- (void)onSuccess;
@required
/**
 * @type callback
 * @brief 语音转文字成功回调，该回调返回识别后的全量消息。
 * @param message 识别完成后得到的文字消息
 * @notes 若识别过程中发生了网络连接中断，则重连后回调的信息中只包含重连后识别的文字消息，不再包含上一次连接后识别的消息。
 */
- (void)onMessage:(NSString *_Nonnull)message;
@required
/**
 * @type callback
 * @brief 当语音识别服务内部发生错误事件时触发该回调。
 * @param errorCode 错误码  <br>
 *        + <0: 参数错误或 API 调用顺序错误，参看 ByteRTCASRErrorCode{@link #ByteRTCASRErrorCode}；  <br>
 *        + >0: 参看 [语音识别服务错误码](https://bytedance.feishu.cn/docs/doccnMx9153dZEpfLX2I6BkFsMg#VPknqs)
 * @param errorMessage 错误原因说明
 */
- (void)onError:(NSInteger)errorCode withErrorMessage:(NSString *_Nonnull)errorMessage;
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
 * @hidden
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
 *          initWithAppId:delegate:parameters:{@link #ByteRTCEngineKit#initWithAppId:delegate:parameters:} 方法则会重新创建一个全新的
 *          ByteRTCEngineKit{@link #ByteRTCEngineKit} 实例。
 */
+ (instancetype _Nonnull)sharedEngineWithAppId:(NSString * _Nonnull)appId
                                      delegate:(id<ByteRTCEngineDelegate> _Nullable)delegate
                                      __deprecated_msg("Will be removed in new version");
/**
 * @hidden
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
 *          initWithAppId:delegate:parameters:{@link #ByteRTCEngineKit#initWithAppId:delegate:parameters:} 方法则会重新创建一个全新的
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
 * @return 由 initWithAppId:delegate:parameters:{@link #ByteRTCEngineKit#initWithAppId:delegate:parameters:} 创建的 ByteRTCEngineKit{@link #ByteRTCEngineKit} 对象。
 * @notes  <br>
 *        + 如果未调用 initWithAppId:delegate:parameters:{@link #ByteRTCEngineKit#initWithAppId:delegate:parameters:}
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
 * @hidden
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
 * @brief 手动销毁引擎实例对象，如果当前的引擎对象是通过 initWithAppId:delegate:parameters:{@link #ByteRTCEngineKit#initWithAppId:delegate:parameters:}
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
 * @brief 销毁由 initWithAppId:delegate:parameters:{@link #ByteRTCEngineKit#initWithAppId:delegate:parameters:} 创建的引擎实例，并释放所有相关资源。
 * @notes  <br>
 *        + 请确保一定是在所有业务场景的最后阶段才调用该方法。  <br>
 *        + 该方法在调用之后，会销毁所有 SDK 相关的内存，并且停止与媒体服务器的任何交互。  <br>
 *        + 在上一次 initWithAppId:delegate:parameters:{@link #ByteRTCEngineKit#initWithAppId:delegate:parameters:} 调用之后对SDK进行的任何设置，
 *          将在下一次有效执行 initWithAppId:delegate:parameters:{@link #ByteRTCEngineKit#initWithAppId:delegate:parameters:} 时生效。  <br>
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
 * @hidden
 * @deprecated
 * @type api
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
 * @hidden
 * @deprecated from 326.1，use setUserVisiblity instead
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
 *            - 从静默观众切换至主播时，房间内其他用户会收到 rtcEngine:onUserJoined:elapsed:{@link #ByteRTCEngineDelegate#rtcEngine:onUserJoined:elapsed:}；  <br>
 *            - 从主播切换至静默观众时，房间内其他用户会收到 rtcEngine:onUserLeave:reason:{@link #ByteRTCEngineDelegate#rtcEngine:onUserLeave:reason:} 。
 */
- (BOOL)setUserRole:(ByteRTCUserRoleType)role
    __deprecated_msg("Will be removed in new version");
/**
 * @type api
 * @region 房间管理
 * @author liuzhiqiang
 * @brief 设置用户可见性。默认为可见。  <br>
 *        通过对用户可见性进行设置，可以控制用户在房间内的行为：<br>
 *        + 能否发布音视频流；  <br>
 *        + 用户自身是否在房间中隐身。
 * @param enable 设置用户是否对房间内其他用户可见：  <br>
 *        + true: 可以被房间中的其他用户感知，且可以在房间内发布和订阅音视频流；  <br>
 *        + false: 无法被房间中的其他用户感知，且只能在房间内订阅音视频流。
 * @return 方法调用结果：  <br>
 *        + YES: 方法调用成功  <br>
 *        + NO: 方法调用失败  <br>
 * @notes  <br>
 *         + 该方法在加入房间前后均可调用。 <br>
 *         + 在房间内调用此方法，房间内其他用户会收到相应的回调通知：<br>
 *             - 从 false 切换至 true 时，房间内其他用户会收到 rtcEngine:onUserJoined:elapsed:{@link #ByteRTCEngineDelegate#rtcEngine:onUserJoined:elapsed:} 回调通知；  <br>
 *             - 从 true 切换至 false 时，房间内其他用户会收到 rtcEngine:onUserLeave:reason:{@link #ByteRTCEngineDelegate#rtcEngine:onUserLeave:reason:} 回调通知。 <br>
 *         + 若调用该方法将可见性设为 false，此时尝试发布流会收到 rtcEngine:onWarning:{@link #ByteRTCEngineDelegate#rtcEngine:onWarning:} 警告，具体原因参看 ByteRTCWarningCode{@link #ByteRTCWarningCode} 中的 ByteRTCWarningCodePublishStreamForbiden 警告码。
 */
- (BOOL)setUserVisibility:(BOOL)enable;


/**
 * @type api
 * @region 房间管理
 * @author shenpengliang
 * @brief 将本端音视频流发布到此房间。
 * @notes <br>
 *        + 多房间模式下，默认音视频流不自动发布。你必须调用此接口，进行手动发布。<br>
 *        + 调用 setUserVisibility:{@link #ByteRTCEngineKit#setUserVisibility:} 方法将自身设置为不可见后无法调用该方法，需将自身切换至可见后方可调用该方法发布音视频流。 <br>
 *        + 用户在房间内，同一时间仅能发布一路音视频流。
 *        + 房间内用户调用此方法成功发布音视频流后，房间中的其他用户将会收到 rtcEngine:onStreamAdd:{@link #ByteRTCEngineDelegate#rtcEngine:onStreamAdd:} 回调通知。
 */
- (BOOL)publish;


/**
 * @type api
 * @region 房间管理
 * @author shenpengliang
 * @brief 在当前所在房间内停止发布本地音视频流。
 * @notes  <br>
 *        + 在多房间模式下，调用 publish{@link #ByteRTCEngineKit#publish} 手动发布音视频流后，调用此接口停止发布。<br>
 *        + 用户调用此方法停止发布音视频流后，房间中的其他用户将会收到 rtcEngine:didStreamRemoved:stream:reason:{@link #ByteRTCEngineDelegate#rtcEngine:didStreamRemoved:stream:reason:} 回调通知。
 */
- (BOOL)unpublish;
/**
 * @type api
 * @deprecated from 329.1, no use
 * @region 房间管理
 * @author shenpengliang
 * @brief 获取当前用户角色。  <br>
 * @return 当前用户角色，详见 ByteRTCUserRoleType{@link #ByteRTCUserRoleType} 枚举类型。  <br>
 */
- (ByteRTCUserRoleType)clientRole DEPRECATED_MSG_ATTRIBUTE("no useful");

/**
 * @hidden
 * @type api
 * @deprecated from 326.1, use joinRoom with RoomConfig instead
 * @region 房间管理
 * @author shenpengliang
 * @brief 创建/加入房间：房间不存在时即创建房间；房间存在时即加入这个房间。  <br>
 *        同一个房间内的用户间可以相互通话。  <br>
 *        用户调用 sharedEngineWithAppId:delegate:{@link #ByteRTCEngineKit#sharedEngineWithAppId:delegate:} 创建 RTC 引擎后，需调用此方法加入房间实现同其他用户进行音视频通话。  <br>
 *        如果用户调用此方法加入房间，则后续重复调用此方法均会失败，用户必须调用 leaveRoom:{@link #ByteRTCEngineKit#leaveRoom:} 退出当前房间后，才能加入下一个房间。  <br>
 *        本地用户调用此方法加入房间成功后，会收到 rtcEngine:onUserJoined:elapsed:{@link #ByteRTCEngineDelegate#rtcEngine:onUserJoined:elapsed:} 回调通知，远端用户会收到 rtcEngine:onUserJoined:elapsed:{@link #ByteRTCEngineDelegate#rtcEngine:onUserJoined:elapsed:} 回调通知。  <br>
 * @param token 动态密钥，用于对登录用户进行鉴权验证。  <br>
 *         进入房间需要携带 Token。测试时可使用控制台生成临时 Token ，正式上线需要使用密钥 SDK 在你的服务端生成并下发 Token 。  <br>
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
            userInfo:(ByteRTCUserInfo *_Nonnull)userInfo DEPRECATED_MSG_ATTRIBUTE("Please use joinRoomByKey with roomConfig");

/**
 * @type api
 * @region 房间管理
 * @author shenpengliang
 * @brief 创建/加入房间：房间不存在时即创建房间；房间存在时，未加入房间的用户可加入这个房间。  <br>
 *        同一个房间内的用户间可以相互通话。  <br>
 *        进房后重复调用无效，用户必须调用 leaveRoom:{@link #ByteRTCEngineKit#leaveRoom:} 退出当前房间后，才能加入下一个房间。  <br>
 * @param token 动态密钥，用于对登录用户进行鉴权验证。  <br>
 *        进入房间需要携带 Token。测试时可使用控制台生成临时 Token ，正式上线需要使用密钥 SDK 在你的服务端生成并下发 Token 。  <br>
 *        使用不同 AppID 的 App 是不能互通的。  <br>
 *        请务必保证生成 Token 使用的 AppID 和创建引擎时使用的 AppID 相同，否则会导致加入房间失败。  <br>
 * @param roomId 加入的房间 ID。  <br>
 *        房间 ID 为长度在 128 字节以内的非空字符串，支持以下字符集范围:  <br>
 *             1. 26 个大写字母 A ~ Z 。  <br>
 *             2. 26 个小写字母 a ~ z 。  <br>
 *             3. 10 个数字 0 ~ 9 。  <br>
 *             4. 下划线 "_"，at 符 "@"，减号 "-"。  <br>
 * @param userInfo 用户信息，参看 ByteRTCUserInfo{@link #ByteRTCUserInfo}。  <br>
 * @param rtcRoomConfig 房间参数配置，设置房间模式以及是否自动发布或订阅流。具体配置模式参看 ByteRTCRoomConfig{@link #ByteRTCRoomConfig}。
 * @return 方法调用结果。  <br>
 *        +  0: 成功  <br>
 *        + -1: 参数无效  <br>
 *        + -2: 已经在房间内。接口调用成功后，只要收到返回值为 0 ，且未调用 leaveRoom:{@link #ByteRTCEngineKit#leaveRoom:} 成功，则再次调用进房接口时，无论填写的房间 ID 和用户 ID 是否重复，均触发此返回值。  <br>
 *        + -3: engine 为空 <br>
 * @notes  <br>
 *       + 同一个 AppID 的同一个房间内，每个用户的用户 ID 必须是唯一的。如果两个用户的用户 ID 相同，则后加入房间的用户会将先加入房间的用户踢出房间，并且先加入房间的用户会收到 rtcEngine:onError:{@link #ByteRTCEngineDelegate#rtcEngine:onError:} 回调通知，错误类型为重复登录 BRERR_DUPLICATE_LOGIN。  <br>
 *       + 本地用户调用此方法加入房间成功后，会收到 rtcEngine:onJoinRoomResult:withUid:errorCode:joinType:elapsed:{@link #ByteRTCEngineDelegate#rtcEngine:onJoinRoomResult:withUid:errorCode:joinType:elapsed:} 回调通知。  <br>
 *       + 本地用户调用 setUserVisibility:{@link #ByteRTCEngineKit#setUserVisibility:} 将自身设为可见后加入房间，远端用户会收到 rtcEngine:onUserJoined:elapsed:{@link #ByteRTCEngineDelegate#rtcEngine:onUserJoined:elapsed:} 回调通知。  <br>
 *       + 用户加入房间成功后，在本地网络状况不佳的情况下，SDK 可能会与服务器失去连接，此时 SDK 将会自动重连。重连成功后，本地会收到 rtcEngine:onUserJoined:elapsed:{@link #ByteRTCEngineDelegate#rtcEngine:onUserJoined:elapsed:} 回调通知。  <br>
 */
- (int)joinRoomByKey:(NSString *_Nullable)token
              roomId:(NSString *_Nonnull)roomId
            userInfo:(ByteRTCUserInfo *_Nonnull)userInfo
       rtcRoomConfig:(ByteRTCRoomConfig *_Nonnull)rtcRoomConfig;


/**
 *  @type api
 *  @deprecated from 328.1, use leaveRoom without block instead
 *  @region 房间管理
 *  @author shenpengliang
 *  @brief 离开房间。  <br>
 *         用户调用此方法离开房间，结束通话过程，释放所有通话相关的资源。  <br>
 *         调用 joinRoomByKey:roomId:userInfo:rtcRoomConfig:{@link #ByteRTCEngineKit#joinRoomByKey:roomId:userInfo:rtcRoomConfig:} 方法加入房间后，必须调用此方法离开房间，否则无法进入下一个房间。无论当前是否在房间内，都可以调用此方法。重复调用此方法没有负面影响。  <br>
 *         此方法是异步操作，调用返回时并没有真正退出房间。真正退出房间后，SDK 会执行调用此方法时传入的 Block 块。  <br>
 *  @param leaveRoomBlock 离开房间完成后执行的 Block 块。Block 的输入参数为加入房间到离开房间过程间的统计信息，详见 ByteRTCRoomStats{@link #ByteRTCRoomStats}。  <br>
 *  @return 方法调用结果。  <br>
 *         +  0: 方法调用成功  <br>
 *         + <0: 方法调用失败  <br>
 *  @notes  <br>
 *        + 可见的用户离开房间后，房间内其他用户会收到 rtcEngine:onUserLeave:reason:{@link #ByteRTCEngineDelegate#rtcEngine:onUserLeave:reason:} 回调通知。  <br>
 *        + 如果调用此方法后立即销毁引擎，SDK 将无法执行作为参数传入的 Block 块。  <br>
 */
- (int)leaveRoom:(void (^_Nullable)(ByteRTCRoomStats *_Nonnull stat))leaveRoomBlock
DEPRECATED_MSG_ATTRIBUTE("Please use leaveRoom");


/**
 * @type api
 * @region 房间管理
 * @author shenpengliang
 * @brief 离开房间。 <br>
 *        用户调用此方法离开房间，结束通话过程，释放所有通话相关的资源。 <br>
 * @return 方法调用结果。 <br>
 *        + 0: 方法调用成功 <br>
 *        + <0: 方法调用失败 <br>
 * @notes <br>
 *       + 用户离开房间后，本地会收到 rtcEngine:onLeaveRoomWithStats:{@link #ByteRTCEngineDelegate#rtcEngine:onLeaveRoomWithStats:} 的回调；  <br>
 *       + 可见的用户离开房间后，房间内其他用户会收到 rtcEngine:onUserLeave:reason:{@link #ByteRTCEngineDelegate#rtcEngine:onUserLeave:reason:} 回调通知；  <br>
 *       + 调用 joinRoomByKey:roomId:userInfo:rtcRoomConfig:{@link #ByteRTCEngineKit#joinRoomByKey:roomId:userInfo:rtcRoomConfig:} 方法加入房间后，必须调用此方法离开房间，否则无法进入下一个房间。无论当前是否在房间内，都可以调用此方法。重复调用此方法没有负面影响。  <br>
 */
- (int)leaveRoom;

/**
 * @type api
 * @region 房间管理
 * @author shenpengliang
 * @brief 更新 Token。  <br>
 *        用户调用 joinRoomByKey:roomId:userInfo:rtcRoomConfig:{@link #ByteRTCEngineKit#joinRoomByKey:roomId:userInfo:rtcRoomConfig:} 方法加入房间时，
 *        如果使用了过期的 Token 将导致加入房间失败，并会收到 rtcEngine:onJoinRoomResult:withUid:errorCode:joinType:elapsed:{@link #ByteRTCEngineDelegate#rtcEngine:onJoinRoomResult:withUid:errorCode:joinType:elapsed:} 回调，
 *        回调错误码为 ByteRTCErrorCode{@link #ByteRTCErrorCode} 中的 ByteRTCErrorCodeInvalidToken
 *        此时需要重新获取 Token，并调用此方法更新 Token。更新 Token 后，SDK 会自动加入房间。 <br>
 * @param token 更新的动态密钥。  <br>
 * @return 方法调用结果。  <br>
 *         +  0: 方法调用成功。  <br>
 *         + <0: 方法调用失败。  <br>
 * @notes Token 过期时，如果已经加入房间成功，则不会受到影响。Token 过期的错误会在下一次使用过期的 Token 加入房间时，或因本地网络状况不佳导致断网重新连入房间时通知用户。
 */
- (int)updateToken:(NSString *_Nonnull)token;

/**
 * @type api
 * @region 引擎管理
 * @author chenweiming.push
 * @brief 获取 SDK 内各种错误码、警告码的描述文字。
 * @param code  <br>
 *        通过 rtcEngine:onWarning:{@link #ByteRTCEngineDelegate#rtcEngine:onWarning:} 和 rtcEngine:onError:{@link #ByteRTCEngineDelegate#rtcEngine:onError:} 回调获得的值，
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
 *        进房前调用该方法，本地用户会收到 rtcEngine:onMediaDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCEngineDelegate#rtcEngine:onMediaDeviceStateChanged:device_type:device_state:device_error:} 的回调。  <br>
 *        进房后调用该方法，房间中的其他用户会收到 rtcEngine:onUserStartAudioCapture:{@link #ByteRTCEngineDelegate#rtcEngine:onUserStartAudioCapture:} 的回调。
 * @notes  <br>
 *       + 若未取得当前设备的麦克风权限，调用该方法后会触发 rtcEngine:onWarning:{@link #ByteRTCEngineDelegate#rtcEngine:onWarning:} 回调。  <br>
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
  *        进房前调用该方法，本地用户会收到 rtcEngine:onMediaDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCEngineDelegate#rtcEngine:onMediaDeviceStateChanged:device_type:device_state:device_error:} 的回调。  <br>
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
 * @author dixing
 * @brief 设置音质档位。你应根据业务场景需要选择适合的音质档位。  <br>
 * @param audioProfile 音质档位，参看 ByteRTCAudioProfileType{@link #ByteRTCAudioProfileType}
 * @notes  <br>
 *        + 该方法在进房前后均可调用；  <br>
 *        + 支持通话过程中动态切换音质档位。
 */
- (void)setAudioProfile:(ByteRTCAudioProfileType)audioProfile;

/**
 * @type api
 * @region 媒体流管理
 * @author shenpengliang
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
 * @hidden
 * @deprecated from 326.1, use SubscribeUserStream instead
 * @type api
 * @region 媒体流管理
 * @author shenpengliang
 * @brief 设置对来自指定远端用户的音频流的接收状态。默认为接收。
 * @param uid 指定远端用户的 ID
 * @param muteState 接收状态，标识是否接收远端音频流，详见 ByteRTCMuteState{@link #ByteRTCMuteState}
 */
- (void)muteRemoteAudio:(NSString * _Nonnull)uid muteState:(ByteRTCMuteState)muteState
DEPRECATED_MSG_ATTRIBUTE("Please use subscribeUserStream");

/**
 * @hidden
 * @deprecated from 326.1, use  pauseAllSubscribedStream/resumeAllSubscribedStream instead
 * @type api
 * @region 媒体流管理
 * @author shenpengliang
 * @brief 设置对来自远端的所有音频流的接收状态。默认为接收。
 * @param muteState 接收状态，标识是否接收远端音频流，详见 ByteRTCMuteState{@link #ByteRTCMuteState}
 * @notes 本方法只影响本地是否接收远端音频流，并不影响远端音频设备的采集发送功能。
 */
- (void)muteAllRemoteAudio:(ByteRTCMuteState)muteState
DEPRECATED_MSG_ATTRIBUTE("Please use pauseAllSubscribedStream or resumeAllSubscribedStream");

/**
 * @type api
 * @region 房间管理
 * @author shenpengliang
 * @brief 暂停接收来自远端的媒体流
 * @param mediaType 媒体流类型，指定需要暂停接收音频还是视频流，参看 ByteRTCPauseResumControlMediaType{@link #ByteRTCPauseResumControlMediaType}。
 * @notes  <br>
 *        + 该方法仅暂停远端流的接收，并不影响远端流的采集和发送；  <br>
 *        + 该方法不改变用户的订阅状态以及订阅流的属性。  <br>
 *        + 若想恢复接收远端流，需调用 resumeAllSubscribedStream:{@link #ByteRTCEngineKit#resumeAllSubscribedStream:}。
 */
- (void)pauseAllSubscribedStream:(ByteRTCPauseResumControlMediaType) mediaType;

/**
 * @type api
 * @region 房间管理
 * @author shenpengliang
 * @brief 恢复接收来自远端的媒体流
 * @param mediaType 媒体流类型，指定需要暂停接收音频还是视频流，参看 ByteRTCPauseResumControlMediaType{@link #ByteRTCPauseResumControlMediaType}
 * @notes <br>
 *        + 该方法仅恢复远端流的接收，并不影响远端流的采集和发送；  <br>
 *        + 该方法不改变用户的订阅状态以及订阅流的属性。
 */
- (void)resumeAllSubscribedStream:(ByteRTCPauseResumControlMediaType) mediaType;

/**
 * @deprecated from 325.1, use enableAudioPropertiesReport instead
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
 * @hidden
 * @deprecated from 323.1, use setCaptureVolume instead
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
- (void)setRecordingVolume:(NSInteger)volume
DEPRECATED_MSG_ATTRIBUTE("Please use setCaptureVolume");

/**
 * @type api
 * @region 音频管理
 * @author wangjunzheng
 * @brief 调节音频采集音量
 * @param index 流索引，指定调节主流还是调节屏幕流的音量，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param volume 采集的音量值和原始音量的比值，范围是 [0, 400]，单位为 %，自带溢出保护。
 * @notes <br>
 *        + 无论是采集来自麦克风的音频流，还是屏幕音频流；无论是 RTC SDK 内部采集，还是自定义采集，都可以使用此接口进行音量调节。
 *        + 在开启音频采集前后，你都可以使用此接口设定采集音量。
 */
- (void)setCaptureVolume:(ByteRTCStreamIndex)index volume:(int)volume;

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

/**
 * @type api
 * @region 音频管理
 * @author wangjunzheng
 * @brief 启用音量提示。  <br>
 * @param config 音频信息提示的相关配置，详见 ByteRTCAudioPropertiesConfig{@link #ByteRTCAudioPropertiesConfig}  <br>
 * @notes 开启提示后，你可以：  <br>
 *       + 通过 rtcEngine:onLocalAudioPropertiesReport:{@link #ByteRTCEngineDelegate#rtcEngine:onLocalAudioPropertiesReport:} 回调获取本地麦克风和屏幕音频流采集的音量信息；  <br>
 *       + 通过 rtcEngine:onRemoteAudioPropertiesReport:totalRemoteVolume:{@link #ByteRTCEngineDelegate#rtcEngine:onRemoteAudioPropertiesReport:totalRemoteVolume:} 回调获取订阅的远端用户的音量信息。  <br>
 */
- (void)enableAudioPropertiesReport:(ByteRTCAudioPropertiesConfig* _Nonnull)config;

/**
 * @type api
 * @region 音频管理
 * @author majun.lvhiei
 * @brief 开启/关闭耳返功能
 * @param mode 是否开启耳返功能，参看 ByteRTCEarMonitorMode{@link #ByteRTCEarMonitorMode}
 * @notes <br>
 *        + 你必须在使用 RTC SDK 提供的内部音频采集功能时，使用耳返功能。<br>
 *        + 耳返功能仅在连接了有线耳机时有效。<br>
 *        + 受 iOS 平台限制，RTC 仅支持软件耳返功能。
 */
- (void)setEarMonitorMode:(ByteRTCEarMonitorMode)mode;

/**
 * @type api
 * @region 音频管理
 * @author majun.lvhiei
 * @brief 设置耳返的音量
 * @param [in] volume 耳返的音量，取值范围：[0,100]，单位：%
 * @notes <br>
 *        + 设置耳返音量前，你必须先调用 setEarMonitorMode:{@link #setEarMonitorMode:} 打开耳返功能。<br>
 *        + 耳返功能仅在使用 RTC SDK 提供的内部音频采集功能，并连接了有线耳机时有效。<br>
 */
- (void)setEarMonitorVolume:(NSInteger)volume;

#pragma mark Core Video Methods
/**-----------------------------------------------------------------------------
 * @name 视频核心方法
 * -----------------------------------------------------------------------------
 */

/**
 * @type api
 * @region 自定义视频采集渲染
 * @author sunhang.io
 * @brief 将本地视频流与自定义渲染器绑定。
 * @param index 视频流属性。采集的视频流/屏幕视频流，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param videoSink 自定义视频渲染器，参看 ByteRTCVideoSinkDelegate{@link #ByteRTCVideoSinkDelegate}
 * @param requiredFormat video_sink 适用的视频帧编码格式，参看 ByteRTCVideoSinkPixelFormat{@link #ByteRTCVideoSinkPixelFormat}
 * @notes  <br>
 *        + RTC SDK 默认使用 RTC SDK 自带的渲染器（内部渲染器）进行视频渲染。
 *        + 如果需要解除绑定，必须将 videoSink 设置为 null。进退房操作不会影响绑定状态。
 *        + 一般在收到 rtcEngine:onFirstLocalVideoFrameCaptured:withFrameInfo:{@link #ByteRTCEngineDelegate#rtcEngine:onFirstLocalVideoFrameCaptured:withFrameInfo:} 回调通知完成本地视频首帧采集后，调用此方法为视频流绑定自定义渲染器；然后加入房间。
 */
- (void)setLocalVideoSink:(ByteRTCStreamIndex)index
                withSink:(id<ByteRTCVideoSinkDelegate> _Nullable)videoSink
         withPixelFormat:(ByteRTCVideoSinkPixelFormat)requiredFormat;

/**
 * @type api
 * @region 自定义视频采集渲染
 * @author sunhang.io
 * @brief 将远端视频流与自定义渲染器绑定。
 * @param streamKey 远端流信息，用于指定需要渲染的视频流来源及属性，参看 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
 * @param videoSink 自定义视频渲染器，参看 ByteRTCVideoSinkDelegate{@link #ByteRTCVideoSinkDelegate}
 * @param requiredFormat videoSink 适用的视频帧编码格式，参看 ByteRTCVideoSinkPixelFormat{@link #ByteRTCVideoSinkPixelFormat}
 * @notes  <br>
 *        + RTC SDK 默认使用 RTC SDK 自带的渲染器（内部渲染器）进行视频渲染。
 *        + 该方法进房前后均可以调用。若想在进房前调用，你需要在加入房间前获取远端流信息；若无法预先获取远端流信息，你可以在加入房间并通过 rtcEngine:onStreamAdd:{@link #ByteRTCEngineDelegate#rtcEngine:onStreamAdd:} 回调获取到远端流信息之后，再调用该方法。
 *        + 如果需要解除绑定，必须将 videoSink 设置为 null。进退房操作不会影响绑定状态。
 */
- (void)setRemoteVideoSink:(ByteRTCRemoteStreamKey* _Nonnull)streamKey
                withSink:(id<ByteRTCVideoSinkDelegate> _Nullable)videoSink
         withPixelFormat:(ByteRTCVideoSinkPixelFormat)requiredFormat;

/**
 * @hidden
 * @deprecated
 * @type api
 * @region 自定义视频采集渲染
 * @author sunhang.io
 * @brief 设置本地视频外部渲染器。
 * @param videoRenderer 外部渲染器，具体参照 ByteRTCVideoSinkDelegate{@link #ByteRTCVideoSinkDelegate}
 * @return  <br>
 *         + 0：方法调用成功  <br>
 *         + <0：方法调用失败  <br>
 */
- (int)setLocalVideoRenderer:(id<ByteRTCVideoSinkProtocol> _Nullable)videoRenderer
DEPRECATED_MSG_ATTRIBUTE("Please use setLocalVideoSink");

/**
 * @hidden
 * @deprecated
 * @type api
 * @region 自定义视频采集渲染f
 * @author sunhang.io
 * @brief 设置本地视频外部渲染器。
 * @param videoRenderer 外部渲染器，具体参照 ByteRTCVideoSinkDelegate{@link #ByteRTCVideoSinkDelegate}
 * @param roomId 房间ID
 * @param userId 用户ID
 * @return  <br>
 *         + 0：方法调用成功  <br>
 *         + <0：方法调用失败  <br>
 */
- (int)setLocalVideoRenderer:(id<ByteRTCVideoSinkProtocol> _Nullable)videoRenderer
                   forRoomId:(NSString * _Nonnull)roomId
                   forUserId:(NSString * _Nonnull)userId
DEPRECATED_MSG_ATTRIBUTE("Please use setLocalVideoSink");

/**
 * @hidden
 * @deprecated
 * @type api
 * @region 自定义视频采集渲染
 * @author sunhang.io
 * @brief 设置来自指定远端用户的视频流的外部渲染器。<br>
 *        如果需要将远端视频流和外部渲染器解绑，将 videoRenderer 设置为 null。
 * @param videoRenderer 外部视频渲染器，参看 ByteRTCVideoSinkProtocol{@link #ByteRTCVideoSinkProtocol}
 * @param roomId 房间 ID
 * @param userId 远端用户 ID
 * @return  <br>
 *         + 0：方法调用成功  <br>
 *         + <0：方法调用失败  <br>
 */
- (int)setRemoteVideoRenderer:(id<ByteRTCVideoSinkProtocol> _Nullable)videoRenderer
                    forRoomId:(NSString * _Nonnull)roomId
                    forUserId:(NSString * _Nonnull)userId
DEPRECATED_MSG_ATTRIBUTE("Please use setRemoteVideoSink");

/**
 * @hidden
 * @deprecated
 * @type api
 * @region 自定义视频采集渲染
 * @author sunhang.io
 * @brief 设置来自制定远端用户的视频流的外部渲染器。
 * @param videoRenderer 外部视频渲染器，参看 ByteRTCVideoSinkProtocol{@link #ByteRTCVideoSinkProtocol}
 * @param userId 远端用户 ID
 * @return  <br>
 *         + 0：方法调用成功  <br>
 *         + <0：方法调用失败  <br>
 */
- (int)setRemoteVideoRenderer:(id<ByteRTCVideoSinkProtocol> _Nullable)videoRenderer
                    forUserId:(NSString * _Nonnull)userId
DEPRECATED_MSG_ATTRIBUTE("Please use setRemoteVideoSink");

/**
 * @hidden
 * @deprecated
 * @type api
 * @hidden
 * @region 视频管理
 * @author panjian.fishing
 * @brief 启动推送多路视频流，设置推送多路流时的各路视频参数，
 *        包括分辨率、帧率、码率、缩放模式、网络不佳时的回退策略等。
 * @param videoSolutions 视频参数数组首地址，参看 ByteRTCVideoSolution{@link #ByteRTCVideoSolution}。  <br>
*                        最多支持 3 路参数。当设置了多路参数时，分辨率必须是依次减小，从大到小排列的。 <br>
 *                       最大分辨率没有限制。但是如果设置的分辨率无法编码，就会导致编码推流失败。
 * @return  <br>
 *         + 0：方法调用成功  <br>
 *         + <0：方法调用失败  <br>
 * @notes <br>
 *        + 当使用内部采集时，视频采集的分辨率、帧率会根据编码参数进行适配。<br>
 *        + 默认的视频编码参数为：分辨率 640px * 360px，帧率 15fps。<br>
 *        + 变更编码分辨率后马上生效，可能会引发相机重启。
 */
- (int)setVideoEncoderConfig:(NSArray <ByteRTCVideoSolution *> * _Nullable)videoSolutions;


/**
 * @type api
 * @region 视频管理
 * @author wangzhanqiang
 * @brief 启动推送多路视频流，设置推送多路流时的各路视频参数，包括分辨率、帧率、码率、缩放模式、网络不佳时的回退策略等。
 * @param streamIndex 视频流属性，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}。
 * @param videoSolutions 要推送的多路视频流参数，参看 ByteRTCVideoSolution{@link #ByteRTCVideoSolution}。 <br>
 *                       最多支持 4 路参数。当设置了多路参数时，分辨率必须是从大到小排列。 <br>
 *                       最大分辨率为 4096px * 4096px，超过或设置的分辨率无法编码时，会导致编码推流失败。
 * @return  <br>
 *        + 0：成功  <br>
 *        + !0：失败  <br>
 * @notes  <br>
 *       + 当使用内部采集时，视频采集的分辨率、帧率会根据最大的编码分辨率、帧率进行适配<br>
 *       + 默认的视频编码参数为：分辨率 640px * 360px，帧率 15fps。<br>
 *       + 变更编码分辨率后马上生效，可能会引发相机重启。<br>
 *       + 屏幕流只取视频参数数组的第一组数据。
 */
- (int)setVideoEncoderConfig:(ByteRTCStreamIndex)streamIndex config:(NSArray <ByteRTCVideoSolution *> * _Nullable)videoSolutions;

/**
 * @type api
 * @region 视频管理
 * @author wangcheng.leo
 * @brief 设置 RTC SDK 内部采集时的视频采集参数。<br>
 *        如果你的项目使用了 SDK 内部采集模块，可以通过本接口指定视频采集参数包括分辨率、帧率。
 * @param captureConfig 视频采集参数。参看: ByteRTCVideoCaptureConfig{@link #ByteRTCVideoCaptureConfig}。
 * @return  <br>
 *        + 0: 成功；  <br>
 *        + <0: 失败；  <br>
 * @notes  <br>
 * + 本接口在引擎创建后可调用，调用后立即生效。建议在调用 startVideoCapture{@link #startVideoCapture} 前调用本接口。
 * + 建议同一设备上的不同 Engine 使用相同的视频采集参数。
 * + 如果调用本接口前使用内部模块开始视频采集，采集参数默认为 setVideoEncoderConfig:config:{@link #ByteRTCEngineKit#setVideoEncoderConfig:config:} 中设置的参数。
 */
- (int)setVideoCaptureConfig:(ByteRTCVideoCaptureConfig * _Nullable)captureConfig;

/**
 * @type api
 * @region 视频管理
 * @author sunhang.io
 * @brief 设置本地视频渲染时，使用的视图，并设置渲染模式。  <br>
 *        你应在加入房间前，绑定本地视图。退出房间后，此设置仍然有效。
 *        如果需要解除绑定，你可以调用本方法绑定空视图。
 * @param streamIndex 流属性，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param canvas 视图信息和渲染模式，参看 ByteRTCVideoCanvas{@link #ByteRTCVideoCanvas}
 * @return  <br>
 *         + 0：方法调用成功  <br>
 *         + <0：方法调用失败  <br>
 */
- (int)setLocalVideoCanvas:(ByteRTCStreamIndex)streamIndex
                withCanvas:(ByteRTCVideoCanvas * _Nullable)canvas;

/**
 * @type api
 * @region 视频管理
 * @author sunhang.io
 * @brief 渲染来自指定远端用户 uid 的视频流时，设置使用的视图和渲染模式。  <br>
 *        如果需要解除视频的绑定视图，把 canvas 设置为空。
 * @notes  <br>
 *       + 实际使用时，你可以在收到回调 rtcEngine:onUserJoined:elapsed:{@link #ByteRTCEngineDelegate#rtcEngine:onUserJoined:elapsed:} 或 rtcEngine:onFirstRemoteVideoFrameRendered:withFrameInfo:{@link #ByteRTCEngineDelegate#rtcEngine:onFirstRemoteVideoFrameRendered:withFrameInfo:} 时获得远端用户 uid。
 *         这两个回调的差别是：如果启用了视频录制功能，视频录制服务会作为一个哑客户端加入房间，因此其他客户端会收到对应的 rtcEngine:onUserJoined:elapsed:{@link #ByteRTCEngineDelegate#rtcEngine:onUserJoined:elapsed:} 回调；
 *         而不会收到 rtcEngine:onFirstRemoteVideoFrameRendered:withFrameInfo:{@link #ByteRTCEngineDelegate#rtcEngine:onFirstRemoteVideoFrameRendered:withFrameInfo:} 回调。你不应给录制的哑客户端绑定视图（因为它不会发送视频流）。
 *       + 你应在加入房间后，绑定视图。退出房间后，此设置失效。
 * @param uid 视频来源的远端用户 ID
 * @param streamIndex 视频流属性，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param canvas 视图信息和渲染模式，参看 ByteRTCVideoCanvas{@link #ByteRTCVideoCanvas}
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
  * @author zhangzhenyu.samuel
  * @brief 开启内部视频采集。默认为关闭状态。  <br>
  *        调用该方法后，本地用户会收到 rtcEngine:onMediaDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCEngineDelegate#rtcEngine:onMediaDeviceStateChanged:device_type:device_state:device_error:} 的回调。  <br>
  *        进房后调用该方法，房间中的其他用户会收到 rtcEngine:onUserStartVideoCapture:{@link #ByteRTCEngineDelegate#rtcEngine:onUserStartVideoCapture:} 的回调。
  * @notes  <br>
  *       + 内部视频采集指：使用 RTC SDK 内置视频采集模块，进行采集。
  *       + 若未取得当前设备的摄像头权限，调用该方法会不成功，并触发 rtcEngine:onMediaDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCEngineDelegate#rtcEngine:onMediaDeviceStateChanged:device_type:device_state:device_error:} 回调。  <br>
  *       + 调用 stopVideoCapture{@link #ByteRTCEngineKit#stopVideoCapture} 可以关闭视频采集设备，否则，SDK 只会在销毁引擎的时候自动关闭设备。  <br>
  *       + 无论是否发布视频数据，你都可以调用该方法开启视频采集，并且调用后方可发布视频。  <br>
  *       + 如果需要从自定义视频采集切换为内部视频采集，你必须先关闭自定义采集，再调用此方法手动开启内部采集。
  */
- (void)startVideoCapture;

 /**
  * @type api
  * @region 视频管理
  * @author zhangzhenyu.samuel
  * @brief 关闭内部视频采集。默认为关闭状态。  <br>
  *        调用该方法后，本地用户会收到 rtcEngine:onMediaDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCEngineDelegate#rtcEngine:onMediaDeviceStateChanged:device_type:device_state:device_error:} 的回调。  <br>
  *        进房后调用该方法，房间中的其他用户会收到 rtcEngine:onUserStopVideoCapture:{@link #ByteRTCEngineDelegate#rtcEngine:onUserStopVideoCapture:} 的回调。
  * @notes  <br>
  *       + 调用 startVideoCapture{@link #startVideoCapture} 可以开启视频采集设备。  <br>
  *       + 设备开启后若一直未调用此方法关闭本地视频采集，则 SDK 会在销毁引擎的时候自动关闭。  <br>
  */
- (void)stopVideoCapture;

/**
 * @type api
 * @region 视频管理
 * @author zhushufan.ref
 * @brief 停止/启动发送本地视频流，默认不发送。<br>
 *        无论你使用内部视频采集，还是自定义视频采集，你都应使用此接口启动发送本地视频流。<br>
 *        调用该方法后，房间中的其他用户会收到 rtcEngine:onUserMuteVideo:withMuteState:{@link #ByteRTCEngineDelegate#rtcEngine:onUserMuteVideo:withMuteState:} 的回调。
 * @param mute_state 发送状态，标识是否发送本地视频流，参看 ByteRTCMuteState{@link #ByteRTCMuteState}
 * @notes <br>
 *        + 本方法只是停止/启动本地视频流的发送，不影响视频采集状态。
 *        + 无论是否开启视频采集，你都可以启动发送本地视频流。这样，一旦开始采集视频，即可进行发送。
 */
- (void)muteLocalVideo:(ByteRTCMuteState)mute_state;

/**
 * @hidden
 * @deprecated from 326.1, use  subscribeUserStream instead
 * @type api
 * @region 媒体流管理
 * @author shenpengliang
 * @brief 设置是否播放远端视频流
 * @param uid 视频来源的远端用户 ID
 * @param muteState 播放状态，标识是否播放远端视频流，参看 ByteRTCMuteState{@link #ByteRTCMuteState}
 * @return  <br>
 *         + 0：方法调用成功  <br>
 *         + <0：方法调用失败  <br>
 */
- (int)muteRemoteVideo:(NSString * _Nonnull)uid
                        withMuteState:(ByteRTCMuteState)muteState DEPRECATED_MSG_ATTRIBUTE("Please use subscribeUserStream");

/**
 * @hidden
 * @deprecated from 326.1, use  pauseAllSubscribedStream/resumeAllSubscribedStream instead
 * @type api
 * @region 媒体流管理
 * @author shenpengliang
 * @brief 设置是否播放所有远端视频流
 * @param muteState 播放状态，标识是否播放远端视频流，参看 ByteRTCMuteState{@link #ByteRTCMuteState}
 * @return  <br>
 *         + 0：方法调用成功  <br>
 *         + <0：方法调用失败  <br>
 */
- (int)muteAllRemoteVideo:(ByteRTCMuteState)muteState
DEPRECATED_MSG_ATTRIBUTE("Please use pauseAllSubscribedStream or resumeAllSubscribedStream");

/**
 * @deprecated from 329.1, use setLocalVideoMirrorType instead
 * @type api
 * @region 视频管理
 * @author wangjunlin.3182
 * @brief 设置采用前置摄像头采集时，是否开启镜像模式。默认为关闭状态。 <br>
 * @param mode 是否开启镜像模式，参看 ByteRTCMirrorMode{@link #ByteRTCMirrorMode}
 * @return  <br>
 *         + 0：成功  <br>
 *         + <0：失败  <br>
 */
- (int)setLocalVideoMirrorMode:(ByteRTCMirrorMode) mode;

/**
 * @type api
 * @region 视频管理
 * @author wangjunlin.3182
 * @brief 为本地采集到的视频流开启镜像
 * @param mirrorType 设置镜像类型，参看 ByteRTCMirrorType{@link #ByteRTCMirrorType}
 * @notes <br>
 *        + 该接口调用前，各视频源的初始状态如下：<br>
 *        <table>
 *           <tr><th></th><th>前置摄像头</th><th>后置摄像头</th><th>自定义采集视频源</th> <th>桌面端摄像头</th> </tr>
 *           <tr><td>移动端</td><td>本地渲染镜像，编码传输不镜像</td><td> 本地渲染不镜像，编码传输不镜像 </td><td> 本地渲染不镜像，编码传输不镜像 </td><td>/</td></tr>
 *           <tr><td>桌面端</td><td>/</td><td>/</td><td> 本地渲染不镜像，编码传输不镜像 </td><td> 本地渲染镜像，编码传输不镜像 </td></tr>
 *        </table>
 *        + 切换视频源不影响镜像设置。<br>
 *        + 屏幕视频流始终不受镜像设置影响。<br>
 */
- (int)setLocalVideoMirrorType:(ByteRTCMirrorType) mirrorType;

/**
 * @type api
 * @region 视频管理
 * @author zhangzhenyu.samuel
 * @brief 切换视频内部采集时使用的前置/后置摄像头 <br>
 *        调用此接口后，在本地会触发 rtcEngine:onMediaDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCEngineDelegate#rtcEngine:onMediaDeviceStateChanged:device_type:device_state:device_error:} 回调。
 * @param cameraId 移动端摄像头 ID，参看 ByteRTCCameraID{@link #ByteRTCCameraID}。  <br>
 * @return  <br>
 *         + 0：方法调用成功  <br>
 *         + <0：方法调用失败  <br>
 * @notes <br>
 *        + 默认使用前置摄像头。
 *        + 如果你正在使用相机进行视频采集，切换操作当即生效；如果相机未启动，后续开启内部采集时，会打开设定的摄像头。
 */
- (int)switchCamera:(ByteRTCCameraID) cameraId;

/**
 * @hidden
 * @type api
 * @region 视频特效
 * @author zhushufan.ref
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
 * @author zhushufan.ref
 * @brief 视频特效许可证检查
 * @param licenseFile 许可证文件绝对路径
 * @return  <br>
 *      + 0: 许可证验证成功  <br>
 *      + !0: 许可证验证失败
 * @notes enableVideoEffect:{@link #enableVideoEffect:} 开始使用视频特效前，需要先调用这个方法进行许可证验证
 */
- (int)checkVideoEffectLicense:(NSString * _Nonnull)licenseFile;

/**
 * @type api
 * @region 视频特效
 * @author zhushufan.ref
 * @brief 创建/销毁视频特效引擎
 * @param enabled  <br>
 *        是否创建视频特效引擎  <br>
 *       + true: 创建  <br>
 *       + false: 销毁
 * @return 方法调用结果  <br>
 *        + 0: 成功  <br>
 *        + !0: 失败
 * @notes  <br>
 *       + 该方法须在调用 checkVideoEffectLicense:{@link #checkVideoEffectLicense:} 和 setVideoEffectAlgoModelPath:{@link #setVideoEffectAlgoModelPath:} 后调用。  <br>
 *       + 该方法不直接开启/关闭视频特效，你须在调用该方法后，调用 setVideoEffectNodes:{@link #setVideoEffectNodes:} 开启视频特效。  <br>
 *       + 通用场景下，特效引擎会随 RTC 引擎销毁而销毁。当你对性能有较高要求时，可在不使用特效相关功能时调用该方法中 false 单独销毁特效引擎。
 */
- (int)enableVideoEffect:(BOOL)enabled;

/**
 * @type api
 * @region 视频特效
 * @author zhushufan.ref
 * @brief 设置视频特效算法模型路径
 * @param modelPath  <br>
 *        模型路径
 */
- (void)setVideoEffectAlgoModelPath:(NSString * _Nonnull)modelPath;

/**
 * @type api
 * @region 视频特效
 * @author zhushufan.ref
 * @brief 设置视频特效素材包，支持同时设置多个素材包
 * @param effectNodePaths 特效素材包路径数组
 * @return  <br>
 *      + 0: 调用成功  <br>
 *      + 1000: 未集成 CV SDK  <br>
 *      + 1001: 本 RTC 版本不支持 CV 功能  <br>
 *      + <0: 调用失败，具体错误码，请参考[CV SDK 文档](http://ailab-cv-sdk.bytedance.com/docs/2036/99783/)。
 * @notes 在调用这个方法之前，你须先调用 enableVideoEffect:{@link #ByteRTCEngineKit#enableVideoEffect:} 。
 */
- (int) setVideoEffectNodes:(NSArray <NSString *> *_Nonnull)effectNodePaths;

/**
 * @type api
 * @region 视频特效
 * @author zhushufan.ref
 * @brief 设置特效强度
 * @param nodePath 特效素材包路径。
 * @param nodeKey 需要设置的素材 key 名称。参看 [素材key对应说明](http://ailab-cv-sdk.bytedance.com/docs/2036/99769/)。
 * @param nodeValue 需要设置的强度值。取值范围为 [0,1]，超出该范围设置无效。
 * @return  <br>
 *      + 0: 调用成功  <br>
 *      + 1000: 未集成 CV SDK  <br>
 *      + 1001: 本 RTC 版本不支持 CV 功能  <br>
 *      + <0: 调用失败，具体错误码，请参考 [CV SDK 文档](http://ailab-cv-sdk.bytedance.com/docs/2036/99783/)。
 * @notes 该接口仅适用于同时含有上述三个参数的特效资源，对于如大部分贴纸类等没有强度参数的特效，该接口调用无效。
 */
- (int) updateVideoEffectNode:(NSString * _Nonnull)nodePath nodeKey:(NSString * _Nonnull)nodeKey  nodeValue:(float) nodeValue;

/**
 * @type api
 * @region 视频特效
 * @author zhushufan.ref
 * @brief 设置颜色滤镜
 * @param resPath  <br>
 *        滤镜资源包绝对路径
 * @return  <br>
 *      + 0: 调用成功  <br>
 *      + 1000: 未集成 CV SDK  <br>
 *      + 1001: 本 RTC 版本不支持 CV 功能  <br>
 *      + <0: 调用失败，具体错误码，请参考[CV SDK 文档](http://ailab-cv-sdk.bytedance.com/docs/2036/99783/)。
 */
- (int) setVideoEffectColorFilter:(NSString * _Nonnull)resPath;

/**
 * @type api
 * @region 视频特效
 * @author zhushufan.ref
 * @brief 设置已启用的颜色滤镜强度
 * @param intensity 滤镜强度。取值范围 [0,1]，超出范围时设置无效
 * @return  <br>
 *      + 0: 调用成功  <br>
 *      + 1000: 未集成 CV SDK  <br>
 *      + 1001: 本 RTC 版本不支持 CV 功能  <br>
 *      + <0: 调用失败，具体错误码，请参考 [CV SDK 文档](http://ailab-cv-sdk.bytedance.com/docs/2036/99783/)。
 */
- (int) setVideoEffectColorFilterIntensity:(float) intensity;


#pragma mark - MediaMetadataData InnerVideoSource
/**
 * @hidden
 * @deprecated
 * @type api
 * @region 视频数据回调
 * @author wangjunlin.3182
 * @brief 注册 metadata 观察者，用于接收或发送 metadata，底层通过在视频帧中添加 SEI 数据实现该功能。  <br>
 *        注册观察者后，发送的视频帧里面没有 SEI 信息， 会触发 videoFrameMediaMetaDataAtTime:{@link #videoFrameMediaMetaDataAtTime:} 回调。  <br>
 *        注册观察者后，接收的视频帧里面有 SEI 信息，会触发接收 receiveVideoFrameFromUID:withExtendedData:atTimestamp:{@link #receiveVideoFrameFromUID:withExtendedData:atTimestamp:} 回调。  <br>
 * @param metadataObserver metadata 观察者，详见： ByteRTCMediaMetadataObserver{@link #ByteRTCMediaMetadataObserver}
 * @return  <br>
 *         + YES: 设置成功  <br>
 *         + NO: 设置失败  <br>
 * @notes  <br>
 *      + 使用视频自定义采集与渲染时，可以直接在视频帧中添加与获取 metadata，不建议使用本接口。
 *      + 本接口支持动态取消注册，将参数设置为 nullptr 取消注册。  <br>
 */
- (BOOL)setMediaMetadataObserver:(_Nullable id<ByteRTCMediaMetadataObserver>) metadataObserver;

/**
 * @type api
 * @region 视频管理
 * @author wangjunlin.3182
 * @brief 在视频通信时，通过视频帧发送 SEI 数据。
 * @param streamIndex 媒体流类型，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param message SEI 消息。长度不超过 4 kB。
 * @param repeatCount 消息发送重复次数。取值范围是 [0, 30]。<br>
 *                    调用此接口后，SEI 数据会添加到当前视频帧开始的连续 `repeatCount` 个视频帧中。
 * @return <br>
 *        + >=0: 将被添加到视频帧中的 SEI 的数量  <br>
 *        + < 0: 发送失败
 * @notes <br>
 *        + 你可以通过此接口对 RTC SDK 内部采集的视频帧添加 SEI。对于采用自定义采集获得的视频帧：如果原视频帧中没有添加 SEI 数据，那么你可以调用此接口为其中添加 SEI 信息后，进行编码传输；如果原视频帧中已添加了 SEI 数据，那么，调用此接口不生效<br>
 *        + 如果调用此接口之后的 2s 内，没有可带 SEI 的视频帧（比如没有开启视频采集和传输），那么，SEI 数据不会被加进视频帧中。<br>
 *        + 消息发送成功后，远端会收到 rtcEngine:onSEIMessageReceived:andMessage:{@link #ByteRTCEngineDelegate#rtcEngine:onSEIMessageReceived:andMessage:} 回调。
 */
- (int)sendSEIMessage:(ByteRTCStreamIndex)streamIndex andMessage:(NSData* _Nonnull)message andRepeatCount:(int)repeatCount;

#pragma mark - VideoFrameObserver InnerVideoSource

/**
 * @hidden
 * @type api
 * @region 视频数据回调
 * @author sunhang.io
 * @brief 注册/取消注册视频数据回调观察者
 * @param frameObserver 视频数据回调的观察者对象，详见： ByteRTCVideoFrameObserver{@link #ByteRTCVideoFrameObserver} 。<br>
 *        将参数设置为 nullptr 取消注册。
 * @return  <br>
 *        + YES： 设置成功 <br>
 *        + NO： 设置失败
 * @notes 该方法可以在任意时间调用，建议在 joinRoomByKey:roomId:userInfo:rtcRoomConfig:{@link #ByteRTCEngineKit#joinRoomByKey:roomId:userInfo:rtcRoomConfig:} 前。
 */
- (BOOL)setVideoFrameObserver:(_Nullable id<ByteRTCVideoFrameObserver>) frameObserver;

/**
 * @type api
 * @region 视频处理
 * @author zhushufan.ref
 * @brief 设置自定义视频前处理器。<br>
 *        使用这个视频前处理器，你能够调用 processVideoFrame:{@link #ByteRTCVideoProcessorDelegate#processVideoFrame:} 对 RTC SDK 采集得到的视频帧进行前处理，并将处理后的视频帧用于 RTC 音视频通信。
 * @param processor 自定义视频处理器，详见 ByteRTCVideoProcessorDelegate{@link #ByteRTCVideoProcessorDelegate}。如果传入 null，则不对 RTC SDK 采集得到的视频帧进行前处理。<br>
 *        SDK 只持有 processor 的弱引用，你应保证其生命周期。<br>
 *        在设计 `processor` 时，应从 ByteRTCVideoFrame{@link #ByteRTCVideoFrame} 的 `textureBuf` 字段获取视频帧数据；<br>
 *        处理后返回的视频帧数据格式应为 ByteRTCVideoPixelFormat{@link #ByteRTCVideoPixelFormat} 中的 `ByteRTCVideoPixelFormatCVPixelBuffer`，且必须存放在返回帧数据的 `textureBuf` 字段中。
 * @param config 自定义视频前处理器适用的设置，详见 ByteRTCVideoPreprocessorConfig{@link #ByteRTCVideoPreprocessorConfig}。<br>
 *               当前，`config` 中的 `required_pixel_format` 仅支持：`ByteRTCVideoPixelFormatI420` 和 `ByteRTCVideoPixelFormatUnknown`：<br>
 *               + 设置为 `UNKNOW` 时，RTC SDK 给出供 processor 处理的视频帧格式即采集的格式。<br>
 *               + 设置为 `ByteRTCVideoPixelFormatI420` 时，RTC SDK 会将采集得到的视频转变为对应的格式，供前处理使用。<br>
 *               + 设置为其他值时，此方法调用失败。
 * @return <br>
 *         + 0：方法调用成功 <br>
 *         + !0：方法调用失败 <br>
 * @notes  <br>
 *        + 重复调用此接口时，仅最后一次调用生效。效果不会叠加。<br>
 *        + 对于 iOS 平台，将 ByteRTCVideoPreprocessorConfig{@link #ByteRTCVideoPreprocessorConfig} 中的 required_pixel_format 设置为 `kVideoPixelFormatUnknown`，可以通过避免格式转换带来一些性能优化。
 */
- (int)registerLocalVideoProcessor:(_Nullable id<ByteRTCVideoProcessorDelegate>) processor
                  withConfig:(ByteRTCVideoPreprocessorConfig* _Nullable)config;

#pragma mark - LocalEncodedVideoFrameObserver
/**
 * @type api
 * @region 视频数据回调
 * @author wangzhanqiang
 * @brief 注册本地视频帧监测器。  <br>
 *        无论使用内部采集还是自定义采集，调用该方法后，SDK 每监测到一帧本地视频帧时，都会将视频帧信息通过 onLocalEncodedVideoFrame:Frame:{@link #ByteRTCLocalEncodedVideoFrameObserver#onLocalEncodedVideoFrame:Frame:} 回调给用户
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
 * @hidden
 * @deprecated from 326.1, use joinRoom with MultiRoomConfig instead
 * @type api
 * @region 房间管理
 * @author shenpengliang
 * @brief 设置房间中音视频流的订阅模式（自动/手动）。默认自动订阅。  <br>
 *        如需开启手动订阅功能，建议在调用 joinRoomByKey:roomId:userInfo:rtcRoomConfig:{@link #ByteRTCEngineKit#joinRoomByKey:roomId:userInfo:rtcRoomConfig:} 方法加入房间前完成设置。  <br>
 * @param audioMode 音频流的订阅模式。参看 ByteRTCSubscribeMode{@link #ByteRTCSubscribeMode} 。  <br>
 * @param videoMode 视频流的订阅模式。参看 ByteRTCSubscribeMode{@link #ByteRTCSubscribeMode} 。  <br>
 * @return 方法执行结果。  <br>
 *         + YES: 方法调用成功。  <br>
 *         + NO: 方法调用失败。  <br>
 * @notes SDK 提供两种订阅模式：<br>
 *          1. 自动订阅模式。开启自动订阅功能时，SDK 自动帮助用户订阅房间中所有其他用户发布的音视频流；<br>
 *          2. 手动订阅模式。关闭自动订阅功能时，用户根据需要调用 subscribeStream:subscribeConfig:{@link #subscribeStream:subscribeConfig:} 方法手动订阅其他用户发布的音视频流。  <br>
 */
- (BOOL)enableAutoSubscribe:(ByteRTCSubscribeMode)audioMode videoMode:(ByteRTCSubscribeMode)videoMode
DEPRECATED_MSG_ATTRIBUTE("Please use joinRoomBykey with roomConfig");

/**
 * @hidden
 * @deprecated from 326.1, use subscribeUserStream instead
 * @type api
 * @region 房间管理
 * @author shenpengliang
 * @brief 订阅指定的房间内远端音视频流。  <br>
 *        关闭自动订阅功能，使用手动订阅模式时,调用此方法按需订阅房间中的音视频流。  <br>
 *        要关闭自动订阅功能，启动手动订阅模式时，你必须在加入房间前调用 enableAutoSubscribe:videoMode:{@link #enableAutoSubscribe:videoMode:}。<br>
 * @param userId 发布远端音视频流的用户 ID 。  <br>
 * @param info 选择订阅配置，详见 ByteRTCSubscribeConfig{@link #ByteRTCSubscribeConfig} 。  <br>
 * @notes <br>
 *        + 订阅流失败时，会受到 rtcEngine:onError:{@link #ByteRTCEngineDelegate#rtcEngine:onError:} 回调。具体错误可参考错误码 ByteRTCErrorCode{@link #ByteRTCErrorCode} <br>
 *        + 如果指定的流在当前房间内不存在，则 SDK 不会订阅。  <br>
 *        + 用户加入房间后，可以根据相关回调获取房间内的音视频流信息，并进行手动订阅：
 *            - 当用户刚加入房间，会收到 rtcEngine:onStreamAdd:{@link #ByteRTCEngineDelegate#rtcEngine:onStreamAdd:} 回调，了解当前房间内已发布的音视频流信息；<br>
 *            - 当房间内有新的音视频流发布/停止发布时，会收到 rtcEngine:onStreamAdd:{@link #ByteRTCEngineDelegate#rtcEngine:onStreamAdd:} 和
 *              rtcEngine:didStreamRemoved:stream:reason:{@link #ByteRTCEngineDelegate#rtcEngine:didStreamRemoved:stream:reason:} 回调
 */
- (void)subscribeStream:(NSString *_Nonnull)userId subscribeConfig:(ByteRTCSubscribeConfig *_Nonnull)info
DEPRECATED_MSG_ATTRIBUTE("Please use subscribeUserStream");

/**
 * @type api
 * @region 房间管理
 * @author shenpengliang
 * @brief 订阅房间内指定的远端音视频流。  <br>
 *        无论是否开启自动订阅，你都可以调用此方法按需订阅房间中的音视频流。  <br>
 *        该方法也可用于更新已经订阅的流的属性、媒体类型等配置。
 * @param userId 指定订阅的远端发布音视频流的用户 ID。  <br>
 * @param streamType 流属性，用于指定订阅主流/屏幕流，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}。  <br>
 * @param mediaType 媒体类型，用于指定订阅音/视频，参看 ByteRTCSubscribeMediaType{@link #ByteRTCSubscribeMediaType}。<br>
 * @param videoConfig 视频订阅配置，参看 ByteRTCSubscribeVideoConfig{@link #ByteRTCSubscribeVideoConfig}。<br>
 * @notes <br>
 *        + 你可以通过 rtcEngine:onStreamAdd:{@link #ByteRTCEngineDelegate#rtcEngine:onStreamAdd:} 和 rtcEngine:didStreamRemoved:stream:reason:{@link #ByteRTCEngineDelegate#rtcEngine:didStreamRemoved:stream:reason:} 两个回调获取当前房间你的音视频流信息，并调用本方法按需订阅流或修改订阅配置。  <br>
 *        + 若订阅失败，你会收到 rtcEngine:onError:{@link #ByteRTCEngineDelegate#rtcEngine:onError:} 回调通知，具体失败原因参看 ByteRTCErrorCode{@link #ByteRTCErrorCode}。
 *        + 若调用 pauseAllSubscribedStream:{@link #ByteRTCEngineKit#pauseAllSubscribedStream:} 暂停接收远端音视频流，此时仍可使用该方法对暂停接收的流进行设置，你会在调用 resumeAllSubscribedStream:{@link #ByteRTCEngineKit#resumeAllSubscribedStream:} 恢复接收流后收到修改设置后的流。  <br>
 */
- (void)subscribeUserStream:(NSString *_Nonnull)userId streamType:(ByteRTCStreamIndex)streamType mediaType:(ByteRTCSubscribeMediaType)mediaType videoConfig:(ByteRTCSubscribeVideoConfig *_Nonnull)videoConfig;

/**
 * @hidden
 * @deprecated from 326.1, use subscribeUserStream instead
 * @type api
 * @region 房间管理
 * @author shenpengliang
 * @brief 停止订阅指定的房间内远端音视频流。  <br>
 *        关闭自动订阅功能，使用手动订阅模式时,调用此方法停止订阅房间中的音视频流。  <br>
 *        要关闭自动订阅功能，启动手动订阅模式时，你必须在加入房间前调用 enableAutoSubscribe:videoMode:{@link #enableAutoSubscribe:videoMode:}。<br>
 * @param userId 发布远端音视频流的用户 ID 。  <br>
 * @param isScreen 订阅的流是否是屏幕共享流。  <br>
 * @notes 不管是否订阅了指定的远端音视频流，都可以调用此方法停止订阅。停止订阅的 userId 无效或未订阅时，SDK 不会做任何处理，没有负面影响。  <br>
 */
- (void)unSubscribeStream:(NSString *_Nonnull)userId isScreen:(BOOL)isScreen
DEPRECATED_MSG_ATTRIBUTE("Please use subscribeUserStream");

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
 * @region 转推直播
 * @author wanghaoxu
 * @brief 开启转推直播，并设置合流的视频视图布局和音频属性。
 * @param transcoding observer
 *        转推直播配置参数，详见 ByteRTCLiveTranscoding{@link #ByteRTCLiveTranscoding}
 * @param observer  端云一体转推直播观察者。  <br>
 *       + 转推直播的状态和方式会通过回调上报 RTC Engine。  <br>
 *       + 只有房间模式为直播模式，且用户角色为主播的用户才能调用此方法。  <br>
 *       + 启用端云一体转推直播时，回调合流完成的音视频流和 SEI 信息给 App。详见 LiveTranscodingDelegate{@link #LiveTranscodingDelegate} 数据类型。
 * @notes  <br>
 *       + 启用服务端转推时，设置 observer 为 null。  <br>
 *       + 只有主播角色的用户才能开启转推直播。<br>
 *       + 调用该方法后，启动结果和推流过程中的错误均会通过回调 rtcEngine:onLiveTranscodingResult:errorCode:{@link #ByteRTCEngineDelegate#rtcEngine:onLiveTranscodingResult:errorCode:} 通知用户。
 */
- (int)startLiveTranscoding:(ByteRTCLiveTranscoding *_Nullable)transcoding observer:(id<LiveTranscodingDelegate> _Nullable)observer;

/**
 * @type api
 * @region 转推直播
 * @brief 停止转推直播。
 * @return 方法调用结果。  <br>
 *         +  0：方法调用成功  <br>
 *         + <0：方法调用失败
 */
- (int)stopLiveTranscoding;

/**
 * @type api
 * @region 转推直播
 * @brief 更新转推直播参数。  <br>
 *        启用转推直播功能后，你可以使用此方法更新转推直播功能配置参数。
 * @param transcoding
 *        视频合流配置参数，详见 ByteRTCLiveTranscoding{@link #ByteRTCLiveTranscoding} 类型。
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
 * @hidden
 * @deprecated 使用 setVideoSourceType 替代
 * @type api
 * @region 视频管理
 * @author zhushufan.ref
 * @brief 配置视频采集源。
 * @param type 视频输入类型，参看 ByteRTCMediaInputType{@link #ByteRTCMediaInputType}。
 * @notes  <br>
 *       + 1. 该方法在进房前后均可以调用。  <br>
 *       + 2. 当你已调用 startVideoCapture{@link #startVideoCapture} 开启内部采集后，再调用此方法切换至自定义采集时，SDK 会自动关闭内部采集。  <br>
 *       + 3. 当你已开启自定义采集后，想要切换至内部采集，你必须先调用此方法指定使用内部采集，然后调用 startVideoCapture{@link #startVideoCapture} 手动开启内部采集。
 */
- (void)setVideoInputType:(ByteRTCMediaInputType)type;

/**
 * @hidden
 * @deprecated
 * @type api
 * @region 视频管理
 * @author zhushufan.ref
 * @brief 切换视频采集方式（内部采集/自定义采集）
 * @param type 视频采集方式，参看 ByteRTCVideoSourceType{@link #ByteRTCVideoSourceType}
 * @notes  <br>
 *       + 默认使用内部采集。内部采集指：使用 RTC SDK 内置的视频采集机制进行视频采集。 <br>
 *       + 该方法进房前后均可调用。  <br>
 *       + 当你已调用 startVideoCapture{@link #ByteRTCEngineKit#startVideoCapture} 开启内部采集后，再调用此方法切换至自定义采集时，SDK 会自动关闭内部采集。  <br>
 *       + 当你调用此方法开启自定义采集后，想要切换至内部采集，你必须先调用此方法关闭自定义采集，然后调用 startVideoCapture{@link #ByteRTCEngineKit#startVideoCapture} 手动开启内部采集。
 */
- (void)setVideoSourceType:(ByteRTCVideoSourceType)type;

/**
 * @type api
 * @region 自定义视频采集渲染
 * @author zhangzhenyu.samuel
 * @brief 推送外部视频帧。
 * @param frame 该视频帧包含待 SDK 编码的视频数据
 * @param pts CMTime
 * @return  <br>
 *         + YES 推送成功  <br>
 *         + NO 推送失败  <br>
 * @notes 推送外部视频帧前，必须调用 setVideoSourceType:WithStreamIndex:{@link #ByteRTCEngineKit#setVideoSourceType:WithStreamIndex:} 开启外部视频源采集。
 */
- (BOOL)pushExternalVideoFrame:(CVPixelBufferRef _Nonnull )frame time:(CMTime)pts;

/**
 * @type api
 * @region 自定义视频采集渲染
 * @author zhangzhenyu.samuel
 * @brief 推送外部视频帧。
 * @param frame 该视频帧包含待 SDK 编码的视频数据
 * @param pts CMTime
 * @param rotation 当前视频角度
 * @return  <br>
 *         + YES 推送成功  <br>
 *         + NO 推送失败  <br>
 * @notes 推送外部视频帧前，必须调用 setVideoSourceType:WithStreamIndex:{@link #ByteRTCEngineKit#setVideoSourceType:WithStreamIndex:} 开启外部视频源采集。
 */
- (BOOL)pushExternalVideoFrame:(CVPixelBufferRef _Nonnull )frame time:(CMTime)pts rotation:(ByteRTCVideoRotation)rotation;

/**
 * @type api
 * @region 自定义视频采集渲染
 * @author zhangzhenyu.samuel
 * @brief 推送外部视频帧。
 * @param frame 该视频帧包含待 SDK 编码的视频数据
 * @param pts CMTime
 * @param rotation 当前视频角度
 * @param extendedData 当前帧的扩展数据，没有的话就传空
 * @param supplementoryInfo 附加信息，比如人脸位置等等
 * @return  <br>
 *         + YES 推送成功  <br>
 *         + NO 推送失败  <br>
 * @notes 推送外部视频帧前，必须调用 setVideoSourceType:WithStreamIndex:{@link #ByteRTCEngineKit#setVideoSourceType:WithStreamIndex:} 开启外部视频源采集。
 */
- (BOOL)pushExternalVideoFrame:(CVPixelBufferRef _Nonnull )frame time:(CMTime)pts
                                                             rotation:(ByteRTCVideoRotation)rotation
                                                         extendedData:(NSData* _Nullable)extendedData
                                                    supplementaryInfo:(NSData* _Nullable)supplementoryInfo;


/**
 * @type api
 * @region 自定义视频采集渲染
 * @author zhangzhenyu.samuel
 * @brief 推送外部视频帧，使用 ByteRTCVideoFrame 进行封装。
 * @param frame 该视频帧包含待 SDK 编码的视频数据，参考 ByteRTCVideoFrame{@link #ByteRTCVideoFrame}
 * @return  <br>
 *         + YES 推送成功  <br>
 *         + NO 推送失败  <br>
 * @notes 推送外部视频帧前，必须调用 setVideoSourceType:WithStreamIndex:{@link #ByteRTCEngineKit#setVideoSourceType:WithStreamIndex:} 开启外部视频源采集。
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
 *      + 启用自定义音频采集渲染的状态在离开房间后仍然有效，会一直持续到调用 disableExternalAudioDevice{@link #disableExternalAudioDevice} 关闭自定义音频采集渲染为止。  <br>
 *      + 启用自定义音频采集渲染后，仍需要使用 pushExternalAudioFrame:{@link #pushExternalAudioFrame:}，推送外部音频数据，再使用 pullExternalAudioFrame:{@link #pullExternalAudioFrame:} 拉取外部音频数据。  <br>
 *      + 使用该方法启用自定义音频采集渲染后，SDK 会自动关闭内部采集使用的音频设备。  <br>
 *      + 当你已调用 startAudioCapture{@link #startAudioCapture} 开启内部采集后，再调用此方法切换至自定义采集时，SDK 会自动关闭内部采集。  <br>
 *      + 当你调用此方法开启自定义采集后，想要切换至内部采集，你必须先调用 disableExternalAudioDevice{@link #disableExternalAudioDevice} 关闭自定义采集，然后调用 startVideoCapture{@link #startVideoCapture} 手动开启内部采集。
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
  * @deprecated from 325.1, use ByteRTCAudioMixingManager instead
  * @hidden
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
  *      + 调用该方法混音的数据来源外部缓存，且音频格式为PCM；startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} 方法混音数据来源外部文件，且支持的文件格式有: mp3，aac，m4a，3gp，wav。这两种混音方式可以共存。  <br>
  *      + enable 为 NO 时，停止外部音频流混音。 或者引擎释放时，SDK内部会停止混音。  <br>
  *      + 该方法启动的外部音频流混音不支持音量调节，暂停，暂停恢复操作。
  */
- (BOOL)setAudioPlayoutMixStream:(BOOL) enable
                    sampleRate:(int) sampleRate
                    channelNum:(int) channelNum
DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCAudioMixingManager");

/**
 * @deprecated from 325.1, use ByteRTCAudioMixingManager instead
 * @hidden
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

- (int)getAudioMixingStreamCachedFrameNum
DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCAudioMixingManager");

 /**
  * @deprecated from 325.1, use ByteRTCAudioMixingManager instead
  * @hidden
  * @type api
  * @region 混音
  * @author wangjunzheng
  * @brief 向SDK推送混音的音频数据
  * @param audioFrame  <br>
  *        PCM音频数据，其格式与 setAudioPlayoutMixStream 保持一致。
  * @param frameNum  <br>
  *        采样点数。若音频采样率为 48000HZ，则单个声道每秒的数据量为 48000 个采样点，10 毫秒的音频数据对应的采样点数为 480 个采样点。
  * @return  <br>
  *       + YES: 成功  <br>
  *       + NO: 失败
  * @notes
  *      + 调用该方法前，必须通过 setAudioPlayoutMixStream 方法设置 audioFrame 的数据格式。  <br>
  *      + 调用该方法前，先通过 getAudioMixingStreamCachedFrameNum 获取缓存的数据量，并调整推送数据的节奏以避免内部缓溢出导致推送失败。  <br>
  *      + 使用参考建议：首次推送数据，请在应用侧先缓存一定数据（如 200 毫秒）， 然后一次性推送过去；此后的推送操作定时 10 毫秒一次，并且每次的音频数据量为 10 毫秒数据量。
  */
- (BOOL)pushAudioMixingStreamData:(void* _Nonnull)audioFrame
                         frameNum:(int)frameNum
DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCAudioMixingManager");

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
 * @notes 使用本方法设置参数，并使用 setAudioFrameObserver:{@link #ByteRTCEngineKit#setAudioFrameObserver:} 注册数据观察者，
 *        之后可以在 ByteRTCAudioFrameObserver{@link #ByteRTCAudioFrameObserver}的
 *        onRecordAudioFrame:{@link #ByteRTCAudioFrameObserver#onRecordAudioFrame:}收到数据
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
 * @notes 使用本方法设置参数，并使用 setAudioFrameObserver:{@link #ByteRTCEngineKit#setAudioFrameObserver:} 注册数据观察者，
 *        之后可以在 ByteRTCAudioFrameObserver{@link #ByteRTCAudioFrameObserver}的
 *        onPlaybackAudioFrame:{@link #ByteRTCAudioFrameObserver#onPlaybackAudioFrame:}收到数据
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
 * @notes 使用本方法设置参数，并使用 setAudioFrameObserver:{@link #ByteRTCEngineKit#setAudioFrameObserver:} 注册数据观察者，
 *        之后可以在 ByteRTCAudioFrameObserver{@link #ByteRTCAudioFrameObserver}的
 *        onMixedAudioFrame:{@link #ByteRTCAudioFrameObserver#onMixedAudioFrame:}收到数据
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
 * @region 音频处理
 * @author majun.lvhiei
 * @brief 设置自定义音频处理器。  <br>
 *        使用该处理器，你可以调用 processAudioFrame:{@link #ByteRTCAudioProcessor#processAudioFrame:} 对 RTC SDK 采集得到的音频帧进行自定义处理，并将处理后的音频帧用于 RTC 音视频通信。  <br>
 *        SDK 只持有 processor 的弱引用，你应保证其生命周期。
 * @param audioProcessor 自定义音频处理器，参看 ByteRTCAudioProcessor{@link #ByteRTCAudioProcessor} 。如果传入null，则不对 RTC SDK 采集得到的音频帧进行自定义处理。
 * @param format 自定义音频参数格式，参看 ByteRTCAudioFormat{@link #ByteRTCAudioFormat}，SDK 将按指定设置给出音频帧。
 * @return  方法调用结果  <br>
 *        + YES: 方法调用成功  <br>
 *        + NO: 方法调用失败
 * @notes 重复调用此接口时，仅最后一次调用生效。效果不会叠加。
 */
- (BOOL)registerLocalAudioProcessor:(_Nullable id<ByteRTCAudioProcessor>) audioProcessor
                             format:(ByteRTCAudioFormat* _Nullable)format;

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
 * @brief 给房间内的所有其他用户发送文本消息。
 * @param message  <br>
 *        发送的文本消息内容  <br>
 *        消息不超过 62KB。
 * @return 这次发送消息的编号，从 1 开始递增。
 * @notes  <br>
 *      + 在房间内广播文本消息前，必须先调用 joinRoomByKey:roomId:userInfo:rtcRoomConfig:{@link #ByteRTCEngineKit#joinRoomByKey:roomId:userInfo:rtcRoomConfig:} 加入房间。  <br>
 *      + 调用该函数后会收到一次 rtcEngine:onRoomMessageSendResult:error:{@link #ByteRTCEngineDelegate#rtcEngine:onRoomMessageSendResult:error:} 回调，通知消息发送方发送成功或失败；  <br>
 *      + 若文本消息发送成功，则房间内所有用户会收到 rtcEngine:onRoomMessageReceived:message:{@link #ByteRTCEngineDelegate#rtcEngine:onRoomMessageReceived:message:} 回调。
 */
- (int)sendRoomMessage:(NSString *  _Nonnull)message;

/**
 * @type api
 * @region 实时消息通信
 * @author hanchenchen.c
 * @brief 给房间内的所有其他用户发送二进制消息。
 * @param message  <br>
 *        用户发送的二进制广播消息  <br>
 *        消息不超过 46KB。
 * @return 这次发送消息的编号，从 1 开始递增。
 * @notes  <br>
 *      + 在房间内广播二进制消息前，必须先调用 joinRoomByKey:roomId:userInfo:rtcRoomConfig:{@link #ByteRTCEngineKit#joinRoomByKey:roomId:userInfo:rtcRoomConfig:} 加入房间。  <br>
 *      + 调用该函数后会收到一次 rtcEngine:onRoomMessageSendResult:error:{@link #ByteRTCEngineDelegate#rtcEngine:onRoomMessageSendResult:error:} 回调，通知消息发送方发送成功或失败；  <br>
 *      + 若二进制消息发送成功，则房间内所有用户会收到 rtcEngine:onRoomBinaryMessageReceived:message:{@link #ByteRTCEngineDelegate#rtcEngine:onRoomBinaryMessageReceived:message:} 回调。
 */
- (int)sendRoomBinaryMessage:(NSData *  _Nonnull)message;

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
 *        + 需要在调用 joinRoomByKey:roomId:userInfo:rtcRoomConfig:{@link #ByteRTCEngineKit#joinRoomByKey:roomId:userInfo:rtcRoomConfig:} 之前调用，
 *           joinRoomByKey:roomId:userInfo:rtcRoomConfig:{@link #ByteRTCEngineKit#joinRoomByKey:roomId:userInfo:rtcRoomConfig:}之后调用该方法无效。
 */
- (int)setBusinessId:(NSString* _Nullable)businessId;

/**
 * @type api
 * @region 引擎管理
 * @author chenweiming.push
 * @brief 通话结束，将用户反馈的问题上报到 RTC <br>
 * @param types 预设问题列表，参看 ByteRTCProblemFeedbackOption{@link #ByteRTCProblemFeedbackOption}  <br>
 * @param desc 预设问题以外的其他问题的具体描述  <br>
 * @return <br>
 *         + 0: 上报成功  <br>
 *         + -1: 上报失败，还没加入过房间 <br>
 *         + -2: 上报失败，数据解析错误  <br>
 *         + -3: 上报失败，字段缺失  <br>
 * @notes 如果用户上报时在房间内，那么问题会定位到用户当前所在的一个或多个房间；
 *        如果用户上报时不在房间内，那么问题会定位到引擎此前退出的房间。
 */
- (int)feedbackTypes:(NSArray* _Nullable)types desc:(NSString* _Nullable)desc;

#pragma mark Monitor Related
/**-----------------------------------------------------------------------------
 * @name 监控相关
 * -----------------------------------------------------------------------------
 */

/**
 * @hidden
 * @deprecated
 * @type api
 * @region 引擎管理
 * @author chenweiming.push
 * @brief 设置设备 ID 。  <br>
 *        监控时可以根据设置的 deviceID 来查找相关信息。必须在 initWithAppId:delegate:parameters:{@link #ByteRTCEngineKit#initWithAppId:delegate:parameters:} 前调用。
 * @param deviceID  <br>
 *        设备 ID 。
 */
+ (void)setDeviceId:(NSString* _Nonnull) deviceID
    __deprecated_msg("Will be removed in new version");

/**
 * @hidden
 * @deprecated
 * @type api
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
 *        + 本函数必须在创建 RtcEngine 实例 initWithAppId:delegate:parameters:{@link #ByteRTCEngineKit#initWithAppId:delegate:parameters:} 前调用。
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
 *        + 必须在创建 RtcEngine 实例 initWithAppId:delegate:parameters:{@link #ByteRTCEngineKit#initWithAppId:delegate:parameters:} 前设置。  <br>
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
 * @brief 给房间内指定的用户发送文本消息（P2P）。
 * @param uid  <br>
 *        消息接收用户的 ID
 * @param message  <br>
 *        发送的文本消息内容。  <br>
 *        消息不超过 62KB。
 * @return 这次发送消息的编号，从 1 开始递增。
 * @notes  <br>
 *      + 在发送房间内文本消息前，必须先调用 joinRoomByKey:roomId:userInfo:rtcRoomConfig:{@link #ByteRTCEngineKit#joinRoomByKey:roomId:userInfo:rtcRoomConfig:} 加入房间。  <br>
 *      + 调用该函数后会收到一次 rtcEngine:onUserMessageSendResult:error:{@link #ByteRTCEngineDelegate#rtcEngine:onUserMessageSendResult:error:} 回调，通知消息发送方发送成功或失败。  <br>
 *      + 若文本消息发送成功，则 uid 所指定的用户会收到 rtcEngine:onUserMessageReceived:message:{@link #ByteRTCEngineDelegate#rtcEngine:onUserMessageReceived:message:} 回调。
 */
- (int64_t)sendUserMessage:(NSString * _Nonnull)uid message:(NSString * _Nonnull)message;

/**
 * @type api
 * @region 实时消息通信
 * @author hanchenchen.c
 * @brief 给房间内指定的用户发送二进制消息（P2P）。
 * @param uid  <br>
 *        消息接收用户的 ID
 * @param message  <br>
 *        发送的二进制消息内容  <br>
 *        消息不超过 46KB。
 * @return 这次发送消息的编号，从 1 开始递增。
 * @notes  <br>
 *      + 在发送房间内二进制消息前，必须先调用 joinRoomByKey:roomId:userInfo:rtcRoomConfig:{@link #ByteRTCEngineKit#joinRoomByKey:roomId:userInfo:rtcRoomConfig:} 加入房间。  <br>
 *      + 调用该函数后会收到一次 rtcEngine:onUserMessageSendResult:error:{@link #ByteRTCEngineDelegate#rtcEngine:onUserMessageSendResult:error:}回调，通知消息发送方发送成功或失败；  <br>
 *      + 若二进制消息发送成功，则 uid 所指定的用户会收到 rtcEngine:onUserBinaryMessageReceived:message:{@link #ByteRTCEngineDelegate#rtcEngine:onUserBinaryMessageReceived:message:}回调。
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
 * @hidden
 * @deprecated from 325.1, use ByteRTCAudioMixingManager instead
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
- (int)getAudioMixingDuration
DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCAudioMixingManager");

/**
 * @hidden
 * @deprecated from 325.1, use ByteRTCAudioMixingManager instead
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
- (int)getAudioMixingCurrentPosition
DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCAudioMixingManager");


/**
 * @hidden
 * @deprecated from 325.1, use ByteRTCAudioMixingManager instead
 * @type api
 * @region 混音
 * @author wangjunzheng
 * @brief 停止播放音乐文件及混音
 * @return  <br>
 *       + 0：成功
 *       + <0：失败
 * @notes  <br>
 *      + 调用 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} 方法开始播放音乐文件及混音后，调用该方法可以停止播放音乐文件及混音。  <br>
 *      + 请在房间内调用该方法。
 */
- (int)stopAudioMixing
DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCAudioMixingManager");

/**
 * @hidden
 * @deprecated from 325.1, use ByteRTCAudioMixingManager instead
 * @type api
 * @region 混音
 * @author wangjunzheng
 * @brief 暂停播放音乐文件
 * @return  <br>
 *        + 0: 成功  <br>
 *        + <0: 失败
 * @notes  <br>
 *      + 调用 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} 方法开始播放音乐文件及混音后，可以通过调用该方法暂停播放音乐文件。  <br>
 *      + 调用该方法暂停播放音乐文件后，可调用 resumeAudioMixing:{@link #ByteRTCAudioMixingManager#resumeAudioMixing:} 方法恢复播放。  <br>
 *      + 请在房间内调用该方法。
 */
- (int)pauseAudioMixing
DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCAudioMixingManager");

/**
 * @hidden
 * @deprecated from 325.1, use ByteRTCAudioMixingManager instead
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
- (int)resumeAudioMixing
DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCAudioMixingManager");

/**
 * @hidden
 * @deprecated from 325.1, use ByteRTCAudioMixingManager instead
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
- (int)adjustAudioMixingVolume:(NSInteger)volume
DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCAudioMixingManager");

/**
 * @hidden
 * @deprecated from 325.1, use ByteRTCAudioMixingManager instead
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
 *      + 该方法可以选择是否让对方听到本地播放的音频，并指定循环播放的次数。 调用本方法播放音乐文件及混音结束后，应用会收到 rtcEngineLocalAudioMixingDidFinish:{@link #ByteRTCEngineDelegate#rtcEngineLocalAudioMixingDidFinish:} 回调。  <br>
 *      + 开始播放音乐文件及混音后，可以调用 stopAudioMixing{@link #stopAudioMixing} 方法停止播放音乐文件。  <br>
 *      + 该方法混音数据来源外部文件，且支持的文件格式有: mp3，aac，m4a，3gp，wav；而 setAudioPlayoutMixStream 混音的数据来源外部缓存且音频格式为PCM；这两种混音方式可以共存。  <br>
 *      + 单个房间只支持一路音乐文件的播放，多次调用该函数后，只有最后一次调用会生效。  <br>
 *      + 请在房间内调用该方法。
 */
- (int)startAudioMixing:(NSString *  _Nonnull)filePath
               loopback:(BOOL)loopback
                replace:(BOOL)replace
                  cycle:(NSInteger)cycle
DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCAudioMixingManager");

/**
 * @hidden
 * @deprecated from 325.1, use ByteRTCAudioMixingManager instead
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
- (int)setAudioMixingPosition:(NSInteger)pos
DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCAudioMixingManager");

/**
 * @hidden
 * @deprecated from 325.1, use ByteRTCAudioMixingManager instead
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
- (int)adjustAudioMixingPlayoutVolume:(NSInteger)volume
DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCAudioMixingManager");

/**
 * @hidden
 * @deprecated from 325.1, use ByteRTCAudioMixingManager instead
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
- (int)adjustAudioMixingPublishVolume:(NSInteger)volume
DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCAudioMixingManager");

/**
 * @hidden
 * @deprecated from 325.1, use ByteRTCAudioMixingManager instead
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
              withVolume:(NSInteger)volume
DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCAudioMixingManager");

/**
 * @hidden
 * @deprecated from 325.1, use ByteRTCAudioMixingManager instead
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
- (int)getEffectVolume:(NSInteger)soundId
DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCAudioMixingManager");

/**
 * @hidden
 * @deprecated from 325.1, use ByteRTCAudioMixingManager instead
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
 *      + 调用该方法播放音效结束后，应用会收到 rtcEngineLocalAudioMixingDidFinish:{@link #ByteRTCEngineDelegate#rtcEngineLocalAudioMixingDidFinish:} 回调。
 *      + 可以多次调用该方法，通过传入不同的音效文件的 soundId 和 filePath，以实现同时播放多个音效文件，实现音效叠加。
 *      + 可以通过 stopEffect:{@link #stopEffect:} 方法停止播放指定音效文件。
 *      + 请在房间内调用该方法。
 */
- (int)playEffect:(NSInteger)soundId
         filePath:(NSString * _Nullable)filePath
         loopback:(BOOL)loopback
            cycle:(NSInteger)cycle
       withVolume:(NSInteger)volume
DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCAudioMixingManager");

/**
 * @hidden
 * @deprecated from 325.1, use ByteRTCAudioMixingManager instead
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
- (int)preloadEffect:(NSInteger)soundId filePath:(NSString * _Nullable)filePath
DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCAudioMixingManager");

/**
 * @hidden
 * @deprecated from 325.1, use ByteRTCAudioMixingManager instead
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
- (int)unloadEffect:(NSInteger)soundId
DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCAudioMixingManager");

/**
 * @hidden
 * @deprecated from 325.1, use ByteRTCAudioMixingManager instead
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
- (int)pauseEffect:(NSInteger)soundId
DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCAudioMixingManager");

/**
 * @hidden
 * @deprecated from 325.1, use ByteRTCAudioMixingManager instead
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
- (int)resumeEffect:(NSInteger)soundId
DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCAudioMixingManager");

/**
 * @hidden
 * @deprecated from 325.1, use ByteRTCAudioMixingManager instead
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
- (int)stopEffect:(NSInteger)soundId
DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCAudioMixingManager");

/**
 * @hidden
 * @deprecated
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
- (int)setEffectsVolume:(NSInteger)volume
DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCAudioMixingManager");

/**
 * @hidden
 * @deprecated from 325.1, use ByteRTCAudioMixingManager instead
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
- (int)unloadAllEffects
DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCAudioMixingManager");


/**
 * @hidden
 * @deprecated from 325.1, use ByteRTCAudioMixingManager instead
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
- (int)pauseAllEffects
DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCAudioMixingManager");

/**
 * @hidden
 * @deprecated
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
- (int)resumeAllEffects
DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCAudioMixingManager");

 /**
  * @hidden
  * @deprecated from 325.1, use ByteRTCAudioMixingManager instead
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
- (int)stopAllEffects
DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCAudioMixingManager");

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
 *        + 设置回退选项后，本端订阅的音视频流发生回退或从回退中恢复时,会收到 rtcEngine:OnSimulcastSubscribeFallback:{@link #ByteRTCEngineDelegate#rtcEngine:OnSimulcastSubscribeFallback:} 回调通知。  <br>
 *        + 设置回退选项后，本端订阅的视频流因为回退分辨率发生变化时,会收到 rtcEngine:onRemoteVideoSizeChanged:withFrameInfo:{@link #ByteRTCEngineDelegate#rtcEngine:onRemoteVideoSizeChanged:withFrameInfo:}
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
 * @author wangjunlin.3182
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
 * @author wangjunlin.3182
 * @brief 设置自定义加密和解密方式
 *        需要实现对应的加密和解密方法。详情参考 ByteRTCEncryptHandler{@link #ByteRTCEncryptHandler}  <br>
 * @param handler  <br>
 *        自定义加密 handler，需要实现里面的加密和解密方法  <br>
 * @notes
 *       + 该方法与 setEncryptType:key:{@link #setEncryptType:key:} 为互斥关系,
 *         即按照调用顺序，最后一个调用的方法为最终生效的版本  <br>
 *       + 该方法必须在调用 joinRoomByKey:roomId:userInfo:rtcRoomConfig:{@link #ByteRTCEngineKit#joinRoomByKey:roomId:userInfo:rtcRoomConfig:}
 * 之前调用，可重复调用，以最后调用的参数作为生效参数  <br>
 *       + 无论加密或者解密，其对原始数据的长度修改，需要控制在90%-120%之间，即如果输入数据为100字节，则处理完成后的数据必须在
 *         90至120字节之间，如果加密或解密结果超出该长度限制，则该音视频桢会被丢弃  <br>
 *       + 数据加密/解密为串行执行，因而视实现方式不同，可能会影响到最终渲染效率，是否使用该方法，需要由使用方谨慎评估  <br>
 */
- (void)setCustomizeEncryptHandler:(id<ByteRTCEncryptHandler> _Nullable)handler;

#pragma mark - Extention Methods

/**
 * @type api
 * @region 多房间
 * @author shenpengliang
 * @brief 创建并获取一个 ByteRTCRoom 对象  <br>
 * @param roomId 标识通话房间的房间 ID，最大长度为 128 字节的非空字符串。支持的字符集范围为:  <br>
 *       + 26 个大写字母 A ~ Z  <br>
 *       + 26 个小写字母 a ~ z  <br>
 *       + 10 个数字 0 ~ 9  <br>
 *       + 下划线 "_", at 符 "@", 减号 "-"  <br>
 *        多房间模式下，调用创建房间接口后，请勿调用同样的 roomID 创建房间，否则会导致创建房间失败。  <br>
 * @notes <br>
 *       + 用户可以多次调用此方法创建多个 ByteRTCRoom 对象，再分别调用各 ByteRTCRoom 对象的 joinRoomByToken:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoomByToken:userInfo:roomConfig:} 方法，实现同时加入多个房间；  <br>
 *       + 加入多个房间后，用户可以同时订阅各房间的音视频流，但是目前仅支持同一时间在一个房间内发布一路音视频流。  <br>
 */
- (ByteRTCRoom * _Nullable)createRtcRoom:(NSString * _Nonnull)roomId;


#pragma mark - ScreenCapture
/**
 * @hidden
 * @deprecated from 327.1, use startScreenSharingWithPreferredExtension instead
 * @type api
 * @region 屏幕共享
 * @author liyi.000
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
 *        3.调用该接口后远端能收到 rtcEngine:onFirstRemoteVideoFrameRendered:withFrameInfo:{@link #ByteRTCEngineDelegate#rtcEngine:onFirstRemoteVideoFrameRendered:withFrameInfo:} 和 rtcEngine:onStreamAdd:{@link #ByteRTCEngineDelegate#rtcEngine:onStreamAdd:} 事件。
 */
- (int)setScreenCapture:(BOOL)enable Rect:(CGRect)rect screenCaptureParam:(ByteRTCScreenCaptureParam * _Nonnull)param;

/**
 * @type api
 * @region 屏幕共享
 * @author liyi.000
 * @brief 发布本地屏幕共享流。
 * @notes  <br>
 *       + 直播、游戏、云游戏房间模式下，仅可见的用户可以调用此方法。你可以调用 setUserVisibility:{@link #ByteRTCEngineKit#setUserVisibility:} 方法设置用户在房间中的可见性。  <br>
 *       + 此方法只影响屏幕共享视频流的发布状态，并不影响屏幕视频流的采集情况。<br>
 *       + 发布成功后，远端会收到 rtcEngine:onStreamAdd:{@link #ByteRTCEngineDelegate#rtcEngine:onStreamAdd:} 回调。<br>
 *       + 调用 unpublishScreen{@link #ByteRTCEngineKit#unpublishScreen} 取消发布。
 */
- (void)publishScreen;

/**
 * @type api
 * @region 屏幕共享
 * @author liyi.000
 * @brief 取消发布屏幕流
 * @notes  <br>
 *       + 此方法只影响屏幕共享视频流的发布状态，并不影响屏幕视频流的采集情况。<br>
 *       + 调用成功后，远端会收到 rtcEngine:didStreamRemoved:stream:reason:{@link #ByteRTCEngineDelegate#rtcEngine:didStreamRemoved:stream:reason:} 回调。<br>
 *       + 调用 publishScreen{@link #ByteRTCEngineKit#publishScreen} 启动发布。
 */
- (void)unpublishScreen;

/**
 * @type api
 * @region 屏幕共享
 * @author liyi.000
 * @brief 推送外部屏幕采集帧
 * @param frame 该视频帧包含待 SDK 编码的视频数据
 * @param pts 每一帧的时间戳，单位 ms
 * @param rotation 帧的旋转角度包含: 0, 90, 180, 270
 * @notes 屏幕采集分为内部采集和外部采集，本方法属于外部采集。
 */
- (void)pushScreenCaptureFrame:(CVPixelBufferRef _Nonnull )frame time:(CMTime)pts rotation:(int)rotation;

/**
 * @type api
 * @region 屏幕共享
 * @author liyi.000
 * @brief 开始内部屏幕采集
 * @param extension 传入 Broadcast Upload Extension 的 Bundle Id，用于在设置中优先展示 Extension
 * @param groupId App 和 Extension 应该归属于同一个 App Group，此处需要传入 Group Id。
 * @return 0 :成功;
 *        -1 :失败;
 * @notes
 *        1.屏幕采集分为内部采集和外部采集，本方法属于内部采集。
 *        内部采集：由 SDK 进行屏幕采集和后续所有流程
 *        外部采集：用户负责采集屏幕数据帧，通过接口提供给 SDK
 *        2.调用该接口后远端能收到 rtcEngine:onFirstRemoteVideoFrameRendered:withFrameInfo:{@link #ByteRTCEngineDelegate#rtcEngine:onFirstRemoteVideoFrameRendered:withFrameInfo:} 和 rtcEngine:onStreamAdd:{@link #ByteRTCEngineDelegate#rtcEngine:onStreamAdd:} 事件。
 *        3.内部采集时，外部不需要屏幕采集帧。
 */
- (int)startScreenSharingWithPreferredExtension:(NSString *_Nullable)extension groupId:(NSString *_Nonnull)groupId API_AVAILABLE(ios(12));

/**
 * @type api
 * @region 屏幕共享
 * @author liyi.000
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
 * @param parameters 保留参数
 */
- (void)setRuntimeParameters:(NSDictionary * _Nullable)parameters;

#pragma mark - ASR
/**
 * @type api
 * @region 语音识别服务
 * @author wangjunzheng
 * @brief 开启自动语音识别服务。该方法将识别后的用户语音转化成文字，并通过 onMessage:{@link #ByteRTCASREngineEventHandler#onMessage:} 事件回调给用户。
 * @param handler 语音识别服务使用状态回调，参看 ByteRTCASREngineEventHandler{@link #ByteRTCASREngineEventHandler}
 * @param asrConfig 校验信息，参看 ByteRTCASRConfig{@link #ByteRTCASRConfig}
 */
- (void)startASR:(ByteRTCASRConfig *_Nonnull)asrConfig handler:(id<ByteRTCASREngineEventHandler> _Nonnull)handler ;
/**
 * @type api
 * @region 语音识别服务
 * @author wangjunzheng
 * @brief 关闭语音识别服务
 */
- (void)stopASR;

#pragma mark - FileRecording
/**
 * @type api
 * @region 本地录制
 * @author wunailiang
 * @brief 该方法将通话过程中的音视频数据录制到本地的文件中。
 * @param streamIndex 流属性，指定录制主流还是屏幕流，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param recordingConfig 本地录制参数配置，参看 ByteRTCRecordingConfig{@link #ByteRTCRecordingConfig}
 * @return   <br>
 *        + 0: 正常
 *        + -1: 参数设置异常
 *        + -2: 当前版本 SDK 不支持该特性，请联系技术支持人员
 * @notes  <br>
 *        + 调用该方法后，你会收到 rtcEngine:onRecordingStateUpdate:state:error_code:recording_info:{@link #ByteRTCEngineDelegate#rtcEngine:onRecordingStateUpdate:state:error_code:recording_info:} 回调。  <br>
 *        + 如果录制正常，系统每秒钟会通过 rtcEngine:onRecordingProgressUpdate:process:recording_info:{@link #ByteRTCEngineDelegate#rtcEngine:onRecordingProgressUpdate:process:recording_info:} 回调通知录制进度。
 */
- (int)startFileRecording:(ByteRTCStreamIndex)streamIndex
        withRecordingConfig:(ByteRTCRecordingConfig* _Nonnull)recordingConfig;

/**
 * @type api
 * @region 本地录制
 * @author wunailiang
 * @brief 停止本地录制
 * @param streamIndex 流属性，指定停止主流或者屏幕流录制，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @notes  <br>
 *        + 调用 startFileRecording:withRecordingConfig:{@link #ByteRTCEngineKit#startFileRecording:withRecordingConfig:} 开启本地录制后，你必须调用该方法停止录制。  <br>
 *        + 调用该方法后，你会收到 rtcEngine:onRecordingStateUpdate:state:error_code:recording_info:{@link #ByteRTCEngineDelegate#rtcEngine:onRecordingStateUpdate:state:error_code:recording_info:} 回调提示录制结果。
 */
- (void)stopFileRecording:(ByteRTCStreamIndex)streamIndex;

/**
  * @type api
  * @region 混音
  * @author wangjunzheng
  * @brief 混音管理接口创建
  * @return 混音管理实例，详见ByteRTCAudioMixingManager{@link #ByteRTCAudioMixingManager}
  */
- (ByteRTCAudioMixingManager *_Nullable)getAudioMixingManager;

/**
 * @type api
 * @region 音频管理
 * @author majun.lvhiei
 * @brief 获取位置音频接口实例，包括范围语音、空间语音等和位置相关的音频接口。  <br>
 * @return 位置音频管理接口实例。如果返回 NULL，则表示不支持空间音频，详见 ByteRTCPositionAudioRender{@link #ByteRTCPositionAudioRender} 。  <br>
 * @notes  <br>
 *       + 只有在使用支持真双声道播放的设备时，才能开启空间音频效果；  <br>
 *       + 在网络状况不佳的情况下，即使开启了这一功能，也不会产生空间音频效果；  <br>
 *       + 机型性能不足可能会导致音频卡顿，使用低端机时，不建议开启空间音频效果；  <br>
 *       + 空间音频效果在启用服务端选路功能时，不生效。  <br> 
 */
- (ByteRTCPositionAudioRender *_Nullable)getPositionAudioRender;

#pragma mark - Rtm
/**
 * @type api
 * @region 实时消息通信
 * @author hanchenchen.c
 * @brief 必须先登录注册一个 uid，才能发送房间外消息和向业务服务器发送消息
 * @param token  <br>
 *        动态密钥  <br>
 *        用户登录必须携带的 Token，用于鉴权验证。  <br>
 *        本 Token 与加入房间时必须携带的 Token 不同。测试时可使用控制台生成临时 Token，正式上线需要使用密钥 SDK 在你的服务端生成并下发 Token。
 * @param uid  <br>
 *        用户 ID  <br>
 *        用户 ID 在 appid的维度下是唯一的。
 * @notes  <br>
 *       + 在调用本接口登录后，如果想要登出，需要调用 logout{@link #ByteRTCEngineKit#logout} 登出后，才能再次登录。  <br>
 *       + 本地用户调用此方法登录后，会收到 rtcEngine:onLoginResult:errorCode:elapsed:{@link #ByteRTCEngineDelegate#rtcEngine:onLoginResult:errorCode:elapsed:} 回调通知登录结果，远端用户不会收到通知。
 */
- (void)login:(NSString * _Nonnull)token uid:(NSString * _Nonnull)uid;
/**
 * @type api
 * @region 实时消息通信
 * @author hanchenchen.c
 * @brief 调用本接口登出后，无法调用房间外消息以及端到服务器消息相关的方法或收到相关回调。
 * @notes  <br>
 *       + 调用本接口登出前，必须先调用 login:uid:{@link #ByteRTCEngineKit#login:uid:} 登录  <br>
 *       + 本地用户调用此方法登出后，会收到 rtcEngineOnLogout:{@link #ByteRTCEngineDelegate#rtcEngineOnLogout:}  回调通知结果，远端用户不会收到通知。
 */
- (void)logout;
/**
 * @type api
 * @region 实时消息通信
 * @author hanchenchen.c
 * @brief 更新用户用于登录的 Token  <br>
 *        Token 有一定的有效期，当 Token 过期时，需调用此方法更新登录的 Token 信息。  <br>
 *        调用 login:uid:{@link #ByteRTCEngineKit#login:uid:} 方法登录时，如果使用了过期的 Token 将导致登录失败，并会收到 rtcEngine:onLoginResult:errorCode:elapsed:{@link #ByteRTCEngineDelegate#rtcEngine:onLoginResult:errorCode:elapsed:} 回调通知，错误码为 ByteRTCLoginErrorCodeInvalidToken。此时需要重新获取 Token，并调用此方法更新 Token。
 * @param token  <br>
 *        更新的动态密钥  <br>
 * @notes  <br>
 *       + 如果 Token 无效导致登录失败，则调用此方法更新 Token 后，SDK 会自动重新登录，而用户不需要自己调用 login:uid:{@link #ByteRTCEngineKit#login:uid:} 方法。  <br>
 *       + Token 过期时，如果已经成功登录，则不会受到影响。Token 过期的错误会在下一次使用过期 Token 登录时，或因本地网络状况不佳导致断网重新登录时通知给用户。
 */
- (void)updateLoginToken:(NSString * _Nonnull)token;
/**
 * @type api
 * @region 实时消息通信
 * @author hanchenchen.c
 * @brief 设置业务服务器参数  <br>
 *        客户端调用 sendServerMessage:{@link #ByteRTCEngineKit#sendServerMessage:} 或 sendServerBinaryMessage:{@link #ByteRTCEngineKit#sendServerBinaryMessage:} 发送消息给业务服务器之前，必须需要设置有效签名和业务服务器地址。
 * @param signature  <br>
 *        动态签名  <br>
 *        业务服务器会使用该签名对请求进行鉴权验证。  <br>
 * @param url  <br>
 *        业务服务器的地址
 * @notes  <br>
 *       + 用户必须调用 login:uid:{@link #ByteRTCEngineKit#login:uid:} 登录后，才能调用本接口。  <br>
 *       + 调用本接口后，SDK 会使用 rtcEngine:onServerParamsSetResult:{@link #ByteRTCEngineDelegate#rtcEngine:onServerParamsSetResult:} 返回相应结果。
 */
- (void)setServerParams:(NSString * _Nonnull)signature url:(NSString * _Nonnull)url;
/**
 * @type api
 * @region 实时消息通信
 * @author hanchenchen.c
 * @brief 查询对端用户或本端用户的登录状态
 * @param peerUserId  <br>
 *        需要查询的用户 ID
 * @notes  <br>
 *       + 必须调用 login:uid:{@link #ByteRTCEngineKit#login:uid:} 登录后，才能调用本接口。  <br>
 *       + 调用本接口后，SDK 会使用 rtcEngine:onGetPeerOnlineStatus:status:{@link #ByteRTCEngineDelegate#rtcEngine:onGetPeerOnlineStatus:status:} 回调通知查询结果。  <br>
 *       + 在发送房间外消息之前，用户可以通过本接口了解对端用户是否登录，从而决定是否发送消息。也可以通过本接口查询自己查看自己的登录状态。
 */
- (void)getPeerOnlineStatus:(NSString * _Nonnull)peerUserId;
/**
 * @type api
 * @region 实时消息通信
 * @author hanchenchen.c
 * @brief 给房间外指定的用户发送文本消息（P2P）
 * @param userId  <br>
 *        消息接收用户的 ID
 * @param messageStr  <br>
 *        发送的文本消息内容  <br>
 *        消息不超过 62KB。
 * @return  <br>
 *        + >0：发送成功，返回这次发送消息的编号，从 1 开始递增  <br>
 *        + -1：发送失败，RtcEngine 实例未创建  <br>
 *        + -2：发送失败，userId 为空
 * @notes  <br>
 *       + 在发送房间外文本消息前，必须先调用 login:uid:{@link #ByteRTCEngineKit#login:uid:} 完成登录。  <br>
 *       + 用户调用本接口发送文本信息后，会收到一次 rtcEngine:onUserMessageSendResultOutsideRoom:error:{@link #ByteRTCEngineDelegate#rtcEngine:onUserMessageSendResultOutsideRoom:error:} 回调，得知消息是否成功发送；  <br>
 *       + 若文本消息发送成功，则 userId 所指定的用户会通过 rtcEngine:onUserMessageReceivedOutsideRoom:message:{@link #ByteRTCEngineDelegate#rtcEngine:onUserMessageReceivedOutsideRoom:message:} 回调收到该消息。
 */
- (int64_t)sendUserMessageOutsideRoom:(NSString * _Nonnull)userId message:(NSString * _Nonnull)messageStr;
/**
 * @type api
 * @region 实时消息通信
 * @author hanchenchen.c
 * @brief 给房间外指定的用户发送二进制消息（P2P）
 * @param userId  <br>
 *        消息接收用户的 ID
 * @param messageStr  <br>
 *        发送的二进制消息内容  <br>
 *        消息不超过 46KB。
 * @return  <br>
 *        + >0：发送成功，返回这次发送消息的编号，从 1 开始递增  <br>
 *        + -1：发送失败，RtcEngine 实例未创建  <br>
 *        + -2：发送失败，userId 为空
 * @notes  <br>
 *       + 在发送房间外二进制消息前，必须先调用 login:uid:{@link #ByteRTCEngineKit#login:uid:} 完成登录。  <br>
 *       + 用户调用本接口发送二进制消息后，会收到一次 rtcEngine:onUserMessageSendResultOutsideRoom:error:{@link #ByteRTCEngineDelegate#rtcEngine:onUserMessageSendResultOutsideRoom:error:} 回调，通知消息是否发送成功；  <br>
 *       + 若二进制消息发送成功，则 userId 所指定的用户会通过 rtcEngine:onUserBinaryMessageReceivedOutsideRoom:message:{@link #ByteRTCEngineDelegate#rtcEngine:onUserBinaryMessageReceivedOutsideRoom:message:}  回调收到该条消息。
 */
- (int64_t)sendUserBinaryMessageOutsideRoom:(NSString * _Nonnull)userId message:(NSData * _Nonnull)messageStr;
/**
 * @type api
 * @region 实时消息通信
 * @author hanchenchen.c
 * @brief 客户端给业务服务器发送文本消息（P2Server）
 * @param messageStr  <br>
 *        发送的文本消息内容  <br>
 *        消息不超过 62KB。
 * @return  <br>
 *        + >0：发送成功，返回这次发送消息的编号，从 1 开始递增  <br>
 *        + -1：发送失败，RtcEngine 实例未创建
 * @notes  <br>
 *       + 在向业务服务器发送文本消息前，必须先调用 login:uid:{@link #ByteRTCEngineKit#login:uid:} 完成登录，随后调用 setServerParams:url:{@link #ByteRTCEngineKit#setServerParams:url:} 设置业务服务器。  <br>
 *       + 调用本接口后，会收到一次 rtcEngine:onServerMessageSendResult:error:{@link #ByteRTCEngineDelegate#rtcEngine:onServerMessageSendResult:error:} 回调，通知消息发送方是否发送成功。  <br>
 *       + 若文本消息发送成功，则之前调用 setServerParams:url:{@link #ByteRTCEngineKit#setServerParams:url:} 设置的业务服务器会收到该条消息。
 */
- (int64_t)sendServerMessage:(NSString * _Nonnull)messageStr;
/**
 * @type api
 * @region 实时消息通信
 * @author hanchenchen.c
 * @brief 客户端给业务服务器发送二进制消息（P2Server）
 * @param messageStr  <br>
 *        发送的二进制消息内容  <br>
 *        消息不超过 46KB。
 * @return  <br>
 *        + >0：发送成功，返回这次发送消息的编号，从 1 开始递增  <br>
 *        + -1：发送失败，RtcEngine 实例未创建
 * @notes  <br>
 *       + 在向业务服务器发送二进制消息前，先调用 login:uid:{@link #ByteRTCEngineKit#login:uid:} 完成登录，随后调用 setServerParams:url:{@link #ByteRTCEngineKit#setServerParams:url:} 设置业务服务器。  <br>
 *       + 调用本接口后，会收到一次 rtcEngine:onServerMessageSendResult:error:{@link #ByteRTCEngineDelegate#rtcEngine:onServerMessageSendResult:error:} 回调，通知消息发送方发送成功或失败；  <br>
 *       + 若二进制消息发送成功，则之前调用 setServerParams:url:{@link #ByteRTCEngineKit#setServerParams:url:} 设置的业务服务器会收到该条消息。
 */
- (int64_t)sendServerBinaryMessage:(NSData * _Nonnull)messageStr;

#pragma mark  ScreenAudio

/**
 * @type api
 * @region 屏幕共享
 * @author wangjunzheng
 * @brief 在屏幕共享时，设置屏幕音频的采集方式（内部采集/自定义采集）
 * @param sourceType 屏幕音频输入源类型, 参看 ByteRTCAudioSourceType{@link #ByteRTCAudioSourceType}
 * @notes  <br>
 *      + 默认采集方式是 RTC SDK 内部采集。当前不支持使用内部采集，请调用此方法，设置为使用自定义采集。<br>
 *      + 你应该在 publishScreen{@link #ByteRTCEngineKit#publishScreen} 前，调用此方法。否则，你将收到 rtcEngine:onWarning:{@link #ByteRTCEngineDelegate#rtcEngine:onWarning:} 的报错：`ByteRTCWarningSetScreenAudioSourceTypeFailed` <br>
 *      + 如果设定为自定义采集，你必须再调用 publishScreen{@link #ByteRTCEngineKit#publishScreen} 将自定义采集到的屏幕音频帧推送到 RTC SDK。<br>
 *      + 无论是内部采集还是自定义采集，你都必须调用 publishScreen{@link #ByteRTCEngineKit#publishScreen} 将采集到的屏幕音频推送到远端。
 */
- (void) setScreenAudioSourceType:(ByteRTCAudioSourceType)sourceType;

/**
 * @type api
 * @region 屏幕共享
 * @author wangjunzheng
 * @brief 在屏幕共享时，设置屏幕音频流和麦克风采集到的音频流的混流方式
 * @param index 混流方式，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex} <br>
 *        + `ByteRTCStreamIndexMain`: 将屏幕音频流和麦克风采集到的音频流混流 <br>
 *        + `ByteRTCStreamIndexScreen`: 将屏幕音频流和麦克风采集到的音频流分为两路音频流
 * @notes 你应该在 publishScreen{@link #ByteRTCEngineKit#publishScreen} 之前，调用此方法。否则，你将收到 rtcEngine:onWarning:{@link #rtcEngine:onWarning:} 的报错：`ByteRTCWarningSetScreenAudioStreamIndexFailed`
 */
- (void) setScreenAudioStreamIndex:(ByteRTCStreamIndex) index;

/**
 * @hidden
 * @type api
 * @region 屏幕共享
 * @author wangjunzheng
 * @brief 在屏幕共享时，开始使用 RTC SDK 内部采集方式，采集屏幕音频
 * @notes <br>
 *        + 采集后，你还需要调用 PublishScreen{@link #IRtcRoom#PublishScreen} 将采集到的屏幕音频推送到远端。<br>
 *        + 要关闭屏幕音频内部采集，调用 StopScreenAudioCapture{@link #IRtcEngineLite#StopScreenAudioCapture}。<br>
 *        + 此接口暂不支持。
 */
- (void) startScreenAudioCapture;

 /**
 * @hidden
 * @type api
 * @region 屏幕共享
 * @author wangjunzheng
 * @brief 在屏幕共享时，停止使用 RTC SDK 内部采集方式，采集屏幕音频。
 * @notes <br>
 *      + 要开始屏幕音频内部采集，调用 StartScreenAudioCapture{@link #IRtcEngineLite#StartScreenAudioCapture}。<br>
 *      + 此接口暂不支持。
 */
- (void) stopScreenAudioCapture;

/**
 * @type api
 * @region 屏幕共享
 * @author wangjunzheng
 * @brief 使用自定义采集方式，采集屏幕共享时的屏幕音频时，将音频帧推送至 RTC SDK 处进行编码等处理。
 * @param audioFrame 音频数据帧，参见 ByteRTCAudioFrame{@link #ByteRTCAudioFrame}
 * @return 方法调用结果  <br>
 *        + 0: 设置成功  <br>
 *        + <0: 设置失败  <br>
 * @notes  <br>
 *        + 调用此接口推送屏幕共享时的自定义采集的音频数据前，必须调用 setScreenAudioSourceType:{@link #setScreenAudioSourceType:} 开启屏幕音频自定义采集。  <br>
 *        + 你应每隔 10 毫秒，调用一次此方法推送一次自定义采集的音频帧。一次推送的音频帧中应包含 frame.sample_rate / 100 个音频采样点。比如，假如采样率为 48000Hz，则每次应该推送 480 个采样点。  <br>
 *        + 音频采样格式为 S16。音频缓冲区内的数据格式必须为 PCM 数据，其容量大小应该为 samples * frame.channel * 2。  <br>
 *        + 此函数运行在用户级线程内。若同时运行其他进程，将导致本进程中断。  <br>
 *        + 调用此接口将自定义采集的音频帧推送到 RTC SDK 后，你必须调用 publishScreen{@link #publishScreen} 将采集到的屏幕音频推送到远端。在调用 publishScreen{@link #publishScreen} 前，推送到 RTC SDK 的音频帧信息会丢失。
 */
- (int) pushScreenAudioFrame:(ByteRTCAudioFrame* _Nonnull)audioFrame;

#pragma mark EncodedVideo
/**
 * @type api
 * @region 视频管理
 * @author wangzhanqiang
 * @brief 设置向 SDK 输入的视频源
 * @param type 视频输入源类型，参看 ByteRTCVideoSourceType{@link #ByteRTCVideoSourceType}
 * @param streamIndex 视频流的属性，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @notes  <br>
 *        + 默认使用内部采集。内部采集指：使用 RTC SDK 内置的视频采集机制进行视频采集。 <br>
 *        + 该方法进房前后均可调用。  <br>
 *        + 当你已调用 startVideoCapture{@link #ByteRTCEngineKit#startVideoCapture} 开启内部采集后，再调用此方法切换至自定义采集时，SDK 会自动关闭内部采集。  <br>
 *        + 当你调用此方法开启自定义采集后，想要切换至内部采集，你必须先调用此方法关闭自定义采集，然后调用 startVideoCapture{@link #ByteRTCEngineKit#startVideoCapture} 手动开启内部采集。
 *        + 当你需要向 SDK 推送自定义编码后的视频帧，你需调用该方法将视频源切换至自定义编码视频源。
 */
- (void)setVideoSourceType:(ByteRTCVideoSourceType)type WithStreamIndex:(ByteRTCStreamIndex)streamIndex;

/**
 * @type api
 * @region 视频管理
 * @author wangzhanqiang
 * @brief 注册自定义编码帧推送事件回调
 * @param handler 自定义编码帧回调类，参看 ByteRTCExternalVideoEncoderEventHandler{@link #ByteRTCExternalVideoEncoderEventHandler}
 * @notes  <br>
 *       + 该方法需在进房前调用。 <br>
 *       + 引擎销毁前需取消注册，调用该方法将参数设置为 nullptr 即可。
 */
- (void)setExternalVideoEncoderEventHandler:(id<ByteRTCExternalVideoEncoderEventHandler> _Nullable)handler;

/**
 * @type api
 * @region 视频管理
 * @author wangzhanqiang
 * @brief 推送自定义编码后的视频流
 * @param streamIndex 需要推送的编码流的属性，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param videoIndex 对应的编码流下标，从 0 开始，如果调用 setVideoEncoderConfig:config:{@link #ByteRTCEngineKit#setVideoEncoderConfig:config:} 设置了多路流，此处数量须与之保持一致
 * @param videoFrame 编码流视频帧信息，参看 ByteRTCEncodedVideoFrame{@link #ByteRTCEncodedVideoFrame}。  <br>
 * @notes  <br>
 *        + 目前仅支持推送 H264 和 ByteVC1 格式的视频帧。  <br>
 *        + 该函数运行在用户调用线程内  <br>
 *        + 推送自定义编码视频帧前，必须调用 setVideoSourceType:WithStreamIndex:{@link #ByteRTCEngineKit#setVideoSourceType:WithStreamIndex:} 将视频输入源切换至自定义编码视频源。
 */
- (BOOL)pushExternalEncodedVideoFrame:(ByteRTCStreamIndex)streamIndex
                       withVideoIndex:(NSInteger)videoIndex
                withEncodedVideoFrame:(ByteRTCEncodedVideoFrame* _Nonnull)videoFrame;

/**
 * @type api
 * @region 视频管理
 * @author wangzhanqiang
 * @brief 在订阅远端视频流之前，设置远端视频数据解码方式
 * @param key 远端流信息，指定对哪一路视频流进行解码方式设置，参看 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}。
 * @param config 视频解码方式，参看 ByteRTCVideoDecoderConfig{@link #ByteRTCVideoDecoderConfig}。
 * @notes  <br>
 *        + 该方法近适用于手动订阅模式，并且在订阅远端流之前使用。  <br>
 *        + 当你想要对远端流进行自定义解码时，你需要先调用 registerRemoteEncodedVideoFrameObserver:{@link #ByteRTCEngineKit#registerRemoteEncodedVideoFrameObserver:} 注册远端视频流监测器，然后再调用该接口将解码方式设置为自定义解码。监测到的视频数据会通过 onRemoteEncodedVideoFrame:withEncodedVideoFrame:{@link #ByteRTCRemoteEncodedVideoFrameObserver#onRemoteEncodedVideoFrame:withEncodedVideoFrame:} 回调出来。
 */
- (void)setVideoDecoderConfig:(ByteRTCRemoteStreamKey * _Nonnull)key
       withVideoDecoderConfig:(ByteRTCVideoDecoderConfig)config;

/**
 * @type api
 * @region 视频管理
 * @author wangzhanqiang
 * @brief 在订阅远端视频流之后，向远端请求关键帧
 * @param key 远端流信息，参看 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}。
 * @notes  <br>
 *        + 该方法仅适用于手动订阅模式，并且在成功订阅远端流之后使用。  <br>
 *        + 该方法适用于调用 setVideoDecoderConfig:withVideoDecoderConfig:{@link #ByteRTCEngineKit#setVideoDecoderConfig:withVideoDecoderConfig:} 开启自定义解码功能后，并且自定义解码失败的情况下使用
 */
- (void)requestRemoteVideoKeyFrame:(ByteRTCRemoteStreamKey * _Nonnull)key;

/**
 * @type api
 * @region 视频管理
 * @author wangzhanqiang
 * @brief 注册远端编码后视频数据回調。  <br>
 *        完成注册后，当 SDK 监测到远端编码后视频帧时，会触发 onRemoteEncodedVideoFrame:withEncodedVideoFrame:{@link #ByteRTCRemoteEncodedVideoFrameObserver#onRemoteEncodedVideoFrame:withEncodedVideoFrame:} 回调
 * @param observer 远端编码后视频数据监测器，参看 ByteRTCRemoteEncodedVideoFrameObserver{@link #ByteRTCRemoteEncodedVideoFrameObserver}
 * @notes  <br>
 *       + 该方法需在进房前调用。 <br>
 *       + 引擎销毁前需取消注册，调用该方法将参数设置为 nullptr 即可。
 */
- (void)registerRemoteEncodedVideoFrameObserver:(id<ByteRTCRemoteEncodedVideoFrameObserver> _Nullable)observer;

/**
 * @type api
 * @region 音频管理
 * @author wangjunzheng
 * @brief 发送音频流同步信息。将消息通过音频流发送到远端，并实现与音频流同步，该接口调用成功后，远端用户会收到 onStreamSyncInfoReceived:streamType:data:{@link #ByteRTCEngineDelegate#onStreamSyncInfoReceived:streamType:data:} 回调。
 * @param data 消息内容。
 * @param config 媒体流信息同步的相关配置，详见 ByteRTCStreamSycnInfoConfig{@link #ByteRTCStreamSycnInfoConfig} 。
 * @return  <br>
 *        + >=0: 消息发送成功。返回成功发送的次数。  <br>
 *        + -1: 消息发送失败。消息长度大于 16 字节。  <br>
 *        + -2: 消息发送失败。传入的消息内容为空。  <br>
 *        + -3: 消息发送失败。不支持通过屏幕流进行消息同步。  <br>
 *        + -4: 消息发送失败。通过用麦克风采集到的音频流进行消息同步时，此音频流还未发布；请在发布麦克风流，并收到 onStreamPublishSuccess:{@link #ByteRTCRoom#onStreamPublishSuccess:} 之后，再调用该接口。  <br>
 */
#pragma mark StreamSyncInfo
- (int)sendStreamSyncInfo:(NSData* _Nonnull)data config:(ByteRTCStreamSycnInfoConfig * _Nonnull)config;
@end
