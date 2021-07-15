package com.ss.video.rtc.demo.meetingrtcdemo.voicechat;

import android.os.Bundle;
import android.text.Editable;
import android.text.InputFilter;
import android.text.TextUtils;
import android.util.Log;
import android.view.View;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;

import com.ss.video.rtc.demo.basic_module.acivities.BaseActivity;
import com.ss.video.rtc.demo.basic_module.adapter.TextWatcherAdapter;
import com.ss.video.rtc.demo.basic_module.utils.AppExecutors;
import com.ss.video.rtc.demo.basic_module.utils.IMEUtils;
import com.ss.video.rtc.demo.basic_module.utils.WindowUtils;
import com.ss.video.rtc.demo.meetingrtcdemo.R;
import com.ss.video.rtc.demo.meetingrtcdemo.core.MeetingApplication;
import com.ss.video.rtc.demo.meetingrtcdemo.core.MeetingDataManager;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.RefreshUserNameEvent;

import java.util.regex.Pattern;

public class ProfileDetailActivity extends BaseActivity implements View.OnClickListener{

    public static final String INPUT_REGEX = "^[\\u4e00-\\u9fa5a-zA-Z0-9@_-]+$";
    public static final int USER_NAME_MAX_LENGTH = 18;

    private View mRootView;
    private View mClearBtn;
    private View mToastLayout;
    private TextView mToastTv;
    private TextView mConfirmBtn;
    private EditText mUserNameEt;
    private TextView mErrorTv;
    private String mUserName;

    private final Runnable mAutoDismiss = () -> {
        if (isFinishing()) {
            return;
        }
        if (mToastLayout != null) {
            mToastLayout.setVisibility(View.GONE);
        }
    };

    private final TextWatcherAdapter mUserNameTextWatcher = new TextWatcherAdapter() {

        @Override
        public void afterTextChanged(Editable s) {
            Log.d("afterTextChanged", s.toString());
            setupInputStatus(s.toString());
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_profile_detail);
    }

    @Override
    protected void onGlobalLayoutCompleted() {
        super.onGlobalLayoutCompleted();

        ImageView backArrow = findViewById(R.id.title_bar_left_iv);
        backArrow.setImageResource(R.drawable.back_arrow);
        backArrow.setOnClickListener(v -> finish());
        TextView title = findViewById(R.id.title_bar_title_tv);
        title.setText("设置名称");
        mConfirmBtn = findViewById(R.id.title_bar_right_tv);
        mConfirmBtn.setText("确定");
        mConfirmBtn.setOnClickListener(this);

        mToastLayout = findViewById(R.id.profile_toast_layout);
        mToastTv = findViewById(R.id.profile_toast_text);
        mRootView = findViewById(R.id.profile_root_view);
        mUserNameEt = findViewById(R.id.profile_user_name_input);
        mClearBtn = findViewById(R.id.profile_user_name_clear);
        mErrorTv = findViewById(R.id.profile_user_name_error);

        mRootView.setOnClickListener(this);
        mClearBtn.setOnClickListener(this);

        mUserName = MeetingApplication.sUserName;
        mUserNameEt.setText(mUserName);
        mUserNameEt.removeTextChangedListener(mUserNameTextWatcher);
        mUserNameEt.addTextChangedListener(mUserNameTextWatcher);
    }

    @Override
    public void onClick(View v) {
        if (v == mConfirmBtn) {
            String userName = mUserNameEt.getText().toString().trim();
            if (TextUtils.isEmpty(userName)) {
                setupInputStatus(userName);
            } else {
                AppExecutors.networkIO().execute(() -> {
                    final RefreshUserNameEvent res = MeetingDataManager.getManager().changeUserName(userName);
                    AppExecutors.mainThread().execute(() -> {
                        if (ProfileDetailActivity.this.isFinishing()) {
                            return;
                        }
                        if (res != null) {
                            if (res.isSuccess) {
                                finish();
                            } else {
                                showToast(res.errorMsg);
                            }
                        } else {
                            showToast("系统繁忙，请稍后重试");
                        }
                    });
                });
            }
        } else if (v == mClearBtn) {
            mUserNameEt.setText("");
        } else if (v == mRootView) {
            IMEUtils.closeIME(mRootView);
        }
    }

    private void setupInputStatus(String newUserName) {
        if (newUserName.length() > USER_NAME_MAX_LENGTH) {
            mErrorTv.setText(R.string.login_input_meeting_id_waring);
            mErrorTv.setVisibility(View.VISIBLE);
            mConfirmBtn.setEnabled(true);
        } else {
            if (Pattern.matches(INPUT_REGEX, newUserName)) {
                mErrorTv.setVisibility(View.INVISIBLE);
                mConfirmBtn.setEnabled(true);
            } else {
                mErrorTv.setVisibility(View.VISIBLE);
                mErrorTv.setText(R.string.audio_input_wrong_content_waring);
                mConfirmBtn.setEnabled(false);
            }
        }
        mUserName = newUserName;
    }

    private void showToast(String toast) {
        mToastLayout.setVisibility(View.VISIBLE);
        mToastLayout.removeCallbacks(mAutoDismiss);
        mToastLayout.postDelayed(mAutoDismiss, 2000);
        mToastTv.setText(toast);
    }

    @Override
    protected void setupStatusBar() {
        WindowUtils.setLayoutFullScreen(getWindow());
    }
}
