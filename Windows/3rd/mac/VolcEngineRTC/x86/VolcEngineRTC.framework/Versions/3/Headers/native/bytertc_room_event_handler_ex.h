/*
 * Copyright (c) 2020 The VolcEngineRTC project authors. All Rights Reserved.
 * @brief VolcEngineRTC Event Handler Lite
*/

#pragma once

#include "rtc/bytertc_defines.h"
#include "rtc/bytertc_video_defines_ex.h"
#include "bytertc_room_event_handler.h"

namespace bytertc {
/**
 * @locale zh
 * @type callback
 * @brief IRTCRoomEventHandlerEx Class<br>
 * 注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。
 */
class IRTCRoomEventHandlerEx {
public:
    /**
     * @locale zh
     * @hidden constructor/destructor
     */
    virtual ~IRTCRoomEventHandlerEx() {}
    /**
     * @locale zh
     * @type callback
     * @region 房间管理
     * @brief 房间内新增媒体流的回调。包含由摄像头/麦克风采集的媒体流或屏幕流。
     * @param stream_key 参看 RemoteStreamKey{@link #RemoteStreamKey}。
     * @param is_screen 是否是屏幕流。
     * @param type 远端媒体流的类型，参看 MediaStreamType{@link #MediaStreamType}。
     * @note 当房间内的远端用户调用 publishStream{@link #IRTCRoomEx#publishStream} 成功发布媒体流时，本地用户会收到该回调，此时本地用户可以自行选择是否调用 subscribeStream{@link #IRTCRoomEx#subscribeStream} 订阅此流。
     */
    virtual void onUserPublishStream(const RemoteStreamKey& stream_key, bool is_screen, MediaStreamType type) {
    }
    /**
     * @locale zh
     * @type callback
     * @region 房间管理
     * @brief 房间内媒体流移除的回调。包含由摄像头/麦克风采集的媒体流或屏幕流。
     * @param stream_key 参看 RemoteStreamKey{@link #RemoteStreamKey}。
     * @param type 移除的远端流类型，参看 MediaStreamType{@link #MediaStreamType}。  
     * @param reason 远端流移除的原因，参看 StreamRemoveReason{@link #StreamRemoveReason}。
     * @note 收到该回调通知后，你可以自行选择是否调用 unsubscribeStream{@link #IRTCRoomEx#unsubscribeStream} 取消订阅此流。
     */
    virtual void onUserUnpublishStream(
            const RemoteStreamKey& stream_key, MediaStreamType type, StreamRemoveReason reason) {
    }
    /**
     * @locale zh
     * @type callback
     * @region 房间管理
     * @brief 流状态改变回调，发生流相关的警告或错误时会收到此回调。
     * @param stream_key 参看 RemoteStreamKey{@link #RemoteStreamKey}。
     * @param state 流状态码，参看 ErrorCode{@link #ErrorCode} 及 WarningCode{@link #WarningCode}。
     * @param extra_info 附加信息，目前为空。
     */
    virtual void onStreamStateChanged(
            const StreamKey& stream_key, int state, const char* extra_info) {
    }

}; /* class IRTCRoomEventHandlerEx */

} /* namespace bytertc */