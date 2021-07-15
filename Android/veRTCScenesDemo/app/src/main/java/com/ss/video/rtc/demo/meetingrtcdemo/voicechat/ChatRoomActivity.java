package com.ss.video.rtc.demo.meetingrtcdemo.voicechat;

import android.Manifest;
import android.app.AlertDialog;
import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.text.TextUtils;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.core.content.ContextCompat;
import androidx.recyclerview.widget.GridLayoutManager;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.ss.video.rtc.base.utils.JsonUtils;
import com.ss.video.rtc.demo.basic_module.acivities.BaseActivity;
import com.ss.video.rtc.demo.basic_module.ui.CommonDialog;
import com.ss.video.rtc.demo.basic_module.utils.WindowUtils;
import com.ss.video.rtc.demo.meetingrtcdemo.R;
import com.ss.video.rtc.demo.meetingrtcdemo.common.MLog;
import com.ss.video.rtc.demo.meetingrtcdemo.core.MeetingApplication;
import com.ss.video.rtc.demo.meetingrtcdemo.core.MeetingRTCManager;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.CSHostChangeEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.CSInviteMicEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.CSJoinMeetingEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.CSLeaveMeetingEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.CSMeetingEndEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.CSMicOffEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.CSMicOnEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.CSMuteMicEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.CSRaiseHandsMicEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.CSToastEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.CSUnmuteMicEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.MeetingEventManager;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.RTCVolumeEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.SocketConnectEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.TokenExpiredEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.CreateJoinRoomResult;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.MeetingRoomInfo;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.MeetingUserInfo;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.UserStatus;
import com.ss.video.rtc.demo.meetingrtcdemo.resource.Constants;
import com.ss.video.rtc.engine.handler.IRtcEngineEventHandler;

import org.greenrobot.eventbus.Subscribe;
import org.greenrobot.eventbus.ThreadMode;

import java.util.LinkedList;
import java.util.List;

import static android.content.pm.PackageManager.PERMISSION_GRANTED;

public class ChatRoomActivity extends BaseActivity {
    private final int mHighLightColor = Color.parseColor("#4080FF");
    private final int mNormalColor = Color.parseColor("#86909C");

    private ChatRoomAdapter mChatRoomAdapter;
    private ChatRoomChatAdapter mChatRoomChatAdapter;

    private View mToastLayout;
    private View mMuteLocalLayout;
    private TextView mToastTv;
    private TextView mRoomIdTv;
    private TextView mDurationTv;
    private TextView mMicStatusTv;
    private TextView mRaiseHandTv;
    private ImageView mRaiseHandIv;
    private ImageView mMicStatusIv;
    private ImageView mAudioStatsIv;
    private RecyclerView mChatRv;

    private long mLastTs = 0;
    private long mEnterTs = 0;

    private String mUserId = "";
    private String mHostUserId = "";
    private boolean mIsSpeaker = false;
    private boolean mIsRaiseDialogShowing = false;
    private boolean mIsRaiseHand = false;
    private boolean mIsSomeoneRaiseHand = false;
    private long mLastShowDisconnectMs = 0;
    private boolean mIsOpen = true;

    private SocketConnectEvent.ConnectStatus mConnectStatus;

    private final ChatRaisingDialog.UserOptionCallback mUserOptionCallback = VoiceChatDataManger::onUserOption;

    private final Runnable mAutoDismiss = () -> {
        if (isFinishing()) {
            return;
        }
        if (mToastLayout != null) {
            mToastLayout.setVisibility(View.GONE);
        }
    };

    private final Runnable mNetWorkRunnable = () -> {
        if (isFinishing()) {
            return;
        }
        if (mConnectStatus != SocketConnectEvent.ConnectStatus.CONNECTED) {
            ChatRoomActivity.this.leaveRoom();
            ChatRoomActivity.this.finish();
        }
    };

    private final Runnable mDurationCounting = new Runnable() {
        @Override
        public void run() {
            if (!isFinishing()) {
                updateDuration();
                if (mDurationTv != null) {
                    mDurationTv.postDelayed(mDurationCounting, 500);
                }
            }
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_chat_room);

        requestPermissions(Manifest.permission.RECORD_AUDIO);
    }

    @Override
    protected void onGlobalLayoutCompleted() {
        super.onGlobalLayoutCompleted();

        Intent intent = getIntent();
        boolean isCreateRoom = intent.getBooleanExtra(Constants.EXTRA_KEY_IS_CREATE_ROOM, true);
        String roomId = intent.getStringExtra(Constants.EXTRA_KEY_MEETING_ID);
        String roomTitle = intent.getStringExtra(Constants.EXTRA_KEY_ROOM_TITLE);
        String userName = MeetingApplication.sUserName;

        mUserId = VoiceChatDataManger.getUid();

        ImageView leaveBtn = findViewById(R.id.chat_room_leave);
        leaveBtn.setOnClickListener(v -> attemptLeaveRoom());
        mRoomIdTv = findViewById(R.id.chat_room_id);
        mRoomIdTv.setText(roomId);
        mDurationTv = findViewById(R.id.chat_room_duration);
        mDurationTv.setText("00:00");
        TextView prefix = findViewById(R.id.chat_room_host_prefix);
        if (!TextUtils.isEmpty(userName)) {
            prefix.setText(userName.substring(0, 1));
        }

        mMuteLocalLayout = findViewById(R.id.voice_chat_room_mute_local_layout);
        mMicStatusIv = findViewById(R.id.voice_chat_room_mute_local_btn);
        mMicStatusTv = findViewById(R.id.voice_chat_room_mute_local_txt);
        mMicStatusIv.setOnClickListener((v) -> switchMic(!mIsOpen));


        RecyclerView userRv = findViewById(R.id.layout_room_user_rv);
        GridLayoutManager gridLayoutManager = new GridLayoutManager(ChatRoomActivity.this, 4);
        gridLayoutManager.setSpanSizeLookup(new GridLayoutManager.SpanSizeLookup() {
            @Override
            public int getSpanSize(int position) {
                return position == 0 ? 4 : 1;
            }
        });
        userRv.setLayoutManager(gridLayoutManager);
        mChatRoomAdapter = new ChatRoomAdapter();
        userRv.setAdapter(mChatRoomAdapter);

        MeetingRoomInfo chatRoomInfo = new MeetingRoomInfo();
        chatRoomInfo.room_name = roomTitle;
        mChatRoomAdapter.setChatRoomInfo(chatRoomInfo);

        mChatRv = findViewById(R.id.layout_room_chat_rv);
        mChatRv.setLayoutManager(new LinearLayoutManager(this, RecyclerView.VERTICAL, false));
        mChatRoomChatAdapter = new ChatRoomChatAdapter();
        mChatRv.setAdapter(mChatRoomChatAdapter);

        mToastLayout = findViewById(R.id.room_toast_layout);
        mToastTv = findViewById(R.id.room_toast_text);
        mToastLayout.setOnClickListener((v) -> {
            mToastLayout.setVisibility(View.GONE);
            mLastShowDisconnectMs = System.currentTimeMillis();
        });

        mRaiseHandTv = findViewById(R.id.voice_chat_room_raise_hand_txt);
        mRaiseHandIv = findViewById(R.id.voice_chat_room_raise_hand_btn);
        mRaiseHandIv.setOnClickListener((v) -> {
            if (isHost()) {
                openRaisingList();
            } else {
                if (mIsSpeaker) {
                    confirmBecomeListener();
                } else {
                    mIsRaiseHand = true;
                    VoiceChatDataManger.requestRaiseHand();
                    requestPermissions(Manifest.permission.RECORD_AUDIO);
                    updateUI();
                }
            }
        });
        findViewById(R.id.voice_chat_room_audio_stats_btn).setOnClickListener((v) -> {
            openAudioStatsList();
        });

        updateUI();
        MeetingEventManager.register(this);
        if (!isCreateRoom) {
            VoiceChatDataManger.requestJoinRoom(roomId, MeetingApplication.sUserName);
        } else {
            onCreateJoinRoomResult(VoiceChatDataManger.sCreateRoomResult);
        }
    }

    @Override
    protected void setupStatusBar() {
        WindowUtils.setLayoutFullScreen(getWindow());
    }

    private void switchMic(boolean isOpen) {
        mIsOpen = isOpen;
        mMicStatusIv.setImageResource(isOpen ? R.drawable.voice_audio_enable : R.drawable.voice_audio_disable);
        mMicStatusTv.setText(isOpen ? "静音自己" : "取消静音");
        VoiceChatDataManger.switchMic(isOpen);
    }

    private boolean isHost() {
        return !TextUtils.isEmpty(mUserId) && TextUtils.equals(mUserId, mHostUserId);
    }

    @Override
    public void onBackPressed() {
        attemptLeaveRoom();
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        if (ContextCompat.checkSelfPermission(this, Manifest.permission.RECORD_AUDIO) == PERMISSION_GRANTED) {
            switchMic(true);
        }
    }

    public void attemptLeaveRoom() {
        AlertDialog.Builder builder = new AlertDialog.Builder(ChatRoomActivity.this, R.style.transparentDialog);
        View view = getLayoutInflater().inflate(R.layout.layout_leave_meeting, null);
        builder.setView(view);
        TextView titleTv = view.findViewById(R.id.leave_meeting_title);
        TextView finishTv = view.findViewById(R.id.leave_meeting_finish);
        TextView confirmTv = view.findViewById(R.id.leave_meeting_confirm);
        TextView cancelTv = view.findViewById(R.id.leave_meeting_cancel);
        builder.setCancelable(true);
        final AlertDialog dialog = builder.create();
        finishTv.setVisibility(View.GONE);
        if (isHost()) {
            if (mChatRoomAdapter.getSpeakerCount() > 1) {
                titleTv.setText("离开会将房间移交给下一位连麦主播，是否确认离开？");
            } else {
                titleTv.setText("离开会解散房间，是否确认离开？");
            }
        } else {
            titleTv.setText("是否确认离开房间？");
        }

        confirmTv.setBackgroundResource(R.drawable.meeting_leave_alert_bg);
        confirmTv.setTextColor(Color.parseColor("#FFFFFF"));

        confirmTv.setOnClickListener((v) -> {
            dialog.dismiss();
            leaveRoom();
            super.finish();
        });

        cancelTv.setOnClickListener((v) -> {
            dialog.dismiss();
        });
        dialog.show();
    }

    private void leaveRoom() {
        VoiceChatDataManger.requestLeaveRoom();
        MeetingRTCManager.leaveChannel();
    }

    private void openRaisingList() {
        ChatRaisingDialog chatRaisingDialog = new ChatRaisingDialog(this, mUserOptionCallback);
        chatRaisingDialog.setOnDismissListener((dialogInterface) -> {
            mIsRaiseDialogShowing = false;
            mIsSomeoneRaiseHand = false;
            updateUI();
        });
        chatRaisingDialog.show();
        mIsRaiseDialogShowing = true;
    }

    private void openAudioStatsList() {
        ChatAudioStatsDialog chatRaisingDialog = new ChatAudioStatsDialog(this);
        chatRaisingDialog.show();
    }

    private List<MeetingUserInfo> getUserList(List<MeetingUserInfo> userInfoList, boolean isSpeaker) {
        if (userInfoList == null || userInfoList.isEmpty()) {
            return null;
        }
        LinkedList<MeetingUserInfo> speakers = new LinkedList<>();
        for (MeetingUserInfo info : userInfoList) {
            if (info != null) {
                if (isSpeaker) {
                    if (info.user_status == UserStatus.UserStatusOnMicrophone.getStatus()) {
                        speakers.add(info);
                    }
                } else {
                    if (info.user_status != UserStatus.UserStatusOnMicrophone.getStatus()) {
                        speakers.add(info);
                    }
                }
            }
        }
        return speakers;
    }

    private void startCounting() {
        mDurationTv.removeCallbacks(mDurationCounting);
        mDurationTv.post(mDurationCounting);
    }

    private void updateDuration() {
        long duration = System.currentTimeMillis() - mEnterTs + mLastTs;
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
        mDurationTv.setText(str);
    }

    private void updateUI() {
        int micVisible = (mIsSpeaker || isHost()) ? View.VISIBLE : View.GONE;
        mMuteLocalLayout.setVisibility(micVisible);

        if (!isHost()) {
            if (mIsSpeaker) {
                mRaiseHandIv.setImageResource(R.drawable.voice_disable_raise_hand_unselected);
                mRaiseHandTv.setTextColor(mNormalColor);
                mRaiseHandTv.setText("下麦");
            } else {
                if (mIsRaiseHand) {
                    mRaiseHandIv.setImageResource(R.drawable.voice_raise_hand_selected);
                    mRaiseHandTv.setTextColor(mHighLightColor);
                } else {
                    mRaiseHandIv.setImageResource(R.drawable.voice_raise_hand_unselected);
                    mRaiseHandTv.setTextColor(mNormalColor);
                }
                mRaiseHandTv.setText("举手上麦");
            }
        } else {
            mRaiseHandTv.setText("列表管理");
            if (mIsRaiseDialogShowing || !mIsSomeoneRaiseHand) {
                mRaiseHandIv.setImageResource(R.drawable.voice_user_list_unselected);
                mRaiseHandTv.setTextColor(mNormalColor);
            } else {
                if (mIsSomeoneRaiseHand) {
                    mRaiseHandIv.setImageResource(R.drawable.voice_raise_hand_selected);
                    mRaiseHandTv.setTextColor(mHighLightColor);
                } else {
                    mRaiseHandIv.setImageResource(R.drawable.voice_user_list_unselected);
                    mRaiseHandTv.setTextColor(mNormalColor);
                }
            }
        }
    }

    private void showToast(String toast, boolean isShort) {
        mToastLayout.setVisibility(View.VISIBLE);
        mToastLayout.removeCallbacks(mAutoDismiss);
        if (isShort) {
            mToastLayout.postDelayed(mAutoDismiss, 2000);
        }
        mToastTv.setText(toast);
    }

    private void confirmBecomeListener() {
        if (VoiceChatDataManger.sIsDialogShowing) {
            return;
        }
        VoiceChatDataManger.sIsDialogShowing = true;
        CommonDialog dialog = new CommonDialog(this);
        dialog.setMessage("是否确认下麦？");
        dialog.setPositiveListener(v -> {
            VoiceChatDataManger.requestBecomeListener();
            dialog.dismiss();
        });
        dialog.setOnDismissListener((dialogInterface) -> VoiceChatDataManger.sIsDialogShowing = false);
        dialog.setNegativeListener(v -> dialog.dismiss());
        dialog.show();
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onCSJoinMeetingEvent(CSJoinMeetingEvent event) {
        ChatMsgInfo info = new ChatMsgInfo();
        info.content = event.user.user_name + "  加入了房间";
        mChatRoomChatAdapter.addChatMsgInfo(info);
        mChatRoomAdapter.addUser(event.user);
        mChatRv.post(() -> mChatRv.smoothScrollToPosition(mChatRoomChatAdapter.getItemCount()));
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onCSLeaveMeetingEvent(CSLeaveMeetingEvent event) {
        ChatMsgInfo info = new ChatMsgInfo();
        info.content = event.user.user_name + "  离开了房间";
        mChatRoomChatAdapter.addChatMsgInfo(info);
        mChatRoomAdapter.removeUser(event.user);
        mChatRv.post(() -> mChatRv.smoothScrollToPosition(mChatRoomChatAdapter.getItemCount()));
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onCreateJoinRoomResult(CreateJoinRoomResult event) {
        VoiceChatDataManger.setRoomInfo(event);
        if (event.info != null && event.users != null) {
            mHostUserId = event.info.host_id;

            List<MeetingUserInfo> speakers = getUserList(event.users, true);
            List<MeetingUserInfo> audiences = getUserList(event.users, false);
            mIsOpen = false;
            for (MeetingUserInfo info : event.users) {
                if (TextUtils.equals(info.user_id, mUserId)) {
                    mIsRaiseHand = info.user_status == UserStatus.UserStatusRaiseHands.getStatus();
                    mIsOpen = info.is_mic_on && isHost();
                    break;
                }
            }
            mChatRoomAdapter.setSpeakerList(speakers);
            mChatRoomAdapter.setListenerList(audiences);
            mChatRoomAdapter.setChatRoomInfo(event.info);

            mLastTs = Math.max(0, (event.info.now - event.info.created_at) / 1000000);
            mEnterTs = System.currentTimeMillis();
            mRoomIdTv.setText(event.info.room_id);
            MeetingRTCManager.joinChannel(event.token, event.info.room_id, null, mUserId);
            switchMic(mIsOpen);
            startCounting();

            updateUI();
        } else {
            CommonDialog dialog = new CommonDialog(this);
            dialog.setCancelable(false);
            dialog.setMessage("加入房间失败，回到房间列表页");
            dialog.setPositiveListener((v) -> finish());
            dialog.show();

            leaveRoom();
        }
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onCSRaiseHandsMicEvent(CSRaiseHandsMicEvent event) {
        mChatRoomAdapter.updateRaiseHandStatus(event.userId);
        mIsSomeoneRaiseHand = true;
        updateUI();
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onCSInviteMicEvent(CSInviteMicEvent event) {
        if (VoiceChatDataManger.sIsDialogShowing) {
            return;
        }
        VoiceChatDataManger.sIsDialogShowing = true;
        if (TextUtils.equals(event.userId, mUserId)) {
            CommonDialog dialog = new CommonDialog(this);
            dialog.setMessage("主播邀请您上麦");
            dialog.setPositiveListener(v -> {
                VoiceChatDataManger.confirmBecomeSpeaker();
                dialog.dismiss();
            });
            dialog.setNegativeListener(v -> dialog.dismiss());
            dialog.setOnDismissListener((dialogInterface) -> VoiceChatDataManger.sIsDialogShowing = false);
            dialog.show();
        }
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onCSMicOnEvent(CSMicOnEvent event) {
        if (TextUtils.equals(event.user.user_id, mUserId)) {
            requestPermissions(Manifest.permission.RECORD_AUDIO);
            showToast("您已经成功上麦", true);
            mIsSpeaker = true;
            mIsRaiseHand = false;
            switchMic(true);
        }
        mChatRoomAdapter.onUserRoleChange(event.user.user_id, true);
        updateUI();
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onCSMicOffEvent(CSMicOffEvent event) {
        if (TextUtils.equals(event.userId, mUserId)) {
            showToast("您已回到听众席", true);
            mIsSpeaker = false;
            switchMic(false);
        }
        mChatRoomAdapter.onUserRoleChange(event.userId, false);
        updateUI();
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onCSMeetingEndEvent(CSMeetingEndEvent event) {
        leaveRoom();
        finish();
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onCSMuteMicEvent(CSMuteMicEvent event) {
        mChatRoomAdapter.updateUserMicStatus(event.userId, false);
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onCSUnmuteMicEvent(CSUnmuteMicEvent event) {
        mChatRoomAdapter.updateUserMicStatus(event.userId, true);
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onSocketConnectEvent(SocketConnectEvent event) {
        if (event.status == SocketConnectEvent.ConnectStatus.CONNECTING) {
            if (mConnectStatus != SocketConnectEvent.ConnectStatus.CONNECTING) {
                mToastTv.setText("网络链接已断开，请检查设置");
                mToastLayout.postDelayed(mNetWorkRunnable, 60_000);
            }

            if (System.currentTimeMillis() - mLastShowDisconnectMs > 2000) {
                mToastLayout.setVisibility(View.VISIBLE);
            }
        } else {
            mToastLayout.setVisibility(View.GONE);
            mToastLayout.removeCallbacks(mNetWorkRunnable);

            if (event.status == SocketConnectEvent.ConnectStatus.RECONNECTED) {
                VoiceChatDataManger.reconnect();
            }
        }
        mConnectStatus = event.status;
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onCSToastEvent(CSToastEvent event) {
        showToast(event.toast, true);
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onRTCVolumeEvent(RTCVolumeEvent event) {
        if (event.speakers == null || event.speakers.length == 0) {
            return;
        }
        List<String> uidList = new LinkedList<>();
        for (IRtcEngineEventHandler.AudioVolumeInfo info : event.speakers) {
            if (info.volume >= Constants.VOLUME_MIN_THRESHOLD) {
                if (!TextUtils.isEmpty(info.uid)) {
                    uidList.add(info.uid);
                }
            }
        }
        MLog.d("onRTCVolumeEvent", JsonUtils.toJson(uidList));
        mChatRoomAdapter.updateVolumeStatus(uidList);
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onCSHostChangeEvent(CSHostChangeEvent event) {
        if (!TextUtils.isEmpty(event.hostId)) {
            mHostUserId = event.hostId;
        }
        if (TextUtils.equals(mUserId, event.hostId)) {
            updateUI();
        }
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onTokenExpiredEvent(TokenExpiredEvent event) {
        finish();
    }
}
