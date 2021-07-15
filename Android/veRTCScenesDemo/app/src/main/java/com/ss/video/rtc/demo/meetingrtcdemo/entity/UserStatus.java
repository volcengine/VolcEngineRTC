package com.ss.video.rtc.demo.meetingrtcdemo.entity;

public enum UserStatus {
    UserStatusAudience(0),
    UserStatusRaiseHands(1),
    UserStatusOnMicrophone(2);

    private int value;

    UserStatus(int value) {
        this.value = value;
    }

    public int getStatus() {
        return value;
    }
}
