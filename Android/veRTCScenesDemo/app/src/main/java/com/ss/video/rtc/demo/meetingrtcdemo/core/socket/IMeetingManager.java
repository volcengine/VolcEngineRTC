package com.ss.video.rtc.demo.meetingrtcdemo.core.socket;

import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.RefreshUserNameEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.CreateJoinRoomResult;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.AuditStateResult;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.LoginInfo;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.MeetingRecordInfo;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.MeetingRoomInfo;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.MeetingTokenInfo;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.MeetingUserInfo;

import java.util.List;

/**
 * Interface between client and server.
 */
public interface IMeetingManager {

    /**
     * set up connection between client and server.
     *
     * @param host server url
     */
    void startConnect(String host);

    /**
     * disconnect the connection between client and server.
     */
    void disconnect();

    void reconnect();

    /**
     * Judge the status of connection between client and server.
     *
     * @return true:connected
     */
    boolean hasConnected();

    LoginInfo passwordFreeLogin(String userName);

    int verifyLoginToken(String token);

    /**
     * Get appId.
     *
     * @return AppId
     */
    String getAppId();

    /**
     * Change user name
     *
     * @param userName new user name
     */
    RefreshUserNameEvent changeUserName(String userName);

    /**
     * Request server to start a meeting or join a meeting.
     *
     * @param userName   user's name
     * @param roomId   meeting's id
     * @param micOn    status of local microphone
     * @param cameraOn status of local camera
     * @return the result.
     *      0:success
     *      -1:fail
     *      406:
     */
    MeetingTokenInfo joinMeeting(String userName, String roomId, boolean micOn, boolean cameraOn);

    /**
     * Notice server that local user is leaving meeting.
     */
    void leaveMeeting();

    /**
     * Notice server this local user has changed microphone status.
     *
     * @param on true:microphone on  false:microphone off
     */
    void toggleMicState(boolean on);

    /**
     * Notice server that local user has changed camera status.
     *
     * @param on true:camera on  false:camera off
     */
    void toggleCameraState(boolean on);

    /**
     * Get users' information in meeting.
     *
     * @return users' information list.See {@link MeetingUserInfo}
     */
    List<MeetingUserInfo> getMeetingParticipantsInfo();

    /**
     * Get single user information.
     *
     * @param userId user's id
     * @return user's information.See {@link MeetingUserInfo}
     */
    MeetingUserInfo getMeetingParticipantInfo(String userId);

    /***
     * Get meeting information.
     * @return meeting information.See {@link MeetingRoomInfo}
     */
    MeetingRoomInfo getMeetingInfo();

    /**
     * Change host of meeting.
     *
     * @param userId user's id of new host
     * @return th result.
     *      0:success
     *      -1:fail
     *      404:user has left meeting
     *      416:no authority
     */
    int changeHost(String userId);

    /**
     * Ask server to mute single user.
     *
     * @param userId user's id.
     */
    void muteUserMic(String userId);

    /**
     * Ask server to mute all users.
     */
    void muteAllUserMic();

    /**
     * Ask user to open microphone.
     *
     * @param userId user's id.
     */
    void askUserMicOn(String userId);

    /**
     * Ask user to open camera.
     *
     * @param userId user's id.
     */
    void askUserCameraOn(String userId);

    /**
     * Request server to close meeting.
     */
    void closeMeeting();

    /**
     * Notice server to start recording meeting.
     */
    void startScreenShare();

    /**
     * Notice server to stop recording meeting.
     */
    void stopScreenShare();

    /**
     * Request server to start recording meeting.
     * @param users id list of users who are showing.
     * @param screenUid id of user who is sharing screen.
     */
    void startMeetingRecord(List<String> users, String screenUid);

    /**
     * Notice server to start recording meeting.
     * @param users id list of users who are showing.
     * @param screenUid id of user who is sharing screen.
     */
    void updateRecordLayout(List<String> users, String screenUid);

    /**
     * Get meeting record from server。
     *
     * @return record info struct.See {@link MeetingRecordInfo}
     */
    List<MeetingRecordInfo> getHistoryMeetingRecord();

    CreateJoinRoomResult csReconnect();

    String csGetAppID();

    List<MeetingRoomInfo> csGetMeetings();

    CreateJoinRoomResult csCreateMeeting(String roomName, String userName);

    CreateJoinRoomResult csJoinMeeting(String roomId, String userName);

    void csLeaveMeeting();

    List<MeetingUserInfo> csGetRaiseHands();

    List<MeetingUserInfo> csGetAudiences();

    void csInviteMic(String userId);

    void csConfirmMic();

    void csRaiseHandsMic();

    void csAgreeMic(String userId);

    void csOffSelfMic();

    void csOffMic(String userId);

    void csMuteMic();

    void csUnmuteMic();

    /**
     * Delete meeting record which owner is me.
     *
     * @param vid video id.
     */
    void deleteHistoryMeetingRecord(String vid);

    AuditStateResult getAuditState(String deviceType, String appVersion);
}