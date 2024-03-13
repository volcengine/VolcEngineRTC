package com.faceunity.nama.listener;

import android.view.View;
import android.view.View.OnClickListener;

/**
 * DESC：
 * Created on 2021/4/26
 */
public abstract class OnMultiClickListener implements OnClickListener {
    private long mLastClickTime = 0L;
    private int mViewId = View.NO_ID;
    private static long MIN_CLICK_DELAY_TIME = 500L;

    @Override
    public void onClick(View v) {
        long curClickTime = System.currentTimeMillis();
        int viewId = v.getId();
        if (mViewId == viewId) {
            if (curClickTime - mLastClickTime >= MIN_CLICK_DELAY_TIME) {
                mLastClickTime = curClickTime;
                onMultiClick(v);
            }
        } else {
            mViewId = viewId;
            mLastClickTime = curClickTime;
            onMultiClick(v);
        }
    }


    /**
     * 处理后的点击事件
     *
     * @param v
     */
    protected abstract void onMultiClick(View v);


}
