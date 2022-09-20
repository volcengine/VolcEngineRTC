//
//  GameRTCEngineKit.h
//  bytertc
//
//  Created by bytedance on 2021/5/26.
//

#import <Foundation/Foundation.h>
#import "GameRTCEngineKitDefines.h"

NS_ASSUME_NONNULL_BEGIN
@class GameRTCEngineKit;
/**
 * @type callback
 */
@protocol GameRTCEngineDelegate <NSObject>

/**
 * @type callback
 * @region 房间管理
 * @brief 用户成功加入房间/重连进房后，收到此回调。
 * @param engine GameRTCEngineKit 实例
 * @param roomId 房间 ID
 * @param uid 用户 ID
 * @param state 用户加入房间回调的状态码:  <br>
 *        + 0: 成功  <br>
 *        + !0: 失败  <br>
 *        + 具体原因参看错误码 GameRTCRoomStateCode{@link #GameRTCRoomStateCode} 以及警告码 GameRTCEngineWarningCode{@link #GameRTCEngineWarningCode} 
 * @param extraInfo 额外信息。
 */
- (void)rtcEngine:(GameRTCEngineKit *)engine onRoomStateChanged:(NSString *)roomId uid:(NSString *)uid 
          state:(GameRTCRoomStateCode)state extraInfo:(NSString *)extraInfo;

/**
 * @type callback
 * @region 房间管理
 * @brief 用户成功加入房间/重连进房后，收到此回调。
 * @param engine GameRTCEngineKit 实例
 * @param roomId 房间 ID
 * @param uid 用户 ID
 * @param state 流状态码，参看 GameRTCStreamStateCode{@link #GameRTCStreamStateCode} 以及警告码 GameRTCEngineWarningCode{@link #GameRTCEngineWarningCode}
 * @param extraInfo 额外信息。
 */
- (void)rtcEngine:(GameRTCEngineKit *)engine onStreamStateChanged:(NSString *)roomId uid:(NSString *)uid 
          state:(GameRTCStreamStateCode)state extraInfo:(NSString *)extraInfo;

/**
 * @type callback
 * @region 房间管理
 * @brief 离开房间成功回调 <br>
 *        用户调用 leaveRoom:{@link #GameRTCEngineKit#leaveRoom:} 方法后，SDK 会停止所有的发布订阅流，并释放所有通话相关的音视频资源。SDK 完成所有的资源释放后，用户收到此回调。<br>
 *        离开房间结束通话后，如果 App 需要使用系统音视频设备，建议在收到此回调后再初始化音视频设备.否则可能由于 SDK 占用了导致 App 初始化音视频设备失败。
 * @param engine GameRTCEngineKit 实例
 * @param roomId 房间 ID
 * @notes 用户调用 leaveRoom:{@link #GameRTCEngineKit#leaveRoom:} 方法离开房间后，如果立即调用 destroy{@link #GameRTCEngineKit#destroy} 方法销毁 GameRTC 引擎，则将无法收到此回调事件。
 */
- (void)rtcEngine:(GameRTCEngineKit *)engine onLeaveRoom:(NSString *)roomId;

/**
 * @type callback
 * @region 房间管理
 * @brief 远端用户加入房间回调。<br>
 *        以下情形下，本地用户会收到此回调：<br>
 *        + 远端用户首次加入房间/重连加入房间；<br>
 *        + 本地用户加入房间时，会收到回调，提示已在房间中的远端用户。
 * @param engine GameRTCEngineKit 实例
 * @param roomId 房间 ID
 * @param uid 用户 ID
 */
- (void)rtcEngine:(GameRTCEngineKit *)engine onUserJoined:(NSString *)roomId uid:(NSString *)uid;

/**
 * @type callback
 * @region 房间管理
 * @brief 远端用户离开房间回调。<br>
 *        房间中有用户主动调用 leaveRoom:{@link #GameRTCEngineKit#leaveRoom:} 方法离开房间或断线超时离开房间时，房间中其他用户都会收到此回调。
 * @param engine GameRTCEngineKit 实例
 * @param roomId 房间 ID
 * @param uid 离开房间的用户的用户 ID
 * @param reason 用户离开的原因。参看 GameRTCUserLeaveType{@link #GameRTCUserLeaveType}
 */
- (void)rtcEngine:(GameRTCEngineKit *)engine onUserLeave:(NSString *)roomId uid:(NSString *)uid reason:(GameRTCUserLeaveType)reason;

/**
 * @type callback
 * @region 音频管理
 * @brief 远端用户开关麦克风回调 <br>
 *        当用户调用 enableMicrophone:room:{@link #GameRTCEngineKit#enableMicrophone:room:} 更改本地音频采集和发布状态时，房间内其他用户会收到此回调。
 * @param engine GameRTCEngineKit 实例
 * @param enabled 是否开启麦克风 <br>
 *        + true: 打开麦克风 <br>
 *        + false: 关闭麦克风 <br>
 * @param roomId 房间 ID
 * @param uid 更改本地音频采集和发布状态的用户的 ID
 */
- (void)rtcEngine:(GameRTCEngineKit *)engine onMicrophoneEnabled:(BOOL)enabled room:(NSString *)roomId uid:(NSString *)uid;

/**
 * @type callback
 * @region 音频管理
 * @brief 远端用户启停音频数据发送的回调 <br>
 *        当用户调用 enableAudioSend:room:{@link #GameRTCEngineKit#enableAudioSend:room:} 更改本地音频发送状态时，房间内其他用户会收到此回调。
 * @param engine GameRTCEngineKit 实例
 * @param enabled 是否开启音频发送 <br>
 *        + true: 开启音频发送 <br>
 *        + false: 停止音频发送 <br>
 * @param roomId 房间 ID
 * @param uid 更改本地音频发送状态的用户的 ID
 */
- (void)rtcEngine:(GameRTCEngineKit *)engine onAudioSendEnabled:(BOOL)enabled room:(NSString *)roomId uid:(NSString *)uid;

/**
 * @type callback
 * @region 音频管理
 * @brief 远端用户启停音频数据接收的回调 <br>
 *        当用户调用 enableSpeakerphone:room:{@link #GameRTCEngineKit#enableSpeakerphone:room:} 更改远端音频接收状态时，房间内其他用户会收到此回调。
 * @param engine GameRTCEngineKit 实例
 * @param enabled 是否接收远端音频 <br>
 *        + true: 开启接收远端音频 <br>
 *        + false: 停止接收远端音频 <br>
 * @param roomId 房间 ID
 * @param uid 更改远端音频接收状态的用户的 ID
 */
- (void)rtcEngine:(GameRTCEngineKit *)engine onSpeakerphoneEnabled:(BOOL)enabled room:(NSString *)roomId uid:(NSString *)uid;

/**
 * @type callback
 * @region 音频管理
 * @brief 提示本地采集的音量信息和在房间内订阅的远端用户的音量信息。<br>
 *        本回调默认不开启。你可以通过 GameRTCRoomConfig{@link #GameRTCRoomConfig} 中的参数 audioVolumeIndicationInterval 开启。
 * @param engine GameRTCEngineKit 实例
 * @param roomId 房间 ID
 * @param speakers 本地用户和订阅的远端用户的 ID 和音量。参看 GameRTCAudioVolumeInfo{@link #GameRTCAudioVolumeInfo}。
 * @param totalVolume speakers 中包含的所有音频音量之和，取值范围是：[0,255]
 * @notes  <br>
 *        + 对于本地用户：只要进行本地音频采集，回调内就会包含本地音频流的音量信息。<br>
 *        + 对于远端用户：本地必须订阅某远端用户的音频流，回调内才会包含其发送的音频流的音量信息。
 */
- (void)rtcEngine:(GameRTCEngineKit *)engine onAudioVolumeIndication:(NSString *)roomId speakers:(NSArray<GameRTCAudioVolumeInfo *> *)speakers totalVolume:(NSInteger)totalVolume;

/**
 * @type callback
 * @region 引擎管理
 * @brief 用户与 RTC 服务器连接状态发生改变时，收到此回调。
 * @param engine GameRTCEngineKit 实例
 * @param state 用户当前与 RTC 服务器的连接状态，参看 GameRTCConnectionState{@link #GameRTCConnectionState}
 */
- (void)rtcEngine:(GameRTCEngineKit *)engine onConnectionStateChanged:(GameRTCConnectionState)state;

/**
 * @type callback
 * @region 引擎管理
 * @brief 通话中用户的媒体流网络上下行质量报告回调。加入房间成功后，每隔 2 秒会触发此回调，通知房间内用户与媒体服务器之间数据交互的网络质量。
 * @param engine GameRTCEngineKit 实例
 * @param roomId 房间 ID
 * @param uid 回调的网络质量报告所属用户的用户 ID 。
 * @param txQuality 用户的媒体流上行网络质量，参看 GameRTCNetworkQuality{@link #GameRTCNetworkQuality}。
 * @param rxQuality 用户的媒体流下行网络质量，参看 GameRTCNetworkQuality{@link #GameRTCNetworkQuality}。
 * @notes <br>
 *        + 当 uid 为本地用户 ID 时，txQuality 为该用户的上行网络质量，rxQuality 为该用户的下行网络质量。<br>
 *        + 当 uid 为远端用户 ID 时，目前仅支持获取该用户的上行网络质量 txQuality ，下行网络质量 rxQuality 为 0 。
 */
- (void)rtcEngine:(GameRTCEngineKit *)engine onNetworkQuality:(NSString*)roomId uid:(NSString *)uid txQuality:(GameRTCNetworkQuality)txQuality rxQuality:(GameRTCNetworkQuality)rxQuality;

/**
 * @type callback
 * @region 引擎管理
 * @brief SDK 运行时出现了引擎相关的警告时，收到此回调。
 * @param engine GameRTCEngineKit 实例
 * @param Code 警告码，详情定义参看 GameRTCEngineWarningCode{@link #GameRTCEngineWarningCode}
 * @notes 通常情况下，SDK 上报的警告信息可以忽略，SDK 能够自动恢复。
 */
- (void)rtcEngine:(GameRTCEngineKit *)engine onEngineWarning:(GameRTCEngineWarningCode)Code;

/**
 * @type callback
 * @region 房间管理
 * @brief SDK 运行时，出现房间相关警告，收到此回调。
 * @param engine GameRTCEngineKit 实例
 * @param Code 警告代码，详情定义见: GameRTCRoomWarningCode{@link #GameRTCRoomWarningCode}
 * @param roomId 房间 ID
 * @notes 通常情况下，SDK 上报的警告信息可以忽略，SDK 能够自动恢复。
 */
- (void)rtcEngine:(GameRTCEngineKit *)engine onRoomWarning:(GameRTCRoomWarningCode)Code room:(NSString *)roomId;

/**
 * @type callback
 * @region 房间管理
 * @brief 房间相关错误回调。<br>
 * @param engine GameRTCEngineKit 实例
 * @param Code 错误码，参见 GameRTCRoomErrorCode{@link #GameRTCRoomErrorCode}。
 * @param roomId 房间 ID
 */
- (void)rtcEngine:(GameRTCEngineKit *)engine onRoomError:(GameRTCRoomErrorCode)Code room:(NSString *)roomId;

/**
 * @type callback
 * @region 监控
 * @brief 埋点日志回调
 * @param engine GameRTCEngineKit 实例
 * @param data 具体的埋点内容
 * @param type 埋点的类型
 */
- (void)rtcEngine:(GameRTCEngineKit *)engine
     onMonitorLog:(NSDictionary * _Nullable)data withType:(NSString *_Nullable)type;

@end

/**
 * @type api
 */
GAME_RTC_EXPORT @interface GameRTCEngineKit : NSObject
/**
 * @type callback
 */
@property (nonatomic, weak) id<GameRTCEngineDelegate> delegate;

/**
 * @type api
 * @region 引擎管理
 * @author chuzhongtao
 * @brief 创建 GameRTCEngine 实例。  <br>
 *        GameRTCEngine 实例成功创建后，你才可以使用 SDK 提供的其他能力。
 * @param config 引擎相关配置信息，参看 GameRTCEngineConfig{@link #GameRTCEngineConfig}。
 * @param delegate SDK 回调给应用层的 delegate。
 * @param params 预留字段，json 字符串，通常填空字符串即可。使用时，联系技术支持人员。
 * @return GameRTCEngine 实例。
 * @notes 该方法在第一次调用时初始化一个 RTCEngine 单例，除非调用 destroy{@link #GameRTCEngineKit#destroy} 方法，否则后续的所有调用均返回同一个内部实例。  <br>
 */
+ (instancetype)sharedEngineWithConfig:(GameRTCEngineConfig *)config delegate:(id<GameRTCEngineDelegate>)delegate parameters:(NSString *)params;

/**
 * @type api
 * @region 引擎管理
 * @brief 销毁引擎 <br>
 *        销毁引擎实例，并释放所有相关资源
 * @notes  <br>
 *        + 你必须在所有业务场景的最后阶段调用该方法。该方法在调用之后，会销毁所有 SDK 相关的内存，并且停止与媒体服务器的任何交互。  <br>
 *        + 你不可以在回调线程中直接调用本方法；也不可以在回调方法中等待主线程的执行而同时在主线程调用本方法，否则会造成死锁。原因是本方法为阻塞调用，会阻塞当前线程直到 SDK 彻底完成退出逻辑。
 */
+ (void)destroy;

/**
 * @type api
 * @region 引擎管理
 * @brief 获取 SDK 当前的版本号。
 * @return SDK 当前的版本号。
 */
+ (NSString *)getSdkVersion;



 /**
 * @type api
 * @region 房间管理
 * @brief 加入实时语音房间。<br>
 *        在使用实时语音的通话功能时，必须先加入实时语音房间。  <br>
 *        调用该方法后，会收到 rtcEngine:onRoomStateChanged:uid:state:extraInfo:{@link #GameRTCEngineDelegate#rtcEngine:onRoomStateChanged:uid:state:extraInfo:} 回调。
 * @param roomId
 *        房间 ID，用户调用此接口加入的房间的房间 ID。<br>
 *        房间 ID 为最大长度为 128 字节的非空字符串，支持的字符集范围为: <br>
 *             1. 26 个大写字母 A ~ Z 。<br>
 *             2. 26 个小写字母 a ~ z 。<br>
 *             3. 10 个数字 0 ~ 9 。<br>
 *             4. 下划线 "_", at 符 "@", 减号 "-"。<br>
 * @param uid
 *        用户 ID，用户调用此接口加入的房间时使用的用户 ID 。<br>
 *        用户 ID 为最大长度为 128 字节的非空字符串，支持的字符集范围为:<br>
 *             1. 26 个大写字母 A ~ Z 。 <br>
 *             2. 26 个小写字母 a ~ z 。 <br>
 *             3. 10 个数字 0 ~ 9 。 <br>
 *             4. 下划线 "_", at 符 "@", 减号 "-"。<br>
 * @param token
 *        动态密钥，用于对登录用户进行鉴权验证。<br>
 *        进入房间需要携带 Token。测试时可使用控制台生成临时 Token ，正式上线需要使用密钥 SDK 在你的服务端生成并下发 Token
 * @param config
 *        房间配置参数，参看 GameRTCRoomConfig{@link #GameRTCRoomConfig}
 * @return 方法调用结果<br>
 *         +  0: 成功 <br>
 *         + -1: roomId 为空，失败<br>
 *         + -2: userId 为空，失败<br>
 *         + -3: Engine 创建失败<br>
 * @notes <br>
 *        + 使用不同 App ID 的 App 是不能互通的。<br>
 *        + 请务必保证生成 Token 使用的 App ID 和创建引擎时使用的 App ID 相同，否则会导致加入房间失败。<br>
 *        + 用户加入房间成功后，在本端网络状况不佳的情况下，SDK 可能会与服务器失去连接，此时 SDK 将会自动重连。重连成功后，本端会收到 rtcEngine:onRoomStateChanged:uid:state:extraInfo:{@link #GameRTCEngineDelegate#rtcEngine:onRoomStateChanged:uid:state:extraInfo:} 回调。<br>
 *        + 同一个 App ID 的同一个房间内，每个用户的用户ID 必须是唯一的。如果两个用户的用户 ID 相同，则后加入房间的用户会将先加入房间的用户踢出房间，并且先加入房间的用户会收到 rtcEngine:onRoomError:room:{@link #GameRTCEngineDelegate#rtcEngine:onRoomError:room:} 回调通知。
*/
- (int)joinRoom:(NSString *)roomId uid:(NSString *)uid token:(NSString *)token config:(GameRTCRoomConfig *)config;

/**
 * @type api
 * @region 房间管理
 * @brief 离开房间<br>
 *        用户调用此方法离开房间，结束通话过程，释放所有通话相关的资源。<br>
 *        调用 joinRoom:uid:token:config:{@link #GameRTCEngineKit#joinRoom:uid:token:config:} 方法加入房间后，在通话结束时必须调用此方法结束通话，否则无法开始下一次通话。无论当前是否在房间中，都可以调用此方法。重复调用此方法不会有负面影响。<br>
 *        此方法是异步操作，调用返回时并没有真正退出房间。真正退出房间后，本端会收到 rtcEngine:onLeaveRoom:{@link #GameRTCEngineDelegate#rtcEngine:onLeaveRoom:} 回调通知。
 * @param roomId
 *        房间 ID，用户调用此接口加入的房间的房间 ID。<br>
 *        房间 ID 为最大长度为 128 字节的非空字符串，支持的字符集范围为: <br>
 *             1. 26 个大写字母 A ~ Z 。<br>
 *             2. 26 个小写字母 a ~ z 。<br>
 *             3. 10 个数字 0 ~ 9 。<br>
 *             4. 下划线 "_", at 符 "@", 减号 "-"。<br>
 * @return 方法调用结果<br>
 *         +  0：成功<br>
 *         + -1：引擎已经被销毁或者未创建，或者是房间 ID 不存在<br>
 */
- (int)leaveRoom:(NSString *)roomId;

/**
 * @type api
 * @region 房间管理
 * @brief 更新进房 token。
 *        在进房时如果收到错误码为 GameRTCJoinRoomErrorCodeJoinRoomInvalidToken 的 rtcEngine:onRoomStateChanged:uid:state:extraInfo:{@link #GameRTCEngineDelegate#rtcEngine:onRoomStateChanged:uid:state:extraInfo:} 回调，表示 token 过期导致进房失败。
 *        此时，你应调用此接口，以新 token 进房。
 * @param roomId
 *        房间 ID，用户调用此接口加入的房间的房间 ID<br>
 *        房间 ID 为最大长度为 128 字节的非空字符串，支持的字符集范围为: <br>
 *             1. 26 个大写字母 A ~ Z 。<br>
 *             2. 26 个小写字母 a ~ z 。<br>
 *             3. 10 个数字 0 ~ 9 。<br>
 *             4. 下划线 "_", at 符 "@", 减号 "-"。<br>
 * @param token
 *        动态密钥，用于对登录用户进行鉴权验证。<br>
 *        进入房间需要携带 Token。测试时可使用控制台生成临时 Token ，正式上线需要使用密钥 SDK 在你的服务端生成并下发 Token
 * @return 方法调用结果<br>
 *         +  0：成功<br>
 *         + -1：引擎已经被销毁或者未创建，或者是房间 ID 为空
 */
- (int)updateToken:(NSString *)token room:(NSString *)roomId;

/**
 * @type api
 * @region 范围语音
 * @brief 在世界房间中，使用范围语音功能时，设定语音的接收范围和衰减信息。
 * @param range 语音的收听范围，参看 GameRTCReceiveRange{@link #GameRTCReceiveRange}
 * @param roomId 房间 ID
 * @return 方法调用结果
 *         +  0：成功
 *         + -1：失败。引擎已经被销毁或者未创建，或者是房间 ID 为空
 * @notes 你应在加入房间时，通过参数设置，加入世界房间，并开启范围语音: <br>
 *        - 关于世界房间，参看 GameRTCRoomType{@link #GameRTCRoomType} 的 GameRTCRoomTypeWorld 参数。<br>
 *        - 关于范围语音，参看 enableRangeAudio{@link #GameRTCRoomConfig#enableRangeAudio}。
 */
- (int)updateReceiveRange:(GameRTCReceiveRange *)range room:(NSString *)roomId;

/**
 * @type api
 * @region 范围语音
 * @brief 使用范围、空间语音功能时，设置玩家的坐标。
 * @param position 玩家坐标值，参看 GameRTCPositionInfo{@link #GameRTCPositionInfo}
 * @param roomId 房间 ID
 * @return 方法调用结果 <br>
 *         +  0：成功 <br>
 *         + -1：失败。引擎已经被销毁或者未创建，或者是房间 ID 为空
 */
- (int)updatePosition:(GameRTCPositionInfo *)position room:(NSString *)roomId;

/**
 * @type api
 * @region 范围语音
 * @brief 使用范围语音功能时，设置音量衰减模式
 * @param type 音量衰减模式，参看 GameAttenuationType{@link #GameAttenuationType}
 * @param coefficient 音量衰减因子
 * @param roomId 房间 ID
 * @return 方法调用结果 <br>
 *         +  0：成功 <br>
 *         + -1：失败。引擎已经被销毁或者未创建，或者是房间 ID 为空，或者是未开启范围语音功能
 */
- (int)setAttenuationModel:(GameAttenuationType)type coefficient:(float)coefficient room:(NSString *)roomId;

/**
 * @type api
 * @region 空间语音
 * @brief 使用空间语音功能时，设置玩家的方位。
 * @param forward 玩家方位值，参看 GameRTCOrientation{@link #GameRTCOrientation}
 * @param right
 * @param up
 * @param roomId 房间 ID
 * @return 方法调用结果 <br>
 *         +  0：成功 <br>
 *         + -1：失败。引擎已经被销毁或者未创建，或者是房间 ID 为空
 */
- (int)updateOrientation:(GameRTCOrientation *)forward right:(GameRTCOrientation *)right up:(GameRTCOrientation *)up room:(NSString *)roomId;

/**
 * @type api
 * @region 音频管理
 * @brief 控制本地音频采集和发布状态。<br>
 *        改变该状态后，房间内其他用户会收到 rtcEngine:onMicrophoneEnabled:room:uid:{@link #GameRTCEngineDelegate#rtcEngine:onMicrophoneEnabled:room:uid:} 回调。
 * @param enable 本地音频采集和发布状态：<br>
 *        + true：开始采集本地音频，并向房间内发布。<br>
 *        + false: 停止采集本地音频，并停止发布。
 * @param roomId 房间 ID。
 * @return 方法调用结果 <br>
 *         +  0：成功 <br>
 *         + -1：引擎已经被销毁或者未创建，或者是房间 ID 为空
 */
- (int)enableMicrophone:(BOOL)enable room:(NSString *)roomId;

/**
 * @type api
 * @region 音频管理
 * @brief 控制本地语音的发送状态：发送/不发送  <br>
 *        使用此方法后，房间中的其他用户会收到回调 rtcEngine:onAudioSendEnabled:room:uid:{@link #GameRTCEngineDelegate#rtcEngine:onAudioSendEnabled:room:uid:}。
 * @param enable 发送状态，标识是否发送语音：<br>
 *        + true：发布语音 <br>
 *        + false: 不发布语音
 * @param roomId 房间 ID
 * @return 方法调用结果  <br>
 *         + 0：方法调用成功  <br>
 *         + < 0：方法调用失败  <br>
 * @notes 初次调用本方法发送本地语音时，会开启本地音频采集功能。
 *        之后再次调用本方法时，仅控制本地音频流的发送状态，不会影响本地音频采集状态。
 */
- (int)enableAudioSend:(BOOL)enable room:(NSString *)roomId;

/**
 * @type api
 * @region 音频管理
 * @brief 设置对来自远端的语音的接收状态。
 *        使用此方法后，房间中的其他用户会收到回调 rtcEngine:onSpeakerphoneEnabled:room:uid:{@link #GameRTCEngineDelegate#rtcEngine:onSpeakerphoneEnabled:room:uid:}。
 * @param enable 接收状态：<br>
 *        + true：接收 <br>
 *        + false: 不接收 <br>
 * @param roomId 房间 ID
 * @return 方法调用结果：<br>
 *         +  0：成功 <br>
 *         + -1：失败。引擎已经被销毁或者未创建，或者是房间 ID 为空
 * @notes 本方法只控制本地是否接收远端音频流，并不影响本地音频播放设备的工作状态。
 */
- (int)enableSpeakerphone:(BOOL)enable room:(NSString *)roomId;

/**
 * @type api
 * @region 音频管理
 * @brief 设置对来自指定远端用户的语音的接收状态。
 * @param enable 接收状态：<br>
 *        + true：接收 <br>
 *        + false: 不接收 <br>
 * @param roomId 房间 ID
 * @param uid 指定远端用户的 ID
 * @return 方法调用结果 <br>
 *         +  0：成功 <br>
 *         + -1：失败。引擎已经被销毁或者未创建，或者是房间 ID 为空
 * @notes 本方法只控制本地是否接收远端音频流，并不影响本地音频播放设备的工作状态。
  */
- (int)enableAudioReceive:(BOOL)enable room:(NSString *)roomId uid:(NSString*)uid;

/**
 * @type api
 * @region 音频管理
 * @brief 调节音频采集音量。
 * @param volume 音频采集音量，调节范围：[0,400]  <br>
 *        + 0：静音  <br>
 *        + 100：原始音量  <br>
 *        + 400: 最大可为原始音量的 4 倍(自带溢出保护，防止音量放大可能导致的爆音等问题)。  <br>
 * @notes 为保证更好的通话质量，建议将 volume 值设为 [0,100]。
 * @return 方法调用结果 <br>
 *         +  0：成功 <br>
 *         + -1：失败。引擎已经被销毁或者未创建，或者是房间 ID 为空
 */
- (int)setRecordingVolume:(int)volume;

/**
 * @type api
 * @region 音频管理
 * @brief 调节本地播放的所有远端用户混音后的音量。
 * @param volume 播放音量，调节范围：[0,400]  <br>
 *       + 0：静音  <br>
 *       + 100：原始音量  <br>
 *       + 400: 最大可为原始音量的 4 倍(自带溢出保护，防止音量放大可能导致的爆音等问题)。  <br>
 * @notes 为保证更好的通话质量，建议将 volume 值设为 [0,100]。
 * @return 方法调用结果 <br>
 *         +  0：成功 <br>
 *         + -1：失败。引擎已经被销毁或者未创建，或者是房间 ID 为空
 */
- (int)setPlaybackVolume:(int)volume;

/**
 * @type api
 * @region 音频管理
 * @brief 调节来自指定远端用户的音频播放音量，默认为 100。
 * @param volume 播放音量，调节范围：[0,400]  <br>
 *              + 0: 静音  <br>
 *              + 100: 原始音量  <br>
 *              + 400: 最大可为原始音量的 4 倍(自带溢出保护，防止音量放大可能导致的爆音等问题)。
 * @param roomId 房间 ID
 * @param uid 指定远端用户的 ID
 * @return 方法调用结果 <br>
 *         +  0：成功 <br>
 *         + -1：失败。引擎已经被销毁或者未创建，或者是房间 ID 为空
 */
- (int)setRemoteAudioPlaybackVolume:(int)volume room:(NSString *)roomId uid:(NSString *)uid;

/**
 * @hidden
 * @type api
 * @region 自定义音频采集渲染
 * @brief 启用外部音频采集渲染。
 * @param recordingFormat 外部音频采集数据格式，详见 GameRTCAudioFormat{@link #GameRTCAudioFormat}
 * @param playbackFormat 外部音频渲染数据格式，详见 GameRTCAudioFormat{@link #GameRTCAudioFormat}
 * @notes  <br>
 *      + 该方法应该在 joinRoom:uid:token:config:{@link #GameRTCEngineKit#joinRoom:uid:token:config:} 前使用。  <br>
 *      + 启用自定义音频采集渲染后，使用 pushExternalAudioFrame:{@link #GameRTCEngineKit#pushExternalAudioFrame:} 推送音频数据。  <br>
 *      + 启用自定义音频采集渲染后，使用 pullExternalAudioFrame:{@link #GameRTCEngineKit#pullExternalAudioFrame:} 拉取音频数据。  <br>
 */
- (void)enableExternalAudioDevice:(GameRTCAudioFormat * _Nonnull) recordingFormat playbackFormat:(GameRTCAudioFormat * _Nonnull) playbackFormat;

/**
 * @hidden
 * @type api
 * @region 自定义音频采集渲染
 * @brief 禁用已开启的自定义音频采集渲染，将音频采集渲染由自定义模块切换至内部模块。
 * @notes  <br>
 *      + 使用该 API 禁用自定义音频采集渲染后， SDK 不会自动开启内部的音频采集，需要开启 SDK 内部采集请使用 enableMicrophone:room:{@link #GameRTCEngineKit#enableMicrophone:room:}。  <br>
 *      + 调用后，在开启本地音频的情况下，用户进房发布时会使用内部模块。开启本地音频的方法详见 enableAudioSend:room:{@link #GameRTCEngineKit#enableAudioSend:room:}。  <br>
 *      + 启用自定义音频采集渲染请使用 enableExternalAudioDevice:playbackFormat:{@link #GameRTCEngineKit#enableExternalAudioDevice:playbackFormat:}。此方法需要在进房前调用。  <br>
 */
- (void)disableExternalAudioDevice;

/**
 * @hidden
 * @type api
 * @region 自定义音频采集渲染
 * @brief 推送外部音频数据。
 * @param audioFrame 音频数据帧，详见 GameRTCAudioFrame{@link #GameRTCAudioFrame}
 * @return  方法调用结果  <br>
 *          + 0: 设置成功  <br>
 *          + < 0: 设置失败  <br>
 * @notes  <br>
 *       + 推送外部音频数据前，必须开启自定义采集。  <br>
 *       + 本方法中设置的 sampleRate（音频采样率） 和 channel（音频声道） 必须与 enableExternalAudioDevice:playbackFormat:{@link #GameRTCEngineKit#enableExternalAudioDevice:playbackFormat:} 中设置的 sampleRate 和 channel 保持一致。  <br>
 *       + 此方法推送音频数据的间隔为 10 毫秒。 samples (音频采样点个数）应该为 audioFrame.sampleRate / 100，如设置采样率为 48000 时，每次应该推送 480 个采样点。  <br>
 *       + 音频采样格式为 S16。音频缓冲区内的数据格式必须为 PCM 数据，其容量大小应该为 audioFrame.samples × audioFrame.channel × 2。  <br>
 *       + 该函数运行在用户级线程内。若同时运行其他进程，将导致本进程中断。  <br>
 */
- (int)pushExternalAudioFrame:(GameRTCAudioFrame * _Nonnull) audioFrame;

/**
 * @hidden
 * @type api
 * @region 自定义音频采集渲染
 * @brief 拉取外部音频数据。
 * @param audioFrame 音频数据帧，详见 GameRTCAudioFrame{@link #GameRTCAudioFrame}
 * @return  方法调用结果  <br>
 *        + 0: 设置成功  <br>
 *        + < 0: 设置失败  <br>
 * @notes  <br>
 *       + 拉取外部音频数据前，必须开启自定义采集。  <br>
 *       + 本方法中设置的 sampleRate（音频采样率） 和 channel（音频声道） 必须与 enableExternalAudioDevice:playbackFormat:{@link #GameRTCEngineKit#enableExternalAudioDevice:playbackFormat:} 中设置的 sampleRate 和 channel 保持一致。  <br>
 *       + 此方法拉取音频数据的间隔为 10 毫秒，音频采样格式为 S16。 samples (音频采样点个数）应该为 audioFrame.sampleRate / 100，如设置采样率为 48000 时， 每次应该拉取 480 个采样点。  <br>
 *       + 音频采样格式为 S16。音频缓冲区内的数据格式必须为 PCM 数据，其容量大小应该为 audioFrame.samples × audioFrame.channel × 2。  <br>
 *       + 该函数运行在用户级线程内。若同时运行其他进程，将导致本进程中断。  <br>
 */
- (int)pullExternalAudioFrame:(GameRTCAudioFrame * _Nonnull) audioFrame;

/**
 * @type api
 * @region 音频管理
 * @brief 设置音频场景类型。  <br>
 *        你可以根据你的应用所在场景，选择合适的音频场景类型。  <br>
 *        选择音频场景后，RTC 会自动根据客户端音频路由和发布订阅状态，适用通话音量/媒体音量。  <br>
 *        本方法在进房前和进房后设置均可生效。
 * @param audioScenario 音频场景类型，适用通话音量/媒体音量
 *        详见 GameRTCAudioScenarioType{@link #GameRTCAudioScenarioType}
 * @notes  <br>
 *        + 通话音量更适合通话、会议等对信息准确度更高的场景。通话音量会激活系统硬件信号处理，使通话声音更清晰。同时，音量无法降低到 0。  <br>
 *        + 媒体音量更适合娱乐场景，因其声音的表现力会更强。媒体音量下，最低音量可以为 0。
 */
- (void)setAudioScenario:(GameRTCAudioScenarioType)audioScenario;

/**
 * @type api
 * @region 音频管理
 * @author dixing
 * @brief 设置音质档位。你应根据业务场景需要选择适合的音质档位。  <br>
 * @param audioProfile 音质档位，参看 GameRTCAudioProfileType{@link #GameRTCAudioProfileType}
 * @notes  <br>
 *        + 该方法在进房前后均可调用；  <br>
 *        + 支持通话过程中动态切换音质档位。
 */
- (void)setAudioProfile:(GameRTCAudioProfileType)audioProfile;

/**
 * @type api
 * @region 美声特效管理
 * @author luomingkang
 * @brief 设置变声特效类型。  <br>
 *        你可以根据你的需要，选择合适的变声特效。  <br>
 *        本方法只在单声道情况下生效，且与setAudioEffect接口互斥，后设置的特效会覆盖先设置的特效  <br>
 *        本方法在进房前和进房后设置均可生效。
 * @param voiceChanger 变声特效类型
 *        详见 GameRTCVoiceChangerType{@link #GameRTCVoiceChangerType}
 * @notes  <br>
 *        + 设置巨人特效后会进行基频检测，在确认男女之后选择对应的参数进行设置。  <br>
 */
- (void)setVoiceChangerType:(GameRTCVoiceChangerType)voiceChanger;

/**
 * @type api
 * @region 美声特效管理
 * @author luomingkang
 * @brief 设置混响特效类型。  <br>
 *        你可以根据你的需要，选择合适的混响特效。  <br>
 *        本方法只在单声道情况下生效，且与setVoiceType接口互斥，后设置的特效会覆盖先设置的特效  <br>
 *        本方法在进房前和进房后设置均可生效。
 * @param voiceReverb 变声特效类型
 *        详见 GameRTCVoiceReverbType{@link #GameRTCVoiceReverbType}
 */
- (void)setVoiceReverbType:(GameRTCVoiceReverbType)voiceReverb;

@end

NS_ASSUME_NONNULL_END
