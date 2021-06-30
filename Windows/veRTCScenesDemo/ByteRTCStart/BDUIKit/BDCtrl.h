//
//  BDCtrl.h
//
//  Copyright 2020. All rights reserved.
//

#pragma once

#include <richedit.h>
#include <richole.h>
#include <commctrl.h>
#include <assert.h>
#include "BDMisc.h"
#include "BDWinApp.h"
#include "BDWnd.h"


#pragma comment(lib, "comctl32.lib")

#if (_RICHEDIT_VER < 0x0300)
#error DWinUI requires RichEdit version 3 or higher
#endif

///////////////////////////////////////////////////////////////////////////////
// Classes in this file:
//
// BDCtrl - InitCommonControls
// BDStaticT<T> BDStatic - L"STATIC" wrapper 
// BDButtonT<T> BDButton - L"BUTTON" wrapper
// BDEditT<T> BDEdit - L"EDIT" wrapper
// BDComboBox<T> BDComboBox - L"COMBOBOX" wrapper
// BDComboBox<T> BDComboBox - L"COMBOBOX" wrapper
// DScrollBarT<T> DScrollBar - L"SCROLLBAR" wrapper

// These are wrapper classes for Windows standard and common controls.
// To implement a window based on a control, use following:
// Example: Implementing a window based on a list box
//
// class BDMyListBox : BDWndImpl<BDMyListBox, BDListBox>
// {
// public:
//      BEGIN_MSG_MAP(BDMyListBox)
//          // put your message handler entries here
//      END_MSG_MAP()
// };


///////////////////////////////////////////////////////////////////////////////
// BDCtrl

class BDCtrl
{
public:
    static BOOL InitCommonControls(DWORD dwFlags)
    {
        INITCOMMONCONTROLSEX iccx = { sizeof(INITCOMMONCONTROLSEX), dwFlags };
        BOOL bRet = ::InitCommonControlsEx(&iccx);
        assert(bRet);
        return bRet;
    }
};

///////////////////////////////////////////////////////////////////////////////
// BDStatic - client side for a Windows STATIC control

/*
Style Description
SS_BITMAP Specifies that a bitmap is to be displayed in the static control. The text is the name of a bitmap (not a filename) defined elsewhere in the resource file. The style ignores the nWidth and nHeight parameters; the control automatically sizes itself to accommodate the bitmap.
SS_BLACKFRAME Specifies a box with a frame drawn in the same color as the window frames. This color is black in the default color scheme.
SS_BLACKRECT Specifies a rectangle filled with the current window frame color. This color is black in the default color scheme.
SS_CENTER Specifies a simple rectangle and centers the text in the rectangle. The text is formatted before it is displayed. Words that extend past the end of a line are automatically wrapped to the beginning of the next centered line. Words that are longer than the width of the control are truncated.
SS_CENTERIMAGE Specifies that a bitmap is centered in the static control that contains it. The control is not resized, so that a bitmap too large for the control will be clipped. If the static control contains a single line of text, the text is centered vertically in the client area of the control.
Microsoft Windows XP: This style bit no longer results in unused portions of the control being filled with the color of the top left pixel of the bitmap or icon. Unused portions of the control will remain the background color.

SS_EDITCONTROL Windows 2000: Specifies that the static control duplicates the text-displaying characteristics of a multiline edit control. Specifically, the average character width is calculated in the same manner as with an edit control, and the function does not display a partially visible last line.
SS_ENDELLIPSIS Microsoft Windows NT or later: If the end of a string does not fit in the rectangle, it is truncated and ellipses are added. If a word that is not at the end of the string goes beyond the limits of the rectangle, it is truncated without ellipses. Compare with SS_PATHELLIPSIS and SS_WORDELLIPSIS.
SS_ENHMETAFILE Specifies that an enhanced metafile is to be displayed in the static control. The text is the name of a metafile. An enhanced metafile static control has a fixed size; the metafile is scaled to fit the static control's client area.
SS_ETCHEDFRAME Draws the frame of the static control using the EDGE_ETCHED edge style. For more information, see the DrawEdge function.
SS_ETCHEDHORZ Draws the top and bottom edges of the static control using the EDGE_ETCHED edge style. For more information, see the DrawEdge function.
SS_ETCHEDVERT Draws the left and right edges of the static control using the EDGE_ETCHED edge style. For more information, see the DrawEdge function.
SS_GRAYFRAME Specifies a box with a frame drawn with the same color as the screen background (desktop). This color is gray in the default color scheme.
SS_GRAYRECT Specifies a rectangle filled with the current screen background color. This color is gray in the default color scheme.
SS_ICON Specifies an icon to be displayed in the dialog box. If the control is created as part of a dialog box, the text is the name of an icon (not a filename) defined elsewhere in the resource file. If the control is created via CreateWindow or a related function, the text is the name of an icon (not a filename) defined in the resource file associated with the module specified by the hInstance parameter to CreateWindow.

The icon can be an animated cursor.

The style ignores the CreateWindow parameters nWidth and nHeight; the control automatically sizes itself to accommodate the icon. As it uses the LoadIcon function, the SS_ICON style can load only icons of dimensions SM_CXICON and SM_CYICON. This restriction can be bypassed by using the SS_REALSIZEIMAGE style in addition to SS_ICON.

If an icon cannot be loaded through LoadIcon, an attempt is made to load the specified resource as a cursor using LoadCursor. If that too fails, an attempt is made to load from the device driver using LoadImage.
SS_LEFT Specifies a simple rectangle and left-aligns the text in the rectangle. The text is formatted before it is displayed. Words that extend past the end of a line are automatically wrapped to the beginning of the next left-aligned line. Words that are longer than the width of the control are truncated.
SS_LEFTNOWORDWRAP Specifies a simple rectangle and left-aligns the text in the rectangle. Tabs are expanded, but words are not wrapped. Text that extends past the end of a line is clipped.
SS_NOPREFIX Prevents interpretation of any ampersand (&) characters in the control's text as accelerator prefix characters. These are displayed with the ampersand removed and the next character in the string underlined. This static control style may be included with any of the defined static controls. You can combine SS_NOPREFIX with other styles. This can be useful when filenames or other strings that may contain an ampersand (&) must be displayed in a static control in a dialog box.
SS_NOTIFY Sends the parent window STN_CLICKED, STN_DBLCLK, STN_DISABLE, and STN_ENABLE notification messages when the user clicks or double-clicks the control.
SS_OWNERDRAW Specifies that the owner of the static control is responsible for drawing the control. The owner window receives a WM_DRAWITEM message whenever the control needs to be drawn.
SS_PATHELLIPSIS Windows NT or later: Replaces characters in the middle of the string with ellipses so that the result fits in the specified rectangle. If the string contains backslash (\) characters, SS_PATHELLIPSIS preserves as much as possible of the text after the last backslash. Compare with SS_ENDELLIPSIS and SS_WORDELLIPSIS.
SS_REALSIZECONTROL Windows XP or later: Adjusts the bitmap to fit the size of the static control. For example, changing the locale can change the system font, and thus controls might be resized. If a static control had a bitmap, the bitmap would no longer fit the control. This style bit dictates automatic redimensioning of bitmaps to fit their controls.
If SS_CENTERIMAGE is specified, the bitmap or icon is centered (and clipped if needed). If SS_CENTERIMAGE is not specified, the bitmap or icon is stretched or shrunk.

Note that the redimensioning in the two axes are independent, and the result may have a changed aspect ratio.

Compare with SS_REALSIZEIMAGE.

SS_REALSIZEIMAGE Specifies that the actual resource width is used and the icon is loaded using LoadImage. SS_REALSIZEIMAGE is always used in conjunction with SS_ICON.
SS_REALSIZEIMAGE uses LoadImage, overriding the process normally followed under SS_ICON. It does not load cursors; if LoadImage fails, no further attempts to load are made. It uses the actual resource width. The static control is resized accordingly, but the icon remains aligned to the originally specified left and top edges of the control.

Note that if SS_CENTERIMAGE is also specified, the icon is centered within the control's space, which was specified using the CreateWindow parameters nWidth and nHeight.

Compare with SS_REALSIZECONTROL.

SS_RIGHT Specifies a simple rectangle and right-aligns the text in the rectangle. The text is formatted before it is displayed. Words that extend past the end of a line are automatically wrapped to the beginning of the next right-aligned line. Words that are longer than the width of the control are truncated.
SS_RIGHTJUST Specifies that the lower right corner of a static control with the SS_BITMAP or SS_ICON style is to remain fixed when the control is resized. Only the top and left sides are adjusted to accommodate a new bitmap or icon.
SS_SIMPLE Specifies a simple rectangle and displays a single line of left-aligned text in the rectangle. The text line cannot be shortened or altered in any way. Also, if the control is disabled, the control does not gray its text.
SS_SUNKEN Draws a half-sunken border around a static control.
SS_TYPEMASK Windows 2000: A composite style bit that results from using the OR operator on SS_* style bits. Can be used to mask out valid SS_* bits from a given bitmask. Note that this is out of date and does not correctly include all valid styles. Thus, you should not use this style.
SS_WHITEFRAME Specifies a box with a frame drawn with the same color as the window background. This color is white in the default color scheme.
SS_WHITERECT Specifies a rectangle filled with the current window background color. This color is white in the default color scheme.
SS_WORDELLIPSIS Windows NT or later: Truncates any word that does not fit in the rectangle and adds ellipses.
Compare with SS_ENDELLIPSIS and SS_PATHELLIPSIS.
*/

template <class TBase>
class BDStaticT : public TBase
{
public:
    // Constructors
    BDStaticT(HWND hWnd = NULL) : TBase(hWnd)
    { }

    BDStaticT< TBase >& operator =(HWND hWnd)
    {
        this->m_hWnd = hWnd;
        return *this;
    }

    HWND Create(HWND hWndParent, BDPRect rect, BDHMenu MenuOrID, LPCWSTR szWindowName = NULL,
        DWORD dwStyle = WS_CHILD | WS_VISIBLE, DWORD dwExStyle = 0, LPVOID lpCreateParam = NULL)
    {
        return TBase::Create(GetWndClassName(), hWndParent, rect, MenuOrID, szWindowName, dwStyle, dwExStyle, lpCreateParam);
    }

    // Attributes
    static LPCWSTR GetWndClassName()
    {
        return L"STATIC";
    }

    HICON GetIcon() const
    {
        assert(::IsWindow(this->m_hWnd));
        return (HICON)::SendMessage(this->m_hWnd, STM_GETICON, 0, 0L);
    }

    HICON SetIcon(HICON hIcon)
    {
        assert(::IsWindow(this->m_hWnd));
        return (HICON)::SendMessage(this->m_hWnd, STM_SETICON, (WPARAM)hIcon, 0L);
    }

    HENHMETAFILE GetEnhMetaFile() const
    {
        assert(::IsWindow(this->m_hWnd));
        return (HENHMETAFILE)::SendMessage(this->m_hWnd, STM_GETIMAGE, IMAGE_ENHMETAFILE, 0L);
    }

    HENHMETAFILE SetEnhMetaFile(HENHMETAFILE hMetaFile)
    {
        assert(::IsWindow(this->m_hWnd));
        return (HENHMETAFILE)::SendMessage(this->m_hWnd, STM_SETIMAGE, IMAGE_ENHMETAFILE, (LPARAM)hMetaFile);
    }

    HBITMAP GetBitmap() const
    {
        assert(::IsWindow(this->m_hWnd));
        return (HBITMAP)::SendMessage(this->m_hWnd, STM_GETIMAGE, IMAGE_BITMAP, 0L);
    }

    HBITMAP SetBitmap(HBITMAP hBitmap)
    {
        assert(::IsWindow(this->m_hWnd));
        return (HBITMAP)::SendMessage(this->m_hWnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);
    }

    HCURSOR GetCursor() const
    {
        assert(::IsWindow(this->m_hWnd));
        return (HCURSOR)::SendMessage(this->m_hWnd, STM_GETIMAGE, IMAGE_CURSOR, 0L);
    }

    HCURSOR SetCursor(HCURSOR hCursor)
    {
        assert(::IsWindow(this->m_hWnd));
        return (HCURSOR)::SendMessage(this->m_hWnd, STM_SETIMAGE, IMAGE_CURSOR, (LPARAM)hCursor);
    }

    BDString GetWindowText() const
    {
        BDString strRet;
        int nLen = ::GetWindowTextLength(this->m_hWnd);
        if (nLen > 0)
        {
            strRet.GetBuffer(nLen);
            ::GetWindowText(this->m_hWnd, strRet.GetBuffer(), nLen);
        }
        else
        {
            strRet.Empty();
        }
        return strRet;
    }
};

typedef BDStaticT<BDWnd>   BDStatic;


///////////////////////////////////////////////////////////////////////////////
// DButton - client side for a Windows BUTTON control

template <class TBase>
class BDButtonT : public TBase
{
public:
    // Constructors
    BDButtonT(HWND hWnd = NULL) : TBase(hWnd)
    { }

    BDButtonT< TBase >& operator =(HWND hWnd)
    {
        this->m_hWnd = hWnd;
        return *this;
    }

    HWND Create(HWND hWndParent, BDPRect rect, BDHMenu MenuOrID, LPCWSTR szWindowName = NULL,
        DWORD dwStyle = 0, DWORD dwExStyle = 0, LPVOID lpCreateParam = NULL)
    {
        return TBase::Create(GetWndClassName(), hWndParent, rect, MenuOrID, szWindowName, dwStyle, dwExStyle, lpCreateParam);
    }

    // Attributes
    static LPCWSTR GetWndClassName()
    {
        return L"BUTTON";
    }

    UINT GetState() const
    {
        assert(::IsWindow(this->m_hWnd));
        return (UINT)::SendMessage(this->m_hWnd, BM_GETSTATE, 0, 0L);
    }

    void SetState(BOOL bHighlight)
    {
        assert(::IsWindow(this->m_hWnd));
        ::SendMessage(this->m_hWnd, BM_SETSTATE, bHighlight, 0L);
    }

    int GetCheck() const
    {
        assert(::IsWindow(this->m_hWnd));
        return (int)::SendMessage(this->m_hWnd, BM_GETCHECK, 0, 0L);
    }

    void SetCheck(int nCheck)
    {
        assert(::IsWindow(this->m_hWnd));
        ::SendMessage(this->m_hWnd, BM_SETCHECK, nCheck, 0L);
    }

    UINT GetButtonStyle() const
    {
        assert(::IsWindow(this->m_hWnd));
        return (UINT)::GetWindowLong(this->m_hWnd, GWL_STYLE) & 0xFFFF;
    }

    void SetButtonStyle(UINT nStyle, BOOL bRedraw = TRUE)
    {
        assert(::IsWindow(this->m_hWnd));
        ::SendMessage(this->m_hWnd, BM_SETSTYLE, nStyle, (LPARAM)bRedraw);
    }

    HICON GetIcon() const
    {
        assert(::IsWindow(this->m_hWnd));
        return (HICON)::SendMessage(this->m_hWnd, BM_GETIMAGE, IMAGE_ICON, 0L);
    }

    HICON SetIcon(HICON hIcon)
    {
        assert(::IsWindow(this->m_hWnd));
        return (HICON)::SendMessage(this->m_hWnd, BM_SETIMAGE, IMAGE_ICON, (LPARAM)hIcon);
    }

    HBITMAP GetBitmap() const
    {
        assert(::IsWindow(this->m_hWnd));
        return (HBITMAP)::SendMessage(this->m_hWnd, BM_GETIMAGE, IMAGE_BITMAP, 0L);
    }

    HBITMAP SetBitmap(HBITMAP hBitmap)
    {
        assert(::IsWindow(this->m_hWnd));
        return (HBITMAP)::SendMessage(this->m_hWnd, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);
    }

#if (_WIN32_WINNT >= _WIN32_WINNT_WINXP)
    BOOL GetIdealSize(LPSIZE lpSize) const
    {
        assert(::IsWindow(this->m_hWnd));
        return (BOOL)::SendMessage(this->m_hWnd, BCM_GETIDEALSIZE, 0, (LPARAM)lpSize);
    }

    BOOL GetImageList(PBUTTON_IMAGELIST pButtonImagelist) const
    {
        assert(::IsWindow(this->m_hWnd));
        return (BOOL)::SendMessage(this->m_hWnd, BCM_GETIMAGELIST, 0, (LPARAM)pButtonImagelist);
    }

    BOOL SetImageList(PBUTTON_IMAGELIST pButtonImagelist)
    {
        assert(::IsWindow(this->m_hWnd));
        return (BOOL)::SendMessage(this->m_hWnd, BCM_SETIMAGELIST, 0, (LPARAM)pButtonImagelist);
    }

    BOOL GetTextMargin(LPRECT lpRect) const
    {
        assert(::IsWindow(this->m_hWnd));
        return (BOOL)::SendMessage(this->m_hWnd, BCM_GETTEXTMARGIN, 0, (LPARAM)lpRect);
    }

    BOOL SetTextMargin(LPRECT lpRect)
    {
        assert(::IsWindow(this->m_hWnd));
        return (BOOL)::SendMessage(this->m_hWnd, BCM_SETTEXTMARGIN, 0, (LPARAM)lpRect);
    }
#endif // (_WIN32_WINNT >= _WIN32_WINNT_WINXP)

#if (WINVER >= _WIN32_WINNT_VISTA)
    void SetDontClick(BOOL bDontClick)
    {
        assert(::IsWindow(this->m_hWnd));
        ::SendMessage(this->m_hWnd, BM_SETDONTCLICK, (WPARAM)bDontClick, 0L);
    }

    BOOL SetDropDownState(BOOL bDropDown)
    {
        assert(::IsWindow(this->m_hWnd));
        assert((this->GetStyle() & (BS_SPLITBUTTON | BS_DEFSPLITBUTTON)) != 0);
        return (BOOL)::SendMessage(this->m_hWnd, BCM_SETDROPDOWNSTATE, (WPARAM)bDropDown, 0L);
    }

    BOOL GetSplitInfo(PBUTTON_SPLITINFO pSplitInfo) const
    {
        assert(::IsWindow(this->m_hWnd));
        assert((this->GetStyle() & (BS_SPLITBUTTON | BS_DEFSPLITBUTTON)) != 0);
        return (BOOL)::SendMessage(this->m_hWnd, BCM_GETSPLITINFO, 0, (LPARAM)pSplitInfo);
    }

    BOOL SetSplitInfo(PBUTTON_SPLITINFO pSplitInfo)
    {
        assert(::IsWindow(this->m_hWnd));
        assert((this->GetStyle() & (BS_SPLITBUTTON | BS_DEFSPLITBUTTON)) != 0);
        return (BOOL)::SendMessage(this->m_hWnd, BCM_SETSPLITINFO, 0, (LPARAM)pSplitInfo);
    }

    int GetNoteLength() const
    {
        assert(::IsWindow(this->m_hWnd));
        assert((this->GetStyle() & (BS_COMMANDLINK | BS_DEFCOMMANDLINK)) != 0);
        return (int)::SendMessage(this->m_hWnd, BCM_GETNOTELENGTH, 0, 0L);
    }

    BOOL GetNote(LPWSTR lpstrNoteText, int cchNoteText) const
    {
        assert(::IsWindow(this->m_hWnd));
        assert((this->GetStyle() & (BS_COMMANDLINK | BS_DEFCOMMANDLINK)) != 0);
        return (BOOL)::SendMessage(this->m_hWnd, BCM_GETNOTE, cchNoteText, (LPARAM)lpstrNoteText);
    }

    BOOL SetNote(LPCWSTR lpstrNoteText)
    {
        assert(::IsWindow(this->m_hWnd));
        assert((this->GetStyle() & (BS_COMMANDLINK | BS_DEFCOMMANDLINK)) != 0);
        return (BOOL)::SendMessage(this->m_hWnd, BCM_SETNOTE, 0, (LPARAM)lpstrNoteText);
    }

    LRESULT SetElevationRequiredState(BOOL bSet)
    {
        assert(::IsWindow(this->m_hWnd));
        return ::SendMessage(this->m_hWnd, BCM_SETSHIELD, 0, (LPARAM)bSet);
    }
#endif // (_WIN32_WINNT >= _WIN32_WINNT_VISTA)

    // Operations
    void Click()
    {
        assert(::IsWindow(this->m_hWnd));
        ::SendMessage(this->m_hWnd, BM_CLICK, 0, 0L);
    }
};

typedef BDButtonT<BDWnd>   BDButton;


///////////////////////////////////////////////////////////////////////////////
// BDEdit - client side for a Windows EDIT control

template <class TBase>
class BDEditT : public TBase
{
public:
    // Constructors
    BDEditT(HWND hWnd = NULL) : TBase(hWnd)
    { }

    BDEditT< TBase >& operator =(HWND hWnd)
    {
        this->m_hWnd = hWnd;
        return *this;
    }

    HWND Create(HWND hWndParent, BDPRect rect, BDHMenu MenuOrID, LPCWSTR szWindowName = NULL,
        DWORD dwStyle = 0, DWORD dwExStyle = 0, LPVOID lpCreateParam = NULL)
    {
        return TBase::Create(GetWndClassName(), hWndParent, BDPRect(rect.m_lpRect), BDHMenu(MenuOrID.m_hMenu), szWindowName, dwStyle, dwExStyle, lpCreateParam);
    }

    // Attributes
    static LPCWSTR GetWndClassName()
    {
        return L"EDIT";
    }

    BOOL CanUndo() const
    {
        assert(::IsWindow(this->m_hWnd));
        return (BOOL)::SendMessage(this->m_hWnd, EM_CANUNDO, 0, 0L);
    }

    int GetLineCount() const
    {
        assert(::IsWindow(this->m_hWnd));
        return (int)::SendMessage(this->m_hWnd, EM_GETLINECOUNT, 0, 0L);
    }

    BOOL GetModify() const
    {
        assert(::IsWindow(this->m_hWnd));
        return (BOOL)::SendMessage(this->m_hWnd, EM_GETMODIFY, 0, 0L);
    }

    void SetModify(BOOL bModified = TRUE)
    {
        assert(::IsWindow(this->m_hWnd));
        ::SendMessage(this->m_hWnd, EM_SETMODIFY, bModified, 0L);
    }

    void GetRect(LPRECT lpRect) const
    {
        assert(::IsWindow(this->m_hWnd));
        ::SendMessage(this->m_hWnd, EM_GETRECT, 0, (LPARAM)lpRect);
    }

    DWORD GetSel() const
    {
        assert(::IsWindow(this->m_hWnd));
        return (DWORD)::SendMessage(this->m_hWnd, EM_GETSEL, 0, 0L);
    }

    void GetSel(int& nStartChar, int& nEndChar) const
    {
        assert(::IsWindow(this->m_hWnd));
        ::SendMessage(this->m_hWnd, EM_GETSEL, (WPARAM)&nStartChar, (LPARAM)&nEndChar);
    }

    HLOCAL GetHandle() const
    {
        assert(::IsWindow(this->m_hWnd));
        return (HLOCAL)::SendMessage(this->m_hWnd, EM_GETHANDLE, 0, 0L);
    }

    void SetHandle(HLOCAL hBuffer)
    {
        assert(::IsWindow(this->m_hWnd));
        ::SendMessage(this->m_hWnd, EM_SETHANDLE, (WPARAM)hBuffer, 0L);
    }

    DWORD GetMargins() const
    {
        assert(::IsWindow(this->m_hWnd));
        return (DWORD)::SendMessage(this->m_hWnd, EM_GETMARGINS, 0, 0L);
    }

    void GetMargins(UINT& nLeft, UINT& nRight) const
    {
        assert(::IsWindow(this->m_hWnd));
        DWORD dwRet = (DWORD)::SendMessage(this->m_hWnd, EM_GETMARGINS, 0, 0L);
        nLeft = D_LOWORD(dwRet);
        nRight = D_HIWORD(dwRet);
    }

    void SetMargins(UINT nLeft, UINT nRight, WORD wFlags = EC_LEFTMARGIN | EC_RIGHTMARGIN)
    {
        assert(::IsWindow(this->m_hWnd));
        ::SendMessage(this->m_hWnd, EM_SETMARGINS, wFlags, MAKELONG(nLeft, nRight));
    }

    UINT GetLimitText() const
    {
        assert(::IsWindow(this->m_hWnd));
        return (UINT)::SendMessage(this->m_hWnd, EM_GETLIMITTEXT, 0, 0L);
    }

    void SetLimitText(UINT nMax)
    {
        assert(::IsWindow(this->m_hWnd));
        ::SendMessage(this->m_hWnd, EM_SETLIMITTEXT, nMax, 0L);
    }

    POINT PosFromChar(UINT nChar) const
    {
        assert(::IsWindow(this->m_hWnd));
        DWORD dwRet = (DWORD)::SendMessage(this->m_hWnd, EM_POSFROMCHAR, nChar, 0);
        POINT point = { GET_X_LPARAM(dwRet), GET_Y_LPARAM(dwRet) };
        return point;
    }

    int CharFromPos(POINT pt, int* pLine = NULL) const
    {
        assert(::IsWindow(this->m_hWnd));
        DWORD dwRet = (DWORD)::SendMessage(this->m_hWnd, EM_CHARFROMPOS, 0, MAKELPARAM(pt.x, pt.y));
        if (pLine != NULL)
            *pLine = (int)(short)D_HIWORD(dwRet);
        return (int)(short)D_LOWORD(dwRet);
    }

    // NOTE: first word in lpszBuffer must contain the size of the buffer!
    int GetLine(int nIndex, LPWSTR lpszBuffer) const
    {
        assert(::IsWindow(this->m_hWnd));
        return (int)::SendMessage(this->m_hWnd, EM_GETLINE, nIndex, (LPARAM)lpszBuffer);
    }

    int GetLine(int nIndex, LPWSTR lpszBuffer, int nMaxLength) const
    {
        assert(::IsWindow(this->m_hWnd));
        *(LPWORD)lpszBuffer = (WORD)nMaxLength;
        return (int)::SendMessage(this->m_hWnd, EM_GETLINE, nIndex, (LPARAM)lpszBuffer);
    }

    TCHAR GetPasswordChar() const
    {
        assert(::IsWindow(this->m_hWnd));
        return (TCHAR)::SendMessage(this->m_hWnd, EM_GETPASSWORDCHAR, 0, 0L);
    }

    void SetPasswordChar(TCHAR ch)
    {
        assert(::IsWindow(this->m_hWnd));
        ::SendMessage(this->m_hWnd, EM_SETPASSWORDCHAR, ch, 0L);
    }

    EDITWORDBREAKPROC GetWordBreakProc() const
    {
        assert(::IsWindow(this->m_hWnd));
        return (EDITWORDBREAKPROC)::SendMessage(this->m_hWnd, EM_GETWORDBREAKPROC, 0, 0L);
    }

    void SetWordBreakProc(EDITWORDBREAKPROC ewbprc)
    {
        assert(::IsWindow(this->m_hWnd));
        ::SendMessage(this->m_hWnd, EM_SETWORDBREAKPROC, 0, (LPARAM)ewbprc);
    }

    int GetFirstVisibleLine() const
    {
        assert(::IsWindow(this->m_hWnd));
        return (int)::SendMessage(this->m_hWnd, EM_GETFIRSTVISIBLELINE, 0, 0L);
    }

    int GetThumb() const
    {
        assert(::IsWindow(this->m_hWnd));
        assert((this->GetStyle() & ES_MULTILINE) != 0);
        return (int)::SendMessage(this->m_hWnd, EM_GETTHUMB, 0, 0L);
    }

    BOOL SetReadOnly(BOOL bReadOnly = TRUE)
    {
        assert(::IsWindow(this->m_hWnd));
        return (BOOL)::SendMessage(this->m_hWnd, EM_SETREADONLY, bReadOnly, 0L);
    }

    UINT GetImeStatus(UINT uStatus) const
    {
        assert(::IsWindow(this->m_hWnd));
        return (UINT)::SendMessage(this->m_hWnd, EM_GETIMESTATUS, uStatus, 0L);
    }

    UINT SetImeStatus(UINT uStatus, UINT uData)
    {
        assert(::IsWindow(this->m_hWnd));
        return (UINT)::SendMessage(this->m_hWnd, EM_SETIMESTATUS, uStatus, uData);
    }

    BOOL GetCueBannerText(LPCWSTR lpstrText, int cchText) const
    {
        assert(::IsWindow(this->m_hWnd));
        return (BOOL)::SendMessage(this->m_hWnd, EM_GETCUEBANNER, (WPARAM)lpstrText, cchText);
    }

    // bKeepWithFocus - Vista only
    BOOL SetCueBannerText(LPCWSTR lpstrText, BOOL bKeepWithFocus = FALSE)
    {
        assert(::IsWindow(this->m_hWnd));
        return (BOOL)::SendMessage(this->m_hWnd, EM_SETCUEBANNER, (WPARAM)bKeepWithFocus, (LPARAM)(lpstrText));
    }

    // Operations
    void EmptyUndoBuffer()
    {
        assert(::IsWindow(this->m_hWnd));
        ::SendMessage(this->m_hWnd, EM_EMPTYUNDOBUFFER, 0, 0L);
    }

    BOOL FmtLines(BOOL bAddEOL)
    {
        assert(::IsWindow(this->m_hWnd));
        return (BOOL)::SendMessage(this->m_hWnd, EM_FMTLINES, bAddEOL, 0L);
    }

    void LimitText(int nChars = 0)
    {
        assert(::IsWindow(this->m_hWnd));
        ::SendMessage(this->m_hWnd, EM_LIMITTEXT, nChars, 0L);
    }

    int LineFromChar(int nIndex = -1) const
    {
        assert(::IsWindow(this->m_hWnd));
        return (int)::SendMessage(this->m_hWnd, EM_LINEFROMCHAR, nIndex, 0L);
    }

    int LineIndex(int nLine = -1) const
    {
        assert(::IsWindow(this->m_hWnd));
        return (int)::SendMessage(this->m_hWnd, EM_LINEINDEX, nLine, 0L);
    }

    int LineLength(int nLine = -1) const
    {
        assert(::IsWindow(this->m_hWnd));
        return (int)::SendMessage(this->m_hWnd, EM_LINELENGTH, nLine, 0L);
    }

    void LineScroll(int nLines, int nChars = 0)
    {
        assert(::IsWindow(this->m_hWnd));
        ::SendMessage(this->m_hWnd, EM_LINESCROLL, nChars, nLines);
    }

    void ReplaceSel(LPCWSTR lpszNewText, BOOL bCanUndo = FALSE)
    {
        assert(::IsWindow(this->m_hWnd));
        ::SendMessage(this->m_hWnd, EM_REPLACESEL, (WPARAM)bCanUndo, (LPARAM)lpszNewText);
    }

    void SetRect(LPCRECT lpRect)
    {
        assert(::IsWindow(this->m_hWnd));
        ::SendMessage(this->m_hWnd, EM_SETRECT, 0, (LPARAM)lpRect);
    }

    void SetRectNP(LPCRECT lpRect)
    {
        assert(::IsWindow(this->m_hWnd));
        ::SendMessage(this->m_hWnd, EM_SETRECTNP, 0, (LPARAM)lpRect);
    }

    void SetSel(DWORD dwSelection, BOOL bNoScroll = FALSE)
    {
        assert(::IsWindow(this->m_hWnd));
        ::SendMessage(this->m_hWnd, EM_SETSEL, LOWORD(dwSelection), HIWORD(dwSelection));
        if (!bNoScroll)
            ::SendMessage(this->m_hWnd, EM_SCROLLCARET, 0, 0L);
    }

    void SetSel(int nStartChar, int nEndChar, BOOL bNoScroll = FALSE)
    {
        assert(::IsWindow(this->m_hWnd));
        ::SendMessage(this->m_hWnd, EM_SETSEL, nStartChar, nEndChar);
        if (!bNoScroll)
            ::SendMessage(this->m_hWnd, EM_SCROLLCARET, 0, 0L);
    }

    void SetSelAll(BOOL bNoScroll = FALSE)
    {
        SetSel(0, -1, bNoScroll);
    }

    void SetSelNone(BOOL bNoScroll = FALSE)
    {
        SetSel(-1, 0, bNoScroll);
    }

    BOOL SetTabStops(int nTabStops, LPINT rgTabStops)
    {
        assert(::IsWindow(this->m_hWnd));
        return (BOOL)::SendMessage(this->m_hWnd, EM_SETTABSTOPS, nTabStops, (LPARAM)rgTabStops);
    }

    BOOL SetTabStops()
    {
        assert(::IsWindow(this->m_hWnd));
        return (BOOL)::SendMessage(this->m_hWnd, EM_SETTABSTOPS, 0, 0L);
    }

    BOOL SetTabStops(const int& cxEachStop)    // takes an 'int'
    {
        assert(::IsWindow(this->m_hWnd));
        return (BOOL)::SendMessage(this->m_hWnd, EM_SETTABSTOPS, 1, (LPARAM)(LPINT)&cxEachStop);
    }

    void ScrollCaret()
    {
        assert(::IsWindow(this->m_hWnd));
        ::SendMessage(this->m_hWnd, EM_SCROLLCARET, 0, 0L);
    }

    int Scroll(int nScrollAction)
    {
        assert(::IsWindow(this->m_hWnd));
        assert((this->GetStyle() & ES_MULTILINE) != 0);
        LRESULT lRet = ::SendMessage(this->m_hWnd, EM_SCROLL, nScrollAction, 0L);
        if (!(BOOL)D_HIWORD(lRet))
            return -1;   // failed
        return (int)(short)D_LOWORD(lRet);
    }

    void InsertText(int nInsertAfterChar, LPCWSTR lpstrText, BOOL bNoScroll = FALSE, BOOL bCanUndo = FALSE)
    {
        SetSel(nInsertAfterChar, nInsertAfterChar, bNoScroll);
        ReplaceSel(lpstrText, bCanUndo);
    }

    void AppendText(LPCWSTR lpstrText, BOOL bNoScroll = FALSE, BOOL bCanUndo = FALSE)
    {
        InsertText(this->GetWindowTextLength(), lpstrText, bNoScroll, bCanUndo);
    }

    BOOL ShowBalloonTip(PEDITBALLOONTIP pEditBaloonTip)
    {
        assert(::IsWindow(this->m_hWnd));
        return (BOOL)::SendMessage(this->m_hWnd, EM_SHOWBALLOONTIP, 0, (LPARAM)pEditBaloonTip);
    }

    BOOL HideBalloonTip()
    {
        assert(::IsWindow(this->m_hWnd));
        return (BOOL)::SendMessage(this->m_hWnd, EM_HIDEBALLOONTIP, 0, 0L);
    }

#if (_WIN32_WINNT >= _WIN32_WINNT_VISTA)
    DWORD GetHilite() const
    {
        assert(::IsWindow(this->m_hWnd));
        return (DWORD)::SendMessage(this->m_hWnd, EM_GETHILITE, 0, 0L);
    }

    void GetHilite(int& nStartChar, int& nEndChar) const
    {
        assert(::IsWindow(this->m_hWnd));
        DWORD dwRet = (DWORD)::SendMessage(this->m_hWnd, EM_GETHILITE, 0, 0L);
        nStartChar = (int)(short)D_LOWORD(dwRet);
        nEndChar = (int)(short)D_HIWORD(dwRet);
    }

    void SetHilite(int nStartChar, int nEndChar)
    {
        assert(::IsWindow(this->m_hWnd));
        ::SendMessage(this->m_hWnd, EM_SETHILITE, nStartChar, nEndChar);
    }
#endif // (_WIN32_WINNT >= _WIN32_WINNT_VISTA)

    // Clipboard operations
    BOOL Undo()
    {
        assert(::IsWindow(this->m_hWnd));
        return (BOOL)::SendMessage(this->m_hWnd, EM_UNDO, 0, 0L);
    }

    void Clear()
    {
        assert(::IsWindow(this->m_hWnd));
        ::SendMessage(this->m_hWnd, WM_CLEAR, 0, 0L);
    }

    void Copy()
    {
        assert(::IsWindow(this->m_hWnd));
        ::SendMessage(this->m_hWnd, WM_COPY, 0, 0L);
    }

    void Cut()
    {
        assert(::IsWindow(this->m_hWnd));
        ::SendMessage(this->m_hWnd, WM_CUT, 0, 0L);
    }

    void Paste()
    {
        assert(::IsWindow(this->m_hWnd));
        ::SendMessage(this->m_hWnd, WM_PASTE, 0, 0L);
    }

    // New messages added in Windows 10.0.17763
#if defined(NTDDI_VERSION) && defined(NTDDI_WIN10_RS5) && (NTDDI_VERSION >= NTDDI_WIN10_RS5)
    DWORD SetExtendedStyle(DWORD dwStyle, DWORD dwMask)
    {
        assert(::IsWindow(this->m_hWnd));
        return ::SendMessage(this->m_hWnd, EM_SETEXTENDEDSTYLE, dwMask, dwStyle);
    }

    DWORD GetExtendedStyle() const
    {
        assert(::IsWindow(this->m_hWnd));
        return ::SendMessage(this->m_hWnd, EM_GETEXTENDEDSTYLE, 0, 0L);
    }

    BOOL SetEndOfLine(EC_ENDOFLINE eolType)
    {
        assert(::IsWindow(this->m_hWnd));
        return (BOOL)::SendMessage(this->m_hWnd, EM_SETENDOFLINE, eolType, 0L);
    }

    EC_ENDOFLINE GetEndOfLine() const
    {
        assert(::IsWindow(this->m_hWnd));
        return (EC_ENDOFLINE)::SendMessage(this->m_hWnd, EM_GETENDOFLINE, 0, 0L);
    }

    BOOL EnableSearchWeb(BOOL bEnable)
    {
        assert(::IsWindow(this->m_hWnd));
        return (BOOL)::SendMessage(this->m_hWnd, EM_ENABLESEARCHWEB, (WPARAM)bEnable, 0L);
    }

    void SearchWeb()
    {
        assert(::IsWindow(this->m_hWnd));
        ::SendMessage(this->m_hWnd, EM_SEARCHWEB, 0, 0L);
    }

    BOOL SetCaretIndex(DWORD dwCaretIndex)
    {
        assert(::IsWindow(this->m_hWnd));
        return (BOOL)::SendMessage(this->m_hWnd, EM_SETCARETINDEX, dwCaretIndex, 0L);
    }

    DWORD GetCaretIndex() const
    {
        assert(::IsWindow(this->m_hWnd));
        return ::SendMessage(this->m_hWnd, EM_GETCARETINDEX, 0, 0L);
    }

    BOOL GetZoom(int& nNum, int& nDen) const
    {
        assert(::IsWindow(this->m_hWnd));
        return (BOOL)::SendMessage(this->m_hWnd, EM_GETZOOM, (WPARAM)&nNum, (LPARAM)&nDen);
    }

    BOOL SetZoom(int nNum, int nDen)
    {
        assert(::IsWindow(this->m_hWnd));
        assert((nNum >= 0) && (nNum <= 64));
        assert((nDen >= 0) && (nDen <= 64));
        return (BOOL)::SendMessage(this->m_hWnd, EM_SETZOOM, nNum, nDen);
    }

    DWORD GetFileLineFromChar(DWORD dwCharIndex) const
    {
        assert(::IsWindow(this->m_hWnd));
        return ::SendMessage(this->m_hWnd, EM_FILELINEFROMCHAR, dwCharIndex, 0L);
    }

    DWORD GetFileLineIndex(DWORD dwLineNum) const
    {
        assert(::IsWindow(this->m_hWnd));
        return ::SendMessage(this->m_hWnd, EM_FILELINEINDEX, dwLineNum, 0L);
    }

    DWORD GetFileLineLength(DWORD dwCharIndex) const
    {
        assert(::IsWindow(this->m_hWnd));
        return ::SendMessage(this->m_hWnd, EM_FILELINELENGTH, dwCharIndex, 0L);
    }

    DWORD GetFileLine(DWORD dwLineNum, LPWSTR lpstrLine, WORD wLen) const
    {
        assert(::IsWindow(this->m_hWnd));
        WORD* pw = (WORD*)lpstrLine;
        *pw = wLen;
        return ::SendMessage(this->m_hWnd, EM_GETFILELINE, dwLineNum, (LPARAM)lpstrLine);
    }

    BDString GetFileLine(DWORD dwLineNum) const
    {
        BDString strLine;
        DWORD dwCharIndex = GetFileLineIndex(dwLineNum);
        if (dwCharIndex != (DWORD)-1)
        {
            DWORD dwLen = GetFileLineLength(dwCharIndex);
            if (dwLen > 0)
            {
                LPWSTR lpstrLine = strLine.GetBufferSetLength(dwLen);
                assert(GetFileLine(dwLineNum, lpstrLine, (WORD)dwLen) == dwLen);
                strLine.ReleaseBuffer();
            }
        }

        return strLine;
    }

    DWORD GetFileLineCount() const
    {
        assert(::IsWindow(this->m_hWnd));
        return ::SendMessage(this->m_hWnd, EM_GETFILELINECOUNT, 0, 0L);
    }
#endif // defined(NTDDI_VERSION) && defined(NTDDI_WIN10_RS5) && (NTDDI_VERSION >= NTDDI_WIN10_RS5)

    BDString GetWindowText() const
    {
        BDString strRet;
        int nLen = ::GetWindowTextLength(this->m_hWnd);
        if (nLen > 0)
        {
            strRet.GetBufferSetLength(nLen);
            ::GetWindowTextW(this->m_hWnd, (LPWSTR)(LPCWSTR)strRet, nLen + 1);
        }
        else
        {
            strRet.Empty();
        }
        return strRet;
    }
};

typedef BDEditT<BDWnd>   BDEdit;


///////////////////////////////////////////////////////////////////////////////
// BDComboBox - client side for a Windows COMBOBOX control

template <class TBase>
class BDComboBoxT : public TBase
{
public:
    // Constructors
    BDComboBoxT(HWND hWnd = NULL) : TBase(hWnd)
    { }

    BDComboBoxT< TBase >& operator =(HWND hWnd)
    {
        this->m_hWnd = hWnd;
        return *this;
    }

    HWND Create(HWND hWndParent, BDPRect rect = NULL, LPCWSTR szWindowName = NULL,
        DWORD dwStyle = 0, DWORD dwExStyle = 0,
        BDHMenu MenuOrID = 0U, LPVOID lpCreateParam = NULL)
    {
        return TBase::Create(GetWndClassName(), hWndParent, rect.m_lpRect, MenuOrID.m_hMenu, szWindowName, dwStyle, dwExStyle, lpCreateParam);
    }

    // Attributes
    static LPCWSTR GetWndClassName()
    {
        return L"COMBOBOX";
    }

    // for entire combo box
    int GetCount() const
    {
        assert(::IsWindow(this->m_hWnd));
        return (int)::SendMessage(this->m_hWnd, CB_GETCOUNT, 0, 0L);
    }

    int GetCurSel() const
    {
        assert(::IsWindow(this->m_hWnd));
        return (int)::SendMessage(this->m_hWnd, CB_GETCURSEL, 0, 0L);
    }

    int SetCurSel(int nSelect)
    {
        assert(::IsWindow(this->m_hWnd));
        return (int)::SendMessage(this->m_hWnd, CB_SETCURSEL, nSelect, 0L);
    }

    LCID GetLocale() const
    {
        assert(::IsWindow(this->m_hWnd));
        return (LCID)::SendMessage(this->m_hWnd, CB_GETLOCALE, 0, 0L);
    }

    LCID SetLocale(LCID nNewLocale)
    {
        assert(::IsWindow(this->m_hWnd));
        return (LCID)::SendMessage(this->m_hWnd, CB_SETLOCALE, (WPARAM)nNewLocale, 0L);
    }

    int GetTopIndex() const
    {
        assert(::IsWindow(this->m_hWnd));
        return (int)::SendMessage(this->m_hWnd, CB_GETTOPINDEX, 0, 0L);
    }

    int SetTopIndex(int nIndex)
    {
        assert(::IsWindow(this->m_hWnd));
        return (int)::SendMessage(this->m_hWnd, CB_SETTOPINDEX, nIndex, 0L);
    }

    UINT GetHorizontalExtent() const
    {
        assert(::IsWindow(this->m_hWnd));
        return (UINT)::SendMessage(this->m_hWnd, CB_GETHORIZONTALEXTENT, 0, 0L);
    }

    void SetHorizontalExtent(UINT nExtent)
    {
        assert(::IsWindow(this->m_hWnd));
        ::SendMessage(this->m_hWnd, CB_SETHORIZONTALEXTENT, nExtent, 0L);
    }

    int GetDroppedWidth() const
    {
        assert(::IsWindow(this->m_hWnd));
        return (int)::SendMessage(this->m_hWnd, CB_GETDROPPEDWIDTH, 0, 0L);
    }

    int SetDroppedWidth(UINT nWidth)
    {
        assert(::IsWindow(this->m_hWnd));
        return (int)::SendMessage(this->m_hWnd, CB_SETDROPPEDWIDTH, nWidth, 0L);
    }

    BOOL GetComboBoxInfo(PCOMBOBOXINFO pComboBoxInfo) const
    {
        assert(::IsWindow(this->m_hWnd));
        return (BOOL)::SendMessage(this->m_hWnd, CB_GETCOMBOBOXINFO, 0, (LPARAM)pComboBoxInfo);
    }

    // for edit control
    DWORD GetEditSel() const
    {
        assert(::IsWindow(this->m_hWnd));
        return (DWORD)::SendMessage(this->m_hWnd, CB_GETEDITSEL, 0, 0L);
    }

    BOOL SetEditSel(int nStartChar, int nEndChar)
    {
        assert(::IsWindow(this->m_hWnd));
        return (BOOL)::SendMessage(this->m_hWnd, CB_SETEDITSEL, 0, MAKELONG(nStartChar, nEndChar));
    }

    // for combobox item
    DWORD_PTR GetItemData(int nIndex) const
    {
        assert(::IsWindow(this->m_hWnd));
        return (DWORD_PTR)::SendMessage(this->m_hWnd, CB_GETITEMDATA, nIndex, 0L);
    }

    int SetItemData(int nIndex, DWORD_PTR dwItemData)
    {
        assert(::IsWindow(this->m_hWnd));
        return (int)::SendMessage(this->m_hWnd, CB_SETITEMDATA, nIndex, (LPARAM)dwItemData);
    }

    void* GetItemDataPtr(int nIndex) const
    {
        assert(::IsWindow(this->m_hWnd));
        return (void*)GetItemData(nIndex);
    }

    int SetItemDataPtr(int nIndex, void* pData)
    {
        assert(::IsWindow(this->m_hWnd));
        return SetItemData(nIndex, (DWORD_PTR)pData);
    }

    int GetLBText(int nIndex, LPWSTR lpszText) const
    {
        assert(::IsWindow(this->m_hWnd));
        return (int)::SendMessage(this->m_hWnd, CB_GETLBTEXT, nIndex, (LPARAM)lpszText);
    }

    int GetLBText(int nIndex, BDString& strText) const
    {
        assert(::IsWindow(this->m_hWnd));
        int cchLen = GetLBTextLen(nIndex);
        if (cchLen == CB_ERR)
            return CB_ERR;
        int nRet = CB_ERR;
        LPWSTR lpstr = strText.GetBufferSetLength(cchLen);
        if (lpstr != NULL)
        {
            nRet = GetLBText(nIndex, lpstr);
            strText.ReleaseBuffer();
        }
        return nRet;
    }

    int GetLBTextLen(int nIndex) const
    {
        assert(::IsWindow(this->m_hWnd));
        return (int)::SendMessage(this->m_hWnd, CB_GETLBTEXTLEN, nIndex, 0L);
    }

    int GetItemHeight(int nIndex) const
    {
        assert(::IsWindow(this->m_hWnd));
        return (int)::SendMessage(this->m_hWnd, CB_GETITEMHEIGHT, nIndex, 0L);
    }

    int SetItemHeight(int nIndex, UINT cyItemHeight)
    {
        assert(::IsWindow(this->m_hWnd));
        return (int)::SendMessage(this->m_hWnd, CB_SETITEMHEIGHT, nIndex, MAKELONG(cyItemHeight, 0));
    }

    BOOL GetExtendedUI() const
    {
        assert(::IsWindow(this->m_hWnd));
        return (BOOL)::SendMessage(this->m_hWnd, CB_GETEXTENDEDUI, 0, 0L);
    }

    int SetExtendedUI(BOOL bExtended = TRUE)
    {
        assert(::IsWindow(this->m_hWnd));
        return (int)::SendMessage(this->m_hWnd, CB_SETEXTENDEDUI, bExtended, 0L);
    }

    void GetDroppedControlRect(LPRECT lprect) const
    {
        assert(::IsWindow(this->m_hWnd));
        ::SendMessage(this->m_hWnd, CB_GETDROPPEDCONTROLRECT, 0, (LPARAM)lprect);
    }

    BOOL GetDroppedState() const
    {
        assert(::IsWindow(this->m_hWnd));
        return (BOOL)::SendMessage(this->m_hWnd, CB_GETDROPPEDSTATE, 0, 0L);
    }

    int GetMinVisible() const
    {
        assert(::IsWindow(this->m_hWnd));
        return (int)::SendMessage(this->m_hWnd, CB_GETMINVISIBLE, 0, 0L);
    }

    BOOL SetMinVisible(int nMinVisible)
    {
        assert(::IsWindow(this->m_hWnd));
        return (BOOL)::SendMessage(this->m_hWnd, CB_SETMINVISIBLE, nMinVisible, 0L);
    }

    // Vista only
    BOOL GetCueBannerText(LPWSTR lpwText, int cchText) const
    {
        assert(::IsWindow(this->m_hWnd));
        return (BOOL)::SendMessage(this->m_hWnd, CB_GETCUEBANNER, (WPARAM)lpwText, cchText);
    }

    // Vista only
    BOOL SetCueBannerText(LPCWSTR lpcwText)
    {
        assert(::IsWindow(this->m_hWnd));
        return (BOOL)::SendMessage(this->m_hWnd, CB_SETCUEBANNER, 0, (LPARAM)lpcwText);
    }

    // Operations
    int InitStorage(int nItems, UINT nBytes)
    {
        assert(::IsWindow(this->m_hWnd));
        return (int)::SendMessage(this->m_hWnd, CB_INITSTORAGE, (WPARAM)nItems, nBytes);
    }

    void ResetContent()
    {
        assert(::IsWindow(this->m_hWnd));
        ::SendMessage(this->m_hWnd, CB_RESETCONTENT, 0, 0L);
    }

    // for edit control
    BOOL LimitText(int nMaxChars)
    {
        assert(::IsWindow(this->m_hWnd));
        return (BOOL)::SendMessage(this->m_hWnd, CB_LIMITTEXT, nMaxChars, 0L);
    }

    // for drop-down combo boxes
    void ShowDropDown(BOOL bShowIt = TRUE)
    {
        assert(::IsWindow(this->m_hWnd));
        ::SendMessage(this->m_hWnd, CB_SHOWDROPDOWN, bShowIt, 0L);
    }

    // manipulating listbox items
    int AddString(LPCWSTR lpszString)
    {
        assert(::IsWindow(this->m_hWnd));
        return (int)::SendMessage(this->m_hWnd, CB_ADDSTRING, 0, (LPARAM)lpszString);
    }

    int DeleteString(UINT nIndex)
    {
        assert(::IsWindow(this->m_hWnd));
        return (int)::SendMessage(this->m_hWnd, CB_DELETESTRING, nIndex, 0L);
    }

    int InsertString(int nIndex, LPCWSTR lpszString)
    {
        assert(::IsWindow(this->m_hWnd));
        return (int)::SendMessage(this->m_hWnd, CB_INSERTSTRING, nIndex, (LPARAM)lpszString);
    }

    int Dir(UINT attr, LPCWSTR lpszWildCard)
    {
        assert(::IsWindow(this->m_hWnd));
        return (int)::SendMessage(this->m_hWnd, CB_DIR, attr, (LPARAM)lpszWildCard);
    }

    // selection helpers
    int FindString(int nStartAfter, LPCWSTR lpszString) const
    {
        assert(::IsWindow(this->m_hWnd));
        return (int)::SendMessage(this->m_hWnd, CB_FINDSTRING, nStartAfter, (LPARAM)lpszString);
    }

    int FindStringExact(int nIndexStart, LPCWSTR lpszFind) const
    {
        assert(::IsWindow(this->m_hWnd));
        return (int)::SendMessage(this->m_hWnd, CB_FINDSTRINGEXACT, nIndexStart, (LPARAM)lpszFind);
    }

    int SelectString(int nStartAfter, LPCWSTR lpszString)
    {
        assert(::IsWindow(this->m_hWnd));
        return (int)::SendMessage(this->m_hWnd, CB_SELECTSTRING, nStartAfter, (LPARAM)lpszString);
    }

    // Clipboard operations
    void Clear()
    {
        assert(::IsWindow(this->m_hWnd));
        ::SendMessage(this->m_hWnd, WM_CLEAR, 0, 0L);
    }

    void Copy()
    {
        assert(::IsWindow(this->m_hWnd));
        ::SendMessage(this->m_hWnd, WM_COPY, 0, 0L);
    }

    void Cut()
    {
        assert(::IsWindow(this->m_hWnd));
        ::SendMessage(this->m_hWnd, WM_CUT, 0, 0L);
    }

    void Paste()
    {
        assert(::IsWindow(this->m_hWnd));
        ::SendMessage(this->m_hWnd, WM_PASTE, 0, 0L);
    }
};

typedef BDComboBoxT<BDWnd>  BDComboBox;


///////////////////////////////////////////////////////////////////////////////
// BDScrollBar - client side for a Windows SCROLLBAR control

template <class TBase>
class BDScrollBarT : public TBase
{
public:
    // Constructors
    BDScrollBarT(HWND hWnd = NULL) : TBase(hWnd)
    { }

    BDScrollBarT< TBase >& operator =(HWND hWnd)
    {
        this->m_hWnd = hWnd;
        return *this;
    }

    HWND Create(HWND hWndParent, BDPRect rect = NULL, LPCWSTR szWindowName = NULL,
        DWORD dwStyle = 0, DWORD dwExStyle = 0,
        BDHMenu MenuOrID = 0U, LPVOID lpCreateParam = NULL)
    {
        return TBase::Create(GetWndClassName(), hWndParent, rect.m_lpRect, BDHMenu(MenuOrID.m_hMenu), szWindowName, dwStyle, dwExStyle, lpCreateParam);
    }

    // Attributes
    static LPCWSTR GetWndClassName()
    {
        return L"SCROLLBAR";
    }

    int GetScrollPos() const
    {
        assert(::IsWindow(this->m_hWnd));
        return ::GetScrollPos(this->m_hWnd, SB_CTL);
    }

    int SetScrollPos(int nPos, BOOL bRedraw = TRUE)
    {
        assert(::IsWindow(this->m_hWnd));
        return ::SetScrollPos(this->m_hWnd, SB_CTL, nPos, bRedraw);
    }

    void GetScrollRange(LPINT lpMinPos, LPINT lpMaxPos) const
    {
        assert(::IsWindow(this->m_hWnd));
        ::GetScrollRange(this->m_hWnd, SB_CTL, lpMinPos, lpMaxPos);
    }

    void SetScrollRange(int nMinPos, int nMaxPos, BOOL bRedraw = TRUE)
    {
        assert(::IsWindow(this->m_hWnd));
        ::SetScrollRange(this->m_hWnd, SB_CTL, nMinPos, nMaxPos, bRedraw);
    }

    BOOL GetScrollInfo(LPSCROLLINFO lpScrollInfo) const
    {
        assert(::IsWindow(this->m_hWnd));
        return ::GetScrollInfo(this->m_hWnd, SB_CTL, lpScrollInfo);
    }

    int SetScrollInfo(LPSCROLLINFO lpScrollInfo, BOOL bRedraw = TRUE)
    {
        assert(::IsWindow(this->m_hWnd));
        return ::SetScrollInfo(this->m_hWnd, SB_CTL, lpScrollInfo, bRedraw);
    }

    int GetScrollLimit() const
    {
        SCROLLINFO info = { sizeof(SCROLLINFO), SIF_RANGE | SIF_PAGE };
        ::GetScrollInfo(this->m_hWnd, SB_CTL, &info);
        if (info.nPage > 1)
            info.nMax -= info.nPage - 1;
        return info.nMax;
    }

    BOOL GetScrollBarInfo(PSCROLLBARINFO pScrollBarInfo) const
    {
        assert(::IsWindow(this->m_hWnd));
        return (BOOL)::SendMessage(this->m_hWnd, SBM_GETSCROLLBARINFO, 0, (LPARAM)pScrollBarInfo);
    }

    // Operations
    void ShowScrollBar(BOOL bShow = TRUE)
    {
        assert(::IsWindow(this->m_hWnd));
        ::ShowScrollBar(this->m_hWnd, SB_CTL, bShow);
    }

    BOOL EnableScrollBar(UINT nArrowFlags = ESB_ENABLE_BOTH)
    {
        assert(::IsWindow(this->m_hWnd));
        return ::EnableScrollBar(this->m_hWnd, SB_CTL, nArrowFlags);
    }
};

typedef BDScrollBarT<BDWnd>   BDScrollBar;

