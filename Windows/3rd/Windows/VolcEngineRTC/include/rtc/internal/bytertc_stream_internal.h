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

enum StreamMessageChannelType {
    /**
     * @brief SEI消息类型
     */
    kStreamMessageChannelTypeSEI = 0,
    /**
     * @brief 媒体流消息类型
     */
    kStreamMessageChannelTypeDataMessage,
};
/** 
 * @hidden(Android, iOS, Mac, Windows) 仅供内部使用
 * @brief ByteRTC SDK 推一路无房间流
 * @notes  一般在linux端SDK使用
 */
BYTERTC_API int startPushStream(void* engine, const char* token, const char* stream_id);

/** 
 * @hidden(Android, iOS, Mac, Windows) 仅供内部使用
 * @brief ByteRTC SDK 停止推无房间流
 * @notes  一般在linux端SDK使用
 */
BYTERTC_API void stopPushStream(void* engine);

/** 
 * @hidden(Android, iOS, Mac, Windows) 仅供内部使用
 * @brief ByteRTC SDK 通过流发送消息到拉流端
 * @notes  一般在linux端SDK使用
 */
BYTERTC_API int64_t sendDataMessageToStream(void* engine, const char* stream_id, const char* message,
        DataMessageSourceType source_type);

class IEngineInternalStreamEventHandler {
public:
    virtual ~IEngineInternalStreamEventHandler() = default;
    virtual void onPushStreamResult(const char* stream_id, int error_code) {}
};

/** 
 * @hidden(Android, iOS, Mac, Windows) 仅供内部使用
 * @brief 设置推无房间流结果回调
 * @param [in] engine 当前app应用的RTC引擎
 * @param [in] handler 当前app应用的内部事件回调句柄
 * @notes 必须在StartPushStream前调用该函数
 */
BYTERTC_API void setEngineInternalStreamEventHandler(void *engine, IEngineInternalStreamEventHandler* handler);

}  // namespace bytertc
