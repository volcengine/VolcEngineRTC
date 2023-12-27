package com.faceunity.nama.repo;

import com.faceunity.nama.R;
import com.faceunity.nama.entity.MakeupCombinationBean;

import java.io.File;
import java.util.ArrayList;

/**
 * DESC：美妆数据构造
 * Created on 2021/3/28
 */
public class MakeupSource {
    public static String BUNDLE_FACE_MAKEUP = "graphics" + File.separator + "face_makeup.bundle";

    //region 组合妆容

    /**
     * 构造美妆组合妆容配置
     *
     * @return ArrayList<MakeupCombinationBean>
     */
    public static ArrayList<MakeupCombinationBean> buildCombinations() {
        ArrayList<MakeupCombinationBean> combinations = new ArrayList<MakeupCombinationBean>();
        combinations.add(new MakeupCombinationBean("origin", R.mipmap.icon_control_none, R.string.makeup_radio_remove, null));
        combinations.add(new MakeupCombinationBean("jianling", R.mipmap.icon_makeup_combination_age, R.string.makeup_combination_jianling, "makeup/jianling.bundle"));
        combinations.add(new MakeupCombinationBean("nuandong", R.mipmap.icon_makeup_combination_warm_winter, R.string.makeup_combination_nuandong, "makeup/nuandong.bundle"));
        combinations.add(new MakeupCombinationBean("hongfeng", R.mipmap.icon_makeup_combination_red_maple, R.string.makeup_combination_hongfeng, "makeup/hongfeng.bundle"));
        combinations.add(new MakeupCombinationBean("rose", R.mipmap.icon_makeup_combination_rose, R.string.makeup_combination_rose, "makeup/rose.bundle"));
        combinations.add(new MakeupCombinationBean("shaonv", R.mipmap.icon_makeup_combination_girl, R.string.makeup_combination_shaonv, "makeup/shaonv.bundle"));
        combinations.add(new MakeupCombinationBean("ziyun", R.mipmap.icon_makeup_combination_purple_rhyme, R.string.makeup_combination_ziyun, "makeup/ziyun.bundle"));
        combinations.add(new MakeupCombinationBean("yanshimao", R.mipmap.icon_makeup_combination_bored_cat, R.string.makeup_combination_yanshimao, "makeup/yanshimao.bundle"));
        combinations.add(new MakeupCombinationBean("renyu", R.mipmap.icon_makeup_combination_mermaid, R.string.makeup_combination_renyu, "makeup/renyu.bundle"));
        combinations.add(new MakeupCombinationBean("chuqiu", R.mipmap.icon_makeup_combination_early_autumn, R.string.makeup_combination_chuqiu, "makeup/chuqiu.bundle"));
        combinations.add(new MakeupCombinationBean("qianzhihe", R.mipmap.icon_makeup_combination_paper_cranes, R.string.makeup_combination_qianzhihe, "makeup/qianzhihe.bundle"));
        combinations.add(new MakeupCombinationBean("chaomo", R.mipmap.icon_makeup_combination_supermodel, R.string.makeup_combination_chaomo, "makeup/chaomo.bundle"));
        combinations.add(new MakeupCombinationBean("chuju", R.mipmap.icon_makeup_combination_daisy, R.string.makeup_combination_chuju, "makeup/chuju.bundle"));
        combinations.add(new MakeupCombinationBean("gangfeng", R.mipmap.icon_makeup_combination_harbour_wind, R.string.makeup_combination_gangfeng, "makeup/gangfeng.bundle"));
        combinations.add(new MakeupCombinationBean("xinggan", R.mipmap.icon_makeup_combination_sexy, R.string.makeup_combination_sexy, "makeup/xinggan.bundle"));
        combinations.add(new MakeupCombinationBean("tianmei", R.mipmap.icon_makeup_combination_sweet, R.string.makeup_combination_sweet, "makeup/tianmei.bundle"));
        combinations.add(new MakeupCombinationBean("linjia", R.mipmap.icon_makeup_combination_neighbor_girl, R.string.makeup_combination_neighbor, "makeup/linjia.bundle"));
        combinations.add(new MakeupCombinationBean("oumei", R.mipmap.icon_makeup_combination_occident, R.string.makeup_combination_occident, "makeup/oumei.bundle"));
        combinations.add(new MakeupCombinationBean("wumei", R.mipmap.icon_makeup_combination_charming, R.string.makeup_combination_charming, "makeup/wumei.bundle"));
        return combinations;
    }

    //endregion 
}
