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
     * @brief 使用自定义图片替换视频原有背景。
     */
    kVirtualBackgroundSourceImage = 1,
};

/** 
 * @hidden for internal use only
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
struct VirtualBackgroundSource {
    /** 
     * @brief 虚拟背景类型，详见 VirtualBackgroundSourceType{@link #VirtualBackgroundSourceType} 。
     */
    VirtualBackgroundSourceType source_type = kVirtualBackgroundSourceColor;
    /** 
     * @brief 纯色背景使用的颜色。<br>
     *        格式为 0xAARRGGBB 。
     */
    uint32_t source_color = 0xFFFFFFFF;
    /** 
     * @brief 自定义背景图片的绝对路径。
     *       + 支持的格式为 jpg、jpeg、png。  <br>
     *       + 图片分辨率超过 1080P 时，图片会被等比缩放至和视频一致。  <br>
     *       + 图片和视频宽高比一致时，图片会被直接缩放至和视频一致。  <br>
     *       + 图片和视频长宽比不一致时，为保证图片内容不变形，图片按短边缩放至与视频帧一致，使图片填满视频帧，对多出的高或宽进行剪裁。  <br>
     *       + 自定义图片带有局部透明效果时，透明部分由黑色代替。
     */
    const char* source_path = nullptr;
};
/** 
 * @type keytype
 * @brief 人脸检测结果
 */
struct FaceDetectResult {
    /** 
     * @brief 人脸信息存储上限，最多可存储 10 个人脸信息
     */
    static const int max_face_num = 10;
    /** 
     * @brief 人脸检测结果 <br>
     *        + 0：检测成功 <br>
     *        + !0：检测失败。详见[错误码](https://www.volcengine.com/docs/6705/102042)。
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
    /** 
     * @brief 进行人脸识别的视频帧的时间戳。
     */
    int64_t frame_timestamp_us = 0;
};

/** 
 * @hidden for internal use only
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
 * @hidden for internal use only
 * @type keytype
 * @brief 人像属性检测结果
 */
struct ExpressionDetectResult {
    /** 
     * @brief 人脸信息存储上限，最多可存储 10 个人脸信息
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
     *        调用 enableFaceDetection{@link #IVideoEffect#enableFaceDetection} 注册了 IFaceDetectionObserver{@link #IFaceDetectionObserver}，并使用 RTC SDK 中包含的特效 SDK 进行视频特效处理时，你会收到此回调。
     * @param [in] result 人脸检测结果, 参看 FaceDetectResult{@link #FaceDetectResult}。
     */
    virtual void onFaceDetectResult(const FaceDetectResult& result) = 0;
    /** 
     * @hidden for internal use only
     * @type callback
     * @region 视频特效
     * @brief 特效 SDK 进行人像属性检测结果的回调。 <br>
     *        调用 registerFaceDetectionObserver{@link #IVideoEffect#registerFaceDetectionObserver} 注册了 IFaceDetectionObserver{@link #IFaceDetectionObserver}，并调用 setVideoEffectExpressionDetect{@link #IVideoEffect#setVideoEffectExpressionDetect} 开启人像属性检测后，你会收到此回调。
     * @param [in] result 人像属性检测结果, 参看 ExpressionDetectResult{@link #ExpressionDetectResult}。
     */
    virtual void onExpressionDetectResult(const ExpressionDetectResult& result) = 0;

};

/** 
 * @type api
 * @region 音视频处理
 * @brief 高级视频特效。
 */
class IVideoEffect {
public:
    /** 
     * @type api
     * @brief 检查视频特效证书，设置算法模型路径，并初始化特效模块。
     * @param [in] license_file_path 证书文件的绝对路径，用于鉴权。
     * @param [in] algo_model_dir 算法模型绝对路径，即存放特效 SDK 所有算法模型的目录。
     * @return  <br>
     *      + 0: 调用成功。
     *      + –1000: 未集成特效 SDK。
     *      + –1002: 特效 SDK 版本不兼容。
     *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
     */
    virtual int initCVResource(const char* license_file_path, const char* algo_model_dir) = 0;

    /** 
     * @hidden for internal use only
     * @type api
     * @brief 设置视频特效算法模型地址，并初始化特效模块。
     * @param [in] finder ResourceFinder 地址
     * @param [in] deleter ResourceDeleter 地址
     * @return  <br>
     *      + 0: 调用成功。
     *      + –1000: 未集成特效 SDK。
     *      + –1001: 特效 SDK 不支持该功能。
     *      + –1002: 特效 SDK 版本不兼容。
     *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
     */
    virtual int setAlgoModelResourceFinder(uintptr_t finder, uintptr_t deleter) = 0;

    /** 
     * @deprecated since 3.50 and will be deleted in 3.55, use initCVResource{@link #IVideoEffect#initCVResource} instead.
     * @type api
     * @region 视频特效
     * @brief 设置视频特效算法模型路径
     * @param [in] modelPath 模型路径
     */
    virtual void setAlgoModelPath(const char* modelPath) = 0;

    /** 
     * @deprecated since 3.50 and will be deleted in 3.55, use initCVResource{@link #IVideoEffect#initCVResource} instead.
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
     *      + < 0: 调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。  <br>
     * @notes 开始使用视频特效前，你必须先调用这个方法进行许可证验证
     */
    virtual int checkLicense(void* androidContext, void* jnienv, const char* licensePath) = 0;

    /** 
     * @type api
     * @region 视频特效
     * @hidden(iOS, Android)
     * @brief 从特效 SDK 获取授权消息，用于获取在线许可证。
     * @param [in] ppmsg 授权消息字符串地址
     * @param [in] len 授权消息字符串的长度
     * @return  <br>
     *      + 0: 调用成功。
     *      + –1000: 未集成特效 SDK。
     *      + –1001: 特效 SDK 不支持该功能。
     *      + –1002: 特效 SDK 版本不兼容。
     *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
     * @notes <br>
     *        + 使用视频特效的功能前，你必须获取特效 SDK 的在线许可证。  <br>
     *        + 通过此接口获取授权消息后，你必须参考 [在线授权说明](https://www.volcengine.com/docs/6705/102012) 自行实现获取在线许可证的业务逻辑。获取许可证后，你必须调用 initCVResource{@link #IVideoEffect#initCVResource} 确认许可证有效。然后，你才可以使用 CV 功能。  <br>
     *        + 获取授权消息后，调用 freeAuthMessage{@link #freeAuthMessage} 释放内存。
     */
    virtual int getAuthMessage(char ** ppmsg, int * len) = 0;
    /** 
     * @type api
     * @region 视频特效
     * @hidden(iOS,Android)
     * @brief 使用完授权消息字符串后，释放内存。
     * @param [in] pmsg getAuthMessage 返回的授权消息字符串。
     * @return  <br>
     *      + 0: 调用成功。
     *      + –1000: 未集成特效 SDK。
     *      + –1001: 特效 SDK 不支持该功能。
     *      + –1002: 特效 SDK 版本不兼容。
     *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
     */
    virtual int freeAuthMessage(char * pmsg) = 0;

    /** 
     * @deprecated since 3.50 and will be deleted in 3.55, use enableVideoEffect{@link #IVideoEffect#enableVideoEffect} instead.
     * @type api
     * @region 视频特效
     * @brief 开启关闭视频特效
     * @param [in] enabled 是否开启特效，true: 开启，false: 关闭
     * @return  <br>
     *      + 0: 调用成功。  <br>
     *      + 1000: 未集成特效 SDK。  <br>
     *      + 1001: 特效 SDK 不支持该功能。  <br>
     *      + < 0: 调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。  <br>
     * @notes 在调用 CheckLicense{@link #checkLicense} 和 SetAlgoModelPath{@link #setAlgoModelPath} 后调用此方法。
     */
    virtual int enableEffect(bool enabled) = 0;
    
    /** 
     * @hidden for internal use only
     * @region 视频特效
     * @brief 返回视频特效句柄。私有接口
     */
    virtual void* getEffectHandle() = 0;

    /** 
     * @type api
     * @brief 开启高级美颜、滤镜等视频特效。
     * @return  <br>
     *      + 0: 调用成功。
     *      + –1000: 未集成特效 SDK。
     *      + –1001: 特效 SDK 不支持该功能。
     *      + –1002: 特效 SDK 版本不兼容。
     *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
     * @notes  <br>
     *      + 调用本方法前，必须先调用 initCVResource{@link #IVideoEffect#initCVResource} 进行初始化。
     *      + 调用该方法后，特效不直接生效，你还需调用 setEffectNodes{@link #IVideoEffect#setEffectNodes} 设置视频特效素材包或调用 setColorFilter{@link #IVideoEffect#setColorFilter} 设置滤镜。
     *      + 调用 disableVideoEffect{@link #IVideoEffect#disableVideoEffect} 关闭视频特效。
     */
    virtual int enableVideoEffect() = 0;

    /** 
     * @type api
     * @brief 关闭视频特效。
     * @return  <br>
     *      + 0: 调用成功。
     *      + –1000: 未集成特效 SDK。
     *      + –1001: 特效 SDK 不支持该功能。
     *      + –1002: 特效 SDK 版本不兼容。
     *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
     * @notes 调用 enableVideoEffect{@link #IVideoEffect#enableVideoEffect} 开启视频特效。
     */
    virtual int disableVideoEffect() = 0;

    /** 
     * @type api
     * @brief 设置视频特效素材包。
     * @param [in] effectNodePaths 特效素材包绝对路径数组。
     *        要取消当前视频特效，将此参数设置为 null。
     * @param [in] nodeNum 特效素材包个数。
     * @return  <br>
     *      + 0: 调用成功。
     *      + –1000: 未集成特效 SDK。
     *      + –1001: 特效 SDK 不支持该功能。
     *      + –1002: 特效 SDK 版本不兼容。
     *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
     * @notes 调用本方法前，必须先调用 enableVideoEffect{@link #IVideoEffect#enableVideoEffect}。
     */
    virtual int setEffectNodes(const char** effectNodePaths, int nodeNum) = 0;

    /** 
     * @hidden for internal use only
     * @type api
     * @brief  叠加视频特效素材包。
     * @param [in] effectNodePaths 特效素材包绝对路径数组。
     * @param [in] nodeNum 特效素材包个数。
     * @return  <br>
     *      + 0: 调用成功。
     *      + –1000: 未集成特效 SDK。
     *      + –1001: 特效 SDK 不支持该功能。
     *      + –1002: 特效 SDK 版本不兼容。
     *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
     * @notes 该接口会在 setEffectNodes{@link #IVideoEffect#setEffectNodes} 设置的特效基础上叠加特效。
     */
    virtual int appendEffectNodes(const char** effectNodePaths, int nodeNum) = 0;

    /** 
     * @hidden for internal use only
     * @type api
     * @brief  移除指定的视频特效资源。
     * @param [in] effectNodePaths 特效素材包绝对路径数组。
     * @param [in] nodeNum 特效素材包个数。
     * @return  <br>
     *      + 0: 调用成功。
     *      + –1000: 未集成特效 SDK。
     *      + –1001: 特效 SDK 不支持该功能。
     *      + –1002: 特效 SDK 版本不兼容。
     *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
     * @notes 移除 setEffectNodes{@link #IVideoEffect#SetEffectNodes} 或 appendEffectNodes{@link #IVideoEffect#appendEffectNodes} 设置的视频特效资源。
     */
    virtual int removeEffectNodes(const char** effectNodePaths, int nodeNum) = 0;

    /** 
     * @deprecated since 3.50 and will be deleted in 3.55, use updateEffectNode{@link #IVideoEffect#updateEffectNode} instead.
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
     *      + < 0: 调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。  <br>
     */
    virtual int updateNode(const char* nodePath, const char* nodeKey, float nodeValue) = 0;

    /** 
     * @type api
     * @brief 设置特效强度。
     * @param [in] effectNodePath 特效素材包绝对路径，参考[素材包结构说明](https://www.volcengine.com/docs/6705/102039)。
     * @param [in] nodeKey 需要设置的素材 key 名称，参考[素材 key 对应说明](https://www.volcengine.com/docs/6705/102041)。
     * @param [in] nodeValue 特效强度值，取值范围 [0,1]，超出范围时设置无效。
     * @return  <br>
     *      + 0: 调用成功。
     *      + –1000: 未集成特效 SDK。
     *      + –1001: 特效 SDK 不支持该功能。
     *      + –1002: 特效 SDK 版本不兼容。
     *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
     */
    virtual int updateEffectNode(const char* effectNodePath, const char* nodeKey, float nodeValue) = 0;

    /** 
     * @type api
     * @brief 设置颜色滤镜。
     * @param [in] resPath 滤镜资源包绝对路径。
     * @return  <br>
     *      + 0: 调用成功。
     *      + –1000: 未集成特效 SDK。
     *      + –1001: 特效 SDK 不支持该功能。
     *      + –1002: 特效 SDK 版本不兼容。
     *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
     * @notes 调用 setColorFilterIntensity{@link #IVideoEffect#setColorFilterIntensity} 设置已启用颜色滤镜的强度。设置强度为 0 时即关闭颜色滤镜。
     */
    virtual int setColorFilter(const char* resPath) = 0;

    /** 
     * @type api
     * @brief 设置已启用颜色滤镜的强度。
     * @param [in] intensity 滤镜强度。取值范围 [0,1]，超出范围时设置无效。
     *                  当设置滤镜强度为 0 时即关闭颜色滤镜。
     * @return  <br>
     *      + 0: 调用成功。
     *      + –1000: 未集成特效 SDK。
     *      + –1001: 特效 SDK 不支持该功能。
     *      + –1002: 特效 SDK 版本不兼容。
     *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
     */
    virtual int setColorFilterIntensity(float intensity) = 0;
    
    /** 
     * @hidden for internal use only
     * @type api
     * @brief 私有接口，设置视频特效素材包。
     * @param [in] stickerPath 特效素材包绝对路径。
     *        要取消当前视频特效，将此参数设置为 null。
     * @return  <br>
     *      + 0: 调用成功。
     *      + –1000: 未集成特效 SDK。
     *      + –1001: 特效 SDK 不支持该功能。
     *      + –1002: 特效 SDK 版本不兼容。
     *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
     * @notes 调用本方法前，必须先调用 enableVideoEffect{@link #IVideoEffect#enableVideoEffect}。
     */
    virtual int ApplyStickerEffect(const char* stickerPath) = 0;

    /** 
     * @hidden(Linux)
     * @type api
     * @brief 将摄像头采集画面中的人像背景替换为指定图片或纯色背景。
     * @param [in] bg_sticker_path 背景贴纸特效素材绝对路径。
     * @param [in] source 背景贴纸对象，参看 VirtualBackgroundSource{@link #VirtualBackgroundSource}。
     * @return  <br>
     *      + 0: 调用成功。
     *      + –1000: 未集成特效 SDK。
     *      + –1001: 特效 SDK 不支持该功能。
     *      + –1002: 特效 SDK 版本不兼容。
     *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
     * @notes <br>
     *      + 调用本方法前，必须先调用 initCVResource{@link #IVideoEffect#initCVResource} 进行初始化。
     *      + 调用 disableVirtualBackground{@link #IVideoEffect#disableVirtualBackground} 关闭虚拟背景。
     */
    virtual int enableVirtualBackground(const char* bg_sticker_path, const VirtualBackgroundSource& source) = 0;

    /** 
     * @hidden(Linux)
     * @type api
     * @brief 关闭虚拟背景。
     * @return  <br>
     *      + 0: 调用成功。
     *      + –1000: 未集成特效 SDK。
     *      + –1001: 特效 SDK 不支持该功能。
     *      + –1002: 特效 SDK 版本不兼容。
     *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
     * @notes 调用 enableVirtualBackground{@link #IVideoEffect#enableVirtualBackground} 开启虚拟背景后，可以调用此接口关闭虚拟背景。
     */
    virtual int disableVirtualBackground() = 0;

    /** 
     * @hidden for internal use only
     * @type api
     * @brief 开启人像属性检测。
     * @param [in] expressionDetectConfig 人像属性检测参数，参看 VideoEffectExpressionConfig{@link #VideoEffectExpressionConfig}。
     * @return  <br>
     *      + 0: 调用成功。
     *      + –1000: 未集成特效 SDK。
     *      + –1001: 特效 SDK 不支持该功能。
     *      + –1002: 特效 SDK 版本不兼容。
     *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
     */
    virtual int setVideoEffectExpressionDetect(const VideoEffectExpressionDetectConfig& expressionDetectConfig) = 0;

    /** 
     * @deprecated since 3.50 and will be deleted in 3.55, use enableFaceDetection{@link #IVideoEffect#enableFaceDetection} and disableFaceDetection{@link #IVideoEffect#disableFaceDetection} instead.
     * @type api
     * @brief 注册人脸检测结果回调观察者。
     *        注册此观察者后，你会周期性收到 onFaceDetectResult{@link #IFaceDetectionObserver#onFaceDetectResult} 回调。
     * @param [in] observer 人脸检测结果回调观察者，参看 IFaceDetectionObserver{@link #IFaceDetectionObserver}。
     * @param [in] interval_ms 时间间隔，必须大于 0。单位：ms。实际收到回调的时间间隔大于 `interval`，小于 `interval+视频采集帧间隔`。
     * @return  <br>
     *      + 0: 调用成功。
     *      + –1000: 未集成特效 SDK。
     *      + –1001: 特效 SDK 不支持该功能。
     *      + –1002: 特效 SDK 版本不兼容。
     *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
     */
    virtual int registerFaceDetectionObserver(IFaceDetectionObserver* observer, int interval_ms) = 0;

    /** 
     * @type api
     * @brief 开启人脸识别功能，并设置人脸检测结果回调观察者。
     *        此观察者后，你会周期性收到 onFaceDetectResult{@link #IFaceDetectionObserver#onFaceDetectResult} 回调。
     * @param [in] observer 人脸检测结果回调观察者，参看 IFaceDetectionObserver{@link #IFaceDetectionObserver}。
     * @param [in] interval_ms 两次回调之间的最小时间间隔，必须大于 0，单位为毫秒。实际收到回调的时间间隔大于 interval_ms，小于 interval_ms+视频采集帧间隔。
     * @param [in] faceModelPath 人脸检测算法模型文件路径，一般为 ttfacemodel 文件夹中 tt_face_vXXX.model 文件的绝对路径。
     * @return  <br>
     *      + 0: 调用成功。
     *      + –1000: 未集成特效 SDK。
     *      + –1001: 特效 SDK 不支持该功能。
     *      + –1002: 特效 SDK 版本不兼容。
     *      + -1004: 初始化中，初始化完成后启动此功能。
     *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
     */
    virtual int enableFaceDetection(IFaceDetectionObserver* observer, unsigned int interval_ms, const char* faceModelPath) = 0;

    /** 
     * @type api
     * @brief 关闭人脸识别功能。
     * @return  <br>
     *      + 0: 调用成功。
     *      + –1000: 未集成特效 SDK。
     *      + –1001: 特效 SDK 不支持该功能。
     *      + –1002: 特效 SDK 版本不兼容。
     *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
     */
    virtual int disableFaceDetection() = 0;

    /** 
     * @deprecated since 3.50 and will be deleted in 3.55, use enableVirtualBackground{@link #IVideoEffect#enableVirtualBackground} instead.
     * @type api
     * @region 视频特效
     * @brief 将摄像头采集画面中的人像背景替换为指定图片或纯色背景。
     *        若要取消背景特效，将背景贴纸特效素材路径设置为null。
     * @param [in] modelPath 传入背景贴纸特效素材路径。  <br>
     * @param [in] source 设置背景特效图片的本地路径。参看 VirtualBackgroundSource{@link #VirtualBackgroundSource}。  <br>
     * @return  <br>
     *        + 0：调用成功。  <br>
     *        + 1000：未集成特效 SDK。  <br>
     *        + 1001：特效 SDK 不支持该功能。  <br>
     *        + < 0：调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
     * @notes  <br>
     *        调用此接口前需依次调用以下接口：<br>
     * 1、检查视频特效许可证 checkLicense{@link #IVideoEffect#checkLicense}；<br>
     * 2、设置视频特效算法模型路径 setAlgoModelPath{@link #IVideoEffect#setAlgoModelPath}；<br>
     * 3、开启视频特效 enableEffect{@link #IVideoEffect#enableEffect}。
     */
    virtual int setBackgroundSticker(const char* modelPath, const VirtualBackgroundSource& source) = 0;

};

}  // namespace bytertc

#endif // BYTE_RTC_VIDEO_EFFECT_INTERFACE_H__
