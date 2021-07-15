package com.ss.video.rtc.demo.meetingrtcdemo.voicechat;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.ss.video.rtc.demo.meetingrtcdemo.R;

import java.util.LinkedList;
import java.util.List;

public class ChatRoomChatAdapter  extends RecyclerView.Adapter<RecyclerView.ViewHolder> {

    private final List<ChatMsgInfo> mMsgInfoList = new LinkedList<>();

    @NonNull
    @Override
    public RecyclerView.ViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.item_voice_chat_layout, parent, false);
        return new ChatViewHolder(view);
    }

    @Override
    public void onBindViewHolder(@NonNull RecyclerView.ViewHolder holder, int position) {
        if (holder instanceof ChatViewHolder) {
            ((ChatViewHolder) holder).bind(mMsgInfoList.get(position));
        }
    }

    @Override
    public int getItemCount() {
        return mMsgInfoList.size();
    }

    public void addChatMsgInfo(ChatMsgInfo info) {
        if (info == null) {
            return;
        }
        mMsgInfoList.add(info);
        notifyItemInserted(mMsgInfoList.size() - 1);
    }

    private static class ChatViewHolder extends RecyclerView.ViewHolder {

        private final TextView mChatTv;

        public ChatViewHolder(@NonNull View itemView) {
            super(itemView);
            mChatTv = (TextView) itemView;
        }

        public void bind(ChatMsgInfo info) {
            if (info != null) {
                mChatTv.setText(info.content);
            } else {
                mChatTv.setText("");
            }
        }
    }
}
