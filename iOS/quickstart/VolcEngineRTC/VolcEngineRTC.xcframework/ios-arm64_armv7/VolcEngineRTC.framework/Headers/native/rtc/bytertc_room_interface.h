/*
 * Copyright (c) 2020 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngine Room Interface
 */

#pragma once

#ifndef BYTE_RTC_ROOM_INTERFACE_H__
#define BYTE_RTC_ROOM_INTERFACE_H__

#include "bytertc_video_effect_interface.h"  // NOLINT
#include "bytertc_defines.h"
#include "bytertc_room_event_handler_interface.h"
#include "bytertc_transcoder_interface.h"

namespace bytertc {

/**
 * @type api
 * @brief 房间接口
 */
class IRtcRoom {
public:
    /**
     * @hidden
     * @brief 析构函数
     */
    virtual ~IRtcRoom() {
    }

    /**
     * @hidden
     * @type api
     * @region 多房间
     * @brief 销毁房间，该接口实现上会先执行退房操作，然后释放房间处理回调指针
     */
    virtual void Destroy() = 0;

    /**
     * @hidden
     * @deprecated from 327.1, use SetUserVisibility instead
     * @type api
     * @region 多房间
     * @brief 设置用户角色。默认角色为主播。  <br>
     *        通过设置不同的用户角色，可以控制用户在房间内的行为：<br>
     *        + 能否发布音视频流；<br>
     *        + 用户自身是否在房间中隐身。<br>
     * @param [in] role 用户角色，参看 UserRoleType{@link #UserRoleType}。
     * @notes  <br>
     *       + 在加入房间前后，用户均可调用此方法设置用户角色。 <br>
     *       + 在房间内，调用此方法成功切换角色后，房间内其他用户会收到相应的回调通知：<br>
     *            - 从静默观众切换至主播时，房间内其他用户会收到 OnUserJoined{@link #OnUserJoined}；  <br>
     *            - 从主播切换至静默观众时，房间内其他用户会收到 OnUserLeave{@link #OnUserLeave} 。
     */
    virtual void SetUserRole(UserRoleType role) = 0;



    /**
     * @type api
     * @region 多房间
     * @brief 设置用户可见性。默认为可见。  <br>
     *        通过对用户可见性进行设置，可以控制用户在房间内的行为：<br>
     *        + 能否发布音视频流；  <br>
     *        + 用户自身是否在房间中隐身。
     * @param [in] enable 设置用户是否对房间内其他用户可见：  <br>
     *        + true: 可以被房间中的其他用户感知，且可以在房间内发布和订阅音视频流；  <br>
     *        + false: 无法被房间中的其他用户感知，且只能在房间内订阅音视频流。
     * @notes  <br>
     *        + 该方法在加入房间前后均可调用。 <br>
     *        + 在房间内调用此方法，房间内其他用户会收到相应的回调通知：<br>
     *            - 从 false 切换至 true 时，房间内其他用户会收到 OnUserJoined{@link #IRTCRoomEventHandler#OnUserJoined} 回调通知；  <br>
     *            - 从 true 切换至 false 时，房间内其他用户会收到 OnUserLeave{@link #IRTCRoomEventHandler#OnUserLeave} 回调通知。 <br>
     *        + 若调用该方法将可见性设为 false，此时尝试发布流会收到 OnWarning{@link #IRtcEngineLiteEventHandler#OnWarning} 警告，具体原因参看 WarningCode{@link #WarningCode} 中的 kWarningCodePublishStreamForbiden 警告码。
     */
    virtual void SetUserVisibility(bool enable) = 0;



    /**
     * @hidden
     * @type api
     * @region 多房间
     * @brief 设置 IRTCRoom{@link #IRtcRoom} 对象的事件句柄。
     *        通过设置事件句柄可以监听此 IRTCRoom{@link #IRtcRoom} 对象对应的房间的回调事件。
     * @param [in] room_event_handler
     *        回调处理器，详见 IRTCRoomEventHandler{@link #IRTCRoomEventHandler}
     */
    virtual void SetRtcRoomEventHandler(IRTCRoomEventHandler* room_event_handler) = 0;

    /**
     * @hidden
     * @deprecated from 326.1, use function joinRoom with MultiRoomConfig parameter instead
     * @type api
     * @region 多房间
     * @brief 加入房间。
     *        用户调用此方法加入此 IRTCRoom{@link #IRtcRoom}
     * 对应的房间。在一个房间内的用户可以相互通话。调用加入房间前，需要调用 CreateRtcRoom{@link #CreateRtcRoom} 方法
     *        创建房间对应的 IRTCRoom{@link #IRtcRoom} 对象。
     * @param [in] token
     *        动态密钥，用于对登录用户进行鉴权验证。进入房间需要携带 Token。可以在控制台生成临时 Token
     * 进行测试，正式上线需要使用密钥 SDK 在你的服务端生成并下发 Token 。
     * @param [in] user_info
     *        用户信息，包含用户id，以及用户需要透传的额外信息
     * @param [in] profileType 房间模式，详见 RoomProfileType{@link #RoomProfileType} 枚举类型。  <br>
     * @return
     *      0: 成功
     *      other: 失败
     * @notes
     *        1.使用不同 App ID 的 App 是不能互通的。
     *        2.调用该方法成功加入房间后，本端会收到 OnJoinRoomResult{@link #OnJoinRoomResult} 回调通知，errorcode 为 0
     * ，JoinRoomType{@link #JoinRoomType} 为 KJoinRoomFirst。 3.本端网络状况不佳的情况下，SDK
     * 可能会与服务器失去连接，此时 SDK 将会自动重连，重连成功后收到 OnJoinRoomResult{@link #OnJoinRoomResult}
     * 回调通知， errorcode 为 0 ，JoinRoomType{@link #JoinRoomType} 为 kJoinRoomTypeReconnected 4.同一个 App ID
     * 的同一个房间内，每个用户的用户 ID 必须是唯一的。如果两个用户的用户 ID 相同，则后加入房间的用户会将先加入
     *          房间的用户踢出房间，并且先加入房间的用户会收到 OnRoomError{@link #OnRoomError}回调通知，
     *          错误类型为重复登录 kErrorCodeDuplicateLogin{@link #kErrorCodeDuplicateLogin} 。
     *        5.请务必保证生成 Token 使用的App ID 和创建引擎时使用的 App ID 相同，否则会导致加入房间失败。
     *        6.该方法仅能加入此 IRTCRoom{@link #IRtcRoom}
     *        对应的房间，如果需要加入其它房间需要创建对应房间的 IRTCRoom{@link #IRtcRoom} 对象。
     */
    virtual void JoinRoom(const char* token, const UserInfo& user_info, RoomProfileType profile_type) = 0;

    /**
     * @type api
     * @region 多房间
     * @brief 创建/加入房间：房间不存在时即创建房间；房间存在时，未加入房间的用户可加入这个房间。  <br>
     *        同一房间内的用户间可以相互通话。  <br>
     *        进房后重复调用无效，用户必须调用 LeaveRoom{@link #IRtcRoom#LeaveRoom} 退出当前房间后，才能加入下一个房间。  <br>
     * @param [in] token 动态密钥，用于对登录用户进行鉴权验证。  <br>
     *        进入房间需要携带 Token。测试时可使用控制台生成临时 Token，正式上线需要使用密钥 SDK 在您的服务端生成并下发 Token。  <br>
     *       + 使用不同 App ID 的 App 是不能互通的。  <br>
     *       + 请务必保证生成 Token 使用的 App ID 和创建引擎时使用的 App ID 相同，否则会导致加入房间失败。  <br>
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
     *        + -1：room_id / user_info.uid 包含了无效的参数。  <br>
     *        + -2：已经在房间内。接口调用成功后，只要收到返回值为 0 ，且未调用 LeaveRoom:{@link #IRtcRoom#LeaveRoom} 成功，则再次调用进房接口时，无论填写的房间 ID 和用户 ID 是否重复，均触发此返回值。  <br>
     * @notes  <br>
     *       + 同一个 App ID 的同一个房间内，每个用户的用户 ID 必须是唯一的。如果两个用户的用户 ID 相同，则后进房的用户会将先进房的用户踢出房间，并且先进房的用户会收到 OnError{@link #IRtcEngineLiteEventHandler#OnError} 回调通知，错误类型详见 ErrorCode{@link #ErrorCode} 中的 kErrorCodeDuplicateLogin。  <br>
     *       + 本地用户调用此方法加入房间成功后，会收到 OnJoinRoomResult{@link #IRTCRoomEventHandler#OnJoinRoomResult} 回调通知。  <br>
     *       + 本地用户调用 SetUserVisibility{@link #IRtcRoom#SetUserVisibility} 将自身设为可见后加入房间，远端用户会收到 OnUserJoined{@link #IRTCRoomEventHandler#OnUserJoined}。  <br>
     *       + 用户加入房间成功后，在本地网络状况不佳的情况下，SDK 可能会与服务器失去连接，此时 SDK 将会自动重连。重连成功后，本地会收到 OnJoinRoomResult{@link #IRTCRoomEventHandler#OnJoinRoomResult} 回调通知。  <br>
     */
    virtual int JoinRoom(const char* token, const UserInfo& user_info, const MultiRoomConfig& config) = 0;

    /**
     * @type api
     * @region 多房间
     * @brief 离开房间。  <br>
     *        用户调用此方法离开房间，结束通话过程，释放所有通话相关的资源。  <br>
     *        加入房间后，必须调用此方法结束通话，否则无法开始下一次通话。无论当前是否在房间内，都可以调用此方法。重复调用此方法没有负面影响。  <br>
     * @notes  <br>
     *       + 此方法是异步操作，调用返回时并没有真正退出房间。真正退出房间后，本地会收到 OnLeaveRoom{@link #IRTCRoomEventHandler#OnLeaveRoom} 回调通知。  <br>
     *       + 可见的用户离开房间后，房间内其他用户会收到 OnUserLeave{@link #IRTCRoomEventHandler#OnUserLeave} 回调通知。  <br>
     *       + 如果调用此方法后立即销毁引擎，SDK 将无法触发 OnLeaveRoom{@link #IRTCRoomEventHandler#OnLeaveRoom} 回调。  <br>
     *       + 调用 JoinRoom{@link #IRtcRoom#JoinRoom} 方法加入房间后，必须调用此方法离开房间，否则无法进入下一个房间。无论当前是否在房间内，都可以调用此方法。重复调用此方法没有负面影响。  <br>
     */
    virtual void LeaveRoom() = 0;

    /**
     * @type api
     * @region 多房间
     * @brief 更新 Token。  <br>
     *        Token 有一定的有效期，当 Token 过期时，用户需调用此方法更新房间的 Token 信息。  <br>
     *        用户调用 JoinRoom{@link #IRtcRoom#JoinRoom} 方法加入房间时，如果使用了过期的 Token 将导致加入房间失败，并会收到 OnJoinRoomResult{@link #IRTCRoomEventHandler#OnJoinRoomResult} 回调通知，错误码为 ErrorCode{@link #ErrorCode} 中的 kErrorCodeInvalidToken 。此时需要重新获取 Token，并调用此方法更新 Token。  <br>
     * @param [in] token 更新的动态密钥。  <br>
     * @notes  <br>
     *       + 如果用户因 Token 过期导致加入房间失败，则调用此方法更新 Token 后，SDK 会自动重新加入房间，而不需要用户自己调用 JoinRoom{@link #IRtcRoom#JoinRoom} 方法。  <br>
     *       + Token 过期时，如果已经加入房间成功，则不会受到影响。Token 过期的错误会在下一次使用过期 Token 加入房间时，或因本地网络状况不佳导致断网重新连入房间时通知给用户。  <br>
     */
    virtual void UpdateToken(const char* token) = 0;

    /**
     * @type api
     * @region 多房间
     * @brief 给房间内指定的用户发送文本消息（P2P）
     * @param [in] uid  <br>
     *        消息接收用户的 ID
     * @param [in] message  <br>
     *        发送的文本消息内容。  <br>
     *        消息不超过 62KB。
     * @return 这次发送消息的编号，从 1 开始递增。
     * @notes  <br>
     *       + 在发送房间内文本消息前，必须先调用 JoinRoom{@link #IRtcRoom#JoinRoom} 加入房间。  <br>
     *       + 调用该函数后会收到一次 OnUserMessageSendResult{@link #IRTCRoomEventHandler#OnUserMessageSendResult} 回调，通知消息发送方发送成功或失败；  <br>
     *       + 若文本消息发送成功，则 uid 所指定的用户会收到 OnUserMessageReceived{@link #IRTCRoomEventHandler#OnUserMessageReceived} 回调。
     */
    virtual int64_t SendUserMessage(const char* uid, const char* message) = 0;

    /**
     * @type api
     * @region 多房间
     * @brief 给房间内指定的用户发送二进制消息（P2P）
     * @param [in] uid  <br>
     *        消息接收用户的 ID
     * @param [in] length   <br>
     *        二进制字符串的长度。
     * @param [in] message   <br>
     *        二进制消息的内容。
     *        消息不超过 46KB。
     * @return 这次发送消息的编号，从 1 开始递增。
     * @notes  <br>
     *       + 在发送房间内二进制消息前，必须先调用 JoinRoom{@link #IRtcRoom#JoinRoom} 加入房间。  <br>
     *       + 调用该函数后会收到一次 OnUserMessageSendResult{@link #IRTCRoomEventHandler#OnUserMessageSendResult} 回调，通知消息发送方发送成功或失败；  <br>
     *       + 若二进制消息发送成功，则 uid 所指定的用户会收到 OnUserBinaryMessageReceived{@link #IRTCRoomEventHandler#OnUserBinaryMessageReceived} 回调。
     */
    virtual int64_t SendUserBinaryMessage(const char* uid, int length, const uint8_t* message) = 0;

    /**
     * @type api
     * @region 多房间
     * @brief 给房间内的所有其他用户发送广播消息。
     * @param [in] message  <br>
     *        用户发送的广播消息  <br>
     *        消息不超过 62KB。
     * @notes  <br>
     *       + 在发送房间内二进制消息前，必须先调用 JoinRoom{@link #IRtcRoom#JoinRoom} 加入房间。  <br>
     *       + 调用该函数后，会收到一次 OnRoomMessageSendResult{@link #IRTCRoomEventHandler#OnRoomMessageSendResult} 回调。  <br>
     *       + 同一房间内的其他用户会收到 OnRoomMessageReceived{@link #IRTCRoomEventHandler#OnRoomMessageReceived} 回调。
     */
    virtual int64_t SendRoomMessage(const char* message) = 0;
    /**
     * @type api
     * @region 多房间
     * @brief 给房间内的所有其他用户发送广播消息。
     * @param [in] size  <br>
     *        发送的二进制消息长度
     * @param [in] message  <br>
     *        用户发送的二进制广播消息  <br>
     *        消息不超过 46KB。
     * @notes  <br>
     *       + 在发送房间内二进制消息前，必须先调用 JoinRoom{@link #IRtcRoom#JoinRoom} 加入房间。  <br>
     *       + 调用该函数后，会收到一次 OnRoomMessageSendResult{@link #IRTCRoomEventHandler#OnRoomMessageSendResult} 回调。  <br>
     *       + 同一房间内的其他用户会收到 OnRoomBinaryMessageReceived{@link #IRTCRoomEventHandler#OnRoomBinaryMessageReceived} 回调。
     */
    virtual int64_t SendRoomBinaryMessage(int size, const uint8_t* message) = 0;
    /**
     * @type api
     * @region 多房间
     * @brief 将本端音视频流发布到此房间。
     * @notes  <br>
     *        1.多房间模式下，默认音视频流不自动发布。你必须调用此接口，进行手动发布。<br>
     *        2.调用 SetUserVisibility{@link #IRtcRoom#SetUserVisibility} 方法将自身设置为不可见后无法调用该方法，需将自身切换至可见后方可调用该方法发布音视频流。 <br>
     *        3.用户在房间内，同一时间仅能发布一路音视频流。<br>
     *        4.房间内用户调用此方法成功发布音视频流后，房间中的其他用户将会收到 OnStreamAdd{@link #IRTCRoomEventHandler#OnStreamAdd} 回调通知。
     */
    virtual void Publish() = 0;

    /**
     * @type api
     * @region 多房间
     * @brief 停止将本端音视频流发布到此房间。
     * @notes  <br>
     *        1.在多房间模式下，调用 Publish{@link #IRtcRoom#Publish} 手动发布音视频流后，调用此接口停止发布。<br>
     *        2.房间内用户调用此方法停止发布音视频流后，房间中的其他用户将会收到 OnStreamRemove{@link #IRTCRoomEventHandler#OnStreamRemove} 回调通知。
     */
    virtual void Unpublish() = 0;


    /**
     * @hidden
     * @deprecated from 327.1, use PublishScreen without params instead
     * @type api
     * @region 多房间
     * @brief 发布本地屏幕共享流到房间。
     * @param [in] paramters
     *        屏幕共享流编码参数，详见 ScreenParameters{@link #ScreenParameters}
     * @notes  <br>
     *       + 此方法适用于调用 SetUserVisibility{@link #IRtcRoom#SetUserVisibility} 方法将自身设为可见的用户。  <br>
     *       + 调用此方法发布本端屏幕共享流后，用户还需要通过设置定时任务周期性调用 PushScreenFrame{@link
     * #IRtcEngineLite#PushScreenFrame} 方法，将需要发送的屏幕数据推送给 SDK。  <br>
     *       + 远端会收到 OnFirstRemoteVideoFrameRendered{@link #IRTCRoomEventHandler#OnFirstRemoteVideoFrameRendered}
     * 、OnStreamAdd{@link#IRTCRoomEventHandler#OnStreamAdd} 事件。  <br>
     *       + 该函数和 StartScreenVideoCapture{@link#IRtcEngineLite#StartScreenVideoCapture} 函数是互斥调用的，可在调用
     * UnpublishScreen{@link#IUnpublishScreen} 函数后调用上述函数。  <br>
     *       + 在收到 OnFirstRemoteVideoFrameRendered{@link#IRTCRoomEventHandler#OnFirstRemoteVideoFrameRendered}
     * 事件后通过调用 SetRemoteVideoCanvas{@link #SetRemoteVideoCanvas} 或 SetRemoteVideoSink{@link #SetRemoteVideoSink}
     * 函数来设置远端屏幕共享视图。  <br>
     *       + 本地可调用 SetLocalVideoCanvas{@link #IRtcEngineLite#SetLocalVideoCanvas} 或
     * SetLocalVideoSink{@link #SetLocalVideoSink} 函数设置本地屏幕共享视图。  <br>
     *       + 也可通过注册 RegisterVideoFrameObserver{@link#RegisterVideoFrameObserver} 视频回调对象，监听
     * OnLocalScreenFrame{@link #IVideoFrameObserver#OnLocalScreenFrame}本地屏幕视频回调事件和 OnRemoteScreenFrame{@link
     * #IVideoFrameObserver#OnRemoteScreenFrame}远端屏幕共享视频回调事件来获取原始数据。  <br>
     *       + 该方法在 JoinRoom{@link #JoinRoom} 后才能调用。  <br>
     */
    virtual void PublishScreen(const ScreenParameters& paramters) = 0;

    /**
     * @type api
     * @region 屏幕共享
     * @brief 发布本地屏幕共享流到房间。
     * @notes  <br>
     *       + 你必须先加入房间，才能调用此方法。<br>
     *       + 直播、游戏、云游戏房间模式下，仅可见的用户可以调用此方法。你可以调用 SetUserVisibility{@link #IRtcRoom#SetUserVisibility} 方法设置用户在房间中的可见性。  <br>
     *       + 此方法只影响屏幕共享视频流的发布状态，并不影响屏幕视频流的采集情况。你可以通过两种方式进行采集：<br>
     *              - RTC SDK 内部采集：参看 StartScreenVideoCapture{@link#IRtcEngineLite#StartScreenVideoCapture} 和 StartScreenAudioCapture{@link#IRtcEngineLite#StartScreenAudioCapture} <br>
     *              - RTC SDK 外部采集：你可以自行采集屏幕音视频流，并周期性调用 PushScreenFrame{@link#IRtcEngineLite#PushScreenFrame} 和 PushScreenAudioFrame{@link#IRtcEngineLite#PushScreenAudioFrame} 将采集得到的音视频帧推送到 RTC SDK 用于编码传输。<br>
     *       + 发布成功后，远端会收到 OnStreamAdd{@link #IRTCRoomEventHandler#OnStreamAdd} 回调；如果调用 RegisterVideoFrameObserver{@link#RegisterVideoFrameObserver} 注册了视频帧回调观察者，那么也会收到 OnRemoteScreenFrame{@link #IVideoFrameObserver#OnRemoteScreenFrame} 回调。
     *       + 调用 UnpublishScreen{@link #IRtcRoom#UnpublishScreen} 取消发布。
     */
    virtual void PublishScreen() = 0;

    /**
     * @type api
     * @region 屏幕共享
     * @brief 停止发布本地屏幕共享流到房间。
     * @notes 远端会收到 OnStreamRemove{@link #IRTCRoomEventHandler#OnStreamRemove} 事件。
     * @notes  <br>
     *       + 此方法只影响屏幕共享视频流的发布状态，并不影响屏幕视频流的采集情况。<br>
     *       + 调用 PublishScreen{@link #IRtcRoom#PublishScreen} 启动发布。
     */
    virtual void UnpublishScreen() = 0;

    /**
     * @hidden
     * @deprecated from 326.1, use SubscribeUserStream instead
     * @type api
     * @region 多房间
     * @brief 订阅指定的房间内远端音视频流。  <br>
     *        关闭自动订阅功能，使用手动订阅模式时用户调用此方法按需订阅房间中的音视频流。  <br>
     *        此方法仅在关闭自动订阅功能时生效。用户需在加入房间前调用 EnableAutoSubscribe{@link #EnableAutoSubscribe}
     * 方法关闭自动订阅功能以使用手动订阅模式。  <br> 用户在自动订阅功能开启时调用此方法，SDK 不会订阅音视频流，并通过
     * OnRoomWarning{@link #OnRoomWarning} 回调通知用户订阅失败，回调警告码为
     * kWarningCodeSubscribeStreamForbiden{@link #kWarningCodeSubscribeStreamForbiden} 。  <br> 订阅流失败时，SDK
     * 会按失败原因回调 OnRoomError{@link #OnRoomError} 通知用户，具体错误可参考错误码 ErrorCode{@link
     * #ErrorCode} 描述。  <br>
     * @param [in] user_id 指定订阅的远端用户的用户ID 。  <br>
     * @param [in] info 选择订阅配置，详见数据结构 SubscribeConfig{@link #SubscribeConfig} 。  <br>
     * @notes  <br>
     *       + 此方法仅支持订阅当前房间中的远端音视频流。如果指定的流在当前房间内不曾存在，则 SDK 不会订阅。  <br>
     *       + 用户调用 JoinRoom{@link #JoinRoom} 方法加入房间后：1.当房间内有新的音视频流发布时，本地会收到
     * OnStreamAdd{@link #OnStreamAdd} 回调通知；2.当房间内音视频流停止发布时，本地会收到 OnStreamRemove{@link
     * #OnStreamRemove}
     * 回调通知。通过这两个回调用户可以获得当前房间中的音视频流信息，并在需要时调用此方法订阅该音视频流。  <br>
     */
    virtual void SubscribeStream(const char* user_id, const SubscribeConfig& info) = 0;

    /**
     * @type api
     * @region 多房间
     * @brief 订阅房间内指定的远端音视频流。  <br>
     *        无论是自动订阅还是手动订阅模式，你都可以调用此方法按需订阅房间中的音视频流。  <br>
     *        该方法也可用于更新已经订阅的流的属性、媒体类型等配置。 <br>
     * @param [in] user_id 指定订阅的远端发布音视频流的用户 ID。
     * @param [in] stream_type 流属性，用于指定订阅主流/屏幕流，参看 StreamIndex{@link #StreamIndex}。
     * @param [in] media_type 媒体类型，用于指定订阅音/视频，参看 SubscribeMediaType{@link #SubscribeMediaType}。
     * @param [in] video_config 视频订阅配置，参看 SubscribeVideoConfig{@link #SubscribeVideoConfig}。
     * @notes  <br>
     *        + 你可以通过 OnStreamAdd{@link #IRTCRoomEventHandler#OnStreamAdd} 和 OnStreamRemove{@link #IRTCRoomEventHandler#OnStreamRemove} 两个回调获取当前房间你的音视频流信息，并调用本方法按需订阅流或修改订阅配置。  <br>
     *        + 若订阅失败，你会收到 OnRoomError{@link #IRTCRoomEventHandler#OnRoomError} 回调通知，具体失败原因参看 ErrorCode{@link #ErrorCode}。
     *        + 若调用 PauseAllSubscribedStream{@link #IRtcRoom#PauseAllSubscribedStream} 暂停接收远端音视频流，此时仍可使用该方法对暂停接收的流进行设置，你会在调用 ResumeAllSubscribedStream{@link #IRtcRoom#ResumeAllSubscribedStream} 恢复接收流后收到修改设置后的流。  <br>
     */
    virtual void SubscribeUserStream(const char* user_id, StreamIndex stream_type, SubscribeMediaType media_type, const SubscribeVideoConfig& video_config) = 0;

    /**
     * @type api
     * @region 多房间
     * @brief 停止订阅指定的房间内远端音视频流。  <br>
     *        关闭自动订阅功能，使用手动订阅模式时用户调用此方法停止订阅已订阅的音视频流。  <br>
     *        此方法仅在关闭自动订阅功能时生效。用户需在加入房间时设置 config 关闭自动订阅功能以使用手动订阅模式。  <br>
     * @param [in] user_id 指定停止订阅的远端音视频流的用户的ID。  <br>
     * @param [in] is_screen 指定停止的流是不是屏幕流。  <br>
     * @notes  <br>
     *       + 不管是否订阅了指定的远端音视频流，都可以调用此方法停止订阅。停止订阅的 stream_id 无效或未订阅时，SDK不会做任何处理，没有负面影响。  <br>
     */
    virtual void Unsubscribe(const char* user_id, bool is_screen) = 0;

    /**
     * @hidden
     */
    virtual void EnableSubscribeLocalStream(bool enable) = 0;

    /**
     * @deprecated from 323.1, use OnUserStartAudioCapture instead
     * @type api
     * @region 多房间
     * @brief 开启/关闭音量提示。默认关闭。<br>
     *        开启音量提示后，将按设置的时间间隔收到本地采集音量或订阅的远端用户的音量信息回调。
     *        关于回调的具体信息，参看 OnAudioVolumeIndication{@link #IRTCRoomEventHandler#OnAudioVolumeIndication}
     * @param [in] interval 收到音量提示回调的时间间隔：  <br>
     *                + ≤ 0：禁用音量提示功能。  <br>
     *                + > 0：启用音量提示功能，并设置收到音量提示回调的时间间隔。单位为毫秒。<br>
     *                建议设置为大于等于 200 毫秒；小于 10 毫秒时，行为未定义。
     */
    virtual void SetAudioVolumeIndicationInterval(int interval) = 0;


    /**
     * @type api
     * @region 多房间
     * @brief 调节来自远端用户的音频播放音量
     * @param user_id 音频来源的远端用户 ID
     * @param volume  播放音量，取值范围： [0,400]  <br>
     *              + 0: 静音  <br>
     *              + 100: 原始音量  <br>
     *              + 400: 最大可为原始音量的 4 倍(自带溢出保护)  <br>
     */
    virtual void SetRemoteAudioPlaybackVolume(const char* user_id, int volume) = 0;

    /**
     * @hidden
     * @deprecated from 326.1, use PauseAllSubscribedStream/ResumeAllSubscribedStream instead
     * @type api
     * @region 多房间
     * @brief 设置对来自远端的所有音频流的接收状态。默认为接收。
     * @param [in] mute_state 接收状态。参看：MuteState{@link #MuteState}
     * @notes 本方法只影响本地是否接收远端音频流，并不影响远端音频设备的采集发送功能。
     */
    virtual void MuteAllRemoteAudio(MuteState mute_state) = 0;

    /**
     * @type api
     * @region 多房间
     * @brief 暂停接收来自远端的媒体流。
     * @param [in] media_type 媒体流类型，指定需要暂停接收音频还是视频流，参看 PauseResumeControlMediaType{@link #PauseResumeControlMediaType}。
     * @notes  <br>
     *        + 该方法仅暂停远端流的接收，并不影响远端流的采集和发送；  <br>
     *        + 该方法不改变用户的订阅状态以及订阅流的属性。  <br>
     *        + 若想恢复接收远端流，需调用 ResumeAllSubscribedStream{@link #IRtcRoom#ResumeAllSubscribedStream}。
     */
    virtual void PauseAllSubscribedStream(PauseResumeControlMediaType media_type) = 0;

    /**
     * @type api
     * @region 多房间
     * @brief 恢复接收来自远端的媒体流
     * @param [in] media_type 媒体流类型，指定需要暂停接收音频还是视频流，参看 PauseResumeControlMediaType{@link #PauseResumeControlMediaType}
     * @notes <br>
     *        + 该方法仅恢复远端流的接收，并不影响远端流的采集和发送；  <br>
     *        + 该方法不改变用户的订阅状态以及订阅流的属性。
     */
    virtual void ResumeAllSubscribedStream(PauseResumeControlMediaType media_type) = 0;

    /**
     * @hidden
     * @deprecated from 326.1, use SubscribeUserStream instead
     * @type api
     * @region 多房间
     * @brief 设置对来自远端指定用户的音频流的接收状态。默认为接收。
     * @param [in] uid 指定远端用户的 ID
     * @param [in] mute_state 接收状态。参看：MuteState{@link #MuteState}
     * @notes 本方法只影响本地是否接收远端音频流，并不影响远端音频设备的采集发送功能。
     */
    virtual void MuteRemoteAudio(const char* uid, MuteState mute_state) = 0;


#ifndef ByteRTC_AUDIO_ONLY

    /**
     * @hidden
    */
    virtual void UpdateCloudRending(const char* cloudrenderJsonString) = 0;

    /**
     * @type api
     * @region 多房间
     * @brief 开启转推直播，并设置合流的视频视图布局和音频属性。
     * @param [in] param 转推直播配置参数。参看 ITranscoderParam{@link #ITranscoderParam}。
     * @param [in] observer 端云一体转推直播观察者。参看 ITranscoderObserver{@link #ITranscoderObserver}。
     *       + 启用服务端转推时，设置 observer 为 null。  <br>
     *       + 启用端云一体转推直播时，设置 observer 接收合流完成的音视频流和 SEI 信息。
     * @notes <br>
     *        1.只有房间模式为直播模式的用户才能调用此方法。  <br>
     *        2.调用该方法后，关于启动结果和推流过程中的错误，会收到 OnLiveTranscodingResult{@link #IRTCRoomEventHandler#OnLiveTranscodingResult} 回调。
     *        3.调用 StopLiveTranscoding{@link #IRtcRoom#StopLiveTranscoding} 停止转推直播。
     */
    virtual void StartLiveTranscoding(ITranscoderParam* param, ITranscoderObserver* observer) = 0;

    /**
     * @type api
     * @region 多房间
     * @brief 停止转推直播。<br>
     *        关于启动转推直播，参看 StartLiveTranscoding{@link #IRtcRoom#StartLiveTranscoding}。
     */
    virtual void StopLiveTranscoding() = 0;

    /**
     * @type api
     * @region 多房间
     * @brief 更新转推直播参数。  <br>
     *        使用 StartLiveTranscoding{@link #IRtcRoom#StartLiveTranscoding} 启用转推直播功能后，使用此方法更新功能配置参数。
     * @param [in] param 配置参数，参看 ITranscoderParam{@link #ITranscoderParam}
     */
    virtual void UpdateLiveTranscoding(ITranscoderParam* param) = 0;

    /**
     * @hidden
     * @deprecated frpm 325, use SetRemoteVideoCanvas in rtcengine instead
     * @type api
     * @region 多房间
     * @brief 设置来自指定远端用户 user_id 的视频渲染时，使用的视图，并设置渲染模式。 <br>
     *        如果需要解除某个用户的绑定视图，你可以把 view 设置为空。
     * @notes  <br>
     *       + 实际使用时，你可以在收到回调 OnUserJoined{@link #OnUserJoined} 或 onFirstRemoteVideoFrame{@link #onfirstremotevideoframe} 时获得远端用户 user_id。  <br>
     *       + 这两个回调的差别是：如果启用了视频录制功能，视频录制服务会作为一个哑客户端加入房间，因此其他客户端会收到对应的 OnUserJoined{@link #OnUserJoined} 回调；
     *       + 而不会收到 onFirstRemoteVideoFrame{@link #onfirstremotevideoframe} 回调。你不应给录制的亚客户端绑定视图（因为它不会发送视频流）。
     * @param [in] user_id 视频来源的远端用户 ID。
     * @param [in] index 视频流属性，参看 StreamIndex{@link #StreamIndex}
     * @param [in] canvas 视图信息和渲染模式，参看：VideoCanvas{@link #VideoCanvas}
     * @return  <br>
     *        + 0：成功  <br>
     *        + !0：失败  <br>
     * @notes 你应在加入房间后，绑定视图。退出房间后，此设置不失效。
     */
    virtual void SetRemoteVideoCanvas(const char* user_id, StreamIndex index, const VideoCanvas& canvas) = 0;

    /**
     * @deprecated frpm 325.1
     * @hidden
     * @type api
     * @region 多房间
     * @brief 去除所有远端视频。
     */
    virtual void RemoveAllRemoteVideo() = 0;

    /**
     * @deprecated frpm 325.1
     * @hidden
     * @type api
     * @region 多房间
     * @brief 去除屏幕共享所有远端视图。
     */
    virtual void RemoveAllRemoteScreen() = 0;

    /**
     * @hidden
     * @deprecated from 326.1, use PauseAllSubscribedStream/ResumeAllSubscribedStream instead
     * @type api
     * @region 多房间
     * @brief 设置是否播放所有远端视频流
     * @param  [in] muteState 接收状态，标识是否接收所有远端音/视频流，参看 MuteState{@link #MuteState}   <br>
     *       + true：停止播放  <br>
     *       + false：开启播放  <br>
     * @notes 本方法不影响远端视频采集和发送状态
     */
    virtual void MuteAllRemoteVideo(MuteState muteState) = 0;


    /**
     * @hidden
     * @deprecated from 326.1, use SubscribeUserStream instead
     * @type api
     * @region 多房间
     * @brief 设置是否播放远端视频流
     * @param [in] userid 视频来源的远端用户 ID
     * @param  [in] muteState 接收状态，标识是否接收远端音/视频流，参看 MuteState{@link #MuteState}   <br>
     *       + true：停止播放  <br>
     *       + false：开启播放  <br>
     * @notes 本方法不影响远端视频采集和发送状态
     */
    virtual void MuteRemoteVideo(const char* userid, MuteState muteState) = 0;

#endif

    /**
     * @hidden
     */
    virtual void SetCustomUserRole(const char* role) = 0;

    /**
     * @hidden
     * @deprecated from 326.1, use JoinRoom instead
     * @type api
     * @region 多房间
     * @brief 设置订阅模式。  <br>
     *        用户调用此方法设置房间中音视频流的订阅模式。默认为自动订阅。  <br>
     *        如需开启手动订阅功能，建议在调用 JoinRoom{@link #JoinRoom} 方法加入房间前完成设置。  <br>
     * @param [in] audio_mode 音频流的订阅模式。参看 SubscribeMode{@link #SubscribeMode}。  <br>
     * @param [in] video_mode 视频流的订阅模式。参看 SubscribeMode{@link #SubscribeMode}。  <br>
     */
    virtual void EnableAutoSubscribe(SubscribeMode audio_mode, SubscribeMode video_mode) = 0;
};

} // namespace bytertc

#endif // BYTE_RTC_ROOM_INTERFACE_H__
