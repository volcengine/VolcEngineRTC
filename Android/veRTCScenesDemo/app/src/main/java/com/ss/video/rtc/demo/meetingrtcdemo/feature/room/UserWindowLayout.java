package com.ss.video.rtc.demo.meetingrtcdemo.feature.room;

import android.content.Context;
import android.util.AttributeSet;
import android.view.LayoutInflater;
import android.view.SurfaceView;
import android.view.View;
import android.widget.FrameLayout;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.TextView;

import com.ss.video.rtc.demo.basic_module.utils.Utilities;
import com.ss.video.rtc.demo.meetingrtcdemo.R;
import com.ss.video.rtc.demo.meetingrtcdemo.core.MeetingDataManager;
import com.ss.video.rtc.demo.meetingrtcdemo.core.MeetingRTCManager;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.MeetingUserInfo;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.VideoCanvasWrapper;
import com.ss.video.rtc.demo.meetingrtcdemo.resource.Constants;

public class UserWindowLayout extends RelativeLayout {

    public MeetingUserInfo mMeetingUserInfo;
    public View mTalkStatus;
    public View mBigTalkStatus;
    public TextView mUidPrefix;
    public TextView mBigUid;
    public TextView mSmallUid;
    public TextView mBigHostTag;
    public TextView mSmallHostTag;
    public ImageView mBigScreenShareTag;
    public ImageView mSmallScreenShareTag;
    public FrameLayout mVideoContainer;
    public LinearLayout mBigTags;
    public LinearLayout mSmallTags;

    private final Runnable mAutoDismissRunnable = () -> {
        if (mMeetingUserInfo == null) {
            return;
        }
        if (mMeetingUserInfo.is_mic_on && MeetingDataManager.getUserVolume(mMeetingUserInfo.user_id)
                >= Constants.VOLUME_OVERFLOW_THRESHOLD) {
            if (mMeetingUserInfo.is_camera_on) {
                mBigTalkStatus.setVisibility(View.INVISIBLE);
                mTalkStatus.setVisibility(View.VISIBLE);
            } else {
                mBigTalkStatus.setVisibility(View.VISIBLE);
                mTalkStatus.setVisibility(View.INVISIBLE);
            }
        } else {
            mBigTalkStatus.setVisibility(View.INVISIBLE);
            mTalkStatus.setVisibility(View.INVISIBLE);
        }
    };

    public UserWindowLayout(Context context) {
        this(context, null);
    }

    public UserWindowLayout(Context context, AttributeSet attrs) {
        this(context, attrs, 0);
    }

    public UserWindowLayout(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        LayoutInflater.from(context).inflate(R.layout.layout_user_window, this);
        mTalkStatus = findViewById(R.id.meeting_user_talking);
        mBigTalkStatus = findViewById(R.id.meeting_user_big_highlight);
        mUidPrefix = findViewById(R.id.meeting_user_big_uid);
        mBigUid = findViewById(R.id.meeting_user_big_full_id);
        mSmallUid = findViewById(R.id.meeting_user_small_full_id);
        mBigScreenShareTag = findViewById(R.id.meeting_user_big_share_screen_status);
        mSmallScreenShareTag = findViewById(R.id.meeting_user_small_share_screen_status);
        mBigHostTag = findViewById(R.id.meeting_user_big_host_status);
        mSmallHostTag = findViewById(R.id.meeting_user_small_host_status);
        mVideoContainer = findViewById(R.id.meeting_view_container);
        mBigTags = findViewById(R.id.meeting_user_big_tags);
        mSmallTags = findViewById(R.id.meeting_user_small_tags);

        mBigTags.setVisibility(View.GONE);
        mSmallTags.setVisibility(View.GONE);
    }

    public void bind(MeetingUserInfo info) {
        if (info == null) {
            mTalkStatus.setVisibility(View.INVISIBLE);
            mBigTalkStatus.setVisibility(View.INVISIBLE);
            mUidPrefix.setVisibility(View.VISIBLE);
            mBigUid.setVisibility(View.VISIBLE);
            mBigTags.setVisibility(View.GONE);
            mSmallTags.setVisibility(View.GONE);
            mUidPrefix.setText("");
            mBigUid.setText("");
            mMeetingUserInfo = null;
            mVideoContainer.removeAllViews();
        } else {
            String uid = info.user_id;
            String userName = info.user_name;
            String originUid = mMeetingUserInfo == null ? "" : mMeetingUserInfo.user_id;
            if (uid == null || !uid.equals(originUid) || !info.is_camera_on) {
                mVideoContainer.removeAllViews();
            }
            if (info.is_camera_on) {
                mUidPrefix.setVisibility(View.GONE);
                mBigUid.setVisibility(View.GONE);
                mBigTags.setVisibility(View.GONE);
                mSmallUid.setVisibility(View.VISIBLE);
                mSmallUid.setText(userName);
                mSmallTags.setVisibility(View.VISIBLE);
                mSmallHostTag.setVisibility(info.is_host ? View.VISIBLE : View.GONE);
                mSmallScreenShareTag.setVisibility(info.is_sharing ? View.VISIBLE : View.GONE);

                if (mVideoContainer.getChildCount() == 0) {
                    VideoCanvasWrapper wrapper = MeetingDataManager.getRenderView(uid);
                    if (wrapper == null) {
                        wrapper = MeetingDataManager.addOrUpdateRenderView(uid, true);
                    }
                    if (MeetingDataManager.isSelf(uid)) {
                        MeetingRTCManager.setupLocalVideo(wrapper.videoCanvas);
                    } else {
                        MeetingRTCManager.setupRemoteVideo(wrapper.videoCanvas);
                    }
                    SurfaceView view = wrapper.getSurfaceView();
                    if (view != null && view.getParent() != mVideoContainer) {
                        Utilities.removeFromParent(view);
                        mVideoContainer.addView(view, new FrameLayout.LayoutParams(
                                FrameLayout.LayoutParams.MATCH_PARENT,
                                FrameLayout.LayoutParams.MATCH_PARENT));
                    }
                }
            } else {
                mUidPrefix.setVisibility(View.VISIBLE);
                mBigUid.setVisibility(View.VISIBLE);
                mBigTags.setVisibility(View.VISIBLE);
                mUidPrefix.setText(userName == null ? "" : userName.substring(0, 1));
                mBigUid.setText(userName);
                mBigHostTag.setVisibility(info.is_host ? View.VISIBLE : View.GONE);
                mBigScreenShareTag.setVisibility(info.is_sharing ? View.VISIBLE : View.GONE);
                mSmallTags.setVisibility(View.GONE);
                mVideoContainer.removeAllViews();
            }

            mTalkStatus.removeCallbacks(mAutoDismissRunnable);
            if (info.is_mic_on) {
                if (MeetingDataManager.getUserVolume(info.user_id) >= Constants.VOLUME_OVERFLOW_THRESHOLD) {
                    if (info.is_camera_on) {
                        mBigTalkStatus.setVisibility(View.INVISIBLE);
                        mTalkStatus.setVisibility(View.VISIBLE);
                    } else {
                        mBigTalkStatus.setVisibility(View.VISIBLE);
                        mTalkStatus.setVisibility(View.INVISIBLE);
                    }
                    mTalkStatus.postDelayed(mAutoDismissRunnable, Constants.VOLUME_INTERVAL_MS);
                } else {
                    mTalkStatus.setVisibility(View.INVISIBLE);
                    mBigTalkStatus.setVisibility(View.INVISIBLE);
                }
            } else {
                mBigTalkStatus.setVisibility(View.INVISIBLE);
                mTalkStatus.setVisibility(View.INVISIBLE);
            }

            mMeetingUserInfo = info.deepCopy(new MeetingUserInfo());
        }
    }
}
