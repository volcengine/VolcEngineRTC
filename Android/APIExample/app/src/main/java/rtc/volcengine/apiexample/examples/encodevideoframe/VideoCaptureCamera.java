package rtc.volcengine.apiexample.examples.encodevideoframe;

import android.graphics.ImageFormat;
import android.graphics.SurfaceTexture;
import android.hardware.Camera;
import android.media.MediaCodec;
import android.media.MediaCodecInfo;
import android.media.MediaFormat;
import android.util.Log;
import android.view.TextureView;


import com.ss.bytertc.engine.RTCEngine;
import com.ss.bytertc.engine.data.StreamInfo;
import com.ss.bytertc.engine.data.VideoCodecType;
import com.ss.bytertc.engine.data.VideoPictureType;
import com.ss.bytertc.engine.data.VideoRotation;
import com.ss.bytertc.engine.handler.IExternalVideoEncoderEventHandler;
import com.ss.bytertc.engine.mediaio.RTCEncodedVideoFrame;

import java.io.IOException;
import java.nio.ByteBuffer;


public class VideoCaptureCamera extends IExternalVideoEncoderEventHandler implements  TextureView.SurfaceTextureListener, Camera.PreviewCallback {

    private static final String TAG = "VideoCaptureCamera";
    private static int VIDEO_WIDTH = 1280;
    private static int VIDEO_HEIGHT = 960;
    private static final int FRAME_RATE = 30;
    private static final int BIT_RATE = 4000000;

    private Camera camera;
    private TextureView textureView;
    private MediaCodec mediaCodec;
    private RTCEngine rtcVideo;

    public VideoCaptureCamera(RTCEngine rtcVideo, TextureView textureView) {
        this.textureView = textureView;
        this.rtcVideo = rtcVideo;
    }


    @Override
    public void onPreviewFrame(byte[] data, Camera camera) {
        // Process the camera preview frame here
        byte[] i420bytes = NV21ToNV21(data, VIDEO_WIDTH, VIDEO_HEIGHT);
        if (isStart) {
            encodeAndPushFrame(i420bytes);
        }
    }


    public void openCamera() {
        camera = Camera.open();
        Camera.Parameters parameters = camera.getParameters();
        Camera.Size previewSize = parameters.getPreviewSize();
        parameters.setPreviewFormat(ImageFormat.NV21);
        parameters.setPreviewSize(VIDEO_WIDTH, VIDEO_HEIGHT);
        camera.setParameters(parameters);
        if (textureView != null) {
            textureView.setRotation(90);
        }
    }

    public void releaseCamera() {
        if (camera != null) {
            camera.setPreviewCallback(null);
            camera.stopPreview();
            camera.release();
            camera = null;
        }
    }

    private void startCameraPreview() {
        try {
            camera.setPreviewTexture(textureView.getSurfaceTexture());
            camera.setPreviewCallback(this);
            camera.startPreview();
        } catch (IOException e) {
            Log.e(TAG, "Error starting camera preview: " + e.getMessage());
        }
    }

    private void initMediaCodec() {
        try {
            mediaCodec = MediaCodec.createEncoderByType(MediaFormat.MIMETYPE_VIDEO_AVC);
            MediaFormat format = MediaFormat.createVideoFormat(MediaFormat.MIMETYPE_VIDEO_AVC, VIDEO_WIDTH, VIDEO_HEIGHT);
            format.setInteger(MediaFormat.KEY_BIT_RATE, BIT_RATE);
            format.setInteger(MediaFormat.KEY_FRAME_RATE, FRAME_RATE);
            format.setInteger(MediaFormat.KEY_COLOR_FORMAT, MediaCodecInfo.CodecCapabilities.COLOR_FormatYUV420SemiPlanar);
            format.setInteger(MediaFormat.KEY_I_FRAME_INTERVAL, 1);
            mediaCodec.configure(format, null, null, MediaCodec.CONFIGURE_FLAG_ENCODE);
            mediaCodec.start();
        } catch (IOException e) {
            Log.e(TAG, "Error initializing MediaCodec: " + e.getMessage());
        }
    }

    private void releaseMediaCodec() {
        if (mediaCodec != null) {
            mediaCodec.stop();
            mediaCodec.release();
            mediaCodec = null;
        }
    }

    private void encodeAndPushFrame(byte[] data) {
        try {
            ByteBuffer[] inputBuffers = mediaCodec.getInputBuffers();
            ByteBuffer[] outputBuffers = mediaCodec.getOutputBuffers();
            int inputBufferIndex = mediaCodec.dequeueInputBuffer(-1);
            if (inputBufferIndex >= 0) {
                ByteBuffer inputBuffer = inputBuffers[inputBufferIndex];
                inputBuffer.clear();
                inputBuffer.put(data);
                mediaCodec.queueInputBuffer(inputBufferIndex, 0, data.length, 0, 0);
            }

            MediaCodec.BufferInfo bufferInfo = new MediaCodec.BufferInfo();
            int outputBufferIndex = mediaCodec.dequeueOutputBuffer(bufferInfo, 0);
            while (outputBufferIndex >= 0) {
                ByteBuffer outputBuffer = outputBuffers[outputBufferIndex];
                byte[] encodedData = new byte[bufferInfo.size];
                outputBuffer.get(encodedData);
                // Process the encoded frame here
                pushEncodedFrame(encodedData, bufferInfo);

                mediaCodec.releaseOutputBuffer(outputBufferIndex, false);
                outputBufferIndex = mediaCodec.dequeueOutputBuffer(bufferInfo, 0);
            }
        } catch (Exception e) {
            Log.e(TAG, "Error encoding frame: " + e.getMessage());
        }
    }

    private ByteBuffer mEncodedBuffer;
    private ByteBuffer configData = ByteBuffer.allocateDirect(1);
    private void pushEncodedFrame(byte[] encodedData, MediaCodec.BufferInfo bufferInfo) {
        int frameType = 0;
        if (mEncodedBuffer != null && encodedData.length > mEncodedBuffer.capacity()) {
            mEncodedBuffer = ByteBuffer.allocateDirect(encodedData.length);
        }
        // Implement the logic to push encoded frames using the pushExternalEncodedVideoFrame(streamIndex, videoIndex, encodedFrame) function
        // You need to handle I-frames, P-frames, and B-frames separately based on the bufferInfo.flags
        if ((bufferInfo.flags & MediaCodec.BUFFER_FLAG_CODEC_CONFIG) != 0) {
            // This is the codec config data, you may need to handle it differently
            // pushExternalEncodedVideoFrame(streamIndex, videoIndex, encodedData);
            if (configData.capacity() < bufferInfo.size) {
                configData = ByteBuffer.allocateDirect(bufferInfo.size);
            }
            // Save Codec-specific Data
            // 保存Codec-specific Data
            configData.put(encodedData);

        } else if ((bufferInfo.flags & MediaCodec.BUFFER_FLAG_KEY_FRAME) != 0) {
            // This is an I-frame
            // pushExternalEncodedVideoFrame(streamIndex, videoIndex, encodedData);
            frameType = 1; // 或者使用 VideoPictureType.fromId(1) 获取枚举值

            mEncodedBuffer = ByteBuffer.allocateDirect(
                    configData.capacity() + bufferInfo.size);
            configData.rewind();
            // If it is a keyframe, it is necessary to combine Codec-specific Data and keyframe data.
            // 为关键帧时需要拼接Codec-specific Data和关键帧数据
            mEncodedBuffer.put(configData);
            mEncodedBuffer.put(encodedData);
            mEncodedBuffer.position(0);

            byte[] buffer = new byte[mEncodedBuffer.remaining()];
            mEncodedBuffer.get(buffer);

        } else if ((bufferInfo.flags & MediaCodec.BUFFER_FLAG_SYNC_FRAME) != 0) {
            // P 帧
            frameType = 2; // 或者使用 VideoPictureType.fromId(2) 获取枚举值
            mEncodedBuffer.clear();
            mEncodedBuffer.put(encodedData, 0, encodedData.length);
        } else {
            // B 帧
            frameType = 3; // 或者使用 VideoPictureType.fromId(3) 获取枚举值
            mEncodedBuffer.clear();
            mEncodedBuffer.put(encodedData, 0, encodedData.length);
        }

        RTCEncodedVideoFrame videoFrame = new RTCEncodedVideoFrame(
                mEncodedBuffer,
                bufferInfo.presentationTimeUs,
                bufferInfo.presentationTimeUs,
                VIDEO_WIDTH,
                VIDEO_HEIGHT,
                VideoCodecType.VIDEO_CODEC_TYPE_H264,
                VideoPictureType.fromId(frameType),
                VideoRotation.VIDEO_ROTATION_90);
        rtcVideo.pushExternalEncodedVideoFrame(0,  videoFrame);

    }

    @Override
    public void onSurfaceTextureAvailable(SurfaceTexture surface, int width, int height) {
        // Initialize MediaCodec when the surface is available
        mEncodedBuffer = ByteBuffer.allocateDirect(width * height * 3 / 2);
        openCamera();
        initMediaCodec();
        startCameraPreview();

    }

    boolean isStart = false;

    @Override
    public void onSurfaceTextureSizeChanged(SurfaceTexture surface, int width, int height) {
        // Handle surface size change if needed
    }

    @Override
    public boolean onSurfaceTextureDestroyed(SurfaceTexture surface) {
        // Release MediaCodec when the surface is destroyed
        releaseMediaCodec();
        return true;
    }

    @Override
    public void onSurfaceTextureUpdated(SurfaceTexture surface) {
        // Handle surface update if needed
    }

    @Override
    public void onStart(String streamId, StreamInfo streamInfo) {
        isStart = true;
    }

    @Override
    public void onStop(String streamId, StreamInfo streamInfo){
        isStart = false;
    }

    @Override
    public void onRateUpdate(String streamId, StreamInfo streamInfo, int videoIndex, int fps, int bitrateKbps) {

    }

    @Override
    public void onRequestKeyFrame(String streamId, StreamInfo streamInfo, int videoIndex) {

    }

    @Override
    public void onActiveVideoLayer(String streamId, StreamInfo streamInfo, int videoIndex, boolean active) {

    }

    public static byte[] NV21ToI420(byte[] data, int width, int height) {
        byte[] ret = new byte[width*height*3/2];
        int total = width * height;

        ByteBuffer bufferY = ByteBuffer.wrap(ret, 0, total);
        ByteBuffer bufferV = ByteBuffer.wrap(ret, total, total / 4);
        ByteBuffer bufferU = ByteBuffer.wrap(ret, total + total / 4, total / 4);

        bufferY.put(data, 7, total);
        for (int i=total+7; i<data.length; i+=2) {
            bufferV.put(data[i]);
            if (i+1 < data.length) {
                bufferU.put(data[i+1]);
            }
        }

        return ret;
    }

    public static byte[] NV21ToNV21(byte[] data, int width, int height) {
        byte[] ret = new byte[data.length];
        int total = width * height;

        // 复制Y平面数据
        System.arraycopy(data, 0, ret, 0, total);

        // 交织复制U和V平面数据
        int offset = total;
        for (int i = total + 1; i < data.length; i += 2) {
            ret[offset++] = data[i];
            ret[offset++] = data[i - 1];
        }

        return ret;
    }
}
