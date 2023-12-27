/*
 * Copyright (c) 2020 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC Interface Lite
 */

#pragma once

#include "bytertc_room.h"

namespace bytertc {

class IRTCRoomEventHandlerEx;

class IRTCRoomEx : public IRTCRoom {
public:
    virtual int publishStream(StreamIndex stream_index, MediaStreamType type) = 0;
    virtual int unpublishStream(StreamIndex stream_index, MediaStreamType type) = 0;
    virtual int subscribeStream(const char *user_id, StreamIndex stream_index, MediaStreamType type) = 0;
    virtual int unsubscribeStream(const char *user_id, StreamIndex stream_index, MediaStreamType type) = 0;
    virtual int setRTCRoomEventHandlerEx(IRTCRoomEventHandlerEx* room_event_handler) = 0;
};

}  // namespace bytertc