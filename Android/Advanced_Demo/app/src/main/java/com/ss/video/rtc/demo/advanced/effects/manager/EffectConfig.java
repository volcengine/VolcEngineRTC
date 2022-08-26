package com.ss.video.rtc.demo.advanced.effects.manager;

import android.content.Context;
import android.content.SharedPreferences;

import androidx.annotation.Nullable;

import com.ss.video.rtc.demo.basic_module.utils.GsonUtils;

/**
 * 美颜配置保存类
 */
public class EffectConfig {

    private final SharedPreferences mPreferences;

    public EffectConfig(Context context, String name) {
        mPreferences = context.getSharedPreferences(name, 0);
    }

    public void setConfig(String key, @Nullable Object object) {
        if (object == null) {
            mPreferences.edit().putString(key, null).apply();
            return;
        }
        String json = GsonUtils.gson().toJson(object);
        mPreferences.edit().putString(key, json).apply();
    }

    public @Nullable String getConfig(String key) {
        return mPreferences.getString(key, null);
    }
}
