//
//  GameRTCEngineKitDefines.h
//  bytertc
//
//  Created by bytedance on 2021/5/26.
//

#import <Foundation/Foundation.h>

#ifndef GameRTCEngineKitDefines_h
#define GameRTCEngineKitDefines_h

#define GAME_RTC_EXPORT __attribute__((visibility("default")))

/**
 * @type keytype
 * @brief 音频场景类型。  <br>
 *        选择音频场景后，RTC 会自动根据客户端音频采集播放设备和采集播放状态，适用通话音量/媒体音量。  <br>
 *        你可以调用 setAudioScenario:{@link #GameRTCEngineKit#setAudioScenario:} 设置音频场景。  <br>
 *        如果以下音频场景类型无法满足你的业务需要，请联系技术支持同学进行定制。
 */
typedef NS_ENUM(NSInteger, GameRTCAudioScenarioType) {
    /**
     * @brief 音乐场景。默认为此场景。  <br>
     *        此场景适用于对音乐表现力有要求的场景，如音乐直播等。  <br>
     *        音频采集播放设备和采集播放状态，到音量类型的映射如下：  <br>
     *        <table>
     *           <tr><th></th><th>仅采集音频，不播放音频</th><th>仅播放音频，不采集音频</th><th>采集并播放音频</th><th>备注</th></tr>
     *           <tr><td>设备自带麦克风和扬声器/听筒</td><td>媒体音量</td><td>媒体音量</td><td>通话音量</td><td>/</td></tr>
     *           <tr><td>有线耳机</td><td>媒体音量</td><td>媒体音量</td><td>媒体音量</td><td>/</td></tr>
     *           <tr><td>蓝牙耳机</td><td>媒体音量</td><td>媒体音量</td><td>媒体音量</td><td>即使蓝牙耳机有麦克风，也只能使用设备自带麦克风进行本地音频采集。</td></tr>
     *        </table>
     */
    GameRTCAudioScenarioMusic = 0,
    /**
     * @brief 高质量通话场景。  <br>
     *        此场景适用于对音乐表现力有要求，但又希望能够使用蓝牙耳机上自带的麦克风进行音频采集的场景。  <br>
     *        此场景可以兼顾外放/使用蓝牙耳机时的音频体验，并避免使用蓝牙耳机时音量类型切换导致的听感突变。  <br>
     *        音频采集播放设备和采集播放状态，到音量类型的映射如下：<br>
     *        <table>
     *           <tr><th></th><th>仅采集音频，不播放音频</th><th>仅播放音频，不采集音频</th><th>采集并播放音频</th> <th>备注</th> </tr>
     *           <tr><td>设备自带麦克风和扬声器/听筒</td><td>媒体音量</td><td>媒体音量</td><td>通话音量</td><td>/</td></tr>
     *           <tr><td>有线耳机</td><td>媒体音量</td><td>媒体音量</td><td>媒体音量</td><td>/</td></tr>
     *           <tr><td>蓝牙耳机</td><td>通话音量</td><td>通话音量</td><td>通话音量</td><td>使用蓝牙耳机上自带的麦克风进行音频采集。</td></tr>
     *        </table>
     */
    GameRTCAudioScenarioHighqualityCommunication = 1,
    /**
     * @brief 纯通话音量场景。<br>
     *        此场景下，无论客户端音频采集播放设备和采集播放状态，全程使用通话音量。
     *        适用于需要频繁上下麦的通话或会议场景。  <br>
     *        此场景可以保持统一的音频模式，不会有音量突变的听感；
     *        最大程度地消除回声，使通话清晰度达到最优；
     *        使用蓝牙耳机时，能够使用蓝牙耳机上自带的麦克风进行音频采集。  <br>
     *        但是，会压低使用媒体音量进行播放的其他音频的音量，且音质会变差。
     */
    GameRTCAudioScenarioCommunication = 2,
    /**
     * @brief 纯媒体场景。一般不建议使用。  <br>
     *        此场景下，无论客户端音频采集播放设备和采集播放状态，全程使用媒体音量。  <br>
     *        外放通话时，极易出现回声和啸叫。
     */
    GameRTCAudioScenarioMedia = 3,
    /**
     * @brief 游戏媒体场景。需配合游戏音效消除的优化一起使用。  <br>
     *        此场景下，蓝牙耳机时使用通话音量，其它设备使用媒体音量。
     *        外放通话且无游戏音效消除优化时，极易出现回声和啸叫。
     */
    GameRTCAudioScenarioGameStreaming = 4,
};

/**
 * @type keytype
 * @brief 音质档位
 */
typedef NS_ENUM(NSInteger, GameRTCAudioProfileType) {
    /**
     * @brief 默认音质
     */
    GameRTCAudioProfileDefault = 0,
    /**
     * @brief 流畅音质。  <br>
     *        流畅优先、低延迟、低功耗、低流量消耗，适用于大部分游戏场景，如 MMORPG、MOBA、FPS 等游戏中的小队语音、组队语音、国战语音等。
     */
    GameRTCAudioProfileFluent = 1,
    /**
     * @brief 标准音质。  <br>
     *        适用于对音质有一定要求的场景，同时延时、功耗和流量消耗相对适中，适合 Sirius 等狼人杀类游戏。
     */
    GameRTCAudioProfileStandard = 2,
    /**
     * @brief 高清音质  <br>
     *        超高音质，同时延时、功耗和流量消耗相对较大，适用于连麦 PK、在线教育等场景。 <br>
     *        游戏场景不建议使用。
     */
    GameRTCAudioProfileHD = 3,
};


/**
 * @hidden
 * @type keytype
 * @brief SDK 的服务器环境。
 */
typedef NS_ENUM(NSInteger, GameRTCEnv) {
    /**
     * @hidden
     * @brief 线上环境。
     */
    GameRTCEnvProduct = 0,
    /**
     * @hidden
     * @brief BOE 环境。
     */
    GameRTCEnvBOE = 1,
    /**
     * @hidden
     * @brief 测试环境。
     */
    GameRTCEnvTest = 2,
};

/**
 * @type keytype
 * @brief 引擎配置信息
 */
GAME_RTC_EXPORT @interface GameRTCEngineConfig : NSObject
/**
 * @brief 应用 ID。只有使用相同 appId 创建的 Engine 实例之间才能进行实时音视频通话
 */
@property (nonatomic, copy) NSString * _Nonnull appId;

@end

/**
 * @type keytype
 * @brief 房间类型
 */
typedef NS_ENUM(NSInteger, GameRTCRoomType) {
    /**
     * @brief 小队房间。默认值。<br>
     *        进入同一小队房间的成员是队友关系。 <br>
     *        进入小队房间后，打开麦克风可以向房间内所有队友讲话；打开扬声器就可以收听房间内所有队友讲话。
     */
    GameRTCRoomTypeTeam,
    /**
     * @brief 世界房间。<br>
     *        你需要判断进入同一房间的成员是否为队友关系，进而决定收听逻辑。
     */
    GameRTCRoomTypeWorld,
};

/**
 * @type keytype
 * @brief 房间配置信息
 */
GAME_RTC_EXPORT @interface GameRTCRoomConfig : NSObject
/**
 * @brief 设置是否开启范围语音<br>
 *        + true：开启<br>
 *        + false: 关闭  <br>
 *        + 开启范围语音时，非同一小队玩家的声音会根据距离衰减，如果不需要设置为 false 即可。
 */
@property (nonatomic, assign) BOOL enableRangeAudio;
/**
 * @brief 设置是否开启空间语音<br>
 *        + true：开启<br>
 *        + false: 关闭（默认设置）  <br>
 *        + 开启空间语音后，非同一小队的队友之间收听的声音会根据设置的坐标和方位不同而产生空间音效，如果不需要设置为 false 即可。
 */
@property (nonatomic, assign) BOOL enableSpatialAudio;
/**
 * @brief 收到 rtcEngine:onAudioVolumeIndication:speakers:totalVolume:{@link #GameRTCEngineDelegate#rtcEngine:onAudioVolumeIndication:speakers:totalVolume:} 音量提示回调的时间间隔：  <br>
 *        + ≤ 0：禁用音量提示功能。  <br>
 *        + > 0：启用音量提示功能，并设置收到音量提示回调的时间间隔。单位为毫秒。<br>
 * @notes 建议设置为大于等于 2000 毫秒；小于 10 毫秒时，行为未定义。
 */

@property (nonatomic, assign) int audioVolumeIndicationInterval;
/**
 * @brief 房间类型，参看 GameRTCRoomType{@link #GameRTCRoomType}。
 */
@property (nonatomic, assign) GameRTCRoomType roomType;

@end

/**
 * @type keytype
 * @brief 使用范围语音功能时，语音的接收范围
 */
GAME_RTC_EXPORT @interface GameRTCReceiveRange : NSObject
/**
 * @brief 收听声音无衰减的最小范围值。<br>
 *        当收听者和声源距离小于 min 的时候，收听到的声音完全无衰减。
 */
@property (nonatomic, assign) int min;
/**
 *  @brief 能够收听到声音的最大范围。<br>
 *        当收听者和声源距离大于 max 的时候，无法收听到声音。<br>
 *        当收听者和声源距离处于 [min, max) 之间时，收听到的音量根据距离有衰减。
 */
@property (nonatomic, assign) int max;

@end

/**
 * @type keytype
 * @brief 玩家位置信息
 */
GAME_RTC_EXPORT @interface GameRTCPositionInfo : NSObject
/**
 * @brief x 坐标
 */
@property (nonatomic, assign) int x;
/**
 * @brief y 坐标
 */
@property (nonatomic, assign) int y;
/**
 * @brief z 坐标
 */
@property (nonatomic, assign) int z;

@end

/**
 * @type keytype
 * @brief 描述空间语音中玩家的方位
 */
GAME_RTC_EXPORT @interface GameRTCOrientationInfo : NSObject
/**
 * @brief 前向方位，在 x 轴的投影
 */
@property (nonatomic, assign) float x_axis_0;
/**
 * @brief 前向方位，在 y 轴的投影
 */
@property (nonatomic, assign) float y_axis_0;
/**
 * @brief 前向方位，在 z 轴的投影
 */
@property (nonatomic, assign) float z_axis_0;
/**
 * @brief 右手方位，在 x 轴的投影
 */
@property (nonatomic, assign) float x_axis_1;
/**
 * @brief 右手方位，在 y 轴的投影
 */
@property (nonatomic, assign) float y_axis_1;
/**
 * @brief 右手方位，在 z 轴的投影
 */
@property (nonatomic, assign) float z_axis_1;
/**
 * @brief 头顶方位，在 x 轴的投影
 */
@property (nonatomic, assign) float x_axis_2;
/**
 * @brief 头顶方位，在 y 轴的投影
 */
@property (nonatomic, assign) float y_axis_2;
/**
 * @brief 头顶方位，在 z 轴的投影
 */
@property (nonatomic, assign) float z_axis_2;

@end

/**
 * @type keytype
 * @brief 用户离开房间的原因
 */

typedef NS_ENUM(NSUInteger, GameRTCUserLeaveType) {
    /**
     * @brief 用户主动离开，即调用 leaveRoom:{@link #GameRTCEngineKit#leaveRoom:} 方法退出房间。
     */
    GameRTCUserLeaveTypeQuit = 0,
    /**
     * @brief 用户掉线。用户因为网络等原因掉线，或切换为隐身状态。
     */
    GameRTCUserLeaveTypeDropped = 1,
};

/**
 * @hidden
 */
typedef NS_ENUM(NSInteger, GameRTCLogLevel) {
    /**
     * @hidden
     * @brief 打印 trace 级别及以上级别信息。
     */
    GameRTCLogLevelTrace,
    /**
     * @hidden
     * @brief 打印 debug 级别及以上级别信息。
     */
    GameRTCLogLevelDebug,
    /**
     * @hidden
     * @brief 打印 info 级别及以上级别信息。
     */
    GameRTCLogLevelInfo,
    /**
     * @hidden
     * @brief 打印 warning 级别及以上级别信息。
     */
    GameRTCLogLevelWarning,
    /**
     * @hidden
     * @brief 打印 error 级别信息。
     */
    GameRTCLogLevelError,
};

/**
 * @type keytype
 * @brief 用户与 RTC 服务器的连接状态
 */
typedef NS_ENUM(NSInteger, GameRTCConnectionState) {
    /**
     * @brief 连接中断。
     */
    GameRTCConnectionStateDisconnected = 0,
    /**
     * @brief 首次连接，正在连接中。
     */
    GameRTCConnectionStateConnecting = 1,
    /**
     * @brief 首次连接成功。
     */
    GameRTCConnectionStateConnected = 2,
    /**
     * @brief 连接断开后，重新连接中。
     */
    GameRTCConnectionStateReconnecting = 3,
    /**
     * @brief 连接断开后，重连成功。
     */
    GameRTCConnectionStateReconnected = 4,
    /**
     * @brief 网络连接断开超过 10 秒，仍然会继续重连。
     */
    GameRTCConnectionStateLost = 5,
};

/**
 * @type keytype
 * @brief 用户的媒体流网络上下行质量
 */
typedef NS_ENUM(NSUInteger, GameRTCNetworkQuality) {
    /**
     * @brief 网络质量未知。
     */
    GameRTCNetworkQualityUnknown = 0,
    /**
     * @brief 网络质量极好。
     */
    GameRTCNetworkQualityExcellent = 1,
    /**
     * @brief 用户主观感觉近似“极好”，但码率可能略低于“极好”。
     */
    GameRTCNetworkQualityGood = 2,
    /**
     * @brief 用户主观感受有瑕疵但不影响沟通。
     */
    GameRTCNetworkQualityPoor = 3,
    /**
     * @brief 勉强能够沟通但不顺畅。
     */
    GameRTCNetworkQualityBad = 4,
    /**
     * @brief 网络质量非常差，基本不能沟通。
     */
    GameRTCNetworkQualityVBad = 5,
};

/**
 * @type errorcode
 * @brief 加入房间错误码
 */
typedef NS_ENUM(NSInteger, GameRTCJoinRoomErrorCode) {
    /**
     * @brief 加入房间成功
     */
    GameRTCJoinRoomErrorCodeJoinRoomSuccess = 0,
    /**
     * @brief 调用 joinRoom:uid:token:config:{@link #GameRTCEngineKit#joinRoom:uid:token:config:} 方法时使用的 Token 无效或过期失效。 <br>
     *        需要用户重新获取 Token，并调用 updateToken:room:{@link #GameRTCEngineKit#updateToken:room:} 方法更新 Token。
     */
    GameRTCJoinRoomErrorCodeJoinRoomInvalidToken = -1000,
    /**
     * @brief 加入房间错误。
     *        调用 joinRoom:uid:token:config:{@link #GameRTCEngineKit#joinRoom:uid:token:config:} 方法时发生未知错误导致加入房间失败。需要用户重新加入房间。
     */
    GameRTCJoinRoomErrorCodeJoinRoomError = -1001,
    /**
     * @brief 加入房间失败。
     *        调用 joinRoom:uid:token:config:{@link #GameRTCEngineKit#joinRoom:uid:token:config:} 加入房间或由于网络状况不佳断网重连时，由于服务器错误导致用户加入房间失败，SDK 会自动重试加入房间。
     */
    GameRTCJoinRoomErrorCodeJoinRoomFailed = -2001
};

/**
 * @type errorcode
 * @brief 房间警告码
 */
typedef NS_ENUM(NSInteger, GameRTCRoomWarningCode) {
    /**
     *  @brief 发布音视频流失败。  <br>
     *         用户在所在房间中发布音视频流时，由于服务器错误导致发布失败。SDK 会自动重试发布。
     */
    GameRTCRoomWarningCodePublishStreamFailed       = -2002,
    /**
     *  @brief 订阅音视频流失败。  <br>
     *         当前房间中找不到订阅的音视频流导致订阅失败。建议用户退出重试。
     */
    GameRTCRoomWarningCodeStreamFailed404           = -2003,
    /**
     *  @brief 订阅音视频流失败。  <br>
     *         用户订阅所在房间中的音视频流时，由于服务器错误导致订阅失败。SDK 会自动重试订阅。
     */
    GameRTCRoomWarningCodeStreamFailed5xx           = -2004,
    /**
     *  @hidden
     *  @brief 调度异常，服务器返回的媒体服务器地址不可用。
    */
    GameRTCRoomWarningCodeExpectMediaServerAddress  = -2007,
};

/**
 * @type errorcode
 * @brief 引擎相关警告码
 */
typedef NS_ENUM(NSInteger, GameRTCEngineWarningCode) {
    /**
     *  @brief 麦克风权限异常，当前应用没有获取麦克风权限
     */
    GameRTCEngineWarningCodeNoMicrophonePermission                  = -5002,
    /**
     *  @brief 音频采集设备启动失败。当前音频采集设备可能被其他应用占用
     */
    GameRTCEngineWarningCodeAudioDeviceManagerRecordingStartFail    = -5003,
    /**
     * @brief 音频播放设备启动失败。原因可能为系统资源不足，或参数错误
     */
    GameRTCEngineWarningCodeAudioDeviceManagerPlayoutStartFail      = -5004,
    /**
     * @brief 无可用音频采集设备，请插入可用采集设备
     */
    GameRTCEngineWarningCodeNoRecordingDevice                       = -5005,
    /**
     * @brief 无可用音频播放设备，请插入可用播放设备
     */
    GameRTCEngineWarningCodeNoPlayoutDevice                         = -5006
};

/**
 * @type errorcode
 * @brief 房间相关错误码
 */
typedef NS_ENUM(NSInteger, GameRTCRoomErrorCode) {
    /**
     * @brief 因没有发布音频流权限，导致在房间中发布音视频流失败。  <br>
     *        需要检查 appId 是否正确。
     */
    GameRTCRoomErrorCodeNoPublishPermission         = -1002,
    /**
     * @brief 因没有订阅音频流权限，导致在房间中订阅音视频流失败。  <br>
     *        需要检查 appId 是否正确。
     */
    GameRTCRoomErrorCodeNoSubscribePermission       = -1003,
    /**
     * @brief 用户被踢出房间：<br>
     *        + 本地用户所在房间中有相同用户 ID 的用户加入房间，导致前者被踢出房间；<br>
     *        + 因调用踢出用户的 OpenAPI，被踢出房间；<br>
     *        + 因调用解散房间的 OpenAPI，离开房间。
     */
    GameRTCRoomErrorCodeDuplicateLogin              = -1004,
};

/**
 * @type keytype
 * @brief 音频流来源的用户 ID, 及对应的音量。
 */
GAME_RTC_EXPORT @interface GameRTCAudioVolumeInfo : NSObject
/**
 * @brief 音频流来源的用户 ID
 */
@property (copy, nonatomic) NSString * _Nonnull uid;
/**
 * @brief 音量，取值范围是：[0,255]
 */
@property (assign, nonatomic) NSUInteger volume;
@end


/**
 * @type keytype
 * @brief 音频采样率
 */
typedef NS_ENUM(NSInteger, GameRTCAudioSampleRate) {
    /**
     * @brief 8000 采样率
     */
    GameRTCAudioSampleRate8000 = 8000,
    /**
     * @brief 16000 采样率
     */
    GameRTCAudioSampleRate16000 = 16000,
    /**
     * @brief 32000 采样率
     */
    GameRTCAudioSampleRate32000 = 32000,
    /**
     * @brief 44100 采样率
     */
    GameRTCAudioSampleRate44100 = 44100,
    /**
     * @brief 48000 采样率
     */
    GameRTCAudioSampleRate48000 = 48000
};

/**
 * @type keytype
 * @brief 音频声道
 */
typedef NS_ENUM(NSInteger, GameRTCAudioChannel) {
    /**
     * @brief 单声道
    */
    GameRTCAudioChannelMono = 1,
    /**
     * @brief 双声道
    */
    GameRTCAudioChannelStereo = 2
};

/**
 * @type keytype
 * @brief 音频参数格式
 */
GAME_RTC_EXPORT @interface GameRTCAudioFormat : NSObject
/**
 * @brief 音频采样率，详见 GameRTCAudioSampleRate{@link #GameRTCAudioSampleRate}
*/
@property (nonatomic, assign) GameRTCAudioSampleRate sampleRate;
/**
 * @brief 音频声道，详见 GameRTCAudioChannel{@link #GameRTCAudioChannel}
*/
@property (nonatomic, assign) GameRTCAudioChannel channel;
@end

/**
 *  @type keytype
 *  @brief 音频帧
*/
GAME_RTC_EXPORT @interface GameRTCAudioFrame : NSObject
/**
 *  @brief 音频帧数据
*/
@property (strong, nonatomic) NSData * _Nonnull buffer;
/**
 *  @brief 此音频帧描述的样点数
*/
@property (assign, nonatomic) int samples;
/**
 *  @brief 音频声道，详见 GameRTCAudioChannel{@link #GameRTCAudioChannel}
*/
@property (assign, nonatomic) GameRTCAudioChannel channel;
/**
 *  @brief 音频采样率，详见 GameRTCAudioSampleRate{@link #GameRTCAudioSampleRate}
*/
@property (assign, nonatomic) GameRTCAudioSampleRate sampleRate;
@end

#endif /* GameRTCEngineKitDefines_h */
