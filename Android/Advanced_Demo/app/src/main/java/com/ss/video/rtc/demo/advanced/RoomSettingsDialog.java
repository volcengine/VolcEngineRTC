package com.ss.video.rtc.demo.advanced;

import static com.ss.bytertc.engine.type.MessageConfig.MessageConfigReliableOrdered;

import android.content.Context;
import android.os.Bundle;
import android.text.TextUtils;
import android.util.Pair;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.SeekBar;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatDialog;
import androidx.fragment.app.DialogFragment;
import androidx.lifecycle.Lifecycle;
import androidx.lifecycle.LifecycleEventObserver;
import androidx.lifecycle.LifecycleOwner;

import com.ss.bytertc.engine.RTCRoom;
import com.ss.bytertc.engine.RTCVideo;
import com.ss.bytertc.engine.data.StreamIndex;
import com.ss.rtc.demo.advanced.R;
import com.ss.video.rtc.demo.advanced.entity.VideoConfigEntity;
import com.ss.video.rtc.demo.basic_module.ui.CommonListDialog;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

public class RoomSettingsDialog extends DialogFragment implements LifecycleEventObserver {
    public static final String TAG_FOR_SHOW = "RoomSettingsDialog";
    private CommonListDialog mResolutionDialog;
    private CommonListDialog mVideoFrameRateDialog;
    private View rootView;
    private VideoConfigEntity mVideoConfig;
    private boolean mHasConfigChanged;
    private CommonListDialog mLocalVideoMirrorSelectDialog;

    private RTCVideo mRTCVideo;
    private RTCRoom mRTCRoom;
    private String mSEIMessage;

    public void setConfig(RTCVideo rtcVideo, RTCRoom rtcRoom) {
        this.mRTCVideo = rtcVideo;
        this.mRTCRoom = rtcRoom;
    }

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
        rootView = inflater.inflate(R.layout.fragment_room_setting, container, false);
        ImageView backArrow = rootView.findViewById(R.id.title_bar_left_iv);
        backArrow.setImageResource(R.mipmap.back_arrow);
        backArrow.setOnClickListener(v -> dismiss());
        TextView title = rootView.findViewById(R.id.title_bar_title_tv);
        title.setText(R.string.setting);
        handleResolution();
        handleFrameRate();
        handleLocalVideoType();
        handleMessage();
        return rootView;
    }

    /**** 分辨率***/
    private void handleResolution() {
        View videoResolution = rootView.findViewById(R.id.settings_video_resolution);
        TextView vrLeftTv = videoResolution.findViewById(R.id.left_tv);
        vrLeftTv.setText(R.string.video_resolution);
        TextView vrRightTv = videoResolution.findViewById(R.id.right_tv);
        String[] resolutions = VideoConfigEntity.getResolutions();
        vrRightTv.setText(resolutions[mVideoConfig.index]);
        videoResolution.setOnClickListener(v -> {
            List<String> list = new ArrayList<>(Arrays.asList(resolutions));
            mResolutionDialog = new CommonListDialog(getActivity(), list);
            mResolutionDialog.setButtonClickListener(v1 -> mResolutionDialog.dismiss());
            mResolutionDialog.setOnItemClickListener((index, str) -> {
                mHasConfigChanged = true;
                mVideoConfig.index = index;
                vrRightTv.setText(resolutions[mVideoConfig.index]);
                setBitrate();
                mResolutionDialog.dismiss();
            });
            mResolutionDialog.show();
        });
    }

    /**** 帧率***/
    private void handleFrameRate() {
        View videoFrameRate = rootView.findViewById(R.id.settings_video_frame_rate);
        TextView vfrLeftTv = videoFrameRate.findViewById(R.id.left_tv);
        vfrLeftTv.setText(R.string.video_frame_rate);
        TextView vfrRightTv = videoFrameRate.findViewById(R.id.right_tv);

        vfrRightTv.setText(getString(R.string.frame_rate, mVideoConfig.getFrameRate()));
        videoFrameRate.setOnClickListener(v -> {
            List<String> list = new ArrayList<>(Arrays.asList(ConfigManger.getInstance().getVideoConfig().getFrameRates()));
            mVideoFrameRateDialog = new CommonListDialog(getActivity(), list);
            mVideoFrameRateDialog.setButtonClickListener(v1 -> {
                mVideoFrameRateDialog.dismiss();
            });
            mVideoFrameRateDialog.setOnItemClickListener((index, str) -> {
                mHasConfigChanged = true;
                mVideoConfig.setFrameRate(Integer.parseInt(str.trim()));
                vfrRightTv.setText(getString(R.string.frame_rate, mVideoConfig.getFrameRate()));
                mVideoFrameRateDialog.dismiss();
            });
            mVideoFrameRateDialog.show();
        });
        setBitrate();
    }

    /****设置本地视频是否镜像渲染***/
    private void handleLocalVideoType() {
        View localVideoType = rootView.findViewById(R.id.settings_local_video_type);
        TextView vfrLeftTv = localVideoType.findViewById(R.id.left_tv);
        vfrLeftTv.setText(R.string.local_video_mirror_type);
        TextView vfrRightTv = localVideoType.findViewById(R.id.right_tv);

        vfrRightTv.setText(mVideoConfig.getLocalVideoMirrorType());
        localVideoType.setOnClickListener(v -> {
            List<String> list = new ArrayList<>(Arrays.asList(ConfigManger.getInstance().getVideoConfig().getLocalVideoMirrorTypes()));
            mLocalVideoMirrorSelectDialog = new CommonListDialog(getActivity(), list);
            mLocalVideoMirrorSelectDialog.setButtonClickListener(v1 -> {
                mLocalVideoMirrorSelectDialog.dismiss();
            });
            mLocalVideoMirrorSelectDialog.setOnItemClickListener((index, str) -> {
                mHasConfigChanged = true;
                mVideoConfig.setLocalVideoMirrorType(index);
                vfrRightTv.setText(mVideoConfig.getLocalVideoMirrorType());
                mLocalVideoMirrorSelectDialog.dismiss();
            });
            mLocalVideoMirrorSelectDialog.show();
        });
    }

    /****设置码率信息***/
    private void setBitrate() {
        //初始化控件
        View videoBitRate = rootView.findViewById(R.id.settings_video_bit_rate);
        TextView vbrLeftTv = videoBitRate.findViewById(R.id.left_tv);
        vbrLeftTv.setText(R.string.video_bit_rate);
        TextView vbrRightTv = videoBitRate.findViewById(R.id.right_tv);
        SeekBar vbrSeekBar = videoBitRate.findViewById(R.id.seek_bar);
        vbrSeekBar.setOnSeekBarChangeListener(null);

        //计算正确的码率数值
        VideoConfigEntity config = ConfigManger.getInstance().getVideoConfig();
        Pair<Integer, Integer> bitRatePair = config.getBitRatePair();
        vbrSeekBar.setMax(bitRatePair.second - bitRatePair.first);
        int currentValue = config.getBitRate();
        int progress;
        int adjustValue = currentValue;
        if (currentValue < bitRatePair.first) {
            progress = 0;
            adjustValue = bitRatePair.first;
        } else if (currentValue > bitRatePair.second) {
            progress = bitRatePair.second - bitRatePair.first;
            adjustValue = bitRatePair.second;
        } else {
            progress = currentValue - bitRatePair.first;
        }
        mHasConfigChanged = true;
        mVideoConfig.setBitRate(adjustValue);
        vbrRightTv.setText(getString(R.string.bit_rate, adjustValue));
        vbrSeekBar.setProgress(progress);

        //设置码率更改回调
        vbrSeekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                mHasConfigChanged = true;
                int value = progress + bitRatePair.first;
                mVideoConfig.setBitRate(value);
                vbrRightTv.setText(getString(R.string.bit_rate, value));
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {
            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
            }
        });
    }

    private void handleMessage() {
        View seiMessage = rootView.findViewById(R.id.settings_sei_message);
        TextView seiTv = seiMessage.findViewById(R.id.left_tv);
        seiTv.setText(R.string.message_sei);
        seiMessage.setOnClickListener((v) -> {
            handleSendSEI();
        });

        View roomMessage = rootView.findViewById(R.id.settings_room_message);
        TextView roomTv = roomMessage.findViewById(R.id.left_tv);
        roomTv.setText(R.string.message_room);
        roomMessage.setOnClickListener((v) -> {
            BottomDialog bottomDialog = new BottomDialog(getActivity());
            bottomDialog.setConfig(mRTCVideo, mRTCRoom);
            bottomDialog.show();
        });
    }

    private void handleSendSEI() {
        PreJoinSettingsDialog.CommonInputDialog.IInputCallback targetCallback
                = new PreJoinSettingsDialog.CommonInputDialog.IInputCallback() {
            @Override
            String getHint() {
                return "SEI消息";
            }

            @Override
            String getEmptyTip() {
                return null;
            }

            @Override
            void action(String input) {
                mSEIMessage = input;
            }
        };
        PreJoinSettingsDialog.CommonInputDialog.IInputCallback messageCallback
                = new PreJoinSettingsDialog.CommonInputDialog.IInputCallback() {
            @Override
            String getHint() {
                return "重复次数";
            }

            @Override
            String getEmptyTip() {
                return null;
            }

            @Override
            void action(String input) {
                int count;
                try {
                    count = Integer.parseInt(input);
                } catch (Exception e) {
                    count = 0;
                }
                byte[] message = TextUtils.isEmpty(mSEIMessage) ? new byte[0] : mSEIMessage.getBytes();
                mRTCVideo.sendSEIMessage(StreamIndex.STREAM_INDEX_MAIN, message, count);
            }
        };
        LinkedList<PreJoinSettingsDialog.CommonInputDialog.IInputCallback> callbacks = new LinkedList<>();
        callbacks.add(targetCallback);
        callbacks.add(messageCallback);
        PreJoinSettingsDialog.CommonInputDialog dialog
                = new PreJoinSettingsDialog.CommonInputDialog(getContext(),
                "发送SEI消息",
                "你可以使用 SEI 信息实现多种场景，如歌词同步、布局切换等", callbacks);
        dialog.show();
    }

    @Override
    public void onPause() {
        super.onPause();
        if (mHasConfigChanged) {
            ConfigManger.getInstance().updateConfig(mVideoConfig, false);
        }
    }

    @Override
    public void onStateChanged(@NonNull LifecycleOwner source, @NonNull Lifecycle.Event event) {
        if (event == Lifecycle.Event.ON_DESTROY) {
            dismiss();
        }
    }

    @Override
    public void onDestroyView() {
        super.onDestroyView();
        if (mResolutionDialog != null) {
            mResolutionDialog.dismiss();
        }
        if (mVideoFrameRateDialog != null) {
            mVideoFrameRateDialog.dismiss();
        }
    }

    static class BottomDialog extends AppCompatDialog {

        private RTCVideo mRTCVideo;
        private RTCRoom mRTCRoom;

        public BottomDialog(Context context) {
            super(context);
        }

        public BottomDialog(Context context, int theme) {
            super(context, theme);
        }

        protected BottomDialog(Context context, boolean cancelable, OnCancelListener cancelListener) {
            super(context, cancelable, cancelListener);
        }

        @Override
        protected void onCreate(Bundle savedInstanceState) {
            super.onCreate(savedInstanceState);
            setContentView(R.layout.room_setting_message);

            View binaryMessage = findViewById(R.id.message_bottom_binary);
            if (binaryMessage != null) {
                binaryMessage.setOnClickListener((v) -> {
                    RoomMessageDialog dialog = new RoomMessageDialog(getContext());
                    dialog.setConfig(true, mRTCVideo, mRTCRoom);
                    dialog.show();
                    dismiss();
                });
            }
            View textMessage = findViewById(R.id.message_bottom_text);
            if (textMessage != null) {
                textMessage.setOnClickListener((v) -> {
                    RoomMessageDialog dialog = new RoomMessageDialog(getContext());
                    dialog.setConfig(false, mRTCVideo, mRTCRoom);
                    dialog.show();
                    dismiss();
                });
            }
        }

        public void setConfig(RTCVideo rtcVideo, RTCRoom rtcRoom) {
            this.mRTCVideo = rtcVideo;
            this.mRTCRoom = rtcRoom;
        }
    }

    static class RoomMessageDialog extends AppCompatDialog {

        private RTCVideo mRTCVideo;
        private RTCRoom mRTCRoom;
        private boolean mIsBinary = false;

        public RoomMessageDialog(Context context) {
            super(context);
        }

        public RoomMessageDialog(Context context, int theme) {
            super(context, theme);
        }

        protected RoomMessageDialog(Context context, boolean cancelable, OnCancelListener cancelListener) {
            super(context, cancelable, cancelListener);
        }

        @Override
        public void onCreate(@Nullable Bundle savedInstanceState) {
            super.onCreate(savedInstanceState);
            setContentView(R.layout.fragment_message_setting);
            ImageView backArrow = findViewById(R.id.title_bar_left_iv);
            if (backArrow != null) {
                backArrow.setImageResource(R.mipmap.back_arrow);
                backArrow.setOnClickListener(v -> dismiss());
            }

            handleP2PMessage();
            handleRoomMessage();
        }


        private void handleP2PMessage() {
            View roomMessage = findViewById(R.id.message_settings_p2p);
            if (roomMessage == null) {
                return;
            }
            TextView roomTv = roomMessage.findViewById(R.id.left_tv);
            roomTv.setText(R.string.message_setting_p2p);
            roomMessage.setOnClickListener((v) -> {
                SendP2pMessageDialog sendP2pMessageDialog = new SendP2pMessageDialog(getContext());
                sendP2pMessageDialog.setConfig(mIsBinary, mRTCVideo, mRTCRoom);
                sendP2pMessageDialog.show();
                dismiss();
            });
        }

        private void handleRoomMessage() {
            View roomMessage = findViewById(R.id.message_settings_room);
            if (roomMessage == null) {
                return;
            }
            TextView roomTv = roomMessage.findViewById(R.id.left_tv);
            roomTv.setText(R.string.message_setting_room);
            roomMessage.setOnClickListener((v) -> {
                SendRoomMessageDialog sendRoomMessageDialog = new SendRoomMessageDialog(getContext());
                sendRoomMessageDialog.setConfig(mIsBinary, mRTCVideo, mRTCRoom);
                sendRoomMessageDialog.show();
                dismiss();
            });
        }

        public void setConfig(boolean isBinary, RTCVideo rtcVideo, RTCRoom rtcRoom) {
            this.mIsBinary = isBinary;
            this.mRTCVideo = rtcVideo;
            this.mRTCRoom = rtcRoom;
        }
    }

    static class SendP2pMessageDialog extends AppCompatDialog {

        private RTCVideo mRTCVideo;
        private RTCRoom mRTCRoom;
        private boolean mIsBinary = false;

        public SendP2pMessageDialog(Context context) {
            super(context);
        }

        public SendP2pMessageDialog(Context context, int theme) {
            super(context, theme);
        }

        protected SendP2pMessageDialog(Context context, boolean cancelable, OnCancelListener cancelListener) {
            super(context, cancelable, cancelListener);
        }

        @Override
        protected void onCreate(Bundle savedInstanceState) {
            super.onCreate(savedInstanceState);
            setContentView(R.layout.dialog_send_p2p_message);
            EditText userIdEt = findViewById(R.id.p2p_user_id_et);
            EditText contentEt = findViewById(R.id.p2p_content_et);
            View send = findViewById(R.id.p2p_message_send);
            View cancel = findViewById(R.id.p2p_message_cancel);

            if (send != null) {
                send.setOnClickListener((v) -> {
                    String userId = "";
                    if (userIdEt != null) {
                        userId = userIdEt.getText().toString().trim();
                    }

                    String content = "";
                    if (contentEt != null) {
                        content = contentEt.getText().toString().trim();
                    }
                    if (mRTCVideo != null) {
                        if (mIsBinary) {
                            mRTCRoom.sendUserBinaryMessage(userId, content.getBytes(), MessageConfigReliableOrdered);
                        } else {
                            mRTCRoom.sendUserMessage(userId, content, MessageConfigReliableOrdered);
                        }
                    }
                    dismiss();
                });
            }

            if (cancel != null) {
                cancel.setOnClickListener((v) -> dismiss());
            }
        }

        public void setConfig(boolean isBinary, RTCVideo rtcEngine, RTCRoom rtcRoom) {
            this.mIsBinary = isBinary;
            this.mRTCVideo = rtcEngine;
            this.mRTCRoom = rtcRoom;
        }
    }

    static class SendRoomMessageDialog extends AppCompatDialog {

        private RTCVideo mRTCVideo;
        private RTCRoom mRTCRoom;
        private boolean mIsBinary = false;

        public SendRoomMessageDialog(Context context) {
            super(context);
        }

        public SendRoomMessageDialog(Context context, int theme) {
            super(context, theme);
        }

        protected SendRoomMessageDialog(Context context, boolean cancelable, OnCancelListener cancelListener) {
            super(context, cancelable, cancelListener);
        }

        @Override
        protected void onCreate(Bundle savedInstanceState) {
            super.onCreate(savedInstanceState);
            setContentView(R.layout.dialog_send_room_message);

            EditText contentEt = findViewById(R.id.room_content_et);
            View cancel = findViewById(R.id.room_message_cancel);
            View send = findViewById(R.id.room_message_send);

            if (send != null) {
                send.setOnClickListener((v) -> {
                    String content = "";
                    if (contentEt != null) {
                        content = contentEt.getText().toString().trim();
                    }
                    if (mRTCVideo != null) {
                        if (mIsBinary) {
                            mRTCRoom.sendRoomBinaryMessage(content.getBytes());
                        } else {
                            mRTCRoom.sendRoomMessage(content);
                        }
                    }
                    dismiss();
                });
            }

            if (cancel != null) {
                cancel.setOnClickListener((v) -> dismiss());
            }
        }

        public void setConfig(boolean isBinary, RTCVideo rtcVideo, RTCRoom rtcRoom) {
            this.mIsBinary = isBinary;
            this.mRTCVideo = rtcVideo;
            this.mRTCRoom = rtcRoom;
        }
    }
}
