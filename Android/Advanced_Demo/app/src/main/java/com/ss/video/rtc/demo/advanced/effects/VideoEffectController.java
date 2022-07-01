package com.ss.video.rtc.demo.advanced.effects;

import com.ss.bytertc.engine.RTCEngine;
import com.ss.bytertc.engine.video.VideoFrame;
import com.ss.video.rtc.demo.advanced.cfg.MemoryConfig;
import com.ss.video.rtc.demo.advanced.effects.constants.VideoEffectConstants;
import com.ss.video.rtc.demo.advanced.effects.inner.InnerCVVideoController;

import java.util.ArrayList;
import java.util.List;

public class VideoEffectController implements IEffectController {
    private static VideoEffectController sInstance;

    private RTCEngine mEngine = null;

    private IEffectController mCurrentEffectController;

    public static VideoEffectController getInstance() {
        if (sInstance == null) {
            sInstance = new VideoEffectController();
        }

        return sInstance;
    }

    public IEffectController getEffectController() {
        ensureEffectController();

        return mCurrentEffectController;
    }

    private void ensureEffectController() {
        if (mCurrentEffectController == null) {
            int effectType = MemoryConfig.getInt(VideoEffectConstants.KEY_EFFECT_TYPE, 0);
            switch (effectType) {
                case VideoEffectConstants.EFFECT_TYPE_INNER:
                    mCurrentEffectController = InnerCVVideoController.getsInstance();
                    break;
            }
        }
    }

    @Override
    public void init(RTCEngine engine) {
        mEngine = engine;
        getEffectController().init(mEngine);
    }

    @Override
    public void destroy() {
        getEffectController().destroy();
        mEngine = null;
        mCurrentEffectController = null;
    }

    @Override
    public void setVideoEffectNodes(ArrayList<String> paths) {
        getEffectController().setVideoEffectNodes(paths);
    }

    @Override
    public void setVideoEffectColorFilter(String path) {
        getEffectController().setVideoEffectColorFilter(path);
    }

    @Override
    public void setVideoEffectColorFilterIntensity(float intensity) {
        getEffectController().setVideoEffectColorFilterIntensity(intensity);
    }

    @Override
    public void updateVideoEffectNode(String path, String key, float value) {
        getEffectController().updateVideoEffectNode(path, key, value);
    }

    @Override
    public void setSticker(String path, List<String> pathList) {
        getEffectController().setSticker(path, pathList);
    }

    public VideoFrame processVideoFrame(VideoFrame frame) {
        return getEffectController().processVideoFrame(frame);
    }

    @Override
    public List<String> getVideoEffectCompose() {
        return getEffectController().getVideoEffectCompose();
    }
}
