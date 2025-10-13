package rtc.volcengine.apiexample.common.data;
import android.opengl.EGLContext;

import com.ss.bytertc.engine.data.CameraId;
import com.ss.bytertc.engine.data.VideoBufferType;
import com.ss.bytertc.engine.data.VideoContentType;
import com.ss.bytertc.engine.data.VideoFrameData;
import com.ss.bytertc.engine.data.VideoPixelFormat;
import com.ss.bytertc.engine.data.VideoRotation;
import com.ss.bytertc.engine.video.FovVideoFrameInfo;
import com.ss.bytertc.engine.video.IVideoFrame;

import java.nio.ByteBuffer;
import java.util.concurrent.atomic.AtomicInteger;

public class DemoVideoFrame implements IVideoFrame {
    private VideoFrameData mVfd = null;
    private CameraId mCameraId = CameraId.CAMERA_ID_INVALID;
    private final AtomicInteger mRefCount = new AtomicInteger(1);

    /*
     * only create RAW_MEMORY VideoFrame constructor
     * planeData only support Direct memory
     * */
    public DemoVideoFrame(int pixelFormat, int width, int height, int rotation, long timestampUs,
                          int numberOfPlanes, int[] planeStride, ByteBuffer[] planeData){
        mVfd = new VideoFrameData();
        mVfd.bufferType = VideoBufferType.RAW_MEMORY;
        mVfd.pixelFormat = VideoPixelFormat.fromId(pixelFormat);
        mVfd.contentType = VideoContentType.NORMAL_FRAME;
        mVfd.width = width;
        mVfd.height = height;
        mVfd.rotation = VideoRotation.fromId(rotation);
        mVfd.timestampUs = timestampUs;
        mVfd.seiData = null;
        mVfd.roiData = null;
        mVfd.numberOfPlanes = numberOfPlanes;
        mVfd.planeData = planeData;
        mVfd.planeStride = planeStride;
        mVfd.textureId = 0;
        mVfd.textureMatrix = null;
        mVfd.eglContext = null;
        mVfd.fovTileInfo = null;
        mCameraId = CameraId.CAMERA_ID_INVALID;
        switch (mVfd.pixelFormat) {
            case I420:
            case NV12:
            case NV21:
            case RGBA:
                break;
            default: {
                mVfd.pixelFormat = VideoPixelFormat.UNKNOWN;
                mVfd.numberOfPlanes = 0;
                mVfd.planeData = null;
                mVfd.planeStride = null;
                break;
            }
        }
        for (int i = 0; mVfd.planeData != null && i < mVfd.planeData.length; ++i) {
            if (!mVfd.planeData[i].isDirect()) {
                mVfd.pixelFormat = VideoPixelFormat.UNKNOWN;
                mVfd.numberOfPlanes = 0;
                mVfd.planeData = null;
                mVfd.planeStride = null;
            }
        }
    }
    /*
     * only create GL_TEXTURE VideoFrame constructor
     * */
    public DemoVideoFrame(int pixelFormat, int width, int height, int rotation, long timestampUs,
                          int textureId, float[] textureMatrix, EGLContext eglCtxHandle){
        mVfd = new VideoFrameData();
        mVfd.bufferType = VideoBufferType.GL_TEXTURE;
        mVfd.pixelFormat = VideoPixelFormat.fromId(pixelFormat);
        mVfd.contentType = VideoContentType.NORMAL_FRAME;
        mVfd.width = width;
        mVfd.height = height;
        mVfd.rotation = VideoRotation.fromId(rotation);
        mVfd.timestampUs = timestampUs;
        mVfd.seiData = null;
        mVfd.roiData = null;
        mVfd.numberOfPlanes = 0;
        mVfd.planeData = null;
        mVfd.planeStride = null;
        mVfd.textureId = textureId;
        mVfd.textureMatrix = textureMatrix;
        mVfd.eglContext = eglCtxHandle;
        mVfd.fovTileInfo = null;
        mCameraId = CameraId.CAMERA_ID_INVALID;
        switch (mVfd.pixelFormat) {
            case TEXTURE_2D:
            case TEXTURE_OES:
                break;
            default: {
                mVfd.pixelFormat = VideoPixelFormat.UNKNOWN;
                mVfd.textureId = 0;
                mVfd.textureMatrix = null;
                mVfd.eglContext = null;
                break;
            }
        }
    }

    @Override
    public VideoBufferType bufferType() { return mVfd.bufferType; }
    @Override
    public VideoPixelFormat pixelFormat() { return mVfd.pixelFormat; }
    @Override
    public VideoContentType contentType() {  return mVfd.contentType; }
    @Override
    public long timestampUs() { return mVfd.timestampUs;  }
    @Override
    public int width() { return  mVfd.width;}
    @Override
    public int height() {return mVfd.height;}
    @Override
    public VideoRotation rotation() {return  mVfd.rotation;}
    @Override
    public int numberOfPlanes() {return  mVfd.numberOfPlanes;}
    @Override
    public ByteBuffer planeData(int planeIndex) {
        if (mVfd.planeData != null && planeIndex >= 0 && planeIndex < mVfd.planeData.length)
            return mVfd.planeData[planeIndex];
        else
            return null;
    }
    @Override
    public int planeStride(int planeIndex) {
        if (mVfd.planeStride != null && planeIndex >=0 && planeIndex <= mVfd.planeStride.length)
            return  mVfd.planeStride[planeIndex];
        else
            return 0;
    }
    @Override
    public ByteBuffer seiData() { return mVfd.seiData; }
    @Override
    public int textureId() { return  mVfd.textureId; }
    @Override
    public float[] textureMatrix() { return  mVfd.textureMatrix; }
    @Override
    public EGLContext eglContext() { return  mVfd.eglContext; }
    @Override
    public void addRef() {
        int preval = mRefCount.getAndIncrement();
        if(preval <1 ){
            throw new ArithmeticException("addRef on an object that has already been destroyed.");
        }
    }
    @Override
    public long releaseRef() {
        int preval = mRefCount.getAndDecrement();
        if(preval ==1 ){
            if (mVfd != null) {
                mVfd.pixelFormat = VideoPixelFormat.UNKNOWN;
                mVfd.width = 0;
                mVfd.height = 0;
                mVfd.seiData = null;
                mVfd.roiData = null;
                mVfd.numberOfPlanes = 0;
                mVfd.planeData = null;
                mVfd.planeStride = null;
                mVfd.textureMatrix = null;
                mVfd.eglContext = null;
                mVfd.fovTileInfo = null;
            }
        }
        // we allow decrement on an released object, just return the ref count for debugging
        return  mRefCount.get();
    }
    @Override
    public FovVideoFrameInfo fovTileInfo() {return mVfd.fovTileInfo; }
    @Override
    public CameraId cameraId() { return mCameraId; }


}

