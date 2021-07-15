package com.ss.video.rtc.demo.meetingrtcdemo.feature.verify;

import android.app.AlertDialog;
import android.content.Intent;
import android.graphics.Color;
import android.net.Uri;
import android.os.Bundle;
import android.text.Editable;
import android.text.InputFilter;
import android.text.TextUtils;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;

import androidx.lifecycle.Lifecycle;

import com.ss.video.rtc.demo.basic_module.acivities.BaseActivity;
import com.ss.video.rtc.demo.basic_module.adapter.TextWatcherAdapter;
import com.ss.video.rtc.demo.basic_module.utils.AppExecutors;
import com.ss.video.rtc.demo.basic_module.utils.IMEUtils;
import com.ss.video.rtc.demo.basic_module.utils.SPUtils;
import com.ss.video.rtc.demo.basic_module.utils.WindowUtils;
import com.ss.video.rtc.demo.meetingrtcdemo.R;
import com.ss.video.rtc.demo.meetingrtcdemo.common.LengthFilterWithCallback;
import com.ss.video.rtc.demo.meetingrtcdemo.core.MeetingApplication;
import com.ss.video.rtc.demo.meetingrtcdemo.core.MeetingDataManager;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.MeetingEventManager;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.RefreshUserNameEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.SocketConnectEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.UpgradeAppEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.AuditStateResult;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.LoginInfo;
import com.ss.video.rtc.demo.meetingrtcdemo.resource.Constants;

import org.greenrobot.eventbus.Subscribe;
import org.greenrobot.eventbus.ThreadMode;

import java.util.regex.Pattern;

public class VerifyActivity extends BaseActivity implements View.OnClickListener {

    public static final String NAME_INPUT_REGEX = "^[\\u4e00-\\u9fa5a-zA-Z0-9@_-]*$";

    private EditText mPhoneNumberEt;
    private TextView mConfirmTv;
    private TextView mPhoneNumberError;
    private View mRoomLayout;
    private View mToastLayout;
    private TextView mToastTv;

    private long mLastShowDisconnectMs = 0;

    private SocketConnectEvent.ConnectStatus mConnectStatus = SocketConnectEvent.ConnectStatus.DISCONNECTED;

    private final Runnable mAutoDismiss = () -> {
        if (isFinishing()) {
            return;
        }
        if (mToastLayout != null) {
            mToastLayout.setVisibility(View.GONE);
        }
    };

    private final TextWatcherAdapter mTextWatcher = new TextWatcherAdapter() {
        @Override
        public void afterTextChanged(Editable s) {
            super.afterTextChanged(s);
            setupConfirmStatus();
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_verify);
    }

    @Override
    protected void setupStatusBar() {
        WindowUtils.setLayoutFullScreen(getWindow());
    }

    @Override
    protected void onGlobalLayoutCompleted() {
        mRoomLayout = findViewById(R.id.verify_root_layout);
        mToastLayout = findViewById(R.id.verify_toast_layout);
        mToastTv = findViewById(R.id.verify_toast_text);
        mPhoneNumberEt = findViewById(R.id.verify_input_phone_number_et);
        mPhoneNumberError = findViewById(R.id.verify_input_phone_number_waring_tv);
        mConfirmTv = findViewById(R.id.verify_confirm);
        mConfirmTv.setOnClickListener(this);
        mRoomLayout.setOnClickListener(this);

        InputFilter phoneNumFilter = new LengthFilterWithCallback(18, (overflow) -> {
            if (overflow) {
                mPhoneNumberError.setVisibility(View.VISIBLE);
                mPhoneNumberError.setText(R.string.audio_input_wrong_content_waring);
            } else {
                mPhoneNumberError.setVisibility(View.INVISIBLE);
            }
        });
        InputFilter[] phoneNumFilters = new InputFilter[]{phoneNumFilter};
        mPhoneNumberEt.setFilters(phoneNumFilters);

        mPhoneNumberEt.addTextChangedListener(mTextWatcher);
        setupConfirmStatus();

        MeetingEventManager.register(this);
    }

    @Override
    public void finish() {
        super.finish();
        MeetingEventManager.unregister(this);
    }

    @Override
    public void onClick(View v) {
        if (v == mConfirmTv) {
            onClickConfirm();
        } else if (v == mRoomLayout) {
            IMEUtils.closeIME(mRoomLayout);
        }
    }

    @Override
    public void onBackPressed() {}

    private void setupConfirmStatus() {
        String phoneNum = mPhoneNumberEt.getText().toString().trim();

        boolean isPhoneMatch = Pattern.matches(NAME_INPUT_REGEX, phoneNum);
        if (isPhoneMatch) {
            mPhoneNumberError.setVisibility(View.INVISIBLE);
        } else {
            mPhoneNumberError.setText(R.string.audio_input_wrong_content_waring);
            mPhoneNumberError.setVisibility(View.VISIBLE);
        }
        if (TextUtils.isEmpty(phoneNum) || !isPhoneMatch) {
            mConfirmTv.setAlpha(0.3F);
            mConfirmTv.setEnabled(false);
        } else {
            mConfirmTv.setEnabled(true);
            mConfirmTv.setAlpha(1F);
        }
    }

    private void onClickConfirm() {
        String phoneNum = mPhoneNumberEt.getText().toString().trim();
        mConfirmTv.setEnabled(false);
        IMEUtils.closeIME(mConfirmTv);
        AppExecutors.networkIO().execute(() -> {
            LoginInfo info = MeetingDataManager.getManager().passwordFreeLogin(phoneNum);
            AppExecutors.mainThread().execute(() -> {
                mConfirmTv.setEnabled(true);
                if (info != null && !TextUtils.isEmpty(info.login_token)) {
                    MeetingDataManager.setToken(info.login_token);
                    MeetingApplication.sUserName = info.user_name;
                    MeetingApplication.sUserID = info.user_id;
                    SPUtils.putString(Constants.SP_KEY_USER_ID, info.user_id);
                    MeetingEventManager.post(new RefreshUserNameEvent(info.user_name, true));
                    VerifyActivity.this.finish();
                } else {
                    showToast("操作失败，请稍后重试");
                }
            });
        });
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
            VerifyActivity.this.startActivity(i);
        });
        dialog.show();
    }

    private void showToast(String toast) {
        mToastLayout.setVisibility(View.VISIBLE);
        mToastLayout.removeCallbacks(mAutoDismiss);
        mToastLayout.postDelayed(mAutoDismiss, 2000);
        mToastTv.setText(toast);
    }

    private void dismissToast() {
        mToastLayout.removeCallbacks(mAutoDismiss);
        mToastLayout.setVisibility(View.GONE);
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onUpgradeAppEvent(UpgradeAppEvent event) {
        openUpdateDialog(event.result);
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onSocketConnectEvent(SocketConnectEvent event) {
        if (event.status == SocketConnectEvent.ConnectStatus.CONNECTED) {
            dismissToast();
        } else {
            if (System.currentTimeMillis() - mLastShowDisconnectMs > 4000) {
                showToast("网络链接已断开，请检查设置");
                mLastShowDisconnectMs = System.currentTimeMillis();
            }
        }
        mConnectStatus = event.status;
    }
}
