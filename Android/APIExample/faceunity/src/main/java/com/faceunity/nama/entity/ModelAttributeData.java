package com.faceunity.nama.entity;

/**
 * 模型单项补充模型
 */
public class ModelAttributeData {
    private double defaultV = 0.0;//默认值
    private double standV = 0.0;//无变化时候的基准值
    private double minRange = 0.0;//范围最小值
    private double maxRange = 1.0;//范围最大值

    public ModelAttributeData(double defaultV, double standV, double minRange, double maxRange) {
        this.defaultV = defaultV;
        this.standV = standV;
        this.minRange = minRange;
        this.maxRange = maxRange;
    }


    public double getDefaultV() {
        return defaultV;
    }

    public void setDefaultV(double defaultV) {
        this.defaultV = defaultV;
    }

    public double getStandV() {
        return standV;
    }

    public void setStandV(double standV) {
        this.standV = standV;
    }

    public double getMinRange() {
        return minRange;
    }

    public void setMinRange(double minRange) {
        this.minRange = minRange;
    }

    public double getMaxRange() {
        return maxRange;
    }

    public void setMaxRange(double maxRange) {
        this.maxRange = maxRange;
    }
}
