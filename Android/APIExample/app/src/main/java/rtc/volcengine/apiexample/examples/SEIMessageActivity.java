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
import com.ss.bytertc.engine.data.EngineConfig;
import com.ss.bytertc.engine.data.SEICountPerFrame;
import com.ss.bytertc.engine.data.StreamInfo;
import com.ss.bytertc.engine.data.VideoBufferType;
import com.ss.bytertc.engine.data.VideoFrameData;
import com.ss.bytertc.engine.data.VideoPixelFormat;
import com.ss.bytertc.engine.data.VideoRotation;
import com.ss.bytertc.engine.data.VideoSourceType;
import com.ss.bytertc.engine.handler.IRTCRoomEventHandler;
import com.ss.bytertc.engine.handler.IRTCEngineEventHandler;
import com.ss.bytertc.engine.live.MixedStreamConfig;
import com.ss.bytertc.engine.live.MixedStreamLayoutRegionConfig;
import com.ss.bytertc.engine.live.MixedStreamMediaType;
import com.ss.bytertc.engine.live.MixedStreamPushTargetConfig;
import com.ss.bytertc.engine.live.MixedStreamPushTargetType;
import com.ss.bytertc.engine.live.MixedStreamRenderMode;
import com.ss.bytertc.engine.live.MixedStreamTaskErrorCode;
import com.ss.bytertc.engine.live.MixedStreamTaskEvent;
import com.ss.bytertc.engine.live.MixedStreamTaskInfo;
import com.ss.bytertc.engine.live.MixedStreamVideoType;
import com.ss.bytertc.engine.type.ChannelProfile;
import com.ss.bytertc.engine.type.RTCRoomStats;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.nio.ByteBuffer;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;

import rtc.volcengine.apiexample.BaseActivity;
import rtc.volcengine.apiexample.R;
import rtc.volcengine.apiexample.Utils.MD5Utils;
import rtc.volcengine.apiexample.Utils.ToastUtil;
import rtc.volcengine.apiexample.common.Constants;
import rtc.volcengine.apiexample.common.annotations.ApiExample;

@ApiExample(order = 10, name = "SEI消息", category = "消息管理")
public class SEIMessageActivity extends BaseActivity {

    private static final String TAG = "SEIMessageActivity";

    private RTCEngine rtcVideo;
    private RTCRoom rtcRoom;
    private boolean isJoined;

    private Button btnJoinRoom, btnSendSEIMsg, startPushStream, stopPushStream, btnSendLayoutMsg;
    private Button btnStartPushFrame, btnStopPushFrame;
    private EditText roomIdInput, seiMsgInput, pushUrlInput, layoutMsgInput, videoFrameMsgInput;
    private FrameLayout localViewContainer;
    private MixedStreamConfig mixedStreamConfig;
    private MixedStreamPushTargetConfig targetConfig;
    private String roomID;
    private static final String CDN_TASK_ID = "111";
    private String videoPath_420;

    private byte[] fileData = null;
    private int fileDataOffset = 0;
    private int fileDataBufferSize = 0;
    private ScheduledExecutorService scheduledExecutor = Executors.newSingleThreadScheduledExecutor();
    private boolean isPushTaskRunning = false;
    private String videoType = "yuv";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_seimessage);
        setTitle(R.string.title_sei_msg);

        initUI();
        initResource();
        openFile(videoPath_420);

        EngineConfig config = new EngineConfig();
        config.context = this;
        config.appID = Constants.APP_ID;
        rtcVideo = RTCEngine.createRTCEngine(config, rtcVideoEventHandler);
        // 开启音视频采集
        rtcVideo.startAudioCapture();
        rtcVideo.startVideoCapture();

        mixedStreamConfig = MixedStreamConfig.defaultMixedStreamConfig();
        targetConfig = new MixedStreamPushTargetConfig();

        setLocalRenderView();
    }

    private void initUI() {
        localViewContainer = findViewById(R.id.local_view_container);
        btnJoinRoom = findViewById(R.id.btn_join_room);
        roomIdInput = findViewById(R.id.room_id_input);
        btnSendSEIMsg = findViewById(R.id.btn_send_sei_msg);
        seiMsgInput = findViewById(R.id.sei_msg_input);
        pushUrlInput = findViewById(R.id.push_url_input);
        startPushStream = findViewById(R.id.btn_start_push);
        stopPushStream = findViewById(R.id.btn_stop_push);
        layoutMsgInput = findViewById(R.id.layout_msg_input);
        btnSendLayoutMsg = findViewById(R.id.btn_send_layout_msg);
        btnStartPushFrame = findViewById(R.id.btn_start_push_frame);
        btnStopPushFrame = findViewById(R.id.btn_stop_push_frame);
        videoFrameMsgInput = findViewById(R.id.video_frame_msg_input);

        pushUrlInput.setText(getRTMPAddr("111", CDN_TASK_ID));

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

        btnSendSEIMsg.setOnClickListener(v -> {
            String msg = seiMsgInput.getText().toString();
            if (TextUtils.isEmpty(msg)) {
                ToastUtil.showAlert(this, "sei消息为空");
            }

            rtcVideo.sendSEIMessage(msg.getBytes(StandardCharsets.UTF_8), 3, SEICountPerFrame.SEI_COUNT_PER_FRAME_SINGLE);
        });

        startPushStream.setOnClickListener(v -> {
            startPushMixedStreamToCDN();
        });

        stopPushStream.setOnClickListener(v -> stopPushCDNStream());
        btnSendLayoutMsg.setOnClickListener(v -> updateCDNStreamConfig());

        btnStartPushFrame.setOnClickListener(v -> {
            startPushVideo();
        });

        btnStopPushFrame.setOnClickListener( v -> {
            stopPushVideo();
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

    private String videoFrameMsg;
    private void startPushVideo() {
        videoFrameMsg = videoFrameMsgInput.getText().toString();
        if (TextUtils.isEmpty(videoFrameMsg)) {
            ToastUtil.showShortToast(this, "sei消息为空");
            return;
        }
        rtcVideo.stopVideoCapture();
        rtcVideo.setVideoSourceType( VideoSourceType.VIDEO_SOURCE_TYPE_EXTERNAL);

        if (!isPushTaskRunning) {
            scheduledExecutor = Executors.newSingleThreadScheduledExecutor();
            scheduledExecutor.scheduleAtFixedRate(pushVideoFrameTask, 10, 1000 / 25, TimeUnit.MILLISECONDS);
            isPushTaskRunning = true;
        }
    }
    Runnable pushVideoFrameTask = new Runnable() {
        @Override
        public void run() {
            int width = 360;
            int height = 640;
            // 每10ms的数据大小
            int bufferSize = width * height * 3 / 2;

            int chromaWidth = (width+1) / 2;
            int chromaHeight = (height+1) / 2;
            int uvSize = chromaWidth * chromaHeight;
            int uStart = width * height;
            int vStart = uStart + uvSize;

            ByteBuffer pushBuffer = ByteBuffer.allocateDirect(bufferSize);

            int nRead = 0;
            if (fileData != null) {
                nRead = Integer.min(bufferSize, fileDataBufferSize - fileDataOffset);
                pushBuffer.put(fileData, fileDataOffset, nRead);
                fileDataOffset += nRead;
            }
            Log.i(TAG, "offset:" + fileDataOffset + " read:" + nRead);
            if (nRead == 0) {
                fileDataOffset = 0;
                return;
            }

            pushBuffer.rewind();
            pushBuffer.limit(uStart);
            ByteBuffer directBufferY = pushBuffer.slice();

            pushBuffer.position(uStart);
            pushBuffer.limit(uStart + uvSize);
            ByteBuffer directBufferU = pushBuffer.slice();

            pushBuffer.position(vStart);
            pushBuffer.limit(vStart + uvSize);
            ByteBuffer directBufferV = pushBuffer.slice();

            VideoFrameData frame = new VideoFrameData();

            if ("yuv".equals(videoType)) {
                frame.pixelFormat = VideoPixelFormat.I420;
            } else {
                frame.pixelFormat = VideoPixelFormat.NV12;
            }
            frame.bufferType = VideoBufferType.RAW_MEMORY;
            frame.numberOfPlanes = 3;
            frame.width = 360;
            frame.height = 640;
            frame.rotation = VideoRotation.fromId(0);
            frame.timestampUs = System.currentTimeMillis() * TimeUnit.MILLISECONDS.toMicros(1);
            frame.planeData = new ByteBuffer[3];
            frame.planeStride = new int[3];
            frame.planeData[0] = directBufferY;
            frame.planeStride[0] = width;
            frame.planeData[1] = directBufferU;
            frame.planeStride[1] = chromaWidth;
            frame.planeData[2] = directBufferV;
            frame.planeStride[2] = chromaWidth;
            frame.seiData = ByteBuffer.wrap(videoFrameMsg.getBytes(StandardCharsets.UTF_8));

            rtcVideo.pushExternalVideoFrame(frame);
        }
    };

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

    private void stopPushVideo() {
        if (isPushTaskRunning && scheduledExecutor != null) {
            scheduledExecutor.shutdown();
            scheduledExecutor = null;
            isPushTaskRunning = false;
        }
        fileDataOffset = 0;
        rtcVideo.startVideoCapture();
        rtcVideo.setVideoSourceType( VideoSourceType.VIDEO_SOURCE_TYPE_INTERNAL);
    }

    IRTCEngineEventHandler rtcVideoEventHandler = new IRTCEngineEventHandler() {
        @Override
        public void onSEIMessageReceived(String streamId, StreamInfo streamInfo, ByteBuffer message) {
            Charset charset = Charset.defaultCharset();
            String dataString = charset.decode(message).toString();
            ToastUtil.showLongToast(SEIMessageActivity.this, "onSEIMessageReceived：" + dataString);
        }

        @Override
        public void onMixedStreamEvent(MixedStreamTaskInfo info, MixedStreamTaskEvent event, MixedStreamTaskErrorCode error) {
            super.onMixedStreamEvent(info, event, error);
            String msg = String.format("onMixingEvent,taskId:%s, error:%s, event:%s", info.getTaskId(), error.toString(), event.toString());
            Log.d(TAG, msg);
            ToastUtil.showLongToast(SEIMessageActivity.this, msg);
        }
    };

    IRTCRoomEventHandler rtcRoomEventHandler = new IRTCRoomEventHandler() {
        @Override
        public void onRoomStateChanged(String roomId, String uid, int state, String extraInfo) {
            super.onRoomStateChanged(roomId, uid, state, extraInfo);
            String info = String.format("roomId:%s, uid:%s, state:%d, extraInfo:%s", roomId, uid, state, extraInfo);
            ToastUtil.showShortToast(SEIMessageActivity.this, info);
        }

        @Override
        public void onLeaveRoom(RTCRoomStats stats) {
            super.onLeaveRoom(stats);
            ToastUtil.showLongToast(SEIMessageActivity.this, "onLeaveRoom, stats:" + stats.toString());
        }
    };

    /**
     * {zh}
     * 开启合流转推
     */
    private void startPushMixedStreamToCDN() {
        String cdnAddr = pushUrlInput.getText().toString();
        if (cdnAddr.isEmpty()) {
            ToastUtil.showAlert(this, "cdn address is null");
            return;
        }
        Log.i(TAG, "startPushMixedStreamToCDN, cdnAddr:" + cdnAddr);
        String msg = layoutMsgInput.getText().toString();

        mixedStreamConfig.userID = localUid;
        mixedStreamConfig.roomID = roomID;

        mixedStreamConfig.regions = getLayoutRegions();
        mixedStreamConfig.backgroundColor = "#000000";
        if (!TextUtils.isEmpty(msg)) {
            mixedStreamConfig.userConfigExtraInfo = msg;
        }
        targetConfig.pushCDNURL = cdnAddr;
        targetConfig.pushTargetType = MixedStreamPushTargetType.PUSH_TO_CDN;
        rtcVideo.startPushMixedStream(CDN_TASK_ID, targetConfig, mixedStreamConfig);
    }

    private MixedStreamLayoutRegionConfig[] getLayoutRegions() {
        int width = 360;
        int height = 640;
        int userNum = 1;
        MixedStreamLayoutRegionConfig[] regions = new MixedStreamLayoutRegionConfig[userNum];
        int index = 0;
        MixedStreamLayoutRegionConfig region = new MixedStreamLayoutRegionConfig();
        region.roomID = roomID;
        region.userID = localUid;
        region.locationX = (index * width / userNum);
        // 留出部分背景区域
        region.locationY = (50);
        region.width = (width / userNum);
        region.height = (height);
        region.alpha = (1);
        region.zOrder = (0);
        region.renderMode = (MixedStreamRenderMode.MIXED_STREAM_RENDER_MODE_HIDDEN);
        region.streamType = (MixedStreamVideoType.MIXED_STREAM_VIDEO_TYPE_MAIN);
        region.mediaType = (MixedStreamMediaType.MIXED_STREAM_MEDIA_TYPE_AUDIO_AND_VIDEO);
        regions[index] = region;
        return regions;
    }

    private void updateCDNStreamConfig() {
        String cdnAddr = pushUrlInput.getText().toString();
        if (cdnAddr.isEmpty()) {
            ToastUtil.showAlert(this, "cdn address is null");
            return;
        }
        String msg = layoutMsgInput.getText().toString();
        if (msg.isEmpty()) {
            ToastUtil.showAlert(this, "sei消息为空");
            return;
        }

        if (!TextUtils.isEmpty(msg)) {
            mixedStreamConfig.userConfigExtraInfo = msg;
        }
        targetConfig.pushCDNURL = cdnAddr;
        targetConfig.pushTargetType = MixedStreamPushTargetType.PUSH_TO_CDN;
        rtcVideo.updatePushMixedStream(CDN_TASK_ID, targetConfig, mixedStreamConfig);
    }

    private void initResource() {
        copyAssetsFile("i420_360x640.yuv");
        videoPath_420 = getExternalFilesDir("").getPath() + "/i420_360x640.yuv";
    }

    private void copyAssetsFile(String fileName) {
        final File file = new File(getExternalFilesDir(""), fileName);
        if (file.exists()) {
            Log.i(TAG, "File exists.");
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
     * 停止CDN推流
     */
    private void stopPushCDNStream() {
        rtcVideo.stopPushMixedStream(CDN_TASK_ID, MixedStreamPushTargetType.PUSH_TO_CDN);
    }


    public static String getRTMPAddr(String roomID, String taskID) {
        long timeStamp = System.currentTimeMillis();
        long expire = timeStamp + 7200;
        String path = "/rtc_test/" + taskID;
        String authKey = "Uq8e962ghCCY2pBUB9Me2Fwy";
        String keyStr = path + authKey + expire;
        String sign = MD5Utils.md5Hash(keyStr);

        String addr = "rtmp://fcdn-test-hl.uplive.ixigua.com/rtc_test/" + taskID + "?sign=" + sign + "&expire=" + expire;
        Log.i(TAG, "rtmp addr: " + addr);
        return addr;
    }

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
        if (fileData != null){
            fileData = null;
        }
        System.gc();
        RTCEngine.destroyRTCEngine();
    }
}