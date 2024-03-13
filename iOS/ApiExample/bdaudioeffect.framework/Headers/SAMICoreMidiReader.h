//
// Created by CHENZEMIN on 2022/7/8.
//

#ifndef SAMI_CORE_OC_MEMIDIREADER_H
#define SAMI_CORE_OC_MEMIDIREADER_H

#import <Foundation/Foundation.h>

#ifdef __cplusplus
extern "C" {
#endif

@interface SAMICore_MidiEvent : NSObject
@property (nonatomic, assign) double time_ms;
@property (nonatomic, assign) int event_type;
@property (nonatomic, assign) int channel_index;
@property (nonatomic, assign) int second_byte;
@property (nonatomic, assign) int third_byte;

- (_Nonnull id)initWithTimeMs:(double)time_ms_
           EventType:(int)event_type_
        ChannelIndex:(int)channel_index_
          SecondByte:(int)second_byte_
           ThirdByte:(int)third_byte_;
@end

@interface SAMICore_MidiNote : NSObject
@property (nonatomic, assign) double time_ms;
@property (nonatomic, assign) double duration_ms;
@property (nonatomic, assign) int pitch;
@property (nonatomic, assign) int velocity;

- (_Nonnull id)initWithTimeMs:(double)time_ms_
          DurationMs:(double)duration_ms_
               pitch:(int)pitch_
            Velocity:(int)velocity_;
@end

@interface SAMICore_MidiReader: NSObject

+ (NSArray<SAMICore_MidiEvent*>* _Nonnull)readMidiEventsFromFile:(NSString * _Nonnull)path
                                          TrackIndex:(size_t)track_idx;

+ (NSArray<SAMICore_MidiNote*>* _Nonnull)readMidiNotesFromFile:(NSString * _Nonnull)path
                                        TrackIndex:(size_t)track_idx
                                          Truncate:(bool)truncate;

@end

#ifdef __cplusplus
}   // extern "C"
#endif

#endif  //SAMI_CORE_OC_MEMIDIREADER_H
