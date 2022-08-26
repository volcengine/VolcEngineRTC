package com.ss.video.rtc.demo.advanced.effects.model;

import java.util.List;

/**
 * 美颜功能集合
 */
public class EffectSection {
    public boolean hasProgress; // 是否有强度
    public String title; // 美颜功能集合名称
    public List<? extends EffectNode> effectNodes; // 包含的具体美颜功能

    public EffectSection(String title, boolean hasProgress, List<? extends EffectNode> effectNodes) {
        this.title = title;
        this.hasProgress = hasProgress;
        this.effectNodes = effectNodes;
    }
}
