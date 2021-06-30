package com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus;

public class HostChangedEvent {

    public String formerUid;
    public String currentUid;

    public HostChangedEvent(String formerUid, String currentUid) {
        this.formerUid = formerUid;
        this.currentUid = currentUid;
    }
}
