package com.ss.video.rtc.demo.meetingrtcdemo.feature.room;

import android.content.Context;
import android.util.AttributeSet;
import android.view.View;
import android.widget.FrameLayout;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.ss.video.rtc.demo.basic_module.utils.Utilities;
import com.ss.video.rtc.demo.meetingrtcdemo.core.MeetingDataManager;
import com.ss.video.rtc.demo.meetingrtcdemo.entity.MeetingUserInfo;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class RoomMainLayout extends FrameLayout {

    private boolean mIsSpeechMode = false;

    private boolean mIsClear = false;

    private final List<UserWindowLayout> mUserWindowLayoutList = new ArrayList<>();
    private final List<MeetingUserInfo> mMeetingUserInfoList = new ArrayList<>();
    private MeetingUserInfo mFirstUserInfo;
    private MeetingUserInfo mSecondUserInfo;

    private View.OnClickListener mOnStopShareClick;
    private View.OnClickListener mOnExpandClick;

    private RoomSpeechLayout mSpeechLayout;

    public RoomMainLayout(@NonNull Context context) {
        super(context);
        initView();
    }

    public RoomMainLayout(@NonNull Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
        initView();
    }

    public RoomMainLayout(@NonNull Context context, @Nullable AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        initView();
    }

    @Override
    protected void onSizeChanged(int w, int h, int oldw, int oldh) {
        super.onSizeChanged(w, h, oldw, oldh);
        if (mIsClear) {
            return;
        }
        if (mIsSpeechMode) {
            bindSpeechData(mFirstUserInfo, mSecondUserInfo, mOnStopShareClick, mOnExpandClick);
        } else {
            bindGridData(mMeetingUserInfoList);
        }
    }

    private void initView() {
        mFirstUserInfo = null;
        mSecondUserInfo = null;
        mMeetingUserInfoList.clear();
        for (int i = 0; i < 6; i++) {
            UserWindowLayout layout = new UserWindowLayout(Utilities.getApplicationContext());
            mUserWindowLayoutList.add(layout);
            addView(layout);
            layout.bind(null);
            layout.setVisibility(View.GONE);
        }
        mSpeechLayout = new RoomSpeechLayout(getContext());
        addView(mSpeechLayout);
        mSpeechLayout.setVisibility(View.GONE);
    }

    public void bindGridData(List<MeetingUserInfo> meetingUserInfoList) {
        mIsClear = false;
        if (mIsSpeechMode) {
            mIsSpeechMode = false;
            dismissSpeech();
        }
        if (meetingUserInfoList == null || meetingUserInfoList.isEmpty()) {
            dismissAllGrid();
            return;
        }
        mMeetingUserInfoList.clear();
        int maxTimes = Math.min(meetingUserInfoList.size(), MeetingDataManager.MAX_SHOW_USER_COUNT);
        for (int i = 0; i < maxTimes; i++) {
            mMeetingUserInfoList.add(meetingUserInfoList.get(i));
        }
        checkGridViewSize();
        int showSize = mMeetingUserInfoList.size();
        for (int i = 0; i < showSize; i++) {
            mUserWindowLayoutList.get(i).bind(mMeetingUserInfoList.get(i));
        }
        UserWindowLayout layout;
        for (int i = showSize; i < mUserWindowLayoutList.size(); i++) {
            layout = mUserWindowLayoutList.get(i);
            layout.bind(null);
            layout.setVisibility(View.GONE);
        }
    }

    public void bindSpeechData(MeetingUserInfo firstInfo, MeetingUserInfo secondInfo,
                               View.OnClickListener onStopShareClick,
                               View.OnClickListener onExpandClick) {
        mIsClear = false;
        if (!mIsSpeechMode) {
            mIsSpeechMode = true;
            dismissAllGrid();
        }
        mFirstUserInfo = firstInfo;
        mSecondUserInfo = secondInfo;
        mOnStopShareClick = onStopShareClick;
        mOnExpandClick = onExpandClick;

        int viewWidth = getWidth() / 2;
        int viewHeight = viewWidth * 3 / 4;

        int goneStartIndex;
        if (secondInfo == null) {
            UserWindowLayout first = mUserWindowLayoutList.get(0);
            first.setVisibility(View.VISIBLE);

            LayoutParams params = (FrameLayout.LayoutParams) first.getLayoutParams();
            params.width = viewWidth;
            params.height = viewHeight;
            params.setMargins(viewWidth / 2, 0, 0, 0);
            first.setLayoutParams(params);
            first.bind(firstInfo);
            if (first.getParent() == null || first.getParent() != this) {
                Utilities.removeFromParent(first);
                addView(first);
            }
            goneStartIndex = 1;
        } else {
            UserWindowLayout first = mUserWindowLayoutList.get(0);
            first.setVisibility(View.VISIBLE);
            LayoutParams paramsFirst = (FrameLayout.LayoutParams) first.getLayoutParams();
            paramsFirst.width = viewWidth;
            paramsFirst.height = viewHeight;
            paramsFirst.setMargins(0, 0, 0, 0);
            first.setLayoutParams(paramsFirst);
            first.bind(firstInfo);
            if (first.getParent() == null || first.getParent() != this) {
                Utilities.removeFromParent(first);
                addView(first);
            }

            UserWindowLayout second = mUserWindowLayoutList.get(1);
            second.setVisibility(View.VISIBLE);
            LayoutParams paramsSecond = (FrameLayout.LayoutParams) second.getLayoutParams();
            paramsSecond.width = viewWidth;
            paramsSecond.height = viewHeight;
            paramsSecond.setMargins(viewWidth, 0, 0, 0);
            second.setLayoutParams(paramsSecond);
            second.bind(secondInfo);
            if (second.getParent() == null || second.getParent() != this) {
                Utilities.removeFromParent(second);
                addView(second);
            }
            goneStartIndex = 2;
        }
        mSpeechLayout.bindData(onStopShareClick, onExpandClick);
        mSpeechLayout.setVisibility(View.VISIBLE);
        LayoutParams paramsScreen = (FrameLayout.LayoutParams) mSpeechLayout.getLayoutParams();
        paramsScreen.width = getWidth();
        paramsScreen.height = getHeight() - viewHeight;
        paramsScreen.setMargins(0, viewHeight, 0, 0);
        mSpeechLayout.setLayoutParams(paramsScreen);
        if (mSpeechLayout.getParent() == null || mSpeechLayout.getParent() != this) {
            Utilities.removeFromParent(mSpeechLayout);
            addView(mSpeechLayout);
        }
        UserWindowLayout layout;
        for (int i = goneStartIndex; i < mUserWindowLayoutList.size(); i++) {
            layout = mUserWindowLayoutList.get(i);
            layout.bind(null);
            layout.setVisibility(View.GONE);
        }
    }

    private void dismissAllGrid() {
        mMeetingUserInfoList.clear();
        for (UserWindowLayout view : mUserWindowLayoutList) {
            view.bind(null);
            view.setVisibility(View.GONE);
        }
    }

    private void dismissSpeech() {
        mFirstUserInfo = null;
        mSecondUserInfo = null;
        mSpeechLayout.setVisibility(View.GONE);
        mSpeechLayout.clear();
        for (UserWindowLayout view : mUserWindowLayoutList) {
            view.bind(null);
            view.setVisibility(View.GONE);
        }
    }

    private void checkGridViewSize() {
        int showSize = mMeetingUserInfoList.size();
        int parentWidth = getWidth();
        int parentHeight = getHeight();
        int viewWidth;
        int viewHeight;
        if (showSize < 2) {
            viewWidth = parentWidth;
            viewHeight = parentHeight;
        } else if (showSize < 3) {
            viewWidth = parentWidth;
            viewHeight = parentHeight / 2;
        } else if (showSize < 5) {
            viewWidth = parentWidth / 2;
            viewHeight = parentHeight / 2;
        } else {
            viewWidth = parentWidth / 2;
            viewHeight = parentHeight / 3;
        }

        if (showSize <= 2) {
            LayoutParams params0 = (FrameLayout.LayoutParams) mUserWindowLayoutList.get(0).getLayoutParams();
            params0.width = viewWidth;
            params0.height = viewHeight;
            params0.setMargins(0, 0, 0, 0);
            mUserWindowLayoutList.get(0).setLayoutParams(params0);

            LayoutParams params1 = (FrameLayout.LayoutParams) mUserWindowLayoutList.get(1).getLayoutParams();
            params1.width = viewWidth;
            params1.height = viewHeight;
            params1.setMargins(0, viewHeight, 0, 0);
            mUserWindowLayoutList.get(1).setLayoutParams(params1);
        } else {
            for (int i = 0; i < Math.min(showSize, mUserWindowLayoutList.size()); i++) {
                LayoutParams params = (FrameLayout.LayoutParams) mUserWindowLayoutList.get(i).getLayoutParams();
                params.width = viewWidth;
                params.height = viewHeight;
                params.setMargins((i % 2) * viewWidth, (i / 2) * viewHeight, 0, 0);
                mUserWindowLayoutList.get(i).setLayoutParams(params);
            }
        }

        UserWindowLayout layout;
        for (int i = 0; i < mUserWindowLayoutList.size(); i++) {
            layout = mUserWindowLayoutList.get(i);
            if (layout.getParent() == null) {
                addView(layout);
            }
            layout.setVisibility(i < showSize ? View.VISIBLE : View.GONE);
        }
    }

    public void onCameraStatusChanged(String uid, boolean on) {
        MeetingUserInfo info;
        for (int i = 0; i < mMeetingUserInfoList.size(); i++) {
            info = mMeetingUserInfoList.get(i);
            if (uid.equals(info.user_id)) {
                info.is_camera_on = on;
                mUserWindowLayoutList.get(i).bind(info);
            }
        }
    }

    public void onHostChanged(String formerUid, String currentUid) {
        MeetingUserInfo info;
        for (int i = 0; i < mMeetingUserInfoList.size(); i++) {
            info = mMeetingUserInfoList.get(i);
            if (formerUid.equals(info.user_id)) {
                info.is_host = false;
                mUserWindowLayoutList.get(i).bind(info);
            } else if (currentUid.equals(info.user_id)) {
                info.is_host = true;
                mUserWindowLayoutList.get(i).bind(info);
            }
        }
    }

    public void clear() {
        removeAllViews();
        mIsClear = true;
    }

    public void onVolumeEvent(Map<String, Integer> uidVolumeMap) {
        if (uidVolumeMap == null || uidVolumeMap.isEmpty()) {
            return;
        }
        MeetingUserInfo info;
        for (int i = 0; i < mMeetingUserInfoList.size(); i++) {
            info = mMeetingUserInfoList.get(i);
            if (uidVolumeMap.containsKey(info.user_id)) {
                info.volume = uidVolumeMap.get(info.user_id);
                mUserWindowLayoutList.get(i).bind(info);
            }
        }
    }
}
