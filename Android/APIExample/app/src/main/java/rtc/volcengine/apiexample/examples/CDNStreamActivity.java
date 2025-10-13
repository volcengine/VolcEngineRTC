package rtc.volcengine.apiexample.examples;

import androidx.appcompat.widget.AppCompatButton;

import android.os.Bundle;
import android.text.TextUtils;
import android.util.Log;
import android.view.TextureView;
import android.widget.Button;
import android.widget.EditText;
import android.widget.FrameLayout;
import android.widget.Spinner;

import com.ss.bytertc.engine.RTCRoom;
import com.ss.bytertc.engine.RTCRoomConfig;
import com.ss.bytertc.engine.RTCEngine;
import com.ss.bytertc.engine.UserInfo;
import com.ss.bytertc.engine.VideoCanvas;
import com.ss.bytertc.engine.data.EngineConfig;;
import com.ss.bytertc.engine.data.StreamInfo;
import com.ss.bytertc.engine.handler.IRTCRoomEventHandler;
import com.ss.bytertc.engine.handler.IRTCEngineEventHandler;
import com.ss.bytertc.engine.live.MixedStreamConfig;
import com.ss.bytertc.engine.live.MixedStreamLayoutRegionConfig;
import com.ss.bytertc.engine.live.MixedStreamMediaType;
import com.ss.bytertc.engine.live.MixedStreamPushTargetConfig;
import com.ss.bytertc.engine.live.MixedStreamPushTargetType;
import com.ss.bytertc.engine.live.MixedStreamRenderMode;
import com.ss.bytertc.engine.live.MixedStreamTaskErrorCode;
import com.ss.bytertc.engine.live.MixedStreamTaskEvent;
import com.ss.bytertc.engine.live.MixedStreamTaskInfo;
import com.ss.bytertc.engine.live.MixedStreamVideoType;
import com.ss.bytertc.engine.type.ChannelProfile;
import com.ss.bytertc.engine.type.RTCRoomStats;

import java.util.ArrayList;
import java.util.HashMap;

import rtc.volcengine.apiexample.BaseActivity;
import rtc.volcengine.apiexample.R;
import rtc.volcengine.apiexample.Utils.MD5Utils;
import rtc.volcengine.apiexample.Utils.ToastUtil;
import rtc.volcengine.apiexample.common.Constants;
import rtc.volcengine.apiexample.common.annotations.ApiExample;

/**
 * 功能名称： ByteRTC 推流到CDN
 * 功能简单描述：对于一个音视频通话，你可以将其中的多路音视频流合为一路，并将合并得到的音视频流推送到指定的推流地址（通常是 CDN 地址）
 *
 * 此功能涉及的API及回调：
 *     createRTCEngine 创建引擎
 *     destroyRTCEngine 销毁引擎
 *     startAudioCapture 开启音频采集
 *     startVideoCapture 开启视频采集
 *     createRTCRoom 创建RTC房间
 *     joinRoom 进入RTC房间
 *     startPushMixedStreamToCDN 开始CDN推流
 *     updatePushMixedStreamToCDN 更新推流参数
 *     stopPushStreamToCDN 关闭CDN推流

 *     leaveRoom 离开RTC房间
 *     destroy 销毁RTC房间
 *
 *
 *
 *     onRoomStateChanged 房间状态回调
 *     onLeaveRoom 离房回调
 *     onUserJoined 用户加入回调
 *     onUserLeave  用户离开回调
 *     onUserPublishStream 用户发流回调
 *     onUserUnpublishStream 用户停止发流回调
 *

 *
 * Demo实现时的逻辑
 *    本Demo演示功能：合流转推，
 *       展示了1*4和2*2两种布局模式
 *       房间内最多展示4路流
 *    为了展示简单，所有功能的token都由客户端生成，请在真正接入时视具体情况而定
 */
@ApiExample(name = "推流到CDN", order = 8)
public class CDNStreamActivity extends BaseActivity {
    private static final String TAG = "CDNStreamActivity";
    private String roomID;
    private static final String CDN_TASK_ID = "111";
    private FrameLayout localViewContainer;
    private Button btnJoinRoom;
    private EditText roomIdInput;
    private FrameLayout[] remoteContainers = new FrameLayout[3];
    private HashMap<String, Integer> remoteUserViewMap = new HashMap<>();
    private ArrayList<String> userNameList = new ArrayList<>();
    private boolean[] isRemoteViewUsed = new boolean[3];
    private EditText cdnAddressInput;
    private EditText layoutColorInput;
    private Spinner layoutMode;
    private AppCompatButton btnStartPush, btnUpdatePushConfig, btnStopPush;
    private RTCEngine rtcVideo;
    private RTCRoom rtcRoom;

    private MixedStreamConfig mixedStreamConfig;
    private MixedStreamPushTargetConfig targetConfig;
    private boolean isJoined;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_cdn_stream);
        setTitle(R.string.title_cdn_stream);
        initUI();

        // 创建引擎
        EngineConfig config = new EngineConfig();
        config.context = this;
        config.appID = Constants.APP_ID;
        rtcVideo = RTCEngine.createRTCEngine(config, videoEventHandler);// 开启音频采集
        // 设置本端渲染视图
        setLocalRenderView();
        // 开启音视频采集
        rtcVideo.startVideoCapture();
        rtcVideo.startAudioCapture();

        userNameList.add(localUid);

        mixedStreamConfig = MixedStreamConfig.defaultMixedStreamConfig();
        targetConfig = new MixedStreamPushTargetConfig();
    }

    private void initUI() {
        localViewContainer = findViewById(R.id.local_view_container);
        remoteContainers[0] = findViewById(R.id.remote_view_container1);
        remoteContainers[1] = findViewById(R.id.remote_view_container2);
        remoteContainers[2] = findViewById(R.id.remote_view_container3);
        cdnAddressInput = findViewById(R.id.cdn_address_input);
        layoutColorInput = findViewById(R.id.layout_color_input);
        layoutMode = findViewById(R.id.layout_mode_spinner);
        btnJoinRoom = findViewById(R.id.btn_join_room);
        roomIdInput = findViewById(R.id.room_id_input);

        btnStartPush = findViewById(R.id.btn_start_push);
        btnUpdatePushConfig = findViewById(R.id.btn_update_push_config);
        btnStopPush = findViewById(R.id.btn_stop_push);

        btnStartPush.setOnClickListener(v -> startPushCDNStream());
        btnUpdatePushConfig.setOnClickListener(v -> updateCDNStreamConfig());
        btnStopPush.setOnClickListener(v -> stopPushCDNStream());
        btnJoinRoom.setOnClickListener(v -> {
            String roomId = roomIdInput.getText().toString();
            if (isJoined) {
                leaveRoom();

                isJoined = false;
                btnJoinRoom.setText("进入房间");
                return;
            }
            if (TextUtils.isEmpty(roomId)) {
                ToastUtil.showAlert(this, "roomID is null");
                return;
            }
            joinRoom(roomId);
            isJoined = true;
            btnJoinRoom.setText("退出房间");

            cdnAddressInput.setText(getRTMPAddr(roomId, CDN_TASK_ID));
        });
    }

    /**
     * 设置本地渲染视图，支持TextureView和SurfaceView
     */
    private void setLocalRenderView() {
        TextureView textureView = new TextureView(this);
        localViewContainer.removeAllViews();
        localViewContainer.addView(textureView);

        VideoCanvas videoCanvas = new VideoCanvas();
        videoCanvas.renderView = textureView;
        videoCanvas.renderMode = VideoCanvas.RENDER_MODE_HIDDEN;
        // 设置本地视频渲染视图
        rtcVideo.setLocalVideoCanvas(videoCanvas);
    }

    private void setRemoteRenderView(String uid, String streamId) {
        for (int i = 0; i < isRemoteViewUsed.length; i++) {
            if (!isRemoteViewUsed[i]) {
                isRemoteViewUsed[i] = true;
                remoteUserViewMap.put(uid, i);

                TextureView textureView = new TextureView(this);
                remoteContainers[i].removeAllViews();
                remoteContainers[i].addView(textureView);


                VideoCanvas videoCanvas = new VideoCanvas();
                videoCanvas.renderView = textureView;
                videoCanvas.renderMode = VideoCanvas.RENDER_MODE_HIDDEN;
                rtcVideo.setRemoteVideoCanvas(streamId, videoCanvas);
                break;
            }
        }
    }

    private void removeRemoteView(String uid, String streamId) {
        int index = remoteUserViewMap.get(uid);
        if (index >= 0 && index < 3) {
            remoteContainers[index].removeAllViews();
            isRemoteViewUsed[index] = false;
        }
        remoteUserViewMap.remove(uid);


        rtcVideo.setRemoteVideoCanvas(streamId, null);

    }

    /**
     * 加入房间
     *
     * @param roomId
     */
    private void joinRoom(String roomId) {
        this.roomID = roomId;
        rtcRoom = rtcVideo.createRTCRoom(roomId);
        rtcRoom.setRTCRoomEventHandler(rtcRoomEventHandler);
        String token = requestRoomToken(roomId);
        // 用户信息
        UserInfo userInfo = new UserInfo(localUid, "");
        // 设置房间配置
        boolean isAutoPublishAudio = true;
        boolean isAutoPublishVideo = true;
        boolean isAutoSubscribeAudio = true;
        boolean isAutoSubscribeVideo = true;
        RTCRoomConfig roomConfig = new RTCRoomConfig(ChannelProfile.CHANNEL_PROFILE_CHAT_ROOM, "", isAutoPublishAudio, isAutoPublishVideo, isAutoSubscribeAudio, isAutoSubscribeVideo);
        // 加入房间
        rtcRoom.joinRoom(token, userInfo, true, roomConfig);
        ;
    }

    /**
     * 离开房间
     */
    private void leaveRoom() {
        stopPushCDNStream();
        if (rtcRoom != null) {
            rtcRoom.leaveRoom();
            rtcRoom.destroy();
            rtcRoom = null;
        }
    }

    /**
     * 开始推流到CDN
     */
    private void startPushCDNStream() {
        String cdnAddr = cdnAddressInput.getText().toString();
        if (cdnAddr.isEmpty()) {
            ToastUtil.showAlert(this, "cdn address is null");
            return;
        }

        targetConfig.pushCDNURL = cdnAddr;
        targetConfig.pushTargetType = MixedStreamPushTargetType.PUSH_TO_CDN;

        mixedStreamConfig.userID = localUid;
        mixedStreamConfig.roomID = roomID;
        mixedStreamConfig.backgroundColor = layoutColorInput.getText().toString();
        mixedStreamConfig.regions = getLayoutRegions();

        int ret = rtcVideo.startPushMixedStream(CDN_TASK_ID, targetConfig, mixedStreamConfig);
        if (ret != 0) {
            ToastUtil.showAlert(this, "startPushMixedStream failed, ret:" + ret);
        }
    }

    /**
     * 更新推流参数
     */
    private void updateCDNStreamConfig() {
        String cdnAddr = cdnAddressInput.getText().toString();
        if (cdnAddr.isEmpty()) {
            ToastUtil.showAlert(this, "cdn address is null");
            return;
        }
        targetConfig.pushCDNURL = cdnAddr;

        mixedStreamConfig.backgroundColor = layoutColorInput.getText().toString();
        mixedStreamConfig.regions = getLayoutRegions();
        rtcVideo.updatePushMixedStream(CDN_TASK_ID, targetConfig, mixedStreamConfig);
    }

    /**
     * 停止CDN推流
     */
    private void stopPushCDNStream() {
        rtcVideo.stopPushMixedStream(CDN_TASK_ID, MixedStreamPushTargetType.PUSH_TO_CDN);
    }

    /**
     * 设置推流到CDN上的布局
     * 此处展示了1*4、 2*2两种布局模式
     */
    private MixedStreamLayoutRegionConfig[] getLayoutRegions() {
        int width = 360;
        int height = 640;
        int userNum = userNameList.size();
        MixedStreamLayoutRegionConfig[] regions = new MixedStreamLayoutRegionConfig[userNum];
        int index = 0;
        String mode = layoutMode.getSelectedItem().toString();
        if ("1x4".equals(mode)) {
            for (String uid : userNameList) {
                MixedStreamLayoutRegionConfig region = new MixedStreamLayoutRegionConfig();
                region.roomID = roomID;
                region.userID = uid;
                region.locationX = (index * width / userNum);
                // 留出部分背景区域
                region.locationY = (50);
                region.width = (width / userNum);
                region.height = (height);
                region.alpha = (1);
                region.zOrder = (0);
                region.renderMode = (MixedStreamRenderMode.MIXED_STREAM_RENDER_MODE_HIDDEN);
                region.streamType = (MixedStreamVideoType.MIXED_STREAM_VIDEO_TYPE_MAIN);
                region.mediaType = (MixedStreamMediaType.MIXED_STREAM_MEDIA_TYPE_AUDIO_AND_VIDEO);
                regions[index] = region;
                index ++;
            }
        } else if ("2x2".equals(mode)) {
            for (String uid : userNameList) {
                MixedStreamLayoutRegionConfig region = new MixedStreamLayoutRegionConfig();
                region.roomID = (roomID);
                region.userID = (uid);
                region.locationX = ((index % 2) * width / userNum);
                region.locationY = ((index / 2) * height / 2 + 50);
                region.width = (width / 2);
                // 为展示部分背景
                region.height = (height / 2);
                region.alpha = (1);
                region.zOrder = (0);
                region.renderMode = (MixedStreamRenderMode.MIXED_STREAM_RENDER_MODE_HIDDEN);
                region.streamType = (MixedStreamVideoType.MIXED_STREAM_VIDEO_TYPE_MAIN);
                region.mediaType = (MixedStreamMediaType.MIXED_STREAM_MEDIA_TYPE_AUDIO_AND_VIDEO);
                regions[index] = region;
                index ++;
            }
        }
        return regions;
    }

    IRTCRoomEventHandler rtcRoomEventHandler = new IRTCRoomEventHandler() {
        @Override
        public void onRoomStateChanged(String roomId, String uid, int state, String extraInfo) {
            super.onRoomStateChanged(roomId, uid, state, extraInfo);
            String info = String.format("roomId:%s, uid:%s, state:%d, extraInfo:%s", roomId, uid, state, extraInfo);
            ToastUtil.showLongToast(CDNStreamActivity.this, info);
        }

        @Override
        public void onUserPublishStreamVideo(String streamId, StreamInfo streamInfo, boolean isPublish) {
            if (isPublish) {
                runOnUiThread(() -> setRemoteRenderView(streamInfo.userId, streamInfo.streamId));
            } else {
                runOnUiThread(() -> removeRemoteView(streamInfo.userId, streamInfo.streamId));
            }

        }

        @Override
        public void onUserJoined(UserInfo userInfo) {
            super.onUserJoined(userInfo);
            Log.i(TAG, "onUserJoined, uid:" + userInfo.getUid());
            ToastUtil.showShortToast(CDNStreamActivity.this, "onUserJoined, uid:" + userInfo.getUid());
            userNameList.add(userInfo.getUid());
        }

        @Override
        public void onUserLeave(String uid, int reason) {
            super.onUserLeave(uid, reason);
            userNameList.remove(uid);
        }

        @Override
        public void onLeaveRoom(RTCRoomStats stats) {
            super.onLeaveRoom(stats);
            ToastUtil.showLongToast(CDNStreamActivity.this, "onLeaveRoom, stats:" + stats.toString());
        }
    };

    /**
     * 引擎回调信息
     */
    IRTCEngineEventHandler videoEventHandler = new IRTCEngineEventHandler() {
        @Override
        public void onMixedStreamEvent(MixedStreamTaskInfo info, MixedStreamTaskEvent event, MixedStreamTaskErrorCode error) {
            super.onMixedStreamEvent(info, event, error);
            String msg = String.format("onMixedStreamEvent,taskId:%s, error:%s, event:%s", info.getTaskId(), error.toString(), event.toString());
            Log.d(TAG, msg);
            ToastUtil.showLongToast(CDNStreamActivity.this, msg);
        }
    };

    /**
     * TODO: 开源删除
     */
    public static String getRTMPAddr(String roomID, String taskID) {
        long timeStamp = System.currentTimeMillis();
        long expire = timeStamp + 7200;
        String path = "/rtc_test/" + roomID + taskID;
        String authKey = "Uq8e962ghCCY2pBUB9Me2Fwy";
        String keyStr = path + authKey + expire;
        String sign = MD5Utils.md5Hash(keyStr);

        String addr = "rtmp://fcdn-test-hl.uplive.ixigua.com/rtc_test/" + roomID + taskID + "?sign=" + sign + "&expire=" + expire;
        Log.i(TAG, "rtmp addr: " + addr);
        return addr;
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        leaveRoom();
        if (rtcVideo != null) {
            rtcVideo.stopAudioCapture();
            rtcVideo.stopVideoCapture();
            stopPushCDNStream();
        }

        if (rtcRoom != null) {
            rtcRoom.destroy();
            rtcRoom = null;
        }
        RTCEngine.destroyRTCEngine();
    }

}