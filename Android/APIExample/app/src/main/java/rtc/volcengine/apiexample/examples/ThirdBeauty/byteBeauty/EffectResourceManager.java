package rtc.volcengine.apiexample.examples.ThirdBeauty.byteBeauty;

import android.content.Context;


import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import rtc.volcengine.apiexample.common.Constants;

/**
 * 美颜资源管理类
 * 1.负责资源的拷贝
 * 2.负责各种资源路径的获取
 */
public class EffectResourceManager {

    private Context context;
    
    public EffectResourceManager(Context context) {
        this.context = context;
    }
    
    /**
     * 获取证书文件路径
     */
    public String getLicensePath() {
        return context.getApplicationContext().getExternalFilesDir("assets").getAbsolutePath()
                + "/resource/cvlab/LicenseBag.bundle" + Constants.BYTE_EFFECT_LIC_NAME;
    }

    /**
     * 获取模型文件路径
     */
    public String getModelPath() {
        return context.getApplicationContext().getExternalFilesDir("assets").getAbsolutePath()
                + "/resource/cvlab/ModelResource.bundle";
    }

    /**
     * 获取美颜文件路径
     */
    public String getBeautyPath() {
        return context.getApplicationContext().getExternalFilesDir("assets").getAbsolutePath()
                + "/resource/cvlab/ComposeMakeup.bundle/ComposeMakeup/beauty_Android_lite";
    }

    /**
     * 获取美形文件路径
     */
    public String getReshapePath() {
        return context.getApplicationContext().getExternalFilesDir("assets").getAbsolutePath()
                + "/resource/cvlab/ComposeMakeup.bundle/ComposeMakeup/reshape_lite";
    }

    /**
     * 获取人像模型文件路径
     */
    public String getEffectPortraitPath() {
        return getStickerPathByName("matting_bg");
    }

    /**
     * 获取贴纸文件路径
     * @param name 贴纸文件名称
     */
    public String getStickerPathByName(String name) {
        return context.getApplicationContext().getExternalFilesDir("assets").getAbsolutePath()
                + "/resource/cvlab/StickerResource.bundle/stickers/" + name;
    }

    /**
     * 获取滤镜文件路径
     * @param name 滤镜文件名称
     */
    public String getFilterPathByName(String name) {
        return context.getApplicationContext().getExternalFilesDir("assets").getAbsolutePath()
                + "/resource/cvlab/FilterResource.bundle/Filter/" + name;
    }

    /**
     * 初始化美颜资源文件
     * 将安装包内的资源文件拷贝到外部存储上
     */
    public void initVideoEffectResource() {
        // 每次重新拷贝证书文件
        File licensePath = new File(getExternalResourcePath(), "cvlab/LicenseBag.bundle");
        licensePath.deleteOnExit();
        copyAssetFolder(context, "cvlab/LicenseBag.bundle", licensePath.getAbsolutePath());

        File modelPath = new File(getExternalResourcePath(), "cvlab/ModelResource.bundle");
        if (!modelPath.exists()) {
            copyAssetFolder(context, "cvlab/ModelResource.bundle", modelPath.getAbsolutePath());
        }
        File stickerPath = new File(getExternalResourcePath(), "cvlab/StickerResource.bundle");
        if (!stickerPath.exists()) {
            copyAssetFolder(context, "cvlab/StickerResource.bundle", stickerPath.getAbsolutePath());
        }
        File filterPath = new File(getExternalResourcePath(), "cvlab/FilterResource.bundle");
        if (!filterPath.exists()) {
            copyAssetFolder(context, "cvlab/FilterResource.bundle", filterPath.getAbsolutePath());
        }
        File composerPath = new File(getExternalResourcePath(), "cvlab/ComposeMakeup.bundle");
        if (!composerPath.exists()) {
            copyAssetFolder(context, "cvlab/ComposeMakeup.bundle", composerPath.getAbsolutePath());
        }
        File virtualPicturePath = new File(getExternalResourcePath(), "virtual_background.png");
        if (!virtualPicturePath.exists()) {
            copyAssetFile(context, "virtual_background.png", virtualPicturePath.getAbsolutePath());
        }
    }

    public String getExternalResourcePath() {
        return context.getApplicationContext().getExternalFilesDir("assets").getAbsolutePath() + "/resource/";
    }

    public boolean copyAssetFolder(Context context, String srcName, String dstName) {
        try {
            boolean result = true;
            String fileList[] = context.getAssets().list(srcName);
            if (fileList == null) return false;

            if (fileList.length == 0) {
                result = copyAssetFile(context, srcName, dstName);
            } else {
                File file = new File(dstName);
                result = file.mkdirs();
                for (String filename : fileList) {
                    result &= copyAssetFolder(context, srcName + File.separator + filename, dstName + File.separator + filename);
                }
            }
            return result;
        } catch (IOException e) {
            e.printStackTrace();
            return false;
        }
    }

    public boolean copyAssetFile(Context context, String srcName, String dstName) {
        try {
            InputStream in = context.getAssets().open(srcName);
            File outFile = new File(dstName);
            OutputStream out = new FileOutputStream(outFile);
            byte[] buffer = new byte[1024];
            int read;
            while ((read = in.read(buffer)) != -1) {
                out.write(buffer, 0, read);
            }
            in.close();
            out.close();
            return true;
        } catch (IOException e) {
            e.printStackTrace();
            return false;
        }
    }
}
