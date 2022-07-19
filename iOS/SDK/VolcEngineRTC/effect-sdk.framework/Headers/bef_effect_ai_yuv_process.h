//// Copyright (C) 2019 Beijing Bytedance Network Technology Co., Ltd.

#ifndef BEF_EFFECT_YUV_PROCESS_H
#define BEF_EFFECT_YUV_PROCESS_H

#include "bef_effect_ai_public_define.h"
/**
 * @param image yuv数据源
 * @param dst 结果输出地址
 * @param pixel_format yuv数据格式
 * 目前支持BEF_AI_PIX_FMT_YUV420P BEF_AI_PIX_FMT_NV12 和BEF_AI_PIX_FMT_NV21
 * @param image_width输入图像宽度
 * @param image_height 输入图像高度
 * @param dst_width 输出图像宽度
 * @param dst_height 输出图像高度
 * @param orientation 输入图像的旋转角度
 * @param is_front 是否需要左右翻转
 */
BEF_SDK_API void cvt_yuv2rgba(
        const unsigned char* image,
        unsigned char* dst,
        bef_ai_pixel_format pixel_format,
        int image_width,
        int image_height,
        int dst_width,
        int dst_height,
        bef_ai_rotate_type orientation,
        bool is_front);

/**
 * @param image rgba数据源
 * @param dst 结果输出地址
 * @param pixel_format 输出yuv数据的格式
 * 目前支持BEF_AI_PIX_FMT_YUV420P BEF_AI_PIX_FMT_NV12 和BEF_AI_PIX_FMT_NV21
 * @param image_width输入图像宽度
 * @param image_height 输入图像高度
 */
BEF_SDK_API void cvt_rgba2yuv(
        const unsigned char *image,
        unsigned char *dst,
        bef_ai_pixel_format dst_pixel_format,
        int image_width,
        int image_height);


unsigned char *cvt_resize(
        const unsigned char *image,
        int image_width,
        int image_height,
        int resize_width,
        int resize_height
        );

BEF_SDK_API void cvt_yuv_resize(
        const unsigned char *image,
        unsigned char *dst,
        bef_ai_pixel_format pixel_format,
        int image_width,
        int image_height,
        int resize_width,
        int resize_height
        );

#endif //BEF_EFFECT_YUV_PROCESS_H
