package rtc.volcengine.apiexample.examples;

import android.os.Bundle;
import android.text.TextUtils;
import android.view.TextureView;
import android.widget.Button;
import android.widget.EditText;
import android.widget.FrameLayout;

import com.ss.bytertc.engine.RTCRoom;
import com.ss.bytertc.engine.RTCRoomConfig;
import com.ss.bytertc.engine.RTCEngine;
import com.ss.bytertc.engine.UserInfo;
import com.ss.bytertc.engine.VideoCanvas;
import com.ss.bytertc.engine.data.EngineConfig;
import com.ss.bytertc.engine.data.StreamInfo;
import com.ss.bytertc.engine.data.StreamSyncInfoConfig;
import com.ss.bytertc.engine.handler.IRTCRoomEventHandler;
import com.ss.bytertc.engine.handler.IRTCEngineEventHandler;
import com.ss.bytertc.engine.type.ChannelProfile;
import com.ss.bytertc.engine.type.RTCRoomStats;

import java.nio.ByteBuffer;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;

import rtc.volcengine.apiexample.BaseActivity;
import rtc.volcengine.apiexample.R;
import rtc.volcengine.apiexample.Utils.ToastUtil;
import rtc.volcengine.apiexample.common.Constants;
import rtc.volcengine.apiexample.common.annotations.ApiExample;

@ApiExample(order = 11, name = "随帧同步消息")
public class StreamSyncInfoActivity extends BaseActivity {

    private Button btnJoinRoom, btnSendMsg;
    private EditText roomIdInput, msgInput;
    private FrameLayout localViewContainer;

    private RTCEngine rtcVideo;
    private RTCRoom rtcRoom;
    private boolean isJoined;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_stream_sync_info);
        setTitle(R.string.title_stream_sync_info);

        initUI();

        EngineConfig config = new EngineConfig();
        config.context = this;
        config.appID = Constants.APP_ID;
        rtcVideo = RTCEngine.createRTCEngine(config, rtcVideoEventHandler);
        // 开启音视频采集
        rtcVideo.startAudioCapture();
        rtcVideo.startVideoCapture();

        setLocalRenderView();

    }

    private void initUI() {
        localViewContainer = findViewById(R.id.local_view_container);
        btnJoinRoom = findViewById(R.id.btn_join_room);
        btnSendMsg = findViewById(R.id.btn_send_msg);
        msgInput = findViewById(R.id.msg_input);
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

        btnSendMsg.setOnClickListener(v -> {
            String msg = msgInput.getText().toString();
            if (TextUtils.isEmpty(msg)) {
                ToastUtil.showAlert(this, "message is null");
            }

            sendMsg(msg);
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

    /**
     * 加入房间
     * @param roomId
     */
    private void joinRoom(String roomId) {

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

    private void sendMsg(String msg) {
        StreamSyncInfoConfig config = new StreamSyncInfoConfig(0, StreamSyncInfoConfig.SyncInfoStreamType.SYNC_INFO_STREAM_TYPE_AUDIO);
        rtcVideo.sendStreamSyncInfo(msg.getBytes(StandardCharsets.UTF_8), config);
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

    IRTCEngineEventHandler rtcVideoEventHandler = new IRTCEngineEventHandler() {
        @Override
            public void onStreamSyncInfoReceived(String streamId, StreamInfo streamInfo, StreamSyncInfoConfig.SyncInfoStreamType streamType, ByteBuffer data) {
            Charset charset = Charset.defaultCharset();
            String dataString = charset.decode(data).toString();
            ToastUtil.showLongToast(StreamSyncInfoActivity.this, "onStreamSyncInfoReceived：" + dataString);
        }
    };

    IRTCRoomEventHandler rtcRoomEventHandler = new IRTCRoomEventHandler() {
        @Override
        public void onRoomStateChanged(String roomId, String uid, int state, String extraInfo) {
            super.onRoomStateChanged(roomId, uid, state, extraInfo);
            String info = String.format("roomId:%s, uid:%s, state:%d, extraInfo:%s", roomId, uid, state, extraInfo);
            ToastUtil.showShortToast(StreamSyncInfoActivity.this, info);
        }

        @Override
        public void onLeaveRoom(RTCRoomStats stats) {
            super.onLeaveRoom(stats);
            ToastUtil.showLongToast(StreamSyncInfoActivity.this, "onLeaveRoom, stats:" + stats.toString());
        }
    };

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
        RTCEngine.destroyRTCEngine();
    }

}