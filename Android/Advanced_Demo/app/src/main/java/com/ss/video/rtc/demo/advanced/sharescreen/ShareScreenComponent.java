package com.ss.video.rtc.demo.advanced.sharescreen;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.graphics.Color;
import android.media.projection.MediaProjectionManager;
import android.os.Build;
import android.util.Pair;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.MainThread;
import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.lifecycle.Lifecycle;
import androidx.lifecycle.LifecycleEventObserver;
import androidx.lifecycle.LifecycleOwner;

import com.ss.bytertc.engine.RTCRoom;
import com.ss.bytertc.engine.RTCVideo;
import com.ss.bytertc.engine.VideoEncoderConfig;
import com.ss.bytertc.engine.data.ScreenMediaType;
import com.ss.bytertc.engine.data.StreamIndex;
import com.ss.bytertc.engine.data.VideoSourceType;
import com.ss.bytertc.engine.type.MediaStreamType;
import com.ss.rtc.demo.advanced.R;
import com.ss.video.rtc.demo.advanced.ConfigManger;
import com.ss.video.rtc.demo.advanced.entity.VideoConfigEntity;
import com.ss.video.rtc.demo.advanced.utils.CommonUtil;
import com.ss.video.rtc.demo.basic_module.utils.Utilities;

import org.webrtc.RXScreenCaptureService;

public class ShareScreenComponent implements LifecycleEventObserver {
    private MediaProjectionManager mProjectionManager;
    private TextView mSelfStatusTv;
    private ImageView mSelfStatusIv;
    private final RTCVideo mRTCVideo;
    private final RTCRoom mRTCRoom;
    private final Activity mHostActivity;
    private boolean mSharing;
    private final VideoConfigEntity mVideoConfig = ConfigManger.getInstance().getVideoConfig();

    /**
     * @param rtcVideo    火山RTC引擎
     * @param hostActivity 宿主Activity
     */
    public ShareScreenComponent(@NonNull RTCVideo rtcVideo, @NonNull RTCRoom rtcRoom, @NonNull Activity hostActivity) {
        mRTCVideo = rtcVideo;
        mRTCRoom = rtcRoom;
        mHostActivity = hostActivity;
    }

    /**
     * 设置屏幕共享状态状态TextView 和 停止、重起按钮
     *
     * @param statusTv    共享状态状态TextView
     * @param turnOnOffIv 停止、重起按钮
     */
    public void setStatusTvAndBtn(@NonNull TextView statusTv, @NonNull ImageView turnOnOffIv) {
        mSelfStatusTv = statusTv;
        mSelfStatusIv = turnOnOffIv;
        turnOnOffIv.setOnClickListener(v -> {
            if (mSharing) {
                stopScreenSharing();
            } else {
                startScreenSharing();
            }
        });
        refreshStatus();
    }

    private void refreshStatus() {
        if (mSelfStatusTv != null) {
            mSelfStatusTv.setText(mSharing ? "正在屏幕共享" : "等待屏幕共享");
        }
        if (mSelfStatusIv != null) {
            mSelfStatusIv.setImageResource(mSharing ? R.drawable.screen_share_on : R.drawable.screen_share_off);
            mSelfStatusIv.setColorFilter(mSharing ? Color.TRANSPARENT : Color.GRAY);
        }
    }

    /**
     * 宿主生命周期回调
     */
    @Override
    public void onStateChanged(@NonNull LifecycleOwner source, @NonNull Lifecycle.Event event) {
        if (event == Lifecycle.Event.ON_DESTROY) {
            stopScreenSharing();
        }
    }

    /**
     * 开启媒体（屏幕音频、屏幕视频）
     */
    public void startScreenSharing() {
        requestPermissionForScreenSharing(mHostActivity);
    }

    public static final int REQUEST_CODE_OF_SCREEN_SHARING = 101;

    /*** 向系统发起屏幕共享的权限请求*/
    private void requestPermissionForScreenSharing(Activity activity) {
        if (activity.isFinishing()) {
            CommonUtil.showShortToast(Utilities.getApplicationContext(), "请求屏幕共享权限失败:activity is null/finishing");
            return;
        }
        if (Build.VERSION.SDK_INT < Build.VERSION_CODES.LOLLIPOP) {
            CommonUtil.showShortToast(activity, "当前系统版本过低，无法支持屏幕共享");
            return;
        }
        if (mProjectionManager == null) {
            mProjectionManager = (MediaProjectionManager) Utilities.getApplicationContext().getSystemService(Context.MEDIA_PROJECTION_SERVICE);
        }
        if (mProjectionManager != null) {
            activity.startActivityForResult(mProjectionManager.createScreenCaptureIntent(), REQUEST_CODE_OF_SCREEN_SHARING);
        } else {
            CommonUtil.showShortToast(activity, "当前系统版本过低，无法支持屏幕共享");
        }
    }

    /***
     * 宿主Activity/Fragment的onActivityResult中调用
     * 处理系统对屏幕分享权限请求的返回:如果用户同意授权开启前台服务
     * */
    public void handlePermissionResult(int resultCode, @Nullable Intent data) {
        if (resultCode == Activity.RESULT_OK) {
            startScreenCapture(data);
        } else {
            CommonUtil.showShortToast(Utilities.getApplicationContext(), "开启屏幕共享失败");
        }
    }

    private void startScreenCapture(Intent data) {
        startRXScreenCaptureService(data);
        //编码参数
        VideoEncoderConfig config = new VideoEncoderConfig();
        Pair<Integer, Integer> videoSize = mVideoConfig.getResolution();
        config.width = (videoSize.first != null && videoSize.first > 0) ? videoSize.first : 720;
        config.height = (videoSize.second != null && videoSize.second > 0) ? videoSize.second : 1280;
        config.frameRate = mVideoConfig.getFrameRate() > 0 ? mVideoConfig.getFrameRate() : 15;
        config.maxBitrate = mVideoConfig.getBitRate() > 0 ? mVideoConfig.getBitRate() : 1600;
        mRTCVideo.setScreenVideoEncoderConfig(config);
        // 开启屏幕视频数据采集
        mRTCVideo.startScreenCapture(ScreenMediaType.SCREEN_MEDIA_TYPE_VIDEO_AND_AUDIO, data);
    }

    private void startRXScreenCaptureService(@Nullable Intent data) {
        Context context = Utilities.getApplicationContext();
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.Q) {
            Intent iData = new Intent();
            iData.putExtra(RXScreenCaptureService.KEY_LARGE_ICON, R.drawable.launcher_quick_start);
            iData.putExtra(RXScreenCaptureService.KEY_SMALL_ICON, R.drawable.launcher_quick_start);
            iData.putExtra(RXScreenCaptureService.KEY_LAUNCH_ACTIVITY, mHostActivity.getClass().getCanonicalName());
            iData.putExtra(RXScreenCaptureService.KEY_CONTENT_TEXT, "正在录制/投射您的屏幕");
            iData.putExtra(RXScreenCaptureService.KEY_RESULT_DATA, data);
            context.startForegroundService(RXScreenCaptureService.getServiceIntent(context, RXScreenCaptureService.COMMAND_LAUNCH, iData));
        }
    }

    /**
     * 停止屏幕音视频采集
     */
    @MainThread
    public void stopScreenSharing() {
        mRTCVideo.stopScreenCapture();
    }

    /**
     * 停止屏幕流发布
     */
    @MainThread
    public void unPublishScreen() {
        mSharing = false;
        refreshStatus();
        mRTCRoom.unpublishScreen(MediaStreamType.RTC_MEDIA_STREAM_TYPE_BOTH);
    }

    /**
     * 向RTC房间推屏幕流
     */
    @MainThread
    public void publishScreen() {
        mSharing = true;
        refreshStatus();
        mRTCRoom.publishScreen(MediaStreamType.RTC_MEDIA_STREAM_TYPE_BOTH);
        mRTCVideo.setVideoSourceType(StreamIndex.STREAM_INDEX_SCREEN, VideoSourceType.VIDEO_SOURCE_TYPE_INTERNAL);
    }
}
