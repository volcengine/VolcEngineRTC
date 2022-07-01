package com.ss.video.rtc.demo.advanced.effects;

import android.app.Dialog;
import android.content.Context;
import android.graphics.Color;
import android.os.Bundle;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.view.Window;
import android.view.WindowManager;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.SeekBar;

import androidx.annotation.NonNull;

import com.google.android.material.tabs.TabLayout;
import com.ss.bytertc.engine.RTCEngine;
import com.ss.bytertc.engine.data.VirtualBackgroundSource;
import com.ss.bytertc.engine.data.VirtualBackgroundSourceType;
import com.ss.rtc.demo.advanced.R;
import com.ss.video.rtc.demo.advanced.utils.CVUtils;

import java.io.File;
import java.util.ArrayList;
import java.util.HashMap;

public class CVDialog extends Dialog implements SeekBar.OnSeekBarChangeListener{

    private final RTCEngine mEngine;
    private final Context mContext;
    private final String mExternalResourcePath;
    private Window mWindow = null;
    private RadioButton mSelectedStickerBtn;

    private ViewGroup mBeautyLayout;
    private ViewGroup mStickerLayout;
    private ViewGroup mFilterLayout;
    private ViewGroup mBackgroundLayout;
    private SeekBar mBeautySeekbar;
    private RadioGroup mBeautyRadioGroup;
    private RadioGroup mStickerRadioGroupRow_first;
    private RadioGroup mStickerRadioGroupRow_second;
    private SeekBar mFilterSeekbar;
    private RadioGroup mFilterRadioGroup;
    private RadioGroup mBackgroundRadioGroup;


    private final HashMap<Integer, Integer> mSeekBarProgressMap = new HashMap<>();
    private final ArrayList<String> mEffectPathList = new ArrayList<>();


    public CVDialog(@NonNull Context context, RTCEngine engine) {
        super(context);
        mEngine = engine;
        mContext = context;
        mExternalResourcePath = mContext.getExternalFilesDir("assets").getAbsolutePath();
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.dialog_video_effect);
        initWindow();
        initUI();
        mEffectPathList.addAll(VideoEffectController.getInstance().getVideoEffectCompose());
//        mEngine.setVideoEffectNodes(mEffectPathList);
        VideoEffectController.getInstance().setVideoEffectNodes(mEffectPathList);
    }

    private void setTabViewVisibility(TabLayout.Tab tab, boolean visible) {
        switch (tab.getText().toString()) {
            case "美颜" :
                mBeautyLayout.setVisibility(visible ? View.VISIBLE : View.GONE);
                break;
            case "贴纸" :
                mStickerLayout.setVisibility(visible ? View.VISIBLE : View.GONE);
                break;
            case "滤镜" :
                mFilterLayout.setVisibility(visible ? View.VISIBLE : View.GONE);
                break;
            case "背景分割" :
                mBackgroundLayout.setVisibility(visible ? View.VISIBLE : View.GONE);
                break;
        }
    }

    private void initWindow() {
        Window window = getWindow();
        window.setBackgroundDrawableResource(android.R.color.transparent);
        window.setLayout(WindowManager.LayoutParams.MATCH_PARENT,WindowManager.LayoutParams.WRAP_CONTENT);
        window.setGravity(Gravity.BOTTOM);
        window.setDimAmount(0);
    }

    private void initUI() {
        mBeautyLayout = findViewById(R.id.beauty_layout);
        mStickerLayout = findViewById(R.id.sticker_layout);
        mFilterLayout = findViewById(R.id.filter_layout);
        mBackgroundLayout = findViewById(R.id.background_layout);
        TabLayout mTabLayout = findViewById(R.id.tab_layout);
        mTabLayout.addTab(mTabLayout.newTab().setText("美颜"));
        mTabLayout.addTab(mTabLayout.newTab().setText("贴纸"));
        mTabLayout.addTab(mTabLayout.newTab().setText("滤镜"));
        mTabLayout.addTab(mTabLayout.newTab().setText("背景分割"));
        mTabLayout.addOnTabSelectedListener(new TabLayout.OnTabSelectedListener() {
            @Override
            public void onTabSelected(TabLayout.Tab tab) {
                setTabViewVisibility(tab, true);
            }

            @Override
            public void onTabUnselected(TabLayout.Tab tab) {
                setTabViewVisibility(tab, false);
            }

            @Override
            public void onTabReselected(TabLayout.Tab tab) {

            }
        });

        // beauty
        mBeautySeekbar = findViewById(R.id.beauty_degree_seekbar);
        mBeautySeekbar.setOnSeekBarChangeListener(this);
        mBeautyRadioGroup = findViewById(R.id.beauty_radio_group);
        mBeautyRadioGroup.setOnCheckedChangeListener(new RadioGroup.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(RadioGroup group, int checkedId) {
                if (mSeekBarProgressMap.containsKey(checkedId)) {
                    mBeautySeekbar.setProgress(mSeekBarProgressMap.get(checkedId));
                } else {
                    mBeautySeekbar.setProgress(0);
                }
            }
        });

        mStickerRadioGroupRow_first = findViewById(R.id.sticker_radio_group_row1);
        mStickerRadioGroupRow_second = findViewById(R.id.sticker_radio_group_row2);
        mStickerRadioGroupRow_first.setOnCheckedChangeListener(stickerChangeListener);
        mStickerRadioGroupRow_second.setOnCheckedChangeListener(stickerChangeListener);


        for (int i = 0; i < mStickerRadioGroupRow_first.getChildCount(); i++) {
            mStickerRadioGroupRow_first.getChildAt(i).setOnClickListener(stickerButtonClickListener);
            mStickerRadioGroupRow_second.getChildAt(i).setOnClickListener(stickerButtonClickListener);
        }

        mFilterSeekbar = findViewById(R.id.video_filter_seekbar);
        mFilterSeekbar.setOnSeekBarChangeListener(this);
        mFilterRadioGroup = findViewById(R.id.filter_radio_group);
        mFilterRadioGroup.setOnCheckedChangeListener(new RadioGroup.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(RadioGroup group, int checkedId) {
                if (checkedId == R.id.btn_filter_mitao) {
                    VideoEffectController.getInstance().setVideoEffectColorFilter("Filter_06_03");
                } else if (checkedId == R.id.btn_filter_qingtou) {
                    VideoEffectController.getInstance().setVideoEffectColorFilter("Filter_37_L5");
                } else if (checkedId == R.id.btn_filter_yese) {
                    VideoEffectController.getInstance().setVideoEffectColorFilter("Filter_35_L3");
                } else if (checkedId == R.id.btn_filter_lengyang) {
                    VideoEffectController.getInstance().setVideoEffectColorFilter("Filter_30_Po8");
                }
                mFilterSeekbar.setProgress(0);
                VideoEffectController.getInstance().setVideoEffectColorFilterIntensity(0);
            }
        });
        VideoEffectController.getInstance().setVideoEffectColorFilter("Filter_06_03");//default mitao
        VideoEffectController.getInstance().setVideoEffectColorFilterIntensity(0);

        mBackgroundRadioGroup = findViewById(R.id.background_radio_group);
        mBackgroundRadioGroup.setOnCheckedChangeListener((RadioGroup group, int checkedId) -> {
            if (checkedId == R.id.btn_color_background) {
                VirtualBackgroundSource backgroundSource = new VirtualBackgroundSource();
                backgroundSource.sourceType = VirtualBackgroundSourceType.SourceTypeColor;
                backgroundSource.sourceColor = Color.parseColor("#1278ff");
                mEngine.enableVirtualBackground(backgroundSource);
            } else if (checkedId == R.id.btn_pic_background) {
                VirtualBackgroundSource backgroundSource = new VirtualBackgroundSource();
                backgroundSource.sourceType = VirtualBackgroundSourceType.SourceTypeImage;
                backgroundSource.sourcePath = CVUtils.getExternalResourcePath() + File.separator + "virtual_background.png";
                mEngine.enableVirtualBackground(backgroundSource);
            } else {
                mEngine.disableVirtualBackground();
            }
        });
    }

    RadioGroup.OnCheckedChangeListener stickerChangeListener = new RadioGroup.OnCheckedChangeListener() {
        @Override
        public void onCheckedChanged(RadioGroup group, int checkedId) {
            if (checkedId == -1) {
                return;
            }
            if (!((RadioButton) group.findViewById(checkedId)).isChecked()) {
                return;
            }
            ArrayList<String> pathList = null;
            String sticker = "";
            switch (checkedId) {
                case R.id.btn_black_cat:
                    pathList = new ArrayList<>();
                    pathList.addAll(mEffectPathList);
                    sticker = getByteStickerPath() + "heimaoyanjing";
                    pathList.add(sticker);
                    break;
                case R.id.btn_zhaocao_cat:
                    pathList = new ArrayList<>();
                    pathList.addAll(mEffectPathList);
                    sticker = getByteStickerPath() + "zhaocaimao";
                    pathList.add(sticker);
                    break;
                case R.id.btn_queai_bear:
                    pathList = new ArrayList<>();
                    pathList.addAll(mEffectPathList);
                    sticker = getByteStickerPath() + "kejiganqueaixiong";
                    pathList.add(sticker);
                    break;
                case R.id.btn_magic_stone:
                    pathList = new ArrayList<>();
                    pathList.addAll(mEffectPathList);
                    sticker = getByteStickerPath() + "mofabaoshi";
                    pathList.add(sticker);
                    break;
                case R.id.btn_longjuanfeng:
                    pathList = new ArrayList<>();
                    pathList.addAll(mEffectPathList);
                    sticker = getByteStickerPath() + "aidelongjuanfeng";
                    pathList.add(sticker);
                    break;
                case R.id.btn_meihouwang:
                    pathList = new ArrayList<>();
                    pathList.addAll(mEffectPathList);
                    sticker = getByteStickerPath() + "meihouwang";
                    pathList.add(sticker);
                    break;
                case R.id.btn_manhualian:
                    pathList = new ArrayList<>();
                    pathList.addAll(mEffectPathList);
                    sticker = getByteStickerPath() + "manhualian";
                    pathList.add(sticker);
                    break;
                case R.id.btn_keaizhu:
                    pathList = new ArrayList<>();
                    pathList.addAll(mEffectPathList);
                    sticker = getByteStickerPath() + "keaizhu";
                    pathList.add(sticker);
                    break;
                default:
                    pathList = new ArrayList<>();
            }
            if (checkedId != -1) {
//                mEngine.setVideoEffectNodes(pathList);

                VideoEffectController.getInstance().setSticker(sticker, pathList);
                if (group == mStickerRadioGroupRow_first) {
                    mStickerRadioGroupRow_second.clearCheck();
                } else {
                    mStickerRadioGroupRow_first.clearCheck();
                }
            }
        }
    };

    View.OnClickListener stickerButtonClickListener = v -> {
        if (v == mSelectedStickerBtn) {
            ((RadioButton) v).setChecked(false);
            VideoEffectController.getInstance().setVideoEffectNodes(mEffectPathList);
            VideoEffectController.getInstance().setSticker(null, mEffectPathList);
            mSelectedStickerBtn = null;
            return;
        }
        mSelectedStickerBtn = (RadioButton) v;
    };

    @Override
    public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {

    }

    @Override
    public void onStartTrackingTouch(SeekBar seekBar) {

    }

    @Override
    public void onStopTrackingTouch(SeekBar seekBar) {
        float value = seekBar.getProgress() / 100f;
        if (seekBar.getId() == R.id.beauty_degree_seekbar) {
            switch (mBeautyRadioGroup.getCheckedRadioButtonId()) {
                case R.id.btn_face_white:
                    VideoEffectController.getInstance().updateVideoEffectNode(getByteComposePath(), "whiten", value);
                    break;
                case R.id.btn_face_beauty:
                    VideoEffectController.getInstance().updateVideoEffectNode(getByteComposePath(), "smooth", value);
                    break;
                case R.id.btn_big_eyes:
                    VideoEffectController.getInstance().updateVideoEffectNode(getByteShapePath(), "Internal_Deform_Eye", value);
                    break;
                case R.id.btn_face_shape:
                    VideoEffectController.getInstance().updateVideoEffectNode(getByteShapePath(), "Internal_Deform_Overall", value);
                    break;
            }
            mSeekBarProgressMap.put(mBeautyRadioGroup.getCheckedRadioButtonId(), seekBar.getProgress());
        } else if (seekBar.getId() == R.id.video_filter_seekbar) {
            VideoEffectController.getInstance().setVideoEffectColorFilterIntensity(value);
            mSeekBarProgressMap.put(mFilterRadioGroup.getCheckedRadioButtonId(), seekBar.getProgress());
        }
    }

    public String getByteStickerPath() {
        File stickerPath = new File(mExternalResourcePath + "/resource/", "cvlab/StickerResource.bundle");
        return stickerPath.getAbsolutePath()+"/stickers/";
    }

    public String getByteComposePath() {
        File composerPath = new File(mExternalResourcePath + "/resource/", "cvlab/ComposeMakeup.bundle");
        return composerPath.getAbsolutePath()+"/ComposeMakeup/beauty_Android_live";
    }

    public String getByteShapePath() {
        File composerPath = new File(mExternalResourcePath+ "/resource/", "cvlab/ComposeMakeup.bundle");
        return composerPath.getAbsolutePath()+"/ComposeMakeup/reshape_live";
    }

    public String getByteColorFilterPath() {
        File filterPath = new File(mExternalResourcePath + "/resource/", "cvlab/FilterResource.bundle");
        return filterPath.getAbsolutePath() + "/Filter/";
    }
}
