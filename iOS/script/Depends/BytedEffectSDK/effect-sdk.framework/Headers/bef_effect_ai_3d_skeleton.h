#ifndef BEF_EFFECT_AI_3D_SKELETON_H
#define BEF_EFFECT_AI_3D_SKELETON_H

#include "bef_effect_ai_public_define.h"
#if defined(__ANDROID__) || defined(TARGET_OS_ANDROID)
#include<jni.h>
#endif

typedef unsigned  long long bef_ai_3d_skeleton_handle;

#define AI_3D_SKELETON_JOINT_NUM 24 // 身体3D关键点个数
#define AI_3D_SKELETON_SHAPE_COEFF_DIM 10 // 身体shape系数的维数
#define AI_3D_SKELETON_ONE_HAND_JOINT_NUM 21 // 单个手3D关键点个数
#define AI_3D_SKELETON_EXTENDED_JOINT_NUM 64 // 身体+双手3D关键点个数
#define AI_3D_SKELETON_MAX_TARGET_NUM 5 // 所允许的最多目标个数
#define AI_3D_SKELETON_INPUT_KEYPOINT2D_NUM 18 // 输入的2D关键点个数
#define AI_3D_SKELETON_HEATMAP_KEYPOINT_NUM 27

/**
 * @brief 模型参数类型
 *bef_ai_3d_skeleton_WHOLEBODY: 0 upper body;   1 whole body
 */
typedef enum bef_ai_3d_skeleton_param_type {
  bef_ai_3d_skeleton_WHOLEBODY = 0,        ///< TODO: 根据实际情况修改
  bef_ai_3d_skeleton_WITHHANDS = 1,
  bef_ai_3d_skeleton_MAXTARGETNUM = 2,
  bef_ai_3d_skeleton_TARGETSPEFRAME = 3,
  bef_ai_3d_skeleton_WRISTSCORETHRES = 4,
  bef_ai_3d_skeleton_HSWRISTSCORETHRES = 5,
  bef_ai_3d_skeleton_CHECKROOTINVERSE = 6,
  bef_ai_3d_skeleton_TASKPERTICK = 7,
  bef_ai_3d_skeleton_SMOOTHWINSIZE = 8,
  bef_ai_3d_skeleton_SMOOTHORIGINSIGMAXY = 9,
  bef_ai_3d_skeleton_SMOOTHORIGINSIGMAZ = 10,
  bef_ai_3d_skeleton_WITHWRISTOFFSET = 11,
  bef_ai_3d_skeleton_HANDPROBTHRES = 12,
  bef_ai_3d_skeleton_CHECKWRISTROT = 13,
  bef_ai_3d_skeleton_SMOOTHSIGMABETAS = 14,
  bef_ai_3d_skeleton_FITTINGENABLE = 15,
  bef_ai_3d_skeleton_FITTINGROOTENABLE = 16
} bef_ai_3d_skeleton_param_type;


typedef struct bef_ai_skeleton_3d_args{
    const unsigned char *image;
    bef_ai_pixel_format pixel_format;
    int image_width;
    int image_height;
    int image_stride;
    bef_ai_rotate_type rotation;
    float points2d[AI_3D_SKELETON_MAX_TARGET_NUM*AI_3D_SKELETON_INPUT_KEYPOINT2D_NUM*2]; // 2D关键点位置
    int point_valid[AI_3D_SKELETON_MAX_TARGET_NUM*AI_3D_SKELETON_INPUT_KEYPOINT2D_NUM]; // 2D关键点是否有效
    int keypoint_num; // 2D关键点个数
    int target_num; // 目标个数
}bef_ai_skeleton_3d_args;

/**
 * @brief 封装Avatar3D单个目标信息的结构体
 *
 */
typedef struct bef_ai_skeleton3d_target {
  float quaternion[AI_3D_SKELETON_EXTENDED_JOINT_NUM*4]; // 3D关键点四元数
  float betas[10]; // blendshape系数
  float root[3]; // 根3D关键点在相机坐标下的位置
  float joints[AI_3D_SKELETON_EXTENDED_JOINT_NUM*3]; // 3D关键点在相机坐标下的位置
  float scores[AI_3D_SKELETON_EXTENDED_JOINT_NUM]; // 3D关键点的置信度，仅提供（L-shoulder, R-shoulder, L-elbow, R-elbow, L-wrist, R-wrist, L-knee, R-knee, L-ankle, R-ankle）10个3D关键点的置信度，其它点为默认值0
  float joint_valid[AI_3D_SKELETON_EXTENDED_JOINT_NUM]; // 关键点是否有效, whole_body下全为1, 非whole_body下半身3D关键点为0
  float heatmap_kpts_2d[AI_3D_SKELETON_HEATMAP_KEYPOINT_NUM*2];
  float box[4]; // 输入网络的人体框
  int joint_num; // 3D关键点个数
  int tracking_id; // 目标id
  int new_target; // 是否是新目标
}bef_ai_skeleton3d_target;

/**
 * @brief 封装预测接口的返回值
 *
 * @note 不同的算法，可以在这里添加自己的自定义数据
 */
typedef struct bef_ai_skeleton3d_ret {
    bef_ai_skeleton3d_target targets[AI_3D_SKELETON_MAX_TARGET_NUM]; // 目标列表
    int target_num; // 目标个数
    float focal_length; // 摄像机焦距
    int tracking; // 下一帧是tracking模式还是detect模式，detect模式下需要输入人体2D关键点坐标得到人体bbox，tracking模式下通过前一帧的3D关键点结果计算人体bbox
}bef_ai_skeleton3d_ret;


/**
 * @brief 创建3d骨骼的句柄
 * @param [in] model_path 模型文件路径
 * @param [out] handle    Created skeleton handle
 *                        创建的3d骨骼句柄
 * @return If succeed return BEF_RESULT_SUC, other value please see bef_effect_ai_public_define.h
 *         成功返回 BEF_RESULT_SUC, 失败返回相应错误码, 具体请参考 bef_effect_ai_public_define.h
 */
BEF_SDK_API bef_effect_result_t
bef_effect_ai_3d_skeleton_create(bef_ai_3d_skeleton_handle *handle);


BEF_SDK_API bef_effect_result_t
bef_effect_ai_3d_skeleton_load_model(bef_ai_3d_skeleton_handle handle, const char* modelPath);

BEF_SDK_API bef_effect_result_t
bef_effect_ai_3d_skeleton_set_param(bef_ai_3d_skeleton_handle handle, bef_ai_3d_skeleton_param_type type, float value);


BEF_SDK_API bef_effect_result_t
bef_effect_ai_3d_skeleton_detect(bef_ai_3d_skeleton_handle handle, bef_ai_skeleton_3d_args* args, bef_ai_skeleton3d_ret* ret);



BEF_SDK_API void
bef_effect_ai_3d_skeleton_release(bef_ai_3d_skeleton_handle handle);


/**
 * @brief 3d人体关键点授权
 * @param [in] handle Created skeleton detect handle
 *                    已创建的骨骼检测句柄
 * @param [in] license 授权文件字符串
 * @param [in] length  授权文件字符串长度
 * @return If succeed return BEF_RESULT_SUC, other value please refer bef_effect_ai_public_define.h
 *         成功返回 BEF_RESULT_SUC, 授权码非法返回 BEF_RESULT_INVALID_LICENSE ，其它失败返回相应错误码, 具体请参考 bef_effect_ai_public_define.h
 */

#if defined(__ANDROID__) || defined(TARGET_OS_ANDROID)
BEF_SDK_API bef_effect_result_t bef_effect_ai_3d_skeleton_check_license(JNIEnv* env, jobject context, bef_ai_3d_skeleton_handle handle, const char *licensePath);
#else
#ifdef __APPLE__
BEF_SDK_API bef_effect_result_t bef_effect_ai_3d_skeleton_check_license(bef_ai_3d_skeleton_handle handle, const char *licensePath);
#endif
#endif

BEF_SDK_API bef_effect_result_t
bef_effect_ai_3d_skeleton_check_online_license(bef_ai_3d_skeleton_handle handle, const char *licensePath);

#endif
