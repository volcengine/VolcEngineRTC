package com.ss.video.rtc.demo.meetingrtcdemo.feature.history;

import android.content.Intent;
import android.net.Uri;

import com.ss.video.rtc.demo.basic_module.utils.AppExecutors;
import com.ss.video.rtc.demo.meetingrtcdemo.core.MeetingDataManager;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.MeetingRecordInfo;

import java.util.LinkedList;
import java.util.List;

public class HistoryPresenter {

    private final HistoryActivity mHistoryActivity;

    public HistoryPresenter(HistoryActivity historyActivity) {
        mHistoryActivity = historyActivity;
    }

    public void loadData(boolean isMine) {
        AppExecutors.networkIO().submit(() -> {
            List<MeetingRecordInfo> infoList = MeetingDataManager.getManager().getHistoryMeetingRecord();
            if (mHistoryActivity != null && !mHistoryActivity.isFinishing()) {
                List<MeetingRecordInfo> filterList = new LinkedList<>();
                for (MeetingRecordInfo info : infoList) {
                    if (info.video_holder == isMine) {
                        filterList.add(info);
                    }
                }
                mHistoryActivity.runOnUiThread(() -> mHistoryActivity.showData(filterList));
            }
        });
    }

    public void downloadMeetingFile(String url) {
        if (mHistoryActivity != null && !mHistoryActivity.isFinishing()) {
            Intent i = new Intent(Intent.ACTION_VIEW);
            i.setData(Uri.parse(url));
            mHistoryActivity.startActivity(i);
        }
    }
}
