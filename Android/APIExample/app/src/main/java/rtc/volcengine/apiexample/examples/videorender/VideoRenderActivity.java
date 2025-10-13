package rtc.volcengine.apiexample.examples.videorender;

import android.os.Bundle;
import android.text.TextUtils;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.FrameLayout;
import android.widget.Spinner;

import com.ss.bytertc.engine.RTCRoom;
import com.ss.bytertc.engine.RTCRoomConfig;
import com.ss.bytertc.engine.RTCEngine;
import com.ss.bytertc.engine.UserInfo;
import com.ss.bytertc.engine.data.EngineConfig;
import com.ss.bytertc.engine.data.VideoPixelFormat;
import com.ss.bytertc.engine.handler.IRTCRoomEventHandler;
import com.ss.bytertc.engine.handler.IRTCEngineEventHandler;
import com.ss.bytertc.engine.type.ChannelProfile;
import com.ss.bytertc.engine.type.RTCRoomStats;
import com.ss.bytertc.engine.video.LocalVideoSinkConfig;

import rtc.volcengine.apiexample.BaseActivity;
import rtc.volcengine.apiexample.R;
import rtc.volcengine.apiexample.Utils.ToastUtil;
import rtc.volcengine.apiexample.common.Constants;
import rtc.volcengine.apiexample.common.annotations.ApiExample;

@ApiExample(name = "自定义渲染", order = 8.3)
public class VideoRenderActivity extends BaseActivity {

    private FrameLayout localViewContainer;

    private Button btnJoinRoom, btnStartRender, btnStopRender;
    private EditText roomIdInput;
    private Spinner videoFormatSpinner;
    RTCEngine rtcVideo;
    RTCRoom rtcRoom;

    boolean isJoined;
    private String roomID;

    private CustomRenderView videoSink;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_video_render);

        setTitle(R.string.title_video_render);

        initUI();

        EngineConfig config = new EngineConfig();
        config.context = this;
        config.appID = Constants.APP_ID;
        rtcVideo = RTCEngine.createRTCEngine(config, rtcVideoEventHandler);
        // 开启音视频采集
        rtcVideo.startVideoCapture();
        rtcVideo.startAudioCapture();

    }

    private void initUI() {
        localViewContainer = findViewById(R.id.local_view_container);
        btnJoinRoom = findViewById(R.id.btn_join_room);
        roomIdInput = findViewById(R.id.room_id_input);
        videoSink = new CustomRenderView(this);
        btnStartRender = findViewById(R.id.btn_start_render);
        btnStopRender = findViewById(R.id.btn_stop_render);
        videoFormatSpinner = findViewById(R.id.video_format_spinner);

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

        btnStartRender.setOnClickListener(v -> {
            renderLocalVideo();
        });

        btnStopRender.setOnClickListener(v -> {
            stopLocalRender();
        });

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
        RTCRoomConfig roomConfig = new RTCRoomConfig(ChannelProfile.CHANNEL_PROFILE_CHAT_ROOM, "", isAutoPublishAudio, isAutoPublishVideo, isAutoSubscribeAudio, isAutoSubscribeVideo);
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

    private void renderLocalVideo() {
        FrameLayout.LayoutParams params = new FrameLayout.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT,
                ViewGroup.LayoutParams.MATCH_PARENT);
        localViewContainer.removeAllViews();
        localViewContainer.addView((View) videoSink, params);
        LocalVideoSinkConfig config = new LocalVideoSinkConfig();
        String format = videoFormatSpinner.getSelectedItem().toString();
        if ("I420".equals(format)) {
            config.pixelFormat = VideoPixelFormat.I420;
        } else {
            config.pixelFormat = VideoPixelFormat.RGBA;
        }
        rtcVideo.setLocalVideoSink(videoSink, config);
    }

    private void stopLocalRender() {
        localViewContainer.removeAllViews();
        LocalVideoSinkConfig config = new LocalVideoSinkConfig();
        String format = videoFormatSpinner.getSelectedItem().toString();
        if ("I420".equals(format)) {
            config.pixelFormat = VideoPixelFormat.I420;
        } else {
            config.pixelFormat = VideoPixelFormat.RGBA;
        }
        rtcVideo.setLocalVideoSink(null, config);
    }

    IRTCRoomEventHandler rtcRoomEventHandler = new IRTCRoomEventHandler() {
        @Override
        public void onRoomStateChanged(String roomId, String uid, int state, String extraInfo) {
            super.onRoomStateChanged(roomId, uid, state, extraInfo);
            String info = String.format("onRoomStateChanged roomId:%s, uid:%s, state:%d, extraInfo:%s", roomId, uid, state, extraInfo);
            ToastUtil.showShortToast(VideoRenderActivity.this, info);
        }

        @Override
        public void onLeaveRoom(RTCRoomStats stats) {
            super.onLeaveRoom(stats);
            ToastUtil.showLongToast(VideoRenderActivity.this, "onLeaveRoom, stats:" + stats.toString());
        }
    };

    IRTCEngineEventHandler rtcVideoEventHandler = new IRTCEngineEventHandler() {
    };


    @Override
    protected void onDestroy() {
        super.onDestroy();
        if (rtcVideo != null) {
            rtcVideo.stopAudioCapture();
            rtcVideo.stopVideoCapture();
        }
        RTCEngine.destroyRTCEngine();
        if (videoSink != null) {
            videoSink.release();
            videoSink = null;
        }
    }
}