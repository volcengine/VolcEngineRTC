
#ifndef _BEF_EFFECT_FOOT_DETECT_AI_H_
#define _BEF_EFFECT_FOOT_DETECT_AI_H_


#if defined(__ANDROID__) || defined(TARGET_OS_ANDROID)
#include<jni.h>
#endif

#include "bef_effect_ai_public_define.h"

#define BEF_MAX_FEET_NUM 2
#define BEF_FEET_KEY_POINT_NUM 66


typedef struct bef_ai_foot_st {
  int id; // id
  bef_ai_rect box; // 脚框
  float left_prob; // 脚是左脚的概率
  float foot_prob; // 是脚的概率
  bef_ai_tt_key_point joints2d[BEF_FEET_KEY_POINT_NUM]; // 脚的2d关键点，66x2
  unsigned char* segment; // 腿部的分割
  bef_ai_rect segment_box; // 腿部分割的框
  float trans[12]; // 脚的3d姿态的旋转矩阵，3x4
} bef_ai_foot, *ptr_bef_ai_foot;


typedef struct bef_ai_foot_ret_st {
  bef_ai_foot p_feet[BEF_MAX_FEET_NUM]; // foot 信息
  int feet_count; // 检出的feet总数
} bef_ai_foot_ret, *ptr_bef_ai_foot_ret;


typedef void *bef_ai_foot_sdk_handle;


/**
 * @brief 模型参数类型
 *
 */
typedef enum {
  BEF_kFootEdgeMode = 1,
}bef_ai_foot_param_type;


/**
 * @brief 模型枚举，有些模块可能有多个模型
 *
 */
typedef enum  {
  BEF_FootJoints2dModel = 1,
  BEF_FootJoints3dModel = 2,  ///< 暂时无用
  BEF_FootDetectionModel = 3,
  BEF_FootFilterModel = 4,
  BEF_FootLeftRightModel = 5,
  BEF_LegSegModel = 6,
}bef_ai_foot_model_type;


BEF_SDK_API bef_effect_result_t
bef_effect_ai_foot_detect_create(bef_ai_foot_sdk_handle *handle);

BEF_SDK_API bef_effect_result_t
bef_effect_ai_foot_detect(
                       bef_ai_foot_sdk_handle handle,
                       const unsigned char *image,
                       bef_ai_pixel_format pixel_format,
                       int image_width,
                       int image_height,
                       int image_stride,
                       bef_ai_rotate_type orientation,
                       bef_ai_foot_ret *p_foot_result);

BEF_SDK_API bef_effect_result_t
bef_effect_ai_foot_detect_setmodel(bef_ai_foot_sdk_handle handle,
                                   bef_ai_foot_model_type type,
                                   const char * strModelPath);


BEF_SDK_API bef_effect_result_t
bef_effect_ai_foot_detect_setparam(bef_ai_foot_sdk_handle handle,
                                   bef_ai_foot_param_type type,
                                   float value);



BEF_SDK_API bef_effect_result_t
bef_effect_ai_foot_render_resolution(bef_ai_foot_sdk_handle handle,
                                     int width,
                                     int height);

BEF_SDK_API bef_ai_foot_ret*
bef_effect_ai_foot_assign_memory(bef_ai_foot_sdk_handle handle);

BEF_SDK_API bef_effect_result_t
bef_effect_ai_foot_release_memory(bef_ai_foot_ret* result);

BEF_SDK_API bef_effect_result_t
bef_effect_ai_foot_detect_destroy(bef_ai_foot_sdk_handle handle);


 /**
  * @brief 足部检测授权
  * @param [in] handle Created hand detect handle
  *                    已创建的足部检测句柄
  * @param [in] license 授权文件字符串
  * @param [in] length  授权文件字符串长度
  * @return If succeed return BEF_RESULT_SUC, other value please refer bef_effect_ai_public_public_define.h
  *         成功返回 BEF_RESULT_SUC, 授权码非法返回 BEF_RESULT_INVALID_LICENSE ，其它失败返回相应错误码, 具体请参考 bef_effect_ai_public_public_define.h
  */

 #if defined(__ANDROID__) || defined(TARGET_OS_ANDROID)
 BEF_SDK_API bef_effect_result_t bef_effect_ai_foot_check_license(JNIEnv* env, jobject context,
         bef_effect_handle_t handle, const char *licensePath);
 #else
 #ifdef __APPLE__
 BEF_SDK_API bef_effect_result_t bef_effect_ai_foot_check_license(bef_effect_handle_t handle,
         const char *licensePath);
 #else
 BEF_SDK_API bef_effect_result_t bef_effect_ai_foot_check_license(bef_effect_handle_t handle,
 const char *licensePath);
 #endif
 #endif


#endif // _BEF_EFFECT_FOOT_DETECT_AI_H_
