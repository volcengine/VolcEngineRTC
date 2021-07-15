#pragma once

#ifdef WIN32
#define BYTEAUDIO_API __declspec(dllexport)
#else
#define BYTEAUDIO_API __attribute__((__visibility__("default")))
#endif

#include <stdint.h>

#include <string>
#include <vector>

namespace bae {

struct ByteAudioInputStreamReport {
    uint32_t down_stream_num = 0;
    // audio encode layer statistic
    bool enc_input_mute = false;
    double enc_input_audio_level = 0;
    double enc_input_duration = 0;
    double enc_input_energy = 0.0;

    uint32_t enc_input_sample_rate = 0;
    uint32_t enc_input_channel_num = 0;

    std::string enc_codec_name = "null";
    // std::vector<cricket::AudioCodec> current_codecs;
    uint32_t enc_sample_rate = 0;
    uint32_t enc_channel_num = 0;
    uint32_t enc_target_bitrate = 0;
    uint32_t enc_dtx_count = 0;
    uint32_t enc_frame_length;
    double enc_rtf = 0.0;
    double enc_inband_fec_rate = 0.0;
    int enc_inband_fec_lossrate = 0;

    // audio recoerd devices statistic
    std::string audio_layer;
    uint32_t record_sample_rate = 0;
    uint32_t record_channels = 0;
    double record_level = 0.0;
    double record_total_energy = 0.0;
    double record_total_duration = 0.0;
    std::string audio_device_mode = "";

    // audio pre-process statistic
    bool prep_aec_enable = false;
    uint32_t prep_aec_mode = 2;

    bool prep_ans_enable = false;
    uint32_t prep_ans_mode = 2;
    float prep_denoise_db = 0;

    bool prep_agc_enable = false;
    uint32_t prep_agc_mode = 0;
    float prep_agc_gain_db = 0;

    bool loudnorm_enable = false;

    double prep_echo_return_loss = 0.0;
    double prep_echo_return_loss_enhancement = 0.0;
    int32_t prep_echo_delay_ms = 0;
    int32_t prep_echo_delay_median_ms = 0;
    int32_t prep_echo_delay_standard_deviation_ms = 0;
    float prep_residual_echo_likelihood = 0;
    float prep_residual_echo_likelihood_max = 0;
    double prep_nonlinear_process_suppression = 0.0;

    // vad report
    bool prep_vad_enable = false;
    bool prep_vad_enable_process = false;
    int prep_vad_level = 0;
    double prep_vad_process_rate = 0;
    double prep_vad_process_power_rate = 0;

    double prep_aec_rtf = 0.0;
    double prep_ans_rtf = 0.0;
    double prep_agc_rtf = 0.0;
    double prep_vad_rtf = 0.0;
    double record_frame_rate = 0.0;
    double vocal_loudnorm_rtf = 0.0f;

    int prep_aec_input_level = 0;
    int prep_aec_output_level = 0;
    int prep_ans_output_level = 0;
    int prep_agc_output_level = 0;
    int vocal_loudnorm_input_level = 0;
    int vocal_loudnorm_output_level = 0;

    int record_volume = 0;
    int prep_channel_select = -1;

    float sceen_input_volume = 0.0;
    double sceen_input_level = 0.0;
    double sceen_input_total_energy = 0.0;
    double sceen_input_total_duration = 0.0;
};

struct ByteAudioOutputStreamReport {
    // audio decode statistic
    uint32_t dec_muted = 0;
    std::string dec_codec_name = "null";
    uint32_t dec_sample_rate = 0;
    uint32_t dec_channels = 0;
    uint32_t dec_frame_length = 0;
    double dec_duration = 0;
    uint32_t dec_samples_out = 0;
    // std::vector<cricket::AudioCodec> current_codecs;

    float accelerate_rate = 0.0f;
    float preemptive_expand_rate = 0.0f;
    float expand_rate = 0.0f;
    float speech_expand_rate = 0.0f;
    // uint64_t lated_packet_samples = 0;
    int32_t decoding_normal_count = 0;
    int32_t decoding_plc_count = 0;
    int32_t decoding_cng_count = 0;
    int32_t decoding_plc_cng_count = 0;
    int32_t decoding_inbandfec_count = 0;

    uint64_t concealed_samples = 0;
    uint64_t concealment_event = 0;
    uint64_t recv_total_samples = 0;
    double recv_audio_level = 0;
    double recv_audio_total_energy = 0.0f;
    double recv_audio_total_duration = 0.0f;
    double decoding_rtf = 0.0;
    uint32_t dec_dtx_count = 0;
    uint32_t nico_dec_1stream_cnt = 0;
    uint32_t nico_dec_2stream_cnt = 0;

    // audio play devices statistic
    std::string audio_layer;
    uint32_t play_sample_rate = 0;
    uint32_t play_channels = 0;
    double play_level = 0.0;
    double play_total_energy = 0.0;
    double play_total_duration = 0.0;

    // audio post-process statistic
    bool post_enable_eq = false;
    bool post_enable_drc = false;
    uint32_t post_sample_rate = 0;
    uint32_t post_channel_num = 0;
    int post_play_gain = 100;

    double play_frame_rate = 0.0;
    int playback_volume = 0;
};

}  // namespace bae
