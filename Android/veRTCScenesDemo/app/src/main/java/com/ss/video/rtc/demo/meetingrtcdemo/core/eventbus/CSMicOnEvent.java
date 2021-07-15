package com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus;

import com.ss.video.rtc.demo.meetingrtcdemo.entity.MeetingUserInfo;

public class CSMicOnEvent {
    public MeetingUserInfo user;

    public CSMicOnEvent(MeetingUserInfo user) {
        this.user = user;
    }
}
