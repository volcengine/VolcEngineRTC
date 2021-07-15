package com.ss.video.rtc.demo.meetingrtcdemo.core.socket;

import android.text.TextUtils;
import android.util.Log;

import com.google.gson.reflect.TypeToken;
import com.ss.video.rtc.demo.basic_module.utils.AppExecutors;
import com.ss.video.rtc.demo.basic_module.utils.SafeToast;
import com.ss.video.rtc.demo.meetingrtcdemo.common.MLog;
import com.ss.video.rtc.demo.meetingrtcdemo.core.MeetingApplication;
import com.ss.video.rtc.demo.meetingrtcdemo.core.MeetingDataManager;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.AskOpenCameraEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.AskOpenMicEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.CSHostChangeEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.CSInviteMicEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.CSJoinMeetingEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.CSLeaveMeetingEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.CSMeetingEndEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.CSMicOffEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.CSMicOnEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.CSMuteMicEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.CSRaiseHandsMicEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.CSToastEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.CSUnmuteMicEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.CameraStatusChangedEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.HostChangedEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.KickedOffEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.MeetingEndEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.MeetingEventManager;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.MicStatusChangeEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.MuteAllEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.MuteEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.RecordEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.RefreshUserNameEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.ShareScreenEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.SocketConnectEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.UserJoinEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.UserLeaveEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.AuditStateResult;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.LoginInfo;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.CSGetUserList;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.CreateJoinRoomResult;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.MeetingAppIdInfo;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.MeetingBroadcast;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.MeetingRecordInfo;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.MeetingRoomInfo;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.MeetingTokenInfo;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.MeetingUserInfo;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.RoomListInfo;
import com.ss.video.rtc.demo.meetingrtcdemo.voicechat.VoiceChatDataManger;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.net.URISyntaxException;
import java.util.List;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;

import io.socket.client.Ack;
import io.socket.client.IO;
import io.socket.client.Socket;
import io.socket.engineio.client.transports.WebSocket;

/**
 * Manager of meeting socket.
 */
public class MeetingSocketIOManager implements IMeetingManager {

    private static final int ERROR_SERVER_TIMEOUT = 503;
    private static final int ERROR_LOCAL_TIMEOUT = -10000;

    //request from client
    private static final String PASSWORD_FREE_LOGIN = "passwordFreeLogin";
    private static final String CHANGE_USER_NAME = "changeUserName";
    private static final String VERIFY_LOGIN_TOKEN = "verifyLoginToken";
    private static final String GET_APP_ID = "getAppID";
    private static final String JOIN_MEETING = "joinMeeting";
    private static final String LEAVE_MEETING = "leaveMeeting";
    private static final String TURN_ON_MIC = "turnOnMic";
    private static final String TURN_OFF_MIC = "turnOffMic";
    private static final String TURN_ON_CAMERA = "turnOnCamera";
    private static final String TURN_OFF_CAMERA = "turnOffCamera";
    private static final String GET_MEETING_USER_INFO = "getMeetingUserInfo";
    private static final String GET_MEETING_INFO = "getMeetingInfo";
    private static final String CHANGE_HOST = "changeHost";
    private static final String MUTE_USER = "muteUser";
    private static final String ASK_MIC_ON = "askMicOn";
    private static final String ASK_CAMERA_ON = "askCameraOn";
    private static final String END_MEETING = "endMeeting";
    private static final String START_SHARE_SCREEN = "startShareScreen";
    private static final String END_SHARE_SCREEN = "endShareScreen";
    private static final String RECORD_MEETING = "recordMeeting";
    private static final String UPDATE_RECORD_LAYOUT = "updateRecordLayout";
    private static final String GET_HISTORY_VIDEO_RECORD = "getHistoryVideoRecord";
    private static final String DELETE_VIDEO_RECORD = "deleteVideoRecord";

    private static final String CS_USER_RECONNECT = "csUserReconnect";
    private static final String CS_GET_APPID = "csGetAppID";
    private static final String CS_GET_MEETINGS = "csGetMeetings";
    private static final String CS_CREATE_MEETING = "csCreateMeeting";
    private static final String CS_JOIN_MEETING = "csJoinMeeting";
    private static final String CS_LEAVE_MEETING = "csLeaveMeeting";
    private static final String CS_GET_RAISE_HANDS = "csGetRaiseHands";
    private static final String CS_GET_AUDIENCES = "csGetAudiences";
    private static final String CS_INVITE_MIC = "csInviteMic";
    private static final String CS_CONFIRM_MIC = "csConfirmMic";
    private static final String CS_RAISE_HANDS_MIC = "csRaiseHandsMic";
    private static final String CS_AGREE_MIC = "csAgreeMic";
    private static final String CS_OFF_SELF_MIC = "csOffSelfMic";
    private static final String CS_OFF_MIC = "csOffMic";
    private static final String CS_MUTE_MIC = "csMuteMic";
    private static final String CS_UNMUTE_MIC = "csUnmuteMic";

    private static final String USER_RECONNECT = "userReconnect";

    //broadcast from server
    private static final String ON_USER_MIC_STATUS_CHANGE = "onUserMicStatusChange";
    private static final String ON_USER_CAMERA_STATUS_CHANGE = "onUserCameraStatusChange";
    private static final String ON_HOST_CHANGE = "onHostChange";
    private static final String ON_USER_JOIN_MEETING = "onUserJoinMeeting";
    private static final String ON_USER_LEAVE_MEETING = "onUserLeaveMeeting";
    private static final String ON_SHARE_SCREEN_STATUS_CHANGED = "onShareScreenStatusChanged";
    private static final String ON_RECORD = "onRecord";
    private static final String ON_MEETING_END = "onMeetingEnd";
    private static final String ON_MUTE_ALL = "onMuteAll";
    private static final String ON_RECORD_FINISHED = "onRecordFinished";
    private static final String ON_USER_KICKED_OFF = "onUserKickedOff";

    //notice from server
    private static final String ON_MUTE_USER = "onMuteUser";
    private static final String ON_ASKING_MIC_ON = "onAskingMicOn";
    private static final String ON_ASKING_CAMERA_ON = "onAskingCameraOn";

    private static final String ON_CS_JOIN_MEETING = "onCsJoinMeeting";
    private static final String ON_CS_LEAVE_MEETING = "onCsLeaveMeeting";
    private static final String ON_CS_RAISE_HANDS_MIC = "onCsRaiseHandsMic";
    private static final String ON_CS_INVITE_MIC = "onCsInviteMic";
    private static final String ON_CS_MIC_ON = "onCsMicOn";
    private static final String ON_CS_MIC_OFF = "onCsMicOff";
    private static final String ON_CS_MUTE_MIC = "onCsMuteMic";
    private static final String ON_CS_UNMUTE_MIC = "onCsUnmuteMic";
    private static final String ON_CS_MEETING_END = "onCsMeetingEnd";
    private static final String ON_CS_HOST_CHANGE = "onCsHostChange";

    private Socket mSocket;

    private void registerCallback(Socket socket) {
        if (socket == null) {
            return;
        }
        socket.on(Socket.EVENT_CONNECT, args -> {
            Log.d("registerCallback", "connect");
            MeetingEventManager.post(new SocketConnectEvent(SocketConnectEvent.ConnectStatus.CONNECTED));
        });
        socket.on(Socket.EVENT_RECONNECT, args -> {
            Log.d("registerCallback", "reconnect");
            reconnect();
            MeetingEventManager.post(new SocketConnectEvent(SocketConnectEvent.ConnectStatus.RECONNECTED));
        });
        socket.on(Socket.EVENT_CONNECTING, args -> {
            Log.d("registerCallback", "connecting");
            MeetingEventManager.post(new SocketConnectEvent(SocketConnectEvent.ConnectStatus.CONNECTING));
        });
        socket.on(Socket.EVENT_RECONNECTING, args -> {
            Log.d("registerCallback", "reconnecting");
            MeetingEventManager.post(new SocketConnectEvent(SocketConnectEvent.ConnectStatus.CONNECTING));
        });
        socket.on(Socket.EVENT_DISCONNECT, args -> {
            Log.d("registerCallback", "disconnect");
            MeetingEventManager.post(new SocketConnectEvent(SocketConnectEvent.ConnectStatus.DISCONNECTED));
        });
        socket.on(ON_USER_MIC_STATUS_CHANGE, args -> {
            printArgs("vcbroadcast", ON_USER_MIC_STATUS_CHANGE, args);
            MeetingBroadcast broadcast = MeetingBroadcast.getBroadcast(args[0]);
            if (MeetingDataManager.isSelf(broadcast.user_id)) {
                if (MeetingDataManager.getMicStatus() != broadcast.status) {
                    MeetingDataManager.switchMic(false);
                }
            } else {
                MeetingEventManager.post(new MicStatusChangeEvent(broadcast.user_id, broadcast.status));
            }
        });
        socket.on(ON_USER_CAMERA_STATUS_CHANGE, args -> {
            printArgs("vcbroadcast", "ON_USER_CAMERA_STATUS_CHANGE", args);
            MeetingBroadcast broadcast = MeetingBroadcast.getBroadcast(args[0]);
            if (MeetingDataManager.isSelf(broadcast.user_id)) {
                if (MeetingDataManager.getCameraStatus() != broadcast.status) {
                    MeetingDataManager.switchCamera(false);
                }
            } else {
                MeetingEventManager.post(new CameraStatusChangedEvent(broadcast.user_id, broadcast.status));
            }
        });
        socket.on(ON_HOST_CHANGE, args -> {
            printArgs("vcbroadcast", "ON_HOST_CHANGE", args);
            MeetingBroadcast broadcast = MeetingBroadcast.getBroadcast(args[0]);
            MeetingEventManager.post(new HostChangedEvent(broadcast.former_host_id, broadcast.host_id));
        });
        socket.on(ON_USER_JOIN_MEETING, args -> {
            printArgs("vcbroadcast", "ON_USER_JOIN_MEETING", args);
            MeetingBroadcast broadcast = MeetingBroadcast.getBroadcast(args[0]);
            if (broadcast != null) {
                MeetingUserInfo info = new MeetingUserInfo();
                info.user_id = broadcast.user_id;
                info.user_name = broadcast.user_name;
                info.user_uniform_name = broadcast.user_uniform_name;
                info.room_id = broadcast.room_id;
                info.is_camera_on = broadcast.is_camera_on;
                info.is_mic_on = broadcast.is_mic_on;
                info.is_host = broadcast.is_host;
                info.is_sharing = broadcast.is_sharing;
                info.created_at = broadcast.created_at;
                MeetingEventManager.post(new UserJoinEvent(info));
            }
        });
        socket.on(ON_USER_LEAVE_MEETING, args -> {
            printArgs("vcbroadcast", "ON_USER_LEAVE_MEETING", args);
            MeetingBroadcast broadcast = MeetingBroadcast.getBroadcast(args[0]);
            if (broadcast != null) {
                MeetingUserInfo info = new MeetingUserInfo();
                info.user_id = broadcast.user_id;
                MeetingEventManager.post(new UserLeaveEvent(info));
            }
        });
        socket.on(ON_SHARE_SCREEN_STATUS_CHANGED, args -> {
            printArgs("vcbroadcast", "ON_SHARE_SCREEN_STATUS_CHANGED", args);
            MeetingBroadcast broadcast = MeetingBroadcast.getBroadcast(args[0]);
            MeetingEventManager.post(new ShareScreenEvent(broadcast.status, broadcast.user_id));
        });
        socket.on(ON_RECORD, args -> {
            printArgs("vcbroadcast", "ON_RECORD", args);
            MeetingEventManager.post(new RecordEvent(true));
        });
        socket.on(ON_MEETING_END, args -> {
            printArgs("vcbroadcast", "ON_MEETING_END", args);
            MeetingEventManager.post(new MeetingEndEvent());
        });
        socket.on(ON_MUTE_ALL, args -> {
            printArgs("vcbroadcast", "ON_MUTE_ALL", args);
            if (!MeetingDataManager.isSelfHost()) {
                MeetingEventManager.post(new MuteEvent(MeetingDataManager.getSelfId()));
            }
            MeetingEventManager.post(new MuteAllEvent());
        });
        socket.on(ON_RECORD_FINISHED, args -> {
            printArgs("vcbroadcast", "ON_RECORD_FINISHED", args);
            MeetingEventManager.post(new RecordEvent(false));
        });
        socket.on(ON_USER_KICKED_OFF, args -> {
            printArgs("vcbroadcast", "ON_USER_KICKED_OFF", args);
            MeetingEventManager.post(new KickedOffEvent());
        });
        socket.on(ON_MUTE_USER, args -> {
            printArgs("vcbroadcast", "ON_MUTE_USER", args);
            MeetingBroadcast broadcast = MeetingBroadcast.getBroadcast(args[0]);
            if (MeetingDataManager.isSelf(broadcast.user_id)) {
                MeetingEventManager.post(new MuteEvent(MeetingDataManager.getSelfId()));
            }
        });
        socket.on(ON_ASKING_MIC_ON, args -> {
            printArgs("vcbroadcast", "ON_ASKING_MIC_ON", args);
            MeetingBroadcast broadcast = MeetingBroadcast.getBroadcast(args[0]);
            if (MeetingDataManager.isSelf(broadcast.user_id)) {
                MeetingEventManager.post(new AskOpenMicEvent());
            }
        });
        socket.on(ON_ASKING_CAMERA_ON, args -> {
            printArgs("vcbroadcast", "ON_ASKING_CAMERA_ON", args);
            MeetingBroadcast broadcast = MeetingBroadcast.getBroadcast(args[0]);
            if (MeetingDataManager.isSelf(broadcast.user_id)) {
                MeetingEventManager.post(new AskOpenCameraEvent());
            }
        });
        socket.on(ON_CS_JOIN_MEETING, args -> {
            printArgs("vcbroadcast", "ON_CS_JOIN_MEETING", args);
            MeetingBroadcast broadcast = MeetingBroadcast.getBroadcast(args[0]);
            if (!TextUtils.isEmpty(broadcast.user_id) && !VoiceChatDataManger.isSelf(broadcast.user_id)) {
                MeetingEventManager.post(new CSJoinMeetingEvent(0, MeetingBroadcast.toUserInfo(broadcast)));
            }
        });
        socket.on(ON_CS_LEAVE_MEETING, args -> {
            printArgs("vcbroadcast", "ON_CS_LEAVE_MEETING", args);
            MeetingBroadcast broadcast = MeetingBroadcast.getBroadcast(args[0]);
            if (!TextUtils.isEmpty(broadcast.user_id) && !VoiceChatDataManger.isSelf(broadcast.user_id)) {
                MeetingEventManager.post(new CSLeaveMeetingEvent(MeetingBroadcast.toUserInfo(broadcast)));
            }
        });
        socket.on(ON_CS_RAISE_HANDS_MIC, args -> {
            printArgs("vcbroadcast", "ON_CS_RAISE_HANDS_MIC", args);
            MeetingBroadcast broadcast = MeetingBroadcast.getBroadcast(args[0]);
            if (!TextUtils.isEmpty(broadcast.user_id)) {
                MeetingEventManager.post(new CSRaiseHandsMicEvent(broadcast.user_id));
            }
        });
        socket.on(ON_CS_INVITE_MIC, args -> {
            printArgs("vcbroadcast", "ON_CS_INVITE_MIC", args);
            MeetingBroadcast broadcast = MeetingBroadcast.getBroadcast(args[0]);
            if (!TextUtils.isEmpty(broadcast.user_id) && VoiceChatDataManger.isSelf(broadcast.user_id)) {
                MeetingEventManager.post(new CSInviteMicEvent(broadcast.user_id));
            }
        });
        socket.on(ON_CS_MIC_ON, args -> {
            printArgs("vcbroadcast", "ON_CS_MIC_ON", args);
            MeetingBroadcast broadcast = MeetingBroadcast.getBroadcast(args[0]);
            MeetingEventManager.post(new CSMicOnEvent(MeetingBroadcast.toUserInfo(broadcast)));
        });
        socket.on(ON_CS_MIC_OFF, args -> {
            printArgs("vcbroadcast", "ON_CS_MIC_OFF", args);
            MeetingBroadcast broadcast = MeetingBroadcast.getBroadcast(args[0]);
            MeetingEventManager.post(new CSMicOffEvent(broadcast.user_id));
        });
        socket.on(ON_CS_MUTE_MIC, args -> {
            printArgs("vcbroadcast", "ON_CS_MUTE_MIC", args);
            MeetingBroadcast broadcast = MeetingBroadcast.getBroadcast(args[0]);
            MeetingEventManager.post(new CSMuteMicEvent(broadcast.user_id));
        });
        socket.on(ON_CS_UNMUTE_MIC, args -> {
            printArgs("vcbroadcast", "ON_CS_UNMUTE_MIC", args);
            MeetingBroadcast broadcast = MeetingBroadcast.getBroadcast(args[0]);
            MeetingEventManager.post(new CSUnmuteMicEvent(broadcast.user_id));
        });
        socket.on(ON_CS_MEETING_END, args -> {
            printArgs("vcbroadcast", "ON_CS_MEETING_END", args);
            MeetingBroadcast broadcast = MeetingBroadcast.getBroadcast(args[0]);
            MeetingEventManager.post(new CSMeetingEndEvent(broadcast.room_id));
        });
        socket.on(ON_CS_HOST_CHANGE, args -> {
            printArgs("vcbroadcast", "ON_CS_HOST_CHANGE", args);
            MeetingBroadcast broadcast = MeetingBroadcast.getBroadcast(args[0]);
            MeetingEventManager.post(new CSHostChangeEvent(broadcast.former_host_id,
                    broadcast.host_info == null ? null : broadcast.host_info.user_id));
        });
    }

    @Override
    public void startConnect(String host) {
        try {
            MeetingEventManager.post(new SocketConnectEvent(SocketConnectEvent.ConnectStatus.CONNECTING));
            mSocket = IO.socket(host, buildOptions());
            registerCallback(mSocket);
            mSocket.connect();
        } catch (URISyntaxException e) {
            Log.e("MeetingManagerImpl", "startConnect exception", e);
        }
    }

    private IO.Options buildOptions() {
        IO.Options options = new IO.Options();
        options.path = "/vc_control";
        options.secure = true;
        options.forceNew = false;
        options.reconnection = true;
        options.transports = new String[]{WebSocket.NAME};
        options.timeout = 6000;
        options.reconnectionDelay = 2000;
        options.reconnectionDelayMax = 6000;
        String wsid = "Android_" + System.currentTimeMillis();
        String did = MeetingDataManager.getDeviceId();
        options.query = "wsid=" + wsid + "&did=" + did;

        MLog.d("buildOptions", "wsid: " + wsid + "   did:" + did);

        return options;
    }

    @Override
    public void disconnect() {
        if (mSocket != null) {
            mSocket.disconnect();
        }
    }

    @Override
    public void reconnect() {
        if (mSocket != null && MeetingDataManager.isInMeeting()) {
            printArgs("vcrequest", "reconnect execute");
            JSONObject json = new JSONObject();
            try {
                json.put("login_token", MeetingDataManager.getToken());
            } catch (JSONException e) {
                e.printStackTrace();
            }
            mSocket.emit(USER_RECONNECT, json, (Ack) args -> printArgs("vcrequest", "reconnect", args));
        }
    }

    @Override
    public boolean hasConnected() {
        return mSocket != null && mSocket.connected();
    }

    @Override
    public LoginInfo passwordFreeLogin(String userName) {
        JSONObject json = new JSONObject();
        final LoginInfo[] result = new LoginInfo[1];
        final CountDownLatch countDownLatch = new CountDownLatch(1);
        try {
            json.put("user_name", userName);
            mSocket.emit(PASSWORD_FREE_LOGIN, json, (Ack) args -> {
                printArgs("vcrequest", "passwordFreeLogin", args);
                ServerResponse<LoginInfo> response = new ServerResponse<>(args[0], LoginInfo.class);
                result[0] = response.getData();
                countDownLatch.countDown();
            });
            countDownLatch.await(2000, TimeUnit.MILLISECONDS);
            return result[0];
        } catch (Exception e) {
            printArgs("vcrequest", "passwordFreeLogin exception.");
            return null;
        }
    }

    @Override
    public RefreshUserNameEvent changeUserName(String userName) {
        JSONObject json = new JSONObject();
        final RefreshUserNameEvent[] result = new RefreshUserNameEvent[]{ null };
        final CountDownLatch countDownLatch = new CountDownLatch(1);
        try {
            json.put("login_token", MeetingDataManager.getToken());
            json.put("user_name", userName);
            mSocket.emit(CHANGE_USER_NAME, json, (Ack) args -> {
                printArgs("vcrequest", "changeUserName done.");
                ServerResponse<Object> response = new ServerResponse<>(args[0], Object.class);
                RefreshUserNameEvent event = new RefreshUserNameEvent(userName, response.getCode() == 200);
                event.errorMsg = response.getMsg();
                MeetingEventManager.post(event);
                result[0] = event;
                countDownLatch.countDown();
            });
            countDownLatch.await(2000, TimeUnit.MILLISECONDS);
            return result[0];
        } catch (Exception e) {
            printArgs("vcrequest", "changeUserName exception.");
            return null;
        }
    }

    @Override
    public int verifyLoginToken(String token) {
        JSONObject json = new JSONObject();
        final Integer[] result = new Integer[]{ -1 };
        final CountDownLatch countDownLatch = new CountDownLatch(1);
        try {
            json.put("login_token", token);
            mSocket.emit(VERIFY_LOGIN_TOKEN, json, (Ack) args -> {
                printArgs("vcrequest", "verifyLoginToken done.");
                ServerResponse<Object> response = new ServerResponse<>(args[0], Object.class);
                result[0] = response.getCode();
                countDownLatch.countDown();
            });
            countDownLatch.await(2000, TimeUnit.MILLISECONDS);
            return result[0];
        } catch (Exception e) {
            printArgs("vcrequest", "verifyLoginToken exception.");
            return -1;
        }
    }

    @Override
    public String getAppId() {
        final ServerResponse<MeetingAppIdInfo>[] result = new ServerResponse[1];
        final CountDownLatch countDownLatch = new CountDownLatch(1);
        JSONObject json = new JSONObject();
        try {
            json.put("login_token", MeetingDataManager.getToken());
        } catch (JSONException e) {
            e.printStackTrace();
        }
        mSocket.emit(GET_APP_ID, json, (Ack) args -> {
            printArgs("vcrequest", "getAppId", args);
            ServerResponse<MeetingAppIdInfo> response = new ServerResponse<>(args[0], MeetingAppIdInfo.class);
            result[0] = response;
            countDownLatch.countDown();
        });
        try {
            countDownLatch.await(2000, TimeUnit.MILLISECONDS);
            if (result[0] == null) {
                return null;
            } else {
                MeetingAppIdInfo info = result[0].getData();
                if (info == null) {
                    return null;
                } else {
                    return info.app_id;
                }
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
            return null;
        }
    }

    @Override
    public MeetingTokenInfo joinMeeting(String userName, String roomId, boolean micOn, boolean cameraOn) {
        final MeetingTokenInfo[] result = new MeetingTokenInfo[1];
        final CountDownLatch countDownLatch = new CountDownLatch(1);
        JSONObject json = new JSONObject();
        try {
            json.put("login_token", MeetingDataManager.getToken());
            json.put("app_id", MeetingDataManager.getAppId());
            json.put("user_id", MeetingApplication.sUserID);
            json.put("user_name", userName);
            json.put("room_id", roomId);
            json.put("mic", micOn);
            json.put("camera", cameraOn);
            mSocket.emit(JOIN_MEETING, json, (Ack) args -> {
                printArgs("vcrequest", "joinMeeting", args);
                ServerResponse<MeetingTokenInfo> response = new ServerResponse<>(args[0], MeetingTokenInfo.class);
                result[0] = response.getData();
                if (response.getCode() == 406) {
                    AppExecutors.mainThread().execute(() -> SafeToast.show("会议房间已满员"));
                }
                if (response.getCode() == 702) {
                    AppExecutors.mainThread().execute(() -> SafeToast.show("服务端Token生成失败，请重试"));
                }
                countDownLatch.countDown();
            });
        } catch (JSONException e) {
            e.printStackTrace();
        }

        try {
            countDownLatch.await(2000, TimeUnit.MILLISECONDS);
            return result[0];
        } catch (InterruptedException e) {
            e.printStackTrace();
            return null;
        }
    }

    @Override
    public void leaveMeeting() {
        JSONObject json = new JSONObject();
        try {
            json.put("login_token", MeetingDataManager.getToken());
        } catch (JSONException e) {
            e.printStackTrace();
        }
        mSocket.emit(LEAVE_MEETING, json,
                (Ack) args -> printArgs("vcrequest", "leaveMeeting"));
    }

    @Override
    public void toggleMicState(boolean on) {
        JSONObject json = new JSONObject();
        try {
            json.put("login_token", MeetingDataManager.getToken());
        } catch (JSONException e) {
            e.printStackTrace();
        }
        mSocket.emit(on ? TURN_ON_MIC : TURN_OFF_MIC, json,
                (Ack) args -> printArgs("vcrequest", "toggleMicState"));
    }

    @Override
    public void toggleCameraState(boolean on) {
        JSONObject json = new JSONObject();
        try {
            json.put("login_token", MeetingDataManager.getToken());
        } catch (JSONException e) {
            e.printStackTrace();
        }
        mSocket.emit(on ? TURN_ON_CAMERA : TURN_OFF_CAMERA, json,
                (Ack) args -> printArgs("vcrequest", "toggleCameraState"));
    }

    @Override
    public List<MeetingUserInfo> getMeetingParticipantsInfo() {
        final Object[] result = new Object[1];
        final CountDownLatch countDownLatch = new CountDownLatch(1);
        JSONObject json = new JSONObject();
        try {
            json.put("login_token", MeetingDataManager.getToken());
        } catch (JSONException e) {
            e.printStackTrace();
        }
        mSocket.emit(GET_MEETING_USER_INFO, json, (Ack) args -> {
            printArgs("vcrequest", "getMeetingParticipantsInfo", args);

            ServerResponse<List<MeetingUserInfo>> response = new ServerResponse<>(args[0],
                    new TypeToken<List<MeetingUserInfo>>() {
                    }.getType());

            List<MeetingUserInfo> infoList = response.getData();
            result[0] = infoList;

            if (infoList != null && !infoList.isEmpty()) {
                for (MeetingUserInfo info : infoList) {
                    if (info.is_host) {
                        MeetingDataManager.setHostUid(info.user_id);
                    }
                }
            }

            countDownLatch.countDown();
        });

        try {
            countDownLatch.await(2000, TimeUnit.MILLISECONDS);
            return result[0] == null ? null : (List<MeetingUserInfo>) result[0];
        } catch (InterruptedException e) {
            e.printStackTrace();
            printError("getMeetingParticipantsInfo", e);
            return null;
        }
    }

    @Override
    public MeetingUserInfo getMeetingParticipantInfo(String userId) {
        final MeetingUserInfo[] result = new MeetingUserInfo[1];
        final CountDownLatch countDownLatch = new CountDownLatch(1);
        JSONObject json = new JSONObject();
        try {
            json.put("login_token", MeetingDataManager.getToken());
            json.put("user_id", userId);
            mSocket.emit(GET_MEETING_USER_INFO, json, (Ack) args -> {
                printArgs("vcrequest", "getMeetingParticipantInfo", args);
                ServerResponse<MeetingUserInfo> response = new ServerResponse<>(args[0], MeetingUserInfo.class);
                result[0] = response.getData();
                countDownLatch.countDown();
            });
        } catch (JSONException e) {
            e.printStackTrace();
        }

        try {
            countDownLatch.await(2000, TimeUnit.MILLISECONDS);
            return result[0];
        } catch (InterruptedException e) {
            e.printStackTrace();
            return null;
        }
    }

    @Override
    public MeetingRoomInfo getMeetingInfo() {
        final MeetingRoomInfo[] result = new MeetingRoomInfo[1];
        final CountDownLatch countDownLatch = new CountDownLatch(1);
        JSONObject json = new JSONObject();
        try {
            json.put("login_token", MeetingDataManager.getToken());
        } catch (JSONException e) {
            e.printStackTrace();
        }
        mSocket.emit(GET_MEETING_INFO, json, (Ack) args -> {
            printArgs("vcrequest", "getMeetingInfo", args);
            ServerResponse<MeetingRoomInfo> response = new ServerResponse<>(args[0], MeetingRoomInfo.class);
            result[0] = response.getData();
            countDownLatch.countDown();
        });

        try {
            countDownLatch.await(2000, TimeUnit.MILLISECONDS);
            return result[0];
        } catch (InterruptedException e) {
            e.printStackTrace();
            return null;
        }
    }

    @Override
    public int changeHost(String userId) {
        final Object[] result = new Object[]{ERROR_LOCAL_TIMEOUT};
        final CountDownLatch countDownLatch = new CountDownLatch(1);
        JSONObject json = new JSONObject();
        try {
            json.put("login_token", MeetingDataManager.getToken());
            json.put("user_id", userId);
            mSocket.emit(CHANGE_HOST, json, (Ack) args -> {
                printArgs("vcrequest", "changeHost", args);
                ServerResponse<Object> response = new ServerResponse<>(args[0], Object.class);
                result[0] = response.getCode();
                countDownLatch.countDown();
            });
        } catch (JSONException e) {
            printError("changeHost", e);
            e.printStackTrace();
        }

        try {
            countDownLatch.await(2000, TimeUnit.MILLISECONDS);
            int errorCode = (int) result[0];
            if (errorCode == ERROR_LOCAL_TIMEOUT || errorCode == 504 || errorCode == ERROR_SERVER_TIMEOUT) {
                AppExecutors.mainThread().execute(() -> SafeToast.show("移交主持人失败，请重试"));
            }
            return result[0] == null ? -1 : (int) result[0];
        } catch (InterruptedException e) {
            e.printStackTrace();
            return -1;
        }
    }

    @Override
    public void muteUserMic(String userId) {
        JSONObject json = new JSONObject();
        try {
            json.put("login_token", MeetingDataManager.getToken());
            json.put("user_id", userId);
            mSocket.emit(MUTE_USER, json);
        } catch (JSONException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void muteAllUserMic() {
        final Object[] result = new Object[]{ERROR_LOCAL_TIMEOUT};
        final CountDownLatch countDownLatch = new CountDownLatch(1);
        JSONObject json = new JSONObject();
        try {
            json.put("login_token", MeetingDataManager.getToken());
        } catch (JSONException e) {
            e.printStackTrace();
        }
        mSocket.emit(MUTE_USER, json, (Ack) args -> {
            printArgs("vcrequest", "muteAllUserMic", args[0]);
            ServerResponse<Object> response = new ServerResponse<>(args[0], Object.class);
            result[0] = response.getCode();
            countDownLatch.countDown();
        });
        try {
            countDownLatch.await(2000, TimeUnit.MILLISECONDS);
            int errorCode = (int) result[0];
            if (errorCode == ERROR_LOCAL_TIMEOUT || errorCode == ERROR_SERVER_TIMEOUT) {
                AppExecutors.mainThread().execute(() -> SafeToast.show("全体静音失败，请重试"));
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void askUserMicOn(String userId) {
        JSONObject json = new JSONObject();
        try {
            json.put("login_token", MeetingDataManager.getToken());
            json.put("user_id", userId);
            mSocket.emit(ASK_MIC_ON, json);
        } catch (JSONException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void askUserCameraOn(String userId) {
        JSONObject json = new JSONObject();
        try {
            json.put("login_token", MeetingDataManager.getToken());
            json.put("user_id", userId);
            mSocket.emit(ASK_CAMERA_ON, json);
        } catch (JSONException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void closeMeeting() {
        JSONObject json = new JSONObject();
        try {
            json.put("login_token", MeetingDataManager.getToken());
        } catch (JSONException e) {
            e.printStackTrace();
        }
        mSocket.emit(END_MEETING, json, (Ack) args -> printArgs("vcrequest", "closeMeeting"));
    }

    @Override
    public void startScreenShare() {
        JSONObject json = new JSONObject();
        try {
            json.put("login_token", MeetingDataManager.getToken());
        } catch (JSONException e) {
            e.printStackTrace();
        }
        mSocket.emit(START_SHARE_SCREEN, json, (Ack) args -> printArgs("vcrequest", "startScreenShare"));
    }

    @Override
    public void stopScreenShare() {
        JSONObject json = new JSONObject();
        try {
            json.put("login_token", MeetingDataManager.getToken());
        } catch (JSONException e) {
            e.printStackTrace();
        }
        mSocket.emit(END_SHARE_SCREEN, json, (Ack) args -> printArgs("vcrequest", "stopScreenShare"));
    }

    @Override
    public void startMeetingRecord(List<String> users, String screenUid) {
        final CountDownLatch countDownLatch = new CountDownLatch(1);
        JSONArray array = new JSONArray();
        if (users != null) {
            for (String uid : users) {
                array.put(uid);
            }
        }
        JSONObject json = new JSONObject();
        try {
            json.put("login_token", MeetingDataManager.getToken());
            json.put("users", array);
            json.put("screen_uid", screenUid == null ? "" : screenUid);
        } catch (JSONException e) {
            e.printStackTrace();
        }
        mSocket.emit(RECORD_MEETING, json, (Ack) args -> {
            ServerResponse<Object> response = new ServerResponse<>(args[0], Object.class);
            if (response.getCode() == 412) {
                AppExecutors.mainThread().execute(() -> SafeToast.show("屏幕共享发起失败，请提示前一位参会者结束共享"));
            }
            countDownLatch.countDown();
            printArgs("vcrequest", "startMeetingRecord");
        });
        try {
            countDownLatch.await(2000, TimeUnit.MILLISECONDS);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    public void updateRecordLayout(List<String> users, String screenUid) {
        JSONArray array = new JSONArray();
        if (users != null) {
            for (String uid : users) {
                array.put(uid);
            }
        }
        JSONObject json = new JSONObject();
        try {
            json.put("login_token", MeetingDataManager.getToken());
            json.put("users", array);
            json.put("screen_uid", screenUid == null ? "" : screenUid);
        } catch (JSONException e) {
            e.printStackTrace();
        }
        mSocket.emit(UPDATE_RECORD_LAYOUT, json, (Ack) args -> printArgs("vcrequest", "updateRecordLayout"));
    }

    @Override
    public List<MeetingRecordInfo> getHistoryMeetingRecord() {
        final Object[] result = new Object[1];
        final CountDownLatch countDownLatch = new CountDownLatch(1);
        JSONObject json = new JSONObject();
        try {
            json.put("login_token", MeetingDataManager.getToken());
        } catch (JSONException e) {
            e.printStackTrace();
        }
        mSocket.emit(GET_HISTORY_VIDEO_RECORD, json, (Ack) args -> {
            printArgs("vcrequest", "getHistoryMeetingRecord", args);
            ServerResponse<List<MeetingRecordInfo>> response = new ServerResponse<>(args[0],
                    new TypeToken<List<MeetingRecordInfo>>() {
                    }.getType());
            result[0] = response.getData();
            countDownLatch.countDown();
        });
        try {
            countDownLatch.await(2000, TimeUnit.MILLISECONDS);
            return result[0] == null ? null : (List<MeetingRecordInfo>) result[0];
        } catch (InterruptedException e) {
            e.printStackTrace();
            return null;
        }
    }

    @Override
    public void deleteHistoryMeetingRecord(String vid) {
        JSONObject json = new JSONObject();
        try {
            json.put("login_token", MeetingDataManager.getToken());
            json.put("vid", vid);
            mSocket.emit(DELETE_VIDEO_RECORD, json, (Ack) args ->
                    printArgs("vcrequest", "deleteHistoryMeetingRecord", vid));
        } catch (JSONException e) {
            e.printStackTrace();
        }
    }

    @Override
    public AuditStateResult getAuditState(String deviceType, String appVersion) {
        final Object[] result = new Object[]{ ERROR_LOCAL_TIMEOUT };
        final CountDownLatch countDownLatch = new CountDownLatch(1);
        JSONObject json = new JSONObject();
        try {
            json.put("login_token", MeetingDataManager.getToken());
            json.put("device_type", deviceType);
            json.put("app_version", appVersion);
            mSocket.emit(CHANGE_HOST, json, (Ack) args -> {
                printArgs("vcrequest", "getAuditState", args);
                ServerResponse<AuditStateResult> response = new ServerResponse<>(args[0], AuditStateResult.class);
                result[0] = response.getData();
                countDownLatch.countDown();
            });
        } catch (JSONException e) {
            printError("getAuditState", e);
            e.printStackTrace();
        }

        try {
            countDownLatch.await(2000, TimeUnit.MILLISECONDS);
            return result[0] == null ? null : (AuditStateResult) result[0];
        } catch (InterruptedException e) {
            e.printStackTrace();
            return null;
        }
    }

    @Override
    public CreateJoinRoomResult csReconnect() {
        final Object[] result = new Object[1];
        final CountDownLatch countDownLatch = new CountDownLatch(1);
        JSONObject json = new JSONObject();
        try {
            json.put("login_token", MeetingDataManager.getToken());
        } catch (JSONException e) {
            e.printStackTrace();
        }
        mSocket.emit(CS_USER_RECONNECT, json, (Ack) args -> {
            ServerResponse<CreateJoinRoomResult> response = new ServerResponse<>(args[0], CreateJoinRoomResult.class);
            result[0] = response.getData();
            countDownLatch.countDown();
            printArgs("vcrequest", "csReconnect", args);
        });
        try {
            countDownLatch.await(2000, TimeUnit.MILLISECONDS);
            return result[0] == null ? null : (CreateJoinRoomResult) result[0];
        } catch (InterruptedException e) {
            e.printStackTrace();
            return null;
        }
    }

    @Override
    public String csGetAppID() {
        final Object[] result = new Object[1];
        final CountDownLatch countDownLatch = new CountDownLatch(1);
        mSocket.emit(CS_GET_APPID, (Ack) args -> {
            printArgs("vcrequest", "csGetAppID", args);
            ServerResponse<String> response = new ServerResponse<>(args[0],
                    new TypeToken<List<MeetingRecordInfo>>() {
                    }.getType());
            result[0] = response.getData();
            countDownLatch.countDown();
        });
        try {
            countDownLatch.await(2000, TimeUnit.MILLISECONDS);
            return result[0] == null ? null : (String) result[0];
        } catch (InterruptedException e) {
            e.printStackTrace();
            return null;
        }
    }

    @Override
    public List<MeetingRoomInfo> csGetMeetings() {
        final Object[] result = new Object[1];
        final CountDownLatch countDownLatch = new CountDownLatch(1);
        JSONObject json = new JSONObject();
        try {
            json.put("login_token", MeetingDataManager.getToken());
        } catch (JSONException e) {
            e.printStackTrace();
        }
        mSocket.emit(CS_GET_MEETINGS, json, (Ack) args -> {
            printArgs("vcrequest", "csGetMeetings", args);
            ServerResponse<RoomListInfo> response = new ServerResponse<>(args[0], RoomListInfo.class);

            if (response.getData() != null) {
                result[0] = response.getData().infos;
            } else {
                result[0] = null;
            }
            countDownLatch.countDown();
        });
        try {
            countDownLatch.await(2000, TimeUnit.MILLISECONDS);
            return result[0] == null ? null : (List<MeetingRoomInfo>) result[0];
        } catch (InterruptedException e) {
            e.printStackTrace();
            return null;
        }
    }

    @Override
    public CreateJoinRoomResult csCreateMeeting(String roomName, String userName) {
        final Object[] result = new Object[1];
        final CountDownLatch countDownLatch = new CountDownLatch(1);
        JSONObject json = new JSONObject();
        try {
            json.put("login_token", MeetingDataManager.getToken());
            json.put("room_name", roomName == null ? "" : roomName);
            json.put("user_name", userName == null ? "" : userName);
        } catch (JSONException e) {
            e.printStackTrace();
        }
        mSocket.emit(CS_CREATE_MEETING, json, (Ack) args -> {
            ServerResponse<CreateJoinRoomResult> response = new ServerResponse<>(args[0], CreateJoinRoomResult.class);
            result[0] = response.getData();
            if (response.getCode() == 430) {
                MeetingEventManager.post(new CSToastEvent("输入内容包含敏感词，请重新输入"));
            }
            countDownLatch.countDown();
            printArgs("vcrequest", "csCreateMeeting", args);
        });
        try {
            countDownLatch.await(2000, TimeUnit.MILLISECONDS);
            return result[0] == null ? null : (CreateJoinRoomResult) result[0];
        } catch (InterruptedException e) {
            e.printStackTrace();
            return null;
        }
    }

    @Override
    public CreateJoinRoomResult csJoinMeeting(String roomId, String userName) {
        final Object[] result = new Object[1];
        final CountDownLatch countDownLatch = new CountDownLatch(1);
        JSONObject json = new JSONObject();
        try {
            json.put("login_token", MeetingDataManager.getToken());
            json.put("room_id", roomId == null ? "" : roomId);
            json.put("user_name", userName == null ? "" : userName);
        } catch (JSONException e) {
            e.printStackTrace();
        }
        mSocket.emit(CS_JOIN_MEETING, json, (Ack) args -> {
            ServerResponse<CreateJoinRoomResult> response = new ServerResponse<>(args[0], CreateJoinRoomResult.class);
            result[0] = response.getData();
            countDownLatch.countDown();
            printArgs("vcrequest", "csJoinMeeting", args);
        });
        try {
            countDownLatch.await(2000, TimeUnit.MILLISECONDS);
            return result[0] == null ? null : (CreateJoinRoomResult) result[0];
        } catch (InterruptedException e) {
            e.printStackTrace();
            return null;
        }
    }

    @Override
    public void csLeaveMeeting() {
        JSONObject json = new JSONObject();
        try {
            json.put("login_token", MeetingDataManager.getToken());
        } catch (JSONException e) {
            e.printStackTrace();
        }
        mSocket.emit(CS_LEAVE_MEETING, json, (Ack) args -> printArgs("vcrequest", "csLeaveMeeting"));
    }

    @Override
    public List<MeetingUserInfo> csGetRaiseHands() {
        final Object[] result = new Object[1];
        final CountDownLatch countDownLatch = new CountDownLatch(1);
        JSONObject json = new JSONObject();
        try {
            json.put("login_token", MeetingDataManager.getToken());
        } catch (JSONException e) {
            e.printStackTrace();
        }
        mSocket.emit(CS_GET_RAISE_HANDS, json, (Ack) args -> {
            printArgs("vcrequest", "csGetRaiseHands", args);
            ServerResponse<CSGetUserList> response = new ServerResponse<>(args[0], CSGetUserList.class);
            if (response.getCode() == 200) {
                result[0] = response.getData().users;
            } else {
                if (response.getCode() == 416) {
                    MeetingEventManager.post(new CSToastEvent("没有操作权限"));
                } else {
                    MeetingEventManager.post(new CSToastEvent("系统繁忙，请稍后重试"));
                }

                result[0] = null;
            }
            countDownLatch.countDown();
        });
        try {
            countDownLatch.await(2000, TimeUnit.MILLISECONDS);
            return result[0] == null ? null : (List<MeetingUserInfo>) result[0];
        } catch (InterruptedException e) {
            e.printStackTrace();
            return null;
        }
    }

    @Override
    public List<MeetingUserInfo> csGetAudiences() {
        final Object[] result = new Object[1];
        final CountDownLatch countDownLatch = new CountDownLatch(1);
        JSONObject json = new JSONObject();
        try {
            json.put("login_token", MeetingDataManager.getToken());
        } catch (JSONException e) {
            e.printStackTrace();
        }
        mSocket.emit(CS_GET_AUDIENCES, json, (Ack) args -> {
            printArgs("vcrequest", "csGetRaiseHands", args);
            ServerResponse<CSGetUserList> response = new ServerResponse<>(args[0], CSGetUserList.class);
            if (response.getCode() == 200) {
                result[0] = response.getData().users;
            } else {
                if (response.getCode() == 416) {
                    MeetingEventManager.post(new CSToastEvent("没有操作权限"));
                } else {
                    MeetingEventManager.post(new CSToastEvent("系统繁忙，请稍后重试"));
                }

                result[0] = null;
            }
            countDownLatch.countDown();
        });
        try {
            countDownLatch.await(2000, TimeUnit.MILLISECONDS);
            return result[0] == null ? null : (List<MeetingUserInfo>) result[0];
        } catch (InterruptedException e) {
            e.printStackTrace();
            return null;
        }
    }

    @Override
    public void csInviteMic(String userId) {
        final Integer[] result = new Integer[]{ERROR_LOCAL_TIMEOUT};
        final CountDownLatch countDownLatch = new CountDownLatch(1);
        JSONObject json = new JSONObject();
        try {
            json.put("user_id", userId);
            json.put("login_token", MeetingDataManager.getToken());
            mSocket.emit(CS_INVITE_MIC, json, (Ack) args -> {
                printArgs("vcrequest", "csInviteMic", args);
                result[0] = 0;
                countDownLatch.countDown();
            });
            countDownLatch.await(2000, TimeUnit.MILLISECONDS);
            if (result[0] == ERROR_LOCAL_TIMEOUT) {
                MeetingEventManager.post(new CSToastEvent("操作失败，请重试提示"));
            }
        } catch (JSONException | InterruptedException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void csConfirmMic() {
        JSONObject json = new JSONObject();
        try {
            json.put("login_token", MeetingDataManager.getToken());
        } catch (JSONException e) {
            e.printStackTrace();
        }
        mSocket.emit(CS_CONFIRM_MIC, json, (Ack) args ->
                printArgs("vcrequest", "csConfirmMic", args));
    }

    @Override
    public void csRaiseHandsMic() {
        JSONObject json = new JSONObject();
        try {
            json.put("login_token", MeetingDataManager.getToken());
        } catch (JSONException e) {
            e.printStackTrace();
        }
        mSocket.emit(CS_RAISE_HANDS_MIC, json, (Ack) args ->
                printArgs("vcrequest", "csRaiseHandsMic", args));
    }

    @Override
    public void csAgreeMic(String userId) {
        final Integer[] result = new Integer[]{ERROR_LOCAL_TIMEOUT};
        final CountDownLatch countDownLatch = new CountDownLatch(1);
        JSONObject json = new JSONObject();
        try {
            json.put("user_id", userId);
            json.put("login_token", MeetingDataManager.getToken());
            mSocket.emit(CS_AGREE_MIC, json, (Ack) args -> {
                printArgs("vcrequest", "csAgreeMic", args);
                result[0] = 0;
                countDownLatch.countDown();
            });
            countDownLatch.await(2000, TimeUnit.MILLISECONDS);
            if (result[0] == ERROR_LOCAL_TIMEOUT) {
                MeetingEventManager.post(new CSToastEvent("操作失败，请重试提示"));
            }
        } catch (JSONException | InterruptedException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void csOffSelfMic() {
        final Integer[] result = new Integer[]{ERROR_LOCAL_TIMEOUT};
        final CountDownLatch countDownLatch = new CountDownLatch(1);
        JSONObject json = new JSONObject();
        try {
            json.put("login_token", MeetingDataManager.getToken());
        } catch (JSONException e) {
            e.printStackTrace();
        }
        mSocket.emit(CS_OFF_SELF_MIC, json, (Ack) args -> {
            printArgs("vcrequest", "csOffSelfMic", args);
            result[0] = 0;
            countDownLatch.countDown();
        });
        try {
            countDownLatch.await(2000, TimeUnit.MILLISECONDS);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        if (result[0] == ERROR_LOCAL_TIMEOUT) {
            MeetingEventManager.post(new CSToastEvent("操作失败，请重试提示"));
        }
    }

    @Override
    public void csOffMic(String userId) {
        final Integer[] result = new Integer[]{ERROR_LOCAL_TIMEOUT};
        final CountDownLatch countDownLatch = new CountDownLatch(1);
        JSONObject json = new JSONObject();
        try {
            json.put("user_id", userId);
            json.put("login_token", MeetingDataManager.getToken());
            mSocket.emit(CS_OFF_MIC, json, (Ack) args -> {
                printArgs("vcrequest", "csOffMic", args);
                result[0] = 0;
                countDownLatch.countDown();
            });
            countDownLatch.await(2000, TimeUnit.MILLISECONDS);
            if (result[0] == ERROR_LOCAL_TIMEOUT) {
                MeetingEventManager.post(new CSToastEvent("操作失败，请重试提示"));
            }
        } catch (JSONException | InterruptedException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void csMuteMic() {
        JSONObject json = new JSONObject();
        try {
            json.put("login_token", MeetingDataManager.getToken());
        } catch (JSONException e) {
            e.printStackTrace();
        }
        mSocket.emit(CS_MUTE_MIC, json, (Ack) args ->
                printArgs("vcrequest", "csMuteMic", args));
    }

    @Override
    public void csUnmuteMic() {
        JSONObject json = new JSONObject();
        try {
            json.put("login_token", MeetingDataManager.getToken());
        } catch (JSONException e) {
            e.printStackTrace();
        }
        mSocket.emit(CS_UNMUTE_MIC, json, (Ack) args ->
                printArgs("vcrequest", "csUnmuteMic", args));
    }

    /**
     * Print log.
     *
     * @param type   request or broadcast
     * @param method function's name
     * @param args   parameters of function
     */
    private void printArgs(String type, String method, Object... args) {
        if (args == null || args.length == 0) {
            return;
        }
        StringBuilder builder = new StringBuilder();
        for (Object o : args) {
            builder.append(o.toString()).append(";");
        }
        Log.d(type + ":" + method, builder.toString());
    }

    private void printError(String method, Exception e) {
        if (e == null) {
            return;
        }
        Log.e(method, "MeetingManagerImplError", e);
    }
}
