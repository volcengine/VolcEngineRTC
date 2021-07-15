package com.ss.video.rtc.demo.meetingrtcdemo.voicechat;

import android.text.TextUtils;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.GridLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.ss.video.rtc.demo.meetingrtcdemo.R;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.MeetingRoomInfo;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.MeetingUserInfo;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.UserStatus;

import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Set;

public class ChatRoomAdapter extends RecyclerView.Adapter<RecyclerView.ViewHolder> {

    private static final int VIEW_TYPE_HEADER = 0;
    private static final int VIEW_TYPE_COMMON = 1;

    private static final String HEADER_USERS_CHANGED = "header_users_changed";
    private static final String HEADER_LISTENER_CHANGED = "header_listener_changed";
    private static final String HEADER_UPDATE_HIGHLIGHT = "header_update_highlight";

    private MeetingRoomInfo mChatRoomInfo;
    private final Set<String> mHighlightUids = new HashSet<>();
    private final List<MeetingUserInfo> mChatRoomListenerList = new LinkedList<>();
    private final List<MeetingUserInfo> mChatRoomSpeakerList = new LinkedList<>();

    @NonNull
    @Override
    public RecyclerView.ViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view;
        if (VIEW_TYPE_HEADER == viewType) {
            view = LayoutInflater.from(parent.getContext()).inflate(R.layout.item_voice_chat_room_header, parent, false);
            return new ChatRoomHeaderViewHolder(view);
        } else {
            view = LayoutInflater.from(parent.getContext()).inflate(R.layout.item_voice_listener_layout, parent, false);
            return new ChatRoomCommonViewHolder(view);
        }
    }

    @Override
    public void onBindViewHolder(@NonNull RecyclerView.ViewHolder holder, int position) {
        if (holder instanceof ChatRoomHeaderViewHolder) {
            ((ChatRoomHeaderViewHolder) holder).bind(mChatRoomInfo, mChatRoomSpeakerList, mChatRoomListenerList.size());
        } else if (holder instanceof ChatRoomCommonViewHolder) {
            ((ChatRoomCommonViewHolder) holder).bind(mChatRoomListenerList.get(position - 1));
        }
    }

    @Override
    public void onBindViewHolder(@NonNull RecyclerView.ViewHolder holder, int position, @NonNull List<Object> payloads) {
        if (payloads.contains(HEADER_UPDATE_HIGHLIGHT)) {
            if (holder instanceof ChatRoomHeaderViewHolder) {
                ((ChatRoomHeaderViewHolder) holder).updateHighlight(mHighlightUids);
            }
        } else if (payloads.contains(HEADER_USERS_CHANGED)) {
            if (holder instanceof ChatRoomHeaderViewHolder) {
                ((ChatRoomHeaderViewHolder) holder).notifyUserListChanged(mChatRoomSpeakerList);
            }
        } else if (payloads.contains(HEADER_LISTENER_CHANGED)) {
            if (holder instanceof ChatRoomHeaderViewHolder) {
                ((ChatRoomHeaderViewHolder) holder).notifyListenerListChanged(mChatRoomListenerList.size());
            }
        } else {
            super.onBindViewHolder(holder, position, payloads);
        }
    }

    @Override
    public int getItemViewType(int position) {
        if (position == 0) {
            return VIEW_TYPE_HEADER;
        } else {
            return VIEW_TYPE_COMMON;
        }
    }

    @Override
    public int getItemCount() {
        return mChatRoomListenerList.size() + 1;
    }

    public void setChatRoomInfo(MeetingRoomInfo chatRoomInfo) {
        mChatRoomInfo = chatRoomInfo;
        notifyItemChanged(0);
    }

    public void setSpeakerList(List<MeetingUserInfo> chatRoomUserInfoList) {
        mChatRoomSpeakerList.clear();
        if (chatRoomUserInfoList != null) {
            mChatRoomSpeakerList.addAll(chatRoomUserInfoList);
        }
        notifyItemChanged(0);
    }

    public void setListenerList(List<MeetingUserInfo> chatRoomUserInfoList) {
        mChatRoomListenerList.clear();
        if (chatRoomUserInfoList != null) {
            mChatRoomListenerList.addAll(chatRoomUserInfoList);
        }
        notifyDataSetChanged();
    }

    public void addUser(MeetingUserInfo info) {
        String uid = info.user_id;
        if (TextUtils.isEmpty(uid)) {
            return;
        }
        for (MeetingUserInfo temp : mChatRoomListenerList) {
            if (TextUtils.equals(uid, temp.user_id)) {
                return;
            }
        }
        mChatRoomListenerList.add(info);
        notifyItemInserted(mChatRoomListenerList.size() + 1);
        notifyItemChanged(0, HEADER_LISTENER_CHANGED);
    }

    public void removeUser(MeetingUserInfo info) {
        String uid = info.user_id;
        if (TextUtils.isEmpty(uid)) {
            return;
        }
        for (int i = 0; i < mChatRoomSpeakerList.size(); i++) {
            MeetingUserInfo temp = mChatRoomSpeakerList.get(i);
            if (TextUtils.equals(uid, temp.user_id)) {
                mChatRoomSpeakerList.remove(i);
                notifyItemChanged(0);
                break;
            }
        }
        for (int i = 0; i < mChatRoomListenerList.size(); i++) {
            MeetingUserInfo temp = mChatRoomListenerList.get(i);
            if (TextUtils.equals(uid, temp.user_id)) {
                mChatRoomListenerList.remove(i);
                notifyItemRemoved(i + 1);
                break;
            }
        }
        notifyItemChanged(0, HEADER_LISTENER_CHANGED);
    }

    public void updateVolumeStatus(List<String> userIdList) {
        mHighlightUids.clear();
        mHighlightUids.addAll(userIdList);
        notifyItemChanged(0, HEADER_UPDATE_HIGHLIGHT);
    }

    public void updateUserMicStatus(String uid, boolean isMicOn) {
        if (TextUtils.isEmpty(uid)) {
            return;
        }
        for (int i = 0; i < mChatRoomSpeakerList.size(); i++) {
            MeetingUserInfo info = mChatRoomSpeakerList.get(i);
            if (TextUtils.equals(uid, info.user_id)) {
                if (info.is_mic_on != isMicOn) {
                    info.is_mic_on = isMicOn;
                    notifyItemChanged(0, HEADER_UPDATE_HIGHLIGHT);
                }
                return;
            }
        }
    }

    public void updateRaiseHandStatus(String uid) {
        if (TextUtils.isEmpty(uid)) {
            return;
        }
        for (int i = 0; i < mChatRoomListenerList.size(); i++) {
            if (TextUtils.equals(uid, mChatRoomListenerList.get(i).user_id)) {
                mChatRoomListenerList.get(i).user_status = UserStatus.UserStatusRaiseHands.getStatus();
                notifyItemChanged(i + 1);
                return;
            }
        }
    }

    public void onUserRoleChange(String uid, boolean isSpeaker) {
        MeetingUserInfo userInfo = null;
        if (isSpeaker) {
            for (int i = 0; i < mChatRoomListenerList.size(); i++) {
                MeetingUserInfo temp = mChatRoomListenerList.get(i);
                if (TextUtils.equals(uid, temp.user_id)) {
                    mChatRoomListenerList.remove(i);
                    notifyItemRemoved(i + 1);
                    userInfo = temp;
                    break;
                }
            }

            for (int i = 0; i < mChatRoomSpeakerList.size(); i++) {
                MeetingUserInfo temp = mChatRoomSpeakerList.get(i);
                if (TextUtils.equals(uid, temp.user_id)) {
                    mChatRoomSpeakerList.remove(i);
                    break;
                }
            }
            if (userInfo != null) {
                userInfo.user_status = UserStatus.UserStatusOnMicrophone.getStatus();
                mChatRoomSpeakerList.add(userInfo);
                notifyItemChanged(0, HEADER_USERS_CHANGED);
            }
        } else {
            for (int i = 0; i < mChatRoomSpeakerList.size(); i++) {
                MeetingUserInfo temp = mChatRoomSpeakerList.get(i);
                if (TextUtils.equals(uid, temp.user_id)) {
                    mChatRoomSpeakerList.remove(i);
                    userInfo = temp;
                    notifyItemChanged(0, HEADER_USERS_CHANGED);
                    break;
                }
            }

            for (MeetingUserInfo temp : mChatRoomListenerList) {
                if (TextUtils.equals(uid, temp.user_id)) {
                    return;
                }
            }
            if (userInfo != null) {
                userInfo.user_status = UserStatus.UserStatusAudience.getStatus();
                mChatRoomListenerList.add(userInfo);
                notifyItemInserted(mChatRoomListenerList.size() + 1);
            }
        }
    }

    public int getSpeakerCount() {
        return mChatRoomSpeakerList.size();
    }

    private static class ChatRoomHeaderViewHolder extends RecyclerView.ViewHolder {

        private final TextView mHeaderTitle;
        private final TextView mListenerCount;
        private final ChatSpeakerAdapter mChatSpeakerAdapter = new ChatSpeakerAdapter();

        public ChatRoomHeaderViewHolder(@NonNull View itemView) {
            super(itemView);
            mHeaderTitle = itemView.findViewById(R.id.item_voice_header_title);
            mListenerCount = itemView.findViewById(R.id.item_voice_listener_count);
            RecyclerView speakerRv = itemView.findViewById(R.id.item_voice_speaker_rv);
            speakerRv.setLayoutManager(new GridLayoutManager(itemView.getContext(), 3));
            speakerRv.setAdapter(mChatSpeakerAdapter);
        }

        public void bind(MeetingRoomInfo info, List<MeetingUserInfo> infoList, int count) {
            if (info != null) {
                mHeaderTitle.setText(info.room_name);
            }
            mChatSpeakerAdapter.setSpeakerList(infoList);
            notifyListenerListChanged(count);
        }

        public void updateHighlight(Set<String> uids) {
            mChatSpeakerAdapter.updateHighlight(uids);
        }

        public void notifyUserListChanged(List<MeetingUserInfo> infoList) {
            mChatSpeakerAdapter.setSpeakerList(infoList);
        }

        public void notifyListenerListChanged(int count) {
            mListenerCount.setText(String.format("其他听众%d人", count));
        }
    }

    private static class ChatRoomCommonViewHolder extends RecyclerView.ViewHolder {

        private final View mIsRaising;
        private final TextView mUserNamePrefix;
        private final TextView mUserName;

        public ChatRoomCommonViewHolder(@NonNull View itemView) {
            super(itemView);
            mIsRaising = itemView.findViewById(R.id.item_voice_listener_raise);
            mUserNamePrefix = itemView.findViewById(R.id.item_voice_listener_avatar);
            mUserName = itemView.findViewById(R.id.item_voice_listener_name);
        }

        public void bind(MeetingUserInfo info) {
            if (info == null) {
                mIsRaising.setVisibility(View.INVISIBLE);
                mUserNamePrefix.setText("");
                mUserName.setText("");
            } else {
                mIsRaising.setVisibility(info.user_status == UserStatus.UserStatusRaiseHands.getStatus() ? View.VISIBLE : View.INVISIBLE);
                String userName = info.user_name;
                mUserName.setText(info.user_name);
                if (!TextUtils.isEmpty(userName)) {
                    mUserNamePrefix.setText(userName.substring(0, 1));
                } else {
                    mUserNamePrefix.setText("");
                }
            }
        }
    }

    private static class ChatSpeakerAdapter extends RecyclerView.Adapter<RecyclerView.ViewHolder> {

        private static final String HIGHLIGHT_ON = "highlight_on";
        private static final String HIGHLIGHT_OFF = "highlight_off";

        private final List<MeetingUserInfo> mChatRoomSpeakerList = new LinkedList<>();

        @NonNull
        @Override
        public RecyclerView.ViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
            View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.item_voice_speaker_layout, parent, false);
            return new ChatSpeakerViewHolder(view);
        }

        @Override
        public void onBindViewHolder(@NonNull RecyclerView.ViewHolder holder, int position) {
            if (holder instanceof ChatSpeakerViewHolder) {
                ((ChatSpeakerViewHolder) holder).bind(mChatRoomSpeakerList.get(position));
            }
        }

        @Override
        public void onBindViewHolder(@NonNull RecyclerView.ViewHolder holder, int position, @NonNull List<Object> payloads) {
            if (payloads.contains(HIGHLIGHT_ON)) {
                ((ChatSpeakerViewHolder) holder).updateHighlight(true);
            } else if (payloads.contains(HIGHLIGHT_OFF)) {
                ((ChatSpeakerViewHolder) holder).updateHighlight(false);
            } else {
                super.onBindViewHolder(holder, position, payloads);
            }
        }

        @Override
        public int getItemCount() {
            return mChatRoomSpeakerList.size();
        }

        public void setSpeakerList(List<MeetingUserInfo> chatRoomUserInfoList) {
            mChatRoomSpeakerList.clear();
            if (chatRoomUserInfoList != null) {
                mChatRoomSpeakerList.addAll(chatRoomUserInfoList);
            }
            notifyDataSetChanged();
        }

        public void updateHighlight(Set<String> uids) {
            for (int i = 0; i < mChatRoomSpeakerList.size(); i++) {
                MeetingUserInfo info = mChatRoomSpeakerList.get(i);
                if (uids.contains(info.user_id) && info.is_mic_on) {
                    notifyItemChanged(i, HIGHLIGHT_ON);
                } else {
                    notifyItemChanged(i, HIGHLIGHT_OFF);
                }
            }
        }
    }

    private static class ChatSpeakerViewHolder extends RecyclerView.ViewHolder {

        private final View mHighlight;
        private final TextView mUserNamePrefix;
        private final TextView mUserName;

        public ChatSpeakerViewHolder(@NonNull View itemView) {
            super(itemView);
            mHighlight = itemView.findViewById(R.id.item_voice_speaker_highlight);
            mUserNamePrefix = itemView.findViewById(R.id.item_voice_speaker_avatar);
            mUserName = itemView.findViewById(R.id.item_voice_speaker_name);
        }

        public void bind(MeetingUserInfo info) {
            if (info == null) {
                mUserNamePrefix.setText("");
                mUserName.setText("");
                updateHighlight(false);
            } else {
                String userName = info.user_name;
                mUserName.setText(userName);
                if (!TextUtils.isEmpty(userName)) {
                    mUserNamePrefix.setText(userName.substring(0, 1));
                } else {
                    mUserNamePrefix.setText("");
                }
            }
        }

        public void updateHighlight(boolean isHighlight) {
            mHighlight.setVisibility(isHighlight ? View.VISIBLE : View.INVISIBLE);
        }
    }
}
