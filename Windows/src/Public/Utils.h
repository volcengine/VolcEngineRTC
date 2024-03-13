#ifndef UTILS_H
#define UTILS_H

#include <string.h>
#include <string>
#include <QString>

#include "UserWidget.h"

class Utils
{

public:


private:
    Utils();

public:

    static std::string generateToken(const std::string& room_id, const std::string& uid);
    static bool checkIDValid(const QString name, const QString properity, QString& error_msg); //TODO


};

enum GlobalErrors {
    ERROR_VIDEO_CAPTURE = 0, //采集设备出错
};

#endif // UTILS_H
