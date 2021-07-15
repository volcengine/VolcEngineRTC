package com.ss.video.rtc.demo.meetingrtcdemo.feature.settings;

import android.content.Intent;
import android.os.Bundle;
import android.text.TextUtils;
import android.util.Pair;
import android.view.View;
import android.widget.ImageView;
import android.widget.Switch;
import android.widget.TextView;

import androidx.annotation.Nullable;

import com.ss.video.rtc.demo.basic_module.acivities.BaseActivity;
import com.ss.video.rtc.demo.basic_module.ui.CommonListSettingDialog;
import com.ss.video.rtc.demo.basic_module.ui.CommonSeekbarSettingDialog;
import com.ss.video.rtc.demo.meetingrtcdemo.R;
import com.ss.video.rtc.demo.meetingrtcdemo.core.MeetingDataManager;
import com.ss.video.rtc.demo.meetingrtcdemo.core.MeetingRTCManager;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.MeetingEndEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.MeetingEventManager;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.RoomCloseEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.TokenExpiredEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.SettingsConfigEntity;
import com.ss.video.rtc.demo.meetingrtcdemo.feature.history.HistoryActivity;
import com.ss.video.rtc.demo.meetingrtcdemo.resource.Constants;
import com.ss.video.rtc.engine.VideoStreamDescription;

import org.greenrobot.eventbus.Subscribe;
import org.greenrobot.eventbus.ThreadMode;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class SettingsActivity extends BaseActivity {

    private String mRefer = "";
    private SettingsConfigEntity mOriginConfigEntity;
    private SettingsConfigEntity mCurrentConfigEntity;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        Intent intent = getIntent();
        mRefer = intent.getStringExtra(Constants.REFER_KEY);
        mOriginConfigEntity = MeetingDataManager.sSettingsConfigEntity;
        mCurrentConfigEntity = mOriginConfigEntity.deepCopy();
        setContentView(R.layout.activity_settings);
    }

    @Override
    protected void onGlobalLayoutCompleted() {
        super.onGlobalLayoutCompleted();

        ImageView backArrow = findViewById(R.id.title_bar_left_iv);
        backArrow.setImageResource(R.drawable.back_arrow);
        backArrow.setOnClickListener(v -> finish());
        TextView title = findViewById(R.id.title_bar_title_tv);
        title.setText(R.string.settings_title);

        setResolution();
        setFrameRate();
        setBitRate();
        setScreenResolution();
        setScreenFrameRate();
        setScreenBitRate();
        setRealTimeStat();
        setAllHistory();
        setMyHistory();

        MeetingEventManager.register(this);
    }

    @Override
    public void finish() {
        super.finish();
        MeetingEventManager.unregister(this);
        if (mCurrentConfigEntity != mOriginConfigEntity) {
            VideoStreamDescription description = new VideoStreamDescription();
            description.videoSize = mCurrentConfigEntity.getResolution();
            description.frameRate = mCurrentConfigEntity.getFrameRate();
            description.maxKbps = mCurrentConfigEntity.getBitRate();
            MeetingRTCManager.setVideoProfiles(new VideoStreamDescription[]{description});
        }
        MeetingDataManager.sSettingsConfigEntity = mCurrentConfigEntity;
    }

    public void setResolution() {
        View videoResolution = findViewById(R.id.settings_video_resolution);
        TextView vrLeftTv = videoResolution.findViewById(R.id.left_tv);
        vrLeftTv.setText(R.string.settings_video_resolution);
        TextView vrRightTv = videoResolution.findViewById(R.id.right_tv);
        String[] resolutions = mCurrentConfigEntity.getResolutions();
        vrRightTv.setText(resolutions[mCurrentConfigEntity.index]);
        videoResolution.setOnClickListener(v -> {
            List<String> list = new ArrayList<>(Arrays.asList(resolutions));
            CommonListSettingDialog dialog = new CommonListSettingDialog(
                    SettingsActivity.this, list, mCurrentConfigEntity.index, "分辨率",
                    new CommonListSettingDialog.CommonListDialogListener() {
                @Override
                public void onConfirmClick(int index, String str) {
                    mCurrentConfigEntity.index = index;
                    vrRightTv.setText(resolutions[mCurrentConfigEntity.index]);
                    setBitRate();
                }

                @Override
                public void onItemClick(int index, String str) {

                }
            });
            dialog.show();
        });
    }

    public void setFrameRate() {
        View videoFrameRate = findViewById(R.id.settings_video_frame_rate);
        TextView vfrLeftTv = videoFrameRate.findViewById(R.id.left_tv);
        vfrLeftTv.setText(R.string.settings_video_frame_rate);
        TextView vfrRightTv = videoFrameRate.findViewById(R.id.right_tv);
        int frameRate = mCurrentConfigEntity.getFrameRate();
        vfrRightTv.setText(getString(R.string.settings_frame_rate, frameRate));
        videoFrameRate.setOnClickListener(v -> {
            List<String> list = new ArrayList<>(Arrays.asList(mCurrentConfigEntity.getFrameRates()));
            int index = 0;
            for (int i = 0; i < list.size(); i++) {
                if (TextUtils.equals(list.get(i), frameRate + "")) {
                    index = i;
                    break;
                }
            }
            CommonListSettingDialog dialog = new CommonListSettingDialog(
                    SettingsActivity.this, list, index, "帧率",
                    new CommonListSettingDialog.CommonListDialogListener() {
                @Override
                public void onConfirmClick(int index, String str) {
                    mCurrentConfigEntity.setFrameRate(Integer.parseInt(list.get(index)));
                    vfrRightTv.setText(getString(R.string.settings_frame_rate,
                            mCurrentConfigEntity.getFrameRate()));
                }

                @Override
                public void onItemClick(int index, String str) {

                }
            });
            dialog.show();
        });
    }

    public void setBitRate() {
        View videoBitRate = findViewById(R.id.settings_video_bit_rate);
        TextView vbrLeftTv = videoBitRate.findViewById(R.id.left_tv);
        vbrLeftTv.setText(R.string.settings_video_bit_rate);
        TextView vbrRightTv = videoBitRate.findViewById(R.id.right_tv);

        Pair<Integer, Integer> bitRatePair = mCurrentConfigEntity.getBitRatePair();
        int currentValue = mCurrentConfigEntity.getBitRate();
        int adjustValue = currentValue;
        if (currentValue < bitRatePair.first) {
            adjustValue = bitRatePair.first;
        } else if (currentValue > bitRatePair.second) {
            adjustValue = bitRatePair.second;
        }
        mCurrentConfigEntity.setBitRate(adjustValue);
        vbrRightTv.setText(getString(R.string.settings_bit_rate, adjustValue));

        videoBitRate.setOnClickListener(v -> {
            CommonSeekbarSettingDialog dialog = new CommonSeekbarSettingDialog(
                    SettingsActivity.this, bitRatePair.first, bitRatePair.second,
                    mCurrentConfigEntity.getBitRate(), "码率", "Kbps",
                    new CommonSeekbarSettingDialog.CommonSeekbarDialogListener() {
                @Override
                public void onConfirmClick(int value) {
                    mCurrentConfigEntity.setBitRate(value);
                    vbrRightTv.setText(getString(R.string.settings_bit_rate, value));
                }

                @Override
                public void onValueChanged(int value) {

                }
            }
            );
            dialog.show();
        });
    }

    public void setRealTimeStat() {
        View videoRealTimeLog = findViewById(R.id.settings_video_log);
        TextView vrtlLeftTv = videoRealTimeLog.findViewById(R.id.left_tv);
        vrtlLeftTv.setText(R.string.settings_video_log);
        Switch vrtlSwitch = videoRealTimeLog.findViewById(R.id.switch_lg);
        vrtlSwitch.setChecked(mCurrentConfigEntity.enableLog);
        vrtlSwitch.setOnCheckedChangeListener((buttonView, isChecked) -> mCurrentConfigEntity.enableLog = isChecked);
    }

    public void setScreenResolution() {
        View videoResolution = findViewById(R.id.settings_screen_resolution);
        TextView vrLeftTv = videoResolution.findViewById(R.id.left_tv);
        vrLeftTv.setText(R.string.settings_screen_resolution);
        TextView vrRightTv = videoResolution.findViewById(R.id.right_tv);
        String[] resolutions = mCurrentConfigEntity.getResolutions();
        vrRightTv.setText(resolutions[mCurrentConfigEntity.screenIndex]);
        videoResolution.setOnClickListener(v -> {
            List<String> list = new ArrayList<>(Arrays.asList(resolutions));
            CommonListSettingDialog dialog = new CommonListSettingDialog(
                    SettingsActivity.this, list, mCurrentConfigEntity.screenIndex, "屏幕共享分辨率",
                    new CommonListSettingDialog.CommonListDialogListener() {
                        @Override
                        public void onConfirmClick(int index, String str) {
                            mCurrentConfigEntity.screenIndex = index;
                            vrRightTv.setText(resolutions[mCurrentConfigEntity.screenIndex]);
                        }

                        @Override
                        public void onItemClick(int index, String str) {

                        }
                    });
            dialog.show();
        });
    }

    public void setScreenFrameRate() {
        View videoFrameRate = findViewById(R.id.settings_screen_frame_rate);
        TextView vfrLeftTv = videoFrameRate.findViewById(R.id.left_tv);
        vfrLeftTv.setText(R.string.settings_screen_frame_rate);
        TextView vfrRightTv = videoFrameRate.findViewById(R.id.right_tv);
        int frameRate = mCurrentConfigEntity.getScreenFrameRate();
        vfrRightTv.setText(getString(R.string.settings_frame_rate, frameRate));
        videoFrameRate.setOnClickListener(v -> {
            List<String> list = new ArrayList<>(Arrays.asList(mCurrentConfigEntity.getFrameRates()));
            int index = 0;
            for (int i = 0; i < list.size(); i++) {
                if (TextUtils.equals(list.get(i), frameRate + "")) {
                    index = i;
                    break;
                }
            }
            CommonListSettingDialog dialog = new CommonListSettingDialog(
                    SettingsActivity.this, list, index, "屏幕共享帧率",
                    new CommonListSettingDialog.CommonListDialogListener() {
                        @Override
                        public void onConfirmClick(int index, String str) {
                            mCurrentConfigEntity.setScreenFrameRate(Integer.parseInt(list.get(index)));
                            vfrRightTv.setText(getString(R.string.settings_frame_rate,
                                    mCurrentConfigEntity.getScreenFrameRate()));
                        }

                        @Override
                        public void onItemClick(int index, String str) {

                        }
                    });
            dialog.show();
        });
    }

    public void setScreenBitRate() {
        View videoBitRate = findViewById(R.id.settings_screen_bit_rate);
        TextView vbrLeftTv = videoBitRate.findViewById(R.id.left_tv);
        vbrLeftTv.setText(R.string.settings_screen_bit_rate);
        TextView vbrRightTv = videoBitRate.findViewById(R.id.right_tv);

        Pair<Integer, Integer> bitRatePair = mCurrentConfigEntity.getScreenBitRatePair();
        int currentValue = mCurrentConfigEntity.getScreenBitRate();
        int adjustValue = currentValue;
        if (currentValue < bitRatePair.first) {
            adjustValue = bitRatePair.first;
        } else if (currentValue > bitRatePair.second) {
            adjustValue = bitRatePair.second;
        }
        mCurrentConfigEntity.setScreenBitRate(adjustValue);
        vbrRightTv.setText(getString(R.string.settings_bit_rate, adjustValue));

        videoBitRate.setOnClickListener(v -> {
            CommonSeekbarSettingDialog dialog = new CommonSeekbarSettingDialog(
                    SettingsActivity.this, bitRatePair.first, bitRatePair.second,
                    mCurrentConfigEntity.getScreenBitRate(), "屏幕共享码率", "Kbps",
                    new CommonSeekbarSettingDialog.CommonSeekbarDialogListener() {
                        @Override
                        public void onConfirmClick(int value) {
                            mCurrentConfigEntity.setScreenBitRate(value);
                            vbrRightTv.setText(getString(R.string.settings_bit_rate, value));
                        }

                        @Override
                        public void onValueChanged(int value) {

                        }
                    }
            );
            dialog.show();
        });
    }

    public void setAllHistory() {
        View historyMeetings = findViewById(R.id.settings_history_meetings);
        TextView historyMeetingsTv = historyMeetings.findViewById(R.id.left_tv);
        historyMeetingsTv.setText(R.string.settings_view_history_meetings);
        historyMeetings.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(SettingsActivity.this, HistoryActivity.class);
                intent.putExtra(Constants.REFER_KEY, mRefer);
                intent.putExtra(Constants.EXTRA_KEY_VIEW_TYPE, Constants.EXTRA_VIEW_TYPE_ALL);
                startActivity(intent);
            }
        });
    }

    public void setMyHistory() {
        View historyMeetings = findViewById(R.id.settings_my_history_meetings);
        TextView historyMeetingsTv = historyMeetings.findViewById(R.id.left_tv);
        historyMeetingsTv.setText(R.string.settings_view_my_history_meetings);
        historyMeetings.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(SettingsActivity.this, HistoryActivity.class);
                intent.putExtra(Constants.REFER_KEY, mRefer);
                intent.putExtra(Constants.EXTRA_KEY_VIEW_TYPE, Constants.EXTRA_VIEW_TYPE_MINE);
                startActivity(intent);
            }
        });
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onMeetingEndEvent(MeetingEndEvent endEvent) {
        if (Constants.REFER_ROOM.equals(mRefer)) {
            finish();
        }
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onRoomCloseEvent(RoomCloseEvent event) {
        if (Constants.REFER_ROOM.equals(mRefer)) {
            finish();
        }
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onTokenExpiredEvent(TokenExpiredEvent event) {
        if (Constants.REFER_ROOM.equals(mRefer)) {
            finish();
        }
    }
}
