
#include "Utils.h"
#include <chrono>
#include <gdiplus.h>
#include <random>
#include <sstream>

using namespace Gdiplus;

namespace rtcutil {

std::string ConvertBDStringToUTF8(BDString strValue) {
    std::wstring wbuffer;
#ifdef _UNICODE
    wbuffer.assign((LPCWSTR)strValue, strValue.GetLength());
#else
    int length = ::MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS, (LPCTSTR)strValue, -1, NULL, 0);
    wbuffer.resize(length);
    MultiByteToWideChar(CP_ACP, 0, (LPCTSTR)strValue, -1, (LPWSTR)(wbuffer.data()), wbuffer.length());
#endif
    int length = WideCharToMultiByte(CP_UTF8, 0, wbuffer.data(), wbuffer.size(), NULL, 0, NULL, NULL);
    std::string buffer;
    buffer.resize(length);
    WideCharToMultiByte(CP_UTF8, 0, strValue, -1, (LPSTR)(buffer.data()), length, NULL, NULL);
    return (buffer);
}

BDString ConvertUTF8ToBDString(std::string utf8str) {
    int nLen = ::MultiByteToWideChar(CP_UTF8, NULL, utf8str.data(), utf8str.size(), NULL, 0);
    std::wstring wbuffer;
    wbuffer.resize(nLen);
    ::MultiByteToWideChar(CP_UTF8, NULL, utf8str.data(), utf8str.size(), (LPWSTR)(wbuffer.data()), wbuffer.length());
#ifdef UNICODE
    return (BDString(wbuffer.data(), wbuffer.length()));
#else
    nLen = WideCharToMultiByte(CP_ACP, 0, wbuffer.data(), wbuffer.length(), NULL, 0, NULL, NULL);
    std::string ansistr;
    ansistr.resize(nLen);
    WideCharToMultiByte(
            CP_ACP, 0, (LPWSTR)(wbuffer.data()), wbuffer.length(), (LPSTR)(ansistr.data()), ansistr.size(), NULL, NULL);
    return (CString(ansistr.data(), ansistr.length()));
#endif
}

void SetWindowCentor(HWND hwnd) {
    RECT rect;
    int scrWidth = GetSystemMetrics(SM_CXSCREEN);
    int scrHeight = GetSystemMetrics(SM_CYSCREEN);
    GetWindowRect(hwnd, &rect);
    long width = rect.right - rect.left;
    long height = rect.bottom - rect.top;
    rect.left = (scrWidth - width) / 2;
    rect.top = (scrHeight - height) / 2;
    SetWindowPos(hwnd, HWND_TOP, rect.left, rect.top, width, height, SWP_NOSIZE | SWP_NOZORDER);
}

std::string GetSystemTimeText() {
    SYSTEMTIME st;
    GetLocalTime(&st);
    BDString csTime;
    csTime.Format(L"%4d-%d-%d %02d:%02d:%02d.%03d", st.wYear, st.wMonth, st.wDay, 
        st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
    return std::string(ConvertBDStringToUTF8(csTime));
}

int64_t GetTimestamp() {
    return (int64_t)std::chrono::duration_cast<std::chrono::seconds>(
        std::chrono::system_clock::now().time_since_epoch())
        .count();
}


bool DrawImage(HDC DC, Gdiplus::Image* pImage, INT nXPos, INT nYPos, INT Width, INT Height)
{
    if (pImage == NULL) return false;

    Graphics graphics(DC);

    INT nImageWidth = pImage->GetWidth();
    INT nImageHeight = pImage->GetHeight();

    RectF rcDrawRect;
    rcDrawRect.X = (REAL)nXPos;
    rcDrawRect.Y = (REAL)nYPos;
    rcDrawRect.Width = (REAL)Width;
    rcDrawRect.Height = (REAL)Height;

    // Painting image
    graphics.DrawImage(pImage, rcDrawRect, 0, 0, (REAL)nImageWidth, (REAL)nImageHeight, UnitPixel);
    return true;
}

bool LoadFile(LPCWSTR szFileName, Gdiplus::Image*& pImage)
{
    DWORD RSize;
    HANDLE hOpenFile = (HANDLE)CreateFile(szFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, NULL, NULL);
    DWORD dwSize = GetFileSize(hOpenFile, NULL);

    HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE | GMEM_NODISCARD, dwSize);
    if (!hGlobal)
        return false;

    char *pData = reinterpret_cast<char*>(GlobalLock(hGlobal));
    if (!pData)
    {
        GlobalFree(hGlobal);
        return false;
    };

    ReadFile(hOpenFile, pData, dwSize, &RSize, NULL);

    IStream *pStream = NULL;
    if (CreateStreamOnHGlobal(hGlobal, TRUE, &pStream) != S_OK)
        return FALSE;

    pImage = Image::FromStream(pStream);

    GlobalUnlock(hGlobal);
    pStream->Release();

    return true;
}

std::string UuidGenerator() {
    char uuid[32] = { 0 };
    std::random_device rd;
    snprintf(uuid, sizeof(uuid), "%08x", rd());
    snprintf(uuid + 8, sizeof(uuid) - 8, "%08x", rd());
    snprintf(uuid + 16, sizeof(uuid) - 16, "%08x", rd());
    return uuid;
}

std::string GetDeviceId() {
    // TODO WuNL add windows get device ID
    const char* data_Set = "SOFTWARE\\Microsoft\\Cryptography";
    HKEY hKEY = nullptr;
    std::string key = "MachineGuid";
    std::string deviceId = "";

    int res = ::RegOpenKeyExA(HKEY_LOCAL_MACHINE, data_Set, 0, KEY_READ | KEY_WOW64_64KEY, &hKEY);
    DWORD dwType = REG_SZ;
    DWORD dwSize = 0;
    if (ERROR_SUCCESS == res) {
        res = ::RegQueryValueExA(hKEY, key.c_str(), 0, &dwType, nullptr, &dwSize);
    }
    std::vector<BYTE> regData;
    if (ERROR_SUCCESS == res && dwSize > 0) {
        regData.resize(dwSize);
        res = ::RegQueryValueExA(hKEY, key.c_str(), 0, &dwType, regData.data(), &dwSize);
    }

    if (!regData.empty()) {
        deviceId = (char*)regData.data();
    }

    // close registry
    if (hKEY != nullptr) {
        ::RegCloseKey(hKEY);
        hKEY = nullptr;
    }

    return deviceId;
}

std::string GetOsInfo() {
    // get os name according to version number
    OSVERSIONINFO osver = { sizeof(OSVERSIONINFO) };
    GetVersionEx(&osver);
    std::string os_name;
    if (osver.dwMajorVersion == 5 && osver.dwMinorVersion == 0)
        os_name = "Windows 2000";
    else if (osver.dwMajorVersion == 5 && osver.dwMinorVersion == 1)
        os_name = "Windows XP";
    else if (osver.dwMajorVersion == 6 && osver.dwMinorVersion == 0)
        os_name = "Windows 2003";
    else if (osver.dwMajorVersion == 5 && osver.dwMinorVersion == 2)
        os_name = "windows vista";
    else if (osver.dwMajorVersion == 6 && osver.dwMinorVersion == 1)
        os_name = "windows 7";
    else if (osver.dwMajorVersion == 6 && osver.dwMinorVersion == 2)
        os_name = "windows 10";

    std::ostringstream res;
    res << os_name << " " << osver.dwMajorVersion << '.' << osver.dwMinorVersion;
    return res.str();
}

void GetDisplayList(std::vector<RECT>& displayList) {
    for (int index = 0;; index++) {
        DISPLAY_DEVICE device;
        device.cb = sizeof(device);
        bool result = EnumDisplayDevices(NULL, index, &device, 0);
        if (!result) {
            break;
        }
        if (!(device.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP)) {
            continue;
        }

        DEVMODE device_mode;
        device_mode.dmSize = sizeof(DEVMODE);
        device_mode.dmDriverExtra = 0;
        EnumDisplaySettingsEx(device.DeviceName, ENUM_CURRENT_SETTINGS, &device_mode, 0);

        RECT rect;
        rect.left = device_mode.dmPosition.x;
        rect.top = device_mode.dmPosition.y;
        rect.right = device_mode.dmPelsWidth + rect.left;
        rect.bottom = device_mode.dmPelsHeight + rect.top;
        displayList.push_back(rect);
    }
}

void string_replace(std::string *strBig, const std::string &strsrc, const std::string &strdst) {
    std::string::size_type pos = 0;
    std::string::size_type srclen = strsrc.size();
    std::string::size_type dstlen = strdst.size();

    while ((pos = (*strBig).find(strsrc, pos)) != std::string::npos) {
        (*strBig).replace(pos, srclen, strdst);
        pos += dstlen;
    }
}

std::string getTimestampDescription(int64_t timestamp) {
    time_t tm(timestamp);
    std::string des(ctime(&tm));
    string_replace(&des, "\n", "");
    return des;
}

bool IsValidRoomString(const BDString& str) {
    for (int i = 0; i < (int)str.GetLength(); i++) {
        wchar_t ch = str[i];
        if (ch >= L'a' && ch <= L'z') continue;
        else if (ch >= L'A' && ch <= L'Z') continue;
        else if (ch >= L'0' && ch <= L'9') continue;
        else if (ch == L'@' || ch == L'.' || ch == L'_' || ch == L'-') continue;
        return false;
    }

    return true;
}

bool IsValidUserString(const BDString& str) {
    for (int i = 0; i < (int)str.GetLength(); i++) {
        wchar_t ch = str[i];
        if (ch >= L'a' && ch <= L'z') continue;
        else if (ch >= L'A' && ch <= L'Z') continue;
        else if (ch >= L'0' && ch <= L'9') continue;
        else if(ch >= 0x4E00 && ch <= 0x9FEF) continue;
        else if (ch >= 0x3400 && ch <= 0x4DB5) continue;

        return false;
    }

    return true;
}
}  // namespace rtcutil