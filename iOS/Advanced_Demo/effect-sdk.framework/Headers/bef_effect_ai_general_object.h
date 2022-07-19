//
// Created by QunZhang on 2020/4/21.
//

#ifndef ANDROIDDEMO_BEF_EFFECT_AI_GENERAL_OBJECT_H
#define ANDROIDDEMO_BEF_EFFECT_AI_GENERAL_OBJECT_H

#if defined(__ANDROID__) || defined(TARGET_OS_ANDROID)
#include <jni.h>
#endif

#include "bef_effect_ai_public_define.h"

/**
 * @brief 为算法推荐配置的算法参数
 * InputWidth:  输入图片的宽
 * InputHeight: 输入图片的高
 */
typedef struct bef_ai_general_object_detection_recommend_config_st {
    int InputWidth = 128;
    int InputHeight = 224;
} bef_ai_general_object_detection_recommend_config;

/**
 * @brief 模型参数类型
 * kDetectShortSideLen: 检测模型输入图片的短边边长，值越大，小目标检测效果越好，初始值为128
 */
typedef enum bef_ai_general_object_detection_param_type_st {
    BEF_AI_GENERAL_OBJECT_DETECT_SHORT_SIDE_LEN = 1,
} bef_ai_general_object_detection_param_type;

/**
 * @brief 模型枚举
 * kPureDetect: 仅做物体检测
 */
typedef enum bef_general_object_detection_model_type_st {
    BEF_AI_GENERAL_OBJECT_PURE_DETECT = 1,
    BEF_AI_GENERAL_OBJECT_DETECT_CLS = 2,
    BEF_AI_GENERAL_OBJECT_CLS_NAME = 3,
    BEF_AI_GENERAL_OBJECT_DETECT_TRACK = 4
} bef_general_object_detection_model_type;

/**
 * @brief 物体信息
 * bbox:  物体在图片中的位置
 * label: 物体的类别，类别详情请联系：tianyuan@bytedance.com
 */
typedef struct bef_ai_object_info_st {
    bef_ai_rect bbox;
    int label;
} bef_ai_object_info;

/**
 * @brief 封装预测接口的返回值
 * obj_infos: 物体信息
 * obj_num:   物体数量
 */
typedef struct bef_ai_general_object_detection_result_st {
    bef_ai_object_info *obj_infos;
    int obj_num;
} bef_ai_general_object_detection_result;

typedef struct bef_ai_track_box_st {
    int x;  // 左上角x坐标
    int y;  // 左上角y坐标
    int w;  // 宽 width
    int h;  // 高 height
} bef_ai_track_box;

typedef struct bef_ai_track_ret_st {
    int tracker_id;  // 跟踪实例的ID（也可以看作跟踪目标的ID）
    float score;     // 对这次结果的置信度
    bef_ai_track_box roi;         // 预测的区域
} bef_ai_track_ret;

typedef struct bef_ai_tracking_result_st {
    int tracker_ret_len;
    bef_ai_track_ret* tracker_rets;
} bef_ai_tracking_result;

/**
 * @brief 创建检测名柄
 * @param [out] handle Created hand detect handle
 *                     创建的检测句柄
 * @return If succeed return BEF_RESULT_SUC, other value please see bef_effect_ai_public_define.h
 *         成功返回 BEF_RESULT_SUC, 失败返回相应错误码, 具体请参考 bef_effect_ai_public_public_define.h
 */
BEF_SDK_API bef_effect_result_t
bef_effect_ai_general_object_create(
        bef_effect_handle_t  *handle
        );

/**
 * @brief 传入检测图片
 * @param [in] handle Created hand detect handle
 *                    已创建的人手检测句柄
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
 * @param [in] orientation Image orientation
 *                         输入图像的转向，具体请参考 bef_effect_ai_public_public_define.h 中的 bef_ai_rotate_type
 * @param [in] result
 * @return If succeed return BEF_RESULT_SUC, other value please see bef_effect_ai_public_public_define.h
 *         成功返回 BEF_RESULT_SUC, 失败返回相应错误码, 具体请参考 bef_effect_ai_public_public_define.h
 */
BEF_SDK_API bef_effect_result_t
bef_effect_ai_general_object_detect(
        bef_effect_handle_t handle,
        const unsigned char *image,
        bef_ai_pixel_format pixel_format,
        int image_width,
        int image_height,
        int image_stride,
        bef_ai_rotate_type orientation,
        bef_ai_general_object_detection_result *result
        );

/**
 * 加载检测模型
 * @param handle 检测句柄
 * @param type 模型类型
 * @param model_path 模型绝对路径
 * @return 成功返回 BEF_RESULT_SUC, 失败返回相应错误码, 具体请参考 bef_effect_ai_public_public_define.h
 */
BEF_SDK_API bef_effect_result_t
bef_effect_ai_general_object_load_model(
        bef_effect_handle_t handle,
        bef_general_object_detection_model_type type,
        const char *model_path
        );

/**
 * 设置 float 参数
 * @param handle 检测句柄
 * @param type 参数类型
 * @param value 参数值
 * @return 成功返回 BEF_RESULT_SUC, 失败返回相应错误码, 具体请参考 bef_effect_ai_public_public_define.h
 */
BEF_SDK_API bef_effect_result_t
bef_effect_ai_general_object_set_paramf(
        bef_effect_handle_t handle,
        bef_ai_general_object_detection_param_type type,
        float value
        );

/**
 * 设置字符串参数
 * @param handle 检测句柄
 * @param type 参数类型
 * @param value 参数值
 * @return 成功返回 BEF_RESULT_SUC, 失败返回相应错误码, 具体请参考 bef_effect_ai_public_public_define.h
 */
BEF_SDK_API bef_effect_result_t
bef_effect_ai_general_object_set_params(
        bef_effect_handle_t handle,
        bef_ai_general_object_detection_param_type type,
        const char *value
        );

/**
 * 销毁检测句柄
 * @param handle 检测句柄
 * @return 成功返回 BEF_RESULT_SUC, 失败返回相应错误码, 具体请参考 bef_effect_ai_public_public_define.h
 */
BEF_SDK_API bef_effect_result_t
bef_effect_ai_general_object_release(
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
BEF_SDK_API bef_effect_result_t bef_effect_ai_general_object_check_license(JNIEnv* env, jobject context,
        bef_effect_handle_t handle, const char *licensePath);
#else
#ifdef __APPLE__
BEF_SDK_API bef_effect_result_t bef_effect_ai_general_object_check_license(bef_effect_handle_t handle,
        const char *licensePath);
#endif
#endif

#endif //ANDROIDDEMO_BEF_EFFECT_AI_GENERAL_OBJECT_H
