//
//  byte_rtc_engine_event_handler.h
//  bytertc
//
//  Created by xiewei on 2020/6/22.
//

#pragma once
#include "byte_rtc_engine_defines.h"
#include "byte_rtc_engine_lite_event_handler.h"
#include "byte_rtc_room_interface.h"

namespace bytertc {

/**
 *@type callback
 *@brief 音视频引擎事件回调接口。  <br>
 *       CreateByteRtcEngine{@link #CreateByteRtcEngine}  传入该回调实例。<br>
 * 详见 IRtcEngineLiteEventHandler{@link #IRtcEngineLiteEventHandler} 、IRTCRoomEventHandler{@link #IRTCRoomEventHandler}
 */
class IRtcEngineEventHandler : public IRtcEngineLiteEventHandler,
                               public IRTCRoomEventHandler {
public:
    /**
     * @hidden
     */
    virtual ~IRtcEngineEventHandler() {
    }
private:
     /**
      * @hidden
     */
    virtual void OnChannelWarning(int warn) override {
    }
     /**
      * @hidden
     */
    virtual void OnChannelError(int err) override {
    }
};
}
