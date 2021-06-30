package com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus;

public class ShareScreenEvent {
    public boolean isStart;
    public String shareUid;

    public ShareScreenEvent(boolean isStart, String shareUid) {
        this.isStart = isStart;
        this.shareUid = shareUid;
    }
}
