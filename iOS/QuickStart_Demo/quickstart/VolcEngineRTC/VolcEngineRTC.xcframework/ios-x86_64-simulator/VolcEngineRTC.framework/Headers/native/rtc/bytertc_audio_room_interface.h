/*
 * Copyright (c) 2022 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC Room Interface
 */

#pragma once

#include "bytertc_audio_defines.h"
#include "bytertc_audio_room_event_handler.h"

namespace bytertc {

/** 
 * @type api
 * @brief 房间接口
 */
class IRTCAudioRoom {
public:
    /** 
     * @hidden
     * @brief 析构函数
     */
    virtual ~IRTCAudioRoom() {
    }

    /** 
     * @hidden
     * @type api
     * @region 多房间
     * @brief 销毁房间，该接口实现上会先执行退房操作，然后释放房间处理回调指针
     */
    virtual void Destroy() = 0;

    /** 
     * @type api
     * @region 多房间
     * @brief 创建/加入房间：房间不存在时即创建房间；房间存在时，未加入房间的用户可加入这个房间。  <br>
     *        同一房间内的用户间可以相互通话。  <br>
     *        进房后重复调用无效，用户必须调用 `LeaveRoom` 退出当前房间后，才能加入下一个房间。  <br>
     * @param [in] token 动态密钥，用于对登录用户进行鉴权验证。  <br>
     *        进入房间需要携带 Token。测试时可使用控制台生成临时 Token，正式上线需要使用密钥 SDK 在您的服务端生成并下发 Token。  <br>
     *       + 使用不同 App ID 的 App 是不能互通的。  <br>
     *       + 请务必保证生成 Token 使用的 App ID 和创建引擎时使用的 App ID 相同，否则会导致加入房间失败。  <br>
     * @param [in] user_info 用户信息，参看 UserInfo{@link #UserInfo}。  <br>
     * @param [in] room_config 房间参数配置，设置房间模式以及是否自动发布或订阅流。具体配置模式参看 AudioRoomConfig{@link #AudioRoomConfig}。  <br>
     * @return  <br>
     *        +  0: 成功  <br>
     *        + -1：room_id / user_info.uid 包含了无效的参数。  <br>
     *        + -2：已经在房间内。接口调用成功后，只要收到返回值为 0 ，且未调用 `LeaveRoom` 成功，则再次调用进房接口时，无论填写的房间 ID 和用户 ID 是否重复，均触发此返回值。  <br>
     * @notes  <br>
     *       + 同一个 App ID 的同一个房间内，每个用户的用户 ID 必须是唯一的。如果两个用户的用户 ID 相同，则后进房的用户会将先进房的用户踢出房间，并且先进房的用户会收到 OnError{@link #IRTCAudioEngineEventHandler#OnError} 回调通知，错误类型详见 ErrorCode{@link #ErrorCode} 中的 kErrorCodeDuplicateLogin。  <br>
     *       + 本地用户调用此方法加入房间成功后，会收到 OnJoinRoomResult{@link #IRTCAudioRoomEventHandler#OnJoinRoomResult} 回调通知。  <br>
     *       + 本地用户调用 SetUserVisibility{@link #IRTCAudioRoom#SetUserVisibility} 将自身设为可见后加入房间，远端用户会收到 OnUserJoined{@link #IRTCAudioRoomEventHandler#OnUserJoined}。  <br>
     *       + 用户加入房间成功后，在本地网络状况不佳的情况下，SDK 可能会与服务器失去连接，此时 SDK 将会自动重连。重连成功后，本地会收到 OnJoinRoomResult{@link #IRTCAudioRoomEventHandler#OnJoinRoomResult} 回调通知。  <br>
     */
    virtual int JoinRoom(const char* token, const UserInfo& user_info, const AudioRoomConfig& room_config) = 0;

    /** 
     * @type api
     * @region 多房间
     * @brief 离开房间。  <br>
     *        用户调用此方法离开房间，结束通话过程，释放所有通话相关的资源。  <br>
     *        加入房间后，必须调用此方法结束通话，否则无法开始下一次通话。无论当前是否在房间内，都可以调用此方法。重复调用此方法没有负面影响。  <br>
     * @notes  <br>
     *       + 此方法是异步操作，调用返回时并没有真正退出房间。真正退出房间后，本地会收到 OnLeaveRoom{@link #IRTCAudioRoomEventHandler#OnLeaveRoom} 回调通知。  <br>
     *       + 可见的用户离开房间后，房间内其他用户会收到 OnUserLeave{@link #IRTCAudioRoomEventHandler#OnUserLeave} 回调通知。  <br>
     *       + 如果调用此方法后立即销毁引擎，SDK 将无法触发 OnLeaveRoom{@link #IRTCAudioRoomEventHandler#OnLeaveRoom} 回调。  <br>
     *       + 调用 JoinRoom{@link #IRTCAudioRoom#JoinRoom} 方法加入房间后，必须调用此方法离开房间，否则无法进入下一个房间。无论当前是否在房间内，都可以调用此方法。重复调用此方法没有负面影响。  <br>
     */
    virtual void LeaveRoom() = 0;

    /** 
     * @type api
     * @region 多房间
     * @brief 更新 Token。  <br>
     *        Token 有一定的有效期，当 Token 过期时，用户需调用此方法更新房间的 Token 信息。  <br>
     *        用户调用 JoinRoom{@link #IRTCAudioRoom#JoinRoom} 方法加入房间时，如果使用了过期的 Token 将导致加入房间失败，并会收到 OnJoinRoomResult{@link #IRTCAudioRoomEventHandler#OnJoinRoomResult} 回调通知，错误码为 ErrorCode{@link #ErrorCode} 中的 kErrorCodeInvalidToken 。此时需要重新获取 Token，并调用此方法更新 Token。  <br>
     * @param [in] token 更新的动态密钥。  <br>
     * @notes  <br>
     *       + 如果用户因 Token 过期导致加入房间失败，则调用此方法更新 Token 后，SDK 会自动重新加入房间，而不需要用户自己调用 JoinRoom{@link #IRTCAudioRoom#JoinRoom} 方法。  <br>
     *       + Token 过期时，如果已经加入房间成功，则不会受到影响。Token 过期的错误会在下一次使用过期 Token 加入房间时，或因本地网络状况不佳导致断网重新连入房间时通知给用户。  <br>
     */
    virtual void UpdateToken(const char* token) = 0;

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
     *            - 从 false 切换至 true 时，房间内其他用户会收到 OnUserJoined{@link #IRTCAudioRoomEventHandler#OnUserJoined} 回调通知；  <br>
     *            - 从 true 切换至 false 时，房间内其他用户会收到 OnUserLeave{@link #IRTCAudioRoomEventHandler#OnUserLeave} 回调通知。 <br>
     *        + 若调用该方法将可见性设为 false，此时尝试发布流会收到 OnWarning{@link #IRTCAudioEngineEventHandler#OnWarning} 警告，具体原因参看 WarningCode{@link #WarningCode} 中的 kWarningCodePublishStreamForbiden 警告码。
     */
    virtual void SetUserVisibility(bool enable) = 0;

    /** 
     * @hidden
     * @type api
     * @region 多房间
     * @brief 设置 IRtcRoom{@link #IRtcRoom} 对象的事件句柄。
     *        通过设置事件句柄可以监听此 IRtcRoom{@link #IRtcRoom} 对象对应的房间的回调事件。
     * @param [in] room_event_handler
     *        回调处理器，详见 IRTCRoomEventHandler{@link #IRTCRoomEventHandler}
     */
    virtual void SetRTCRoomEventHandler(IRTCAudioRoomEventHandler* room_event_handler) = 0;

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
     * @type api
     * @region 多房间
     * @brief 给房间内指定的用户发送文本消息（P2P）
     * @param [in] user_id  <br>
     *        消息接收用户的 ID
     * @param [in] message  <br>
     *        发送的文本消息内容。  <br>
     *        消息不超过 62KB。
     * @return 这次发送消息的编号，从 1 开始递增。
     * @notes  <br>
     *       + 在发送房间内文本消息前，必须先调用 JoinRoom{@link #IRTCAudioRoom#JoinRoom} 加入房间。  <br>
     *       + 调用该函数后会收到一次 OnUserMessageSendResult{@link #IRTCAudioRoomEventHandler#OnUserMessageSendResult} 回调，通知消息发送方发送成功或失败；  <br>
     *       + 若文本消息发送成功，则 user_id 所指定的用户会收到 OnUserMessageReceived{@link #IRTCAudioRoomEventHandler#OnUserMessageReceived} 回调。
     */
    virtual int64_t SendUserMessage(const char* user_id, const char* message) = 0;

    /** 
     * @type api
     * @region 多房间
     * @brief 给房间内指定的用户发送二进制消息（P2P）
     * @param [in] user_id  <br>
     *        消息接收用户的 ID
     * @param [in] length   <br>
     *        二进制字符串的长度。
     * @param [in] message   <br>
     *        二进制消息的内容。
     *        消息不超过 46KB。
     * @return 这次发送消息的编号，从 1 开始递增。
     * @notes  <br>
     *       + 在发送房间内二进制消息前，必须先调用 JoinRoom{@link #IRTCAudioRoom#JoinRoom} 加入房间。  <br>
     *       + 调用该函数后会收到一次 OnUserMessageSendResult{@link #IRTCAudioRoomEventHandler#OnUserMessageSendResult} 回调，通知消息发送方发送成功或失败；  <br>
     *       + 若二进制消息发送成功，则 user_id 所指定的用户会收到 OnUserBinaryMessageReceived{@link #IRTCAudioRoomEventHandler#OnUserBinaryMessageReceived} 回调。
     */
    virtual int64_t SendUserBinaryMessage(const char* user_id, int length, const uint8_t* message) = 0;

    /** 
     * @type api
     * @region 多房间
     * @brief 给房间内的所有其他用户发送广播消息。
     * @param [in] message  <br>
     *        用户发送的广播消息  <br>
     *        消息不超过 62KB。
     * @notes  <br>
     *       + 在发送房间内二进制消息前，必须先调用 JoinRoom{@link #IRTCAudioRoom#JoinRoom} 加入房间。  <br>
     *       + 调用该函数后，会收到一次 OnRoomMessageSendResult{@link #IRTCAudioRoomEventHandler#OnRoomMessageSendResult} 回调。  <br>
     *       + 同一房间内的其他用户会收到 OnRoomMessageReceived{@link #IRTCAudioRoomEventHandler#OnRoomMessageReceived} 回调。
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
     *       + 在发送房间内二进制消息前，必须先调用 JoinRoom{@link #IRTCAudioRoom#JoinRoom} 加入房间。  <br>
     *       + 调用该函数后，会收到一次 OnRoomMessageSendResult{@link #IRTCAudioRoomEventHandler#OnRoomMessageSendResult} 回调。  <br>
     *       + 同一房间内的其他用户会收到 OnRoomBinaryMessageReceived{@link #IRTCAudioRoomEventHandler#OnRoomBinaryMessageReceived} 回调。
     */
    virtual int64_t SendRoomBinaryMessage(int size, const uint8_t* message) = 0;

    virtual void PublishStream() = 0;

    virtual void UnpublishStream() = 0;

    virtual void SubscribeStream(const char* user_id) = 0;
    
    virtual void UnsubscribeStream(const char* user_id) = 0;

    /** 
     * @type api
     * @region 多房间
     * @brief 暂停接收来自远端的媒体流。
     * @notes  <br>
     *        + 该方法仅暂停远端流的接收，并不影响远端流的采集和发送；  <br>
     *        + 该方法不改变用户的订阅状态以及订阅流的属性。  <br>
     *        + 若想恢复接收远端流，需调用 ResumeAllSubscribedStream{@link #IRTCAudioRoom#ResumeAllSubscribedStream}。
     */
    virtual void PauseAllSubscribedStream() = 0;

    /** 
     * @type api
     * @region 多房间
     * @brief 恢复接收来自远端的媒体流
     * @notes <br>
     *        + 该方法仅恢复远端流的接收，并不影响远端流的采集和发送；  <br>
     *        + 该方法不改变用户的订阅状态以及订阅流的属性。
     */
    virtual void ResumeAllSubscribedStream() = 0;

    /** 
     * @type api
     * @region 多房间
     * @brief 开始跨房间转发媒体流。
     *        在用户进入房间后调用本接口，实现向多个房间转发媒体流，适用于跨房间连麦等场景。<br>  
     * @param [in] configuration 跨房间媒体流转发指定房间的信息。参看 ForwardStreamConfiguration{@link #ForwardStreamConfiguration}。
     * @return  <br>
     *        0: 方法调用成功  <br>
     *        <0: 方法调用失败  <br>
     * @notes <br>
     *        + 调用本方法后，将在本端触发 OnForwardStreamStateChanged{@link #IRTCAudioRoomEventHandler#OnForwardStreamStateChanged} 回调。
     *        + 调用本方法后，你可以通过监听 OnForwardStreamEvent{@link #IRTCAudioRoomEventHandler#OnForwardStreamEvent} 回调来获取各个目标房间在转发媒体流过程中的相关事件。
     *        + 开始转发后，目标房间中的用户将接收到本地用户进房 OnUserJoined{@link #IRTCAudioRoomEventHandler#OnUserJoined} 和发流 OnUserPublishStream{@link #IRTCAudioRoomEventHandler#OnUserPublishStream}  的回调。
     *        + 调用本方法后，可以调用 UpdateForwardStreamToRooms{@link #IRTCAudioRoom#UpdateForwardStreamToRooms} 更新目标房间信息，例如，增加或减少目标房间等。
     *        + 调用本方法后，可以调用 StopForwardStreamToRooms{@link #IRTCAudioRoom#StopForwardStreamToRooms} 停止向所有房间转发媒体流。
     *        + 调用本方法后，可以调用 PauseForwardStreamToAllRooms{@link #IRTCAudioRoom#PauseForwardStreamToAllRooms} 暂停向所有房间转发媒体流。
     */
    virtual int StartForwardStreamToRooms(const ForwardStreamConfiguration& configuration) = 0;

    /** 
     * @type api
     * @region 房间管理
     * @brief 更新跨房间媒体流转发信息。<br>
     *        通过 StartForwardStreamToRooms{@link #IRTCAudioRoom#StartForwardStreamToRooms} 发起媒体流转发后，可调用本方法增加或者减少目标房间，或更新房间密钥。
     *        调用本方法增加或删减房间后，将在本端触发 OnForwardStreamStateChanged{@link #IRTCAudioRoomEventHandler#OnForwardStreamStateChanged} 回调，包含发生了变动的目标房间中媒体流转发状态。
     * @param [in] configuration 跨房间媒体流转发目标房间信息。参看 ForwardStreamConfiguration{@link #ForwardStreamConfiguration}。
     * @return  <br>
     *        0: 方法调用成功  <br>
     *        <0: 方法调用失败  <br>
     * @notes <br>
     *        + 增加目标房间后，新增目标房间中的用户将接收到本地用户进房 OnUserJoined{@link #IRTCAudioRoomEventHandler#OnUserJoined} 和发布 OnUserPublishStream{@link #IRTCAudioRoomEventHandler#OnUserPublishStream}  的回调。
     *        + 删减目标房间后，原目标房间中的用户将接收到本地用户停止发布 OnUserUnPublishStream{@link #IRTCAudioRoomEventHandler#OnUserUnPublishStream}  和退房 OnUserLeave{@link #IRTCAudioRoomEventHandler#OnUserLeave} 的回调。
     */
    virtual int UpdateForwardStreamToRooms(const ForwardStreamConfiguration& configuration) = 0;

    /** 
     * @type api
     * @region 多房间
     * @brief 停止跨房间媒体流转发。
     *        通过 StartForwardStreamToRooms{@link #IRTCAudioRoom#StartForwardStreamToRooms} 发起媒体流转发后，可调用本方法停止向所有目标房间转发媒体流。
     * @notes <br>
     *        + 调用本方法后，将在本端触发 OnForwardStreamStateChanged{@link #IRTCAudioRoomEventHandler#OnForwardStreamStateChanged} 回调。
     *        + 调用本方法后，原目标房间中的用户将接收到本地用户停止发布 OnUserUnPublishStream{@link #IRTCAudioRoomEventHandler#OnUserUnPublishStream}  和退房 OnUserLeave{@link #IRTCAudioRoomEventHandler#OnUserLeave} 的回调。
     *        + 如果需要停止向指定的房间转发媒体流，请调用 UpdateForwardStreamToRooms{@link #IRTCAudioRoom#UpdateForwardStreamToRooms} 更新房间信息。
     *        + 如果需要暂停转发，请调用 PauseForwardStreamToAllRooms{@link #IRTCAudioRoom#PauseForwardStreamToAllRooms}，并在之后随时调用 ResumeForwardStreamToAllRooms{@link #IRTCAudioRoom#ResumeForwardStreamToAllRooms} 快速恢复转发。 
     */
    virtual void StopForwardStreamToRooms() = 0;

    /** 
     * @type api
     * @region 多房间
     * @brief 暂停跨房间媒体流转发。
     *        通过 StartForwardStreamToRooms{@link #IRTCAudioRoom#StartForwardStreamToRooms} 发起媒体流转发后，可调用本方法暂停向所有目标房间转发媒体流。
     *        调用本方法暂停向所有目标房间转发后，你可以随时调用 ResumeForwardStreamToAllRooms{@link #IRTCAudioRoom#ResumeForwardStreamToAllRooms} 快速恢复转发。
     * @notes 调用本方法后，目标房间中的用户将接收到本地用户停止发布 OnUserUnPublishStream{@link #IRTCAudioRoomEventHandler#OnUserUnPublishStream}  和退房 OnUserLeave{@link #IRTCAudioRoomEventHandler#OnUserLeave} 的回调。
     */
     virtual void PauseForwardStreamToAllRooms() = 0;

    /** 
     * @type api
     * @region 多房间
     * @brief 恢复跨房间媒体流转发。
     *        调用 PauseForwardStreamToAllRooms{@link #IRTCAudioRoom#PauseForwardStreamToAllRooms} 暂停转发之后，调用本方法恢复向所有目标房间转发媒体流。
     * @notes <br>
     *        目标房间中的用户将接收到本地用户进房 OnUserJoined{@link #IRTCAudioRoomEventHandler#OnUserJoined} 和发布 OnUserPublishStream{@link #IRTCAudioRoomEventHandler#OnUserPublishStream}  的回调。
     */
    virtual void ResumeForwardStreamToAllRooms() = 0;
};

}  // namespace bytertc

