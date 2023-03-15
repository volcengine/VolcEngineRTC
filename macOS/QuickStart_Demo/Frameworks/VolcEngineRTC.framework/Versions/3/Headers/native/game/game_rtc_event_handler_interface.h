/*
 *  Copyright (c) 2021 The ByteRtc project authors. All Rights Reserved.
 *  @company ByteDance.Inc
 *  @brief 游戏语音引擎处理回调
 */
#pragma once

#include "game_rtc_defines.h"

namespace bytertc {
namespace gamertc {
class IGameRTCEventHandler {
public:
    /**
     * @type callback
     * @region 游戏语音事件回调
     * @brief 当加入房间成功时收到该回调
     * @param [in] room_id 房间 ID
     * @param [in] user_id 用户 ID
     * @param [in] error_code 用户加入房间回调的状态码，0 为成功，非0 表示失败。<br>
     *        具体原因参考错误码 RoomErrorCode{@link #RoomErrorCode}以及 RoomWarningCode{@link #RoomWarningCode}  <br>
     * @param [in] is_rejoined
     *        标识是否重新进房，首次进房该值为false，发生断网重连进房时为true
     * @param [in] elapsed 进房耗时
     */
    virtual void onRoomStateChanged(const char* room_id, const char* user_id,
            RoomStateCode state,
            const char* extra_info) {
        (void)room_id;
        (void)user_id;
        (void)state;
        (void)extra_info;
    }
    
    /**
     * @type callback
     * @region 游戏语音事件回调
     * @brief 当加入房间成功时收到该回调
     * @param [in] room_id 房间 ID
     * @param [in] user_id 用户 ID
     * @param [in] error_code 用户加入房间回调的状态码，0 为成功，非0 表示失败。<br>
     *        具体原因参考错误码 RoomErrorCode{@link #RoomErrorCode}以及 RoomWarningCode{@link #RoomWarningCode}  <br>
     * @param [in] is_rejoined
     *        标识是否重新进房，首次进房该值为false，发生断网重连进房时为true
     * @param [in] elapsed 进房耗时
     */
    virtual void onStreamStateChanged(const char* room_id, const char* user_id,
        StreamStateCode state, const char* extra_info) {
        (void)room_id;
        (void)user_id;
        (void)state;
        (void)extra_info;
    }

    /**
     * @type callback
     * @region 游戏语音事件回调
     * @brief 离开房间时回调
     * @param [in] room_id 房间 ID
     */
    virtual void onLeaveRoom(const char* room_id) {
        (void)room_id;
    }

    /**
     * @type callback
     * @region 游戏语音事件回调
     * @brief 房间内其他用户加入时回调
     * @param [in] room_id 房间 ID
     * @param [in] user_id 用户 ID
     */
    virtual void onUserJoined(const char* room_id, const char* user_id) {
        (void)room_id;
        (void)user_id;
    }

    /**
     * @type callback
     * @region 游戏语音事件回调
     * @brief 房间内其他用户离开房间时回调
     * @param [in] room_id 房间 ID
     * @param [in] user_id 用户 ID
     * @param [in] reason 用户离开原因，详见 UserLeaveReasonType{@link #UserLeaveReasonType}。
     */
    virtual void onUserLeave(const char* room_id, const char* user_id, UserLeaveReasonType reason) {
        (void)room_id;
        (void)user_id;
        (void)reason;
    }

    /**
     * @type callback
     * @region 游戏语音事件回调
     * @brief 房间内其他用户的麦克风状态变化时回调
     * @param [in] room_id 房间 ID
     * @param [in] user_id 用户 ID
     * @param [in] enable
     *        true: 表示麦克风打开
     *        false: 表示麦克风关闭
     */
    virtual void onMicrophoneEnabled(const char* room_id, const char* user_id, bool enable) {
        (void)room_id;
        (void)user_id;
        (void)enable;
    }

    /**
     * @type callback
     * @region 游戏语音事件回调
     * @brief 房间内其他用户的语音发送状态变化时回调
     * @param [in] room_id 房间 ID
     * @param [in] user_id 用户 ID
     * @param [in] enable
     *        true: 表示允许语音发送
     *        false: 表示禁止语音发送
     */
    virtual void onAudioSendEnabled(const char* room_id, const char* user_id, bool enable) {
        (void)room_id;
        (void)user_id;
        (void)enable;
    }

    /**
     * @type callback
     * @region 游戏语音事件回调
     * @brief 房间内其他用户的扬声器状态变化时回调
     * @param [in] room_id 房间 ID
     * @param [in] user_id 用户 ID
     * @param [in] enable
     *        true: 表示扬声器打开，可以接收其他用户的音频数据
     *        false: 表示扬声器关闭，不接收接收其他用户的音频数据
     */
    virtual void onSpeakerphoneEnabled(const char* room_id, const char* user_id, bool enable) {
        (void)room_id;
        (void)user_id;
        (void)enable;
    }

    /**
     * @type callback
     * @region 游戏语音事件回调
     * @brief 音量信息回调
     * @param [in] room_id 房间 ID
     * @param [in] speakers 音量数组，每个元素包括用户名和音量值
     * @param [in] speaker_number 音量数组的长度
     * @param [in] total_volume 总的音量值
     */
    virtual void onAudioVolumeIndication(const char* room_id, const AudioVolumeInfo* speakers,
            unsigned int speaker_number,
            int total_volume) {
        (void)room_id;
        (void)speakers;
        (void)speaker_number;
        (void)total_volume;
    }
    
    virtual void onTokenWillExpire(const char* room_id) {
        (void)room_id;
    }

    /**
     * @type callback
     * @region 游戏语音事件回调
     * @brief 用户网络质量回调
     * @param [in] room_id 房间 ID
     * @param [in] user_id 网络状态关联的用户 ID
     * @param [in] tx_quality
     *        user_id 所属用户的媒体流上行网络质量。
     * @param [in] rx_quality
     *        user_id 所属用户的媒体流下行网络质量。
     *  @notes 
     *        + 当 user_id 为本地用户 ID 时，txQuality 为该用户的上行网络质量，rxQuality 为该用户的下行网络质量。
     *        + 当 user_id 为远端用户 ID 时，目前仅支持获取该用户的上行网络质量 txQuality ，下行网络质量 rxQuality 为 0 。
     *        + 网络质量的定义：
     *                     kNetworkQualityUnknown(0)：质量未知。
     *                     kNetworkQualityExcellent(1)：质量极好。
     *                     kNetworkQualityGood(2)：用户主观感觉和极好差不多，但码率可能略低于极好。
     *                     kNetworkQualityPoor(3)：用户主观感受有瑕疵但不影响沟通。
     *                     kNetworkQualityBad(4)：勉强能沟通但不顺畅。
     *                     kNetworkQualityVbad(5)：网络质量非常差，基本不能沟通。
     */
    virtual void onNetworkQuality(const char* room_id, const char* user_id,
            NetworkQuality tx_quality, NetworkQuality rx_quality) {
        (void)room_id;
        (void)user_id;
        (void)tx_quality;
        (void)rx_quality;
    }

    /**
     * @type callback
     * @region 游戏语音事件回调
     * @brief SDK 与信令服务器连接状态改变回调。连接状态改变时触发。
     * @param [in] state
     *        当前 SDK 与信令服务器的连接状态，详见：GameConnectionState。
     * @notes 更多信息参见 [连接状态提示](https://www.volcengine.com/docs/6348/95376)。
     */
    virtual void onConnectionStateChanged(ConnectionState state) {
        (void)state;
    }

    /**
     * @type callback
     * @region 游戏语音事件回调
     * @brief 房间相关警告事件触发回调，例如订阅时媒体地址无效
     * @param [in] room_id 房间 ID
     * @param [in] warn 警告码，具体参考 RoomWarnCode
     */
    virtual void onRoomWarning(const char* room_id, RoomWarnCode warn) {
        (void)room_id;
        (void)warn;
    }

    /**
     * @type callback
     * @region 游戏语音事件回调
     * @brief 房间相关错误事件触发回调，例如 token 过期
     * @param [in] room_id 房间 ID
     * @param [in] err 错误码，具体参考 RoomErrorCode
     */
    virtual void onRoomError(const char* room_id, RoomErrorCode err) {
        (void)room_id;
        (void)err;
    }

    /**
     * @type callback
     * @region 游戏语音事件回调
     * @brief 引擎相关警告事件触发回调，例如没有麦克风权限
     * @param [in] warn 警告码，具体参考 EngineWarnCode
     */
    virtual void onEngineWarning(EngineWarnCode warn) {
        (void)warn;
    }

    /**
     * @type callback
     * @region 游戏语音事件回调
     * @brief 日志事件上报
     * @param [in] log_type
     *        日志类型，固定为 live_webrtc_monitor_log
     * @param [in] log_content
     *        日志内容
     */
    virtual void onLogReport(const char* log_type, const char* log_content) {
        (void)log_type;
        (void)log_content;
    }

    /**
     * @hidden
     * @brief 析构函数
     */
    virtual ~IGameRTCEventHandler() {}
};

} // namespace gamertc
} // namespace bytertc
