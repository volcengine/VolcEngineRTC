package com.faceunity.nama.entity;

/**
 * DESC：美颜滤镜
 * Created on 2021/4/26
 */
public class FaceBeautyFilterBean {

    private String key;//名称标识
    private int imageRes;//图片
    private int desRes;//描述
    private double intensity = 0.4;//强度

    public FaceBeautyFilterBean(String key, int imageRes, int desRes) {
        this.key = key;
        this.imageRes = imageRes;
        this.desRes = desRes;
    }

    public FaceBeautyFilterBean(String key, int imageRes, int desRes, double intensity) {
        this.key = key;
        this.imageRes = imageRes;
        this.desRes = desRes;
        this.intensity = intensity;
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

    public double getIntensity() {
        return intensity;
    }

    public void setIntensity(double intensity) {
        this.intensity = intensity;
    }
}
