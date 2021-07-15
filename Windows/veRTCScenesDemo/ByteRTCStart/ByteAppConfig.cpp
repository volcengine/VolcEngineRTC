#include "ByteAppConfig.h"
#include <Windows.h>

#define CONFIGER_FILE ".\\Configer.ini"
APPConfig* APPConfig::m_app_config = nullptr;

APPConfig* APPConfig::Instance() {
    if (!m_app_config) {
        m_app_config = new APPConfig();
    }
    return m_app_config;
}

const std::string& APPConfig::GetLoginUserID() {
    char buffer[256];
    memset(buffer, 0x00, sizeof buffer);
    int code = GetPrivateProfileStringA("Login", "UserId", "", buffer, sizeof buffer, CONFIGER_FILE);
    m_user_id = buffer;

    return m_user_id;
}

void APPConfig::SetLoginUserId(const std::string& user_id) {
    m_user_id = user_id;
    WritePrivateProfileStringA("Login", "UserId", user_id.c_str(), CONFIGER_FILE);
}

const std::string& APPConfig::GetLoginUserName() {
    char buffer[256];
    memset(buffer, 0x00, sizeof buffer);
    int code = GetPrivateProfileStringA("Login", "UserName", "", buffer, sizeof buffer, CONFIGER_FILE);
    m_user_name = buffer;

    return m_user_name;
}

void APPConfig::SetLoginUserName(const std::string& user_name) {
    m_user_name = user_name;
    WritePrivateProfileStringA("Login", "UserName", user_name.c_str(), CONFIGER_FILE);
}

const std::string& APPConfig::GetLoginToken() {
    char buffer[256];
    memset(buffer, 0x00, sizeof buffer);
    int code = GetPrivateProfileStringA("Login", "Token", "", buffer, sizeof buffer, CONFIGER_FILE);
    m_token = buffer;

    return m_token;
}

void APPConfig::SetLoginToken(const std::string& user_token) {
    m_token = user_token;
    WritePrivateProfileStringA("Login", "Token", user_token.c_str(), CONFIGER_FILE);
}

bool APPConfig::HaveLoginInfo() {
    GetLoginUserID();
    GetLoginUserName();
    GetLoginToken();

    return !m_user_id.empty() && !m_user_name.empty() && !m_token.empty();
}