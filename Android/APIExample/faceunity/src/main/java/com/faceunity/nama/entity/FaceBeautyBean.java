package com.faceunity.nama.entity;

/**
 * DESC：美颜
 * Created on 2021/4/26
 */
public class FaceBeautyBean {

    private String key;//名称标识
    private int desRes;//描述
    private int closeRes;//图片
    private int openRes;//图片
    private boolean canUseFunction = true;

    public FaceBeautyBean(String key, int desRes, int closeRes, int openRes) {
        this.key = key;
        this.desRes = desRes;
        this.closeRes = closeRes;
        this.openRes = openRes;
        this.canUseFunction = true;
    }

    public FaceBeautyBean(String key, int desRes, int closeRes, int openRes,boolean canUseFunction) {
        this.key = key;
        this.desRes = desRes;
        this.closeRes = closeRes;
        this.openRes = openRes;
        this.canUseFunction = canUseFunction;
    }

    public String getKey() {
        return key;
    }

    public void setKey(String key) {
        this.key = key;
    }

    public int getDesRes() {
        return desRes;
    }

    public void setDesRes(int desRes) {
        this.desRes = desRes;
    }

    public int getCloseRes() {
        return closeRes;
    }

    public void setCloseRes(int closeRes) {
        this.closeRes = closeRes;
    }

    public int getOpenRes() {
        return openRes;
    }

    public void setOpenRes(int openRes) {
        this.openRes = openRes;
    }

    public boolean isCanUseFunction() {
        return canUseFunction;
    }

    public void setCanUseFunction(boolean canUseFunction) {
        this.canUseFunction = canUseFunction;
    }
}
