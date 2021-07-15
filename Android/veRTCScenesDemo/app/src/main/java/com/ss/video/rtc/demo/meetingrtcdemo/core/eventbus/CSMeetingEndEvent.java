package com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus;

public class CSMeetingEndEvent {
    public String roomId;

    public CSMeetingEndEvent(String roomId) {
        this.roomId = roomId;
    }
}
