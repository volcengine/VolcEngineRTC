/*
 *  Copyright (c) 2021 The ByteRtc project authors. All Rights Reserved.
 *  @company ByteDance.Inc
 *  @brief 游戏语音引擎配置信息
 */
#pragma once

namespace bytertc {
/**
 * @type keytype
 * @brief 描述范围语音中语音接收范围
 */
struct ReceiveRange {
    /**
     * @brief 不同小队成员设置收发世界模式并且开启区域语音时，设置收听的最小范围值，在小于 min 的时候，声音完全无衰减;
     */
    int min;
    /**
     *  @brief 不同小队成员设置收发世界模式并且开启区域语音时，设置收听的最大范围值，在大于 max 的时候，声音无法听见
     *         在 [min, max) 之间根据距离远近实现声音的衰减
     */
    int max;
};

/**
 * @type keytype
 * @brief 描述范围语音中语音接受范围的界限, 当没有合理的范围提供时，作为默认的接收范围
 */
enum ReceiveRangeLimit {
    /**
     * @brief 默认最小范围
     */
    defaultMin = 0,
    /**
     * @brief 默认最大范围
     */
    defaultMax = 10000,
};

/**
 * @type keytype
 * @brief 范围语音中用户的位置，坐标系需要自行建立。
 */
struct Position {
    /**
     * @brief x 坐标
     */
    int x;
    /**
     * @brief y 坐标
     */
    int y;
    /**
     * @brief z 坐标
     */
    int z;

    bool isEqual(Position pos){
        return x == pos.x && y == pos.y && z == pos.z;
    }
};

/**
 * @type keytype
 * @brief 坐标
 */
struct Orientation {
    /**
     * @brief x 方向向量
     */
    float x;
    /**
     * @brief y 方向向量
     */
    float y;
    /**
     * @brief z 方向向量
     */
    float z;
};

/**
 * @type keytype
 * @brief 用于确定朝向的正方向基准。默认的正方向和位置坐标系的三个正方向一致。
 * @notes 如果不使用默认值，需保证三个向量两两垂直。
 */
struct HumanOrientation{
    /**
     * @brief 正前方朝向向量
     */
    Orientation forward =  { 1,0,0 };
    /**
     * @brief 正右方朝向向量
     */
    Orientation right = { 0,1,0 };
    /**
     * @brief 正上方朝向向量
     */
    Orientation up = { 0,0,1 };
};

/**
 * @hidden
 * @type keytype
 * @brief 游戏语音收发模式，接收方和发布方可选的模式范围一致，只有发布方和接收方设置的模式匹配时，才可能进行通话
 */
enum RangeAudioMode {
    /**
     * @brief 默认模式，发送方将发送模式设置为该模式，表示发送方针对该房间关闭麦克风，接收方设置接收模式为该模式，表示接收方不收听该房间的语音
     */
    kRangeAudioModeUndefined = 0,
    /**
     * @brief 小队模式，发送方将发送模式设置为该模式，表示只向同小队的成员发布语音，接收方设置接收模式为该模式，表示只收听同小队成员的语音
     */
    kRangeAudioModeTeam,
    /**
     * @brief 世界模式，发送方将发送模式设置为该模式，表示发布的语音可以让小队成员收听，非小队成员在满足收听条件（接收世界模式  <br>
     *       + 开启区域语音衰减时，距离足够近；关闭区域语音衰减时，可以直接听到）时也可收听；接收方将接收模式设置为该模式表示收  <br>
     *       + 听小队成员的声音和非队友在世界模式下发送的声音  <br>
     */
    kRangeAudioModeWorld
};

/**
* @hidden(iOS, Android, Windows, macOS)
* @type keytype
* @brief 远端用户的位置信息。
*/
struct RemoteUserPositionInfo {
    /**
     * @brief 音量衰减量。取值范围是 `[0,100]`，随距离呈线性衰减，当 factor 为 0 时，表示听不到声音。
     */
    int factor = 0;
    /**
     * @brief 发送模式，详见 RangeAudioMode{@link #RangeAudioMode} 。
     */
    int recv_mode = 0;
    /**
     * 发送模式{@link RangeAudioMode }
     */
    int send_mode = 0;
    /**
     * 位置信息
     */
    Position pos_ = {0, 0, 0};
    /**
     * 用户id
     */
    const char* user_id = nullptr;
    /**
     * 小队id
     */
    const char* team_id = nullptr;
};

} // namespace bytertc
