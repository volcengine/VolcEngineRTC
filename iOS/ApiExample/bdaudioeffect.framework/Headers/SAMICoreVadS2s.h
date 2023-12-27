//
// Created by ByteDance on 2023/5/23.
//

#ifndef SAMI_CORE_SAMICOREVADS2S_H
#define SAMI_CORE_SAMICOREVADS2S_H

@interface VadForS2s: NSObject

- (int)vadForS2sProcess:(NSString *)input_file withValue:(float)threshold;

@end

#endif  //SAMI_CORE_SAMICOREVADS2S_H
