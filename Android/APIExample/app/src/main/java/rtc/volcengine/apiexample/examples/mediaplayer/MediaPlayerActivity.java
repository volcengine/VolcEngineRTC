package rtc.volcengine.apiexample.examples.mediaplayer;

import androidx.appcompat.widget.AppCompatButton;

import android.os.Bundle;
import android.text.TextUtils;
import android.util.Log;
import android.view.SurfaceView;
import android.view.TextureView;
import android.widget.EditText;
import android.widget.FrameLayout;
import android.widget.SeekBar;
import android.widget.TextView;

import com.bytedance.vcloud.cacheModule.utils.CmLog;
import com.pandora.common.env.Env;
import com.pandora.common.env.config.Config;
import com.pandora.common.env.config.VodConfig;
import com.pandora.ttlicense2.LicenseManager;
import com.ss.bytertc.engine.RTCRoom;
import com.ss.bytertc.engine.RTCRoomConfig;
import com.ss.bytertc.engine.RTCVideo;
import com.ss.bytertc.engine.UserInfo;
import com.ss.bytertc.engine.VideoCanvas;
import com.ss.bytertc.engine.data.AudioMixingType;
import com.ss.bytertc.engine.data.AudioSourceType;
import com.ss.bytertc.engine.data.RemoteStreamKey;
import com.ss.bytertc.engine.data.StreamIndex;
import com.ss.bytertc.engine.handler.IRTCRoomEventHandler;
import com.ss.bytertc.engine.handler.IRTCVideoEventHandler;
import com.ss.bytertc.engine.type.ChannelProfile;
import com.ss.bytertc.engine.type.MediaStreamType;
import com.ss.bytertc.engine.type.RTCRoomStats;
import com.ss.bytertc.engine.type.StreamRemoveReason;
import com.ss.mediakit.medialoader.AVMDLLog;
import com.ss.ttm.player.TTPlayer;
import com.ss.ttvideoengine.SeekCompletionListener;
import com.ss.ttvideoengine.TTVideoEngine;
import com.ss.ttvideoengine.VideoEngineCallback;
import com.ss.ttvideoengine.source.DirectUrlSource;
import com.ss.ttvideoengine.strategy.source.StrategySource;
import com.ss.ttvideoengine.utils.Error;
import com.ss.ttvideoengine.utils.TTVideoEngineLog;

import java.io.File;
import java.util.Random;

import rtc.volcengine.apiexample.BaseActivity;
import rtc.volcengine.apiexample.BuildConfig;
import rtc.volcengine.apiexample.R;
import rtc.volcengine.apiexample.Utils.ToastUtil;
import rtc.volcengine.apiexample.common.Constants;
import rtc.volcengine.apiexample.common.annotations.ApiExample;

public class MediaPlayerActivity extends BaseActivity {

    private static final String TAG = "MediaPlayerActivity";
    private AppCompatButton btnJoinRoom;
    private AppCompatButton btnOpen, btnStart, btnStop, btnPause;
    private AppCompatButton btnPublish, btnUnPublish;
    private EditText roomIdInput;
    private EditText mediaUrlInput;
    private EditText seekPosInput;
    private SeekBar progressBar, playVolumeBar, publishVolumeBar;
    private TextView progressText, playVolumeText, publishVolumeText;
    private FrameLayout remoteViewContainer;
    private AppCompatButton btnSeek;
    private SurfaceView mediaPlayerView;
    private boolean isJoined;
    private RTCVideo rtcVideo;
    private RTCRoom rtcRoom;
    private String roomID;
    private TTVideoEngine ttVideoEngine;
    private MediaAudioProcess audioProcessor;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_media_player);
        setTitle(R.string.title_media_player);
        initUI();
        initTTEnv();

        rtcVideo = RTCVideo.createRTCVideo(this, Constants.APP_ID, rtcVideoEventHandler, null, null);
        initTTVideoEngine();
    }

    private void initUI() {
        btnJoinRoom = findViewById(R.id.btn_join_room);
        roomIdInput = findViewById(R.id.room_id_input);
        btnOpen = findViewById(R.id.btn_open);
        mediaPlayerView = findViewById(R.id.media_player_view);
        btnStart = findViewById(R.id.btn_play);
        btnOpen = findViewById(R.id.btn_open);
        btnStop = findViewById(R.id.btn_stop);
        btnPause = findViewById(R.id.btn_pause);
        mediaUrlInput = findViewById(R.id.media_url_input);
        btnPublish = findViewById(R.id.btn_publish);
        btnUnPublish = findViewById(R.id.btn_unpublish);
//        progressBar = findViewById(R.id.progress_bar);
        playVolumeBar = findViewById(R.id.play_volume_bar);
        publishVolumeBar = findViewById(R.id.publish_volume_bar);
//        progressText = findViewById(R.id.progress_text);
        playVolumeText = findViewById(R.id.play_volume_text);
        publishVolumeText = findViewById(R.id.publish_volume_text);
        remoteViewContainer = findViewById(R.id.remote_view_container);
        btnSeek = findViewById(R.id.btn_seek);
        seekPosInput = findViewById(R.id.position_input);



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
        btnStart.setOnClickListener(v -> ttVideoEngine.play());
        btnStop.setOnClickListener(v -> ttVideoEngine.stop());
        btnOpen.setOnClickListener(v -> {
            String url = mediaUrlInput.getText().toString();
            if (TextUtils.isEmpty(url)) {
                ToastUtil.showAlert(this, "url is null");
                return;
            }
            openMediaSource(url);
        });
        btnPause.setOnClickListener(v -> ttVideoEngine.pause());
        btnPublish.setOnClickListener(v -> startPublish());
        btnUnPublish.setOnClickListener(v -> stopPublish());
        playVolumeBar.setOnSeekBarChangeListener(seekBarChangeListener);
        publishVolumeBar.setOnSeekBarChangeListener(seekBarChangeListener);
        btnSeek.setOnClickListener(v -> {
            Log.i(TAG, "duration:" + ttVideoEngine.getDuration());
            String posStr = seekPosInput.getText().toString();
            if (!posStr.isEmpty()) {
                seekTo(Integer.parseInt(posStr));
            }
        });
    }

    private void initTTEnv() {
        if (BuildConfig.DEBUG) {
            TTVideoEngineLog.turnOn(TTVideoEngineLog.LOG_DEBUG, 1);
            AVMDLLog.turnOn(AVMDLLog.LOG_DEBUG, 1);
            LicenseManager.turnOnLogcat(true);
            CmLog.turnLogLevel(CmLog.LogLevel.D, true);
        }

        File videoCacheDir = new File(getCacheDir(), "video_cache");
        if (!videoCacheDir.exists()) {
            videoCacheDir.mkdirs();
        }
        VodConfig.Builder vodBuilder = new VodConfig.Builder(this)
                .setCacheDirPath(videoCacheDir.getAbsolutePath())
                .setMaxCacheSize(300 * 1024 * 1024);

        Config.Builder playerConfigBuilder = new Config.Builder()
                .setApplicationContext(getApplicationContext())
                .setAppID(getString(R.string.player_app_id))
                .setAppName("ApiExampleDemo")
                // 将 license 文件拷贝到 app 的 assets 文件夹中，并设置 LicenseUri
                // 下面 LicenseUri 对应工程中 assets 路径为：assets/license/vod.lic
                .setLicenseUri("assets:///tt.lic")
                .setAppChannel("channel");
        Env.init(playerConfigBuilder.build());
    }

    private void initTTVideoEngine() {
        ttVideoEngine = new TTVideoEngine(getApplicationContext(), TTVideoEngine.PLAYER_TYPE_OWN);

        ttVideoEngine.setSurfaceHolder(mediaPlayerView.getHolder());
        audioProcessor = new MediaAudioProcess(rtcVideo);
        ttVideoEngine.setVideoEngineCallback(new VideoEngineCallback() {
            @Override
            public void onError(Error error) {
                VideoEngineCallback.super.onError(error);
                Log.i(TAG, "error: " + error.toString());
            }

            @Override
            public void onPlaybackStateChanged(TTVideoEngine engine, int playbackState) {
                VideoEngineCallback.super.onPlaybackStateChanged(engine, playbackState);
                Log.i(TAG, "onPlaybackStateChanged: " + playbackState);
            }

            @Override
            public void onPrepare(TTVideoEngine engine) {
                VideoEngineCallback.super.onPrepare(engine);
                Log.i(TAG, "onPrepare");
            }
        });

        playVolumeBar.setMax((int)ttVideoEngine.getMaxVolume());
        playVolumeText.setText((int)ttVideoEngine.getMaxVolume() + "");
        playVolumeBar.setProgress((int)ttVideoEngine.getVolume());

    }

    SeekBar.OnSeekBarChangeListener seekBarChangeListener = new SeekBar.OnSeekBarChangeListener() {
        @Override
        public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
            if (seekBar == playVolumeBar) {
                if (ttVideoEngine != null) {
                    ttVideoEngine.setVolume(progress, progress);
                }
                playVolumeText.setText("" + progress);
            } else if (seekBar == publishVolumeBar) {
                audioProcessor.setVolume(progress);
                publishVolumeText.setText("" + progress);
            }
        }

        @Override
        public void onStartTrackingTouch(SeekBar seekBar) {
        }

        @Override
        public void onStopTrackingTouch(SeekBar seekBar) {
        }
    };

    private void openMediaSource(String url) {
        String vid = "video_id" + new Random().nextInt(1000); // 视频源与 vid 必须一一对应
        final String cacheKey = TTVideoEngine.computeMD5(url);

    // 1.组装资源
        StrategySource directUrlSource = new DirectUrlSource.Builder()
                .setVid(vid)
                .addItem(new DirectUrlSource.UrlItem.Builder()
                        .setUrl(url)
                        .setCacheKey(cacheKey)
                        .build())
                .build();

    // 2.设置播放源
        ttVideoEngine.setStrategySource(directUrlSource);
        ttVideoEngine.setObjectOption(TTVideoEngine.PLAYER_OPTION_AUDIO_PROCESSOR_OBJECT, audioProcessor);
//        Log.i(TAG, "setAudioProcessor start");
//        ttVideoEngine.setAudioProcessor(audioProcessor);
//        Log.i(TAG, "setAudioProcessor end");

    }

    private void startPublish() {
        rtcVideo.setAudioSourceType(AudioSourceType.AUDIO_SOURCE_TYPE_EXTERNAL);
        audioProcessor.enablePublishStream(true);

    }

    private void stopPublish() {
        audioProcessor.enablePublishStream(false);
    }

    private void seekTo(int position) {
        if (ttVideoEngine != null) {
            ttVideoEngine.seekTo(position, new SeekCompletionListener() {
                @Override
                public void onCompletion(boolean b) {
                    Log.i(TAG, "seek complete");
                }
            });
        }
    }

    private void setRemoteRenderView(String uid) {
        TextureView textureView = new TextureView(this);
        remoteViewContainer.removeAllViews();
        remoteViewContainer.addView(textureView);

        VideoCanvas videoCanvas = new VideoCanvas();
        videoCanvas.renderView = textureView;
        videoCanvas.renderMode = VideoCanvas.RENDER_MODE_HIDDEN;

        RemoteStreamKey remoteStreamKey = new RemoteStreamKey(roomID, uid, StreamIndex.STREAM_INDEX_MAIN);
        // 设置本地视频渲染视图
        rtcVideo.setRemoteVideoCanvas(remoteStreamKey, videoCanvas);
    }

    private void removeRemoteView(String uid) {
        RemoteStreamKey remoteStreamKey = new RemoteStreamKey(roomID, uid, StreamIndex.STREAM_INDEX_MAIN);
        rtcVideo.setRemoteVideoCanvas(remoteStreamKey, null);
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
            Log.i(TAG, "onRoomStateChanged:" + info);
            ToastUtil.showShortToast(MediaPlayerActivity.this, info);
        }

        @Override
        public void onUserJoined(UserInfo userInfo, int elapsed) {
            super.onUserJoined(userInfo, elapsed);
            ToastUtil.showLongToast(MediaPlayerActivity.this, "onUserJoined, uid:" + userInfo.getUid());
        }

        @Override
        public void onUserPublishStream(String uid, MediaStreamType type) {
            super.onUserPublishStream(uid, type);
            runOnUiThread(() -> {
                // 设置远端视频渲染视图
                setRemoteRenderView(uid);
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
        public void onLeaveRoom(RTCRoomStats stats) {
            super.onLeaveRoom(stats);
            ToastUtil.showLongToast(MediaPlayerActivity.this, "onLeaveRoom, stats:" + stats.toString());
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
        if (ttVideoEngine != null) {
            ttVideoEngine.releaseAsync();
            ttVideoEngine = null;
        }
    }
}