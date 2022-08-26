package com.ss.video.rtc.demo.advanced.effects.model;

import android.content.Context;
import android.text.TextUtils;
import android.util.Log;

import com.google.gson.reflect.TypeToken;
import com.ss.video.rtc.demo.advanced.effects.manager.EffectConfig;
import com.ss.video.rtc.demo.basic_module.utils.GsonUtils;

import java.util.Arrays;
import java.util.List;

/**
 * 美颜模型数据
 */
public class EffectModel {

    private static final String TAG = "BeautyModel";

    private static final String CONFIG_FILE_NAME = "effect_module";
    private static final String SP_KEY_BEAUTY_LIST = "sp_key_beauty_list";
    private static final String SP_KEY_FILTER_LIST = "sp_key_filter_list";
    private static final String SP_KEY_STICKER_LIST = "sp_key_sticker_list";
    private static final String SP_KEY_VIRTUAL_BACKGROUND_LIST = "sp_key_virtual_background_list";

    private final EffectConfig mEffectConfig;
    private final EffectSection mBeautySection = new EffectSection("美颜", true, null);
    private final EffectSection mStickerSection = new EffectSection("贴纸", false, null);
    private final EffectSection mFilterSection = new EffectSection("滤镜", true, null);
    private final EffectSection mVirtualBackgroundSection = new EffectSection("背景分割", false, null);

    public EffectModel(Context context) {
        mEffectConfig = new EffectConfig(context, CONFIG_FILE_NAME);
    }

    public EffectSection getBeautySection() {
        List<? extends EffectNode> beautyEffectNodes = mBeautySection.effectNodes;
        if (beautyEffectNodes == null) {
            String json = mEffectConfig.getConfig(SP_KEY_BEAUTY_LIST);

            if (TextUtils.isEmpty(json)) {
                beautyEffectNodes = createBeautyList();
            } else {
                try {
                    beautyEffectNodes = GsonUtils.gson().fromJson(json, new TypeToken<List<BeautyEffectNode>>() {
                    }.getType());
                } catch (Exception e) {
                    beautyEffectNodes = createBeautyList();
                    Log.e(TAG, "getBeautySection() exception : " + json);
                }
            }
            mBeautySection.effectNodes = beautyEffectNodes;
        }
        return mBeautySection;
    }

    public EffectSection getStickerSection() {
        List<? extends EffectNode> stickerEffectNodes = mStickerSection.effectNodes;
        if (stickerEffectNodes == null) {
            String json = mEffectConfig.getConfig(SP_KEY_STICKER_LIST);

            if (TextUtils.isEmpty(json)) {
                stickerEffectNodes = createStickerList();
            } else {
                try {
                    stickerEffectNodes = GsonUtils.gson().fromJson(json, new TypeToken<List<StickerEffectNode>>() {
                    }.getType());
                } catch (Exception e) {
                    Log.e(TAG, "getStickerSection() exception : " + json);
                    stickerEffectNodes = createStickerList();
                }
            }
            mStickerSection.effectNodes = stickerEffectNodes;
        }
        return mStickerSection;
    }

    public EffectSection getFilterSection() {
        List<? extends EffectNode> filterEffectNodes = mFilterSection.effectNodes;
        if (filterEffectNodes == null) {
            String json = mEffectConfig.getConfig(SP_KEY_FILTER_LIST);

            if (TextUtils.isEmpty(json)) {
                filterEffectNodes = createFilterList();
            } else {
                try {
                    filterEffectNodes = GsonUtils.gson().fromJson(json, new TypeToken<List<FilterEffectNode>>() {
                    }.getType());
                } catch (Exception e) {
                    Log.e(TAG, "getFilterSection() exception : " + json);
                    filterEffectNodes = createFilterList();
                }
            }
            mFilterSection.effectNodes = filterEffectNodes;
        }
        return mFilterSection;
    }

    public EffectSection getVirtualBackgroundSection() {
        List<? extends EffectNode> vbEffectNodes = mVirtualBackgroundSection.effectNodes;
        if (vbEffectNodes == null) {
            String json = mEffectConfig.getConfig(SP_KEY_VIRTUAL_BACKGROUND_LIST);

            if (TextUtils.isEmpty(json)) {
                vbEffectNodes = createVirtualBackgroundList();
            } else {
                try {
                    vbEffectNodes = GsonUtils.gson().fromJson(json, new TypeToken<List<VirtualBackgroundEffectNode>>() {
                    }.getType());
                } catch (Exception e) {
                    Log.e(TAG, "getVirtualBackgroundSection() exception : " + json);
                    vbEffectNodes = createVirtualBackgroundList();
                }
            }
            mVirtualBackgroundSection.effectNodes = vbEffectNodes;
        }
        return mVirtualBackgroundSection;
    }

    public void save() {
        mEffectConfig.setConfig(SP_KEY_BEAUTY_LIST, mBeautySection.effectNodes);
        mEffectConfig.setConfig(SP_KEY_FILTER_LIST, mFilterSection.effectNodes);
        mEffectConfig.setConfig(SP_KEY_STICKER_LIST, mStickerSection.effectNodes);
        mEffectConfig.setConfig(SP_KEY_VIRTUAL_BACKGROUND_LIST, mVirtualBackgroundSection.effectNodes);
    }

    public void clear() {
        mEffectConfig.setConfig(SP_KEY_BEAUTY_LIST, null);
        mEffectConfig.setConfig(SP_KEY_FILTER_LIST, null);
        mEffectConfig.setConfig(SP_KEY_STICKER_LIST, null);
        mEffectConfig.setConfig(SP_KEY_VIRTUAL_BACKGROUND_LIST, null);
    }

    private static List<EffectNode> createBeautyList() {
        BeautyEffectNode node0 = new BeautyEffectNode("美白", "whiten", "beauty");
        BeautyEffectNode node1 = new BeautyEffectNode("磨皮", "smooth", "beauty");
        BeautyEffectNode node2 = new BeautyEffectNode("大眼", "Internal_Deform_Eye", "reshape");
        BeautyEffectNode node3 = new BeautyEffectNode("瘦脸", "Internal_Deform_Overall", "reshape");
        return Arrays.asList(node0, node1, node2, node3);
    }

    private static List<EffectNode> createStickerList() {
        StickerEffectNode node0 = new StickerEffectNode("黑猫眼镜", "heimaoyanjing");
        StickerEffectNode node1 = new StickerEffectNode("招财猫", "zhaocaimao");
        StickerEffectNode node2 = new StickerEffectNode("缺爱熊", "kejiganqueaixiong");
        StickerEffectNode node3 = new StickerEffectNode("魔法宝石", "mofabaoshi");
        StickerEffectNode node4 = new StickerEffectNode("龙卷风", "aidelongjuanfeng");
        StickerEffectNode node5 = new StickerEffectNode("美猴王", "meihouwang");
        StickerEffectNode node6 = new StickerEffectNode("漫画脸", "manhualian");
        StickerEffectNode node7 = new StickerEffectNode("猪可爱", "keaizhu");
        return Arrays.asList(node0, node1, node2, node3, node4, node5, node6, node7);
    }

    private static List<EffectNode> createFilterList() {
        FilterEffectNode node0 = new FilterEffectNode("蜜桃", "Filter_06_03");
        FilterEffectNode node1 = new FilterEffectNode("清透", "Filter_37_L5");
        FilterEffectNode node2 = new FilterEffectNode("夜色", "Filter_35_L3");
        FilterEffectNode node3 = new FilterEffectNode("冷氧", "Filter_30_Po8");
        return Arrays.asList(node0, node1, node2, node3);
    }

    private static List<EffectNode> createVirtualBackgroundList() {
        VirtualBackgroundEffectNode node0 = new VirtualBackgroundEffectNode("纯色", "color");
        VirtualBackgroundEffectNode node1 = new VirtualBackgroundEffectNode("图片", "image");
        return Arrays.asList(node0, node1);
    }
}
