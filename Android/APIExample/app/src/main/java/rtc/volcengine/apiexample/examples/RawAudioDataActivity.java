package rtc.volcengine.apiexample.examples;

import android.os.Bundle;
import android.text.TextUtils;
import android.util.Log;
import android.view.TextureView;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.FrameLayout;
import android.widget.Switch;

import com.ss.bytertc.engine.IAudioFrameObserver;
import com.ss.bytertc.engine.RTCRoom;
import com.ss.bytertc.engine.RTCRoomConfig;
import com.ss.bytertc.engine.RTCVideo;
import com.ss.bytertc.engine.UserInfo;
import com.ss.bytertc.engine.VideoCanvas;
import com.ss.bytertc.engine.data.AudioChannel;
import com.ss.bytertc.engine.data.AudioFormat;
import com.ss.bytertc.engine.data.AudioFrameCallbackMethod;
import com.ss.bytertc.engine.data.AudioSampleRate;
import com.ss.bytertc.engine.data.RemoteStreamKey;
import com.ss.bytertc.engine.data.StreamIndex;
import com.ss.bytertc.engine.handler.IRTCRoomEventHandler;
import com.ss.bytertc.engine.handler.IRTCVideoEventHandler;
import com.ss.bytertc.engine.type.ChannelProfile;
import com.ss.bytertc.engine.type.RTCRoomStats;
import com.ss.bytertc.engine.utils.IAudioFrame;
import com.ss.bytertc.engine.utils.LogUtil;

import rtc.volcengine.apiexample.BaseActivity;
import rtc.volcengine.apiexample.R;
import rtc.volcengine.apiexample.Utils.ToastUtil;
import rtc.volcengine.apiexample.common.Constants;
import rtc.volcengine.apiexample.common.annotations.ApiExample;
import rtc.volcengine.apiexample.examples.mediaplayer.MediaPlayerActivity;

/**
 * 功能名称： VolcEngineRTC 原始音频数据
 * 功能简单描述：通过注册回调接口，获取原始的指定类型的音频数据
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
 *     registerAudioFrameObserver  注册音频数据回调观察者
 *     enableAudioFrameCallback  设置并开启指定的音频数据帧回调
 *
 *     onRoomStateChanged 房间状态回调
 *     onLeaveRoom 离房回调
 *     onUserJoined 用户加入回调
 *     onUserLeave  用户离开回调
 *     onUserPublishStream 用户发流回调
 *     onUserUnpublishStream 用户停止发流回调
 *
 *     onRecordAudioFrame 返回麦克风录制的音频数据
 *     onPlaybackAudioFrame 返回订阅的所有远端用户混音后的音频数据
 *     onRemoteUserAudioFrame 返回远端单个用户的音频数据
 *     onMixedAudioFrame  返回本地麦克风录制和订阅的所有远端用户混音后的音频数据
 *     onRecordScreenAudioFrame  返回本地屏幕录制的音频数据
 *
 * Demo实现时的逻辑
 *    本Demo演示功能：获取原始音频数据的代码实现流程
 *    IAudioFrameObserver 回调的数据无法修改后发送到远端
 *    如果想在发送音频前进行处理且处理效果发送到远端，请使用 自定义音频处理 接口，参考文档：https://www.volcengine.com/docs/6348/80635
 *    为了展示简单，所有功能的token都由客户端生成，请在真正接入时视具体情况而定
 */

@ApiExample(order = 3, name = "原始音频数据", category = "音频管理")
public class RawAudioDataActivity extends BaseActivity {

    private static final String  TAG = "RawAudioDataActivity";

    private FrameLayout localViewContainer;
    private Button btnJoinRoom;
    private EditText roomIdInput;
    private Switch audioFrameCallbackSwitch;

    RTCVideo rtcVideo;
    RTCRoom rtcRoom;

    boolean isJoined;
    boolean isShowRecordDataLog;
    boolean isShowMixDataLog;
    boolean isShowPlaybackDataLog;
    boolean isShowRemoteUserDataLog;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_raw_audio);
        setTitle(R.string.title_raw_audio_data);
        initUI();

        rtcVideo = RTCVideo.createRTCVideo(this, Constants.APP_ID, rtcVideoEventHandler, null, null);
        setLocalRenderView();
        // 开启音视频采集
        rtcVideo.startVideoCapture();
        rtcVideo.startAudioCapture();

        // 注册音频数据回调
        rtcVideo.registerAudioFrameObserver(audioFrameObserver);
    }

    private void initUI() {
        localViewContainer = findViewById(R.id.local_view_container);
        btnJoinRoom = findViewById(R.id.btn_join_room);
        roomIdInput = findViewById(R.id.room_id_input);
        audioFrameCallbackSwitch = findViewById(R.id.audio_callback_switch);

        btnJoinRoom.setOnClickListener(v -> {
            String roomId = roomIdInput.getText().toString();
            if (isJoined) {
                leaveRoom();

                isJoined = false;
                audioFrameCallbackSwitch.setEnabled(false);
                audioFrameCallbackSwitch.setChecked(false);
                btnJoinRoom.setText("进入房间");
                return;
            }
            if (TextUtils.isEmpty(roomId)) {
                ToastUtil.showAlert(this, "roomID is null");
                return;
            }
            joinRoom(roomId);
            isJoined = true;
            audioFrameCallbackSwitch.setEnabled(true);
            btnJoinRoom.setText("退出房间");
        });

        audioFrameCallbackSwitch.setOnCheckedChangeListener((buttonView, isChecked) -> {
            enableAudioFrameCallback(isChecked);
        });
    }

    private void enableAudioFrameCallback(boolean enable) {
        if (enable) {
            // 'AUDIO_FRAME_CALLBACK_RECORD(0)`、`AUDIO_FRAME_CALLBACK_PLAYBACK(1)`、`AUDIO_FRAME_CALLBACK_MIXED(2)，
            // 需要在参数 `format` 中指定准确的采样率和声道，暂不支持设置为自动
            AudioFormat format = new AudioFormat(AudioSampleRate.AUDIO_SAMPLE_RATE_48000, AudioChannel.AUDIO_CHANNEL_MONO);
            // 开启本地麦克风录制的音频数据回调
            rtcVideo.enableAudioFrameCallback(AudioFrameCallbackMethod.AUDIO_FRAME_CALLBACK_RECORD, format);
            // 开启本地麦克风录制和订阅的远端所有用户混音后的音频数据回调
            rtcVideo.enableAudioFrameCallback(AudioFrameCallbackMethod.AUDIO_FRAME_CALLBACK_MIXED, format);
            // 开启订阅的远端所有用户混音后的音频数据回调
            rtcVideo.enableAudioFrameCallback(AudioFrameCallbackMethod.AUDIO_FRAME_CALLBACK_PLAYBACK, format);

            // `AUDIO_FRAME_CALLBACK_REMOTE_USER(3)`，暂不支持音频参数格式中设置准确的采样率和声道，你需要设置为自动
            AudioFormat audioFormat = new AudioFormat(AudioSampleRate.AUDIO_SAMPLE_RATE_AUTO, AudioChannel.AUDIO_CHANNEL_AUTO);
            // 开启订阅的远端每个用户混音前的音频数据回调
            rtcVideo.enableAudioFrameCallback(AudioFrameCallbackMethod.AUDIO_FRAME_CALLBACK_REMOTE_USER, audioFormat);
        } else {
            rtcVideo.disableAudioFrameCallback(AudioFrameCallbackMethod.AUDIO_FRAME_CALLBACK_RECORD);
            rtcVideo.disableAudioFrameCallback(AudioFrameCallbackMethod.AUDIO_FRAME_CALLBACK_MIXED);
            rtcVideo.disableAudioFrameCallback(AudioFrameCallbackMethod.AUDIO_FRAME_CALLBACK_PLAYBACK);
            rtcVideo.disableAudioFrameCallback(AudioFrameCallbackMethod.AUDIO_FRAME_CALLBACK_REMOTE_USER);
        }

        isShowPlaybackDataLog = false;
        isShowMixDataLog = false;
        isShowRecordDataLog = false;
        isShowRemoteUserDataLog = false;
    }

    private IAudioFrameObserver audioFrameObserver = new IAudioFrameObserver() {
        @Override
        public void onRecordAudioFrame(IAudioFrame audioFrame) {
            Log.i(TAG, "onRecordAudioFrame:");
            if (!isShowRecordDataLog) {
                ToastUtil.showShortToast(RawAudioDataActivity.this, "onRecordAudioFrame");
                isShowRecordDataLog = true;
            }
        }

        @Override
        public void onPlaybackAudioFrame(IAudioFrame audioFrame) {
            Log.i(TAG, "onPlaybackAudioFrame:");
            if (!isShowPlaybackDataLog) {
                ToastUtil.showShortToast(RawAudioDataActivity.this, "onPlaybackAudioFrame");
                isShowPlaybackDataLog = true;
            }
        }

        @Override
        public void onRemoteUserAudioFrame(RemoteStreamKey streamKey, IAudioFrame audioFrame) {
            Log.i(TAG, "onRemoteUserAudioFrame:");
            if (!isShowRemoteUserDataLog) {
                ToastUtil.showShortToast(RawAudioDataActivity.this, "onRemoteUserAudioFrame");
                isShowRemoteUserDataLog = true;
            }
        }

        @Override
        public void onMixedAudioFrame(IAudioFrame audioFrame) {
            Log.i(TAG, "onMixedAudioFrame:");
            if (!isShowMixDataLog) {
                ToastUtil.showShortToast(RawAudioDataActivity.this, "onMixedAudioFrame");
                isShowMixDataLog = true;
            }
        }
    };

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

    IRTCVideoEventHandler rtcVideoEventHandler = new IRTCVideoEventHandler() {
    };

    IRTCRoomEventHandler rtcRoomEventHandler = new IRTCRoomEventHandler() {
        @Override
        public void onRoomStateChanged(String roomId, String uid, int state, String extraInfo) {
            super.onRoomStateChanged(roomId, uid, state, extraInfo);
            String info = String.format("roomId:%s, uid:%s, state:%d, extraInfo:%s", roomId, uid, state, extraInfo);
            ToastUtil.showLongToast(RawAudioDataActivity.this, info);
        }

        @Override
        public void onLeaveRoom(RTCRoomStats stats) {
            super.onLeaveRoom(stats);
            ToastUtil.showLongToast(RawAudioDataActivity.this, "onLeaveRoom, stats:" + stats.toString());
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
    }
}