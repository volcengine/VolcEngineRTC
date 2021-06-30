#include "MeetingManager.h"
#include "json/json.h"
#include "Utils.h"

MeetingManager* g_meetingEngine = NULL;

MeetingManager* MeetingManager::GetInstance() {
    if (g_meetingEngine == NULL) {
        g_meetingEngine = new MeetingManager();
    }
    return g_meetingEngine;
}

MeetingManager::MeetingManager() {
    m_connectionManager = std::make_unique<ConnectionManager>();
}

MeetingManager::~MeetingManager() {
    m_connectionManager = nullptr;
}

void MeetingManager::registerNotification(IMeetingNotification* notification) {
    m_notification = notification;
}

void MeetingManager::startConnect() {
    if (m_connectionManager) {
        m_connectionManager->RegisterConnectedEvent(std::bind(&MeetingManager::onWebsocketConnected, this));
        m_connectionManager->RegisterConnectingEvetn(std::bind(&MeetingManager::onWebsocketConnecting, this));
        m_connectionManager->StartConnection();
    }
}

void MeetingManager::disconnect() {
    if (m_connectionManager) {
        m_connectionManager->StopConnection();
    }
}

void MeetingManager::getAppId(std::function<void(int, const std::string&)> callback) {
    Json::Value request;

    if (m_connectionManager) {
        m_connectionManager->SendSignallingMessage("getAppID", request, [callback, this](const Json::Value& response) {
#ifdef _DEBUG
            Json::StreamWriterBuilder builder;
            const std::string json_file = Json::writeString(builder, response);
#endif // _DEBUG

            auto code = response["code"].asInt();
            std::string res;
            if (code == 200) {
                m_appId = response["response"]["app_id"].asString();
                res = m_appId;
            }
            else {
                res = response["message"].asString();
            }
            callback(code, res);
        });
    }
}

void MeetingManager::joinMeeting(const std::string& userId,
    const std::string& roomId,
    bool micOn,
    bool cameraOn,
    std::function<void(int, const std::string&)> callback) {

    Json::Value request;
    request["app_id"] = m_appId;
    request["user_id"] = userId;
    request["room_id"] = roomId;
    request["mic"] = micOn;
    request["camera"] = cameraOn;

    m_room_id = roomId;
    m_user_id = userId;

    if (m_connectionManager) {
        m_connectionManager->SendSignallingMessage("joinMeeting", request, [callback](const Json::Value& response) {
#ifdef _DEBUG
            Json::StreamWriterBuilder builder;
            const std::string json_file = Json::writeString(builder, response);
#endif // _DEBUG
            auto code = response["code"].asInt();
            std::string res;
            if (code == 200) {
                res = response["response"]["token"].asString();
            }
            else {
                res = response["message"].asString();;
            }

            callback(code, res);
        });
    }
}

void MeetingManager::leaveMeeting(std::function<void(int)> callback) {
    Json::Value request;
    if (m_connectionManager) {
        m_connectionManager->SendSignallingMessage("leaveMeeting", request, [callback](const Json::Value& response) {
#ifdef _DEBUG
            Json::StreamWriterBuilder builder;
            const std::string json_file = Json::writeString(builder, response);
#endif // _DEBUG
            auto code = response["code"].asInt();
            callback(code);
        });
    }
}

void MeetingManager::userReconnect(std::function<void(int)> callback) {
    Json::Value request;
    if (m_connectionManager) {
        m_connectionManager->SendSignallingMessage("userReconnect", request, [callback](const Json::Value& response) {
#ifdef _DEBUG
            Json::StreamWriterBuilder builder;
            const std::string json_file = Json::writeString(builder, response);
#endif // _DEBUG
            auto code = response["code"].asInt();
            callback(code);
        });
    }
}

void MeetingManager::toggleMicState(bool on, std::function<void(int)> callback) {
    Json::Value request;
    if (m_connectionManager) {
        m_connectionManager->SendSignallingMessage(on ? "turnOnMic" : "turnOffMic", request, [callback](const Json::Value& response) {
#ifdef _DEBUG
            Json::StreamWriterBuilder builder;
            const std::string json_file = Json::writeString(builder, response);
#endif // _DEBUG
            auto code = response["code"].asInt();
            callback(code);
        });
    }
}

void MeetingManager::toggleCameraState(bool on, std::function<void(int)> callback) {
    Json::Value request;
    if (m_connectionManager) {
        m_connectionManager->SendSignallingMessage(on ? "turnOnCamera" : "turnOffCamera", request, [callback](const Json::Value& response) {
#ifdef _DEBUG
            Json::StreamWriterBuilder builder;
            const std::string json_file = Json::writeString(builder, response);
#endif // _DEBUG
            auto code = response["code"].asInt();
            callback(code);
        });
    }
}

void MeetingManager::getMeetingParticipantsInfoInternal(const std::string& userId, std::function<void(int, const std::list<User>&)> callback) {
    Json::Value request;
    if (!userId.empty()) {
        request["user_id"] = userId;
    }

    if (m_connectionManager) {
        m_connectionManager->SendSignallingMessage("getMeetingUserInfo", request, [callback](const Json::Value& response) {
#ifdef _DEBUG
            Json::StreamWriterBuilder builder;
            const std::string json_file = Json::writeString(builder, response);
#endif // _DEBUG

            int code = response["code"].asInt();
            const Json::Value& jUsers = response["response"];

            std::list<User> users;
            int size = jUsers.size();
            for (int i = 0; i < size; ++i) {
                const Json::Value& item = jUsers[i];
                User user;
                user.uid = item["user_id"].asString();
                user.time_of_joining = item["created_at"].asInt64();
                user.is_host = item["is_host"].asBool();
                user.is_screen_shared = item["is_sharing"].asBool();
                user.is_mic_on = item["is_mic_on"].asBool();
                user.is_camera_on = item["is_camera_on"].asBool();

                users.push_back(user);
            }
            callback(code, users);
        });
    }
}

void MeetingManager::getMeetingParticipantsInfo(std::function<void(int, const std::list<User>&)> callback) {
    getMeetingParticipantsInfoInternal("", callback);
}

void MeetingManager::getMeetingParticipantInfo(const std::string& userId,
    std::function<void(int, const User&)> callback) {
    getMeetingParticipantsInfoInternal(userId, [callback](int code, const std::list<User>& users) {
        if (users.empty()) {
            callback(code, User());
        }
        else {
            callback(code, *users.begin());
        }
    });
}

void MeetingManager::getMeetingInfo(std::function<void(int, const Room&)> callback) {

    if (m_connectionManager) {
        m_connectionManager->SendSignallingMessage("getMeetingInfo", Json::Value(), [callback](const Json::Value& response) {
#ifdef _DEBUG
            Json::StreamWriterBuilder builder;
            const std::string json_file = Json::writeString(builder, response);
#endif // _DEBUG
            int code = response["code"].asInt();
            auto jValue = response["response"];
            Room room;
            if (code == 200) {
                room.room_id = jValue["room_id"].asString();
                room.host_uid = jValue["host_id"].asString();
                room.is_recording = jValue["record"].asBool();
                room.screen_shared_uid = jValue["screen_shared_uid"].asString();
                room.meeting_start_time = jValue["created_at"].asInt64();
                room.now = jValue["now"].asInt64();
            }

            callback(code, room);
        });
    }
}

int MeetingManager::changeHost(const std::string& userId, std::function<void(int)> callback) {
    Json::Value request;
    request["user_id"] = userId;

    if (m_connectionManager) {
        m_connectionManager->SendSignallingMessage("changeHost", request, [callback](const Json::Value& response) {
#ifdef _DEBUG
            Json::StreamWriterBuilder builder;
            const std::string json_file = Json::writeString(builder, response);
#endif // _DEBUG
            auto code = response["code"].asInt();
            callback(code);
        });
    }
    return 0;
}

void MeetingManager::muteUserMic(const std::string& userId, std::function<void(int)> callback) {
    Json::Value request;
    if (!userId.empty()) {
        request["user_id"] = userId;
    }

    if (m_connectionManager) {
        m_connectionManager->SendSignallingMessage("muteUser", request, [callback](const Json::Value& response) {
#ifdef _DEBUG
            Json::StreamWriterBuilder builder;
            const std::string json_file = Json::writeString(builder, response);
#endif // _DEBUG
            auto code = response["code"].asInt();
            callback(code);
        });
    }
}

void MeetingManager::muteAllUserMic(std::function<void(int)> callback) {
    muteUserMic("", callback);
}

void MeetingManager::askUserMacOn(const std::string& userId, std::function<void(int)> callback) {
    Json::Value request;
    if (!userId.empty()) {
        request["user_id"] = userId;
    }

    if (m_connectionManager) {
        m_connectionManager->SendSignallingMessage("askMicOn", request, [callback](const Json::Value& response) {
#ifdef _DEBUG
            Json::StreamWriterBuilder builder;
            const std::string json_file = Json::writeString(builder, response);
#endif // _DEBUG
            auto code = response["code"].asInt();
            callback(code);
        });
    }
}

void MeetingManager::askUserCameraOn(const std::string& userId, std::function<void(int)> callback) {
    Json::Value request;
    if (!userId.empty()) {
        request["user_id"] = userId;
    }

    if (m_connectionManager) {
        m_connectionManager->SendSignallingMessage("askCameraOn", request, [callback](const Json::Value& response) {
#ifdef _DEBUG
            Json::StreamWriterBuilder builder;
            const std::string json_file = Json::writeString(builder, response);
#endif // _DEBUG
            auto code = response["code"].asInt();
            callback(code);
        });
    }
}

void MeetingManager::closeMeeting(std::function<void(int)> callback) {
    Json::Value request;
    if (m_connectionManager) {
        m_connectionManager->SendSignallingMessage("endMeeting", request, [callback](const Json::Value& response) {
#ifdef _DEBUG
            Json::StreamWriterBuilder builder;
            const std::string json_file = Json::writeString(builder, response);
#endif // _DEBUG
            auto code = response["code"].asInt();
            callback(code);
        });
    }
}

void MeetingManager::startScreenShare(std::function<void(int)> callback) {
    Json::Value request;
    if (m_connectionManager) {
        m_connectionManager->SendSignallingMessage("startShareScreen", request, [callback](const Json::Value& response) {
#ifdef _DEBUG
            Json::StreamWriterBuilder builder;
            const std::string json_file = Json::writeString(builder, response);
#endif // _DEBUG
            auto code = response["code"].asInt();
            callback(code);
        });
    }
}

void MeetingManager::stopScreenShare(std::function<void(int)> callback) {
    Json::Value request;
    if (m_connectionManager) {
        m_connectionManager->SendSignallingMessage("endShareScreen", request, [callback](const Json::Value& response) {
#ifdef _DEBUG
            Json::StreamWriterBuilder builder;
            const std::string json_file = Json::writeString(builder, response);
#endif // _DEBUG
            auto code = response["code"].asInt();
            callback(code);
        });
    }
}

void MeetingManager::startMeetingRecord(const std::vector<std::string>& users, const std::string& screen_uid, std::function<void(int)> callback) {
    Json::Value request;
    Json::Value jUsers(Json::arrayValue);
    for (auto& user : users) {
        jUsers.append(user);
    }

    request["users"] = jUsers;
    if (!screen_uid.empty()) {
        request["screen_uid"] = screen_uid;
    }

    if (m_connectionManager) {
        m_connectionManager->SendSignallingMessage("recordMeeting", request, [callback](const Json::Value& response) {
#ifdef _DEBUG
            Json::StreamWriterBuilder builder;
            const std::string json_file = Json::writeString(builder, response);
#endif // _DEBUG
            auto code = response["code"].asInt();
            callback(code);
        });
    }
}

void MeetingManager::updateRecordLayout(const std::vector<std::string>& users, const std::string& screen_uid, std::function<void(int)> callback) {
    return;

    Json::Value request;
    Json::Value jUsers(Json::arrayValue);
    for (auto& user : users) {
        jUsers.append(user);
    }

    request["users"] = jUsers;
    if (!screen_uid.empty()) {
        request["screen_uid"] = screen_uid;
    }

    if (m_connectionManager) {
        m_connectionManager->SendSignallingMessage("updateRecordLayout", request, [callback](const Json::Value& response) {
#ifdef _DEBUG
            Json::StreamWriterBuilder builder;
            const std::string json_file = Json::writeString(builder, response);
#endif // _DEBUG
            auto code = response["code"].asInt();
            callback(code);
        });
    }
}

void MeetingManager::getHistoryMeetingRecord(std::function<void(int, const std::list<RecordInfo>&)> callback) {
    if (m_connectionManager) {
        m_connectionManager->SendSignallingMessage("getHistoryVideoRecord", Json::Value(), [callback](const Json::Value& response) {
#ifdef _DEBUG
            Json::StreamWriterBuilder builder;
            const std::string json_file = Json::writeString(builder, response);
#endif // _DEBUG
            std::list<RecordInfo> RecordInfos;
            auto code = response["code"].asInt();
            if (code == 200) {
                auto records = response["response"];
                int size = records.size();
                for (int i = 0; i < size; ++i) {
                    const Json::Value& item = records[i];
                    RecordInfo record;
                    record.room_id = item["room_id"].asString();
                    record.url = item["download_url"].asString();
                    record.meeting_start_time = item["created_at"].asInt64();
                    RecordInfos.push_back(record);
                }
            }
            callback(code, RecordInfos);
        });
    }
}

//================================================================
void MeetingManager::onWebsocketConnected() {
    registerEevent();
    assert(m_notification);
    if (m_notification) {
        m_notification->onWebsocketConnected();
    }
}

void MeetingManager::onWebsocketConnecting() {
    assert(m_notification);
    if (m_notification) {
        m_notification->onWebsocketConnecting();
    }
}

void MeetingManager::registerEevent() {
    if (m_connectionManager) {
        m_connectionManager->RegisterEmitEvent("onUserMicStatusChange", std::bind(&MeetingManager::onUserMicStateChange, this, std::placeholders::_1));
        m_connectionManager->RegisterEmitEvent("onUserCameraStatusChange", std::bind(&MeetingManager::onUserCameraStateChange, this, std::placeholders::_1));
        m_connectionManager->RegisterEmitEvent("onHostChange", std::bind(&MeetingManager::onHostChange, this, std::placeholders::_1));
        m_connectionManager->RegisterEmitEvent("onUserJoinMeeting", std::bind(&MeetingManager::onUserJoinMeeting, this, std::placeholders::_1));
        m_connectionManager->RegisterEmitEvent("onUserLeaveMeeting", std::bind(&MeetingManager::onUserLeaveMeeting, this, std::placeholders::_1));
        m_connectionManager->RegisterEmitEvent("onShareScreenStatusChanged", std::bind(&MeetingManager::onScreenShareStateChanged, this, std::placeholders::_1));
        m_connectionManager->RegisterEmitEvent("onRecord", std::bind(&MeetingManager::onStartMeetingRecord, this, std::placeholders::_1));
        m_connectionManager->RegisterEmitEvent("onMeetingEnd", std::bind(&MeetingManager::onMeetingClose, this, std::placeholders::_1));
        m_connectionManager->RegisterEmitEvent("onMuteAll", std::bind(&MeetingManager::onMuteAllMic, this, std::placeholders::_1));
        m_connectionManager->RegisterEmitEvent("onMuteUser", std::bind(&MeetingManager::onMuteUser, this, std::placeholders::_1));
        m_connectionManager->RegisterEmitEvent("onAskingMicOn", std::bind(&MeetingManager::onAskingMicOn, this, std::placeholders::_1));
        m_connectionManager->RegisterEmitEvent("onAskingCameraOn", std::bind(&MeetingManager::onAskingCameraOn, this, std::placeholders::_1));
        m_connectionManager->RegisterEmitEvent("onUserKickedOff", std::bind(&MeetingManager::onUserKickedOff, this, std::placeholders::_1));
    }
}

void MeetingManager::onUserMicStateChange(const Json::Value& response) {
#ifdef _DEBUG
    Json::StreamWriterBuilder builder;
    const std::string json_file = Json::writeString(builder, response);
#endif // _DEBUG

    std::string userId = response["data"]["user_id"].asString();
    bool status = response["data"]["status"].asBool();

    assert(m_notification);
    if (m_notification) {
        m_notification->onUserMicStateChange(userId, status);
    }
}

void MeetingManager::onUserCameraStateChange(const Json::Value& response) {
#ifdef _DEBUG
    Json::StreamWriterBuilder builder;
    const std::string json_file = Json::writeString(builder, response);
#endif // _DEBUG
    std::string userId = response["data"]["user_id"].asString();
    bool status = response["data"]["status"].asBool();

    assert(m_notification);
    if (m_notification) {
        m_notification->onUserCameraStateChange(userId, status);
    }
}

void MeetingManager::onHostChange(const Json::Value& response) {
#ifdef _DEBUG
    Json::StreamWriterBuilder builder;
    const std::string json_file = Json::writeString(builder, response);
#endif // _DEBUG
    std::string formerHostId = response["data"]["former_host_id"].asString();
    std::string hostId = response["data"]["host_id"].asString();
    assert(m_notification);
    if (m_notification) {
        m_notification->onHostChange(formerHostId, hostId);
    }
}

void MeetingManager::onUserJoinMeeting(const Json::Value& response) {
#ifdef _DEBUG
    Json::StreamWriterBuilder builder;
    const std::string json_file = Json::writeString(builder, response);
#endif // _DEBUG
    User user;
    user.uid = response["data"]["user_id"].asString();
    user.time_of_joining = response["data"]["created_at"].asInt64();
    user.is_host = response["data"]["is_host"].asBool();
    user.is_screen_shared = response["data"]["is_sharing"].asBool();
    user.is_mic_on = response["data"]["is_mic_on"].asBool();
    user.is_camera_on = response["data"]["is_camera_on"].asBool();

    assert(m_notification);
    if (m_notification) {
        m_notification->onUserJoinMeeting(user);
    }
}

void MeetingManager::onUserLeaveMeeting(const Json::Value& response) {
#ifdef _DEBUG
    Json::StreamWriterBuilder builder;
    const std::string json_file = Json::writeString(builder, response);
#endif // _DEBUG
    std::string userId = response["data"]["user_id"].asString();

    assert(m_notification);
    if (m_notification) {
        m_notification->onUserLeaveMeeting(userId);
    }
}

void MeetingManager::onScreenShareStateChanged(const Json::Value& response) {
#ifdef _DEBUG
    Json::StreamWriterBuilder builder;
    const std::string json_file = Json::writeString(builder, response);
#endif // _DEBUG
    std::string userId = response["data"]["user_id"].asString();
    bool status = response["data"]["status"].asBool();
    assert(m_notification);
    if (m_notification) {
        m_notification->onScreenShareStateChanged(userId, status);
    }
}

void MeetingManager::onStartMeetingRecord(const Json::Value& response) {
#ifdef _DEBUG
    Json::StreamWriterBuilder builder;
    const std::string json_file = Json::writeString(builder, response);
#endif // _DEBUG
    assert(m_notification);
    if (m_notification) {
        m_notification->onStartMeetingRecord();
    }
}

void MeetingManager::onMeetingClose(const Json::Value& response) {
#ifdef _DEBUG
    Json::StreamWriterBuilder builder;
    const std::string json_file = Json::writeString(builder, response);
#endif // _DEBUG
    assert(m_notification);
    if (m_notification) {
        m_notification->onMeetingClose();
    }
}

void MeetingManager::onMuteAllMic(const Json::Value& response) {
#ifdef _DEBUG
    Json::StreamWriterBuilder builder;
    const std::string json_file = Json::writeString(builder, response);
#endif // _DEBUG

    assert(m_notification);
    if (m_notification) {
        m_notification->onMuteAllMic();
    }
}

void MeetingManager::onMuteUser(const Json::Value& response) {
#ifdef _DEBUG
    Json::StreamWriterBuilder builder;
    const std::string json_file = Json::writeString(builder, response);
#endif // _DEBUG

    std::string userId = response["data"]["user_id"].asString();
    assert(m_notification);
    if (m_notification) {
        m_notification->onMuteUser(userId);
    }
}

void MeetingManager::onAskingMicOn(const Json::Value& response) {
#ifdef _DEBUG
    Json::StreamWriterBuilder builder;
    const std::string json_file = Json::writeString(builder, response);
#endif // _DEBUG

    std::string userId = response["data"]["user_id"].asString();
    assert(m_notification);
    if (m_notification) {
        m_notification->onAskingMicOn(userId);
    }
}

void MeetingManager::onAskingCameraOn(const Json::Value& response) {
#ifdef _DEBUG
    Json::StreamWriterBuilder builder;
    const std::string json_file = Json::writeString(builder, response);
#endif // _DEBUG

    std::string userId = response["data"]["user_id"].asString();
    assert(m_notification);
    if (m_notification) {
        m_notification->onAskingCameraOn(userId);
    }
}

void MeetingManager::onUserKickedOff(const Json::Value& response) {
#ifdef _DEBUG
    Json::StreamWriterBuilder builder;
    const std::string json_file = Json::writeString(builder, response);
#endif // _DEBUG

    assert(m_notification);
    if (m_notification) {
        m_notification->onUserKickedOff();
    }
}