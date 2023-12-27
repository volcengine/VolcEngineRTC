//
// Created by LIJING on 2021/11/22.
//

#ifndef SAMI_CORE_OC_SAMICORE_H
#define SAMI_CORE_OC_SAMICORE_H

#import <Foundation/Foundation.h>

#import "SAMICoreCode.h"

#import "SAMICoreIdentify.h"
#import "SAMICorePropertyId.h"
#import "SAMICoreDataType.h"
#import "SAMICoreEffectParam.h"

#ifdef __cplusplus
extern "C" {
#endif

@interface SAMICore: NSObject

typedef void (*SAMICore_LogCallBackPtr)(const char* _Nullable , SAMICore_LogLevel);
+ (int)SAMICoreSetLogCallBack:(SAMICore_LogCallBackPtr _Nonnull)logFuncPtr;

+ (int)initContextWithType:(SAMICore_ContextType)type
                 parameter:(id _Nonnull)params;

+ (int)releaseContext:(SAMICore_ContextType)type;

- (_Nullable instancetype)initWithIdentify:(SAMICore_Identify)identify
                                     param:(id _Nullable)param
                                    result:(int* _Nullable)result;

- (void)destroy;
- (int)setProperty:(SAMICore_Property* _Nonnull)inAudioProperty withId:(SAMICore_PropertyId)id;
- (int)getProperty:(SAMICore_Property* _Nonnull)outAudioProperty withId:(SAMICore_PropertyId)id;

- (int)processWithInBlock:(SAMICore_AudioBlock* _Nullable)inBlock outBlock:(SAMICore_AudioBlock* _Nullable)outBlock;

- (int)initDebugWithConfig:(SAMICore_DebugConfig* _Nullable)config;
- (int)releaseDebugConfig;

@end

#ifdef __cplusplus
}   // extern "C"
#endif

#endif  //SAMI_CORE_OC_SAMICORE_H
