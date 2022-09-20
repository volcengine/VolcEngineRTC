#pragma once
#include <string>

/**
 * VolcEngineRTC 常量定义
 *
 * - APPID 使用SDK前需要为自己的应用申请一个AppId，详情参见{https://www.volcengine.com/docs/6348/69865}
 * - TOKEN 加入房间的时候需要使用token完成鉴权，详情参见{https://www.volcengine.com/docs/6348/70121}
 * - INPUT_REGEX SDK 对房间名、用户名的限制是：非空且最大长度不超过128位的数字、大小写字母、@ . _ -
 */
class Constants
{
public:
	 static  std::string APP_ID;
	 static  std::string TOKEN ;
	 static  std::string INPUT_REGEX;
};

std::string Constants::APP_ID = "";

std::string Constants::TOKEN = "";

std::string Constants::INPUT_REGEX = "^[a-zA-Z0-9@._-]{1,128}$";