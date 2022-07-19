//
//  bef_effect_ai_error_code_format.h
//  effect-sdk
//
//  Created by qun on 2021/3/9.
//

#ifndef bef_effect_ai_error_code_format_h
#define bef_effect_ai_error_code_format_h

#include "bef_effect_ai_public_define.h"

/// @brief 根据错误码获取对应提示
/// @param errorCode 错误码
BEF_SDK_API const char *bef_effect_ai_error_code_get(int errorCode);

#endif /* bef_effect_ai_error_code_format_h */
