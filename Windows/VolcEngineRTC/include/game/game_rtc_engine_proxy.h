/*
 *  Copyright (c) 2021 The ByteRtc project authors. All Rights Reserved.
 *  @company ByteDance.Inc
 *  @brief 游戏语音定义信息
 */

#pragma once

namespace bytertc {
namespace gamertc {
class IGameRTCEngineProxy {
public:
    virtual int IsTeammate(const std::string& user_id) const = 0;
    virtual std::string GetTeamId() const = 0;
    virtual std::string GetAppId() const = 0;
    virtual void EnableAudioSpatialRender(bool enable) = 0;
};

} // namespace gamertc
} // namespace bytertc
