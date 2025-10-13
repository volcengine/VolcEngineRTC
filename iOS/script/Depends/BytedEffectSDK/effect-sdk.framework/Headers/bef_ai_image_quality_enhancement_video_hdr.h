#ifndef _BEF_AI_IMAGE_QUALITY_ENHANCEMENT_VIDEO_HDR_H_
#define _BEF_AI_IMAGE_QUALITY_ENHANCEMENT_VIDEO_HDR_H_

#include "bef_ai_image_quality_enhancement_public_define.h"

/**
 * @brief Create effect handle.
 * @param handle      handle that will be created.
 * @return            If succeed return BEF_EFFECT_RESULT_SUC, other value please see bef_effect_ai_public_define.h.
 */
BEF_SDK_API bef_effect_result_t
bef_ai_image_quality_enhancement_video_lite_hdr_create(bef_image_quality_enhancement_handle* handle, const bef_ai_hdr_init_config* config);


BEF_SDK_API bef_effect_result_t
bef_ai_image_quality_enhancement_video_lite_hdr_process(bef_image_quality_enhancement_handle handle, const bef_ai_hdr_lite_param* input_para, const bef_ai_hdr_lite_input* input, bef_ai_hdr_lite_output* output);



/**
 * @param handle Created effect detect handle
 *                   已创建的句柄
 * @param license_path licese path under the dircetory
 *                  license 在文件系统中的绝对路径
 * @param result If succeed return BEF_EFFECT_RESULT_SUC, other value please see bef_effect_ai_public_define.h.
 *
 */
BEF_SDK_API bef_effect_result_t
bef_ai_image_quality_enhancement_video_lite_hdr_check_license(bef_image_quality_enhancement_handle handle, const char* license_path);

BEF_SDK_API bef_effect_result_t
bef_ai_image_quality_enhancement_video_lite_hdr_check_online_license(bef_image_quality_enhancement_handle handle, const char* license_path);

/**
 * @param handle    handle that will  destroy
 */
BEF_SDK_API bef_effect_result_t
bef_ai_image_quality_enhancement_video_lite_hdr_destory(bef_image_quality_enhancement_handle handle);


#endif
