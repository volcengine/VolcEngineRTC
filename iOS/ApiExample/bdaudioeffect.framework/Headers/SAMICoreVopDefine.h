//
// Created by ByteDance on 2023/7/12.
//

#ifndef SAMI_CORE_SAMICOREVOPDEFINE_H
#define SAMI_CORE_SAMICOREVOPDEFINE_H

typedef NS_ENUM(NSInteger, SAMICore_VopLanguage) {
    SAMICore_OC_JAPANESE,
    SAMICore_OC_ENGLISH,
};
typedef NS_ENUM(NSInteger, SAMICore_VopTextType) {
    SAMICore_OC_PRIMARY = 50,
    SAMICore_OC_STANDARD = 80
};

typedef NS_ENUM(NSInteger, SAMICore_VopRecordingType) {
    SAMICore_OC_PCM_S16,
    SAMICore_OC_FILE,
    SAMICore_OC_INTERNAL
};
typedef NS_ENUM(NSInteger, SAMICore_VopState) {
    SAMICore_OC_Error,
    SAMICore_OC_UNINITIALIZED,
    SAMICore_OC_AGREEING,
    SAMICore_OC_RECORDING,
    SAMICore_OC_UPLOADING,
    SAMICore_OC_BUILDING,
    SAMICore_OC_COMPLETED
};
typedef NS_ENUM(NSInteger, SAMICore_VopSpeakerInfoCommand) {
    SAMICore_OC_SIGN_AGREEMENT,
    SAMICore_OC_START_RECORD_TASK,
    SAMICore_OC_START_BUILD_TASK,
    SAMICore_OC_SET_PUBLIC,
    SAMICore_OC_SET_PRIVATE,
    SAMICore_OC_DELETE,
};

typedef NS_ENUM(NSInteger, SAMICore_VopTextState) {
    SAMICore_OC_AVAILABLE,
    SAMICore_OC_SUCCESS_END,
    SAMICore_OC_FAILED_END,
};

typedef NS_ENUM(NSInteger, SAMICore_VopProcessRecordAudioResult) {
    SAMICore_OC_INTERNAL_ERROR,
    SAMICore_OC_NETWORK_ERROR,
    SAMICore_OC_PASSED,
    SAMICore_OC_SNR_FAILED,
    SAMICore_OC_WER_FAILED,
    SAMICore_OC_SKIPPED,
};




#endif  //SAMI_CORE_SAMICOREVOPDEFINE_H
