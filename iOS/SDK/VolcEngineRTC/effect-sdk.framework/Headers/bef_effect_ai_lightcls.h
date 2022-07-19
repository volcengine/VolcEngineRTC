#ifndef ANDROIDDEMO_BEF_EFFECT_AI_LIGHTCLS_H
#define ANDROIDDEMO_BEF_EFFECT_AI_LIGHTCLS_H

#if defined(__ANDROID__) || defined(TARGET_OS_ANDROID)
#include <jni.h>
#endif

#include "bef_effect_ai_public_define.h"

#define LIGHT_CLASSES 7

//typedef enum {
//    Indoor_Yellow = 0,
//    Indoor_White,
//    Indoor_weak,
//    Sunny,
//    Cloudy,
//    Night,
//    Backlight
//} bef_ai_light_cls_light_type;

typedef struct bef_ai_light_cls_result_st {
    int selected_index;
    float prob;
} bef_ai_light_cls_result;


/**
 @brief 创建光线检测句柄
 
 @param [in] handle 待创建的光线检测句柄
 
 @param [in] model_path 模型文件路径
 
 @return If succeed return BEF_RESULT_SUC, other value please see bef_effect_ai_public_define.h
         成功返回 BEF_RESULT_SUC, 失败返回相应错误码, 具体请参考 bef_effect_ai_public_define.h
 */
BEF_SDK_API bef_effect_result_t
bef_effect_ai_lightcls_create(
        bef_effect_handle_t *handle,
        const char *model_path,
        int fps
        );

/**
 @brief 光线检测
 @param [in] handle Created light detect handle
                    已创建的光线检测句柄
 @param [in] image Image base address
                   输入图片的数据指针
 @param [in] pixel_format Pixel format of input image
                          输入图片的格式
 @param [in] image_width  Image width
                          输入图像的宽度 (以像素为单位)
 @param [in] image_height Image height
                          输入图像的高度 (以像素为单位)
 @param [in] image_stride Image stride in each row
                          输入图像每一行的步长 (以像素为单位)
 @param [in] orientation Image orientation
                         输入图像的转向，具体请参考 bef_effect_ai_public_define.h 中的 bef_rotate_type
 @param [out] bef_ai_light_cls_result  存放结果信息，需外部分配好内存
 @return If succeed return BEF_RESULT_SUC, other value please see bef_effect_ai_public_define.h
         成功返回 BEF_RESULT_SUC, 失败返回相应错误码, 具体请参考 bef_effect_ai_public_define.h
*/
BEF_SDK_API bef_effect_result_t
bef_effect_ai_lightcls_detect(
        bef_effect_handle_t handle,
        const unsigned char *image,
        bef_ai_pixel_format pixel_format,
        int image_width,
        int image_height,
        int image_stride,
        bef_ai_rotate_type orientation,
        bef_ai_light_cls_result *result
        );

/**
 @param [in] handle Destroy the created light detect handle
                    销毁创建的光线检测句柄
*/
BEF_SDK_API bef_effect_result_t
bef_effect_ai_lightcls_release(
        bef_effect_handle_t handle
        );

/**
 @brief 光线检测授权
 @param [in] handle Created light detect handle
                    已创建的光线检测句柄
 @param [in] license 授权文件字符串
 @param [in] length  授权文件字符串长度
 @return If succeed return BEF_RESULT_SUC, other value please refer bef_effect_ai_public_define.h
         成功返回 BEF_RESULT_SUC, 授权码非法返回 BEF_RESULT_INVALID_LICENSE ，其它失败返回相应错误码, 具体请参考 bef_effect_ai_public_define.h
*/
#if defined(__ANDROID__) || defined(TARGET_OS_ANDROID)
BEF_SDK_API bef_effect_result_t
bef_effect_ai_lightcls_check_license(
        JNIEnv* env,
        jobject context,
        bef_effect_handle_t handle,
        const char *licensePath
        );
#else
#ifdef __APPLE__
BEF_SDK_API bef_effect_result_t
bef_effect_ai_lightcls_check_license(
        bef_effect_handle_t handle,
        const char *licensePath
        );
#endif
#endif

BEF_SDK_API bef_effect_result_t
bef_effect_ai_lightcls_check_online_license(bef_effect_handle_t handle, const char *licensePath);

#endif //ANDROIDDEMO_BEF_EFFECT_AI_LIGHTCLS_H
