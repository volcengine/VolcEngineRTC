package com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus;

public class CameraStatusChangedEvent {
    public String uid;
    public boolean status;

    public CameraStatusChangedEvent(String uid, boolean status) {
        this.uid = uid;
        this.status = status;
    }
}
