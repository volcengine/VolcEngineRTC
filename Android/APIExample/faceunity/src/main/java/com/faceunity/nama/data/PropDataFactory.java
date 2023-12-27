package com.faceunity.nama.data;



import androidx.annotation.NonNull;

import com.faceunity.core.entity.FUBundleData;
import com.faceunity.core.faceunity.FURenderKit;
import com.faceunity.core.model.prop.Prop;
import com.faceunity.core.model.prop.sticker.Sticker;
import com.faceunity.nama.entity.PropBean;
import com.faceunity.nama.infe.AbstractPropDataFactory;
import com.faceunity.nama.repo.PropSource;

import java.util.ArrayList;

/**
 * DESC：道具业务工厂
 * Created on 2021/3/2
 */
public class PropDataFactory extends AbstractPropDataFactory {

    /*渲染控制器*/
    private final FURenderKit mFURenderKit = FURenderKit.getInstance();
    /*道具列表*/
    private final ArrayList<PropBean> propBeans;
    /*默认选中下标*/
    private int currentPropIndex;
    /*当前道具*/
    public Prop currentProp;

    public PropDataFactory(int index) {
        currentPropIndex = index;
        propBeans = PropSource.buildPropBeans();
    }


    /**
     * 获取当前选中下标
     *
     * @return
     */
    @Override
    public int getCurrentPropIndex() {
        return currentPropIndex;
    }

    /**
     * 设置当前选中下标
     *
     * @param currentPropIndex
     */
    @Override
    public void setCurrentPropIndex(int currentPropIndex) {
        this.currentPropIndex = currentPropIndex;
    }

    /**
     * 获取道具队列
     *
     * @return
     */
    @Override
    @NonNull
    public ArrayList<PropBean> getPropBeans() {
        return propBeans;
    }

    /**
     * 道具选中
     *
     * @param bean
     */
    @Override
    public void onItemSelected(PropBean bean) {
        String path = bean.getPath();
        if (path == null || path.trim().length() == 0) {
            mFURenderKit.getPropContainer().removeAllProp();
            currentProp = null;
            return;
        }
        Prop prop = new Sticker(new FUBundleData(path));
        mFURenderKit.getPropContainer().replaceProp(currentProp, prop);
        currentProp = prop;
    }


    /**
     * FURenderKit加载当前特效
     */
    public void bindCurrentRenderer() {
        PropBean propBean = propBeans.get(currentPropIndex);
        onItemSelected(propBean);
    }
}
