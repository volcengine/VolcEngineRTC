package com.ss.video.rtc.demo.meetingrtcdemo.voicechat;

import android.content.Intent;
import android.os.Bundle;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.ss.video.rtc.demo.basic_module.acivities.BaseActivity;
import com.ss.video.rtc.demo.basic_module.utils.WindowUtils;
import com.ss.video.rtc.demo.meetingrtcdemo.R;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.CSRefreshMeetingsEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.MeetingEventManager;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.TokenExpiredEvent;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.MeetingRoomInfo;
import com.ss.video.rtc.demo.meetingrtcdemo.resource.Constants;

import org.greenrobot.eventbus.Subscribe;
import org.greenrobot.eventbus.ThreadMode;

import java.util.LinkedList;
import java.util.List;

public class ChatRoomListActivity extends BaseActivity {

    private ChatRoomListAdapter mChatRoomListAdapter;

    private final ChatRoomListAdapter.OnChatInfoClickListener mOnCharInfoClick = info -> {
        Intent intent = new Intent(ChatRoomListActivity.this, ChatRoomActivity.class);
        intent.putExtra(Constants.EXTRA_KEY_MEETING_ID, info.room_id);
        intent.putExtra(Constants.EXTRA_KEY_USER_NAME, info.host_name);
        intent.putExtra(Constants.EXTRA_KEY_IS_CREATE_ROOM, false);
        startActivity(intent);
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        VoiceChatDataManger.init();
        setContentView(R.layout.activity_chat_room_list);
    }

    @Override
    protected void onGlobalLayoutCompleted() {
        super.onGlobalLayoutCompleted();

        ImageView backArrow = findViewById(R.id.title_bar_left_iv);
        backArrow.setImageResource(R.drawable.back_arrow);
        backArrow.setOnClickListener(v -> finish());
        TextView title = findViewById(R.id.title_bar_title_tv);
        title.setText("语音沙龙");
        TextView rightRv = findViewById(R.id.title_bar_right_tv);
        rightRv.setText("刷新");
        rightRv.setOnClickListener((v) -> getRoomList());

        RecyclerView chatRoomListRv = findViewById(R.id.voice_chat_list_rv);
        chatRoomListRv.setLayoutManager(new LinearLayoutManager(this, RecyclerView.VERTICAL, false));
        mChatRoomListAdapter = new ChatRoomListAdapter(mOnCharInfoClick);
        chatRoomListRv.setAdapter(mChatRoomListAdapter);

        findViewById(R.id.voice_chat_list_create_room).setOnClickListener((v) -> {
            startActivity(new Intent(ChatRoomListActivity.this, CreateChatRoomActivity.class));
        });

        MeetingEventManager.register(this);
    }

    @Override
    protected void setupStatusBar() {
        WindowUtils.setLayoutFullScreen(getWindow());
    }

    @Override
    protected void onResume() {
        super.onResume();
        getRoomList();
    }

    @Override
    public void finish() {
        super.finish();
        VoiceChatDataManger.release();
        MeetingEventManager.unregister(this);
    }

    private void getRoomList() {
        VoiceChatDataManger.requestRoomList();
    }

    private void setRoomList(List<MeetingRoomInfo> infoList) {
        List<MeetingRoomInfo> list = new LinkedList<>();
        if (infoList != null) {
            list.addAll(infoList);
        }
        mChatRoomListAdapter.setData(list);
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onCSRefreshMeetingsEvent(CSRefreshMeetingsEvent event) {
        setRoomList(event.meetings);
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onTokenExpiredEvent(TokenExpiredEvent event) {
        finish();
    }
}
