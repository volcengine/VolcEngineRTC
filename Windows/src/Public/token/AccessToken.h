#pragma once

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include "./utils.h"

namespace rtc {
namespace tools {

struct AccessToken {
    enum Privileges{
        PrivPublishStream = 0,

        // not exported, do not use directly
    	privPublishAudioStream=1,
    	privPublishVideoStream=2,
    	privPublishDataStream=3,

    	PrivSubscribeStream=4,
    };

    static std::string Version() { return "001"; }

    typedef std::map<uint16_t, uint32_t> PrivilegeMap;

    TOOLS_DECLARE_PACKABLE_6(Msg, uint32_t, nonce, uint32_t, issuedAt, uint32_t, expireAt,
                            std::string, roomID, std::string, userID,
                           PrivilegeMap, privileges);

    TOOLS_DECLARE_PACKABLE_2(Content, Msg, msg, std::string, signature);

    // Initializes token struct by required parameters.
    AccessToken(const std::string& appID, const std::string& appKey,
           const std::string& roomID, const std::string& userID)
           : app_id_(appID),
           app_key_(appKey),
           room_id_(roomID),
           user_id_(userID){
           uint32_t now = uint32_t(time(NULL));
           issued_at_ = now;
           nonce_ = GenerateSalt();
    }

    // AddPrivilege adds permission for token with an expiration.
    void AddPrivilege(Privileges privilege, uint32_t expireTimestamp = 0) {
        privileges_[uint16_t(privilege)] = expireTimestamp;

        if (privilege == Privileges::PrivPublishStream){
            privileges_[Privileges::privPublishAudioStream] = expireTimestamp;
            privileges_[Privileges::privPublishVideoStream] = expireTimestamp;
            privileges_[Privileges::privPublishDataStream] = expireTimestamp;
        }
    }

    // ExpireTime sets token expire time, won't expire by default.
    // The token will be invalid after expireTime no matter what privilege's expireTime is.
    void ExpireTime(uint32_t expireTimestamp = 0) {
        expire_at_ = expireTimestamp;
    }

    std::string packMsg() {
        Msg msg;
        msg.nonce = nonce_;
        msg.issuedAt = issued_at_;
        msg.expireAt = expire_at_;
        msg.roomID = room_id_;
        msg.userID = user_id_;
        msg.privileges = privileges_;
        return Pack(msg);
    }

    // Serialize generates the token string
    std::string Serialize() {
        std::string msg = packMsg();
        signature_ = HmacSign2(app_key_, msg, HMAC_SHA256_LENGTH);

        std::stringstream buf;
        buf << Pack(msg) << Pack(signature_);

        std::stringstream ss;
        ss << AccessToken::Version() << app_id_ << base64Encode(buf.str());
        return ss.str();
    }

    // Verify checks if this token valid, called by server side.
    bool Verify(std::string key){
        if (expire_at_ > 0 &&time(0) > expire_at_){
            return false;
        }

        app_key_ = key;
        return HmacSign2(app_key_, packMsg(), HMAC_SHA256_LENGTH) == signature_;
    }



  std::string app_id_;
  std::string app_key_;
  std::string room_id_;
  std::string user_id_;
  uint32_t issued_at_;
  uint32_t nonce_;
  uint32_t expire_at_;
  PrivilegeMap privileges_;
  std::string signature_;
};


inline AccessToken Parse(std::string raw){
    AccessToken token("","","","");

    if (raw.substr(0, VERSION_LENGTH) != AccessToken::Version()) {
        return token;
    }

    try {
        token.app_id_ = raw.substr(VERSION_LENGTH, APP_ID_LENGTH);
        std::string contentEncoded = base64Decode(raw.substr(VERSION_LENGTH + APP_ID_LENGTH, raw.size()));

        std::string msgRaw;
        Unpack(contentEncoded, msgRaw);

        std::string sig = contentEncoded.substr(2 + msgRaw.size(), contentEncoded.size());

        Unpack(sig, token.signature_);

        AccessToken::Msg msg;
        Unpack(msgRaw, msg);
        token.nonce_ = msg.nonce;
        token.issued_at_ = msg.issuedAt;
        token.expire_at_ = msg.expireAt;
        token.room_id_ = msg.roomID;
        token.user_id_ = msg.userID;
        token.privileges_ = msg.privileges;

    } catch (std::exception& e) {
      std::cerr << e.what();

      return token;
    }

    return token;
};

}
}
