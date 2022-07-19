#ifndef BEF_EFFECT_AI_UTILS_H_
#define BEF_EFFECT_AI_UTILS_H_

#include <vector>
#include <string>
#include <chrono>

#include "Bach/BachCommon.h"
#include "bef_effect_ai_public_define.h"
#if defined(__ANDROID__)
#if BEF_EFFECT_ANDROID_WITH_JNI
#include <jni.h>
const char *getPackageName(JNIEnv *env, jobject context);
#endif
#endif

#ifdef __APPLE__
std::string getBundleId();
#endif

std::string getAppId();

// @targetdir  out targetdir
// decode resouces to a temp dir, should del the temp after load resources
// @return the temp dir
//

void decodeBuffer(const char* buffer, size_t bufferlen, const char* key, char* outbuffer, size_t* outbuferLen, size_t bufferOffset = 0, bool addEnd = true);

#if 0
#define OUTPARAM
void decodeResource(const char* resourcedir, OUTPARAM char* targetdir, const char* key);
void copy_r_decode(const char* src_dir, const char* dst_dir, const char* decode_suffix, const char* key);
#endif

void r_decode(const char* src_dir, const char* decode_suffix, const char* key);

void r_del_decoded(const char* src_dir, const char* decode_suffix);

using Time = decltype(std::chrono::high_resolution_clock::now());

Time time();

double time_diff(Time t1, Time t2);

int reformat_license_error_code(int license_code);

//void hookFileLoad(labcv_license::MultiLicRes *licBag);

void  hookFileLoad(const char* key);

std::string getOnlineDeviceId();

Bach::AEPixelFormat BachPixelFormatConvert(bef_ai_pixel_format format);
Bach::AERotateMode  BachRotateModeConvert(bef_ai_rotate_type orientation);
bef_effect_result_t BachReturnCodeConvert(Bach::BachErrorCode code);

#endif
