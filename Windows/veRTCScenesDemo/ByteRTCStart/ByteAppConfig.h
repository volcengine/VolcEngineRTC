#pragma once
#include <string>

#define VERSION "1.0.0"

class APPConfig {
public:
    const std::string& GetLoginUserID();
    void SetLoginUserId(const std::string& user_id);
    const std::string& GetLoginUserName();
    void SetLoginUserName(const std::string& user_name);
    const std::string& GetLoginToken();
    void SetLoginToken(const std::string& user_token);
    bool HaveLoginInfo();
    void SetCheckUpdate() { m_check_update = true; }
    bool IsCheckUpdate() const { return m_check_update; }
    static APPConfig* Instance();

private:
    APPConfig() = default;
    ~APPConfig() = default;

    std::string m_user_id;
    std::string m_user_name;
    std::string m_token;
    bool m_check_update = false;

    static APPConfig* m_app_config;
};