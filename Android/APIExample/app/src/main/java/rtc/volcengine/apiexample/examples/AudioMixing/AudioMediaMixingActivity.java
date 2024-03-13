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

import com.ss.bytertc.engine.IMediaPlayerEventHandler;
import com.ss.bytertc.engine.RTCRoom;
import com.ss.bytertc.engine.RTCRoomConfig;
import com.ss.bytertc.engine.RTCVideo;
import com.ss.bytertc.engine.UserInfo;
import com.ss.bytertc.engine.VideoCanvas;
import com.ss.bytertc.engine.audio.IMediaPlayer;
import com.ss.bytertc.engine.data.AudioChannel;
import com.ss.bytertc.engine.data.AudioMixingType;
import com.ss.bytertc.engine.data.AudioSampleRate;
import com.ss.bytertc.engine.data.MediaPlayerConfig;
import com.ss.bytertc.engine.data.MediaPlayerCustomSource;
import com.ss.bytertc.engine.data.MediaPlayerCustomSourceMode;
import com.ss.bytertc.engine.data.MediaPlayerCustomSourceStreamType;
import com.ss.bytertc.engine.data.PlayerError;
import com.ss.bytertc.engine.data.PlayerState;
import com.ss.bytertc.engine.data.StreamIndex;
import com.ss.bytertc.engine.handler.IRTCRoomEventHandler;
import com.ss.bytertc.engine.handler.IRTCVideoEventHandler;
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
import rtc.volcengine.apiexample.examples.mediaplayer.MediaPlayerActivity;

/**
 * 功能名称： VolcEngineRTC 音乐混音
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
 *     getMediaPlayer 获取音乐播放功能实例
 *
 *     IMediaPlayer API:
 *     setEventHandler 设置回调句柄
 *     open 打开音乐文件
 *     getTotalDuration  获取音乐文件时长
 *     getAudioTrackCount  获取当前音乐文件的音轨数
 *     getVolume  setVolume 获取/设置播放音量
 *     pause  resume stop 暂停 恢复 停止
 *     setAudioPitch 变调
 *     setPosition getPosition 设置/获取播放位置
 *     setAudioDualMonoMode selectAudioTrack 设置声道模式
 *     pushExternalAudioFrame 推送PCM数据
 *     openWithCustomSource 打开PCM文件
 *
 *
 *
 *     onRoomStateChanged 房间状态回调
 *     onLeaveRoom 离房回调
 *     onUserJoined 用户加入回调
 *     onUserLeave  用户离开回调
 *     onUserPublishStream 用户发流回调
 *     onUserUnpublishStream 用户停止发流回调
 *
 *     onMediaPlayerStateChanged 播放状态改变时回调
 *     onMediaPlayerPlayingProgress 播放进度实时回调
 *
 *
 *
 *
 * Demo实现时的逻辑
 *    本Demo演示功能：音乐混音功能，仅展示播放音乐和播放PCM；
 *    为了展示简单，所有功能的token都由客户端生成，请在真正接入时视具体情况而定
 */

public class AudioMediaMixingActivity extends BaseActivity {

    private static final String TAG = "MediaMixingActivity";

    private Button btnJoinRoom;
    private EditText roomIdInput;
    private AppCompatButton btnOpen1;
    private AppCompatButton btnPlay1;
    private AppCompatButton btnStop1;
    private AppCompatButton btnPause1;
    private AppCompatButton btnResume1;
    private AppCompatButton btnSetAudioTrack;
    private AppCompatButton btnSetProgress;
    private EditText audioTraceInput;
    private EditText progressInput;

    private AppCompatButton btnPlay2;
    private AppCompatButton btnStop2;
    private AppCompatButton btnPause2;
    private AppCompatButton btnResume2;


    private EditText resInput1;
    private SeekBar volumeBar1;
    private TextView effectVolume1;
    private SeekBar progressBar1;
    private TextView progressText1;
    private FrameLayout localViewContainer;

    private boolean isJoined;
    private RTCVideo rtcVideo;
    private RTCRoom rtcRoom;
    private IMediaPlayer mediaPlayer;
    private IMediaPlayer pcmPlayer;

    private static final int PLAYER_ID_1 = 0;
    private static final int PLAYER_ID_PCM = 1;

    private String path1;
    private String pcmPath;

    private byte[] fileData = null;
    private int fileDataOffset = 0;
    private int fileDataBufferSize = 0;
    private ByteBuffer mByteBuffer;

    private ScheduledExecutorService scheduledExecutor = Executors.newSingleThreadScheduledExecutor();
    private boolean isFirstPush = true;
    private boolean isPushTaskRunning = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_audio_media_mixing);
        initUI();
        initMediaResource();

        rtcVideo = RTCVideo.createRTCVideo(this, Constants.APP_ID, rtcVideoEventHandler, null, null);
        // 开启音视频采集
        rtcVideo.startAudioCapture();
        rtcVideo.startVideoCapture();
        setLocalRenderView();
        // ID范围[0, 3]，最多创建4个播放器实例
        pcmPlayer = rtcVideo.getMediaPlayer(PLAYER_ID_PCM);
        mediaPlayer = rtcVideo.getMediaPlayer(PLAYER_ID_1);

        mediaPlayer.setEventHandler(playerEventHandler);
        pcmPlayer.setEventHandler(playerEventHandler);
    }

    private void initUI() {
        localViewContainer = findViewById(R.id.local_view_container);
        btnJoinRoom = findViewById(R.id.btn_join_room);
        roomIdInput = findViewById(R.id.room_id_input);
        btnStop1 = findViewById(R.id.btn_stop);
        btnPlay1 = findViewById(R.id.btn_play);
        btnPause1 = findViewById(R.id.btn_pause);
        btnResume1 = findViewById(R.id.btn_resume);
        resInput1 = findViewById(R.id.res_input1);
        volumeBar1 = findViewById(R.id.volume_bar1);
        effectVolume1 = findViewById(R.id.volume_text1);
        progressBar1 = findViewById(R.id.progress_bar1);
        progressText1 = findViewById(R.id.progress_text1);
        btnOpen1 = findViewById(R.id.btn_open);
        btnSetAudioTrack = findViewById(R.id.btn_set_audio_track);
        btnSetProgress = findViewById(R.id.btn_set_progress);
        progressInput = findViewById(R.id.progress_input);
        audioTraceInput = findViewById(R.id.audio_track_input);

        btnStop2 = findViewById(R.id.btn_stop2);
        btnPlay2 = findViewById(R.id.btn_play2);
        btnPause2 = findViewById(R.id.btn_pause2);
        btnResume2 = findViewById(R.id.btn_resume2);

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

        btnOpen1.setOnClickListener(v -> openMedia(path1));
        btnPlay1.setOnClickListener(v -> mediaPlayer.start());
        btnStop1.setOnClickListener(v -> mediaPlayer.stop());
        btnPause1.setOnClickListener(v -> mediaPlayer.pause());
        btnResume1.setOnClickListener(v -> mediaPlayer.resume());
        volumeBar1.setOnSeekBarChangeListener(seekBarChangeListener);
        btnSetProgress.setOnClickListener(v -> {
            String progress = progressInput.getText().toString();
            if (TextUtils.isEmpty(progress)) {
                ToastUtil.showAlert(this, "输入为空");
                return;
            }
            mediaPlayer.setPosition(Integer.parseInt(progress));
        });
        btnSetAudioTrack.setOnClickListener(v -> {
            String audioTrack = audioTraceInput.getText().toString();
            if (TextUtils.isEmpty(audioTrack)) {
                ToastUtil.showAlert(this, "输入为空");
                return;
            }
            mediaPlayer.selectAudioTrack(Integer.parseInt(audioTrack));
        });

        btnPlay2.setOnClickListener(v -> startPlayPCM());
        btnStop2.setOnClickListener(v -> stopPlayPCM());
        btnPause2.setOnClickListener(v -> stopPushPCM());
        btnResume2.setOnClickListener(v -> startPushPCM());

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


    private void openMedia(String filePath) {
        MediaPlayerConfig playerConfig = new MediaPlayerConfig();
        playerConfig.startPos = 0;
        playerConfig.autoPlay = false;
        playerConfig.playCount = 1;
        playerConfig.type = AudioMixingType.AUDIO_MIXING_TYPE_PLAYOUT_AND_PUBLISH;
        playerConfig.callbackOnProgressInterval = 500;
        mediaPlayer.open(filePath, playerConfig);
    }

    private void startPlayPCM() {
        openFile(pcmPath);

        MediaPlayerCustomSource source = new MediaPlayerCustomSource();
        source.mode = MediaPlayerCustomSourceMode.PUSH;
        source.type = MediaPlayerCustomSourceStreamType.RAW;
        source.provider = null;

        MediaPlayerConfig playerConfig = new MediaPlayerConfig();
        playerConfig.startPos = 0;
        playerConfig.autoPlay = true;
        playerConfig.playCount = 1;
        playerConfig.type = AudioMixingType.AUDIO_MIXING_TYPE_PLAYOUT_AND_PUBLISH;
        playerConfig.callbackOnProgressInterval = 500;

        pcmPlayer.openWithCustomSource(source, playerConfig);
        startPushPCM();
    }

    private void stopPlayPCM() {
        stopPushPCM();
        pcmPlayer.stop();
        fileDataOffset = 0;
        isFirstPush = true;
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
                stopPlayPCM();
                return;
            }
            audioFrame.buffer = pushBuffer.array();
            pcmPlayer.pushExternalAudioFrame(audioFrame);
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
        copyAssetsFile("qilixiang.m4a");
        copyAssetsFile("16k-mono.pcm");
        path1 = getExternalFilesDir("").getPath() + "/qilixiang.m4a";
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

    SeekBar.OnSeekBarChangeListener seekBarChangeListener = new SeekBar.OnSeekBarChangeListener() {
        @Override
        public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
            if (seekBar == volumeBar1) {
                mediaPlayer.setVolume(progress, AudioMixingType.AUDIO_MIXING_TYPE_PLAYOUT_AND_PUBLISH);
                pcmPlayer.setVolume(progress, AudioMixingType.AUDIO_MIXING_TYPE_PLAYOUT_AND_PUBLISH);
                effectVolume1.setText("" + progress);
            } else if (seekBar == progressBar1) {
                mediaPlayer.setPosition(progress);
                progressText1.setText("" + progress);
            }
        }

        @Override
        public void onStartTrackingTouch(SeekBar seekBar) {
        }

        @Override
        public void onStopTrackingTouch(SeekBar seekBar) {
        }
    };

    IMediaPlayerEventHandler playerEventHandler = new IMediaPlayerEventHandler() {
        @Override
        public void onMediaPlayerStateChanged(int playerId, PlayerState state, PlayerError error) {
            String msg = String.format("onMediaPlayerStateChanged, playerId:%d, state:%s, error:%s", playerId, state.toString(), error.toString());
            ToastUtil.showShortToast(AudioMediaMixingActivity.this, msg);
            runOnUiThread(() -> {
                if (state.equals(PlayerState.PLAYING) && playerId == PLAYER_ID_1) {
                    progressBar1.setMax(mediaPlayer.getTotalDuration());
                }
            });
        }

        @Override
        public void onMediaPlayerPlayingProgress(int playerId, long progress) {
            Log.d(TAG, "onMediaPlayerPlayingProgress, playerId:" + playerId + " progress:" + progress);
            runOnUiThread(() -> {
                if (playerId == PLAYER_ID_1) {
                    progressBar1.setProgress((int) progress);
                    progressText1.setText("" + progress);
                }
            });
        }
    };

    IRTCVideoEventHandler rtcVideoEventHandler = new IRTCVideoEventHandler() {
    };

    IRTCRoomEventHandler rtcRoomEventHandler = new IRTCRoomEventHandler() {
        @Override
        public void onRoomStateChanged(String roomId, String uid, int state, String extraInfo) {
            super.onRoomStateChanged(roomId, uid, state, extraInfo);
            String info = String.format("onRoomStateChanged,roomId:%s, uid:%s, state:%d, extraInfo:%s", roomId, uid, state, extraInfo);
            ToastUtil.showLongToast(AudioMediaMixingActivity.this, info);
        }

        @Override
        public void onLeaveRoom(RTCRoomStats stats) {
            super.onLeaveRoom(stats);
            ToastUtil.showLongToast(AudioMediaMixingActivity.this, "onLeaveRoom, stats:" + stats.toString());
        }

        @Override
        public void onUserJoined(UserInfo userInfo, int elapsed) {
            super.onUserJoined(userInfo, elapsed);
            ToastUtil.showShortToast(AudioMediaMixingActivity.this, "onUserJoined, uid:" + userInfo.getUid());
        }

        @Override
        public void onUserLeave(String uid, int reason) {
            super.onUserLeave(uid, reason);
            String info = String.format("onUserLeave, uid:%s, reason:%s", uid, reason + "");
            ToastUtil.showLongToast(AudioMediaMixingActivity.this, info);
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