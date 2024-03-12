/*
 * Copyright (c) 2020 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC Video Effect Interface
*/

#pragma once

#include <stdint.h>
#include "bytertc_defines.h"

namespace bytertc {
/**
 * @locale zh
 * @type keytype
 * @brief 虚拟背景类型。
 */
/**
 * @locale en
 * @type keytype
 * @brief Virtual background type.
 */
enum VirtualBackgroundSourceType {
    /**
     * @locale zh
     * @brief 使用纯色背景替换视频原有背景。
     */
    /**
     * @locale en
     * @brief Replace the original background with a solid color.
     */
    kVirtualBackgroundSourceTypeColor = 0,
    /**
     * @locale zh
     * @brief 使用自定义图片替换视频原有背景。
     */
    /**
     * @locale en
     * @brief Replace the original background with the specified image.
     */
    kVirtualBackgroundSourceTypeImage = 1,
};

/**
 * @locale zh
 * @hidden for internal use only
 * @type keytype
 * @brief 人像属性检测参数
 */
/**
 * @locale en
 * @hidden for internal use only
 * @type keytype
 * @brief Expression detection configuration
 */
struct VideoEffectExpressionDetectConfig {
  /**
   * @locale zh
   * @brief 是否开启年龄检测。
   */
  /**
   * @locale en
   * @brief Whether to enable age detection.
   */
  bool detect_age = false;
  /**
   * @locale zh
   * @brief 是否开启性别检测。
   */
  /**
   * @locale en
   * @brief Whether to enable gender detection.
   */
  bool detect_gender = false;
  /**
   * @locale zh
   * @brief 是否开启表情检测。
   */
  /**
   * @locale en
   * @brief Whether to enable emotion detection.
   */
  bool detect_emotion = false;
  /**
   * @locale zh
   * @brief 是否开启吸引力检测。
   */
  /**
   * @locale en
   * @brief Whether to enable attractiveness detection.
   */
  bool detect_attractiveness = false;
  /**
   * @locale zh
   * @brief 是否开启开心程度检测。
   */
  /**
   * @locale en
   * @brief Whether to enable happiness detection.
   */
  bool detect_happiness = false;
};

/**
 * @locale zh
 * @type keytype
 * @brief 虚拟背景对象。
 */
/**
 * @locale en
 * @type keytype
 * @brief Virtual background object.
 */
struct VirtualBackgroundSource {
    /**
     * @locale zh
     * @brief 虚拟背景类型，详见 VirtualBackgroundSourceType{@link #VirtualBackgroundSourceType} 。
     */
    /**
     * @locale en
     * @brief See VirtualBackgroundSourceType{@link #VirtualBackgroundSourceType}.
     */
    VirtualBackgroundSourceType source_type = kVirtualBackgroundSourceTypeColor;
    /**
     * @locale zh
     * @brief 纯色背景使用的颜色。<br>
     *        格式为 0xAARRGGBB 。
     */
    /**
     * @locale en
     * @brief The solid color of the background. <br>
     *        The format is 0xAARRGGBB. 
     */
    uint32_t source_color = 0xFFFFFFFF;
    /**
     * @locale zh
     * @brief 自定义背景图片的绝对路径。<br>
     *       + 支持的格式为 jpg、jpeg、png。  <br>
     *       + 图片分辨率超过 1080P 时，图片会被等比缩放至和视频一致。  <br>
     *       + 图片和视频宽高比一致时，图片会被直接缩放至和视频一致。  <br>
     *       + 图片和视频长宽比不一致时，为保证图片内容不变形，图片按短边缩放至与视频帧一致，使图片填满视频帧，对多出的高或宽进行剪裁。  <br>
     *       + 自定义图片带有局部透明效果时，透明部分由黑色代替。
     */
    /**
     * @locale en
     * @brief The absolute path of the specified image.<br>
     *       + You can upload a .JPG, .PNG, or .JPEG file.  <br>
     *       + The image with a resolution higher than 1080p(Full HD) will be rescaled proportionally to fit in the video.  <br>
     *       + If the image's aspect ratio matches the video's, the image will be rescaled proportionally to fit in the video.  <br>
     *       + If the image’s aspect ratio doesn't match the video's, the shortest side (either height or width) of the image will be stretched proportionally to match the video. Then the image will be cropped to fill in the video.  <br>
     *       + The transparent area in the image will be filled with black.
     */
    const char* source_path = nullptr;
};
/**
 * @locale zh
 * @type keytype
 * @brief 人脸检测结果
 */
/**
 * @locale en
 * @type keytype
 * @brief Face Detection Result
 */
struct FaceDetectResult {
    /**
     * @locale zh
     * @brief 人脸信息存储上限，最多可存储 10 个人脸信息
     */
    /**
     * @locale en
     * @brief Face information storage limit, up to 10 faces can be stored.
     */
    static const int max_face_num = 10;
    /**
     * @locale zh
     * @brief 人脸检测结果 <br>
     *        + 0：检测成功 <br>
     *        + !0：检测失败。详见[错误码](https://www.volcengine.com/docs/6705/102042)。
     */
    /**
     * @locale en
     * @brief Face Detection Result <br>
     *        + 0: Success <br>
     *        + !0: Failure. See [Error Code Table](https://docs.byteplus.com/en/effects/docs/error-code-table).
     */
    int detect_result = 0;
    /**
     * @locale zh
     * @brief 检测到的人脸的数量
     */
    /**
     * @locale en
     * @brief Number of the detected face
     */
    int face_count = 0;
    /**
     * @locale zh
     * @brief 识别到人脸的矩形框。数组的长度和检测到的人脸数量一致。参看 Rectangle{@link #Rectangle}。
     */
    /**
     * @locale en
     * @brief The face recognition rectangles. The length of the array is the same as the number of detected faces. See Rectangle{@link #Rectangle}.
     */
    Rectangle rect[max_face_num];
    /**
     * @locale zh
     * @brief 原始图片宽度(px)
     */
    /**
     * @locale en
     * @brief Width of the original image (px)
     */
    int image_width = 0;
    /**
     * @locale zh
     * @brief 原始图片高度(px)
     */
    /**
     * @locale en
     * @brief Height of the original image (px)
     */
    int image_height = 0;
    /**
     * @locale zh
     * @brief 进行人脸识别的视频帧的时间戳。
     */
    /**
     * @locale en
     * @brief The time stamp of the video frame using face detection.
     */
    int64_t frame_timestamp_us = 0;
};

/**
 * @locale zh
 * @hidden for internal use only
 * @type keytype
 * @brief 人像属性检测信息
 */
/**
 * @locale en
 * @hidden for internal use only
 * @type keytype
 * @brief Expression detect information
 */
struct ExpressionDetectInfo {
   /**
    * @locale zh
    * @brief 预测年龄，取值范围 (0, 100)。
    */
   /**
    * @locale en
    * @brief The estimated age in range of (0, 100).
    */
    float age = 0;
    /**
    * @locale zh
    * @brief 预测为男性的概率，取值范围 (0.0, 1.0)。
    */
   /**
    * @locale en
    * @brief The estimated probability of being a male in range of (0.0, 1.0).
    */
    float boy_prob = 0;
    /**
    * @locale zh
    * @brief 预测的吸引力分数，取值范围 (0, 100)。
    */
   /**
    * @locale en
    * @brief The estimated attractiveness in range of (0, 100).
    */
    float attractive = 0;
    /**
    * @locale zh
    * @brief 预测的微笑程度，取值范围 (0, 100)。
    */
   /**
    * @locale en
    * @brief The estimated happy score in range of (0, 100).
    */
    float happy_score = 0;
    /**
    * @locale zh
    * @brief 预测的伤心程度，取值范围 (0, 100)。
    */
   /**
    * @locale en
    * @brief The estimated sad score in range of (0, 100).
    */
    float sad_score = 0;
    /**
    * @locale zh
    * @brief 预测的生气程度，取值范围 (0, 100)。
    */
   /**
    * @locale en
    * @brief The estimated angry score in range of (0, 100).
    */
    float angry_score = 0;
    /**
    * @locale zh
    * @brief 预测的吃惊程度，取值范围 (0, 100)。
    */
   /**
    * @locale en
    * @brief The estimated surprise score in range of (0, 100).
    */
    float surprise_score = 0;
    /**
    * @locale zh
    * @brief 预测的情绪激动程度，取值范围 (0, 100)。
    */
   /**
    * @locale en
    * @brief The estimated emotional arousal in range of (0, 100).
    */
    float arousal = 0;
    /**
    * @locale zh
    * @brief 预测的情绪正负程度，取值范围 (-100, 100)。
    */
   /**
    * @locale en
    * @brief The estimated emotional valence in range of (-100, 100).
    */
    float valence = 0;
};

/**
 * @locale zh
 * @hidden for internal use only
 * @type keytype
 * @brief 人像属性检测结果
 */
/**
 * @locale en
 * @hidden for internal use only
 * @type keytype
 * @brief Expression detection result
 */
struct ExpressionDetectResult {
    /**
     * @locale zh
     * @brief 人脸信息存储上限，最多可存储 10 个人脸信息
     */
    /**
     * @locale en
     * @brief Face information storage limit, up to 10 faces can be stored.
     */
    static const int max_face_num = 10;
   /**
    * @locale zh
    * @brief 特征识别结果 <br>
    *        + 0：识别成功 <br>
    *        + !0：识别失败 
    */
   /**
    * @locale en
    * @brief Expression detection result <br>
    *        + 0: Success <br>
    *        + !0: Failure 
    */
    int detect_result = 0;
   /**
    * @locale zh
    * @brief 识别到的人脸数量。
    */
   /**
    * @locale en
    * @brief The number of detected faces.
    */
    int face_count = 0;
   /**
    * @locale zh
    * @brief 特征识别信息。数组的长度和检测到的人脸数量一致。参看 ExpressionDetectInfo{@link #ExpressionDetectInfo}。
    */
   /**
    * @locale en
    * @brief Expression detection information. The length of the array is the same as the number of detected faces. See ExpressionDetectInfo{@link #ExpressionDetectInfo}.
    */
    ExpressionDetectInfo detect_info[max_face_num];
};

/**
 * @locale zh
 * @type callback
 * @region 视频特效
 * @brief 人脸检测结果回调观察者<br>
 * 注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。
 */
/**
 * @locale en
 * @type callback
 * @region Video Effect
 * @brief Face detection observer<br>
 * Note: Callback functions are thrown synchronously in a non-UI thread within the SDK. Therefore, you must not perform any time-consuming operations or direct UI operations within the callback function, as this may cause the app to crash.
 */
class IFaceDetectionObserver {
public:
    /**
     * @locale zh
     * @type callback
     * @region 视频特效
     * @brief 特效 SDK 进行人脸检测结果的回调。 <br>
     *        调用 enableFaceDetection{@link #IVideoEffect#enableFaceDetection} 注册了 IFaceDetectionObserver{@link #IFaceDetectionObserver}，并使用 RTC SDK 中包含的特效 SDK 进行视频特效处理时，你会收到此回调。
     * @param result 人脸检测结果, 参看 FaceDetectResult{@link #FaceDetectResult}。
     */
    /**
     * @locale en
     * @type callback
     * @region Video Effect
     * @brief Callback of the result of face detection with Effect SDK. <br>
     *        After calling enableFaceDetection{@link #IVideoEffect#enableFaceDetection} and using the Effect SDK integrated in the RTC SDK, you will receive this callback.
     * @param result Face detection result. See FaceDetectResult{@link #FaceDetectResult}.
    */
    virtual void onFaceDetectResult(const FaceDetectResult& result) = 0;
    /**
     * @locale zh
     * @hidden for internal use only
     * @type callback
     * @region 视频特效
     * @brief 特效 SDK 进行人像属性检测结果的回调。 <br>
     *        调用 registerFaceDetectionObserver{@link #IVideoEffect#registerFaceDetectionObserver} 注册了 IFaceDetectionObserver{@link #IFaceDetectionObserver}，并调用 setVideoEffectExpressionDetect{@link #IVideoEffect#setVideoEffectExpressionDetect} 开启人像属性检测后，你会收到此回调。
     * @param result 人像属性检测结果, 参看 ExpressionDetectResult{@link #ExpressionDetectResult}。
     */
    /**
     * @locale en
     * @hidden for internal use only
     * @type callback
     * @region Video Effect
     * @brief Callback of the result of face detection with Effect SDK. <br>
     *        After calling registerFaceDetectionObserver{@link #IVideoEffect#registerFaceDetectionObserver} and setVideoEffectExpressionDetect{@link #IVideoEffect#setVideoEffectExpressionDetect}, you will receive this callback.
     * @param result Expression detection result. See ExpressionDetectResult{@link #ExpressionDetectResult}.
    */
    virtual void onExpressionDetectResult(const ExpressionDetectResult& result) = 0;

};

/**
 * @locale zh
 * @type api
 * @region 音视频处理
 * @brief 高级视频特效，参看[集成指南](https://www.volcengine.com/docs/6348/114717)。
 */
/**
 * @locale en
 * @type api
 * @region Audio & Video Processing
 * @brief Advanced video effects. See [integration guide](https://docs.byteplus.com/byteplus-rtc/docs/114717).
 */
class IVideoEffect {
public:
    virtual ~IVideoEffect() = default;

    /**
     * @locale zh
     * @type api
     * @brief 检查视频特效证书，设置算法模型路径，并初始化特效模块。
     * @param license_file_path 证书文件的绝对路径，用于鉴权。
     * @param algo_model_dir 算法模型绝对路径，即存放特效 SDK 所有算法模型的目录。
     * @return  
     *      + 0: 调用成功。<br>
     *      + –1000: 未集成特效 SDK。<br>
     *      + –1002: 特效 SDK 版本不兼容。<br>
     *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
     */
    /**
     * @locale en
     * @type api
     * @brief Checks video effect license, sets the video effect resource model path, and initializes video effect.
     * @param license_file_path The absolute path of the license file for authorization.
     * @param algo_model_dir The absolute path of the Effects SDK's models file.
     * @return  
     *      + 0: Success.<br>
     *      + –1000: The Effects SDK is not integrated.<br>
     *      + –1002: Your Effects SDK's version is incompatible.<br>
     *      + < 0: Other error. See [error code table](https://docs.byteplus.com/effects/docs/error-code-table) for specific instructions.
     */
    virtual int initCVResource(const char* license_file_path, const char* algo_model_dir) = 0;

    /**
     * @locale zh
     * @hidden for internal use only
     * @type api
     * @brief 设置视频特效算法模型地址，并初始化特效模块。
     * @param finder ResourceFinder 地址
     * @param deleter ResourceDeleter 地址
     * @return  
     *      + 0: 调用成功。<br>
     *      + –1000: 未集成特效 SDK。<br>
     *      + –1001: 特效 SDK 不支持该功能。<br>
     *      + –1002: 特效 SDK 版本不兼容。<br>
     *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
     */
    /**
     * @locale en
     * @hidden for internal use only
     * @type api
     * @brief  Sets the video effects resource finder path and initializes video effects.
     * @param finder ResourceFinder path
     * @param deleter ResourceDeleter path
     * @return  
     *      + 0: Success.<br>
     *      + –1000: The Effects SDK is not integrated.<br>
     *      + –1001: This API is unavailable for your Effects SDK.<br>
     *      + –1002: Your Effects SDK's version is incompatible.<br>
     *      + < 0: Other error. See [error code table](https://docs.byteplus.com/effects/docs/error-code-table) for specific instructions.
     */
    virtual int setAlgoModelResourceFinder(uintptr_t finder, uintptr_t deleter) = 0;

    /**
     * @locale zh
     * @deprecated since 3.50 and will be deleted in 3.55, use initCVResource{@link #IVideoEffect#initCVResource} instead.
     * @type api
     * @region 视频特效
     * @brief 设置视频特效算法模型路径
     * @param model_path 模型路径
     */
    /**
     * @locale en
     * @deprecated since 3.50 and will be deleted in 3.55, use initCVResource{@link #IVideoEffect#initCVResource} instead.
     * @type api
     * @region Video Effects
     * @brief Sets the video effects algorithm model path
     * @param model_path  Model path
     */
    virtual void setAlgoModelPath(const char* model_path) = 0;

    /**
     * @locale zh
     * @deprecated since 3.50 and will be deleted in 3.55, use initCVResource{@link #IVideoEffect#initCVResource} instead.
     * @type api
     * @region 视频特效
     * @brief 视频特效许可证检查
     * @param android_context  <br>
     *        Android Context 对象指针(jobject 类型)。Android 以外平台传入 nullptr
     * @param jnienv Android  <br>
     *        JNIEnv 指针。Android 以外平台传入 nullptr
     * @param license_path 许可证文件绝对路径
     * @return  
     *      + 0: 调用成功。  <br>
     *      + 1000: 未集成特效 SDK。  <br>
     *      + 1001: 特效 SDK 不支持该功能。  <br>
     *      + < 0: 调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。  
     * @note 开始使用视频特效前，你必须先调用这个方法进行许可证验证
     */
    /**
     * @locale en
     * @deprecated since 3.50 and will be deleted in 3.55, use initCVResource{@link #IVideoEffect#initCVResource} instead.
     * @type api
     * @region Video Effects
     * @brief  Video effects license check
     * @param android_context   <br>
     *        Android Context object pointer (jobject type). The nullptr
     * @param jnienv Android <br>
     *        JNIEnv pointer is passed to platforms other than Android. Incoming nullptr
     * @param license_path  Absolute path of license file from platforms other than Android
     * @return   
     *       + 0: call succeeded <br>
     *       + 1000: not integrated cvsdk <br>
     *       + 1001: cv function is not supported in this RTC version <br>
     *       + < 0: Failure Please refer to [Error Code Table](https://docs.byteplus.com/en/effects/docs/error-code-table).
     * @note  Before you start using video effects, you must first call this method for license verification
     */
    virtual int checkLicense(void* android_context, void* jnienv, const char* license_path) = 0;

    /**
     * @locale zh
     * @type api
     * @region 视频特效
     * @hidden(iOS, Android)
     * @brief 从特效 SDK 获取授权消息，用于获取在线许可证。
     * @param ppmsg 授权消息字符串地址
     * @param len 授权消息字符串的长度
     * @return  
     *      + 0: 调用成功。<br>
     *      + –1000: 未集成特效 SDK。<br>
     *      + –1001: 特效 SDK 不支持该功能。<br>
     *      + –1002: 特效 SDK 版本不兼容。<br>
     *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
     * @note 
     *        + 使用视频特效的功能前，你必须获取特效 SDK 的在线许可证。  <br>
     *        + 通过此接口获取授权消息后，你必须参考 [在线授权说明](https://www.volcengine.com/docs/6705/102012) 自行实现获取在线许可证的业务逻辑。获取许可证后，你必须调用 initCVResource{@link #IVideoEffect#initCVResource} 确认许可证有效。然后，你才可以使用 CV 功能。  <br>
     *        + 获取授权消息后，调用 freeAuthMessage{@link #freeAuthMessage} 释放内存。
     */
    /**
     * @locale en
     * @type api
     * @region Video Effects
     * @hidden(iOS, Android)
     * @brief Get authorization messages from the Effect SDK to obtain online licenses.
     * @param ppmsg Authorization message string address
     * @param len Authorization message string length
     * @return   
     *      + 0: Success.<br>
     *      + –1000: The Effects SDK is not integrated.<br>
     *      + –1001: This API is unavailable for your Effects SDK.<br>
     *      + –1002: Your Effects SDK's version is incompatible.<br>
     *      + < 0: Other error. See [error code table](https://docs.byteplus.com/effects/docs/error-code-table) for specific instructions.
     * @note  
     *         + You must obtain an online license for the Effect SDK before using the CV functions. <br>
     *         + After obtaining authorization messages through this API, you must refer to [Online License Guide](https://docs.byteplus.com/en/effects/docs/windows-license-guide) to implement the business logic of obtaining online licenses by yourself. After obtaining the license, you must call initCVResource{@link #IVideoEffect#initCVResource} to confirm that the license is valid. Then you can use the CV function. <br>
     *         + After obtaining the authorization message, call freeAuthMessage{@link #freeAuthMessage} to free memory.
     */
    virtual int getAuthMessage(char ** ppmsg, int * len) = 0;
    /**
     * @locale zh
     * @type api
     * @region 视频特效
     * @hidden(iOS,Android)
     * @brief 使用完授权消息字符串后，释放内存。
     * @param pmsg getAuthMessage 返回的授权消息字符串。
     * @return  
     *      + 0: 调用成功。<br>
     *      + –1000: 未集成特效 SDK。<br>
     *      + –1001: 特效 SDK 不支持该功能。<br>
     *      + –1002: 特效 SDK 版本不兼容。<br>
     *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
     */
    /**
     * @locale en
     * @type api
     * @region Video Effects
     * @hidden(iOS,Android)
     * @brief After using the authorization message string, free the memory.
     * @param pmsg The authorization message string returned by getAuthMessage.
     * @return   
     *      + 0: Success.<br>
     *      + –1000: The Effects SDK is not integrated.<br>
     *      + –1001: This API is unavailable for your Effects SDK.<br>
     *      + –1002: Your Effects SDK's version is incompatible.<br>
     *      + < 0: Other error. See [error code table](https://docs.byteplus.com/effects/docs/error-code-table) for specific instructions.
     */
    virtual int freeAuthMessage(char * pmsg) = 0;

    /**
     * @locale zh
     * @deprecated since 3.50 and will be deleted in 3.55, use enableVideoEffect{@link #IVideoEffect#enableVideoEffect} instead.
     * @type api
     * @region 视频特效
     * @brief 开启关闭视频特效
     * @param enabled 是否开启特效，true: 开启，false: 关闭
     * @return  
     *      + 0: 调用成功。  <br>
     *      + 1000: 未集成特效 SDK。  <br>
     *      + 1001: 特效 SDK 不支持该功能。  <br>
     *      + < 0: 调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。  
     * @note 在调用 CheckLicense{@link #checkLicense} 和 SetAlgoModelPath{@link #setAlgoModelPath} 后调用此方法。
     */
    /**
     * @locale en
     * @deprecated since 3.50 and will be deleted in 3.55, use enableVideoEffect{@link #IVideoEffect#enableVideoEffect} instead.
     * @type api
     * @region Video Effects
     * @brief  Turn on and off video effects
     * @param enabled  Whether to turn on effects, true: on, false: off
     * @return   
     *      + 0: Succeed <br>
     *      + 1000: Effect SDK is not integrated  <br>
     *      + 1001: CV functionality is not supported in the current RTC version  <br>
     *      + <0: Other errors, see [Error Code Table](https://docs.byteplus.com/en/effects/docs/error-code-table).
     * @note Call this API after CheckLicense{@link #checkLicense} and SetAlgoModelPath{@link #setAlgoModelPath}.
     */
    virtual int enableEffect(bool enabled) = 0;
    
    /**
     * @locale zh
     * @hidden for internal use only
     * @region 视频特效
     * @brief 返回视频特效句柄。私有接口
     */
    /**
     * @locale en
     * @hidden for internal use only
     * @region Video Effects
     * @brief Returns video effect handle. Private method
     */
    virtual void* getEffectHandle() = 0;

    /**
     * @locale zh
     * @type api
     * @brief 开启高级美颜、滤镜等视频特效。
     * @return  
     *      + 0: 调用成功。<br>
     *      + –1000: 未集成特效 SDK。<br>
     *      + –1001: 特效 SDK 不支持该功能。<br>
     *      + –1002: 特效 SDK 版本不兼容。<br>
     *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
     * @note  
     *      + 调用本方法前，必须先调用 initCVResource{@link #IVideoEffect#initCVResource} 进行初始化。<br>
     *      + 调用该方法后，特效不直接生效，你还需调用 setEffectNodes{@link #IVideoEffect#setEffectNodes} 设置视频特效素材包或调用 setColorFilter{@link #IVideoEffect#setColorFilter} 设置滤镜。<br>
     *      + 调用 disableVideoEffect{@link #IVideoEffect#disableVideoEffect} 关闭视频特效。
     */
    /**
     * @locale en
     * @type api
     * @brief Enables video effects including beauty and color filters.
     * @return  
     *      + 0: Success.<br>
     *      + –1000: The Effects SDK is not integrated.<br>
     *      + –1001: This API is unavailable for your Effects SDK.<br>
     *      + –1002: Your Effects SDK's version is incompatible.<br>
     *      + < 0: Other error. See [error code table](https://docs.byteplus.com/effects/docs/error-code-table) for specific instructions.
     * @note  
     *      + You must call initCVResource{@link #IVideoEffect#initCVResource} before calling this API.<br>
     *      + This API does not turn on video effects directly, you must call setEffectNodes{@link #IVideoEffect#setEffectNodes} or setColorFilter{@link #IVideoEffect#setColorFilter} next.<br>
     *      + Call disableVideoEffect{@link #IVideoEffect#disableVideoEffect} to turn off video effects.
     */
    virtual int enableVideoEffect() = 0;

    /**
     * @locale zh
     * @type api
     * @brief 关闭视频特效。
     * @return  
     *      + 0: 调用成功。<br>
     *      + –1000: 未集成特效 SDK。<br>
     *      + –1001: 特效 SDK 不支持该功能。<br>
     *      + –1002: 特效 SDK 版本不兼容。<br>
     *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
     * @note 调用 enableVideoEffect{@link #IVideoEffect#enableVideoEffect} 开启视频特效。
     */
    /**
     * @locale en
     * @type api
     * @brief Disables video effects.
     * @return  
     *      + 0: Success.<br>
     *      + –1000: The Effects SDK is not integrated.<br>
     *      + –1001: This API is unavailable for your Effects SDK.<br>
     *      + –1002: Your Effects SDK's version is incompatible.<br>
     *      + < 0: Other error. See [error code table](https://docs.byteplus.com/effects/docs/error-code-table) for specific instructions.
     * @note Call enableVideoEffect{@link #IVideoEffect#enableVideoEffect} to enable video effects.
     */
    virtual int disableVideoEffect() = 0;

    /**
     * @locale zh
     * @type api
     * @brief 设置视频特效素材包。
     * @param effect_node_paths 特效素材包绝对路径数组。<br>
     *        要取消当前视频特效，将此参数设置为 null。
     * @param node_num 特效素材包个数。
     * @return  
     *      + 0: 调用成功。<br>
     *      + –1000: 未集成特效 SDK。<br>
     *      + –1001: 特效 SDK 不支持该功能。<br>
     *      + –1002: 特效 SDK 版本不兼容。<br>
     *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
     * @note 调用本方法前，必须先调用 enableVideoEffect{@link #IVideoEffect#enableVideoEffect}。
     */
    /**
     * @locale en
     * @type api
     * @brief Sets the video effects material package.
     * @param effect_node_paths Array of effect material package paths. <br>
     *        To remove the current video effect, set it to null.
     * @param node_num Number of effect material packages.
     * @return   
     *      + 0: Success.<br>
     *      + –1000: The Effects SDK is not integrated.<br>
     *      + –1001: This API is unavailable for your Effects SDK.<br>
     *      + –1002: Your Effects SDK's version is incompatible.<br>
     *      + < 0: Other error. See [error code table](https://docs.byteplus.com/effects/docs/error-code-table) for specific instructions.
     * @note You must call enableVideoEffect{@link #IVideoEffect#enableVideoEffect} before calling this API.
     */
    virtual int setEffectNodes(const char** effect_node_paths, int node_num) = 0;

    /**
     * @locale zh
     * @hidden for internal use only
     * @type api
     * @brief  叠加视频特效素材包。
     * @param effect_node_paths 特效素材包绝对路径数组。
     * @param node_num 特效素材包个数。
     * @return  
     *      + 0: 调用成功。<br>
     *      + –1000: 未集成特效 SDK。<br>
     *      + –1001: 特效 SDK 不支持该功能。<br>
     *      + –1002: 特效 SDK 版本不兼容。<br>
     *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
     * @note 该接口会在 setEffectNodes{@link #IVideoEffect#setEffectNodes} 设置的特效基础上叠加特效。
     */
    /**
     * @locale en
     * @hidden for internal use only
     * @type api
     * @brief  Appends video effects material package.
     * @param effect_node_paths Array of effect material package paths.
     * @param node_num Number of effect material packages.
     * @return  
     *      + 0: Success.<br>
     *      + –1000: The Effects SDK is not integrated.<br>
     *      + –1001: This API is unavailable for your Effects SDK.<br>
     *      + –1002: Your Effects SDK's version is incompatible.<br>
     *      + < 0: Other error. See [error code table](https://docs.byteplus.com/effects/docs/error-code-table) for specific instructions.
     * @note This API adds new video effect to the video effect you set with setEffectNodes{@link #IVideoEffect#setEffectNodes}.
     */
    virtual int appendEffectNodes(const char** effect_node_paths, int node_num) = 0;

    /**
     * @locale zh
     * @hidden for internal use only
     * @type api
     * @brief  移除指定的视频特效资源。
     * @param effect_node_paths 特效素材包绝对路径数组。
     * @param node_num 特效素材包个数。
     * @return  
     *      + 0: 调用成功。<br>
     *      + –1000: 未集成特效 SDK。<br>
     *      + –1001: 特效 SDK 不支持该功能。<br>
     *      + –1002: 特效 SDK 版本不兼容。<br>
     *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
     * @note 移除 setEffectNodes{@link #IVideoEffect#SetEffectNodes} 或 appendEffectNodes{@link #IVideoEffect#appendEffectNodes} 设置的视频特效资源。
     */
    /**
     * @locale en
     * @hidden for internal use only
     * @type api
     * @brief  Removes the designated video effects material package.
     * @param effect_node_paths Array of effect material package paths.
     * @param node_num Number of effect material packages.
     * @return  
     *      + 0: Success.<br>
     *      + –1000: The Effects SDK is not integrated.<br>
     *      + –1001: This API is unavailable for your Effects SDK.<br>
     *      + –1002: Your Effects SDK's version is incompatible.<br>
     *      + < 0: Other error. See [error code table](https://docs.byteplus.com/effects/docs/error-code-table) for specific instructions.
     * @note Removes the designated video effects in setEffectNodes{@link #IVideoEffect#setEffectNodes} or appendEffectNodes{@link #IVideoEffect#appendEffectNodes}.
     */
    virtual int removeEffectNodes(const char** effect_node_paths, int node_num) = 0;

    /**
     * @locale zh
     * @deprecated since 3.50 and will be deleted in 3.55, use updateEffectNode{@link #IVideoEffect#updateEffectNode} instead.
     * @type api
     * @region 视频特效
     * @brief 设置特效强度
     * @param node_path  <br>
     *        特效素材包路径
     * @param node_key  <br>
     *        需要设置的素材 key 名称，取值请参考 [素材 key 对应说明](http://ailab-cv-sdk.bytedance.com/docs/2036/99769/)。
     * @param node_value  <br>
     *        需要设置的强度值 取值范围 [0,1]，超出范围时设置无效。
     * @return  
     *      + 0: 调用成功。  <br>
     *      + 1000: 未集成特效 SDK。  <br>
     *      + 1001: 特效 SDK 不支持该功能。  <br>
     *      + < 0: 调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。  
     */
    /**
     * @locale en
     * @deprecated since 3.50 and will be deleted in 3.55, use updateEffectNode{@link #IVideoEffect#updateEffectNode} instead.
     * @type api
     * @region Video Effects
     * @brief  Set the effect intensity
     * @param node_path <br>
     *         Special effects material package path
     * @param node_key <br>
     *         The name of the material key to be set, please refer to [Material key correspondence instructions](http://ailab-cv-sdk.bytedance.com/docs/2036/99769/) for the value.
     * @param node_value <br>
     *         The intensity value that needs to be set, the value range [0,1], and the setting is invalid when it exceeds the range.
     * @return   
     *       + 0: Call succeeded <br>
     *       + 1000: The Effect SDK is not integrated.  <br>
     *       + 1001: This API is not available for your Effect SDK.  <br>
     *       + < 0: Failure. For specific error codes, please refer to [Error Code Table](https://docs.byteplus.com/en/effects/docs/error-code-table).
     */
    virtual int updateNode(const char* node_path, const char* node_key, float node_value) = 0;

    /**
     * @locale zh
     * @type api
     * @brief 设置特效强度。
     * @param effect_node_path 特效素材包绝对路径，参考[素材包结构说明](https://www.volcengine.com/docs/6705/102039)。
     * @param node_key 需要设置的素材 key 名称，参考[素材 key 对应说明](https://www.volcengine.com/docs/6705/102041)。
     * @param node_value 特效强度值，取值范围 [0,1]，超出范围时设置无效。
     * @return  
     *      + 0: 调用成功。<br>
     *      + –1000: 未集成特效 SDK。<br>
     *      + –1001: 特效 SDK 不支持该功能。<br>
     *      + –1002: 特效 SDK 版本不兼容。<br>
     *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
     */
    /**
     * @locale en
     * @type api
     * @brief Sets the intensity of video effects.
     * @param effect_node_path The absolute path of the effects resource package, see [Resource Package Structure](https://docs.byteplus.com/effects/docs/resource-package-structure-v421-and-later).
     * @param node_key The name of the material key to be set, see [Functions of Resource Keys](https://docs.byteplus.com/effects/docs/functions-of-resource-keys-v421-and-later) for the value.
     * @param node_value The intensity value that needs to be set, the value range [0,1], and the setting is invalid when it exceeds the range.
     * @return   
     *      + 0: Success.<br>
     *      + –1000: The Effects SDK is not integrated.<br>
     *      + –1001: This API is unavailable for your Effects SDK.<br>
     *      + –1002: Your Effects SDK's version is incompatible.<br>
     *      + < 0: Other error. See [error code table](https://docs.byteplus.com/effects/docs/error-code-table) for specific instructions.
     */
    virtual int updateEffectNode(const char* effect_node_path, const char* node_key, float node_value) = 0;

    /**
     * @locale zh
     * @type api
     * @brief 设置颜色滤镜。
     * @param res_path 滤镜资源包绝对路径。
     * @return  
     *      + 0: 调用成功。<br>
     *      + –1000: 未集成特效 SDK。<br>
     *      + –1001: 特效 SDK 不支持该功能。<br>
     *      + –1002: 特效 SDK 版本不兼容。<br>
     *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
     * @note 调用 setColorFilterIntensity{@link #IVideoEffect#setColorFilterIntensity} 设置已启用颜色滤镜的强度。设置强度为 0 时即关闭颜色滤镜。
     */
    /**
     * @locale en
     * @type api
     * @brief Sets the color filter.
     * @param res_path Filter effects package absolute path.
     * @return   
     *      + 0: Success.<br>
     *      + –1000: The Effects SDK is not integrated.<br>
     *      + –1001: This API is unavailable for your Effects SDK.<br>
     *      + –1002: Your Effects SDK's version is incompatible.<br>
     *      + < 0: Other error. See [error code table](https://docs.byteplus.com/effects/docs/error-code-table) for specific instructions.
     * @note Call setColorFilterIntensity{@link #IVideoEffect#setColorFilterIntensity} to set the intensity of the color filter enabled. Set the intensity to 0 to turn off color filter.
     */
    virtual int setColorFilter(const char* res_path) = 0;

    /**
     * @locale zh
     * @type api
     * @brief 设置已启用颜色滤镜的强度。
     * @param intensity 滤镜强度。取值范围 [0,1]，超出范围时设置无效。<br>
     *                  当设置滤镜强度为 0 时即关闭颜色滤镜。
     * @return  
     *      + 0: 调用成功。<br>
     *      + –1000: 未集成特效 SDK。<br>
     *      + –1001: 特效 SDK 不支持该功能。<br>
     *      + –1002: 特效 SDK 版本不兼容。<br>
     *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
     */
    /**
     * @locale en
     * @type api
     * @brief Sets the intensity of the color filter enabled.
     * @param intensity Filter intensity. The value range [0,1] is set to be invalid when the range is exceeded.<br>
     *                  Set the intensity to 0 to turn off color filter.
     * @return   
     *      + 0: Success.<br>
     *      + –1000: The Effects SDK is not integrated.<br>
     *      + –1001: This API is unavailable for your Effects SDK.<br>
     *      + –1002: Your Effects SDK's version is incompatible.<br>
     *      + < 0: Other error. See [error code table](https://docs.byteplus.com/effects/docs/error-code-table) for specific instructions.
     */
    virtual int setColorFilterIntensity(float intensity) = 0;
    
    /**
     * @locale zh
     * @hidden for internal use only
     * @type api
     * @brief 私有接口，设置视频特效素材包。
     * @param sticker_path 特效素材包绝对路径。<br>
     *        要取消当前视频特效，将此参数设置为 null。
     * @return  
     *      + 0: 调用成功。<br>
     *      + –1000: 未集成特效 SDK。<br>
     *      + –1001: 特效 SDK 不支持该功能。<br>
     *      + –1002: 特效 SDK 版本不兼容。<br>
     *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
     * @note 调用本方法前，必须先调用 enableVideoEffect{@link #IVideoEffect#enableVideoEffect}。
     */
    /**
     * @locale en
     * @hidden for internal use only
     * @type api
     * @brief Private method，Sets the video effects material package.
     * @param sticker_path effect material package path. <br>
     *        To remove the current video effect, set it to null.
     * @return   
     *      + 0: Success.<br>
     *      + –1000: The Effects SDK is not integrated.<br>
     *      + –1001: This API is not available for your Effects SDK.<br>
     *      + –1002: Your Effects SDK's version is incompatible.<br>
     *      + < 0: Other error. See [error code table](https://docs.byteplus.com/effects/docs/error-code-table) for specific instructions.
     * @note You must call enableVideoEffect{@link #IVideoEffect#enableVideoEffect} before calling this API.
     */
    virtual int applyStickerEffect(const char* sticker_path) = 0;

    /**
     * @locale zh
     * @hidden(Linux)
     * @type api
     * @brief 将摄像头采集画面中的人像背景替换为指定图片或纯色背景。
     * @param background_sticker_path 背景贴纸特效素材绝对路径。
     * @param source 背景贴纸对象，参看 VirtualBackgroundSource{@link #VirtualBackgroundSource}。
     * @return  
     *      + 0: 调用成功。<br>
     *      + –1000: 未集成特效 SDK。<br>
     *      + –1001: 特效 SDK 不支持该功能。<br>
     *      + –1002: 特效 SDK 版本不兼容。<br>
     *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
     * @note 
     *      + 调用本方法前，必须先调用 initCVResource{@link #IVideoEffect#initCVResource} 进行初始化。<br>
     *      + 调用 disableVirtualBackground{@link #IVideoEffect#disableVirtualBackground} 关闭虚拟背景。
     */
    /**
     * @locale en
     * @hidden(Linux)
     * @type api
     * @brief Sets the original background to a specified image or a solid color.
     * @param background_sticker_path The absolute path of virtual background effects.
     * @param source Virtual background source. See VirtualBackgroundSource{@link #VirtualBackgroundSource}.
     * @return  
     *      + 0: Success.<br>
     *      + –1000: The Effects SDK is not integrated.<br>
     *      + –1001: This API is unavailable for your Effects SDK.<br>
     *      + –1002: Your Effects SDK's version is incompatible.<br>
     *      + < 0: Other error. See [error code table](https://docs.byteplus.com/effects/docs/error-code-table) for specific instructions.
     * @note 
     *      + You must call initCVResource{@link #IVideoEffect#initCVResource} before calling this API.<br>
     *      + Call disableVirtualBackground{@link #IVideoEffect#disableVirtualBackground} to turn off the virtual background.
     */
    virtual int enableVirtualBackground(const char* background_sticker_path, const VirtualBackgroundSource& source) = 0;

    /**
     * @locale zh
     * @hidden(Linux)
     * @type api
     * @brief 关闭虚拟背景。
     * @return  
     *      + 0: 调用成功。<br>
     *      + –1000: 未集成特效 SDK。<br>
     *      + –1001: 特效 SDK 不支持该功能。<br>
     *      + –1002: 特效 SDK 版本不兼容。<br>
     *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
     * @note 调用 enableVirtualBackground{@link #IVideoEffect#enableVirtualBackground} 开启虚拟背景后，可以调用此接口关闭虚拟背景。
     */
    /**
     * @locale en
     * @hidden(Linux)
     * @type api
     * @brief Turns off the virtual background.
     * @return   
     *      + 0: Success.<br>
     *      + –1000: The Effects SDK is not integrated.<br>
     *      + –1001: This API is unavailable for your Effects SDK.<br>
     *      + –1002: Your Effects SDK's version is incompatible.<br>
     *      + < 0: Other error. See [error code table](https://docs.byteplus.com/effects/docs/error-code-table) for specific instructions.
     * @note After calling enableVirtualBackground{@link #IVideoEffect#enableVirtualBackground} to enable the virtual background function, you can call this API to turn it off.
     */
    virtual int disableVirtualBackground() = 0;

    /**
     * @locale zh
     * @hidden for internal use only
     * @type api
     * @brief 开启人像属性检测。
     * @param expression_detection_config 人像属性检测参数，参看 VideoEffectExpressionDetectConfig{@link #VideoEffectExpressionDetectConfig}。
     * @return  
     *      + 0: 调用成功。<br>
     *      + –1000: 未集成特效 SDK。<br>
     *      + –1001: 特效 SDK 不支持该功能。<br>
     *      + –1002: 特效 SDK 版本不兼容。<br>
     *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
     */
    /**
     * @locale en
     * @hidden for internal use only
     * @type api
     * @brief  Sets the configuration for video effects expression detection.
     * @param expression_detection_config Expression detection configuration. See VideoEffectExpressionDetectConfig{@link #VideoEffectExpressionDetectConfig}.
     * @return  
     *      + 0: Success.<br>
     *      + –1000: The Effects SDK is not integrated.<br>
     *      + –1001: This API is unavailable for your Effects SDK.<br>
     *      + –1002: Your Effects SDK's version is incompatible.<br>
     *      + < 0: Other error. See [error code table](https://docs.byteplus.com/effects/docs/error-code-table) for specific instructions.
     */
    virtual int setVideoEffectExpressionDetect(const VideoEffectExpressionDetectConfig& expression_detection_config) = 0;

    /**
     * @locale zh
     * @deprecated since 3.50 and will be deleted in 3.55, use enableFaceDetection{@link #IVideoEffect#enableFaceDetection} and disableFaceDetection{@link #IVideoEffect#disableFaceDetection} instead.
     * @type api
     * @brief 注册人脸检测结果回调观察者。<br>
     *        注册此观察者后，你会周期性收到 onFaceDetectResult{@link #IFaceDetectionObserver#onFaceDetectResult} 回调。
     * @param observer 人脸检测结果回调观察者，参看 IFaceDetectionObserver{@link #IFaceDetectionObserver}。
     * @param interval_ms 时间间隔，必须大于 0。单位：ms。实际收到回调的时间间隔大于 `interval`，小于 `interval+视频采集帧间隔`。
     * @return  
     *      + 0: 调用成功。<br>
     *      + –1000: 未集成特效 SDK。<br>
     *      + –1001: 特效 SDK 不支持该功能。<br>
     *      + –1002: 特效 SDK 版本不兼容。<br>
     *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
     */
    /**
     * @locale en
     * @deprecated since 3.50 and will be deleted in 3.55, use enableFaceDetection{@link #IVideoEffect#enableFaceDetection} and disableFaceDetection{@link #IVideoEffect#disableFaceDetection} instead.
     * @type api
     * @brief  Register the observer for the result of face detection.<br>
     *        With this observer, you will receive onFaceDetectResult{@link #IFaceDetectionObserver#onFaceDetectResult} periodically.
     * @param observer See IFaceDetectionObserver{@link #IFaceDetectionObserver}.
     * @param interval_ms Time interval in ms. The value should be greater than 0. The actual time interval of receiving callbacks is between `interval` and `interval+the time slot of a captured video frame`.
     * @return 
     *      + 0: Success.<br>
     *      + –1000: The Effects SDK is not integrated.<br>
     *      + –1001: This API is unavailable for your Effects SDK.<br>
     *      + –1002: Your Effects SDK's version is incompatible.<br>
     *      + < 0: Other error. See [error code table](https://docs.byteplus.com/effects/docs/error-code-table) for specific instructions.
     */
    virtual int registerFaceDetectionObserver(IFaceDetectionObserver* observer, int interval_ms) = 0;

    /**
     * @locale zh
     * @type api
     * @brief 开启人脸识别功能，并设置人脸检测结果回调观察者。<br>
     *        此观察者后，你会周期性收到 onFaceDetectResult{@link #IFaceDetectionObserver#onFaceDetectResult} 回调。
     * @param observer 人脸检测结果回调观察者，参看 IFaceDetectionObserver{@link #IFaceDetectionObserver}。
     * @param interval_ms 两次回调之间的最小时间间隔，必须大于 0，单位为毫秒。实际收到回调的时间间隔大于 interval_ms，小于 interval_ms+视频采集帧间隔。
     * @param face_model_path 人脸检测算法模型文件路径，一般为 ttfacemodel 文件夹中 tt_face_vXXX.model 文件的绝对路径。
     * @return  
     *      + 0: 调用成功。<br>
     *      + –1000: 未集成特效 SDK。<br>
     *      + –1001: 特效 SDK 不支持该功能。<br>
     *      + –1002: 特效 SDK 版本不兼容。<br>
     *      + -1004: 初始化中，初始化完成后启动此功能。<br>
     *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
     */
    /**
     * @locale en
     * @type api
     * @brief Starts face detection and registers the observer for the result.<br>
     *        With this observer, you will receive onFaceDetectResult{@link #IFaceDetectionObserver#onFaceDetectResult} periodically.
     * @param observer See IFaceDetectionObserver{@link #IFaceDetectionObserver}.
     * @param interval_ms The minimum time interval between two callbacks in milliseconds. The value should be greater than 0. The actual time interval is between interval_ms and interval_ms+the time slot of a captured video frame.
     * @param face_model_path The absolute path of the face detection algorithm file. Typically it is the tt_face_vXXX.model file in the ttfacemodel folder.
     * @return 
     *      + 0: Success.<br>
     *      + –1000: The Effects SDK is not integrated.<br>
     *      + –1001: This API is unavailable for your Effects SDK.<br>
     *      + –1002: Your Effects SDK's version is incompatible.<br>
     *      + -1004: Initializing. This function will be available when the initialization is completed.<br>
     *      + < 0: Other error. See [error code table](https://docs.byteplus.com/effects/docs/error-code-table) for specific instructions.
     */
    virtual int enableFaceDetection(IFaceDetectionObserver* observer, unsigned int interval_ms, const char* face_model_path) = 0;

    /**
     * @locale zh
     * @type api
     * @brief 关闭人脸识别功能。
     * @return  
     *      + 0: 调用成功。<br>
     *      + –1000: 未集成特效 SDK。<br>
     *      + –1001: 特效 SDK 不支持该功能。<br>
     *      + –1002: 特效 SDK 版本不兼容。<br>
     *      + < 0: 调用失败，错误码对应具体描述参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
     */
    /**
     * @locale en
     * @type api
     * @brief Stops face detection.
     * @return 
     *      + 0: Success.<br>
     *      + –1000: The Effects SDK is not integrated.<br>
     *      + –1001: This API is unavailable for your Effects SDK.<br>
     *      + –1002: Your Effects SDK's version is incompatible.<br>
     *      + < 0: Other error. See [error code table](https://docs.byteplus.com/effects/docs/error-code-table) for specific instructions.
     */
    virtual int disableFaceDetection() = 0;

    /**
     * @locale zh
     * @hidden(Linux)
     * @deprecated since 3.50 and will be deleted in 3.55, use enableVirtualBackground{@link #IVideoEffect#enableVirtualBackground} instead.
     * @type api
     * @region 视频特效
     * @brief 将摄像头采集画面中的人像背景替换为指定图片或纯色背景。<br>
     *        若要取消背景特效，将背景贴纸特效素材路径设置为null。
     * @param model_path 传入背景贴纸特效素材路径。  
     * @param source 设置背景特效图片的本地路径。参看 VirtualBackgroundSource{@link #VirtualBackgroundSource}。  
     * @return  
     *        + 0：调用成功。  <br>
     *        + 1000：未集成特效 SDK。  <br>
     *        + 1001：特效 SDK 不支持该功能。  <br>
     *        + < 0：调用失败。具体错误码，参看 [错误码表](https://www.volcengine.com/docs/6705/102042)。
     * @note  
     *        调用此接口前需依次调用以下接口：<br>
     * 1、检查视频特效许可证 checkLicense{@link #IVideoEffect#checkLicense}；<br>
     * 2、设置视频特效算法模型路径 setAlgoModelPath{@link #IVideoEffect#setAlgoModelPath}；<br>
     * 3、开启视频特效 enableEffect{@link #IVideoEffect#enableEffect}。
     */
    /**
     * @locale en
     * @hidden(Linux)
     * @deprecated since 3.50 and will be deleted in 3.55, use enableVirtualBackground{@link #IVideoEffect#enableVirtualBackground} instead.
     * @type api
     * @region Video Effects
     * @brief Set the original background to a specified image or a solid color.<br>
     *        To disable this effect, set the modelPath parameter to null.
     * @param model_path Set the path of virtual background effects.  
     * @param source Set the local path of background images. See VirtualBackgroundSource{@link #VirtualBackgroundSource}.
     * @return  
     *        + 0：Success.  <br>
     *        + 1000：The BytePlus Effects SDK is not integrated.  <br>
     *        + 1001：This feature is not supported in the BytePlus Effects SDK.  <br>
     *        + < 0：Other errors. See [Error Code Table](https://docs.byteplus.com/en/effects/docs/error-code-table).
     * @note  
     *        Before calling this method, you should call checkLicense{@link #IVideoEffect#checkLicense}、setAlgoModelPath{@link #IVideoEffect#setAlgoModelPath}, and enableEffect {@link #IVideoEffect#enableEffect} in order.
     */
    virtual int setBackgroundSticker(const char* model_path, const VirtualBackgroundSource& source) = 0;

};

}  // namespace bytertc
