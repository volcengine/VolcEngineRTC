
#ifndef BEF_EFFECT_AI_SKELETON_H
#define BEF_EFFECT_AI_SKELETON_H

#include "bef_effect_ai_public_define.h"

#if defined(__ANDROID__) || defined(TARGET_OS_ANDROID)
#include<jni.h>
#endif

#define BEF_AI_MAX_SKELETON_POINT_NUM 18
#define BEF_AI_MAX_SKELETON_NUM  2


typedef struct bef_ai_skeleton_point_info_st {
    float x; // 对应 cols, 范围在 [0, width] 之间
    float y; // 对应 rows, 范围在 [0, height] 之间
    bool is_detect; // 如果该值为 0, 则 x,y 无意义
    float score;
} bef_ai_skeleton_point_info;

typedef struct bef_ai_skeleton_info_st {
    bef_ai_skeleton_point_info      keyPointInfos[BEF_AI_MAX_SKELETON_POINT_NUM];     // 检测到的骨骼信息
    bef_ai_rect  skeletonRect; // 骨骼rect
} bef_ai_skeleton_info;

typedef struct bef_ai_skeleton_result_st {
    bef_ai_rotate_type orient;
    int body_count;
    bef_ai_skeleton_info body[BEF_AI_MAX_SKELETON_NUM];
} bef_ai_skeleton_result;

/**
 * @brief 创建骨骼的句柄
 * @param [in] model_path 模型文件路径
 * @param [out] handle    Created skeleton handle
 *                        创建的骨骼句柄
 * @return If succeed return BEF_RESULT_SUC, other value please see bef_effect_ai_public_define.h
 *         成功返回 BEF_RESULT_SUC, 失败返回相应错误码, 具体请参考 bef_effect_ai_public_define.h
 */
BEF_SDK_API bef_effect_result_t
bef_effect_ai_skeleton_create(
                             const char *model_path,
                             bef_effect_handle_t *handle
                             );

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
 * @param [in, out] skeleton_info skeleton_info不可为nullptr,如果传入*skeleton_info为NULL，则内部会分配内存，需要调用者使用delete[] (*skeleton_info)释放
 *                                如果*skeleton_info不为NULL，则长度为*skeleton_info_num，
 *                                会根据检测结果最多填充*skeleton_info_num个骨骼数据
 * @return If succeed return BEF_RESULT_SUC, other value please see bef_effect_ai_public_define.h
 *         成功返回 BEF_RESULT_SUC, 失败返回相应错误码, 具体请参考 bef_effect_ai_public_define.h
 */
BEF_SDK_API bef_effect_result_t
bef_effect_ai_skeleton_detect(
                             bef_effect_handle_t handle,
                             const unsigned char *image,
                             bef_ai_pixel_format pixel_format,
                             int image_width,
                             int image_height,
                             int image_stride,
                             bef_ai_rotate_type orientation,
                             int *skeleton_info_num,
                             bef_ai_skeleton_info **skeleton_info
                             );

/**
 * @brief 人体关键点检测图片模式
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
 * @param [in, out] skeleton_info skeleton_info不可为nullptr,如果传入*skeleton_info为NULL，则内部会分配内存，需要调用者使用delete[] (*skeleton_info)释放
 *                                如果*skeleton_info不为NULL，则长度为*skeleton_info_num，
 *                                会根据检测结果最多填充*skeleton_info_num个骨骼数据
 * @return If succeed return BEF_RESULT_SUC, other value please see bef_effect_ai_public_define.h
 *         成功返回 BEF_RESULT_SUC, 失败返回相应错误码, 具体请参考 bef_effect_ai_public_define.h
 *
 */
BEF_SDK_API bef_effect_result_t bef_effect_ai_skeleton_detect_image_mode(
        bef_effect_handle_t handle,
        const unsigned char *image,
        bef_ai_pixel_format pixel_format,
        int image_width,
        int image_height,
        int image_stride,
        bef_ai_rotate_type orientation,
        int *skeleton_info_num,
        bef_ai_skeleton_info **skeleton_info
);

/**
 * @brief set detection inputSize 设置检测算法的输入尺寸
 * 如果不设置，默认width = 128 height = 224
 * @param [in] handle Created skeleton handle
 *                      已创建的骨骼句柄
 * @param [in] width Skeleton detect  width
 *                      宽度
 * @param [in] height Skeleton detect network height
 *                      高度
 * @return If succeed return BEF_RESULT_SUC, other value please refer bef_effect_ai_public_define.h
 *         成功返回 BEF_RESULT_SUC, 失败返回相应错误码, 具体请参考 bef_effect_ai_public_define.h
 */
BEF_SDK_API bef_effect_result_t
bef_effect_ai_skeleton_set_detection_inputsize(
        bef_effect_handle_t handle,
        int width,
        int height
);
/**
 * @brief set tracking inputsize 设置跟踪算法的输入尺寸
 * 如果不设置，默认width = 144 height = 192
 * @param [in] handle Created skeleton handle
 *                      已创建的骨骼句柄
 * @param [in] width Skeleton detect  width
 *                      宽度
 * @param [in] height Skeleton detect network height
 *                      高度
 * @return If succeed return BEF_RESULT_SUC, other value please refer bef_effect_ai_public_define.h
 *         成功返回 BEF_RESULT_SUC, 失败返回相应错误码, 具体请参考 bef_effect_ai_public_define.h
 */
BEF_SDK_API bef_effect_result_t
bef_effect_ai_skeleton_set_tracking_inputsize(
        bef_effect_handle_t handle,
        int width,
        int height
);

/**
 * @brief 检测骨骼个数， 最大数设置为 BEF_MAX_SKELETON_NUM 为 2
 * @param [in] handle Created skeleton handle
 *                      已创建的骨骼句柄
 * @param [in] max_skeleton_num 设置检测最大g骨骼数 range in [1, 2]
 * @return If succeed return BEF_RESULT_SUC, other value please refer bef_effect_ai_public_define.h
 *         成功返回 BEF_RESULT_SUC, 失败返回相应错误码, 具体请参考 bef_effect_ai_public_define.h
 */
BEF_SDK_API bef_effect_result_t
bef_effect_ai_skeleton_set_targetnum(
                                bef_effect_handle_t handle,
                                int max_skeleton_num
                                );


/**
 * @param [in] handle Destroy the created skeleton handle
 *                    销毁创建的骨骼句柄
 */
BEF_SDK_API void
bef_effect_ai_skeleton_destroy(
                              bef_effect_handle_t handle
                              );





/**
 * @brief 人体关键点授权
 * @param [in] handle Created skeleton detect handle
 *                    已创建的骨骼检测句柄
 * @param [in] license 授权文件字符串
 * @param [in] length  授权文件字符串长度
 * @return If succeed return BEF_RESULT_SUC, other value please refer bef_effect_ai_public_define.h
 *         成功返回 BEF_RESULT_SUC, 授权码非法返回 BEF_RESULT_INVALID_LICENSE ，其它失败返回相应错误码, 具体请参考 bef_effect_ai_public_define.h
 */

#if defined(__ANDROID__) || defined(TARGET_OS_ANDROID)
BEF_SDK_API bef_effect_result_t bef_effect_ai_skeleton_check_license(JNIEnv* env, jobject context, bef_effect_handle_t handle, const char *licensePath);
#else
#ifdef __APPLE__
BEF_SDK_API bef_effect_result_t bef_effect_ai_skeleton_check_license(bef_effect_handle_t handle, const char *licensePath);
#endif
#endif

BEF_SDK_API bef_effect_result_t
bef_effect_ai_skeleton_check_online_license(bef_effect_handle_t handle, const char *licensePath);
#endif // BEF_EFFECT_AI_SKELETON_H

