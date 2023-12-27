package com.faceunity.nama.data;

import com.faceunity.core.controller.bodyBeauty.BodyBeautyParam;
import com.faceunity.core.entity.FUBundleData;
import com.faceunity.core.faceunity.FURenderKit;
import com.faceunity.core.model.bodyBeauty.BodyBeauty;
import com.faceunity.nama.entity.BodyBeautyBean;
import com.faceunity.nama.entity.ModelAttributeData;
import com.faceunity.nama.infe.AbstractBodyBeautyDataFactory;
import com.faceunity.nama.repo.BodyBeautySource;

import java.util.ArrayList;
import java.util.HashMap;


/**
 * DESC：美体业务工厂
 * Created on 2021/3/2
 */
public class BodyBeautyDataFactory extends AbstractBodyBeautyDataFactory {


    interface BodyBeautySetParamInterface {
        void setValue(double value);
    }

    interface BodyBeautyGetParamInterface {
        double getValue();
    }


    /*渲染控制器*/
    private final FURenderKit mFURenderKit = FURenderKit.getInstance();

    /*美体数据模型*/
    public final BodyBeauty bodyBeauty;

    public BodyBeautyDataFactory() {
        bodyBeauty = new BodyBeauty(new FUBundleData(BodyBeautySource.BUNDLE_BODY_BEAUTY));

    }


    /**
     * 获取美体属性列表
     *
     * @return
     */
    @Override
    public ArrayList<BodyBeautyBean> getBodyBeautyParam() {
        return BodyBeautySource.buildBodyBeauty();
    }

    /**
     * 获取美体扩展参数
     *
     * @return
     */
    @Override
    public HashMap<String, ModelAttributeData> getModelAttributeRange() {
        return BodyBeautySource.buildModelAttributeRange();
    }


    /**
     * 获取模型参数
     *
     * @param key 名称标识
     * @return
     */
    @Override
    public double getParamIntensity(String key) {
        if (bodyBeautyGetMapping.containsKey(key)) {
            return bodyBeautyGetMapping.get(key).getValue();
        }
        return 0.0;
    }

    /**
     * 设置属性参数
     *
     * @param key   名称标识
     * @param value 结果值
     */
    @Override
    public void updateParamIntensity(String key, double value) {
        if (bodyBeautySetMapping.containsKey(key)) {
            bodyBeautySetMapping.get(key).setValue(value);
        }
    }

    /**
     * 获取当前模型
     *
     * @return
     */
    private BodyBeauty getCurrentBodyBeautyModel() {
        return bodyBeauty;
    }

    /**
     * 美体开关设置
     *
     * @param enable
     */
    @Override
    public void enableBodyBeauty(boolean enable) {
        if (mFURenderKit.getBodyBeauty() != null) {
            mFURenderKit.getBodyBeauty().setEnable(enable);
        }
    }

    @Override
    public boolean isBodyBeautyEnabled() {
        if (mFURenderKit.getBodyBeauty() != null) {
            return mFURenderKit.getBodyBeauty().getEnable();
        }
        return true;
    }

    /*模型映射设置模型值*/
    private final HashMap<String, BodyBeautySetParamInterface> bodyBeautySetMapping = new HashMap<String, BodyBeautySetParamInterface>() {
        {
            put(BodyBeautyParam.BODY_SLIM_INTENSITY, value -> getCurrentBodyBeautyModel().setBodySlimIntensity(value));
            put(BodyBeautyParam.LEG_STRETCH_INTENSITY, value -> getCurrentBodyBeautyModel().setLegStretchIntensity(value));
            put(BodyBeautyParam.WAIST_SLIM_INTENSITY, value -> getCurrentBodyBeautyModel().setWaistSlimIntensity(value));
            put(BodyBeautyParam.SHOULDER_SLIM_INTENSITY, value -> getCurrentBodyBeautyModel().setShoulderSlimIntensity(value));
            put(BodyBeautyParam.HIP_SLIM_INTENSITY, value -> getCurrentBodyBeautyModel().setHipSlimIntensity(value));
            put(BodyBeautyParam.HEAD_SLIM_INTENSITY, value -> getCurrentBodyBeautyModel().setHeadSlimIntensity(value));
            put(BodyBeautyParam.LEG_SLIM_INTENSITY, value -> getCurrentBodyBeautyModel().setLegSlimIntensity(value));
        }
    };

    /*模型映射获取模型值*/
    HashMap<String, BodyBeautyGetParamInterface> bodyBeautyGetMapping = new HashMap<String, BodyBeautyGetParamInterface>() {
        {
            put(BodyBeautyParam.BODY_SLIM_INTENSITY, () -> getCurrentBodyBeautyModel().getBodySlimIntensity());
            put(BodyBeautyParam.LEG_STRETCH_INTENSITY, () -> getCurrentBodyBeautyModel().getLegStretchIntensity());
            put(BodyBeautyParam.WAIST_SLIM_INTENSITY, () -> getCurrentBodyBeautyModel().getWaistSlimIntensity());
            put(BodyBeautyParam.SHOULDER_SLIM_INTENSITY, () -> getCurrentBodyBeautyModel().getShoulderSlimIntensity());
            put(BodyBeautyParam.HIP_SLIM_INTENSITY, () -> getCurrentBodyBeautyModel().getHipSlimIntensity());
            put(BodyBeautyParam.HEAD_SLIM_INTENSITY, () -> getCurrentBodyBeautyModel().getHeadSlimIntensity());
            put(BodyBeautyParam.LEG_SLIM_INTENSITY, () -> getCurrentBodyBeautyModel().getLegSlimIntensity());

        }
    };


    /**
     * FURenderKit加载当前特效
     */
    public void bindCurrentRenderer() {
        mFURenderKit.setBodyBeauty(bodyBeauty);
    }


}
