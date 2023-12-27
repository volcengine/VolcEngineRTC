package rtc.volcengine.apiexample.examples;

import android.content.res.AssetManager;
import android.os.Bundle;
import android.util.Log;
import android.view.TextureView;
import android.view.View;
import android.widget.AdapterView;
import android.widget.Button;
import android.widget.EditText;
import android.widget.FrameLayout;
import android.widget.Spinner;

import com.ss.bytertc.engine.RTCRoom;
import com.ss.bytertc.engine.RTCRoomConfig;
import com.ss.bytertc.engine.RTCVideo;
import com.ss.bytertc.engine.UserInfo;
import com.ss.bytertc.engine.VideoCanvas;
import com.ss.bytertc.engine.VideoEncoderConfig;
import com.ss.bytertc.engine.data.MirrorType;
import com.ss.bytertc.engine.data.RemoteStreamKey;
import com.ss.bytertc.engine.data.StreamIndex;
import com.ss.bytertc.engine.data.VideoFrameInfo;
import com.ss.bytertc.engine.data.VideoOrientation;
import com.ss.bytertc.engine.data.VideoRotationMode;
import com.ss.bytertc.engine.handler.IRTCRoomEventHandler;
import com.ss.bytertc.engine.handler.IRTCVideoEventHandler;
import com.ss.bytertc.engine.type.ChannelProfile;
import com.ss.bytertc.engine.type.MediaStreamType;
import com.ss.bytertc.engine.type.RTCRoomStats;
import com.ss.bytertc.engine.type.StreamRemoveReason;
import com.ss.bytertc.engine.video.ByteWatermark;
import com.ss.bytertc.engine.video.RTCWatermarkConfig;
import com.ss.bytertc.engine.video.VideoCaptureConfig;

import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;

import rtc.volcengine.apiexample.BaseActivity;
import rtc.volcengine.apiexample.R;
import rtc.volcengine.apiexample.Utils.ToastUtil;
import rtc.volcengine.apiexample.common.Constants;
import rtc.volcengine.apiexample.common.annotations.ApiExample;
import rtc.volcengine.apiexample.examples.mediaplayer.MediaPlayerActivity;

/**
 * 功能名称： VolcEngineRTC 视频常用配置
 * 功能简单描述：修改视频常用的采集、编码参数，设置旋转角度、水印等功能
 * 参考文档：https://www.volcengine.com/docs/6348/70122
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
 *     setVideoCaptureConfig 设置 RTC SDK 内部采集时的视频采集参数
 *     setVideoEncoderConfig 设置视频编码参数
 *     setLocalVideoMirrorType 为采集到的视频流开启镜像
 *     setVideoWatermark 在指定视频流上添加水印
 *     clearVideoWatermark 清除水印
 *     setVideoCaptureRotation 设置本端采集的视频帧的旋转角度
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
 *    本Demo演示功能：视频常用参数的设置
 *    为了展示简单，所有功能的token都由客户端生成，接入SDK时建议将Token生成逻辑放在服务端
 */
@ApiExample(name = "视频配置", order = 7)
public class VideoConfigActivity extends BaseActivity {

    private FrameLayout localViewContainer;
    private FrameLayout remoteViewContainer;
    private Spinner localRenderMode, remoteRenderMode;
    private Spinner mirrorTypeSpinner;
    private Spinner videoOrientation, videoRotationMode;
    private Spinner capturePreference, encoderPreference;
    private EditText captureWidth, captureHeight, captureFrameRate;
    private EditText encoderWidth, encoderHeight, encoderFrameRate, maxBitrate, minBitrate;
    private Button btnSetCaptureConfig, btnSetEncoderConfig;
    private RTCVideo rtcVideo;
    private RTCRoom rtcRoom;
    private static final String roomID = "room_video_config";
    private String curRemoteUid;
    private TextureView localTextureView, remoteTextureView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_video_config);
        setTitle(R.string.title_video_config);
        initUI();
        initResource();


        rtcVideo = RTCVideo.createRTCVideo(this, Constants.APP_ID, rtcVideoEventHandler, null, null);
        // 设置本端渲染视图
        setLocalRenderView(VideoCanvas.RENDER_MODE_HIDDEN);
        // 开启音频采集
        rtcVideo.startVideoCapture();
        rtcVideo.startAudioCapture();
        joinRoom(roomID);
    }

    private void initUI() {
        localTextureView = new TextureView(this);
        remoteTextureView = new TextureView(this);
        localViewContainer = findViewById(R.id.local_view_container);
        remoteViewContainer = findViewById(R.id.remote_view_container);
        localRenderMode = findViewById(R.id.local_render_mode_spinner);
        remoteRenderMode = findViewById(R.id.remote_render_mode_spinner);
        mirrorTypeSpinner = findViewById(R.id.mirror_type_spinner);
        videoOrientation = findViewById(R.id.video_orientation_spinner);
        videoRotationMode = findViewById(R.id.video_rotation_mode_spinner);
        capturePreference = findViewById(R.id.capture_preference_spinner);
        encoderPreference = findViewById(R.id.encoder_preference_spinner);
        captureWidth = findViewById(R.id.capture_width);
        captureHeight = findViewById(R.id.capture_height);
        captureFrameRate = findViewById(R.id.capture_frame_rate);
        encoderWidth = findViewById(R.id.encoder_width);
        encoderHeight = findViewById(R.id.encoder_height);
        encoderFrameRate = findViewById(R.id.encoder_frame_rate);
        btnSetCaptureConfig = findViewById(R.id.btn_capture_config);
        btnSetEncoderConfig = findViewById(R.id.btn_encoder_config);
        minBitrate = findViewById(R.id.min_bit_rate);
        maxBitrate = findViewById(R.id.max_bit_rate);


        localRenderMode.setOnItemSelectedListener(itemSelectedListener);
        remoteRenderMode.setOnItemSelectedListener(itemSelectedListener);
        mirrorTypeSpinner.setOnItemSelectedListener(itemSelectedListener);
        videoOrientation.setOnItemSelectedListener(itemSelectedListener);
        videoRotationMode.setOnItemSelectedListener(itemSelectedListener);
        btnSetEncoderConfig.setOnClickListener(v -> setVideoEncoderConfig());
        btnSetCaptureConfig.setOnClickListener(v -> setVideoCaptureConfig());
        findViewById(R.id.btn_add_watermark).setOnClickListener(v -> addWatermark());
        findViewById(R.id.btn_clear_watermark).setOnClickListener(v -> clearWatermark());
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
    private void setLocalRenderView(int renderMode) {
        localViewContainer.removeAllViews();
        localViewContainer.addView(localTextureView);

        VideoCanvas videoCanvas = new VideoCanvas();
        videoCanvas.renderView = localTextureView;
        videoCanvas.renderMode = renderMode;
        // 设置本地视频渲染视图
        rtcVideo.setLocalVideoCanvas(StreamIndex.STREAM_INDEX_MAIN, videoCanvas);
    }

    private void setRemoteRenderView(String uid, int renderMode) {
        remoteViewContainer.removeAllViews();
        remoteViewContainer.addView(remoteTextureView);

        VideoCanvas videoCanvas = new VideoCanvas();
        videoCanvas.renderView = remoteTextureView;
        videoCanvas.renderMode = renderMode;

        RemoteStreamKey remoteStreamKey = new RemoteStreamKey(roomID, uid, StreamIndex.STREAM_INDEX_MAIN);
        // 设置本地视频渲染视图
        rtcVideo.setRemoteVideoCanvas(remoteStreamKey, videoCanvas);
    }

    private void removeRemoteView(String uid) {
        RemoteStreamKey remoteStreamKey = new RemoteStreamKey(roomID, uid, StreamIndex.STREAM_INDEX_MAIN);
        rtcVideo.setRemoteVideoCanvas(remoteStreamKey, null);
    }

    private void setVideoEncoderConfig() {
        String width = encoderWidth.getText().toString();
        String height = encoderHeight.getText().toString();
        String frameRate = encoderFrameRate.getText().toString();
        String minBitrateStr = minBitrate.getText().toString();
        String maxBitrateStr = maxBitrate.getText().toString();

        VideoEncoderConfig config = new VideoEncoderConfig();
        config.width = width.isEmpty() ? 1920 : Integer.parseInt(width);
        config.height = height.isEmpty() ? 1080 : Integer.parseInt(height);
        config.frameRate = frameRate.isEmpty() ? 30 : Integer.parseInt(frameRate);
        if (!minBitrateStr.isEmpty()) {
            config.minBitrate = Integer.parseInt(minBitrateStr);
        }
        if (!maxBitrateStr.isEmpty()) {
            config.maxBitrate = Integer.parseInt(maxBitrateStr);
        }
        switch (encoderPreference.getSelectedItem().toString()) {
            case "MaintainFramerate":
                config.encodePreference = VideoEncoderConfig.EncoderPreference.MAINTAIN_FRAMERATE;
                break;
            case "MaintainQuality":
                config.encodePreference = VideoEncoderConfig.EncoderPreference.MAINTAIN_QUALITY;
                break;
            case "Disabled":
                config.encodePreference = VideoEncoderConfig.EncoderPreference.DISABLED;
                break;
            case "Balance":
                config.encodePreference = VideoEncoderConfig.EncoderPreference.BALANCE;
                break;

        }
        rtcVideo.setVideoEncoderConfig(config);
    }

    private void setVideoCaptureConfig() {
        String width = captureWidth.getText().toString();
        String height = captureHeight.getText().toString();
        String frameRate = captureFrameRate.getText().toString();

        VideoCaptureConfig config = new VideoCaptureConfig();
        switch (capturePreference.getSelectedItem().toString()) {
            case "AUTO":
                config.capturePreference = VideoCaptureConfig.CapturePreference.AUTO;
                break;
            case "MANUAL":
                config.capturePreference = VideoCaptureConfig.CapturePreference.MANUAL;
                break;
            case "AUTO_PERFORMANCE":
                config.capturePreference = VideoCaptureConfig.CapturePreference.AUTO_PERFORMANCE;
                break;
        }
        if (config.capturePreference == VideoCaptureConfig.CapturePreference.MANUAL) {
            // capturePreference为manual时，手动设置视频参数才会生效
            config.width = width.isEmpty() ? 1920 : Integer.parseInt(width);
            config.height = height.isEmpty() ? 1080 : Integer.parseInt(height);
            config.frameRate = frameRate.isEmpty() ? 30 : Integer.parseInt(frameRate);
        }
        rtcVideo.setVideoCaptureConfig(config);
    }

    private void addWatermark() {
        String path = getExternalFilesDir("").getPath() + "/img.png";
        ByteWatermark byteWatermark = new ByteWatermark(0f, 0f, 0.5f ,0.5f);
        RTCWatermarkConfig config = new RTCWatermarkConfig(true, byteWatermark, byteWatermark);
        rtcVideo.setVideoWatermark(StreamIndex.STREAM_INDEX_MAIN, path, config);
    }

    private void clearWatermark() {
        rtcVideo.clearVideoWatermark(StreamIndex.STREAM_INDEX_MAIN);
    }

    AdapterView.OnItemSelectedListener itemSelectedListener = new AdapterView.OnItemSelectedListener() {
        @Override
        public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
            if (parent.getId() == R.id.local_render_mode_spinner) {
                switch (localRenderMode.getSelectedItem().toString()) {
                    case "RENDER_MODE_HIDDEN":
                        setLocalRenderView(VideoCanvas.RENDER_MODE_HIDDEN);
                        break;
                    case "RENDER_MODE_FIT":
                        setLocalRenderView(VideoCanvas.RENDER_MODE_FIT);
                        break;
                    case "RENDER_MODE_FILL":
                        setLocalRenderView(VideoCanvas.RENDER_MODE_FILL);
                        break;
                }
            } else if (parent.getId() == R.id.remote_render_mode_spinner) {
                switch (remoteRenderMode.getSelectedItem().toString()) {
                    case "RENDER_MODE_HIDDEN":
                        setRemoteRenderView(curRemoteUid, VideoCanvas.RENDER_MODE_HIDDEN);
                        break;
                    case "RENDER_MODE_FIT":
                        setRemoteRenderView(curRemoteUid, VideoCanvas.RENDER_MODE_FIT);
                        break;
                    case "RENDER_MODE_FILL":
                        setRemoteRenderView(curRemoteUid, VideoCanvas.RENDER_MODE_FILL);
                        break;
                }
            } else if (parent.getId() == R.id.mirror_type_spinner) {
                switch (mirrorTypeSpinner.getSelectedItem().toString()) {
                    case "MIRROR_TYPE_NONE":
                        rtcVideo.setLocalVideoMirrorType(MirrorType.MIRROR_TYPE_NONE);
                        break;
                    case "MIRROR_TYPE_RENDER":
                        rtcVideo.setLocalVideoMirrorType(MirrorType.MIRROR_TYPE_RENDER);
                        break;
                    case "MIRROR_TYPE_RENDER_AND_ENCODER":
                        rtcVideo.setLocalVideoMirrorType(MirrorType.MIRROR_TYPE_RENDER_AND_ENCODER);
                        break;
                }
            } else if (parent.getId() == R.id.video_orientation_spinner) {
                switch (videoOrientation.getSelectedItem().toString()) {
                    case "Adaptive":
                        rtcVideo.setVideoOrientation(VideoOrientation.ADAPTIVE);
                        break;
                    case "Portrait":
                        rtcVideo.setVideoOrientation(VideoOrientation.PORTRAIT);
                        break;
                    case "Landscape":
                        rtcVideo.setVideoOrientation(VideoOrientation.LANDSCAPE);
                        break;
                }
            } else if (parent.getId() == R.id.video_rotation_mode_spinner) {
                switch (videoRotationMode.getSelectedItem().toString()) {
                    case "FollowApp":
                        rtcVideo.setVideoRotationMode(VideoRotationMode.FOLLOW_APP);
                        break;
                    case "FollowGSensor":
                        rtcVideo.setVideoRotationMode(VideoRotationMode.FOLLOW_GSENSOR);
                        break;
                }
            }
        }

        @Override
        public void onNothingSelected(AdapterView<?> parent) {

        }
    };

    IRTCVideoEventHandler rtcVideoEventHandler = new IRTCVideoEventHandler() {
        @Override
        public void onLocalVideoSizeChanged(StreamIndex streamIndex, VideoFrameInfo frameInfo) {
            super.onLocalVideoSizeChanged(streamIndex, frameInfo);
            String info = String.format("onLocalVideoSizeChanged, width:%d, height:%d, rotation:%d", frameInfo.getWidth(), frameInfo.getHeight(), frameInfo.rotation);
            ToastUtil.showShortToast(VideoConfigActivity.this, info);
        }
    };

    IRTCRoomEventHandler rtcRoomEventHandler = new IRTCRoomEventHandler() {
        @Override
        public void onRoomStateChanged(String roomId, String uid, int state, String extraInfo) {
            super.onRoomStateChanged(roomId, uid, state, extraInfo);
            String info = String.format("roomId:%s, uid:%s, state:%d, extraInfo:%s", roomId, uid, state, extraInfo);
            ToastUtil.showShortToast(VideoConfigActivity.this, info);
        }

        @Override
        public void onUserPublishStream(String uid, MediaStreamType type) {
            super.onUserPublishStream(uid, type);
            curRemoteUid = uid;
            runOnUiThread(() -> {
                // 设置远端视频渲染视图
                setRemoteRenderView(uid, VideoCanvas.RENDER_MODE_HIDDEN);
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
        public void onUserJoined(UserInfo userInfo, int elapsed) {
            super.onUserJoined(userInfo, elapsed);
            ToastUtil.showShortToast(VideoConfigActivity.this, "onUserJoined, uid:" + userInfo.getUid());
        }

        @Override
        public void onLeaveRoom(RTCRoomStats stats) {
            super.onLeaveRoom(stats);
            ToastUtil.showLongToast(VideoConfigActivity.this, "onLeaveRoom, stats:" + stats.toString());
        }
    };

    private void initResource() {
        copyAssetsFile("img.png");

    }

    private void copyAssetsFile(String fileName) {
        final File file = new File(getExternalFilesDir(""), fileName);
        if (file.exists()) {
            Log.i("AudioEffect", "File exists.");
            return;
        }
        try {
            // get Assets.
            AssetManager assetManager = getAssets();
            InputStream is = assetManager.open(fileName);
            FileOutputStream fos = new FileOutputStream(file);
            byte[] buffer = new byte[1024];
            int len = 0;
            // Write file.
            while ((len = is.read(buffer)) != -1) {
                fos.write(buffer, 0, len);
            }
            fos.close();
            is.close();
        } catch (Exception e) {
            e.printStackTrace();
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
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        leaveRoom();
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