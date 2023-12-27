//
// Created by CHENZEMIN on 2022/7/27.
//

#ifndef SAMI_CORE_SAMI_CORE_AUDIO_IO_DEF_H
#define SAMI_CORE_SAMI_CORE_AUDIO_IO_DEF_H

#include <stdio.h>

enum class SAMICoreAudioEncoderFormat {
    kNone = 0,
    kMp3,       // not supported in ttffmpeg(D android)
    kAiff_S16,  // not supported in ttffmpeg(D android)
    kAiff_S24,  // not supported in ttffmpeg(D android)
    kWav_S16,
    kWav_S24,  // not supported in ttffmpeg(D android)
    kWav_F32,  // not supported in ttffmpeg(D android)
    kFLAC_F32,
    kAAC_LC,
    kAAC_LD,
    kAAC_HE,
};

enum class SAMICoreAudioEncoderAcceleration {
    kSoftware,
    kHardware_Acceleration,
};

enum class SAMICoreAudioEncoderThreading {
    kSingleThreaded,
    kMultiThreaded
};

struct SAMICoreAudioEncoderSettings {
    SAMICoreAudioEncoderFormat format{SAMICoreAudioEncoderFormat::kNone};
    SAMICoreAudioEncoderAcceleration acc{SAMICoreAudioEncoderAcceleration::kSoftware};
    SAMICoreAudioEncoderThreading threading{SAMICoreAudioEncoderThreading::kSingleThreaded};
    int num_threads{0};
};

struct SAMICoreMidiEvent {
    double time_ms;
    int event_type;
    int channel_index;
    int second_byte;
    int third_byte;
};

typedef struct MidiEventArray {
    SAMICoreMidiEvent* events;
    int length;
}SAMICoreMidiEventArray;

struct SAMICoreMidiNote {
    double time_ms;
    double duration_ms;
    int pitch;
    int velocity;
};

typedef struct MidiNoteArray {
    SAMICoreMidiNote* notes;
    int length;
}SAMICoreMidiNoteArray;

#endif  //SAMI_CORE_SAMI_CORE_AUDIO_IO_DEF_H
