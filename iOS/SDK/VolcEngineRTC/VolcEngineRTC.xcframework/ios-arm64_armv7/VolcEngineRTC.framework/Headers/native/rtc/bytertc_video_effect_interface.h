/*
 * Copyright (c) 2020 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC Video Effect Interface
*/

#pragma once

#ifndef BYTE_RTC_VIDEO_EFFECT_INTERFACE_H__
#define BYTE_RTC_VIDEO_EFFECT_INTERFACE_H__

#include <stdint.h>
#include "bytertc_defines.h"

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
 * @hidden
 * @type keytype
 * @brief 人像属性检测参数
 */
struct VideoEffectExpressionDetectConfig {
  /** 
   * @brief 是否开启年龄检测。
   */
  bool detect_age = false;
  /** 
   * @brief 是否开启性别检测。
   */
  bool detect_gender = false;
  /** 
   * @brief 是否开启表情检测。
   */
  bool detect_emotion = false;
  /** 
   * @brief 是否开启吸引力检测。
   */
  bool detect_attractiveness = false;
  /** 
   * @brief 是否开启开心程度检测。
   */
  bool detect_happiness = false;
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
 * @type keytype
 * @brief 人脸检测结果
 */
struct FaceDetectResult {
    /**
     * @hidden
     */
    static const int max_face_num = 10;
    /** 
     * @brief 人脸检测结果 <br>
     *        + 0：检测成功 <br>
     *        + !0：检测失败。详见[CV 错误码](http://ailab-cv-sdk.bytedance.com/docs/2036/99783/)。
     */
    int detect_result = 0;
    /** 
     * @brief 检测到的人脸的数量
     */
    int face_count = 0;
    /** 
     * @brief 识别到人脸的矩形框。数组的长度和检测到的人脸数量一致。参看 Rectangle{@link #Rectangle}。
     */
    Rectangle rect[max_face_num];
    /** 
     * @brief 原始图片宽度(px)
     */
    int image_width = 0;
    /** 
     * @brief 原始图片高度(px)
     */
    int image_height = 0;
};

/**  
 * @hidden
 * @type keytype
 * @brief 人像属性检测信息
 */
struct ExpressionDetectInfo {
   /** 
    * @brief 预测年龄，取值范围 (0, 100)。
    */
   float age = 0;
    /** 
    * @brief 预测为男性的概率，取值范围 (0.0, 1.0)。
    */
   float boy_prob = 0;
    /** 
    * @brief 预测的吸引力分数，取值范围 (0, 100)。
    */
   float attractive = 0;
    /** 
    * @brief 预测的微笑程度，取值范围 (0, 100)。
    */
   float happy_score = 0;
    /** 
    * @brief 预测的伤心程度，取值范围 (0, 100)。
    */
   float sad_score = 0;
    /** 
    * @brief 预测的生气程度，取值范围 (0, 100)。
    */
   float angry_score = 0;
    /** 
    * @brief 预测的吃惊程度，取值范围 (0, 100)。
    */
   float surprise_score = 0;
    /** 
    * @brief 预测的情绪激动程度，取值范围 (0, 100)。
    */
   float arousal = 0;
    /** 
    * @brief 预测的情绪正负程度，取值范围 (-100, 100)。
    */
   float valence = 0;
};

/** 
 * @hidden
 * @type keytype
 * @brief 人像属性检测结果
 */
struct ExpressionDetectResult {
    /** 
     * @hidden
     */
    static const int max_face_num = 10;
   /** 
    * @brief 特征识别结果 <br>
    *        + 0：识别成功 <br>
    *        + !0：识别失败 <br>
    */
   int detect_result = 0;
   /** 
    * @brief 识别到的人脸数量。
    */
   int face_count = 0;
   /** 
    * @brief 特征识别信息。数组的长度和检测到的人脸数量一致。参看 ExpressionDetectInfo{@link #ExpressionDetectInfo}。
    */
   ExpressionDetectInfo detect_info[max_face_num];
};

/** 
 * @type callback
 * @region 视频特效
 * @brief 人脸检测结果回调观察者
 */
class IFaceDetectionObserver {
public:
    /** 
     * @type callback
     * @region 视频特效
     * @brief 特效 SDK 进行人脸检测结果的回调。 <br>
     *        调用 RegisterFaceDetectionObserver{@link #IVideoEffect#RegisterFaceDetectionObserver} 注册了 IFaceDetectionObserver{@link #IFaceDetectionObserver}，并使用 RTC SDK 中包含的特效 SDK 进行视频特效处理时，你会收到此回调。
     * @param [in] result 人脸检测结果, 参看 FaceDetectResult{@link #FaceDetectResult}。
     */
    virtual void OnFaceDetectResult(const FaceDetectResult& result) = 0;
    /** 
     * @hidden
     * @type callback
     * @region 视频特效
     * @brief 特效 SDK 进行人像属性检测结果的回调。 <br>
     *        调用 RegisterFaceDetectionObserver{@link #IVideoEffect#RegisterFaceDetectionObserver} 注册了 IFaceDetectionObserver{@link #IFaceDetectionObserver}，并调用 SetVideoEffectExpressionDetect{@link #IVideoEffect#SetVideoEffectExpressionDetect} 开启人像属性检测后，你会收到此回调。
     * @param [in] result 人像属性检测结果, 参看 ExpressionDetectResult{@link #ExpressionDetectResult}。
     */
    virtual void OnExpressionDetectResult(const ExpressionDetectResult& result) = 0;
    
};

/** 
 * @type api
 * @brief 视频特效接口
 */
class IVideoEffect {
public:
    /** 
     * @hidden
     * @type api
     * @region 视频特效
     * @brief 设置视频特效算法模型地址，并初始化特效模块。
     * @param [in] finder ResourceFinder 地址
     * @param [in] deleter ResourceDeleter 地址
     * @return  <br>
     *      + 0: 调用成功。  <br>
     *      + 1000: 未集成特效 SDK。  <br>
     *      + 1001: 特效 SDK 不支持该功能。  <br>
     *      + < 0: 调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/5889/61813)。  <br>
     */
    virtual int SetAlgoModelResourceFinder(uintptr_t finder, uintptr_t deleter) = 0;

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
     *      + 0: 调用成功。  <br>
     *      + 1000: 未集成特效 SDK。  <br>
     *      + 1001: 特效 SDK 不支持该功能。  <br>
     *      + < 0: 调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/5889/61813)。  <br>
     * @notes 开始使用视频特效前，你必须先调用这个方法进行许可证验证
     */
    virtual int CheckLicense(void* androidContext, void* jnienv, const char* licensePath) = 0;

    /** 
     * @type api
     * @region 视频特效
     * @hidden (iOS, Android)
     * @brief 从特效 SDK 获取授权消息，用于获取在线许可证。
     * @param [in] ppmsg 授权消息字符串地址
     * @param [in] len 授权消息字符串的长度
     * @return  <br>
     *      + 0: 调用成功。  <br>
     *      + 1000: 未集成特效 SDK。  <br>
     *      + 1001: 特效 SDK 不支持该功能。  <br>
     *      + < 0: 调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/5889/61813)。  <br>
     * @notes <br>
     *        + 使用视频特效的功能前，你必须获取特效 SDK 的在线许可证。  <br>
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
     *      + 0: 调用成功。  <br>
     *      + 1000: 未集成特效 SDK。  <br>
     *      + 1001: 特效 SDK 不支持该功能。  <br>
     *      + < 0: 调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/5889/61813)。  <br>
     */
    virtual int FreeAuthMessage(char * pmsg) = 0;

    /** 
     * @type api
     * @region 视频特效
     * @brief 开启关闭视频特效
     * @param [in] enabled 是否开启特效，true: 开启，false: 关闭
     * @return  <br>
     *      + 0: 调用成功。  <br>
     *      + 1000: 未集成特效 SDK。  <br>
     *      + 1001: 特效 SDK 不支持该功能。  <br>
     *      + < 0: 调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/5889/61813)。  <br>
     * @notes 在调用CheckLicense{@link #CheckLicense}和SetAlgoModelPath{@link #SetAlgoModelPath}后调用此方法
     */
    virtual int EnableEffect(bool enabled) = 0;

    /** 
     * @type api
     * @region 视频特效
     * @brief 设置视频特效算法模型路径
     * @param [in] modelPath 模型路径
     */
    virtual void SetAlgoModelPath(const char* modelPath) = 0;
    
    /** 
     * @hidden
     * @type api
     * @region 视频特效
     * @brief 开启人像属性检测。
     * @param [in] expressionDetectConfig 人像属性检测参数，参看 VideoEffectExpressionDetectConfig{@link #VideoEffectExpressionDetectConfig}。
     * @return  <br>
     *      + 0: 调用成功。  <br>
     *      + 1000: 未集成特效 SDK。  <br>
     *      + 1001: 特效 SDK 不支持该功能。  <br>
     *      + < 0: 调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/5889/61813)。  <br>
     */
    virtual int SetVideoEffectExpressionDetect(const VideoEffectExpressionDetectConfig& expressionDetectConfig) = 0;
    
    /** 
     * @type api
     * @region 视频特效
     * @brief 设置视频特效素材包
     * @param [in] effectNodePaths 特效素材包路径数组 <br>
     *        要取消当前视频特效，将此参数设置为 null。
     * @param [in] nodeNum  <br>
     *        特效素材包个数
     * @return  <br>
     *      + 0: 调用成功。  <br>
     *      + 1000: 未集成特效 SDK。  <br>
     *      + 1001: 特效 SDK 不支持该功能。  <br>
     *      + < 0: 调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/5889/61813)。  <br>
     */
    virtual int SetEffectNodes(const char** effectNodePaths, int nodeNum) = 0;
    
    /** 
     * @hidden
     * @type api
     * @region 视频特效
     * @brief  叠加视频特效素材包。
     * @param [in] effectNodePaths 特效素材包路径数组。 
     * @param [in] nodeNum   特效素材包个数。
     * @return  <br>
     *      + 0: 调用成功。  <br>
     *      + 1000: 未集成特效 SDK。  <br>
     *      + 1001: 特效 SDK 不支持该功能。  <br>
     *      + < 0: 调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/5889/61813)。  <br>
     * @notes  该接口会在 SetEffectNodes{@link #IVideoEffect#SetEffectNodes} 设置的特效基础上叠加特效。
     */
    virtual int AppendEffectNodes(const char** effectNodePaths, int nodeNum) = 0;
    
    /** 
     * @hidden
     * @type api
     * @region 视频特效
     * @brief  移除指定的视频特效资源。
     * @param [in] effectNodePaths 特效素材包路径数组。 
     * @param [in] nodeNum   特效素材包个数。
     * @return  <br>
     *      + 0: 调用成功。  <br>
     *      + 1000: 未集成特效 SDK。  <br>
     *      + 1001: 特效 SDK 不支持该功能。  <br>
     *      + < 0: 调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/5889/61813)。  <br>
     * @notes 移除 SetEffectNodes{@link #IVideoEffect#SetEffectNodes} 或 AppendEffectNodes{@link #IVideoEffect#AppendEffectNodes} 设置的视频特效资源。
     */
    virtual int RemoveEffectNodes(const char** effectNodePaths, int nodeNum) = 0;

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
     *      + 0: 调用成功。  <br>
     *      + 1000: 未集成特效 SDK。  <br>
     *      + 1001: 特效 SDK 不支持该功能。  <br>
     *      + < 0: 调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/5889/61813)。  <br>
     */
    virtual int UpdateNode(const char* nodePath, const char* nodeKey, float nodeValue) = 0;

    /** 
     * @type api
     * @region 视频特效
     * @brief 设置颜色滤镜
     * @param [in] resPath  <br>
     *        滤镜资源包绝对路径。
     * @return  <br>
     *      + 0: 调用成功。  <br>
     *      + 1000: 未集成特效 SDK。  <br>
     *      + 1001: 特效 SDK 不支持该功能。  <br>
     *      + < 0: 调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/5889/61813)。  <br>
     */
    virtual int SetColorFilter(const char* resPath) = 0;

    /** 
     * @type api
     * @region 视频特效
     * @brief 设置已启用颜色滤镜的强度
     * @param [in] intensity  <br>
     *        滤镜强度。取值范围 [0,1]，超出范围时设置无效。
     * @return  <br>
     *      + 0: 调用成功。  <br>
     *      + 1000: 未集成特效 SDK。  <br>
     *      + 1001: 特效 SDK 不支持该功能。  <br>
     *      + < 0: 调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/5889/61813)。  <br>
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
     *        + 1000: 未集成特效 SDK。  <br>
     *        + 1001: 特效 SDK 不支持该功能。  <br>
     *        + > 40000: 调用失败，特效 SDK 授权错误，具体错误码请参考 [错误码表](https://www.volcengine.com/docs/5889/61813)。  <br>
     *        + < 0: 调用失败，特效 SDK 内部错误，具体错误码请参考 [错误码表](https://www.volcengine.com/docs/5889/61813)。  <br>
     */
    virtual int InitVirtualBackground(void* androidContext, void* jnienv, const char* licensePath,const char* modelPath) = 0;

    /** 
     * @type api
     * @region 视频特效
     * @brief 开启虚拟背景。
     * @param [in] source 虚拟背景对象，详见 VirtualBackgroundSource{@link #VirtualBackgroundSource} 。
     * @return  <br>
     *        + 0: 调用成功。  <br>
     *        + < 0: 调用失败，特效 SDK 内部错误，具体错误码请参考 [错误码表](https://www.volcengine.com/docs/5889/61813)。  <br>
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
     *        + < 0: 调用失败，具体错误码请参考 [错误码表](https://www.volcengine.com/docs/5889/61813)。  <br>
     * @notes 调用 EnableVirtualBackground{@link #EnableVirtualBackground} 开启虚拟背景后，可以调用此接口关闭虚拟背景。
     */
    virtual int DisableVirtualBackground() = 0;

    /** 
     * @type api
     * @region 视频特效
     * @brief 注册人脸检测结果回调观察者 <br>
     *        注册此观察者后，你会周期性收到 OnFaceDetectResult{@link #IFaceDetectionObserver#OnFaceDetectResult} 回调。
     * @param [in] observer 人脸检测结果回调观察者，参看 IFaceDetectionObserver{@link #IFaceDetectionObserver}。
     * @param [in] interval_ms 时间间隔。单位：ms。实际收到回调的时间间隔大于 `interval`，小于 `interval + 视频采集帧间隔`。
     * @return <br>
     *        + 0：方法调用成功  <br>
     *        + < 0：方法调用失败  <br>
     */
    virtual int RegisterFaceDetectionObserver(IFaceDetectionObserver * observer, int interval_ms) = 0;
};

}  // namespace bytertc

#endif // BYTE_RTC_VIDEO_EFFECT_INTERFACE_H__
