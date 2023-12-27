package com.faceunity.nama.base;

import android.view.View;

/**
 * DESC：RecycleView 通用业务调用
 * Created on 2021/4/26
 */
public abstract class BaseDelegate<T> {

    /**
     * 根据页面以及数据内容返回Item的布局index,默认返回第一个布局
     *
     * @param data
     * @param position
     * @return
     */
    public int getItemViewType(T data, int position) {
        return 0;
    }


    /**
     * 为ViewHolder绑定数据item
     *
     * @param viewType
     * @param helper
     * @param data
     * @param position
     * @return
     */
    public abstract void convert(int viewType, BaseViewHolder helper, T data, int position);

    /**
     * 绑定单击事件
     *
     * @param view
     * @param data
     * @param position
     */
    public void onItemClickListener(View view, T data, int position) {

    }


    /**
     * 绑定长按事件
     *
     * @param view
     * @param data
     * @param position
     */
    public boolean onItemLongClickListener(View view, T data, int position) {
        return false;
    }

}
