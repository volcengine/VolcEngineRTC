package com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus;

import com.ss.video.rtc.demo.meetingrtcdemo.entity.MeetingUserInfo;

public class UserLeaveEvent {

    public MeetingUserInfo meetingUserInfo;

    public UserLeaveEvent(MeetingUserInfo meetingUserInfo) {
        this.meetingUserInfo = meetingUserInfo;
    }
}
