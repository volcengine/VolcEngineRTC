#include "wss_connector.h"

WebSocketConnector::WebSocketConnector() {
}

WebSocketConnector::~WebSocketConnector() {
}

void WebSocketConnector::Init() {
    mSioWrapper.reset(new sio::client());
}

void WebSocketConnector::Fini() {
    mSioWrapper.reset(nullptr);
}

void WebSocketConnector::SetReconnectParams(int attempts, int delayMsec, int maxDelayMsec) {
    if (mSioWrapper) {
        mSioWrapper->set_reconnect_attempts(attempts);
        mSioWrapper->set_reconnect_delay(delayMsec);
        mSioWrapper->set_reconnect_delay_max(maxDelayMsec);
    }
}

void WebSocketConnector::SetWssOpenedListener(const sio::client::socket_listener &l) {
    if (mSioWrapper) {
        mSioWrapper->set_socket_open_listener(l);
    }
}

void WebSocketConnector::SetWssFailedListener(const sio::client::con_listener &l) {
    if (mSioWrapper) {
        mSioWrapper->set_fail_listener(l);
    }
}

void WebSocketConnector::SetWssClosedListener(const sio::client::socket_listener &l) {
    if (mSioWrapper) {
        mSioWrapper->set_socket_close_listener(l);
    }
}

void WebSocketConnector::SetWssReconnectListener(const sio::client::reconnect_listener &l) {
    if (mSioWrapper) {
        mSioWrapper->set_reconnect_listener(l);
    }
}

void WebSocketConnector::SetWssReconnecting(std::function<void(void)> const &l) {
    if (mSioWrapper) {
        mSioWrapper->set_reconnecting_listener(l);
    }
}

void WebSocketConnector::SetWssEventListener(const std::string &eventName, const sio::socket::event_listener &func) {
    if (mSioWrapper && mSioWrapper->socket()) {
        mSioWrapper->socket()->on(eventName, func);
    }
}

void WebSocketConnector::SetWssEventListener(const std::string &eventName, const sio::socket::event_listener_aux &func){
  if (mSioWrapper && mSioWrapper->socket()) {
      mSioWrapper->socket()->on(eventName, func);
  }
}

void WebSocketConnector::Connect(const std::string &uri, const std::string &path, const std::map<std::string, std::string>& query,
    const std::map<std::string, std::string>& http_extra_headers) {
    if (mSioWrapper) {
        mSioWrapper->connect(uri, path, query, http_extra_headers);
    }
}

void WebSocketConnector::Close() {
    if (mSioWrapper) {
        mSioWrapper->close();
    }
}

void WebSocketConnector::EmitSocketMessage(const std::string &name,
        const sio::message::list &msglist,
        const std::function<void(sio::message::list const &)> &ack) {
    if (mSioWrapper && mSioWrapper->socket()) {
        mSioWrapper->socket()->emit(name, msglist, ack);
    }
}