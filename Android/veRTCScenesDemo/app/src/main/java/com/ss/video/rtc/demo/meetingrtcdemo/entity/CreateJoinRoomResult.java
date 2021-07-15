package com.ss.video.rtc.demo.meetingrtcdemo.entity;

import java.util.List;

public class CreateJoinRoomResult {
    public String token;
    public MeetingRoomInfo info;
    public List<MeetingUserInfo> users;

    @Override
    public String toString() {
        return "CreateJoinRoomResult{" +
                "token='" + token + '\'' +
                ", info=" + info +
                ", users=" + users +
                '}';
    }
}
