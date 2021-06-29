// Copyright (C) 2020 Beijing Bytedance Network Technology Co., Ltd.
//
// RTC SDK 视频特效接口
//
#pragma once
#include <stdint.h>

namespace bytertc {

/**
 * @type api
 * @region 视频管理
 * @brief 视频特效接口
 */
class IVideoEffect {
public:
    /**
     * @type api
     * @region 视频管理
     * @brief 检查当前版本是否支持视频特效
     * @return:
     *       0: 不支持
     *       >0: 支持视频特效
     */
    virtual int CheckSupport() = 0;

    /**
     * @type api
     * @region 视频管理
     * @brief 视频特效许可证检查
     * @param androidContext  Android Context对象指针(jobject类型) 。 Android  以外平台传入nullptr
     * @param jnienv Android JNIEnv 指针。 Android  以外平台传入nullptr
     * @param licensePath 许可证文件绝对路径
     * @return
     *      0: 许可证验证成功
     *      !0: 许可证验证验证失败
     * @notes 调用EnableEffect{@link #EnableEffect}开始使用视频特效前，需要先调用这个方法进行许可证验证
     */
    virtual int CheckLicense(void* androidContext, void* jnienv, const char* licensePath) = 0;

    /**
     * @type api
     * @region 视频管理
     * @brief 开启关闭视频特效
     * @param enabled 是否开启特效，true: 开启，false: 关闭
     * @return
     *      0: 成功
     *      !0: 失败。
     * @notes 在调用CheckLicense{@link #CheckLicense}和SetAlgoModelPath{@link #SetAlgoModelPath}后调用此方法
     */
    virtual int EnableEffect(bool enabled) = 0;

    /**
     * @type api
     * @region 视频管理
     * @brief 设置视频特效算法模型路径
     * @param modelPath 模型路径
     */
    virtual void SetAlgoModelPath(const char* modelPath) = 0;

    /**
     * @type api
     * @region 视频管理
     * @brief 设置特效包，支持同时设置多个特效包
     * @param effectPackPaths 特效包路径数组
     * @param nodeNum 特效包个数
     */
    virtual void SetEffectNodes(const char** effectNodePaths, int nodeNum) = 0;

    /**
     * @type api
     * @region 视频管理
     * @brief 增加特效包，支持同时增加多个特效包
     * @param effectNodePaths 要追加的特效包路径数组
     * @param nodeNum 特效包个数
     */
    virtual void AddEffectNodes(const char** effectNodePaths, int nodeNum) = 0;

    /**
     * @type api
     * @region 视频管理
     * @brief 移除特效包，支持同时移除多个特效包
     * @param effectNodePaths  要移除的特效包路径数组
     * @param nodeNum  特效包个数
     */
    virtual void RemoveEffectNodes(const char** effectNodePaths, int nodeNum) = 0;

    /**
     * @type api
     * @region 视频管理
     * @brief 设置特效强度
     * @param nodePath  特效包路径
     * @param nodeKey  需要设置的键名称
     * @param nodeValue  要设置的强度值。取值范围[0,1] ，超出范围时设置无效
     * @notes nodeKey 的取值请参考特效包的参数说明文件
     */
    virtual void UpdateNode(const char* nodePath, const char* nodeKey, float nodeValue) = 0;

    /**
     * @type api
     * @region  视频管理
     * @brief     设置颜色滤镜
     * @param  resPath  滤镜资源包绝对路径
     */
    virtual void SetColorFilter(const char* resPath) = 0;

    /**
     * @type api
     * @region 视频管理
     * @brief 设置颜色滤镜强度
     * @param intensity  滤镜强度。取值范围[0,1] ，超出范围时设置无效
     */
    virtual void SetColorFilterIntensity(float intensity) = 0;
};

}  // namespace bytertc
