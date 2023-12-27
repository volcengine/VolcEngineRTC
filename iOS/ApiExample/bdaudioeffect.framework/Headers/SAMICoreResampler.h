//
// Created by zhangkg on 2022/9/19.
//

#ifndef SAMI_CORE_OC_RESAMPLER_H
#define SAMI_CORE_OC_RESAMPLER_H

#import <Foundation/Foundation.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef NS_ENUM(int, SAMICore_ResampleType) {
    SAMICore_ResampleType_SpecifiedInAndOutLength = 0,
    SAMICore_ResampleType_ModifiedOutLength = 1
};

@interface SAMICore_ResampleSettingParam : NSObject
    @property (nonatomic, assign) const size_t src_frames;
    @property (nonatomic, assign) const size_t dst_frames;
    @property (nonatomic, assign) const size_t channels;
    @property (nonatomic, assign) const SAMICore_ResampleType resampleType;
@end

@interface SAMICoreOCResampler : NSObject
- (_Nullable instancetype)initWithResampleParam:(SAMICore_ResampleSettingParam* _Nonnull)param;

-(int)inputBlockSizeRequest:(int)given_output_block_size;

// only support planner data if channels >= 2
-(size_t)resample:(const float* _Nonnull const* _Nonnull)source
      source_frame:(size_t)source_frames
       destination:(float* _Nonnull* _Nonnull)destination
       dest_frames:(size_t)dest_frames;
@end

#ifdef __cplusplus
}   // extern "C"
#endif

#endif  //SAMI_CORE_OC_RESAMPLER_H