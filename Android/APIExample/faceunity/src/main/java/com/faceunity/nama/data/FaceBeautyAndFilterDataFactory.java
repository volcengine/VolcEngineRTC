package com.faceunity.nama.data;


import androidx.annotation.NonNull;

import com.faceunity.core.controller.facebeauty.FaceBeautyParam;
import com.faceunity.core.faceunity.FURenderKit;
import com.faceunity.core.model.facebeauty.FaceBeauty;
import com.faceunity.nama.entity.FaceBeautyBean;
import com.faceunity.nama.entity.FaceBeautyFilterBean;
import com.faceunity.nama.entity.ModelAttributeData;
import com.faceunity.nama.infe.AbstractFaceBeautyDataFactory;
import com.faceunity.nama.repo.FaceBeautySource;

import java.util.ArrayList;
import java.util.HashMap;


/**
 * DESC：美颜业务工厂
 * Created on 2021/3/1
 */
public class FaceBeautyAndFilterDataFactory extends AbstractFaceBeautyDataFactory {


    interface FaceBeautySetParamInterface {
        /**
         * 设置属性值
         *
         * @param value
         */
        void setValue(double value);
    }

    interface FaceBeautyGetParamInterface {
        /**
         * 获取属性值
         *
         * @return
         */
        double getValue();
    }

    /*渲染控制器*/
    private FURenderKit mFURenderKit = FURenderKit.getInstance();

    /*当前生效美颜数据模型*/
    public FaceBeauty defaultFaceBeauty = FaceBeautySource.getDefaultFaceBeauty();

    /*默认滤镜选中下标*/
    private int currentFilterIndex = 0;

    /**
     * 获取美肤参数列表
     *
     * @return
     */
    @NonNull
    @Override
    public ArrayList<FaceBeautyBean> getSkinBeauty() {
        return FaceBeautySource.buildSkinParams();
    }

    /**
     * 获取美型参数列表
     *
     * @return
     */
    @NonNull
    @Override
    public ArrayList<FaceBeautyBean> getShapeBeauty() {
        return FaceBeautySource.buildShapeParams();
    }


    /**
     * 获取美肤、美型扩展参数
     *
     * @return
     */
    @NonNull
    @Override
    public HashMap<String, ModelAttributeData> getModelAttributeRange() {
        return FaceBeautySource.buildModelAttributeRange();
    }


    /**
     * 获取滤镜参数列表
     *
     * @return
     */
    @NonNull
    @Override
    public ArrayList<FaceBeautyFilterBean> getBeautyFilters() {
        ArrayList<FaceBeautyFilterBean> filterBeans = FaceBeautySource.buildFilters();
        for (int i = 0; i < filterBeans.size(); i++) {
            if (filterBeans.get(i).getKey().equals(defaultFaceBeauty.getFilterName())) {
                filterBeans.get(i).setIntensity(defaultFaceBeauty.getFilterIntensity());
                currentFilterIndex = i;
            }

        }
        return filterBeans;
    }

    /**
     * 获取当前滤镜下标
     *
     * @return
     */
    @Override
    public int getCurrentFilterIndex() {
        return currentFilterIndex;
    }

    /**
     * 设置当前滤镜下标
     *
     * @param currentFilterIndex
     */
    @Override
    public void setCurrentFilterIndex(int currentFilterIndex) {
        this.currentFilterIndex = currentFilterIndex;
    }


    /**
     * 美颜开关设置
     *
     * @param enable
     */
    @Override
    public void enableFaceBeauty(boolean enable) {
        if (mFURenderKit.getFaceBeauty() != null) {
            mFURenderKit.getFaceBeauty().setEnable(enable);
        }
    }

    @Override
    public boolean isFaceBeautyEnabled() {
        if (mFURenderKit.getFaceBeauty() != null) {
            return mFURenderKit.getFaceBeauty().getEnable();
        }
        return true;
    }

    /**
     * 获取模型参数
     *
     * @param key 名称标识
     * @return 属性值
     */
    @Override
    public double getParamIntensity(@NonNull String key) {
        if (faceBeautyGetMapping.containsKey(key)) {
            return faceBeautyGetMapping.get(key).getValue();
        }
        return 0.0;
    }

    /**
     * 设置模型参数
     *
     * @param key   名称标识
     * @param value 属性值
     */
    @Override
    public void updateParamIntensity(@NonNull String key, double value) {
        if (faceBeautySetMapping.containsKey(key)) {
            faceBeautySetMapping.get(key).setValue(value);
        }
    }

    /**
     * 切换滤镜
     *
     * @param name      滤镜名称标识
     * @param intensity 滤镜强度
     * @param resID     滤镜名称
     */
    @Override
    public void onFilterSelected(@NonNull String name, double intensity, int resID) {
        defaultFaceBeauty.setFilterName(name);
        defaultFaceBeauty.setFilterIntensity(intensity);
    }

    /**
     * 更换滤镜强度
     *
     * @param intensity 滤镜强度
     */
    @Override
    public void updateFilterIntensity(double intensity) {
        defaultFaceBeauty.setFilterIntensity(intensity);
    }


    /*模型映射设置模型值*/
    private final HashMap<String, FaceBeautySetParamInterface> faceBeautySetMapping = new HashMap<String, FaceBeautySetParamInterface>() {{
        put(FaceBeautyParam.COLOR_INTENSITY, defaultFaceBeauty::setColorIntensity);
        put(FaceBeautyParam.BLUR_INTENSITY, defaultFaceBeauty::setBlurIntensity);
        put(FaceBeautyParam.RED_INTENSITY, defaultFaceBeauty::setRedIntensity);
        put(FaceBeautyParam.SHARPEN_INTENSITY, defaultFaceBeauty::setSharpenIntensity);
        put(FaceBeautyParam.EYE_BRIGHT_INTENSITY, defaultFaceBeauty::setEyeBrightIntensity);
        put(FaceBeautyParam.TOOTH_WHITEN_INTENSITY, defaultFaceBeauty::setToothIntensity);
        put(FaceBeautyParam.REMOVE_POUCH_INTENSITY, defaultFaceBeauty::setRemovePouchIntensity);
        put(FaceBeautyParam.REMOVE_NASOLABIAL_FOLDS_INTENSITY, defaultFaceBeauty::setRemoveLawPatternIntensity);
        /*美型*/
        put(FaceBeautyParam.FACE_SHAPE_INTENSITY, defaultFaceBeauty::setFaceShapeIntensity);
        put(FaceBeautyParam.CHEEK_THINNING_INTENSITY, defaultFaceBeauty::setCheekThinningIntensity);
        put(FaceBeautyParam.CHEEK_V_INTENSITY, defaultFaceBeauty::setCheekVIntensity);
        put(FaceBeautyParam.CHEEK_LONG_INTENSITY, defaultFaceBeauty::setCheekLongIntensity);
        put(FaceBeautyParam.CHEEK_CIRCLE_INTENSITY, defaultFaceBeauty::setCheekCircleIntensity);
        put(FaceBeautyParam.CHEEK_NARROW_INTENSITY, defaultFaceBeauty::setCheekNarrowIntensity);
        put(FaceBeautyParam.CHEEK_SHORT_INTENSITY, defaultFaceBeauty::setCheekShortIntensity);
        put(FaceBeautyParam.CHEEK_SMALL_INTENSITY, defaultFaceBeauty::setCheekSmallIntensity);
        put(FaceBeautyParam.INTENSITY_CHEEKBONES_INTENSITY, defaultFaceBeauty::setCheekBonesIntensity);
        put(FaceBeautyParam.INTENSITY_LOW_JAW_INTENSITY, defaultFaceBeauty::setLowerJawIntensity);
        put(FaceBeautyParam.EYE_ENLARGING_INTENSITY, defaultFaceBeauty::setEyeEnlargingIntensity);
        put(FaceBeautyParam.EYE_CIRCLE_INTENSITY, defaultFaceBeauty::setEyeCircleIntensity);
        put(FaceBeautyParam.BROW_HEIGHT_INTENSITY, defaultFaceBeauty::setBrowHeightIntensity);
        put(FaceBeautyParam.BROW_SPACE_INTENSITY, defaultFaceBeauty::setBrowSpaceIntensity);
        put(FaceBeautyParam.INTENSITY_EYE_LID, defaultFaceBeauty::setEyeLidIntensity);
        put(FaceBeautyParam.INTENSITY_EYE_HEIGHT, defaultFaceBeauty::setEyeHeightIntensity);
        put(FaceBeautyParam.INTENSITY_BROW_THICK, defaultFaceBeauty::setBrowThickIntensity);
        put(FaceBeautyParam.INTENSITY_LIP_THICK, defaultFaceBeauty::setLipThickIntensity);
        put(FaceBeautyParam.FACE_THREED, defaultFaceBeauty::setFaceThreeIntensity);
        put(FaceBeautyParam.CHIN_INTENSITY, defaultFaceBeauty::setChinIntensity);
        put(FaceBeautyParam.FOREHEAD_INTENSITY, defaultFaceBeauty::setForHeadIntensity);
        put(FaceBeautyParam.NOSE_INTENSITY, defaultFaceBeauty::setNoseIntensity);
        put(FaceBeautyParam.MOUTH_INTENSITY, defaultFaceBeauty::setMouthIntensity);
        put(FaceBeautyParam.CANTHUS_INTENSITY, defaultFaceBeauty::setCanthusIntensity);
        put(FaceBeautyParam.EYE_SPACE_INTENSITY, defaultFaceBeauty::setEyeSpaceIntensity);
        put(FaceBeautyParam.EYE_ROTATE_INTENSITY, defaultFaceBeauty::setEyeRotateIntensity);
        put(FaceBeautyParam.LONG_NOSE_INTENSITY, defaultFaceBeauty::setLongNoseIntensity);
        put(FaceBeautyParam.PHILTRUM_INTENSITY, defaultFaceBeauty::setPhiltrumIntensity);
        put(FaceBeautyParam.SMILE_INTENSITY, defaultFaceBeauty::setSmileIntensity);
    }};

    /*模型映射获取模型值*/
    HashMap<String, FaceBeautyGetParamInterface> faceBeautyGetMapping = new HashMap<String, FaceBeautyGetParamInterface>() {
        {
            put(FaceBeautyParam.COLOR_INTENSITY, defaultFaceBeauty::getColorIntensity);
            put(FaceBeautyParam.BLUR_INTENSITY, defaultFaceBeauty::getBlurIntensity);
            put(FaceBeautyParam.RED_INTENSITY, defaultFaceBeauty::getRedIntensity);
            put(FaceBeautyParam.SHARPEN_INTENSITY, defaultFaceBeauty::getSharpenIntensity);
            put(FaceBeautyParam.EYE_BRIGHT_INTENSITY, defaultFaceBeauty::getEyeBrightIntensity);
            put(FaceBeautyParam.TOOTH_WHITEN_INTENSITY, defaultFaceBeauty::getToothIntensity);
            put(FaceBeautyParam.REMOVE_POUCH_INTENSITY, defaultFaceBeauty::getRemovePouchIntensity);
            put(FaceBeautyParam.REMOVE_NASOLABIAL_FOLDS_INTENSITY, defaultFaceBeauty::getRemoveLawPatternIntensity);
            /*美型*/
            put(FaceBeautyParam.FACE_SHAPE_INTENSITY, defaultFaceBeauty::getFaceShapeIntensity);
            put(FaceBeautyParam.CHEEK_THINNING_INTENSITY, defaultFaceBeauty::getCheekThinningIntensity);
            put(FaceBeautyParam.CHEEK_V_INTENSITY, defaultFaceBeauty::getCheekVIntensity);
            put(FaceBeautyParam.CHEEK_LONG_INTENSITY, defaultFaceBeauty::getCheekLongIntensity);
            put(FaceBeautyParam.CHEEK_CIRCLE_INTENSITY, defaultFaceBeauty::getCheekCircleIntensity);
            put(FaceBeautyParam.CHEEK_NARROW_INTENSITY, defaultFaceBeauty::getCheekNarrowIntensity);
            put(FaceBeautyParam.CHEEK_SHORT_INTENSITY, defaultFaceBeauty::getCheekShortIntensity);
            put(FaceBeautyParam.CHEEK_SMALL_INTENSITY, defaultFaceBeauty::getCheekSmallIntensity);
            put(FaceBeautyParam.INTENSITY_CHEEKBONES_INTENSITY, defaultFaceBeauty::getCheekBonesIntensity);
            put(FaceBeautyParam.INTENSITY_LOW_JAW_INTENSITY, defaultFaceBeauty::getLowerJawIntensity);
            put(FaceBeautyParam.EYE_ENLARGING_INTENSITY, defaultFaceBeauty::getEyeEnlargingIntensity);
            put(FaceBeautyParam.EYE_CIRCLE_INTENSITY, defaultFaceBeauty::getEyeCircleIntensity);
            put(FaceBeautyParam.BROW_HEIGHT_INTENSITY, defaultFaceBeauty::getBrowHeightIntensity);
            put(FaceBeautyParam.BROW_SPACE_INTENSITY, defaultFaceBeauty::getBrowSpaceIntensity);
            put(FaceBeautyParam.INTENSITY_EYE_LID, defaultFaceBeauty::getEyeLidIntensity);
            put(FaceBeautyParam.INTENSITY_EYE_HEIGHT, defaultFaceBeauty::getEyeHeightIntensity);
            put(FaceBeautyParam.INTENSITY_BROW_THICK, defaultFaceBeauty::getBrowThickIntensity);
            put(FaceBeautyParam.INTENSITY_LIP_THICK, defaultFaceBeauty::getLipThickIntensity);
            put(FaceBeautyParam.FACE_THREED, defaultFaceBeauty::getFaceThreeIntensity);
            put(FaceBeautyParam.CHIN_INTENSITY, defaultFaceBeauty::getChinIntensity);
            put(FaceBeautyParam.FOREHEAD_INTENSITY, defaultFaceBeauty::getForHeadIntensity);
            put(FaceBeautyParam.NOSE_INTENSITY, defaultFaceBeauty::getNoseIntensity);
            put(FaceBeautyParam.MOUTH_INTENSITY, defaultFaceBeauty::getMouthIntensity);
            put(FaceBeautyParam.CANTHUS_INTENSITY, defaultFaceBeauty::getCanthusIntensity);
            put(FaceBeautyParam.EYE_SPACE_INTENSITY, defaultFaceBeauty::getEyeSpaceIntensity);
            put(FaceBeautyParam.EYE_ROTATE_INTENSITY, defaultFaceBeauty::getEyeRotateIntensity);
            put(FaceBeautyParam.LONG_NOSE_INTENSITY, defaultFaceBeauty::getLongNoseIntensity);
            put(FaceBeautyParam.PHILTRUM_INTENSITY, defaultFaceBeauty::getPhiltrumIntensity);
            put(FaceBeautyParam.SMILE_INTENSITY, defaultFaceBeauty::getSmileIntensity);
        }
    };


    /**
     * FURenderKit加载当前特效
     */
    public void bindCurrentRenderer() {
        mFURenderKit.setFaceBeauty(defaultFaceBeauty);
    }
}
