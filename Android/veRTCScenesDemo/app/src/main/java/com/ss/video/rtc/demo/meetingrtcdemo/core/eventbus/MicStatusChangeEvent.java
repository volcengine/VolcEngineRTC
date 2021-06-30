package com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus;

public class MicStatusChangeEvent {
    public String uid;
    public boolean status;

    public MicStatusChangeEvent(String uid, boolean status) {
        this.uid = uid;
        this.status = status;
    }
}
