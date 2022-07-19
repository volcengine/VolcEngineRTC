package com.ss.video.rtc.demo.advanced;

import static com.ss.bytertc.engine.data.VideoSourceType.VIDEO_SOURCE_TYPE_EXTERNAL;
import static com.ss.bytertc.engine.data.VideoSourceType.VIDEO_SOURCE_TYPE_INTERNAL;

import android.content.Context;
import android.content.Intent;
import android.hardware.Camera;
import android.os.Bundle;
import android.os.Handler;
import android.os.HandlerThread;
import android.os.Looper;
import android.text.TextUtils;
import android.util.Log;
import android.view.TextureView;
import android.view.View;
import android.view.ViewGroup;
import android.widget.FrameLayout;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentTransaction;

import com.ss.bytertc.engine.RTCEngine;
import com.ss.bytertc.engine.RTCRoomConfig;
import com.ss.bytertc.engine.UserInfo;
import com.ss.bytertc.engine.VideoCanvas;
import com.ss.bytertc.engine.VideoEncoderConfig;
import com.ss.bytertc.engine.data.AudioRoute;
import com.ss.bytertc.engine.data.CameraId;
import com.ss.bytertc.engine.data.MirrorType;
import com.ss.bytertc.engine.data.RemoteStreamKey;
import com.ss.bytertc.engine.data.StreamIndex;
import com.ss.bytertc.engine.data.VideoFrameInfo;
import com.ss.bytertc.engine.data.VideoPixelFormat;
import com.ss.bytertc.engine.data.VideoRotation;
import com.ss.bytertc.engine.handler.IRTCEngineEventHandler;
import com.ss.bytertc.engine.type.ChannelProfile;
import com.ss.bytertc.engine.type.MediaStreamType;
import com.ss.bytertc.engine.video.IVideoSink;
import com.ss.bytertc.engine.video.builder.CpuBufferVideoFrameBuilder;
import com.ss.rtc.demo.advanced.R;
import com.ss.video.rtc.demo.advanced.effects.CVDialog;
import com.ss.video.rtc.demo.advanced.effects.VideoEffectController;
import com.ss.video.rtc.demo.advanced.entity.VideoConfigEntity;
import com.ss.video.rtc.demo.advanced.external.CustomCapture;
import com.ss.video.rtc.demo.advanced.external.CustomRenderView;
import com.ss.video.rtc.demo.advanced.utils.CommonUtil;
import com.ss.video.rtc.demo.basic_module.utils.SafeToast;

import java.nio.ByteBuffer;
import java.nio.CharBuffer;
import java.nio.charset.Charset;
import java.nio.charset.CharsetDecoder;
import java.nio.charset.StandardCharsets;
import java.util.List;
import java.util.Locale;
import java.util.concurrent.TimeUnit;

/**
 * VolcEngineRTC 视频通话的主页面
 * 本示例不限制房间内最大用户数；同时最多渲染四个用户的视频数据（自己和三个远端用户视频数据）；
 * <p>
 * 包含如下简单功能：
 * - 创建引擎
 * - 设置视频发布参数
 * - 渲染自己的视频数据
 * - 加入音视频通话房间
 * - 切换前置/后置摄像头
 * - 打开/关闭麦克风
 * - 打开/关闭摄像头
 * - 切换听筒/扬声器
 * - 渲染远端用户的视频数据
 * - 离开房间
 * - 销毁引擎
 * <p>
 * 实现一个基本的音视频通话的流程如下：
 * 1.创建引擎 {@link RTCEngine#create(Context, String, IRTCEngineEventHandler)}
 * 2.设置编码参数 {@link RTCEngine#setVideoEncoderConfig(List)}
 * 3.开启本地视频采集 {@link RTCEngine#startVideoCapture()}
 * 4.设置本地视频渲染视图 {@link RTCEngine#setLocalVideoCanvas(StreamIndex, VideoCanvas)}
 * 5.加入音视频通话房间 {@link RTCEngine#joinRoom(java.lang.String, java.lang.String,
 *   com.ss.bytertc.engine.UserInfo, com.ss.bytertc.engine.RTCRoomConfig)}
 * 6.在收到远端用户视频首帧之后，设置用户的视频渲染视图 {@link RTCEngine#setRemoteVideoCanvas(String, StreamIndex, VideoCanvas)}
 * 7.在用户离开房间之后移出用户的视频渲染视图 {@link RTCRoomActivity#removeRemoteView(String)}
 * 8.离开音视频通话房间 {@link RTCEngine#leaveRoom()}
 * 9.销毁引擎 {@link RTCEngine#destroyEngine(RTCEngine)}
 * <p>
 * 有以下常见的注意事项：
 * 1.创建引擎时，需要注册 RTC 事件回调的接口，类型是 IRTCEngineEventHandler 用户需要持有这个引用，例如本示例中
 * 将其作为 Activity 成员变量。因为这个引用在引擎内部是弱引用，可能会被系统回收导致收不到回调事件
 * 2.本示例中，我们在 {@link IRTCEngineEventHandler#onFirstRemoteVideoFrameDecoded} 这个事件中给远端用户
 * 设置远端用户视频渲染视图，这个回调表示的是收到了远端用户的视频第一帧。当然也可以在
 * {@link IRTCEngineEventHandler#onUserJoined} 回调中设置远端用户视频渲染视图
 * 3.SDK 回调不在主线程，UI 操作需要切换线程
 * 4.用户成功加入房间后，SDK 会通过 {@link IRTCEngineEventHandler#onUserJoined} 回调已经在房间的用户信息
 * 5.SDK 支持同时发布多个参数的视频流，接口是 {@link RTCEngine#setVideoEncoderConfig}
 * 6.加入房间时，需要有有效的 token，加入失败时会通过 {@link IRTCEngineEventHandler#onError(int)} 输出对应的错误码
 * 7.用户可以通过 {@link RTCEngine#joinRoom(java.lang.String, java.lang.String,
 *   com.ss.bytertc.engine.UserInfo, com.ss.bytertc.engine.RTCRoomConfig)} 中的 ChannelProfile
 *   来获得不同场景下的性能优化。本示例是音视频通话场景，因此使用 {@link ChannelProfile#CHANNEL_PROFILE_COMMUNICATION}
 * 8.不需要在每次加入/退出房间时销毁引擎。本示例退出房间时销毁引擎是为了展示完整的使用流程
 * <p>
 * 详细的API文档参见{https://www.volcengine.com/docs/6348/70080}
 */
public class RTCRoomActivity extends AppCompatActivity implements ConfigManger.ConfigObserver {
    private static final String TAG = "RTCRoomActivity";

    private ImageView mSpeakerIv;
    private ImageView mAudioIv;
    private ImageView mVideoIv;
    private ImageView mSetting;
    private ImageView mBeautyIv;

    private CVDialog mCVDialog;

    private boolean mIsSpeakerPhone = true;
    private boolean mIsMuteAudio = false;
    private boolean mIsMuteVideo = false;
    private CameraId mCameraID = CameraId.CAMERA_ID_FRONT;

    private FrameLayout mSelfContainer;
    private final FrameLayout[] mRemoteContainerArray = new FrameLayout[3];
    private final TextView[] mUserIdTvArray = new TextView[3];
    private final String[] mShowUidArray = new String[3];

    private RTCEngine mInstance;
    private IRTCEngineEventHandler mIRtcEngineEventHandler = new IRTCEngineEventHandler() {

        /**
         * 第一帧远端视频流在视图上渲染成功后，收到此回调。
         */
        @Override
        public void onFirstRemoteVideoFrameDecoded(RemoteStreamKey remoteStreamKey, VideoFrameInfo frameInfo) {
            super.onFirstRemoteVideoFrameDecoded(remoteStreamKey, frameInfo);
            Log.d("IRtcEngineEventHandler", "onFirstRemoteVideoFrame: " + remoteStreamKey.toString());
            runOnUiThread(() -> setRemoteView(remoteStreamKey));
        }

        /**
         * 远端主播角色用户加入房间回调。
         */
        @Override
        public void onUserJoined(UserInfo userInfo, int elapsed) {
            super.onUserJoined(userInfo, elapsed);
            Log.d("IRtcEngineEventHandler", "onUserJoined: " + userInfo.getUid());
        }

        /**
         * 远端用户离开房间回调。
         */
        @Override
        public void onUserLeave(String uid, int reason) {
            super.onUserLeave(uid, reason);
            Log.d("IRtcEngineEventHandler", "onUserOffline: " + uid);
            runOnUiThread(() -> removeRemoteView(uid));
        }

        /**
         * 警告回调，详细可以看 {https://www.volcengine.com/docs/6348/70082#warncode}
         */
        @Override
        public void onWarning(int warn) {
            super.onWarning(warn);
            Log.d("IRtcEngineEventHandler", "onWarning: " + warn);
        }

        /**
         * 错误回调，详细可以看 {https://www.volcengine.com/docs/6348/70082#errorcode}
         */
        @Override
        public void onError(int err) {
            super.onError(err);
            Log.d("IRtcEngineEventHandler", "onError: " + err);
            showAlertDialog(String.format(Locale.US, "error: %d", err));
        }

        @Override
        public void onUserMessageReceived(String uid, String message) {
            super.onUserMessageReceived(uid, message);
            showMessage("收到点对点消息", uid, message);
        }

        @Override
        public void onUserBinaryMessageReceived(String uid, ByteBuffer message) {
            super.onUserBinaryMessageReceived(uid, message);
            showMessage("收到点对点消息", uid, byteBufferToString(message));
        }

        @Override
        public void onRoomMessageReceived(String uid, String message) {
            super.onRoomMessageReceived(uid, message);
            showMessage("收到广播消息", uid, message);
        }

        @Override
        public void onRoomBinaryMessageReceived(String uid, ByteBuffer message) {
            super.onRoomBinaryMessageReceived(uid, message);
            showMessage("收到广播消息", uid, byteBufferToString(message));
        }

        @Override
        public void onUserMessageSendResult(long msgid, int error) {
            super.onUserMessageSendResult(msgid, error);
            String tip;
            if (error != 0) {
                tip = String.format(Locale.US, "点对点消息发送失败(%d)", error);
            } else {
                tip = "点对点消息发送成功";
            }
            runOnUiThread(() -> SafeToast.show(RTCRoomActivity.this, tip, Toast.LENGTH_SHORT));
        }

        @Override
        public void onSEIMessageReceived(RemoteStreamKey remoteStreamKey, ByteBuffer message) {
            super.onSEIMessageReceived(remoteStreamKey, message);
            runOnUiThread(() -> showMessage("收到SEI消息", remoteStreamKey.getUserId(), byteBufferToString(message)));
        }

        private String byteBufferToString(ByteBuffer buffer) {
            CharBuffer charBuffer;
            try {
                Charset charset = StandardCharsets.UTF_8;
                CharsetDecoder decoder = charset.newDecoder();
                charBuffer = decoder.decode(buffer);
                buffer.flip();
                return charBuffer.toString();
            } catch (Exception ex) {
                ex.printStackTrace();
                return null;
            }
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_room);
        Intent intent = getIntent();
        String roomId = intent.getStringExtra(Constants.ROOM_ID_EXTRA);
        String userId = intent.getStringExtra(Constants.USER_ID_EXTRA);

        initUI(roomId, userId);
        initEngineAndJoinRoom(roomId, userId);
        ConfigManger.getInstance().addObserver(this);
        VideoEffectController.getInstance().init(mInstance);
        Log.e("RTCRoom", "RTCRoomActivity.onCreate  this:" + this);
    }

    private void initUI(String roomId, String userId) {
        mSelfContainer = findViewById(R.id.self_video_container);
        mRemoteContainerArray[0] = findViewById(R.id.remote_video_0_container);
        mRemoteContainerArray[1] = findViewById(R.id.remote_video_1_container);
        mRemoteContainerArray[2] = findViewById(R.id.remote_video_2_container);
        mUserIdTvArray[0] = findViewById(R.id.remote_video_0_user_id_tv);
        mUserIdTvArray[1] = findViewById(R.id.remote_video_1_user_id_tv);
        mUserIdTvArray[2] = findViewById(R.id.remote_video_2_user_id_tv);
        findViewById(R.id.switch_camera).setOnClickListener((v) -> onSwitchCameraClick());
        mSpeakerIv = findViewById(R.id.switch_audio_router);
        mAudioIv = findViewById(R.id.switch_local_audio);
        mVideoIv = findViewById(R.id.switch_local_video);
        mSetting = findViewById(R.id.setting_btn);
        mBeautyIv = findViewById(R.id.beauty);
        findViewById(R.id.hang_up).setOnClickListener((v) -> onBackPressed());
        mSpeakerIv.setOnClickListener((v) -> updateSpeakerStatus());
        mAudioIv.setOnClickListener((v) -> updateLocalAudioStatus());
        mVideoIv.setOnClickListener((v) -> updateLocalVideoStatus());
        mSetting.setOnClickListener(v -> {
            RoomSettingsDialog settingsDialog = new RoomSettingsDialog();
            settingsDialog.setConfig(mInstance);
            FragmentManager fragmentManager = getSupportFragmentManager();
            FragmentTransaction ft = fragmentManager.beginTransaction();
            ft.add(settingsDialog, RoomSettingsDialog.TAG_FOR_SHOW);
            ft.commitAllowingStateLoss();
        });
        mBeautyIv.setOnClickListener((v) -> showCVDialog());
        TextView roomIDTV = findViewById(R.id.room_id_text);
        TextView userIDTV = findViewById(R.id.self_video_user_id_tv);
        roomIDTV.setText(String.format("RoomID:%s", roomId));
        userIDTV.setText(String.format("UserID:%s", userId));
    }

    private void showCVDialog() {
        if (mCVDialog == null) {
            mCVDialog = new CVDialog(this, mInstance);
        }
        mCVDialog.show();
    }

    private final VideoConfigEntity mVideoConfig = ConfigManger.getInstance().getVideoConfig();

    private void initEngineAndJoinRoom(String roomId, String userId) {
        // 创建引擎
        mInstance = RTCEngine.create(getApplicationContext(), Constants.APPID, mIRtcEngineEventHandler);
        // 设置视频发布参数
        VideoEncoderConfig videoEncoderConfig = new VideoEncoderConfig(
                mVideoConfig.getResolution().first,
                mVideoConfig.getResolution().second,
                mVideoConfig.getFrameRate(),
                mVideoConfig.getBitRate(),
                VideoEncoderConfig.ScaleMode.SCALE_MODE_AUTO.getValue());
        mInstance.setVideoEncoderConfig(videoEncoderConfig);
        setLocalRenderView(userId);
        // 开启本地视频采集
        startVideoCapture();
        // 开启本地音频采集
        mInstance.startAudioCapture();
        // 加入房间
        RTCRoomConfig roomConfig = new RTCRoomConfig(ChannelProfile.CHANNEL_PROFILE_COMMUNICATION,
                true, true, true);
        int joinRoomRes = mInstance.joinRoom(Constants.TOKEN, roomId,
                UserInfo.create(userId, ""), roomConfig);
        Log.i(TAG, "initEngineAndJoinRoom: " + joinRoomRes);
    }

    private void setLocalRenderView(String uid) {
        boolean customRender = ConfigManger.getInstance().isCustomRender();
        int index = mVideoConfig.mLocalVideoMirrorType == 2 ? 3 : mVideoConfig.mLocalVideoMirrorType;
        mInstance.setLocalVideoMirrorType(MirrorType.fromId(index));
        if (customRender) {
            IVideoSink videoSink = new CustomRenderView(this);
            FrameLayout.LayoutParams params = new FrameLayout.LayoutParams(
                    ViewGroup.LayoutParams.MATCH_PARENT,
                    ViewGroup.LayoutParams.MATCH_PARENT);
            mSelfContainer.removeAllViews();
            mSelfContainer.addView((View) videoSink, params);
            mInstance.setLocalVideoSink(StreamIndex.STREAM_INDEX_MAIN, videoSink, IVideoSink.PixelFormat.I420);
        } else {
            VideoCanvas videoCanvas = new VideoCanvas();
            videoCanvas.uid = uid;
            videoCanvas.isScreen = false;
            videoCanvas.renderMode = mVideoConfig.mLocalVideoFillMode == 1
                    ? VideoCanvas.RENDER_MODE_HIDDEN
                    : VideoCanvas.RENDER_MODE_FIT;
            videoCanvas.renderView = new TextureView(this);
            FrameLayout.LayoutParams params = new FrameLayout.LayoutParams(
                    ViewGroup.LayoutParams.MATCH_PARENT,
                    ViewGroup.LayoutParams.MATCH_PARENT);
            mSelfContainer.removeAllViews();
            mSelfContainer.addView(videoCanvas.renderView, params);
            // 设置本地视频渲染视图
            mInstance.setLocalVideoCanvas(StreamIndex.STREAM_INDEX_MAIN, videoCanvas);
        }
    }

    private void setRemoteRenderView(RemoteStreamKey remoteStreamKey, FrameLayout container) {
        boolean customRender = ConfigManger.getInstance().isCustomRender();
        if (customRender) {
            IVideoSink videoSink = new CustomRenderView(this);
            FrameLayout.LayoutParams params = new FrameLayout.LayoutParams(
                    ViewGroup.LayoutParams.MATCH_PARENT,
                    ViewGroup.LayoutParams.MATCH_PARENT);
            container.removeAllViews();
            container.addView((View) videoSink, params);
            mInstance.setRemoteVideoSink(remoteStreamKey, videoSink, IVideoSink.PixelFormat.I420);
        } else {
            VideoCanvas videoCanvas = new VideoCanvas();
            videoCanvas.uid = remoteStreamKey.getUserId();
            videoCanvas.isScreen = false;
            videoCanvas.renderMode = mVideoConfig.mRemoteVideoFillMode == 1
                    ? VideoCanvas.RENDER_MODE_HIDDEN
                    : VideoCanvas.RENDER_MODE_FIT;
            videoCanvas.renderView = new TextureView(this);
            FrameLayout.LayoutParams params = new FrameLayout.LayoutParams(
                    ViewGroup.LayoutParams.MATCH_PARENT,
                    ViewGroup.LayoutParams.MATCH_PARENT);
            container.removeAllViews();
            container.addView(videoCanvas.renderView, params);
            // 设置远端用户视频渲染视图
            mInstance.setRemoteVideoCanvas(remoteStreamKey.getUserId(), StreamIndex.STREAM_INDEX_MAIN, videoCanvas);
        }
    }

    private void setRemoteView(RemoteStreamKey remoteStreamKey) {
        int emptyInx = -1;
        String uid = remoteStreamKey.getUserId();
        for (int i = 0; i < mShowUidArray.length; i++) {
            if (TextUtils.isEmpty(mShowUidArray[i]) && emptyInx == -1) {
                emptyInx = i;
            } else if (TextUtils.equals(uid, mShowUidArray[i])) {
                return;
            }
        }
        if (emptyInx < 0) {
            return;
        }
        mShowUidArray[emptyInx] = uid;
        mUserIdTvArray[emptyInx].setText(String.format("UserId:%s", uid));
        setRemoteRenderView(remoteStreamKey, mRemoteContainerArray[emptyInx]);
    }

    private void removeRemoteView(String uid) {
        for (int i = 0; i < mShowUidArray.length; i++) {
            if (TextUtils.equals(uid, mShowUidArray[i])) {
                mShowUidArray[i] = null;
                mUserIdTvArray[i].setText(null);
                mRemoteContainerArray[i].removeAllViews();
            }
        }
    }

    private void onSwitchCameraClick() {
        boolean isCustomCapture = ConfigManger.getInstance().isCustomCapture();
        if (isCustomCapture) {
            CustomCapture.ins().switchCamera();
            return;
        }
        // 切换前置/后置摄像头（默认使用前置摄像头）
        if (mCameraID.equals(CameraId.CAMERA_ID_FRONT)) {
            mCameraID = CameraId.CAMERA_ID_BACK;
        } else {
            mCameraID = CameraId.CAMERA_ID_FRONT;
        }
        mInstance.switchCamera(mCameraID);
    }

    private void updateSpeakerStatus() {
        mIsSpeakerPhone = !mIsSpeakerPhone;
        // 设置使用哪种方式播放音频数据
        mInstance.setAudioRoute(mIsSpeakerPhone ? AudioRoute.AUDIO_ROUTE_SPEAKERPHONE
                : AudioRoute.AUDIO_ROUTE_EARPIECE);
        mSpeakerIv.setImageResource(mIsSpeakerPhone ? R.drawable.speaker_on : R.drawable.speaker_off);
    }

    private void updateLocalAudioStatus() {
        mIsMuteAudio = !mIsMuteAudio;
        // 开启/关闭本地音频发送
        if (mIsMuteAudio) {
            mInstance.unpublishStream(MediaStreamType.RTC_MEDIA_STREAM_TYPE_AUDIO);
        } else {
            mInstance.publishStream(MediaStreamType.RTC_MEDIA_STREAM_TYPE_AUDIO);
        }
        mAudioIv.setImageResource(mIsMuteAudio ? R.drawable.mute_audio : R.drawable.normal_audio);
    }

    private void updateLocalVideoStatus() {
        mIsMuteVideo = !mIsMuteVideo;
        if (mIsMuteVideo) {
            // 关闭视频采集
            stopVideoCapture();
        } else {
            // 开启视频采集
            startVideoCapture();
        }
        mVideoIv.setImageResource(mIsMuteVideo ? R.drawable.mute_video : R.drawable.normal_video);
    }

    private void showAlertDialog(String message) {
        runOnUiThread(() -> {
            AlertDialog.Builder builder = new AlertDialog.Builder(this);
            builder.setMessage(message);
            builder.setPositiveButton("知道了", (dialog, which) -> dialog.dismiss());
            builder.create().show();
        });
    }

    /* 视频采集:主要是自定义外部采集源相关功能 */

    /* 视频发布数据线程 */
    private HandlerThread mPushStreamThread;
    /* 视频发布数据线程对应Handler */
    private Handler mPushStreamHandler;
    private boolean mIsCapturing;


    private final Camera.PreviewCallback mPreviewCallback = new Camera.PreviewCallback() {

        @Override
        public void onPreviewFrame(byte[] data, Camera camera) {
            if (mPushStreamThread == null || !mPushStreamThread.isAlive() || mPushStreamHandler == null) {
                return;
            }
            mPushStreamHandler.post(() -> {
                Camera.Parameters parameters = camera.getParameters();
                Camera.Size size = parameters.getPreviewSize();
                int cameraId = CustomCapture.ins().getCameraId();
                int width = size.width;
                int height = size.height;

                VideoRotation rotation;
                if (cameraId == Camera.CameraInfo.CAMERA_FACING_FRONT) {
                    rotation = VideoRotation.VIDEO_ROTATION_270;
                } else {
                    android.hardware.Camera.CameraInfo info = new android.hardware.Camera.CameraInfo();
                    android.hardware.Camera.getCameraInfo(CustomCapture.ins().getCameraId(), info);
                    rotation = VideoRotation.fromId(info.orientation);
                }

                byte[] yuv = CommonUtil.nv21ToI420(data, width, height);

                ByteBuffer directBuffer = ByteBuffer.allocateDirect(yuv.length);
                int chromaWidth = (width + 1) / 2;
                int chromaHeight = (height + 1) / 2;
                int uvSize = chromaWidth * chromaHeight;
                int uStart = width * height;
                int vStart = uStart + uvSize;

                directBuffer.put(yuv);
                directBuffer.rewind();
                directBuffer.limit(uStart);
                ByteBuffer directBufferY = directBuffer.slice();

                directBuffer.position(uStart);
                directBuffer.limit(uStart + uvSize);
                ByteBuffer directBufferU = directBuffer.slice();

                directBuffer.position(vStart);
                directBuffer.limit(vStart + uvSize);
                ByteBuffer directBufferV = directBuffer.slice();

                CpuBufferVideoFrameBuilder builder = new CpuBufferVideoFrameBuilder(VideoPixelFormat.kVideoPixelFormatI420);
                builder.setWidth(width)
                        .setHeight(height)
                        .setRotation(rotation)
                        .setTimeStampUs(System.currentTimeMillis() * TimeUnit.MILLISECONDS.toNanos(1))
                        .setPlaneData(0, directBufferY)
                        .setPlaneStride(0, width)
                        .setPlaneData(1, directBufferU)
                        .setPlaneStride(1, chromaWidth)
                        .setPlaneData(2, directBufferV)
                        .setPlaneStride(2, chromaWidth);

                if (mInstance != null) {
                    mInstance.pushExternalVideoFrame(builder.build());
                }

                CustomCapture.ins().updateBuffer();
            });
        }
    };

    private void startVideoCapture() {
        if (mIsCapturing) {
            return;
        }
        mIsCapturing = true;
        boolean isCustomCapture = ConfigManger.getInstance().isCustomCapture();
        mInstance.setVideoSourceType(StreamIndex.STREAM_INDEX_MAIN, isCustomCapture ? VIDEO_SOURCE_TYPE_EXTERNAL : VIDEO_SOURCE_TYPE_INTERNAL);
        if (isCustomCapture) {
            mPushStreamThread = new HandlerThread("PushHandlerThread");
            mPushStreamThread.start();
            mPushStreamHandler = new Handler(mPushStreamThread.getLooper());
            mPushStreamHandler.post(() -> CustomCapture.ins().startCapture(this, mPreviewCallback));
        } else {
            mInstance.startVideoCapture();
        }
    }

    private void stopVideoCapture() {
        if (!mIsCapturing) {
            return;
        }
        boolean isCustomCapture = ConfigManger.getInstance().isCustomCapture();
        CommonUtil.printDebugLog("RTCRoomActivity stopVideoCapture isCustomCapture:" + isCustomCapture);
        if (isCustomCapture) {
            if (mPushStreamHandler != null) {
                mPushStreamHandler.removeCallbacksAndMessages(null);
                mPushStreamHandler = null;
            }
            if (mPushStreamThread != null && mPushStreamThread.isAlive()) {
                mPushStreamThread.quit();
            }
            CustomCapture.ins().stopCapture();
        } else {
            if (mInstance != null) {
                mInstance.stopVideoCapture();
            }
        }
        mIsCapturing = false;
    }

    @Override
    public void finish() {
        super.finish();
        stopVideoCapture();
        // 离开房间
        if (mInstance != null) {
            mInstance.leaveRoom();
        }
        // 销毁引擎
        RTCEngine.destroyEngine(mInstance);
        mIRtcEngineEventHandler = null;
        mInstance = null;
        ConfigManger.getInstance().removeObserver(this);
        ConfigManger.getInstance().release();
        VideoEffectController.getInstance().destroy();
    }

    @Override
    public void onConfigChange(VideoConfigEntity config) {
        if (mInstance == null) {
            return;
        }
        VideoEncoderConfig videoEncoderConfig = new VideoEncoderConfig(
                mVideoConfig.getResolution().first,
                mVideoConfig.getResolution().second,
                mVideoConfig.getFrameRate(),
                mVideoConfig.getBitRate(),
                VideoEncoderConfig.ScaleMode.SCALE_MODE_AUTO.getValue());
        mInstance.setVideoEncoderConfig(videoEncoderConfig);
        int index = config.mLocalVideoMirrorType == 2 ? 3 : config.mLocalVideoMirrorType;
        mInstance.setLocalVideoMirrorType(MirrorType.fromId(index));
    }

    private void showMessage(String title, String uid, String message) {
        runOnUiThread(() -> {
            AlertDialog.Builder builder = new AlertDialog.Builder(this);
            builder.setCancelable(true);
            builder.setTitle(title);
            builder.setMessage(uid + ": " + message);
            final AlertDialog dialog = builder.create();
            dialog.show();
            new Handler(Looper.getMainLooper()).postDelayed(() -> {
                if (dialog.isShowing()) {
                    dialog.dismiss();
                }
            }, 2000);
        });
    }
}