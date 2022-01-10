/*
 * Copyright (c) 2020 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngine Interface
 */

#pragma once

#ifndef BYTE_RTC_INTERFACE_H__
#define BYTE_RTC_INTERFACE_H__

#include <stddef.h>
#include <stdio.h>
#include <stdarg.h>
#include <memory>
#include "bytertc_defines.h"
#include "bytertc_engine_lite_interface.h"
#include "bytertc_engine_event_handler.h"
#include "bytertc_video_frame.h"
#include "bytertc_audio_frame.h"

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
     * @hidden
     * @deprecated
     * @type api
     * @region 房间管理
     * @brief 创建/加入房间：房间不存在时即创建房间；房间存在时即加入这个房间。  <br>
     *        同一房间内的用户间可以相互通话。  <br>
     *        进房后重复调用无效，用户必须调用 LeaveRoom{@link #LeaveRoom} 退出当前房间后，才能加入下一个房间。  <br>
     *        本地用户调用此方法加入房间成功后，会收到 OnJoinRoomResult{@link #OnJoinRoomResult} 回调通知，远端用户会收到 OnUserJoined{@link #OnUserJoined} 回调通知。  <br>
     * @param [in] token 动态密钥，用于对登录用户进行鉴权验证。  <br>
     *        进入房间需要携带 Token。测试时可使用控制台生成临时 Token，正式上线需要使用密钥 SDK 在你的服务端生成并下发 Token。  <br>
     * @param [in] room_id 加入的房间 ID。  <br>
     *        房间 ID 为长度在 128 字节以内的非空字符串，支持以下字符集范围:  <br>
     *            1. 26 个大写字母 A ~ Z 。  <br>
     *            2. 26 个小写字母 a ~ z 。  <br>
     *            3. 10 个数字 0 ~ 9 。  <br>
     *            4. 下划线 "_"，at 符 "@"，减号 "-"。  <br>
     * @param [in] user_info 用户信息，参看 UserInfo{@link #UserInfo}。  <br>
     * @param [in] profile_type 房间模式。  <br>
     *        你应该根据业务需要，选择合适的房间模式。  <br>
     *        你必须在进房前设置房间模式，并且进房后不可更改。  <br>
     *        房间模式参看 RoomProfileType{@link #RoomProfileType}。  <br>
     * @return  <br>
     *        +  0: 成功  <br>
     *        + -1: room_id 为空，失败  <br>
     *        + -2: user_info 为空，失败  <br>
     * @notes  <br>
     *       + 使用不同 App ID 的 App 是不能互通的。  <br>
     *       + 请务必保证生成 Token 使用的 App ID 和创建引擎时使用的 App ID 相同，否则会导致加入房间失败。  <br>
     *       + 用户加入房间成功后，在本地网络状况不佳的情况下，SDK 可能会与服务器失去连接，此时 SDK 将会自动重连。重连成功后，本地会收到 OnJoinRoomResult{@link #OnJoinRoomResult} 回调通知。  <br>
     *       + 同一个 App ID 的同一个房间内，每个用户的用户 ID 必须是唯一的。如果两个用户的用户 ID 相同，则后进房的用户会将先进房的用户踢出房间，并且先进房的用户会收到 OnError{@link #IRtcEngineLiteEventHandler#OnError} 回调通知，错误类型详见 ErrorCode{@link #ErrorCode}。  <br>
     */
    virtual int JoinRoom(
            const char* token, const char* room_id, const UserInfo& user_info, RoomProfileType profile_type) = 0;
    /**
     * @type api
     * @region 房间管理
     * @brief 创建/加入房间：房间不存在时即创建房间；房间存在时即加入这个房间。  <br>
     *        同一房间内的用户间可以相互通话。  <br>
     *        进房后重复调用无效，用户必须调用 LeaveRoom{@link #IRtcRoom#LeaveRoom} 退出当前房间后，才能加入下一个房间。  <br>
     *        本地用户调用此方法加入房间成功后，会收到 OnJoinRoomResult{@link #IRTCRoomEventHandler#OnJoinRoomResult} 回调通知。  <br>
     *        本地用户调用 SetUserVisibility{@link #IRtcRoom#SetUserVisibility} 将自身设为可见后加入房间，远端用户会收到 OnUserJoined{@link #IRTCRoomEventHandler#OnUserJoined}。
     * @param [in] token 动态密钥，用于对登录用户进行鉴权验证。  <br>
     *        进入房间需要携带 Token。测试时可使用控制台生成临时 Token，正式上线需要使用密钥 SDK 在您的服务端生成并下发 Token。  <br>
     *        使用不同 App ID 的 App 是不能互通的。  <br>
     *        请务必保证生成 Token 使用的 App ID 和创建引擎时使用的 App ID 相同，否则会导致加入房间失败。  <br>
     * @param [in] room_id 加入的房间 ID。  <br>
     *        房间 ID 为长度在 128 字节以内的非空字符串，支持以下字符集范围:  <br>
     *            1. 26 个大写字母 A ~ Z 。  <br>
     *            2. 26 个小写字母 a ~ z 。  <br>
     *            3. 10 个数字 0 ~ 9 。  <br>
     *            4. 下划线 "_"，at 符 "@"，减号 "-"。  <br>
     * @param [in] user_info 用户信息，参看 UserInfo{@link #UserInfo}。  <br>
     * @param [in] room_config 房间参数配置，设置房间模式以及是否自动发布或订阅流。具体配置模式参看 RTCRoomConfig{@link #RTCRoomConfig}。  <br>
     * @return  <br>
     *        +  0: 成功  <br>
     *        + -1：room_id / user_info.uid 包含了无效的参数  <br>
     *        + -2：已经在房间内。接口调用成功后，只要收到返回值为 0 ，且未调用 LeaveRoom:{@link #IRtcRoom#LeaveRoom} 成功，则再次调用进房接口时，无论填写的房间 ID 和用户 ID 是否重复，均触发此返回值。  <br>  <br>
     * @notes  <br>
     *       + 同一个 App ID 的同一个房间内，每个用户的用户 ID 必须是唯一的。如果两个用户的用户 ID 相同，则后进房的用户会将先进房的用户踢出房间，并且先进房的用户会收到 OnError{@link #IRtcEngineLiteEventHandler#OnError} 回调通知，错误类型详见 ErrorCode{@link #ErrorCode} 中的 kErrorCodeDuplicateLogin。  <br>
     *       + 本地用户调用此方法加入房间成功后，会收到 OnJoinRoomResult{@link #IRTCRoomEventHandler#OnJoinRoomResult} 回调通知。  <br>
     *       + 本地用户调用 SetUserVisibility{@link #IRtcRoom#SetUserVisibility} 将自身设为可见后加入房间，远端用户会收到 OnUserJoined{@link #IRTCRoomEventHandler#OnUserJoined}。  <br>
     *       + 用户加入房间成功后，在本地网络状况不佳的情况下，SDK 可能会与服务器失去连接，此时 SDK 将会自动重连。重连成功后，本地会收到 OnJoinRoomResult{@link #IRTCRoomEventHandler#OnJoinRoomResult} 回调通知。  <br>     
     */
    virtual int JoinRoom(const char* token, const char* room_id, const UserInfo& user_info, const RTCRoomConfig& room_config) = 0;
/**
 * @hidden
 */
private:
    /**
     * @hidden
     */
    void JoinRoom(const char* token, const UserInfo& user_info, RoomProfileType profile_type) override{};
    /**
     * @hidden
     */
    int JoinRoom(const char* token, const UserInfo& user_info, const MultiRoomConfig& config) override{ return 0;};
    /**
     * @hidden
     */
    void SetRtcRoomEventHandler(IRTCRoomEventHandler* room_event_handler) override {};
};

/**
 * @type api
 * @region 引擎管理
 * @brief 创建 RTCEngine 实例。  <br>
 *        如果当前线程中未创建引擎实例，那么你必须先使用此方法，以使用 RTC 提供的各种音视频能力。  <br>
 *        如果当前线程中已创建了引擎实例，再次调用此方法时，会创建另一个独立的引擎实例。
 * @param [in] app_id  <br>
 *        每个应用的唯一标识符。只有使用相同的 app_id 生成的实例，才能够进行音视频通信。
 * @param [in] event_handler  <br>
 *        SDK 回调给应用层的 Callback 对象，详见 IRtcEngineEventHandler{@link #IRtcEngineEventHandler} 。
 * @param [in] parameters 用以覆盖默认参数的本引擎实例参数。JSON 字符串格式。
 * @return 可用的 IRtcEngine{@link #IRtcEngine} 实例。
 * @notes  <br>
 *        + 如果你在同一个线程中创建了多个引擎实例，这些实例必须分别调用 DestroyRtcEngine{@link #DestroyRtcEngine} 销毁。
 *        + 在 Linux 平台上创建引擎实例的数量取决于系统的硬件性能。
 */
BYTERTC_API bytertc::IRtcEngine* CreateRtcEngine(const char* app_id,
        bytertc::IRtcEngineEventHandler* event_handler, const char* parameters);

/**
 * @hidden
 * @region 引擎管理
 * @brief 创建游戏 RTCEngine 实例。
 * @param [in] app_id  <br>
 *        每个应用的唯一标识符。不同的 AppId 生成的实例进行音视频通话完全独立，无法互通。
 * @param [in] event_handler  <br>
 *        SDK 回调给应用层的 Callback 对象，详见 IRTCEngineEventHandler{@link #IRtcEngineEventHandler} 。
 * @param [in] parameters 保留参数
 * @return 可用的 IRtcEngine{@link #IRtcEngine} 实例。
 * @notes  <br>
 *        + 该方法创建并初始化 IRtcEngine{@link #IRtcEngine} 实例。使用 IRtcEngine，必须先调用该接口进行初始化。  <br>
 *        + IRtcEngine{@link #IRtcEngine} 实例通过指定的 IRTCEngineEventHandler{@link #IRtcEngineEventHandler}
 *          通知应用程序引擎运行时的事件。IRTCEngineEventHandler{@link #IRtcEngineEventHandler} 中定义的所有方法都是可选实现的。
 */
BYTERTC_API bytertc::IRtcEngine* CreateGameRtcEngine(const char* app_id,
        bytertc::IRtcEngineEventHandler* event_handler, const char* parameters);

/**
 * @hidden
 * @region 引擎管理
 * @brief 创建 RTCEngine 实例。
 * @param [in] app_id  <br>
 *        每个应用的唯一标识符。不同的 AppId 生成的实例进行音视频通话完全独立，无法互通。
 * @param [in] event_handler  <br>
 *        SDK 回调给应用层的 Callback 对象，详见 IRTCEngineEventHandler{@link #IRtcEngineEventHandler} 。
 * @param [in] parameters 保留参数
 * @return 可用的 IRtcEngine{@link #IRtcEngine} 实例。
 * @notes  <br>
 *        + 该方法创建并初始化 IRtcEngine{@link #IRtcEngine} 实例。使用 IRtcEngine，必须先调用该接口进行初始化。  <br>
 *        + IRtcEngine{@link #IRtcEngine} 实例通过指定的 IRTCEngineEventHandler{@link #IRtcEngineEventHandler}
 *          通知应用程序引擎运行时的事件。IRTCEngineEventHandler{@link #IRtcEngineEventHandler} 中定义的所有方法都是可选实现的。
 */
BYTERTC_API bytertc::IRtcEngine* CreateRtcEngineWithPtr(
        const char* app_id, std::unique_ptr<bytertc::IRtcEngineEventHandler> event_handler,
        const char* parameters);

/**
 * @hidden
 * @region 引擎管理
 * @brief 创建游戏 RTCEngine 实例。
 * @param [in] app_id  <br>
 *        每个应用的唯一标识符。不同的 AppId 生成的实例进行音视频通话完全独立，无法互通。
 * @param [in] event_handler  <br>
 *        SDK 回调给应用层的 Callback 对象，详见 IRTCEngineEventHandler{@link #IRtcEngineEventHandler} 。
 * @param [in] parameters 保留参数
 * @return 可用的 IRtcEngine{@link #IRtcEngine} 实例。
 * @notes  <br>
 *        + 该方法创建并初始化 IRtcEngine{@link #IRtcEngine} 实例。使用 IRtcEngine，必须先调用该接口进行初始化。  <br>
 *        + IRtcEngine{@link #IRtcEngine} 实例通过指定的 IRTCEngineEventHandler{@link #IRtcEngineEventHandler}
 *          通知应用程序引擎运行时的事件。IRTCEngineEventHandler{@link #IRtcEngineEventHandler} 中定义的所有方法都是可选实现的。
 */
BYTERTC_API bytertc::IRtcEngine* CreateGameRtcEngineWithPtr(
        const char* app_id, std::unique_ptr<bytertc::IRtcEngineEventHandler> event_handler,
        const char* parameters);

/**
 * @type api
 * @region 引擎管理
 * @brief 销毁由 CreateRtcEngine{@link #CreateRtcEngine} 创建的 RTCEngine 实例，并释放所有相关资源。
 * @param [in] engine  <br>
 *        CreateRtcEngine{@link #CreateRtcEngine} 时，返回的实例。
 * @notes  <br>
 *        + 请确保和需要销毁的 IRtcEngine{@link #IRtcEngine} 实例相关的业务场景全部结束后，才调用此方法。  <br>
 *        + 该方法在调用之后，会销毁所有和此 IRtcEngine{@link #IRtcEngine} 实例相关的内存，并且停止与媒体服务器的任何交互。  <br>
 *        + 你不可以在回调线程中直接调用本方法；也不可以在回调方法中等待主线程的执行而同时在主线程调用本方法，否则会造成死锁。原因是本方法为阻塞调用，会阻塞当前线程直到 SDK 彻底完成退出逻辑。
 */
BYTERTC_API void DestroyRtcEngine(bytertc::IRtcEngine* engine);

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
BYTERTC_API void DestroyGameRtcEngine(bytertc::IRtcEngine* engine);

/**
 * @type api
 * @region 错误码
 * @brief 获取错误码的描述
 * @param [in] code 需要获取描述的错误码
 * @return 错误码的描述
 * @notes  该接口是通用功能，调用时不需要依赖引擎对象。
 */
BYTERTC_API const char* GetErrorDescription(int code);

/**
 * @type api
 * @region 引擎管理
 * @brief 获取当前 SDK 版本信息。
 * @return 当前 SDK 版本信息。
 */
BYTERTC_API const char* GetSDKVersion();

}    // namespace bytertc

#endif  // BYTE_RTC_INTERFACE_H__
