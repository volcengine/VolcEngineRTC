package com.ss.video.rtc.demo.advanced.entity;

import android.util.Pair;

import com.ss.rtc.demo.advanced.R;
import com.ss.video.rtc.demo.basic_module.utils.Utilities;
import com.google.gson.annotations.SerializedName;

public class VideoConfigEntity {

    public static final int VIDEO_SOURCE_TYPE_CAMERA = 1;
    public static final int VIDEO_SOURCE_TYPE_SCREEN = 2;

    @SerializedName("mVideoSource")
    public int mVideoSource = VIDEO_SOURCE_TYPE_CAMERA;

    @SerializedName("index")
    public int index = 0;

    @SerializedName("bitRate")
    private int mBitRate = -1;

    @SerializedName("frameRate")
    private int mFrameRate;

    @SerializedName("enableLog")
    public boolean enableLog = false;

    @SerializedName("customCapture")
    public boolean mCustomCapture = false;

    @SerializedName("customRender")
    public boolean mCustomRender = false;

    @SerializedName("localRenderMirror")
    public boolean mLocalRenderMirror = true;

    @SerializedName("localVideoFillMode")
    public int mLocalVideoFillMode = 1;

    @SerializedName("remoteVideoFillMode")
    public int mRemoteVideoFillMode = 1;

    @SerializedName("localVideoMirrorType")
    public int mLocalVideoMirrorType = 1;

    public static String[] getResolutions() {
        String[] resolutions = Utilities.getApplicationContext()
                .getResources().getStringArray(R.array.video_resolution);
        return resolutions;
    }

    public Pair<Integer, Integer> getResolution() {
        String str = getResolutions()[index];
        // 1920 * 1080
        // width * height
        String[] split = str.split("\\*");
        return new Pair<>(Integer.parseInt(split[1].trim()),
                Integer.parseInt(split[0].trim()));
    }

    public Pair<Integer, Integer> getBitRatePair() {
        String[] bitRates = Utilities.getApplicationContext()
                .getResources().getStringArray(R.array.video_bit_rate);
        String str = bitRates[index];
        // min - max
        String[] split = str.split("-");
        return new Pair<>(Integer.parseInt(split[0].trim()),
                Integer.parseInt(split[1].trim()));
    }

    public int getBitRate() {
        Pair<Integer, Integer> pair = getBitRatePair();
        if (mBitRate >= 0) {
            if (mBitRate > pair.second) {
                return (mBitRate = pair.second);
            }
            return mBitRate;
        }
        return (mBitRate = pair.second);
    }

    public void setBitRate(int bitRate) {
        mBitRate = bitRate;
    }

    public String[] getFrameRates() {
        String[] frameRates = Utilities.getApplicationContext()
                .getResources().getStringArray(R.array.video_frame_rate);
        String str = frameRates[index];
        String[] split = str.split("/");
        for (int i = 0; i < split.length; i++) {
            split[i] = split[i].trim();
        }
        return split;
    }

    public int getFrameRate() {
        if (mFrameRate > 0) {
            return mFrameRate;
        }
        String[] frameRates = getFrameRates();
        return (mFrameRate = Integer.parseInt(frameRates[2].trim()));
    }

    public void setFrameRate(int frameRate) {
        mFrameRate = frameRate;
    }

    public String[] getLocalVideoMirrorTypes() {
        String[] mirrorType = Utilities.getApplicationContext()
                .getResources().getStringArray(R.array.local_video_mirror_types);
        for (int i = 0; i < mirrorType.length; i++) {
            mirrorType[i] = mirrorType[i].trim();
        }
        return mirrorType;
    }

    public String getLocalVideoMirrorType() {
        String[] mirrorType = Utilities.getApplicationContext()
                .getResources().getStringArray(R.array.local_video_mirror_types);
        return mirrorType[mLocalVideoMirrorType];
    }

    public void setLocalVideoMirrorType(int mirrorType) {
        mLocalVideoMirrorType = mirrorType;
    }

}
