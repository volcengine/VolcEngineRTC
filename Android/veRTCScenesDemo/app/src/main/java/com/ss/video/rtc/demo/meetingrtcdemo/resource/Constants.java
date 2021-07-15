package com.ss.video.rtc.demo.meetingrtcdemo.resource;

public class Constants {
    private Constants() {
    }

    public static final boolean IS_TEST = true;

    public static final int ROOM_REQUEST_CODE = 99;
    public static final int REQUEST_CODE_DUPLICATE_LOGIN = 100;
    public static final int REQUEST_CODE_OF_SCREEN_SHARING = 101;

    public static final String SP_FILE_NAME = "meeting_sp";

    public static final String SP_KEY_VIDEO_CONFIG = "video_config";

    public static final String SP_KEY_USER_ID = "user_id";
    public static final String SP_KEY_USER_NAME = "user_name";
    public static final String SP_KEY_TOKEN = "token";

    public static final String REFER_KEY = "refer_key";
    public static final String REFER_LOGIN = "refer_login";
    public static final String REFER_ROOM = "refer_room";

    public static final String EXTRA_KEY_USER_ID = "user_id";
    public static final String EXTRA_KEY_USER_UNIFORM_NAME = "user_uniform_name";
    public static final String EXTRA_KEY_MEETING_ID = "meeting_id";
    public static final String EXTRA_KEY_TOKEN = "token";
    public static final String EXTRA_KEY_MEETING_LAST = "meeting_last";
    public static final String EXTRA_KEY_USER_NAME = "user_name";
    public static final String EXTRA_KEY_ROOM_TITLE = "room_title";
    public static final String EXTRA_KEY_IS_CREATE_ROOM = "is_create_room";
    public static final String EXTRA_KEY_VIEW_TYPE = "view_type";

    public static final String EXTRA_VIEW_TYPE_ALL = "extra_view_type_all";
    public static final String EXTRA_VIEW_TYPE_MINE = "extra_view_type_mine";

    public static final int VOLUME_INTERVAL_MS = 1000;
    public static final int VOLUME_SMOOTH = 8;
    public static final int VOLUME_MIN_THRESHOLD = 10;
    public static final int VOLUME_OVERFLOW_THRESHOLD = 100000;
}
