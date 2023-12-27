//
// Created by cmj on 2022/4/24.
//

#ifndef SAMI_CORE_SAMI_CORE_AUTH_CHECK_H
#define SAMI_CORE_SAMI_CORE_AUTH_CHECK_H

typedef enum contextType {
    SAMICoreContextType_Lic_Auth = 0,
    TokenVerifyOnlineContext,
    TokenVerifyOfflineContext,
    TokenVerifyMixedContext,
    SAMICoreContextType_AbConfig = 4,
} SAMICoreContextType;

struct LicAuthParams {
    bool offlineAuth;
    const unsigned char* licBuffer;
    int licBufferLen;
    const char* appId;
};

typedef enum tokenType {
    TOKEN_TO_B = 0,
    TOKEN_TO_C_D,
    TOKEN_TO_B_MIXED,
} SAMICoreTokenType;

typedef struct TokenVerifyOnlineParameter {
    const char* url;
    const char* appKey;
    const char* token;
    const char* extra;  // json
    SAMICoreTokenType tokenType;
} SAMICoreTokenVerifyOnlineParameter;

typedef struct TokenVerifyOfflineParameter {
    const char* appKey;
    const char* token;
    const char* extra;
} SAMICoreTokenVerifyOfflineParameter;

/*
 * @brief offline and online mixed token Parameter
 * */
typedef SAMICoreTokenVerifyOfflineParameter SAMICoreTokenVerifyMixedParameter;

typedef struct TokenCreateParameter {
    const char* url;
    const char* accessKey;
    const char* secretKey;
    const char* appKey;
    const char* version;
    long int expiration;
} SAMICoreTokenCreateParameter;

typedef struct TokenResult {
    const char* token;
    long int expiration;
} SAMICoreTokenResult;

#endif  //SAMI_CORE_SAMI_CORE_AUTH_CHECK_H
