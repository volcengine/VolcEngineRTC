package com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus;

public class RefreshUserNameEvent {
    public boolean isSuccess;
    public String userName;
    public String errorMsg;

    public RefreshUserNameEvent(String userName, boolean isSuccess) {
        this.userName = userName;
        this.isSuccess = isSuccess;
    }
}
