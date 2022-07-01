package com.ss.video.rtc.demo.advanced.effects.inner;

import android.content.Context;
import android.util.Log;

import com.ss.bytertc.engine.RTCEngine;
import com.ss.bytertc.engine.video.VideoFrame;
import com.ss.video.rtc.demo.advanced.Constants;
import com.ss.video.rtc.demo.advanced.effects.EffectControllerBase;
import com.ss.video.rtc.demo.advanced.utils.CVUtils;
import com.ss.video.rtc.demo.basic_module.utils.Utilities;

import java.io.File;
import java.util.ArrayList;
import java.util.List;

public class InnerCVVideoController extends EffectControllerBase {

    private static final String TAG = "InnerCVVideoController";

    public static Context mContext;

    private static InnerCVVideoController sInstance = new InnerCVVideoController();

    public InnerCVVideoController() {
        mContext = Utilities.getApplicationContext();
    }

    public static InnerCVVideoController getsInstance() {
        if (sInstance == null) {
            sInstance = new InnerCVVideoController();
        }
        return sInstance;
    }

    @Override
    public VideoFrame processVideoFrame(VideoFrame rtcVideoFrame) {
        return rtcVideoFrame;
    }

    @Override
    public List<String> getVideoEffectCompose() {
        List<String> list = new ArrayList<>();
        list.add(getByteComposePath());
        list.add(getByteShapePath());
        return list;
    }

    @Override
    public void init(RTCEngine engine) {
        super.init(engine);

        CVUtils.initVideoEffect();

        int licCheckRes = mRTCEngine.checkVideoEffectLicense(Utilities.getApplicationContext(), "");
        mRTCEngine.setVideoEffectAlgoModelPath("");
        int effectOpenRes = mRTCEngine.enableVideoEffect(true);
        Log.i(TAG, "check lic:" + licCheckRes +  " enable effect: " + effectOpenRes);
        setVideoEffectNodes(getVideoEffectCompose());

        String portraitPath = "";
        mRTCEngine.initVirtualBackground(Utilities.getApplicationContext(), "", portraitPath);
    }

    public void destroy() {
        super.destroy();

        sInstance = null;
    }

    /***** 设置美颜参数 ******/

    public void setVideoEffectNodes(List<String> paths) {
        mRTCEngine.setVideoEffectNodes(paths);
    }

    public void setVideoEffectColorFilter(String path) {
        path = getByteColorFilterPath() + path;
        mRTCEngine.setVideoEffectColorFilter(path);
    }

    public void setVideoEffectColorFilterIntensity(float intensity) {
        mRTCEngine.setVideoEffectColorFilterIntensity(intensity);
    }

    public void updateVideoEffectNode(String path, String key, float value) {
        mRTCEngine.updateVideoEffectNode(path, key, value);
    }

    // 绝对路径
    public void setSticker(String path, List<String> pathList) {
        setVideoEffectNodes(pathList);
    }

    public String getByteStickerPath() {
        return "";
    }

    public String getByteComposePath() {
        return "";
    }

    public String getByteShapePath() {
        return "";
    }

    public String getByteColorFilterPath() {
        return "";
    }
}
