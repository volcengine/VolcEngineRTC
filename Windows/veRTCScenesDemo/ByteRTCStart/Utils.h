#ifndef _RTC_UTILS_H 
#define _RTC_UTILS_H

#include <string>
#include "BDUIKit/BDMisc.h"

namespace Gdiplus {
    class Image;
}

namespace rtcutil {
std::string ConvertBDStringToUTF8(BDString strValue);
BDString ConvertUTF8ToBDString(std::string utf8str);
void SetWindowCentor(HWND hwnd);
std::string GetSystemTimeText();
int64_t GetTimestamp();

bool IsValidUserString(const BDString& str);
bool IsValidRoomString(const BDString& str);

bool LoadFile(LPCWSTR szFileName, Gdiplus::Image*& pImage);
bool DrawImage(HDC DC, Gdiplus::Image* pImage, INT nXPos, INT nYPos, INT Width, INT Height);

std::string UuidGenerator();
std::string GetDeviceId();
std::string GetOsInfo();
void GetDisplayList(std::vector<RECT>& displayList);
}  // namespace rtcutil

#endif