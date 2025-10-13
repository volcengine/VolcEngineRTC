package rtc.volcengine.apiexample.examples.encodevideoframe;

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
import com.ss.bytertc.engine.data.EngineConfig;
import com.ss.bytertc.engine.data.StreamInfo;
import com.ss.bytertc.engine.data.VideoSourceType;
import com.ss.bytertc.engine.handler.IRTCRoomEventHandler;
import com.ss.bytertc.engine.handler.IRTCEngineEventHandler;
import com.ss.bytertc.engine.type.ChannelProfile;
import com.ss.bytertc.engine.type.RTCRoomStats;
import rtc.volcengine.apiexample.BaseActivity;
import rtc.volcengine.apiexample.R;
import rtc.volcengine.apiexample.Utils.ToastUtil;
import rtc.volcengine.apiexample.common.Constants;
import rtc.volcengine.apiexample.common.annotations.ApiExample;

@ApiExample(name = "自定义编码视频", order = 8.4)
public class EncodeVideoFrameActivity extends BaseActivity {

    private static final String TAG = "EncodeVideoFrameActivity";
    private FrameLayout localViewContainer;
    private FrameLayout remoteViewContainer;

    private Button btnJoinRoom, btnStartPush, btnStopPush;
    private EditText roomIdInput;
    private Spinner videoFormatSpinner;
    RTCEngine rtcVideo;
    RTCRoom rtcRoom;

    boolean isJoined;
    private String roomID;

    VideoCaptureCamera videoCaptureCamera;
    TextureView textureView;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_encode_video_frame);

        setTitle(R.string.title_encode_video_frame);

        initUI();
        EngineConfig config = new EngineConfig();
        config.context = this;
        config.appID = Constants.APP_ID;
        rtcVideo = RTCEngine.createRTCEngine(config, rtcVideoEventHandler);

        rtcVideo.startAudioCapture();
        setLocalRenderView();
        videoCaptureCamera = new VideoCaptureCamera(rtcVideo, textureView);
        textureView.setSurfaceTextureListener(videoCaptureCamera);

        rtcVideo.setVideoSourceType(VideoSourceType.VIDEO_SOURCE_TYPE_ENCODED_WITHOUT_SIMULCAST);
        int ret = rtcVideo.setExternalVideoEncoderEventHandler(videoCaptureCamera);
        Log.i(TAG, "handler ret: " + ret);
    }

    private void initUI() {
        localViewContainer = findViewById(R.id.local_view_container);
        remoteViewContainer = findViewById(R.id.remote_view_container);
        btnJoinRoom = findViewById(R.id.btn_join_room);
        roomIdInput = findViewById(R.id.room_id_input);

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

    }

    /**
     * 设置本地渲染视图，支持TextureView和SurfaceView
     */
    private void setLocalRenderView() {
        textureView = new TextureView(this);
        localViewContainer.removeAllViews();
        localViewContainer.addView(textureView);
    }

    private void setRemoteRenderView(String streamId) {
        TextureView remoteTextureView = new TextureView(this);
        remoteViewContainer.removeAllViews();
        remoteViewContainer.addView(remoteTextureView);
        VideoCanvas videoCanvas = new VideoCanvas();
        videoCanvas.renderView = remoteTextureView;
        videoCanvas.renderMode = VideoCanvas.RENDER_MODE_HIDDEN;
        // 设置远端视频渲染视图
        rtcVideo.setRemoteVideoCanvas(streamId, videoCanvas);
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
        boolean isAutoPublishAudio = true;
        boolean isAutoPublishVideo = true;
        boolean isAutoSubscribeAudio = true;
        boolean isAutoSubscribeVideo = true;
        RTCRoomConfig roomConfig = new RTCRoomConfig(ChannelProfile.CHANNEL_PROFILE_CHAT_ROOM, "",isAutoPublishAudio, isAutoPublishVideo, isAutoSubscribeAudio, isAutoSubscribeVideo);
        // 加入房间
        rtcRoom.joinRoom(token, userInfo, true, roomConfig);;
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

    IRTCRoomEventHandler rtcRoomEventHandler = new IRTCRoomEventHandler() {
        @Override
        public void onRoomStateChanged(String roomId, String uid, int state, String extraInfo) {
            super.onRoomStateChanged(roomId, uid, state, extraInfo);
            String info = String.format("roomId:%s, uid:%s, state:%d, extraInfo:%s", roomId, uid, state, extraInfo);
            ToastUtil.showShortToast(EncodeVideoFrameActivity.this, info);
        }

        @Override
        public void onLeaveRoom(RTCRoomStats stats) {
            super.onLeaveRoom(stats);
            ToastUtil.showLongToast(EncodeVideoFrameActivity.this, "onLeaveRoom, stats:" + stats.toString());
        }

        @Override
        public void onUserPublishStreamVideo(String streamId, StreamInfo streamInfo, boolean isPublish) {
            if (isPublish) {
                // 设置远端视频渲染视图
                runOnUiThread(() -> setRemoteRenderView(streamInfo.streamId));
            }
        }
    };

    IRTCEngineEventHandler rtcVideoEventHandler = new IRTCEngineEventHandler() {};

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
        if (videoCaptureCamera != null) {
            videoCaptureCamera.releaseCamera();
        }
        RTCEngine.destroyRTCEngine();
    }
}