/*
 * Copyright 2020 @bytedance
 *
 *  Created on: Dec 16, 2021
 */
#pragma once

#include <stdint.h>

namespace bytertc {
/**  
 * @type keytype
 * @brief 相机补光灯状态
 */
enum TorchState{

    /**  
     * @brief 相机补光灯关闭
     */
    kTorchStateOff=0,
    /**  
     * @brief 相机补光灯打开
     */
    kTorchStateOn=1,
};

/**  
 * @hidden(macOS, Windows)
 * @type api
 * @region 视频管理
 * @brief 相机控制接口
 * @notes 必须已调用 StartVideoCapture{@link #IRtcEngineLite#StartVideoCapture} 使用 SDK 内部采集模块进行视频采集时，才能使用这个接口。
 */
class ICameraControl {
public:
    /**  
     * @hidden(macOS, Windows)
     * @type api
     * @region 视频管理
     * @brief 设置当前使用的摄像头（前置/后置）的变焦倍数
     * @param zoom_val 变焦倍数。取值范围是 [1, <最大变焦倍数>]。<br>
     *                 最大变焦倍数可以通过调用 GetCameraZoomMaxRatio{@link #GetCameraZoomMaxRatio} 获取。
     * @return  <br>
     *        + 0： 成功。 <br>
     *        + < 0： 失败。
     * @notes <br>
     *        + 必须已调用 StartVideoCapture{@link #IRtcEngineLite#StartVideoCapture} 使用 SDK 内部采集模块进行视频采集时，才能设置摄像头变焦倍数。<br>
     *        + 设置结果在调用 StopVideoCapture{@link #IRtcEngineLite#StopVideoCapture} 关闭内部采集后失效。
     */
    virtual int SetCameraZoomRatio(float zoom_val) = 0;

    /**  
     * @hidden(macOS, Windows)
     * @type api
     * @region 视频管理
     * @brief 获取当前使用的摄像头（前置/后置）的最大变焦倍数
     * @return 最大变焦倍数
     * @notes 必须已调用 StartVideoCapture{@link #IRtcEngineLite#StartVideoCapture} 使用 SDK 内部采集模块进行视频采集时，才能检测摄像头最大变焦倍数。
     */
    virtual float GetCameraZoomMaxRatio() = 0;

    /**  
     * @hidden(macOS, Windows)
     * @type api
     * @region 视频管理
     * @brief 检测当前使用的摄像头（前置/后置），是否支持变焦（数码/光学变焦）。
     * @return  <br>
     *        + true: 支持 <br>
     *        + false: 不支持
     * @notes 必须已调用 StartVideoCapture{@link #IRtcEngineLite#StartVideoCapture} 使用 SDK 内部采集模块进行视频采集时，才能检测摄像头变焦能力。
     */
    virtual bool IsCameraZoomSupported() = 0;

    /**  
     * @hidden(macOS, Windows)
     * @type api
     * @region 视频管理
     * @brief 检测当前使用的摄像头（前置/后置），是否支持闪光灯。
     * @return  <br>
     *        + true: 支持 <br>
     *        + false: 不支持
     * @notes 必须已调用 StartVideoCapture{@link #IRtcEngineLite#StartVideoCapture} 使用 SDK 内部采集模块进行视频采集时，才能检测闪光能力。
     */
    virtual bool IsCameraTorchSupported() = 0;

    /**  
     * @hidden(macOS, Windows)
     * @type api
     * @region 视频管理
     * @brief 打开/关闭当前使用的摄像头（前置/后置）的闪光灯
     * @param torch_state 打开/关闭。参看 TorchState{@link #TorchState}。
     * @return  <br>
     *        + 0： 成功。
     *        + < 0： 失败。
     * @notes <br>
     *        + 必须已调用 StartVideoCapture{@link #IRtcEngineLite#StartVideoCapture} 使用 SDK 内部采集模块进行视频采集时，才能设置闪光灯。<br>
     *        + 设置结果在调用 StopVideoCapture{@link #IRtcEngineLite#StopVideoCapture} 关闭内部采集后失效。
     */
    virtual int SetCameraTorch(TorchState torch_state) = 0;

    /** 
     * @hidden(macOS, Windows)
     * @type api
     * @region 视频管理
     * @brief 检查当前使用的摄像头是否支持对焦点设置
     * @return  <br>
     *        + true： 支持。
     *        + false： 不支持。
     * @notes <br>
     *        + 必须已调用 StartVideoCapture{@link #IRtcEngineLite#StartVideoCapture} 使用 SDK 内部采集模块进行视频采集时，才能检查对焦点设置能力。<br>
     */
    virtual bool IsCameraFocusPositionSupported() = 0;
    
    /** 
     * @hidden(macOS, Windows)
     * @type api
     * @region 视频管理
     * @brief 设置当前使用的摄像头的对焦点
     * @param x 对焦点水平方向归一化坐标。以本地预览画布的左上为原点。取值范围为[0, 1]，0为最左边，1为最右边。
     * @param y 对焦点垂直方向归一化坐标。以本地预览画布的左上为原点。取值范围为[0, 1]，0为最上边，1为最下边。
     * @return  <br>
     *        + 0： 成功。
     *        + < 0： 失败。
     * @notes <br>
     *        + 必须已调用 StartVideoCapture{@link #IRtcEngineLite#StartVideoCapture} 使用 SDK 内部采集模块进行视频采集，并且使用SDK内部渲染时，才能设置对焦点。<br>
     *        + 对焦点设置为画布中央(即[0.5， 0.5]) 时，恢复系统默认值。
     *        + 设置结果在调用 StopVideoCapture{@link #IRtcEngineLite#StopVideoCapture} 关闭内部采集后失效。
     */
    virtual int SetCameraFocusPosition(float x, float y) = 0;
    
    /** 
     * @hidden(macOS, Windows)
     * @type api
     * @region 视频管理
     * @brief 检查当前使用的摄像头是否支持曝光点设置
     * @return  <br>
     *        + true： 支持。
     *        + false： 不支持。
     * @notes <br>
     *        + 必须已调用 StartVideoCapture{@link #IRtcEngineLite#StartVideoCapture} 使用 SDK 内部采集模块进行视频采集时，才能检查曝光点设置能力。<br>
     */
    virtual bool IsCameraExposurePositionSupported() = 0;
    
    /** 
     * @hidden(macOS, Windows)
     * @type api
     * @region 视频管理
     * @brief 设置当前使用的摄像头的曝光点
     * @param x 曝光点水平方向归一化坐标。以本地预览画布的左上为原点。取值范围为[0, 1]，0为最左边，1为最右边。
     * @param y 曝光点垂直方向归一化坐标。以本地预览画布的左上为原点。取值范围为[0, 1]，0为最上边，1为最下边。
     * @return  <br>
     *        + 0： 成功。
     *        + < 0： 失败。
     * @notes <br>
     *        + 必须已调用 StartVideoCapture{@link #IRtcEngineLite#StartVideoCapture} 使用 SDK 内部采集模块进行视频采集，并且使用SDK内部渲染时，才能设置曝光点。<br>
     *        + 曝光点设置为画布中央(即[0.5， 0.5]) 时，恢复系统默认值。
     *        + 设置结果在调用 StopVideoCapture{@link #IRtcEngineLite#StopVideoCapture} 关闭内部采集后失效。
     */
    virtual int SetCameraExposurePosition(float x, float y) = 0;
    
    /** 
     * @hidden(macOS, Windows)
     * @type api
     * @region 视频管理
     * @brief 设置当前使用的摄像头的曝光补偿
     * @param val 曝光补偿值，取值范围[-1, 1]，0为系统默认值(没有曝光补偿)。
     * @return  <br>
     *        + 0： 成功。
     *        + < 0： 失败。
     * @notes <br>
     *        + 必须已调用 StartVideoCapture{@link #IRtcEngineLite#StartVideoCapture} 使用 SDK 内部采集模块进行视频采集时，才能设置曝光补偿。<br>
     *        + 设置结果在调用 StopVideoCapture{@link #IRtcEngineLite#StopVideoCapture} 关闭内部采集后失效。
     */
    virtual int SetCameraExposureCompensation(float val) = 0;
};

}  // namespace bytertc
