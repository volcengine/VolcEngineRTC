#pragma once

#ifdef WIN32
#define BYTEAUDIO_API __declspec(dllexport)
#else
#define BYTEAUDIO_API __attribute__((__visibility__("default")))
#endif

#include <stdint.h>

#include <map>
#include <string>
#include <vector>

#include "bae_report.h"
#include "byteaudio/bae_value.h"

namespace bae {
/**
 * @brief Audio codec type supported.
 */
enum ByteAudioCodecType {
    // Invalid type
    kByteAudioCodecInvalid = 0,
    // PCM
    kByteAudioCodecPCM = 10000,
    // Opus
    kByteAudioCodecOpus = 10001,
    // G711A
    kByteAudioCodecG711A = 10002,
    // G711U
    kByteAudioCodecG711U = 10003,
    // AAC
    kByteAudioCodecAAC = 10004,
    // NICO andio codec
    kByteAudioCodecNICO = 10007,
};

enum ByteAudioAACTransType {
    kByteAudioTTRAW = 0,
    kByteAudioTTADTS = 1,
    kByteAudioTTADIF = 2,
    kByteAudioTTLATM_MCP1 = 3,
    kByteAudioTTLATM_MCP0 = 4,
    kByteAudioTTInvalid
};

/**
 * @brief Audio format of ByteAudioStreamBuffer.
 */
struct ByteAudioStreamFormat {
    // sample rate
    int sample_rate;
    // num of channels
    int channel_num;
    // bitrate bps, only for input stream
    int bitrate_bps;
    // frame size in ms, default 20, just used by pcm format
    int framesize_ms = 20;
    // transType, just used by aac
    ByteAudioAACTransType aac_trans_type;
    // aot, just used by aac
    int aac_aot;
    // see @ByteAudioCodecType
    ByteAudioCodecType codec_type;
};

/**
 * @brief Options for output stream pull buffer.
 * @attention Only for realx jitter buffer.
 */
struct ByteAudioPullBufferOptions {
    // whether got buffer (jitter buffer give to audio decoder)
    bool got_buffer;
    // decode operation (jitter buffer give to audio decoder)
    int decode_operation;
    // whether inbandfec (jitter buffer give to audio decoder)
    bool is_inbandfec;
    // in dtx mode (decoder give to jitter buffer)
    bool in_dtx_mode;
    // sync buffer size (decoder give to jitter buffer)
    unsigned int sync_buffer_size;
    // end timestamp (decoder give to jitter buffer)
    unsigned int end_timestamp;
    // stretched samples (decoder give to jitter buffer)
    int stretched_samples;
    // last decode length (decoder give to jitter buffer)
    unsigned int last_decode_length;
    // generate noise sample (decoder give to jitter buffer)
    unsigned int generate_noise_sample;
    // transType, just used by aac
    ByteAudioAACTransType aac_trans_type;
    // aot, just used by aac
    int aac_aot;
};

/**
 * @brief Audio buffer for stream and filter.
 * @attention Only for realx jitter buffer.
 */
enum ByteAudioStreamNum { kByteAudioMinAudioStreamNum = 1, kByteAudioMaxAudioStreamNum = 4 };
struct ByteAudioStreamBuffer {
    // data
    int8_t* data;
    // size of data
    int length = 0;
    // see @ByteAudioStreamFormat
    ByteAudioStreamFormat format;
    // timestamp
    unsigned int timestamp = 0;
    // audio level dbov, only for RealX
    unsigned short audio_level_dbov = 0;
    // is voice active, only for RealX
    bool voice_active = true;
    // new audio codec payload offset, only for Realx
    int nBytes[2 * kByteAudioMaxAudioStreamNum] = {0};
    // new audio codec stream num, only for Realx
    int num_stream = 0;
    uint16_t publish_event_session_id = 0;
    uint16_t subscribe_event_session_id = 0;
};

/**
 * @brief Error code.
 */
enum ByteAudioErrorCode {
    // success
    kByteAudioSuccess = 0,
    // general failure
    kByteAudioFailure = -1,
    // failure of invalid param
    kByteAudioInvalidParam = -2,
    // failure of wrong state
    kByteAudioWrongState = -3,
    // failure of no frame
    kByteAudioNoFrame = -4,
    // failure of not implemented
    kByteAudioNotImplemented = -5,
    // failure of runtime device error
    kByteAudioRuntimeDeviceError = -6,
    // failure of no permission
    kByteAudioNoPermission = -7,
    // failure of resource unavailable
    kByteAudioResourceLimited = -8,
    // failure of no device exists or have been removed
    kByteAudioDeviceNotExists = -9,
    // failure of device not support param
    kByteAudioDeviceParamNotSupport = -10
};

/**
 * @brief Audio routing.
 */
enum ByteAudioRouting {
    // default audio routing
    kByteAudioRoutingDefault = 0,
    // headset
    kByteAudioRoutingHeadset = 1,
    // earpiece
    kByteAudioRoutingEarpiece = 2,
    // speaker
    kByteAudioRoutingSpeakerhone = 3,
    // headset bluetooth
    kByteAudioRoutingHeadsetBluetooth = 4,
};

enum ByteAudioEventKey {
    // notify route changed. code: new route. See @ByteAudioRouting; msg: change reason
    kByteAudioEventRouteChanged = 1000,
    // iOS interruption begin
    kByteAudioEventInterruptionBegin = 1001,
    // iOS interruption end
    kByteAudioEventInterruptionEnd = 1002,
    // iOS media server terminate
    kByteAudioEventMediaServerTerminate = 1003,
    // iOS media server reset
    kByteAudioEventMediaServerReset = 1004,
    // iOS switch to media mode when screen captured to avoid interrupt background screen capture
    kByteAudioEventScreenCaptureMediaMode = 1005,
    // iOS device restart
    kByteAudioEventDeviceRestart = 1006,

    // record start event. code: 0 success; other: error see @ByteAudioErrorCode
    kByteAudioEventRecordingStart = 1100,
    // record first frame callback. msg: time_since_start(milliseconds)
    kByteAudioEventRecordingFirstCallback = 1101,
    // record no frame error. msg: check_time_seconds, start time out(seconds)
    kByteAudioEventRecordingNoCallbackError = 1102,
    // record stop event. code: 0 success; other: error see @ByteAudioErrorCode
    kByteAudioEventRecordingStop = 1103,
    // record stream interrupt error.
    kByteAudioEventRecordingStreamError = 1104,
    // record device volume changed.
    kByteAudioEventRecordingDeviceVolumeChanged = 1105,
    // PC record device changed.
    kByteAudioEventRecordingDeviceChanged = 1106,

    // playout start event. code: 0 success; other: error see @ByteAudioErrorCode
    kByteAudioEventPlayoutStart = 1200,
    // playout first frame callback. msg: time_since_start, start delay(milliseconds)
    kByteAudioEventPlayoutFirstCallback = 1201,
    // playout no frame error. msg: check_time_seconds, start time out(seconds)
    kByteAudioEventPlayoutNoCallbackError = 1202,
    // playout stop event. code: 0 success; other: error see @ByteAudioErrorCode
    kByteAudioEventPlayoutStop = 1203,
    // playout stream interrupt error.
    kByteAudioEventPlayoutStreamError = 1204,
    // playout device volume changed.
    kByteAudioEventPlayoutDeviceVolumeChanged = 1205,
    // PC playout device changed.
    kByteAudioEventPlayoutDeviceChanged = 1206,

    // frst audio frame recorded of input stream. code: the id of stream
    kByteAudioEventInputStreamFirstRecorded = 2000,
    // frst audio frame encoded of input stream. code: the id of stream
    kByteAudioEventInputStreamFirstEncoded = 2001,
    // audio frame encode failed of input stream. code: the id of stream
    kByteAudioEventInputStreamEncodeFailed = 2002,

    // first audio frame decoded of output stream. code: the id of stream
    kByteAudioEventOutputStreamFirstDecoded = 4000,
};

/**
 * @brief Audio device type.
 */
enum ByteAudioDeviceType {
    // render device
    kByteAudioRenderDevice,
    // capture device
    kByteAudioCaptureDevice,
};

/**
 * @brief Audio device state.
 */
enum ByteAudioDeviceStateType {
    // The device is active.
    kByteAudioDeviceStateActive = 1,
    // The device is disabled.
    kByteAudioDeviceStateDisabled = 2,
    // The device is not present.
    kByteAudioDeviceStateNotPresent = 4,
    // The device is unplugged.
    kByteAudioDeviceStateUnplugged = 8
};

/**
 * @brief Audio scenario type.
 */
enum ByteAudioScenarioType {
    /**
     * @brief music scenario, which is default.
     *        use communication mode in speaker/receiver, media mode in others.
     *        suitable in need of music performance such as live broatcasting or game.
     */
    kByteAudioScenarioMusic = 0,

    /**
     * @brief high-quality communication scenario.
     *        use communication mode in speaker/receiver and bluetooth, media mode in others.
     *        suitable in scenes of voice chat app with music.
     */
    kByteAudioScenarioHighQualityCommunication = 1,
    /**
     * @brief communication scenario.
     *        use communication mode every time whenever.
     *        suitable in scenes of switch mic frequently or video conference.
     */
    kByteAudioScenarioCommunication = 2,

    /**
     * @brief media scenario.
     *        use media mode every time whenever.
     *        suitable for special business needs and not recommended.
     */
    kByteAudioScenarioMedia = 3,
};

/**
 * @brief Audio scenario strategy.
 */
struct ByteAudioScenarioStrategy {
    /**
     * @brief Audio session mode.
     */
    enum Mode {
        // for iOS, use remote io audiounit and default session mode
        // for Android, use default audiosource and normal mode
        Media = 0,
        // for iOS, use vpio audiounit and voicechat session mode
        // for Android, use voice_communication audiosource and communication mode
        Communication = 1,
    };

    /**
     * @brief Audio scenario option in the state of broadcast/audience/voicechat
     */
    struct Option {
        Option() = default;

        Option(Mode broadcast, Mode audience, Mode voicechat);

        Option(const Option& src) = default;

        Option& operator=(const Option& src) = default;

        bool operator!=(const ByteAudioScenarioStrategy::Option& other) const;

        bool operator==(const ByteAudioScenarioStrategy::Option& other) const;

        Mode broadcast_session_mode;
        Mode audience_session_mode;
        Mode voicechat_session_mode;
    };

    ByteAudioScenarioStrategy() = default;

    explicit ByteAudioScenarioStrategy(ByteAudioScenarioType type);

    ByteAudioScenarioStrategy(const ByteAudioScenarioStrategy& src) = default;

    ByteAudioScenarioStrategy& operator=(const ByteAudioScenarioStrategy& src) = default;

    bool operator!=(const ByteAudioScenarioStrategy& other) const;

    bool operator==(const ByteAudioScenarioStrategy& other) const;

    // indicates scenario strategy when using built-in receiver/speaker
    Option built_in_device_info;
    // indicates scenario strategy when using wired headset
    Option wired_headset_info;
    // indicates scenario strategy when using bluetooth headset
    Option bt_headset_info;
    // indicates type of scenario
    ByteAudioScenarioType type;
};

/**
 * @brief Event callback handler.
 */
class ByteAudioEventHandler {
public:
    /**
     * @brief Destructor.
     */
    virtual ~ByteAudioEventHandler() = default;

    /**
     * @brief event notify
     * @param event_key: event key, see@ByteAudioEventKey
     * @param code: event code
     * @param msg: event message
     */
    virtual void on_event(ByteAudioEventKey event_key, int code, const char* msg){};

    /**
     * @brief notify the change of audio device state
     * @param device_id: device id of audio device
     * @param device_type: 0: capture, 1: render, see @ByteAudioDeviceType
     * @param device_state: state of device, see @ByteAudioDeviceStateType
     * @param device_info: info of changed device
     */
    virtual void on_audio_device_state_changed(const char* device_id, int device_type, int device_state,
                                               const char* device_info){};

    /**
     * @brief notify the change of default audio device changed
     * @param device_type: 0: capture, 1: render, see @ByteAudioDeviceType
     * @param device_info: info of changed device
     */
    virtual void on_default_device_changed(int device_type, const char* device_info){};

    /**
     * @brief log message callback
     * @param msg: log message
     */
    virtual void on_log_message(const char* msg){};
};

/**
 * @brief Audio filter callback for external effect process.
 */
class ByteAudioFilter {
public:
    /**
     * @brief Destructor.
     */
    virtual ~ByteAudioFilter() = default;

    /**
     * @brief Callback stream buffer for external process.
     * @param buffer: stream buffer
     * @return error code, refer to @ByteAudioErrorCode
     */
    virtual int on_process(ByteAudioStreamBuffer& buffer) = 0;

    // filter may use different samplerate and channel number, so need to have a specific timestamp
    unsigned int timestamp = 0;

    int32_t expected_sample_rate = -1;
    int32_t expected_channels_num = -1;
};

/**
 * @brief Option key of input/output/aux stream, determin property of stream.
 */
enum ByteAudioStreamOptionKey {
    /**
     * @brief Enable mix with aux (for input stream).
     * value_type: bool, default false
     */
    kInputOptMixWithAux = 10001,
    /**
     * @brief Enable mix with playout (for input stream).
     * value_type: bool, default false
     */
    kInputOptMixWithPlayout = 10002,
    /**
     * @brief Enable mix with record (for input stream).
     * value_type: bool, default true
     */
    kInputOptMixWithRecord = 10003,

    /**
     * @brief Aux stream type (for aux stream).
     * value_type: int32_t
     * scope: 0: audio_file (default)
     *        1: pcm_stream(pull)
     *        2: pcm_stream(push)
     */
    kAuxOptStreamType = 20000,
    /**
     * @brief Enable mix to input (for aux stream).
     * value_type: bool, default false
     */
    kAuxOptMix2Input = 20001,
    /**
     * @brief Enable mix to output (for aux stream).
     * value_type: bool, default false
     */
    kAuxOptMix2Output = 20002,
    /**
     * @brief Volume gain of mix to input (for aux stream).
     * value_type: int32_t
     * scope: 0 ~ 400 (default 100)
     */
    kAuxOptMix2InputGain = 20003,
    /**
     * @brief Volume gain of mix to output (for aux stream).
     * value_type: int32_t
     * scope: 0 ~ 400 (default 100)
     */
    kAuxOptMix2OutputGain = 20004,
    /**
     * @brief position of file aux
     * value_type: int32_t
     */
    kAuxOptPosition = 20005,
    /**
     * @brief duration of file aux
     * value_type: int32_t
     */
    kAuxOptDuration = 20006,
    /**
     * @brief Whether to mute of file aux (for aux stream).
     * value_type: bool, default false
     */
    kAuxOptMute = 20007,
    /**
     * @brief loop time for file aux
     * value_type: int32_t
     */
    kAuxOptLoopCount = 20008,

    /**
     * @brief select audio track
     * value_type: int32_t, (read/write)
     */
    kAuxOptAudioTrack = 20009,

    /**
     * @brief Wether aux stream is preloaded
     * value_type: bool, (read only)
     */
    kAuxOptPreloaded = 20010,

    /**
     * @brief Force switch to media mode when the aux stream is ready to playing out,
     *        if a output stream started once, ignore this option.
     * value_type: bool, default false
     */
    kAuxOptForceMediaMode = 20011,

    /**
     * @brief loudness for each aux stream
     * value_type: float, default 1.0f
     */
    kAuxOptIntegratedLoudness = 20012,

    /**
     * @brief playout delay in ms of the aux stream.
     * value_type: int32_t, read only
     */
    kAuxOptPlayoutDelayMs = 20013,

    /**
     * @brief publish delay in ms of the aux stream.
     * value_type: int32_t, read only
     */
    kAuxOptPublishDelayMs = 20014,

    /**
     * @brief User customized Option Key (for all stream).
     * scope: [40000, 100000)
     */
};

class ByteAudioInputSink;
/**
 * @brief Input stream, charge of record/preprocess/mix/encode and push stream buffer to external SDK/APP.
 */
class ByteAudioInputStream {
public:
    /**
     * @brief Get name of stream.
     * @return name of stream
     */
    virtual const std::string& get_name() = 0;

    /**
     * @brief Get id of stream.
     * @attention id is unique and defined incrementally by engine in order of time.
     * @return id of stream
     */
    virtual uint32_t get_id() const = 0;

    /**
     * @brief Adjust volume gain.
     * @param gain: stream volume gain, scope: 0 ~ 400 (default 100)
     * @return error code, refer to @ByteAudioErrorCode
     */
    virtual int set_gain(int gain) = 0;

    /**
     * @brief whether mute the output of input stream, have no effects on playout/aux mix
     * @param mute:
     *        true: mute the output of input stream
     *        false: unmute the output of input stream
     * @return error code, refer to @ByteAudioErrorCode
     */
    virtual int set_mute(bool mute) = 0;

    /**
     * @brief Set stream format.
     * @attention only valid before start_stream
     * @param stream_format: see @ByteAudioStreamFormat
     * @return error code, refer to @ByteAudioErrorCode
     */
    virtual int set_stream_format(ByteAudioStreamFormat stream_format) = 0;

    /**
     * @brief Update stream format after push_buffer, this is an api without a mutex.
     * @param stream_format: see @ByteAudioStreamFormat
     * @return error code, refer to @ByteAudioErrorCode
     */
    virtual int update_stream_format(ByteAudioStreamFormat stream_format) = 0;

    /**
     * @brief Set Options value.
     * @attention only valid before start_stream
     * @param key: option key, see @ByteAudioStreamOptionKey
     * @param key: option value, refer to @ByteAudioStreamOptionKey to set RXValue with correct type
     * @return error code, refer to @ByteAudioErrorCode
     */
    virtual int set_value(int key, ByteAudioValue value) = 0;

    /**
     * @brief Get Options value.
     * @param key: option key, see @ByteAudioStreamOptionKey
     * @param value: pointer of RXValue
     * @return error code, refer to @ByteAudioErrorCode
     */
    virtual int get_value(int key, ByteAudioValue* value) = 0;

    /**
     * @brief Start stream, apply stream format and options.
     *        will offer stream buffer
     * @return error code, refer to @ByteAudioErrorCode
     */
    virtual int start_stream() = 0;

    /**
     * @brief Stop stream, apply stream format and options.
     *        will no longer offer stream buffer
     * @return error code, refer to @ByteAudioErrorCode
     */
    virtual int stop_stream() = 0;

    /**
     * @brief Register @ByteAudioInputSink for offer stream buffer.
     * @param sink: refer to @ByteAudioInputSink
     * @return error code, refer to @ByteAudioErrorCode
     */
    virtual int set_input_stream_sink(ByteAudioInputSink* sink) = 0;

    /**
     * @brief report statistic of InputStream
     * @return error code, refer to @ByteAudioInputStreamReport
     */
    virtual ByteAudioInputStreamReport get_report_stats() = 0;

    /**
     * @brief report statistic of InputStream
     * @return report map with pairs <report name, report value>
     */
    virtual std::map<std::string, std::string> get_report_stats_map() = 0;
};

/**
 * @brief Input sink for offer stream buffer external SDK/APP, register to input stream.
 */
class ByteAudioInputSink {
public:
    virtual ~ByteAudioInputSink() = default;

    /**
     * @brief Callback stream buffer from input stream.
     * @param stream: handle of input stream
     * @param buf: stream buffer, refer to @ByteAudioStreamBuffer
     * @return error code, refer to @ByteAudioErrorCode
     */
    virtual int on_push_audio_buffer(ByteAudioInputStream* stream, ByteAudioStreamBuffer& buf) = 0;
};

class ByteAudioAuxSink;
/**
 * @brief Aux stream, charge of mix file/pcm_stream into input/output stream.
 */
class ByteAudioAuxStream {
public:
    virtual ~ByteAudioAuxStream() = default;

    /**
     * @brief Get name of stream.
     * @return name of stream
     */
    virtual const std::string& get_name() = 0;

    /**
     * @brief Get id of stream.
     * @attention id is unique and defined incrementally by engine in order of time.
     * @return id of stream
     */
    virtual uint32_t get_id() const = 0;

    /**
     * @brief Adjust volume gain.
     * @param gain: stream volume gain, scope: 0 ~ 400 (default 100)
     * @return error code, refer to @ByteAudioErrorCode
     */
    virtual int set_gain(int gain) = 0;

    /**
     * @brief get current volume gain.
     * @return gain value
     */
    virtual int get_gain() = 0;
    /**
     * @brief Set stream format.
     * @attention only valid before start_stream
     * @param stream_format: see @ByteAudioStreamFormat
     * @return error code, refer to @ByteAudioErrorCode
     */
    virtual int set_stream_format(ByteAudioStreamFormat stream_format) = 0;

    /**
     * @brief Get stream format
     * @return current stream format
     */
    virtual ByteAudioStreamFormat get_stream_format() = 0;

    /**
     * @brief Set Options value.
     * @attention only valid before start_stream
     * @param key: option key, see @ByteAudioStreamOptionKey
     * @param key: option value, refer to @ByteAudioStreamOptionKey to set RXValue with correct type
     * @return error code, refer to @ByteAudioErrorCode
     */
    virtual int set_value(int key, ByteAudioValue value) = 0;

    /**
     * @brief Get Options value.
     * @param key: option key, see @ByteAudioStreamOptionKey
     * @param value: pointer of RXValue
     * @return error code, refer to @ByteAudioErrorCode
     */
    virtual int get_value(int key, ByteAudioValue* value) = 0;

    /**
     * @brief Pause stream.
     * @return error code, refer to @ByteAudioErrorCode
     */
    virtual int pause_stream() = 0;

    /**
     * @brief Resume stream.
     * @return error code, refer to @ByteAudioErrorCode
     */
    virtual int resume_stream() = 0;
    /**
     * @brief preload stream
     * @return error code, refer to @ByteAudioErrorCode
     */
    virtual int preload_stream() = 0;
    /**
     * @brief unload stream
     * @return error code, refer to @ByteAudioErrorCode
     */
    virtual int unload_stream() = 0;
    /**
     * @brief Start stream, apply stream format and options.
     *        will offer stream buffer
     * @return error code, refer to @ByteAudioErrorCode
     */
    virtual int start_stream() = 0;

    /**
     * @brief Stop stream, apply stream format and options.
     *        will no longer offer stream buffer
     * @return error code, refer to @ByteAudioErrorCode
     */
    virtual int stop_stream() = 0;

    /**
     * @brief Register @ByteAudioAuxSink to pcm stream type aux stream.
     * @param sink: refer to @ByteAudioInputSink
     * @return error code, refer to @ByteAudioErrorCode
     */
    virtual int set_aux_stream_sink(ByteAudioAuxSink* sink) = 0;

    /**
     * @brief Set path to file aux stream.
     * @param sink: refer to @ByteAudioInputSink
     * @return error code, refer to @ByteAudioErrorCode
     */
    virtual int set_aux_stream_source_path(const std::string& path) = 0;

    /**
     * @brief Add input_stream name to aux_stream for mix.
     * @param stream_name: refer to an input_stream name
     * @return error code, refer to @ByteAudioErrorCode
     */
    virtual int add_input_stream_name_for_mix(const char* stream_name) = 0;

    /**
     * @brief push pcm stream to aux stream.
     * @param sink: refer to @ByteAudioInputSink
     * @return error code, refer to @ByteAudioErrorCode
     */
    virtual void on_push_audio_frame(ByteAudioStreamBuffer& buffer) = 0;

    /**
     * @brief Clear input_stream name to aux_stream for mix.
     * @param stream_name: refer to an input_stream name
     * @return error code, refer to @ByteAudioErrorCode
     */
    virtual int clear_input_stream_name_for_mix() = 0;
};

/**
 * @brief Aux sink for pull stream buffer and notify mix event, register to aux stream.
 */
class ByteAudioAuxSink {
public:
    /**
     * @brief Destructor.
     */
    virtual ~ByteAudioAuxSink() = default;

    /**
     * @brief Pull stream buffer from external SDK/APP.
     * @param sink: refer to @ByteAudioInputSink
     * @return error code, refer to @ByteAudioErrorCode
     */
    virtual int on_pull_audio_buffer(ByteAudioAuxStream* stream, ByteAudioStreamBuffer& buf) = 0;
    /**
     * @brief Notify external SDK/APP input mixing begin.
     */
    virtual void on_aux_mixing_begin(ByteAudioAuxStream* stream) = 0;
    /**
     * @brief Notify external SDK/APP input mixing end.
     */
    virtual void on_aux_mixing_end(ByteAudioAuxStream* stream) = 0;
};

class ByteAudioOutputSink;
class ByteAudioOutputFrameObserver;
/**
 * @brief Output stream: pull stream buffer from external SDK/APP, and decode/mix/postprocess/playout.
 */
class ByteAudioOutputStream {
public:
    /**
     * @brief Get name of stream.
     * @return name of stream
     */
    virtual const std::string& get_name() = 0;

    /**
     * @brief Get id of stream.
     * @attention id is unique and defined incrementally by engine in order of time.
     * @return id of stream
     */
    virtual uint32_t get_id() const = 0;

    /**
     * @brief Adjust volume gain.
     * @param gain: stream volume gain, scope: 0 ~ 400 (default 100)
     * @return error code, refer to @ByteAudioErrorCode
     */
    virtual int set_gain(int gain) = 0;

    /**
     * @brief whether mute the output of output stream, have no effects on input/aux mix
     * @param mute:
     *        true: mute the output of output stream
     *        false: unmute the output of output stream
     * @return error code, refer to @ByteAudioErrorCode
     */
    virtual int set_mute(bool mute) = 0;

    /**
     * @brief Set stream format.
     * @attention only valid before start_stream
     * @param stream_format: see @ByteAudioStreamFormat
     * @return error code, refer to @ByteAudioErrorCode
     */
    virtual int set_stream_format(ByteAudioStreamFormat stream_format) = 0;

    /**
     * @brief Set Options value.
     * @attention only valid before start_stream
     * @param key: option key, see @ByteAudioStreamOptionKey
     * @param key: option value, refer to @ByteAudioStreamOptionKey to set RXValue with correct type
     * @return error code, refer to @ByteAudioErrorCode
     */
    virtual int set_value(int key, ByteAudioValue value) = 0;

    /**
     * @brief Get Options value.
     * @param key: option key, see @ByteAudioStreamOptionKey
     * @param value: pointer of RXValue
     * @return error code, refer to @ByteAudioErrorCode
     */
    virtual int get_value(int key, ByteAudioValue* value) = 0;

    /**
     * @brief Start stream, apply stream format and options.
     *        will offer stream buffer
     * @return error code, refer to @ByteAudioErrorCode
     */
    virtual int start_stream() = 0;

    /**
     * @brief Stop stream, apply stream format and options.
     *        will no longer offer stream buffer
     * @return error code, refer to @ByteAudioErrorCode
     */
    virtual int stop_stream() = 0;

    /**
     * @brief Register @ByteAudioOutputSink for feed stream buffer into output stream.
     * @param sink: refer to @ByteAudioOutputSink
     * @return error code, refer to @ByteAudioErrorCode
     */
    virtual int set_output_stream_sink(ByteAudioOutputSink* sink) = 0;

    /**
     * @brief Register @ByteAudioOutputFrameObserver for callback audio frame.
     * @param observer: refer to @ByteAudioOutputFrameObserver
     * @return error code, refer to @ByteAudioErrorCode
     */
    virtual int set_frame_observer(ByteAudioOutputFrameObserver* observer) = 0;

    /**
     * @brief report statistic of OutPutStream
     * @return error code, refer to @ByteAudioOutPutStreamReport
     */
    virtual ByteAudioOutputStreamReport get_report_stats() = 0;

    /**
     * @brief report statistic of OutputStream
     * @return report map with pairs <report name, report value>
     */
    virtual std::map<std::string, std::string> get_report_stats_map() = 0;
};

/**
 * @brief Output sink pull offer stream buffer external SDK/APP, register to output stream.
 */
class ByteAudioOutputSink {
public:
    virtual ~ByteAudioOutputSink() = default;

    /**
     * @brief Feed stream buffer into output stream when this func callback
     * @param stream: handle of output stream
     * @param buf: stream buffer, refer to @ByteAudioStreamBuffer
     * @param options: pull options, only used for RealX jitterbuffer
     * @return error code, refer to @ByteAudioErrorCode
     */
    virtual int on_pull_audio_buffer(ByteAudioOutputStream* stream, ByteAudioStreamBuffer& buf,
                                     ByteAudioPullBufferOptions* options) = 0;
};

class ByteAudioOutputFrameObserver {
public:
    /**
     * @brief Callback the decoded pcm stream buffer from output stream.
     * need set
     * @param stream: handle of output stream
     * @param buf: stream buffer, refer to @ByteAudioStreamBuffer
     * @return error code, refer to @ByteAudioErrorCode
     */
    virtual int on_audio_frame_decoded(ByteAudioOutputStream* stream, ByteAudioStreamBuffer& buf) = 0;
};

class IByteAudioEngine {
public:
    struct CreateOptions {};

    /**
     * @brief Get a shared intance of IByteAudioEngine.
     * @return pointer of IByteAudioEngine
     */
    static IByteAudioEngine* get_engine_instance();

    /**
     * @brief Create a new ByteAudio Engine.
     *
     * @return pointer of IByteAudioEngine
     *
     * @attention 
     * The instance returned from create_engine does not support realx audio device.
     * If you want to use realx audio device, please use the instance returned by get_engine_instance()
     */
    BYTEAUDIO_API static IByteAudioEngine* create_engine(const CreateOptions& options);

    /**
     * @brief destroy the audio engine returned by create_engine().
     *
     * @param engine  pointer of IByteAudioEngine
     */
    BYTEAUDIO_API static void destroy_engine(IByteAudioEngine* engine);

    /**
     * @brief Set server configure.
     * @param cfg: type of json string, contains server configure info
     * @return error code, refer to @ByteAudioErrorCode
     */
    virtual int set_server_configure(const std::string& cfg) = 0;

    /**
     * @brief Add event handler to ByteAudio. ByteAudio can notify event to every external listener.
     * @param event_handler: refer to @ByteAudioEventHandler
     */
    virtual void add_event_handler(ByteAudioEventHandler* event_handler) = 0;

    /**
     * @brief Remove event handler from ByteAudio. If once removed, ByteAudio no longer notify event to external.
     * listener
     * @param event_handler: refer to @ByteAudioEventHandler
     */
    virtual void remove_event_handler(ByteAudioEventHandler* event_handler) = 0;

    /**
     * @brief Create a new input stream.
     * @attention The external needs hold the @ByteAudioInputStream handle, and must release it by destroy_input_stream
     * after used
     * @param name: name of stream called by external SDK/APP
     * @return handle of @ByteAudioInputStream
     */
    virtual ByteAudioInputStream* create_input_stream(const std::string& name) = 0;

    /**
     * @brief Destory a input stream.
     * @param input_stream: handle of @ByteAudioInputStream
     */
    virtual void destroy_input_stream(ByteAudioInputStream* input_stream) = 0;

    /**
     * @brief Create a new output stream.
     * @attention The external needs hold the @ByteAudioOutputStream handle, and must release it by
     * destroy_output_stream after used
     * @param name: name of stream called by external SDK/APP
     * @return handle of @ByteAudioOutputStream
     */
    virtual ByteAudioOutputStream* create_output_stream(const std::string& name) = 0;

    /**
     * @brief Destory a output stream.
     * @param output_stream: handle of @ByteAudioOutputStream
     */
    virtual void destroy_output_stream(ByteAudioOutputStream* output_stream) = 0;

    /**
     * @brief Create a new aux stream.
     * @attention The external needs hold the @ByteAudioAuxStream handle, and must release it by
     * destroy_aux_stream after used
     * @param name: name of stream called by external SDK/APP
     * @return handle of @ByteAudioAuxStream
     */
    virtual ByteAudioAuxStream* create_aux_stream(const std::string& name) = 0;

    /**
     * @brief Destory a aux stream.
     * @param aux_stream: handle of @ByteAudioAuxStream
     */
    virtual void destroy_aux_stream(ByteAudioAuxStream* aux_stream) = 0;

    /**
     * @brief Query supported audio encode codecs by ByteAudio.
     * @return vector of ByteAudioStreamFormat, contains codec_type/sample_rate/channel_num/default_bitrate combination
     */
    virtual const std::vector<ByteAudioStreamFormat> supported_encode_formats() const = 0;

    /**
     * @brief Query supported audio encode codecs by ByteAudio in rtc
     * @return vector of ByteAudioStreamFormat, contains codec_type/sample_rate/channel_num/default_bitrate combination
     */
    virtual const std::vector<ByteAudioStreamFormat> supported_rtc_encode_formats() const = 0;

    /**
     * @brief Query supported audio decode codecs by ByteAudio.
     * @return vector of ByteAudioStreamFormat, contains codec_type/sample_rate/channel_num/default_bitrate combination
     */
    virtual const std::vector<ByteAudioStreamFormat> supported_decode_formats() const = 0;

    /**
     * @brief Set mobile route to speakerphone.
     * @param enable
     *        true: route to speakerphone
     *        false: route to earpiece
     */
    virtual void set_enable_speakerphone(bool enable) = 0;

    /**
     * @brief Enable mobile audio route change.
     * @param enable
     *        true: enable mobile audio route change.
     *        false: disable mobile audio route change.
     */
    virtual void enable_audio_router(bool enable) = 0;

    /**
     * @brief Set enable ear monitor that can hear what you said.
     * @param enable
     *        true: enable
     *        false: disable
     */
    virtual void enable_ear_monitor(bool enable) = 0;

    /**
     * @brief Set headset monitor volume, which is different with record/playback volume.
     * @param volume: headset monitor volume
     */
    virtual int adjust_headset_monitor_volume(int volume) = 0;

    /**
     * @brief Enable/disable external audio source.
     * @attention only valid when has no streams
     * @param enable: enable or disable external audio source
     * @param rec_sr: external record sample rate
     * @param rec_chn: external record channel nums
     * @param play_sr: external playout sample rate
     * @param play_chn: external plaout channel nums
     * @return error code, refer to @ByteAudioErrorCode
     */
    virtual int set_external_audio_source(bool enable, int rec_sr, int rec_chn, int play_sr, int play_chn) = 0;

    /**
     * @brief Query external audio source is enabled.
     * @return external audio is enabled or disabled
     */
    virtual bool is_external_audio_source() = 0;

    /**
     * @brief Push external audio buffer for audio record in external audio source.
     * @attention only valid when external audio source  is enabled
     * @param buffer stream buffer for push data. ByteAudio will copy memory.
     * @return error code, refer to @ByteAudioErrorCode
     */
    virtual int push_external_audio_buffer(ByteAudioStreamBuffer* buffer) = 0;

    /**
     * @brief Pull external audio buffer for audio playout in external audio source.
     * @attention only valid when external audio source is enabled
     * @param buffer stream buffer for pull data. ByteAudio write memory in buffer.
     * @return error code, refer to @ByteAudioErrorCode
     */
    virtual int pull_external_audio_buffer(ByteAudioStreamBuffer* buffer) = 0;

    /**
     * @brief Set external filter process sink for audio preprocess.
     * @param sink: the callback sink for usage of external process
     */
    virtual void set_input_filter(ByteAudioFilter* filter) = 0;

    /**
     * @brief Set external filter process sink for audio preprocess, this filter is used before headset ear monitor.
     * @param sink: the callback sink for usage of external process
     */
    virtual void set_front_input_filter(ByteAudioFilter* filter) = 0;

    /**
     * @brief Set external filter process sink for audio postprocess.
     * @param sink: the callback sink for usage of external process
     */
    virtual void set_output_filter(ByteAudioFilter* filter) = 0;

    /**
     * @brief Disables/Re-enables the local audio
     * The audio function is enabled by default. This method disables or re-enables the local audio function, that is,
     * to stop or restart local audio capturing.
     * @param enable: Sets whether to disable/re-enable the local audio function
     *                true: (Default) Re-enable the local audio, that is, to start the local audio capturing device
     *                false: Disable the local audio function, that is, to stop local audio capturing.
     */
    virtual void enable_local_audio(bool enabled) = 0;

    /**
     * @brief Set audio scenario
     * @param scenario: Set the audio scenario, see @ByteAudioScenarioType.
     *                  Note: 1. only valid in Android/iOS.
     *                        2. support runtime change to device
     */
    virtual int set_audio_scenario(ByteAudioScenarioType scenario) = 0;

    /**
     * @brief Customize the audio mode strategy for the type of audio scenario
     * @param scenario_strategy: the scenario strategy with the type of ByteAudioScenarioType that want to customize, see @ByteAudioScenarioStrategy.
     *                  Note: 1. will be reset to default after every time that the last stream stop
     *                        2. support runtime change to device
     *                        3. only valid in Android/iOS.
     */
    virtual int customize_audio_scenario(const ByteAudioScenarioStrategy& scenario_strategy) = 0;

    /**
     * @brief Adjusts the recording volume of all input streams.
     * @param [in] volume: volume of recording for all input streams, scope: 0 ~ 400 (default 100)
     */
    virtual int adjust_record_volume(int volume) = 0;

    /**
     * @brief Adjusts the playback volume of all output & aux streams.
     * @param [in] volume: volume of all output & aux streams for playback, scope: 0 ~ 400 (default 100)
     */
    virtual int adjust_playback_volume(int volume) = 0;

    /**
     * @brief Enable/Disable screen audio capture.
     * @param enable whether to enable or disable screen audio capture (default disabled).
     */
    virtual int enable_screen_capture(bool enable) = 0;

    /**
     * @brief Adjusts the screen audio capture stream volume.
     * @param volume volume of screen audio capture stream, scope: 0 ~ 400 (default 100).
     */
    virtual int adjust_screen_volume(int volume) = 0;

    /**
     * @brief set optional values to engine.
     * @attention valid at all times.
     * @param key option key, defined in private interface.
     * @param value value to be set.
     * @return error code, refer to @ByteAudioErrorCode.
     */
    virtual int set_value(int key, ByteAudioValue value) = 0;

    /**
     * @brief get optinal values from engine.
     * @param key option key, defined in private interface.
     * @param value value to be get.
     * @return error code, refer to @ByteAudioErrorCode.
     */
    virtual int get_value(int key, ByteAudioValue* value) = 0;

    /**
     * @brief share cpu state with rx_media_engine.
     * @param cpu_overload_times to be set.
     */
    virtual void set_cpu_overload_times(int cpu_overload_times) = 0;
};

BYTEAUDIO_API IByteAudioEngine* get_engine_instance();
}  // namespace bae
