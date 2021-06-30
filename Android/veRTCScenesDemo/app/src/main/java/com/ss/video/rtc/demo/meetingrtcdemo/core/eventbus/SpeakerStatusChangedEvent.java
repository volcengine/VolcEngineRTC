package com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus;

public class SpeakerStatusChangedEvent {

    public boolean isSpeaker;

    public SpeakerStatusChangedEvent(boolean isSpeaker) {
        this.isSpeaker = isSpeaker;
    }
}
