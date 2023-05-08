/*
 * Copyright (c) 2022 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief ByteRTCAudio
*/

#import <UIKit/UIKit.h>
#import "rtc/ByteRTCRtsDefines.h"
#import "rtc/ByteRTCAudioDefines.h"
#import "rtc/ByteRTCAudioMixingManager.h"

@class ByteRTCAudio;
@class ByteRTCAudioRoom;

#pragma mark - ByteRTCAudioDelegate
/** 
 * @type callback
 * @brief ByteRTCAudioDelegate 协议包含了SDK提供的回调方法，SDK通过代理向应用程序上报一些运行时事件
 */
@protocol ByteRTCAudioDelegate <NSObject>
@optional

#pragma mark - Engine Management Delegate Methods
/** 
 * @type callback
 * @region 警告码
 * @brief 发生警告回调。  <br>
 *        SDK 运行时出现了警告。SDK 通常会自动恢复，警告信息可以忽略。
 * @param engine ByteRTCAudio 对象。
 * @param Code 警告代码，参看 ByteRTCWarningCode{@link #ByteRTCWarningCode}。
 */
- (void)rtcEngine:(ByteRTCAudio * _Nonnull)engine onWarning:(ByteRTCWarningCode)Code;
/** 
 * @type callback
 * @region 错误码
 * @brief 发生错误回调。<br>
 *        SDK 运行时出现了网络或媒体相关的错误，且无法自动恢复时触发此回调。
 * @param engine ByteRTCAudio 对象。  <br>
 * @param errorCode 错误代码，参看 ByteRTCErrorCode{@link #ByteRTCErrorCode}。  <br>
 */
- (void)rtcEngine:(ByteRTCAudio * _Nonnull)engine onError:(ByteRTCErrorCode)errorCode;
/** 
 * @type callback
 * @region 引擎管理
 * @brief SDK 与信令服务器连接状态改变回调。连接状态改变时触发。
 * @param engine ByteRTCAudio 对象。
 * @param state 当前 SDK 与信令服务器的连接状态，详见 ByteRTCConnectionState{@link #ByteRTCConnectionState}。
 * @notes 更多信息参见 [连接状态提示](https://www.volcengine.com/docs/6348/95376)。
 */
- (void)rtcEngine:(ByteRTCAudio * _Nonnull)engine onConnectionStateChanged:(ByteRTCConnectionState)state;
/** 
 * @type callback
 * @region 引擎管理
 * @brief SDK 当前网络连接类型改变回调。当 SDK 的当前网络连接类型发生改变时回调该事件。
 * @param engine ByteRTCAudio 对象。
 * @param type SDK 当前的网络连接类型，详见 ByteRTCNetworkType{@link #ByteRTCNetworkType} 。
 */
- (void)rtcEngine:(ByteRTCAudio * _Nonnull)engine onNetworkTypeChanged:(ByteRTCNetworkType)type;

/** 
 * @type callback
 * @region 引擎管理
 * @brief 创建房间失败回调。
 * @param roomId 房间 ID。
 * @param errorCode 创建房间错误码，具体原因参看 ByteRTCErrorCode{@link #ByteRTCErrorCode}。
 */
- (void)rtcEngine:(ByteRTCAudio *_Nonnull)engine onCreateRoomStateChanged:(NSString * _Nonnull)roomId errorCode:(NSInteger)errorCode;

/** 
 * @type callback
 * @region 多房间
 * @brief 房间内的用户调用 startAudioCapture{@link #ByteRTCAudio#startAudioCapture} 开启音频采集时，房间内其他用户会收到此回调。
 * @param engine ByteRTCAudio 实例
 * @param roomId 开启音频采集的用户所在的房间 ID
 * @param userId 开启音频采集的远端用户 ID
 */
- (void)rtcEngine:(ByteRTCAudio * _Nonnull)engine onUserStartAudioCapture:(NSString* _Nonnull)roomId
              uid:(NSString *_Nonnull)userId;
/** 
 * @type callback
 * @region 多房间
 * @brief 房间内的用户调用 stopAudioCapture{@link #ByteRTCAudio#stopAudioCapture} 关闭音频采集时，房间内其他用户会收到此回调。
 * @param engine ByteRTCAudio 实例
 * @param roomId 关闭音频采集的用户所在的房间 ID
 * @param userId 关闭音频采集的远端用户 ID
 */
- (void)rtcEngine:(ByteRTCAudio * _Nonnull)engine onUserStopAudioCapture:(NSString* _Nonnull)roomId
              uid:(NSString *_Nonnull)userId;
/** 
 * @type callback
 * @region 多房间
 * @brief 发布音频流时，采集到第一帧音频帧，收到该回调。
 * @param engine ByteRTCAudio 对象
 * @notes 如果发布音频流时，未开启本地音频采集，SDK 会推送静音帧，也会收到此回调。
 */
- (void)rtcEngineOnFirstLocalAudioFrame:(ByteRTCAudio * _Nonnull)engine;

/** 
 * @type callback
 * @region 多房间
 * @brief 当收到远端流的第一帧音频的时候上报该事件
 * @param engine ByteRTCAudio 对象
 * @param key 远端流信息, 详见 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
 * @notes 用户刚收到房间内每一路音频流时，都会收到该回调。
 */
- (void)rtcEngine:(ByteRTCAudio * _Nonnull)engine onFirstRemoteAudioFrame:(ByteRTCRemoteStreamKey * _Nonnull)key;
/** 
* @deprecated since 3.50. Use rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCAudioDelegate#rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:} instead.
* @type callback
* @region 多房间
* @brief 本地音频流的状态发生改变时，收到此回调。
* @param engine ByteRTCAudio 对象
* @param state 本地音频设备的当前状态，详见 ByteRTCLocalAudioStreamState{@link #ByteRTCLocalAudioStreamState}
* @param error 本地音频流状态改变时的错误码，详见 ByteRTCLocalAudioStreamError{@link #ByteRTCLocalAudioStreamError}
*/
- (void)rtcEngine:(ByteRTCAudio * _Nonnull)engine onLocalAudioStateChanged:(ByteRTCLocalAudioStreamState)state
         error:(ByteRTCLocalAudioStreamError)error;
/** 
* @hidden not available
* @type callback
* @region 多房间
* @brief 订阅的远端音频流状态发生改变时，收到此回调。
* @param engine ByteRTCAudio 对象
* @param key 远端流信息, 详见 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
* @param state 远端音频流的当前状态，详见 ByteRTCRemoteAudioState{@link #ByteRTCRemoteAudioState}
* @param reason 远端音频流状态改变的原因，详见 ByteRTCRemoteAudioStateChangeReason{@link #ByteRTCRemoteAudioStateChangeReason}
*/
- (void)rtcEngine:(ByteRTCAudio * _Nonnull)engine onRemoteAudioStateChanged:(ByteRTCRemoteStreamKey * _Nonnull)key
         state:(ByteRTCRemoteAudioState)state reason:(ByteRTCRemoteAudioStateChangeReason)reason;
/** 
* @type callback
* @region 多房间
* @brief 音频首帧发送状态改变时，收到此回调。
* @param engine ByteRTCAudio 对象  <br>
* @param roomId 音频发布用户所在的房间 ID
* @param user 本地用户信息，详见 ByteRTCUser{@link #ByteRTCUser}
* @param state 首帧发送状态，详见 ByteRTCFirstFrameSendState{@link #ByteRTCFirstFrameSendState}
*/
- (void)rtcEngine:(ByteRTCAudio * _Nonnull)engine onAudioFrameSendStateChanged:(NSString * _Nonnull)roomId
          rtcUser:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFrameSendState)state;
/** 
* @type callback
* @region 多房间
* @brief 音频首帧播放状态改变时，收到此回调
* @param engine ByteRTCAudio 对象
* @param roomId 音频发布用户所在的房间 ID
* @param user 音频流来源的用户信息，参看 ByteRTCUser{@link #ByteRTCUser}
* @param state 首帧播放状态，详见 ByteRTCFirstFramePlayState{@link #ByteRTCFirstFramePlayState}
*/
- (void)rtcEngine:(ByteRTCAudio * _Nonnull)engine onAudioFramePlayStateChanged:(NSString * _Nonnull)roomId
          rtcUser:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFramePlayState)state;


#pragma mark - Audio Management Delegate Methods
 /** 
  * @type callback
  * @region 音频管理
  * @brief 调用 enableAudioPropertiesReport:{@link #ByteRTCAudio#enableAudioPropertiesReport:} 后，根据设置的 interval 值，你会周期性地收到此回调，了解本地音频的相关信息。  <br>
  *        本地音频包括使用 RTC SDK 内部机制采集的麦克风音频和屏幕音频。
  * @param engine ByteRTCAudio 对象
  * @param audioPropertiesInfos 本地音频信息，详见 ByteRTCLocalAudioPropertiesInfo{@link #ByteRTCLocalAudioPropertiesInfo} 。
  */
 - (void)rtcEngine:(ByteRTCAudio * _Nonnull)engine
    onLocalAudioPropertiesReport:(NSArray<ByteRTCLocalAudioPropertiesInfo *> * _Nonnull)audioPropertiesInfos;
 /** 
  * @type callback
  * @region 音频管理
  * @brief 远端用户进房后，本地调用 enableAudioPropertiesReport:{@link #ByteRTCAudio#enableAudioPropertiesReport:} ，根据设置的 interval 值，本地会周期性地收到此回调，了解订阅的远端用户的音频信息。<br>
  *        远端用户的音频包括使用 RTC SDK 内部机制/自定义机制采集的麦克风音频和屏幕音频。
  * @param engine ByteRTCAudio 对象
  * @param audioPropertiesInfos 远端音频信息，其中包含音频流属性、房间 ID、用户 ID ，详见 ByteRTCRemoteAudioPropertiesInfo{@link #ByteRTCRemoteAudioPropertiesInfo}。
  * @param totalRemoteVolume 订阅的所有远端流的总音量，范围是 [0,255]。  <br>
  *       + [0,25] 接近无声；  <br>
  *       + [25,75] 为低音量；  <br>
  *       + [76,204] 为中音量；  <br>
  *       + [205,255] 为高音量。  <br>
  */
 - (void)rtcEngine:(ByteRTCAudio * _Nonnull)engine
    onRemoteAudioPropertiesReport:(NSArray<ByteRTCRemoteAudioPropertiesInfo *> * _Nonnull)audioPropertiesInfos
    totalRemoteVolume:(NSInteger)totalRemoteVolume;
/** 
 * @type callback
 * @region 音频管理
 * @brief 音频流同步信息回调。可以通过此回调，在远端用户调用 sendStreamSyncInfo:repeatCount:{@link #ByteRTCAudio#sendStreamSyncInfo:repeatCount:} 发送音频流同步消息后，收到远端发送的音频流同步信息。  <br>
 * @param engine 当前 ByteRTCAudio 实例。
 * @param remoteStreamKey 远端流信息，详见 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey} 。
 * @param data 消息内容。
 */
- (void)rtcEngine:(ByteRTCAudio * _Nonnull)engine
        onStreamSyncInfoReceived:(ByteRTCRemoteStreamKey* _Nonnull)remoteStreamKey
        streamType:(ByteRTCSyncInfoStreamType)streamType data:(NSData* _Nonnull)data;

/** 
 * @type callback
 * @region 音频事件回调
 * @brief 音频播放路由变化时，收到该回调。
 * @param device 新的音频播放路由，详见 ByteRTCAudioRoute{@link #ByteRTCAudioRoute}
 * @notes 插拔音频外设，或调用 setAudioRoute:{@link #ByteRTCAudio#setAudioRoute:} 都可能触发音频路由切换，详见[移动端设置音频路由](https://www.volcengine.com/docs/6348/117836) 。
 */
- (void)rtcEngine:(ByteRTCAudio *_Nonnull)engine onAudioRouteChanged:(ByteRTCAudioRoute)device;

/** 
 * @type callback
 * @region 引擎管理
 * @brief 音频设备状态回调。提示音频采集、音频播放等设备的状态。
 * @param engine ByteRTCAudio 实例
 * @param deviceId 设备 ID
 * @param deviceType 设备类型，参看 ByteRTCAudioDeviceType{@link #ByteRTCAudioDeviceType}。
 * @param deviceState 设备状态，参看 ByteRTCMediaDeviceState{@link #ByteRTCMediaDeviceState}。
 * @param deviceError 设备错误类型，参看 ByteRTCMediaDeviceError{@link #ByteRTCMediaDeviceError}。
 */
- (void)rtcEngine:(ByteRTCAudio * _Nonnull)engine onAudioDeviceStateChanged:(NSString* _Nonnull)deviceId
      device_type:(ByteRTCAudioDeviceType)deviceType
     device_state:(ByteRTCMediaDeviceState)deviceState
     device_error:(ByteRTCMediaDeviceError)deviceError;
/** 
 * @type callback
 * @region 引擎管理
 * @brief 音频设备警告回调。音频设备包括音频采集设备和音频渲染设备。
 * @param engine ByteRTCAudio 对象
 * @param deviceId 设备 ID
 * @param deviceType 参看 ByteRTCAudioDeviceType{@link #ByteRTCAudioDeviceType}
 * @param deviceWarning 参看 ByteRTCMediaDeviceWarning{@link #ByteRTCMediaDeviceWarning}
 */
- (void)rtcEngine:(ByteRTCAudio * _Nonnull)engine onAudioDeviceWarning:(NSString* _Nonnull)deviceId
    deviceType:(ByteRTCAudioDeviceType)deviceType
    deviceWarning:(ByteRTCMediaDeviceWarning)deviceWarning;

#pragma mark - Data Statistics Delegate Methods
/** 
 * @type callback
 * @region 引擎管理
 * @brief 周期性（2s）地发出回调，报告当前cpu与memory使用率
 * @param engine ByteRTCAudio 对象
 * @param stats 返回包含当前系统状态信息的结构体，详见 ByteRTCSysStats{@link #ByteRTCSysStats}
 */
- (void)rtcEngine:(ByteRTCAudio * _Nonnull)engine onSysStats:(const ByteRTCSysStats * _Nonnull)stats;

#pragma mark - Real-time Messaging Delegate Methods
/** 
 * @type callback
 * @region 实时消息通信
 * @brief 登录结果回调
 * @param engine ByteRTCAudio 对象
 * @param uid  <br>
 *        登录用户 ID
 * @param errorCode  <br>
 *        登录结果  <br>
 *        详见 ByteRTCLoginErrorCode{@link #ByteRTCLoginErrorCode}。
 * @param elapsed  <br>
 *        从调用 login:uid:{@link #ByteRTCAudio#login:uid:} 接口开始到返回结果所用时长。  <br>
 *        单位为 ms。
 * @notes 调用 login:uid:{@link #ByteRTCAudio#login:uid:} 后，会收到此回调。
 */
- (void)rtcEngine:(ByteRTCAudio * _Nonnull)engine onLoginResult:(NSString * _Nonnull)uid
        errorCode:(ByteRTCLoginErrorCode)errorCode elapsed:(NSInteger)elapsed;
/** 
 * @type callback
 * @region 实时消息通信
 * @brief 登出结果回调
 * @param engine ByteRTCAudio 对象
 * @notes 调用 logout{@link #ByteRTCAudio#logout} 后，会收到此回调。
 */
- (void)rtcEngineOnLogout:(ByteRTCAudio * _Nonnull)engine;
/** 
 * @type callback
 * @region 实时消息通信
 * @brief 设置应用服务器参数的返回结果
 * @param engine ByteRTCAudio 对象
 * @param errorCode <br>
 *        设置结果  <br>
 *        + 返回 200，设置成功  <br>
 *        + 返回其他，设置失败，详见 ByteRTCUserMessageSendResult{@link #ByteRTCUserMessageSendResult}
 * @notes 调用 setServerParams:url:{@link #ByteRTCAudio#setServerParams:url:} 后，会收到此回调。
 */
- (void)rtcEngine:(ByteRTCAudio * _Nonnull)engine onServerParamsSetResult:(NSInteger)errorCode;
/** 
 * @type callback
 * @region 实时消息通信
 * @brief 查询对端或本端用户登录状态的返回结果
 * @param engine ByteRTCAudio 对象
 * @param peerUserId 需要查询的用户 ID
 * @param status 查询的用户登录状态，详见 ByteRTCUserOnlineStatus{@link #ByteRTCUserOnlineStatus}.
 * @notes 必须先调用 getPeerOnlineStatus:{@link #ByteRTCAudio#getPeerOnlineStatus:}，才能收到此回调。
 */
- (void)rtcEngine:(ByteRTCAudio * _Nonnull)engine onGetPeerOnlineStatus:(NSString * _Nonnull)peerUserId
           status:(ByteRTCUserOnlineStatus)status;
/** 
 * @type callback
 * @region 实时消息通信
 * @brief 收到房间外用户调用 sendUserMessageOutsideRoom:message:config:{@link #ByteRTCAudio#sendUserMessageOutsideRoom:message:config:} 发来的文本消息时，会收到此回调
 * @param engine ByteRTCAudio 对象
 * @param uid 消息发送者 ID
 * @param message 收到的文本消息内容
 */
- (void)rtcEngine:(ByteRTCAudio * _Nonnull)engine onUserMessageReceivedOutsideRoom:(NSString * _Nonnull)uid
          message:(NSString * _Nonnull)message;
/** 
 * @type callback
 * @region 实时消息通信
 * @brief 收到房间外用户调用 sendUserBinaryMessageOutsideRoom:message:config:{@link #ByteRTCAudio#sendUserBinaryMessageOutsideRoom:message:config:} 发来的二进制消息时，会收到此回调。
 * @param engine ByteRTCAudio 对象
 * @param uid 消息发送者 ID
 * @param message 收到的二进制消息内容
 */
- (void)rtcEngine:(ByteRTCAudio * _Nonnull)engine onUserBinaryMessageReceivedOutsideRoom:(NSString * _Nonnull)uid
          message:(NSData * _Nonnull)message;
/** 
 * @type callback
 * @region 实时消息通信
 * @brief 给房间外指定的用户发送消息的回调
 * @param engine ByteRTCAudio 对象
 * @param msgid 本条消息的 ID。所有的 P2P 和 P2Server 消息共用一个 ID 序列。
 * @param error 消息发送结果，详见 ByteRTCUserMessageSendResult{@link #ByteRTCUserMessageSendResult}。
 * @notes 当调用 sendUserMessageOutsideRoom:message:config:{@link #ByteRTCAudio#sendUserMessageOutsideRoom:message:config:} 或 sendUserBinaryMessageOutsideRoom:message:config:{@link #ByteRTCAudio#sendUserBinaryMessageOutsideRoom:message:config:} 发送消息后，会收到此回调。
 */
- (void)rtcEngine:(ByteRTCAudio * _Nonnull)engine onUserMessageSendResultOutsideRoom:(int64_t)msgid
            error:(ByteRTCUserMessageSendResult)error;
/** 
 * @type callback
 * @region 实时消息通信
 * @brief 给应用服务器发送消息的回调。
 * @param engine ByteRTCAudio 对象。
 * @param msgid 本条消息的 ID。
 *              所有的 P2P 和 P2Server 消息共用一个 ID 序列。
 * @param error 消息发送结果。详见 ByteRTCUserMessageSendResult{@link #ByteRTCUserMessageSendResult}。
 * @param message 应用服务器收到 HTTP 请求后，在 ACK 中返回的信息。消息不超过 64 KB。
 * @notes 本回调为异步回调。当调用 sendServerMessage:{@link #ByteRTCAudio#sendServerMessage:} 或 sendServerBinaryMessage:{@link #ByteRTCAudio#sendServerBinaryMessage:} 接口发送消息后，会收到此回调。
 */
- (void)rtcEngine:(ByteRTCAudio * _Nonnull)engine onServerMessageSendResult:(int64_t)msgid
            error:(ByteRTCUserMessageSendResult)error message:(NSData * _Nonnull)message;

#pragma mark - Network Probe Delegate Methods
/** 
 * @type callback
 * @region 通话前网络探测
 * @brief 通话前网络探测结果。  <br>
 *        成功调用 startNetworkDetection:uplinkBandwidth:downlink:downlinkBandwidth:{@link #ByteRTCAudio#startNetworkDetection:uplinkBandwidth:downlink:downlinkBandwidth:} 接口开始探测后，会在 3s 内首次收到该回调，之后每 2s 收到一次该回调。
 * @param engine ByteRTCAudio 对象
 * @param type 探测网络类型为上行/下行  <br>
 * @param quality 探测网络的质量，参看 ByteRTCNetworkQuality{@link #ByteRTCNetworkQuality}。 <br>
 * @param rtt 探测网络的 RTT，单位：ms  <br>
 * @param lost_rate 探测网络的丢包率  <br>
 * @param bitrate 探测网络的带宽，单位：kbps  <br>
 * @param jitter 探测网络的抖动,单位：ms  <br>
 */
- (void)rtcEngine:(ByteRTCAudio * _Nonnull)engine onNetworkDetectionResult:(ByteRTCNetworkDetectionLinkType)type
          quality:(ByteRTCNetworkQuality)quality rtt:(int)rtt lostRate:(double)lost_rate
          bitrate:(int)bitrate jitter:(int)jitter;
/** 
 * @type callback
 * @region 通话前网络探测
 * @brief 通话前网络探测结束  <br>
 *        以下情况将停止探测并收到本一次本回调：<br>
 *        1. 当调用 stopNetworkDetection{@link #ByteRTCAudio#stopNetworkDetection} 接口停止探测后，会收到一次该回调；
 *        2. 当收到远端/本端音频首帧后，停止探测；
 *        3. 当探测超过3分钟后，停止探测；
 *        4. 当探测链路断开一定时间之后，停止探测。
 * @param engine ByteRTCAudio 对象
 * @param err_code 停止探测的原因类型,参考 ByteRTCNetworkDetectionStopReason{@link #ByteRTCNetworkDetectionStopReason}  <br>
 */
- (void)rtcEngine:(ByteRTCAudio * _Nonnull)engine
    onNetworkDetectionStopped:(ByteRTCNetworkDetectionStopReason)err_code;
/** 
 * @type callback
 * @brief 首次调用 getNetworkTimeInfo{@link #ByteRTCAudio#getNetworkTimeInfo} 后，SDK 内部启动网络时间同步，同步完成时会触发此回调。
 * @param engine ByteRTCAudio{@link #ByteRTCAudio} 对象
 */
- (void)rtcEngineOnNetworkTimeSynchronized:(ByteRTCAudio *_Nonnull)engine;
/** 
 * @type callback
 * @brief license过期时间提醒
 * @param engine ByteRTCAudio 对象
 * @param days 过期时间天数
 */
- (void)rtcEngine:(ByteRTCAudio *  _Nonnull)engine onLicenseWillExpire:(NSInteger)days;

#pragma mark - Audio Mixing Delegate Methods
/** 
 * @type callback
 * @region 混音
 * @brief 音频混音文件播放状态改变时回调
 * @param engine 当前 ByteRTCAudio 对象
 * @param mixId 混音 ID，使用 ByteRTCAudioMixingManager{@link #ByteRTCAudioMixingManager} 相关接口时传入的唯一 ID。
 * @param state 混音状态，参看 ByteRTCAudioMixingState{@link #ByteRTCAudioMixingState}。
 * @param error 错误码，参看 ByteRTCAudioMixingError{@link #ByteRTCAudioMixingError}。
 * @notes  <br>
 *       此回调会被触发的时机汇总如下：  <br>
 *       + 当调用 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} 方法成功后，会触发 state 值为 ByteRTCAudioMixingStatePlaying 回调；否则触发 state 值为 ByteRTCAudioMixingStateFailed 的回调。  <br>
 *       + 当使用相同的 ID 重复调用 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} 后，后一次会覆盖前一次，且本回调会以 ByteRTCAudioMixingStateStopped 通知前一次混音已停止。  <br>
 *       + 当调用 pauseAudioMixing:{@link #ByteRTCAudioMixingManager#pauseAudioMixing:} 方法暂停播放成功后，会触发 state 值为 ByteRTCAudioMixingStatePaused 回调；否则触发 state 值为 ByteRTCAudioMixingStateFailed 的回调。  <br>
 *       + 当调用 resumeAudioMixing:{@link #ByteRTCAudioMixingManager#resumeAudioMixing:} 方法恢复播放成功后，会触发 state 值为 ByteRTCAudioMixingStatePlaying 回调；否则触发 state 值为 ByteRTCAudioMixingStateFailed 的回调。  <br>
 *       + 当调用 stopAudioMixing:{@link #ByteRTCAudioMixingManager#stopAudioMixing:} 方法停止播放成功后，会触发 state 值为 ByteRTCAudioMixingStateStopped 回调；否则触发 state 值为 ByteRTCAudioMixingStateFailed 的回调。  <br>
 *       + 播放结束会触发 state 值为 ByteRTCAudioMixingStateFinished 回调。
 */
- (void)rtcEngine:(ByteRTCAudio * _Nonnull)engine onAudioMixingStateChanged:(NSInteger)mixId
            state:(ByteRTCAudioMixingState)state error:(ByteRTCAudioMixingError)error;
/** 
 * @type callback
 * @region 混音
 * @brief 混音音频文件播放进度回调
 * @param engine 当前 ByteRTCAudio 对象
 * @param mixId 混音 ID  <br>
 * @param progress 当前混音音频文件播放进度，单位毫秒
 * @notes 调用 setAudioMixingProgressInterval:interval:{@link #ByteRTCAudioMixingManager#setAudioMixingProgressInterval:interval:} 将时间间隔设为大于 0 的值后，或调用 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} 将 ByteRTCAudioMixingConfig{@link #ByteRTCAudioMixingConfig} 中的时间间隔设为大于 0 的值后，SDK 会按照设置的时间间隔回调该事件。 <br>
 */
- (void)rtcEngine:(ByteRTCAudio * _Nonnull)engine onAudioMixingPlayingProgress:(NSInteger)mixId
         progress:(int64_t)progress;

#pragma mark -  Network Proxy Delegate Methods
/** 
 * @type callback
 * @region 网络代理
 * @brief HTTP 代理连接状态改变时，收到该回调。
 * @param engine ByteRTCAudio 对象
 * @param state 当前 HTTP 代理连接状态
 */
- (void)rtcEngine:(ByteRTCAudio * _Nonnull)engine onHttpProxyState:(NSInteger)state;
/** 
 * @type callback
 * @region 网络代理
 * @brief HTTPS 代理连接状态改变时，收到该回调。
 * @param engine ByteRTCAudio 对象
 * @param state 当前 HTTPS 代理连接状态
 */
- (void)rtcEngine:(ByteRTCAudio * _Nonnull)engine onHttpsProxyState:(NSInteger)state;
/** 
 * @type callback
 * @region 网络代理
 * @brief SOCKS5 代理状态改变时，收到该回调。
 * @param engine ByteRTCAudio 对象
 * @param state SOCKS5 代理连接状态
 * @param cmd 代理连接的每一步操作命令
 * @param proxy_address 代理地址信息
 * @param local_address 当前连接使用的本地地址
 * @param remote_address 远端的连接地址
 */
- (void)rtcEngine:(ByteRTCAudio * _Nonnull)engine onSocks5ProxyState:(NSInteger)state
              cmd:(NSString * _Nonnull)cmd
    proxy_address:(NSString * _Nonnull)proxy_address
    local_address:(NSString * _Nonnull)local_address
   remote_address:(NSString * _Nonnull)remote_address;





#pragma mark - Local Recording Delegate Methods
/** 
 * @type callback
 * @region 本地录制
 * @brief 获取本地录制状态回调。  <br>
 *        该回调由 startFileRecording:{@link #ByteRTCAudio#startFileRecording:} 或 stopFileRecording{@link #ByteRTCAudio#stopFileRecording} 触发。
 * @param engine ByteRTCAudio 对象
 * @param state 录制状态，参看 ByteRTCRecordingState{@link #ByteRTCRecordingState}
 * @param error_code 录制错误码，参看 ByteRTCRecordingErrorCode{@link #ByteRTCRecordingErrorCode}
 * @param recording_info 录制文件的详细信息，参看 ByteRTCRecordingInfo{@link #ByteRTCRecordingInfo}
 */
- (void)rtcEngine:(ByteRTCAudio* _Nonnull)engine onRecordingStateUpdate:(ByteRTCRecordingState)state
       error_code:(ByteRTCRecordingErrorCode)error_code
   recording_info:(ByteRTCRecordingInfo* _Nonnull)recording_info;
/** 
 * @type callback
 * @region 本地录制
 * @brief 本地录制进度回调。  <br>
 *        该回调由 startFileRecording:{@link #ByteRTCAudio#startFileRecording:} 触发，录制状态正常时，系统每秒钟都会通过该回调提示录制进度。
 * @param engine ByteRTCAudio 对象
 * @param process 录制进度，参看 ByteRTCRecordingProgress{@link #ByteRTCRecordingProgress}
 * @param recording_info 录制文件的详细信息，参看 ByteRTCRecordingInfo{@link #ByteRTCRecordingInfo}
 */
- (void)rtcEngine:(ByteRTCAudio* _Nonnull)engine
    onRecordingProgressUpdate:(ByteRTCRecordingProgress* _Nonnull)process
   recording_info:(ByteRTCRecordingInfo* _Nonnull)recording_info;
/** 
*  @type callback
*  @brief 调用 startAudioRecording:{@link #ByteRTCAudio#startAudioRecording:} 或者 stopAudioRecording{@link #ByteRTCAudio#stopAudioRecording} 改变音频文件录制状态时，收到此回调。
*  @param state 录制状态，参看 ByteRTCAudioRecordingState{@link #ByteRTCAudioRecordingState}
*  @param error_code 录制错误码，参看 ByteRTCAudioRecordingErrorCode{@link #ByteRTCAudioRecordingErrorCode}
*/
- (void)rtcEngine:(ByteRTCAudio* _Nonnull)engine
        onAudioRecordingStateUpdate:(ByteRTCAudioRecordingState)state
                         error_code:(ByteRTCAudioRecordingErrorCode)error_code;

 /** 
  * @type callback
  * @brief 调用 startCloudProxy:{@link #ByteRTCAudio#startCloudProxy:} 开启云代理，SDK 首次成功连接云代理服务器时，回调此事件。
  * @param interval 从开启云代理到连接成功经过的时间，单位为 ms
  */
 - (void)rtcEngine:(ByteRTCAudio * _Nonnull)engine onCloudProxyConnected:(NSInteger)interval;

/** 
 * @hidden
 * @type callback
 * @brief 音频dump状态回调。
 * @param status 音频dump状态，参看 ByteRTCAudioDumpStatus{@link #ByteRTCAudioDumpStatus}。
 * @notes 本回调用于内部排查音质相关异常问题，开发者无需关注。
 */
- (void)rtcEngine:(ByteRTCAudio* _Nonnull)engine onAudioDumpStateChanged: (ByteRTCAudioDumpStatus)status;
@end

#pragma mark - ByteRTCAudio
/** 
 * @type api
 * @region 引擎管理
 * @brief SDK 回调给应用层的 delegate 对象，详见 ByteRTCAudio{@link #ByteRTCAudio}
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCAudio : NSObject
/**
 * @hidden
 */
@property(nonatomic, weak) id<ByteRTCAudioDelegate> _Nullable delegate;

#pragma mark - Engine Management Methods
/** 
 * @type api
 * @region 引擎管理
 * @brief 创建 ByteRTCAudio 实例。  <br>
 *        如果当前进程中未创建引擎实例，那么你必须先使用此方法，以使用 RTC 提供的各种音频能力。  <br>
 *        如果当前进程中已创建了引擎实例，再次调用此方法时，会返回已创建的引擎实例。
 * @param appId 每个应用的唯一标识符，由 RTC 控制台随机生成的。不同的 appId 生成的实例在 RTC 中进行音音频通话完全独立，无法互通。
 * @param delegate SDK 回调给应用层的 delegate，详见 ByteRTCAudioDelegate{@link #ByteRTCAudioDelegate}。
 * @param parameters 用以覆盖默认参数的本引擎实例参数。JSON 字符串格式。
 * @return  <br>
 *        + ByteRTCAudio：创建成功。返回一个可用的 ByteRTCAudio{@link #ByteRTCAudio} 实例  <br>
 *        + Null：创建失败。
 */
+ (ByteRTCAudio * _Nullable)createRTCAudio:(NSString * _Nonnull)appId
                    delegate:(id<ByteRTCAudioDelegate> _Nullable)delegate
                  parameters:(NSDictionary* _Nullable)parameters;
/** 
 * @type api
 * @region 引擎管理
 * @brief 手动销毁引擎实例对象，如果当前的引擎对象是通过 createRTCAudio:delegate:parameters:{@link #ByteRTCAudio#createRTCAudio:delegate:parameters:} 所创建的，则行为与 destroy{@link #ByteRTCAudioRoom#destroy} 保持一致
 * @notes  <br>
 *      + 请确保和需要销毁的 ByteRTCAudioDelegate{@link #ByteRTCAudioDelegate} 实例相关的业务场景全部结束后，才调用此方法  <br>
 *      + 该方法在调用之后，会销毁所有和此 ByteRTCAudioDelegate{@link #ByteRTCAudioDelegate} 实例相关的内存，并且停止与媒体服务器的任何交互  <br>
 *      + 调用本方法会启动 SDK 退出逻辑。引擎线程会保留，直到退出逻辑完成。因此，不要在回调线程中直接调用此 API，也不要在回调中等待主线程的执行，并同时在主线程调用本方法。不然会造成死锁。  <br>
 *      + 可以通过 Objective-C 的ARC机制，在 dealloc 时自动触发销毁逻辑
 */
+ (void)destroyRTCAudio;
/** 
 * @type api
 * @region 引擎管理
 * @brief 获取 SDK 当前的版本号。
 * @return SDK 当前的版本号。
 */
+ (NSString * _Nonnull)getSDKVersion;
/** 
 * @type api
 * @region 引擎管理
 * @brief 获取 SDK 内各种错误码、警告码的描述文字。
 * @param code  <br>
 *        通过 rtcEngine:onWarning:{@link #ByteRTCAudioDelegate#rtcEngine:onWarning:} 和 rtcEngine:onError:{@link #ByteRTCAudioDelegate#rtcEngine:onError:} 回调获得的值，
 *        具体可以参考 ByteRTCWarningCode{@link #ByteRTCWarningCode} 和 ByteRTCErrorCode{@link #ByteRTCErrorCode} 。
 * @return 描述文字。
 */
+ (NSString * _Nonnull)getErrorDescription:(NSInteger)code;
/** 
 * @type api
 * @region 引擎管理
 * @brief 设置业务标识参数  <br>
 *        可通过 businessId 区分不同的业务场景。businessId 由客户自定义，相当于一个“标签”，可以分担和细化现在 AppId 的逻辑划分的功能，但不需要鉴权。
 * @param businessId 用户设置的自己的 businessId 值。businessId 只是一个标签，颗粒度需要用户自定义。
 * @return  <br>
 *        + 0： 成功  <br>
 *        + < 0： 失败  <br>
 *        + -6001： 用户已经在房间中。  <br>
 *        + -6002： 输入非法，合法字符包括所有小写字母、大写字母和数字，除此外还包括四个独立字符分别是：英文句号，短横线，下划线和 @ 。
 * @notes 需要在调用 joinRoom:userInfo:roomConfig:{@link #ByteRTCAudioRoom#joinRoom:userInfo:roomConfig:} 之前调用，joinRoom:userInfo:roomConfig:{@link #ByteRTCAudioRoom#joinRoom:userInfo:roomConfig:}之后调用该方法无效。
 */
- (int)setBusinessId:(NSString* _Nullable)businessId;
/** 
 * @type api
 * @region 引擎管理
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
- (int)feedback:(NSArray<ByteRTCProblemOption *> * _Nullable)types desc:(NSString* _Nullable)desc;
/** 
 * @type api
 * @brief 设置运行时的参数
 * @param parameters 保留参数
 * @notes 该接口需在 joinRoom:userInfo:roomConfig:{@link #ByteRTCAudioRoom#joinRoom:userInfo:roomConfig:} 和 startAudioCapture{@link #ByteRTCAudio#startAudioCapture} 之前调用。
 */
- (void)setRuntimeParameters:(NSDictionary * _Nullable)parameters;

#pragma mark - Audio Management Methods
/** 
 * @type api
 * @region 音频管理
 * @brief 开启内部音频采集。默认为关闭状态。  <br>
 *        内部采集是指：使用 RTC SDK 内置的音频采集机制进行音频采集。
 *        调用该方法开启后，本地用户会收到 rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCAudioDelegate#rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:} 的回调。  <br>
 *        非隐身用户进房后调用该方法，房间中的其他用户会收到 rtcEngine:onUserStartAudioCapture:uid:{@link #ByteRTCAudioDelegate#rtcEngine:onUserStartAudioCapture:uid:} 的回调。
 * @notes  <br>
 *       + 若未取得当前设备的麦克风权限，调用该方法后会触发 rtcEngine:onWarning:{@link #ByteRTCAudioDelegate#rtcEngine:onWarning:} 回调。  <br>
 *       + 调用 stopAudioCapture{@link #ByteRTCAudio#stopAudioCapture} 可以关闭音频采集设备，否则，SDK 只会在销毁引擎的时候自动关闭设备。  <br>
 *       + 由于不同硬件设备初始化响应时间不同，频繁调用 stopAudioCapture{@link #ByteRTCAudio#stopAudioCapture} 和本接口闭麦/开麦可能出现短暂无声问题，建议使用 publishStream{@link #ByteRTCAudioRoom#publishStream}/unpublishStream{@link #ByteRTCAudioRoom#unpublishStream} 实现临时闭麦和重新开麦。
 *       + 创建引擎后，无论是否发布音频数据，你都可以调用该方法开启音频采集，并且调用后方可发布音频。  <br>
 *       + 如果需要从自定义音频采集切换为内部音频采集，你必须先停止发布流，调用 setAudioSourceType:{@link #ByteRTCAudio#setAudioSourceType:} 关闭自定义采集，再调用此方法手动开启内部采集。
 */
- (void)startAudioCapture;
 /** 
  * @type api
  * @region 音频管理
  * @brief 关闭内部音频采集。默认为关闭状态。  <br>
  *        内部采集是指：使用 RTC SDK 内置的音频采集机制进行音频采集。
  *        调用该方法，本地用户会收到 rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCAudioDelegate#rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:} 的回调。  <br>
  *        非隐身用户进房后调用该方法，房间中的其他用户会收到 rtcEngine:onUserStopAudioCapture:uid:{@link #ByteRTCAudioDelegate#rtcEngine:onUserStopAudioCapture:uid:} 的回调。
  * @notes  <br>
  *       + 调用 startAudioCapture{@link #ByteRTCAudio#startAudioCapture} 可以开启音频采集设备。  <br>
  *       + 如果不调用本方法停止内部音频采集，则只有当销毁引擎实例时，内部音频采集才会停止。
  */
 - (void)stopAudioCapture;
/** 
 * @hidden(macOS)
 * @type api
 * @region 音频管理
 * @brief 设置音频场景类型。
 *        你可以根据你的应用所在场景，选择合适的音频场景类型。
 *        选择音频场景后，SDK 会自动根据客户端音频采集播放设备和状态，适用通话音量/媒体音量。
 * @param audioScenario 音频场景类型，参看 ByteRTCAudioScenarioType{@link #ByteRTCAudioScenarioType}。
 * @notes  <br>
 *        + 建议在加入房间和调用音频相关接口之前，调用此接口设置音频场景类型。如果在此之后调用此接口，可能会引入音频卡顿。
 *        + 通话音量更适合通话、会议等对信息准确度更高的场景。通话音量会激活系统硬件信号处理，使通话声音更清晰。同时，音量无法降低到 0。
 *        + 媒体音量更适合娱乐场景，因其声音的表现力会更强。媒体音量下，最低音量可以为 0。
 */
- (void)setAudioScenario:(ByteRTCAudioScenarioType)audioScenario;
/** 
 * @type api
 * @region 音频管理
 * @brief 设置音质档位。当所选的 ByteRTCRoomProfile{@link #ByteRTCRoomProfile} 中的音频参数无法满足你的场景需求时，调用本接口切换的音质档位。
 * @param audioProfile 音质档位，参看 ByteRTCAudioProfileType{@link #ByteRTCAudioProfileType}
 * @notes  <br>
 *        + 该方法在进房前后均可调用；  <br>
 *        + 支持通话过程中动态切换音质档位。
 */
- (void)setAudioProfile:(ByteRTCAudioProfileType)audioProfile;
/** 
 * @type api
 * @region 音频管理
 * @brief 调节音频采集音量
 * @param volume 采集的音量值和原始音量的比值，范围是 [0, 400]，单位为 %，自带溢出保护。
 *               只改变音频数据的音量信息，不涉及本端硬件的音量调节。<br>
 *        为保证更好的通话质量，建议将 volume 值设为 [0,100]。
 *       + 0：静音  <br>
 *       + 100：原始音量  <br>
 *       + 400: 最大可为原始音量的 4 倍(自带溢出保护)  <br>
 * @notes 在开启音频采集前后，你都可以使用此接口设定采集音量。
 */
- (void)setCaptureVolume:(NSInteger)volume;
/** 
 * @type api
 * @region 音频管理
 * @brief 调节本地播放的所有远端用户混音后的音量。播放音频前或播放音频时，你都可以使用此接口设定播放音量。
 * @param volume 音频播放音量值和原始音量的比值，范围是 [0, 400]，单位为 %，自带溢出保护。  <br>
 *               只改变音频数据的音量信息，不涉及本端硬件的音量调节。<br>
 *        为保证更好的通话质量，建议将 volume 值设为 [0,100]。  <br>
 *       + 0: 静音  <br>
 *       + 100: 原始音量  <br>
 *       + 400: 最大可为原始音量的 4 倍(自带溢出保护)  <br>
     * @notes 假设某远端用户 A 始终在被调节的目标用户范围内，当该方法与 setRemoteAudioPlaybackVolume:remoteUid:playVolume:{@link #ByteRTCAudio#setRemoteAudioPlaybackVolume:remoteUid:playVolume:} 或 setRemoteRoomAudioPlaybackVolume:{@link #ByteRTCAudioRoom#setRemoteRoomAudioPlaybackVolume:} 共同使用时，本地收听用户 A 的音量将为两次设置的音量效果的叠加。
 */
- (void)setPlaybackVolume:(NSInteger)volume;
/** 
 * @type api
 * @region 音频管理
 * @brief 启用音频信息提示。  <br>
 * @param config 详见 ByteRTCAudioPropertiesConfig{@link #ByteRTCAudioPropertiesConfig}  <br>
 * @notes 开启提示后，你可以：  <br>
 *       + 通过 rtcEngine:onLocalAudioPropertiesReport:{@link #ByteRTCAudioDelegate#rtcEngine:onLocalAudioPropertiesReport:} 回调获取本地麦克风和屏幕音频流采集的音频信息；  <br>
 *       + 通过 rtcEngine:onRemoteAudioPropertiesReport:totalRemoteVolume:{@link #ByteRTCAudioDelegate#rtcEngine:onRemoteAudioPropertiesReport:totalRemoteVolume:} 回调获取订阅的远端用户的音频信息。  <br>
 */
- (void)enableAudioPropertiesReport:(ByteRTCAudioPropertiesConfig* _Nonnull)config;
/** 
 * @hidden(macOS)
 * @type api
 * @region 音频管理
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
 * @brief 设置耳返的音量。
 * @param volume 耳返的音量，取值范围：[0,100]，单位：%
 * @notes 设置耳返音量前，你必须先调用 setEarMonitorMode:{@link #setEarMonitorMode:} 打开耳返功能。
 */
- (void)setEarMonitorVolume:(NSInteger)volume;
/** 
 * @hidden(macOS)
 * @type api
 * @region 音频管理
 * @brief 在纯媒体音频场景下,切换 iOS 设备与耳机之间的蓝牙传输协议。
 * @param mode 蓝牙传输协议。详见 ByteRTCBluetoothMode{@link #ByteRTCBluetoothMode}。
 * @notes 以下场景你会收到 rtcEngine:onAudioDeviceWarning:deviceType:deviceWarning:{@link #ByteRTCAudioDelegate#rtcEngine:onAudioDeviceWarning:deviceType:deviceWarning:} 回调：1）当前不支持设置 HFP；2）非纯媒体音频场景，建议在调用此接口前调用 setAudioScenario:{@link #ByteRTCAudio#setAudioScenario:} 设置纯媒体音频场景。
 */
- (void)setBluetoothMode:(ByteRTCBluetoothMode) mode;
/** 
 * @type api
 * @region 混音
 * @brief 开启本地语音变调功能，多用于 K 歌场景。  <br>
 *        使用该方法，你可以对本地语音的音调进行升调或降调等调整。
 * @param pitch 相对于语音原始音调的升高/降低值，取值范围[-12，12]，默认值为 0，即不做调整。  <br>
 *        取值范围内每相邻两个值的音高距离相差半音，正值表示升调，负值表示降调，设置的绝对值越大表示音调升高或降低越多。  <br>
 *        超出取值范围则设置失败，并且会触发 rtcEngine:onWarning:{@link #ByteRTCAudioDelegate#rtcEngine:onWarning:} 回调，提示 ByteRTCWarningCode{@link #ByteRTCWarningCode} 错误码为 `WARNING_CODE_SET_SCREEN_STREAM_INVALID_VOICE_PITCH` 设置语音音调不合法
 */
- (void)setLocalVoicePitch:(NSInteger)pitch;
/** 
 * @type api
 * @region 音频管理
 * @brief 开启/关闭音量均衡功能。  <br>
 *        开启音量均衡功能后，人声的响度会调整为 -16lufs。如果已调用 setAudioMixingLoudness:loudness:{@link #ByteRTCAudioMixingManager#setAudioMixingLoudness:loudness:} 传入了混音音乐的原始响度，此音乐播放时，响度会调整为 -20lufs。
 * @param enable 是否开启音量均衡功能：  <br>
 *       + true: 是  <br>
 *       + false: 否
 * @notes 该接口须在调用 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} 开始播放音频文件之前调用。
 */
- (void)enableVocalInstrumentBalance:(BOOL)enable;
/** 
 * @type api
 * @region 音频管理
 * @brief 打开/关闭音量闪避功能。  <br>
 *        开启该功能后，当检测到远端人声时，本地的音频播放音量会自动减弱，从而保证远端人声的清晰可辨；当远端人声消失时，本地音频音量会恢复到闪避前的音量水平。
 * @param enable 是否开启音量闪避：  <br>
 *        + true: 是  <br>
 *        + false: 否
 */
- (void)enablePlaybackDucking:(BOOL)enable;
/** 
 * @type api
 * @region 多房间
 * @brief 调节来自远端用户的音频播放音量
 * @param room_id 音频来源用户所在的房间 ID
 * @param uid 音频来源的远端用户 ID
 * @param volume 音频播放音量值和原始音量的比值，范围是 [0, 400]，单位为 %，自带溢出保护。为保证更好的通话质量，建议将 volume 值设为 [0,100]。 <br>
 *               只改变音频数据的音量信息，不涉及本端硬件的音量调节。<br>
 *              + 0: 静音  <br>
 *              + 100: 原始音量，默认值  <br>
 *              + 400: 最大可为原始音量的 4 倍(自带溢出保护)  <br>
 * @notes 假设某远端用户 A 始终在被调节的目标用户范围内，<br>
 *        + 当该方法与 setRemoteRoomAudioPlaybackVolume:{@link #ByteRTCAudioRoom#setRemoteRoomAudioPlaybackVolume:} 共同使用时，本地收听用户 A 的音量为后调用的方法设置的音量；<br>
 *        + 当该方法与 setPlaybackVolume:{@link #ByteRTCAudio#setPlaybackVolume:} 方法共同使用时，本地收听用户 A 的音量将为两次设置的音量效果的叠加。
 */
- (void)setRemoteAudioPlaybackVolume:(NSString *_Nonnull)room_id
                           remoteUid:(NSString *_Nonnull)uid
                          playVolume:(NSInteger)volume;
/** 
 * @hidden(macOS)
 * @type api
 * @brief 强制切换当前的音频播放路由。默认使用 setDefaultAudioRoute:{@link #ByteRTCAudio#setDefaultAudioRoute:} 中设置的音频路由。
 *        音频播放路由发生变化时，会收到 rtcEngine:onAudioRouteChanged:{@link #ByteRTCAudioDelegate#rtcEngine:onAudioRouteChanged:} 回调。
 * @param audioRoute 音频播放路由，参见 ByteRTCAudioRoute{@link #ByteRTCAudioRoute}。仅支持扬声器和默认路由设备。
 * @return  <br>
 *        + 0: 方法调用成功  <br>
 *        + < 0: 方法调用失败。失败原因参看 ByteRTCMediaDeviceWarning{@link #ByteRTCMediaDeviceWarning} 回调。
 * @notes <br>
 *      + 你必须调用 setAudioScenario:{@link #ByteRTCAudio#setAudioScenario:} 将音频场景切换为 `COMMUNICATION` 后，再调用本接口。<br>
 *      + 连接/移除音频设备后，音频路由可能发生切换。切换逻辑参见[移动端设置音频路由](https://www.volcengine.com/docs/6348/117836)。<br>
 *      + 不同音频场景中，音频路由和发布订阅状态到音量类型的映射关系详见 ByteRTCAudioScenarioType{@link #ByteRTCAudioScenarioType} 。
 */
- (int)setAudioRoute:(ByteRTCAudioRoute)audioRoute;
 /** 
 * @hidden(macOS)
 * @type api
 * @brief 将默认的音频播放设备设置为听筒或扬声器。<br>
 *        当所有音频外设（耳机，音箱等）移除后，音频路由将被切换到默认设备。发生切换时会收到 rtcEngine:onAudioRouteChanged:{@link #ByteRTCAudioDelegate#rtcEngine:onAudioRouteChanged:} 回调。
 * @param audioRoute 音频播放设备。参看 ByteRTCAudioRoute{@link #ByteRTCAudioRoute}。仅支持听筒或扬声器。
 * @return <br>
 *        + 0: 方法调用成功。<br>
 *        + < 0: 方法调用失败。
 * @notes 参见[移动端设置音频路由](https://www.volcengine.com/docs/6348/117836)。
 */
- (int)setDefaultAudioRoute:(ByteRTCAudioRoute)audioRoute;
/** 
 * @hidden(macOS)
 * @type api
 * @region 音频管理
 * @brief 获取当前使用的音频播放路由。  <br>
 * @return 详见 ByteRTCAudioRoute{@link #ByteRTCAudioRoute}
 * @notes 要设置音频路由，详见 setAudioRoute:{@link #ByteRTCAudio#setAudioRoute:}。
 */
- (ByteRTCAudioRoute)getAudioRoute;
/** 
 * @type api
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
 * @type api
 * @region 音频管理
 * @brief 发送音频流同步信息。将消息通过音频流发送到远端，并实现与音频流同步，该接口调用成功后，远端用户会收到 rtcEngine:onStreamSyncInfoReceived:streamType:data:{@link #ByteRTCAudioDelegate#rtcEngine:onStreamSyncInfoReceived:streamType:data:} 回调。
 * @param data 消息内容。
 * @param repeatCount 消息发送重复次数。取值范围是 [0, 30]。
 * @return  <br>
 *        + >=0: 消息发送成功。返回成功发送的次数。  <br>
 *        + -1: 消息发送失败。消息长度大于 255 字节。  <br>
 *        + -2: 消息发送失败。传入的消息内容为空。  <br>
 *        + -3: 消息发送失败。通过屏幕流进行消息同步时，此屏幕流还未发布。  <br>
 *        + -4: 消息发送失败。通过用麦克风或自定义设备采集到的音频流进行消息同步时，此音频流还未发布，详见错误码 ByteRTCErrorCode{@link #ByteRTCErrorCode}。  <br>
 * @notes 
 * + 调用本接口的频率建议不超过 50 次每秒。
 * + 在 `ByteRTCRoomProfileInteractivePodcast` 房间模式下，此消息一定会送达。在其他房间模式下，如果本地用户未说话，此消息不一定会送达。
 */
- (int)sendStreamSyncInfo:(NSData* _Nonnull)data repeatCount:(int)repeatCount;

#pragma mark - Voice Effect Management Methods
/** 
 * @type api
 * @valid since 3.32
 * @region 美声特效管理
 * @brief 设置变声特效类型
 * @param voiceChanger 变声特效类型，参看 ByteRTCVoiceChangerType{@link #ByteRTCVoiceChangerType}。
 * @return 方法调用结果： <br>
 *        + 0：成功；<br>
 *        + !0：失败。
 * @notes  <br>
 *        + 在进房前后都可设置。  <br>
 *        + 对 RTC SDK 内部采集的音频和自定义采集的音频都生效。 <br>
 *        + 只对单声道音频生效。<br>
 *        + 与 setVoiceReverbType:{@link #setVoiceReverbType:} 互斥，后设置的特效会覆盖先设置的特效。<br>
 *        + 使用本接口前，请联系 RTC 技术支持了解更多详情。
 */
- (void)setVoiceChangerType:(ByteRTCVoiceChangerType)voiceChanger;
/** 
 * @type api
 * @valid since 3.32
 * @region 美声特效管理
 * @brief 设置混响特效类型
 * @param voiceReverb 混响特效类型，参看 ByteRTCVoiceReverbType{@link #ByteRTCVoiceReverbType}。
 * @return 方法调用结果： <br>
 *        + 0：成功；<br>
 *        + !0：失败。
 * @notes  <br>
 *        + 在进房前后都可设置。  <br>
 *        + 对 RTC SDK 内部采集的音频和自定义采集的音频都生效。 <br>
 *        + 只对单声道音频生效。<br>
 *        + 与 setVoiceChangerType:{@link #setVoiceChangerType:} 互斥，后设置的特效会覆盖先设置的特效。 <br>
 *        + 使用本接口前，请联系 RTC 技术支持了解更多详情。
 */
- (void)setVoiceReverbType:(ByteRTCVoiceReverbType)voiceReverb;
/** 
 * @type api
 * @brief 设置本地采集语音的均衡效果。包含内部采集和外部采集，但不包含混音音频文件。
 * @param config 语音均衡效果，参看 ByteRTCVoiceEqualizationConfig{@link #ByteRTCVoiceEqualizationConfig}
 * @return  <br>
 *        + 0： 成功。  <br>
 *        + < 0： 失败。
 * @notes 根据奈奎斯特采样率，音频采样率必须大于等于设置的中心频率的两倍，否则，设置不生效。
 */
-(int)setLocalVoiceEqualization:(ByteRTCVoiceEqualizationConfig* _Nonnull)config;
/** 
 * @type api
 * @brief 设置本地采集音频的混响效果。包含内部采集和外部采集，但不包含混音音频文件。
 * @param param 混响效果，参看 ByteRTCVoiceReverbConfig{@link #ByteRTCVoiceReverbConfig}
 * @return  <br>
 *        + 0： 成功。  <br>
 *        + < 0： 失败。
 * @notes 调用 enableLocalVoiceReverb:{@link #ByteRTCAudio#enableLocalVoiceReverb:} 开启混响效果。
 */
-(int)setLocalVoiceReverbParam:(ByteRTCVoiceReverbConfig* _Nonnull)param;
/** 
 * @type api
 * @brief 开启本地音效混响效果
 * @param enable 是否开启
 * @return  <br>
 *        + 0： 成功。  <br>
 *        + < 0： 失败。
 * @notes 调用 setLocalVoiceReverbParam:{@link #ByteRTCAudio#setLocalVoiceReverbParam:} 设置混响效果。
 */
-(int)enableLocalVoiceReverb:(bool)enable;

#pragma mark - Custom Audio Capture Rendering Methods
/** 
 * @type api
 * @region 自定义音频采集渲染
 * @brief  切换音频采集方式
 * @param type 音频数据源，详见 ByteRTCAudioSourceType{@link #ByteRTCAudioSourceType}。<br>
 *             默认使用内部音频采集。音频采集和渲染方式无需对应。
 * @return  方法调用结果：  <br>
 *        + >0: 切换成功。<br>
 *        + -1：切换失败。
 * @notes  <br>
 *      + 进房前后调用此方法均有效。<br>
 *      + 如果你调用此方法由内部采集切换至自定义采集，SDK 会自动关闭内部采集。然后，调用 pushExternalAudioFrame:{@link #ByteRTCAudio#pushExternalAudioFrame:} 推送自定义采集的音频数据到 RTC SDK 用于传输。 <br>
 *      + 如果你调用此方法由自定义采集切换至内部采集，你必须再调用 startAudioCapture{@link #ByteRTCAudio#startAudioCapture} 手动开启内部采集。
 */
- (int)setAudioSourceType:(ByteRTCAudioSourceType)type;
/** 
 * @type api
 * @region 自定义音频采集渲染
 * @brief  切换音频渲染方式
 * @param type 音频输出类型，详见 ByteRTCAudioRenderType{@link #ByteRTCAudioRenderType} <br>
 *             默认使用内部音频渲染。音频采集和渲染方式无需对应。
 * @return  方法调用结果：  <br>
 *        + >0: 切换成功。<br>
 *        + -1：切换失败。
 * @notes  <br>
 *      + 进房前后调用此方法均有效。<br>
 *      + 如果你调用此方法切换至自定义渲染，调用 pullExternalAudioFrame:{@link #ByteRTCAudio#pullExternalAudioFrame:} 获取音频数据。 <br>
 */
- (int)setAudioRenderType:(ByteRTCAudioRenderType)type;
/** 
 * @type api
 * @region 自定义音频采集渲染
 * @brief 推送自定义采集的音频数据到 RTC SDK。
 * @param audioFrame 音频数据帧，详见 ByteRTCAudioFrame{@link #ByteRTCAudioFrame}
 * @return 方法调用结果  <br>
 *          + true: 设置成功  <br>
 *          + false: 设置失败  <br>
 * @notes  <br>
 *       + 推送外部音频数据前，必须先调用 setAudioSourceType:{@link #ByteRTCAudio#setAudioSourceType:} 开启自定义采集。<br>
 *       + 你必须每隔 10 毫秒推送一次外部采集的音频数据。单次推送的 samples (音频采样点个数）应该为 audioFrame.sampleRate / 100。比如设置采样率为 48000 时， 每次应该推送 480 个采样点。  <br>
 *       + 音频采样格式为 S16。音频缓冲区内的数据格式必须为 PCM 数据，其容量大小应该为 audioFrame.samples × audioFrame.channel × 2。  <br>
 */
 - (BOOL)pushExternalAudioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;
/** 
 * @type api
 * @region 自定义音频采集渲染
 * @brief 拉取音频数据，用于自定义渲染。
 * @param audioFrame 音频数据帧，详见 ByteRTCAudioFrame{@link #ByteRTCAudioFrame}
 * @return  方法调用结果  <br>
 *        + true: 设置成功  <br>
 *        + false: 设置失败  <br>
 * @notes  <br>
 *       + 拉取外部音频数据前，必须先调用 setAudioRenderType:{@link #ByteRTCAudio#setAudioRenderType:} 开启自定义渲染。<br>
 *       + 由于 RTC SDK 的帧长为 10 毫秒，你应当每隔 10 毫秒拉取一次音频数据。确保音频采样点数（sample）x 拉取频率等于 audioFrame 的采样率 （sampleRate）。如设置采样率为 48000 时，每 10 毫秒调用本接口拉取数据，每次应拉取 480 个采样点。  <br>
 *       + 音频采样格式为 S16。音频缓冲区内的数据格式必须为 PCM 数据，其容量大小应该为 audioFrame.samples × audioFrame.channel × 2。  <br>
 */
 - (BOOL)pullExternalAudioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;

#pragma mark - Audio Data Callback Methods
/** 
 * @type api
 * @region 音频数据回调
 * @brief 设置并开启指定的音频数据帧回调
 * @param method 音频回调方法，参看 ByteRTCAudioFrameCallbackMethod{@link #ByteRTCAudioFrameCallbackMethod}。  <br>
 *               当音频回调方法设置为 `0`、`1`、`2`时，你需要在参数 `format` 中指定准确的采样率和声道，暂不支持设置为自动。  <br>
 *               当音频回调方法设置为 `3`时，暂不支持音频参数格式中设置准确的采样率和声道，你需要设置为自动。
 * @param format 音频参数格式，参看 ByteRTCAudioFormat{@link #ByteRTCAudioFormat}。
 * @notes 开启音频回调并调用 registerAudioFrameObserver:{@link #ByteRTCAudio#registerAudioFrameObserver:} ByteRTCAudioFrameObserver{@link #ByteRTCAudioFrameObserver} 会收到对应的音频回调。两者调用顺序没有限制且相互独立。  <br>
 */
- (void)enableAudioFrameCallback:(ByteRTCAudioFrameCallbackMethod)method
                          format:(ByteRTCAudioFormat* _Nullable)format;
/** 
 * @type api
 * @region 音频数据回调
 * @brief 关闭音频回调
 * @param method 音频回调方法，参看 ByteRTCAudioFrameCallbackMethod{@link #ByteRTCAudioFrameCallbackMethod}。
 * @notes 该方法需要在调用 enableAudioFrameCallback:format:{@link #ByteRTCAudio#enableAudioFrameCallback:format:} 之后调用。
 */
- (void)disableAudioFrameCallback:(ByteRTCAudioFrameCallbackMethod)method;
/** 
 * @type api
 * @region 音频数据回调
 * @brief 注册音频数据回调观察者。  <br>
 * @param audioFrameObserver 音频数据观察者，参看 ByteRTCAudioFrameObserver{@link #ByteRTCAudioFrameObserver}。如果传入 null，则取消注册。
 * @return  <br>
 *        + true: 方法调用成功 <br>
 *        + false: 方法调用失败 <br>
 * @notes 注册音频数据回调观察者并调用 enableAudioFrameCallback:format:{@link #ByteRTCAudio#enableAudioFrameCallback:format:} 后，ByteRTCAudioFrameObserver{@link #ByteRTCAudioFrameObserver} 会收到对应的音频回调。
 */
- (BOOL)registerAudioFrameObserver:(_Nullable id<ByteRTCAudioFrameObserver>) audioFrameObserver;

#pragma mark - Audio Processing Methods

/** 
* @type api
* @brief 注册自定义音频处理器。<br>
*        注册完成后，你可以调用 enableAudioProcessor:audioFormat:{@link #ByteRTCAudio#enableAudioProcessor:audioFormat:}，对本地采集或接收到的远端音频进行处理。
* @param processor 自定义音频处理器，详见 ByteRTCAudioFrameProcessor{@link #ByteRTCAudioFrameProcessor}。<br>
*        SDK 只持有 processor 的弱引用，你应保证其生命周期。
* @return 方法调用结果： <br>
*        + true：成功；<br>
*        + false：失败。
* @notes 重复调用此接口时，仅最后一次调用生效。
*/
- (BOOL)registerAudioProcessor:(_Nullable id<ByteRTCAudioFrameProcessor>)processor;
/** 
 * @type api
 * @brief 设置并开启指定的音频帧回调，进行自定义处理。
 * @param method 音频帧类型，参看 ByteRTCAudioFrameMethod{@link #ByteRTCAudioFrameMethod}。可多次调用此接口，处理不同类型的音频帧。  <br>
 *        选择不同类型的音频帧将收到对应的回调：  <br>
 *        + 选择本地采集的音频时，会收到 onProcessRecordAudioFrame:{@link #ByteRTCAudioFrameProcessor#onProcessRecordAudioFrame:}。<br>
 *        + 选择远端音频流的混音音频时，会收到 onProcessPlayBackAudioFrame:{@link #ByteRTCAudioFrameProcessor#onProcessPlayBackAudioFrame:}。 <br>
 *        + 选择远端音频流时，会收到 onProcessRemoteUserAudioFrame:audioFrame:{@link #ByteRTCAudioFrameProcessor#onProcessRemoteUserAudioFrame:audioFrame:}。 <br>
 *        + 选择软件耳返音频时，会收到 onProcessEarMonitorAudioFrame:{@link #ByteRTCAudioFrameProcessor#onProcessEarMonitorAudioFrame:}。(仅适用于 iOS 平台)
 *        + 选择屏幕共享音频流时，会收到 onProcessScreenAudioFrame:{@link #ByteRTCAudioFrameProcessor#onProcessScreenAudioFrame:}。
 * @param format 设定自定义处理时获取的音频帧格式，参看 ByteRTCAudioFormat{@link #ByteRTCAudioFormat}。
 * @notes <br>
 *        + 在调用此接口前，你需要调用 registerAudioProcessor:{@link #ByteRTCAudio#registerAudioProcessor:} 注册自定义音频处理器。<br>
 *        + 要关闭音频自定义处理，调用 disableAudioProcessor:{@link #ByteRTCAudio#disableAudioProcessor:}。
 */
- (void)enableAudioProcessor:(ByteRTCAudioFrameMethod)method
                 audioFormat:(ByteRTCAudioFormat *_Nullable)format;
/** 
* @type api
* @brief 关闭自定义音频处理。
* @param method 音频帧类型，参看 ByteRTCAudioFrameMethod{@link #ByteRTCAudioFrameMethod}。
*/
- (void)disableAudioProcessor:(ByteRTCAudioFrameMethod)method;


#pragma mark - Encryption Methods
/** 
 * @type api
 * @region 加密
 * @brief 设置传输时使用内置加密的方式 <br>
 * @param encrypt_type 内置加密算法，详见 ByteRTCEncryptType{@link #ByteRTCEncryptType}
 * @param key 加密密钥，长度限制为 36 位，超出部分将会被截断
 * @notes  <br>
 *       + 使用传输时内置加密时，使用此方法；如果需要使用传输时自定义加密，参看 onEncryptData:{@link #ByteRTCEncryptHandler#onEncryptData:}。
 *         内置加密和自定义加密互斥，根据最后一个调用的方法确定传输加密的方案。  <br>
 *       + 该方法必须在进房之前调用，可重复调用，以最后调用的参数作为生效参数。  <br>
 */
- (void)setEncryptInfo:(ByteRTCEncryptType)encrypt_type key:(NSString * _Nonnull)key;
/** 
 * @type api
 * @region 加密
 * @brief 设置自定义加密和解密方式
 *        需要实现对应的加密和解密方法。详情参考 ByteRTCEncryptHandler{@link #ByteRTCEncryptHandler}  <br>
 * @param handler  <br>
 *        自定义加密 handler，需要实现里面的加密和解密方法  <br>
 * @notes
 *       + 该方法与 setEncryptInfo:key:{@link #ByteRTCAudio#setEncryptInfo:key:} 为互斥关系,
 *         即按照调用顺序，最后一个调用的方法为最终生效的版本  <br>
 *       + 该方法必须在调用 joinRoom:userInfo:roomConfig:{@link #ByteRTCAudioRoom#joinRoom:userInfo:roomConfig:}
 * 之前调用，可重复调用，以最后调用的参数作为生效参数  <br>
 *       + 无论加密或者解密，其对原始数据的长度修改，需要控制在90%-120%之间，即如果输入数据为100字节，则处理完成后的数据必须在
 *         90至120字节之间，如果加密或解密结果超出该长度限制，则该音音频桢会被丢弃  <br>
 *       + 数据加密/解密为串行执行，因而视实现方式不同，可能会影响到最终渲染效率，是否使用该方法，需要由使用方谨慎评估  <br>
 */
- (void)setCustomizeEncryptHandler:(id<ByteRTCEncryptHandler> _Nullable)handler;

#pragma mark - Multi-room Methods
/** 
 * @type api
 * @region 房间管理
 * @brief 创建房间实例。
 *        调用此方法仅返回一个房间实例，你仍需调用 joinRoom:userInfo:roomConfig:{@link #ByteRTCAudioRoom#joinRoom:userInfo:roomConfig:} 才能真正地创建/加入房间。
 *        多次调用此方法以创建多个 ByteRTCAudioRoom{@link #ByteRTCAudioRoom} 实例。分别调用各 ByteRTCAudioRoom 实例中的 joinRoom:userInfo:roomConfig:{@link #ByteRTCAudioRoom#joinRoom:userInfo:roomConfig:} 方法，同时加入多个房间。
 *        多房间模式下，用户可以同时订阅各房间的音频流。
 * @param roomId 标识通话房间的房间 ID。该字符串符合正则表达式：`[a-zA-Z0-9_@\-\.]{1,128}`。
 * @return 创建的 ByteRTCAudioRoom{@link #ByteRTCAudioRoom} 房间实例。
 * @notes <br>
 *        + 如果需要加入的房间已存在，你仍需先调用本方法来获取 ByteRTCAudioRoom 实例，再调用 joinRoom:userInfo:roomConfig:{@link #ByteRTCAudioRoom#joinRoom:userInfo:roomConfig:} 加入房间。
 *        + 请勿使用同样的 roomId 创建多个房间，否则后创建的房间实例会替换先创建的房间实例。
 *        + 加入多个房间后，用户可以同时订阅各房间的音频流，同一时间仅能在一个房间内发布音频流。
 */
- (ByteRTCAudioRoom * _Nullable)createRTCRoom:(NSString * _Nonnull)roomId;

#pragma mark - Speech Recognition Service Methods
/** 
 * @hidden(macOS)
 * @type api
 * @region 语音识别服务
 * @brief 开启自动语音识别服务。该方法将识别后的用户语音转化成文字，并通过 onMessage:{@link #ByteRTCASREngineEventHandler#onMessage:} 事件回调给用户。
 * @param handler 语音识别服务使用状态回调，参看 ByteRTCASREngineEventHandler{@link #ByteRTCASREngineEventHandler}
 * @param asrConfig 校验信息，参看 ByteRTCASRConfig{@link #ByteRTCASRConfig}
 */
- (void)startASR:(ByteRTCASRConfig * _Nonnull)asrConfig handler:(id<ByteRTCASREngineEventHandler> _Nonnull)handler;
/** 
 * @hidden(macOS)
 * @type api
 * @region 语音识别服务
 * @brief 关闭语音识别服务
 */
- (void)stopASR;

#pragma mark - Local Recording Methods
/** 
 * @type api
 * @region 本地录制
 * @brief 该方法将通话过程中的音频数据录制到本地的文件中。
 * @param recordingConfig 本地录制参数配置，参看 ByteRTCRecordingConfig{@link #ByteRTCRecordingConfig}
 * @return   <br>
 *        + 0: 正常
 *        + -1: 参数设置异常
 *        + -2: 当前版本 SDK 不支持该特性，请联系技术支持人员
 * @notes  <br>
 *        + 调用该方法后，你会收到 rtcEngine:onRecordingStateUpdate:error_code:recording_info:{@link #ByteRTCAudioDelegate#rtcEngine:onRecordingStateUpdate:error_code:recording_info:} 回调。  <br>
 *        + 如果录制正常，系统每秒钟会通过 rtcEngine:onRecordingProgressUpdate:recording_info:{@link #ByteRTCAudioDelegate#rtcEngine:onRecordingProgressUpdate:recording_info:} 回调通知录制进度。
 */
- (int)startFileRecording:(ByteRTCRecordingConfig* _Nonnull)recordingConfig;
/** 
 * @type api
 * @region 本地录制
 * @brief 停止本地录制
 * @notes  <br>
 *        + 调用 startFileRecording:{@link #ByteRTCAudio#startFileRecording:} 开启本地录制后，你必须调用该方法停止录制。  <br>
 *        + 调用该方法后，你会收到 rtcEngine:onRecordingStateUpdate:error_code:recording_info:{@link #ByteRTCAudioDelegate#rtcEngine:onRecordingStateUpdate:error_code:recording_info:} 回调提示录制结果。
 */
- (void)stopFileRecording;
/** 
 * @type api
 * @brief 开启录制语音通话，生成本地文件。
 * @param recordingConfig 参看 ByteRTCAudioRecordingConfig{@link #ByteRTCAudioRecordingConfig}
 * @return  <br>
 *        + 0: 正常 <br>
 *        + -2: 参数设置异常 <br>
 *        + -3: 当前版本 SDK 不支持该特性，请联系技术支持人员
 * @notes <br>
 *        + 录制包含各种音频效果。但不包含背景音乐。<br>
 *        + 调用 stopAudioRecording{@link #ByteRTCAudio#stopAudioRecording} 关闭录制。<br>
 *        + 加入房间后才可调用。如果加入了多个房间，录制的文件中会包含各个房间的音频。离开最后一个房间后，录制任务自动停止。 <br>
 *        + 调用该方法后，你会收到 rtcEngine:onAudioRecordingStateUpdate:error_code:{@link #IRTCAudioEventHandler#rtcEngine:onAudioRecordingStateUpdate:error_code:} 回调。  <br>
 */
- (int)startAudioRecording:(ByteRTCAudioRecordingConfig* _Nonnull) recordingConfig;
/** 
 * @type api
 * @brief 停止音频文件录制
 * @return <br>
 *         + 0: 正常 <br>
 *         + -3: 当前版本 SDK 不支持该特性，请联系技术支持人员
 * @notes 调用 startAudioRecording:{@link #ByteRTCAudio#startAudioRecording:} 开启本地录制。
 */
 - (int)stopAudioRecording;

#pragma mark - Audio Mixing Methods
/** 
  * @type api
  * @region 混音
  * @brief 混音管理接口创建
  * @return 混音管理实例，详见ByteRTCAudioMixingManager{@link #ByteRTCAudioMixingManager}
  */
 - (ByteRTCAudioMixingManager *_Nullable)getAudioMixingManager;

#pragma mark - Real-time Messaging Methods
/** 
 * @type api
 * @region 实时消息通信
 * @brief 必须先登录，才能调用 sendUserMessageOutsideRoom:message:config:{@link #ByteRTCAudio#sendUserMessageOutsideRoom:message:config:} 和 sendServerMessage:{@link #ByteRTCAudio#sendServerMessage:} 发送房间外点对点消息和向应用服务器发送消息 <br>
 *        在调用本接口登录后，如果想要登出，需要调用 logout{@link #ByteRTCAudio#logout}
 * @param token  <br>
 *        动态密钥  <br>
 *        用户登录必须携带的 Token，用于鉴权验证。  <br>
 *        登录 Token 与加入房间时必须携带的 Token 不同。测试时可使用控制台生成临时 Token，`roomId` 填任意值或置空，正式上线需要使用密钥 SDK 在你的服务端生成并下发 Token。
 * @param uid  <br>
 *        用户 ID  <br>
 *        用户 ID 在 appid的维度下是唯一的。
 * @return <br>
 *        + `0`：成功<br>
 *        + `-1`：失败。无效参数<br>
 *        + `-2`：无效调用。用户已经登录。成功登录后再次调用本接口将收到此返回值 <br>
 *        + `-3`：失败。Engine 为空。调用 createRTCAudio:delegate:parameters:{@link #ByteRTCAudio#createRTCAudio:delegate:parameters:} 创建引擎实例后再调用本接口。
 * @notes  本地用户调用此方法登录后，会收到 rtcEngine:onLoginResult:errorCode:elapsed:{@link #ByteRTCAudioDelegate#rtcEngine:onLoginResult:errorCode:elapsed:} 回调通知登录结果，远端用户不会收到通知。
 */
- (int64_t)login:(NSString * _Nonnull)token uid:(NSString * _Nonnull)uid;
/** 
 * @type api
 * @region 实时消息通信
 * @brief 调用本接口登出后，无法调用房间外消息以及端到服务器消息相关的方法或收到相关回调。
 * @notes  <br>
 *       + 调用本接口登出前，必须先调用 login:uid:{@link #ByteRTCAudio#login:uid:} 登录  <br>
 *       + 本地用户调用此方法登出后，会收到 rtcEngineOnLogout:{@link #ByteRTCAudioDelegate#rtcEngineOnLogout:}  回调通知结果，远端用户不会收到通知。
 */
- (void)logout;
/** 
 * @type api
 * @region 实时消息通信
 * @brief 更新用户用于登录的 Token  <br>
 *        Token 有一定的有效期，当 Token 过期时，需调用此方法更新登录的 Token 信息。  <br>
 *        调用 login:uid:{@link #ByteRTCAudio#login:uid:} 方法登录时，如果使用了过期的 Token 将导致登录失败，并会收到 rtcEngine:onLoginResult:errorCode:elapsed:{@link #ByteRTCAudioDelegate#rtcEngine:onLoginResult:errorCode:elapsed:} 回调通知，错误码为 ByteRTCLoginErrorCodeInvalidToken。此时需要重新获取 Token，并调用此方法更新 Token。
 * @param token  <br>
 *        更新的动态密钥  <br>
 * @notes  <br>
 *       + 如果 Token 无效导致登录失败，则调用此方法更新 Token 后，SDK 会自动重新登录，而用户不需要自己调用 login:uid:{@link #ByteRTCAudio#login:uid:} 方法。  <br>
 *       + Token 过期时，如果已经成功登录，则不会受到影响。Token 过期的错误会在下一次使用过期 Token 登录时，或因本地网络状况不佳导致断网重新登录时通知给用户。
 */
- (void)updateLoginToken:(NSString * _Nonnull)token;
/** 
 * @type api
 * @region 实时消息通信
 * @brief 设置应用服务器参数  <br>
 *        客户端调用 sendServerMessage:{@link #ByteRTCAudio#sendServerMessage:} 或 sendServerBinaryMessage:{@link #ByteRTCAudio#sendServerBinaryMessage:} 发送消息给应用服务器之前，必须需要设置有效签名和应用服务器地址。
 * @param signature  <br>
 *        动态签名  <br>
 *        应用服务器会使用该签名对请求进行鉴权验证。  <br>
 * @param url  <br>
 *        应用服务器的地址
 * @notes  <br>
 *       + 用户必须调用 login:uid:{@link #ByteRTCAudio#login:uid:} 登录后，才能调用本接口。  <br>
 *       + 调用本接口后，SDK 会使用 rtcEngine:onServerParamsSetResult:{@link #ByteRTCAudioDelegate#rtcEngine:onServerParamsSetResult:} 返回相应结果。
 */
- (void)setServerParams:(NSString * _Nonnull)signature url:(NSString * _Nonnull)url;
/** 
 * @type api
 * @region 实时消息通信
 * @brief 查询对端用户或本端用户的登录状态
 * @param peerUserId  <br>
 *        需要查询的用户 ID
 * @notes  <br>
 *       + 必须调用 login:uid:{@link #ByteRTCAudio#login:uid:} 登录后，才能调用本接口。  <br>
 *       + 调用本接口后，SDK 会使用 rtcEngine:onGetPeerOnlineStatus:status:{@link #ByteRTCAudioDelegate#rtcEngine:onGetPeerOnlineStatus:status:} 回调通知查询结果。  <br>
 *       + 在发送房间外消息之前，用户可以通过本接口了解对端用户是否登录，从而决定是否发送消息。也可以通过本接口查询自己查看自己的登录状态。
 */
- (void)getPeerOnlineStatus:(NSString * _Nonnull)peerUserId;
/** 
 * @type api
 * @region 实时消息通信
 * @brief 给房间外指定的用户发送文本消息（P2P）
 * @param userId  <br>
 *        消息接收用户的 ID
 * @param messageStr  <br>
 *        发送的文本消息内容  <br>
 *        消息不超过 64 KB。
 * @param config 消息类型，参看 ByteRTCMessageConfig{@link #ByteRTCMessageConfig}。
 * @return  <br>
 *        + >0：发送成功，返回这次发送消息的编号，从 1 开始递增  <br>
 *        + -1：发送失败，RtcEngine 实例未创建  <br>
 *        + -2：发送失败，userId 为空
 * @notes  <br>
 *       + 在发送房间外文本消息前，必须先调用 login:uid:{@link #ByteRTCAudio#login:uid:} 完成登录。  <br>
 *       + 用户调用本接口发送文本信息后，会收到一次 rtcEngine:onUserMessageSendResultOutsideRoom:error:{@link #ByteRTCAudioDelegate#rtcEngine:onUserMessageSendResultOutsideRoom:error:} 回调，得知消息是否成功发送；  <br>
 *       + 若文本消息发送成功，则 userId 所指定的用户会通过 rtcEngine:onUserMessageReceivedOutsideRoom:message:{@link #ByteRTCAudioDelegate#rtcEngine:onUserMessageReceivedOutsideRoom:message:} 回调收到该消息。
 */
- (int64_t)sendUserMessageOutsideRoom:(NSString * _Nonnull)userId message:(NSString * _Nonnull)messageStr config:(ByteRTCMessageConfig)config;
/** 
 * @type api
 * @region 实时消息通信
 * @brief 给房间外指定的用户发送二进制消息（P2P）
 * @param userId  <br>
 *        消息接收用户的 ID
 * @param messageStr  <br>
 *        发送的二进制消息内容  <br>
 *        消息不超过 46KB。
 * @param config 消息类型，参看 ByteRTCMessageConfig{@link #ByteRTCMessageConfig}。
 * @return  <br>
 *        + >0：发送成功，返回这次发送消息的编号，从 1 开始递增  <br>
 *        + -1：发送失败，RtcEngine 实例未创建  <br>
 *        + -2：发送失败，userId 为空
 * @notes  <br>
 *       + 在发送房间外二进制消息前，必须先调用 login:uid:{@link #ByteRTCAudio#login:uid:} 完成登录。  <br>
 *       + 用户调用本接口发送二进制消息后，会收到一次 rtcEngine:onUserMessageSendResultOutsideRoom:error:{@link #ByteRTCAudioDelegate#rtcEngine:onUserMessageSendResultOutsideRoom:error:} 回调，通知消息是否发送成功；  <br>
 *       + 若二进制消息发送成功，则 userId 所指定的用户会通过 rtcEngine:onUserBinaryMessageReceivedOutsideRoom:message:{@link #ByteRTCAudioDelegate#rtcEngine:onUserBinaryMessageReceivedOutsideRoom:message:}  回调收到该条消息。
 */
- (int64_t)sendUserBinaryMessageOutsideRoom:(NSString * _Nonnull)userId message:(NSData * _Nonnull)messageStr config:(ByteRTCMessageConfig)config;
/** 
 * @type api
 * @region 实时消息通信
 * @brief 客户端给应用服务器发送文本消息（P2Server）
 * @param messageStr  <br>
 *        发送的文本消息内容  <br>
 *        消息不超过 64 KB。
 * @return  <br>
 *        + >0：发送成功，返回这次发送消息的编号，从 1 开始递增  <br>
 *        + -1：发送失败，RtcEngine 实例未创建
 * @notes  <br>
 *       + 在向应用服务器发送文本消息前，必须先调用 login:uid:{@link #ByteRTCAudio#login:uid:} 完成登录，随后调用 setServerParams:url:{@link #ByteRTCAudio#setServerParams:url:} 设置应用服务器。  <br>
 *       + 调用本接口后，会收到一次 rtcEngine:onServerMessageSendResult:error:message:{@link #ByteRTCAudioDelegate#rtcEngine:onServerMessageSendResult:error:message:} 回调，通知消息发送方是否发送成功。  <br>
 *       + 若文本消息发送成功，则之前调用 setServerParams:url:{@link #ByteRTCAudio#setServerParams:url:} 设置的应用服务器会收到该条消息。
 */
- (int64_t)sendServerMessage:(NSString * _Nonnull)messageStr;
/** 
 * @type api
 * @region 实时消息通信
 * @brief 客户端给应用服务器发送二进制消息（P2Server）
 * @param messageStr  <br>
 *        发送的二进制消息内容  <br>
 *        消息不超过 46KB。
 * @return  <br>
 *        + >0：发送成功，返回这次发送消息的编号，从 1 开始递增  <br>
 *        + -1：发送失败，RtcEngine 实例未创建
 * @notes  <br>
 *       + 在向应用服务器发送二进制消息前，先调用 login:uid:{@link #ByteRTCAudio#login:uid:} 完成登录，随后调用 setServerParams:url:{@link #ByteRTCAudio#setServerParams:url:} 设置应用服务器。  <br>
 *       + 调用本接口后，会收到一次 rtcEngine:onServerMessageSendResult:error:message:{@link #ByteRTCAudioDelegate#rtcEngine:onServerMessageSendResult:error:message:} 回调，通知消息发送方发送成功或失败；  <br>
 *       + 若二进制消息发送成功，则之前调用 setServerParams:url:{@link #ByteRTCAudio#setServerParams:url:} 设置的应用服务器会收到该条消息。
 */
- (int64_t)sendServerBinaryMessage:(NSData * _Nonnull)messageStr;

#pragma mark - Pre-call Network Detection Methods
/** 
 * @type api
 * @region 通话前网络探测
 * @brief 开始通话前网络探测
 * @param is_test_uplink  是否探测上行带宽
 * @param expected_uplink_bitrate  期望上行带宽，单位：kbps<br>范围为 {0, [100-10000]}，其中， `0` 表示由 SDK 指定最高码率。
 * @param is_test_downlink  是否探测下行带宽
 * @param expected_downlink_bitrate  期望下行带宽，单位：kbps<br>范围为 {0, [100-10000]}，其中， `0` 表示由 SDK 指定最高码率。
 * @return 开启通话前网络探测结果，详见 ByteRTCNetworkDetectionStartReturn{@link #ByteRTCNetworkDetectionStartReturn}
 * @notes  <br>
 *       + 成功调用本接口后，会在 3s 内收到一次 rtcEngine:onNetworkDetectionResult:quality:rtt:lostRate:bitrate:jitter:{@link #ByteRTCAudioDelegate#rtcEngine:onNetworkDetectionResult:quality:rtt:lostRate:bitrate:jitter:} 回调，此后每 2s 会收到一次该回调，通知探测结果；  <br>
 *       + 若探测停止，则会收到一次 rtcEngine:onNetworkDetectionStopped:{@link #ByteRTCAudioDelegate#rtcEngine:onNetworkDetectionStopped:} 通知探测停止。
 */
- (ByteRTCNetworkDetectionStartReturn)startNetworkDetection:(bool)is_test_uplink
    uplinkBandwidth:(int)expected_uplink_bitrate downlink:(bool)is_test_downlink
    downlinkBandwidth:(int)expected_downlink_bitrate;
/** 
 * @type api
 * @region 通话前网络探测
 * @brief 停止通话前网络探测
 * @notes  <br>
 *       调用本接口后，会收到一次 rtcEngine:onNetworkDetectionStopped:{@link #ByteRTCAudioDelegate#rtcEngine:onNetworkDetectionStopped:} 通知探测停止。
 */
- (void)stopNetworkDetection;

/** 
 * @type api
 * @region 云代理
 * @brief 开启云代理
 * @param cloudProxiesInfo 云代理服务器信息列表。参看 ByteRTCCloudProxyInfo{@link #ByteRTCCloudProxyInfo}。
 * @notes  <br>
 *        + 在加入房间前调用此接口  <br>
 *        + 在开启云代理后，进行通话前网络探测 <br>
 *        + 开启云代理后，并成功链接云代理服务器后，会收到 rtcEngine:onCloudProxyConnected:{@link #ByteRTCAudioDelegate#rtcEngine:onCloudProxyConnected:}。<br>
 *        + 要关闭云代理，调用 stopCloudProxy{@link #ByteRTCAudio#stopCloudProxy}。
 */
- (void)startCloudProxy:(NSArray <ByteRTCCloudProxyInfo *> * _Nullable)cloudProxiesInfo;
/** 
 * @type api
 * @region 云代理
 * @brief 关闭云代理
 * @notes 要开启云代理，调用 startCloudProxy:{@link #ByteRTCAudio#startCloudProxy:}
 */
- (void)stopCloudProxy;
/** 
 * @type api
 * @brief 通过 NTP 协议，获取网络时间。
 * @return 网络时间。参看 ByteRTCNetworkTimeInfo{@link #ByteRTCNetworkTimeInfo}。
 * @notes <br>
 *        + 第一次调用此接口会启动网络时间同步功能，并返回 `0`。同步完成后，会收到 rtcEngineOnNetworkTimeSynchronized:{@link #ByteRTCAudioDelegate#rtcEngineOnNetworkTimeSynchronized:}，此后，再次调用此 API，即可获取准确的网络时间。
 *        + 在合唱场景下，合唱参与者应在相同的网络时间播放背景音乐。
 */
- (ByteRTCNetworkTimeInfo *_Nonnull)getNetworkTimeInfo;
/** 
 * @type api
 * @brief 在听众端，设置订阅的所有远端音频流精准对齐后播放。
 * @param streamKey 作为对齐基准的远端音频流。参看 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}。<br>
 *                  一般选择主唱的音频流。<br>
 *                  你必须在收到 rtcRoom:onUserPublishStream:{@link #ByteRTCAudioRoomDelegate#rtcRoom:onUserPublishStream:}，确认此音频流已发布后，调用此 API。
 * @param mode 是否对齐，默认不对齐。参看 ByteRTCAudioAlignmentMode{@link #ByteRTCAudioAlignmentMode}。
 * @notes <br>
 *        + 你必须在实时合唱场景下使用此功能。在加入房间时，所有人应设置 ByteRTCRoomProfile{@link #ByteRTCRoomProfile} 为 `ByteRTCRoomProfileChorus`。<br>
 *        + 订阅的所有远端流必须通过 startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} 开启了背景音乐混音，并将 ByteRTCAudioMixingConfig{@link #ByteRTCAudioMixingConfig} 中的 `syncProgressToRecordFrame` 设置为 `true`。<br>
 *        + 如果订阅的某个音频流延迟过大，可能无法实现精准对齐。<br>
 *        + 合唱的参与者不应调用此 API，因为调用此 API 会增加延迟。如果希望从听众变为合唱参与者，应关闭对齐功能。
 */
- (void)setAudioAlignmentProperty:(ByteRTCRemoteStreamKey * _Nonnull)streamKey
           withMode:(ByteRTCAudioAlignmentMode)mode;

@end
