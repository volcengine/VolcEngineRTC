package com.faceunity.nama.control;

import android.annotation.SuppressLint;
import android.content.Context;
import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.recyclerview.widget.RecyclerView;

import android.util.AttributeSet;
import android.view.LayoutInflater;
import android.view.View;

import com.faceunity.core.utils.DecimalUtils;
import com.faceunity.nama.R;
import com.faceunity.nama.base.BaseDelegate;
import com.faceunity.nama.base.BaseListAdapter;
import com.faceunity.nama.base.BaseViewHolder;
import com.faceunity.nama.entity.FaceBeautyFilterBean;
import com.faceunity.nama.infe.AbstractFaceBeautyDataFactory;
import com.faceunity.nama.seekbar.DiscreteSeekBar;

import java.util.ArrayList;

/**
 * DESC：
 * Created on 2021/4/26
 */
public class FilterControlView extends BaseControlView {
    private AbstractFaceBeautyDataFactory mDataFactory;

    /* 滤镜 */
    private ArrayList<FaceBeautyFilterBean> mFilters;
    private BaseListAdapter<FaceBeautyFilterBean> mFiltersAdapter;

    private RecyclerView recyclerView;
    private DiscreteSeekBar discreteSeekBar;

    public FilterControlView(@NonNull Context context) {
        super(context);
        init();
    }

    public FilterControlView(@NonNull Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
        init();
    }

    public FilterControlView(@NonNull Context context, @Nullable AttributeSet attrs, int defStyleAttr) {
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
        mFilters = dataFactory.getBeautyFilters();
        mFiltersAdapter.setData(mFilters);
        recyclerView.setAdapter(mFiltersAdapter);
        recyclerView.scrollToPosition(mDataFactory.getCurrentFilterIndex());
        if (mDataFactory.getCurrentFilterIndex() == 0) {
            discreteSeekBar.setVisibility(View.INVISIBLE);
        } else {
            seekToSeekBar(mFilters.get(mDataFactory.getCurrentFilterIndex()).getIntensity(), 0.0, 1.0);
        }
    }


    private void init() {
        LayoutInflater.from(mContext).inflate(R.layout.layout_filter_control, this);
        initView();
        initAdapter();
        bindListener();
    }

    private void initView() {
        recyclerView = findViewById(R.id.recycler_view);
        discreteSeekBar = findViewById(R.id.seek_bar);
        initHorizontalRecycleView(recyclerView);
    }


    /**
     * 构造Adapter
     */
    private void initAdapter() {
        mFiltersAdapter = new BaseListAdapter<>(new ArrayList<>(), new BaseDelegate<FaceBeautyFilterBean>() {
            @Override
            public void convert(int viewType, BaseViewHolder helper, FaceBeautyFilterBean data, int position) {
                helper.setText(R.id.tv_control, data.getDesRes());
                helper.setImageResource(R.id.iv_control, data.getImageRes());
                helper.itemView.setSelected(mDataFactory.getCurrentFilterIndex() == position);
            }

            @Override
            public void onItemClickListener(View view, FaceBeautyFilterBean data, int position) {
                if (mDataFactory.getCurrentFilterIndex() != position) {
                    changeAdapterSelected(mFiltersAdapter, mDataFactory.getCurrentFilterIndex(), position);
                    mDataFactory.setCurrentFilterIndex(position);
                    mDataFactory.onFilterSelected(data.getKey(), data.getIntensity(), data.getDesRes());
                    if (position == 0) {
                        discreteSeekBar.setVisibility(View.INVISIBLE);
                    } else {
                        seekToSeekBar(data.getIntensity(), 0.0, 1.0);
                    }
                }

            }
        }, R.layout.list_item_control_title_image_square);
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
                FaceBeautyFilterBean bean = mFilters.get(mDataFactory.getCurrentFilterIndex());
                if (!DecimalUtils.doubleEquals(bean.getIntensity(), valueF)) {
                    bean.setIntensity(valueF);
                    mDataFactory.updateFilterIntensity(valueF);
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
}
