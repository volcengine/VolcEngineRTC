//
//

#ifndef ANDROIDDEMO_BEF_EFFECT_AI_C2_H
#define ANDROIDDEMO_BEF_EFFECT_AI_C2_H

#if defined(__ANDROID__) || defined(TARGET_OS_ANDROID)
#include <jni.h>
#endif

#include "bef_effect_ai_public_define.h"

typedef unsigned  long long bef_ai_c2_handle;

#define C3_NUM_CLASS 208

typedef struct {
    int id;                     // id
    float confidence;           // 置信度
    bool satisfied;             // 是否检测到
    float thresh;
} bef_ai_c2_category_item;

/**
 * @brief 模型参数类型
 *
 */
typedef enum {
    BEF_AI_C2_USE_EDGE_MODE,   //默认值为1，表示视频模式, 0:图像模式
} bef_ai_c2_param_type;


/**
 * @brief 模型枚举，有些模块可能有多个模型
 *
 */
typedef enum {
    BEF_AI_kC2Model1 = 1,
} bef_ai_c2_model_type;

/**
 * @brief 封装预测接口的返回值
 */
typedef struct {
    bef_ai_c2_category_item items[C3_NUM_CLASS];    // 类别信息
    int n_classes;                                  // 数量
} bef_ai_c2_ret;


BEF_SDK_API
bef_effect_result_t bef_effect_ai_c2_create(bef_ai_c2_handle *handle);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_c2_check_license(bef_ai_c2_handle handle, const char *licensePath);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_c2_check_online_license(bef_ai_c2_handle handle, const char* licensePath);


BEF_SDK_API
bef_effect_result_t bef_effect_ai_c2_detect(bef_ai_c2_handle handle,
                                            const unsigned char *image,
                                            bef_ai_pixel_format pixelFormat,
                                            int imageWidth,
                                            int imageHeight,
                                            int imageStride,
                                            bef_ai_rotate_type rotation,
                                            bef_ai_c2_ret *result);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_c2_set_model(bef_ai_c2_handle handle, bef_ai_c2_model_type type, const char *modelPath);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_c2_set_paramF(bef_ai_c2_handle handle, bef_ai_c2_param_type type, float value);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_c2_set_paramS(bef_ai_c2_handle handle, bef_ai_c2_param_type type, char *value);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_c2_release(bef_ai_c2_handle handle);


#endif //ANDROIDDEMO_BEF_EFFECT_AI_C2_H
