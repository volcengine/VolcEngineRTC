//
//  TokenGenerator.m
//  ApiExample
//
//  Created by bytedance on 2023/10/7.
//  Copyright © 2021 bytedance. All rights reserved.
//

#import "TokenGenerator.h"
#include "./AccessToken.h"
#include <string>
#include <stdint.h>
using namespace rtc::tools;

@implementation TokenGenerator

+ (NSString *)tokenWithAppID:(NSString *)appId appKey:(NSString *)appKey roomId:(NSString *)roomId uid:(NSString *)userId {
    
    std::string kAppID  = appId.UTF8String;
    std::string kAppKey = appKey.UTF8String;
    std::string kRoomID = roomId.UTF8String;
    std::string kUserID = userId.UTF8String;

    AccessToken token(kAppID, kAppKey, kRoomID, kUserID);
    token.AddPrivilege(AccessToken::Privileges::PrivSubscribeStream, time(0));
    token.AddPrivilege(AccessToken::Privileges::PrivPublishStream, time(0) + 3600);
    token.ExpireTime(time(0) + 3600 * 2);

    std::string s = token.Serialize();
    printf("token: %s\n", s.c_str());

    AccessToken t = Parse(s);

    printf("appID: %s\n", t.app_id_.c_str());
    printf("appKey: %s\n", t.app_key_.c_str());
    printf("roomID: %s\n", t.room_id_.c_str());
    printf("userID: %s\n", t.user_id_.c_str());
    printf("issuedAt: %d\n", t.issued_at_);
    printf("expireAt: %d\n", t.expire_at_);
    printf("nonce: %d\n", t.nonce_);
    printf("data: %d\n", t.privileges_[AccessToken::Privileges::PrivSubscribeStream]);
    printf("signature: %s\n", t.signature_.c_str());

    printf("verify: %d\n", t.Verify(kAppKey));
    
    return [NSString stringWithUTF8String:s.c_str()];
    
}
@end
