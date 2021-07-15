package com.ss.video.rtc.demo.meetingrtcdemo.feature.history;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.ss.video.rtc.demo.meetingrtcdemo.R;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.MeetingRecordInfo;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.LinkedList;
import java.util.List;
import java.util.Locale;

public class HistoryAdapter extends RecyclerView.Adapter<RecyclerView.ViewHolder> {

    private final List<MeetingRecordInfo> mMeetingRecordInfoList = new LinkedList<>();
    private final OnClickRecord mOnClickRecord;

    public HistoryAdapter(OnClickRecord onClickRecord) {
        mOnClickRecord = onClickRecord;
    }

    @NonNull
    @Override
    public RecyclerView.ViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.list_item_history, parent, false);
        return new HistoryViewHolder(view, mOnClickRecord);
    }

    @Override
    public void onBindViewHolder(@NonNull RecyclerView.ViewHolder holder, int position) {
        if (holder instanceof HistoryViewHolder) {
            ((HistoryViewHolder) holder).bind(mMeetingRecordInfoList.get(position));
        }
    }

    @Override
    public int getItemCount() {
        return mMeetingRecordInfoList.size();
    }

    public void setRecordList(List<MeetingRecordInfo> list) {
        if (list == null || list.isEmpty()) {
            return;
        }
        mMeetingRecordInfoList.clear();
        mMeetingRecordInfoList.addAll(list);
        notifyDataSetChanged();
    }

    static class HistoryViewHolder extends RecyclerView.ViewHolder {

        private final TextView mUrl;
        private final OnClickRecord mOnClickRecord;

        public HistoryViewHolder(@NonNull View itemView, OnClickRecord onClickRecord) {
            super(itemView);
            mUrl = itemView.findViewById(R.id.meeting_record_url);
            mOnClickRecord = onClickRecord;
        }

        public void bind(MeetingRecordInfo info) {
            mUrl.setText(formatTime(info.created_at));
            itemView.setOnClickListener(v -> mOnClickRecord.onClick(info.download_url));
            itemView.setOnLongClickListener((v) -> {
                mOnClickRecord.onLongClick(info);
                return true;
            });
        }

        private String formatTime(long time){
            SimpleDateFormat sdr = new SimpleDateFormat("yyyy/MM/dd HH:mm:ss", Locale.CHINA);
            return sdr.format(new Date(time / 1000000));
        }
    }

    public interface OnClickRecord {
        void onClick(String url);
        void onLongClick(MeetingRecordInfo info);
    }
}