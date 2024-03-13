package com.faceunity.nama.control;

import android.content.Context;
import android.util.AttributeSet;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.widget.SwitchCompat;
import androidx.recyclerview.widget.RecyclerView;

import com.faceunity.core.utils.DecimalUtils;
import com.faceunity.nama.R;
import com.faceunity.nama.base.BaseDelegate;
import com.faceunity.nama.base.BaseListAdapter;
import com.faceunity.nama.base.BaseViewHolder;
import com.faceunity.nama.entity.BodyBeautyBean;
import com.faceunity.nama.entity.ModelAttributeData;
import com.faceunity.nama.infe.AbstractBodyBeautyDataFactory;
import com.faceunity.nama.seekbar.DiscreteSeekBar;

import java.util.ArrayList;
import java.util.HashMap;

/**
 * DESC：
 * Created on 2021/4/26
 */
public class BodyBeautyControlView extends BaseControlView {

    private RecyclerView recyclerView;
    private DiscreteSeekBar discreteSeekBar;
    private LinearLayout recoverLayout;
    private ImageView recoverImageView;
    private TextView recoverTextView;
    private SwitchCompat switchCompat;

    private AbstractBodyBeautyDataFactory mDataFactory;
    private HashMap<String, ModelAttributeData> mModelAttributeRange;
    private ArrayList<BodyBeautyBean> mBodyBeautyBeans;
    private BaseListAdapter<BodyBeautyBean> mBodyAdapter;
    private int mBodyIndex = -1;


    public BodyBeautyControlView(@NonNull Context context) {
        super(context);
        init();
    }

    public BodyBeautyControlView(@NonNull Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
        init();
    }

    public BodyBeautyControlView(@NonNull Context context, @Nullable AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        init();
    }

    private void init() {
        LayoutInflater.from(mContext).inflate(R.layout.layout_body_beauty_control, this);
        initView();
        initAdapter();
        bindListener();
    }


    public void bindDataFactory(AbstractBodyBeautyDataFactory dataFactory) {
        mDataFactory = dataFactory;
        mBodyBeautyBeans = mDataFactory.getBodyBeautyParam();
        mBodyAdapter.setData(mBodyBeautyBeans);
        mModelAttributeRange = mDataFactory.getModelAttributeRange();
        if (mBodyIndex > 0) {
            BodyBeautyBean data = mBodyBeautyBeans.get(mBodyIndex);
            double value = mDataFactory.getParamIntensity(data.getKey());
            double stand = mModelAttributeRange.get(data.getKey()).getStandV();
            double maxRange = mModelAttributeRange.get(data.getKey()).getMaxRange();
            seekToSeekBar(value, stand, maxRange);
        } else {
            discreteSeekBar.setVisibility(INVISIBLE);
        }
        setRecoverEnable(checkParamsChanged());
    }

    public void updateOnSelected() {
        if (switchCompat != null) {
            boolean enabled = mDataFactory == null || mDataFactory.isBodyBeautyEnabled();
            switchCompat.setChecked(enabled);
        }
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

    private void initAdapter() {
        mBodyAdapter = new BaseListAdapter<>(new ArrayList<>(), new BaseDelegate<BodyBeautyBean>() {
            @Override
            public void convert(int viewType, BaseViewHolder helper, BodyBeautyBean data, int position) {
                helper.setText(R.id.tv_control, data.getDesRes());
                double value = mDataFactory.getParamIntensity(data.getKey());
                double stand = mModelAttributeRange.get(data.getKey()).getStandV();
                if (DecimalUtils.doubleEquals(value, stand)) {
                    helper.setImageResource(R.id.iv_control, data.getCloseRes());
                } else {
                    helper.setImageResource(R.id.iv_control, data.getOpenRes());
                }
                helper.itemView.setSelected(position == mBodyIndex);
            }

            @Override
            public void onItemClickListener(View view, BodyBeautyBean data, int position) {
                if (mBodyIndex != position) {
                    changeAdapterSelected(mBodyAdapter, mBodyIndex, position);
                    mBodyIndex = position;
                    double value = mDataFactory.getParamIntensity(data.getKey());
                    double stand = mModelAttributeRange.get(data.getKey()).getStandV();
                    double maxRange = mModelAttributeRange.get(data.getKey()).getMaxRange();
                    seekToSeekBar(value, stand, maxRange);
                }
            }

        }, R.layout.list_item_control_title_image_circle);
        recyclerView.setAdapter(mBodyAdapter);
    }

    private void bindListener() {
        findViewById(R.id.cyt_main).setOnTouchListener((v, event) -> true);
        discreteSeekBar.setOnProgressChangeListener(new DiscreteSeekBar.OnSimpleProgressChangeListener() {

            @Override
            public void onProgressChanged(DiscreteSeekBar seekBar, int value, boolean fromUser) {
                if (!fromUser) {
                    return;
                }
                double valueF = 1.0 * (value - seekBar.getMin()) / 100;
                BodyBeautyBean data = mBodyBeautyBeans.get(mBodyIndex);
                double intensity = mDataFactory.getParamIntensity(data.getKey());
                double range = mModelAttributeRange.get(data.getKey()).getMaxRange();
                double res = valueF * range;
                if (!DecimalUtils.doubleEquals(res, intensity)) {
                    mDataFactory.updateParamIntensity(data.getKey(), res);
                    setRecoverEnable(checkParamsChanged());
                    updateBeautyItemUI(mBodyAdapter.getViewHolderByPosition(mBodyIndex), data);
                }
            }
        });
        findViewById(R.id.lyt_beauty_recover).setOnClickListener((view) -> showDialog(mContext.getString(R.string.dialog_reset_avatar_model), () -> recoverData()));
        switchCompat.setOnCheckedChangeListener((buttonView, isChecked) -> {
            mDataFactory.enableBodyBeauty(isChecked);

        });
    }

    /**
     * 设置滚动条数值
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
    private void updateBeautyItemUI(BaseViewHolder viewHolder, BodyBeautyBean bean) {
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
    }

    /**
     * 重置数据
     */
    private void recoverData() {
        for (BodyBeautyBean bean : mBodyBeautyBeans) {
            double intensity = mModelAttributeRange.get(bean.getKey()).getDefaultV();
            mDataFactory.updateParamIntensity(bean.getKey(), intensity);
        }
        BodyBeautyBean data = mBodyBeautyBeans.get(mBodyIndex);
        double value = mDataFactory.getParamIntensity(data.getKey());
        double stand = mModelAttributeRange.get(data.getKey()).getStandV();
        double maxRange = mModelAttributeRange.get(data.getKey()).getMaxRange();
        seekToSeekBar(value, stand, maxRange);
        mBodyAdapter.notifyDataSetChanged();
        setRecoverEnable(false);
    }

    /**
     * 遍历数据确认还原按钮是否可以点击
     *
     * @return Boolean
     */
    private boolean checkParamsChanged() {
        if (mBodyBeautyBeans.size() > mBodyIndex && mBodyIndex >= 0) {
            BodyBeautyBean bean = mBodyBeautyBeans.get(mBodyIndex);
            double value = mDataFactory.getParamIntensity(bean.getKey());
            double defaultV = mModelAttributeRange.get(bean.getKey()).getDefaultV();
            if (!DecimalUtils.doubleEquals(value, defaultV)) {
                return true;
            }
            for (BodyBeautyBean beautyBean : mBodyBeautyBeans) {
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
}
