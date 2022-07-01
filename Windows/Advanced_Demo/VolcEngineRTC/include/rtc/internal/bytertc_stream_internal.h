/*
 * Copyright 2020 @bytedance
 *
 *  Created on: Mar 16, 2020
 */

#pragma once

#include "../bytertc_engine_interface.h"
#include <stdint.h>
#include <stdarg.h>

namespace bytertc {

/** 
 * @brief ByteRTC SDK 推一路无房间流
 * @notes  一般在linux端SDK使用
 */
BYTERTC_API int StartPushStream(IRtcEngine* engine, const char* token, const char* stream_id);

/** 
 * @brief ByteRTC SDK 停止推无房间流
 * @notes  一般在linux端SDK使用
 */
BYTERTC_API void StopPushStream(IRtcEngine* engine);

class IEngineInternalStreamEventHandler {
public:
    virtual ~IEngineInternalStreamEventHandler() = default;
    virtual void OnPushStreamResult(const char* stream_id, int error_code) {}
};

/** 
 * @brief 设置推无房间流结果回调
 * @param [in] engine 当前app应用的RTC引擎
 * @param [in] handler 当前app应用的内部事件回调句柄
 * @notes 必须在StartPushStream前调用该函数
 */
BYTERTC_API void SetEngineInternalStreamEventHandler(IRtcEngine *engine, IEngineInternalStreamEventHandler* handler);

}  // namespace bytertc
