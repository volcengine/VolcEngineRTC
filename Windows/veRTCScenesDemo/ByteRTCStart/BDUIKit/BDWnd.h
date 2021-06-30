//
//  BDWnd.h
//
//  Copyright 2020. All rights reserved.
//

#pragma once

#include "BDBase.h"
#include "BDThunk.h"
#include "BDMsg.h"
#include "BDMisc.h"
#include <assert.h>
#include <vector>
#include <Olectl.h>    //for OCM__BASE


///////////////////////////////////////////////////////////////////////////////
// Classes in this file:
//
// DECLARE_BDWND_CLASS(WndClassName)
// DECLARE_BDWND_CLASS2(WndClassName, EnclosingClass)
// DECLARE_BDWND_CLASS_EX(WndClassName, style, bkgnd)
// DECLARE_BDWND_CLASS_EX2(WndClassName, EnclosingClass, style, bkgnd)
// DECLARE_BDWND_SUPERCLASS(WndClassName, OrigWndClassName)
// DECLARE_BDWND_SUPERCLASS2(WndClassName, EnclosingClass, OrigWndClassName)
//
// BDWnd - HWND Wrapper
// BDWinTraits - Window Style and ExStyle Wrapper
//
// BDMsgHandler - Pure Virtual ProcessWindowMessage Interface
// BDWndImplRoot<T> - Root for MsgForward Wrapper
// BDWndImplBaseT<T,Trait=BDControlWinTraits> - WndProc and Style Wrapper  StartWindowProc
// BDWndImplBase = BDWndImplBaseT<BDWnd>
// BDWndImpl<T,TBase=BDWnd,Trait=DControlWinTraits> - Register + Create Wrapper
// 
// BDDynamicChain
//
// BDContainedWindow<T,Trait> 
// BDContainedWindow


//////////////////////////////////////////////////////////////////////////////
// Class Styles
// CS_BYTEALIGNCLIENT  Aligns the window's client area on a byte boundary (in the x direction).
// CS_BYTEALIGNWINDOW  Aligns the window on a byte boundary (in the x direction). 
// CS_CLASSDC  Allocates one device context to be shared by all windows in the class.
// CS_DBLCLKS  Sends a double-click message to the window procedure when the user double-clicks the mouse while the cursor is within a window belonging to the class. 
// CS_DROPSHADOW  Windows XP: Enables the drop shadow effect on a window.
// CS_GLOBALCLASS  Specifies that the window class is an application global class. in dll and can use in every process.
// CS_HREDRAW  Redraws the entire window if a movement or size adjustment changes the width of the client area.
// CS_VREDRAW  Redraws the entire window if a movement or size adjustment changes the height of the client area.
// CS_NOCLOSE  Disables Close on the window menu.
// CS_OWNDC  Allocates a unique device context for each window in the class.
// CS_PARENTDC  Sets the clipping rectangle of the child window to that of the parent window so that the child can draw on the parent. Specifying CS_PARENTDC enhances an application's performance. 
// CS_SAVEBITS  Saves, as a bitmap, the portion of the screen image obscured by a window of this class.

#define BD_CS_NORMALFRAME        CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS|CS_OWNDC

//Example:
//public:
//    DECLARE_BDWND_CLASS(L"BDHyperLink")

#ifndef DECLARE_BDWND_CLASS
#define DECLARE_BDWND_CLASS(WndClassName) \
static BDWndClassInfo& GetWndClassInfo() \
{ \
    static BDWndClassInfo wc = \
    { \
        { sizeof(WNDCLASSEX), BD_CS_NORMALFRAME, BDWndImplBaseT::StartWindowProc, \
        0, 0, NULL, NULL, NULL, (HBRUSH)(COLOR_WINDOW+1), NULL, WndClassName, NULL }, \
        NULL, NULL, 0 \
    }; \
    return wc; \
}
#endif

#ifndef DECLARE_BDWND_CLASS2
#define DECLARE_BDWND_CLASS2(WndClassName, EnclosingClass) \
static BDWndClassInfo& GetWndClassInfo() \
{ \
    static BDWndClassInfo wc = \
    { \
        { sizeof(WNDCLASSEX), BD_CS_NORMALFRAME, EnclosingClass::StartWindowProc, \
          0, 0, NULL, NULL, NULL, (HBRUSH)(COLOR_WINDOW+1), NULL, WndClassName, NULL }, \
        NULL, NULL, 0\
    }; \
    return wc; \
}
#endif

#ifndef DECLARE_BDWND_CLASS_EX
#define DECLARE_BDWND_CLASS_EX(WndClassName, style, bkgnd) \
static BDWndClassInfo& GetWndClassInfo() \
{ \
    static BDWndClassInfo wc = \
    { \
        { sizeof(WNDCLASSEX), style, StartWindowProc, \
        0, 0, NULL, NULL, NULL, (HBRUSH)(bkgnd+1), NULL, WndClassName, NULL }, \
        NULL, NULL, 0 \
    }; \
    return wc; \
}
#endif

#ifndef DECLARE_BDWND_CLASS_EX2
#define DECLARE_BDWND_CLASS_EX2(WndClassName, EnclosingClass, style, bkgnd) \
static BDWndClassInfo& GetWndClassInfo() \
{ \
    static BDWndClassInfo wc = \
    { \
        { sizeof(WNDCLASSEX), style, EnclosingClass::StartWindowProc, \
          0, 0, NULL, NULL, NULL, (HBRUSH)(bkgnd + 1), NULL, WndClassName, NULL }, \
        NULL, NULL, 0 \
    }; \
    return wc; \
}
#endif

#ifndef DECLARE_BDWND_SUPERCLASS
#define DECLARE_BDWND_SUPERCLASS(WndClassName, OrigWndClassName) \
static BDWndClassInfo& GetWndClassInfo() \
{ \
    static BDWndClassInfo wc = \
    { \
        { sizeof(WNDCLASSEX), 0, StartWindowProc, \
        0, 0, NULL, NULL, NULL, NULL, NULL, WndClassName, NULL }, \
        OrigWndClassName, NULL, 0\
    }; \
    return wc; \
}
#endif

#ifndef DECLARE_BDWND_SUPERCLASS2
#define DECLARE_BDWND_SUPERCLASS2(WndClassName, EnclosingClass, OrigWndClassName) \
static BDWndClassInfo& GetWndClassInfo() \
{ \
    static BDWndClassInfo wc = \
    { \
        { sizeof(WNDCLASSEX), 0, EnclosingClass::StartWindowProc, \
          0, 0, NULL, NULL, NULL, NULL, NULL, WndClassName, NULL }, \
          OrigWndClassName, NULL, 0 \
    }; \
    return wc; \
  }
#endif


///////////////////////////////////////////////////////////////////////////////
// to avoid redefinition problems with class members

#ifdef SetWindowLongPtrA
#undef SetWindowLongPtrA
inline LONG_PTR SetWindowLongPtrA(HWND hWnd, int nIndex, LONG_PTR dwNewLong)
{
    return(::SetWindowLongA(hWnd, nIndex, LONG(dwNewLong)));
}
#endif

#ifdef SetWindowLongPtrW
#undef SetWindowLongPtrW
inline LONG_PTR SetWindowLongPtrW(HWND hWnd, int nIndex, LONG_PTR dwNewLong)
{
    return(::SetWindowLongW(hWnd, nIndex, LONG(dwNewLong)));
}
#endif

#ifdef GetWindowLongPtrA
#undef GetWindowLongPtrA
inline LONG_PTR GetWindowLongPtrA(HWND hWnd, int nIndex)
{
    return(::GetWindowLongA(hWnd, nIndex));
}
#endif

#ifdef GetWindowLongPtrW
#undef GetWindowLongPtrW
inline LONG_PTR GetWindowLongPtrW(HWND hWnd, int nIndex)
{
    return(::GetWindowLongW(hWnd, nIndex));
}
#endif

#ifdef SetClassLongPtrA
#undef SetClassLongPtrA
inline LONG_PTR SetClassLongPtrA(HWND hWnd, int nIndex, LONG_PTR dwNewLong)
{
    return ::SetClassLongA(hWnd, nIndex, LONG(dwNewLong));
}
#endif

#ifdef SetClassLongPtrW
#undef SetClassLongPtrW
inline LONG_PTR SetClassLongPtrW(HWND hWnd, int nIndex, LONG_PTR dwNewLong)
{
    return ::SetClassLongW(hWnd, nIndex, LONG(dwNewLong));
}
#endif

#ifdef GetClassLongPtrA
#undef GetClassLongPtrA
inline LONG_PTR GetClassLongPtrA(HWND hWnd, int nIndex)
{
    return ::GetClassLongA(hWnd, nIndex);
}
#endif

#ifdef GetClassLongPtrW
#undef GetClassLongPtrW
inline LONG_PTR GetClassLongPtrW(HWND hWnd, int nIndex)
{
    return ::GetClassLongW(hWnd, nIndex);
}
#endif


/////////////////////////////////////////////////////////////////////////////
// BDWnd - HWND Wrapper 4B

class BDWnd
{
public:
    BDWnd(HWND hWnd = NULL) : m_hWnd(hWnd)
    {
    }

    BDWnd& operator=(HWND hWnd)
    {
        m_hWnd = hWnd;
        return *this;
    }

    // T::GetWndClassName() should return L"XXX" for WndClassName
    static LPCWSTR GetWndClassName()
    {
        return NULL;
    }

    void Attach(HWND hWndNew)
    {
        assert(m_hWnd == NULL);
        assert((hWndNew == NULL) || ::IsWindow(hWndNew));
        m_hWnd = hWndNew;
    }

    HWND Detach()
    {
        HWND hWnd = m_hWnd;
        m_hWnd = NULL;
        return hWnd;
    }

    HWND Create(LPCWSTR lpstrWndClass, HWND hWndParent, BDPRect rect, BDHMenu MenuOrID, 
        LPCWSTR szWindowName = NULL, DWORD dwStyle = 0, DWORD dwExStyle = 0, LPVOID lpCreateParam = NULL) throw()
    {
        assert(m_hWnd == NULL);

        if(rect.m_lpRect == NULL)
        {
            rect.m_lpRect = &rcDefault;
        }

        m_hWnd = ::CreateWindowEx(dwExStyle, lpstrWndClass, szWindowName, dwStyle, 
            rect.m_lpRect->left, rect.m_lpRect->top, rect.m_lpRect->right - rect.m_lpRect->left, rect.m_lpRect->bottom - rect.m_lpRect->top, 
            hWndParent, MenuOrID.m_hMenu, BDWinApp::GetAppInstance(), lpCreateParam);

        return m_hWnd;
    }

    BOOL DestroyWindow()
    {
        assert(::IsWindow(m_hWnd));

        if(!::DestroyWindow(m_hWnd))
            return FALSE;

        m_hWnd = NULL;
        return TRUE;
    }
    
// Attributes

    operator HWND() const throw()
    {
        return m_hWnd;
    }

    DWORD GetStyle() const throw()
    {
        assert(::IsWindow(m_hWnd));
        return (DWORD)::GetWindowLong(m_hWnd, GWL_STYLE);
    }

    DWORD GetExStyle() const throw()
    {
        assert(::IsWindow(m_hWnd));
        return (DWORD)::GetWindowLong(m_hWnd, GWL_EXSTYLE);
    }

    LONG GetWindowLong(int nIndex) const throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::GetWindowLong(m_hWnd, nIndex);
    }

    LONG_PTR GetWindowLongPtr(int nIndex) const throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::GetWindowLongPtr(m_hWnd, nIndex);
    }

    LONG SetWindowLong(int nIndex, LONG dwNewLong) throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::SetWindowLong(m_hWnd, nIndex, dwNewLong);
    }

    LONG_PTR SetWindowLongPtr(int nIndex, LONG_PTR dwNewLong) throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::SetWindowLongPtr(m_hWnd, nIndex, dwNewLong);
    }

    WORD GetWindowWord(int nIndex) const throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::GetWindowWord(m_hWnd, nIndex);
    }

    WORD SetWindowWord(int nIndex, WORD wNewWord) throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::SetWindowWord(m_hWnd, nIndex, wNewWord);
    }

// Message Functions

    LRESULT SendMessage(UINT message, WPARAM wParam = 0, LPARAM lParam = 0) throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::SendMessage(m_hWnd,message,wParam,lParam);
    }

    BOOL PostMessage(UINT message, WPARAM wParam = 0, LPARAM lParam = 0) throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::PostMessage(m_hWnd,message,wParam,lParam);
    }

    BOOL SendNotifyMessage(UINT message, WPARAM wParam = 0, LPARAM lParam = 0) throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::SendNotifyMessage(m_hWnd, message, wParam, lParam);
    }

// support for C style macros
    static LRESULT SendMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) throw()
    {
        assert(::IsWindow(hWnd));
        return ::SendMessage(hWnd, message, wParam, lParam);
    }

// Window Text Functions

    BOOL SetWindowText(LPCWSTR lpszString) throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::SetWindowText(m_hWnd, lpszString);
    }

    int GetWindowText(LPWSTR lpszStringBuf, int nMaxCount) const throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::GetWindowText(m_hWnd, lpszStringBuf, nMaxCount);
    }

    int GetWindowText(BDString& strText) const
    {
        int nLength;
        LPWSTR pszText;

        nLength = GetWindowTextLength();
        pszText = (LPWSTR)strText.GetBuffer(nLength + 1);
        nLength = GetWindowText(pszText, nLength + 1);
        strText.ReleaseBuffer(nLength);

        return nLength;
    }

    int GetWindowTextLength() const throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::GetWindowTextLength(m_hWnd);
    }

// Font Functions

    void SetFont(HFONT hFont, BOOL bRedraw = TRUE) throw()
    {
        assert(::IsWindow(m_hWnd));
        ::SendMessage(m_hWnd, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(bRedraw, 0));
    }

    HFONT GetFont() const throw()
    {
        assert(::IsWindow(m_hWnd));
        return (HFONT)::SendMessage(m_hWnd, WM_GETFONT, 0, 0);
    }

// Menu Functions (non-child windows only)

    HMENU GetMenu() const throw()
    {
        assert(::IsWindow(m_hWnd));
        return (HMENU)::GetMenu(m_hWnd);
    }

    BOOL SetMenu(HMENU hMenu) throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::SetMenu(m_hWnd, hMenu);
    }

    BOOL DrawMenuBar() throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::DrawMenuBar(m_hWnd);
    }

    HMENU GetSystemMenu(BOOL bRevert) const throw()
    {
        assert(::IsWindow(m_hWnd));
        return (HMENU)::GetSystemMenu(m_hWnd, bRevert);
    }

    BOOL HiliteMenuItem(HMENU hMenu, UINT uItemHilite, UINT uHilite) throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::HiliteMenuItem(m_hWnd, hMenu, uItemHilite, uHilite);
    }

// Window Size and Position Functions

    BOOL IsIconic() const throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::IsIconic(m_hWnd);
    }

    BOOL IsZoomed() const throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::IsZoomed(m_hWnd);
    }

    BOOL MoveWindow(int x, int y, int nWidth, int nHeight, BOOL bRepaint = TRUE) throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::MoveWindow(m_hWnd, x, y, nWidth, nHeight, bRepaint);
    }

    BOOL MoveWindow(LPCRECT lpRect, BOOL bRepaint = TRUE) throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::MoveWindow(m_hWnd, lpRect->left, lpRect->top, lpRect->right - lpRect->left, lpRect->bottom - lpRect->top, bRepaint);
    }

    BOOL SetWindowPos(HWND hWndInsertAfter,
        int x, int y, int cx, int cy, UINT nFlags) throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::SetWindowPos(m_hWnd, hWndInsertAfter, x, y, cx, cy, nFlags);
    }

    BOOL SetWindowPos(HWND hWndInsertAfter, LPCRECT lpRect, UINT nFlags) throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::SetWindowPos(m_hWnd, hWndInsertAfter, lpRect->left, lpRect->top, lpRect->right - lpRect->left, lpRect->bottom - lpRect->top, nFlags);
    }

    UINT ArrangeIconicWindows() throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::ArrangeIconicWindows(m_hWnd);
    }

    BOOL BringWindowToTop() throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::BringWindowToTop(m_hWnd);
    }

    BOOL GetWindowRect(LPRECT lpRect) const throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::GetWindowRect(m_hWnd, lpRect);
    }

    BOOL GetClientRect(LPRECT lpRect) const throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::GetClientRect(m_hWnd, lpRect);
    }

    BOOL GetWindowPlacement(WINDOWPLACEMENT FAR* lpwndpl) const throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::GetWindowPlacement(m_hWnd, lpwndpl);
    }

    BOOL SetWindowPlacement(const WINDOWPLACEMENT FAR* lpwndpl) throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::SetWindowPlacement(m_hWnd, lpwndpl);
    }

// Coordinate Mapping Functions

    BOOL ClientToScreen(LPPOINT lpPoint) const throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::ClientToScreen(m_hWnd, lpPoint);
    }

    BOOL ClientToScreen(LPRECT lpRect) const throw()
    {
        assert(::IsWindow(m_hWnd));
        if(!::ClientToScreen(m_hWnd, (LPPOINT)lpRect))
            return FALSE;
        return ::ClientToScreen(m_hWnd, ((LPPOINT)lpRect)+1);
    }

    BOOL ScreenToClient(LPPOINT lpPoint) const throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::ScreenToClient(m_hWnd, lpPoint);
    }

    BOOL ScreenToClient(LPRECT lpRect) const throw()
    {
        assert(::IsWindow(m_hWnd));
        if(!::ScreenToClient(m_hWnd, (LPPOINT)lpRect))
            return FALSE;
        return ::ScreenToClient(m_hWnd, ((LPPOINT)lpRect)+1);
    }

    int MapWindowPoints(HWND hWndTo, LPPOINT lpPoint, UINT nCount) const throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::MapWindowPoints(m_hWnd, hWndTo, lpPoint, nCount);
    }

    int MapWindowPoints(HWND hWndTo, LPRECT lpRect) const throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::MapWindowPoints(m_hWnd, hWndTo, (LPPOINT)lpRect, 2);
    }

// Update and Painting Functions

    HDC BeginPaint(LPPAINTSTRUCT lpPaint) throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::BeginPaint(m_hWnd, lpPaint);
    }

    void EndPaint(LPPAINTSTRUCT lpPaint) throw()
    {
        assert(::IsWindow(m_hWnd));
        ::EndPaint(m_hWnd, lpPaint);
    }

    HDC GetDC() throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::GetDC(m_hWnd);
    }

    HDC GetWindowDC() throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::GetWindowDC(m_hWnd);
    }

    int ReleaseDC(HDC hDC) throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::ReleaseDC(m_hWnd, hDC);
    }

    void Print(HDC hDC, DWORD dwFlags) const throw()
    {
        assert(::IsWindow(m_hWnd));
        ::SendMessage(m_hWnd, WM_PRINT, (WPARAM)hDC, dwFlags);
    }

    void PrintClient(HDC hDC, DWORD dwFlags) const throw()
    {
        assert(::IsWindow(m_hWnd));
        ::SendMessage(m_hWnd, WM_PRINTCLIENT, (WPARAM)hDC, dwFlags);
    }

    BOOL UpdateWindow() throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::UpdateWindow(m_hWnd);
    }

    void SetRedraw(BOOL bRedraw = TRUE) throw()
    {
        assert(::IsWindow(m_hWnd));
        ::SendMessage(m_hWnd, WM_SETREDRAW, (WPARAM)bRedraw, 0);
    }

    BOOL GetUpdateRect(LPRECT lpRect, BOOL bErase = FALSE) throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::GetUpdateRect(m_hWnd, lpRect, bErase);
    }

    int GetUpdateRgn(HRGN hRgn, BOOL bErase = FALSE) throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::GetUpdateRgn(m_hWnd, hRgn, bErase);
    }

    BOOL Invalidate(BOOL bErase = TRUE) throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::InvalidateRect(m_hWnd, NULL, bErase);
    }

    BOOL InvalidateRect(LPCRECT lpRect, BOOL bErase = TRUE) throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::InvalidateRect(m_hWnd, lpRect, bErase);
    }

    BOOL ValidateRect(LPCRECT lpRect) throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::ValidateRect(m_hWnd, lpRect);
    }

    void InvalidateRgn(HRGN hRgn, BOOL bErase = TRUE) throw()
    {
        assert(::IsWindow(m_hWnd));
        ::InvalidateRgn(m_hWnd, hRgn, bErase);
    }

    BOOL ValidateRgn(HRGN hRgn) throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::ValidateRgn(m_hWnd, hRgn);
    }

    BOOL ShowWindow(int nCmdShow) throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::ShowWindow(m_hWnd, nCmdShow);
    }

    BOOL IsWindowVisible() const throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::IsWindowVisible(m_hWnd);
    }

    BOOL ShowOwnedPopups(BOOL bShow = TRUE) throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::ShowOwnedPopups(m_hWnd, bShow);
    }

    HDC GetDCEx(HRGN hRgnClip, DWORD flags) throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::GetDCEx(m_hWnd, hRgnClip, flags);
    }

    BOOL LockWindowUpdate(BOOL bLock = TRUE) throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::LockWindowUpdate(bLock ? m_hWnd : NULL);
    }

    BOOL RedrawWindow(LPCRECT lpRectUpdate = NULL, HRGN hRgnUpdate = NULL,
            UINT flags = RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE) throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::RedrawWindow(m_hWnd, lpRectUpdate, hRgnUpdate, flags);
    }

// Timer Functions

    UINT_PTR SetTimer(UINT_PTR nIDEvent, UINT nElapse,
            void (CALLBACK* lpfnTimer)(HWND, UINT, UINT_PTR, DWORD) = NULL) throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::SetTimer(m_hWnd, nIDEvent, nElapse, (TIMERPROC)lpfnTimer);
    }

    BOOL KillTimer(UINT_PTR nIDEvent) throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::KillTimer(m_hWnd, nIDEvent);
    }

// Window State Functions

    BOOL IsWindowEnabled() const throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::IsWindowEnabled(m_hWnd);
    }

    BOOL EnableWindow(BOOL bEnable = TRUE) throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::EnableWindow(m_hWnd, bEnable);
    }

    HWND SetActiveWindow() throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::SetActiveWindow(m_hWnd);
    }

    HWND SetCapture() throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::SetCapture(m_hWnd);
    }

    HWND SetFocus() throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::SetFocus(m_hWnd);
    }

// Dialog-Box Item Functions

    BOOL CheckDlgButton(int nIDButton, UINT nCheck) throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::CheckDlgButton(m_hWnd, nIDButton, nCheck);
    }

    BOOL CheckRadioButton(int nIDFirstButton, int nIDLastButton,
        int nIDCheckButton) throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::CheckRadioButton(m_hWnd, nIDFirstButton, nIDLastButton, nIDCheckButton);
    }

    int DlgDirList(LPWSTR lpPathSpec, int nIDListBox, int nIDStaticPath, UINT nFileType) throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::DlgDirList(m_hWnd, lpPathSpec, nIDListBox, nIDStaticPath, nFileType);
    }

    int DlgDirListComboBox(LPWSTR lpPathSpec, int nIDComboBox, int nIDStaticPath, UINT nFileType) throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::DlgDirListComboBox(m_hWnd, lpPathSpec, nIDComboBox, nIDStaticPath, nFileType);
    }

    BOOL DlgDirSelect(LPWSTR lpString, int nCount, int nIDListBox) throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::DlgDirSelectEx(m_hWnd, lpString, nCount, nIDListBox);
    }

    BOOL DlgDirSelectComboBox(LPWSTR lpString, int nCount, int nIDComboBox) throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::DlgDirSelectComboBoxEx(m_hWnd, lpString, nCount, nIDComboBox);
    }

    UINT GetDlgItemInt(int nID, BOOL* lpTrans = NULL, BOOL bSigned = TRUE) const throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::GetDlgItemInt(m_hWnd, nID, lpTrans, bSigned);
    }

    UINT GetDlgItemText(int nID, LPWSTR lpStr, int nMaxCount) const throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::GetDlgItemText(m_hWnd, nID, lpStr, nMaxCount);
    }

    UINT GetDlgItemText(int nID, BDString& strText) const
    {
        assert(::IsWindow(m_hWnd));

        HWND hItem = GetDlgItem(nID);
        if (hItem != NULL)
        {
            int nLength;
            LPWSTR pszText;

            nLength = ::GetWindowTextLength(hItem);
            pszText = (LPWSTR)strText.GetBuffer(nLength + 1);
            nLength = ::GetWindowText(hItem, pszText, nLength + 1);
            strText.ReleaseBuffer(nLength);

            return nLength;
        }
        else
        {
            strText.Empty();

            return 0;
        }
    }

    BDWnd GetNextDlgGroupItem(HWND hWndCtl, BOOL bPrevious = FALSE) const throw()
    {
        assert(::IsWindow(m_hWnd));
        return BDWnd(::GetNextDlgGroupItem(m_hWnd, hWndCtl, bPrevious));
    }

    BDWnd GetNextDlgTabItem(HWND hWndCtl, BOOL bPrevious = FALSE) const throw()
    {
        assert(::IsWindow(m_hWnd));
        return BDWnd(::GetNextDlgTabItem(m_hWnd, hWndCtl, bPrevious));
    }

    UINT IsDlgButtonChecked(int nIDButton) const throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::IsDlgButtonChecked(m_hWnd, nIDButton);
    }

    LRESULT SendDlgItemMessage(int nID, UINT message, WPARAM wParam = 0, LPARAM lParam = 0) throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::SendDlgItemMessage(m_hWnd, nID, message, wParam, lParam);
    }

    BOOL SetDlgItemInt(int nID, UINT nValue, BOOL bSigned = TRUE) throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::SetDlgItemInt(m_hWnd, nID, nValue, bSigned);
    }

    BOOL SetDlgItemText(int nID, LPCWSTR lpszString) throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::SetDlgItemText(m_hWnd, nID, lpszString);
    }

// Scrolling Functions

    int GetScrollPos(_In_ int nBar) const throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::GetScrollPos(m_hWnd, nBar);
    }

    BOOL GetScrollRange(int nBar, LPINT lpMinPos, LPINT lpMaxPos) const throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::GetScrollRange(m_hWnd, nBar, lpMinPos, lpMaxPos);
    }

    BOOL ScrollWindow(int XAmount, int YAmount, const RECT* lpRect, const RECT* lpClipRect)
    {
        assert(::IsWindow(m_hWnd));
        return ::ScrollWindow(m_hWnd, XAmount, YAmount, lpRect, lpClipRect);
    }

    int ScrollWindowEx(int dx, int dy, LPCRECT lpRectScroll, LPCRECT lpRectClip, HRGN hRgnUpdate, LPRECT lpRectUpdate, UINT uFlags) throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::ScrollWindowEx(m_hWnd, dx, dy, lpRectScroll, lpRectClip, hRgnUpdate, lpRectUpdate, uFlags);
    }

    int ScrollWindowEx(int dx, int dy, UINT uFlags, LPCRECT lpRectScroll = NULL,
        LPCRECT lpRectClip = NULL, HRGN hRgnUpdate = NULL, LPRECT lpRectUpdate = NULL) throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::ScrollWindowEx(m_hWnd, dx, dy, lpRectScroll, lpRectClip, hRgnUpdate, lpRectUpdate, uFlags);
    }

    int SetScrollPos(int nBar, int nPos, BOOL bRedraw = TRUE) throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::SetScrollPos(m_hWnd, nBar, nPos, bRedraw);
    }

    BOOL SetScrollRange(int nBar, int nMinPos, int nMaxPos, BOOL bRedraw = TRUE) throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::SetScrollRange(m_hWnd, nBar, nMinPos, nMaxPos, bRedraw);
    }

    BOOL ShowScrollBar(UINT nBar, BOOL bShow = TRUE) throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::ShowScrollBar(m_hWnd, nBar, bShow);
    }

    BOOL EnableScrollBar(UINT uSBFlags, UINT uArrowFlags = ESB_ENABLE_BOTH) throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::EnableScrollBar(m_hWnd, uSBFlags, uArrowFlags);
    }

// Window Access Functions

    BDWnd ChildWindowFromPoint(POINT point) const throw()
    {
        assert(::IsWindow(m_hWnd));
        return BDWnd(::ChildWindowFromPoint(m_hWnd, point));
    }

    BDWnd ChildWindowFromPointEx(POINT point, UINT uFlags) const throw()
    {
        assert(::IsWindow(m_hWnd));
        return BDWnd(::ChildWindowFromPointEx(m_hWnd, point, uFlags));
    }

    BDWnd GetTopWindow() const throw()
    {
        assert(::IsWindow(m_hWnd));
        return BDWnd(::GetTopWindow(m_hWnd));
    }

    BDWnd GetWindow(UINT nCmd) const throw()
    {
        assert(::IsWindow(m_hWnd));
        return BDWnd(::GetWindow(m_hWnd, nCmd));
    }

    BDWnd GetLastActivePopup() const throw()
    {
        assert(::IsWindow(m_hWnd));
        return BDWnd(::GetLastActivePopup(m_hWnd));
    }

    BOOL IsChild(HWND hWnd) const throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::IsChild(m_hWnd, hWnd);
    }

    BDWnd GetParent() const throw()
    {
        assert(::IsWindow(m_hWnd));
        return BDWnd(::GetParent(m_hWnd));
    }

    BDWnd SetParent(HWND hWndNewParent) throw()
    {
        assert(::IsWindow(m_hWnd));
        return BDWnd(::SetParent(m_hWnd, hWndNewParent));
    }

// Window Tree Access

    int GetDlgCtrlID() const throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::GetDlgCtrlID(m_hWnd);
    }

    int SetDlgCtrlID(int nID) throw()
    {
        assert(::IsWindow(m_hWnd));
        return (int)::SetWindowLong(m_hWnd, GWL_ID, nID);
    }

    BDWnd GetDlgItem(int nID) const throw()
    {
        assert(::IsWindow(m_hWnd));
        return BDWnd(::GetDlgItem(m_hWnd, nID));
    }

// Alert Functions

    BOOL FlashWindow(BOOL bInvert) throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::FlashWindow(m_hWnd, bInvert);
    }

    int MessageBox(LPCWSTR lpszText, LPCWSTR lpszCaption = L"", UINT nType = MB_OK) throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::MessageBox(m_hWnd, lpszText, lpszCaption, nType);
    }

// Clipboard Functions

    BOOL ChangeClipboardChain(HWND hWndNewNext) throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::ChangeClipboardChain(m_hWnd, hWndNewNext);
    }

    HWND SetClipboardViewer() throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::SetClipboardViewer(m_hWnd);
    }

    BOOL OpenClipboard() throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::OpenClipboard(m_hWnd);
    }

// Caret Functions

    BOOL CreateCaret(HBITMAP hBitmap, int w, int h) throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::CreateCaret(m_hWnd, hBitmap, w, h);
    }

    BOOL CreateSolidCaret(int nWidth, int nHeight) throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::CreateCaret(m_hWnd, (HBITMAP)0, nWidth, nHeight);
    }

    BOOL CreateGrayCaret(int nWidth, int nHeight) throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::CreateCaret(m_hWnd, (HBITMAP)1, nWidth, nHeight);
    }

    BOOL HideCaret() throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::HideCaret(m_hWnd);
    }

    BOOL ShowCaret() throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::ShowCaret(m_hWnd);
    }

// Drag-Drop Functions

    void DragAcceptFiles(BOOL bAccept = TRUE) throw()
    {
        assert(::IsWindow(m_hWnd)); 
        //::DragAcceptFiles(m_hWnd, bAccept);
    }

// Icon Functions

    HICON SetIcon(HICON hIcon, BOOL bBigIcon = TRUE) throw()
    {
        assert(::IsWindow(m_hWnd));
        return (HICON)::SendMessage(m_hWnd, WM_SETICON, bBigIcon, (LPARAM)hIcon);
    }

    HICON GetIcon(BOOL bBigIcon = TRUE) const throw()
    {
        assert(::IsWindow(m_hWnd));
        return (HICON)::SendMessage(m_hWnd, WM_GETICON, bBigIcon, 0);
    }

// Help Functions

    BOOL WinHelp(LPCWSTR lpszHelp, UINT nCmd = HELP_CONTEXT, DWORD dwData = 0) throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::WinHelp(m_hWnd, lpszHelp, nCmd, dwData);
    }

    BOOL SetWindowContextHelpId(DWORD dwContextHelpId) throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::SetWindowContextHelpId(m_hWnd, dwContextHelpId);
    }

    DWORD GetWindowContextHelpId() const throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::GetWindowContextHelpId(m_hWnd);
    }

// Hot Key Functions

    int SetHotKey(WORD wVirtualKeyCode, WORD wModifiers) throw()
    {
        assert(::IsWindow(m_hWnd));
        return (int)::SendMessage(m_hWnd, WM_SETHOTKEY, MAKEWORD(wVirtualKeyCode, wModifiers), 0);
    }

    DWORD GetHotKey() const throw()
    {
        assert(::IsWindow(m_hWnd));
        return (DWORD)::SendMessage(m_hWnd, WM_GETHOTKEY, 0, 0);
    }

// Misc. Operations

    BOOL GetScrollInfo(int fnBar, LPSCROLLINFO lpsi)
    {
        assert(::IsWindow(m_hWnd));
        return ::GetScrollInfo(m_hWnd, fnBar, lpsi);
    }

    int SetScrollInfo(int fnBar, LPSCROLLINFO lpsi, BOOL fRedraw)
    {
        assert(::IsWindow(m_hWnd));
        return ::SetScrollInfo(m_hWnd, fnBar, lpsi, fRedraw);
    }

    BOOL IsDialogMessage(LPMSG lpMsg) throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::IsDialogMessage(m_hWnd, lpMsg);
    }

    void NextDlgCtrl() const throw()
    {
        assert(::IsWindow(m_hWnd));
        ::SendMessage(m_hWnd, WM_NEXTDLGCTL, 0, 0L);
    }

    void PrevDlgCtrl() const throw()
    {
        assert(::IsWindow(m_hWnd));
        ::SendMessage(m_hWnd, WM_NEXTDLGCTL, 1, 0L);
    }

    void GotoDlgCtrl(HWND hWndCtrl) const throw()
    {
        assert(::IsWindow(m_hWnd));
        ::SendMessage(m_hWnd, WM_NEXTDLGCTL, (WPARAM)hWndCtrl, 1L);
    }

    BOOL ResizeClient(int nWidth, int nHeight, BOOL bRedraw = TRUE) throw()
    {
        assert(::IsWindow(m_hWnd));

        RECT rcWnd;
        if(!GetClientRect(&rcWnd))
            return FALSE;

        if(nWidth != -1)
            rcWnd.right = nWidth;
        if(nHeight != -1)
            rcWnd.bottom = nHeight;

        if(!::AdjustWindowRectEx(&rcWnd, GetStyle(), (!(GetStyle() & WS_CHILD) && (GetMenu() != NULL)), GetExStyle()))
            return FALSE;

        UINT uFlags = SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE;
        if(!bRedraw)
            uFlags |= SWP_NOREDRAW;

        return SetWindowPos(NULL, 0, 0, rcWnd.right - rcWnd.left, rcWnd.bottom - rcWnd.top, uFlags);
    }

    int GetWindowRgn(HRGN hRgn) throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::GetWindowRgn(m_hWnd, hRgn);
    }

    int SetWindowRgn(HRGN hRgn, BOOL bRedraw = FALSE) throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::SetWindowRgn(m_hWnd, hRgn, bRedraw);
    }

    HDWP DeferWindowPos(HDWP hWinPosInfo, HWND hWndInsertAfter,
        int x, int y, int cx, int cy, UINT uFlags) throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::DeferWindowPos(hWinPosInfo, m_hWnd, hWndInsertAfter, x, y, cx, cy, uFlags);
    }

    DWORD GetWindowThreadID() throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::GetWindowThreadProcessId(m_hWnd, NULL);
    }

    DWORD GetWindowProcessID() throw()
    {
        assert(::IsWindow(m_hWnd));
        DWORD dwProcessID;
        ::GetWindowThreadProcessId(m_hWnd, &dwProcessID);
        return dwProcessID;
    }

    BOOL IsWindow() const throw()
    {
        return ::IsWindow(m_hWnd);
    }

    BOOL IsWindowUnicode() const throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::IsWindowUnicode(m_hWnd);
    }

    BOOL IsParentDialog() throw()
    {
        assert(::IsWindow(m_hWnd));
        WCHAR szBuf[8]; // "#32770" + NUL character
        if (GetClassName(GetParent(), szBuf, sizeof(szBuf)/sizeof(szBuf[0])) == 0)
            return FALSE;
        return wcscmp((LPCWSTR)szBuf, (LPCWSTR)L"#32770") == 0;
    }

    BOOL ShowWindowAsync(int nCmdShow) throw()
    {
        assert(::IsWindow(m_hWnd));
        return ::ShowWindowAsync(m_hWnd, nCmdShow);
    }

    BDWnd GetDescendantWindow(int nID) const throw()
    {
        assert(::IsWindow(m_hWnd));

        // GetDlgItem recursive (return first found)
        // breadth-first for 1 level, then depth-first for next level

        // use GetDlgItem since it is a fast USER function
        HWND hWndChild, hWndTmp;
        if((hWndChild = ::GetDlgItem(m_hWnd, nID)) != NULL)
        {
            if(::GetTopWindow(hWndChild) != NULL)
            {
                // children with the same ID as their parent have priority
                BDWnd wnd(hWndChild);
                hWndTmp = wnd.GetDescendantWindow(nID);
                if(hWndTmp != NULL)
                    return BDWnd(hWndTmp);
            }
            return BDWnd(hWndChild);
        }

        // walk each child
        for(hWndChild = ::GetTopWindow(m_hWnd); hWndChild != NULL;
            hWndChild = ::GetNextWindow(hWndChild, GW_HWNDNEXT))
        {
            BDWnd wnd(hWndChild);
            hWndTmp = wnd.GetDescendantWindow(nID);
            if(hWndTmp != NULL)
                return BDWnd(hWndTmp);
        }

        return BDWnd(NULL);    // not found
    }

    void SendMessageToDescendants(UINT message, WPARAM wParam = 0, LPARAM lParam = 0, BOOL bDeep = TRUE) throw()
    {
        for(HWND hWndChild = ::GetTopWindow(m_hWnd); hWndChild != NULL;
            hWndChild = ::GetNextWindow(hWndChild, GW_HWNDNEXT))
        {
            ::SendMessage(hWndChild, message, wParam, lParam);

            if(bDeep && ::GetTopWindow(hWndChild) != NULL)
            {
                // send to child windows after parent
                BDWnd wnd(hWndChild);
                wnd.SendMessageToDescendants(message, wParam, lParam, bDeep);
            }
        }
    }

    BOOL CenterWindow(HWND hWndCenter = NULL) throw()
    {
        assert(::IsWindow(m_hWnd));

        // determine owner window to center against
        DWORD dwStyle = GetStyle();
        if(hWndCenter == NULL)
        {
            if(dwStyle & WS_CHILD)
                hWndCenter = ::GetParent(m_hWnd);
            else
                hWndCenter = ::GetWindow(m_hWnd, GW_OWNER);
        }

        // get coordinates of the window relative to its parent
        RECT rcDlg;
        ::GetWindowRect(m_hWnd, &rcDlg);
        RECT rcArea;
        RECT rcCenter;
        HWND hWndParent;
        if(!(dwStyle & WS_CHILD))
        {
            // don't center against invisible or minimized windows
            if(hWndCenter != NULL)
            {
                DWORD dwStyleCenter = ::GetWindowLong(hWndCenter, GWL_STYLE);
                if(!(dwStyleCenter & WS_VISIBLE) || (dwStyleCenter & WS_MINIMIZE))
                    hWndCenter = NULL;
            }

            // center within screen coordinates
            HMONITOR hMonitor = NULL;
            if(hWndCenter != NULL)
            {
                hMonitor = ::MonitorFromWindow(hWndCenter, MONITOR_DEFAULTTONEAREST);
            }
            else
            {
                hMonitor = ::MonitorFromWindow(m_hWnd, MONITOR_DEFAULTTONEAREST);
            }
            assert(hMonitor != NULL);
            if (!(hMonitor != NULL)) return FALSE;

            MONITORINFO minfo;
            minfo.cbSize = sizeof(MONITORINFO);
            BOOL bResult = ::GetMonitorInfo(hMonitor, &minfo);
            assert(bResult);
            if (!bResult) return FALSE;

            rcArea = minfo.rcWork;
            if(hWndCenter == NULL)
                rcCenter = rcArea;
            else
                ::GetWindowRect(hWndCenter, &rcCenter);
        }
        else
        {
            // center within parent client coordinates
            hWndParent = ::GetParent(m_hWnd);
            assert(::IsWindow(hWndParent));

            ::GetClientRect(hWndParent, &rcArea);
            assert(::IsWindow(hWndCenter));
            ::GetClientRect(hWndCenter, &rcCenter);
            ::MapWindowPoints(hWndCenter, hWndParent, (POINT*)&rcCenter, 2);
        }

        int DlgWidth = rcDlg.right - rcDlg.left;
        int DlgHeight = rcDlg.bottom - rcDlg.top;

        // find dialog's upper left based on rcCenter
        int xLeft = (rcCenter.left + rcCenter.right) / 2 - DlgWidth / 2;
        int yTop = (rcCenter.top + rcCenter.bottom) / 2 - DlgHeight / 2;

        // if the dialog is outside the screen, move it inside
        if(xLeft + DlgWidth > rcArea.right)
            xLeft = rcArea.right - DlgWidth;
        if(xLeft < rcArea.left)
            xLeft = rcArea.left;

        if(yTop + DlgHeight > rcArea.bottom)
            yTop = rcArea.bottom - DlgHeight;
        if(yTop < rcArea.top)
            yTop = rcArea.top;

        // map screen coordinates to child coordinates
        return ::SetWindowPos(m_hWnd, NULL, xLeft, yTop, -1, -1,
            SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
    }

    BOOL ModifyStyle(DWORD dwRemove, DWORD dwAdd, UINT nFlags = 0) throw()
    {
        assert(::IsWindow(m_hWnd));

        DWORD dwStyle = ::GetWindowLong(m_hWnd, GWL_STYLE);
        DWORD dwNewStyle = (dwStyle & ~dwRemove) | dwAdd;
        if(dwStyle == dwNewStyle)
            return FALSE;

        ::SetWindowLong(m_hWnd, GWL_STYLE, dwNewStyle);
        if(nFlags != 0)
        {
            ::SetWindowPos(m_hWnd, NULL, 0, 0, 0, 0,
                SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE | nFlags);
        }

        return TRUE;
    }

    BOOL ModifyStyleEx(DWORD dwRemove, DWORD dwAdd, UINT nFlags = 0) throw()
    {
        assert(::IsWindow(m_hWnd));

        DWORD dwStyle = ::GetWindowLong(m_hWnd, GWL_EXSTYLE);
        DWORD dwNewStyle = (dwStyle & ~dwRemove) | dwAdd;
        if(dwStyle == dwNewStyle)
            return FALSE;

        ::SetWindowLong(m_hWnd, GWL_EXSTYLE, dwNewStyle);
        if(nFlags != 0)
        {
            ::SetWindowPos(m_hWnd, NULL, 0, 0, 0, 0,
                SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE | nFlags);
        }

        return TRUE;
    }

    BDWnd GetTopLevelParent() const throw()
    {
        assert(::IsWindow(m_hWnd));

        HWND hWndParent = m_hWnd;
        HWND hWndTmp;
        while((hWndTmp = ::GetParent(hWndParent)) != NULL)
            hWndParent = hWndTmp;

        return BDWnd(hWndParent);
    }

    BDWnd GetTopLevelWindow() const throw()
    {
        assert(::IsWindow(m_hWnd));

        HWND hWndParent;
        HWND hWndTmp = m_hWnd;

        do
        {
            hWndParent = hWndTmp;
            hWndTmp = (::GetWindowLong(hWndParent, GWL_STYLE) & WS_CHILD) ? ::GetParent(hWndParent) : ::GetWindow(hWndParent, GW_OWNER);
        }
        while(hWndTmp != NULL);

        return BDWnd(hWndParent);
    }

//Extensions

    BOOL PrintWindow(HDC hDC, UINT uFlags = 0)
    {
        assert(::IsWindow(m_hWnd));
        return ::PrintWindow(m_hWnd, hDC, uFlags);
    }

    BOOL DragDetect(POINT pt)
    {
        assert(::IsWindow(m_hWnd));
        return ::DragDetect(m_hWnd, pt);
    }

    BOOL DragDetect()
    {
        assert(::IsWindow(m_hWnd));

        POINT pt = {};
        ::GetCursorPos(&pt);
        return ::DragDetect(m_hWnd, pt);
    }

    BDWnd GetAncestor(UINT uFlags) const
    {
        assert(::IsWindow(m_hWnd));
        return BDWnd(::GetAncestor(m_hWnd, uFlags));
    }

// Note: Does not work properly on Vista Aero and above
    BOOL AnimateWindow(DWORD dwFlags, DWORD dwTime = 200)
    {
        assert(::IsWindow(m_hWnd));
        return ::AnimateWindow(m_hWnd, dwTime, dwFlags);
    }

    BOOL FlashWindowEx(DWORD dwFlags, UINT uCount, DWORD dwTimeout = 0)
    {
        assert(::IsWindow(m_hWnd));

        FLASHWINFO fi = { sizeof(FLASHWINFO) };
        fi.hwnd = m_hWnd;
        fi.dwFlags = dwFlags;
        fi.uCount = uCount;
        fi.dwTimeout = dwTimeout;
        return ::FlashWindowEx(&fi);
    }

    BOOL StopFlashWindowEx()
    {
        assert(::IsWindow(m_hWnd));

        FLASHWINFO fi = { sizeof(FLASHWINFO) };
        fi.hwnd = m_hWnd;
        fi.dwFlags = FLASHW_STOP;
        return ::FlashWindowEx(&fi);
    }

// Class long properties

    DWORD GetClassLong(int nIndex) const
    {
        assert(::IsWindow(m_hWnd));
        return ::GetClassLong(m_hWnd, nIndex);
    }

    DWORD SetClassLong(int nIndex, LONG dwNewLong)
    {
        assert(::IsWindow(m_hWnd));
        return ::SetClassLong(m_hWnd, nIndex, dwNewLong);
    }

    ULONG_PTR GetClassLongPtr(int nIndex) const
    {
        assert(::IsWindow(m_hWnd));
        return ::GetClassLongPtr(m_hWnd, nIndex);
    }

    ULONG_PTR SetClassLongPtr(int nIndex, LONG_PTR dwNewLong)
    {
        assert(::IsWindow(m_hWnd));
        return ::SetClassLongPtr(m_hWnd, nIndex, dwNewLong);
    }

// Layered windows

    BOOL SetLayeredWindowAttributes(COLORREF crlKey, BYTE byteAlpha, DWORD dwFlags)
    {
        assert(::IsWindow(m_hWnd));
        assert((GetExStyle() & WS_EX_LAYERED) != 0);

        return ::SetLayeredWindowAttributes(m_hWnd, crlKey, byteAlpha, dwFlags);
    }

    BOOL UpdateLayeredWindow(HDC hdcDst, LPPOINT pptDst, LPSIZE psize, HDC hdcSrc, LPPOINT pptSrc, COLORREF crlKey, BLENDFUNCTION* pblend, DWORD dwFlags)
    {
        assert(::IsWindow(m_hWnd));
        assert((GetExStyle() & WS_EX_LAYERED) != 0);

        return ::UpdateLayeredWindow(m_hWnd, hdcDst, pptDst, psize, hdcSrc, pptSrc, crlKey, pblend, dwFlags);
    }

    BOOL UpdateLayeredWindow(LPPOINT pptDst = NULL)
    {
        assert(::IsWindow(m_hWnd));
        assert((GetExStyle() & WS_EX_LAYERED) != 0);

        return ::UpdateLayeredWindow(m_hWnd, NULL, pptDst, NULL, NULL, NULL, COLORREF(0), NULL, 0);
    }

    BOOL GetLayeredWindowAttributes(COLORREF* pcrlKey, BYTE* pbyteAlpha, DWORD* pdwFlags) const
    {
        assert(::IsWindow(m_hWnd));
        assert((GetExStyle() & WS_EX_LAYERED) != 0);

        return ::GetLayeredWindowAttributes(m_hWnd, pcrlKey, pbyteAlpha, pdwFlags);
    }

// Mouse tracking

    BOOL StartTrackMouseLeave()
    {
        assert(::IsWindow(m_hWnd));

        TRACKMOUSEEVENT tme = {};
        tme.cbSize = sizeof(TRACKMOUSEEVENT);
        tme.dwFlags = TME_LEAVE;
        tme.hwndTrack = m_hWnd;
        return ::TrackMouseEvent(&tme);
    }

    BOOL StartTrackMouse(DWORD dwFlags, DWORD dwHoverTime = HOVER_DEFAULT)
    {
        assert(::IsWindow(m_hWnd));

        TRACKMOUSEEVENT tme = {};
        tme.cbSize = sizeof(TRACKMOUSEEVENT);
        tme.dwFlags = dwFlags;
        tme.hwndTrack = m_hWnd;
        tme.dwHoverTime = dwHoverTime;
        return ::TrackMouseEvent(&tme);
    }

    BOOL CancelTrackMouse(DWORD dwType)
    {
        assert(::IsWindow(m_hWnd));

        TRACKMOUSEEVENT tme = {};
        tme.cbSize = sizeof(TRACKMOUSEEVENT);
        tme.dwFlags = TME_CANCEL | dwType;
        tme.hwndTrack = m_hWnd;
        return ::TrackMouseEvent(&tme);
    }

public:
    static HWND GetDesktopListView()
    {
        HWND hwndLV = ::GetTopWindow(::GetTopWindow(::FindWindow(L"ProgMan", NULL)));
        return hwndLV;
    }

public:
    HWND m_hWnd;
    static RECT rcDefault;

#if defined(D_INCLUDE_TEST) && (D_INCLUDE_TEST==1)
public:
    static DVoid Test()
    {
        BDWnd wnd;
        BDHMenu menu;
        wnd.Create(L"Edit", BDWnd::GetDesktopListView(), BDWnd::rcDefault, menu, L"BDWnd Test Window",
            WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU | WS_SIZEBOX | WS_HSCROLL | WS_VSCROLL | WS_VISIBLE,
            WS_EX_ACCEPTFILES);
        wnd.ShowWindow(SW_SHOW);
        wnd.UpdateWindow();
    }
#endif
};

// Avoid Linking error when in header
_declspec(selectany) RECT BDWnd::rcDefault = { CW_USEDEFAULT, CW_USEDEFAULT, 0, 0 };


/////////////////////////////////////////////////////////////////////////////
// DWinTraits - Manages Windows class information

template <DWORD t_dwStyle = 0, DWORD t_dwExStyle = 0>
class DWinTraits
{
public:
    static DWORD GetWndStyle(DWORD dwStyle)
    {
        return dwStyle == 0 ? t_dwStyle : dwStyle;
    }
    static DWORD GetWndExStyle(DWORD dwExStyle)
    {
        return dwExStyle == 0 ? t_dwExStyle : dwExStyle;
    }
};

///////////////////////////////////////////////////////////////////////////////
// Window Styles
// WS_BORDER  Creates a window that has a thin-line border.
// WS_CAPTION  Creates a window that has a title bar (includes the WS_BORDER style).
// WS_CHILD  Creates a child window. This style cannot be used with the WS_POPUP style.
// WS_CHILDWINDOW  Same as the WS_CHILD style.
// WS_CLIPCHILDREN  Excludes the area occupied by child windows when drawing occurs within the parent window. This style is used when creating the parent window.
// WS_CLIPSIBLINGS  Clips child window that has a border of a style typically used with dialog boxes. A window with this style cannot have a title bar.
// WS_GROUP  Specifies the first control of a group of controls. The group consists of this first control and all controls defined after it, up to the next control with the WS_GROUP style. WS_TABSTOP 
// WS_TABSTOP  Specifies a control that can receive the keyboard focus when the user presses the TAB key. Pressing the TAB key changes the keyboard focus to the next control with the WS_TABSTOP style.
// WS_MINIMIZEBOX  Creates a window that has a Minimize button. 
// WS_MAXIMIZEBOX  Creates a window that has a Maximize button. 
// WS_SYSMENU  Creates a window that has a Close (X) button in the non-client area.
// WS_OVERLAPPED  Creates an overlapped window. An overlapped window has a title bar and a border. 
// WS_OVERLAPPEDWINDOW  Creates an overlapped window with the WS_OVERLAPPED, WS_CAPTION, WS_SYSMENU, WS_THICKFRAME, WS_MINIMIZEBOX, and WS_MAXIMIZEBOX styles
// WS_POPUP  Creates a pop-up window.
// WS_POPUPWINDOW  Creates a pop-up window with WS_BORDER, WS_POPUP, and WS_SYSMENU styles.
// WS_SIZEBOX  Creates a window that has a sizing border. Same as the WS_THICKFRAME style.
// WS_THICKFRAME  Creates a window that has a sizing border. Same as the WS_SIZEBOX style.
// WS_DISABLED  Creates a window that is initially disabled. A disabled window cannot receive input from the user.
// WS_VISIBLE  Creates a wi windows relative to each other;
// WS_DLGFRAME  Creates a window that is initially visible.
// WS_HSCROLL  Creates a window that has a horizontal scroll bar.
// WS_VSCROLL  Creates a window that has a vertical scroll bar.
//
// Window Extend Styles
// WS_EX_ACCEPTFILES  Specifies that a window created with this style accepts drag-drop files.
// WS_EX_CAPTIONOKBTN  Adds an OK button in the caption bar. (Not work)
// WS_EX_CLIENTEDGE  Specifies that a window has a border with a sunken edge. 
// WS_EX_CONTEXTMENU  Adds a Help button in the caption bar.
// WS_EX_DLGMODALFRAME  Creates a window that has a double border;
// WS_EX_INK  Indicates that no default beeping sound is generated on clicking on the window.
// WS_EX_LAYOUTRTL  Creates a window whose horizontal origin is on the right edge. Increasing horizontal values advance to the left.
// WS_EX_LTRREADING  The window text is displayed using left-to-right reading-order properties. This is the default.
// WS_EX_NOACTIVATE  A top-level window created with this style cannot be activated. If a child window has this style, tapping it does not cause its top-level parent to be activated.
// WS_EX_NOANIMATION  A window created with this style does not show animated exploding and imploding rectangles, and does not have a button on the taskbar.
// WS_EX_NODRAG  A window created with this style cannot be dragged using a mouse or stylus.
// WS_EX_NOINHERITLAYOUT  A window created with this style does not pass its window layout to its child windows.
// WS_EX_OVERLAPPEDWINDOW  Combines the WS_EX_CLIENTEDGE and WS_EX_WINDOWEDGE styles.
// WS_EX_PALETTEWINDOW  Combines the WS_EX_WINDOWEDGE, WS_EX_TOOLWINDOW, and WS_EX_TOPMOST styles.
// WS_EX_RTLREADING  If the shell language is Hebrew, Arabic, or another language that supports reading-order alignment, the window text is displayed using right-to-left reading-order properties.
// WS_EX_STATICEDGE  Creates a window with a three-dimensional border style intended to be used for items that do not accept user input.
// WS_EX_TOOLWINDOW  Creates a tool window; that is, a window intended to be used as a floating toolbar.
// WS_EX_TOPMOST  Specifies that a window created with this style should be placed above all non-topmost windows and should stay above them, even when the window is deactivated.
// WS_EX_WINDOWEDGE  Specifies that a window has a border with a raised edge.
//

typedef DWinTraits<WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 0> DControlWinTraits;
typedef DWinTraits<WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, WS_EX_APPWINDOW | WS_EX_WINDOWEDGE> DFrameWinTraits;
typedef DWinTraits<WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_HSCROLL| WS_VSCROLL, WS_EX_APPWINDOW | WS_EX_WINDOWEDGE> DScrollFrameWinTraits;
typedef DWinTraits<WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VSCROLL, WS_EX_APPWINDOW | WS_EX_WINDOWEDGE> DVScrollFrameWinTraits;
typedef DWinTraits<WS_OVERLAPPEDWINDOW | WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, WS_EX_MDICHILD> DMDIChildWinTraits;

typedef DWinTraits<WS_POPUP, 0> DBaseWinTraits;
typedef DWinTraits<WS_POPUP, WS_EX_TOPMOST|WS_EX_WINDOWEDGE|WS_EX_TOOLWINDOW|WS_EX_ACCEPTFILES> DToolWinTraits;
typedef DWinTraits<0, 0> DNullTraits;


template <DWORD t_dwStyle = 0, DWORD t_dwExStyle = 0, class TWinTraits = DControlWinTraits>
class DWinTraitsOR
{
public:
    static DWORD GetWndStyle(_In_ DWORD dwStyle)
    {
        return dwStyle | t_dwStyle | TWinTraits::GetWndStyle(dwStyle);
    }
    static DWORD GetWndExStyle(_In_ DWORD dwExStyle)
    {
        return dwExStyle | t_dwExStyle | TWinTraits::GetWndExStyle(dwExStyle);
    }
};


//////////////////////////////////////////////////////////////////////////////////
// BDMsgHandler

class BDMsgHandler
{
public:
    virtual BOOL ProcessWindowMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// BDWndProcThunk 
// Contains "this link node" + "thunk code"

class BDWndProcThunk
{
public:
    BDCreateWndData cd;    //12B (4B this+4B ThreadID+4B Next)
    BDThunk thunk;        // 8B pointer -> 16B trunk

    BOOL Init(WNDPROC proc, void* pThis)
    {
        return thunk.Init((DWORD_PTR)proc, pThis);
    }

    WNDPROC GetWNDPROC()
    {
        return (WNDPROC)thunk.GetCodeAddress();
    }
};

//////////////////////////////////////////////////////////////////////////////////
// BDWndImplRoot
// BDWnd + BDMsgMap
// Contains BDWndProcThunk + BDMSG*(To Set bHandled) + DWORD state(for Destroy mark)
// Implemention of FORWARD_NOTIFICATIONS() REFLECT_NOTIFICATIONS() and DEFAULT_REFLECTION_HANDLER() in ProcessWindowMessage()

enum { WINSTATE_DESTROYED = 0x00000001 };

template <class TBase /* = BDWnd */>
class BDWndImplRoot : public TBase, public BDMsgHandler
{
public:
    BDWndProcThunk m_thunk;
    const BDMSG* m_pCurrentMsg;
    DWORD m_dwState;

    BDWndImplRoot() : m_pCurrentMsg(NULL), m_dwState(0)
    {
    }

    virtual ~BDWndImplRoot()
    {

    }

    const BDMSG* GetCurrentMessage() const
    {
        return m_pCurrentMsg;
    }

    BOOL IsMsgHandled() const
    {
        const BDMSG* pMsg = GetCurrentMessage();
        return pMsg->bHandled;
    }

    void SetMsgHandled(BOOL bHandled)
    {
        BDMSG* pMsg = (BDMSG*)GetCurrentMessage();
        pMsg->bHandled = bHandled;
    }

    //Send these Messages to Parent
    LRESULT ForwardNotifications(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        LRESULT lResult = 0;
        switch(uMsg)
        {
        case WM_COMMAND:
        case WM_NOTIFY:
        case WM_PARENTNOTIFY:
        case WM_DRAWITEM:
        case WM_MEASUREITEM:
        case WM_COMPAREITEM:
        case WM_DELETEITEM:
        case WM_VKEYTOITEM:
        case WM_CHARTOITEM:
        case WM_HSCROLL:
        case WM_VSCROLL:
        case WM_CTLCOLORBTN:
        case WM_CTLCOLORDLG:
        case WM_CTLCOLOREDIT:
        case WM_CTLCOLORLISTBOX:
        case WM_CTLCOLORMSGBOX:
        case WM_CTLCOLORSCROLLBAR:
        case WM_CTLCOLORSTATIC:
            lResult = this->GetParent().SendMessage(uMsg, wParam, lParam);
            break;
        default:
            bHandled = FALSE;
            break;
        }
        return lResult;
    }

    //Send these messages to child
    LRESULT ReflectNotifications(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        HWND hWndChild = NULL;

        switch(uMsg)
        {
        case WM_COMMAND:
            if(lParam != NULL)    // not from a menu
                hWndChild = (HWND)lParam;
            break;
        case WM_NOTIFY:
            hWndChild = ((LPNMHDR)lParam)->hwndFrom;
            break;
        case WM_PARENTNOTIFY:
            switch(LOWORD(wParam))
            {
            case WM_CREATE:
            case WM_DESTROY:
                hWndChild = (HWND)lParam;
                break;
            default:
                hWndChild = this->GetDlgItem(HIWORD(wParam));
                break;
            }
            break;
        case WM_DRAWITEM:
            if(wParam)    // not from a menu
                hWndChild = ((LPDRAWITEMSTRUCT)lParam)->hwndItem;
            break;
        case WM_MEASUREITEM:
            if(wParam)    // not from a menu
                hWndChild = this->GetDlgItem(((LPMEASUREITEMSTRUCT)lParam)->CtlID);
            break;
        case WM_COMPAREITEM:
            if(wParam)    // not from a menu
                hWndChild =  ((LPCOMPAREITEMSTRUCT)lParam)->hwndItem;
            break;
        case WM_DELETEITEM:
            if(wParam)    // not from a menu
                hWndChild =  ((LPDELETEITEMSTRUCT)lParam)->hwndItem;

            break;
        case WM_VKEYTOITEM:
        case WM_CHARTOITEM:
        case WM_HSCROLL:
        case WM_VSCROLL:
            hWndChild = (HWND)lParam;
            break;
        case WM_CTLCOLORBTN:
        case WM_CTLCOLORDLG:
        case WM_CTLCOLOREDIT:
        case WM_CTLCOLORLISTBOX:
        case WM_CTLCOLORMSGBOX:
        case WM_CTLCOLORSCROLLBAR:
        case WM_CTLCOLORSTATIC:
            hWndChild = (HWND)lParam;
            break;
        default:
            break;
        }

        if(hWndChild == NULL)
        {
            bHandled = FALSE;
            return 1;
        }

        assert(::IsWindow(hWndChild));
        return ::SendMessage(hWndChild, OCM__BASE + uMsg, wParam, lParam);
    }

    //Handle forwarded messages in child
    static BOOL DefaultReflectionHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult)
    {
        switch(uMsg)
        {
        case OCM_COMMAND:
        case OCM_NOTIFY:
        case OCM_PARENTNOTIFY:
        case OCM_DRAWITEM:
        case OCM_MEASUREITEM:
        case OCM_COMPAREITEM:
        case OCM_DELETEITEM:
        case OCM_VKEYTOITEM:
        case OCM_CHARTOITEM:
        case OCM_HSCROLL:
        case OCM_VSCROLL:
        case OCM_CTLCOLORBTN:
        case OCM_CTLCOLORDLG:
        case OCM_CTLCOLOREDIT:
        case OCM_CTLCOLORLISTBOX:
        case OCM_CTLCOLORMSGBOX:
        case OCM_CTLCOLORSCROLLBAR:
        case OCM_CTLCOLORSTATIC:
            lResult = ::DefWindowProc(hWnd, uMsg - OCM__BASE, wParam, lParam);
            return TRUE;
        default:
            break;
        }
        return FALSE;
    }
};


//////////////////////////////////////////////////////////////////////////////////////////////
// DWndImplBaseT
// Add WinTraits for dwStyle and dwExStyle
// Contains StartWindowProc for Setup Thunk
// Contains the main WindowProc to ProcessWindowMessage
// Contains Create to setup "this" in Thunk before CreateWindow
// SubclassWindow/UnsubclassWindow

template <class TBase /* = BDWnd */, class TWinTraits = DControlWinTraits>
class BDWndImplBaseT : public BDWndImplRoot<TBase>
{
public:
    WNDPROC m_pfnSuperWindowProc;

    BDWndImplBaseT() : m_pfnSuperWindowProc(::DefWindowProc)
    {
    }

    static DWORD GetWndStyle(DWORD dwStyle)
    {
        return TWinTraits::GetWndStyle(dwStyle);
    }
    static DWORD GetWndExStyle(DWORD dwExStyle)
    {
        return TWinTraits::GetWndExStyle(dwExStyle);
    }

    virtual WNDPROC GetWindowProc()
    {
        return WindowProc;
    }

    static LRESULT CALLBACK StartWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
		BDWndImplBaseT< TBase, TWinTraits > *pWindow = nullptr;
		LRESULT lRes = 0;
		BOOL bRet;

		if (uMsg == WM_NCCREATE)
		{
			MDICREATESTRUCT * pMDIC = (MDICREATESTRUCT *)((LPCREATESTRUCT)lParam)->lpCreateParams;
			pWindow = (BDWndImplBaseT< TBase, TWinTraits > *)(pMDIC->lParam);
			SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pWindow);
		}
		else
			pWindow = (BDWndImplBaseT< TBase, TWinTraits > *)GetWindowLongPtr(hWnd, GWLP_USERDATA);

		if (pWindow) {
			// Save current Msg
			BDMSG msg(hWnd, uMsg, wParam, lParam);
			const BDMSG* pOldMsg = pWindow->m_pCurrentMsg;
			pWindow->m_pCurrentMsg = &msg;
			pWindow->m_hWnd = hWnd;

			bRet = pWindow->ProcessWindowMessage(hWnd, uMsg, wParam, lParam, lRes, 0);
			// if Not handled
			if (!bRet)
			{
				//如果不是WM_NCDESTROY就用默认的函数来处理
				if (uMsg != WM_NCDESTROY)
				{
					lRes = ::DefWindowProc(hWnd, uMsg, wParam, lParam);
				}
				else
				{
					// 如果是WM_NCDESTROY 
					LONG_PTR pfnWndProc = ::GetWindowLongPtr(pWindow->m_hWnd, GWLP_WNDPROC);
					lRes = pWindow->DefWindowProc(uMsg, wParam, lParam);

					//unsubclass, if needed
					if (pWindow->m_pfnSuperWindowProc != ::DefWindowProc && ::GetWindowLongPtr(pWindow->m_hWnd, GWLP_WNDPROC) == pfnWndProc)
					{
						::SetWindowLongPtr(pWindow->m_hWnd, GWLP_WNDPROC, (LONG_PTR)pWindow->m_pfnSuperWindowProc);
					}
					// mark window as destroyed
					pWindow->m_dwState |= WINSTATE_DESTROYED;
				}
			}

			// for WM_NCDESTROY we Call OnFinalMessage
			if ((pWindow->m_dwState & WINSTATE_DESTROYED) && pOldMsg == NULL)
			{
				// clear out window handle
				HWND hWndThis = pWindow->m_hWnd;
				pWindow->m_hWnd = NULL;
				pWindow->m_dwState &= ~WINSTATE_DESTROYED;
				// clean up after window is destroyed
				pWindow->m_pCurrentMsg = pOldMsg;
				pWindow->OnFinalMessage(hWndThis);
			}
			else
			{
				pWindow->m_pCurrentMsg = pOldMsg;
			}

			return lRes;
		}
		else {
			return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
		}

        /*BDWndImplBaseT< TBase, TWinTraits >* pThis = (BDWndImplBaseT< TBase, TWinTraits >*)BDWinApp::ExtractCreateWndData();
        assert(pThis != NULL);
        if(!pThis) return 0;
        
        pThis->m_hWnd = hWnd;

        pThis->m_thunk.Init(pThis->GetWindowProc(), pThis);

        WNDPROC pProc = pThis->m_thunk.GetWNDPROC();
        WNDPROC pOldProc = (WNDPROC)::SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)pProc);
        (void)(pOldProc);

        return pProc(hWnd, uMsg, wParam, lParam);*/
    }

    static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        BDWndImplBaseT<TBase, TWinTraits>* pThis = (BDWndImplBaseT<TBase, TWinTraits>*)hWnd;

        //Save current Msg
        BDMSG msg(pThis->m_hWnd, uMsg, wParam, lParam);
        const BDMSG* pOldMsg = pThis->m_pCurrentMsg;
        pThis->m_pCurrentMsg = &msg;

        //Process Msg
        //ProcessWindowMessage是另一个基类DMsgMap的虚函数
        //BEGIN_MSG_MAP会在子类中声明它
        LRESULT lRes = 0;
        BOOL bRet = pThis->ProcessWindowMessage(pThis->m_hWnd, uMsg, wParam, lParam, lRes, 0);

        assert(pThis->m_pCurrentMsg == &msg);

        // if Not handled
        if(!bRet)
        {
            //如果不是WM_NCDESTROY就用默认的函数来处理
            if(uMsg != WM_NCDESTROY)
            {
                lRes = pThis->DefWindowProc(uMsg, wParam, lParam);
            }
            else
            {
                // 如果是WM_NCDESTROY 
                LONG_PTR pfnWndProc = ::GetWindowLongPtr(pThis->m_hWnd, GWLP_WNDPROC);
                lRes = pThis->DefWindowProc(uMsg, wParam, lParam);

                //unsubclass, if needed
                if(pThis->m_pfnSuperWindowProc != ::DefWindowProc && ::GetWindowLongPtr(pThis->m_hWnd, GWLP_WNDPROC) == pfnWndProc)
                {
                    ::SetWindowLongPtr(pThis->m_hWnd, GWLP_WNDPROC, (LONG_PTR)pThis->m_pfnSuperWindowProc);
                }
                // mark window as destroyed
                pThis->m_dwState |= WINSTATE_DESTROYED;
            }
        }

        // for WM_NCDESTROY we Call OnFinalMessage
        if((pThis->m_dwState & WINSTATE_DESTROYED) && pOldMsg== NULL)
        {
            // clear out window handle
            HWND hWndThis = pThis->m_hWnd;
            pThis->m_hWnd = NULL;
            pThis->m_dwState &= ~WINSTATE_DESTROYED;
            // clean up after window is destroyed
            pThis->m_pCurrentMsg = pOldMsg;
            pThis->OnFinalMessage(hWndThis);
        }
        else 
        {
            pThis->m_pCurrentMsg = pOldMsg;
        }

        return lRes;
    }

    HWND Create(HWND hWndParent, BDPRect rect, LPCWSTR szWindowName, DWORD dwStyle, DWORD dwExStyle,
                BDHMenu MenuOrID, ATOM atom, LPVOID lpCreateParam = NULL)
    {
        assert(this->m_hWnd == NULL);

        // Allocate the thunk structure here, where we can fail gracefully.
        BOOL result = this->m_thunk.Init(NULL,NULL);

        if (result == FALSE) 
        {
            SetLastError(ERROR_OUTOFMEMORY);
            return NULL;
        }

        if(atom == 0)
        {    
            return NULL;
        }

        // BDWinApp::AddCreateWndData(&this->m_thunk.cd, this);

        if (MenuOrID.m_hMenu == NULL && (dwStyle & WS_CHILD))
        {
            MenuOrID.m_hMenu = (HMENU)(UINT_PTR)this;
        }

        if(rect.m_lpRect == NULL)
        {
            rect.m_lpRect = &TBase::rcDefault;
        }

		// Use MDICREATESTRUCT to support MDI child window
		MDICREATESTRUCT mdic;
		memset(&mdic, 0, sizeof(mdic));
		mdic.lParam = (LPARAM)this;
        HWND hWnd = ::CreateWindowEx(dwExStyle, MAKEINTATOM(atom), szWindowName,
            dwStyle, rect.m_lpRect->left, rect.m_lpRect->top, rect.m_lpRect->right - rect.m_lpRect->left,
            rect.m_lpRect->bottom - rect.m_lpRect->top, hWndParent, MenuOrID.m_hMenu,
            BDWinApp::GetAppInstance(), &mdic);

        return hWnd;
    }

    //subclassWindow should overwrite 
    //virtual WNDPROC GetWindowProc()
    BOOL SubclassWindow(HWND hWnd)
    {
        assert(this->m_hWnd == NULL);
        assert(::IsWindow(hWnd));

        BOOL result = this->m_thunk.Init(GetWindowProc(), this);
        if (result == FALSE)
        {
            return FALSE;
        }

        WNDPROC pProc = this->m_thunk.GetWNDPROC();
        WNDPROC pfnWndProc = (WNDPROC)::SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)pProc);
        if(pfnWndProc == NULL)
            return FALSE;

        m_pfnSuperWindowProc = pfnWndProc;
        this->m_hWnd = hWnd;
        return TRUE;
    }

    // Back to m_pfnSuperWindowProc
    HWND UnsubclassWindow(BOOL bForce = FALSE)
    {
        assert(this->m_hWnd != NULL);

        WNDPROC pOurProc = this->m_thunk.GetWNDPROC();
        WNDPROC pActiveProc = (WNDPROC)::GetWindowLongPtr(this->m_hWnd, GWLP_WNDPROC);

        HWND hWnd = NULL;
        if (bForce || pOurProc == pActiveProc)
        {
            if(!::SetWindowLongPtr(this->m_hWnd, GWLP_WNDPROC, (LONG_PTR)m_pfnSuperWindowProc))
                return NULL;

            m_pfnSuperWindowProc = ::DefWindowProc;
            hWnd = this->m_hWnd;
            this->m_hWnd = NULL;
        }
        return hWnd;
    }

    LRESULT DefWindowProc()
    {
        const BDMSG* pMsg = this->m_pCurrentMsg;
        LRESULT lRes = 0;
        if (pMsg != NULL)
        {
            lRes = DefWindowProc(pMsg->message, pMsg->wParam, pMsg->lParam);
        }
        return lRes;
    }

    LRESULT DefWindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        return ::CallWindowProc(m_pfnSuperWindowProc, this->m_hWnd, uMsg, wParam, lParam);
    }

    virtual void OnFinalMessage(HWND /*hWnd*/)
    {
        // override to do something, if needed
    }
};

typedef BDWndImplBaseT<BDWnd>    DWndImplBase;


////////////////////////////////////////////////////////////////////////////////////////////
// DWndImpl<T> - Used for App Window

template <class T, class TBase = BDWnd, class TWinTraits = DControlWinTraits>
class BDWndImpl : public BDWndImplBaseT<TBase, TWinTraits>
{
public:
    DECLARE_BDWND_CLASS(NULL)

    static LPCWSTR GetWndCaption()
    {
        return NULL;
    }

    HWND Create(HWND hWndParent, BDPRect rect, BDHMenu MenuOrID, 
        LPCWSTR szWindowName = NULL, DWORD dwStyle = 0, DWORD dwExStyle = 0, LPVOID lpCreateParam = NULL)
    {
        if (T::GetWndClassInfo().m_lpszOrigName == NULL)
        {
            T::GetWndClassInfo().m_lpszOrigName = this->GetWndClassName();
        }

        ATOM atom = BDWinApp::RegisterWndClassInfo(&T::GetWndClassInfo(), &this->m_pfnSuperWindowProc);
        assert(atom != 0);

        dwStyle = T::GetWndStyle(dwStyle);
        dwExStyle = T::GetWndExStyle(dwExStyle);

        if (szWindowName == NULL)
            szWindowName = T::GetWndCaption();

        return BDWndImplBaseT< TBase, TWinTraits >::Create(hWndParent, rect, szWindowName,
            dwStyle, dwExStyle, MenuOrID, atom, lpCreateParam);
    }
};


/////////////////////////////////////////////////////////////////////////////
// DDynamicChain - provides support for dynamic chaining
// Using one array to manage all callbacks of DMsgHandler

struct D_CHAIN_ENTRY
{
    DWORD m_dwChainID;        //ChainID
    BDMsgHandler* m_pObject;        //DMsgHandler* ProcessWindowMessage
    DWORD m_dwMsgMapID;        //MsgMapID using ALT_MSG_MAP(1)
};

_declspec(selectany) std::vector<D_CHAIN_ENTRY*> m_aChainEntry;    //vector<D_CHAIN_ENTRY*>
_declspec(selectany) BDCriticalSection g_csCallChain;

class DDynamicChain
{
public:
    static void Clear()
    {
        g_csCallChain.Enter();
        int nCount = m_aChainEntry.size();
        for (int i = 0; i < nCount; i++)
        {
            if (m_aChainEntry[i] != NULL) delete m_aChainEntry[i];
        }
        g_csCallChain.Leave();
    }

    static bool SetChainEntry(DWORD dwChainID, BDMsgHandler* pObject, DWORD dwMsgMapID = 0)
    {
        g_csCallChain.Enter();
        int nCount = m_aChainEntry.size();
        for(int i = 0; i < nCount; i++)
        {
            if(m_aChainEntry[i] != NULL && ((D_CHAIN_ENTRY*)m_aChainEntry[i])->m_dwChainID == dwChainID)
            {
                ((D_CHAIN_ENTRY*)m_aChainEntry[i])->m_pObject = pObject;
                ((D_CHAIN_ENTRY*)m_aChainEntry[i])->m_dwMsgMapID = dwMsgMapID;
                return true;
            }
        }

        // create a new one
        D_CHAIN_ENTRY* pEntry = new D_CHAIN_ENTRY;
        if(pEntry == NULL)
            return false;

        pEntry->m_dwChainID = dwChainID;
        pEntry->m_pObject = pObject;
        pEntry->m_dwMsgMapID = dwMsgMapID;

        for(int i = 0; i < (int)m_aChainEntry.size(); i++)
        {
            if(m_aChainEntry[i] == NULL)
            {
                m_aChainEntry[i]= pEntry;
                return true;
            }
        }

        m_aChainEntry.push_back(pEntry);
        g_csCallChain.Leave();
        return true;
    }

    static bool RemoveChainEntry(DWORD dwChainID)
    {
        g_csCallChain.Enter();
        int nCount = m_aChainEntry.size();
        for(int i = 0; i < nCount; i++)
        {
            if(m_aChainEntry[i] != NULL && ((D_CHAIN_ENTRY*)m_aChainEntry[i])->m_dwChainID == dwChainID)
            {
                delete m_aChainEntry[i];
                m_aChainEntry[i] = NULL;
                return true;
            }
        }
        g_csCallChain.Leave();
        return false;
    }

    static bool CallChain(DWORD dwChainID, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult)
    {
        g_csCallChain.Enter();
        int nCount = m_aChainEntry.size();
        for(int i = 0; i < nCount; i++)
        {
            if(m_aChainEntry[i] != NULL && ((D_CHAIN_ENTRY*)m_aChainEntry[i])->m_dwChainID == dwChainID)
                return (((D_CHAIN_ENTRY*)m_aChainEntry[i])->m_pObject)->ProcessWindowMessage(hWnd, uMsg, wParam, lParam, lResult, ((D_CHAIN_ENTRY*)m_aChainEntry[i])->m_dwMsgMapID)?true:false;
        }
        g_csCallChain.Leave();
        return false;
    }
};


/////////////////////////////////////////////////////////////////////////////
// BDContainedWindow - Implements a contained window
// https://docs.microsoft.com/en-us/cpp/atl/reference/ccontainedwindowt-class?view=vs-2019
//

template <class TBase /* = BDWnd */, class TWinTraits= DControlWinTraits>
class BDContainedWindowT : public TBase
{
public:
    BDWndProcThunk m_thunk;
    LPCWSTR m_lpszClassName;
    WNDPROC m_pfnSuperWindowProc;
    BDMsgHandler* m_pObject;
    DWORD m_dwMsgMapID;
    const BDMSG* m_pCurrentMsg;

    // If you use this constructor you must supply the Window Class Name, Object* and Message Map ID Later to the Create call
    BDContainedWindowT() : m_pCurrentMsg(NULL)
    {
    }

    BDContainedWindowT(LPWSTR lpszClassName, BDMsgHandler* pObject, DWORD dwMsgMapID = 0)
        : m_lpszClassName(lpszClassName), m_pfnSuperWindowProc(::DefWindowProc),
        m_pObject(pObject), m_dwMsgMapID(dwMsgMapID), m_pCurrentMsg(NULL)
    {
    }

    BDContainedWindowT(BDMsgHandler* pObject, DWORD dwMsgMapID = 0)
        : m_lpszClassName(TBase::GetWndClassName()), m_pfnSuperWindowProc(::DefWindowProc),
        m_pObject(pObject), m_dwMsgMapID(dwMsgMapID), m_pCurrentMsg(NULL)
    {
    }

    void SwitchMessageMap(DWORD dwMsgMapID)
    {
        m_dwMsgMapID = dwMsgMapID;
    }

    const BDMSG* GetCurrentMessage() const
    {
        return m_pCurrentMsg;
    }

    LRESULT DefWindowProc()
    {
        const BDMSG* pMsg = m_pCurrentMsg;
        LRESULT lRes = 0;
        if (pMsg != NULL)
            lRes = DefWindowProc(pMsg->message, pMsg->wParam, pMsg->lParam);
        return lRes;
    }

    LRESULT DefWindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        return ::CallWindowProc(m_pfnSuperWindowProc, this->m_hWnd, uMsg, wParam, lParam);
    }

    static LRESULT CALLBACK StartWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        BDContainedWindowT<TBase>* pThis = (BDContainedWindowT<TBase>*)BDWinApp::ExtractCreateWndData();
        assert(pThis != NULL);
        if(!pThis)
        {
            return 0;
        }
        pThis->m_hWnd = hWnd;

        // Initialize the thunk.  This was allocated in DContainedWindowT::Create,
        // so failure is unexpected here.

        pThis->m_thunk.Init(WindowProc, pThis);
        WNDPROC pProc = pThis->m_thunk.GetWNDPROC();
        WNDPROC pOldProc = (WNDPROC)::SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)pProc);

        D_UNUSED(pOldProc);    // avoid unused warning
        return pProc(hWnd, uMsg, wParam, lParam);
    }

    static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        BDContainedWindowT<TBase>* pThis = (BDContainedWindowT<TBase>*)hWnd;
        assert(pThis != NULL);
        if(!pThis) return 0;
        assert(pThis->m_hWnd != NULL);
        assert(pThis->m_pObject != NULL);
        if(!pThis->m_hWnd || !pThis->m_pObject) return 0;

        BDMSG msg(pThis->m_hWnd, uMsg, wParam, lParam);
        const BDMSG* pOldMsg = pThis->m_pCurrentMsg;
        pThis->m_pCurrentMsg = &msg;
        LRESULT lRes = 0;
        BOOL bRet = pThis->m_pObject->ProcessWindowMessage(pThis->m_hWnd, uMsg, wParam, lParam, lRes, pThis->m_dwMsgMapID);
        // restore saved value for the current message
        assert(pThis->m_pCurrentMsg == &msg);
        pThis->m_pCurrentMsg = pOldMsg;
        // do the default processing if message was not handled
        if(!bRet)
        {
            if(uMsg != WM_NCDESTROY)
                lRes = pThis->DefWindowProc(uMsg, wParam, lParam);
            else
            {
                // unsubclass, if needed
                LONG_PTR pfnWndProc = ::GetWindowLongPtr(pThis->m_hWnd, GWLP_WNDPROC);
                lRes = pThis->DefWindowProc(uMsg, wParam, lParam);
                if(pThis->m_pfnSuperWindowProc != ::DefWindowProc && ::GetWindowLongPtr(pThis->m_hWnd, GWLP_WNDPROC) == pfnWndProc)
                    ::SetWindowLongPtr(pThis->m_hWnd, GWLP_WNDPROC, (LONG_PTR)pThis->m_pfnSuperWindowProc);
                // clear out window handle
                pThis->m_hWnd = NULL;
            }
        }
        return lRes;
    }

    ATOM RegisterWndSuperclass()
    {
        ATOM atom = 0;

        WNDCLASSEX wc;
        wc.cbSize = sizeof(WNDCLASSEX);
        if(!::GetClassInfoEx(NULL, m_lpszClassName, &wc))
        {
            if (!::GetClassInfoEx(BDWinApp::GetResInstance(), m_lpszClassName, &wc))
            {
                return atom;
            }
        }

        m_pfnSuperWindowProc = wc.lpfnWndProc;
        
        size_t cchBuff = wcslen((LPCWSTR)m_lpszClassName) + 14;
        LPWSTR szBuff = (LPWSTR)DALLOC(cchBuff * sizeof(WCHAR));
        if (NULL == szBuff)
        {
            return atom;
        }
        wcsncpy((wchar_t*)szBuff, (LPCWSTR)L"DWinUI:", cchBuff);
        wcsncat((wchar_t*)(szBuff+7), (LPCWSTR)m_lpszClassName, cchBuff);

        WNDCLASSEX wc1;
        wc1.cbSize = sizeof(WNDCLASSEX);
        SetLastError(0);
        atom = (ATOM)::GetClassInfoEx(BDWinApp::GetResInstance(), szBuff, &wc1);
        if(atom == 0 && GetLastError() == ERROR_CLASS_DOES_NOT_EXIST)
        {
            wc.lpszClassName = szBuff;
            wc.lpfnWndProc = StartWindowProc;
            wc.hInstance = BDWinApp::GetAppInstance();
            wc.style &= ~CS_GLOBALCLASS;
            BDWndClassInfo dwc = {};
            dwc.m_wc = wc;
            atom = BDWinApp::RegisterWndClassInfo(&dwc, &dwc.pWndProc);
        }

        DFREE(szBuff);
        return atom;
    }

    HWND Create(HWND hWndParent, BDPRect rect, LPCWSTR szWindowName = NULL,
        DWORD dwStyle = 0, DWORD dwExStyle = 0, BDHMenu MenuOrID = 0U, LPVOID lpCreateParam = NULL)
    {
        BOOL result;
        assert(this->m_hWnd == NULL);

        ATOM atom = RegisterWndSuperclass();
        if(atom == 0)
            return NULL;

        // Allocate the thunk structure here, where we can fail gracefully.

        result = m_thunk.Init(NULL,NULL);
        if (result == FALSE)
        {
            SetLastError(ERROR_OUTOFMEMORY);
            return NULL;
        }

        BDWinApp::AddCreateWndData(&m_thunk.cd, this);

        if(MenuOrID.m_hMenu == NULL && (dwStyle & WS_CHILD))
            MenuOrID.m_hMenu = (HMENU)(UINT_PTR)this;
        if(rect.m_lpRect == NULL)
            rect.m_lpRect = &TBase::rcDefault;

        dwStyle = TWinTraits::GetWndStyle(dwStyle);
        dwExStyle = TWinTraits::GetWndExStyle(dwExStyle);

        HWND hWnd = ::CreateWindowEx(dwExStyle, MAKEINTATOM(atom), szWindowName, dwStyle,
            rect.m_lpRect->left, rect.m_lpRect->top,
            rect.m_lpRect->right - rect.m_lpRect->left,
            rect.m_lpRect->bottom - rect.m_lpRect->top,
            hWndParent, MenuOrID.m_hMenu,
            BDWinApp::GetAppInstance(), lpCreateParam);
        
        assert(this->m_hWnd == hWnd);
        return hWnd;
    }

    HWND Create(BDMsgHandler* pObject, DWORD dwMsgMapID, HWND hWndParent,
        BDPRect rect, LPCWSTR szWindowName = NULL, DWORD dwStyle = 0, DWORD dwExStyle = 0,
        BDHMenu MenuOrID = 0U, LPVOID lpCreateParam = NULL)
    {
        m_lpszClassName = TBase::GetWndClassName();
        m_pfnSuperWindowProc = ::DefWindowProc;
        m_pObject = pObject;
        m_dwMsgMapID = dwMsgMapID;
        return Create(hWndParent, rect, szWindowName, dwStyle, dwExStyle, MenuOrID, lpCreateParam);
    }

    HWND Create(LPCWSTR lpszClassName, BDMsgHandler* pObject, DWORD dwMsgMapID, HWND hWndParent,
        BDPRect rect, LPCWSTR szWindowName = NULL, DWORD dwStyle = 0, DWORD dwExStyle = 0, BDHMenu MenuOrID = 0U, LPVOID lpCreateParam = NULL)
    {
        m_lpszClassName = lpszClassName;
        m_pfnSuperWindowProc = ::DefWindowProc;
        m_pObject = pObject;
        m_dwMsgMapID = dwMsgMapID;
        return Create(hWndParent, rect, szWindowName, dwStyle, dwExStyle, MenuOrID, lpCreateParam);
    }

    BOOL SubclassWindow(HWND hWnd)
    {
        BOOL result;
        assert(this->m_hWnd == NULL);
        assert(::IsWindow(hWnd));

        result = m_thunk.Init(WindowProc, this);
        if (result == FALSE)
        {
            return result;
        }

        WNDPROC pProc = m_thunk.GetWNDPROC();
        WNDPROC pfnWndProc = (WNDPROC)::SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)pProc);
        if(pfnWndProc == NULL)
            return FALSE;
        m_pfnSuperWindowProc = pfnWndProc;
        this->m_hWnd = hWnd;
        return TRUE;
    }

    // Use only if you want to subclass before window is destroyed,
    // WindowProc will automatically subclass when  window goes away
    HWND UnsubclassWindow(BOOL bForce = FALSE)
    {
        assert(this->m_hWnd != NULL);

        WNDPROC pOurProc = m_thunk.GetWNDPROC();
        WNDPROC pActiveProc = (WNDPROC)::GetWindowLongPtr(this->m_hWnd, GWLP_WNDPROC);

        HWND hWnd = NULL;
        if (bForce || pOurProc == pActiveProc)
        {
            if(!::SetWindowLongPtr(this->m_hWnd, GWLP_WNDPROC, (LONG_PTR)m_pfnSuperWindowProc))
                return NULL;

            m_pfnSuperWindowProc = ::DefWindowProc;
            hWnd = this->m_hWnd;
            this->m_hWnd = NULL;
        }
        return hWnd;
    }

    LRESULT ReflectNotifications(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        HWND hWndChild = NULL;

        switch(uMsg)
        {
        case WM_COMMAND:
            if(lParam != NULL)    // not from a menu
                hWndChild = (HWND)lParam;
            break;
        case WM_NOTIFY:
            hWndChild = ((LPNMHDR)lParam)->hwndFrom;
            break;
        case WM_PARENTNOTIFY:
            switch(LOWORD(wParam))
            {
            case WM_CREATE:
            case WM_DESTROY:
                hWndChild = (HWND)lParam;
                break;
            default:
                hWndChild = this->GetDlgItem(HIWORD(wParam));
                break;
            }
            break;
        case WM_DRAWITEM:
            if(wParam)    // not from a menu
                hWndChild = ((LPDRAWITEMSTRUCT)lParam)->hwndItem;
            break;
        case WM_MEASUREITEM:
            if(wParam)    // not from a menu
                hWndChild = this->GetDlgItem(((LPMEASUREITEMSTRUCT)lParam)->CtlID);
            break;
        case WM_COMPAREITEM:
            if(wParam)    // not from a menu
                hWndChild = ((LPCOMPAREITEMSTRUCT)lParam)->hwndItem;
            break;
        case WM_DELETEITEM:
            if(wParam)    // not from a menu
                hWndChild = ((LPDELETEITEMSTRUCT)lParam)->hwndItem;

            break;
        case WM_VKEYTOITEM:
        case WM_CHARTOITEM:
        case WM_HSCROLL:
        case WM_VSCROLL:
            hWndChild = (HWND)lParam;
            break;
        case WM_CTLCOLORBTN:
        case WM_CTLCOLORDLG:
        case WM_CTLCOLOREDIT:
        case WM_CTLCOLORLISTBOX:
        case WM_CTLCOLORMSGBOX:
        case WM_CTLCOLORSCROLLBAR:
        case WM_CTLCOLORSTATIC:
            hWndChild = (HWND)lParam;
            break;
        default:
            break;
        }

        if(hWndChild == NULL)
        {
            bHandled = FALSE;
            return 1;
        }

        assert(::IsWindow(hWndChild));
        return ::SendMessage(hWndChild, OCM__BASE + uMsg, wParam, lParam);
    }
};

typedef BDContainedWindowT<BDWnd, DControlWinTraits>    BDContainedWindow;
