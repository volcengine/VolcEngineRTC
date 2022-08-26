package com.ss.video.rtc.demo.advanced;

import static com.ss.bytertc.engine.type.MessageConfig.MessageConfigReliableOrdered;

import android.annotation.SuppressLint;
import android.content.Context;
import android.graphics.Color;
import android.graphics.drawable.ColorDrawable;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.text.TextUtils;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.Window;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.Switch;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatDialog;
import androidx.fragment.app.DialogFragment;
import androidx.lifecycle.Lifecycle;
import androidx.lifecycle.LifecycleEventObserver;
import androidx.lifecycle.LifecycleOwner;

import com.ss.bytertc.engine.RTCEngine;
import com.ss.bytertc.engine.RTCVideo;
import com.ss.bytertc.engine.VideoCanvas;
import com.ss.bytertc.engine.handler.IRTCEngineEventHandler;
import com.ss.bytertc.engine.handler.IRTCVideoEventHandler;
import com.ss.bytertc.engine.type.NetworkDetectionLinkType;
import com.ss.bytertc.engine.type.NetworkDetectionStartReturn;
import com.ss.rtc.demo.advanced.R;
import com.ss.video.rtc.demo.advanced.entity.VideoConfigEntity;
import com.ss.video.rtc.demo.basic_module.ui.CommonListDialog;
import com.ss.video.rtc.demo.basic_module.utils.SafeToast;
import com.ss.video.rtc.demo.basic_module.utils.Utilities;

import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Locale;
import java.util.Map;

import common.SubTitleLayout;
import common.ValueLayout;

public class PreJoinSettingsDialog extends DialogFragment implements LifecycleEventObserver {
    public static final String TAG_FOR_SHOW = "PreJoinSettingsDialog";
    private VideoConfigEntity mVideoConfig;
    private boolean mHasChanged;
    private View rootView;
    private CommonListDialog mLocalFitModeDialog;
    private CommonListDialog mRemoteFitModeDialog;

    @Override
    public void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setStyle(DialogFragment.STYLE_NO_TITLE, R.style.DialogFullScreen);
        mVideoConfig = ConfigManger.getInstance().getVideoConfig();
    }

    @Override
    public void onAttach(@NonNull Context context) {
        super.onAttach(context);
        Object hostObj = getHost();
        if (hostObj instanceof LifecycleOwner) {
            ((LifecycleOwner) hostObj).getLifecycle().addObserver(this);
        }
    }

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        rootView = inflater.inflate(R.layout.fragment_pre_join_setting, container, false);
        //titlebar
        ImageView backArrow = rootView.findViewById(R.id.title_bar_left_iv);
        backArrow.setImageResource(R.mipmap.back_arrow);
        backArrow.setOnClickListener(v -> dismiss());
        TextView title = rootView.findViewById(R.id.title_bar_title_tv);
        title.setText(R.string.setting);

        //采集渲染设定
        View capLayout = rootView.findViewById(R.id.sub_title_cap_layout);
        TextView capTitle = capLayout.findViewById(R.id.title);
        capTitle.setText(R.string.sub_title_cap);
        //视频源
        View videoSource = rootView.findViewById(R.id.video_source);
        TextView videoSourceTv = videoSource.findViewById(R.id.left_tv);
        videoSourceTv.setText(R.string.video_source);
        RadioGroup videoSourceRG = videoSource.findViewById(R.id.video_source_rg);
        RadioButton cameraSource = videoSource.findViewById(R.id.video_source_camera_rb);
        cameraSource.setText(R.string.video_source_camera);
        cameraSource.setChecked(mVideoConfig.mVideoSource == VideoConfigEntity.VIDEO_SOURCE_TYPE_CAMERA);
        RadioButton screenSource = videoSource.findViewById(R.id.video_source_screen_rb);
        screenSource.setText(R.string.video_source_screen);
        screenSource.setChecked(mVideoConfig.mVideoSource == VideoConfigEntity.VIDEO_SOURCE_TYPE_SCREEN);
        videoSourceRG.setOnCheckedChangeListener((group, checkedId) -> {
            int targetSource = checkedId == R.id.video_source_camera_rb
                    ? VideoConfigEntity.VIDEO_SOURCE_TYPE_CAMERA
                    : VideoConfigEntity.VIDEO_SOURCE_TYPE_SCREEN;
            if (mVideoConfig.mVideoSource != targetSource) {
                mHasChanged = true;
                mVideoConfig.mVideoSource = targetSource;
            }
        });
        //外部源采集
        View captureView = rootView.findViewById(R.id.custom_capture);
        TextView externalVideoTv = captureView.findViewById(R.id.left_tv);
        externalVideoTv.setText(R.string.pre_join_setting_external_video_source);
        @SuppressLint("UseSwitchCompatOrMaterialCode")
        Switch externalVideoSwitch = captureView.findViewById(R.id.switch_lg);
        externalVideoSwitch.setChecked(mVideoConfig.mCustomCapture);
        externalVideoSwitch.setOnCheckedChangeListener((compoundButton, b) -> {
            boolean customCaptureEnable = externalVideoSwitch.isChecked();
            mHasChanged = true;
            mVideoConfig.mCustomCapture = customCaptureEnable;
        });
        //外部源渲染
        View renderView = rootView.findViewById(R.id.custom_render);
        TextView externalRenderTv = renderView.findViewById(R.id.left_tv);
        externalRenderTv.setText(R.string.pre_join_setting_external_render);
        @SuppressLint("UseSwitchCompatOrMaterialCode")
        Switch externalRenderSwitch = renderView.findViewById(R.id.switch_lg);
        externalRenderSwitch.setChecked(mVideoConfig.mCustomRender);
        externalRenderSwitch.setOnCheckedChangeListener((compoundButton, b) -> {
            boolean customRenderEnable = externalRenderSwitch.isChecked();
            mHasChanged = true;
            mVideoConfig.mCustomRender = customRenderEnable;
        });
        //本地视图填充模式
        handleLocalVideoFillMode();
        //远端视图填充模式
        handleRemoteVideoFillMode();

        //进房前检测
        View networkQualityLayout = rootView.findViewById(R.id.sub_title_network_quality_layout);
        TextView networkQualityTitle = networkQualityLayout.findViewById(R.id.title);
        networkQualityTitle.setText(R.string.sub_title_network_quality);
        View networkQuality = rootView.findViewById(R.id.network_quality);
        TextView networkQualityTv = networkQuality.findViewById(R.id.left_tv);
        networkQualityTv.setText(R.string.network_quality_test);
        networkQuality.setOnClickListener(v -> {
            NetworkQualityDialog dialog = new NetworkQualityDialog(getContext());
            dialog.show();
        });

        //消息
        SubTitleLayout rtmLayout = rootView.findViewById(R.id.subtitle_rtm_message);
        rtmLayout.setTitle("消息");
        ValueLayout rtmMessage = rootView.findViewById(R.id.rtm_message);
        rtmMessage.setTitle("发送房间外实时消息");
        rtmMessage.setOnClickListener(v -> {
            RTMDialog dialog = new RTMDialog(getContext());
            dialog.show();
        });
        return rootView;
    }

    /****设置本地视频渲染填充模式***/
    private void handleLocalVideoFillMode() {
        View localFitModeView = rootView.findViewById(R.id.local_fit_mode);
        TextView localFitModeTitleTv = localFitModeView.findViewById(R.id.left_tv);
        localFitModeTitleTv.setText(R.string.local_view_fit_mode);
        TextView desc = localFitModeView.findViewById(R.id.right_tv);
        HashMap<Integer, String> fillModes = getAllFitModeDesc();
        int curFitMode = mVideoConfig.mLocalVideoFillMode;
        desc.setText(fillModes.get(curFitMode));
        localFitModeView.setOnClickListener(view -> {
            ArrayList<String> modes = new ArrayList<>(2);
            modes.addAll(fillModes.values());
            mLocalFitModeDialog = new CommonListDialog(getActivity(), modes);
            mLocalFitModeDialog.setButtonClickListener(v -> mLocalFitModeDialog.dismiss());
            mLocalFitModeDialog.setOnItemClickListener((index, str) -> {
                desc.setText(str);
                int fillMode = getFitModeByDesc(fillModes, str);
                mHasChanged = true;
                mVideoConfig.mLocalVideoFillMode = fillMode;
                mLocalFitModeDialog.dismiss();
            });
            mLocalFitModeDialog.show();
        });
    }

    private HashMap<Integer, String> getAllFitModeDesc() {
        String[] videoFillMode = Utilities.getApplicationContext()
                .getResources().getStringArray(R.array.video_fill_mode);
        HashMap<Integer, String> fitModes = new HashMap<>(2);
        if (videoFillMode == null || videoFillMode.length == 0) {
            return fitModes;
        }
        for (String item : videoFillMode) {
            String[] kv = item.split("-");
            if (kv.length < 2) {
                continue;
            }
            fitModes.put(Integer.parseInt(kv[1]), kv[0]);
        }
        return fitModes;
    }

    private Integer getFitModeByDesc(HashMap<Integer, String> fitModes, String desc) {
        Integer result = VideoCanvas.RENDER_MODE_FIT;
        if (fitModes == null || fitModes.size() == 0) {
            return result;
        }
        if (TextUtils.isEmpty(desc)) {
            return result;
        }
        for (Map.Entry<Integer, String> entry : fitModes.entrySet()) {
            if (TextUtils.equals(desc, entry.getValue())) {
                result = entry.getKey();
            }
        }
        return result;
    }

    /****设置远端视频渲染填充模式***/
    private void handleRemoteVideoFillMode() {
        View remoteFitModeView = rootView.findViewById(R.id.remote_fit_mode);
        TextView remoteFitModeTitleTv = remoteFitModeView.findViewById(R.id.left_tv);
        remoteFitModeTitleTv.setText(R.string.remote_view_fit_mode);
        TextView desc = remoteFitModeView.findViewById(R.id.right_tv);
        HashMap<Integer, String> fillModes = getAllFitModeDesc();
        int curFitMode = mVideoConfig.mRemoteVideoFillMode;
        desc.setText(fillModes.get(curFitMode));
        remoteFitModeView.setOnClickListener(view -> {
            ArrayList<String> modes = new ArrayList<>(2);
            modes.addAll(fillModes.values());
            mRemoteFitModeDialog = new CommonListDialog(getActivity(), modes);
            mRemoteFitModeDialog.setButtonClickListener(v -> mRemoteFitModeDialog.dismiss());
            mRemoteFitModeDialog.setOnItemClickListener((index, str) -> {
                desc.setText(str);
                int fillMode = getFitModeByDesc(fillModes, str);
                mHasChanged = true;
                mVideoConfig.mRemoteVideoFillMode = fillMode;
                mRemoteFitModeDialog.dismiss();
            });
            mRemoteFitModeDialog.show();
        });
    }

    public static class NetworkQualityDialog extends AppCompatDialog {

        private RTCVideo mRTCVideo;
        private boolean mEnableUplinkDetection = true;
        private int mUplinkDetectionTarget = 10000;
        private boolean mEnableDownlinkDetection = true;
        private int mDownlinkDetectionTarget = 10000;

        private View mStartLayout;
        private View mStopLayout;
        private View mUplinkStatLayout;
        private View mDownlinkStatLayout;

        private ValueLayout mUplinkNetwork;
        private ValueLayout mUplinkRTT;
        private ValueLayout mUplinkLossRate;
        private ValueLayout mUplinkBandwidth;
        private ValueLayout mUplinkJitter;

        private ValueLayout mDownlinkNetwork;
        private ValueLayout mDownlinkRTT;
        private ValueLayout mDownlinkLossRate;
        private ValueLayout mDownlinkBandwidth;
        private ValueLayout mDownlinkJitter;

        private final Handler mMainHandler = new Handler(Looper.getMainLooper());

        private final IRTCVideoEventHandler mIRTCEngineEventHandler = new IRTCVideoEventHandler() {
            @Override
            public void onNetworkDetectionResult(NetworkDetectionLinkType type, int quality, int rtt, double lostRate, int bitrate, int jitter) {
                super.onNetworkDetectionResult(type, quality, rtt, lostRate, bitrate, jitter);
                mMainHandler.post(() -> {
                    String network = quality + "";
                    if (type == NetworkDetectionLinkType.NetworkDetectionLinkTypeUp) {
                        mUplinkNetwork.setValue(network);
                        mUplinkRTT.setValue(rtt + "ms");
                        mUplinkLossRate.setValue(lostRate * 100 + "%");
                        mUplinkBandwidth.setValue(bitrate + "kbps");
                        mUplinkJitter.setValue(jitter + "ms");
                    } else if (type == NetworkDetectionLinkType.NetworkDetectionLinkTypeDown) {
                        mDownlinkNetwork.setValue(network);
                        mDownlinkRTT.setValue(rtt + "ms");
                        mDownlinkLossRate.setValue(lostRate * 100 + "%");
                        mDownlinkBandwidth.setValue(bitrate + "kbps");
                        mDownlinkJitter.setValue(jitter + "ms");
                    }
                });
            }
        };

        public NetworkQualityDialog(Context context) {
            super(context);
            supportRequestWindowFeature(Window.FEATURE_NO_TITLE);
        }

        public NetworkQualityDialog(Context context, int theme) {
            super(context, theme);
            supportRequestWindowFeature(Window.FEATURE_NO_TITLE);
        }

        protected NetworkQualityDialog(Context context, boolean cancelable, OnCancelListener cancelListener) {
            super(context, cancelable, cancelListener);
            supportRequestWindowFeature(Window.FEATURE_NO_TITLE);
        }

        @Override
        protected void onCreate(Bundle savedInstanceState) {
            super.onCreate(savedInstanceState);
            setContentView(R.layout.setting_network_quality);
            getWindow().setBackgroundDrawable(new ColorDrawable(Color.WHITE));
            getWindow().setLayout(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT);

            mStartLayout = findViewById(R.id.start_detection);
            mStopLayout = findViewById(R.id.stop_detection);

            SubTitleLayout titleLayout = mStartLayout.findViewById(R.id.title_bar_layout);
            titleLayout.setTitle("网络监测");

            View uplinkView = mStartLayout.findViewById(R.id.uplink_switch);
            TextView uplinkSwitchTv = uplinkView.findViewById(R.id.left_tv);
            uplinkSwitchTv.setText("上行带宽探测");
            Switch uplinkSwitchSwitch = uplinkView.findViewById(R.id.switch_lg);
            uplinkSwitchSwitch.setChecked(mEnableUplinkDetection);
            uplinkSwitchSwitch.setOnCheckedChangeListener((compoundButton, b) -> {
                mEnableUplinkDetection = b;
            });

            ValueLayout uplinkBitrateView = mStartLayout.findViewById(R.id.uplink_bitrate);
            uplinkBitrateView.setTitle("上行带宽探测目标码率");
            uplinkBitrateView.setValue(mUplinkDetectionTarget + "kbps");
            uplinkBitrateView.setOnClickListener(view -> {
                CommonInputDialog.IInputCallback inputCallback = new CommonInputDialog.IInputCallback() {

                    @Override
                    String getHint() {
                        return null;
                    }

                    @Override
                    String getEmptyTip() {
                        return null;
                    }

                    @Override
                    void action(String input) {
                        int num;
                        try {
                            num = Integer.parseInt(input);
                        } catch (Exception e) {
                            num = 0;
                        }
                        mUplinkDetectionTarget = num;
                        uplinkBitrateView.setValue(mUplinkDetectionTarget + "kbps");
                    }
                };
                CommonInputDialog dialog = new CommonInputDialog(getContext(),
                        "目标码率", "默认值：由SDK自动上探最高码率（10000kbps）",
                        Collections.singletonList(inputCallback));
                dialog.show();
            });

            View downlinkView = mStartLayout.findViewById(R.id.downlink_switch);
            TextView downlinkSwitchTv = downlinkView.findViewById(R.id.left_tv);
            downlinkSwitchTv.setText("下行带宽探测");
            Switch downlinkSwitchSwitch = downlinkView.findViewById(R.id.switch_lg);
            downlinkSwitchSwitch.setChecked(mEnableDownlinkDetection);
            downlinkSwitchSwitch.setOnCheckedChangeListener((compoundButton, b) -> {
                mEnableDownlinkDetection = b;
            });

            ValueLayout downlinkBitrateView = mStartLayout.findViewById(R.id.downlink_bitrate);
            downlinkBitrateView.setTitle("下行带宽探测目标码率");
            downlinkBitrateView.setValue(mDownlinkDetectionTarget + "kbps");
            downlinkBitrateView.setOnClickListener(view -> {
                CommonInputDialog.IInputCallback inputCallback = new CommonInputDialog.IInputCallback() {

                    @Override
                    String getHint() {
                        return null;
                    }

                    @Override
                    String getEmptyTip() {
                        return null;
                    }

                    @Override
                    void action(String input) {
                        int num;
                        try {
                            num = Integer.parseInt(input);
                        } catch (Exception e) {
                            num = 0;
                        }
                        mDownlinkDetectionTarget = num;
                        downlinkBitrateView.setValue(mDownlinkDetectionTarget + "kbps");
                    }
                };
                CommonInputDialog dialog = new CommonInputDialog(getContext(),
                        "目标码率", "默认值：由SDK自动上探最高码率（10000kbps）",
                        Collections.singletonList(inputCallback));
                dialog.show();
            });

            TextView startDetectionBtn = mStartLayout.findViewById(R.id.start_detection_btn);
            startDetectionBtn.setOnClickListener(v -> {
                switchStatus(true);
                showOrHideStats();
                NetworkDetectionStartReturn startReturn
                        = mRTCVideo.startNetworkDetection(mEnableUplinkDetection, mUplinkDetectionTarget,
                        mEnableDownlinkDetection, mDownlinkDetectionTarget);
                SafeToast.show(getContext(), "网络监测开启结果: " + startReturn.toString(), Toast.LENGTH_SHORT);
            });

            mUplinkStatLayout = mStopLayout.findViewById(R.id.uplink_stat_layout);
            mDownlinkStatLayout = mStopLayout.findViewById(R.id.downlink_stat_layout);

            SubTitleLayout uplinkTitleLayout = mStopLayout.findViewById(R.id.uplink_title_bar_layout);
            uplinkTitleLayout.setTitle("上行网络");

            mUplinkNetwork = mStopLayout.findViewById(R.id.uplink_network);
            mUplinkNetwork.setTitle("网络质量");
            mUplinkNetwork.showArrow(false);

            mUplinkRTT = mStopLayout.findViewById(R.id.uplink_rtt);
            mUplinkRTT.setTitle("RTT");
            mUplinkRTT.showArrow(false);

            mUplinkLossRate = mStopLayout.findViewById(R.id.uplink_loss_rate);
            mUplinkLossRate.setTitle("丢包率");
            mUplinkLossRate.showArrow(false);

            mUplinkBandwidth = mStopLayout.findViewById(R.id.uplink_bandwidth);
            mUplinkBandwidth.setTitle("带宽");
            mUplinkBandwidth.showArrow(false);

            mUplinkJitter = mStopLayout.findViewById(R.id.uplink_jitter);
            mUplinkJitter.setTitle("抖动");
            mUplinkJitter.showArrow(false);

            SubTitleLayout downlinkTitleLayout = mStopLayout.findViewById(R.id.downlink_title_bar_layout);
            downlinkTitleLayout.setTitle("下行网络");

            mDownlinkNetwork = mStopLayout.findViewById(R.id.downlink_network);
            mDownlinkNetwork.setTitle("网络质量");
            mDownlinkNetwork.showArrow(false);

            mDownlinkRTT = mStopLayout.findViewById(R.id.downlink_rtt);
            mDownlinkRTT.setTitle("RTT");
            mDownlinkRTT.showArrow(false);

            mDownlinkLossRate = mStopLayout.findViewById(R.id.downlink_loss_rate);
            mDownlinkLossRate.setTitle("丢包率");
            mDownlinkLossRate.showArrow(false);

            mDownlinkBandwidth = mStopLayout.findViewById(R.id.downlink_bandwidth);
            mDownlinkBandwidth.setTitle("带宽");
            mDownlinkBandwidth.showArrow(false);

            mDownlinkJitter = mStopLayout.findViewById(R.id.downlink_jitter);
            mDownlinkJitter.setTitle("抖动");
            mDownlinkJitter.showArrow(false);

            TextView stopDetectionBtn = mStopLayout.findViewById(R.id.stop_detection_btn);
            stopDetectionBtn.setOnClickListener(v -> {
                switchStatus(false);
                mRTCVideo.stopNetworkDetection();
            });

            switchStatus(false);
        }

        @Override
        public void show() {
            super.show();
            mRTCVideo = RTCVideo.createRTCVideo(Utilities.getApplicationContext(),
                    Constants.APPID, mIRTCEngineEventHandler, null, null);
        }

        @Override
        public void dismiss() {
            super.dismiss();
            RTCVideo.destroyRTCVideo();
            mRTCVideo = null;
        }

        private void switchStatus(boolean isNetworkDetection) {
            mStartLayout.setVisibility(isNetworkDetection ? View.GONE : View.VISIBLE);
            mStopLayout.setVisibility(isNetworkDetection ? View.VISIBLE : View.GONE);
            mUplinkNetwork.setValue("");
            mUplinkRTT.setValue(0 + "ms");
            mUplinkLossRate.setValue(0 + "%");
            mUplinkBandwidth.setValue(0 + "kbps");
            mUplinkJitter.setValue(0 + "ms");
            mDownlinkNetwork.setValue("");
            mDownlinkRTT.setValue(0 + "ms");
            mDownlinkLossRate.setValue(0 + "%");
            mDownlinkBandwidth.setValue(0 + "kbps");
            mDownlinkJitter.setValue(0 + "ms");
        }

        private void showOrHideStats() {
            mUplinkStatLayout.setVisibility(mEnableUplinkDetection ? View.VISIBLE : View.GONE);
            mDownlinkStatLayout.setVisibility(mEnableDownlinkDetection ? View.VISIBLE : View.GONE);
        }
    }

    public static class RTMDialog extends AppCompatDialog {

        private RTCEngine mRTCEngine;
        private final IRTCEngineEventHandler mIRTCEngineEventHandler = new IRTCEngineEventHandler() {
            @Override
            public void onUserBinaryMessageReceivedOutsideRoom(String uid, ByteBuffer message) {
                super.onUserBinaryMessageReceivedOutsideRoom(uid, message);
                showMessage("接收到房间外实时消息", uid, message.array().toString());
            }

            @Override
            public void onUserMessageReceivedOutsideRoom(String uid, String message) {
                super.onUserMessageReceivedOutsideRoom(uid, message);
                showMessage("接收到房间外实时消息", uid, message);
            }

            @Override
            public void onUserMessageSendResultOutsideRoom(long msgid, int error) {
                super.onUserMessageSendResultOutsideRoom(msgid, error);
                String tip;
                if (error != 0) {
                    tip = String.format(Locale.US, "点对点消息发送失败(%d)", error);
                } else {
                    tip = "点对点消息发送成功";
                }
                new Handler(Looper.getMainLooper()).post(() ->
                        SafeToast.show(getContext(), tip, Toast.LENGTH_SHORT));
            }

            @Override
            public void onLoginResult(String uid, int error_code, int elapsed) {
                super.onLoginResult(uid, error_code, elapsed);
            }
        };

        private ValueLayout mLoginLayout;
        private ValueLayout mSendMessageLayout;
        private String mLoginUid;
        private String mSendUid;

        public RTMDialog(Context context) {
            super(context);
            supportRequestWindowFeature(Window.FEATURE_NO_TITLE);
        }

        @Override
        protected void onCreate(Bundle savedInstanceState) {
            super.onCreate(savedInstanceState);
            setContentView(R.layout.setting_rtm_message);
            getWindow().setBackgroundDrawable(new ColorDrawable(Color.WHITE));
            getWindow().setLayout(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT);

            SubTitleLayout subTitleLayout = findViewById(R.id.rtm_title);
            subTitleLayout.setTitle("房间外消息");
            mLoginLayout = findViewById(R.id.rtm_login_uid);
            mLoginLayout.setTitle("Login UserID");
            mSendMessageLayout = findViewById(R.id.rtm_send_message);
            mSendMessageLayout.setTitle("点对点消息");
            mLoginLayout.setOnClickListener(v -> {
                CommonInputDialog.IInputCallback loginCallback = new CommonInputDialog.IInputCallback() {
                    @Override
                    String getHint() {
                        return "Login userId";
                    }

                    @Override
                    String getEmptyTip() {
                        return null;
                    }

                    @Override
                    void action(String input) {
                        mLoginUid = input;
                        mLoginLayout.setValue(input);
                        mRTCEngine.logout();
                        mRTCEngine.login("", input);
                    }
                };
                CommonInputDialog dialog = new CommonInputDialog(getContext(), "Login UserID",
                        "发送房间外消息前，需要 Login\n" +
                                "Login UID 可以和 joinRoom UID 不一致",
                        Collections.singletonList(loginCallback));
                dialog.show();
            });
            mSendMessageLayout.setOnClickListener(v -> {
                CommonInputDialog.IInputCallback targetCallback = new CommonInputDialog.IInputCallback() {
                    @Override
                    String getHint() {
                        return "接收端 Login userId";
                    }

                    @Override
                    String getEmptyTip() {
                        return null;
                    }

                    @Override
                    void action(String input) {
                        mSendUid = input;
                    }
                };
                CommonInputDialog.IInputCallback messageCallback = new CommonInputDialog.IInputCallback() {
                    @Override
                    String getHint() {
                        return "消息";
                    }

                    @Override
                    String getEmptyTip() {
                        return null;
                    }

                    @Override
                    void action(String input) {
                        mRTCEngine.sendUserMessageOutsideRoom(mSendUid, input, MessageConfigReliableOrdered);
                    }
                };
                LinkedList<CommonInputDialog.IInputCallback> callbacks = new LinkedList<>();
                callbacks.add(targetCallback);
                callbacks.add(messageCallback);
                CommonInputDialog dialog = new CommonInputDialog(getContext(), "发送点对点消息",
                        "你可以使用点对点消息实现多种场景，如呼叫、邀请等。", callbacks);
                dialog.show();
            });
        }

        @Override
        public void show() {
            super.show();
            mRTCEngine = RTCEngine.createEngine(Utilities.getApplicationContext(),
                    Constants.APPID, mIRTCEngineEventHandler, null, null);
        }

        @Override
        public void dismiss() {
            super.dismiss();
            RTCEngine.destroyEngine(mRTCEngine);
        }

        private void showMessage(String title, String uid, String message) {
            new Handler(Looper.getMainLooper()).post(() -> {
                AlertDialog.Builder builder = new AlertDialog.Builder(getContext());
                builder.setCancelable(true);
                builder.setTitle(title);
                builder.setMessage(uid + ": " + message);
                final AlertDialog dialog = builder.create();
                dialog.show();
                new Handler(Looper.getMainLooper()).postDelayed(() -> {
                    if (dialog.isShowing()) {
                        dialog.dismiss();
                    }
                }, 2000);
            });
        }
    }

    @Override
    public void onStateChanged(@NonNull LifecycleOwner source, @NonNull Lifecycle.Event event) {
        if (event == Lifecycle.Event.ON_DESTROY) {
            dismiss();
        }
    }

    @Override
    public void onPause() {
        super.onPause();
        if (mHasChanged) {
            ConfigManger.getInstance().updateConfig(mVideoConfig);
        }
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        if (mLocalFitModeDialog != null) {
            mLocalFitModeDialog.dismiss();
        }
        if (mRemoteFitModeDialog != null) {
            mRemoteFitModeDialog.dismiss();
        }
    }

    public static class CommonInputDialog extends AppCompatDialog {

        private TextView mTitleTv;
        private TextView mMessageTv;
        private TextView mCancelTv;
        private TextView mConfirmTv;
        private LinearLayout mInputLayout;
        private final List<IInputCallback> mIInputCallbackList = new LinkedList<>();
        private String mTitle;
        private String mMessage;

        public CommonInputDialog(Context context, String title, String message,
                                 List<IInputCallback> callbacks) {
            super(context);
            mTitle = title;
            mMessage = message;
            if (callbacks != null) {
                mIInputCallbackList.addAll(callbacks);
            }
        }

        @Override
        protected void onCreate(Bundle savedInstanceState) {
            super.onCreate(savedInstanceState);
            setContentView(R.layout.dialog_common_input);

            mTitleTv = findViewById(R.id.common_input_title);
            mMessageTv = findViewById(R.id.common_input_message);
            mCancelTv = findViewById(R.id.common_input_cancel);
            mConfirmTv = findViewById(R.id.common_input_confirm);
            mInputLayout = findViewById(R.id.common_input_et_layout);
            for (int i = 0; i < mIInputCallbackList.size(); i++) {
                EditText editText = new EditText(getContext());
                LinearLayout.LayoutParams params = new LinearLayout.LayoutParams(
                        ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT);
                mInputLayout.addView(editText, params);

                IInputCallback callback = mIInputCallbackList.get(i);
                if (callback != null) {
                    editText.setHint(callback.getHint());
                }
            }

            mTitleTv.setText(mTitle);
            mMessageTv.setText(mMessage);

            mCancelTv.setOnClickListener(v -> dismiss());
            mConfirmTv.setOnClickListener(v -> {
                for (int i = 0; i < mIInputCallbackList.size(); i++) {
                    EditText inputEt = (EditText) mInputLayout.getChildAt(i);
                    IInputCallback callback = mIInputCallbackList.get(i);
                    if (callback != null) {
                        callback.action(inputEt.getText().toString());
                    }
                }
                dismiss();
            });
        }

        @Override
        public void dismiss() {
            super.dismiss();
            mIInputCallbackList.clear();
        }

        public static abstract class IInputCallback {

            abstract String getHint();

            abstract String getEmptyTip();

            abstract void action(String input);
        }
    }
}
