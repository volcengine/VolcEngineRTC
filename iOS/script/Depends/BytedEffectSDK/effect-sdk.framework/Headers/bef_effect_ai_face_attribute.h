
#ifndef _BEF_EFFECT_FACE_ATTRIBUTE_H_
#define _BEF_EFFECT_FACE_ATTRIBUTE_H_

#if defined(__ANDROID__) || defined(TARGET_OS_ANDROID)
#if BEF_EFFECT_ANDROID_WITH_JNI
#include<jni.h>
#endif
#endif

#include "bef_effect_ai_public_define.h"
#include "bef_effect_ai_face_detect.h"

typedef enum {
  BEF_FACE_ATTRIBUTE_AGE          = 0x00000001,     //年龄
  BEF_FACE_ATTRIBUTE_GENDER       = 0x00000002,     //性别
  BEF_FACE_ATTRIBUTE_EXPRESSION   = 0x00000004,     //表情
  BEF_FACE_ATTRIBUTE_ATTRACTIVE   = 0x00000008,     //颜值
  BEF_FACE_ATTRIBUTE_HAPPINESS    = 0x00000010,     //开心程度
  BEF_FACE_ATTRIBUTE_CONFUSE      = 0x00000400,     //疑惑
} bef_ai_face_attribute_types;

typedef enum {
  BEF_FACE_ATTRIBUTE_ForceDetect = 0x10000000,     //未加平滑的裸数据，重置缓存，在切换摄像头时等上下帧剧烈变化时使用
                                //用于处理切换摄像头，跟踪的人脸ID 混淆的问题
} bef_ai_face_attribut_config;

/*
 *@brief 表情类别枚举
**/
typedef enum {
  BEF_FACE_ATTRIBUTE_ANGRY = 0,                   //生气
  BEF_FACE_ATTRIBUTE_DISGUST = 1,                 //厌恶
  BEF_FACE_ATTRIBUTE_FEAR = 2,                    //害怕
  BEF_FACE_ATTRIBUTE_HAPPY = 3,                   //高兴
  BEF_FACE_ATTRIBUTE_SAD = 4,                     //伤心
  BEF_FACE_ATTRIBUTE_SURPRISE = 5,                //吃惊
  BEF_FACE_ATTRIBUTE_NEUTRAL = 6,                 //平静
  BEF_FACE_ATTRIBUTE_NUM_EXPRESSION = 7           //支持的表情个数
}bef_ai_face_attribute_expression_type;

/*
 *@brief 模型类别枚举
**/
typedef enum {
  BEF_FACE_ATTRIBUTE_MODEL_AGE = 0,
  BEF_FACE_ATTRIBUTE_MODEL_EXP = 1,
  BEF_FACE_ATTRIBUTE_MODEL_CONFUSED = 2
}bef_ai_face_attribute_model_type;

/*
 *@breif 单个人脸属性结构体
**/
typedef struct bef_ai_face_attribute_info {
  float age;                          // 预测的年龄值， 值范围【0，100】之间
  float boy_prob;                     // 预测为男性的概率值，值范围【0.0，1.0】之间
  float attractive;                   // 预测的颜值分数，范围【0，100】之间
  float happy_score;                  // 预测的微笑程度，范围【0，100】之间
  bef_ai_face_attribute_expression_type exp_type;            // 预测的表情类别
  float exp_probs[BEF_FACE_ATTRIBUTE_NUM_EXPRESSION];    // 预测的每个表情的概率，未加平滑处理
  // extra
  float real_face_prob;               // 预测属于真人脸的概率，用于区分雕塑、漫画等非真实人脸
  float quality;                      // 预测人脸的质量分数，范围【0，100】之间
  float arousal;                      // 情绪的强烈程度
  float valence;                      // 情绪的正负情绪程度
  float sad_score;                    // 伤心程度
  float angry_score;                  // 生气程度
  float surprise_score;               // 吃惊的程度
  float mask_prob;                    // 预测带口罩的概率
  float wear_hat_prob;                // 戴帽子的概率
  float mustache_prob;                // 有胡子的概率
  float lipstick_prob;                // 涂口红的概率
  float wear_glass_prob;              // 带普通眼镜的概率
  float wear_sunglass_prob;           // 带墨镜的概率
  float blur_score;                   // 模糊程度
  float illumination;                 // 光照
  float confused_prob;                ///< 疑惑表情概率
} bef_ai_face_attribute_info;


typedef enum {
  // 身份相关的属性(性别、年龄)检测隔帧数，默认值为12;
  BEF_FACE_ATTRIBUTE_IDRelatedDetectInterval = 1,
  // 非身份相关的属性(表情、颜值、微笑程度）检测隔帧数，默认值为1，即每帧都识别；
  // 保留字段，当前不可设；
  BEF_FACE_ATTRIBUTE_DetectInterval = 2,
  // 当身份相关的属性识别置信度足够高时，停止计算该属性（结果在SDK中存储中正常返回，对外不感知）
  // 默认值为1，表示打开，设置为0,表示关闭；
  BEF_FACE_ATTRIBUTE_IDRelatedAccumulateResult = 3,
}bef_ai_face_attribute_param_config_type;

/*
 *@brief 多个人脸属性结构体
 *@param
 *      face_count 有效的人脸个数
**/
typedef struct bef_ai_face_attribute_result {
  bef_ai_face_attribute_info  attr_info[BEF_MAX_FACE_NUM];    //存放人脸属性结果数组
  int face_count;                         //有效的人脸个数，即表示attr_info中的前face_count个人脸是有效的
} bef_ai_face_attribute_result;



/**
 * @brief 创建人脸属性检测的句柄
 * @param [in] config Config of face attribute detect algorithm
 *                    人脸属性检测算法的配置
 * @param [in] strModelPath 模型文件所在路径
 * @param [out] handle Created face attribute detect handle
 *                     创建的人脸属性检测句柄
 * @return If succeed return BEF_RESULT_SUC, other value please see bef_effect_base_define.h
 *         成功返回 BEF_RESULT_SUC, 失败返回相应错误码, 具体请参考 bef_effect_base_define.h
 */
BEF_SDK_API bef_effect_result_t
bef_effect_ai_face_attribute_create(
  unsigned long long config,
  const char * strModelPath,
  bef_effect_handle_t *handle
);

/**
 * @brief 初始化人脸属性模型
 * @param [in] handle Created face attribute detect handle
 *                    已创建的人脸属性检测句柄
 * @param [in] strModelPath 模型文件所在路径
 * @param [in] type 模型文件类型
 * @return If succeed return BEF_RESULT_SUC, other value please see bef_effect_base_define.h
 *         成功返回 BEF_RESULT_SUC, 失败返回相应错误码, 具体请参考 bef_effect_base_define.h
 */
BEF_SDK_API bef_effect_result_t
bef_effect_ai_face_attribute_init_model(
  bef_effect_handle_t handle,
  const char * strModelPath,
  bef_ai_face_attribute_model_type type
);

/**
 * @brief 单个人脸属性检测
 * @param [in] handle Created face attribute detect handle
 *                    已创建的人脸属性检测句柄
 * @param [in] image Image base address
 *                   输入图片的数据指针
 * @param [in] pixel_format Pixel format of input image
 *                          输入图片的格式
 * @param [in] image_width  Image width
 *                          输入图像的宽度 (以像素为单位)
 * @param [in] image_height Image height
 *                          输入图像的高度 (以像素为单位)
 * @param [in] image_stride Image stride in each row
 *                          输入图像每一行的步长 (以像素为单位)
 * @param [in] ptr_base_info 人脸检测结果
 * @param [in] detect_config Config of face detect, for example
 *                           人脸检测相关的配置
 * @return If succeed return BEF_RESULT_SUC, other value please see bef_effect_base_define.h
 *         成功返回 BEF_RESULT_SUC, 失败返回相应错误码, 具体请参考 bef_effect_base_define.h
 */
BEF_SDK_API bef_effect_result_t
bef_effect_ai_face_attribute_detect(
  bef_effect_handle_t handle,
  const unsigned char *image,
  bef_ai_pixel_format pixel_format,
  int image_width,
  int image_height,
  int image_stride,
  const bef_ai_face_106 *ptr_base_info,
  unsigned long long config,
  bef_ai_face_attribute_info *ptr_face_attribute_info
);

/**
 * @brief 多个人脸属性检测
 * @param [in] handle Created face attribute detect handle
 *                    已创建的人脸属性检测句柄
 * @param [in] image Image base address
 *                   输入图片的数据指针
 * @param [in] pixel_format Pixel format of input image
 *                          输入图片的格式
 * @param [in] image_width  Image width
 *                          输入图像的宽度 (以像素为单位)
 * @param [in] image_height Image height
 *                          输入图像的高度 (以像素为单位)
 * @param [in] image_stride Image stride in each row
 *                          输入图像每一行的步长 (以像素为单位)
 * @param [in] ptr_base_info 人脸检测结果
 * @param [in] face_count 人脸检测人脸数
 * @param [in] detect_config Config of face detect, for example
 *                           人脸检测相关的配置
 * @return If succeed return BEF_RESULT_SUC, other value please see bef_effect_base_define.h
 *         成功返回 BEF_RESULT_SUC, 失败返回相应错误码, 具体请参考 bef_effect_base_define.h
 */
BEF_SDK_API bef_effect_result_t
bef_effect_ai_face_attribute_detect_batch(
  bef_effect_handle_t handle,
  const unsigned char *image,
  bef_ai_pixel_format pixel_format,
  int image_width,
  int image_height,
  int image_stride,
  const bef_ai_face_106 *ptr_base_info,
  int face_count,
  unsigned long long config,
  bef_ai_face_attribute_result *ptr_face_attribute_result
);


/**
 * @brief Set face attribute detect parameter based on type 
 *     设置人脸属性检测的相关参数
 * @param [in] handle Created face detect handle
 *                    已创建的人脸检测句柄
 * @param [in] type Face detect type that needs to be set, check bef_face_detect_type for the detailed
 *                  需要设置的人体检测类型，可参考 bef_face_detect_type
 * @param [in] value Type value, check bef_face_detect_type for the detailed
 *                   参数值, 具体请参数 bef_face_detect_type 枚举中的说明
 * @return If succeed return BEF_RESULT_SUC, other value please refer bef_effect_base_define.h
 *         成功返回 BEF_RESULT_SUC, 失败返回相应错误码, 具体请参考 bef_effect_base_define.h
 */
BEF_SDK_API bef_effect_result_t
bef_effect_ai_face_attribute_setparam(
  bef_effect_handle_t handle,
  bef_ai_face_attribute_param_config_type type,
  float value
);


/**
 * @param [in] handle Destroy the created face attribute detect handle
 *                    销毁创建的人脸属性检测句柄
 */
BEF_SDK_API void
bef_effect_ai_face_attribute_destroy(
  bef_effect_handle_t handle
);

/**
 * @brief 人脸属性检测授权
 * @param [in] handle Created face attribute detect handle
 *                    已创建的人脸检测句柄
 * @param [in] license 授权文件字符串
 * @param [in] length  授权文件字符串长度
 * @return If succeed return BEF_RESULT_SUC, other value please refer bef_effect_ai_public_define.h
 *         成功返回 BEF_RESULT_SUC, 授权码非法返回 BEF_RESULT_INVALID_LICENSE ，其它失败返回相应错误码, 具体请参考 bef_effect_ai_public_define.h
 */
#if defined(__ANDROID__) || defined(TARGET_OS_ANDROID)
#if BEF_EFFECT_ANDROID_WITH_JNI
BEF_SDK_API bef_effect_result_t bef_effect_ai_face_attribute_check_license(JNIEnv *env, jobject context,
                                                                 bef_effect_handle_t handle,
                                                                 const char *licensePath);
#else
BEF_SDK_API bef_effect_result_t bef_effect_ai_face_attribute_check_license(bef_effect_handle_t handle,
                                                                 const char *licensePath);
#endif
#else
#ifdef __APPLE__
BEF_SDK_API bef_effect_result_t bef_effect_ai_face_attribute_check_license(bef_effect_handle_t handle,
        const char *licensePath);
#endif
#endif

BEF_SDK_API bef_effect_result_t
bef_effect_ai_face_attribute_check_online_license(bef_effect_handle_t handle, const char *licensePath);

#endif // _BEF_EFFECT_FACE_DETECT_AI_H_
