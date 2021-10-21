/*
 * Copyright (c) 2020 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngine Room
*/

#import <CoreMedia/CMTime.h>
#import <UIKit/UIKit.h>
#import "ByteRTCDefines.h"

@class ByteRTCRoom;

@protocol ByteRTCRoomDelegate <NSObject>
@optional

/**
 * @hidden
 * @type callback
 * @region 房间管理
 * @author shenpengliang
 * @brief 加入房间的回调。此回调表示用户调用JoinRoom的结果，根据错误码判断成功失败以及区别是否为重连  <br>
 *        本地用户加入房间成功后，在本地网络状况不佳的情况下，SDK 可能会与服务器失去连接。此时 SDK
 * 将会自动重连，并在重连成功通过此回调事件通知用户重连成功。  <br>
 * @param rtcRoom  ByteRTCRoom 对象。  <br>
 * @param roomId 房间 ID 。本地用户加入的房间的房间 ID 。  <br>
 * @param uid 用户ID 。本地用户的用户ID 。  <br>
 * @param joinType 本次回调属于加入房间的类型 0 表示用户调用joinRoom 1表示因网络原因掉线重连。 <br>
 * @param elapsed 连接耗时。本地用户从开始join到成功所经历的时间间隔，单位为 ms 。  <br>
 * @param errorCode 用户加入房间回调的状态码，0 为成功，非0 表示失败。<br>
 *        具体原因参考错误码 ErrorCode{@link #ErrorCode}以及 WarningCode{@link #WarningCode}  <br>
 */

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom
    onJoinRoomResult:(NSString *_Nonnull)roomId
             withUid:(nonnull NSString *)uid
           errorCode:(NSInteger)errorCode
            joinType:(NSInteger)joinType
             elapsed:(NSInteger)elapsed;

/**
 * @hidden
 * @type callback
 * @region 房间管理
 * @author shenpengliang
 * @brief 离开房间成功回调。  <br>
 *        用户调用 LeaveChannel{@link #LeaveChannel} 方法后，SDK
 * 会停止所有的发布订阅流，并释放所有通话相关的音视频资源。SDK 完成所有的资源释放后通过此回调通知用户。  <br>
 *        离开房间结束通话后，如果 App 需要使用系统音视频设备，则建议在收到此回调后再初始化音视频设备，否则可能由于
 * SDK 占用了导致 App 初始化音视频设备失败。  <br>
 * @param rtcRoom  ByteRTCRoom 对象。  <br>
 * @param stats 本次通话的统计数据，详见数据结构 ByteRTCRoomStats{@link #ByteRTCRoomStats} 。  <br>
 * @notes  <br>
 *       + 用户调用 LeaveRoom{@link #LeaveRoom} 方法离开房间后，如果立即调用 DestroyRtcEngine{@link
 * #DestroyRtcEngine} 方法销毁 RTC 引擎，则将无法收到此回调事件。  <br>
 */
- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onLeaveRoomWithStats:(ByteRTCRoomStats *_Nonnull)stats;

/**
 * @hidden
 * @type callback
 * @region 房间管理
 * @author shenpengliang
 * @brief SDK 发生警告回调。  <br>
 *        SDK 内部遇到可恢复错误时，在尝试自动恢复的同时，会通过此回调通知用户。此回调事件仅用做通知。  <br>
 * @param rtcRoom  ByteRTCRoom 对象。  <br>
 * @param warningCode 警告码，详见枚举类型 ByteRTCWarningCode{@link #ByteRTCWarningCode} 。  <br>
 */

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onRoomWarning:(ByteRTCWarningCode)warningCode;

/**
 * @hidden
 * @type callback
 * @region 房间管理
 * @author shenpengliang
 * @brief SDK 发生错误回调。  <br>
 *        SDK 内部遇到不可恢复错误时，会通过此回调通知 App，需要 App 根据错误码进行操作或提示用户。  <br>
 * @param rtcRoom  ByteRTCRoom 对象。  <br>
 * @param errorCode 错误码，详见枚举类型 ByteRTCErrorCode{@link #ByteRTCErrorCode} 。  <br>
 */

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onRoomError:(ByteRTCErrorCode)errorCode;

/**
 * @hidden
 * @type callback
 * @region 音频事件回调
 * @author wangjunzheng
 * @brief 提示房间内所有用户发送音量的回调。
 * @param rtcRoom  ByteRTCRoom 对象。  <br>
 * @param speakers
 *        房间内所有用户 ID, 以及对应的发送音量。参见：ByteRTCAudioVolumeInfo{@link #ByteRTCAudioVolumeInfo}。
 * @param [in] totalRemoteVolume 房间内所有音频流的总音量，取值范围是：[0,255]
 * @notes 本回调默认不开启。你可以通过调用 SetAudioVolumeIndicationInterval{@link #IRtcRoom#SetAudioVolumeIndicationInterval} 开启。  <br>
 */

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom
    onAudioVolumeIndication:(NSArray<ByteRTCAudioVolumeInfo *> *_Nonnull)speakers
                              totalRemoteVolume:(NSInteger)totalRemoteVolume;

/**
 * @hidden
 * @type callback
 * @region 视频管理
 * @brief 用户加入房间成功后，每 2s 会收到一次房间内统计信息的回调。
 * @param rtcRoom  ByteRTCRoom 对象。  <br>
 * @param stats 当前 ByteRTCRoom 统计数据，详见：ByteRTCRoomStats{@link #ByteRTCRoomStats}
 */

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onRoomStats:(ByteRTCRoomStats *_Nonnull)stats;

/**
 * @hidden
 * @type callback
 * @region 数据统计
 * @author liuzhiqiang.avcoder
 * @brief 通话中本地音视频流的统计信息以及网络状态的回调。
 *        该回调描述本地设备发送音视频流的统计信息，每 2 秒触发一次。
 * @param rtcRoom  ByteRTCRoom 对象。  <br>
 * @param stats  当前房间本地流数据统计。 详见：ByteRTCLocalStreamStats{@link #ByteRTCLocalStreamStats} <br>
 */

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onLocalStreamStats:(ByteRTCLocalStreamStats *_Nonnull)stats;

/**
 * @hidden
 * @type callback
 * @region 数据统计
 * @author liuzhiqiang.avcoder
 * @brief 通话中远端音视频流的统计信息以及网络状态的回调。
 *        该回调描述远端设备发送音视频流的统计信息，每 2 秒触发一次。
 * @param rtcRoom  ByteRTCRoom 对象。  <br>
 * @param stats  当前房间本地流数据统计。 详见：ByteRTCRemoteStreamStats{@link #ByteRTCRemoteStreamStats} <br>
 */

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onRemoteStreamStats:(ByteRTCRemoteStreamStats *_Nonnull)stats;

/**
 * @hidden
 * @type callback
 * @region 房间管理
 * @author shenpengliang
 * @brief 远端用户加入房间回调。  <br>
 *        此回调用于提示房间中有新用户加入。如果本地用户已经在房间中，有新的远端用户加入时，SDK
 * 通过此回调方法通知房间中有新用户加入；如果用户加入房间前，房间中已有其他用户，加入房间后用户也会收到这些已在房间中的远端用户的加入房间回调。
 * <br> 回调的具体触发时机如下：  <br>
 *        1.远端的房间模式为通信模式的用户或房间模式为其他模式的主播、观众角色的用户，调用 JoinChannel{@link
 * #JoinChannel} 方法加入房间。  <br>
 *        2.远端的房间模式为通信模式的用户或房间模式为其他模式的主播、观众角色的用户，在断网后重连入房间。  <br>
 *        3.远端已在房间中的房间模式为直播、游戏或云游戏模式的静默观众角色的用户，调用 SetClientRole{@link
 * #SetClientRole} 方法将用户角色切换至主播或观众。  <br>
 *        4.本地用户加入房间时，会收到已在房间中的远端的房间模式为通信模式的用户或房间模式为其他模式的主播、观众角色的用户的加入房间回调。
 * <br>
 * @param rtcRoom  ByteRTCRoom 对象。  <br>
 * @param userInfo 用户信息 。新加入的远端用户的用户ID以及在房间内需要透传的信息 。  <br>
 * @param elapsed  保留字段
 * <br>
 */

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onUserJoined:(ByteRTCUserInfo *_Nonnull)userInfo elapsed:(NSInteger)elapsed;

/**
 * @hidden
 * @type callback
 * @region 房间管理
 * @author shenpengliang
 * @brief 远端用户离开房间回调。  <br>
 *        此回调用于提示房间中有远端用户离开。用户离开房间的原因有两个，即用户主动调用 LeaveChannel{@link #LeaveChannel} 方法离开房间和超时掉线。  <br>
 *        回调的具体触发时机如下：  <br>
 *        1.远端的房间模式为通信模式的用户或房间模式为其他模式的主播、观众角色的用户，调用 LeaveChannel{@link #LeaveChannel} 方法离开房间。用户离开的原因为 kUserOfflineReasonQuit{@link #kUserOfflineReasonQuit}。  <br>
 *        2.远端已在房间中的房间模式为直播、游戏或云游戏模式的主播、观众角色的用户调用 SetClientRole{@link #SetClientRole} 方法将用户角色切换至静默观众。用户离开的原因为 kUserOfflineReasonQuit{@link #kUserOfflineReasonQuit}。  <br>
 *        3.远端的房间模式为通信模式的用户或房间模式为其他模式的主播、观众角色的用户，断网且一直未恢复。用户离开的原因为 kUserOfflineReasonDropped{@link #kUserOfflineReasonDropped}。  <br>
 * @param rtcRoom  ByteRTCRoom 对象。  <br>
 * @param uid 用户ID 。离开房间的远端用户的用户ID 。  <br>
 * @param reason 用户离开的原因，详见枚举类型 ByteRTCUserOfflineReason{@link #ByteRTCUserOfflineReason} 。  <br>
 */

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onUserLeave:(NSString *_Nonnull)uid reason:(ByteRTCUserOfflineReason)reason;

/**
 * @hidden
 * @type callback
 * @region 音频事件回调
 * @author wangjunzheng
 * @brief 当房间内用户调用 MuteAllRemoteAudio{@link #IRtcRoom#MuteAllRemoteAudio}，
 *        改变接收所有远端音频流的状态时, 房间内其他用户收到这个回调。
 * @param rtcRoom  ByteRTCRoom 对象。  <br>
 * @param uid 改变接收状态的用户 ID
 * @param muteState 接收状态，详见：ByteRTCMuteState{@link #ByteRTCMuteState}
 */

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onMuteAllRemoteAudio:(NSString *_Nonnull)uid muteState:(ByteRTCMuteState)muteState;

/**
 * @hidden
 * @type callback
 * @region 视频管理
 * @brief 房间内用户暂停/恢复接收所有视频流时，房间内其他用户收到此回调。参看 MuteAllRemoteVideo{@link #MuteAllRemoteVideo}。
 * @param rtcRoom  ByteRTCRoom 对象。  <br>
 * @param uid 暂停/恢复接收视频流的用户 ID。
 * @param muteState 暂停/恢复接收视频流。参看 ByteRTCMuteState{@link #ByteRTCMuteState}。
 */

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onMuteAllRemoteVideo:(NSString *_Nonnull)uid withMuteState:(ByteRTCMuteState)muteState;

/**
 * @hidden
 * @type callback
 * @region 音频事件回调
 * @author wangjunzheng
 * @brief 房间内某用户调用 MuteLocalAudio{@link #MuteLocalAudio}
 *        改变本地音频发送状态时，房间内其他用户会收到此回调。
 * @param rtcRoom  ByteRTCRoom 对象。  <br>
 * @param [in] uid 改变本地音频发送状态的用户 ID
 * @param [in] muteState 发送状态，参看 ByteRTCMuteState{@link #ByteRTCMuteState}
 */
- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onUserMuteAudio:(NSString *_Nonnull)uid muteState:(ByteRTCMuteState)muteState;

/**
 * @hidden
  * @deprecated
  * @type callback
  * @region 音频事件回调
  * @author wangjunzheng
  * @brief 远端用户开启/关闭音频设备采集回调
  *         提示有远端用户已开启/关闭音频设备采集，该回调由远端用户调用 enableLocalAudio:{@link #enableLocalAudio:} 方法触发
  * @param rtcRoom ByteRTCRoom对象
  * @param enabled YES: 该用户开启了音频设备采集；NO: 该用户关闭了音频设备采集
  * @param uid 远端用户ID
  *       + 该接口已废弃，请使用 onUserStartAudioCapture{@link #onUserStartAudioCapture} 以及 onUserStopAudioCapture{@link #onUserStopAudioCapture} <br>
 */

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom didLocalAudioEnabled:(BOOL)enabled byUid:(NSString *_Nonnull)uid;


/**
 * @hidden
 * @type callback
 * @region 音频事件回调
 * @author wangjunzheng
 * @brief 远端用户开启/关闭音频设备采集回调
 *         提示有远端用户已开启/关闭音频设备采集，该回调由远端用户调用 startAudioCapture:{@link #startAudioCapture:} 方法触发
 * @param rtcRoom ByteRTCRoom对象
 * @param userId 远端用户ID
 */
- (void)rtcRoom:(ByteRTCRoom * _Nonnull)rtcRoom onUserStartAudioCapture:(NSString *_Nonnull)userId;



/**
 * @type callback
 * @region 音频事件回调
 * @author wangjunzheng
 * @brief 远端用户开启/关闭音频设备采集回调
 *         提示有远端用户已开启/关闭音频设备采集，该回调由远端用户调用 stopAudioCapture:{@link #stopAudioCapture:} 方法触发
 * @param rtcRoom ByteRTCRoom对象
 * @param userId 远端用户ID
 */

- (void)rtcRoom:(ByteRTCRoom * _Nonnull)rtcRoom onUserStopAudioCapture:(NSString *_Nonnull)userId;

/**
 * @hidden
 * @type callback
 * @region 音频事件回调
 * @author wangjunzheng
 * @brief 本地采集到第一帧音频帧时，收到该回调
 * @param rtcRoom  ByteRTCRoom 对象。  <br>
 * @param streamIndex 音频流属性, 参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 */

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onFirstLocalAudioFrame:(ByteRTCStreamIndex) streamIndex;

/**
 * @hidden
 * @type callback
 * @region 音频事件回调
 * @author wangjunzheng
 * @brief 接收到来自远端某音频流的第一帧时，收到该回调。
 * @param rtcRoom  ByteRTCRoom 对象。  <br>
 * @param key 远端音频流信息, 详见 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
 * @notes 用户刚收到房间内每一路音频流时，都会收到该回调。
 */

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onFirstRemoteAudioFrame:(ByteRTCRemoteStreamKey * _Nonnull)key;

/**
 * @hidden
 * @type callback
 * @region 房间管理
 * @author shenpengliang
 * @brief 用户加入房间时，会收到此回调，包含房间中所有已发布的流。 <br>
 *        房间内的用户发布新的音视频流时，房间内的其他用户会收到此回调。  <br>
 * @param rtcRoom  ByteRTCRoom 对象。  <br>
 * @param stream 流属性，参看 ByteRTCStream{@link #ByteRTCStream} 。  <br>
 */

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onStreamAdd:(id<ByteRTCStream> _Nonnull)stream;

/**
 * @hidden
 * @type callback
 * @region 房间管理
 * @author shenpengliang
 * @brief 房间内的远端用户停止发布音视频流时，本地用户会收到此回调。
 * @param rtcRoom  ByteRTCRoom 对象。  <br>
 * @param uid 远端用户ID
 * @param stream 流的属性。参看 ByteRTCStream{@link #ByteRTCStream} 。
 * @param reason 远端流移除的原因。参看 StreamRemoveReason{@link #StreamRemoveReason} 。
 */

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom
    didStreamRemoved:(NSString *_Nonnull)uid
              stream:(id<ByteRTCStream> _Nonnull)stream
              reason:(ByteRTCStreamRemoveReason)reason;

/**
 * @hidden
 * @type callback
 * @region 房间管理
 * @author shenpengliang
 * @brief 当订阅一个流成功的时候回调该事件
 *       当更新流的内容时比如增加或者减少音视频流成功更新时也会回调该事件
 * @param rtcRoom  ByteRTCRoom 对象。  <br>
 * @param state
 *       订阅流的结果，详见：{@link #ByteRTCSubscribeState}
 * @param userId
 *       用户的标识
 * @param info
 *       流的属性，详见：{@link #ByteRTCSubscribeConfig}
 */

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom
    onStreamSubscribed:(ByteRTCSubscribeState)state
                userId:(NSString *_Nonnull)userId
       subscribeConfig:(ByteRTCSubscribeConfig *_Nonnull)info;

/**
 * @hidden
 * @type callback
 * @region 房间管理
 * @author shenpengliang
 * @brief 当发布流成功的时候回调该事件
 * @param rtcRoom  ByteRTCRoom 对象。  <br>
 * @param userId 用户ID
 * @param isScreen 该流是否是屏幕流
 *
 */

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onStreamPublishSuccess:(NSString *_Nonnull)userId isScreen:(BOOL)isScreen;

/**
 * @hidden
 * @type callback
 * @region 流消息
 * @brief 接收到房间内广播消息的回调。
 * @param rtcRoom  ByteRTCRoom 对象。  <br>
 * @param uid 消息发送者 ID
 * @param message 收到的消息内容
 * @notes
 *        1.同一房间内其他用户调用 SendRoomMessage{@link #IRtcRoom#SendRoomMessage} 发送广播消息时会收到该回调。
 */

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onRoomMessageReceived:(NSString *_Nonnull)uid
        message:(NSString *_Nonnull)message;

/**
 * @hidden
 * @type callback
 * @region 流消息
 * @brief 接收到房间内二进制广播消息的回调。
 * @param rtcRoom  ByteRTCRoom 对象。  <br>
 * @param uid 消息发送者 ID
 * @param message 收到的二进制消息内容
 * @notes
 *        1.同一房间内其他用户调用 SendRoomBinaryMessage{@link #IRtcRoom#SendRoomBinaryMessage} 发送二进制广播消息时会收到该回调。
 */

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onRoomBinaryMessageReceived:(NSString *_Nonnull)uid
        message:(NSData *_Nonnull)message;

/**
 * @hidden
 * @type callback
 * @region 流消息
 * @brief 点对点消息回调。接收到同一房间内 uid 所属用户发来消息时触发。
 * @param rtcRoom  ByteRTCRoom 对象。  <br>
 * @param uid  <br>
 *        消息发送者 ID 。
 * @param message  <br>
 *        收到的消息内容。
 * @notes  <br>
 *        + 同一房间内其他用户调用 SendUserMessage{@link #IRtcRoom#SendUserMessage} 发送消息给本地用户时会收到该回调。
 */

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom
    onUserMessageReceived:(NSString *_Nonnull)uid
               message:(NSString *_Nonnull)message;

/**
 * @hidden
 * @type callback
 * @region 流消息
 * @brief 接收到同一房间内 uid 所属用户发来二进制消息的回调。
 * @param rtcRoom  ByteRTCRoom 对象。  <br>
 * @param uid 消息发送者 ID
 * @param message 收到的二进制消息内容
 * @notes  <br>
 *        + 同一房间内其他用户调用 SendUserBinaryMessage{@link #IRtcRoom#SendUserBinaryMessage} 发送消息给本地用户时会收到该回调。
 */

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom
    onUserBinaryMessageReceived:(NSString *_Nonnull)uid
               message:(NSData *_Nonnull)message;

/**
 * @hidden
 * @type callback
 * @region 流消息
 * @brief 当调用 SendUserMessage{@link #IRtcRoom#SendUserMessage} 函数发送消息后，回调此条消息的发送结果（反馈）。
 * @param rtcRoom  ByteRTCRoom 对象。  <br>
 * @param msgid 本条消息的 ID
 * @param error 消息发送结果，详见 ByteRTCUserMessageSendResult{@link #ByteRTCUserMessageSendResult}
 */

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onUserMessageSendResult:(int64_t)msgid error:(ByteRTCUserMessageSendResult)error;

/**
 * @hidden
 * @type callback
 * @region 流消息
 * @brief 当调用 SendRoomMessage{@link #IRtcRoom#SendRoomMessage} 函数发送消息后，回调此条消息的发送结果（反馈）。
 * @param rtcRoom  ByteRTCRoom 对象。  <br>
 * @param msgid 本条消息的 ID
 * @param error 消息发送结果，详见 ByteRTCRoomMessageSendResult{@link #ByteRTCRoomMessageSendResult}
 */

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onRoomMessageSendResult:(int64_t)msgid error:(ByteRTCRoomMessageSendResult)error;

/**
 * @hidden
 * @type callback
 * @region CDN推流
 * @author shenpengliang
 * @brief 直播推流转码状态回调。  <br>
 *         用户调用 enableLiveTranscoding:{@link #enableLiveTranscoding:} 方法启动直播推流转码功能后，直播推流转码功能启动成功或失败时、推流过程中发生错误时，SDK 通过此回调通知用户对应的状态事件。  <br>
 *         回调事件为错误状态事件时，App 需根据功能状态码的处理建议做对应的处理，如通知用户或重试等。  <br>
 * @param rtcRoom ByteRTCRoom 对象。  <br>
 * @param url 推流地址。直播推流的地址，为 URL 地址。  <br>
 * @param errorCode 直播推流转码功能状态码，详见枚举类型 ByteRTCTranscodingError{@link #ByteRTCTranscodingError} 。  <br>
 */
- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onLiveTranscodingResult:(NSString *_Nonnull)url errorCode:(ByteRTCTranscodingError)errorCode;

/**
 * @hidden
 * @type callback
 * @region 视频管理
 * @brief 第一帧本地采集的视频/屏幕共享画面在本地视图渲染完成时，收到此回调。
 * @param rtcRoom ByteRTCRoom 对象。  <br>
 * @param streamIndex 流属性。参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}。
 * @param frameInfo 视频信息。参看 ByteRTCVideoFrameInfo{@link #ByteRTCVideoFrameInfo}。
 */

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onFirstLocalVideoFrameCaptured:(ByteRTCStreamIndex)streamIndex withFrameInfo:(ByteRTCVideoFrameInfo *_Nonnull)frameInfo;

/**
 * @hidden
 * @type callback
 * @region 视频管理
 * @brief 本地视频大小或旋转配置发生改变时，收到此回调。
 * @param rtcRoom ByteRTCRoom 对象。  <br>
 * @param streamIndex 流属性。参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}。
 * @param frameInfo 视频信息。参看 ByteRTCVideoFrameInfo{@link #ByteRTCVideoFrameInfo}。
 */

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom
    onLocalVideoSizeChanged:(ByteRTCStreamIndex)streamIndex
                     withFrameInfo:(ByteRTCVideoFrameInfo *_Nonnull)frameInfo;

/**
 * @hidden
 * @type callback
 * @region 视频管理
 * @brief 远端视频大小或旋转配置发生改变时，房间内订阅此视频流的用户会收到此回调。
 * @param rtcRoom ByteRTCRoom 对象。  <br>
 * @param streamKey 远端流信息。参看 ByteRTCRemoteStreamKey{@link #RemoteStreamKey}。
 * @param frameInfo 视频帧信息。参看 ByteRTCVideoFrameInfo{@link #ByteRTCVideoFrameInfo}。
 */

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom
    onRemoteVideoSizeChanged:(ByteRTCRemoteStreamKey *_Nonnull)streamKey
                     withFrameInfo:(ByteRTCVideoFrameInfo *_Nonnull)frameInfo;

/**
 * @hidden
 * @type callback
 * @region 视频管理
 * @brief 第一帧远端视频流在视图上渲染成功后，收到此回调。
 * @param rtcRoom ByteRTCRoom 对象。  <br>
 * @param streamKey 远端流信息。参看 ByteRTCRemoteStreamKey{@link #RemoteStreamKey}。
 * @param frameInfo 视频帧信息。参看 ByteRTCVideoFrameInfo{@link #ByteRTCVideoFrameInfo}。
 */

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom
    onFirstRemoteVideoFrameRendered:(ByteRTCRemoteStreamKey *_Nonnull)streamKey
                      withFrameInfo:(ByteRTCVideoFrameInfo *_Nonnull)frameInfo;

/**
 * @hidden
 * @type callback
 * @region 视频管理
 * @brief 房间内用户暂停/恢复发送视频流时，房间内其他用户()收到此回调。参看 MuteLocalVideoStream{@link #MuteLocalVideoStream}。
 * @param rtcRoom ByteRTCRoom 对象。  <br>
 * @param uid 暂停/恢复发送视频流的用户 ID。
 * @param mute 暂停/恢复发送视频流。参看 ByteRTCMuteState{@link #ByteRTCMuteState}。
 */

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onUserMuteVideo:(NSString *_Nonnull)uid withMuteState:(ByteRTCMuteState)muteState;
/**
 * @hidden
 * @type callback
 * @region 视频管理
 * @brief 远端用户开启本地视频采集时回调该事件，当远端用户调用 startVideoCapture{@link #startVideoCapture} 时，其他用户会触发此回调。
 * @param rtcRoom ByteRTCRoom 对象。  <br>
 * @param uid 用户ID，提示是哪个用户的视频流。
 * @notes 提示有其他用户启用了本地视频功能。
 */
- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onUserStartVideoCapture:(NSString *_Nonnull)uid;

 /**
  * @hidden
  * @type callback
  * @region 视频管理
  * @brief 远端用户关闭本地视频采集时回调该事件，当远端用户调用 startVideoCapture{@link #startVideoCapture} 时，其他用户会触发此回调。
  * @param rtcRoom ByteRTCRoom 对象。  <br>
  * @param uid 用户ID，提示是哪个用户的视频流。
  * @notes 提示有其他用户关闭了视频功能。
  */

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onUserStopVideoCapture:(NSString *_Nonnull)uid;

/**
 * @hidden
 * @type callback
 * @region 音频事件回调
 * @author wangjunzheng
 * @brief 本地音频的状态发生改变时，该回调通知当前的本地音频状态。
 * @param rtcRoom ByteRTCRoom 对象。  <br>
 * @param state 本地音频设备的状态，详见： ByteRTCLocalAudioStreamState{@link #ByteRTCLocalAudioStreamState}
 * @param error 本地音频状态改变时的错误码，详见：ByteRTCLocalAudioStreamError{@link #ByteRTCLocalAudioStreamError}
 */

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom
    onLocalAudioStateChanged:(ByteRTCLocalAudioStreamState)state
                     error:(ByteRTCLocalAudioStreamError)error;

/**
 * @hidden
 * @type callback
 * @region 音频事件回调
 * @author wangjunzheng
 * @brief 用户订阅来自远端的音频流状态发生改变时，会收到此回调，了解当前的远端音频流状态。
 * @param rtcRoom ByteRTCRoom 对象。  <br>
 * @param key 远端流信息, 参看 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
 * @param state 远端音频流状态，参看 ByteRTCRemoteAudioState{@link #ByteRTCRemoteAudioState}
 * @param reason 远端音频流状态改变的原因，参看 ByteRTCRemoteAudioStateChangeReason{@link #ByteRTCRemoteAudioStateChangeReason}
 */

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom
    onRemoteAudioStateChanged:(ByteRTCRemoteStreamKey * _Nonnull)key
                            state:(ByteRTCRemoteAudioState)state
                           reason:(ByteRTCRemoteAudioStateChangeReason)reason;

/**
 * @hidden
 * @type callback
 * @region 视频管理
 * @brief 本地视频流的状态发生改变时，收到该事件。
 * @param rtcRoom ByteRTCRoom 对象。  <br>
 * @param index 音视频属性, 参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param state 本地视频流状态，详见 ByteRTCLocalVideoStreamState{@link #ByteRTCLocalVideoStreamState}
 * @param error 本地视频状态改变时的错误码，详见 ByteRTCLocalVideoStreamError{@link #ByteRTCLocalVideoStreamError}
 */

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom
    onLocalVideoStateChanged:(ByteRTCStreamIndex)streamIndex
             withStreamState:(ByteRTCLocalVideoStreamState)state
             withStreamError:(ByteRTCLocalVideoStreamError)error;


/**
 * @hidden
 * @type callback
 * @region 视频管理
 * @brief 远端视频流的状态发生改变时，房间内的用户会收到该事件。
 * @param rtcRoom ByteRTCRoom 对象。  <br>
 * @param index 音视频属性, 参看 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
 * @param state 本地视频流状态，详见 ByteRTCRemoteVideoState{@link #ByteRTCRemoteVideoState}
 * @param error 本地视频状态改变时的错误码，详见 ByteRTCRemoteVideoStateChangeReason{@link #ByteRTCRemoteVideoStateChangeReason}
 */

- (void)rtcRoom:(ByteRTCRoom * _Nonnull)rtcRoom
    onRemoteVideoStateChanged:(ByteRTCRemoteStreamKey * _Nonnull)streamKey
               withVideoState:(ByteRTCRemoteVideoState)state
         withVideoStateReason:(ByteRTCRemoteVideoStateChangeReason)reason;

/**
 * @hidden
 * @type callback
 * @region 房间管理
 * @author shenpengliang
 * @brief 音频首帧发送状态改变回调
 * @param rtcRoom ByteRTCRoom 对象。  <br>
 * @param user 本地用户信息，详见 ByteRTCUser{@link #ByteRTCUser}
 * @param state 首帧发送状态，详见 ByteRTCFirstFrameSendState{@link #ByteRTCFirstFrameSendState}
 */

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onAudioFrameSendStateChanged:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFrameSendState)state;

/**
 * @hidden
 * @type callback
 * @region 房间管理
 * @author shenpengliang
 * @brief 视频首帧发送状态改变回调
 * @param rtcRoom ByteRTCRoom 对象。  <br>
 * @param user 本地用户信息，详见 ByteRTCUser{@link #ByteRTCUser}
 * @param state 首帧发送状态，详见 ByteRTCFirstFrameSendState{@link #ByteRTCFirstFrameSendState}
 */

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onVideoFrameSendStateChanged:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFrameSendState)state;

/**
 * @hidden
 * @type callback
 * @region 房间管理
 * @author shenpengliang
 * @brief 屏幕共享流视频首帧发送状态改变回调
 * @param rtcRoom ByteRTCRoom 对象。  <br>
 * @param user 本地用户信息，详见 ByteRTCUser{@link #ByteRTCUser}
 * @param state 首帧发送状态，详见 ByteRTCFirstFrameSendState{@link #ByteRTCFirstFrameSendState}
 */

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onScreenVideoFrameSendStateChanged:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFrameSendState)state;

/**
 * @hidden
 * @type callback
 * @region 房间管理
 * @author shenpengliang
 * @brief 音频首帧播放状态改变回调
 * @param rtcRoom ByteRTCRoom 对象。  <br>
 * @param user 远端用户信息，详见 ByteRTCUser{@link #ByteRTCUser}
 * @param state 首帧播放状态，详见 ByteRTCFirstFramePlayState{@link #ByteRTCFirstFramePlayState}
 */

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onAudioFramePlayStateChanged:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFramePlayState)state;

/**
 * @hidden
 * @type callback
 * @region 房间管理
 * @author shenpengliang
 * @brief 视频首帧播放状态改变回调
 * @param rtcRoom ByteRTCRoom 对象。  <br>
 * @param user 远端用户信息，详见 ByteRTCUser{@link #ByteRTCUser}
 * @param state 首帧播放状态，详见 ByteRTCFirstFramePlayState{@link #ByteRTCFirstFramePlayState}
 */

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onVideoFramePlayStateChanged:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFramePlayState)state;

/**
 * @hidden
 * @type callback
 * @region 房间管理
 * @author shenpengliang
 * @brief 屏幕共享流视频首帧播放状态改变回调
 * @param rtcRoom ByteRTCRoom 对象。  <br>
 * @param user 远端用户信息，详见 ByteRTCUser{@link #ByteRTCUser}
 * @param state 首帧播放状态，详见 ByteRTCFirstFramePlayState{@link #ByteRTCFirstFramePlayState}
 */

- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onScreenVideoFramePlayStateChanged:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFramePlayState)state;

@end

BYTERTC_APPLE_EXPORT @interface ByteRTCRoom : NSObject

@property(nonatomic, weak) id<ByteRTCRoomDelegate> _Nullable delegate;

#pragma mark - Core Methods


/**
 * @hidden
 * @type api
 * @region 房间管理
 * @author shenpengliang
 * @brief 销毁房间，该接口实现上会先执行退房操作，然后释放房间处理回调指针
 */

- (void)destroy;

/**
 * @hidden
 * @type api
 * @region 房间管理
 * @author shenpengliang
 * @brief 获取房间id
 */

- (NSString *_Nullable)getRoomId;

/**
 * @hidden
 * @type api
 * @region 房间管理
 * @author shenpengliang
 * @brief 设置 ByteRTCRoomDelegate{@link #ByteRTCRoomDelegate} 代理。
 *        通过设置事件句柄可以监听此 IRTCRoom{@link #IRTCRoom} 对象对应的房间的回调事件。
 * @param roomDelegate
 *        回调处理器，详见 IRTCRoomEventHandler{@link #IRTCRoomEventHandler}
 */

- (void)setRtcRoomDelegate:(id<ByteRTCRoomDelegate> _Nullable)roomDelegate;

/**
 * @hidden
 * @type api
 * @region 房间管理
 * @author shenpengliang
 * @brief 加入房间。用户调用此方法加入房间，在一个房间内的用户间可以相互通话。  <br>
 *         用户调用 createRtcRoom:{@link #createRtcRoom:} 创建 房间
 * 后，需调用此方法加入房间实现同其他用户进行音视频通话。如果用户调用此方法加入房间，则后续重复调用此方法加入相同的房间均会失败，才能加入相同房间。  <br> 用户调用此方法加入房间成功后，其他用户会收到 rtcRoom:onUserJoined:elapsed:{@link
 * #ByteRTCRoomDelegate#rtcRoom:onUserJoined:elapsed:} 回调通知。  <br>
 * @param token 动态密钥，用于对登录用户进行鉴权验证。  <br>
 *         进入房间需要携带 Token。测试时可使用控制台生成临时 Token ，正式上线需要使用密钥 SDK 在您的服务端生成并下发 Token 。  <br>
 * @param roomProfile
 *          房间模式，详见枚举类型 ByteRTCRoomProfile{@link #ByteRTCRoomProfile}
 * @param userInfo
 *         用户信息
 *         用户 ID，最大长度为128字节的非空字符串。支持的字符集范围为: <br>
 *             1. 26个大写字母 A ~ Z <br>
 *             2. 26个小写字母 a ~ z <br>
 *             3. 10个数字 0 ~ 9 <br>
 *             4. 下划线"_", at符"@", 减号"-" <br>
 *         透传信息，最大长度200字节 <br>
 * @return 方法调用结果。  <br>
 *         +  0: 成功  <br>
 *         + -1: roomId 为空，失败  <br>
 *         + -2: userId 为空，失败  <br>
 * @notes  <br>
 *        + 使用不同 App ID 的 App 是不能互通的。  <br>
 *        + 请务必保证生成 Token 使用的 App ID 和创建引擎时使用的 App ID 相同，否则会导致加入房间失败。  <br>
 *        + 用户加入房间成功后，在本地网络状况不佳的情况下，SDK 可能会与服务器失去连接，此时 SDK 将会自动重连。重连成功后，本地会收到 joinRoomByToken:token
 * roomId:roomProfile:userInfo:{@link #joinRoomByToken:token roomId:roomProfile:userInfo:} 回调通知。  <br>
 *        + 房间模式（房间模式参考 joinRoomByToken:token roomId:roomProfile:userInfo:{@link #joinRoomByToken:token
 * roomId:roomProfile:userInfo:}）为通话模式下的用户或直播、游戏、云游戏模式下用户角色（用户角色参考 setUserRole:{@link #setUserRole:}
 * ）为主播、观众的用户加入房间成功后，远端用户会收到 rtcRoom:onUserJoined:elapsed:{@link #ByteRTCRoomDelegate#rtcRoom:onUserJoined:elapsed:} 回调通知。
 * <br>
 *        + 同一个 App ID 的同一个房间内，每个用户的用户ID 必须是唯一的。如果两个用户的用户ID
 * 相同，则后加入房间的用户会将先加入房间的用户踢出房间，并且先加入房间的用户会收到 rtcRoom:onRoomError:{@link #ByteRTCRoomDelegate#rtcRoom:onUserJoined:elapsed:}
 * 回调通知，错误类型为重复登录 BRERR_DUPLICATE_LOGIN{@link #BRERR_DUPLICATE_LOGIN} 。  <br>
 */

- (int)joinRoomByToken:(NSString *_Nullable)token userInfo:(ByteRTCUserInfo *_Nonnull)userInfo roomProfile:(ByteRTCRoomProfile)roomProfile;


/**
 * @hidden
 * @type api
 * @region 房间管理
 * @author shenpengliang
 * @brief 设置用户角色。  <br>
 *         用户可通过设置用户角色，控制：1.是否发布音视频流；2.用户自身是否在房间中隐身。用户角色详见 ByteRTCUserRoleType{@link #ByteRTCUserRoleType} 枚举类型。
 * <br> 默认用户角色为主播角色 ByteRTCUserRoleTypeBroadcaster{@link #ByteRTCUserRoleTypeBroadcaster} 。  <br> 房间模式（通过joinRoomByToken:token
 * roomId:roomProfile:userInfo:{@link #joinRoomByToken:token
 * roomId:roomProfile:userInfo:}）为直播模式、游戏模式、云游戏模式时，设置用户角色生效。房间模式为通信模式时不区分用户角色。  <br>
 * @param role 用户角色，详见 ByteRTCUserRoleType{@link #ByteRTCUserRoleType} 枚举类型。  <br>
 * @return 方法调用结果。  <br>
 *         + YES: 方法调用成功  <br>
 *         +  NO: 方法调用失败  <br>
 * @notes  <br>
 *        + 在加入房间前，用户可调用此方法设置用户角色。加入房间后，用户也可通过此方法切换用户角色。  <br>
 *        + 用户在加入房间成功后调用该方法切换用户角色，调用成功后，远端用户会收到相应的回调通知：1.本地用户角色从静默观众切换至观众或主播时，远端用户会收到
 * rtcRoom:onUserJoined:elapsed:{@link #ByteRTCRoomDelegate#rtcRoom:onUserJoined:elapsed:}
 * 回调通知；2.本地用户角色从观众或主播切换至静默观众时，远端用户会收到 rtcRoom:didOfflineOfUid:reason:{@link
 * #ByteRTCRoomDelegate#rtcRoom:didOfflineOfUid:reason:} 回调通知。  <br>
 */
- (int)setUserRole:(ByteRTCUserRoleType)role;

/**
 * @hidden
 * @type api
 * @region 房间管理
 * @author shenpengliang
 * @brief 获取当前用户角色。  <br>
 * @return 当前用户角色，详见 ByteRTCUserRoleType{@link #ByteRTCUserRoleType} 枚举类型。  <br>
 */

- (ByteRTCUserRoleType)clientRole;

/**
 * @hidden
 * @type api
 * @region 房间管理
 * @author shenpengliang
 * @brief 离开房间。  <br>
 *         用户调用此方法离开房间，结束通话过程，释放所有通话相关的资源。  <br>
 *         调用 joinRoomByToken:token roomId:roomProfile:userInfo:{@link #joinRoomByToken:token roomId:roomProfile:userInfo:}
 * 方法加入房间后，在通话结束时必须调用此方法结束通话，否则无法开始下一次通话。无论当前是否在房间中，都可以调用此方法。重复调用此方法不会有负面影响。  <br>
 *         此方法是异步操作，调用返回时并没有真正退出房间。真正退出房间后，SDK 会执行调用此方法时传入的 Block 块。  <br>
 * @return 方法调用结果。  <br>
 *         +  0: 方法调用成功  <br>
 *         + <0: 方法调用失败  <br>
 * @notes  <br>
 *        + 通信模式下的用户和其他房间模式下的主播、 观众角色的用户离开房间后，远端用户会收到 rtcRoom:onUserLeave:reason:{@link
 */

- (int)leaveRoom;


/**
 * @hidden
 * @type api
 * @region 房间管理
 * @author shenpengliang
 * @brief 更新 Token。  <br>
 *         Token 有一定的有效期，当 Token 过期时，用户需调用此方法更新房间的 Token 信息。  <br>
 *         用户调用joinRoomByToken:token roomId:roomProfile:userInfo:{@link #joinRoomByToken:token roomId:roomProfile:userInfo:} 方法加入房间时，如果使用了过期的
 * Token 将导致加入房间失败，并会收到 rtcRoom:onJoinRoomResult:{@link #ByteRTCRoomDelegate#rtcRoom:onJoinRoomResult:} 回调通知，回调错误码为
 * BRERR_INVALID_TOKEN{@link #BRERR_INVALID_TOKEN} 。此时需要重新获取 Token ，并调用此方法更新 Token。  <br>
 * @param token 更新的动态密钥。Token 用于对登录用户进行鉴权验证。  <br>
 * @return 方法调用结果。  <br>
 *         +  0: 方法调用成功。  <br>
 *         + <0: 方法调用失败。  <br>
 * @notes <br>
 *        + 如果用户因 Token 过期导致加入房间失败，则调用此方法更新 Token 后 SDK 会自动重新加入房间，而不需要用户自己调用 joinRoomByToken:token
 * roomId:roomProfile:userInfo:{@link #joinRoomByToken:token roomId:roomProfile:userInfo:} 方法。  <br>
 *        + Token过期时，如果已经加入房间成功，则不会受到影响。Token 过期的错误会在下一次使用过期的 Token
 * 加入房间或由于本地网络状况不佳导致断网重连入房间时通知给用户。  <br>
 */

- (int)renewToken:(NSString *_Nullable)token;

/**
 * @hidden
 * @type api
 * @region 房间管理
 * @author shenpengliang
 * @brief 将本端音视频流发布到此房间。
 * @notes
 *        1.此方法仅支持在关闭自动发布功能时调用，用户可通过调用 EnableAutoPublish{@link #EnableAutoPublish}
 *          方法设置关闭自动发布。
 *        2.直播、游戏、云游戏房间模式下，此方法仅适用于角色为主播的用户。App 可以通过调用
 *          SetUserRole{@link #SetUserRole} 方法设置用户角色。
 *        3.目前 SDK 只支持用户同一时间发布一路音视频流。
 *        4.用户调用此方法成功发布音视频流后，房间中的其他用户将会收到 OnStreamAdd{@link #OnStreamAdd} 回调通知。
**/

- (int)publish;

/**
 * @hidden
 * @type api
 * @region 房间管理
 * @author shenpengliang
 * @brief 停止将本端音视频流发布到此房间。
 * @notes
 *        1.此方法仅支持在关闭自动发布功能时调用，用户可通过调用 EnableAutoPublish{@link #EnableAutoPublish}
 *        方法设置关闭自动发布。
 *        2.用户调用此方法停止发布音视频流后，房间中的其他用户将会收到 didStreamRemoved{@link
 *        #didStreamRemoved} 回调通知。
 */

- (int)unpublish;

/**
 * @hidden
 * @type api
 * @region 屏幕共享
 * @author zhangzhenyu.samuel
 * @brief 发布本地屏幕共享流到房间。
 * @param [in] paramters
 *        屏幕共享流编码参数，详见 ScreenParameters{@link #ScreenParameters}
 * @notes  <br>
 *       + 直播、游戏、云游戏房间模式下，此方法仅适用于角色为主播的用户。应用可以通过调用
 * SetUserRole{@link#SetUserRole} 方法设置用户角色。  <br>
         +调用此方法发布本端屏幕共享流后，用户还需要通过设置定时任务周期性调用 pushScreenCaptureFrame:time:rotation:{@link ByteRTCEngineKit#pushScreenCaptureFrame:time:rotation:} 方法，将需要发送的屏幕数据推送给 SDK。
 *       + 远端会收到 onFirstRemoteVideoFrameRendered{@link #ByteRTCRoomDelegate#onFirstRemoteVideoFrameRendered}
 * 、OnStreamAdd{@link#ByteRTCRoomDelegate#OnStreamAdd} 事件。  <br>
 *       + 该函数和 StartScreenCaptureByWindowId{@link#IRtcEngineLite#StartScreenCaptureByWindowId}
 * 、StartScreenCaptureByScreenRect{@link#IRtcEngineLite#StartScreenCaptureByScreenRect} 函数是互斥调用的，可在调用
 * UnpublishScreen{@link#IUnpublishScreen} 函数后调用上述函数。  <br>
 *       + 在收到 onFirstRemoteVideoFrameRendered{@link#ByteRTCRoomDelegate#onFirstRemoteVideoFrameRendered} 事件后通过调用
 * setRemoteScreenRenderer{@link #setRemoteScreenRenderer}
 * 函数来设置远端屏幕共享视图。  <br>
 *       + 本地可调用 SetupLocalScreen{@link #IRtcEngineLite#SetupLocalScreen} 或
 * SetLocalScreenRender{@link#IRtcEngineLite#SetLocalScreenRender} 函数设置本地屏幕共享视图。  <br>
 *       + 也可通过注册 RegisterVideoFrameObserver{@link#RegisterVideoFrameObserver} 视频回调对象，监听
 * OnLocalScreenFrame{@link #IVideoFrameObserver#OnLocalScreenFrame}本地屏幕视频回调事件和 OnRemoteScreenFrame{@link
 * #IVideoFrameObserver#OnRemoteScreenFrame}远端屏幕共享视频回调事件来获取原始数据。  <br>
 */

- (int)publishScreen:(ByteRTCScreenParam * _Nonnull)param;

/**
 * @hidden
 * @type api
 * @region 屏幕共享
 * @author zhangzhenyu.samuel
 * @brief 停止发布本地屏幕共享流到房间。
 * @notes 远端会收到 didStreamRemoved{@link #ByteRTCRoomDelegate#didStreamRemoved} 事件。
 */

- (int)unpublishScreen;

/**
 * @hidden
 * @type api
 * @region 房间管理
 * @author shenpengliang
 * @brief 订阅指定的房间内远端音视频流。  <br>
 *        关闭自动订阅功能，使用手动订阅模式时用户调用此方法按需订阅房间中的音视频流。  <br>
 *        此方法仅在关闭自动订阅功能时生效。用户需在加入房间前调用 enableAutoSubscribe{@link #enableAutoSubscribe}
 * 方法关闭自动订阅功能以使用手动订阅模式。  <br> 用户在自动订阅功能开启时调用此方法，SDK 不会订阅音视频流，并通过
 * onRoomWarning{@link #onRoomWarning} 回调通知用户订阅失败，回调警告码为
 * ByteRTCWarningCode{@link #ByteRTCWarningCode} 。  <br> 订阅流失败时，SDK
 * 会按失败原因回调 onRoomError{@link #onRoomError} 通知用户，具体错误可参考错误码 ByteRTCErrorCode{@link
 * #ErrorCode} 描述。  <br>
 * @param userId 指定订阅的远端用户的用户ID 。  <br>
 * @param info 选择订阅配置，详见数据结构 ByteRTCSubscribeConfig{@link #ByteRTCSubscribeConfig} 。  <br>
 * @notes  <br>
 *       + 此方法仅支持订阅当前房间中的远端音视频流。如果指定的流在当前房间内不曾存在，则 SDK 不会订阅。  <br>
 *       + 用户调用 JoinRoom{@link #JoinRoom} 方法加入房间后：1.当房间内有新的音视频流发布时，本地会收到
 * OnStreamAdd{@link #OnStreamAdd} 回调通知；2.当房间内音视频流停止发布时，本地会收到 didStreamRemoved{@link
 * #didStreamRemoved}
 * 回调通知。通过这两个回调用户可以获得当前房间中的音视频流信息，并在需要时调用此方法订阅该音视频流。  <br>
 */

- (int)subscribeStream:(NSString *_Nonnull)userId subscribeConfig:(ByteRTCSubscribeConfig *_Nonnull)info;

/**
 * @hidden
 * @type api
 * @region 房间管理
 * @author shenpengliang
 * @brief 停止订阅指定的房间内远端音视频流。  <br>
 *        关闭自动订阅功能，使用手动订阅模式时用户调用此方法停止订阅已订阅的音视频流。  <br>
 *        此方法仅在关闭自动订阅功能时生效。用户需在加入房间前调用 enableAutoSubscribe{@link #enableAutoSubscribe} 方法关闭自动订阅功能以使用手动订阅模式。  <br>
 * @param userId 指定停止订阅的远端音视频流的用户的ID。  <br>
 * @param isScreen 指定停止的流是不是屏幕流。  <br>
 * @notes  <br>
 *       + 不管是否订阅了指定的远端音视频流，都可以调用此方法停止订阅。停止订阅的 stream_id 无效或未订阅时，SDK不会做任何处理，没有负面影响。  <br>
 */

- (int)unSubscribeStream:(NSString *_Nonnull)userId isScreen:(BOOL)isScreen;

/**
 * @hidden
 * @type api
 * @region 房间管理
 * @author shenpengliang
 * @brief 设置订阅模式。  <br>
 *        用户调用此方法设置房间中音视频流的订阅模式。SDK 默认使用自动订阅模式。<br>
 *        如需开启手动订阅功能，建议在调用 JoinChannel{@link #JoinChannel} 方法加入房间前设置完成。  <br>
 * @param audioMode 音频流的订阅模式。详见枚举类型 ByteRTCSubscribeMode{@link #ByteRTCSubscribeMode}。  <br>
 * @param videoMode 视频流的订阅模式。详见枚举类型 ByteRTCSubscribeMode{@link #ByteRTCSubscribeMode}。  <br>
 * @notes  <br>
 *       + SDK 提供两种订阅模式：1.自动订阅模式，开启自动订阅功能时，SDK 自动帮助用户订阅房间中所有其他用户发布的音视频流；2.手动订阅模式，关闭自动订阅功能时，SDK不会自动订阅房间内的音视频流，只通过 OnStreamAdd{@link #OnStreamAdd} 和 didStreamRemoved{@link #didStreamRemoved} 回调通知用户当前所在房间中有哪些音视频流，由用户根据自己的需要调用 subscribeStream{@link #subscribeStream} 方法手动订阅其他用户发布的音视频流。  <br>
 *       + SDK 可以分别对音频/视频设置订阅模式。  <br>
 */

- (int)enableAutoSubscribe:(ByteRTCSubscribeMode)audioMode videoMode:(ByteRTCSubscribeMode)videoMode;

/**
 * @hidden
 * @type api
 * @region 音频管理
 * @author wangjunzheng
 * @brief 设置是否开启房间内音量提示。<br>
 *        如果开启，将以设置的时间间隔收到音量事件回调。无论房间内有无发言，都会收到回调。
 *        具体回调参看 OnAudioVolumeIndication{@link #IRTCRoomEventHandler#OnAudioVolumeIndication}
 * @param interval 收到音量提示回调的时间间隔  <br>
 *                + ≤ 0：禁用音量提示功能。  <br>
 *                + > 0：启用音量提示功能，并设置收到音量提示回调的时间间隔。单位为毫秒。<br>
 *                建议设置为大于等于 200 毫秒；小于 10 毫秒时，行为未定义。
 */

- (void)setAudioVolumeIndicationInterval:(NSInteger)interval;

/**
 * @hidden
 * @type api
 * @region 音频管理
 * @author wangjunzheng
 * @brief 设置对来自远端的所有音频流的接收状态。默认为接收。
 * @param muteState 接收状态。参看：ByteRTCMuteState{@link #ByteRTCMuteState}
 * @notes 本方法只影响本地是否接收远端音频流，并不影响远端音频设备的采集发送功能。
 */

- (void)muteAllRemoteAudio:(ByteRTCMuteState)muteState;

/**
 * @hidden
 * @type api
 * @region 音频管理
 * @author wangjunzheng
 * @brief 设置对来自远端指定用户的音频流的接收状态。默认为接收。
 * @param userId 指定远端用户的 ID
 * @param muteState 接收状态。参看：ByteRTCMuteState{@link #ByteRTCMuteState}
 * @notes 本方法只影响本地是否接收远端音频流，并不影响远端音频设备的采集发送功能。
 */

- (void)muteRemoteAudio:(NSString *_Nonnull)userId muteState:(ByteRTCMuteState)muteState;

/**
 * @hidden
 * @type api
 * @region 视频管理
 * @author liyi.000
 * @brief 设置是否播放所有远端视频流
 * @param  muteState 参看 ByteRTCMuteState{@link #ByteRTCMuteState}   <br>
 *       + true：停止播放  <br>
 *       + false：开启播放  <br>
 * @notes 本方法不影响远端视频采集和发送状态
 */

- (int)muteAllRemoteVideo:(ByteRTCMuteState)muteState;

/**
 * @hidden
 * @type api
 * @region 视频管理
 * @author liyi.000
 * @brief 设置是否播放远端视频流
 * @param uid 视频来源的远端用户 ID
 * @param  muteState 参看 ByteRTCMuteState{@link #ByteRTCMuteState}   <br>
 *       + true：停止播放  <br>
 *       + false：开启播放  <br>
 * @notes 本方法不影响远端视频采集和发送状态
 */

- (int)muteRemoteVideo:(NSString * _Nonnull)uid
                  mute:(ByteRTCMuteState)muteState;

/**
 * @hidden
 * @type api
 * @region CDN推流
 * @author shenpengliang
 * @brief 开启客户端合流,并传入合流参数和时间回调接收对象
 * @param transcoding 客户端合流参数。  <br>
 * @param observer 合流之后,接收音视频数据和事件的回调对象  <br>
 * @notes
 *        1.直播推流转码功能，会根据设置的视频视图布局和音频属性进行合流并推送合流到设置的 CDN。
 *        2.只有房间模式为直播模式，且用户角色为主播的用户才能调用此方法。
 */

- (int)startLiveTranscoding:(ByteRTCLiveTranscoding *_Nonnull)transcoding observer:(id<LiveTranscodingDelegate> _Nonnull)observer;

/**
 * @hidden
 * @type api
 * @region CDN推流
 * @author shenpengliang
 * @brief 停止直播推流转码。
 */

- (int)stopLiveTranscoding;

/**
 * @hidden
 * @type api
 * @region CDN推流
 * @author shenpengliang
 * @brief 设置画中画布局。该方法设置直播场景里的画中画布局。该方法仅适用于服务器端推流的场景。
 * @param transcoding 客户端合流参数。  <br>
 */

- (int)updateLiveTranscoding:(ByteRTCLiveTranscoding *_Nonnull)transcoding;

/**
 * @hidden
 * @type api
 * @region 视频管理
 * @author sunhang.io
 * @brief 设置来自指定远端用户 user_id 的视频渲染时，使用的视图，并设置渲染模式。 <br>
 *        你应在加入房间前，绑定视图。退出房间后，此设置失效。<br>
 *        如果需要解除某个用户的绑定视图，你可以把 view 设置为空。
 * @notes  <br>
 *       + 实际使用时，你可以在收到回调 OnUserJoined{@link #OnUserJoined} 或 onFirstRemoteVideoFrame{@link #onfirstremotevideoframe} 时获得远端用户 user_id。  <br>
 *       + 这两个回调的差别是：如果启用了视频录制功能，视频录制服务会作为一个哑客户端加入房间，因此其他客户端会收到对应的 OnUserJoined{@link #OnUserJoined} 回调；
 *       + 而不会收到 onFirstRemoteVideoFrameRendered{@link #onFirstRemoteVideoFrameRendered} 回调。你不应给录制的亚客户端绑定视图（因为它不会发送视频流）。
 * @param uid 视频来源的远端用户 ID。
 * @param streamIndex 视频流属性, 参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param canvas 视图信息和渲染模式，参看：ByteRTCVideoCanvas{@link #ByteRTCVideoCanvas}
 * @return  <br>
 *        + 0：成功  <br>
 *        + !0：失败  <br>
 */

- (int)setRemoteVideoCanvas:(NSString * _Nonnull)uid
                  withIndex:(ByteRTCStreamIndex)streamIndex
                 withCanvas:(ByteRTCVideoCanvas * _Nullable)canvas;

/**
 * @hidden
 * @type api
 * @region 自定义视频采集渲染
 * @author sunhang.io
 * @brief 设置特定远端用户的外部渲染器。
 * @param videoRenderer 外部渲染器，具体参照 ByteRTCVideoSinkProtocol{@link #ByteRTCVideoSinkProtocol}
 * @param roomId 房间ID
 * @param userId 用户ID
 * @notes 该方法绑定远程用户视频流的渲染器，如需解绑，设置为空即可。
 */

- (int)setRemoteVideoRenderer:(id<ByteRTCVideoSinkProtocol> _Nullable)videoRenderer
                    forRoomId:(NSString * _Nonnull)roomId
                    forUserId:(NSString * _Nonnull)userId;

/**
 * @hidden
 * @type api
 * @region 流消息
 * @author hanchenchen.c
 * @brief 给房间内指定的用户发送消息，返回这次发送消息的编号。  <br>
 *        调用该函数后会收到一次 OnUserMessageSendResult{@link #IRTCRoomEventHandler#OnUserMessageSendResult}
 *        回调，告知发送结果。
 * @param [in] userId  <br>
 *        指定用户 ID 。
 * @param [in] message  <br>
 *        发送的消息内容。
 * @return 这次发送消息的编号，从 1 开始递增。
 * @notes
 *      1.调用该函数后会收到一次OnUserMessageSendResult{@link
 * #ByteRTCRoomDelegate#OnUserMessageSendResult} 回调；
 *      2.若消息发送成功，则 uid 所指定的用户会收到
 * OnUserMessageReceived{@link #IRTCRoomEventHandler#OnUserMessageReceived} 回调。
 */

- (int64_t)sendUserMessage:(NSString *_Nonnull)userId message:(NSString *_Nonnull)message;

/**
 * @hidden
 * @type api
 * @region 流消息
 * @author hanchenchen.c
 * @brief 给房间内指定的用户发送二进制消息，返回这次发送消息的编号。
 * @param uid 指定用户 ID
 * @param message 发送的二进制消息内容
 * @return
 *      返回这次发送消息的编号，从 1 开始递增
 * @notes
 *      1.调用该函数后会收到一次 OnUserMessageSendResult{@link
 * #ByteRTCRoomDelegate#OnUserMessageSendResult} 回调；
 *      2.若消息发送成功，则 uid 所指定的用户会收到
 * OnUserBinaryMessageReceived{@link #IRTCRoomEventHandler#OnUserBinaryMessageReceived} 回调。
 */

- (int64_t)sendUserBinaryMessage:(NSString * _Nonnull)uid message:(NSData * _Nonnull)message;

/**
 * @hidden
 * @type api
 * @region 流消息
 * @author hanchenchen.c
 * @brief 给房间内的所有其他用户发送广播消息。
 * @param message 用户发送的广播消息
 * @notes
 *      1.调用该函数后会收到一次 OnRoomMessageSendResult{@link
 * #ByteRTCRoomDelegate#OnRoomMessageSendResult} 回调；
 *      2.同一房间内的其他用户会收到 OnRoomMessageReceived{@link
 * #ByteRTCRoomDelegate#OnRoomMessageReceived} 回调。
 */

- (int64_t)sendRoomMessage:(NSString *_Nonnull)message;

/**
 * @hidden
 * @type api
 * @region 流消息
 * @author hanchenchen.c
 * @brief 给房间内的所有其他用户发送广播消息。
 * @param message 用户发送的二进制广播消息
 * @notes
 *      1.调用该函数后会收到一次 OnRoomMessageSendResult{@link
 * #ByteRTCRoomDelegate#OnRoomMessageSendResult} 回调；
 *      2.同一房间内的其他用户会收到 OnRoomBinaryMessageReceived{@link
 * #ByteRTCRoomDelegate#OnRoomBinaryMessageReceived} 回调。
 */

- (int64_t)sendRoomBinaryMessage:(NSData *  _Nonnull)message;

/**
 * @hidden
 * @type api
 * @region 自定义视频采集渲染
 * @author sunhang.io
 * @brief 设置屏幕共享远端外部渲染器
 * @param videoRenderer 外部渲染器，具体参照 ByteRTCVideoSinkProtocol{@link #ByteRTCVideoSinkProtocol}
 * @param roomId 房间ID
 * @param userId 用户ID
 * @notes 该方法绑定远端用户屏幕共享流的渲染器，如需解绑，设置为空即可。
 */

- (int)setRemoteScreenRenderer:(id<ByteRTCVideoSinkProtocol> _Nullable)videoRenderer
                    forRoomId:(NSString * _Nonnull)roomId
                     forUserId:(NSString * _Nonnull)userId;

@end
