#ifndef     BEF_AI_IMAGE_QUALITY_ENHANCEMENT_VIDA_H
#define     BEF_AI_IMAGE_QUALITY_ENHANCEMENT_VIDA_H

#include "bef_ai_image_quality_enhancement_public_define.h"

/**
 * @brief Create effect handle.
 * @param handle      handle that will be created.
 * @return            If succeed return BEF_EFFECT_RESULT_SUC, other value please see bef_effect_ai_public_define.h.
 */
BEF_SDK_API bef_effect_result_t
bef_ai_image_quality_enhancement_vida_create(bef_image_quality_enhancement_handle* handle, bef_ai_vida_init_config* config);

/**
 * process the input and get the resoult
 * @param handle
 * @param data buffer start addr
 * @param width buffer width
 * @param height buffer height
 * @return If succeed return BEF_EFFECT_RESULT_SUC, other value please see bef_effect_ai_public_define.h.
 */
BEF_SDK_API bef_effect_result_t
bef_ai_image_quality_enhancement_vida_process(bef_image_quality_enhancement_handle handle, void* data, int width, int height, float* result);

/**
 * @param handle Created effect detect handle
 *                   已创建的句柄
 * @param license_path licese path under the dircetory
 *                  license 在文件系统中的绝对路径
 * @param result If succeed return BEF_EFFECT_RESULT_SUC, other value please see bef_effect_ai_public_define.h.
 *
 */

#if defined(__ANDROID__) || defined(TARGET_OS_ANDROID)
#include<jni.h>
BEF_SDK_API bef_effect_result_t
bef_ai_image_quality_enhancement_vida_check_license(JNIEnv* env, jobject context, bef_image_quality_enhancement_handle handle, const char* license_path);
#endif

#ifdef __APPLE__
BEF_SDK_API bef_effect_result_t
bef_ai_image_quality_enhancement_vida_check_license(bef_image_quality_enhancement_handle handle, const char* license_path);
#endif

BEF_SDK_API bef_effect_result_t
bef_ai_image_quality_enhancement_vida_check_online_license(bef_image_quality_enhancement_handle handle, const char* license_path);

/**
 * @param handle    handle that will  destroy
 */
BEF_SDK_API bef_effect_result_t
bef_ai_image_quality_enhancement_vida_destory(bef_image_quality_enhancement_handle handle);

#endif
