package com.faceunity.nama.control;

import android.animation.ValueAnimator;
import android.content.Context;
import android.util.AttributeSet;
import android.widget.FrameLayout;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.FragmentActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;
import androidx.recyclerview.widget.SimpleItemAnimator;

import com.faceunity.nama.base.BaseListAdapter;
import com.faceunity.nama.dialog.BaseDialogFragment;
import com.faceunity.nama.dialog.ConfirmDialogFragment;
import com.faceunity.nama.listener.OnBottomAnimatorChangeListener;

/**
 * DESC：自定义菜单Base类
 * Created on 2021/4/26
 */
public abstract class BaseControlView extends FrameLayout {

    protected Context mContext;

    public BaseControlView(@NonNull Context context) {
        super(context);
        mContext = context;
    }

    public BaseControlView(@NonNull Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
        mContext = context;
    }

    public BaseControlView(@NonNull Context context, @Nullable AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        mContext = context;
    }


    /**
     * adapter单项点击，选中状态变更
     *
     * @param adapter  BaseListAdapter<T>
     * @param old      nt
     * @param position Int
     */
    protected <T> void changeAdapterSelected(BaseListAdapter<T> adapter, int old, int position) {
        if (old >= 0 && adapter.getViewByPosition(old) != null) {
            adapter.getViewByPosition(old).setSelected(false);
        }
        if (position >= 0 && adapter.getViewByPosition(position) != null) {
            adapter.getViewByPosition(position).setSelected(true);
        }
    }


    /**
     * 显示弹框
     *
     * @param tip
     * @param runnable
     */
    protected void showDialog(String tip, Runnable runnable) {
        ConfirmDialogFragment confirmDialogFragment = ConfirmDialogFragment.newInstance(tip, new BaseDialogFragment.OnClickListener() {
            @Override
            public void onConfirm() {
                runnable.run();
            }

            @Override
            public void onCancel() {

            }
        });
        confirmDialogFragment.show(((FragmentActivity) mContext).getSupportFragmentManager(), "ConfirmDialogFragmentReset");
    }


    protected void initHorizontalRecycleView(RecyclerView recyclerView) {
        recyclerView.setHasFixedSize(true);
        recyclerView.setLayoutManager(new LinearLayoutManager(mContext, LinearLayoutManager.HORIZONTAL, false));
        ((SimpleItemAnimator) recyclerView.getItemAnimator()).setSupportsChangeAnimations(false);
    }


    /****************************************菜单动画*****************************************************/


    protected boolean isBottomShow;
    protected ValueAnimator bottomLayoutAnimator = null;
    protected OnBottomAnimatorChangeListener onBottomAnimatorChangeListener = null;


}
