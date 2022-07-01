package com.ss.video.rtc.demo.advanced.cfg;


import com.ss.video.rtc.demo.advanced.utils.SharedPrefsUtils;

public class CfgBooleanSP extends CfgSP<Boolean>{

    public CfgBooleanSP(String spKey) {
        super(spKey);
    }

    @Override
    public Boolean getValue() {
        return SharedPrefsUtils.getBoolean(mSPKey, getDefaultValue());
    }

    @Override
    public Boolean getDefaultValue() {
        return false;
    }

    @Override
    public void setValue(Object value) {
        SharedPrefsUtils.putBoolean(mSPKey, (Boolean) value);
    }
}
