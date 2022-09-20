//
//  bytertc_transcoder_base_interface.h
//  ByteRTC
//
#pragma once

namespace bytertc {
/** 
 * @hidden
 * @type keytype
 * @brief 合流房间状态
 */
enum TranscoderRoomStatus {
    /**
     * @brief join room status
     */
    kRoomStatusJoinRoom,
    /**
     * @brief leave room status
     */
    kRoomStatusLeaveRoom,
    /**
     * @brief room status was offline
     */
    kRoomStatusOffline,
    /**
     * @brief room status was online
     */
    kRoomStatusOnline,
};

/** 
 * @type keytype
 * @brief 合流输出内容类型
 */
enum TranscoderContentControlType {
    /** 
     * @brief 输出的混流包含音频和视频
     */
    kHasAudioAndVideo = 0,
    /** 
     * @brief 输出的混流只包含音频
     */
    kHasAudioOnly = 1,
    /** 
     * @brief 输出的混流只包含视频
     */
    kHasVideoOnly = 2,
};
/** 
 * @type keytype
 * @brief 合流转码参数
 */
class ITranscoderParamBase {
public:
    /** 
     * @type api
     * @region 转码
     * @brief 获取合流房间 ID
     * @return 合流房间 ID
     */
    virtual const char* roomID() = 0;
    /** 
     * @hidden
     * @type api
     * @region 转推直播
     * @brief 获取 other 数据
     * @return Other数据
     */
    virtual const char* other() = 0;
    /** 
     * @type api
     * @region 转推直播
     * @brief 获取通过 flatten{@link #ITranscoderParamBase#flatten} 方法转换得到的 json 格式内容
     * @return json 格式数据
     */
    virtual const char* jsonContent() = 0;
    /** 
     * @type api
     * @region 转推直播
     * @brief 获取合流参数中视窗的数量
     * @return 合流参数中视窗的数量
     */
    virtual int32_t layoutRegionsSize() = 0;
    /** 
     * @type api
     * @region 转推直播
     * @brief 获取背景颜色
     * @return 背景颜色
     */
    virtual const char* backgroundColor() = 0;
    /** 
     * @type api
     * @region 转推直播
     * @brief 设置合流房间 ID
     * @param [in] room_id 发起合流的用户所在的房间 ID
     */
    virtual void setRoomID(const char* room_id) = 0;
    /** 
     * @type api
     * @region 转推直播
     * @brief 设置 jsonContent  <br>
     *        传入通过 flatten{@link #ITranscoderParamBase#flatten} 方法转换得到的 json 格式内容
     * @param [in] json_content json 格式内容
     */
    virtual void setJsonContent(const char* json_content) = 0;
    /** 
     * @hidden
     * @type api
     * @region 转推直播
     * @brief 设置 other 数据
     * @param [in] other other 数据
     */
    virtual void setOther(const char* other) = 0;
    /** 
     * @type api
     * @region 转推直播
     * @brief 将合流参数转成 json 字符串
     * @param [in] contentType 内容属性，表明是合流信令
     * @param [in] action 合流状态，可选取值如下：  <br>
     *               + started: 开启合流  <br>
     *               + layoutChanged: 更新合流布局  <br>
     *               + stopped: 停止合流
     * @return 转换后的 json 字符串
     */
    virtual const char* flatten(const char* contentType, const char* action) = 0;
    /**
     * @hidden
     */
    ~ITranscoderParamBase() = default;
};
}/*namespace bytertc*/
