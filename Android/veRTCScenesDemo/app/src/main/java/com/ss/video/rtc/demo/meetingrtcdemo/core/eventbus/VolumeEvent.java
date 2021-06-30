package com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus;

import java.util.Map;

public class VolumeEvent {
    public Map<String, Integer> uidVolumeMap;

    public VolumeEvent(Map<String, Integer> uidVolumeMap) {
        this.uidVolumeMap = uidVolumeMap;
    }
}
