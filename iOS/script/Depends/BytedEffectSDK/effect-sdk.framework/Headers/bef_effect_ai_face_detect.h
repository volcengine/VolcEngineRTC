
#ifndef _BEF_EFFECT_FACE_DETECT_AI_H_
#define _BEF_EFFECT_FACE_DETECT_AI_H_

#if defined(__ANDROID__) || defined(TARGET_OS_ANDROID)
#if BEF_EFFECT_ANDROID_WITH_JNI
#include<jni.h>
#endif
#endif

#include "bef_effect_ai_public_define.h"


//***************************** begin Create-Config *****************/
// Config when creating handle
#define BEF_DETECT_LARGE_MODEL 0x00100000  // 106模型初始化参数，更准, 现已废弃
#define BEF_DETECT_SMALL_MODEL 0x00200000  // 106模型初始化参数，更快
#define BEF_DETECT_FACE_240_DETECT_FASTMODE \
0x00300000  // 240模型初始化参数，更快
//**************************** end of Create-Config *****************/

//***************************** begin Mode-Config ******************/
#define BEF_DETECT_MODE_VIDEO_SLOW 0x00010000  // 视频检测，能检测更小的人脸,初始化+预测参数
#define BEF_DETECT_MODE_VIDEO 0x00020000  // 视频检测，初始化+预测参数
#define BEF_DETECT_MODE_IMAGE 0x00040000  // 图片检测，初始化+预测参数
#define BEF_DETECT_MODE_IMAGE_SLOW \
0x00080000  // 图片检测，人脸检测模型效果更好，能检测更小的人脸，初始化+预测参数
//***************************** enf of Mode-Config *****************/

//***************************** Begin Config-106 point and action **/
// for 106 key points detect
// NOTE 当前版本 张嘴、摇头、点头、挑眉默认都开启，设置相关的位不生效
#define BEF_FACE_DETECT 0x00000001  // 检测106点
// 人脸动作
#define BEF_EYE_BLINK 0x00000002   // 眨眼
#define BEF_MOUTH_AH 0x00000004    // 张嘴
#define BEF_HEAD_YAW 0x00000008    // 摇头
#define BEF_HEAD_PITCH 0x00000010  // 点头
#define BEF_BROW_JUMP 0x00000020   // 挑眉
#define BEF_MOUTH_POUT 0x00000040  // 嘟嘴

#define BEF_DETECT_FULL 0x0000007F  // 检测上面所有的特征，初始化+预测参数

#define BEF_EYE_BLINK_LEFT \
0x00000080  // 左眼闭眼，只用于提取对应的action，动作检测依然是眨眼
#define BEF_EYE_BLINK_RIGHT \
0x00000100  // 右眼闭眼，只用于提取对应的action，动作检测依然是眨眼
#define BEF_INDIAN_HEAD_ROLL \
0x00000200  // 印度式摇头，只用于提取对应的action，动作检测依然是摇头

//**************************** End Config-106 point and action *******/

//******************************* Begin Config-280 point *************/
// for 280 points
// NOTE: 现在改了二级策略，眉毛、眼睛、嘴巴关键点会在一个模型中出
#define TT_MOBILE_FACE_240_DETECT \
0x00000100  // 检测二级关键点: 眉毛, 眼睛, 嘴巴，初始化+预测参数
#define AI_BROW_EXTRA_DETECT TT_MOBILE_FACE_240_DETECT   // 眉毛 13*2个点
#define AI_EYE_EXTRA_DETECT TT_MOBILE_FACE_240_DETECT    // 眼睛 22*2个点
#define AI_MOUTH_EXTRA_DETECT TT_MOBILE_FACE_240_DETECT  // 嘴巴 64个点
#define AI_MOUTH_MASK_DETECT 0x00000300   // 嘴巴 mask
#define AI_TEETH_MASK_DETECT 0x00000300   // 牙齿 mask
#define AI_FACE_MASK_DETECT 0x00000500     // 人脸 mask
#define AI_IRIS_EXTRA_DETECT 0x00000800   // 虹膜 20*2个点

#define TT_MOBILE_FACE_280_DETECT \
0x00000900  // 检测二级关键点: 眉毛, 眼睛, 嘴巴，虹膜，初始化+预测参数
//******************************* End Config-280 point ***************/

#define TT_MOBILE_FORCE_DETECT 0x00001000  // 强制这帧人脸检测，并显示结果

//bef_effect_public_face_define
#define BEF_MAX_FACE_NUM  10

// 眼睛,眉毛,嘴唇详细检测结果, 280点结果
typedef struct bef_ai_face_ext_info_t {
    int eye_count;                  // 检测到眼睛数量
    int eyebrow_count;              // 检测到眉毛数量
    int lips_count;                 // 检测到嘴唇数量
    int iris_count;                 // 检测到虹膜数量
    
    bef_ai_fpoint eye_left[22];        // 左眼关键点
    bef_ai_fpoint eye_right[22];       // 右眼关键点
    bef_ai_fpoint eyebrow_left[13];    // 左眉毛关键点
    bef_ai_fpoint eyebrow_right[13];   // 右眉毛关键点
    bef_ai_fpoint lips[64];            // 嘴唇关键点
    bef_ai_fpoint left_iris[20];       // 左虹膜关键点
    bef_ai_fpoint right_iris[20];      // 右虹膜关键点
} bef_ai_face_ext_info;




// 供106点使用
typedef struct bef_ai_face_106_st {
    bef_ai_rect rect;                // 代表面部的矩形区域
    float score;                  // 置信度
    bef_ai_fpoint points_array[106]; // 人脸106关键点的数组
    float visibility_array[106];  // 对应点的能见度，点未被遮挡1.0, 被遮挡0.0
    float yaw;                    // 水平转角,真实度量的左负右正
    float pitch;                  // 俯仰角,真实度量的上负下正
    float roll;                   // 旋转角,真实度量的左负右正
    float eye_dist;               // 两眼间距
    int ID;                       // faceID: 每个检测到的人脸拥有唯一的faceID.人脸跟踪丢失以后重新被检测到,会有一个新的faceID
    unsigned int action;          // 动作, 定义在 bef_ai_effect_face_detect.h 里
    unsigned int tracking_cnt;
} bef_ai_face_106, *p_bef_ai_face_106;


// @brief 检测结果
typedef struct bef_ai_face_info_st {
    bef_ai_face_106 base_infos[BEF_MAX_FACE_NUM];          // 检测到的人脸信息
    bef_ai_face_ext_info extra_infos[BEF_MAX_FACE_NUM];    // 眼睛，眉毛，嘴唇关键点等额外的信息
    int face_count;                                     // 检测到的人脸数目
} bef_ai_face_info, *p_bef_ai_face_info;

// brief 算法格外参数设置
typedef struct bef_ai_face_image_st {
    bef_ai_face_106 base_info;         // 检测到的人脸信息
    bef_ai_face_ext_info extra_info;   // 眼睛，眉毛，嘴唇关键点等额外的信息
    unsigned int texture_id;          // 基于人脸位置的截图（已补充额头部分、已旋正）
    bef_ai_pixel_format pixel_format;  // 截图格式，目前均为RGBA
    int image_width;                // 截图像素宽度
    int image_height;               // 截图像素高度
    int image_stride;               // 截图行跨度
} bef_ai_face_image_st, *p_bef_ai_face_image_st;


#define BEF_MOUTH_MASK_WIDTH 256
#define BEF_FACE_MASK_WIDTH BEF_MOUTH_MASK_WIDTH
#define BEF_TEETH_MASK_WIDTH BEF_MOUTH_MASK_WIDTH
typedef struct bef_ai_face_mask_base{
    int mask_size;        // mask_size
    unsigned char mask[BEF_MOUTH_MASK_WIDTH * BEF_MOUTH_MASK_WIDTH];  // mask data
    float warp_mat[6];          // warp mat data ptr, size 2*3
    int id;
}bef_ai_face_mask_base,  *p_bef_ai_face_mask_base;

// brief 唇部mask
typedef struct bef_ai_mouth_mask_info{
    bef_ai_face_mask_base mouth_mask[BEF_MAX_FACE_NUM];
    int face_count;
}bef_ai_mouth_mask_info,  *p_bef_ai_mouth_mask_info;

// brief 嘴内mask
typedef struct bef_ai_teeth_mask_info{
    bef_ai_face_mask_base teeth_mask[BEF_MAX_FACE_NUM];
    int face_count;
}bef_ai_teeth_mask_info,  *p_bef_ai_teeth_mask_infos;

// brief 面部mask
typedef struct bef_ai_face_mask_info{
    bef_ai_face_mask_base face_mask[BEF_MAX_FACE_NUM];
    int face_count;
}bef_ai_face_mask_info,  *p_bef_ai_face_mask_info;

// brief  每个脸的遮挡概率
typedef struct bef_ai_face_occlusion_info_base {
  float prob;
  int id;
} bef_ai_face_occlusion_info_base, *p_bef_ai_face_occlusion_info_base;

// brief  mask类型枚举
typedef enum {
    BEF_FACE_DETECT_MOUTH_MASK = 1,
    BEF_FACE_DETECT_TEETH_MASK = 2,
    BEF_FACE_DETECT_FACE_MASK = 3,
} bef_face_mask_type;


/**
 * @brief 创建人脸检测的句柄
 * @param [in] config Config of face detect algorithm 人脸检测算法的配置
 * 图片模式： BEF_DETECT_SMALL_MODEL| BEF_DETECT_MODE_IMAGE | BEF_DETECT_FULL
 * 视频模式： BEF_DETECT_SMALL_MODEL| BEF_DETECT_MODE_VIDEO | BEF_DETECT_FULL
 * 图片稍慢模式： BEF_DETECT_SMALL_MODEL| BEF_DETECT_MODE_IMAGE_SLOW | BEF_DETECT_FULL
 *
 * @param [in] strModelPath 模型文件所在路径
 * @param [out] handle Created face detect handle
 *                     创建的人脸检测句柄
 * @return If succeed return BEF_RESULT_SUC, other value please see bef_effect_ai_public_define.h
 *         成功返回 BEF_RESULT_SUC, 失败返回相应错误码, 具体请参考 bef_effect_ai_public_define.h
 */
BEF_SDK_API bef_effect_result_t
bef_effect_ai_face_detect_create(
                                 unsigned long long config,
                                 const char * strModelPath,
                                 bef_effect_handle_t *handle
                                 );

/**
 * @brief 人脸检测
 * @param [in] handle Created face detect handle
 *                    已创建的人脸检测句柄
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
 * @param [in] orientation Image orientation
 *                         输入图像的转向，具体请参考 bef_effect_ai_public_define.h 中的 bef_rotate_type
 * @param [in] detect_config Config of face detect, for example, BEF_FACE_DETECT | BEF_DETECT_EYEBALL | BEF_BROW_JUMP
 *                           人脸检测相关的配置
 * @return If succeed return BEF_RESULT_SUC, other value please see bef_effect_ai_public_define.h
 *         成功返回 BEF_RESULT_SUC, 失败返回相应错误码, 具体请参考 bef_effect_ai_public_define.h
 */
BEF_SDK_API bef_effect_result_t
bef_effect_ai_face_detect(
                          bef_effect_handle_t handle,
                          const unsigned char *image,
                          bef_ai_pixel_format pixel_format,
                          int image_width,
                          int image_height,
                          int image_stride,
                          bef_ai_rotate_type orientation,
                          unsigned long long detect_config,
                          bef_ai_face_info *p_face_info
                          );

typedef enum {
    // 设置每隔多少帧进行一次人脸检测(默认值有人脸时24, 无人脸时24/3=8), 值越大,
    // cpu占用率越低, 但检测出新人脸的时间越长.
    BEF_FACE_PARAM_FACE_DETECT_INTERVAL = 1,  // default 24
    // 设置能检测到的最大人脸数目(默认值5),
    // 当跟踪到的人脸数大于该值时，不再进行新的检测. 该值越大, 但相应耗时越长.
    // 设置值不能大于 AI_MAX_FACE_NUM
    BEF_FACE_PARAM_MAX_FACE_NUM = 2,  // default 5
    // 动态调整能够检测人脸的大小，视频模式强制是4，图片模式可以通过设置为8，检测更小的人脸，检测级别，越高代表能检测更小的人脸，取值范围：4～10
    BEF_FACE_PARAM_MIN_DETECT_LEVEL = 3,
    // base 关键点去抖参数，[1-30]
    BEF_FACE_PARAM_BASE_SMOOTH_LEVEL = 4,
    // extra 关键点去抖参数，[1-30]
    BEF_FACE_PARAM_EXTRA_SMOOTH_LEVEL = 5,
    // 嘴巴 mask 去抖动参数， [0-1], 默认0， 平滑效果更好，速度更慢
    BEF_FACE_PARAM_MASK_SMOOTH_TYPE = 6,
} bef_face_detect_type;


/**
 * @brief Set face detect parameter based on type 设置人脸检测的相关参数
 * @param [in] handle Created face detect handle
 *                    已创建的人脸检测句柄
 * @param [in] type Face detect type that needs to be set, check bef_face_detect_type for the detailed
 *                  需要设置的人体检测类型，可参考 bef_face_detect_type
 * @param [in] value Type value, check bef_face_detect_type for the detailed
 *                   参数值, 具体请参数 bef_face_detect_type 枚举中的说明
 * @return If succeed return BEF_RESULT_SUC, other value please refer bef_effect_ai_public_define.h
 *         成功返回 BEF_RESULT_SUC, 失败返回相应错误码, 具体请参考 bef_effect_ai_public_define.h
 */
BEF_SDK_API bef_effect_result_t
bef_effect_ai_face_detect_setparam(
                                   bef_effect_handle_t handle,
                                   bef_face_detect_type type,
                                   float value
                                   );
/*
 *@brief 初始化handle
 *@param [in] config 指定240模型的模型参数，创建240或者280
 *Config-240，TT_MOBILE_FACE_240_DETECT
 *Config-280，TT_MOBILE_FACE_280_DETECT
 *Config-240 快速模式, TT_MOBILE_FACE_240_DETECT | TT_MOBILE_FACE_240_DETECT_FASTMODE
 *Config-280 快速模式, TT_MOBILE_FACE_280_DETECT | TT_MOBILE_FACE_240_DETECT_FASTMODE
 *@param [in] param_path 模型的文件路径
 */
BEF_SDK_API bef_effect_result_t
bef_effect_ai_face_detect_add_extra_model(
                                          bef_effect_handle_t handle,
                                          unsigned long long config, // 配置config，创建240或者280
                                          // Config-240，TT_MOBILE_FACE_240_DETECT
                                          // Config-280，TT_MOBILE_FACE_280_DETECT
                                          // Config-240 快速模式, TT_MOBILE_FACE_240_DETECT | TT_MOBILE_FACE_240_DETECT_FASTMODE
                                          // Config-280 快速模式, TT_MOBILE_FACE_280_DETECT | TT_MOBILE_FACE_240_DETECT_FASTMODE
                                          const char *param_path
                                          );

/**
 * @brief 获取不同类型的mask输出
 *
 */
BEF_SDK_API bef_effect_result_t bef_effect_ai_face_mask_detect(bef_effect_handle_t handle,unsigned long long config, bef_face_mask_type mask_type, void * result);

/**
 * @param [in] handle Destroy the created face detect handle
 *                    销毁创建的人脸检测句柄
 */
BEF_SDK_API void
bef_effect_ai_face_detect_destroy(
                                  bef_effect_handle_t handle
                                  );

/**
 * @brief 人脸检测授权
 * @param [in] handle Created face detect handle
 *                    已创建的人脸检测句柄
 * @param [in] license 授权文件字符串
 * @param [in] length  授权文件字符串长度
 * @return If succeed return BEF_RESULT_SUC, other value please refer bef_effect_ai_public_define.h
 *         成功返回 BEF_RESULT_SUC, 授权码非法返回 BEF_RESULT_INVALID_LICENSE ，其它失败返回相应错误码, 具体请参考 bef_effect_ai_public_define.h
 */
#if defined(__ANDROID__) || defined(TARGET_OS_ANDROID)
#if BEF_EFFECT_ANDROID_WITH_JNI
BEF_SDK_API bef_effect_result_t bef_effect_ai_face_check_license(JNIEnv *env, jobject context,
                                                                 bef_effect_handle_t handle,
                                                                 const char *licensePath);
#else
BEF_SDK_API bef_effect_result_t bef_effect_ai_face_check_license(bef_effect_handle_t handle,
                                                                 const char *licensePath);
#endif

#else
#ifdef __APPLE__
BEF_SDK_API bef_effect_result_t bef_effect_ai_face_check_license(bef_effect_handle_t handle, const char *licensePath);
#endif
#endif


BEF_SDK_API bef_effect_result_t bef_effect_ai_face_check_online_license(bef_effect_handle_t handle, const char *licensePath);

#endif // _BEF_EFFECT_FACE_DETECT_AI_H_
