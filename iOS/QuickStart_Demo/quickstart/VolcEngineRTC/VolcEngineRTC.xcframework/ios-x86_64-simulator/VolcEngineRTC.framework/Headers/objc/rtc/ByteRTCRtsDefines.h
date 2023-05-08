/*
 * Copyright (c) 2022 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief Objective-C VolcEngineRTC Common Defines
*/

#import <CoreMedia/CMTime.h>
#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
#import <UIKit/UIKit.h>
typedef UIView   ByteRTCView;
typedef UIImage  ByteRTCImage;
#elif TARGET_OS_MAC
#import <AppKit/AppKit.h>
typedef NSView   ByteRTCView;
typedef NSImage  ByteRTCImage;
#endif

#ifdef __APPLE__
#define _BYTERTC_PLATFORM_APPLE 1
#include <TargetConditionals.h>
#if TARGET_OS_IPHONE
#define _BYTERTC_PLATFORM_MAC 0
#define _BYTERTC_PLATFORM_IOS 1
#elif TARGET_IPHONE_SIMULATOR
#define _BYTERTC_PLATFORM_MAC 0
#define _BYTERTC_PLATFORM_IOS 1
#elif TARGET_OS_MAC
#define _BYTERTC_PLATFORM_MAC 1
#define _BYTERTC_PLATFORM_IOS 0
#else
#error "Unknown Apple platform"
#endif
#endif

#define BYTERTC_TARGET_MAC (_BYTERTC_PLATFORM_MAC == 1)
#define BYTERTC_TARGET_IOS (_BYTERTC_PLATFORM_IOS == 1)

#define BYTERTC_APPLE_EXPORT __attribute__((visibility("default")))




/**
 * @hidden currently not available
 */
typedef NS_ENUM(NSInteger, ByteRTSReturnStatus) {

    ByteRTSReturnStatusSuccess = 0,

    ByteRTSReturnStatusFailure = -1,

    ByteRTSReturnStatusParameterErr = -2,

    ByteRTSReturnStatusWrongState = -3,

    ByteRTSReturnStatusHasInRoom = -4,

    ByteRTSReturnStatusHasInLogin = -5,

    ByteRTSReturnStatusRoomIdInUse = -8,
};


/** 
 *  @type keytype
 *  @brief 远端用户离开房间的原因。  <br>
 */
typedef NS_ENUM(NSUInteger, ByteRTCUserOfflineReason) {
    /** 
     * @brief 远端用户调用 `leaveRoom` 方法主动退出房间。  <br>
     */
    ByteRTCUserOfflineReasonQuit = 0,
    /** 
     * @brief 远端用户因网络等原因掉线。  <br>
     */
    ByteRTCUserOfflineReasonDropped = 1,
    /** 
     * @brief 远端用户切换至隐身状态。  <br>
     */
     ByteRTCUserOfflineReasonSwitchToInvisible = 2,
    /** 
     * @brief 远端用户被踢出出房间。
     *        因调用踢出用户的 OpenAPI，远端用户被踢出房间。
     */
    ByteRTCUserOfflineReasonKickedByAdmin = 3,
};

/** 
 * @type keytype
 * @brief SDK 与信令服务器连接状态。
 */
typedef NS_ENUM(NSInteger, ByteRTCConnectionState) {
    /** 
     * @brief 连接断开超过 12s，此时 SDK 会尝试自动重连。
     */
    ByteRTCConnectionStateDisconnected = 1,
    /** 
     * @brief 首次请求建立连接，正在连接中。
     */
    ByteRTCConnectionStateConnecting = 2,
    /** 
     * @brief 首次连接成功。
     */
    ByteRTCConnectionStateConnected = 3,
    /** 
     * @brief 涵盖了以下情况：<br>
     *        + 首次连接时，10秒连接不成功; <br>
     *        + 连接成功后，断连 10 秒。自动重连中。
     */
    ByteRTCConnectionStateReconnecting = 4,
    /** 
     * @brief 连接断开后，重连成功。
     */
    ByteRTCConnectionStateReconnected = 5,
    /** 
     * @brief 处于 `ByteRTCConnectionStateDisconnected` 状态超过 10 秒，且期间重连未成功。SDK 仍将继续尝试重连。
     */
    ByteRTCConnectionStateLost = 6,
    /** 
     * @brief 连接失败，服务端状态异常。SDK 不会自动重连，请重新进房，或联系技术支持。
     */
    ByteRTCConnectionStateFailed = 7,
};

/** 
 * @type keytype
 * @brief SDK 网络连接类型。
 */
typedef NS_ENUM(NSInteger, ByteRTCNetworkType) {
    /** 
     * @brief 网络连接类型未知。
     */
    ByteRTCNetworkTypeUnknown = -1,
    /** 
     * @brief 网络连接已断开。
     */
    ByteRTCNetworkTypeDisconnected = 0,
    /** 
     * @brief 网络连接类型为 LAN 。
     */
    ByteRTCNetworkTypeLAN = 1,
    /** 
     * @brief 网络连接类型为 Wi-Fi（包含热点）。
     */
    ByteRTCNetworkTypeWIFI = 2,
    /** 
     * @brief 网络连接类型为 2G 移动网络。
     */
    ByteRTCNetworkTypeMobile2G = 3,
    /** 
     * @brief 网络连接类型为 3G 移动网络。
     */
    ByteRTCNetworkTypeMobile3G = 4,
    /** 
     * @brief 网络连接类型为 4G 移动网络。
     */
    ByteRTCNetworkTypeMobile4G = 5,
    /** 
     * @brief 网络连接类型为 5G 移动网络。
     */
    ByteRTCNetworkTypeMobile5G = 6,
};

/** 
 * @type keytype
 * @brief 媒体流网络质量。
 */
typedef NS_ENUM(NSUInteger, ByteRTCNetworkQuality) {
    /** 
     * @brief 网络质量未知。
     */
    ByteRTCNetworkQualityUnknown = 0,
    /** 
     * @brief 网络质量极好。
     */
    ByteRTCNetworkQualityExcellent = 1,
    /** 
     * @brief 主观感觉和 kNetworkQualityExcellent 差不多，但码率可能略低。
     */
    ByteRTCNetworkQualityGood = 2,
    /** 
     * @brief 主观感受有瑕疵但不影响沟通。
     */
    ByteRTCNetworkQualityPoor = 3,
    /** 
     * @brief 勉强能沟通但不顺畅。
     */
    ByteRTCNetworkQualityBad = 4,
    /** 
     * @brief 网络质量非常差，基本不能沟通。
     */
    ByteRTCNetworkQualityVeryBad = 5,
    /** 
     * @brief 12 s 内无应答，代表网络断开，将返回本枚举值。
     * 你也可以通过 rtcEngine:onConnectionStateChanged: 监听 ByteRTCConnectionStateDisconnected = 1 感知网络断开。
     * 更多网络状态信息参见 [连接状态提示](https://www.volcengine.com/docs/6348/95376)。
     */
    ByteRTCNetworkQualityDown = 6,
};

/** 
 * @type errorcode
 * @brief 回调错误码。
 *        SDK 内部遇到不可恢复的错误时，会通过 `rtcEngine:onError:` 回调通知用户。
 */
typedef NS_ENUM(NSInteger, ByteRTSErrorCode) {
    /** 
     * @brief Token 无效。
     *        进房时使用的 Token 无效或过期失效。需要用户重新获取 Token，并调用
     *        `updateToken:` 方法更新 Token。
     */
    ByteRTSErrorCodeInvalidToken               = -1000,
    /** 
     * @brief 加入房间错误。
     *        进房时发生未知错误导致加入房间失败。需要用户重新加入房间。
     */
    ByteRTSErrorCodeJoinRoom             = -1001,
    /** 
     * @brief 相同用户 ID 的用户加入本房间，当前用户被踢出房间
     */
    ByteRTSErrorCodeDuplicateLogin             = -1004,

    /** 
     * @brief 服务端调用 OpenAPI 将当前用户踢出房间
     */
    ByteRTSErrorCodeKickedOut = -1006,

    /** 
     * @brief 当调用 `createRtcRoom:` ，如果 roomId 非法，会返回 null，并抛出该错误
     */
    ByteRTSErrorCodeRoomIdIllegal = -1007,


    /** 
     * @brief Token 过期。调用 `joinRoomByKey:roomId:userInfo:rtcRoomConfig:` 使用新的 Token 重新加入房间。
     */
    ByteRTSErrorCodeTokenExpired            = -1009,
        /** 
     * @brief 调用 `updateToken:` 传入的 Token 无效
     */
    ByteRTSErrorCodeUpdateTokenWithInvalidToken     = -1010,

    /** 
     * @brief 服务端调用 OpenAPI 解散房间，所有用户被移出房间。
     */
    ByteRTSErrorCodeRoomDismiss = -1011,

    /** 
     * @brief 通话回路检测已经存在同样 roomId 的房间了
     */
    ByteRTSRoomAlreadyExist = -1013,

    /** 
     * @brief 加入多个房间时使用了不同的 uid。<br>
     *        同一个引擎实例中，用户需使用同一个 uid 加入不同的房间。
     */
    ByteRTSUserIDDifferent = -1014,

    /** 
     * @brief 服务端异常状态导致退出房间。  <br>
     *        SDK与信令服务器断开，并不再自动重连，可联系技术支持。  <br>
     */
    ByteRTSErrorCodeAbnormalServerStatus = -1084,
};

/** 
 * @type errorcode
 * @brief 回调警告码。
 *        警告码说明 SDK 内部遇到问题正在尝试恢复。警告码仅作通知。
 */
typedef NS_ENUM(NSInteger, ByteRTSWarningCode) {
    /** 
     * @deprecated since 3.46 and will be deleted in 3.52.
     */
    ByteRTSWarningCodeGetRoomFailed              = -2000,
    /** 
     * @brief 进房失败。  <br>
     *        初次进房或者由于网络状况不佳断网重连时，由于服务器错误导致进房失败。SDK 会自动重试进房。
     */
    ByteRTSWarningCodeJoinRoomFailed             = -2001,
    /** 
     * @brief 发布音视频流失败。
     *        当你在所在房间中发布音视频流时，由于服务器错误导致发布失败。SDK 会自动重试发布。
     */
    ByteRTSWarningCodePublishStreamFailed        = -2002,
    /** 
     * @hidden currently not available
     * @brief 函数调用顺序错误，当前代码中未使用。
     */
    ByteRTSWarningCodeInvokeError = -2005,
    /** 
     * @hidden for internal use only
     * @brief 调度异常，服务器返回的媒体服务器地址不可用。
     */
    ByteRTSWarningCodeInvalidExpectMediaServerAddress = -2007,
    /** 
     * @brief 发送自定义广播消息失败，当前你未在房间中。
     */
    ByteRTSWarningCodeSendCustomMessage = -2011,
    /** 
     * @deprecated since 3.46 and will be deleted in 3.52.
     * @brief 同样roomid的房间已经存在了
     */
    ByteRTSWarningCodeRoomAlreadyExist = -2015,

    /** 
     * @brief 新生成的房间已经替换了同样roomId的旧房间
     */
    ByteRTSWarningCodeOldRoomBeenReplaced = -2016
};

/** 
 * @type keytype
 * @brief 日志级别。
 */
typedef NS_ENUM(NSUInteger, ByteRTCLogLevel) {
    /** 
     * @brief 打印 trace 级别及以上级别信息。
     */
    ByteRTCLogLevelTrace,
    /** 
     * @brief 打印 debug 级别及以上级别信息。
     */
    ByteRTCLogLevelDebug,
    /** 
     * @brief 打印 info 级别及以上级别信息。
     */
    ByteRTCLogLevelInfo,
    /** 
     * @brief 打印 warning 级别及以上级别信息。
     */
    ByteRTCLogLevelWarning,
    /** 
     * @brief 打印 error 级别信息。
     */
    ByteRTCLogLevelError,
};

/** 
 * @type errorcode
 * @brief 登录结果  <br>
 *        调用 `login:uid:` 登录的结果，会通过 `rtcEngine:onLoginResult:errorCode:elapsed:` 回调通知用户。
 */
typedef NS_ENUM(NSInteger, ByteRTCLoginErrorCode) {
    /** 
     * @brief 调用 `login:uid:` 方法登录成功。
     */
    ByteRTCLoginErrorCodeSuccess = 0,
    /** 
     * @brief 调用 `login:uid:` 方法时使用的 Token 无效或过期失效。需要用户重新获取 Token。
     */
    ByteRTCLoginErrorCodeInvalidToken = -1000,
    /** 
     * @brief 登录错误  <br>
     *        调用 `login:uid:` 方法时发生未知错误导致登录失败。需要用户重新登录。
     */
    ByteRTCLoginErrorCodeLoginFailed = -1001,
    /** 
     * @brief 调用 `login:uid:` 方法时传入的用户 ID 有问题。
     */
    ByteRTCLoginErrorCodeInvalidUserId = -1002,
    /** 
     * @brief 调用 `login:uid:` 登录时服务器错误。
     */
    ByteRTCLoginErrorCodeServerError = -1003,
};

/** 
 * @type keytype
 * @brief 发送消息的可靠有序类型
 */
typedef NS_ENUM(NSInteger, ByteRTCMessageConfig) {
    /** 
     * @brief 低延时可靠有序消息
     */
    ByteRTCMessageConfigReliableOrdered = 0,
    /** 
     * @brief 超低延时有序消息
     */
    ByteRTCMessageConfigUnreliableOrdered = 1,
    /** 
     * @brief 超低延时无序消息
     */
    ByteRTCMessageConfigUnreliableUnordered = 2,
};

/** 
 * @type errorcode
 * @brief 发送消息结果，成功或失败，及失败原因
 */
typedef NS_ENUM(NSInteger, ByteRTCUserMessageSendResult) {
    /** 
     * @brief 发送消息成功
     */
    ByteRTCUserMessageSendResultSuccess = 0,
    /** 
     * @brief 发送超时，没有发送。
     */
    ByteRTCUserMessageSendResultTimeout = 1,
    /** 
     * @brief 通道断开，没有发送
     */
    ByteRTCUserMessageSendResultNetworkDisconnected = 2,
    /** 
     * @brief 找不到接收方
     */
    ByteRTCUserMessageSendResultNoReceiver = 3,
    /** 
     * @brief 远端用户没有登录或进房
     */
    ByteRTCUserMessageSendResultNoRelayPath = 4,
    /** 
     * @brief 超过 QPS 限制
     */
    ByteRTCUserMessageSendResultExceedQPS = 5,
    /** 
     * @brief 消息发送方没有加入房间
     */
    ByteRTCUserMessageSendResultNotJoin = 100,
    /** 
     * @brief 连接未完成初始化
     */
    ByteRTCUserMessageSendResultInit = 101,
    /** 
     * @brief 没有可用的数据传输通道连接
     */
    ByteRTCUserMessageSendResultNoConnection = 102,
    /** 
     * @brief 消息超过最大长度，当前为64KB
     */
    ByteRTCUserMessageSendResultExceedMaxLength = 103,
    /** 
     * @brief 接收消息的单个用户 id 为空
     */
    ByteRTCUserMessageSendResultEmptyUser = 104,
    /** 
     * @brief 房间外或应用服务器消息发送方没有登录
     */
    ByteRTCUserMessageSendResultNotLogin = 105,
    /** 
     * @brief 发送消息给业务方服务器之前没有设置参数
     */
    ByteRTCUserMessageSendResultServerParamsNotSet = 106,
    /** 
     * @brief 失败，未知错误。
     */
    ByteRTCUserMessageSendResultUnknown = 1000,
};

/** 
 * @type keytype
 * @brief 用户在线状态
 */
typedef NS_ENUM(NSInteger, ByteRTCUserOnlineStatus) {
    /** 
     * @brief 对端用户离线
     *        对端用户已经调用 `logout`，或者没有调用 `login:uid:` 进行登录
     */
    ByteRTCUserOnlineStatusOffline = 0,
    /** 
     * @brief 对端用户在线
     *        对端用户调用 `login:uid:` 登录，并且连接状态正常
     */
    ByteRTCUserOnlineStatusOnline = 1,
    /** 
     * @brief 无法获取对端用户在线状态
     *        发生级联错误、对端用户在线状态异常时返回
     */
    ByteRTCUserOnlineStatusUnreachable = 2,
};

/** 
 * @type errorcode
 * @brief 房间内广播消息发送结果
 */
typedef NS_ENUM(NSInteger, ByteRTCRoomMessageSendResult) {
    /** 
     * @brief 消息发送成功
     */
    ByteRTCRoomMessageSendResultSuccess = 200,
    /** 
     * @brief 发送超时，没有发送
     */
    ByteRTCRoomMessageSendResultTimeout = 1,
    /** 
     * @brief 通道断开，没有发送
     */
    ByteRTCRoomMessageSendResultNetworkDisconnected = 2,
    /** 
     * @brief 超过 QPS 限制
     */
    ByteRTCRoomMessageSendResultExceedQPS = 5,
    /** 
     * @brief 失败，发送方未加入房间
     */
    ByteRTCRoomMessageSendResultNotJoin = 100,
    /** 
     * @brief 失败，连接未完成初始化。
     */
    ByteRTCRoomMessageSendResultInit = 101,
    /** 
     * @brief 失败，没有可用的连接。
     */
    ByteRTCRoomMessageSendResultNoConnection = 102,
    /** 
     * @brief 消息超过最大长度，当前为 64KB
     */
    ByteRTCRoomMessageSendResultExceedMaxLength = 103,
    /** 
     * @brief 失败，未知错误。
     */
    ByteRTCRoomMessageSendResultUnknown = 1000,
};

/** 
 * @hidden for internal use only
 * @type keytype
 * @brief SDK 的服务器环境。
 */
typedef NS_ENUM(NSInteger, ByteRTCEnv) {
    /** 
     * @brief 线上环境。
     */
    ByteRTCEnvProduct = 0,
    /** 
     * @brief BOE 环境。
     */
    ByteRTCEnvBOE = 1,
    /** 
     * @brief 测试环境。
     */
    ByteRTCEnvTest = 2,
};

/** 
 * @type keytype
 * @brief App 使用的 cpu 和 memory 信息  <br>
 *        信息由 SDK 周期性（2s）地通过 `reportSysStats` 回调事件通知给用户。
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCSysStats : NSObject
/** 
 * @brief 当前系统 cpu 核数
 */
@property(assign, nonatomic) unsigned int cpu_cores;
/** 
 * @brief 当前应用的 CPU 使用率，取值范围为 [0, 1]。
 */
@property(assign, nonatomic) double cpu_app_usage;
/** 
 * @hidden currently not available
 * @brief 当前系统的 CPU 使用率，取值范围为 [0, 1]。
 */
@property(assign, nonatomic) double cpu_total_usage;
/** 
 * @brief 当前App的内存使用（单位 MB）
 */
@property(assign, nonatomic) double memory_usage;
/** 
 * @brief 全量内存（单位MB）
 */
@property(assign, nonatomic) unsigned long long full_memory;
/** 
 * @brief 系统已使用内存（单位MB）
 */
@property(assign, nonatomic) unsigned long long total_memory_usage;
/** 
 * @brief 空闲可分配内存（单位MB）
 */
@property(assign, nonatomic) unsigned long long free_memory;
/** 
 * @brief 当前应用的内存使用率（单位 %）
 */
@property(assign, nonatomic) double memory_ratio;
/** 
 * @brief 系统内存使用率（单位 %）
 */
@property(assign, nonatomic) double total_memory_ratio;
@end

/** 
 * @hidden for internal use only
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

/** 
 * @type keytype
 * @brief 云代理信息
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCCloudProxyInfo: NSObject
/** 
 * @type keytype
 * @brief 云代理服务器 IP
 */
@property(strong, nonatomic) NSString* _Nonnull cloudProxyIp;
/** 
 * @type keytype
 * @brief 云代理服务器端口
 */
@property(assign, nonatomic) int cloudProxyPort;
@end
