#ifndef _BEF_EFFECT_AI_HAL_API_H_
#define _BEF_EFFECT_AI_HAL_API_H_

#include "bef_effect_ai_public_define.h"

/**
 * @brief Initialize effect handle.
 * @param handle          Effect handle
 * @param model_path      model path
 * @param license_path    license path
 * @param use_pipeline    use_pipeline
 * @return           If succeed return BEF_EFFECT_RESULT_SUC, other value please see bef_effect_ai_public_define.h
 */
BEF_SDK_API bef_effect_result_t bef_effect_ai_hal_init(bef_effect_handle_t *handle, 
                                                      const char *model_path, 
                                                      const char *license_path, 
                                                      bool use_pipeline);

/**
 * @param handle      Effect handle that will  destroy
 */
BEF_SDK_API bef_effect_result_t bef_effect_ai_hal_destory(bef_effect_handle_t handle);

/**
 * process image
 * @param handle       Effect handle
 * @param image        imput image
 * @param out_image    output image
 * @param format_in    imput image format
 * @param format_out   output image format
 * @param width        image width
 * @param height       imput height
 * @param run_times    render times
 * @param orientation  image orientation
 * @return          If succeed return BEF_EFFECT_RESULT_SUC, other value please see bef_effect_ai_public_define.h
 */
BEF_SDK_API bef_effect_result_t bef_effect_ai_hal_process(bef_effect_handle_t handle, 
                                                          unsigned char* image,
                                                          unsigned char* out_image,
                                                          bef_ai_pixel_format format_in, 
                                                          bef_ai_camera_position is_front,
                                                          int width, 
                                                          int height, 
                                                          int run_times,
                                                          bef_ai_rotate_type orientation);

/**
 * Set color filter with a specified string.
 * @param handle    Effect handle
 * @param filter_path   The absolute path of effect package.
 * @return          If succeed return BEF_EFFECT_RESULT_SUC, other value please see bef_effect_ai_public_define.h
 */
BEF_SDK_API bef_effect_result_t bef_effect_ai_hal_set_color_filter_v2(bef_effect_handle_t handle, const char* filter_path);

/**
 * @param handle      Effect handle that will be created
 * @param fIntensity  Filter smooth intensity, range in [0.0, 1.0]
 * if fIntensity is 0 , this filter would not work.
 * @return            if succeed return BEF_EFFECT_RESULT_SUC,  other value please see bef_effect_ai_public_define.h
 */
BEF_SDK_API bef_effect_result_t bef_effect_ai_hal_set_intensity(bef_effect_handle_t handle, int intensityType, float fIntensity);

/**
 * @brief Set effect with a specified string.
 * @param handle    Effect handle
 * @param stickerPath   The absolute path of effect package.
 * @return          If succeed return BEF_EFFECT_RESULT_SUC, other value please see bef_effect_define.h
 */
BEF_SDK_API bef_effect_result_t bef_effect_ai_hal_set_effect(bef_effect_handle_t handle, const char* stickerPath);

/**
 * @brief append composer effect path array
 * 追加资源包路径数组,通过追加数组设置特效的组合
 * @param nodePaths 特效资源路径的数组
 * @param nodeNum 特效资源路径的数组长度
 */
BEF_SDK_API bef_effect_result_t bef_effect_ai_hal_composer_append_nodes(bef_effect_handle_t handle, 
                                                                        const char *nodePaths[], 
                                                                        int nodeNum);

/**
 * @brief remove composer effect path array
 * 删除资源包路径数组,通过删除数组设置特效的组合
 * @param nodePaths 特效资源路径的数组
 * @param nodeNum 特效资源路径的数组长度
 */
BEF_SDK_API bef_effect_result_t bef_effect_ai_hal_composer_remove_nodes(bef_effect_handle_t handle, 
                                                                        const char *nodePaths[], 
                                                                        int nodeNum);

/**
 * @brief set composer effect path array
 * 设置资源包路径数组,通过更新数组设置特效的组合
 * @param nodePaths 特效资源路径的数组
 * @param nodeNum 特效资源路径的数组长度
 *
 */
BEF_SDK_API bef_effect_result_t bef_effect_ai_hal_composer_set_nodes(bef_effect_handle_t handle, 
                                                                    const char *nodePaths[], 
                                                                    int nodeNum);

/// 设置资源包路径数组，可通过额外的 ndoeTags 设置附加信息
/// @param handle 创建的 handle
/// @param nodePaths 特效资源路径数组
/// @param nodeTags 特效资源附加信息，与nodePaths 一一对应
/// @param nodeNum 特效资源数组的长度
BEF_SDK_API bef_effect_result_t bef_effect_ai_hal_composer_set_nodes_with_tags(bef_effect_handle_t handle, 
                                                                                const char *nodePaths[], 
                                                                                const char *nodeTags[], 
                                                                                int nodeNum);

/**
* @brief 清理并行框架残余算法任务，在切后台、切换分辨率或切相机时使用。总之画面会不连续出现的时候都应该调用
* @param handle     Effect handle
*/
BEF_SDK_API bef_effect_result_t bef_effect_ai_hal_clean_pipeline_processor_task(bef_effect_handle_t handle);

/**
 * @brief Set camera toward
 * @param handle        Effect handle that  initialized
 * @param position      Camera positin
 * @return if succeed return IES_RESULT_SUC,  other value please see bef_effect_base_define.h
 */
BEF_SDK_API bef_effect_result_t bef_effect_ai_hal_set_camera_device_position(bef_effect_handle_t handle,  
                                                                            bef_ai_camera_position position);

/**
 * @brief set composer node intensity
 * 设置组合特效的单个节点的强度
 * @param handle Effect Handle
 * @param key 特效资源的路径
 * @param value 特效的强度
 */
BEF_SDK_API bef_effect_result_t bef_effect_ai_hal_composer_update_node(bef_effect_handle_t handle, 
                                                                    const char *nodePath,
                                                                    const char *nodeTag, 
                                                                    float value);

#endif
