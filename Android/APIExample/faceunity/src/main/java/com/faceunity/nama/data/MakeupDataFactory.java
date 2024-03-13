package com.faceunity.nama.data;


import androidx.annotation.NonNull;

import com.faceunity.nama.FUConfig;
import com.faceunity.core.entity.FUBundleData;
import com.faceunity.core.faceunity.FURenderKit;
import com.faceunity.core.model.makeup.SimpleMakeup;
import com.faceunity.nama.entity.MakeupCombinationBean;
import com.faceunity.nama.infe.AbstractMakeupDataFactory;
import com.faceunity.nama.repo.MakeupSource;
import com.faceunity.nama.utils.FuDeviceUtils;

import java.util.ArrayList;
import java.util.HashMap;

/**
 * DESC：美妆业务工厂
 * Created on 2021/3/1
 */
public class MakeupDataFactory extends AbstractMakeupDataFactory {


    /*渲染控制器*/
    private FURenderKit mFURenderKit = FURenderKit.getInstance();

    /*组合妆容列表*/
    private ArrayList<MakeupCombinationBean> makeupCombinations;
    /*组合妆容当前下标*/
    private int currentCombinationIndex;//-1：自定义
    /*美妆数据模型*/
    private SimpleMakeup currentMakeup;
    /*美妆数据模型缓存*/
    private HashMap<String, SimpleMakeup> makeupMap = new HashMap<>();


    public MakeupDataFactory(int index) {
        makeupCombinations = MakeupSource.buildCombinations();
        currentCombinationIndex = index;
        currentMakeup = getMakeupModel(makeupCombinations.get(currentCombinationIndex)); // 当前生效模型
    }

    //region 组合妆

    /**
     * 获取当前组合妆容列表
     *
     * @return
     */
    @Override
    @NonNull
    public ArrayList<MakeupCombinationBean> getMakeupCombinations() {
        return makeupCombinations;
    }

    /**
     * 获取当前组合妆容下标
     *
     * @return
     */
    @Override
    public int getCurrentCombinationIndex() {
        return currentCombinationIndex;
    }

    /**
     * 设置组合妆容下标
     *
     * @param currentCombinationIndex
     */
    @Override
    public void setCurrentCombinationIndex(int currentCombinationIndex) {
        this.currentCombinationIndex = currentCombinationIndex;
    }

    /**
     * 切换组合妆容
     *
     * @param bean
     */
    @Override
    public void onMakeupCombinationSelected(MakeupCombinationBean bean) {
        currentMakeup = getMakeupModel(bean);
        mFURenderKit.setMakeup(currentMakeup);
    }

    /**
     * 切换美妆模型整体强度
     *
     * @param intensity
     */
    @Override
    public void updateCombinationIntensity(double intensity) {
        currentMakeup.setMakeupIntensity(intensity);
    }

    /**
     * 构造美妆模型
     *
     * @param bean
     * @return
     */
    private SimpleMakeup getMakeupModel(MakeupCombinationBean bean) {
        if (bean.getBundlePath() == null) {
            return null;
        } else {
            if (makeupMap.containsKey(bean.getKey())) {
                return makeupMap.get(bean.getKey());
            }
            SimpleMakeup makeup = new SimpleMakeup(new FUBundleData(MakeupSource.BUNDLE_FACE_MAKEUP));
            makeup.setCombinedConfig(new FUBundleData(bean.getBundlePath()));
            makeup.setMakeupIntensity(bean.getIntensity());
            makeup.setMachineLevel(FUConfig.DEVICE_LEVEL > FuDeviceUtils.DEVICE_LEVEL_MID);//更新设备等级去设置是否开启人脸遮挡
            makeupMap.put(bean.getKey(), makeup);
            return makeup;
        }
    }


    //endregion 组合妆

    /**
     * FURenderKit加载当前特效
     */
    public void bindCurrentRenderer() {
        mFURenderKit.setMakeup(currentMakeup);
    }
}