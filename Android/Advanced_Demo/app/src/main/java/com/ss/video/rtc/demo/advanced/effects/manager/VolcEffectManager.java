package com.ss.video.rtc.demo.advanced.effects.manager;

import android.graphics.Color;
import android.text.TextUtils;
import android.util.Log;

import com.ss.bytertc.engine.RTCVideo;
import com.ss.bytertc.engine.data.VirtualBackgroundSource;
import com.ss.bytertc.engine.data.VirtualBackgroundSourceType;
import com.ss.bytertc.engine.video.IVideoEffect;
import com.ss.bytertc.engine.video.RTCVideoEffect;
import com.ss.video.rtc.demo.advanced.effects.resource.EffectResource;
import com.ss.video.rtc.demo.basic_module.utils.Utilities;

import java.io.File;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * 具体调用 RTC 实现美颜功能类
 */
public class VolcEffectManager {

    private static final String TAG = "VolcBeautyManager";

    private RTCVideo mRTCVideo;

    private IVideoEffect mRTCVideoEffect;

    /**
     * 初始化美颜相关资源
     * @param rtcVideo RTCVideo 对象
     */
    public void initEffect(RTCVideo rtcVideo) {
        mRTCVideo = rtcVideo;
        if (mRTCVideo == null) {
            return;
        }

        mRTCVideoEffect = rtcVideo.getVideoEffectInterface();

        String licPath = EffectResource.getLicensePath();
        String modelPath = EffectResource.getModelPath();

        int res =  mRTCVideoEffect.initCVResource(licPath,modelPath);
        Log.i(TAG, "initCVResource: " + res);


        int enableEffectRes = mRTCVideoEffect.enableVideoEffect();
        Log.i(TAG, "enableVideoEffect: " + enableEffectRes);

        List<String> effectNodePaths = Arrays.asList(EffectResource.getBeautyPath(), EffectResource.getReshapePath());
        int effectNodesRes = mRTCVideoEffect.setEffectNodes(effectNodePaths);
        Log.i(TAG, "setVideoEffectNodes: " + effectNodesRes);
    }

    /**
     * 修改美颜强度
     * @param key 美颜的键值
     * @param value 具体的值，取值范围[0, 1]，值越大越明显
     */
    public void onBeautyEffectChanged(String key, float value) {
        if (mRTCVideoEffect == null) {
            return;
        }
        mRTCVideoEffect.updateEffectNode(EffectResource.getBeautyPath(), key, value);
    }

    /**
     * 修改美形强度
     * @param key 美形的键值
     * @param value 具体的值，取值范围[0, 1]，值越大越明显
     */
    public void onReshapeEffectChanged(String key, float value) {
        if (mRTCVideoEffect == null) {
            return;
        }
        mRTCVideoEffect.updateEffectNode(EffectResource.getReshapePath(), key, value);
    }

    /**
     * 修改滤镜强度
     * @param key 滤镜名称
     * @param value 具体的值，取值范围[0, 1]，值越大越明显
     */
    public void onFilterEffectChanged(String key, float value) {
        if (mRTCVideoEffect == null) {
            return;
        }
        mRTCVideoEffect.setColorFilter(EffectResource.getFilterPathByName(key));
        mRTCVideoEffect.setColorFilterIntensity(value);
    }

    /**
     * 修改贴纸
     * @param key 贴纸名称
     * @param selected 是否选中
     */
    public void onStickerEffectClicked(String key, boolean selected) {
        if (mRTCVideoEffect == null) {
            return;
        }
        ArrayList<String> pathList = new ArrayList<>();
        pathList.add(EffectResource.getBeautyPath());
        pathList.add(EffectResource.getReshapePath());
        if (selected) {
            pathList.add(EffectResource.getStickerPathByName(key));
        }
        mRTCVideoEffect.setEffectNodes(pathList);
    }

    /**
     * 使用背景分割功能
     * @param type 背景分割的类型
     * @param selected 是否选中
     */
    public void onVirtualEffectClicked(String type, boolean selected) {
        if (mRTCVideoEffect == null) {
            return;
        }
        if (selected) {
            VirtualBackgroundSource backgroundSource = new VirtualBackgroundSource();
            if (TextUtils.equals(type, "color")) {
                backgroundSource.sourceType = VirtualBackgroundSourceType.COLOR;
                backgroundSource.sourceColor = Color.parseColor("#1278ff");
            } else if (TextUtils.equals(type, "image")) {
                backgroundSource.sourceType = VirtualBackgroundSourceType.IMAGE;
                backgroundSource.sourcePath = EffectResource.getExternalResourcePath() + File.separator + "virtual_background.png";
            } else {
                return;
            }

            String portraitPath = EffectResource.getEffectPortraitPath();
            mRTCVideoEffect.enableVirtualBackground(portraitPath,backgroundSource);
        } else {
            mRTCVideoEffect.disableVirtualBackground();
        }
    }
}
