package com.ss.video.rtc.demo.meetingrtcdemo.voicechat;

import android.text.TextUtils;

import com.ss.video.rtc.demo.basic_module.utils.AppExecutors;
import com.ss.video.rtc.demo.meetingrtcdemo.core.MeetingDataManager;
import com.ss.video.rtc.demo.meetingrtcdemo.core.MeetingRTCManager;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.CSRefreshListenerEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.CSRefreshMeetingsEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.CSRefreshRaiseHandEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.MeetingEventManager;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.SocketConnectEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.socket.IMeetingManager;
import com.ss.video.rtc.demo.meetingrtcdemo.core.socket.MeetingSocketIOManager;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.CreateJoinRoomResult;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.MeetingRoomInfo;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.MeetingUserInfo;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.UserStatus;
import com.ss.video.rtc.demo.meetingrtcdemo.resource.Constants;

import org.greenrobot.eventbus.Subscribe;
import org.greenrobot.eventbus.ThreadMode;

import java.util.LinkedList;
import java.util.List;

public class VoiceChatDataManger {

    private static final String sServerHost = "https://rtcio.bytedance.com:443";

    private static IMeetingManager sInstance;

    private static String sAppId = "";
    private static boolean sMicStatus = false;
    private static boolean sIsRequestAppId = false;

    private static VoiceChatDataManger sVoiceInstance = null;
    public static CreateJoinRoomResult sCreateRoomResult = null;
    public static boolean sIsDialogShowing = false;

    private static SocketConnectEvent.ConnectStatus sConnectStatus = SocketConnectEvent.ConnectStatus.DISCONNECTED;

    private static final List<MeetingUserInfo> sUserList = new LinkedList<>();

    public static void init() {
        sInstance = getManager();
        sUserList.clear();

        sVoiceInstance = new VoiceChatDataManger();
        MeetingEventManager.register(sVoiceInstance);
    }

    public static void release() {
        MeetingEventManager.unregister(sVoiceInstance);
        sVoiceInstance = null;
        sInstance.disconnect();
        sInstance = null;
    }

    public static IMeetingManager getManager() {
        if (sInstance == null) {
            synchronized (VoiceChatDataManger.class) {
                if (sInstance == null) {
                    sInstance = new MeetingSocketIOManager();
                    sInstance.startConnect(sServerHost);
                }
            }
        }
        return sInstance;
    }

    public static boolean isSelf(String uid) {
        return !TextUtils.isEmpty(uid) && TextUtils.equals(uid, getUid());
    }

    public static void requestChangeUserName(String userName) {

    }

    public static void setRoomInfo(CreateJoinRoomResult result) {
        sCreateRoomResult = result;
    }

    public static String getUid() {
        return MeetingDataManager.getDeviceId();
    }

    public static void requestCreateRoom(String roomName, String userName) {
        AppExecutors.networkIO().execute(() -> {
            CreateJoinRoomResult result = sInstance.csCreateMeeting(roomName, userName);
            sUserList.clear();
            if (result != null && result.info != null) {
                List<MeetingUserInfo> users = result.users;
                if (users != null) {
                    sUserList.addAll(users);
                }
                MeetingEventManager.post(result);
            } else {
                MeetingEventManager.post(new CreateJoinRoomResult());
            }
        });
    }

    public static void requestJoinRoom(String roomId, String userName) {
        AppExecutors.networkIO().execute(() -> {
            CreateJoinRoomResult result = sInstance.csJoinMeeting(roomId, userName);
            sUserList.clear();
            if (result != null && result.info != null) {
                List<MeetingUserInfo> users = result.users;
                if (users != null) {
                    sUserList.addAll(users);
                }
                MeetingEventManager.post(result);
            } else {
                MeetingEventManager.post(new CreateJoinRoomResult());
            }
        });
    }

    public static void requestLeaveRoom() {
        AppExecutors.networkIO().execute(() -> {
            sInstance.csLeaveMeeting();
        });
    }

    public static void requestRoomList() {
        AppExecutors.networkIO().execute(() -> {
            List<MeetingRoomInfo> meetings = sInstance.csGetMeetings();
            MeetingEventManager.post(new CSRefreshMeetingsEvent(meetings));
        });
    }

    public static void requestRaiseHandUserList() {
        AppExecutors.networkIO().execute(() -> {
            List<MeetingUserInfo> infos = sInstance.csGetRaiseHands();
            MeetingEventManager.post(new CSRefreshRaiseHandEvent(infos));
        });
    }

    public static void requestListenerUserList() {
        AppExecutors.networkIO().execute(() -> {
            List<MeetingUserInfo> infos = sInstance.csGetAudiences();
            MeetingEventManager.post(new CSRefreshListenerEvent(infos));
        });
    }

    public static void requestRaiseHand() {
        AppExecutors.networkIO().execute(() -> sInstance.csRaiseHandsMic());
    }

    public static void requestBecomeListener() {
        AppExecutors.networkIO().execute(() -> sInstance.csOffSelfMic());
    }

    public static void confirmBecomeSpeaker(){
        AppExecutors.networkIO().execute(() -> sInstance.csConfirmMic());
    }

    public static void onUserOption(MeetingUserInfo info) {
        if (info == null) {
            return;
        }
        AppExecutors.networkIO().execute(() -> {
            int status = info.user_status;
            if (status == UserStatus.UserStatusOnMicrophone.getStatus()) {
                sInstance.csOffMic(info.user_id);
            } else if (status == UserStatus.UserStatusRaiseHands.getStatus()) {
                sInstance.csAgreeMic(info.user_id);
            } else if (status == UserStatus.UserStatusAudience.getStatus()) {
                sInstance.csInviteMic(info.user_id);
            }
        });
    }

    public static void switchMic(boolean isOn) {
        AppExecutors.networkIO().execute(() -> {
            if (isOn) {
                sInstance.csUnmuteMic();
            } else {
                sInstance.csMuteMic();
            }
        });
        MeetingRTCManager.muteLocalAudioStream(isOn);
    }

    public static void reconnect() {
        AppExecutors.networkIO().execute(() -> {
            CreateJoinRoomResult result = sInstance.csReconnect();
            sUserList.clear();
            if (result != null && result.info != null) {
                List<MeetingUserInfo> users = result.users;
                if (users != null) {
                    sUserList.addAll(users);
                }
                MeetingEventManager.post(result);
            } else {
                MeetingEventManager.post(new CreateJoinRoomResult());
            }
        });
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onSocketConnectEvent(SocketConnectEvent event) {
        sConnectStatus = event.status;

        if (!TextUtils.isEmpty(sAppId)) {
            return;
        }
        if (event.status != SocketConnectEvent.ConnectStatus.CONNECTED) {
            return;
        }
        AppExecutors.networkIO().execute(() -> {
            if (sIsRequestAppId) {
                return;
            }
            sIsRequestAppId = true;
            String appId = getManager().getAppId();
            if (!TextUtils.isEmpty(appId)) {
                sAppId = appId;
                MeetingRTCManager.createEngine(appId);
                MeetingRTCManager.enableLocalVideo(false);
            }
        });
    }
}
