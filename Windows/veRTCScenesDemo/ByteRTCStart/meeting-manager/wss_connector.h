/*
 *  Copyright (c) 2020 The OnerRtc project authors. All Rights Reserved.
 *  @author TangXiangJun
 *  @email  tangxiangjun@bytedance.com
 *  @company ByteDance.Inc
 *  @brief Oner rtc engine secure websocket connector
 */
#pragma once

#include "sio_client.h"
#include <string>
#include <map>

class WebSocketConnector {
public:
    WebSocketConnector();
    virtual ~WebSocketConnector();
    virtual void Init();
    virtual void Fini();

    //folowing api will only work as expectation within func calls between Init and Fini
    virtual void SetReconnectParams(int attempts, int delayMsec, int maxDelayMsec);
    virtual void SetWssOpenedListener(const sio::client::socket_listener &l);
    virtual void SetWssFailedListener(const sio::client::con_listener &l);
    virtual void SetWssClosedListener(const sio::client::socket_listener &l);
    virtual void SetWssReconnectListener(const sio::client::reconnect_listener &l);
    virtual void SetWssReconnecting(const std::function<void(void)> &l);
    virtual void SetWssEventListener(const std::string &eventName, const sio::socket::event_listener &func);
    virtual void SetWssEventListener(const std::string &eventName, const sio::socket::event_listener_aux &func);

    virtual void Connect(const std::string &uri, const std::string &path, const std::map<std::string, std::string>& query,
        const std::map<std::string, std::string>& http_extra_headers = {});
    virtual void Close();
    virtual void EmitSocketMessage(const std::string &name,
            const sio::message::list &msglist,
            const std::function<void(sio::message::list const &)> &ack);

private:
    std::unique_ptr<sio::client> mSioWrapper;
};
