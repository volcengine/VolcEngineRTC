package com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus;

import com.ss.video.rtc.demo.meetingrtcdemo.entity.MeetingUserInfo;

public class CSLeaveMeetingEvent {
    public MeetingUserInfo user;

    public CSLeaveMeetingEvent(MeetingUserInfo user) {
        this.user = user;
    }
}
