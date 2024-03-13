//
// Created by shenpengliang on 2021/8/23.
//

#pragma once

namespace bytertc {
/**
 * @locale zh
 * @hidden(Windows,Linux,macOS)
 * @type callback
 * @brief 语音识别服务使用状态回调<br>
 * 注意：回调函数是在 SDK 内部线程（非 UI 线程）同步抛出来的，请不要做耗时操作或直接操作 UI，否则可能导致 app 崩溃。
 */
/**
 * @locale en
 * @hidden(Windows,Linux,macOS)
 * @type callback
 * @brief Speech recognition service usage status callback<br>
 * Note: Callback functions are thrown synchronously in a non-UI thread within the SDK. Therefore, you must not perform any time-consuming operations or direct UI operations within the callback function, as this may cause the app to crash.
 */
class IRTCASREngineEventHandler {
public:
    /**
     * @locale zh
     * @hidden constructor/destructor
     * @brief 析构函数
     */
    /**
     * @locale en
     * @hidden constructor/destructor
     * @brief Destructor
     */
    virtual ~IRTCASREngineEventHandler() {
    }
    /**
     * @locale zh
     * @type callback
     * @brief 语音识别服务开启成功回调
     */
    /**
     * @locale en
     * @type callback
     * @brief  Speech recognition service starts successful callback
     */
    virtual void onSuccess() = 0;
    /**
     * @locale zh
     * @type callback
     * @brief 语音转文字成功回调，该回调返回识别后的全量消息。
     * @param message 识别完成后得到的文字消息
     * @note 若识别过程中发生了网络连接中断，则重连后回调的信息中只包含重连后识别的文字消息，不再包含上一次连接后识别的消息。
     */
    /**
     * @locale en
     * @type callback
     * @brief Callback of successful voice to text conversion. All the recognized text is returned through this callback.
     * @param message Text message obtained after the completion of the recognition
     * @note If the network connection is interrupted during the recognition process, the callback after the reconnection carries only the text message recognized after the reconnection.
     */
    virtual void onMessage(const char* message) = 0;
    /**
     * @locale zh
     * @type callback
     * @brief 当语音识别服务内部发生错误事件时触发该回调。
     * @param error_code 错误码  <br>
     *        + < 0: 参数错误或 API 调用顺序错误，参看 RTCASRErrorCode{@link #RTCASRErrorCode}；  <br>
     *        + >0: 参看 [语音识别服务错误码](https://www.volcengine.com/docs/6561/80818#_3-3-%E9%94%99%E8%AF%AF%E7%A0%81)  
     * @param error_message 错误原因说明
     */
    /**
     * @locale en
     * @type callback
     * @brief This callback is triggered when an error event occurs within the speech recognition service.
     * @param error_code Error code <br>
     *         + < 0: parameter error or API call order error. See RTCASRErrorCode{@link #RTCASRErrorCode}; <br>
     *         + > 0: see [speech recognition service error code](https://docs.byteplus.com/en/speech/docs/real-time-speech-recog#bbbf89f6)  
     * @param error_message Detailed error message
     */
    virtual void onError(int error_code, const char* error_message) = 0;
};
}  // namespace bytertc
