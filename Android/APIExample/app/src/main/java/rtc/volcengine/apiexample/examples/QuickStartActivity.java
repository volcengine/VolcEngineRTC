package rtc.volcengine.apiexample.examples;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.TextureView;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.FrameLayout;
import android.widget.Toast;

import com.ss.bytertc.engine.RTCRoom;
import com.ss.bytertc.engine.RTCRoomConfig;
import com.ss.bytertc.engine.RTCVideo;
import com.ss.bytertc.engine.UserInfo;
import com.ss.bytertc.engine.VideoCanvas;
import com.ss.bytertc.engine.data.RemoteStreamKey;
import com.ss.bytertc.engine.data.StreamIndex;
import com.ss.bytertc.engine.handler.IRTCRoomEventHandler;
import com.ss.bytertc.engine.handler.IRTCVideoEventHandler;
import com.ss.bytertc.engine.type.ChannelProfile;
import com.ss.bytertc.engine.type.MediaStreamType;
import com.ss.bytertc.engine.type.RTCRoomStats;
import com.ss.bytertc.engine.type.StreamRemoveReason;

import java.util.regex.Pattern;

import rtc.volcengine.apiexample.BaseActivity;
import rtc.volcengine.apiexample.BuildConfig;
import rtc.volcengine.apiexample.R;
import rtc.volcengine.apiexample.Utils.ToastUtil;
import rtc.volcengine.apiexample.common.Constants;
import rtc.volcengine.apiexample.common.annotations.ApiExample;
import rtc.volcengine.apiexample.examples.PictureInPicture.PictureInPictureActivity;

/**
 * 功能名称： VolcEngineRTC 快速开始
 * 功能简单描述：快速跑通 ByteRTC 音视频通话功能
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
 *     onRoomStateChanged 房间状态回调
 *     onLeaveRoom 离房回调
 *     onUserJoined 用户加入回调
 *     onUserLeave  用户离开回调
 *     onUserPublishStream 用户发流回调
 *     onUserUnpublishStream 用户停止发流回调
 *
 *
 * Demo实现时的逻辑
 *    请按照界面给出的步骤开发音视频通话功能
 *    为了展示简单，所有功能的token都由客户端生成，请在真正接入时视具体情况而定
 */

@ApiExample(name = "快速开始", category = "基础功能", order = 0)
public class QuickStartActivity extends BaseActivity {

    private Button btnCreateEngine;
    private Button btnStartCapture;
    private Button btnSetLocalView;
    private Button btnJoinRoom;
    private Button btnLeaveRoom;
    private Button btnDestroyRoom;
    private Button btnDestroyEngine;

    private FrameLayout localViewContainer;
    private FrameLayout remoteViewContainer;
    private EditText roomIdInput;

    private RTCVideo rtcVideo;
    private RTCRoom rtcRoom;
    private String roomId;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_quick_start);
        setTitle(R.string.title_quick_start);

        initUI();
    }

    private void initUI() {
        localViewContainer = findViewById(R.id.local_view_container);
        remoteViewContainer = findViewById(R.id.remote_view_container);

        btnCreateEngine = findViewById(R.id.btn_create_engine);
        btnStartCapture = findViewById(R.id.btn_start_capture);
        btnSetLocalView = findViewById(R.id.btn_set_local_view);
        btnJoinRoom = findViewById(R.id.btn_join_room);
        btnLeaveRoom = findViewById(R.id.btn_leave_room);
        btnDestroyRoom = findViewById(R.id.btn_destroy_room);
        btnDestroyEngine = findViewById(R.id.btn_destroy_engine);
        roomIdInput = findViewById(R.id.room_id_input);

        btnCreateEngine.setOnClickListener(v -> {
            // Step1: 创建引擎
            rtcVideo = RTCVideo.createRTCVideo(QuickStartActivity.this, Constants.APP_ID, rtcVideoEventHandler, null, null);
        });

        btnStartCapture.setOnClickListener(v -> {
            if (rtcVideo ==  null) {
                return;
            }

            // Step2: 开启音视频采集
            rtcVideo.startVideoCapture();
            rtcVideo.startAudioCapture();
        });

        btnSetLocalView.setOnClickListener(v -> {
            if (rtcVideo ==  null) {
                return;
            }

            // Step3: 设置本地视频渲染窗口
            TextureView localTextureView = new TextureView(this);
            localViewContainer.removeAllViews();
            localViewContainer.addView(localTextureView);

            VideoCanvas videoCanvas = new VideoCanvas();
            videoCanvas.renderView = localTextureView;
            videoCanvas.renderMode = VideoCanvas.RENDER_MODE_HIDDEN;
            // 设置本地视频渲染视图
            rtcVideo.setLocalVideoCanvas(StreamIndex.STREAM_INDEX_MAIN, videoCanvas);
        });

        btnJoinRoom.setOnClickListener(v -> {
            roomId = roomIdInput.getText().toString();
            if (!Pattern.matches(INPUT_REGEX, roomId)) {
                ToastUtil.showAlert(this, "输入不合法，只支持数字、大小写字母、@._-,长度小于128字符");
                return;
            }

            if (rtcVideo == null) {
                ToastUtil.showAlert(this, "引擎未创建");
                return;
            }

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
        });

        btnLeaveRoom.setOnClickListener(v -> {
            if (rtcRoom != null) {
                rtcRoom.leaveRoom();
            }
        });

        btnDestroyRoom.setOnClickListener(v -> {
            if (rtcRoom != null) {
                rtcRoom.destroy();
            }
            rtcRoom = null;
        });

        btnDestroyEngine.setOnClickListener(v -> {
            RTCVideo.destroyRTCVideo();
            rtcVideo = null;
        });

    }

    private void setRemoteRenderView(String uid) {
        TextureView remoteTextureView = new TextureView(this);
        remoteViewContainer.removeAllViews();
        remoteViewContainer.addView(remoteTextureView);
        VideoCanvas videoCanvas = new VideoCanvas();
        videoCanvas.renderView = remoteTextureView;
        videoCanvas.renderMode = VideoCanvas.RENDER_MODE_HIDDEN;

        RemoteStreamKey remoteStreamKey = new RemoteStreamKey(roomId, uid, StreamIndex.STREAM_INDEX_MAIN);
        // 设置远端视频渲染视图
        rtcVideo.setRemoteVideoCanvas(remoteStreamKey, videoCanvas);
    }

    private void removeRemoteView(String uid) {
        RemoteStreamKey remoteStreamKey = new RemoteStreamKey(roomId, uid, StreamIndex.STREAM_INDEX_MAIN);
        rtcVideo.setRemoteVideoCanvas(remoteStreamKey, null);
    }

    IRTCVideoEventHandler rtcVideoEventHandler = new IRTCVideoEventHandler() {
        @Override
        public void onWarning(int warn) {
            super.onWarning(warn);
            ToastUtil.showLongToast(QuickStartActivity.this, "onError:" + warn);
        }

        @Override
        public void onError(int err) {
            super.onError(err);
            runOnUiThread(() -> ToastUtil.showLongToast(QuickStartActivity.this, "onError:" + err));
        }
    };

    IRTCRoomEventHandler rtcRoomEventHandler = new IRTCRoomEventHandler() {
        @Override
        public void onRoomStateChanged(String roomId, String uid, int state, String extraInfo) {
            super.onRoomStateChanged(roomId, uid, state, extraInfo);
            String info = String.format("roomId:%s, uid:%s, state:%d, extraInfo:%s", roomId, uid, state, extraInfo);
            ToastUtil.showShortToast(QuickStartActivity.this, info);
        }

        @Override
        public void onUserPublishStream(String uid, MediaStreamType type) {
            super.onUserPublishStream(uid, type);
            runOnUiThread(() -> {
                // 设置远端视频渲染视图
                setRemoteRenderView(uid);
            });
        }

        @Override
        public void onUserUnpublishStream(String uid, MediaStreamType type, StreamRemoveReason reason) {
            super.onUserUnpublishStream(uid, type, reason);
            runOnUiThread(() -> {
                // 解除远端视频渲染视图绑定
                removeRemoteView(uid);
            });
        }

        @Override
        public void onLeaveRoom(RTCRoomStats stats) {
            super.onLeaveRoom(stats);
            ToastUtil.showLongToast(QuickStartActivity.this, "onLeaveRoom, stats:" + stats.toString());
        }

        @Override
        public void onTokenWillExpire() {
            super.onTokenWillExpire();
            ToastUtil.showAlert(QuickStartActivity.this, "Token Will Expire");
        }
    };

    @Override
    protected void onDestroy() {
        super.onDestroy();
        if (rtcRoom != null) {
            rtcRoom.destroy();
            rtcRoom = null;
        }
        RTCVideo.destroyRTCVideo();
        rtcVideo = null;
    }
}