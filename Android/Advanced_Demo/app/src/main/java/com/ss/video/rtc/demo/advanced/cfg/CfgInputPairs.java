package com.ss.video.rtc.demo.advanced.cfg;

import com.ss.video.rtc.demo.advanced.utils.SharedPrefsUtils;
import com.ss.video.rtc.demo.basic_module.utils.GsonUtils;

public abstract class CfgInputPairs<K, V> extends CfgPairs<K, V> {

    private final String mInputSpKey;
    private final String mApplyInputSpKey;
    protected final Class<V> mVClazz;

    public CfgInputPairs(String spKey, Class<K> kClazz, Class<V> vClazz) {
        super(spKey, kClazz);
        mVClazz = vClazz;
        mInputSpKey = spKey + "_apply_input_text";
        mApplyInputSpKey = spKey + "_apply_input_sp_key";
    }

    @Override
    @SuppressWarnings("unchecked")
    public V getValue() {
        if (SharedPrefsUtils.getBoolean(mApplyInputSpKey, false)) {
            K k = super.getKey();
            k = SharedPrefsUtils.getValue(mInputSpKey, mKClazz, k);
            if (k instanceof String && mVClazz.equals(String.class)) {
                return (V)k;
            }
            String json = GsonUtils.gson().toJson(k);
            return GsonUtils.gson().fromJson(json, mVClazz);
        }
        return super.getValue();
    }

    @Override
    public void applyKeyByIndex(int index) {
        SharedPrefsUtils.putBoolean(mApplyInputSpKey, false);
        super.applyKeyByIndex(index);
    }

    public void applyInputKey(String inputText) {
        SharedPrefsUtils.putBoolean(mApplyInputSpKey, true);
        SharedPrefsUtils.putValue(mInputSpKey, inputText);
    }

    public K getInputKey() {
        K k = super.getKey();
        return SharedPrefsUtils.getValue(mInputSpKey, mKClazz, k);
    }

    @Override
    public K getKey() {
        if (SharedPrefsUtils.getBoolean(mApplyInputSpKey, false)) {
            return getInputKey();
        } else {
            return super.getKey();
        }
    }
}
