/*
 * Copyright (c) 2023 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC Internal API
*/

#pragma once

#ifndef BYTE_RTC_P2P_INTERNAL_H__
#define BYTE_RTC_P2P_INTERNAL_H__

#include "api/cpp/rtc/bytertc_defines.h"
#include <stdint.h>
#include <stdarg.h>

namespace bytertc {
enum ConnectionType{
    kConnectionTypeP2S = 0,
    kConnectionTypeP2P,
};

enum P2PSignalState{
    kP2PSignalStateStart = 0,
    kP2PSignalStateStop,
};

class IEngineInternalP2PEventHandler {
public:
    virtual ~IEngineInternalP2PEventHandler() = default;
    virtual void onP2PConnectionStatusUpdated(ConnectionType state) {}
    virtual void onP2PSignalingStatusUpdated(P2PSignalState state) {}
};

/** {zh}
 * @brief 设置P2P内部事件回调
 * @param [in] engine 当前app应用的RTC引擎
 * @param [in] handler 当前app应用的P2P内部事件回调句柄
 * @notes  必须在joinChannel之前调用
 */
/** {en}
 * @brief Set the p2p internal event callback
 * @param [in] engine RTC engine for current app
 * @param [in] handler P2P internal event callback handle for the current app
 * @notes You should call this method after enableP2P returns success
 * @notes You should call this method before entering the room.
 */
BYTERTC_API void setP2PEventHandler(void* engine, IEngineInternalP2PEventHandler* handler);

/** {zh}
 * @brief 开启P2P能力
 * @param [in] engine 当前app应用的RTC引擎
 * @param [in] room_id 需要开启P2P的房间号
 * @param [in] only_lan 是否只开启局域网P2P
 * @return 返回P2P是否开启成功, 0: 成功, -1: 失败
 * @notes  必须在joinChannel之前调用
 */
/** {en}
 * @brief Enable P2P ability and set the p2p internal callback event
 * @param [in] engine RTC engine for current app
 * @param [in] room_id The room id to enable P2P
 * @param [in] only_lan Whether only enable lan P2P
 * @return Returns whether the P2P is enabled successfully, 0: success, -1: failure
 * @notes You should call this method before entering the room.
 */
BYTERTC_API int enableP2P(void* engine, const char* room_id, bool only_lan);
      
}  // namespace bytertc

#endif // BYTE_RTC_P2P_INTERNAL_H__ 
