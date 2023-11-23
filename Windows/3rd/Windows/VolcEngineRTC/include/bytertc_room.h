/*
 * Copyright (c) 2020 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC Room Interface
 */

#pragma once

#ifndef BYTE_RTC_ROOM_INTERFACE_H__
#define BYTE_RTC_ROOM_INTERFACE_H__

#include "rtc/bytertc_video_effect_interface.h"  // NOLINT
#include "rtc/bytertc_defines.h"
#include "bytertc_room_event_handler.h"
#include "rtc/bytertc_transcoder_interface.h"
#include "rtc/bytertc_publicstream_interface.h"
#include "rtc/bytertc_range_audio_interface.h"
#include "rtc/bytertc_spatial_audio_interface.h"
#include "rtc/bytertc_panoramic_video_interface.h"
namespace bytertc {

/** 
 * @type api
 * @brief 房间接口
 */
class IRTCRoom {
public:
    /** 
     * @hidden constructor/destructor
     * @brief 析构函数
     */
    virtual ~IRTCRoom() {
    }

    /** 
     * @type api
     * @region 多房间
     * @brief 退出并销毁调用 createRTCRoom{@link #IRTCVideo#createRTCRoom} 所创建的房间实例。
     */
    virtual void destroy() = 0;

    /** 
     * @type api
     * @region 多房间
     * @brief 设置用户可见性。未调用该接口前，本地用户默认对他人可见。
     * @param [in] enable 设置用户是否对房间内其他用户可见：  <br>
     *        + true: 可见，用户可以在房间内发布音视频流，房间中的其他用户将收到用户的行为通知，例如进房、开启视频采集和退房。
     *        + false: 不可见，用户不可以在房间内发布音视频流，房间中的其他用户不会收到用户的行为通知，例如进房、开启视频采集和退房。
     * @return  <br>
     *        + 0: 调用成功。
     *        + < 0: 调用失败。参看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明。
     * @notes  <br>
     *       + 在加入房间前后，用户均可调用此方法设置用户可见性。
     *       + 设置用户可见性，会收到设置成功/失败回调 onUserVisibilityChanged{@link #IRTCRoomEventHandler#onUserVisibilityChanged}。（v3.54 新增）
     *   &#x0020;  • 在加入房间前设置用户可见性，若设置的可见性与默认值不同，将在加入房间时触发本回调。
     *   &#x0020;  • 在加入房间后设置用户可见性，若可见性前后不同，会触发本回调。
     *   &#x0020;  • 在断网重连后，若可见性发生改变，会触发本回调。
     *       + 在房间内，调用此方法成功切换用户可见性后，房间内其他用户会收到相应的回调。
     *   &#x0020;  • 从可见换至不可见时，房间内其他用户会收到 onUserLeave{@link #IRTCRoomEventHandler#onUserLeave}。
     *   &#x0020;  • 从不可见切换至可见时，房间内其他用户会收到 onUserJoined{@link #IRTCRoomEventHandler#onUserJoined}。
     *   &#x0020;  • 若调用该方法将可见性设为 `false`，此时尝试发布流会收到 `kWarningCodePublishStreamForbiden` 警告。
     */
    virtual int setUserVisibility(bool enable) = 0;

    /** 
     * @type api
     * @region 多房间
     * @brief 通过设置 IRTCRoom{@link #IRTCRoom} 对象的事件句柄，监听此对象对应的回调事件。
     * @param [in] room_event_handler 参见 IRTCRoomEventHandler{@link #IRTCRoomEventHandler}
     * @return  <br>
     *        + 0: 调用成功。
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     */
    virtual int setRTCRoomEventHandler(IRTCRoomEventHandler* room_event_handler) = 0;

    /** 
     * @type api
     * @region 多房间
     * @brief 创建/加入房间：房间不存在时即创建房间；房间存在时，未加入房间的用户可加入这个房间。  <br>
     *        同一房间内的用户间可以相互通话。  <br>
     * @param [in] token 动态密钥，用于对登录用户进行鉴权验证。  <br>
     *        进入房间需要携带 Token。测试时可使用控制台生成临时 Token，正式上线需要使用密钥 SDK 在您的服务端生成并下发 Token。Token 有效期及生成方式参看[使用 Token 完成鉴权](70121)。  <br>
     *       + 使用不同 App ID 的 App 是不能互通的。  <br>
     *       + 请务必保证生成 Token 使用的 App ID 和创建引擎时使用的 App ID 相同，否则会导致加入房间失败。具体失败原因会通过 onRoomStateChanged{@link #IRTCRoomEventHandler#onRoomStateChanged} 回调告知。  <br>
     * @param [in] user_info 用户信息，参看 UserInfo{@link #UserInfo}。  <br>
     * @param [in] config 房间参数配置，设置房间模式以及是否自动发布或订阅流。具体配置模式参看 RTCRoomConfig{@link #RTCRoomConfig}。  <br>
     * @return  <br>
     *        +  0: 成功  <br>
     *        + -1：room_id / user_info.uid 包含了无效的参数。  <br>
     *        + -2：已经在房间内。接口调用成功后，只要收到返回值为 0 ，且未调用 leaveRoom:{@link #IRTCRoom#leaveRoom} 成功，则再次调用进房接口时，无论填写的房间 ID 和用户 ID 是否重复，均触发此返回值。  <br>
     * @notes  <br>
     *       + 同一个 App ID 的同一个房间内，每个用户的用户 ID 必须是唯一的。如果两个用户的用户 ID 相同，则后进房的用户会将先进房的用户踢出房间，并且先进房的用户会收到 onRoomStateChanged{@link #IRTCRoomEventHandler#onRoomStateChanged} 回调通知，错误类型详见 ErrorCode{@link #ErrorCode} 中的 kErrorCodeDuplicateLogin。  <br>
     *       + 本地用户调用此方法加入房间成功后，会收到 onRoomStateChanged{@link #IRTCRoomEventHandler#onRoomStateChanged} 回调通知。若本地用户同时为可见用户，加入房间时远端用户会收到 onUserJoined{@link #IRTCRoomEventHandler#onUserJoined} 回调通知。关于可见性设置参看 setUserVisibility{@link #IRTCRoom#setUserVisibility}。  <br>
     *       + 用户加入房间成功后，在本地网络状况不佳的情况下，SDK 可能会与服务器失去连接，并触发 onConnectionStateChanged{@link #IRTCVideoEventHandler#onConnectionStateChanged} 回调。此时 SDK 会自动重试，直到成功重连。重连成功后，本地会收到 onRoomStateChanged{@link #IRTCRoomEventHandler#onRoomStateChanged} 回调通知。
     */
    virtual int joinRoom(const char* token, const UserInfo& user_info, const RTCRoomConfig& config) = 0;

    /** 
     * @type api
     * @region 多房间
     * @brief 离开房间。  <br>
     *        用户调用此方法离开房间，结束通话过程，释放所有通话相关的资源。  <br>
     *        加入房间后，必须调用此方法结束通话，否则无法开始下一次通话。无论当前是否在房间内，都可以调用此方法。重复调用此方法没有负面影响。  <br>
     *        此方法是异步操作，调用返回时并没有真正退出房间。真正退出房间后，本地会收到 onLeaveRoom{@link #IRTCRoomEventHandler#onLeaveRoom} 回调通知。  <br>
     * @return  <br>
     *        + 0: 调用成功。
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @notes  <br>
     *       + 可见的用户离开房间后，房间内其他用户会收到 onUserLeave{@link #IRTCRoomEventHandler#onUserLeave} 回调通知。  <br>
     *       + 如果调用此方法后立即销毁引擎，SDK 将无法触发 onLeaveRoom{@link #IRTCRoomEventHandler#onLeaveRoom} 回调。  <br>
     */
    virtual int leaveRoom() = 0;

    /** 
     * @type api
     * @brief 更新 Token。
     *        Token 中同时包含进房、发布和订阅权限，各权限有一定的有效期，并且到期前 30 秒会触发回调，提示用户更新 Token 相关权限。此时需要重新获取 Token，并调用此方法更新 Token，以保证通话的正常进行。
     * @param [in] token 重新获取的有效 Token。
     *        如果传入的 Token 无效，回调错误码为 ErrorCode{@link #ErrorCode} 中的 `-1010`。
     * @return 方法调用结果：
     *        + 0：成功；
     *        + <0：失败。具体失败原因参看 ReturnStatus{@link #ReturnStatus}。
     * @notes <br>
     *      + 3.50（不含）以前的版本中，Token 中的发布和订阅权限为保留参数，无实际控制权限；3.50 及以后版本开放 Token 发布订阅控制权限，如需通过 Token 控制连麦权限，请联系技术支持团队开通白名单后支持。
     *      + 请勿同时调用 updateToken{@link #IRTCRoom#updateToken} 和 joinRoom{@link #IRTCRoom#joinRoom} 方法更新 Token。若因 Token 过期或无效导致加入房间失败或已被移出房间，你应该在获取新的有效 Token 后调用 joinRoom{@link #IRTCRoom#joinRoom} 重新加入房间。
     */
    virtual int updateToken(const char* token) = 0;

    /** 
     * @type api
     * @region 多房间
     * @brief 给房间内指定的用户发送点对点文本消息（P2P）。
     * @param [in] uid  <br>
     *        消息接收用户的 ID
     * @param [in] message  <br>
     *        发送的文本消息内容。  <br>
     *        消息不超过 64 KB。
     * @param [in] config 消息类型，参看 MessageConfig{@link #MessageConfig}。
     * @return 这次发送消息的编号，从 1 开始递增。
     * @notes  <br>
     *       + 在发送房间内文本消息前，必须先调用 joinRoom{@link #IRTCRoom#joinRoom} 加入房间。  <br>
     *       + 调用该函数后会收到一次 onUserMessageSendResult{@link #IRTCRoomEventHandler#onUserMessageSendResult} 回调，通知消息发送方发送成功或失败；  <br>
     *       + 若文本消息发送成功，则 uid 所指定的用户会收到 onUserMessageReceived{@link #IRTCRoomEventHandler#onUserMessageReceived} 回调。
     */
    virtual int64_t sendUserMessage(const char* uid, const char* message, MessageConfig config = kMessageConfigReliableOrdered) = 0;

    /** 
     * @type api
     * @region 多房间
     * @brief 给房间内指定的用户发送点对点二进制消息（P2P）。
     * @param [in] uid  <br>
     *        消息接收用户的 ID
     * @param [in] length   <br>
     *        二进制字符串的长度。
     * @param [in] message   <br>
     *        二进制消息的内容。
     *        消息不超过 46KB。
     * @param [in] config 消息类型，参看 MessageConfig{@link #MessageConfig}。
     * @return 这次发送消息的编号，从 1 开始递增。
     * @notes  <br>
     *       + 在发送房间内二进制消息前，必须先调用 joinRoom{@link #IRTCRoom#joinRoom} 加入房间。  <br>
     *       + 调用该函数后会收到一次 onUserMessageSendResult{@link #IRTCRoomEventHandler#onUserMessageSendResult} 回调，通知消息发送方发送成功或失败；  <br>
     *       + 若二进制消息发送成功，则 uid 所指定的用户会收到 onUserBinaryMessageReceived{@link #IRTCRoomEventHandler#onUserBinaryMessageReceived} 回调。
     */
    virtual int64_t sendUserBinaryMessage(const char* uid, int length, const uint8_t* message, MessageConfig config = kMessageConfigReliableOrdered) = 0;

    /** 
     * @type api
     * @region 多房间
     * @brief 给房间内的所有其他用户群发文本消息。
     * @param [in] message  <br>
     *        用户发送的广播消息  <br>
     *        消息不超过 64 KB。
     * @notes  <br>
     *       + 在发送房间内二进制消息前，必须先调用 joinRoom{@link #IRTCRoom#joinRoom} 加入房间。  <br>
     *       + 调用该函数后，会收到一次 onRoomMessageSendResult{@link #IRTCRoomEventHandler#onRoomMessageSendResult} 回调。  <br>
     *       + 同一房间内的其他用户会收到 onRoomMessageReceived{@link #IRTCRoomEventHandler#onRoomMessageReceived} 回调。
     */
    virtual int64_t sendRoomMessage(const char* message) = 0;
    /** 
     * @type api
     * @region 多房间
     * @brief 给房间内的所有其他用户群发二进制消息。
     * @param [in] size  <br>
     *        发送的二进制消息长度
     * @param [in] message  <br>
     *        用户发送的二进制广播消息  <br>
     *        消息不超过 46KB。
     * @return 这次发送消息的编号，从 1 开始递增。
     * @notes  <br>
     *       + 在发送房间内二进制消息前，必须先调用 joinRoom{@link #IRTCRoom#joinRoom} 加入房间。  <br>
     *       + 调用该函数后，会收到一次 onRoomMessageSendResult{@link #IRTCRoomEventHandler#onRoomMessageSendResult} 回调。  <br>
     *       + 同一房间内的其他用户会收到 onRoomBinaryMessageReceived{@link #IRTCRoomEventHandler#onRoomBinaryMessageReceived} 回调。
     */
    virtual int64_t sendRoomBinaryMessage(int size, const uint8_t* message) = 0;

    /** 
     * @type api
     * @region 房间管理
     * @brief 在当前所在房间内发布本地通过摄像头/麦克风采集的媒体流
     * @param [in] type 媒体流类型，用于指定发布音频/视频，参看 MediaStreamType{@link #MediaStreamType}
     * @return  <br>
     *        + 0: 调用成功。
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @notes <br>
     *        + 如果你已经在用户进房时通过调用 joinRoom{@link #IRTCRoom#joinRoom} 成功选择了自动发布，则无需再调用本接口。<br>
     *        + 调用 setUserVisibility{@link #IRTCRoom#setUserVisibility} 方法将自身设置为不可见后无法调用该方法，需将自身切换至可见后方可调用该方法发布摄像头音视频流。 <br>
     *        + 如果你需要发布屏幕共享流，调用 publishScreen{@link #IRTCRoom#publishScreen}。(Linux 不适用)<br>
     *        + 如果你需要向多个房间发布流，调用 startForwardStreamToRooms{@link #IRTCRoom#startForwardStreamToRooms}。  <br>
     *        + 调用此方法后，房间中的所有远端用户会收到 onUserPublishStream{@link #IRTCRoomEventHandler#onUserPublishStream} 回调通知，其中成功收到了音频流的远端用户会收到 onFirstRemoteAudioFrame{@link #IRTCVideoEventHandler#onFirstRemoteAudioFrame} 回调，订阅了视频流的远端用户会收到 onFirstRemoteVideoFrameDecoded{@link #IRTCVideoEventHandler#onFirstRemoteVideoFrameDecoded} 回调。<br>
     *        + 调用 unpublishStream{@link #IRTCRoom#unpublishStream} 取消发布。
     */
    virtual int publishStream(MediaStreamType type) = 0;

    /** 
     * @type api
     * @region 房间管理
     * @brief 停止将本地摄像头/麦克风采集的媒体流发布到当前所在房间中
     * @param [in] type 媒体流类型，用于指定停止发布音频/视频，参看 MediaStreamType{@link #MediaStreamType}
     * @return  <br>
     *        + 0: 调用成功。
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @notes  <br>
     *        + 调用 publishStream{@link #IRTCRoom#publishStream} 手动发布摄像头音视频流后，你需调用此接口停止发布。<br>
     *        + 调用此方法停止发布音视频流后，房间中的其他用户将会收到 onUserUnpublishStream{@link #IRTCRoomEventHandler#onUserUnpublishStream} 回调通知。
     */
    virtual int unpublishStream(MediaStreamType type) = 0;

    /** 
     * @type api
     * @region 屏幕共享
     * @brief 在当前所在房间内手动发布本地屏幕共享音视频流。<br>
     *        如果你需要手动向多个房间发布屏幕共享流，可以使用同样的 uid 加入多个房间，并在每个房间调用该方法。同时，你可以在不同的房间发布不同的屏幕共享流类型。
     * @param [in] type 媒体流类型，用于指定发布屏幕音频/视频，参看 MediaStreamType{@link #MediaStreamType}。
     * @return  <br>
     *        + 0: 调用成功。
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @notes <br>
     *        + 即使你已经在用户进房时通过调用 joinRoom{@link #IRTCRoom#joinRoom} 成功选择了自动发布，也需要调用本接口。<br>
     *        + 调用 setUserVisibility{@link #IRTCRoom#setUserVisibility} 方法将自身设置为不可见后无法调用该方法，需将自身切换至可见后方可调用该方法发布屏幕流。 <br>
     *        + 调用该方法后，房间中的所有远端用户会收到 onUserPublishScreen{@link #IRTCRoomEventHandler#onUserPublishScreen} 回调，其中成功收到音频流的远端用户会收到 onFirstRemoteAudioFrame{@link #IRTCVideoEventHandler#onFirstRemoteAudioFrame} 回调，订阅了视频流的远端用户会收到 onFirstRemoteVideoFrameDecoded{@link #IRTCVideoEventHandler#onFirstRemoteVideoFrameDecoded} 回调。<br>
     *        + 调用该方法后，本地用户会收到 onScreenVideoFrameSendStateChanged{@link #IRTCVideoEventHandler#onScreenVideoFrameSendStateChanged}。<br>
     *        + 调用 unpublishScreen{@link #IRTCRoom#unpublishScreen} 取消发布。 <br>
     *        + 对 Linux，仅支持发布视频流。<br>
     *        + 查看 [PC 端屏幕共享](https://www.volcengine.com/docs/6348/70144)，获取更多信息。
     */
    virtual int publishScreen(MediaStreamType type) = 0;

    /** 
     * @type api
     * @region 屏幕共享
     * @brief 停止将本地屏幕共享音视频流发布到当前所在房间中
     * @param [in] type 媒体流类型，用于指定停止发布屏幕音频/视频，参看 MediaStreamType{@link #MediaStreamType}
     * @return  <br>
     *        + 0: 调用成功。
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @notes <br>
     *        + 调用 publishScreen{@link #IRTCRoom#publishScreen} 发布屏幕流后，你需调用此接口停止发布。 <br>
     *        + 调用此方法停止发布屏幕音视频流后，房间中的其他用户将会收到 onUserUnpublishScreen{@link #IRTCRoomEventHandler#onUserUnpublishScreen} 回调。
     */
    virtual int unpublishScreen(MediaStreamType type) = 0;

    /** 
     * @deprecated since 3.36 and will be deleted in 3.51, use subscribeStream{@link #IRTCRoom#subscribeStream}, unsubscribeStream{@link #IRTCRoom#unsubscribeStream}, subscribeScreen{@link #IRTCRoom#subscribeScreen} and unsubscribeScreen{@link #IRTCRoom#unsubscribeScreen} instead.
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
     *        + 若订阅失败，你会收到 onStreamStateChanged{@link #IRTCRoomEventHandler#onStreamStateChanged} 回调通知，具体失败原因参看 ErrorCode{@link #ErrorCode}。
     *        + 若调用 pauseAllSubscribedStream{@link #IRTCRoom#pauseAllSubscribedStream} 暂停接收远端音视频流，此时仍可使用该方法对暂停接收的流进行设置，你会在调用 resumeAllSubscribedStream{@link #IRTCRoom#resumeAllSubscribedStream} 恢复接收流后收到修改设置后的流。  <br>
     */
    BYTERTC_DEPRECATED virtual int subscribeUserStream(const char* user_id, StreamIndex stream_type, SubscribeMediaType media_type, const SubscribeVideoConfig& video_config) = 0;
    /** 
     * @type api
     * @region 视频管理
     * @brief 设置期望订阅的远端视频流的参数。
     * @param [in] user_id 期望配置订阅参数的远端视频流发布用户的 ID。
     * @param [in] remote_video_config 期望配置的远端视频流参数，参看 RemoteVideoConfig{@link #RemoteVideoConfig}。
     * @return 方法调用结果：
     *        + 0：成功；
     *        + <0：失败。具体失败原因参看 ReturnStatus{@link #ReturnStatus}。
     * @notes <br>
     *        + 若使用 342 及以前版本的 SDK，调用该方法前请联系技术支持人员开启按需订阅功能。  <br>
     *        + 该方法仅在发布端调用 enableSimulcastMode{@link #IRTCVideo#enableSimulcastMode} 开启了发送多路视频流的情况下生效，此时订阅端将收到来自发布端与期望设置的参数最相近的一路流；否则订阅端只会收到一路参数为分辨率 640px × 360px、帧率 15fps 的视频流。  <br>
     *        + 若发布端开启了推送多路流功能，但订阅端不对流参数进行设置，则默认接受发送端设置的分辨率最大的一路视频流。  <br>
     *        + 该方法需在进房后调用，若想进房前设置，你需调用 joinRoom{@link #IRTCRoom#joinRoom}，并对 `room_config` 中的 `remote_video_config` 进行设置。  <br>
     *        + SDK 会根据发布端和所有订阅端的设置灵活调整视频流的参数，具体调整策略详见[推送多路流](https://www.volcengine.com/docs/6348/70139)文档。
     */
    virtual int setRemoteVideoConfig(const char *user_id,const RemoteVideoConfig &remote_video_config) = 0;

    /** 
     * @type api
     * @region 房间管理
     * @brief 订阅房间内指定的通过摄像头/麦克风采集的媒体流，或更新对指定远端用户的订阅选项
     * @param [in] user_id 指定订阅的远端发布音视频流的用户 ID。
     * @param [in] type 媒体流类型，用于指定订阅音频/视频。参看 MediaStreamType{@link #MediaStreamType}。
     * @return 方法调用结果：
     *        + 0：成功；
     *        + <0：失败。具体失败原因参看 ReturnStatus{@link #ReturnStatus}。
     * @notes  <br>
     *        + 当调用本接口时，当前用户已经订阅该远端用户，不论是通过手动订阅还是自动订阅，都将根据本次传入的参数，更新订阅配置。<br>
     *        + 你必须先通过 onUserPublishStream{@link #IRTCRoomEventHandler#onUserPublishStream}} 回调获取当前房间里的远端摄像头音视频流信息，然后调用本方法按需订阅。  <br>
     *        + 调用该方法后，你会收到 onStreamSubscribed{@link #IRTCRoomEventHandler#onStreamSubscribed} 通知方法调用结果。  <br>
     *        + 成功订阅远端用户的媒体流后，订阅关系将持续到调用 unsubscribeStream{@link #IRTCRoom#unsubscribeStream} 取消订阅或本端用户退房。 <br>
     *        + 关于其他调用异常，你会收到 onStreamStateChanged{@link #IRTCRoomEventHandler#onStreamStateChanged} 回调通知，具体异常原因参看 ErrorCode{@link #ErrorCode}。
     */
    virtual int subscribeStream(const char *user_id,MediaStreamType type) = 0;
    /** 
     * @type api
     * @region 房间管理
     * @brief 订阅房间内所有通过摄像头/麦克风采集的媒体流，或更新订阅选项。
     * @param [in] type 媒体流类型，用于指定订阅音频/视频。参看 MediaStreamType{@link #MediaStreamType}。
     * @return  <br>
     *        0: 方法调用成功  <br>
     *        !0: 方法调用失败  <br>
     * @notes  <br>
     *        + 多次调用订阅接口时，将根据末次调用接口和传入的参数，更新订阅配置。<br>
     *        + 开启音频选路后，如果房间内的媒体流超过上限，建议通过调用 subscribeStream{@link #IRTCRoom#subscribeStream} 逐一指定需要订阅的媒体流。<br>
     *        + 调用该方法后，你会收到 onStreamSubscribed{@link #IRTCRoomEventHandler#onStreamSubscribed} 通知方法调用结果。  <br>
     *        + 成功订阅远端用户的媒体流后，订阅关系将持续到调用 unsubscribeStream{@link #IRTCRoom#unsubscribeStream} 取消订阅或本端用户退房。 <br>
     *        + 关于其他调用异常，你会收到 onStreamStateChanged{@link #IRTCRoomEventHandler#onStreamStateChanged} 回调通知，具体异常原因参看 ErrorCode{@link #ErrorCode}。
     */
     virtual int subscribeAllStreams(MediaStreamType type) = 0;

    /** 
     * @type api
     * @region 房间管理
     * @brief 取消订阅房间内指定的通过摄像头/麦克风采集的媒体流。  <br>
     *        该方法对自动订阅和手动订阅模式均适用。
     * @param [in] user_id 指定取消订阅的远端发布音视频流的用户 ID。
     * @param [in] type 媒体流类型，用于指定取消订阅音频/视频。参看 MediaStreamType{@link #MediaStreamType}。
     * @return 方法调用结果：
     *        + 0：成功；
     *        + <0：失败。具体失败原因参看 ReturnStatus{@link #ReturnStatus}。
     * @notes  <br>
     *        + 调用该方法后，你会收到 onStreamSubscribed{@link #IRTCRoomEventHandler#onStreamSubscribed} 通知方法调用结果。  <br>
     *        + 关于其他调用异常，你会收到 onStreamStateChanged{@link #IRTCRoomEventHandler#onStreamStateChanged} 回调通知，具体失败原因参看 ErrorCode{@link #ErrorCode}。
     */
    virtual int unsubscribeStream(const char *user_id,MediaStreamType type) = 0;
    /** 
     * @type api
     * @region 房间管理
     * @brief 取消订阅房间内所有的通过摄像头/麦克风采集的媒体流。  <br>
     *        自动订阅和手动订阅的流都可以通过本方法取消订阅。
     * @param [in] type 媒体流类型，用于指定取消订阅音频/视频。参看 MediaStreamType{@link #MediaStreamType}。
     * @return 方法调用结果：  <br>
     *        + 0：成功  <br>
     *        + !0：失败
     * @notes  <br>
     *        + 调用该方法后，你会收到 onStreamSubscribed{@link #IRTCRoomEventHandler#onStreamSubscribed} 通知方法调用结果。  <br>
     *        + 关于其他调用异常，你会收到 onStreamStateChanged{@link #IRTCRoomEventHandler#onStreamStateChanged} 回调通知，具体失败原因参看 ErrorCode{@link #ErrorCode}。
     */
    virtual int unsubscribeAllStreams(MediaStreamType type) = 0;
    /** 
     * @type api
     * @region 房间管理
     * @brief 订阅房间内指定的远端屏幕共享音视频流，或更新对指定远端用户的订阅选项
     * @param [in] user_id 指定订阅的远端发布屏幕流的用户 ID。
     * @param [in] type 媒体流类型，用于指定订阅音频/视频。参看 MediaStreamType{@link #MediaStreamType}。
     * @return 方法调用结果：
     *        + 0：成功；
     *        + <0：失败。具体失败原因参看 ReturnStatus{@link #ReturnStatus}。
     * @notes  <br>
     *        + 当调用本接口时，当前用户已经订阅该远端用户，不论是通过手动订阅还是自动订阅，都将根据本次传入的参数，更新订阅配置。<br>
     *        + 你必须先通过 onUserPublishScreen{@link #IRTCRoomEventHandler#onUserPublishScreen}} 回调获取当前房间里的远端屏幕流信息，然后调用本方法按需订阅。  <br>
     *        + 调用该方法后，你会收到 onStreamSubscribed{@link #IRTCRoomEventHandler#onStreamSubscribed} 通知方法调用结果。  <br>
     *        + 成功订阅远端用户的媒体流后，订阅关系将持续到调用 unsubscribeScreen{@link #IRTCRoom#unsubscribeScreen} 取消订阅或本端用户退房。 <br>
     *        + 关于其他调用异常，你会收到 onStreamStateChanged{@link #IRTCRoomEventHandler#onStreamStateChanged} 回调通知，具体异常原因参看 ErrorCode{@link #ErrorCode}。
     */
    virtual int subscribeScreen(const char *user_id,MediaStreamType type) = 0;

    /** 
     * @type api
     * @region 房间管理
     * @brief 取消订阅房间内指定的远端屏幕共享音视频流。  <br>
     *        该方法对自动订阅和手动订阅模式均适用。
     * @param [in] user_id 指定取消订阅的远端发布屏幕流的用户 ID。
     * @param [in] type 媒体流类型，用于指定取消订阅音频/视频。参看 MediaStreamType{@link #MediaStreamType}。
     * @return 方法调用结果：
     *        + 0：成功；
     *        + <0：失败。具体失败原因参看 ReturnStatus{@link #ReturnStatus}。
     * @notes  <br>
     *        + 调用该方法后，你会收到 onStreamSubscribed{@link #IRTCRoomEventHandler#onStreamSubscribed} 通知方法调用结果。  <br>
     *        + 关于其他调用异常，你会收到 onStreamStateChanged{@link #IRTCRoomEventHandler#onStreamStateChanged} 回调通知，具体失败原因参看 ErrorCode{@link #ErrorCode}。
     */
    virtual int unsubscribeScreen(const char *user_id,MediaStreamType type) = 0;

    /**
     * @hidden for internal use only.
     */
    virtual int enableSubscribeLocalStream(bool enable) = 0;

    /** 
     * @type api
     * @region 多房间
     * @brief 暂停接收来自远端的媒体流。
     * @param [in] media_type 媒体流类型，指定需要暂停接收音频还是视频流，参看 PauseResumeControlMediaType{@link #PauseResumeControlMediaType}。
     * @return  <br>
     *        + 0: 调用成功。
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @notes  <br>
     *        + 该方法仅暂停远端流的接收，并不影响远端流的采集和发送；  <br>
     *        + 该方法不改变用户的订阅状态以及订阅流的属性。  <br>
     *        + 若想恢复接收远端流，需调用 resumeAllSubscribedStream{@link #IRTCRoom#resumeAllSubscribedStream}。 <br>
     *        + 多房间场景下，仅暂停接收发布在当前所在房间的流。
     */
    virtual int pauseAllSubscribedStream(PauseResumeControlMediaType media_type) = 0;

    /** 
     * @type api
     * @region 多房间
     * @brief 恢复接收来自远端的媒体流
     * @param [in] media_type 媒体流类型，指定需要暂停接收音频还是视频流，参看 PauseResumeControlMediaType{@link #PauseResumeControlMediaType}
     * @return  <br>
     *        + 0: 调用成功。
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @notes <br>
     *        + 该方法仅恢复远端流的接收，并不影响远端流的采集和发送；  <br>
     *        + 该方法不改变用户的订阅状态以及订阅流的属性。
     */
    virtual int resumeAllSubscribedStream(PauseResumeControlMediaType media_type) = 0;


    /** 
     * @type api
     * @region 多房间
     * @brief 设置发流端音画同步。  <br>
     *        当同一用户同时使用两个通话设备分别采集发送音频和视频时，有可能会因两个设备所处的网络环境不一致而导致发布的流不同步，此时你可以在视频发送端调用该接口，SDK 会根据音频流的时间戳自动校准视频流，以保证接收端听到音频和看到视频在时间上的同步性。
     * @param [in] audio_user_id 音频发送端的用户 ID，将该参数设为空则可解除当前音视频的同步关系。
     * @return  <br>
     *        + 0: 调用成功。
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @notes <br>
     *        + 该方法在进房前后均可调用。  <br>
     *        + 进行音画同步的音频发布用户 ID 和视频发布用户 ID 须在同一个 RTC 房间内。  <br>
     *        + 调用该接口后音画同步状态发生改变时，你会收到 onAVSyncStateChange{@link #IRTCRoomEventHandler#onAVSyncStateChange} 回调。  <br>
     *        + 同一 RTC 房间内允许存在多个音视频同步关系，但需注意单个音频源不支持与多个视频源同时同步。  <br>
     *        + 如需更换同步音频源，再次调用该接口传入新的 `audio_user_id` 即可；如需更换同步视频源，需先解除当前的同步关系，后在新视频源端开启同步。
     */
    virtual int setMultiDeviceAVSync(const char* audio_user_id) = 0;

    /**
     * @hidden for internal use only.
     */
    virtual int updateCloudRendering(const char* cloudrenderJsonString) = 0;


    /**
     * @hidden for internal use only.
     */
    virtual int setCustomUserRole(const char* role) = 0;

    /** 
     * @type api
     * @region 多房间
     * @brief 开始跨房间转发媒体流。
     *        在调用 joinRoom{@link #IRTCRoom#joinRoom} 后调用本接口，实现向多个房间转发媒体流，适用于跨房间连麦等场景。<br>
     * @param [in] configuration 跨房间媒体流转发指定房间的信息。参看 ForwardStreamConfiguration{@link #ForwardStreamConfiguration}。
     * @return  <br>
     *        0: 方法调用成功  <br>
     *        <0: 方法调用失败  <br>
     * @notes <br>
     *        + 调用本方法后，将在本端触发 onForwardStreamStateChanged{@link #IRTCRoomEventHandler#onForwardStreamStateChanged} 回调。
     *        + 调用本方法后，你可以通过监听 onForwardStreamEvent{@link #IRTCRoomEventHandler#onForwardStreamEvent} 回调来获取各个目标房间在转发媒体流过程中的相关事件。
     *        + 开始转发后，目标房间中的用户将接收到本地用户进房 onUserJoined{@link #IRTCRoomEventHandler#onUserJoined} 和发流 onUserPublishStream{@link #IRTCRoomEventHandler#onUserPublishStream}/onUserPublishScreen{@link #IRTCRoomEventHandler#onUserPublishScreen} 的回调。
     *        + 调用本方法后，可以调用 updateForwardStreamToRooms{@link #IRTCRoom#updateForwardStreamToRooms} 更新目标房间信息，例如，增加或减少目标房间等。
     *        + 调用本方法后，可以调用 stopForwardStreamToRooms{@link #IRTCRoom#stopForwardStreamToRooms} 停止向所有房间转发媒体流。
     *        + 调用本方法后，可以调用 pauseForwardStreamToAllRooms{@link #IRTCRoom#pauseForwardStreamToAllRooms} 暂停向所有房间转发媒体流。
     */
    virtual int startForwardStreamToRooms(const ForwardStreamConfiguration& configuration) = 0;

    /** 
     * @type api
     * @region 房间管理
     * @brief 更新跨房间媒体流转发信息。<br>
     *        通过 startForwardStreamToRooms{@link #IRTCRoom#startForwardStreamToRooms} 发起媒体流转发后，可调用本方法增加或者减少目标房间，或更新房间密钥。
     *        调用本方法增加或删减房间后，将在本端触发 onForwardStreamStateChanged{@link #IRTCRoomEventHandler#onForwardStreamStateChanged} 回调，包含发生了变动的目标房间中媒体流转发状态。
     * @param [in] configuration 跨房间媒体流转发目标房间信息。参看 ForwardStreamConfiguration{@link #ForwardStreamConfiguration}。
     * @return  <br>
     *        + 0: 方法调用成功  <br>
     *        + <0: 方法调用失败
     * @notes <br>
     *        + 增加目标房间后，新增目标房间中的用户将接收到本地用户进房 onUserJoined{@link #IRTCRoomEventHandler#onUserJoined} 和发布 onUserPublishStream{@link #IRTCRoomEventHandler#onUserPublishStream}/onUserPublishScreen{@link #IRTCRoomEventHandler#onUserPublishScreen} 的回调。
     *        + 删减目标房间后，原目标房间中的用户将接收到本地用户停止发布 onUserUnpublishStream{@link #IRTCRoomEventHandler#onUserUnpublishStream}/onUserUnpublishScreen{@link #IRTCRoomEventHandler#onUserUnpublishScreen} 和退房 onUserLeave{@link #IRTCRoomEventHandler#onUserLeave} 的回调。
     */
    virtual int updateForwardStreamToRooms(const ForwardStreamConfiguration& configuration) = 0;

    /** 
     * @type api
     * @region 多房间
     * @brief 停止跨房间媒体流转发。
     *        通过 startForwardStreamToRooms{@link #IRTCRoom#startForwardStreamToRooms} 发起媒体流转发后，可调用本方法停止向所有目标房间转发媒体流。
     * @return  <br>
     *        + 0: 调用成功。
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @notes <br>
     *        + 调用本方法后，将在本端触发 onForwardStreamStateChanged{@link #IRTCRoomEventHandler#onForwardStreamStateChanged} 回调。
     *        + 调用本方法后，原目标房间中的用户将接收到本地用户停止发布 onUserUnpublishStream{@link #IRTCRoomEventHandler#onUserUnpublishStream}/onUserUnpublishScreen{@link #IRTCRoomEventHandler#onUserUnpublishScreen} 和退房 onUserLeave{@link #IRTCRoomEventHandler#onUserLeave} 的回调。
     *        + 如果需要停止向指定的房间转发媒体流，请调用 updateForwardStreamToRooms{@link #IRTCRoom#updateForwardStreamToRooms} 更新房间信息。
     *        + 如果需要暂停转发，请调用 pauseForwardStreamToAllRooms{@link #IRTCRoom#pauseForwardStreamToAllRooms}，并在之后随时调用 resumeForwardStreamToAllRooms{@link #IRTCRoom#resumeForwardStreamToAllRooms} 快速恢复转发。
     */
    virtual int stopForwardStreamToRooms() = 0;

    /** 
     * @type api
     * @region 多房间
     * @brief 暂停跨房间媒体流转发。
     *        通过 startForwardStreamToRooms{@link #IRTCRoom#startForwardStreamToRooms} 发起媒体流转发后，可调用本方法暂停向所有目标房间转发媒体流。
     *        调用本方法暂停向所有目标房间转发后，你可以随时调用 resumeForwardStreamToAllRooms{@link #IRTCRoom#resumeForwardStreamToAllRooms} 快速恢复转发。
     * @return  <br>
     *        + 0: 调用成功。
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @notes 调用本方法后，目标房间中的用户将接收到本地用户停止发布 onUserUnpublishStream{@link #IRTCRoomEventHandler#onUserUnpublishStream}/onUserUnpublishScreen{@link #IRTCRoomEventHandler#onUserUnpublishScreen} 和退房 onUserLeave{@link #IRTCRoomEventHandler#onUserLeave} 的回调。
     */
     virtual int pauseForwardStreamToAllRooms() = 0;

    /** 
     * @type api
     * @region 多房间
     * @brief 恢复跨房间媒体流转发。
     *        调用 pauseForwardStreamToAllRooms{@link #IRTCRoom#pauseForwardStreamToAllRooms} 暂停转发之后，调用本方法恢复向所有目标房间转发媒体流。
     * @return  <br>
     *        + 0: 调用成功。
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @notes <br>
     *        目标房间中的用户将接收到本地用户进房 onUserJoined{@link #IRTCRoomEventHandler#onUserJoined} 和发布 onUserPublishStream{@link #IRTCRoomEventHandler#onUserPublishStream}/onUserPublishScreen{@link #IRTCRoomEventHandler#onUserPublishScreen} 的回调。
     */
    virtual int resumeForwardStreamToAllRooms() = 0;

    /** 
     * @hidden(Linux)
     * @type api
     * @region 范围语音
     * @brief 获取范围语音接口实例。
     * @return 方法调用结果： <br>
     *        + IRangeAudio：成功，返回一个 IRangeAudio{@link #IRangeAudio} 实例。  <br>
     *        + nullptr：失败，当前 SDK 不支持范围语音功能。
     * @notes 首次调用该方法须在创建房间后、加入房间前。范围语音相关 API 和调用时序详见[范围语音](https://www.volcengine.com/docs/6348/114727)。
     */
    virtual IRangeAudio* getRangeAudio() = 0;

    /** 
     * @hidden(Linux)
     * @type api
     * @region 空间音频
     * @brief 获取空间音频接口实例。
     * @return 方法调用结果：  <br>
     *        + ISpatialAudio：成功，返回一个 ISpatialAudio{@link #ISpatialAudio} 实例。  <br>
     *        + nullptr：失败，当前 SDK 不支持空间音频功能。
     * @notes  <br>
     *        + 首次调用该方法须在创建房间后、加入房间前。空间音频相关 API 和调用时序详见[空间音频](https://www.volcengine.com/docs/6348/93903)。 <br>
     *        + 只有在使用支持真双声道播放的设备时，才能开启空间音频效果；  <br>
     *        + 机型性能不足可能会导致音频卡顿，使用低端机时，不建议开启空间音频效果；  <br>
     *        + SDK 最多支持 30 个用户同时开启空间音频功能。
     */
    virtual ISpatialAudio* getSpatialAudio() = 0;
    /** 
     * @type api
     * @region 多房间
     * @brief 调节某个房间内所有远端用户的音频播放音量。
     * @param [in] volume 音频播放音量值和原始音量的比值，范围是 [0, 400]，单位为 %，自带溢出保护。为保证更好的通话质量，建议将 volume 值设为 [0,100]。 <br>
     *              + 0: 静音  <br>
     *              + 100: 原始音量，默认值  <br>
     *              + 400: 最大可为原始音量的 4 倍(自带溢出保护)  <br>
     * @return  <br>
     *        + 0: 调用成功。
     *        + < 0 : 调用失败。查看 ReturnStatus{@link #ReturnStatus} 获得更多错误说明
     * @notes 假设某远端用户 A 始终在被调节的目标用户范围内，<br>
     *        + 当该方法与 setRemoteAudioPlaybackVolume{@link #IRTCVideo#setRemoteAudioPlaybackVolume} 共同使用时，本地收听用户 A 的音量为后调用的方法设置的音量；<br>
     *        + 当该方法与 setPlaybackVolume{@link #IRTCVideo#setPlaybackVolume} 方法共同使用时，本地收听用户 A 的音量将为两次设置的音量效果的叠加。
     */
    virtual int setRemoteRoomAudioPlaybackVolume(int volume) = 0;
    /** 
     * @hidden for internal use only on Windows and Android
     * @type api
     * @region 视频管理
     * @brief 接收端调用本接口获取全景视频接口引擎。
     * @return 方法调用结果： <br>
     *        + IPanoramicVideo：成功，返回一个 IPanoramicVideo{@link #IPanoramicVideo} 实例。  <br>
     *        + null：失败，当前 SDK 不支持全景视频功能。
     * @notes <br>
     *        + 接收端的调用时序为 createRTCVideo{@link #IRTCVideo#createRTCVideo} >  createRTCRoom{@link #IRTCVideo#createRTCRoom} > 本接口 > joinRoom{@link #IRTCRoom#joinRoom}。<br>
     *        + 获取 IPanoramicVideo 实例后，再调用 updateQuaternionf{@link #IPanoramicVideo#updateQuaternionf} 更新头位姿四元数。<br>
     *        + 你需要使用外部渲染器对接收到的全景视频进行渲染，参见 setRemoteVideoSink{@link #IRTCVideo#setRemoteVideoSink}。
     */
    virtual IPanoramicVideo* getPanoramicVideo() = 0;

    /** 
     * @valid since 3.52.
     * @type api
     * @region 房间管理
     * @brief 设置本端发布流在音频选路中的优先级。
     * @param [in] audio_selection_priority 本端发布流在音频选路中的优先级，默认正常参与音频选路。参见 AudioSelectionPriority{@link #AudioSelectionPriority}。 
     * @notes <br>
     *       + 在控制台上为本 appId 开启音频选路后，调用本接口才会生效。进房前后调用均可生效。更多信息参见[音频选路](https://www.volcengine.com/docs/6348/113547)。
     *       + 如果本端用户同时加入不同房间，使用本接口进行的设置相互独立。
     * 
     */
    virtual int setAudioSelectionConfig(AudioSelectionPriority audio_selection_priority) = 0;

    /** 
     * @valid since 3.52.
     * @type api
     * @region 房间管理
     * @brief 设置/更新房间附加信息，可用于标识房间状态或属性，或灵活实现各种业务逻辑。
     * @param [in] key 房间附加信息键值，长度小于 10 字节。<br>
     *        同一房间内最多可存在 5 个 key，超出则会从第一个 key 起进行替换。
     * @param [in] value 房间附加信息内容，长度小于 128 字节。
     * @return  <br>
     *        + 0: 方法调用成功，返回本次调用的任务编号； <br>
     *        + <0: 方法调用失败，具体原因详见 SetRoomExtraInfoResult{@link #SetRoomExtraInfoResult}。  
     * @notes  <br>
     *       + 在设置房间附加信息前，必须先调用 joinRoom{@link #IRTCRoom#joinRoom} 加入房间。  <br>
     *       + 调用该方法后，会收到一次 onSetRoomExtraInfoResult{@link #IRTCRoomEventHandler#onSetRoomExtraInfoResult} 回调，提示设置结果。  <br>
     *       + 调用该方法成功设置附加信息后，同一房间内的其他用户会收到关于该信息的回调 onRoomExtraInfoUpdate{@link #IRTCRoomEventHandler#onRoomExtraInfoUpdate}。<br>
     *       + 新进房的用户会收到进房前房间内已有的全部附加信息通知。
     */
    virtual int64_t setRoomExtraInfo(const char*key,const char*value) = 0;

    /** 
     * @type api
     * @region 字幕翻译服务
     * @brief 识别或翻译房间内所有用户的语音，形成字幕。<br>
     *        语音识别或翻译的结果会通过 onSubtitleMessageReceived{@link #IRTCRoomEventHandler#onSubtitleMessageReceived} 事件回调给你。<br> 
     *        调用该方法后，用户会收到 onSubtitleStateChanged{@link #IRTCRoomEventHandler#onSubtitleStateChanged} 回调，通知字幕是否开启。
     * @param [in] subtitle_config 字幕配置信息。参看 SubtitleConfig{@link #SubtitleConfig}。
     * @return  <br>
     *        +  0: 调用成功。  <br>
     *        + !0: 调用失败。
     * @notes <br>
     *         此方法需要在进房后调用。  <br> 
     *         如果想要指定源语言，你需要在进房前调用 `joinRoom` 接口，通过 extraInfo 参数传入 `"SourceLanguage": "zh"` 字符串来指定自己的源语言，目前仅支持指定中文、英文和日文。如果你未指定源语言，SDK 会将系统语种设定为源语言。 
     */ 
    virtual int startSubtitle(const SubtitleConfig& subtitle_config) = 0;
    /** 
     * @type api
     * @region 字幕翻译服务
     * @brief 关闭字幕。 <br>
     *        调用该方法后，用户会收到 onSubtitleStateChanged{@link #IRTCRoomEventHandler#onSubtitleStateChanged} 回调，通知字幕是否关闭。
     * @return  <br>
     *        +  0: 调用成功。  <br>
     *        + !0: 调用失败。 
     */
    virtual int stopSubtitle() = 0;
    /** 
     * @type api
     * @valid since 3.53
     * @brief 获取房间 ID。
     * @return 房间 ID。
     */
    virtual const char* getRoomId() = 0;
};

} // namespace bytertc

#endif // BYTE_RTC_ROOM_INTERFACE_H__
