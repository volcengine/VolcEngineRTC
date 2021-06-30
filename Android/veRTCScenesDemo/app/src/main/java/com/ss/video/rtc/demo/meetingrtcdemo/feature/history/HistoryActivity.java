package com.ss.video.rtc.demo.meetingrtcdemo.feature.history;

import android.content.Intent;
import android.os.Bundle;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.Nullable;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.ss.video.rtc.demo.basic_module.acivities.BaseActivity;
import com.ss.video.rtc.demo.meetingrtcdemo.R;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.MeetingEndEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.MeetingEventManager;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.MeetingRecordInfo;
import com.ss.video.rtc.demo.meetingrtcdemo.resource.Constants;

import org.greenrobot.eventbus.Subscribe;
import org.greenrobot.eventbus.ThreadMode;

import java.util.List;

import static androidx.recyclerview.widget.RecyclerView.VERTICAL;

public class HistoryActivity extends BaseActivity {

    private HistoryPresenter mHistoryPresenter;
    private HistoryAdapter mHistoryAdapter;

    private String mRefer = "";

    private final HistoryAdapter.OnClickRecord mOnClickRecord = url -> mHistoryPresenter.downloadMeetingFile(url);

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_history);

        Intent intent = getIntent();
        mRefer = intent.getStringExtra(Constants.REFER_KEY);
    }

    @Override
    protected void onGlobalLayoutCompleted() {
        super.onGlobalLayoutCompleted();

        ImageView backArrow = findViewById(R.id.title_bar_left_iv);
        backArrow.setImageResource(R.drawable.back_arrow);
        backArrow.setOnClickListener(v -> finish());
        TextView title = findViewById(R.id.title_bar_title_tv);
        title.setText(R.string.history_title);

        RecyclerView recyclerView = findViewById(R.id.meeting_record_recycler_view);
        recyclerView.setLayoutManager(new LinearLayoutManager(this, VERTICAL, false));
        mHistoryAdapter = new HistoryAdapter(mOnClickRecord);
        recyclerView.setAdapter(mHistoryAdapter);

        mHistoryPresenter = new HistoryPresenter(this);
        mHistoryPresenter.loadData();
        MeetingEventManager.register(this);
    }

    @Override
    public void finish() {
        super.finish();
        MeetingEventManager.unregister(this);
    }

    public void showData(List<MeetingRecordInfo> infoList) {
        mHistoryAdapter.setRecordList(infoList);
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onMeetingEndEvent(MeetingEndEvent endEvent) {
        if (Constants.REFER_ROOM.equals(mRefer)) {
            finish();
        }
    }
}