// Copyright (C) 2019 Beijing Bytedance Network Technology Co., Ltd.
#ifndef bef_effect_ai_api_h
#define bef_effect_ai_api_h

#include "bef_effect_ai_public_define.h"
#include "bef_effect_ai_face_detect.h"
#include "bef_effect_ai_hand.h"
#include "bef_effect_ai_skeleton.h"
#include "bef_effect_ai_face_attribute.h"

#if (defined(__ANDROID__) || defined(TARGET_OS_ANDROID))
#if BEF_EFFECT_ANDROID_WITH_JNI
#include <jni.h>
#endif
#endif


/**
 * @brief Create effect handle.
 * @param handle      Effect handle that will be created.
 * @return            If succeed return BEF_EFFECT_RESULT_SUC, other value please see bef_effect_ai_public_define.h.
 */
BEF_SDK_API bef_effect_result_t bef_effect_ai_create(bef_effect_handle_t *handle);

/**
 * @param handle      Effect handle that will  destroy
 */
BEF_SDK_API void bef_effect_ai_destroy(bef_effect_handle_t handle);



/**
 * @brief Initialize effect handle.
 * @param handle     Effect handle
 * @param width      Texture width
 * @param height     Texture height
 * @param strModeDir  Resource folder
 * @return           If succeed return BEF_EFFECT_RESULT_SUC, other value please see bef_effect_ai_public_define.h
 */
BEF_SDK_API bef_effect_result_t bef_effect_ai_init(bef_effect_handle_t handle, int width, int height, const char *strModeDir, const char* deviceName);


/**
 * should set imageMode = true while processing images with only faceMakeup sticker has been set
 * @param handle
 * @param imageMode
 * @return
 */
BEF_SDK_API bef_effect_result_t bef_effect_ai_set_image_mode(bef_effect_handle_t handle, bool imageMode);

/**
* @brief Return all available features name, can only be called after bef_effect_ai_init
* @return            If succeed return BEF_EFFECT_RESULT_SUC, `features` will contain all available feature name item, each item has length of BEF_EFFECT_FEATURE_LEN,
            `len` would point to a number which stands for the amount of features.
            BEF_RESULT_FAIL is returned if the given space is not big enough (according to `len`) to hold data returned by this api.
            BEF_RESULT_INVALID_EFFECT_HANDLE is returned if this api been called before `bef_effect_ai_init`.
*/
BEF_SDK_API bef_effect_result_t bef_effect_available_features(char (*features)[BEF_EFFECT_FEATURE_LEN], int* len);



/**
 * @brief Set camera toward
 * @param handle        Effect handle that  initialized
 * @param position      Camera positin
 * @return if succeed return IES_RESULT_SUC,  other value please see bef_effect_base_define.h
 */
BEF_SDK_API bef_effect_result_t bef_effect_ai_set_camera_device_position(bef_effect_handle_t handle,  bef_ai_camera_position position);

BEF_SDK_API bef_effect_result_t bef_effect_ai_set_device_rotation(bef_effect_handle_t handle, float* quaternion);

 /**
 * @brief Set frame size.
 * @param handle     Effect handle
 * @param width      Texture width
 * @param height     Texture height
 * @return           If succeed return BEF_EFFECT_RESULT_SUC,  other value please see bef_effect_ai_public_define.h
 */
BEF_SDK_API bef_effect_result_t bef_effect_ai_set_width_height(bef_effect_handle_t handle, int width, int height);


/**
 * @brief Set camera orientation, which is used for detection.
 * @param handle      Effect handle that  initialized
 * @param orientation  Camera clock wise
 * @return            if succeed return IES_RESULT_SUC,  other value please see bef_effect_base_define.h
 */
BEF_SDK_API bef_effect_result_t bef_effect_ai_set_orientation(bef_effect_handle_t handle, bef_ai_rotate_type orientation);

/**
 * @brief Setup beauty-face-filter with a specified string.
 * @param handle      Effect handle
 * @param strBeautyName The name of beauty will apply
 * @return            If succeed return BEF_EFFECT_RESULT_SUC,  other value please see bef_effect_ai_public_define.h
 */
BEF_SDK_API bef_effect_result_t bef_effect_ai_set_beauty(bef_effect_handle_t handle, const char *strBeautyName);

/**
 * @brief Setup beauty-face-filter with a specified string.
 * @param handle      Effect handle
 * @param strMakeupName The path of makeup resource will apply
 * @return            If succeed return BEF_EFFECT_RESULT_SUC,  other value please see bef_effect_define.h
 */
BEF_SDK_API bef_effect_result_t bef_effect_ai_set_buildin_makeup(bef_effect_handle_t handle, const char* strMakeupName);


/**
 * @brief Setup reshape-face-filter with a specified string.
 * @param handle          Effect handle
 * @param strPath    The absolute path of effect package.
 * @return                If succeed return BEF_EFFECT_RESULT_SUC, other value please see bef_effect_ai_public_define.h
 */
BEF_SDK_API bef_effect_result_t bef_effect_ai_set_reshape_face(bef_effect_handle_t handle, const char *strPath);

/**
 * @brief Update reshape-face-filter parameters
 * @param handle          Effect handle
 * @param fIntensity      Filter intensity, range in [0.0, 1.0]
 * @return                if succeed return BEF_EFFECT_RESULT_SUC, other value please see bef_effect_ai_public_define.h
 */
BEF_SDK_API bef_effect_result_t bef_effect_ai_update_reshape_face(bef_effect_handle_t handle, const float fIntensity);

/**
 * @brief Update reshape-face-filter parameters
 * @param handle          Effect handle
 * @param eyeIntensity    eye intensity, range in [0.0, 1.0]
  * @param cheekIntensity cheek intensity, range in [0.0, 1.0]
 * @return                if succeed return BEF_EFFECT_RESULT_SUC, other value please see bef_effect_ai_public_define.h
 */
BEF_SDK_API bef_effect_result_t bef_effect_ai_update_reshape_face_intensity(bef_effect_handle_t handle, const float eyeIntensity, const float cheekIntensity);


/**
 @param handle              effect handle
 @param leftFilterPath current filter path
 @param rightFilterPath    next filter path
 @parm  direction           the direction that the next filter will appear
 @param position            the borderline of left-filter and right-filter in x-axis.
 @return            if succeed return BEF_EFFECT_RESULT_SUC, other value please see bef_effect_ai_public_define.h
 */
BEF_SDK_API bef_effect_result_t bef_effect_ai_switch_color_filter_v2(bef_effect_handle_t handle, const char *leftFilterPath, const char *rightFilterPath, float position);
/**
 * Set color filter with a specified string.
 * @param handle    Effect handle
 * @param strPath   The absolute path of effect package.
 * @return          If succeed return BEF_EFFECT_RESULT_SUC, other value please see bef_effect_ai_public_define.h
 */
BEF_SDK_API bef_effect_result_t bef_effect_ai_set_color_filter_v2(bef_effect_handle_t handle, const char *strPath);

/**
 * @brief Set effect with a specified string.
 * @param handle    Effect handle
 * @param strPath   The absolute path of effect package.
 * @return          If succeed return BEF_EFFECT_RESULT_SUC, other value please see bef_effect_define.h
 */
BEF_SDK_API bef_effect_result_t bef_effect_ai_set_effect(bef_effect_handle_t handle, const char *strPath);

/**
 * @brief set composer resource path,
 * 设置composer资源包路径，使composer资源包生效
 * @param handle Effect Handle
 * @param strPath composer file path
 * @Deprecated
 */
BEF_SDK_API bef_effect_result_t bef_effect_ai_set_composer(bef_effect_handle_t handle, const char *strPath);

/**
 * @brief set composer effect path array
 * 设置资源包路径数组,通过更新数组设置特效的组合
 * @param nodePaths 特效资源路径的数组
 * @param nodeNum 特效资源路径的数组长度
 *
 */
BEF_SDK_API bef_effect_result_t bef_effect_ai_composer_set_nodes(bef_effect_handle_t handle, const char *nodePaths[], int nodeNum);

/// 设置资源包路径数组，可通过额外的 ndoeTags 设置附加信息
/// @param handle 创建的 handle
/// @param nodePaths 特效资源路径数组
/// @param nodeTags 特效资源附加信息，与nodePaths 一一对应
/// @param nodeNum 特效资源数组的长度
BEF_SDK_API bef_effect_result_t bef_effect_ai_composer_set_nodes_with_tags(bef_effect_handle_t handle, const char *nodePaths[], const char *nodeTags[], int nodeNum);

/**
 * @brief append composer effect path array
 * 追加资源包路径数组,通过追加数组设置特效的组合
 * @param nodePaths 特效资源路径的数组
 * @param nodeNum 特效资源路径的数组长度
 *
 */
BEF_SDK_API bef_effect_result_t bef_effect_ai_composer_append_nodes(bef_effect_handle_t handle, const char *nodePaths[], int nodeNum);
/**
 * @brief append composer effect path array
 * 追加资源包路径数组,通过追加数组设置特效的组合
 * @param nodePaths 特效资源路径的数组
 * @param nodeTags 特效资源附加信息，与nodePaths 一一对应
 * @param nodeNum 特效资源路径的数组长度
 *
 */
BEF_SDK_API bef_effect_result_t bef_effect_ai_composer_append_nodes_with_tags(bef_effect_handle_t handle, const char *nodePaths[], const char *nodeTags[], int nodeNum);

/**
 * @brief remove composer effect path array
 * 删除资源包路径数组,通过删除数组设置特效的组合
 * @param nodePaths 特效资源路径的数组
 * @param nodeNum 特效资源路径的数组长度
 *
 */
BEF_SDK_API bef_effect_result_t bef_effect_ai_composer_remove_nodes(bef_effect_handle_t handle, const char *nodePaths[], int nodeNum);

/**
 * @brief set composer node intensity
 * 设置组合特效的单个节点的强度
 * @param handle Effect Handle
 * @param key 特效资源的路径
 * @param value 特效的强度
 */
BEF_SDK_API bef_effect_result_t bef_effect_ai_composer_update_node(bef_effect_handle_t handle, const char *nodePath,const char *nodeTag, float value);

/**
 * @brief 设置Composer模式
 * @param handle        Effect handle
 * @param mode          0: A槽区+B槽区模式（Composer Feature）, 1: A槽区+B槽区+C槽区模式（Composer下沉）
 * @param orderType     0: 按照zorder排序, 目前只支持0
 * @return              成功返回BEF_EFFECT_RESULT_SUC, 其它值参考bef_effect_define.h
 * @Deprecated
 */
BEF_SDK_API bef_effect_result_t bef_effect_ai_composer_set_mode(bef_effect_handle_t handle, int mode, int orderType);

/**
 * @param handle          Effect handle
 * @param textureid_src   texture source
 * @return                if succeed return BEF_EFFECT_RESULT_SUC, other value please see bef_effect_ai_public_define.h
 */
BEF_SDK_API bef_effect_result_t bef_effect_ai_algorithm_texture(bef_effect_handle_t handle, unsigned int textureid_src, double timeStamp);

/**
 * @param handle          Effect handle
 * @param texture         texture source
 * @param buffer          buffer address
 * @param buffer_format   format of buffer, see bef_ai_pixel_format
 * @param buffer_width    with of buffer
 * @param buffer_height   height of buffer
 * @param buffer_stride   stride of buffer
 * @param timeStamp       current time, unit second
 * @return                if succeed return BEF_EFFECT_RESULT_SUC, other value please see bef_effect_ai_public_define.h
 */
BEF_SDK_API bef_effect_result_t bef_effect_ai_algorithm_texture_with_buffer(bef_effect_handle_t handle,
                                                                            unsigned int texture,
                                                                            const unsigned char *buffer,
                                                                            bef_ai_pixel_format buffer_format,
                                                                            int buffer_width,
                                                                            int buffer_height,
                                                                            int buffer_stride,
                                                                            double timeStamp);

/**
 * @param [in] handle Created effect handle
 *                    初始化的特效句柄，需要再OpenGL环境中使用
 * @param [in] img_in 数据buffer
 * @param [in] fmt_in 数据buffer的格式，支持RGBA,BGRA(ios支持）,NV21,NV12,YUV420P
 * @param [in] image_width 数据buffer图像的宽度
 * @param [in] image_height 数据buffer图像的长度
 * @param [in] image_stride 数据buffer的步长（一行的占用的字节数）
 * @param [in] timestamp     时间戳
 * @return If succeed return BEF_RESULT_SUC, other value please refer bef_effect_ai_public_define.h
 *         成功返回 BEF_RESULT_SUC, 失败返回相应错误码, 具体请参考 bef_effect_ai_public_define.h
 */
BEF_SDK_API bef_effect_result_t
bef_effect_ai_algorithm_buffer(
                              bef_effect_handle_t handle,
                              const unsigned char *img_in,
                              bef_ai_pixel_format fmt_in,
                              int image_width,
                              int image_height,
                              int image_stride,
                              double timestamp
                              );

/**
 * @breif            Draw srcTexture with effects to dstTexture.
 * @param handle     Effect handle
 * @param srcTexture source texture
 * @param dstTexture distination texture
 * @return           if succeed return IES_RESULT_SUC,  other value please see bef_effect_base_define.h
 */
BEF_SDK_API bef_effect_result_t bef_effect_ai_process_texture(bef_effect_handle_t handle, unsigned int srcTexture, unsigned int dstTexture, double timeStamp);

/**
 * @breif Draw source buffer with effects to destination buffer.
 *        绘制特效
 * @param [in] handle Created effect handle
 *                    初始化的特效句柄
 * @param [in] img_in 输入图片buffer
 * @param [in] fmt_in 输入图片buffer的格式，支持RGBA,BGRA（ios支持）,NV12,NV21,YUV420P
 * @param [in] image_width 输入图片buffer的宽度
 * @param [in] image_height 输入图片buffer的高度
 * @param [in] image_stride 输入图片buffer的步长（一行字节数）
 * @param [in] img_out 输出图片数据
 * @param [in] fmt_out 输出图片数据格式，支持RGBA,NV12,NV21,YUV420P
 * @param [in] timestamp   Current timestamp
 *                         时间戳
 * @return If succeed return BEF_RESULT_SUC, other value please see bef_effect_ai_public_define.h
 *         成功返回 BEF_RESULT_SUC, 失败返回相应错误码, 具体请参考 bef_effect_ai_public_define.h
 */
#if BEF_EFFECT_ANDROID_WITH_JNI
BEF_SDK_API bef_effect_result_t
bef_effect_ai_process_buffer(bef_effect_handle_t handle,
                             const unsigned char *img_in,
                             bef_ai_pixel_format fmt_in,
                             int image_width,
                             int image_height,
                             int image_stride,
                             unsigned char *img_out,
                             bef_ai_pixel_format fmt_out,
                             double timestamp
                             );
#else
BEF_SDK_API bef_effect_result_t
bef_effect_ai_process_buffer(bef_effect_handle_t handle,
                            const unsigned char *img_in,
                            bef_ai_pixel_format fmt_in,
                            int image_width,
                            int image_height,
                            int image_stride,
                            unsigned char *img_out,
                            bef_ai_camera_position is_front,
                            double timestamp,
                            int readflag,
                            int firstFrameCnt,
                            int previewMode,
                            bef_ai_rotate_type orientation,
                            int dstTexture
                            );
#endif
/**
 * @param handle      Effect handle that will be created
 * @param fIntensity  Filter smooth intensity, range in [0.0, 1.0]
 * if fIntensity is 0 , this filter would not work.
 * @return            if succeed return BEF_EFFECT_RESULT_SUC,  other value please see bef_effect_ai_public_define.h
 */
BEF_SDK_API bef_effect_result_t bef_effect_ai_set_intensity(bef_effect_handle_t handle, bef_intensity_type intensityType, float fIntensity);

/**
 * @brief 开启或关闭并行框架，开启后算法在独立线程完成检测。默认不开启
 * @param handle effect handle
 * @param usePipeline 控制参数
 */
BEF_SDK_API bef_effect_result_t bef_effect_ai_use_pipeline_processor(bef_effect_handle_t handle, bool usePipeline);

/**
* @brief 清理并行框架残余算法任务，在切后台、切换分辨率或切相机时使用。总之画面会不连续出现的时候都应该调用
* @param handle     Effect handle
*/
BEF_SDK_API bef_effect_result_t bef_effect_ai_clean_pipeline_processor_task(bef_effect_handle_t handle);

/**
 * @brief 开启并行框架3buffer策略，避免 buffer 的拷贝
 * @param handle effect handle
 * @param use3Buffer 是否开启3buffer
 */
BEF_SDK_API bef_effect_result_t bef_effect_ai_use_3buffer(bef_effect_handle_t handle, bool use3buffer);

/**
 * @brief 获取人脸检测结果
 * @param handle 已创建的授权
 * @param result 人脸检测结果
 * @return If succeed return BEF_RESULT_SUC, other value please refer bef_effect_ai_public_define.h
 *         成功返回 BEF_RESULT_SUC, 授权码非法返回BEF_RESULT_INVALID_LICENSE，其它失败返回相应错误码, 具体请参考 bef_effect_ai_public_define.h
 */
BEF_SDK_API bef_effect_result_t bef_effect_ai_get_face_detect_result(bef_effect_handle_t handle, bef_ai_face_info* result);


/**
 * @brief 获取人脸检测mask结果
 * @param handle 已创建的授权
 * @param mask_type mask类型枚举值， bef_face_mask_type
 * @param result 人脸检测mask结果，根据类型输入
 * @return If succeed return BEF_RESULT_SUC, other value please refer bef_effect_ai_public_define.h
 *         成功返回 BEF_RESULT_SUC, 授权码非法返回BEF_RESULT_INVALID_LICENSE，其它失败返回相应错误码, 具体请参考 bef_effect_ai_public_define.h
 */
BEF_SDK_API bef_effect_result_t bef_effect_ai_get_face_seg_result(bef_effect_handle_t handle, int mask_type, void* result);


/**
 * @brief 获取手的检测结果
 * @param handle 已创建的授权
 * @param result 手检测结果
 * @return If succeed return BEF_RESULT_SUC, other value please refer bef_effect_ai_public_define.h
 *         成功返回 BEF_RESULT_SUC, 授权码非法返回BEF_RESULT_INVALID_LICENSE，其它失败返回相应错误码, 具体请参考 bef_effect_ai_public_define.h
 */
BEF_SDK_API bef_effect_result_t bef_effect_ai_get_hand_detect_result(bef_effect_handle_t handle, bef_ai_hand_info *result);

/**
 * @brief 获取人体检测结果
 * @param handle 已创建的授权
 * @param result 人体检测结果
 * @return If succeed return BEF_RESULT_SUC, other value please refer bef_effect_ai_public_define.h
 *         成功返回 BEF_RESULT_SUC, 授权码非法返回BEF_RESULT_INVALID_LICENSE，其它失败返回相应错误码, 具体请参考 bef_effect_ai_public_define.h
 */
BEF_SDK_API bef_effect_result_t bef_effect_ai_get_skeleton_detect_result(bef_effect_handle_t handle, bef_ai_skeleton_result *result);

/**
 * @brief 获取人脸属性检测结果
 * @param handle 已创建的授权
 * @param result 人脸属性检测结果
 * @return If succeed return BEF_RESULT_SUC, other value please refer bef_effect_ai_public_define.h
 *         成功返回 BEF_RESULT_SUC, 授权码非法返回BEF_RESULT_INVALID_LICENSE，其它失败返回相应错误码, 具体请参考 bef_effect_ai_public_define.h
 */
BEF_SDK_API bef_effect_result_t bef_effect_ai_get_face_attr_detect_result(bef_effect_handle_t handle, bef_ai_face_attribute_result *result);



/**
* @brief 给贴纸发送消息
* @param handle 已创建的授权
* @param msgID 消息id
* @return If succeed return BEF_RESULT_SUC, other value please refer bef_effect_ai_public_define.h
*         成功返回 BEF_RESULT_SUC, 授权码非法返回BEF_RESULT_INVALID_LICENSE，其它失败返回相应错误码, 具体请参考 bef_effect_ai_public_define.h
*/
BEF_SDK_API bef_effect_result_t bef_effect_ai_send_msg(bef_effect_handle_t handle, unsigned int msgID, long arg1, long arg2, const char *arg3);


/**
* @brief 给贴纸发送开拍重置信息，这个函数目前仅用在使用creator
*        设计的贴纸，并且确认勾选了开拍重置选项
* @param handle 已创建的授权
* @return If succeed return BEF_RESULT_SUC, other value please refer bef_effect_ai_public_define.h
*         成功返回 BEF_RESULT_SUC, 授权码非法返回BEF_RESULT_INVALID_LICENSE，其它失败返回相应错误码, 具体请参考 bef_effect_ai_public_define.h
*/
BEF_SDK_API bef_effect_result_t bef_effect_ai_reset_sticker(bef_effect_handle_t handle);

/// @brief 处理触摸事件
/// @param handle 已创建的句柄
/// @param event 触摸事件类型
/// @param x 触摸位置
/// @param y 触摸位置
/// @param force 压力值
/// @param majorRadius 触摸范围
/// @param pointerId 触摸点id
/// @param pointerCount 触摸点数量
BEF_SDK_API bef_effect_result_t bef_effect_ai_process_touch(bef_effect_handle_t handle, bef_ai_touch_event_code event, float x, float y, float force, float majorRadius, int pointerId, int pointerCount);

/// @brief 处理手势事件
/// @param handle 已创建的句柄
/// @param gesture 手势类型
/// @param x 触摸位置，缩放手势表示缩放比例，旋转手势表示旋转角度
/// @param y 触摸位置
/// @param dx 移动距离
/// @param dy 移动距离
/// @param factor 缩放因数
BEF_SDK_API bef_effect_result_t bef_effect_ai_process_gesture(bef_effect_handle_t handle, bef_ai_gesture_event_code gesture, float x, float y, float dx, float dy, float factor);

/// @brief 通过 buffer 设置 render cache texture
/// @details 传入一个固定名字的纹理给到 SDK，传入一个 buffer，SDK 会将其解析成纹理
/// @param handle 句柄
/// @param key 纹理名称
/// @param image 图像数据
BEF_SDK_API bef_effect_result_t bef_effect_ai_set_render_cache_texture_with_buffer(bef_effect_handle_t handle, const char* key, bef_ai_image* image);

/// @brief 通过文件设置 render cache texture
/// @details 传入一个固定名字的纹理给到 SDK，传入一个文件路径，SDK 会将其解析成纹理
/// @param handle 句柄
/// @param key 纹理名称
/// @param path 文件绝对路径
BEF_SDK_API bef_effect_result_t bef_effect_ai_set_render_cache_texture(bef_effect_handle_t handle, const char* key, const char* path);

/// @brief 设置 gles 版本
/// @details 需要在初始化之前调用才有效果
/// @param handle 句柄
/// @param api gles 版本，参见 bef_ai_render_api_type
BEF_SDK_API bef_effect_result_t bef_effect_ai_set_render_api(bef_effect_handle_t handle, bef_ai_render_api_type api);

/// @brief 是否使用内置传感器
/// @param handle 句柄
/// @param useBuiltinSensor 是否使用内置传感器
BEF_SDK_API bef_effect_result_t bef_effect_ai_use_builtin_sensor(bef_effect_handle_t handle, bool useBuiltinSensor);

/// @brief 在一定时间内加载素材
/// @param handle 句柄
/// @param timeout 等待时间，单位 us，-1 时表示一直等待直到素材加载完成
BEF_SDK_API bef_effect_result_t bef_effect_ai_load_resource_with_timeout(bef_effect_handle_t handle, int timeout);

/// @brief 通过key获取一张截图
/// @param handle Effect实例
/// @param key 要获取截图对应的key值
/// @param image 指向由effect分配的截图，如果当前无截图返回nullptr
/// @return 成功则返回BEF_RESULT_SUC
BEF_SDK_API bef_effect_result_t bef_effect_ai_get_captured_image_with_key(bef_effect_handle_t handle, const char* key, bef_ai_image** image);

/// @brief 释放截图
/// @param handle Effect实例
/// @param image 指向通过bef_effect_get_captured_image_with_key获取的截图
/// @return
BEF_SDK_API void bef_effect_ai_release_captured_image(bef_effect_handle_t handle, bef_ai_image* image);

#ifdef __ANDROID__
/**
 * @param handle Created effect detect handle
 *                   已创建的句柄
 * @param result Current face detect result struct
 *
 */
#if BEF_EFFECT_ANDROID_WITH_JNI
BEF_SDK_API bef_effect_result_t 
bef_effect_ai_check_license(
                            JNIEnv* env, 
                            jobject context, 
                            bef_effect_handle_t handle, 
                            const char *licensePath);

BEF_SDK_API bef_effect_result_t
bef_effect_ai_check_license_buffer(
                           JNIEnv* env,
                           jobject context,
                           bef_effect_handle_t handle,
                           const char *buffer,
                           unsigned long buffer_len
                           );
#else
BEF_SDK_API bef_effect_result_t
bef_effect_ai_check_license(
                           bef_effect_handle_t handle,
                           const char *licensePath
                           );
#endif

#else
BEF_SDK_API bef_effect_result_t
bef_effect_ai_check_license(
                           bef_effect_handle_t handle,
                           const char *licensePath
                           );

BEF_SDK_API bef_effect_result_t
bef_effect_ai_check_license_buffer(
                           bef_effect_handle_t handle,
                           const char *buffer,
                           unsigned long buffer_len
                           );
#endif


BEF_SDK_API bef_effect_result_t
bef_effect_ai_check_online_license(bef_effect_handle_t handle, const char *licensePath);

/// @brief 开启或关闭强制人脸检测
/// @param handle Effect实例
/// @param force 开关值
/// @return 成功则返回BEF_RESULT_SUC
BEF_SDK_API bef_effect_result_t bef_effect_ai_set_algorithm_force_detect(bef_effect_handle_t handle, bool force);

#endif /* bef_effect_ai_h */
