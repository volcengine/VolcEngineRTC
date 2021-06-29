#pragma once
#include "byte_rtc_engine_interface.h"
#include <stdint.h>
#include <stdarg.h>

namespace bytertc {

/**
 *@brief 自定义用户角色
 *@notes  必须在joinChannel之前调用
 */
BYTE_API void SetCustomUserRole(IRtcEngine* engine, const char* role);

/**
*@brief 设置 Byte SDK 默认开启使用QUIC获取配置
*@notes  一般在linux端SDK使用
*/
BYTE_API void SetDefaultEnableQuicGetAccess();

/**
*@brief 设置 Byte SDK 默认开启使用KCP获取配置
*@notes  一般在linux端SDK使用
*/
BYTE_API void SetDefaultEnableKcpGetAccess();

/**
*@brief 设置 Byte SDK 默认开启使用KCP消息通道
*@notes  一般在linux端SDK使用
*/
BYTE_API void SetDefaultEnableKcpDataChannel();

struct VideoStreamDescription {
public:
    unsigned int width;
    unsigned int height;
    unsigned int frame_rate;
    unsigned int max_kbps;
    ScaleMode scale_mode;
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

class IEngineInternalEventHandler {
public:
    virtual ~IEngineInternalEventHandler() {
    }
    /**
     *@brief 当前byte引擎是否启用ice复用功能
     *@param [in] muxed
     *       当前byte引擎是否启用ice复用
     *       true  :启用ice复用
     *       false :不启用ice复用
     */
    virtual void OnPeerConnectionICEMux(bool muxed){};
    virtual void OnSystemInfoLog(double app_cpu_usage, double total_cpu_usage, double app_memery_usage){};
    virtual void OnSignalingAddrChanged(const char* addr){};
    virtual void OnConfigAddrChanged(const char* addr){};
    virtual void OnMediaServerAddrChanged(const char* addr){};
};

/**
 *@brief 设置当前引擎的内部回调事件
 *@param [in] engine
 *       当前app应用的byte engine引擎
 *@param [in] handler
 *       当前app应用的内部事件回调句柄
 *@notes  必须在join channel前调用该函数
 */
BYTE_API void SetEngineInternalEventHandler(
      IRtcEngine *engine,
      IEngineInternalEventHandler* handler);
}  // namespace bytertc
