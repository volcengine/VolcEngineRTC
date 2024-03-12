/*
 * Copyright (c) 2020 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC Internal API
*/

#pragma once

#include "bytertc_defines.h"
#include <stdint.h>
#include <stdarg.h>

namespace bytertc {

/** {zh}
 * @brief 自定义用户角色
 * @notes  必须在joinChannel之前调用
 */
/** {en}
 * @brief Customize user roles
 * @notes You should call this method before entering the room.
 */
BYTERTC_API void setCustomUserRole(void* engine, const char* role);

/** {zh}
 * @brief 设置 ByteRTC SDK 默认开启使用QUIC获取配置
 * @notes  一般在linux端SDK使用
 */
/** {en}
 * @brief Set ByteRTC SDK to use QUIC to get configuration by default
 * @notes Generally used in the SDK for Linux
 */
BYTERTC_API void setDefaultEnableQuicGetAccess();

/** {zh}
 * @brief 设置 ByteRTC SDK 默认开启使用KCP获取配置
 * @notes  一般在linux端SDK使用
 */
/** {en}
 * @brief Set ByteRTC SDK to use KCP to get configuration by default
 * @notes Generally used in the SDK for Linux
 */
BYTERTC_API void setDefaultEnableKcpGetAccess();

/** {zh}
 * @brief 设置 ByteRTC SDK 默认开启通话前网络探测
 * @notes  一般在linux端SDK使用
 */
/** {en}
 * @brief Set ByteRTC SDK to enable pre-call network detection by default
 * @notes Generally used in the SDK for Linux
 */
BYTERTC_API void setDefaultEnableNetworkDetect();

/** {zh}
 * @brief 设置 ByteRTC SDK 默认开启使用KCP消息通道
 * @notes  一般在linux端SDK使用
 */
/** {en}
 * @brief Set ByteRTC SDK to use KCP message channel by default
 * @notes Generally used in the SDK for Linux
 */
BYTERTC_API void setDefaultEnableKcpDataChannel();

struct VideoStreamDescription {
    unsigned int width;
    unsigned int height;
    unsigned int frame_rate;
    unsigned int max_kbps;
};

enum class PixelFormat {
      kDefault = 0,
      kI420 = 1,
      kRGBA = 2,
      kTexture = 3,
};

enum class NetworkFamily {
    kNetworkFamilyNone = 0,
    kNetworkFamilyIPv4 = 1,
    kNetworkFamilyIPv6 = 2,
    kNetworkFamilyBoth = 3,
};

enum StreamFlag {
    kStreamFlagNone = 0,
    kStreamFlagNormal = 1 << 0,
    kStreamFlagDocShare = 1 << 1,
    kStreamFlagMCU = 1 << 2,
    kStreamFlagMeetTogether = 1 << 3,
    // 1 << 4 被服务端占用用作 sip 流
    kStreamFlagMultiStream = 1 << 6,
};

}  // namespace bytertc

