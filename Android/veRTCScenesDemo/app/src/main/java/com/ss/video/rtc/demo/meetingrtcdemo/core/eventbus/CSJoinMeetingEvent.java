package com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus;

import com.ss.video.rtc.demo.meetingrtcdemo.entity.MeetingUserInfo;

public class CSJoinMeetingEvent {

    public int errorCode;
    public MeetingUserInfo user;

    public CSJoinMeetingEvent(int errorCode, MeetingUserInfo user) {
        this.errorCode = errorCode;
        this.user = user;
    }
}
