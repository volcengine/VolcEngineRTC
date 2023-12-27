//
// Created by CHENZEMIN on 2022/7/26.
//

#ifndef SAMI_CORE_SAMI_CORE_IO_H
#define SAMI_CORE_SAMI_CORE_IO_H
#include <stdio.h>
#include "sami_core_audio_io_def.h"
#include "sami_core_def.h"

SAMI_CORE_EXTERN_C_BEGIN

typedef void* SAMICoreFileSource;

typedef void* SAMICoreAudioEncoder;

SAMI_CORE_DLL_EXPORT int SAMICoreFileSourceCreate(SAMICoreFileSource* fileSource, const char* inputPath);

SAMI_CORE_DLL_EXPORT bool SAMICoreFileSourceSeek(SAMICoreFileSource fileSource, size_t position);

SAMI_CORE_DLL_EXPORT size_t SAMICoreFileSourceRead(SAMICoreFileSource fileSource, float* buffer, size_t frame_num);

SAMI_CORE_DLL_EXPORT size_t SAMICoreFileSourceGetNumChannel(SAMICoreFileSource fileSource);

SAMI_CORE_DLL_EXPORT size_t SAMICoreFileSourceGetSampleRate(SAMICoreFileSource fileSource);

SAMI_CORE_DLL_EXPORT size_t SAMICoreFileSourceGetNumFrames(SAMICoreFileSource fileSource);

SAMI_CORE_DLL_EXPORT size_t SAMICoreFileSourceGetNumBit(SAMICoreFileSource fileSource);

SAMI_CORE_DLL_EXPORT size_t SAMICoreFileSourceGetPosition(SAMICoreFileSource fileSource);

SAMI_CORE_DLL_EXPORT void SAMICoreFileSourceDestory(SAMICoreFileSource fileSource);

SAMI_CORE_DLL_EXPORT int SAMICoreAudioEncoderCreate(SAMICoreAudioEncoder* audioEncoder, void* settings);

SAMI_CORE_DLL_EXPORT int SAMICoreAudioEncoderOpen(SAMICoreAudioEncoder audioEncoder, const char* output_path,
                                                  int sample_rate, int num_channels, long long bit_rate);

SAMI_CORE_DLL_EXPORT long long SAMICoreAudioEncoderWritePlanarData(SAMICoreAudioEncoder audioEncoder,
                                                                   const float* const* planar_data, int num_channels,
                                                                   long long num_sample_per_channel);

SAMI_CORE_DLL_EXPORT long long SAMICoreAudioEncoderWriteInterleaveData(SAMICoreAudioEncoder audioEncoder,
                                                                       const float* interleave_data, int num_channels,
                                                                       long long num_sample_per_channel);

SAMI_CORE_DLL_EXPORT void SAMICoreAudioEncoderClose(SAMICoreAudioEncoder audioEncoder);

SAMI_CORE_DLL_EXPORT void SAMICoreAudioEncoderFlush(SAMICoreAudioEncoder audioEncoder);

SAMI_CORE_DLL_EXPORT int SAMICoreAudioEncoderGetSampleRate(SAMICoreAudioEncoder audioEncoder);

SAMI_CORE_DLL_EXPORT int SAMICoreAudioEncoderGetNumChannels(SAMICoreAudioEncoder audioEncoder);

SAMI_CORE_DLL_EXPORT bool SAMICoreAudioEncoderIsOpen(SAMICoreAudioEncoder audioEncoder);

SAMI_CORE_DLL_EXPORT void SAMICoreAudioEncoderDestory(SAMICoreAudioEncoder audioEncoder);

SAMI_CORE_DLL_EXPORT SAMICoreMidiEventArray SAMICoreReadMidiEventsFromFile(const char* path, size_t track_idx = 0);

SAMI_CORE_DLL_EXPORT SAMICoreMidiNoteArray SAMICoreReadMidiNotesFromFile(const char* path, size_t track_idx = 0,
                                                                         bool truncate = true);

SAMI_CORE_DLL_EXPORT void SAMICoreMidiEventDestory(SAMICoreMidiEventArray midi_array);

SAMI_CORE_DLL_EXPORT void SAMICoreMidiNoteDestory(SAMICoreMidiNoteArray midi_array);

SAMI_CORE_EXTERN_C_END

#endif  //SAMI_CORE_SAMI_CORE_IO_H
