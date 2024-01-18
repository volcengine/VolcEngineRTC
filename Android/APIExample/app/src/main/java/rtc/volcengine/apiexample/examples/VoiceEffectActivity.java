package rtc.volcengine.apiexample.examples;

import androidx.appcompat.widget.SwitchCompat;

import android.os.Bundle;
import android.text.TextUtils;
import android.view.TextureView;
import android.view.View;
import android.widget.AdapterView;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.FrameLayout;
import android.widget.SeekBar;
import android.widget.Spinner;
import android.widget.TextView;

import com.ss.bytertc.engine.RTCRoom;
import com.ss.bytertc.engine.RTCRoomConfig;
import com.ss.bytertc.engine.RTCVideo;
import com.ss.bytertc.engine.UserInfo;
import com.ss.bytertc.engine.VideoCanvas;
import com.ss.bytertc.engine.data.AudioMixingType;
import com.ss.bytertc.engine.data.StreamIndex;
import com.ss.bytertc.engine.handler.IRTCRoomEventHandler;
import com.ss.bytertc.engine.handler.IRTCVideoEventHandler;
import com.ss.bytertc.engine.type.AnsMode;
import com.ss.bytertc.engine.type.ChannelProfile;
import com.ss.bytertc.engine.type.RTCRoomStats;
import com.ss.bytertc.engine.type.VoiceChangerType;
import com.ss.bytertc.engine.type.VoiceEqualizationBandFrequency;
import com.ss.bytertc.engine.type.VoiceEqualizationConfig;
import com.ss.bytertc.engine.type.VoiceReverbConfig;
import com.ss.bytertc.engine.type.VoiceReverbType;

import rtc.volcengine.apiexample.BaseActivity;
import rtc.volcengine.apiexample.R;
import rtc.volcengine.apiexample.Utils.ToastUtil;
import rtc.volcengine.apiexample.common.Constants;
import rtc.volcengine.apiexample.common.annotations.ApiExample;


/**
 * 功能名称： VolcEngineRTC 美声与音效
 * 功能简单描述：该功能展示了混响、变声、降噪等功能
 *
 * 此功能涉及的API及回调：
 *     createRTCVideo 创建引擎
 *     destroyRTCVideo 销毁引擎
 *     startVideoCapture 开启视频采集
 *     createRTCRoom 创建RTC房间
 *     joinRoom 进入RTC房间
 *     leaveRoom 离开RTC房间
 *     destroy 销毁RTC房间
 *     setRuntimeParameters 初始化Sami库
 *
 *     setVoiceReverbType 设置混响特效类型
 *     setVoiceChangerType 设置变声特效类型
 *     setLocalVoicePitch 开启本地语音变调功能
 *     enableLocalVoiceReverb 开启本地音效混响效果
 *     setLocalVoiceReverbParam 设置本地采集音频的混响效果
 *     setAnsMode  设置通话中的音频降噪模式
 *
 *     onRoomStateChanged 房间状态回调
 *     onLeaveRoom 离房回调
 *     onUserJoined 用户加入回调
 *     onUserLeave  用户离开回调
 *     onUserPublishStream 用户发流回调
 *     onUserUnpublishStream 用户停止发流回调
 *

 *
 * Demo实现时的逻辑
 *    本Demo演示功能：美声与音效，演示了各种声音处理特效，使用该功能前请咨询技术人员，其中Windows端变声需要申请付费账号，
 *    为了展示简单，所有功能的token都由客户端生成，请在真正接入时视具体情况而定
 */

@ApiExample(name = "声音特效", order = 5)
public class VoiceEffectActivity extends BaseActivity {


    private Button btnJoinRoom;
    private EditText roomIdInput;
    private Spinner voiceChangerType, voiceReverbType, ansMode, voiceEqualization;
    private SeekBar voicePitchBar;
    private SeekBar voiceGainBar;
    private SeekBar roomSizeBar;
    private SeekBar decayTimeBar;
    private SeekBar dampingBar;
    private SeekBar wetGainBar;
    private SeekBar dryGainBar;
    private SeekBar preDelayBar;
    private FrameLayout localViewContainer;
    private SwitchCompat voiceReverbSwitch;
    private RTCVideo rtcVideo;
    private RTCRoom rtcRoom;
    private boolean isJoined;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_voice_effect);
        setTitle(R.string.title_voice_effect);
        initUI();

        rtcVideo = RTCVideo.createRTCVideo(this, Constants.APP_ID, rtcVideoEventHandler, null, null);
        // 开启音视频采集
        rtcVideo.startAudioCapture();
        rtcVideo.startVideoCapture();

        setLocalRenderView();


    }

    private void initUI() {
        localViewContainer = findViewById(R.id.local_view_container);
        btnJoinRoom = findViewById(R.id.btn_join_room);
        roomIdInput = findViewById(R.id.room_id_input);
        voiceChangerType = findViewById(R.id.voice_changer_spinner);
        voiceReverbType = findViewById(R.id.voice_reverb_spinner);
        ansMode = findViewById(R.id.ans_mode_spinner);
        voiceEqualization = findViewById(R.id.voice_equalization_spinner);
        voicePitchBar = findViewById(R.id.voice_pitch_bar);
        voiceGainBar = findViewById(R.id.voice_gain_bar);
        roomSizeBar = findViewById(R.id.room_size_bar);
        decayTimeBar = findViewById(R.id.decay_time_bar);
        dampingBar = findViewById(R.id.damping_bar);
        wetGainBar = findViewById(R.id.wet_gain_bar);
        dryGainBar = findViewById(R.id.dry_gain_bar);
        preDelayBar = findViewById(R.id.pre_delay_bar);
        voiceReverbSwitch = findViewById(R.id.voice_reverb_switch);


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

        voiceChangerType.setOnItemSelectedListener(itemSelectedListener);
        voiceReverbType.setOnItemSelectedListener(itemSelectedListener);
        ansMode.setOnItemSelectedListener(itemSelectedListener);
        voiceEqualization.setOnItemSelectedListener(itemSelectedListener);
        voicePitchBar.setOnSeekBarChangeListener(seekBarChangeListener);
        voiceGainBar.setOnSeekBarChangeListener(seekBarChangeListener);
        decayTimeBar.setOnSeekBarChangeListener(seekBarChangeListener);
        dampingBar.setOnSeekBarChangeListener(seekBarChangeListener);
        wetGainBar.setOnSeekBarChangeListener(seekBarChangeListener);
        dryGainBar.setOnSeekBarChangeListener(seekBarChangeListener);
        preDelayBar.setOnSeekBarChangeListener(seekBarChangeListener);
        roomSizeBar.setOnSeekBarChangeListener(seekBarChangeListener);
        voiceReverbSwitch.setOnCheckedChangeListener((buttonView, isChecked) -> rtcVideo.enableLocalVoiceReverb(isChecked));


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

    AdapterView.OnItemSelectedListener itemSelectedListener = new AdapterView.OnItemSelectedListener() {
        @Override
        public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
            if (parent.getId() == R.id.voice_changer_spinner) {
                String item = voiceChangerType.getSelectedItem().toString();
                rtcVideo.setVoiceChangerType(getVoiceChangerType(item));
            } else if (parent.getId() == R.id.ans_mode_spinner) {
                String item = ansMode.getSelectedItem().toString();
                rtcVideo.setAnsMode(getAnsMode(item));
            } else if (parent.getId() == R.id.voice_reverb_spinner) {
                String item = voiceReverbType.getSelectedItem().toString();
                rtcVideo.setVoiceReverbType(getVoiceReverbType(item));
            } else if(parent.getId() == R.id.voice_equalization_spinner) {
                String item = voiceEqualization.getSelectedItem().toString();
                setLocalVoiceEqualization(getBandFrequency(item), voiceGainBar.getProgress());
            }
        }

        @Override
        public void onNothingSelected(AdapterView<?> parent) {

        }
    };

    private VoiceChangerType getVoiceChangerType(String name) {
        switch (name) {
            case "VOICE_CHANGER_ORIGINAL":
                return VoiceChangerType.VOICE_CHANGER_ORIGINAL;
            case "VOICE_CHANGER_GIANT":
                return VoiceChangerType.VOICE_CHANGER_GIANT;
            case "VOICE_CHANGER_CHIPMUNK":
                return VoiceChangerType.VOICE_CHANGER_CHIPMUNK;
            case "VOICE_CHANGER_MINIONST":
                return VoiceChangerType.VOICE_CHANGER_MINIONST;
            case "VOICE_CHANGER_VIBRATO":
                return VoiceChangerType.VOICE_CHANGER_VIBRATO;
            case "VOICE_CHANGER_ROBOT":
                return VoiceChangerType.VOICE_CHANGER_ROBOT;
            default:
                return VoiceChangerType.VOICE_CHANGER_ORIGINAL;
        }
    }

    private VoiceReverbType getVoiceReverbType(String name) {
        switch (name) {
            case "VOICE_REVERB_ORIGINAL":
                return VoiceReverbType.VOICE_REVERB_ORIGINAL;
            case "VOICE_REVERB_ECHO":
                return VoiceReverbType.VOICE_REVERB_ECHO;
            case "VOICE_REVERB_CONCERT":
                return VoiceReverbType.VOICE_REVERB_CONCERT;
            case "VOICE_REVERB_ETHEREAL":
                return VoiceReverbType.VOICE_REVERB_ETHEREAL;
            case "VOICE_REVERB_KTV":
                return VoiceReverbType.VOICE_REVERB_KTV;
            case "VOICE_REVERB_STUDIO":
                return VoiceReverbType.VOICE_REVERB_STUDIO;
            case "VOICE_REVERB_VIRTUAL_STEREO":
                return VoiceReverbType.VOICE_REVERB_VIRTUAL_STEREO;
            case "VOICE_REVERB_SPACIOUS":
                return VoiceReverbType.VOICE_REVERB_SPACIOUS;
            case "VOICE_REVERB_3D":
                return VoiceReverbType.VOICE_REVERB_3D;
            default:
                return VoiceReverbType.VOICE_REVERB_ORIGINAL;
        }
    }

    private VoiceEqualizationBandFrequency getBandFrequency(String name) {
        switch (name) {
            case "VOICE_EQUALIZATION_BAND_FREQUENCY_31":
                return VoiceEqualizationBandFrequency.VOICE_EQUALIZATION_BAND_FREQUENCY_31;
            case "VOICE_EQUALIZATION_BAND_FREQUENCY_62":
                return VoiceEqualizationBandFrequency.VOICE_EQUALIZATION_BAND_FREQUENCY_62;
            case "VOICE_EQUALIZATION_BAND_FREQUENCY_125":
                return VoiceEqualizationBandFrequency.VOICE_EQUALIZATION_BAND_FREQUENCY_125;
            case "VOICE_EQUALIZATION_BAND_FREQUENCY_250":
                return VoiceEqualizationBandFrequency.VOICE_EQUALIZATION_BAND_FREQUENCY_250;
            case "VOICE_EQUALIZATION_BAND_FREQUENCY_500":
                return VoiceEqualizationBandFrequency.VOICE_EQUALIZATION_BAND_FREQUENCY_500;
            case "VOICE_EQUALIZATION_BAND_FREQUENCY_1k":
                return VoiceEqualizationBandFrequency.VOICE_EQUALIZATION_BAND_FREQUENCY_1K;
            case "VOICE_EQUALIZATION_BAND_FREQUENCY_2k":
                return VoiceEqualizationBandFrequency.VOICE_EQUALIZATION_BAND_FREQUENCY_2K;
            case "VOICE_EQUALIZATION_BAND_FREQUENCY_4k":
                return VoiceEqualizationBandFrequency.VOICE_EQUALIZATION_BAND_FREQUENCY_4K;
            case "VOICE_EQUALIZATION_BAND_FREQUENCY_8k":
                return VoiceEqualizationBandFrequency.VOICE_EQUALIZATION_BAND_FREQUENCY_8K;
            case "VOICE_EQUALIZATION_BAND_FREQUENCY_16k":
                return VoiceEqualizationBandFrequency.VOICE_EQUALIZATION_BAND_FREQUENCY_16K;
            default:
                return VoiceEqualizationBandFrequency.VOICE_EQUALIZATION_BAND_FREQUENCY_31;
        }
    }

    private AnsMode getAnsMode(String name) {
        switch (name) {
            case "ANS_MODE_DISABLE":
                return AnsMode.ANS_MODE_DISABLE;
            case "ANS_MODE_LOW":
                return AnsMode.ANS_MODE_LOW;
            case "ANS_MODE_MEDIUM":
                return AnsMode.ANS_MODE_MEDIUM;
            case "ANS_MODE_HIGH":
                return AnsMode.ANS_MODE_HIGH;
            case "ANS_MODE_AUTOMATIC":
                return AnsMode.ANS_MODE_AUTOMATIC;
            default:
                return AnsMode.ANS_MODE_DISABLE;
        }
    }



    SeekBar.OnSeekBarChangeListener seekBarChangeListener = new SeekBar.OnSeekBarChangeListener() {
        @Override
        public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
            if (seekBar == voicePitchBar) {
                rtcVideo.setLocalVoicePitch(progress);
                ((TextView) findViewById(R.id.voice_pitch_text)).setText("" + progress);
            } else if (seekBar == voiceGainBar) {
                String item = voiceEqualization.getSelectedItem().toString();
                setLocalVoiceEqualization(getBandFrequency(item), progress);
                ((TextView) findViewById(R.id.voice_gain_text)).setText("" + progress);
            } else if (seekBar == roomSizeBar) {
                ((TextView) findViewById(R.id.room_size_text)).setText("" + progress);
                setLocalVoiceReverbParam();
            } else if (seekBar == dampingBar) {
                ((TextView) findViewById(R.id.damping_text)).setText("" + progress);
                setLocalVoiceReverbParam();
            } else if (seekBar == decayTimeBar) {
                ((TextView) findViewById(R.id.decat_time_text)).setText("" + progress);
                setLocalVoiceReverbParam();
            } else if (seekBar == wetGainBar) {
                ((TextView) findViewById(R.id.wet_gain_text)).setText("" + progress);
                setLocalVoiceReverbParam();
            } else if (seekBar == dryGainBar) {
                ((TextView) findViewById(R.id.dry_gain_text)).setText("" + progress);
                setLocalVoiceReverbParam();
            } else if (seekBar == preDelayBar) {
                ((TextView) findViewById(R.id.pre_delay_text)).setText("" + progress);
                setLocalVoiceReverbParam();
            }
        }

        @Override
        public void onStartTrackingTouch(SeekBar seekBar) {
        }

        @Override
        public void onStopTrackingTouch(SeekBar seekBar) {
        }
    };

    private void setLocalVoiceEqualization(VoiceEqualizationBandFrequency frequency, int gain) {
        VoiceEqualizationConfig config = new VoiceEqualizationConfig(frequency, gain);
        rtcVideo.setLocalVoiceEqualization(config);
    }

    private void setLocalVoiceReverbParam() {
        if (!voiceReverbSwitch.isChecked()) {
            ToastUtil.showAlert(this, "请先开启混响效果开关");
            return;
        }
        VoiceReverbConfig config = new VoiceReverbConfig(roomSizeBar.getProgress(), decayTimeBar.getProgress(), dampingBar.getProgress(),
                wetGainBar.getProgress(), dryGainBar.getProgress(), preDelayBar.getProgress());
        rtcVideo.setLocalVoiceReverbParam(config);
    }

    IRTCVideoEventHandler rtcVideoEventHandler = new IRTCVideoEventHandler() {
    };

    IRTCRoomEventHandler rtcRoomEventHandler = new IRTCRoomEventHandler() {
        @Override
        public void onRoomStateChanged(String roomId, String uid, int state, String extraInfo) {
            super.onRoomStateChanged(roomId, uid, state, extraInfo);
            String info = String.format("roomId:%s, uid:%s, state:%d, extraInfo:%s", roomId, uid, state, extraInfo);
            ToastUtil.showShortToast(VoiceEffectActivity.this, info);
        }

        @Override
        public void onLeaveRoom(RTCRoomStats stats) {
            super.onLeaveRoom(stats);
            ToastUtil.showLongToast(VoiceEffectActivity.this, "onLeaveRoom, stats:" + stats.toString());
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