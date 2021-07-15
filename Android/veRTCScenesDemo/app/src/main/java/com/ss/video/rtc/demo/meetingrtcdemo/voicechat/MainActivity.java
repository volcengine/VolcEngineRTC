package com.ss.video.rtc.demo.meetingrtcdemo.voicechat;

import android.app.AlertDialog;
import android.content.Intent;
import android.graphics.Color;
import android.net.Uri;
import android.os.Bundle;
import android.text.TextUtils;
import android.util.Log;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.lifecycle.Lifecycle;

import com.ss.video.rtc.demo.basic_module.acivities.BaseActivity;
import com.ss.video.rtc.demo.basic_module.utils.AppExecutors;
import com.ss.video.rtc.demo.basic_module.utils.SPUtils;
import com.ss.video.rtc.demo.basic_module.utils.WindowUtils;
import com.ss.video.rtc.demo.meetingrtcdemo.R;
import com.ss.video.rtc.demo.meetingrtcdemo.core.MeetingApplication;
import com.ss.video.rtc.demo.meetingrtcdemo.core.MeetingDataManager;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.MeetingEventManager;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.RefreshUserNameEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.SocketConnectEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.TokenExpiredEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.UpgradeAppEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.AuditStateResult;
import com.ss.video.rtc.demo.meetingrtcdemo.feature.login.LoginActivity;
import com.ss.video.rtc.demo.meetingrtcdemo.feature.verify.VerifyActivity;
import com.ss.video.rtc.demo.meetingrtcdemo.resource.Constants;
import com.ss.video.rtc.engine.RtcEngine;

import org.greenrobot.eventbus.Subscribe;
import org.greenrobot.eventbus.ThreadMode;

public class MainActivity extends BaseActivity implements View.OnClickListener {

    private View mEntranceLayout;
    private View mProfileLayout;
    private View mMeetingEntranceBtn;
    private View mChatEntranceBtn;
    private View mUserName;
    private View mPrivacyAgreement;
    private View mServiceAgreement;
    private View mDisclaimer;
    private TextView mMainPageTv;
    private TextView mProfileTv;
    private TextView mUserNamePrefix;
    private TextView mUserNameTv;
    private ImageView mMainPageIv;
    private ImageView mProfileIv;

    private boolean mVerifiedToken = false;
    private boolean mVerifyingToken = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        MeetingDataManager.init();
        MeetingDataManager.getManager();

        String token = SPUtils.getString(Constants.SP_KEY_TOKEN, "");
        if (TextUtils.isEmpty(token)) {
            mVerifiedToken = true;
            mVerifyingToken = true;
            Intent intent = new Intent(this, VerifyActivity.class);
            startActivity(intent);
        }
    }

    @Override
    protected void onGlobalLayoutCompleted() {
        super.onGlobalLayoutCompleted();
        mEntranceLayout = findViewById(R.id.layout_main_page_entrance);
        mProfileLayout = findViewById(R.id.layout_main_page_profile);
        mMeetingEntranceBtn = findViewById(R.id.meeting_entrance);
        mChatEntranceBtn = findViewById(R.id.voice_chat_entrance);
        mMainPageTv = findViewById(R.id.main_page_txt);
        mProfileTv = findViewById(R.id.profile_txt);
        mMainPageIv = findViewById(R.id.main_page_btn);
        mProfileIv = findViewById(R.id.profile_btn);
        mUserNamePrefix = findViewById(R.id.profile_user_avatar);

        mUserName = findViewById(R.id.profile_user_name);
        TextView userNameLeftTv = mUserName.findViewById(R.id.left_tv);
        userNameLeftTv.setText("用户名");
        mUserNameTv = mUserName.findViewById(R.id.right_tv);

        mPrivacyAgreement = findViewById(R.id.profile_privacy_agreement);
        TextView privacyAgreementLeftTv = mPrivacyAgreement.findViewById(R.id.left_tv);
        privacyAgreementLeftTv.setText("隐私协议");

        mServiceAgreement = findViewById(R.id.profile_service_agreement);
        TextView serviceAgreementLeftTv = mServiceAgreement.findViewById(R.id.left_tv);
        serviceAgreementLeftTv.setText("服务协议");

        mDisclaimer = findViewById(R.id.profile_disclaimer);
        TextView disclaimerLeftTv = mDisclaimer.findViewById(R.id.left_tv);
        disclaimerLeftTv.setText("免责声明");

        View demoVersion = findViewById(R.id.profile_demo_version);
        TextView demoVersionLeftTv = demoVersion.findViewById(R.id.left_tv);
        demoVersionLeftTv.setText("Demo版本");
        TextView demoVersionRightTv = demoVersion.findViewById(R.id.right_tv);
        demoVersionRightTv.setText("v2.1.0");

        View sdkVersion = findViewById(R.id.profile_sdk_version);
        TextView sdkVersionLeftTv = sdkVersion.findViewById(R.id.left_tv);
        sdkVersionLeftTv.setText("SDK版本");
        TextView sdkVersionRightTv = sdkVersion.findViewById(R.id.right_tv);
        sdkVersionRightTv.setText(RtcEngine.getSdkVersion());

        findViewById(R.id.profile_exit_login).setOnClickListener((v) -> {
            onTokenExpiredEvent(new TokenExpiredEvent());
        });

        mMeetingEntranceBtn.setOnClickListener(this);
        mChatEntranceBtn.setOnClickListener(this);
        mMainPageIv.setOnClickListener(this);
        mProfileIv.setOnClickListener(this);
        mUserName.setOnClickListener(this);
        mPrivacyAgreement.setOnClickListener(this);
        mServiceAgreement.setOnClickListener(this);
        mDisclaimer.setOnClickListener(this);

        switchMainLayout(true);

        setUserName();
        MeetingEventManager.register(this);
    }

    @Override
    protected void setupStatusBar() {
        WindowUtils.setLayoutFullScreen(getWindow());
    }

    @Override
    public void onClick(View v) {
        if (v == mMeetingEntranceBtn) {
            startActivity(new Intent(this, LoginActivity.class));
        } else if (v == mChatEntranceBtn) {
            startActivity(new Intent(this, ChatRoomListActivity.class));
        } else if (v == mMainPageIv) {
            switchMainLayout(true);
        } else if (v == mProfileIv) {
            switchMainLayout(false);
        } else if (v == mUserName) {
            startActivity(new Intent(this, ProfileDetailActivity.class));
        } else if (v == mPrivacyAgreement) {
            openBrowser("https://www.volcengine.com/docs/6348/68918");
        } else if (v == mServiceAgreement) {
            openBrowser("https://www.volcengine.com/docs/6348/68917");
        } else if (v == mDisclaimer) {
            openBrowser("https://www.volcengine.com/docs/6348/68916");
        }
    }

    @Override
    protected void onResume() {
        super.onResume();
        setUserName();
    }

    @Override
    public void finish() {
        super.finish();
        MeetingEventManager.unregister(this);
    }

    private void setUserName() {
        String userNameStr = MeetingApplication.sUserName;

        if (mUserNameTv != null) {
            mUserNameTv.setText(userNameStr);
        }
        if (!TextUtils.isEmpty(userNameStr) && mUserNamePrefix != null) {
            mUserNamePrefix.setText(MeetingApplication.sUserName.substring(0, 1));
        }
    }

    private void switchMainLayout(boolean isEntrance) {
        if (isEntrance) {
            mEntranceLayout.setVisibility(View.VISIBLE);
            mProfileLayout.setVisibility(View.GONE);
            mMainPageIv.setImageResource(R.drawable.main_page_selected);
            mProfileIv.setImageResource(R.drawable.profile_unselected);
            mMainPageTv.setTextColor(Color.parseColor("#4080FF"));
            mProfileTv.setTextColor(Color.parseColor("#86909C"));
        } else {
            mEntranceLayout.setVisibility(View.GONE);
            mProfileLayout.setVisibility(View.VISIBLE);
            mMainPageIv.setImageResource(R.drawable.main_page_unselected);
            mProfileIv.setImageResource(R.drawable.profile_selected);
            mMainPageTv.setTextColor(Color.parseColor("#86909C"));
            mProfileTv.setTextColor(Color.parseColor("#4080FF"));
        }
    }

    public void openBrowser(String url) {
        Intent i = new Intent(Intent.ACTION_VIEW);
        i.setData(Uri.parse(url));
        startActivity(i);
    }

    private void openUpdateDialog(AuditStateResult result) {
        if (getLifecycle().getCurrentState() != Lifecycle.State.RESUMED) {
            return;
        }
        AlertDialog.Builder builder = new AlertDialog.Builder(this, R.style.transparentDialog);
        View view = getLayoutInflater().inflate(R.layout.layout_verify_upgrade, null);
        builder.setView(view);
        TextView cancel = view.findViewById(R.id.verify_upgrade_dialog_cancel);
        TextView confirm = view.findViewById(R.id.verify_upgrade_dialog_confirm);
        builder.setCancelable(true);
        AlertDialog dialog = builder.create();
        cancel.setOnClickListener((d) -> dialog.dismiss());
        confirm.setOnClickListener(v -> {
            Intent i = new Intent(Intent.ACTION_VIEW);
            i.setData(Uri.parse(result.url));
            MainActivity.this.startActivity(i);
        });
        dialog.show();
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onUpgradeAppEvent(UpgradeAppEvent event) {
        openUpdateDialog(event.result);
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onRefreshUserNameEvent(RefreshUserNameEvent event) {
        if (event.isSuccess) {
            MeetingApplication.sUserName = event.userName;
            SPUtils.putString(Constants.SP_KEY_USER_NAME, event.userName);
            setUserName();
        }
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onSocketConnectEvent(SocketConnectEvent event) {
        if (mVerifiedToken) {
            return;
        }
        if (mVerifyingToken) {
            return;
        }
        if (TextUtils.isEmpty(MeetingDataManager.getToken())) {
            return;
        }
        if (event.status == SocketConnectEvent.ConnectStatus.CONNECTED) {
            mVerifyingToken = true;
            mVerifiedToken = false;
            AppExecutors.networkIO().execute(() -> {
                mVerifiedToken = true;
                mVerifyingToken = false;
                int code = MeetingDataManager.getManager().verifyLoginToken(MeetingDataManager.getToken());
                if (code != 200) {
                    AppExecutors.mainThread().execute(() -> {
                        Intent intent = new Intent(this, VerifyActivity.class);
                        startActivity(intent);
                    });
                }
            });
        }
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onTokenExpiredEvent(TokenExpiredEvent event) {
        switchMainLayout(true);
        SPUtils.putString(Constants.SP_KEY_USER_ID, "");
        SPUtils.putString(Constants.SP_KEY_USER_NAME, "");
        SPUtils.putString(Constants.SP_KEY_TOKEN, "");

        Intent intent = new Intent(this, VerifyActivity.class);
        intent.setFlags(Intent.FLAG_ACTIVITY_SINGLE_TOP);
        startActivity(intent);
    }
}
