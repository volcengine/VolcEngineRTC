
#ifndef ANDROIDDEMO_BEF_EFFECT_AI_license_cake_H
#define ANDROIDDEMO_BEF_EFFECT_AI_license_cake_H

#if defined(__ANDROID__) || defined(TARGET_OS_ANDROID)
#include <jni.h>
#endif

#include "bef_effect_ai_public_define.h"

#define LICENSECAKE_DEDETECTION_MAX_DETECTED_NUM 2
/**
 * @brief 模型参数类型
 */
typedef enum {
    ALGORITHM_PARAMS_KEY_LICENSEFACE_DEDETECTION_DETECT_INTERVAL = 0,                   // 定义执行检测算法帧率，例如每隔n帧执行一次检测算法
    ALGORITHM_PARAMS_KEY_LICENSEFACE_DEDETECTION_SIDE_MODEL_LEN = 1,                    // 定义执行检测算法的输入分辨率
    ALGORITHM_PARAMS_KEY_LICENSEFACE_DEDETECTION_DETECT_USE_REGRESSOR = 2,              // 定义是否执行跟踪（回归）算法，暂未ready
    ALGORITHM_PARAMS_KEY_LICENSEFACE_DEDETECTION_DETECT_USE_TRACKER = 3,                // 定义是否执行跟踪（卡尔曼滤波）算法，暂未ready
} bef_ai_license_cake_param_type;

/**
 * @brief 封装预测接口的返回值
 *
 * @note 不同的算法，可以在这里添加自己的自定义数据
 */
typedef struct {
    int id;         //返回当前检测目标的实例ID
    int label;      //返回当前检测目标的类别
    float det_score;//返回当前检测目标的置信度
    bef_ai_rect rect;     //返回当前检测目标的bbox位置
} bef_ai_license_cake_info;

/*
 * @brief 检测结果
 *@ */
typedef struct  {
    int Licensecake_count;  /**< 检测到的Licensecake数目, p_Licensecakes数组中, 只有前Licensecake_count个结果是有效的, 后面的是无效 */
    bef_ai_license_cake_info p_Licensecakes[LICENSECAKE_DEDETECTION_MAX_DETECTED_NUM]; /**< 检测到的Licensecake信息 */
} bef_ai_license_cake_ret;


bef_effect_result_t LicenseCake_ReleaseHandle(bef_effect_handle_t handle);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_license_cake_create(bef_effect_handle_t *handle);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_license_cake_init(bef_effect_handle_t handle, const char *modelPath);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_license_cake_detect(bef_effect_handle_t handle,
                                                         const unsigned char *image,
                                                         bef_ai_pixel_format pixel_format,
                                                         int image_width,
                                                         int image_height,
                                                         int image_stride,
                                                         bef_ai_rotate_type orientation,
                                                         int *gesture_info_num,
                                                         bef_ai_license_cake_info **gesture_info);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_license_cake_set_paramS(bef_effect_handle_t handle, bef_ai_license_cake_param_type type, const char *value);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_license_cake_set_paramF(bef_effect_handle_t handle, bef_ai_license_cake_param_type type, float value);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_license_cake_set_paramI(bef_effect_handle_t handle, bef_ai_license_cake_param_type type, int value);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_license_cake_release(bef_effect_handle_t handle);

/**
 * @brief 动态手势授权
 * @param [in] handle Created dynamic gesture handle
 *                    已创建的动态手势句柄
 * @param [in] license 授权文件字符串
 * @param [in] length  授权文件字符串长度
 * @return If succeed return BEF_RESULT_SUC, other value please refer bef_effect_ai_public_define.h
 *         成功返回 BEF_RESULT_SUC, 授权码非法返回 BEF_RESULT_INVALID_LICENSE ，其它失败返回相应错误码, 具体请参考 bef_effect_ai_public_define.h
 */

BEF_SDK_API
bef_effect_result_t bef_effect_ai_license_cake_check_license(bef_effect_handle_t handle, const char *licensePath);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_license_cake_check_online_license(bef_effect_handle_t handle, const char *licensePath);

#endif //ANDROIDDEMO_BEF_EFFECT_AI_license_cake_H
