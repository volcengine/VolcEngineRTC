package com.ss.video.rtc.demo.advanced.external;

import android.Manifest;
import android.app.Activity;
import android.content.pm.PackageManager;
import android.graphics.ImageFormat;
import android.graphics.SurfaceTexture;
import android.hardware.Camera;
import android.opengl.GLES11Ext;
import android.os.Handler;
import android.os.HandlerThread;
import android.os.Process;
import android.util.Log;
import android.view.Surface;

import java.util.List;

public class CustomCapture {
    private static final String TAG = "CustomCapture";
    private static int mWidth = 0;
    private static int mHeight = 0;
    private static final int VIDEO_MIN_FPS = 15;
    private static final int VIDEO_MAX_FPS = 24;

    private volatile static CustomCapture sInstance = null;

    private Camera mCamera;
    private int mCameraID = Camera.CameraInfo.CAMERA_FACING_FRONT;
    private HandlerThread mCameraThread;
    private Handler mCameraHandler;
    private byte[] mPreviewData;
    private final SurfaceTexture surfaceTexture = new SurfaceTexture(GLES11Ext.GL_TEXTURE_EXTERNAL_OES);
    private Camera.PreviewCallback previewCallback;
    private Activity mHostActivity;

    private CustomCapture() {
    }

    public static CustomCapture ins() {
        if (sInstance == null) {
            synchronized (CustomCapture.class) {
                if (sInstance == null) {
                    sInstance = new CustomCapture();
                }
            }
        }
        return sInstance;
    }

    public boolean hasVideoPermission(Activity activity) {
        int res = activity.checkPermission(Manifest.permission.CAMERA, android.os.Process.myPid(), Process.myUid());
        return res == PackageManager.PERMISSION_GRANTED;
    }

    public int getCameraId(){
        return mCameraID;
    }

    public void startCapture(Activity hostActivity ,Camera.PreviewCallback previewCallback) {
        this.mHostActivity = hostActivity;
        if (!hasVideoPermission(hostActivity)) {
            return;
        }
        if (mCameraThread != null) {
            stopThread();
        }
        mCameraThread = new HandlerThread("CustomCameraThread");
        mCameraThread.start();
        mCameraHandler = new Handler(mCameraThread.getLooper());
        mCameraHandler.post(() -> {
            mCamera = Camera.open(Camera.CameraInfo.CAMERA_FACING_FRONT);
            CustomCapture.this.previewCallback = previewCallback;
            initCamera(surfaceTexture, previewCallback);
        });
    }

    private void initCamera(SurfaceTexture surfaceTexture, Camera.PreviewCallback previewCallback) {
        try {
            mCamera.setErrorCallback((errorCode, c) -> {
                Log.d(TAG, "errorCode: " + errorCode);
            });
            setCameraDisplayOrientation();
            Camera.Parameters parameters = mCamera.getParameters();
            checkBuffer(parameters.getSupportedPreviewSizes());
            parameters.setPreviewSize(mWidth, mHeight);
            parameters.setPreviewFrameRate(VIDEO_MIN_FPS);
            parameters.setPreviewFormat(ImageFormat.NV21);
            mCamera.setParameters(parameters);
            mCamera.addCallbackBuffer(mPreviewData);
            mCamera.setPreviewCallbackWithBuffer(previewCallback);
            mCamera.setPreviewTexture(surfaceTexture);

            mCamera.startPreview();
        } catch (Exception e) {
            e.printStackTrace();
            Log.e(TAG, e.getMessage(), e);
        }
    }

    public void setCameraDisplayOrientation() {
        if (!hasVideoPermission(mHostActivity)) {
            return;
        }
        if (mHostActivity == null){
            mCamera.setDisplayOrientation(90);
            return;
        }
        android.hardware.Camera.CameraInfo info = new android.hardware.Camera.CameraInfo();
        android.hardware.Camera.getCameraInfo(mCameraID, info);
        int rotation = mHostActivity.getWindowManager().getDefaultDisplay().getRotation();
        int degrees = 0;
        switch (rotation) {
            case Surface.ROTATION_0:
                degrees = 0;
                break;
            case Surface.ROTATION_90:
                degrees = 90;
                break;
            case Surface.ROTATION_180:
                degrees = 180;
                break;
            case Surface.ROTATION_270:
                degrees = 270;
                break;
        }
        int result;
        if (info.facing == Camera.CameraInfo.CAMERA_FACING_FRONT) {
            result = (info.orientation + degrees) % 360;
            result = (360 - result) % 360;  // compensate the mirror
        } else {  // back-facing
            result = (info.orientation - degrees + 360) % 360;
        }
        mCamera.setDisplayOrientation(result);
    }

    public void switchCamera(){
        if (previewCallback == null){
            return;
        }
        if (!hasVideoPermission(mHostActivity)) {
            return;
        }
        mCamera.setPreviewCallback(null);
        mCamera.stopPreview();
        mCamera.release();
        if (mCameraID == Camera.CameraInfo.CAMERA_FACING_FRONT) {
            mCameraID = Camera.CameraInfo.CAMERA_FACING_BACK;
        } else {
            mCameraID = Camera.CameraInfo.CAMERA_FACING_FRONT;
        }
        mCamera = Camera.open(mCameraID);
        initCamera(surfaceTexture, previewCallback);
    }

    public void updateBuffer() {
        if (!hasVideoPermission(mHostActivity)) {
            return;
        }
        mCamera.addCallbackBuffer(mPreviewData);
    }

    public void checkBuffer(List<Camera.Size> sizes) {
        if (sizes == null) {
            return;
        }
        Camera.Size targetSize = null;
        for (Camera.Size size : sizes) {
            if (targetSize == null || targetSize.width < size.width) {
                targetSize = size;
            }
        }
        if (targetSize != null) {
            mWidth = targetSize.width;
            mHeight = targetSize.height;
        }
        mPreviewData = new byte[mWidth * mHeight * 3 / 2];
    }

    public void stopCapture() {
        if (mCameraHandler == null) {
            return;
        }
        if (!hasVideoPermission(mHostActivity)) {
            return;
        }
        mCameraHandler.post(() -> {
            if (mCamera != null) {
                mCamera.setPreviewCallback(null);
                mCamera.stopPreview();
                mCamera.release();
                mCamera = null;
                stopThread();
            }
        });
    }

    private void stopThread() {
        if (mCameraThread != null) {
            mCameraThread.quit();
            mCameraThread = null;
        }
        if (mCameraHandler != null) {
            mCameraHandler = null;
        }
    }
}
