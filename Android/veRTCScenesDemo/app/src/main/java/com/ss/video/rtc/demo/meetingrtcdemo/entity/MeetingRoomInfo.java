package com.ss.video.rtc.demo.meetingrtcdemo.entity;

public class MeetingRoomInfo {
    public String room_id; // meeting's id
    public String room_name; // meeting's name
    public String host_id; // host's id
    public String host_name; // host's name
    public String screen_shared_uid; // user's id who is sharing screen
    public boolean record; // whether meeting is recording
    public long created_at; // timestamp when meeting created
    public long now;
    public int user_counts;
    public int micon_counts;

    @Override
    public String toString() {
        return "MeetingRoomInfo{" +
                "room_id='" + room_id + '\'' +
                ", room_name='" + room_name + '\'' +
                ", host_id='" + host_id + '\'' +
                ", host_name='" + host_name + '\'' +
                ", screen_shared_uid='" + screen_shared_uid + '\'' +
                ", record=" + record +
                ", created_at=" + created_at +
                ", now=" + now +
                ", user_counts=" + user_counts +
                ", micon_counts=" + micon_counts +
                '}';
    }
}