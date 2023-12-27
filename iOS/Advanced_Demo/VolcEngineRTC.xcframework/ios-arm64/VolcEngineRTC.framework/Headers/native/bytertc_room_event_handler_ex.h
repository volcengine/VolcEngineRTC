/*
 * Copyright (c) 2020 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC Event Handler Lite
*/

#pragma once

#include "rtc/bytertc_defines.h"
#include "rtc/bytertc_video_defines_ex.h"
#include "bytertc_room_event_handler.h"

namespace bytertc {

class IRTCRoomEventHandlerEx {
public:
    virtual ~IRTCRoomEventHandlerEx() {}

    virtual void onUserPublishStream(const RemoteStreamKey& stream_key, bool is_screen, MediaStreamType type) {
    }

    virtual void onUserUnpublishStream(
            const RemoteStreamKey& stream_key, MediaStreamType type, StreamRemoveReason reason) {
    }

    virtual void onStreamStateChanged(
            const StreamKey& stream_key, int state, const char* extra_info) {
    }

}; /* class IRTCRoomEventHandlerEx */

} /* namespace bytertc */