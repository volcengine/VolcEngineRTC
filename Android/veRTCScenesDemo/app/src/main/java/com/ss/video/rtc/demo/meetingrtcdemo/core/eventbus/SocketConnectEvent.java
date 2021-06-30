package com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus;

public class SocketConnectEvent {
    public ConnectStatus status;

    public SocketConnectEvent(ConnectStatus status) {
        this.status = status;
    }

    public enum ConnectStatus {
        CONNECTED,
        CONNECTING,
        RECONNECTED,
        DISCONNECTED
    }
}
