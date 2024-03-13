package com.faceunity.nama.infe;

import com.faceunity.nama.entity.BodyBeautyBean;
import com.faceunity.nama.entity.ModelAttributeData;

import java.util.ArrayList;
import java.util.HashMap;

/**
 * DESC：数据构造工厂抽象类
 * Created on 2021/4/26
 */
public abstract class AbstractBodyBeautyDataFactory {


    /**
     * 获取美体参数集合
     * @return
     */
    public abstract ArrayList<BodyBeautyBean> getBodyBeautyParam();



    /**
     * 获取美体项目数据扩展模型
     * @return
     */
    public abstract HashMap<String, ModelAttributeData> getModelAttributeRange();


    /**
     * 根据名称标识获取对应的值
     *
     * @param key String  标识
     * @return Double  值
     */
    public abstract double getParamIntensity(String key);

    /**
     * 根据名称标识更新对应的值
     *
     * @param key String  标识
     * @return Double  值
     */
    public abstract void updateParamIntensity(String key, double value);

    /**
     * 美体开关
     *
     * @param enable Boolean
     */
    public abstract void enableBodyBeauty(boolean enable);

    public abstract boolean isBodyBeautyEnabled();

}
