package com.ss.video.rtc.demo.meetingrtcdemo.core;

import android.app.Application;

import com.ss.video.rtc.demo.basic_module.utils.SPUtils;
import com.ss.video.rtc.demo.basic_module.utils.Utilities;
import com.ss.video.rtc.demo.meetingrtcdemo.resource.Constants;

public class MeetingApplication extends Application {

    public static String sUserName = "";
    public static String sUserID = "";

    @Override
    public void onCreate() {
        super.onCreate();
        SPUtils.initSP(this, Constants.SP_FILE_NAME);
        Utilities.initApp(this);

        sUserName = SPUtils.getString(Constants.SP_KEY_USER_NAME, "");
        sUserID = SPUtils.getString(Constants.SP_KEY_USER_ID, "");
    }
}
