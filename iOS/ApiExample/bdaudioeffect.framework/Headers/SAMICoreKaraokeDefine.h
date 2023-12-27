//
// Created by zhangkg on 2022/11/7.
//

#ifndef SAMI_CORE_KARAOKE_DEFINE_H
#define SAMI_CORE_KARAOKE_DEFINE_H

#import <Foundation/Foundation.h>
#include "SAMICoreCode.h"
#include "SAMICoreDataType.h"


#ifdef __cplusplus
extern "C" {
#endif

// Karaoke message ID
typedef NS_ENUM(NSInteger, SAMICore_KaraokeMessageId) {
    // record
    SAMICore_Karaoke_Record_ToEnd = 10,
    SAMICore_Karaoke_Record_StopFinished = 11,

    // edit
    SAMICore_Karaoke_Edit_ToEnd = 50,
    SAMICore_Karaoke_Edit_StopFinished = 51,
    SAMICore_Karaoke_Edit_ErrorOccurred = 52,

    // byteTuner state
    SAMICore_Karaoke_ByteTuner_Succeed = 100,
    SAMICore_Karaoke_ByteTuner_ErrorOccurred = 101,

    // log tracker
    SAMICore_Karaoke_LogTracker_BeCalled = 102,
    SAMICore_Karaoke_LogTracker_Failed = 103,
    SAMICore_Karaoke_LogTracker_Performance = 104
};

// Karaoke message callback
typedef void (^SAMICore_KaraokeMessageCallBackPtr)(SAMICore_KaraokeMessageId, NSDictionary* _Nullable);

#ifdef __cplusplus
}   // extern "C"
#endif
#endif  //SAMI_CORE_KARAOKE_DEFINE_H
