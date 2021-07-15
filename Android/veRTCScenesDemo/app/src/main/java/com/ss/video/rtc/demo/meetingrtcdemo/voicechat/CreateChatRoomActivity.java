package com.ss.video.rtc.demo.meetingrtcdemo.voicechat;

import android.content.Intent;
import android.os.Bundle;
import android.text.Editable;
import android.text.TextUtils;
import android.util.Log;
import android.view.View;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.Nullable;

import com.ss.video.rtc.demo.basic_module.acivities.BaseActivity;
import com.ss.video.rtc.demo.basic_module.adapter.TextWatcherAdapter;
import com.ss.video.rtc.demo.basic_module.utils.WindowUtils;
import com.ss.video.rtc.demo.meetingrtcdemo.R;
import com.ss.video.rtc.demo.meetingrtcdemo.core.MeetingApplication;
import com.ss.video.rtc.demo.meetingrtcdemo.core.MeetingDataManager;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.CSToastEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.MeetingEventManager;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.TokenExpiredEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.CreateJoinRoomResult;
import com.ss.video.rtc.demo.meetingrtcdemo.resource.Constants;

import org.greenrobot.eventbus.Subscribe;
import org.greenrobot.eventbus.ThreadMode;

import java.util.regex.Pattern;

public class CreateChatRoomActivity extends BaseActivity {

    public static final String INPUT_REGEX = "^[\\u4e00-\\u9fa5a-zA-Z0-9@_-]+$";
    public static final int USER_NAME_MAX_LENGTH = 18;

    private View mRoomConfirmBtn;
    private View mToastLayout;
    private TextView mToastTv;
    private EditText mRoomTitleInput;
    private EditText mUserNameInput;
    private TextView mUserNameInputError;
    private String mUserName;

    private final TextWatcherAdapter mUserNameTextWatcher = new TextWatcherAdapter() {

        @Override
        public void afterTextChanged(Editable s) {
            Log.d("afterTextChanged", s.toString());
            checkUserName(s.toString());
        }
    };

    private final Runnable mAutoDismiss = () -> {
        if (isFinishing()) {
            return;
        }
        if (mToastLayout != null) {
            mToastLayout.setVisibility(View.GONE);
        }
    };

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_create_chat_room);
    }

    @Override
    protected void onGlobalLayoutCompleted() {
        super.onGlobalLayoutCompleted();

        ImageView backArrow = findViewById(R.id.title_bar_left_iv);
        backArrow.setImageResource(R.drawable.back_arrow);
        backArrow.setOnClickListener(v -> finish());
        TextView title = findViewById(R.id.title_bar_title_tv);
        title.setText("语音沙龙");

        mToastLayout = findViewById(R.id.create_room_toast_layout);
        mToastTv = findViewById(R.id.create_room_toast_text);
        mRoomConfirmBtn = findViewById(R.id.create_chat_room_btn);
        mRoomTitleInput = findViewById(R.id.create_chat_room_title_et);
        mUserNameInput = findViewById(R.id.create_chat_room_id_et);
        mUserNameInputError = findViewById(R.id.create_chat_room_id_waring_tv);
        mUserNameInput.setText(MeetingApplication.sUserName);
        mUserNameInput.removeTextChangedListener(mUserNameTextWatcher);
        mUserNameInput.addTextChangedListener(mUserNameTextWatcher);
        mRoomConfirmBtn.setOnClickListener((v) -> {
            String roomTitle = mRoomTitleInput.getText().toString().trim();
            String userName = mUserNameInput.getText().toString().trim();
            if (TextUtils.isEmpty(roomTitle) || TextUtils.isEmpty(userName)) {
                showToast("输入不得为空");
                return;
            }
            if (userName.length() > USER_NAME_MAX_LENGTH || !Pattern.matches(INPUT_REGEX, userName)) {
                return;
            }
            VoiceChatDataManger.requestCreateRoom(roomTitle, userName);
        });

        MeetingEventManager.register(this);
    }

    @Override
    protected void setupStatusBar() {
        WindowUtils.setLayoutFullScreen(getWindow());
    }

    @Override
    public void finish() {
        super.finish();
        MeetingEventManager.unregister(this);
    }

    private void showToast(String toast) {
        mToastLayout.setVisibility(View.VISIBLE);
        mToastLayout.removeCallbacks(mAutoDismiss);
        mToastLayout.postDelayed(mAutoDismiss, 2000);
        mToastTv.setText(toast);
    }

    private void checkUserName(String newUserName) {
        if (!TextUtils.isEmpty(mUserName) && newUserName.length() > USER_NAME_MAX_LENGTH) {
            mUserNameInputError.setText(R.string.audio_input_wrong_content_waring);
            mUserNameInputError.setVisibility(View.VISIBLE);
        } else {
            if (Pattern.matches(INPUT_REGEX, newUserName)) {
                mUserNameInputError.setVisibility(View.INVISIBLE);
                MeetingApplication.sUserName = newUserName;
            } else {
                if (TextUtils.isEmpty(newUserName)) {
                    mUserNameInputError.setVisibility(View.INVISIBLE);
                } else {
                    mUserNameInputError.setVisibility(View.VISIBLE);
                    mUserNameInputError.setText(R.string.audio_input_wrong_content_waring);
                }
            }
        }
        mUserName = newUserName;
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onCreateJoinRoomResult(CreateJoinRoomResult event) {
        VoiceChatDataManger.setRoomInfo(event);
        if (event.info != null && event.users != null) {
            String roomTitle = mRoomTitleInput.getText().toString().trim();
            String userName = mUserNameInput.getText().toString().trim();
            Intent intent = new Intent(CreateChatRoomActivity.this, ChatRoomActivity.class);
            intent.putExtra(Constants.EXTRA_KEY_USER_NAME, userName);
            intent.putExtra(Constants.EXTRA_KEY_ROOM_TITLE, roomTitle);
            startActivity(intent);
            CreateChatRoomActivity.this.finish();
        } else {
            //todo 加入房间失败
        }
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onCSToastEvent(CSToastEvent event) {
        showToast(event.toast);
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onTokenExpiredEvent(TokenExpiredEvent event) {
        finish();
    }
}
