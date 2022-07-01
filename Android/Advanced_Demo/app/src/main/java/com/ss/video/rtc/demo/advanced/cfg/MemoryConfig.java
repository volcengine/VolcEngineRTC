package com.ss.video.rtc.demo.advanced.cfg;

import java.util.HashMap;
import java.util.Map;

public class MemoryConfig {
    private static Map<String, Object> sMemoryConfigMap = new HashMap<>();

    public static void put(String key, Object value) {
        sMemoryConfigMap.put(key, value);
    }

    public static Object get(String key) {
        return sMemoryConfigMap.get(key);
    }

    public static int getInt(String key, int defaultValue) {
        Object obj = sMemoryConfigMap.get(key);
        if (obj instanceof Integer) {
            return (Integer) obj;
        }

        return defaultValue;
    }

    public static String getString(String key) {
        Object obj = sMemoryConfigMap.get(key);
        if (obj instanceof String) {
            return (String) obj;
        }

        return null;
    }

    public static boolean getBoolean(String key) {
        Object obj = sMemoryConfigMap.get(key);
        if (obj instanceof Boolean) {
            return (Boolean) obj;
        }

        return false;
    }
}
