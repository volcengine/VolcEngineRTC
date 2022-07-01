package com.ss.video.rtc.demo.advanced.cfg;

import com.ss.video.rtc.demo.advanced.utils.SharedPrefsUtils;

import java.util.ArrayList;
import java.util.Collection;
import java.util.LinkedHashMap;
import java.util.List;

public abstract class CfgPairs<K, V> {

    protected final String mSpKey;
    protected final String mSpKeyNoSet;
    protected final Class<K> mKClazz;
    private final LinkedHashMap<Object, V> mMap = new LinkedHashMap<>();
    final Object NULL_OBJ = new Object();

    public boolean isNoSet() {
        return SharedPrefsUtils.getBoolean(mSpKeyNoSet, false);
    }

    public void setNoSet(boolean noSet) {
        SharedPrefsUtils.putBoolean(mSpKeyNoSet, noSet);
    }

    public CfgPairs(String spKey, Class<K> kClazz) {
        mSpKey = spKey;
        mSpKeyNoSet = mSpKey + "_cfg_no_set";
        mKClazz = kClazz;
    }

    public void append(K k, V v) {
        if (k == null) {
            mMap.put(NULL_OBJ, v);
        } else {
            mMap.put(k, v);
        }
    }

    public V getValue() {
        Object obj = getKey();
        if (obj == null) {
            return mMap.get(NULL_OBJ);
        }
        return mMap.get(getKey());
    }

    public K getKey() {
        return SharedPrefsUtils.getValue(mSpKey, mKClazz, getDefaultKey());
    }

    public abstract K getDefaultKey();

    public List<V> getValues() {
        return new ArrayList<>(mMap.values());
    }
    @SuppressWarnings("unchecked")
    public V getValue(int index) {
        Collection<V> values = mMap.values();
        return (V) values.toArray()[index];
    }
    @SuppressWarnings("unchecked")
    public K getKey(int index) {
        Object obj = mMap.keySet().toArray()[index];
        if (obj == NULL_OBJ) {
            return null;
        }
        return (K) obj;
    }

    public void applyKeyByIndex(int index) {
        setKey(getKey(index));
    }

    public void setKey(Object obj) {
        @SuppressWarnings("unchecked")
        K k = (K) obj;
        SharedPrefsUtils.putValue(mSpKey, k);
    }
}
