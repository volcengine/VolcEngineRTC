//
// Created by QunZhang on 2020/5/19.
//

#ifndef ANDROIDDEMO_BEF_EFFECT_AI_DYNAMIC_ACTION_H
#define ANDROIDDEMO_BEF_EFFECT_AI_DYNAMIC_ACTION_H

#if defined(__ANDROID__) || defined(TARGET_OS_ANDROID)
#include <jni.h>
#endif

#include "bef_effect_ai_public_define.h"

#define BEF_AI_DYNAMIC_ACTION_MAX_PERSON_NUM_ALLOWED 20
#define BEF_AI_DYNAMIC_ACTION_PERSON_KEY_POINT_NUM 18 // skeleton

// 人检测的返回结构体
// 结构体有默认值 调用方需要根据返回值是否是默认值 判断是否有相应的检测结果
typedef struct bef_ai_dynamic_action_info_st {
    int id;                       ///< 人的id，track_id
    int person_id;                ///< 人的id，来自于skeleton
    bef_ai_rect rect;                  ///< 人矩形框 默认: 0
    bef_ai_rect rect_stl;              ///< 人矩形框 默认: 0
    unsigned int action;          ///< 动态类别, 默认: 0
    unsigned int action_duration; ///< 动态类别的中间停留帧数, 默认: 0
    float action_score;           ///< 动态类别置信度 默认: 0
} bef_ai_dynamic_action_info, *p_bef_ai_dynamic_action_info;


typedef struct bef_ai_dynamic_action_sk_info_st {
    int id;                                                                     // 人的 id
    bef_ai_rect rect;                                                           // 人体框
    bef_ai_tt_key_point key_points[BEF_AI_DYNAMIC_ACTION_PERSON_KEY_POINT_NUM]; // 人体关键点
} bef_ai_dynamic_action_sk_info;

// dynamic action from skeleton
#define BEF_AI_DYNAMIC_ACTION_NO_ACTION 0            // NoAction: 无动作
#define BEF_AI_DYNAMIC_ACTION_PUSH_UP 1              // PushUp: 俯卧撑
#define BEF_AI_DYNAMIC_ACTION_SIT_UP 2               // SitUp: 仰卧起坐
#define BEF_AI_DYNAMIC_ACTION_ROW_FAST 3             // RowFast: 半身快速划船
#define BEF_AI_DYNAMIC_ACTION_ROW_SLOW 4             // RowSlow: 半身慢速划船
#define BEF_AI_DYNAMIC_ACTION_SQUAT_FRONT 5          // SquatFront: 正面下蹲
#define BEF_AI_DYNAMIC_ACTION_ROW_SLOW_FULL 6        // RowSlowFull: 全身慢速划船
#define BEF_AI_DYNAMIC_ACTION_ROW_FAST_FULL 7        // RowFastFull: 全身快速划船
#define BEF_AI_DYNAMIC_ACTION_JUMP_JACK 8            // JumpJack: 开合跳
#define BEF_AI_DYNAMIC_ACTION_SQUAT_PROFILE 9        // SquatProfile: 侧面下蹲

/// @brief 检测结果
typedef struct bef_ai_dynamic_action_result_st {
    // 检测到的人信息
    bef_ai_dynamic_action_info p_persons[BEF_AI_DYNAMIC_ACTION_MAX_PERSON_NUM_ALLOWED];
    // 检测到的人数目，p_persons 数组中，只有前person_count个结果是有效的，后面的是无效
    int person_count;

} bef_ai_dynamic_action_result, *p_bef_ai_dynamic_action_result;

typedef struct bef_ai_dynamic_action_sk_st {
    bef_ai_dynamic_action_sk_info sk_infos[BEF_AI_DYNAMIC_ACTION_MAX_PERSON_NUM_ALLOWED];
    int person_count;
} bef_ai_dynamic_action_sk;

typedef enum {
    BEF_AI_DYNAMIC_ACTION_REFRESH_FRAME_INTERVAL = 1,      // 设置检测刷新帧数, 暂不支持
    BEF_AI_DYNAMIC_ACTION_MAX_PERSON_NUM = 2,              // 设置最多人的个数，默认为1，目前最多设置为20；
} bef_ai_dynamic_action_param_type;

typedef enum {
    BEF_AI_DYNAMIC_ACTION_MODEL_SK = 0x0001,               // 人体skeleton模型
    BEF_AI_DYNAMIC_ACTION_MODEL_DETECT = 0x0002,           // 人体detection模型 (TODO)
    BEF_AI_DYNAMIC_ACTION_MODEL_DYNAMIC_ACTION = 0x0004,   // 动态姿态模型 (TODO)
} bef_ai_dynamic_action_model_type;                        // TODO: 其实这里以需要加载的能力为划分更好

BEF_SDK_API bef_effect_result_t
bef_effect_ai_dynamic_action_create(
        bef_effect_handle_t *handle,
        unsigned int config
);

BEF_SDK_API bef_effect_result_t
bef_effect_ai_dynamic_action_set_param(
        bef_effect_handle_t handle,
        bef_ai_dynamic_action_param_type type,
        float value
);

BEF_SDK_API bef_effect_result_t
bef_effect_ai_dynamic_action_load_model(
        bef_effect_handle_t handle,
        bef_ai_dynamic_action_model_type type,
        const char *model_path
);

BEF_SDK_API bef_effect_result_t
bef_effect_ai_dynamic_action_detect(
        bef_effect_handle_t handle,
        const unsigned char *image,
        bef_ai_pixel_format pixel_format,
        int image_width,
        int image_height,
        int image_stride,
        bef_ai_rotate_type orientation,
        unsigned long long detect_config,
        int delay_framecount,
        bef_ai_dynamic_action_result *result,
        bef_ai_dynamic_action_sk *sk_result
);

BEF_SDK_API bef_effect_result_t
bef_effect_ai_dynamic_action_release(
        bef_effect_handle_t handle
);

/**
 * @brief 通用物体检测授权
 * @param [in] handle Created hand detect handle
 *                    已创建的人手检测句柄
 * @param [in] license 授权文件字符串
 * @param [in] length  授权文件字符串长度
 * @return If succeed return BEF_RESULT_SUC, other value please refer bef_effect_ai_public_public_define.h
 *         成功返回 BEF_RESULT_SUC, 授权码非法返回 BEF_RESULT_INVALID_LICENSE ，其它失败返回相应错误码, 具体请参考 bef_effect_ai_public_public_define.h
 */

#if defined(__ANDROID__) || defined(TARGET_OS_ANDROID)
BEF_SDK_API bef_effect_result_t bef_effect_ai_dynamic_action_check_license(JNIEnv* env, jobject context,
        bef_effect_handle_t handle, const char *licensePath);
#else
#ifdef __APPLE__
BEF_SDK_API bef_effect_result_t bef_effect_ai_dynamic_action_check_license(bef_effect_handle_t handle,
        const char *licensePath);
#endif
#endif

#endif //ANDROIDDEMO_BEF_EFFECT_AI_DYNAMIC_ACTION_H
