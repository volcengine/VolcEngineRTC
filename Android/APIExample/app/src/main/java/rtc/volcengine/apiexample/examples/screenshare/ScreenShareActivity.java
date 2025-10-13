package rtc.volcengine.apiexample.examples.screenshare;

import android.content.Context;
import android.content.Intent;
import android.media.projection.MediaProjectionManager;
import android.os.Build;
import android.os.Bundle;
import android.text.TextUtils;
import android.util.Log;
import android.view.TextureView;
import android.widget.Button;
import android.widget.EditText;
import android.widget.FrameLayout;

import androidx.annotation.Nullable;

import com.ss.bytertc.base.media.screen.RXScreenCaptureService;
import com.ss.bytertc.engine.RTCEngine;
import com.ss.bytertc.engine.RTCRoom;
import com.ss.bytertc.engine.RTCRoomConfig;
import com.ss.bytertc.engine.UserInfo;
import com.ss.bytertc.engine.VideoCanvas;
import com.ss.bytertc.engine.VideoEncoderConfig;
import com.ss.bytertc.engine.data.EngineConfig;
import com.ss.bytertc.engine.data.ScreenMediaType;
import com.ss.bytertc.engine.data.StreamInfo;
import com.ss.bytertc.engine.handler.IRTCEngineEventHandler;
import com.ss.bytertc.engine.handler.IRTCRoomEventHandler;
import com.ss.bytertc.engine.type.ChannelProfile;
import com.ss.bytertc.engine.type.RTCRoomStats;
import com.ss.bytertc.engine.type.VideoDeviceType;

import rtc.volcengine.apiexample.BaseActivity;
import rtc.volcengine.apiexample.R;
import rtc.volcengine.apiexample.Utils.ToastUtil;
import rtc.volcengine.apiexample.common.Constants;
import rtc.volcengine.apiexample.common.annotations.ApiExample;

@ApiExample(name = "屏幕共享", order = 8.2)
public class ScreenShareActivity extends BaseActivity {

    private static final String TAG = "ScreenShareActivity";

    private FrameLayout localViewContainer;
    private FrameLayout remoteViewContainer;

    private MediaProjectionManager projectionManager;

    private Button btnJoinRoom, btnStartScreenShare;
    private EditText roomIdInput;
    private boolean isJoined;
    private boolean isShareing;
    private RTCEngine rtcVideo;
    private RTCRoom rtcRoom;
    private String roomID;
    public static final int REQUEST_CODE_OF_SCREEN_SHARING = 101;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_screen_share);

        setTitle(R.string.title_screen_share);
        initUI();


        EngineConfig config = new EngineConfig();
        config.context = this;
        config.appID = Constants.APP_ID;
        rtcVideo = RTCEngine.createRTCEngine(config, rtcVideoEventHandler);
        // 设置本端渲染视图
        setLocalRenderView();
        // 开启音频采集
        startCameraCapture();
    }

    private void initUI() {
        localViewContainer = findViewById(R.id.local_view_container);
        remoteViewContainer = findViewById(R.id.remote_view_container);
        btnJoinRoom = findViewById(R.id.btn_join_room);
        roomIdInput = findViewById(R.id.room_id_input);
        btnStartScreenShare = findViewById(R.id.btn_start_screen_share);


        btnJoinRoom.setOnClickListener(v -> {
            String roomId = roomIdInput.getText().toString();
            localUid = ((EditText) findViewById(R.id.user_id_input)).getText().toString();

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

        btnStartScreenShare.setOnClickListener(v -> {
            if (!isJoined) {
                return;
            }
            if (isShareing) {
                stopScreenShare();
                isShareing = false;
                btnStartScreenShare.setText("开始投屏");
                startCameraCapture();
                return;
            }

            startScreenShare();
            isShareing = true;
            btnStartScreenShare.setText("停止投屏");
        });

    }

    private void startScreenShare() {
        requestPermissionForScreenSharing();
    }

    private void stopScreenShare() {
        rtcVideo.stopScreenCapture();
    }

    // 开启音频采集
    private void startCameraCapture() {
        rtcVideo.startVideoCapture();
        rtcVideo.startAudioCapture();
    }

    /*** 向系统发起屏幕共享的权限请求*/
    private void requestPermissionForScreenSharing() {
        if (Build.VERSION.SDK_INT < Build.VERSION_CODES.LOLLIPOP) {
            ToastUtil.showShortToast(this, "当前系统版本过低，无法支持屏幕共享");
            return;
        }
        if (projectionManager == null) {
            projectionManager = (MediaProjectionManager) getApplicationContext().getSystemService(Context.MEDIA_PROJECTION_SERVICE);
        }
        if (projectionManager != null) {
            startActivityForResult(projectionManager.createScreenCaptureIntent(), REQUEST_CODE_OF_SCREEN_SHARING);
        } else {
            ToastUtil.showShortToast(this, "当前系统版本过低，无法支持屏幕共享");
        }
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
        if (projectionManager != null && requestCode == REQUEST_CODE_OF_SCREEN_SHARING && resultCode == RESULT_OK) {
            startScreenCapture(data);
        } else {
            super.onActivityResult(requestCode, resultCode, data);
        }
    }

    private void startScreenCapture(Intent data) {
        startRXScreenCaptureService(data);
        //编码参数
        VideoEncoderConfig config = new VideoEncoderConfig();
        config.width = 720;
        config.height =  1280;
        config.frameRate = 15;
        config.maxBitrate = 1600;
        rtcVideo.setVideoEncoderConfig(config);
        // 开启屏幕视频数据采集
        rtcVideo.startScreenCapture(ScreenMediaType.SCREEN_MEDIA_TYPE_VIDEO_AND_AUDIO, data);
    }

    private void startRXScreenCaptureService(@Nullable Intent data) {
        Context context = getApplicationContext();
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.Q) {
            Intent iData = new Intent();
            iData.putExtra(RXScreenCaptureService.KEY_LARGE_ICON, R.mipmap.icon);
            iData.putExtra(RXScreenCaptureService.KEY_SMALL_ICON, R.mipmap.icon);
            iData.putExtra(RXScreenCaptureService.KEY_LAUNCH_ACTIVITY, R.string.app_name);
            iData.putExtra(RXScreenCaptureService.KEY_LAUNCH_ACTIVITY, this.getClass().getCanonicalName());
            iData.putExtra(RXScreenCaptureService.KEY_CONTENT_TEXT, "正在录制/投射您的屏幕");
            iData.putExtra(RXScreenCaptureService.KEY_RESULT_DATA, data);
            context.startForegroundService(RXScreenCaptureService.getServiceIntent(context, RXScreenCaptureService.COMMAND_LAUNCH, iData));
        }
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
        RTCRoomConfig roomConfig = new RTCRoomConfig(ChannelProfile.CHANNEL_PROFILE_CHAT_ROOM, isAutoPublishAudio, isAutoPublishVideo, isAutoSubscribeAudio, isAutoSubscribeVideo);
        // 加入房间
        rtcRoom.joinRoom(token, userInfo, true, roomConfig);;
        rtcRoom.publishStreamAudio(true);
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
        rtcVideo.setLocalVideoCanvas(videoCanvas);
    }

    private void setRemoteRenderView(String streamId) {
        TextureView textureView = new TextureView(this);
        remoteViewContainer.removeAllViews();
        remoteViewContainer.addView(textureView);
        VideoCanvas videoCanvas = new VideoCanvas();
        videoCanvas.renderView = textureView;
        videoCanvas.renderMode = VideoCanvas.RENDER_MODE_HIDDEN;
        // 设置远端视频渲染视图
        rtcVideo.setRemoteVideoCanvas(streamId, videoCanvas);
    }

    private void removeRemoteView(String streamId) {
        remoteViewContainer.removeAllViews();
        rtcVideo.setRemoteVideoCanvas(streamId, null);
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

    IRTCEngineEventHandler rtcVideoEventHandler = new IRTCEngineEventHandler() {
        @Override
        public void onVideoDeviceStateChanged(String deviceId, VideoDeviceType deviceType, int deviceState, int deviceError) {
            Log.i(TAG, "onVideoDeviceStateChanged, type: " + deviceType + " state:" + deviceState);
        }
    };

    IRTCRoomEventHandler rtcRoomEventHandler = new IRTCRoomEventHandler() {
        @Override
        public void onRoomStateChanged(String roomId, String uid, int state, String extraInfo) {
            super.onRoomStateChanged(roomId, uid, state, extraInfo);
            String info = String.format("roomId:%s, uid:%s, state:%d, extraInfo:%s", roomId, uid, state, extraInfo);
            ToastUtil.showShortToast(ScreenShareActivity.this, info);
        }

        @Override
        public void onUserPublishStreamVideo(String streamId, StreamInfo streamInfo, boolean isPublish) {
            if (isPublish) {
                Log.i(TAG, "onUserPublishScreen, streamId: " + streamId);
                runOnUiThread(() -> {
                    // 设置远端视频渲染视图
                    setRemoteRenderView(streamId);
                });
            } else {
                Log.i(TAG, "onUserUnpublishScreen, uid: " + streamId);
                runOnUiThread(() -> {
                    // 解除远端视频渲染视图绑定
                    removeRemoteView(streamId);
                });
            }
        }


        @Override
        public void onLeaveRoom(RTCRoomStats stats) {
            super.onLeaveRoom(stats);
            ToastUtil.showLongToast(ScreenShareActivity.this, "onLeaveRoom, stats:" + stats.toString());
        }

        @Override
        public void onUserLeave(String uid, int reason) {
            super.onUserLeave(uid, reason);
            runOnUiThread(() -> {
                // 解除远端视频渲染视图绑定
                removeRemoteView(uid);
            });
        }
    };

    @Override
    protected void onDestroy() {
        super.onDestroy();
        if (rtcVideo != null) {
            rtcVideo.stopAudioCapture();
            rtcVideo.stopVideoCapture();
            rtcVideo.stopScreenCapture();
        }
        if (rtcRoom != null) {
            rtcRoom.publishStreamVideo(false);
            rtcRoom.publishStreamAudio(false);
            rtcRoom.destroy();
            rtcRoom = null;
        }
        RTCEngine.destroyRTCEngine();
    }
}

