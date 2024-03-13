package com.faceunity.nama.ui;

import android.content.Context;
import android.util.AttributeSet;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.LinearLayout;

import androidx.annotation.Nullable;

import com.faceunity.nama.R;
import com.faceunity.nama.checkbox.CheckGroup;
import com.faceunity.nama.control.BodyBeautyControlView;
import com.faceunity.nama.control.FaceBeautyShapeControlView;
import com.faceunity.nama.control.FaceBeautySkinControlView;
import com.faceunity.nama.control.FilterControlView;
import com.faceunity.nama.control.MakeupControlView;
import com.faceunity.nama.control.PropControlView;
import com.faceunity.nama.data.FaceUnityDataFactory;

/**
 * DESC：
 * Created on 2021/4/26
 */
public class FaceUnityView extends LinearLayout {

    private Context mContext;

    public FaceUnityView(Context context) {
        super(context);
        mContext = context;
        init();
    }

    public FaceUnityView(Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
        mContext = context;
        init();
    }

    public FaceUnityView(Context context, @Nullable AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        mContext = context;
        init();
    }


    private FaceUnityDataFactory mDataFactory;

    private CheckGroup mCheckGroupView;//底部菜单
    private FaceBeautySkinControlView mFaceBeautySkinControlView;//美肤菜单
    private FaceBeautyShapeControlView mFaceBeautyShapeControlView;//美颜菜单
    private FilterControlView mFilterControlView;//滤镜菜单
    private MakeupControlView mMakeupControlView;//美妆菜单
    private PropControlView mPropControlView;//道具菜单
    private BodyBeautyControlView mBodyBeautyControlView;//美体菜单
    private View lineView;//分割线


    private void init() {
        LayoutInflater.from(mContext).inflate(R.layout.layout_faceunity, this);
        initView();
        bindBottomView();
    }

    /**
     * 绑定数据工厂
     *
     * @param dataFactory FaceUnityDataFactory
     */
    public void bindDataFactory(FaceUnityDataFactory dataFactory) {
        mDataFactory = dataFactory;
        mFaceBeautySkinControlView.bindDataFactory(dataFactory.mFaceBeautyAndFilterDataFactory);
        mFaceBeautyShapeControlView.bindDataFactory(dataFactory.mFaceBeautyAndFilterDataFactory);
        mFilterControlView.bindDataFactory(dataFactory.mFaceBeautyAndFilterDataFactory);
        mMakeupControlView.bindDataFactory(dataFactory.mMakeupDataFactory);
        mPropControlView.bindDataFactory(dataFactory.mPropDataFactory);
        mBodyBeautyControlView.bindDataFactory(dataFactory.mBodyBeautyDataFactory);
        switch (dataFactory.currentFunctionIndex) {
            case -1:
                mCheckGroupView.check(-1);
                break;
            case 0:
                mCheckGroupView.check(R.id.radio_skin_beauty);
                break;
            case 1:
                mCheckGroupView.check(R.id.radio_shape_beauty);
                break;
            case 2:
                mCheckGroupView.check(R.id.radio_filter);
                break;
            case 3:
                mCheckGroupView.check(R.id.radio_sticker);
                break;
            case 4:
                mCheckGroupView.check(R.id.radio_makeup);
                break;
            case 5:
                mCheckGroupView.check(R.id.radio_body);
                break;
        }
    }

    /**
     * 初始化View
     */
    private void initView() {
        mCheckGroupView = findViewById(R.id.group_function);
        mFaceBeautySkinControlView = findViewById(R.id.control_beauty_skin);
        mFaceBeautyShapeControlView = findViewById(R.id.control_beauty_shape);
        mFilterControlView= findViewById(R.id.control_filter);
        mMakeupControlView = findViewById(R.id.control_makeup);
        mPropControlView = findViewById(R.id.control_prop);
        mBodyBeautyControlView = findViewById(R.id.control_body);
        lineView = findViewById(R.id.line);
    }


    /**
     * 底部功能菜单切换
     */
    private void bindBottomView() {
        mCheckGroupView.setOnCheckedChangeListener((group, checkedId) -> {
            if (checkedId == R.id.radio_skin_beauty) {
                showFunction(0);
                mDataFactory.onFunctionSelected(0);
            } else if (checkedId == R.id.radio_shape_beauty) {
                showFunction(1);
                mDataFactory.onFunctionSelected(1);
            } else if (checkedId == R.id.radio_filter) {
                showFunction(2);
                mDataFactory.onFunctionSelected(2);
            } else if (checkedId == R.id.radio_sticker) {
                showFunction(3);
                mDataFactory.onFunctionSelected(3);
            } else if (checkedId == R.id.radio_makeup) {
                showFunction(4);
                mDataFactory.onFunctionSelected(4);
            } else if (checkedId == R.id.radio_body) {
                showFunction(5);
                mDataFactory.onFunctionSelected(5);
            } else {
                showFunction(-1);
            }
        });
    }

    /**
     * UI菜单显示控制
     *
     * @param index Int
     */
    private void showFunction(int index) {
        mFaceBeautySkinControlView.setVisibility((index == 0) ? View.VISIBLE : View.GONE);
        if (index == 0) {
            mFaceBeautySkinControlView.updateOnSelected();
        }
        mFaceBeautyShapeControlView.setVisibility((index == 1) ? View.VISIBLE : View.GONE);
        if (index == 1) {
            mFaceBeautyShapeControlView.updateOnSelected();
        }
        mFilterControlView.setVisibility((index == 2) ? View.VISIBLE : View.GONE);
        mPropControlView.setVisibility((index == 3) ? View.VISIBLE : View.GONE);
        mMakeupControlView.setVisibility((index == 4) ? View.VISIBLE : View.GONE);
        mBodyBeautyControlView.setVisibility((index == 5) ? View.VISIBLE : View.GONE);
        if (index == 5) {
            mBodyBeautyControlView.updateOnSelected();
        }
        lineView.setVisibility((index != -1) ? View.VISIBLE : View.GONE);
    }
}
