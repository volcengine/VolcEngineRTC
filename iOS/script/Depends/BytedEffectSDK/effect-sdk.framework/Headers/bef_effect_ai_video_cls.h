
#ifndef ANDROIDDEMO_BEF_EFFECT_AI_VIDEO_CLS_H
#define ANDROIDDEMO_BEF_EFFECT_AI_VIDEO_CLS_H

#if defined(__ANDROID__) || defined(TARGET_OS_ANDROID)
#include <jni.h>
#endif

#include "bef_effect_ai_public_define.h"

typedef unsigned long long bef_ai_video_cls_handle;

/**
 * @brief 模型参数类型
 *
 */
typedef enum {
    BEF_AI_kVideoClsEdgeMode = 1,        ///< TODO: 根据实际情况修改
} bef_ai_video_cls_param_type;


/**
 * @brief 模型枚举，有些模块可能有多个模型
 *
 */
typedef enum {
    BEF_AI_kVideoClsModel1 = 1,          ///< TODO: 根据实际情况更改
} bef_ai_video_cls_model_type;


/**
 * @brief 封装预测接口的输入数据
 *
 * @note 不同的算法，可以在这里添加自己的数据
 */
typedef struct {
    bef_ai_base_args *bases;           ///< 对视频帧数据做了基本的封装
    int is_last; //是否为最后一帧
} bef_ai_video_cls_args;


typedef struct {
    int id; //类别id
    float confidence; //类别的置信度
    float thres; //类别的默认阈值
} bef_ai_video_cls_type;


/**
 * @brief 封装预测接口的返回值
 *
 * @note 不同的算法，可以在这里添加自己的自定义数据
 */
typedef struct {
    // 下面只做举例，不同的算法需要单独设置
    bef_ai_video_cls_type* classes;//内存由sdk分配，由sdk释放
    int n_classes;
} bef_ai_video_cls_ret;

/**
 * @brief 封装预测接口的返回值
 *
 * @note 不同的算法，可以在这里添加自己的自定义数据
 */
typedef struct {
    float* feat;//内存由sdk分配，由sdk释放
    int len_feat;
} bef_ai_video_cls_feat;

BEF_SDK_API
bef_effect_result_t bef_effect_ai_video_cls_create(bef_ai_video_cls_handle *handle);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_video_cls_check_license(bef_ai_video_cls_handle handle, const char *licensePath);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_video_cls_check_online_license(bef_ai_video_cls_handle handle, const char *licensePath);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_video_cls_detect(bef_ai_video_cls_handle handle,
                                                    bef_ai_video_cls_args *args,
                                                    bef_ai_video_cls_ret *result);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_video_cls_set_model(bef_ai_video_cls_handle handle, bef_ai_video_cls_model_type type, const char *modelPath);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_video_cls_set_paramF(bef_ai_video_cls_handle handle, bef_ai_video_cls_param_type type, float value);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_video_cls_set_paramS(bef_ai_video_cls_handle handle, bef_ai_video_cls_param_type type, char *value);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_video_cls_release(bef_ai_video_cls_handle handle);

#endif //ANDROIDDEMO_BEF_EFFECT_AI_VIDEO_CLS_H
