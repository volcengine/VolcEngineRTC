
#ifndef ANDROIDDEMO_BEF_EFFECT_AI_SKIN_SEGMENTATION_H
#define ANDROIDDEMO_BEF_EFFECT_AI_SKIN_SEGMENTATION_H

#include "bef_effect_ai_public_define.h"

/**
 * @brief 输出结果
 *
 */
typedef struct
{
    int width;
    int height;
    unsigned char* mask;
} bef_ai_skin_segmentation_ret;


/**
 * @brief 模型参数类型
 *
 */
typedef enum {
    BEF_AI_SKIN_SEG_MODEL_KEY = 0,     // 设置皮肤分割模型的key，默认tt_skin_seg, string
    BEF_AI_SKIN_SEG_IS_NEED_FACE = 1,  // 是否加载人脸模型以去除五官皮肤, int
} bef_ai_skin_segmentation_param_type;

bef_effect_result_t SkinSegmentation_ReleaseHandle(bef_effect_handle_t handle);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_skin_segmentation_create(bef_effect_handle_t *handle);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_skin_segmentation_init(bef_effect_handle_t handle, const char *modelPath);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_skin_segmentation_detect(bef_effect_handle_t handle,
                                                           const unsigned char *image,
                                                           bef_ai_pixel_format pixel_format,
                                                           int image_width,
                                                           int image_height,
                                                           int image_stride,
                                                           bef_ai_rotate_type orientation,
                                                           bef_ai_skin_segmentation_ret *result);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_skin_segmentation_set_paramS(bef_effect_handle_t handle, bef_ai_skin_segmentation_param_type type, const char *value);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_skin_segmentation_set_paramI(bef_effect_handle_t handle, bef_ai_skin_segmentation_param_type type, int value);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_skin_segmentation_release(bef_effect_handle_t handle);

/**
 * @brief 皮肤分割授权
 * @param [in] handle Created skeleton detect handle
 *                    已创建的皮肤分割句柄
 * @param [in] license 授权文件字符串
 * @param [in] length  授权文件字符串长度
 * @return If succeed return BEF_RESULT_SUC, other value please refer bef_effect_ai_public_define.h
 *         成功返回 BEF_RESULT_SUC, 授权码非法返回 BEF_RESULT_INVALID_LICENSE ，其它失败返回相应错误码, 具体请参考 bef_effect_ai_public_define.h
 */
BEF_SDK_API
bef_effect_result_t bef_effect_ai_skin_segmentation_check_license(bef_effect_handle_t handle, const char *licensePath);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_skin_segmentation_check_online_license(bef_effect_handle_t handle, const char *licensePath);

#endif //ANDROIDDEMO_BEF_EFFECT_AI_SKIN_SEGMENTATION_H
