package com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus;

import org.greenrobot.eventbus.EventBus;

public class MeetingEventManager {

    private static final EventBus sInstance;

    static {
        sInstance = EventBus.getDefault();
    }

    public static void post(Object object) {
        sInstance.post(object);
    }

    public static void register(Object object) {
        sInstance.register(object);
    }

    public static void unregister(Object object) {
        sInstance.unregister(object);
    }
}
