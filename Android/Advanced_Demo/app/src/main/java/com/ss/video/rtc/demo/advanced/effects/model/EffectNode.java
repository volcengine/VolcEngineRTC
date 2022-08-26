package com.ss.video.rtc.demo.advanced.effects.model;

public class EffectNode {

    public String name; // UI上展示的名称
    public String key; // 素材的键值，区分具体美颜效果、美形效果、滤镜、贴纸

    public float value; // 美颜、美形、滤镜的强度
    public boolean selected; // 是否选中

    public EffectNode(String name, String key) {
        this.name = name;
        this.key = key;
    }

    @Override
    public String toString() {
        return "EffectNode{" +
                "name='" + name + '\'' +
                ", key='" + key + '\'' +
                ", value=" + value +
                ", selected=" + selected +
                '}';
    }
}
