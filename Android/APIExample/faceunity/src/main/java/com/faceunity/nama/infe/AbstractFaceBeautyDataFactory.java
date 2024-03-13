package com.faceunity.nama.infe;

import com.faceunity.nama.entity.FaceBeautyBean;
import com.faceunity.nama.entity.FaceBeautyFilterBean;
import com.faceunity.nama.entity.ModelAttributeData;

import java.util.ArrayList;
import java.util.HashMap;

/**
 * DESC：数据构造工厂抽象类
 * Created on 2021/4/26
 */
public abstract class AbstractFaceBeautyDataFactory {


    /**
     * 美肤底部菜单数据
     *
     * @return
     */
    public abstract ArrayList<FaceBeautyBean> getSkinBeauty();


    /**
     * 美型底部菜单数据
     *
     * @return
     */
    public abstract ArrayList<FaceBeautyBean> getShapeBeauty();


    /**
     * 滤镜底部菜单数据
     *
     * @return
     */
    public abstract ArrayList<FaceBeautyFilterBean> getBeautyFilters();

    /**
     * 获取当前滤镜下标
     *
     * @return
     */
    public abstract int getCurrentFilterIndex();

    /**
     * 设置当前滤镜下标
     *
     * @param currentFilterIndex
     */
    public abstract void setCurrentFilterIndex(int currentFilterIndex);


    /**
     * 美颜项目数据扩展模型
     *
     * @return
     */
    public abstract HashMap<String, ModelAttributeData> getModelAttributeRange();

    /**
     * 切换滤镜
     *
     * @param name      String
     * @param intensity Double
     */
    public abstract void onFilterSelected(String name, double intensity, int resDes);


    /**
     * 更改滤镜强度
     *
     * @param intensity Double
     */
    public abstract void updateFilterIntensity(double intensity);

    /**
     * 美颜开关
     *
     * @param enable Boolean
     */
    public abstract void enableFaceBeauty(boolean enable);

    /**
     * 获取单项强度
     *
     * @param key String
     * @return Double
     */
    public abstract double getParamIntensity(String key);

    /**
     * 设置单项强度
     *
     * @param key   String
     * @param value Double
     */
    public abstract void updateParamIntensity(String key, double value);

    public abstract boolean isFaceBeautyEnabled();

}
