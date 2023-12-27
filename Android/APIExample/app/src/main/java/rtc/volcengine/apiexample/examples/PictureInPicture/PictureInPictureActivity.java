package rtc.volcengine.apiexample.examples.PictureInPicture;

import android.content.Intent;
import android.content.pm.PackageManager;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.provider.Settings;
import android.text.TextUtils;
import android.view.TextureView;
import android.widget.Button;
import android.widget.EditText;
import android.widget.FrameLayout;

import androidx.annotation.NonNull;

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

import rtc.volcengine.apiexample.BaseActivity;
import rtc.volcengine.apiexample.R;
import rtc.volcengine.apiexample.Utils.ToastUtil;
import rtc.volcengine.apiexample.common.Constants;
import rtc.volcengine.apiexample.common.annotations.ApiExample;
import rtc.volcengine.apiexample.examples.mediaplayer.MediaPlayerActivity;

/**
 * 功能名称： VolcEngineRTC 画中画
 * 功能简单描述：实现画中画功能
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
 *   setRemoteVideoCanvas  设置远端视频外部渲染
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
 *    本Demo演示功能：开启画中画功能
 *    为了展示简单，所有功能的token都由客户端生成，接入SDK时建议将Token生成逻辑放在服务端
 */
@ApiExample(name = "画中画", order = 6, category = "视频管理")
public class PictureInPictureActivity extends BaseActivity {
    private FrameLayout localViewContainer;
    private FrameLayout remoteViewContainer;

    private Button btnJoinRoom;
    private Button btnOpenFloatWindow;
    private EditText roomIdInput;
    private boolean isJoined;
    private RTCVideo rtcVideo;
    private RTCRoom rtcRoom;
    private String roomID;

    private FloatWindowManager floatWindowManager;
    TextureView textureView;

    private static final int REQUEST_CODE_FLOATING_WINDOW = 1001;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_picture_in_picture);
        setTitle(R.string.title_picture_in_picture);
        initUI();


        rtcVideo = RTCVideo.createRTCVideo(this, Constants.APP_ID, rtcVideoEventHandler, null, null);
        // 设置本端渲染视图
        setLocalRenderView();
        // 开启音频采集
        rtcVideo.startVideoCapture();
        rtcVideo.startAudioCapture();
    }

    private void initUI() {
        localViewContainer = findViewById(R.id.local_view_container);
        remoteViewContainer = findViewById(R.id.remote_view_container);
        btnJoinRoom = findViewById(R.id.btn_join_room);
        roomIdInput = findViewById(R.id.room_id_input);
        btnOpenFloatWindow = findViewById(R.id.btn_float_window);

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

        textureView = new TextureView(this);
        floatWindowManager = new FloatWindowManager(this, textureView);
        floatWindowManager.getCloseButton().setOnClickListener(v -> closeFloatingWindow());
        btnOpenFloatWindow.setOnClickListener(v -> requestFloatingWindowPermission());
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
     * 设置本地渲染视图，支持TextureView和SurfaceView
     */
    private void setLocalRenderView() {
        TextureView localTextureView = new TextureView(this);
        localViewContainer.removeAllViews();
        localViewContainer.addView(localTextureView);

        VideoCanvas videoCanvas = new VideoCanvas();
        videoCanvas.renderView = localTextureView;
        videoCanvas.renderMode = VideoCanvas.RENDER_MODE_HIDDEN;
        // 设置本地视频渲染视图
        rtcVideo.setLocalVideoCanvas(StreamIndex.STREAM_INDEX_MAIN, videoCanvas);
    }

    private void setRemoteRenderView(String uid) {
        if (textureView.getParent() == null) {
            remoteViewContainer.removeAllViews();
            remoteViewContainer.addView(textureView);
        }
        VideoCanvas videoCanvas = new VideoCanvas();
        videoCanvas.renderView = textureView;
        videoCanvas.renderMode = VideoCanvas.RENDER_MODE_HIDDEN;

        RemoteStreamKey remoteStreamKey = new RemoteStreamKey(roomID, uid, StreamIndex.STREAM_INDEX_MAIN);
        // 设置本地视频渲染视图
        rtcVideo.setRemoteVideoCanvas(remoteStreamKey, videoCanvas);
    }

    private void removeRemoteView(String uid) {
        RemoteStreamKey remoteStreamKey = new RemoteStreamKey(roomID, uid, StreamIndex.STREAM_INDEX_MAIN);
        rtcVideo.setRemoteVideoCanvas(remoteStreamKey, null);
    }


    // 悬浮窗需要先请求权限
    private void requestFloatingWindowPermission() {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M && !Settings.canDrawOverlays(this)) {
            Intent intent = new Intent(Settings.ACTION_MANAGE_OVERLAY_PERMISSION, Uri.parse("package:" + getPackageName()));
            startActivityForResult(intent, REQUEST_CODE_FLOATING_WINDOW);
        } else {
            // 已经获得了悬浮窗口权限，可以添加悬浮窗口
            addFloatingWindow();
        }
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == REQUEST_CODE_FLOATING_WINDOW) {
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M && Settings.canDrawOverlays(this)) {
                addFloatingWindow();
            } else {
                ToastUtil.showAlert(this, "未授予悬浮窗口权限，无法添加悬浮窗口");
            }
        }
    }

    private void addFloatingWindow() {
        remoteViewContainer.removeView(textureView);
        floatWindowManager.openWindow();
    }

    private void closeFloatingWindow() {
        floatWindowManager.closeWindow();
        if (textureView.getParent() != null) {
            remoteViewContainer.addView(textureView);
        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        if (requestCode == REQUEST_CODE_FLOATING_WINDOW) {
            if (grantResults.length > 0 && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                addFloatingWindow();
            } else {
                ToastUtil.showAlert(this, "未授予悬浮窗口权限，无法添加悬浮窗口");
            }
        }
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
        this.roomID = null;
    }

    IRTCVideoEventHandler rtcVideoEventHandler = new IRTCVideoEventHandler() {
    };

    IRTCRoomEventHandler rtcRoomEventHandler = new IRTCRoomEventHandler() {
        @Override
        public void onRoomStateChanged(String roomId, String uid, int state, String extraInfo) {
            super.onRoomStateChanged(roomId, uid, state, extraInfo);
            String info = String.format("roomId:%s, uid:%s, state:%d, extraInfo:%s", roomId, uid, state, extraInfo);
            ToastUtil.showShortToast(PictureInPictureActivity.this, info);
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
            ToastUtil.showLongToast(PictureInPictureActivity.this, "onLeaveRoom, stats:" + stats.toString());
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
        RTCVideo.destroyRTCVideo();
        closeFloatingWindow();
    }
}