#ifndef BYTE_AUDIO_ENGINE_TYPES_H
#define BYTE_AUDIO_ENGINE_TYPES_H

#import <AVFoundation/AVFoundation.h>

#define BYTEAUDIO_API __attribute__((__visibility__("default")))

typedef NS_ENUM(NSInteger, ByteAudioErrorCode) {
    // success
    ByteAudioErrorCodeSuccess = 0,
    // general failure
    ByteAudioErrorCodeFailure = -1,
    // failure of invalid param
    ByteAudioErrorCodeInvalidParam = -2,
    // failure of wrong state
    ByteAudioErrorCodeWrongState = -3,
    // failure of no frame
    ByteAudioErrorCodeNoFrame = -4,
    // failure of not implemented
    ByteAudioErrorCodeNotImplemented = -5,

    // failure of runtime device error
    ByteAudioErrorCodeRuntimeDeviceError = -6,
    // failure of no permission
    ByteAudioErrorCodeNoPermission = -7,
    // failure of resource unavailable
    ByteAudioErrorCodeResourceLimited = -8,
    // failure of no device exists or have been removed
    ByteAudioErrorCodeDeviceNotExists = -9,
    // failure of device not support param
    ByteAudioErrorCodeDeviceParamNotSupport = -10,
};

typedef NS_ENUM(NSInteger, ByteAudioRouting) {
    // default audio routing
    ByteAudioRoutingDefault = 0,
    // headset
    ByteAudioRoutingHeadset = 1,
    // earpiece
    ByteAudioRoutingEarpiece = 2,
    // speaker
    ByteAudioRoutingSpeakerPhone = 3,
    // headset bluetooth
    ByteAudioRoutingHeadsetBluetooth = 4,
};

#pragma mark - ByteAudioStreamOption
/**
 *  ByteAudioStreamOption
 * Used to create ByteAudioInputStream, ByteAudioOutputStream, ByteAudioMuxStream, and specify
 * stream parameters
 */
typedef NS_ENUM(NSInteger, ByteAudioOption) {
    // Enable mix with aux (for input stream).
    ByteAudioInputOptMixWithAux = 10001,
    // Enable mix with playout (for input stream).
    ByteAudioInputOptMixWithPlayout = 10002,

    // Aux stream type (for aux stream).
    ByteAudioAuxOptStreamType = 20000,
    // Enable mix to input (for aux stream).
    ByteAudioAuxOptMix2Input = 20001,
    // Enable mix to output (for aux stream).
    ByteAudioAuxOptMix2Output = 20002,
    // Volume gain of mix to input (for aux stream).
    ByteAudioAuxOptMix2InputGain = 20003,
    // Volume gain of mix to output (for aux stream).
    ByteAudioAuxOptMix2OutputGain = 20004,
    // position of file aux
    ByteAudioAuxOptPosition = 20005,
    // duration of file aux
    ByteAudioAuxOptDuration = 20006,
    // Whether to mute of file aux (for aux stream).
    ByteAudioAuxOptMute = 20007,
    // loop time for file aux
    ByteAudioAuxOptLoopCount = 20008,
    // select audio track
    ByteAudioAuxOptAudioTrack = 20009,
};

typedef NS_ENUM(NSInteger, ByteAudioCodecType) {
    // Invalid type
    ByteAudioCodecNull = 0,
    // PCM
    ByteAudioCodecPCM = 10000,
    // Opus
    ByteAudioCodecOpus = 10001,
    // G711A
    ByteAudioCodecG711A = 10002,
    // G711U
    ByteAudioCodecG711U = 10003,
    // AAC
    ByteAudioCodecAAC = 10004,
    // NICO andio codec
    ByteAudioCodecInvalid
};

typedef NS_ENUM(NSInteger, ByteAudioEventKey) {
    // notify route changed. code: new route. see @ByteAudioRouting; msg: change reason
    ByteAudioEventRouteChanged = 1000,
    // iOS interruption begin
    ByteAudioEventInterruptionBegin = 1001,
    // iOS interruption end
    ByteAudioEventInterruptionEnd = 1002,
    // iOS media server terminate
    ByteAudioEventMediaServerTerminate = 1003,
    // iOS media server reset
    ByteAudioEventMediaServerReset = 1004,
    // iOS switch to media mode when screen captured to avoid interrupt background screen capture.
    ByteAudioEventScreenCaptureMediaMode = 1005,
    // iOS device restart
    ByteAudioEventDeviceRestart = 1006,

    // record start event. code: 0 success; other: error see @ByteAudioErrorCode
    ByteAudioEventRecordingStart = 1100,
    // record first frame callback. msg: time_since_start(milliseconds)
    ByteAudioEventRecordingFirstCallback = 1101,
    // record no frame error. msg: check_time_seconds, start time out(seconds)
    ByteAudioEventRecordingNoCallbackError = 1102,
    // record stop event. code: 0 success; other: error see @ByteAudioErrorCode
    ByteAudioEventRecordingStop = 1103,
    // record stream interrupt error.
    ByteAudioEventRecordingStreamError = 1104,
    // record device volume changed.
    ByteAudioEventRecordingDeviceVolumeChanged = 1105,

    // playout start event. code: 0 success; other: error see @ByteAudioErrorCode
    ByteAudioEventPlayoutStart = 1200,
    // playout first frame callback. msg: time_since_start, start delay(milliseconds)
    ByteAudioEventPlayoutFirstCallback = 1201,
    // playout no frame error. msg: check_time_seconds, start time out(seconds)
    ByteAudioEventPlayoutNoCallbackError = 1202,
    // playout stop event. code: 0 success; other: error see @ByteAudioErrorCode
    ByteAudioEventPlayoutStop = 1203,
    // playout stream interrupt error.
    ByteAudioEventPlayoutStreamError = 1204,
    // playout device volume changed.
    ByteAudioEventPlayoutDeviceVolumeChanged = 1105,
};

#pragma mark - ByteAudioStreamFormat
/**
 *  ByteAudioStreamFormat Specify audio data format
 */
BYTEAUDIO_API
@interface ByteAudioStreamFormat : NSObject
@property(nonatomic, assign) int sampleRate;
@property(nonatomic, assign) int channelNum;
@property(nonatomic, assign) int bitrateBps;
@property(nonatomic, assign) ByteAudioCodecType codecType;

- (int)getSampleRate;

- (int)getChannelNum;

- (ByteAudioCodecType)getCodecType;
@end

#pragma mark - ByteAudioStreamBuffer
/**
 *  ByteAudioStreamBuffer Specify ByteAudio external SDK data interaction structure
 */
BYTEAUDIO_API
@interface ByteAudioStreamBuffer : NSObject

@property(nonatomic, assign) int8_t* _Nullable data;
@property(nonatomic, assign) int length;
@property(nonatomic, assign) unsigned int timestamp;
@property(nonatomic, assign) ByteAudioStreamFormat* _Nonnull streamFormat;

- (void)initWithComponents:(int8_t* _Nullable)data
                    format:(ByteAudioStreamFormat* _Nonnull)streamFormat;

- (int)getLength;

- (unsigned int)getTimeStamp;

- (ByteAudioStreamFormat* _Nonnull)getStreamFormat;

@end

/**
 *  ByteAudioFilterDelegate Register into ByteAudioEngine for ByteAudio
 * SDK and external data exchange
 */
@protocol ByteAudioFilterDelegate <NSObject>

/**
 * ByteAudio SDK exchanges data with external audio processing
 *
 * @param stream Data buffer for data exchange
 *
 * @return @see ByteAudioErrorCode
 */
- (ByteAudioErrorCode)onProcess:(ByteAudioStreamBuffer* _Nonnull)stream;

@end

#endif  // BYTE_AUDIO_ENGINE_TYPES_H
