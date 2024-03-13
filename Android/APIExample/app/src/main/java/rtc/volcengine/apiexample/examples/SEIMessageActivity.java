package rtc.volcengine.apiexample.examples;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.text.TextUtils;
import android.util.Log;
import android.view.TextureView;
import android.widget.Button;
import android.widget.EditText;
import android.widget.FrameLayout;

import com.ss.bytertc.engine.RTCRoom;
import com.ss.bytertc.engine.RTCRoomConfig;
import com.ss.bytertc.engine.RTCVideo;
import com.ss.bytertc.engine.UserInfo;
import com.ss.bytertc.engine.VideoCanvas;
import com.ss.bytertc.engine.data.RemoteStreamKey;
import com.ss.bytertc.engine.data.SEICountPerFrame;
import com.ss.bytertc.engine.data.StreamIndex;
import com.ss.bytertc.engine.data.StreamSycnInfoConfig;
import com.ss.bytertc.engine.handler.IRTCRoomEventHandler;
import com.ss.bytertc.engine.handler.IRTCVideoEventHandler;
import com.ss.bytertc.engine.live.ByteRTCStreamMixingEvent;
import com.ss.bytertc.engine.live.ByteRTCStreamMixingType;
import com.ss.bytertc.engine.live.ByteRTCTranscoderErrorCode;
import com.ss.bytertc.engine.live.IMixedStreamObserver;
import com.ss.bytertc.engine.live.MixedStreamConfig;
import com.ss.bytertc.engine.live.MixedStreamType;
import com.ss.bytertc.engine.type.ChannelProfile;
import com.ss.bytertc.engine.type.RTCRoomStats;
import com.ss.bytertc.engine.video.VideoFrame;

import java.nio.ByteBuffer;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;

import rtc.volcengine.apiexample.BaseActivity;
import rtc.volcengine.apiexample.R;
import rtc.volcengine.apiexample.Utils.MD5Utils;
import rtc.volcengine.apiexample.Utils.ToastUtil;
import rtc.volcengine.apiexample.common.Constants;
import rtc.volcengine.apiexample.common.annotations.ApiExample;

@ApiExample(order = 10, name = "SEI消息", category = "消息管理")
public class SEIMessageActivity extends BaseActivity {

    private static final String TAG = "SEIMessageActivity";

    private RTCVideo rtcVideo;
    private RTCRoom rtcRoom;
    private boolean isJoined;

    private Button btnJoinRoom, btnSendSEIMsg, startPushStream, stopPushStream, btnSendLayoutMsg;
    private EditText roomIdInput, seiMsgInput, pushUrlInput, layoutMsgInput;
    private FrameLayout localViewContainer;
    private MixedStreamConfig mixedStreamConfig;
    private String roomID;
    private static final String CDN_TASK_ID = "111";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_seimessage);
        setTitle(R.string.title_sei_msg);

        initUI();

        rtcVideo = RTCVideo.createRTCVideo(this, Constants.APP_ID, rtcVideoEventHandler, null, null);
        // 开启音视频采集
        rtcVideo.startAudioCapture();
        rtcVideo.startVideoCapture();

        mixedStreamConfig = MixedStreamConfig.defaultMixedStreamConfig();

        setLocalRenderView();
    }

    private void initUI() {
        localViewContainer = findViewById(R.id.local_view_container);
        btnJoinRoom = findViewById(R.id.btn_join_room);
        roomIdInput = findViewById(R.id.room_id_input);
        btnSendSEIMsg = findViewById(R.id.btn_send_sei_msg);
        seiMsgInput = findViewById(R.id.sei_msg_input);
        pushUrlInput = findViewById(R.id.push_url_input);
        startPushStream = findViewById(R.id.btn_start_push);
        stopPushStream = findViewById(R.id.btn_stop_push);
        layoutMsgInput = findViewById(R.id.layout_msg_input);
        btnSendLayoutMsg = findViewById(R.id.btn_send_layout_msg);

        pushUrlInput.setText(getRTMPAddr("111", CDN_TASK_ID));

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
        });

        btnSendSEIMsg.setOnClickListener(v -> {
            String msg = seiMsgInput.getText().toString();
            if (TextUtils.isEmpty(msg)) {
                ToastUtil.showAlert(this, "message is null");
            }

            rtcVideo.sendSEIMessage(StreamIndex.STREAM_INDEX_MAIN, msg.getBytes(StandardCharsets.UTF_8), 3, SEICountPerFrame.SEI_COUNT_PER_FRAME_SINGLE);
        });

        startPushStream.setOnClickListener(v -> {
            startPushMixedStreamToCDN();
        });

        stopPushStream.setOnClickListener(v -> stopPushCDNStream());
        btnSendLayoutMsg.setOnClickListener(v -> updateCDNStreamConfig());

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
        rtcVideo.setLocalVideoCanvas(StreamIndex.STREAM_INDEX_MAIN, videoCanvas);
    }

    /**
     * 加入房间
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
        boolean isAutoPublish = true;
        boolean isAutoSubscribeAudio = true;
        boolean isAutoSubscribeVideo = true;
        RTCRoomConfig roomConfig = new RTCRoomConfig(ChannelProfile.CHANNEL_PROFILE_CHAT_ROOM, isAutoPublish, isAutoSubscribeAudio, isAutoSubscribeVideo);
        // 加入房间
        rtcRoom.joinRoom(token, userInfo, roomConfig);
    }

    /**
     * 离开房间
     */
    private void leaveRoom() {
        if (rtcRoom != null) {
            rtcRoom.leaveRoom();
            rtcRoom.destroy();
            rtcRoom = null;
        }
    }

    IRTCVideoEventHandler rtcVideoEventHandler = new IRTCVideoEventHandler() {
        @Override
        public void onSEIMessageReceived(RemoteStreamKey remoteStreamKey, ByteBuffer message) {
            super.onSEIMessageReceived(remoteStreamKey, message);
            Charset charset = Charset.defaultCharset();
            String dataString = charset.decode(message).toString();
            ToastUtil.showLongToast(SEIMessageActivity.this, "onSEIMessageReceived：" + dataString);
        }
    };

    IRTCRoomEventHandler rtcRoomEventHandler = new IRTCRoomEventHandler() {
        @Override
        public void onRoomStateChanged(String roomId, String uid, int state, String extraInfo) {
            super.onRoomStateChanged(roomId, uid, state, extraInfo);
            String info = String.format("roomId:%s, uid:%s, state:%d, extraInfo:%s", roomId, uid, state, extraInfo);
            ToastUtil.showShortToast(SEIMessageActivity.this, info);
        }

        @Override
        public void onLeaveRoom(RTCRoomStats stats) {
            super.onLeaveRoom(stats);
            ToastUtil.showLongToast(SEIMessageActivity.this, "onLeaveRoom, stats:" + stats.toString());
        }
    };

    /**
     * {zh}
     * 开启合流转推
     */
    private void startPushMixedStreamToCDN() {
        String cdnAddr = pushUrlInput.getText().toString();
        if (cdnAddr.isEmpty()) {
            ToastUtil.showAlert(this, "cdn address is null");
            return;
        }
        String msg = layoutMsgInput.getText().toString();

        mixedStreamConfig.setUserID(localUid);
        mixedStreamConfig.setRoomID(roomID);
        mixedStreamConfig.setPushURL(cdnAddr);

        MixedStreamConfig.MixedStreamLayoutConfig layoutConfig = new MixedStreamConfig.MixedStreamLayoutConfig();
        layoutConfig.setRegions(getLayoutRegions());
        layoutConfig.setBackgroundColor("#000000");
        if (!TextUtils.isEmpty(msg)) {
            layoutConfig.setUserConfigExtraInfo(msg);
        }
        mixedStreamConfig.setLayout(layoutConfig);
        rtcVideo.startPushMixedStreamToCDN(CDN_TASK_ID, mixedStreamConfig, mixedStreamObserver);
    }

    private MixedStreamConfig.MixedStreamLayoutRegionConfig[] getLayoutRegions() {
        int width = 360;
        int height = 640;
        int userNum = 1;
        MixedStreamConfig.MixedStreamLayoutRegionConfig[] regions = new MixedStreamConfig.MixedStreamLayoutRegionConfig[userNum];
        int index = 0;
        MixedStreamConfig.MixedStreamLayoutRegionConfig region = new MixedStreamConfig.MixedStreamLayoutRegionConfig();
        region.setRoomID(roomID);
        region.setUserID(localUid);
        region.setLocationX(index * width / userNum);
        // 留出部分背景区域
        region.setLocationY(50);
        region.setWidth(width / userNum);
        region.setHeight(height);
        region.setAlpha(1);
        region.setZOrder(0);
        region.setRenderMode(MixedStreamConfig.MixedStreamRenderMode.MIXED_STREAM_RENDER_MODE_HIDDEN);
        region.setStreamType(MixedStreamConfig.MixedStreamLayoutRegionConfig.MixedStreamVideoType.MIXED_STREAM_VIDEO_TYPE_MAIN);
        region.setMediaType(MixedStreamConfig.MixedStreamMediaType.MIXED_STREAM_MEDIA_TYPE_AUDIO_AND_VIDEO);
        regions[index] = region;
        return regions;
    }

    private void updateCDNStreamConfig() {
        String cdnAddr = pushUrlInput.getText().toString();
        if (cdnAddr.isEmpty()) {
            ToastUtil.showAlert(this, "cdn address is null");
            return;
        }
        String msg = layoutMsgInput.getText().toString();
        if (msg.isEmpty()) {
            ToastUtil.showAlert(this, "message is null");
            return;
        }
        mixedStreamConfig.setPushURL(cdnAddr);

        MixedStreamConfig.MixedStreamLayoutConfig layoutConfig = new MixedStreamConfig.MixedStreamLayoutConfig();
        layoutConfig.setRegions(getLayoutRegions());
        layoutConfig.setUserConfigExtraInfo(msg);
        layoutConfig.setBackgroundColor("#000000");
        mixedStreamConfig.setLayout(layoutConfig);

        rtcVideo.updatePushMixedStreamToCDN(CDN_TASK_ID, mixedStreamConfig);
    }

    /**
     * 停止CDN推流
     */
    private void stopPushCDNStream() {
        rtcVideo.stopPushStreamToCDN(CDN_TASK_ID);
    }

    IMixedStreamObserver mixedStreamObserver = new IMixedStreamObserver() {
        @Override
        public boolean isSupportClientPushStream() {
            ToastUtil.showShortToast(SEIMessageActivity.this, "isSupportClientPushStream");
            return false;
        }

        @Override
        public void onMixingEvent(ByteRTCStreamMixingEvent eventType, String taskId, ByteRTCTranscoderErrorCode error, MixedStreamType mixType) {
            String msg = String.format("onMixingEvent, type:%s, taskId:%s, error:%s, mixType:%s", eventType.toString(), taskId, error.toString(), mixType.toString());
            Log.d(TAG, msg);
            ToastUtil.showLongToast(SEIMessageActivity.this, msg);
        }

        @Override
        public void onMixingAudioFrame(String taskId, byte[] audioFrame, int frameNum, long timeStampMs) {
            String msg = String.format("onMixingEvent, taskId:%s, frameNum:%d, timeStampMs:%l", taskId, frameNum, timeStampMs);
            Log.d(TAG, msg);
            ToastUtil.showLongToast(SEIMessageActivity.this, msg);
        }

        @Override
        public void onMixingVideoFrame(String taskId, VideoFrame videoFrame) {
            String msg = String.format("onMixingVideoFrame, taskId:%s", taskId);
            Log.d(TAG, msg);
            ToastUtil.showLongToast(SEIMessageActivity.this, msg);
        }

        @Override
        public void onMixingDataFrame(String taskId, byte[] dataFrame, long time) {
            String msg = String.format("onMixingDataFrame, taskId:%s", taskId);
            Log.d(TAG, msg);
            ToastUtil.showLongToast(SEIMessageActivity.this, msg);
        }

        @Override
        public void onCacheSyncVideoFrames(String taskId, String[] userIds, VideoFrame[] videoFrame, byte[][] dataFrame, int count) {
            String msg = String.format("onCacheSyncVideoFrames, taskId:%s", taskId);
            Log.d(TAG, msg);
            ToastUtil.showLongToast(SEIMessageActivity.this, msg);
        }
    };

    public static String getRTMPAddr(String roomID, String taskID) {
        long timeStamp = System.currentTimeMillis();
        long expire = timeStamp + 7200;
        String path = "/rtc_test/" + taskID;
        String authKey = "Uq8e962ghCCY2pBUB9Me2Fwy";
        String keyStr = path + authKey + expire;
        String sign = MD5Utils.md5Hash(keyStr);

        String addr = "rtmp://fcdn-test-hl.uplive.ixigua.com/rtc_test/" + taskID + "?sign=" + sign + "&expire=" + expire;
        Log.i(TAG, "rtmp addr: " + addr);
        return addr;
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        if (rtcVideo != null) {
            rtcVideo.stopAudioCapture();
            rtcVideo.stopVideoCapture();
        }
        if (rtcRoom != null) {
            rtcRoom.destroy();
            rtcRoom = null;
        }
        RTCVideo.destroyRTCVideo();
    }
}