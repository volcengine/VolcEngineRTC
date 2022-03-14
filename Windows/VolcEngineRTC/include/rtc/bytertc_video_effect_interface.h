/*
 * Copyright (c) 2020 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC Video Effect Interface
*/

#pragma once

#ifndef BYTE_RTC_VIDEO_EFFECT_INTERFACE_H__
#define BYTE_RTC_VIDEO_EFFECT_INTERFACE_H__

#include <stdint.h>

namespace bytertc {
/** 
 * @type keytype
 * @brief 虚拟背景类型。
 */
enum VirtualBackgroundSourceType {
    /** 
     * @brief 使用纯色背景替换视频原有背景。
     */
    kVirtualBackgroundSourceColor = 0,
    /** 
     * @brief 使用自定义图片背景替换视频原有背景。
     */
    kVirtualBackgroundSourceImage = 1,
};

/** 
 * @type keytype
 * @brief 虚拟背景对象。
 */
struct VirtualBackgroundSource{
    /** 
     * @brief 虚拟背景类型，详见 VirtualBackgroundSourceType{@link #VirtualBackgroundSourceType} 。
     */
    VirtualBackgroundSourceType source_type;
    /** 
     * @brief 纯色背景使用的颜色。<br>
     *        格式为 0xAARRGGBB 。
     */
    uint32_t source_color = 0xFFFFFFFF;
    /** 
     * @brief 自定义图片背景使用的图片的绝对路径。
     * @notes  <br>
     *       + 支持的格式为 jpg、jpeg、和 png。<br>
     *       + 分辨率超过 1080P 时，图片会被等比缩放。背景图片和视频分辨率不一致时，图片会被裁剪缩放。<br>
     */
    const char* source_path = nullptr;
};

/** 
 * @type api
 * @brief 视频特效接口
 */
class IVideoEffect {
public:
    /** 
     * @type api
     * @region 视频特效
     * @brief 视频特效许可证检查
     * @param androidContext  <br>
     *        Android Context 对象指针(jobject 类型)。Android 以外平台传入 nullptr
     * @param jnienv Android  <br>
     *        JNIEnv 指针。Android 以外平台传入 nullptr
     * @param licensePath 许可证文件绝对路径
     * @return  <br>
     *      + 0: 调用成功  <br>
     *      + 1000: 未集成cvsdk  <br>
     *      + 1001: 本RTC版本不支持cv功能  <br>
     *      + < 0: 调用失败，具体错误码请参考 [CV SDK 文档](http://ailab-cv-sdk.bytedance.com/docs/2036/99783/)。
     * @notes 开始使用视频特效前，你必须先调用这个方法进行许可证验证
     */
    virtual int CheckLicense(void* androidContext, void* jnienv, const char* licensePath) = 0;

    /** 
     * @type api
     * @region 视频特效
     * @hidden (iOS, Android)
     * @brief 从 CV SDK 获取授权消息，用于获取在线许可证。
     * @param [in] ppmsg 授权消息字符串地址
     * @param [in] len 授权消息字符串的长度
     * @return  <br>
     *      + 0: 调用成功  <br>
     *      + 1000: 未集成 CV SDK  <br>
     *      + 1001: 本 RTC 版本不支持 CV 功能  <br>
     *      + < 0: 调用失败，具体错误码，请参考 [CV SDK 文档](http://ailab-cv-sdk.bytedance.com/docs/2036/99783/)。
     * @notes <br>
     *        + 使用 CV 的功能前，你必须获取 CV SDK 的在线许可证。  <br>
     *          通过此接口获取授权消息后，你必须参考 [在线授权说明](http://ailab-cv-sdk.bytedance.com/docs/2036/99798/)。 <br>
     *          自行实现获取在线许可证的业务逻辑。获取许可证后，你必须调用 CheckLicense{@link #CheckLicense} 确认许可证有效。然后，你才可以使用 CV 功能。  <br>
     *        + 获取授权消息后，调用 FreeAuthMessage{@link #FreeAuthMessage} 释放内存。
     */
    virtual int GetAuthMessage(char ** ppmsg, int * len) = 0;
    /** 
     * @type api
     * @region 视频特效
     * @hidden (iOS, Android)
     * @brief 使用完授权消息字符串后，释放内存。
     * @param [in] pmsg GetAuthMessage 返回的授权消息字符串。
     * @return  <br>
     *      + 0: 调用成功  <br>
     *      + 1000: 未集成 CV SDK  <br>
     *      + 1001: 本 RTC 版本不支持 CV 功能  <br>
     *      + < 0: 调用失败，具体错误码，请参考 [CV SDK 文档](http://ailab-cv-sdk.bytedance.com/docs/2036/99783/)。
     */
    virtual int FreeAuthMessage(char * pmsg) = 0;

    /** 
     * @type api
     * @region 视频特效
     * @brief 开启关闭视频特效
     * @param enabled 是否开启特效，true: 开启，false: 关闭
     * @return
     *      0: 调用成功
     *      1000: 未集成cvsdk
     *      < 0: 调用失败，具体错误码含义请参考cvsdk文档
     * @notes 在调用CheckLicense{@link #CheckLicense}和SetAlgoModelPath{@link #SetAlgoModelPath}后调用此方法
     */
    virtual int EnableEffect(bool enabled) = 0;

    /** 
     * @type api
     * @region 视频特效
     * @brief 设置视频特效算法模型路径
     * @param modelPath 模型路径
     */
    virtual void SetAlgoModelPath(const char* modelPath) = 0;

    /** 
     * @type api
     * @region 视频特效
     * @brief 设置视频特效素材包
     * @param effectNodePaths 特效素材包路径数组 <br>
     *        要取消当前视频特效，将此参数设置为 null。
     * @param [in] nodeNum  <br>
     *        特效素材包个数
     * @return  <br>
     *      + 0: 调用成功  <br>
     *      + 1000: 未集成 CV SDK  <br>
     *      + 1001: 本 RTC 版本不支持 CV 功能  <br>
     *      + < 0: 调用失败，具体错误码，请参考 [CV SDK 文档](http://ailab-cv-sdk.bytedance.com/docs/2036/99783/)。
     */
    virtual int SetEffectNodes(const char** effectNodePaths, int nodeNum) = 0;


    /** 
     * @type api
     * @region 视频特效
     * @brief 设置特效强度
     * @param [in] nodePath  <br>
     *        特效素材包路径
     * @param [in] nodeKey  <br>
     *        需要设置的素材 key 名称，取值请参考 [素材 key 对应说明](http://ailab-cv-sdk.bytedance.com/docs/2036/99769/)。
     * @param [in] nodeValue  <br>
     *        需要设置的强度值 取值范围 [0,1]，超出范围时设置无效。
     * @return  <br>
     *      + 0: 调用成功  <br>
     *      + 1000: 未集成 CV SDK  <br>
     *      + 1001: 本 RTC 版本不支持 CV 功能  <br>
     *      + < 0: 调用失败，具体错误码，请参考 [CV SDK 文档](http://ailab-cv-sdk.bytedance.com/docs/2036/99783/)。
     */
    virtual int UpdateNode(const char* nodePath, const char* nodeKey, float nodeValue) = 0;

    /** 
     * @type api
     * @region 视频特效
     * @brief 设置颜色滤镜
     * @param [in] resPath  <br>
     *        滤镜资源包绝对路径。
     * @return  <br>
     *      + 0: 调用成功  <br>
     *      + 1000: 未集成 CV SDK  <br>
     *      + 1001: 本 RTC 版本不支持 CV 功能  <br>
     *      + < 0: 调用失败，具体错误码，请参考 [CV SDK 文档](http://ailab-cv-sdk.bytedance.com/docs/2036/99783/)。
     */
    virtual int SetColorFilter(const char* resPath) = 0;

    /** 
     * @type api
     * @region 视频特效
     * @brief 设置已启用颜色滤镜的强度
     * @param [in] intensity  <br>
     *        滤镜强度。取值范围 [0,1]，超出范围时设置无效。
     * @return  <br>
     *      + 0: 调用成功  <br>
     *      + 1000: 未集成 CV SDK  <br>
     *      + 1001: 本 RTC 版本不支持 CV 功能  <br>
     *      + < 0: 调用失败，具体错误码，请参考 [CV SDK 文档](http://ailab-cv-sdk.bytedance.com/docs/2036/99783/)。
     */
    virtual int SetColorFilterIntensity(float intensity) = 0;

    /** 
     * @type api
     * @region 视频特效
     * @brief 虚拟背景功能初始化。
     * @param [in] androidContext Android Context 对象指针(jobject 类型)。非 Android 平台传入 nullptr 即可。
     * @param [in] jnienv Android JNIEnv 指针。非 Android 平台传入 nullptr 即可。
     * @param [in] licensePath CV 许可证文件的绝对路径
     * @param [in] modelPath 模型参数文件的绝对路径
     * @return  <br>
     *        + 0: 调用成功。  <br>
     *        + 1000: 调用失败，未集成 CV SDK 。  <br>
     *        + 1001: 调用失败，本 SDK 版本不支持 CV 功能。  <br>
     *        + > 40000: 调用失败，CV SDK 授权错误，具体错误码请参考 [CV SDK 文档](http://ailab-cv-sdk.bytedance.com/docs/2036/99783/)。  <br>
     *        + < 0: 调用失败，CV SDK 内部错误，具体错误码请参考 [CV SDK 文档](http://ailab-cv-sdk.bytedance.com/docs/2036/99783/)。  <br>
     */
    virtual int InitVirtualBackground(void* androidContext, void* jnienv, const char* licensePath,const char* modelPath) = 0;

    /** 
     * @type api
     * @region 视频特效
     * @brief 开启虚拟背景。
     * @param [in] source 虚拟背景对象，详见 VirtualBackgroundSource{@link #VirtualBackgroundSource} 。
     * @return  <br>
     *        + 0: 调用成功。  <br>
     *        + < 0: 调用失败，CV SDK 内部错误，具体错误码请参考 [CV SDK 文档](http://ailab-cv-sdk.bytedance.com/docs/2036/99783/)。  <br>
     *        + -1: 调用失败，未调用 InitVirtualBackground{@link #IVideoEffect#InitVirtualBackground} 或调用失败，导致 license 验证失败。  <br>
     *        + -4: 调用失败，自定义背景图片打开失败。  <br>
     *        + -37: 调用失败，自定义背景图片解码失败。  <br>
     *        + -38: 调用失败，图片格式不支持。支持的图片格式是 jpg、jpeg、和 png。  <br>
     * @notes  <br>
     *       + 调用此接口前，需要先调用 InitVirtualBackground{@link #IVideoEffect#InitVirtualBackground} 初始化 CV 环境；  <br>
     *       + 虚拟背景仅支持摄像头采集的视频流，包括 RTC SDK 内部机制采集的方式和自定义采集的方式。虚拟背景不支持屏幕视频流。  <br>
     */
    virtual int EnableVirtualBackground(const VirtualBackgroundSource& source) = 0;

    /** 
     * @type api
     * @region 视频特效
     * @brief 关闭虚拟背景。
     * @return  <br>
     *        + 0: 调用成功。  <br>
     *        + < 0: 调用失败，具体错误码请参考 [CV SDK 文档](http://ailab-cv-sdk.bytedance.com/docs/2036/99783/)。  <br>
     * @notes 调用 EnableVirtualBackground{@link #EnableVirtualBackground} 开启虚拟背景后，可以调用此接口关闭虚拟背景。
     */
    virtual int DisableVirtualBackground() = 0;
};

}  // namespace bytertc

#endif // BYTE_RTC_VIDEO_EFFECT_INTERFACE_H__
