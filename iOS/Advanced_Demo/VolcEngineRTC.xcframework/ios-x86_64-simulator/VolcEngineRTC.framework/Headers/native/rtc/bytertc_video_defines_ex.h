//  bytertc_video_defines_ex.h
//  ByteRTC

#pragma once
namespace bytertc {

enum VideoContentCategory {
    /**
     * @hidden for internal use only
     */
    kVideoContentCategoryCamera = 0, // 相机
    /**
     * @hidden for internal use only
     */
    kVideoContentCategoryScreen = 1, // 屏幕共享
};

struct VideoSourceConfig {
    /**
     * @hidden for internal use only
     */
    VideoSourceType source_type = kVideoSourceTypeExternal;
    /**
     * @hidden for internal use only
     */
    VideoContentCategory content_category = kVideoContentCategoryCamera;
};

struct AudioContentTypeConfig {
    /**
     * @hidden for internal use only
     */
    bool has_mic = true;
    /**
     * @hidden for internal use only
     */
    bool has_screen_audio = false;
    /**
     * @hidden for internal use only
     */
    bool has_media_player = false;
};

struct AudioEncodeConfig {
    /**
     * @hidden for internal use only
     */
    int codec_type = -1;
    /**
     * @hidden for internal use only
     */
    int enc_mode = -1;
    /**
     * @hidden for internal use only
     */
    int channel_num = -1;
    /**
     * @hidden for internal use only
     */
    int enc_bitrate = -1;
    /**
     * @hidden for internal use only
     */
    int use_dtx = -1;
    /**
     * @hidden for internal use only
     */
    int use_inbandfec = -1;
    /**
     * @hidden for internal use only
     */
    int sample_rate = -1;
    /**
     * @hidden for internal use only
     */
    int packet_size = -1;
};

enum StreamPriority {
    /**
     * @hidden for internal use only
     */
    kStreamPriorityLow = 0,
    /**
     * @hidden for internal use only
     */
    kStreamPriorityNormal = 1,
    /**
     * @hidden for internal use only
     */
    kStreamPriorityHigh = 2,
};

struct StreamKey {
    /**
     * @hidden for internal use only
     */
    const char* room_id;
    /**
     * @hidden for internal use only
     */
    const char* user_id;
    /**
     * @hidden for internal use only
     */
    StreamIndex stream_index;
};

}