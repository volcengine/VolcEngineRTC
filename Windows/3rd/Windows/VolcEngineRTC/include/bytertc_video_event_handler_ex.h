/*
 * Copyright (c) 2020 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC Event Handler Lite
*/

#pragma once

#include "rtc/bytertc_defines.h"
#include "bytertc_video_event_handler.h"
#include "rtc/bytertc_video_defines_ex.h"
namespace bytertc {

class IRTCVideoEventHandlerEx {
public:
    /**
     * @hidden
     */
    virtual ~IRTCVideoEventHandlerEx() {
    }

    virtual void onAudioFrameSendStateChanged(
            const StreamKey& stream_key, const char* meta_data, FirstFrameSendState state) {
    }

    virtual void onVideoFrameSendStateChanged(
            const StreamKey& stream_key, const char* meta_data, FirstFrameSendState state) {
    }

    virtual void onAudioFramePlayStateChanged(
            const StreamKey& stream_key, const char* meta_data, FirstFramePlayState state) {
    }

    virtual void onVideoFramePlayStateChanged(
            const StreamKey& stream_key,  const char* meta_data, FirstFramePlayState state) {
    }

    virtual void onLocalStreamStats(StreamIndex index, const LocalStreamStats& stats) {
    }

    virtual void onRemoteStreamStats(const StreamKey& stream_key, const RemoteStreamStats& stats) {
    }

    virtual void onSimulcastSubscribeFallback(
            const StreamKey& stream_key, const RemoteStreamSwitch& event) {
    }

    virtual void onPerformanceAlarms(StreamIndex stream_index, bytertc::PerformanceAlarmMode mode,
            bytertc::PerformanceAlarmReason reason, const bytertc::SourceWantedData& data) {
    }
};
} /* namespace bytertc */