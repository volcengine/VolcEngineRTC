
#ifndef ANDROIDDEMO_BEF_EFFECT_AI_C1_H
#define ANDROIDDEMO_BEF_EFFECT_AI_C1_H


#if defined(__ANDROID__) || defined(TARGET_OS_ANDROID)
#include <jni.h>
#endif

#include "bef_effect_ai_public_define.h"


#define BEF_AI_C1_NUM_CLASSES 22
typedef unsigned long long bef_ai_c1_handle;

/*
 * @brief 模型枚举
 **/
typedef enum {
    BEF_AI_C1_MODEL_SMALL = 0x00000001,
    BEF_AI_C1_MODEL_LARGE = 0x00000002
} bef_ai_c1_model_type;

typedef enum {
    BEF_AI_C1_USE_VIDEO_MODE = 1,  //默认值为1，表示视频模式, 0:图像模式
    BEF_AI_C1_USE_MultiLabels = 2,  //默认为0， 表示不用多标签模式，1：多标签模式
} bef_ai_c1_param_type;

typedef struct {
    float prob;                     // 置信度
    bool satisfied;                 // 是否检测到
} bef_ai_c1_category;

typedef struct {
    bef_ai_c1_category items[BEF_AI_C1_NUM_CLASSES];
} bef_ai_c1_output;

BEF_SDK_API
bef_effect_result_t bef_effect_ai_c1_create(bef_ai_c1_handle *handle, bef_ai_c1_model_type modelType, const char *modelPath);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_c1_check_license(bef_ai_c1_handle handle, const char *licensePath);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_c1_check_onine_license(bef_ai_c1_handle handle, const char *licensePath);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_c1_detect(bef_ai_c1_handle handle,
                                            const unsigned char *image,
                                            bef_ai_pixel_format pixelFormat,
                                            int imageWidth,
                                            int imageHeight,
                                            int imageStride,
                                            bef_ai_rotate_type rotation,
                                            bef_ai_c1_output *result);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_c1_set_param(bef_ai_c1_handle handle, bef_ai_c1_param_type type, float value);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_c1_release(bef_ai_c1_handle handle);

#endif //ANDROIDDEMO_BEF_EFFECT_AI_C1_H
