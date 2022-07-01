package com.ss.video.rtc.demo.advanced.cfg;


import com.ss.video.rtc.demo.advanced.utils.SharedPrefsUtils;

public class CfgIntegerSP extends CfgSP<Integer>{

    public CfgIntegerSP(String spKey) {
        super(spKey);
    }

    @Override
    public Integer getValue() {
        return SharedPrefsUtils.getInt(mSPKey, getDefaultValue());
    }

    @Override
    public Integer getDefaultValue() {
        return 0;
    }

    @Override
    public void setValue(Object value) {
        SharedPrefsUtils.putInt(mSPKey, (Integer) value);
    }
}
