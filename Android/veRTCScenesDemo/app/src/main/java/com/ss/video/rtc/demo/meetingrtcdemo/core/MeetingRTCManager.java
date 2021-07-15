package com.ss.video.rtc.demo.meetingrtcdemo.core;

import android.content.Intent;
import android.text.TextUtils;
import android.util.Log;
import android.util.Pair;

import com.ss.video.rtc.demo.basic_module.utils.AppExecutors;
import com.ss.video.rtc.demo.basic_module.utils.Utilities;
import com.ss.video.rtc.demo.meetingrtcdemo.common.MLog;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.MeetingEventManager;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.RTCStatEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.RTCVolumeEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.MeetingUserInfo;
import com.ss.video.rtc.demo.meetingrtcdemo.resource.Constants;
import com.ss.video.rtc.engine.ByteStream;
import com.ss.video.rtc.engine.PublisherConfiguration;
import com.ss.video.rtc.engine.RtcEngine;
import com.ss.video.rtc.engine.SubscribeConfig;
import com.ss.video.rtc.engine.VideoCanvas;
import com.ss.video.rtc.engine.VideoStreamDescription;
import com.ss.video.rtc.engine.handler.IRtcEngineEventHandler;
import com.ss.video.rtc.engine.video.ScreenSharingParameters;

import java.util.List;

import static com.ss.video.rtc.engine.RtcEngine.SubscribeFallbackOptions.SUBSCRIBE_FALLBACK_OPTIONS_AUDIO_ONLY;

public class MeetingRTCManager {

    private static RtcEngine sInstance = null;

    private static final IRtcEngineEventHandler sRtcEventHandler = new IRtcEngineEventHandler() {

        private RemoteAudioStats mAudioStats = new RemoteAudioStats();
        private RemoteVideoStats mVideoStats = new RemoteVideoStats();

        @Override
        public void onStreamAdd(ByteStream stream) {
            super.onStreamAdd(stream);
            AppExecutors.mainThread().execute(() -> {
                if (stream == null || TextUtils.isEmpty(stream.userId)) {
                    return;
                }
                MLog.d("onStreamAdd", stream.toString());
                String screenUid = MeetingDataManager.getScreenShareUid();
                if (TextUtils.equals(screenUid, stream.userId) && stream.isScreen) {
                    MeetingDataManager.addOrUpdateScreenView(stream.userId, true);
                    return;
                }
                List<MeetingUserInfo> users = MeetingDataManager.getMeetingShowingUserInfoList();
                if (users == null || users.isEmpty()) {
                    return;
                }
                for (MeetingUserInfo info : users) {
                    if (info == null) {
                        continue;
                    }
                    if (TextUtils.equals(stream.userId, info.user_id)) {
                        SubscribeConfig config = new SubscribeConfig(stream.isScreen, true, true, 0);
                        subscribeStream(stream.userId, config);
                        return;
                    }
                }
            });
        }

        @Override
        public void onRtcStats(IRtcEngineEventHandler.RtcStats stats) {
            if (!MeetingDataManager.sSettingsConfigEntity.enableLog) {
                return;
            }
            Pair<Integer, Integer> resolution = MeetingDataManager.sSettingsConfigEntity.getResolution();
            int frameRate = MeetingDataManager.sSettingsConfigEntity.getFrameRate();
            StringBuilder sb = new StringBuilder();
            sb.append("[LOCAL]").append("\n");
            sb.append("RES: ").append(resolution.second).append("*").append(resolution.first).append("\n");
            sb.append("FPS: ").append(frameRate).append("\n");
            sb.append("BIT(VIDEO): ").append(stats.txVideoKBitRate).append("kbps").append("\n");
            sb.append("BIT(AUDIO): ").append(stats.txAudioKBitRate).append("kbps").append("\n");
            sb.append("\n");
            sb.append("[REMOTE]").append("\n");
            sb.append("RTT(VIDEO): ").append(mVideoStats.rtt).append("ms").append("\n");
            sb.append("RTT(AUDIO): ").append(mAudioStats.rtt).append("ms").append("\n");
            sb.append("CPU: ").append(stats.cpuAppUsage).append("%|").append(stats.cpuTotalUsage).append("%").append("\n");
            sb.append("BIT(VIDEO): ").append(mVideoStats.receivedKBitrate).append("kbps").append("\n");
            sb.append("BIT(AUDIO): ").append(mAudioStats.receivedKBitrate).append("kbps").append("\n");
            sb.append("RES: ").append(mVideoStats.width).append("*").append(mVideoStats.height).append("\n");
            sb.append("FPS: ").append(mVideoStats.rendererOutputFrameRate).append("-").append(mVideoStats.receivedKBitrate).append("\n");
            sb.append("LOSS（VIDEO）: ").append(mVideoStats.videoLossRate).append("%").append("\n");
            sb.append("LOSS(AUDIO): ").append(mAudioStats.audioLossRate).append("%").append("\n");
            MeetingEventManager.post(new RTCStatEvent(sb.toString()));
        }

        @Override
        public void onRemoteAudioStats(RemoteAudioStats stats) {
            super.onRemoteAudioStats(stats);
            mAudioStats = stats;
        }

        @Override
        public void onRemoteVideoStats(RemoteVideoStats stats) {
            super.onRemoteVideoStats(stats);
            mVideoStats = stats;
        }

        @Override
        public void onLocalAudioStats(LocalAudioStats stats) {
            super.onLocalAudioStats(stats);
            MeetingEventManager.post(stats);
        }

        @Override
        public void onAudioVolumeIndication(IRtcEngineEventHandler.AudioVolumeInfo[] speakers, int totalVolume) {
            if (speakers == null || speakers.length == 0) {
                return;
            }
            MeetingEventManager.post(new RTCVolumeEvent(speakers, totalVolume));
        }

        @Override
        public void onError(int err) {
            Log.e("RTCManager", "onError:" + err);
        }
    };

    public static void createEngine(String appId) {
        if (sInstance == null) {
            RtcEngine.setLoggerMessageLevel(IRtcEngineEventHandler.RtcLogLevel.RTC_LOG_LEVEL_ERROR);

            RtcEngine.setDeviceId(MeetingDataManager.getDeviceId());

            RtcEngine.ByteRtcEnv env = RtcEngine.ByteRtcEnv.kByteRtcEnvProduct;
            RtcEngine.setEnv(env);

            try {
                sInstance = RtcEngine.create(Utilities.getApplicationContext(), appId, sRtcEventHandler);
                enableAutoSubscribe(true, false);
                setRemoteSubscribeFallbackOption(SUBSCRIBE_FALLBACK_OPTIONS_AUDIO_ONLY);
                setLocalVideoMirrorMode(RtcEngine.VIDEO_MIRROR_MODE_ENABLED);
                enableAudioVolumeIndication(Constants.VOLUME_INTERVAL_MS, Constants.VOLUME_SMOOTH);
            } catch (Exception e) {
                MLog.e("createEngine", "", e);
            }
        }
    }

    public static void destroyEngine() {
        MLog.d("destroyEngine", "");
        if (sInstance == null) {
            return;
        }
        sInstance = null;
        RtcEngine.destroy();
    }

    public static void enableAutoSubscribe(boolean audioSubscribe, boolean videoSubscribe) {
        MLog.d("enableAutoSubscribe", "audioSubscribe :" + audioSubscribe +  ", videoSubscribe: " + videoSubscribe);
        if (sInstance == null) {
            return;
        }
        RtcEngine.SubscribeMode audioMode = audioSubscribe ? RtcEngine.SubscribeMode.AUTO_SUBSCRIBE_MODE : RtcEngine.SubscribeMode.MANUAL_SUBSCRIBE_MODE;
        RtcEngine.SubscribeMode videoMode = videoSubscribe ? RtcEngine.SubscribeMode.AUTO_SUBSCRIBE_MODE : RtcEngine.SubscribeMode.MANUAL_SUBSCRIBE_MODE;
        sInstance.enableAutoSubscribe(audioMode, videoMode);
    }

    public static void muteLocalAudioStream(boolean enable) {
        MLog.d("muteLocalAudioStream", "");
        if (sInstance == null) {
            return;
        }
        sInstance.muteLocalAudioStream(!enable);
    }

    public static void enableLocalVideo(boolean enable) {
        MLog.d("enableLocalVideo", "");
        if (sInstance == null) {
            return;
        }
        sInstance.enableLocalVideo(enable);
    }

    public static void startPreview() {
        MLog.d("startPreview", "");
        if (sInstance == null) {
            return;
        }
        sInstance.startPreview();
    }

    public static void stopPreview() {
        MLog.d("stopPreview", "");
        if (sInstance == null) {
            return;
        }
        sInstance.stopPreview();
    }

    public static void setLocalVideoMirrorMode(int mode) {
        MLog.d("setLocalVideoMirrorMode", "" + mode);
        if (sInstance == null) {
            return;
        }
        sInstance.setLocalVideoMirrorMode(mode);
    }

    public static void setVideoProfiles(VideoStreamDescription[] descriptions) {
        MLog.d("setVideoProfiles", "");
        if (sInstance == null) {
            return;
        }
        sInstance.setVideoProfiles(descriptions);
    }

    public static void setupLocalVideo(VideoCanvas canvas) {
        MLog.d("setupLocalVideo", "");
        if (sInstance == null) {
            return;
        }
        sInstance.setupLocalVideo(canvas);
    }

    public static void setupRemoteVideo(VideoCanvas canvas) {
        MLog.d("setupRemoteVideo", ":" + canvas.uid);
        if (sInstance == null) {
            return;
        }
        sInstance.setupRemoteVideo(canvas);
    }

    public static void setupRemoteScreen(VideoCanvas canvas) {
        MLog.d("setupRemoteScreen", ":" + canvas.uid);
        if (sInstance == null) {
            return;
        }
        sInstance.setupRemoteScreen(canvas);
    }

    public static void joinChannel(String token, String roomId, PublisherConfiguration configuration, String uid) {
        MLog.d("joinChannel", "token:" + token + " roomId:" + roomId + " uid:" + uid);
        if (sInstance == null) {
            return;
        }
        sInstance.joinChannel(token, roomId, configuration, uid);
    }

    public static void leaveChannel() {
        MLog.d("leaveChannel", "");
        if (sInstance == null) {
            return;
        }
        sInstance.leaveChannel();
    }

    public static void switchCamera() {
        MLog.d("switchCamera", "");
        if (sInstance == null) {
            return;
        }
        sInstance.switchCamera();
    }

    public static void setEnableSpeakerphone(boolean open) {
        MLog.d("setEnableSpeakerphone", "open");
        if (sInstance == null) {
            return;
        }
        sInstance.setEnableSpeakerphone(open);
    }

    public static void enableAudioVolumeIndication(int interval, int smooth) {
        MLog.d("enableAudioVolumeIndication", "" + interval + ":" + smooth);
        if (sInstance == null) {
            return;
        }
        sInstance.enableAudioVolumeIndication(interval, smooth);
    }

    public static void subscribeStream(String uid, SubscribeConfig config) {
        MLog.d("subscribeStream", "" + uid + ":" + config.toString());
        if (sInstance == null) {
            return;
        }
        sInstance.subscribeStream(uid, config);
    }

    public static void unSubscribe(String uid, boolean isScreen) {
        MLog.d("unSubscribe", "" + uid + ":" + isScreen);
        if (sInstance == null) {
            return;
        }
        sInstance.unSubscribe(uid, isScreen);
    }

    public static void setRemoteSubscribeFallbackOption(RtcEngine.SubscribeFallbackOptions options) {
        MLog.d("setRemoteSubscribeFallbackOption", "" + options.toString());
        if (sInstance == null) {
            return;
        }
        sInstance.setRemoteSubscribeFallbackOption(options);
    }

    public static int startScreenSharing(Intent intent, ScreenSharingParameters params) {
        int res;
        if (sInstance != null) {
            res = sInstance.startScreenSharing(intent, params);
        } else {
            res = -1;
        }
        MLog.d("startScreenCapture", "" + res);
        return res;
    }

    public static int stopScreenSharing() {
        int res;
        if (sInstance != null) {
            res = sInstance.stopScreenSharing();
        } else {
            res = -1;
        }
        MLog.d("stopScreenSharing", "" + res);
        return res;
    }

    public static int updateScreenSharingParameters(ScreenSharingParameters params) {
        int res;
        if (sInstance != null) {
            res = sInstance.updateScreenSharingParameters(params);
        } else {
            res = -1;
        }
        MLog.d("updateScreenSharingParameters", "" + params + ":" + res);
        return res;
    }

    public static int feedback(int grade, int type, String description) {
//        int res = RtcEngine.feedback(Utilities.getApplicationContext(), grade, type, description);
        int res = 0;
        MLog.d("feedback", "grade:" + grade + ", " + "type: " + type + ", " + "description:" + description + ", " + "res: "+ res);
        return res;
    }
}
