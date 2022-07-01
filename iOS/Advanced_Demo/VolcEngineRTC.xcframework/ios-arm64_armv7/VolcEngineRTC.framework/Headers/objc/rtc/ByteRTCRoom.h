/*
 * Copyright (c) 2020 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC Room
*/

#import <CoreMedia/CMTime.h>
#import <UIKit/UIKit.h>
#import "ByteRTCDefines.h"
#import "ByteRTCRangeAudio.h"
#import "ByteRTCSpatialAudio.h"

@class ByteRTCRoom;

/** 
 * @type callback
 * @brief 房间事件回调接口
 */
@protocol ByteRTCRoomDelegate <NSObject>
@optional

 /** 
  * @type callback
  * @region 多房间
  * @author shenpengliang
  * @brief 房间状态改变回调，加入房间、离开房间、发生房间相关的警告或错误时会收到此回调。
  * @param roomId 房间 ID。
  * @param uid 用户 ID。
  * @param state 房间状态码。  <br>
  *              + 0: 成功。  <br>
  *              + !0: 失败，具体原因参看 ByteRTCErrorCode{@link #ByteRTCErrorCode} 及 ByteRTCWarningCode{@link #ByteRTCWarningCode}。
  * @param extraInfo 额外信息。
  *                  `joinType`表示加入房间的类型，`0`为首次进房，`1`为重连进房。
  *                  `elapsed`表示加入房间耗时，即本地用户从调用 joinRoomByToken:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoomByToken:userInfo:roomConfig:} 到加入房间成功所经历的时间间隔，单位为 ms。
  */
 - (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom
    onRoomStateChanged:(NSString *_Nonnull)roomId
             withUid:(nonnull NSString *)uid
           state:(NSInteger)state
           extraInfo:(NSString *_Nonnull)extraInfo;

/** 
 * @type callback
 * @region 多房间
 * @author shenpengliang
 * @brief 流状态改变回调，发生流相关的警告或错误时会收到此回调。
 * @param roomId 房间 ID。
 * @param uid 用户 ID。
 * @param state 流状态码，参看 ByteRTCErrorCode{@link #ByteRTCErrorCode} 及 ByteRTCWarningCode{@link #ByteRTCWarningCode}。
 * @param extraInfo 附加信息，目前为空。
 */
- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom
   onStreamStateChanged:(NSString *_Nonnull)roomId
            withUid:(nonnull NSString *)uid
          state:(NSInteger)state
          extraInfo:(NSString *_Nonnull)extraInfo;

/** 
 * @hidden
 * @type callback
 * @region 多房间
 * @author shenpengliang
 * @brief 离开房间成功回调。  <br>
 *        用户调用 leaveRoom{@link #ByteRTCRoom#leaveRoom} 方法后，SDK 会停止所有的发布订阅流，并释放所有通话相关的音视频资源。SDK 完成所有的资源释放后通过此回调通知用户。  <br>
 * @param rtcRoom  ByteRTCRoom 对象。  <br>
 * @param stats 本次通话的统计数据，详见数据结构 ByteRTCRoomStats{@link #ByteRTCRoomStats} 。  <br>
 * @notes  <br>
 *       + 用户调用 leaveRoom{@link #ByteRTCRoom#leaveRoom} 方法离开房间后，如果立即调用 destroyEngine{@link #destroyEngine} 方法销毁 RTC 引擎，则将无法收到此回调事件。  <br>
 *       + 离开房间结束通话后，如果 App 需要使用系统音视频设备，则建议在收到此回调后再初始化音视频设备，否则可能由于 SDK 占用了导致 App 初始化音视频设备失败。  <br>
 */
- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onLeaveRoomWithStats:(ByteRTCRoomStats *_Nonnull)stats;

 /** 
  * @hidden
  * @deprecated since 341.1 by onRoomStateChanged and onStreamStateChanged
  * @type callback
  * @region 多房间
  * @author shenpengliang
  * @brief 发生警告回调。  <br>
  *        SDK 运行时出现了警告。SDK 通常会自动恢复，警告信息可以忽略。
  * @param rtcRoom ByteRTCRoom 对象。
  * @param warningCode 警告码，详见枚举类型 ByteRTCWarningCode{@link #ByteRTCWarningCode} 。
  */
 - (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onRoomWarning:(ByteRTCWarningCode)warningCode;

/** 
 * @hidden
 * @deprecated since 341.1 by onRoomStateChanged and onStreamStateChanged
 * @type callback
 * @region 多房间
 * @author shenpengliang
 * @brief 发生错误回调。  <br>
 *        SDK 运行时出现了错误。SDK 通常无法自动恢复，应用需要采取行动。
 * @param rtcRoom  ByteRTCRoom 对象。
 * @param errorCode 错误码，详见枚举类型 ByteRTCErrorCode{@link #ByteRTCErrorCode} 。
 */
- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onRoomError:(ByteRTCErrorCode)errorCode;

/** 
 * @type callback
 * @region 多房间
 * @brief 发布端调用 setMultiDeviceAVSync:{@link #ByteRTCRoom#setMultiDeviceAVSync:} 后音视频同步状态发生改变时，会收到此回调。
 * @param rtcRoom ByteRTCRoom 实例
 * @param state 音视频同步状态，参看 ByteRTCAVSyncState{@link #ByteRTCAVSyncState}。
 */
- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onAVSyncStateChange:(ByteRTCAVSyncState)state;

 /** 
  * @hidden
  * @deprecated since 329.1, use onLocalAudioPropertiesReport/onRemoteAudioPropertiesReport instead
  * @type callback
  * @region 多房间
  * @author wangjunzheng
  * @brief 提示本地采集的音量信息和在房间内订阅的远端用户的音量信息。<br>
  *        本回调默认不开启。你可以通过调用 setAudioVolumeIndicationInterval:{@link #setAudioVolumeIndicationInterval:} 开启。  <br>
  * @param rtcRoom  ByteRTCRoom 对象。
  * @param speakers 本地用户和订阅的远端用户的 ID 和音量。
  *                      参看 ByteRTCAudioVolumeInfo{@link #ByteRTCAudioVolumeInfo}。
  * @param totalRemoteVolume speakers 中包含的所有音频音量之和，取值范围是 [0,255]。
  * @notes <br>
  *        + 对于本地用户：只要进行本地音频采集，回调内就会包含本地音频流的音量信息。<br>
  *        + 对于远端用户：本地必须订阅某远端用户的音频流，回调内才会包含其发送的音频流的音量信息。
  */
 - (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom
    onAudioVolumeIndication:(NSArray<ByteRTCAudioVolumeInfo *> *_Nonnull)speakers
                              totalRemoteVolume:(NSInteger)totalRemoteVolume;

/** 
 * @type callback
 * @region 多房间
 * @author liuzhiqiang.avcoder
 * @brief 房间内通话统计信息回调。   <br>
 *        用户进房开始通话后，每 2s 收到一次本回调。
 * @param rtcRoom  ByteRTCRoom 对象。
 * @param stats 当前 ByteRTCRoom 统计数据，详见：ByteRTCRoomStats{@link #ByteRTCRoomStats}
 */
- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onRoomStats:(ByteRTCRoomStats *_Nonnull)stats;

/** 
 * @type callback
 * @region 多房间
 * @author liuzhiqiang.avcoder
 * @brief 本地流数据统计以及网络质量回调。  <br>
 *        本地用户发布流成功后，SDK 会周期性（2s）的通过此回调事件通知用户发布的流在此次统计周期内的质量统计信息。  <br>
 *        统计信息通过 ByteRTCLocalStreamStats{@link #ByteRTCLocalStreamStats} 类型的回调参数传递给用户，其中包括发送音视频比特率、发送帧率、编码帧率，网络质量等。  <br>
 * @param rtcRoom  ByteRTCRoom 对象。  <br>
 * @param stats  当前房间本地流数据统计。详见：ByteRTCLocalStreamStats{@link #ByteRTCLocalStreamStats} <br>
 */
- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onLocalStreamStats:(ByteRTCLocalStreamStats *_Nonnull)stats;

/** 
 * @type callback
 * @region 多房间
 * @author liuzhiqiang.avcoder
 * @brief 本地订阅的远端音/视频流数据统计以及网络质量回调。  <br>
 *        本地用户订阅流成功后，SDK 会周期性（2s）的通过此回调事件通知用户订阅的流在此次统计周期内的质量统计信息，包括：发送音视频比特率、发送帧率、编码帧率，网络质量等。
 * @param rtcRoom  ByteRTCRoom 对象。
 * @param stats  当前房间本地流数据统计。 详见：ByteRTCRemoteStreamStats{@link #ByteRTCRemoteStreamStats}
 */
- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onRemoteStreamStats:(ByteRTCRemoteStreamStats *_Nonnull)stats;

/** 
 * @type callback
 * @region 多房间
 * @author shenpengliang
 * @brief 远端可见用户加入房间，或房内隐身用户切换为可见的回调。<br>
 *        1. 远端用户调用 setUserVisibility:{@link #ByteRTCRoom#setUserVisibility:} 方法将自身设为可见后加入房间时，房间内其他用户将收到该事件。  <br>
 *        2. 远端可见用户断网后重新连入房间时，房间内其他用户将收到该事件。  <br>
 *        3. 房间内隐身远端用户调用 setUserVisibility:{@link #ByteRTCRoom#setUserVisibility:} 方法切换至可见时，房间内其他用户将收到该事件。  <br>
 *        4. 新进房用户会收到进房前已在房内的主播角色用户的进房回调通知。  <br>
 * @param rtcRoom ByteRTCRoom 对象。  <br>
 * @param userInfo 用户信息，参看 ByteRTCUserInfo{@link #ByteRTCUserInfo}。  <br>
 * @param elapsed 保留字段，无意义
 */
- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onUserJoined:(ByteRTCUserInfo *_Nonnull)userInfo elapsed:(NSInteger)elapsed;

    /** 
     * @type callback
     * @author shenpengliang
     * @brief 远端用户离开房间，或切至不可见时，本地用户会收到此事件
     * @param uid 离开房间，或切至不可见的的远端用户 ID。  <br>
     * @param reason 用户离开房间的原因：  <br>
     *              + 0: 远端用户调用 leaveRoom{@link #ByteRTCRoom#leaveRoom} 主动退出房间。  <br>
     *              + 1: 远端用户因 Token 过期或网络原因等掉线。 <br>
     *              + 2: 远端用户调用 setUserVisibility:{@link #ByteRTCRoom#setUserVisibility:} 切换至不可见状态。 <br>
     *              + 3: 服务端调用 OpenAPI 将远端用户踢出房间。
     */
    - (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onUserLeave:(NSString *_Nonnull)uid reason:(ByteRTCUserOfflineReason)reason;
    /** 
     * @type callback
     * @brief Token 过期前 30 秒将触发该回调。<br>
     *        调用 updateToken:{@link #ByteRTCEngineKit#updateToken:} 更新 Token。否则 Token 过期后，用户将被移出房间无法继续进行音视频通话。
     */
     - (void)onTokenWillExpire:(ByteRTCRoom *_Nonnull)rtcRoom;

/** 
 * @hidden
 * @type callback
 * @region 多房间
 * @author shenpengliang
 * @brief 当房间内用户调用 MuteAllRemoteAudio{@link #MuteAllRemoteAudio}，
 *        改变接收所有远端音频流的状态时, 房间内其他用户收到这个回调。
 * @param rtcRoom  ByteRTCRoom 对象。  <br>
 * @param uid 改变接收状态的用户 ID
 * @param muteState 接收状态，详见：ByteRTCMuteState{@link #ByteRTCMuteState}
 */
- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onMuteAllRemoteAudio:(NSString *_Nonnull)uid muteState:(ByteRTCMuteState)muteState;

/** 
 * @hidden
 * @type callback
 * @region 多房间
 * @brief 房间内用户暂停/恢复接收所有视频流时，房间内其他用户收到此回调。参看 MuteAllRemoteVideo{@link #MuteAllRemoteVideo}。
 * @param rtcRoom  ByteRTCRoom 对象。  <br>
 * @param uid 暂停/恢复接收视频流的用户 ID。
 * @param muteState 暂停/恢复接收视频流。参看 ByteRTCMuteState{@link #ByteRTCMuteState}。
 */
- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onMuteAllRemoteVideo:(NSString *_Nonnull)uid withMuteState:(ByteRTCMuteState)muteState;

/** 
 * @hidden
 * @deprecated since 336.1, use onUserPublishStream, onUserPublishScreen, onUserUnPublishStream and onUserUnPublishScreen instead.
 * @type callback
 * @region 多房间
 * @author shenpengliang
 * @brief 房间内用户暂停/恢复发送音频流时，房间内其他用户会收到此回调。参看 muteLocalAudio:{@link #ByteRTCEngineKit#muteLocalAudio:}。
 * @param rtcRoom  ByteRTCRoom 实例
 * @param uid 改变本地音频发送状态的用户 ID
 * @param muteState 发送状态，参看 ByteRTCMuteState{@link #ByteRTCMuteState}
 */
- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onUserMuteAudio:(NSString *_Nonnull)uid muteState:(ByteRTCMuteState)muteState;

/** 
 * @hidden
 * @deprecated since 323.1, use onUserStartAudioCapture instead
 * @type callback
 * @region 多房间
 * @author dixing
 * @brief 远端用户开启/关闭音频设备采集回调
 *         提示有远端用户已开启/关闭音频设备采集，该回调由远端用户调用 enableLocalAudio:{@link #enableLocalAudio:} 方法触发
 * @param rtcRoom ByteRTCRoom对象
 * @param enabled YES: 该用户开启了音频设备采集；NO: 该用户关闭了音频设备采集
 * @param uid 远端用户ID
 *       + 该接口已废弃，请使用 onUserStartAudioCapture{@link #ByteRTCEngineDelegate#onUserStartAudioCapture} 以及 onUserStopAudioCapture{@link #ByteRTCEngineDelegate#onUserStopAudioCapture} <br>
 */
- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom didLocalAudioEnabled:(BOOL)enabled byUid:(NSString *_Nonnull)uid;

 /** 
  * @type callback
  * @region 多房间
  * @author dixing
  * @brief 房间内的用户调用 startAudioCapture{@link #ByteRTCEngineKit#startAudioCapture} 开启音频采集时，房间内其他用户会收到此回调。
  * @param rtcRoom ByteRTCRoom 实例
  * @param userId 开启音频采集的远端用户 ID
  */
 - (void)rtcRoom:(ByteRTCRoom * _Nonnull)rtcRoom onUserStartAudioCapture:(NSString *_Nonnull)userId;

 /** 
  * @type callback
  * @region 多房间
  * @author dixing
  * @brief 房间内的用户调用 stopAudioCapture{@link #ByteRTCEngineKit#stopAudioCapture} 关闭音频采集时，房间内其他用户会收到此回调。
  * @param rtcRoom ByteRTCRoom 实例
  * @param userId 关闭音频采集的远端用户 ID
  */
 - (void)rtcRoom:(ByteRTCRoom * _Nonnull)rtcRoom onUserStopAudioCapture:(NSString *_Nonnull)userId;

/** 
 * @type callback
 * @region 多房间
 * @author wangjunzheng
 * @brief 本地采集到第一帧音频帧时，收到该回调。
 * @param rtcRoom ByteRTCRoom 对象。
 * @param streamIndex 音频流属性, 详见 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 */
- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onFirstLocalAudioFrame:(ByteRTCStreamIndex) streamIndex;

 /** 
  * @type callback
  * @region 多房间
  * @author wangjunzheng
  * @brief 当收到远端流的第一帧音频的时候上报该事件
  * @param rtcRoom ByteRTCRoom 对象。
  * @param key 远端流信息, 详见 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
  * @notes 用户刚收到房间内每一路音频流时，都会收到该回调。
  */
 - (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onFirstRemoteAudioFrame:(ByteRTCRemoteStreamKey * _Nonnull)key;

 /** 
  * @hidden
  * @deprecated since 336.1, use onUserPublishStream and onUserPublishScreen instead.
  * @type callback
  * @region 多房间
  * @author shenpengliang
  * @brief 以下情况会触发此回调：<br>
  *        + 房间内的用户发布新的音视频流时，房间内的其他用户会收到此回调通知。  <br>
  *        + 房间内的用户原音视频流被移出后，又重新发布音视频流时，房间内的其他用户会收到此回调通知。  <br>
  *        + 用户刚加入房间时，会收到此回调，包含房间中所有已发布的流。
  * @param rtcRoom  ByteRTCRoom 对象。  <br>
  * @param stream 流属性，参看 ByteRTCStream{@link #ByteRTCStream} 。  <br>
  */
 - (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onStreamAdd:(id<ByteRTCStream> _Nonnull)stream;

 /** 
  * @hidden
  * @deprecated since 336.1, use onUserUnPublishStream and onUserUnPublishScreen instead.
  * @type callback
  * @region 多房间
  * @author shenpengliang
  * @brief 房间内的远端用户停止发布音视频流时，本地用户会收到此回调通知。  <br>
  * @param rtcRoom ByteRTCRoom 对象
  * @param uid 远端流来源的用户 ID 。  <br>
  * @param stream 流的属性，参看 ByteRTCStream{@link #ByteRTCStream}。  <br>
  * @param reason 远端流移除的原因，参看 ByteRTCStreamRemoveReason{@link #ByteRTCStreamRemoveReason} 。  <br>
  */
 - (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom
    didStreamRemoved:(NSString *_Nonnull)uid
              stream:(id<ByteRTCStream> _Nonnull)stream
              reason:(ByteRTCStreamRemoveReason)reason;
/** 
 * @type callback
 * @region 房间管理
 * @author shenpengliang
 * @brief 房间内新增远端摄像头/麦克风采集的媒体流流的回调。
 * @param rtcRoom ByteRTCRoom 实例
 * @param userId 远端流发布用户的用户 ID。
 * @param type 远端媒体流的类型，参看 ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}。
 * @notes 当房间内的远端用户调用 publishStream:{@link #ByteRTCRoom#publishStream:} 成功发布由摄像头/麦克风采集的媒体流时，本地用户会收到该回调，此时本地用户可以自行选择是否调用 subscribeStream:mediaStreamType:{@link #ByteRTCRoom#subscribeStream:mediaStreamType:} 订阅此流。
 */
- (void)rtcRoom:(ByteRTCRoom * _Nonnull)rtcRoom onUserPublishStream:(NSString *_Nonnull)userId            type:(ByteRTCMediaStreamType)type;
/** 
 * @type callback
 * @region 房间管理
 * @author shenpengliang
 * @brief 房间内远端摄像头/麦克风采集的媒体流移除的回调。
 * @param rtcRoom ByteRTCRoom 实例
 * @param userId 移除的远端流发布用户的用户 ID。  <br>
 * @param type 移除的远端流类型，参看 ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}。  <br>
 * @param reason 远端流移除的原因，参看 ByteRTCStreamRemoveReason{@link #ByteRTCStreamRemoveReason}。
 * @notes 收到该回调通知后，你可以自行选择是否调用 unSubscribeStream:mediaStreamType:{@link #ByteRTCRoom#unSubscribeStream:mediaStreamType:} 取消订阅此流。
 */
- (void)rtcRoom:(ByteRTCRoom * _Nonnull)rtcRoom onUserUnPublishStream:(NSString *_Nonnull)userId            type:(ByteRTCMediaStreamType)type
           reason:(ByteRTCStreamRemoveReason)reason;
/** 
 * @type callback
 * @region 房间管理
 * @author shenpengliang
 * @brief 房间内新增远端屏幕共享音视频流的回调。
 * @param rtcRoom ByteRTCRoom实例
 * @param userId 远端流发布用户的用户 ID。
 * @param type 远端媒体流的类型，参看 ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}。
 * @notes 当房间内的远端用户调用 publishScreen:{@link #ByteRTCRoom#publishScreen:} 成功发布来自屏幕共享的音视频流时，本地用户会收到该回调，此时本地用户可以自行选择是否调用 subscribeScreen:mediaStreamType:{@link #ByteRTCRoom#subscribeScreen:mediaStreamType:} 订阅此流。
 */
- (void)rtcRoom:(ByteRTCRoom * _Nonnull)rtcRoom onUserPublishScreen:(NSString *_Nonnull)userId   type:(ByteRTCMediaStreamType)type;
/** 
 * @type callback
 * @region 房间管理
 * @author shenpengliang
 * @brief 房间内远端屏幕共享音视频流移除的回调。
 * @param rtcRoom ByteRTCRoom 实例
 * @param userId 移除的远端流发布用户的用户 ID。  <br>
 * @param type 移除的远端流类型，参看 ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}。  <br>
 * @param reason 远端流移除的原因，参看 ByteRTCStreamRemoveReason{@link #ByteRTCStreamRemoveReason}。
 * @notes 收到该回调通知后，你可以自行选择是否调用 unSubscribeScreen:mediaStreamType:{@link #ByteRTCRoom#unSubscribeScreen:mediaStreamType:} 取消订阅此流。
 */
- (void)rtcRoom:(ByteRTCRoom * _Nonnull)rtcRoom onUserUnPublishScreen:(NSString *_Nonnull)userId type:(ByteRTCMediaStreamType)type
           reason:(ByteRTCStreamRemoveReason)reason;
/** 
 * @type callback
 * @region 房间管理
 * @author shenpengliang
 * @brief 关于订阅媒体流状态改变的回调
 * @param rtcRoom ByteRTCRoom 对象
 * @param state 订阅媒体流状态，参看 ByteRTCSubscribeState{@link #ByteRTCSubscribeState}
 * @param userId 流发布用户的用户 ID
 * @param info 流的属性，参看 ByteRTCSubscribeConfig{@link #ByteRTCSubscribeConfig}
 * @notes  <br>
 *        本地用户收到该回调的时机包括：  <br>
 *        + 调用 subscribeStream:mediaStreamType:{@link #ByteRTCRoom#subscribeStream:mediaStreamType:} 或 unSubscribeStream:mediaStreamType:{@link #ByteRTCRoom#unSubscribeStream:mediaStreamType:} 订阅/取消订阅指定远端摄像头音视频流后；  <br>
 *        + 调用 subscribeScreen:mediaStreamType:{@link #ByteRTCRoom#subscribeScreen:mediaStreamType:} 或 unSubscribeScreen:mediaStreamType:{@link #ByteRTCRoom#unSubscribeScreen:mediaStreamType:} 订阅/取消订阅指定远端屏幕共享流后。
 */
- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom
    onStreamSubscribed:(ByteRTCSubscribeState)state
                userId:(NSString *_Nonnull)userId
       subscribeConfig:(ByteRTCSubscribeConfig *_Nonnull)info;

/** 
 * @hidden
 * @type callback
 * @region 多房间
 * @author shenpengliang
 * @brief 当发布流成功的时候回调该事件
 * @param rtcRoom  ByteRTCRoom 对象。  <br>
 * @param userId 用户ID
 * @param isScreen 该流是否是屏幕流
 *
 */
- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onStreamPublishSuccess:(NSString *_Nonnull)userId isScreen:(BOOL)isScreen;

 /** 
  * @type callback
  * @region 多房间
  * @author hanchenchen.c
  * @brief 收到房间中调用 sendRoomMessage:{@link #ByteRTCEngineKit#sendRoomMessage:} 发送的广播文本消息时，收到此回调。
  * @param rtcRoom ByteRTCRoom 对象
  * @param uid 消息发送者 ID 。
  * @param message 收到的文本消息内容。
  */
 - (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onRoomMessageReceived:(NSString *_Nonnull)uid
        message:(NSString *_Nonnull)message;

 /** 
  * @type callback
  * @region 多房间
  * @author hanchenchen.c
  * @brief 收到房间中调用 sendRoomBinaryMessage:{@link #ByteRTCRoom#sendRoomBinaryMessage:} 发送的广播二进制消息时，收到此回调。
  * @param rtcRoom ByteRTCRoom 对象
  * @param uid 消息发送者 ID 。
  * @param message 收到的二进制消息内容。
  */
 - (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onRoomBinaryMessageReceived:(NSString *_Nonnull)uid
        message:(NSData *_Nonnull)message;

 /** 
  * @type callback
  * @region 多房间
  * @author hanchenchen.c
  * @brief 收到来自房间中其他用户通过 sendUserMessage:message:{@link #ByteRTCRoom#sendUserMessage:message:} 发来的文本消息时（P2P），会收到此回调。
  * @param rtcRoom ByteRTCRoom 对象
  * @param uid 消息发送者的用户 ID 。
  * @param message 收到的文本消息内容。
  */
 - (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom
    onUserMessageReceived:(NSString *_Nonnull)uid
               message:(NSString *_Nonnull)message;

 /** 
 * @type callback
 * @region 多房间
 * @author hanchenchen.c
 * @brief 收到来自房间中其他用户通过 sendUserBinaryMessage:message:{@link #ByteRTCRoom#sendUserBinaryMessage:message:} 发来的二进制消息时，会收到此回调。
 * @param rtcRoom ByteRTCRoom 对象
 * @param uid 消息发送者的用户 ID 。
 * @param message 收到的二进制消息内容。
 */
- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom
    onUserBinaryMessageReceived:(NSString *_Nonnull)uid
               message:(NSData *_Nonnull)message;

 /** 
  * @type callback
  * @region 多房间
  * @author hanchenchen.c
  * @brief 向房间内单个用户发送文本或二进制消息后（P2P），消息发送方会收到该消息发送结果回调。
  * @param rtcRoom ByteRTCRoom 对象。
  * @param msgid 本条消息的 ID。
  * @param error 消息发送结果，详见 ByteRTCUserMessageSendResult{@link #ByteRTCUserMessageSendResult}
  * @notes  <br>
  *        + 你应调用 sendUserMessage:message:{@link #ByteRTCRoom#sendUserMessage:message:} 向房间内单个用户发送文本消息 <br>
  *        + 你应调用 sendUserBinaryMessage:message:{@link #ByteRTCRoom#sendUserBinaryMessage:message:} 向房间内单个用户发送二进制消息
  */
 - (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onUserMessageSendResult:(int64_t)msgid error:(ByteRTCUserMessageSendResult)error;

 /** 
  * @type callback
  * @region 多房间
  * @author hanchenchen.c
  * @brief 向房间内所有用户群发文本或二进制消息后，消息发送方会收到该消息发送结果回调。
  * @param rtcRoom ByteRTCRoom 对象。
  * @param msgid 本条消息的 ID。
  * @param error 消息发送结果，详见 ByteRTCRoomMessageSendResult{@link #ByteRTCRoomMessageSendResult}
  * @notes  <br>
  *        + 你应调用 sendRoomMessage:{@link #ByteRTCRoom#sendRoomMessage:} 向房间内群发文本消息 <br>
  *        + 你应调用 sendRoomBinaryMessage:{@link #ByteRTCRoom#sendRoomBinaryMessage:} 向房间内群发二进制消息
  */
 - (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onRoomMessageSendResult:(int64_t)msgid error:(ByteRTCRoomMessageSendResult)error;

 /** 
  * @type callback
  * @region 多房间
  * @author zhushufan.ref
  * @brief 第一帧本地采集的视频/屏幕共享画面在本地视图渲染完成时，收到此回调。
  * @param rtcRoom ByteRTCRoom 对象。  <br>
  * @param streamIndex 流属性，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
  * @param frameInfo 视频帧信息，参看 ByteRTCVideoFrameInfo{@link #ByteRTCVideoFrameInfo}
  */
 - (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onFirstLocalVideoFrameCaptured:(ByteRTCStreamIndex)streamIndex withFrameInfo:(ByteRTCVideoFrameInfo *_Nonnull)frameInfo;

 /** 
  * @type callback
  * @region 多房间
  * @author zhushufan.ref
  * @brief 本地视频大小或旋转信息发生变化时，收到此回调。
  * @param rtcRoom ByteRTCRoom 对象。
  * @param streamIndex 流属性，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
  * @param frameInfo 视频帧信息，参看 ByteRTCVideoFrameInfo{@link #ByteRTCVideoFrameInfo}
  */
 - (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom
    onLocalVideoSizeChanged:(ByteRTCStreamIndex)streamIndex
                     withFrameInfo:(ByteRTCVideoFrameInfo *_Nonnull)frameInfo;

/** 
 * @type callback
 * @region 多房间
 * @author zhushufan.ref
 * @brief 远端视频大小或旋转配置发生改变时，房间内订阅此视频流的用户会收到此回调。
 * @param rtcRoom ByteRTCRoom 对象。  <br>
 * @param streamKey 远端流信息。参看 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
 * @param frameInfo 视频帧信息。参看 ByteRTCVideoFrameInfo{@link #ByteRTCVideoFrameInfo}
 */
- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom
    onRemoteVideoSizeChanged:(ByteRTCRemoteStreamKey *_Nonnull)streamKey
                     withFrameInfo:(ByteRTCVideoFrameInfo *_Nonnull)frameInfo;

/** 
 * @type callback
 * @region 多房间
 * @author zhushufan.ref
 * @brief SDK 内部渲染成功远端视频流首帧后，收到此回调。
 * @param rtcRoom ByteRTCRoom 对象。  <br>
 * @param streamKey 远端流信息，参看 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
 * @param frameInfo 视频帧信息，参看 ByteRTCVideoFrameInfo{@link #ByteRTCVideoFrameInfo}
 */
- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom
    onFirstRemoteVideoFrameRendered:(ByteRTCRemoteStreamKey *_Nonnull)streamKey
                      withFrameInfo:(ByteRTCVideoFrameInfo *_Nonnull)frameInfo;

/** 
 * @type callback
 * @region 多房间
 * @author zhushufan.ref
 * @brief SDK 接收并解码远端视频流首帧后，收到此回调。
 * @param rtcRoom ByteRTCRoom 对象。  <br>
 * @param streamKey 远端流信息，参看 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
 * @param frameInfo 视频帧信息，参看 ByteRTCVideoFrameInfo{@link #ByteRTCVideoFrameInfo}
 */
- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom
    onFirstRemoteVideoFrameDecoded:(ByteRTCRemoteStreamKey *_Nonnull)streamKey
                      withFrameInfo:(ByteRTCVideoFrameInfo *_Nonnull)frameInfo;

/** 
 * @hidden
 * @deprecated since 336.1, use onUserPublishStream, onUserPublishScreen, onUserUnPublishStream and onUserUnPublishScreen instead.
 * @type callback
 * @region 多房间
 * @author shenpengliang
 * @brief 房间内用户暂停/恢复发送视频流时，房间内其他用户会收到此回调。参看 muteLocalVideo:{@link #ByteRTCEngineKit#muteLocalVideo:}。
 * @param rtcRoom ByteRTCRoom 实例
 * @param uid 暂停/恢复发送视频流的用户 ID。
 * @param muteState 视频流的发送状态。参看 ByteRTCMuteState{@link #ByteRTCMuteState}
 */
- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onUserMuteVideo:(NSString *_Nonnull)uid withMuteState:(ByteRTCMuteState)muteState;

/** 
 * @type callback
 * @region 多房间
 * @brief 房间内的可见用户调用 startVideoCapture{@link #ByteRTCEngineKit#startVideoCapture} 开启内部视频采集时，房间中其他用户会收到此回调。
 * @param rtcRoom ByteRTCRoom 实例  <br>
 * @param userId 调用 startVideoCapture{@link #ByteRTCEngineKit#startVideoCapture} 接口的远端用户 ID
 */
- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onUserStartVideoCapture:(NSString *_Nonnull)userId;

 /** 
  * @type callback
  * @region 多房间
  * @brief 房间内的可见用户调用 stopVideoCapture{@link #ByteRTCEngineKit#stopVideoCapture} 时，本地用户将会收到该回调。
  * @param rtcRoom ByteRTCRoom 实例
  * @param uid 关闭视频采集的远端用户 ID
  */
 - (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onUserStopVideoCapture:(NSString *_Nonnull)uid;

/** 
 * @type callback
 * @region 多房间
 * @author wangjunzheng
 * @brief 本地音频流的状态发生改变时，收到此回调。
 * @param rtcRoom ByteRTCRoom 对象。  <br>
 * @param state 本地音频设备的当前状态，详见 ByteRTCLocalAudioStreamState{@link #ByteRTCLocalAudioStreamState}
 * @param error 本地音频流状态改变时的错误码，详见 ByteRTCLocalAudioStreamError{@link #ByteRTCLocalAudioStreamError}
 */
- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom
    onLocalAudioStateChanged:(ByteRTCLocalAudioStreamState)state
                     error:(ByteRTCLocalAudioStreamError)error;

/** 
 * @type callback
 * @region 多房间
 * @author wangjunzheng
 * @brief 订阅的远端音频流状态发生改变时，收到此回调。
 * @param rtcRoom ByteRTCRoom 对象。  <br>
 *  @param key 远端流信息, 详见 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
 *  @param state 远端音频流的当前状态，详见 ByteRTCRemoteAudioState{@link #ByteRTCRemoteAudioState}
 *  @param reason 远端音频流状态改变的原因，详见 ByteRTCRemoteAudioStateChangeReason{@link #ByteRTCRemoteAudioStateChangeReason}
 */
- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom
    onRemoteAudioStateChanged:(ByteRTCRemoteStreamKey * _Nonnull)key
                            state:(ByteRTCRemoteAudioState)state
                           reason:(ByteRTCRemoteAudioStateChangeReason)reason;

/** 
 * @type callback
 * @region 多房间
 * @brief 本地视频流的状态发生改变时，收到该事件。
 * @param rtcRoom ByteRTCRoom 对象。  <br>
 * @param streamIndex 流属性，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param state 本地视频流的当前状态，详见 ByteRTCLocalVideoStreamState{@link #ByteRTCLocalVideoStreamState}
 * @param error 本地视频状态改变时的错误码，详见 ByteRTCLocalVideoStreamError{@link #ByteRTCLocalVideoStreamError}
 */
- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom
    onLocalVideoStateChanged:(ByteRTCStreamIndex)streamIndex
             withStreamState:(ByteRTCLocalVideoStreamState)state
             withStreamError:(ByteRTCLocalVideoStreamError)error;

/** 
 * @type callback
 * @region 多房间
 * @brief 远端视频流的状态发生改变时，房间内订阅此流的用户会收到该事件。
 * @param rtcRoom ByteRTCRoom 对象。  <br>
 * @param streamKey 远端视频流信息，房间、用户 ID、流属性等，参看 ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
 * @param state 远端视频流的当前状态，参看 ByteRTCRemoteVideoState{@link #ByteRTCRemoteVideoState}
 * @param reason 远端视频流状态改变的原因，参看 ByteRTCRemoteVideoStateChangeReason{@link #ByteRTCRemoteVideoStateChangeReason}
 */
- (void)rtcRoom:(ByteRTCRoom * _Nonnull)rtcRoom
    onRemoteVideoStateChanged:(ByteRTCRemoteStreamKey * _Nonnull)streamKey
               withVideoState:(ByteRTCRemoteVideoState)state
         withVideoStateReason:(ByteRTCRemoteVideoStateChangeReason)reason;

/** 
 * @type callback
 * @region 多房间
 * @author shenpengliang
 * @brief 音频首帧发送状态改变时，收到此回调。
 * @param rtcRoom ByteRTCRoom 对象。  <br>
 * @param user 本地用户信息，详见 ByteRTCUser{@link #ByteRTCUser}
 * @param state 首帧发送状态，详见 ByteRTCFirstFrameSendState{@link #ByteRTCFirstFrameSendState}
 */
- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onAudioFrameSendStateChanged:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFrameSendState)state;

/** 
 * @type callback
 * @region 多房间
 * @author shenpengliang
 * @brief 视频首帧发送状态改变时，收到此回调
 * @param rtcRoom ByteRTCRoom 对象。  <br>
 * @param user 本地用户信息，详见 ByteRTCUser{@link #ByteRTCUser}
 * @param state 首帧发送状态，详见 ByteRTCFirstFrameSendState{@link #ByteRTCFirstFrameSendState}
 */
- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onVideoFrameSendStateChanged:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFrameSendState)state;

/** 
 * @type callback
 * @region 多房间
 * @author shenpengliang
 * @brief 屏幕共享流视频首帧发送状态改变时，收到此回调
 * @param rtcRoom ByteRTCRoom 对象。  <br>
 * @param user 本地用户信息，详见 ByteRTCUser{@link #ByteRTCUser}
 * @param state 首帧发送状态，详见 ByteRTCFirstFrameSendState{@link #ByteRTCFirstFrameSendState}
 */
- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onScreenVideoFrameSendStateChanged:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFrameSendState)state;

/** 
 * @type callback
 * @region 多房间
 * @author shenpengliang
 * @brief 音频首帧播放状态改变时，收到此回调
 * @param rtcRoom ByteRTCRoom 对象。  <br>
 * @param user 音频流来源的用户信息，参看 ByteRTCUser{@link #ByteRTCUser}
 * @param state 首帧播放状态，详见 ByteRTCFirstFramePlayState{@link #ByteRTCFirstFramePlayState}
 */
- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onAudioFramePlayStateChanged:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFramePlayState)state;

/** 
 * @type callback
 * @region 多房间
 * @author shenpengliang
 * @brief 视频首帧播放状态改变时，收到此回调
 * @param rtcRoom ByteRTCRoom 对象。  <br>
 * @param user 视频流来源的用户信息，参看 ByteRTCUser{@link #ByteRTCUser}
 * @param state 首帧播放状态，详见 ByteRTCFirstFramePlayState{@link #ByteRTCFirstFramePlayState}
 */
- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onVideoFramePlayStateChanged:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFramePlayState)state;

/** 
 * @hidden
 * @type callback
 * @region 多房间
 * @author shenpengliang
 * @brief 屏幕共享流视频首帧播放状态改变时，收到此回调
 * @param rtcRoom ByteRTCRoom 对象。  <br>
 * @param user 屏幕共享流来源的用户信息，参看 ByteRTCUser{@link #ByteRTCUser}
 * @param state 首帧播放状态，详见 ByteRTCFirstFramePlayState{@link #ByteRTCFirstFramePlayState}
 */
- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onScreenVideoFramePlayStateChanged:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFramePlayState)state;

/** 
 * @type callback
 * @region 视频管理
 * @author qipengxiang
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
 *        + 通话人数超过 5 人时，只有被封禁/解禁用户会收到该回调。
 */
- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onVideoStreamBanned:(NSString *_Nonnull)uid isBanned:(BOOL)banned;

/** 
 * @type callback
 * @region 音频事件回调
 * @author qipengxiang
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
 *        + 通话人数超过 5 人时，只有被封禁/解禁用户会收到该回调。
 */
- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onAudioStreamBanned:(NSString *_Nonnull)uid isBanned:(BOOL)banned;

#pragma mark ForwardStream related callback
    /** 
     * @type callback
     * @region 多房间
     * @brief 跨房间媒体流转发状态和错误回调
     * @param rtcRoom ByteRTCRoom 对象
     * @param infos 跨房间媒体流转发目标房间信息数组，详见 ForwardStreamStateInfo{@link #ForwardStreamStateInfo}
     */
    - (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onForwardStreamStateChanged:(NSArray<ForwardStreamStateInfo *> * _Nonnull)infos;
    /** 
     * @type callback
     * @region 多房间
     * @brief 跨房间媒体流转发事件回调
     * @param rtcRoom ByteRTCRoom 对象
     * @param infos 跨房间媒体流转发目标房间事件数组，详见 ForwardStreamEventInfo{@link #ForwardStreamEventInfo}
     */
    - (void)rtcRoom:(ByteRTCRoom * _Nonnull)rtcRoom onForwardStreamEvent:(NSArray<ForwardStreamEventInfo *> * _Nonnull)infos;

/** 
 * @type callback
 * @region 公共流事件回调
 * @author qipengxiang
 * @brief 公共流发布结果回调<br>
 *        startPushPublicStream:withLayout:{@link #ByteRTCRoom#startPushPublicStream:withLayout:} 接口发布公共流后，启动结果通过此回调方法通知用户。
 * @param streamid 公共流 ID
 * @param code 公共流发布结果状态码<br>
 *             `200`: 发布成功
 */
- (void)rtcRoom:(ByteRTCRoom *_Nonnull)rtcRoom onPushPublicStreamResult:(NSString *_Nonnull)streamid errorCode:(int)code;
@end

/**
 * @type api
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCRoom : NSObject

@property(nonatomic, weak) id<ByteRTCRoomDelegate> _Nullable delegate;

#pragma mark - Core Methods

/** 
 * @type api
 * @region 多房间
 * @author shenpengliang
 * @brief 销毁房间
 * @notes 退出并销毁调用 createRtcRoom:{@link #ByteRTCEngineKit#createRtcRoom:} 所创建的房间。
 */
- (void)destroy;

/** 
 * @type api
 * @region 多房间
 * @author shenpengliang
 * @brief 获取房间 ID
 */
- (NSString *_Nullable)getRoomId;

/** 
 * @type api
 * @region 多房间
 * @author shenpengliang
 * @brief 通过设置 ByteRTCRoomDelegate{@link #ByteRTCRoomDelegate} 代理，可以监听此 `ByteRTCRoom` 对象对应的回调事件。
 * @param roomDelegate 参见 ByteRTCRoomDelegate{@link #ByteRTCRoomDelegate}。
 */
- (void)setRtcRoomDelegate:(id<ByteRTCRoomDelegate> _Nullable)roomDelegate;

/** 
 * @hidden
 * @deprecated since 326.1, use joinRoomByToken with MultiRoomConfig instead
 * @type api
 * @region 多房间
 * @author shenpengliang
 * @brief 加入房间。<br>
 *        同一房间内的用户间可以相互通话。  <br>
 *        调用 createRtcRoom:{@link #ByteRTCEngineKit#createRtcRoom:} 创建房间后，调用此方法加入房间，同房间内其他用户进行音视频通话。<br>
 *        用户调用此方法加入房间成功后，其他用户会收到 rtcRoom:onUserJoined:elapsed:{@link #rtcRoom:onUserJoined:elapsed:} 回调通知。  <br>
 * @param token 动态密钥，用于对进房用户进行鉴权验证。  <br>
 *        进入房间需要携带 Token。测试时可使用控制台生成临时 Token，正式上线需要使用密钥 SDK 在你的服务端生成并下发 Token。  <br>
 * @param userInfo 用户 ID。最大长度为 128 字节的非空字符串。支持的字符集范围为: <br>
 *        1. 26个大写字母 A ~ Z <br>
 *        2. 26个小写字母 a ~ z <br>
 *        3. 10个数字 0 ~ 9 <br>
 *        4. 下划线"_", at符"@", 减号"-" <br>
 * @param roomProfile 房间模式。  <br>
 *        你应该根据业务需要，选择合适的房间模式。  <br>
 *        你必须在进房前设置房间模式，并且进房后不可更改。  <br>
 *        房间模式参看 ByteRTCRoomProfile{@link #ByteRTCRoomProfile}。
 * @return 方法调用结果。  <br>
 *         +  0: 成功  <br>
 *         + -1: roomId 为空，失败  <br>
 *         + -2: userId 为空，失败  <br>
 * @notes  <br>
 *        + 使用不同 App ID 的 App 是不能互通的。  <br>
 *        + 请务必保证生成 Token 使用的 App ID 和创建引擎时使用的 App ID 相同，否则会导致加入房间失败。  <br>
 *        + 用户加入房间成功后，在本地网络状况不佳的情况下，SDK 可能会与服务器失去连接，此时 SDK 将会自动重连。重连成功后，本地会收到 rtcEngine:onUserJoined:elapsed:{@link #ByteRTCRoomDelegate#rtcEngine:onUserJoined:elapsed:} 回调通知。  <br>
 */
- (int)joinRoomByToken:(NSString *_Nullable)token userInfo:(ByteRTCUserInfo *_Nonnull)userInfo roomProfile:(ByteRTCRoomProfile)roomProfile
DEPRECATED_MSG_ATTRIBUTE("Please use joinRoomByToken with multiRoomConfig");

/** 
 * @type api
 * @region 多房间
 * @author shenpengliang
 * @brief 加入房间。<br>
 *        调用 createRtcRoom:{@link #ByteRTCEngineKit#createRtcRoom:} 创建房间后，调用此方法加入房间，同房间内其他用户进行音视频通话。  <br>
 * @param token 动态密钥，用于对进房用户进行鉴权验证。  <br>
 *        进入房间需要携带 Token。测试时可使用控制台生成临时 Token，正式上线需要使用密钥 SDK 在你的服务端生成并下发 Token。  <br>
 *        使用不同 AppID 的 App 是不能互通的。  <br>
 *        请务必保证生成 Token 使用的 AppID 和创建引擎时使用的 AppID 相同，否则会导致加入房间失败。  <br>
 * @param userInfo 用户 ID。参看 ByteRTCUserInfo{@link #ByteRTCUserInfo}。  <br>
 * @param roomConfig 房间参数配置，设置房间模式以及是否自动发布或订阅流。具体配置模式参看 ByteRTCMultiRoomConfig{@link #ByteRTCMultiRoomConfig}。  <br>
 * @return 方法调用结果。  <br>
 *        +  0: 成功  <br>
 *        + -1: 参数无效  <br>
 *        + -2: 已经在房间内。接口调用成功后，只要收到返回值为 0 ，且未调用 leaveRoom{@link #ByteRTCRoom#leaveRoom} 成功，则再次调用进房接口时，无论填写的房间 ID 和用户 ID 是否重复，均触发此返回值。  <br>
 *        + -3: room 为空 <br>
 * @notes  <br>
 *        + 同一个 AppID 的同一个房间内，每个用户的用户 ID 必须是唯一的。如果两个用户的用户 ID 相同，则后加入房间的用户会将先加入房间的用户踢出房间，并且先加入房间的用户会收到 rtcEngine:onError:{@link #ByteRTCEngineDelegate#rtcEngine:onError:} 回调通知，错误类型为重复登录 BRERR_DUPLICATE_LOGIN。  <br>
 *        + 本地用户调用此方法加入房间成功后，会收到 rtcRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onRoomStateChanged:withUid:state:extraInfo:} 回调通知。  <br>
 *        + 本地用户调用 setUserVisibility:{@link #ByteRTCRoom#setUserVisibility:} 将自身设为可见后加入房间，远端用户会收到 rtcRoom:onUserJoined:elapsed:{@link #ByteRTCRoomDelegate#rtcRoom:onUserJoined:elapsed:} 回调通知。  <br>
 *        + 用户加入房间成功后，在本地网络状况不佳的情况下，SDK 可能会与服务器失去连接，此时 SDK 将会自动重连。重连成功后，本地会收到 rtcRoom:onUserJoined:elapsed:{@link #ByteRTCRoomDelegate#rtcRoom:onUserJoined:elapsed:} 回调通知。  <br>
 */
- (int)joinRoomByToken:(NSString *_Nullable)token userInfo:(ByteRTCUserInfo *_Nonnull)userInfo roomConfig:(ByteRTCMultiRoomConfig *_Nonnull)roomConfig;

/** 
 * @hidden
 * @deprecated since 328.1, use setUserVisibility instead
 * @type api
 * @region 多房间
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
 *        + 用户在加入房间成功后调用该方法切换用户角色，调用成功后，远端用户会收到相应的回调通知：1.本地用户角色从隐身用户切换至观众或主播时，远端用户会收到
 * rtcRoom:onUserJoined:elapsed:{@link #ByteRTCRoomDelegate#rtcRoom:onUserJoined:elapsed:}
 * 回调通知；2.本地用户角色从观众或主播切换至隐身用户时，远端用户会收到 rtcRoom:didOfflineOfUid:reason:{@link
 * #ByteRTCRoomDelegate#rtcRoom:didOfflineOfUid:reason:} 回调通知。  <br>
 */
- (int)setUserRole:(ByteRTCUserRoleType)role
    __deprecated_msg("Will be removed in new version");

/** 
 * @type api
 * @region 多房间
 * @author liuzhiqiang
 * @brief 设置用户可见性。默认可见。  <br>
 * @param enable 设置用户是否对房间内其他用户可见：  <br>
 *        + true: 可以在房间内发布音视频流，房间中的其他用户将收到用户的行为通知，例如进房、开启视频采集和退房。  <br>
 *        + false: 不可以在房间内发布音视频流，房间中的其他用户不会收到用户的行为通知，例如进房、开启视频采集和退房。
 * @return  <br>
 *         + 0: 方法调用成功  <br>
 *         + < 0: 方法调用失败  <br>
 * @notes  <br>
 *       + 该方法在加入房间前后均可调用。 <br>
 *       + 在房间内调用此方法，房间内其他用户会收到相应的回调通知：<br>
 *            - 从 false 切换至 true 时，房间内其他用户会收到 rtcRoom:onUserJoined:elapsed:{@link #ByteRTCRoomDelegate#rtcRoom:onUserJoined:elapsed:} 回调通知；  <br>
 *            - 从 true 切换至 false 时，房间内其他用户会收到 rtcRoom:onUserLeave:reason:{@link #ByteRTCRoomDelegate#rtcRoom:onUserLeave:reason:} 回调通知。  <br>
 *       + 若调用该方法将可见性设为 false，此时尝试发布流会收到 `ByteRTCWarningCodeSubscribeStreamForbiden` 警告。
 */
- (BOOL)setUserVisibility:(BOOL)enable;

/** 
 * @hidden
 * @type api
 * @region 多房间
 * @author shenpengliang
 * @brief 获取当前用户角色。  <br>
 * @return 当前用户角色，详见 ByteRTCUserRoleType{@link #ByteRTCUserRoleType} 枚举类型。  <br>
 */
- (ByteRTCUserRoleType)clientRole;

/** 
 * @type api
 * @region 多房间
 * @author wangzhanqiang
 * @brief 设置发流端音画同步。  <br>
 *        当同一用户同时使用两个通话设备分别采集发送音频和视频时，有可能会因两个设备所处的网络环境不一致而导致发布的流不同步，此时你可以在视频发送端调用该接口，SDK 会根据音频流的时间戳自动校准视频流，以保证接收端听到音频和看到视频在时间上的同步性。
 * @param audioUserId 音频发送端的用户 ID，将该参数设为空则可解除当前音视频的同步关系。
 * @return 方法调用结果：  <br>
 *        + True：成功  <br>
 *        + False：失败
 * @notes <br>
 *        + 该方法在进房前后均可调用。  <br>
 *        + 进行音画同步的音频发布用户 ID 和视频发布用户 ID 须在同一个 RTC 房间内。  <br>
 *        + 调用该接口后音画同步状态发生改变时，你会收到 rtcRoom:onAVSyncStateChange:{@link #ByteRTCRoomDelegate#rtcRoom:onAVSyncStateChange:} 回调。  <br>
 *        + 同一 RTC 房间内允许存在多个音视频同步关系，但需注意单个音频源不支持与多个视频源同时同步。  <br>
 *        + 如需更换同步音频源，再次调用该接口传入新的 `audioUserId` 即可；如需更换同步视频源，需先解除当前的同步关系，后在新视频源端开启同步。
 */
- (BOOL)setMultiDeviceAVSync:(NSString* _Nullable) audioUserId;

/** 
 *  @type api
 *  @region 房间管理
 *  @author shenpengliang
 *  @brief 离开房间。  <br>
 *         用户调用此方法离开房间，结束通话过程，释放所有通话相关的资源。  <br>
 *  @return 方法调用结果。  <br>
 *         +  0: 方法调用成功  <br>
 *         + < 0: 方法调用失败  <br>
 *  @notes  <br>
 *        + 用户离开房间后，本地会收到 onLeaveRoomWithStats:{@link #ByteRTCRoomDelegate#rtcRoom:onLeaveRoomWithStats:} 的回调；  <br>
 *        + 调用 setUserVisibility:{@link #ByteRTCRoom#setUserVisibility:} 方法将自身设为可见的用户离开房间后，房间内其他用户会收到 rtcRoom:onUserLeave:reason:{@link #ByteRTCRoomDelegate#rtcRoom:onUserLeave:reason:} 回调通知。  <br>
 *        + 调用 joinRoomByToken:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoomByToken:userInfo:roomConfig:} 方法加入房间后，必须调用此方法离开房间，否则无法进入下一个房间。无论当前是否在房间内，都可以调用此方法。重复调用此方法没有负面影响。  <br>
 */
- (int)leaveRoom;


/** 
 * @type api
 * @region 多房间
 * @author shenpengliang
 * @brief 更新 Token。  <br>
 *        用户调用 joinRoomByToken:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoomByToken:userInfo:roomConfig:} 方法加入房间时，
 *        如果使用了过期的 Token 将导致加入房间失败，并会收到 rtcRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onRoomStateChanged:withUid:state:extraInfo:} 回调，
 *        回调错误码为 ByteRTCErrorCode{@link #ByteRTCErrorCode} 中的 ByteRTCErrorCodeInvalidToken。
 *        此时需要重新获取 Token，并调用此方法更新 Token。更新 Token 后，SDK 会自动加入房间。 <br>
 * @param token 更新的动态密钥。
 * @return 方法调用结果。  <br>
 *         +  0: 方法调用成功。  <br>
 *         + < 0: 方法调用失败。  <br>
 * @notes Token 过期时，如果已经加入房间成功，则不会受到影响。Token 过期的错误会在下一次使用过期的 Token 加入房间时，或因本地网络状况不佳导致断网重新连入房间时通知用户。
 */
- (int)renewToken:(NSString *_Nullable)token;
/** 
 * @type api
 * @region 视频管理
 * @author zhaomingliang
 * @brief 设置期望订阅的远端视频流的参数。
 * @param userId 期望订阅的远端视频流发布用户的 ID。
 * @param remoteVideoConfig 期望订阅的远端视频流参数，参看 ByteRTCRemoteVideoConfig{@link #ByteRTCRemoteVideoConfig}。
 * @notes <br>
 *        + 该方法仅在发布端调用 enableSimulcastMode:{@link #ByteRTCEngineKit#enableSimulcastMode:} 开启了发送多路视频流的情况下生效，此时订阅端将收到来自发布端与期望设置的参数最相近的一路流；否则订阅端只会收到一路参数为分辨率 640px × 360px、帧率 15fps 的视频流。  <br>
 *        + 若发布端开启了推送多路流功能，但订阅端不对流参数进行设置，则默认接受发送端设置的分辨率最大的一路视频流。  <br>
 *        + 该方法需在进房后调用，若想进房前设置，你需调用 joinRoomByToken:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoomByToken:userInfo:roomConfig:}，并对 `roomConfig` 中的 `remoteVideoConfig` 进行设置。  <br>
 *        + 该方法在订阅前后都可调用，订阅后的设置会在重新订阅该流时生效。 <br>
 *        + SDK 会根据发布端和所有订阅端的设置灵活调整视频流的参数，具体调整策略详见[推送多路流](https://www.volcengine.com/docs/6348/70139)文档。
 */
- (int) setRemoteVideoConfig:(NSString * _Nonnull) userId remoteVideoConfig:(ByteRTCRemoteVideoConfig *_Nonnull) remoteVideoConfig;

/** 
 * @hidden
 * @deprecated since 336.1, use publishStream instead.
 * @type api
 * @region 多房间
 * @author shenpengliang
 * @brief 在当前所在房间内开始发布本地音视频流
 * @notes <br>
 *        + 多房间模式下，默认音视频流不自动发布。你必须调用此接口，进行手动发布。<br>
 *        + 调用 setUserVisibility:{@link #ByteRTCRoom#setUserVisibility:} 方法将自身设置为不可见后无法调用该方法，需将自身切换至可见后方可调用该方法发布音视频流。 <br>
 *        + 如果你需要发布屏幕共享流，调用 publishScreen:{@link #ByteRTCRoom#publishScreen:}。<br>
 *        + 如果你需要向多个房间发布音视频流，调用 startForwardStreamToRooms:{@link #ByteRTCRoom#startForwardStreamToRooms:}。
 *        + 用户调用此方法成功发布音视频流后，房间中的其他用户将会收到 rtcRoom:onStreamAdd:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamAdd:} 回调通知。
 */
- (int)publish;
/** 
 * @type api
 * @region 房间管理
 * @author shenpengliang
 * @brief 在当前所在房间内发布本地通过摄像头/麦克风采集的媒体流
 * @param type 媒体流类型，用于指定发布音频/视频，参看 ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}
 * @return 方法调用结果： <br>
 *        + 0: 发布成功  <br>
 *        + -1: 发布失败
 * @notes <br>
 *        + 调用 setUserVisibility:{@link #ByteRTCRoom#setUserVisibility:} 方法将自身设置为不可见后无法调用该方法，需将自身切换至可见后方可调用该方法发布摄像头音视频流。 <br>
 *        + 如果你需要发布屏幕共享流，调用 publishScreen:{@link #ByteRTCRoom#publishScreen:}。<br>
 *        + 如果你需要向多个房间发布流，调用 startForwardStreamToRooms:{@link #ByteRTCRoom#startForwardStreamToRooms:}。  <br>
 *        + 调用此方法后，房间中的所有远端用户会收到 rtcRoom:onUserPublishStream:type:{@link #ByteRTCRoomDelegate#rtcRoom:onUserPublishStream:type:} 回调通知，其中成功收到了音频流的远端用户会收到 rtcRoom:onFirstRemoteAudioFrame:{@link #ByteRTCRoomDelegate#rtcRoom:onFirstRemoteAudioFrame:} 回调，订阅了视频流的远端用户会收到 rtcRoom:onFirstRemoteVideoFrameDecoded:withFrameInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onFirstRemoteVideoFrameDecoded:withFrameInfo:} 回调。<br>
 *        + 调用 unpublishStream:{@link #ByteRTCRoom#unpublishStream:} 取消发布。
 */
- (int)publishStream:(ByteRTCMediaStreamType)type;


 /** 
  * @hidden
  * @deprecated since 336.1, use unpublishStream instead.
  * @type api
  * @region 多房间
  * @author shenpengliang
  * @brief 停止将本端音视频流发布到此房间
  * @notes <br>
  *        + 在多房间模式下，调用 publish{@link #ByteRTCRoom#publish} 手动发布音视频流后，调用此接口停止发布。<br>
  *        + 房间内用户调用此方法停止发布音视频流后，房间中的其他用户将会收到 rtcRoom:didStreamRemoved:stream:reason:{@link #ByteRTCRoomDelegate#rtcRoom:didStreamRemoved:stream:reason:} 回调通知。
  */
 - (int)unpublish;
/** 
 * @type api
 * @region 房间管理
 * @author shenpengliang
 * @brief 停止将本地摄像头/麦克风采集的媒体流发布到当前所在房间中
 * @param type 媒体流类型，用于指定停止发布音频/视频，参看 ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}
 * @return  <br>
 *        + 0: 停止发布成功  <br>
 *        + -1: 停止发布失败
 * @notes  <br>
 *        + 调用 publishStream:{@link #ByteRTCRoom#publishStream:} 手动发布摄像头音视频流后，你需调用此接口停止发布。<br>
 *        + 调用此方法停止发布音视频流后，房间中的其他用户将会收到 rtcRoom:onUserUnPublishStream:type:reason: {@link #ByteRTCRoomDelegate#rtcRoom:onUserUnPublishStream:type:reason:} 回调通知。
 */
- (int)unpublishStream:(ByteRTCMediaStreamType)type;


/** 
 * @hidden
 * @deprecated since 336.1
 * @type api
 * @region 多房间
 * @author liyi.000
 * @brief 发布本地屏幕视频流到此房间。（外部采集）<br>
 *        调用此方法后，你还需要周期性调用 pushScreenCaptureFrame:time:rotation:{@link #ByteRTCEngineKit#pushScreenCaptureFrame:time:rotation:} 方法，
 *        将需要发送的屏幕数据推送给 SDK。
 * @notes <br>
 *       + 仅房间内可见的用户可以进行手动发布。调用 setUserVisibility:{@link #ByteRTCRoom#setUserVisibility:} 可以设置用户可见性。<br>
 *       + 调用此方法后，房间内的远端用户会收到 rtcRoom:onStreamAdd:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamAdd:} 事件。
 *       + 如果你需要由外部屏幕采集切换为内部采集，你必须调用 unpublishScreen{@link #unpublishScreen} 关闭外部采集后，
 *         通过调用 startScreenSharingWithPreferredExtension:groupId:{@link #startScreenSharingWithPreferredExtension:groupId:} 开启内部采集。
 *       + 本地可调用 setLocalVideoRenderer:forUserId: 函数设置本地屏幕共享视图。  <br>
 *       + 也可通过注册 setVideoFrameObserver:{@link #setVideoFrameObserver:} 视频回调对象，监听
 * onLocalScreenFrame:{@link #ByteRTCVideoFrameObserver#onLocalScreenFrame:}本地屏幕视频回调事件和 onRemoteScreenFrame:user:room:{@link
 * #ByteRTCVideoFrameObserver#onRemoteScreenFrame:user:room:} 远端屏幕共享视频回调事件来获取原始数据。  <br>
 */
- (int)publishScreen;
/** 
 * @type api
 * @region 屏幕共享
 * @author liyi.000
 * @brief 在当前所在房间内发布本地屏幕共享音视频流
 * @param type 媒体流类型，用于指定发布屏幕音频/视频，参看 ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}。
 * @return  <br>
 *       + 0: 发布成功 <br>
 *       + -1: 发布失败
 * @notes <br>
 *        + 调用 setUserVisibility:{@link #ByteRTCRoom#setUserVisibility:} 方法将自身设置为不可见后无法调用该方法，需将自身切换至可见后方可调用该方法发布屏幕流。 <br>
 *        + 调用该方法后，房间中的所有远端用户会收到 rtcRoom:onUserPublishScreen:type:{@link #ByteRTCRoomDelegate#rtcRoom:onUserPublishScreen:type:} 回调，其中成功收到音频流的远端用户会收到 rtcRoom:onFirstRemoteAudioFrame:{@link #ByteRTCRoomDelegate#rtcRoom:onFirstRemoteAudioFrame:} 回调，订阅了视频流的远端用户会收到 rtcRoom:onFirstRemoteVideoFrameDecoded:withFrameInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onFirstRemoteVideoFrameDecoded:withFrameInfo:} 回调。<br>
 *        + 如果你需要向多个房间发布流，调用 startForwardStreamToRooms:{@link #ByteRTCRoom#startForwardStreamToRooms:}。  <br>
 *        + 调用 unpublishScreen:{@link #ByteRTCRoom#unpublishScreen:} 取消发布。
 */
- (int)publishScreen:(ByteRTCMediaStreamType)type;

/** 
 * @hidden
 * @deprecated since 336.1
 * @type api
 * @region 多房间
 * @author liyi.000
 * @brief 停止发布本地屏幕共享流到房间。
 * @notes <br>
 *        + 调用此方法后，远端会收到 rtcRoom:didStreamRemoved:stream:reason:{@link #ByteRTCRoomDelegate#rtcRoom:didStreamRemoved:stream:reason:} 回调。<br>
 *        + 要发布本地屏幕视频流到指定房间，可以调用 publishScreen:{@link #publishScreen:}
 */
- (int)unpublishScreen;
/** 
 * @type api
 * @region 屏幕共享
 * @author liyi.000
 * @brief 停止将本地屏幕共享音视频流发布到当前所在房间中
 * @param type 媒体流类型，用于指定停止发布屏幕音频/视频，参看 ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}
 * @return <br>
 *      + 0: 停止发布成功 <br>
 *      + -1: 停止发布失败
 * @notes <br>
 *        + 调用 publishScreen:{@link #ByteRTCRoom#publishScreen:} 发布屏幕流后，你需调用此接口停止发布。 <br>
 *        + 调用此方法停止发布屏幕音视频流后，房间中的其他用户将会收到 rtcRoom:onUserUnPublishScreen:type:reason:{@link #ByteRTCRoomDelegate#rtcRoom:onUserUnPublishScreen:type:reason:} 回调。
 */
- (int)unpublishScreen:(ByteRTCMediaStreamType)type;

/** 
 * @hidden
 * @deprecated since 326.1, use subscribeUserStream instead
 * @type api
 * @region 多房间
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
 * rtcRoom:onStreamAdd:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamAdd:} 回调通知；2.当房间内音视频流停止发布时，本地会收到 rtcRoom:didStreamRemoved:stream:reason:{@link #ByteRTCRoomDelegate#rtcRoom:didStreamRemoved:stream:reason:}
 * 回调通知。通过这两个回调用户可以获得当前房间中的音视频流信息，并在需要时调用此方法订阅该音视频流。  <br>
 */
- (int)subscribeStream:(NSString *_Nonnull)userId subscribeConfig:(ByteRTCSubscribeConfig *_Nonnull)info
DEPRECATED_MSG_ATTRIBUTE("Please use subscribeUserStream");

/** 
 * @hidden
 * @deprecated since 336.1, use subscribeStream, unsubscribeStream, subscribeScreen and unsubscribeScreen instead.
 * @type api
 * @region 多房间
 * @author shenpengliang
 * @brief 订阅房间内指定的远端音视频流。  <br>
 *        无论是自动订阅还是手动订阅模式，你都可以调用此方法按需订阅房间中的音视频流。  <br>
 *        该方法也可用于更新已经订阅的流的属性、媒体类型等配置。
 * @param userId 指定订阅的远端发布音视频流的用户 ID 。  <br>
 * @param streamType 流属性，用于指定订阅主流/屏幕流，参看 ByteRTCStreamIndex{@link #ByteRTCStreamIndex} 。  <br>
 * @param mediaType 媒体类型，用于指定订阅音/视频，参看 ByteRTCSubscribeMediaType{@link #ByteRTCSubscribeMediaType}。<br>
 * @param videoConfig 视频订阅配置，参看 ByteRTCSubscribeVideoConfig{@link #ByteRTCSubscribeVideoConfig}。<br>
 * @notes <br>
 *        + 你必须通过 rtcRoom:onStreamAdd:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamAdd:} 和 rtcRoom:didStreamRemoved:stream:reason:{@link #ByteRTCRoomDelegate#rtcRoom:didStreamRemoved:stream:reason:} 两个回调获取当前房间里的音视频流信息，并调用本方法按需订阅流或修改订阅配置。  <br>
 *        + 若订阅失败，你会收到 rtcEngine:onError:{@link #ByteRTCEngineDelegate#rtcEngine:onError:} 回调通知，具体失败原因参看 ByteRTCErrorCode{@link #ByteRTCErrorCode}。
 *        + 若调用 pauseAllSubscribedStream:{@link #ByteRTCRoom#pauseAllSubscribedStream:} 暂停接收远端音视频流，此时仍可使用该方法对暂停接收的流进行设置，你会在调用 resumeAllSubscribedStream:{@link #ByteRTCRoom#resumeAllSubscribedStream:} 恢复接收流后收到修改设置后的流。  <br>
 */
- (void)subscribeUserStream:(NSString *_Nonnull)userId streamType:(ByteRTCStreamIndex)streamType mediaType:(ByteRTCSubscribeMediaType)mediaType videoConfig:(ByteRTCSubscribeVideoConfig *_Nonnull)videoConfig;
/** 
 * @type api
 * @region 房间管理
 * @author liuzhiqiang
 * @brief 订阅房间内指定的通过摄像头/麦克风采集的媒体流。  <br>
 *        该方法对自动订阅和手动订阅模式均适用。
 * @param userId 指定订阅的远端发布音视频流的用户 ID。
 * @param mediaStreamType 媒体流类型，用于指定订阅音频/视频。参看 ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}。
 * @notes  <br>
 *        + 你必须先通过 rtcRoom:onUserPublishStream:type:{@link #ByteRTCRoomDelegate#rtcRoom:onUserPublishStream:type:} 回调获取当前房间里的远端摄像头音视频流信息，然后调用本方法按需订阅。  <br>
 *        + 调用该方法后，你会收到 rtcRoom:onStreamSubscribed:userId:subscribeConfig:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamSubscribed:userId:subscribeConfig:} 通知方法调用结果。  <br>
 *        + 关于其他调用异常，你会收到 rtcRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamStateChanged:withUid:state:extraInfo:} 回调通知，具体异常原因参看 ByteRTCErrorCode{@link #ByteRTCErrorCode}。
 */
- (void)subscribeStream:(NSString *_Nonnull)userId mediaStreamType:(ByteRTCMediaStreamType)mediaStreamType;
/** 
 * @type api
 * @region 房间管理
 * @author liuzhiqiang
 * @brief 取消订阅房间内指定的通过摄像头/麦克风采集的媒体流。  <br>
 *        该方法对自动订阅和手动订阅模式均适用。
 * @param userId 指定取消订阅的远端发布音视频流的用户 ID。
 * @param mediaStreamType 媒体流类型，用于指定取消订阅音频/视频。参看 ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}。
 * @notes  <br>
 *        + 调用该方法后，你会收到 rtcRoom:onStreamSubscribed:userId:subscribeConfig:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamSubscribed:userId:subscribeConfig:} 通知流的退订结果。  <br>
 *        + 关于其他调用异常，你会收到 rtcRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamStateChanged:withUid:state:extraInfo:} 回调通知，具体失败原因参看 ByteRTCErrorCode{@link #ByteRTCErrorCode}。
 */
- (void)unSubscribeStream:(NSString *_Nonnull)userId mediaStreamType:(ByteRTCMediaStreamType)mediaStreamType;
/** 
 * @type api
 * @region 房间管理
 * @author liuzhiqiang
 * @brief 订阅房间内指定的远端屏幕共享音视频流。  <br>
 *        该方法对自动订阅和手动订阅模式均适用。
 * @param userId 指定订阅的远端发布屏幕流的用户 ID。
 * @param mediaStreamType 媒体流类型，用于指定订阅音频/视频。参看 ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}。
 * @notes  <br>
 *        + 你必须先通过 rtcRoom:onUserPublishScreen:type:{@link #ByteRTCRoomDelegate #rtcRoom:onUserPublishScreen:type:} 回调获取当前房间里的远端屏幕流信息，然后调用本方法按需订阅。  <br>
 *        + 调用该方法后，你会收到 rtcRoom:onStreamSubscribed:userId:subscribeConfig:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamSubscribed:userId:subscribeConfig:} 通知流的订阅结果。  <br>
 *        + 关于其他调用异常，你会收到 rtcRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamStateChanged:withUid:state:extraInfo:} 回调通知，具体异常原因参看 ByteRTCErrorCode{@link #ByteRTCErrorCode}。
 */
- (void)subscribeScreen:(NSString *_Nonnull)userId mediaStreamType:(ByteRTCMediaStreamType)mediaStreamType;
/** 
 * @type api
 * @region 房间管理
 * @author liuzhiqiang
 * @brief 取消订阅房间内指定的远端屏幕共享音视频流。  <br>
 *        该方法对自动订阅和手动订阅模式均适用。
 * @param userId 指定取消订阅的远端发布屏幕流的用户 ID。
 * @param mediaStreamType 媒体流类型，用于指定取消订阅音频/视频。参看 ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}。
 * @notes  <br>
 *        + 调用该方法后，你会收到 rtcRoom:onStreamSubscribed:userId:subscribeConfig:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamSubscribed:userId:subscribeConfig:} 通知流的退订结果。  <br>
 *        + 关于其他调用异常，你会收到 rtcRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamStateChanged:withUid:state:extraInfo:} 回调通知，具体失败原因参看 ByteRTCErrorCode{@link #ByteRTCErrorCode}。
 */
- (void)unSubscribeScreen:(NSString *_Nonnull)userId mediaStreamType:(ByteRTCMediaStreamType)mediaStreamType;

 /** 
  * @hidden
  * @deprecated since 326.1, use subscribeUserStream instead
  * @type api
  * @region 多房间
  * @author shenpengliang
  * @brief 停止订阅指定的房间内远端音视频流。  <br>
  *        关闭自动订阅功能，使用手动订阅模式时,调用此方法停止订阅房间中的音视频流。  <br>
  *        要关闭自动订阅功能，启动手动订阅模式时，你必须在加入房间前调用 enableAutoSubscribe:videoMode:{@link #enableAutoSubscribe:videoMode:}。<br>
  * @param userId 发布远端音视频流的用户 ID 。  <br>
  * @param isScreen 订阅的流是否是屏幕共享流。  <br>
  * @notes <br>
  *         + 要开始订阅，参看 subscribeUserStream:streamType:mediaType:videoConfig:{@link #ByteRTCRoom#subscribeUserStream:streamType:mediaType:videoConfig:} <br>
  *         + 不管是否订阅了指定的远端音视频流，都可以调用此方法停止订阅。停止订阅的 userId 无效或未订阅时，SDK 不会做任何处理，没有负面影响。  <br>
  */
 - (int)unSubscribeStream:(NSString *_Nonnull)userId isScreen:(BOOL)isScreen
DEPRECATED_MSG_ATTRIBUTE("Please use subscribeUserStream");

/** 
 * @hidden
 * @deprecated since 326.1, use joinRoomBytoken with MultiRoomConfig instead
 * @type api
 * @region 多房间
 * @author shenpengliang
 * @brief 设置订阅模式。  <br>
 *        用户调用此方法设置房间中音视频流的订阅模式。SDK 默认使用自动订阅模式。<br>
 *        如需开启手动订阅功能，建议在调用 JoinChannel{@link #JoinChannel} 方法加入房间前设置完成。  <br>
 * @param audioMode 音频流的订阅模式。详见枚举类型 ByteRTCSubscribeMode{@link #ByteRTCSubscribeMode}。  <br>
 * @param videoMode 视频流的订阅模式。详见枚举类型 ByteRTCSubscribeMode{@link #ByteRTCSubscribeMode}。  <br>
 * @notes  <br>
 *       + SDK 提供两种订阅模式：1.自动订阅模式，开启自动订阅功能时，SDK 自动帮助用户订阅房间中所有其他用户发布的音视频流；2.手动订阅模式，关闭自动订阅功能时，SDK不会自动订阅房间内的音视频流，只通过 rtcRoom:onStreamAdd:{@link #ByteRTCRoomDelegate#rtcRoom:onStreamAdd:} 和 rtcRoom:didStreamRemoved:stream:reason:{@link #ByteRTCRoomDelegate#rtcRoom:didStreamRemoved:stream:reason:} 回调通知用户当前所在房间中有哪些音视频流，由用户根据自己的需要调用 subscribeStream{@link #subscribeStream} 方法手动订阅其他用户发布的音视频流。  <br>
 *       + SDK 可以分别对音频/视频设置订阅模式。  <br>
 */
- (int)enableAutoSubscribe:(ByteRTCSubscribeMode)audioMode videoMode:(ByteRTCSubscribeMode)videoMode
DEPRECATED_MSG_ATTRIBUTE("Please use joinRoomByToken with multiRoomConfig");

 /** 
  * @hidden
  * @deprecated since 323.1, use enableAudioPropertiesReport instead
  * @type api
  * @region 多房间
  * @author wangjunzheng
  * @brief 开启/关闭房间内音量提示。默认关闭。<br>
  *        开启音量提示后，将按设置的时间间隔收到本地采集音量或订阅的远端用户的音量信息回调。
  *        关于回调的具体信息，参看 rtcEngine:onAudioVolumeIndication:totalRemoteVolume:{@link #rtcEngine:onAudioVolumeIndication:totalRemoteVolume:}。
  * @param interval 收到音量提示回调的时间间隔  <br>
  *                + ≤ 0：禁用音量提示功能。  <br>
  *                + > 0：启用音量提示功能，并设置收到音量提示回调的时间间隔。单位为毫秒。<br>
  *                建议设置为大于等于 200 毫秒；小于 10 毫秒时，行为未定义。
  */
 - (void)setAudioVolumeIndicationInterval:(NSInteger)interval;

/** 
 * @type api
 * @region 音频管理
 * @author majun.lvhiei
 * @brief 调节来自指定远端用户的音频播放音量，默认为 100。
 * @param uid 音频来源的远端用户 ID
 * @param volume 音频播放音量值和原始音量的比值，范围是 [0, 400]，单位为 %，自带溢出保护。  <br>
 *        为保证更好的通话质量，建议将 volume 值设为 [0,100]。  <br>
 *              + 0: 静音  <br>
 *              + 100: 原始音量  <br>
 *              + 400: 最大可为原始音量的 4 倍(自带溢出保护)  <br>
 */
- (void)setRemoteAudioPlaybackVolume:(NSString* _Nonnull)uid volume:(int)volume;

/** 
 * @hidden
 * @deprecated since 326.1, use pauseAllSubscribedStream/resumeAllSubscribedStream instead
 * @type api
 * @region 多房间
 * @author shenpengliang
 * @brief 设置对来自远端的所有音频流的接收状态。默认为接收。
 * @param muteState 接收状态。参看：ByteRTCMuteState{@link #ByteRTCMuteState}
 * @notes 本方法只影响本地是否接收远端音频流，并不影响远端音频设备的采集发送功能。
 */
- (void)muteAllRemoteAudio:(ByteRTCMuteState)muteState
DEPRECATED_MSG_ATTRIBUTE("Please use pauseAllSubscribedStream or resumeAllSubscribedStream");

/** 
 * @type api
 * @region 多房间
 * @author shenpengliang
 * @brief 暂停接收来自远端的媒体流
 * @param mediaType 媒体流类型，指定需要暂停接收音频还是视频流，参看 ByteRTCPauseResumControlMediaType{@link #ByteRTCPauseResumControlMediaType}
 * @notes <br>
 *        + 该方法仅暂停远端流的接收，并不影响远端流的采集和发送；  <br>
 *        + 该方法不改变用户的订阅状态以及订阅流的属性。  <br>
 *        + 若想恢复接收远端流，需调用 resumeAllSubscribedStream:{@link #ByteRTCRoom#resumeAllSubscribedStream:}。
 */
- (void)pauseAllSubscribedStream:(ByteRTCPauseResumControlMediaType) mediaType;

/** 
 * @type api
 * @region 多房间
 * @author shenpengliang
 * @brief 恢复接收来自远端的媒体流
 * @param mediaType 媒体流类型，指定需要暂停接收音频还是视频流，参看 ByteRTCPauseResumControlMediaType{@link #ByteRTCPauseResumControlMediaType}
 * @notes <br>
 *        + 该方法仅恢复远端流的接收，并不影响远端流的采集和发送；  <br>
 *        + 该方法不改变用户的订阅状态以及订阅流的属性。
 */
- (void)resumeAllSubscribedStream:(ByteRTCPauseResumControlMediaType) mediaType;

/** 
 * @hidden
 * @deprecated since 326.1, use subscribeUserStream instead
 * @type api
 * @region 多房间
 * @author shenpengliang
 * @brief 设置对来自远端指定用户的音频流的接收状态。默认为接收。
 * @param userId 指定远端用户的 ID
 * @param muteState 接收状态。参看：ByteRTCMuteState{@link #ByteRTCMuteState}
 * @notes 本方法只影响本地是否接收远端音频流，并不影响远端音频设备的采集发送功能。
 */
- (void)muteRemoteAudio:(NSString *_Nonnull)userId muteState:(ByteRTCMuteState)muteState
DEPRECATED_MSG_ATTRIBUTE("Please use subscribeUserStream");

/** 
 * @hidden
 * @deprecated since 326.1, use pauseAllSubscribedStream/resumeAllSubscribedStream instead
 * @type api
 * @region 多房间
 * @author shenpengliang
 * @brief 设置是否接收所有远端视频流
 * @param  muteState 参看 ByteRTCMuteState{@link #ByteRTCMuteState}   <br>
 *       + true：停止播放  <br>
 *       + false：开启播放  <br>
 * @notes 本方法不影响远端视频采集和发送状态
 */
- (int)muteAllRemoteVideo:(ByteRTCMuteState)muteState
DEPRECATED_MSG_ATTRIBUTE("Please use pauseAllSubscribedStream or resumeAllSubscribedStream");

/** 
 * @hidden
 * @deprecated since 326.1, use subscribeUserStream instead
 * @type api
 * @region 多房间
 * @author shenpengliang
 * @brief 设置是否播放远端视频流
 * @param uid 视频来源的远端用户 ID
 * @param  muteState 参看 ByteRTCMuteState{@link #ByteRTCMuteState}   <br>
 *       + true：停止播放  <br>
 *       + false：开启播放  <br>
 * @notes 本方法不影响远端视频采集和发送状态
 */
- (int)muteRemoteVideo:(NSString * _Nonnull)uid
                  mute:(ByteRTCMuteState)muteState DEPRECATED_MSG_ATTRIBUTE("Please use subscribeUserStream");

/** 
 * @type api
 * @region 多房间
 * @author wanghaoxu
 * @brief 新增转推直播任务，并设置合流的视频视图布局和音频属性。  <br>
 *        同一个任务中转推多路直播流时，SDK 会先将多路流合成一路流，然后再进行转推。
 * @param task_id 转推直播任务 ID。<br>
 *               你可以在同一房间内发起多个转推直播任务，并用不同的任务 ID 加以区。当你需要发起多个转推直播任务时，应使用多个 ID；当你仅需发起一个转推直播任务时，建议使用空字符串。
 * @param transcoding 转推直播配置参数，详见 ByteRTCLiveTranscoding{@link #ByteRTCLiveTranscoding}。
 * @param observer 端云一体转推直播观察者。详见 LiveTranscodingDelegate{@link #LiveTranscodingDelegate}。  <br>
 *        通过注册 observer 接收转推直播相关的回调。
 * @notes  <br>
 *       + 调用该方法后，启动结果和推流过程中的错误均会通过回调 onStreamMixingEvent:taskId:error:mixType:{@link #LiveTranscodingDelegate#onStreamMixingEvent:taskId:error:mixType:} 通知用户。
 *       + 调用 stopLiveTranscoding:{@link #ByteRTCRoom#stopLiveTranscoding:} 停止转推直播
 */
- (int)startLiveTranscoding:(NSString * _Nonnull)task_id transcoding:(ByteRTCLiveTranscoding *_Nullable)transcoding observer:(id<LiveTranscodingDelegate> _Nullable)observer;

/** 
 * @type api
 * @region 多房间
 * @brief 停止转推直播。
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
 * @brief 更新转推直播参数。  <br>
 *        开启转推直播功能后，你可以使用此方法更新合流转推功能配置参数。
 * @param task_id 转推直播任务 ID。指定想要更新参数设置的转推直播任务。
 * @param transcoding 配置参数，详见 ByteRTCLiveTranscoding{@link #ByteRTCLiveTranscoding} 。
 * @return 方法调用结果。  <br>
 *         +  0：方法调用成功  <br>
 *         + < 0：方法调用失败
 */
- (int)updateLiveTranscoding:(NSString *_Nonnull)task_id transcoding:(ByteRTCLiveTranscoding *_Nonnull)transcoding;

 /** 
  * @type api
  * @region 多房间
  * @author sunhang.io
  * @brief 渲染来自指定远端用户 uid 的视频流时，设置使用的视图和渲染模式。  <br>
  *        如果需要解除视频的绑定视图，把 canvas 设置为空。
  * @notes  <br>
  *       + 实际使用时，你可以在收到回调 rtcRoom:onUserJoined:elapsed:{@link #ByteRTCRoomDelegate#rtcRoom:onUserJoined:elapsed:} 或 rtcRoom:onFirstRemoteVideoFrameRendered:withFrameInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onFirstRemoteVideoFrameRendered:withFrameInfo:} 时获得远端用户 uid。
  *         这两个回调的差别是：如果启用了视频录制功能，视频录制服务会作为一个哑客户端加入房间，因此其他客户端会收到对应的 rtcRoom:onUserJoined:elapsed:{@link #ByteRTCRoomDelegate#rtcRoom:onUserJoined:elapsed:} 回调；
  *         而不会收到 rtcRoom:onFirstRemoteVideoFrameRendered:withFrameInfo:{@link #ByteRTCRoomDelegate#rtcRoom:onFirstRemoteVideoFrameRendered:withFrameInfo:} 回调。你不应给录制的哑客户端绑定视图（因为它不会发送视频流）。
  *       + 你应在加入房间后，绑定视图。退出房间后，此设置失效。
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
  * @region 多房间
  * @author hanchenchen.c
  * @brief 给房间内指定的用户发送文本消息（P2P）。
  * @param userId  <br>
  *        消息接收用户的 ID
  * @param message  <br>
  *        发送的文本消息内容。  <br>
  *        消息不超过 62KB。
  * @return 这次发送消息的编号，从 1 开始递增。
  * @notes  <br>
  *      + 在发送房间内文本消息前，必须先调用 joinRoomByToken:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoomByToken:userInfo:roomConfig:} 加入房间。  <br>
  *      + 调用该函数后会收到一次 rtcRoom:onUserMessageSendResult:error:{@link #ByteRTCRoomDelegate#rtcRoom:onUserMessageSendResult:error:} 回调，通知消息发送方发送成功或失败。  <br>
  *      + 若文本消息发送成功，则 uid 所指定的用户会收到 rtcRoom:onUserMessageReceived:message:{@link #ByteRTCRoomDelegate#rtcRoom:onUserMessageReceived:message:} 回调。
  */
 - (int64_t)sendUserMessage:(NSString *_Nonnull)userId message:(NSString *_Nonnull)message;

 /** 
  * @type api
  * @region 多房间
  * @author hanchenchen.c
  * @brief 给房间内指定的用户发送二进制消息（P2P）。
  * @param uid  <br>
  *        消息接收用户的 ID
  * @param message  <br>
  *        发送的二进制消息内容  <br>
  *        消息不超过 46KB。
  * @return 这次发送消息的编号，从 1 开始递增。
  * @notes  <br>
  *      + 在发送房间内二进制消息前，必须先调用 joinRoomByToken:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoomByToken:userInfo:roomConfig:} 加入房间。  <br>
  *      + 调用该函数后会收到一次 rtcRoom:onUserMessageSendResult:error:{@link #ByteRTCRoomDelegate#rtcRoom:onUserMessageSendResult:error:} 回调，通知消息发送方发送成功或失败；  <br>
  *      + 若二进制消息发送成功，则 uid 所指定的用户会收到 rtcRoom:onUserBinaryMessageReceived:message:{@link #ByteRTCRoomDelegate#rtcRoom:onUserBinaryMessageReceived:message:} 回调。
  */
 - (int64_t)sendUserBinaryMessage:(NSString * _Nonnull)uid message:(NSData * _Nonnull)message;

 /** 
  * @type api
  * @region 多房间
  * @author hanchenchen.c
  * @brief 给房间内的所有其他用户发送文本消息。
  * @param message  <br>
  *        发送的文本消息内容。  <br>
  *        消息不超过 62KB。
  * @return 这次发送消息的编号，从 1 开始递增。
  * @notes  <br>
  *      + 在发送房间内文本消息前，必须先调用 joinRoomByToken:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoomByToken:userInfo:roomConfig:} 加入房间。  <br>
  *      + 调用该函数后会收到一次 rtcRoom:onRoomMessageSendResult:error:{@link #ByteRTCRoomDelegate#rtcRoom:onRoomMessageSendResult:error:} 回调，通知消息发送方发送成功或失败；  <br>
  *      + 若文本消息发送成功，则房间内所有远端用户会收到 rtcRoom:onRoomMessageReceived:message:{@link #ByteRTCRoomDelegate#rtcRoom:onRoomMessageReceived:message:} 回调。
  */
 - (int64_t)sendRoomMessage:(NSString *_Nonnull)message;

 /** 
  * @type api
  * @region 多房间
  * @author hanchenchen.c
  * @brief 给房间内的所有其他用户发送二进制消息。
  * @param message  <br>
  *        用户发送的二进制广播消息  <br>
  *        消息不超过 46KB。
  * @return 这次发送消息的编号，从 1 开始递增。
  * @notes  <br>
  *      + 在房间内广播二进制消息前，必须先调用 joinRoomByToken:userInfo:roomConfig:{@link #ByteRTCRoom#joinRoomByToken:userInfo:roomConfig:} 加入房间。  <br>
  *      + 调用该函数后会收到一次 rtcRoom:onRoomMessageSendResult:error:{@link #ByteRTCRoomDelegate#rtcRoom:onRoomMessageSendResult:error:} 回调，通知消息发送方发送成功或失败；  <br>
  *      + 若二进制消息发送成功，则房间内所有用户会收到 rtcRoom:onRoomBinaryMessageReceived:message:{@link #ByteRTCRoomDelegate#rtcRoom:onRoomBinaryMessageReceived:message:} 回调。
  */
 - (int64_t)sendRoomBinaryMessage:(NSData *  _Nonnull)message;

#pragma mark ForwardStream
    /** 
     * @type api
     * @region 多房间
     * @author wunailiang
     * @brief 开始跨房间转发媒体流。
     *        在用户进入房间后调用本接口，实现向多个房间转发媒体流，适用于跨房间连麦等场景。<br>
     * @param configurations 跨房间媒体流转发指定房间的信息。参看 ForwardStreamConfiguration{@link #ForwardStreamConfiguration}。
     * @return  <br>
     *        0: 方法调用成功
     *        <0: 方法调用失败  <br>
     * @notes <br>
     *        + 调用本方法后，将在本端触发 rtcRoom:onForwardStreamStateChanged:{@link #ByteRTCRoomDelegate#rtcRoom:onForwardStreamStateChanged:} 回调。
     *        + 调用本方法后，你可以通过监听 rtcRoom:onForwardStreamEvent:{@link #ByteRTCRoomDelegate#rtcRoom:onForwardStreamEvent:} 回调来获取各个目标房间在转发媒体流过程中的相关事件。
     *        + 开始转发后，目标房间中的用户将接收到本地用户进房 rtcRoom:onUserJoined:elapsed:{@link #ByteRTCRoomDelegate#rtcRoom:onUserJoined:elapsed:} 和发流 rtcRoom:onUserJoined:elapsed:{@link #ByteRTCRoomDelegate#rtcRoom:onUserJoined:elapsed:} 的回调。
     *        + 调用本方法后，可以调用 updateForwardStreamToRooms:{@link #ByteRTCRoom#updateForwardStreamToRooms:} 更新目标房间信息，例如，增加或减少目标房间等。
     *        + 调用本方法后，可以调用 stopForwardStreamToRooms{@link #ByteRTCRoom#stopForwardStreamToRooms} 停止向所有房间转发媒体流。
     *        + 调用本方法后，可以调用 pauseForwardStreamToAllRooms{@link #ByteRTCRoom#pauseForwardStreamToAllRooms} 暂停向所有房间转发媒体流。
     */
    - (int)startForwardStreamToRooms:(NSArray <ForwardStreamConfiguration *> * _Nullable)configurations;
    /** 
     * @type api
     * @region 多房间
     * @author wunailiang
     * @brief 更新跨房间媒体流转发信息。<br>
     *        通过 startForwardStreamToRooms:{@link #ByteRTCRoom#startForwardStreamToRooms:} 发起媒体流转发后，可调用本方法增加或者减少目标房间，或更新房间密钥。
     *        调用本方法增加或删减房间后，将在本端触发 rtcRoom:onForwardStreamStateChanged:{@link #ByteRTCRoomDelegate#rtcRoom:onForwardStreamStateChanged:} 回调，包含发生了变动的目标房间中媒体流转发状态。
     * @param configurations 跨房间媒体流转发目标房间信息。参看 ForwardStreamConfiguration{@link #ForwardStreamConfiguration}。
     * @return  <br>
     *        0: 方法调用成功  <br>
     *        <0: 方法调用失败  <br>
     * @notes <br>
     *        + 增加目标房间后，新增目标房间中的用户将接收到本地用户进房 rtcRoom:onUserJoined:elapsed:{@link #ByteRTCRoomDelegate#rtcRoom:onUserJoined:elapsed:} 和发布 rtcRoom:onUserJoined:elapsed:{@link #ByteRTCRoomDelegate#rtcRoom:onUserJoined:elapsed:} 的回调。
     *        + 删减目标房间后，原目标房间中的用户将接收到本地用户停止发布 rtcRoom:onUserUnPublishStream:type:reason: {@link #ByteRTCRoomDelegate#rtcRoom:onUserUnPublishStream:type:reason:} 和退房 rtcRoom:onUserLeave:reason:{@link #ByteRTCRoomDelegate#rtcRoom:onUserLeave:reason:} 的回调。
     */
    - (int)updateForwardStreamToRooms:(NSArray <ForwardStreamConfiguration *> * _Nullable)configurations;
    /** 
     * @type api
     * @region 多房间
     * @author wunailiang
     * @brief 停止跨房间媒体流转发。
     *        通过 startForwardStreamToRooms:{@link #ByteRTCRoom#startForwardStreamToRooms:} 发起媒体流转发后，可调用本方法停止向所有目标房间转发媒体流。
     * @notes <br>
     *        + 调用本方法后，将在本端触发 rtcRoom:onForwardStreamStateChanged:{@link #ByteRTCRoomDelegate#rtcRoom:onForwardStreamStateChanged:} 回调。
     *        + 调用本方法后，原目标房间中的用户将接收到本地用户停止发布 rtcRoom:onUserUnPublishStream:type:reason: {@link #ByteRTCRoomDelegate#rtcRoom:onUserUnPublishStream:type:reason:} 和退房 rtcRoom:onUserLeave:reason:{@link #ByteRTCRoomDelegate#rtcRoom:onUserLeave:reason:} 的回调。
     *        + 如果需要停止向指定的房间转发媒体流，请调用 updateForwardStreamToRooms:{@link #ByteRTCRoom#updateForwardStreamToRooms:} 更新房间信息。
     *        + 如果需要暂停转发，请调用 pauseForwardStreamToAllRooms{@link #ByteRTCRoom#pauseForwardStreamToAllRooms}，并在之后随时调用 resumeForwardStreamToAllRooms{@link #ByteRTCRoom#resumeForwardStreamToAllRooms} 快速恢复转发。
     */
    - (void)stopForwardStreamToRooms;
    /** 
     * @type api
     * @region 多房间
     * @author wunailiang
     * @brief 暂停跨房间媒体流转发。
     *        通过 startForwardStreamToRooms:{@link #ByteRTCRoom#startForwardStreamToRooms:} 发起媒体流转发后，可调用本方法暂停向所有目标房间转发媒体流。
     *        调用本方法暂停向所有目标房间转发后，你可以随时调用 resumeForwardStreamToAllRooms{@link #ByteRTCRoom#resumeForwardStreamToAllRooms} 快速恢复转发。
     * @notes 调用本方法后，目标房间中的用户将接收到本地用户停止发布 rtcRoom:onUserUnPublishStream:type:reason: {@link #ByteRTCRoomDelegate#rtcRoom:onUserUnPublishStream:type:reason:} 和退房 rtcRoom:onUserLeave:reason:{@link #ByteRTCRoomDelegate#rtcRoom:onUserLeave:reason:} 的回调。
     */
     - (void)pauseForwardStreamToAllRooms;
    /** 
     * @type api
     * @region 多房间
     * @author wunailiang
     * @brief 恢复跨房间媒体流转发。
     *        调用 pauseForwardStreamToAllRooms{@link #ByteRTCRoom#pauseForwardStreamToAllRooms} 暂停转发之后，调用本方法恢复向所有目标房间转发媒体流。
     * @notes <br>
     *        目标房间中的用户将接收到本地用户进房 rtcRoom:onUserJoined:elapsed:{@link #ByteRTCRoomDelegate#rtcRoom:onUserJoined:elapsed:} 和发布 rtcRoom:onUserJoined:elapsed:{@link #ByteRTCRoomDelegate#rtcRoom:onUserJoined:elapsed:} 的回调。
     */
    - (void)resumeForwardStreamToAllRooms;

/** 
 * @type api
 * @author qipengxiang
 * @brief 发布一路公共流<br>
 *        公共流是指不属于任何房间，也不属于任何用户的媒体流。使用同一 `appID` 的用户，可以调用 startPlayPublicStream:{@link ByteRTCRoom#startPlayPublicStream:} 获取和播放指定的公共流。
 * @param publicStreamId 公共流 ID。<br>
 * @param publicStreamParam 推公共流配置参数。详见 ByteRTCPublicStreaming{@link #ByteRTCPublicStreaming}。
 *              一路公共流可以包含多路房间内的媒体流，按照指定的布局方式进行聚合。<br>
 *              如果指定的媒体流还未发布，则公共流将在指定流开始发布后实时更新。
 * @return
 *        + 0: 成功。同时将收到 rtcEngine:onPushPublicStreamResult:errorCode:{@link #ByteRTCEngineDelegate#rtcEngine:onPushPublicStreamResult:errorCode:} 回调。<br>
 *        + !0: 失败。当参数不合法或参数为空，调用失败。<br>
 * @notes  <br>
 *        + 只有房间模式为直播模式( `CHANNEL_PROFILE_LIVE_BROADCASTING` )的用户才能调用此方法。
 *        + 同一用户使用同一公共流 ID 多次调用本接口无效。如果你希望更新公共流参数，调用 updatePublicStreamParam:withLayout:{@link ByteRTCRoom#updatePublicStreamParam:withLayout:} 接口。<br>
 *        + 不同用户使用同一公共流 ID 多次调用本接口时，RTC 将使用最后一次调用时传入的参数更新公共流。<br>
 *        + 使用不同的 ID 多次调用本接口可以发布多路公共流。<br>
 *        + 调用 stopPushPublicStream:{@link ByteRTCRoom#stopPushPublicStream:} 停止发布公共流。
 */
- (int)startPushPublicStream:(NSString * _Nonnull)publicStreamId withLayout:(ByteRTCPublicStreaming *_Nullable)publicStreamParam;

/** 
 * @type api
 * @author qipengxiang
 * @brief 停止发布当前用户发布的公共流<br>
 *        关于发布公共流，查看 startPushPublicStream:withLayout:{@link #ByteRTCRoom#startPushPublicStream:withLayout:}。
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
 *        关于发布公共流，查看 startPushPublicStream:withLayout:{@link #ByteRTCRoom#startPushPublicStream:withLayout:}。
 * @param publicStreamId 公共流ID<br>
 *              指定的流必须为当前用户所发布的。
 * @param publicStreamParam 推公共流配置参数。详见 ByteRTCPublicStreaming{@link #ByteRTCPublicStreaming}。
 * @return
 *        + 0: 成功<br>
 *        + !0: 失败<br>
 */
- (int)updatePublicStreamParam:(NSString * _Nonnull)publicStreamId withLayout:(ByteRTCPublicStreaming *_Nullable)publicStreamParam;

/** 
 * @type api
 * @region 范围语音
 * @author chuzhongtao
 * @brief 获取范围语音接口实例。
 * @return 方法调用结果： <br>
 *        + ByteRTCRangeAudio：成功，返回一个 ByteRTCRangeAudio{@link #ByteRTCRangeAudio} 实例。  <br>
 *        + NULL：失败，当前 SDK 不支持范围语音功能。
 * @notes 首次调用该方法须在创建房间后、加入房间前。
 */
- (ByteRTCRangeAudio *_Nullable)getRangeAudio;

/** 
 * @type api
 * @region 空间音频
 * @author majun.lvhiei
 * @brief 获取空间音频接口实例。  <br>
 * @return 方法调用结果：  <br>
 *        + ByteRTCSpatialAudio：成功，返回一个 ByteRTCSpatialAudio{@link #ByteRTCSpatialAudio} 实例。  <br>
 *        + NULL：失败，当前 SDK 不支持空间音频功能。
 * @notes  <br>
 *        + 首次调用该方法须在创建房间后、加入房间前。 空间音频相关 API 和调用时序详见[空间音频](https://www.volcengine.com/docs/6348/93903)。 <br>
 *        + 只有在使用支持真双声道播放的设备时，才能开启空间音频效果；  <br>
 *        + 机型性能不足可能会导致音频卡顿，使用低端机时，不建议开启空间音频效果；  <br>
 *        + SDK 最多支持 30 个用户同时开启空间音频功能。
 */
- (ByteRTCSpatialAudio *_Nullable)getSpatialAudio;

@end
