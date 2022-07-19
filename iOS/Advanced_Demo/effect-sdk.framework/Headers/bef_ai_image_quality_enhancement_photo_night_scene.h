#ifndef BEF_AI_IMAGE_QUALIGHT_ENHANCEMENT_PHOTO_NIGHT_SCENE_H
#define BEF_AI_IMAGE_QUALIGHT_ENHANCEMENT_PHOTO_NIGHT_SCENE_H

#include "bef_ai_image_quality_enhancement_public_define.h"


BEF_SDK_API bef_effect_result_t
bef_ai_image_quality_enhancement_photo_night_scene_create(bef_image_quality_enhancement_handle* handle,
                                                            const char* skin_seg_path, int width, int height, int image_number,
                                                          bef_ai_lens_yuv_type type);

BEF_SDK_API bef_effect_result_t
bef_ai_image_quality_enhancement_photo_night_scene_process(bef_image_quality_enhancement_handle handle, void** input, int input_size, void **output);

BEF_SDK_API bef_effect_result_t
bef_ai_image_quality_enhancement_photo_night_scene_destroy(bef_image_quality_enhancement_handle handle);

BEF_SDK_API bef_effect_result_t
bef_ai_image_quality_enhancement_photo_night_scene_check_online_license(bef_image_quality_enhancement_handle handle, const char* license_path);

#if defined(__ANDROID__) || defined(TARGET_OS_ANDROID)
#include<jni.h>
BEF_SDK_API bef_effect_result_t
bef_ai_image_quality_enhancement_photo_night_scene_check_license(JNIEnv* env, jobject context, bef_image_quality_enhancement_handle handle, const char* license_path);
#endif


#ifdef __APPLE__
BEF_SDK_API bef_effect_result_t
bef_ai_image_quality_enhancement_photo_night_scene_check_license(bef_image_quality_enhancement_handle handle, const char* license_path);
#endif

#endif
