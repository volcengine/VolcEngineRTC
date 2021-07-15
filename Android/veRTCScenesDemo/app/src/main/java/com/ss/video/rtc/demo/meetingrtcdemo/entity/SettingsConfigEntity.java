package com.ss.video.rtc.demo.meetingrtcdemo.entity;

import android.util.Pair;

import com.google.gson.annotations.SerializedName;
import com.ss.video.rtc.demo.basic_module.utils.Utilities;
import com.ss.video.rtc.demo.meetingrtcdemo.R;

import java.util.Objects;

public class SettingsConfigEntity {

    @SerializedName("index")
    public int index = 3;

    @SerializedName("screen_index")
    public int screenIndex = 3;

    @SerializedName("bitRate")
    private int mBitRate = 400;

    @SerializedName("frameRate")
    private int mFrameRate = 15;

    @SerializedName("screenBitRate")
    private int mScreenBitRate = 400;

    @SerializedName("screenFrameRate")
    private int mScreenFrameRate = 15;

    @SerializedName("enableLog")
    public boolean enableLog = false;

    public String[] getResolutions() {
        return Utilities.getApplicationContext().getResources().getStringArray(R.array.video_resolution);
    }

    public Pair<Integer, Integer> getResolution() {
        String str = getResolutions()[index];
        /*
        format: width * height
        example: 1920 * 1080
         */
        String[] split = str.split("\\*");
        return new Pair<>(Integer.parseInt(split[1].trim()),
                Integer.parseInt(split[0].trim()));
    }
    public Pair<Integer, Integer> getScreenResolution() {
        String str = getResolutions()[screenIndex];
        /*
        format: width * height
        example: 1920 * 1080
         */
        String[] split = str.split("\\*");
        return new Pair<>(Integer.parseInt(split[1].trim()),
                Integer.parseInt(split[0].trim()));
    }

    public Pair<Integer, Integer> getBitRatePair() {
        String[] bitRates = Utilities.getApplicationContext()
                .getResources().getStringArray(R.array.video_bit_rate);
        String str = bitRates[index];
        //format: min - max
        String[] split = str.split("-");
        return new Pair<>(Integer.parseInt(split[0].trim()),
                Integer.parseInt(split[1].trim()));
    }

    public Pair<Integer, Integer> getScreenBitRatePair() {
        String[] bitRates = Utilities.getApplicationContext()
                .getResources().getStringArray(R.array.video_bit_rate);
        String str = bitRates[screenIndex];
        //format: min - max
        String[] split = str.split("-");
        return new Pair<>(Integer.parseInt(split[0].trim()),
                Integer.parseInt(split[1].trim()));
    }

    public int getBitRate() {
        Pair<Integer, Integer> pair = getBitRatePair();
        if (mBitRate >= 0) {
            if (mBitRate > pair.second) {
                return (mBitRate = pair.second);
            } else if (mBitRate < pair.first) {
                return (mBitRate = pair.first);
            } else {
                return mBitRate;
            }
        }
        return (mBitRate = pair.second);
    }

    public int getScreenBitRate() {
        Pair<Integer, Integer> pair = getBitRatePair();
        if (mScreenBitRate >= 0) {
            if (mScreenBitRate > pair.second) {
                return (mScreenBitRate = pair.second);
            } else if (mScreenBitRate < pair.first) {
                return (mScreenBitRate = pair.first);
            } else {
                return mScreenBitRate;
            }
        }
        return (mScreenBitRate = pair.second);
    }

    public void setBitRate(int bitRate) {
        mBitRate = bitRate;
    }

    public void setScreenBitRate(int bitRate) {
        mScreenBitRate = bitRate;
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
        return (mFrameRate = Integer.parseInt(frameRates[0].trim()));
    }

    public int getScreenFrameRate() {
        if (mScreenFrameRate > 0) {
            return mScreenFrameRate;
        }
        String[] frameRates = getFrameRates();
        return (mScreenFrameRate = Integer.parseInt(frameRates[0].trim()));
    }

    public void setFrameRate(int frameRate) {
        mFrameRate = frameRate;
    }

    public void setScreenFrameRate(int frameRate) {
        mScreenFrameRate = frameRate;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        SettingsConfigEntity that = (SettingsConfigEntity) o;
        return index == that.index &&
                mBitRate == that.mBitRate &&
                mFrameRate == that.mFrameRate &&
                enableLog == that.enableLog;
    }

    @Override
    public int hashCode() {
        return Objects.hash(index, mBitRate, mFrameRate, enableLog);
    }

    public SettingsConfigEntity deepCopy() {
        SettingsConfigEntity newEntity = new SettingsConfigEntity();
        newEntity.index = this.index;
        newEntity.screenIndex = this.screenIndex;
        newEntity.mFrameRate = this.mFrameRate;
        newEntity.mScreenFrameRate = this.mScreenFrameRate;
        newEntity.mBitRate = this.mBitRate;
        newEntity.mScreenBitRate = this.mScreenBitRate;
        newEntity.enableLog = this.enableLog;
        return newEntity;
    }
}
