
#ifndef ANDROIDDEMO_BEF_EFFECT_AI_DYNAMIC_GESTURE_H
#define ANDROIDDEMO_BEF_EFFECT_AI_DYNAMIC_GESTURE_H

#include "bef_effect_ai_public_define.h"

#define BEF_AI_DYNAMIC_GESTURE_SWIPING_LEFT 0
#define BEF_AI_DYNAMIC_GESTURE_SWIPING_RIGHT 1
#define BEF_AI_DYNAMIC_GESTURE_SWIPING_DOWN 2
#define BEF_AI_DYNAMIC_GESTURE_SWIPING_UP 3
#define BEF_AI_DYNAMIC_GESTURE_SLIDING_TWO_FINGERS_LEFT 4
#define BEF_AI_DYNAMIC_GESTURE_SLIDING_TWO_FINGERS_RIGHT 5
#define BEF_AI_DYNAMIC_GESTURE_SLIDING_TWO_FINGERS_DOWN 6
#define BEF_AI_DYNAMIC_GESTURE_ZOOMING_IN_WITH_FULL_HAND 7
#define BEF_AI_DYNAMIC_GESTURE_ZOOMING_OUT_WITH_FULL_HAND 8
#define BEF_AI_DYNAMIC_GESTURE_ZOOMING_IN_WITH_TWO_FINGERS 9
#define BEF_AI_DYNAMIC_GESTURE_ZOOMING_OUT_WITH_TWO_FINGERS 10
#define BEF_AI_DYNAMIC_GESTURE_THUMB_UP 11
#define BEF_AI_DYNAMIC_GESTURE_THUMB_DOWN 12
#define BEF_AI_DYNAMIC_GESTURE_SHAKING_HAND 13
#define BEF_AI_DYNAMIC_GESTURE_STOP_SIGN 14
#define BEF_AI_DYNAMIC_GESTURE_DRUMMING_FINGERS 15
#define BEF_AI_DYNAMIC_GESTURE_NO_GESTURE 16

#define BEF_MAX_GESTURE_HAND_NUM 2

/**
 * @brief 模型参数类型
 *
 */
typedef enum {
    BEF_AI_DYNGEST_REFRESH_FRAME_INTERVAL = 0,     // 设置检测刷新帧数, 暂不支持
    BEF_AI_DYNGEST_NUM_REQ_FRAMES = 1,             // 设置多帧处理动态手势输出结果
    BEF_AI_DYNGEST_FRAMES_INTERVAL = 2,            // 设置隔帧处理
    BEF_AI_DYNAMIC_GESTURE_MODEL_GESTURE_CLS = 3,  // 设置模型类型
} bef_ai_dynamic_gesture_param_type;

/**
 * @brief 封装预测接口的返回值
 *
 * @note 不同的算法，可以在这里添加自己的自定义数据
 */
typedef struct {
    int action;
    float action_score;
} bef_ai_dynamic_gesture_info;

/// @brief 检测结果
typedef struct {
    bef_ai_dynamic_gesture_info p_gestures[BEF_MAX_GESTURE_HAND_NUM]; ///< 检测到的动态手势信息
    int gesture_count;                                                ///< 检测到的手势数量；
} bef_ai_dynamic_gesture_ret;

bef_effect_result_t DynamicGesture_ReleaseHandle(bef_effect_handle_t handle);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_dynamic_gesture_create(bef_effect_handle_t *handle);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_dynamic_gesture_init(bef_effect_handle_t handle, const char *modelPath);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_dynamic_gesture_detect(bef_effect_handle_t handle,
                                                         const unsigned char *image,
                                                         bef_ai_pixel_format pixel_format,
                                                         int image_width,
                                                         int image_height,
                                                         int image_stride,
                                                         bef_ai_rotate_type orientation,
                                                         int *gesture_info_num,
                                                         bef_ai_dynamic_gesture_info **gesture_info);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_dynamic_gesture_set_paramS(bef_effect_handle_t handle, bef_ai_dynamic_gesture_param_type type, const char *value);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_dynamic_gesture_set_paramF(bef_effect_handle_t handle, bef_ai_dynamic_gesture_param_type type, float value);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_dynamic_gesture_set_paramI(bef_effect_handle_t handle, bef_ai_dynamic_gesture_param_type type, int value);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_dynamic_gesture_release(bef_effect_handle_t handle);

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
bef_effect_result_t bef_effect_ai_dynamic_gesture_check_license(bef_effect_handle_t handle, const char *licensePath);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_dynamic_gesture_check_online_license(bef_effect_handle_t handle, const char *licensePath);

#endif //ANDROIDDEMO_BEF_EFFECT_AI_DYNAMIC_GESTURE_H
