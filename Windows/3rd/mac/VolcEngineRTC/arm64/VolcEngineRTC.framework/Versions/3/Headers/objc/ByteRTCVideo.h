/*
 * Copyright (c) 2020 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC
*/
#import <CoreMedia/CMTime.h>
#import "rtc/ByteRTCDefines.h"
#import "rtc/ByteRTCHttpClientProtocol.h"
#import "rtc/ByteRTCAudioMixingManager.h"
#import "rtc/ByteRTCAudioEffectPlayer.h"
#import "rtc/ByteRTCMediaPlayer.h"
#import "rtc/ByteRTCSingScoringManager.h"
@class ByteRTCVideo;
@class ByteRTCRoom;
@class ByteRTCKTVManager;
/**
 * @type api
 */
@protocol ByteRTCHttpClientProtocol;

#pragma mark - ByteRTCVideoDelagate

/**
 * @locale zh
 * @type callback
 * @brief ByteRTCVideoDelegate 协议包含了SDK提供的回调方法，SDK通过代理向应用程序上报一些运行时事件<br>
 * 注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。
 */
/**
 * @locale en
 * @type callback
 * @brief ByteRTCVideoDelegate protocol contains the callback method provided by the SDK, which reports some run-time events to the application through a proxy<br>
 * Note: Callback functions are thrown synchronously in a non-UI thread within the SDK. Therefore, you must not perform any time-consuming operations or direct UI operations within the callback function, as this may cause the app to crash.
 */
@protocol ByteRTCVideoDelegate <NSObject>
@optional
#pragma mark - Core Delegate Methods
// @name  core event callback
/**
 * @locale zh
 * @type callback
 * @region 警告码
 * @brief 发生警告回调。  <br>
 *        SDK 运行时出现了警告。SDK 通常会自动恢复，警告信息可以忽略。
 * @param engine ByteRTCVideo 对象。
 * @param code 警告代码，参看 ByteRTCWarningCode{@link #ByteRTCWarningCode}。
 * @list 引擎管理
 * @order 5
 */
/**
 * @locale en
 * @type callback
 * @region Warning code
 * @brief A warning occurred during the SDK runtime. The SDK usually recovers automatically and warnings can be ignored.
 * @param engine ByteRTCVideo object.
 * @param code Warning code. See ByteRTCWarningCode{@link #ByteRTCWarningCode}.
 * @list Engine Management
 * @order 5
 */
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onWarning:(ByteRTCWarningCode)code;
/**
 * @locale zh
 * @type callback
 * @region 错误码
 * @brief 发生错误回调。<br>
 *        SDK 运行时出现了网络或媒体相关的错误，且无法自动恢复时触发此回调。<br>
 *        你可能需要干预.
 * @param engine ByteRTCVideo 对象。  
 * @param errorCode 错误代码，参看 ByteRTCErrorCode{@link #ByteRTCErrorCode}。  
 * @list 引擎管理
 * @order 6
 */
/**
 * @locale en
 * @type callback
 * @region Error code
 * @brief Error callback occurred. This callback is triggered when a network or media-related error occurs during the <br>
 *        SDK runtime and cannot be automatically recovered and you may need to intervene.
 * @param engine ByteRTCVideo object. 
 * @param errorCode  BigInt. See ByteRTCErrorCode{@link #ByteRTCErrorCode}. 
 * @list Engine Management
 * @order 6
 */
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onError:(ByteRTCErrorCode)errorCode;


/**
 * @brief 内部线程发生block时触发,回调线程名和block次数
 * 
 */
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onDeadLockError:(ByteRTCDeadLockMsg *_Nonnull)deadlockMsg;
/**
* @locale zh
* @valid since 3.52
* @type callback
* @brief 当访问插件失败时，收到此回调。<br>
*        RTC SDK 将一些功能封装成插件。当使用这些功能时，如果插件不存在，功能将无法使用。
* @param extensionName 插件名字
* @param msg 失败说明
*/
/**
* {en}
* @valid since 3.52
* @type callback
* @brief Failed to access the extension.<br>
*        RTC SDK provides some features with extensions. Without implementing the extension, you cannot use the corresponding feature.
* @param extensionName The name of extension.
* @param msg Error message.
*/
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onExtensionAccessError:(NSString * _Nonnull)extensionName msg:(NSString * _Nonnull)msg;
/**
 * @locale zh
 * @type callback
 * @region 引擎管理
 * @brief 创建房间失败回调。
 * @param roomId 房间 ID。
 * @param errorCode 创建房间错误码，具体原因参看 ByteRTCErrorCode{@link #ByteRTCErrorCode}。
 */
/**
 * @locale en
 * @type callback
 * @region Engine Management
 * @brief Callback on create room failure.
 * @param roomId  Room ID.
 * @param errorCode Create room error code. See ByteRTCErrorCode{@link #ByteRTCErrorCode} for specific indications.
 */
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onCreateRoomStateChanged:(NSString * _Nonnull)roomId errorCode:(NSInteger)errorCode;

/**
 * @locale zh
 * @type callback
 * @region 引擎管理
 * @brief SDK 与信令服务器连接状态改变回调。连接状态改变时触发。
 * @param engine ByteRTCVideo 对象
 * @param state 当前 SDK 与信令服务器的连接状态，详见 ByteRTCConnectionState{@link #ByteRTCConnectionState}。
 * @note 更多信息参见 [连接状态提示](https://www.volcengine.com/docs/6348/95376)。
 */
/**
 * @locale en
 * @type callback
 * @region  engine management
 * @brief SDK  connection state change callback with signaling server. Triggered when the connection state changes.
 * @param engine ByteRTCVideo object
 * @param state The current connection status between the SDK and the signaling server. See ByteRTCConnectionState{@link #ByteRTCConnectionState}.
 * @note Refer to [Getting Connection Status](https://docs.byteplus.com/byteplus-rtc/docs/95376) for more details.
 */
- (void) rtcEngine:(ByteRTCVideo * _Nonnull)engine onConnectionStateChanged:(ByteRTCConnectionState) state;
/**
 * @locale zh
 * @type callback
 * @region 引擎管理
 * @brief SDK 当前网络连接类型改变回调。
 * @param engine ByteRTCVideo 对象
 * @param type SDK 当前的网络连接类型，详见 ByteRTCNetworkType{@link #ByteRTCNetworkType}
 */
/**
 * @locale en
 * @type callback
 * @region  engine management
 * @brief SDK  current network connection type change callback.
 * @param engine ByteRTCVideo object
 * @param type SDK The current network connection type. See ByteRTCNetworkType{@link #ByteRTCNetworkType}
 */
- (void) rtcEngine:(ByteRTCVideo * _Nonnull)engine onNetworkTypeChanged:(ByteRTCNetworkType) type;
#pragma mark - Core Audio Delegate Methods
// @name core audio event callback

/**
 * @locale zh
 * @deprecated since 3.36 and will be deleted in 3.51, use rtcRoom:onUserPublishStream:type:{@link #ByteRTCRoomDelegate#rtcRoom:onUserPublishStream:type:}, rtcRoom:onUserPublishScreen:type:{@link #ByteRTCRoomDelegate#rtcRoom:onUserPublishScreen:type:}, rtcRoom:onUserUnpublishStream:type:reason:{@link #ByteRTCRoomDelegate#rtcRoom:onUserUnpublishStream:type:reason:} and rtcRoom:onUserUnpublishScreen:type:reason:{@link #ByteRTCRoomDelegate#rtcRoom:onUserUnpublishScreen:type:reason:} instead.
 * @type callback
 * @region 媒体流管理
 * @brief 房间内用户暂停/恢复发送音频流时，房间内其他用户会收到此回调。
 * @param engine ByteRTCVideo 实例
 * @param uid 改变本地音频发送状态的用户 ID
 * @param muteState 发送状态，参看 ByteRTCMuteState{@link #ByteRTCMuteState}
 */
/**
 * @locale en
 * @deprecated since 3.45 and will be deleted in 3.51, use rtcRoom:onUserPublishStream:type:{@link #ByteRTCRoomDelegate#rtcRoom:onUserPublishStream:type:}, rtcRoom:onUserPublishScreen:type:{@link #ByteRTCRoomDelegate#rtcRoom:onUserPublishScreen:type:}, rtcRoom:onUserUnpublishStream:type:reason:{@link #ByteRTCRoomDelegate#rtcRoom:onUserUnpublishStream:type:reason:} and rtcRoom:onUserUnpublishScreen:type:reason:{@link #ByteRTCRoomDelegate#rtcRoom:onUserUnpublishScreen:type:reason:} instead.
 * @type callback
 * @region Media Stream Management
 * @brief Transmission state change of an audio stream in the room triggers this callback.
 * @param engine ByteRTCVideo instance
 * @param uid The user who changes his/her transmission state of the audio streams
 * @param muteState Transmission state of the audio streams. Refer to ByteRTCMuteState{@link #ByteRTCMuteState} for more details.
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onUserMuteAudio:(NSString * _Nonnull)roomId
        uid:(NSString * _Nonnull)uid muteState:(ByteRTCMuteState)muteState __deprecated_msg("Will be removed in new version");

/**
 * @locale zh
 * @type callback
 * @region 音频事件回调
 * @brief 房间内的可见用户调用 startAudioCapture{@link #ByteRTCVideo#startAudioCapture} 开启音频采集时，房间内其他用户会收到此回调。
 * @param engine ByteRTCVideo 实例
 * @param roomId 开启音频采集的用户所在的房间 ID
 * @param userId 开启音频采集的远端用户 ID
 */
/**
 * @locale en
 * @type callback
 * @region Audio event callback
 * @brief The remote clients in the room will be informed of the state change via this callback after the visible user starts audio capture by calling startAudioCapture{@link #ByteRTCVideo#startAudioCapture}.
 * @param engine ByteRTCVideo instance
 * @param roomId ID of the room where the user enables audio capture
 * @param userId The user who starts the internal audio capture
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onUserStartAudioCapture:(NSString* _Nonnull)roomId
              uid:(NSString *_Nonnull)userId;

/**
 * @locale zh
 * @type callback
 * @region 音频事件回调
 * @brief 房间内的可见用户调用 stopAudioCapture{@link #ByteRTCVideo#stopAudioCapture} 关闭音频采集时，房间内其他用户会收到此回调。
 * @param engine ByteRTCVideo 实例
 * @param roomId 关闭音频采集的用户所在的房间 ID
 * @param userId 关闭音频采集的远端用户 ID
 */
/**
 * @locale en
 * @type callback
 * @region Audio event callback
 * @brief The remote clients in the room will be informed of the state change via this callback after the visible user stops audio capture by calling stopAudioCapture{@link #ByteRTCVideo#stopAudioCapture}.
 * @param engine ByteRTCVideo instance
 * @param roomId ID of the room where the user disables audio capture
 * @param userId The user who stops the internal audio capture
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onUserStopAudioCapture:(NSString* _Nonnull)roomId
              uid:(NSString *_Nonnull)userId;
/**
 * @locale zh
 * @type callback
 * @region 音频事件回调
 * @brief 当收到远端流的第一帧音频的时候上报该事件
 * @param engine ByteRTCVideo 对象
 * @param key 远端流信息, 详见 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
 * @note 用户刚收到房间内每一路音频流时，都会收到该回调。
 */
/**
 * @locale en
 * @type callback
 * @region Audio event callback
 * @brief Report the event when the first frame of audio of the remote stream is received
 * @param engine ByteRTCVideo object
 * @param key Remote stream information. See ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
 * @note The callback will be received when the user has just received each audio stream in the room.
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onFirstRemoteAudioFrame:(ByteRTCRemoteStreamKey * _Nonnull)key;
 /**
  * @locale zh
  * @type callback
  * @region 音频管理
  * @brief 调用 enableAudioPropertiesReport:{@link #ByteRTCVideo#enableAudioPropertiesReport:} 后，根据设置的 interval 值，你会周期性地收到此回调，了解本地音频的相关信息。  <br>
  *        本地音频包括使用 RTC SDK 内部机制采集的麦克风音频，屏幕音频和本地混音音频信息。
  * @param engine ByteRTCVideo 对象
  * @param audioPropertiesInfos 本地音频信息，详见 ByteRTCLocalAudioPropertiesInfo{@link #ByteRTCLocalAudioPropertiesInfo} 。
  */
 /**
  * @locale en
  * @type callback
  * @region Audio Management
  * @brief After calling enableAudioPropertiesReport:{@link #ByteRTCVideo#enableAudioPropertiesReport:}, you will periodically receive this callback for the information about local audio. <br>
  *        Local audio includes the microphone audio, the screen audio captured using RTC SDK internal mechanisms, and locally mixing audio.
  * @param engine ByteRTCVideo object
  * @param audioPropertiesInfos See ByteRTCLocalAudioPropertiesInfo{@link #ByteRTCLocalAudioPropertiesInfo}.
  */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onLocalAudioPropertiesReport:(NSArray<ByteRTCLocalAudioPropertiesInfo *> * _Nonnull)audioPropertiesInfos;
 /**
  * @locale zh
  * @hidden(iOS)
  * @type callback
  * @region 音频设备管理
  * @brief 回调音频设备测试时的播放音量
  * @param volume 音频设备测试播放音量。取值范围：[0,255]
  * @note 调用 startAudioPlaybackDeviceTest:interval:{@link #ByteRTCAudioDeviceManager#startAudioPlaybackDeviceTest:interval:} 或 startAudioDeviceRecordTest:{@link #ByteRTCAudioDeviceManager#startAudioDeviceRecordTest:}，开始播放音频文件或录音时，将开启该回调。本回调为周期性回调，回调周期由上述接口的 `interval` 参数指定。
  */
 /**
  * @locale en
  * @hidden(iOS)
  * @type callback
  * @region Audio Device Management
  * @brief Notification on the playing volume during the test for the local audio devices
  * @param volume Playing volume during the test for the local audio devices. The range is [0,255].
  * @note Start an audio-device test by calling startAudioPlaybackDeviceTest:interval:{@link #ByteRTCAudioDeviceManager#startAudioPlaybackDeviceTest:interval:} or startAudioDeviceRecordTest:{@link #ByteRTCAudioDeviceManager#startAudioDeviceRecordTest:} will register this callback for regular notification on playing volume. You can set the time interval between each callback by passing a proper value when calling the API above.
  */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onAudioPlaybackDeviceTestVolume:(int)volume;

 /**
  * @locale zh
  * @hidden(iOS)
  * @type callback
  * @region 设备管理
  * @brief 音频设备音量改变回调。当通过系统设置，改变音频设备音量或静音状态时，触发本回调。本回调无需手动开启。
  * @param deviceType 设备类型，包括麦克风和扬声器，参阅 ByteRTCAudioDeviceType{@link #ByteRTCAudioDeviceType}。
  * @param volume 音量值，[0, 255]。当 volume 变为 0 时，muted 会转为 True。
  * @param muted 是否禁音状态。扬声器被设置为禁音时，muted 为 True，但 volume 保持不变。
  */
 /**
  * @locale en
  * @hidden(iOS)
  * @type callback
  * @region device management
  * @brief Callback to notify you the volume of the audio device has been changed or when the device has been muted or unmuted. No need to activate the notification beforehand.
  * @param deviceType Includes microphones and speakers. Refer to ByteRTCAudioDeviceType{@link #ByteRTCAudioDeviceType} for more details.
  * @param volume Volume ranging [0, 255]. When the volume turns to 0, muted turns to True.
  * @param muted Whether is muted. When a speaker is muted, muted turns True but volume remains unchanged.
  */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onAudioDeviceVolumeChanged:(ByteRTCAudioDeviceType)deviceType volume:(int)volume muted:(bool)muted;

 /**
  * @locale zh
  * @type callback
  * @region 音频管理
  * @brief 远端用户进房后，本地调用 enableAudioPropertiesReport:{@link #ByteRTCVideo#enableAudioPropertiesReport:} ，根据设置的 interval 值，本地会周期性地收到此回调，了解订阅的远端用户的音频信息。<br>
  *        远端用户的音频包括使用 RTC SDK 内部机制/自定义机制采集的麦克风音频和屏幕音频。
  * @param engine ByteRTCVideo 对象
  * @param audioPropertiesInfos 远端音频信息，其中包含音频流属性、房间 ID、用户 ID ，详见 ByteRTCRemoteAudioPropertiesInfo{@link #ByteRTCRemoteAudioPropertiesInfo}。
  * @param totalRemoteVolume 订阅的所有远端流的总音量，范围是 [0,255]。  <br>
  *       + [0,25] 接近无声；  <br>
  *       + [25,75] 为低音量；  <br>
  *       + [76,204] 为中音量；  <br>
  *       + [205,255] 为高音量。  
  */
 /**
  * @locale en
  * @type callback
  * @region Audio Management
  * @brief After calling enableAudioPropertiesReport:{@link #ByteRTCVideo#enableAudioPropertiesReport:}, you will periodically receive this callback for the information about the subscribed remote audio streams. <br>
  *        The remote audio streams includes the microphone audio and screen audio collected using the RTC SDK internal mechanism/custom mechanism.
  * @param engine ByteRTCVideo object
  * @param audioPropertiesInfos See ByteRTCRemoteAudioPropertiesInfo{@link #ByteRTCRemoteAudioPropertiesInfo}.
  * @param totalRemoteVolume The total volume of all the subscribed remote streams. The range is [0,255]. <br>
  *        + [0,25] Is close to silent; <br>
  *        + [25,75] Is low volume; <br>
  *        + [76,204] Is medium volume; <br>
  *        + [205,255] Is high volume. 
  */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onRemoteAudioPropertiesReport:(NSArray<ByteRTCRemoteAudioPropertiesInfo *> * _Nonnull)audioPropertiesInfos totalRemoteVolume:(NSInteger)totalRemoteVolume;
/**
 * @locale zh
 * @type callback
 * @region 音频管理
 * @brief 调用 enableAudioPropertiesReport:{@link #ByteRTCVideo#enableAudioPropertiesReport:}  后，根据设置的 `config.interval`，你会周期性地收到此回调，获取房间内的最活跃用户信息。
 * @param roomId 房间 ID
 * @param uid 最活跃用户（ActiveSpeaker）的用户 ID
 */
/**
 * @locale en
 * @type callback
 * @region Audio Management
 * @brief After calling enableAudioPropertiesReport:{@link #ByteRTCVideo#enableAudioPropertiesReport:}, you will periodically receive this callback for the active speaker information. 
 * @param roomId  Room ID.
 * @param uid The user ID of the active speaker.
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onActiveSpeaker:(NSString * _Nonnull)roomId uid:(NSString *_Nonnull)uid;
#pragma mark - Core Video Delegate Methods
// @name core video event callback

/**
 * @locale zh
 * @deprecated since 3.36 and will be deleted in 3.51, use rtcRoom:onUserPublishStream:type:{@link #ByteRTCRoomDelegate#rtcRoom:onUserPublishStream:type:}, rtcRoom:onUserPublishScreen:type:{@link #ByteRTCRoomDelegate#rtcRoom:onUserPublishScreen:type:}, rtcRoom:onUserUnpublishStream:type:reason:{@link #ByteRTCRoomDelegate#rtcRoom:onUserUnpublishStream:type:reason:} and rtcRoom:onUserUnpublishScreen:type:reason:{@link #ByteRTCRoomDelegate#rtcRoom:onUserUnpublishScreen:type:reason:} instead.
 * @type callback
 * @region 视频管理
 * @param engine ByteRTCVideo 实例
 * @brief 房间内用户暂停/恢复发送视频流时，房间内其他用户会收到此回调。
 * @param uid 暂停/恢复发送视频流的用户 ID。
 * @param muteState 视频流的发送状态。参看 ByteRTCMuteState{@link #ByteRTCMuteState}。
 */
/**
 * @locale en
 * @deprecated since 3.45 and will be deleted in 3.51, use rtcRoom:onUserPublishStream:type:{@link #ByteRTCRoomDelegate#rtcRoom:onUserPublishStream:type:}, rtcRoom:onUserPublishScreen:type:{@link #ByteRTCRoomDelegate#rtcRoom:onUserPublishScreen:type:}, rtcRoom:onUserUnpublishStream:type:reason:{@link #ByteRTCRoomDelegate#rtcRoom:onUserUnpublishStream:type:reason:} and rtcRoom:onUserUnpublishScreen:type:reason:{@link #ByteRTCRoomDelegate#rtcRoom:onUserUnpublishScreen:type:reason:} instead.
 * @type callback
 * @region Video management
 * @param engine ByteRTCVideo instance
 * @brief Transmission state change of an video stream in the room triggers this callback.
 * @param uid The user who changes his/her transmission state of the video streams
 * @param muteState Transmission state of the video streams. Refer to ByteRTCMuteState{@link #ByteRTCMuteState} for more details.
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onUserMuteVideo:(NSString * _Nonnull)roomId
              uid:(NSString * _Nonnull)uid withMuteState:(ByteRTCMuteState)muteState 
              NS_SWIFT_NAME(rtcEngine(_:onUserMuteVideo:uid:withMuteState:)) __deprecated_msg("Will be removed in new version");
/**
 * @locale zh
 * @type callback
 * @region 视频管理
 * @brief 房间内的可见用户调用 startVideoCapture{@link #ByteRTCVideo#startVideoCapture} 开启内部视频采集时，房间中其他用户会收到此回调。
 * @param engine ByteRTCVideo 实例
 * @param roomId 开启视频采集的用户所在的房间 ID
 * @param uid 调用 startVideoCapture{@link #ByteRTCVideo#startVideoCapture} 接口的远端用户 ID
 */
/**
 * @locale en
 * @type callback
 * @region Video management
 * @brief The remote clients in the room will be informed of the state change via this callback after the visible user starts video capture by startVideoCapture{@link #ByteRTCVideo#startVideoCapture}.
 * @param engine ByteRTCVideo instance
 * @param roomId ID of the room where the remote user enables video capture
 * @param uid The user who starts the internal video capture
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onUserStartVideoCapture:(NSString * _Nonnull)roomId
              uid:(NSString * _Nonnull)uid;
/**
 * @locale zh
 * @type callback
 * @region 视频管理
 * @brief 房间内的可见用户调用 stopVideoCapture{@link #ByteRTCVideo#stopVideoCapture} 关闭内部视频采集时，房间内其他用户会收到此回调。<br>
 *        若发布视频数据前未开启采集，房间内所有可见用户会收到此回调。
 * @param engine ByteRTCVideo 实例
 * @param roomId 关闭视频采集的用户所在的房间 ID
 * @param uid 关闭视频采集的远端用户 ID
 */
/**
 * @locale en
 * @type callback
 * @region Video management
 * @brief The remote clients in the room will be informed of the state change via  this callback after the visible user stops video capture by calling stopVideoCapture{@link #ByteRTCVideo#stopVideoCapture}.<br>
 *        If you don't start video capture before you publish video data, all visible user will receive this callback.
 * @param engine ByteRTCVideo instance
 * @param roomId ID of the room where the remote user disables video capture
 * @param uid The user who stops the internal video capture
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onUserStopVideoCapture:(NSString * _Nonnull)roomId
              uid:(NSString * _Nonnull)uid;
/**
 * @locale zh
 * @type callback
 * @region 视频管理
 * @brief 第一帧本地采集的视频/屏幕共享画面在本地视图渲染完成时，收到此回调。
 * @param engine ByteRTCVideo 对象
 * @param streamIndex 流属性，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param frameInfo 视频帧信息，参看 ByteRTCVideoFrameInfo{@link #ByteRTCVideoFrameInfo}
 */
/**
 * @locale en
 * @type callback
 * @region Video Management
 * @brief Receive this callback when the first locally captured video/screen share screen is rendered in the local view.
 * @param engine ByteRTCVideo object
 * @param streamIndex Stream property. See ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param frameInfo Video frame information. See ByteRTCVideoFrameInfo{@link #ByteRTCVideoFrameInfo}
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onFirstLocalVideoFrameCaptured:(ByteRTCStreamIndex)streamIndex withFrameInfo:(ByteRTCVideoFrameInfo * _Nonnull)frameInfo NS_SWIFT_NAME(rtcEngine(_:onFirstLocalVideoFrameCaptured:withFrameInfo:));
/**
 * @locale zh
 * @type callback
 * @region 视频管理
 * @brief SDK 内部渲染成功远端视频流首帧后，收到此回调。
 * @param engine ByteRTCVideo 对象
 * @param streamKey 远端流信息，参看 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
 * @param frameInfo 视频帧信息，参看 ByteRTCVideoFrameInfo{@link #ByteRTCVideoFrameInfo}
 */
/**
 * @locale en
 * @type callback
 * @region Video Management
 * @brief Receive this callback after the first frame of remote video stream is locally rendered by SDK.
 * @param engine ByteRTCVideo object
 * @param streamKey  Remote stream information. See ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
 * @param frameInfo  Video frame information. See ByteRTCVideoFrameInfo{@link #ByteRTCVideoFrameInfo}
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onFirstRemoteVideoFrameRendered:(ByteRTCRemoteStreamKey * _Nonnull)streamKey withFrameInfo:(ByteRTCVideoFrameInfo * _Nonnull)frameInfo NS_SWIFT_NAME(rtcEngine(_:onFirstRemoteVideoFrameRendered:withFrameInfo:));
/**
 * @locale zh
 * @type callback
 * @region 视频管理
 * @brief SDK 接收并解码远端视频流首帧后，收到此回调。
 * @param engine ByteRTCVideo 对象
 * @param streamKey 远端流信息，参看 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
 * @param frameInfo 视频帧信息，参看 ByteRTCVideoFrameInfo{@link #ByteRTCVideoFrameInfo}
 * @note 
 *       + 对于主流，进入房间后，仅在发布端第一次发布的时候，订阅端会收到该回调，此后不受重新发布的影响，只要不重新加入房间，就不会再收到该回调。<br>
 *       + 对于屏幕流，用户每次重新发布屏幕视频流在订阅端都会重新触发一次该回调。
 */
/**
 * @locale en
 * @type callback
 * @region Video Management
 * @brief Receive this callback after the first frame of remote video stream is received and decoded by SDK.
 * @param engine ByteRTCVideo object
 * @param streamKey  Remote stream information, see ByteRTCRemoteStreamKey {@link #ByteRTCRemoteStreamKey}
 * @param frameInfo  Video frame information, see ByteRTCVideoFrameInfo {@link #ByteRTCVideoFrameInfo}
 * @note 
 *       + For main stream, after joining the room, the subscriber will receive this callback only when the publisher publishes video stream for the first time.<br>
 *       + For screen-sharing stream, the subscriber will receive this callback every time the publisher publishes or republishes the screen video stream.
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onFirstRemoteVideoFrameDecoded:(ByteRTCRemoteStreamKey * _Nonnull)streamKey withFrameInfo:(ByteRTCVideoFrameInfo * _Nonnull)frameInfo NS_SWIFT_NAME(rtcEngine(_:onFirstRemoteVideoFrameDecoded:withFrameInfo:));
/**
 * @locale zh
 * @type callback
 * @region 视频管理
 * @brief 远端视频大小或旋转信息发生改变时，房间内订阅此视频流的用户会收到此回调。
 * @param engine ByteRTCVideo 对象
 * @param streamKey 流属性，参看 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
 * @param frameInfo 视频帧信息，参看 ByteRTCVideoFrameInfo{@link #ByteRTCVideoFrameInfo}
 */
/**
 * @locale en
 * @type callback
 * @region Video Management
 * @brief Users in the room who subscribe to this video stream receive this callback when the remote video size or rotation information changes.
 * @param engine ByteRTCVideo object
 * @param streamKey Stream property. See ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
 * @param frameInfo Video frame information. See ByteRTCVideoFrameInfo{@link #ByteRTCVideoFrameInfo}
 */
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onRemoteVideoSizeChanged:(ByteRTCRemoteStreamKey *_Nonnull)streamKey withFrameInfo:(ByteRTCVideoFrameInfo *_Nonnull)frameInfo NS_SWIFT_NAME(rtcEngine(_:onRemoteVideoSizeChanged:withFrameInfo:));
/**
 * @locale zh
 * @type callback
 * @region 视频管理
 * @brief 本地视频大小或旋转信息发生改变时，收到此回调。
 * @param engine ByteRTCVideo 对象
 * @param streamIndex 流属性，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param frameInfo 视频帧信息，参看 ByteRTCVideoFrameInfo{@link #ByteRTCVideoFrameInfo}
 */
/**
 * @locale en
 * @type callback
 * @region video management
 * @brief Receive this callback when local video size or rotation information changes.
 * @param engine  ByteRTCVideo object
 * @param streamIndex Stream property. See ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param frameInfo Frame information. See ByteRTCVideoFrameInfo{@link #ByteRTCVideoFrameInfo}
 */
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onLocalVideoSizeChanged:(ByteRTCStreamIndex)streamIndex withFrameInfo:(ByteRTCVideoFrameInfo *_Nonnull)frameInfo NS_SWIFT_NAME(rtcEngine(_:onLocalVideoSizeChanged:withFrameInfo:));
/**
 * @locale zh
 * @deprecated since 3.37 and will be deleted in 3.51, use rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:} and rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:} instead.
 * @type callback
 * @region 引擎管理
 * @brief 媒体设备状态回调。提示音频采集、音频播放、摄像头视频采集、屏幕视频采集四种媒体设备的状态。
 * @param engine ByteRTCVideo 实例
 * @param deviceID 设备 ID
 * @param deviceType 设备类型，参看 ByteRTCMediaDeviceType{@link #ByteRTCMediaDeviceType}。
 * @param deviceState 设备状态，参看 ByteRTCMediaDeviceState{@link #ByteRTCMediaDeviceState}。
 * @param deviceError 设备错误类型，参看 ByteRTCMediaDeviceError{@link #ByteRTCMediaDeviceError}。
 */
/**
 * @locale en
 * @deprecated since 3.45 and will be deleted in 3.51, use rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:} and rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:} instead.
 * @type callback
 * @region Engine management
 * @brief Media device state callback, returns the state of four media devices: audio capture, audio playback, video capture, and screen capture.
 * @param engine ByteRTCVideo instance
 * @param deviceID Device ID
 * @param deviceType Device type. See ByteRTCMediaDeviceType{@link #ByteRTCMediaDeviceType}.
 * @param deviceState Device state. See ByteRTCMediaDeviceState{@link #ByteRTCMediaDeviceState}.
 * @param deviceError Device error. See ByteRTCMediaDeviceError{@link #ByteRTCMediaDeviceError}.
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onMediaDeviceStateChanged:(NSString*_Nonnull)deviceID
        device_type:(ByteRTCMediaDeviceType)deviceType
        device_state:(ByteRTCMediaDeviceState)deviceState
        device_error:(ByteRTCMediaDeviceError)deviceError
    __attribute((deprecated("Will be removed in new version")));
/**
 * @locale zh
 * @type callback
 * @region 引擎管理
 * @brief 音频设备状态回调。提示音频采集、音频播放等设备的状态。
 * @param engine ByteRTCVideo 实例
 * @param deviceID 设备 ID
 * @param deviceType 设备类型，参看 ByteRTCAudioDeviceType{@link #ByteRTCAudioDeviceType}。
 * @param deviceState 设备状态，参看 ByteRTCMediaDeviceState{@link #ByteRTCMediaDeviceState}。
 * @param deviceError 设备错误类型，参看 ByteRTCMediaDeviceError{@link #ByteRTCMediaDeviceError}。
 */
/**
 * @locale en
 * @type callback
 * @region Engine management
 * @brief Audio device state callback, returns the state of audio capture and audio playback devices.
 * @param engine ByteRTCVideo instance
 * @param deviceID Device ID
 * @param deviceType Device type. See ByteRTCAudioDeviceType{@link #ByteRTCAudioDeviceType}.
 * @param deviceState Device state. See ByteRTCMediaDeviceState{@link #ByteRTCMediaDeviceState}.
 * @param deviceError Device error. See ByteRTCMediaDeviceError{@link #ByteRTCMediaDeviceError}.
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onAudioDeviceStateChanged:(NSString*_Nonnull)deviceID
      device_type:(ByteRTCAudioDeviceType)deviceType
     device_state:(ByteRTCMediaDeviceState)deviceState
     device_error:(ByteRTCMediaDeviceError)deviceError;
/**
 * @locale zh
 * @type callback
 * @region 引擎管理
 * @brief 视频设备状态发生改变回调。当设备的视频状态发生改变时，SDK 会触发该回调，提示摄像头视频采集、屏幕视频采集等设备的状态。
 * @param  deviceID 设备 ID
 * @param  deviceType 设备类型，参看 ByteRTCVideoDeviceType{@link #ByteRTCVideoDeviceType}。
 * @param  deviceState 设备状态，参看 ByteRTCMediaDeviceState{@link #ByteRTCMediaDeviceState}。
 * @param  deviceError 设备错误类型，参看 ByteRTCMediaDeviceError{@link #ByteRTCMediaDeviceError}。
 */
/**
 * @locale en
 * @type callback
 * @region Engine management
 * @brief Video device state callback. It returns the state of media devices, including video capture and screen capture.
 * @param  deviceID Device ID
 * @param  deviceType Device type. Refer to ByteRTCVideoDeviceType{@link #ByteRTCVideoDeviceType} for more details.
 * @param  deviceState Device state. Refer to ByteRTCMediaDeviceState{@link #ByteRTCMediaDeviceState} for more details.
 * @param  deviceError Device error. Refer to ByteRTCMediaDeviceError{@link #ByteRTCMediaDeviceError} for more details.
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onVideoDeviceStateChanged:(NSString*_Nonnull)deviceID
      device_type:(ByteRTCVideoDeviceType)deviceType
     device_state:(ByteRTCMediaDeviceState)deviceState
     device_error:(ByteRTCMediaDeviceError)deviceError;
/**
 * @locale zh
 * @deprecated since 3.37 and will be deleted in 3.51, use rtcEngine:onAudioDeviceWarning:deviceType:deviceWarning:{@link #ByteRTCVideoDelegate#rtcEngine:onAudioDeviceWarning:deviceType:deviceWarning:} and rtcEngine:onVideoDeviceWarning:deviceType:deviceWarning:{@link #ByteRTCVideoDelegate#rtcEngine:onVideoDeviceWarning:deviceType:deviceWarning:} instead.
 * @type callback
 * @region 引擎管理
 * @brief 媒体设备警告回调。媒体设备包括：音频采集设备、音频渲染设备、和视频采集设备。
 * @param engine ByteRTCVideo 对象
 * @param deviceId 设备 ID
 * @param deviceType 参看 ByteRTCMediaDeviceType{@link #ByteRTCMediaDeviceType}
 * @param deviceWarning 参看 ByteRTCMediaDeviceWarning{@link #ByteRTCMediaDeviceWarning}
 */
/**
 * @locale en
 * @deprecated since 3.45 and will be deleted in 3.51, use rtcEngine:onAudioDeviceWarning:deviceType:deviceWarning:{@link #ByteRTCVideoDelegate#rtcEngine:onAudioDeviceWarning:deviceType:deviceWarning:} and rtcEngine:onVideoDeviceWarning:deviceType:deviceWarning:{@link #ByteRTCVideoDelegate#rtcEngine:onVideoDeviceWarning:deviceType:deviceWarning:} instead.
 * @type callback
 * @region Engine Management
 * @brief Media device warning callback. The media devices includes: audio capture devices, audio rendering devices, and video capture devices.
 * @param engine ByteRTCVideo object
 * @param deviceId Device ID
 * @param deviceType See ByteRTCMediaDeviceType{@link #ByteRTCMediaDeviceType}
 * @param deviceWarning See ByteRTCMediaDeviceWarning{@link #ByteRTCMediaDeviceWarning}
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onMediaDeviceWarning:(NSString*_Nonnull)deviceId
    deviceType:(ByteRTCMediaDeviceType)deviceType
    deviceWarning:(ByteRTCMediaDeviceWarning)deviceWarning
    __deprecated_msg("Will be removed in new version");
/**
 * @locale zh
 * @type callback
 * @region 引擎管理
 * @brief 音频设备警告回调。音频设备包括音频采集设备和音频渲染设备。
 * @param engine ByteRTCVideo 对象
 * @param deviceId 设备 ID
 * @param deviceType 参看 ByteRTCAudioDeviceType{@link #ByteRTCAudioDeviceType}
 * @param deviceWarning 参看 ByteRTCMediaDeviceWarning{@link #ByteRTCMediaDeviceWarning}
 */
/**
 * @locale en
 * @type callback
 * @region Engine Management
 * @brief Audio device warning callback. The audio devices includes audio capture devices and audio rendering devices.
 * @param engine ByteRTCVideo object
 * @param deviceId Device ID
 * @param deviceType See ByteRTCAudioDeviceType{@link #ByteRTCAudioDeviceType}
 * @param deviceWarning See ByteRTCMediaDeviceWarning{@link #ByteRTCMediaDeviceWarning}
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onAudioDeviceWarning:(NSString*_Nonnull)deviceId
    deviceType:(ByteRTCAudioDeviceType)deviceType
    deviceWarning:(ByteRTCMediaDeviceWarning)deviceWarning;
/**
 * @locale zh
 * @type callback
 * @region 引擎管理
 * @brief 视频设备警告回调。视频设备包括视频采集设备。
 * @param engine ByteRTCVideo 对象
 * @param deviceId 设备 ID
 * @param deviceType 参看 ByteRTCVideoDeviceType{@link #ByteRTCVideoDeviceType}
 * @param deviceWarning 参看 ByteRTCMediaDeviceWarning{@link #ByteRTCMediaDeviceWarning}
 */
/**
 * @locale en
 * @type callback
 * @region Engine Management
 * @brief Video device warning callback. The video devices includes video capture devices.
 * @param engine ByteRTCVideo object
 * @param deviceId Device ID
 * @param deviceType See ByteRTCVideoDeviceType{@link #ByteRTCVideoDeviceType}
 * @param deviceWarning See ByteRTCMediaDeviceWarning{@link #ByteRTCMediaDeviceWarning}
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onVideoDeviceWarning:(NSString*_Nonnull)deviceId
    deviceType:(ByteRTCVideoDeviceType)deviceType
    deviceWarning:(ByteRTCMediaDeviceWarning)deviceWarning;

/**
 * @locale zh
 * @type callback
 * @region 房间管理
 * @brief 本地音频首帧发送状态发生改变时，收到此回调。
 * @param engine ByteRTCVideo 对象
 * @param roomId 音频流发布用户所在的房间 ID
 * @param user 本地用户信息，详见 ByteRTCUser{@link #ByteRTCUser}
 * @param state 首帧发送状态，详见 ByteRTCFirstFrameSendState{@link #ByteRTCFirstFrameSendState}
 */
/**
 * @locale en
 * @type callback
 * @region Room Management
 * @brief Receive this callback when the sending state of the first audio frame changes.
 * @param engine ByteRTCVideo object
 * @param roomId ID of the room from which the audio is published
 * @param user Local user information. See ByteRTCUser{@link #ByteRTCUser}
 * @param state First frame sending status. See ByteRTCFirstFrameSendState{@link #ByteRTCFirstFrameSendState}
 */
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onAudioFrameSendStateChanged:(NSString * _Nonnull)roomId
              rtcUser:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFrameSendState)state;

/**
 * @locale zh
 * @type callback
 * @region 房间管理
 * @brief 本地视频首帧发送状态发生改变时，收到此回调。
 * @param engine ByteRTCVideo 对象
 * @param roomId 视频流发布用户所在的房间 ID
 * @param user 本地用户信息，详见 ByteRTCUser{@link #ByteRTCUser}
 * @param state 首帧发送状态，详见 ByteRTCFirstFrameSendState{@link #ByteRTCFirstFrameSendState}
 */
/**
 * @locale en
 * @type callback
 * @region Room management
 * @brief Receive this callback when the video first frame sending state changes
 * @param engine ByteRTCVideo object
 * @param roomId ID of the room from which the video is published
 * @param user Local user information. See ByteRTCUser{@link #ByteRTCUser}
 * @param state First frame sending status. See ByteRTCFirstFrameSendState{@link #ByteRTCFirstFrameSendState}
 */
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onVideoFrameSendStateChanged:(NSString * _Nonnull)roomId
          rtcUser:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFrameSendState)state;

/**
 * @locale zh
 * @type callback
 * @region 房间管理
 * @brief 屏幕共享流的视频首帧发送状态发生改变时，收到此回调。
 * @param engine ByteRTCVideo 对象。  
 * @param roomId 屏幕流发布用户所在的房间 ID
 * @param user 本地用户信息，参看 ByteRTCUser{@link #ByteRTCUser}
 * @param state 首帧发送状态，参看 ByteRTCFirstFrameSendState{@link #ByteRTCFirstFrameSendState}
 */
/**
 * @locale en
 * @type callback
 * @region Room Management
 * @brief You will receive this callback when the first video frame of the screen sharing is sent witha change in status.
 * @param engine ByteRTCVideo instance.
 * @param roomId ID of the room from which the screen stream is published
 * @param user Local user information. See ByteRTCUser{@link #ByteRTCUser}
 * @param state First frame sending status. See ByteRTCFirstFrameSendState{@link #ByteRTCFirstFrameSendState}
 */
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onScreenVideoFrameSendStateChanged:(NSString * _Nonnull)roomId
          rtcUser:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFrameSendState)state;

/**
 * @locale zh
 * @type callback
 * @region 房间管理
 * @brief 音频首帧播放状态发生改变时，收到此回调。
 * @param engine ByteRTCVideo 对象。  
 * @param roomId 音频流发布用户所在的房间 ID
 * @param user 音频流来源的用户信息，参看 ByteRTCUser{@link #ByteRTCUser}
 * @param state 首帧播放状态，参看 ByteRTCFirstFramePlayState{@link #ByteRTCFirstFramePlayState}
 */
/**
 * @locale en
 * @type callback
 * @region Room Management
 * @brief Receive this callback when the audio first frame playback state changes
 * @param engine ByteRTCVideo instance. 
 * @param roomId ID of the room from which the audio is published
 * @param user User information from the audio stream. See ByteRTCUser{@link #ByteRTCUser}
 * @param state First frame playback status. See ByteRTCFirstFramePlayState{@link #ByteRTCFirstFramePlayState}
 */
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onAudioFramePlayStateChanged:(NSString * _Nonnull)roomId
          rtcUser:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFramePlayState)state;

/**
 * @locale zh
 * @type callback
 * @region 房间管理
 * @brief 视频首帧播放状态发生改变时，收到此回调。
 * @param engine ByteRTCVideo 对象。  
 * @param user 视频流来源的用户信息，参看 ByteRTCUser{@link #ByteRTCUser}
 * @param roomId 视频流发布用户所在的房间 ID
 * @param state 首帧播放状态，参看 ByteRTCFirstFramePlayState{@link #ByteRTCFirstFramePlayState}
 */
/**
 * @locale en
 * @type callback
 * @region Room Management
 * @brief Receive this callback when the video first frame playback state changes
 * @param engine ByteRTCVideo instance.
 * @param roomId ID of the room from which the video is published
 * @param user User information from the video stream source. See ByteRTCUser{@link #ByteRTCUser}
 * @param state First frame playback state. See ByteRTCFirstFramePlayState{@link #ByteRTCFirstFramePlayState}
 */
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onVideoFramePlayStateChanged:(NSString * _Nonnull)roomId
          rtcUser:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFramePlayState)state;

/**
 * @locale zh
 * @type callback
 * @region 房间管理
 * @brief 屏幕共享流视频首帧播放状态发生改变时，收到此回调。
 * @param engine ByteRTCVideo 对象。  
 * @param roomId 屏幕流发布用户所在的房间 ID
 * @param user 屏幕共享流来源的用户信息，参看 ByteRTCUser{@link #ByteRTCUser}
 * @param state 首帧播放状态，参看 ByteRTCFirstFramePlayState{@link #ByteRTCFirstFramePlayState}
 */
/**
 * @locale en
 * @type callback
 * @region Room Management
 * @brief You will receive this callback when the first frame playback state changes
 * @param engine ByteRTCVideo object. 
 * @param roomId ID of the room from which the screen stream is published
 * @param user Screen sharing user information from the stream source. See ByteRTCUser{@link #ByteRTCUser}
 * @param state First frame playback status. See ByteRTCFirstFramePlayState{@link #ByteRTCFirstFramePlayState}
 */
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onScreenVideoFramePlayStateChanged:(NSString * _Nonnull)roomId rtcUser:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFramePlayState)state;
#pragma mark - Media Stream Delegate Methods
// @name media data event callback
/**
 * @locale zh
 *  @type callback
 *  @region 音频事件回调
 *  @brief 发布音频流时，采集到第一帧音频帧，收到该回调。
 *  @param engine ByteRTCVideo 对象
 *  @param streamIndex 音频流属性, 详见 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @note 如果发布音频流时，未开启本地音频采集，SDK 会推送静音帧，也会收到此回调。
 */
/**
 * @locale en
 *  @type callback
 *  @region Audio event callback
 *  @brief Receive the callback when publishing local audio stream.
 *  @param engine ByteRTCVideo object
 *  @param streamIndex  Audio stream properties. See ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onFirstLocalAudioFrame:(ByteRTCStreamIndex) streamIndex;
#pragma mark - Media Device Delegate Methods
// @name media device event callback
/**
 * @locale zh
 * @hidden(macOS)
 * @deprecated since 3.38 and will be deleted in 3.51, use rtcEngine:onAudioRouteChanged:{@link #ByteRTCVideoDelegate#rtcEngine:onAudioRouteChanged:} instead.
 * @type callback
 * @region 音频事件回调
 * @brief 音频播放设备变化时，收到该回调。
 * @param engine ByteRTCVideo 实例。
 * @param device 新的音频设备，详见 ByteRTCAudioPlaybackDevice{@link #ByteRTCAudioPlaybackDevice}
 * @note 音频设备设置与音频路由策略，详见 setAudioPlaybackDevice:{@link #ByteRTCVideo#setAudioPlaybackDevice:}
 */
/**
 * @locale en
 * @hidden(macOS)
 * @deprecated since 3.45 and will be deleted in 3.51, use rtcEngine:onAudioRouteChanged:{@link #ByteRTCVideoDelegate#rtcEngine:onAudioRouteChanged:} instead.
 * @type callback
 * @region Audio event callback
 * @brief You will receive this callback when the audio playback device changes.
 * @param engine ByteRTCVideo instance.
 * @param device New audio playback device. See ByteRTCAudioPlaybackDevice{@link #ByteRTCAudioPlaybackDevice}
 * @note For the settings of audio playback device and audio routing, see setAudioPlaybackDevice:{@link #ByteRTCVideo#setAudioPlaybackDevice:}.
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onAudioPlaybackDeviceChanged:(ByteRTCAudioPlaybackDevice)device __deprecated_msg("Will be removed in new version");
/**
 * @locale zh
 * @hidden(macOS)
 * @type callback
 * @region 音频事件回调
 * @brief 音频播放路由变化时，收到该回调。
 * @param device 新的音频播放路由，详见 ByteRTCAudioRoute{@link #ByteRTCAudioRoute}
 * @note 插拔音频外设，或调用 setAudioRoute:{@link #ByteRTCVideo#setAudioRoute:} 都可能触发音频路由切换，详见[移动端设置音频路由](https://www.volcengine.com/docs/6348/117836) 。
 */
/**
 * @locale en
 * @hidden(macOS)
 * @type callback
 * @region Audio event callback
 * @brief RTC notifies the audio route changes via this callback.
 * @param device Current audio playback device. Refer to ByteRTCAudioRoute{@link #ByteRTCAudioRoute} for more information.
 * @note Either of the following actions will lead to audio route switching. See [Set the Audio Route](https://docs.byteplus.com/byteplus-rtc/docs/117836). <br>
 * + Connecting/Disconnecting an audio device<br>
 * + Designating the other audio device by calling setAudioRoute:{@link #ByteRTCVideo#setAudioRoute:}.
 */
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onAudioRouteChanged:(ByteRTCAudioRoute)device;
#pragma mark custom message Delegate Methods
// @name send message callback
/**
 * @locale zh
 * @type callback
 * @region 视频管理
 * @brief 收到通过调用 sendSEIMessage:andMessage:andRepeatCount:andCountPerFrame:{@link #ByteRTCVideo#sendSEIMessage:andMessage:andRepeatCount:andCountPerFrame:} 发送带有 SEI 消息的视频帧时，收到此回调。
 * @param engine 当前 ByteRTCVideo 实例。
 * @param remoteStreamKey 包含 SEI 发送者的用户名，所在的房间名和媒体流，参看 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
 * @param message 收到的 SEI 消息内容
 */
/**
 * @locale en
 * @type callback
 * @region Video management
 * @brief Receive this callback when you receive a video frame with a SEI message by calling sendSEIMessage:andMessage:andRepeatCount:andCountPerFrame:{@link #ByteRTCVideo#sendSEIMessage:andMessage:andRepeatCount:andCountPerFrame:}.
 * @param engine Current ByteRTCVideo instance
 * @param remoteStreamKey Contains the user name, room name and media stream of the SEI sender. See ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
 * @param message Received SEI message content
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onSEIMessageReceived:(ByteRTCRemoteStreamKey* _Nonnull)remoteStreamKey andMessage:(NSData* _Nonnull)message;
/**
 * @locale zh
 * @type callback
 * @region 消息
 * @brief 黑帧视频流发布状态回调。  <br>
 *        在语音通话场景下，本地用户调用 sendSEIMessage:andMessage:andRepeatCount:andCountPerFrame:{@link #ByteRTCVideo#sendSEIMessage:andMessage:andRepeatCount:andCountPerFrame:} 通过黑帧视频流发送 SEI 数据时，流的发送状态会通过该回调通知远端用户。  <br>
 *        你可以通过此回调判断携带 SEI 数据的视频帧为黑帧，从而不对该视频帧进行渲染。
 * @param engine 当前 ByteRTCVideo 实例。
 * @param remoteStreamKey 远端流信息，参看 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}。
 * @param eventType 黑帧视频流状态，参看 ByteRTCSEIStreamEventType{@link #ByteRTCSEIStreamEventType}
 */
/**
 * @locale en
 * @type callback
 * @region Message
 * @brief Callback about publishing status of the black frame video stream.  <br>
 *        In a voice call scenario, when the local user calls sendSEIMessage:andMessage:andRepeatCount:andCountPerFrame:{@link #ByteRTCVideo#sendSEIMessage:andMessage:andRepeatCount:andCountPerFrame:} to send SEI data with a black frame, the sending status of the stream is notified to the remote user through this callback.  <br>
 *        You can tell from this callback that the video frame carrying SEI data is a black frame and thus not render that video frame.
 * @param engine Current ByteRTCVideo instance
 * @param remoteStreamKey Information about stream from the remote user, see ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}.
 * @param eventType State of the black frame video stream, see ByteRTCSEIStreamEventType{@link #ByteRTCSEIStreamEventType}.
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onSEIStreamUpdate:(ByteRTCRemoteStreamKey* _Nonnull)remoteStreamKey eventType:(ByteRTCSEIStreamEventType)eventType;
/**
 * @locale zh
 * @type callback
 * @region 音频管理
 * @brief 音频流同步信息回调。可以通过此回调，在远端用户调用 sendStreamSyncInfo:config:{@link #ByteRTCVideo#sendStreamSyncInfo:config:} 发送音频流同步消息后，收到远端发送的音频流同步信息。  
 * @param engine 当前 ByteRTCVideo 实例。
 * @param remoteStreamKey 远端流信息，详见 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey} 。
 * @param streamType 媒体流类型，详见 ByteRTCSyncInfoStreamType{@link #ByteRTCSyncInfoStreamType} 。
 * @param data 消息内容。
 */
/**
 * @locale en
 * @type callback
 * @region audio management
 * @brief Audio stream synchronization information callback. You can use this callback to receive audio stream synchronization information sent remotely after the remote user calls sendStreamSyncInfo:config:{@link #ByteRTCVideo#sendStreamSyncInfo:config:} to send an audio stream synchronization message. 
 * @param engine  Current ByteRTCVideo instance.
 * @param remoteStreamKey  For remote stream information. See ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}.
 * @param streamType  Media stream type. See ByteRTCSyncInfoStreamType{@link #ByteRTCSyncInfoStreamType}.
 * @param data Message content.
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onStreamSyncInfoReceived:(ByteRTCRemoteStreamKey* _Nonnull)remoteStreamKey streamType:(ByteRTCSyncInfoStreamType)streamType data:(NSData* _Nonnull)data;
#pragma mark - Statistics Delegate Methods
// @name data statistics callback
/**
 * @locale zh
 * @type callback
 * @region 数据统计
 * @brief 报告当前设备 cpu 与 memory 使用率，每 2s 触发一次。
 * @param engine ByteRTCVideo 对象
 * @param stats cpu 和 memory 使用率信息，详见 ByteRTCSysStats{@link #ByteRTCSysStats} 数据类型
 * @list 引擎管理
 * @order 2
 */
/**
 * @locale en
 * @type callback
 * @region Data statistics
 * @brief Report the current device CPU and memory usage, which is triggered every 2s.
 * @param engine ByteRTCVideo object
 * @param stats Cpu and memory usage information. See ByteRTCSysStats{@link #ByteRTCSysStats} data type
 * @list Engine Management
 * @order 2
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onSysStats:(const ByteRTCSysStats * _Nonnull)stats NS_SWIFT_NAME(rtcEngine(_:onSysStats:));
/**
 * @locale zh
 * @type callback
 * @region 音频事件回调
 * @brief 本地音频流的状态发生改变时，收到此回调。
 * @param engine ByteRTCVideo 对象
 * @param state 本地音频设备的当前状态，详见 ByteRTCLocalAudioStreamState{@link #ByteRTCLocalAudioStreamState}
 * @param error 本地音频流状态改变时的错误码，详见 ByteRTCLocalAudioStreamError{@link #ByteRTCLocalAudioStreamError}
 * @list 引擎管理
 * @order 2
 */
/**
 * @locale en
 * @type callback
 * @region Audio event callback
 * @brief Receive this callback when the state of the local audio stream changes.
 * @param engine ByteRTCVideo object
 * @param state The current state of the local audio device. See ByteRTCLocalAudioStreamState{@link #ByteRTCLocalAudioStreamState}
 * @param error Error code when the state of the local audio stream changes. See ByteRTCLocalAudioStreamError{@link #ByteRTCLocalAudioStreamError}
 */
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onLocalAudioStateChanged:(ByteRTCLocalAudioStreamState)state
                     error:(ByteRTCLocalAudioStreamError)error;
/**
 * @locale zh
 *  @type callback
 *  @region 音频事件回调
 *  @brief 订阅的远端音频流状态发生改变时，收到此回调。
 *  @param engine ByteRTCVideo 对象
 *  @param key 远端流信息, 详见 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
 *  @param state 远端音频流的当前状态，详见 ByteRTCRemoteAudioState{@link #ByteRTCRemoteAudioState}
 *  @param reason 远端音频流状态改变的原因，详见 ByteRTCRemoteAudioStateChangeReason{@link #ByteRTCRemoteAudioStateChangeReason}
 */
/**
 * @locale en
 *  @type callback
 *  @region Audio event callback
 *  @brief Receive this callback when the state of the remote audio stream subscribed to changes.
 *  @param engine ByteRTCVideo object
 *  @param key Remote stream information. See ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
 *  @param state The current state of the remote audio stream. See ByteRTCRemoteAudioState{@link #ByteRTCRemoteAudioState}
 *  @param reason The reason for the change in the state of the remote audio stream. See ByteRTCRemoteAudioStateChangeReason{@link #ByteRTCRemoteAudioStateChangeReason}
 */
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onRemoteAudioStateChanged:(ByteRTCRemoteStreamKey * _Nonnull)key
                      state:(ByteRTCRemoteAudioState)state
                      reason:(ByteRTCRemoteAudioStateChangeReason)reason;
/**
 * @locale zh
 * @type callback
 * @region 视频管理
 * @brief 本地视频流的状态发生改变时，收到该事件。
 * @param engine ByteRTCVideo 对象
 * @param streamIndex 流属性，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param state 本地视频流的当前状态，参看 ByteRTCLocalVideoStreamState{@link #ByteRTCLocalVideoStreamState}
 * @param error 本地视频状态改变时的错误码，参看 ByteRTCLocalVideoStreamError{@link #ByteRTCLocalVideoStreamError}
 */
/**
 * @locale en
 * @type callback
 * @region Video management
 * @brief Receive this event when the state of the local video stream changes.
 * @param engine ByteRTCVideo object
 * @param streamIndex Stream property. See ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param state Current state of local video stream. See ByteRTCLocalVideoStreamState{@link #ByteRTCLocalVideoStreamState}
 * @param error Error code when local video state changes. See ByteRTCLocalVideoStreamError{@link #ByteRTCLocalVideoStreamError}
 */
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onLocalVideoStateChanged:(ByteRTCStreamIndex)streamIndex
             withStreamState:(ByteRTCLocalVideoStreamState)state
             withStreamError:(ByteRTCLocalVideoStreamError)error NS_SWIFT_NAME(rtcEngine(_:onLocalVideoStateChanged:withStreamState:withStreamError:));
/**
 * @locale zh
 * @type callback
 * @region 视频管理
 * @brief 远端视频流的状态发生改变时，房间内订阅此流的用户会收到该事件。
 * @param engine ByteRTCVideo 对象
 * @param streamKey 远端视频流信息，房间、用户 ID、流属性等，参看 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
 * @param state 远端视频流的当前状态，参看 ByteRTCRemoteVideoState{@link #ByteRTCRemoteVideoState}
 * @param reason 远端视频流状态改变的原因，参看 ByteRTCRemoteVideoStateChangeReason{@link #ByteRTCRemoteVideoStateChangeReason}
 * @note 本回调仅适用于主流，不适用于屏幕流。
 */
/**
 * @locale en
 * @type callback
 * @region Video management
 * @brief When the state of the remote video stream changes, users in the room who subscribe to this stream will receive the event.
 * @param engine ByteRTCVideo object
 * @param streamKey Remote video stream information, room, user ID, stream attributes, etc.. See ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
 * @param state The current state of the remote video stream. See ByteRTCRemoteVideoState{@link #ByteRTCRemoteVideoState}
 * @param reason The reason for the change in the state of the remote video stream. See ByteRTCRemoteVideoStateChangeReason{@link #ByteRTCRemoteVideoStateChangeReason}
 */
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onRemoteVideoStateChanged:(ByteRTCRemoteStreamKey*_Nonnull)streamKey
                withVideoState:(ByteRTCRemoteVideoState)state
                withVideoStateReason:(ByteRTCRemoteVideoStateChangeReason)reason NS_SWIFT_NAME(rtcEngine(_:onRemoteVideoStateChanged:withVideoState:withVideoStateReason:));
/**
 * @locale zh
 * @hidden(macOS)
 * @valid since 3.54
 * @type callback
 * @region 音视频处理
 * @brief 远端视频流的超分状态发生改变时，房间内订阅此流的用户会收到该回调。
 * @param streamKey 远端流信息，包括房间 ID、用户 ID、流属性，参看 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}。
 * @param mode 超分模式，参看 ByteRTCVideoSuperResolutionMode{@link #ByteRTCVideoSuperResolutionMode}。
 * @param reason 超分模式改变原因，参看 ByteRTCVideoSuperResolutionModeChangedReason{@link #ByteRTCVideoSuperResolutionModeChangedReason}。
 */
/**
 * @locale en
 * @hidden not available
 * @type callback
 * @region Audio & Video Processing
 * @brief When the super resolution mode of a remote video stream changes, users in the room who subscribe to this stream will receive this callback.
 * @param streamKey Remote stream information that includes the room ID, user ID, and stream type. See ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}.
 * @param mode Super resolution mode. See ByteRTCVideoSuperResolutionMode{@link #ByteRTCVideoSuperResolutionMode}.
 * @param reason Remote video stream super resolution mode change reason. See ByteRTCVideoSuperResolutionModeChangedReason{@link #ByteRTCVideoSuperResolutionModeChangedReason}
 */
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onRemoteVideoSuperResolutionModeChanged:(ByteRTCRemoteStreamKey*_Nonnull)streamKey
                    withMode:(ByteRTCVideoSuperResolutionMode)mode
                    withReason:(ByteRTCVideoSuperResolutionModeChangedReason)reason NS_SWIFT_NAME(rtcEngine(_:onRemoteVideoSuperResolutionModeChanged:withMode:withReason:));

/**
 * @locale zh
 * @valid since 3.54
 * @hidden(macOS)
 * @type callback
 * @region 音视频处理
 * @brief 降噪模式状态变更回调。当降噪模式的运行状态发生改变，SDK 会触发该回调，提示用户降噪模式改变后的运行状态及状态发生改变的原因。
 * @param mode 视频降噪模式，参看 ByteRTCVideoDenoiseMode{@link #ByteRTCVideoDenoiseMode}。
 * @param reason 视频降噪模式改变的原因，参看 ByteRTCVideoDenoiseModeChangedReason{@link #ByteRTCVideoDenoiseModeChangedReason}。
 */
/**
 * @locale en
 * @hidden not available
 * @type callback
 * @region Audio & Video Processing
 * @brief When the state of the video noise reduction mode changes, this callback will return the real state of the mode and the reasons for the changes.
 * @param mode Video noise reduction mode. Refer to ByteRTCVideoDenoiseMode{@link #ByteRTCVideoDenoiseMode} for more details.
 * @param reason Video noise reduction mode change reason. Refer to ByteRTCVideoDenoiseModeChangedReason{@link #ByteRTCVideoDenoiseModeChangedReason} for more<br>
 * details.
 */
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine
    onVideoDenoiseModeChanged:(ByteRTCVideoDenoiseMode)mode
                                 withReason:(ByteRTCVideoDenoiseModeChangedReason)reason NS_SWIFT_NAME(rtcEngine(_:onVideoDenoiseModeChanged:withReason:));

#pragma mark - Rtm
/**
 * @locale zh
 * @type callback
 * @region 实时消息通信
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
 * @note 调用 login:uid:{@link #ByteRTCVideo#login:uid:} 后，会收到此回调。
 */
/**
 * @locale en
 * @type callback
 * @region Real-time messaging
 * @brief Login result callback
 * @param engine ByteRTCVideo object
 * @param uid   <br>
 *        Login user ID
 * @param errorCode   <br>
 *        Login result <br>
 *        See ByteRTCLoginErrorCode{@link #ByteRTCLoginErrorCode}.
 * @param elapsed   <br>
 *        The time it takes from calling the login:uid:{@link #ByteRTCVideo#login:uid:} interface to return the result. <br>
 *         Is in ms.
 * @note Receive this callback after calling login:uid:{@link #ByteRTCVideo#login:uid:}.
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onLoginResult:(NSString * _Nonnull)uid errorCode:(ByteRTCLoginErrorCode)errorCode elapsed:(NSInteger)elapsed;
/**
 * @locale zh
 * @type callback
 * @region 实时消息通信
 * @brief 登出结果回调
 * @param engine ByteRTCVideo 对象
 * @param reason 用户登出的原因，参看 ByteRTCLogoutReason{@link #ByteRTCLogoutReason}
 * @note 在以下两种情况下会收到此回调：调用 logout{@link #ByteRTCVideo#logout} 接口主动退出；或其他用户以相同 UserId 进行 `login` 导致本地用户被动登出。
 */
/**
 * @locale en
 * @type callback
 * @region Real-time messaging
 * @brief Callback of the logout result 
 * @param engine ByteRTCVideo object
 * @param reason It describes the reason why users log out. See ByteRTCLogoutReason{@link #ByteRTCLogoutReason}
 * @note You will receive this callback when calling logout{@link #ByteRTCVideo#logout} or when the local user is kicked out because another user logs in with the same UserId.
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onLogout:(ByteRTCLogoutReason)reason;
/**
 * @locale zh
 * @type callback
 * @region 实时消息通信
 * @brief 设置应用服务器参数的返回结果
 * @param engine ByteRTCVideo 对象
 * @param errorCode <br>
 *        设置结果  <br>
 *        + 返回 200，设置成功  <br>
 *        + 返回其他，设置失败，详见 ByteRTCUserMessageSendResult{@link #ByteRTCUserMessageSendResult}
 * @note 调用 setServerParams:url:{@link #ByteRTCVideo#setServerParams:url:} 后，会收到此回调。
 */
/**
 * @locale en
 * @type callback
 * @region Real-time messaging
 * @brief Set the return result of the application server parameter
 * @param engine ByteRTCVideo object
 * @param errorCode  <br>
 *         + 200, set successfully <br>
 *         + != 200: Failure. Refer to ByteRTCUserMessageSendResult{@link #ByteRTCUserMessageSendResult} for details.
 * @note Receive this callback after calling setServerParams:url:{@link #ByteRTCVideo#setServerParams:url:}.
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onServerParamsSetResult:(NSInteger)errorCode;
/**
 * @locale zh
 * @type callback
 * @region 实时消息通信
 * @brief 查询对端或本端用户登录状态的返回结果
 * @param engine ByteRTCVideo 对象
 * @param peerUserId  <br>
 *        需要查询的用户 ID
 * @param status  <br>
 *        查询的用户登录状态  <br>
 *        详见 ByteRTCUserOnlineStatus{@link #ByteRTCUserOnlineStatus}.
 * @note 必须先调用 getPeerOnlineStatus:{@link #ByteRTCVideo#getPeerOnlineStatus:}，才能收到此回调。
 */
/**
 * @locale en
 * @type callback
 * @region Real-time messaging
 * @brief Returns the result of querying the login status of the peer or local user
 * @param engine ByteRTCVideo object
 * @param peerUserId   <br>
 *        User ID to query
 * @param status   <br>
 *        User login status of the query <br>
 *        See ByteRTCUserOnlineStatus{@link #ByteRTCUserOnlineStatus}.
 * @note You must first call getPeerOnlineStatus:{@link #ByteRTCVideo#getPeerOnlineStatus:} to receive this callback.
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onGetPeerOnlineStatus:(NSString * _Nonnull)peerUserId status:(ByteRTCUserOnlineStatus)status;
/**
 * @locale zh
 * @type callback
 * @region 实时消息通信
 * @brief 收到房间外用户调用 sendUserMessageOutsideRoom:message:config:{@link #ByteRTCVideo#sendUserMessageOutsideRoom:message:config:} 发来的文本消息时，会收到此回调
 * @param engine ByteRTCVideo 对象
 * @param uid  <br>
 *        消息发送者 ID
 * @param message  <br>
 *        收到的文本消息内容
 */
/**
 * @locale en
 * @type callback
 * @region Real-time messaging
 * @brief Receive this callback when you receive a text message from an out-of-room user calling sendUserMessageOutsideRoom:message:config:{@link #ByteRTCVideo#sendUserMessageOutsideRoom:message:config:}
 * @param engine ByteRTCVideo object
 * @param uid   <br>
 *        User ID of the message sender
 * @param message   <br>
 *        Received text message content
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onUserMessageReceivedOutsideRoom:(NSString * _Nonnull)uid message:(NSString * _Nonnull)message;
/**
 * @locale zh
 * @type callback
 * @region 实时消息通信
 * @brief 收到房间外用户调用 sendUserBinaryMessageOutsideRoom:message:config:{@link #ByteRTCVideo#sendUserBinaryMessageOutsideRoom:message:config:} 发来的二进制消息时，会收到此回调。
 * @param engine ByteRTCVideo 对象
 * @param  uid  <br>
 *         消息发送者 ID
 * @param  message  <br>
 *         收到的二进制消息内容
 */
/**
 * @locale en
 * @type callback
 * @region Real-time messaging
 * @brief Receive this callback when you receive a binary message from an out-of-room user call sendUserBinaryMessageOutsideRoom:message:config:{@link #ByteRTCVideo#sendUserBinaryMessageOutsideRoom:message:config:}.
 * @param engine ByteRTCVideo object
 * @param  uid   <br>
 *          User ID of the message sender
 * @param  message   <br>
 *          Binary message content received
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onUserBinaryMessageReceivedOutsideRoom:(NSString * _Nonnull)uid message:(NSData * _Nonnull)message;
/**
 * @locale zh
 * @type callback
 * @region 实时消息通信
 * @brief 给房间外指定的用户发送消息的回调
 * @param engine ByteRTCVideo 对象
 * @param msgid  <br>
 *        本条消息的 ID  <br>
 *        所有的 P2P 和 P2Server 消息共用一个 ID 序列。
 * @param error  <br>
 *        消息发送结果  <br>
 *        详见 ByteRTCUserMessageSendResult{@link #ByteRTCUserMessageSendResult}。
 * @note 当调用 sendUserMessageOutsideRoom:message:config:{@link #ByteRTCVideo#sendUserMessageOutsideRoom:message:config:} 或 sendUserBinaryMessageOutsideRoom:message:config:{@link #ByteRTCVideo#sendUserBinaryMessageOutsideRoom:message:config:} 发送消息后，会收到此回调。
 */
/**
 * @locale en
 * @type callback
 * @region Real-time messaging
 * @brief A callback that sends a message to a specified user outside the room
 * @param engine ByteRTCVideo object
 * @param msgid   <br>
 *        The ID of this message <br>
 *        All P2P and P2Server messages share a single ID sequence.
 * @param error   <br>
 *         Message sending result <br>
 *         See ByteRTCUserMessageSendResult{@link #ByteRTCUserMessageSendResult}.
 * @note Receive this callback when you send a message by calling sendUserMessageOutsideRoom:message:config:{@link #ByteRTCVideo#sendUserMessageOutsideRoom:message:config:} or sendUserBinaryMessageOutsideRoom:message:config:{@link #ByteRTCVideo#sendUserBinaryMessageOutsideRoom:message:config:}.
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onUserMessageSendResultOutsideRoom:(NSInteger)msgid error:(ByteRTCUserMessageSendResult)error;
/**
 * @locale zh
 * @type callback
 * @region 实时消息通信
 * @brief 给应用服务器发送消息的回调。
 * @param engine ByteRTCVideo 对象。
 * @param msgid 本条消息的 ID。<br>
 *              所有的 P2P 和 P2Server 消息共用一个 ID 序列。
 * @param error 消息发送结果。详见 ByteRTCUserMessageSendResult{@link #ByteRTCUserMessageSendResult}。
 * @param message 应用服务器收到 HTTP 请求后，在 ACK 中返回的信息。消息不超过 64 KB。
 * @note 本回调为异步回调。当调用 sendServerMessage:{@link #ByteRTCVideo#sendServerMessage:} 或 sendServerBinaryMessage:{@link #ByteRTCVideo#sendServerBinaryMessage:} 接口发送消息后，会收到此回调。
 */
/**
 * @locale en
 * @type callback
 * @region Real-time messaging
 * @brief Callback to send a message to the application server.
 * @param engine ByteRTCVideo object.
 * @param msgid The ID of this message. All P2P and P2Server messages share a single ID sequence.
 * @param error Message sending result, see ByteRTCUserMessageSendResult{@link #ByteRTCUserMessageSendResult}.
 * @param message The message returned in ACK when the application server receives HTTP request. The message should not exceed 64 KB.
 * @note This callback is asynchronous. Receive this callback when a message is sent by calling the sendServerMessage:{@link #ByteRTCVideo#sendServerMessage:} or sendServerBinaryMessage:{@link #ByteRTCVideo#sendServerBinaryMessage:} interface.
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onServerMessageSendResult:(int64_t)msgid error:(ByteRTCUserMessageSendResult)error message:(NSData * _Nonnull)message;
#pragma mark - Network Probe Methods
/**
 * @locale zh
 * @type callback
 * @region 通话前网络探测
 * @brief 通话前网络探测结果的回调。  <br>
 *        成功调用 startNetworkDetection:uplinkBandwidth:downlink:downlinkBandwidth:{@link #ByteRTCVideo#startNetworkDetection:uplinkBandwidth:downlink:downlinkBandwidth:} 接口开始探测后，会在 3s 内首次收到该回调，之后每 2s 收到一次该回调。
 * @param engine ByteRTCVideo 对象
 * @param type 探测网络类型为上行/下行  
 * @param quality 探测网络的质量，参看 ByteRTCNetworkQuality{@link #ByteRTCNetworkQuality}。 
 * @param rtt 探测网络的 RTT，单位：ms  
 * @param lostRate 探测网络的丢包率  
 * @param bitrate 探测网络的带宽，单位：kbps  
 * @param jitter 探测网络的抖动,单位：ms  
 */
/**
 * @locale en
 * @type callback
 * @region Pre-call network detection
 * @brief Callback of pre-call network detection result.  <br>
 *        After successfully calling startNetworkDetection:uplinkBandwidth:downlink:downlinkBandwidth:{@link #ByteRTCVideo#startNetworkDetection:uplinkBandwidth:downlink:downlinkBandwidth:}, you will receive this callback for the first time in 3s and every 2s thereafter.
 * @param engine ByteRTCVideo instance.
 * @param type Identifies the network type as uplink/downlink. 
 * @param quality Network quality, see ByteRTCNetworkQuality{@link #ByteRTCNetworkQuality}. 
 * @param rtt Network RTT in ms. 
 * @param lostRate Packet loss rate. 
 * @param bitrate Network bandwidth in kbps. 
 * @param jitter Network jitter in ms 
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onNetworkDetectionResult:(ByteRTCNetworkDetectionLinkType)type quality:(ByteRTCNetworkQuality)quality rtt:(int)rtt lostRate:(double)lostRate bitrate:(int)bitrate jitter:(int)jitter;
/**
 * @locale zh
 * @type callback
 * @region 通话前网络探测
 * @brief 通话前网络探测结束  <br>
 *        以下情况将停止探测并收到一次本回调：<br>
 *        1. 当调用 stopNetworkDetection{@link #ByteRTCVideo#stopNetworkDetection} 接口停止探测后，会收到一次该回调；<br>
 *        2. 当收到远端/本端音频首帧后，停止探测；<br>
 *        3. 当探测超过3分钟后，停止探测；<br>
 *        4. 当探测链路断开一定时间之后，停止探测。
 * @param engine ByteRTCVideo 对象
 * @param errorCode  <br>
 *        停止探测的原因类型,参考 ByteRTCNetworkDetectionStopReason{@link #ByteRTCNetworkDetectionStopReason}  
 */
/**
 * @locale en
 * @type callback
 * @region Pre-call network probing
 * @brief Pre-call network probing ends <br>
 *        The following will stop detection and receive this primary callback:  <br>
 *        1. This callback is received once when the stopNetworkDetection{@link #ByteRTCVideo#stopNetworkDetection} interface is called to stop probing;  <br>
 *        2. Stop detection when the first frame of remote/local audio is received;  <br>
 *        3. Stop detecting when the detection exceeds 3 minutes;  <br>
 *        4. When the probe link is disconnected for a certain period of time, the probe is stopped.
 * @param engine ByteRTCVideo object
 * @param errorCode   <br>
 *        See ByteRTCNetworkDetectionStopReason{@link #ByteRTCNetworkDetectionStopReason} for reasons of stopping probing.
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onNetworkDetectionStopped:(ByteRTCNetworkDetectionStopReason)errorCode;
#pragma mark - Log Delegate Methods
// @name log related callbacks
/**
 * @locale zh
 * @deprecated since 3.45 and will be deleted in 3.51.
 * @type callback
 * @region 引擎管理
 * @brief SDK 内部日志回调。  <br>
 *        SDK 内部运行时，会把日志回调给业务方，方便排查问题。
 * @param engine ByteRTCVideo 对象。
 * @param dict 日志内容。
 */
/**
 * @locale en
 * @deprecated since 3.45 and will be deleted in 3.51.
 * @type callback
 * @region Engine management
 * @brief SDK Internal log callbacks. <br>
 *        SDK internal runtime will call back the log to the business side to facilitate troubleshooting.
 * @param engine ByteRTCVideo object.
 * @param dict Log content.
 */
- (void)rtcEngine:(ByteRTCVideo* _Nonnull)engine log:(NSDictionary* _Nonnull)dict;
#pragma mark Audio Mix Delegate Methods
// @name audio mix callback
/**
 * @locale zh
 * @deprecated since 353. Use ByteRTCAudioEffectPlayerEventHandler{@link #ByteRTCAudioEffectPlayerEventHandler} and ByteRTCMediaPlayerEventHandler{@link #ByteRTCMediaPlayerEventHandler} instead.
 * @type callback
 * @region 混音
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
 * @note  
 *       此回调会被触发的时机汇总如下：  <br>
 *       + 当调用 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} 方法成功后，会触发 state 值为 ByteRTCAudioMixingStatePlaying 回调；否则触发 state 值为 ByteRTCAudioMixingStateFailed 的回调。  <br>
 *       + 当使用相同的 ID 重复调用 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} 后，后一次会覆盖前一次，且本回调会以 ByteRTCAudioMixingStateStopped 通知前一次混音已停止。  <br>
 *       + 当调用 pauseAudioMixing:{@link #ByteRTCAudioMixingManager#pauseAudioMixing:} 方法暂停播放成功后，会触发 state 值为 ByteRTCAudioMixingStatePaused 回调；否则触发 state 值为 ByteRTCAudioMixingStateFailed 的回调。  <br>
 *       + 当调用 resumeAudioMixing:{@link #ByteRTCAudioMixingManager#resumeAudioMixing:} 方法恢复播放成功后，会触发 state 值为 ByteRTCAudioMixingStatePlaying 回调；否则触发 state 值为 ByteRTCAudioMixingStateFailed 的回调。  <br>
 *       + 当调用 stopAudioMixing:{@link #ByteRTCAudioMixingManager#stopAudioMixing:} 方法停止播放成功后，会触发 state 值为 ByteRTCAudioMixingStateStopped 回调；否则触发 state 值为 ByteRTCAudioMixingStateFailed 的回调。  <br>
 *       + 播放结束会触发 state 值为 ByteRTCAudioMixingStateFinished 回调。
 */
/**
 * @locale en
 * @deprecated since 353. Use ByteRTCAudioEffectPlayerEventHandler{@link #ByteRTCAudioEffectPlayerEventHandler} and ByteRTCMediaPlayerEventHandler{@link #ByteRTCMediaPlayerEventHandler} instead.
 * @type callback
 * @region Audio Mixing
 * @brief Callback when audio mix file playback state changes
 * @param engine Current RTC SDK engine object
 * @param mixId   <br>
 *        Mix ID <br>
 *        Unique ID passed in when using ByteRTCAudioMixingManager{@link #ByteRTCAudioMixingManager} related interface.
 * @param state   <br>
 *        Mix status <br>
 *        The mix status can be referred to: ByteRTCAudioMixingState{@link #ByteRTCAudioMixingState}.
 * @param error   <br>
 *         Error code <br>
 *         See ByteRTCAudioMixingError{@link #ByteRTCAudioMixingError}.
 * @note   
 *        The timing of this callback will be triggered is summarized as follows: <br>
 *        + When startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} method is successfully called, the callback with the state value ByteRTCAudioMixingStatePlaying will be triggered; otherwise, the callback with the state value ByteRTCAudioMixingStateFailed will be triggered. <br>
 *        + When startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} is repeatedly called with the same ID, the latter overrides the previous one, and this callback notifies the previous mix has stopped with ByteRTCAudioMixingStateStopped. <br>
 *        + When the pauseAudioMixing:{@link #ByteRTCAudioMixingManager#pauseAudioMixing:} method pauses playback successfully, a callback with the state value ByteRTCAudioMixingStatePaused will be triggered; otherwise, a callback with the state value ByteRTCAudioMixingStateFailed will be triggered. <br>
 *        + When calling the resumeAudioMixing:{@link #ByteRTCAudioMixingManager#resumeAudioMixing:} method to resume playback successfully, a callback with the state value ByteRTCAudioMixingStatePlaying will be triggered; otherwise, a callback with the state value ByteRTCAudioMixingStateFailed will be triggered. <br>
 *        + When the stopAudioMixing:{@link #ByteRTCAudioMixingManager#stopAudioMixing:} method stops playing successfully, a callback with the state value ByteRTCAudioMixingStateStopped will be triggered; otherwise, a callback with the state value ByteRTCAudioMixingStateFailed will be triggered. <br>
 *        + The end of playback triggers a callback with the state value ByteRTCAudioMixingStateFinished.
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onAudioMixingStateChanged:(NSInteger)mixId state:(ByteRTCAudioMixingState)state error:(ByteRTCAudioMixingError)error;
/**
 * @locale zh
 * @type callback
 * @region 混音
 * @brief 混音音频文件播放进度回调
 * @param engine 当前 RTC SDK 对象
 * @param mixId 混音 ID  
 * @param progress 当前混音音频文件播放进度，单位毫秒
 * @note 调用 setAudioMixingProgressInterval:interval:{@link #ByteRTCAudioMixingManager#setAudioMixingProgressInterval:interval:} 将时间间隔设为大于 0 的值后，或调用 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} 将 ByteRTCAudioMixingConfig{@link #ByteRTCAudioMixingConfig} 中的时间间隔设为大于 0 的值后，SDK 会按照设置的时间间隔回调该事件。 
 */
/**
 * @locale en
 * @type callback
 * @region Audio Mixing
 * @brief Callback for playback progress of mixed audio files
 * @param engine Current RTC SDK object
 * @param mixId ID of the mixing task
 * @param progress The current playback progress (ms) of the mixed audio file
 * @note After calling setAudioMixingProgressInterval:interval:{@link #ByteRTCAudioMixingManager#setAudioMixingProgressInterval:interval:} to set the time interval to a value greater than 0, or calling startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} to set the time interval in ByteRTCAudioMixingConfig{@link #ByteRTCAudioMixingConfig} to a value greater than 0, the SDK will trigger the callback according to the set time interval.
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onAudioMixingPlayingProgress:(NSInteger)mixId progress:(int64_t) progress;
#pragma mark Performance Delegate Methods
// @name performance related callbacks
/**
 * @locale zh
 * @type callback
 * @region 音视频回退
 * @brief 本地未通过 setPublishFallbackOption:{@link #ByteRTCVideo#setPublishFallbackOption:} 开启发布性能回退，检测到设备性能不足时，收到此回调。  <br>
 *        本地通过 setPublishFallbackOption:{@link #ByteRTCVideo#setPublishFallbackOption:} 开启发布性能回退，因设备性能/网络原因，造成发布性能回退/恢复时，收到此回调。  
 * @param mode 指示本地是否开启发布回退功能。参看 ByteRTCPerformanceAlarmMode{@link #ByteRTCPerformanceAlarmMode}  <br>
 *             + 当发布端未开启发布性能回退时，mode 值为 ByteRTCPerformanceAlarmModeNormal。  <br>
 *             + 当发布端开启发布性能回退时，mode 值为 ByteRTCPerformanceAlarmModeSimulcast。
 * @param roomId  <br>
 *                + 未开启发布性能回退时，roomId 为空  <br>
 *                + 开启发布性能回退时，roomId 是告警影响的房间 ID。
 * @param reason 告警原因，参看 ByteRTCPerformanceAlarmReason{@link #ByteRTCPerformanceAlarmReason}
 * @param data 性能回退相关数据，详见 ByteRTCSourceWantedData{@link #ByteRTCSourceWantedData}。
 */
/**
 * @locale en
 * @type callback
 * @region  audio & video fallback
 * @brief When the publish performance fallback setPublishFallbackOption:{@link #ByteRTCVideo#setPublishFallbackOption:} is not turned on locally, and when insufficient device performance is detected, this callback is received.   <br>
 *        When the setPublishFallbackOption:{@link #ByteRTCVideo#setPublishFallbackOption:} is locally turned on, and when the publish performance fallback/recovery is caused due to device performance/network reasons, this callback is received. 
 * @param mode  Indicates whether the release fallback function is turned on locally. See ByteRTCPerformanceAlarmMode{@link #ByteRTCPerformanceAlarmMode} <br>
 *              + When the publisher does not turn on the release performance fallback, the mode value is ByteRTCPerformanceAlarmModeNormal. <br>
 *              + When the publisher turns on the release performance fallback, the mode value is ByteRTCPerformanceAlarmModeSimulcast.
 * @param roomId   <br>
 *                 + When the release performance fallback is not turned on, the roomId is empty <br>
 *                 + When the release performance fallback is turned on, the roomId is the room ID affected by the alarm.
 * @param reason For alarm reasons. See ByteRTCPerformanceAlarmReason{@link #ByteRTCPerformanceAlarmReason}
 * @param data Performance fallback related data. See ByteRTCSourceWantedData{@link #ByteRTCSourceWantedData}.
 */
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onPerformanceAlarms:(ByteRTCPerformanceAlarmMode)mode
                         roomId:(NSString *_Nonnull)roomId
                         reason:(ByteRTCPerformanceAlarmReason)reason
               sourceWantedData:(ByteRTCSourceWantedData *_Nonnull)data;
/**
 * @locale zh
 * @type callback
 * @region 音视频回退
 * @brief 音视频流因网络环境变化等原因发生回退，或从回退中恢复时，触发该回调。
 * @param engine 当前 ByteRTCVideo 实例
 * @param event 流切换信息。详见 ByteRTCRemoteStreamSwitchEvent{@link #ByteRTCRemoteStreamSwitchEvent}。
 */
/**
 * @locale en
 * @type callback
 * @region audio & video rollback
 * @brief Once the fallback option is set, fallback or reverting from a Fallback of a media stream will trigger this callback.
 * @param engine Current ByteRTCVideo instance
 * @param event Information of stream switching. Refer to ByteRTCRemoteStreamSwitchEvent{@link #ByteRTCRemoteStreamSwitchEvent} for more details.
 */
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onSimulcastSubscribeFallback:(ByteRTCRemoteStreamSwitchEvent *_Nonnull)event;

#if BYTERTC_TARGET_MAC
/**
 * @locale zh
 * @hidden(iOS)
 * @type callback
 * @brief 外部采集时，调用 setOriginalScreenVideoInfo:withOriginalCaptureHeight:{@link #ByteRTCVideo#setOriginalScreenVideoInfo:withOriginalCaptureHeight:} 设置屏幕或窗口大小改变前的分辨率后，若屏幕采集模式为智能模式，你将收到此回调，根据 RTC 智能决策合适的帧率和分辨率积（宽*高）重新采集。
 * @param frameUpdateInfo RTC 智能决策后合适的帧率和分辨率积（宽*高）。参看 ByteRTCFrameUpdateInfo{@link #ByteRTCFrameUpdateInfo}。
 */
/**
 * @locale en
 * @hidden(iOS)
 * @type callback
 * @brief After calling setOriginalScreenVideoInfo:withOriginalCaptureHeight:{@link #ByteRTCVideo#setOriginalScreenVideoInfo:withOriginalCaptureHeight:} to set the original width and height of the external shared-screen stream and setting the encoding mode to the automatic mode, you will receive this callback to re-capture the stream based on the recommended pixel and framerate by RTC.
 * @param frameUpdateInfo The recommended pixel and framerate by RTC. See ByteRTCFrameUpdateInfo{@link #ByteRTCFrameUpdateInfo}.
 */
- (void)rtcEngine: (ByteRTCVideo* _Nonnull)engine onExternalScreenFrameUpdate: (ByteRTCFrameUpdateInfo* _Nullable)frameUpdateInfo;
#endif
#pragma mark Proxy Delegate Methods
// @name Socks5 and HTTP proxy callbacks
/**
 * @locale zh
 * @type callback
 * @deprecated 在3.52及之后废弃，将在3.57删除，使用 rtcEngine:onLocalProxyStateChanged:withProxyState:withProxyError:{@link #ByteRTCVideoDelegate#rtcEngine:onLocalProxyStateChanged:withProxyState:withProxyError:} 替换
 * @region 网络代理
 * @brief HTTP 代理连接状态改变时，收到该回调。
 * @param engine ByteRTCVideo 对象
 * @param state 当前 HTTP 代理连接状态
 */
/**
 * @locale en
 * @type callback
 * @deprecated since 3.52, will be deleted at 3.57, use rtcEngine:onLocalProxyStateChanged:withProxyState:withProxyError:{@link #ByteRTCVideoDelegate#rtcEngine:onLocalProxyStateChanged:withProxyState:withProxyError:} instead
 * @region Network proxy
 * @brief This callback is triggered when the HTTP proxy connection status changes.
 * @param engine ByteRTCVideo object
 * @param state Current HTTP proxy connection status
 */
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onHttpProxyState:(NSInteger)state;
/**
 * @locale zh
 * @type callback
 * @deprecated 在3.52及之后废弃，将在3.57删除，使用 rtcEngine:onLocalProxyStateChanged:withProxyState:withProxyError:{@link #ByteRTCVideoDelegate#rtcEngine:onLocalProxyStateChanged:withProxyState:withProxyError:} 替换
 * @region 网络代理
 * @brief HTTPS 代理连接状态改变时，收到该回调。
 * @param engine ByteRTCVideo 对象
 * @param state 当前 HTTPS 代理连接状态
 */
/**
 * @locale en
 * @type callback
 * @deprecated since 3.52, will be deleted at 3.57, use rtcEngine:onLocalProxyStateChanged:withProxyState:withProxyError:{@link #ByteRTCVideoDelegate#rtcEngine:onLocalProxyStateChanged:withProxyState:withProxyError:} instead
 * @region Network proxy
 * @brief This callback is triggered when the HTTPS proxy connection status changes.
 * @param engine ByteRTCVideo object
 * @param state Current HTTPS proxy connection status
 */
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onHttpsProxyState:(NSInteger)state;
/**
 * @locale zh
 * @type callback
 * @deprecated 在3.52及之后废弃，将在3.57删除，使用 rtcEngine:onLocalProxyStateChanged:withProxyState:withProxyError:{@link #ByteRTCVideoDelegate#rtcEngine:onLocalProxyStateChanged:withProxyState:withProxyError:} 替换
 * @region 网络代理
 * @brief SOCKS5 代理状态改变时，收到该回调。
 * @param engine ByteRTCVideo 对象
 * @param state SOCKS5 代理连接状态
 * @param cmd 代理连接的每一步操作命令
 * @param proxyAddress 代理地址信息
 * @param localAddress 当前连接使用的本地地址
 * @param remoteAddress 远端的连接地址
 */
/**
 * @locale en
 * @type callback
 * @deprecated since 3.52, will be deleted at 3.57, use rtcEngine:onLocalProxyStateChanged:withProxyState:withProxyError:{@link #ByteRTCVideoDelegate#rtcEngine:onLocalProxyStateChanged:withProxyState:withProxyError:} instead
 * @region Network proxy
 * @brief This callback is triggered when the Socks proxy connection status changes.
 * @param engine ByteRTCVideo object
 * @param state SOCKS5 proxy connection status
 * @param cmd Every step of the proxy connection operating command
 * @param proxyAddress Proxy address information
 * @param localAddress Local address used by the current connection
 * @param remoteAddress Remote connection address
 */
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onSocks5ProxyState:(NSInteger)state
                   cmd:(NSString *_Nonnull)cmd
         proxy_address:(NSString *_Nonnull)proxyAddress
         local_address:(NSString *_Nonnull)localAddress
        remote_address:(NSString *_Nonnull)remoteAddress;
#pragma mark FileRecording related callback
/**
 * @locale zh
 * @type callback
 * @region 本地录制
 * @brief 获取本地录制状态回调。  <br>
 *        该回调由 startFileRecording:withRecordingConfig:type:{@link #ByteRTCVideo#startFileRecording:withRecordingConfig:type:} 或 stopFileRecording:{@link #ByteRTCVideo#stopFileRecording:} 触发。
 * @param engine ByteRTCVideo 对象
 * @param type 录制流的流属性，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param state 录制状态，参看 ByteRTCRecordingState{@link #ByteRTCRecordingState}
 * @param errorCode 录制错误码，参看 ByteRTCRecordingErrorCode{@link #ByteRTCRecordingErrorCode}
 * @param recordingInfo 录制文件的详细信息，参看 ByteRTCRecordingInfo{@link #ByteRTCRecordingInfo}
 */
/**
 * @locale en
 * @type callback
 * @region  local recording
 * @brief  Get local recording status callback.   <br>
 *         The callback is triggered by either startFileRecording:withRecordingConfig:type:{@link #ByteRTCVideo#startFileRecording:withRecordingConfig:type:} or stopFileRecording:{@link #ByteRTCVideo#stopFileRecording:}.
 * @param engine ByteRTCVideo object
 * @param type Stream properties of the recorded stream. See ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param state Recording status. See ByteRTCRecordingState{@link #ByteRTCRecordingState}
 * @param errorCode Recording error code. See ByteRTCRecordingErrorCode{@link #ByteRTCRecordingErrorCode}
 * @param recordingInfo Recording file details. See ByteRTCRecordingInfo{@link #ByteRTCRecordingInfo}
 */
- (void)rtcEngine:(ByteRTCVideo* _Nonnull)engine onRecordingStateUpdate:(ByteRTCStreamIndex)type
                         state:(ByteRTCRecordingState)state
                    error_code:(ByteRTCRecordingErrorCode)errorCode
                recording_info:(ByteRTCRecordingInfo* _Nonnull)recordingInfo;
/**
 * @locale zh
 * @type callback
 * @region 本地录制
 * @brief 本地录制进度回调。  <br>
 *        该回调由 startFileRecording:withRecordingConfig:type:{@link #ByteRTCVideo#startFileRecording:withRecordingConfig:type:} 触发，录制状态正常时，系统每秒钟都会通过该回调提示录制进度。
 * @param engine ByteRTCVideo 对象
 * @param type 录制流的流属性，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param process 录制进度，参看 ByteRTCRecordingProgress{@link #ByteRTCRecordingProgress}
 * @param recordingInfo 录制文件的详细信息，参看 ByteRTCRecordingInfo{@link #ByteRTCRecordingInfo}
 */
/**
 * @locale en
 * @type callback
 * @region  local recording
 * @brief  Local recording progress callback.   <br>
 *        This callback is triggered by startFileRecording:withRecordingConfig:type:{@link #ByteRTCVideo#startFileRecording:withRecordingConfig:type:}. When the recording state is normal, the system will prompt the recording progress through this callback every second.
 * @param engine ByteRTCVideo object
 * @param type Stream properties of the recorded stream. See ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param process Recording progress. See ByteRTCRecordingProgress{@link #ByteRTCRecordingProgress}
 * @param recordingInfo Details of the recorded file. See ByteRTCRecordingInfo{@link #ByteRTCRecordingInfo}
 */
- (void)rtcEngine:(ByteRTCVideo* _Nonnull)engine onRecordingProgressUpdate:(ByteRTCStreamIndex)type
                          process:(ByteRTCRecordingProgress* _Nonnull)process
                   recording_info:(ByteRTCRecordingInfo* _Nonnull)recordingInfo;
/**
* @locale zh
*  @type callback
*  @brief 调用 startAudioRecording:{@link #ByteRTCVideo#startAudioRecording:} 或者 stopAudioRecording{@link #ByteRTCVideo#stopAudioRecording} 改变音频文件录制状态时，收到此回调。
*  @param state 录制状态，参看 ByteRTCAudioRecordingState{@link #ByteRTCAudioRecordingState}
*  @param errorCode 录制错误码，参看 ByteRTCAudioRecordingErrorCode{@link #ByteRTCAudioRecordingErrorCode}
*/
/**
* @locale en
*  @type callback
*  @brief When calling startAudioRecording:{@link #ByteRTCVideo#startAudioRecording:} or stopAudioRecording{@link #ByteRTCVideo#stopAudioRecording} to change the recording status, receive the callback.
*  @param state See ByteRTCAudioRecordingState{@link #ByteRTCAudioRecordingState}.
*  @param errorCode See ByteRTCAudioRecordingErrorCode{@link #ByteRTCAudioRecordingErrorCode}.
*/
- (void)rtcEngine:(ByteRTCVideo* _Nonnull)engine
        onAudioRecordingStateUpdate:(ByteRTCAudioRecordingState)state
                         error_code:(ByteRTCAudioRecordingErrorCode)errorCode;

/**
 * @locale zh
 * @type callback
 * @brief 公共流发布结果回调。<br>
 *        调用 startPushPublicStream:withLayout:{@link #ByteRTCVideo#startPushPublicStream:withLayout:} <br>
 *        接口或直接在服务端启动推公共流功能后，你会通过此回调收到启动结果和推流过程中的错误。
 * @param engine engine 实例
 * @param roomId 发布公共流的房间 ID
 * @param streamId 公共流ID。
 * @param errorCode 公共流发布结果状态码。 详见 ByteRTCPublicStreamErrorCode{@link #ByteRTCPublicStreamErrorCode}。
 */
/**
 * @locale en
 * @hidden currently not available
 * @type callback
 * @brief Callback of the result of publishing the public stream<br>
 *        You will be informed of the result of publishing the public stream by this callback after calling startPushPublicStream:withLayout:{@link #ByteRTCVideo#startPushPublicStream:withLayout:}.
 * @param engine engine instance
 * @param roomId Room ID from which the public stream is published
 * @param streamId ID of the public stream
 * @param errorCode Result and status code of publishing the public stream. Refer to ByteRTCPublicStreamErrorCode{@link #ByteRTCPublicStreamErrorCode} for details.
 */
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onPushPublicStreamResult:(NSString *_Nonnull)roomId
        publicStreamId:(NSString *_Nonnull)streamId
        errorCode:(ByteRTCPublicStreamErrorCode)errorCode;

/**
 * @locale zh
 * @type callback
 * @brief 订阅公共流的结果回调  <br>
 *        调用 startPlayPublicStream:{@link #ByteRTCVideo#startPlayPublicStream:} 接口拉公共流后，你会通过此回调收到启动结果和拉流过程中的错误。
 * @param engine engine 实例
 * @param publicStreamId 公共流ID。
 * @param errorCode 公共流订阅结果状态码。 详见 ByteRTCPublicStreamErrorCode{@link #ByteRTCPublicStreamErrorCode}。
 */
/**
 * @locale en
 * @hidden currently not available
 * @type callback
 * @brief Callback of the result of subscribing to the public stream<br>
 *        You will be informed of the result of subscribing to the public stream by this callback after calling startPushPublicStream:withLayout:{@link #ByteRTCVideo#startPushPublicStream:withLayout:}.
 * @param engine engine instance
 * @param publicStreamId ID of the public stream
 * @param errorCode Result and status code of subscribing to the public stream. Refer to ByteRTCPublicStreamErrorCode{@link #ByteRTCPublicStreamErrorCode} for details.
 */
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onPlayPublicStreamResult:(NSString *_Nonnull)publicStreamId
        errorCode:(ByteRTCPublicStreamErrorCode)errorCode;
/**
 * @locale zh
 * @type callback
 * @brief 回调公共流中包含的 SEI 信息。<br>
 *        调用 startPlayPublicStream:{@link #ByteRTCVideo#startPlayPublicStream:} 接口启动拉公共流功能后，通过此回调收到公共流中的 SEI 消息。
 * @param engine ByteRTCVideo 实例。
 * @param publicStreamId 公共流 ID。
 * @param message 收到的 SEI 消息内容。<br>
 * 本回调可以获取通过调用客户端 `sendSEIMessage:andMessage:andRepeatCount:andCountPerFrame:` 插入的 SEI 信息。<br>
 * 当公共流中的多路视频流均包含有 SEI 信息：SEI 不互相冲突时，将通过多次回调分别发送；SEI 在同一帧有冲突时，则只有一条流中的 SEI 信息被透传并融合到公共流中。
 * @param sourceType SEI 消息类型，自 3.52.1 版本后固定为 `0`，自定义消息。参看 ByteRTCDataMessageSourceType{@link #ByteRTCDataMessageSourceType}。
 * @note  
 * 通过 Open API 插入的自定义信息，应通过回调 rtcEngine:onPublicStreamDataMessageReceived:andMessage:andSourceType:{@link #ByteRTCVideoDelegate#rtcEngine:onPublicStreamDataMessageReceived:andMessage:andSourceType:} 获取。
 */
/**
 * @locale en
 * @hidden currently not available
 * @type callback
 * @brief Callback on receiving the SEI message carried by the public video stream.<br>
 *        After calling startPlayPublicStream:{@link #ByteRTCVideo#startPlayPublicStream:}, you will receive this callback if the public stream has an SEI message.
 * @param engine The ByteRTCVideo instance.
 * @param publicStreamId The ID of the public stream.
 * @param message The SEI(supplemental enhancement information) message carried by the public video stream.<br>
 * The SEI you can get via this callback is inserted by calling `sendSEIMessage:andMessage:andRepeatCount:andCountPerFrame:` in the SDK.<br>
 * You receive SEI from all the video streams if the SEI messages do not have conflicts. However, if the SEI messages from different video streams have conflicts, you will receive only one of them.
 * @param sourceType SEI source type.  Since V3.52.1, the value is always `0`, for custom messages. Refer to ByteRTCDataMessageSourceType{@link #ByteRTCDataMessageSourceType}. 
 * @note 
 * You also need to listen to rtcEngine:onPublicStreamDataMessageReceived:andMessage:andSourceType:{@link #ByteRTCVideoDelegate#rtcEngine:onPublicStreamDataMessageReceived:andMessage:andSourceType:} to receive data messages inserted via Open API in the server.
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onPublicStreamSEIMessageReceived:(NSString* _Nonnull)publicStreamId andMessage:(NSData* _Nonnull)message andSourceType:(ByteRTCDataMessageSourceType)sourceType;
/**
  * @locale zh
  * @type callback
  * @valid since 3.52
  * @brief 回调公共流中包含的数据信息。<br>
  *        通过 startPlayPublicStream:{@link #ByteRTCVideo#startPlayPublicStream:} 开始播放公共流后，可以通过本回调获取公共流中的数据消息，包括调用 Open API 发送的 SEI 消息和音量回调。
  * @param engine ByteRTCVideo 实例。
  * @param publicStreamId 公共流 ID
  * @param message 收到的数据消息内容，如下：<br>
  * + 调用公共流 OpenAPI 发送的自定义消息。<br>
  * + 媒体流音量变化，需要通过公共流 OpenAPI 开启回调。JSON 格式说明如下：<br>
  * {<br>
  * &nbsp;&nbsp;&nbsp;&nbsp;"Type"&nbsp;:&nbsp;"VolumeIndication", //具体业务类型<br>
  * &nbsp;&nbsp;&nbsp;&nbsp;"VolumeInfos"[&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;// 业务类型对应信息<br>
  * &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;{<br>
  * &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"RoomId":"1000001", // 房间ID<br>
  * &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"UserId":"1000001", // 用户ID<br>
  * &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"StreamType":0, // 0:摄像头流；1:屏幕流<br>
  * &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"LinearVolume":1 // 线性音量大小<br>
  * &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;}<br>
  * &nbsp;&nbsp;&nbsp;&nbsp;]<br>
  * }
  * @param sourceType 数据消息来源，参看 ByteRTCDataMessageSourceType{@link #ByteRTCDataMessageSourceType}。通过调用客户端 API 插入的 SEI 信息，应通过回调 rtcEngine:onPublicStreamSEIMessageReceived:andMessage:andSourceType:{@link #ByteRTCVideoDelegate#rtcEngine:onPublicStreamSEIMessageReceived:andMessage:andSourceType:} 获取。
  */
/**
  * @locale en
  * @hidden currently not available
  * @type callback
  * @brief Callback on receiving the data message carried by the public video stream.<br>
  * After calling startPlayPublicStream:{@link #ByteRTCVideo#startPlayPublicStream:}, you can listen to this callback and retrieve SEI messages inserted by Open API calls or audio volume.
  * @param engine The ByteRTCVideo instance.
  * @param publicStreamId ID of the public stream
  * @param message The data messages carried by the public video stream.<br>
  * + Data inserted by calling the OpenAPI.<br>
  * + Media volume in JSON, before you can receive which you need to enable it via calling the OpenAPI. Refer to the definition below to parse the JSON string.<br>
  * {<br>
  * &nbsp;&nbsp;&nbsp;&nbsp;"Type"&nbsp;:&nbsp;"VolumeIndication",<br>
  * &nbsp;&nbsp;&nbsp;&nbsp;"VolumeInfos":[<br>
  * &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;{<br>
  * &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"RoomId":"1000001",<br>
  * &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"UserId":"1000001",<br>
  * &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"StreamType":0,&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;//  `0` for main stream and `1` for the screen sharing stream<br>
  * &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"LinearVolume":1<br>
  * &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;}<br>
  * &nbsp;&nbsp;&nbsp;&nbsp;]<br>
  * }
  * @param sourceType Message source. Refer to ByteRTCDataMessageSourceType{@link #ByteRTCDataMessageSourceType}.
  * @note You also need to listen to rtcEngine:onPublicStreamSEIMessageReceived:andMessage:andSourceType:{@link #ByteRTCVideoDelegate#rtcEngine:onPublicStreamSEIMessageReceived:andMessage:andSourceType:} to receive SEI inserted via API in the client SDK.
  */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onPublicStreamDataMessageReceived:(NSString* _Nonnull)publicStreamId andMessage:(NSData* _Nonnull)message andSourceType:(ByteRTCDataMessageSourceType)sourceType;

    /**
     * @locale zh
     * @valid since 3.56
     * @hidden for internal use only
     * @type callback
     * @brief 回调公共流中包含的 SEI 信息。<br>
     *        调用 startPlayPublicStream:{@link #ByteRTCVideo#startPlayPublicStream:} 接口启动拉公共流功能后，通过此回调收到公共流中的 SEI 消息。
     * @param publicStreamId 公共流 ID。
     * @param channelId SEI 消息通道 ID，取值范围 [0 - 255]。通过此参数，你可以为不同接受方设置不同的 ChannelID，这样不同接收方可以根据回调中的 ChannelID 选择应关注的 SEI 信息。
     * @param message 收到的 SEI 消息内容。<br>
     * 通过调用客户端 `sendPublicStreamSEIMessage` 插入的 SEI 信息。
     */
    /**
     * @locale en
     * @valid since 3.56
     * @hidden for internal use only
     * @type callback
     * @brief Callback on receiving the SEI message carried by the public video stream.<br>
     *        After calling startPlayPublicStream:{@link #ByteRTCVideo#startPlayPublicStream:}, you will receive this callback if the public stream has an SEI message.
     * @param publicStreamId The ID of the public stream.
     * @param channelId SEI message channel ID. The value range is [0 - 255]. With this parameter, you can set different ChannelIDs for different recipients. In this way, different recipients can choose the SEI information  based on the ChannelID received in the callback.
     * @param message The SEI(supplemental enhancement information) message carried by the public video stream.<br>
     * The SEI you can get via this callback is inserted by calling `sendPublicStreamSEIMessage` in the SDK.
     */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onPublicStreamSEIMessageReceivedWithChannel:(NSString* _Nonnull)publicStreamId andChannelId:(int)channelId andMessage:(NSData* _Nonnull)message;
/**
 * @locale zh
 * @type callback
 * @brief 公共流的首帧视频解码成功<br>
 *        关于订阅公共流，详见 startPlayPublicStream:{@link #ByteRTCVideo#startPlayPublicStream:}。
 * @param engine ByteRTCVideo 对象
 * @param publicStreamId 公共流 ID
 * @param frameInfo 视频帧信息，参看 ByteRTCVideoFrameInfo{@link #ByteRTCVideoFrameInfo}
 */
/**
 * @locale en
 * @hidden currently not available
 * @type callback
 * @brief Callback of successfully decoding of the first video frame of the public stream<br>
 *        Refer to startPlayPublicStream:{@link #ByteRTCVideo#startPlayPublicStream:} for details about subscribing to a public stream.
 * @param engine ByteRTCVideo instance
 * @param publicStreamId ID of the public stream
 * @param frameInfo Information of the video stream. Refer to ByteRTCVideoFrameInfo{@link #ByteRTCVideoFrameInfo} for more details.
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onFirstPublicStreamVideoFrameDecoded:(NSString * _Nonnull)publicStreamId withFrameInfo:(ByteRTCVideoFrameInfo * _Nonnull)frameInfo NS_SWIFT_NAME(rtcEngine(_:onFirstPublicStreamVideoFrameDecoded:withFrameInfo:));
/**
 * @locale zh
 * @type callback
 * @brief 公共流的音频首帧解码成功<br>
 *        关于订阅公共流，详见 startPlayPublicStream:{@link #ByteRTCVideo#startPlayPublicStream:}。
 * @param engine ByteRTCVideo 对象
 * @param publicStreamId 公共流 ID
 */
/**
 * @locale en
 * @hidden currently not available
 * @type callback
 * @brief Callback of successfully decoding of the first audio frame of the public stream<br>
 *        Refer to startPlayPublicStream:{@link #ByteRTCVideo#startPlayPublicStream:} for details about subscribing to a public stream.
 * @param engine ByteRTCVideo instance
 * @param publicStreamId ID of the public stream
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onFirstPublicStreamAudioFrame:(NSString * _Nonnull)publicStreamId;
/**
 * @locale zh
 * @type callback
 * @brief 调用 startCloudProxy:{@link #ByteRTCVideo#startCloudProxy:} 开启云代理，SDK 首次成功连接云代理服务器时，回调此事件。
 * @param interval 从开启云代理到连接成功经过的时间，单位为 ms
 */
/**
 * @locale en
 * @type callback
 * @brief Receives the callback when you call startCloudProxy:{@link #ByteRTCVideo#startCloudProxy:} to start cloud proxy, and the SDK connects the proxy server successfully.
 * @param interval The interval in ms between starting cloud proxy and connects the cloud proxy server successfully.
 */
- (void)rtcEngine:(ByteRTCVideo *  _Nonnull)engine onCloudProxyConnected:(NSInteger)interval;
/**
 * @locale zh
 * @type callback
 * @region 网络管理
 * @brief 关于音视频回路测试结果的回调。
 * @param result 测试结果，参看 ByteRTCEchoTestResult{@link #ByteRTCEchoTestResult}。
 * @note 该回调触发的时机包括： <br>
 *        + 检测过程中采集设备发生错误时；  <br>
 *        + 检测成功后；  <br>
 *        + 非设备原因导致检测过程中未接收到音/视频回放，停止检测后。
 */
/**
 * @locale en
 * @type callback
 * @region Network Management
 * @brief Callback about the call test result.
 * @param result Test result, see ByteRTCEchoTestResult{@link #ByteRTCEchoTestResult}.
 * @note The timing when this callback will be triggered is as follows:  <br>
 *        + A device-related error occurred during the test；  <br>
 *        + After a successful test；  <br>
 *        + After stopping the test, provided that the audio/video playback was not received during the test due to non-device reasons.
 */
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onEchoTestResult:(ByteRTCEchoTestResult)result NS_SWIFT_NAME(rtcEngine(_:onEchoTestResult:));

/**
 * @locale zh
 * @hidden for internal use only
 * @type callback
 * @brief 音频dump状态回调。
 * @param status 音频dump状态，参看 ByteRTCAudioDumpStatus{@link #ByteRTCAudioDumpStatus}。
 * @note 本回调用于内部排查音质相关异常问题，开发者无需关注。
 */
/**
 * @locale en
 * @hidden for internal use only
 * @type callback
 * @brief audio dump status change callback
 * @param status audio dump status, see ByteRTCAudioDumpStatus{@link #ByteRTCAudioDumpStatus}.
 * @note This callback is used to internally troubleshoot sound quality related exceptions, which developers need not pay attention to.
 */
- (void)rtcEngine: (ByteRTCVideo* _Nonnull)engine onAudioDumpStateChanged: (ByteRTCAudioDumpStatus)status;
/**
 * @locale zh
 * @type callback
 * @brief 首次调用 getNetworkTimeInfo{@link #ByteRTCVideo#getNetworkTimeInfo} 后，SDK 内部启动网络时间同步，同步完成时会触发此回调。
 * @param engine ByteRTCVideo{@link #ByteRTCVideo} 对象
 */
/**
 * @locale en
 * @type callback
 * @brief After calling getNetworkTimeInfo{@link #ByteRTCVideo#getNetworkTimeInfo} for the first time, the SDK starts network time synchronization internally. This callback will be triggered when the synchronization is completed.
 * @param engine See ByteRTCVideo{@link #ByteRTCVideo}.
 */
- (void)rtcEngineOnNetworkTimeSynchronized:(ByteRTCVideo *_Nonnull)engine;

/**
 * @locale zh
 * @hidden internal use only
 * @type callback
 * @brief license过期时间提醒
 * @param engine ByteRTCVideo{@link #ByteRTCVideo} 对象
 * @param days 过期时间天数
 */

/**
 * @locale en
 * @hidden internal use only
 * @type callabck
 * @brief License expiration time reminder
 * @param engine ByteRTCVideo{@link #ByteRTCVideo} object.
 * @param days Expiration time in days
 */
- (void)rtcEngine:(ByteRTCVideo *  _Nonnull)engine onLicenseWillExpire:(NSInteger)days;
/**
 * @locale zh
 * @hidden internal use
 * @valid since 3.52
 * @type callback
 * @brief 试验性接口回调
 * @param param 回调内容(JSON string)
 */
/**
 * @locale en
 * @hidden internal use
 * @valid since 3.52
 * @type callabck
 * @brief callback for experimental api
 * @param param result of callback in JSON string
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onInvokeExperimentalAPI:(NSString * _Nonnull) param;

/**
 * @locale zh
 * @type callback
 * @brief 通话前回声检测结果回调。
 * @param result 参见 ByteRTCHardwareEchoDetectionResult{@link #ByteRTCHardwareEchoDetectionResult}。
 * @note 
 *        + 通话前调用 startHardwareEchoDetection:{@link #ByteRTCVideo#startHardwareEchoDetection:} 后，将触发本回调返回检测结果。<br>
 *        + 建议在收到检测结果后，调用 stopHardwareEchoDetection{@link #ByteRTCVideo#stopHardwareEchoDetection} 停止检测，释放对音频设备的占用。<br>
 *        + 如果 SDK 在通话中检测到回声，将通过 rtcEngine:onAudioDeviceWarning:deviceType:deviceWarning:{@link #ByteRTCVideoDelegate#rtcEngine:onAudioDeviceWarning:deviceType:deviceWarning:} 回调 `ByteRTCMediaDeviceWarningDetectLeakEcho`。
 */
/**
 * @locale en
 * @type callback
 * @brief Callback that notifies you the result of the echo detection before a call
 * @param result Refer to ByteRTCHardwareEchoDetectionResult{@link #ByteRTCHardwareEchoDetectionResult} for more details.
 * @note  
 *        + This callback notifies you the result of the echo detection by calling startHardwareEchoDetection:{@link #ByteRTCVideo#startHardwareEchoDetection:}. <br>
 *        + We recommend to call stopHardwareEchoDetection{@link #ByteRTCVideo#stopHardwareEchoDetection} to stop the detection. <br>
 *        + Listen to `ByteRTCMediaDeviceWarningDetectLeakEcho` in the callback of rtcEngine:onAudioDeviceWarning:deviceType:deviceWarning:{@link #ByteRTCVideoDelegate#rtcEngine:onAudioDeviceWarning:deviceType:deviceWarning:} for the echo issue during a call.
 */
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onHardwareEchoDetectionResult:(ByteRTCHardwareEchoDetectionResult)result NS_SWIFT_NAME(rtcEngine(_:onHardwareEchoDetectionResult:));
/**
 * @locale zh
 * @type callback
 * @region proxy
 * @brief 本地代理状态发生改变回调。调用 setLocalProxy:{@link #ByteRTCVideo#setLocalProxy:} 设置本地代理后，SDK 会触发此回调，返回代理连接的状态。  
 * @param type 本地代理类型。参看 ByteRTCLocalProxyType{@link #ByteRTCLocalProxyType} 。  
 * @param state 本地代理状态。参看 ByteRTCLocalProxyState{@link #ByteRTCLocalProxyState}。  
 * @param error 本地代理错误。参看 ByteRTCLocalProxyError{@link #ByteRTCLocalProxyError}。
 */
/**
 * @locale en
 * @type callback
 * @region proxy
 * @brief Callback on local proxy connection. After calling setLocalProxy:{@link #ByteRTCVideo#setLocalProxy:} to set local proxies, you will receive this callback that informs you of the states of local proxy connection. 
 * @param type The types of local proxies. Refer to ByteRTCLocalProxyType{@link #ByteRTCLocalProxyType} for details.  
 * @param state The states of local proxy connection. Refer to ByteRTCLocalProxyState{@link #ByteRTCLocalProxyState} for details.  
 * @param error The errors of local proxy connection. Refer to ByteRTCLocalProxyError{@link #ByteRTCLocalProxyError} for details.
 */
- (void)rtcEngine:(ByteRTCVideo * _Nonnull)engine onLocalProxyStateChanged:(ByteRTCLocalProxyType)type withProxyState:(ByteRTCLocalProxyState)state withProxyError:(ByteRTCLocalProxyError)error;
/**
 * @locale zh
 * @hidden internal use only
 * @type callback
 * @brief 当特效设置失败时，收到此回调。
 * @param error 特效错误类型。参看 ByteRTCEffectErrorType{@link #ByteRTCEffectErrorType}。
 * @param msg 错误信息。
 */
/**
 * @locale en
 * @hidden internal use only
 * @type callback
 * @brief Effect failed.
 * @param error The error type of effect. Refer to ByteRTCEffectErrorType{@link #ByteRTCEffectErrorType} for details.
 * @param msg Error message.
 */
- (void)rtcEngine:(ByteRTCVideo *_Nonnull)engine onEffectError:(ByteRTCEffectErrorType)error msg:(NSString * _Nonnull)msg;
@end
#pragma mark - RTCVideo
/**
 * @type api
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVideo : NSObject
/**
 * @type callback
 */
@property (nonatomic, weak) id<ByteRTCVideoDelegate> _Nullable delegate;
/**
 * @hidden
 * @deprecated
 */
@property (nonatomic, weak) id<ByteRTCMonitorDelegate> _Nullable monitorDelegate
    __deprecated_msg("Will be removed in new version");

#pragma mark Core Methods
/**
 * @hidden for internal use only
 */
+ (void)setDeviceId:(NSString* _Nonnull) deviceID;

// @name core method
/**
 * @locale zh
 * @type api
 * @region 引擎管理
 * @brief 创建引擎对象。<br>
 *        如果当前进程中未创建引擎实例，那么你必须先使用此方法，以使用 RTC 提供的各种音视频能力。  <br>
 *        如果当前进程中已创建了引擎实例，再次调用此方法时，会返回已创建的引擎实例。
 * @param appId 每个应用的唯一标识符，由 RTC 控制台随机生成的。<br>
 *              不同的 AppId 生成的实例在 RTC 中进行音视频通话完全独立，无法互通。
 * @param delegate SDK 回调给应用层的 delegate，详见 ByteRTCVideoDelegate{@link #ByteRTCVideoDelegate}
 * @param parameters 私有参数。如需使用请联系技术支持人员。
 * @return 可用的 ByteRTCVideo{@link #ByteRTCVideo} 实例
 * @list 引擎管理
 * @order 1
 */
/**
 * @locale en
 * @type api
 * @region Engine Management
 * @brief Creates an engine instance.   <br>
 *        This is the very first API that you must call if you want to use all the RTC capabilities.  <br>
 *        If there is no engine instance in current process, calling this API will create one. If an engine instance has been created, calling this API again will have the created engine instance returned.
 * @param appId A unique identifier for each App, randomly generated by the RTC console. Engine instances created with different AppIds cannot communicate with each other.
 * @param delegate Delegate sent from SDK to App. See ByteRTCVideoDelegate{@link #ByteRTCVideoDelegate}
 * @param parameters Reserved parameters. Please contact technical support fellow if needed.
 * @return A ByteRTCVideo{@link #ByteRTCVideo} instance
 * @list Engine Management
 * @order 1
 */
+ (ByteRTCVideo * _Nullable) createRTCVideo:(NSString * _Nonnull)appId
                                      delegate:(id<ByteRTCVideoDelegate> _Nullable)delegate
                                    parameters:(NSDictionary * _Nonnull)parameters;

/**
 * @locale zh
 * @hidden internal use only
 * @type api
 * @region 引擎管理
 * @brief 创建多实例引擎对象  <br>
 *        如果当前进程中未创建引擎实例，那么你必须先使用此方法，以使用 RTC 提供的各种音视频能力。  <br>
 *        如果当前进程中已创建了引擎实例，再次调用此方法时，会返回新创建的引擎实例。
 * @param context Android Application Context
 * @param appId 每个应用的唯一标识符，由 RTC 控制台随机生成的。不同的 AppId 生成的实例在 RTC 中进行音视频通话完全独立，无法互通。  
 * @param handler SDK 回调给应用层的 Handler，详见 IRTCVideoEventHandler{@link #IRTCVideoEventHandler}  
 * @param eglContext 如果需要支持外部纹理硬编码，则需要以 `JObject` 方式传入 `eglContext`。  
 * @param parameters 私有参数。如需使用请联系技术支持人员。
 * @return  
 *        + RTCVideo：创建成功。返回一个可用的 ByteRTCVideo{@link #ByteRTCVideo} 实例  <br>
 *        + Null：.so 文件加载失败，创建失败。
 * @note 你应注意保持 handler 的生命周期必须大于 ByteRTCVideo{@link #ByteRTCVideo} 的生命周期，即 handler 必须在调用 destroyRTCVideo{@link #RTCVideo#destroyRTCVideo} 之后销毁。
 */
/**
 * @locale en
 * @hidden internal use only
 * @type api
 * @region Engine Management
 * @brief Creates an engine instance for multi-engine senario.   <br>
 *        This is the very first API that you must call if you want to use all the RTC capabilities.  <br>
 *        If there is no engine instance in current process, calling this API will create one. If an engine instance has been created, calling this API again will have a new created engine instance returned.
 * @param context Android application context
 * @param appId A unique identifier for each App, randomly generated by the RTC console. Engine instances created with different AppIds cannot communicate with each other.
 * @param handler Handler sent from SDK to App. See IRTCVideoEventHandler{@link #IRTCVideoEventHandler} 
 * @param eglContext If you need SDK to support custom texture hardcoding, you must import the eglContext in a JObject. 
 * @param parameters Reserved parameters. Please contact technical support fellow if needed.
 * @return  
 *         + RTCVideo: A successfully created engine instance.  <br>
 *         + Null: Failed to load the .so file. No instance is returned.
 * @note The lifecycle of the handler must be longer than that of the RTCVideo, i.e. the handler must be created before calling createRTCVideo:delegate:parameters:{@link #RTCVideo#createRTCVideo:delegate:parameters:} and destroyed after calling destroyRTCVideo{@link #RTCVideo#destroyRTCVideo}.
 */
+ (ByteRTCVideo * _Nullable) createRTCVideoMulti:(NSString * _Nonnull)appId
                               delegate:(id<ByteRTCVideoDelegate> _Nullable)delegate
                                      parameters:(NSDictionary * _Nonnull)parameters;

/**
 * @locale zh
 * @type api
 * @region 引擎管理
 * @brief 销毁由 createRTCVideo:delegate:parameters:{@link #ByteRTCVideo#createRTCVideo:delegate:parameters:} 所创建的引擎实例，并释放所有相关资源。
 * @note  
 *      + 请确保和需要销毁的 ByteRTCVideo{@link #ByteRTCVideo} 实例相关的业务场景全部结束后，才调用此方法  <br>
 *      + 该方法在调用之后，会销毁所有和此 ByteRTCVideo{@link #ByteRTCVideo} 实例相关的内存，并且停止与媒体服务器的任何交互  <br>
 *      + 调用本方法会启动 SDK 退出逻辑。引擎线程会保留，直到退出逻辑完成。因此，不要在回调线程中直接调用此 API，会导致死锁。同时此方法是耗时操作，不建议在主线程调用本方法，避免主线程阻塞。  <br>
 *      + 可以通过 Objective-C 的ARC机制，在 dealloc 时自动触发销毁逻辑
 * @list 引擎管理
 * @order 2
 */
/**
 * @locale en
 * @type api
 * @region Engine Management
 * @brief Destroy the engine instance created by createRTCVideo:delegate:parameters:{@link #ByteRTCVideo#createRTCVideo:delegate:parameters:}, and release all related resources.
 * @note  
 *       + Call this API after all business scenarios related to the engine instance are destroyed.  <br>
 *       + When the API is called, RTC SDK destroys all memory associated with the engine instance and stops any interaction with the media server.  <br>
 *       + Calling this API will start the SDK exit logic. The engine thread is held until the exit logic is complete. The engine thread is retained until the exit logic is complete. Therefore, do not call this API directly in the callback thread, or it will cause a deadlock. This function takes a long time to execute, so it's not recommended to call this API in the main thread, or the main thread may be blocked.<br>
 *       + You can enable ARC for Objective-C, to automatically trigger the destruction logic when the dealloc method is called.
 * @list Engine Management
 * @order 2
 */
+ (void)destroyRTCVideo NS_SWIFT_NAME(destroyRTCVideo());
/**
 * @locale zh
 * @hidden internal use only
 * @type api
 * @region 引擎管理
 * @brief 销毁由 createRTCVideoMulti:delegate:parameters:{@link #ByteRTCVideo#createRTCVideoMulti:delegate:parameters:} 所创建的引擎实例，并释放所有相关资源。
 * @note  
 *      + 请确保和需要销毁的 ByteRTCVideo{@link #ByteRTCVideo} 实例相关的业务场景全部结束后，才调用此方法  <br>
 *      + 该方法在调用之后，会销毁所有和此 ByteRTCVideo{@link #ByteRTCVideo} 实例相关的内存，并且停止与媒体服务器的任何交互  <br>
 *      + 调用本方法会启动 SDK 退出逻辑。引擎线程会保留，直到退出逻辑完成。因此，不要在回调线程中直接调用此 API，会导致死锁。同时此方法是耗时操作，不建议在主线程调用本方法，避免主线程阻塞。  <br>
 *      + 可以通过 Objective-C 的ARC机制，在 dealloc 时自动触发销毁逻辑
 */
/**
 * @locale en
 * @hidden internal use only
 * @type api
 * @region Engine Management
 * @brief Destroy the engine instance created by createRTCVideoMulti:delegate:parameters:{@link #ByteRTCVideo#createRTCVideoMulti:delegate:parameters:}, and release all related resources.
 * @note  
 *       + Call this API after all business scenarios related to the engine instance are destroyed.  <br>
 *       + When the API is called, RTC SDK destroys all memory associated with the engine instance and stops any interaction with the media server.  <br>
 *       + Calling this API will start the SDK exit logic. The engine thread is held until the exit logic is complete. The engine thread is retained until the exit logic is complete. Therefore, do not call this API directly in the callback thread, or it will cause a deadlock. This function takes a long time to execute, so it's not recommended to call this API in the main thread, or the main thread may be blocked.<br>
 *       + You can enable ARC for Objective-C, to automatically trigger the destruction logic when the dealloc method is called.
 */
+ (void)destroyRTCVideoMulti:(ByteRTCVideo*)engine;

/**
 * @locale zh
 * @type api
 * @region 引擎管理
 * @brief 获取 SDK 当前的版本号。
 * @return SDK 当前的版本号。
 * @list 引擎管理
 * @order 5
 */
/**
 * @locale en
 * @type api
 * @region  engine management
 * @brief  Gets the current version number of the SDK.
 * @return SDK  The current version number.
 * @list Engine Management
 * @order 5
 */
+ (NSString * _Nonnull)getSDKVersion;

/**
 * @locale zh
 * @type api
 * @region 引擎管理
 * @brief 配置 SDK 本地日志参数，包括日志级别、存储路径、日志文件最大占用的总空间、日志文件名前缀。
 * @param logConfig 本地日志参数，参看 ByteRTCLogConfig{@link #ByteRTCLogConfig}。
 * @return 
 *        + 0：成功。<br>
 *        + –1：失败，本方法必须在创建引擎前调用。<br>
 *        + –2：失败，参数填写错误。
 * @note 本方法必须在调用 createRTCVideo:delegate:parameters:{@link #ByteRTCVideo#createRTCVideo:delegate:parameters:} 之前调用。
 * @list 引擎管理
 * @order 30
 */
/**
 * @locale en
 * @type api
 * @region Engine Management
 * @brief Configures the local log parameters of RTC SDK, including the logging level, directory, and the limits for total log file size.
 * @param logConfig Local log parameters. See ByteRTCLogConfig{@link #ByteRTCLogConfig}.
 * @return 
 *        + 0: Success.<br>
 *        + –1: Failure. This API must be called before creating engine.<br>
 *        + –2: Failure. Invalid parameters.
 * @note This API must be called before createRTCVideo:delegate:parameters:{@link #ByteRTCVideo#createRTCVideo:delegate:parameters:}.
 * @list Engine Management
 * @order 30
 */
+ (int) setLogConfig:(ByteRTCLogConfig *_Nonnull) logConfig;

/**
 * @locale zh
 * @type api
 * @region 引擎管理
 * @brief 获取 SDK 内各种错误码、警告码的描述文字。
 * @param code  <br>
 *        通过 rtcEngine:onWarning:{@link #ByteRTCVideoDelegate#rtcEngine:onWarning:} 和 rtcEngine:onError:{@link #ByteRTCVideoDelegate#rtcEngine:onError:} 回调获得的值，<br>
 *        具体可以参考 ByteRTCWarningCode{@link #ByteRTCWarningCode} 和 ByteRTCErrorCode{@link #ByteRTCErrorCode} 。
 * @return 描述文字。
 * @list 引擎管理
 * @order 15
 */
/**
 * @locale en
 * @type api
 * @region  engine management
 * @brief Gets the description text of different error codes and warning codes in the SDK.
 * @param code   <br>
 *        The value obtained by rtcEngine:onWarning:{@link #ByteRTCVideoDelegate#rtcEngine:onWarning:} and rtcEngine:onError:{@link #ByteRTCVideoDelegate#rtcEngine:onError:} callbacks,<br>
 *        For details, please refer to ByteRTCWarningCode{@link #ByteRTCWarningCode} and ByteRTCErrorCode{@link #ByteRTCErrorCode}.
 * @return  Description text.
 * @list Engine Management
 * @order 15
 */
+ (NSString * _Nonnull)getErrorDescription:(NSInteger)code;
#pragma mark Core Audio Methods
// @name audio core method
/**
 * @locale zh
 * @type api
 * @region 自定义音频采集渲染
 * @brief 切换音频采集方式
 * @param type 音频数据源，详见 ByteRTCAudioSourceType{@link #ByteRTCAudioSourceType}。<br>
 *             默认使用内部音频采集。音频采集和渲染方式无需对应。
 * @return 方法调用结果：  <br>
 *        + >0: 切换成功。<br>
 *        + -1：切换失败。
 * @note  
 *      + 进房前后调用此方法均有效。<br>
 *      + 如果你调用此方法由内部采集切换至自定义采集，SDK 会自动关闭内部采集。然后，调用 pushExternalAudioFrame:{@link #ByteRTCVideo#pushExternalAudioFrame:} 推送自定义采集的音频数据到 RTC SDK 用于传输。 <br>
 *      + 如果你调用此方法由自定义采集切换至内部采集，你必须再调用 startAudioCapture{@link #ByteRTCVideo#startAudioCapture} 手动开启内部采集。
 */
/**
 * @locale en
 * @type api
 * @region Custom Audio Capture and Rendering
 * @brief Switches the audio capture type.
 * @param type Audio input source type. See ByteRTCAudioSourceType{@link #ByteRTCAudioSourceType} <br>
 *            Use internal audio capture by default. The audio capture type and the audio render type may be different from each other.
 * @return  Method call result:   <br>
 *         + >0: Success. <br>
 *         + -1: Failure.
 * @note   
 *       + You can call this API before or after joining the room.<br>
 *       + If you call this API to switch from internal audio capture to custom capture, the internal audio capture is automatically disabled. You must call pushExternalAudioFrame:{@link #ByteRTCVideo#pushExternalAudioFrame:} to push custom captured audio data to RTC SDK for transmission. <br>
 *       + If you call this API to switch from custom capture to internal capture, you must then call startAudioCapture{@link #ByteRTCVideo#startAudioCapture} to enable internal capture.
 */
- (int)setAudioSourceType:(ByteRTCAudioSourceType) type;
/**
 * @locale zh
 * @type api
 * @region 自定义音频采集渲染
 * @brief  切换音频渲染方式
 * @param type 音频输出类型，详见 ByteRTCAudioRenderType{@link #ByteRTCAudioRenderType} <br>
 *             默认使用内部音频渲染。音频采集和渲染方式无需对应。
 * @return  方法调用结果：  <br>
 *        + >0: 切换成功。<br>
 *        + -1：切换失败。
 * @note  
 *      + 进房前后调用此方法均有效。<br>
 *      + 如果你调用此方法切换至自定义渲染，调用 pullExternalAudioFrame:{@link #ByteRTCVideo#pullExternalAudioFrame:} 获取音频数据。 
 */
/**
 * @locale en
 * @type api
 * @region Custom Audio Capture and Rendering
 * @brief Switches the audio render type.
 * @param type Audio output source type. See ByteRTCAudioRenderType{@link #ByteRTCAudioRenderType}. <br>
 *             Use internal audio render by default. The audio capture type and the audio render type may be different from each other.
 * @return   Method call result:   <br>
 *         + >0: Success. <br>
 *         + -1: Failure.
 * @note   
 *       + You can call this API before or after joining the room. <br>
 *       + After calling this API to enable custom audio rendering, call pullExternalAudioFrame:{@link #ByteRTCVideo#pullExternalAudioFrame:} for audio data.
 */
- (int)setAudioRenderType:(ByteRTCAudioRenderType) type;
/**
 * @locale zh
 * @type api
 * @region 音频管理
 * @brief 开启内部音频采集。默认为关闭状态。  <br>
 *        内部采集是指：使用 RTC SDK 内置的音频采集机制进行音频采集。<br>
 *        调用该方法开启后，本地用户会收到 rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:} 的回调。  <br>
 *        非隐身用户进房后调用该方法，房间中的其他用户会收到 rtcEngine:onUserStartAudioCapture:uid:{@link #ByteRTCVideoDelegate#rtcEngine:onUserStartAudioCapture:uid:} 的回调。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note  
 *       + 若未取得当前设备的麦克风权限，调用该方法后会触发 rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:} 回调，对应的错误码为 `ByteRTCMediaDeviceError.ByteRTCMediaDeviceErrorDeviceNoPermission = 1`。<br>
 *       + 调用 stopAudioCapture{@link #ByteRTCVideo#stopAudioCapture} 可以关闭音频采集设备，否则，SDK 只会在销毁引擎的时候自动关闭设备。  <br>
 *       + 由于不同硬件设备初始化响应时间不同，频繁调用 stopAudioCapture{@link #ByteRTCVideo#stopAudioCapture} 和本接口闭麦/开麦可能出现短暂无声问题，建议使用 publishStream:{@link #ByteRTCRoom#publishStream:}/unpublishStream:{@link #ByteRTCRoom#unpublishStream:} 实现临时闭麦和重新开麦。<br>
 *       + 创建引擎后，无论是否发布音频数据，你都可以调用该方法开启音频采集，并且调用后方可发布音频。  <br>
 *       + 如果需要从自定义音频采集切换为内部音频采集，你必须先停止发布流，调用 setAudioSourceType:{@link #ByteRTCVideo#setAudioSourceType:} 关闭自定义采集，再调用此方法手动开启内部采集。
 */
/**
 * @locale en
 * @type api
 * @region Audio management
 * @brief Starts internal audio capturing. The default is off.   <br>
 *        Internal capture refers to audio capture using the built-in capture module of the SDK.<br>
 *        After this API is called, the local user will receive rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:}.<br>
 *        If this API is called by a visible user, the other users in the room will receive rtcEngine:onUserStartAudioCapture:uid:{@link #ByteRTCVideoDelegate#rtcEngine:onUserStartAudioCapture:uid:}.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note   
 *        + Calling this API without obtaining permission to use the microphone of the current device will trigger rtcEngine:onWarning:{@link #ByteRTCVideoDelegate#rtcEngine:onWarning:}.  <br>
 *        + Call stopAudioCapture{@link #ByteRTCVideo#stopAudioCapture} to stop the internal audio capture. Otherwise, the internal audio capture will sustain until you destroy the engine instance. <br>
 *        + To mute and unmute microphones, we recommend using publishStream:{@link #ByteRTCRoom#publishStream:} and unpublishStream:{@link #ByteRTCRoom#unpublishStream:}, other than stopAudioCapture{@link #ByteRTCVideo#stopAudioCapture} and this API. Because starting and stopping capture devices often need some time waiting for the response of the device, that may lead to a short silence during the communication.<br>
 *        + Once you create the engine instance, you can start internal audio capture regardless of the audio publishing state. The audio stream will start publishing only after the audio capture starts. <br>
 *        + To switch from custom to internal audio capture, stop publishing before disabling the custom audio capture module by calling setAudioSourceType:{@link #ByteRTCVideo#setAudioSourceType:} and then call this API to enable the internal audio capture.
 */
- (int)startAudioCapture;
 /**
  * @locale zh
  * @type api
  * @region 音频管理
  * @brief 关闭内部音频采集。默认为关闭状态。  <br>
  *        内部采集是指：使用 RTC SDK 内置的音频采集机制进行音频采集。<br>
  *        调用该方法，本地用户会收到 rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:} 的回调。  <br>
  *        非隐身用户进房后调用该方法，房间中的其他用户会收到 rtcEngine:onUserStopAudioCapture:uid:{@link #ByteRTCVideoDelegate#rtcEngine:onUserStopAudioCapture:uid:} 的回调。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
  * @note  
  *       + 调用 startAudioCapture{@link #ByteRTCVideo#startAudioCapture} 可以开启音频采集设备。  <br>
  *       + 如果不调用本方法停止内部视频采集，则只有当销毁引擎实例时，内部音频采集才会停止。
  */
 /**
  * @locale en
  * @type api
  * @region audio management
  * @brief Stops internal audio capturing. The default is off.   <br>
  *        Internal audio capture refers to: capturing audio using the built-in module.<br>
  *        The local client will be informed via rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:} after stopping audio capture by calling this API.<br>
  *         The remote clients in the room will be informed of the state change via rtcEngine:onUserStopAudioCapture:uid:{@link #ByteRTCVideoDelegate#rtcEngine:onUserStopAudioCapture:uid:} after the visible client stops audio capture by calling this API.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
  * @note   
  *        + Call startAudioCapture{@link #ByteRTCVideo#startAudioCapture} to enable the internal audio capture. <br>
  *        + Without calling this API the internal audio capture will sustain until you destroy the engine instance.
  */
- (int)stopAudioCapture;
/**
 * @locale zh
 * @hidden(macOS)
 * @type api
 * @region 音频管理
 * @brief 设置音频场景类型。<br>
 *        你可以根据你的应用所在场景，选择合适的音频场景类型。<br>
 *        选择音频场景后，SDK 会自动根据客户端音频采集播放设备和状态，适用通话音量/媒体音量。
 * @param audioScenario 音频场景类型，参看 ByteRTCAudioScenarioType{@link #ByteRTCAudioScenarioType}。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note  
 *        + 建议在加入房间和调用音频相关接口之前，调用此接口设置音频场景类型。如果在此之后调用此接口，可能会引入音频卡顿。<br>
 *        + 通话音量更适合通话、会议等对信息准确度更高的场景。通话音量会激活系统硬件信号处理，使通话声音更清晰。同时，音量无法降低到 0。<br>
 *        + 媒体音量更适合娱乐场景，因其声音的表现力会更强。媒体音量下，最低音量可以为 0。
 */
/**
 * @locale en
 * @hidden(macOS)
 * @type api
 * @region Audio management
 * @brief Sets the audio scenarios.<br>
 *        You can choose the appropriate audio scenario according to your application.<br>
 *        After selecting the audio scenario, SDK will automatically select the call/media volume, according to the client-side audio device and status.
 * @param audioScenario  Audio scenarios. See ByteRTCAudioScenarioType{@link #ByteRTCAudioScenarioType}.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note   
 *         + It is recommended to call this API before joining the room and calling other audio related interfaces. If this API is called afterwards, audio lag may be introduced.<br>
 *         + Call volume is more suitable for calls, meetings and other scenarios that demand information accuracy. Call volume will activate the system hardware signal processor, making the sound clearer. The volume cannot be reduced to 0. <br>
 *         + Media volume is more suitable for entertainment scenarios, which require musical expression. The volume can be reduced to 0.
 */
- (int)setAudioScenario:(ByteRTCAudioScenarioType)audioScenario;
/**
 * @locale zh
 * @valid since 3.55
 * @hidden(macOS) internal use only
 * @type api
 * @brief 设置音频场景类型。<br>
 *        选择音频场景后，SDK 会自动根据场景切换对应的音量模式（通话音量/媒体音量）和该场景下的最佳音频配置。和 `setAudioScenario` 不同的是，`audioScenario` 只修改了音量模式，不会修改音频相关的算法配置。<br>
 *        该接口不应与旧接口 `setAudioScenario` 混用。
 * @param audioScene 音频场景类型，参看 ByteRTCAudioSceneType{@link #ByteRTCAudioSceneType}。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note  
 *        + 此接口在进房前后调用都有效。<br>
 *        + 通话音量更适合通话、会议等对信息准确度更高的场景。通话音量会激活系统硬件信号处理，使通话声音更清晰。同时，音量无法降低到 0。<br>
 *        + 媒体音量更适合娱乐场景，因其声音的表现力会更强。媒体音量下，最低音量可以为 0。
 */
/**
 * @locale en
 * @valid since 3.55
 * @hidden(macOS) internal use only
 * @type api
 * @brief Sets the audio scenarios.<br>
 *        After selecting the audio scenario, SDK will automatically switch to the proper volume modes (the call/media volume) according to the scenarios and the best audio configurations under such scenarios. This API is different with `setAudioScenario` in that `audioScenario` will only change the volume mode and will not change the algorithm related to audio. <br>
 *        This API should not be used at the same time with the old one. 
 * @param audioScene Audio scenarios. See ByteRTCAudioSceneType{@link #ByteRTCAudioSceneType}.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note  
 *        + You can use this API both before and after joining the room.<br>
 *        + Call volume is more suitable for calls, meetings and other scenarios that demand information accuracy. Call volume will activate the system hardware signal processor, making the sound clearer. The volume cannot be reduced to 0. <br>
 *        + Media volume is more suitable for entertainment scenarios, which require musical expression. The volume can be reduced to 0.
 */
- (int)setAudioScene:(ByteRTCAudioSceneType)audioScene;

/**
 * @locale zh
 * @type api
 * @region 音频管理
 * @brief 设置音质档位。<br>
 *        当所选的 ByteRTCRoomProfile{@link #ByteRTCRoomProfile} 中的音频参数无法满足你的场景需求时，调用本接口切换的音质档位。
 * @param audioProfile 音质档位，参看 ByteRTCAudioProfileType{@link #ByteRTCAudioProfileType}
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note  
 *        + 该方法在进房前后均可调用；  <br>
 *        + 支持通话过程中动态切换音质档位。
 */
/**
 * @locale en
 * @type api
 * @region audio management
 * @brief Sets the sound quality. You should choose the appropriate sound quality according to the needs of the business scenario.   
 * @param audioProfile  Sound quality. See ByteRTCAudioProfileType{@link #ByteRTCAudioProfileType}
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note   
 *         + This method can be called before and after entering the room; <br>
 *         + Support dynamic switching of sound quality during a call.
 */
- (int)setAudioProfile:(ByteRTCAudioProfileType)audioProfile;
/**
 * @locale zh
 * @type api
 * @region 音频管理
 * @brief 支持根据业务场景，设置通话中的音频降噪模式。
 * @param ansMode 降噪模式。具体参见 ByteRTCAnsMode{@link #ByteRTCAnsMode}。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note  
 *        + 该接口进房前后均可调用，可重复调用，仅最后一次调用生效。<br>
 *        + 降噪算法包含传统降噪和 AI 降噪。传统降噪主要是抑制平稳噪声，比如空调声、风扇声等。而 AI 降噪主要是抑制非平稳噪声，比如键盘敲击声、桌椅碰撞声等。<br>
 *        + 在 V3.57.1 之前的版本，只有以下 ByteRTCRoomProfile{@link #ByteRTCRoomProfile} 场景时，调用本接口可以开启 AI 降噪。其余场景的 AI 降噪不会生效。<br>
 *                 -  游戏语音模式： `ByteRTCRoomProfileGame`<br>
 *                 -  高音质游戏模式： `ByteRTCRoomProfileGameHD`<br>
 *                 -  云游戏模式： `ByteRTCRoomProfileCloudGame`<br>
 *                 -  1 vs 1 音视频通话： `ByteRTCRoomProfileChat`<br>
 *                 -  多端同步播放音视频：`ByteRTCRoomProfileLwTogether`<br>
 *                 -  云端会议中的个人设备：`ByteRTCRoomProfileMeeting`<br>
 *                 -  课堂互动模式：`ByteRTCRoomProfileClassroom`<br>
 *                 -  云端会议中的会议室终端：`ByteRTCRoomProfileMeetingRoom`
 */
/**
 * @locale en
 * @type api
 * @region audio management
 * @brief Set the Active Noise Cancellation(ANC) mode during audio and video communications.
 * @param ansMode ANC modes. See ByteRTCAnsMode{@link #ByteRTCAnsMode}.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note You can call this API before or after entering a room. When you repeatedly call it, only the last call takes effect.
 */
- (int)setAnsMode:(ByteRTCAnsMode)ansMode;

#if BYTERTC_TARGET_MAC
/**
 * @locale zh
 * @hidden(iOS)
 * @valid since 3.51
 * @type api
 * @region 音频设备管理
 * @brief 打开/关闭 AGC 功能
 * @brief 打开/关闭 AGC(Analog Automatic Gain Control)模拟自动增益控制功能。<br>
 *        开启该功能后，SDK 会自动调节麦克风的采集音量，确保音量稳定。
 * @param enable 是否打开 AGC 功能: <br>
 *        + true: 打开 AGC 功能。<br>
 *        + false: 关闭 AGC 功能。
 * @return  
 *        +  0: 调用成功。<br>
 *        + -1: 调用失败。
 * @note  
 *         该方法在进房前后均可调用。如果你需要在进房前使用 AGC 功能，请联系技术支持获得私有参数，传入对应 ByteRTCRoomProfile{@link #ByteRTCRoomProfile} 。 <br>
 *         要想在进房后开启 AGC 功能，你需要把 ByteRTCRoomProfile{@link #ByteRTCRoomProfile} 设为 `ByteRTCRoomProfileMeeting`、`ByteRTCRoomProfileMeetingRoom` 或`ByteRTCRoomProfileClassroom` 。 <br>
 *         AGC 功能生效后，不建议再调用 setAudioCaptureDeviceVolume:{@link #ByteRTCAudioDeviceManager#setAudioCaptureDeviceVolume:} 来调节设备麦克风的采集音量。
 */
/**
 * @locale en
 * @hidden(iOS)
 * @valid since 3.51
 * @type api
 * @region Audio device Management
 * @brief  Turns on/ off AGC(Analog Automatic Gain Control). <br>
 *         After AGC is enabled, SDK can automatically adjust mircrophone pickup volume to keep the output volume at a steady level.
 * @param enable whether to turn on AGC. <br>
 *        + true: AGC is turned on.  <br>
 *        + false: AGC is turned off,with DAGC(Digtal Automatic Gain Control) still on. 
 * @return  
 *         + 0: Success. <br>
 *         + -1: Failure.
 * @note  
 *         You can call this method before and after joining the room. To turn on AGC before joining the room, you need to contact the technical support to get a private parameter to set ByteRTCRoomProfile{@link #ByteRTCRoomProfile}. <br>
 *         To enable AGC after joining the room, you must set ByteRTCRoomProfile{@link #ByteRTCRoomProfile} to `ByteRTCRoomProfileMeeting`, `ByteRTCRoomProfileMeetingRoom`  or `ByteRTCRoomProfileClassroom`.  <br>
 *         It is not recommended to call setAudioCaptureDeviceVolume:{@link #ByteRTCAudioDeviceManager#setAudioCaptureDeviceVolume:} to adjust mircrophone pickup volume with AGC on. 
 */
- (int)enableAGC:(BOOL)enable;
#endif

/**
 * @locale zh
 * @type api
 * @valid since 3.32
 * @region 美声特效管理
 * @brief 设置变声特效类型
 * @param voiceChanger 变声特效类型，参看 ByteRTCVoiceChangerType{@link #ByteRTCVoiceChangerType}。
 * @return 方法调用结果：<br>
 *        + 0：成功；<br>
 *        + <0：失败。具体失败原因参看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus}。
 * @note  
 *        + 在进房前后都可设置。  <br>
 *        + 对 RTC SDK 内部采集的音频和自定义采集的音频都生效。 <br>
 *        + 只对单声道音频生效。<br>
 *        + 与 setVoiceReverbType:{@link #setVoiceReverbType:} 互斥，后设置的特效会覆盖先设置的特效。 
 */
/**
 * @locale en
 * @type api
 * @valid since 3.32
 * @brief Sets the type of voice change effect.
 * @param voiceChanger The sound change effect type. See ByteRTCVoiceChangerType{@link #ByteRTCVoiceChangerType}.
 * @return API call result:<br>
 *        + 0: Success.<br>
 *        + <0: Failure. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for specific reasons.
 * @note   
 *         + You can call it before and after entering the room. <br>
 *         + Effective for both internal and external audio source. <br>
 *         + Only valid for mono-channel audio. <br>
 *         + Mutually exclusive with setVoiceReverbType:{@link #setVoiceReverbType:}, and the effects set later will override the effects set first.
 */
- (int)setVoiceChangerType:(ByteRTCVoiceChangerType)voiceChanger;
/**
 * @locale zh
 * @type api
 * @valid since 3.32
 * @region 美声特效管理
 * @brief 设置混响特效类型
 * @param voiceReverb 混响特效类型，参看 ByteRTCVoiceReverbType{@link #ByteRTCVoiceReverbType}。
 * @return 方法调用结果：<br>
 *        + 0：成功；<br>
 *        + <0：失败。具体失败原因参看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus}。
 * @note  
 *        + 在进房前后都可设置。  <br>
 *        + 对 RTC SDK 内部采集的音频和自定义采集的音频都生效。 <br>
 *        + 只对单声道音频生效。<br>
 *        + 与 setVoiceChangerType:{@link #setVoiceChangerType:} 互斥，后设置的特效会覆盖先设置的特效。
 */
/**
 * @locale en
 * @type api
 * @valid since 3.32
 * @region Bel Sound Effect Management
 * @brief Sets the reverb effect type
 * @param voiceReverb Reverb effect type. See ByteRTCVoiceReverbType{@link #ByteRTCVoiceReverbType}.
 * @return API call result:<br>
 *        + 0: Success.<br>
 *        + <0: Failure. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for specific reasons.
 * @note   
 *         + You can call it before and after entering the room. <br>
 *         + Effective for both internal and external audio source. <br>
 *         + Only valid for mono-channel audio. <br>
 *         + Mutually exclusive with setVoiceChangerType:{@link #setVoiceChangerType:}, and the effects set later will override the effects set first.
 */
- (int)setVoiceReverbType:(ByteRTCVoiceReverbType)voiceReverb;
/**
 * @locale zh
 * @type api
 * @brief 设置本地采集语音的均衡效果。包含内部采集和外部采集，但不包含混音音频文件。
 * @param config 语音均衡效果，参看 ByteRTCVoiceEqualizationConfig{@link #ByteRTCVoiceEqualizationConfig}
 * @return  
 *        + 0： 成功。  <br>
 *        + < 0： 失败。
 * @note 根据奈奎斯特采样率，音频采样率必须大于等于设置的中心频率的两倍，否则，设置不生效。
 */
/**
 * @locale en
 * @type api
 * @brief Set the equalization effect for the local captured audio. The audio includes both internal captured audio and external captured voice, but not the mixing audio file.
 * @param config See ByteRTCVoiceEqualizationConfig{@link #ByteRTCVoiceEqualizationConfig}.
 * @return   
 *         + 0: Success. <br>
 *         + < 0: Failure.
 * @note According to the Nyquist acquisition rate, the audio acquisition rate must be greater than twice the set center frequency. Otherwise, the setting will not be effective.
 */
-(int)setLocalVoiceEqualization:(ByteRTCVoiceEqualizationConfig* _Nonnull)config;
/**
 * @locale zh
 * @type api
 * @brief 设置本地采集音频的混响效果。包含内部采集和外部采集，但不包含混音音频文件。
 * @param param 混响效果，参看 ByteRTCVoiceReverbConfig{@link #ByteRTCVoiceReverbConfig}
 * @return  
 *        + 0： 成功。  <br>
 *        + < 0： 失败。
 * @note 调用 enableLocalVoiceReverb:{@link #ByteRTCVideo#enableLocalVoiceReverb:} 开启混响效果。
 */
/**
 * @locale en
 * @type api
 * @brief Set the reverb effect for the local captured audio. The audio includes both internal captured audio and external captured voice, but not the mixing audio file.
 * @param param See ByteRTCVoiceReverbConfig{@link #ByteRTCVoiceReverbConfig}.
 * @return   
 *         + 0: Success. <br>
 *         + < 0: Failure.
 * @note Call enableLocalVoiceReverb:{@link #ByteRTCVideo#enableLocalVoiceReverb:} to enable the reverb effect.
 */
 -(int)setLocalVoiceReverbParam:(ByteRTCVoiceReverbConfig* _Nonnull)param;
/**
 * @locale zh
 * @type api
 * @brief 开启本地音效混响效果
 * @param enable 是否开启
 * @return  
 *        + 0： 成功。  <br>
 *        + < 0： 失败。
 * @note 调用 setLocalVoiceReverbParam:{@link #ByteRTCVideo#setLocalVoiceReverbParam:} 设置混响效果。
 */
/**
 * @locale en
 * @type api
 * @brief Enable the reverb effect for the local captured voice.
 * @param enable
 * @return   
 *         + 0: Success. <br>
 *         + < 0: Failure.
 * @note Call setLocalVoiceReverbParam:{@link #ByteRTCVideo#setLocalVoiceReverbParam:} to set the reverb effect.
 */
-(int)enableLocalVoiceReverb:(bool)enable;
/**
 * @locale zh
 * @valid since 3.58.1
 * @type api
 * @region 音量管理
 * @brief 设置是否将录音信号静音（不改变本端硬件）。
 * @param index 流索引，指定调节主流/屏幕流音量，参看 [StreamIndex](70083#streamindex-2)。
 * @param mute 是否静音音频采集。<br>
 *        + True：静音（关闭麦克风）<br>
 *        + False：（默认）开启麦克风
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。具体失败原因参看 ReturnStatus{@link #ReturnStatus}。
 * @note 
          + 该方法支持选择静音或取消静音麦克风采集，而不影响 SDK 音频流发布状态。<br>
          + 静音后通过 setCaptureVolume:volume:{@link #ByteRTCVideo#setCaptureVolume:volume:} 调整音量不会取消静音状态，音量状态会保存至取消静音。<br>
          + 调用 startAudioCapture{@link #ByteRTCVideo#startAudioCapture} 开启音频采集前后，都可以使用此接口设置采集音量。
 */
/**
 * @locale en
 * @valid since 3.58.1
 * @type api
 * @region Volume management
 * @brief Set whether to mute the recording signal (without changing the local hardware).
 * @param index Stream index, specifying the main stream or screen stream volume adjustment. See [StreamIndex](70083#streamindex-2).
 * @param mute Whether to mute audio capture.<br>
 *        + True: Mute (disable microphone) <br>
 *        + False: (Default) Enable microphone 
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Failure. See ReturnStatus{@link #ReturnStatus} for more details.
 * @note  
          + Calling this API does not affect the status of SDK audio stream publishing.<br>
          + Adjusting the volume by calling setCaptureVolume:volume:{@link #ByteRTCVideo#setCaptureVolume:volume:} after muting will not cancel the mute state. The volume state will be retained until unmuted.<br>
          + You can use this interface to set the capture volume before or after calling startAudioCapture{@link #ByteRTCVideo#startAudioCapture} to enable audio capture.
 */
- (int)muteAudioCapture:(ByteRTCStreamIndex)index mute:(bool)mute;
/**
 * @locale zh
 * @type api
 * @region 音频管理
 * @brief 调节音频采集音量
 * @param index 流索引，指定调节主流还是调节屏幕流的音量，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param volume 采集的音量值和原始音量的比值，范围是 [0, 400]，单位为 %，自带溢出保护。<br>
 *        为保证更好的通话质量，建议将 volume 值设为 [0,100]。<br>
 *       + 0：静音  <br>
 *       + 100：原始音量  <br>
 *       + 400: 最大可为原始音量的 4 倍(自带溢出保护)  
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note 在开启音频采集前后，你都可以使用此接口设定采集音量。
 */
/**
 * @locale en
 * @type api
 * @region Audio Management
 * @brief Adjusts the audio capture volume.
 * @param index Index of the stream, whose volume needs to be adjusted. Refer to ByteRTCStreamIndex{@link #ByteRTCStreamIndex} for more details.
 * @param volume Ratio of capture volume to original volume. Ranging: [0,400]. Unit: %<br>
 *        + 0: Mute <br>
 *        + 100: Original volume. To ensure the audio quality, we recommend [0, 100].<br>
 *        + 400: Four times the original volume with signal-clipping protection.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note  Call this API to set the volume of the audio capture before or during the audio capture.
 */
- (int)setCaptureVolume:(ByteRTCStreamIndex)index volume:(int)volume;
/**
 * @locale zh
 * @type api
 * @region 音量管理
 * @brief 调节本地播放的所有远端用户混音后的音量。<br>
 *        播放音频前或播放音频时，你都可以使用此接口设定播放音量。
 * @param volume 音频播放音量值和原始音量的比值，范围是 [0, 400]，单位为 %，自带溢出保护。  <br>
 *        为保证更好的通话质量，建议将 volume 值设为 [0,100]。  <br>
 *       + 0: 静音  <br>
 *       + 100: 原始音量  <br>
 *       + 400: 最大可为原始音量的 4 倍(自带溢出保护)  
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note 假设某远端用户 A 始终在被调节的目标用户范围内，当该方法与 setRemoteAudioPlaybackVolume:remoteUid:playVolume:{@link #ByteRTCVideo#setRemoteAudioPlaybackVolume:remoteUid:playVolume:} 或 setRemoteRoomAudioPlaybackVolume:{@link #ByteRTCRoom#setRemoteRoomAudioPlaybackVolume:} 共同使用时，本地收听用户 A 的音量将为两次设置的音量效果的叠加。
 */
/**
 * @locale en
 * @type api
 * @region volume management
 * @brief Adjusts the playback volume of the mixed remote audio.  You can call this API before or during the playback.
 * @param volume Ratio(%) of playback volume to original volume, in the range [0, 400], with overflow protection.  <br>
 *        To ensure the audio quality, we recommend setting the volume to `100`.  <br>
 *        + 0: mute <br>
 *        + 100: original volume <br>
 *        + 400: Four times the original volume with signal-clipping protection.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note Suppose a remote user A is always within the range of the target user whose playback volume will be adjusted, if you use both this method and setRemoteAudioPlaybackVolume:remoteUid:playVolume:{@link #ByteRTCVideo#setRemoteAudioPlaybackVolume:remoteUid:playVolume:}/setRemoteRoomAudioPlaybackVolume:{@link #ByteRTCRoom#setRemoteRoomAudioPlaybackVolume:}, the volume that the local user hears from user A is the overlay of both settings.
 */
- (int)setPlaybackVolume:(NSInteger)volume;
/**
 * @locale zh
 * @type api
 * @region 音频管理
 * @brief 启用音频信息提示。启用后，你可以收到 rtcEngine:onLocalAudioPropertiesReport:{@link #ByteRTCVideoDelegate#rtcEngine:onLocalAudioPropertiesReport:}，rtcEngine:onRemoteAudioPropertiesReport:totalRemoteVolume:{@link #ByteRTCVideoDelegate#rtcEngine:onRemoteAudioPropertiesReport:totalRemoteVolume:}，和 rtcEngine:onActiveSpeaker:uid:{@link #ByteRTCVideoDelegate#rtcEngine:onActiveSpeaker:uid:}。
 * @param config 详见 ByteRTCAudioPropertiesConfig{@link #ByteRTCAudioPropertiesConfig}  
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 */
/**
 * @locale en
 * @type api
 * @region Audio management
 * @brief Enables audio information prompts. After that, you will receive rtcEngine:onLocalAudioPropertiesReport:{@link #ByteRTCVideoDelegate#rtcEngine:onLocalAudioPropertiesReport:}, rtcEngine:onRemoteAudioPropertiesReport:totalRemoteVolume:{@link #ByteRTCVideoDelegate#rtcEngine:onRemoteAudioPropertiesReport:totalRemoteVolume:}, and rtcEngine:onActiveSpeaker:uid:{@link #ByteRTCVideoDelegate#rtcEngine:onActiveSpeaker:uid:}.
 * @param config See ByteRTCAudioPropertiesConfig{@link #ByteRTCAudioPropertiesConfig}.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 */
- (int)enableAudioPropertiesReport:(ByteRTCAudioPropertiesConfig* _Nonnull)config;
/**
 * @locale zh
 * @type api
 * @region 多房间
 * @brief 调节来自指定远端用户的音频播放音量。
 * @param roomID 音频来源用户所在的房间 ID
 * @param userID 音频来源的远端用户 ID
 * @param volume 音频播放音量值和原始音量的比值，范围是 [0, 400]，单位为 %，自带溢出保护。为保证更好的通话质量，建议将 volume 值设为 [0,100]。 <br>
 *              + 0: 静音  <br>
 *              + 100: 原始音量，默认值  <br>
 *              + 400: 最大可为原始音量的 4 倍(自带溢出保护)  
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note 假设某远端用户 A 始终在被调节的目标用户范围内，<br>
 *        + 当该方法与 setRemoteRoomAudioPlaybackVolume:{@link #ByteRTCRoom#setRemoteRoomAudioPlaybackVolume:} 共同使用时，本地收听用户 A 的音量为后调用的方法设置的音量；<br>
 *        + 当该方法与 setPlaybackVolume:{@link #ByteRTCVideo#setPlaybackVolume:} 方法共同使用时，本地收听用户 A 的音量将为两次设置的音量效果的叠加。
 */
/**
 * @locale en
 * @type api
 * @region  multi-room
 * @brief Adjusts the audio playback volume from the specified remote user.
 * @param roomID ID of the room from which the remote audio source is published.
 * @param userID The remote user ID of the audio source
 * @param volume Ratio(%) of playback volume to original volume, in the range [0, 400], with overflow protection.  <br>
 *               To ensure the audio quality, we recommend setting the volume within `100`.  <br>
 *               + 0: mute <br>
 *               + 100: original volume. Default value. <br>
 *               + 400: Up to 4 times the original volume (with overflow protection) 
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note Suppose a remote user A is always within the range of the target user whose playback volume will be adjusted,<br>
 *        + If you use both this method and setRemoteRoomAudioPlaybackVolume:{@link #ByteRTCRoom#setRemoteRoomAudioPlaybackVolume:}, the volume that the local user hears from user A is the volume set by the method called later.<br>
 *        + If you use both this method and setPlaybackVolume:{@link #ByteRTCVideo#setPlaybackVolume:}, the volume that the local user hears from user A is the overlay of both settings.
 */
- (int)setRemoteAudioPlaybackVolume:(NSString *_Nonnull)roomID
                           remoteUid:(NSString *_Nonnull)userID
                          playVolume:(NSInteger)volume;
/**
 * @locale zh
 * @type api
 * @region 音频管理
 * @brief 开启/关闭耳返功能。
 * @param mode 是否开启耳返功能，参看 ByteRTCEarMonitorMode{@link #ByteRTCEarMonitorMode}。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note 
 *        + 耳返功能仅适用于由 RTC SDK 内部采集的音频。  <br>
 *        + 使用耳返必须佩戴耳机。为保证低延时耳返最佳体验，建议佩戴有线耳机。  <br>
 *        + 对于 iOS，仅支持软件耳返功能。<br>
 *        + 对于 macOS，耳返功能仅支持设备通过 3.5mm 接口、USB 接口、或蓝牙方式直连耳机时可以使用。对于通过 HDMI 或 USB-C 接口连接显示器，再连接，或通过连接 OTG 外接声卡再连接的耳机，不支持耳返功能。
 */
/**
 * @locale en
 * @type api
 * @region Audio management
 * @brief Enables/Disables in-ear monitoring.
 * @param mode Whether or not in-ear monitoring is enabled. See ByteRTCEarMonitorMode{@link #ByteRTCEarMonitorMode}.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note  
 *         + In-ear monitoring is effective for audios captured by the RTC SDK.  <br>
 *         + We recommend that you use wired earbuds/headphones for a low-latency, high-resolution audio experience.  <br>
 *         + For iOS, you can only use SDK-level in-ear monitoring.<br>
 *         + For macOS, you can use ear monitoring feature when the earpiece is directly connected to the device by 3.5mm interface, USB interface, or BlueTooth. You cannot use ear monitoring feature when the earpiece is connected to a monitor via the HDMI or USB-C interface, and then connected to the device, or connected to an OTG external sound card, and then connected to the device.
 */
- (int)setEarMonitorMode:(ByteRTCEarMonitorMode)mode;
/**
 * @locale zh
 * @type api
 * @region 音频管理
 * @brief 设置耳返的音量。
 * @param volume 耳返的音量，取值范围：[0,100]，单位：%
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明。
 * @note 设置耳返音量前，你必须先调用 setEarMonitorMode:{@link #ByteRTCVideo#setEarMonitorMode:} 打开耳返功能。
 */
/**
 * @locale en
 * @type api
 * @region Audio Management
 * @brief Sets the in-ear monitoring volume.
 * @param volume The monitoring volume with the adjustment range between 0% and 100%.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details.
 * @note Call setEarMonitorMode:{@link #ByteRTCVideo#setEarMonitorMode:} before setting the volume.
 */
- (int)setEarMonitorVolume:(NSInteger)volume;
/**
 * @locale zh
 * @hidden(macOS)
 * @type api
 * @region 音频管理
 * @brief 在纯媒体音频场景下,切换 iOS 设备与耳机之间的蓝牙传输协议。
 * @param mode 蓝牙传输协议。详见 ByteRTCBluetoothMode{@link #ByteRTCBluetoothMode}。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note 以下场景你会收到 rtcEngine:onAudioDeviceWarning:deviceType:deviceWarning:{@link #ByteRTCVideoDelegate#rtcEngine:onAudioDeviceWarning:deviceType:deviceWarning:} 回调：1）当前不支持设置 HFP；2）非纯媒体音频场景，建议在调用此接口前调用 setAudioScenario:{@link #ByteRTCVideo#setAudioScenario:}设置纯媒体音频场景。
 */
/**
 * @locale en
 * @hidden(macOS)
 * @type api
 * @region Audio Management
 * @brief  On iOS, you can change the Bluetooth profile when the media volume is set in all scenarios.
 * @param mode The Bluetooth profiles. See ByteRTCBluetoothMode{@link #ByteRTCBluetoothMode}.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note You will receive rtcEngine:onAudioDeviceWarning:deviceType:deviceWarning:{@link #ByteRTCVideoDelegate#rtcEngine:onAudioDeviceWarning:deviceType:deviceWarning:} in the following scenarios: 1) You cannot change the Bluetooth profile to HFP.;2) The media volume is not set in all scenarios. We suggest that you call setAudioScenario:{@link #ByteRTCVideosetaudioscenario:} to set the media volume scenario before calling this API.
 */
- (int)setBluetoothMode:(ByteRTCBluetoothMode) mode;
/**
 * @locale zh
 * @type api
 * @region 混音
 * @brief 开启本地语音变调功能，多用于 K 歌场景。  <br>
 *        使用该方法，你可以对本地语音的音调进行升调或降调等调整。
 * @param pitch 相对于语音原始音调的升高/降低值，取值范围[-12，12]，默认值为 0，即不做调整。  <br>
 *        取值范围内每相邻两个值的音高距离相差半音，正值表示升调，负值表示降调，设置的绝对值越大表示音调升高或降低越多。  <br>
 *        超出取值范围则设置失败，并且会触发 rtcEngine:onWarning:{@link #ByteRTCVideoDelegate#rtcEngine:onWarning:} 回调，提示 ByteRTCWarningCode{@link #ByteRTCWarningCode} 错误码为 `WARNING_CODE_SET_SCREEN_STREAM_INVALID_VOICE_PITCH` 设置语音音调不合法
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 */
/**
 * @locale en
 * @type api
 * @region Audio Mixing
 * @brief Changes local voice to a different key, mostly used in Karaoke scenarios.  <br>
 *        You can adjust the pitch of local voice such as ascending or descending with this method.
 * @param pitch The value that is higher or lower than the original local voice within a range from -12 to 12. The default value is 0, i.e. no adjustment is made.  <br>
 *        The difference in pitch between two adjacent values within the value range is a semitone, with positive values indicating an ascending tone and negative values indicating a descending tone, and the larger the absolute value set, the more the pitch is raised or lowered.  <br>
 *        Out of the value range, the setting fails and triggers rtcEngine:onWarning:{@link #ByteRTCVideoDelegate#rtcEngine:onWarning:} callback, indicating `WARNING_CODE_SET_SCREEN_STREAM_INVALID_VOICE_PITCH` for invalid value setting with ByteRTCWarningCode{@link #ByteRTCWarningCode}.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 */
- (int)setLocalVoicePitch:(NSInteger)pitch;
/**
 * @locale zh
 * @type api
 * @region 音频管理
 * @brief 开启/关闭音量均衡功能。  <br>
 *        开启音量均衡功能后，人声的响度会调整为 -16lufs。如果已调用 setAudioMixingLoudness:loudness:{@link #ByteRTCAudioMixingManager#setAudioMixingLoudness:loudness:} 传入了混音音乐的原始响度，此音乐播放时，响度会调整为 -20lufs。
 * @param enable 是否开启音量均衡功能：  <br>
 *       + YES: 是  <br>
 *       + NO: 否
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note 该接口须在调用 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} 开始播放音频文件之前调用。
 */
/**
 * @locale en
 * @type api
 * @region Audio Management
 * @brief Enables/disables the loudness equalization function.  <br>
 *        If you call this API with the parameter set to True, the loudness of user's voice will be adjusted to -16lufs. If then you also call setAudioMixingLoudness:loudness:{@link #ByteRTCAudioMixingManager#setAudioMixingLoudness:loudness:} and import the original loudness of the audio data used in audio mixing, the loudness will be adjusted to -20lufs when the audio data starts to play.
 * @param enable Whether to enable loudness equalization function:  <br>
 *        + true: Yes <br>
 *        + false: No
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note You must call this API before starting to play the audio file with startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:}.
 */
- (int)enableVocalInstrumentBalance:(BOOL)enable;
/**
 * @locale zh
 * @type api
 * @region 音频管理
 * @brief 打开/关闭音量闪避功能，适用于在 RTC 通话过程中会同时播放短视频或音乐的场景，如“一起看”、“在线 KTV”等。  <br>
 *        开启该功能后，当检测到远端人声时，本地的媒体播放音量会自动减弱，从而保证远端人声的清晰可辨；当远端人声消失时，本地媒体音量会恢复到闪避前的音量水平。
 * @param enable 是否开启音量闪避：  <br>
 *        + YES: 是  <br>
 *        + NO: 否
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 */
/**
 * @locale en
 * @type api
 * @region Audio Management
 * @brief Enables/disables the playback ducking function. This function is usually used in scenarios where short videos or music will be played simultaneously during RTC calls.  <br>
 *        With the function on, if remote voice is detected, the local media volume will be lowered to ensure the clarity of the remote voice. If remote voice disappears, the local media volume restores.
 * @param enable Whether to enable playback ducking:  <br>
 *        + YES: Yes  <br>
 *        + NO: No
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 */
- (int)enablePlaybackDucking:(BOOL)enable;
#pragma mark Core Video Methods
// @name video core method
/**
 * @locale zh
 * @type api
 * @deprecated since 3.57, use setLocalVideoRender:withSink:withLocalRenderConfig:{@link #ByteRTCVideo#setLocalVideoRender:withSink:withLocalRenderConfig:} instead.
 * @region 自定义视频采集渲染
 * @brief 将本地视频流与自定义渲染器绑定。
 * @param index 视频流属性。采集的视频流/屏幕视频流，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param videoSink 自定义视频渲染器，参看 ByteRTCVideoSinkDelegate{@link #ByteRTCVideoSinkDelegate}
 * @param requiredFormat videoSink 适用的视频帧编码格式，参看 ByteRTCVideoSinkPixelFormat{@link #ByteRTCVideoSinkPixelFormat}
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note  
 *        + RTC SDK 默认使用 RTC SDK 自带的渲染器（内部渲染器）进行视频渲染。<br>
 *        + 如果需要解除绑定，必须将 videoSink 设置为 null。退房时将清除绑定状态。<br>
 *        + 一般在收到 rtcEngine:onFirstLocalVideoFrameCaptured:withFrameInfo:{@link #ByteRTCVideoDelegate#rtcEngine:onFirstLocalVideoFrameCaptured:withFrameInfo:} 回调通知完成本地视频首帧采集后，调用此方法为视频流绑定自定义渲染器；然后加入房间。<br>
 *        + 本方法获取的是前处理后的视频帧，如需获取其他位置的视频帧（如采集后的视频帧），请调用 setLocalVideoRender:withSink:withLocalRenderConfig:{@link #ByteRTCVideo#setLocalVideoRender:withSink:withLocalRenderConfig:}。
 */
/**
 * @locale en
 * @type api
 * @region Custom Video Capturing & Rendering
 * @brief Binds the local video stream to a custom renderer.
 * @param index Video stream type. See ByteRTCStreamIndex{@link #ByteRTCStreamIndex}.
 * @param videoSink Custom video renderer. See ByteRTCVideoSinkDelegate{@link #ByteRTCVideoSinkDelegate}.
 * @param requiredFormat Video frame encoding format that applys to custom rendering. See ByteRTCVideoSinkPixelFormat{@link #ByteRTCVideoSinkPixelFormat}.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note  
 *        + RTC SDK uses its own renderer (internal renderer) for video rendering by default.  <br>
 *        + If you need to unbind the video stream from the custom render, you must set videoSink to `null`. The binding status will be cleared when you leave room.  <br>
 *        + You should call this API before joining the room, and after receiving rtcEngine:onFirstLocalVideoFrameCaptured:withFrameInfo:{@link #ByteRTCVideoDelegate#rtcEngine:onFirstLocalVideoFrameCaptured:withFrameInfo:} which reports that the first local video frame has been successfully captured.<br>
 *        + This method gets video frames that have undergone preprocessing. If you need to obtain video frames from other positions, such as after capture, you should call setLocalVideoRender:withSink:withLocalRenderConfig:{@link #ByteRTCVideo#setLocalVideoRender:withSink:withLocalRenderConfig:} instead.
 */
- (int)setLocalVideoSink:(ByteRTCStreamIndex)index
                withSink:(id<ByteRTCVideoSinkDelegate> _Nullable)videoSink
         withPixelFormat:(ByteRTCVideoSinkPixelFormat)requiredFormat NS_SWIFT_NAME(setLocalVideoSink(_:withSink:withPixelFormat:));

/**
 * @locale zh
 * @valid since 3.57
 * @type api
 * @region 自定义视频帧回调
 * @brief 将本地视频流与自定义渲染器绑定。你可以通过参数设置返回指定位置和格式的视频帧数据。
 * @param index 视频流属性。采集的视频流/屏幕视频流，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}。
 * @param videoSink 自定义视频渲染器，参看 ByteRTCVideoSinkDelegate{@link #ByteRTCVideoSinkDelegate}。
 * @param config 本地视频帧回调配置，参看 ByteRTCLocalVideoSinkConfig{@link #ByteRTCLocalVideoSinkConfig}。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0: 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明。
 * @note  
 *        + RTC SDK 默认使用自带的渲染器（内部渲染器）进行视频渲染。<br>
 *        + 退房时将清除绑定状态。<br>
 *        + 如果需要解除绑定，你必须将 videoSink 设置为 null。<br>
 *        + 一般在收到 rtcEngine:onFirstLocalVideoFrameCaptured:withFrameInfo:{@link #ByteRTCVideoDelegate#rtcEngine:onFirstLocalVideoFrameCaptured:withFrameInfo:} 回调通知完成本地视频首帧采集后，调用此方法为视频流绑定自定义渲染器；然后加入房间。
 */
/**
 * @locale en
 * @valid since 3.55
 * @type api
 * @region Custom Video frame callback
 * @brief Binds the local video stream to a custom renderer. You can set the position and format of the obtained video frame.
 * @param index Video stream type. See ByteRTCStreamIndex{@link #ByteRTCStreamIndex}.
 * @param videoSink Custom video renderer. See ByteRTCVideoSinkDelegate{@link #ByteRTCVideoSinkDelegate}.
 * @param config Video frame callback config. See ByteRTCLocalVideoSinkConfig{@link #ByteRTCLocalVideoSinkConfig}.
 * @return  
 *        + 0: Success.<br>
 *        + < 0: Failure. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details.
 * @note  
 *        + RTC SDK uses its own renderer (internal renderer) for video rendering by default.<br>
 *        + The binding state will be reset when you leave the room.<br>
 *        + If you need to unbind the video stream from the custom render, set videoSink to `null`.<br>
 *        + You should call this API before joining the room, and after receiving rtcEngine:onFirstLocalVideoFrameCaptured:withFrameInfo:{@link #ByteRTCVideoDelegate#rtcEngine:onFirstLocalVideoFrameCaptured:withFrameInfo:} which reports that the first local video frame has been successfully captured.
 */
- (int)setLocalVideoRender:(ByteRTCStreamIndex)index
                withSink:(id<ByteRTCVideoSinkDelegate> _Nullable)videoSink
         withLocalRenderConfig:(ByteRTCLocalVideoSinkConfig*)config NS_SWIFT_NAME(setLocalVideoRender(_:withSink:withLocalRenderConfig:));

/**
 * @locale zh
 * @type api
 * @deprecated since 3.57, use setRemoteVideoRender:withSink:withRemoteRenderConfig:{@link #ByteRTCVideo#setRemoteVideoRender:withSink:withRemoteRenderConfig:} instead.
 * @region 自定义视频采集渲染
 * @brief 将远端视频流与自定义渲染器绑定。
 * @param streamKey 远端流信息，用于指定需要渲染的视频流来源及属性，参看 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
 * @param videoSink 自定义视频渲染器，参看 ByteRTCVideoSinkDelegate{@link #ByteRTCVideoSinkDelegate}
 * @param requiredFormat videoSink 适用的视频帧编码格式，参看 ByteRTCVideoSinkPixelFormat{@link #ByteRTCVideoSinkPixelFormat}
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note  
 *        + RTC SDK 默认使用 RTC SDK 自带的渲染器（内部渲染器）进行视频渲染。<br>
 *        + 该方法进房前后均可以调用。若想在进房前调用，你需要在加入房间前获取远端流信息；若无法预先获取远端流信息，你可以在加入房间并通过 rtcRoom:onUserPublishStream:type:{@link #ByteRTCRoomDelegate#rtcRoom:onUserPublishStream:type:} 回调获取到远端流信息之后，再调用该方法。<br>
 *        + 如果需要解除绑定，必须将 videoSink 设置为 null。退房时将清除绑定状态。<br>
 *        + 本方法获取的是后处理后的视频帧，如需获取其他位置的视频帧（如解码后的视频帧），请调用 setRemoteVideoRender:withSink:withRemoteRenderConfig:{@link #ByteRTCVideo#setRemoteVideoRender:withSink:withRemoteRenderConfig:}。
 */
/**
 * @locale en
 * @type api
 * @region Custom Video Capturing & Rendering
 * @brief Binds the remote video stream to a custom renderer.
 * @param streamKey Remote stream information which specifys the source and type of the video stream to be rendered. See ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
 * @param videoSink Custom video renderer. See ByteRTCVideoSinkDelegate{@link #ByteRTCVideoSinkDelegate}.
 * @param requiredFormat Encoding format that applys to the custom renderer. See ByteRTCVideoSinkPixelFormat{@link #ByteRTCVideoSinkPixelFormat}.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note  
 *        + RTC SDK uses its own renderer (internal renderer) for video rendering by default.  <br>
 *        + Joining or leaving the room will not affect the binding state. <br>
 *        + This API can be called before and after entering the room. To call before entering the room, you need to get the remote stream information before joining the room; if you cannot get the remote stream information in advance, you can call the API after joining the room and getting the remote stream information through rtcRoom:onUserPublishStream:type:{@link #ByteRTCRoomDelegate#rtcRoom:onUserPublishStream:type:}.<br>
 *        + If you need to unbind the remote stream from the renderer, you must set videoSink to null.
 */
- (int)setRemoteVideoSink:(ByteRTCRemoteStreamKey* _Nonnull)streamKey
                withSink:(id<ByteRTCVideoSinkDelegate> _Nullable)videoSink
         withPixelFormat:(ByteRTCVideoSinkPixelFormat)requiredFormat NS_SWIFT_NAME(setRemoteVideoSink(_:withSink:withPixelFormat:));

/**
 * @locale zh
 * @valid since 3.57
 * @type api
 * @region 自定义视频帧回调
 * @brief 将远端视频流与自定义渲染器绑定。你可以通过参数设置返回指定位置和格式的视频帧数据。
 * @param streamKey 远端流信息，用于指定需要渲染的视频流来源及属性，参看 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}。
 * @param videoSink 自定义视频渲染器，参看 ByteRTCVideoSinkDelegate{@link #ByteRTCVideoSinkDelegate}。
 * @param config 远端视频帧回调配置，参看 ByteRTCRemoteVideoSinkConfig{@link #ByteRTCRemoteVideoSinkConfig}
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0: 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明。
 * @note  
 *        + RTC SDK 默认使用自带的渲染器（内部渲染器）进行视频渲染。<br>
 *        + 该方法进房前后均可以调用。若想在进房前调用，你需要在加入房间前获取远端流信息；若无法预先获取远端流信息，你可以在加入房间并通过 rtcRoom:onUserPublishStream:type:{@link #ByteRTCRoomDelegate#rtcRoom:onUserPublishStream:type:} 回调获取到远端流信息之后，再调用该方法。<br>
 *        + 退房时将清除绑定状态。<br>
 *        + 如果需要解除绑定，你必须将 videoSink 设置为 null。
 */
/**
 * @locale en
 * @hidden currently not available
 * @type api
 * @region Custom Video Capturing & Rendering
 * @brief Binds the remote video stream to a custom renderer.
 * @param streamKey Remote stream information which specifys the source and type of the video stream to be rendered. See ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
 * @param videoSink Custom video renderer. See ByteRTCVideoSinkDelegate{@link #ByteRTCVideoSinkDelegate}.
 * @param requiredFormat Encoding format that applys to the custom renderer. See ByteRTCVideoSinkPixelFormat{@link #ByteRTCVideoSinkPixelFormat}.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note  
 *        + RTC SDK uses its own renderer (internal renderer) for video rendering by default.  <br>
 *        + Joining or leaving the room will not affect the binding state. <br>
 *        + This API can be called before and after entering the room. To call before entering the room, you need to get the remote stream information before joining the room; if you cannot get the remote stream information in advance, you can call the API after joining the room and getting the remote stream information through rtcRoom:onUserPublishStream:type:{@link #ByteRTCRoomDelegate#rtcRoom:onUserPublishStream:type:}.<br>
 *        + If you need to unbind the remote stream from the renderer, you must set videoSink to null.
 */
- (int)setRemoteVideoRender:(ByteRTCRemoteStreamKey* _Nonnull)streamKey
                 withSink:(id<ByteRTCVideoSinkDelegate> _Nullable)videoSink
          withRemoteRenderConfig:(ByteRTCRemoteVideoSinkConfig*)config NS_SWIFT_NAME(setRemoteVideoRender(_:withSink:withRemoteRenderConfig:));

/**
 * @locale zh
 * @hidden(macOS)
 * @valid since 3.54
 * @type api
 * @region 音视频处理
 * @brief 设置远端视频超分模式。
 * @param streamKey 远端流信息，用于指定需要设置超分的视频流来源及属性，参看 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}。
 * @param mode 超分模式，参看 ByteRTCVideoSuperResolutionMode{@link #ByteRTCVideoSuperResolutionMode}。
 * @return 
 *        + 0: ByteRTCReturnStatusSuccess，SDK 调用成功，并不代表超分模式实际状态，需要根据回调 rtcEngine:onRemoteVideoSuperResolutionModeChanged:withMode:withReason:{@link #ByteRTCVideoDelegate#rtcEngine:onRemoteVideoSuperResolutionModeChanged:withMode:withReason:} 判断实际状态。<br>
 *        + -1: ByteRTCReturnStatusNativeInValid，native library 未加载。<br>
 *        + -2: ByteRTCReturnStatusParameterErr，参数非法，指针为空或字符串为空。<br>
 *        + -9: ByteRTCReturnStatusScreenNotSupport，不支持对屏幕流开启超分。<br>
 *        其他错误码参看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus}。
 * @note 
 *        + 如需使用该功能，需集成超分插件 ByteRTCVideoSRExtension.xcframework 及依赖库 bmf_mods_shared.xcframework，详情参看[按需集成插件](1108726)文档。<br>
 *        + 该方法须进房后调用。<br>
 *        + 远端用户视频流的原始分辨率不能超过 640 × 360 px。<br>
 *        + 支持对一路远端流开启超分，不支持对多路流开启超分。
 */
/**
 * @locale en
 * @hidden not available
 * @type api
 * @region Audio & Video Processing
 * @brief Sets the super resolution mode for remote video stream.
 * @param streamKey Remote stream information that specifies the source and type of the video stream. See ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}.
 * @param mode Super resolution mode. See ByteRTCVideoSuperResolutionMode{@link #ByteRTCVideoSuperResolutionMode}.
 * @return. <br>
 *        + 0: ByteRTCReturnStatusSuccess. It does not indicate the actual status of the super resolution mode, you should refer to rtcEngine:onRemoteVideoSuperResolutionModeChanged:withMode:withReason:{@link #ByteRTCVideoDelegate#rtcEngine:onRemoteVideoSuperResolutionModeChanged:withMode:withReason:} callback.<br>
 *        + -1: ByteRTCReturnStatusNativeInValid. Native library is not loaded.<br>
 *        + -2: ByteRTCReturnStatusParameterErr. Invalid parameter.<br>
 *        + -9: ByteRTCReturnStatusScreenNotSupport. Failure. Screen stream is not supported.<br>
 *        See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more return value indications.
 * @note 
 *        + Call this API after joining room.<br>
 *        + The original resolution of the remote video stream should not exceed 640 × 360 pixels.<br>
 *        + You can only turn on super-resolution mode for one stream.
 */
- (int)setRemoteVideoSuperResolution:(ByteRTCRemoteStreamKey* _Nonnull)streamKey
                                            withMode:(ByteRTCVideoSuperResolutionMode)mode;

/**
 * @locale zh
 * @hidden(macOS)
 * @valid since 3.54
 * @type api
 * @region 音视频处理
 * @brief 设置视频降噪模式。
 * @param mode 视频降噪模式。参看 ByteRTCVideoDenoiseMode{@link #ByteRTCVideoDenoiseMode}。
 * @return 
 *        + 0: API 调用成功。 用户可以根据回调函数 rtcEngine:onVideoDenoiseModeChanged:withReason:{@link #ByteRTCVideoDelegate#rtcEngine:onVideoDenoiseModeChanged:withReason:} 判断视频降噪是否开启。<br>
 *        + < 0: API 调用失败。
 * @note 如需使用该功能，需集成降噪插件 ByteRTCVideoDenoiseExtension.xcframework 及依赖库 bmf_mods_shared.xcframework，详情参看[按需集成插件](1108726)文档。
 */
/**
 * @locale en
 * @hidden not available
 * @type api
 * @region Audio & Video Processing
 * @brief Sets the video noise reduction mode.
 * @param mode Video noise reduction mode. Refer to ByteRTCVideoDenoiseMode{@link #ByteRTCVideoDenoiseMode} for more details.
 * @return 
 *        + 0: Success. Please refer to rtcEngine:onVideoDenoiseModeChanged:withReason:{@link #ByteRTCVideoDelegate#rtcEngine:onVideoDenoiseModeChanged:withReason:} callback for the actual state of video noise reduction mode.<br>
 *        + < 0: Failure.
 */
- (int)setVideoDenoiser:(ByteRTCVideoDenoiseMode)mode;

/**
 * @locale zh
 * @valid since 3.57
 * @hidden(iOS)
 * @type api
 * @region 音视频处理
 * @brief 设置视频暗光增强模式。<br>
 *        对于光线不足、照明不均匀或背光等场景下推荐开启，可有效改善画面质量。
 * @param mode 默认不开启。参看 ByteRTCVideoEnhancementMode{@link #ByteRTCVideoEnhancementMode}。
 * @return 
 *        + 0: API 调用成功。会立即生效，但需要等待下载和检测完成后才能看到增强后的效果。<br>
 *        + < 0: API 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明。
 * @note 
 *        + 开启后会影响设备性能，应根据实际需求和设备性能决定是否开启。<br>
 *        + 对 RTC SDK 内部采集的视频和自定义采集的视频都生效。
 */
/**
 * @locale en
 * @valid since 3.57
 * @hidden(iOS)
 * @type api
 * @region Audio & Video Processing
 * @brief Sets the video lowlight enhancement mode.<br>
 *        It can significantly improve image quality in scenarios with insufficient light, contrast lighting, or backlit situations.
 * @param mode It defaults to Disable. Refer to ByteRTCVideoEnhancementMode{@link #ByteRTCVideoEnhancementMode} for more details.
 * @return 
 *        + 0: Success. The RTC SDK takes immediate action, yet it may require some time for downloads and detection processes before you can see the enhancement.<br>
 *        + < 0: Failure. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details.
 * @note 
 *        + Turning on this mode will impact device performance. This feature should be activated only when required and the device performance is adequate.<br>
 *        + Functionality applies to videos captured by the internal module as well as those from custom collections.
 */
- (int)setLowLightAdjusted:(ByteRTCVideoEnhancementMode)mode;

/**
 * @locale zh
 * @deprecated since 3.37 and will be deleted in 3.51, use setVideoEncoderConfig:{@link #ByteRTCVideo#setVideoEncoderConfig:} instead.
 * @type api
 * @region 视频管理
 * @brief 设置推送多路流时的各路视频参数，包括分辨率、帧率、码率、缩放模式、网络不佳时的回退策略等。
 * @param streamIndex 视频流属性，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}。
 * @param videoSolutions 要推送的多路视频流参数，参看 ByteRTCVideoSolution{@link #ByteRTCVideoSolution}。 <br>
 *                       最多支持 4 路参数。当设置了多路参数时，分辨率必须是从大到小排列。 <br>
 *                       最大分辨率为 4096px × 4096px，超过或设置的分辨率无法编码时，会导致编码推流失败。
 * @return  
 *        + 0：成功  <br>
 *        + !0：失败  
 * @note  
 *       + 该接口已废弃，请使用同名新接口代替；若仍需使用该旧接口，请注意无需先调用 `enableSimulcastMode` 开启推送多路流模式。<br>
 *       + 当使用内部采集时，视频采集的分辨率、帧率会根据最大的编码分辨率、帧率进行适配<br>
 *       + 默认的视频编码参数为：分辨率 640px × 360px，帧率 15fps。<br>
 *       + 变更编码分辨率后马上生效，可能会引发相机重启。<br>
 *       + 屏幕流只取视频参数数组的第一组数据。
 */
/**
 * @locale en
 * @deprecated since 3.45 and will be deleted in 3.51, use setVideoEncoderConfig:{@link #ByteRTCVideo#setVideoEncoderConfig:} instead.
 * @type api
 * @region Video management
 * @brief  Sets the video encoder configuration of each individual stream for simulcasting, including resolution, frame rate, bitrate, scale mode, fallback strategy under poor network conditions, etc.
 * @param  Stream type. See ByteRTCStreamIndex{@link #ByteRTCStreamIndex}.
 * @param videoSolutions Video parameters of each individual stream for simulcasting. See ByteRTCVideoSolution{@link #ByteRTCVideoSolution}. <br>
 *                        The length of `videoSolutions` is no more than 4. The resolutions must be in descending sort. <br>
 *                        The maximum resolution is 4096px × 4096px. If the resolution exceeds the limit or the video cannot be encoded, the simulcasting will fail.
 * @return   
 *         + 0: Success <br>
 *         +! 0: Failure 
 * @note   
 *        + When using the internal capture, the resolution and frame rate will be adapted to the maximum resolution and frame rate for encoding. <br>
 *        + The video streams are encoded by default with resolution of 640px × 360px and frame rate of 15fps. <br>
 *        + When you call this API, it will take effect immediately, which may cause the camera to restart. <br>
 *        + The screen stream takes the first set of parameters.
 */
- (int)setVideoEncoderConfig:(ByteRTCStreamIndex)streamIndex config:(NSArray <ByteRTCVideoSolution *> * _Nullable)videoSolutions __deprecated_msg("Will be removed in new version");
/**
 * @locale zh
 * @type api
 * @brief 设置本端采集的视频帧的旋转角度。<br>
 *        当摄像头倒置或者倾斜安装时，可调用本接口进行调整。对于手机等普通设备，可调用 setVideoRotationMode:{@link #ByteRTCVideo#setVideoRotationMode:} 实现旋转。
 * @param rotation 相机朝向角度，默认为 `ByteRTCVideoRotation0`，无旋转角度。详见 ByteRTCVideoRotation{@link #ByteRTCVideoRotation}。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note  
 *        + 对于内部采集的视频画面，如果已调用 setVideoRotationMode:{@link #ByteRTCVideo#setVideoRotationMode:} 设置了旋转方向，会在此基础上叠加旋转角度。<br>
 *        + 调用本接口也将对自定义采集视频画面生效，在原有的旋转角度基础上叠加本次设置。<br>
 *        + 视频贴纸特效或通过 enableVirtualBackground{@link #ByteRTCVideoEffect#enableVirtualBackground:withSource:} 增加的虚拟背景，也会跟随本接口的设置进行旋转。<br>
 *        + 本地渲染视频和发送到远端的视频都会相应旋转，但不会应用到单流转推中。如果希望在单流转推的视频中应用旋转，调用 setVideoOrientation:{@link #ByteRTCVideo#setVideoOrientation:}。
 */
/**
 * @locale en
 * @type api
 * @brief Set the rotation of the video images captured from the local device.<br>
 *        Call this API to rotate the videos when the camera is fixed upside down or tilted. For rotating videos on a phone, we recommend to use setVideoRotationMode:{@link #ByteRTCVideo#setVideoRotationMode:}.
 * @param rotation It defaults to `ByteRTCVideoRotation0`, which means not to rotate. Refer to ByteRTCVideoRotation{@link #ByteRTCVideoRotation}.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note 
 *        + For the videos captured by the internal module, the rotation will be combined with that set by calling setVideoRotationMode:{@link #ByteRTCVideo#setVideoRotationMode:}.<br>
 *        + This API affects the external-sourced videos. The final rotation would be the original rotation angles adding up with the rotation set by calling this API.<br>
 *        + The elements added during the video pre-processing stage, such as video sticker and background applied using enableVirtualBackground{@link #ByteRTCVideoEffect#enableVirtualBackground:withSource:} will also be rotated by this API.<br>
 *        + The rotation would be applied to both locally rendered video s and those sent out. However, if you need to rotate a video which is intended for pushing to CDN individually, use setVideoOrientation:{@link #ByteRTCVideo#setVideoOrientation:}.
 */
- (int)setVideoCaptureRotation:(ByteRTCVideoRotation)rotation;
/**
 * @locale zh
 * @type api
 * @region 视频管理
 * @brief 该方法设置视频流发布端是否开启发布多路编码参数不同的视频流的模式。
 * @param enabled 是否开启推送多路视频流模式： <br>
 *        + YES：开启 <br>
 *        + NO：关闭（默认）
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note 
 *        + 你应在进房前或进房后但未发布流时，调用此方法。  <br>
 *        + 开启推送多路流后，不能动态关闭，也不能更新多路流的路数和编码参数。  <br>
 *        + 开启推送多路视频流模式后，你可以在发布流前调用 setVideoEncoderConfig:{@link #ByteRTCVideo#setVideoEncoderConfig:} 为多路视频流分别设置编码参数。  <br>
 *        + 该功能关闭时，或该功能开启但未设置多路流参数时，默认只发一路视频流，该流的编码参数为：分辨率 640px × 360px，帧率 15fps。
 */
/**
 * @locale en
 * @type api
 * @region Video Management
 * @brief Enables/Disables the mode of publishing multiple video streams with different encoding configuration.
 * @param enabled Whether to enable the mode of publishing multiple video streams:  <br>
 *        + YES: Yes  <br>
 *        + NO: No(Default setting)
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note 
 *        + You should call this API  <br>
 *            - before entering the room, or  <br>
 *            - after entering the room but before publishing streams  <br>
 *        + When the simulcast mode is turned on, it cannot be turned off dynamically, nor can the parameters for video encoding be updated.  <br>
 *        + After setting this API to "True", you can call setVideoEncoderConfig:{@link #ByteRTCVideo#setVideoEncoderConfig:} to set encoding configuration for each stream before you publish stream.  <br>
 *        + If this function is off, or if this function is on but you don't set the configuration of any stream, only one stream will be sent with a resolution of 640px × 360px and a frame rate of 15fps.
 */
- (int) enableSimulcastMode:(BOOL) enabled;
/**
 * @locale zh
 * @type api
 * @region 视频管理
 * @brief 视频发布端设置期望发布的最大分辨率视频流参数，包括分辨率、帧率、码率、网络不佳时的回退策略等。  <br>
 *        该接口支持设置一路视频流参数，设置多路参数请使用 setVideoEncoderConfig:{@link #ByteRTCVideo#setVideoEncoderConfig:}。
 * @param encoderConfig 期望发布的最大分辨率视频流参数。参看 ByteRTCVideoEncoderConfig{@link #ByteRTCVideoEncoderConfig}。
 * @return 方法调用结果： <br>
 *        + 0：成功  <br>
 *        + !0：失败  
 * @note  
 *        + 你可以同时使用 enableSimulcastMode:{@link #ByteRTCVideo#enableSimulcastMode:} 方法来发布多路分辨率不同的流。具体而言，若期望发布多路不同分辨率的流，你需要在发布流之前调用本方法以及 enableSimulcastMode:{@link #ByteRTCVideo#enableSimulcastMode:} 方法开启多路流模式，SDK 会根据订阅端的设置智能调整发布的流数（最多发布 4 条）以及各路流的参数。其中，调用本方法设置的分辨率为各路流中的最大分辨率。具体规则参看[推送多路流](https://www.volcengine.com/docs/6348/70139)文档。<br>
 *        + 调用该方法前，SDK 默认仅发布一条分辨率为 640px × 360px，帧率为 15fps 的视频流。  <br>
 *        + 自定义采集的场景下，务必调用该接口设置分辨率，以保证远端收到画面的完整性。<br>
 *        + 该方法适用于摄像头采集的视频流，设置屏幕共享视频流参数参看 setScreenVideoEncoderConfig:{@link #ByteRTCVideo#setScreenVideoEncoderConfig:}。
 */
/**
 * @locale en
 * @type api
 * @region Video Management
 * @brief Video publisher call this API to set the parameters of the maximum resolution video stream that is expected to be published, including resolution, frame rate, bitrate, and fallback strategy in poor network conditions.<br>
 *        You can only set configuration for one stream with this API. If you want to set configuration for multiple streams, Call setVideoEncoderConfig:{@link #ByteRTCVideo#setVideoEncoderConfig:}.
 * @param encoderConfig The maximum video encoding parameter. See ByteRTCVideoEncoderConfig{@link #ByteRTCVideoEncoderConfig}.
 * @return  API call result: <br>
 *        + 0: Success <br>
 *        + ! 0: Failure 
 * @note  
 *        + You can use enableSimulcastMode:{@link #ByteRTCVideo#enableSimulcastMode:} simultaneously to publish streams with different resolutions. Specifically, if you want to publish multiple streams with different resolutions, you need to call this method and enable the simulcast mode with enableSimulcastMode:{@link #ByteRTCVideo#enableSimulcastMode:} before publishing your streams. The SDK will intelligently adjust the number of streams to be published (up to 4) and their parameters based on the settings of the subscribing end. The resolution set by calling this method will be the maximum resolution among the streams. For specific rules, please refer to [Simulcasting](https://docs.byteplus.com/en/byteplus-rtc/docs/70139).<br>
 *        + Without calling this API, SDK will only publish one stream for you with a resolution of 640px × 360px and a frame rate of 15fps.  <br>
 *        + In custom capturing, you must call this API to set the encoding parameters to ensure the integrity of the picture received by remote users. <br>
 *        + This API is applicable to the video stream captured by the camera, see setScreenVideoEncoderConfig:{@link #ByteRTCVideo#setScreenVideoEncoderConfig:} for setting parameters for screen sharing video stream.
 */
- (int)setMaxVideoEncoderConfig:(ByteRTCVideoEncoderConfig * _Nullable) encoderConfig;
/**
 * @locale zh
 * @hidden currently not available
 * @brief iOS 和 Mac 不支持 Fov，对齐其他端预留接口。
 */
/**
 * @locale en
 * @hidden currently not available
 */
- (int)setVideoEncoderConfig:(ByteRTCVideoEncoderConfig * _Nullable) encoderConfig withParameters:(NSDictionary * _Nullable) parameters;
/**
 * @locale zh
 * @type api
 * @region 视频管理
 * @brief 视频发布端设置推送多路流时各路流的参数，包括分辨率、帧率、码率、网络不佳时的回退策略等。
 * @param encoderConfigs 要推送的多路视频流的参数，最多支持设置 3 路参数，超过 3 路时默认取前 3 路的值。  <br>
 *        当设置了多路参数时，分辨率和帧率必须是从大到小排列。需注意，所设置的分辨率是各路流的最大分辨率。参看 ByteRTCVideoEncoderConfig{@link #ByteRTCVideoEncoderConfig}。
 * @return 方法调用结果： <br>
 *        + 0：成功  <br>
 *        + !0：失败  
 * @note  
 *        + 该方法设置的多路参数是否均生效，取决于是否同时调用了 enableSimulcastMode:{@link #ByteRTCVideo#enableSimulcastMode:} 开启发布多路参数不同的视频流模式。若未开启推送多路流模式，但调用本方法设置了多个分辨率，SDK 则默认发布设置的第一条流，多个分辨率的设置会在开启推送多路流模式之后生效。  <br>
 *        + 若期望推送多路不同分辨率的流，你需要在发布流之前调用本方法以及 enableSimulcastMode:{@link #ByteRTCVideo#enableSimulcastMode:} 方法。<br>
 *        + 开启推送多路流后，不能动态关闭，也不能更新多路流的路数和编码参数。  <br>
 *        + 调用该方法设置多路视频流参数前，SDK 默认仅发布一条分辨率为 640px × 360px，帧率为 15fps 的视频流。  <br>
 *        + 调用该方法设置分辨率不同的多条流后，SDK 会根据订阅端设置的期望订阅参数自动匹配发送的流，具体规则参看[推送多路流](https://www.volcengine.com/docs/6348/70139)文档。  <br>
 *        + 该方法适用于摄像头采集的视频流，设置屏幕共享视频流参数参看 setScreenVideoEncoderConfig:{@link #ByteRTCVideo#setScreenVideoEncoderConfig:}。
 */
/**
 * @locale en
 * @type api
 * @region Video Management
 * @brief Video publisher call this API to set the configurations of each stream published, including resolution, frame rate, bitrate, and fallback strategy in poor network conditions.
 * @param encoderConfig List of configurations for multiple streams. You can set parameters for up to 3 streams, SDK will always take the value of the first 3 streams when parameters for more streams are set.<br>
 *        The resolution you set is the maximum resolution of each stream, and must be arranged in descending order. The frame rates must be arranged in descending order. See ByteRTCVideoEncoderConfig{@link #ByteRTCVideoEncoderConfig}.
 * @return  API call result: <br>
 *        + 0: Success <br>
 *        + ! 0: Failure 
 * @note  
 *        + If you call this API after enabling the mode of publishing multiple streams with enableSimulcastMode:{@link #ByteRTCVideo#enableSimulcastMode:}, SDK will publish streams as you set, otherwise the SDK by default publishes the first stream that you have set. <br>
 *        + If you want to publish multiple streams with different resolutions, you need to call this method and enableSimulcastMode:{@link #ByteRTCVideo#enableSimulcastMode:}.<br>
 *        + When the simulcast mode is turned on, it cannot be turned off dynamically, nor can the parameters for video encoding be updated.  <br>
 *        + Without calling this API to set parameters for multiple video streams, the SDK only publishes one video stream with a resolution of 640px × 360px and a frame rate of 15fps.  <br>
 *        + After setting parameters for multiple video streams, SDK will automatically match the streams to be published based on the desired subscription parameters set by subscribers.  <br>
 *        + This API is applicable to the video stream captured by the camera, see setScreenVideoEncoderConfig:{@link #ByteRTCVideo#setScreenVideoEncoderConfig:} for setting parameters for screen sharing video stream.
 */
-(int)setVideoEncoderConfig:(NSArray <ByteRTCVideoEncoderConfig *> * _Nullable) encoderConfigs;

/**
 * @locale zh
 * @type api
 * @region 屏幕共享
 * @brief 为发布的屏幕共享视频流设置期望的编码参数，包括分辨率、帧率、码率、网络不佳时的回退策略等。
 * @param encoderConfig 屏幕共享视频流参数。参看 ByteRTCScreenVideoEncoderConfig{@link #ByteRTCScreenVideoEncoderConfig}。
 * @return  
 *         + 0：成功。  <br>
 *         + !0：失败。  
 * @note 
 *      + 该方法需在 publishScreen:{@link #ByteRTCRoom#publishScreen:} 发布屏幕共享流之前调用，之后调用不生效。<br>
 *      + 建议在采集视频前设置编码参数。若采集前未设置编码参数，则使用默认编码参数: 分辨率 1920px × 1080px，帧率 15fps。
 */
/**
 * @locale en
 * @type api
 * @region Screen Sharing
 * @brief Set the encoding configuration for shared-screen streams, including the resolution, frame rate, bitrate, and fallback strategies under challenging network conditions.
 * @param encoderConfig The encoding configuration for shared-screen streams. See ByteRTCScreenVideoEncoderConfig{@link #ByteRTCScreenVideoEncoderConfig}.
 * @return  
 *        + 0: Success. <br>
 *        + ! 0: Failure.
 * @note  
 *      + Call this API before publishing screen sharing stream with publishScreen:{@link #ByteRTCRoom#publishScreen:}.<br>
 *      + We recommend that you set the encoding configuration before video capture. Otherwise, the streams will be captured based on the default configuration(1080p@15fps).
 */
-(int)setScreenVideoEncoderConfig:(ByteRTCScreenVideoEncoderConfig * _Nullable) encoderConfig;

/**
 * @locale zh
 * @hidden(macOS)
 * @valid since 3.58
 * @type api
 * @region 视频管理
 * @brief 开启自定义采集视频帧的 Alpha 通道编码功能。
 *        适用于需要分离推流端视频主体与背景，且在拉流端可自定义渲染背景的场景。
 * @param streamIndex 需开启该功能的视频流类型，当前仅支持对 ByteRTCStreamIndex.ByteRTCStreamIndexMain 即主流开启。
 * @param alphaLayout 分离后的 Alpha 通道相对于 RGB 通道信息的排列位置。当前仅支持 ByteRTCAlphaLayout.ByteRTCAlphaLayoutTop，即置于 RGB 通道信息上方。
 * @return 方法调用结果：
 *         - 0：成功；
 *         - !0：失败。
 * @notes <br>
 *        - 该接口仅作用于自定义采集的 ByteRTCVideoPixelFormat.ByteRTCVideoPixelFormatCVPixelBuffer 格式视频帧。
 *        - 该接口须在发布视频流之前调用。
 *        - 调用本接口开启 Alpha 通道编码后，你需调用 pushExternalVideoFrame:{@link #ByteRTCVideo#pushExternalVideoFrame:} 把自定义采集的视频帧推送至 RTC SDK。若推送了不支持的视频帧格式，则调用 pushExternalVideoFrame:{@link #ByteRTCVideo#pushExternalVideoFrame:} 时会返回错误码 ByteRTCReturnStatus.ByteRTCReturnStatusParameterErr。
 */
-(int)enableAlphaChannelVideoEncode:(ByteRTCStreamIndex)streamIndex withAlphaLayout:(ByteRTCAlphaLayout)alphaLayout;

/**
 * @locale zh
 * @hidden(macOS)
 * @valid since 3.58
 * @type api
 * @region 视频管理
 * @brief 关闭外部采集视频帧的 Alpha 通道编码功能。
 * @param streamIndex 需关闭该功能的视频流类型，当前仅支持设置为 ByteRTCStreamIndex.ByteRTCStreamIndexMain 即主流。
 * @return 方法调用结果：
 *         - 0：成功；
 *         - !0：失败。
 * @notes 该接口须在停止发布视频流之后调用。 
 */
-(int)disableAlphaChannelVideoEncode:(ByteRTCStreamIndex)streamIndex;

#if BYTERTC_TARGET_MAC
/**
 * @locale zh
 * @hidden(iOS)
 * @type api
 * @region 屏幕共享
 * @brief  外部采集时，当屏幕或待采集窗口大小发生改变，为了使 RTC 更好地决策合适的帧率和分辨率积，调用此接口设置改变前的分辨率。
 * @param originalCaptureWidth 首次采集屏幕流的宽度。   
 * @param originalCaptureHeight 首次采集屏幕流的高度。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note  
 *        + 调用此接口之前，建议调用 setScreenVideoEncoderConfig:{@link #ByteRTCVideo#setScreenVideoEncoderConfig:} 设置屏幕流编码相关参数：编码模式设置为智能模式，屏幕帧宽高设置为0，最大码率设置为-1，最小码率设置为0。<br>
 *        + 调用此接口后，你将收到回调 rtcEngine:onExternalScreenFrameUpdate:{@link #ByteRTCVideoDelegate#rtcEngine:onExternalScreenFrameUpdate:}，根据 RTC 智能推荐的帧率和分辨率积重新采集。
 */
/**
 * @locale en
 * @hidden(iOS)
 * @type api
 * @region screen sharing
 * @brief  When the resolution of the external shared-screen stream changes, you can call this API to set the original pixel and framerate to help RTC(in the automatic mode) recommend these configurations.
 * @param originalCaptureWidth The original width of shared-screen streams.   
 * @param originalCaptureHeight The original height of shared-screen streams.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note  
 *        + Before calling this API，you are advised to call setScreenVideoEncoderConfig:{@link #ByteRTCVideo#setScreenVideoEncoderConfig:} to set the encoding configuration: set the encoding mode to the automatic mode, the width and height to 0, the maximum bitrate to -1, and the minimum bitrate to 0.<br>
 *        + After calling this API，you will receive rtcEngine:onExternalScreenFrameUpdate:{@link #ByteRTCVideoDelegate#rtcEngine:onExternalScreenFrameUpdate:} to re-capture the stream based on the recommended pixel and framerate by RTC.
 */
-(int)setOriginalScreenVideoInfo:(int) originalCaptureWidth
        withOriginalCaptureHeight:(int)originalCaptureHeight;

#endif
/**
 * @locale zh
 * @type api
 * @region 视频管理
 * @brief 设置 RTC SDK 内部采集时的视频采集参数。<br>
 *        如果你的项目使用了 SDK 内部采集模块，可以通过本接口指定视频采集参数包括模式、分辨率、帧率。
 * @param captureConfig 视频采集参数。参看: ByteRTCVideoCaptureConfig{@link #ByteRTCVideoCaptureConfig}。
 * @return  
 *        + 0: 成功；  <br>
 *        + < 0: 失败；  
 * @note  
 * + 本接口在引擎创建后可调用，调用后立即生效。建议在调用 startVideoCapture{@link #ByteRTCVideo#startVideoCapture} 前调用本接口。<br>
 * + 建议同一设备上的不同引擎使用相同的视频采集参数。<br>
 * + 如果调用本接口前使用内部模块开始视频采集，采集参数默认为 Auto 模式。
 */
/**
 * @locale en
 * @type api
 * @region  Video Management
 * @brief Sets the video capture parameters for internal capture of the RTC SDK. <br>
 *        If your project uses the SDK internal capture module, you can specify the video capture parameters including preference, resolution and frame rate through this interface.
 * @param captureConfig  Video capture parameters. See: ByteRTCVideoCaptureConfig{@link #ByteRTCVideoCaptureConfig}.
 * @return  
 *         + 0: Success; <br>
 *         + < 0: Failure; 
 * @note   
 *  + This interface can be called after the engine is created and takes effect immediately after being called. It is recommended to call this method before startVideoCapture{@link #ByteRTCVideo#startVideoCapture}.<br>
 *  + It is recommended that different Engines on the same device use the same video capture parameters.<br>
 *  + If you use the internal module to start video capture before calling this interface, the capture parameters default to Auto.
 */
- (int)setVideoCaptureConfig:(ByteRTCVideoCaptureConfig * _Nullable)captureConfig;
/**
 * @locale zh
 * @type api
 * @region 视频管理
 * @brief 设置本地视频渲染时使用的视图，并设置渲染模式。
 * @param streamIndex 流属性，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param canvas 视图信息和渲染模式，参看 ByteRTCVideoCanvas{@link #ByteRTCVideoCanvas}
 * @return  
 *         + 0：方法调用成功  <br>
 *         + < 0：方法调用失败  
 * @note  
 *        + 你应在加入房间前，绑定本地视图。退出房间后，此设置仍然有效。 <br>
 *        + 如果需要解除绑定，你可以调用本方法传入空视图。
 */
/**
 * @locale en
 * @type api
 * @region Video Management
 * @brief Sets the view to be used for local video rendering and the rendering mode.  
 * @param streamIndex Video stream type. See ByteRTCStreamIndex{@link #ByteRTCStreamIndex}.
 * @param canvas View information and rendering mode. See ByteRTCVideoCanvas{@link #ByteRTCVideoCanvas}.
 * @return   
 *         + 0: Success <br>
 *         + -1: Failure 
 * @note  
 *       + You should bind your stream to a view before joining the room. This setting will remain in effect after you leave the room. <br>
 *       + If you need to unbind the local video stream from the current view, you can call this API and set the videoCanvas to `null`.
 */
- (int)setLocalVideoCanvas:(ByteRTCStreamIndex)streamIndex
                withCanvas:(ByteRTCVideoCanvas * _Nullable)canvas NS_SWIFT_NAME(setLocalVideoCanvas(_:withCanvas:));
/**
 * @locale zh
 * @type api
 * @region 视频管理
 * @brief 修改本地视频渲染模式和背景色。
 * @param streamIndex 视频流属性。参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param renderMode 渲染模式。参看 ByteRTCRenderMode{@link #ByteRTCRenderMode}
 * @param backgroundColor 背景颜色。参看 ByteRTCVideoCanvas{@link #ByteRTCVideoCanvas}.backgroundColor
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note 你可以在本地视频渲染过程中，调用此接口。调用结果会实时生效。
 */
/**
 * @locale en
 * @type api
 * @region  video management
 * @brief Update the render mode and background color of local video rendering.
 * @param streamIndex See ByteRTCStreamIndex{@link #ByteRTCStreamIndex}.
 * @param renderMode See ByteRTCRenderMode{@link #ByteRTCRenderMode}.
 * @param backgroundColor See ByteRTCVideoCanvas{@link #ByteRTCVideoCanvas}.backgroundColor.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note Calling this API during local video rendering will be effective immediately.
 */
- (int)updateLocalVideoCanvas:(ByteRTCStreamIndex)streamIndex
                withRenderMode:(ByteRTCRenderMode)renderMode
          withBackgroundColor:(NSUInteger)backgroundColor NS_SWIFT_NAME(updateLocalVideoCanvas(_:withRenderMode:withBackgroundColor:));
/**
 * @locale zh
 * @type api
 * @region 视频管理
 * @brief 渲染来自指定远端用户 uid 的视频流时，设置使用的视图和渲染模式。  <br>
 *        如果需要解除视频的绑定视图，把 `canvas.view` 设置为空。(`canvas` 中其他参数不能为空。)
 * @param key 远端流信息, 详见 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}。
 * @param canvas 视图信息和渲染模式，参看 ByteRTCVideoCanvas{@link #ByteRTCVideoCanvas}。3.56 版本起支持通过 `renderRotation` 设置远端视频渲染的旋转角度。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note 本地用户离开房间时，会解除调用此 API 建立的绑定关系；远端用户离开房间则不会影响。
 */
/**
 * @locale en
 * @type api
 * @region Custom Video Capturing & Rendering
 * @brief Sets the view and rendering mode to use when rendering a video stream from a specified remote user uid. <br>
 *         If you need to unbind the video view, set canvas to empty.
 * @param key Remote stream information. See ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}.
 * @param canvas View information and rendering mode. See ByteRTCVideoCanvas{@link #ByteRTCVideoCanvas}. Starting from version 3.56, you can set the rotation angle of the remote video rendering using `renderRotation`.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note When the local user leaves the room, the setting will be invalid. The remote user leaving the room does not affect the setting.
 */
- (int)setRemoteVideoCanvas:(ByteRTCRemoteStreamKey * _Nonnull)key
             withCanvas:(ByteRTCVideoCanvas * _Nullable)canvas NS_SWIFT_NAME(setRemoteVideoCanvas(_:withCanvas:));

/**
 * @locale zh
 * @deprecated since 3.56 on iOS, and will be deleted in 3.62. Use updateRemoteStreamVideoCanvas:withRemoteVideoRenderConfig:{@link #ByteRTCVideo#updateRemoteStreamVideoCanvas:withRemoteVideoRenderConfig:} instead.
 * @type api
 * @region 视频管理
 * @brief 修改远端视频帧的渲染设置，包括渲染模式和背景颜色。
 * @param key 远端流信息, 详见 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
 * @param renderMode 渲染模式，参看 ByteRTCRenderMode{@link #ByteRTCRenderMode}
 * @param backgroundColor 背景颜色，参看 ByteRTCVideoCanvas{@link #ByteRTCVideoCanvas}.backgroundColor
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note 你可以在远端视频渲染过程中，调用此接口。调用结果会实时生效。
 * @deprecated 从 3.56起， 将在3.62删除，使用updateRemoteStreamVideoCanvas替代。
 */
/**
 * @locale en
 * @deprecated since 3.56 on iOS, and will be deleted in 3.62. Use updateRemoteStreamVideoCanvas:withRemoteVideoRenderConfig:{@link #ByteRTCVideo#updateRemoteStreamVideoCanvas:withRemoteVideoRenderConfig:} instead.
 * @type api
 * @region Video management
 * @brief Modifies remote video frame rendering settings, including render mode and background color.
 * @param key Remote stream information to the remote. See ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}.
 * @param renderMode See ByteRTCRenderMode{@link #ByteRTCRenderMode}.
 * @param backgroundColor See ByteRTCVideoCanvas{@link #ByteRTCVideoCanvas}.backgroundColor.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note Calling this API during remote video rendering will be effective immediately.
 * @deprecated since 3.56, will be deleted in 3.62, use updateRemoteStreamVideoCanvas instead.
 */
- (int)updateRemoteStreamVideoCanvas:(ByteRTCRemoteStreamKey * _Nonnull)key
                withRenderMode:(ByteRTCRenderMode)renderMode
                withBackgroundColor:(NSUInteger)backgroundColor NS_SWIFT_NAME(updateRemoteStreamVideoCanvas(_:withRenderMode:withBackgroundColor:));

/**
 * @locale zh
 * @hidden(macOS)
 * @valid since 3.56
 * @type api
 * @region 视频管理
 * @brief 使用 SDK 内部渲染时，修改远端视频帧的渲染设置，包括渲染模式、背景颜色和旋转角度。
 * @param key 远端流信息。参看 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}。
 * @param remoteVideoRenderConfig 视频帧渲染设置。具体参看 ByteRTCRemoteVideoRenderConfig{@link #ByteRTCRemoteVideoRenderConfig}。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note
 *        + 调用 setRemoteVideoCanvas:withCanvas:{@link #ByteRTCVideo#setRemoteVideoCanvas:withCanvas:} 设置了远端视频渲染模式后，你可以调用此接口更新渲染模式、背景颜色、旋转角度的设置。<br>
 *        + 该接口可以在远端视频渲染过程中调用，调用结果会实时生效。
 */
/**
 * @locale en
 * @hidden(macOS)
 * @valid since 3.56
 * @type api
 * @region Video management
 * @brief Modifies remote video frame rendering settings, including render mode, background color, and rotation angle, while using the internal rendering of the SDK.
 * @param key Information about the remote stream. See ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}.
 * @param remoteVideoRenderConfig Video rendering settings. See ByteRTCRemoteVideoRenderConfig{@link #ByteRTCRemoteVideoRenderConfig}.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Failure. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note
 *        + After setting the rendering configuration for the remote video frame with setRemoteVideoCanvas:withCanvas:{@link #ByteRTCVideo#setRemoteVideoCanvas:withCanvas:}, you can call this API to update settings including render mode, background color, and rotation angle.<br>
 *        + Calling this API during remote video rendering will be effective immediately.
 */
- (int)updateRemoteStreamVideoCanvas:(ByteRTCRemoteStreamKey * _Nonnull)key
         withRemoteVideoRenderConfig:(ByteRTCRemoteVideoRenderConfig * _Nonnull)remoteVideoRenderConfig
            NS_SWIFT_NAME(updateRemoteStreamVideoCanvas(_:withRemoteVideoRenderConfig:));

 /**
  * @locale zh
  * @type api
  * @region 视频管理
  * @brief 立即开启内部视频采集。默认为关闭状态。  <br>
  *        内部视频采集指：使用 RTC SDK 内置视频采集模块，进行采集。<br>
  *        调用该方法后，本地用户会收到 rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:} 的回调。  <br>
  *        非隐身用户进房后调用该方法，房间中的其他用户会收到 rtcEngine:onUserStartVideoCapture:uid:{@link #ByteRTCVideoDelegate#rtcEngine:onUserStartVideoCapture:uid:} 的回调。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
  * @note  
  *       + 调用 stopVideoCapture{@link #ByteRTCVideo#stopVideoCapture} 可以停止内部视频采集。否则，只有当销毁引擎实例时，内部视频采集才会停止。  <br>
  *       + 创建引擎后，无论是否发布视频数据，你都可以调用该方法开启内部视频采集。只有当（内部或外部）视频采集开始以后视频流才会发布。  <br>
  *       + 如果需要从自定义视频采集切换为内部视频采集，你必须先停止发布流，关闭自定义采集，再调用此方法手动开启内部采集。<br>
  *       + 内部视频采集使用的摄像头由 switchCamera:{@link #ByteRTCVideo#switchCamera:} 接口指定。（macOS 不支持）<br>
  *       + 自 v3.37.0 升级版本，你需要在应用中向用户申请摄像头权限后才能开始采集。
  */
 /**
  * @locale en
  * @type api
  * @region Video Management
  * @brief Enables internal video capture immediately. The default setting is off.   <br>
  *        Internal video capture refers to: capturing video using the built-in module.<br>
  *        The local client will be informed via rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:} after starting video capture by calling this API.<br>
  *        The remote clients in the room will be informed of the state change via rtcEngine:onUserStartVideoCapture:uid:{@link #ByteRTCVideoDelegate#rtcEngine:onUserStartVideoCapture:uid:} after the visible client starts video capture by calling this API.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
  * @note   
  *        + Call stopVideoCapture{@link #ByteRTCVideo#stopVideoCapture} to stop the internal video capture. Otherwise, the internal video capture will sustain until you destroy the engine instance.<br>
  *        + Once you create the engine instance, you can start internal video capture regardless of the video publishing state. The video stream will start publishing only after the video capture starts. <br>
  *        + To switch from custom to internal video capture, stop publishing before disabling the custom video capture module and then call this API to enable the internal video capture.<br>
  *        + Call switchCamera:{@link #ByteRTCVideo#switchCamera:} to switch the camera used by the internal video capture module. You cannot switch camera on macOS. <br>
  *        + Since the upgrade in v3.37.0, to start capture by calling this API, you need to request the capture permission in your App.
  */
- (int)startVideoCapture NS_SWIFT_NAME(startVideoCapture());
 /**
  * @locale zh
  * @type api
  * @region 视频管理
  * @brief 立即关闭内部视频采集。默认为关闭状态。  <br>
  *        内部视频采集指：使用 RTC SDK 内置视频采集模块，进行采集。<br>
  *        调用该方法后，本地用户会收到 rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:} 的回调。  <br>
  *        非隐身用户进房后调用该方法，房间中的其他用户会收到 rtcEngine:onUserStopVideoCapture:uid:{@link #ByteRTCVideoDelegate#rtcEngine:onUserStopVideoCapture:uid:} 的回调。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
  * @note  
  *       + 调用 startVideoCapture{@link #ByteRTCVideo#startVideoCapture} 可以开启内部视频采集。  <br>
  *       + 如果不调用本方法停止内部视频采集，则只有当销毁引擎实例时，内部视频采集才会停止。 
  */
 /**
  * @locale en
  * @type api
  * @region Video Management
  * @brief Disables internal video capture immediately. The default is off.  <br>
  *        Internal video capture refers to: use the RTC SDK built-in video capture module to capture.<br>
  *        The local client will be informed via rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:} after stopping video capture by calling this API.<br>
  *        The remote clients in the room will be informed of the state change via rtcEngine:onUserStopVideoCapture:uid:{@link #ByteRTCVideoDelegate#rtcEngine:onUserStopVideoCapture:uid:} after the visible client stops video capture by calling this API.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
  * @note   
  *        + A call startVideoCapture{@link #ByteRTCVideo#startVideoCapture} to enable the internal video capture. <br>
  *        + Without calling this API the internal video capture will sustain until you destroy the engine instance.
  */
- (int)stopVideoCapture NS_SWIFT_NAME(stopVideoCapture());
/**
 * @locale zh
 * @type api
 * @region 视频管理
 * @brief 为采集到的视频流开启镜像
 * @param mirrorType 镜像类型，参看 ByteRTCMirrorType{@link #ByteRTCMirrorType}
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note 
 *        + 切换视频源不影响镜像设置。<br>
 *        + 屏幕视频流始终不受镜像设置影响。<br>
 *        + 使用外部渲染器时，`mirrorType` 支持设置为 `0`（无镜像）和 `3`（本地预览和编码传输镜像），不支持设置为 `1`（本地预览镜像）。<br>
 *        + 该接口调用前，各视频源的初始状态如下：<br>
 *        <table>
 *           <tr><th></th><th>前置摄像头</th><th>后置摄像头</th><th>自定义采集视频源</th> <th>桌面端摄像头</th> </tr>
 *           <tr><td>移动端</td><td>本地预览镜像，编码传输不镜像</td><td> 本地预览不镜像，编码传输不镜像 </td><td> 本地预览不镜像，编码传输不镜像 </td><td>/</td></tr>
 *           <tr><td>桌面端</td><td>/</td><td>/</td><td> 本地预览不镜像，编码传输不镜像 </td><td> 本地预览镜像，编码传输不镜像 </td></tr> 
 *        </table>
 */
/**
 * @locale en
 * @type api
 * @region Video management
 * @brief Sets the mirror mode for the captured video stream.
 * @param mirrorType Mirror type. See ByteRTCMirrorType{@link #ByteRTCMirrorType}.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note  
 *         + Switching video streams does not affect the settings of the mirror type. <br>
 *         + This API is not applicable to screen-sharing streams. <br>
 *         + When using an external renderer, you can set `mirrorType` to `0` and `3`, but you cannot set it to `1`. <br>
 *         + Before you call this API, the initial states of each video stream are as follows: <br>
 *         <table>
 *            <tr><th></th><th>Front-facing camera</th><th>Back-facing camera</th><th>Custom capturing</th><th>Built-in camera</th></tr>
 *            <tr><td>Mobile device</td><td>The preview is mirrored. The published video stream is not mirrored.</td><td>The preview and the published video stream are not mirrored.</td><td>The preview and the published video stream are not mirrored.</td><td>/</td></tr>
 *            <tr><td>PC</td><td>/</td><td>/</td><td>The preview and the published video stream are not mirrored.</td><td>The preview is mirrored. The published video stream is not mirrored.</td></tr>
 *         </table>
 */
- (int)setLocalVideoMirrorType:(ByteRTCMirrorType) mirrorType;

/**
 * @locale zh
 * @type api
 * @valid since 3.57
 * @region 视频管理
 * @brief 使用内部渲染时，为远端流开启镜像。
 * @param key 远端流信息，用于指定需要镜像的视频流来源及属性，参看 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}。
 * @param mirrorType 远端流的镜像类型，参看 ByteRTCRemoteMirrorType{@link #ByteRTCRemoteMirrorType}。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0: 调用失败，参看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明。
 */
- (int)setRemoteVideoMirrorType:(ByteRTCRemoteStreamKey*)key withMirrorType:(ByteRTCRemoteMirrorType)mirrorType;

/**
 * @locale zh
 * @hidden(macOS)
 * @type api
 * @brief 设置采集视频的旋转模式。默认以 App 方向为旋转参考系。<br>
 *        接收端渲染视频时，将按照和发送端相同的方式进行旋转。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @param rotationMode 视频旋转参考系为 App 方向或重力方向，参看 ByteRTCVideoRotationMode{@link #ByteRTCVideoRotationMode}。
 * @note 
 *        + 旋转仅对内部视频采集生效，不适用于外部视频源和屏幕源。<br>
 *        + 调用该接口时已开启视频采集，将立即生效；调用该接口时未开启视频采集，则将在采集开启后生效。<br>
 *        + 更多信息请参考[视频采集方向](https://www.volcengine.com/docs/6348/106458)。
 */
/**
 * @locale en
 * @hidden(macOS)
 * @type api
 * @brief Sets the orientation of the video capture. By default, the App direction is used as the orientation reference.<br>
 *        During rendering, the receiving client rotates the video in the same way as the sending client does.
 * @param rotationMode Rotation reference can be the orientation of the App or gravity. Refer to ByteRTCVideoRotationMode{@link #ByteRTCVideoRotationMode} for details.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note 
 *        + The orientation setting is effective for internal video capture only. That is, the orientation setting is not effective to the custom video source or the screen-sharing stream.<br>
 *        + If the video capture is on, the setting will be effective once you call this API. If the video capture is off, the setting will be effective on when capture starts.
 */
- (int)setVideoRotationMode:(ByteRTCVideoRotationMode) rotationMode;

/**
 * @locale zh
 * @hidden(macOS)
 * @type api
 * @region 自定义流处理
 * @brief 在自定义视频前处理及编码前，设置 RTC 链路中的视频帧朝向，默认为 Adaptive 模式。<br>
 *        移动端开启视频特效贴纸，或使用自定义视频前处理时，建议固定视频帧朝向为 Portrait 模式。单流转推场景下，建议根据业务需要固定视频帧朝向为 Portrait 或 Landscape 模式。不同模式的具体显示效果参看[视频帧朝向](https://www.volcengine.com/docs/6348/128787)。
 * @param orientation 视频帧朝向，参看 ByteRTCVideoOrientation{@link #ByteRTCVideoOrientation}。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note 
 *        + 视频帧朝向设置仅适用于内部采集视频源。对于自定义采集视频源，设置视频帧朝向可能会导致错误，例如宽高对调。屏幕源不支持设置视频帧朝向。<br>
 *        + 编码分辨率的更新与视频帧处理是异步操作，进房后切换视频帧朝向可能导致画面出现短暂的裁切异常，因此建议在进房前设置视频帧朝向，且不在进房后进行切换。
 */
/**
 * @locale en
 * @hidden(macOS)
 * @type api
 * @region Audio & Video Processing
 * @brief Sets the orientation of the video frame before custom video processing and encoding. The default value is `Adaptive`.<br>
 *        You should set the orientation to `Portrait` when using video effects or custom processing.<br>
 *        You should set the orientation to `Portrait` or `Landscape` when pushing a single stream to the CDN.
 * @param orientation Orientation of the video frame. See ByteRTCVideoOrientation{@link #ByteRTCVideoOrientation}.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note 
 *        + The orientation setting is only applicable to internal captured video sources. For custom captured video sources, setting the video frame orientation may result in errors, such as swapping width and height. Screen sources do not support video frame orientation setting.  <br>
 *        + We recommend setting the orientation before joining room. The updates of encoding configurations and the orientation are asynchronous, therefore can cause a brief malfunction in preview if you change the orientation after joining room.
 */
- (int)setVideoOrientation:(ByteRTCVideoOrientation) orientation;
/**
 * @locale zh
 * @hidden(macOS)
 * @type api
 * @region 视频管理
 * @brief 切换视频内部采集时使用的前置/后置摄像头 <br>
 *        调用此接口后，在本地会触发 rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:} 回调。
 * @param cameraId 摄像头类型，参看 ByteRTCCameraID{@link #ByteRTCCameraID}。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note 
 *        + 默认使用前置摄像头。<br>
 *        + 如果你正在使用相机进行视频采集，切换操作当即生效；如果相机未启动，后续开启内部采集时，会打开设定的摄像头。
 */
/**
 * @locale en
 * @hidden(macOS)
 * @type api
 * @region Video Management
 * @brief Switches to the front-facing/back-facing camera used in the internal video capture  <br>
 *        The local client will be informed via rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:} after calling this API.
 * @param cameraId Camera type. Refer to ByteRTCCameraID{@link #ByteRTCCameraID} for more details.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note  
 *         + Front-facing camera is the default camera.<br>
 *         + If the internal video capturing is on, the switch is effective once you call this API. If the internal video capturing is off, the setting will be effective when capture starts.
 */
- (int)switchCamera:(ByteRTCCameraID) cameraId;

/**
 * @locale zh
 * @type api
 * @region 音视频处理
 * @brief 获取视频特效接口。
 * @return 视频特效接口，参看 ByteRTCVideoEffect{@link #ByteRTCVideoEffect}。
 */
/**
 * @locale en
 * @type api
 * @region Audio & Video Processing
 * @brief Gets video effect interfaces.
 * @return Video effect interfaces. See ByteRTCVideoEffect{@link #ByteRTCVideoEffect}.
 */
- (ByteRTCVideoEffect* _Null_unspecified)getVideoEffectInterface NS_SWIFT_NAME(getVideoEffectInterface());

#if BYTERTC_TARGET_MAC
/**
 * @locale zh
 * @type api
 * @deprecated since 3.50 and will be deleted in 3.55, use getAuthMessage:{@link #ByteRTCVideoEffect#getAuthMessage:} instead.
 * @hidden(iOS)
 * @region 视频特效
 * @brief 从特效 SDK 获取授权消息，用于获取在线许可证。
 * @param ppmsg 授权消息字符串地址
 * @return  
 *      + 0: 调用成功。<br>
 *      + –1000: 未集成特效 SDK。<br>
 *      + –1001: 特效 SDK 不支持该功能。<br>
 *      + –1002: 特效 SDK 版本不兼容。<br>
 *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
 * @note 
 *        + 使用视频特效的功能前，你必须获取特效 SDK 的在线许可证。  <br>
 *        + 通过此接口获取授权消息后，参考 [在线授权说明](https://www.volcengine.com/docs/6705/102012)，自行实现获取在线许可证的业务逻辑。获取许可证后，你必须调用 initCVResource:withAlgoModelDir:{@link #ByteRTCVideoEffect#initCVResource:withAlgoModelDir:} 确认许可证有效。然后，你才可以使用 CV 功能。  
 */
/**
 * @locale en
 * @type api
 * @deprecated since 3.50 and will be deleted in 3.55, use getAuthMessage:{@link #ByteRTCVideoEffect#getAuthMessage:} instead.
 * @hidden(iOS)
 * @region Video Effects
 * @brief Get authorization messages from the Effect SDK for the online license.
 * @param ppmsg Authorization message string address
 * @return   
 *      + 0: Success.<br>
 *      + –1000: The Effects SDK is not integrated.<br>
 *      + –1001: This API is unavailable for your Effects SDK.<br>
 *      + –1002: Your Effects SDK's version is incompatible.<br>
 *      + < 0: Other error. See [Error Code Table](https://docs.byteplus.com/en/effects/docs/error-code-table) for specific instructions.
 * @note  
 *         + You must get an online license for the Effect SDK before using the CV functions. <br>
 *         + After getting authorization messages with this API, implement the code of getting the online license with [Online License Guide](https://docs.byteplus.com/en/effects/docs/windows-license-guide). Then call initCVResource:withAlgoModelDir:{@link #ByteRTCVideoEffect#initCVResource:withAlgoModelDir:} to validate the license. After that, you can use the CV function. 
 */
- (int)getAuthMessage:(NSString *_Nullable*_Nullable)ppmsg;
#endif

/**
 * @locale zh
 * @deprecated since 3.50 and will be deleted in 3.55, use initCVResource:withAlgoModelDir:{@link #ByteRTCVideoEffect#initCVResource:withAlgoModelDir:} instead.
 * @type api
 * @region 视频特效
 * @brief 视频特效许可证检查
 * @param licenseFile 许可证文件绝对路径
 * @return  
 *      + 0: 调用成功。  <br>
 *      + 1000: 未集成特效 SDK。  <br>
 *      + 1001: 特效 SDK 不支持该功能。  <br>
 *      + < 0: 调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。  
 * @note enableVideoEffect{@link #ByteRTCVideoEffect#enableVideoEffect} 开始使用视频特效前，需要先调用这个方法进行许可证验证
 */
/**
 * @locale en
 * @deprecated since 3.50 and will be deleted in 3.55, use initCVResource:withAlgoModelDir:{@link #ByteRTCVideoEffect#initCVResource:withAlgoModelDir:} instead.
 * @type api
 * @region Video Effects
 * @brief Video effects license check
 * @param licenseFile Absolute path of license file
 * @return   
 *      + 0: Success <br>
 *      + 1000: The Effect SDK is not integrated.  <br>
 *      + 1001: This API is not available for your Effect SDK.   <br>
 *      + <0: Other errors. See [Error Code Table](https://docs.byteplus.com/en/effects/docs/error-code-table).
 * @note enableVideoEffect{@link #ByteRTCVideoEffect#enableVideoEffect} Before you start using video effects, you need to call this method for license verification
 */
- (int)checkVideoEffectLicense:(NSString * _Nonnull)licenseFile NS_SWIFT_NAME(checkVideoEffectLicense(_:)) __deprecated_msg("Will be removed in new version");

/**
 * @locale zh
 * @deprecated since 3.50 and will be deleted in 3.55, use initCVResource:withAlgoModelDir:{@link #ByteRTCVideoEffect#initCVResource:withAlgoModelDir:} instead.
 * @type api
 * @region 视频特效
 * @brief 设置视频特效算法模型路径
 * @param modelPath  <br>
 *        模型路径
 */
/**
 * @locale en
 * @deprecated since 3.50 and will be deleted in 3.55, use initCVResource:withAlgoModelDir:{@link #ByteRTCVideoEffect#initCVResource:withAlgoModelDir:} instead.
 * @type api
 * @region Video Effects
 * @brief Sets the video effects algorithm model path
 * @param modelPath   <br>
 *         Model path
 */
- (void)setVideoEffectAlgoModelPath:(NSString * _Nonnull)modelPath __deprecated_msg("Will be removed in new version");

/**
 * @locale zh
 * @hidden for internal use only
 * @deprecated since 3.50 and will be deleted in 3.55, use ByteRTCVideoEffect.setAlgoModelResourceFinder instead.
 * @type api
 * @region 视频特效
 * @brief 设置视频特效算法模型地址，并初始化特效模块。
 * @param finder ResourceFinder 地址
 * @param deteter ResourceDeleter 地址
 * @return  
 *      + 0: 调用成功。  <br>
 *      + 1000: 未集成特效 SDK。  <br>
 *      + 1001: 特效 SDK 不支持该功能。  <br>
 *      + < 0: 调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。  
 */
/**
 * @locale en
 * @hidden for internal use only
 * @deprecated since 3.50 and will be deleted in 3.55, use ByteRTCVideoEffect.setAlgoModelResourceFinder instead.
 * @type api
 * @region Video Effects
 * @brief  Sets the video effects resource finder path and initializes video effects.
 * @param finder ResourceFinder path
 * @param deteter ResourceDeleter path
 * @return  
 *      + 0: Success <br>
 *      + 1000: The Effect SDK is not integrated.  <br>
 *      + 1001: This API is not available for your Effect SDK.   <br>
 *      + <0: Other errors. See [Error Code Table](https://docs.byteplus.com/en/effects/docs/error-code-table).
 */
- (int)setVideoEffectAlgoModelResourceFinder:(void *_Nonnull)finder deleter:(void *_Nonnull)deteter __deprecated_msg("Will be removed in new version");

/**
 * @locale zh
 * @deprecated since 3.50 and will be deleted in 3.55, use enableVideoEffect{@link #ByteRTCVideoEffect#enableVideoEffect} instead.
 * @type api
 * @region 视频特效
 * @brief 创建/销毁视频特效引擎
 * @param enabled 是否创建视频特效引擎  <br>
 *       + YES: 创建  <br>
 *       + NO: 销毁
 * @return  
 *        + 0: 调用成功。  <br>
 *        + 1000: 未集成特效 SDK。  <br>
 *        + 1001: 特效 SDK 不支持该功能。  <br>
 *        + < 0: 调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。  
 * @note  
 *       + 该方法须在调用 initCVResource:withAlgoModelDir:{@link #ByteRTCVideoEffect#initCVResource:withAlgoModelDir:} 和 setVideoEffectAlgoModelPath:{@link #ByteRTCVideo#setVideoEffectAlgoModelPath:} 后调用。  <br>
 *       + 该方法不直接开启/关闭视频特效，你须在调用该方法后，调用 setVideoEffectNodes:{@link #setVideoEffectNodes:} 开启视频特效。  <br>
 *       + 通用场景下，特效引擎会随 RTC 引擎销毁而销毁。当你对性能有较高要求时，可在不使用特效相关功能时调用该方法中 false 单独销毁特效引擎。
 */
/**
 * @locale en
 * @deprecated since 3.50 and will be deleted in 3.55, use enableVideoEffect{@link #ByteRTCVideoEffect#enableVideoEffect} instead.
 * @type api
 * @region Video Effects
 * @brief  Create/destroy video effects engine
 * @param enabled Whether to create video effects engine <br>
 *        + YES: create <br>
 *        + NO: destroy
 * @return   
 *      + 0: Success <br>
 *      + 1000: The Effect SDK is not integrated.  <br>
 *      + 1001: This API is not available for your Effect SDK.   <br>
 *      + <0: Other errors. See [Error Code Table](https://docs.byteplus.com/en/effects/docs/error-code-table).
 * @note   
 *        + This method must be called after calling initCVResource:withAlgoModelDir:{@link #ByteRTCVideoEffect#initCVResource:withAlgoModelDir:} and setVideoEffectAlgoModelPath:{@link #ByteRTCVideo#setVideoEffectAlgoModelPath:}. <br>
 *        + This method does not directly turn on/off video effects. After calling this method, you must call setVideoEffectNodes:{@link #setVideoEffectNodes:} to turn on video effects. <br>
 *        + In a common scenario, the special effects engine will be destroyed with the destruction of the RTC engine. When you have high performance requirements, you can call false in this method to destroy the special effects engine separately when the special effects related functions are not used.
 */
- (int)enableVideoEffect:(BOOL)enabled NS_SWIFT_NAME(enableVideoEffect(_:)) __deprecated_msg("Will be removed in new version");

/**
 * @locale zh
 * @deprecated since 3.50 and will be deleted in 3.55, use setEffectNodes:{@link #ByteRTCVideoEffect#setEffectNodes:} instead.
 * @type api
 * @region 视频特效
 * @brief 设置视频特效素材包
 * @param effectNodePaths 特效素材包路径数组 <br>
 *        要取消当前视频特效，将此参数设置为 null。
 * @return  
  *      + 0: 调用成功。  <br>
  *      + 1000: 未集成特效 SDK。  <br>
  *      + 1001: 特效 SDK 不支持该功能。  <br>
  *      + < 0: 调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。  
 * @note 在调用这个方法之前，你须先调用 enableVideoEffect{@link #ByteRTCVideoEffect#enableVideoEffect} 。
 */
/**
 * @locale en
 * @deprecated since 3.50 and will be deleted in 3.55, use setEffectNodes:{@link #ByteRTCVideoEffect#setEffectNodes:} instead.
 * @type api
 * @region Video Effects
 * @brief Sets video effects material package.
* @param effectNodePaths Array of effect material package paths. <br>
*        To remove the current video effect, set it to null.
 * @return   
 *      + 0: Success <br>
 *      + 1000: The Effect SDK is not integrated.  <br>
 *      + 1001: This API is not available for your Effect SDK.   <br>
 *      + <0: Other errors. See [Error Code Table](https://docs.byteplus.com/en/effects/docs/error-code-table).
 * @note Before calling this method, you must first call enableVideoEffect{@link #ByteRTCVideoEffect#enableVideoEffect}.
 */
- (int) setVideoEffectNodes:(NSArray <NSString *> *_Nonnull)effectNodePaths __deprecated_msg("Will be removed in new version");

/**
 * @locale zh
 * @hidden for internal use only
 * @deprecated since 3.50 and will be deleted in 3.55, use appendEffectNodes:{@link #ByteRTCVideoEffect#appendEffectNodes:} instead.
 * @type api
 * @region 视频特效
 * @brief  叠加视频特效素材包。
 * @param effectNodePaths 特效素材包路径数组。
 * @return  
 *      + 0: 调用成功。  <br>
 *      + 1000: 未集成特效 SDK。  <br>
 *      + 1001: 特效 SDK 不支持该功能。  <br>
 *      + < 0: 调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。  
 * @note  该接口会在 setVideoEffectNodes:{@link #ByteRTCVideo#setVideoEffectNodes:} 设置的特效基础上叠加特效。
 */
/**
 * @locale en
 * @hidden for internal use only
 * @deprecated since 3.50 and will be deleted in 3.55, use appendEffectNodes:{@link #ByteRTCVideoEffect#appendEffectNodes:} instead.
 * @type api
 * @region Video Effects
 * @brief  Appends video effects material package.
 * @param effectNodePaths Array of effect material package paths.
 * @return  
 *      + 0: Success <br>
 *      + 1000: The Effect SDK is not integrated.  <br>
 *      + 1001: This API is not available for your Effect SDK.   <br>
 *      + <0: Other errors. See [Error Code Table](https://docs.byteplus.com/en/effects/docs/error-code-table).
 * @note  This API adds new video effect to the video effect you set with setVideoEffectNodes:{@link #ByteRTCVideo#setVideoEffectNodes:}.
 */
- (int) appendVideoEffectNodes:(NSArray <NSString *> *_Nonnull)effectNodePaths NS_SWIFT_NAME(appendVideoEffectNodes(_:)) __deprecated_msg("Will be removed in new version");

/**
 * @locale zh
 * @hidden for internal use only
 * @deprecated since 3.50 and will be deleted in 3.55, use removeEffectNodes:{@link #ByteRTCVideoEffect#removeEffectNodes:} instead.
 * @type api
 * @region 视频特效
 * @brief 移除指定的视频特效资源。
 * @param effectNodes 特效素材包路径数组。 
 * @return  
 *      + 0: 调用成功。  <br>
 *      + 1000: 未集成特效 SDK。  <br>
 *      + 1001: 特效 SDK 不支持该功能。  <br>
 *      + < 0: 调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。  
 * @note 移除 setVideoEffectNodes:{@link #ByteRTCVideo#setVideoEffectNodes:} 或 appendVideoEffectNodes:{@link #ByteRTCVideo#appendVideoEffectNodes:} 设置的视频特效资源。
 */
/**
 * @locale en
 * @hidden for internal use only
 * @deprecated since 3.50 and will be deleted in 3.55, use removeEffectNodes:{@link #ByteRTCVideoEffect#removeEffectNodes:} instead.
 * @type api
 * @region Video Effects
 * @brief Removes the designated video effects material package.
 * @param effectNodes Array of effect material package paths.
 * @return  
 *      + 0: Success <br>
 *      + 1000: The Effect SDK is not integrated.  <br>
 *      + 1001: This API is not available for your Effect SDK.   <br>
 *      + <0: Other errors. See [Error Code Table](https://docs.byteplus.com/en/effects/docs/error-code-table).
 * @note Removes the designated video effects in setVideoEffectNodes:{@link #ByteRTCVideo#setVideoEffectNodes:} or appendVideoEffectNodes:{@link #ByteRTCVideo#appendVideoEffectNodes:}.
 */
- (int) removeVideoEffectNodes:(NSArray <NSString *> *_Nonnull)effectNodePaths NS_SWIFT_NAME(removeVideoEffectNodes(_:)) __deprecated_msg("Will be removed in new version");

/**
 * @locale zh
 * @deprecated since 3.50 and will be deleted in 3.55, use updateEffectNode:key:value:{@link #ByteRTCVideoEffect#updateEffectNode:key:value:} instead.
 * @type api
 * @region 视频特效
 * @brief 设置特效强度
 * @param nodePath 特效素材包路径。
 * @param nodeKey 需要设置的素材 key 名称。参看 [素材key对应说明](https://www.volcengine.com/docs/6705/102041)。
 * @param nodeValue 需要设置的强度值。取值范围为 [0,1]，超出该范围设置无效。
 * @return  
  *      + 0: 调用成功。  <br>
  *      + 1000: 未集成特效 SDK。  <br>
  *      + 1001: 特效 SDK 不支持该功能。  <br>
  *      + < 0: 调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。  
 * @note 该接口仅适用于同时含有上述三个参数的特效资源，对于如大部分贴纸类等没有强度参数的特效，该接口调用无效。
 */
/**
 * @locale en
 * @deprecated since 3.50 and will be deleted in 3.55, use updateEffectNode:key:value:{@link #ByteRTCVideoEffect#updateEffectNode:key:value:} instead.
 * @type api
 * @region Video Effects
 * @brief Sets effect intensity
 * @param nodePath  Effect material package path.
 * @param nodeKey  The name of the material key to be set. See [Material key correspondence instructions](http://ailab-cv-sdk.bytedance.com/docs/2036/99769/).
 * @param nodeValue The intensity value to be set. The value range is [0,1], and the setting beyond this range is invalid.
 * @return   
 *      + 0: Success <br>
 *      + 1000: The Effect SDK is not integrated.  <br>
 *      + 1001: This API is not available for your Effect SDK.   <br>
 *      + <0: Other errors. See [Error Code Table](https://docs.byteplus.com/en/effects/docs/error-code-table).
 * @note This interface is only applicable to special effects resources that contain the above three parameters at the same time. For special effects that do not have strength parameters, such as most stickers, this interface call is invalid.
 */
- (int) updateVideoEffectNode:(NSString * _Nonnull)nodePath nodeKey:(NSString * _Nonnull)nodeKey  nodeValue:(float) nodeValue NS_SWIFT_NAME(updateVideoEffectNode(_:nodeKey:nodeValue:)) __deprecated_msg("Will be removed in new version");

/**
 * @locale zh
 * @deprecated since 3.50 and will be deleted in 3.55, use setColorFilter:{@link #ByteRTCVideoEffect#setColorFilter:} instead.
 * @type api
 * @region 视频特效
 * @brief 设置颜色滤镜
 * @param resPath  <br>
 *        滤镜资源包绝对路径
 * @return  
  *      + 0: 调用成功。  <br>
  *      + 1000: 未集成特效 SDK。  <br>
  *      + 1001: 特效 SDK 不支持该功能。  <br>
  *      + < 0: 调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。  
 */
/**
 * @locale en
 * @deprecated since 3.50 and will be deleted in 3.55, use setColorFilter:{@link #ByteRTCVideoEffect#setColorFilter:} instead.
 * @type api
 * @region Video Effects
 * @brief Sets color filter
 * @param resPath   <br>
 *        Filter effect package absolute path
 * @return   
 *      + 0: Success <br>
 *      + 1000: The Effect SDK is not integrated.  <br>
 *      + 1001: This API is not available for your Effect SDK.   <br>
 *      + <0: Other errors. See [Error Code Table](https://docs.byteplus.com/en/effects/docs/error-code-table).
 */
- (int) setVideoEffectColorFilter:(NSString * _Nonnull)resPath __deprecated_msg("Will be removed in new version");

/**
 * @locale zh
 * @deprecated since 3.50 and will be deleted in 3.55, use setColorFilterIntensity:{@link #ByteRTCVideoEffect#setColorFilterIntensity:} instead.
 * @type api
 * @region 视频特效
 * @brief 设置已启用的颜色滤镜强度
 * @param intensity 滤镜强度。取值范围 [0,1]，超出范围时设置无效
 * @return  
  *      + 0: 调用成功。  <br>
  *      + 1000: 未集成特效 SDK。  <br>
  *      + 1001: 特效 SDK 不支持该功能。  <br>
  *      + < 0: 调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。  
  */
/**
 * @locale en
 * @deprecated since 3.50 and will be deleted in 3.55, use setColorFilterIntensity:{@link #ByteRTCVideoEffect#setColorFilterIntensity:} instead.
 * @type api
 * @region Video Effects
 * @brief Sets the color filter intensity
 * @param intensity Filter intensity that is enabled. The value range [0,1] is invalid when the range is exceeded
 * @return   
 *      + 0: Success <br>
 *      + 1000: The Effect SDK is not integrated.  <br>
 *      + 1001: This API is not available for your Effect SDK.   <br>
 *      + <0: Other errors. See [Error Code Table](https://docs.byteplus.com/en/effects/docs/error-code-table).
 */
- (int) setVideoEffectColorFilterIntensity:(float) intensity __deprecated_msg("Will be removed in new version");

/**
 * @locale zh
 * @deprecated since 3.50 and will be deleted in 3.55, use enableVirtualBackground:withSource:{@link #ByteRTCVideoEffect#enableVirtualBackground:withSource:} instead.
 * @type api
 * @region 视频特效
 * @brief 将摄像头采集画面中的人像背景替换为指定图片或纯色背景。<br>
 *        若要取消背景特效，将背景贴纸特效素材路径设置为null。
 * @param modelPath 传入背景贴纸特效素材路径。  
 * @param source 设置背景特效图片的本地路径。参看 ByteRTCVirtualBackgroundSource{@link #ByteRTCVirtualBackgroundSource}。  
 * @return  
 *        + 0：调用成功。  <br>
 *        + 1000：未集成特效 SDK。  <br>
 *        + 1001：特效 SDK 不支持该功能。  <br>
 *        + < 0：调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
 * @note  
 *        调用此接口前需依次调用以下接口：1、检查视频特效许可证 initCVResource:withAlgoModelDir:{@link #ByteRTCVideoEffect#initCVResource:withAlgoModelDir:}；2、设置视频特效算法模型路径 setVideoEffectAlgoModelPath:{@link #ByteRTCVideo#setVideoEffectAlgoModelPath:}；3、开启视频特效 enableVideoEffect{@link #ByteRTCVideoEffect#enableVideoEffect}。
 */
/**
 * @locale en
 * @deprecated since 3.50 and will be deleted in 3.55, use enableVirtualBackground:withSource:{@link #ByteRTCVideoEffect#enableVirtualBackground:withSource:} instead.
 * @type api
 * @region Video Effects
 * @brief Set the original background to a specified image or a solid color.<br>
 *        To disable this effect, set the modelPath parameter to null.
 * @param modelPath Set the path of virtual background effects.  
 * @param source Set the local path of background images. See ByteRTCVirtualBackgroundSource{@link #ByteRTCVirtualBackgroundSource}.
 * @return  
 *        + 0：Success.  <br>
 *        + 1000：The BytePlus Effects SDK is not integrated.  <br>
 *        + 1001：This feature is not supported in the BytePlus Effects SDK.  <br>
 *        + < 0：Other errors. See [Error Code Table](https://docs.byteplus.com/en/effects/docs/error-code-table).
 * @note  
 *        Before calling this method, you should call initCVResource:withAlgoModelDir:{@link #ByteRTCVideoEffect#initCVResource:withAlgoModelDir:}、setVideoEffectAlgoModelPath:{@link #ByteRTCVideo#setVideoEffectAlgoModelPath:}, and enableVideoEffect{@link #ByteRTCVideoEffect#enableVideoEffect} in order.
 */
- (int) setBackgroundSticker:(NSString* _Nullable)modelPath source:(ByteRTCVirtualBackgroundSource* _Nonnull)source __deprecated_msg("Will be removed in new version");

/**
 * @locale zh
 * @hidden for internal use only
 * @deprecated since 3.50 and will be deleted in 3.55, use setVideoEffectExpressionDetect:{@link #ByteRTCVideo#setVideoEffectExpressionDetect:} instead.
 * @type api
 * @region 视频特效
 * @brief 开启人像属性检测。
 * @param config 人像属性参数，参看 ByteRTCExpressionDetectConfig{@link #ByteRTCExpressionDetectConfig}。
 * @return  
 *      + 0: 调用成功。  <br>
 *      + 1000: 未集成特效 SDK。  <br>
 *      + 1001: 特效 SDK 不支持该功能。  <br>
 *      + < 0: 调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。  
 */
/**
 * @locale en
 * @hidden for internal use only
 * @deprecated since 3.50 and will be deleted in 3.55, use setVideoEffectExpressionDetect:{@link #ByteRTCVideo#setVideoEffectExpressionDetect:} instead.
 * @type api
 * @region Video Effects
 * @brief  Sets the configuration for video effects expression detection.
 * @param config Expression detection configuration. See ByteRTCExpressionDetectConfig{@link #ByteRTCExpressionDetectConfig}.
 * @return  
 *      + 0: Success <br>
 *      + 1000: The Effect SDK is not integrated.  <br>
 *      + 1001: This API is not available for your Effect SDK.   <br>
 *      + <0: Other errors. See [Error Code Table](https://docs.byteplus.com/en/effects/docs/error-code-table).
 */
- (int)setVideoEffectExpressionDetect:(ByteRTCExpressionDetectConfig *_Nonnull)config __deprecated_msg("Will be removed in new version");

/**
 * @locale zh
 * @deprecated since 3.50 and will be deleted in 3.55, use registerFaceDetectionObserver:withInterval:{@link #ByteRTCVideoEffect#registerFaceDetectionObserver:withInterval:} instead.
 * @type api
 * @region 视频特效
 * @brief 注册人脸检测结果回调观察者 <br>
 *        注册此观察者后，你会周期性收到 onFaceDetectResult:{@link #ByteRTCFaceDetectionObserver#onFaceDetectResult:} 回调。
 * @param faceDetectionObserver 人脸检测结果回调观察者，参看 ByteRTCFaceDetectionObserver{@link #ByteRTCFaceDetectionObserver}。
 * @param interval 时间间隔，必须大于 0。单位：ms。实际收到回调的时间间隔大于 `interval`，小于 `interval + 视频采集帧间隔`。
 * @return 
 *        + 0：方法调用成功  <br>
 *        + < 0：方法调用失败  
 */
/**
 * @locale en
 * @deprecated since 3.50 and will be deleted in 3.55, use registerFaceDetectionObserver:withInterval:{@link #ByteRTCVideoEffect#registerFaceDetectionObserver:withInterval:} instead.
 * @type api
 * @region Video Effects
 * @brief  Register the observer for the result of face detection. <br>
 *        With this observer, you will receive onFaceDetectResult:{@link #ByteRTCFaceDetectionObserver#onFaceDetectResult:} periodically.
 * @param faceDetectionObserver See ByteRTCFaceDetectionObserver{@link #ByteRTCFaceDetectionObserver}.
 * @param interval Time interval in ms. The value should be greater than 0. The actual time interval of receiving callbacks is between `interval` and `interval + the time slot of a captured video frame`.
 * @return 
 *       + 0: Success <br>
 *       + <0: Failure 
 */
- (int) registerFaceDetectionObserver:(_Nullable id<ByteRTCFaceDetectionObserver>)faceDetectionObserver
                  withInterval:(NSInteger)interval NS_SWIFT_NAME(registerFaceDetectionObserver(_:withInterval:)) __deprecated_msg("Will be removed in new version");

/**
 * @locale zh
 * @type api
 * @region 音视频处理
 * @brief 开启/关闭基础美颜。
 * @param enable 基础美颜开关 <br>
 *        + YES: 开启基础美颜 <br>
 *        + NO: 关闭基础美颜（默认） 
 * @return  
 *        + 0: 调用成功。<br>
 *        + –1000: 未集成特效 SDK。<br>
 *        + –1001: RTC SDK 版本不支持此功能。<br>
 *        + –1002: 特效 SDK 当前版本不支持此功能，建议使用特效 SDK v4.4.2+ 版本。<br>
 *        + –1003: 联系技术支持人员。<br>
 *        + –1004: 正在下载相关资源，下载完成后生效。<br>
 *        + <0: 调用失败，特效 SDK 内部错误，具体错误码请参考[错误码表](https://www.volcengine.com/docs/6705/102042)。
 * @note 
 *        + 本方法不能与高级视频特效接口共用。如已购买高级视频特效，建议参看[集成指南](https://www.volcengine.com/docs/6348/114717)使用高级美颜、特效、贴纸功能等。<br>
 *        + 使用此功能需要集成特效 SDK，建议使用特效 SDK v4.4.2+ 版本。更多信息参看 [Native 端基础美颜](https://www.volcengine.com/docs/6348/372605)。<br>
 *        + 调用 setBeautyIntensity:withIntensity:{@link #ByteRTCVideo#setBeautyIntensity:withIntensity:} 设置基础美颜强度。若在调用本方法前没有设置美颜强度，则使用默认强度。各基础美颜模式的强度默认值分别为：美白 0.7，磨皮 0.8，锐化 0.5，清晰 0.7。<br>
 *        + 本方法仅适用于视频源，不适用于屏幕源。
 */
/**
 * @locale en
 * @type api
 * @region Audio & Video Processing
 * @brief Enables/Disables basic beauty effects.
 * @param enable Whether to enable basic beauty effects. <br>
 *        + YES: Enables basic beauty effects. <br>
 *        + NO: (Default) Disables basic beauty effects. 
 * @return  
 *        + 0: Success.<br>
 *        + –1000: The Effect SDK is not integrated.<br>
 *        + –1001: This API is not available for your current RTC SDK.<br>
 *        + –1002: This API is not available for your current Effect SDK. You can upgrade your Effect SDK to v4.4.2+.<br>
 *        + –1003: Contact our technical support team for further instructions.<br>
 *        + –1004: Downloading related resources. The beauty effects will take effect after downloading.<br>
 *        + <0: Failure. Effect SDK internal error. For specific error code, see [Error Code Table](https://docs.byteplus.com/effects/docs/error-code-table).
 * @note 
 *        + You cannot use the basic beauty effects and the advanced effect features at the same time. See [how to use advanced effect features](https://docs.byteplus.com/byteplus-rtc/docs/114717) for more information.<br>
 *        + You need to integrate Effect SDK before calling this API. Effect SDK v4.4.2+ is recommended.<br>
 *        + Call setBeautyIntensity:withIntensity:{@link #ByteRTCVideo#setBeautyIntensity:withIntensity:} to set the beauty effect intensity. If you do not set the intensity before calling this API, the default intensity will be enabled. The default values for the intensity of each beauty mode are as follows: 0.7 for brightning, 0.8 for smoothing, 0.5 for sharpening, and 0.7 for clarity.<br>
 *        + This API is not applicable to screen capturing.
 */
- (int) enableEffectBeauty:(BOOL)enable;

/**
 * @locale zh
 * @type api
 * @region 音视频处理
 * @brief 调整基础美颜强度。
 * @param beautyMode 基础美颜模式，参看 ByteRTCEffectBeautyMode{@link #ByteRTCEffectBeautyMode}。
 * @param intensity 美颜强度，取值范围为 [0,1]。强度为 0 表示关闭。<br>
 *                  各基础美颜模式的强度默认值分别为：美白 0.7，磨皮 0.8，锐化 0.5，清晰 0.7。
 * @return  
 *        + 0: 调用成功。<br>
 *        + –1000: 未集成特效 SDK。<br>
 *        + –1001: RTC SDK 版本不支持此功能。<br>
 *        + <0: 调用失败，特效 SDK 内部错误，具体错误码请参考[错误码表](https://www.volcengine.com/docs/6705/102042)。
 * @note 
 *        + 若在调用 enableVideoEffect{@link #ByteRTCVideoEffect#enableVideoEffect} 前设置美颜强度，则对应美颜功能的强度初始值会根据设置更新。 <br>
 *        + 销毁引擎后，美颜功能强度恢复默认值。 
 */
/**
 * @locale en
 * @type api
 * @region Audio & Video Processing
 * @brief Sets the beauty effect intensity.
 * @param beautyMode Basic beauty effect. See ByteRTCEffectBeautyMode{@link #ByteRTCEffectBeautyMode}.
 * @param intensity Beauty effect intensity in range of [0,1]. When you set it to 0, the beauty effect will be turned off.<br>
 *                  The default values for the intensity of each beauty mode are as follows: 0.7 for brightning, 0.8 for smoothing, 0.5 for sharpening, and 0.7 for clarity.
 * @return  
 *        + 0: Success.<br>
 *        + –1000: The Effect SDK is not integrated.<br>
 *        + –1001: This API is not available for your current RTC SDK.<br>
 *        + <0: Failure. Effect SDK internal error. For specific error code, see [Error Code Table](https://docs.byteplus.com/effects/docs/error-code-table).
 * @note 
 *        + If you call this API before calling enableVideoEffect{@link #ByteRTCVideoEffect#enableVideoEffect}, the default settings of beauty effect intensity will adjust accordingly. <br>
 *        + If you destroy the engine, the beauty effect settings will be invalid. 
 */
- (int) setBeautyIntensity:(ByteRTCEffectBeautyMode) beautyMode
            withIntensity:(float)intensity;

#pragma mark - ICameraControl
/**
 * @locale zh
 * @hidden(macOS)
 * @type api
 * @region 视频管理
 * @brief 设置当前使用的摄像头（前置/后置）的变焦倍数
 * @param zoomRatio 变焦倍数。取值范围是 [1, <最大变焦倍数>]。<br>
 *                 最大变焦倍数可以通过调用 getCameraZoomMaxRatio{@link #ByteRTCVideo#getCameraZoomMaxRatio} 获取。
 * @return  
 *        + 0： 成功。 <br>
 *        + < 0： 失败。
 * @note 
 *        + 必须已调用 startVideoCapture{@link #ByteRTCVideo#startVideoCapture} 使用 SDK 内部采集模块进行视频采集时，才能设置摄像头变焦倍数。<br>
 *        + 设置结果在调用 stopVideoCapture{@link #ByteRTCVideo#stopVideoCapture} 关闭内部采集后失效。<br>
 *        + 你可以调用 setVideoDigitalZoomConfig:size:{@link #ByteRTCVideo#setVideoDigitalZoomConfig:size:} 设置数码变焦参数，调用 setVideoDigitalZoomControl:{@link #ByteRTCVideo#setVideoDigitalZoomControl:} 进行数码变焦。
 */
/**
 * @locale en
 * @hidden(macOS)
 * @type api
 * @region  video management
 * @brief Sets the zoom magnification of the currently used camera (front/rear).
 * @param zoomRatio Camera zoom parameters. 1.0 means scaling to the original image, the maximum value that can be set is obtained through the getCameraZoomMaxRatio{@link #ByteRTCVideo#getCameraZoomMaxRatio} method 
 * @return   
 *       + 0: Success <br>
 *       + -1: Failure 
 * @note  
 *         + The camera zoom factor can only be set when startVideoCapture{@link #ByteRTCVideo#startVideoCapture} is called for video capture using the SDK internal capture module. <br>
 *         + The setting result fails after calling stopVideoCapture{@link #ByteRTCVideo#stopVideoCapture} to turn off internal collection.<br>
 *         + Call setVideoDigitalZoomConfig:size:{@link #ByteRTCVideo#setVideoDigitalZoomConfig:size:} to set digital zoom. Call setVideoDigitalZoomControl:{@link #ByteRTCVideo#setVideoDigitalZoomControl:} to perform digital zoom.
 */
- (int) setCameraZoomRatio: (float) zoomRatio;
/**
 * @locale zh
 * @hidden(macOS)
 * @type api
 * @region 视频管理
 * @brief 获取当前使用的摄像头（前置/后置）的最大变焦倍数
 * @return 最大变焦倍数
 * @note 必须已调用 startVideoCapture{@link #ByteRTCVideo#startVideoCapture} 使用 SDK 内部采集模块进行视频采集时，才能检测摄像头最大变焦倍数。
 */
/**
 * @locale en
 * @hidden(macOS)
 * @type api
 * @region  video management
 * @brief Gets the maximum zoom magnification of the currently used camera (front/rear).
 * @return  The maximum zoom parameters that can be set  
 */
- (float) getCameraZoomMaxRatio;
/**
 * @locale zh
 * @hidden(macOS)
 * @type api
 * @region 视频管理
 * @brief 检测当前使用的摄像头（前置/后置），是否支持变焦（数码/光学变焦）。
 * @return  
 *        + true: 支持 <br>
 *        + false: 不支持
 * @note 必须已调用 startVideoCapture{@link #ByteRTCVideo#startVideoCapture} 使用 SDK 内部采集模块进行视频采集时，才能检测摄像头变焦能力。
 */
/**
 * @locale en
 * @hidden(macOS)
 * @type api
 * @region  video management
 * @brief Detects whether the currently used camera supports zoom (digital/optical zoom).
 * @return   
 *       + true: supports scaling <br>
 *       + false: does not support scaling 
 */
- (bool) isCameraZoomSupported;
/**
 * @locale zh
 * @hidden(macOS)
 * @type api
 * @region 视频管理
 * @brief 检测当前使用的摄像头（前置/后置），是否支持闪光灯。
 * @return  
 *        + true: 支持 <br>
 *        + false: 不支持
 * @note 必须已调用 startVideoCapture{@link #ByteRTCVideo#startVideoCapture} 使用 SDK 内部采集模块进行视频采集时，才能检测闪光能力。
 */
/**
 * @locale en
 * @hidden(macOS)
 * @type api
 * @region  video management
 * @brief Detects whether the currently used camera supports flash.
 * @return   
 *       + true: support fill light <br>
 *       + false: not support fill light 
 */
- (bool) isCameraTorchSupported;
/**
 * @locale zh
 * @hidden(macOS)
 * @type api
 * @region 视频管理
 * @brief 打开/关闭当前使用的摄像头（前置/后置）的闪光灯
 * @param torchState 打开/关闭。参看 ByteRTCTorchState{@link #ByteRTCTorchState}。
 * @return  
 *        + 0： 成功。<br>
 *        + < 0： 失败。
 * @note 
 *        + 必须已调用 startVideoCapture{@link #ByteRTCVideo#startVideoCapture} 使用 SDK 内部采集模块进行视频采集时，才能设置闪光灯。<br>
 *        + 设置结果在调用 stopVideoCapture{@link #ByteRTCVideo#stopVideoCapture} 关闭内部采集后失效。
 */
/**
 * @locale en
 * @hidden(macOS)
 * @type api
 * @region  video management
 * @brief Turns on/off the flash of the currently used camera.
 * @param torchState   <br>
 *          Fill light status. See ByteRTCTorchState{@link #ByteRTCTorchState} 
 * @return   
 *       + 0: Success <br>
 *       + -1: Failure 
 */
- (int) setCameraTorch: (ByteRTCTorchState)torchState;
/**
 * @locale zh
 * @hidden(macOS)
 * @type api
 * @region 视频管理
 * @brief 检查当前使用的摄像头是否支持手动对焦。
 * @return  
 *        + true: 支持。 <br>
 *        + false: 不支持。
 * @note 必须已调用 startVideoCapture{@link #ByteRTCVideo#startVideoCapture} 使用 SDK 内部采集模块进行视频采集，才能检查摄像头是否支持手动对焦。
 */
/**
 * @locale en
 * @hidden(macOS)
 * @type api
 * @region Video Management
 * @brief Checks if manual focus is available for the currently used camera.
 * @return  
 *        + true: Available. <br>
 *        + false: Unavailable.
 * @note You must call startVideoCapture{@link #ByteRTCVideo#startVideoCapture} to start SDK internal video capturing before calling this API.
 */
- (bool)isCameraFocusPositionSupported;
/**
 * @locale zh
 * @hidden(macOS)
 * @type api
 * @region 视频管理
 * @brief 设置当前使用的摄像头的对焦点。
 * @param position 对焦点坐标。以本地预览画布的左上为坐标原点，`position`的`x`字段为对焦点水平方向归一化坐标，`y`字段为对焦点垂直方向归一化坐标，取值范围为 [0, 1]。
 * @return  
 *        + 0: 成功。 <br>
 *        + < 0: 失败。
 * @note 
 *        + 必须已调用 startVideoCapture{@link #ByteRTCVideo#startVideoCapture} 使用 SDK 内部采集模块进行视频采集，并且使用 SDK 内部渲染时，才能设置对焦点。  <br>
 *        + 对焦点设置为画布中央（即`x`和`y`均取 0.5）时，恢复系统默认值。  <br>
 *        + 调用 stopVideoCapture{@link #ByteRTCVideo#stopVideoCapture} 关闭内部采集后，设置的对焦点失效。
 */
/**
 * @locale en
 * @hidden(macOS)
 * @type api
 * @region Video Management
 * @brief Sets the manual focus position for the currently used camera.
 * @param position The position of the focus point. Setting the upper-left corner of the canvas as the origin, the `x` in `position` means the x-coordinate of the focus point in range of [0, 1], and the `y` in `position` means the y-coordinate of the focus point in range of [0, 1].
 * @return  
 *        + 0: Success. <br>
 *        + < 0: Failure.
 * @note 
 *        + You must call startVideoCapture{@link #ByteRTCVideo#startVideoCapture} to start SDK internal video capturing, and use SDK internal rendering before calling this API. <br>
 *        + When you set the focus point at the center of the canvas, the focus point setting will be canceled.  <br>
 *        + The camera focus point setting will be invalid after calling stopVideoCapture{@link #ByteRTCVideo#stopVideoCapture} to stop internal capturing.
 */
- (int)setCameraFocusPosition:(CGPoint)position;
/**
 * @locale zh
 * @hidden(macOS)
 * @type api
 * @region 视频管理
 * @brief 检查当前使用的摄像头是否支持手动设置曝光点。
 * @return  
 *        + true: 支持。 <br>
 *        + false: 不支持。
 * @note 必须已调用 startVideoCapture{@link #ByteRTCVideo#startVideoCapture} 使用 SDK 内部采集模块进行视频采集时，才能检查曝光点设置能力。
 */
/**
 * @locale en
 * @hidden(macOS)
 * @type api
 * @region Video Management
 * @brief Checks if manual exposure setting is available for the currently used camera.
 * @return  
 *        + true: Available. <br>
 *        + false: Unavailable.
 * @note You must call startVideoCapture{@link #ByteRTCVideo#startVideoCapture} to start SDK internal video capturing before calling this API.
 */
- (bool)isCameraExposurePositionSupported;
/**
 * @locale zh
 * @hidden(macOS)
 * @type api
 * @region 视频管理
 * @brief 设置当前使用的摄像头的曝光点。
 * @param position 曝光点坐标。以本地预览画布的左上为坐标原点，`position`的`x`字段为曝光点水平方向归一化坐标，`y`字段为曝光点垂直方向归一化坐标，取值范围为 [0, 1]。
 * @return  
 *        + 0: 成功。 <br>
 *        + < 0: 失败。
 * @note 
 *        + 必须已调用 startVideoCapture{@link #ByteRTCVideo#startVideoCapture} 使用 SDK 内部采集模块进行视频采集，并且使用 SDK 内部渲染时，才能设置曝光点。  <br>
 *        + 曝光点设置为画布中央（即`x`和`y`均取 0.5）时，恢复系统默认值。  <br>
 *        + 调用 stopVideoCapture{@link #ByteRTCVideo#stopVideoCapture} 关闭内部采集后，设置的曝光点失效。
 */
/**
 * @locale en
 * @hidden(macOS)
 * @type api
 * @region Video Management
 * @brief Sets the manual exposure position for the currently used camera.
 * @param position The position of the exposure point. Setting the upper-left corner of the canvas as the origin, the `x` in `position` means the x-coordinate of the exposure point in range of [0, 1], and the `y` in `position` means the y-coordinate of the exposure point in range of [0, 1].
 * @return  
 *        + 0: Success. <br>
 *        + < 0: Failure.
 * @note 
 *        + You must call startVideoCapture{@link #ByteRTCVideo#startVideoCapture} to start SDK internal video capturing, and use SDK internal rendering before calling this API. <br>
 *        + When you set the exposure point at the center of the canvas, the exposure point setting will be canceled.  <br>
 *        + The camera exposure point setting will be invalid after calling stopVideoCapture{@link #ByteRTCVideo#stopVideoCapture} to stop internal capturing.
 */
- (int)setCameraExposurePosition:(CGPoint)position;

/**
 * @locale zh
 * @hidden(macOS)
 * @type api
 * @region 视频管理
 * @brief 设置当前使用的摄像头的曝光补偿。
 * @param val 曝光补偿值，取值范围 [-1, 1]，0 为系统默认值(没有曝光补偿)。
 * @return  
 *        + 0: 成功。 <br>
 *        + < 0: 失败。
 * @note 
 *        + 必须已调用 startVideoCapture{@link #ByteRTCVideo#startVideoCapture} 使用 SDK 内部采集模块进行视频采集时，才能设置曝光补偿。  <br>
 *        + 调用 stopVideoCapture{@link #ByteRTCVideo#stopVideoCapture} 关闭内部采集后，设置的曝光补偿失效。
 */
/**
 * @locale en
 * @hidden(macOS)
 * @type api
 * @region Video Management
 * @brief Sets the exposure compensation for the currently used camera.
 * @param val Exposure compensation in range of [-1, 1]. Default to 0, which means no exposure compensation.
 * @return  
 *        + 0: Success. <br>
 *        + < 0: Failure.
 * @note 
 *        + You must call startVideoCapture{@link #ByteRTCVideo#startVideoCapture} to start SDK internal video capturing, and use SDK internal rendering before calling this API. <br>
 *        + The camera exposure compensation setting will be invalid after calling stopVideoCapture{@link #ByteRTCVideo#stopVideoCapture} to stop internal capturing.
 */
- (int)setCameraExposureCompensation:(float)val;

/**
 * @locale zh
 * @type api
 * @hidden(macOS)
 * @valid since 353
 * @brief 启用或禁用内部采集时人脸自动曝光模式。此模式会改善强逆光下，脸部过暗的问题；但也会导致 ROI 以外区域过亮/过暗的问题。
 * @param enable 是否启用。默认开启。
 * @return  
 *        + 0: 成功. <br>
 *        + !0: 失败.
 * @note 在采集前或采集中调用此接口均可生效。
 */
/**
 * @locale en
 * @type api
 * @hidden(macOS, Windows, Linux)
 * @valid since 353
 * @brief Enable or disable face auto exposure mode during internal video capture. This mode fixes the problem that the face is too dark under strong backlight; but it will also cause the problem of too bright/too dark in the area outside the ROI region.
 * @param enable Whether to enable the mode. True by default.
 * @return  
 *        + 0: Success. <br>
 *        + !0: Failure.
 * @note Calling this API takes effect immediately whether before or after internal video capturing.
 */
- (int)enableCameraAutoExposureFaceMode:(bool)enable;

/**
 * @locale zh
 * @hidden(macOS)
 * @type api
 * @valid since 353
 * @brief 设置内部采集适用动态帧率时，帧率的最小值。
 * @param framerate 最小值。单位为 fps。默认值是 7。<br>
 *                  动态帧率的最大帧率是通过 setVideoCaptureConfig:{@link #ByteRTCVideo#setVideoCaptureConfig:} 设置的帧率值。当传入参数大于最大帧率时，使用固定帧率模式，帧率为最大帧率；当传入参数小于最大帧率时，使用动态帧率。
 * @return  
 *        + 0: 成功. <br>
 *        + !0: 失败.
 * @note 
 *        + 你必须在调用 startVideoCapture{@link #ByteRTCVideo#startVideoCapture} 开启内部采集前，调用此接口方可生效。<br>
 *        + 如果由于性能降级、静态适配等原因导致采集最大帧率变化时，已设置的最小帧率值会与新的采集最大帧率值重新比较。比较结果变化可能导致固定/动态帧率模式切换。
 */
/**
 * @locale en
 * @hidden(macOS)
 * @type api
 * @valid since 353
 * @brief Set the minimum frame rate of of the dynamic framerate mode during internal video capture.
 * @param framerate The minimum value in fps. The default value is 7.<br>
 *                  The maximum value of the dynamic framerate mode is set by calling setVideoCaptureConfig:{@link #ByteRTCVideo#setVideoCaptureConfig:}. When minimum value exceeds the maximum value, the frame rate is set to a fixed value as the maximum value; otherwise, dynamic framerate mode is enabled.
 * @return  
 *        + 0: Success. <br>
 *        + !0: Failure.
 * @note 
 *        + You must call this API before calling startVideoCapture{@link #ByteRTCVideo#startVideoCapture} to enable internal capture to make the setting valid.<br>
 *        + If the maximum frame rate changes due to performance degradation, static adaptation, etc., the set minimum frame rate value will be re-compared with the new maximum value. Changes in comparison results may cause switch between fixed and dynamic frame rate modes.
 */
- (int)setCameraAdaptiveMinimumFrameRate:(int)framerate;

#pragma mark - MediaMetadataData InnerVideoSource
/**
 * @locale zh
 * @deprecated since 3.50 and will be deleted in 3.55, use sendSEIMessage:andMessage:andRepeatCount:andCountPerFrame:{@link #ByteRTCVideo#sendSEIMessage:andMessage:andRepeatCount:andCountPerFrame:} instead.
 * @type api
 * @region 消息
 * @brief 通过视频帧发送 SEI 数据。  <br>
 *        在视频通话场景下，SEI 数据会随视频帧发送；在语音通话场景下，SDK 会自动生成一路 16px × 16px 的黑帧视频流用来发送 SEI 数据。
 * @param streamIndex 指定携带 SEI 数据的媒体流类型，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}。  <br>
 *        语音通话场景下，该值需设为 `ByteRTCStreamIndexMain`，否则 SEI 数据会被丢弃从而无法送达远端。
 * @param message SEI 消息。长度不超过 4KB。
 * @param repeatCount 消息发送重复次数。取值范围是 [0, 30]。<br>
 *                    调用此接口后，SEI 数据会添加到从当前视频帧开始的连续 `repeatCount+1` 个视频帧中。
 * @return 
 *        + >=0: 将被添加到视频帧中的 SEI 的数量  <br>
 *        + <0: 发送失败
 * @note 
 *        + 语音通话场景中，仅支持在内部采集模式下调用该接口发送 SEI 数据，且调用频率需为 15/repeat_count FPS。  <br>
 *        + 视频帧仅携带前后 2s 内收到的 SEI 数据；语音通话场景下，若调用此接口后 1min 内未有 SEI 数据发送，则 SDK 会自动取消发布视频黑帧。  <br>
 *        + 消息发送成功后，远端会收到 rtcEngine:onSEIMessageReceived:andMessage:{@link #ByteRTCVideoDelegate#rtcEngine:onSEIMessageReceived:andMessage:} 回调。  <br>
 *        + 语音通话切换至视频通话时，会停止使用黑帧发送 SEI 数据，自动转为用采集到的正常视频帧发送 SEI 数据。
 */
/**
 * @locale en
 * @deprecated since 3.50 and will be deleted in 3.55, use sendSEIMessage:andMessage:andRepeatCount:andCountPerFrame:{@link #ByteRTCVideo#sendSEIMessage:andMessage:andRepeatCount:andCountPerFrame:} instead.
 * @type api
 * @region Message
 * @brief Sends SEI data.  <br>
 *        In a video call scenario, SEI is sent with the video frame, while in a voice call scenario, SDK will automatically publish a black frame with a resolution of 16px × 16px to carry SEI data.
 * @param streamIndex Specifys the type of media stream that carries SEI data. See ByteRTCStreamIndex{@link #ByteRTCStreamIndex}.  <br>
 *        In a voice call, you should set this parameter to `ByteRTCStreamIndexMain`, otherwise the SEI data is discarded and cannot be sent to the remote user.
 * @param message SEI data up to 4KB in length.
 * @param repeatCount Number of times a message is sent repeatedly. The value range is [0,30]. <br>
 *                    After calling this API, the SEI data will be added to a consecutive `repeatCount+1` number of video frames starting from the current frame.
 * @return  
 *         + `>=0`: The number of SEIs to be added to the video frame <br>
 *         + `<0`: Failure
 * @note  
 *         + In a voice call scenario, this API can be called to send SEI data only in internal capture mode and with a frequency of 15/repeat_count FPS.  <br>
 *         + Each video frame carrys only the SEI data received within 2s before and after. In a voice call scenario, if no SEI data is sent within 1min after calling this API, SDK will automatically cancel publishing black frames.  <br>
 *         + After the message is sent successfully, the remote user who subscribed your video stream will receive rtcEngine:onSEIMessageReceived:andMessage:{@link #ByteRTCVideoDelegate#rtcEngine:onSEIMessageReceived:andMessage:}.<br>
 *         + When you switch from a voice call to a video call, SEI data will automatically start to be sent with normally captured video frames instead of black frames.
 */
- (int)sendSEIMessage:(ByteRTCStreamIndex)streamIndex andMessage:(NSData* _Nonnull)message andRepeatCount:(int)repeatCount __deprecated_msg("Will be removed in new version");
/**
 * @locale zh
 * @type api
 * @region 消息
 * @brief 通过视频帧发送 SEI 数据。<br>
 *        在视频通话场景下，SEI 数据会随视频帧发送；在语音通话场景下，SDK 会自动生成一路 16px × 16px 的黑帧视频流用来发送 SEI 数据。
 * @param streamIndex 指定携带 SEI 数据的媒体流类型，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}。<br>
 *        语音通话场景下，该值需设为 `ByteRTCStreamIndexMain`，否则 SEI 数据会被丢弃从而无法送达远端。
 * @param message SEI 消息，建议每帧 SEI 数据总长度长度不超过 4 KB。
 * @param repeatCount 消息发送重复次数。取值范围是 [0, max{29, %{视频帧率}-1}]。推荐范围 [2,4]。<br>
 *                    调用此接口后，SEI 数据会添加到从当前视频帧开始的连续 `repeatCount+1` 个视频帧中。
 * @param mode SEI 发送模式，参看 ByteRTCSEICountPerFrame{@link #ByteRTCSEICountPerFrame}。
 * @return 
 *        + >= 0: 将被添加到视频帧中的 SEI 的数量。<br>
 *        + < 0: 发送失败。
 * @note 
 *        + 每秒发送的 SEI 消息数量建议不超过当前的视频帧率。在语音通话场景下，黑帧帧率为 15 fps。<br>
 *        + 语音通话场景中，仅支持在内部采集模式下调用该接口发送 SEI 数据。<br>
 *        + 视频通话场景中，使用自定义采集并通过 pushExternalVideoFrame:{@link #ByteRTCVideo#pushExternalVideoFrame:} 推送至 SDK 的视频帧，若本身未携带 SEI 数据，也可通过本接口发送 SEI 数据；若原视频帧中已添加了 SEI 数据，则调用此方法不生效。<br>
 *        + 视频帧仅携带前后 2s 内收到的 SEI 数据；语音通话场景下，若调用此接口后 1min 内未有 SEI 数据发送，则 SDK 会自动取消发布视频黑帧。<br>
 *        + 消息发送成功后，远端会收到 rtcEngine:onSEIMessageReceived:andMessage:{@link #ByteRTCVideoDelegate#rtcEngine:onSEIMessageReceived:andMessage:} 回调。<br>
 *        + 语音通话切换至视频通话时，会停止使用黑帧发送 SEI 数据，自动转为用采集到的正常视频帧发送 SEI 数据。
 */
/**
 * @locale en
 * @type api
 * @region Message
 * @brief Sends SEI data.<br>
 *        In a video call scenario, SEI is sent with the video frame, while in a voice call scenario, SDK will automatically publish a black frame with a resolution of 16 × 16 pixels to carry SEI data.
 * @param streamIndex Specifys the type of media stream that carries SEI data. See ByteRTCStreamIndex{@link #ByteRTCStreamIndex}.  <br>
 *        In a voice call, you should set this parameter to `ByteRTCStreamIndexMain`, otherwise the SEI data is discarded and cannot be sent to the remote user.
 * @param message SEI data. No more than 4 KB SEI data per frame is recommended.
 * @param repeatCount Number of times a message is sent repeatedly. The value range is [0, max{29, %{video frame rate}-1}]. Recommended range: [2,4].<br>
 *                    After calling this API, the SEI data will be added to a consecutive `repeatCount+1` number of video frames starting from the current frame.
 * @param mode SEI sending mode. See ByteRTCSEICountPerFrame{@link #ByteRTCSEICountPerFrame}.
 * @return  
 *         + >= 0: The number of SEIs to be added to the video frame <br>
 *         + < 0: Failure
 * @note
 *         + We recommend the number of SEI messages per second should not exceed the current video frame rate. In a voice call, the blank-frame rate is 15 fps.<br>
 *         + In a voice call, this API can be called to send SEI data only in internal capture mode.<br>
 *         + In a video call, the custom captured video frame can also be used for sending SEI data if the original video frame contains no SEI data, otherwise calling this method will not take effect.<br>
 *         + Each video frame carrys only the SEI data received within 2s before and after. In a voice call scenario, if no SEI data is sent within 1min after calling this API, SDK will automatically cancel publishing black frames.<br>
 *         + After the message is sent successfully, the remote user who subscribed your video stream will receive rtcEngine:onSEIMessageReceived:andMessage:{@link #ByteRTCVideoDelegate#rtcEngine:onSEIMessageReceived:andMessage:}.<br>
 *         + When you switch from a voice call to a video call, SEI data will automatically start to be sent with normally captured video frames instead of black frames.
 */
- (int)sendSEIMessage:(ByteRTCStreamIndex)streamIndex andMessage:(NSData* _Nonnull)message andRepeatCount:(int)repeatCount andCountPerFrame:(ByteRTCSEICountPerFrame) mode;
    /**
     * @locale zh
     * @valid since 3.56
     * @hidden for internal use only
     * @type api
     * @region 消息
     * @brief <span id="IRTCVideo-sendseimessage-2"></span> 公共流视频帧发送 SEI 数据。
     * @param streamIndex 指定携带 SEI 数据的媒体流类型，参看 StreamIndex{@link #StreamIndex}。
     * @param channelId SEI 的消息传输通道，取值范围 [0 - 255]。通过此参数，你可以为不同接受方设置不同的 ChannelID，这样不同接收方可以根据回调中的 ChannelID 选择应关注的 SEI 信息。
     * @param message SEI 消息。
     * @param repeatCount 消息发送重复次数。取值范围是 [0, max{29, %{视频帧率}-1}]。推荐范围 [2,4]。<br>
     *                    调用此接口后，SEI 数据会添加到从当前视频帧开始的连续 `repeat_count+1` 个视频帧中。
     * @param mode SEI 发送模式，参看 ByteRTCSEICountPerFrame{@link #ByteRTCSEICountPerFrame}。
     * @return 
     *        + < 0：说明调用失败<br>
     *        + = 0：说明当前发送队列已满，无法发送<br>
     *        + > 0: 说明调用成功，该数值为已经发送 SEI 的数量
     * @note 
     *        + 每秒发送的 SEI 消息数量建议不超过当前的视频帧率<br>
     *        + 视频通话场景中，使用自定义采集并通过 pushExternalVideoFrame:{@link #ByteRTCVideo#pushExternalVideoFrame:} 推送至 SDK 的视频帧，若本身未携带 SEI 数据，也可通过本接口发送 SEI 数据；若原视频帧中已添加了 SEI 数据，则调用此方法不生效。<br>
     *        + 视频帧仅携带前后 2s 内收到的 SEI 数据<br>
     *        + 消息发送成功后，远端会收到 rtcEngine:onPublicStreamSEIMessageReceivedWithChannel:andChannelId:andMessage:{@link #ByteRTCVideoDelegate#rtcEngine:onPublicStreamSEIMessageReceivedWithChannel:andChannelId:andMessage:} 回调。<br>
     *        + 调用失败时，本地及远端都不会收到回调。
     */
    /**
     * @locale en
     * @valid since 3.56
     * @hidden for internal use only
     * @type api
     * @region Message
     * @brief <span id="IRTCVideo-sendseimessage-2"></span> Public stream sends SEI data.
     * @param streamIndex Specifys the type of media stream that carries SEI data. See StreamIndex{@link #StreamIndex}.  
     * @param channelId SEI message channel id. The value range is [0 - 255]. With this parameter, you can set different ChannelIDs for different recipients. In this way, different recipients can choose the SEI information  based on the ChannelID received in the callback.
     * @param message SEI data.
     * @param repeatCount Number of times a message is sent repeatedly. The value range is [0, max{29, %{video frame rate}-1}]. Recommended range: [2,4].<br>
     *                    After calling this API, the SEI data will be added to a consecutive `repeat_count+1` number of video frames starting from the current frame.
     * @param mode SEI sending mode. See ByteRTCSEICountPerFrame{@link #ByteRTCSEICountPerFrame}.
     * @return  
     *        + < 0：说明调用失败<br>
     *        + = 0：说明当前发送队列已满，无法发送<br>
     *        + > 0: 说明调用成功，该数值为已经发送 SEI 的数量
     * @note  
     *         + We recommend the number of SEI messages per second should not exceed the current video frame rate.<br>
     *         + In a video call, the custom captured video frame can also be used for sending SEI data if the original video frame contains no SEI data, otherwise calling this method will not take effect.<br>
     *         + Each video frame carrys only the SEI data received within 2s before and after. In a voice call scenario, if no SEI data is sent within 1min after calling this API, SDK will automatically cancel publishing black frames.<br>
     *         + After the message is sent successfully, the remote user who subscribed your video stream will receive rtcEngine:onPublicStreamSEIMessageReceivedWithChannel:andChannelId:andMessage:{@link #ByteRTCVideoDelegate#rtcEngine:onPublicStreamSEIMessageReceivedWithChannel:andChannelId:andMessage:}.<br>
     *         + When the call fails, neither the local nor the remote side will receive a callback.
     */
- (int)sendPublicStreamSEIMessage:(ByteRTCStreamIndex)streamIndex andChannelId:(int)channelId andMessage:(NSData* _Nonnull)message andRepeatCount:(int)repeatCount andCountPerFrame:(ByteRTCSEICountPerFrame)mode;
#pragma mark - VideoFrameObserver InnerVideoSource
/**
 * @locale zh
 * @type api
 * @valid since 3.51
 * @brief 设置本地摄像头数码变焦参数，包括缩放倍数，移动步长。
 * @param type 数码变焦参数类型，缩放系数或移动步长。参看 ByteRTCZoomConfigType{@link #ByteRTCZoomConfigType}。必填。
 * @param size 缩放系数或移动步长，保留到小数点后三位。默认值为 0。必填。<br>
 *                  选择不同 `type` 时有不同的取值范围。当计算后的结果超过缩放和移动边界时，取临界值。<br>
 *                  + `ByteRTCZoomConfigTypeFocusOffset`：缩放系数增量，范围为 [0, 7]。例如，设置为 0.5 时，如果调用 setVideoDigitalZoomControl:{@link #ByteRTCVideo#setVideoDigitalZoomControl:} 选择 Zoom in，则缩放系数增加 0.5。缩放系数范围 [1，8]，默认为 `1`，原始大小。<br>
 *                  + `ByteRTCZoomConfigTypeMoveOffset`：移动百分比，范围为 [0, 0.5]，默认为 0，不移动。如果调用 setVideoDigitalZoomControl:{@link #ByteRTCVideo#setVideoDigitalZoomControl:} 选择的是左右移动，则移动距离为 size x 原始视频宽度；如果选择的是上下移动，则移动距离为 size x 原始视频高度。例如，视频帧边长为 1080 px，设置为 0.5 时，实际移动距离为 0.5 x 1080 px = 540 px。
 * @return  
 *        + 0：成功。  <br>
 *        + !0：失败。  
 * @note
 *        + 每次调用本接口只能设置一种参数。如果缩放系数和移动步长都需要设置，分别调用本接口传入相应参数。<br>
 *        + 由于移动步长的默认值为 `0` ，在调用 setVideoDigitalZoomControl:{@link #ByteRTCVideo#setVideoDigitalZoomControl:} 或 startVideoDigitalZoomControl:{@link #ByteRTCVideo#startVideoDigitalZoomControl:} 进行数码变焦操作前，应先调用本接口。
 */
/**
 * @locale en
 * @type api
 * @valid since 3.51
 * @brief Set the step size for each digital zooming control to the local videos.
 * @param type Required. Identifying which type the `size` is referring to. Refer to ByteRTCZoomConfigType{@link #ByteRTCZoomConfigType}. 
 * @param size Required. Reserved to three decimal places. It defaults to `0`. <br>
 *                  The meaning and range vary from different `type`s. If the scale or moving distance exceeds the range, the limit is taken as the result.<br>
 *                  + `ByteRTCZoomConfigTypeFocusOffset`: Increasement or decrease to the scaling factor. Range: [0, 7]. For example, when it is set to 0.5 and setVideoDigitalZoomControl:{@link #ByteRTCVideo#setVideoDigitalZoomControl:} is called to zoom in, the scale will increase `0.5`. The scale ranges [1，8] and defaults to `1`, which means an original size.<br>
 *                  + `ByteRTCZoomConfigTypeMoveOffset`：Ratio of the distance to the border of video images. It ranges [0, 0.5] and defaults to `0`, which means no offset. When you call setVideoDigitalZoomControl:{@link #ByteRTCVideo#setVideoDigitalZoomControl:} and choose `CAMERA_MOVE_LEFT`, the moving distance is size x original width. While for the `CAMERA_MOVE_UP`, the moving distance is size x original height. Suppose that a video spans 1080 px and the `size` is set to `0.5` so that the distance would be 0.5 x 1080 px = 540 px.
 * @return  
 *        + 0: Success. <br>
 *        + ! 0: Failure.
 * @note
 *        + Only one size can be set for a single call. You must call this API to pass values respectively if you intend to set multiple `size`s.<br>
 *        + As the default `size` is `0`, you must call this API before performing any digital zoom control by calling setVideoDigitalZoomControl:{@link #ByteRTCVideo#setVideoDigitalZoomControl:} or startVideoDigitalZoomControl:{@link #ByteRTCVideo#startVideoDigitalZoomControl:}.
 */
- (int)setVideoDigitalZoomConfig:(ByteRTCZoomConfigType)type size:(float)size;
/**
 * @locale zh
 * @type api
 * @valid since 3.51
 * @brief 控制本地摄像头数码变焦，缩放或移动一次。设置对本地预览画面和发布到远端的视频都生效。
 * @param direction 数码变焦操作类型，参看 ByteRTCZoomDirectionType{@link #ByteRTCZoomDirectionType}。
 * @return  
 *        + 0：成功。  <br>
 *        + !0：失败。  
 * @note
 *        + 由于默认步长为 `0`，调用该方法前需通过 setVideoDigitalZoomConfig:size:{@link #ByteRTCVideo#setVideoDigitalZoomConfig:size:} 设置参数。<br>
 *        + 调用该方法进行移动前，应先使用本方法或 startVideoDigitalZoomControl:{@link #ByteRTCVideo#startVideoDigitalZoomControl:} 进行放大，否则无法移动。<br>
 *        + 当数码变焦操作超出范围时，将置为临界值。例如，移动到了图片边界、放大到了 8 倍、缩小到原图大小。<br>
 *        + 如果你希望实现持续数码变焦操作，调用 startVideoDigitalZoomControl:{@link #ByteRTCVideo#startVideoDigitalZoomControl:}。<br>
 *        + 如果你需要对摄像头进行光学变焦控制，参看 setCameraZoomRatio:{@link #ByteRTCVideo#setCameraZoomRatio:}。（macOS 不适用）
 */
/**
 * @locale en
 * @type api
 * @brief Digital zoom or move the local video image once. This action affects both the video preview locally and the stream published.
 * @param direction Action of the digital zoom control. Refer to ByteRTCZoomDirectionType{@link #ByteRTCZoomDirectionType}.
 * @return  
 *        + 0: Success. <br>
 *        + ! 0: Failure.
 * @note
 *        + As the default offset is `0`, you must call setVideoDigitalZoomConfig:size:{@link #ByteRTCVideo#setVideoDigitalZoomConfig:size:} before this API.<br>
 *        + You can only move video images after they are magnified via this API or startVideoDigitalZoomControl:{@link #ByteRTCVideo#startVideoDigitalZoomControl:}.<br>
 *        + When you request an out-of-range scale or movement, SDK will execute it with the limits. For example, when the image has been moved to the border, the image cannot be zoomed out, or has been magnified to 8x.<br>
 *        + Call startVideoDigitalZoomControl:{@link #ByteRTCVideo#startVideoDigitalZoomControl:} to have a continuous and repeatedly digital zoom control.<br>
 *        + Refer to setCameraZoomRatio:{@link #ByteRTCVideo#setCameraZoomRatio:} if you intend to have an optical zoom control to the camera. For iOS only.
 */
- (int)setVideoDigitalZoomControl:(ByteRTCZoomDirectionType) direction;
/**
 * @locale zh
 * @type api
 * @valid since 3.51
 * @brief 开启本地摄像头持续数码变焦，缩放或移动。设置对本地预览画面和发布到远端的视频都生效。
 * @param direction 数码变焦操作类型，参看 ByteRTCZoomDirectionType{@link #ByteRTCZoomDirectionType}。
 * @return  
 *        + 0：成功。  <br>
 *        + !0：失败。  
 * @note 
 *        + 由于默认步长为 `0`，调用该方法前需通过 setVideoDigitalZoomConfig:size:{@link #ByteRTCVideo#setVideoDigitalZoomConfig:size:} 设置参数。<br>
 *        + 调用该方法进行移动前，应先使用本方法或 setVideoDigitalZoomControl:{@link #ByteRTCVideo#setVideoDigitalZoomControl:} 进行放大，否则无法移动。<br>
 *        + 当数码变焦操作超出范围时，将置为临界值并停止操作。例如，移动到了图片边界、放大到了 8 倍、缩小到原图大小。<br>
 *        + 你也可以调用 stopVideoDigitalZoomControl{@link #ByteRTCVideo#stopVideoDigitalZoomControl} 手动停止控制。<br>
 *        + 如果你希望实现单次数码变焦操作，调用 setVideoDigitalZoomControl:{@link #ByteRTCVideo#setVideoDigitalZoomControl:}。<br>
 *        + 如果你需要对摄像头进行光学变焦控制，参看 setCameraZoomRatio:{@link #ByteRTCVideo#setCameraZoomRatio:}。（macOS 不适用）
 */
/**
 * @locale en
 * @type api
 * @valid since 3.51
 * @brief Continuous and repeatedly digital zoom control. This action effect both the video preview locally and the stream published.
 * @param direction Action of the digital zoom control. Refer to ByteRTCZoomDirectionType{@link #ByteRTCZoomDirectionType}.
 * @return  
 *        + 0: Success. <br>
 *        + ! 0: Failure.
 * @note 
 *        + As the default offset is `0`, you must call setVideoDigitalZoomConfig:size:{@link #ByteRTCVideo#setVideoDigitalZoomConfig:size:} before this API.<br>
 *        + You can only move video images after they are magnified via this API or setVideoDigitalZoomControl:{@link #ByteRTCVideo#setVideoDigitalZoomControl:}.<br>
 *        + The control process stops when the scale reaches the limit, or the images have been moved to the border. if the next action exceeds the scale or movement range, SDK will execute it with the limits. <br>
 *        + Call stopVideoDigitalZoomControl{@link #ByteRTCVideo#stopVideoDigitalZoomControl} to stop the ongoing zoom control.<br>
 *        + Call setVideoDigitalZoomControl:{@link #ByteRTCVideo#setVideoDigitalZoomControl:} to have a one-time digital zoom control.<br>
 *        + Refer to setCameraZoomRatio:{@link #ByteRTCVideo#setCameraZoomRatio:} if you intend to have an optical zoom control to the camera. For iOS only.
 */
- (int)startVideoDigitalZoomControl:(ByteRTCZoomDirectionType)direction;
/**
 * @locale zh
 * @type api
 * @valid since 3.51
 * @brief 停止本地摄像头持续数码变焦。
 * @return  
 *        + 0：成功。  <br>
 *        + !0：失败。  
 * @note 关于开始数码变焦，参看 startVideoDigitalZoomControl:{@link #ByteRTCVideo#startVideoDigitalZoomControl:}。
 */
/**
 * @locale en
 * @type api
 * @brief Stop the ongoing digital zoom control instantly. 
 * @return  
 *        + 0: Success. <br>
 *        + ! 0: Failure.
 * @note Refer to startVideoDigitalZoomControl:{@link #ByteRTCVideo#startVideoDigitalZoomControl:} for starting digital zooming.
 */
- (int)stopVideoDigitalZoomControl;
/**
 * @locale zh
 * @type api
 * @region 视频处理
 * @brief 设置自定义视频前处理器。<br>
 *        使用这个视频前处理器，你能够调用 processVideoFrame:{@link #ByteRTCVideoProcessorDelegate#processVideoFrame:} 对 RTC SDK 采集得到的视频帧进行前处理，并将处理后的视频帧用于 RTC 音视频通信。
 * @param processor 自定义视频处理器，详见 ByteRTCVideoProcessorDelegate{@link #ByteRTCVideoProcessorDelegate}。如果传入 null，则不对 RTC SDK 采集得到的视频帧进行前处理。<br>
 *        SDK 只持有 processor 的弱引用，你应保证其生命周期。<br>
 *        在设计 `processor` 时，应从 ByteRTCVideoFrame{@link #ByteRTCVideoFrame} 的 `textureBuf` 字段获取视频帧数据；<br>
 *        处理后返回的视频帧数据格式应为 ByteRTCVideoPixelFormat{@link #ByteRTCVideoPixelFormat} 中的 `ByteRTCVideoPixelFormatCVPixelBuffer`，且必须存放在返回帧数据的 `textureBuf` 字段中。
 * @param config 自定义视频前处理器适用的设置，详见 ByteRTCVideoPreprocessorConfig{@link #ByteRTCVideoPreprocessorConfig}。<br>
 *               当前，`config` 中的 `required_pixel_format` 仅支持：`ByteRTCVideoPixelFormatI420` 和 `ByteRTCVideoPixelFormatUnknown`：<br>
 *               + 设置为 `Unknown` 时，RTC SDK 给出供 processor 处理的视频帧格式即采集的格式。<br>
 *               + 设置为 `ByteRTCVideoPixelFormatI420` 时，RTC SDK 会将采集得到的视频转变为对应的格式，供前处理使用。<br>
 *               + 设置为其他值时，此方法调用失败。
 * @return 
 *         + 0：方法调用成功 <br>
 *         + !0：方法调用失败 
 * @note  
 *        + 重复调用此接口时，仅最后一次调用生效。效果不会叠加。<br>
 *        + 对于 iOS 平台，将 ByteRTCVideoPreprocessorConfig{@link #ByteRTCVideoPreprocessorConfig} 中的 requiredPixelFormat 设置为 `kVideoPixelFormatUnknown`，可以通过避免格式转换带来一些性能优化。
 */
/**
 * @locale en
 * @type api
 * @region  Video Processing
 * @brief  Set up a custom video preprocessor. <br>
 *         Using this video preprocessor, you can call processVideoFrame:{@link #ByteRTCVideoProcessorDelegate#processVideoFrame:} to preprocess the video frames captured by the RTC SDK and use the processed video frames for RTC audio & video communication.
 * @param processor Custom video processor. See ByteRTCVideoProcessorDelegate{@link #ByteRTCVideoProcessorDelegate}. If null is passed in, the video frames captured by the RTC SDK are not preprocessed. <br>
 *        SDK only holds weak references to the processor, you should guarantee its Life Time. <br>
 *         When designing the'processor ', the video frame data should be obtained from the'textureBuf' field of ByteRTCVideoFrame{@link #ByteRTCVideoFrame}; <br>
 *         The video frame data returned after processing should be in the format of'ByteRTCVideoPixelFormat 'in ByteRTCVideoPixelFormat{@link #ByteRTCVideoPixelFormat}, and must be stored in the'textureBuf' field that returns the frame data.
 * @param config Customize the settings applicable to the video preprocessor. See ByteRTCVideoPreprocessorConfig{@link #ByteRTCVideoPreprocessorConfig}. <br>
 *                Currently, the 'required_pixel_format 'in'config' only supports: 'ByteRTCVideoPixelFormatI420' and'ByteRTCVideoPixelFormatUnknown ': <br>
 *                + When set to'Unknown', the RTC SDK gives the format of the video frame for processing by the processor, that is, the format of the acquisition. <br>
 *                + When set to'ByteRTCVideoPixelFormatI420 ', the RTC SDK will convert the captured video into the corresponding format for pre-processing. This method call fails when <br>
 *                + Is set to another value.
 * @return  
 *          + 0: Success. <br>
 *          +! 0: failure 
 * @note   
 *         + When this interface is called repeatedly, only the last call takes effect. The effects do not stack. <br>
 *         + For iOS platforms, setting the requiredPixelFormat in ByteRTCVideoPreprocessorConfig{@link #ByteRTCVideoPreprocessorConfig} to'kVideoPixelFormatUnknown 'brings some performance optimization by avoiding format conversion.
 */
- (int)registerLocalVideoProcessor:(_Nullable id<ByteRTCVideoProcessorDelegate>) processor
                  withConfig:(ByteRTCVideoPreprocessorConfig* _Nullable)config NS_SWIFT_NAME(registerLocalVideoProcessor(_:withConfig:));
#pragma mark - LocalEncodedVideoFrameObserver
/**
 * @locale zh
 * @type api
 * @region 视频数据回调
 * @brief 注册本地视频帧监测器。  <br>
 *        无论使用内部采集还是自定义采集，调用该方法后，SDK 每监测到一帧本地视频帧时，都会将视频帧信息通过 onLocalEncodedVideoFrame:Frame:{@link #ByteRTCLocalEncodedVideoFrameObserver#onLocalEncodedVideoFrame:Frame:} 回调给用户
 * @param frameObserver 本地视频帧监测器，参看 ByteRTCLocalEncodedVideoFrameObserver{@link #ByteRTCLocalEncodedVideoFrameObserver}。将参数设置为 nullptr 则取消注册。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note 该方法可在进房前后任意时间调用，在进房前调用可保证尽可能早地监测视频帧并触发回调
 */
/**
 * @locale en
 * @type api
 * @region Video Data Callback
 * @brief Register a local video frame observer.   <br>
 *        This method applys to both internal capturing and custom capturing.  <br>
 *        After calling this API, SDK triggers onLocalEncodedVideoFrame:Frame:{@link #ByteRTCLocalEncodedVideoFrameObserver#onLocalEncodedVideoFrame:Frame:} whenever a video frame is captured.
 * @param frameObserver Local video frame observer. See ByteRTCLocalEncodedVideoFrameObserver{@link #ByteRTCLocalEncodedVideoFrameObserver}. You can cancel the registration by setting it to `nullptr`.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note You can call this API before or after entering the RTC room. Calling this API before entering the room ensures that video frames are monitored and callbacks are triggered as early as possible.
 */
- (int)registerLocalEncodedVideoFrameObserver:(_Nullable id<ByteRTCLocalEncodedVideoFrameObserver>) frameObserver NS_SWIFT_NAME(registerLocalEncodedVideoFrameObserver(_:));
#pragma mark Audio Routing Controller
// @name audio playback route
/**
 * @locale zh
 * @hidden(macOS)
 * @deprecated since 3.38 and will be deleted in 3.51, use setDefaultAudioRoute:{@link #ByteRTCVideo#setDefaultAudioRoute:} instead.
 * @type api
 * @region 音频管理
 * @brief 设置音频播放设备为扬声器或者听筒，默认使用扬声器。  <br>
 *        音频播放设备发生变化时，会收到 rtcEngine:onAudioPlaybackDeviceChanged:{@link #ByteRTCVideoDelegate#rtcEngine:onAudioPlaybackDeviceChanged:} 回调。  
 * @param audioPlaybackDevice 音频播放设备（扬声器或者听筒），详见 ByteRTCAudioPlaybackDevice{@link #ByteRTCAudioPlaybackDevice}。  
 * @return  方法调用结果  <br>
 *        + 0: 方法调用成功  <br>
 *        + < 0: 方法调用失败  
 * @note  
 *       + 该方法适用于手机等移动设备。  <br>
 *       + 听筒和扬声器为移动设备自带的音频播放设备。听筒一般用于通话，扬声器一般用于外放。  <br>
 *       + 连接有线或者蓝牙音频播放设备后，音频路由将切换至有线耳机或者蓝牙耳机。不同音频场景中，音频路由和发布订阅状态到音量类型的映射关系详见 ByteRTCAudioScenarioType{@link #ByteRTCAudioScenarioType} 。  <br>
 *       + 进房前和进房后，均可调用此方法设置音频播放设备。  
 */
/**
 * @locale en
 * @hidden(macOS)
 * @deprecated since 3.45 and will be deleted in 3.51, use setDefaultAudioRoute:{@link #ByteRTCVideo#setDefaultAudioRoute:} instead.
 * @type api
 * @region Audio management
 * @brief  Sets the speaker or the earpiece as the audio playback device. The audio playback device defaults to the speaker.  <br>
 *         When the audio playback device changes, you will receive the rtcEngine:onAudioPlaybackDeviceChanged:{@link #ByteRTCVideoDelegate#rtcEngine:onAudioPlaybackDeviceChanged:} callback. 
 * @param audioPlaybackDevice  Audio playback device (speaker or earpiece). See ByteRTCAudioPlaybackDevice{@link #ByteRTCAudioPlaybackDevice}. 
 * @return   
 *         + 0: Success <br>
 *         + < 0: failure 
 * @note   
 *        + This API is applicable for mobile devices such as mobile phones. <br>
 *        + The earpiece and the speaker are mobile devices' built-in audio playback devices. The earpiece is usually used for calling and the speaker is usually used for playing out loud. <br>
 *        + After connecting to a wired or bluetooth audio playback device, the audio route will switch to them. For the selected volume type in different audio scenarios, see ByteRTCAudioScenarioType{@link #ByteRTCAudioScenarioType}. <br>
 *        + You can call this API before or after joining room.
 */
- (int)setAudioPlaybackDevice:(ByteRTCAudioPlaybackDevice)audioPlaybackDevice __deprecated_msg("Will be removed in new version");
/**
 * @locale zh
 * @hidden(macOS)
 * @type api
 * @brief 强制切换当前的音频播放路由。默认使用 setDefaultAudioRoute:{@link #ByteRTCVideo#setDefaultAudioRoute:} 中设置的音频路由。<br>
 *        音频播放路由发生变化时，会收到 rtcEngine:onAudioRouteChanged:{@link #ByteRTCVideoDelegate#rtcEngine:onAudioRouteChanged:} 回调。
 * @param audioRoute 音频播放路由，参见 ByteRTCAudioRoute{@link #ByteRTCAudioRoute}。仅支持扬声器和默认路由设备。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note 
 *      + 对于绝大多数音频场景，使用 setDefaultAudioRoute:{@link #ByteRTCVideo#setDefaultAudioRoute:} 设置默认音频路由，并借助 RTC SDK 的音频路由自动切换逻辑即可完成。切换逻辑参见[移动端设置音频路由](https://www.volcengine.com/docs/6348/117836)。你应仅在例外的场景下，使用此接口，比如在接入外接音频设备时，手动切换音频路由。<br>
 *      + 本接口仅支持在 `ByteRTCAudioScenarioCommunication` 音频场景下使用。你可以通过调用 setAudioScenario:{@link #ByteRTCVideo#setAudioScenario:} 切换音频场景。<br>
 *      + 不同音频场景中，音频路由和发布订阅状态到音量类型的映射关系详见 ByteRTCAudioScenarioType{@link #ByteRTCAudioScenarioType} 。
 */
/**
 * @locale en
 * @hidden(macOS)
 * @type api
 * @brief Set the current audio playback route. The default device is set via setDefaultAudioRoute:{@link #ByteRTCVideo#setDefaultAudioRoute:}. <br>
 *         When the audio playback route changes, you will receive rtcEngine:onAudioRouteChanged:{@link #ByteRTCVideoDelegate#rtcEngine:onAudioRouteChanged:}.
 * @param audioRoute Audio route. Refer to ByteRTCAudioRoute{@link #ByteRTCAudioRoute}. You can only use the build-in speaker or the default route.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note 
 *      + You can implement most scenarios by calling setDefaultAudioRoute:{@link #ByteRTCVideo#setDefaultAudioRoute:} and the default audio route switching strategy of the RTC SDK. For details about the strategy, see [Set the Audio Route](https://docs.byteplus.com/byteplus-rtc/docs/117836). You should use this API in a few exceptional scenarios like manually switching audio route with external audio device connected.<br>
 *      + This interface is only supported in the `ByteRTCAudioScenarioCommunication` audio scenario. Call setAudioScenario:{@link #ByteRTCVideo#setAudioScenario:} to switch between different audio scenarios.<br>
 *      + For the volume type in different audio scenarios, refer to ByteRTCAudioScenarioType{@link #ByteRTCAudioScenarioType}.
 */
- (int)setAudioRoute:(ByteRTCAudioRoute)audioRoute;
/**
 * @locale zh
 * @hidden(macOS)
 * @type api
 * @region 音频管理
 * @brief 获取当前使用的音频播放路由。  
 * @return 详见 ByteRTCAudioRoute{@link #ByteRTCAudioRoute}
 * @note 要设置音频路由，详见 setAudioRoute:{@link #ByteRTCVideo#setAudioRoute:}，仅适用于移动端。
 */
/**
 * @locale en
 * @hidden(macOS)
 * @type api
 * @region Audio management
 * @brief Gets the information of currently-using playback route.
 * @return See ByteRTCAudioRoute{@link #ByteRTCAudioRoute}.
 * @note To set the audio playback route, see setAudioRoute:{@link #ByteRTCVideo#setAudioRoute:}. For mobile only.
 */
- (ByteRTCAudioRoute)getAudioRoute;
/**
 * @locale zh
 * @type api
 * @brief 启用匹配外置声卡的音频处理模式
 * @param enable <br>
 *        + true: 开启 <br>
 *        + false: 不开启(默认)
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note  
 *        + 当采用外接声卡进行音频采集时，建议开启此模式，以获得更好的音质。<br>
 *        + 开启此模式时，仅支持耳机播放。如果需要使用扬声器或者外置音箱播放，关闭此模式。
 */
/**
 * @locale en
 * @type api
 * @brief Enables the audio process mode for external sound card.
 * @param enable <br>
 *        + true: enable <br>
 *        + false: disable (by default)
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note   
 *         + When you use external sound card for audio capture, enable this mode for better audio quality. <br>
 *         + When using the mode, you can only use earphones. If you need to use internal or external speaker, disable this mode.
 */
- (int)enableExternalSoundCard:(bool)enable;
 /**
 * @locale zh
 * @hidden(macOS)
 * @type api
 * @brief 将默认的音频播放设备设置为听筒或扬声器。
 * @param audioRoute 音频播放设备。参看 ByteRTCAudioRoute{@link #ByteRTCAudioRoute}。仅支持听筒或扬声器。
 * @return 
 *        + 0: 方法调用成功。<br>
 *        + < 0: 方法调用失败。
 * @note 对于音频路由切换逻辑，参见[移动端设置音频路由](https://www.volcengine.com/docs/6348/117836)。
 */
/**
 * @locale en
 * @hidden(macOS)
 * @type api
 * @brief Set the speaker or earpiece as the default audio playback device.
 * @param audioRoute Audio playback device. Refer to ByteRTCAudioRoute{@link #ByteRTCAudioRoute}. You can only use earpiece and speakerphone.
 * @return 
 *         + 0: Success. <br>
 *         + < 0: failure. It fails when the device designated is neither a speaker nor an earpiece.
 * @note For the default audio route switching strategy of the RTC SDK, see [Set the Audio Route](https://docs.byteplus.com/byteplus-rtc/docs/117836).
 */
- (int)setDefaultAudioRoute:(ByteRTCAudioRoute)audioRoute;
#pragma mark Push mixed or signle stream to CDN
/**
 * @locale zh
 * @deprecated since 3.52, will be deleted in 3.58, use startPushMixedStreamToCDN:mixedConfig:observer:{@link #ByteRTCVideo#startPushMixedStreamToCDN:mixedConfig:observer:} instead.
 * @type api
 * @region 转推直播
 * @brief 新增转推直播任务，并设置合流的图片、视频视图布局和音频属性。  <br>
 *        同一个任务中转推多路直播流时，SDK 会先将多路流合成一路流，然后再进行转推。
 * @param taskID 转推直播任务 ID，长度不超过 126 字节。<br>
 *               你可以在同一房间内发起多个转推直播任务，并用不同的任务 ID 加以区分。当你需要发起多个转推直播任务时，应使用多个 ID；当你仅需发起一个转推直播任务时，建议使用空字符串。
 * @param transcoding 转推直播配置参数，详见 ByteRTCLiveTranscoding{@link #ByteRTCLiveTranscoding}。
 * @param observer 端云一体转推直播观察者。详见 LiveTranscodingDelegate{@link #LiveTranscodingDelegate}。  <br>
 *        通过注册 observer 接收转推直播相关的回调。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note  
 *       + 在调用该接口前，你需要在[控制台](https://console.volcengine.com/rtc/workplaceRTC)开启转推直播功能。   <br>
 *       + 调用该方法后，启动结果和推流过程中的错误均会通过回调 onStreamMixingEvent:taskId:error:mixType:{@link #LiveTranscodingDelegate#onStreamMixingEvent:taskId:error:mixType:} 通知用户。<br>
 *       + 调用 stopLiveTranscoding:{@link #ByteRTCVideo#stopLiveTranscoding:} 停止转推直播
 */
/**
 * @locale en
 * @deprecated since 3.52, will be deleted in 3.58, use startPushMixedStreamToCDN:mixedConfig:observer:{@link #ByteRTCVideo#startPushMixedStreamToCDN:mixedConfig:observer:} instead.
 * @type api
 * @region Push to CDN
 * @brief Creates a new task of pushing media streams to CDN and sets the relevant configurations.  <br>
 *        When pushing more than one live streams in the same task, SDK will first mix those streams into one single stream and then push it to CDN.
 * @param taskID Task ID. The length should not exceed 126 bytes.<br>
 *        You may want to push more than one mixed stream to CDN from the same room. When you do that, use different ID for corresponding tasks; if you will start only one task, use an empty string.
 * @param transcoding Configurations to be set when pushing streams to CDN. See ByteRTCLiveTranscoding{@link #ByteRTCLiveTranscoding}
 * @param observer Register this observer to receive callbacks from the SDK. See LiveTranscodingDelegate{@link #LiveTranscodingDelegate}.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note  
 *       + Before calling this API，you need to enable Push to CDN on the [console](https://console.byteplus.com/rtc/workplaceRTC).     <br>
 *        + After this API is called, the local user will receive onStreamMixingEvent:taskId:error:mixType:{@link #LiveTranscodingDelegate#onStreamMixingEvent:taskId:error:mixType:} about the result and errors during the pushing process.  <br>
 *        + Call stopLiveTranscoding:{@link #ByteRTCVideo#stopLiveTranscoding:} to stop pushing streams to CDN.
 */
- (int)startLiveTranscoding:(NSString * _Nonnull)taskID transcoding:(ByteRTCLiveTranscoding *_Nullable)transcoding observer:(id<LiveTranscodingDelegate> _Nullable)observer __deprecated_msg("deprecated since 352, will be deleted in 358, use startPushMixedStreamToCDN instead");
/**
 * @locale zh
 * @deprecated since 3.52, will be deleted in 3.58, use stopPushStreamToCDN:{@link #ByteRTCVideo#stopPushStreamToCDN:} instead.
 * @type api
 * @region 转推直播
 * @brief 停止转推直播，会收到 onStreamMixingEvent:taskId:error:mixType:{@link #LiveTranscodingDelegate#onStreamMixingEvent:taskId:error:mixType:} 回调。  <br>
 *        关于启动转推直播，参看 startLiveTranscoding:transcoding:observer:{@link #ByteRTCVideo#startLiveTranscoding:transcoding:observer:}。
 * @param taskID 转推直播任务 ID。可以指定想要停止的转推直播任务。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 */
/**
 * @locale en
 * @deprecated since 3.52, will be deleted in 3.58, use stopPushStreamToCDN:{@link #ByteRTCVideo#stopPushStreamToCDN:} instead.
 * @type api
 * @region Push to CDN
 * @brief Stops pushing media streams to CDN.  You will be informed of the change via the onStreamMixingEvent:taskId:error:mixType:{@link #LiveTranscodingDelegate#onStreamMixingEvent:taskId:error:mixType:} callback. <br>
 *        For starting pushing media streams to CDN, see startLiveTranscoding:transcoding:observer:{@link #ByteRTCVideo#startLiveTranscoding:transcoding:observer:}.
 * @param taskID Task ID. Specifys which pushing task you want to stop.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 */
- (int)stopLiveTranscoding:(NSString *_Nonnull)taskID __deprecated_msg("deprecated since 352, will be deleted in 358, use stopPushStreamToCDN instead");
/**
 * @locale zh
 * @deprecated since 3.52, will be deleted in 3.58, use updatePushMixedStreamToCDN:mixedConfig:{@link #ByteRTCVideo#updatePushMixedStreamToCDN:mixedConfig:} instead.
 * @type api
 * @region 多房间
 * @brief 更新转推直播参数，会收到 onStreamMixingEvent:taskId:error:mixType:{@link #LiveTranscodingDelegate#onStreamMixingEvent:taskId:error:mixType:} 回调。  <br>
 *        开启转推直播功能后，你可以使用此方法更新合流转推功能配置参数。
 * @param taskID 转推直播任务 ID。指定想要更新参数设置的转推直播任务。
 * @param transcoding 转推直播配置参数，参看 ByteRTCLiveTranscoding{@link #ByteRTCLiveTranscoding}。除特殊说明外，均支持过程中更新。<br>
 *                   调用时，结构体中没有传入值的属性，会被更新为默认值。
 * @return 方法调用结果。  <br>
 *         +  0：方法调用成功  <br>
 *         + < 0：方法调用失败
 */
/**
 * @locale en
 * @deprecated since 3.52, will be deleted in 3.58, use updatePushMixedStreamToCDN:mixedConfig:{@link #ByteRTCVideo#updatePushMixedStreamToCDN:mixedConfig:} instead.
 * @type api
 * @region Multi-room
 * @brief Updates parameters needed when pushing media streams to CDN.  The local user will be informed of the change via the onStreamMixingEvent:taskId:error:mixType:{@link #LiveTranscodingDelegate#onStreamMixingEvent:taskId:error:mixType:} callback. <br>
 *        After enabling the function of pushing streams to CDN, you can call this API to update the relevant configurations.
 * @param taskID Task ID. Specifys of which pushing task you want to update the parameters.
 * @param Transcoding Configurations that you want to update. See ByteRTCLiveTranscoding{@link #ByteRTCLiveTranscoding} for specific indications. You can update any property for the task unless it is specified as unavailable for updates.<br>
 *                   If you left some properties blank, you can expect these properties to be set to their default values.
 * @return  API call result.   <br>
 *          + 0: Success <br>
 *          + < 0: failure
 */
- (int)updateLiveTranscoding:(NSString *_Nonnull)taskID transcoding:(ByteRTCLiveTranscoding *_Nonnull)transcoding __deprecated_msg("deprecated since 352, will be deleted in 358, use updatePushMixedStreamToCDN instead");
/**
 * @locale zh
 * @valid since 3.52
 * @type api
 * @region 转推直播
 * @brief 新增合流转推直播任务，并设置合流的图片、视频视图布局和音频属性。  <br>
 *        同一个任务中转推多路直播流时，SDK 会先将多路流合成一路流，然后再进行转推。
 * @param taskID 转推直播任务 ID，长度不超过 126 字节。<br>
 *               你可以在同一房间内发起多个转推直播任务，并用不同的任务 ID 加以区分。当你需要发起多个转推直播任务时，应使用多个 ID；当你仅需发起一个转推直播任务时，建议使用空字符串。
 * @param config 转推直播配置参数，详见 ByteRTCMixedStreamConfig{@link #ByteRTCMixedStreamConfig}。
 * @param observer 端云一体转推直播观察者。详见 ByteRTCMixedStreamObserver{@link #ByteRTCMixedStreamObserver}。  <br>
 *        通过注册 observer 接收转推直播相关的回调。
 * @return 方法调用结果。  <br>
 *         +  0：方法调用成功  <br>
 *         + < 0：方法调用失败
 * @note  
 *       + 在调用该接口前，你需要在[控制台](https://console.volcengine.com/rtc/workplaceRTC)开启转推直播功能。     <br>
 *       + 调用该方法后，启动结果和推流过程中的错误均会通过回调 onMixingEvent:taskId:error:mixType:{@link #ByteRTCMixedStreamObserver#onMixingEvent:taskId:error:mixType:} 通知用户。<br>
 *       + 如果已在[控制台](https://console.volcengine.com/rtc/cloudRTC?tab=callback)配置了转推直播的服务端回调，调用本接口会收到 [TranscodeStarted](https://www.volcengine.com/docs/6348/75125#transcodestarted)。重复调用该接口时，第二次调用会同时触发 [TranscodeStarted](https://www.volcengine.com/docs/6348/75125#transcodestarted) 和 [TranscodeUpdated](https://www.volcengine.com/docs/6348/75125#transcodeupdated)。<br>
 *       + 调用 stopPushStreamToCDN:{@link #ByteRTCVideo#stopPushStreamToCDN:} 停止转推直播
 */
/**
 * @locale en
 * @valid since 3.52
 * @type api
 * @region Push to CDN
 * @brief Creates a new task of pushing mixed media streams to CDN and sets the relevant configurations.  <br>
 *        When pushing more than one live streams in the same task, SDK will first mix those streams into one single stream and then push it to CDN.
 * @param taskID Task ID. The length should not exceed 126 bytes.<br>
 *        You may want to push more than one mixed stream to CDN from the same room. When you do that, use different ID for corresponding tasks; if you will start only one task, use an empty string.
 * @param config Configurations to be set when pushing streams to CDN. See ByteRTCMixedStreamConfig{@link #ByteRTCMixedStreamConfig}
 * @param observer Register this observer to receive callbacks from the SDK. See ByteRTCMixedStreamObserver{@link #ByteRTCMixedStreamObserver}.
 * @return  API call result.   <br>
 *            + 0: Success <br>
 *            + <0: Failure
 * @note  
 *        + Before calling this API，you need to enable Push to CDN on the [console](https://console.byteplus.com/rtc/workplaceRTC).  <br>
 *        + After this API is called, the local user will receive onMixingEvent:taskId:error:mixType:{@link #ByteRTCMixedStreamObserver#onMixingEvent:taskId:error:mixType:} about the result and errors during the pushing process.  <br>
 *       + If you have subscribed to the push-to-CDN server callback in the [console](https://console.byteplus.com/rtc/cloudRTC?tab=callback), calling this API will receive a [TranscodeStarted](https://docs.byteplus.com/en/byteplus-rtc/docs/75125#transcodestarted) server callback notification. When calling this API repeatedly, subsequent calls to this API will trigger both [TranscodeStarted](https://docs.byteplus.com/en/byteplus-rtc/docs/75125#transcodestarted) and [TranscodeUpdated](https://docs.byteplus.com/en/byteplus-rtc/docs/75125#transcodeupdated) callbacks.<br>
 *        + Call stopPushStreamToCDN:{@link #ByteRTCVideo#stopPushStreamToCDN:} to stop pushing streams to CDN.
 */
- (int)startPushMixedStreamToCDN:(NSString * _Nonnull)taskID mixedConfig:(ByteRTCMixedStreamConfig *_Nullable)config observer:(id<ByteRTCMixedStreamObserver> _Nullable)observer;
/**
 * @locale zh
 * @valid since 3.52
 * @type api
 * @region 多房间
 * @brief 更新合流转推直播参数，会收到 onMixingEvent:taskId:error:mixType:{@link #ByteRTCMixedStreamObserver#onMixingEvent:taskId:error:mixType:} 回调。  <br>
 *        开启转推直播功能后，你可以使用此方法更新合流转推功能配置参数。
 * @param taskID 转推直播任务 ID。指定想要更新参数设置的转推直播任务。
 * @param config 转推直播配置参数，参看 ByteRTCMixedStreamConfig{@link #ByteRTCMixedStreamConfig}。除特殊说明外，均支持过程中更新。
 * @return 方法调用结果。  <br>
 *         +  0：方法调用成功  <br>
 *         + < 0：方法调用失败
 */
/**
 * @locale en
 * @valid since 3.52
 * @type api
 * @region Multi-room
 * @brief Updates parameters needed when pushing mixed media streams to CDN.  The local user will be informed of the change via the onMixingEvent:taskId:error:mixType:{@link #ByteRTCMixedStreamObserver#onMixingEvent:taskId:error:mixType:} callback. <br>
 *        After enabling the function of pushing streams to CDN, you can call this API to update the relevant configurations.
 * @param taskID Task ID. Specifys of which pushing task you want to update the parameters.
 * @param config Configurations that you want to update. Some of the configurations cannot be updated. See ByteRTCMixedStreamConfig{@link #ByteRTCMixedStreamConfig} for specific indications.
 * @return  API call result.   <br>
 *          + 0: Success <br>
 *          + <0: Failure
 */
- (int)updatePushMixedStreamToCDN:(NSString *_Nonnull)taskID mixedConfig:(ByteRTCMixedStreamConfig *_Nonnull)config;

/**
 * @locale zh
 * @type api
 * @region 转推直播
 * @brief 新增单流转推直播任务。
 * @param taskID 任务 ID。<br>
 *               你可以发起多个转推直播任务，并用不同的任务 ID 加以区分。当你需要发起多个转推直播任务时，应使用多个 ID；当你仅需发起一个转推直播任务时，建议使用空字符串。
 * @param singleStream 转推直播配置参数。详见 ByteRTCPushSingleStreamParam{@link #ByteRTCPushSingleStreamParam}。
 * @param observer 单流转推直播观察者。详见 ByteRTCPushSingleStreamToCDNObserver{@link #ByteRTCPushSingleStreamToCDNObserver}。  <br>
 *        通过注册 observer 接收单流转推直播相关的回调。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note  
 *       + 在调用该接口前，你需要在[控制台](https://console.volcengine.com/rtc/workplaceRTC)开启转推直播功能。     <br>
 *       + 调用该方法后，关于启动结果和推流过程中的错误，会收到 onStreamPushEvent:taskId:error:{@link #ByteRTCPushSingleStreamToCDNObserver#onStreamPushEvent:taskId:error:} 回调。<br>
 *       + 调用 stopPushStreamToCDN:{@link #ByteRTCVideo#stopPushStreamToCDN:} 停止任务。<br>
 *       + 由于本功能不进行编解码，所以推到 RTMP 的视频流会根据推流端的分辨率、编码方式、关闭摄像头等变化而变化。
 */
/**
 * @locale en
 * @type api
 * @region Push to CDN
 * @brief Creates a new task of pushing a single media stream to CDN.
 * @param taskID Task ID. <br>
 *        You may want to start more than one task to push streams to CDN. When you do that, use different IDs for corresponding tasks; if you will start only one task, use an empty string.
 * @param singleStream Configurations for pushing a single stream to CDN. See PushByteRTCPushSingleStreamParam{@link #ByteRTCPushSingleStreamParam}.
 * @param observer Register this observer to receive callbacks from the SDK. See ByteRTCPushSingleStreamToCDNObserver{@link #ByteRTCPushSingleStreamToCDNObserver}.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note   
 *       + Before calling this API，you need to enable Push to CDN on the [console](https://console.byteplus.com/rtc/workplaceRTC).      <br>
 *       + After calling this API, you will be informed of the result and errors during the pushing process with onStreamPushEvent:taskId:error:{@link #ByteRTCPushSingleStreamToCDNObserver#onStreamPushEvent:taskId:error:}.<br>
 *       + Call stopPushStreamToCDN:{@link #ByteRTCVideo#stopPushStreamToCDN:} to stop the task.<br>
 *       + Since this API does not perform encoding and decoding, the video stream pushed to RTMP will change according to the resolution, encoding method, and turning off the camera of the end of pushing streams.
 */
- (int)startPushSingleStreamToCDN:(NSString *_Nonnull)taskID singleStream:(ByteRTCPushSingleStreamParam *_Nonnull)singleStream observer:(id<ByteRTCPushSingleStreamToCDNObserver>_Nullable)observer NS_SWIFT_NAME(startPushSingleStreamToCDN(_:singleStream:observer:));
/**
 * @locale zh
 * @type api
 * @region 转推直播
 * @brief 停止转推直播。<br>
 *        该方法可用于停止单流转推直播或停止合流转推直播，通过 taskId 区分需要停止的任务。
 * @param taskID 任务 ID。可以指定想要停止的单流转推直播或合流转推直播任务。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note 
 *        + 关于启动单流转推直播，参看 startPushSingleStreamToCDN:singleStream:observer:{@link #ByteRTCVideo#startPushSingleStreamToCDN:singleStream:observer:}。<br>
 *        + 关于启动合流转推直播，参看 startPushMixedStreamToCDN:mixedConfig:observer:{@link #ByteRTCVideo#startPushMixedStreamToCDN:mixedConfig:observer:}。
 */
/**
 * @locale en
 * @type api
 * @region Push to CDN
 * @brief Stops the task to push a single media stream to CDN. <br>
 *        This API can be used to stop both pushing single and mixed stream to CDN. You need to distinguish the tasks to be stopped by different "taskId".
 * @param taskID Task ID. Specifys the task you want to stop.
 * @return  
 *        + 0: Success<br>
 *        + < 0 : Failure. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details.<br>
 *        + To start pushing single stream to CDN, see startPushSingleStreamToCDN:singleStream:observer:{@link #ByteRTCVideo#startPushSingleStreamToCDN:singleStream:observer:}.<br>
 *        + To start pushing mixed stream to CDN, see startPushMixedStreamToCDN:mixedConfig:observer:{@link #ByteRTCVideo#startPushMixedStreamToCDN:mixedConfig:observer:}.
 */
- (int)stopPushStreamToCDN:(NSString *_Nonnull)taskID NS_SWIFT_NAME(stopPushStreamToCDN(_:));
 /**
  * @locale zh
  * @hidden internal use only
  * @type api
  * @brief 开启缓存同步功能。开启后，会缓存收到的实时音视频数据，并对齐不同数据中的时间戳完成同步。此功能会影响音视频数据消费的实时性。
  * @param config 参看 ByteRTCChorusCacheSyncConfig{@link #ByteRTCChorusCacheSyncConfig}。
  * @param observer 事件和数据观察者，参看 ByteRTCChorusCacheSyncObserver{@link #ByteRTCChorusCacheSyncObserver}。
  * @return 查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus}。
  * @note 要关闭缓存同步功能，调用 stopChorusCacheSync{@link #RTCVideo#stopChorusCacheSync}。
  */
 /**
  * @locale en
  * @hidden internal use only
  * @type api
  * @brief Start aligning RTC data by cache. Received RTC data from different sources will be cached, and aligned based on the included timestamps. This feature compromizes the real-time nature of RTC data consumption.
  * @param config See ChorusCacheSyncConfig{@link #ChorusCacheSyncConfig}.
  * @param observer Event and data observer. See IChorusCacheSyncObserver{@link #IChorusCacheSyncObserver}.
  * @return See ByteRTCReturnStatus{@link #ByteRTCReturnStatus}.
  * @note To disable the feature, call stopChorusCacheSync{@link #ByteRTCVideo#stopChorusCacheSync}.
  */
- (int)startChorusCacheSync:(ByteRTCChorusCacheSyncConfig* _Nullable)config observer:(id<ByteRTCChorusCacheSyncObserver> _Nullable)observer;
 /**
  * @locale zh
  * @hidden internal use only
  * @type api
  * @brief 关闭缓存同步功能。
  * @return 查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus}。
  */
 /**
  * @locale en
  * @hidden internal use only
  * @type api
  * @brief Stop aligning RTC data by cache.
  * @return See ByteRTCReturnStatus{@link #ByteRTCReturnStatus}.
  */
-(int)stopChorusCacheSync;

#pragma mark public streaming
/**
 * @locale zh
 * @type api
 * @brief 发布一路公共流<br>
 *        用户可以指定房间内多个用户发布的媒体流合成一路公共流。使用同一 `appID` 的用户，可以调用 startPlayPublicStream:{@link #ByteRTCVideo#startPlayPublicStream:} 获取和播放指定的公共流。
 * @param publicStreamId 公共流 ID。
 * @param publicStream 公共流参数。详见 ByteRTCPublicStreaming{@link #ByteRTCPublicStreaming}。<br>
 *              一路公共流可以包含多路房间内的媒体流，按照指定的布局方式进行聚合。<br>
 *              如果指定的媒体流还未发布，则公共流将在指定流开始发布后实时更新。
 * @return
 *        + 0: 成功。同时将收到 rtcEngine:onPushPublicStreamResult:publicStreamId:errorCode:{@link #ByteRTCVideoDelegate#rtcEngine:onPushPublicStreamResult:publicStreamId:errorCode:} 回调。<br>
 *        + !0: 失败。当参数不合法或参数为空，调用失败。
 * @note  
 *        + 同一用户使用同一公共流 ID 多次调用本接口无效。如果你希望更新公共流参数，调用 updatePublicStreamParam:withLayout:{@link #ByteRTCVideo#updatePublicStreamParam:withLayout:} 接口。<br>
 *        + 不同用户使用同一公共流 ID 多次调用本接口时，RTC 将使用最后一次调用时传入的参数更新公共流。<br>
 *        + 使用不同的 ID 多次调用本接口可以发布多路公共流。<br>
 *        + 调用 stopPushPublicStream:{@link #ByteRTCVideo#stopPushPublicStream:} 停止发布公共流。<br>
 *        + 关于公共流功能的介绍，详见[发布和订阅公共流](https://www.volcengine.com/docs/6348/108930)
 */
/**
 * @locale en
 * @hidden currently not available
 * @type api
 * @brief Starts publishing a public media stream.<br>
 *        Users within the same `appID` can call startPlayPublicStream:{@link #ByteRTCVideo#startPlayPublicStream:} to subscribe to the public stream regardless the user has joined which room or has not joined any room.
 * @param publicStreamId ID of the public stream.
 * @param publicStream Properties of the public stream. Refer to ByteRTCPublicStreaming{@link #ByteRTCPublicStreaming} for more details.<br>
 *              A public stream can include a bundle of media streams and appears as the designated layout.
 * @return
 *        + 0: Success. And you will be informed by rtcEngine:onPushPublicStreamResult:publicStreamId:errorCode:{@link #ByteRTCVideoDelegate#rtcEngine:onPushPublicStreamResult:publicStreamId:errorCode:}. <br>
 *        + !0: Failure because of invalid parameter or empty parameters.
 * @note
 *        + Call updatePublicStreamParam:withLayout:{@link #ByteRTCVideo#updatePublicStreamParam:withLayout:} to update the properties of the public stream which is published by the same user. Calling this API with the same stream ID repeatedly by the same user can not update the existing public stream.<br>
 *        + If Users with different userID call this API with the same stream ID, the public stream will be updated with the parameters passed in the latest call.<br>
 *        + To publish multiple public streams, call this API with different stream ID respectively.<br>
 *        + To stop publishing the public stream, call stopPushPublicStream:{@link #ByteRTCVideo#stopPushPublicStream:}.<br>
 *        + Please contact ts to enable this function before using it.
 */
- (int)startPushPublicStream:(NSString * _Nonnull)publicStreamId withLayout:(ByteRTCPublicStreaming *_Nullable)publicStream;
/**
 * @locale zh
 * @type api
 * @brief 停止发布当前用户发布的公共流<br>
 *        关于发布公共流，查看 startPushPublicStream:withLayout:{@link #ByteRTCVideo#startPushPublicStream:withLayout:}。
 * @param publicStreamId 公共流 ID<br>
 *                  指定的流必须为当前用户所发布。
 * @return
 *        + 0: 成功<br>
 *        + !0: 失败
 */
/**
 * @locale en
 * @hidden currently not available.
 * @type api
 * @brief Stops the public stream published by the current user.<br>
 *        Refer to startPushPublicStream:withLayout:{@link #ByteRTCVideo#startPushPublicStream:withLayout:} for details about starting publishing a public stream.
 * @param publicStreamId ID of the public stream<br>
 *                  The public stream must be published by the current user.
 * @return
 *        + 0: Success<br>
 *        + !0: Failure
 */
- (int)stopPushPublicStream:(NSString * _Nonnull)publicStreamId;

/**
 * @locale zh
 * @type api
 * @brief 更新公共流参数<br>
 *        关于发布公共流，查看 startPushPublicStream:withLayout:{@link #ByteRTCVideo#startPushPublicStream:withLayout:}。<br>
 *        建议调用更新公共流前判断公共流是否已经成功启动，相关回调详见 rtcEngine:onPushPublicStreamResult:publicStreamId:errorCode:{@link #ByteRTCVideoDelegate#rtcEngine:onPushPublicStreamResult:publicStreamId:errorCode:}。
 * @param publicStreamId 公共流ID<br>
 *              指定的流必须为当前用户所发布的。
 * @param publicStream 推公共流配置参数。详见 ByteRTCPublicStreaming{@link #ByteRTCPublicStreaming}。
 * @return
 *        + 0: 成功<br>
 *        + !0: 失败
 */
/**
 * @locale en
 * @hidden currently not available.
 * @type api
 * @brief Updates the properties of the public stream published by the current user.<br>
 *        Refer to startPushPublicStream:withLayout:{@link #ByteRTCVideo#startPushPublicStream:withLayout:} for details about starting publishing a public stream.
 * @param publicStreamId ID of the public stream<br>
 *              The stream to be updated must be published by the current user.
 * @param publicStream Properties of the public stream. Refer to ByteRTCPublicStreaming{@link #ByteRTCPublicStreaming} for more details.current user.
 * @return 
 *        + 0: Success<br>
 *        + !0: Failure
 * @note Make sure the public stream has started successfully via rtcEngine:onPushPublicStreamResult:publicStreamId:errorCode:{@link #ByteRTCVideoDelegate#rtcEngine:onPushPublicStreamResult:publicStreamId:errorCode:} before calling this API.
 */
- (int)updatePublicStreamParam:(NSString * _Nonnull)publicStreamId withLayout:(ByteRTCPublicStreaming *_Nullable)publicStream;
/**
 * @locale zh
 * @type api
 * @brief 订阅指定公共流<br>
 *        无论用户是否在房间内，都可以调用本接口获取和播放指定的公共流。
 * @param publicStreamId 公共流ID，如果指定流暂未发布，则本地客户端将在其开始发布后接收到流数据。
 * @return 
 *        + 0: 成功。同时将收到 rtcEngine:onPlayPublicStreamResult:errorCode:{@link #ByteRTCVideoDelegate#rtcEngine:onPlayPublicStreamResult:errorCode:} 回调。<br>
 *        + !0: 失败。当参数不合法或参数为空，调用失败。
 * @note  
 *        + 在调用本接口之前，建议先绑定渲染视图。<br>
 *              - 调用 setPublicStreamVideoCanvas:withCanvas:{@link #ByteRTCVideo#setPublicStreamVideoCanvas:withCanvas:} 绑定内部渲染视图。<br>
 *              - 调用 setPublicStreamVideoSink:withSink:withPixelFormat:{@link #ByteRTCVideo#setPublicStreamVideoSink:withSink:withPixelFormat:} 绑定自定义渲染视图：<br>
 *        + 调用本接口后，可以通过 rtcEngine:onFirstPublicStreamVideoFrameDecoded:withFrameInfo:{@link #ByteRTCVideoDelegate#rtcEngine:onFirstPublicStreamVideoFrameDecoded:withFrameInfo:} 和 rtcEngine:onFirstPublicStreamAudioFrame:{@link #ByteRTCVideoDelegate#rtcEngine:onFirstPublicStreamAudioFrame:} 回调公共流的视频和音频首帧解码情况。<br>
 *        + 调用本接口后，可以通过 rtcEngine:onPublicStreamSEIMessageReceived:andMessage:andSourceType:{@link #ByteRTCVideoDelegate#rtcEngine:onPublicStreamSEIMessageReceived:andMessage:andSourceType:} 回调公共流中包含的 SEI 信息。<br>
 *        + 订阅公共流之后，可以通过调用 stopPlayPublicStream:{@link #ByteRTCVideo#stopPlayPublicStream:} 接口取消订阅公共流。
 */
/**
 * @locale en
 * @hidden currently not available.
 * @type api
 * @brief Subscribes to specified public stream.<br>
 *        This API can be called to get and play the specified public stream regardless of whether the user is in the room or not.
 * @param publicStreamId ID of the public stream. If the stream has not been published then, the local client will receive the public stream once it starts publishing.
 * @return 
 *        + 0: Success. You will also be informed by rtcEngine:onPlayPublicStreamResult:errorCode:{@link #ByteRTCVideoDelegate#rtcEngine:onPlayPublicStreamResult:errorCode:}.  <br>
 *        + !0: Failure because of invalid parameter or empty parameters.
 * @note  
 *        + We recommend you bind a view for the public stream before calling this API. <br>
 *              - Internal renderer: By calling setPublicStreamVideoCanvas:withCanvas:{@link #ByteRTCVideo#setPublicStreamVideoCanvas:withCanvas:}.<br>
 *              - Custom renderer: By calling setPublicStreamVideoSink:withSink:withPixelFormat:{@link #ByteRTCVideo#setPublicStreamVideoSink:withSink:withPixelFormat:}.<br>
 *        + After calling this API, the local user will be informed once the first frame has been decoded successfully by rtcEngine:onFirstPublicStreamVideoFrameDecoded:withFrameInfo:{@link #ByteRTCVideoDelegate#rtcEngine:onFirstPublicStreamVideoFrameDecoded:withFrameInfo:} and rtcEngine:onFirstPublicStreamAudioFrame:{@link #ByteRTCVideoDelegate#rtcEngine:onFirstPublicStreamAudioFrame:}.<br>
 *        + If the public stream contains SEI information, the local user will be informed by rtcEngine:onPublicStreamSEIMessageReceived:andMessage:andSourceType:{@link #ByteRTCVideoDelegate#rtcEngine:onPublicStreamSEIMessageReceived:andMessage:andSourceType:}.<br>
 *        + Call stopPlayPublicStream:{@link #ByteRTCVideo#stopPlayPublicStream:} to cancel subscribing the public stream.
     */
- (int)startPlayPublicStream:(NSString * _Nonnull)publicStreamId;
/**
 * @locale zh
 * @type api
 * @brief 取消订阅指定公共流<br>
 *        关于订阅公共流，查看 startPlayPublicStream:{@link #ByteRTCVideo#startPlayPublicStream:}。
 * @param publicStreamId 公共流ID
 * @return  
 *        + 0：成功  <br>
 *        + !0：失败  
 */
/**
 * @locale en
 * @hidden currently not available.
 * @type api
 * @brief Cancel subscribing the public stream.<br>
 *        Call this method to cancel subscribing to the public stream by calling startPlayPublicStream:{@link #ByteRTCVideo#startPlayPublicStream:}.
 * @param publicStreamId ID of the public stream
 * @return
 *        + 0: Success<br>
 *        + !0: Failure
 */
- (int)stopPlayPublicStream:(NSString * _Nonnull)publicStreamId;

/**
 * @locale zh
 * @type api
 * @brief 为指定公共流绑定内部渲染视图。
 * @param publicStreamId 公共流ID
 * @param canvas 内部渲染视图，如果需要解除视频的绑定视图，把 videoCanvas 设置为空。详见 ByteRTCVideoCanvas{@link #ByteRTCVideoCanvas}
 * @return  
 *        + 0：成功  <br>
 *        + !0：失败  
 */
/**
 * @locale en
 * @hidden currently not available.
 * @type api
 * @brief Assign a internal render view to the public stream
 * @param publicStreamId ID of the public stream
 * @param canvas Internal render view. Set to be a blank view if you want to unbind. Refer to ByteRTCVideoCanvas{@link #ByteRTCVideoCanvas} for more details.
 * @return
 *        + 0: Success<br>
 *        + !0: Failure
 */
- (int)setPublicStreamVideoCanvas:(NSString *_Nonnull)publicStreamId withCanvas:(ByteRTCVideoCanvas * _Nullable)canvas NS_SWIFT_NAME(setPublicStreamVideoCanvas(_:withCanvas:));

/**
 * @locale zh
 * @type api
 * @brief 为指定公共流绑定自定义渲染器。详见[自定义视频渲染](https://www.volcengine.com/docs/6348/81201)。
 * @param publicStreamId 公共流ID
 * @param videoSink 自定义视频渲染器，需要释放渲染器资源时，将 videoSink 设置为 `null`。参看 ByteRTCVideoSinkDelegate{@link #ByteRTCVideoSinkDelegate}
 * @param requiredFormat videoSink 适用的视频帧编码格式，参看 ByteRTCVideoSinkPixelFormat{@link #ByteRTCVideoSinkPixelFormat}
 * @return  
 *        + 0: 成功  <br>
 *        + <0: 失败  
 */
/**
 * @locale en
 * @hidden currently not available.
 * @type api
 * @brief Assign a custom renderer to the public stream
 * @param publicStreamId ID of the public stream
 * @param videoSink Custom renderer. Set to be `null` when you want to release the renderer. Refer to ByteRTCVideoSinkDelegate{@link #ByteRTCVideoSinkDelegate} for more details.
 * @param requiredFormat Format of the video frames required by the external video renderer. Refer to  ByteRTCVideoSinkPixelFormat{@link #ByteRTCVideoSinkPixelFormat} for more details.
 * @return  
 *        + 0: Success<br>
 *        + !0: Failure
 */
- (int)setPublicStreamVideoSink:(NSString *_Nonnull)publicStreamId
                       withSink:(id<ByteRTCVideoSinkDelegate> _Nullable)videoSink
                withPixelFormat:(ByteRTCVideoSinkPixelFormat)requiredFormat NS_SWIFT_NAME(setPublicStreamVideoSink(_:withSink:withPixelFormat:));

/**
 * @locale zh
 * @type api
 * @valid since 3.51
 * @brief 调节公共流的音频播放音量。
 * @param publicStreamId 公共流 ID
 * @param volume 音频播放音量值和原始音量值的比值，该比值的范围是 `[0, 400]`，单位为 %，且自带溢出保护。为保证更好的音频质量，建议设定在 `[0, 100]` 之间，其中 100 为系统默认值。 
 * @return   
 *         + 0: 成功调用。<br>
 *         + -2: 参数错误。
 */
/**
 * @locale en
 * @type api
 * @valid since 3.51
 * @brief Set the audio playback volume of the public stream.
 * @param publicStreamId ID of the public stream.
 * @param volume Ratio(%) of the audio playback volume to the original volume, in the range `[0, 400]`, with overflow protection. The default volume is 100. <br>
 *               To ensure the audio quality, the recommended range is `[0, 100]`.  
 * @return   
 *         + 0: Success. <br>
 *         + -2: Wrong parameter.
 */
- (int)setPublicStreamAudioPlaybackVolume:(NSString *_Nonnull)publicStreamId volume:(NSInteger)volume;

#pragma mark External Video Data
// @name custom video capture
/**
 * @locale zh
 * @type api
 * @region 自定义视频采集渲染
 * @brief 推送外部视频帧。
 * @param frame 该视频帧包含待 SDK 编码的视频数据，参考 ByteRTCVideoFrame{@link #ByteRTCVideoFrame}。
 * @return 方法调用结果：<br>
 *        + 0：成功；<br>
 *        + <0：失败。具体失败原因参看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus}。
 * @note 推送外部视频帧前，必须调用 setVideoSourceType:WithStreamIndex:{@link #ByteRTCVideo#setVideoSourceType:WithStreamIndex:} 开启外部视频源采集。
 */
/**
 * @locale en
 * @type api
 * @region Custom video capture rendering
 * @brief Pushes external video frames, encapsulated with ByteRTCVideoFrame.
 * @param frame This video frame contains video data to be encoded by the SDK. Refer to ByteRTCVideoFrame{@link #ByteRTCVideoFrame}.
 * @return API call result:<br>
 *        + 0: Success.<br>
 *        + <0: Failure. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for specific reasons.
 * @note Before pushing an external video frame, you must call setVideoSourceType:WithStreamIndex:{@link #ByteRTCVideo#setVideoSourceType:WithStreamIndex:} Turn on external video source capture.
 */
- (int)pushExternalVideoFrame:(ByteRTCVideoFrame * _Nonnull)frame;

#pragma mark External Audio Data
/**
 * @locale zh
 * @type api
 * @region 音频数据回调
 * @brief 设置并开启指定的音频数据帧回调
 * @param method 音频回调方法，参看 ByteRTCAudioFrameCallbackMethod{@link #ByteRTCAudioFrameCallbackMethod}。  <br>
 *               当音频回调方法设置为 `0`、`1`、`2`时，你需要在参数 `format` 中指定准确的采样率和声道，暂不支持设置为自动。  <br>
 *               当音频回调方法设置为 `3`时，暂不支持音频参数格式中设置准确的采样率和声道，你需要设置为自动。
 * @param format 音频参数格式，参看 ByteRTCAudioFormat{@link #ByteRTCAudioFormat}。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note 开启音频回调并调用 registerAudioFrameObserver:{@link #ByteRTCVideo#registerAudioFrameObserver:} 后，ByteRTCAudioFrameObserver{@link #ByteRTCAudioFrameObserver} 会收到对应的音频回调。两者调用顺序没有限制且相互独立。  
 */
/**
 * @locale en
 * @type api
 * @region Audio Data Callback
 * @brief Enable audio frames callback and set the format for the specified type of audio frames.
 * @param method Audio data callback method. See ByteRTCAudioFrameCallbackMethod{@link #ByteRTCAudioFrameCallbackMethod}. <br>
 *               If `method` is set as `0`, `1`, or `2`, set `format` to the accurate value listed in the audio parameters format.<br>
 *               If `method` is set as `3`, set `format` to `auto`.
 * @param format Audio parameters format. See ByteRTCAudioFormat{@link #ByteRTCAudioFormat}.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note After calling this API and registerAudioFrameObserver:{@link #ByteRTCVideo#registerAudioFrameObserver:}, ByteRTCAudioFrameObserver{@link #ByteRTCAudioFrameObserver} will receive the corresponding audio data callback. However, these two APIs are independent of each other and the calling order is not restricted. 
 */
- (int)enableAudioFrameCallback:(ByteRTCAudioFrameCallbackMethod) method format:(ByteRTCAudioFormat* _Nullable)format;
/**
 * @locale zh
 * @type api
 * @region 音频数据回调
 * @brief 关闭音频回调
 * @param method 音频回调方法，参看 ByteRTCAudioFrameCallbackMethod{@link #ByteRTCAudioFrameCallbackMethod}。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note 该方法需要在调用 enableAudioFrameCallback:format:{@link #ByteRTCVideo#enableAudioFrameCallback:format:} 之后调用。
 */
/**
 * @locale en
 * @type api
 * @region Audio Data Callback
 * @brief Disables audio data callback.
 * @param method Audio data callback method. See ByteRTCAudioFrameCallbackMethod{@link #ByteRTCAudioFrameCallbackMethod}.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note Call this API after calling enableAudioFrameCallback:format:{@link #ByteRTCVideo#enableAudioFrameCallback:format:}.
 */
- (int)disableAudioFrameCallback:(ByteRTCAudioFrameCallbackMethod) method;
/**
 * @locale zh
 * @type api
 * @region 音频数据回调
 * @brief 注册音频数据回调观察者。  
 * @param audioFrameObserver 音频数据观察者，参看 ByteRTCAudioFrameObserver{@link #ByteRTCAudioFrameObserver}。如果传入 null，则取消注册。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note 注册音频数据回调观察者并调用 enableAudioFrameCallback:format:{@link #ByteRTCVideo#enableAudioFrameCallback:format:} 后，ByteRTCAudioFrameObserver{@link #ByteRTCAudioFrameObserver} 会收到对应的音频回调。对回调中收到的音频数据进行处理，不会影响 RTC 的编码发送或渲染。
 */
/**
 * @locale en
 * @type api
 * @region Audio Data Callback
 * @brief Register an audio frame observer.  
 * @param audioFrameObserver Audio data callback observer. See ByteRTCAudioFrameObserver{@link #ByteRTCAudioFrameObserver}. Use `null` to cancel the registration.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note After calling this API and enableAudioFrameCallback:format:{@link #ByteRTCVideo#enableAudioFrameCallback:format:}, ByteRTCAudioFrameObserver{@link #ByteRTCAudioFrameObserver} receives the corresponding audio data callback. You can retrieve the audio data and perform processing on it without affecting the audio that RTC SDK uses to encode or render.
 */
- (int)registerAudioFrameObserver:(_Nullable id<ByteRTCAudioFrameObserver>) audioFrameObserver NS_SWIFT_NAME(registerAudioFrameObserver(_:));
/**
* @locale zh
* @type api
* @brief 注册自定义音频处理器。<br>
*        注册完成后，你可以调用 enableAudioProcessor:audioFormat:{@link #ByteRTCVideo#enableAudioProcessor:audioFormat:}，对本地采集到的音频进行处理，RTC SDK 将对处理后的音频进行编码和发送。也可以对接收到的远端音频进行自定义处理，RTC SDK 将对处理后的音频进行渲染。
* @param processor 自定义音频处理器，详见 ByteRTCAudioFrameProcessor{@link #ByteRTCAudioFrameProcessor}。<br>
*        SDK 只持有 processor 的弱引用，你应保证其生命周期。需要取消注册时，设置此参数为 nullptr。<br>

 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note
 * + 重复调用此接口时，仅最后一次调用生效。<br>
 * + 更多相关信息，详见[音频自定义处理](https://www.volcengine.com/docs/6348/80635)。
*/
/**
* @locale en
* @type api
* @brief  Register a custom audio preprocessor. <br>
*         After that, you can call enableAudioProcessor:audioFormat:{@link #ByteRTCVideo#enableAudioProcessor:audioFormat:} to process the audio streams that either captured locally or received from the remote side. RTC SDK then encodes or renders the processed data.
* @param processor Custom audio processor. See ByteRTCAudioFrameProcessor{@link #ByteRTCAudioFrameProcessor}。<br>
*        SDK only holds weak references to the processor, you should guarantee its Life Time. To cancel registration, set the parameter to nullptr.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details.
* @note 
* + When this interface is repeatedly called, only the last call takes effect.<br>
* + Refer to [Custom Audio Processing](https://docs.byteplus.com/en/byteplus-rtc/docs/80635) for more information.
*/
- (int)registerAudioProcessor:(_Nullable id<ByteRTCAudioFrameProcessor>)processor;
/**
 * @locale zh
 * @type api
 * @brief 设置并开启指定的音频帧回调，进行自定义处理。
 * @param method 音频帧类型，参看 ByteRTCAudioFrameMethod{@link #ByteRTCAudioFrameMethod}。可多次调用此接口，处理不同类型的音频帧。  <br>
 *        选择不同类型的音频帧将收到对应的回调：  <br>
 *        + 选择本地采集的音频时，会收到 onProcessRecordAudioFrame:{@link #ByteRTCAudioFrameProcessor#onProcessRecordAudioFrame:}。<br>
 *        + 选择远端音频流的混音音频时，会收到 onProcessPlayBackAudioFrame:{@link #ByteRTCAudioFrameProcessor#onProcessPlayBackAudioFrame:}。 <br>
 *        + 选择远端音频流时，会收到 onProcessRemoteUserAudioFrame:audioFrame:{@link #ByteRTCAudioFrameProcessor#onProcessRemoteUserAudioFrame:audioFrame:}。 <br>
 *        + 选择软件耳返音频时，会收到 onProcessEarMonitorAudioFrame:{@link #ByteRTCAudioFrameProcessor#onProcessEarMonitorAudioFrame:}。(仅适用于 iOS 平台)<br>
 *        + 选择屏幕共享音频流时，会收到 onProcessScreenAudioFrame:{@link #ByteRTCAudioFrameProcessor#onProcessScreenAudioFrame:}。
 * @param format 设定自定义处理时获取的音频帧格式，参看 ByteRTCAudioFormat{@link #ByteRTCAudioFormat}。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note 
 *        + 在调用此接口前，你需要调用 registerAudioProcessor:{@link #ByteRTCVideo#registerAudioProcessor:} 注册自定义音频处理器。<br>
 *        + 要关闭音频自定义处理，调用 disableAudioProcessor:{@link #ByteRTCVideo#disableAudioProcessor:}。
 */
/**
 * @locale en
 * @type api
 * @brief Enable audio frames callback for custom processing and set the format for the specified type of audio frames.
 * @param  method The types of audio frames. See ByteRTCAudioFrameMethod{@link #ByteRTCAudioFrameMethod}. Set this parameter to process multiple types of audio. <br>
 *        With different values, you will receive the corresponding callback: <br>
 *        + For locally captured audio, you will receive onProcessRecordAudioFrame:{@link #ByteRTCAudioFrameProcessor#onProcessRecordAudioFrame:}.  <br>
 *        + For mixed remote audio, you will receive onProcessPlayBackAudioFrame:{@link #ByteRTCAudioFrameProcessor#onProcessPlayBackAudioFrame:}. <br>
 *        + For audio from remote users, you will receive onProcessRemoteUserAudioFrame:audioFrame:{@link #ByteRTCAudioFrameProcessor#onProcessRemoteUserAudioFrame:audioFrame:}. <br>
 *        + For SDK-level in-ear monitoring audio, you will receive onProcessEarMonitorAudioFrame:{@link #ByteRTCAudioFrameProcessor#onProcessEarMonitorAudioFrame:} (Only on iOS).<br>
 *        + For shared-screen audio, you will receive onProcessScreenAudioFrame:{@link #ByteRTCAudioFrameProcessor#onProcessScreenAudioFrame:}.
 * @param  format The format of the returned audio frame. See ByteRTCAudioFormat{@link #ByteRTCAudioFormat}.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note 
 *        + Before calling this API, call registerAudioProcessor:{@link #ByteRTCVideo#registerAudioProcessor:} to register a processor. <br>
 *        + To disable custom audio processing, call disableAudioProcessor:{@link #ByteRTCVideo#disableAudioProcessor:}.
 */
- (int)enableAudioProcessor:(ByteRTCAudioFrameMethod)method
                 audioFormat:(ByteRTCAudioFormat *_Nullable)format;
/**
* @locale zh
* @type api
* @brief 关闭自定义音频处理。
* @param method 音频帧类型，参看 ByteRTCAudioFrameMethod{@link #ByteRTCAudioFrameMethod}。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
*/
/**
* @locale en
* @type api
* @brief Disable custom audio processing.
* @param method Audio Frame type. See ByteRTCAudioFrameMethod{@link #ByteRTCAudioFrameMethod}.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
*/
- (int)disableAudioProcessor:(ByteRTCAudioFrameMethod)method;
/**
 * @locale zh
 * @type api
 * @region 自定义音频采集渲染
 * @brief 推送自定义采集的音频数据到 RTC SDK。
 * @param audioFrame 音频数据帧，详见 ByteRTCAudioFrame{@link #ByteRTCAudioFrame}<br>
 *        + 音频采样格式为 S16。音频缓冲区内的数据格式必须为 PCM 数据，其容量大小应该为 audioFrame.samples × audioFrame.channel × 2。<br>
 *        + 必须指定具体的采样率和声道数，不支持设置为自动。
 * @return  方法调用结果  <br>
 *          + 0: 设置成功  <br>
 *          + < 0: 设置失败  
 * @note  
 *       + 推送外部音频数据前，必须先调用 setAudioSourceType:{@link #ByteRTCVideo#setAudioSourceType:} 开启自定义采集。<br>
 *       + 你必须每隔 10 毫秒推送一次外部采集的音频数据。单次推送的 samples (音频采样点个数）应该为 audioFrame.sampleRate / 100。比如设置采样率为 48000 时， 每次应该推送 480 个采样点。
 */
 /**
  * @locale en
  * @type api
  * @region Custom Audio Capture and Rendering
  * @brief Push custom captured audio data to the RTC SDK.
  * @param audioFrame Audio data frame. See ByteRTCAudioFrame{@link #ByteRTCAudioFrame}
  * @return 
  *         + 0: Success <br>
  *         + < 0: Failure 
  * @note   
  *        + Before pushing external audio data, you must call setAudioSourceType:{@link #ByteRTCVideo#setAudioSourceType:} to enable custom audio capture. <br>
  *        + You must push custom captured audio data every 10 milliseconds. The samples (number of audio sampling points) of a single push should be `audioFrame.sample Rate/100`. For example, when the sampling rate is set to 48000, data of 480 sampling points should be pushed each time. <br>
  *        + Audio sampling format must be S16. The data format in the audio buffer must be PCM, and its capacity size should be `audioFrame.samples × audioFrame.channel × 2`.
  */
- (int)pushExternalAudioFrame:(ByteRTCAudioFrame * _Nonnull) audioFrame;
/**
 * @locale zh
 * @type api
 * @region 自定义音频采集渲染
 * @brief 拉取下行音频数据用于自定义音频渲染。<br>
 *        调用该方法后，SDK 会主动拉取待播放的音频数据，包括远端已解码和混音后的音频数据，用于外部播放。
 * @param audioFrame 音频数据帧，详见 ByteRTCAudioFrame{@link #ByteRTCAudioFrame}
 * @return  方法调用结果  <br>
 *        + 0: 设置成功  <br>
 *        + < 0: 设置失败  
 * @note  
 *       + 拉取外部音频数据前，必须先调用 setAudioRenderType:{@link #ByteRTCVideo#setAudioRenderType:} 开启自定义渲染。<br>
 *       + 由于 RTC SDK 的帧长为 10 毫秒，你应当每隔 10 毫秒拉取一次音频数据。确保音频采样点数（sample）x 拉取频率等于 audioFrame 的采样率 （sampleRate）。如设置采样率为 48000 时，每 10 毫秒调用本接口拉取数据，每次应拉取 480 个采样点。  <br>
 *       + 音频采样格式为 S16。音频缓冲区内的数据格式必须为 PCM 数据，其容量大小应该为 audioFrame.samples × audioFrame.channel × 2。  
 */
 /**
  * @locale en
  * @type api
  * @region Custom audio capture and rendering
  * @brief Pulls audio data for custom rendering.
  * @param audioFrame Audio data frame. See ByteRTCAudioFrame{@link #ByteRTCAudioFrame}
  * @return 
  *           + 0: Success <br>
  *           + < 0: Failure 
  * @note   
  *        + Before pulling custom audio data, you must call setAudioRenderType:{@link #ByteRTCVideo#setAudioRenderType:} to enable custom audio capture and rendering. <br>
  *        + You should pull audio data every 10 milliseconds since the duration of a RTC SDK audio frame is 10 milliseconds. Samples x call frequency = audioFrame's sample rate. Assume that the sampling rate is set to 48000, call this API every 10 ms, so that 480 sampling points should be pulled each time. <br>
  *        + The audio sampling format is S16. The data format in the audio buffer is PCM, and its capacity size is `audioFrame.samples × audioFrame.channel × 2`. 
  */
- (int)pullExternalAudioFrame:(ByteRTCAudioFrame * _Nonnull) audioFrame;
/**
 * @locale zh
 * @type api
 * @region 引擎管理
 * @brief 设置业务标识参数  <br>
 *        可通过 businessId 区分不同的业务场景。businessId 由客户自定义，相当于一个“标签”，可以分担和细化现在 AppId 的逻辑划分的功能，但不需要鉴权。
 * @param businessId  <br>
 *        用户设置的自己的 businessId 值<br>
 *        businessId 只是一个标签，颗粒度需要用户自定义。
 * @return  
 *        + 0： 成功  <br>
 *        + < 0： 失败  <br>
 *        + -6001： 用户已经在房间中。  <br>
 *        + -6002： 输入非法，合法字符包括所有小写字母、大写字母和数字，除此外还包括四个独立字符分别是：英文句号，短横线，下划线和 @ 。
 * @note  
 *        + 需要在调用 joinRoom:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoom:userInfo:roomConfig:} 进房之前调用，进房之后调用该方法无效。
 * @list 引擎管理
 * @order 20
 */
/**
 * @locale en
 * @type api
 * @region Engine management
 * @brief Sets the business ID   <br>
 *        You can use businessId to distinguish different business scenarios. You can customize your businessId to serve as a sub AppId, which can share and refine the function of the AppId, but it does not need authentication.
 * @param businessId   <br>
 *        Your customized businessId<br>
 *        BusinessId is a tag, and you can customize its granularity.
 * @return   
 *         + 0: Success <br>
 *         + < 0: Failure <br>
 *         + -6001: The user is already in the room. <br>
 *         + -6002: The input is invalid. Legal characters include all lowercase letters, uppercase letters, numbers, and four other symbols, including '.', '-','_', and '@'.
 * @note   
 *         + You must call this API before the joinRoom:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoom:userInfo:roomConfig:} API, otherwise it will be invalid.
 * @list Engine Management
 * @order 20
 */
- (int)setBusinessId:(NSString* _Nullable)businessId;
/**
 * @locale zh
 * @type api
 * @region 引擎管理
 * @brief 通话结束，将用户反馈的问题上报到 RTC。 
 * @param types 预设问题列表，参看 ByteRTCProblemFeedbackOption{@link #ByteRTCProblemFeedbackOption}  
 * @param info 预设问题以外的其他问题的具体描述，房间信息。参看 ByteRTCProblemFeedbackInfo{@link #ByteRTCProblemFeedbackInfo}   
 * @return 
 *         + 0: 上报成功  <br>
 *         + -1: 上报失败，还没加入过房间 <br>
 *         + -2: 上报失败，数据解析错误  <br>
 *         + -3: 上报失败，字段缺失  
 * @note 
 *         + 你可以在 [RTC 控制台](https://console.volcengine.com/rtc/callQualityRTC/feedback)上查看用户通过此接口提交的反馈详情和整体趋势。<br>
 *         + 如果用户上报时在房间内，那么问题会定位到用户当前所在的一个或多个房间；如果用户上报时不在房间内，那么问题会定位到引擎此前退出的房间。
 * @list 引擎管理
 * @order 10
 */
/**
 * @locale en
 * @type api
 * @region Engine management
 * @brief The call ends and the user feedback problem is reported to RTC 
 * @param types The list of preset problems. See ByteRTCProblemFeedbackOption{@link #ByteRTCProblemFeedbackOption} 
 * @param info Specific description of other problems other than the preset problem, and room's information. See ByteRTCProblemFeedbackInfo{@link #ByteRTCProblemFeedbackInfo} 
 * @return  
 *          + 0: Report successfully <br>
 *          + -1: Failed to report, haven't joined the room yet <br>
 *          + -2: Failed to report, data analysis error <br>
 *          + -3: Failed to report, missing fields 
 * @note If the user is in the room when reporting, the report leads to the room / rooms where the user is currently located;<br>
 *        If the user is not in the room when reporting, the report leads to the previously exited Room.
 * @list Engine Management
 * @order 10
 */
- (int)feedback:(ByteRTCProblemFeedbackOption)types info:(ByteRTCProblemFeedbackInfo* _Nullable)info;

/**
 * @locale zh
 * @type api
 * @valid since 353
 * @brief 获取 C++ 层 [IRTCVideo 句柄](https://www.volcengine.com/docs/6348/70095#irtcvideo)。
 * @return 
 *         + >0：方法调用成功, 返回 C++ 层 `IRTCVideo` 的地址。<br>
 *         + NULL：方法调用失败
 * @note 在一些场景下，获取 C++ 层 `IRTCVideo`，并通过其完成操作，相较于通过 OC 封装层完成有显著更高的执行效率。典型的场景有：视频/音频帧自定义处理，音视频通话加密等。
 */
/**
 * @locale en
 * @type api
 * @brief Get [IRTCVideo](https://docs.byteplus.com/byteplus-rtc/docs/70095#irtcvideo) in C++ layer.
 * @return 
 *         + >0：Success. Return the address of `IRTCVideo` in C++ layer.<br>
 *         + NULL：Failure.
 * @note In some scenarios, getting and working with `IRTCVideo` in C++ layer has much higher execution efficiency than through the OC encapsulation layer. Typical scenarios include: custom processing of video/audio frames, encryption of audio and video calls, etc.
 */
- (void * _Nullable) getNativeHandle;

#pragma mark Fallback Related
/**
 * @locale zh
 * @type api
 * @region 音视频回退
 * @brief 设置发布的音视频流的回退选项。  <br>
 *        你可以调用该接口设置网络不佳或设备性能不足时从大流起进行降级处理，以保证通话质量。
 * @param option 本地发布的音视频流回退选项，参看 ByteRTCPublishFallbackOption{@link #ByteRTCPublishFallbackOption}。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note  
 *        + 该方法仅在调用 enableSimulcastMode:{@link #ByteRTCVideo#enableSimulcastMode:} 开启了发送多路视频流的情况下生效。  <br>
 *        + 该方法必须在进房前设置，进房后设置或更改设置无效。  <br>
 *        + 调用该方法后，如因性能或网络不佳产生发布性能回退或恢复，本端会提前收到 rtcEngine:onPerformanceAlarms:roomId:reason:sourceWantedData:{@link #ByteRTCVideoDelegate#rtcEngine:onPerformanceAlarms:roomId:reason:sourceWantedData:} 回调发出的告警，以便采集设备配合调整。<br>
 *        + 设置回退后，本地发布的音视频流发生回退或从回退中恢复时，远端会收到 rtcEngine:onSimulcastSubscribeFallback:{@link #ByteRTCVideoDelegate#rtcEngine:onSimulcastSubscribeFallback:} 回调，通知该情况。  <br>
 *        + 你可以调用客户端 API 或者在服务端下发策略设置回退。当使用服务端下发配置实现时，下发配置优先级高于在客户端使用 API 设定的配置。
 */
/**
 * @locale en
 * @type api
 * @region Audio & Video Fallback
 * @brief Sets the fallback option for published audio & video streams.   <br>
 *        You can call this API to set whether to automatically lower the resolution you set of the published streams under limited network conditions.
 * @param option Fallback option, see ByteRTCPublishFallbackOption{@link #ByteRTCPublishFallbackOption}.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note  
 *         + This API only works after you call enableSimulcastMode:{@link #ByteRTCVideo#enableSimulcastMode:} to enable the mode of publishing multiple streams. <br>
 *         + You must call this API before the user enters the room. <br>
 *         + After calling this method, if there is a performance degradation or recovery due to poor performance or network conditions, the local end will receive early warnings through the rtcEngine:onPerformanceAlarms:roomId:reason:sourceWantedData:{@link #ByteRTCVideoDelegate#rtcEngine:onPerformanceAlarms:roomId:reason:sourceWantedData:} callback to adjust the capture device. <br>
 *         + After setting the fallback option, the user subscribed to the audio/video stream will receive rtcEngine:OnSimulcastSubscribeFallback:{@link #ByteRTCVideoDelegate#rtcEngine:onSimulcastSubscribeFallback:} when the audio/video stream published by the local user falls back or resumes from the fallback.  <br>
 *         + You can alternatively set fallback options in the console, which is of higher priority.
 */
- (int)setPublishFallbackOption:(ByteRTCPublishFallbackOption)option;
/**
 * @locale zh
 * @type api
 * @region 音视频回退
 * @brief 设置订阅的音视频流的回退选项。 <br>
 *        你可调用该接口设置网络不佳或设备性能不足时允许订阅流进行降级或只订阅音频流，以保证通话流畅。
 * @param option 订阅的音视频流回退选项，参看 ByteRTCSubscribeFallbackOption{@link #ByteRTCSubscribeFallbackOption}。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note  
 *        + 你必须在进房前设置，进房后设置或更改设置无效。  <br>
 *        + 设置回退选项后，订阅的音视频流发生回退或从回退中恢复时，会收到 rtcEngine:onSimulcastSubscribeFallback:{@link #ByteRTCVideoDelegate#rtcEngine:onSimulcastSubscribeFallback:} 和 rtcEngine:onRemoteVideoSizeChanged:withFrameInfo:{@link #ByteRTCVideoDelegate#rtcEngine:onRemoteVideoSizeChanged:withFrameInfo:} 回调通知。  <br>
 *        + 你可以调用 API 或者在服务端下发策略设置回退。当使用服务端下发配置实现时，下发配置优先级高于在客户端使用 API 设定的配置。
 */
/**
 * @locale en
 * @type api
 * @region Audio & Video Fallback
 * @brief Sets the fallback option for subscribed RTC streams.   <br>
 *        You can call this API to set whether to lower the resolution of currently subscribed stream under limited network conditions.
 * @param option Fallback option, see ByteRTCSubscribeFallbackOption{@link #ByteRTCSubscribeFallbackOption} for more details.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note  
 *         + You must call this API before enterting the room.  <br>
 *         + When the fallback option is set, the local user will receive rtcEngine:onSimulcastSubscribeFallback:{@link #ByteRTCVideoDelegate#rtcEngine:onSimulcastSubscribeFallback:} and rtcEngine:onRemoteVideoSizeChanged:withFrameInfo:{@link #ByteRTCVideoDelegate#rtcEngine:onRemoteVideoSizeChanged:withFrameInfo:} when the subscribed audio/video stream falls back or resumes from a fallback.  <br>
 *         + You can alternatively set fallback options in the console, which is of higher priority.
 */
- (int)setSubscribeFallbackOption:(ByteRTCSubscribeFallbackOption)option;

/**
 * @locale zh
 * @type api
 * @region 音视频回退
 * @brief 设置用户优先级。
 * @param priority 远端用户的优先级, 详见枚举类型 ByteRTCRemoteUserPriority{@link #ByteRTCRemoteUserPriority}
 * @param roomId 房间 ID
 * @param uid 远端用户的 ID
 * @return + 0：方法调用成功  <br>
 *         + < 0：方法调用失败  
 * @note  
 *        + 该方法与 setSubscribeFallbackOption:{@link #setSubscribeFallbackOption:}  搭配使用。  <br>
 *        + 如果开启了订阅流回退选项，弱网或性能不足时会优先保证收到的高优先级用户的流的质量。  <br>
 *        + 该方法在进房前后都可以使用，可以修改远端用户的优先级。
 */
/**
 * @locale en
 * @type api
 * @region  audio & video fallback
 * @brief Sets user priority
 * @param priority Priority of remote user. See enumeration type ByteRTCRemoteUserPriority{@link #ByteRTCRemoteUserPriority}
 * @param roomId Room ID
 * @param uid ID of remote user
 * @return  + 0: Success. <br>
 *          + < 0: failure 
 * @note   
 *         + This method is used with setSubscribeFallbackOption:{@link #setSubscribeFallbackOption:}. <br>
 *         + If the subscription flow fallback option is turned on, weak connections or insufficient performance will give priority to ensuring the quality of the flow received by high-priority users. <br>
 *         + This method can be used before and after entering the room, and the priority of the remote user can be modified.
 */
- (int)setRemoteUserPriority:(ByteRTCRemoteUserPriority)priority
                         InRoomId:(NSString *_Nonnull)roomId
                         uid:(NSString *_Nonnull)uid NS_SWIFT_NAME(setRemoteUserPriority(_:InRoomId:uid:));
#pragma mark AES Related
/**
 * @locale zh
 * @type api
 * @region 加密
 * @brief 设置传输时使用内置加密的方式。
 * @param encrypt_type 内置加密算法，详见 ByteRTCEncryptType{@link #ByteRTCEncryptType}
 * @param key 加密密钥，长度限制为 36 位，超出部分将会被截断
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note  
 *       + 使用传输时内置加密时，使用此方法；如果需要使用传输时自定义加密，参看 onEncryptData:{@link #ByteRTCEncryptHandler#onEncryptData:}。<br>
 *         内置加密和自定义加密互斥，根据最后一个调用的方法确定传输加密的方案。  <br>
 *       + 该方法必须在进房之前调用，可重复调用，以最后调用的参数作为生效参数。  
 */
/**
 * @locale en
 * @type api
 * @region Encryption
 * @brief Sets the way to use built-in encryption when transmitting.
 * @param encrypt_type Built-in encryption algorithm. See ByteRTCEncryptType{@link #ByteRTCEncryptType}
 * @param key Encryption key, limited to 36 bits in length, beyond which it will be truncated
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note   
 *        + Use this method when using built-in encryption when transmitting; if you need to use transmission See onEncryptData:{@link #ByteRTCEncryptHandler#onEncryptData:}.<br>
 *         Built-in encryption and custom encryption mutex, determine the scheme of transmission encryption according to the last called method. <br>
 *        + This method must be called before entering the room, and can be called repeatedly, taking the last called parameter as the effective parameter. 
 */
- (int)setEncryptInfo:(ByteRTCEncryptType)encrypt_type key:(NSString * _Nonnull)key;
/**
 * @locale zh
 * @type api
 * @region 加密
 * @brief 设置自定义加密和解密方式。
 * @param handler 自定义加密 handler，需要实现里面的加密和解密方法。参看 ByteRTCEncryptHandler{@link #ByteRTCEncryptHandler}。  
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note 
 *       + 该方法与 setEncryptInfo:key:{@link #setEncryptInfo:key:} 为互斥关系，即按照调用顺序，最后一个调用的方法为最终生效的版本。  <br>
 *       + 该方法必须在调用 joinRoom:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoom:userInfo:roomConfig:} 之前调用，可重复调用，以最后调用的参数作为生效参数。  <br>
 *       + 无论加密或者解密，其对原始数据的长度修改，需要控制在 180% 之间，即如果输入数据为 100 字节，则处理完成后的数据必须不超过 180 字节，如果加密或解密结果超出该长度限制，则该音视频帧可能会被丢弃。  <br>
 *       + 数据加密/解密为串行执行，因而视实现方式不同，可能会影响到最终渲染效率，是否使用该方法，需要由使用方谨慎评估。  
 */
/**
 * @locale en
 * @type api
 * @region  encryption
 * @brief Sets custom encryption and decryption methods.
 * @param handler Custom encryption handler, which needs to implement the encryption and decryption method. See ByteRTCEncryptHandler{@link #ByteRTCEncryptHandler}. 
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note 
 *        + The method and setEncryptInfo:key:{@link #setEncryptInfo:key:} are mutually exclusive relationships, that is, according to the call order, the last call method takes effect version. <br>
 *        + This method must be called before calling joinRoom:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoom:userInfo:roomConfig:}, which can be called repeatedly, taking the last called parameter as the effective parameter. <br>
 *        + Whether encrypted or decrypted, the length of the modified data needs to be controlled under 180%. That is, if the input data is 100 bytes, the processed data must be less than 180 bytes. If the encryption or decryption result exceeds the limit, the audio & video frame may be discarded. <br>
 *        + Data encryption/decryption is performed serially, so depending on the implementation The method may affect the final rendering efficiency. Whether to use this method needs to be carefully evaluated by the user. 
 */
- (int)setCustomizeEncryptHandler:(id<ByteRTCEncryptHandler> _Nullable)handler NS_SWIFT_NAME(setCustomizeEncryptHandler(_:));

#pragma mark - Extention Methods
/**
 * @locale zh
 * @type api
 * @region 房间管理
 * @brief 创建房间实例。<br>
 *        调用此方法仅返回一个房间实例，你仍需调用 joinRoom:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoom:userInfo:roomConfig:} 才能真正地创建/加入房间。<br>
 *        多次调用此方法以创建多个 ByteRTCRoom{@link #ByteRTCRoom} 实例。分别调用各 ByteRTCRoom 实例中的 joinRoom:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoom:userInfo:roomConfig:} 方法，同时加入多个房间。<br>
 *        多房间模式下，用户可以同时订阅各房间的音视频流。
 * @param roomId 标识通话房间的房间 ID。该字符串符合正则表达式：`[a-zA-Z0-9_@\-\.]{1,128}`。
 * @return 创建的 ByteRTCRoom{@link #ByteRTCRoom} 房间实例。
 * @note 
 *        + 如果需要加入的房间已存在，你仍需先调用本方法来获取 ByteRTCRoom 实例，再调用 joinRoom:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoom:userInfo:roomConfig:} 加入房间。<br>
 *        + 请勿使用同样的 roomId 创建多个房间，否则后创建的房间实例会替换先创建的房间实例。<br>
 *        + 如果你需要在多个房间发布音视频流，无须创建多房间，直接调用 startForwardStreamToRooms:{@link #ByteRTCRoom#startForwardStreamToRooms:} 开始跨房间转发媒体流。
 */
/**
 * @locale en
 * @type api
 * @region Room Management
 * @brief Create a room instance.<br>
 *        This API only returns a room instance. You still need to call joinRoom:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoom:userInfo:roomConfig:} to actually create/join the room.<br>
 *        Each call of this API creates one ByteRTCRoom{@link #ByteRTCRoom} instance. Call this API as many times as the number of rooms you need, and then call joinRoom:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoom:userInfo:roomConfig:} of each RTCRoom instance to join multiple rooms at the same time.<br>
 *        In multi-room mode, a user can subscribe to media streams in the joined rooms at the same time.
 * @param roomId The string matches the regular expression: `[a-zA-Z0-9_@\-\.]{1,128}`.
 * @return ByteRTCRoom{@link #ByteRTCRoom} instance.
 * @note 
 *       + If the room that you wish to join already exists, you still need to call this API first to create the ByteRTCRoom instance, and then call joinRoom:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoom:userInfo:roomConfig:}.<br>
 *       + Do not create multiple rooms with the same roomId, otherwise the newly created room instance will replace the old one.<br>
 *       + To forward streams to the other rooms, call startForwardStreamToRooms:{@link #ByteRTCRoom#startForwardStreamToRooms:} instead of enabling Multi-room mode.
 */
- ( ByteRTCRoom * _Nullable)createRTCRoom:(NSString * _Nonnull)roomId;
#pragma mark - ScreenCapture
/**
 * @locale zh
 * @type api
 * @region 屏幕共享
 * @brief 推送外部屏幕采集帧
 * @param frame 该视频帧包含待 SDK 编码的视频数据<br>
 *              支持的视频像素格式：NV12、BGRA、ARGB
 * @param pts 每一帧的时间戳，单位 ms
 * @param rotation 帧的旋转角度包含: 0, 90, 180, 270
 * @return 方法调用结果：<br>
 *        + 0：成功；<br>
 *        + <0：失败。具体失败原因参看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus}。
 * @note 屏幕采集分为内部采集和外部采集，本方法属于外部采集。
 */
/**
 * @locale en
 * @type api
 * @region  screen sharing
 * @brief  Push external screen acquisition frame
 * @param frame  The video frame contains the video data to be encoded by the SDK<br>
 *               Supported video pixel format: NV12, BGRA, ARGB.
 * @param pts  Timestamp of each frame, the rotation angle of the unit ms
 * @param rotation  Frame contains: 0, 90, 180, 270
 * @return API call result:<br>
 *        + 0: Success.<br>
 *        + <0: Failure. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for specific reasons.
 * @note  Screen acquisition is divided into internal acquisition and external acquisition, this method belongs to external acquisition.
 */
- (int)pushScreenVideoFrame:(CVPixelBufferRef _Nonnull )frame time:(CMTime)pts rotation:(int)rotation;
/**
 * @locale zh
 * @hidden(macOS)
 * @type api
 * @region 屏幕共享
 * @brief 设置 Extension 配置项。你必须在使用屏幕内部采集功能前，设置使用的 Extension。
 * @param groupId 你的应用和 Extension 应该归属于同一个 App Group，此处需要传入 Group Id。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note 必须在调用 createRTCVideo:delegate:parameters:{@link #ByteRTCVideo#createRTCVideo:delegate:parameters:} 之后立即调用此方法。在引擎实例的生命周期中，此方法只需要调用一次。  
 */
/**
 * @locale en
 * @hidden(macOS)
 * @type api
 * @region  Screen Sharing
 * @brief  Set Extension configuration. It should be set before capturing screen internally.
 * @param groupId  Your app and Extension should belong to the same App Group. You need to put in their Group ID here.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note You must call this API immediately after calling createRTCVideo:delegate:parameters:{@link #ByteRTCVideo#createRTCVideo:delegate:parameters:}. You only need to call this API once in the life cycle of the engine instance. 
 */
- (int)setExtensionConfig:(NSString *_Nullable)groupId;
/**
 * @locale zh
 * @type api
 * @hidden(macOS)
 * @region 屏幕共享
 * @brief 使用 RTC SDK 内部采集模块开始采集屏幕音频流和（或）视频流。
 * @param type 媒体类型，参看 ByteRTCScreenMediaType{@link #ByteRTCScreenMediaType}。
 * @param bundleId 绑定 Extension 的 Bundle ID，绑定后应用中共享屏幕的选择列表中只展示你的 Extension 可供选择。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note 
 *      + 调用本接口时，采集模式应为内部模式。在外部采集模式下调用无效，并将触发 rtcEngine:onVideoDeviceWarning:deviceType:deviceWarning:{@link #ByteRTCVideoDelegate#rtcEngine:onVideoDeviceWarning:deviceType:deviceWarning:} 或 rtcEngine:onAudioDeviceWarning:deviceType:deviceWarning:{@link #ByteRTCVideoDelegate#rtcEngine:onAudioDeviceWarning:deviceType:deviceWarning:} 回调。<br>
 *      + 当从 iOS 控制中心发起屏幕采集时无需调用本方法。 <br>
 *      + 采集后，你还需要调用 publishScreen:{@link #ByteRTCRoom#publishScreen:} 发布采集到的屏幕音视频。<br>
 *      + 开启屏幕音频/视频采集成功后，本地用户会收到 rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:} 和 rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:} 回调。
 */
/**
 * @locale en
 * @type api
 * @hidden(macOS)
 * @region Screen Sharing
 * @brief Starts capturing the screen audio and/or video stream with the RTC SDK internal module.
 * @param type Media type. See ByteRTCScreenMediaType{@link #ByteRTCScreenMediaType}.
 * @param bundleId The bundle ID of the Extension, which is used to only display your Extension in your app.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note 
 *      + The call of this API takes effects only when you are using RTC SDK to record screen. You will get a warning by rtcEngine:onVideoDeviceWarning:deviceType:deviceWarning:{@link #ByteRTCVideoDelegate#rtcEngine:onVideoDeviceWarning:deviceType:deviceWarning:} or rtcEngine:onAudioDeviceWarning:deviceType:deviceWarning:{@link #ByteRTCVideoDelegate#rtcEngine:onAudioDeviceWarning:deviceType:deviceWarning:} after calling this API when the source is set to an external recorder.<br>
 *      + If you start the Extension from the iOS control center, this API do not need to be called. <br>
 *      + After the streams are captured, you need to call publishScreen:{@link #ByteRTCRoom#publishScreen:} to push the streams to the remote end. <br>
 *      + You will receive rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:} and rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:} when the capturing is started. 
 */
- (int)startScreenCapture:(ByteRTCScreenMediaType) type bundleId:(NSString *_Nullable)bundleId;
/**
 * @locale zh
 * @hidden(macOS)
 * @type api
 * @region 屏幕共享
 * @brief 更新内部屏幕采集时采集的媒体类型。
 * @param type 媒体类型，参看 ByteRTCScreenMediaType{@link #ByteRTCScreenMediaType}。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note 
 *      + 你需在开启屏幕视频流采集后调用该方法。<br>
 *      + 本地用户会收到 rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:} 或 rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:} 回调。
 */
/**
 * @locale en
 * @hidden(macOS)
 * @type api
 * @region Screen Sharing
 * @brief Updates the media type of the internal screen capture.
 * @param type Media type. See ByteRTCScreenMediaType{@link #ByteRTCScreenMediaType}.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note 
 *      + Call this API after starting screen capture. <br>
 *      + You will receive rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:} or rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:}. 
 */
- (int)updateScreenCapture:(ByteRTCScreenMediaType) type;
/**
 * @locale zh
 * @hidden(macOS)
 * @type api
 * @region 屏幕共享
 * @brief 在屏幕共享时，停止使用 RTC SDK 内部采集方式采集屏幕音视频。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note 
 *     + 调用本接口时，采集模式应为内部模式。在外部采集模式下调用无效，并将触发 rtcEngine:onVideoDeviceWarning:deviceType:deviceWarning:{@link #ByteRTCVideoDelegate#rtcEngine:onVideoDeviceWarning:deviceType:deviceWarning:} 或 rtcEngine:onAudioDeviceWarning:deviceType:deviceWarning:{@link #ByteRTCVideoDelegate#rtcEngine:onAudioDeviceWarning:deviceType:deviceWarning:} 回调。<br>
 *     + 当从 iOS 控制中心发起屏幕采集时无需调用本方法。 <br>
 *     + 本方法只会停止本地屏幕采集，并不会影响屏幕流的发布状态。<br>
 *     + 本地用户会收到 rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:} 和 rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:} 的回调。 
 */
/**
 * @locale en
 * @hidden(macOS)
 * @type api
 * @region Screen Sharing
 * @brief Stop internal screen capture.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note 
 *      + The call of this API takes effects only when you are using RTC SDK to record screen. You will get a warning by rtcEngine:onVideoDeviceWarning:deviceType:deviceWarning:{@link #ByteRTCVideoDelegate#rtcEngine:onVideoDeviceWarning:deviceType:deviceWarning:} or rtcEngine:onAudioDeviceWarning:deviceType:deviceWarning:{@link #ByteRTCVideoDelegate#rtcEngine:onAudioDeviceWarning:deviceType:deviceWarning:} after calling this API when the source is set to an external recorder.<br>
 *      + Calling this API changes the capturing status without affecting the publishing status.  <br>
 *      + You will receive rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:} and rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:}. 
 */
- (int)stopScreenCapture;
/**
 * @locale zh
 * @hidden(macOS)
 * @type api
 * @region 屏幕共享
 * @brief 向屏幕共享 Extension 发送自定义消息
 * @param messsage 发送给 Extension 的消息内容
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note 
 *       + 在 startScreenCapture:bundleId:{@link #ByteRTCVideo#startScreenCapture:bundleId:} 后调用该方法。<br>
 *       + 通过 onReceiveMessageFromApp:{@link #ByteRtcScreenCapturerExtDelegate#onReceiveMessageFromApp:} 回调发送的消息。
 */
/**
 * @locale en
 * @hidden(macOS)
 * @type api
 * @region  Screen Sharing
 * @brief Sends message to screen capture Extension
 * @param messsage  Message sent to the Extension
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note 
 *       + Call this API after calling startScreenCapture:bundleId:{@link #ByteRTCVideo#startScreenCapture:bundleId:}.<br>
 *       + The extension will receive onReceiveMessageFromApp:{@link #ByteRtcScreenCapturerExtDelegate#onReceiveMessageFromApp:} when the message is sent.
 */
- (int)sendScreenCaptureExtensionMessage:(NSData *_Nonnull) messsage;
/**
 * @locale zh
 * @hidden for internal use only
 * @type api
 * @brief 音频设备管理接口创建，该接口不依赖引擎
 * @param handler 音频设备的事件回调，参看 ByteRTCAudioDeviceEventHandler{@link #ByteRTCAudioDeviceEventHandler}
 * @return 音频设备管理接口
 */
/**
 * @locale en
 * @hidden for internal use only
 * @type api
 * @brief Audio Facility Management interface is created, this interface does not depend on the engine, and is mainly used for audio Facility Management without an engine
 * @param handler Audio device event callback, see ByteRTCAudioDeviceEventHandler{@link #ByteRTCAudioDeviceEventHandler}.
 * @return API of audio device management
 */
+ (ByteRTCAudioDeviceManager *_Null_unspecified)createAudioDeviceManager:(id<ByteRTCAudioDeviceEventHandler> _Nonnull)handler;
/**
 * @locale zh
 * @type api
 * @brief 设置运行时的参数
 * @param parameters 保留参数
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note 该接口需在 joinRoom:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoom:userInfo:roomConfig:} 和 startAudioCapture{@link #ByteRTCVideo#startAudioCapture} 之前调用。
 * @list 引擎管理
 * @order 25
 */
/**
 * @locale en
 * @type api
 * @brief Sets runtime parameters
 * @param parameters Reserved parameters
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note Call this API before joinRoom:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoom:userInfo:roomConfig:} and startAudioCapture{@link #ByteRTCVideo#startAudioCapture}.
 * @list Engine Management
 * @order 25
 */
- (int)setRuntimeParameters:(NSDictionary * _Nullable)parameters;
#if BYTERTC_TARGET_MAC
/**
 * @locale zh
 * @type api
 * @hidden(iOS)
 * @region 屏幕共享
 * @brief 获取共享对象(应用窗口和桌面)列表。
 * @return 共享对象(应用窗口和桌面)列表。参看 ByteRTCScreenCaptureSourceInfo{@link #ByteRTCScreenCaptureSourceInfo}。<br>
 *         枚举值可作为调用 startScreenVideoCapture:captureParameters:{@link #ByteRTCVideo#startScreenVideoCapture:captureParameters:} 开启屏幕共享时的输入参数。
 * @note 仅桌面端可用。
 */
/**
 * @locale en
 * @type api
 * @hidden(iOS)
 * @region screen sharing
 * @brief  Get the list of shared objects (application windows and screens).
 * @return The list of shared objects. See ByteRTCScreenCaptureSourceInfo{@link #ByteRTCScreenCaptureSourceInfo}。<br>
 *         The enumerated value can be used for startScreenVideoCapture:captureParameters:{@link #ByteRTCVideo#startScreenVideoCapture:captureParameters:}.
 * @note Only valid for PC and macOS.
 */
- (NSArray<ByteRTCScreenCaptureSourceInfo *> *_Nonnull)getScreenCaptureSourceList;
/**
 * @locale zh
 * @type api
 * @hidden(iOS)
 * @region 屏幕共享
 * @brief 采集屏幕视频流，用于共享。屏幕视频流包括：屏幕上显示的内容，或应用窗口中显示的内容。
 * @param sourceInfo 待共享的屏幕源，参看 ByteRTCScreenCaptureSourceInfo{@link #ByteRTCScreenCaptureSourceInfo}。<br>
 *                   你可以调用 getScreenCaptureSourceList{@link #ByteRTCVideo#getScreenCaptureSourceList} 获得所有可以共享的屏幕源。
 * @param captureParameters 共享参数。参看 ByteRTCScreenCaptureParam{@link #ByteRTCScreenCaptureParam}。
 * @return  
 *        + 0: 成功  <br>
 *        + -1: 失败  
 * @note  
 *       + 调用本接口时，采集模式应为内部模式。在外部采集模式下调用无效，并将触发 rtcEngine:onVideoDeviceWarning:deviceType:deviceWarning:{@link #ByteRTCVideoDelegate#rtcEngine:onVideoDeviceWarning:deviceType:deviceWarning:} 回调。<br>
 *       + 调用此方法仅开启屏幕流视频采集，不会发布采集到的视频。发布屏幕流视频需要调用 publishScreen:{@link #ByteRTCRoom#publishScreen:}。<br>
 *       + 调用 stopScreenVideoCapture{@link #ByteRTCVideo#stopScreenVideoCapture} 关闭屏幕视频源采集。  <br>
 *       + 本地用户通过 rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:} 的回调获取屏幕采集状态，包括开始、暂停、恢复、错误等。  <br>
 *       + 调用成功后，本端会收到 rtcEngine:onFirstLocalVideoFrameCaptured:withFrameInfo:{@link #ByteRTCVideoDelegate#rtcEngine:onFirstLocalVideoFrameCaptured:withFrameInfo:} 回调。  <br>
 *       + 调用此接口前，你可以调用 setScreenVideoEncoderConfig:{@link #ByteRTCVideo#setScreenVideoEncoderConfig:} 设置屏幕视频流的采集帧率和编码分辨率。  <br>
 *       + 在收到 rtcEngine:onFirstLocalVideoFrameCaptured:withFrameInfo:{@link #ByteRTCVideoDelegate#rtcEngine:onFirstLocalVideoFrameCaptured:withFrameInfo:} 回调后，通过调用 setLocalVideoCanvas:withCanvas:{@link #ByteRTCVideo#setLocalVideoCanvas:withCanvas:} 或 setLocalVideoSink:withSink:withPixelFormat:{@link #ByteRTCVideo#setLocalVideoSink:withSink:withPixelFormat:} 函数设置本地屏幕共享视图。  <br>
 *       + 再开启采集屏幕视频流后，你可以调用 updateScreenCaptureHighlightConfig:{@link #ByteRTCVideo#updateScreenCaptureHighlightConfig:} 更新边框高亮设置，调用 updateScreenCaptureMouseCursor:{@link #ByteRTCVideo#updateScreenCaptureMouseCursor:} 更新对鼠标的处理设置，PC 端还可以调用 updateScreenCaptureFilterConfig:{@link #ByteRTCVideo#updateScreenCaptureFilterConfig:} 设置需要过滤的窗口。  
 */
/**
 * @locale en
 * @type api
 * @hidden(iOS)
 * @region screen sharing
 * @brief Capture screen video stream for sharing. Screen video stream includes: content displayed on the screen, or content in the application window.
 * @param sourceInfo Screen capture source information. See ByteRTCScreenCaptureSourceInfo{@link #ByteRTCScreenCaptureSourceInfo}. <br>
 *                    Call getScreenCaptureSourceList{@link #ByteRTCVideo#getScreenCaptureSourceList} to get all the screen sources that can be shared.
 * @param captureParameters Screen capture parameters. See ByteRTCScreenCaptureParam{@link #ByteRTCScreenCaptureParam}.
 * @return 
 *         + 0: Success; <br>
 *         + -1: Failure; 
 * @note 
 *        + The call of this API takes effects only when you are using RTC SDK to record screen. You will get a warning by rtcEngine:onVideoDeviceWarning:deviceType:deviceWarning:{@link #ByteRTCVideoDelegate#rtcEngine:onVideoDeviceWarning:deviceType:deviceWarning:} after calling this API when the video source is set to an external recorder.<br>
 *        + This API only starts screen capturing but does not publish the captured video. Call publishScreen:{@link #ByteRTCRoom#publishScreen:} to publish the captured video. <br>
 *        + To turn off screen video capture, call stopScreenVideoCapture{@link #ByteRTCVideo#stopScreenVideoCapture}. <br>
 *        + Local users will receive rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:} on the state of screen capturing such as start, pause, resume, and error. <br>
 *        + After successfully calling this API, local users will receive rtcEngine:onFirstLocalVideoFrameCaptured:withFrameInfo:{@link #ByteRTCVideoDelegate#rtcEngine:onFirstLocalVideoFrameCaptured:withFrameInfo:}. <br>
 *        + Before calling this API, you can call setScreenVideoEncoderConfig:{@link #ByteRTCVideo#setScreenVideoEncoderConfig:} to set the frame rate and encoding resolution of the screen video stream. <br>
 *        + After receiving rtcEngine:onFirstLocalVideoFrameCaptured:withFrameInfo:{@link #ByteRTCVideoDelegate#rtcEngine:onFirstLocalVideoFrameCaptured:withFrameInfo:}, you can set the local screen sharing view by calling setLocalVideoCanvas:withCanvas:{@link #ByteRTCVideo#setLocalVideoCanvas:withCanvas:} or setLocalVideoSink:withSink:withPixelFormat:{@link #ByteRTCVideo#setLocalVideoSink:withSink:withPixelFormat:}. <br>
 *        + After you start capturing screen video stream for sharing，you can call updateScreenCaptureHighlightConfig:{@link #ByteRTCVideo#updateScreenCaptureHighlightConfig:} to update border highlighting settings, updateScreenCaptureMouseCursor:{@link #ByteRTCVideo#updateScreenCaptureMouseCursor:} to update the processing settings for the mouse, and updateScreenCaptureFilterConfig:{@link #ByteRTCVideo#updateScreenCaptureFilterConfig:} to set the window that needs to be filtered on PC clinets.<br>

 */
- (int)startScreenVideoCapture:(ByteRTCScreenCaptureSourceInfo *_Nonnull)sourceInfo captureParameters:(ByteRTCScreenCaptureParam *_Nonnull)captureParameters NS_SWIFT_NAME(startScreenVideoCapture(_:captureParameters:));
/**
 * @locale zh
 * @hidden(iOS)
 * @type api
 * @region 屏幕共享
 * @brief 停止屏幕视频流采集。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note  
 *       + 调用本接口时，采集模式应为内部模式。在外部采集模式下调用无效，并将触发 rtcEngine:onVideoDeviceWarning:deviceType:deviceWarning:{@link #ByteRTCVideoDelegate#rtcEngine:onVideoDeviceWarning:deviceType:deviceWarning:} 回调。<br>
 *       + 要开启屏幕视频流采集，调用 startScreenVideoCapture:captureParameters:{@link #ByteRTCVideo#startScreenVideoCapture:captureParameters:}。  <br>
 *       + 调用后，本地用户会收到 rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:} 的回调。  <br>
 *       + 调用此接口不影响屏幕视频流发布。  
 */
/**
 * @locale en
 * @hidden(iOS)
 * @type api
 * @region screen sharing
 * @brief Stops capturing screen video stream.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note 
 *        + The call of this API takes effects only when you are using RTC SDK to record screen. You will get a warning by rtcEngine:onVideoDeviceWarning:deviceType:deviceWarning:{@link #ByteRTCVideoDelegate#rtcEngine:onVideoDeviceWarning:deviceType:deviceWarning:} after calling this API when the video source is set to an external recorder.<br>
 *        + To enable screen video stream capture, calling startScreenVideoCapture:captureParameters:{@link #ByteRTCVideo#startScreenVideoCapture:captureParameters:}. <br>
 *        + You will receive rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCVideoDelegate#rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:} after calling this API. <br>
 *        + This API has no effect on screen video stream publishing. 
 */
- (int)stopScreenVideoCapture;
/**
 * @locale zh
 * @type api
 * @hidden(iOS)
 * @region 屏幕共享
 * @brief 内部屏幕流采集时，更新采集区域。
 * @param regionRect 采集区域相对 startScreenVideoCapture:captureParameters:{@link #ByteRTCVideo#startScreenVideoCapture:captureParameters:} 中设定区域的值。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note 调用此接口前，必须先通过调用 startScreenVideoCapture:captureParameters:{@link #ByteRTCVideo#startScreenVideoCapture:captureParameters:} 开启了内部屏幕流采集。
 */
/**
 * @locale en
 * @type api
 * @hidden(iOS)
 * @region Screen sharing
 * @brief Update the capture area when capturing screen video streams through the internal capture module .
 * @param regionRect The relative capture area to the area set by startScreenVideoCapture:captureParameters:{@link #ByteRTCVideo#startScreenVideoCapture:captureParameters:}.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note Before calling this API, you must call startScreenVideoCapture:captureParameters:{@link #ByteRTCVideo#startScreenVideoCapture:captureParameters:} to start internal screen stream capture.
 */
- (int)updateScreenCaptureRegion:(CGRect)regionRect;
/**
 * @locale zh
 * @type api
 * @hidden(iOS)
 * @region 屏幕共享
 * @brief 内部屏幕流采集时，更新边框高亮设置。默认展示边框。
 * @param config 边框高亮设置。参见 ByteRTCHighlightConfig{@link #ByteRTCHighlightConfig}。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note 调用此接口前，必须已通过调用 startScreenVideoCapture:captureParameters:{@link #ByteRTCVideo#startScreenVideoCapture:captureParameters:} 开启了内部屏幕流采集。
 */
/**
 * @locale en
 * @type api
 * @hidden(iOS)
 * @region Screen sharing
 * @brief Update border highlighting settings when capturing screen video streams through the internal capture module. The border is shown by default.
 * @param config Border highlighting settings. See ByteRTCHighlightConfig{@link #ByteRTCHighlightConfig}.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note  Before calling this API, you must have turned on internal screen capture by calling startScreenVideoCapture:captureParameters:{@link #ByteRTCVideo#startScreenVideoCapture:captureParameters:}.
 */
- (int)updateScreenCaptureHighlightConfig:(ByteRTCHighlightConfig *_Nonnull)config NS_SWIFT_NAME(updateScreenCaptureHighlightConfig(_:));
/**
 * @locale zh
 * @type api
 * @hidden(iOS)
 * @region 屏幕共享
 * @brief 内部屏幕流采集时，更新对鼠标的处理设置。默认采集鼠标。
 * @param mouseCursorCaptureState 参看 ByteRTCMouseCursorCaptureState{@link #ByteRTCMouseCursorCaptureState}。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note 调用此接口前，必须已通过调用 startScreenVideoCapture:captureParameters:{@link #ByteRTCVideo#startScreenVideoCapture:captureParameters:} 开启了内部屏幕流采集。
 */
/**
 * @locale en
 * @hidden(iOS)
 * @type api
 * @region Screen sharing
 * @brief Update the processing settings for the mouse when capturing screen video streams through the capture module provided by the RTC SDK. The mouse is shown by default.
 * @param mouseCursorCaptureState See ByteRTCMouseCursorCaptureState{@link #ByteRTCMouseCursorCaptureState}.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note  Before calling this API, you must have turned on internal screen capture by calling startScreenVideoCapture:captureParameters:{@link #ByteRTCVideo#startScreenVideoCapture:captureParameters:}.
 */
- (int)updateScreenCaptureMouseCursor:(ByteRTCMouseCursorCaptureState)mouseCursorCaptureState;
/**
 * @locale zh
 * @type api
 * @hidden(iOS)
 * @region 屏幕共享
 * @brief 通过 RTC SDK 提供的采集模块采集屏幕视频流时，设置需要过滤的窗口。
 * @param excludedWindowList 过滤掉的窗口列表。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note 
 *       + 调用此接口前，必须已通过调用 startScreenVideoCapture:captureParameters:{@link #ByteRTCVideo#startScreenVideoCapture:captureParameters:} 开启了内部屏幕流采集。<br>
 *       + 本函数在屏幕源类别是屏幕而非应用窗体时才起作用。详见：ByteRTCScreenCaptureSourceType{@link #ByteRTCScreenCaptureSourceType}。<br>
 *       + 调用本接口排除指定窗口时，共享视频的帧率无法达到 30fps。
 */
/**
 * @locale en
 * @type api
 * @hidden(iOS)
 * @region Screen sharing
 * @brief When capturing screen video streams through the capture module provided by the RTC SDK, set the windows to be filtered out.
 * @param excludedWindowList The windows to be filtered out.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note  
 *        + Before calling this API, you must have turned on internal screen capture by calling startScreenVideoCapture:captureParameters:{@link #ByteRTCVideo#startScreenVideoCapture:captureParameters:}. <br>
 *        + This function only works when the screen source is a screen rather than an application window. See: ByteRTCScreenCaptureSourceType{@link #ByteRTCScreenCaptureSourceType}.<br>
 *        + When you call this API to exclude specific windows, the frame rate of the shared-screen stream will be lower than 30fps。
 */
- (int)updateScreenCaptureFilterConfig:(NSArray<NSNumber *> * _Nullable) excludedWindowList;
/**
 * @locale zh
 * @type api
 * @hidden(iOS)
 * @region 屏幕共享
 * @brief 获取屏幕采集对象缩略图
 * @param sourceType 屏幕采集对象的类型。详见 ByteRTCScreenCaptureSourceType{@link #ByteRTCScreenCaptureSourceType}。
 * @param sourceId 屏幕分享时，共享对象的 ID。可通过 getScreenCaptureSourceList{@link #ByteRTCVideo#getScreenCaptureSourceList} 返回的`ByteRTCScreenCaptureSourceInfo`共享对象列表中获取。
 * @param maxWidth 最大宽度。保持采集对象本身的宽高比不变，将缩略图缩放到指定范围内的最大宽高。如果给出的尺寸与共享对象比例不同，得到的缩略图会有黑边。
 * @param maxHeight 最大高度。参见 maxWidth 的说明。
 * @return 屏幕采集对象缩略图。缩略图由屏幕共享对象等比缩放而来。缩略图的大小小于等于此接口设定的尺寸。
 */
/**
 * @locale en
 * @type api
 * @hidden(iOS)
 * @region  screen share
 * @brief  Get the thumbnail of the screen
 * @param sourceType Type of the screen capture object. See ByteRTCScreenCaptureSourceType{@link #ByteRTCScreenCaptureSourceType}.
 * @param sourceId ID of the screen-shared object. You can get the ID from `ByteRTCScreenCaptureSourceInfo` returned by calling getScreenCaptureSourceList{@link #ByteRTCVideo#getScreenCaptureSourceList}.
 * @param maxWidth Maximum width. RTC will scale the thumbnail to fit the given size while maintaining the original aspect ratio. If the aspect ratio of the given size does not match the sharing object, the thumbnail will have blank borders.
 * @param maxHeight Maximum height. Refer to the note for `maxWidth`.
 * @return The thumbnail of the sharing object.  <br>
 *         The thumbnail is of the same width-height ratio of the object. The size of the trumbnail is no larger than the specified size.
 */
- (ByteRTCImage *_Nonnull)getThumbnail:(ByteRTCScreenCaptureSourceType)sourceType sourceId:(intptr_t)sourceId maxWidth:(int)maxWidth maxHeight:(int)maxHeight;
/**
 * @locale zh
 * @hidden(iOS)
 * @brief 获取应用窗体所属应用的图标。
 * @region 屏幕共享
 * @param sourceId 屏幕共享对象的 ID，可通过 getScreenCaptureSourceList{@link #ByteRTCVideo#getScreenCaptureSourceList} 返回的`ByteRTCScreenCaptureSourceInfo`共享对象列表中获取。
 * @param width 最大宽度。返回的图标将是宽高相等的，输入的宽高不等时，取二者较小值。宽高范围为 [32,256]，超出该范围将返回 `nullptr`，默认输出 100 x 100 的图像。
 * @param height 最大高度。参见 `width` 的说明。
 * @return 应用图标。当屏幕共享对象为应用窗体时有效，否则返回 `nullptr`。
 */
/**
 * @locale en
 * @hidden(iOS)
 * @brief Gets application window preview thumbnail for screen sharing.
 * @region Screen Sharing
 * @param sourceId ID of the screen-sharing object. You can get the ID from `ByteRTCScreenCaptureSourceInfo` returned by calling getScreenCaptureSourceList{@link #ByteRTCVideo#getScreenCaptureSourceList}.
 * @param width Maximum width of the App icon. The width is always equal to the height. SDK will set the height and width to the smaller value if the given values are unequal. RTC will return `nullptr` if you set the value with a number out of the valid range, [32, 256]. The default size is 100 x 100.
 * @param height Maximum height of the app icon. Refer to the note for `width`.
 * @return Application icon thumbnail. You can call this API when the item to be shared is an application. If not, the return value will be `nullptr`.
 */
- (ByteRTCImage *_Nonnull)getWindowAppIcon:(intptr_t)sourceId width:(int)width height:(int)height;
#endif
/**
 * @locale zh
 * @type api
 * @hidden(iOS)
 * @region 音频管理
 * @brief 创建音频设备管理实例
 * @return ByteRTCAudioDeviceManager{@link #ByteRTCAudioDeviceManager}
 */
/**
 * @locale en
 * @type api
 * @hidden(iOS)
 * @region audio management
 * @brief Get ByteRTCAudioDeviceManager{@link #ByteRTCAudioDeviceManager}
 * @return ByteRTCAudioDeviceManager{@link #ByteRTCAudioDeviceManager}
 */
- (ByteRTCAudioDeviceManager *_Null_unspecified)getAudioDeviceManager;
/**
 * @locale zh
 * @type api
 * @hidden(iOS)
 * @region 视频设备管理
 * @brief 创建视频设备管理实例
 * @return 视频设备管理实例，详见 ByteRTCVideoDeviceManager{@link #ByteRTCVideoDeviceManager}
 */
/**
 * @locale en
 * @type api
 * @hidden(iOS)
 * @region Video Device Management
 * @brief Get ByteRTCVideoDeviceManager{@link #ByteRTCVideoDeviceManager}
 * @return ByteRTCVideoDeviceManager{@link #ByteRTCVideoDeviceManager}
 */
- (ByteRTCVideoDeviceManager * _Null_unspecified)getVideoDeviceManager NS_SWIFT_NAME(getVideoDeviceManager());

#pragma mark - ASR
/**
 * @locale zh
 * @hidden(macOS)
 * @type api
 * @region 语音识别服务
 * @brief 开启自动语音识别服务。<br>
 *        该方法将识别后的用户语音转化成文字，并通过 onMessage:{@link #ByteRTCASREngineEventHandler#onMessage:} 事件回调给用户。
 * @param handler 语音识别服务使用状态回调，参看 ByteRTCASREngineEventHandler{@link #ByteRTCASREngineEventHandler}
 * @param asrConfig 校验信息，参看 ByteRTCASRConfig{@link #ByteRTCASRConfig}
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 */
/**
 * @locale en
 * @hidden currently not available
 * @type api
 * @region speech recognition service
 * @brief Enables automatic speech recognition service. This method converts the recognized user's voice into text and calls it back to the user via the onMessage:{@link #ByteRTCASREngineEventHandler#onMessage:} event.
 * @param handler The speech recognition service uses a status callback. See ByteRTCASREngineEventHandler{@link #ByteRTCASREngineEventHandler}
 * @param asrConfig Check information. See ByteRTCASRConfig{@link #ByteRTCASRConfig}
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 */
- (int)startASR:(ByteRTCASRConfig *_Nonnull)asrConfig handler:(id<ByteRTCASREngineEventHandler> _Nonnull)handler ;
/**
 * @locale zh
 * @hidden(macOS)
 * @type api
 * @region 语音识别服务
 * @brief 关闭语音识别服务
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 */
/**
 * @locale en
 * @hidden currently not available
 * @type api
 * @region speech recognition service
 * @brief Turn off speech recognition service
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 */
- (int)stopASR;
#pragma mark - FileRecording
/**
 * @locale zh
 * @type api
 * @region 本地录制
 * @brief 该方法将通话过程中的音视频数据录制到本地的文件中。
 * @param streamIndex 流属性，指定录制主流还是屏幕流，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param recordingConfig 本地录制参数配置，参看 ByteRTCRecordingConfig{@link #ByteRTCRecordingConfig}
 * @param recordingType 本地录制的媒体类型，参看 ByteRTCRecordingType{@link #ByteRTCRecordingType}
 * @return   
 *        + 0: 正常<br>
 *        + -1: 参数设置异常<br>
 *        + -2: 当前版本 SDK 不支持该特性，请联系技术支持人员
 * @note  
 *        + 调用该方法后，你会收到 rtcEngine:onRecordingStateUpdate:state:error_code:recording_info:{@link #ByteRTCVideoDelegate#rtcEngine:onRecordingStateUpdate:state:error_code:recording_info:} 回调。  <br>
 *        + 如果录制正常，系统每秒钟会通过 rtcEngine:onRecordingProgressUpdate:process:recording_info:{@link #ByteRTCVideoDelegate#rtcEngine:onRecordingProgressUpdate:process:recording_info:} 回调通知录制进度。
 */
/**
 * @locale en
 * @type api
 * @region Local recording
 * @brief This method records the audio & video data during the call to a local file.
 * @param streamIndex Stream property, specify whether to record mainstream or screen stream. See ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param recordingConfig Local recording parameter configuration. See ByteRTCRecordingConfig{@link #ByteRTCRecordingConfig}
 * @param recordingType Locally recorded media type, see ByteRTCRecordingType{@link #ByteRTCRecordingType}
 * @return    
 *         + 0: normal<br>
 *         + -1: Parameter setting exception<br>
 *         + -2: The current version of the SDK does not support this feature, please contact technical support
 * @note   
 *         + After this API is called, the local user will receive rtcEngine:onRecordingStateUpdate:state:error_code:recording_info:{@link #ByteRTCVideoDelegate#rtcEngine:onRecordingStateUpdate:state:error_code:recording_info:} callback. <br>
 *         + If the recording is normal, the system will report the recording progress through rtcEngine:onRecordingProgressUpdate:process:recording_info:{@link #ByteRTCVideoDelegate#rtcEngine:onRecordingProgressUpdate:process:recording_info:} callback every second.
 */
- (int)startFileRecording:(ByteRTCStreamIndex)streamIndex
      withRecordingConfig:(ByteRTCRecordingConfig* _Nonnull)recordingConfig type:(ByteRTCRecordingType)recordingType NS_SWIFT_NAME(startFileRecording(_:withRecordingConfig:type:));
/**
 * @locale zh
 * @type api
 * @region 本地录制
 * @brief 停止本地录制
 * @param streamIndex 流属性，指定停止主流或者屏幕流录制，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note  
 *        + 调用 startFileRecording:withRecordingConfig:type:{@link #ByteRTCVideo#startFileRecording:withRecordingConfig:type:} 开启本地录制后，你必须调用该方法停止录制。  <br>
 *        + 调用该方法后，你会收到 rtcEngine:onRecordingStateUpdate:state:error_code:recording_info:{@link #ByteRTCVideoDelegate#rtcEngine:onRecordingStateUpdate:state:error_code:recording_info:} 回调提示录制结果。
 */
/**
 * @locale en
 * @type api
 * @region Local recording
 * @brief Stops local recording
 * @param streamIndex Stream property, specify to stop mainstream or screen stream recording. See ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note   
 *         + After calling startFileRecording:withRecordingConfig:type:{@link #ByteRTCVideo#startFileRecording:withRecordingConfig:type:} to start local recording, you must call this method to stop recording. <br>
 *         + The recording result will be called back through rtcEngine:onRecordingStateUpdate:state:error_code:recording_info:{@link #ByteRTCVideoDelegate#rtcEngine:onRecordingStateUpdate:state:error_code:recording_info:}.
 */
- (int)stopFileRecording:(ByteRTCStreamIndex)streamIndex;
/**
 * @locale zh
 * @type api
 * @brief 开启录制语音通话，生成本地文件。<br>
 *        在进房前后开启录制，如果未打开麦克风采集，录制任务正常进行，只是不会将数据写入生成的本地文件；只有调用 startAudioCapture{@link #ByteRTCVideo#startAudioCapture} 接口打开麦克风采集后，才会将录制数据写入本地文件。
 * @param recordingConfig 参看 ByteRTCAudioRecordingConfig{@link #ByteRTCAudioRecordingConfig}
 * @return  
 *        + 0: 正常 <br>
 *        + -2: 参数设置异常 <br>
 *        + -3: 当前版本 SDK 不支持该特性，请联系技术支持人员
 * @note 
 *        + 录制包含各种音频效果。但不包含背景音乐。<br>
 *        + 调用 stopAudioRecording{@link #ByteRTCVideo#stopAudioRecording} 关闭录制。<br>
 *        + 加入房间前后均可调用。在进房前调用该方法，退房之后，录制任务不会自动停止，需调用stopAudioRecording{@link #ByteRTCVideo#stopAudioRecording} 关闭录制。在进房后调用该方法，退房之后，录制任务会自动被停止。如果加入了多个房间，录制的文件中会包含各个房间的音频。<br>
 *        + 调用该方法后，你会收到 rtcEngine:onAudioRecordingStateUpdate:error_code:{@link #ByteRTCVideoDelegate#rtcEngine:onAudioRecordingStateUpdate:error_code:} 回调。  
 */
/**
 * @locale en
 * @type api
 * @brief Starts recording audio communication, and generate the local file.<br>
 *        If you call this API before or after joining the room without internal audio capture, then the recording task can still begin but the data will not be recorded in the local files. Only when you call startAudioCapture{@link #ByteRTCVideo#startAudioCapture} to enable internal audio capture, the data will be recorded in the local files.
 * @param recordingConfig See ByteRTCAudioRecordingConfig{@link #ByteRTCAudioRecordingConfig}.
 * @return  
 *        + 0: Success <br>
 *        + -2: Invalid parameters <br>
 *        + -3: Not valid in this SDK. Please contact the technical support.
 * @note 
 *        + All audio effects are valid in the file. Mixed audio file is not included in the file. <br>
 *        + Call stopAudioRecording{@link #ByteRTCVideo#stopAudioRecording} to stop recording. <br>
 *        + You can call this API before and after joining the room. If this API is called before you join the room, you need to call stopAudioRecording{@link #ByteRTCVideo#stopAudioRecording} to stop recording. If this API is called after you join the room, the recording task ends automatically. If you join multiple rooms, audio from all rooms are recorded in one file.  <br>
 *        + After calling the API, you'll receive rtcEngine:onAudioRecordingStateUpdate:error_code:{@link #ByteRTCVideoDelegate#rtcEngine:onAudioRecordingStateUpdate:error_code:}. 
 */
- (int)startAudioRecording:(ByteRTCAudioRecordingConfig* _Nonnull) recordingConfig;
/**
 * @locale zh
 * @type api
 * @brief 停止音频文件录制
 * @return 
 *         + 0: 正常 <br>
 *         + -3: 当前版本 SDK 不支持该特性，请联系技术支持人员
 * @note 调用 startAudioRecording:{@link #ByteRTCVideo#startAudioRecording:} 开启本地录制。
 */
 /**
 * @locale en
 * @type api
 * @brief Stop audio recording.
 * @return 
 *         + 0: Success <br>
 *         + <0: Failure
 * @note Call startAudioRecording:{@link #ByteRTCVideo#startAudioRecording:} to start the recording task.
 */
- (int)stopAudioRecording;
 /**
  * @locale zh
  * @type api
  * @deprecated since 353.1, will be deleted in 359, use getAudioEffectPlayer{@link #ByteRTCVideo#getAudioEffectPlayer} or getMediaPlayer:{@link #ByteRTCVideo#getMediaPlayer:} instead
  * @region 混音
  * @brief 混音管理接口创建
  * @return 混音管理实例，详见ByteRTCAudioMixingManager{@link #ByteRTCAudioMixingManager}
  */
 /**
  * @locale en
  * @type api
  * @deprecated since 353.1, will be deleted in 359, use getAudioEffectPlayer{@link #ByteRTCVideo#getAudioEffectPlayer} or getMediaPlayer:{@link #ByteRTCVideo#getMediaPlayer:} instead
  * @region  mixing
  * @brief Mixing management interface creation
  * @return  Mixing management instance. See ByteRTCAudioMixingManager{@link #ByteRTCAudioMixingManager}
  */
- (ByteRTCAudioMixingManager *_Nullable)getAudioMixingManager __deprecated_msg("deprecated since 353.1, will be deleted in 359, use getAudioEffectPlayer and getMediaPlayer instead");
 /**
 * @locale zh
 * @type api
 * @valid since 3.53
 * @brief 创建音效播放器实例。
 * @return 音效播放器。详见 ByteRTCAudioEffectPlayer{@link #ByteRTCAudioEffectPlayer}。
 */
/**
 * @locale en
 * @type api
 * @valid since 3.53
 * @brief Create an instance for audio effect player.
 * @return See ByteRTCAudioEffectPlayer{@link #ByteRTCAudioEffectPlayer}.
 */
- (ByteRTCAudioEffectPlayer *_Nullable)getAudioEffectPlayer;
 /**
 * @locale zh
 * @type api
 * @valid since 3.53
 * @brief 创建音乐播放器实例。
 * @param playerId 音乐播放器实例 id。取值范围为 `[0, 3]`。最多同时存在4个实例，超出取值范围时返回 nullptr。
 * @return 音乐播放器实例，详见 ByteRTCMediaPlayer{@link #ByteRTCMediaPlayer}
 */
/**
 * @locale en
 * @type api
 * @valid since 3.53
 * @brief Create a media player instance.
 * @param playerId Media player id. The range is `[0, 3]`. You can create up to 4 instances at the same time. If it exceeds the range, nullptr will be returned.
 * @return Media player instance. See ByteRTCMediaPlayer{@link #ByteRTCMediaPlayer}.
 */
- (ByteRTCMediaPlayer *_Nullable)getMediaPlayer:(int)playerId;

#pragma mark - Rtm
/**
 * @locale zh
 * @type api
 * @region 实时消息通信
 * @brief 登陆 RTS 服务器。
 *        必须先登录，才能调用 sendUserMessageOutsideRoom:message:config:{@link #ByteRTCVideo#sendUserMessageOutsideRoom:message:config:} 和 sendServerMessage:{@link #ByteRTCVideo#sendServerMessage:} 发送房间外点对点消息和向应用服务器发送消息 <br>
 *        在调用本接口登录后，如果想要登出，需要调用 logout{@link #ByteRTCVideo#logout}
 * @param token  用户登录必须携带的 Token，用于鉴权验证。<br>
 *               测试时可使用[控制台](https://console.volcengine.com/rtc/listRTC)生成临时 Token，`roomId` 填任意值。<br>
 *               正式上线需要使用密钥 SDK 在你的服务端生成并下发 Token，`roomId` 置空，Token 有效期及生成方式参看[使用 Token 完成鉴权](70121)。
 * @param uid 用户 ID，在 appid的维度下是唯一的。
 * @return 
 *        + 0：成功；<br>
 *        + <0：失败。具体失败原因参看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus}。
 * @note  本地用户调用此方法登录后，会收到 rtcEngine:onLoginResult:errorCode:elapsed:{@link #ByteRTCVideoDelegate#rtcEngine:onLoginResult:errorCode:elapsed:} 回调通知登录结果，远端用户不会收到通知。
 */
/**
 * @locale en
 * @type api
 * @region Real-time messaging
 * @brief Log in to call sendUserMessageOutsideRoom:message:config:{@link #ByteRTCVideo#sendUserMessageOutsideRoom:message:config:} and sendServerMessage:{@link #ByteRTCVideo#sendServerMessage:} to send P2P messages or send messages to a server without joining the RTC room. <br>
 *        To log out, call logout{@link #ByteRTCVideo#logout}.
 * @param token Token is required during login for authentication. <br>
 *        This Token is different from that required by calling joinRoom. You can assign any value even null to `roomId` to generate a login token. During developing and testing, you can use temporary tokens generated on the console. Deploy the token generating application on your server.
 * @param uid User ID which need to be unique within one appid.
 * @return 
 *        + 0: Success.<br>
 *        + <0: Failure. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for specific reasons.
 * @note The local user will receive rtcEngine:onLoginResult:errorCode:elapsed:{@link #ByteRTCVideoDelegate#rtcEngine:onLoginResult:errorCode:elapsed:} after this API is called successfully. But remote users will not receive notification about that.
 */
- (int)login:(NSString * _Nonnull)token uid:(NSString * _Nonnull)uid;
/**
 * @locale zh
 * @type api
 * @region 实时消息通信
 * @brief 登出 RTS 服务器。
 *        调用本接口登出后，无法调用房间外消息以及端到服务器消息相关的方法或收到相关回调。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note  
 *       + 调用本接口登出前，必须先调用 login:uid:{@link #ByteRTCVideo#login:uid:} 登录  <br>
 *       + 本地用户调用此方法登出后，会收到 rtcEngine:onLogout:{@link #ByteRTCVideoDelegate#rtcEngine:onLogout:}  回调通知结果，远端用户不会收到通知。
 */
/**
 * @locale en
 * @type After api
 * @region  real-time messaging
 * @brief Calls this interface to log out, it is impossible to call methods related to out-of-room messages and end-to-server messages or receive related callbacks.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note   
 *        + Before calling this interface to log out, login:uid:{@link #ByteRTCVideo#login:uid:} Login <br>
 *        + After local users call this method to log out, they will receive rtcEngine:onLogout:{@link #ByteRTCVideoDelegate#rtcEngine:onLogout:} callback notification results, and remote users will not receive notifications.
 */
- (int)logout;
/**
 * @locale zh
 * @type api
 * @region 实时消息通信
 * @brief 更新用户用于登录的 Token  <br>
 *        Token 有一定的有效期，当 Token 过期时，需调用此方法更新登录的 Token 信息。  <br>
 *        调用 login:uid:{@link #ByteRTCVideo#login:uid:} 方法登录时，如果使用了过期的 Token 将导致登录失败，并会收到 rtcEngine:onLoginResult:errorCode:elapsed:{@link #ByteRTCVideoDelegate#rtcEngine:onLoginResult:errorCode:elapsed:} 回调通知，错误码为 ByteRTCLoginErrorCodeInvalidToken。此时需要重新获取 Token，并调用此方法更新 Token。
 * @param token  <br>
 *        更新的动态密钥  
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note  
 *       + 如果 Token 无效导致登录失败，则调用此方法更新 Token 后，SDK 会自动重新登录，而用户不需要自己调用 login:uid:{@link #ByteRTCVideo#login:uid:} 方法。  <br>
 *       + Token 过期时，如果已经成功登录，则不会受到影响。Token 过期的错误会在下一次使用过期 Token 登录时，或因本地网络状况不佳导致断网重新登录时通知给用户。
 */
/**
 * @locale en
 * @type api
 * @region Real-time messaging
 * @brief Updates the Token used by the user to log in. <br>
 *        Token used by the user to log in has a certain valid period. When the Token expires, you need to call this method to update the login Token information. <br>
 *        If login:uid:{@link #ByteRTCVideo#login:uid:}  is called with an expired Token, the login fails and the local user will receive rtcEngine:onLoginResult:errorCode:elapsed:{@link #ByteRTCVideoDelegate#rtcEngine:onLoginResult:errorCode:elapsed:} about corresponding error code. You need to reacquire a Token and update it with this method.
 * @param token   <br>
 *        Updated dynamic key 
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note   
 *        + If the token is invalid and the login fails, call this method to update the token, and the SDK will automatically log in again. The user does not need to call the login:uid:{@link #ByteRTCVideo#login:uid:} method. <br>
 *        + Token expires, if you have successfully logged in, it will not be affected. An expired Token error will be notified to the user the next time you log in with an expired Token, or when you log in again due to a disconnection due to poor local network conditions.
 */
- (int)updateLoginToken:(NSString * _Nonnull)token;
/**
 * @locale zh
 * @type api
 * @region 实时消息通信
 * @brief 设置应用服务器参数  <br>
 *        客户端调用 sendServerMessage:{@link #ByteRTCVideo#sendServerMessage:} 或 sendServerBinaryMessage:{@link #ByteRTCVideo#sendServerBinaryMessage:} 发送消息给应用服务器之前，必须需要设置有效签名和应用服务器地址。
 * @param signature 动态签名，应用服务器可使用该签名验证消息来源。<br>
 *        签名需自行定义，可传入任意非空字符串，建议将 uid 等信息编码为签名。<br>
 *        设置的签名会以 post 形式发送至通过本方法中 url 参数设置的应用服务器地址。
 * @param url 应用服务器的地址
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note  
 *       + 用户必须调用 login:uid:{@link #ByteRTCVideo#login:uid:} 登录后，才能调用本接口。  <br>
 *       + 调用本接口后，SDK 会使用 rtcEngine:onServerParamsSetResult:{@link #ByteRTCVideoDelegate#rtcEngine:onServerParamsSetResult:} 返回相应结果。
 */
/**
 * @locale en
 * @type api
 * @region Real-time messaging
 * @brief Sets application server parameters   <br>
 *        Client side calls sendServerMessage:{@link #ByteRTCVideo#sendServerMessage:} or sendServerBinaryMessage:{@link #ByteRTCVideo#sendServerBinaryMessage:} Before sending a message to the application server, you must set a valid signature and application server address.
 * @param signature Dynamic signature. The App server may use the signature to verify the source of messages.<br>
 *        You need to define the signature yourself. It can be any non-empty string. It is recommended to encode information such as UID into the signature.<br>
 *        The signature will be sent to the address set through the "url" parameter in the form of a POST request.
 * @param url Address of the application server
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note   
 *        + The user must call login:uid:{@link #ByteRTCVideo#login:uid:} before logging in to call this interface. <br>
 *        + After calling this interface, the SDK will use rtcEngine:onServerParamsSetResult:{@link #ByteRTCVideoDelegate#rtcEngine:onServerParamsSetResult:} to return the corresponding result.
 */
- (int)setServerParams:(NSString * _Nonnull)signature url:(NSString * _Nonnull)url;
/**
 * @locale zh
 * @type api
 * @region 实时消息通信
 * @brief 查询对端用户或本端用户的登录状态
 * @param peerUserId  <br>
 *        需要查询的用户 ID
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note  
 *       + 必须调用 login:uid:{@link #ByteRTCVideo#login:uid:} 登录后，才能调用本接口。  <br>
 *       + 调用本接口后，SDK 会使用 rtcEngine:onGetPeerOnlineStatus:status:{@link #ByteRTCVideoDelegate#rtcEngine:onGetPeerOnlineStatus:status:} 回调通知查询结果。  <br>
 *       + 在发送房间外消息之前，用户可以通过本接口了解对端用户是否登录，从而决定是否发送消息。也可以通过本接口查询自己查看自己的登录状态。
 */
/**
 * @locale en
 * @type api
 * @region Real-time messaging
 * @brief Query the login status of the opposite or local user
 * @param peerUserId   <br>
 *        User ID to query
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note   
 *        + You must call login:uid:{@link #ByteRTCVideo#login:uid:} After logging in, you can call this interface. <br>
 *        + After calling this interface, the SDK will use rtcEngine:onGetPeerOnlineStatus:status:{@link #ByteRTCVideoDelegate#rtcEngine:onGetPeerOnlineStatus:status:} callback to notify the query result. <br>
 *        + Before sending an out-of-room message, the user can know whether the peer user is logged in through this interface to decide whether to send a message. You can also check your login status through this interface.
 */
- (int)getPeerOnlineStatus:(NSString * _Nonnull)peerUserId;
/**
 * @locale zh
 * @type api
 * @region 实时消息通信
 * @brief 给房间外指定的用户发送文本消息（P2P）
 * @param userId  <br>
 *        消息接收用户的 ID
 * @param messageStr  <br>
 *        发送的文本消息内容  <br>
 *        消息不超过 64 KB。
 * @param config 消息类型，参看 ByteRTCMessageConfig{@link #ByteRTCMessageConfig}。
 * @return  
 *        + >0：发送成功，返回这次发送消息的编号，从 1 开始递增  <br>
 *        + -1：发送失败，ByteRTCVideo 实例未创建  <br>
 *        + -2：发送失败，userId 为空
 * @note  
 *       + 在发送房间外文本消息前，必须先调用 login:uid:{@link #ByteRTCVideo#login:uid:} 完成登录。  <br>
 *       + 用户调用本接口发送文本信息后，会收到一次 rtcEngine:onUserMessageSendResultOutsideRoom:error:{@link #ByteRTCVideoDelegate#rtcEngine:onUserMessageSendResultOutsideRoom:error:} 回调，得知消息是否成功发送；  <br>
 *       + 若文本消息发送成功，则 userId 所指定的用户会通过 rtcEngine:onUserMessageReceivedOutsideRoom:message:{@link #ByteRTCVideoDelegate#rtcEngine:onUserMessageReceivedOutsideRoom:message:} 回调收到该消息。
 */
/**
 * @locale en
 * @type api
 * @region Real-time messaging
 * @brief Sends a text message (P2P) to a specified user outside the room
 * @param userId   <br>
 *        Message Receives the user's ID
 * @param messageStr   <br>
 *        Text message content sent <br>
 *        Message does not exceed 64 KB.
 * @param config Message type, see ByteRTCMessageConfig{@link #ByteRTCMessageConfig}.
 * @return   
 *         + > 0: Sent successfully, return the number of the sent message, increment from 1 <br>
 *         + -1: Sent failed, ByteRTCVideo instance not created <br>
 *         + -2: Sent failed, userId is empty
 * @note   
 *        + Before sending an out-of-room text message, you should call login:uid:{@link #ByteRTCVideo#login:uid:} to complete login. <br>
 *        + After the user calls this interface to send a text message, he will receive an rtcEngine:onUserMessageSendResultOutsideRoom:error:{@link #ByteRTCVideoDelegate#rtcEngine:onUserMessageSendResultOutsideRoom:error:} callback to know whether the message was sent successfully; <br>
 *        + If the text message is sent successfully, the user specified by the userId will receive the message through rtcEngine:onUserMessageReceivedOutsideRoom:message:{@link #ByteRTCVideoDelegate#rtcEngine:onUserMessageReceivedOutsideRoom:message:} callback.
 */
- (NSInteger)sendUserMessageOutsideRoom:(NSString * _Nonnull)userId message:(NSString * _Nonnull)messageStr config:(ByteRTCMessageConfig)config;
/**
 * @locale zh
 * @type api
 * @region 实时消息通信
 * @brief 给房间外指定的用户发送二进制消息（P2P）
 * @param userId  <br>
 *        消息接收用户的 ID
 * @param messageStr  <br>
 *        发送的二进制消息内容  <br>
 *        消息不超过 46KB。
 * @param config 消息类型，参看 ByteRTCMessageConfig{@link #ByteRTCMessageConfig}。
 * @return  
 *        + >0：发送成功，返回这次发送消息的编号，从 1 开始递增  <br>
 *        + -1：发送失败，ByteRTCVideo 实例未创建  <br>
 *        + -2：发送失败，userId 为空
 * @note  
 *       + 在发送房间外二进制消息前，必须先调用 login:uid:{@link #ByteRTCVideo#login:uid:} 完成登录。  <br>
 *       + 用户调用本接口发送二进制消息后，会收到一次 rtcEngine:onUserMessageSendResultOutsideRoom:error:{@link #ByteRTCVideoDelegate#rtcEngine:onUserMessageSendResultOutsideRoom:error:} 回调，通知消息是否发送成功；  <br>
 *       + 若二进制消息发送成功，则 userId 所指定的用户会通过 rtcEngine:onUserBinaryMessageReceivedOutsideRoom:message:{@link #ByteRTCVideoDelegate#rtcEngine:onUserBinaryMessageReceivedOutsideRoom:message:}  回调收到该条消息。
 */
/**
 * @locale en
 * @type api
 * @region Real-time messaging
 * @brief Send binary messages (P2P) to the specified user outside the room
 * @param userId   <br>
 *        Message receiving user's ID
 * @param messageStr   <br>
 *        Binary message content sent <br>
 *        Message does not exceed 46KB.
 * @param config Message type, see ByteRTCMessageConfig{@link #ByteRTCMessageConfig}.
 * @return   
 *         + > 0: Sent successfully, return the number of the sent message, increment from 1 <br>
 *         + -1: Sent failed, ByteRTCVideo instance not created <br>
 *         + -2: Sent failed, userId is empty
 * @note   
 *        + Before sending out-of-room binary messages, you must call login:uid:{@link #ByteRTCVideo#login:uid:} to complete login. <br>
 *        + After the user calls this interface to send a binary message, he will receive an rtcEngine:onUserMessageSendResultOutsideRoom:error:{@link #ByteRTCVideoDelegate#rtcEngine:onUserMessageSendResultOutsideRoom:error:} callback to notify whether the message was sent successfully; <br>
 *        + If the binary message is sent successfully, the user specified by the userId will use rtcEngine:onUserBinaryMessageReceivedOutsideRoom:message:{@link #ByteRTCVideoDelegate#rtcEngine:onUserBinaryMessageReceivedOutsideRoom:message:} callback Receive the message.
 */
- (NSInteger)sendUserBinaryMessageOutsideRoom:(NSString * _Nonnull)userId message:(NSData * _Nonnull)messageStr config:(ByteRTCMessageConfig)config;
/**
 * @locale zh
 * @type api
 * @region 实时消息通信
 * @brief 客户端给应用服务器发送文本消息（P2Server）
 * @param messageStr  <br>
 *        发送的文本消息内容  <br>
 *        消息不超过 64 KB。
 * @return  
 *        + >0：发送成功，返回这次发送消息的编号，从 1 开始递增  <br>
 *        + -1：发送失败，ByteRTCVideo 实例未创建
 * @note  
 *       + 在向应用服务器发送文本消息前，必须先调用 login:uid:{@link #ByteRTCVideo#login:uid:} 完成登录，随后调用 setServerParams:url:{@link #ByteRTCVideo#setServerParams:url:} 设置应用服务器。  <br>
 *       + 调用本接口后，会收到一次 rtcEngine:onServerMessageSendResult:error:message:{@link #ByteRTCVideoDelegate#rtcEngine:onServerMessageSendResult:error:message:} 回调，通知消息发送方是否发送成功。  <br>
 *       + 若文本消息发送成功，则之前调用 setServerParams:url:{@link #ByteRTCVideo#setServerParams:url:} 设置的应用服务器会收到该条消息。
 */
/**
 * @locale en
 * @type api
 * @region Real-time messaging
 * @brief Client side sends a text message to the application server (P2Server)
 * @param messageStr   <br>
 *        The content of the text message sent <br>
 *        The message does not exceed 64 KB.
 * @return   
 *         + > 0: Sent successfully, return the number of the sent message, increment from 1 <br>
 *         + -1: Sent failed, ByteRTCVideo instance not created
 * @note   
 *        + Before sending a text message to the application server, you must first call login:uid:{@link #ByteRTCVideo#login:uid:} to complete the login, and then call setServerParams:url:{@link #ByteRTCVideo#setServerParams:url:} Set up the application server. <br>
 *        + After calling this interface, you will receive an rtcEngine:onServerMessageSendResult:error:message:{@link #ByteRTCVideoDelegate#rtcEngine:onServerMessageSendResult:error:message:} callback to inform the message sender whether the message was sent successfully. <br>
 *        + If the text message is sent successfully, the application server that previously called setServerParams:url:{@link #ByteRTCVideo#setServerParams:url:} will receive the message.
 */
- (NSInteger)sendServerMessage:(NSString * _Nonnull)messageStr;
/**
 * @locale zh
 * @type api
 * @region 实时消息通信
 * @brief 客户端给应用服务器发送二进制消息（P2Server）
 * @param messageStr  <br>
 *        发送的二进制消息内容  <br>
 *        消息不超过 46KB。
 * @return  
 *        + >0：发送成功，返回这次发送消息的编号，从 1 开始递增  <br>
 *        + -1：发送失败，ByteRTCVideo 实例未创建
 * @note  
 *       + 在向应用服务器发送二进制消息前，先调用 login:uid:{@link #ByteRTCVideo#login:uid:} 完成登录，随后调用 setServerParams:url:{@link #ByteRTCVideo#setServerParams:url:} 设置应用服务器。  <br>
 *       + 调用本接口后，会收到一次 rtcEngine:onServerMessageSendResult:error:message:{@link #ByteRTCVideoDelegate#rtcEngine:onServerMessageSendResult:error:message:} 回调，通知消息发送方发送成功或失败；  <br>
 *       + 若二进制消息发送成功，则之前调用 setServerParams:url:{@link #ByteRTCVideo#setServerParams:url:} 设置的应用服务器会收到该条消息。
 */
/**
 * @locale en
 * @type api
 * @region Real-time messaging
 * @brief Client side sends binary messages to the application server (P2Server)
 * @param messageStr   <br>
 *        Binary message content sent <br>
 *        Message does not exceed 46KB.
 * @return   
 *         + > 0: Send successfully, return the number of the sent message, increment from 1 <br>
 *         + -1: Send failed, ByteRTCVideo instance not created
 * @note   
 *        + Before sending a binary message to the application server, call login:uid:{@link #ByteRTCVideo#login:uid:} to complete the login, then call setServerParams:url:{@link #ByteRTCVideo#setServerParams:url:} Set up the application server. <br>
 *        + After calling this interface, you will receive an rtcEngine:onServerMessageSendResult:error:message:{@link #ByteRTCVideoDelegate#rtcEngine:onServerMessageSendResult:error:message:} callback to inform the message sender that the sending succeeded or failed; <br>
 *        + If the binary message is sent successfully, the application server that previously called setServerParams:url:{@link #ByteRTCVideo#setServerParams:url:} will receive the message.
 */
- (NSInteger)sendServerBinaryMessage:(NSData * _Nonnull)messageStr;
/**
 * @locale zh
 * @type api
 * @region 通话前网络探测
 * @brief 开始通话前网络探测
 * @param isTestUplink  是否探测上行带宽
 * @param expectedUplinkBitrate  期望上行带宽，单位：kbps<br>范围为 {0, [100-10000]}，其中， `0` 表示由 SDK 指定最高码率。
 * @param isTestDownlink  是否探测下行带宽
 * @param expectedDownlinkBitrate  期望下行带宽，单位：kbps<br>范围为 {0, [100-10000]}，其中， `0` 表示由 SDK 指定最高码率。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note  
 *       + 成功调用本接口后，会在 3s 内收到一次 rtcEngine:onNetworkDetectionResult:quality:rtt:lostRate:bitrate:jitter:{@link #ByteRTCVideoDelegate#rtcEngine:onNetworkDetectionResult:quality:rtt:lostRate:bitrate:jitter:} 回调，此后每 2s 会收到一次该回调，通知探测结果；  <br>
 *       + 若探测停止，则会收到一次 rtcEngine:onNetworkDetectionStopped:{@link #ByteRTCVideoDelegate#rtcEngine:onNetworkDetectionStopped:} 通知探测停止。
 */
/**
 * @locale en
 * @type api
 * @region Pre-call network detection
 * @brief Pre-call network detection
 * @param isTestUplink Whether to detect uplink bandwidth
 * @param expectedUplinkBitrate Expected uplink bandwidth, unit: kbps<br>Range: {0, [100-10000]}, `0`: Auto, that RTC will set the highest bite rate.
 * @param isTestDownlink Whether to detect downlink bandwidth
 * @param expectedDownlinkBitrate Expected downlink bandwidth, unit: kbps<br>Range: {0, [100-10000]}, `0`: Auto, that RTC will set the highest bite rate.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note   
 *        + After calling this interface, you will receive rtcEngine:onNetworkDetectionResult:quality:rtt:lostRate:bitrate:jitter:{@link #ByteRTCVideoDelegate#rtcEngine:onNetworkDetectionResult:quality:rtt:lostRate:bitrate:jitter:} within 3s and every 2s thereafter notifying the probe result; <br>
 *        + If the probe stops, you will receive rtcEngine:onNetworkDetectionStopped:{@link #ByteRTCVideoDelegate#rtcEngine:onNetworkDetectionStopped:} Notify probe to stop.
 */
- (int)startNetworkDetection:(bool)isTestUplink uplinkBandwidth:(int)expectedUplinkBitrate downlink:(bool)isTestDownlink downlinkBandwidth:(int)expectedDownlinkBitrate;
/**
 * @locale zh
 * @type api
 * @region 通话前网络探测expectedDownlinkBitrate
 * @brief 停止通话前网络探测
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note  
 *       调用本接口后，会收到一次 rtcEngine:onNetworkDetectionStopped:{@link #ByteRTCVideoDelegate#rtcEngine:onNetworkDetectionStopped:} 通知探测停止。
 */
/**
 * @locale en
 * @type api
 * @region Pre-call network probe
 * @brief Stop pre-call network probe
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note   
 *        + After calling this interface, you will receive an rtcEngine:onNetworkDetectionStopped:{@link #ByteRTCVideoDelegate#rtcEngine:onNetworkDetectionStopped:} notification to stop the probe.
 */
- (int)stopNetworkDetection;
#pragma mark  ScreenAudio
/**
 * @locale zh
 * @type api
 * @region 屏幕共享
 * @brief 在屏幕共享时，设置屏幕音频的采集方式（内部采集/自定义采集）
 * @param sourceType 屏幕音频输入源类型, 参看 ByteRTCAudioSourceType{@link #ByteRTCAudioSourceType}。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note  
 *      + 默认采集方式是 RTC SDK 内部采集。<br>
 *      + 你应该在 publishScreen:{@link #ByteRTCRoom#publishScreen:} 前，调用此方法。否则，你将收到 rtcEngine:onWarning:{@link #ByteRTCVideoDelegate#rtcEngine:onWarning:} 的报错：`ByteRTCWarningSetScreenAudioSourceTypeFailed`。 <br>
 *      + 如果设定为内部采集，你必须重新开始采集。<br>
 *      + 如果设定为自定义采集，你必须再调用 pushScreenAudioFrame:{@link #ByteRTCVideo#pushScreenAudioFrame:} 将自定义采集到的屏幕音频帧推送到 RTC SDK。<br>
 *      + 无论是内部采集还是自定义采集，你都必须调用 publishScreen:{@link #ByteRTCRoom#publishScreen:} 将采集到的屏幕音频发布给远端。
 */
/**
 * @locale en
 * @type api
 * @region Screen Sharing
 * @brief Sets the screen audio source type. (internal capture/custom capture)
 * @param sourceType Screen audio source type. See ByteRTCAudioSourceType{@link #ByteRTCAudioSourceType}.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note   
 *       + The default screen audio source type is RTC SDK internal capture. <br>
 *       + You should call this API before calling publishScreen:{@link #ByteRTCRoom#publishScreen:}. Otherwise, you will receive rtcEngine:onWarning:{@link #ByteRTCVideoDelegate#rtcEngine:onWarning:} with 'ByteRTCWarningSetScreenAudioSourceTypeFailed'. <br>
 *       + When using internal capture, you need to restart screen capture.<br>
 *       + When using custom capture, you need to call pushScreenAudioFrame:{@link #ByteRTCVideo#pushScreenAudioFrame:} to push the audio stream to the RTC SDK. <br>
 *       + Whether you use internal capture or custom capture, you must call publishScreen:{@link #ByteRTCRoom#publishScreen:} to publish the captured screen audio stream.
 */
- (int)setScreenAudioSourceType:(ByteRTCAudioSourceType)sourceType;
/**
 * @locale zh
 * @type api
 * @region 屏幕共享
 * @brief 在屏幕共享时，设置屏幕音频流和麦克风采集到的音频流的混流方式
 * @param index 混流方式，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex} <br>
 *        + `ByteRTCStreamIndexMain`: 将屏幕音频流和麦克风采集到的音频流混流 <br>
 *        + `ByteRTCStreamIndexScreen`: 默认值，将屏幕音频流和麦克风采集到的音频流分为两路音频流
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note 你应该在 publishScreen:{@link #ByteRTCRoom#publishScreen:} 之前，调用此方法。否则，你将收到 rtcEngine:onWarning:{@link #ByteRTCVideoDelegate#rtcEngine:onWarning:} 的报错：`ByteRTCWarningSetScreenAudioStreamIndexFailed`
 */
/**
 * @locale en
 * @type api
 * @region Screen sharing
 * @brief Sets the mix mode of the screen audio stream and the audio stream collected by the microphone when the screen is shared
 * @param index Mix mode. See ByteRTCStreamIndex{@link #ByteRTCStreamIndex} <br>
 *         + 'ByteRTCStreamIndexMain': Mix the audio stream collected by the screen audio stream and the microphone <br>
 *         + 'ByteRTCStreamIndexScreen': By default, it divides the screen audio stream and the audio stream collected by the microphone into two audio streams
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note You should call this method before publishScreen:{@link #ByteRTCRoom#publishScreen:}. Otherwise, you will receive 'ByteRTCWarningSetScreenAudioStreamIndexFailed' from rtcEngine:onWarning:{@link #ByteRTCVideoDelegate#rtcEngine:onWarning:}
 */
- (int)setScreenAudioStreamIndex:(ByteRTCStreamIndex) index;
/**
 * @locale zh
 * @type api
 * @region 屏幕共享
 * @brief 使用自定义采集方式，采集屏幕共享时的屏幕音频时，将音频帧推送至 RTC SDK 处进行编码等处理。
 * @param audioFrame 音频数据帧，参见 ByteRTCAudioFrame{@link #ByteRTCAudioFrame}<br>
 *                   + 音频采样格式为 S16。音频缓冲区内的数据格式必须为 PCM 数据，其容量大小应该为 samples × frame.channel × 2。  <br>
 *                   + 必须指定具体的采样率和声道数，不支持设置为自动。
 * @return 方法调用结果  <br>
 *        + 0: 设置成功  <br>
 *        + < 0: 设置失败  
 * @note  
 *        + 调用此接口推送屏幕共享时的自定义采集的音频数据前，必须调用 setScreenAudioSourceType:{@link #ByteRTCVideo#setScreenAudioSourceType:} 开启屏幕音频自定义采集。  <br>
 *        + 你应每隔 10 毫秒，调用一次此方法推送一次自定义采集的音频帧。一次推送的音频帧中应包含 frame.sample_rate / 100 个音频采样点。比如，假如采样率为 48000Hz，则每次应该推送 480 个采样点。  <br>
 *        + 调用此接口将自定义采集的音频帧推送到 RTC SDK 后，你必须调用 publishScreen:{@link #ByteRTCRoom#publishScreen:} 将采集到的屏幕音频推送到远端。在调用 publishScreen:{@link #ByteRTCRoom#publishScreen:} 前，推送到 RTC SDK 的音频帧信息会丢失。
 */
/**
 * @locale en
 * @type api
 * @region Screen Sharing
 * @brief Using a custom capture method, when capturing screen audio during screen sharing, push the audio frame to the RTC SDK for encoding and other processing.
 * @param audioFrame Audio data frame. See ByteRTCAudioFrame{@link #ByteRTCAudioFrame}
 * @return Method call result   <br>
 *         + 0: Setup succeeded <br>
 *         + < 0: Setup failed 
 * @note   
 *         + You must call this API after calling setScreenAudioSourceType:{@link #ByteRTCVideo#setScreenAudioSourceType:} to enable custom capture of the screen audio. <br>
 *         + You should call this method every 10 milliseconds to push a custom captured audio frame. A push audio frame should contain frame.sample _rate/100 audio sample points. For example, if the sampling rate is 48000Hz, 480 sampling points should be pushed each time. <br>
 *         + The audio sampling format is S16. The data format in the audio buffer must be PCM data, and its capacity size should be samples × frame.channel × 2. <br>
 *         + After calling this interface to push the custom captured audio frame to the RTC SDK, you must call publishScreen:{@link #ByteRTCRoom#publishScreen:} to push the captured screen audio to the remote end. Audio frame information pushed to the RTC SDK is lost before calling publishScreen:{@link #ByteRTCRoom#publishScreen:}.
 */
- (int) pushScreenAudioFrame:(ByteRTCAudioFrame* _Nonnull)audioFrame;

#if BYTERTC_TARGET_MAC
/**
 * @locale zh
 * @hidden(iOS)
 * @type api
 * @region 屏幕共享
 * @brief 在屏幕共享时，开始使用 RTC SDK 内部采集方式，采集屏幕音频
 * @param deviceId 虚拟设备 ID
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note 
 *        + 调用本接口时，采集模式应为内部模式。在外部采集模式下调用无效，并将触发 rtcEngine:onAudioDeviceWarning:deviceType:deviceWarning:{@link #ByteRTCVideoDelegate#rtcEngine:onAudioDeviceWarning:deviceType:deviceWarning:} 回调。<br>
 *        + 采集后，你还需要调用 publishScreen:{@link #ByteRTCRoom#publishScreen:} 将采集到的屏幕音频推送到远端。<br>
 *        + 要关闭屏幕音频内部采集，调用 stopScreenAudioCapture{@link #ByteRTCVideo#stopScreenAudioCapture}。
 */
/**
 * @locale en
 * @hidden(iOS)
 * @type api
 * @region screen sharing
 * @brief Starts using RTC SDK internal capture to capture screen audio during screen sharing.
 * @param deviceId ID of the virtual device
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note  
 *         + The call of this API takes effects only when you are using RTC SDK to record screen. You will get a warning by rtcEngine:onAudioDeviceWarning:deviceType:deviceWarning:{@link #ByteRTCVideoDelegate#rtcEngine:onAudioDeviceWarning:deviceType:deviceWarning:} after calling this API when the video source is set to an external recorder.<br>
 *         + You also need to call publishScreen:{@link #ByteRTCRoom#publishScreen:} to publish the captured screen audio. <br>
 *         + To disable screen audio internal capture, call stopScreenAudioCapture{@link #ByteRTCVideo#stopScreenAudioCapture}.
 */
- (int)startScreenAudioCapture:(NSString *_Nonnull)deviceId;
/**
 * @locale zh
 * @hidden(iOS)
 * @type api
 * @region 屏幕共享
 * @brief 在屏幕共享时，停止使用 RTC SDK 内部采集方式，采集屏幕音频。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note  
 *        + 调用本接口时，采集模式应为内部模式。在外部采集模式下调用无效，并将触发 rtcEngine:onAudioDeviceWarning:deviceType:deviceWarning:{@link #ByteRTCVideoDelegate#rtcEngine:onAudioDeviceWarning:deviceType:deviceWarning:} 回调。<br>
 *        + 要开始屏幕音频内部采集，调用 startScreenAudioCapture:{@link #ByteRTCVideo#startScreenAudioCapture:}。
 */
/**
 * @locale en
 * @hidden(iOS)
 * @type api
 * @region Screen sharing
 * @brief Stops using RTC SDK internal capture to capture screen audio during screen sharing.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note 
 *        + The call of this API takes effects only when you are using RTC SDK to record screen. You will get a warning by rtcEngine:onAudioDeviceWarning:deviceType:deviceWarning:{@link #ByteRTCVideoDelegate#rtcEngine:onAudioDeviceWarning:deviceType:deviceWarning:} after calling this API when the video source is set to an external recorder.<br>
 *        + This API can only stop the screen capture by the RTC SDK. If the video source has been set to external recorder, the call of this API will fail with a warning message. You need to stop it in the external recorder. <br>
 *        + To enable the screen audio internal capture, call startScreenAudioCapture:{@link #ByteRTCVideo#startScreenAudioCapture:}.
 */
- (int)stopScreenAudioCapture;
/**
 * @locale zh
 * @hidden(iOS)
 * @type api
 * @region 屏幕共享
 * @brief 在屏幕共享时，设置屏幕音频流的声道数
 * @param channel 声道数，参看 ByteRTCAudioChannel{@link #ByteRTCAudioChannel}
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note 当你调用 setScreenAudioStreamIndex:{@link #ByteRTCVideo#setScreenAudioStreamIndex:} 并设置屏幕音频流和麦克风音频流混流时，此接口不生效，音频通道数由 setAudioProfile:{@link #ByteRTCVideo#setAudioProfile:} 控制。
 */
/**
 * @locale en
 * @hidden(iOS)
 * @type api
 * @region Screen sharing
 * @brief Set the audio channel of the screen-sharing audio stream
 * @param channel The number of Audio channels. See ByteRTCAudioChannel{@link #ByteRTCAudioChannel}.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note When you call setScreenAudioStreamIndex:{@link #ByteRTCVideo#setScreenAudioStreamIndex:} to mix the microphone audio stream and the screen-sharing audio stream, the audio channel is set by setAudioProfile:{@link #ByteRTCVideo#setAudioProfile:} rather than this API.
 */
- (int)setScreenAudioChannel:(ByteRTCAudioChannel) channel;

#endif

#pragma mark EncodedVideo

/**
 * @locale zh
 * @type api
 * @region 视频管理
 * @brief 设置向 SDK 输入的视频源，包括屏幕流<br>
 *        默认使用内部采集。内部采集指：使用 RTC SDK 内置的视频采集机制进行视频采集。 
 * @param type 视频输入源类型，参看 ByteRTCVideoSourceType{@link #ByteRTCVideoSourceType}
 * @param streamIndex 视频流的属性，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note  
 *        + 该方法进房前后均可调用。  <br>
 *        + 当你已调用 startVideoCapture{@link #ByteRTCVideo#startVideoCapture} 开启内部采集后，再调用此方法切换至自定义采集时，SDK 会自动关闭内部采集。  <br>
 *        + 当你调用此方法开启自定义采集后，想要切换至内部采集，你必须先调用此方法关闭自定义采集，然后调用 startVideoCapture{@link #ByteRTCVideo#startVideoCapture} 手动开启内部采集。<br>
 *        + 当你需要向 SDK 推送自定义编码后的视频帧，你需调用该方法将视频源切换至自定义编码视频源。
 */
/**
 * @locale en
 * @type api
 * @region Video Management
 * @brief Set the video source, including the screen recordings.<br>
 *        The internal video capture is the default, which refers to capturing video using the built-in module.
 * @param type Video source type. Refer to ByteRTCVideoSourceType{@link #ByteRTCVideoSourceType} for more details.
 * @param streamIndex Stream index. Refer to ByteRTCStreamIndex{@link #ByteRTCStreamIndex} for more details.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note   
 *         + You can call this API whether the user is in a room or not. <br>
 *         + Calling this API to switch to the custom video source will stop the enabled internal video capture.<br>
 *         + To switch to internal video capture, call this API to stop custom capture and then call startVideoCapture{@link #ByteRTCVideo#startVideoCapture} to enable internal video capture.<br>
 *         + To push custom encoded video frames to the SDK, call this API to switch `ByteRTCVideoSourceType` to `ByteRTCVideoSourceTypeEncodedManualSimulcast` or `ByteRTCVideoSourceTypeEncodedAutoSimulcast`.
 */
- (int)setVideoSourceType:(ByteRTCVideoSourceType)type WithStreamIndex:(ByteRTCStreamIndex)streamIndex NS_SWIFT_NAME(setVideoSourceType(_:WithStreamIndex:));
/**
 * @locale zh
 * @type api
 * @region 视频管理
 * @brief 注册自定义编码帧推送事件回调
 * @param handler 自定义编码帧回调类，参看 ByteRTCExternalVideoEncoderEventHandler{@link #ByteRTCExternalVideoEncoderEventHandler}
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note  
 *       + 该方法需在进房前调用。 <br>
 *       + 引擎销毁前需取消注册，调用该方法将参数设置为 nullptr 即可。
 */
/**
 * @locale en
 * @type api
 * @region Video management
 * @brief Register custom encoded frame push event callback
 * @param handler Custom encoded frame callback class. See ByteRTCExternalVideoEncoderEventHandler{@link #ByteRTCExternalVideoEncoderEventHandler}
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note   
 *        + This method needs to be called before entering the room. <br>
 *        + The engine needs to be unregistered before it is destroyed. Call this method to set the parameter to nullptr.
 */
- (int)setExternalVideoEncoderEventHandler:(id<ByteRTCExternalVideoEncoderEventHandler> _Nullable)handler;
/**
 * @locale zh
 * @type api
 * @region 视频管理
 * @brief 推送自定义编码后的视频流
 * @param streamIndex 需要推送的编码流的属性，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param videoIndex 对应的编码流下标，从 0 开始，如果调用 setVideoEncoderConfig:{@link #ByteRTCVideo#setVideoEncoderConfig:} 设置了多路流，此处数量须与之保持一致
 * @param videoFrame 编码流视频帧信息，参看 ByteRTCEncodedVideoFrame{@link #ByteRTCEncodedVideoFrame}。
 * @return 方法调用结果：<br>
 *        + 0：成功；<br>
 *        + <0：失败。具体失败原因参看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus}。
 * @note  
 *        + 目前仅支持推送 H264 和 ByteVC1 格式的视频帧，且视频流协议格式须为 Annex B 格式。  <br>
 *        + 该函数运行在用户调用线程内  <br>
 *        + 推送自定义编码视频帧前，必须调用 setVideoSourceType:WithStreamIndex:{@link #ByteRTCVideo#setVideoSourceType:WithStreamIndex:} 将视频输入源切换至自定义编码视频源。
 */
/**
 * @locale en
 * @type api
 * @region Video management
 * @brief Push custom encoded video stream
 * @param streamIndex The properties of the encoded stream that need to be pushed. See ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param videoIndex The corresponding encoded stream subscript, starting from 0, if you call setVideoEncoderConfig:{@link #ByteRTCVideo#setVideoEncoderConfig:} The number of multiple streams must be consistent here
 * @param videoFrame Encoding For streaming video frame information. See ByteRTCEncodedVideoFrame{@link #ByteRTCEncodedVideoFrame}.
 * @return API call result:<br>
 *        + 0: Success.<br>
 *        + <0: Failure. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for specific reasons.
 * @note  
 *        + Currently, only video frames in H264 and ByteVC1 formats are supported, and the video stream protocol must be in an Annex B format. <br>
 *        + This function runs within the user calling thread <br>
 *        + Before pushing a custom encoded video frame, you must call setVideoSourceType:WithStreamIndex:{@link #ByteRTCVideo#setVideoSourceType:WithStreamIndex:} to switch the video input source to the custom encoded video source.
 */
- (int)pushExternalEncodedVideoFrame:(ByteRTCStreamIndex)streamIndex
                       withVideoIndex:(NSInteger)videoIndex
                withEncodedVideoFrame:(ByteRTCEncodedVideoFrame* _Nonnull)videoFrame NS_SWIFT_NAME(pushExternalEncodedVideoFrame(_:withVideoIndex:withEncodedVideoFrame:));
/**
 * @locale zh
 * @type api
 * @region 视频管理
 * @brief 在订阅远端视频流之前，设置远端视频数据解码方式
 * @param key 远端流信息，指定对哪一路视频流进行解码方式设置，参看 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}。
 * @param config 视频解码方式，参看 ByteRTCVideoDecoderConfig{@link #ByteRTCVideoDecoderConfig}。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note  
 *        + 当你想要对远端流进行自定义解码时，你需要先调用 registerRemoteEncodedVideoFrameObserver:{@link #ByteRTCVideo#registerRemoteEncodedVideoFrameObserver:} 注册远端视频流监测器，然后再调用该接口将解码方式设置为自定义解码。监测到的视频数据会通过 onRemoteEncodedVideoFrame:withEncodedVideoFrame:{@link #ByteRTCRemoteEncodedVideoFrameObserver#onRemoteEncodedVideoFrame:withEncodedVideoFrame:} 回调出来。<br>
 *        + 自 3.56 起，要用于自动订阅场景下，你可以设置 `key` 中的 `RoomId` 和 `UserId` 为 `nullptr`，此时，通过此接口设置的解码方式根据 `key` 中的 `StreamIndex` 值，适用于所有的远端主流或屏幕流的解码方式。
 */
/**
 * @locale en
 * @type api
 * @region Video Management
 * @brief Before subscribing to the remote video stream, set the remote video data decoding method
 * @param key The remote stream information specifies which video stream to decode. See ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}.
 * @param config  Video decoding method. See ByteRTCVideoDecoderConfig{@link #ByteRTCVideoDecoderConfig}.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note   
 *         + When you want to custom decode a remote stream, you need to call registerRemoteEncodedVideoFrameObserver:{@link #ByteRTCVideo#registerRemoteEncodedVideoFrameObserver:} Register the remote video stream monitor, and then call the interface to set the decoding method to custom decoding. The monitored video data is called back through onRemoteEncodedVideoFrame:withEncodedVideoFrame:{@link #ByteRTCRemoteEncodedVideoFrameObserver#onRemoteEncodedVideoFrame:withEncodedVideoFrame:}.<br>
 *        + Since version 3.56, for automatic subscription, you can set the `RoomId` and `UserId` of `key` as `nullptr`. In this case, the decoding settings set by calling the API applies to all remote main streams or screen sharing streams based on the `StreamIndex` value of `key`.
 */
- (int)setVideoDecoderConfig:(ByteRTCRemoteStreamKey * _Nonnull)key
       withVideoDecoderConfig:(ByteRTCVideoDecoderConfig)config NS_SWIFT_NAME(setVideoDecoderConfig(_:withVideoDecoderConfig:));
/**
 * @locale zh
 * @type api
 * @region 视频管理
 * @brief 在订阅远端视频流之后，向远端请求关键帧
 * @param key 远端流信息，参看 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note  
 *        + 该方法仅适用于手动订阅模式，并且在成功订阅远端流之后使用。  <br>
 *        + 该方法适用于调用 setVideoDecoderConfig:withVideoDecoderConfig:{@link #ByteRTCVideo#setVideoDecoderConfig:withVideoDecoderConfig:} 开启自定义解码功能后，并且自定义解码失败的情况下使用
 */
/**
 * @locale en
 * @type api
 * @region Video Management
 * @brief After subscribing to the remote video stream, request the keyframe
 * @param key Remote stream information to the remote. See ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note   
 *         + This method is only suitable for manual subscription mode and is used after successful subscription to the remote flow. <br>
 *         + This method is suitable for calling setVideoDecoderConfig:withVideoDecoderConfig:{@link #ByteRTCVideo#setVideoDecoderConfig:withVideoDecoderConfig:} After the custom decoding function is turned on, and the custom decoding fails
 */
- (int)requestRemoteVideoKeyFrame:(ByteRTCRemoteStreamKey * _Nonnull)key;
/**
 * @locale zh
 * @type api
 * @region 视频管理
 * @brief 注册远端编码后视频数据回调。  <br>
 *        完成注册后，当 SDK 监测到远端编码后视频帧时，会触发 onRemoteEncodedVideoFrame:withEncodedVideoFrame:{@link #ByteRTCRemoteEncodedVideoFrameObserver#onRemoteEncodedVideoFrame:withEncodedVideoFrame:} 回调
 * @param observer 远端编码后视频数据监测器，参看 ByteRTCRemoteEncodedVideoFrameObserver{@link #ByteRTCRemoteEncodedVideoFrameObserver}
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note  
 *       + 更多自定义解码功能说明参看 [自定义视频编解码](https://www.volcengine.com/docs/6348/82921#%E8%87%AA%E5%AE%9A%E4%B9%89%E8%A7%86%E9%A2%91%E8%A7%A3%E7%A0%81)。<br>
 *       + 该方法适用于手动订阅，并且进房前后均可调用，建议在进房前调用。 <br>
 *       + 引擎销毁前需取消注册，调用该方法将参数设置为 nullptr 即可。
 */
/**
 * @locale en
 * @type api
 * @region  video management
 * @brief  Video data callback after registering remote encoding.   <br>
 *         After registration, when the SDK detects a remote encoded video frame, onRemoteEncodedVideoFrame:withEncodedVideoFrame:{@link #ByteRTCRemoteEncodedVideoFrameObserver#onRemoteEncodedVideoFrame:withEncodedVideoFrame:} callback
 * @param observer Remote encoded video data monitor. See ByteRTCRemoteEncodedVideoFrameObserver{@link #ByteRTCRemoteEncodedVideoFrameObserver}
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note  
 *        + See [Custom Video Encoding and Decoding](https://docs.byteplus.com/byteplus-rtc/docs/82921#custom-video-decoding) for more details about custom video decoding. <br>
 *        + This method applys to manual subscription mode and can be called either before or after entering the Room. It is recommended to call it before entering the room. <br>
 *        + The engine needs to be unregistered before it is destroyed. Call this method to set the parameter to nullptr.
 */
- (int)registerRemoteEncodedVideoFrameObserver:(id<ByteRTCRemoteEncodedVideoFrameObserver> _Nullable)observer NS_SWIFT_NAME(registerRemoteEncodedVideoFrameObserver(_:));
#pragma mark StreamSyncInfo
/**
 * @locale zh
 * @type api
 * @region 音频管理
 * @brief 发送音频流同步信息。将消息通过音频流发送到远端，并实现与音频流同步，该接口调用成功后，远端用户会收到 rtcEngine:onStreamSyncInfoReceived:streamType:data:{@link #ByteRTCVideoDelegate#rtcEngine:onStreamSyncInfoReceived:streamType:data:} 回调。
 * @param data 消息内容。
 * @param config 媒体流信息同步的相关配置，详见 ByteRTCStreamSycnInfoConfig{@link #ByteRTCStreamSycnInfoConfig} 。
 * @return  
 *        + >=0: 消息发送成功。返回成功发送的次数。  <br>
 *        + -1: 消息发送失败。消息长度大于 255 字节。  <br>
 *        + -2: 消息发送失败。传入的消息内容为空。  <br>
 *        + -3: 消息发送失败。通过屏幕流进行消息同步时，此屏幕流还未发布。  <br>
 *        + -4: 消息发送失败。通过用麦克风或自定义设备采集到的音频流进行消息同步时，此音频流还未发布，详见错误码 ByteRTCErrorCode{@link #ByteRTCErrorCode}。  
 * @note
 * + 调用本接口的频率建议不超过 50 次每秒。<br>
 * + 在 `ByteRTCRoomProfileInteractivePodcast` 房间模式下，此消息一定会送达。在其他房间模式下，如果本地用户未说话，此消息不一定会送达。
 */
/**
 * @locale en
 * @type api
 * @region Audio management
 * @brief Sends audio stream synchronization information. The message is sent to the remote end through the audio stream and synchronized with the audio stream. After the interface is successfully called, the remote user will receive rtcEngine:onStreamSyncInfoReceived:streamType:data:{@link #ByteRTCVideoDelegate#rtcEngine:onStreamSyncInfoReceived:streamType:data:}.
 * @param data Message content.
 * @param config  For configuration of media stream information synchronization. See ByteRTCStreamSycnInfoConfig{@link #ByteRTCStreamSycnInfoConfig}.
 * @return   
 *         + > = 0: Message sent successfully. Returns the number of successful sends. <br>
 *         + -1: Message sending failed. Message length greater than 16 bytes. <br>
 *         + -2: Message sending failed. The content of the incoming message is empty. <br>
 *         + -3: Message sending failed. This screen stream was not published when the message was synchronized through the screen stream. <br>
 *         + -4: Message sending failed. This audio stream is not yet published when you synchronize messages with an audio stream captured by a microphone or custom device, as described in the error code ByteRTCErrorCode{@link #ByteRTCErrorCode}. 
 * @note
 * + Regarding the frequency, we recommend no more than 50 calls per second.<br>
 * + When using `ByteRTCRoomProfileInteractivePodcast` as room profile, the data will be delivered. For other coom profiles, the data may be lost when the local user is muted.
 */
- (int)sendStreamSyncInfo:(NSData* _Nonnull)data config:(ByteRTCStreamSycnInfoConfig * _Nonnull)config;
/**
 * @locale zh
 * @deprecated since 3.45 and will be deleted in 3.51, use setPlaybackVolume:{@link #ByteRTCVideo#setPlaybackVolume:} instead.
 * @type api
 * @region 媒体流管理
 * @brief 控制本地音频流播放状态：播放/不播放  
 * @param muteState 播放状态，标识是否播放本地音频流，详见：ByteRTCMuteState{@link #ByteRTCMuteState}
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note 本方法仅控制本地收到音频流的播放状态，并不影响本地音频播放设备。
 */
/**
 * @locale en
 * @deprecated since 3.45 and will be deleted in 3.51, use setPlaybackVolume:{@link #ByteRTCVideo#setPlaybackVolume:} instead.
 * @type api
 * @region Media stream management
 * @brief Plays/Stops playing the local audio stream.
 * @param muteState Playinging status to identify whether to play the local audio stream, see: ByteRTCMuteState{@link #ByteRTCMuteState}
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note This method only controls the local audio The playinging state of the stream but does not affect the local audio playback device.
 */
- (int)muteAudioPlayback:(ByteRTCMuteState)muteState __deprecated_msg("Will be removed in new version");
/**
 * @locale zh
 * @type api
 * @region 网络管理
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
 * @note  
 *        + 调用该方法开始音视频回路检测后，你可以调用 stopEchoTest{@link #ByteRTCVideo#stopEchoTest} 立即结束测试，也可等待测试 60s 后自动结束，以更换设备进行下一次测试，或进房。  <br>
 *        + 在该方法之前调用的所有跟设备控制、流控制相关的方法均在开始检测时失效，在结束检测后恢复生效。  <br>
 *        + 在调用 startEchoTest:playDelay:{@link #ByteRTCVideo#startEchoTest:playDelay:} 和 stopEchoTest{@link #ByteRTCVideo#stopEchoTest} 之间调用的所有跟设备采集、流控制、进房相关的方法均不生效，并会收到 rtcEngine:onWarning:{@link #ByteRTCVideoDelegate#rtcEngine:onWarning:} 回调，提示警告码为 `ByteRTCWarningCodeInEchoTestMode`。  <br>
 *        + 音视频回路检测的结果会通过 rtcEngine:onEchoTestResult:{@link #ByteRTCVideoDelegate#rtcEngine:onEchoTestResult:} 回调通知。
 */
/**
 * @locale en
 * @type api
 * @region Network Management
 * @brief Starts a call test.  <br>
 *        Before entering the room, you can call this API to test whether your local audio/video equipment as well as the upstream and downstream networks are working correctly.  <br>
 *        Once the test starts, SDK will record your sound or video. If you receive the playback within the delay range you set, the test is considered normal.
 * @param echoConfig Test configurations, see ByteRTCEchoTestConfig{@link #ByteRTCEchoTestConfig}.
 * @param delayTime Delayed audio/video playback time specifying how long you expect to receive the playback after starting the. The range of the value is [2,10] in seconds and the default value is 2.
 * @return API call result:  <br>
 *        + 0: Success  <br>
 *        + -1: Failure, testing in progress  <br>
 *        + -2: Failure, the user us already in the room  <br>
 *        + -3: Failure, neither video nor audio is captured  <br>
 *        + -4: Failure, parameter exception  <br>
 *        + -5: Failure, the roomID is already used
 * @note  
 *        + Once you start the test, you can either call stopEchoTest{@link #ByteRTCVideo#stopEchoTest} or wait until the test stops automatically after 60s, to start the next test or enter the room.  <br>
 *        + All APIs related to device control and stream control called before this API are invalidated during the test and are restored after the test.  <br>
 *        + All APIs related to device control, stream control, and room entry called during the test do not take effect, and you will receive rtcEngine:onWarning:{@link #ByteRTCVideoDelegate#rtcEngine:onWarning:} with the warning code `ByteRTCWarningCodeInEchoTestMode`.<br>
 *        + You will receive the test result from rtcEngine:onEchoTestResult:{@link #ByteRTCVideoDelegate#rtcEngine:onEchoTestResult:}.
 */
- (int)startEchoTest:(ByteRTCEchoTestConfig *_Nullable)echoConfig playDelay:(NSInteger)delayTime;
/**
 * @locale zh
 * @type api
 * @region 网络管理
 * @brief 停止音视频回路测试。  <br>
 *        调用 startEchoTest:playDelay:{@link #ByteRTCVideo#startEchoTest:playDelay:} 开启音视频回路检测后，你必须调用该方法停止检测。
 * @return 方法调用结果：  <br>
 *        + 0：成功  <br>
 *        + -1：失败，未开启回路检测
 * @note 音视频回路检测结束后，所有对系统设备及音视频流的控制均会恢复到开始检测前的状态。
 */
/**
 * @locale en
 * @type api
 * @region Network Management
 * @brief Stops the current call test.  <br>
 *        After calling startEchoTest:playDelay:{@link #ByteRTCVideo#startEchoTest:playDelay:}, you must call this API to stop the test.
 * @return API call result:  <br>
 *        + 0: Success  <br>
 *        + -1: Failure, no test is in progress
 * @note After stopping the test with this API, all the system devices and streams are restored to the state they were in before the test.
 */
- (int)stopEchoTest;

/**
 * @locale zh
 * @type api
 * @region 音视频处理
 * @brief 在指定视频流上添加水印。
 * @param streamIndex 需要添加水印的视频流属性，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}。
 * @param imagePath 水印图片路径，仅支持本地文件绝对路径，长度限制为 512 字节。   <br>
 *        水印图片为 PNG 或 JPG 格式。
 * @param rtcWatermarkConfig 水印参数，参看 ByteRTCVideoWatermarkConfig{@link #ByteRTCVideoWatermarkConfig}。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note  
 *        + 调用 clearVideoWatermark{@link #ByteRTCVideo#clearVideoWatermark:} 移除指定视频流的水印。  <br>
 *        + 同一路流只能设置一个水印，新设置的水印会代替上一次的设置。你可以多次调用本方法来设置不同流的水印。  <br>
 *        + 进入房间前后均可调用此方法。  <br>
 *        + 若开启本地预览镜像，或开启本地预览和编码传输镜像，则远端水印均不镜像；在开启本地预览水印时，本端水印会镜像。  <br>
 *        + 开启大小流后，水印对大小流均生效，且针对小流进行等比例缩小。
 */
/**
 * @locale en
 * @type api
 * @region  Audio & Video Processing
 * @brief Adds watermark to designated video stream.
 * @param streamIndex Targeting stream index of the watermark. See ByteRTCStreamIndex{@link #ByteRTCStreamIndex}.
 * @param imagePath The absolute path of the watermark image. The path should be less than 512 bytes.<br>
 *        The watermark image should be in PNG or JPG format.
 * @param rtcWatermarkConfig Watermark configurations. See ByteRTCVideoWatermarkConfig{@link #ByteRTCVideoWatermarkConfig}.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note 
 *        + Call clearVideoWatermark{@link #ByteRTCVideo#clearVideoWatermark:} to remove the watermark on the designated video stream. <br>
 *        + You can only add one watermark to one video stream. The newly added watermark replaces the previous one. You can call this API multiple times to add watermarks to different streams. <br>
 *        + You can call this API before and after joining room. <br>
 *        + If you mirror the preview, or the preview and the published stream, the watermark will also be mirrored locally, but the published watermark will not be mirrored. <br>
 *        + When you enable simulcast mode, the watermark will be added to all video streams, and it will scale down to smaller encoding configurations accordingly. 
 */
- (int)setVideoWatermark:(ByteRTCStreamIndex)streamIndex
            withImagePath:(NSString * _Nullable)imagePath
   withRtcWatermarkConfig:(ByteRTCVideoWatermarkConfig* _Nonnull)rtcWatermarkConfig;
/**
 * @locale zh
 * @type api
 * @region 音视频处理
 * @brief 移除指定视频流的水印。
 * @param streamIndex 需要移除水印的视频流属性，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 */
/**
 * @locale en
 * @type api
 * @region  Audio & Video Processing
 * @brief Removes video watermark from designated video stream.
 * @param streamIndex Targeting stream index of the watermark. See ByteRTCStreamIndex{@link #ByteRTCStreamIndex}.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 */
- (int)clearVideoWatermark:(ByteRTCStreamIndex)streamIndex NS_SWIFT_NAME(clearVideoWatermark(_:));
/**
 * @locale zh
 * @type api
 * @brief 截取本地视频画面
 * @param streamIndex 截图的视频流的属性，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}。
 * @param callback 本地截图的回调。参看 ByteRTCVideoSnapshotCallbackDelegate{@link #ByteRTCVideoSnapshotCallbackDelegate}。
 * @return 本地截图任务的编号，从 `1` 开始递增。
 * @note 
 *        + 对截取的画面，包含本地视频处理的全部效果，包含旋转，镜像，美颜等。<br>
 *        + 不管采用 SDK 内部采集，还是自定义采集，都可以进行截图。
 */
/**
 * @locale en
 * @type api
 * @brief Take a snapshot of the local video.
 * @param streamIndex See ByteRTCStreamIndex{@link #ByteRTCStreamIndex}.
 * @param callback See ByteRTCVideoSnapshotCallbackDelegate{@link #ByteRTCVideoSnapshotCallbackDelegate}.
 * @return The index of the local snapshot task, starting from `1`.
 * @note 
 *        + The snapshot is taken with all video effects on, like rotation, and mirroring. <br>
 *        + You can take the snapshot either using SDK internal video capture or customized capture.
 */
- (NSInteger)takeLocalSnapshot:(ByteRTCStreamIndex)streamIndex callback:(id<ByteRTCVideoSnapshotCallbackDelegate> _Nullable)callback;
/**
 * @locale zh
 * @type api
 * @brief 截取远端视频画面
 * @param streamKey 截图的视频流，参看 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}。
 * @param callback 参看 ByteRTCVideoSnapshotCallbackDelegate{@link #ByteRTCVideoSnapshotCallbackDelegate}。
 * @return 远端截图任务的编号，从 `1` 开始递增。
 */
/**
 * @locale en
 * @type api
 * @brief Take a snapshot of the remote video.
 * @param streamKey See ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}.
 * @param callback See ByteRTCVideoSnapshotCallbackDelegate{@link #ByteRTCVideoSnapshotCallbackDelegate}.
 * @return The index of the remote snapshot task, starting from `1`.
 */
- (NSInteger)takeRemoteSnapshot:(ByteRTCRemoteStreamKey* _Nonnull)streamKey callback:(id<ByteRTCVideoSnapshotCallbackDelegate> _Nullable)callback;
/**
 * @locale zh
 * @type api
 * @region 云代理
 * @brief 开启云代理
 * @param cloudProxiesInfo 云代理服务器信息列表。参看 ByteRTCCloudProxyInfo{@link #ByteRTCCloudProxyInfo}。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note  
 *        + 在加入房间前调用此接口  <br>
 *        + 在开启云代理后，进行通话前网络探测 <br>
 *        + 开启云代理后，并成功链接云代理服务器后，会收到 rtcEngine:onCloudProxyConnected:{@link #ByteRTCVideoDelegate#rtcEngine:onCloudProxyConnected:}。<br>
 *        + 要关闭云代理，调用 stopCloudProxy{@link #ByteRTCVideo#stopCloudProxy}。
 */
/**
 * @locale en
 * @type api
 * @region  cloud proxy
 * @brief Starts cloud proxy
 * @param  cloudProxiesInfo cloud proxy informarion list. See ByteRTCCloudProxyInfo{@link #ByteRTCCloudProxyInfo}.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note   
 *         + Call this API before joining the room.<br>
 *         + Start pre-call network detection after starting cloud proxy. <br>
 *         + After starting cloud proxy and connects the cloud proxy server successfully, receives rtcEngine:onCloudProxyConnected:{@link #ByteRTCVideoDelegate#rtcEngine:onCloudProxyConnected:}. <br>
 *         + To stop cloud proxy, call stopCloudProxy{@link #ByteRTCVideo#stopCloudProxy}.
 */
- (int)startCloudProxy:(NSArray <ByteRTCCloudProxyInfo *> * _Nullable)cloudProxiesInfo;
/**
 * @locale zh
 * @type api
 * @region 云代理
 * @brief 关闭云代理
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note 要开启云代理，调用 startCloudProxy:{@link #ByteRTCVideo#startCloudProxy:}
 */
/**
 * @locale en
 * @type api
 * @region  cloud proxy
 * @brief  Stop cloud proxy
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note To start cloud proxy, call startCloudProxy:{@link #ByteRTCVideo#startCloudProxy:}.
 */
- (int)stopCloudProxy;
/**
 * @locale zh
 * @type api
 * @brief 创建 K 歌评分管理接口。
 * @return K 歌评分管理接口,详见 ByteRTCSingScoringManager{@link #ByteRTCSingScoringManager}。
 */
/**
 * @locale en
 * @type api
 * @brief Create a karaoke scoring management interface.
 * @return Karaoke scoring management interface, see ByteRTCSingScoringManager{@link #ByteRTCSingScoringManager}.
 */
- (ByteRTCSingScoringManager *_Nullable)getSingScoringManager;

/**
 * @locale zh
 * @hidden(macOS)
 * @type api
 * @region 音视频传输
 * @brief 摄像头处于关闭状态时，使用静态图片填充本地推送的视频流。<br>
 *        调用 `stopVideoCapture` 接口时，会开始推静态图片。若要停止发送图片，可传入空字符串或启用内部摄像头采集。<br>
 *        可重复调用该接口来更新图片。
 * @param filePath 设置静态图片的路径。  <br>
 *        支持本地文件绝对路径，不支持网络链接，长度限制为 512 字节。   <br>
 *        静态图片支持类型为 JPEG/JPG、PNG、BMP。  <br>
 *        若图片宽高比与设置的编码宽高比不一致，图片会被等比缩放，黑边填充空白区域。推流帧率与码率与设置的编码参数一致。
 * @return  
 *        + 0: 成功。  <br>
 *        + -1: 失败。
 * @note  
 *        + 该接口只适用于 SDK 内部摄像头采集，不适用于自定义视频采集。  <br>
 *        + 本地预览无法看到静态图片。  <br>
 *        + 进入房间前后均可调用此方法。在多房间场景中，静态图片仅在发布的房间中生效。  <br>
 *        + 针对该静态图片，滤镜和镜像效果不生效，水印效果生效。  <br>
 *        + 只有主流能设置静态图片，屏幕流不支持设置。  <br>
 *        + 开启大小流后，静态图片对大小流均生效，且针对小流进行等比例缩小。
 */
/**
 * @locale en
 * @hidden(macOS)
 * @type api
 * @region Audio & Video Transport
 * @brief Set an alternative image when the local internal video capture is not enabled.<br>
 *        When you call `stopVideoCapture`, an alternative image will be pushed. You can set the path to null or open the camera to stop publishing the image.<br>
 *        You can repeatedly call this API to update the image.
 * @param filePath Set the path of the static image.  <br>
 *        You can use the absolute path (file://xxx). The maximum size for the path is 512 bytes.  <br>
 *        You can upload a .JPG, .JPEG, .PNG, or .BMP file.  <br>
 *        When the aspect ratio of the image is inconsistent with the video encoder configuration, the image will be proportionally resized, with the remaining pixels rendered black. The framerate and the bitrate are consistent with the video encoder configuration.
 * @return  
 *        + 0: Success.  <br>
 *        + -1: Failure.
 * @note  
 *        + The API is only effective when publishing an internally captured video.  <br>
 *        + You cannot locally preview the image.  <br>
 *        + You can call this API before and after joining an RTC room. In the multi-room mode, the image can be only displayed in the room you publish the stream.  <br>
 *        + You cannot apply effects like filters and mirroring to the image, while you can watermark the image.  <br>
 *        + The image is not effective for a screen-sharing stream.  <br>
 *        + When you enable the simulcast mode, the image will be added to all video streams, and it will be proportionally scaled down to smaller encoding configurations.
 */
- (int)setDummyCaptureImagePath:(NSString * _Nonnull)filePath;
/**
 * @locale zh
 * @type api
 * @brief 通过 NTP 协议，获取网络时间。
 * @return 网络时间。参看 ByteRTCNetworkTimeInfo{@link #ByteRTCNetworkTimeInfo}。
 * @note 
 *        + 第一次调用此接口会启动网络时间同步功能，并返回 `0`。同步完成后，会收到 rtcEngineOnNetworkTimeSynchronized:{@link #ByteRTCVideoDelegate#rtcEngineOnNetworkTimeSynchronized:}，此后，再次调用此 API，即可获取准确的网络时间。<br>
 *        + 在合唱场景下，合唱参与者应在相同的网络时间播放背景音乐。
 */
/**
 * @locale en
 * @type api
 * @brief Obtain the synchronization network time information.
 * @return See ByteRTCNetworkTimeInfo{@link #ByteRTCNetworkTimeInfo}.
 * @note 
 *        + When you call this API for the first time, you starts synchornizing the network time information and receive the return value `0`. After the synchonization finishes, you will receive rtcEngineOnNetworkTimeSynchronized:{@link #ByteRTCVideoDelegate#rtcEngineOnNetworkTimeSynchronized:}. After that, calling this API will get you the correct network time. <br>
 *        + Under chorus scenario, participants shall start audio mixing at the same network time.
 */
- (ByteRTCNetworkTimeInfo *_Nonnull)getNetworkTimeInfo;
/**
 * @locale zh
 * @type api
 * @brief 在听众端，设置订阅的所有远端音频流精准对齐后播放。
 * @param streamKey 作为对齐基准的远端音频流。参看 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}。<br>
 *                  一般选择主唱的音频流。<br>
 *                  你必须在收到 rtcRoom:onUserPublishStream:type:{@link #ByteRTCRoomDelegate#rtcRoom:onUserPublishStream:type:}，确认此音频流已发布后，调用此 API。
 * @param mode 是否对齐，默认不对齐。参看 ByteRTCAudioAlignmentMode{@link #ByteRTCAudioAlignmentMode}。
 * @return  
 *        + 0: 调用成功。<br>
 *        + < 0 : 调用失败。查看 ByteRTCReturnStatus{@link #ByteRTCReturnStatus} 获得更多错误说明
 * @note 
 *        + 你必须在实时合唱场景下使用此功能。在加入房间时，所有人应设置 ByteRTCRoomProfile{@link #ByteRTCRoomProfile} 为 `ByteRTCRoomProfileChorus`。<br>
 *        + 订阅的所有远端流必须通过 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} 开启了背景音乐混音，并将 ByteRTCAudioMixingConfig{@link #ByteRTCAudioMixingConfig} 中的 `syncProgressToRecordFrame` 设置为 `true`。<br>
 *        + 如果订阅的某个音频流延迟过大，可能无法实现精准对齐。<br>
 *        + 合唱的参与者不应调用此 API，因为调用此 API 会增加延迟。如果希望从听众变为合唱参与者，应关闭对齐功能。
 */
/**
 * @locale en
 * @type api
 * @brief On the listener side, set all subscribed audio streams precisely timely aligned.
 * @param streamKey The remote audio stream used as the benchmark during time alignment. See ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}. <br>
 *                  You are recommended to use the audio stream from the lead singer. <br>
 *                  You must call this API after receiving rtcRoom:onUserPublishStream:type:{@link #ByteRTCRoomDelegate#rtcRoom:onUserPublishStream:type:}.
 * @param mode Whether to enable the alignment. Disabled by default. See ByteRTCAudioAlignmentMode{@link #ByteRTCAudioAlignmentMode}.
 * @return  
 *        + 0: Success.<br>
 *        + < 0 : Fail. See ByteRTCReturnStatus{@link #ByteRTCReturnStatus} for more details
 * @note 
 *        + You must use the function when all participants set ByteRTCRoomProfile{@link #ByteRTCRoomProfile} to `ByteRTCRoomProfileChorus` when joining the room. <br>
 *        + All remote participants must call startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} to play background music and set `syncProgressToRecordFrame` of ByteRTCAudioMixingConfig{@link #ByteRTCAudioMixingConfig} to `true`. <br>
 *        + If the subscribed audio stream is delayed too much, it may not be precisely aligned. <br>
 *        + The chorus participants must not enable the alignment. If you wish to change the role from listener to participant, you should disable the alignment.
 */
- (int)setAudioAlignmentProperty:(ByteRTCRemoteStreamKey * _Nonnull)streamKey
           withMode:(ByteRTCAudioAlignmentMode)mode;

/**
 * @locale zh
 * @hidden internal use
 * @valid since 3.52
 * @type api
 * @brief 调用实验性 API。<br>
 *        调用后，可能会触发 rtcEngine:onInvokeExperimentalAPI:{@link #ByteRTCVideoDelegate#rtcEngine:onInvokeExperimentalAPI:}。
 * @param param JSON 字符串，形如：<br>
 * ```{<br>
 *   "api_name":"startPublish",<br>
 *   "params":{<br>
 *     "streamID":"",<br>
 *     "observer":"",<br>
 *     "uri":"",<br>
 *     "option":""<br>
 *   }<br>
 * }```
 * @return  
 *        + 0： 成功。  <br>
 *        + < 0： 失败。  
 */
/**
 * @locale en
 * @hidden internal use
 * @valid since 3.52
 * @type api
 * @brief invoke experimental API. <br>
 *        You may receive rtcEngine:onInvokeExperimentalAPI:{@link #ByteRTCVideoDelegate#rtcEngine:onInvokeExperimentalAPI:}.
 * @note param JSON string like:<br>
 * ```{<br>
 *   "api_name":"startPublish",<br>
 *   "params":{<br>
 *     "streamID":"",<br>
 *     "observer":"",<br>
 *     "uri":"",<br>
 *     "option":""<br>
 *   }<br>
 * }```
 * @return  
 *        + 0: Success.  <br>
 *        + < 0: Failure.
 */
- (int)invokeExperimentalAPI:(NSString * _Nonnull)param;


#pragma mark - KTV
/**
 * @locale zh
 * @hidden(macOS)
 * @type api
 * @brief 创建 KTV 管理接口。
 * @return KTV 管理接口，参看 ByteRTCKTVManager{@link #ByteRTCKTVManager}。
 */
/**
 * @locale en
 * @hidden currently not available
 * @type api
 * @brief Creates the KTV manager interfaces.
 * @return KTV manager interfaces. See ByteRTCKTVManager{@link #ByteRTCKTVManager}.
 */
- (ByteRTCKTVManager * _Nullable)getKTVManager;


/**
 * @locale zh
 * @type api
 * @region 音频设备
 * @brief 开启通话前回声检测
 * @param testAudioFilePath 用于回声检测的音频文件的绝对路径，路径字符串使用 UTF-8 编码格式，支持以下音频格式: mp3，aac，m4a，3gp，wav。<br>
 *         音频文件不为静音文件，推荐时长为 10 ～ 20 秒。
 * @return 方法调用结果：  <br>
 *        + 0: 成功。<br>
 *        + -1：失败。上一次检测未结束，请先调用 stopHardwareEchoDetection{@link #ByteRTCVideo#stopHardwareEchoDetection} 停止检测 后重新调用本接口。<br>
 *        + -2：失败。路径不合法或音频文件格式不支持。
 * @note 
 *        + 只有当 ByteRTCRoomProfile{@link #ByteRTCRoomProfile} 为 `ByteRTCRoomProfileMeeting` 和 `ByteRTCRoomProfileMeetingRoom` 时支持开启本功能。<br>
 *        + 开启检测前，你需要向用户获取音频设备的使用权限。<br>
 *        + 开启检测前，请确保音频设备没有被静音，采集和播放音量正常。<br>
 *        + 调用本接口后监听 rtcEngine:onHardwareEchoDetectionResult:{@link #ByteRTCVideoDelegate#rtcEngine:onHardwareEchoDetectionResult:} 获取检测结果。<br>
 *        + 检测期间，进程将独占音频设备，无法使用其他音频设备测试接口： startEchoTest:playDelay:{@link #ByteRTCVideo#startEchoTest:playDelay:}、startAudioDeviceRecordTest:{@link #ByteRTCAudioDeviceManager#startAudioDeviceRecordTest:} 或 startAudioPlaybackDeviceTest:interval:{@link #ByteRTCAudioDeviceManager#startAudioPlaybackDeviceTest:interval:}。 <br>
 *        + 调用  stopHardwareEchoDetection{@link #ByteRTCVideo#stopHardwareEchoDetection} 停止检测，释放对音频设备的占用。
 */
/**
 * @locale en
 * @type api
 * @region Audio Management
 * @brief Start echo detection before joining a room.
 * @param testAudioFilePath Absolute path of the music file for the detection. It is expected to encode with UTF-8. The following files are supported: mp3, aac, m4a, 3gp, wav. <br>
 *        We recommend to assign a music file whose duration is between 10 to 20 seconds.<br>
 *        Do not pass a Silent file.
 * @return Method call result:   <br>
 *         + 0: Success. <br>
 *        + -1: Failure due to the onging process of the previous detection. Call stopHardwareEchoDetection{@link #ByteRTCVideo#stopHardwareEchoDetection} to stop it before calling this API again.<br>
 *        + -2: Failure due to an invalid file path or file format.
 * @note  
 *        + You can use this feature only when ByteRTCRoomProfile{@link #ByteRTCRoomProfile} is set to `ByteRTCRoomProfileMeeting` or `ByteRTCRoomProfileMeetingRoom`.<br>
 *        + Before calling this API, ask the user for the permissions to access the local audio devices. <br>
 *        + Before calling this api, make sure the audio devices are activate and keep the capture volume and the playback volume within a reasonable range.<br>
 *        + The detection result is passed as the argument of rtcEngine:onHardwareEchoDetectionResult:{@link #ByteRTCVideoDelegate#rtcEngine:onHardwareEchoDetectionResult:}. <br>
 *        + During the detection, the SDK is not able to response to the other testing APIs, such as startEchoTest:playDelay:{@link #ByteRTCVideo#startEchoTest:playDelay:}, startAudioDeviceRecordTest:{@link #ByteRTCAudioDeviceManager#startAudioDeviceRecordTest:} or startAudioPlaybackDeviceTest:interval:{@link #ByteRTCAudioDeviceManager#startAudioPlaybackDeviceTest:interval:}. <br>
 *        + Call  stopHardwareEchoDetection{@link #ByteRTCVideo#stopHardwareEchoDetection} to stop the detection and release the audio devices.
 */
- (int)startHardwareEchoDetection:(NSString * _Nonnull)testAudioFilePath;
/**
 * @locale zh
 * @type api
 * @region 音频设备
 * @brief 停止通话前回声检测
 * @return 方法调用结果：  <br>
 *        + 0: 成功。<br>
 *        + -1：失败。
 * @note 
 *       + 关于开启通话前回声检测，参看 startHardwareEchoDetection:{@link #ByteRTCVideo#startHardwareEchoDetection:} 。<br>
 *       + 建议在收到 rtcEngine:onHardwareEchoDetectionResult:{@link #ByteRTCVideoDelegate#rtcEngine:onHardwareEchoDetectionResult:} 通知的检测结果后，调用本接口停止检测。<br>
 *       + 在用户进入房间前结束回声检测，释放对音频设备的占用，以免影响正常通话。
 */
/**
 * @locale en
 * @type api
 * @region Audio Management
 * @brief Stop the echo detection before joining a room.
 * @return Method call result:  <br>
 *        + 0: Success. <br>
 *        + -1: Failure.
 * @note 
 *        + Refer to startHardwareEchoDetection:{@link #ByteRTCVideo#startHardwareEchoDetection:} for information on how to start a echo detection. <br>
 *        + We recommend calling this API to stop the detection once getting the detection result from rtcEngine:onHardwareEchoDetectionResult:{@link #ByteRTCVideoDelegate#rtcEngine:onHardwareEchoDetectionResult:}. <br>
 *        + You must stop the echo detection to release the audio devices before the user joins a room. Otherwise, the detection may interfere with the call.
 */
- (int)stopHardwareEchoDetection;

/**
 * @locale zh
 * @hidden(macOS)
 * @type api
 * @brief 启用蜂窝网络辅助增强，改善通话质量。
 * @param config 参看 ByteRTCMediaTypeEnhancementConfig{@link #ByteRTCMediaTypeEnhancementConfig}。
 * @return 方法调用结果：  <br>
 *        + 0: 成功。<br>
 *        + -1：失败，内部错误。 <br>
 *        + -2: 失败，输入参数错误。 
 * @note 此功能默认不开启。
 */
/**
 * @locale en
 * @hidden(macOS)
 * @type api
 * @brief Enable cellular network assisted communication to improve call quality.
 * @param config See ByteRTCMediaTypeEnhancementConfig{@link #ByteRTCMediaTypeEnhancementConfig}.
 * @return Method call result:   <br>
 *        + 0: Success. <br>
 *        + -1: Failure, internal error. <br>
 *        + -2: Failure, invalid parameters. 
 * @note The function is off by default.
 */
- (int)setCellularEnhancement:(ByteRTCMediaTypeEnhancementConfig * _Nonnull)config;

 /**
  * @locale zh
  * @type api
  * @region 代理
  * @brief 设置本地代理。
  * @param configurations 本地代理配置参数。参看 ByteRTCLocalProxyInfo{@link #ByteRTCLocalProxyInfo}。  <br>
  *        你可以根据自己的需要选择同时设置 Http 隧道 和 Socks5 两类代理，或者单独设置其中一类代理。如果你同时设置了 Http 隧道 和 Socks5 两类代理，此时，媒体和信令采用 Socks5 代理， Http 请求采用 Http 隧道代理；如果只设置 Http 隧道 或 Socks5 一类代理，媒体、信令和 Http 请求均采用已设置的代理。 <br>
  *        调用此接口设置本地代理后，若想清空当前已有的代理设置，可再次调用此接口，选择不设置任何代理即可清空。
  * @note 
  *       + 该方法需要在进房前调用。<br>
  *       + 调用该方法设置本地代理后，SDK 会触发 rtcEngine:onLocalProxyStateChanged:withProxyState:withProxyError:{@link #ByteRTCVideoDelegate#rtcEngine:onLocalProxyStateChanged:withProxyState:withProxyError:} ，返回代理连接的状态。
  */
 /**
  * @locale en
  * @type api
  * @region proxy
  * @brief Sets local proxy.
  * @param configurations Local proxy configurations. Refer to ByteRTCLocalProxyInfo{@link #ByteRTCLocalProxyInfo} for details. <br>
  *         You can set both Http tunnel and Socks5 as your local proxies, or only set one of them based on your needs. If you set both Http tunnel and Socks5 as your local proxies, then media traffic and signaling are routed through Socks5 proxy and Http requests through Http tunnel proxy. If you set either Http tunnel or Socks5 as your local proxy, then media traffic, signaling and Http requests are all routed through the proxy you chose. <br>
  *         If you want to remove the existing local proxy configurations, you can call this API with the parameter set to null. 
  * @note 
  *       + You must call this API before joining the room.  <br>
  *       + After calling this API, you will receive rtcEngine:onLocalProxyStateChanged:withProxyState:withProxyError:{@link #ByteRTCVideoDelegate#rtcEngine:onLocalProxyStateChanged:withProxyState:withProxyError:} callback that informs you of the states of local proxy connection. 
  */
- (int)setLocalProxy:(NSArray <ByteRTCLocalProxyInfo *> * _Nonnull)configurations;
@end
