package com.ss.video.rtc.demo.advanced.cfg;

import com.ss.video.rtc.demo.advanced.utils.SharedPrefsUtils;

public class CfgStringSP extends CfgSP<String>{

    public CfgStringSP(String spKey) {
        super(spKey);
    }

    @Override
    public String getValue() {
        return SharedPrefsUtils.getString(mSPKey, getDefaultValue());
    }

    @Override
    public String getDefaultValue() {
        return "";
    }

    @Override
    public void setValue(Object value) {
        SharedPrefsUtils.putString(mSPKey, (String) value);
    }
}
