package com.faceunity.nama.entity;

/**
 * DESC：美妆-组合妆容
 * Created on 2021/4/26
 */
public class MakeupCombinationBean {

    private String key;//名称标识
    private int imageRes;//图片
    private int desRes;//描述
    private String bundlePath;//资源句柄
    private double intensity = 0.7;//强度

    public MakeupCombinationBean(String key, int imageRes, int desRes, String bundlePath) {
        this.key = key;
        this.imageRes = imageRes;
        this.desRes = desRes;
        this.bundlePath = bundlePath;
    }

    public String getKey() {
        return key;
    }

    public void setKey(String key) {
        this.key = key;
    }

    public int getImageRes() {
        return imageRes;
    }

    public void setImageRes(int imageRes) {
        this.imageRes = imageRes;
    }

    public int getDesRes() {
        return desRes;
    }

    public void setDesRes(int desRes) {
        this.desRes = desRes;
    }

    public String getBundlePath() {
        return bundlePath;
    }

    public void setBundlePath(String bundlePath) {
        this.bundlePath = bundlePath;
    }

    public double getIntensity() {
        return intensity;
    }

    public void setIntensity(double intensity) {
        this.intensity = intensity;
    }
}
