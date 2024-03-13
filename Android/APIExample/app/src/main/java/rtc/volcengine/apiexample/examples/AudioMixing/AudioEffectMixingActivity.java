package rtc.volcengine.apiexample.examples.AudioMixing;

import androidx.appcompat.widget.AppCompatButton;

import android.content.res.AssetManager;
import android.os.Bundle;
import android.text.TextUtils;
import android.util.Log;
import android.view.TextureView;
import android.widget.Button;
import android.widget.EditText;
import android.widget.FrameLayout;
import android.widget.SeekBar;
import android.widget.TextView;

import com.ss.bytertc.engine.IAudioEffectPlayerEventHandler;
import com.ss.bytertc.engine.RTCRoom;
import com.ss.bytertc.engine.RTCRoomConfig;
import com.ss.bytertc.engine.RTCVideo;
import com.ss.bytertc.engine.UserInfo;
import com.ss.bytertc.engine.VideoCanvas;
import com.ss.bytertc.engine.audio.IAudioEffectPlayer;
import com.ss.bytertc.engine.data.AudioEffectPlayerConfig;
import com.ss.bytertc.engine.data.AudioMixingType;
import com.ss.bytertc.engine.data.PlayerError;
import com.ss.bytertc.engine.data.PlayerState;
import com.ss.bytertc.engine.data.StreamIndex;
import com.ss.bytertc.engine.handler.IRTCRoomEventHandler;
import com.ss.bytertc.engine.handler.IRTCVideoEventHandler;
import com.ss.bytertc.engine.type.ChannelProfile;
import com.ss.bytertc.engine.type.RTCRoomStats;

import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;

import rtc.volcengine.apiexample.BaseActivity;
import rtc.volcengine.apiexample.R;
import rtc.volcengine.apiexample.Utils.ToastUtil;
import rtc.volcengine.apiexample.common.Constants;
import rtc.volcengine.apiexample.examples.CrossRoomPKActivity;
import rtc.volcengine.apiexample.examples.MultiRoomActivity;
import rtc.volcengine.apiexample.examples.mediaplayer.MediaPlayerActivity;

/**
 * 功能名称： VolcEngineRTC 音效混音
 * 功能简单描述：如果需要在通话过程中播放音效或音乐文件等，而且让房间内的其他成员也听到声音，需要使用混音功能。混音功能可以将麦克风采集的音频数据与音频文件、PCM 音频数据等合并为一路音频流后，发布到房间内
 * 参考文档：https://www.volcengine.com/docs/6348/70141
 *
 * 此功能涉及的API及回调：
 *     createRTCVideo 创建引擎
 *     destroyRTCVideo 销毁引擎
 *     startAudioCapture 开启音频采集
 *     createRTCRoom 创建RTC房间
 *     joinRoom 进入RTC房间
 *     leaveRoom 离开RTC房间
 *     destroy 销毁RTC房间
 *     getAudioEffectPlayer 获取音效播放功能实例
 *
 *     IAudioEffectPlayer API:
 *     setEventHandler 设置回调
 *     preload 预加载音效
 *     start 开始播放音效文件
 *     stop 停止播放音效文件
 *     stopAll 停止播放所有音效文件
 *     pauseAll 暂停播放所有音效文件
 *     resumeAll 恢复播放所有音效文件
 *     getDuration 获取音效文件时长 setPosition 设置播放位置
 *     getVolume 获取播放音量  setVolumeAll 设置所有音效的音量大小  setVolume调节指定音效的音量大小
 *
 *
 *     onRoomStateChanged 房间状态回调
 *     onLeaveRoom 离房回调
 *     onUserJoined 用户加入回调
 *     onUserLeave  用户离开回调
 *     onUserPublishStream 用户发流回调
 *     onUserUnpublishStream 用户停止发流回调
 *
 *     onAudioEffectPlayerStateChanged 播放状态回调
 *

 *
 * Demo实现时的逻辑
 *    本Demo演示功能：音效混音功能，播放本地音效和在线URL音效
 *    为了展示简单，所有功能的token都由客户端生成，请在真正接入时视具体情况而定
 */

public class AudioEffectMixingActivity extends BaseActivity {
    private Button btnJoinRoom;
    private EditText roomIdInput;
    private EditText resInput1;
    private AppCompatButton btnPreload1;
    private AppCompatButton btnUnload1;
    private AppCompatButton btnPlay1;
    private AppCompatButton btnStop1;
    private AppCompatButton btnPause1;
    private AppCompatButton btnResume1;
    private SeekBar volumeBar1;
    private TextView effectVolume1;

    private EditText resInput2;
    private AppCompatButton btnPreload2;
    private AppCompatButton btnUnload2;
    private AppCompatButton btnPlay2;
    private AppCompatButton btnStop2;
    private AppCompatButton btnPause2;
    private AppCompatButton btnResume2;
    private SeekBar volumeBar2;
    private TextView effectVolume2;

    private AppCompatButton btnPauseAll;
    private AppCompatButton btnResumeAll;
    private AppCompatButton btnStopAll;
    private SeekBar volumeAllBar;
    private TextView effectAllVolume;
    private FrameLayout localViewContainer;


    private boolean isJoined;
    private RTCVideo rtcVideo;
    private RTCRoom rtcRoom;
    private IAudioEffectPlayer effectPlayer;

    private static final int EFFECT_ID_1 = 111;
    private static final int EFFECT_ID_2 = 222;

    private String path1;
    private  String path2;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_audio_effect_mixing);
        initUI();
        initEffectResource();

        rtcVideo = RTCVideo.createRTCVideo(this, Constants.APP_ID, rtcVideoEventHandler, null, null);
        // 开启音频采集
        rtcVideo.startAudioCapture();
        rtcVideo.startVideoCapture();
        setLocalRenderView();

        effectPlayer = rtcVideo.getAudioEffectPlayer();
        effectPlayer.setEventHandler(effectPlayerEventHandler);
    }


    private void initUI() {
        localViewContainer = findViewById(R.id.local_view_container);
        btnJoinRoom = findViewById(R.id.btn_join_room);
        roomIdInput = findViewById(R.id.room_id_input);
        resInput1 = findViewById(R.id.res_input1);
        btnPreload1  =findViewById(R.id.btn_preload);
        btnUnload1 = findViewById(R.id.btn_unload);
        btnStop1 = findViewById(R.id.btn_stop);
        btnPlay1 = findViewById(R.id.btn_play);
        btnPause1 = findViewById(R.id.btn_pause);
        btnResume1 = findViewById(R.id.btn_resume);
        volumeBar1 = findViewById(R.id.volume_bar1);
        effectVolume1 = findViewById(R.id.volume_text1);

        resInput2 = findViewById(R.id.res_input2);
        btnPreload2  =findViewById(R.id.btn_preload2);
        btnUnload2 = findViewById(R.id.btn_unload2);
        btnStop2 = findViewById(R.id.btn_stop2);
        btnPlay2 = findViewById(R.id.btn_play2);
        btnPause2 = findViewById(R.id.btn_pause2);
        btnResume2 = findViewById(R.id.btn_resume2);
        volumeBar2 = findViewById(R.id.volume_bar2);
        effectVolume2 = findViewById(R.id.volume_text2);

        btnPauseAll = findViewById(R.id.btn_pauseAll);
        btnResumeAll = findViewById(R.id.btn_resumeAll);
        btnStopAll = findViewById(R.id.btn_stopAll);
        volumeAllBar = findViewById(R.id.volume_all_bar);
        effectAllVolume = findViewById(R.id.volume_all_text);

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

        // preload
        btnPreload1.setOnClickListener(v -> effectPlayer.preload(EFFECT_ID_1, path1));
        // unload
        btnUnload1.setOnClickListener(v -> effectPlayer.unload(EFFECT_ID_1));
        btnPlay1.setOnClickListener(v -> startEffect(EFFECT_ID_1, path1));
        btnStop1.setOnClickListener(v -> effectPlayer.stop(EFFECT_ID_1));
        btnPause1.setOnClickListener(v -> effectPlayer.pause(EFFECT_ID_1));
        btnResume1.setOnClickListener(v -> effectPlayer.resume(EFFECT_ID_1));
        volumeBar1.setOnSeekBarChangeListener(volumeBarChangeListener);

        // preload
        btnPreload2.setOnClickListener(v -> {
            path2 = resInput2.getText().toString();
            if (TextUtils.isEmpty(path2)) {
                ToastUtil.showShortToast(this, "url is null");
                return;
            }
            effectPlayer.preload(EFFECT_ID_2, path2);
        });
        // unload
        btnUnload2.setOnClickListener(v -> effectPlayer.unload(EFFECT_ID_2));
        btnPlay2.setOnClickListener(v -> {
            path2 = resInput2.getText().toString();
            if (TextUtils.isEmpty(path2)) {
                ToastUtil.showShortToast(this, "url is null");
                return;
            }
            startEffect(EFFECT_ID_2, path2);
        });
        btnStop2.setOnClickListener(v -> effectPlayer.stop(EFFECT_ID_2));
        btnPause2.setOnClickListener(v -> effectPlayer.pause(EFFECT_ID_2));
        btnResume2.setOnClickListener(v -> effectPlayer.resume(EFFECT_ID_2));
        volumeBar2.setOnSeekBarChangeListener(volumeBarChangeListener);

        btnStopAll.setOnClickListener(v -> effectPlayer.stopAll());
        btnResumeAll.setOnClickListener(v -> effectPlayer.resumeAll());
        btnPauseAll.setOnClickListener(v -> effectPlayer.pauseAll());
        volumeAllBar.setOnSeekBarChangeListener(volumeBarChangeListener);

    }

    SeekBar.OnSeekBarChangeListener volumeBarChangeListener = new SeekBar.OnSeekBarChangeListener() {
        @Override
        public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
            if (seekBar == volumeBar1) {
                effectPlayer.setVolume(EFFECT_ID_1, progress);
                effectVolume1.setText("" + progress);
            } else if (seekBar == volumeBar2) {
                effectPlayer.setVolume(EFFECT_ID_2, progress);
                effectVolume2.setText("" + progress);
            } else if (seekBar == volumeAllBar) {
                effectPlayer.setVolumeAll(progress);
                effectAllVolume.setText("" + progress);
            }
        }

        @Override
        public void onStartTrackingTouch(SeekBar seekBar) {
        }

        @Override
        public void onStopTrackingTouch(SeekBar seekBar) {
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

    private void startEffect(int effectId, String path) {
        AudioEffectPlayerConfig playerConfig = new AudioEffectPlayerConfig();
        playerConfig.type = AudioMixingType.AUDIO_MIXING_TYPE_PLAYOUT_AND_PUBLISH;
        playerConfig.startPos = 0;
        playerConfig.playCount = 1;
        playerConfig.pitch = 0;
        effectPlayer.start(effectId, path, playerConfig);
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

    IAudioEffectPlayerEventHandler effectPlayerEventHandler = new IAudioEffectPlayerEventHandler() {
        @Override
        public void onAudioEffectPlayerStateChanged(int effectId, PlayerState state, PlayerError error) {
            String msg = String.format("onAudioEffectPlayerStateChanged, effectId:%d, state:%s, error:%s", effectId, state.toString(), error.toString());
            ToastUtil.showShortToast(AudioEffectMixingActivity.this, msg);
        }
    };

    IRTCVideoEventHandler rtcVideoEventHandler = new IRTCVideoEventHandler() {
    };

    IRTCRoomEventHandler rtcRoomEventHandler = new IRTCRoomEventHandler() {
        @Override
        public void onRoomStateChanged(String roomId, String uid, int state, String extraInfo) {
            super.onRoomStateChanged(roomId, uid, state, extraInfo);
            String info = String.format("onRoomStateChanged,roomId:%s, uid:%s, state:%d, extraInfo:%s", roomId, uid, state, extraInfo);
            ToastUtil.showShortToast(AudioEffectMixingActivity.this, info);
        }

        @Override
        public void onLeaveRoom(RTCRoomStats stats) {
            super.onLeaveRoom(stats);
            ToastUtil.showLongToast(AudioEffectMixingActivity.this, "onLeaveRoom, stats:" + stats.toString());
        }

        @Override
        public void onUserJoined(UserInfo userInfo, int elapsed) {
            super.onUserJoined(userInfo, elapsed);
            ToastUtil.showShortToast(AudioEffectMixingActivity.this, "onUserJoined, uid:" + userInfo.getUid());
        }

        @Override
        public void onUserLeave(String uid, int reason) {
            super.onUserLeave(uid, reason);
            String info = String.format("onUserLeave, uid:%s, reason:%s", uid, reason + "");
            ToastUtil.showLongToast(AudioEffectMixingActivity.this, info);
        }
    };

    private void initEffectResource() {
        copyAssetsFile("effect_1.mp3");
        // 本地文件路径
        path1 = getExternalFilesDir("").getPath() + "/effect_1.mp3";
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