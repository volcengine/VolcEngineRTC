#include "Utils.h"

#include <QApplication>
#include <regex>

#include "AccessToken.h"
#include "Config.h"

static std::string const base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";

Utils::Utils()
{

}

//模拟服务端生成控制台的token
std::string generateServerToken(
        const std::string room_id,
        const std::string uid)
{
    if (g_appid.empty() || g_appkey.empty() || room_id.empty() || uid.empty()) {
        return "";
    }

    rtc::tools::AccessToken token(g_appid, g_appkey, room_id, uid);
    token.AddPrivilege(rtc::tools::AccessToken::Privileges::PrivSubscribeStream, time(0));
    token.AddPrivilege(rtc::tools::AccessToken::Privileges::PrivPublishStream, time(0) + 3600);
    token.ExpireTime(time(0) + 3600 * 2);

    std::string s = token.Serialize();
    return s;
}



inline std::string base64_encode(unsigned char const* input, size_t len) {
    std::string ret;
    int i = 0;
    int j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];

    while (len--) {
        char_array_3[i++] = *(input++);
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) +
                ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) +
                ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for (i = 0; (i < 4); i++) {
                ret += base64_chars[char_array_4[i]];
            }
            i = 0;
        }
    }

    if (i) {
        for (j = i; j < 3; j++) {
            char_array_3[j] = '\0';
        }

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) +
            ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) +
            ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;

        for (j = 0; (j < i + 1); j++) {
            ret += base64_chars[char_array_4[j]];
        }

        while ((i++ < 3)) {
            ret += '=';
        }
    }

    return ret;
}

inline std::string base64_encode(std::string const& input) {
    return base64_encode(
        reinterpret_cast<const unsigned char*>(input.data()),
        input.size()
    );
}

std::string Utils::generateToken(
        const std::string& room_id,
        const std::string& uid) {

    std::string token_server;
    if (room_id.empty() || uid.empty() || g_appid.empty() || g_appkey.empty()) {
        return token_server;
    }

    token_server = generateServerToken(room_id, uid);
    return token_server;
}

bool Utils::checkIDValid(const QString name, const QString properity, QString &error_msg)
{

    if (name.isEmpty())
    {
        error_msg = properity + QStringLiteral("不能为空");
        return false;
    }

    if (name.size() > 128)
    {
        error_msg = properity + QStringLiteral("不能超过128个字符");
        return false;
    }
    std::string str_name = name.toStdString();
    std::regex re("^[a-zA-Z0-9@._-]{1,128}$");
    if (std::regex_match(str_name.c_str(), re)) {
        error_msg = "ok";
        return true;
    } else {
        error_msg = "只支持数字、大小写字母、@._-";
        return false;
    }
    return false;
}

