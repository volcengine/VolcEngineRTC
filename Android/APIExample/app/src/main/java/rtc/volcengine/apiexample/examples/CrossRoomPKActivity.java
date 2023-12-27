package rtc.volcengine.apiexample.examples;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.text.TextUtils;
import android.view.TextureView;
import android.widget.Button;
import android.widget.EditText;
import android.widget.FrameLayout;
import android.widget.Toast;

import com.ss.bytertc.engine.RTCRoom;
import com.ss.bytertc.engine.RTCRoomConfig;
import com.ss.bytertc.engine.RTCVideo;
import com.ss.bytertc.engine.UserInfo;
import com.ss.bytertc.engine.VideoCanvas;
import com.ss.bytertc.engine.data.ForwardStreamEventInfo;
import com.ss.bytertc.engine.data.ForwardStreamInfo;
import com.ss.bytertc.engine.data.ForwardStreamStateInfo;
import com.ss.bytertc.engine.data.StreamIndex;
import com.ss.bytertc.engine.handler.IRTCRoomEventHandler;
import com.ss.bytertc.engine.handler.IRTCVideoEventHandler;
import com.ss.bytertc.engine.type.ChannelProfile;
import com.ss.bytertc.engine.type.RTCRoomStats;

import java.util.Collections;

import rtc.volcengine.apiexample.BaseActivity;
import rtc.volcengine.apiexample.R;
import rtc.volcengine.apiexample.Utils.ToastUtil;
import rtc.volcengine.apiexample.common.Constants;
import rtc.volcengine.apiexample.common.annotations.ApiExample;
import rtc.volcengine.apiexample.examples.mediaplayer.MediaPlayerActivity;

/**
 * 功能名称： ByteRTC 跨房转推
 * 功能简单描述：跨房间转发媒体流，指可见用户的媒体流可以同时转发到多个 RTC 房间。
 *             转发目标房间的数量在 RTC 侧没有限制。 本功能适用于以下场景，观众在原来的房间中就能够接收到来自其他房间主播的媒体流。
 * 参考文档： https://www.volcengine.com/docs/6348/104398
 *
 * 此功能涉及的API及回调：
 *     createRTCVideo 创建引擎
 *     destroyRTCVideo 销毁引擎
 *     startAudioCapture 开启音频采集
 *     startVideoCapture 开启视频采集
 *     createRTCRoom 创建RTC房间
 *     joinRoom 进入RTC房间
 *     leaveRoom 离开RTC房间
 *     destroy 销毁RTC房间
 *
 *     startForwardStreamToRooms 开始转发媒体流
 *     stopForwardStreamToRooms  停止转发媒体流
 *
 *     setLocalVideoCanvas 设置本地视频渲染视图
 *     setRemoteVideoCanvas 设置远端视频渲染视图
 *
 *     onRoomStateChanged 房间状态回调
 *     onLeaveRoom 离房回调
 *     onUserJoined 用户加入回调
 *     onUserLeave  用户离开回调
 *     onUserPublishStream 用户发流回调
 *     onUserUnpublishStream 用户停止发流回调
 *
 * Demo实现时的逻辑
 *    本Demo演示功能：在本端房间向其他房间转推媒体流
 *    为了展示简单，所有功能的token都由客户端生成，请在真正接入时视具体情况而定
 */

@ApiExample(order = 2, category = "音视频传输", name = "跨房间PK")
public class CrossRoomPKActivity extends BaseActivity {

    private FrameLayout localViewContainer;
    private Button btnJoinRoom;
    private Button btnStartTransmit;
    private Button btnStopTransmit;
    private Button btnPauseTransmit;
    private Button btnResumeTransmit;
    private EditText mainRoomIdInput;
    private EditText transmitRoomIdInput;

    RTCVideo rtcVideo;
    RTCRoom rtcRoom;

    boolean isJoined;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_cross_room_pk_activity);
        setTitle(R.string.title_cross_room_pk);
        initUI();

        // 创建引擎
        rtcVideo = RTCVideo.createRTCVideo(this, Constants.APP_ID, videoEventHandler, null, null);
        // 设置本端渲染视图
        setLocalRenderView();
        // 开启音视频采集
        rtcVideo.startVideoCapture();
        rtcVideo.startAudioCapture();

    }

    private void initUI() {
        localViewContainer = findViewById(R.id.local_view_container);
        btnJoinRoom = findViewById(R.id.btn_join_room);
        btnStartTransmit = findViewById(R.id.btn_start_transmit);
        btnStopTransmit = findViewById(R.id.btn_stop_transmit);
        btnPauseTransmit = findViewById(R.id.btn_pause_transmit);
        btnResumeTransmit = findViewById(R.id.btn_resume_transmit);
        mainRoomIdInput = findViewById(R.id.main_room_input);
        transmitRoomIdInput = findViewById(R.id.transmit_room_input);

        btnJoinRoom.setOnClickListener(v -> {
            String roomId = mainRoomIdInput.getText().toString();
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

        btnStartTransmit.setOnClickListener(v -> {
            String roomId = transmitRoomIdInput.getText().toString();
            // 开始转推
            startForwardStreamToRooms(roomId);
        });

        btnStopTransmit.setOnClickListener(v -> {
            if (rtcRoom != null) {
                // 停止转推
                rtcRoom.stopForwardStreamToRooms();
            }
        });

        btnPauseTransmit.setOnClickListener(v -> {
            if (rtcRoom != null) {
                // 暂停转推
                rtcRoom.pauseForwardStreamToAllRooms();
            }
        });

        btnResumeTransmit.setOnClickListener(v -> {
            if (rtcRoom != null) {
                // 恢复转推
                rtcRoom.resumeForwardStreamToAllRooms();
            }
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
        rtcVideo.setLocalVideoCanvas(StreamIndex.STREAM_INDEX_MAIN, videoCanvas);
    }

    /**
     * 加入房间
     * @param roomId
     */
    private void joinRoom(String roomId) {
        rtcRoom = rtcVideo.createRTCRoom(roomId);
        rtcRoom.setRTCRoomEventHandler(roomEventHandler);
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

    /**
     * 开启转推
     * @param roomId
     */
    private void startForwardStreamToRooms(String roomId) {
        if (TextUtils.isEmpty(roomId)) {
            ToastUtil.showAlert(this, "roomId is null");
            return;
        }

        // 可以向多个房间转推，实例代码仅展示向一个房间转推
        ForwardStreamInfo forwardStreamInfo = new ForwardStreamInfo(roomId, requestRoomToken(roomId));
        if (rtcRoom != null) {
            rtcRoom.startForwardStreamToRooms(Collections.singletonList(forwardStreamInfo));
        }
    }


    /**
     * 房间回调信息
     */
    IRTCRoomEventHandler roomEventHandler = new IRTCRoomEventHandler() {
        @Override
        public void onRoomStateChanged(String roomId, String uid, int state, String extraInfo) {
            super.onRoomStateChanged(roomId, uid, state, extraInfo);
            String info = String.format("roomId:%s, uid:%s, state:%d, extraInfo:%s", roomId, uid, state, extraInfo);
            ToastUtil.showLongToast(CrossRoomPKActivity.this, info);
        }

        @Override
        public void onForwardStreamEvent(ForwardStreamEventInfo[] eventInfos) {
            super.onForwardStreamEvent(eventInfos);
            String msg = String.format("ForwardStreamEvent, roomid:%s, event:%d", eventInfos[0].roomId, eventInfos[0].event.value());
            ToastUtil.showLongToast(CrossRoomPKActivity.this, msg);
        }

        @Override
        public void onForwardStreamStateChanged(ForwardStreamStateInfo[] stateInfos) {
            super.onForwardStreamStateChanged(stateInfos);
            String msg = String.format("ForwardStreamStateChanged, roomid:%s, event:%d", stateInfos[0].roomId, stateInfos[0].state.value());
            ToastUtil.showLongToast(CrossRoomPKActivity.this, msg);
        }

        @Override
        public void onLeaveRoom(RTCRoomStats stats) {
            super.onLeaveRoom(stats);
            ToastUtil.showLongToast(CrossRoomPKActivity.this, "onLeaveRoom, stats:" + stats.toString());
        }

        @Override
        public void onUserJoined(UserInfo userInfo, int elapsed) {
            super.onUserJoined(userInfo, elapsed);
            ToastUtil.showShortToast(CrossRoomPKActivity.this, "onUserJoined, uid:" + userInfo.getUid());
        }


    };

    /**
     * 引擎回调信息
     */
    IRTCVideoEventHandler videoEventHandler = new IRTCVideoEventHandler() {
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
        RTCVideo.destroyRTCVideo();
    }
}