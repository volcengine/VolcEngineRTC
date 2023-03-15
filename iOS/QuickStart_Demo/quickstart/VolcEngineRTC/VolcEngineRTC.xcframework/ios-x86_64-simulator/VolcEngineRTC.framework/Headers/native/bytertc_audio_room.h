/*
 * Copyright (c) 2022 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC Room Interface
 */

#pragma once

#include "bytertc_audio_room_event_handler.h"
#include "rtc/bytertc_audio_defines.h"
#include "rtc/bytertc_range_audio_interface.h"
#include "rtc/bytertc_spatial_audio_interface.h"

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
     * @type api
     * @region 多房间
     * @author shenpengliang
     * @brief 退出并销毁调用 createRTCRoom{@link #IRTCAudio#createRTCRoom} 所创建的房间实例。
     */
    virtual void destroy() = 0;

    /** 
     * @type api
     * @region 多房间
     * @author shenpengliang
     * @brief 创建/加入房间：房间不存在时即创建房间；房间存在时，未加入房间的用户可加入这个房间。  <br>
     *        同一房间内的用户间可以相互通话。  <br>
     *        进房后重复调用无效。  <br>
     * @param [in] token 动态密钥，用于对登录用户进行鉴权验证。  <br>
     *        进入房间需要携带 Token。测试时可使用控制台生成临时 Token，正式上线需要使用密钥 SDK 在您的服务端生成并下发 Token。  <br>
     *       + 使用不同 App ID 的 App 是不能互通的。  <br>
     *       + 请务必保证生成 Token 使用的 App ID 和创建引擎时使用的 App ID 相同，否则会导致加入房间失败。  <br>
     * @param [in] user_info 用户信息，参看 UserInfo{@link #UserInfo}。  <br>
     * @param [in] room_config 房间参数配置，设置房间模式以及是否自动发布或订阅流。具体配置模式参看 AudioRoomConfig{@link #AudioRoomConfig}。  <br>
     * @return  <br>
     *        +  0: 成功  <br>
     *        + -1：room_id / user_info.uid 包含了无效的参数。  <br>
     *        + -2：已经在房间内。接口调用成功后，只要收到返回值为 0 ，且未调用 `leaveRoom` 成功，则再次调用进房接口时，无论填写的房间 ID 和用户 ID 是否重复，均触发此返回值。  <br>
     * @notes  <br>
     *       + 同一个 App ID 的同一个房间内，每个用户的用户 ID 必须是唯一的。如果两个用户的用户 ID 相同，则后进房的用户会将先进房的用户踢出房间，并且先进房的用户会收到 onRoomStateChanged{@link #IRTCAudioRoomEventHandler#onRoomStateChanged} 回调通知，错误类型详见 ErrorCode{@link #ErrorCode} 中的 kErrorCodeDuplicateLogin。  <br>
     *       + 本地用户调用此方法加入房间成功后，会收到 onRoomStateChanged{@link #IRTCAudioRoomEventHandler#onRoomStateChanged} 回调通知。  <br>
     *       + 本地用户调用 setUserVisibility{@link #IRTCAudioRoom#setUserVisibility} 将自身设为可见后加入房间，远端用户会收到 onUserJoined{@link #IRTCAudioRoomEventHandler#onUserJoined}。  <br>
     *       + 用户加入房间成功后，在本地网络状况不佳的情况下，SDK 可能会与服务器失去连接，此时 SDK 将会自动重连。重连成功后，本地会收到 onRoomStateChanged{@link #IRTCAudioRoomEventHandler#onRoomStateChanged} 回调通知。如果加入房间的用户可见，远端用户会收到 onUserJoined{@link #IRTCAudioRoomEventHandler#onUserJoined}。 
     */
    virtual int joinRoom(const char* token, const UserInfo& user_info, const AudioRoomConfig& room_config) = 0;

    /** 
     * @type api
     * @region 多房间
     * @author shenpengliang
     * @brief 离开房间。  <br>
     *        用户调用此方法离开房间，结束通话过程，释放所有通话相关的资源。  <br>
     *        加入房间后，必须调用此方法结束通话，否则无法开始下一次通话。无论当前是否在房间内，都可以调用此方法。重复调用此方法没有负面影响。  <br>
     * @notes  <br>
     *       + 此方法是异步操作，调用返回时并没有真正退出房间。真正退出房间后，本地会收到 onLeaveRoom{@link #IRTCAudioRoomEventHandler#onLeaveRoom} 回调通知。  <br>
     *       + 可见的用户离开房间后，房间内其他用户会收到 onUserLeave{@link #IRTCAudioRoomEventHandler#onUserLeave} 回调通知。  <br>
     *       + 如果调用此方法后立即销毁引擎，SDK 将无法触发 onLeaveRoom{@link #IRTCAudioRoomEventHandler#onLeaveRoom} 回调。
     */
    virtual void leaveRoom() = 0;

    /** 
     * @type api
     * @author shenpengliang
     * @brief 更新 Token。  <br>
     *        用于加入房间的 Token 有一定的有效期。在 Token 过期前 30 秒，会收到 onTokenWillExpire{@link #IRTCAudioRoomEventHandler#onTokenWillExpire} 回调，此时需要重新获取 Token，并调用此方法更新 Token，否则用户将因为 Token 过期被移出房间。 <br>
     *        调用 joinRoom{@link #IRTCAudioRoom#joinRoom} 方法加入房间或断网重连进入房间时，如果 Token 过期或无效，将导致加入房间失败，并会收到 onRoomStateChanged{@link #IRTCAudioRoomEventHandler#onRoomStateChanged} 回调通知，回调错误码为 ErrorCode{@link #ErrorCode} 中的 `ERROR_CODE_INVALID_TOKEN`。此时需要重新获取 Token，并调用此方法更新 Token。 更新 Token 后，SDK 会自动加入房间。 <br>
     * @param token 有效的 Token。  <br>
     *        如果传入的 Token 无效，回调错误码为 ErrorCode{@link #ErrorCode} 中的 `ERROR_CODE_UPDATE_TOKEN_WITH_INVALID_TOKEN`。
     * @return 方法调用结果。  <br>
     *         +  0: 方法调用成功  <br>
     *         + < 0: 方法调用失败  <br>
     * @notes 当 Token 过期时，用户将被移出房间并将收到 OnError{@link #IRTCAudioRoomEventHandler#onError} 回调， `ERROR_CODE_EXPIRED_TOKEN`，此时需要重新获取 Token，并调用 joinRoom{@link #IRTCAudioRoom#joinRoom} 重新加入房间。
     */
    virtual void updateToken(const char* token) = 0;

    /** 
     * @type api
     * @region 多房间
     * @author shenpengliang
     * @brief 设置用户可见性。默认为可见。  <br>
     *        通过对用户可见性进行设置，可以控制用户在房间内的行为：<br>
     *        + 能否发布音频流；  <br>
     *        + 用户自身是否在房间中隐身。
     * @param [in] enable 设置用户是否对房间内其他用户可见：  <br>
     *        + true: 可以被房间中的其他用户感知，且可以在房间内发布和订阅音频流；  <br>
     *        + false: 无法被房间中的其他用户感知，且只能在房间内订阅音频流。
     * @notes  <br>
     *        + 该方法在加入房间前后均可调用。 <br>
     *        + 在房间内调用此方法，房间内其他用户会收到相应的回调通知：<br>
     *            - 从 false 切换至 true 时，房间内其他用户会收到 onUserJoined{@link #IRTCAudioRoomEventHandler#onUserJoined} 回调通知；  <br>
     *            - 从 true 切换至 false 时，房间内其他用户会收到 onUserLeave{@link #IRTCAudioRoomEventHandler#onUserLeave} 回调通知。 <br>
     *        + 若调用该方法将可见性设为 false，此时尝试发布流会收到 onWarning{@link #IRTCAudioEventHandler#onWarning} 警告，具体原因参看 WarningCode{@link #WarningCode} 中的 kWarningCodePublishStreamForbiden 警告码。
     */
    virtual void setUserVisibility(bool enable) = 0;

    /** 
     * @type api
     * @region 多房间
     * @author shenpengliang
     * @brief 设置 IRTCAudioRoom{@link #IRTCAudioRoom} 对象的事件句柄。
     *        通过设置事件句柄可以监听此 IRTCAudioRoom{@link #IRTCAudioRoom} 对象对应的房间的回调事件。
     * @param [in] room_event_handler 回调处理器，详见 IRTCAudioRoomEventHandler{@link #IRTCAudioRoomEventHandler}
     */
    virtual void setRTCRoomEventHandler(IRTCAudioRoomEventHandler* room_event_handler) = 0;

    /** 
     * @type api
     * @region 多房间
     * @author hanchenchen.c
     * @brief 给房间内指定的用户发送文本消息（P2P）
     * @param [in] user_id  <br>
     *        消息接收用户的 ID
     * @param [in] message  <br>
     *        发送的文本消息内容。  <br>
     *        消息不超过 64 KB。
     * @param [in] config   <br>
     *        消息发送的可靠/有序类型，参看 MessageConfig{@link #MessageConfig}  <br>
     * @return 这次发送消息的编号，从 1 开始递增。
     * @notes  <br>
     *       + 在发送房间内文本消息前，必须先调用 joinRoom{@link #IRTCAudioRoom#joinRoom} 加入房间。  <br>
     *       + 调用该函数后会收到一次 onUserMessageSendResult{@link #IRTCAudioRoomEventHandler#onUserMessageSendResult} 回调，通知消息发送方发送成功或失败；  <br>
     *       + 若文本消息发送成功，则 user_id 所指定的用户会收到 onUserMessageReceived{@link #IRTCAudioRoomEventHandler#onUserMessageReceived} 回调。
     */
    virtual int64_t sendUserMessage(const char* user_id, const char* message, MessageConfig config) = 0;

    /** 
     * @type api
     * @region 多房间
     * @author hanchenchen.c
     * @brief 给房间内指定的用户发送二进制消息（P2P）
     * @param [in] user_id  <br>
     *        消息接收用户的 ID
     * @param [in] length   <br>
     *        二进制字符串的长度。
     * @param [in] message   <br>
     *        二进制消息的内容。
     *        消息不超过 64KB。
     * @param [in] config   <br>
     *        消息发送的可靠/有序类型，参看 MessageConfig{@link #MessageConfig}  <br>
     * @return 这次发送消息的编号，从 1 开始递增。
     * @notes  <br>
     *       + 在发送房间内二进制消息前，必须先调用 joinRoom{@link #IRTCAudioRoom#joinRoom} 加入房间。  <br>
     *       + 调用该函数后会收到一次 onUserMessageSendResult{@link #IRTCAudioRoomEventHandler#onUserMessageSendResult} 回调，通知消息发送方发送成功或失败；  <br>
     *       + 若二进制消息发送成功，则 user_id 所指定的用户会收到 onUserBinaryMessageReceived{@link #IRTCAudioRoomEventHandler#onUserBinaryMessageReceived} 回调。
     */
    virtual int64_t sendUserBinaryMessage(const char* user_id, int length, const uint8_t* message, MessageConfig config) = 0;

    /** 
     * @type api
     * @region 多房间
     * @author hanchenchen.c
     * @brief 给房间内的所有其他用户群发文本消息。
     * @param [in] message  <br>
     *        用户发送的广播消息  <br>
     *        消息不超过 64 KB。
     * @return 这次发送消息的编号，从 1 开始递增。
     * @notes  <br>
     *       + 在发送房间内二进制消息前，必须先调用 joinRoom{@link #IRTCAudioRoom#joinRoom} 加入房间。  <br>
     *       + 调用该函数后，会收到一次 onRoomMessageSendResult{@link #IRTCAudioRoomEventHandler#onRoomMessageSendResult} 回调。  <br>
     *       + 同一房间内的其他用户会收到 onRoomMessageReceived{@link #IRTCAudioRoomEventHandler#onRoomMessageReceived} 回调。
     */
    virtual int64_t sendRoomMessage(const char* message) = 0;
    /** 
     * @type api
     * @region 多房间
     * @author hanchenchen.c
     * @brief 给房间内的所有其他用户群发二进制消息。
     * @param [in] size  <br>
     *        发送的二进制消息长度
     * @param [in] message  <br>
     *        用户发送的二进制广播消息  <br>
     *        消息不超过 64KB。
     * @return 这次发送消息的编号，从 1 开始递增。
     * @notes  <br>
     *       + 在发送房间内二进制消息前，必须先调用 joinRoom{@link #IRTCAudioRoom#joinRoom} 加入房间。  <br>
     *       + 调用该函数后，会收到一次 onRoomMessageSendResult{@link #IRTCAudioRoomEventHandler#onRoomMessageSendResult} 回调。  <br>
     *       + 同一房间内的其他用户会收到 onRoomBinaryMessageReceived{@link #IRTCAudioRoomEventHandler#onRoomBinaryMessageReceived} 回调。
     */
    virtual int64_t sendRoomBinaryMessage(int size, const uint8_t* message) = 0;

    /** 
     * @type api
     * @region 房间管理
     * @author shenpengliang
     * @brief 在当前所在房间内发布本地麦克风采集的音频流
     * @notes <br>
     *        + 如果你已经在用户进房时通过调用 joinRoom{@link #IRTCAudioRoom#joinroom} 成功选择了自动发布，则无需再调用本接口。<br>
     *        + 调用 setUserVisibility{@link #IRTCAudioRoom#setUserVisibility} 方法将自身设置为不可见后无法调用该方法，需将自身切换至可见后方可调用该方法发布音频流。 <br>
     *        + 如果你需要向多个房间发布流，调用 startForwardStreamToRooms{@link #IRTCAudioRoom#startForwardStreamToRooms}。  <br>
     *        + 调用此方法后，房间中的所有远端用户会收到 onUserPublishStream{@link #IRTCAudioRoomEventHandler#onUserPublishStream} 回调通知，其中成功收到了音频流的远端用户会收到 onFirstRemoteAudioFrame{@link #IRTCAudioEventHandler#onFirstRemoteAudioFrame} 回调。<br>
     *        + 调用 unpublishStream{@link #IRTCAudioRoom#unpublishStream} 取消发布。
     */
    virtual void publishStream() = 0;

    /** 
     * @type api
     * @region 房间管理
     * @author shenpengliang
     * @brief 停止将本地麦克风采集的音频流发布到当前所在房间中
     * @notes  <br>
     *        + 调用 publishStream{@link #IRTCAudioRoom#publishStream} 手动发布麦克风音频流后，你需调用此接口停止发布。<br>
     *        + 调用此方法停止发布音频流后，房间中的其他用户将会收到 onUserUnPublishStream{@link #IRTCAudioRoomEventHandler#onUserUnPublishStream} 回调通知。
     */
    virtual void unpublishStream() = 0;

    /** 
     * @type api
     * @region 房间管理
     * @author liuzhiqiang
     * @brief 订阅房间内指定的通过麦克风采集的音频流。  <br>
     *        该方法对自动订阅和手动订阅模式均适用。
     * @param [in] user_id 指定订阅的远端发布音频流的用户 ID。
     * @notes  <br>
     *        + 你必须先通过 onUserPublishStream{@link #IRTCAudioRoomEventHandler#onUserPublishStream} 回调获取当前房间里的远端音频流信息，然后调用本方法按需订阅。  <br>
     *        + 成功订阅远端用户的媒体流后，订阅关系将持续到调用 unsubscribeStream{@link #IRTCAudioRoom#unsubscribeStream} 取消订阅或本端用户退房。 <br>
     *        + 关于其他调用异常，你会收到 onStreamStateChanged{@link #IRTCAudioRoomEventHandler#onStreamStateChanged} 回调通知，具体异常原因参看 ErrorCode{@link #ErrorCode}。
     */
    virtual void subscribeStream(const char* user_id) = 0;

    /** 
     * @type api
     * @region 房间管理
     * @author liuzhiqiang
     * @brief 取消订阅房间内指定的通过麦克风采集的音频流。  <br>
     *        该方法对自动订阅和手动订阅模式均适用。
     * @param userId 指定取消订阅的远端发布音频流的用户 ID。
     * @notes  <br>
     *        + 关于其他调用异常，你会收到 onStreamStateChanged{@link #IRTCAudioRoomEventHandler#onStreamStateChanged} 回调通知，具体失败原因参看 ErrorCode{@link #ErrorCode}。
     */
    virtual void unsubscribeStream(const char* user_id) = 0;

    /** 
     * @type api
     * @region 多房间
     * @author shenpengliang
     * @brief 暂停接收来自远端的音频流。
     * @notes  <br>
     *        + 该方法仅暂停远端流的接收，并不影响远端流的采集和发送；  <br>
     *        + 该方法不改变用户的订阅状态以及订阅流的属性。  <br>
     *        + 若想恢复接收远端流，需调用 resumeAllSubscribedStream{@link #IRTCAudioRoom#resumeAllSubscribedStream}。 <br>
     *        + 多房间场景下，仅暂停接收发布在当前所在房间的流。
     */
    virtual void pauseAllSubscribedStream() = 0;

    /** 
     * @type api
     * @region 多房间
     * @author shenpengliang
     * @brief 恢复接收来自远端的音频流
     * @notes <br>
     *        + 该方法仅恢复远端流的接收，并不影响远端流的采集和发送；  <br>
     *        + 该方法不改变用户的订阅状态以及订阅流的属性。
     */
    virtual void resumeAllSubscribedStream() = 0;

    /** 
     * @type api
     * @region 多房间
     * @author wunailiang
     * @brief 开始跨房间转发音频流。
     *        在用户进入房间后调用本接口，实现向多个房间转发音频流，适用于跨房间连麦等场景。<br>
     * @param [in] configuration 跨房间音频流转发指定房间的信息。参看 ForwardStreamConfiguration{@link #ForwardStreamConfiguration}。
     * @return  <br>
     *        0: 方法调用成功  <br>
     *        <0: 方法调用失败  <br>
     * @notes <br>
     *        + 调用本方法后，将在本端触发 onForwardStreamStateChanged{@link #IRTCAudioRoomEventHandler#onForwardStreamStateChanged} 回调。
     *        + 调用本方法后，你可以通过监听 onForwardStreamEvent{@link #IRTCAudioRoomEventHandler#onForwardStreamEvent} 回调来获取各个目标房间在转发音频流过程中的相关事件。
     *        + 开始转发后，目标房间中的用户将接收到本地用户进房 onUserJoined{@link #IRTCAudioRoomEventHandler#onUserJoined} 和发流 onUserPublishStream{@link #IRTCAudioRoomEventHandler#onUserPublishStream}  的回调。
     *        + 调用本方法后，可以调用 updateForwardStreamToRooms{@link #IRTCAudioRoom#updateForwardStreamToRooms} 更新目标房间信息，例如，增加或减少目标房间等。
     *        + 调用本方法后，可以调用 stopForwardStreamToRooms{@link #IRTCAudioRoom#stopForwardStreamToRooms} 停止向所有房间转发音频流。
     *        + 调用本方法后，可以调用 pauseForwardStreamToAllRooms{@link #IRTCAudioRoom#pauseForwardStreamToAllRooms} 暂停向所有房间转发音频流。
     */
    virtual int startForwardStreamToRooms(const ForwardStreamConfiguration& configuration) = 0;

    /** 
     * @type api
     * @region 房间管理
     * @author wunailiang
     * @brief 更新跨房间音频流转发信息。<br>
     *        通过 startForwardStreamToRooms{@link #IRTCAudioRoom#startForwardStreamToRooms} 发起音频流转发后，可调用本方法增加或者减少目标房间，或更新房间密钥。
     *        调用本方法增加或删减房间后，将在本端触发 onForwardStreamStateChanged{@link #IRTCAudioRoomEventHandler#onForwardStreamStateChanged} 回调，包含发生了变动的目标房间中音频流转发状态。
     * @param [in] configuration 跨房间音频流转发目标房间信息。参看 ForwardStreamConfiguration{@link #ForwardStreamConfiguration}。
     * @return  <br>
     *        0: 方法调用成功  <br>
     *        <0: 方法调用失败  <br>
     * @notes <br>
     *        + 增加目标房间后，新增目标房间中的用户将接收到本地用户进房 onUserJoined{@link #IRTCAudioRoomEventHandler#onUserJoined} 和发布 onUserPublishStream{@link #IRTCAudioRoomEventHandler#onUserPublishStream}  的回调。
     *        + 删减目标房间后，原目标房间中的用户将接收到本地用户停止发布 onUserUnPublishStream{@link #IRTCAudioRoomEventHandler#onUserUnPublishStream}  和退房 onUserLeave{@link #IRTCAudioRoomEventHandler#onUserLeave} 的回调。
     */
    virtual int updateForwardStreamToRooms(const ForwardStreamConfiguration& configuration) = 0;

    /** 
     * @type api
     * @region 多房间
     * @author wunailiang
     * @brief 停止跨房间音频流转发。
     *        通过 startForwardStreamToRooms{@link #IRTCAudioRoom#startForwardStreamToRooms} 发起音频流转发后，可调用本方法停止向所有目标房间转发音频流。
     * @notes <br>
     *        + 调用本方法后，将在本端触发 onForwardStreamStateChanged{@link #IRTCAudioRoomEventHandler#onForwardStreamStateChanged} 回调。
     *        + 调用本方法后，原目标房间中的用户将接收到本地用户停止发布 onUserUnPublishStream{@link #IRTCAudioRoomEventHandler#onUserUnPublishStream}  和退房 onUserLeave{@link #IRTCAudioRoomEventHandler#onUserLeave} 的回调。
     *        + 如果需要停止向指定的房间转发音频流，请调用 updateForwardStreamToRooms{@link #IRTCAudioRoom#updateForwardStreamToRooms} 更新房间信息。
     *        + 如果需要暂停转发，请调用 pauseForwardStreamToAllRooms{@link #IRTCAudioRoom#pauseForwardStreamToAllRooms}，并在之后随时调用 resumeForwardStreamToAllRooms{@link #IRTCAudioRoom#resumeForwardStreamToAllRooms} 快速恢复转发。
     */
    virtual void stopForwardStreamToRooms() = 0;

    /** 
     * @type api
     * @region 多房间
     * @author wunailiang
     * @brief 暂停跨房间音频流转发。
     *        通过 startForwardStreamToRooms{@link #IRTCAudioRoom#startForwardStreamToRooms} 发起音频流转发后，可调用本方法暂停向所有目标房间转发音频流。
     *        调用本方法暂停向所有目标房间转发后，你可以随时调用 resumeForwardStreamToAllRooms{@link #IRTCAudioRoom#resumeForwardStreamToAllRooms} 快速恢复转发。
     * @notes 调用本方法后，目标房间中的用户将接收到本地用户停止发布 onUserUnPublishStream{@link #IRTCAudioRoomEventHandler#onUserUnPublishStream}  和退房 onUserLeave{@link #IRTCAudioRoomEventHandler#onUserLeave} 的回调。
     */
     virtual void pauseForwardStreamToAllRooms() = 0;

    /** 
     * @type api
     * @region 多房间
     * @author wunailiang
     * @brief 恢复跨房间音频流转发。
     *        调用 pauseForwardStreamToAllRooms{@link #IRTCAudioRoom#pauseForwardStreamToAllRooms} 暂停转发之后，调用本方法恢复向所有目标房间转发音频流。
     * @notes <br>
     *        目标房间中的用户将接收到本地用户进房 onUserJoined{@link #IRTCAudioRoomEventHandler#onUserJoined} 和发布 onUserPublishStream{@link #IRTCAudioRoomEventHandler#onUserPublishStream}  的回调。
     */
    virtual void resumeForwardStreamToAllRooms() = 0;
    /** 
     * @type api
     * @region 范围语音
     * @author chuzhongtao
     * @brief 获取范围语音接口实例。
     * @return 方法调用结果： <br>
     *        + IRangeAudio：成功，返回一个 IRangeAudio{@link #IRangeAudio} 实例。  <br>
     *        + nullptr：失败，当前 SDK 不支持范围语音功能。
     * @notes 首次调用该方法须在创建房间后、加入房间前。范围语音相关 API 和调用时序详见[范围语音](https://www.volcengine.com/docs/6348/114727)。 
     */
    virtual IRangeAudio* getRangeAudio() = 0;

    /** 
     * @type api
     * @region 空间音频
     * @author majun.lvhiei
     * @brief 获取空间音频接口实例。  <br>
     * @return 方法调用结果：  <br>
     *        + ISpatialAudio：成功，返回一个 ISpatialAudio{@link #ISpatialAudio} 实例。  <br>
     *        + nullptr：失败，当前 SDK 不支持空间音频功能。
     * @notes  <br>
     *        + 首次调用该方法须在创建房间后、加入房间前。 空间音频相关 API 和调用时序详见[空间音频](https://www.volcengine.com/docs/6348/93903)。 <br>
     *        + 只有在使用支持真双声道播放的设备时，才能开启空间音频效果；  <br>
     *        + 机型性能不足可能会导致音频卡顿，使用低端机时，不建议开启空间音频效果；  <br>
     *        + SDK 最多支持 30 个用户同时开启空间音频功能。
     */
    virtual ISpatialAudio* getSpatialAudio() = 0;
};

}  // namespace bytertc
