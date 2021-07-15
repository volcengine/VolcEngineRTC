package com.ss.video.rtc.demo.meetingrtcdemo.voicechat;

import android.text.TextUtils;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.ss.video.rtc.demo.meetingrtcdemo.R;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.MeetingRoomInfo;

import java.util.LinkedList;
import java.util.List;

public class ChatRoomListAdapter extends RecyclerView.Adapter<RecyclerView.ViewHolder> {

    private final List<MeetingRoomInfo> mChatRoomInfoList = new LinkedList<>();
    private final OnChatInfoClickListener mOnChatInfoClick;

    public ChatRoomListAdapter(OnChatInfoClickListener onCharInfoClick) {
        mOnChatInfoClick = onCharInfoClick;
    }

    @NonNull
    @Override
    public RecyclerView.ViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.item_chat_room_layout, parent, false);
        return new ChatRoomListViewHolder(view, mOnChatInfoClick);
    }

    @Override
    public void onBindViewHolder(@NonNull RecyclerView.ViewHolder holder, int position) {
        if (holder instanceof ChatRoomListViewHolder) {
            ((ChatRoomListViewHolder) holder).bind(mChatRoomInfoList.get(position));
        }
    }

    public void setData(List<MeetingRoomInfo> chatRoomInfoList) {
        mChatRoomInfoList.clear();
        if (chatRoomInfoList != null) {
            mChatRoomInfoList.addAll(chatRoomInfoList);
        }
        notifyDataSetChanged();
    }

    @Override
    public int getItemCount() {
        return mChatRoomInfoList.size();
    }

    private static class ChatRoomListViewHolder extends RecyclerView.ViewHolder {

        private final TextView mTitle;
        private final TextView mNamePrefix;
        private final TextView mHostname;
        private final TextView mUserCount;
        private final TextView mRoomId;
        private MeetingRoomInfo mChatRoomInfo;

        public ChatRoomListViewHolder(@NonNull View itemView, OnChatInfoClickListener onChatInfoClick) {
            super(itemView);
            mTitle = itemView.findViewById(R.id.item_chat_room_layout_title);
            mNamePrefix = itemView.findViewById(R.id.item_chat_room_layout_avatar);
            mHostname = itemView.findViewById(R.id.item_chat_room_layout_user_name);
            mUserCount = itemView.findViewById(R.id.item_chat_room_layout_room_info);
            mRoomId = itemView.findViewById(R.id.item_chat_room_layout_room_id);
            itemView.setOnClickListener(v -> {
                if (mChatRoomInfo != null) {
                    onChatInfoClick.onChatInfoClick(mChatRoomInfo);
                }
            });
        }

        public void bind(MeetingRoomInfo info) {
            mChatRoomInfo = info;
            if (info == null) {
                mTitle.setText("");
                mNamePrefix.setText("");
                mHostname.setText("");
                mUserCount.setText("");
                mRoomId.setText("");
                return;
            }
            String hostName = info.host_name;
            mTitle.setText(info.room_name);
            if (!TextUtils.isEmpty(hostName)) {
                mNamePrefix.setText(hostName.substring(0, 1));
            } else {
                mNamePrefix.setText("");
            }
            mHostname.setText(hostName);
            mUserCount.setText(String.format("房内总人数 %d / 连麦人数 %d", info.user_counts, info.micon_counts));
            if (info.room_id == null) {
                info.room_id = "";
            }
            mRoomId.setText(String.format("ID: %s", info.room_id));
        }
    }

    public interface OnChatInfoClickListener {
        void onChatInfoClick(MeetingRoomInfo info);
    }
}
