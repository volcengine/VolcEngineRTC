package com.ss.video.rtc.demo.meetingrtcdemo.entity;

public class MeetingRoomInfo {
    public String room_id; // meeting's id
    public String host_id; // host's id
    public String screen_shared_uid; // user's id who is sharing screen
    public boolean record; // whether meeting is recording
    public long created_at; // timestamp when meeting created
    public long now;

    @Override
    public String toString() {
        return "MeetingRoomInfo{" +
                "room_id='" + room_id + '\'' +
                ", host_id='" + host_id + '\'' +
                ", screen_shared_uid='" + screen_shared_uid + '\'' +
                ", record='" + record + '\'' +
                ", created_at=" + created_at +
                ", now=" + now +
                '}';
    }
}