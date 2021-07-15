//
//  BDWinApp.cpp
//
//  Copyright 2020. All rights reserved.
//

#include "BDWinApp.h"
#include "BDBase.h"
#include "BDPool.h"
#include <vector>
#include <assert.h>

BDCriticalSection g_csWindowCreate;
BDCreateWndData* g_pCreateWndList;

BDCriticalSection g_csAtom;
std::vector<ATOM> g_arrAtoms;
BDPool pool;

///////////////////////////////////////////////////////////////////////////////////////
// BDWinApp

HINSTANCE BDWinApp::m_hInst;
HINSTANCE BDWinApp::m_hResInst;
DWORD BDWinApp::m_dwMainThreadID;

void BDWinApp::SetAppInstance(HINSTANCE inst)
{
    m_hInst = inst;
    m_hResInst = inst;
}

HINSTANCE BDWinApp::GetAppInstance()
{
    return m_hInst;
}

void BDWinApp::SetResInstance(HINSTANCE inst)
{
    m_hResInst = inst;
}

HINSTANCE BDWinApp::GetResInstance()
{
    return m_hResInst;
}

ATOM BDWinApp::RegisterWndClassInfo(BDWndClassInfo* pNewWndClass, WNDPROC* pProc)
{
    if (pNewWndClass == NULL || pProc == NULL)
    {
        return 0;
    }

    if (pNewWndClass->m_atom == 0)
    {
        if (pNewWndClass->m_lpszOrigName != NULL)
        {
            WNDCLASSEXW wc = {};
            wc.cbSize = sizeof(WNDCLASSEXW);
            if (!::GetClassInfoExW(NULL, pNewWndClass->m_lpszOrigName, &wc))
            {
                if (!::GetClassInfoExW(BDWinApp::GetAppInstance(), pNewWndClass->m_lpszOrigName, &wc))
                {
                    return 0;
                }
            }
            LPCWSTR lpsz = pNewWndClass->m_wc.lpszClassName;
            WNDPROC proc = pNewWndClass->m_wc.lpfnWndProc;
            pNewWndClass->m_wc = wc;
            pNewWndClass->m_wc.lpszClassName = lpsz;                    //Restore the ClassName and proc
            pNewWndClass->m_wc.lpfnWndProc = proc;
            pNewWndClass->pWndProc = pNewWndClass->m_wc.lpfnWndProc;    //Save the WndProc
        }

        if (pNewWndClass->m_wc.lpszClassName == NULL)
        {
            return 0;                //We must define a new window class name
        }

        pNewWndClass->m_wc.hInstance = BDWinApp::GetAppInstance();
        pNewWndClass->m_wc.style &= ~CS_GLOBALCLASS;
        
        if (!(pNewWndClass->m_wc.hCursor))
        {
            pNewWndClass->m_wc.hCursor = ::LoadCursor(NULL, IDC_ARROW);            //Set the Default values for WNDCLASSEX
        }

        WNDCLASSEXW wcTemp = {};
        wcTemp.cbSize = sizeof(wcTemp);
        pNewWndClass->m_atom = static_cast<ATOM>(::GetClassInfoExW(pNewWndClass->m_wc.hInstance, pNewWndClass->m_wc.lpszClassName, &wcTemp));
        if (pNewWndClass->m_atom == 0)
        {
            ATOM atom = ::RegisterClassExW(&pNewWndClass->m_wc);
            if (atom != 0)
            {
                pNewWndClass->m_atom = atom;            //Save the ATOM
                
                //Add to Global Arrays
                g_csAtom.Enter();
                g_arrAtoms.push_back(atom);
                g_csAtom.Leave();
            }
        }
    }

    //if we subclass it , return the old proc for parent
    if (pNewWndClass->m_lpszOrigName != NULL)
    {
        assert(pProc != NULL);
        assert(pNewWndClass->pWndProc != NULL);
        *pProc = pNewWndClass->pWndProc;
    }
    return pNewWndClass->m_atom;
}

ATOM* BDWinApp::GetRegWindowAtoms(int* nCount)
{
    if (nCount) *nCount = g_arrAtoms.size();
    return (ATOM*)g_arrAtoms.data();
}

bool BDWinApp::IsAtom(LPCWSTR lpstr)
{
    DWORD nValue = (DWORD)(HANDLE)lpstr;
    if (nValue <= 65535) return true;
    return false;
}

void BDWinApp::AddCreateWndData(BDCreateWndData* pData, void* pObject)
{
    if (pData == NULL) return;

    //Set this and tid
    pData->m_pThis = pObject;
    pData->m_dwThreadID = ::GetCurrentThreadId();

    //Insert at head
    g_csWindowCreate.Enter();
    pData->m_pNext = g_pCreateWndList;
    g_pCreateWndList = pData;
    g_csWindowCreate.Leave();
}

void* BDWinApp::ExtractCreateWndData()
{
    void* pv = NULL;
    g_csWindowCreate.Enter();

    BDCreateWndData* pEntry = g_pCreateWndList;
    if (pEntry != NULL)
    {
        //Search for tid
        DWORD dwThreadID = ::GetCurrentThreadId();
        BDCreateWndData* pPrev = NULL;
        while (pEntry != NULL)
        {
            if (pEntry->m_dwThreadID == dwThreadID)
            {
                if (pPrev == NULL)
                    g_pCreateWndList = pEntry->m_pNext;
                else
                    pPrev->m_pNext = pEntry->m_pNext;
                pv = pEntry->m_pThis;
                break;
            }
            pPrev = pEntry;
            pEntry = pEntry->m_pNext;
        }
    }
    g_csWindowCreate.Leave();
    return pv;
}

bool BDWinApp::IsVista()
{
    return true;
}


///////////////////////////////////////////////////////////////////////////////////////
// BDMessageLoop

BDMessageLoop* BDMessageLoop::m_pThis = NULL;

BDMessageLoop* BDMessageLoop::GetCurrentLoop()
{
    if (m_pThis == NULL)
    {
        m_pThis = new BDMessageLoop();
    }
    return m_pThis;
}

BDMessageLoop::BDMessageLoop()
{
    m_msg = {};
}

BOOL BDMessageLoop::AddMessageFilter(BDMessageFilter* pMessageFilter)
{
    m_aMsgFilter.push_back(pMessageFilter);
    return TRUE;
}

BOOL BDMessageLoop::RemoveMessageFilter(BDMessageFilter* pMessageFilter)
{
    //m_aMsgFilter.erase(pMessageFilter);
    return TRUE;
}

BOOL BDMessageLoop::AddIdleHandler(BDIdleHandler* pIdleHandler)
{
    m_aIdleHandler.push_back(pIdleHandler);
    return TRUE;
}

BOOL BDMessageLoop::RemoveIdleHandler(BDIdleHandler* pIdleHandler)
{
    //return m_aIdleHandler.erase(pIdleHandler);
    return TRUE;
}

void SetTabFocus(HWND hChildWnd)
{
    HWND hwndFirst = ::GetParent(hChildWnd);

    if (hwndFirst)
    {
        BOOL bFound = FALSE;
        HWND hwndNext = NULL;
        HWND FirstChild = NULL;

        while (hwndNext = ::FindWindowEx(hwndFirst, hwndNext, NULL, NULL))
        {

            DWORD dwStyle = ::GetWindowLong(hwndNext, GWL_STYLE);

            if ((dwStyle & WS_TABSTOP) && (dwStyle & WS_VISIBLE) && !(dwStyle & WS_DISABLED))
            {
                if (!bFound)
                {
                    if (FirstChild == NULL) FirstChild = hwndNext;

                    if (GetFocus() == hwndNext)
                    {
                        bFound = TRUE;
                    }

                }
                else {
                    bFound = FALSE;
                    ::SetFocus(hwndNext);
                    break;
                }

            }

        }

        if (bFound) ::SetFocus(FirstChild);

    }
}


int BDMessageLoop::Run()
{
    BOOL bDoIdle = TRUE;
    int nIdleCount = 0;
    BOOL bRet;

    for(;;)
    {
        while(bDoIdle && !::PeekMessage(&m_msg, NULL, 0, 0, PM_NOREMOVE))
        {
            if(!OnIdle(nIdleCount++))
                bDoIdle = FALSE;
        }

        bRet = ::GetMessage(&m_msg, NULL, 0, 0);

        if(bRet == -1)
        {
            continue;
        }
        else if(!bRet)
        {
            break;
        }

        if(!PreTranslateMessage(&m_msg))
        {
            if (m_msg.message == WM_KEYDOWN && m_msg.wParam == VK_TAB)
            {
                ::SetTabFocus(m_msg.hwnd);
            }

            ::TranslateMessage(&m_msg);
            ::DispatchMessage(&m_msg);
        }

        if(IsIdleMessage(&m_msg))
        {
            bDoIdle = TRUE;
            nIdleCount = 0;
        }
    }

    return (int)m_msg.wParam;
}

BOOL BDMessageLoop::IsIdleMessage(MSG* pMsg)
{
    // These messages should NOT cause idle processing
    switch(pMsg->message)
    {
    case WM_MOUSEMOVE:
    case WM_NCMOUSEMOVE:
    case WM_PAINT:
    case 0x0118:    // WM_SYSTIMER (caret blink)
        return FALSE;
    }

    return TRUE;
}

BOOL BDMessageLoop::PreTranslateMessage(MSG* pMsg)
{
    int nCount = (int)(m_aMsgFilter.size() - 1);
    for(int i = nCount; i >= 0; i--)
    {
        BDMessageFilter* pMessageFilter = (BDMessageFilter*)m_aMsgFilter[i];
        if(pMessageFilter != NULL && pMessageFilter->PreTranslateMessage(pMsg))
            return TRUE;
    }
    return FALSE;   // not translated
}

BOOL BDMessageLoop::OnIdle(int /*nIdleCount*/)
{
    int nCount = (int)m_aIdleHandler.size();
    for(int i = 0; i < nCount; i++)
    {
        BDIdleHandler* pIdleHandler = (BDIdleHandler*)m_aIdleHandler[i];
        if (pIdleHandler != NULL)
        {
            pIdleHandler->OnIdle();
        }
    }
    return FALSE;   // don't continue
}
