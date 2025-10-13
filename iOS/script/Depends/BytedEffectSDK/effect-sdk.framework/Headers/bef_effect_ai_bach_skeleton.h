
#ifndef BEF_EFFECT_AI_BACH_SKELETON_H
#define BEF_EFFECT_AI_BACH_SKELETON_H

#include "bef_effect_ai_public_define.h"

#if defined(__ANDROID__) || defined(TARGET_OS_ANDROID)
#include<jni.h>
#endif

#define BEF_AI_MAX_BACH_SKELETON_POINT_NUM 63
#define BEF_AI_MAX_BACH_SKELETON_NUM  2

typedef struct bef_ai_bach_skeleton_point_info_st {
    float x; // 对应 cols, 范围在 [0, width] 之间
    float y; // 对应 rows, 范围在 [0, height] 之间
    bool is_detect; // 如果该值为 0, 则 x,y 无意义
    float score; // 对应点的分数
} bef_ai_bach_skeleton_point_info;

typedef struct bef_ai_bach_skeleton_info_st {
    int id;
    int orientation;
    bef_ai_bach_skeleton_point_info keyPointInfos[BEF_AI_MAX_BACH_SKELETON_POINT_NUM];     // 检测到的骨骼信息
    bef_ai_rect  skeletonRect; // 骨骼rect
} bef_ai_bach_skeleton_info;

/**
 * @brief 模型参数类型
 *
 */
typedef enum {
    BEF_AI_BACH_SKELETON_BODY_MAX_COUNT = 0,     // 最大可检测的人体数量（最多为5）, int。
    BEF_AI_BACH_SKELETON_FORCE_DETECT = 1,       // 设置跟踪模式，int。
                                                 //    0: 非强制检测（跟踪模式，默认值）
                                                 //    1: 强制每帧检测
    BEF_AI_BACH_SKELETON_IMAGE_MODE = 2,         // 设置检测模式
                                                 //    0: 视频模式（检测+跟踪，默认值）
                                                 //    1：图片模式（无跟踪）
} bef_ai_bach_skeleton_param_type;

bef_effect_result_t BachSkeleton_ReleaseHandle(bef_effect_handle_t handle);

/**
 * @brief 创建骨骼的句柄
 * @param [in] model_path 模型文件路径
 * @param [out] handle    Created skeleton handle
 *                        创建的骨骼句柄
 * @return If succeed return BEF_RESULT_SUC, other value please see bef_effect_ai_public_define.h
 *         成功返回 BEF_RESULT_SUC, 失败返回相应错误码, 具体请参考 bef_effect_ai_public_define.h
 */
BEF_SDK_API bef_effect_result_t
bef_effect_ai_bach_skeleton_create(bef_effect_handle_t *handle);

BEF_SDK_API
bef_effect_result_t bef_effect_ai_bach_skeleton_init(bef_effect_handle_t handle, const char *modelPath);


/**
 * @brief 人体关键点检测
 * @param [in] handle Created skeleton handle
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
 * @param [in, out] skeleton_info_num 不可为 NULL， 如果传入*skeleton_info为NULL，传入数据无意义，会返回检测的骨骼数量
 *                                如果*skeleton_info不为NULL，表示skeleton_info的长度，
 *                                如果 skeleton_info_num 大于 *skeleton_info长度，则 返回*skeleton_info长度
 * @param [in, out] bach_skeleton_info skeleton_info不可为nullptr,如果传入*skeleton_info为NULL，则内部会分配内存，需要调用者使用delete[] (*skeleton_info)释放
 *                                如果*skeleton_info不为NULL，则长度为*skeleton_info_num，
 *                                会根据检测结果最多填充*skeleton_info_num个骨骼数据
 * @return If succeed return BEF_RESULT_SUC, other value please see bef_effect_ai_public_define.h
 *         成功返回 BEF_RESULT_SUC, 失败返回相应错误码, 具体请参考 bef_effect_ai_public_define.h
 */
BEF_SDK_API bef_effect_result_t
bef_effect_ai_bach_skeleton_detect(
        bef_effect_handle_t handle,
        const unsigned char *image,
        bef_ai_pixel_format pixel_format,
        int image_width,
        int image_height,
        int image_stride,
        bef_ai_rotate_type orientation,
        int *skeleton_bach_info_num,
        bef_ai_bach_skeleton_info **bach_skeleton_info
);

/**
 * @brief 检测骨骼个数， 最大数设置为 BEF_MAX_SKELETON_NUM 为 2
 * @param [in] handle Created skeleton handle
 *                      已创建的骨骼句柄
 * @param [in] max_skeleton_num 设置检测最大g骨骼数 range in [1, 2]
 * @return If succeed return BEF_RESULT_SUC, other value please refer bef_effect_ai_public_define.h
 *         成功返回 BEF_RESULT_SUC, 失败返回相应错误码, 具体请参考 bef_effect_ai_public_define.h
 */
BEF_SDK_API
bef_effect_result_t bef_effect_ai_bach_skeleton_set_paramI(bef_effect_handle_t handle, bef_ai_bach_skeleton_param_type type, int value);


/**
 * @param [in] handle Destroy the created skeleton handle
 *                    销毁创建的骨骼句柄
 */
BEF_SDK_API
bef_effect_result_t bef_effect_ai_bach_skeleton_release(bef_effect_handle_t handle);


/**
 * @brief 人体关键点授权
 * @param [in] handle Created skeleton detect handle
 *                    已创建的骨骼检测句柄
 * @param [in] license 授权文件字符串
 * @param [in] length  授权文件字符串长度
 * @return If succeed return BEF_RESULT_SUC, other value please refer bef_effect_ai_public_define.h
 *         成功返回 BEF_RESULT_SUC, 授权码非法返回 BEF_RESULT_INVALID_LICENSE ，其它失败返回相应错误码, 具体请参考 bef_effect_ai_public_define.h
 */
BEF_SDK_API
bef_effect_result_t bef_effect_ai_bach_skeleton_check_license(bef_effect_handle_t handle, const char *licensePath);


BEF_SDK_API
bef_effect_result_t bef_effect_ai_bach_skeleton_check_online_license(bef_effect_handle_t handle, const char *licensePath);
#endif // BEF_EFFECT_AI_BACH_SKELETON_H

