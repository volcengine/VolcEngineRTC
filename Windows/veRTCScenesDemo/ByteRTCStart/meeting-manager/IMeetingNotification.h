#pragma once
#include <string>
#include "BDMisc.h"

struct User {
    std::string uid; // user ID
    std::string user_name; // user ID
    std::string user_uniform_id;
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

struct VerifySms {
    std::string user_id;
    BDString user_name;
    std::string login_token;
    int64_t create_at = 0;
};

struct RecordInfo {
    std::string room_id;
    std::string url; // Conference recording download address
    std::string vid;
    bool video_holder = false;
    int64_t meeting_start_time; // UTC/GMT meeting start time
};

struct AuditState {
    std::string url;
    bool state;
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
    virtual void onUserMicStateChange(const std::string& userId, bool on) {};

    /*
    * User's camera status changes. Triggered by user turning camera on / off
    * @param userId: user ID
    * @param on: camera status, true: camera on£¬false: camera off
    */
    virtual void onUserCameraStateChange(const std::string& userId, bool on) {};

    /*
    * Host change event. 1. Triggered by host change request; 2. Triggered by the host leaving the meeting
    * @param formerHostId: last host ID
    * @param hostId: new host ID
    */
    virtual void onHostChange(const std::string& formerHostId, const std::string& hostId) {};

    /*
    * User join meeting event
    * @param userId: user ID
    */
    virtual void onUserJoinMeeting(const User& userId) {};

    /*
    * User leaving conference event
    * @param userId: user ID
    */
    virtual void onUserLeaveMeeting(const std::string& userId) {};

    /*
    * Screen share status change event. Triggered by user start / stop screen sharing
    * @param userId: Screen sharer ID
    * @param state: Status of screen sharing. True: turn on screen sharing, false: turn off screen sharing
    */
    virtual void onScreenShareStateChanged(const std::string& userId, bool state) {};

    /*
    * The meeting began recording. Triggered by the host recording the meeting
    */
    virtual void onStartMeetingRecord() {};

    /*
    * Notice of the end of the plenary session. Triggered by the moderator
    */
    virtual void onMeetingClose() {};

    /*
    * All silent. Triggered by the moderator
    */
    virtual void onMuteAllMic() {};

    /*
    * Silent specific user. Triggered by the moderator
    */
    virtual void onMuteUser(const std::string& userId) {};

    /*
    * Ask the user to turn on microphone event.
    * Triggered when the host requests to turn on the microphone£¬Only target user is notified
    * @param userId user ID
    */
    virtual void onAskingMicOn(const std::string& userId) {};

    /*
    * Ask the user to turn on camera event.
    * Triggered when the host requests to turn on the camera£¬Only target user is notified
    * @param userId user ID
    */
    virtual void onAskingCameraOn(const std::string& userId) {};

    /*
    * Users are kicked off the line
    */
    virtual void onUserKickedOff() {};
    /*
    * Websocket connection success events
    */
    virtual void onWebsocketConnected() {};
    /*
    * Websocket reconnecting event
    */
    virtual void onWebsocketConnecting() {};

    virtual void onInvaildToken(int code) {};
};