/*
 *  Copyright (c) 2020 The OnerRtc project authors. All Rights Reserved.
 *  @author TangXiangJun
 *  @email  tangxiangjun@bytedance.com
 *  @company ByteDance.Inc
 *  @brief Oner rtc engine's manager of connections
 */
#pragma once

#include <map>
#include <string>
#include <vector>
#include <chrono>
#include <functional>
#include "bus/byte_basic_task_queue.h"
#include "json/json.h"
#include "wss_connector.h"

class ConnectionManager : public bytertc::basic::WeakHandler<ConnectionManager> {
public:
    ConnectionManager();
    ~ConnectionManager();

    void StartConnection();
    void StopConnection();
    void SendSignallingMessage(const std::string& type, const Json::Value &req = Json::Value(), std::function<void(const Json::Value&)> callback = [](const Json::Value&) {});
    void RegisterEmitEvent(const std::string& event, std::function<void(const Json::Value&)> response_callback);
    void RegisterConnectedEvent(std::function<void()> notification);
    void RegisterConnectingEvetn(std::function<void()> notification);

private:
    struct Message {
        std::string type;
        sio::message::ptr msg;
        std::function<void(sio::message::list const &)> ack;
    };

    void OpenWebsocket();
    void CloseWebsocket();
    void OnWebsocketConnected(std::string const &nsp);
    void OnWebsocketFail();
    void OnWebsocketClose(std::string const &nsp);
    void OnWebsocketReconnect(unsigned, unsigned);
    void OnWebsocketReconnecting();
    void OnReceivedEmitEvent(sio::event &event, std::function<void(const Json::Value&)> response_callback);

private:
    std::string m_reconnect_id;
    uint32_t m_task_tag;
    bool m_ws_open;
    //TaskThread *m_worker_thread;

    uint64_t m_open_count;
    std::chrono::system_clock::time_point m_ws_start_ts;
    std::chrono::system_clock::time_point mTransportTcpDnsReslovedTimeStamp;
    std::chrono::system_clock::time_point mTransportTcpConnectedTimeStamp;
    std::chrono::system_clock::time_point mTransportTcpDataReceivedTimeStamp;

private:
    bool m_is_first_server_configure;
    std::string m_ws_url;
    std::string m_ws_path;

    std::unique_ptr<WebSocketConnector> mWssConnector;
    std::shared_ptr<bytertc::basic::TaskQueue> mSignalingQueue;
    std::function<void()> m_connected_notification = nullptr;
    std::function<void()> m_connecting_notification = nullptr;
};
