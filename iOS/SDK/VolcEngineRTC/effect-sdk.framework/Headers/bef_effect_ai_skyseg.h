//
//  bef_effect_ai_skyseg.h
//  effect-sdk
//
//  Created by qun on 2020/10/21.
//

#ifndef bef_effect_ai_skyseg_h
#define bef_effect_ai_skyseg_h

#include "bef_effect_ai_public_define.h"

#if defined(__ANDROID__) || defined(TARGET_OS_ANDROID)
#include<jni.h>
#endif

typedef unsigned long long bef_ai_skyseg_handle;

/**
 * @brief 创建句柄
 * @param [out] handle    Created skyseg handle
 * @return If succeed return BEF_RESULT_SUC, other value please see bef_effect_ai_public_define.h
 *         成功返回 BEF_RESULT_SUC, 失败返回相应错误码, 具体请参考 bef_effect_ai_public_define.h
 */
BEF_SDK_API bef_effect_result_t
bef_effect_ai_skyseg_create_handle(bef_ai_skyseg_handle* handle);

/*
 * @brief 从文件初始化模型参数
 **/

BEF_SDK_API bef_effect_result_t
bef_effect_ai_skyseg_init_model(bef_ai_skyseg_handle handle,
                                const char* modelPath);

/*
 * @brief 设置SDK参数
 * net_input_width 和 net_input_height
 * 表示神经网络的传入，一般情况下不同模型不太一样
 * 此处（HairParser）传入值约定为 net_input_width = 128, net_input_height = 224
 **/
BEF_SDK_API bef_effect_result_t
bef_effect_ai_skyseg_set_param(bef_ai_skyseg_handle handle,
                                int width,
                                int height);

/*
 * * @brief 获取输出mask shape
* output_width, output_height, channel 用于得到 bef_effect_ai_skyseg_detect 接口输出的
* alpha 大小 如果在 bef_effect_ai_skyseg_set_param 的参数中，net_input_width，net_input_height
* 已按约定传入，即 net_input_width = 128, net_input_height = 224
* channel 始终返回 1
 */
BEF_SDK_API bef_effect_result_t
bef_effect_ai_skyseg_get_output_shape(bef_ai_skyseg_handle handle,
                                      int *output_width,
                                      int *output_height,
                                      int *channel);

/*
 * @brief 进行抠图操作
 * @note  注意dst_alpha_data 空间需要外部分配
 * image 为传入图片的大小，图片大小任意
 * pixel_format， image_width, image_height, image_stride 为传入图片的信息
 **/
BEF_SDK_API bef_effect_result_t
bef_effect_ai_skyseg_detect(bef_ai_skyseg_handle handle,
                                     const unsigned char* image,
                                     bef_ai_pixel_format pixel_format,
                                     int image_width,
                                     int image_height,
                                     int image_stride,
                                     bef_ai_rotate_type orientation,
                                     unsigned char *dst_alpha_data,
                                     bool need_flip_alpha,
                                     bool need_sky_check,
                            bool *has_sky);

/*
 * @brief 释放句柄
 **/
BEF_SDK_API bef_effect_result_t bef_effect_ai_skyseg_destroy(bef_ai_skyseg_handle handle);

/**
 * @brief 天空分割授权
 * @param [in] handle Created skyseg  handle
 * @param [in] license 授权文件字符串
 * @return If succeed return BEF_RESULT_SUC, other value please refer bef_effect_ai_public_define.h
 *         成功返回 BEF_RESULT_SUC, 授权码非法返回 BEF_RESULT_INVALID_LICENSE ，其它失败返回相应错误码, 具体请参考 bef_effect_ai_public_define.h
 */
BEF_SDK_API bef_effect_result_t bef_effect_ai_skyseg_check_license(bef_ai_skyseg_handle handle, const char* licensePath);

BEF_SDK_API bef_effect_result_t
bef_effect_ai_skyseg_check_online_license(bef_ai_skyseg_handle handle, const char* licensePath);

#endif /* bef_effect_ai_skyseg_h */
