//
// Created by shenpengliang on 2021/8/23.
//

#pragma once

namespace bytertc {
/**
 * @type keytype
 * @brief 语音识别服务使用状态回调
 */
class IRTCASREngineEventHandler {
public:
    /**
     * @hidden
     * @brief 析构函数
     */
    virtual ~IRTCASREngineEventHandler() {
    }
    /**
     * @type callback
     * @brief 语音识别服务开启成功回调
     */
    virtual void OnSuccess() = 0;
    /**
     * @type callback
     * @brief 语音转文字成功回调，该回调返回识别后的全量消息。
     * @param [in] message 识别完成后得到的文字消息
     * @notes 若识别过程中发生了网络连接中断，则重连后回调的信息中只包含重连后识别的文字消息，不再包含上一次连接后识别的消息。
     */
    virtual void OnMessage(const char* message) = 0;
    /**
     * @type callback
     * @brief 当语音识别服务内部发生错误事件时触发该回调。
     * @param [in] error_code 错误码  <br>
     *        + <0: 参数错误或 API 调用顺序错误，参看 RTCASRErrorCode{@link #RTCASRErrorCode}；  <br> 
     *        + >0: 参看 [语音识别服务错误码](https://bytedance.feishu.cn/docs/doccnMx9153dZEpfLX2I6BkFsMg#VPknqs)  
     * @param [in] error_message 错误原因说明
     */
    virtual void OnError(int error_code, const char* error_message) = 0;
};
}  // namespace bytertc
