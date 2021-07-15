package com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus;

import com.ss.video.rtc.demo.meetingrtcdemo.entity.MeetingRoomInfo;

import java.util.List;

public class CSRefreshMeetingsEvent {

    public List<MeetingRoomInfo> meetings;

    public CSRefreshMeetingsEvent(List<MeetingRoomInfo> meetings) {
        this.meetings = meetings;
    }
}
