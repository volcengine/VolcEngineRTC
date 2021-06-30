package com.ss.video.rtc.demo.meetingrtcdemo.entity;

import com.ss.video.rtc.demo.basic_module.utils.GsonUtils;

import org.json.JSONException;
import org.json.JSONObject;

public class MeetingBroadcast {
    public boolean status;
    public String user_id; // user's id
    public String room_id; // meeting's id
    public String host_id; // host's id
    public String former_host_id; // former host's id
    public long created_at; // UTC/GMT timestamp when meeting created
    public boolean is_host; // whether user is host
    public boolean is_sharing; // whether somebody is sharing screen
    public boolean is_mic_on;  // whether local microphone is on
    public boolean is_camera_on; // whether local camera is on

    public static MeetingBroadcast getBroadcast(Object originResp) {
        if (originResp instanceof JSONObject) {
            JSONObject resp = (JSONObject) originResp;
            String response;
            try {
                response = resp.getString("data");
                if (!JSONObject.NULL.equals(response)) {
                    return GsonUtils.gson().fromJson(response, MeetingBroadcast.class);
                } else {
                    return null;
                }
            } catch (JSONException e) {
                e.printStackTrace();
                return null;
            }
        } else {
            return null;
        }
    }
}