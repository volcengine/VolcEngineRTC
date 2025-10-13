#ifndef BEF_EFFECT_AI_AVABOOST_H
#define BEF_EFFECT_AI_AVABOOST_H

#include "bef_effect_ai_public_define.h"

#if defined(__ANDROID__) || defined(TARGET_OS_ANDROID)
#include<jni.h>
#endif

/**
 * @brief 输出结果
 */
typedef struct
{
    float pose[16];    // 面部 4x4 姿态矩阵
    float beta[52];    // 52 维表情系数
} bef_ai_avaboost_ret;

/**
 * @brief 模型参数类型
 */
typedef enum {
    BEF_AI_AVABOOST_USE_POSE = 0,       // 是否输出人脸姿态，可选为0或1。默认为1，输出。注意，对于某些情况为了节省模型体积，可以针对业务定制不含姿态的模型，对于这种模型，如果该参数设置为1，则会报错。int
    BEF_AI_AVABOOST_CALIBRATION = 1,    // 是否进行自动标定，可选为0或1，默认为1。为了缓解误激活（如不应张嘴时张嘴），算法进行过程中，会动态地寻找最接近于无表情的帧，并将该帧除了 eyeLook 与 舌头 相关表情外的其他表情视为误激活，并加以抵消。int
    BEF_AI_AVABOOST_MESH_SCALE = 2,     // 在输出姿态上叠加的资产缩放，默认为1.0。一般我们希望我们的素材大小接近于标准大小（附上标准 obj），但是对于某些已上线的资产，我们无法调整，不得以加入此参数。如果你的资产坐标非常大，则应该将该字段设为一个很小的值。如果 ava_boost_use_pose 为 0，则该字段无效。 float
    BEF_AI_AVABOOST_FOV = 3,            // 设备视场角，角度制，默认为 65.5。该值主要影响输出的人脸姿态，如果 ava_boost_use_pose 为 0，则该字段无效。float
    BEF_AI_AVABOOST_EXTRA_PITCH = 4,    // 在输出姿态上叠加的俯仰角，默认为0.0。 一般我们希望我们的素材俯仰角接近标准角度（同上），但是对于不符合的资产，可以通过一个额外的角来对齐调整，该值为弧度值。如果 ava_boost_use_pose 为 0，则该字段无效。float
    BEF_AI_AVABOOST_CALIB_THRESH = 5,   // 自动标定时判定无表情帧的阈值，默认为6.0。即除了 eyeLook 与 舌头 相关的表情激活值之和需要小于一个阈值才会被选定为无表情帧。如果 ava_boost_calibration 设置为 0，该字段无效。float
    BEF_AI_AVABOOST_SMOOTH_WO_TONGUE = 6,// 除了舌头之外的所有表情的平滑系数，默认值为 -10。令该帧的输出与上一帧的差值的绝对值为 diff，平滑系数为 s，则 alpha = exp(s * diff)。上一帧的权重为 alpha，当前帧为 1 - alpha。float
    BEF_AI_AVABOOST_SMOOTH_TONGUE = 7,  // 舌头的表情平滑系数，默认为 -4。解释同上。float
    BEF_AI_AVABOOST_TONGUE_CLIP_THRESH = 8, // 由于舌头输出数值的特殊性，该系数低于一定阈值时会被裁减，剩下有激活的部分会使用 sigmoid 曲线从 0 平滑过渡至 1. 该字段即为提及的阈值，默认为 0.4。float
    BEF_AI_AVABOOST_TONGUE_SIGMOID_WIDTH = 9,// 解释同上，该字段为从标准 sigmoid 曲线过渡的宽度，默认为 10.0。该值越大，意味着过渡越陡峭。float
    BEF_AI_AVABOOST_POSE_MODE = 10,     // 人脸姿态的形式，可选为"mv"或"mvp"，两者都为 4x4矩阵，前者不含投影矩阵，默认为"mvp"。如果 ava_boost_use_pose 为 0，则该字段无效。string
    BEF_AI_AVABOOST_WARP_AFFINE_MODE = 11,// 输入图像预处理时的裁剪方法，可选为“warpAffine”或“tt_warpAffine”。前者效果更好，后者速度更快，默认为前者。string
    BEF_AI_AVABOOST_MODEL_NAME = 12,    // 模型名字, string
    BEF_AI_AVABOOST_EXP_ORDER = 13,     // 输出表情系数的顺序。可选为“avacap”或“origin”，为与 avacap 保持一致，默认为 avacap。但推荐使用新版，因此推荐始终明确填写"origin". 两种顺序见文档末尾。string
} bef_ai_avaboost_param_type;

bef_effect_result_t AvaBoost_ReleaseHandle(bef_effect_handle_t handle);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_avaboost_create(bef_effect_handle_t *handle);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_avaboost_init(bef_effect_handle_t handle, const char *modelPath);


BEF_SDK_API
bef_effect_result_t bef_effect_ai_avaboost_detect(
                  bef_effect_handle_t handle,
                  const unsigned char *image,
                  bef_ai_pixel_format pixel_format,
                  int image_width,
                  int image_height,
                  int image_stride,
                  bef_ai_rotate_type orientation,
                  bef_ai_avaboost_ret* result
);


BEF_SDK_API
bef_effect_result_t bef_effect_ai_avaboost_set_paramI(bef_effect_handle_t handle, bef_ai_avaboost_param_type type, int value);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_avaboost_set_paramF(bef_effect_handle_t handle, bef_ai_avaboost_param_type type, float value);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_avaboost_set_paramS(bef_effect_handle_t handle, bef_ai_avaboost_param_type type, const char* value);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_avaboost_release(bef_effect_handle_t handle);

/**
 * @brief avaboost授权
 * @param [in] handle Created avaboost handle
 *                    已创建的avaboost句柄
 * @param [in] license 授权文件字符串
 * @param [in] length  授权文件字符串长度
 * @return If succeed return BEF_RESULT_SUC, other value please refer bef_effect_ai_public_define.h
 *         成功返回 BEF_RESULT_SUC, 授权码非法返回 BEF_RESULT_INVALID_LICENSE ，其它失败返回相应错误码, 具体请参考 bef_effect_ai_public_define.h
 */
BEF_SDK_API
bef_effect_result_t bef_effect_ai_avaboost_check_license(bef_effect_handle_t handle, const char *licensePath);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_avaboost_check_online_license(bef_effect_handle_t handle, const char *licensePath);

#endif // BEF_EFFECT_AI_AVABOOST_H
