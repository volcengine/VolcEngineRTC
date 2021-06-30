package com.ss.video.rtc.demo.meetingrtcdemo.feature.room;

import android.content.Context;
import android.util.AttributeSet;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.FrameLayout;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.ss.video.rtc.demo.basic_module.utils.Utilities;
import com.ss.video.rtc.demo.meetingrtcdemo.R;
import com.ss.video.rtc.demo.meetingrtcdemo.core.MeetingDataManager;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.VideoCanvasWrapper;

public class FullScreenLayout extends FrameLayout {

    private FrameLayout mFullScreenContainer;
    private View mFullScreenShareStatus;
    private View mFullScreenHostStatus;
    private TextView mFullScreenUserName;
    private TextView mFullScreenStatus;

    public FullScreenLayout(@NonNull Context context) {
        super(context);
        initView();
    }

    public FullScreenLayout(@NonNull Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
        initView();
    }

    public FullScreenLayout(@NonNull Context context, @Nullable AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        initView();
    }

    private void initView() {
        LayoutInflater.from(getContext()).inflate(R.layout.layout_full_screen_container, this, true);
        mFullScreenContainer = findViewById(R.id.full_screen_render_container);
        mFullScreenShareStatus = findViewById(R.id.full_screen_share);
        mFullScreenHostStatus = findViewById(R.id.full_screen_host);
        mFullScreenUserName = findViewById(R.id.full_screen_name);
        mFullScreenStatus = findViewById(R.id.full_screen_stat);
    }

    public void bind(String uid, boolean isHost) {
        mFullScreenContainer.setVisibility(View.VISIBLE);
        mFullScreenShareStatus.setVisibility(View.VISIBLE);
        mFullScreenUserName.setVisibility(View.VISIBLE);

        mFullScreenUserName.setText(uid);
        mFullScreenHostStatus.setVisibility(isHost ? View.VISIBLE : View.GONE);

        VideoCanvasWrapper wrapper = MeetingDataManager.getScreenView();
        if (wrapper != null) {
            View view = wrapper.getSurfaceView();
            if (view != null) {
                if (view.getParent() == null || view.getParent() != mFullScreenContainer) {
                    Utilities.removeFromParent(view);
                    mFullScreenContainer.addView(view, new FrameLayout.LayoutParams(
                            ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT));
                }
            }
        }
    }

    public void bindStatus(String status) {
        mFullScreenStatus.setText(status);
    }
}
