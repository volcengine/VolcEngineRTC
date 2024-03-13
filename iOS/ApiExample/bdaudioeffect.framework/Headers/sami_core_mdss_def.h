#ifndef SAMI_CORE_MDSS_DEF_H
#define SAMI_CORE_MDSS_DEF_H

#include "sami_core_def.h"

typedef enum MulDimSingScoringMode {
    MulDimSingScoring_Note = 0x01,
    MulDimSingScoring_Rhythm = 0x02,
    MulDimSingScoring_Emotion = 0x04
} SAMICoreMulDimSingScoringMode;

typedef struct MulDimSingScoringCreateParameter {
    int sample_rate;
    unsigned int mode;
    char const* lyricsFilepath;
    char const* midiFilepath;
    SAMICoreTokenVerifyOnlineParameter lyricsAlignmentServiceParameter; /* needed by Rhythm or Emotion */
    char const* tmp_filepath;
} SAMICoreMulDimSingScoringCreateParameter;

typedef struct MulDimSingScoringRealtimeInfo {
    double timeMilliseconds;  // Timestamp (-1, 0~T)
    double songScore;  // Score till the current song position (0~100)
    int sentenceCount; // Sentences' number count

    int sentenceIndex;     // 0-Based Sentence-Index to identify the sentenceScore referring to. (-1, 0~N-1)
    double sentenceScore;  // Score of the last sentence (0~100)

    double userPitch;      // MIDI pitch value of the detected Vocal (-1, 0.0~127.0)
    int userNote;          // MIDI Note value of the detected Vocal (-1, 0~127)
    int userCent;          // MIDI Note Cent of the detected Vocal (-50~+50)
    int userOctave;        // Octave offset of the detected Vocal (-9, +9)

    double refPitch;      // MIDI pitch value of the Reference MIDI (-1, 0.0~127.0)
    int refNote;          // MIDI Note value of the Reference MIDI (-1, 0~127)
    int refCent;          // MIDI Note Cent of the Reference MIDI (-50~+50)
} SAMICoreMulDimSingScoringRealtimeInfo;

typedef struct MulDimSingScoringOverallInfo {
    float rhythm_score;
    float emotion_score;
    float note_score;
} SAMICoreMulDimSingScoringOverallInfo;

#endif