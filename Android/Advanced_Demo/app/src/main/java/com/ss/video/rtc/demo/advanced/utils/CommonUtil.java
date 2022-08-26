package com.ss.video.rtc.demo.advanced.utils;

import android.content.Context;
import android.util.Log;
import android.widget.Toast;

import androidx.annotation.StringRes;

import com.ss.video.rtc.demo.basic_module.utils.SafeToast;
import com.ss.video.rtc.demo.basic_module.utils.Utilities;

import java.nio.ByteBuffer;
import java.nio.CharBuffer;
import java.nio.charset.Charset;
import java.nio.charset.CharsetDecoder;
import java.nio.charset.StandardCharsets;

public class CommonUtil {

    public static void showShortToast(Context context, String msg) {
        SafeToast.show(Utilities.getApplicationContext(), msg, Toast.LENGTH_SHORT);
    }

    public static void showShortToast(Context context, @StringRes int msgResId) {
        SafeToast.show(Utilities.getApplicationContext(), msgResId, Toast.LENGTH_SHORT);
    }

    public static void showLongToast(Context context, String msg) {
        SafeToast.show(Utilities.getApplicationContext(), msg, Toast.LENGTH_LONG);
    }

    public static void showLongToast(Context context, @StringRes int msgResId) {
        SafeToast.show(Utilities.getApplicationContext(), msgResId, Toast.LENGTH_LONG);
    }

    private static final String DEFAULT_TAG = "CommonUtil";

    public static void printDebugLog(String logMsg) {
        Log.d(DEFAULT_TAG, logMsg);
    }

    public static void printDebugLog(String tag, String logMsg) {
        Log.d(tag, logMsg);
    }

    public static void printErrorLog(String errMsg) {
        Log.e(DEFAULT_TAG, errMsg);
    }

    public static void printErrorLog(String tag, String errMsg) {
        Log.e(tag, errMsg);
    }

    public static byte[] nv21ToI420(byte[] data, int width, int height) {
        byte[] ret = new byte[data.length];
        int total = width * height;

        ByteBuffer bufferY = ByteBuffer.wrap(ret, 0, total);
        ByteBuffer bufferU = ByteBuffer.wrap(ret, total, total / 4);
        ByteBuffer bufferV = ByteBuffer.wrap(ret, total + total / 4, total / 4);

        bufferY.put(data, 0, total);
        for (int i = total; i < data.length; i += 2) {
            bufferV.put(data[i]);
            bufferU.put(data[i + 1]);
        }
        return ret;
    }

    public static String byteBufferToString(ByteBuffer buffer) {
        CharBuffer charBuffer;
        try {
            Charset charset = StandardCharsets.UTF_8;
            CharsetDecoder decoder = charset.newDecoder();
            charBuffer = decoder.decode(buffer);
            buffer.flip();
            return charBuffer.toString();
        } catch (Exception ex) {
            ex.printStackTrace();
            return null;
        }
    }
}
