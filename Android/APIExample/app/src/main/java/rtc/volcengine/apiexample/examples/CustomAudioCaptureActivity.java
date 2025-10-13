package rtc.volcengine.apiexample.examples;

import android.content.res.AssetManager;
import android.os.Bundle;
import android.text.TextUtils;
import android.util.Log;
import android.view.TextureView;
import android.widget.Button;
import android.widget.EditText;
import android.widget.FrameLayout;

import com.ss.bytertc.engine.RTCRoom;
import com.ss.bytertc.engine.RTCRoomConfig;
import com.ss.bytertc.engine.RTCEngine;
import com.ss.bytertc.engine.UserInfo;
import com.ss.bytertc.engine.VideoCanvas;
import com.ss.bytertc.engine.data.AudioChannel;
import com.ss.bytertc.engine.data.AudioSampleRate;
import com.ss.bytertc.engine.data.AudioSourceType;
import com.ss.bytertc.engine.data.EngineConfig;
import com.ss.bytertc.engine.handler.IRTCRoomEventHandler;
import com.ss.bytertc.engine.handler.IRTCEngineEventHandler;
import com.ss.bytertc.engine.type.ChannelProfile;
import com.ss.bytertc.engine.type.RTCRoomStats;
import com.ss.bytertc.engine.utils.AudioFrame;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.nio.ByteBuffer;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;

import rtc.volcengine.apiexample.BaseActivity;
import rtc.volcengine.apiexample.R;
import rtc.volcengine.apiexample.Utils.ToastUtil;
import rtc.volcengine.apiexample.common.Constants;
import rtc.volcengine.apiexample.common.annotations.ApiExample;

@ApiExample(order = 4.1, name = "自定义音频采集")
public class CustomAudioCaptureActivity extends BaseActivity {

    private static final String TAG = "CustomAudioCaptureActivity";
    private FrameLayout localViewContainer;
    private Button btnJoinRoom, btnStartPush, btnStopPush;
    private EditText roomIdInput;
    private boolean isJoined;

    private RTCEngine rtcVideo;
    private RTCRoom rtcRoom;
    private byte[] fileData = null;
    private int fileDataOffset = 0;
    private int fileDataBufferSize = 0;
    private ByteBuffer mByteBuffer;

    private ScheduledExecutorService scheduledExecutor = Executors.newSingleThreadScheduledExecutor();
    private boolean isFirstPush = true;
    private boolean isPushTaskRunning = false;
    private String pcmPath;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_custom_audio_capture);

        initUI();
        initMediaResource();
        initUI();
        openFile(pcmPath);

        EngineConfig config = new EngineConfig();
        config.context = this;
        config.appID = Constants.APP_ID;
        rtcVideo = RTCEngine.createRTCEngine(config, rtcVideoEventHandler);
        // 开启视频采集
        rtcVideo.startVideoCapture();
        setLocalRenderView();
        rtcVideo.setAudioSourceType(AudioSourceType.AUDIO_SOURCE_TYPE_EXTERNAL);
    }

    private void initUI() {
        localViewContainer = findViewById(R.id.local_view_container);
        btnJoinRoom = findViewById(R.id.btn_join_room);
        roomIdInput = findViewById(R.id.room_id_input);
        btnStartPush = findViewById(R.id.btn_start_push);
        btnStopPush = findViewById(R.id.btn_stop_push);

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

        btnStartPush.setOnClickListener(v -> {
            startPushPCM();
        });

        btnStopPush.setOnClickListener(v -> {
            stopPushPCM();
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

    private void stopPushPCM() {
        if (isPushTaskRunning && scheduledExecutor != null) {
            scheduledExecutor.shutdown();
            scheduledExecutor = null;
            isPushTaskRunning = false;
        }
    }

    private void startPushPCM() {
        if (!isPushTaskRunning) {
            scheduledExecutor = Executors.newSingleThreadScheduledExecutor();
            scheduledExecutor.scheduleAtFixedRate(pushAudioFrameTask, 10, 10, TimeUnit.MILLISECONDS);
            isPushTaskRunning = true;
        }
    }
    Runnable pushAudioFrameTask = new Runnable() {
        @Override
        public void run() {
            // 每10ms的数据大小
            int size = 16 * 10;
            if (isFirstPush) {
                // 建议第一次时传入200ms的缓冲数据，避免噪音
                size = size * 20;
                isFirstPush = false;
            }
            ByteBuffer pushBuffer = ByteBuffer.allocate(size * 2);
            AudioFrame audioFrame = new AudioFrame();
            audioFrame.channel = AudioChannel.AUDIO_CHANNEL_MONO;
            audioFrame.sampleRate = AudioSampleRate.AUDIO_SAMPLE_RATE_16000;
            audioFrame.samples = size;

            int nRead = 0;
            if (fileData != null) {
                nRead = Integer.min(size * 2, fileDataBufferSize - fileDataOffset);
                pushBuffer.put(fileData, fileDataOffset, nRead);
                fileDataOffset += nRead;
            }
            Log.i(TAG, "offset:" + fileDataOffset + " read:" + nRead);
            if (nRead == 0) {
                fileDataOffset = 0;
            }
            audioFrame.buffer = pushBuffer.array();
            rtcVideo.pushExternalAudioFrame(audioFrame);
        }
    };

    /**
     * 打开文件
     * @param file_path
     * @return
     */
    public int openFile(String file_path) {
        FileInputStream fis = null;
        try {
            File file = new File(file_path);
            if (!file.exists() || !file.isFile()) {
                return -1;
            }
            fileDataBufferSize = (int) file.length();
            if (fileDataBufferSize <= 0) {
                return -2;
            }
            fileData = new byte[fileDataBufferSize];
            fis = new FileInputStream(file_path);
            fis.read(fileData, 0, fileDataBufferSize);
            mByteBuffer = ByteBuffer.wrap(fileData);
            fis.close();
            Log.i(TAG, "init success mFileSize=" + fileDataBufferSize + ", this =" + this);
            return 0;
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            if (fis != null) {
                try {
                    fis.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
        return -1;
    }

    private void initMediaResource() {
        copyAssetsFile("16k-mono.pcm");
        pcmPath = getExternalFilesDir("").getPath() + "/16k-mono.pcm";
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
    };

    IRTCRoomEventHandler rtcRoomEventHandler = new IRTCRoomEventHandler() {
        @Override
        public void onRoomStateChanged(String roomId, String uid, int state, String extraInfo) {
            super.onRoomStateChanged(roomId, uid, state, extraInfo);
            String info = String.format("onRoomStateChanged,roomId:%s, uid:%s, state:%d, extraInfo:%s", roomId, uid, state, extraInfo);
            ToastUtil.showLongToast(CustomAudioCaptureActivity.this, info);
        }

        @Override
        public void onLeaveRoom(RTCRoomStats stats) {
            super.onLeaveRoom(stats);
            ToastUtil.showLongToast(CustomAudioCaptureActivity.this, "onLeaveRoom, stats:" + stats.toString());
        }

        @Override
        public void onUserJoined(UserInfo userInfo) {
            super.onUserJoined(userInfo);
            ToastUtil.showShortToast(CustomAudioCaptureActivity.this, "onUserJoined, uid:" + userInfo.getUid());
        }

        @Override
        public void onUserLeave(String uid, int reason) {
            super.onUserLeave(uid, reason);
            String info = String.format("onUserLeave, uid:%s, reason:%s", uid, reason + "");
            ToastUtil.showLongToast(CustomAudioCaptureActivity.this, info);
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