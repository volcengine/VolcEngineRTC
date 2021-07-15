package com.ss.video.rtc.demo.meetingrtcdemo.feature.room;

import android.annotation.SuppressLint;
import android.content.ClipData;
import android.content.ClipboardManager;
import android.content.Context;
import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.content.res.Configuration;
import android.graphics.Color;
import android.os.Bundle;
import android.text.TextUtils;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.view.ViewTreeObserver;
import android.view.WindowManager;
import android.widget.FrameLayout;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.TextView;

import androidx.annotation.Nullable;

import com.ss.video.rtc.demo.basic_module.acivities.BaseActivity;
import com.ss.video.rtc.demo.basic_module.utils.SafeToast;
import com.ss.video.rtc.demo.basic_module.utils.Utilities;
import com.ss.video.rtc.demo.basic_module.utils.WindowUtils;
import com.ss.video.rtc.demo.meetingrtcdemo.R;
import com.ss.video.rtc.demo.meetingrtcdemo.common.MLog;
import com.ss.video.rtc.demo.meetingrtcdemo.core.MeetingDataManager;
import com.ss.video.rtc.demo.meetingrtcdemo.core.MeetingRTCManager;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.AskOpenMicEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.CameraStatusChangedEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.HostChangedEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.KickedOffEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.MeetingEndEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.MeetingEventManager;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.MicStatusChangeEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.RTCStatEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.RecordEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.RefreshRoomUserEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.RoomCloseEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.ShareScreenEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.SocketConnectEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.SpeakerStatusChangedEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.TokenExpiredEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.VolumeEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.MeetingUserInfo;
import com.ss.video.rtc.demo.meetingrtcdemo.resource.Constants;

import org.greenrobot.eventbus.Subscribe;
import org.greenrobot.eventbus.ThreadMode;

import java.util.List;

@SuppressLint("ClickableViewAccessibility")
public class RoomActivity extends BaseActivity implements View.OnClickListener {

    private static final int MAIN_MODEL_UNSET = -1;
    private static final int MAIN_MODEL_NORMAL = 0;
    private static final int MAIN_MODEL_SPEECH = 1;
    private static final int MAIN_MODEL_FULL_SCREEN = 2;

    private int mCurrentModel = MAIN_MODEL_UNSET;
    private int mScreenWidth = 0;
    private long mEnterMeetingMs;
    private long mMeetingLastMs;
    private long mLastShowDisconnectMs = 0;
    private String mMeetingId;
    private String mUserId;
    private String mUserName;
    private String mUserUniformName;
    private String mToken;

    private SocketConnectEvent.ConnectStatus mConnectStatus;

    private RoomPresenter mRoomPresenter;

    private TextView mMeetingDurationTv;
    private TextView mRTCStatTv;
    private TextView mSpeakerTv;
    private TextView mMoreFuncTv;
    private ImageView mSwitchCameraIv;
    private ImageView mLeaveMeetingIv;
    private ImageView mRecordStatusIv;
    private ImageView mMicIv;
    private ImageView mCameraIv;
    private ImageView mScreenShareIv;
    private ImageView mParticipantIv;
    private ImageView mMoreFuncIv;
    private ImageView mRecordIv;
    private ImageView mSpeakerIv;
    private ImageView mSettingIv;
    private ImageView mExpandIv;
    private View mBottomFuncExtension;
    private View mDisconnectTip;
    private FrameLayout mFullScreenContainer;
    private RelativeLayout mScreenShareStatus;

    private RoomMainLayout mRoomMainLayout;

    private boolean mIsLastLandScape = false;
    private boolean mIsLastSpeechMode = false;
    private final ViewTreeObserver.OnGlobalLayoutListener mOnGlobalLayoutListener = () -> {
        boolean isLandScape = isLandScape();
        boolean hasSomeoneScreenShare = MeetingDataManager.hasSomeoneScreenShare();
        if (isLandScape == mIsLastLandScape && hasSomeoneScreenShare == mIsLastSpeechMode) {
            return;
        }
        mDisconnectTip.bringToFront();
        mIsLastLandScape = isLandScape;
        mIsLastSpeechMode = hasSomeoneScreenShare;
        if (isLandScape) {
            toggleFullScreenModel();
        } else {
            if (hasSomeoneScreenShare) {
                toggleSpeechModel();
            } else {
                toggleNormalModel();
            }
        }
    };

    private final View.OnTouchListener mRootOnTouchListener = (v, event) -> {
        showOrHideMore(false);
        return false;
    };

    private final Runnable mDelayCheck = () -> {
        if (mConnectStatus != SocketConnectEvent.ConnectStatus.CONNECTED) {
            mRoomPresenter.leaveRoom();
            MeetingEventManager.post(new RoomCloseEvent());
            RoomActivity.this.finish();
        }
    };

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        Intent intent = getIntent();
        mMeetingId = intent.getStringExtra(Constants.EXTRA_KEY_MEETING_ID);
        mUserId = intent.getStringExtra(Constants.EXTRA_KEY_USER_ID);
        mUserName = intent.getStringExtra(Constants.EXTRA_KEY_USER_NAME);
        mUserUniformName = intent.getStringExtra(Constants.EXTRA_KEY_USER_UNIFORM_NAME);
        mToken = intent.getStringExtra(Constants.EXTRA_KEY_TOKEN);
        mMeetingLastMs = intent.getLongExtra(Constants.EXTRA_KEY_MEETING_LAST, 0);

        MeetingDataManager.startMeeting(mUserId, mUserName, mUserUniformName, mMeetingId);

        setContentView(R.layout.activity_room);
        mRoomPresenter = new RoomPresenter(this);
        mEnterMeetingMs = System.currentTimeMillis();
    }

    @Override
    protected void onGlobalLayoutCompleted() {
        super.onGlobalLayoutCompleted();

        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);

        TextView meetingTv = findViewById(R.id.room_meeting_id);
        if (mMeetingId.length() <= 6) {
            meetingTv.setText(mMeetingId);
        } else {
            meetingTv.setText(String.format("%s...%s", mMeetingId.substring(0, 3), mMeetingId.substring(mMeetingId.length() - 3)));
        }
        meetingTv.setOnLongClickListener((v) -> {
            ClipboardManager cm = (ClipboardManager) getSystemService(Context.CLIPBOARD_SERVICE);
            ClipData mClipData = ClipData.newPlainText("Label", mMeetingId);
            cm.setPrimaryClip(mClipData);
            SafeToast.show("房间号已复制");
            return true;
        });

        mMeetingDurationTv = findViewById(R.id.room_meeting_duration);
        mRTCStatTv = findViewById(R.id.room_stat);
        mSwitchCameraIv = findViewById(R.id.room_switch_camera);
        mLeaveMeetingIv = findViewById(R.id.room_leave_meeting);
        mRecordStatusIv = findViewById(R.id.room_record_status);
        mMicIv = findViewById(R.id.room_bottom_mic);
        mCameraIv = findViewById(R.id.room_bottom_camera);
        mScreenShareIv = findViewById(R.id.room_bottom_screen_share);
        mParticipantIv = findViewById(R.id.room_bottom_participants);
        mMoreFuncIv = findViewById(R.id.room_bottom_more_iv);
        mMoreFuncTv = findViewById(R.id.room_bottom_more_tv);
        mRecordIv = findViewById(R.id.room_bottom_record);
        mSpeakerIv = findViewById(R.id.room_bottom_speaker);
        mSpeakerTv = findViewById(R.id.room_bottom_speaker_tv);
        mSettingIv = findViewById(R.id.room_bottom_setting);
        mExpandIv = findViewById(R.id.room_expand_full_screen);
        mBottomFuncExtension = findViewById(R.id.layout_room_bottom_more);
        mDisconnectTip = findViewById(R.id.room_disconnect_tip);
        mFullScreenContainer = findViewById(R.id.room_full_screen_container);
        mScreenShareStatus = findViewById(R.id.room_speech_share_status);
        mRoomMainLayout = findViewById(R.id.layout_room_main);

        mScreenWidth = mRoomMainLayout.getWidth();
        mRoomMainLayout.getViewTreeObserver().addOnGlobalLayoutListener(mOnGlobalLayoutListener);
        mRoomMainLayout.setOnTouchListener(mRootOnTouchListener);

        mCameraIv.setImageResource(MeetingDataManager.getCameraStatus() ? R.drawable.camera_on : R.drawable.camera_off_red);
        mMicIv.setImageResource(MeetingDataManager.getMicStatus() ? R.drawable.mic_on : R.drawable.mic_off_red);
        mRTCStatTv.setVisibility(MeetingDataManager.sSettingsConfigEntity.enableLog ? View.VISIBLE : View.GONE);
        showOrHideMore(false);
        updateRecStatusUI();

        mSwitchCameraIv.setOnClickListener(this);
        mLeaveMeetingIv.setOnClickListener(this);
        mMicIv.setOnClickListener(this);
        mCameraIv.setOnClickListener(this);
        mScreenShareIv.setOnClickListener(this);
        mParticipantIv.setOnClickListener(this);
        mMoreFuncIv.setOnClickListener(this);
        mRecordIv.setOnClickListener(this);
        mSpeakerIv.setOnClickListener(this);
        mSettingIv.setOnClickListener(this);
        mScreenShareStatus.setOnClickListener(this);
        mDisconnectTip.setOnClickListener(this);

        mRoomPresenter.joinChannel(mToken, mMeetingId, mUserId);
        mRoomPresenter.startCountDuration();

        MeetingEventManager.register(this);
        MeetingDataManager.initRoomUsers();
    }

    @Override
    public void onBackPressed() {
        mRoomPresenter.attemptLeaveMeeting();
    }

    @Override
    protected void onResume() {
        super.onResume();
        if (MeetingDataManager.getCameraStatus()) {
            MeetingRTCManager.enableLocalVideo(true);
        }
        if (mRTCStatTv != null) {
            mRTCStatTv.setVisibility(MeetingDataManager.sSettingsConfigEntity.enableLog ? View.VISIBLE : View.GONE);
        }
    }

    @Override
    protected void onPause() {
        super.onPause();
        if (MeetingDataManager.getCameraStatus()) {
            MeetingRTCManager.enableLocalVideo(false);
        }
    }

    @Override
    public void finish() {
        super.finish();
        mRoomMainLayout.getViewTreeObserver().removeOnGlobalLayoutListener(mOnGlobalLayoutListener);
        mRoomMainLayout.setOnTouchListener(null);
        mRoomPresenter.finish();
        MeetingDataManager.endMeeting();
        MeetingEventManager.unregister(this);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
        if (requestCode == Constants.REQUEST_CODE_OF_SCREEN_SHARING) {
            MeetingDataManager.onScreenSharingIntent(resultCode, data);
        } else {
            super.onActivityResult(requestCode, resultCode, data);
        }
    }

    @Override
    public void onClick(View v) {
        if (v == mSwitchCameraIv) {
            MeetingDataManager.switchCameraType(true);
        } else if (v == mLeaveMeetingIv) {
            mRoomPresenter.attemptLeaveMeeting();
        } else if (v == mMicIv) {
            MeetingDataManager.switchMic(true);
        } else if (v == mCameraIv) {
            MeetingDataManager.switchCamera(true);
        } else if (v == mScreenShareIv) {
            mRoomPresenter.onScreenShareClick();
        } else if (v == mParticipantIv) {
            mRoomPresenter.openParticipant();
        } else if (v == mMoreFuncIv) {
            showOrHideMore(mBottomFuncExtension.getVisibility() != View.VISIBLE);
        } else if (v == mRecordIv) {
            mRoomPresenter.onRecordClick();
        } else if (v == mSpeakerIv) {
            MeetingDataManager.switchSpeaker();
        } else if (v == mSettingIv) {
            mRoomPresenter.openSettings();
        } else if (v == mExpandIv) {
            setActivityOrientation(true);
        } else if (v == mScreenShareStatus) {
            mRoomPresenter.onScreenShareClick();
        } else if (v == mDisconnectTip) {
            mDisconnectTip.setVisibility(View.GONE);
            mLastShowDisconnectMs = System.currentTimeMillis();
        }
    }

    public View getCountingView() {
        return mMeetingDurationTv;
    }

    public void updateDuration() {
        long duration = System.currentTimeMillis() - mEnterMeetingMs + mMeetingLastMs;
        long min = duration / 1000 / 60;
        long s = (duration / 1000) % 60;
        String str = "";
        if (min < 10) {
            str = str + "0";
        }
        str += min;
        str += ":";
        if (s < 10) {
            str = str + "0";
        }
        str += s;
        mMeetingDurationTv.setText(str);
    }

    public void updateVideoStatus(String uid, boolean on) {
        if (TextUtils.isEmpty(uid)) {
            return;
        }
        if (MeetingDataManager.isSelf(uid)) {
            mCameraIv.setImageResource(on ? R.drawable.camera_on : R.drawable.camera_off_red);
        }

        mRoomMainLayout.onCameraStatusChanged(uid, on);
    }

    public void updateAudioStatus(String uid, boolean on) {
        if (TextUtils.isEmpty(uid)) {
            return;
        }
        if (MeetingDataManager.isSelf(uid)) {
            mMicIv.setImageResource(on ? R.drawable.mic_on : R.drawable.mic_off_red);
        }
    }

    @SuppressLint("ClickableViewAccessibility")
    private void toggleFullScreenModel() {
        MLog.d("configurationChanged", "toggleFullScreenModel");
        if (mCurrentModel == MAIN_MODEL_FULL_SCREEN) {
            return;
        }
        mCurrentModel = MAIN_MODEL_FULL_SCREEN;
        switchFullScreen(true);

        mRoomMainLayout.clear();

        ViewGroup.LayoutParams layoutParams = new ViewGroup.LayoutParams(
                WindowUtils.getScreenWidth(this),
                WindowUtils.getScreenHeight(this));
        FullScreenLayout layout = new FullScreenLayout(this);
        layout.setLayoutParams(layoutParams);
        mFullScreenContainer.addView(layout, layoutParams);
        String uid = MeetingDataManager.getScreenShareUid();
        String host = MeetingDataManager.getHostUid();
        boolean isHost = uid != null && uid.equals(host);
        layout.bind(MeetingDataManager.getScreenShareUid(), isHost);

        layout.setOnTouchListener((v, event) -> {
            if (event.getAction() == MotionEvent.ACTION_DOWN) {
                mFullScreenContainer.removeAllViews();
                setActivityOrientation(false);
            }
            return false;
        });

        updateRecStatusUI();
    }

    private void toggleSpeechModel() {
        MLog.d("configurationChanged", "toggleSpeechModel");
        mCurrentModel = MAIN_MODEL_SPEECH;
        switchFullScreen(false);
        mFullScreenContainer.removeAllViews();

        mRoomMainLayout.bindSpeechData(MeetingDataManager.getMyUserInfo(),
                MeetingDataManager.getSecondUserInfo(),
                v -> mRoomPresenter.onScreenShareClick(),
                v -> setActivityOrientation(true));

        updateRecStatusUI();
    }

    private void toggleNormalModel() {
        MLog.d("configurationChanged", "toggleNormalModel");
        mCurrentModel = MAIN_MODEL_NORMAL;
        switchFullScreen(false);
        mFullScreenContainer.removeAllViews();

        List<MeetingUserInfo> userInfoList = MeetingDataManager.getMeetingShowingUserInfoList();
        mRoomMainLayout.bindGridData(userInfoList);
        updateRecStatusUI();
    }

    private void switchFullScreen(boolean isFullScreen) {
        WindowManager.LayoutParams lp = getWindow().getAttributes();
        if (isFullScreen) {
            lp.flags |= WindowManager.LayoutParams.FLAG_FULLSCREEN;
            getWindow().setAttributes(lp);
            getWindow().addFlags(WindowManager.LayoutParams.FLAG_LAYOUT_NO_LIMITS);
        } else {
            lp.flags &= (~WindowManager.LayoutParams.FLAG_FULLSCREEN);
            getWindow().setAttributes(lp);
            getWindow().clearFlags(WindowManager.LayoutParams.FLAG_LAYOUT_NO_LIMITS);
        }
    }

    private void setActivityOrientation(boolean setLandscape) {
        if (setLandscape) {
            if (this.getResources().getConfiguration().orientation == Configuration.ORIENTATION_PORTRAIT) {
                setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
            }
        } else {
            if (this.getResources().getConfiguration().orientation == Configuration.ORIENTATION_LANDSCAPE) {
                setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);
            }
        }
    }

    public boolean isLandScape() {
        return mScreenWidth != 0 && mRoomMainLayout.getWidth() > mScreenWidth ;
    }

    private void showOrHideMore(boolean isShow) {
        mBottomFuncExtension.setVisibility(isShow ? View.VISIBLE : View.GONE);
        mMoreFuncIv.setImageResource(isShow ? R.drawable.func_more_on : R.drawable.func_more);
        mMoreFuncTv.setTextColor(isShow ? Color.parseColor("#165DFF") : Color.WHITE);

        updateStatsLocation();
    }

    private void updateStatsLocation() {
        RelativeLayout.LayoutParams params = (RelativeLayout.LayoutParams) mRTCStatTv.getLayoutParams();
        if (params == null) {
            return;
        }
        int bottomMargin = params.bottomMargin;
        if (isLandScape()) {
            if (bottomMargin != 0) {
                params.bottomMargin = 0;
                mRTCStatTv.setLayoutParams(params);
            }
        } else {
            boolean isMoreShow = mBottomFuncExtension.getVisibility() == View.VISIBLE;
            int dp64 = (int) Utilities.dip2Px(isMoreShow ? 128 : 64);
            if (bottomMargin != dp64) {
                params.bottomMargin = dp64;
                mRTCStatTv.setLayoutParams(params);
            }
        }
    }

    private void updateRecStatusUI() {
        mRecordStatusIv.setVisibility(MeetingDataManager.isRecording() ? View.VISIBLE : View.GONE);
        mRecordIv.setImageResource(MeetingDataManager.isRecording() ? R.drawable.record_on : R.drawable.record_off);
        RelativeLayout.LayoutParams params = (RelativeLayout.LayoutParams) mRecordStatusIv.getLayoutParams();
        if (MeetingDataManager.hasSomeoneScreenShare()) {
            if (mCurrentModel == MAIN_MODEL_FULL_SCREEN) {
                params.topMargin = (int) Utilities.dip2Px(40);
            } else {
                params.topMargin = (int) Utilities.dip2Px(62) + WindowUtils.getScreenWidth(this) * 3 / 8;
            }
        } else {
            params.topMargin = (int) Utilities.dip2Px(62);
        }
        mRecordStatusIv.setLayoutParams(params);
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onRefreshRoomUserEvent(RefreshRoomUserEvent event) {
        int iconRes;
        if (MeetingDataManager.hasSomeoneScreenShare()) {
            iconRes = R.drawable.screen_share_on;
            if (mCurrentModel == MAIN_MODEL_SPEECH || mCurrentModel == -1) {
                if (isLandScape()) {
                    setActivityOrientation(false);
                } else {
                    toggleSpeechModel();
                }
            } else if (mCurrentModel == MAIN_MODEL_FULL_SCREEN) {
                if (isLandScape()) {
                    toggleFullScreenModel();
                } else {
                    setActivityOrientation(true);
                }
            }
        } else {
            if (isLandScape()) {
                setActivityOrientation(false);
            } else {
                toggleNormalModel();
            }
            iconRes = R.drawable.screen_share_off;
        }
        mScreenShareIv.setImageResource(iconRes);
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onCameraStatusChanged(CameraStatusChangedEvent event) {
        updateVideoStatus(event.uid, event.status);
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onMicStatusChanged(MicStatusChangeEvent event) {
        updateAudioStatus(event.uid, event.status);
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onSpeakerStatusChangedEvent(SpeakerStatusChangedEvent event) {
        mSpeakerIv.setImageResource(event.isSpeaker ? R.drawable.speaker : R.drawable.receiver);
        mSpeakerTv.setText(event.isSpeaker ? "扬声器" : "听筒");
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onShareScreenEvent(ShareScreenEvent event) { }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onHostChangedEvent(HostChangedEvent event) {
        mRoomMainLayout.onHostChanged(event.formerUid, event.currentUid);
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onRecordEvent(RecordEvent event) {
        updateRecStatusUI();
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onMeetingEndEvent(MeetingEndEvent event) {
        mRoomPresenter.onMeetingEnd();
        finish();
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onKickedOffEvent(KickedOffEvent event) {
        mRoomPresenter.onMeetingEnd();
        setResult(Constants.REQUEST_CODE_DUPLICATE_LOGIN);
        finish();
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onRTCStat(RTCStatEvent event) {
        mRTCStatTv.setVisibility(MeetingDataManager.sSettingsConfigEntity.enableLog ? View.VISIBLE : View.GONE);
        mRTCStatTv.setText(event.stat);
        mRTCStatTv.bringToFront();

        updateStatsLocation();
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onAskOpenMicEvent(AskOpenMicEvent event) {
        mRoomPresenter.onAskOpenMic();
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onSocketConnectEvent(SocketConnectEvent event) {
        if (event.status == SocketConnectEvent.ConnectStatus.CONNECTED) {
            mDisconnectTip.removeCallbacks(mDelayCheck);
            mDisconnectTip.setVisibility(View.GONE);
        } else {
            if (mConnectStatus == SocketConnectEvent.ConnectStatus.DISCONNECTED) {
                mDisconnectTip.removeCallbacks(mDelayCheck);
                mDisconnectTip.postDelayed(mDelayCheck, 60_000);
            }

            if (System.currentTimeMillis() - mLastShowDisconnectMs > 2000) {
                mDisconnectTip.setVisibility(View.VISIBLE);
            }
        }
        mConnectStatus = event.status;
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onVolumeEvent(VolumeEvent event) {
        mRoomMainLayout.onVolumeEvent(event.uidVolumeMap);
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onTokenExpiredEvent(TokenExpiredEvent event) {
        finish();
    }
}
