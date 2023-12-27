//
// Created by xiangning zhu on 2021/1/12.
//

#ifndef SAMI_CORE_H
#define SAMI_CORE_H
#include "sami_core_def.h"

SAMI_CORE_EXTERN_C_BEGIN

typedef void* SAMICoreHandle;

typedef void (*SAMICoreLogCallBackPtr)(const char*, SAMICoreLogLevel); //(deprecated)

SAMI_CORE_DLL_EXPORT int SAMICoreLogConfig(SAMICoreLogCallBackPtr logFuncPtr); //(deprecated)

/**
 * logLevel:
 *    DEFAULT = 1,
 *    VERBOSE = 2,
 *    DEBUG = 3,
 *    INFO = 4,
 *    WARN = 5,
 *    ERROR = 6,
 *    FATAL = 7,
 * */
typedef int (*SAMICoreLogCallBackFuncPtr)(int logLevel, const char* msg);

/**
 * @brief: Register the log callback
 * @param: SAMICoreLogCallBackFuncPtr : callback function
 * @return: SAMI_OK : success
 * */
SAMI_CORE_DLL_EXPORT int SAMICoreInitLogConfig(SAMICoreLogCallBackFuncPtr logFuncPtr);

SAMI_CORE_DLL_EXPORT int SAMICoreInitContext(SAMICoreContextType contextType, void* params);
SAMI_CORE_DLL_EXPORT int SAMICoreReleaseContext(SAMICoreContextType type);

SAMI_CORE_DLL_EXPORT int SAMICoreInitDebugConfig(SAMICoreHandle handle, SAMICoreDebugConfig* config);
SAMI_CORE_DLL_EXPORT int SAMICoreReleaseDebugConfig(SAMICoreHandle handle);

SAMI_CORE_DLL_EXPORT int SAMICoreCreateHandleByIdentify(SAMICoreHandle* handle, SAMICoreIdentify identify, void* param);

SAMI_CORE_DLL_EXPORT int SAMICoreDestroyHandle(SAMICoreHandle handle);

SAMI_CORE_DLL_EXPORT int SAMICoreSetProperty(SAMICoreHandle handle, SAMICorePropertyId id,
                                             SAMICoreProperty* inAudioProperty);

SAMI_CORE_DLL_EXPORT int SAMICoreGetPropertyById(SAMICoreHandle handle, SAMICorePropertyId id,
                                                 SAMICoreProperty* outAudioProperty);

SAMI_CORE_DLL_EXPORT int SAMICoreGetAllProperties(SAMICoreHandle handle, SAMICorePropertySet* parametersSet);

SAMI_CORE_DLL_EXPORT int SAMICoreProcess(SAMICoreHandle handle, SAMICoreBlock* inBlock, SAMICoreBlock* outBlock);

SAMI_CORE_DLL_EXPORT int SAMICoreProcessRealtime(SAMICoreHandle handle, SAMICoreBlock* inBlock,
                                                 SAMICoreBlock* outBlock);

SAMI_CORE_DLL_EXPORT int SAMICoreProcessAsync(SAMICoreHandle handle, SAMICoreBlock* inBlock);

SAMI_CORE_DLL_EXPORT int SAMICoreDestroyProperty(SAMICoreProperty* parameter);

SAMI_CORE_DLL_EXPORT int SAMICoreDestroyAudioBlock(SAMICoreBlock* inBlock);

SAMI_CORE_DLL_EXPORT int SAMICoreDestroyPropertySet(SAMICorePropertySet* parametersSet);

SAMI_CORE_EXTERN_C_END
#endif  // SAMI_CORE_H
