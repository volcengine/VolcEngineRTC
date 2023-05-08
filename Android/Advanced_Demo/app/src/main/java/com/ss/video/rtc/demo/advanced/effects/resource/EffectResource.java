package com.ss.video.rtc.demo.advanced.effects.resource;

import android.content.Context;

import com.ss.video.rtc.demo.advanced.effects.utils.CVUtils;
import com.ss.video.rtc.demo.basic_module.utils.Utilities;

import java.io.File;

/**
 * 美颜资源管理类
 * 1.负责资源的拷贝
 * 2.负责各种资源路径的获取
 */
public class EffectResource {

    private static final String LICENSE_NAME = "";

    /**
     * 获取证书文件路径
     */
    public static String getLicensePath() {
        return Utilities.getApplicationContext().getExternalFilesDir("assets").getAbsolutePath()
                + "/resource/cvlab/LicenseBag.bundle" + LICENSE_NAME;
    }

    /**
     * 获取模型文件路径
     */
    public static String getModelPath() {
        return Utilities.getApplicationContext().getExternalFilesDir("assets").getAbsolutePath()
                + "/resource/cvlab/ModelResource.bundle";
    }

    /**
     * 获取美颜文件路径
     */
    public static String getBeautyPath() {
        return Utilities.getApplicationContext().getExternalFilesDir("assets").getAbsolutePath()
                + "/resource/cvlab/ComposeMakeup.bundle/ComposeMakeup/beauty_Android_live";
    }

    /**
     * 获取美形文件路径
     */
    public static String getReshapePath() {
        return Utilities.getApplicationContext().getExternalFilesDir("assets").getAbsolutePath()
                + "/resource/cvlab/ComposeMakeup.bundle/ComposeMakeup/reshape_live";
    }

    /**
     * 获取人像模型文件路径
     */
    public static String getEffectPortraitPath() {
        return getStickerPathByName("matting_bg");
    }

    /**
     * 获取贴纸文件路径
     * @param name 贴纸文件名称
     */
    public static String getStickerPathByName(String name) {
        return Utilities.getApplicationContext().getExternalFilesDir("assets").getAbsolutePath()
                + "/resource/cvlab/StickerResource.bundle/stickers/" + name;
    }

    /**
     * 获取滤镜文件路径
     * @param name 滤镜文件名称
     */
    public static String getFilterPathByName(String name) {
        return Utilities.getApplicationContext().getExternalFilesDir("assets").getAbsolutePath()
                + "/resource/cvlab/FilterResource.bundle/Filter/" + name;
    }

    /**
     * 初始化美颜资源文件
     * 将安装包内的资源文件拷贝到外部存储上
     */
    public static void initVideoEffectResource() {
        Context context = Utilities.getApplicationContext();
        // 每次重新拷贝证书文件
        File licensePath = new File(getExternalResourcePath(), "cvlab/LicenseBag.bundle");
        licensePath.deleteOnExit();
        CVUtils.copyAssetFolder(context, "cvlab/LicenseBag.bundle", licensePath.getAbsolutePath());

        File modelPath = new File(getExternalResourcePath(), "cvlab/ModelResource.bundle");
        if (!modelPath.exists()) {
            CVUtils.copyAssetFolder(context, "cvlab/ModelResource.bundle", modelPath.getAbsolutePath());
        }
        File stickerPath = new File(getExternalResourcePath(), "cvlab/StickerResource.bundle");
        if (!stickerPath.exists()) {
            CVUtils.copyAssetFolder(context, "cvlab/StickerResource.bundle", stickerPath.getAbsolutePath());
        }
        File filterPath = new File(getExternalResourcePath(), "cvlab/FilterResource.bundle");
        if (!filterPath.exists()) {
            CVUtils.copyAssetFolder(context, "cvlab/FilterResource.bundle", filterPath.getAbsolutePath());
        }
        File composerPath = new File(getExternalResourcePath(), "cvlab/ComposeMakeup.bundle");
        if (!composerPath.exists()) {
            CVUtils.copyAssetFolder(context, "cvlab/ComposeMakeup.bundle", composerPath.getAbsolutePath());
        }
        File virtualPicturePath = new File(getExternalResourcePath(), "virtual_background.png");
        if (!virtualPicturePath.exists()) {
            CVUtils.copyAssetFile(context, "virtual_background.png", virtualPicturePath.getAbsolutePath());
        }
    }

    public static String getExternalResourcePath() {
        return Utilities.getApplicationContext().getExternalFilesDir("assets").getAbsolutePath() + "/resource/";
    }
}
