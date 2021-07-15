/*
 * Copyright 2020 @bytedance
 *
 *  Created on: Mar 16, 2020
 */

#pragma once

#include "video_effect_interface.h"  // NOLINT
#include "byte_rtc_engine_defines.h"
#include "byte_rtc_room_event_handler_interface.h"

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
     * @region 房间管理
     * @brief 销毁房间，该接口实现上会先执行退房操作，然后释放房间处理回调指针
     */
    virtual void Destroy() = 0;

    /**
     * @type api
     * @region 房间管理
     * @brief 设置用户角色。  <br>
     *        用户可通过设置用户角色，控制：1.是否发布音视频流；2.用户自身是否在房间中隐身。详见用户角色 CLIENT_ROLE_TYPE{@link #CLIENT_ROLE_TYPE}。  <br>
     *        默认用户角色为主播角色 CLIENT_ROLE_BROADCASTER{@link #CLIENT_ROLE_BROADCASTER}  <br>
     *        房间模式（通过调用接口 SetChannelProfile{@link #SetChannelProfile} 可设置房间模式）为直播模式、游戏模式、云游戏模式时，设置用户角色生效。房间模式为通信模式时不区分用户角色。  <br>
     * @param [in] role 用户角色，详见 CLIENT_ROLE_TYPE{@link #CLIENT_ROLE_TYPE} 。  <br>
     * @notes  <br>
     *       + 在加入房间前，用户可调用此方法设置用户角色。加入房间后，用户也可通过此方法切换用户角色。  <br>
     *       + 用户在加入房间成功后调用该方法切换用户角色，调用成功后，远端用户会收到相应的回调通知：1.用户角色从静默观众切换至观众或主播时会收到 OnUserJoined{@link #OnUserJoined} 回调通知；2.用户角色从观众或主播切换至静默观众时会收到 OnUserOffline{@link #OnUserOffline} 回调通知。  <br>
     */
    virtual void SetClientRole(CLIENT_ROLE_TYPE role) = 0;

    /**
     * @type api
     * @region 房间管理
     * @brief 设置房间模式。  <br>
     *        通过设置房间模式，用户可以选择应用 SDK 针对不同房间模式场景的优化策略。  <br>
     *        默认的房间模式为通信模式 CHANNEL_PROFILE_COMMUNICATION{@link #CHANNEL_PROFILE_COMMUNICATION}  <br>
     *        房间模式必须在调用 JoinChannel{@link #JoinChannel} 加入房间前设置，加入房间后设置不生效。设置用户角色（通过方法 SetClientRole{@link #SetClientRole} ）建议在设置完房间模式后。  <br>
     * @param [in] profile_type 房间模式，详见 CHANNEL_PROFILE_TYPE{@link #CHANNEL_PROFILE_TYPE} 枚举类型。  <br>
     * @notes  <br>
     *       + 为保证音视频质量和实时性，建议相同房间内的用户使用相同的房间模式。  <br>
     */
    virtual void SetChannelProfile(CHANNEL_PROFILE_TYPE profile_type) = 0;

    /**
     * @hidden
     * @type api
     * @region 房间管理
     * @brief 设置 IRTCRoom{@link #IRTCRoom} 对象的事件句柄。
     *        通过设置事件句柄可以监听此 IRTCRoom{@link #IRTCRoom} 对象对应的房间的回调事件。
     * @param [in] room_event_handler
     *        回调处理器，详见 IRTCRoomEventHandler{@link #IRTCRoomEventHandler}
     */
    virtual void SetRtcRoomEventHandler(IRTCRoomEventHandler* room_event_handler) = 0;

    /**
     * @hidden
     * @type api
     * @region 房间管理
     * @brief 加入房间。
     *        用户调用此方法加入此 IRTCRoom{@link #IRTCRoom}
     * 对应的房间。在一个房间内的用户可以相互通话。调用加入房间前，需要调用 CreateRtcRoom{@link #CreateRtcRoom} 方法
     *        创建房间对应的 IRTCRoom{@link #IRTCRoom} 对象。
     * @param [in] token
     *        动态密钥，用于对登录用户进行鉴权验证。进入房间需要携带 Token。可以在控制台生成临时 Token
     * 进行测试，正式上线需要使用密钥 SDK 在您的服务端生成并下发 Token 。
     * @param [in] uid
     *        用户 ID，最大长度为128字节的非空字符串。支持的字符集范围为:
     *            1. 26个大写字母 A ~ Z
     *            2. 26个小写字母 a ~ z
     *            3. 10个数字 0 ~ 9
     *            4. 下划线"_", at符"@", 减号"-"
     * @param [in] info
     *        预留参数。
     * @return
     *      0: 成功
     *      other: 失败
     * @notes
     *        1.使用不同 App ID 的 App 是不能互通的。
     *        2.调用该方法成功加入房间后，本端会收到 OnJoinChannelSuccess{@link #OnJoinChannelSuccess} 回调通知。
     *        3.本端网络状况不佳的情况下，SDK 可能会与服务器失去连接，此时 SDK 将会自动重连，重连成功后，本端会收到
     *          OnRejoinChannelSuccess{@link #OnRejoinChannelSuccess} 回调通知。
     *        4.房间模式（房间模式参考 SetChannelProfile{@link #SetChannelProfile}
     * ）为通话模式下的用户或直播、游戏、云游戏模式 下用户角色（用户角色参考 SetClientRole{@link #SetClientRole}
     * ）为主播或观众的用户加入房间成功后，远端用户会收到 OnUserJoined{@link #OnUserJoined} 回调通知。 5.同一个 App ID
     * 的同一个房间内，每个用户的用户 ID 必须是唯一的。如果两个用户的用户 ID 相同，则后加入房间的用户会将先加入
     *          房间的用户踢出房间，并且先加入房间的用户会收到 OnChannelError{@link #OnChannelError}
     * 回调通知，错误类型为重复登录 BRERR_DUPLICATE_LOGIN{@link #BRERR_DUPLICATE_LOGIN} 。 6.请务必保证生成 Token 使用的
     * App ID 和创建引擎时使用的 App ID 相同，否则会导致加入房间失败。 7.该方法仅能加入此 IRTCRoom{@link #IRTCRoom}
     * 对应的房间，如果需要加入其它房间需要创建对应房间的 IRTCRoom{@link #IRTCRoom} 对象。
     */
    virtual void JoinChannel(const char* token, const char* uid, const char* info) = 0;

    /**
     * @type api
     * @region 房间管理
     * @brief 离开房间。  <br>
     *        用户调用此方法离开房间，结束通话过程，释放所有通话相关的资源。  <br>
     *        调用 JoinChannel{@link #JoinChannel} 方法加入房间后，在通话结束时必须调用此方法结束通话，否则无法开始下一次通话。无论当前是否在房间中，都可以调用此方法。重复调用此方法不会有负面影响。  <br>
     *        此方法是异步操作，调用返回时并没有真正退出房间。真正退出房间后，本地会收到 OnLeaveChannel{@link #OnLeaveChannel} 回调通知。  <br>
     * @notes  <br>
     *       + 通信模式下的用户和其他房间模式下的主播、 观众角色的用户离开房间后，远端用户会收到 OnUserOffline{@link #OnUserOffline} 回调通知。  <br>
     *       + 如果调用 LeaveChannel 后立即调用销毁引擎，SDK 将无法触发 OnLeaveChannel{@link #OnLeaveChannel} 回调。  <br>
     */
    virtual void LeaveChannel() = 0;

    /**
     * @type api
     * @region 房间管理
     * @brief 更新 Token。  <br>
     *        Token 有一定的有效期，当 Token 过期时，用户需调用此方法更新房间的 Token 信息。  <br>
     *        用户调用 JoinChannel{@link #JoinChannel} 方法加入房间时，如果使用了过期的 Token 将导致加入房间失败，并会收到 OnChannelError{@link #OnChannelError} 回调通知，回调错误码为 BRERR_INVALID_TOKEN{@link #BRERR_INVALID_TOKEN} 。此时需要重新获取 Token ，并调用此方法更新 Token。  <br>
     * @param [in] token 更新的动态密钥。Token 用于对登录用户进行鉴权验证。  <br>
     * @notes  <br>
     *       + 如果用户因 Token 过期导致加入房间失败，则调用此方法更新 Token 后 SDK 会自动重新加入房间，而不需要用户自己调用 JoinChannel{@link #JoinChannel} 方法。  <br>
     *       + Token过期时，如果已经加入房间成功，则不会受到影响。Token 过期的错误会在下一次使用过期的 Token 加入房间或由于本地网络状况不佳导致断网重连入房间时通知给用户。  <br>
     */
    virtual void RenewToken(const char* token) = 0;

    /**
     * @type api
     * @region 流消息
     * @brief 给房间内指定的用户发送消息，返回这次发送消息的编号。  <br>
     *        调用该函数后会收到一次 OnUserMessageSendResult{@link #IRTCRoomEventHandler#OnUserMessageSendResult}
     *        回调，告知发送结果。
     * @param [in] uid  <br>
     *        指定用户 ID 。
     * @param [in] message  <br>
     *        发送的消息内容。
     * @return 这次发送消息的编号，从 1 开始递增。
     * @notes
     *      1.调用该函数后会收到一次OnUserMessageSendResult{@link
     * #IRTCRoomEventHandler#OnUserMessageSendResult} 回调；
     *      2.若消息发送成功，则 uid 所指定的用户会收到
     * OnUserMessageReceived{@link #IRTCRoomEventHandler#OnUserMessageReceived} 回调。
     */
    virtual int64_t SendUserMessage(const char* uid, const char* message) = 0;

    /**
     * @type api
     * @region 流消息
     * @brief 给房间内指定的用户发送二进制消息，返回这次发送消息的编号。
     * @param [in] uid 指定用户 ID
     * @param [in] length 二进制字符串的长度
     * @param [in] message 发送的二进制消息内容
     * @return
     *      返回这次发送消息的编号，从 1 开始递增
     * @notes
     *      1.调用该函数后会收到一次 OnUserMessageSendResult{@link
     * #IRTCRoomEventHandler#OnUserMessageSendResult} 回调；
     *      2.若消息发送成功，则 uid 所指定的用户会收到
     * OnUserBinaryMessageReceived{@link #IRTCRoomEventHandler#OnUserBinaryMessageReceived} 回调。
     */
    virtual int64_t SendUserBinaryMessage(const char* uid, int length, const uint8_t* message) = 0;

    /**
     * @type api
     * @region 流消息
     * @brief 给房间内的所有其他用户发送广播消息。
     * @param [in] message 用户发送的广播消息
     * @notes
     *      1.调用该函数后会收到一次 OnRoomMessageSendResult{@link
     * #IRTCRoomEventHandler#OnRoomMessageSendResult} 回调；
     *      2.同一房间内的其他用户会收到 OnRoomMessageReceived{@link
     * #IRTCRoomEventHandler#OnRoomMessageReceived} 回调。
     */
    virtual int64_t SendRoomMessage(const char* message) = 0;

    /**
     * @type api
     * @region 流消息
     * @brief 给房间内的所有其他用户发送广播消息。
     * @param [in] size 发送的二进制消息长度
     * @param [in] message 用户发送的二进制广播消息
     * @notes
     *      1.调用该函数后会收到一次 OnRoomMessageSendResult{@link
     * #IRTCRoomEventHandler#OnRoomMessageSendResult} 回调；
     *      2.同一房间内的其他用户会收到 OnRoomBinaryMessageReceived{@link
     * #IRTCRoomEventHandler#OnRoomBinaryMessageReceived} 回调。
     */
    virtual int64_t SendRoomBinaryMessage(int size, const uint8_t* message) = 0;

    /**
     * @hidden
     * @type api
     * @region 房间管理
     * @brief 将本端音视频流发布到此房间。
     * @notes
     *        1.此方法仅支持在关闭自动发布功能时调用，用户可通过调用 EnableAutoPublish{@link #EnableAutoPublish}
     * 方法设置关闭自动发布。 2.直播、游戏、云游戏房间模式下，此方法仅适用于角色为主播的用户。App 可以通过调用
     * SetClientRole{@link #SetClientRole} 方法设置用户角色。 3.目前 SDK 只支持用户同一时间发布一路音视频流。
     *        4.用户调用此方法成功发布音视频流后，房间中的其他用户将会收到 OnStreamAdd{@link #OnStreamAdd} 回调通知。
     */
    virtual void Publish() = 0;

    /**
     * @hidden
     * @type api
     * @region 房间管理
     * @brief 停止将本端音视频流发布到此房间。
     * @notes
     *        1.此方法仅支持在关闭自动发布功能时调用，用户可通过调用 EnableAutoPublish{@link #EnableAutoPublish}
     * 方法设置关闭自动发布。 2.用户调用此方法停止发布音视频流后，房间中的其他用户将会收到 OnStreamRemove{@link
     * #OnStreamRemove} 回调通知。
     */
    virtual void Unpublish() = 0;

    /**
     * @type api
     * @region 视频管理
     * @brief 发布本地屏幕共享流到房间。
     * @param [in] paramters
     *        屏幕共享流编码参数，详见 ScreenParameters{@link #ScreenParameters}
     * @notes  <br>
     *       + 直播、游戏、云游戏房间模式下，此方法仅适用于角色为主播的用户。应用可以通过调用 SetClientRole{@link#SetClientRole} 方法设置用户角色。  <br>
     *       + 调用此方法发布本端屏幕共享流后，用户还需要通过设置定时任务周期性调用 PushScreenFrame{@link #IRtcEngineLite#PushScreenFrame} 方法，将需要发送的屏幕数据推送给 SDK。  <br>
     *       + 远端会收到 OnFirstRemoteScreenFrame{@link #IRTCRoomEventHandler#OnFirstRemoteScreenFrame} 、OnStreamAdd{@link#IRTCRoomEventHandler#OnStreamAdd} 事件。  <br>
     *       + 该函数和 StartScreenCaptureByWindowId{@link#IRtcEngineLite#StartScreenCaptureByWindowId} 、StartScreenCaptureByScreenRect{@link#IRtcEngineLite#StartScreenCaptureByScreenRect} 函数是互斥调用的，可在调用 UnpublishScreen{@link#IUnpublishScreen} 函数后调用上述函数。  <br>
     *       + 在收到 OnFirstRemoteScreenFrame{@link#IRTCRoomEventHandler#OnFirstRemoteScreenFrame} 事件后通过调用 SetupRemoteScreen{@link #SetupRemoteScreen} 或 SetRemoteScreenRender{@link #SetRemoteScreenRender} 函数来设置远端屏幕共享视图。  <br>
     *       + 本地可调用 SetupLocalScreen{@link #IRtcEngineLite#SetupLocalScreen} 或 SetLocalScreenRender{@link#IRtcEngineLite#SetLocalScreenRender} 函数设置本地屏幕共享视图。  <br>
     *       + 也可通过注册 RegisterVideoFrameObserver{@link#RegisterVideoFrameObserver} 视频回调对象，监听 OnLocalScreenFrame{@link #IVideoFrameObserver#OnLocalScreenFrame}本地屏幕视频回调事件和 OnRemoteScreenFrame{@link #IVideoFrameObserver#OnRemoteScreenFrame}远端屏幕共享视频回调事件来获取原始数据。  <br>
     */
    virtual void PublishScreen(const ScreenParameters& paramters = ScreenParameters()) = 0;

    /**
     * @type api
     * @region 视频管理
     * @brief 停止发布本地屏幕共享流到房间。
     * @notes 远端会收到 OnStreamRemove{@link #IRTCRoomEventHandler#OnStreamRemove} 事件。
     */
    virtual void UnpublishScreen() = 0;

    /**
     * @type api
     * @region 房间管理
     * @brief 订阅指定的房间内远端音视频流。  <br>
     *        关闭自动订阅功能，使用手动订阅模式时用户调用此方法按需订阅房间中的音视频流。  <br>
     *        此方法仅在关闭自动订阅功能时生效。用户需在加入房间前调用 EnableAutoSubscribe{@link #EnableAutoSubscribe} 方法关闭自动订阅功能以使用手动订阅模式。  <br>
     *        用户在自动订阅功能开启时调用此方法，SDK 不会订阅音视频流，并通过 OnChannelWarning{@link #OnChannelWarning} 回调通知用户订阅失败，回调警告码为 BRWARN_SUBSCRIBE_STREAM_FORBIDEN{@link #BRWARN_SUBSCRIBE_STREAM_FORBIDEN} 。  <br>
     *        订阅流失败时，SDK 会按失败原因回调 OnChannelError{@link #OnChannelError} 通知用户，具体错误可参考错误码 RTC_ERROR_CODE{@link #RTC_ERROR_CODE} 描述。  <br>
     * @param [in] user_id 指定订阅的远端用户的用户ID 。  <br>
     * @param [in] info 选择订阅配置，详见数据结构 SubscribeConfig{@link #SubscribeConfig} 。  <br>
     * @notes  <br>
     *       + 此方法仅支持订阅当前房间中的远端音视频流。如果指定的流在当前房间内不曾存在，则 SDK 不会订阅。  <br>
     *       + 用户调用 JoinChannel{@link #JoinChannel} 方法加入房间后：1.当房间内有新的音视频流发布时，本地会收到 OnStreamAdd{@link #OnStreamAdd} 回调通知；2.当房间内音视频流停止发布时，本地会收到 OnStreamRemove{@link #OnStreamRemove} 回调通知。通过这两个回调用户可以获得当前房间中的音视频流信息，并在需要时调用此方法订阅该音视频流。  <br>
     */
    virtual void SubscribeStream(const char* user_id, const SubscribeConfig& info) = 0;

    /**
     * @type api
     * @region 房间管理
     * @brief 停止订阅指定的房间内远端音视频流。  <br>
     *        关闭自动订阅功能，使用手动订阅模式时用户调用此方法停止订阅已订阅的音视频流。  <br>
     *        此方法仅在关闭自动订阅功能时生效。用户需在加入房间前调用 EnableAutoSubscribe{@link #EnableAutoSubscribe} 方法关闭自动订阅功能以使用手动订阅模式。  <br>
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
     * @type api
     * @region 音频管理
     * @brief 设置是否开启房间内音量提示。<br>
     *        如果开启，将以设置的时间间隔收到音量事件回调。无论房间内有无发言，都会收到回调。
     *        具体回调参看 OnAudioVolumeIndication{@link #IRTCRoomEventHandler#OnAudioVolumeIndication}
     * @param interval 收到音量提示回调的时间间隔  <br>
     *                + ≤ 0：禁用音量提示功能。  <br>
     *                + > 0：启用音量提示功能，并设置收到音量提示回调的时间间隔。单位为毫秒。<br>
     *                建议设置为大于等于 200 毫秒；小于 10 毫秒时，行为未定义。
     */
    virtual void SetAudioVolumeIndicationInterval(int interval) = 0;

    /**
     * @type api
     * @region 音频管理
     * @brief 调节来自远端用户的音频播放音量
     * @param user_id 音频来源的远端用户 ID
     * @param volume  播放音量，取值范围： [0,400]  <br>
     *              + 0: 静音  <br>
     *              + 100: 原始音量  <br>
     *              + 400: 最大可为原始音量的 4 倍(自带溢出保护)  <br>
     */
    virtual void SetRemoteAudioPlaybackVolume(const char* user_id, int volume) = 0;

    /**
     * @type api
     * @region 音频管理
     * @brief 设置对来自远端的所有音频流的接收状态。默认为接收。
     * @param [in] mute_state 接收状态。参看：MuteState{@link #MuteState}
     * @notes 本方法只影响本地是否接收远端音频流，并不影响远端音频设备的采集发送功能。
     */
    virtual void MuteAllRemoteAudio(MuteState mute_state) = 0;

    /**
     * @type api
     * @region 音频管理
     * @brief 设置对来自远端指定用户的音频流的接收状态。默认为接收。
     * @param [in] uid 指定远端用户的 ID
     * @param [in] mute_state 接收状态。参看：MuteState{@link #MuteState}
     * @notes 本方法只影响本地是否接收远端音频流，并不影响远端音频设备的采集发送功能。
     */
    virtual void MuteRemoteAudio(const char* uid, MuteState mute_state) = 0;

#ifndef BYTERTC_AUDIO_ONLY

    /**
     * @hidden
    */
    virtual void UpdateCloudRending(const char* cloudrenderJsonString) = 0;

    /**
     * @hidden
     * @type api
     * @region CDN 推流
     * @brief 开启直播推流转码。
     *        该方法用于开启直播推流转码，并设置旁路推流的视频视图布局及音频属性等。
     * @param [in] transcode_json_string
     *        转码属性
     * @notes
     *        1.直播推流转码功能，会根据设置的视频视图布局和音频属性进行合流并推送合流到设置的 CDN。
     *        2.只有房间模式为直播模式，且用户角色为主播的用户才能调用此方法。
     */
    virtual void EnableLiveTranscoding(const char* transcode_json_string) = 0;

    /**
     * @hidden
     * @type api
     * @region CDN 推流
     * @brief 停止直播推流转码。
     */
    virtual void DisableLiveTranscoding() = 0;

    /**
     * @hidden
     * @type api
     * @region CDN 推流
     * @brief 设置画中画布局。该方法设置直播场景里的画中画布局。该方法仅适用于服务器端推流的场景。
     * @param [in] transcode_json_string
     *        布局属性
     */
    virtual void SetVideoCompositingLayout(const char* transcode_json_string) = 0;

    /**
     * @type api
     * @region 视频管理
     * @brief 设置来自指定远端用户 user_id 的视频渲染时，使用的视图，并设置渲染模式。 <br>
     *        你应在加入房间前，绑定视图。退出房间后，此设置失效。<br>
     *        如果需要解除某个用户的绑定视图，你可以把 view 设置为空。
     * @notes  <br>
     *       + 实际使用时，你可以在收到回调 OnUserJoined{@link #OnUserJoined} 或 onFirstRemoteVideoFrame{@link #onfirstremotevideoframe} 时获得远端用户 user_id。  <br>
     *       + 这两个回调的差别是：如果启用了视频录制功能，视频录制服务会作为一个哑客户端加入房间，因此其他客户端会收到对应的 OnUserJoined{@link #OnUserJoined} 回调；
     *       + 而不会收到 onFirstRemoteVideoFrame{@link #onfirstremotevideoframe} 回调。你不应给录制的亚客户端绑定视图（因为它不会发送视频流）。
     * @param [in] user_id 视频来源的远端用户 ID。
     * @param [in] index 视频流属性, 参看 StreamIndex{@link #StreamIndex}
     * @param [in] canvas 视图信息和渲染模式，参看：VideoCanvas{@link #VideoCanvas}
     * @return  <br>
     *        + 0：成功  <br>
     *        + !0：失败  <br>
     */
    virtual void SetRemoteVideoCanvas(const char* user_id, StreamIndex index, const VideoCanvas& canvas) = 0;

    /**
     * @type api
     * @region 视频管理
     * @brief 设置远端视频外部渲染器
     * @param [in] uid
     *        远端用户ID
     * @param [in] render
     *        外部渲染器，详见：{@link #IVideoSink}
     * @notes 该方法绑定远程用户视频流的渲染器，如需解绑，设置为空即可。
     */
    virtual void SetRemoteVideoRender(const char* uid, IVideoSink* render) = 0;

    /**
     * @type api
     * @region 视频管理
     * @brief 去除所有远端视频。
     */
    virtual void RemoveAllRemoteVideo() = 0;

    /**
     * @type api
     * @region 视频管理
     * @brief 设置屏幕共享远端外部渲染器
     * @param [in] uid
     *        远端用户ID
     * @param [in] render
     *        外部渲染器，详见：IVideoSink{@link #IVideoSink}
     * @notes 该方法绑定远端用户屏幕共享流的渲染器，如需解绑，设置为空即可。
     */
    virtual void SetRemoteScreenRender(const char* uid, IVideoSink* render) = 0;

    /**
     * @type api
     * @region 视频管理
     * @brief 去除屏幕共享所有远端视图。
     */
    virtual void RemoveAllRemoteScreen() = 0;

    /**
     * @type api
     * @region 视频管理
     * @brief 设置是否默认接收视频流.
     * @param  [in] mute  <br>
     *       + true：禁止远端的视频  <br>
     *       + false：开启远端的视频  <br>
     * @notes 该方法在加入房间前后都可调用。如果在加入房间后调用，会接收不到后面加入房间的用户的视频流
     */
    virtual void SetDefaultMuteAllRemoteVideoStreams(bool mute) = 0;

    /**
     * @type api
     * @region 视频管理
     * @brief 远端首帧视频帧渲染.
     * @param [in] userid 远端用户ID
     * @param [in] elapse 加入频道开始到该回调触发过去的时间（ms）
     * @param [in] timestamp 当前时间的时间戳（ms）
     * @return  <br>
     *        + 0：成功  <br>
     *        + !0：失败  <br>
     */
    virtual int RemoteFirstVideoFrameRender(const char* userid, unsigned int elapse, int64_t timestamp) {
        return 0;
    }

    /**
     * @type api
     * @region 视频管理
     * @brief 设置是否播放所有远端视频流
     * @param  [in] muteState 参看 MuteState{@link #MuteState}   <br>
     *       + true：停止播放  <br>
     *       + false：开启播放  <br>
     * @notes 本方法不影响远端视频采集和发送状态
     */
    virtual void MuteAllRemoteVideo(MuteState muteState) = 0;

    /**
     * @type api
     * @region 视频管理
     * @brief 设置是否播放远端视频流
     * @param [in] userid 视频来源的远端用户 ID
     * @param  [in] muteState 参看 MuteState{@link #MuteState}   <br>
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
     * @type api
     * @region 房间管理
     * @brief 设置订阅模式。  <br>
     *        用户调用此方法设置房间中音视频流的订阅模式。SDK 默认使用自动订阅模式。<br>
     *        如需开启手动订阅功能，建议在调用 JoinChannel{@link #JoinChannel} 方法加入房间前设置完成。  <br>
     * @param [in] audio_mode 音频流的订阅模式。详见枚举类型 SubscribeMode{@link #SubscribeMode}。  <br>
     * @param [in] video_mode 视频流的订阅模式。详见枚举类型 SubscribeMode{@link #SubscribeMode}。  <br>
     * @notes  <br>
     *       + SDK 提供两种订阅模式：1.自动订阅模式，开启自动订阅功能时，SDK 自动帮助用户订阅房间中所有其他用户发布的音视频流；2.手动订阅模式，关闭自动订阅功能时，SDK不会自动订阅房间内的音视频流，只通过 OnStreamAdd{@link #OnStreamAdd} 和 OnStreamRemove{@link #OnStreamRemove} 回调通知用户当前所在房间中有哪些音视频流，由用户根据自己的需要调用 SubscribeStream{@link #SubscribeStream} 方法手动订阅其他用户发布的音视频流。  <br>
     *       + SDK 可以分别对音频/视频设置订阅模式。  <br>
     */
    virtual void EnableAutoSubscribe(SubscribeMode audio_mode, SubscribeMode video_mode) = 0;
};

} /* namespace bytertc */
