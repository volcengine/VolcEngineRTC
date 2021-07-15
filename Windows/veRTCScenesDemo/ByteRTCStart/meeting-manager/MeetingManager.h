#pragma once
#include <string>
#include <list>
#include <memory>
#include "IMeetingNotification.h"
#include "connection_manager.h"

class MeetingManager{

public:
    static MeetingManager* GetInstance();

    void registerNotification(IMeetingNotification* notification);
    /**
    * Start connecting to the conference control server,{@link IMeetingNotification} callback onConnectSuccess¡¢onConnectError events
    */
    void startConnect();

    /**
    * Disconnect conference control server{@link IMeetingNotification} callback onDisconnect event
    */
    void disconnect();

    /**
    * Get Application ID
    * @return error code and Application ID
    */
    void getAppId(std::function<void(int, const std::string&)> callback);

    /**
    * Join / create meeting, The creator defaults to the host
    * @param userId: user ID
    * @param roomId: room ID
    * @param micOn: microphone on or not,true: microphone on  false: icrophone off
    * @param cameraOn: camera on or not, true: camera on  false: camera off
    * @return error code and token
    */
    void joinMeeting(const std::string& userName,
        const std::string& userId,
        const std::string& roomId,
        bool micOn,
        bool cameraOn,
        std::function<void(int, const std::string&)> callback);

    /**
    * Leave the meeting, Participants call
    * @return error code
    */
    void leaveMeeting(std::function<void(int)> callback);
    /**
    * User reconnection
    * @return error code
    */
    void userReconnect(std::function<void(int)> callback);

    /*
    * Microphone status switch
    * @param on: true: Microphone on£¬false: Microphone off
    * @return error code
    */
    void toggleMicState(bool on, std::function<void(int)> callback);

    /*
    * Camera status switch
    * @param on: true: Camera on£¬false: Camera off
    * @return error code
    */
    void toggleCameraState(bool on, std::function<void(int)> callback);

    /*
    * Get the list of participants
    * @return error code and list of participants, See structure description {@link User}
    */
    void getMeetingParticipantsInfo(std::function<void(int code, const std::list<User>&)> callback);

    /*
    * Get specific participant information
    * @return error code and participant information, See structure description {@link User}
    */
    void getMeetingParticipantInfo(const std::string& userId, std::function<void(int code, const User&)> callback);

    /*
    * Get conference information
    * @return  error code and conference information, See structure description {@link Room}
    */
    void getMeetingInfo(std::function<void(int, const Room&)> callback);

    /*
    * Change the host, Host moves host or automatically assign the moderator after the moderator exits the meeting
    * @param userId: new host ID
    * @return error code, 0: success, - 1: failure, 404: the user has left the conference, 416: no operation permission
    */
    int changeHost(const std::string& userId, std::function<void(int)> callback);

    /*
    * Mute specific user
    * @param userId: user ID
    * @return error code
    */
    void muteUserMic(const std::string& userId, std::function<void(int)> callback);

    /*
    * Silence all users
    * @return error code
    */
    void muteAllUserMic(std::function<void(int)> callback);

    /*
    * Request user to turn on microphone
    * @param userId: user ID
    * @return error code
    */
    void askUserMacOn(const std::string& userId, std::function<void(int)> callback);

    /*
    * Request the user to turn on the camera
    * @param userId: user ID
    * @return error code
    */
    void askUserCameraOn(const std::string& userId, std::function<void(int)> callback);

    /*
    * close meeting, Only the moderator has permission to operate
    * @return error code
    */
    void closeMeeting(std::function<void(int)> callback);

    /*
    * Start screen sharing
    * @return error code
    */
    void startScreenShare(std::function<void(int)> callback);

    /*
    * Stop screen sharing
    * @return error code
    */
    void stopScreenShare(std::function<void(int)> callback);

    /*
    * Start recording meeting
    * @return error code
    */
    void startMeetingRecord(const std::vector<std::string>& users, const std::string& screen_uid, std::function<void(int)> callback);

    /*
    * Update recording layout
    * @return error code
    */
    void updateRecordLayout(const std::vector<std::string>& users, const std::string& screen_uid, std::function<void(int)> callback);

    /*
    * Get the download address information of historical videos
    * @return error code and video download address list, See structure description {@link RecordInfo}
    */
    void getHistoryMeetingRecord(std::function<void(int code, const std::list<RecordInfo>&)> callback);

    void deleteVideoRecord(const std::string& vid, std::function<void(int)> callback);

    void getAuditState(const std::string& version, std::function<void(int, const AuditState&)> callback);

    void passwordFreeLogin(const std::string& user_name, std::function<void(int, const VerifySms&)> callback);

    void changeUserName(const std::string& nickname, std::function<void(int)> callback);

    void verifyLoginToken(const std::string& token, std::function<void(int)> callback);

    void setMeetingToken(const std::string& token) {
        m_token = token;
    }

private:
    MeetingManager();
    ~MeetingManager();
    void getMeetingParticipantsInfoInternal(const std::string& userId, std::function<void(int, const std::list<User>&)> callback);

protected:
    /*
    * Register all conference callback events
    */
    void registerEevent();

    void onInvalidToken(int code);

    void onWebsocketConnected();

    void onWebsocketConnecting();

    /*
    * User microphone status change event
    */
    void onUserMicStateChange(const Json::Value& response);

    /*
    * User camera status change event
    */
    void onUserCameraStateChange(const Json::Value& response);

    /*
    * Host change event
    */
    void onHostChange(const Json::Value& response);

    /*
    * User join meeting event
    */
    void onUserJoinMeeting(const Json::Value& response);

    /*
    * User leaving conference event
    */
    void onUserLeaveMeeting(const Json::Value& response);

    /*
    * Screen sharing state change event
    */
    void onScreenShareStateChanged(const Json::Value& response);

    /*
    * The meeting started recording the event. Triggered when the moderator records the meeting
    */
    void onStartMeetingRecord(const Json::Value& response);

    /*
    * Meeting closing event, Triggered when the moderator ends the meeting
    */
    void onMeetingClose(const Json::Value& response);

    /*
    * All silent event. Trigger when the host silences all users
    */
    void onMuteAllMic(const Json::Value& response);

    /*
    * Mute specific user. Triggered when the host silences a specific user
    */
    void onMuteUser(const Json::Value& response);

    /*
    * Request user to turn on microphone event
    */
    void onAskingMicOn(const Json::Value& response);

    /*
    * Request user to turn on camera event
    */
    void onAskingCameraOn(const Json::Value& response);

    /*
    * Users are kicked off the line
    */
    void onUserKickedOff(const Json::Value& response);

protected:
    std::vector<IMeetingNotification*> m_notifications;
    std::unique_ptr<ConnectionManager> m_connectionManager = nullptr;
    std::string m_appId;
    std::string m_room_id;
    std::string m_user_id;
    std::string m_token;
};