#pragma once
#include <string>

struct User {
    std::string uid; // user ID
    int64_t time_of_joining; // UTC/GMT join meeting time
    bool is_host; // Host or not
    bool is_screen_shared; // shared screen or not
    bool is_mic_on;  // microphone on or not
    bool is_camera_on; // camera on or not
};

struct Room {
    std::string room_id; // rom ID
    std::string host_uid; // host ID
    std::string screen_shared_uid; // screen sharer ID
    bool is_recording = false; // recording on or not
    int64_t meeting_start_time; // UTC/GMT, meeting start time
    int64_t now;  // UTC/GMT current time
};

struct TokenInfo {
    std::string user_id; // user ID
    std::string room_id; // room ID
    std::string token; // meeting token
    std::string app_id; // app ID
};

struct RecordInfo {
    std::string room_id;
    std::string url; // Conference recording download address
    int64_t meeting_start_time; // UTC/GMT meeting start time
};

// Broadcast messages except for microphone on and camera notification
class IMeetingNotification {

public:
    /*
    * User microphone status changes.
    * 1. triggered by the user's request to turn on / off the microphone;
    * 2. triggered by the host mute single user
    * @param userId: user ID
    * @param on: microphone status, true: microphone on£¬false: microphone off
    */
    virtual void onUserMicStateChange(const std::string& userId, bool on) = 0;

    /*
    * User's camera status changes. Triggered by user turning camera on / off
    * @param userId: user ID
    * @param on: camera status, true: camera on£¬false: camera off
    */
    virtual void onUserCameraStateChange(const std::string& userId, bool on) = 0;

    /*
    * Host change event. 1. Triggered by host change request; 2. Triggered by the host leaving the meeting
    * @param formerHostId: last host ID
    * @param hostId: new host ID
    */
    virtual void onHostChange(const std::string& formerHostId, const std::string& hostId) = 0;

    /*
    * User join meeting event
    * @param userId: user ID
    */
    virtual void onUserJoinMeeting(const User& userId) = 0;

    /*
    * User leaving conference event
    * @param userId: user ID
    */
    virtual void onUserLeaveMeeting(const std::string& userId) = 0;

    /*
    * Screen share status change event. Triggered by user start / stop screen sharing
    * @param userId: Screen sharer ID
    * @param state: Status of screen sharing. True: turn on screen sharing, false: turn off screen sharing
    */
    virtual void onScreenShareStateChanged(const std::string& userId, bool state) = 0;

    /*
    * The meeting began recording. Triggered by the host recording the meeting
    */
    virtual void onStartMeetingRecord() = 0;

    /*
    * Notice of the end of the plenary session. Triggered by the moderator
    */
    virtual void onMeetingClose() = 0;

    /*
    * All silent. Triggered by the moderator
    */
    virtual void onMuteAllMic() = 0;

    /*
    * Silent specific user. Triggered by the moderator
    */
    virtual void onMuteUser(const std::string& userId) = 0;

    /*
    * Ask the user to turn on microphone event.
    * Triggered when the host requests to turn on the microphone£¬Only target user is notified
    * @param userId user ID
    */
    virtual void onAskingMicOn(const std::string& userId) = 0;

    /*
    * Ask the user to turn on camera event.
    * Triggered when the host requests to turn on the camera£¬Only target user is notified
    * @param userId user ID
    */
    virtual void onAskingCameraOn(const std::string& userId) = 0;

    /*
    * Users are kicked off the line
    */
    virtual void onUserKickedOff() = 0;
    /*
    * Websocket connection success events
    */
    virtual void onWebsocketConnected() = 0;
    /*
    * Websocket reconnecting event
    */
    virtual void onWebsocketConnecting() = 0;
};