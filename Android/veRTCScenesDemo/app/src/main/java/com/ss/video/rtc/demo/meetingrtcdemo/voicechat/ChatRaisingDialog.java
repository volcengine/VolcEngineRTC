package com.ss.video.rtc.demo.meetingrtcdemo.voicechat;

import android.content.Context;
import android.graphics.Color;
import android.text.TextUtils;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.WindowManager;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatDialog;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.ss.video.rtc.demo.basic_module.ui.CommonDialog;
import com.ss.video.rtc.demo.basic_module.utils.WindowUtils;
import com.ss.video.rtc.demo.meetingrtcdemo.R;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.CSJoinMeetingEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.CSLeaveMeetingEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.CSMicOffEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.CSMicOnEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.CSRaiseHandsMicEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.CSRefreshListenerEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.CSRefreshRaiseHandEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.MeetingEventManager;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.MeetingUserInfo;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.UserStatus;

import org.greenrobot.eventbus.Subscribe;
import org.greenrobot.eventbus.ThreadMode;

import java.util.LinkedList;
import java.util.List;

public class ChatRaisingDialog extends AppCompatDialog {

    private final int mHighLightColor = Color.parseColor("#ffffff");
    private final int mNormalColor = Color.parseColor("#86909C");

    private final View mView;
    private final List<MeetingUserInfo> mRaiseData = new LinkedList<>();
    private final List<MeetingUserInfo> mListenerData = new LinkedList<>();
    private final RecyclerView mRaiseRv;
    private final RecyclerView mListenerRv;
    private final RaisingAdapter mRaiseAdapter;
    private final RaisingAdapter mListenerAdapter;

    public ChatRaisingDialog(Context context, UserOptionCallback userOptionCallback) {
        super(context, R.style.CommonDialog);
        setCancelable(true);

        mView = LayoutInflater.from(getContext()).inflate(R.layout.dialog_voice_users, null);

        mView.findViewById(R.id.dialog_voice_users_hover).setOnClickListener((v) -> dismiss());

        mRaiseRv = mView.findViewById(R.id.dialog_voice_users_speaker);
        mRaiseRv.setLayoutManager(new LinearLayoutManager(context, RecyclerView.VERTICAL, false));
        mRaiseAdapter = new RaisingAdapter(mRaiseData, userOptionCallback);
        mRaiseRv.setAdapter(mRaiseAdapter);

        mListenerRv = mView.findViewById(R.id.dialog_voice_users_listener);
        mListenerRv.setLayoutManager(new LinearLayoutManager(context, RecyclerView.VERTICAL, false));
        mListenerAdapter = new RaisingAdapter(mListenerData, userOptionCallback);
        mListenerRv.setAdapter(mListenerAdapter);

        TextView raiseTv = mView.findViewById(R.id.dialog_voice_users_raise_list);
        TextView listenerTv = mView.findViewById(R.id.dialog_voice_users_listener_list);
        View raiseIndicator = mView.findViewById(R.id.dialog_voice_users_raise_indicator);
        View listenerIndicator = mView.findViewById(R.id.dialog_voice_users_listener_indicator);
        mRaiseRv.setVisibility(View.VISIBLE);
        mListenerRv.setVisibility(View.GONE);
        raiseTv.setTextColor(mHighLightColor);
        listenerTv.setTextColor(mNormalColor);
        raiseIndicator.setVisibility(View.VISIBLE);
        listenerIndicator.setVisibility(View.GONE);
        mView.findViewById(R.id.dialog_voice_users_raise_list).setOnClickListener(v -> {
            mRaiseRv.setVisibility(View.VISIBLE);
            mListenerRv.setVisibility(View.GONE);
            raiseTv.setTextColor(mHighLightColor);
            listenerTv.setTextColor(mNormalColor);
            raiseIndicator.setVisibility(View.VISIBLE);
            listenerIndicator.setVisibility(View.GONE);
        });
        mView.findViewById(R.id.dialog_voice_users_listener_list).setOnClickListener(v -> {
            mRaiseRv.setVisibility(View.GONE);
            mListenerRv.setVisibility(View.VISIBLE);
            raiseTv.setTextColor(mNormalColor);
            listenerTv.setTextColor(mHighLightColor);
            raiseIndicator.setVisibility(View.GONE);
            listenerIndicator.setVisibility(View.VISIBLE);
        });
        mView.findViewById(R.id.dialog_voice_users_close).setOnClickListener(v -> {
            dismiss();
        });
    }

    public void setRaiseUserList(List<MeetingUserInfo> infoList) {
        mRaiseData.clear();
        if (infoList != null) {
            mRaiseData.addAll(infoList);
        }
        mRaiseAdapter.setData(infoList);
    }

    public void setListenerUserList(List<MeetingUserInfo> infoList) {
        mListenerData.clear();
        if (infoList != null) {
            mListenerData.addAll(infoList);
        }
        mListenerAdapter.setData(infoList);
    }

    @Override
    public void show() {
        super.show();
        WindowManager.LayoutParams params = getWindow().getAttributes();
        params.width = WindowUtils.getScreenWidth(getContext());
        params.height = ViewGroup.LayoutParams.MATCH_PARENT;
        getWindow().setAttributes(params);
        getWindow().setContentView(mView, new ViewGroup.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT,
                ViewGroup.LayoutParams.MATCH_PARENT));

        MeetingEventManager.register(this);
        initData();
    }

    @Override
    public void dismiss() {
        super.dismiss();
        MeetingEventManager.unregister(this);
    }

    private void initData() {
        VoiceChatDataManger.requestRaiseHandUserList();
        VoiceChatDataManger.requestListenerUserList();
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onCSRefreshRaiseHandEvent(CSRefreshRaiseHandEvent event) {
        setRaiseUserList(event.users);
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onCSRefreshListenerEvent(CSRefreshListenerEvent event) {
        setListenerUserList(event.users);
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onCSJoinMeetingEvent(CSJoinMeetingEvent event) {
        initData();
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onCSLeaveMeetingEvent(CSLeaveMeetingEvent event) {
        initData();
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onCSRaiseHandsMicEvent(CSRaiseHandsMicEvent event) {
        MeetingUserInfo info = mListenerAdapter.removeUser(event.userId);
        if (info != null) {
            mRaiseAdapter.addUser(info);
        }
        mRaiseAdapter.updateUserStatusChanged(event.userId, UserStatus.UserStatusRaiseHands.getStatus());
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onCSMicOnEvent(CSMicOnEvent event) {
        MeetingUserInfo info = mListenerAdapter.removeUser(event.user.user_id);
        if (info != null) {
            mRaiseAdapter.addUser(info);
        }
        mRaiseAdapter.updateUserStatusChanged(event.user.user_id, UserStatus.UserStatusOnMicrophone.getStatus());
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onCSMicOffEvent(CSMicOffEvent event) {
        MeetingUserInfo info = mRaiseAdapter.removeUser(event.userId);
        if (info != null) {
            mListenerAdapter.addUser(info);
        }
        mListenerAdapter.updateUserStatusChanged(event.userId, UserStatus.UserStatusAudience.getStatus());
    }


    private static class RaisingAdapter extends RecyclerView.Adapter<RecyclerView.ViewHolder> {

        private final List<MeetingUserInfo> mData = new LinkedList<>();
        private final UserOptionCallback mUserOptionCallback;

        public RaisingAdapter(List<MeetingUserInfo> data, UserOptionCallback userOptionCallback) {
            mData.addAll(data);
            mUserOptionCallback = userOptionCallback;
        }

        @NonNull
        @Override
        public RecyclerView.ViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
            View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.item_voice_users, parent, false);
            return new RaisingViewHolder(view, mUserOptionCallback);
        }

        @Override
        public void onBindViewHolder(@NonNull RecyclerView.ViewHolder holder, int position) {
            if (holder instanceof RaisingViewHolder) {
                ((RaisingViewHolder) holder).bind(mData.get(position));
            }
        }

        @Override
        public int getItemCount() {
            return mData.size();
        }

        public void setData(List<MeetingUserInfo> userInfo) {
            mData.clear();
            if (userInfo != null) {
                mData.addAll(userInfo);
            }
            notifyDataSetChanged();
        }

        public void updateUserStatusChanged(String uid, int status) {
            if (TextUtils.isEmpty(uid)) {
                return;
            }
            for (int i = 0; i < mData.size(); i++) {
                if (TextUtils.equals(mData.get(i).user_id, uid)) {
                    mData.get(i).user_status = status;
                    notifyItemChanged(i);
                    return;
                }
            }
        }

        public void addUser(MeetingUserInfo info) {
            if (info == null || TextUtils.isEmpty(info.user_id)) {
                return;
            }
            for (int i = 0; i < mData.size(); i++) {
                if (TextUtils.equals(mData.get(i).user_id, info.user_id)) {
                    return;
                }
            }
            mData.add(info);
            notifyItemInserted(mData.size());
        }

        public MeetingUserInfo removeUser(String uid) {
            if (TextUtils.isEmpty(uid)) {
                return null;
            }
            for (int i = 0; i < mData.size(); i++) {
                if (TextUtils.equals(mData.get(i).user_id, uid)) {
                    MeetingUserInfo info = mData.remove(i);
                    notifyItemRemoved(i);
                    return info;
                }
            }
            return null;
        }
    }

    private static class RaisingViewHolder extends RecyclerView.ViewHolder {

        private final TextView mUserPrefixTv;
        private final TextView mUserNameTv;
        private final TextView mOptionTv;
        private final UserOptionCallback mUserOptionCallback;
        private MeetingUserInfo mInfo;

        public RaisingViewHolder(@NonNull View itemView, UserOptionCallback userOptionCallback) {
            super(itemView);
            mUserPrefixTv = itemView.findViewById(R.id.item_voice_user_prefix);
            mUserNameTv = itemView.findViewById(R.id.item_voice_user_name);
            mOptionTv = itemView.findViewById(R.id.item_voice_user_option);
            mUserOptionCallback = userOptionCallback;
            mOptionTv.setOnClickListener((v) -> {
                if (mInfo != null && mUserOptionCallback != null) {
                    MeetingUserInfo info = mInfo;
                    if (info.user_status == UserStatus.UserStatusOnMicrophone.getStatus()) {
                        if (VoiceChatDataManger.sIsDialogShowing) {
                            return;
                        }
                        VoiceChatDataManger.sIsDialogShowing = true;
                        CommonDialog dialog = new CommonDialog(itemView.getContext());
                        dialog.setMessage("是否将该用户下麦？");
                        dialog.setPositiveListener(dialogView -> {
                            mUserOptionCallback.onClick(mInfo);
                            dialog.dismiss();
                        });
                        dialog.setNegativeListener(dialogView -> dialog.dismiss());
                        dialog.setOnDismissListener((dialogInterface) -> VoiceChatDataManger.sIsDialogShowing = false);
                        dialog.show();
                    } else {
                        mUserOptionCallback.onClick(mInfo);
                    }
                }
            });
        }

        public void bind(MeetingUserInfo info) {
            mInfo = info;
            mUserPrefixTv.setText(info.user_name.substring(0, 1));
            mUserNameTv.setText(info.user_name);
            if (info.user_status == UserStatus.UserStatusRaiseHands.getStatus()) {
                mOptionTv.setText("同意");
                mOptionTv.setBackgroundResource(R.drawable.item_voice_listener_option_unselected_bg);
            } else if (info.user_status == UserStatus.UserStatusOnMicrophone.getStatus()) {
                mOptionTv.setText("下麦");
                mOptionTv.setBackgroundResource(R.drawable.item_voice_listener_option_selected_bg);
            } else {
                mOptionTv.setText("邀请上麦");
                mOptionTv.setBackgroundResource(R.drawable.item_voice_listener_option_unselected_bg);
            }
        }
    }

    public interface UserOptionCallback {
        void onClick(MeetingUserInfo info);
    }
}