package com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus;

public class CSHostChangeEvent {
    public String formerHostId;
    public String hostId;

    public CSHostChangeEvent(String formerHostId, String hostId) {
        this.formerHostId = formerHostId;
        this.hostId = hostId;
    }
}
