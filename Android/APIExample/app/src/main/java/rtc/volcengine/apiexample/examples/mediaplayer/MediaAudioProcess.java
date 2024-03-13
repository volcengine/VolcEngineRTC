package rtc.volcengine.apiexample.examples.mediaplayer;

import android.util.Log;

import com.ss.bytertc.engine.RTCVideo;
import com.ss.bytertc.engine.data.AudioChannel;
import com.ss.bytertc.engine.data.AudioSampleRate;
import com.ss.bytertc.engine.utils.AudioFrame;
import com.ss.ttm.player.AudioProcessor;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class MediaAudioProcess extends AudioProcessor {
    private static final String TAG = "MediaAudioProcess";

    private RTCVideo rtcVideo;
    private int sampleRate;
    private int channelNum;
    private boolean isPublishStream = false;
    private ByteBuffer mRTCBuffer;
    private int volume = 100;

    public MediaAudioProcess(RTCVideo rtcVideo) {
        this.rtcVideo = rtcVideo;
    }


    @Override
    public void audioOpen(int sampleRate, int channels, int duration, int format) {
        Log.i(TAG, "audioOpen: " + sampleRate + " " + channels + " " + duration + " "+ format);
        this.channelNum = channels;
        this.sampleRate = sampleRate;
    }

    @Override
    public void audioProcess(ByteBuffer[] byteBuffers, int samples, long timestamp) {
        Log.i(TAG, "audioProcess" + samples + " " + timestamp);
        // S16 格式一个声道中每个采样占两个字节
        int length = samples * channelNum * 2;
        if (mRTCBuffer == null || mRTCBuffer.capacity() < length) {
            mRTCBuffer = ByteBuffer.allocate(length);
            mRTCBuffer.order(ByteOrder.LITTLE_ENDIAN);
        }
        mRTCBuffer.clear();
        ByteBuffer srcBuffer0 = byteBuffers[0];
        srcBuffer0.order(ByteOrder.LITTLE_ENDIAN);
        ByteBuffer srcBuffer1 = null;
        if (channelNum > 1) {
            srcBuffer1 = byteBuffers[1];
            srcBuffer1.order(ByteOrder.LITTLE_ENDIAN);
        }
        // S16 双声道为 左右左右...
        for (int i = 0; i < samples; i++) {
            oneSampleFLTPtoS16(srcBuffer0, mRTCBuffer);
            if (srcBuffer1 != null) {
                oneSampleFLTPtoS16(srcBuffer1, mRTCBuffer);
            }
        }
        adjustVolume(mRTCBuffer, volume);

        AudioFrame frame = new AudioFrame(mRTCBuffer.array(), samples, AudioSampleRate.fromId(sampleRate), AudioChannel.fromId(channelNum));

        if (rtcVideo != null && isPublishStream) {
            rtcVideo.pushExternalAudioFrame(frame);
        }
    }

    private void adjustVolume(ByteBuffer buffer, float volume) {
        // Create a temporary buffer to hold the adjusted samples
        ByteBuffer tempBuffer = ByteBuffer.allocate(buffer.capacity());
        tempBuffer.order(buffer.order());

        // Adjust the volume of each 16-bit sample in the buffer
        buffer.rewind();
        while (buffer.hasRemaining()) {
            // Read the next 16-bit sample
            short sample = buffer.getShort();

            // Apply volume adjustment within the 0 to 400 scale
            sample = (short) (sample * volume / 100.0f);

            // Clip the sample to ensure it stays within the valid range
            sample = (short) Math.max(Short.MIN_VALUE, Math.min(Short.MAX_VALUE, sample));

            // Write the adjusted sample to the temporary buffer
            tempBuffer.putShort(sample);
        }

        // Reset position for subsequent reads
        buffer.rewind();

        // Copy the adjusted samples back to the original buffer
        tempBuffer.flip();
        buffer.put(tempBuffer);

        // Reset position for subsequent writes
        buffer.rewind();
    }

    @Override
    public void audioClose() {

    }

    @Override
    public void audioRelease(int i) {

    }

    public void enablePublishStream(boolean enable) {
        this.isPublishStream = enable;
    }

    public void setVolume(int volume) {
        this.volume = volume;
    }

    /*
     * 将一个采样的数据格式从 FLTP 转换为 S16
     */
    private void oneSampleFLTPtoS16(ByteBuffer srcBuffer, ByteBuffer dstBuffer) {
        float sample = srcBuffer.getFloat();
        int value = (int) (1.0f * sample * Short.MAX_VALUE);
        if (value > Short.MAX_VALUE) {
            value = Short.MAX_VALUE;
        } else if (value < Short.MIN_VALUE) {
            value = Short.MIN_VALUE;
        }
        dstBuffer.putShort((short) (value));
    }

}
