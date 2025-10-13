
#ifndef ANDROIDDEMO_BEF_EFFECT_AI_CHROMA_KEYING_H
#define ANDROIDDEMO_BEF_EFFECT_AI_CHROMA_KEYING_H

#if defined(__ANDROID__) || defined(TARGET_OS_ANDROID)
#include <jni.h>
#endif

#include "bef_effect_ai_public_define.h"

/**
 * @brief 输出结果
 *
 */
typedef struct
{
    int width;
    int height;
    unsigned char color_b;
    unsigned char color_g;
    unsigned char color_r;
    uint8_t* mask;
    int outputTexture;
    int chromaKeyTexture;
} bef_ai_chroma_keying_ret;

/**
 * @brief 参数枚举
 *
 */
typedef enum {
    BEF_AI_CHROMA_KEYING_METHOD = 0,    // 算法key, int。
                                        // 可选值有：0: 移动端实时方案【推荐默认】
                                        //         1: 服务端方案
    BEF_AI_CHROMA_KEYING_CAL_COLOR = 1, // 算法背景色计算key, int。
                                        // 可选值有：0：全图自动主色提取
                                        //         1： 绿幕场景精细化主色提取【默认】
                                        //         ∂2：人工设置主色提取（说明：该选项下返回变量的背景色彩为人工设置色彩）
    BEF_AI_CHROMA_KEYING_BG_R = 2,      // 背景色设置，红色，0～255【默认0】, int。
    BEF_AI_CHROMA_KEYING_BG_G = 3,      // 背景色设置，绿色，0～255【默认255】, int。
    BEF_AI_CHROMA_KEYING_BG_B = 4,      // 背景色设置，蓝色，0～255【默认0】, int。
    BEF_AI_CHROMA_KEYING_BALP = 5,      // 强度调节，float。
                                        // 色彩范围参数 case1: 小于0，自动模式，chroma_keying_cal_color为“1”时候推荐，如【默认-1】
                                        //            case2: 0～1，手动模式，chroma_keying_cal_color为“2”时候推荐设置为0.6～0.7
    BEF_AI_CHROMA_KEYING_KALP = 6,      // 强度调节：锐利度参数【推荐0.15】，建议不调节，float。
    BEF_AI_CHROMA_KEYING_SMOOTH = 7,    // 平滑系数，float。
                                        // case1:小于0时无平滑
                                        // case2:0 仅启用mask时序平滑，估色无时序平滑【推荐0】
                                        // case3:0～1 启用mask时序平滑，参数描述背景色估计平滑下强度（算法内部限制最大为1）
    BEF_AI_CHROMA_KEYING_SHARPEN = 8,   // mask边界锐化key，int。
                                        // 可选有： <=0: 不启用边界锐化
                                        //         >=1: 启用边界锐化【推荐设置为1】
    BEF_AI_CHROMA_KEYING_GET_MASK = 9,  // mask计算并返回，int。
                                        // 可选有：<=0: 不返回mask（仅获得背景色彩估计）
                                        //        >=1: 计算mask，同时获得背景色估计和背景色估值【默认请设1】
} bef_ai_chroma_keying_param_type;

bef_effect_result_t ChromaKeying_ReleaseHandle(bef_effect_handle_t handle);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_chroma_keying_create(bef_effect_handle_t *handle);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_chroma_keying_init(bef_effect_handle_t handle, const char *modelPath);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_chroma_keying_detect(bef_effect_handle_t handle,
                                                           const unsigned char *image,
                                                           bef_ai_pixel_format pixel_format,
                                                           int image_width,
                                                           int image_height,
                                                           int image_stride,
                                                           bef_ai_rotate_type orientation,
                                                           bef_ai_chroma_keying_ret *result,
                                                           bool soft_process);

/**
 * @brief 设置处理参数
 *
 * @param similar 相似度（最主要影响抠图强度
 * @param smooth 平滑度（搭配similar的，影响半透明等过渡状态
 * @param correction 去绿强度
 * @param clip_black/clip_white 对最后结果mask做个黑白截断的曲线增强
 */
BEF_SDK_API
void bef_effect_ai_chroma_keying_set_processParam(float similar, float smoothness, float correction, float clip_black, float clip_white);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_chroma_keying_set_paramF(bef_effect_handle_t handle, bef_ai_chroma_keying_param_type type, float value);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_chroma_keying_set_paramI(bef_effect_handle_t handle, bef_ai_chroma_keying_param_type type, int value);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_chroma_keying_release(bef_effect_handle_t handle);

/**
 * @brief 绿幕抠图授权
 * @param [in] handle Created skeleton detect handle
 *                    已创建的绿幕抠图句柄
 * @param [in] license 授权文件字符串
 * @param [in] length  授权文件字符串长度
 * @return If succeed return BEF_RESULT_SUC, other value please refer bef_effect_ai_public_define.h
 *         成功返回 BEF_RESULT_SUC, 授权码非法返回 BEF_RESULT_INVALID_LICENSE ，其它失败返回相应错误码, 具体请参考 bef_effect_ai_public_define.h
 */

BEF_SDK_API
bef_effect_result_t bef_effect_ai_chroma_keying_check_license(bef_effect_handle_t handle, const char *licensePath);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_chroma_keying_check_online_license(bef_effect_handle_t handle, const char *licensePath);

#endif //ANDROIDDEMO_BEF_EFFECT_AI_SKIN_SEGMENTATION_H
