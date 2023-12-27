package com.faceunity.nama;

import android.content.Context;
import android.hardware.Camera;
import android.os.Handler;
import android.os.Looper;

import com.faceunity.core.callback.OperateCallback;
import com.faceunity.core.entity.FURenderInputData;
import com.faceunity.core.entity.FURenderOutputData;
import com.faceunity.core.enumeration.CameraFacingEnum;
import com.faceunity.core.enumeration.FUAIProcessorEnum;
import com.faceunity.core.enumeration.FUAITypeEnum;
import com.faceunity.core.enumeration.FUTransformMatrixEnum;
import com.faceunity.core.faceunity.FUAIKit;
import com.faceunity.core.faceunity.FURenderConfig;
import com.faceunity.core.faceunity.FURenderKit;
import com.faceunity.core.faceunity.FURenderManager;
import com.faceunity.core.model.facebeauty.FaceBeautyBlurTypeEnum;
import com.faceunity.core.utils.CameraUtils;
import com.faceunity.core.utils.FULogger;
import com.faceunity.nama.listener.FURendererListener;
import com.faceunity.nama.utils.FuDeviceUtils;
import java.io.File;
import java.util.HashMap;


/**
 * DESC：
 * Created on 2021/4/26
 */
public class FURenderer extends IFURenderer {


    public volatile static FURenderer INSTANCE;

    public static FURenderer getInstance() {
        if (INSTANCE == null) {
            synchronized (FURenderer.class) {
                if (INSTANCE == null) {
                    INSTANCE = new FURenderer();
                }
            }
        }
        return INSTANCE;
    }

    /**
     * 状态回调监听
     */
    private FURendererListener mFURendererListener;


    /* 特效FURenderKit*/
    public  FURenderKit mFURenderKit = FURenderKit.getInstance();

    /* 特效FURenderKit*/
    public final FUAIKit mFUAIKit = FUAIKit.getInstance();

    /* AI道具*/
    private final String BUNDLE_AI_FACE = "model" + File.separator + "ai_face_processor.bundle";
    private final String BUNDLE_AI_HUMAN = "model" + File.separator + "ai_human_processor.bundle";

    /* 相机角度-朝向映射 */
    private final HashMap<Integer, CameraFacingEnum> cameraOrientationMap = new HashMap<>();

    /*检测类型*/
    private FUAIProcessorEnum aIProcess = FUAIProcessorEnum.HUMAN_PROCESSOR;

    /*检测标识*/
    private int aIProcessTrackStatus = -1;

    /**
     *
     * @return version
     */
    public String getVersion() {
        return mFURenderKit.getVersion();
    }

    /**
     * 初始化鉴权
     *
     * @param context
     */
    @Override
    public void setup(Context context) {
        FURenderManager.setKitDebug(FULogger.LogLevel.TRACE);
        FURenderManager.setCoreDebug(FULogger.LogLevel.OFF);
        FURenderManager.registerFURender(context, authpack.A(), new OperateCallback() {
            @Override
            public void onSuccess(int errorCode, String errorMessage) {
                FULogger.d("FURenderer","onSuccess errorCode:"+errorCode+",errorMessage:"+errorMessage);
                if (errorCode == FURenderConfig.OPERATE_SUCCESS_AUTH) {
                    mFUAIKit.loadAIProcessor(BUNDLE_AI_FACE, FUAITypeEnum.FUAITYPE_FACEPROCESSOR);
                    mFUAIKit.loadAIProcessor(BUNDLE_AI_HUMAN, FUAITypeEnum.FUAITYPE_HUMAN_PROCESSOR);

                    int cameraFrontOrientation = CameraUtils.INSTANCE.getCameraOrientation(Camera.CameraInfo.CAMERA_FACING_FRONT);
                    int cameraBackOrientation = CameraUtils.INSTANCE.getCameraOrientation(Camera.CameraInfo.CAMERA_FACING_BACK);
                    cameraOrientationMap.put(cameraFrontOrientation, CameraFacingEnum.CAMERA_FRONT);
                    cameraOrientationMap.put(cameraBackOrientation, CameraFacingEnum.CAMERA_BACK);
                }
            }

            @Override
            public void onFail(int errorCode, String errorMessage) {
                FULogger.d("FURenderer","onSuccess errorCode:"+errorCode+",errorMessage:"+errorMessage);
            }
        });
    }

    /**
     * 开启合成状态
     */
    @Override
    public void bindListener(FURendererListener mFURendererListener) {
        FULogger.d("FURenderer","bindListener");
        this.mFURendererListener = mFURendererListener;
    }


    /**
     * 单输入接口，输入texture，必须在具有 GL 环境的线程调用
     *
     * @param texId  纹理 ID
     * @param width  宽
     * @param height 高
     * @return 0
     */
    public int onDrawFrameSingleInput(int texId, int width, int height) {
//        FULogger.d("FURenderer","onDrawFrameSingleInput texId:"+texId+",width:"+width+",height:"+height);
        prepareDrawFrame();

        FURenderInputData inputData = new FURenderInputData(width, height);
        inputData.setTexture(new FURenderInputData.FUTexture(inputTextureType, texId));
        FURenderInputData.FURenderConfig config = inputData.getRenderConfig();
        config.setExternalInputType(externalInputType);
        config.setInputOrientation(inputOrientation);
        config.setDeviceOrientation(deviceOrientation);
        config.setInputBufferMatrix(inputBufferMatrix);
        config.setInputTextureMatrix(inputTextureMatrix);
        config.setCameraFacing(cameraFacing);
        config.setOutputMatrix(outputMatrix);
        mCallStartTime = System.nanoTime();
        if (FUConfig.DEVICE_LEVEL > FuDeviceUtils.DEVICE_LEVEL_MID)//高性能设备
            cheekFaceNum();
        FURenderOutputData outputData = mFURenderKit.renderWithInput(inputData);
        mSumCallTime += System.nanoTime() - mCallStartTime;
        if (outputData.getTexture() != null && outputData.getTexture().getTexId() > 0) {
            return outputData.getTexture().getTexId();
        }
        return 0;
    }

    /**
     * 检查当前人脸数量
     */
    public void cheekFaceNum() {
//        FULogger.d("FURenderer","cheekFaceNum");
        //根据有无人脸 + 设备性能 判断开启的磨皮类型
        float faceProcessorGetConfidenceScore = FUAIKit.getInstance().getFaceProcessorGetConfidenceScore(0);
        if (faceProcessorGetConfidenceScore >= 0.95) {
            //高端手机并且检测到人脸开启均匀磨皮，人脸点位质
            if (FURenderKit.getInstance().getFaceBeauty() != null && FURenderKit.getInstance().getFaceBeauty().getBlurType() != FaceBeautyBlurTypeEnum.EquallySkin) {
                FURenderKit.getInstance().getFaceBeauty().setBlurType(FaceBeautyBlurTypeEnum.EquallySkin);
                FURenderKit.getInstance().getFaceBeauty().setEnableBlurUseMask(true);
            }
        } else {
            if (FURenderKit.getInstance().getFaceBeauty() != null && FURenderKit.getInstance().getFaceBeauty().getBlurType() != FaceBeautyBlurTypeEnum.FineSkin) {
                FURenderKit.getInstance().getFaceBeauty().setBlurType(FaceBeautyBlurTypeEnum.FineSkin);
                FURenderKit.getInstance().getFaceBeauty().setEnableBlurUseMask(false);
            }
        }
    }

    /**
     * 双输入接口，输入 buffer 和 texture，必须在具有 GL 环境的线程调用
     * 由于省去数据拷贝，性能相对最优，优先推荐使用。
     * 缺点是无法保证 buffer 和纹理对齐，可能出现点位和效果对不上的情况。
     * @param img    NV21 buffer
     * @param texId  纹理 ID
     * @param width  宽
     * @param height 高
     * @return
     */
    @Override
    public int onDrawFrameDualInput(byte[] img, int texId, int width, int height) {
//        FULogger.d("FURenderer","onDrawFrameDualInput texId:"+texId+",width:"+width+",height:"+height);
        prepareDrawFrame();
        FURenderInputData inputData = new FURenderInputData(width, height);
        /*注释掉Buffer配置，启用单纹理模式，防止Buffer跟纹理存在不对齐造成，美妆偏移*/
//        inputData.setImageBuffer(new FURenderInputData.FUImageBuffer(inputBufferType, img));//设置为单Buffer输入
        inputData.setTexture(new FURenderInputData.FUTexture(inputTextureType, texId));
        FURenderInputData.FURenderConfig config = inputData.getRenderConfig();
        config.setExternalInputType(externalInputType);
        config.setInputOrientation(inputOrientation);
        config.setDeviceOrientation(deviceOrientation);
        config.setInputBufferMatrix(inputBufferMatrix);
        config.setInputTextureMatrix(inputTextureMatrix);
        config.setOutputMatrix(outputMatrix);
        config.setCameraFacing(cameraFacing);
        mCallStartTime = System.nanoTime();
        FURenderOutputData outputData = mFURenderKit.renderWithInput(inputData);
        mSumCallTime += System.nanoTime() - mCallStartTime;
        if (outputData.getTexture() != null && outputData.getTexture().getTexId() > 0) {
            return outputData.getTexture().getTexId();
        }
        return texId;

    }

    public void init(){
        FULogger.d("FURenderer","init");
        if (mFURendererListener != null) {
            mFURendererListener.onPrepare();
        }
    }

    /**
     * 释放资源
     */
    @Override
    public void release() {
        FULogger.d("FURenderer","release");
        mFURenderKit.release();
        aIProcessTrackStatus = -1;
    }

    public void removeListener() {
        mFURendererListener = null;
    }


    /**
     * 渲染前置执行
     *
     * @return
     */
    private void prepareDrawFrame() {
//        FULogger.d("FURenderer","prepareDrawFrame");
        benchmarkFPS();
        // AI检测
        trackStatus();
    }

    //region AI识别
    /**
     * 设置输入数据朝向
     *
     * @param inputOrientation
     */
    @Override
    public void setInputOrientation(int inputOrientation) {
        FULogger.d("FURenderer","setInputOrientation inputOrientation:"+inputOrientation);
        if (cameraOrientationMap.containsKey(inputOrientation)) {
            CameraFacingEnum cameraFacingEnum = cameraOrientationMap.get(inputOrientation);
            if (cameraFacingEnum == CameraFacingEnum.CAMERA_FRONT) {
                setInputBufferMatrix(FUTransformMatrixEnum.CCROT0);
                setInputTextureMatrix(FUTransformMatrixEnum.CCROT0);
                setOutputMatrix(FUTransformMatrixEnum.CCROT0_FLIPVERTICAL);
                setCameraFacing(CameraFacingEnum.CAMERA_BACK);
            } else {
                setInputBufferMatrix(FUTransformMatrixEnum.CCROT0_FLIPHORIZONTAL);
                setInputTextureMatrix(FUTransformMatrixEnum.CCROT0_FLIPHORIZONTAL);
                setOutputMatrix(FUTransformMatrixEnum.CCROT180);
                setCameraFacing(CameraFacingEnum.CAMERA_FRONT);
            }
        }
        super.setInputOrientation(inputOrientation);
    }

    @Override
    public void setDeviceOrientation(int deviceOrientation) {
        FULogger.d("FURenderer","setDeviceOrientation deviceOrientation:"+deviceOrientation);
        if (cameraFacing == CameraFacingEnum.CAMERA_BACK) {
            if (deviceOrientation == 0) deviceOrientation = 180;
            if (deviceOrientation == 180) deviceOrientation = 0;
        }
        super.setDeviceOrientation(deviceOrientation);
    }

    /**
     * 设置检测类型
     *
     * @param type
     */
    @Override
    public void setAIProcessTrackType(FUAIProcessorEnum type) {
        FULogger.d("FURenderer","setAIProcessTrackType type:"+type.name());
        aIProcess = type;
        aIProcessTrackStatus = -1;
    }

    /**
     * 设置FPS检测
     *
     * @param enable
     */
    @Override
    public void setMarkFPSEnable(boolean enable) {
//        FULogger.d("FURenderer","setMarkFPSEnable enable:"+enable);
        mIsRunBenchmark = enable;
    }


    /**
     * AI识别数目检测
     */
    private void trackStatus() {
        FULogger.d("FURenderer","trackStatus aIProcess:"+aIProcess);
        int trackCount;
        if (aIProcess == FUAIProcessorEnum.HAND_GESTURE_PROCESSOR) {
            trackCount = mFURenderKit.getFUAIController().handProcessorGetNumResults();
        } else if (aIProcess == FUAIProcessorEnum.HUMAN_PROCESSOR) {
            trackCount = mFURenderKit.getFUAIController().humanProcessorGetNumResults();
        } else {
            trackCount = mFURenderKit.getFUAIController().isTracking();
        }
        FULogger.d("FURenderer","trackStatus trackCount:"+trackCount);
        if (trackCount != aIProcessTrackStatus) {
            aIProcessTrackStatus = trackCount;
        } else {
            return;
        }
        if (mFURendererListener != null) {
            mFURendererListener.onTrackStatusChanged(aIProcess, trackCount);
        }
    }
    //endregion AI识别

    //------------------------------FPS 渲染时长回调相关定义------------------------------------

    private static final int NANO_IN_ONE_MILLI_SECOND = 1_000_000;
    private static final int NANO_IN_ONE_SECOND = 1_000_000_000;
    private static final int FRAME_COUNT = 20;
    private boolean mIsRunBenchmark = false;
    private int mCurrentFrameCount;
    private long mLastFrameTimestamp;
    private long mSumCallTime;
    private long mCallStartTime;

    private void benchmarkFPS() {
//        FULogger.d("FURenderer","benchmarkFPS mIsRunBenchmark:"+mIsRunBenchmark);
        if (!mIsRunBenchmark) {
            return;
        }
//        FULogger.d("FURenderer","benchmarkFPS mCurrentFrameCount:"+mCurrentFrameCount+",FRAME_COUNT:"+FRAME_COUNT);
        if (++mCurrentFrameCount == FRAME_COUNT) {
            long tmp = System.nanoTime();
            double fps = (double) NANO_IN_ONE_SECOND / ((double) (tmp - mLastFrameTimestamp) / FRAME_COUNT);
            double renderTime = (double) mSumCallTime / FRAME_COUNT / NANO_IN_ONE_MILLI_SECOND;
            mLastFrameTimestamp = tmp;
            mSumCallTime = 0;
            mCurrentFrameCount = 0;

            if (mFURendererListener != null) {
                mFURendererListener.onFpsChanged(fps, renderTime);
            }
        }
    }


}
