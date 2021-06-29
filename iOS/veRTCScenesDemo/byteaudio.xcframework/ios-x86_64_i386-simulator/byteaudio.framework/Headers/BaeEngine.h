#ifndef BYTE_AUDIO_ENGINE_H
#define BYTE_AUDIO_ENGINE_H

#import "byteaudio/BaeEngineTypes.h"
#import "byteaudio/BaeStream.h"

#pragma mark - ByteAudioEngineDelegate
/**
 *  ByteAudioEngineDelegate include callback methos provided by SDK
 */
@protocol ByteAudioEngineDelegate <NSObject>

/**
 * event notify
 *
 * @param eventKey eventtype @see ByteAudioEventKey
 * @param code error code
 * @param msg event msg
 */
- (void)onByteAudioEvent:(ByteAudioEventKey)eventKey code:(int)code msg:(NSString* _Nonnull)msg;

/**
 * log msg callback
 * @param msg log msg
 */
- (void)onByteAudioLogMessage:(NSString* _Nonnull)msg;

@end

#pragma mark - ByteAudioEngine
/**
 *  ByteAudioEngine Engine control interface exposed by ByteAudio
 */
BYTEAUDIO_API
@interface ByteAudioEngine : NSObject
/**
 * Initialize and obtain a ByteAudioEngine singleton object
 *
 * @return ByteAudioEngine singleton object
 */
+ (ByteAudioEngine* _Nonnull)sharedInstance;

/**
 * initial ByteAudioEngine
 */
- (ByteAudioEngine* _Nonnull)init;

/**
 * Set the parameters issued by the server
 *
 * @param configure The parameter configuration sent by the server is a string in json format
 *
 * @return @see ByteAudioErrorCode
 */
- (int)setServerConfigure:(NSString* _Nonnull)configure;

/**
 * register a ByteAudioEngineDelegate callback
 *
 * @param delegate The ByteAudioEngineDelegate interface class is used to send callback
 * notifications to the App. The SDK will report some runtime events to the App
 * through the proxy method ByteAudioEngineDelegate.
 */
- (void)addEventDelegate:(id<ByteAudioEngineDelegate> _Nonnull)delegate;

/**
 * delete a ByteAudioEngineDelegate callback
 *
 * @param delegate The ByteAudioEngineDelegate object that needs to be deleted
 */
- (void)removeEventDelegate:(id<ByteAudioEngineDelegate> _Nullable)delegate;

/**
 * Pass in the ByteAudioStreamOption input stream parameter to create a ByteAudioInputStream input
 * stream. The instance of the input stream is maintained by ByteAudio, and this method only returns
 * the pointer of the input stream.
 *
 * @param option input stream configuration
 *
 * @return the pointer of ByteAudioInputStream
 */
- (ByteAudioInputStream* _Nullable)createInputStream:(NSString* _Nonnull)name;

/**
 * Release ByteAudioInputStream input stream resources.
 * The input stream instance is maintained by ByteAudio, this method should be used to release the
 * resources occupied by the input stream before destroying the input stream
 *
 * @param inputStream the pointer of input stream
 *
 * @return @see ByteAudioErrorCode
 */
- (int)releaseInputStream:(ByteAudioInputStream* _Nonnull)inputStream;

/**
 * Pass in the ByteAudioStreamOption output stream parameter to create a ByteAudioOutputStream
 * output stream. The instance of the output stream is maintained by ByteAudio, and this method only
 * returns the pointer of the output stream.
 *
 * @param option Output stream parameters, see the definition of ByteAudioStreamOption
 *
 * @return ByteAudioOutputStream pointer
 */
- (ByteAudioOutputStream* _Nullable)createOutputStream:(NSString* _Nonnull)name;

/**
 * ByteAudioOutputStream output stream.
 * The instance of the output stream is maintained by ByteAudio,
 * this method should be used to release the resources occupied by the output stream before
 * destroying the output stream
 *
 * @param outputStream the pointer of output stream
 *
 * @return @see ByteAudioErrorCode
 */
- (int)releaseOutputStream:(ByteAudioOutputStream* _Nonnull)outputStream;

/**
 * Pass in the ByteAudioAuxStreamOption auxiliary stream parameter to create a ByteAudioAuxStream
 * auxiliary stream. The auxiliary stream instance is maintained by ByteAudio, and this method only
 * returns the pointer of the auxiliary stream. The auxiliary stream cannot be destroyed by itself
 * through the delete method, it should be destroyed by calling the destroyAuxStream method.
 *
 * @param option Auxiliary stream parameters, see the definition of ByteAudioAuxStreamOption
 *
 * @return ByteAudioAuxStream pointer
 */
- (ByteAudioAuxStream* _Nullable)createAuxStream:(NSString* _Nonnull)name;

/**
 * ByteAudioAuxStream
 * The auxiliary stream instance is maintained by ByteAudio.
 * This method should be used to release the resources occupied
 * by the output stream before destroying the output stream
 *
 * @param auxStream output stream pointer
 *
 * @return @see ByteAudioErrorCode
 */
- (int)releaseAuxStream:(ByteAudioAuxStream* _Nonnull)auxStream;

/**
 * Turn on/off speaker playback
 *
 * @param enableSpeaker YES: switch to external playback。
 *                      NO: (Default) Switch to the handset.
 *
 * @return @see ByteAudioErrorCode
 */
- (void)setEnableSpeakerphone:(BOOL)enableSpeaker;

/**
 * Enable ByteAudio audio routing function
 *
 * @param enable: YES:turn on；NO：turn off
 */
- (void)enableAudioRouter:(BOOL)enable;

/**
 * Turn on/off the ear return function
 *
 * @param enabled YES: turn on
 *                NO: turn off(default)
 *
 * @return @see ByteAudioErrorCode
 */
- (void)enableEarMonitor:(BOOL)enabled;

/**
 * Set the callback of external audio processing algorithm before input
 * sampleRate is the input data sampling rate expected by audioFilter,
 * and channel is the number of input channels expected by audioFilter
 * @param
 *
 */
- (void)setInputFilter:(id<ByteAudioFilterDelegate> _Nullable)audioFilter
            sampleRate:(int32_t)sr
               channel:(int32_t)ch;

/**
 * Set the callback of external audio processing algorithm before input, this filter is uesd before
 * ear monitor
 * @param sampleRate is the input data sampling rate expected by audioFilter,
 * @param and channel is the number of input channels expected by audioFilter,
 *
 */
- (void)setFrontInputFilter:(id<ByteAudioFilterDelegate> _Nullable)audioFilter
                 sampleRate:(int32_t)sr
                    channel:(int32_t)ch;

/**
 * Processing external audio processing algorithm callback after setting output
 *
 * @param
 *
 */
- (void)setOutputFilter:(id<ByteAudioFilterDelegate> _Nullable)audioFilter;

/**
 * Process external audio processing algorithm callback after setting Output
 * sampleRate is the input data sampling rate expected by audioFilter,
 * channel is the number of input channels expected by audioFilter
 * @param
 *
 */
- (void)setOutputFilterWithSrAndChnnel:(id<ByteAudioFilterDelegate> _Nullable)audioFilter
                            sampleRate:(int32_t)sr
                               channel:(int32_t)ch;

/**
 * Turn off/restart local audio (enabled by default)
 *
 * @param enable: YES: restart NO: close
 */
- (void)enableLocalAudio:(BOOL)enabled;

@end

#endif  // BYTE_AUDIO_ENGINE_H
