/*
 *  Copyright (c) 2020 The OnerRtc project authors. All Rights Reserved.
 *  @author TangXiangJun
 *  @email  tangxiangjun@bytedance.com
 *  @company ByteDance.Inc
 *  @brief Oner rtc engine's utils
 */
#pragma once

#include <string>
#include <vector>
#include <sstream>

#include "sio_client.h"
#include "json/json.h"

//to json
void TransferSioMessageToJson(sio::message const &msg, Json::Value &val,
        std::vector<std::shared_ptr<const std::string> > &buffers);
//to message
void TransferJsonToSioMessage(const Json::Value &val, sio::message::ptr &msg);
