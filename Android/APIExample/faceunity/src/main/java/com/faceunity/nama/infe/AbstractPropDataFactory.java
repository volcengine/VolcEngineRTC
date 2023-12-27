package com.faceunity.nama.infe;

import com.faceunity.nama.entity.PropBean;

import java.util.ArrayList;

/**
 * DESC：数据构造工厂抽象类
 * Created on 2021/4/26
 */
public abstract class AbstractPropDataFactory {


    /**
     * 获取当前选中下标
     *
     * @return
     */
    public abstract int getCurrentPropIndex();

    /**
     * 设置当前选中下标
     *
     * @param currentPropIndex
     */
    public abstract void setCurrentPropIndex(int currentPropIndex);

    /**
     * 获取道具队列
     *
     * @return
     */
    public abstract ArrayList<PropBean> getPropBeans();

    /**
     * 道具选中
     *
     * @param bean StickerBean
     */
    public abstract void onItemSelected(PropBean bean);

}
