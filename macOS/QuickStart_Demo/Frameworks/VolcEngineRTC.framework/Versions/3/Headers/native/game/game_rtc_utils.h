/*
 *  Copyright (c) 2021 The ByteRtc project authors. All Rights Reserved.
 *  @company ByteDance.Inc
 *  @brief 游戏语音定义信息
 */

#pragma once

#include <string>

#include "game_rtc_defines.h"

namespace bytertc {
namespace gamertc {

enum class GameRoomCallback {
    kEnableMicrophone,
    kEnableAudioSend,
    kEnableSpeakerphone,
    kUserJoined
};

enum SubscribeStatus {
  kUnsubscribe = 0,
  kSubscribedPending,
  kSubscribed,
};

enum EngineState {
    kEngineStateUnInitialized = 0,    // before engine creation, after engine destroy called
    kEngineStateInitialized,          // engine has been created
    kEngineStateInRoom                // joinRoom has been called
};

struct GameAudioModeUpdateStats {
    bool is_audio_send_mode_changed = false;
    bool is_audio_recv_mode_changed = false;
};

/**
 * @hidden
 * @type keytype
 * @brief 游戏引擎工作模式
 */
enum RtcMode {
    /**
     * @brief 通用模式，该模式下只能进行普通会议模式的语音通话，开启自动发布订阅。
     */
    kRtcModeGeneral = 0,
    /**
     * @brief 游戏语音模式，该模式下关闭自动发布订阅，会按照游戏业务的策略进行主动发布订阅语音。
     */
    kRtcModeLocalAudio
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

} // namespace gamertc
} // namespace bytertc