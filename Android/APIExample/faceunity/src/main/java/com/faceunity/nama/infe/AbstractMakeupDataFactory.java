package com.faceunity.nama.infe;


import com.faceunity.nama.entity.MakeupCombinationBean;

import java.util.ArrayList;

/**
 * DESC：数据构造工厂抽象类
 * Created on 2021/4/26
 */
public abstract class AbstractMakeupDataFactory {

    /**
     * 获取当前组合妆容列表
     *
     * @return
     */
    public abstract ArrayList<MakeupCombinationBean> getMakeupCombinations();

    /**
     * 获取当前组合妆容下标
     *
     * @return
     */
    public abstract int getCurrentCombinationIndex();

    /**
     * 设置组合妆容下标
     *
     * @param currentCombinationIndex
     */
    public abstract void setCurrentCombinationIndex(int currentCombinationIndex);


    /**
     * 组合妆容选中
     *
     * @param bean MakeupCombinationBean
     */
    public abstract void onMakeupCombinationSelected(MakeupCombinationBean bean);

    /**
     * 设置美妆整体强度
     *
     * @param intensity Double
     */
    public abstract void updateCombinationIntensity(double intensity);

}
