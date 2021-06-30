//
//  BDWinApp.h
//
//  Copyright 2020. All rights reserved.
//
//    BDCreateWndData
//    BDWndClassInfo
//    BDWinApp
//    BDMessageFilter
//    BDIdleHandler
//    BDMessageLoop

#pragma once

#include <windows.h>
#include <vector>


/////////////////////////////////////////////////////////////////////////////
// BDCreateWndData - Store this and tid

struct BDCreateWndData
{
    void* m_pThis;
    DWORD m_dwThreadID;
    BDCreateWndData* m_pNext;
};

struct BDWndClassInfo;
struct BDFrameWndClassInfo;


/////////////////////////////////////////////////////////////////////////////
// BDWinApp - HINSTANCE Wrapper

class BDWinApp
{
public:
    static void SetAppInstance(HINSTANCE inst);
    static HINSTANCE GetAppInstance();

    static void SetResInstance(HINSTANCE inst);
    static HINSTANCE GetResInstance();

public:
    static ATOM  RegisterWndClassInfo(BDWndClassInfo* pNewWndClass, WNDPROC* pProc);
    static ATOM* GetRegWindowAtoms(int* nCount);
    static bool  IsAtom(LPCWSTR lpStr);

public:
    static void  AddCreateWndData(BDCreateWndData* pData, void* pObject);
    static void* ExtractCreateWndData();

public:
    static bool IsVista();

private:
    static HINSTANCE m_hInst;
    static HINSTANCE m_hResInst;

public:
    static DWORD m_dwMainThreadID;
};


///////////////////////////////////////////////////////////////////////////////
// BDMessageFilter - Interface for message filter support

class BDMessageFilter
{
public:
    virtual BOOL PreTranslateMessage(MSG* pMsg) = 0;
};


///////////////////////////////////////////////////////////////////////////////
// BDIdleHandler - Interface for idle processing

class BDIdleHandler
{
public:
    virtual BOOL OnIdle() = 0;
};


///////////////////////////////////////////////////////////////////////////////
// BDMessageLoop - message loop implementation

class BDMessageLoop
{
public:
    static BDMessageLoop* GetCurrentLoop();
protected:
    BDMessageLoop();
private:
    static BDMessageLoop* m_pThis;

public:
    std::vector<void*> m_aMsgFilter;
    std::vector<void*> m_aIdleHandler;
    MSG m_msg;

    BOOL AddMessageFilter(BDMessageFilter* pMessageFilter);
    BOOL RemoveMessageFilter(BDMessageFilter* pMessageFilter);
    BOOL AddIdleHandler(BDIdleHandler* pIdleHandler);
    BOOL RemoveIdleHandler(BDIdleHandler* pIdleHandler);
    int  Run();

    static BOOL IsIdleMessage(MSG* pMsg);

    virtual BOOL PreTranslateMessage(MSG* pMsg);
    virtual BOOL OnIdle(int /*nIdleCount*/);
};
