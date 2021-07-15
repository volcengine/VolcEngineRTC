#include <memory>
#include "utils/json_util.h"
#include "Utils.h"
#include "connection_manager.h"

ConnectionManager::ConnectionManager()
    :mWssConnector(new WebSocketConnector()) {
    mSignalingQueue = std::make_shared<bytertc::basic::TaskQueue>(
        -1, "signaling_worker_thread");
    mSignalingQueue->Startup();
    //mConnectTimerTag = bytertc::basic::TaskQueue::NextTaskId();
}

ConnectionManager::~ConnectionManager() {
   mWssConnector = nullptr;
   mSignalingQueue.reset();
}

void ConnectionManager::RegisterConnectedEvent(std::function<void()> notification) {
    m_connected_notification = notification;
}

void ConnectionManager::RegisterConnectingEvetn(std::function<void()> notification) {
    m_connecting_notification = notification;
}

void ConnectionManager::StartConnection() {
    mSignalingQueue->SafeAsyncTask(CODE_FROM_HERE, this, [&]() {
#ifdef _DEBUG
        const std::string host("rtc-newton.bytedance.com:80");
        m_ws_url = "http://" + host;
#else
        const std::string host("rtc-newton.bytedance.com");
        m_ws_url = "https://" + host;
#endif // DEBUG

        m_ws_path = "/vc_control";
        OpenWebsocket();
    });
}

void ConnectionManager::StopConnection() {
    mSignalingQueue->SafeAsyncTask(CODE_FROM_HERE, this, [&]() {
        CloseWebsocket();
    });
}

void ConnectionManager::SendSignallingMessage(const std::string& type, const Json::Value &req, std::function<void(const Json::Value&)> callback) {
    sio::message::ptr message;
    TransferJsonToSioMessage(req, message);
    mWssConnector->EmitSocketMessage(type, message, [this, callback](sio::message::list const & messages){
        if (messages.size() > 0) {
            sio::message::ptr message = messages.at(0);
            Json::Value responseJson;
            std::vector<std::shared_ptr<const std::string> > buffers;
            TransferSioMessageToJson(*message, responseJson, buffers);

            mSignalingQueue->SafeAsyncTask(CODE_FROM_HERE, this, [callback, responseJson]() {
                callback(responseJson);
            });
        }
    });
}

void ConnectionManager::OpenWebsocket() {
    mWssConnector->Init();
    m_ws_open = true;
    mWssConnector->SetReconnectParams(10, 500, 1000);
    mWssConnector->SetWssOpenedListener(std::bind(&ConnectionManager::OnWebsocketConnected,
            this,
            std::placeholders::_1));
    mWssConnector->SetWssFailedListener(std::bind(&ConnectionManager::OnWebsocketFail, this));
    mWssConnector->SetWssClosedListener(std::bind(&ConnectionManager::OnWebsocketClose, this, std::placeholders::_1));
    mWssConnector->SetWssReconnectListener(std::bind(&ConnectionManager::OnWebsocketReconnect,
            this,
            std::placeholders::_1,
            std::placeholders::_2));
    mWssConnector->SetWssReconnecting(std::bind(&ConnectionManager::OnWebsocketReconnecting, this));

    mTransportTcpDnsReslovedTimeStamp = std::chrono::system_clock::now();
    mTransportTcpConnectedTimeStamp = mTransportTcpDnsReslovedTimeStamp;
    mTransportTcpDataReceivedTimeStamp = mTransportTcpDnsReslovedTimeStamp;

    std::map<std::string, std::string> query;
    query["wsid"] = rtcutil::UuidGenerator();
    query["appid"] = "veRTCDemo";
    query["ua"] = "windows-3.0.3";
    query["did"] = rtcutil::GetDeviceId();

    mWssConnector->Connect(m_ws_url, m_ws_path,  query);
}

void ConnectionManager::RegisterEmitEvent(const std::string& eventName, std::function<void(const Json::Value&)> response_callback) {
    const std::string emitEventName = eventName;
    if (mWssConnector != nullptr) {
        mWssConnector->SetWssEventListener(emitEventName,
                                std::bind(&ConnectionManager::OnReceivedEmitEvent,
                                        this,
                                        std::placeholders::_1,
                                        response_callback));
    }
}

void ConnectionManager::CloseWebsocket() {
    mWssConnector->Close();
}

void ConnectionManager::OnWebsocketConnected(std::string const &nsp) {
    mSignalingQueue->SafeAsyncTask(CODE_FROM_HERE, this, [this]() {
        if (m_connected_notification) {
            m_connected_notification();
        }
    });
}

void ConnectionManager::OnWebsocketFail() {
    mSignalingQueue->SafeAsyncDelayTask(CODE_FROM_HERE, std::chrono::milliseconds(500), this, [this]() {
        OpenWebsocket();
    });
}

void ConnectionManager::OnWebsocketClose(std::string const &nsp) {

}

void ConnectionManager::OnWebsocketReconnect(unsigned q, unsigned s) {

}

void ConnectionManager::OnWebsocketReconnecting() {
    mSignalingQueue->SafeAsyncTask(CODE_FROM_HERE, this, [this]() {
        if (m_connecting_notification) {
            m_connecting_notification();
        }
    });
}

void ConnectionManager::OnReceivedEmitEvent(sio::event &event, std::function<void(const Json::Value&)> response_callback) {
    std::string emitEventName = event.get_name();
    const sio::message::list& messages = event.get_messages();
    if (messages.size() > 0) {
        sio::message::ptr message = messages.at(0);
        Json::Value responseJson;
        std::vector<std::shared_ptr<const std::string> > buffers;
        TransferSioMessageToJson(*message, responseJson, buffers);

        mSignalingQueue->SafeAsyncTask(CODE_FROM_HERE, this, [response_callback, responseJson]() {
            response_callback(responseJson);
        });
    }
}
