package com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus;

import com.ss.video.rtc.demo.meetingrtcdemo.entity.MeetingUserInfo;

import java.util.List;

public class CSRefreshListenerEvent {
    public List<MeetingUserInfo> users;

    public CSRefreshListenerEvent(List<MeetingUserInfo> users) {
        this.users = users;
    }
}
