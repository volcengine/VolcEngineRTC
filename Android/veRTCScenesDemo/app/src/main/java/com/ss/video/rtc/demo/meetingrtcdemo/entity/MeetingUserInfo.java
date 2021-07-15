package com.ss.video.rtc.demo.meetingrtcdemo.entity;

import java.util.Objects;

public class MeetingUserInfo {
    public String user_id; // user's id
    public String user_name; // user's name
    public String user_uniform_name; // user's uniform name for sort
    public String room_id; // meeting's id
    public long created_at; // timestamp when meeting created
    public boolean is_host; // whether user is host
    public boolean is_sharing; // whether somebody is sharing screen
    public boolean is_mic_on;  // whether local microphone is on
    public boolean is_camera_on; // whether local camera is on
    public int volume; //volume value
    public int user_status;

    @Override
    public String toString() {
        return "MeetingUserInfo{" +
                "user_id='" + user_id + '\'' +
                ", user_name='" + user_name + '\'' +
                ", user_uniform_name='" + user_uniform_name + '\'' +
                ", room_id='" + room_id + '\'' +
                ", created_at=" + created_at +
                ", is_host=" + is_host +
                ", is_sharing=" + is_sharing +
                ", is_mic_on=" + is_mic_on +
                ", is_camera_on=" + is_camera_on +
                ", volume=" + volume +
                ", user_status=" + user_status +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        MeetingUserInfo info = (MeetingUserInfo) o;
        return Objects.equals(user_id, info.user_id);
    }

    @Override
    public int hashCode() {
        return Objects.hash(user_id);
    }

    public MeetingUserInfo deepCopy(MeetingUserInfo info) {
        info.user_id = user_id;
        info.room_id = room_id;
        info.created_at = created_at;
        info.is_host = is_host;
        info.is_sharing = is_sharing;
        info.is_mic_on = is_mic_on;
        info.is_camera_on = is_camera_on;
        info.volume = volume;
        return info;
    }
}
