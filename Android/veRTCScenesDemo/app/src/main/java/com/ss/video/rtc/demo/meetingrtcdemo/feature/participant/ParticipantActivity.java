package com.ss.video.rtc.demo.meetingrtcdemo.feature.participant;

import android.app.Activity;
import android.app.AlertDialog;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.Nullable;
import androidx.lifecycle.Lifecycle;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.ss.video.rtc.demo.basic_module.acivities.BaseActivity;
import com.ss.video.rtc.demo.basic_module.ui.CommonDialog;
import com.ss.video.rtc.demo.basic_module.utils.AppExecutors;
import com.ss.video.rtc.demo.meetingrtcdemo.R;
import com.ss.video.rtc.demo.meetingrtcdemo.core.MeetingDataManager;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.AskOpenMicEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.CameraStatusChangedEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.HostChangedEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.KickedOffEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.MeetingEndEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.MeetingEventManager;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.MicStatusChangeEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.MuteAllEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.RoomCloseEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.UserJoinEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.UserLeaveEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.ShareScreenEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.VolumeEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.MeetingUserInfo;
import com.ss.video.rtc.demo.meetingrtcdemo.resource.Constants;

import org.greenrobot.eventbus.Subscribe;
import org.greenrobot.eventbus.ThreadMode;

import java.util.LinkedList;
import java.util.List;
import java.util.Map;

public class ParticipantActivity extends BaseActivity implements View.OnClickListener {

    private TextView mTitleView;
    private View mMuteAllBtn;

    private ParticipantAdapter mParticipantAdapter = null;
    private final ParticipantAdapter.UserOptionCallback mUserOptionCallback = uid -> {
        if (MeetingDataManager.isSelfHost()) {
            showUserOptionDialog(ParticipantActivity.this, uid, MeetingDataManager.isUserMute(uid));
        }
    };

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_participant);
    }

    @Override
    protected void onGlobalLayoutCompleted() {
        super.onGlobalLayoutCompleted();

        ImageView backArrow = findViewById(R.id.title_bar_left_iv);
        backArrow.setImageResource(R.drawable.back_arrow);
        backArrow.setOnClickListener(v -> finish());

        RecyclerView recyclerView = findViewById(R.id.users_recycler_view);
        LinearLayoutManager layoutManager = new LinearLayoutManager(getApplicationContext());
        recyclerView.setLayoutManager(layoutManager);
        mParticipantAdapter = new ParticipantAdapter(new LinkedList<>(), mUserOptionCallback);
        recyclerView.setAdapter(mParticipantAdapter);

        mTitleView = findViewById(R.id.title_bar_title_tv);
        mMuteAllBtn = findViewById(R.id.users_mute_all_users);
        mMuteAllBtn.setVisibility(MeetingDataManager.isSelfHost() ? View.VISIBLE : View.GONE);
        mMuteAllBtn.setOnClickListener(this);

        updateTitle();
        MeetingEventManager.register(this);
        loadParticipant();
    }

    @Override
    public void finish() {
        super.finish();
        MeetingEventManager.unregister(this);
    }

    @Override
    public void onClick(View v) {
        if (v == mMuteAllBtn) {
            AppExecutors.networkIO().execute(() -> MeetingDataManager.getManager().muteAllUserMic());
        }
    }

    private void updateTitle() {
        mTitleView.setText(getString(R.string.users_title, mParticipantAdapter.getItemCount()));
    }

    private void loadParticipant() {
        AppExecutors.networkIO().execute(() -> {
            List<MeetingUserInfo> infoList = MeetingDataManager.getManager().getMeetingParticipantsInfo();
            if (infoList != null && !infoList.isEmpty()) {
                showData(infoList);
            } else {
                showLocalData();
            }
        });
    }

    private void showLocalData() {
        final List<MeetingUserInfo> infoList = MeetingDataManager.getAllMeetingUserInfoList();
        if (infoList.isEmpty()) {
            return;
        }
        String hostUid = MeetingDataManager.getHostUid();
        MeetingUserInfo info;
        MeetingUserInfo hostInfo = null;
        for (int i = infoList.size() - 1; i >= 0; i--) {
            info = infoList.get(i);
            if (hostUid != null && hostUid.equals(info.user_id)) {
                hostInfo = info;
                infoList.remove(i);
                break;
            }
        }
        if (hostInfo != null) {
            infoList.add(0, hostInfo);
        }
        showData(infoList);
    }

    private void showData(List<MeetingUserInfo> infoList) {
        if (isFinishing()) {
            return;
        }
        runOnUiThread(() -> {
            if (!ParticipantActivity.this.isFinishing()) {
                mParticipantAdapter.setData(infoList);
                updateTitle();
            }
        });
    }

    private void showUserOptionDialog(Activity activity, String uid, boolean isMute) {
        if (MeetingDataManager.isSelf(uid)) {
            return;
        }
        AlertDialog.Builder builder = new AlertDialog.Builder(activity, R.style.transparentDialog);
        View view = activity.getLayoutInflater().inflate(R.layout.layout_users_options, null);
        builder.setView(view);
        TextView micOption = view.findViewById(R.id.user_option_mic);
        TextView hostOption = view.findViewById(R.id.user_option_host);
        builder.setCancelable(true);
        AlertDialog dialog = builder.create();
        if (isMute) {
            micOption.setText("请求开麦");
            micOption.setOnClickListener(v -> AppExecutors.networkIO().execute(() -> {
                AppExecutors.networkIO().execute(() -> MeetingDataManager.getManager().askUserMicOn(uid));
                dialog.dismiss();
            }));
        } else {
            micOption.setText("静音");
            micOption.setOnClickListener(v -> AppExecutors.networkIO().execute(() -> {
                AppExecutors.networkIO().execute(() -> MeetingDataManager.getManager().muteUserMic(uid));
                dialog.dismiss();
            }));
        }
        hostOption.setText("移交主持人");
        hostOption.setOnClickListener(v -> AppExecutors.networkIO().execute(() -> {
            AppExecutors.networkIO().execute(() -> MeetingDataManager.getManager().changeHost(uid));
            dialog.dismiss();
        }));
        dialog.show();
    }

    public void onAskOpenMic() {
        if (isFinishing() || getLifecycle().getCurrentState() != Lifecycle.State.RESUMED) {
            return;
        }
        if (MeetingDataManager.isSelfHost()) {
            return;
        }
        if (MeetingDataManager.getMicStatus()) {
            return;
        }
        CommonDialog dialog = new CommonDialog(this);
        dialog.setMessage(this.getString(R.string.on_ask_open_mic));
        dialog.setPositiveListener(v -> {
            if (!MeetingDataManager.getMicStatus()) {
                MeetingDataManager.switchMic(true);
            }
            dialog.dismiss();
        });
        dialog.setNegativeListener(v -> dialog.dismiss());
        dialog.show();
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void OnUserJoinEvent(UserJoinEvent event) {
        mParticipantAdapter.onUserJoin(event.meetingUserInfo);
        updateTitle();
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void OnUserJoinEvent(UserLeaveEvent event) {
        mParticipantAdapter.onUserLeave(event.meetingUserInfo);
        updateTitle();
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void OnShareScreenEvent(ShareScreenEvent event) {
        mParticipantAdapter.onScreenShareChanged(event.shareUid, event.isStart);
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void OnMicStatusChangeEvent(MicStatusChangeEvent event) {
        mParticipantAdapter.onMicStatusChanged(event.uid, event.status);
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void OnCameraStatusChangedEvent(CameraStatusChangedEvent event) {
        mParticipantAdapter.onCameraStatusChanged(event.uid, event.status);
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onHostChangedEvent(HostChangedEvent event) {
        mMuteAllBtn.setVisibility(MeetingDataManager.isSelf(event.currentUid) ? View.VISIBLE : View.GONE);
        mParticipantAdapter.onHostChanged(event.formerUid, event.currentUid);
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onMeetingEndEvent(MeetingEndEvent event) {
        finish();
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onRoomCloseEvent(RoomCloseEvent event) {
        finish();
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onAskOpenMicEvent(AskOpenMicEvent event) {
        onAskOpenMic();
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onVolumeEvent(VolumeEvent event) {
        Map<String, Integer> uidVolumeMap = event.uidVolumeMap;
        for (Map.Entry<String, Integer> entry : uidVolumeMap.entrySet()) {
            mParticipantAdapter.onVolumeEvent(entry.getKey(), entry.getValue());
        }
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onMuteAllEvent(MuteAllEvent event) {
        mParticipantAdapter.onMuteAllEvent();
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onKickedOffEvent(KickedOffEvent event) {
        finish();
    }
}
