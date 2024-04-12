package com.ss.video.rtc.demo.advanced.utils;

import android.content.Context;
import android.content.SharedPreferences;
import android.text.TextUtils;

import com.ss.video.rtc.demo.basic_module.utils.GsonUtils;
import com.ss.video.rtc.demo.basic_module.utils.Utilities;

public class SharedPrefsUtils {

    private static final String SP_NAME = "advanced_demo";

    private SharedPrefsUtils() {}

    private static volatile SharedPreferences sDefaultPrefs;

    private static SharedPreferences getDefaultPrefs() {
        if (sDefaultPrefs == null) {
            synchronized (SharedPrefsUtils.class) {
                if (sDefaultPrefs == null) {
                    sDefaultPrefs = Utilities.getApplicationContext().getSharedPreferences(SP_NAME,
                                    Context.MODE_PRIVATE);
                }
            }
        }
        return sDefaultPrefs;
    }

    private static void putValueInternal(String key, String value) {
        getDefaultPrefs().edit().putString(key, value).apply();
    }

    private static String getValueInternal(String key) {
        return getDefaultPrefs().getString(key, null);
    }

    public static boolean contains(String key) {
        return getDefaultPrefs().contains(key);
    }

    public static String getString(String key, String defValue) {
        return getValue(key, String.class, defValue);
    }

    public static void putString(String key, String value) {
        putValue(key, value);
    }

    public static int getInt(String key, int defValue) {
        return getValue(key, Integer.class, defValue);
    }

    public static void putInt(String key, int value) {
        putValue(key, value);
    }

    public static boolean getBoolean(String key, boolean defValue) {
        return getValue(key, Boolean.class, defValue);
    }

    public static void putBoolean(String key, boolean value) {
        putValue(key, value);
    }

    public static <T> T getValue(String key, Class<T> t, T defValue) {
        String vStr = getValueInternal(key);
        if (TextUtils.isEmpty(vStr)) {
            return defValue;
        }
        T ret = GsonUtils.gson().fromJson(vStr, t);
        return ret == null ? defValue : ret;
    }

    public static void putValue(String key, Object value) {
        String vStr = GsonUtils.gson().toJson(value);
        putValueInternal(key, vStr);
    }
}
