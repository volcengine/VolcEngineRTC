package com.ss.video.rtc.demo.advanced.effects;

import com.ss.bytertc.engine.RTCEngine;
import com.ss.bytertc.engine.video.VideoFrame;

import java.util.ArrayList;
import java.util.List;

public interface IEffectController {
    public void init(RTCEngine engine);

    public void destroy();

    public void setVideoEffectNodes(ArrayList<String> paths);

    public void setVideoEffectColorFilter(String path);

    public void setVideoEffectColorFilterIntensity(float intensity);

    public void updateVideoEffectNode(String path, String key, float value);

    public void setSticker(String path, List<String> pathList);

    public VideoFrame processVideoFrame(VideoFrame frame);

    public List<String> getVideoEffectCompose();
}