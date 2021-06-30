package com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus;

import com.ss.video.rtc.demo.meetingrtcdemo.entity.MeetingUserInfo;

public class UserJoinEvent {

    public MeetingUserInfo meetingUserInfo;

    public UserJoinEvent(MeetingUserInfo meetingUserInfo) {
        this.meetingUserInfo = meetingUserInfo;
    }
}
