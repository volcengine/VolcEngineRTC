package com.faceunity.nama.control;

import android.annotation.SuppressLint;
import android.content.Context;
import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.widget.SwitchCompat;
import androidx.recyclerview.widget.RecyclerView;

import android.util.AttributeSet;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;

import com.faceunity.core.utils.DecimalUtils;
import com.faceunity.nama.R;
import com.faceunity.nama.base.BaseDelegate;
import com.faceunity.nama.base.BaseListAdapter;
import com.faceunity.nama.base.BaseViewHolder;
import com.faceunity.nama.dialog.ToastHelper;
import com.faceunity.nama.entity.FaceBeautyBean;
import com.faceunity.nama.entity.ModelAttributeData;
import com.faceunity.nama.infe.AbstractFaceBeautyDataFactory;
import com.faceunity.nama.seekbar.DiscreteSeekBar;

import java.util.ArrayList;
import java.util.HashMap;

/**
 * DESC：
 * Created on 2021/4/26
 */
public class FaceBeautyShapeControlView extends BaseControlView {
    private AbstractFaceBeautyDataFactory mDataFactory;

    /*  美型 */
    private HashMap<String, ModelAttributeData> mModelAttributeRange;
    private ArrayList<FaceBeautyBean> mShapeBeauty;
    private int mShapeIndex = -1;
    private BaseListAdapter<FaceBeautyBean> mBeautyAdapter;

    private RecyclerView recyclerView;
    private DiscreteSeekBar discreteSeekBar;
    private LinearLayout recoverLayout;
    private ImageView recoverImageView;
    private TextView recoverTextView;
    private SwitchCompat switchCompat;

    public FaceBeautyShapeControlView(@NonNull Context context) {
        super(context);
        init();
    }

    public FaceBeautyShapeControlView(@NonNull Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
        init();
    }

    public FaceBeautyShapeControlView(@NonNull Context context, @Nullable AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        init();
    }


    /**
     * 给控制绑定FaceBeautyController，数据工厂
     *
     * @param dataFactory IFaceBeautyDataFactory
     */
    public void bindDataFactory(AbstractFaceBeautyDataFactory dataFactory) {
        mDataFactory = dataFactory;
        mModelAttributeRange = dataFactory.getModelAttributeRange();
        mShapeBeauty = dataFactory.getShapeBeauty();
        mBeautyAdapter.setData(mShapeBeauty);
        recyclerView.setAdapter(mBeautyAdapter);
        if (mShapeIndex > 0) {
            FaceBeautyBean item = mShapeBeauty.get(mShapeIndex);
            double value = mDataFactory.getParamIntensity(item.getKey());
            double stand = mModelAttributeRange.get(item.getKey()).getStandV();
            double maxRange = mModelAttributeRange.get(item.getKey()).getMaxRange();
            seekToSeekBar(value, stand, maxRange);
        } else {
            discreteSeekBar.setVisibility(INVISIBLE);
        }

        setRecoverEnable(checkFaceShapeChanged());
    }

    public void updateOnSelected() {
        if (switchCompat != null) {
            boolean enabled = mDataFactory == null || mDataFactory.isFaceBeautyEnabled();
            switchCompat.setChecked(enabled);
        }
    }

    private void init() {
        LayoutInflater.from(mContext).inflate(R.layout.layout_face_beauty_control, this);
        initView();
        initAdapter();
        bindListener();
    }

    private void initView() {
        recyclerView = findViewById(R.id.recycler_view);
        discreteSeekBar = findViewById(R.id.seek_bar);
        recoverLayout = findViewById(R.id.lyt_beauty_recover);
        recoverImageView = findViewById(R.id.iv_beauty_recover);
        recoverTextView = findViewById(R.id.tv_beauty_recover);
        switchCompat = findViewById(R.id.switch_compat);
        initHorizontalRecycleView(recyclerView);
    }

    /**
     * 构造Adapter
     */
    private void initAdapter() {
        mBeautyAdapter = new BaseListAdapter<>(new ArrayList<>(), new BaseDelegate<FaceBeautyBean>() {
            @Override
            public void convert(int viewType, BaseViewHolder helper, FaceBeautyBean data, int position) {
                helper.setText(R.id.tv_control, data.getDesRes());
                double value = mDataFactory.getParamIntensity(data.getKey());
                double stand = mModelAttributeRange.get(data.getKey()).getStandV();
                if (DecimalUtils.doubleEquals(value, stand)) {
                    helper.setImageResource(R.id.iv_control, data.getCloseRes());
                } else {
                    helper.setImageResource(R.id.iv_control, data.getOpenRes());
                }
                helper.itemView.setSelected(mShapeIndex == position);

                ImageView ivControl = helper.getView(R.id.iv_control);
                if (!data.isCanUseFunction()) {
                    ivControl.setImageAlpha(154);
                } else {
                    ivControl.setImageAlpha(255);
                }
            }

            @Override
            public void onItemClickListener(View view, FaceBeautyBean data, int position) {
                if (position == mShapeIndex) {
                    return;
                }
                if (!data.isCanUseFunction()) {
                    ToastHelper.showNormalToast(mContext, mContext.getString(R.string.face_beauty_function_tips, mContext.getString(data.getDesRes())));
                    return;
                }
                changeAdapterSelected(mBeautyAdapter, mShapeIndex, position);
                mShapeIndex = position;
                double value = mDataFactory.getParamIntensity(data.getKey());
                double stand = mModelAttributeRange.get(data.getKey()).getStandV();
                double maxRange = mModelAttributeRange.get(data.getKey()).getMaxRange();
                seekToSeekBar(value, stand, maxRange);
            }
        }, R.layout.list_item_control_title_image_circle);
    }


    /**
     * 绑定监听事件
     */
    @SuppressLint("ClickableViewAccessibility")
    private void bindListener() {
        /*拦截触碰事件*/
        findViewById(R.id.fyt_bottom_view).setOnTouchListener((v, event) -> true);
        /*滑动条控制*/
        bindSeekBarListener();
        /*还原数据*/
        recoverLayout.setOnClickListener((view) -> showDialog(mContext.getString(R.string.dialog_reset_avatar_model), () -> recoverData()));
        /*渲染开关*/
        switchCompat.setOnCheckedChangeListener((buttonView, isChecked) -> mDataFactory.enableFaceBeauty(isChecked));
    }


    /**
     * 滚动条绑定事件
     */
    private void bindSeekBarListener() {
        discreteSeekBar.setOnProgressChangeListener(new DiscreteSeekBar.OnSimpleProgressChangeListener() {
            @Override
            public void onProgressChanged(DiscreteSeekBar seekBar, int value, boolean fromUser) {
                if (!fromUser) {
                    return;
                }
                double valueF = 1.0 * (value - seekBar.getMin()) / 100;
                FaceBeautyBean bean = mShapeBeauty.get(mShapeIndex);
                double range = mModelAttributeRange.get(bean.getKey()).getMaxRange();
                double res = valueF * range;
                double intensity = mDataFactory.getParamIntensity(bean.getKey());
                if (!DecimalUtils.doubleEquals(res, intensity)) {
                    mDataFactory.updateParamIntensity(bean.getKey(), res);
                    setRecoverEnable(checkFaceShapeChanged());
                    updateBeautyItemUI(mBeautyAdapter.getViewHolderByPosition(mShapeIndex), bean);
                }
            }
        });
    }

    /**
     * 设置滚动条数值
     *
     * @param value Double 结果值
     * @param stand Double 标准值
     * @param range Double 范围区间
     */
    private void seekToSeekBar(double value, double stand, double range) {
        if (stand == 0.5) {
            discreteSeekBar.setMin(-50);
            discreteSeekBar.setMax(50);
            discreteSeekBar.setProgress((int) (value * 100 / range - 50));
        } else {
            discreteSeekBar.setMin(0);
            discreteSeekBar.setMax(100);
            discreteSeekBar.setProgress((int) (value * 100 / range));
        }
        discreteSeekBar.setVisibility(View.VISIBLE);
    }

    /**
     * 更新单项是否为基准值显示
     */
    private void updateBeautyItemUI(BaseViewHolder viewHolder, FaceBeautyBean bean) {
        double value = mDataFactory.getParamIntensity(bean.getKey());
        double stand = mModelAttributeRange.get(bean.getKey()).getStandV();
        if (viewHolder == null) {
            return;
        }
        if (DecimalUtils.doubleEquals(value, stand)) {
            viewHolder.setImageResource(R.id.iv_control, bean.getCloseRes());
        } else {
            viewHolder.setImageResource(R.id.iv_control, bean.getOpenRes());
        }
        mBeautyAdapter.notifyDataSetChanged();
    }

    /**
     * 重置还原按钮状态
     *
     * @param enable Boolean
     */
    private void setRecoverEnable(Boolean enable) {
        if (enable) {
            recoverImageView.setAlpha(1f);
            recoverTextView.setAlpha(1f);
        } else {
            recoverImageView.setAlpha(0.6f);
            recoverTextView.setAlpha(0.6f);
        }
        recoverLayout.setEnabled(enable);
    }

    /**
     * 遍历美型数据确认还原按钮是否可以点击
     *
     * @return Boolean
     */
    private boolean checkFaceShapeChanged() {
        if (mShapeBeauty.size() > mShapeIndex && mShapeIndex >= 0) {
            FaceBeautyBean bean = mShapeBeauty.get(mShapeIndex);
            double value = mDataFactory.getParamIntensity(bean.getKey());
            double defaultV = mModelAttributeRange.get(bean.getKey()).getDefaultV();
            if (!DecimalUtils.doubleEquals(value, defaultV)) {
                return true;
            }
            for (FaceBeautyBean beautyBean : mShapeBeauty) {
                value = mDataFactory.getParamIntensity(beautyBean.getKey());
                defaultV = mModelAttributeRange.get(beautyBean.getKey()).getDefaultV();
                if (!DecimalUtils.doubleEquals(value, defaultV)) {
                    return true;
                }
            }
        }
        return false;
    }

    /**
     * 还原 美型、美肤数据
     */
    private void recoverData() {
        recoverData(mShapeBeauty, mShapeIndex);
    }

    /**
     * 重置数据
     *
     * @param beautyBeans
     * @param currentIndex
     */
    private void recoverData(ArrayList<FaceBeautyBean> beautyBeans, int currentIndex) {
        for (FaceBeautyBean bean : beautyBeans) {
            double intensity = mModelAttributeRange.get(bean.getKey()).getDefaultV();
            mDataFactory.updateParamIntensity(bean.getKey(), intensity);
        }
        FaceBeautyBean data = beautyBeans.get(currentIndex);
        double value = mDataFactory.getParamIntensity(data.getKey());
        double stand = mModelAttributeRange.get(data.getKey()).getStandV();
        double maxRange = mModelAttributeRange.get(data.getKey()).getMaxRange();
        seekToSeekBar(value, stand, maxRange);
        mBeautyAdapter.notifyDataSetChanged();
        setRecoverEnable(false);
    }
}
