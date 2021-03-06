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
 * VolcEngineRTC ????????????????????????
 * ??????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????
 * <p>
 * ???????????????????????????
 * - ????????????
 * - ????????????????????????
 * - ???????????????????????????
 * - ???????????????????????????
 * - ????????????/???????????????
 * - ??????/???????????????
 * - ??????/???????????????
 * - ????????????/?????????
 * - ?????????????????????????????????
 * - ????????????
 * - ????????????
 * <p>
 * ??????????????????????????????????????????????????????
 * 1.???????????? {@link RTCEngine#create(Context, String, IRTCEngineEventHandler)}
 * 2.?????????????????? {@link RTCEngine#setVideoEncoderConfig(List)}
 * 3.???????????????????????? {@link RTCEngine#startVideoCapture()}
 * 4.?????????????????????????????? {@link RTCEngine#setLocalVideoCanvas(StreamIndex, VideoCanvas)}
 * 5.??????????????????????????? {@link RTCEngine#joinRoom(java.lang.String, java.lang.String,
 *   com.ss.bytertc.engine.UserInfo, com.ss.bytertc.engine.RTCRoomConfig)}
 * 6.??????????????????????????????????????????????????????????????????????????? {@link RTCEngine#setRemoteVideoCanvas(String, StreamIndex, VideoCanvas)}
 * 7.???????????????????????????????????????????????????????????? {@link RTCRoomActivity#removeRemoteView(String)}
 * 8.??????????????????????????? {@link RTCEngine#leaveRoom()}
 * 9.???????????? {@link RTCEngine#destroyEngine(RTCEngine)}
 * <p>
 * ?????????????????????????????????
 * 1.?????????????????????????????? RTC ????????????????????????????????? IRTCEngineEventHandler ???????????????????????????????????????????????????
 * ???????????? Activity ??????????????????????????????????????????????????????????????????????????????????????????????????????????????????
 * 2.???????????????????????? {@link IRTCEngineEventHandler#onFirstRemoteVideoFrameDecoded} ??????????????????????????????
 * ???????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????
 * {@link IRTCEngineEventHandler#onUserJoined} ?????????????????????????????????????????????
 * 3.SDK ????????????????????????UI ????????????????????????
 * 4.??????????????????????????????SDK ????????? {@link IRTCEngineEventHandler#onUserJoined} ????????????????????????????????????
 * 5.SDK ?????????????????????????????????????????????????????? {@link RTCEngine#setVideoEncoderConfig}
 * 6.???????????????????????????????????? token??????????????????????????? {@link IRTCEngineEventHandler#onError(int)} ????????????????????????
 * 7.?????????????????? {@link RTCEngine#joinRoom(java.lang.String, java.lang.String,
 *   com.ss.bytertc.engine.UserInfo, com.ss.bytertc.engine.RTCRoomConfig)} ?????? ChannelProfile
 *   ?????????????????????????????????????????????????????????????????????????????????????????? {@link ChannelProfile#CHANNEL_PROFILE_COMMUNICATION}
 * 8.????????????????????????/??????????????????????????????????????????????????????????????????????????????????????????????????????
 * <p>
 * ?????????API????????????{https://www.volcengine.com/docs/6348/70080}
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
         * ????????????????????????????????????????????????????????????????????????
         */
        @Override
        public void onFirstRemoteVideoFrameDecoded(RemoteStreamKey remoteStreamKey, VideoFrameInfo frameInfo) {
            super.onFirstRemoteVideoFrameDecoded(remoteStreamKey, frameInfo);
            Log.d("IRtcEngineEventHandler", "onFirstRemoteVideoFrame: " + remoteStreamKey.toString());
            runOnUiThread(() -> setRemoteView(remoteStreamKey));
        }

        /**
         * ?????????????????????????????????????????????
         */
        @Override
        public void onUserJoined(UserInfo userInfo, int elapsed) {
            super.onUserJoined(userInfo, elapsed);
            Log.d("IRtcEngineEventHandler", "onUserJoined: " + userInfo.getUid());
        }

        /**
         * ?????????????????????????????????
         */
        @Override
        public void onUserLeave(String uid, int reason) {
            super.onUserLeave(uid, reason);
            Log.d("IRtcEngineEventHandler", "onUserOffline: " + uid);
            runOnUiThread(() -> removeRemoteView(uid));
        }

        /**
         * ?????????????????????????????? {https://www.volcengine.com/docs/6348/70082#warncode}
         */
        @Override
        public void onWarning(int warn) {
            super.onWarning(warn);
            Log.d("IRtcEngineEventHandler", "onWarning: " + warn);
        }

        /**
         * ?????????????????????????????? {https://www.volcengine.com/docs/6348/70082#errorcode}
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
            showMessage("?????????????????????", uid, message);
        }

        @Override
        public void onUserBinaryMessageReceived(String uid, ByteBuffer message) {
            super.onUserBinaryMessageReceived(uid, message);
            showMessage("?????????????????????", uid, byteBufferToString(message));
        }

        @Override
        public void onRoomMessageReceived(String uid, String message) {
            super.onRoomMessageReceived(uid, message);
            showMessage("??????????????????", uid, message);
        }

        @Override
        public void onRoomBinaryMessageReceived(String uid, ByteBuffer message) {
            super.onRoomBinaryMessageReceived(uid, message);
            showMessage("??????????????????", uid, byteBufferToString(message));
        }

        @Override
        public void onUserMessageSendResult(long msgid, int error) {
            super.onUserMessageSendResult(msgid, error);
            String tip;
            if (error != 0) {
                tip = String.format(Locale.US, "???????????????????????????(%d)", error);
            } else {
                tip = "???????????????????????????";
            }
            runOnUiThread(() -> SafeToast.show(RTCRoomActivity.this, tip, Toast.LENGTH_SHORT));
        }

        @Override
        public void onSEIMessageReceived(RemoteStreamKey remoteStreamKey, ByteBuffer message) {
            super.onSEIMessageReceived(remoteStreamKey, message);
            runOnUiThread(() -> showMessage("??????SEI??????", remoteStreamKey.getUserId(), byteBufferToString(message)));
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
        // ????????????
        mInstance = RTCEngine.create(getApplicationContext(), Constants.APPID, mIRtcEngineEventHandler);
        // ????????????????????????
        VideoEncoderConfig videoEncoderConfig = new VideoEncoderConfig(
                mVideoConfig.getResolution().first,
                mVideoConfig.getResolution().second,
                mVideoConfig.getFrameRate(),
                mVideoConfig.getBitRate(),
                VideoEncoderConfig.ScaleMode.SCALE_MODE_AUTO.getValue());
        mInstance.setVideoEncoderConfig(videoEncoderConfig);
        setLocalRenderView(userId);
        // ????????????????????????
        startVideoCapture();
        // ????????????????????????
        mInstance.startAudioCapture();
        // ????????????
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
            // ??????????????????????????????
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
            // ????????????????????????????????????
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
        // ????????????/????????????????????????????????????????????????
        if (mCameraID.equals(CameraId.CAMERA_ID_FRONT)) {
            mCameraID = CameraId.CAMERA_ID_BACK;
        } else {
            mCameraID = CameraId.CAMERA_ID_FRONT;
        }
        mInstance.switchCamera(mCameraID);
    }

    private void updateSpeakerStatus() {
        mIsSpeakerPhone = !mIsSpeakerPhone;
        // ??????????????????????????????????????????
        mInstance.setAudioRoute(mIsSpeakerPhone ? AudioRoute.AUDIO_ROUTE_SPEAKERPHONE
                : AudioRoute.AUDIO_ROUTE_EARPIECE);
        mSpeakerIv.setImageResource(mIsSpeakerPhone ? R.drawable.speaker_on : R.drawable.speaker_off);
    }

    private void updateLocalAudioStatus() {
        mIsMuteAudio = !mIsMuteAudio;
        // ??????/????????????????????????
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
            // ??????????????????
            stopVideoCapture();
        } else {
            // ??????????????????
            startVideoCapture();
        }
        mVideoIv.setImageResource(mIsMuteVideo ? R.drawable.mute_video : R.drawable.normal_video);
    }

    private void showAlertDialog(String message) {
        runOnUiThread(() -> {
            AlertDialog.Builder builder = new AlertDialog.Builder(this);
            builder.setMessage(message);
            builder.setPositiveButton("?????????", (dialog, which) -> dialog.dismiss());
            builder.create().show();
        });
    }

    /* ????????????:????????????????????????????????????????????? */

    /* ???????????????????????? */
    private HandlerThread mPushStreamThread;
    /* ??????????????????????????????Handler */
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
        // ????????????
        if (mInstance != null) {
            mInstance.leaveRoom();
        }
        // ????????????
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