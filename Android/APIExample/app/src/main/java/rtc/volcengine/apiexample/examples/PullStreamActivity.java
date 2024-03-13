package rtc.volcengine.apiexample.examples;

import androidx.appcompat.widget.AppCompatButton;

import android.graphics.Bitmap;
import android.os.Bundle;
import android.text.TextUtils;
import android.util.Log;
import android.view.Surface;
import android.view.SurfaceView;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import com.bytedance.vcloud.cacheModule.utils.CmLog;
import com.pandora.common.env.Env;
import com.pandora.common.env.config.Config;
import com.pandora.common.env.config.VodConfig;
import com.pandora.live.player.LivePlayerBuilder;
import com.pandora.ttlicense2.LicenseManager;
import com.ss.mediakit.medialoader.AVMDLLog;
import com.ss.ttvideoengine.utils.TTVideoEngineLog;
import com.ss.videoarch.liveplayer.ILiveListener;
import com.ss.videoarch.liveplayer.INetworkClient;
import com.ss.videoarch.liveplayer.VeLivePlayer;
import com.ss.videoarch.liveplayer.VeLivePlayerAudioFrame;
import com.ss.videoarch.liveplayer.VeLivePlayerConfiguration;
import com.ss.videoarch.liveplayer.VeLivePlayerDef;
import com.ss.videoarch.liveplayer.VeLivePlayerError;
import com.ss.videoarch.liveplayer.VeLivePlayerObserver;
import com.ss.videoarch.liveplayer.VeLivePlayerStatistics;
import com.ss.videoarch.liveplayer.VeLivePlayerStreamData;
import com.ss.videoarch.liveplayer.VeLivePlayerVideoFrame;
import com.ss.videoarch.liveplayer.VideoLiveManager;
import com.ss.videoarch.liveplayer.log.LiveError;
import com.ss.videoarch.liveplayer.log.VeLivePlayerLog;

import org.json.JSONObject;

import java.io.File;
import java.nio.ByteBuffer;
import java.util.ArrayList;

import rtc.volcengine.apiexample.BaseActivity;
import rtc.volcengine.apiexample.BuildConfig;
import rtc.volcengine.apiexample.R;
import rtc.volcengine.apiexample.Utils.ToastUtil;
import rtc.volcengine.apiexample.common.annotations.ApiExample;

@ApiExample(order = 9.1, name = "拉流")
public class PullStreamActivity extends BaseActivity {

    private static final String TAG = "PullStreamActivity";

    private SurfaceView surfaceView;
    private EditText urlInput;
    private AppCompatButton btnStartPull, btnStopPull;
    private TextView seiMsg;
    private VeLivePlayer livePlayer;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_pull_stream);
        initTTEnv();
        livePlayer = new VideoLiveManager(Env.getApplicationContext());
        initUI();

        // 创建配置
        VeLivePlayerConfiguration config = new VeLivePlayerConfiguration();
        // 打开周期性回调
        config.enableStatisticsCallback = true;
        // 打开 Local DNS 预解析
        config.enableLiveDNS = true;
        config.enableSei = true;
        // 初始化播放器
        livePlayer.setConfig(config);

        // 配置播放器回调
        livePlayer.setObserver(mLivePlayerObserver);



    }

    // VeLivePlayerObserver 回调
    VeLivePlayerObserver mLivePlayerObserver = new VeLivePlayerObserver() {

        @Override
        public void onError(VeLivePlayer player, VeLivePlayerError error) {
            // 错误回调
            Log.d(TAG, String.format("onError(): %s", error.mErrorCode));
            ToastUtil.showShortToast(PullStreamActivity.this, error.mErrorCode + "");
        }

        @Override
        public void onFirstVideoFrameRender(VeLivePlayer player, boolean isFirstFrame) {
            // 视频首帧回调
            Log.d(TAG, String.format("onFirstFrame(): %b", isFirstFrame));
        }

        @Override
        public void onFirstAudioFrameRender(VeLivePlayer player, boolean isFirstFrame) {
            // 音频首帧回调
        }

        @Override
        public void onStallStart(VeLivePlayer player) {
            // 卡顿开始回调
        }

        @Override
        public void onStallEnd(VeLivePlayer player) {
            // 卡顿结束回调
        }

        @Override
        public void onVideoRenderStall(VeLivePlayer player, long stallTime) {
            // 视频卡顿回调
        }

        @Override
        public void onAudioRenderStall(VeLivePlayer player, long stallTime) {
            // 音频卡顿回调
        }

        @Override
        public void onResolutionSwitch(VeLivePlayer player, VeLivePlayerDef.VeLivePlayerResolution resolution, VeLivePlayerError error, VeLivePlayerDef.VeLivePlayerResolutionSwitchReason reason) {
            // 播放档位变化回调
        }

        @Override
        public void onVideoSizeChanged(VeLivePlayer player, int width, int height) {
            // 分辨率变化回调
        }

        @Override
        public void onReceiveSeiMessage(VeLivePlayer player, String message) {
            // SEI 通知回调
            seiMsg.setText("SEI:" + message);
            Log.i(TAG, "receive sei:" + message);
        }

        @Override
        public void onMainBackupSwitch(VeLivePlayer player, VeLivePlayerDef.VeLivePlayerStreamType streamType, VeLivePlayerError error) {
            // 主备切换回调
        }

        @Override
        public void onPlayerStatusUpdate(VeLivePlayer player, VeLivePlayerDef.VeLivePlayerStatus status) {
            // 播放器状态变化回调
        }

        @Override
        public void onStatistics(VeLivePlayer player, VeLivePlayerStatistics statistics) {
            // 周期性回调

        }

        @Override
        public void onSnapshotComplete(VeLivePlayer player, Bitmap bitmap) {
            // 截图回调
        }

        @Override
        public void onRenderVideoFrame(VeLivePlayer player, VeLivePlayerVideoFrame videoFrame) {
            // 视频帧订阅回调
        }

        @Override
        public void onRenderAudioFrame(VeLivePlayer player, VeLivePlayerAudioFrame audioFrame) {
            // 音频帧订阅回调
        }

        @Override
        public void onStreamFailedOpenSuperResolution(VeLivePlayer veLivePlayer, VeLivePlayerError veLivePlayerError) {

        }
    };


    private void initUI() {
        surfaceView = findViewById(R.id.video_view);
        livePlayer.setSurfaceHolder(surfaceView.getHolder());

        btnStartPull = findViewById(R.id.btn_start_pull);
        btnStopPull = findViewById(R.id.btn_stop_pull);
        urlInput = findViewById(R.id.url_input);
        seiMsg = findViewById(R.id.sei_msg);

        btnStartPull.setOnClickListener(v -> {
            String url = urlInput.getText().toString();
            if (TextUtils.isEmpty(url)) {
                ToastUtil.showAlert(PullStreamActivity.this, "url为空");
                return;
            }

            // 配置 RTM 地址
            VeLivePlayerStreamData.VeLivePlayerStream playStreamRTM = new VeLivePlayerStreamData.VeLivePlayerStream();
            playStreamRTM.url = url;
            playStreamRTM.format = VeLivePlayerDef.VeLivePlayerFormat.VeLivePlayerFormatFLV;
            playStreamRTM.resolution = VeLivePlayerDef.VeLivePlayerResolution.VeLivePlayerResolutionOrigin;
            playStreamRTM.streamType = VeLivePlayerDef.VeLivePlayerStreamType.VeLivePlayerStreamTypeMain;

            // 创建 VeLivePlayerStreamData
            VeLivePlayerStreamData streamData = new VeLivePlayerStreamData();
            streamData.mainStreamList = new ArrayList<>();

// 添加 RTM 流地址
            streamData.mainStreamList.add(playStreamRTM);

            // 配置默认 format 和 protocol
            streamData.defaultFormat = VeLivePlayerDef.VeLivePlayerFormat.VeLivePlayerFormatFLV;
            streamData.defaultProtocol = VeLivePlayerDef.VeLivePlayerProtocol.VeLivePlayerProtocolTCP;

// 配置播放源
            livePlayer.setPlayStreamData(streamData);

// 开始播放
            livePlayer.play();

//            livePlayer.setPlayUrl(url);
//            livePlayer.play();
        });
        btnStopPull.setOnClickListener(v -> livePlayer.stop());
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
}