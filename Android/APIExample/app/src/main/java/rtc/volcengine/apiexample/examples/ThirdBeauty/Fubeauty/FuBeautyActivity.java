package rtc.volcengine.apiexample.examples.ThirdBeauty.Fubeauty;

import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.view.TextureView;
import android.widget.FrameLayout;

import com.faceunity.core.enumeration.FUAIProcessorEnum;
import com.faceunity.nama.FURenderer;
import com.faceunity.nama.data.FaceUnityDataFactory;
import com.faceunity.nama.listener.FURendererListener;
import com.faceunity.nama.ui.FaceUnityView;
import com.ss.bytertc.engine.RTCRoom;
import com.ss.bytertc.engine.RTCRoomConfig;
import com.ss.bytertc.engine.RTCVideo;
import com.ss.bytertc.engine.UserInfo;
import com.ss.bytertc.engine.VideoCanvas;
import com.ss.bytertc.engine.data.RemoteStreamKey;
import com.ss.bytertc.engine.data.StreamIndex;
import com.ss.bytertc.engine.data.VideoPixelFormat;
import com.ss.bytertc.engine.handler.IRTCRoomEventHandler;
import com.ss.bytertc.engine.handler.IRTCVideoEventHandler;
import com.ss.bytertc.engine.type.ChannelProfile;
import com.ss.bytertc.engine.type.MediaStreamType;
import com.ss.bytertc.engine.type.RTCRoomStats;
import com.ss.bytertc.engine.type.StreamRemoveReason;
import com.ss.bytertc.engine.video.VideoPreprocessorConfig;

import java.util.HashMap;

import rtc.volcengine.apiexample.BaseActivity;
import rtc.volcengine.apiexample.R;
import rtc.volcengine.apiexample.Utils.ToastUtil;
import rtc.volcengine.apiexample.common.Constants;
/**
 * 功能名称： VolcEngineRTC 相芯美颜
 * 功能简单描述：音视频通话中经常会对本地视频进行美化处理，该Demo展示如何集成相芯SDK，展示美颜功能
 * 参考文档：https://www.volcengine.com/docs/6348/79888
 *
 * 此功能涉及的RTC API及回调：
 *     createRTCVideo 创建引擎
 *     destroyRTCVideo 销毁引擎
 *     startAudioCapture 开启音频采集
 *     startVideoCapture 开启视频采集
 *     createRTCRoom 创建RTC房间
 *     joinRoom 进入RTC房间
 *     leaveRoom 离开RTC房间
 *     destroy 销毁RTC房间
 *     registerLocalVideoProcessor 设置自定义视频前处理器，通过ByteRTCVideoProcessorDelegate收到视频帧回调
 *
 *     onRoomStateChanged 房间状态回调
 *     onLeaveRoom 离房回调
 *     onUserJoined 用户加入回调
 *     onUserLeave  用户离开回调
 *     onUserPublishStream 用户发流回调
 *     onUserUnpublishStream 用户停止发流回调
 *
 *    processVideoFrame 支持修改视频帧并发送到远端
 *

 *
 * Demo实现时的逻辑
 *    本Demo演示功能：ByteRTC 集成相芯SDK，展示美颜功能
 *    registerLocalVideoProcessor 注册本地视频帧回调，processVideoFrame接口修改视频帧并进行美颜处理
 *    processVideoFrame 中收到的视频帧来自不同线程，而相芯SDK不支持跨线程的初始化和调用，因此新增线程统一处理视频数据
 *    CNAMASDK_H 宏用来区分是否已经集成过相芯SDK，集成后则展示功能界面；未集成时展示集成步骤
 *    使用相芯SDK功能，需先申请账号
 *    为了展示简单，所有功能的token都由客户端生成，请在真正接入时视具体情况而定
 */
public class FuBeautyActivity extends BaseActivity {
    private static final String TAG = "FuBeautyActivity";
    private static final String roomID = "beauty_room";
    private FrameLayout localViewContainer;

    private FrameLayout[] remoteContainers = new FrameLayout[3];
    private HashMap<String, Integer> remoteUserViewMap = new HashMap<>();
    private boolean[] isRemoteViewUsed = new boolean[3];
    private FURenderer fuRenderer = FURenderer.getInstance();
    private FaceUnityDataFactory faceUnityDataFactory;
    private RTCVideo rtcVideo;
    private RTCRoom rtcRoom;
    private SensorManager mSensorManager;

    private VideoProcessor customVideoProcessor;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_fu_beauty);
        setTitle(R.string.title_fu_beauty);
        FURenderer.getInstance().setup(getApplicationContext());
        FURenderer.getInstance().setMarkFPSEnable(true);

        initUI();
        mSensorManager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);
        Sensor sensor = mSensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
        mSensorManager.registerListener(sensorEventListener, sensor, SensorManager.SENSOR_DELAY_NORMAL);

        // 创建引擎
        rtcVideo = RTCVideo.createRTCVideo(this, Constants.APP_ID, videoEventHandler, null, null);
        // 设置本端渲染视图
        setLocalRenderView();
        setVideoProcessor();
        // 开启音视频采集
        rtcVideo.startVideoCapture();
        rtcVideo.startAudioCapture();
        joinRoom(roomID);

    }

    private void initUI() {
        localViewContainer = findViewById(R.id.local_view_container);
        remoteContainers[0] = findViewById(R.id.remote_view_container1);
        remoteContainers[1] = findViewById(R.id.remote_view_container2);
        remoteContainers[2] = findViewById(R.id.remote_view_container3);

        FaceUnityView faceUnityView = findViewById(R.id.faceUnityView);
        faceUnityDataFactory = new FaceUnityDataFactory(-1);
        faceUnityView.bindDataFactory(faceUnityDataFactory);
        fuRenderer.bindListener(new FURendererListener() {
            @Override
            public void onPrepare() {
                faceUnityDataFactory.bindCurrentRenderer();
            }

            @Override
            public void onTrackStatusChanged(FUAIProcessorEnum type, int status) {
                runOnUiThread(() -> {
                    ToastUtil.showShortToast(FuBeautyActivity.this, type == FUAIProcessorEnum.FACE_PROCESSOR ? "未检测到人脸" : "未检测到人体");
                });
            }

            @Override
            public void onFpsChanged(double fps, double callTime) {

            }

        });
    }



    private void setVideoProcessor(){
        VideoPreprocessorConfig config = new VideoPreprocessorConfig();
        config.requiredPixelFormat = VideoPixelFormat.TEXTURE_2D;
        if(customVideoProcessor == null) {
            customVideoProcessor = new VideoProcessor();
            customVideoProcessor.setRenderEnable(true);
        }
        rtcVideo.registerLocalVideoProcessor(customVideoProcessor, config);
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

    private void setRemoteRenderView(String uid) {
        for (int i = 0; i < isRemoteViewUsed.length; i++) {
            if (!isRemoteViewUsed[i]) {
                isRemoteViewUsed[i] = true;
                remoteUserViewMap.put(uid, i);

                TextureView textureView = new TextureView(this);
                remoteContainers[i].removeAllViews();
                remoteContainers[i].addView(textureView);

                RemoteStreamKey remoteStreamKey = new RemoteStreamKey(roomID, uid, StreamIndex.STREAM_INDEX_MAIN);
                VideoCanvas videoCanvas = new VideoCanvas();
                videoCanvas.renderView = textureView;
                videoCanvas.renderMode = VideoCanvas.RENDER_MODE_HIDDEN;
                rtcVideo.setRemoteVideoCanvas(remoteStreamKey, videoCanvas);
                break;
            }
        }
    }

    private void removeRemoteView(String uid) {
        int index = remoteUserViewMap.get(uid);
        if (index >= 0 && index < 3) {
            remoteContainers[index].removeAllViews();
            isRemoteViewUsed[index] = false;
        }
        remoteUserViewMap.remove(uid);

        RemoteStreamKey remoteStreamKey = new RemoteStreamKey(roomID, uid, StreamIndex.STREAM_INDEX_MAIN);
        VideoCanvas videoCanvas = new VideoCanvas();
        videoCanvas.renderView = null;
        videoCanvas.renderMode = VideoCanvas.RENDER_MODE_HIDDEN;
        rtcVideo.setRemoteVideoCanvas(remoteStreamKey, videoCanvas);

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
     * 离开房间
     */
    private void leaveRoom() {
        if (rtcRoom != null) {
            rtcRoom.leaveRoom();
            rtcRoom.destroy();
            rtcRoom = null;
        }
    }

    IRTCRoomEventHandler rtcRoomEventHandler = new IRTCRoomEventHandler() {
        @Override
        public void onRoomStateChanged(String roomId, String uid, int state, String extraInfo) {
            super.onRoomStateChanged(roomId, uid, state, extraInfo);
            String info = String.format("roomId:%s, uid:%s, state:%d, extraInfo:%s", roomId, uid, state, extraInfo);
            ToastUtil.showLongToast(FuBeautyActivity.this, info);
        }

        @Override
        public void onUserPublishStream(String uid, MediaStreamType type) {
            super.onUserPublishStream(uid, type);
            setRemoteRenderView(uid);
        }

        @Override
        public void onUserUnpublishStream(String uid, MediaStreamType type, StreamRemoveReason reason) {
            super.onUserUnpublishStream(uid, type, reason);
            removeRemoteView(uid);
        }

        @Override
        public void onLeaveRoom(RTCRoomStats stats) {
            super.onLeaveRoom(stats);
            ToastUtil.showLongToast(FuBeautyActivity.this, "onLeaveRoom, stats:" + stats.toString());
        }

        @Override
        public void onUserJoined(UserInfo userInfo, int elapsed) {
            super.onUserJoined(userInfo, elapsed);
            ToastUtil.showLongToast(FuBeautyActivity.this, "onUserJoined, uid:" + userInfo.getUid());
        }

        @Override
        public void onTokenWillExpire() {
            super.onTokenWillExpire();
            ToastUtil.showLongToast(FuBeautyActivity.this, "onTokenWillExpire");
        }
    };

    /**
     * 引擎回调信息
     */
    IRTCVideoEventHandler videoEventHandler = new IRTCVideoEventHandler() {
    };

    SensorEventListener sensorEventListener = new SensorEventListener() {
        @Override
        public void onSensorChanged(SensorEvent event) {
            if (event.sensor.getType() == Sensor.TYPE_ACCELEROMETER) {
                float x = event.values[0];
                float y = event.values[1];
                float z = event.values[2];
                if (Math.abs(x) > 3 || Math.abs(y) > 3) {
                    if (Math.abs(x) > Math.abs(y)) {
                        fuRenderer.setDeviceOrientation(x > 0 ? 0 : 180);
                    } else {
                        fuRenderer.setDeviceOrientation(y > 0 ? 90 : 270);
                    }
                }
            }
        }

        @Override
        public void onAccuracyChanged(Sensor sensor, int accuracy) {

        }
    };

    @Override
    protected void onDestroy() {
        super.onDestroy();
        leaveRoom();
        if(customVideoProcessor != null) {
            customVideoProcessor.mFURenderer.removeListener();
        }
        mSensorManager.unregisterListener(sensorEventListener);
        if (rtcRoom != null) {
            rtcRoom.destroy();
            rtcRoom = null;
        }
        if (rtcVideo != null) {
            rtcVideo.stopAudioCapture();
            rtcVideo.stopVideoCapture();
        }
        RTCVideo.destroyRTCVideo();
    }
}