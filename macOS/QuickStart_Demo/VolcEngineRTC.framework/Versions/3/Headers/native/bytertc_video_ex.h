/*
 * Copyright (c) 2020 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC Interface Lite
 */

#pragma once

#include "bytertc_video.h"
#include "rtc/bytertc_defines.h"
#include "rtc/bytertc_video_defines_ex.h"
#include "bytertc_video_event_handler_ex.h"

namespace bytertc {

class IRTCRoomEx;
class IVideoSource;
class IPublisher;

class IRTCVideoEx : public IRTCVideo {
public:
    virtual IRTCRoomEx* createRTCRoomEx(const char* room_id) = 0;

    virtual int setVideoSource(StreamIndex stream_index, const VideoSourceConfig& config) = 0;
    virtual int pushExternalVideoFrame(StreamIndex stream_index, IVideoFrame* frame) = 0;
    virtual int setLocalStreamPriority(StreamIndex stream_index, StreamPriority priority) = 0;
    virtual int startVideoCapture(StreamIndex stream_index, const char device_id[MAX_DEVICE_ID_LENGTH]) = 0;
    virtual int stopVideoCapture(StreamIndex stream_index) = 0;
    virtual int setVideoCaptureConfig(StreamIndex stream_index, const VideoCaptureConfig& video_capture_config) = 0;

    virtual int setRemoteAudioPlaybackVolume(const StreamKey& stream_key, int volume) = 0;
    virtual int setCaptureVolume(int volume) = 0;
    virtual int setScreenCaptureVolume(int volume) = 0;
    virtual int setAudioSourceVolume(StreamIndex stream_index, int volume) = 0;
    virtual int setAudioContentType(StreamIndex stream_index, const AudioContentTypeConfig& config) = 0;
    virtual int setAudioEncodeConfig(StreamIndex stream_index, const AudioEncodeConfig& config) = 0;
};

BYTERTC_API bytertc::IRTCVideoEx* createRTCVideoEx(const char* app_id, bytertc::IRTCVideoEventHandler *event_handler, bytertc::IRTCVideoEventHandlerEx *event_handler_ex,
        const char* parameters);

BYTERTC_API void destroyRTCVideoEx();

}  // namespace bytertc