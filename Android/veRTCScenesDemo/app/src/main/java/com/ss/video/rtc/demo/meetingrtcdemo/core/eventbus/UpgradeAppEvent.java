package com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus;

import com.ss.video.rtc.demo.meetingrtcdemo.entity.AuditStateResult;

public class UpgradeAppEvent {
    public AuditStateResult result;

    public UpgradeAppEvent(AuditStateResult result) {
        this.result = result;
    }
}
