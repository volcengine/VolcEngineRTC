package com.ss.video.rtc.demo.meetingrtcdemo.core;

import android.Manifest;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.media.projection.MediaProjectionManager;
import android.os.Build;
import android.os.Process;
import android.text.TextUtils;
import android.util.Log;
import android.util.Pair;
import android.view.SurfaceView;

import com.ss.video.rtc.demo.basic_module.utils.AppExecutors;
import com.ss.video.rtc.demo.basic_module.utils.SPUtils;
import com.ss.video.rtc.demo.basic_module.utils.SafeToast;
import com.ss.video.rtc.demo.basic_module.utils.Utilities;
import com.ss.video.rtc.demo.meetingrtcdemo.common.MLog;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.CameraStatusChangedEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.HostChangedEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.MeetingEventManager;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.MicStatusChangeEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.MuteAllEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.MuteEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.RecordEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.RefreshRoomUserEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.ShareScreenEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.SocketConnectEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.SpeakerStatusChangedEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.UserJoinEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.UserLeaveEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.VolumeEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.socket.IMeetingManager;
import com.ss.video.rtc.demo.meetingrtcdemo.core.socket.MeetingSocketIOManager;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.MeetingUserInfo;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.SettingsConfigEntity;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.VideoCanvasWrapper;
import com.ss.video.rtc.demo.meetingrtcdemo.resource.Constants;
import com.ss.video.rtc.engine.SubscribeConfig;
import com.ss.video.rtc.engine.VideoCanvas;
import com.ss.video.rtc.engine.handler.IRtcEngineEventHandler;
import com.ss.video.rtc.engine.video.ScreenSharingParameters;

import org.greenrobot.eventbus.Subscribe;
import org.greenrobot.eventbus.ThreadMode;

import java.util.Arrays;
import java.util.Comparator;
import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.UUID;

import static com.ss.video.rtc.demo.meetingrtcdemo.resource.Constants.REQUEST_CODE_OF_SCREEN_SHARING;

/**
 * Meeting Data Manager.
 * The class manager all data of meeting.while the class is bridge between user and server.
 * The class transfers User's requests and movements to server.
 * When data update,the class send event to UI component, then UI component should update themselves.
 */
public class MeetingDataManager {

    public static final int MAX_SHOW_USER_COUNT = 6;

    private static final String SP_KEY_MEETING_DEVICE_ID = "meeting_device_id";

    //meeting server's host
    private static final String sServerHost = "https://rtcio.bytedance.com:443";

    private static String sAppId = "";
    private static String sSelfUid = "";
    private static String sHostUid = "";
    private static String sMeetingId = "";
    private static String sScreenShareUid = null;
    private static boolean sMicStatus = false;
    private static boolean sCameraStatus = false;
    private static boolean sSpeakerStatus = false;
    private static boolean sIsRequestAppId = false;
    private static boolean sIsFrontCamera = true;
    private static boolean sIsRecordMeeting = false;

    private static final MeetingUserInfo sMyUserInfo = new MeetingUserInfo();
    private static final Map<String, MeetingUserInfo> mMeetingUserInfoMap = new LinkedHashMap<>();

    private static final Map<String, Integer> sUidVolumeMap = new LinkedHashMap<>();

    private static final List<String> sSubscribeList = new LinkedList<>();

    private static VideoCanvasWrapper sMyWrapper;
    private static final HashMap<String, VideoCanvasWrapper> sUidVideoViewMap = new LinkedHashMap<>();
    private static final HashMap<String, VideoCanvasWrapper> sUidScreenViewMap = new LinkedHashMap<>();

    private static IMeetingManager sInstance = null;

    private static SocketConnectEvent.ConnectStatus sConnectStatus = SocketConnectEvent.ConnectStatus.DISCONNECTED;

    private static MeetingDataManager sMeetingInstance = null;

    public static SettingsConfigEntity sSettingsConfigEntity = new SettingsConfigEntity();

    private static final Comparator<IRtcEngineEventHandler.AudioVolumeInfo> sVolumeComparator = new Comparator<IRtcEngineEventHandler.AudioVolumeInfo>() {

        @Override
        public int compare(IRtcEngineEventHandler.AudioVolumeInfo o1, IRtcEngineEventHandler.AudioVolumeInfo o2) {
            int volume0 = o1 == null ? 0 : o1.volume;
            int volume1 = o2 == null ? 0 : o2.volume;
            int res = Integer.compare(volume1, volume0); //声音降序
            if (res == 0) {
                String uid1 = o1 == null ? "" : o1.uid;
                String uid2 = o2 == null ? "" : o2.uid;
                return compareString(uid1, uid2); //名字升序
            } else {
                return res;
            }
        }

        public int compareString(String o1, String o2) {
            char[] chars1 = o1.toCharArray();
            char[] chars2 = o2.toCharArray();
            int i = 0;
            while (i < chars1.length && i < chars2.length) {
                if (chars1[i] > chars2[i]) {
                    return 1;
                } else if (chars1[i] < chars2[i]) {
                    return -1;
                } else {
                    i++;
                }
            }
            if (i == chars1.length) {
                return -1;
            }
            if (i == chars2.length) {
                return 1;
            }
            return 0;
        }
    };

    private MeetingDataManager() { }

    public static void init() {
        sAppId = "";
        sSelfUid = "";
        sHostUid = "";
        sMeetingId = "";
        sScreenShareUid = null;
        sMicStatus = false;
        sCameraStatus = false;
        sSpeakerStatus = false;
        sIsRequestAppId = false;
        sIsRecordMeeting = false;
        mMeetingUserInfoMap.clear();
        sLastShowingList.clear();
        sUidVolumeMap.clear();

        initDeviceId();

        sMeetingInstance = new MeetingDataManager();
        MeetingEventManager.register(sMeetingInstance);
        sInstance = getManager();

        VideoCanvas canvas = new VideoCanvas(new SurfaceView(Utilities.getApplicationContext()),
                VideoCanvas.BYTERTC_RENDER_HIDDEN, "", true);
        sMyWrapper = new VideoCanvasWrapper(canvas, true);
    }

    public static void release() {
        MeetingEventManager.unregister(sMeetingInstance);
        sMeetingInstance = null;
        sInstance.disconnect();
        sInstance = null;
    }

    public static IMeetingManager getManager() {
        if (sInstance == null) {
            synchronized (MeetingDataManager.class) {
                if (sInstance == null) {
                    sInstance = new MeetingSocketIOManager();
                    sInstance.startConnect(sServerHost);
                }
            }
        }
        return sInstance;
    }

    public static MeetingUserInfo getMyUserInfo() {
        sMyUserInfo.user_id = sSelfUid;
        sMyUserInfo.is_host = isSelfHost();
        sMyUserInfo.is_mic_on = sMicStatus;
        sMyUserInfo.is_camera_on = sCameraStatus;
        sMyUserInfo.is_sharing = !TextUtils.isEmpty(sSelfUid) && isSelf(sScreenShareUid);
        return sMyUserInfo.deepCopy(new MeetingUserInfo());
    }

    public static String getSelfId() {
        return sSelfUid;
    }

    public static boolean isRecording() {
        return  sIsRecordMeeting;
    }

    public static boolean isInMeeting() {
        return !TextUtils.isEmpty(sMeetingId);
    }

    public static boolean isSelf(String uid) {
        return !TextUtils.isEmpty(sSelfUid) && sSelfUid.equals(uid);
    }

    public static void setHostUid(String uid){
        sHostUid = uid;
    }

    public static String getHostUid() {
        return sHostUid;
    }

    public static boolean isSelfHost() {
        return !TextUtils.isEmpty(sSelfUid) && sSelfUid.equals(sHostUid);
    }

    private static void initDeviceId() {
        String uuid = SPUtils.getString(SP_KEY_MEETING_DEVICE_ID, "");
        if (TextUtils.isEmpty(uuid)) {
            uuid = UUID.randomUUID().toString();
            SPUtils.putString(SP_KEY_MEETING_DEVICE_ID, uuid);
        }
    }

    public static String getDeviceId() {
        String uuid = SPUtils.getString(SP_KEY_MEETING_DEVICE_ID, "");
        if (TextUtils.isEmpty(uuid)) {
            initDeviceId();
        }
        return SPUtils.getString(SP_KEY_MEETING_DEVICE_ID, "");
    }

    public static String getAppId() {
        return sAppId;
    }

    public static void startMeeting(String uid, String meetingId) {
        sSelfUid = uid;
        sMeetingId = meetingId;
        mMeetingUserInfoMap.clear();
        sLastShowingList.clear();
        sUidVolumeMap.clear();
    }

    public static void endMeeting() {
        if (isSelf(sScreenShareUid)) {
            stopScreenSharing();
        }
        if (!sIsFrontCamera) {
            switchCameraType(false);
        }
        if (!sSpeakerStatus) {
            switchSpeaker();
        }
        sSelfUid = "";
        sHostUid = "";
        sMeetingId = "";
        sScreenShareUid = "";
        sIsRecordMeeting = false;
        mMeetingUserInfoMap.clear();
        sUidScreenViewMap.clear();
        sUidVideoViewMap.clear();
        sLastShowingList.clear();
        sUidVolumeMap.clear();
    }

    public static void switchMic(boolean isFromUser) {
        int res = Utilities.getApplicationContext().checkPermission(
                Manifest.permission.RECORD_AUDIO, android.os.Process.myPid(), Process.myUid());
        if (res != PackageManager.PERMISSION_GRANTED) {
            if (isFromUser) {
                SafeToast.show("麦克风权限已关闭，请至设备设置页开启。");
            }
            if (!sMicStatus) {
                return;
            }
        }

        sMicStatus = !sMicStatus;
        sMyUserInfo.is_mic_on = sMicStatus;

        MeetingUserInfo aInfo = mMeetingUserInfoMap.get(sSelfUid);
        if (aInfo != null) {
            aInfo.is_mic_on = sMicStatus;
        }
        for (MeetingUserInfo info : sLastShowingList) {
            if (TextUtils.equals(info.user_id, sSelfUid)) {
                info.is_mic_on = sMicStatus;
            }
        }

        if (!TextUtils.isEmpty(sMeetingId)) {
            AppExecutors.networkIO().execute(() -> getManager().toggleMicState(sMicStatus));
        }
        MeetingEventManager.post(new MicStatusChangeEvent(sSelfUid, sMicStatus));
        MeetingRTCManager.muteLocalAudioStream(sMicStatus);
    }

    public static void switchCamera(boolean isFromUser) {
        int res = Utilities.getApplicationContext().checkPermission(
                Manifest.permission.CAMERA, android.os.Process.myPid(), Process.myUid());
        if (res != PackageManager.PERMISSION_GRANTED) {
            if (isFromUser) {
                SafeToast.show("摄像头权限已关闭，请至设备设置页开启。");
            }
            if (!sCameraStatus) {
                return;
            }
        }

        if (isSelf(sScreenShareUid) && !sCameraStatus) {
            SafeToast.show("结束共享后方可打开摄像头");
            return;
        }

        sCameraStatus = !sCameraStatus;
        sMyWrapper.showVideo = sCameraStatus;
        sMyUserInfo.is_camera_on = sCameraStatus;

        MeetingUserInfo aInfo = mMeetingUserInfoMap.get(sSelfUid);
        if (aInfo != null) {
            aInfo.is_camera_on = sCameraStatus;
        }

        for (MeetingUserInfo info : sLastShowingList) {
            if (TextUtils.equals(info.user_id, sSelfUid)) {
                info.is_camera_on = sCameraStatus;
            }
        }

        if (!TextUtils.isEmpty(sMeetingId)) {
            AppExecutors.networkIO().execute(() -> getManager().toggleCameraState(sCameraStatus));
        }
        MeetingEventManager.post(new CameraStatusChangedEvent(sSelfUid, sCameraStatus));
        MeetingRTCManager.enableLocalVideo(sCameraStatus);
    }

    public static void switchSpeaker() {
        sSpeakerStatus = !sSpeakerStatus;
        MeetingRTCManager.setEnableSpeakerphone(sSpeakerStatus);
        MeetingEventManager.post(new SpeakerStatusChangedEvent(sSpeakerStatus));
    }

    public static boolean getMicStatus() {
        return sMicStatus;
    }

    public static boolean getCameraStatus() {
        return sCameraStatus;
    }

    public static boolean hasSomeoneScreenShare() {
        return !TextUtils.isEmpty(sScreenShareUid);
    }

    public static String getScreenShareUid() {
        return sScreenShareUid;
    }

    private static final List<MeetingUserInfo> sLastShowingList = new LinkedList<>();
    public static void updateUserVolume(IRtcEngineEventHandler.AudioVolumeInfo[] speakers) {
        //sort by volume's value
        Arrays.sort(speakers, sVolumeComparator);
        if (speakers.length >= 1) {
            if (speakers[0].volume >= Constants.VOLUME_MIN_THRESHOLD) {
                speakers[0].volume = Constants.VOLUME_OVERFLOW_THRESHOLD;
            }
        }

        LinkedList<MeetingUserInfo> meetingUserInfoList = new LinkedList<>();

        MeetingUserInfo myInfo = getMyUserInfo();
        meetingUserInfoList.add(myInfo);

        sUidVolumeMap.clear();
        for (IRtcEngineEventHandler.AudioVolumeInfo info : speakers) {
            if (info == null || info.volume < Constants.VOLUME_MIN_THRESHOLD) {
                continue;
            }
            if (meetingUserInfoList.size() >= MAX_SHOW_USER_COUNT) {
                break;
            }

            sUidVolumeMap.put(info.uid, info.volume);

            if (info != null && !containsInfo(meetingUserInfoList, info.uid)) {
                MeetingUserInfo userInfo = mMeetingUserInfoMap.get(info.uid);
                if (userInfo != null) {
                    userInfo.volume = info.volume;
                    meetingUserInfoList.add(userInfo);
                }
            }
        }

        if (sUidVolumeMap.containsKey(sSelfUid) && TextUtils.equals(sSelfUid, meetingUserInfoList.get(0).user_id)) {
            meetingUserInfoList.get(0).volume = sUidVolumeMap.get(sSelfUid);
        }

        if (!sUidVolumeMap.isEmpty()) {
            MLog.d("updateUserVolume", "" + sUidVolumeMap);
            MeetingEventManager.post(new VolumeEvent(new LinkedHashMap<>(sUidVolumeMap)));
        }

        for (MeetingUserInfo info : sLastShowingList) {
            if (meetingUserInfoList.size() >= MAX_SHOW_USER_COUNT) {
                break;
            }
            if (info != null && !containsInfo(meetingUserInfoList, info.user_id)) {
                MeetingUserInfo userInfo = mMeetingUserInfoMap.get(info.user_id);
                if (userInfo != null) {
                    userInfo.volume = 0;
                    meetingUserInfoList.add(userInfo);
                }
            }
        }

        for (MeetingUserInfo info : mMeetingUserInfoMap.values()) {
            if (meetingUserInfoList.size() >= MAX_SHOW_USER_COUNT) {
                break;
            }
            if (info != null && !containsInfo(meetingUserInfoList, info.user_id)) {
                MeetingUserInfo userInfo = mMeetingUserInfoMap.get(info.user_id);
                if (userInfo != null) {
                    userInfo.volume = 0;
                    meetingUserInfoList.add(userInfo);
                }
            }
        }

        LinkedList<String> uidList = new LinkedList<>();
        String uid;
        for (MeetingUserInfo info : meetingUserInfoList) {
            uid = info.user_id;
            uidList.add(uid);

            if (!sSubscribeList.contains(info.user_id)) {
                MeetingRTCManager.subscribeStream(uid, new SubscribeConfig(
                        false, true, true, 0));
            }
        }
        for (String subs : sSubscribeList) {
            if (!uidList.contains(subs)) {
                MeetingRTCManager.unSubscribe(subs, false);
            }
        }
        sSubscribeList.clear();
        sSubscribeList.addAll(uidList);

        if (sIsRecordMeeting && isSelfHost()) {
            AppExecutors.networkIO().execute(() -> {
                getManager().updateRecordLayout(uidList, sScreenShareUid);
            });
        }
        sLastShowingList.clear();
        MeetingUserInfo temp;
        for (String userId : uidList) {
            temp = mMeetingUserInfoMap.get(userId);
            if (temp != null) {
                sLastShowingList.add(temp);
            }
        }

        MeetingEventManager.post(new RefreshRoomUserEvent());
    }

    private static boolean containsInfo(List<MeetingUserInfo> infoList, String uid) {
        if (infoList == null || infoList.isEmpty()) {
            return false;
        }
        for (MeetingUserInfo info : infoList) {
            if (info != null) {
                if (info.user_id == null && uid == null) {
                    return true;
                }
                if (info.user_id != null && info.user_id.equals(uid)) {
                    return true;
                }
            }
        }
        return false;
    }

    public static int getUserVolume(String uid) {
        Object volume = sUidVolumeMap.get(uid);
        return volume == null ? 0 : (int) volume;
    }

    public static void initRoomUsers() {
        AppExecutors.networkIO().submit(() -> {
            List<MeetingUserInfo> infoList = sInstance.getMeetingParticipantsInfo();

            synchronized (mMeetingUserInfoMap) {
                mMeetingUserInfoMap.clear();
                for (MeetingUserInfo info : infoList) {
                    mMeetingUserInfoMap.put(info.user_id, info);
                    if (info.is_sharing) {
                        sScreenShareUid = info.user_id;
                    }
                    if (info.is_host) {
                        sHostUid = info.user_id;
                    }
                }

                int max = Math.min(infoList.size(), MAX_SHOW_USER_COUNT);
                MeetingUserInfo info = null;
                for (int i = 0; i < max; i++) {
                    info = infoList.get(i);
                    if (info == null) {
                        continue;
                    }
                    sLastShowingList.add(info);
                    MeetingRTCManager.subscribeStream(info.user_id,
                            new SubscribeConfig(false, true, true, 0));
                    addOrUpdateRenderView(info.user_id, true);

                    if (info.is_sharing) {
                        addOrUpdateScreenView(info.user_id, true);
                    }
                }

                for (MeetingUserInfo temp : sLastShowingList) {
                    if (temp != null && isSelf(temp.user_id)) {
                        info = temp;
                        sLastShowingList.remove(temp);
                        break;
                    }
                }
                if (info != null) {
                    sLastShowingList.add(0, info);
                }
            }
            MeetingEventManager.post(new RefreshRoomUserEvent());
        });
    }

    public static boolean isUserMute(String uid) {
        MeetingUserInfo info = mMeetingUserInfoMap.get(uid);
        return info == null || !(info.is_mic_on);
    }

    public static List<MeetingUserInfo> getAllMeetingUserInfoList() {
        return new LinkedList<>(mMeetingUserInfoMap.values());
    }

    public static List<MeetingUserInfo> getMeetingShowingUserInfoList() {
        return new LinkedList<>(sLastShowingList);
    }

    public static MeetingUserInfo getSecondUserInfo() {
       for (MeetingUserInfo info : sLastShowingList) {
           if (info != null && !isSelf(info.user_id)) {
               return info;
           }
       }
       return null;
    }

    public static VideoCanvasWrapper getMyRenderView() {
        return sMyWrapper;
    }

    public static VideoCanvasWrapper getRenderView(String uid) {
        if (isSelf(uid)) {
            return sMyWrapper;
        } else {
            return sUidVideoViewMap.get(uid);
        }
    }

    public static VideoCanvasWrapper addOrUpdateRenderView(String uid, boolean hasVideo) {
        if (TextUtils.isEmpty(uid)) {
            return null;
        }
        VideoCanvasWrapper wrapper = sUidVideoViewMap.get(uid);
        if (wrapper == null) {
            VideoCanvas canvas = new VideoCanvas(new SurfaceView(Utilities.getApplicationContext()),
                    VideoCanvas.BYTERTC_RENDER_HIDDEN, uid, false);
            wrapper = new VideoCanvasWrapper(canvas, hasVideo);
        } else {
            wrapper.showVideo = hasVideo;
        }
        sUidVideoViewMap.put(uid, wrapper);
        return wrapper;
    }

    public static VideoCanvasWrapper getScreenView() {
        return sUidScreenViewMap.get(sScreenShareUid);
    }

    public static VideoCanvasWrapper addOrUpdateScreenView(String uid, boolean hasVideo) {
        if (TextUtils.isEmpty(uid)) {
            return null;
        }
        sScreenShareUid = uid;
        VideoCanvasWrapper wrapper = sUidScreenViewMap.get(uid);
        if (wrapper == null) {
            VideoCanvas canvas = new VideoCanvas(new SurfaceView(Utilities.getApplicationContext()),
                    VideoCanvas.BYTERTC_RENDER_FIT, uid, true);
            wrapper = new VideoCanvasWrapper(canvas, hasVideo);
        } else {
            wrapper.showVideo = hasVideo;
        }

        MeetingRTCManager.subscribeStream(uid, new SubscribeConfig(true, true ,false, 0));
        MeetingRTCManager.setupRemoteScreen(wrapper.videoCanvas);

        sUidScreenViewMap.put(uid, wrapper);
        return wrapper;
    }

    public static void removeScreenView(String uid) {
        if (sScreenShareUid.equals(uid)) {
            sScreenShareUid = "";
        }
        sUidScreenViewMap.remove(uid);
        MeetingRTCManager.unSubscribe(uid, true);
    }

    public static void startScreenSharing(Activity activity) {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
            MediaProjectionManager manager = (MediaProjectionManager) Utilities.getApplicationContext().getSystemService(Context.MEDIA_PROJECTION_SERVICE);
            if (manager != null) {
                activity.startActivityForResult(manager.createScreenCaptureIntent(), REQUEST_CODE_OF_SCREEN_SHARING);
            } else {
                SafeToast.show("此手机无法开启屏幕分享");
            }
        } else {
            SafeToast.show("当前系统版本过低，无法支持屏幕共享");
        }
    }

    public static void onScreenSharingIntent(int resultCode, Intent intent) {
        if (resultCode == Activity.RESULT_OK) {
            ScreenSharingParameters parameters = new ScreenSharingParameters();
            Pair<Integer, Integer> resolution = sSettingsConfigEntity.getResolution();
            parameters.maxWidth = resolution.first;
            parameters.maxHeight = resolution.second;
            parameters.frameRate = sSettingsConfigEntity.getFrameRate();
            parameters.bitrate = sSettingsConfigEntity.getBitRate();

            sScreenShareUid = sSelfUid;
            sMyUserInfo.is_camera_on = false;
            sMyUserInfo.is_sharing = true;

            if (sCameraStatus) {
                switchCamera(false);
                MeetingEventManager.post(new CameraStatusChangedEvent(sSelfUid, false));
            }

            MeetingEventManager.post(new ShareScreenEvent(true, sSelfUid));
            MeetingRTCManager.startScreenSharing(intent, parameters);
            AppExecutors.networkIO().execute(() -> {
                getManager().startScreenShare();
            });
        } else {
            SafeToast.show("开启屏幕共享失败");
        }
    }

    public static void stopScreenSharing() {
        sScreenShareUid = null;
        sMyUserInfo.is_camera_on = sCameraStatus;
        sMyUserInfo.is_sharing = false;

        MeetingEventManager.post(new ShareScreenEvent(false, sSelfUid));
        MeetingRTCManager.stopScreenSharing();
        AppExecutors.networkIO().execute(() -> {
            getManager().stopScreenShare();
        });

        MeetingRTCManager.enableLocalVideo(sCameraStatus);
        MeetingEventManager.post(new CameraStatusChangedEvent(sSelfUid, sCameraStatus));
    }

    public static void switchCameraType(boolean isFromUser) {
        int res = Utilities.getApplicationContext().checkPermission(
                Manifest.permission.CAMERA, android.os.Process.myPid(), Process.myUid());
        if (res != PackageManager.PERMISSION_GRANTED) {
            if (isFromUser) {
                SafeToast.show("摄像头权限已关闭，请至设备设置页开启。");
            }
            return;
        }
        if (sCameraStatus) {
            MeetingRTCManager.switchCamera();
            sIsFrontCamera = !sIsFrontCamera;
        }
    }

    public static void startMeetingRecord() {
        if (sIsRecordMeeting) {
            return;
        }
        sIsRecordMeeting = true;
        AppExecutors.networkIO().execute(() -> {
            LinkedList<String> uidList = new LinkedList<>();
            for (MeetingUserInfo info : sLastShowingList) {
                uidList.add(info.user_id);
            }
            getManager().startMeetingRecord(uidList, sScreenShareUid);
        });
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onUserJoined(UserJoinEvent event) {
        if (event == null) {
            return;
        }
        MeetingUserInfo userInfo = event.meetingUserInfo;
        if (userInfo == null || TextUtils.isEmpty(userInfo.user_id)) {
            return;
        }

        Log.d("onUserJoined", userInfo.toString());

        mMeetingUserInfoMap.put(userInfo.user_id, userInfo);

        if (!containsInfo(sLastShowingList, userInfo.user_id) && sLastShowingList.size() < MAX_SHOW_USER_COUNT) {
            sLastShowingList.add(userInfo);
            MeetingRTCManager.subscribeStream(userInfo.user_id, new SubscribeConfig(false, true, true, 0));
            addOrUpdateRenderView(userInfo.user_id, userInfo.is_camera_on);
            MeetingEventManager.post(new RefreshRoomUserEvent());
        }
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onUserLeave(UserLeaveEvent event) {
        if (event == null) {
            return;
        }
        MeetingUserInfo userInfo = event.meetingUserInfo;
        if (userInfo == null || TextUtils.isEmpty(userInfo.user_id)) {
            return;
        }

        String uid = userInfo.user_id;
        mMeetingUserInfoMap.remove(uid);
        for (MeetingUserInfo info : sLastShowingList) {
            if (info != null && TextUtils.equals(info.user_id, uid)) {
                sLastShowingList.remove(info);
                MeetingEventManager.post(new RefreshRoomUserEvent());
                break;
            }
        }
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onHostChangedEvent(HostChangedEvent event) {
        sHostUid = event.currentUid;
        MeetingUserInfo aFormerInfo = mMeetingUserInfoMap.get(event.formerUid);
        if (aFormerInfo != null) {
            aFormerInfo.is_host = false;
        }
        MeetingUserInfo aCurrentInfo = mMeetingUserInfoMap.get(event.currentUid);
        if (aCurrentInfo != null) {
            aCurrentInfo.is_host = true;
        }

        for (MeetingUserInfo info : sLastShowingList) {
            if (info != null && TextUtils.equals(info.user_id, event.formerUid)) {
                info.is_host = false;
            }
            if (info != null && TextUtils.equals(info.user_id, event.currentUid)) {
                info.is_host = true;
            }
        }
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onShareScreenEvent(ShareScreenEvent event) {
        MeetingUserInfo aInfo = mMeetingUserInfoMap.get(sScreenShareUid);
        if (aInfo != null) {
            aInfo.is_sharing = false;
        }
        MeetingUserInfo sInfo = mMeetingUserInfoMap.get(sScreenShareUid);
        if (sInfo != null) {
            sInfo.is_sharing = false;
        }
        sScreenShareUid = event.isStart ? event.shareUid : "";

        MeetingUserInfo aaInfo = mMeetingUserInfoMap.get(event.shareUid);
        if (aaInfo != null) {
            aaInfo.is_sharing = event.isStart;
        }
        MeetingUserInfo ssInfo = mMeetingUserInfoMap.get(event.shareUid);
        if (ssInfo != null) {
            ssInfo.is_sharing = event.isStart;
        }
        if (event.isStart) {
            addOrUpdateScreenView(sScreenShareUid, true);
        }
        MeetingEventManager.post(new RefreshRoomUserEvent());
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onMuteEvent(MuteEvent event) {
        if (!sMicStatus) {
            return;
        }
        SafeToast.show("你已被主持人静音");

        switchMic(false);
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onMicStatusChangeEvent(MicStatusChangeEvent event) {
        String uid = event.uid;
        if (TextUtils.isEmpty(uid)) {
            return;
        }

        for (MeetingUserInfo info : sLastShowingList) {
            if (info != null && TextUtils.equals(info.user_id, uid)) {
                info.is_mic_on = event.status;
            }
        }
        MeetingUserInfo aInfo = mMeetingUserInfoMap.get(uid);
        if (aInfo != null) {
            aInfo.is_mic_on = event.status;
        }
        for (MeetingUserInfo info : sLastShowingList) {
            if (info != null && uid.equals(info.user_id)) {
                info.is_mic_on = event.status;
            }
        }
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onCameraStatusChangedEvent(CameraStatusChangedEvent event) {
        String uid = event.uid;
        if (TextUtils.isEmpty(uid)) {
            return;
        }
        for (MeetingUserInfo info : sLastShowingList) {
            if (info != null && TextUtils.equals(info.user_id, uid)) {
                info.is_camera_on = event.status;
            }
        }
        MeetingUserInfo aInfo = mMeetingUserInfoMap.get(uid);
        if (aInfo != null) {
            aInfo.is_camera_on = event.status;
        }
        for (MeetingUserInfo info : sLastShowingList) {
            if (info != null && uid.equals(info.user_id)) {
                info.is_camera_on = event.status;
            }
        }
        MeetingEventManager.post(new RefreshRoomUserEvent());
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onMuteAllEvent(MuteAllEvent event) {
        for (MeetingUserInfo info : mMeetingUserInfoMap.values()) {
            if (!TextUtils.isEmpty(sHostUid) && info != null && !sHostUid.equals(info.user_id)) {
                info.is_mic_on = false;
            }
        }
        for (MeetingUserInfo info : sLastShowingList) {
            if (!TextUtils.isEmpty(sHostUid) && info != null && !sHostUid.equals(info.user_id)) {
                info.is_mic_on = false;
            }
        }
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
                if (!sCameraStatus) {
                    switchCamera(false);
                }
                if (!sMicStatus) {
                    switchMic(false);
                }
            }
        });
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onRecordEvent(RecordEvent event) {
        sIsRecordMeeting = event.isStart;
    }
}
