#ifndef BEF_AI_IMAGE_QUALITY_ENHANCEMENT_NIGHT_SCENE_H
#define BEF_AI_IMAGE_QUALITY_ENHANCEMENT_NIGHT_SCENE_H

#include "bef_ai_image_quality_enhancement_public_define.h"


/**
 * @brief Create effect handle.
 * @param handle      handle that will be created.
 * @return            If succeed return BEF_EFFECT_RESULT_SUC, other value please see bef_effect_ai_public_define.h.
 */
BEF_SDK_API bef_effect_result_t
bef_ai_image_quality_enhancement_night_scene_create(bef_image_quality_enhancement_handle* handle, const char* dir);


/**
 *  set the input property 
 * @param handle
 * @param width Input width of the  buffer or texture
 * @param height Input height of the  buffer or texture
 * @return If succeed return BEF_EFFECT_RESULT_SUC, other value please see bef_effect_ai_public_define.h.
 */
BEF_SDK_API bef_effect_result_t
bef_ai_image_quality_enhancement_night_scene_set_width_and_height(bef_image_quality_enhancement_handle handle, int width , int height);

/**
 * process the input and get the resoult
 * @param handle
 * @param input input infomation of texture
 *              Android的输入需要为oes 纹理， 需要传入纹理的宽高，纹理需要放在input->data.texture[0]
 * @param output output infomation of texture
 *              Android的输出为oes 纹理，返回纹理的宽和高，纹理结果放在output->data.texture[0]
 * @return If succeed return BEF_EFFECT_RESULT_SUC, other value please see bef_effect_ai_public_define.h.
 */
BEF_SDK_API bef_effect_result_t
bef_ai_image_quality_enhancement_night_scene_process(bef_image_quality_enhancement_handle handle, const bef_ai_night_scene_data* input, bef_ai_night_scene_data *output);


/**
 * @param handle Created effect detect handle
 *                   已创建的句柄
 * @param license_path licese path under the dircetory
 *                  license 在文件系统中的绝对路径
 * @param result Current face detect result struct
 *
 */
BEF_SDK_API bef_effect_result_t 
bef_ai_image_quality_enhancement_night_scene_check_license(bef_image_quality_enhancement_handle handle, const char* license_path);

BEF_SDK_API bef_effect_result_t 
bef_ai_image_quality_enhancement_night_scene_check_online_license(bef_image_quality_enhancement_handle handle, const char* license_path);

/**
 * @param handle    handle that will  destroy
 */
BEF_SDK_API bef_effect_result_t 
bef_ai_image_quality_enhancement_night_scene_destory(bef_image_quality_enhancement_handle handle);

#endif 