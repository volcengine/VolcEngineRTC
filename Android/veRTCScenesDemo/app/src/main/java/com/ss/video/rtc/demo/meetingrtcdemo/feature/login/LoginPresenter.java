package com.ss.video.rtc.demo.meetingrtcdemo.feature.login;

import android.content.Intent;
import android.view.View;

import com.ss.video.rtc.demo.basic_module.ui.CommonDialog;
import com.ss.video.rtc.demo.basic_module.ui.CommonExperienceDialog;
import com.ss.video.rtc.demo.basic_module.utils.AppExecutors;
import com.ss.video.rtc.demo.basic_module.utils.IMEUtils;
import com.ss.video.rtc.demo.meetingrtcdemo.R;
import com.ss.video.rtc.demo.meetingrtcdemo.core.MeetingApplication;
import com.ss.video.rtc.demo.meetingrtcdemo.core.MeetingDataManager;
import com.ss.video.rtc.demo.meetingrtcdemo.core.MeetingRTCManager;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.MeetingEventManager;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.RecordEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.RefreshUserNameEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.MeetingTokenInfo;
import com.ss.video.rtc.demo.meetingrtcdemo.feature.room.RoomActivity;
import com.ss.video.rtc.demo.meetingrtcdemo.feature.settings.SettingsActivity;
import com.ss.video.rtc.demo.meetingrtcdemo.resource.Constants;

public class LoginPresenter {

    private LoginActivity mLoginActivity;
    private boolean isJoining = false;

    public LoginPresenter(LoginActivity activity) {
        mLoginActivity = activity;
    }

    public void init() {

    }

    public void release() {
        mLoginActivity = null;
    }

    public void onClickMeeting(View view) {
        if (isJoining) {
            return;
        }
        isJoining = true;
        final String meetingId = mLoginActivity.getMeetingId();
        final String userName = mLoginActivity.getUserName();
        AppExecutors.networkIO().execute(() -> {
            final MeetingTokenInfo info = MeetingDataManager.getManager().joinMeeting(
                    userName, meetingId,
                    MeetingDataManager.getMicStatus(), MeetingDataManager.getCameraStatus());

            isJoining = false;
            if (info == null) {
                return;
            }

            if (info.info != null && info.info.record) {
                MeetingEventManager.post(new RecordEvent(true));
            }

            mLoginActivity.runOnUiThread(() -> {
                final String token = info.token;
                if (mLoginActivity != null && !mLoginActivity.isFinishing()) {
                    mLoginActivity.onJoinRoom();
                    IMEUtils.closeIME(view);

                    MeetingApplication.sUserName = userName;
                    MeetingEventManager.post(new RefreshUserNameEvent(userName, true));
                    Intent intent = new Intent(mLoginActivity, RoomActivity.class);
                    intent.putExtra(Constants.EXTRA_KEY_MEETING_ID, meetingId);
                    intent.putExtra(Constants.EXTRA_KEY_USER_ID, MeetingApplication.sUserID);
                    intent.putExtra(Constants.EXTRA_KEY_USER_NAME, userName);
                    intent.putExtra(Constants.EXTRA_KEY_TOKEN, token);
                    intent.putExtra(Constants.EXTRA_KEY_MEETING_LAST, getMeetingLastMs(info));

                    mLoginActivity.startActivityForResult(intent, Constants.ROOM_REQUEST_CODE);
                }
            });
        });
    }

    private long getMeetingLastMs(MeetingTokenInfo info) {
        if (info == null || info.info == null) {
            return 0;
        }
        long delta = info.info.now - info.info.created_at;
        return Math.max(0, delta / 1000000);
    }

    public void onClickMic() {
        MeetingDataManager.switchMic(true);
    }

    public void onClickCamera() {
        MeetingDataManager.switchCamera(true);
    }

    public void onClickSetting() {
        if (mLoginActivity != null && !mLoginActivity.isFinishing()) {
            Intent intent = new Intent(mLoginActivity, SettingsActivity.class);
            intent.putExtra(Constants.REFER_KEY, Constants.REFER_LOGIN);
            mLoginActivity.startActivity(intent);
        }
    }

    public void dealResult(int requestCode, int resultCode) {
        if (mLoginActivity != null && !mLoginActivity.isFinishing()) {
            if (requestCode == Constants.ROOM_REQUEST_CODE) {
                CommonExperienceDialog dialog = new CommonExperienceDialog(
                        mLoginActivity, MeetingRTCManager::feedback);
                dialog.show();

                if (resultCode == Constants.REQUEST_CODE_DUPLICATE_LOGIN) {
                    CommonDialog kickOutDialog = new CommonDialog(mLoginActivity);
                    kickOutDialog.setMessage(mLoginActivity.getString(R.string.login_duplicate_login));
                    kickOutDialog.setPositiveListener(v -> {
                        kickOutDialog.dismiss();
                    });
                    kickOutDialog.show();
                }
            }
        }
    }
}
