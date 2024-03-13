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
import com.faceunity.nama.entity.MakeupCombinationBean;
import com.faceunity.nama.infe.AbstractMakeupDataFactory;
import com.faceunity.nama.seekbar.DiscreteSeekBar;

import java.util.ArrayList;

/**
 * DESC：
 * Created on 2021/4/26
 */
public class MakeupControlView extends BaseControlView {

    private RecyclerView recyclerView;
    private DiscreteSeekBar discreteSeekBar;

    private AbstractMakeupDataFactory mDataFactory;

    /*  组合妆容 */
    private BaseListAdapter<MakeupCombinationBean> mCombinationAdapter;

    public MakeupControlView(@NonNull Context context) {
        super(context);
        init();
    }

    public MakeupControlView(@NonNull Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
        init();
    }

    public MakeupControlView(@NonNull Context context, @Nullable AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        init();
    }

    private void init() {
        LayoutInflater.from(mContext).inflate(R.layout.layout_make_up_control, this);
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
     * 给控制绑定FaceBeautyController，MakeupController 数据工厂
     *
     * @param dataFactory IFaceBeautyDataFactory
     */
    public void bindDataFactory(AbstractMakeupDataFactory dataFactory) {
        mDataFactory = dataFactory;
        mCombinationAdapter.setData(dataFactory.getMakeupCombinations());
        showCombinationSeekBar(mCombinationAdapter.getData(dataFactory.getCurrentCombinationIndex()));
    }

    /**
     * 组合妆容Adapter
     */
    private void initAdapter() {
        mCombinationAdapter = new BaseListAdapter<>(new ArrayList<>(), new BaseDelegate<MakeupCombinationBean>() {
            @Override
            public void convert(int viewType, BaseViewHolder helper, MakeupCombinationBean data, int position) {
                helper.setText(R.id.tv_control, data.getDesRes());
                helper.setImageResource(R.id.iv_control, data.getImageRes());
                helper.itemView.setSelected(position == mDataFactory.getCurrentCombinationIndex());
            }

            @Override
            public void onItemClickListener(View view, MakeupCombinationBean data, int position) {
                if (position != mDataFactory.getCurrentCombinationIndex()) {
                    changeAdapterSelected(mCombinationAdapter, mDataFactory.getCurrentCombinationIndex(), position);
                    mDataFactory.setCurrentCombinationIndex(position);
                    mDataFactory.onMakeupCombinationSelected(data);
                    showCombinationSeekBar(data);
                }

            }


        }, R.layout.list_item_control_title_image_square);
        recyclerView.setAdapter(mCombinationAdapter);
    }


    /**
     * 绑定监听事件
     */
    @SuppressLint("ClickableViewAccessibility")
    private void bindListener() {
        /*组合妆容强度变更回调*/
        discreteSeekBar.setOnProgressChangeListener(new DiscreteSeekBar.OnSimpleProgressChangeListener() {
            @Override
            public void onProgressChanged(DiscreteSeekBar seekBar, int value, boolean fromUser) {
                if (!fromUser) {
                    return;
                }
                double valueF = 1.0f * (value - seekBar.getMin()) / 100;
                MakeupCombinationBean combination = mCombinationAdapter.getData(mDataFactory.getCurrentCombinationIndex());
                if (!DecimalUtils.doubleEquals(valueF, combination.getIntensity())) {
                    combination.setIntensity(valueF);
                    mDataFactory.updateCombinationIntensity(valueF);
                }
            }
        });
    }

    //endregion  init


    // region  Adapter


// region 视图控制

    /**
     * 选中组合妆容，控制强度调节器以及自定义按钮状态变更
     */
    private void showCombinationSeekBar(MakeupCombinationBean data) {
        if (data.getBundlePath() == null) {
            discreteSeekBar.setVisibility(View.INVISIBLE);
        } else {
            discreteSeekBar.setVisibility(View.VISIBLE);
            discreteSeekBar.setProgress((int) (data.getIntensity() * 100));
        }
    }

    // endregion
}
