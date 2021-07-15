package com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus;

import com.ss.video.rtc.engine.handler.IRtcEngineEventHandler;

public class RTCVolumeEvent {
    public IRtcEngineEventHandler.AudioVolumeInfo[] speakers;
    public int totalVolume;

    public RTCVolumeEvent(IRtcEngineEventHandler.AudioVolumeInfo[] speakers, int totalVolume) {
        this.speakers = speakers;
        this.totalVolume = totalVolume;
    }
}
