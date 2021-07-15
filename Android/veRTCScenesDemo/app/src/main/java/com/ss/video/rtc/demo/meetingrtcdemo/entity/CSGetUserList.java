package com.ss.video.rtc.demo.meetingrtcdemo.entity;

import java.util.List;

public class CSGetUserList {

    public List<MeetingUserInfo> users;

    public CSGetUserList(List<MeetingUserInfo> users) {
        this.users = users;
    }
}
