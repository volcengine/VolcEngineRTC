package com.ss.video.rtc.demo.advanced.external;

import android.content.Context;
import android.opengl.EGLContext;
import android.os.Build;
import android.os.Handler;
import android.os.HandlerThread;
import android.view.TextureView;

import com.bytedance.realx.base.ThreadUtils;
import com.bytedance.realx.video.EglBase;
import com.bytedance.realx.video.RendererCommon;
import com.ss.bytertc.engine.ui.VideoFrameRender;
import com.ss.bytertc.engine.video.IVideoSink;
import com.ss.bytertc.engine.video.VideoFrame;

import java.util.concurrent.atomic.AtomicBoolean;

public class CustomRenderView extends TextureView implements IVideoSink {
    private VideoFrameRender mVideoFrameRender;
    private EglBase mEglBase;

    private HandlerThread mRenderThread;
    private Handler mRenderHandler;
    private EGLContext mEGLContext;
    private boolean mIsFirstFrame = true;
    private RendererCommon.ScalingType mScalingType = RendererCommon.ScalingType.SCALE_ASPECT_FILL;
    private boolean mIsMirror = false;
    private AtomicBoolean mReleased = new AtomicBoolean(false);

    public CustomRenderView(Context context) {
        super(context);
        mRenderThread = new HandlerThread("custom-render-thread");
        mRenderThread.start();
        mRenderHandler = new Handler(mRenderThread.getLooper());
    }

    public void release() {
        if (mReleased.getAndSet(true)) {
            return;
        }
        if (mRenderHandler != null) {
            mRenderHandler.removeCallbacksAndMessages(null);
            mRenderHandler = null;
        }
        if (mRenderThread != null) {
            mRenderThread.quitSafely();
        }
    }

    public void setScalingType(RendererCommon.ScalingType scalingType) {
        this.mScalingType = scalingType;
        if (mVideoFrameRender != null) {
            this.mVideoFrameRender.setScalingType(scalingType);
        }
    }

    private synchronized void applyEglContext(EGLContext sharedContext) {
        ThreadUtils.invokeAtFrontUninterruptibly(mRenderHandler, ()-> {
            if (mEglBase != null) {
                mEglBase.release();
            }
            if (sharedContext != null) {
                mEglBase = EglBase.createEgl14(sharedContext, EglBase.CONFIG_PLAIN);
            } else {
                mEglBase = EglBase.createEgl14(EglBase.CONFIG_PLAIN);
            }
            mEglBase.createDummyPbufferSurface();
            mEglBase.makeCurrent();
        });

        if (mVideoFrameRender != null) {
            mVideoFrameRender.release();
        }

        mVideoFrameRender = new VideoFrameRender("ByteSurfaceViewRender");
        mVideoFrameRender.setRenderView(this, null);
        mVideoFrameRender.init(mEglBase.getEglBaseContext());
        mVideoFrameRender.setProcessTextureLopper(mRenderThread.getLooper());
        mVideoFrameRender.onStart();
        mVideoFrameRender.setScalingType(mScalingType);
        mVideoFrameRender.setMirror(mIsMirror);
    }

    @Override
    public synchronized void onFrame(VideoFrame frame) {
        if (mReleased.get()) {
            return;
        }
        EGLContext currentContext = frame.getEGLContext();
        if (!checkIsSameEglContext(currentContext, mEGLContext) || mIsFirstFrame) {
            mIsFirstFrame = false;
            applyEglContext(currentContext);
            mEGLContext = currentContext;
        }
        mVideoFrameRender.consumeVideoFrame(frame);
    }

    @Override
    public int getRenderElapse() {
        return 0;
    }

    public void setMirror(boolean mirror) {
        mIsMirror = mirror;
        if (mVideoFrameRender != null) {
            mVideoFrameRender.setMirror(mIsMirror);
        }
    }

    private boolean checkIsSameEglContext(EGLContext compare1, EGLContext compare2) {
        return getNativeContext(compare1) == getNativeContext(compare2);
    }

    private long getNativeContext(EGLContext context) {
        if (context == null) {
            return 0;
        }
        return Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP ? context.getNativeHandle()
                : context.getHandle();
    }
}