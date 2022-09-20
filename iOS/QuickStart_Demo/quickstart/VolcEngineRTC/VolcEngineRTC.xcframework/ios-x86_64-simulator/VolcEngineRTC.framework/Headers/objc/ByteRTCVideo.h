/*
 * Copyright (c) 2020 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC
*/
#import <CoreMedia/CMTime.h>
#import "rtc/ByteRTCDefines.h"
#import "rtc/ByteRTCHttpClientProtocol.h"
#import "rtc/ByteRTCAudioMixingManager.h"
@class ByteRTCVideo;
@class ByteRTCRoom;
/**
 * @type api
 */
@protocol ByteRTCHttpClientProtocol;

#pragma mark - ByteRTCVideoDelagate

/** 
 * @type callback
 * @brief ByteRTCVideoDelegate 协议包含了SDK提供的回调方法，SDK通过代理向应用程序上报一些运行时事件
 */
@protocol ByteRTCVideoDelegate <NSObject>
@optional
#pragma mark - Core Delegate Methods
// @name  core event callback
/** 
 * @type callback
 * @region 警告码
 * @brief 发生警告回调。  <br>
 *        SDK 运行时出现了警告。SDK 通常会自动恢复，警告信息可以忽略。
 * @param engine ByteRTCVideo 对象。
 * @param Code 警告代码，参看 ByteRTCWarningCode{@link #ByteRTCWarningCode}。
 */
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onWarning:(ByteRTCWarningCode)Code;
/** 
 * @type callback
 * @region 错误码
 * @brief 发生错误回调。<br>
 *        SDK 运行时出现了网络或媒体相关的错误，且无法自动恢复时触发此回调。
 * @param engine ByteRTCVideo 对象。  <br>
 * @param errorCode 错误代码，参看 ByteRTCErrorCode{@link #ByteRTCErrorCode}。  <br>
 */
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onError:(ByteRTCErrorCode)errorCode;

/** 
 * @type callback
 * @region 引擎管理
 * @author shenpengliang
 * @brief 创建房间失败回调。
 * @param roomId 房间 ID。
 * @param errorCode 创建房间错误码，具体原因参看 ByteRTCErrorCode{@link #ByteRTCErrorCode}。
 */
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onCreateRoomStateChanged:(NSString * _Nonnull)roomId errorCode:(NSInteger)errorCode;

/** 
 * @type callback
 * @region 引擎管理
 * @author hanchenchen.c
 * @brief SDK 与信令服务器连接状态改变回调。连接状态改变时触发。
 * @param engine ByteRTCVideo 对象
 * @param state 当前 SDK 与信令服务器的连接状态，详见 ByteRTCConnectionState{@link #ByteRTCConnectionState}
 */
- (void) rtcEngine:(ByteRTCVideo * _Nonnull)engine connectionChangedToState:(ByteRTCConnectionState) state;
/** 
 * @type callback
 * @region 引擎管理
 * @author hanchenchen.c
 * @brief SDK 当前网络连接类型改变回调。
 * @param engine ByteRTCVideo 对象
 * @param type SDK 当前的网络连接类型，详见 ByteRTCNetworkType{@link #ByteRTCNetworkType}
 */
- (void) rtcEngine:(ByteRTCVideo * _Nonnull)engine networkTypeChangedToType:(ByteRTCNetworkType) type;
#pragma mark - Core Audio Delegate Methods
// @name core audio event callback

/** 
 * @hidden
 * @deprecated since 336.1, use onUserPublishStream, onUserPublishScreen, onUserUnPublishStream and onUserUnPublishScreen instead.
 * @type callback
 * @region 媒体流管理
 * @author shenpengliang
 * @brief 房间内用户暂停/恢复发送音频流时，房间内其他用户会收到此回调。参看 muteLocalAudio:{@link #ByteRTCVideo#muteLocalAudio:}。
 * @param engine ByteRTCVideo 实例
 * @param uid 改变本地音频发送状态的用户 ID
 * @param muteState 发送状态，参看 ByteRTCMuteState{@link #ByteRTCMuteState}
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onUserMuteAudio:(NSString * _Nonnull)roomId
        uid:(NSString * _Nonnull)uid muteState:(ByteRTCMuteState)muteState;

/** 
 * @type callback
 * @region 音频事件回调
 * @author dixing
 * @brief 房间内的可见用户调用 startAudioCapture{@link #ByteRTCVideo#startAudioCapture} 开启音频采集时，房间内其他用户会收到此回调。
 * @param engine ByteRTCVideo 实例
 * @param roomId 开启音频采集的用户所在的房间 ID
 * @param userId 开启音频采集的远端用户 ID
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onUserStartAudioCapture:(NSString* _Nonnull)roomId
              uid:(NSString *_Nonnull)userId;

/** 
 * @type callback
 * @region 音频事件回调
 * @author dixing
 * @brief 房间内的可见用户调用 stopAudioCapture{@link #ByteRTCVideo#stopAudioCapture} 关闭音频采集时，房间内其他用户会收到此回调。
 * @param engine ByteRTCVideo 实例
 * @param roomId 关闭音频采集的用户所在的房间 ID
 * @param userId 关闭音频采集的远端用户 ID
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onUserStopAudioCapture:(NSString* _Nonnull)roomId
              uid:(NSString *_Nonnull)userId;
/** 
 * @type callback
 * @region 音频事件回调
 * @author wangjunzheng
 * @brief 当收到远端流的第一帧音频的时候上报该事件
 * @param engine ByteRTCVideo 对象
 * @param key 远端流信息, 详见 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
 * @notes 用户刚收到房间内每一路音频流时，都会收到该回调。
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onFirstRemoteAudioFrame:(ByteRTCRemoteStreamKey * _Nonnull)key;
 /** 
  * @type callback
  * @region 音频管理
  * @author wangjunzheng
  * @brief 调用 enableAudioPropertiesReport:{@link #ByteRTCVideo#enableAudioPropertiesReport:} 后，根据设置的 interval 值，你会周期性地收到此回调，了解本地音频的相关信息。  <br>
  *        本地音频包括使用 RTC SDK 内部机制采集的麦克风音频和屏幕音频。
  * @param engine ByteRTCVideo 对象
  * @param audioPropertiesInfos 本地音频信息，详见 ByteRTCLocalAudioPropertiesInfo{@link #ByteRTCLocalAudioPropertiesInfo} 。
  */
 - (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onLocalAudioPropertiesReport:(NSArray<ByteRTCLocalAudioPropertiesInfo *> * _Nonnull)audioPropertiesInfos;
 /** 
  * @hidden(iOS)
  * @type callback
  * @region 音频设备管理
  * @brief 回调音频设备测试时的播放音量
  * @param volume 音频设备测试播放音量。单位：毫秒。推荐设置为 200 ms。范围：[0,255]<br>
  * @notes 调用 startPlaybackDeviceTest:interval:{@link #ByteRTCAudioDeviceManager#startPlaybackDeviceTest:interval:} 或 startAudioDeviceRecordTest:{@link #ByteRTCAudioDeviceManager#startAudioDeviceRecordTest:}，开始播放音频文件或录音时，将开启该回调。本回调为周期性回调，回调周期由上述接口的 `interval` 参数指定。
  */
 - (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onAudioPlaybackDeviceTestVolume:(int)volume;
 /** 
  * @type callback
  * @region 音频管理
  * @author wangjunzheng
  * @brief 远端用户进房后，本地调用 enableAudioPropertiesReport:{@link #ByteRTCVideo#enableAudioPropertiesReport:} ，根据设置的 interval 值，本地会周期性地收到此回调，了解订阅的远端用户的音频信息。<br>
  *        远端用户的音频包括使用 RTC SDK 内部机制/自定义机制采集的麦克风音频和屏幕音频。
  * @param engine ByteRTCVideo 对象
  * @param audioPropertiesInfos 远端音频信息，其中包含音频流属性、房间 ID、用户 ID ，详见 ByteRTCRemoteAudioPropertiesInfo{@link #ByteRTCRemoteAudioPropertiesInfo}。
  * @param totalRemoteVolume 订阅的所有远端流的总音量，范围是 [0,255]。  <br>
  *       + [0,25] 接近无声；  <br>
  *       + [25,75] 为低音量；  <br>
  *       + [76,204] 为中音量；  <br>
  *       + [205,255] 为高音量。  <br>
  */
 - (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onRemoteAudioPropertiesReport:(NSArray<ByteRTCRemoteAudioPropertiesInfo *> * _Nonnull)audioPropertiesInfos totalRemoteVolume:(NSInteger)totalRemoteVolume;
/** 
 * @type callback
 * @region 音频管理
 * @author zhangcaining
 * @brief 调用 enableAudioPropertiesReport:{@link #ByteRTCVideo#enableAudioPropertiesReport:}  后，根据设置的 `config.interval`，你会周期性地收到此回调，获取房间内的最活跃用户信息。
 * @param roomId 房间 ID
 * @param uid 最活跃用户（ActiveSpeaker）的用户 ID
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onActiveSpeaker:(NSString * _Nonnull)roomId uid:(NSString *_Nonnull)uid;
#pragma mark - Core Video Delegate Methods
// @name core video event callback

/** 
 * @hidden
 * @deprecated since 336.1, use onUserPublishStream, onUserPublishScreen, onUserUnPublishStream and onUserUnPublishScreen instead.
 * @type callback
 * @region 视频管理
 * @author shenpengliang
 * @param engine ByteRTCVideo 实例
 * @brief 房间内用户暂停/恢复发送视频流时，房间内其他用户会收到此回调。参看 muteLocalVideo:{@link #ByteRTCVideo#muteLocalVideo:}。
 * @param uid 暂停/恢复发送视频流的用户 ID。
 * @param muteState 视频流的发送状态。参看 ByteRTCMuteState{@link #ByteRTCMuteState}。
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onUserMuteVideo:(NSString * _Nonnull)roomId
              uid:(NSString * _Nonnull)uid withMuteState:(ByteRTCMuteState)muteState;
/** 
 * @type callback
 * @region 视频管理
 * @author zhushufan.ref
 * @brief 房间内的可见用户调用 startVideoCapture{@link #ByteRTCVideo#startVideoCapture} 开启内部视频采集时，房间中其他用户会收到此回调。
 * @param engine ByteRTCVideo 实例
 * @param roomId 开启视频采集的用户所在的房间 ID
 * @param uid 调用 startVideoCapture{@link #ByteRTCVideo#startVideoCapture} 接口的远端用户 ID
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onUserStartVideoCapture:(NSString * _Nonnull)roomId
              uid:(NSString * _Nonnull)uid;
/** 
 * @type callback
 * @region 视频管理
 * @author zhushufan.ref
 * @brief 房间内的可见用户调用 stopVideoCapture{@link #ByteRTCVideo#stopVideoCapture} 关闭内部视频采集时，房间内其他用户会收到此回调。
 * @param engine ByteRTCVideo 实例
 * @param roomId 关闭视频采集的用户所在的房间 ID
 * @param uid 关闭视频采集的远端用户 ID
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onUserStopVideoCapture:(NSString * _Nonnull)roomId
              uid:(NSString * _Nonnull)uid;
/** 
 * @type callback
 * @region 视频管理
 * @author zhangzhenyu.samuel
 * @brief 第一帧本地采集的视频/屏幕共享画面在本地视图渲染完成时，收到此回调。
 * @param engine ByteRTCVideo 对象
 * @param streamIndex 流属性，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param frameInfo 视频帧信息，参看 ByteRTCVideoFrameInfo{@link #ByteRTCVideoFrameInfo}
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onFirstLocalVideoFrameCaptured:(ByteRTCStreamIndex)streamIndex withFrameInfo:(ByteRTCVideoFrameInfo * _Nonnull)frameInfo;
/** 
 * @type callback
 * @region 视频管理
 * @author zhushufan.ref
 * @brief SDK 内部渲染成功远端视频流首帧后，收到此回调。
 * @param engine ByteRTCVideo 对象
 * @param streamKey 远端流信息，参看 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
 * @param frameInfo 视频帧信息，参看 ByteRTCVideoFrameInfo{@link #ByteRTCVideoFrameInfo}
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onFirstRemoteVideoFrameRendered:(ByteRTCRemoteStreamKey * _Nonnull)streamKey withFrameInfo:(ByteRTCVideoFrameInfo * _Nonnull)frameInfo;
/** 
 * @type callback
 * @region 视频管理
 * @author zhushufan.ref
 * @brief SDK 接收并解码远端视频流首帧后，收到此回调。
 * @param engine ByteRTCVideo 对象
 * @param streamKey 远端流信息，参看 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
 * @param frameInfo 视频帧信息，参看 ByteRTCVideoFrameInfo{@link #ByteRTCVideoFrameInfo}
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onFirstRemoteVideoFrameDecoded:(ByteRTCRemoteStreamKey * _Nonnull)streamKey withFrameInfo:(ByteRTCVideoFrameInfo * _Nonnull)frameInfo;
/** 
 * @type callback
 * @region 视频管理
 * @author zhushufan.ref
 * @brief 远端视频大小或旋转信息发生变化时，房间内订阅此视频流的用户会收到此回调。
 * @param engine ByteRTCVideo 对象
 * @param streamKey 流属性，参看 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
 * @param frameInfo 视频帧信息，参看 ByteRTCVideoFrameInfo{@link #ByteRTCVideoFrameInfo}
 */
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onRemoteVideoSizeChanged:(ByteRTCRemoteStreamKey *_Nonnull)streamKey withFrameInfo:(ByteRTCVideoFrameInfo *_Nonnull)frameInfo;
/** 
 * @type callback
 * @region 视频管理
 * @author zhushufan.ref
 * @brief 本地视频大小或旋转信息发生变化时，收到此回调。
 * @param engine ByteRTCVideo 对象
 * @param streamIndex 流属性，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param frameInfo 视频帧信息，参看 ByteRTCVideoFrameInfo{@link #ByteRTCVideoFrameInfo}
 */
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onLocalVideoSizeChanged:(ByteRTCStreamIndex)streamIndex withFrameInfo:(ByteRTCVideoFrameInfo *_Nonnull)frameInfo;
/** 
 * @type callback
 * @region 视频管理
 * @author zhushufan.ref
 * @brief 远端视频流状态发生改变回调。
 * @param engine ByteRTCVideo 对象，参考: ByteRTCVideo{@link #ByteRTCVideo}
 * @param uid 发生视频流状态改变的远端用户的用户ID
 * @param state 变更后的远端视频流状态，详见类型 ByteRTCRemoteVideoState{@link #ByteRTCRemoteVideoState}
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine remoteVideoStateChangedOfUid:(NSString * _Nonnull)uid state:(ByteRTCRemoteVideoState)state;
/** 
 * @hidden
 * @deprecated since 337, using onAudioDeviceStateChanged and onVideoDeviceStateChanged instead
 * @type callback
 * @region 引擎管理
 * @author zhangzhenyu.samuel
 * @brief 媒体设备状态回调。提示音频采集、音频播放、摄像头视频采集、屏幕视频采集四种媒体设备的状态。
 * @param engine ByteRTCVideo 实例
 * @param device_id 设备 ID
 * @param device_type 设备类型，参看 ByteRTCMediaDeviceType{@link #ByteRTCMediaDeviceType}。
 * @param device_state 设备状态，参看 ByteRTCMediaDeviceState{@link #ByteRTCMediaDeviceState}。
 * @param device_error 设备错误类型，参看 ByteRTCMediaDeviceError{@link #ByteRTCMediaDeviceError}。
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onMediaDeviceStateChanged:(NSString*_Nonnull)device_id
        device_type:(ByteRTCMediaDeviceType)device_type
        device_state:(ByteRTCMediaDeviceState)device_state
        device_error:(ByteRTCMediaDeviceError)device_error
    __attribute((deprecated("Will be removed in new version")));
/** 
 * @type callback
 * @region 引擎管理
 * @author zhangzhenyu.samuel
 * @brief 音频设备状态回调。提示音频采集、音频播放等设备的状态。
 * @param engine ByteRTCVideo 实例
 * @param device_id 设备 ID
 * @param device_type 设备类型，参看 ByteRTCAudioDeviceType{@link #ByteRTCAudioDeviceType}。
 * @param device_state 设备状态，参看 ByteRTCMediaDeviceState{@link #ByteRTCMediaDeviceState}。
 * @param device_error 设备错误类型，参看 ByteRTCMediaDeviceError{@link #ByteRTCMediaDeviceError}。
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onAudioDeviceStateChanged:(NSString*_Nonnull)device_id
      device_type:(ByteRTCAudioDeviceType)device_type
     device_state:(ByteRTCMediaDeviceState)device_state
     device_error:(ByteRTCMediaDeviceError)device_error;
/** 
 * @type callback
 * @region 引擎管理
 * @author zhangzhenyu.samuel
 * @brief 视频设备状态回调。提示摄像头视频采集、屏幕视频采集等设备的状态。
 * @param engine ByteRTCVideo 实例
 * @param device_id 设备 ID
 * @param device_type 设备类型，参看 ByteRTCVideoDeviceType{@link #ByteRTCVideoDeviceType}。
 * @param device_state 设备状态，参看 ByteRTCMediaDeviceState{@link #ByteRTCMediaDeviceState}。
 * @param device_error 设备错误类型，参看 ByteRTCMediaDeviceError{@link #ByteRTCMediaDeviceError}。
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onVideoDeviceStateChanged:(NSString*_Nonnull)device_id
      device_type:(ByteRTCVideoDeviceType)device_type
     device_state:(ByteRTCMediaDeviceState)device_state
     device_error:(ByteRTCMediaDeviceError)device_error;
/** 
 * @hidden
 * @deprecated since 337, using onAudioDeviceWarning and onVideoDeviceWarning instead
 * @type callback
 * @region 引擎管理
 * @author dixing
 * @brief 媒体设备警告回调。媒体设备包括：音频采集设备、音频渲染设备、和视频采集设备。
 * @param engine ByteRTCVideo 对象
 * @param deviceId 设备 ID
 * @param deviceType 参看 ByteRTCMediaDeviceType{@link #ByteRTCMediaDeviceType}
 * @param deviceWarning 参看 ByteRTCMediaDeviceWarning{@link #ByteRTCMediaDeviceWarning}
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onMediaDeviceWarning:(NSString*_Nonnull)deviceId
    deviceType:(ByteRTCMediaDeviceType)deviceType
    deviceWarning:(ByteRTCMediaDeviceWarning)deviceWarning
    __attribute((deprecated("Will be removed in new version")));
/** 
 * @type callback
 * @region 引擎管理
 * @author dixing
 * @brief 音频设备警告回调。音频设备包括音频采集设备和音频渲染设备。
 * @param engine ByteRTCVideo 对象
 * @param deviceId 设备 ID
 * @param deviceType 参看 ByteRTCAudioDeviceType{@link #ByteRTCAudioDeviceType}
 * @param deviceWarning 参看 ByteRTCMediaDeviceWarning{@link #ByteRTCMediaDeviceWarning}
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onAudioDeviceWarning:(NSString*_Nonnull)deviceId
    deviceType:(ByteRTCAudioDeviceType)deviceType
    deviceWarning:(ByteRTCMediaDeviceWarning)deviceWarning;
/** 
 * @type callback
 * @region 引擎管理
 * @author dixing
 * @brief 视频设备警告回调。视频设备包括视频采集设备。
 * @param engine ByteRTCVideo 对象
 * @param deviceId 设备 ID
 * @param deviceType 参看 ByteRTCVideoDeviceType{@link #ByteRTCVideoDeviceType}
 * @param deviceWarning 参看 ByteRTCMediaDeviceWarning{@link #ByteRTCMediaDeviceWarning}
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onVideoDeviceWarning:(NSString*_Nonnull)deviceId
    deviceType:(ByteRTCVideoDeviceType)deviceType
    deviceWarning:(ByteRTCMediaDeviceWarning)deviceWarning;

/** 
 * @type callback
 * @region 房间管理
 * @author shenpengliang
 * @brief 音频首帧发送状态改变时，收到此回调。
 * @param engine ByteRTCVideo 对象
 * @param roomId 音频流发布用户所在的房间 ID
 * @param user 本地用户信息，详见 ByteRTCUser{@link #ByteRTCUser}
 * @param state 首帧发送状态，详见 ByteRTCFirstFrameSendState{@link #ByteRTCFirstFrameSendState}
 */
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onAudioFrameSendStateChanged:(NSString * _Nonnull)roomId
              rtcUser:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFrameSendState)state;

/** 
 * @type callback
 * @region 房间管理
 * @author shenpengliang
 * @brief 视频首帧发送状态改变时，收到此回调
 * @param engine ByteRTCVideo 对象
 * @param roomId 视频流发布用户所在的房间 ID
 * @param user 本地用户信息，详见 ByteRTCUser{@link #ByteRTCUser}
 * @param state 首帧发送状态，详见 ByteRTCFirstFrameSendState{@link #ByteRTCFirstFrameSendState}
 */
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onVideoFrameSendStateChanged:(NSString * _Nonnull)roomId
          rtcUser:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFrameSendState)state;

/** 
 * @type callback
 * @region 房间管理
 * @author shenpengliang
 * @brief 屏幕共享流视频首帧发送状态改变时，收到此回调
 * @param engine ByteRTCVideo 对象。  <br>
 * @param roomId 屏幕流发布用户所在的房间 ID
 * @param user 本地用户信息，参看 ByteRTCUser{@link #ByteRTCUser}
 * @param state 首帧发送状态，参看 ByteRTCFirstFrameSendState{@link #ByteRTCFirstFrameSendState}
 */
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onScreenVideoFrameSendStateChanged:(NSString * _Nonnull)roomId
          rtcUser:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFrameSendState)state;

/** 
 * @type callback
 * @region 房间管理
 * @author shenpengliang
 * @brief 音频首帧播放状态改变时，收到此回调
 * @param engine ByteRTCVideo 对象。  <br>
 * @param roomId 音频流发布用户所在的房间 ID
 * @param user 音频流来源的用户信息，参看 ByteRTCUser{@link #ByteRTCUser}
 * @param state 首帧播放状态，参看 ByteRTCFirstFramePlayState{@link #ByteRTCFirstFramePlayState}
 */
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onAudioFramePlayStateChanged:(NSString * _Nonnull)roomId
          rtcUser:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFramePlayState)state;

/** 
 * @type callback
 * @region 房间管理
 * @author shenpengliang
 * @brief 视频首帧播放状态改变时，收到此回调
 * @param engine ByteRTCVideo 对象。  <br>
 * @param user 视频流来源的用户信息，参看 ByteRTCUser{@link #ByteRTCUser}
 * @param roomId 视频流发布用户所在的房间 ID
 * @param state 首帧播放状态，参看 ByteRTCFirstFramePlayState{@link #ByteRTCFirstFramePlayState}
 */
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onVideoFramePlayStateChanged:(NSString * _Nonnull)roomId
          rtcUser:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFramePlayState)state;

/** 
 * @type callback
 * @region 房间管理
 * @author shenpengliang
 * @brief 屏幕共享流视频首帧播放状态改变时，收到此回调
 * @param engine ByteRTCVideo 对象。  <br>
 * @param roomId 屏幕流发布用户所在的房间 ID
 * @param user 屏幕共享流来源的用户信息，参看 ByteRTCUser{@link #ByteRTCUser}
 * @param state 首帧播放状态，参看 ByteRTCFirstFramePlayState{@link #ByteRTCFirstFramePlayState}
 */
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onScreenVideoFramePlayStateChanged:(NSString * _Nonnull)roomId rtcUser:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFramePlayState)state;
#pragma mark - Media Stream Delegate Methods
// @name media data event callback
/** 
 *  @type callback
 *  @region 音频事件回调
 *  @author wangjunzheng
 *  @brief 本地采集到第一帧音频帧时，收到该回调。
 *  @param engine ByteRTCVideo 对象
 *  @param streamIndex 音频流属性, 详见 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onFirstLocalAudioFrame:(ByteRTCStreamIndex) streamIndex;
/** 
 *  @hidden
 *  @type callback
 *  @region 音频管理
 *  @author wangjunzheng
 *  @brief 游戏场景中，当房间内远端用户的音频发送模式变化时回调该事件，发送模式只有三种，分别是：静音、向小队发送、向世界发送。
 *  @param engine  ByteRTCVideo 对象
 *  @param uid  远端用户 ID
 *  @param mode  远端用户的音频发送模式
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine didUserAudioSendModeChange:(NSString* _Nonnull )uid mode:(ByteRTCRangeAudioMode)mode;
/** 
 *  @hidden
 *  @type callback
 *  @region 音频管理
 *  @author wangjunzheng
 *  @brief 游戏场景中，当房间内远端用户的音频收听模式变化时回调该事件，收听模式只有三种，分别是：静音、收听小队、收听世界。
 *  @param engine  ByteRTCVideo 对象
 *  @param  uid  远端用户 ID
 *  @param  mode  远端用户的音频收听模式
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine didUserAudioRecvModeChange:(NSString* _Nonnull )uid mode:(ByteRTCRangeAudioMode)mode;
#pragma mark - Media Device Delegate Methods
// @name media device event callback
/** 
 * @hidden
 * @deprecated since 338.1, use onAudioRouteChanged instead
 *  @type callback
 *  @region 音频事件回调
 *  @author dixing
 *  @brief 音频播放设备变化时，收到该回调。
 *  @param engine ByteRTCVideo 实例。
 *  @param device 新的音频设备，详见 ByteRTCAudioPlaybackDevice{@link #ByteRTCAudioPlaybackDevice}
 *  @notes 音频设备设置与音频路由策略，详见 setAudioPlaybackDevice:{@link #ByteRTCVideo#setAudioPlaybackDevice:}
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onAudioPlaybackDeviceChanged:(ByteRTCAudioPlaybackDevice)device;
/** 
 * @hidden(macOS)
 * @type callback
 * @region 音频事件回调
 * @author dixing
 * @brief 音频播放路由变化时，收到该回调。
 * @param device 新的音频播放路由，详见 ByteRTCAudioRoute{@link #ByteRTCAudioRoute}
 * @notes 插拔音频外设，或调用 setAudioRoute:{@link #ByteRTCVideo#setAudioRoute:} 都可能触发音频路由切换，详见[音频路由](117836) 。
 */
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onAudioRouteChanged:(ByteRTCAudioRoute)device;
#pragma mark custom message Delegate Methods
// @name send message callback
/** 
 * @type callback
 * @region 视频管理
 * @author wangjunlin.3182
 * @brief 收到通过调用 sendSEIMessage:andMessage:andRepeatCount:{@link #ByteRTCVideo#sendSEIMessage:andMessage:andRepeatCount:} 带有 SEI 消息的视频帧时，收到此回调
 * @param engine 当前 ByteRTCVideo 实例。
 * @param remoteStreamKey 包含 SEI 发送者的用户名，所在的房间名和媒体流，参看 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
 * @param message 收到的 SEI 消息内容
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onSEIMessageReceived:(ByteRTCRemoteStreamKey* _Nonnull)remoteStreamKey andMessage:(NSData* _Nonnull)message;
/** 
 * @hidden
 * @type callback
 * @region 消息
 * @brief 黑帧视频流发布状态回调。  <br>
 *        在语音通话场景下，本地用户调用 sendSEIMessage:andMessage:andRepeatCount:{@link #ByteRTCVideo#sendSEIMessage:andMessage:andRepeatCount:} 通过黑帧视频流发送 SEI 数据时，流的发送状态会通过该回调通知远端用户。  <br>
 *        你可以通过此回调判断携带 SEI 数据的视频帧为黑帧，从而不对该视频帧进行渲染。
 * @param engine 当前 ByteRTCVideo 实例。
 * @param remoteStreamKey 远端流信息，参看 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}。
 * @param eventType 黑帧视频流状态，参看 ByteSEIStreamEventType{@link #ByteSEIStreamEventType}
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onSEIStreamUpdate:(ByteRTCRemoteStreamKey* _Nonnull)remoteStreamKey eventType:(ByteSEIStreamEventType)eventType;
/** 
 * @type api
 * @region 音频管理
 * @author wangjunzheng
 * @brief 音频流同步信息回调。可以通过此回调，在远端用户调用 sendStreamSyncInfo:config:{@link #ByteRTCVideo#sendStreamSyncInfo:config:} 发送音频流同步消息后，收到远端发送的音频流同步信息。  <br>
 * @param engine 当前 ByteRTCVideo 实例。
 * @param remoteStreamKey 远端流信息，详见 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey} 。
 * @param streamType 媒体流类型，详见 ByteRTCSyncInfoStreamType{@link #ByteRTCSyncInfoStreamType} 。
 * @param data 消息内容。
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onStreamSyncInfoReceived:(ByteRTCRemoteStreamKey* _Nonnull)remoteStreamKey streamType:(ByteRTCSyncInfoStreamType)streamType data:(NSData* _Nonnull)data;
#pragma mark - Statistics Delegate Methods
// @name data statistics callback
/** 
 * @type callback
 * @region 数据统计
 * @author liuzhiqiang.avcoder
 * @brief 报告当前设备 cpu 与 memory 使用率，每 2s 触发一次。
 * @param engine ByteRTCVideo 对象
 * @param stats cpu 和 memory 使用率信息，详见 ByteRTCSysStats{@link #ByteRTCSysStats} 数据类型
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine reportSysStats:(const ByteRTCSysStats * _Nonnull)stats;
/** 
 * @type callback
 * @region 音频事件回调
 * @author wangjunzheng
 * @brief 本地音频流的状态发生改变时，收到此回调。
 * @param engine ByteRTCVideo 对象
 * @param state 本地音频设备的当前状态，详见 ByteRTCLocalAudioStreamState{@link #ByteRTCLocalAudioStreamState}
 * @param error 本地音频流状态改变时的错误码，详见 ByteRTCLocalAudioStreamError{@link #ByteRTCLocalAudioStreamError}
 */
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine
    onLocalAudioStateChanged:(ByteRTCLocalAudioStreamState)state
                     error:(ByteRTCLocalAudioStreamError)error;
/** 
 *  @type callback
 *  @region 音频事件回调
 *  @author wangjunzheng
 *  @brief 订阅的远端音频流状态发生改变时，收到此回调。
 *  @param engine ByteRTCVideo 对象
 *  @param key 远端流信息, 详见 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
 *  @param state 远端音频流的当前状态，详见 ByteRTCRemoteAudioState{@link #ByteRTCRemoteAudioState}
 *  @param reason 远端音频流状态改变的原因，详见 ByteRTCRemoteAudioStateChangeReason{@link #ByteRTCRemoteAudioStateChangeReason}
 */
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine
    onRemoteAudioStateChanged:(ByteRTCRemoteStreamKey * _Nonnull)key
                      state:(ByteRTCRemoteAudioState)state
                      reason:(ByteRTCRemoteAudioStateChangeReason)reason;
/** 
 * @type callback
 * @region 视频管理
 * @author shenpengliang
 * @brief 本地视频流的状态发生改变时，收到该事件。
 * @param engine ByteRTCVideo 对象
 * @param streamIndex 流属性，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param state 本地视频流的当前状态，参看 ByteRTCLocalVideoStreamState{@link #ByteRTCLocalVideoStreamState}
 * @param error 本地视频状态改变时的错误码，参看 ByteRTCLocalVideoStreamError{@link #ByteRTCLocalVideoStreamError}
 */
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine
    onLocalVideoStateChanged:(ByteRTCStreamIndex)streamIndex
             withStreamState:(ByteRTCLocalVideoStreamState)state
             withStreamError:(ByteRTCLocalVideoStreamError)error;
/** 
 * @type callback
 * @region 视频管理
 * @author shenpengliang
 * @brief 远端视频流的状态发生改变时，房间内订阅此流的用户会收到该事件。
 * @param engine ByteRTCVideo 对象
 * @param streamKey 远端视频流信息，房间、用户 ID、流属性等，参看 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
 * @param state 远端视频流的当前状态，参看 ByteRTCRemoteVideoState{@link #ByteRTCRemoteVideoState}
 * @param reason 远端视频流状态改变的原因，参看 ByteRTCRemoteVideoStateChangeReason{@link #ByteRTCRemoteVideoStateChangeReason}
 */
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine
    onRemoteVideoStateChanged:(ByteRTCRemoteStreamKey*_Nonnull)streamKey
               withVideoState:(ByteRTCRemoteVideoState)state
withVideoStateReason:(ByteRTCRemoteVideoStateChangeReason)reason;

#pragma mark - Rtm
/** 
 * @type callback
 * @region 实时消息通信
 * @author hanchenchen.c
 * @brief 登录结果回调
 * @param engine ByteRTCVideo 对象
 * @param uid  <br>
 *        登录用户 ID
 * @param errorCode  <br>
 *        登录结果  <br>
 *        详见 ByteRTCLoginErrorCode{@link #ByteRTCLoginErrorCode}。
 * @param elapsed  <br>
 *        从调用 login:uid:{@link #ByteRTCVideo#login:uid:} 接口开始到返回结果所用时长。  <br>
 *        单位为 ms。
 * @notes 调用 login:uid:{@link #ByteRTCVideo#login:uid:} 后，会收到此回调。
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onLoginResult:(NSString * _Nonnull)uid errorCode:(ByteRTCLoginErrorCode)errorCode elapsed:(NSInteger)elapsed;
/** 
 * @type callback
 * @region 实时消息通信
 * @author hanchenchen.c
 * @brief 登出结果回调
 * @param engine ByteRTCVideo 对象
 * @notes 调用 logout{@link #ByteRTCVideo#logout} 后，会收到此回调。
 */
- (void)rtcEngineOnLogout:(ByteRTCVideo * _Nonnull)engine;
/** 
 * @type callback
 * @region 实时消息通信
 * @author hanchenchen.c
 * @brief 设置应用服务器参数的返回结果
 * @param engine ByteRTCVideo 对象
 * @param errorCode <br>
 *        设置结果  <br>
 *        + 返回 200，设置成功  <br>
 *        + 返回其他，设置失败，详见 ByteRTCUserMessageSendResult{@link #ByteRTCUserMessageSendResult}
 * @notes 调用 setServerParams:url:{@link #ByteRTCVideo#setServerParams:url:} 后，会收到此回调。
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onServerParamsSetResult:(NSInteger)errorCode;
/** 
 * @type callback
 * @region 实时消息通信
 * @author hanchenchen.c
 * @brief 查询对端或本端用户登录状态的返回结果
 * @param engine ByteRTCVideo 对象
 * @param peerUserId  <br>
 *        需要查询的用户 ID
 * @param status  <br>
 *        查询的用户登录状态  <br>
 *        详见 ByteRTCUserOnlineStatus{@link #ByteRTCUserOnlineStatus}.
 * @notes 必须先调用 getPeerOnlineStatus:{@link #ByteRTCVideo#getPeerOnlineStatus:}，才能收到此回调。
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onGetPeerOnlineStatus:(NSString * _Nonnull)peerUserId status:(ByteRTCUserOnlineStatus)status;
/** 
 * @type callback
 * @region 实时消息通信
 * @author hanchenchen.c
 * @brief 收到房间外用户调用 sendUserMessageOutsideRoom:message:config:{@link #ByteRTCVideo#sendUserMessageOutsideRoom:message:config:} 发来的文本消息时，会收到此回调
 * @param engine ByteRTCVideo 对象
 * @param uid  <br>
 *        消息发送者 ID
 * @param message  <br>
 *        收到的文本消息内容
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onUserMessageReceivedOutsideRoom:(NSString * _Nonnull)uid message:(NSString * _Nonnull)message;
/** 
 * @type callback
 * @region 实时消息通信
 * @author hanchenchen.c
 * @brief 收到房间外用户调用 sendUserBinaryMessageOutsideRoom:message:config:{@link #ByteRTCVideo#sendUserBinaryMessageOutsideRoom:message:config:} 发来的二进制消息时，会收到此回调。
 * @param engine ByteRTCVideo 对象
 * @param  uid  <br>
 *         消息发送者 ID
 * @param  message  <br>
 *         收到的二进制消息内容
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onUserBinaryMessageReceivedOutsideRoom:(NSString * _Nonnull)uid message:(NSData * _Nonnull)message;
/** 
 * @type callback
 * @region 实时消息通信
 * @author hanchenchen.c
 * @brief 给房间外指定的用户发送消息的回调
 * @param engine ByteRTCVideo 对象
 * @param msgid  <br>
 *        本条消息的 ID  <br>
 *        所有的 P2P 和 P2Server 消息共用一个 ID 序列。
 * @param error  <br>
 *        消息发送结果  <br>
 *        详见 ByteRTCUserMessageSendResult{@link #ByteRTCUserMessageSendResult}。
 * @notes 当调用 sendUserMessageOutsideRoom:message:config:{@link #ByteRTCVideo#sendUserMessageOutsideRoom:message:config:} 或 sendUserBinaryMessageOutsideRoom:message:config:{@link #ByteRTCVideo#sendUserBinaryMessageOutsideRoom:message:config:} 发送消息后，会收到此回调。
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onUserMessageSendResultOutsideRoom:(int64_t)msgid error:(ByteRTCUserMessageSendResult)error;
/** 
 * @type callback
 * @region 实时消息通信
 * @author hanchenchen.c
 * @brief 给应用服务器发送消息的回调
 * @param engine ByteRTCVideo 对象
 * @param msgid 本条消息的 ID  <br>
 *        所有的 P2P 和 P2Server 消息共用一个 ID 序列。
 * @param error 消息发送结果，详见 ByteRTCUserMessageSendResult{@link #ByteRTCUserMessageSendResult}。
 * @param message 应用服务器收到 HTTP 请求后，在 ACK 中返回的信息。
 * @notes 当调用 sendServerMessage:{@link #ByteRTCVideo#sendServerMessage:} 或 sendServerBinaryMessage:{@link #ByteRTCVideo#sendServerBinaryMessage:} 接口发送消息后，会收到此回调。
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onServerMessageSendResult:(int64_t)msgid error:(ByteRTCUserMessageSendResult)error message:(NSData * _Nonnull)message;
#pragma mark - Network Probe Methods
/** 
 * @type callback
 * @region 通话前网络探测
 * @author hanchenchen.c
 * @brief 通话前网络探测结果。  <br>
 *        成功调用 startNetworkDetection:uplinkBandwidth:downlink:downlinkBandwidth:{@link #ByteRTCVideo#startNetworkDetection:uplinkBandwidth:downlink:downlinkBandwidth:} 接口开始探测后，会在 3s 内首次收到该回调，之后每 2s 收到一次该回调。
 * @param engine ByteRTCVideo 对象
 * @param type 探测网络类型为上行/下行  <br>
 * @param quality 探测网络的质量，参看 ByteRTCNetworkQuality{@link #ByteRTCNetworkQuality}。 <br>
 * @param rtt 探测网络的 RTT，单位：ms  <br>
 * @param lost_rate 探测网络的丢包率  <br>
 * @param bitrate 探测网络的带宽，单位：kbps  <br>
 * @param jitter 探测网络的抖动,单位：ms  <br>
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onNetworkDetectionResult:(ByteRTCNetworkDetectionLinkType)type quality:(ByteRTCNetworkQuality)quality rtt:(int)rtt lostRate:(double)lost_rate bitrate:(int)bitrate jitter:(int)jitter;
/** 
 * @type callback
 * @region 通话前网络探测
 * @author hanchenchen.c
 * @brief 通话前网络探测结束  <br>
 *        以下情况将停止探测并收到本一次本回调：<br>
 *        1. 当调用 stopNetworkDetection{@link #ByteRTCVideo#stopNetworkDetection} 接口停止探测后，会收到一次该回调；
 *        2. 当收到远端/本端音频首帧后，停止探测；
 *        3. 当探测超过3分钟后，停止探测；
 *        4. 当探测链路断开一定时间之后，停止探测。
 * @param engine ByteRTCVideo 对象
 * @param err_code  <br>
 *        停止探测的原因类型,参考 ByteRTCNetworkDetectionStopReason{@link #ByteRTCNetworkDetectionStopReason}  <br>
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onNetworkDetectionStopped:(ByteRTCNetworkDetectionStopReason)err_code;
#pragma mark - Log Delegate Methods
// @name log related callbacks
/** 
 * @hidden
 * @type callback
 * @region 引擎管理
 * @author chenweiming.push
 * @brief SDK 内部日志回调。  <br>
 *        SDK 内部运行时，会把日志回调给业务方，方便排查问题。
 * @param engine  <br>
 *        ByteRTCVideo 对象。
 * @param dict  <br>
 *        日志内容。
 */
- (void)rtcEngine:(ByteRTCVideo* _Nonnull)engine log:(NSDictionary* _Nonnull)dict
    __attribute((deprecated("Will be removed in new version")));
#pragma mark Audio Mix Delegate Methods
// @name audio mix callback
/** 
 * @type callback
 * @region 混音
 * @author majun.lvhiei
 * @brief 音频混音文件播放状态改变时回调
 * @param engine 当前 RTC SDK 对象
 * @param mixId  <br>
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
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine
   onAudioMixingStateChanged:(NSInteger)mixId state:(ByteRTCAudioMixingState)state error:(ByteRTCAudioMixingError)error;
/** 
 * @type callback
 * @region 混音
 * @author majun.lvhiei
 * @brief 混音音频文件播放进度回调
 * @param engine 当前 RTC SDK 对象
 * @param mixId 混音 ID  <br>
 * @param progress 当前混音音频文件播放进度，单位毫秒
 * @notes 调用 setAudioMixingProgressInterval:interval:{@link #ByteRTCAudioMixingManager#setAudioMixingProgressInterval:interval:} 将时间间隔设为大于 0 的值后，或调用 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} 将 ByteRTCAudioMixingConfig{@link #ByteRTCAudioMixingConfig} 中的时间间隔设为大于 0 的值后，SDK 会按照设置的时间间隔回调该事件。 <br>
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine
    onAudioMixingPlayingProgress:(NSInteger)mixId progress:(int64_t) progress;
#pragma mark Performance Delegate Methods
// @name performance related callbacks
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
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine
    onPerformanceAlarmsWithMode:(ByteRTCPerformanceAlarmMode)mode
                         roomId:(NSString *_Nonnull)roomId
                         reason:(ByteRTCPerformanceAlarmReason)reason
               sourceWantedData:(ByteRTCSourceWantedData *_Nonnull)data;
/** 
 * @type callback
 * @region 音视频回退
 * @author panjian.fishing
 * @brief 音视频流因网络环境变化等原因发生回退，或从回退中恢复时，触发该回调。
 * @param engine 当前 ByteRTCVideo 实例
 * @param event 流切换信息。详见 ByteRTCRemoteStreamSwitchEvent{@link #ByteRTCRemoteStreamSwitchEvent}。
 */
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine OnSimulcastSubscribeFallback:(ByteRTCRemoteStreamSwitchEvent *_Nonnull)event;
#pragma mark Proxy Delegate Methods
// @name Socks5 and HTTP proxy callbacks
/** 
 * @type callback
 * @region 网络代理
 * @brief HTTP 代理连接状态改变时，收到该回调。
 * @param engine ByteRTCVideo 对象
 * @param state 当前 HTTP 代理连接状态
 */
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onHttpProxyState:(NSInteger)state;
/** 
 * @type callback
 * @region 网络代理
 * @brief HTTPS 代理连接状态改变时，收到该回调。
 * @param engine ByteRTCVideo 对象
 * @param state 当前 HTTPS 代理连接状态
 */
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onHttpsProxyState:(NSInteger)state;
/** 
 * @type callback
 * @region 网络代理
 * @brief SOCKS5 代理状态改变时，收到该回调。
 * @param engine ByteRTCVideo 对象
 * @param state SOCKS5 代理连接状态
 * @param cmd 代理连接的每一步操作命令
 * @param proxy_address 代理地址信息
 * @param local_address 当前连接使用的本地地址
 * @param remote_address 远端的连接地址
 */
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine
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
 *        该回调由 startFileRecording:withRecordingConfig:type:{@link #ByteRTCVideo#startFileRecording:withRecordingConfig:type:} 或 stopFileRecording:{@link #ByteRTCVideo#stopFileRecording:} 触发。
 * @param engine ByteRTCVideo 对象
 * @param type 录制流的流属性，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param state 录制状态，参看 ByteRTCRecordingState{@link #ByteRTCRecordingState}
 * @param error_code 录制错误码，参看 ByteRTCRecordingErrorCode{@link #ByteRTCRecordingErrorCode}
 * @param recording_info 录制文件的详细信息，参看 ByteRTCRecordingInfo{@link #ByteRTCRecordingInfo}
 */
- (void)rtcEngine:(ByteRTCVideo* _Nonnull)engine
        onRecordingStateUpdate:(ByteRTCStreamIndex)type
                         state:(ByteRTCRecordingState)state
                    error_code:(ByteRTCRecordingErrorCode)error_code
                recording_info:(ByteRTCRecordingInfo* _Nonnull)recording_info;
/** 
 * @type callback
 * @region 本地录制
 * @brief 本地录制进度回调。  <br>
 *        该回调由 startFileRecording:withRecordingConfig:type:{@link #ByteRTCVideo#startFileRecording:withRecordingConfig:type:} 触发，录制状态正常时，系统每秒钟都会通过该回调提示录制进度。
 * @param engine ByteRTCVideo 对象
 * @param type 录制流的流属性，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param process 录制进度，参看 ByteRTCRecordingProgress{@link #ByteRTCRecordingProgress}
 * @param recording_info 录制文件的详细信息，参看 ByteRTCRecordingInfo{@link #ByteRTCRecordingInfo}
 */
- (void)rtcEngine:(ByteRTCVideo* _Nonnull)engine
        onRecordingProgressUpdate:(ByteRTCStreamIndex)type
                          process:(ByteRTCRecordingProgress* _Nonnull)process
                   recording_info:(ByteRTCRecordingInfo* _Nonnull)recording_info;

/** 
 * @type callback
 * @author qipengxiang
 * @brief 公共流发布结果回调。<br>
 *        调用 startPushPublicStream:withLayout:{@link #ByteRTCVideo#startPushPublicStream:withLayout:} <br>
 *        接口或直接在服务端启动推公共流功能后，你会通过此回调收到启动结果和推流过程中的错误。
 * @param engine engine 实例
 * @param streamId 公共流ID。
 * @param errorCode 公共流发布结果状态码。 ByteRTCTranscodingError{@link #ByteRTCTranscodingError}。
 */
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine
onPushPublicStreamResult:(NSString *_Nonnull)roomId
        publiscStreamId:(NSString *_Nonnull)streamId
        errorCode:(ByteRTCTranscodingError)errorCode;

/** 
 * @type callback
 * @author qipengxiang
 * @brief 订阅公共流的结果回调  <br>
 *        调用 startPlayPublicStream:{@link #ByteRTCVideo#startPlayPublicStream:} 接口拉公共流后，你会通过此回调收到启动结果和拉流过程中的错误。
 * @param engine engine 实例
 * @param publicStreamId 公共流ID。
 * @param errorCode 公共流订阅结果状态码。详见枚举类型 ByteRTCTranscodingError{@link #ByteRTCTranscodingError}。
 */
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine
onPlayPublicStreamResult:(NSString *_Nonnull)publicStreamId
        errorCode:(ByteRTCTranscodingError)errorCode;
/** 
 * @type callback
 * @author qipengxiang
 * @brief 回调公共流中包含的 SEI 信息<br>
 *        通过 startPlayPublicStream:{@link #ByteRTCVideo#startPlayPublicStream:} 开始播放公共流后，可以通过本回调获取公共流中包含的 SEI 信息。
 * @param engine ByteRTCVideo 实例。
 * @param publicStreamId 公共流ID
 * @param message 收到的 SEI 消息内容
 * @notes 当公共流中的多路视频流均包含有 SEI 信息时：<br>
 *       SEI 不互相冲突时，将通过多次回调分别发送；<br>
 *       SEI 在同一帧有冲突时，则只有一条流中的 SEI 信息被透传并融合到公共流中。
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onPublicStreamSEIMessageReceived:(NSString* _Nonnull)publicStreamId andMessage:(NSData* _Nonnull)message;
/** 
 * @type callback
 * @author qipengxiang
 * @brief 公共流的首帧视频解码成功<br>
 *        关于订阅公共流，详见 startPlayPublicStream:{@link #ByteRTCVideo#startPlayPublicStream:}。
 * @param engine ByteRTCVideo 对象
 * @param publicStreamId 公共流 ID
 * @param frameInfo 视频帧信息，参看 ByteRTCVideoFrameInfo{@link #ByteRTCVideoFrameInfo}
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onFirstPublicStreamVideoFrameDecoded:(NSString * _Nonnull)publicStreamId withFrameInfo:(ByteRTCVideoFrameInfo * _Nonnull)frameInfo;
/** 
 * @type callback
 * @author qipengxiang
 * @brief 公共流的音频首帧解码成功<br>
 *        关于订阅公共流，详见 startPlayPublicStream:{@link #ByteRTCVideo#startPlayPublicStream:}。
 * @param engine ByteRTCVideo 对象
 * @param publicStreamId 公共流 ID
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onFirstPublicStreamAudioFrame:(NSString * _Nonnull)publicStreamId;
/** 
 * @author daining.nemo
 * @type callback
 * @brief 调用 startCloudProxy:{@link #ByteRTCVideo#startCloudProxy:} 开启云代理，SDK 首次成功连接云代理服务器时，回调此事件。
 * @param interval 从开启云代理到连接成功经过的时间，单位为 ms
 */
- (void)rtcEngine:(ByteRTCVideo *  _Nonnull)engine onCloudProxyConnected:(NSInteger)interval;
/** 
 * @type callback
 * @region 网络管理
 * @author qipengxiang
 * @brief 关于音视频回路测试结果的回调。
 * @param result 测试结果，参看 ByteRTCEchoTestResult{@link #ByteRTCEchoTestResult}。
 * @notes 该回调触发的时机包括： <br>
 *        + 检测过程中采集设备发生错误时；  <br>
 *        + 检测成功后；  <br>
 *        + 非设备原因导致检测过程中未接收到音/视频回放，停止检测后。
 */
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onEchoTestResult:(ByteRTCEchoTestResult)result;
@end
#pragma mark - RTCVideo
/** 
 * @type api
 * @region 引擎管理
 * @author chenweiming.push
 * @brief SDK 回调给应用层的 delegate 对象，详见 ByteRTCVideoDelegate{@link #ByteRTCVideoDelegate}
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVideo : NSObject
/**
 * @hidden
 */
@property (nonatomic, weak) id<ByteRTCVideoDelegate> _Nullable delegate;
/**
 * @hidden
 */
@property (nonatomic, weak) id<ByteRTCMonitorDelegate> _Nullable monitorDelegate
    __deprecated_msg("Will be removed in new version");

#pragma mark Core Methods
/**
 * @hidden
 */
+ (int)setEnv:(ByteRTCEnv)env;
/**
 * @hidden
 */
+ (void)setDeviceId:(NSString* _Nonnull) deviceID;

// @name core method
/** 
 * @type api
 * @region 引擎管理
 * @author chenweiming.push
 * @brief 创建引擎对象。<br>
 *        如果当前线程中未创建引擎实例，那么你必须先使用此方法，以使用 RTC 提供的各种音视频能力。  <br>
 *        如果当前线程中已创建了引擎实例，再次调用此方法时，会返回已创建的引擎实例。
 * @param appId 每个应用的唯一标识符，由 RTC 控制台随机生成的。
 *              不同的 AppId 生成的实例在 RTC 中进行音视频通话完全独立，无法互通。
 * @param delegate SDK 回调给应用层的 delegate，详见 ByteRTCVideoDelegate{@link #ByteRTCVideoDelegate}
 * @param parameters 用以覆盖默认参数的本引擎实例参数。JSON 字符串格式。
 * @return 可用的 ByteRTCVideo{@link #ByteRTCVideo} 实例
 */
+ (ByteRTCVideo * _Nullable) createRTCVideo:(NSString * _Nonnull)appId
                                      delegate:(id<ByteRTCVideoDelegate> _Nullable)delegate
                                    parameters:(NSDictionary * _Nonnull)parameters;
/** 
 * @type api
 * @region 引擎管理
 * @author chenweiming.push
 * @brief 销毁引擎实例对象
 * @notes  <br>
 *      + 请确保和需要销毁的 ByteRTCVideo{@link #ByteRTCVideo} 实例相关的业务场景全部结束后，才调用此方法  <br>
 *      + 该方法在调用之后，会销毁所有和此 ByteRTCVideo{@link #ByteRTCVideo} 实例相关的内存，并且停止与媒体服务器的任何交互  <br>
 *      + 调用本方法会启动 SDK 退出逻辑。引擎线程会保留，直到退出逻辑完成。因此，不要在回调线程中直接调用此 API，也不要在回调中等待主线程的执行，并同时在主线程调用本方法。不然会造成死锁。  <br>
 *      + 可以通过 Objective-C 的ARC机制，在 dealloc 时自动触发销毁逻辑
 */
+ (void)destroyRTCVideo;
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
 * @region 引擎管理
 * @author chenweiming.push
 * @brief 获取 SDK 内各种错误码、警告码的描述文字。
 * @param code  <br>
 *        通过 rtcEngine:onWarning:{@link #ByteRTCVideoDelegate#rtcEngine:onWarning:} 和 rtcEngine:onError:{@link #ByteRTCVideoDelegate#rtcEngine:onError:} 回调获得的值，
 *        具体可以参考 ByteRTCWarningCode{@link #ByteRTCWarningCode} 和 ByteRTCErrorCode{@link #ByteRTCErrorCode} 。
 * @return 描述文字。
 */
+ (NSString * _Nonnull)getErrorDescription:(NSInteger)code;
#pragma mark Core Audio Methods
// @name audio core method
/** 
 * @type api
 * @region 自定义音频采集渲染
 * @author gaoguangyuan
 * @brief 切换音频采集方式
 * @param type 音频数据源，详见 ByteRTCAudioSourceType{@link #ByteRTCAudioSourceType}。<br>
 *             默认使用内部音频采集。音频采集和渲染方式无需对应。
 * @return 方法调用结果：  <br>
 *        + >0: 切换成功。<br>
 *        + -1：切换失败。
 * @notes  <br>
 *      + 进房前后调用此方法均有效。<br>
 *      + 如果你调用此方法由内部采集切换至自定义采集，SDK 会自动关闭内部采集。然后，调用 pushExternalAudioFrame:{@link #ByteRTCVideo#pushExternalAudioFrame:} 推送自定义采集的音频数据到 RTC SDK 用于传输。 <br>
 *      + 如果你调用此方法由自定义采集切换至内部采集，你必须再调用 startAudioCapture{@link #ByteRTCVideo#startAudioCapture} 手动开启内部采集。
 */
- (int)setAudioSourceType:(ByteRTCAudioSourceType) type;
/** 
 * @type api
 * @region 自定义音频采集渲染
 * @author gaoguangyuan
 * @brief  切换音频渲染方式
 * @param type 音频输出类型，详见 ByteRTCAudioRenderType{@link #ByteRTCAudioRenderType} <br>
 *             默认使用内部音频渲染。音频采集和渲染方式无需对应。
 * @return  方法调用结果：  <br>
 *        + >0: 切换成功。<br>
 *        + -1：切换失败。
 * @notes  <br>
 *      + 进房前后调用此方法均有效。<br>
 *      + 如果你调用此方法切换至自定义渲染，调用 pullExternalAudioFrame:{@link #ByteRTCVideo#pullExternalAudioFrame:} 获取音频数据。 <br>
 */
- (int)setAudioRenderType:(ByteRTCAudioRenderType) type;
/** 
 * @type api
 * @region 音频管理
 * @author dixing
 * @brief 开启内部音频采集。默认为关闭状态。  <br>
 *        内部采集是指：使用 RTC SDK 内置的音频采集机制进行视频采集。
 *        调用该方法开启后，本地用户会收到 rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:} 的回调。  <br>
 *        非隐身用户进房后调用该方法，房间中的其他用户会收到 rtcEngine:onUserStartAudioCapture:uid:{@link #ByteRTCVideoDelegate#rtcEngine:onUserStartAudioCapture:uid:} 的回调。
 * @notes  <br>
 *       + 若未取得当前设备的麦克风权限，调用该方法后会触发 rtcEngine:onWarning:{@link #ByteRTCVideoDelegate#rtcEngine:onWarning:} 回调。  <br>
 *       + 调用 stopAudioCapture{@link #ByteRTCVideo#stopAudioCapture} 可以关闭音频采集设备，否则，SDK 只会在销毁引擎的时候自动关闭设备。  <br>
 *       + 由于不同硬件设备初始化响应时间不同，频繁调用 stopAudioCapture{@link #ByteRTCVideo#stopAudioCapture} 和本接口闭麦/开麦可能出现短暂无声问题，建议使用 publishStream:{@link #ByteRTCRoom#publishStream:}/unpublishStream:{@link #ByteRTCRoom#unpublishStream:} 实现临时闭麦和重新开麦。
 *       + 创建引擎后，无论是否发布音频数据，你都可以调用该方法开启音频采集，并且调用后方可发布音频。  <br>
 *       + 尚未进房并且已使用自定义采集时，关闭自定义采集后并不会自动开启内部采集。你需调用此方法手动开启内部采集。
  *       + 如果需要从自定义音频采集切换为内部音频采集，你必须先停止发布流，调用 disableExternalAudioDevice{@link #RTCVideodisableExternalAudioDevice} 关闭自定义采集，再调用此方法手动开启内部采集。
 */
- (void)startAudioCapture;
 /** 
  * @type api
  * @region 音频管理
  * @author dixing
  * @brief 关闭内部音频采集。默认为关闭状态。  <br>
  *        内部采集是指：使用 RTC SDK 内置的音频采集机制进行视频采集。
  *        调用该方法，本地用户会收到 rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:} 的回调。  <br>
  *        非隐身用户进房后调用该方法，房间中的其他用户会收到 rtcEngine:onUserStopAudioCapture:uid:{@link #ByteRTCVideoDelegate#rtcEngine:onUserStopAudioCapture:uid:} 的回调。
  * @notes  <br>
  *       + 调用 startAudioCapture{@link #ByteRTCVideo#startAudioCapture} 可以开启音频采集设备。  <br>
  *       + 如果不调用本方法停止内部视频采集，则只有当销毁引擎实例时，内部音频采集才会停止。
  */
 - (void)stopAudioCapture;
/** 
 * @type api
 * @region 音频管理
 * @author dixing
 * @brief 设置音频场景类型  <br>
 *        你可以根据你的应用所在场景，选择合适的音频场景类型。  <br>
 *        选择音频场景后，SDK 会自动根据客户端音频采集播放设备和状态，适用通话音量/媒体音量。  <br>
 *        本方法在进房前和进房后设置均可生效。
 * @param audioScenario 音频场景类型，参看 ByteRTCAudioScenarioType{@link #ByteRTCAudioScenarioType}。
 * @notes  <br>
 *        + 通话音量更适合通话、会议等对信息准确度更高的场景。通话音量会激活系统硬件信号处理，使通话声音更清晰。同时，音量无法降低到 0。  <br>
 *        + 媒体音量更适合娱乐场景，因其声音的表现力会更强。媒体音量下，最低音量可以为 0。
 */
- (void)setAudioScenario:(ByteRTCAudioScenarioType)audioScenario;
/** 
 * @type api
 * @region 音频管理
 * @author dixing
 * @brief 设置音质档位。当所选的 ByteRTCRoomProfile{@link #ByteRTCRoomProfile} 中的音频参数无法满足你的场景需求时，调用本接口切换的音质档位。  
 * @param audioProfile 音质档位，参看 ByteRTCAudioProfileType{@link #ByteRTCAudioProfileType}
 * @notes  <br>
 *        + 该方法在进房前后均可调用；  <br>
 *        + 支持通话过程中动态切换音质档位。
 */
- (void)setAudioProfile:(ByteRTCAudioProfileType)audioProfile;
/** 
 * @type api
 * @region 美声特效管理
 * @author luomingkang
 * @brief 设置变声特效类型
 * @param voiceChanger 变声特效类型，参看 ByteRTCVoiceChangerType{@link #ByteRTCVoiceChangerType}
 * @notes  <br>
 *        + 在进房前后都可设置。  <br>
 *        + 对 RTC SDK 内部采集的音频和自定义采集的音频都生效。 <br>
 *        + 只对单声道音频生效。<br>
 *        + 只在包含美声特效能力的 SDK 中有效。<br>
 *        + 与 setVoiceReverbType:{@link #setVoiceReverbType:} 互斥，后设置的特效会覆盖先设置的特效。 <br>
 */
- (void)setVoiceChangerType:(ByteRTCVoiceChangerType)voiceChanger;
/** 
 * @type api
 * @region 美声特效管理
 * @author luomingkang
 * @brief 设置混响特效类型
 * @param voiceReverb 混响特效类型，参看 ByteRTCVoiceReverbType{@link #ByteRTCVoiceReverbType}
 * @notes  <br>
 *        + 在进房前后都可设置。  <br>
 *        + 对 RTC SDK 内部采集的音频和自定义采集的音频都生效。 <br>
 *        + 只对单声道音频生效。<br>
 *        + 只在包含美声特效能力的 SDK 中有效。<br>
 *        + 与 setVoiceChangerType:{@link #setVoiceChangerType:} 互斥，后设置的特效会覆盖先设置的特效。 <br>
 */
- (void)setVoiceReverbType:(ByteRTCVoiceReverbType)voiceReverb;
/** 
 * @type api
 * @region 音频管理
 * @author wangjunzheng
 * @brief 调节音频采集音量
 * @param index 流索引，指定调节主流还是调节屏幕流的音量，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param volume 采集的音量值和原始音量的比值，范围是 [0, 400]，单位为 %，自带溢出保护。
 *        为保证更好的通话质量，建议将 volume 值设为 [0,100]。
 *       + 0：静音  <br>
 *       + 100：原始音量  <br>
 *       + 400: 最大可为原始音量的 4 倍(自带溢出保护)  <br>
 * @notes 在开启音频采集前后，你都可以使用此接口设定采集音量。
 */
- (void)setCaptureVolume:(ByteRTCStreamIndex)index volume:(int)volume;
/** 
 * @type api
 * @region 音频管理
 * @author dixing
 * @brief 调节本地播放的所有远端用户混音后的音量。播放音频前或播放音频时，你都可以使用此接口设定播放音量。
 * @param volume 音频播放音量值和原始音量的比值，范围是 [0, 400]，单位为 %，自带溢出保护。  <br>
 *        为保证更好的通话质量，建议将 volume 值设为 [0,100]。  <br>
 *       + 0: 静音  <br>
 *       + 100: 原始音量  <br>
 *       + 400: 最大可为原始音量的 4 倍(自带溢出保护)  <br>
 */
- (void)setPlaybackVolume:(NSInteger)volume;
/** 
 * @type api
 * @region 音频管理
 * @author wangjunzheng
 * @brief 启用音频信息提示。  <br>
 * @param config 详见 ByteRTCAudioPropertiesConfig{@link #ByteRTCAudioPropertiesConfig}  <br>
 * @notes  <br>
 *        开启提示后，你可以：  <br>
 *       + 通过 rtcEngine:onLocalAudioPropertiesReport:{@link #ByteRTCVideoDelegate#rtcEngine:onLocalAudioPropertiesReport:} 回调获取本地麦克风和屏幕音频流采集的音频信息；  <br>
 *       + 通过 rtcEngine:onRemoteAudioPropertiesReport:totalRemoteVolume:{@link #ByteRTCVideoDelegate#rtcEngine:onRemoteAudioPropertiesReport:totalRemoteVolume:} 回调获取订阅的远端用户的音频信息。  <br>
 *       + 通过 rtcEngine:onActiveSpeaker:uid:{@link #ByteRTCVideoDelegate#rtcEngine:onActiveSpeaker:uid:} 回调获取房间内的最活跃用户信息。
 */
- (void)enableAudioPropertiesReport:(ByteRTCAudioPropertiesConfig* _Nonnull)config;
/** 
 * @type api
 * @region 多房间
 * @author majun.lvhiei
 * @brief 调节来自远端用户的音频播放音量
 * @param room_id 音频来源用户所在的房间 ID
 * @param uid 音频来源的远端用户 ID
 * @param volume 音频播放音量值和原始音量的比值，范围是 [0, 400]，单位为 %，自带溢出保护。为保证更好的通话质量，建议将 volume 值设为 [0,100]。 <br>
 *              + 0: 静音  <br>
 *              + 100: 原始音量，默认值  <br>
 *              + 400: 最大可为原始音量的 4 倍(自带溢出保护)  <br>
 */
- (void)setRemoteAudioPlaybackVolume:(NSString *_Nonnull)room_id
                           remoteUid:(NSString *_Nonnull)uid
                          playVolume:(NSInteger)volume;
/** 
 * @hidden(macOS)
 * @type api
 * @region 音频管理
 * @author luoyi.007
 * @brief 开启/关闭耳返功能。
 * @param mode 是否开启耳返功能，参看 ByteRTCEarMonitorMode{@link #ByteRTCEarMonitorMode}。
 * @notes <br>
 *        + 耳返功能仅适用于由 RTC SDK 内部采集的音频。  <br>
 *        + 使用耳返必须佩戴耳机。为保证低延时耳返最佳体验，建议佩戴有线耳机。  <br>
 *        + 受 iOS 平台限制，RTC 仅支持软件耳返功能。
 */
- (void)setEarMonitorMode:(ByteRTCEarMonitorMode)mode;
/** 
 * @hidden(macOS)
 * @type api
 * @region 音频管理
 * @author luoyi.007
 * @brief 设置耳返的音量。
 * @param volume 耳返的音量，取值范围：[0,100]，单位：%
 * @notes <br>
 *        + 设置耳返音量前，你必须先调用 setEarMonitorMode:{@link #setEarMonitorMode:} 打开耳返功能。  
 */
- (void)setEarMonitorVolume:(NSInteger)volume;
/** 
 * @type api
 * @region 混音
 * @author wangjunzheng
 * @brief 开启本地语音变调功能，多用于 K 歌场景。  <br>
 *        使用该方法，你可以对本地语音的音调进行升调或降调等调整。
 * @param pitch 相对于语音原始音调的升高/降低值，取值范围[-12，12]，默认值为 0，即不做调整。  <br>
 *        取值范围内每相邻两个值的音高距离相差半音，正值表示升调，负值表示降调，设置的绝对值越大表示音调升高或降低越多。  <br>
 *        超出取值范围则设置失败，并且会触发 rtcEngine:onWarning:{@link #ByteRTCVideoDelegate#rtcEngine:onWarning:} 回调，提示 ByteRTCWarningCode{@link #ByteRTCWarningCode} 错误码为 `WARNING_CODE_SET_SCREEN_STREAM_INVALID_VOICE_PITCH` 设置语音音调不合法
 */
- (void)setLocalVoicePitch:(NSInteger)pitch;
/** 
 * @type api
 * @region 音频管理
 * @author majun.lvhiei
 * @brief 开启/关闭音量均衡功能。  <br>
 *        开启音量均衡功能后，人声的响度会调整为 -16lufs。如果已调用 setAudioMixingLoudness:loudness:{@link #ByteRTCAudioMixingManager#setAudioMixingLoudness:loudness:} 传入了混音音乐的原始响度，此音乐播放时，响度会调整为 -20lufs。
 * @param enable 是否开启音量均衡功能：  <br>
 *       + True: 是  <br>
 *       + False: 否
 * @notes 该接口须在调用 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} 开始播放音频文件之前调用。
 */
- (void)enableVocalInstrumentBalance:(BOOL)enable;
/** 
 * @type api
 * @region 音频管理
 * @author majun.lvhiei
 * @brief 打开/关闭音量闪避功能，适用于“一起看”等场景。  <br>
 *        开启该功能后，当检测到远端人声时，本地的媒体播放音量会自动减弱，从而保证远端人声的清晰可辨；当远端人声消失时，本地媒体音量会恢复到闪避前的音量水平。
 * @param enable 是否开启音量闪避：  <br>
 *        + True: 是  <br>
 *        + False: 否
 */
- (void)enablePlaybackDucking:(BOOL)enable;
#pragma mark Core Video Methods
// @name video core method
/** 
 * @type api
 * @region 自定义视频采集渲染
 * @author sunhang.io
 * @brief 将本地视频流与自定义渲染器绑定。
 * @param index 视频流属性。采集的视频流/屏幕视频流，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param videoSink 自定义视频渲染器，参看 ByteRTCVideoSinkDelegate{@link #ByteRTCVideoSinkDelegate}
 * @param requiredFormat videoSink 适用的视频帧编码格式，参看 ByteRTCVideoSinkPixelFormat{@link #ByteRTCVideoSinkPixelFormat}
 * @notes  <br>
 *        + RTC SDK 默认使用 RTC SDK 自带的渲染器（内部渲染器）进行视频渲染。
 *        + 如果需要解除绑定，必须将 videoSink 设置为 null。退房时将清除绑定状态。
 *        + 一般在收到 rtcEngine:onFirstLocalVideoFrameCaptured:withFrameInfo:{@link #ByteRTCVideoDelegate#rtcEngine:onFirstLocalVideoFrameCaptured:withFrameInfo:} 回调通知完成本地视频首帧采集后，调用此方法为视频流绑定自定义渲染器；然后加入房间。
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
 *        + 该方法进房前后均可以调用。若想在进房前调用，你需要在加入房间前获取远端流信息；若无法预先获取远端流信息，你可以在加入房间并通过 rtcRoom:onUserPublishStream:type:{@link #ByteRTCRoomDelegate#rtcRoom:onUserPublishStream:type:} 回调获取到远端流信息之后，再调用该方法。
 *        + 如果需要解除绑定，必须将 videoSink 设置为 null。退房时将清除绑定状态。
 */
- (void)setRemoteVideoSink:(ByteRTCRemoteStreamKey* _Nonnull)streamKey
                withSink:(id<ByteRTCVideoSinkDelegate> _Nullable)videoSink
         withPixelFormat:(ByteRTCVideoSinkPixelFormat)requiredFormat;
/** 
 * @hidden
 * @deprecated since 337, using setRemoteVideoConfig:remoteVideoConfig: instead
 * @type api
 * @region 视频管理
 * @author wangzhanqiang
 * @brief 设置推送多路流时的各路视频参数，包括分辨率、帧率、码率、缩放模式、网络不佳时的回退策略等。
 * @param streamIndex 视频流属性，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}。
 * @param videoSolutions 要推送的多路视频流参数，参看 ByteRTCVideoSolution{@link #ByteRTCVideoSolution}。 <br>
 *                       最多支持 4 路参数。当设置了多路参数时，分辨率必须是从大到小排列。 <br>
 *                       最大分辨率为 4096px × 4096px，超过或设置的分辨率无法编码时，会导致编码推流失败。
 * @return  <br>
 *        + 0：成功  <br>
 *        + !0：失败  <br>
 * @notes  <br>
 *       + 该接口已废弃，请使用同名新接口代替；若仍需使用该旧接口，请注意无需先调用 `enableSimulcastMode` 开启推送多路流模式。
 *       + 当使用内部采集时，视频采集的分辨率、帧率会根据最大的编码分辨率、帧率进行适配<br>
 *       + 默认的视频编码参数为：分辨率 640px × 360px，帧率 15fps。<br>
 *       + 变更编码分辨率后马上生效，可能会引发相机重启。<br>
 *       + 屏幕流只取视频参数数组的第一组数据。
 */
- (int)setVideoEncoderConfig:(ByteRTCStreamIndex)streamIndex config:(NSArray <ByteRTCVideoSolution *> * _Nullable)videoSolutions;
/** 
 * @type api
 * @region 视频管理
 * @author zhaomingliang
 * @brief 该方法设置视频流发布端是否开启发布多路编码参数不同的视频流的模式。
 * @param enabled 是否开启推送多路视频流模式： <br>
 *        + True：开启 <br>
 *        + False：关闭（默认）
 * @return 方法调用结果： <br>
 *        + 0: 成功 <br>
 *        + <0: 失败
 * @notes <br>
 *        + 你应在进房前或进房后但未发布流时，调用此方法。  <br>
 *        + 开启推送多路视频流模式后，你可以调用 SetVideoEncoderConfig:{@link #ByteRTCVideo#SetVideoEncoderConfig:} 为多路视频流分别设置编码参数。  <br>
 *        + 该功能关闭时，或该功能开启但未设置多路流参数时，默认只发一路视频流，该流的编码参数为：分辨率 640px × 360px，帧率 15fps。
 */
- (int) enableSimulcastMode:(BOOL) enabled;
/** 
 * @type api
 * @region 视频管理
 * @author zhaomingliang
 * @brief 视频发布端设置期望发布的最大分辨率视频流参数，包括分辨率、帧率、码率、缩放模式、网络不佳时的回退策略等。  <br>
 *        该接口支持设置一路视频流参数，设置多路参数请使用 SetVideoEncoderConfig:{@link #ByteRTCVideo#SetVideoEncoderConfig:}。
 * @param max_solution 期望发布的最大分辨率视频流参数。参看 ByteRTCVideoEncoderConfig{@link #ByteRTCVideoEncoderConfig}。
 * @return 方法调用结果： <br>
 *        + 0：成功  <br>
 *        + !0：失败  <br>
 * @notes  <br>
 *        + 若调用该方法设置了期望发布的最大分辨率的流参数之前，已调用 enableSimulcastMode:{@link #ByteRTCVideo#enableSimulcastMode:} 开启发布多路视频流的模式，SDK 会根据订阅端的设置自动调整发布的流数以及各路流的参数，其中最大分辨率为设置的分辨率，流数最多 4 条，具体参看[推送多路流](https://www.volcengine.com/docs/6348/70139)文档；否则仅发布该条最大分辨率的视频流。 <br>
 *        + 调用该方法设置多路视频流参数前，SDK 默认仅发布一条分辨率为 640px × 360px，帧率为 15fps 的视频流。  <br>
 *        + 该方法适用于摄像头采集的视频流，设置屏幕共享视频流参数参看 SetScreenVideoEncoderConfig:{@link #ByteRTCVideo#SetScreenVideoEncoderConfig:}。
 */
- (int)SetMaxVideoEncoderConfig:(ByteRTCVideoEncoderConfig * _Nullable) max_solution;
/** 
 * @type api
 * @region 视频管理
 * @author zhaomingliang
 * @brief 视频发布端设置推送多路流时各路流的参数，包括分辨率、帧率、码率、缩放模式、网络不佳时的回退策略等。
 * @param channel_solutions 要推送的多路视频流的参数，最多支持设置 3 路参数，超过 3 路时默认取前 3 路的值。  <br>
 *        当设置了多路参数时，分辨率必须是从大到小排列。需注意，所设置的分辨率是各路流的最大分辨率。参看 ByteRTCVideoEncoderConfig{@link #ByteRTCVideoEncoderConfig}。
 * @return 方法调用结果： <br>
 *        + 0：成功  <br>
 *        + !0：失败  <br>
 * @notes  <br>
 *        + 该方法是否生效取决于是否同时调用了 enableSimulcastMode:{@link #ByteRTCVideo#enableSimulcastMode:} 开启发布多路参数不同的视频流模式。若未开启推送多路流模式，但调用本方法设置了多个分辨率，SDK 默认发布分辨率最大的一条流，多个分辨率的设置会在开启推送多路流模式之后生效。  <br>
 *        + 调用该方法设置多路视频流参数前，SDK 默认仅发布一条分辨率为 640px × 360px，帧率为 15fps 的视频流。  <br>
 *        + 调用该方法设置分辨率不同的多条流后，SDK 会根据订阅端设置的期望订阅参数自动匹配发送的流，具体规则参看[推送多路流](https://www.volcengine.com/docs/6348/70139)文档。  <br>
 *        + 该方法适用于摄像头采集的视频流，设置屏幕共享视频流参数参看 SetScreenVideoEncoderConfig:{@link #ByteRTCVideo#SetScreenVideoEncoderConfig:}。
 */
-(int)SetVideoEncoderConfig:(NSArray <ByteRTCVideoEncoderConfig *> * _Nullable) channel_solutions;
/** 
 * @type api
 * @region 共享屏幕管理
 * @author zhaomingliang
 * @brief 为发布的屏幕共享视频流设置期望的编码参数，包括分辨率、帧率、码率、缩放模式、网络不佳时的回退策略等。
 * @param screen_solution 屏幕共享视频流参数。参看 ByteRTCVideoEncoderConfig{@link #ByteRTCVideoEncoderConfig}。
 * @return 方法调用结果： <br>
 *         0：成功  <br>
 *         !0：失败  <br>
 * @notes 调用该方法之前，屏幕共享视频流默认的编码参数为：分辨率 1920px × 1080px，帧率 15fps。
 */
-(int)SetScreenVideoEncoderConfig:(ByteRTCVideoEncoderConfig * _Nullable) screen_solution;
/** 
 * @type api
 * @region 视频管理
 * @author wangcheng.leo
 * @brief 设置 RTC SDK 内部采集时的视频采集参数。<br>
 *        如果你的项目使用了 SDK 内部采集模块，可以通过本接口指定视频采集参数包括模式、分辨率、帧率。
 * @param captureConfig 视频采集参数。参看: ByteRTCVideoCaptureConfig{@link #ByteRTCVideoCaptureConfig}。
 * @return  <br>
 *        + 0: 成功；  <br>
 *        + < 0: 失败；  <br>
 * @notes  <br>
 * + 本接口在引擎创建后可调用，调用后立即生效。建议在调用 startVideoCapture{@link #ByteRTCVideo#startVideoCapture} 前调用本接口。
 * + 建议同一设备上的不同引擎使用相同的视频采集参数。
 * + 如果调用本接口前使用内部模块开始视频采集，采集参数默认为 Auto 模式。
 */
- (int)setVideoCaptureConfig:(ByteRTCVideoCaptureConfig * _Nullable)captureConfig;
/** 
 * @type api
 * @region 视频管理
 * @author sunhang.io
 * @brief 设置本地视频渲染时，使用的视图，并设置渲染模式。
 * @param streamIndex 流属性，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param canvas 视图信息和渲染模式，参看 ByteRTCVideoCanvas{@link #ByteRTCVideoCanvas}
 * @return  <br>
 *         + 0：方法调用成功  <br>
 *         + < 0：方法调用失败  <br>
 * @notes  <br>
 *        + 你应在加入房间前，绑定本地视图。退出房间后，此设置仍然有效。 <br>
 *        + 如果需要解除绑定，你可以调用本方法传入空视图。
 */
- (int)setLocalVideoCanvas:(ByteRTCStreamIndex)streamIndex
                withCanvas:(ByteRTCVideoCanvas * _Nullable)canvas;
/** 
 * @type api
 * @region 视频管理
 * @author wangfujun.911
 * @brief 修改本地视频渲染模式和背景色。
 * @param streamIndex 视频流属性。参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param renderMode 渲染模式。参看 ByteRTCRenderMode{@link #ByteRTCRenderMode}
 * @param backgroundColor 背景颜色。参看 ByteRTCVideoCanvas{@link #ByteRTCVideoCanvas}.backgroundColor
 * @return  <br>
 *        + 0: 成功  <br>
 *        + -1: 失败。VideoCanvas 为空  <br>
 * @notes 你可以在本地视频渲染过程中，调用此接口。调用结果会实时生效。
 */
- (int)updateLocalVideoCanvas:(ByteRTCStreamIndex)streamIndex
                withRenderMode:(ByteRTCRenderMode)renderMode
          withBackgroundColor:(NSUInteger)backgroundColor;
/** 
 * @type api
 * @region 视频管理
 * @author sunhang.io
 * @brief 渲染来自指定远端用户 uid 的视频流时，设置使用的视图和渲染模式。  <br>
 *        如果需要解除视频的绑定视图，把 canvas 设置为空。
 * @notes  <br>
 *       + 你应在收到回调 rtcRoom:onUserJoined:elapsed:{@link #ByteRTCRoomDelegate#rtcRoom:onUserJoined:elapsed:} 或 rtcEngine:onFirstRemoteVideoFrameDecoded:withFrameInfo:{@link #ByteRTCVideoDelegate#rtcEngine:onFirstRemoteVideoFrameDecoded:withFrameInfo:} 后，为此远端视频流绑定视图。
 *         这两个回调的差别是：如果启用了视频录制功能，视频录制服务会作为一个哑客户端加入房间，因此其他客户端会收到对应的 rtcRoom:onUserJoined:elapsed:{@link #ByteRTCRoomDelegate#rtcRoom:onUserJoined:elapsed:} 回调；
 *         而不会收到 rtcEngine:onFirstRemoteVideoFrameDecoded:withFrameInfo:{@link #ByteRTCVideoDelegate#rtcEngine:onFirstRemoteVideoFrameDecoded:withFrameInfo:} 回调。你不应给录制的哑客户端绑定视图（因为它不会发送视频流）。
 *       + 本地用户离开房间时，会解除调用此 API 建立的绑定关系；远端用户离开房间则不会影响。
 * @param uid 视频来源的远端用户 ID
 * @param streamIndex 视频流属性，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param canvas 视图信息和渲染模式，参看 ByteRTCVideoCanvas{@link #ByteRTCVideoCanvas}
 * @return  <br>
 *         + 0：方法调用成功  <br>
 *         + < 0：方法调用失败  <br>
 */
- (int)setRemoteVideoCanvas:(NSString * _Nonnull)uid
                  withIndex:(ByteRTCStreamIndex)streamIndex
             withCanvas:(ByteRTCVideoCanvas * _Nullable)canvas;

/** 
 * @type api
 * @region 视频管理
 * @author wangfujun.911
 * @brief 修改远端视频渲染模式和背景色。
 * @param roomid 房间 ID
 * @param uid 用户 ID
 * @param streamIndex 远端流信息。参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}。
 * @param renderMode 渲染模式，参看 ByteRTCRenderMode{@link #ByteRTCRenderMode}
 * @param backgroundColor 背景颜色，参看 ByteRTCVideoCanvas{@link #ByteRTCVideoCanvas}.backgroundColor
 * @notes 你可以在远端视频渲染过程中，调用此接口。调用结果会实时生效。
 */
- (int)updateRemoteStreamVideoCanvas:(NSString * _Nonnull)roomid
                withUserId:(NSString * _Nonnull)uid
                withIndex:(ByteRTCStreamIndex)streamIndex
                withRenderMode:(ByteRTCRenderMode)renderMode
                withBackgroundColor:(NSUInteger)backgroundColor;
 /** 
  * @type api
  * @region 视频管理
  * @author zhangzhenyu.samuel
  * @brief 立即开启内部视频采集。默认为关闭状态。  <br>
  *        内部视频采集指：使用 RTC SDK 内置视频采集模块，进行采集。<br>
  *        调用该方法后，本地用户会收到 rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:} 的回调。  <br>
  *        非隐身用户进房后调用该方法，房间中的其他用户会收到 rtcEngine:onUserStartVideoCapture:uid:{@link #ByteRTCVideoDelegate#rtcEngine:onUserStartVideoCapture:uid:} 的回调。
  * @notes  <br>
  *       + 调用 stopVideoCapture{@link #ByteRTCVideo#stopVideoCapture} 可以停止内部视频采集。否则，只有当销毁引擎实例时，内部视频采集才会停止。  <br>
  *       + 创建引擎后，无论是否发布视频数据，你都可以调用该方法开启内部视频采集。只有当（内部或外部）视频采集开始以后视频流才会发布。  <br>
  *       + 如果需要从自定义视频采集切换为内部视频采集，你必须先停止发布流，关闭自定义采集，再调用此方法手动开启内部采集。<br>
  *       + 内部视频采集使用的摄像头由 switchCamera:{@link #ByteRTCVideo#switchCamera:} 接口指定。<br>
  *       + 自 v3.37.0 升级版本，你需要在应用中向用户申请摄像头权限后才能开始采集。
  */
 - (void)startVideoCapture;
 /** 
  * @type api
  * @region 视频管理
  * @author zhangzhenyu.samuel
  * @brief 立即关闭内部视频采集。默认为关闭状态。  <br>
  *        内部视频采集指：使用 RTC SDK 内置视频采集模块，进行采集。<br>
  *        调用该方法后，本地用户会收到 rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:} 的回调。  <br>
  *        非隐身用户进房后调用该方法，房间中的其他用户会收到 rtcEngine:onUserStopVideoCapture:uid:{@link #ByteRTCVideoDelegate#rtcEngine:onUserStopVideoCapture:uid:} 的回调。
  * @notes  <br>
  *       + 调用 startVideoCapture{@link #ByteRTCVideo#startVideoCapture} 可以开启内部视频采集。  <br>
  *       + 如果不调用本方法停止内部视频采集，则只有当销毁引擎实例时，内部视频采集才会停止。 <br>
  */
 - (void)stopVideoCapture;
/** 
 * @type api
 * @region 视频管理
 * @author wangjunlin.3182
 * @brief 为采集到的视频流开启镜像
 * @param mirrorType 镜像类型，参看 ByteRTCMirrorType{@link #ByteRTCMirrorType}
 * @notes <br>
 *        + 切换视频源不影响镜像设置。<br>
 *        + 屏幕视频流始终不受镜像设置影响。<br>
 *        + 该接口调用前，各视频源的初始状态如下：<br>
 *        <table>
 *           <tr><th></th><th>前置摄像头</th><th>后置摄像头</th><th>自定义采集视频源</th> <th>桌面端摄像头</th> </tr>
 *           <tr><td>移动端</td><td>本地预览镜像，编码传输不镜像</td><td> 本地预览不镜像，编码传输不镜像 </td><td> 本地预览不镜像，编码传输不镜像 </td><td>/</td></tr>
 *           <tr><td>桌面端</td><td>/</td><td>/</td><td> 本地预览不镜像，编码传输不镜像 </td><td> 本地预览镜像，编码传输不镜像 </td></tr> <br>
 *        </table>
 */
- (int)setLocalVideoMirrorType:(ByteRTCMirrorType) mirrorType;
/** 
 * @type api
 * @author wangjunlin.3182
 * @brief 设置采集视频的旋转模式。默认以 App 方向为旋转参考系。<br>
 *        接收端渲染视频时，将按照和发送端相同的方式进行旋转。<br>
 * @param rotationMode 视频旋转参考系为 App 方向或重力方向，参看 ByteRTCVideoRotationMode{@link #ByteRTCVideoRotationMode}。
 * @return 0:设置成功
 *        <0:设置失败
 * @notes <br>
 *        + 旋转仅对内部视频采集生效，不适用于外部视频源和屏幕源。
 *        + 调用该接口时已开启视频采集，将立即生效；调用该接口时未开启视频采集，则将在采集开启后生效。
 *        + 更多信息请参考[视频采集方向](https://www.volcengine.com/docs/6348/106458)。
 */
- (int)setVideoRotationMode:(ByteRTCVideoRotationMode) rotationMode;

/** 
 * @hidden(macOS)
 * @type api
 * @region 自定义流处理
 * @author wangjunlin.3182
 * @brief 在自定义视频前处理及编码前，设置 RTC 链路中的视频帧朝向，默认为 Adaptive 模式。
 *        移动端开启视频特效贴纸，或使用自定义视频前处理时，建议固定视频帧朝向为 Portrait 模式。单流转推场景下，建议根据业务需要固定视频帧朝向为 Portrait 或 Landscape 模式。不同模式的具体显示效果参看[视频帧朝向](https://www.volcengine.com/docs/6348/128787)。
 * @param orientation 视频帧朝向，参看 ByteRTCVideoOrientation{@link #ByteRTCVideoOrientation}。
 * @notes 
 *        +  设置视频帧朝向仅对内部视频采集生效，不适用于外部视频源和屏幕源。  <br>
 *        + 编码分辨率的更新与视频帧处理是异步操作，进房后切换视频帧朝向可能导致画面出现短暂的裁切异常，因此建议在进房前设置视频帧朝向，且不在进房后进行切换。
 */
- (void)setVideoOrientation:(ByteRTCVideoOrientation) orientation;
/** 
 * @hidden(macOS)
 * @type api
 * @region 视频管理
 * @author zhangzhenyu.samuel
 * @brief 切换视频内部采集时使用的前置/后置摄像头 <br>
 *        调用此接口后，在本地会触发 rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:} 回调。
 * @param cameraId 移动端摄像头 ID，参看 ByteRTCCameraID{@link #ByteRTCCameraID}。  <br>
 * @return  <br>
 *         + 0：方法调用成功  <br>
 *         + < 0：方法调用失败  <br>
 * @notes <br>
 *        + 默认使用前置摄像头。
 *        + 如果你正在使用相机进行视频采集，切换操作当即生效；如果相机未启动，后续开启内部采集时，会打开设定的摄像头。
 */
- (int)switchCamera:(ByteRTCCameraID) cameraId;
#if BYTERTC_TARGET_MAC
/** 
 * @type api
 * @hidden(iOS)
 * @region 视频特效
 * @brief 从特效 SDK 获取授权消息，用于获取在线许可证。
 * @param ppmsg 授权消息字符串地址
 * @return  <br>
 *      + 0: 调用成功。  <br>
 *      + 1000: 未集成特效 SDK。  <br>
 *      + 1001: 特效 SDK 不支持该功能。  <br>
 *      + < 0: 调用失败。参看 [错误码表](https://www.volcengine.com/docs/5889/61813)。  <br>
 * @notes <br>
 *        + 使用视频特效的功能前，你必须获取特效 SDK 的在线许可证。  <br>
 *        + 通过此接口获取授权消息后，参考 [在线授权说明](https://www.volcengine.com/docs/6705/102012)，自行实现获取在线许可证的业务逻辑。获取许可证后，你必须调用 checkVideoEffectLicense:{@link #ByteRTCVideo#checkVideoEffectLicense:} 确认许可证有效。然后，你才可以使用 CV 功能。  <br>
 */
- (int)getAuthMessage:(NSString *_Nullable*_Nullable)ppmsg;
#endif
/** 
 * @type api
 * @region 视频特效
 * @author zhushufan.ref
 * @brief 视频特效许可证检查
 * @param licenseFile 许可证文件绝对路径
 * @return  <br>
 *      + 0: 调用成功。  <br>
 *      + 1000: 未集成特效 SDK。  <br>
 *      + 1001: 特效 SDK 不支持该功能。  <br>
 *      + < 0: 调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/5889/61813)。  <br>
 * @notes enableVideoEffect:{@link #ByteRTCVideo#enableVideoEffect:} 开始使用视频特效前，需要先调用这个方法进行许可证验证
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
 * @return  <br>
 *        + 0: 调用成功。  <br>
 *        + 1000: 未集成特效 SDK。  <br>
 *        + 1001: 特效 SDK 不支持该功能。  <br>
 *        + < 0: 调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/5889/61813)。  <br>
 * @notes  <br>
 *       + 该方法须在调用 checkVideoEffectLicense:{@link #ByteRTCVideo#checkVideoEffectLicense:} 和 setVideoEffectAlgoModelPath:{@link #ByteRTCVideo#setVideoEffectAlgoModelPath:} 后调用。  <br>
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
 * @hidden
 * @type api
 * @region 视频特效
 * @author liqi.ritchie
 * @brief 设置视频特效算法模型地址，并初始化特效模块。
 * @param finder ResourceFinder 地址
 * @param deteter ResourceDeleter 地址
 * @return  <br>
 *      + 0: 调用成功。  <br>
 *      + 1000: 未集成特效 SDK。  <br>
 *      + 1001: 特效 SDK 不支持该功能。  <br>
 *      + < 0: 调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/5889/61813)。  <br>
 */
- (int)setVideoEffectAlgoModelResourceFinder:(void *_Nonnull)finder deleter:(void *_Nonnull)deteter;
/** 
 * @hidden
 * @type api
 * @region 视频特效
 * @author liqi.ritchie
 * @brief 开启人像属性检测。
 * @param config 人像属性参数，参看 ByteRTCExpressionDetectConfig{@link #ByteRTCExpressionDetectConfig}。
 * @return  <br>
 *      + 0: 调用成功。  <br>
 *      + 1000: 未集成特效 SDK。  <br>
 *      + 1001: 特效 SDK 不支持该功能。  <br>
 *      + < 0: 调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/5889/61813)。  <br>
 */
- (int)setVideoEffectExpressionDetect:(ByteRTCExpressionDetectConfig *_Nonnull)config;
/** 
 * @type api
 * @region 视频特效
 * @author zhushufan.ref
 * @brief 设置视频特效素材包
 * @param effectNodePaths 特效素材包路径数组 <br>
 *        要取消当前视频特效，将此参数设置为 null。
 * @return  <br>
  *      + 0: 调用成功。  <br>
  *      + 1000: 未集成特效 SDK。  <br>
  *      + 1001: 特效 SDK 不支持该功能。  <br>
  *      + < 0: 调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/5889/61813)。  <br>
 * @notes 在调用这个方法之前，你须先调用 enableVideoEffect:{@link #ByteRTCVideo#enableVideoEffect:} 。
 */
- (int) setVideoEffectNodes:(NSArray <NSString *> *_Nonnull)effectNodePaths;
/** 
 * @hidden
 * @type api
 * @region 视频特效
 * @author liqi.ritchie
 * @brief  叠加视频特效素材包。
 * @param effectNodePaths 特效素材包路径数组。
 * @return  <br>
 *      + 0: 调用成功。  <br>
 *      + 1000: 未集成特效 SDK。  <br>
 *      + 1001: 特效 SDK 不支持该功能。  <br>
 *      + < 0: 调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/5889/61813)。  <br>
 * @notes  该接口会在 setVideoEffectNodes:{@link #ByteRTCVideo#setVideoEffectNodes:} 设置的特效基础上叠加特效。
 */
- (int) appendVideoEffectNodes:(NSArray <NSString *> *_Nonnull)effectNodePaths;
/** 
 * @hidden
 * @type api
 * @region 视频特效
 * @author liqi.ritchie
 * @brief  移除指定的视频特效资源。
 * @param effectNodes 特效素材包路径数组。 <br>
 * @return  <br>
 *      + 0: 调用成功。  <br>
 *      + 1000: 未集成特效 SDK。  <br>
 *      + 1001: 特效 SDK 不支持该功能。  <br>
 *      + < 0: 调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/5889/61813)。  <br>
 * @notes 移除 setVideoEffectNodes:{@link #ByteRTCVideo#setVideoEffectNodes:} 或 appendVideoEffectNodes:{@link #ByteRTCVideo#appendVideoEffectNodes:} 设置的视频特效资源。
 */
- (int) removeVideoEffectNodes:(NSArray <NSString *> *_Nonnull)effectNodePaths;
/** 
 * @type api
 * @region 视频特效
 * @author zhushufan.ref
 * @brief 设置特效强度
 * @param nodePath 特效素材包路径。
 * @param nodeKey 需要设置的素材 key 名称。参看 [素材key对应说明](https://www.volcengine.com/docs/6705/102041)。
 * @param nodeValue 需要设置的强度值。取值范围为 [0,1]，超出该范围设置无效。
 * @return  <br>
  *      + 0: 调用成功。  <br>
  *      + 1000: 未集成特效 SDK。  <br>
  *      + 1001: 特效 SDK 不支持该功能。  <br>
  *      + < 0: 调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/5889/61813)。  <br>
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
  *      + 0: 调用成功。  <br>
  *      + 1000: 未集成特效 SDK。  <br>
  *      + 1001: 特效 SDK 不支持该功能。  <br>
  *      + < 0: 调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/5889/61813)。  <br>
 */
- (int) setVideoEffectColorFilter:(NSString * _Nonnull)resPath;
/** 
 * @type api
 * @region 视频特效
 * @author zhushufan.ref
 * @brief 设置已启用的颜色滤镜强度
 * @param intensity 滤镜强度。取值范围 [0,1]，超出范围时设置无效
 * @return  <br>
  *      + 0: 调用成功。  <br>
  *      + 1000: 未集成特效 SDK。  <br>
  *      + 1001: 特效 SDK 不支持该功能。  <br>
  *      + < 0: 调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/5889/61813)。  <br>
  */
- (int) setVideoEffectColorFilterIntensity:(float) intensity;
/** 
 * @hidden
 * @deprecated since 3.44, use setBackgroundSticker instead.
 * @type api
 * @region 视频特效
 * @author wangjunlin.3182
 * @brief 虚拟背景功能初始化。
 * @param licensePath CV 许可证文件的绝对路径
 * @param modelPath 模型参数文件的绝对路径
 * @return  <br>
 *        + 0: 调用成功。  <br>
 *        + 1000: 未集成特效 SDK。  <br>
 *        + 1001: 特效 SDK 不支持该功能。  <br>
 *        + > 40000: 调用失败，CV SDK 授权错误，具体错误码请参考 [错误码表](https://www.volcengine.com/docs/5889/61813)。  <br>
 *        + < 0: 调用失败，CV SDK 内部错误，具体错误码请参考 [错误码表](https://www.volcengine.com/docs/5889/61813)。  <br>
 */
- (int) initVirtualBackground:(NSString* _Nonnull)licensePath withModel:(NSString* _Nonnull)modelPath;
/** 
 * @hidden
 * @deprecated since 3.44, use setBackgroundSticker instead.
 * @type api
 * @region 视频特效
 * @author wangjunlin.3182
 * @brief 开启虚拟背景。
 * @param source 虚拟背景对象，详见 ByteRTCVirtualBackgroundSource{@link #ByteRTCVirtualBackgroundSource} 。
 * @return  <br>
 *        + 0: 调用成功。  <br>
 *        + < 0: 调用失败，CV SDK 内部错误，具体错误码请参考 [CV SDK 文档](https://www.volcengine.com/docs/5889/61813)。  <br>
 *        + -1: 调用失败，未调用 initVirtualBackground:withModel:{@link #ByteRTCVideo#initVirtualBackground:withModel:} 或调用失败，导致 license 验证失败。  <br>
 *        + -4: 调用失败，自定义背景图片打开失败。  <br>
 *        + -37: 调用失败，自定义背景图片解码失败。  <br>
 *        + -38: 调用失败，图片格式不支持。支持的图片格式是 jpg、jpeg、和 png。  <br>
 * @notes  <br>
 *       + 调用此接口前，需要先调用 initVirtualBackground:withModel:{@link #ByteRTCVideo#initVirtualBackground:withModel:} 初始化 CV 环境；  <br>
 *       + 虚拟背景仅支持摄像头采集的视频流，包括 RTC SDK 内部机制采集的方式和自定义采集的方式。虚拟背景不支持屏幕视频流。  <br>
 */
- (int) enableVirtualBackground:(ByteRTCVirtualBackgroundSource* _Nonnull)source;
/** 
 * @hidden
 * @deprecated since 3.44, use setBackgroundSticker instead.
 * @type api
 * @region 视频特效
 * @author wangjunlin.3182
 * @brief 关闭虚拟背景。
 * @return  <br>
 *        + 0: 调用成功。  <br>
 *        + < 0: 调用失败，具体错误码请参考 [CV SDK 文档](https://www.volcengine.com/docs/5889/61813)。  <br>
 * @notes 调用 enableVirtualBackground:{@link #ByteRTCVideo#enableVirtualBackground:} 开启虚拟背景后，可以调用此接口关闭虚拟背景。
 */
- (int) disableVirtualBackground;

/** 
 * @type api
 * @region 视频特效
 * @author liqi.ritchie
 * @brief 将摄像头采集画面中的人像背景替换为指定图片或纯色背景。
 *        若要取消背景特效，将背景贴纸特效素材路径设置为null。
 * @param modelPath 传入背景贴纸特效素材路径。  <br>
 * @param source 设置背景特效图片的本地路径。参看 ByteRTCVirtualBackgroundSource{@link #ByteRTCVirtualBackgroundSource}。  <br>
 * @return  <br>
 *        + 0：调用成功。  <br>
 *        + 1000：未集成特效 SDK。  <br>
 *        + 1001：特效 SDK 不支持该功能。  <br>
 *        + < 0：调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/5889/61813)。  
 * @notes  <br>
 *        调用此接口前需依次调用以下接口：1、检查视频特效许可证 checkVideoEffectLicense:{@link #ByteRTCVideo#checkVideoEffectLicense:}；2、设置视频特效算法模型路径 setVideoEffectAlgoModelPath:{@link #ByteRTCVideo#setVideoEffectAlgoModelPath:}；3、开启视频特效 enableVideoEffect:{@link #ByteRTCVideo#enableVideoEffect:}。
 */
- (int) setBackgroundSticker:(NSString* _Nullable)modelPath source:(ByteRTCVirtualBackgroundSource* _Nonnull)source;

/** 
 * @type api
 * @region 音视频处理
 * @author wangjunlin.3182
 * @brief 开启/关闭基础美颜
 * @param enable 基础美颜开关 <br>
 *        + true: 开启基础美颜 <br>
 *        + false: 关闭基础美颜（默认） <br>
 * @return  <br>
 *        + 0: 开启/关闭成功。 <br>
 *        + 1000: 未集成特效 SDK。 <br>
 *        + 1001: RTC SDK 版本不支持此功能。 <br>
 *        + 1002: 特效 SDK 当前版本不支持此功能，建议使用特效 SDK V4.3.1 版本。 <br>
 *        + 1003: 联系技术支持人员。 <br>
 *        + 1004: 正在下载相关资源，下载完成后生效。 <br>
 *        + <0: 调用失败，特效 SDK 内部错误，具体错误码请参考[错误码表](https://www.volcengine.com/docs/5889/61813)。  <br>
 * @notes <br>
 *        + 本方法不能与高级视频特效接口共用。如已购买高级视频特效，建议调用 enableVideoEffect:{@link #ByteRTCVideo#enableVideoEffect:} 使用高级特效、贴纸功能等。 <br>
 *        + 使用此功能需要集成特效 SDK，建议使用特效 SDK V4.3.1+ 版本。 <br>
 *        + 调用 setBeautyIntensity:withIntensity:{@link #ByteRTCVideo#setBeautyIntensity:withIntensity:} 设置基础美颜强度。若在调用本方法前没有设置美颜强度，则初始美白、磨皮、锐化强度均为 0.5。 <br>
 *        + 本方法仅适用于视频源，不适用于屏幕源。 <br>
 */
- (int) enableEffectBeauty:(BOOL)enable;

/** 
 * @type api
 * @region 音视频处理
 * @author wangjunlin.3182
 * @brief 调整基础美颜强度
 * @param beautyMode 基础美颜模式，参看 ByteRTCEffectBeautyMode{@link #ByteRTCEffectBeautyMode}。
 * @param intensity 美颜强度，取值范围为 [0,1]。强度为 0 表示关闭，默认强度为 0.5。
 * @return  <br>
 *        + 0: 开启成功。 <br>
 *        + 1000: 未集成特效 SDK。 <br>
 *        + 1001: RTC SDK 版本不支持此功能。 <br>
 *        + <0: 调用失败，特效 SDK 内部错误，具体错误码请参考[错误码表](https://www.volcengine.com/docs/5889/61813)。  <br>
 * @notes <br>
 *        + 若在调用 enableVideoEffect:{@link #ByteRTCVideo#enableVideoEffect:} 前设置美颜强度，则对应美颜功能的强度初始值会根据设置更新。 <br>
 *        + 销毁引擎后，美颜功能强度恢复默认值。 <br>
 */
- (int) setBeautyIntensity:(ByteRTCEffectBeautyMode) beautyMode
            withIntensity:(float)intensity;
#pragma mark - ICameraControl
/** 
 * @hidden(macOS)
 * @type api
 * @region 视频管理
 * @author zhangzhenyu.samuel
 * @brief 设置当前使用的摄像头（前置/后置）的变焦倍数
 * @param zoom_val 变焦倍数。取值范围是 [1, <最大变焦倍数>]。<br>
 *                 最大变焦倍数可以通过调用 getCameraZoomMaxRatio{@link #getCameraZoomMaxRatio} 获取。
 * @return  <br>
 *        + 0： 成功。 <br>
 *        + < 0： 失败。
 * @notes <br>
 *        + 必须已调用 startVideoCapture{@link #ByteRTCVideo#startVideoCapture} 使用 SDK 内部采集模块进行视频采集时，才能设置摄像头变焦倍数。<br>
 *        + 设置结果在调用 stopVideoCapture{@link #ByteRTCVideo#stopVideoCapture} 关闭内部采集后失效。
 */
- (int) setCameraZoomRatio: (float) zoom_val;
/** 
 * @hidden(macOS)
 * @type api
 * @region 视频管理
 * @author zhangzhenyu.samuel
 * @brief 获取当前使用的摄像头（前置/后置）的最大变焦倍数
 * @return 最大变焦倍数
 * @notes 必须已调用 startVideoCapture{@link #ByteRTCVideo#startVideoCapture} 使用 SDK 内部采集模块进行视频采集时，才能检测摄像头最大变焦倍数。
 */
- (float) getCameraZoomMaxRatio;
/** 
 * @hidden(macOS)
 * @type api
 * @region 视频管理
 * @author zhangzhenyu.samuel
 * @brief 检测当前使用的摄像头（前置/后置），是否支持变焦（数码/光学变焦）。
 * @return  <br>
 *        + true: 支持 <br>
 *        + false: 不支持
 * @notes 必须已调用 startVideoCapture{@link #ByteRTCVideo#startVideoCapture} 使用 SDK 内部采集模块进行视频采集时，才能检测摄像头变焦能力。
 */
- (bool) isCameraZoomSupported;
/** 
 * @hidden(macOS)
 * @type api
 * @region 视频管理
 * @author zhangzhenyu.samuel
 * @brief 检测当前使用的摄像头（前置/后置），是否支持闪光灯。
 * @return  <br>
 *        + true: 支持 <br>
 *        + false: 不支持
 * @notes 必须已调用 startVideoCapture{@link #ByteRTCVideo#startVideoCapture} 使用 SDK 内部采集模块进行视频采集时，才能检测闪光能力。
 */
- (bool) isCameraTorchSupported;
/** 
 * @hidden(macOS)
 * @type api
 * @region 视频管理
 * @author zhangzhenyu.samuel
 * @brief 打开/关闭当前使用的摄像头（前置/后置）的闪光灯
 * @param torch_state 打开/关闭。参看 ByteRTCTorchState{@link #ByteRTCTorchState}。
 * @return  <br>
 *        + 0： 成功。
 *        + < 0： 失败。
 * @notes <br>
 *        + 必须已调用 startVideoCapture{@link #ByteRTCVideo#startVideoCapture} 使用 SDK 内部采集模块进行视频采集时，才能设置闪光灯。<br>
 *        + 设置结果在调用 stopVideoCapture{@link #ByteRTCVideo#stopVideoCapture} 关闭内部采集后失效。
 */
- (int) setCameraTorch: (ByteRTCTorchState)torch_state;
/** 
 * @hidden(macOS)
 * @type api
 * @region 视频管理
 * @author zhangzhenyu.samuel
 * @brief 检查当前使用的摄像头是否支持手动对焦。
 * @return  <br>
 *        + true: 支持。 <br>
 *        + false: 不支持。
 * @notes 必须已调用 startVideoCapture{@link #ByteRTCVideo#startVideoCapture} 使用 SDK 内部采集模块进行视频采集，才能检查摄像头是否支持手动对焦。
 */
- (bool)isCameraFocusPositionSupported;
/** 
 * @hidden(macOS)
 * @type api
 * @region 视频管理
 * @author zhangzhenyu.samuel
 * @brief 设置当前使用的摄像头的对焦点。
 * @param position 对焦点坐标。以本地预览画布的左上为坐标原点，`position`的`x`字段为对焦点水平方向归一化坐标，`y`字段为对焦点垂直方向归一化坐标，取值范围为 [0, 1]。
 * @return  <br>
 *        + 0: 成功。 <br>
 *        + < 0: 失败。
 * @notes <br>
 *        + 必须已调用 startVideoCapture{@link #ByteRTCVideo#startVideoCapture} 使用 SDK 内部采集模块进行视频采集，并且使用 SDK 内部渲染时，才能设置对焦点。  <br>
 *        + 对焦点设置为画布中央（即`x`和`y`均取 0.5）时，恢复系统默认值。  <br>
 *        + 调用 stopVideoCapture{@link #ByteRTCVideo#stopVideoCapture} 关闭内部采集后，设置的对焦点失效。
 */
- (int)setCameraFocusPosition:(CGPoint)position;
/** 
 * @hidden(macOS)
 * @type api
 * @region 视频管理
 * @author zhangzhenyu.samuel
 * @brief 检查当前使用的摄像头是否支持手动设置曝光点。
 * @return  <br>
 *        + true: 支持。 <br>
 *        + false: 不支持。
 * @notes 必须已调用 startVideoCapture{@link #ByteRTCVideo#startVideoCapture} 使用 SDK 内部采集模块进行视频采集时，才能检查曝光点设置能力。
 */
- (bool)isCameraExposurePositionSupported;
/** 
 * @hidden(macOS)
 * @type api
 * @region 视频管理
 * @author zhangzhenyu.samuel
 * @brief 设置当前使用的摄像头的曝光点。
 * @param position 曝光点坐标。以本地预览画布的左上为坐标原点，`position`的`x`字段为曝光点水平方向归一化坐标，`y`字段为曝光点垂直方向归一化坐标，取值范围为 [0, 1]。
 * @return  <br>
 *        + 0: 成功。 <br>
 *        + < 0: 失败。
 * @notes <br>
 *        + 必须已调用 startVideoCapture{@link #ByteRTCVideo#startVideoCapture} 使用 SDK 内部采集模块进行视频采集，并且使用 SDK 内部渲染时，才能设置曝光点。  <br>
 *        + 曝光点设置为画布中央（即`x`和`y`均取 0.5）时，恢复系统默认值。  <br>
 *        + 调用 stopVideoCapture{@link #ByteRTCVideo#stopVideoCapture} 关闭内部采集后，设置的曝光点失效。
 */
- (int)setCameraExposurePosition:(CGPoint)position;
/** 
 * @hidden(macOS)
 * @type api
 * @region 视频管理
 * @author zhangzhenyu.samuel
 * @brief 设置当前使用的摄像头的曝光补偿。
 * @param val 曝光补偿值，取值范围 [-1, 1]，0 为系统默认值(没有曝光补偿)。
 * @return  <br>
 *        + 0: 成功。 <br>
 *        + < 0: 失败。
 * @notes <br>
 *        + 必须已调用 startVideoCapture{@link #ByteRTCVideo#startVideoCapture} 使用 SDK 内部采集模块进行视频采集时，才能设置曝光补偿。  <br>
 *        + 调用 stopVideoCapture{@link #ByteRTCVideo#stopVideoCapture} 关闭内部采集后，设置的曝光补偿失效。
 */
- (int)setCameraExposureCompensation:(float)val;
/** 
 * @type api
 * @region 视频特效
 * @author wangjunlin.3182
 * @brief 注册人脸检测结果回调观察者 <br>
 *        注册此观察者后，你会周期性收到 onFaceDetectionResult:{@link #ByteRTCFaceDetectionObserver#onFaceDetectionResult:} 回调。
 * @param faceDetectionObserver 人脸检测结果回调观察者，参看 ByteRTCFaceDetectionObserver{@link #ByteRTCFaceDetectionObserver}。
 * @param interval 时间间隔，必须大于 0。单位：ms。实际收到回调的时间间隔大于 `interval`，小于 `interval + 视频采集帧间隔`。
 * @return <br>
 *        + 0：方法调用成功  <br>
 *        + < 0：方法调用失败  <br>
 */
- (int) registerFaceDetectionObserver:(_Nullable id<ByteRTCFaceDetectionObserver>)faceDetectionObserver
                  withInterval:(NSInteger)interval;
#pragma mark - MediaMetadataData InnerVideoSource
/** 
 * @type api
 * @region 消息
 * @author wangjunlin.3182
 * @brief 通过视频帧发送 SEI 数据。  <br>
 *        在视频通话场景下，SEI 数据会随视频帧发送；在语音通话场景下，SDK 会自动生成一路 16px × 16px 的黑帧视频流用来发送 SEI 数据。
 * @param streamIndex 指定携带 SEI 数据的媒体流类型，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}。  <br>
 *        语音通话场景下，该值需设为 `ByteRTCStreamIndexMain`，否则 SEI 数据会被丢弃从而无法送达远端。
 * @param message SEI 消息。长度不超过 4KB。
 * @param repeatCount 消息发送重复次数。取值范围是 [0, 30]。<br>
 *                    调用此接口后，SEI 数据会添加到从当前视频帧开始的连续 `repeatCount` 个视频帧中。
 * @return <br>
 *        + >=0: 将被添加到视频帧中的 SEI 的数量  <br>
 *        + <0: 发送失败
 * @notes <br>
 *        + 语音通话场景中，仅支持在内部采集模式下调用该接口发送 SEI 数据，且调用频率需为 15/repeat_count FPS。  <br>
 *        + 视频帧仅携带前后 2s 内收到的 SEI 数据；语音通话场景下，若调用此接口后 1min 内未有 SEI 数据发送，则 SDK 会自动取消发布视频黑帧。  <br>
 *        + 消息发送成功后，远端会收到 rtcEngine:onSEIMessageReceived:andMessage:{@link #ByteRTCVideoDelegate#rtcEngine:onSEIMessageReceived:andMessage:} 回调。  <br>
 *        + 语音通话切换至视频通话时，会停止 SEI 数据发送，你需再次调用该接口方可恢复发送。
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
 * @notes 该方法可以在任意时间调用，建议在 joinRoomByToken:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoomByToken:userInfo:roomConfig:} 前。
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
#pragma mark Audio Routing Controller
// @name audio playback route
/** 
 * @hidden
 * @deprecated since 338.1, use setAudioRoute instead
 * @type api
 * @region 音频管理
 * @author dixing
 * @brief 设置音频播放设备为扬声器或者听筒，默认使用扬声器。  <br>
 *        音频播放设备发生变化时，会收到 rtcEngine:onAudioPlaybackDeviceChanged:{@link #ByteRTCVideoDelegate#rtcEngine:onAudioPlaybackDeviceChanged:} 回调。  <br>
 * @param audioPlaybackDevice 音频播放设备（扬声器或者听筒），详见 ByteRTCAudioPlaybackDevice{@link #ByteRTCAudioPlaybackDevice}。  <br>
 * @return  方法调用结果  <br>
 *        + 0: 方法调用成功  <br>
 *        + < 0: 方法调用失败  <br>
 * @notes  <br>
 *       + 该方法适用于手机等移动设备。  <br>
 *       + 听筒和扬声器为移动设备自带的音频播放设备。听筒一般用于通话，扬声器一般用于外放。  <br>
 *       + 连接有线或者蓝牙音频播放设备后，音频路由将切换至有线耳机或者蓝牙耳机。不同音频场景中，音频路由和发布订阅状态到音量类型的映射关系详见 ByteRTCAudioScenarioType{@link #ByteRTCAudioScenarioType} 。  <br>
 *       + 进房前和进房后，均可调用此方法设置音频播放设备。  <br>
 */
- (int)setAudioPlaybackDevice:(ByteRTCAudioPlaybackDevice)audioPlaybackDevice;
/** 
 * @hidden(macOS)
 * @type api
 * @region 音频管理
 * @author liuxiaowu
 * @brief 设置当前音频播放路由。默认使用 setDefaultAudioRoute:{@link #ByteRTCVideo#setDefaultAudioRoute:} 中设置的音频路由。  <br>
 *        音频播放路由发生变化时，会收到 rtcEngine:onAudioRouteChanged:{@link #ByteRTCVideoDelegate#rtcEngine:onAudioRouteChanged:} 回调。  <br>
 * @param audioRoute 音频播放路由，参见 ByteRTCAudioRoute{@link #ByteRTCAudioRoute}。<br>
 *        不支持 `ByteRTCAudioRouteUnknown`。<br>
 *        当音量类型为媒体音量时，此参数不可设置为 `ByteRTCAudioRouteEarpiece`；当音量模式为通话音量时，此参数不可设置为 `ByteRTCAudioRouteHeadsetBluetooth` 或 `ByteRTCAudioRouteHeadsetUSB`。
 * @return  <br>
 *        + 0: 方法调用成功  <br>
 *        + < 0: 方法调用失败。失败原因参看 ByteRTCMediaDeviceWarning{@link #ByteRTCMediaDeviceWarning} 回调。指定为 `kAudioRouteUnknown` 时将会失败。  <br>
 * @notes <br>
 *        + 你需要调用 setAudioScenario:{@link #ByteRTCVideo#setAudioScenario:} 将音频场景切换为 `ByteRTCAudioScenarioCommunication` 后再调用本接口。<br>
 *        + 连接有线或者蓝牙音频播放设备后，音频路由将自动切换至此设备。<br>
 *        + 移除后，音频设备会自动切换回原设备。<br>
 *        + 不同音频场景中，音频路由和发布订阅状态到音量类型的映射关系详见 ByteRTCAudioScenarioType{@link #ByteRTCAudioScenarioType} 。
 */
- (int)setAudioRoute:(ByteRTCAudioRoute)audioRoute;
/** 
 * @type api
 * @region 音频管理
 * @author dixing
 * @brief 获取当前使用的音频播放路由。  <br>
 * @return 详见 ByteRTCAudioRoute{@link #ByteRTCAudioRoute}
 * @notes 要设置音频路由，移动端详见 setAudioRoute:{@link #ByteRTCVideo#setAudioRoute:}，桌面端详见 setAudioPlaybackDevice:{@link #ByteRTCAudioDeviceManager#setAudioPlaybackDevice:}。
 */
- (ByteRTCAudioRoute)getAudioRoute;
/** 
 * @type api
 * @author liuxiaowu
 * @brief 启用匹配外置声卡的音频处理模式
 * @param enable <br>
 *        + true: 开启 <br>
 *        + false: 不开启(默认)
 * @notes  <br>
 *        + 当采用外接声卡进行音频采集时，建议开启此模式，以获得更好的音质。<br>
 *        + 开启此模式时，仅支持耳机播放。如果需要使用扬声器或者外置音箱播放，关闭此模式。
 */
- (void)enableExternalSoundCard:(bool)enable;
/** 
 * @hidden(macOS,Windows)
 * @type api
 * @region 音频设备管理
 * @author liuxiaowu
 * @brief 将默认的音频播放设备设置为听筒或扬声器。  <br>
 * @param audioRoute 音频播放设备。参看 ByteRTCAudioRoute{@link #ByteRTCAudioRoute} <br>
 * @return 方法调用结果  <br>
 *        + 0: 方法调用成功。立即生效。当所有音频外设移除后，音频路由将被切换到默认设备。<br>
 *        + < 0: 方法调用失败。指定除扬声器和听筒以外的设备将会失败。   <br>
 * @notes    <br>
 *        + 进房前后都可以调用。 <br>
 *        + 更多注意事项参见[音频路由](117836)。
 */
- (int)setDefaultAudioRoute:(ByteRTCAudioRoute)audioRoute;
#pragma mark Combined to Push
/** 
 * @type api
 * @region 转推直播
 * @author wanghaoxu
 * @brief 新增转推直播任务，并设置合流的图片、视频视图布局和音频属性。  <br>
 *        同一个任务中转推多路直播流时，SDK 会先将多路流合成一路流，然后再进行转推。
 * @param task_id 转推直播任务 ID。<br>
 *               你可以在同一房间内发起多个转推直播任务，并用不同的任务 ID 加以区。当你需要发起多个转推直播任务时，应使用多个 ID；当你仅需发起一个转推直播任务时，建议使用空字符串。
 * @param transcoding 转推直播配置参数，详见 ByteRTCLiveTranscoding{@link #ByteRTCLiveTranscoding}。
 * @param observer 端云一体转推直播观察者。详见 LiveTranscodingDelegate{@link #LiveTranscodingDelegate}。  <br>
 *        通过注册 observer 接收转推直播相关的回调。
 * @notes  <br>
 *       + 调用该方法后，启动结果和推流过程中的错误均会通过回调 onStreamMixingEvent:taskId:error:mixType:{@link #LiveTranscodingDelegate#onStreamMixingEvent:taskId:error:mixType:} 通知用户。
 *       + 调用 stopLiveTranscoding:{@link #ByteRTCVideo#stopLiveTranscoding:} 停止转推直播
 */
- (int)startLiveTranscoding:(NSString * _Nonnull)task_id transcoding:(ByteRTCLiveTranscoding *_Nullable)transcoding observer:(id<LiveTranscodingDelegate> _Nullable)observer;
/** 
 * @type api
 * @region 转推直播
 * @brief 停止转推直播，会收到 onStreamMixingEvent:taskId:error:mixType:{@link #LiveTranscodingDelegate#onStreamMixingEvent:taskId:error:mixType:} 回调。  <br>
 *        关于启动转推直播，参看 startLiveTranscoding:transcoding:observer:{@link #ByteRTCVideo#startLiveTranscoding:transcoding:observer:}。
 * @param task_id 转推直播任务 ID。可以指定想要停止的转推直播任务。
 * @return 方法调用结果。  <br>
 *         +  0：方法调用成功  <br>
 *         + < 0：方法调用失败
 */
- (int)stopLiveTranscoding:(NSString *_Nonnull)task_id;
/** 
 * @type api
 * @region 多房间
 * @author shenpengliang
 * @brief 更新转推直播参数，会收到 onStreamMixingEvent:taskId:error:mixType:{@link #LiveTranscodingDelegate#onStreamMixingEvent:taskId:error:mixType:} 回调。  <br>
 *        开启转推直播功能后，你可以使用此方法更新合流转推功能配置参数。
 * @param task_id 转推直播任务 ID。指定想要更新参数设置的转推直播任务。
 * @param transcoding 配置参数，详见 ByteRTCLiveTranscoding{@link #ByteRTCLiveTranscoding} 。
 * @return 方法调用结果。  <br>
 *         +  0：方法调用成功  <br>
 *         + < 0：方法调用失败
 */
- (int)updateLiveTranscoding:(NSString *_Nonnull)task_id transcoding:(ByteRTCLiveTranscoding *_Nonnull)transcoding;

#pragma mark oush single streaming
/** 
 * @hidden not available in 343
 * @type api
 * @region 转推直播
 * @author liqi.ritchie
 * @brief 新增单流转推直播任务。
 * @param task_id 任务 ID。<br>
 *               你可以发起多个转推直播任务，并用不同的任务 ID 加以区分。当你需要发起多个转推直播任务时，应使用多个 ID；当你仅需发起一个转推直播任务时，建议使用空字符串。
 * @param singleStream 转推直播配置参数。详见 ByteRTCPushSingleStreamParam{@link #ByteRTCPushSingleStreamParam}。
 * @param observer 单流转推直播观察者。详见 ByteRTCPushSingleStreamToCDNObserver{@link #ByteRTCPushSingleStreamToCDNObserver}。  <br>
 *        通过注册 observer 接收单流转推直播相关的回调。
 * @notes  <br>
 *       + 调用该方法后，关于启动结果和推流过程中的错误，会收到 onStreamPushEvent:taskId:error:{@link #ByteRTCPushSingleStreamToCDNObserver#onStreamPushEvent:taskId:error:} 回调。
 *       + 调用 stopPushStreamToCDN:{@link #RTCVideo#stopPushStreamToCDN:} 停止任务。
 */
- (int)startPushSingleStreamToCDN:(NSString *_Nonnull)task_id singleStream:(ByteRTCPushSingleStreamParam *_Nonnull)singleStream observer:(id<ByteRTCPushSingleStreamToCDNObserver>_Nullable)observer;
/** 
 * @hidden not available in 343
 * @type api
 * @region 转推直播
 * @author liqi.ritchie
 * @brief 停止转推直播。<br>
 *        关于启动转推直播，参看 startPushStreamToCDN:singleStream:observer:{@link #RTCVideo#startPushStreamToCDN:singleStream:observer:}。
 * @param taskId 任务 ID。可以指定想要停止的单流转推直播任务。
 */
- (int)stopPushStreamToCDN:(NSString *_Nonnull)task_id;

#pragma mark public streaming
/** 
 * @type api
 * @author qipengxiang
 * @brief 发布一路公共流<br>
 *        公共流是指不属于任何房间，也不属于任何用户的媒体流。使用同一 `appID` 的用户，可以调用 startPlayPublicStream:{@link #ByteRTCVideo#startPlayPublicStream:} 获取和播放指定的公共流。
 * @param publicStreamId 公共流 ID。<br>
 * @param publicStream 公共流参数。详见 ByteRTCPublicStreaming{@link #ByteRTCPublicStreaming}。<br>
 *              一路公共流可以包含多路房间内的媒体流，按照指定的布局方式进行聚合。<br>
 *              如果指定的媒体流还未发布，则公共流将在指定流开始发布后实时更新。
 * @return
 *        + 0: 成功。同时将收到 rtcEngine:onPushPublicStreamResult:publiscStreamId:errorCode:{@link #ByteRTCVideoDelegate#rtcEngine:onPushPublicStreamResult:publiscStreamId:errorCode:} 回调。<br>
 *        + !0: 失败。当参数不合法或参数为空，调用失败。<br>
 * @notes  <br>
 *        + 同一用户使用同一公共流 ID 多次调用本接口无效。如果你希望更新公共流参数，调用 updatePublicStreamParam:withLayout:{@link #ByteRTCVideo#updatePublicStreamParam:withLayout:} 接口。<br>
 *        + 不同用户使用同一公共流 ID 多次调用本接口时，RTC 将使用最后一次调用时传入的参数更新公共流。<br>
 *        + 使用不同的 ID 多次调用本接口可以发布多路公共流。<br>
 *        + 调用 stopPushPublicStream:{@link #ByteRTCVideo#stopPushPublicStream:} 停止发布公共流。
 */
- (int)startPushPublicStream:(NSString * _Nonnull)publicStreamId withLayout:(ByteRTCPublicStreaming *_Nullable)publicStream;
/** 
 * @type api
 * @author qipengxiang
 * @brief 停止发布当前用户发布的公共流<br>
 *        关于发布公共流，查看 startPushPublicStream:withLayout:{@link #ByteRTCVideo#startPushPublicStream:withLayout:}。
 * @param publicStreamId 公共流 ID<br>
 *                  指定的流必须为当前用户所发布。
 * @return
 *        + 0: 成功<br>
 *        + !0: 失败<br>
 */
- (int)stopPushPublicStream:(NSString * _Nonnull)publicStreamId;

/** 
 * @type api
 * @author qipengxiang
 * @brief 更新公共流参数<br>
 *        关于发布公共流，查看 startPushPublicStream:withLayout:{@link #ByteRTCVideo#startPushPublicStream:withLayout:}。
 * @param publicStreamId 公共流ID<br>
 *              指定的流必须为当前用户所发布的。
 * @param publicStream 推公共流配置参数。详见 ByteRTCPublicStreaming{@link #ByteRTCPublicStreaming}。
 * @return
 *        + 0: 成功<br>
 *        + !0: 失败<br>
 */
- (int)updatePublicStreamParam:(NSString * _Nonnull)publicStreamId withLayout:(ByteRTCPublicStreaming *_Nullable)publicStream;
/** 
 * @type api
 * @author qipengxiang
 * @brief 订阅指定公共流<br>
 *        无论用户是否在房间内，都可以调用本接口获取和播放指定的公共流。
 * @param publicStreamId 公共流ID，如果指定流暂未发布，则本地客户端将在其开始发布后接收到流数据。<br>
 * @return <br>
 *        + 0: 成功。同时将收到 rtcEngine:onPlayPublicStreamResult:errorCode:{@link #ByteRTCVideoDelegate#rtcEngine:onPlayPublicStreamResult:errorCode:} 回调。<br>
 *        + !0: 失败。当参数不合法或参数为空，调用失败。<br>
 * @notes  <br>
 *        + 在调用本接口之前，建议先绑定渲染视图。<br>
 *              - 调用 setPublicStreamVideoCanvas:withCanvas:{@link #ByteRTCVideo#setPublicStreamVideoCanvas:withCanvas:} 绑定内部渲染视图。<br>
 *              - 调用 setPublicStreamVideoSink:withSink:withPixelFormat:{@link #ByteRTCVideo#setPublicStreamVideoSink:withSink:withPixelFormat:} 绑定自定义渲染视图：<br>
 *        + 调用本接口后，可以通过 rtcEngine:onFirstPublicStreamVideoFrameDecoded:withFrameInfo:{@link #ByteRTCVideoDelegate#rtcEngine:onFirstPublicStreamVideoFrameDecoded:withFrameInfo:} 和 rtcEngine:onFirstPublicStreamAudioFrame:{@link #ByteRTCVideoDelegate#rtcEngine:onFirstPublicStreamAudioFrame:} 回调公共流的视频和音频首帧解码情况。<br>
 *        + 调用本接口后，可以通过 rtcEngine:onPublicStreamSEIMessageReceived:andMessage:{@link #ByteRTCVideoDelegate#rtcEngine:onPublicStreamSEIMessageReceived:andMessage:} 回调公共流中包含的 SEI 信息。<br>
 *        + 订阅公共流之后，可以通过调用 stopPlayPublicStream:{@link ByteRTCVideo#stopPlayPublicStream:} 接口取消订阅公共流。
 */
- (int)startPlayPublicStream:(NSString * _Nonnull)publicStreamId;
/** 
 * @type api
 * @author qipengxiang
 * @brief 取消订阅指定公共流<br>
 *        关于订阅公共流，查看 startPlayPublicStream:{@link #ByteRTCVideo#startPlayPublicStream:}。
 * @param publicStreamId 公共流ID
 * @return  <br>
 *        + 0：成功  <br>
 *        + !0：失败  <br>
 */
- (int)stopPlayPublicStream:(NSString * _Nonnull)publicStreamId;

/** 
 * @type api
 * @author qipengxiang
 * @brief 为指定公共流绑定内部渲染视图。  <br>
 * @param publicStreamId 公共流ID
 * @param canvas 内部渲染视图，如果需要解除视频的绑定视图，把 videoCanvas 设置为空。详见 ByteRTCVideoCanvas{@link #ByteRTCVideoCanvas}
 * @return  <br>
 *        + 0：成功  <br>
 *        + !0：失败  <br>
 */
- (int)setPublicStreamVideoCanvas:(NSString *_Nonnull)publicStreamId withCanvas:(ByteRTCVideoCanvas * _Nullable)canvas;

/** 
 * @type api
 * @author qipengxiang
 * @brief 为指定公共流绑定自定义渲染器。详见[自定义视频渲染](https://www.volcengine.com/docs/6348/81201)。
 * @param publicStreamId 公共流ID
 * @param videoSink 自定义视频渲染器，需要释放渲染器资源时，将 videoSink 设置为 `null`。参看 ByteRTCVideoSinkDelegate{@link #ByteRTCVideoSinkDelegate}
 * @param requiredFormat videoSink 适用的视频帧编码格式，参看 ByteRTCVideoSinkPixelFormat{@link #ByteRTCVideoSinkPixelFormat}
 * @return  <br>
 *        + 0: 成功  <br>
 *        + <0: 失败  <br>
 */
- (int)setPublicStreamVideoSink:(NSString *_Nonnull)publicStreamId
                       withSink:(id<ByteRTCVideoSinkDelegate> _Nullable)videoSink
                withPixelFormat:(ByteRTCVideoSinkPixelFormat)requiredFormat;
#pragma mark External Video Data
// @name custom video capture


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
 * @notes <br>
 *       + 支持的格式：NV12, BGRA, ARGB<br>
 *       + 推送外部视频帧前，必须调用 setVideoSourceType:WithStreamIndex:{@link #ByteRTCVideo#setVideoSourceType:WithStreamIndex:} 开启外部视频源采集。
 */
- (BOOL)pushExternalVideoFrame:(CVPixelBufferRef _Nonnull )frame time:(CMTime)pts;
/** 
 * @type api
 * @region 自定义视频采集渲染
 * @author zhangzhenyu.samuel
 * @brief 推送外部视频帧。
 * @param frame 该视频帧包含待 SDK 编码的视频数据
 * @param pts CMTime
 * @param rotation 当前视频角度，参看 ByteRTCVideoRotationMode{@link #ByteRTCVideoRotationMode}
 * @return  <br>
 *         + YES 推送成功  <br>
 *         + NO 推送失败  <br>
 * @notes <br>
 *       + 支持的格式：NV12, BGRA, ARGB<br>
 *       + 推送外部视频帧前，必须调用 setVideoSourceType:WithStreamIndex:{@link #ByteRTCVideo#setVideoSourceType:WithStreamIndex:} 开启外部视频源采集。
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
 * @notes <br>
 *       + 支持的格式：NV12, BGRA, ARGB<br>
 *       + 推送外部视频帧前，必须调用 setVideoSourceType:WithStreamIndex:{@link #ByteRTCVideo#setVideoSourceType:WithStreamIndex:} 开启外部视频源采集。
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
 * @notes 推送外部视频帧前，必须调用 setVideoSourceType:WithStreamIndex:{@link #ByteRTCVideo#setVideoSourceType:WithStreamIndex:} 开启外部视频源采集。
 */
- (BOOL)pushExternalByteVideoFrame:(ByteRTCVideoFrame * _Nonnull)frame;

#pragma mark External Audio Data
/** 
 * @type api
 * @region 音频数据回调
 * @author wangjunzheng
 * @brief 开启音频回调
 * @param method 音频回调方法，参看 ByteRTCAudioFrameCallbackMethod{@link #ByteRTCAudioFrameCallbackMethod}。  <br>
 *               当音频回调方法设置为 `0`、`1`、`2`时，你需要在参数 `format` 中指定准确的采样率和声道，暂不支持设置为自动。  <br>
 *               当音频回调方法设置为 `3`时，暂不支持音频参数格式中设置准确的采样率和声道，你需要设置为自动。
 * @param format 音频参数格式，参看 ByteRTCAudioFormat{@link #ByteRTCAudioFormat}。
 * @notes 开启音频回调并调用 setAudioFrameObserver:{@link #ByteRTCVideo#setAudioFrameObserver:} 后，ByteRTCAudioFrameObserver{@link #ByteRTCAudioFrameObserver} 会收到对应的音频回调。两者调用顺序没有限制且相互独立。  <br>
 */
- (void)enableAudioFrameCallback:(ByteRTCAudioFrameCallbackMethod) method format:(ByteRTCAudioFormat* _Nullable)format;
/** 
 * @type api
 * @region 音频数据回调
 * @author wangjunzheng
 * @brief 关闭音频回调
 * @param method 音频回调方法，参看 ByteRTCAudioFrameCallbackMethod{@link #ByteRTCAudioFrameCallbackMethod}。
 * @notes 该方法需要在调用 enableAudioFrameCallback:format:{@link #ByteRTCVideo#enableAudioFrameCallback:format:} 之后调用。
 */
- (void)disableAudioFrameCallback:(ByteRTCAudioFrameCallbackMethod) method;
/** 
 * @type api
 * @region 音频数据回调
 * @author wangjunzheng
 * @brief 注册音频数据回调观察者。  <br>
 * @param audioFrameObserver 音频数据观察者，参看 ByteRTCAudioFrameObserver{@link #ByteRTCAudioFrameObserver}。如果传入 null，则取消注册。
 * @return  <br>
 *        + 0: 方法调用成功 <br>
 *        + < 0: 方法调用失败 <br>
 * @notes 注册音频数据回调观察者并调用 enableAudioFrameCallback:format:{@link #ByteRTCVideo#enableAudioFrameCallback:format:} 后，ByteRTCAudioFrameObserver{@link #ByteRTCAudioFrameObserver} 会收到对应的音频回调。
 */
- (BOOL)setAudioFrameObserver:(_Nullable id<ByteRTCAudioFrameObserver>) audioFrameObserver;
/** 
 * @type api
 * @hidden
 * @deprecated since 342, use registerAudioProcessor instead.
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
* @author majun.lvhiei
* @brief 注册自定义音频处理器。<br>
*        注册完成后，你可以调用 enableAudioProcessor:audioFormat:{@link #ByteRTCVideo#enableAudioProcessor:audioFormat:}，对本地采集或接收到的远端音频进行处理。
* @param processor 自定义音频处理器，详见 ByteRTCAudioFrameProcessor{@link #ByteRTCAudioFrameProcessor}。<br>
*        SDK 只持有 processor 的弱引用，你应保证其生命周期。
* @notes 重复调用此接口时，仅最后一次调用生效。
*/
- (BOOL)registerAudioProcessor:(_Nullable id<ByteRTCAudioFrameProcessor>)processor;
/** 
* @type api
* @author majun.lvhiei
* @brief 获取本地采集的音频帧或接收到的远端音频帧，进行自定义处理。
* @param method 音频帧类型，参看 ByteRTCAudioFrameMethod{@link #ByteRTCAudioFrameMethod}。通过多次调用此接口，可以对不同的音频帧进行自定义处理。<br>
*        选择不同的值时，收到的回调不同：<br>
*        + 选择本地采集的音频时，会收到 onProcessRecordAudioFrame:{@link #ByteRTCAudioFrameProcessor#onProcessRecordAudioFrame:} <br>
*        + 选择远端音频流的混音音频时，会收到 onProcessPlayBackAudioFrame:{@link #ByteRTCAudioFrameProcessor#onProcessPlayBackAudioFrame:} <br>
*        + 选择远端音频流时，会收到 onProcessRemoteUserAudioFrame:audioFrame:{@link #ByteRTCAudioFrameProcessor#onProcessRemoteUserAudioFrame:audioFrame:} <br>
* @param format 设定自定义处理时获取的音频帧格式，参看 ByteRTCAudioFormat{@link #ByteRTCAudioFormat}。
* @notes <br>
*        + 在调用此接口前，你需要调用 registerAudioProcessor:{@link #ByteRTCVideo#registerAudioProcessor:} 注册自定义音频处理器。<br>
*        + 要关闭音频自定义处理，调用 disableAudioProcessor:{@link #ByteRTCVideo#disableAudioProcessor:}。
*/
- (void)enableAudioProcessor:(ByteRTCAudioFrameMethod)method
                 audioFormat:(ByteRTCAudioFormat *_Nullable)format;
/** 
* @type api
* @author majun.lvhiei
* @brief 关闭自定义音频处理。
* @param method 音频帧类型，参看 ByteRTCAudioFrameMethod{@link #ByteRTCAudioFrameMethod}。
*/
- (void)disableAudioProcessor:(ByteRTCAudioFrameMethod)method;
/** 
 * @type api
 * @region 自定义音频采集渲染
 * @author dixing
 * @brief 推送自定义采集的音频数据到 RTC SDK。
 * @param audioFrame 音频数据帧，详见 ByteRTCAudioFrame{@link #ByteRTCAudioFrame}
 * @return  方法调用结果  <br>
 *          + 0: 设置成功  <br>
 *          + < 0: 设置失败  <br>
 * @notes  <br>
 *       + 推送外部音频数据前，必须先调用 setAudioSourceType:{@link #ByteRTCVideo#setAudioSourceType:} 开启自定义采集。<br>
 *       + 你必须每隔 10 毫秒推送一次外部采集的音频数据。单次推送的 samples (音频采样点个数）应该为 audioFrame.sampleRate / 100。比如设置采样率为 48000 时， 每次应该推送 480 个采样点。  <br>
 *       + 本方法中设置的 sampleRate（音频采样率） 和 channel（音频声道） 必须与 setAudioSourceType:{@link #ByteRTCVideo#setAudioSourceType:} 中设置的一致。  <br>
 *       + 音频采样格式为 S16。音频缓冲区内的数据格式必须为 PCM 数据，其容量大小应该为 audioFrame.samples × audioFrame.channel × 2。  <br>
 */
 - (int)pushExternalAudioFrame:(ByteRTCAudioFrame * _Nonnull) audioFrame;
/** 
 * @type api
 * @region 自定义音频采集渲染
 * @author dixing
 * @brief 拉取音频数据，用于自定义渲染。
 * @param audioFrame 音频数据帧，详见 ByteRTCAudioFrame{@link #ByteRTCAudioFrame}
 * @return  方法调用结果  <br>
 *        + 0: 设置成功  <br>
 *        + < 0: 设置失败  <br>
 * @notes  <br>
 *       + 拉取外部音频数据前，必须先调用 setAudioRenderType:{@link #ByteRTCVideo#setAudioRenderType:} 开启自定义渲染。<br>
 *       + 你应当每隔 10 毫秒拉取一次音频数据。samples (音频采样点个数）应该为 audioFrame.sampleRate / 100。如设置采样率为 48000 时， 每次应该拉取 480 个采样点。  <br>
 *       + 本方法中设置的 sampleRate（音频采样率） 和 channel（音频声道） 必须与 setAudioRenderType:{@link #ByteRTCVideo#setAudioRenderType:} 中设置的一致，和远端音频采集设置无关。  <br>
 *       + 音频采样格式为 S16。音频缓冲区内的数据格式必须为 PCM 数据，其容量大小应该为 audioFrame.samples × audioFrame.channel × 2。  <br>
 */
 - (int)pullExternalAudioFrame:(ByteRTCAudioFrame * _Nonnull) audioFrame;
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
 *         + < 0: 调用失败  <br>
 */
- (int)setRtcMode:(ByteRTCMode)mode;
/** 
 * @hidden
 * @type api
 * @region 游戏接口
 * @author shazhou
 * @brief 向小队或世界发音频，在创建引擎实例后调用。
 * @param mode 模式选择，向小队发送或者向世界发送。详见 RangeAudioMode{@link #RangeAudioMode}。
 * @return 方法调用结果  <br>
 *         + 0: 调用成功  <br>
 *         + < 0: 调用失败  <br>
 */
- (int)setAudioSendMode:(ByteRTCRangeAudioMode)mode;
/** 
 * @hidden
 * @type api
 * @region 游戏接口
 * @author shazhou
 * @brief 收听小队或世界音频，在创建引擎实例后调用。
 * @param mode 模式选择，收听小队或者世界音频。详见 RangeAudioMode{@link #RangeAudioMode}。
 * @return 方法调用结果  <br>
 *         + 0: 调用成功  <br>
 *         + < 0: 调用失败  <br>
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
 *         + < 0: 调用失败  <br>
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
 *        + < 0： 调用失败  <br>
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
 *        + < 0：调用失败  <br>
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
 *        + < 0：调用失败  <br>
 * @notes
 *         如果开启区域语音，非队友之间在收发世界模式下语音会根据用户之间的距离衰减，超过收听范围就听不到，如果关闭区域语音，非队友之间在收发世界模式下，语音不会随距离衰减
 */
- (int)enableRangeAudio:(BOOL) enable;
/** 
 * @type api
 * @region 引擎管理
 * @author chenweiming.push
 * @brief 设置业务标识参数  <br>
 *        可通过 businessId 区分不同的业务场景。businessId 由客户自定义，相当于一个“标签”，可以分担和细化现在 AppId 的逻辑划分的功能，但不需要鉴权。
 * @param businessId  <br>
 *        用户设置的自己的 businessId 值
 *        businessId 只是一个标签，颗粒度需要用户自定义。
 * @return  <br>
 *        + 0： 成功  <br>
 *        + < 0： 失败  <br>
 *        + -6001： 用户已经在房间中。  <br>
 *        + -6002： 输入非法，合法字符包括所有小写字母、大写字母和数字，除此外还包括四个独立字符分别是：英文句号，短横线，下划线和 @ 。
 * @notes  <br>
 *        + 需要在调用 joinRoomByToken:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoomByToken:userInfo:roomConfig:} 之前调用，joinRoomByToken:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoomByToken:userInfo:roomConfig:}之后调用该方法无效。
 */
- (int)setBusinessId:(NSString* _Nullable)businessId;
/** 
 * @type api
 * @region 引擎管理
 * @author chenweiming.push
 * @brief 通话结束，将用户反馈的问题上报到 RTC <br>
 * @param types 预设问题列表，参看 ByteRTCProblemOption{@link #ByteRTCProblemOption}  <br>
 * @param desc 预设问题以外的其他问题的具体描述  <br>
 * @return <br>
 *         + 0: 上报成功  <br>
 *         + -1: 上报失败，还没加入过房间 <br>
 *         + -2: 上报失败，数据解析错误  <br>
 *         + -3: 上报失败，字段缺失  <br>
 * @notes 如果用户上报时在房间内，那么问题会定位到用户当前所在的一个或多个房间；
 *        如果用户上报时不在房间内，那么问题会定位到引擎此前退出的房间。
 */
- (int)feedback:(NSArray<ByteRTCProblemOption *> * _Nullable)types desc:(NSString* _Nullable)desc;
#pragma mark Monitor Related
// @name monitoring related api
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
 *        + 必须在 createRTCVideo:delegate:parameters:{@link #ByteRTCVideo#createRTCVideo:delegate:parameters:} 前设置。  <br>
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
#pragma mark Fallback Related
/** 
 * @type api
 * @region 音视频回退
 * @author panjian.fishing
 * @brief 设置发布的音视频流的回退选项。  <br>
 *        你可以调用该接口设置网络不佳或设备性能不足时从大流起进行降级处理，以保证通话质量。
 * @param option 本地发布的音视频流回退选项，参看 ByteRTCPublishFallbackOption{@link #ByteRTCPublishFallbackOption}。  <br>
 * @return 方法调用结果： <br>
 *        + 0：成功  <br>
 *        + < 0：失败
 * @notes  <br>
 *        + 该方法仅在调用 enableSimulcastMode:{@link #ByteRTCVideo#enableSimulcastMode:} 开启了发送多路视频流的情况下生效。  <br>
 *        + 该方法必须在进房前设置，进房后设置或更改设置无效。  <br>
 *        + 设置回退后，本地发布的音视频流发生回退或从回退中恢复时，远端会收到 rtcEngine:OnSimulcastSubscribeFallback:{@link #ByteRTCVideoDelegate#rtcEngine:OnSimulcastSubscribeFallback:} 回调通知。  <br>
 *        + 你可以调用客户端 API 或者在服务端下发策略设置回退。当使用服务端下发配置实现时，下发配置优先级高于在客户端使用 API 设定的配置。
 */
- (int)setPublishFallbackOption:(ByteRTCPublishFallbackOption)option;
/** 
 * @type api
 * @region 音视频回退
 * @author panjian.fishing
 * @brief 设置订阅的音视频流的回退选项。 <br>
 *        你可调用该接口设置网络不佳或设备性能不足时允许订阅流进行降级或只订阅音频流，以保证通话流畅。
 * @param option 订阅的音视频流回退选项，参看 ByteRTCSubscribeFallbackOption{@link #ByteRTCSubscribeFallbackOption} 。
 * @return 方法调用结果： <br>
 *        + 0：成功  <br>
 *        + < 0：失败
 * @notes  <br>
 *        + 你必须在进房前设置，进房后设置或更改设置无效。  <br>
 *        + 设置回退选项后，订阅的音视频流发生回退或从回退中恢复时，会收到 rtcEngine:OnSimulcastSubscribeFallback:{@link #ByteRTCVideoDelegate#rtcEngine:OnSimulcastSubscribeFallback:} 和 rtcEngine:onRemoteVideoSizeChanged:withFrameInfo:{@link #ByteRTCVideoDelegate#rtcEngine:onRemoteVideoSizeChanged:withFrameInfo:} 回调通知。  <br>
 *        + 你可以调用 API 或者在服务端下发策略设置回退。当使用服务端下发配置实现时，下发配置优先级高于在客户端使用 API 设定的配置。
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
 *         + < 0：方法调用失败  <br>
 * @notes  <br>
 *        + 该方法与 setSubscribeFallbackOption:{@link #setSubscribeFallbackOption:}  搭配使用。  <br>
 *        + 如果开启了订阅流回退选项，弱网或性能不足时会优先保证收到的高优先级用户的流的质量。  <br>
 *        + 该方法在进房前后都可以使用，可以修改远端用户的优先级。
 */
- (int)setRemoteUserPriority:(ByteRTCRemoteUserPriority)priority
                         InRoomId:(NSString *_Nonnull)roomId
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
 *       + 该方法必须在调用 joinRoomByToken:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoomByToken:userInfo:roomConfig:}
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
 * @brief 创建房间
 *        多次调用此方法以创建多个 ByteRTCRoom 实例。分别调用各 ByteRTCRoom 实例中的 joinRoomByToken:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoomByToken:userInfo:roomConfig:} 方法，同时加入多个房间。多房间模式下，用户可以同时订阅各房间的音视频流。<br>
 * @param roomId 标识通话房间的房间 ID，最大长度为 128 字节的非空字符串。支持的字符集范围为:  <br>
 *        + 26个大写字母 A ~ Z  <br>
 *       + 26个小写字母 a ~ z  <br>
 *       + 10个数字 0 ~ 9  <br>
 *       + 下划线 "_", at 符 "@", 减号 "-"  <br>
 *        多房间模式下，调用创建房间接口后，请勿调用同样的 roomID 创建房间，否则会导致创建房间失败。  <br>
 * @return `ByteRTCRoom` 实例 <br>
 * @notes  如果你需要在多个房间发布音视频流，无须创建多房间，直接调用 startForwardStreamToRooms:{@link #ByteRTCRoom#startForwardStreamToRooms:}。
 */
- ( ByteRTCRoom * _Nullable)createRTCRoom:(NSString * _Nonnull)roomId;
#pragma mark - ScreenCapture
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
 * @hidden(macOS)
 * @type api
 * @region 屏幕共享
 * @author wangzhanqiang
 * @brief 设置 Extension 配置项。你必须在使用屏幕内部采集功能前，设置使用的 Extension。
 * @param groupId 你的应用和 Extension 应该归属于同一个 App Group，此处需要传入 Group Id。
 * @notes 必须在调用 createRTCVideo:delegate:parameters:{@link #ByteRTCVideo#createRTCVideo:delegate:parameters:} 之后立即调用此方法。在引擎实例的生命周期中，此方法只需要调用一次。  <br>
 */
- (void)setExtensionConfig:(NSString *_Nullable)groupId;
/** 
 * @type api
 * @hidden(macOS)
 * @region 屏幕共享
 * @author wangzhanqiang
 * @brief 使用 RTC SDK 内部采集模块开始采集屏幕音频流和（或）视频流。
 * @param type 媒体类型，参看 ByteRTCScreenMediaType{@link #ByteRTCScreenMediaType}。
 * @param bundleId 绑定 Extension 的 Bundle ID，绑定后应用中共享屏幕的选择列表中只展示你的 Extension 可供选择。
 * @notes <br>
 *      + 当从 iOS 控制中心发起屏幕采集时无需调用本方法。 <br>
 *      + 采集后，你还需要调用 publishScreen:{@link #ByteRTCRoom#publishScreen:} 发布采集到的屏幕音视频。<br>
 *      + 开启屏幕音频/视频采集成功后，本地用户会收到 rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:} 和 rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:} 回调。
 */
- (void)startScreenCapture:(ByteRTCScreenMediaType) type bundleId:(NSString *_Nullable)bundleId;
/** 
 * @type api
 * @region 屏幕共享
 * @author wangzhanqiang
 * @brief 更新内部屏幕采集时采集的媒体类型。
 * @param type 媒体类型，参看 ByteRTCScreenMediaType{@link #ByteRTCScreenMediaType}。
 * @notes <br>
 *      + 你需在开启屏幕视频流采集后调用该方法。
 *      + 本地用户会收到 rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:} 或 rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:} 回调。
 */
- (void)updateScreenCapture:(ByteRTCScreenMediaType) type;
/** 
 * @type api
 * @region 屏幕共享
 * @author wangzhanqiang
 * @brief 在屏幕共享时，停止使用 RTC SDK 内部采集方式采集屏幕音视频。
 * @notes <br>
 *     + 本方法只会停止本地屏幕采集，并不会影响屏幕流的发布状态。
 *     + 本地用户会收到 rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:} 和 rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:} 的回调。 <br>
 */
- (void)stopScreenCapture;
/** 
 * @hidden(macOS)
 * @type api
 * @region 屏幕共享
 * @author wangzhanqiang
 * @brief 向屏幕共享 Extension 发送自定义消息
 * @param messsage 发送给 Extension 的消息内容
 * @notes 在 startScreenCapture:bundleId:{@link #ByteRTCVideo#startScreenCapture:bundleId:} 后调用该方法。
 */
- (void)sendScreenCaptureExtensionMessage:(NSData *_Nonnull) messsage;
/** 
 * @hidden
 * @type api
 * @author dixing
 * @brief 音频设备管理接口创建，该接口不依赖引擎
 * @param handler 音频设备的事件回调，参看 ByteRTCAudioDeviceEventHandler{@link #ByteRTCAudioDeviceEventHandler}
 * @return 音频设备管理接口
 */
+ (ByteRTCAudioDeviceManager *_Null_unspecified)createAudioDeviceManager:(id<ByteRTCAudioDeviceEventHandler> _Nonnull)handler;
/** 
 * @type api
 * @brief 设置运行时的参数
 * @param parameters 保留参数
 */
- (void)setRuntimeParameters:(NSDictionary * _Nullable)parameters;
#if BYTERTC_TARGET_MAC
/** 
 * @type api
 * @hidden(iOS)
 * @region 屏幕共享
 * @author liyi.000
 * @brief 获取共享对象(应用窗口和桌面)列表。
 * @return 共享对象(应用窗口和桌面)列表。参看 ByteRTCScreenCaptureSourceInfo{@link #ByteRTCScreenCaptureSourceInfo}。<br>
 *         枚举值可作为调用 startScreenCaptureSourceInfo:captureParameters:{@link #ByteRTCVideo#startScreenCaptureSourceInfo:captureParameters:} 开启屏幕共享时的输入参数。
 * @notes 仅桌面端可用。
 */
- (NSArray<ByteRTCScreenCaptureSourceInfo *> *_Nonnull)getScreenCaptureSourceList;
/** 
 * @type api
 * @hidden(iOS)
 * @region 屏幕共享
 * @author liyi.000
 * @brief 采集屏幕视频流，用于共享。屏幕视频流包括：屏幕上显示的内容，或应用窗口中显示的内容。<br>
 * @param sourceInfo 待共享的屏幕源，参看 ByteRTCScreenCaptureSourceInfo{@link #ByteRTCScreenCaptureSourceInfo}。<br>
 *                   你可以调用 getScreenCaptureSourceList{@link #ByteRTCVideo#getScreenCaptureSourceList} 获得所有可以共享的屏幕源。
 * @param captureParameters 共享参数。参看 ByteRTCScreenCaptureParam{@link #ByteRTCScreenCaptureParam}。
 * @return  <br>
 *        + 0: 成功  <br>
 *        + -1: 失败  <br>
 * @notes  <br>
 *       + 调用此方法仅开启屏幕流视频采集，不会发布采集到的视频。发布屏幕流视频需要调用 publishScreen:{@link #ByteRTCRoom#publishScreen:}。<br>
 *       + 调用 stopScreenCapture{@link #ByteRTCVideo#stopScreenCapture} 关闭屏幕视频源采集。  <br>
 *       + 本地用户通过 rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:} 的回调获取屏幕采集状态，包括开始、暂停、恢复、错误等。  <br>
 *       + 调用成功后，本端会收到 rtcEngine:onFirstLocalVideoFrameCaptured:withFrameInfo:{@link #ByteRTCVideoDelegate#rtcEngine:onFirstLocalVideoFrameCaptured:withFrameInfo:} 回调。  <br>
 *       + 调用此接口前，你可以调用 SetScreenVideoEncoderConfig:{@link #ByteRTCVideo#SetScreenVideoEncoderConfig:} 设置屏幕视频流的采集帧率和编码分辨率。  <br>
 *       + 在收到 rtcEngine:onFirstLocalVideoFrameCaptured:withFrameInfo:{@link #ByteRTCVideoDelegate#rtcEngine:onFirstLocalVideoFrameCaptured:withFrameInfo:} 回调后，通过调用 setLocalVideoCanvas:withCanvas:{@link #ByteRTCVideo#setLocalVideoCanvas:withCanvas:} 或 setLocalVideoSink:withSink:withPixelFormat:{@link #ByteRTCVideo#setLocalVideoSink:withSink:withPixelFormat:} 函数设置本地屏幕共享视图。  <br>
 */
- (int)startScreenCaptureSourceInfo:(ByteRTCScreenCaptureSourceInfo *_Nonnull)sourceInfo captureParameters:(ByteRTCScreenCaptureParam *_Nonnull)captureParameters;
/** 
 * @hidden(iOS)
 * @type api
 * @region 屏幕共享
 * @author liyi.000
 * @brief 停止屏幕视频流采集。
 * @notes  <br>
 *       + 要开启屏幕视频流采集，调用 startScreenCaptureSourceInfo:captureParameters:{@link #ByteRTCVideo#startScreenCaptureSourceInfo:captureParameters:}。  <br>
 *       + 调用后，本地用户会收到 rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:} 的回调。  <br>
 *       + 调用此接口不影响屏幕视频流发布。  <br>
 */
- (void)stopScreenVideoCapture;
/** 
 * @type api
 * @hidden(iOS)
 * @region 屏幕共享
 * @author liyi.000
 * @brief 内部屏幕流采集时，更新采集区域。
 * @param regionRect 采集区域相对 startScreenCaptureSourceInfo:captureParameters:{@link #ByteRTCVideo#startScreenCaptureSourceInfo:captureParameters:} 中设定区域的值。
 * @notes 调用此接口前，必须先通过调用 startScreenCaptureSourceInfo:captureParameters:{@link #ByteRTCVideo#startScreenCaptureSourceInfo:captureParameters:} 开启了内部屏幕流采集。
 */
- (void)updateScreenCaptureRegion:(CGRect)regionRect;
/** 
 * @type api
 * @hidden(iOS)
 * @region 屏幕共享
 * @author liyi.000
 * @brief 内部屏幕流采集时，更新边框高亮设置。默认展示边框。
 * @param config 边框高亮设置。参见 ByteRTCHighlightConfig{@link #ByteRTCHighlightConfig}。
 * @notes 调用此接口前，必须已通过调用 startScreenCaptureSourceInfo:captureParameters:{@link #ByteRTCVideo#startScreenCaptureSourceInfo:captureParameters:} 开启了内部屏幕流采集。
 */
- (void)updateScreenCaptureHighlightConfig:(ByteRTCHighlightConfig *_Nonnull)config;
/** 
 * @type api
 * @hidden(iOS)
 * @region 屏幕共享
 * @author liyi.000
 * @brief 内部屏幕流采集时，更新对鼠标的处理设置。默认采集鼠标。
 * @param mouseCursorCaptureState 参看 ByteRTCMouseCursorCaptureState{@link #ByteRTCMouseCursorCaptureState}。
 * @notes 调用此接口前，必须已通过调用 startScreenCaptureSourceInfo:captureParameters:{@link #ByteRTCVideo#startScreenCaptureSourceInfo:captureParameters:} 开启了内部屏幕流采集。
 */
- (void)UpdateScreenCaptureMouseCursor:(ByteRTCMouseCursorCaptureState)mouseCursorCaptureState;
/** 
 * @type api
 * @hidden(iOS)
 * @region 屏幕共享
 * @author liyi.000
 * @brief 通过 RTC SDK 提供的采集模块采集屏幕视频流时，设置需要过滤的窗口。
 * @param excludedWindowList 过滤掉的窗口列表。
 * @notes <br>
 *       + 调用此接口前，必须已通过调用 startScreenCaptureSourceInfo:captureParameters:{@link #ByteRTCVideo#startScreenCaptureSourceInfo:captureParameters:} 开启了内部屏幕流采集。<br>
 *       + 本函数在屏幕源类别是屏幕而非应用窗体时才起作用。详见：ByteRTCScreenCaptureSourceType{@link #ByteRTCScreenCaptureSourceType}。
 */
- (void)UpdateScreenCaptureFilterConfig:(NSArray<NSNumber *> * _Nullable) excludedWindowList;;
/** 
 * @type api
 * @hidden(iOS)
 * @region 屏幕共享
 * @author panjian.fishing
 * @brief 获取屏幕采集对象缩略图
 * @param sourceType 屏幕采集对象的类型。详见 ByteRTCScreenCaptureSourceType{@link #ByteRTCScreenCaptureSourceType}。
 * @param sourceId 屏幕分享时，共享对象的 ID。可通过 getScreenCaptureSourceList{@link #ByteRTCVideo#getScreenCaptureSourceList} 返回的`ByteRTCScreenCaptureSourceInfo`共享对象列表中获取。
 * @param maxWidth 最大宽度。保持采集对象本身的宽高比不变，将缩略图缩放到指定范围内的最大宽高。如果给出的尺寸与共享对象比例不同，得到的缩略图会有黑边。
 * @param maxHeight 最大高度。参见 maxWidth 的说明。
 * @return 屏幕采集对象缩略图。缩略图由屏幕共享对象等比缩放而来。缩略图的大小小于等于此接口设定的尺寸。
 */
- (ByteRTCImage *_Nonnull)getScreenCaptureSourceThumbnail:(ByteRTCScreenCaptureSourceType)sourceType sourceId:(intptr_t)sourceId maxWidth:(int)maxWidth maxHeight:(int)maxHeight;
/** 
 * @hidden(iOS)
 * @brief 获取应用窗体所属应用的图标。
 * @region 屏幕共享
 * @author liyi.000
 * @param sourceId 屏幕共享对象的 ID，可通过 getScreenCaptureSourceList{@link #ByteRTCVideo#getScreenCaptureSourceList} 返回的`ByteRTCScreenCaptureSourceInfo`共享对象列表中获取。
 * @param width 最大宽度。返回的图标将是宽高相等的，输入的宽高不等时，取二者较小值。宽高范围为 [32,256]，超出该范围将返回 `nullptr`，默认输出 100 x 100 的图像。
 * @param height 最大高度。参见 `width` 的说明。
 * @return 应用图标。当屏幕共享对象为应用窗体时有效，否则返回 `nullptr`。
 */
 - (ByteRTCImage *_Nonnull)getWindowAppIcon:(intptr_t)sourceId width:(int)width height:(int)height;
#endif
/** 
 * @type api
 * @hidden(iOS)
 * @region 音频管理
 * @author dixing
 * @brief 创建音频设备管理实例
 * @return ByteRTCAudioDeviceManager{@link #ByteRTCAudioDeviceManager}
 */
- (ByteRTCAudioDeviceManager *_Null_unspecified)getAudioDeviceManager;
/** 
 * @type api
 * @hidden(iOS)
 * @region 视频设备管理
 * @author zhangzhenyu.samuel
 * @brief 创建视频设备管理实例
 * @return 视频设备管理实例，详见 ByteRTCVideoDeviceManager{@link #ByteRTCVideoDeviceManager}
 */
- (ByteRTCVideoDeviceManager * _Null_unspecified)getVideoDeviceManager;
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
 *        + 调用该方法后，你会收到 rtcEngine:onRecordingStateUpdate:state:error_code:recording_info:{@link #ByteRTCVideoDelegate#rtcEngine:onRecordingStateUpdate:state:error_code:recording_info:} 回调。  <br>
 *        + 如果录制正常，系统每秒钟会通过 rtcEngine:onRecordingProgressUpdate:process:recording_info:{@link #ByteRTCVideoDelegate#rtcEngine:onRecordingProgressUpdate:process:recording_info:} 回调通知录制进度。
 */
- (int)startFileRecording:(ByteRTCStreamIndex)streamIndex
      withRecordingConfig:(ByteRTCRecordingConfig* _Nonnull)recordingConfig type:(ByteRTCRecordingType)recordingType;
/** 
 * @type api
 * @region 本地录制
 * @author wunailiang
 * @brief 停止本地录制
 * @param streamIndex 流属性，指定停止主流或者屏幕流录制，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @notes  <br>
 *        + 调用 startFileRecording:withRecordingConfig:type:{@link #ByteRTCVideo#startFileRecording:withRecordingConfig:type:} 开启本地录制后，你必须调用该方法停止录制。  <br>
 *        + 调用该方法后，你会收到 rtcEngine:onRecordingStateUpdate:state:error_code:recording_info:{@link #ByteRTCVideoDelegate#rtcEngine:onRecordingStateUpdate:state:error_code:recording_info:} 回调提示录制结果。
 */
- (void)stopFileRecording:(ByteRTCStreamIndex)streamIndex;
 /** 
  * @type api
  * @region 混音
  * @author majun.lvhiei
  * @brief 混音管理接口创建
  * @return 混音管理实例，详见ByteRTCAudioMixingManager{@link #ByteRTCAudioMixingManager}
  */
 - (ByteRTCAudioMixingManager *_Nullable)getAudioMixingManager;


#pragma mark - Rtm
/** 
 * @type api
 * @region 实时消息通信
 * @author hanchenchen.c
 * @brief 必须先登录，才能发送房间外点对点消息和向应用服务器发送消息<br>
 *        在调用本接口登录后，如果想要登出，需要调用 logout{@link #ByteRTCVideo#logout}
 * @param token  <br>
 *        动态密钥  <br>
 *        用户登录必须携带的 Token，用于鉴权验证。  <br>
 *        登录 Token 与加入房间时必须携带的 Token 不同。测试时可使用控制台生成临时 Token，`roomId` 填任意值或置空，正式上线需要使用密钥 SDK 在你的服务端生成并下发 Token。
 * @param uid  <br>
 *        用户 ID  <br>
 *        用户 ID 在 appid的维度下是唯一的。
 * @notes  本地用户调用此方法登录后，会收到 rtcEngine:onLoginResult:errorCode:elapsed:{@link #ByteRTCVideoDelegate#rtcEngine:onLoginResult:errorCode:elapsed:} 回调通知登录结果，远端用户不会收到通知。
 */
- (void)login:(NSString * _Nonnull)token uid:(NSString * _Nonnull)uid;
/** 
 * @type api
 * @region 实时消息通信
 * @author hanchenchen.c
 * @brief 调用本接口登出后，无法调用房间外消息以及端到服务器消息相关的方法或收到相关回调。
 * @notes  <br>
 *       + 调用本接口登出前，必须先调用 login:uid:{@link #ByteRTCVideo#login:uid:} 登录  <br>
 *       + 本地用户调用此方法登出后，会收到 rtcEngineOnLogout:{@link #ByteRTCVideoDelegate#rtcEngineOnLogout:}  回调通知结果，远端用户不会收到通知。
 */
- (void)logout;
/** 
 * @type api
 * @region 实时消息通信
 * @author hanchenchen.c
 * @brief 更新用户用于登录的 Token  <br>
 *        Token 有一定的有效期，当 Token 过期时，需调用此方法更新登录的 Token 信息。  <br>
 *        调用 login:uid:{@link #ByteRTCVideo#login:uid:} 方法登录时，如果使用了过期的 Token 将导致登录失败，并会收到 rtcEngine:onLoginResult:errorCode:elapsed:{@link #ByteRTCVideoDelegate#rtcEngine:onLoginResult:errorCode:elapsed:} 回调通知，错误码为 ByteRTCLoginErrorCodeInvalidToken。此时需要重新获取 Token，并调用此方法更新 Token。
 * @param token  <br>
 *        更新的动态密钥  <br>
 * @notes  <br>
 *       + 如果 Token 无效导致登录失败，则调用此方法更新 Token 后，SDK 会自动重新登录，而用户不需要自己调用 login:uid:{@link #ByteRTCVideo#login:uid:} 方法。  <br>
 *       + Token 过期时，如果已经成功登录，则不会受到影响。Token 过期的错误会在下一次使用过期 Token 登录时，或因本地网络状况不佳导致断网重新登录时通知给用户。
 */
- (void)updateLoginToken:(NSString * _Nonnull)token;
/** 
 * @type api
 * @region 实时消息通信
 * @author hanchenchen.c
 * @brief 设置应用服务器参数  <br>
 *        客户端调用 sendServerMessage:{@link #ByteRTCVideo#sendServerMessage:} 或 sendServerBinaryMessage:{@link #ByteRTCVideo#sendServerBinaryMessage:} 发送消息给应用服务器之前，必须需要设置有效签名和应用服务器地址。
 * @param signature  <br>
 *        动态签名  <br>
 *        应用服务器会使用该签名对请求进行鉴权验证。  <br>
 * @param url  <br>
 *        应用服务器的地址
 * @notes  <br>
 *       + 用户必须调用 login:uid:{@link #ByteRTCVideo#login:uid:} 登录后，才能调用本接口。  <br>
 *       + 调用本接口后，SDK 会使用 rtcEngine:onServerParamsSetResult:{@link #ByteRTCVideoDelegate#rtcEngine:onServerParamsSetResult:} 返回相应结果。
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
 *       + 必须调用 login:uid:{@link #ByteRTCVideo#login:uid:} 登录后，才能调用本接口。  <br>
 *       + 调用本接口后，SDK 会使用 rtcEngine:onGetPeerOnlineStatus:status:{@link #ByteRTCVideoDelegate#rtcEngine:onGetPeerOnlineStatus:status:} 回调通知查询结果。  <br>
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
 *        消息不超过 64 KB。
 * @param config 消息类型，参看 ByteRTCMessageConfig{@link #ByteRTCMessageConfig}。
 * @return  <br>
 *        + >0：发送成功，返回这次发送消息的编号，从 1 开始递增  <br>
 *        + -1：发送失败，ByteRTCVideo 实例未创建  <br>
 *        + -2：发送失败，userId 为空
 * @notes  <br>
 *       + 在发送房间外文本消息前，必须先调用 login:uid:{@link #ByteRTCVideo#login:uid:} 完成登录。  <br>
 *       + 用户调用本接口发送文本信息后，会收到一次 rtcEngine:onUserMessageSendResultOutsideRoom:error:{@link #ByteRTCVideoDelegate#rtcEngine:onUserMessageSendResultOutsideRoom:error:} 回调，得知消息是否成功发送；  <br>
 *       + 若文本消息发送成功，则 userId 所指定的用户会通过 rtcEngine:onUserMessageReceivedOutsideRoom:message:{@link #ByteRTCVideoDelegate#rtcEngine:onUserMessageReceivedOutsideRoom:message:} 回调收到该消息。
 */
- (int64_t)sendUserMessageOutsideRoom:(NSString * _Nonnull)userId message:(NSString * _Nonnull)messageStr config:(ByteRTCMessageConfig)config;
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
 * @param config 消息类型，参看 ByteRTCMessageConfig{@link #ByteRTCMessageConfig}。
 * @return  <br>
 *        + >0：发送成功，返回这次发送消息的编号，从 1 开始递增  <br>
 *        + -1：发送失败，ByteRTCVideo 实例未创建  <br>
 *        + -2：发送失败，userId 为空
 * @notes  <br>
 *       + 在发送房间外二进制消息前，必须先调用 login:uid:{@link #ByteRTCVideo#login:uid:} 完成登录。  <br>
 *       + 用户调用本接口发送二进制消息后，会收到一次 rtcEngine:onUserMessageSendResultOutsideRoom:error:{@link #ByteRTCVideoDelegate#rtcEngine:onUserMessageSendResultOutsideRoom:error:} 回调，通知消息是否发送成功；  <br>
 *       + 若二进制消息发送成功，则 userId 所指定的用户会通过 rtcEngine:onUserBinaryMessageReceivedOutsideRoom:message:{@link #ByteRTCVideoDelegate#rtcEngine:onUserBinaryMessageReceivedOutsideRoom:message:}  回调收到该条消息。
 */
- (int64_t)sendUserBinaryMessageOutsideRoom:(NSString * _Nonnull)userId message:(NSData * _Nonnull)messageStr config:(ByteRTCMessageConfig)config;
/** 
 * @type api
 * @region 实时消息通信
 * @author hanchenchen.c
 * @brief 客户端给应用服务器发送文本消息（P2Server）
 * @param messageStr  <br>
 *        发送的文本消息内容  <br>
 *        消息不超过 64 KB。
 * @return  <br>
 *        + >0：发送成功，返回这次发送消息的编号，从 1 开始递增  <br>
 *        + -1：发送失败，ByteRTCVideo 实例未创建
 * @notes  <br>
 *       + 在向应用服务器发送文本消息前，必须先调用 login:uid:{@link #ByteRTCVideo#login:uid:} 完成登录，随后调用 setServerParams:url:{@link #ByteRTCVideo#setServerParams:url:} 设置应用服务器。  <br>
 *       + 调用本接口后，会收到一次 rtcEngine:onServerMessageSendResult:error:message:{@link #ByteRTCVideoDelegate#rtcEngine:onServerMessageSendResult:error:message:} 回调，通知消息发送方是否发送成功。  <br>
 *       + 若文本消息发送成功，则之前调用 setServerParams:url:{@link #ByteRTCVideo#setServerParams:url:} 设置的应用服务器会收到该条消息。
 */
- (int64_t)sendServerMessage:(NSString * _Nonnull)messageStr;
/** 
 * @type api
 * @region 实时消息通信
 * @author hanchenchen.c
 * @brief 客户端给应用服务器发送二进制消息（P2Server）
 * @param messageStr  <br>
 *        发送的二进制消息内容  <br>
 *        消息不超过 46KB。
 * @return  <br>
 *        + >0：发送成功，返回这次发送消息的编号，从 1 开始递增  <br>
 *        + -1：发送失败，ByteRTCVideo 实例未创建
 * @notes  <br>
 *       + 在向应用服务器发送二进制消息前，先调用 login:uid:{@link #ByteRTCVideo#login:uid:} 完成登录，随后调用 setServerParams:url:{@link #ByteRTCVideo#setServerParams:url:} 设置应用服务器。  <br>
 *       + 调用本接口后，会收到一次 rtcEngine:onServerMessageSendResult:error:message:{@link #ByteRTCVideoDelegate#rtcEngine:onServerMessageSendResult:error:message:} 回调，通知消息发送方发送成功或失败；  <br>
 *       + 若二进制消息发送成功，则之前调用 setServerParams:url:{@link #ByteRTCVideo#setServerParams:url:} 设置的应用服务器会收到该条消息。
 */
- (int64_t)sendServerBinaryMessage:(NSData * _Nonnull)messageStr;
/** 
 * @type api
 * @region 通话前网络探测
 * @author hanchenchen.c
 * @brief 开始通话前网络探测
 * @param is_test_uplink  是否探测上行带宽
 * @param expected_uplink_bitrate  期望上行带宽，单位：kbps<br>范围为 {0, [100-10000]}，其中， `0` 表示由 SDK 指定最高码率。
 * @param is_test_downlink  是否探测下行带宽
 * @param expected_downlink_bitrate  期望下行带宽，单位：kbps<br>范围为 {0, [100-10000]}，其中， `0` 表示由 SDK 指定最高码率。
 * @return 开启通话前网络探测结果，详见 ByteRTCNetworkDetectionStartReturn{@link #ByteRTCNetworkDetectionStartReturn}
 * @notes  <br>
 *       + 成功调用本接口后，会在 3s 内收到一次 rtcEngine:onNetworkDetectionResult:quality:rtt:lostRate:bitrate:jitter:{@link #ByteRTCVideoDelegate#rtcEngine:onNetworkDetectionResult:quality:rtt:lostRate:bitrate:jitter:} 回调，此后每 2s 会收到一次该回调，通知探测结果；  <br>
 *       + 若探测停止，则会收到一次 rtcEngine:onNetworkDetectionStopped:{@link #ByteRTCVideoDelegate#rtcEngine:onNetworkDetectionStopped:} 通知探测停止。
 */
- (ByteRTCNetworkDetectionStartReturn)startNetworkDetection:(bool)is_test_uplink uplinkBandwidth:(int)expected_uplink_bitrate downlink:(bool)is_test_downlink downlinkBandwidth:(int)expected_downlink_bitrate;
/** 
 * @type api
 * @region 通话前网络探测
 * @author hanchenchen.c
 * @brief 停止通话前网络探测
 * @notes  <br>
 *       调用本接口后，会收到一次 rtcEngine:onNetworkDetectionStopped:{@link #ByteRTCVideoDelegate#rtcEngine:onNetworkDetectionStopped:} 通知探测停止。
 */
- (void)stopNetworkDetection;
#pragma mark  ScreenAudio
/** 
 * @type api
 * @region 屏幕共享
 * @author liyi.000
 * @brief 在屏幕共享时，设置屏幕音频的采集方式（内部采集/自定义采集）
 * @param sourceType 屏幕音频输入源类型, 参看 ByteRTCAudioSourceType{@link #ByteRTCAudioSourceType}。
 * @notes  <br>
 *      + 默认采集方式是 RTC SDK 内部采集。<br>
 *      + 你应该在 publishScreen:{@link #ByteRTCRoom#publishScreen:} 前，调用此方法。否则，你将收到 rtcEngine:onWarning:{@link #ByteRTCVideoDelegate#rtcEngine:onWarning:} 的报错：`ByteRTCWarningSetScreenAudioSourceTypeFailed`。 <br>
 *      + 如果设定为内部采集，你必须重新开始采集。
 *      + 如果设定为自定义采集，你必须再调用 pushScreenAudioFrame:{@link #ByteRTCVideo#pushScreenAudioFrame:} 将自定义采集到的屏幕音频帧推送到 RTC SDK。<br>
 *      + 无论是内部采集还是自定义采集，你都必须调用 publishScreen:{@link #ByteRTCRoom#publishScreen:} 将采集到的屏幕音频发布给远端。
 */
- (void)setScreenAudioSourceType:(ByteRTCAudioSourceType)sourceType;
/** 
 * @type api
 * @region 屏幕共享
 * @author liyi.000
 * @brief 在屏幕共享时，设置屏幕音频流和麦克风采集到的音频流的混流方式
 * @param index 混流方式，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex} <br>
 *        + `ByteRTCStreamIndexMain`: 将屏幕音频流和麦克风采集到的音频流混流 <br>
 *        + `ByteRTCStreamIndexScreen`: 默认值，将屏幕音频流和麦克风采集到的音频流分为两路音频流
 * @notes 你应该在 publishScreen:{@link #ByteRTCRoom#publishScreen:} 之前，调用此方法。否则，你将收到 rtcEngine:onWarning:{@link #ByteRTCVideoDelegate#rtcEngine:onWarning:} 的报错：`ByteRTCWarningSetScreenAudioStreamIndexFailed`
 */
- (void)setScreenAudioStreamIndex:(ByteRTCStreamIndex) index;
/** 
 * @type api
 * @region 屏幕共享
 * @author liyi.000
 * @brief 使用自定义采集方式，采集屏幕共享时的屏幕音频时，将音频帧推送至 RTC SDK 处进行编码等处理。
 * @param audioFrame 音频数据帧，参见 ByteRTCAudioFrame{@link #ByteRTCAudioFrame}
 * @return 方法调用结果  <br>
 *        + 0: 设置成功  <br>
 *        + < 0: 设置失败  <br>
 * @notes  <br>
 *        + 调用此接口推送屏幕共享时的自定义采集的音频数据前，必须调用 setScreenAudioSourceType:{@link #ByteRTCVideo#setScreenAudioSourceType:} 开启屏幕音频自定义采集。  <br>
 *        + 你应每隔 10 毫秒，调用一次此方法推送一次自定义采集的音频帧。一次推送的音频帧中应包含 frame.sample_rate / 100 个音频采样点。比如，假如采样率为 48000Hz，则每次应该推送 480 个采样点。  <br>
 *        + 音频采样格式为 S16。音频缓冲区内的数据格式必须为 PCM 数据，其容量大小应该为 samples × frame.channel × 2。  <br>
 *        + 调用此接口将自定义采集的音频帧推送到 RTC SDK 后，你必须调用 publishScreen:{@link #ByteRTCRoom#publishScreen:} 将采集到的屏幕音频推送到远端。在调用 publishScreen:{@link #ByteRTCRoom#publishScreen:} 前，推送到 RTC SDK 的音频帧信息会丢失。
 */
- (int) pushScreenAudioFrame:(ByteRTCAudioFrame* _Nonnull)audioFrame;

#if BYTERTC_TARGET_MAC
/** 
 * @hidden(iOS)
 * @type api
 * @region 屏幕共享
 * @author liuxiaowu
 * @brief 在屏幕共享时，开始使用 RTC SDK 内部采集方式，采集屏幕音频
 * @param deviceId 虚拟设备 ID
 * @notes <br>
 *        + 采集后，你还需要调用 publishScreen:{@link #ByteRTCRoom#publishScreen:} 将采集到的屏幕音频推送到远端。<br>
 *        + 要关闭屏幕音频内部采集，调用 stopScreenAudioCapture{@link #ByteRTCVideo#stopScreenAudioCapture}。
 */
- (void)startScreenAudioCapture:(NSString *_Nonnull)deviceId;
/** 
 * @hidden(iOS)
 * @type api
 * @region 屏幕共享
 * @author liyi.000
 * @brief 在屏幕共享时，停止使用 RTC SDK 内部采集方式，采集屏幕音频。
 * @notes 要开始屏幕音频内部采集，调用 startScreenAudioCapture:{@link #ByteRTCVideo#startScreenAudioCapture:}。
 */
- (void)stopScreenAudioCapture;

#endif

#pragma mark EncodedVideo

/** 
 * @type api
 * @region 视频管理
 * @author wangzhanqiang
 * @brief 设置向 SDK 输入的视频源
 *        默认使用内部采集。内部采集指：使用 RTC SDK 内置的视频采集机制进行视频采集。 <br>
 * @param type 视频输入源类型，参看 ByteRTCVideoSourceType{@link #ByteRTCVideoSourceType}
 * @param streamIndex 视频流的属性，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @notes  <br>
 *        + 该方法进房前后均可调用。  <br>
 *        + 当你已调用 startVideoCapture{@link #ByteRTCVideo#startVideoCapture} 开启内部采集后，再调用此方法切换至自定义采集时，SDK 会自动关闭内部采集。  <br>
 *        + 当你调用此方法开启自定义采集后，想要切换至内部采集，你必须先调用此方法关闭自定义采集，然后调用 startVideoCapture{@link #ByteRTCVideo#startVideoCapture} 手动开启内部采集。
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
 * @param videoIndex 对应的编码流下标，从 0 开始，如果调用 SetVideoEncoderConfig:{@link #ByteRTCVideo#SetVideoEncoderConfig:} 设置了多路流，此处数量须与之保持一致
 * @param videoFrame 编码流视频帧信息，参看 ByteRTCEncodedVideoFrame{@link #ByteRTCEncodedVideoFrame}。  <br>
 * @notes  <br>
 *        + 目前仅支持推送 H264 和 ByteVC1 格式的视频帧，且视频流协议格式须为 Annex B 格式。  <br>
 *        + 该函数运行在用户调用线程内  <br>
 *        + 推送自定义编码视频帧前，必须调用 setVideoSourceType:WithStreamIndex:{@link #ByteRTCVideo#setVideoSourceType:WithStreamIndex:} 将视频输入源切换至自定义编码视频源。
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
 *        + 该方法仅适用于手动订阅模式，并且在订阅远端流之前使用。  <br>
 *        + 当你想要对远端流进行自定义解码时，你需要先调用 registerRemoteEncodedVideoFrameObserver:{@link #ByteRTCVideo#registerRemoteEncodedVideoFrameObserver:} 注册远端视频流监测器，然后再调用该接口将解码方式设置为自定义解码。监测到的视频数据会通过 onRemoteEncodedVideoFrame:withEncodedVideoFrame:{@link #ByteRTCRemoteEncodedVideoFrameObserver#onRemoteEncodedVideoFrame:withEncodedVideoFrame:} 回调出来。
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
 *        + 该方法适用于调用 setVideoDecoderConfig:withVideoDecoderConfig:{@link #ByteRTCVideo#setVideoDecoderConfig:withVideoDecoderConfig:} 开启自定义解码功能后，并且自定义解码失败的情况下使用
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
#pragma mark StreamSyncInfo
/** 
 * @type api
 * @region 音频管理
 * @author wangjunzheng
 * @brief 发送音频流同步信息。将消息通过音频流发送到远端，并实现与音频流同步，该接口调用成功后，远端用户会收到 rtcEngine:onStreamSyncInfoReceived:streamType:data:{@link #ByteRTCVideoDelegate#rtcEngine:onStreamSyncInfoReceived:streamType:data:} 回调。
 * @param data 消息内容。
 * @param config 媒体流信息同步的相关配置，详见 ByteRTCStreamSycnInfoConfig{@link #ByteRTCStreamSycnInfoConfig} 。
 * @return  <br>
 *        + >=0: 消息发送成功。返回成功发送的次数。  <br>
 *        + -1: 消息发送失败。消息长度大于 16 字节。  <br>
 *        + -2: 消息发送失败。传入的消息内容为空。  <br>
 *        + -3: 消息发送失败。通过屏幕流进行消息同步时，此屏幕流还未发布。  <br>
 *        + -4: 消息发送失败。通过用麦克风或自定义设备采集到的音频流进行消息同步时，此音频流还未发布，详见错误码 ByteRTCErrorCode{@link #ByteRTCErrorCode}。  <br>
 * @notes 在采用 `ByteRTCRoomProfileLiveBroadcasting` 作为房间模式时，此消息一定会送达。在其他房间模式下，如果本地用户未说话，此消息不一定会送达。
 */
- (int)sendStreamSyncInfo:(NSData* _Nonnull)data config:(ByteRTCStreamSycnInfoConfig * _Nonnull)config;
/** 
 * @type api
 * @region 媒体流管理
 * @author yangpan
 * @brief 控制本地音频流播放状态：播放/不播放  <br>
 * @param muteState 播放状态，标识是否播放本地音频流，详见：ByteRTCMuteState{@link #ByteRTCMuteState}
 * @notes 本方法仅控制本地收到音频流的播放状态，并不影响本地音频播放设备。
 */
- (void)muteAudioPlayback:(ByteRTCMuteState)muteState;
/** 
 * @type api
 * @region 网络管理
 * @author qipengxiang
 * @brief 开启音视频回路测试。  <br>
 *        在进房前，用户可调用该接口对音视频通话全链路进行检测，包括对音视频设备以及用户上下行网络的检测，从而帮助用户判断是否可以正常发布和接收音视频流。  <br>
 *        开始检测后，SDK 会录制你声音或视频。如果你在设置的延时范围内收到了回放，则视为音视频回路测试正常。
 * @param echoConfig 回路测试参数设置，参看 ByteRTCEchoTestConfig{@link #ByteRTCEchoTestConfig}。
 * @param delayTime 音视频延迟播放的时间间隔，用于指定在开始检测多长时间后期望收到回放。取值范围为 [2,10]，单位为秒，默认为 2 秒。
 * @return 方法调用结果：  <br>
 *        + 0：成功  <br>
 *        + -1：失败，当前用户已经在检测中  <br>
 *        + -2：失败，用户已进房  <br>
 *        + -3：失败，音视频均未采集  <br>
 *        + -4：失败，参数异常  <br>
 *        + -5：失败，已经存在相同 roomId 的房间
 * @notes  <br>
 *        + 调用该方法开始音视频回路检测后，你可以调用 stopEchoTest{@link #ByteRTCVideo#stopEchoTest} 立即结束测试，也可等待测试 60s 后自动结束，以更换设备进行下一次测试，或进房。  <br>
 *        + 在该方法之前调用的所有跟设备控制、流控制相关的方法均在开始检测时失效，在结束检测后恢复生效。  <br>
 *        + 在调用 startEchoTest:playDelay:{@link #ByteRTCVideo#startEchoTest:playDelay:} 和 stopEchoTest{@link #ByteRTCVideo#stopEchoTest} 之间调用的所有跟设备采集、流控制、进房相关的方法均不生效，并会收到 rtcEngine:onWarning:{@link #ByteRTCVideoDelegate#rtcEngine:onWarning:} 回调，提示警告码为 `ByteRTCWarningCodeInEchoTestMode`。  <br>
 *        + 音视频回路检测的结果会通过 rtcEngine:onEchoTestResult:{@link #ByteRTCVideoDelegate#rtcEngine:onEchoTestResult:} 回调通知。
 */
- (int)startEchoTest:(ByteRTCEchoTestConfig *_Nullable)echoConfig playDelay:(NSInteger)delayTime;
/** 
 * @type api
 * @region 网络管理
 * @author qipengxiang
 * @brief 停止音视频回路测试。  <br>
 *        调用 startEchoTest:playDelay:{@link #ByteRTCVideo#startEchoTest:playDelay:} 开启音视频回路检测后，你必须调用该方法停止检测。
 * @return 方法调用结果：  <br>
 *        + 0：成功  <br>
 *        + -1：失败，未开启回路检测
 * @notes 音视频回路检测结束后，所有对系统设备及音视频流的控制均会恢复到开始检测前的状态。
 */
- (int)stopEchoTest;

/** 
 * @type api
 * @region 音视频处理
 * @author yanjing
 * @brief 在指定视频流上添加水印。
 * @param streamIndex 需要添加水印的视频流属性，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}。
 * @param imagePath 水印图片路径，支持本地文件绝对路径和Asset 资源路径（/assets/xx.png），长度限制为 512 字节。   <br>
 *        水印图片为 PNG 或 JPG 格式。
 * @param rtcWatermarkConfig 水印参数，参看 ByteRTCVideoWatermarkConfig{@link #ByteRTCVideoWatermarkConfig}。
 * @notes  <br>
 *        + 调用 ClearVideoWatermark{@link #ByteRTCVideo#ClearVideoWatermark:} 移除指定视频流的水印。  <br>
 *        + 同一路流只能设置一个水印，新设置的水印会代替上一次的设置。你可以多次调用本方法来设置不同流的水印。  <br>
 *        + 进入房间前后均可调用此方法。  <br>
 *        + 若开启本地预览镜像，或开启本地预览和编码传输镜像，则远端水印均不镜像；在开启本地预览水印时，本端水印会镜像。  <br>
 *        + 开启大小流后，水印对大小流均生效，且针对小流进行等比例缩小。
 */
- (void)SetVideoWatermark:(ByteRTCStreamIndex)streamIndex
            WithImagePath:(NSString * _Nullable)imagePath
   WithRtcWatermarkConfig:(ByteRTCVideoWatermarkConfig* _Nonnull)rtcWatermarkConfig;
/** 
 * @type api
 * @region 音视频处理
 * @author yanjing
 * @brief 移除指定视频流的水印。
 * @param streamIndex 需要移除水印的视频流属性，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 */
- (void)ClearVideoWatermark:(ByteRTCStreamIndex)streamIndex;
/** 
 * @type api
 * @region 云代理
 * @author daining.nemo
 * @brief 开启云代理
 * @param cloudProxiesInfo 云代理服务器信息列表。参看 ByteRTCCloudProxyInfo{@link #ByteRTCCloudProxyInfo}。
 * @notes  <br>
 *        + 在加入房间前调用此接口  <br>
 *        + 在开启云代理后，进行通话前网络探测 <br>
 *        + 开启云代理后，并成功链接云代理服务器后，会收到 rtcEngine:onCloudProxyConnected:{@link #ByteRTCVideoDelegate#rtcEngine:onCloudProxyConnected:}。<br>
 *        + 要关闭云代理，调用 stopCloudProxy{@link #ByteRTCVideo#stopCloudProxy}。
 */
- (void)startCloudProxy:(NSArray <ByteRTCCloudProxyInfo *> * _Nullable)cloudProxiesInfo;
/** 
 * @type api
 * @region 云代理
 * @author daining.nemo
 * @brief 关闭云代理
 * @notes 要开启云代理，调用 startCloudProxy:{@link #ByteRTCVideo#startCloudProxy:}
 */
- (void)stopCloudProxy;
@end
