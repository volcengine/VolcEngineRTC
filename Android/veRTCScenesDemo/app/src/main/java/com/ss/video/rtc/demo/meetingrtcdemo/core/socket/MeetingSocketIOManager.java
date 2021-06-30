package com.ss.video.rtc.demo.meetingrtcdemo.core.socket;

import android.util.Log;

import com.google.gson.reflect.TypeToken;
import com.ss.video.rtc.demo.basic_module.utils.AppExecutors;
import com.ss.video.rtc.demo.basic_module.utils.SafeToast;
import com.ss.video.rtc.demo.meetingrtcdemo.core.MeetingDataManager;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.AskOpenCameraEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.AskOpenMicEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.CameraStatusChangedEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.HostChangedEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.KickedOffEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.MeetingEndEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.MeetingEventManager;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.MicStatusChangeEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.MuteAllEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.MuteEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.RecordEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.ShareScreenEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.SocketConnectEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.UserJoinEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.UserLeaveEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.MeetingAppIdInfo;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.MeetingBroadcast;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.MeetingRecordInfo;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.MeetingRoomInfo;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.MeetingTokenInfo;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.MeetingUserInfo;

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
        options.query = "wsid=Android_" + System.currentTimeMillis() + "&did=" + MeetingDataManager.getDeviceId();

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
            mSocket.emit(USER_RECONNECT, (Ack) args -> printArgs("vcrequest", "reconnect", args));
        }
    }

    @Override
    public boolean hasConnected() {
        return mSocket != null && mSocket.connected();
    }

    @Override
    public String getAppId() {
        final ServerResponse<MeetingAppIdInfo>[] result = new ServerResponse[1];
        final CountDownLatch countDownLatch = new CountDownLatch(1);
        mSocket.emit(GET_APP_ID, (Ack) args -> {
            printArgs("vcrequest", "getAppId", args);
            ServerResponse<MeetingAppIdInfo> response = new ServerResponse<>(args[0], MeetingAppIdInfo.class);
            result[0] = response;
            countDownLatch.countDown();
        });
        try {
            countDownLatch.await(2000, TimeUnit.MILLISECONDS);
            return result[0] == null ? null : result[0].getData().app_id;
        } catch (InterruptedException e) {
            e.printStackTrace();
            return null;
        }
    }

    @Override
    public MeetingTokenInfo joinMeeting(String userId, String roomId, boolean micOn, boolean cameraOn) {
        final MeetingTokenInfo[] result = new MeetingTokenInfo[1];
        final CountDownLatch countDownLatch = new CountDownLatch(1);
        JSONObject json = new JSONObject();
        try {
            json.put("app_id", MeetingDataManager.getAppId());
            json.put("user_id", userId);
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
        mSocket.emit(LEAVE_MEETING, (Ack) args -> printArgs("vcrequest", "leaveMeeting"));
    }

    @Override
    public void toggleMicState(boolean on) {
        mSocket.emit(on ? TURN_ON_MIC : TURN_OFF_MIC, (Ack) args -> printArgs("vcrequest", "toggleMicState"));
    }

    @Override
    public void toggleCameraState(boolean on) {
        mSocket.emit(on ? TURN_ON_CAMERA : TURN_OFF_CAMERA, (Ack) args -> printArgs("vcrequest", "toggleCameraState"));
    }

    @Override
    public List<MeetingUserInfo> getMeetingParticipantsInfo() {
        final Object[] result = new Object[1];
        final CountDownLatch countDownLatch = new CountDownLatch(1);

        mSocket.emit(GET_MEETING_USER_INFO, (Ack) args -> {
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
        mSocket.emit(GET_MEETING_INFO, (Ack) args -> {
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
        final Object[] result = new Object[]{ ERROR_LOCAL_TIMEOUT };
        final CountDownLatch countDownLatch = new CountDownLatch(1);
        JSONObject json = new JSONObject();
        try {
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
            json.put("user_id", userId);
            mSocket.emit(MUTE_USER, json);
        } catch (JSONException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void muteAllUserMic() {
        final Object[] result = new Object[]{ ERROR_LOCAL_TIMEOUT };
        final CountDownLatch countDownLatch = new CountDownLatch(1);
        mSocket.emit(MUTE_USER, (Ack) args -> {
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
            json.put("user_id", userId);
            mSocket.emit(ASK_CAMERA_ON, json);
        } catch (JSONException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void closeMeeting() {
        mSocket.emit(END_MEETING, (Ack) args -> printArgs("vcrequest", "closeMeeting"));
    }

    @Override
    public void startScreenShare() {
        mSocket.emit(START_SHARE_SCREEN, (Ack) args -> printArgs("vcrequest", "startScreenShare"));
    }

    @Override
    public void stopScreenShare() {
        mSocket.emit(END_SHARE_SCREEN, (Ack) args -> printArgs("vcrequest", "stopScreenShare"));
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
        mSocket.emit(GET_HISTORY_VIDEO_RECORD, (Ack) args -> {
            printArgs("vcrequest", "getHistoryMeetingRecord", args);
            ServerResponse<List<MeetingRecordInfo>> response = new ServerResponse<>(args[0],
                    new TypeToken<List<MeetingRecordInfo>>() {}.getType());
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
