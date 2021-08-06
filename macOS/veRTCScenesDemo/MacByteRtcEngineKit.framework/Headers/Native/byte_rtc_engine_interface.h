#ifndef I_BYTE_RTC_ENGINE_H
#define I_BYTE_RTC_ENGINE_H

#ifdef WIN32
    #define BYTE_API __declspec(dllexport)
#elif __APPLE__
#include <TargetConditionals.h>
    #if TARGET_OS_MAC && !(TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
        #define BYTE_API __attribute__((__visibility__("default"))) extern "C"
    #else
        #define BYTE_API __attribute__((__visibility__("default")))
    #endif
#else
    #define BYTE_API __attribute__((__visibility__("default")))
#endif

#include <stddef.h>
#include <stdio.h>
#include <stdarg.h>
#include <memory>
#include "byte_rtc_engine_defines.h"
#include "byte_rtc_engine_lite_interface.h"
#include "byte_rtc_engine_event_handler.h"
#include "byte_rtc_video_frame.h"

namespace bytertc {

class IRTCRoomEventHandler;
/**
 * @type api
 * @brief 引擎API
 *      IRtcEngine用IRtcEngineEventHandler 注册接口类方法向应用程序发送回调通知
 */
class IRtcEngine : public IRtcRoom,
                   public IRtcEngineLite {
public:

    /**
     * @hidden
     * @brief 析构函数
     */
    virtual ~IRtcEngine() {
    }

    /**
     * @type api
     * @region 房间管理
     * @brief 加入房间。用户调用此方法加入房间，在一个房间内的用户间可以相互通话。  <br>
     *        用户调用 CreateByteRtcEngine{@link #CreateByteRtcEngine} 创建 RTC 引擎后，需调用此方法加入房间实现同其他用户进行音视频通话。如果用户调用此方法加入房间，则后续重复调用此方法均会失败，用户必须调用 LeaveChannel{@link #LeaveChannel} 退出当前房间后，才能加入下一个房间。  <br>
     *        用户调用此方法加入房间成功后，会收到 OnJoinChannelSuccess{@link #OnJoinChannelSuccess} 回调通知。  <br>
     * @param [in] token 动态密钥，用于对登录用户进行鉴权验证。  <br>
     *        进入房间需要携带 Token。测试时可使用控制台生成临时 Token ，正式上线需要使用密钥 SDK 在您的服务端生成并下发 Token 。  <br>
     * @param [in] channel_id 房间ID ，用户调用此接口加入的房间的房间ID 。  <br>
     *        房间ID 为最大长度为128字节的非空字符串，支持的字符集范围为:  <br>
     *            1. 26个大写字母 A ~ Z 。  <br>
     *            2. 26个小写字母 a ~ z 。  <br>
     *            3. 10个数字 0 ~ 9 。  <br>
     *            4. 下划线"_", at符"@", 减号"-"。  <br>
     * @param [in] uid 用户ID ，用户调用此接口加入的房间时使用的用户ID 。  <br>
     *        用户ID 为最大长度为128字节的非空字符串，支持的字符集范围为:  <br>
     *            1. 26个大写字母 A ~ Z 。  <br>
     *            2. 26个小写字母 a ~ z 。  <br>
     *            3. 10个数字 0 ~ 9 。  <br>
     *            4. 下划线"_", at符"@", 减号"-"。  <br>
     * @param [in] info 预留参数。  <br>
     * @return 方法调用结果。  <br>
     *        +  0: 成功  <br>
     *        + -1: channel_id 为空，失败  <br>
     *        + -2: uid 为空，失败  <br>
     * @notes  <br>
     *       + 使用不同 App ID 的 App 是不能互通的。  <br>
     *       + 请务必保证生成 Token 使用的 App ID 和创建引擎时使用的 App ID 相同，否则会导致加入房间失败。  <br>
     *       + 用户加入房间成功后，在本地网络状况不佳的情况下，SDK 可能会与服务器失去连接，此时 SDK 将会自动重连。重连成功后，本地会收到 OnRejoinChannelSuccess{@link #OnRejoinChannelSuccess} 回调通知。  <br>
     *       + 房间模式（房间模式参考 SetChannelProfile{@link #SetChannelProfile} ）为通话模式下的用户或直播、游戏、云游戏模式下用户角色（用户角色参考 SetClientRole{@link #SetClientRole} ）为主播、观众的用户加入房间成功后，远端用户会收到 OnUserJoined{@link #OnUserJoined} 回调通知。  <br>
     *       + 同一个 App ID 的同一个房间内，每个用户的用户ID 必须是唯一的。如果两个用户的用户ID 相同，则后加入房间的用户会将先加入房间的用户踢出房间，并且先加入房间的用户会收到 OnError{@link #OnError} 回调通知，错误类型为重复登录 BRERR_DUPLICATE_LOGIN{@link #BRERR_DUPLICATE_LOGIN} 。  <br>
     */
    virtual int JoinChannel(const char* token, const char* channel_id, const char* uid, const char* info) = 0;

    /**
     * @hidden
     */
    virtual int JoinChannel(
            const char* token, const char* channel_id, const char* uid, const char* info, const char* trace_id) = 0;
private:
    void JoinChannel(const char* token, const char* uid, const char* info) override {};
    void SetRtcRoomEventHandler(IRTCRoomEventHandler* room_event_handler) override {};
};

/**
 * @type api
 * @region 引擎管理
 * @brief 创建 RTCEngine 实例。  <br>
 *        此方法应该作为正常 SDK 流程中的第一步操作，通过创建一个 RTCEngine 实例，来使用 SDK 的其他能力。
 * @param [in] app_id  <br>
 *        每个应用的唯一标识符，由 VRTC 控制台随机生成的。不同的 AppId 生成的实例在 VRTC 中进行音视频通话完全独立，无法互通。
 * @param [in] event_handler  <br>
 *        SDK 回调给应用层的 Callback 对象，详见 IRtcEngineEventHandler{@link #IRtcEngineEventHandler} 。
 * @return 可用的 IRtcEngine{@link #IRtcEngine} 实例。
 * @notes  <br>
 *        + 该方法在第一次调用时初始化一个 RTCEngine 单例，除非调用 DestroyByteRtcEngine{@link #DestroyByteRtcEngine}
 *          方法，否则后续的所有调用均返回同一个实例。  <br>
 *        + 连续多次调用该方法不会创建不同的 IRtcEngine{@link #IRtcEngine} 实例，仅第一次设置的 event_handler 是有效值，后续
 *          的调用均会被忽略。  <br>
 *        + 必须使用相同的 AppId，App 间才能进行通话。  <br>
 *        + 在调用 DestroyByteRtcEngine{@link #DestroyByteRtcEngine} 之后会销毁 IRtcEngine{@link #IRtcEngine} 实例，再次调用
 *          CreateByteRtcEngine{@link #CreateByteRtcEngine} 方法则会重新创建一个全新的 IRtcEngine{@link #IRtcEngine} 实例。
 */
BYTE_API bytertc::IRtcEngine* CreateByteRtcEngine(const char* app_id, bytertc::IRtcEngineEventHandler* event_handler);

/**
 * @type api
 * @region 引擎管理
 * @brief 创建 RTCEngine 实例。  <br>
 *        此方法应该作为正常 SDK 流程中的第一步操作，通过创建一个 RTCEngine 实例，来使用 SDK 的其他能力。
 * @param [in] app_id  <br>
 *        每个应用的唯一标识符，由 VRTC 控制台随机生成的。不同的 AppId 生成的实例在 VRTC 中进行音视频通话完全独立，无法互通。
 * @param [in] event_handler  <br>
 *        SDK 回调给应用层的 Callback 对象，详见 IRtcEngineEventHandler{@link #IRtcEngineEventHandler} 。
 * @param [in] parameters  <br>
 *        JSON字符串，用以覆盖全局参数，详情可见 SetParameters{@link #SetParameters}
 * @return 可用的 IRtcEngine{@link #IRtcEngine} 实例。
 * @notes  <br>
 *        + 该方法在第一次调用时初始化一个 RTCEngine 单例，除非调用 DestroyByteRtcEngine{@link #DestroyByteRtcEngine}
 *          方法，否则后续的所有调用均返回同一个实例。  <br>
 *        + 连续多次调用该方法不会创建不同的 IRtcEngine{@link #IRtcEngine} 实例，仅第一次设置的 event_handler 是有效值，后续
 *          的调用均会被忽略。  <br>
 *        + 必须使用相同的 AppId，App 间才能进行通话。  <br>
 *        + 在调用 DestroyByteRtcEngine{@link #DestroyByteRtcEngine} 之后会销毁 IRtcEngine{@link #IRtcEngine} 实例，再次调用
 *          CreateByteRtcEngine{@link #CreateByteRtcEngine} 方法则会重新创建一个全新的 IRtcEngine{@link #IRtcEngine} 实例。
 */
BYTE_API bytertc::IRtcEngine* CreateByteRtcEngineWithParameters(const char* app_id, bytertc::IRtcEngineEventHandler* event_handler, const char* parameters);

/**
 * @hidden
 * @region 引擎管理
 * @brief 创建游戏 RTCEngine 实例。
 * @param [in] app_id  <br>
 *        每个应用的唯一标识符。不同的 AppId 生成的实例进行音视频通话完全独立，无法互通。
 * @param [in] event_handler  <br>
 *        SDK 回调给应用层的 Callback 对象，详见 IRtcEngineEventHandler{@link #IRtcEngineEventHandler} 。
 * @return 可用的 IRtcEngine{@link #IRtcEngine} 实例。
 * @notes  <br>
 *        + 该方法创建并初始化 IRtcEngine{@link #IRtcEngine} 实例。使用 IRtcEngine，必须先调用该接口进行初始化。  <br>
 *        + IRtcEngine{@link #IRtcEngine} 实例通过指定的 IRtcEngineEventHandler{@link #IRtcEngineEventHandler}
 *          通知应用程序引擎运行时的事件。IRtcEngineEventHandler{@link #IRtcEngineEventHandler} 中定义的所有方法都是可选实现的。
 */
BYTE_API bytertc::IRtcEngine* CreateGameRtcEngine(const char* app_id, bytertc::IRtcEngineEventHandler* event_handler);

/**
 * @hidden
 * @region 引擎管理
 * @brief 创建游戏 RTCEngine 实例。
 * @param [in] app_id  <br>
 *        每个应用的唯一标识符。不同的 AppId 生成的实例进行音视频通话完全独立，无法互通。
 * @param [in] event_handler  <br>
 *        SDK 回调给应用层的 Callback 对象，详见 IRtcEngineEventHandler{@link #IRtcEngineEventHandler} 。
 * @param [in] parameters  <br>
 *        JSON字符串，用以覆盖全局参数，详情可见 SetParameters{@link #SetParameters}
 * @return 可用的 IRtcEngine{@link #IRtcEngine} 实例。
 * @notes  <br>
 *        + 该方法创建并初始化 IRtcEngine{@link #IRtcEngine} 实例。使用 IRtcEngine，必须先调用该接口进行初始化。  <br>
 *        + IRtcEngine{@link #IRtcEngine} 实例通过指定的 IRtcEngineEventHandler{@link #IRtcEngineEventHandler}
 *          通知应用程序引擎运行时的事件。IRtcEngineEventHandler{@link #IRtcEngineEventHandler} 中定义的所有方法都是可选实现的。
 */
BYTE_API bytertc::IRtcEngine* CreateGameRtcEngineWithParameters(
        const char* app_id, bytertc::IRtcEngineEventHandler* event_handler, const char* parameters);

/**
 * @hidden
 * @region 引擎管理
 * @brief 创建 RTCEngine 实例。
 * @param [in] app_id  <br>
 *        每个应用的唯一标识符。不同的 AppId 生成的实例进行音视频通话完全独立，无法互通。
 * @param [in] event_handler  <br>
 *        SDK 回调给应用层的 Callback 对象，详见 IRtcEngineEventHandler{@link #IRtcEngineEventHandler} 。
 * @return 可用的 IRtcEngine{@link #IRtcEngine} 实例。
 * @notes  <br>
 *        + 该方法创建并初始化 IRtcEngine{@link #IRtcEngine} 实例。使用 IRtcEngine，必须先调用该接口进行初始化。  <br>
 *        + IRtcEngine{@link #IRtcEngine} 实例通过指定的 IRtcEngineEventHandler{@link #IRtcEngineEventHandler}
 *          通知应用程序引擎运行时的事件。IRtcEngineEventHandler{@link #IRtcEngineEventHandler} 中定义的所有方法都是可选实现的。
 */
BYTE_API bytertc::IRtcEngine* createByteRtcEngineWithPtr(
        const char* app_id, std::unique_ptr<bytertc::IRtcEngineEventHandler> event_handler);

/**
 * @hidden
 * @region 引擎管理
 * @brief 创建 RTCEngine 实例。
 * @param [in] app_id  <br>
 *        每个应用的唯一标识符。不同的 AppId 生成的实例进行音视频通话完全独立，无法互通。
 * @param [in] event_handler  <br>
 *        SDK 回调给应用层的 Callback 对象，详见 IRtcEngineEventHandler{@link #IRtcEngineEventHandler} 。
 * @param [in] parameters  <br>
 *        JSON字符串，用以覆盖全局参数，详情可见 SetParameters{@link #SetParameters}
 * @return 可用的 IRtcEngine{@link #IRtcEngine} 实例。
 * @notes  <br>
 *        + 该方法创建并初始化 IRtcEngine{@link #IRtcEngine} 实例。使用 IRtcEngine，必须先调用该接口进行初始化。  <br>
 *        + IRtcEngine{@link #IRtcEngine} 实例通过指定的 IRtcEngineEventHandler{@link #IRtcEngineEventHandler}
 *          通知应用程序引擎运行时的事件。IRtcEngineEventHandler{@link #IRtcEngineEventHandler} 中定义的所有方法都是可选实现的。
 */
BYTE_API bytertc::IRtcEngine* createByteRtcEngineWithPtrAndParameters(
        const char* app_id, std::unique_ptr<bytertc::IRtcEngineEventHandler> event_handler,
        const char* parameters);

/**
 * @hidden
 * @region 引擎管理
 * @brief 创建游戏 RTCEngine 实例。
 * @param [in] app_id  <br>
 *        每个应用的唯一标识符。不同的 AppId 生成的实例进行音视频通话完全独立，无法互通。
 * @param [in] event_handler  <br>
 *        SDK 回调给应用层的 Callback 对象，详见 IRtcEngineEventHandler{@link #IRtcEngineEventHandler} 。
 * @return 可用的 IRtcEngine{@link #IRtcEngine} 实例。
 * @notes  <br>
 *        + 该方法创建并初始化 IRtcEngine{@link #IRtcEngine} 实例。使用 IRtcEngine，必须先调用该接口进行初始化。  <br>
 *        + IRtcEngine{@link #IRtcEngine} 实例通过指定的 IRtcEngineEventHandler{@link #IRtcEngineEventHandler}
 *          通知应用程序引擎运行时的事件。IRtcEngineEventHandler{@link #IRtcEngineEventHandler} 中定义的所有方法都是可选实现的。
 */
BYTE_API bytertc::IRtcEngine* createGameRtcEngineWithPtr(
        const char* app_id, std::unique_ptr<bytertc::IRtcEngineEventHandler> event_handler);

/**
 * @hidden
 * @region 引擎管理
 * @brief 创建游戏 RTCEngine 实例。
 * @param [in] app_id  <br>
 *        每个应用的唯一标识符。不同的 AppId 生成的实例进行音视频通话完全独立，无法互通。
 * @param [in] event_handler  <br>
 *        SDK 回调给应用层的 Callback 对象，详见 IRtcEngineEventHandler{@link #IRtcEngineEventHandler} 。
 * @param [in] parameters  <br>
 *        JSON字符串，用以覆盖全局参数，详情可见 SetParameters{@link #SetParameters}
 * @return 可用的 IRtcEngine{@link #IRtcEngine} 实例。
 * @notes  <br>
 *        + 该方法创建并初始化 IRtcEngine{@link #IRtcEngine} 实例。使用 IRtcEngine，必须先调用该接口进行初始化。  <br>
 *        + IRtcEngine{@link #IRtcEngine} 实例通过指定的 IRtcEngineEventHandler{@link #IRtcEngineEventHandler}
 *          通知应用程序引擎运行时的事件。IRtcEngineEventHandler{@link #IRtcEngineEventHandler} 中定义的所有方法都是可选实现的。
 */
BYTE_API bytertc::IRtcEngine* createGameRtcEngineWithPtrAndParameters(
        const char* app_id, std::unique_ptr<bytertc::IRtcEngineEventHandler> event_handler,
        const char* parameters);

/**
 * @type api
 * @region 引擎管理
 * @brief 销毁由 CreateByteRtcEngine{@link #CreateByteRtcEngine} 创建的 RTCEngine 实例，并释放所有相关资源。
 * @param [in] engine  <br>
 *        由 CreateByteRtcEngine{@link #CreateByteRtcEngine} 返回的实例。
 * @notes  <br>
 *        + 请确保一定是在所有业务场景的最后阶段才调用该方法。  <br>
 *        + 该方法在调用之后，会销毁所有 SDK 相关的内存，并且停止与媒体服务器的任何交互。  <br>
 *        + 在上一次 CreateByteRtcEngine{@link #CreateByteRtcEngine} 调用之后对 SDK 进行的任何设置，
 *          将在下一次有效执行 CreateByteRtcEngine{@link #CreateByteRtcEngine} 时生效。  <br>
 *        + 本方法为阻塞调用，会阻塞当前线程直到 SDK 彻底完成退出逻辑，因而需要注意不要在回调线程中
 *          直接调用本方法，也需要注意不要在回调方法中等待主线程的执行而同时在主线程调用本方法，从而
 *          造成死锁。
 */
BYTE_API void DestroyByteRtcEngine(bytertc::IRtcEngine* engine);

/**
 * @hidden
 * @region 引擎管理
 * @brief 销毁由 CreateGameRtcEngine{@link #CreateGameRtcEngine} 创建的游戏 RTCEngine 实例，并释放所有相关资源。
 * @param [in] engine  <br>
 *        由 CreateGameRtcEngine{@link #CreateGameRtcEngine} 返回的实例。
 * @notes  <br>
 *        + 请确保一定是在所有业务场景的最后阶段才调用该方法。  <br>
 *        + 该方法在调用之后，会销毁所有 SDK 相关的内存，并且停止与媒体服务器的任何交互。  <br>
 *        + 在上一次 CreateGameRtcEngine{@link #CreateGameRtcEngine} 调用之后对 SDK 进行的任何设置，
 *          将在下一次有效执行 CreateGameRtcEngine{@link #CreateGameRtcEngine} 时生效。  <br>
 *        + 本方法为阻塞调用，会阻塞当前线程直到 SDK 彻底完成退出逻辑，因而需要注意不要在回调线程中
 *          直接调用本方法，也需要注意不要在回调方法中等待主线程的执行而同时在主线程调用本方法，从而
 *          造成死锁。
 */
BYTE_API void DestroyGameRtcEngine(bytertc::IRtcEngine* engine);

/**
 * @type api
 * @region 性能回退
 * @brief 设置引擎是否开启性能采集功能，默认为开启。
 * @param enable  <br>
 *      + true：开启  <br>
 *      + false：不开启
 * @notes  <br>
 *        + 开启后，SDK内部会采集CPU、内存使用量。可能会对性能有影响。
 *        + 该接口会修改所有引擎实例的配置，是一个全局接口
 */
BYTE_API void EnablePerformanceCollect(bool enable);

/**
 * @type api
 * @region 错误码
 * @brief 获取错误码的描述
 * @param code 需要获取描述的错误码
 * @return 错误码的描述
 */
BYTE_API const char* GetErrorDescription(int code);

/**
 * @type api
 * @region 其他
 * @brief 本次通话质量打分评价
 * @param [in] data
 *        上报的数据，JSON格式，必须包含以下5个字段:
 *        grade: 打分 1～5  <br>
 *        type: 反馈问题集合可多选，参考 PROBLEM_FEEDBACK{@link #PROBLEM_FEEDBACK}  <br>
 *        problem_desc: 其他问题描述  <br>
 *        os_version: 系统版本  <br>
 *        network_type: 网络类型, WiFi, 2g, 3g, 4g, 5g, 台式机填pc  <br>
 * @return
 *        +  0: 成功  <br>
 *        + -1: 上报失败，可能原因JoinChannel失败  <br>
 *        + -2: 传入json解析失败  <br>
 *        + -3: 传入json字段缺失  <br>
 *        + -4: grade取值不合法
 */
BYTE_API int Feedback(const char* data);
}    // namespace bytertc
#endif // I_BYTE_RTC_ENGINE
