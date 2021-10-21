/*
 * Copyright (c) 2020 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngine Event Handler
*/

#pragma once

#ifndef BYTE_RTC_EVENT_HANDLER_H__
#define BYTE_RTC_EVENT_HANDLER_H__

#include "bytertc_defines.h"
#include "bytertc_engine_lite_event_handler.h"
#include "bytertc_room_interface.h"

namespace bytertc {

/**
 * @type callback
 * @brief 音视频引擎事件回调接口。  <br>
 *        创建 RTCEngine 实例 CreateRtcEngine{@link #CreateRtcEngine} 时，传入该回调实例。  <br>
 *        详见 IRtcEngineLiteEventHandler{@link #IRtcEngineLiteEventHandler} 、IRTCRoomEventHandler{@link #IRTCRoomEventHandler}
 */
class IRtcEngineEventHandler : public IRtcEngineLiteEventHandler,
                               public IRTCRoomEventHandler {
public:
    /**
     * @hidden
     */
    virtual ~IRtcEngineEventHandler() {
    }
	
	/**
    * @hidden
    * @type callback
    * @region 游戏接口
    * @brief 游戏场景中，当房间用户的的 sendmode 被修改的时候回调该事件，发送模式只有三种，分别是：静音、向小队发送、向世界发送。
    * @param [in] uid  <br>
    *        远端用户 id 。
    * @param [in] range_audio_mode  <br>
    *        远端用户的发送模式，详见: RangeAudioMode{@link #RangeAudioMode} 。
    */
    virtual void OnUserAudioSendModeChange(const char* uid, int range_audio_mode) {
        (void)uid;
        (void)range_audio_mode;
    }

    /**
     * @hidden
     * @type callback
     * @region 游戏接口
     *@brief 游戏场景中，当房间用户的的 recvmode 被修改的时候回调该事件，收听模式只有三种，分别是：静音、收听小队、收听世界。
     *@param [in] uid  <br>
     *       远端用户 id 。
     *@param [in] range_audio_mode  <br>
     *       远端用户的接收模式，详见: RangeAudioMode{@link #RangeAudioMode} 。
     */
    virtual void OnUserAudioRecvModeChange(const char* uid, int range_audio_mode) {
        (void)uid;
        (void)range_audio_mode;
    }
	
private:
     /**
      * @hidden
     */
    virtual void OnRoomWarning(int warn) override {
    }
     /**
      * @hidden
     */
    virtual void OnRoomError(int err) override {
    }
};

} // namespace bytertc

#endif // BYTE_RTC_EVENT_HANDLER_H__
