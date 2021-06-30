//
//  BDBase.h
//
//  Copyright 2020. All rights reserved.
//

#pragma once

#include <windows.h>

///////////////////////////////////////////////////////////////////////////////
// Classes in this file:
//
// BDPRect - LPRECT wrapper
// BDHMenu - HMENU or ID wrapper
// BDResStr - LPCWSTR or ResID wrapper
// BDCriticalSection - CRITICAL_SECTION wrapper
// BDSRWLock - SRWLOCK wrapper
// struct BDWndClassInfo BDFrameWndClassInfo
// 



/////////////////////////////////////////////////////////////////////////////
// BDPRect 

class BDPRect
{
public:
    BDPRect() { m_lpRect = NULL; }
    BDPRect(LPRECT lpRect) : m_lpRect(lpRect)
    {
    }
    BDPRect(RECT& rc) : m_lpRect(&rc)
    {
    }
    LPRECT m_lpRect;
};


/////////////////////////////////////////////////////////////////////////////
// BDHMenu 

class BDHMenu
{
public:
    BDHMenu() { m_hMenu = NULL; }
    BDHMenu(HMENU hMenu) : m_hMenu(hMenu)
    {
    }
    BDHMenu(UINT nID) : m_hMenu((HMENU)(UINT_PTR)nID)
    {
    }
    UINT ToMenuID()
    {
        return (UINT)(SIZE_T)(int*)m_hMenu;
    }

public:
    HMENU m_hMenu;

public:
    static bool IsMenuID(HMENU menu)
    {
        DWORD nValue = (DWORD)(HANDLE)menu;
        if (nValue <= 65535) return true;
        return false;
    }
};


/////////////////////////////////////////////////////////////////////////////
// BDResStr 

// If the high-order word of the lpName or lpType parameter is zero, the low-order word specifies the integer identifier of the name or type of the given resource. 
// Otherwise, those parameters are long pointers to null-terminated strings. 
// If the first character of the string is a pound sign (#), the remaining characters represent a decimal number that specifies the integer identifier of the resource's name or type. 
// For example, the string "#258" represents the integer identifier 258. 

class BDResStr
{
public:
    BDResStr() { m_lpstr = NULL; }
    BDResStr(LPCWSTR lpString) : m_lpstr(lpString)
    {
    }
    BDResStr(UINT nID) : m_lpstr(MAKEINTRESOURCE(nID))
    {
    }
    UINT ToResID()
    {
        return (UINT)(SIZE_T)(int*)m_lpstr;
    }

public:
    LPCWSTR m_lpstr;

public:
    static bool IsResID(LPCWSTR lpstr)
    {
        DWORD nValue = (DWORD)(HANDLE)lpstr;
        if (nValue <= 65535) return true;
        return false;
    }
};


/////////////////////////////////////////////////////////////////////////////
// BDCriticalSection 

class BDCriticalSection
{
public:
    BDCriticalSection() { Init(); }
    ~BDCriticalSection() { UnInit(); }

    void Init()
    {
        ::InitializeCriticalSection(&m_cs);
    }

    BOOL InitWithSpinCount(DWORD dwSpinCount = 4000)
    {
        return ::InitializeCriticalSectionAndSpinCount(&m_cs, dwSpinCount);
    }

    DWORD SetSpinCount(DWORD dwSpinCount)
    {
        return ::SetCriticalSectionSpinCount(&m_cs, dwSpinCount);
    }

    void UnInit()
    {
        ::DeleteCriticalSection(&m_cs);
    }

    BOOL TryEnter()
    {
        return ::TryEnterCriticalSection(&m_cs);
    }

    void Enter()
    {
        ::EnterCriticalSection(&m_cs);
    }

    void Leave()
    {
        ::LeaveCriticalSection(&m_cs);
    }

private:
    CRITICAL_SECTION m_cs;
};


/////////////////////////////////////////////////////////////////////////////
// BDSRWLock 

class BDSRWLock
{
public:
    void Init()
    {
        ::InitializeSRWLock(&m_lock);
    }

    void AcquireExclusive()
    {
        ::AcquireSRWLockExclusive(&m_lock);
    }

    void ReleaseExclusive()
    {
        ::ReleaseSRWLockExclusive(&m_lock);
    }

    void AcquireShared()
    {
        ::AcquireSRWLockShared(&m_lock);
    }

    void ReleaseShared()
    {
        ::ReleaseSRWLockShared(&m_lock);
    }

private:
    SRWLOCK m_lock;
};


/////////////////////////////////////////////////////////////////////////////
// BDWndClassInfo - Manages Windows class information - Always Unicode

struct BDWndClassInfo
{
    WNDCLASSEXW m_wc;        //[in] WNDCLASSEX
    LPCWSTR m_lpszOrigName;    //[in] Super Class Name
    WNDPROC pWndProc;        //[out] Save the Old pWndProc 
    ATOM m_atom;            //[out] >0 if RegSuccess
};

