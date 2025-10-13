#pragma once

#include "bef_ai_image_quality_enhancement_public_define.h"

BEF_SDK_API bef_effect_result_t
bef_ai_image_quality_enhancement_onekey_enchance_create(bef_image_quality_enhancement_handle* handle, const bef_ai_onekey_enhancement_config* config);


BEF_SDK_API bef_effect_result_t
bef_ai_image_quality_enhancement_onekey_enchance_check_license(bef_image_quality_enhancement_handle handle, const char* license_path);


BEF_SDK_API bef_effect_result_t
bef_ai_image_quality_enhancement_onekey_enchance_check_online_license(bef_image_quality_enhancement_handle handle, const char* license_path);

BEF_SDK_API bef_effect_result_t
bef_ai_image_quality_enhancement_onekey_enchance_destroy(bef_image_quality_enhancement_handle handle);


BEF_SDK_API bef_effect_result_t
bef_ai_image_quality_enhancement_onekey_enchance_process(bef_image_quality_enhancement_handle handle,
                                                         const bef_ai_onekey_process_config* config,
                                                         const bef_ai_lens_data* input,
                                                         bef_ai_lens_data *output);
