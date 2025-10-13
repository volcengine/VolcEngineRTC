
#ifndef BEF_EFFECT_AI_PORTRAT_MATTING_H
#define BEF_EFFECT_AI_PORTRAT_MATTING_H

#include "bef_effect_ai_public_define.h"

#if defined(__ANDROID__) || defined(TARGET_OS_ANDROID)
#if BEF_EFFECT_ANDROID_WITH_JNI
#include<jni.h>
#endif
#endif

/*
 * @brief 推荐配置
 **/
//struct bef_ai_recommend_config {
//    int OutputMinSideLen = 128;
//    int FrashEvery = 15;
//    int EdgeMode = 1;
//};
/*
 * @brief SDK参数
 * edge_mode:
 *    算法参数，用来设置边界的模式
 *    - 0: 不加边界
 *    - 1: 加边界
 *    - 2: 加边界, 其中, 2 和 3 策略不太一样，但效果上差别不大，可随意取一个
 * fresh_every:
 *    算法参数，设置调用多少次强制做预测，目前设置 15 即可
 * MP_OutputMinSideLen:
 *    返回短边的长度, 默认值为128, 需要为16的倍数；
 * MP_OutputWidth 不设置，只做GetParam 兼容之前的调用
 * MP_OutputHeight 不设置，只做GetParam 兼容之前的接口；
 **/
typedef enum {
    BEF_MP_EdgeMode = 0,
    BEF_MP_FrashEvery = 1,
    BEF_MP_OutputMinSideLen = 2,
    BEF_MP_OutputWidth = 3,
    BEF_MP_OutputHeight = 4,
}bef_ai_matting_param_type;

/*
 * @brief 模型类型枚举
 **/
typedef enum {
    BEF_MP_LARGE_MODEL = 0,
    BEF_MP_SMALL_MODEL = 1,
}bef_ai_matting_model_type;


/*
 * @brief 返回结构体，alpha 空间需要调用方负责分配内存和释放，保证有效的控场大于等于widht*height
 * @note 根据输入的大小，短边固定到MP_OutputMinSideLen参数指定的大小，长边保持长宽比缩放；
 *       如果输入的image_height > image_width: 则
 *                width = MP_OutputMinSideLen,
 *                height = (int)(1.0*MP_OutputMinSideLen/image_width*image_height);
 *                //如果长度不为16的倍数，则向上取整到16的倍数
 *                   if(height %16 > 0){
 *                      height = 16*(height/16)+16;
 }
 **/
typedef struct {
    unsigned char* alpha;  // alpha[i, j] 表示第 (i, j) 点的 mask 预测值，值位于[0, 255] 之间
    int width;             // alpha 的宽度
    int height;            // alpha 的高度
}bef_ai_matting_ret;

/**
 * @brief 创建骨骼的句柄
 * @param [out] handle    Created portrait_matting handle
 *                        创建的骨骼句柄
 * @return If succeed return BEF_RESULT_SUC, other value please see bef_effect_ai_public_define.h
 *         成功返回 BEF_RESULT_SUC, 失败返回相应错误码, 具体请参考 bef_effect_ai_public_define.h
 */
BEF_SDK_API bef_effect_result_t
bef_effect_ai_portrait_matting_create(
                             bef_effect_handle_t *handle
                             );

/*
 * @brief 从文件初始化模型参数
 **/

BEF_SDK_API bef_effect_result_t
bef_effect_ai_portrait_matting_init_model(
                                      bef_effect_handle_t handle,
                                      bef_ai_matting_model_type type,
                                      const char* param_path);

/*
 * @brief 设置SDK参数
 **/
BEF_SDK_API bef_effect_result_t
bef_effect_ai_portrait_matting_set_param(
                                        bef_effect_handle_t handle,
                                        bef_ai_matting_param_type type,
                                        int value);

/*
 * @brief 获取SDK参数
 **/
BEF_SDK_API bef_effect_result_t
bef_effect_ai_portrait_matting_get_param(
                                         bef_effect_handle_t handle,
                                         bef_ai_matting_param_type type,
                                         int *value);
/**
 *  @brief 获取输出mask的尺寸
 *  @param handle 人体分割句柄
 *  @param width 输入图的宽度
 *  @param height 输入图的高度
 *  @param output_width[out] 输出mask的宽度
 *  @param output_height[out] 输出mask的高度
 *
 */
BEF_SDK_API bef_effect_result_t
bef_effect_ai_portrait_get_output_shape(bef_effect_handle_t handle,
                                        int width,
                                        int height,
                                        int *output_width,
                                        int *output_height);
/*
 * @brief 进行抠图操作
 * @note ret 结构图空间需要外部分配
 **/
BEF_SDK_API bef_effect_result_t
bef_effect_ai_portrait_matting_do_detect(
                                         bef_effect_handle_t handle,
                                         const unsigned char *src_image_data,
                                         bef_ai_pixel_format pixel_format,
                                         int width,
                                         int height,
                                         int image_stride,
                                         bef_ai_rotate_type orient,
                                         bool need_flip_alpha,
                                         bef_ai_matting_ret *ret);


/*
 * @brief 释放句柄
 **/
BEF_SDK_API bef_effect_result_t
bef_effect_ai_portrait_matting_destroy(bef_effect_handle_t handle);


/**
 * @brief 人像分割授权
 * @param [in] handle Created portrait_matting  handle
 *                    已创建的骨骼检测句柄
 * @param [in] license 授权文件字符串
 * @param [in] length  授权文件字符串长度
 * @return If succeed return BEF_RESULT_SUC, other value please refer bef_effect_ai_public_define.h
 *         成功返回 BEF_RESULT_SUC, 授权码非法返回 BEF_RESULT_INVALID_LICENSE ，其它失败返回相应错误码, 具体请参考 bef_effect_ai_public_define.h
 */

#if defined(__ANDROID__) || defined(TARGET_OS_ANDROID)
#if BEF_EFFECT_ANDROID_WITH_JNI
BEF_SDK_API bef_effect_result_t bef_effect_ai_matting_check_license(JNIEnv* env, jobject context, bef_effect_handle_t handle, const char *licensePath);
#else
BEF_SDK_API bef_effect_result_t bef_effect_ai_matting_check_license(bef_effect_handle_t handle, const char *licensePath);
#endif
#else
#ifdef __APPLE__
BEF_SDK_API bef_effect_result_t bef_effect_ai_matting_check_license(bef_effect_handle_t handle, const char *licensePath);
#endif
#endif

BEF_SDK_API bef_effect_result_t
bef_effect_ai_matting_check_online_license(bef_effect_handle_t handle, const char *licensePath);

#endif // BEF_EFFECT_AI_SKELETON_H

