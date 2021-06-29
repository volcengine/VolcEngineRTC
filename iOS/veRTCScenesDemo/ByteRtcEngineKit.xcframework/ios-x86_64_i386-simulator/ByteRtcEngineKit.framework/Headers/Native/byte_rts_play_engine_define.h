/*
 * Copyright 2020 @bytedance
 *  Created on: Seq 05, 2020
 */

#pragma once

namespace bytertc {

#define RTS_MAX_BUF_SIZE    1024
#define CONTENT_MIN_SIZE    512
#define CONTENT_MAX_SIZE    4096
#define SEI_BUFFER_MAX_SIZE 16

/**
 *@brief RTS播放器事件类型
*/
enum RTSPlayEngineEvent {
    kRtsPlayInited,                // init player(unused)
    kRtsPlaySendOffer,             // send offer
    kRtsPlayRecvAnswer,            // receive answer
    kRtsPlayPrepared,              // prepare offer(unused)
    kRtsPlayStarted,               // start player(unused)
    kRtsPlayStopped,               // stop player(unused)
    kRtsPlayUnInited,              // uninit player(unused)
    kRtsPlayRecvFirstAudioPacket,  // receive first audio packet
    kRtsPlayRecvFirstVideoPacket,  // receive first video packet
    kRtsPlayRecvFirstAudioFrame,   // receive first audio frame
    kRtsPlayRecvFirstVideoFrame,   // receive first video frame
    kRtsPlayHttpStateChange,       // http state change
};

/**
 *@brief RTS播放器错误类型
*/
enum RTSPlayEngineError {
    kRtsPlayErrorNone = 0,
    kRtsPlayErrorIllegalParameters,
    kRtsPlayErrorState,
    
    kRtsPlayErrorPlayBase = 30000,
    kRtsPlayErrorPlayPrepareTimeout,
    
    kRtsPlayErrorSourceBase = 31000,
    kRtsPlayErrorSourceInit,
    kRtsPlayErrorSourcePrepare,
    kRtsPlayErrorSourceStart,
    kRtsPlayErrorSourceStop,
    kRtsPlayErrorSourceUnInit,
    kRtsPlayErrorSourceExpectIpFail,
    kRtsPlayErrorSourceFetchSDPFail,
    kRtsPlayErrorSourceNetRequestFail,

    kRtsPlayErrorPeerBase = 32000,
    kRtsPlayErrorPeerInit,
    kRtsPlayErrorPeerPrepare,
    kRtsPlayErrorPeerStart,
    kRtsPlayErrorPeerStop,
    kRtsPlayErrorPeerUnInit,
    kRtsPlayErrorPeerDecode,        // decoder error
    kRtsPlayErrorPeerNetworkIO,     // network error
    kRtsPlayErrorPeerCreateSDP,     // create sdp error
    kRtsPlayErrorPeerSetLocalSDP,   // set local sdp error
    kRtsPlayErrorPeerSetRemoteSDP,  // set remote sdp error
    kRtsPlayErrorNetworkInterrupt,
};

/**
 *@brief 停止播放原因.
*/
enum RTSStopReason {
    kRtsStopNormal = 0,
    kRtsStopError,
    kRtsStopTimeout,
};

/**
 *@brief 日志级别.
*/
enum RTSPlayEngineLogLevel {
    kRtsPlayLogLevelVerbose = 0,
    kRtsPlayLogLevelDebug,
    kRtsPlayLogLevelInfo,
    kRtsPlayLogLevelWarning,
    kRtsPlayLogLevelError,
    kRtsPlayLogLevelFatal,
};

/**
 *@brief 埋点级别.
*/
enum RTSPlayEngineTraceLevel {
    kRtsPlayTraceLevelVerbose = 0,
    kRtcPlayTraceLevelDebug,
    kRtsPlayTraceLevelInfo,
    kRtsPlayTraceLevelWarning,
    kRtsPlayTraceLevelError,
    kRtsPlayTraceLevelFatal,
};

/**
 *@brief RTS提供商.
*/
enum RTSVenderType {
    kRtsVenderTypeTencent = 0,
    kRtsVenderTypeAlibaba,
    kRtsVenderTypeByte,
    kRtsVenderTypeOther,
};

/**
 *@brief RTS 配置.
*/
struct RTSPlayEngineConfigure {
    RTSVenderType e_vendor_type = kRtsVenderTypeTencent;
    const char* play_uri;
    const char* session_id;
    bool enable_dtls;
    bool enable_hardware_decode;
    int jitter_buffer_ms;
    int jitter_buffer_max_ms;
    void* jvm;         /* JavaVM* for andriod */
    void* app_context; /* jobject* for android */
};
enum RTSTraceType {
    kRtsStopEventTrace = 0,
    kRtsUnInitEventTrace,
};

/**
 *@brief RTS 状态统计信息.
*/
struct RTSPlayEngineStats {
    double audio_volume;
    uint32_t audio_rtt_ms;
    uint32_t audio_dec_sample_rate;
    double audio_fraction_lost;
    uint32_t audio_jitter_buffer_ms;
    uint32_t audio_nack_count;
    int32_t audio_packets_lost;
    uint32_t audio_packets_received;
    uint64_t audio_bytes_received;
    int32_t audio_recv_media_bps;
    uint32_t audio_render_stall_500;
    uint64_t audio_jitterbuffer_flushes;
    uint32_t video_frame_height;
    uint32_t video_frame_width;
    uint32_t video_fps;                 //video_framerate_render
    uint32_t video_rtt_ms;
    double video_fraction_lost;
    uint32_t video_jitter_buffer_ms;
    uint32_t video_nack_count;
    int32_t video_packets_lost;
    uint32_t video_packets_received;
    uint64_t video_bytes_received;
    uint32_t video_recv_media_bps;
    int32_t video_recv_retransmit_bps;
    int32_t video_framerate_recv;
    uint32_t video_framerate_decoder_input;
    uint32_t video_framerate_decoder_output;
    char video_codec_name[CONTENT_MIN_SIZE];
    char video_codec_impl_name[CONTENT_MIN_SIZE];
    double video_jitter;
    uint32_t video_pli_count;
    uint32_t video_fir_count;
    uint32_t video_render_stall_500;
    uint32_t video_dec_bps;
    uint32_t video_dec_cache_frames_num;
    uint32_t video_dec_elapse;

    uint32_t e2e_delay_ms;
    uint64_t concealment_event;
    char json_content[CONTENT_MAX_SIZE];
};

struct RTSPlayEngineTrace {
    RTSPlayEngineTraceLevel trace_level;
    char stats_tag[CONTENT_MIN_SIZE];
    char player_stats[CONTENT_MAX_SIZE];
};

enum RTS_AUDIO_FRAME_TYPE {
    FRAME_TYPE_PCM16 = 0,  ///< PCM 16bit little endian
};

/**
 *@brief RTS 音频帧
*/
struct RTSAudioFrame {
    RTS_AUDIO_FRAME_TYPE type;
    void* data;
    int32_t samples;
    int32_t channels;
    int32_t samplesPerSec;
    int64_t renderTimeMs;
};

enum RTS_VIDEO_FRAME_TYPE {
    // YUV image with i420 layout, also known as yuv420p
    kVideoPixelFormatI420,
};

struct RTSSEIBuffer {
    uint8_t* seiData;
    int32_t seiDataSize;
};

/**
 *@brief RTS 视频帧.
*/
struct RTSVideoFrame {
    RTS_VIDEO_FRAME_TYPE type;
    int32_t width;         ///< width of video frame
    int32_t height;        ///< height of video frame
    int32_t strideY;       ///< stride of Y data buffer
    int32_t strideU;       ///< stride of U data buffer
    int32_t strideV;       ///< stride of V data buffer
    const uint8_t* dataY;  ///< Y data buffer
    const uint8_t* dataU;  ///< U data buffer
    const uint8_t* dataV;  ///< V data buffer
    int32_t rotation;      ///< rotation of this frame (0, 90, 180, 270)
    int64_t renderTimestamp;
    int32_t seiBufferArraySize;
    RTSSEIBuffer seiBufferArray[SEI_BUFFER_MAX_SIZE];
};

}  // namespace bytertc
