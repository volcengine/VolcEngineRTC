package com.ss.video.rtc.demo.advanced.effects;

import com.ss.video.rtc.demo.advanced.effects.model.EffectNode;

/**
 * 美颜效果发生变化时的回调
 */
public interface EffectNodeCallback {

    /**
     * 当美颜被点击时回调
     * @param effectNode 具体的美颜效果，selected字段标识的是选中还是未选中
     */
    void onEffectClicked(EffectNode effectNode);

    /**
     * 当美颜强度改变时回调
     * @param effectNode 具体的美颜效果，value字段表示强度
     */
    void onEffectValueChanged(EffectNode effectNode);
}
