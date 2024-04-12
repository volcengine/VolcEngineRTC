package com.ss.video.rtc.demo.advanced;

import android.app.Application;

import com.ss.video.rtc.demo.basic_module.utils.SPUtils;
import com.ss.video.rtc.demo.basic_module.utils.Utilities;

public class AdvancedApplication extends Application {

    @Override
    public void onCreate() {
        super.onCreate();
        Utilities.initApp(this);
        SPUtils.initSP(this, Constants.SP_FILE_NAME);
    }
}
