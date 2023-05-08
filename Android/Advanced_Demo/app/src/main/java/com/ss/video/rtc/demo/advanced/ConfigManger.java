package com.ss.video.rtc.demo.advanced;

import com.bytedance.realx.base.ThreadUtils;
import com.ss.video.rtc.demo.basic_module.utils.SPUtils;
import com.ss.video.rtc.demo.advanced.entity.VideoConfigEntity;

import java.util.ArrayList;
import java.util.List;

public class ConfigManger {
    public static final String SP_KEY_VIDEO_CONFIG = "video_config";
    private VideoConfigEntity videoConfig;
    private final List<ConfigObserver> observers = new ArrayList<>(1);

    private static class Inner {
        private static final ConfigManger sInstance = new ConfigManger();
    }

    public static ConfigManger getInstance() {
        return Inner.sInstance;
    }

    private ConfigManger() {
        ensureVideoConfig();
    }

    private void ensureVideoConfig() {
        if (videoConfig == null) {
            VideoConfigEntity defaultObj = new VideoConfigEntity();
            videoConfig = SPUtils.getObject(SP_KEY_VIDEO_CONFIG, VideoConfigEntity.class, defaultObj);
        }
    }


    public void addObserver(ConfigObserver observer){
        ThreadUtils.checkIsOnMainThread();
        observers.add(observer);
    }

    public void removeObserver(ConfigObserver observer){
        ThreadUtils.checkIsOnMainThread();
        if (observer == null){
            return;
        }
        observers.remove(observer);
    }

    public VideoConfigEntity getVideoConfig() {
        ensureVideoConfig();
        return videoConfig;
    }

    public boolean isCustomCapture() {
        return videoConfig.mCustomCapture;
    }

    public boolean isCustomRender() {
        return videoConfig.mCustomRender;
    }

    public void updateConfig(VideoConfigEntity videoConfig) {
        updateConfig(videoConfig, true);
    }

    public void updateConfig(VideoConfigEntity videoConfig, boolean save) {
        this.videoConfig = videoConfig;
        if (save) {
            SPUtils.putObject(SP_KEY_VIDEO_CONFIG, videoConfig);
        }
        for (ConfigObserver observer : observers){
            observer.onConfigChange(videoConfig);
        }
    }

    public interface ConfigObserver {
        void onConfigChange(VideoConfigEntity config);
    }

    public void release() {
        this.videoConfig = null;
    }
}
