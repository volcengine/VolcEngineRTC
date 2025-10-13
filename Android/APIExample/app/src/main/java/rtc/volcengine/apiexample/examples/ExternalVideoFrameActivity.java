package rtc.volcengine.apiexample.examples;

import android.content.res.AssetManager;
import android.os.Bundle;
import android.text.TextUtils;
import android.util.Log;
import android.view.TextureView;
import android.widget.Button;
import android.widget.EditText;
import android.widget.FrameLayout;
import android.widget.Spinner;

import com.ss.bytertc.engine.RTCRoom;
import com.ss.bytertc.engine.RTCRoomConfig;
import com.ss.bytertc.engine.RTCEngine;
import com.ss.bytertc.engine.UserInfo;
import com.ss.bytertc.engine.VideoCanvas;
import com.ss.bytertc.engine.data.EngineConfig;
import com.ss.bytertc.engine.data.StreamInfo;
import com.ss.bytertc.engine.data.VideoBufferType;
import com.ss.bytertc.engine.data.VideoFrameData;
import com.ss.bytertc.engine.data.VideoPixelFormat;
import com.ss.bytertc.engine.data.VideoRotation;
import com.ss.bytertc.engine.data.VideoSourceType;
import com.ss.bytertc.engine.handler.IRTCRoomEventHandler;
import com.ss.bytertc.engine.handler.IRTCEngineEventHandler;
import com.ss.bytertc.engine.type.ChannelProfile;
import com.ss.bytertc.engine.type.RTCRoomStats;

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

@ApiExample(name = "外部视频源", order = 8.1)
public class ExternalVideoFrameActivity extends BaseActivity {

    private static final String TAG = "ExternalVideoFrame";
    private FrameLayout localViewContainer;
    private FrameLayout remoteViewContainer;

    private Button btnJoinRoom, btnStartPush, btnStopPush;
    private EditText roomIdInput;
    private Spinner videoTypeSpinner;
    RTCEngine rtcVideo;
    RTCRoom rtcRoom;

    boolean isJoined;
    private String roomID;

    private byte[] fileData = null;
    private int fileDataOffset = 0;
    private int fileDataBufferSize = 0;
    private ScheduledExecutorService scheduledExecutor = Executors.newSingleThreadScheduledExecutor();
    private boolean isPushTaskRunning = false;
    private String videoPath_420, videoPath_nv12;
    private String videoType = "yuv";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_external_video_frame);

        setTitle(R.string.title_external_video_frame);

        initUI();
        initResource();

        EngineConfig config = new EngineConfig();
        config.context = this;
        config.appID = Constants.APP_ID;
        rtcVideo = RTCEngine.createRTCEngine(config, rtcVideoEventHandler);// 开启音频采集
        rtcVideo.startAudioCapture();

        rtcVideo.setVideoSourceType(VideoSourceType.VIDEO_SOURCE_TYPE_EXTERNAL);
        setLocalRenderView();
    }

    private void initUI() {
        localViewContainer = findViewById(R.id.local_view_container);
        remoteViewContainer = findViewById(R.id.remote_view_container);
        btnJoinRoom = findViewById(R.id.btn_join_room);
        roomIdInput = findViewById(R.id.room_id_input);
        btnStartPush = findViewById(R.id.btn_start_push);
        btnStopPush = findViewById(R.id.btn_stop_push);
        videoTypeSpinner = findViewById(R.id.video_type_spinner);

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
            startPushVideo();
        });

        btnStopPush.setOnClickListener(v -> {
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

    private void setRemoteRenderView( String streamId) {
        TextureView remoteTextureView = new TextureView(this);
        remoteViewContainer.removeAllViews();
        remoteViewContainer.addView(remoteTextureView);
        VideoCanvas videoCanvas = new VideoCanvas();
        videoCanvas.renderView = remoteTextureView;
        videoCanvas.renderMode = VideoCanvas.RENDER_MODE_HIDDEN;
        // 设置远端视频渲染视图
        rtcVideo.setRemoteVideoCanvas(streamId, videoCanvas);
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

    private void startPushVideo() {
        videoType = videoTypeSpinner.getSelectedItem().toString();
        if ("yuv".equals(videoType)) {
            openFile(videoPath_420);
        } else {
            openFile(videoPath_nv12);
        }

        if (!isPushTaskRunning) {
            scheduledExecutor = Executors.newSingleThreadScheduledExecutor();
            scheduledExecutor.scheduleWithFixedDelay(pushVideoFrameTask, 10, 1000 / 25, TimeUnit.MILLISECONDS);
            isPushTaskRunning = true;
        }
    }
    Runnable pushVideoFrameTask = new Runnable() {
        @Override
        public void run() {
            int width = 360;
            int height = 640;
            // 每1帧数据大小
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

            pushBuffer.position(uStart);
            pushBuffer.limit(vStart + uvSize);
            ByteBuffer directBufferUV = pushBuffer.slice();

            VideoFrameData frame = new VideoFrameData();
            frame.bufferType = VideoBufferType.RAW_MEMORY;
            frame.width = 360;
            frame.height = 640;
            frame.rotation = VideoRotation.fromId(0);
            frame.timestampUs = System.currentTimeMillis() * TimeUnit.MILLISECONDS.toNanos(1);
            if ("yuv".equals(videoType)) {
                frame.pixelFormat = VideoPixelFormat.I420;
                frame.numberOfPlanes = 3;
                frame.planeData = new ByteBuffer[3];
                frame.planeStride = new int[3];
                frame.planeData[0] = directBufferY;
                frame.planeStride[0] = width;
                frame.planeData[1] = directBufferU;
                frame.planeStride[1] = chromaWidth;
                frame.planeData[2] = directBufferV;
                frame.planeStride[2] = chromaWidth;
            } else {
                frame.pixelFormat = VideoPixelFormat.NV12;
                frame.numberOfPlanes = 2;
                frame.planeData = new ByteBuffer[2];
                frame.planeData[0] = directBufferY;
                frame.planeData[1] = directBufferUV;
                frame.planeStride = new int[2];
                frame.planeStride[0] = width;
                frame.planeStride[1] = width;
            }
            rtcVideo.pushExternalVideoFrame(frame);
        }
        
    };

    private void stopPushVideo() {
        if (isPushTaskRunning && scheduledExecutor != null) {
            scheduledExecutor.shutdown();
            scheduledExecutor = null;
            isPushTaskRunning = false;
        }
        fileDataOffset = 0;
    }


    IRTCRoomEventHandler rtcRoomEventHandler = new IRTCRoomEventHandler() {
        @Override
        public void onRoomStateChanged(String roomId, String uid, int state, String extraInfo) {
            super.onRoomStateChanged(roomId, uid, state, extraInfo);
            String info = String.format("roomId:%s, uid:%s, state:%d, extraInfo:%s", roomId, uid, state, extraInfo);
            ToastUtil.showShortToast(ExternalVideoFrameActivity.this, info);
        }

        @Override
        public void onLeaveRoom(RTCRoomStats stats) {
            super.onLeaveRoom(stats);
            ToastUtil.showLongToast(ExternalVideoFrameActivity.this, "onLeaveRoom, stats:" + stats.toString());
        }

        @Override
        public void onUserPublishStreamVideo(String streamId, StreamInfo streamInfo, boolean isPublish) {
            if (isPublish) {
                // 设置远端视频渲染视图
                runOnUiThread(() -> setRemoteRenderView(streamInfo.streamId));
            }
        }
    };

    IRTCEngineEventHandler rtcVideoEventHandler = new IRTCEngineEventHandler() {};

    /**
     * 打开文件
     * @param file_path
     * @return
     */
    public int openFile(String file_path) {
        if (fileData != null){
            fileData = null;
        }
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

    private void initResource() {
        copyAssetsFile("i420_360x640.yuv");
        copyAssetsFile("nv12_360x640.nv12");
        videoPath_420 = getExternalFilesDir("").getPath() + "/i420_360x640.yuv";
        videoPath_nv12 = getExternalFilesDir("").getPath() + "/nv12_360x640.nv12";
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
        if (fileData!= null) {
            fileData = null;
        }
        RTCEngine.destroyRTCEngine();
    }
}