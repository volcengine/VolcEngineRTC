package com.ss.video.rtc.demo.advanced.cfg;

public abstract class CfgSP<T> {

    protected final String mSPKey;

    public CfgSP(String spKey) {
        mSPKey = spKey;
    }

    public abstract T getValue();

    public abstract T getDefaultValue();

    public abstract void setValue(Object value);
}