package rtc.volcengine.apiexample.examples.ThirdBeauty.Fubeauty;

import android.opengl.EGL14;
import android.opengl.EGLContext;
import android.opengl.GLES20;
import android.opengl.Matrix;
import android.os.Handler;
import android.os.HandlerThread;
import android.util.Log;

import com.bytedance.realx.base.ThreadUtils;
import com.bytedance.realx.video.EglBase;
import com.bytedance.realx.video.EglBase14;
import com.bytedance.realx.video.GlUtil;
import com.faceunity.core.enumeration.FUInputBufferEnum;
import com.faceunity.core.enumeration.FUInputTextureEnum;
import com.faceunity.nama.FUConfig;
import com.faceunity.nama.FURenderer;
import com.faceunity.nama.utils.FuDeviceUtils;
import com.ss.bytertc.engine.data.VideoBufferType;
import com.ss.bytertc.engine.data.VideoPixelFormat;
import com.ss.bytertc.engine.video.IVideoFrame;
import com.ss.bytertc.engine.video.IVideoProcessor;

import java.nio.ByteBuffer;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import javax.microedition.khronos.egl.EGL10;

import rtc.volcengine.apiexample.common.data.DemoVideoFrame;

public class VideoProcessor extends IVideoProcessor {

    private static final String TAG = "SimpleVideoProcessor";

    private final float[] texMatrix = new float[16];

    int mFrameCount = 0;

    public final FURenderer mFURenderer = FURenderer.getInstance();
    public boolean renderSwitch;

    private int skipFrame = 0;
    private HandlerThread mHandlerThread;
    private Handler mHandler;
    private ExecutorService mThreadPool;
    FrameBuffer mFrameBuffer = null;
    private EglBase14.Context mSharedContext = null;
    private EglBase14 mEglbase = null;


    static class FrameBuffer {
        int mFrameBufferId = 0;
        int mTextureId = 0;
        int mTexWidth = 0;
        int mTexHeight = 0;

        public FrameBuffer(int w, int h) {
            mTexWidth = w;
            mTexHeight = h;

            // fbo
            final int frameBuffers[] = new int[1];
            GLES20.glGenFramebuffers(1, frameBuffers, 0);
            mFrameBufferId = frameBuffers[0];
            GLES20.glBindFramebuffer(GLES20.GL_FRAMEBUFFER, mFrameBufferId);

            // texture
            mTextureId = GlUtil.generateTexture(GLES20.GL_TEXTURE_2D);

            GLES20.glActiveTexture(GLES20.GL_TEXTURE0);
            GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, mTextureId);

            GLES20.glTexImage2D(GLES20.GL_TEXTURE_2D, 0, GLES20.GL_RGBA, w, h, 0, GLES20.GL_RGBA,
                    GLES20.GL_UNSIGNED_BYTE, null);
            GLES20.glFramebufferTexture2D(GLES20.GL_FRAMEBUFFER, GLES20.GL_COLOR_ATTACHMENT0,
                    GLES20.GL_TEXTURE_2D, mTextureId, 0);

            GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, 0);
            GLES20.glBindFramebuffer(GLES20.GL_FRAMEBUFFER, 0);
            GlUtil.checkNoGLES2Error("new FrameBuffer");
        }

        public void dispose() {
            mTexWidth = 0;
            mTexHeight = 0;
            // delete texture
            GLES20.glDeleteTextures(1, new int[]{mTextureId}, 0);
            mTextureId = 0;

            // delete fbo
            GLES20.glDeleteFramebuffers(1, new int[] {mFrameBufferId}, 0);
            mFrameBufferId = 0;

            GlUtil.checkNoGLES2Error("releaseGl");
        }

        public void attachCurrent() {
            GLES20.glBindFramebuffer(GLES20.GL_FRAMEBUFFER, mFrameBufferId);
            GLES20.glViewport(0, 0, mTexWidth, mTexHeight);
            GlUtil.checkNoGLES2Error("attachCurrent");
        }

        public void detachCurrent() {
            GLES20.glBindFramebuffer(GLES20.GL_FRAMEBUFFER, 0);
            GlUtil.checkNoGLES2Error("detachCurrent");
        }
    }

    public VideoProcessor() {
        Matrix.setIdentityM(texMatrix, 0);
        mHandlerThread = new HandlerThread("VideoProcessor");
        mHandlerThread.start();
        mHandler = new Handler(mHandlerThread.getLooper());
        mThreadPool = Executors.newSingleThreadExecutor();
    }

    @Override
    public IVideoFrame processVideoFrame(IVideoFrame frame) {
//        Log.d(TAG, "processVideoFrame mFrameCount:" + frame.getTextureID() + ", glcontext: " + EGL14.eglGetCurrentContext());
        try {
            mFrameCount++;
            switch (frame.pixelFormat()) {
                case I420:
                    return processI420Frame(frame);
                case TEXTURE_2D:
                    return processTextureFrame(frame);
            }
        } catch (Exception e) {
            Log.e("SimpleVideoProcessor", "processFrame Exception" + e.toString());
            e.printStackTrace();
        }
        return null;
    }

    public void setRenderEnable(boolean enabled) {
        renderSwitch = enabled;
    }

    public IVideoFrame processI420Frame(IVideoFrame frame) {
//        LogUtil.d("SimpleVideoProcessor", "processI420Frame renderSwitch" + renderSwitch);
        if (!renderSwitch) {
            return frame;
        }

        int width = frame.width();
        int height = frame.height();
        int strip_y = frame.planeStride(0);
        int strip_u = frame.planeStride(1);
        int strip_v =  frame.planeStride(2);
        int chroma_height = (height + 1) / 2;
//        LogUtil.d("SimpleVideoProcessor", "processI420Frame textureID:" + frame.getTextureID() + ",width:" + width + ",height:" + height);
        if (skipFrame > 0) {
            skipFrame--;
            return frame;
        }
        mFURenderer.setInputOrientation(frame.rotation().value());
        if (FUConfig.DEVICE_LEVEL > FuDeviceUtils.DEVICE_LEVEL_MID){
            //高性能设备
            mFURenderer.cheekFaceNum();
        }
        mFURenderer.setInputBufferType(FUInputBufferEnum.FU_FORMAT_I420_BUFFER);
        int texId = mFURenderer.onDrawFrameDualInput(null,
                frame.textureId(), frame.width(),
                frame.height());

        int[] plane_lens = new int[]{strip_y * height, strip_u * chroma_height, strip_v * chroma_height};
        ByteBuffer[] yuv_buffers = new ByteBuffer[3];
        int[] yuv_stride = new int[3];
        for(int i = 0; i < 3; ++i) {
            if (yuv_buffers[i] == null || yuv_buffers[i].capacity() < plane_lens[i]) {
                yuv_buffers[i] = ByteBuffer.allocateDirect(plane_lens[i]);
            }
            ByteBuffer src_plane_buffer = frame.planeData(i).slice();
            src_plane_buffer.rewind();
            src_plane_buffer.limit(plane_lens[i]);
            ByteBuffer plane = yuv_buffers[i];
            plane.put(src_plane_buffer);
            yuv_stride[i] = frame.planeStride(i);
        }

        IVideoFrame src_frame = new DemoVideoFrame(frame.pixelFormat().value(),
                width, height,
                frame.rotation().value(), frame.timestampUs(),
                3, yuv_stride, yuv_buffers);

        return src_frame;
    }

    public synchronized IVideoFrame processTextureFrame(IVideoFrame frame) {
//        Log.d("SimpleVideoProcessor", "processTextureFrame frame rotation: " + frame.getRotation().value());
        IVideoFrame ret_frame;
        try {
             ret_frame = ThreadUtils.invokeAtFrontUninterruptibly(mHandler, () -> {
                updateEGLEnv(frame);

                Log.d("SimpleVideoProcessor", "egl context: " + EGL14.eglGetCurrentContext());
                if (!renderSwitch) {
                    return frame;
                }

                if (skipFrame > 0) {
                    skipFrame--;
                    return frame;
                }

                mFURenderer.setInputOrientation(frame.rotation().value());
                if (FUConfig.DEVICE_LEVEL > FuDeviceUtils.DEVICE_LEVEL_MID){
                    //高性能设备
                    mFURenderer.cheekFaceNum();
                }
                mFURenderer.setInputTextureType(FUInputTextureEnum.FU_ADM_FLAG_COMMON_TEXTURE);
                int textureId = mFURenderer.onDrawFrameDualInput(
                        null,
                        frame.textureId(), frame.width(),
                        frame.height()
                );

                if (skipFrame > 0) {
                    skipFrame--;
                    textureId = frame.textureId();
                }

                IVideoFrame retframe = new DemoVideoFrame(VideoPixelFormat.TEXTURE_2D.value(),
                        frame.width(), frame.height(),
                        frame.rotation().value(), frame.timestampUs(),
                        textureId, frame.textureMatrix(),
                        EGL14.eglGetCurrentContext());

                Log.d("SimpleVideoProcessor", "processTextureFrame-texId:"+textureId);
                return  retframe;

            });
        } catch (RuntimeException e) {
            Log.e(TAG, " failed to do custom video process", e);
            return null;
        }
        return ret_frame;
    }

    void updateEGLEnv(IVideoFrame inputFrame) {
        if (inputFrame == null) {
            return;
        }
        final int[] CONFIG_PIXEL_BUFFER = {
                EGL10.EGL_RENDERABLE_TYPE, EglBase.EGL_OPENGL_ES2_BIT,
                EGL10.EGL_SURFACE_TYPE, EGL10.EGL_PBUFFER_BIT,
                EGL10.EGL_RED_SIZE, 8,
                EGL10.EGL_GREEN_SIZE, 8,
                EGL10.EGL_BLUE_SIZE, 8,
                EGL10.EGL_ALPHA_SIZE, 8,
                EGL10.EGL_DEPTH_SIZE, 8,
                EGL10.EGL_STENCIL_SIZE, 8,
                EGL10.EGL_NONE
        };
        VideoBufferType originFrameType = inputFrame.bufferType();
        final boolean isTextureBuffer = originFrameType == VideoBufferType.GL_TEXTURE;
        boolean isEglEnvChanged = false;
        if (isTextureBuffer) {
            long nativeSharedContext = 0;
            EGLContext eglContext = inputFrame.eglContext();
            EglBase14.Context newSharedContext = new EglBase14.Context(eglContext);
            if (mSharedContext != null) {
                nativeSharedContext = mSharedContext.getNativeEglContext();
            }
            // check the new frame eglcontext is equal with the old one.
            // if context changed. we not sure current egl env chould handle the new frame.
            // in case, we change our shared context, and rebind the current thread's gl env.
            if (newSharedContext.getNativeEglContext() != nativeSharedContext) {
                // mark gl env has changed.
                isEglEnvChanged = true;
                mSharedContext = newSharedContext;
            }
        }
        if (mEglbase == null) {
            //whatever last eglcontext, if we haven't mEglBase right now, need init first
            isEglEnvChanged = true;
        }

        if (!isEglEnvChanged) {
            return;
        }
        try {
            if (mEglbase != null) {
                // release old eglenv
                // we had old glenv initialized, notify user to clear old resource first
                releaseEGL();
            }
            // create new eglenv
            mEglbase = new EglBase14(mSharedContext, CONFIG_PIXEL_BUFFER);
            mEglbase.createDummyPbufferSurface();
            mEglbase.makeCurrent();
            initGL();
        } catch (RuntimeException e) {
            mEglbase.release();
            mEglbase = null;
            Log.e(TAG, " failed to create mEglbase", e);
        }
    }
    // only work processor EGL context run
    void releaseEGL() {
        if (mEglbase == null) {
            return;
        }
        mEglbase.makeCurrent();
        mEglbase.release();
        mEglbase = null;

        if (mFrameBuffer != null) {
            mFrameBuffer.dispose();
            mFrameBuffer = null;
        }
    }

    void initGL() {
        // you can init Gl here or later in processTextureFrame.
    }

}
