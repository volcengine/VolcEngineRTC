//
// Created by ByteDance on 2023/5/23.
//

#ifndef SAMI_CORE_SAMICOREAEDS2S_H
#define SAMI_CORE_SAMICOREAEDS2S_H

@interface AedForS2s: NSObject

- (int)aedForS2sProcess:(NSString *)input_file withValue:(float)threshold modelFile:(NSString *)model configFile:(NSString *)config;

- (int)aedForS2sProcess:(NSString *)input_file withValue:(float)threshold modelFile:(NSString *)model configFile:(NSString *)config businessType:(NSString *)type;

@end

#endif  //SAMI_CORE_SAMICOREAEDS2S_H