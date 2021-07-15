package com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus;

import com.ss.video.rtc.demo.meetingrtcdemo.entity.MeetingUserInfo;

import java.util.List;

public class CSRefreshRaiseHandEvent {
    public List<MeetingUserInfo> users;

    public CSRefreshRaiseHandEvent(List<MeetingUserInfo> users) {
        this.users = users;
    }
}
