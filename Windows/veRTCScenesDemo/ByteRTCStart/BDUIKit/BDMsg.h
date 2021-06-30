//
//  BDMsg.h
//
//  Copyright 2020. All rights reserved.
//

#pragma once


///////////////////////////////////////////////////////////////////////////////
// Macro for MSG_MAP in this file:
//
// DECLARE_EMPTY_MSG_MAP()
//
// BEGIN_MSG_MAP(theClass)
//   ALT_MSG_MAP(msgMapID)
// END_MSG_MAP()
// 
// use DCrack.h for more Message Marcro and Handlers
// LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
// MESSAGE_HANDLER(msg, func)
// MESSAGE_RANGE_HANDLER(msgFirst, msgLast, func)
//
// LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
// COMMAND_HANDLER(id, code, func)
// COMMAND_ID_HANDLER(id, func)
// COMMAND_CODE_HANDLER(code, func)
// COMMAND_RANGE_HANDLER(idFirst, idLast, func)
// COMMAND_RANGE_CODE_HANDLER(idFirst, idLast, code, func)
//
// LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
// NOTIFY_HANDLER(id, cd, func)
// NOTIFY_CODE_HANDLER(cd, func)
// NOTIFY_RANGE_HANDLER(idFirst, idLast, func)
// NOTIFY_RANGE_CODE_HANDLER(idFirst, idLast, cd, func)
//
// FORWARD_NOTIFICATIONS()
//
// REFLECT_NOTIFICATIONS()
// DEFAULT_REFLECTION_HANDLER()
// REFLECTED_COMMAND_HANDLER(id, code, func)
// REFLECTED_COMMAND_ID_HANDLER(id, func)
// REFLECTED_COMMAND_CODE_HANDLER(code, func)
// REFLECTED_COMMAND_RANGE_HANDLER(idFirst, idLast, func)
// REFLECTED_COMMAND_RANGE_CODE_HANDLER(idFirst, idLast, code, func)
//
// REFLECTED_NOTIFY_HANDLER(id, cd, func)
// REFLECTED_NOTIFY_ID_HANDLER(id, func)
// REFLECTED_NOTIFY_CODE_HANDLER(cd, func)
// REFLECTED_NOTIFY_RANGE_HANDLER(idFirst, idLast, func)
// REFLECTED_NOTIFY_RANGE_CODE_HANDLER(idFirst, idLast, cd, func)
//
// CHAIN_MSG_MAP(theChainClass)
// CHAIN_MSG_MAP_MEMBER(theChainMember)
// CHAIN_MSG_MAP_ALT(theChainClass, msgMapID)
// CHAIN_MSG_MAP_ALT_MEMBER(theChainMember, msgMapID)
// CHAIN_MSG_MAP_DYNAMIC(dynaChainID)
// CHAIN_COMMAND_DYNAMIC(dynaChainID)
// 
// Classes in this file:
// class BDMSG 


/////////////////////////////////////////////////////////////////////////////
// Message map
//
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
//
//  Example:
//  BEGIN_MSG_MAP(BDxxxWindow)
//       MESSAGE_HANDLER(WM_PAINT, OnPaint)
//       COMMAND_HANDLER(BDUID_CLISTBOX, LBN_SELCHANGE, OnCListNotify)
//       COMMAND_HANDLER(BDUID_TLISTBOX, LBN_SELCHANGE, OnTListNotify)
//       NOTIFY_ID_HANDLER(BDUID_SLISTBOX, OnSListNotify)
//       COMMAND_ID_HANDLER(BDUID_EDIT, OnClickEdit)
//  END_MSG_MAP()
// 

#define DECLARE_EMPTY_MSG_MAP() \
public: \
    BOOL ProcessWindowMessage(_In_ HWND, _In_ UINT, _In_ WPARAM, _In_ LPARAM, _Inout_ LRESULT&, _In_ DWORD = 0) \
{ \
    return FALSE; \
}

#define BEGIN_MSG_MAP(theClass) \
public: \
    BOOL ProcessWindowMessage(HWND hWnd, UINT uMsg, WPARAM wParam,\
    LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID = 0) \
{ \
    BOOL bHandled = TRUE; \
    (hWnd); \
    (uMsg); \
    (wParam); \
    (lParam); \
    (lResult); \
    (bHandled); \
    switch(dwMsgMapID) \
{ \
    case 0:

#define ALT_MSG_MAP(msgMapID) \
    break; \
    case msgMapID:

#define END_MSG_MAP() \
    break; \
    default: \
    printf("Invalid message map ID (%i)\n", dwMsgMapID); \
    assert(FALSE); \
    break; \
} \
    return FALSE; \
}

#define MESSAGE_HANDLER(msg, func) \
    if(uMsg == msg) \
{ \
    bHandled = TRUE; \
    lResult = func(uMsg, wParam, lParam, bHandled); \
    if(bHandled) \
    return TRUE; \
}

#define MESSAGE_RANGE_HANDLER(msgFirst, msgLast, func) \
    if(uMsg >= msgFirst && uMsg <= msgLast) \
{ \
    bHandled = TRUE; \
    lResult = func(uMsg, wParam, lParam, bHandled); \
    if(bHandled) \
    return TRUE; \
}

#define COMMAND_HANDLER(id, code, func) \
    if(uMsg == WM_COMMAND && id == LOWORD(wParam) && code == HIWORD(wParam)) \
{ \
    bHandled = TRUE; \
    lResult = func(HIWORD(wParam), LOWORD(wParam), (HWND)lParam, bHandled); \
    if(bHandled) \
    return TRUE; \
}

#define COMMAND_ID_HANDLER(id, func) \
    if(uMsg == WM_COMMAND && id == LOWORD(wParam)) \
{ \
    bHandled = TRUE; \
    lResult = func(HIWORD(wParam), LOWORD(wParam), (HWND)lParam, bHandled); \
    if(bHandled) \
    return TRUE; \
}

#define COMMAND_CODE_HANDLER(code, func) \
    if(uMsg == WM_COMMAND && code == HIWORD(wParam)) \
{ \
    bHandled = TRUE; \
    lResult = func(HIWORD(wParam), LOWORD(wParam), (HWND)lParam, bHandled); \
    if(bHandled) \
    return TRUE; \
}

#define COMMAND_RANGE_HANDLER(idFirst, idLast, func) \
    if(uMsg == WM_COMMAND && LOWORD(wParam) >= idFirst  && LOWORD(wParam) <= idLast) \
{ \
    bHandled = TRUE; \
    lResult = func(HIWORD(wParam), LOWORD(wParam), (HWND)lParam, bHandled); \
    if(bHandled) \
    return TRUE; \
}

#define COMMAND_RANGE_CODE_HANDLER(idFirst, idLast, code, func) \
    if(uMsg == WM_COMMAND && code == HIWORD(wParam) && LOWORD(wParam) >= idFirst  && LOWORD(wParam) <= idLast) \
{ \
    bHandled = TRUE; \
    lResult = func(HIWORD(wParam), LOWORD(wParam), (HWND)lParam, bHandled); \
    if(bHandled) \
    return TRUE; \
}

#define NOTIFY_HANDLER(id, cd, func) \
    if(uMsg == WM_NOTIFY && id == ((LPNMHDR)lParam)->idFrom && cd == ((LPNMHDR)lParam)->code) \
{ \
    bHandled = TRUE; \
    lResult = func((int)wParam, (LPNMHDR)lParam, bHandled); \
    if(bHandled) \
    return TRUE; \
}

#define NOTIFY_ID_HANDLER(id, func) \
    if(uMsg == WM_NOTIFY && id == ((LPNMHDR)lParam)->idFrom) \
{ \
    bHandled = TRUE; \
    lResult = func((int)wParam, (LPNMHDR)lParam, bHandled); \
    if(bHandled) \
    return TRUE; \
}

#define NOTIFY_CODE_HANDLER(cd, func) \
    if(uMsg == WM_NOTIFY && cd == ((LPNMHDR)lParam)->code) \
{ \
    bHandled = TRUE; \
    lResult = func((int)wParam, (LPNMHDR)lParam, bHandled); \
    if(bHandled) \
    return TRUE; \
}

#define NOTIFY_RANGE_HANDLER(idFirst, idLast, func) \
    if(uMsg == WM_NOTIFY && ((LPNMHDR)lParam)->idFrom >= idFirst && ((LPNMHDR)lParam)->idFrom <= idLast) \
{ \
    bHandled = TRUE; \
    lResult = func((int)wParam, (LPNMHDR)lParam, bHandled); \
    if(bHandled) \
    return TRUE; \
}

#define NOTIFY_RANGE_CODE_HANDLER(idFirst, idLast, cd, func) \
    if(uMsg == WM_NOTIFY && cd == ((LPNMHDR)lParam)->code && ((LPNMHDR)lParam)->idFrom >= idFirst && ((LPNMHDR)lParam)->idFrom <= idLast) \
{ \
    bHandled = TRUE; \
    lResult = func((int)wParam, (LPNMHDR)lParam, bHandled); \
    if(bHandled) \
    return TRUE; \
}


/////////////////////////////////////////////////////////////////////////////////////////////
// Message forwarding and reflection macros

#define FORWARD_NOTIFICATIONS() \
    { \
    bHandled = TRUE; \
    lResult = ForwardNotifications(uMsg, wParam, lParam, bHandled); \
    if(bHandled) \
    return TRUE; \
    }

#define REFLECT_NOTIFICATIONS() \
    { \
    bHandled = TRUE; \
    lResult = ReflectNotifications(uMsg, wParam, lParam, bHandled); \
    if(bHandled) \
    return TRUE; \
    }

#define DEFAULT_REFLECTION_HANDLER() \
    if(DefaultReflectionHandler(hWnd, uMsg, wParam, lParam, lResult)) \
    return TRUE;

#define REFLECTED_COMMAND_HANDLER(id, code, func) \
    if(uMsg == OCM_COMMAND && id == LOWORD(wParam) && code == HIWORD(wParam)) \
    { \
    bHandled = TRUE; \
    lResult = func(HIWORD(wParam), LOWORD(wParam), (HWND)lParam, bHandled); \
    if(bHandled) \
    return TRUE; \
    }

#define REFLECTED_COMMAND_ID_HANDLER(id, func) \
    if(uMsg == OCM_COMMAND && id == LOWORD(wParam)) \
    { \
    bHandled = TRUE; \
    lResult = func(HIWORD(wParam), LOWORD(wParam), (HWND)lParam, bHandled); \
    if(bHandled) \
    return TRUE; \
    }

#define REFLECTED_COMMAND_CODE_HANDLER(code, func) \
    if(uMsg == OCM_COMMAND && code == HIWORD(wParam)) \
    { \
    bHandled = TRUE; \
    lResult = func(HIWORD(wParam), LOWORD(wParam), (HWND)lParam, bHandled); \
    if(bHandled) \
    return TRUE; \
    }

#define REFLECTED_COMMAND_RANGE_HANDLER(idFirst, idLast, func) \
    if(uMsg == OCM_COMMAND && LOWORD(wParam) >= idFirst  && LOWORD(wParam) <= idLast) \
    { \
    bHandled = TRUE; \
    lResult = func(HIWORD(wParam), LOWORD(wParam), (HWND)lParam, bHandled); \
    if(bHandled) \
    return TRUE; \
    }

#define REFLECTED_COMMAND_RANGE_CODE_HANDLER(idFirst, idLast, code, func) \
    if(uMsg == OCM_COMMAND && code == HIWORD(wParam) && LOWORD(wParam) >= idFirst  && LOWORD(wParam) <= idLast) \
    { \
    bHandled = TRUE; \
    lResult = func(HIWORD(wParam), LOWORD(wParam), (HWND)lParam, bHandled); \
    if(bHandled) \
    return TRUE; \
    }

#define REFLECTED_NOTIFY_HANDLER(id, cd, func) \
    if(uMsg == OCM_NOTIFY && id == ((LPNMHDR)lParam)->idFrom && cd == ((LPNMHDR)lParam)->code) \
    { \
    bHandled = TRUE; \
    lResult = func((int)wParam, (LPNMHDR)lParam, bHandled); \
    if(bHandled) \
    return TRUE; \
    }

#define REFLECTED_NOTIFY_ID_HANDLER(id, func) \
    if(uMsg == OCM_NOTIFY && id == ((LPNMHDR)lParam)->idFrom) \
    { \
    bHandled = TRUE; \
    lResult = func((int)wParam, (LPNMHDR)lParam, bHandled); \
    if(bHandled) \
    return TRUE; \
    }

#define REFLECTED_NOTIFY_CODE_HANDLER(cd, func) \
    if(uMsg == OCM_NOTIFY && cd == ((LPNMHDR)lParam)->code) \
    { \
    bHandled = TRUE; \
    lResult = func((int)wParam, (LPNMHDR)lParam, bHandled); \
    if(bHandled) \
    return TRUE; \
    }

#define REFLECTED_NOTIFY_RANGE_HANDLER(idFirst, idLast, func) \
    if(uMsg == OCM_NOTIFY && ((LPNMHDR)lParam)->idFrom >= idFirst && ((LPNMHDR)lParam)->idFrom <= idLast) \
    { \
    bHandled = TRUE; \
    lResult = func((int)wParam, (LPNMHDR)lParam, bHandled); \
    if(bHandled) \
    return TRUE; \
    }

#define REFLECTED_NOTIFY_RANGE_CODE_HANDLER(idFirst, idLast, cd, func) \
    if(uMsg == OCM_NOTIFY && cd == ((LPNMHDR)lParam)->code && ((LPNMHDR)lParam)->idFrom >= idFirst && ((LPNMHDR)lParam)->idFrom <= idLast) \
    { \
    bHandled = TRUE; \
    lResult = func((int)wParam, (LPNMHDR)lParam, bHandled); \
    if(bHandled) \
    return TRUE; \
    }


/////////////////////////////////////////////////////////////////////////////////////////////
// Chain Msg
// 将消息映射表链接到基类
// CHAIN_MSG_MAP(CFileHandler<CMainWindow>)
#define CHAIN_MSG_MAP(theChainClass) \
{ \
    if(theChainClass::ProcessWindowMessage(hWnd, uMsg, wParam, lParam, lResult)) \
    return TRUE; \
}

// 将消息映射表链接到成员变量
// CHAIN_MSG_MAP_MEMBER(m_view)
#define CHAIN_MSG_MAP_MEMBER(theChainMember) \
{ \
    if(theChainMember.ProcessWindowMessage(hWnd, uMsg, wParam, lParam, lResult)) \
    return TRUE; \
}

////////////////////////////////////////////////////////////////////////////////////////////
// ALT_MSG_MAP(1)
// 将消息路由到theChainClass类的msgMapID号消息表
// CHAIN_MSG_MAP_ALT(CFileHandler<CMainWindow>, 1)
#define CHAIN_MSG_MAP_ALT(theChainClass, msgMapID) \
{ \
    if(theChainClass::ProcessWindowMessage(hWnd, uMsg, wParam, lParam, lResult, msgMapID)) \
    return TRUE; \
}

// 将消息路由到theChainMember成员的msgMapID号消息表
// CHAIN_MSG_MAP_ALT_MEMBER(m_view, 1)
#define CHAIN_MSG_MAP_ALT_MEMBER(theChainMember, msgMapID) \
{ \
    if(theChainMember.ProcessWindowMessage(hWnd, uMsg, wParam, lParam, lResult, msgMapID)) \
    return TRUE; \
}

/////////////////////////////////////////////////////////////////////////////////////////////
// from DDynamicChain
// 将消息路由至dynaChainID号消息处理器
#define CHAIN_MSG_MAP_DYNAMIC(dynaChainID) \
{ \
    if(DDynamicChain::CallChain(dynaChainID, hWnd, uMsg, wParam, lParam, lResult)) \
    return TRUE; \
}

//用来只路由id=0的WM_COMMAND消息(菜单消息)
#define CHAIN_COMMAND_DYNAMIC(dynaChainID) \
{ \
    if ((uMsg == WM_COMMAND) && (HIWORD(wParam)==0) && \
        DDynamicChain::CallChain(dynaChainID, hWnd, uMsg, wParam, lParam, lResult)) \
    return TRUE; \
}


///////////////////////////////////////////////////////////////////////////////
// BDMSG

struct BDMSG : public MSG
{
public:
    int cbSize;
    BOOL bHandled;

    BDMSG() : cbSize(sizeof(BDMSG)), bHandled(TRUE)
    {
        hwnd = NULL;
        message = 0;
        wParam = 0;
        lParam = 0;
        time = 0;
        pt.x = pt.y = 0;
    }

    BDMSG(HWND hWnd, UINT uMsg, WPARAM wParamIn, LPARAM lParamIn,
        DWORD dwTime, POINT ptIn, BOOL bHandledIn) : cbSize(sizeof(BDMSG)), bHandled(bHandledIn)
    {
        hwnd = hWnd;
        message = uMsg;
        wParam = wParamIn;
        lParam = lParamIn;
        time = dwTime;
        pt = ptIn;
    }

    BDMSG(HWND hWnd, UINT uMsg, WPARAM wParamIn, LPARAM lParamIn, BOOL bHandledIn = TRUE) : cbSize(sizeof(BDMSG)), bHandled(bHandledIn)
    {
        hwnd = hWnd;
        message = uMsg;
        wParam = wParamIn;
        lParam = lParamIn;
        time = 0;
        pt.x = pt.y = 0;
    }

    BDMSG(MSG& msg, BOOL bHandledIn = TRUE) : cbSize(sizeof(BDMSG)), bHandled(bHandledIn)
    {
        hwnd = msg.hwnd;
        message = msg.message;
        wParam = msg.wParam;
        lParam = msg.lParam;
        time = msg.time;
        pt = msg.pt;
    }
};
