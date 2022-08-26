package com.ss.video.rtc.demo.advanced.effects.dialog;

import android.content.Context;
import android.os.Bundle;
import android.text.TextUtils;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.view.Window;
import android.view.WindowManager;
import android.widget.FrameLayout;

import androidx.annotation.NonNull;

import com.google.android.material.bottomsheet.BottomSheetDialog;
import com.google.android.material.tabs.TabLayout;
import com.ss.rtc.demo.advanced.R;
import com.ss.video.rtc.demo.advanced.effects.EffectNodeCallback;
import com.ss.video.rtc.demo.advanced.effects.model.EffectSection;
import com.ss.video.rtc.demo.advanced.effects.model.EffectNode;
import com.ss.video.rtc.demo.advanced.effects.model.StickerEffectNode;
import com.ss.video.rtc.demo.advanced.effects.model.VirtualBackgroundEffectNode;
import com.ss.video.rtc.demo.advanced.effects.view.EffectLayout;

import java.util.List;

/**
 * 美颜对话框
 * 展示 mBeautySections 对应的UI，当美颜效果点击或者美颜强度发生变化时，通过 mEffectNodeCallback 将事件回调出去
 */
public class VideoEffectDialog extends BottomSheetDialog {

    private final List<EffectSection> mBeautySections;
    private final EffectNodeCallback mEffectNodeCallback;

    private FrameLayout mBeautyLayoutContainer;

    public VideoEffectDialog(@NonNull Context context, List<EffectSection> beautySections,
                             EffectNodeCallback effectNodeCallback) {
        super(context);
        mBeautySections = beautySections;
        mEffectNodeCallback = effectNodeCallback;
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.dialog_video_effect);
        initWindow();
        initUI();
    }

    private void setTabViewVisibility(TabLayout.Tab tab, boolean visible) {
        String tabTitle = tab.getText() == null ? "" : tab.getText().toString();
        for (int i = 0; i < mBeautyLayoutContainer.getChildCount(); i++) {
            View view = mBeautyLayoutContainer.getChildAt(i);
            String tag = view.getTag().toString();
            view.setVisibility(TextUtils.equals(tabTitle, tag) && visible ? View.VISIBLE : View.GONE);
        }
    }

    private void initUI() {
        TabLayout tabLayout = findViewById(R.id.tab_layout);
        if (tabLayout == null) {
            return;
        }
        mBeautyLayoutContainer = findViewById(R.id.effect_beauty_layout_container);
        if (mBeautySections != null) {
            for (EffectSection section : mBeautySections) {
                tabLayout.addTab(tabLayout.newTab().setText(section.title));

                EffectLayout effectLayout = new EffectLayout(getContext());
                effectLayout.setTag(section.title);
                effectLayout.setEffectSection(section, mEffectNodeCallback);
                effectLayout.setSupportUnSelected(isSupportUnSelected(section));
                FrameLayout.LayoutParams layoutParams = new FrameLayout.LayoutParams(
                        ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT);
                mBeautyLayoutContainer.addView(effectLayout, layoutParams);
                effectLayout.setVisibility(View.GONE);
            }
        }

        tabLayout.addOnTabSelectedListener(new TabLayout.OnTabSelectedListener() {
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

        View view = mBeautyLayoutContainer.getChildAt(0);
        if (view != null) {
            view.setVisibility(View.VISIBLE);
        }
    }

    private void initWindow() {
        Window window = getWindow();
        window.setBackgroundDrawableResource(android.R.color.transparent);
        window.setLayout(WindowManager.LayoutParams.MATCH_PARENT, WindowManager.LayoutParams.WRAP_CONTENT);
        window.setGravity(Gravity.BOTTOM);
        window.setDimAmount(0);
    }

    private boolean isSupportUnSelected(EffectSection section) {
        if (section == null) {
            return false;
        }
        if (section.effectNodes == null || section.effectNodes.isEmpty()) {
            return false;
        }
        for (EffectNode effectNode : section.effectNodes) {
            if (effectNode != null) {
                return effectNode instanceof StickerEffectNode
                        || effectNode instanceof VirtualBackgroundEffectNode;
            }
        }
        return false;
    }
}
