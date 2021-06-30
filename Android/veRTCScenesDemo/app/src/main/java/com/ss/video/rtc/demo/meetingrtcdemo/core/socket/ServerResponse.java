package com.ss.video.rtc.demo.meetingrtcdemo.core.socket;

import com.ss.video.rtc.demo.basic_module.utils.GsonUtils;

import org.json.JSONException;
import org.json.JSONObject;

import java.lang.reflect.Type;

public class ServerResponse<T> {

    private int code = -1;
    private String msg = "";
    private long timestamp = 0;
    private T data;

    public ServerResponse(Object originResponse, Class<T> clz) {
        if (originResponse instanceof JSONObject) {
            JSONObject resp = (JSONObject) originResponse;
            JSONObject response = null;
            try {
                code = resp.getInt("code");
                msg = resp.getString("message");
                timestamp = resp.getLong("timestamp");
                if (!JSONObject.NULL.equals(resp.get("response"))) {
                    response = resp.getJSONObject("response");
                    data = GsonUtils.gson().fromJson(response.toString(), clz);
                }
            } catch (JSONException e) {
                e.printStackTrace();
            }
        }
    }

    public ServerResponse(Object originResponse, Type type) {
        if (originResponse instanceof JSONObject) {
            JSONObject resp = (JSONObject) originResponse;
            String response;
            try {
                code = resp.getInt("code");
                msg = resp.getString("message");
                timestamp = resp.getLong("timestamp");
                Object respObj = resp.get("response");
                if (!JSONObject.NULL.equals(respObj)) {
                    response = resp.getString("response");
                    data = GsonUtils.gson().fromJson(response, type);
                }
            } catch (JSONException e) {
                e.printStackTrace();
            }
        }
    }

    public int getCode() {
        return code;
    }

    public String getMsg() {
        return msg;
    }

    public T getData() {
        return data;
    }

    public long getTimestamp() {
        return timestamp;
    }
}

