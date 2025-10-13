
#ifndef BEF_EFFECT_AI_ACTION_RECOGNITION_H
#define BEF_EFFECT_AI_ACTION_RECOGNITION_H

#include "bef_effect_ai_public_define.h"

#if defined(__ANDROID__) || defined(TARGET_OS_ANDROID)
#include<jni.h>
#endif

#define BEF_AI_ACTION_RECOGNITION_MAX_POINT_NUM 18

// 反馈的身体部位类别
typedef enum {
    BEF_AI_ACTION_RECOGNITION_FeedbackNone = 0,
    BEF_AI_ACTION_RECOGNITION_FeedbackLeftArm = 1,// 左臂
    BEF_AI_ACTION_RECOGNITION_FeedbackRightArm = 2, // 右臂
    BEF_AI_ACTION_RECOGNITION_FeedbackLeftLeg = 3, // 左腿
    BEF_AI_ACTION_RECOGNITION_FeedbackRightLeg = 4, // 右腿
} bef_ai_action_recognition_feedback_body_part;

// 初始姿态类别
typedef enum {
    BEF_AI_ACTION_RECOGNITION_Stand = 1, //站立
    BEF_AI_ACTION_RECOGNITION_Lying = 2, //平躺
    BEF_AI_ACTION_RECOGNITION_Sitting = 3, //坐姿
    BEF_AI_ACTION_RECOGNITION_SideLeft = 4,
    BEF_AI_ACTION_RECOGNITION_SideRight = 5

} bef_ai_action_recognition_start_pose_type;

//动作计数结果信息
typedef struct bef_ai_action_recognition_result_st {
    bef_ai_tt_key_point keypoints[BEF_AI_ACTION_RECOGNITION_MAX_POINT_NUM]; // 检测到的骨骼信息
    bef_ai_action_recognition_feedback_body_part feed_body_part;  // 反馈的身体部位类别
    bef_ai_tt_key_point feedback_keypoints[BEF_AI_ACTION_RECOGNITION_MAX_POINT_NUM*2]; // 检测到的反馈骨骼信息
    int feedback_kp_count;  // 检测到的反馈骨骼信息数量，feedback_keypoints的实际长度
    bool recognize_succeed; // 是否计数成功，为true时，表示计数成功，界面可以增加计数
    bool is_feedback_valid; // 反馈信息是否有效，为true时，表示信息有效，界面可以显示反馈信息
    
} bef_ai_action_recognition_result;

//初始姿态检测结果信息
typedef struct bef_ai_action_recognition_start_pose_result_st {
    bool is_detected; // 是否通过初始姿态检测，为true时，表示通过检测，可以开始计数
} bef_ai_action_recognition_start_pose_result;

/**
 * @brief 创建动作识别的句柄
 * @param [in] model_path 模型文件路径
 * @param [out] handle    Created action_recognition handle
 *                        创建的动作识别句柄
 * @return If succeed return BEF_RESULT_SUC, other value please see bef_effect_ai_public_define.h
 *         成功返回 BEF_RESULT_SUC, 失败返回相应错误码, 具体请参考 bef_effect_ai_public_define.h
 */
BEF_SDK_API bef_effect_result_t
bef_effect_ai_action_recognition_create(
                             const char *model_path,
                             bef_effect_handle_t *handle
                             );

/**
 * @param [in] handle Destroy the created action_recognition handle
 *                    销毁创建的动作识别句柄
 */
BEF_SDK_API void
bef_effect_ai_action_recognition_destroy(
                              bef_effect_handle_t handle
                              );

/**
 * @brief 设置动作识别模板
 * @param [in] handle    Created action_recognition handle
 *                        已创建的动作识别句柄
 * @param [in] template_path 模板文件路径
 
 * @return If succeed return BEF_RESULT_SUC, other value please see bef_effect_ai_public_define.h
 *         成功返回 BEF_RESULT_SUC, 失败返回相应错误码, 具体请参考 bef_effect_ai_public_define.h
 */
BEF_SDK_API bef_effect_result_t
bef_effect_ai_action_recognition_set_template(bef_effect_handle_t handle, const char *template_path);

/**
 * @brief 设置动作识别阈值
 * @param [in] handle    Created action_recognition handle
 *                        已创建的动作识别句柄
 * @param [in] threshold 模板阈值
 
 * @return If succeed return BEF_RESULT_SUC, other value please see bef_effect_ai_public_define.h
 *         成功返回 BEF_RESULT_SUC, 失败返回相应错误码, 具体请参考 bef_effect_ai_public_define.h
 */
BEF_SDK_API bef_effect_result_t
bef_effect_ai_action_recognition_set_template_threshold(bef_effect_handle_t handle, float threshold);

/**
 * @brief 动作识别开始姿态检测
 * @param [in] handle Created action_recognition handle
 *                    已创建的骨骼句柄
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
 * @param [in] orientation  Image orientation
 *                          输入图像的转向，具体请参考 bef_effect_ai_public_define.h 中的 bef_rotate_type
 * @param [in] type pose type  姿势类型
 * @param [in, out] is_detected   detection result 检测结果
 * @return If succeed return BEF_RESULT_SUC, other value please see bef_effect_ai_public_define.h
 *         成功返回 BEF_RESULT_SUC, 失败返回相应错误码, 具体请参考 bef_effect_ai_public_define.h
 */
BEF_SDK_API bef_effect_result_t
bef_effect_ai_action_recognition_start_pose_detect(
                                                   bef_effect_handle_t handle,
                                                   const unsigned char *image,
                                                   bef_ai_pixel_format pixel_format,
                                                   int image_width,
                                                   int image_height,
                                                   int image_stride,
                                                   bef_ai_rotate_type orientation,
                                                   bef_ai_action_recognition_start_pose_type type,
                                                   bef_ai_action_recognition_start_pose_result* result);

/**
 * @brief 动作识别计数
 * @param [in] handle Created action_recognition handle
 *                    已创建的骨骼句柄
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
 * @param [in] confirm_time  count confirmation time
 *                          计数确认时长
 * @param [in] orientation  Image orientation
 *                          输入图像的转向，具体请参考 bef_effect_ai_public_define.h 中的 bef_rotate_type
 * @param [in, out] action_recognition_result  不可为nullptr
 * @return If succeed return BEF_RESULT_SUC, other value please see bef_effect_ai_public_define.h
 *         成功返回 BEF_RESULT_SUC, 失败返回相应错误码, 具体请参考 bef_effect_ai_public_define.h
 */
BEF_SDK_API bef_effect_result_t
bef_effect_ai_action_recognition_count(
                             bef_effect_handle_t handle,
                             const unsigned char *image,
                             bef_ai_pixel_format pixel_format,
                             int image_width,
                             int image_height,
                             int image_stride,
                             bef_ai_rotate_type orientation,
                             int confirm_time,
                             bef_ai_action_recognition_result *action_recognition_result
                             );

/**
 * @brief 人体关键点授权
 * @param [in] handle Created action_recognition handle
 *                    已创建的动作识别句柄
 * @param [in] license 授权文件字符串
 * @param [in] length  授权文件字符串长度
 * @return If succeed return BEF_RESULT_SUC, other value please refer bef_effect_ai_public_define.h
 *         成功返回 BEF_RESULT_SUC, 授权码非法返回 BEF_RESULT_INVALID_LICENSE ，其它失败返回相应错误码, 具体请参考 bef_effect_ai_public_define.h
 */

#if defined(__ANDROID__) || defined(TARGET_OS_ANDROID)
BEF_SDK_API bef_effect_result_t bef_effect_ai_action_recognition_check_license(JNIEnv* env, jobject context, bef_effect_handle_t handle, const char *licensePath);
#else
#ifdef __APPLE__
BEF_SDK_API bef_effect_result_t bef_effect_ai_action_recognition_check_license(bef_effect_handle_t handle, const char *licensePath);
#endif
#endif

BEF_SDK_API bef_effect_result_t
bef_effect_ai_action_recognition_check_online_license(bef_effect_handle_t handle, const char *licensePath);


#endif // BEF_EFFECT_AI_ACTION_RECOGNITION_H

