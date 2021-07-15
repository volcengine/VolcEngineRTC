//
//  ByteRtcEngineKit.h
//  ByteRtcEngineKit
//
//  Created by yanchangqing on 2018/8/16.
//  Copyright © 2018年 bytedance. All rights reserved.
//
#import <CoreMedia/CMTime.h>
#if TARGET_OS_IPHONE || TARGET_OS_SIMULATOR
#import <UIKit/UIKit.h>
#elif TARGET_OS_OSX
#import <AppKit/AppKit.h>
#endif

#import "ByteRtcEngineKitDefines.h"

@class ByteRtcEngineKit;
@class ByteRtcRoom;

/**
 *  @type callback
 *  @brief ByteRtcEngineDelegate 协议包含了SDK提供的回调方法，SDK通过代理向应用程序上报一些运行时事件
 */
@protocol ByteRtcEngineDelegate <NSObject>
@optional

#pragma mark SDK common delegate

/**
 * @type callback
 * @region 警告码
 * @brief 发生警告回调。
 * @notes 该回调方法表示SDK运行时出现了（网络或媒体相关的）警告。通常情况下，SDK上报的警告信息App可以忽略，SDK会自动恢复。
 * @param engine 当前 RTCEngine 对象
 * @param Code 警告代码，详情定义见: ByteRtcWarningCode{@link #ByteRtcWarningCode}
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine didOccurWarning:(ByteRtcWarningCode)Code;

/**
 * @type callback
 * @region 错误码
 * @brief 发生错误回调。
 * @notes 表示SDK运行时出现了（网络或媒体相关的）错误。通常情况下，SDK上报的错误意味着SDK无法自动恢复，需要App干预或提示用户。
 * @param engine 当前 RTCEngine 对象
 * @param errorCode 错误代码，详情定义见: ByteRtcErrorCode{@link #ByteRtcErrorCode}
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine didOccurError:(ByteRtcErrorCode)errorCode;

/**
 *  @type callback
 *  @region 网络连接
 *  @brief SDK 当前网络连接类型改变回调。
 *  @param engine ByteRtcEngineKit 对象
 *  @param type SDK 当前的网络连接类型，详见：ByteRtcNetworkType{@link #ByteRtcNetworkType}
 */

- (void) rtcEngine:(ByteRtcEngineKit * _Nonnull)engine networkTypeChangedToType:(ByteRtcNetworkType)type;

#pragma mark local user delegate
/**
 *  @type callback
 *  @region 房间管理
 *  @brief 加入房间回调。
 *         该回调方法表示该用户成功加入了指定的房间。
 *  @param engine ByteRtcEngineKit 对象
 *  @param channel 房间 ID
 *  @param uid 用户 ID
 *  @param elapsed 从调用 joinChannelByKey:channelName:info:uid:{@link #joinChannelByKey:channelName:info:uid:} 方法到加入房间成功所经历的时间间隔（毫秒）
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine didJoinChannel:(NSString * _Nonnull)channel withUid:(nonnull NSString*)uid elapsed:(NSInteger) elapsed;

/**
 *  @type callback
 *  @region 房间管理
 *  @brief 重新加入房间成功。
 *         该回调方法表示该用户成功重连入指定的房间。有时候由于网络状况异常，SDK 可能会失去和服务器的连接，此时 SDK 会自动重试
 *         连接，重连成功后会通过此回调方法通知用户。
 *  @param engine ByteRtcEngineKit 对象
 *  @param channel 房间 ID
 *  @param uid 用户 ID
 *  @param elapsed 从连接断开到重连成功所经历的时间间隔（毫秒）
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine didRejoinChannel:(NSString * _Nonnull)channel withUid:(nonnull NSString*)uid elapsed:(NSInteger) elapsed;

#pragma mark remote user delegate
/**
 *  @type callback
 *  @region 房间管理
 *  @brief 远端用户加入当前房间回调。
 *         1.频道模式为通信模式。如果本端用户已经在房间中，有新的远端用户加入时，SDK 通过此回调方法通知房间中有新用户加入；如果
 *           用户加入房间前，房间中已有其他用户，新加入的用户也会收到这些已有用户的加入房间回调。
 *         2.频道模式为直播、游戏或云游戏模式。则只会回调用户角色为主播或观众加入房间。
 *  @param engine ByteRtcEngineKit 对象
 *  @param uid 新加入的远端用户 ID
 *  @param elapsed 从本端用户调用 joinChannelByKey:channelName:info:uid:{@link #joinChannelByKey:channelName:info:uid:} 加入房间到收到该事件经历的时间（毫秒）
 *  @notes 此回调会被触发的时机如下：
 *         1.通信模式下的用户或其他模式下用户角色为主播、观众的用户调用 joinChannelByKey:channelName:info:uid:{@link #joinChannelByKey:channelName:info:uid:} 方法加入房间。
 *         2.通信模式下的用户或其他模式下用户角色为主播、观众的用户在断网后重连入房间。
 *         3.直播、游戏或云游戏模式下用户角色为静默观众的用户调用 setClientRole:withKey:{@link #setClientRole:withKey:} 方法将用户角色切换至主播或观众。
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine didJoinedOfUid:(nonnull NSString*)uid elapsed:(NSInteger)elapsed;

/**
 *  @type callback
 *  @region 房间管理
 *  @brief 远端用户离开当前房间回调。
 *         提示本端用户有远端用户离开了房间。用户离开房间的原因有两个，即用户主动调用  leaveChannel:{@link #leaveChannel:} 方法离开
 *         房间和超时掉线。
 *  @param engine ByteRtcEngineKit 对象
 *  @param uid 离开的远端用户 ID
 *  @param reason 用户离开的原因，详见枚举类型 ByteRtcUserOfflineReason{@link #ByteRtcUserOfflineReason}
 *  @notes 此回调会被触发的时机如下：
 *         1.通信模式下的用户或其他模式下用户角色为主播、观众的用户调用  leaveChannel:{@link #leaveChannel:} 方法离开房间。
 *         2.直播、游戏或云游戏模式下用户角色为主播或观众的用户调用 setClientRole:withKey:{@link #setClientRole:withKey:} 方法将用户角色切换s至静默观众。
 *         3.远端用户断网且一直未恢复。
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine didOfflineOfUid:(NSString* _Nonnull )uid reason:(ByteRtcUserOfflineReason)reason;

/**
 *  @type callback
 *  @region 房间管理
 *  @brief 房间内远端流移除回调。
 *         房间内的远端用户停止发布音视频流时，本端用户会收到此回调通知。
 *  @param engine ByteRtcEngineKit 对象
 *  @param stream 流的属性，详见数据结构 ByteRtcByteStream{@link #ByteRtcByteStream}
 *  @param reason 远端流移除原因，详见枚举类型 RtcStreamRemoveReason{@link #RtcStreamRemoveReason}
 */
- (void)rtcEngine:(ByteRtcEngineKit *_Nonnull)engine didStreamRemoved:(ByteRtcByteStream *_Nonnull)stream reason:(RtcStreamRemoveReason)reason;

/**
 *  @type callback
 *  @region 房间管理
 *  @brief 房间内新流发布回调。
 *         房间内的远端用户发布新的音视频流时，本端用户会收到此回调通知。
 *  @param engine ByteRtcEngineKit 对象
 *  @param stream 流的属性，详见数据结构 ByteRtcByteStream{@link #ByteRtcByteStream}
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine didStreamAdded:(ByteRtcByteStream* _Nonnull)stream;




/**
 *  @type callback
 *  @region 频道管理
 *  @brief 视频size变化回调。
 *  @param engine ByteRtcEngineKit对象
 *  @param uid   用户ID
 *  @param width 视频宽度
 *  @param height 视频高度
 *  @param rotation 视频旋转信息，详见类型ByteVideoRotation{@link #ByteVideoRotation}
 */
-(void)rtcEngine:(ByteRtcEngineKit *_Nonnull)engine didStreamSizeChange:(NSString* _Nonnull)uid width:(int)width height:(int)height rotation:(int)rotation;

/**
 *  @hidden
 *  @type callback
 *  @region 流消息
 *  @brief 有新的流数据回调。
 *  @param engine ByteRtcEngineKit对象
 *  @param stateCode 状态码，详见类型ByteSubscribeState{@link #ByteSubscribeState}
 *  @param userId 用户ID
 *  @param info 自定义订阅配置，详见类型ByteSubscribeConfig{@link #ByteSubscribeConfig}
 */

- (void)rtcEngine:(ByteRtcEngineKit *_Nonnull)engine
    didStreamSubscribed:(ByteSubscribeState)stateCode
                 userId:(NSString *_Nonnull)userId
                 config:(ByteSubscribeConfig *_Nonnull)info;

#pragma mark video delegates
/**
 *  @type callback
 *  @region 视频管理
 *  @brief 本地首帧视频数据渲染事件回调。调用 joinChannelByKey:channelName:info:uid:{@link #joinChannelByKey:channelName:info:uid:}后，渲染本地首帧视频数据前的事件。
 *  @param engine ByteRtcEngineKit对象
 *  @param size 视频的宽高尺寸
 *  @param elapsed 从调用 joinChannelByKey:channelName:info:uid:{@link #joinChannelByKey:channelName:info:uid:}到渲染本地首帧视频数据前的总耗时(ms)
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine firstLocalVideoFrameWithSize:(CGSize)size elapsed:(NSInteger)elapsed;

/**
 *  @type callback
 *  @region 视频管理
 *  @brief 远端首帧视频数据渲染事件回调。
 *  @param engine ByteRtcEngineKit对象
 *  @param uid 发送当前帧的远端用户的用户ID
 *  @param size 视频的宽高尺寸
 *  @param elapsed 从开始订阅远端流到开始渲染远端首帧视频数据事件的总耗时(ms)
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine firstRemoteVideoFrameOfUid:(NSString* _Nonnull )uid size:(CGSize)size elapsed:(NSInteger)elapsed;

/**
 *  @type callback
 *  @region 视频管理
 *  @brief 本地首帧屏幕数据渲染事件回调。调用 joinChannelByKey:channelName:info:uid:{@link #joinChannelByKey:channelName:info:uid:} 后，渲染本地首帧屏幕数据前的事件。
 *  @param engine RtcEngine 实例，参考: ByteRtcEngineKit{@link #ByteRtcEngineKit}
 *  @param size 视频的宽高尺寸
 *  @param elapsed 从调用 joinChannelByKey:channelName:info:uid:{@link #joinChannelByKey:channelName:info:uid:} 到渲染本地首帧屏幕数据前的总耗时 (ms)
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine firstLocalScreenFrameWithSize:(CGSize)size elapsed:(NSInteger)elapsed;

/**
 *  @type callback
 *  @region 视频管理
 *  @brief 远端首帧屏幕数据渲染事件回调。
 *  @param engine RtcEngine 实例，参考: ByteRtcEngineKit{@link #ByteRtcEngineKit}
 *  @param uid 发送当前帧的远端用户的用户 id
 *  @param size 视频的宽高尺寸
 *  @param elapsed 从开始订阅远端流到开始渲染远端首帧屏幕数据事件的总耗时 (ms)
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine firstRemoteScreenFrameOfUid:(NSString* _Nonnull )uid size:(CGSize)size elapsed:(NSInteger)elapsed;

/**
 *  @type callback
 *  @region 视频管理
 *  @brief 远端用户暂停/重新发送视频回调。房间中远端用户调用muteLocalVideoStream:YES或muteLocalVideoStream:NO时，本地用户将会收到该回调。
 *  @param engine ByteRtcEngineKit对象
 *  @param muted YES:远端用户恢复发送视频流；NO:远端用户暂停发送视频流
 *  @param uid 调用muteLocalVideoStream接口的远端用户ID
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine didVideoMuted:(BOOL)muted byUid:(NSString * _Nonnull)uid;

/**
 *  @type callback
 *  @region 视频管理
 *  @brief 远端用户启用/关闭视频回调。房间中远端用户调用enableVideo/disableVideo时，本地用户将会收到该回调。
 *  @param engine ByteRtcEngineKit对象
 *  @param enabled YES:远端用户启动了视频功能；NO:远端用户关闭了视频功能
 *  @param uid 调用enableVideo接口的远端用户ID
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine didVideoEnabled:(BOOL)enabled byUid:(NSString * _Nonnull)uid;

/**
 *  @type callback
 *  @region 视频管理
 *  @brief 远端用户启用/关闭本地视频回调。房间中远端用户调用enableLocalVideo时，本地用户将会收到该回调。
 *  @param engine ByteRtcEngineKit对象
 *  @param enabled YES:远端用户启动了本地视频；NO:远端用户关闭了本地视频
 *  @param uid 调用enableLocalVideo接口的远端用户ID
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine didLocalVideoEnabled:(BOOL)enabled byUid:(NSString * _Nonnull)uid;

//API not implemented on mac
#if TARGET_OS_IPHONE || TARGET_OS_SIMULATOR
/**
 *  @type callback
 *  @region 视频管理
 *  @brief 远端首帧视频数据解码事件回调。
 *  @param engine ByteRtcEngineKit对象
 *  @param uid 发送当前帧的远端用户的用户ID
 *  @param size 视频的宽高尺寸
 *  @param elapsed 从开始订阅远端流到远端视频首帧解码事件的总耗时(ms)
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine firstRemoteVideoDecodedOfUid:( NSString* _Nonnull )uid size:(CGSize)size elapsed:(NSInteger)elapsed;
#endif

#pragma mark audio delegates
/**
 *  @type callback
 *  @region 音频管理
 *  @brief 当收到本地第一帧音频的时候上报该事件
 *  @param engine ByteRtcEngineKit 对象
 *  @param elapsed 从开始发布音频流到收到该事件经历的时间（毫秒单位）
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine firstLocalAudioFrame:(NSInteger)elapsed;

/**
 *  @type callback
 *  @region 音频管理
 *  @brief 当收到远端流的第一帧音频的时候上报该事件
 *  @param engine ByteRtcEngineKit 对象
 *  @param uid 远端用户ID
 *  @param elapsed 从开始订阅音频流到收到该事件经历的时间（毫秒单位）
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine firstRemoteAudioFrameOfUid:(NSString * _Nonnull)uid elapsed:(NSInteger)elapsed;

/**
 * @hidden
 * @type callback
 * @region 房间管理
 * @brief 远端用户静音/取消静音所有远端音频流时回调
 *        1. 提示该远端用户对房间内其他所有用户静音/取消静音了音频流
 *        2. 该回调由远端用户调用 MuteAllRemoteAudioStreams{@link #IRtcRoom#MuteAllRemoteAudioStreams} 或 UnmuteAllRemoteAudioStreams{@link #IRtcRoom#UnmuteAllRemoteAudioStreams} 触发
 * @param uid 远端用户 ID
 * @param muted  YES: 该用户静音所有远端音频流；NO: 该用户取消静音了所有远端音频流
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine didAllRemoteAudioMuted:(BOOL)muted byUid:(NSString * _Nonnull)uid;

/**
 *  @hidden
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine didAllRemoteVideoMuted:(BOOL)muted byUid:(NSString * _Nonnull)uid;

/**
 *  @type callback
 *  @region 音频管理
 *  @brief 远端用户音频静音回调。
 *         提示有远端用户已将其本地音频流静音（或取消静音），该回调由远端用户调用 muteLocalAudioStream{@link #muteLocalAudioStream:}，本地用户将会收到该回调。
 *  @param engine ByteRtcEngineKit对象
 *  @param muted YES: 该用户已将其本地音频流静音；NO: 该用户已将其本地音频流取消了静音
 *  @param uid 远端用户 ID
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine didAudioMuted:(BOOL)muted byUid:(NSString * _Nonnull)uid;

/**
 *  @type callback
 *  @region 音频管理
 *  @brief 远端用户启用/关闭音频回调。房间中远端用户调用enableAudio/disableAudio时，本地用户将会收到该回调。
 *  @param engine ByteRtcEngineKit对象
 *  @param enabled YES:远端用户启动了音频功能；NO:远端用户关闭了音频功能
 *  @param uid 调用enableAudio接口的远端用户ID
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine didAudioEnabled:(BOOL)enabled byUid:(NSString * _Nonnull)uid;

/**
 *  @type callback
 *  @region 音频管理
 *  @brief 远端用户开启/关闭音频设备采集回调
 *         提示有远端用户已开启/关闭音频设备采集，该回调由远端用户调用 enableLocalAudio{@link #enableLocalAudio:} 方法触发
 *  @param engine ByteRtcEngineKit对象
 *  @param enabled YES: 该用户开启了音频设备采集；NO: 该用户关闭了音频设备采集
 *  @param uid 远端用户 ID
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine didLocalAudioEnabled:(BOOL)enabled byUid:(NSString * _Nonnull)uid;

/**
 * @type callback
 * @region 音频管理
 * @brief 通话音量提示的回调。回调当前房间内每个用户的音量、总音量。
 * @param engine RtcEngine 实例
 * @param speakers 房间内用户的音量信息的数组，每个用户音量信息详见类型 ByteRtcAudioVolumeInfo{@link #ByteRtcAudioVolumeInfo}，包括发送流与接收流
 * @param totalVolume 房间内的总音量大小，只包括接收流
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine reportAudioVolumeIndicationOfSpeakers:(NSArray<ByteRtcAudioVolumeInfo *> * _Nonnull)speakers totalVolume:(NSInteger)totalVolume;

/**
 *  @type callback
 *  @region 视频管理
 *  @brief 当前通话数据统计回调。该回调在通话或直播中每两秒触发一次。
 *  @param engine RtcEngine 实例
 *  @param stats 频道的统计数据，详见类型ByteRtcStats{@link #ByteRtcStats}
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
 *  @type callback
 *  @region 网络连接
 *  @brief 通话中用户的媒体流网络上下行质量报告回调。
 *  @param engine
 *        ByteRtcEngineKit 对象
 *  @param uid
 *        回调的网络质量报告所属用户的用户 ID
 *  @param txQuality
 *        uid 所属用户的媒体流上行网络质量
 *  @param rxQuality
 *        uid 所属用户的媒体流下行网络质量
 *  @notes
 *        1.加入房间成功后，每隔 2 秒会有一次回调，通知房间内用户与媒体服务器之间数据交互的网络质量；
 *        2.当 uid 为本地用户 ID 时，txQuality 为该用户的上行网络质量，rxQuality 为该用户的下行网络质量；
 *        3.当 uid 为远端用户 ID 时，目前仅支持获取该用户的上行网络质量 txQuality ，下行网络质量 rxQuality 为 ByteRtcNetworkQualityUnknown；
 *        4.ByteNetworkQuality 的定义详见：{@link #ByteNetworkQuality}。
 */
- (void)rtcEngine:(ByteRtcEngineKit *_Nonnull)engine networkQuality:(NSString*_Nonnull)uid txQuality:(ByteNetworkQuality)txQuality rxQuality:(ByteNetworkQuality)rxQuality;

/**
 * @hidden
*/
- (void)rtcEngine:(ByteRtcEngineKit *_Nonnull)engine didLogReport:(NSString*_Nonnull)logType withContent:(NSString*_Nonnull)logContent;


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


//API not implemented on mac
#if TARGET_OS_IPHONE || TARGET_OS_SIMULATOR
/**
 *  @type callback
 *  @region 音频管理
 *  @brief 用户的音频质量回调。每两秒钟更新一次。
 *  @param engine RtcEngine 实例
 *  @param uid 用户 id
 *  @param quality 音频质量，参见 ByteNetworkQuality{@link #ByteNetworkQuality}
 *  @param delay 远端用户的延迟
 *  @param lost 丢失数据包的百分比
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine audioQualityOfUid:(NSString* _Nonnull )uid quality:(ByteNetworkQuality)quality delay:(NSUInteger)delay lost:(NSUInteger)lost;

/**
 *  @hidden
 */
- (void)rtcEngine:(ByteRtcEngineKit* _Nonnull)engine log:(NSDictionary* _Nonnull)dict;


/**
 *  @hidden
 *  @type callback
 *  @region 频道管理
 *  @brief 用于客户端事件报告。
 *  @param engine ByteRtcEngineKit对象
 *  @param data TTMonitor NSDictionary数据
 *  @param logType TTMonitor日志类型
 */
- (void)rtcEngine:(ByteRtcEngineKit * _Nonnull)engine reportToTTMonitorData:(NSDictionary *_Nonnull)data
       logTypeStr:(NSString *_Nullable)logType;
#endif
@end

#pragma mark - ByteRtcEngineMediaMetadataObserver

/**
 * @type callback
 * @region 视频数据回调
 * @brief metadata 观察者，可以接收媒体流中的 metadata， 或者向媒体流中添加 metadata
 */
BYTE_RTC_EXPORT @protocol ByteRtcEngineMediaMetadataObserver <NSObject>
@required
/**
 * @type callback
 * @region 视频数据回调
 * @brief 当SDK准备发送一个视频帧时，会回调该接口，向你询问是否需要在该视频帧中添加 metadata
 * @param timestamp 待添加 metadata 视频帧的时间戳， 单位微秒
 * @return 待发送的数据，大小不能超过1024bytes
 * @notes 1、返回 null 代表不需要添加 metadata
 *        2、回调中不能做长时间逻辑处理，以免影响视频卡顿
 */
- (NSData *_Nullable)videoFrameMediaMetaDataAtTime:(NSTimeInterval)timestamp;

@optional
/**
 * @type callback
 * @region 视频数据回调
 * @brief 当SDK收到的视频帧包含 medatada 时，会回调该接口
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
 * @brief 自定义加密的方法接口，通过继承并实现该方法，可以扩展传输过程中的加密方法，
 *      详见 setCustomizeEncryptHandler:{@link #setCustomizeEncryptHandler:}
 * @param rawData 原始音视频桢数据
 * @return 加密后的数据，可以为空，表示丢弃该桢
 * @notes 返回的数据大小应控制在原始数据的90%~120%范围以内，不然将被丢弃
*/
- (NSData * _Nonnull)ByteEngineEncryptRawData:(NSData * _Nonnull)rawData;

@required
/**
 * @type callback
 * @region 加密
 * @brief 自定义解密的方法接口，通过继承并实现该方法，可以扩展传输过程中的解密方法，
 *      详见 setCustomizeEncryptHandler:{@link #setCustomizeEncryptHandler:}
 * @param rawData 原始音视频桢数据
 * @return 解密后的数据，可以为空，表示丢弃该桢
 * @notes 返回的数据大小应控制在原始数据的90%~120%范围以内，不然将被丢弃
*/
- (NSData * _Nonnull)ByteEngineDecryptRawData:(NSData * _Nonnull)rawData;

@end

/**
 *  @type api
 *  @brief ByteRtcEngineKit 类包含应用程序调用的主要方法。调用 ByteRtcEngineKit 的接口最好在同一个线程进行，不建议在不同的线程同时调用。
*/
BYTE_RTC_EXPORT @interface ByteRtcEngineKit : NSObject
/**
 * @type callback
 * @region 引擎管理
 * @brief SDK回调给应用层的delegate对象，详见 ByteRtcEngineDelegate{@link #ByteRtcEngineDelegate}
 */
@property (nonatomic, weak) id<ByteRtcEngineDelegate> _Nullable delegate;

/**
 * @type api
 * @region 引擎管理
 * @brief 创建引擎对象，此方法应该作为正常 SDK 流程中的第一步操作，通过创建一个引擎实例，来使用 SDK 的其他能力
 * @param appId 每个应用的唯一标识符，由 VRTC 控制台随机生成的。不同的 AppId 生成的实例在 VRTC
 *              中进行音视频通话完全独立，无法互通。
 * @param delegate SDK 回调给应用层的 delegate，详见 ByteRtcEngineDelegate{@link #ByteRtcEngineDelegate}
 * @return 可用的 ByteRtcEngineKit{@link #ByteRtcEngineKit} 实例
 * @notes
 *      1. 该方法在第一次调用时初始化一个 RTCEngine 单例，除非调用 destroy{@link #destroy} 方法，否则后续的所有调用均
 *      返回同一个内部实例
 *      2. 连续多次调用该方法不会创建不同的 ByteRtcEngineKit{@link #ByteRtcEngineKit}，该方法应该与 destroy{@link #destroy}
 *      成对使用
 *      3. 必须使用相同的App ID，App间才能进行通话
 */
+ (instancetype _Nonnull)sharedEngineWithAppId:(NSString * _Nonnull)appId
                                      delegate:(id<ByteRtcEngineDelegate> _Nullable)delegate;

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
                  parameters:(NSDictionary * _Nullable)parameters;

/**
 * @type api
 * @region 引擎管理
 * @brief 获取 ByteRtcEngineKit{@link #ByteRtcEngineKit} 单例对象。
 * @return 由 sharedEngineWithAppId:delegate:{@link #sharedEngineWithAppId:delegate:}
 *     创建的 ByteRtcEngineKit{@link #ByteRtcEngineKit} 对象
 * @notes 如果未调用 sharedEngineWithAppId:delegate:{@link #sharedEngineWithAppId:delegate:}
 *     或在调用 destroy{@link #destroy} 之后调用该方法，则会返回 nil
 */
+ (ByteRtcEngineKit * _Nullable) sharedInstance;

/**
 * @type api
 * @region 引擎管理
 * @brief 销毁由 sharedEngineWithAppId:delegate:{@link #sharedEngineWithAppId:delegate:} 所创建引擎实例，并释放所有相关资源
 * @notes
 *      1. 请确保一定是在所有业务场景的最后阶段才调用该方法
 *      2. 该方法在调用之后，会销毁所有SDK相关的内存，并且停止与媒体服务器的任何交互
 *      3. 在上一次 sharedEngineWithAppId:delegate:{@link #sharedEngineWithAppId:delegate:} 调用之后对SDK进行的任何设置，
 *      将在下一次有效执行 sharedEngineWithAppId:delegate:{@link #sharedEngineWithAppId:delegate:} 时生效
 *      4. 本方法为阻塞调用，会阻塞当前线程直到SDK彻底完成退出逻辑，因而需要注意不要在回调线程中
 *      直接调用本方法，也需要注意不要在回调方法中等待主线程的执行，而同时在主线程调用本方法，从而
 *      造成死锁
 */
+ (void)destroy;

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
 * @brief 获取 SDK 当前的版本号
 * @return NSString* 版本号
 */
+ (NSString * _Nonnull)getSdkVersion;

/**
 * @type api
 * @region 引擎管理
 * @brief 获取SDK内各种错误码、警告码的描述文字
 * @param code 通过 rtcEngine:didOccurWarning:{@link #rtcEngine:didOccurWarning:} 和
 *      rtcEngine:didOccurError:{@link #rtcEngine:didOccurError:} 回调获得的值，
 *      具体可以参考 ByteRtcErrorCode{@link #ByteRtcErrorCode} 和 ByteRtcWarningCode{@link #ByteRtcWarningCode}
 * @return NSString* 描述文字
 */
+ (NSString * _Nonnull)getErrorDescription:(NSInteger) code;

/**
 *  @hidden
 *  @type api
 *  @region 频道管理
 *  @brief 设置端监控上报上下文。
 *  @param projectKey 调用app的project_key，每个app有自己特有的值
 *  @param deviceID app 根据当前软硬件环境生成的唯一设备id
 */
+ (void)setLogReportContext:(NSString * _Nonnull)projectKey deviceID:(NSString * _Nonnull)deviceID;

#if TARGET_OS_IPHONE || TARGET_OS_SIMULATOR
/**
 *  @hidden
 *  @deprecated
 *  @type api
 *  @region 视频管理
 *  @brief 用于生成一个用于渲染的View， 已经废弃，不需要也不推荐使用
 *  @param frame View的宽高
 */
+ (UIView * _Nullable)createRenderView:(CGRect) frame;
#elif TARGET_OS_OSX
/**
 *  @hidden
 *  @deprecated
 *  @type api
 *  @region 视频管理
 *  @brief 用于生成一个用于渲染的View， 已经废弃，不需要也不推荐使用
 *  @param frame View的宽高
 */
+ (NSView * _Nullable)createRenderView:(CGRect) frame;
#endif

/**
 *  @type api
 *  @region 视频管理
 *  @brief 该方法设置本地视频显示信息。
 *  @param local 视频属性
 *  @return   0：方法调用成功；
 *             <0： 方法调用失败
 *  @notes 应用程序通过调用此接口绑定本地视频流的显示视窗(view)，并设置视频显示模式。在应用程序开发中，通常在初始化后调用该方法进行本地视频设置，然后再加入频道。
 *       退出频道后，绑定仍然有效，如果需要解除绑定，可以指定空(NULL)View调用setupLocalVideo。
 */
- (int)setupLocalVideo:(ByteRtcVideoCanvas * _Nullable)local;

/**
 *  @type api
 *  @region 视频管理
 *  @brief 设置本地视频镜像.该方法用于开启或关闭本地视频镜像，默认值为关闭（ByteVideoMirrorModeDisabled）。
 *  @param mode 视频镜像模式，类型为枚举类型ByteVideoMirrorMode{@link #ByteVideoMirrorMode}
 *  @return 0：方法调用成功；
 *           <0： 方法调用失败
 */
- (int)setLocalVideoMirrorMode:(ByteVideoMirrorMode) mode;

/**
 * @type api
 * @region 视频管理
 * @brief 获得当前本地镜像状态
 * @return
 *      true：是镜像模式；
 *      false：不是镜像模式；
 */
- (bool)GetLocalVideoMirrorMode;

/**
 *  @type api
 *  @region 视频管理
 *  @brief 该方法绑定远程用户和显示视图，即设定 uid 指定的用户用哪个视图显示。
 *  @param remote 视频属性
 *  @return   0：方法调用成功；
 *          <0： 方法调用失败
 *  @notes 调用该接口时需要指定远程视频的 uid，一般可以在进频道前提前设置好。
 *       如果应用程序不能事先知道对方的uid，可以在APP收到onUserJoined事件时设置。如果启用了视频录制功能，视频录制服务会做为一个哑客户端加入频道，因此其他客户端也会收到它的onUserJoined事件，
 *       APP不应给它绑定视图（因为它不会发送视频流），如果APP不能识别哑客户端，可以在onFirstRemoteVideoDecoded事件时再绑定视图。解除某个用户的绑定视图可以把view设置为空。退出频道后，SDK会把远程用户的绑定关系清除掉。
 */
- (int)setupRemoteVideo:(ByteRtcVideoCanvas * _Nonnull)remote;

/**
 * @type api
 * @region 视频管理
 * @brief 去除所有远端视频。
 */
- (void)removeAllRemoteVideo;

/**
 *  @type api
 *  @region 视频管理
 *  @brief 该方法绑定远端屏幕视图，即设定用户 id 指定的用户用哪个屏幕视图显示。调用该接口时需要指定远程共享屏幕流的用户 id，一般可以在进频道前提前设置好。
 *  @param remote 视频属性，参考: ByteRtcVideoCanvas{@link #ByteRtcVideoCanvas}
 *  @return   0：方法调用成功；
 *  @notes
 *      应用通常在收到远端 rtcEngine:firstRemoteScreenFrameOfUid:size:elapsed:{@link #rtcEngine:firstRemoteScreenFrameOfUid:size:elapsed:} 事件后调用该函数设置远端屏幕共享视图。
 */
- (int)setupRemoteScreen:(ByteRtcVideoCanvas * _Nonnull)remote;

/**
 * @type api
 * @region 视频管理
 * @brief 去除所有远端屏幕。
 */
- (void)removeAllRemoteScreen;

/**
 *  @type api
 *  @region 房间管理
 *  @brief 加入房间。
 *         用户调用此方法加入房间，在一个房间内的用户可以相互通话。如果房间还未创建，将会自动为用户创建对应的房间。如果已在房间中，用户必
 *         须调用  leaveChannel:{@link #leaveChannel:} 退出当前房间后，才能加入下一个房间。
 *  @param token
 *         动态密钥，用于对登录用户进行鉴权验证。进入频道需要携带 Token。可以在控制台生成临时 Token 进行测试，正式上线需要使用密钥 SDK 在您的服务端生成并下发 Token 。
 *  @param roomId
 *         标识通话房间的房间 ID，最大长度为128字节的非空字符串。支持的字符集范围为:
 *             1. 26个大写字母 A ~ Z
 *             2. 26个小写字母 a ~ z
 *             3. 10个数字 0 ~ 9
 *             4. 下划线"_", at符"@", 减号"-"
 *  @param info
 *         预留参数。
 *  @param userId
 *         用户 ID，最大长度为128字节的非空字符串。支持的字符集范围为:
 *             1. 26个大写字母 A ~ Z
 *             2. 26个小写字母 a ~ z
 *             3. 10个数字 0 ~ 9
 *             4. 下划线"_", at符"@", 减号"-"
 *  @return 0: 方法调用成功
 *          1: roomId 为空
 *          2: userId 为空
 *  @notes
 *         1.使用不同 App ID 的 App 是不能互通的。
 *         2.调用该方法成功加入房间后，本端会收到 rtcEngine:didJoinChannel:withUid:elapsed:{@link #rtcEngine:didJoinChannel:withUid:elapsed:} 回调通知。
 *         3.本端网络状况不佳的情况下，SDK 可能会与服务器失去连接，此时 SDK 将会自动重连，重连成功后，本端会收到
 *           rtcEngine:didRejoinChannel:withUid:elapsed:{@link #rtcEngine:didRejoinChannel:withUid:elapsed:} 回调通知。
 *         4.频道模式（频道模式参考 setChannelProfile:{@link #setChannelProfile:} ）为通话模式下的用户或直播、游戏、云游戏模式
 *           下用户角色（用户角色参考 setClientRole:withKey:{@link #setClientRole:withKey:} ）为主播或观众的用户加入房间成功后，远端用户会收到
 *           rtcEngine:didJoinedOfUid:elapsed:{@link #rtcEngine:didJoinedOfUid:elapsed:} 回调通知。
 *         5.同一个 App ID 的同一个房间内，每个用户的用户 ID 必须是唯一的。如果两个用户的用户 ID 相同，则后加入房间的用户会将先加入
 *           房间的用户踢出房间，并且先加入房间的用户会收到 rtcEngine:didOccurError:{@link #rtcEngine:didOccurError:} 回调通知，错误类型为重复登录
 *           BRERR_DUPLICATE_LOGIN{@link #BRERR_DUPLICATE_LOGIN} 。
 *         6.请务必保证生成 Token 使用的 App ID 和创建引擎时使用的 App ID 相同，否则会导致加入房间失败。
 */
- (int)joinChannelByKey:(NSString * _Nullable)token channelName:(NSString * _Nonnull)roomId info:(NSString * _Nullable)info uid:(NSString * _Nonnull)userId;

/**
 *  @type api
 *  @region 视频管理
 *  @brief 该方法设置SimulCast发布的一组视频属性，每个属性对应一套视频参数，如分辨率、帧率、码率等。
 *  @param profiles 视频属性
 *  @return   0：方法调用成功；
 *             <0： 方法调用失败
 *  @notes 给定的属性列表各项分辨率宽高比应保持一致，并按照从大到小的顺序排列
*/
- (int) setVideoProfiles:(NSArray<ByteVideoSolution *> * _Nonnull)profiles;

/**
 *  @type api
 *  @region 房间管理
 *  @brief 设置用户角色。
 *         在加入房间前，用户可调用此方法设置用户角色（默认为主播）。加入房间后，用户也可通过此方法切换用户角色。
 *  @param role
 *         用户角色，详见枚举类型 ByteRtcClientRole{@link #ByteRtcClientRole}
 *  @param permissionKey
 *         预留参数
 *  @return YES: 方法调用成功
 *           NO: 方法调用失败
 *  @notes
 *         1.设置用户角色在房间模式（频道模式参考 setChannelProfile:{@link #setChannelProfile:} ）为直播模式、游戏模式、云游戏模式时生效。
 *         2.如果用户在加入房间成功后调用该方法切换用户角色，调用成功后，远端用户会收到相应的回调通知：用户角色从静默观众切换至观众或主播时会收到
 *           rtcEngine:didJoinedOfUid:elapsed:{@link #rtcEngine:didJoinedOfUid:elapsed:} 回调通知；用户角色从观众或主播切换至静默观众时会收到 rtcEngine:didOfflineOfUid:reason:{@link #rtcEngine:didOfflineOfUid:reason:} 回调通知。
 *         3.通信模式下，调用此接口不生效。
 */
- (int)setClientRole:(ByteRtcClientRole)role withKey:(NSString * _Nullable)permissionKey;

/**
 *  @type api
 *  @region 房间管理
 *  @brief 离开房间。
 *         调用 joinChannelByKey:channelName:info:uid:{@link #joinChannelByKey:channelName:info:uid:} 方法加入房间后，在通话结束时必须调用此方法结束通话，否则无法开始下一次通话。不管
 *         当前是否在通话中，都可以调用此方法。此方法会将通话相关的所有资源释放掉。由于此方法是异步操作，调用返回时并没有真正退出房间。
 *         真正退出房间后，会触发执行调用接口时传入的 Block。通信模式下的用户和其他房间模式下的主播、观众离开房间后，远端用户会收到
 *         rtcEngine:didOfflineOfUid:reason:{@link #rtcEngine:didOfflineOfUid:reason:} 回调通知。
 *  @param leaveChannelBlock 离开房间后的执行的块，块参数为加入房间到离开房间过程间的统计信息，详见数据结构 ByteRtcStats{@link #ByteRtcStats}
 *  @return  0: 方法调用成功
 *          <0: 方法调用失败
 */
- (int)leaveChannel:(void(^ _Nullable)(ByteRtcStats * _Nonnull stat))leaveChannelBlock;

/**
 *  @type api
 *  @region 视频管理
 *  @brief 该方法用于打开视频模块。
 *  @return   0：方法调用成功；
 *             <0： 方法调用失败
 *  @notes 可以在加入频道前或者通话中调用，在加入频道前调用，则自动开启视频模式，在通话中调用则由音频模式切换为视频模式。
 *       调用该方法后，房间中的其他用户会收到didVideoEnabled的回调。调用 disableVideo 方法可关闭视频模式。
 */
- (int)enableVideo;

/**
 *  @type api
 *  @region 视频管理
 *  @brief 该方法用于关闭视频模块。
 *  @return   0：方法调用成功；
 *             <0： 方法调用失败
 *  @notes 可以在加入频道前或者通话中调用，在加入频道前调用，则自动开启纯音频模式，在通话中不可再切换为视频模式。
 *       在通话中调用则由视频模式切换为纯音频频模式。
 *       只能进行语音通话，不能显示、发送自己的视频，也不能接收、显示别人的视频。
 *       调用该方法后，房间中的其他用户会收到didVideoEnabled的回调。调用 enableVideo 方法可开启视频模式。
 */
- (int)disableVideo;

/**
 *  @type api
 *  @region 音频管理
 *  @brief 打开音频模块。
 *  @return   0：方法调用成功；
 *            <0： 方法调用失败
 *  @notes 打开音频模块(默认为开启状态)。该方法为音频方法的总闸，设置引擎内部音频为开启状态，通过重置整个引擎响应，响应速度较慢。调用该方法后，房间中的其他用户会收到didAudioEnabled的回调。
 */
- (int)enableAudio;

/**
 *  @type api
 *  @region 音频管理
 *  @brief 关闭音频模块。
 *  @return   0：方法调用成功；
 *            <0： 方法调用失败
 *  @notes 关闭音频没模块。该方法为音频方法的总闸，设置引擎内部音频为禁止状态，通过重置整个引擎响应，响应速度较慢。设置关闭音频后，只能进行视频通话，不能发送自己的语音，也不能听到别人的语音。
 *       调用该方法后，房间中的其他用户会收到didAudioEnabled的回调。
 */
- (int)disableAudio;

/**
 *  @type api
 *  @region 视频管理
 *  @brief 该方法开启或关闭本地视频采集。
 *  @param enabled YES:开启本地视频采集；NO:关闭本地视频采集
 *  @return   0：方法调用成功；
 *            <0： 方法调用失败
 *  @notes 请在 enableVideo后（或音视频模式下）调用该方法。使用该方法enable时打开摄像头并发送视频数据，disable时关闭摄像头且不发送视频数据，不影响接收远端视频。
 *       调用该方法后，房间中的其他用户会收到didLocalVideoEnabled的回调。
 */
- (int)enableLocalVideo:(BOOL)enabled;

/**
 *  @type api
 *  @region 音频管理
 *  @brief 开启/关闭本地音频采集。
 *  @param enabled YES:开启本地音频采集（默认）; NO:关闭本地音频采集
 *  @return
 *           0：方法调用成功；
 *         < 0： 方法调用失败
 *  @notes 调用该方法后，房间中的其他用户会收到 rtcEngine:didLocalAudioEnabled:byUid:{@link #rtcEngine:didLocalAudioEnabled:byUid:} 事件回调。
 */
- (int)enableLocalAudio:(BOOL)enabled;

/**
 *  @type api
 *  @region 频道管理
 *  @brief 更新 Token。
 *         此方法用于更新 Token。Token 有一定的有效期，App 使用过期的 Token 调用 joinChannelByKey:channelName:info:uid:{@link #joinChannelByKey:channelName:info:uid:} 会
 *         导致加入房间失败，并收到 rtcEngine:didOccurError:{@link #rtcEngine:didOccurError:} 回调通知，回调错误码为 BRERR_INVALID_TOKEN{@link #BRERR_INVALID_TOKEN} 。
 *         此时需要重新获取 Token ，然后调用此方法更新 Token。
 *  @param token 更新的 Token
 *  @return  0: 方法调用成功
 *          <0: 方法调用失败
 *  @notes Token过期时，如果用户已经加入房间成功，则不会受到影响，Token 过期的错误会在用户下一次用过期的 Token 加入房间或由于本地网络状况不佳导致断网重连入房间时通知给用户。
 */
- (int)renewChannelKey:(NSString * _Nonnull)token;

/**
 *  @type api
 *  @region 视频管理
 *  @brief 开启视频预览。
 *  @return   0：方法调用成功；
 *            <0： 方法调用失败
 *  @notes 此方法在进入频道前启动本地视频预览。启动本地视频预览后，如果调用 leaveChannel:{@link #leaveChannel:} 退出频道，本地预览仍然处于启动状态，如果需要关闭本地预览，需要调用stopPreview。
 *       调用该API前必须：调用setupLocalVideo设置预览窗口及属性；调用enableVideo开启视频功能。
 */
- (int)startPreview;

/**
 *  @type api
 *  @region 视频管理
 *  @brief 关闭视频预览，停止本地视频预览。
 *  @return   0：方法调用成功；
 *            <0： 方法调用失败
 */
- (int)stopPreview;

/**
 *  @type api
 *  @region 音频管理
 *  @brief 静音本地音频流
 *  @param mute YES: 静音本地音频流；NO: 关闭静音本地音频流（默认）
 *  @return
 *           0：方法调用成功；
 *         < 0： 方法调用失败
 *  @notes
 *         1. 该方法静音本地音频流。调用该方法后，房间中的其他用户会收到 rtcEngine:didAudioMuted:byUid:{@link #rtcEngine:didAudioMuted:byUid:} 的回调。
 *         2. 本方法只是静音本地流，并未关闭本地音频采集设备。
 */
- (int)muteLocalAudioStream:(BOOL)mute;

/**
 *  @type api
 *  @region 音频管理
 *  @brief 静音/取消静音指定用户的音频流。
 *  @param uid 指定远端用户的ID
 *  @param mute YES:静音指定用户音频流；NO:取消对指定用户音频流的静音
 *  @return
 *           0：方法调用成功；
 *         < 0： 方法调用失败
*/
- (int)muteRemoteAudioStream:(nonnull NSString*)uid mute:(BOOL)mute;

/**
 *  @type api
 *  @region 音频管理
 *  @brief 静音/取消静音所有音频流
 *  @param mute YES: 静音所有音频流；NO: 取消静音所有音频流
 *  @return
 *           0：方法调用成功；
 *         < 0：方法调用失败
 *  @notes 本方法只控制本地是否静音远端音频流，并不能控制远端音频设备的采集发送功能
 */
- (int)muteAllRemoteAudioStreams:(BOOL)mute;

/**
 *  @type api
 *  @region 视频管理
 *  @brief 停止/开启本地视频流发送。调用该方法后，房间中的其他用户会收到didVideoMuted的回调。
 *  @param mute YES:开启本地视频发送；NO:关闭本地视频发送
 *  @return   0：方法调用成功；
 *            <0： 方法调用失败
 *  @notes 调用该方法后，房间中的其他用户会收到didVideoMuted的回调。
*/
- (int)muteLocalVideoStream:(BOOL)mute;

/**
 *  @type api
 *  @region 视频管理
 *  @brief 停止/开启接收所有远端用户的视频流。
 *  @param mute YES:停止接收远端视频流；NO:开启接收远端视频流
 *  @return   0：方法调用成功；
 *            <0： 方法调用失败
*/
- (int)muteAllRemoteVideoStreams:(BOOL)mute;

/**
 *  @type api
 *  @region 视频管理
 *  @brief 停止/开启接收指定远端用户的视频流。
 *  @param uid 指定用户的用户Id
 *  @param mute YES:停止指定的远端视频流；NO:开启指定的远端视频流
 *  @return   0：方法调用成功；
 *            <0： 方法调用失败
*/
- (int)muteRemoteVideoStream:(NSString * _Nonnull)uid
                        mute:(BOOL)mute;

#pragma mark Screen related

/**
 *  @type api
 *  @region 视频管理
 *  @brief 发布本地共享屏幕流， 调用该方法后需要周期性调用 pushScreenFrame{@link #pushScreenFrame:} ，将要发送的屏幕数据送到 SDK 。
 *  @param maxKbitrete 共享屏幕的码率，单位 kbps
 *  @param frameRate 共享屏幕的帧率，单位 kbps
 *  @return   0 :法调用成功；
 *  @notes
 *        1.调用该方法后需要周期性调用 pushScreenFrame{@link #pushScreenFrame:} ，将要发送的屏幕数据送到 SDK 。
 *        2.远端会收到 rtcEngine:firstRemoteScreenFrameOfUid:size:elapsed:{@link #rtcEngine:firstRemoteScreenFrameOfUid:size:elapsed:} 、rtcEngine:didStreamAdded:{@link #rtcEngine:didStreamAdded:} 事件。
 *        3.通过 unpublishScreen{@link #unpublishScreen:} 函数结束本地屏幕共享。
 */
- (int)publishScreen:(int)maxKbitrete frameRate:(int)frameRate;

/**
 *  @type api
 *  @region 视频管理
 *  @brief 取消共享本地屏幕流。
 *  @return   0 :方法调用成功；
*   @notes
*       1.远端会收到 rtcEngine:didStreamRemoved:reason:{@link #rtcEngine:didStreamRemoved:reason:} 事件
*/
- (int)unpublishScreen;

/**
 *  @type api
 *  @region 视频管理
 *  @brief 推送共享桌面的视频帧。
 *  @param frame 视频帧数据，详见：ByteRtcVideoFrameData{@link #ByteRtcVideoFrameData}
 *  @return   YES: 推送成功;
 *             NO: 推送失败;
*/
- (bool)pushScreenFrame:(ByteRtcVideoFrameData * _Nonnull)frame;

/**
 * @type api
 * @region 视频管理
 * @brief 该方法共享一个窗口或该窗口的部分区域。用户需要在该方法中指定想要共享的窗口 id 。
 * @param [in] windowId
 *        指定待共享的窗口 id
 * @param [in] regionRect
 *        指定共享区域相对于整个窗口的位置，当值都为0时共享整个窗口
 * @param [in] captureParameters
 *        屏幕共享的编码参数配置，详见：ByteRtcScreenCaptureParameters{@link #ByteRtcScreenCaptureParameters}
 * @return  <br>
 *        + 0: 成功；  <br>
 *        + -1: 失败；  <br>
 * @notes  <br>
 *       + 本函数不可和 publishScreen{@link #publishScreen} 、unpublishScreen{@link #unpublishScreen} 混用。  <br>
 */
- (int)startScreenCaptureByWindowId:(intptr_t)windowId regionRect:(CGRect)regionRect captureParameters:(ByteRtcScreenCaptureParameters *_Nonnull)captureParameters;

/**
 * @hidden
 * @type api
 * @region 视频管理
 * @brief 通过指定区域共享屏幕，共享一个屏幕或该屏幕的部分区域。用户需要在该方法中指定想要共享的屏幕区域。
 * @param [in] screenRect
 *        指定待共享的屏幕相对于虚拟屏的位置，虚拟屏指所有屏幕组成的图像区域
 * @param [in] regionRect
 *        指定待共享区域相对于screen_rect的位置
 * @param [in] captureParameters
 *        屏幕共享的编码参数配置，详见：ByteRtcScreenCaptureParameters{@link #ByteRtcScreenCaptureParameters}
 * @return  <br>
 *        + 0: 成功；  <br>
 *        + -1: 失败；  <br>
 * @notes  <br>
 *       + 本函数不可和 publishScreen{@link #publishScreen} 、unpublishScreen{@link #unpublishScreen} 混用。  <br>
 */
- (int)startScreenCaptureByScreenRect:(CGRect)screenRect regionRect:(CGRect)regionRect captureParameters:(ByteRtcScreenCaptureParameters *_Nonnull)captureParameters;

/**
 * @type api
 * @region 视频管理
 * @brief 通过屏幕 id 共享屏幕，共享一个屏幕或该屏幕的部分区域。用户需要在该方法中指定想要共享的屏幕 id 。
 * @param [in] displayId
 *        指定待共享的屏幕 id 。
 * @param [in] regionRect
 *        指定待共享区域相对于整个屏幕的位置
 * @param [in] captureParameters
 *        屏幕共享的编码参数配置，详见：ByteRtcScreenCaptureParameters{@link #ByteRtcScreenCaptureParameters}
 * @return  <br>
 *        + 0: 成功；  <br>
 *        + -1: 失败；  <br>
 * @notes 共享一个窗口或该窗口的部分区域。需要在该方法中指定想要共享的窗口 id 。
 * @notes  <br>
 *       + 本函数不可和 publishScreen{@link #publishScreen} 、unpublishScreen{@link #unpublishScreen} 混用。  <br>
 */
- (int)startScreenCaptureByDisplayId:(intptr_t)displayId regionRect:(CGRect)regionRect captureParameters:(ByteRtcScreenCaptureParameters *_Nonnull)captureParameters;

/**
 * @type api
 * @region 视频管理
 * @brief 更新屏幕共享区域。
 * @param  [in] regionRect  <br>
 *       + 当共享屏幕时，指定待共享区域相对于虚拟屏幕的位置
 *       + 当共享窗口时，指定待共享区域相对于整个窗口的位置
 * @return  <br>
 *        + 0: 成功；  <br>
 *        + -1: 失败；  <br>
 */
- (int)updateScreenCaptureRegion:(CGRect)regionRect;

/**
 * @type api
 * @region 视频管理
 * @brief 更新屏幕共享的编码参数配置。
 * @param [in] captureParameters
 *        屏幕共享的编码参数配置，详见：ByteRtcScreenCaptureParameters{@link #ByteRtcScreenCaptureParameters}
 * @return  <br>
 *        + 0: 成功；  <br>
 *        + -1: 失败；  <br>
 */
- (int)updateScreenCaptureParameters:(ByteRtcScreenCaptureParameters *_Nonnull)captureParameters;

/**
 * @type api
 * @region 视频管理
 * @brief 停止屏幕或者窗口共享。
 * @notes  <br>
 *       + 本函数必须在 startScreenCaptureByScreenRect{@link #startScreenCaptureByScreenRect} 、 startScreenCaptureByDisplayId{@link #startScreenCaptureByDisplayId} 或者 startScreenCaptureByWindowId{@link #startScreenCaptureByWindowId} 之后调用  <br>
 *       + 本函数不可和 publishScreen{@link #publishScreen} 、unpublishScreen{@link #unpublishScreen} 混用。  <br>
 */
- (void)stopScreenCapture;

/**
 *  @type api
 *  @region 视频管理
 *  @brief 获取共享对象(应用窗口和桌面)列表
 *  @return 共享对象(应用窗口和桌面)列表
 */
- (NSArray<ByteRtcScreenCaptureSourceInfo *> *_Nonnull)getScreenCaptureSourceList;

/**
 *  @type api
 *  @region 视频管理
 *  @brief 获取共享对象缩略图
 *  @param sourceType 共享对象类型(窗口或显示器)
 *  @param sourceId 共享对象的 id(窗口或显示器 id)
 *  @param maxWidth 缩略图的最大宽度
 *  @param maxWidth 缩略图的最大高度
 *  @return 缩略图对象
 */
- (NSImage *_Nonnull)getScreenCaptureSourceThumbnail:(ByteScreenCaptureSourceType)sourceType sourceId:(intptr_t)sourceId maxWidth:(int)maxWidth maxHeight:(int)maxHeight;

#pragma mark Subscribe on demand

/**
 *  @type api
 *  @region 房间管理
 *  @brief 开启/关闭自动订阅（手动订阅）功能。
 *         此方法用于设置该房间中是否开启自动订阅（手动订阅）功能。
 *  @param audioMode 开启/关闭音频自动订阅功能。详见枚举类型 ByteSubscribeMode{@link #ByteSubscribeMode} 。
 *  @param videoMode 开启/关闭视频自动订阅功能。详见枚举类型 ByteSubscribeMode{@link #ByteSubscribeMode} 。
 *  @notes SDK 提供两种订阅功能：
 *         1.自动订阅功能，SDK 自动帮助用户订阅房间中所有其他用户发布的音视频流。
 *         2.手动订阅功能，SDK 只通过 rtcEngine:didStreamAdded:{@link #rtcEngine:didStreamAdded:} 和 rtcEngine:didStreamRemoved:reason:{@link #rtcEngine:didStreamRemoved:reason:} 回调通知用户
 *           当前所在房间中有哪些音视频流，由用户根据自己的需要调用 subscribeStream:info:{@link #subscribeStream:info:} 方法手动订阅其他用户发布的音视频流。
 *         3.SDK 可以分别对音频/视频设置订阅模式。  <br>
 */
- (BOOL)enableAutoSubscribe:(ByteSubscribeMode)audioMode videoMode:(ByteSubscribeMode)videoMode;

/**
 *  @type api
 *  @region 房间管理
 *  @brief 停止订阅房间内指定的远端音视频流。
 *  @param userId 指定停止订阅的远端音视频流的发布用户的用户ID
 *  @param isScreen 是否是屏幕共享流
 *  @notes
 *         1.不管是否订阅了指定的远端音视频流，都可以调用此方法停止订阅。
 *         2.此方法仅支持在开启手动订阅（关闭自动订阅）功能时调用，用户可通过调用 enableAutoSubscribe:{@link #enableAutoSubscribe:} 方法开启手动订阅功能。
 */
- (void)unsubscribe:(NSString *_Nonnull)userId isScreen:(BOOL)isScreen;

/**
 *  @type api
 *  @region 房间管理
 *  @brief 订阅指定的房间内远端音视频流。
 *  @param [in] userId 指定订阅的远端音视频流的发布用户的用户ID
 *  @param [in] info
 *         选择订阅配置，详见类 ByteSubscribeConfig{@link #ByteSubscribeConfig}
 *  @notes
 *         1.用户调用 joinChannelByKey:channelName:info:uid:{@link #joinChannelByKey:channelName:info:uid:} 方法加入房间后，当房间内有新的音视频流发布时，本端将会收到 rtcEngine:didStreamAdded:{@link #rtcEngine:didStreamAdded:} 回调通知。
 *           此时用户可以根据需要选择性调用此方法订阅新的音视频流，或者保存流信息在将来需要时再调用此方法订阅该音视频流。
 *         2.此方法仅支持订阅当前房间中的远端音视频流。如果指定的流在当前房间内不曾存在，则 SDK 不会订阅。
 *         3.此方法仅支持在开启手动订阅（关闭自动订阅）功能时调用，用户可通过调用 enableAutoSubscribe:{@link #enableAutoSubscribe:} 方法开启手动订阅功能。
 *         4.如果用户在未开启手动订阅（开启自动订阅）功能时调用此方法，SDK 不会订阅指定音视频流，同时会通过 rtcEngine:didOccurWarning:{@link #rtcEngine:didOccurWarning:} 回调通知用户订阅失败，回调警告码 ByteRtcWarningCode{@link #ByteRtcWarningCode} 。
 */
- (void)subscribeStream:(NSString *_Nonnull)userId info:(ByteSubscribeConfig *_Nonnull)info;

#pragma mark Publish on demand

/**
 *  @type api
 *  @region 房间管理
 *  @brief 开启/关闭自动发布（手动发布）功能。
 *         此方法用于设置该房间中是否开启自动发布（手动发布）功能。
 *  @param enable 是否开启自动发布功能：YES，开启；NO，关闭
 *  @notes SDK 提供两种发布功能：
 *         1.自动发布功能，SDK 在加入房间成功后会自动帮助用户发布本地音视频流到房间中。
 *         2.手动发布功能，由用户根据自己的需求调用 publish{@link #publish} 方法主动发布。
 */
- (void)enableAutoPublish:(bool) enable;

/**
 *  @type api
 *  @region 房间管理
 *  @brief 发布本端音视频流到当前房间中。
 *  @notes 此方法仅支持在开启手动发布功能时调用，用户可通过调用 enableAutoPublish:{@link #enableAutoPublish:} 方法开启手动发布功能。
 */
- (void)publish;

/**
 *  @type api
 *  @region 房间管理
 *  @brief 停止向当前房间发布本端音视频流。
 *  @notes 此方法仅支持在开启手动发布功能时调用，用户可通过调用 enableAutoPublish:{@link #enableAutoPublish:} 方法开启手动发布功能。
 */
- (void)unpublish;


/**
 * @type api
 * @region 混音
 * @brief 获取音乐文件时长
 * @return
 *        > 0: 成功, 音乐文件时长，单位为毫秒。
 *        < 0: 失败
 * @notes 请在房间内调用该方法。
 */
- (int)getAudioMixingDuration;

/**
 * @type api
 * @region 混音
 * @brief 获取音乐文件播放进度
 * @return
 *        > 0: 成功, 音乐文件播放进度，单位为毫秒。
 *        < 0: 失败
 * @notes 请在房间内调用该方法。
 */
- (int)getAudioMixingCurrentPosition;

/**
 * @type api
 * @region 混音
 * @brief 停止播放音乐文件及混音
 * @return
 *       0：成功
 *     < 0：失败
 * @notes
 *      1. 调用 startAudioMixing:loopback:replace:cycle:{@link #startAudioMixing:loopback:replace:cycle:} 开始播放音乐文件及混音后，调用该方法可以停止播放音乐文件及混音。
 *      2. 请在房间内调用该方法。
 */
- (int)stopAudioMixing;

/**
 * @type api
 * @region 混音
 * @brief 暂停播放音乐文件
 * @return
 *        0: 成功
 *      < 0: 失败
 * @notes
 *      1. 调用 startAudioMixing:loopback:replace:cycle:{@link #startAudioMixing:loopback:replace:cycle:} 开始播放音乐文件及混音后，可以通过调用该方法暂停播放音乐文件。
 *      2. 暂停播放音乐文件后，可调用 resumeAudioMixing{@link #resumeAudioMixing} 方法恢复播放。
 *      3. 请在房间内调用该方法
 */
- (int)pauseAudioMixing;

/**
 * @type api
 * @region 混音
 * @brief 恢复播放音乐文件
 * @return
 *        0: 成功
 *      < 0: 失败
 * @notes
 *      1. 调用 pauseAudioMixing{@link #pauseAudioMixing} 暂停播放音乐文件后，可以通过该方法恢复播放。
 *      2. 请在房间内调用该方法
 */
- (int)resumeAudioMixing;

/**
 * @type api
 * @region 混音
 * @brief 调节音乐文件的文件音量。
 * @param volume
 *        音乐文件播放音量范围为 0~400。默认 100 为原始文件音量
 * @return
 *        0: 成功
 *      < 0: 失败
 * @notes
 *        1. 该方法同时调节的是本地和远端播放音量。仅调节本端音量可使用 adjustAudioMixingPlayoutVolume{@link #adjustAudioMixingPlayoutVolume:} ， 仅调节远端音量可使用 adjustAudioMixingPublishVolume{@link #adjustAudioMixingPublishVolume:} 。
 *        2. 该方法对 adjustAudioMixingPlayoutVolume{@link #adjustAudioMixingPlayoutVolume:} 和 adjustAudioMixingPublishVolume{@link #adjustAudioMixingPublishVolume:} 的音量调节影响是乘积关系。
 *        3. 请在房间内调用该方法。
 */
- (int)adjustAudioMixingVolume:(NSInteger)volume;

/**
 * @type api
 * @region 混音
 * @brief 开始播放音乐文件及混音。
 * @param  filePath
 *        指定需要混音的本地文件的绝对路径。支持音频文件格式有: mp3，aac，m4a，3gp，wav。
 * @param  loopback
 *        YES: 只有本地可以听到混音或替换后的音频流。
 *        NO: 本地和对方都可以听到混音或替换后的音频流
 * @param  replace
 *        YES: 只推送设置的本地音频文件，不传输麦克风采集的音频。
 *        NO: 音频文件内容将会和麦克风采集的音频流进行混音
 * @param  cycle 指定音频文件循环播放的次数。
 *        > 0：循环的次数；
 *         -1：无限循环
 * @return
 *      0：成功
 *    < 0：失败
 * @notes
 *      1. 该方法指定本地和麦克风采集的音频流进行混音或替换。替换是指用音频文件替换麦克风采集的音频流。
 *      2. 该方法可以选择是否让对方听到本地播放的音频，并指定循环播放的次数。
 *      3. 开始播放音乐文件及混音后，可以通过 stopAudioMixing{@link #stopAudioMixing} 停止播放音乐文件。
 *      4. 该方法混音数据来源外部文件，且支持的文件格式有: mp3，aac，m4a，3gp，wav。
 *      5. 单个房间只支持一路音乐文件的播放，多次调用该函数后，只有最后一次调用会生效。
 *      6. 请在房间内调用该方法。
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
 * @return
 *        0: 成功
 *      < 0: 失败
 * @notes 该方法可以设置音频文件的播放位置，这样你可以根据实际情况从指定的位置播放音乐文件，无需从头到尾完整播放一个音乐文件。
 */
- (int)setAudioMixingPosition:(NSInteger)pos;

/**
 * @type api
 * @region 混音
 * @brief 调节音乐文件的本地播放音量
 * @param  volume
 *        音乐文件播放音量范围为 0~400。默认 100 为原始文件音量
 * @return
 *        0: 成功
 *      < 0: 失败
 * @notes
 *      1. 该方法调节混音的音乐文件在本地播放的音量大小。
 *      2. 请在房间内调用该方法。
 */
- (int)adjustAudioMixingPlayoutVolume:(NSInteger)volume;

/**
 * @type api
 * @region 混音
 * @brief 调节音乐文件的远端播放音量
 * @param volume
 *        音乐文件播放音量范围为 0~400。默认 100 为原始文件音量
 * @return
 *        0: 成功
 *      < 0: 失败
 * @notes
 *       1. 该方法调节混音的音乐文件在远端播放的音量大小。如果需要同时调节本地和远端播放音量可使用 AdjustAudioMixingVolume{@link #AdjustAudioMixingVolume:} 方法。
 *       2. 请在房间内调用该方法。
 */
- (int)adjustAudioMixingPublishVolume:(NSInteger)volume;

/**
 * @type api
 * @region 音效
 * @brief 调节指定音效文件的文件音量
 * @param soundId
 *        音效ID，应用调用者维护，请保证唯一性。确保此处的 soundId 与  playEffect:filePath:loopback:cycle:withVolume:{@link #playEffect:filePath:loopback:cycle:withVolume:} 设置的 soundId 相同。
 * @param volume 音乐文件播放音量范围为 0~400。默认 100 为原始文件音量
 * @return
 *        0: 成功
 *      < 0: 失败
 * @notes
 *      1. 该方法调节音效文件在本地和远端播放的音量大小。
 *      2. 请在房间内调用该方法。
 */
- (int)setVolumeOfEffect:(NSInteger)soundId
              withVolume:(NSInteger)volume;

/**
 * @type api
 * @region 音效
 * @brief 获取指定音效文件的文件音量
 * @param soundId
 *        音效ID，应用调用者维护，请保证唯一性。确保此处的 soundId 与  playEffect:filePath:loopback:cycle:withVolume:{@link #playEffect:filePath:loopback:cycle:withVolume:} 设置的 soundId 相同。
 * @return
 *        > 0: 成功，文件音量，音量范围为 0~400。
 *        < 0: 失败
 * @notes 请在房间内调用该方法。
 */
- (int)getEffectVolume:(NSInteger)soundId;

/**
 * @type api
 * @region 音效
 * @brief 开始播放指定音效文件。你可以在该方法中设置音效文件的播放次数、音量大小，以及远端用户是否能听到该音效。
 * @param soundId
 *        音效ID，应用调用者维护，请保证唯一性。如果已经通过 preloadEffect:filePath:{@link #preloadEffect:filePath:}  将音效加载至内存，确保此处的 soundId 与 preloadEffect:filePath:{@link #preloadEffect:filePath:} 设置的 soundId 相同。
 * @param filePath
 *        指定需要混音的音频文件名和文件路径名。支持以下音频格式: mp3，aac，m4a，3gp，wav
 * @param loopback
 *        YES: 只有本地可以听到该音效；
 *        NO: 本地和远端用户都可以听到该音效
 * @param  cycle 指定音频文件循环播放的次数。
 *        > 0：循环的次数；
 *         -1：无限循环，直至调用 stopEffect{@link #stopEffect:} 或 stopAllEffects{@link #stopAllEffects} 后停止。
 * @param volume
 *        音效文件播放音量范围为 0~400。默认 100 为原始文件音量
 * @return
 *        0: 成功
 *      < 0: 失败
 * @notes
 *      1. 可以多次调用该方法，通过传入不同的音效文件的 soundId 和 filePath，以实现同时播放多个音效文件，实现音效叠加。
 *      2. 可以通过 stopEffect{@link #stopEffect:} 方法停止播放指定音效文件。
 *      3. 请在房间内调用该方法。
 */
- (int)playEffect:(NSInteger)soundId
         filePath:(NSString * _Nullable)filePath
         loopback:(BOOL)loopback
            cycle:(NSInteger)cycle
       withVolume:(NSInteger)volume;

/**
 * @type api
 * @region 音效
 * @brief 预加载指定音效文件
 * @param soundId
 *        音效ID，应用调用者维护，请保证唯一性
 * @param filePath
 *        指定需要混音的音频文件名和文件路径名。支持以下音频格式: mp3，aac，m4a，3gp，wav
 * @return
 *        0: 成功
 *      < 0: 失败
 * @notes
 *       1. 该方法预加载播放指定音效文件。预加载操作可以在进房间之前完成（所有混音相关接口，如果没有标注请在房间内调用都可在没有进入房间的时候调用）。如果音效文件很长，加载操作可能会耗时较长，建议应用开发者将预加载操作放在子线程进行。
 *       2. 该方法只是预加载播放指定音效文件，只有通过 playEffect:filePath:loopback:cycle:withVolume:{@link #playEffect:filePath:loopback:cycle:withVolume:} 才开始播放指定音效文件。
 *       3. 该方法预加载指定音效文件可以通过 unloadEffect{@link #unloadEffect:} 来卸载。
 */
- (int)preloadEffect:(NSInteger)soundId filePath:(NSString * _Nullable)filePath;

/**
 * @type api
 * @region 音效
 * @brief 卸载指定音效文件
 * @param soundId
 *        音效ID，应用调用者维护，请保证唯一性
 * @return
 *        0: 成功
 *      < 0: 失败
 * @notes
 *      1. 该方法卸载指定音效文件。
 *      2. 如果 unloadEffect{@link #unloadEffect:} 时音效文件没有被卸载，SDK会自动调用该方法卸载音效文件。
 */
- (int)unloadEffect:(NSInteger)soundId;

/**
 * @type api
 * @region 音效
 * @brief 暂停播放指定音效文件
 * @param soundId
 *        音效ID，应用调用者维护，请保证唯一性
 * @return
 *        0: 成功
 *      < 0: 失败
 * @notes
 *      1. pauseEffect{@link #pauseEffect:} 暂停播放指定音效文件可以通过该方法恢复播放。
 *      2. pauseAllEffects{@link #pauseAllEffects} 暂停所有音效文件的播放后，也可以通过该方法恢复单个音效文件播放。
 */
- (int)pauseEffect:(NSInteger)soundId;

/**
 * @type api
 * @region 混音
 * @brief 恢复播放指定音效文件
 * @param  soundId
 *        音效ID，应用调用者维护，请保证唯一性
 * @return
 *        0: 成功
 *      < 0: 失败
 * @notes 该方法恢复播放指定音效文件。
 */
- (int)resumeEffect:(NSInteger)soundId;

/**
 * @type api
 * @region 音效
 * @brief 停止播放指定音效文件
 * @param soundId
 *        音效ID，应用调用者维护，请保证唯一性。如果已经通过 preloadEffect:filePath:{@link #preloadEffect:filePath:}  将音效加载至内存，确保此处的 soundId 与  preloadEffect:filePath:{@link #preloadEffect:filePath:} 设置的 soundId 相同。
 * @return
 *        0: 成功
 *      < 0: 失败
 * @notes
 *      1. 该方法停止播放指定音效文件。
 *      2. 该方法内部会主动调用 unloadEffect{@link #unloadEffect:} 来卸载指定音效文。
 */
- (int)stopEffect:(NSInteger)soundId;

/**
 * @type api
 * @region 混音
 * @brief 调节所有音效文件的文件音量
 * @param  volume
 *        音乐文件播放音量范围为 0~400。默认 100 为原始文件音量
 * @return
 *        0: 成功
 *      < 0: 失败
 * @notes
 *       1. 该方法调节混音的音效文件在本地和远端播放的音量大小。
 *       2. 请在房间内调用该方法。
 */
- (int)setEffectsVolume:(NSInteger)volume;

/**
 * @type api
 * @region 混音
 * @brief 卸载所有音效文件
 * @return
 *       0: 成功
 *     < 0: 失败
 * @notes
 *      1. 该方法卸载所有音效文件。如果引擎被销毁时有音效文件没有被卸载，SDK会自动调用该方法卸载所有音效文件。
 *      2. 离开房间  leaveChannel:{@link #leaveChannel:} 后不会自动调用该方法卸载所有音效文件。如果需要在离开房间后卸载所有音效文件，需要应用主动调用该方法。
 */
- (int)unloadAllEffects;

/**
 * @type api
 * @region 混音
 * @brief 暂停所有音效文件的播放
 * @notes 该方法暂停所有音效文件的播放。
 */
- (int)pauseAllEffects;

/**
 * @type api
 * @region 混音
 * @brief 恢复所有音效文件的播放
 * @return
 *       0: 成功
 *     < 0: 失败
 * @notes
     *     1. 该方法恢复所有音效文件的播放。在调用 pauseAllEffects{@link #pauseAllEffects} 暂停所有音效文件的播放后，可以通过该方法可恢复所有音效文件的播放。
     *     2. pauseEffect{@link #pauseEffect:} 方法暂停单个指定音效文件的播放后，也可以通过该方法恢复播放，但是效率太低，不推荐这么使用。
 */
- (int)resumeAllEffects;

/**
 * @type api
 * @region 混音
 * @brief 停止所有音效文件的播放
 * @return
 *        0: 成功
 *      < 0: 失败
 * @notes 该方法停止所有音效文件的播放。
 */
- (int)stopAllEffects;

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
 *         1.参数 roomId 没有默认值，请确保对该参数正确赋值。
 *         2.请勿给参数 roomId 赋空字符串""或者空指针，否则将无法正确的创建房间对象。
 *         3.用户可以多次调用此方法创建多个 ByteRtcRoom{@link #ByteRtcRoom} 对象，再分别调用各 ByteRtcRoom{@link #ByteRtcRoom} 对象的
 *           joinRoomByToken{@link #joinRoomByToken} 方法，实现同时加入多个房间。
 *         4.加入多个房间后，用户可以同时订阅各房间的音视频流，但是目前仅支持同一时间在一个房间内发布一路音视频流。
 */
- (ByteRtcRoom * _Nullable)createRtcRoom:(NSString * _Nonnull)roomId;

/**
 *  @hidden
 *  @type api
 *  @region 房间管理
 *  @brief 多房间模式下，销毁已存在的房间
 *  @param roomId 销毁的房间的房间 ID
 */
- (void)destroyRtcRoom:(NSString *_Nonnull)roomId;

/**
 *  @type api
 *  @region 房间管理
 *  @brief 设置频道模式。
 *         该方法用于设置房间频道模式。SDK 会针对不用的频道模式应用对应的优化策略。
 *  @param profile 应用程序频道模式，详见枚举类型 ByteChannelProfile{@link #ByteChannelProfile}
 *  @return  0：方法调用成功
 *          <0：方法调用失败
 *  @notes
 *         1.用户必须在调用 joinChannelByKey:channelName:info:uid:{@link #joinChannelByKey:channelName:info:uid:} 前设置频道模式，加入房间后设置不再生效。
 *         2.为保证音视频质量和实时性，建议相同房间内的用户使用相同的频道模式。
 */
- (int)setChannelProfile:(ByteChannelProfile)profile;

/**
 *  @type api
 *  @region 音频管理
 *  @brief 开启/关闭发言者音量提示。
 *  @param interval 指定音量提示的时间间隔; <=0: 禁用音量提示功能；>0 : 提示间隔，单位为毫秒(ms)。建议设置到大于 200 毫秒。少于 10 毫秒时，行为未定义。
 *  @param smooth 音量提示的灵敏度，灵敏度取值范围为 [0,10]。数字越大，波动越灵敏；数字越小，波动越平滑
 *  @return 0： 代表方法调用成功
 *  @notes 开启或禁用发言者音量提示功能。功能开启时将以你设置的 interval 为间隔通过 rtcEngine:reportAudioVolumeIndicationOfSpeakers:totalVolume:{@link
 * #rtcEngine:reportAudioVolumeIndicationOfSpeakers:totalVolume:} 回调用户的音量。
 */
- (int)enableAudioVolumeIndication:(NSInteger)interval
                            smooth:(NSInteger)smooth;
/**
 *  @type api
 *  @region 频道管理
 *  @brief 设置弱网条件下发布的音视频流回退选项
 *  @param option 详见枚举类型BytePublishFallbackOption{@link #BytePublishFallbackOption}
 *  @return 0：方法调用成功，
 *           <0：方法调用失败
 */
- (int)setPublishFallbackOption:(BytePublishFallbackOption)option;

/**
 *  @type api
 *  @region 频道管理
 *  @brief 设置订阅的音视频流回退选项
 *  @param option 详见枚举类型ByteSubscribeFallbackOptions{@link #ByteSubscribeFallbackOptions}
 *  @return 0：方法调用成功，
 *           <0：方法调用失败
 */
- (int)setSubscribeFallbackOption:(ByteSubscribeFallbackOptions)option;

/**
 * @type api
 * @region 其他
 * @brief 设置业务标识参数。
 *       可通过 businessId 区分不同的业务场景（角色/策略等）。businessId 由客户自定义，相当于一个“标签”，可以分担和细化现在 AppId 的逻辑划分的功能。
 * @param businessId 用户设置的自己的 businessId 值。businessId 相当于一个 sub AppId，可以分担和细化现在 AppId 的逻辑划分的功能，但不需要鉴权。businessId 只是一个标签，颗粒度需要用户自定义。
 * @return 0：代表方法调用成功。
 *         -6001：用户已经在房间中。
 *         -6002：输入非法，合法字符包括所有小写字母、大写字母和数字，除此外还包括四个独立字符分别是：英文句号，短横线，下划线和 @。
 * @notes 需要在调用 joinChannelByKey:channelName:info:uid:{@link #joinChannelByKey:channelName:info:uid:} 之前调用，joinChannelByKey:channelName:info:uid:{@link #joinChannelByKey:channelName:info:uid:} 之后调用该方法无效。
 */
- (int)setBusinessId:(NSString*_Nullable)businessId;

/**
 * @type api
 * @region 视频管理
 * @brief 视频图像分割，替换背景
 * @param mode 背景模式，用于设置预制背景，是否虚化等 详见 BackgroundMode{@link #BackgroundMode}
 * @param divideModel 选择使用哪种分割模型， 分割模型类型详见 DivideModel{@link #DivideModel}
 * @return 0: 方法调用成功；
 *         < 0: 方法调用失败；
 */
- (int) replaceBackground:(BackgroundMode)mode
          withDivideModel:(DivideModel)divideModel;

/**
 * @type api
 * @region 视频管理
 * @brief 禁用视频图像分割，替换背景
 */
- (void) disableBackground;

#pragma mark - MediaMetadataData InnerVideoSource

/**
 * @type api
 * @region 视频数据回调
 * @brief 注册 metadata 观察者，用于接收或发送 metadata。
 *        底层通过视频帧中添加 SEI 数据实现该功能。
 * @param metadataObserver  metadata 观察者，详见：ByteRtcEngineMediaMetadataObserver{@link #ByteRtcEngineMediaMetadataObserver}
 * @return YES: 设置成功
 *          NO: 设置失败
 * @notes 使用视频自定义采集与渲染时，可以直接在视频帧中获取 metadata 。不建议使用本接口。
 */
- (BOOL)setMediaMetadataObserver:(_Nullable id<ByteRtcEngineMediaMetadataObserver>) metadataObserver;

//API not implemented on mac
#if TARGET_OS_IPHONE || TARGET_OS_SIMULATOR

/**
 *  @type api
 *  @region 音频管理
 *  @brief 开启/关闭发言者音量提示。
 *  @param interval 指定音量提示的时间间隔; <=0: 禁用音量提示功能；>0 : 提示间隔，单位为毫秒(ms)
 *  @param smooth 音量提示的灵敏度，灵敏度取值范围为[0,10]。数字越大，波动越灵敏；数字越小，波动越平滑
 *  @return   0: 代表方法调用成功；
 *            <0: 代表方法调用失败
 *  @notes 开启或禁用发言者音量提示功能。功能开启时以一定时间间隔通过音量提示回调reportAudioVolumeIndicationOfSpeakers通知用户频道内音量较高的几个用户及他们的音量。
*/
- (int)enableAudioVolumeIndication:(NSInteger)interval
                            smooth:(NSInteger)smooth;

/**
 *  @type api
 *  @region 视频管理
 *  @brief 切换摄像头。
 *  @return   0: 代表方法调用成功；
 *            <0: 代表方法调用失败
*/
- (int)switchCamera;

/**
 *  @hidden
 *  @type api
 *  @region 其他
 *  @brief 设置日志文件的存放目录。
 *  @param fileDir  目录的完整路径
 *  @return   0: 代表方法调用成功；
 *            <0: 代表方法调用失败
*/
- (int)setLogFileDir:(NSString*_Nullable)fileDir;

/**
 *  @hidden
 *  @type api
 *  @region 其他
 *  @brief 设置日志文件的存放目录。
 *  @param level 日志等级
 *  @notes 设置日志等级，默认情况下为RTC_LOG_LEVEL_INFO
*/
- (void)setLogFilter:(ByteRtcLogLevel)level;

/**
 *  @type api
 *  @region 频道管理
 *  @brief 设置设备ID。
 *  @param deviceId applog 生成的 Device ID
 *  @return   0: 设置成功；
 *            <0: 设置失败
*/
- (void)setDeviceId:(NSString*_Nullable)deviceId;

/**
 *  @hidden
 *  @type api
 *  @region 音频管理
 *  @brief 启用/关闭扬声器播放
 *        该方法设置是否切换语音路由到扬声器（外放）
 *  @param enableSpeaker 是否切换语音路由到扬声器（外放）
 *                       true: 切换到外放
 *                       false: 切换到听筒
 *  @return
 *            0: 方法调用成功；
 *          < 0: 方法调用失败；
 */
- (int)setEnableSpeakerphone:(BOOL)enableSpeaker;

/**
 *  @hidden
 *  @type api
 *  @region CDN推流
 *  @brief 设置视频流布局。此方法设置视频流在视图上的显示布局方式，通过将一个ByteRtcVideoCompositingRegion队列传入给layout参数的regions域，设置
 *         多个视频流在View上的显示布局。
 *  @param layout 显示布局，详见 ByteRtcVideoCompositingLayout{@link #ByteRtcVideoCompositingLayout} 类对象
 *  @return  0: 方法调用成功
 *          <0: 方法调用失败
 */
- (int)setVideoCompositingLayout:(ByteRtcVideoCompositingLayout * _Nonnull)layout;

/**
 *  @type api
 *  @region 视频管理
 *  @brief 设置本地视频属性。
 *  @param size 设置的视频尺寸，最高不超过 1280x720
 *  @param frameRate 设置的视频帧率，最高值不超过 30，如： 5、10、15、24、30 等
 *  @param bitrate 设置的视频码率
 *  @return   0: 代表方法调用成功；
 *            <0: 代表方法调用失败
 *  @notes 若设置的视频码率超出合理范围，SDK 会自动按照合理区间处理码率。
*/
- (int)setVideoResolution: (CGSize)size andFrameRate: (NSInteger)frameRate bitrate: (NSInteger) bitrate;

/**
 * @type api
 * @region 视频管理
 * @brief 设置外部视频输入源
 * @param enable 是否使用外部视频源
 *        true: 采用外部输入源
 *        false: 不采用外部输入源
 * @notes
 *  1.该方法应该在startpreview和joinChannel之前调用
 */
- (void)setExternalVideoSource:(bool)enable;

//#pragma mark External media source
//// If external video source is to use, call this API before enableVideo/startPreview
//- (void)setExternalVideoSource:(BOOL)enable useTexture:(BOOL)useTexture pushMode:(BOOL)pushMode;
//// Push a video frame to SDK
//- (BOOL)pushExternalVideoFrame:(CVPixelBufferRef _Nonnull )frame time:(CMTime)pts;
//// only support NV12 and "ios texture"
//- (BOOL)pushExternalByteVideoFrame:(ByteVideoFrame * _Nonnull)frame;
#endif

#pragma mark AES Related

/**
 * @type api
 * @region 加密
 * @brief 设置AES加密算法和加密密钥，有四种内置的加密算法
 * @param encrypt_type 加密类型，详见 ByteEncryptType{@link #ByteEncryptType}
 * @param key 加密密钥，长度限制为36位，超出部分将会被截断
 * @notes
 *      1. 该方法与 setCustomizeEncryptHandler:{@link #setCustomizeEncryptHandler:} 为互斥关系,
 *      即按照调用顺序，最后一个调用的方法为最终生效的版本。
 *      2. 该方法必须在调用 joinChannelByKey:channelName:info:uid:{@link #joinChannelByKey:channelName:info:uid:} 之前调用，可重复调用，以最后调用的参数作为生效参数
 *      3. AES加密算法限制，超过36位的key会被截断，仅取前36位
 */
- (void)setEncryptType:(ByteEncryptType)encrypt_type key:(NSString * _Nonnull)key;

/**
 * @type api
 * @region 加密
 * @brief 设置自定义加密，需要实现对应的加密/解密方法，详情参考
 *      ByteEncryptHandler{@link #ByteEncryptHandler}
 * @param handler 自定义加密handler，需要实现里面的加密和解密方法
 * @notes
 *      1. 该方法与 setEncryptType:key:{@link #setEncryptType:key:} 为互斥关系，即按照调用顺序，
 *      最后一个调用的方法为最终生效的版本
 *      2. 该方法必须在调用 joinChannelByKey:channelName:info:uid:{@link #joinChannelByKey:channelName:info:uid:} 之前调用，可重复调用，以最后调用的参数作为生效参数
 *      3. 无论加密或者解密，其对原始数据的长度修改，需要控制在90%-120%之间，即如果输入数据为100字节，则处理完成后的数据必须在
 *      90至120自己之间，如果加密或解密结果超出该长度限制，则该音视频桢会被丢弃
 *      4. 数据加密/解密为串行执行，因而视实现方式不同，可能会影响到最终渲染效率，是否使用该方法，需要由使用方谨慎评估
 */
- (void)setCustomizeEncryptHandler:(id<ByteEncryptHandler> _Nullable)handler;

#pragma mark Cloud Rending
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

/**
 * @type api
 * @region 其他
 * @brief 设置运行时的参数
 * @param [in] parameters 用以覆盖全局参数，详情可见 setParameters{@link #setParameters}，业务方传入
 * @notes
 */
- (void)setRuntimeParameters:(NSDictionary * _Nullable)parameters;

/**
 * @type api
 * @region 音频管理
 * @brief 调节录音音量。
 * @param volume 录音音量，可在 0~400 范围内进行调节  <br>
 *              + 0：静音  <br>
 *              + 100：原始音量  <br>
 *              + 400: 最大可为原始音量的 4 倍(自带溢出保护)  <br>
 * @notes 为保证更好的通话质量，建议将 volume 值设为 [0,100]
 */
- (void)setRecordingVolume:(NSInteger)volume;

/**
 * @type api
 * @region 音频管理
 * @brief 调节本地播放的所有远端用户音量
 * @param volume 播放音量，可在 0~400 范围内进行调节  <br>
 *              + 0：静音  <br>
 *              + 100：原始音量  <br>
 *              + 400: 最大可为原始音量的 4 倍(自带溢出保护)
 * @notes  <br>
 *       + 该方法调节的是本地播放的所有远端用户混音后的音量  <br>
 *       + 为保证更好的通话质量，建议将 volume 值设为 [0,100]
 */
- (void)setPlaybackVolume:(NSInteger)volume;

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
- (void)setAudioPerformanceProfile:(ByteAudioPerformanceProfile) profile;

/**
 * @type api
 * @region 音频管理
 * @brief 调节远端用户音量，默认值为100
 * @param uid 远端用户ID
 * @param volume  播放音量，可在 0~400 范围内进行调节  <br>
 *              + 0: 静音  <br>
 *              + 100: 原始音量  <br>
 *              + 400: 最大可为原始音量的 4 倍(自带溢出保护)  <br>
 * @return  方法调用结果  <br>
 *        + 0：方法调用成功  <br>
 *        + <0：方法调用失败  <br>
 */
- (void)setRemoteAudioPlaybackVolume:(NSString* _Nonnull)uid volume:(int)volume;

/*
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

@end
