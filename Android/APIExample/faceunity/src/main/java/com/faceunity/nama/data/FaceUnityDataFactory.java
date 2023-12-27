package com.faceunity.nama.data;

import com.faceunity.nama.FUConfig;
import com.faceunity.core.enumeration.FUAIProcessorEnum;
import com.faceunity.core.faceunity.FUAIKit;
import com.faceunity.core.faceunity.FURenderKit;
import com.faceunity.nama.FURenderer;
import com.faceunity.nama.utils.FuDeviceUtils;

/**
 * DESC：
 * Created on 2021/4/25
 * 下标 0美肤、1美型、2滤镜、3贴纸、4美妆、5美体
 */
public class FaceUnityDataFactory {
    /**
     * 道具数据工厂
     */
    public FaceBeautyAndFilterDataFactory mFaceBeautyAndFilterDataFactory;//美颜或者滤镜
    public BodyBeautyDataFactory mBodyBeautyDataFactory;
    public MakeupDataFactory mMakeupDataFactory;
    public PropDataFactory mPropDataFactory;


    private FURenderKit mFURenderKit = FURenderKit.getInstance();
    private FURenderer mFURenderer = FURenderer.getInstance();

    /**
     * 道具加载标识
     */
    public int currentFunctionIndex;
    private boolean hasFaceBeautyOrFilterLoaded = false;
    private boolean hasBodyBeautyLoaded = false;
    private boolean hasMakeupLoaded = false;
    private boolean hasPropLoaded = false;


    public FaceUnityDataFactory(int index) {
        currentFunctionIndex = index;
        mFaceBeautyAndFilterDataFactory = new FaceBeautyAndFilterDataFactory();
        mBodyBeautyDataFactory = new BodyBeautyDataFactory();
        mMakeupDataFactory = new MakeupDataFactory(0);
        mPropDataFactory = new PropDataFactory(0);
    }

    /**
     * FURenderKit加载当前特效
     */
    public void bindCurrentRenderer() {
        bindCurrentRenderer(true);
    }

    /**
     * FURenderKit加载当前特效
     */
    public void bindCurrentRenderer(boolean needBindFaceBeauty) {
        hasFaceBeautyOrFilterLoaded = needBindFaceBeauty;
        //高端机开启小脸检测
        FUAIKit.getInstance().faceProcessorSetFaceLandmarkQuality(FUConfig.DEVICE_LEVEL);
        if (FUConfig.DEVICE_LEVEL  > FuDeviceUtils.DEVICE_LEVEL_MID)
            FUAIKit.getInstance().fuFaceProcessorSetDetectSmallFace(true);
        //选中哪一项加载哪一项道具
        switch (currentFunctionIndex) {
            case 0://美肤
            case 1://美型
            case 2://滤镜
                mFaceBeautyAndFilterDataFactory.bindCurrentRenderer();
                hasFaceBeautyOrFilterLoaded = true;
                break;
            case 3:
                mPropDataFactory.bindCurrentRenderer();
                hasPropLoaded = true;
                break;

            case 4:
                mMakeupDataFactory.bindCurrentRenderer();
                hasMakeupLoaded = true;
                break;
            case 5:
                mBodyBeautyDataFactory.bindCurrentRenderer();
                hasBodyBeautyLoaded = true;
                break;
        }
        //补充没有选中某项但是需要做效果则靠下面这个逻辑
        if (hasFaceBeautyOrFilterLoaded) {
            mFaceBeautyAndFilterDataFactory.bindCurrentRenderer();
        }
        if (hasPropLoaded && currentFunctionIndex != 3) {
            mPropDataFactory.bindCurrentRenderer();
        }
        if (hasMakeupLoaded && currentFunctionIndex != 4) {
            mMakeupDataFactory.bindCurrentRenderer();
        }
        if (hasBodyBeautyLoaded && currentFunctionIndex != 5) {
            mBodyBeautyDataFactory.bindCurrentRenderer();
        }

        if (currentFunctionIndex == 5) {
            mFURenderKit.getFUAIController().setMaxFaces(1);
            mFURenderer.setAIProcessTrackType(FUAIProcessorEnum.HUMAN_PROCESSOR);
        } else {
            mFURenderKit.getFUAIController().setMaxFaces(4);
            mFURenderer.setAIProcessTrackType(FUAIProcessorEnum.FACE_PROCESSOR);
        }
    }

    /**
     * 道具功能切换
     */
    public void onFunctionSelected(int index) {
        currentFunctionIndex = index;
        switch (index) {
            case 0://美肤
            case 1://美型
            case 2://滤镜
                if (!hasFaceBeautyOrFilterLoaded) {
                    mFaceBeautyAndFilterDataFactory.bindCurrentRenderer();
                    hasFaceBeautyOrFilterLoaded = true;
                }
                mFURenderKit.getFUAIController().setMaxFaces(4);
                mFURenderer.setAIProcessTrackType(FUAIProcessorEnum.FACE_PROCESSOR);
                break;
            case 3://贴纸
                if (!hasPropLoaded) {
                    mPropDataFactory.bindCurrentRenderer();
                    hasPropLoaded = true;
                }
                mFURenderKit.getFUAIController().setMaxFaces(4);
                mFURenderer.setAIProcessTrackType(FUAIProcessorEnum.FACE_PROCESSOR);
                break;
            case 4://美妆
                if (!hasMakeupLoaded) {
                    mMakeupDataFactory.bindCurrentRenderer();
                    hasMakeupLoaded = true;
                }
                mFURenderKit.getFUAIController().setMaxFaces(4);
                mFURenderer.setAIProcessTrackType(FUAIProcessorEnum.FACE_PROCESSOR);
                break;
            case 5://美体
                if (!hasBodyBeautyLoaded) {
                    mBodyBeautyDataFactory.bindCurrentRenderer();
                    hasBodyBeautyLoaded = true;
                }
                mFURenderKit.getFUAIController().setMaxFaces(1);
                mFURenderer.setAIProcessTrackType(FUAIProcessorEnum.HUMAN_PROCESSOR);
                break;
        }
    }
}
