package com.ss.video.rtc.demo.advanced.effects;

import com.ss.bytertc.engine.RTCEngine;
import com.ss.bytertc.engine.video.VideoFrame;

import java.util.ArrayList;
import java.util.List;

public abstract class EffectControllerBase implements IEffectController {
    protected RTCEngine mRTCEngine;

    @Override
    public void init(RTCEngine engine) {
        mRTCEngine = engine;
    }

    @Override
    public void destroy() {
        mRTCEngine = null;
    }

    @Override
    public void setVideoEffectNodes(ArrayList<String> paths) {

    }

    @Override
    public void setVideoEffectColorFilter(String path) {

    }

    @Override
    public void setVideoEffectColorFilterIntensity(float intensity) {

    }

    @Override
    public void updateVideoEffectNode(String path, String key, float value) {

    }

    @Override
    public void setSticker(String path, List<String> pathList) {

    }

    @Override
    public VideoFrame processVideoFrame(VideoFrame frame) {
        return null;
    }
}
