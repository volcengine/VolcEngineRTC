package com.ss.video.rtc.demo.meetingrtcdemo.feature.room;

import android.content.Context;
import android.util.AttributeSet;
import android.view.LayoutInflater;
import android.view.SurfaceView;
import android.view.View;
import android.view.ViewGroup;
import android.widget.FrameLayout;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.ss.video.rtc.demo.basic_module.utils.Utilities;
import com.ss.video.rtc.demo.meetingrtcdemo.R;
import com.ss.video.rtc.demo.meetingrtcdemo.core.MeetingDataManager;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.VideoCanvasWrapper;

public class RoomSpeechLayout extends FrameLayout {

    private View mStopShareView;
    private View mExpandView;
    private FrameLayout mScreenContainer;

    public RoomSpeechLayout(@NonNull Context context) {
        super(context);
        initView();
    }

    public RoomSpeechLayout(@NonNull Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
        initView();
    }

    public RoomSpeechLayout(@NonNull Context context, @Nullable AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        initView();
    }

    private void initView() {
        LayoutInflater.from(getContext()).inflate(R.layout.layout_room_speech_container, this, true);
        mStopShareView = findViewById(R.id.room_speech_share_status);
        mExpandView = findViewById(R.id.room_speech_full_screen);
        mScreenContainer = findViewById(R.id.room_speech_screen_container);
    }

    public void bindData(View.OnClickListener onStopShareClick, View.OnClickListener onClickExpand) {
        String screenUid = MeetingDataManager.getScreenShareUid();
        if (MeetingDataManager.isSelf(screenUid)) {
            mScreenContainer.removeAllViews();
            mStopShareView.setVisibility(View.VISIBLE);
            mStopShareView.setOnClickListener(onStopShareClick);
            mStopShareView.setEnabled(true);
            mExpandView.setVisibility(View.GONE);
            mExpandView.setOnClickListener(null);
        } else {
            mStopShareView.setVisibility(View.INVISIBLE);
            mStopShareView.setEnabled(false);
            VideoCanvasWrapper screenWrapper = MeetingDataManager.getScreenView();
            if (screenWrapper == null) {
                screenWrapper = MeetingDataManager.addOrUpdateScreenView(screenUid, true);
            }
            if (screenWrapper != null) {
                SurfaceView render = screenWrapper.getSurfaceView();
                if (render.getParent() == null || render.getParent() != mScreenContainer) {
                    Utilities.removeFromParent(render);
                    mScreenContainer.addView(render, new LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT));
                }
            }
            mExpandView.setVisibility(View.VISIBLE);
            mExpandView.setOnClickListener(onClickExpand);
        }
    }

    public void clear() {
        mScreenContainer.removeAllViews();
    }
}
