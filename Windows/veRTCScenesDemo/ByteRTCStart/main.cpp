// ByteRTCStart.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "resource.h"
#include "BDUserLoginWnd.h"
#include <gdiplus.h>
#include <windows.h>
#include <DbgHelp.h>
#include <stdlib.h>
#pragma comment(lib, "dbghelp.lib")
using namespace Gdiplus;

inline BOOL IsDataSectionNeeded(const WCHAR* pModuleName)
{
    if (pModuleName == 0)
    {
        return FALSE;
    }

    WCHAR szFileName[_MAX_FNAME] = L"";
    _wsplitpath(pModuleName, NULL, NULL, szFileName, NULL);

    if (_wcsicmp(szFileName, L"ntdll") == 0)
        return TRUE;

    return FALSE;
}

inline BOOL CALLBACK MiniDumpCallback(PVOID pParam,
    const PMINIDUMP_CALLBACK_INPUT   pInput,
    PMINIDUMP_CALLBACK_OUTPUT        pOutput)
{
    if (pInput == 0 || pOutput == 0)
        return FALSE;

    switch (pInput->CallbackType)
    {
    case ModuleCallback:
        if (pOutput->ModuleWriteFlags & ModuleWriteDataSeg)
            if (!IsDataSectionNeeded(pInput->Module.FullPath))
                pOutput->ModuleWriteFlags &= (~ModuleWriteDataSeg);
    case IncludeModuleCallback:
    case IncludeThreadCallback:
    case ThreadCallback:
    case ThreadExCallback:
        return TRUE;
    default:;
    }

    return FALSE;
}

inline void CreateMiniDump(PEXCEPTION_POINTERS pep, LPCTSTR strFileName) {
    HANDLE hFile = CreateFile(strFileName, GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    if ((hFile != NULL) && (hFile != INVALID_HANDLE_VALUE))
    {
        MINIDUMP_EXCEPTION_INFORMATION mdei;
        mdei.ThreadId = GetCurrentThreadId();
        mdei.ExceptionPointers = pep;
        mdei.ClientPointers = NULL;

        MINIDUMP_CALLBACK_INFORMATION mci;
        mci.CallbackRoutine = (MINIDUMP_CALLBACK_ROUTINE)MiniDumpCallback;
        mci.CallbackParam = 0;

        ::MiniDumpWriteDump(::GetCurrentProcess(), ::GetCurrentProcessId(), hFile, MiniDumpNormal, (pep != 0) ? &mdei : 0, NULL, &mci);

        CloseHandle(hFile);
    }
}

LONG __stdcall MyUnhandledExceptionFilter(PEXCEPTION_POINTERS pExceptionInfo) {
    DWORD processId = GetCurrentProcessId();
    BDString name;
    name.Format(L"crash\\veRTC%ld.dmp");
    CreateMiniDump(pExceptionInfo, name);
    return   EXCEPTION_EXECUTE_HANDLER;
}

void DisableSetUnhandledExceptionFilter()
{
    void* addr = (void*)GetProcAddress(LoadLibrary(L"kernel32.dll"),
        "SetUnhandledExceptionFilter");

    if (addr)
    {
        unsigned char code[16];
        int size = 0;

        code[size++] = 0x33;
        code[size++] = 0xC0;
        code[size++] = 0xC2;
        code[size++] = 0x04;
        code[size++] = 0x00;

        DWORD dwOldFlag, dwTempFlag;
        VirtualProtect(addr, size, PAGE_READWRITE, &dwOldFlag);
        WriteProcessMemory(GetCurrentProcess(), addr, code, size, NULL);
        VirtualProtect(addr, size, dwOldFlag, &dwTempFlag);
    }
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pszCmdLine, int) {
    SetUnhandledExceptionFilter(MyUnhandledExceptionFilter);

    ULONG_PTR token;
    GdiplusStartupInput gsi;
    GdiplusStartup(&token, &gsi, 0);

    BDWinApp::SetAppInstance(hInstance);
    HMENU hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDC_BYTERTCSTART));

    std::vector<RECT> displayList;
    rtcutil::GetDisplayList(displayList);
    RECT display = displayList[0];
    for (auto& screen : displayList) {
        if (display.left < 0 || display.top < 0) {
            display = screen;
            continue;
        }

        if (screen.left < 0 || screen.top < 0) {
            continue;
        }

        if (screen.left < display.left
            ||(screen.left == display.left && screen.top < display.top)) {
            display = screen;
        }
    }

    auto delta_x = 0;
    auto delta_y = 0;
    if (display.right - display.left > 800) {
        delta_x = (display.right - display.left - 800) / 2;
    }

    if (display.bottom - display.top > 584) {
        delta_y = (display.bottom - display.top - 584) / 2;
    }

    bool loginInfo = APPConfig::Instance()->HaveLoginInfo();

    BDUserLoginWnd wnd;
    RECT r = { display.left + delta_x, display.top + delta_y, display.left + delta_x + 800, display.top + delta_y + 584};
    AdjustWindowRect(&r, WS_OVERLAPPEDWINDOW, false);
    BDHMenu menu;
    wnd.Create(NULL, &r, menu, L"veRTC", WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, 0, hMenu);

    if (loginInfo) {
        VerifySms sms;
        sms.create_at = 0;
        sms.login_token = APPConfig::Instance()->GetLoginToken();
        sms.user_id = APPConfig::Instance()->GetLoginUserID();

        auto name = APPConfig::Instance()->GetLoginUserName();
        sms.user_name = rtcutil::ConvertUTF8ToBDString(name);

        wnd.ShowMeetingFrame(sms);
    }
    else {
        wnd.ShowWindow(SW_SHOW);
    }

    BDMessageLoop* loop = BDMessageLoop::GetCurrentLoop();
    loop->Run();

    GdiplusShutdown(token);
    return(0);
}
