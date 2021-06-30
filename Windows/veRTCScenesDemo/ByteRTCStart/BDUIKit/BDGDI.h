//
//  BDGDI.h
//
//  Copyright 2020. All rights reserved.
//

#pragma once

#include "BDMisc.h"
#include "BDWinApp.h"
#include "BDBase.h"
#include <CommCtrl.h>

// required libraries
#if !defined(D_NO_MSIMG)
#pragma comment(lib, "msimg32.lib")
#endif

#if !defined(D_NO_OPENGL)
#pragma comment(lib, "opengl32.lib")
#endif

///////////////////////////////////////////////////////////////////////////////
// Classes in this file:
//
// BDPenT<t_bManaged> BDPenHandle BDPen - HPEN wrapper
// BDBrushT<t_bManaged> BDBrushHandle BDBrush - HBRUSH wrapper
// BDLogFont - LOGFONT struct wrapper
// BDFontT<t_bManaged> BDFontHandle BDFont - HFONT wrapper
// BDBitmapT<t_bManaged> BDBitmapHandle - HBITMAP wrapper
// BDRgnT<t_bManaged> BDRgnHandle BDRgn - HRGN wrapper 
// BDDCT<t_bManaged> BDDCHandle BDDC - HDC wrapper
// BDPaintDC - ::BeginPaint ::EndPaint
// BDClientDC BDClientDCEx - ::GetDC ::ReleaseDC
// BDWindowDC - ::GetWindowDC ::ReleaseDC
// BDMemoryDC - ::CreateCompatibleDC 
//
// Global functions:
//   GetBitmapResourceInfo()
//   GetBitmapResourceBitsPerPixel()
//   IsAlphaBitmapResource()
//   IsDib16()
//   GetDibColorTableSize()
//   GetDibNumColors(),
//   GetDibBitmap()
//   CopyBitmap()
//   CreatePackedDib16()
//   SetClipboardDib16()
//   GetClipboardDib()


///////////////////////////////////////////////////////////////////////////////
// Bitmap resource helpers to extract bitmap information for a bitmap resource

inline LPBITMAPINFOHEADER GetBitmapResourceInfo(HMODULE hModule, BDResStr image)
{
    HRSRC hResource = ::FindResource(hModule, image.m_lpstr, RT_BITMAP);
    assert(hResource != NULL);
    HGLOBAL hGlobal = ::LoadResource(hModule, hResource);
    assert(hGlobal != NULL);
    LPBITMAPINFOHEADER pBitmapInfoHeader = (LPBITMAPINFOHEADER)::LockResource(hGlobal);
    assert(pBitmapInfoHeader != NULL);
    return pBitmapInfoHeader;
}

inline WORD GetBitmapResourceBitsPerPixel(HMODULE hModule, BDResStr image)
{
    LPBITMAPINFOHEADER pBitmapInfoHeader = GetBitmapResourceInfo(hModule, image);
    assert(pBitmapInfoHeader != NULL);
    return pBitmapInfoHeader->biBitCount;
}

inline WORD GetBitmapResourceBitsPerPixel(BDResStr image)
{
    return GetBitmapResourceBitsPerPixel(BDWinApp::GetResInstance(), image);
}

///////////////////////////////////////////////////////////////////////////////
// 32-bit (alpha channel) bitmap resource helper

// Note: 32-bit (alpha channel) images work only on Windows XP with Common Controls version 6.
// If you want your app to work on older version of Windows, load non-alpha images if Common
// Controls version is less than 6.

inline bool IsAlphaBitmapResource(BDResStr image)
{
    return (GetBitmapResourceBitsPerPixel(image) == 32);
}


///////////////////////////////////////////////////////////////////////////////
// BDPen
#define BD_WHITE_PEN  (HPEN)::GetStockObject(WHITE_PEN)
#define BD_BLACK_PEN  (HPEN)::GetStockObject(BLACK_PEN)

template <bool t_bManaged>
class BDPenT
{
public:
    // Data members
    HPEN m_hPen;

    // Constructor/destructor/operators
    BDPenT(HPEN hPen = NULL) : m_hPen(hPen)
    { }

    ~BDPenT()
    {
        if (t_bManaged && m_hPen != NULL)
            DeleteObject();
    }

    BDPenT<t_bManaged>& operator =(HPEN hPen)
    {
        Attach(hPen);
        return *this;
    }

    void Attach(HPEN hPen)
    {
        if (t_bManaged && m_hPen != NULL && m_hPen != hPen)
            ::DeleteObject(m_hPen);
        m_hPen = hPen;
    }

    HPEN Detach()
    {
        HPEN hPen = m_hPen;
        m_hPen = NULL;
        return hPen;
    }

    operator HPEN() const { return m_hPen; }

    bool IsNull() const { return (m_hPen == NULL); }

    // Create methods
    HPEN CreatePen(int nPenStyle, int nWidth, COLORREF crColor)
    {
        assert(m_hPen == NULL);
        m_hPen = ::CreatePen(nPenStyle, nWidth, crColor);
        return m_hPen;
    }

    HPEN CreatePen(int nPenStyle, int nWidth, const LOGBRUSH* pLogBrush, int nStyleCount = 0, const DWORD* lpStyle = NULL)
    {
        assert(m_hPen == NULL);
        m_hPen = ::ExtCreatePen(nPenStyle, nWidth, pLogBrush, nStyleCount, lpStyle);
        return m_hPen;
    }

    // If your program uses a lot of different pens that you initialize in your source code,
    // this method is probably more efficient. 
    HPEN CreatePenIndirect(LPLOGPEN lpLogPen)
    {
        assert(m_hPen == NULL);
        m_hPen = ::CreatePenIndirect(lpLogPen);
        return m_hPen;
    }

    BOOL DeleteObject()
    {
        assert(m_hPen != NULL);
        BOOL bRet = ::DeleteObject(m_hPen);
        if (bRet)
            m_hPen = NULL;
        return bRet;
    }

    // Attributes
    int GetLogPen(LOGPEN* pLogPen) const
    {
        assert(m_hPen != NULL);
        return ::GetObject(m_hPen, sizeof(LOGPEN), pLogPen);
    }

    bool GetLogPen(LOGPEN& LogPen) const
    {
        assert(m_hPen != NULL);
        return (::GetObject(m_hPen, sizeof(LOGPEN), &LogPen) == sizeof(LOGPEN));
    }

    int GetExtLogPen(EXTLOGPEN* pLogPen, int nSize = sizeof(EXTLOGPEN)) const
    {
        assert(m_hPen != NULL);
        return ::GetObject(m_hPen, nSize, pLogPen);
    }

    bool GetExtLogPen(EXTLOGPEN& ExtLogPen, int nSize = sizeof(EXTLOGPEN)) const
    {
        assert(m_hPen != NULL);
        int nRet = ::GetObject(m_hPen, nSize, &ExtLogPen);
        return ((nRet > 0) && (nRet <= nSize));
    }
};

typedef BDPenT<false>   BDPenHandle;
typedef BDPenT<true>    BDPen;


///////////////////////////////////////////////////////////////////////////////
// BDBrush
#define BD_WHITE_BRUSH  (HBRUSH)::GetStockObject(WHITE_BRUSH)
#define BD_LTGRAY_BRUSH (HBRUSH)::GetStockObject(LTGRAY_BRUSH)
#define BD_GRAY_BRUSH   (HBRUSH)::GetStockObject(GRAY_BRUSH)
#define BD_DKGRAY_BRUSH (HBRUSH)::GetStockObject(DKGRAY_BRUSH)
#define BD_BLACK_BRUSH  (HBRUSH)::GetStockObject(BLACK_BRUSH)
#define BD_NULL_BRUSH   (HBRUSH)::GetStockObject(NULL_BRUSH)
#define BD_HOLLOW_BRUSH (HBRUSH)::GetStockObject(HOLLOW_BRUSH)

template <bool t_bManaged>
class BDBrushT
{
public:
    // Data members
    HBRUSH m_hBrush;

    // Constructor/destructor/operators
    BDBrushT(HBRUSH hBrush = NULL) : m_hBrush(hBrush)
    { }

    ~BDBrushT()
    {
        if (t_bManaged && m_hBrush != NULL)
            DeleteObject();
    }

    BDBrushT<t_bManaged>& operator =(HBRUSH hBrush)
    {
        Attach(hBrush);
        return *this;
    }

    void Attach(HBRUSH hBrush)
    {
        if (t_bManaged && m_hBrush != NULL && m_hBrush != hBrush)
            ::DeleteObject(m_hBrush);
        m_hBrush = hBrush;
    }

    HBRUSH Detach()
    {
        HBRUSH hBrush = m_hBrush;
        m_hBrush = NULL;
        return hBrush;
    }

    operator HBRUSH() const { return m_hBrush; }

    bool IsNull() const { return (m_hBrush == NULL); }

    // Create methods
    HBRUSH CreateSolidBrush(COLORREF crColor)
    {
        assert(m_hBrush == NULL);
        m_hBrush = ::CreateSolidBrush(crColor);
        return m_hBrush;
    }

    HBRUSH CreateHatchBrush(int nIndex, COLORREF crColor)
    {
        assert(m_hBrush == NULL);
        m_hBrush = ::CreateHatchBrush(nIndex, crColor);
        return m_hBrush;
    }

    HBRUSH CreateBrushIndirect(const LOGBRUSH* lpLogBrush)
    {
        assert(m_hBrush == NULL);
        m_hBrush = ::CreateBrushIndirect(lpLogBrush);
        return m_hBrush;
    }

    HBRUSH CreatePatternBrush(HBITMAP hBitmap)
    {
        assert(m_hBrush == NULL);
        m_hBrush = ::CreatePatternBrush(hBitmap);
        return m_hBrush;
    }

    HBRUSH CreateDIBPatternBrush(HGLOBAL hPackedDIB, UINT nUsage)
    {
        assert(hPackedDIB != NULL);
        const void* lpPackedDIB = GlobalLock(hPackedDIB);
        assert(lpPackedDIB != NULL);
        m_hBrush = ::CreateDIBPatternBrushPt(lpPackedDIB, nUsage);
        GlobalUnlock(hPackedDIB);
        return m_hBrush;
    }

    HBRUSH CreateDIBPatternBrush(const void* lpPackedDIB, UINT nUsage)
    {
        assert(m_hBrush == NULL);
        m_hBrush = ::CreateDIBPatternBrushPt(lpPackedDIB, nUsage);
        return m_hBrush;
    }

    HBRUSH CreateSysColorBrush(int nIndex)
    {
        assert(m_hBrush == NULL);
        m_hBrush = ::GetSysColorBrush(nIndex);
        return m_hBrush;
    }

    BOOL DeleteObject()
    {
        assert(m_hBrush != NULL);
        BOOL bRet = ::DeleteObject(m_hBrush);
        if (bRet)
            m_hBrush = NULL;
        return bRet;
    }

    // Attributes
    int GetLogBrush(LOGBRUSH* pLogBrush) const
    {
        assert(m_hBrush != NULL);
        return ::GetObject(m_hBrush, sizeof(LOGBRUSH), pLogBrush);
    }

    bool GetLogBrush(LOGBRUSH& LogBrush) const
    {
        assert(m_hBrush != NULL);
        return (::GetObject(m_hBrush, sizeof(LOGBRUSH), &LogBrush) == sizeof(LOGBRUSH));
    }
};

typedef BDBrushT<false>   BDBrushHandle;
typedef BDBrushT<true>    BDBrush;


///////////////////////////////////////////////////////////////////////////////
// BDFont
#define BD_OEM_FIXED_FONT      (HFONT)::GetStockObject(OEM_FIXED_FONT)
#define BD_ANSI_FIXED_FONT     (HFONT)::GetStockObject(ANSI_FIXED_FONT)
#define BD_ANSI_VAR_FONT       (HFONT)::GetStockObject(ANSI_VAR_FONT)
#define BD_SYSTEM_FONT         (HFONT)::GetStockObject(SYSTEM_FONT)
#define BD_DEVICE_DEFAULT_FONT (HFONT)::GetStockObject(DEVICE_DEFAULT_FONT)
#define BD_SYSTEM_FIXED_FONT   (HFONT)::GetStockObject(SYSTEM_FIXED_FONT)
#define BD_DEFAULT_GUI_FONT      (HFONT)::GetStockObject(DEFAULT_GUI_FONT)

class BDLogFont : public LOGFONT
{
public:
    BDLogFont()
    {
        memset(this, 0, sizeof(LOGFONT));
    }

    BDLogFont(const LOGFONT& lf)
    {
        Copy(&lf);
    }

    BDLogFont(HFONT hFont)
    {
        assert(::GetObjectType(hFont) == OBJ_FONT);
        ::GetObject(hFont, sizeof(LOGFONT), (LOGFONT*)this);
    }

    HFONT CreateFontIndirect()
    {
        return ::CreateFontIndirect(this);
    }

    void SetBold()
    {
        lfWeight = FW_BOLD;
    }

    bool IsBold() const
    {
        return (lfWeight >= FW_BOLD);
    }

    void MakeBolder(int iScale = 1)
    {
        lfWeight += FW_BOLD * iScale;
    }

    void MakeLarger(int iScale)
    {
        if (lfHeight > 0)
            lfHeight += iScale;
        else
            lfHeight -= iScale;
    }

    void SetHeight(LONG nPointSize, HDC hDC = NULL)
    {
        HDC hDC1 = (hDC != NULL) ? hDC : ::GetDC(NULL);
        // For MM_TEXT mapping mode
        lfHeight = -::MulDiv(nPointSize, ::GetDeviceCaps(hDC1, LOGPIXELSY), 72);
        if (hDC == NULL)
            ::ReleaseDC(NULL, hDC1);
    }

    LONG GetHeight(HDC hDC = NULL) const
    {
        HDC hDC1 = (hDC != NULL) ? hDC : ::GetDC(NULL);
        // For MM_TEXT mapping mode
        LONG nPointSize = ::MulDiv(-lfHeight, 72, ::GetDeviceCaps(hDC1, LOGPIXELSY));
        if (hDC == NULL)
            ::ReleaseDC(NULL, hDC1);

        return nPointSize;
    }

    LONG GetDeciPointHeight(HDC hDC = NULL) const
    {
        HDC hDC1 = (hDC != NULL) ? hDC : ::GetDC(NULL);

        POINT ptOrg = { 0, 0 };
        ::DPtoLP(hDC1, &ptOrg, 1);
        POINT pt = { 0, 0 };
        pt.y = abs(lfHeight) + ptOrg.y;
        ::LPtoDP(hDC1, &pt, 1);
        LONG nDeciPoint = ::MulDiv(pt.y, 720, ::GetDeviceCaps(hDC1, LOGPIXELSY));   // 72 points/inch, 10 decipoints/point
        if (hDC == NULL)
            ::ReleaseDC(NULL, hDC1);

        return nDeciPoint;
    }

    void SetHeightFromDeciPoint(LONG nDeciPtHeight, HDC hDC = NULL)
    {
        HDC hDC1 = (hDC != NULL) ? hDC : ::GetDC(NULL);
        POINT pt = { 0, 0 };
        pt.y = ::MulDiv(::GetDeviceCaps(hDC1, LOGPIXELSY), nDeciPtHeight, 720);   // 72 points/inch, 10 decipoints/point
        ::DPtoLP(hDC1, &pt, 1);
        POINT ptOrg = { 0, 0 };
        ::DPtoLP(hDC1, &ptOrg, 1);
        lfHeight = -abs(pt.y - ptOrg.y);
        if (hDC == NULL)
            ::ReleaseDC(NULL, hDC1);
    }

    void SetCaptionFont()
    {
        NONCLIENTMETRICS ncm = { sizeof(NONCLIENTMETRICS) };
        assert(::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(ncm), &ncm, 0));
        Copy(&ncm.lfCaptionFont);
    }

    void SetMenuFont()
    {
        NONCLIENTMETRICS ncm = { sizeof(NONCLIENTMETRICS) };
        assert(::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(ncm), &ncm, 0));
        Copy(&ncm.lfMenuFont);
    }

    void SetStatusFont()
    {
        NONCLIENTMETRICS ncm = { sizeof(NONCLIENTMETRICS) };
        assert(::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(ncm), &ncm, 0));
        Copy(&ncm.lfStatusFont);
    }

    void SetMessageBoxFont()
    {
        NONCLIENTMETRICS ncm = { sizeof(NONCLIENTMETRICS) };
        assert(::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(ncm), &ncm, 0));
        Copy(&ncm.lfMessageFont);
    }

    void Copy(const LOGFONT* pLogFont)
    {
        assert(pLogFont != NULL);
        *(LOGFONT*)this = *pLogFont;
    }

    BDLogFont& operator =(const BDLogFont& src)
    {
        Copy(&src);
        return *this;
    }

    BDLogFont& operator =(const LOGFONT& src)
    {
        Copy(&src);
        return *this;
    }

    BDLogFont& operator =(HFONT hFont)
    {
        assert(::GetObjectType(hFont) == OBJ_FONT);
        ::GetObject(hFont, sizeof(LOGFONT), (LOGFONT*)this);
        return *this;
    }

    bool operator ==(const LOGFONT& logfont) const
    {
        return((logfont.lfHeight == lfHeight) &&
            (logfont.lfWidth == lfWidth) &&
            (logfont.lfEscapement == lfEscapement) &&
            (logfont.lfOrientation == lfOrientation) &&
            (logfont.lfWeight == lfWeight) &&
            (logfont.lfItalic == lfItalic) &&
            (logfont.lfUnderline == lfUnderline) &&
            (logfont.lfStrikeOut == lfStrikeOut) &&
            (logfont.lfCharSet == lfCharSet) &&
            (logfont.lfOutPrecision == lfOutPrecision) &&
            (logfont.lfClipPrecision == lfClipPrecision) &&
            (logfont.lfQuality == lfQuality) &&
            (logfont.lfPitchAndFamily == lfPitchAndFamily) &&
            (lstrcmp(logfont.lfFaceName, lfFaceName) == 0));
    }
};


template <bool t_bManaged>
class BDFontT
{
public:
    // Data members
    HFONT m_hFont;

    // Constructor/destructor/operators
    BDFontT(HFONT hFont = NULL) : m_hFont(hFont)
    { }

    ~BDFontT()
    {
        if (t_bManaged && m_hFont != NULL)
            DeleteObject();
    }

    BDFontT<t_bManaged>& operator =(HFONT hFont)
    {
        Attach(hFont);
        return *this;
    }

    void Attach(HFONT hFont)
    {
        if (t_bManaged && m_hFont != NULL && m_hFont != hFont)
            ::DeleteObject(m_hFont);
        m_hFont = hFont;
    }

    HFONT Detach()
    {
        HFONT hFont = m_hFont;
        m_hFont = NULL;
        return hFont;
    }

    operator HFONT() const { return m_hFont; }

    bool IsNull() const { return (m_hFont == NULL); }

    // Create methods
    HFONT CreateFontIndirect(const LOGFONT* lpLogFont)
    {
        assert(m_hFont == NULL);
        m_hFont = ::CreateFontIndirect(lpLogFont);
        return m_hFont;
    }

    HFONT CreateFontIndirectEx(CONST ENUMLOGFONTEXDV* penumlfex)
    {
        assert(m_hFont == NULL);
        m_hFont = ::CreateFontIndirectEx(penumlfex);
        return m_hFont;
    }

    HFONT CreateFont(int nHeight, int nWidth, int nEscapement,
        int nOrientation, int nWeight, BYTE bItalic, BYTE bUnderline,
        BYTE cStrikeOut, BYTE nCharSet, BYTE nOutPrecision,
        BYTE nClipPrecision, BYTE nQuality, BYTE nPitchAndFamily,
        LPCTSTR lpszFacename)
    {
        assert(m_hFont == NULL);
        m_hFont = ::CreateFont(nHeight, nWidth, nEscapement,
            nOrientation, nWeight, bItalic, bUnderline, cStrikeOut,
            nCharSet, nOutPrecision, nClipPrecision, nQuality,
            nPitchAndFamily, lpszFacename);
        return m_hFont;
    }

    HFONT CreatePointFont(int nPointSize, LPCTSTR lpszFaceName, HDC hDC = NULL, bool bBold = false, bool bItalic = false)
    {
        LOGFONT logFont = {};
        logFont.lfCharSet = DEFAULT_CHARSET;
        logFont.lfHeight = nPointSize;
        wcsncpy_s(logFont.lfFaceName, _countof(logFont.lfFaceName), lpszFaceName, _TRUNCATE);

        if (bBold)
            logFont.lfWeight = FW_BOLD;
        if (bItalic)
            logFont.lfItalic = (BYTE)TRUE;

        return CreatePointFontIndirect(&logFont, hDC);
    }

    HFONT CreatePointFontIndirect(const LOGFONT* lpLogFont, HDC hDC = NULL)
    {
        HDC hDC1 = (hDC != NULL) ? hDC : ::GetDC(NULL);

        // convert nPointSize to logical units based on hDC
        LOGFONT logFont = *lpLogFont;
        POINT pt = { 0, 0 };
        pt.y = ::MulDiv(::GetDeviceCaps(hDC1, LOGPIXELSY), logFont.lfHeight, 720);   // 72 points/inch, 10 decipoints/point
        ::DPtoLP(hDC1, &pt, 1);
        POINT ptOrg = { 0, 0 };
        ::DPtoLP(hDC1, &ptOrg, 1);
        logFont.lfHeight = -abs(pt.y - ptOrg.y);

        if (hDC == NULL)
            ::ReleaseDC(NULL, hDC1);

        return CreateFontIndirect(&logFont);
    }

    BOOL DeleteObject()
    {
        assert(m_hFont != NULL);
        BOOL bRet = ::DeleteObject(m_hFont);
        if (bRet)
            m_hFont = NULL;
        return bRet;
    }

    // Control font helper - default font for controls not in a dialog
    // (NOTE: Caller owns the font, and should destroy it when it's no longer needed)
    static inline HFONT CreateControlFont()
    {
        LOGFONT lf = { 0 };
        ::SystemParametersInfo(SPI_GETICONTITLELOGFONT, sizeof(LOGFONT), &lf, 0);
        HFONT hFont = ::CreateFontIndirect(&lf);
        assert(hFont != NULL);
        return hFont;
    }

    // Bold font helper
    // (NOTE: Caller owns the font, and should destroy it when it's no longer needed)
    static inline HFONT CreateBoldFont(HFONT hFont = NULL)
    {
        LOGFONT lf = { 0 };
        if (hFont == NULL)
        {
            assert(::SystemParametersInfo(SPI_GETICONTITLELOGFONT, sizeof(LOGFONT), &lf, 0) != FALSE);
        }
        else
        {
            assert(::GetObject(hFont, sizeof(LOGFONT), &lf) == sizeof(LOGFONT));
        }
        lf.lfWeight = FW_BOLD;
        HFONT hFontBold = ::CreateFontIndirect(&lf);
        assert(hFontBold != NULL);
        return hFontBold;
    }

    // Attributes
    int GetLogFont(LOGFONT* pLogFont) const
    {
        assert(m_hFont != NULL);
        return ::GetObject(m_hFont, sizeof(LOGFONT), pLogFont);
    }

    bool GetLogFont(LOGFONT& LogFont) const
    {
        assert(m_hFont != NULL);
        return (::GetObject(m_hFont, sizeof(LOGFONT), &LogFont) == sizeof(LOGFONT));
    }
};

typedef BDFontT<false>   BDFontHandle;
typedef BDFontT<true>    BDFont;


///////////////////////////////////////////////////////////////////////////////
// DBitmap

template <bool t_bManaged>
class BDBitmapT
{
public:
    // Data members
    HBITMAP m_hBitmap;

    // Constructor/destructor/operators
    BDBitmapT(HBITMAP hBitmap = NULL) : m_hBitmap(hBitmap)
    { }

    ~BDBitmapT()
    {
        if (t_bManaged && m_hBitmap != NULL)
            DeleteObject();
    }

    BDBitmapT<t_bManaged>& operator =(HBITMAP hBitmap)
    {
        Attach(hBitmap);
        return *this;
    }

    void Attach(HBITMAP hBitmap)
    {
        if (t_bManaged && m_hBitmap != NULL && m_hBitmap != hBitmap)
            ::DeleteObject(m_hBitmap);
        m_hBitmap = hBitmap;
    }

    HBITMAP Detach()
    {
        HBITMAP hBitmap = m_hBitmap;
        m_hBitmap = NULL;
        return hBitmap;
    }

    operator HBITMAP() const { return m_hBitmap; }

    bool IsNull() const { return (m_hBitmap == NULL); }

    // Create and load methods
    HBITMAP LoadBitmap(BDResStr bitmap)
    {
        assert(m_hBitmap == NULL);
        m_hBitmap = ::LoadBitmap(BDWinApp::GetResInstance(), bitmap.m_lpstr);
        return m_hBitmap;
    }

    HBITMAP LoadOEMBitmap(UINT nIDBitmap) // for OBM_/OCR_/OIC_
    {
        assert(m_hBitmap == NULL);
        m_hBitmap = ::LoadBitmap(NULL, MAKEINTRESOURCE(nIDBitmap));
        return m_hBitmap;
    }

    HBITMAP LoadMappedBitmap(UINT nIDBitmap, UINT nFlags = 0, LPCOLORMAP lpColorMap = NULL, int nMapSize = 0)
    {
        assert(m_hBitmap == NULL);
        m_hBitmap = ::CreateMappedBitmap(BDWinApp::GetResInstance(), nIDBitmap, (WORD)nFlags, lpColorMap, nMapSize);
        return m_hBitmap;
    }

    HBITMAP CreateBitmap(int nWidth, int nHeight, UINT nPlanes, UINT nBitsPerPixel, const void* lpBits)
    {
        assert(m_hBitmap == NULL);
        m_hBitmap = ::CreateBitmap(nWidth, nHeight, nPlanes, nBitsPerPixel, lpBits);
        return m_hBitmap;
    }

    HBITMAP CreateBitmapIndirect(LPBITMAP lpBitmap)
    {
        assert(m_hBitmap == NULL);
        m_hBitmap = ::CreateBitmapIndirect(lpBitmap);
        return m_hBitmap;
    }

    HBITMAP CreateCompatibleBitmap(HDC hDC, int nWidth, int nHeight)
    {
        assert(m_hBitmap == NULL);
        m_hBitmap = ::CreateCompatibleBitmap(hDC, nWidth, nHeight);
        return m_hBitmap;
    }

    HBITMAP CreateDiscardableBitmap(HDC hDC, int nWidth, int nHeight)
    {
        assert(m_hBitmap == NULL);
        m_hBitmap = ::CreateDiscardableBitmap(hDC, nWidth, nHeight);
        return m_hBitmap;
    }

    BOOL DeleteObject()
    {
        assert(m_hBitmap != NULL);
        BOOL bRet = ::DeleteObject(m_hBitmap);
        if (bRet)
            m_hBitmap = NULL;
        return bRet;
    }

    // Attributes
    int GetBitmap(BITMAP* pBitMap) const
    {
        assert(m_hBitmap != NULL);
        return ::GetObject(m_hBitmap, sizeof(BITMAP), pBitMap);
    }

    bool GetBitmap(BITMAP& bm) const
    {
        assert(m_hBitmap != NULL);
        return (::GetObject(m_hBitmap, sizeof(BITMAP), &bm) == sizeof(BITMAP));
    }

    bool GetSize(SIZE& size) const
    {
        assert(m_hBitmap != NULL);
        BITMAP bm = { 0 };
        if (!GetBitmap(&bm))
            return false;
        size.cx = bm.bmWidth;
        size.cy = bm.bmHeight;
        return true;
    }

    DWORD GetBitmapBits(DWORD dwCount, LPVOID lpBits) const
    {
        assert(m_hBitmap != NULL);
        return ::GetBitmapBits(m_hBitmap, dwCount, lpBits);
    }

    DWORD SetBitmapBits(DWORD dwCount, const void* lpBits)
    {
        assert(m_hBitmap != NULL);
        return ::SetBitmapBits(m_hBitmap, dwCount, lpBits);
    }

    BOOL GetBitmapDimension(LPSIZE lpSize) const
    {
        assert(m_hBitmap != NULL);
        return ::GetBitmapDimensionEx(m_hBitmap, lpSize);
    }

    BOOL SetBitmapDimension(int nWidth, int nHeight, LPSIZE lpSize = NULL)
    {
        assert(m_hBitmap != NULL);
        return ::SetBitmapDimensionEx(m_hBitmap, nWidth, nHeight, lpSize);
    }

    // DIB support
    HBITMAP CreateDIBitmap(HDC hDC, CONST BITMAPINFOHEADER* lpbmih, DWORD dwInit, CONST VOID* lpbInit, CONST BITMAPINFO* lpbmi, UINT uColorUse)
    {
        assert(m_hBitmap == NULL);
        m_hBitmap = ::CreateDIBitmap(hDC, lpbmih, dwInit, lpbInit, lpbmi, uColorUse);
        return m_hBitmap;
    }

    HBITMAP CreateDIBSection(HDC hDC, CONST BITMAPINFO* lpbmi, UINT uColorUse, VOID** ppvBits, HANDLE hSection, DWORD dwOffset)
    {
        assert(m_hBitmap == NULL);
        m_hBitmap = ::CreateDIBSection(hDC, lpbmi, uColorUse, ppvBits, hSection, dwOffset);
        return m_hBitmap;
    }

    int GetDIBits(HDC hDC, UINT uStartScan, UINT cScanLines, LPVOID lpvBits, LPBITMAPINFO lpbmi, UINT uColorUse) const
    {
        assert(m_hBitmap != NULL);
        return ::GetDIBits(hDC, m_hBitmap, uStartScan, cScanLines, lpvBits, lpbmi, uColorUse);
    }

    int SetDIBits(HDC hDC, UINT uStartScan, UINT cScanLines, CONST VOID* lpvBits, CONST BITMAPINFO* lpbmi, UINT uColorUse)
    {
        assert(m_hBitmap != NULL);
        return ::SetDIBits(hDC, m_hBitmap, uStartScan, cScanLines, lpvBits, lpbmi, uColorUse);
    }
};

typedef BDBitmapT<false>   BDBitmapHandle;
typedef BDBitmapT<true>    BDBitmap;


///////////////////////////////////////////////////////////////////////////////
// BDRgn

template <bool t_bManaged>
class BDRgnT
{
public:
    // Data members
    HRGN m_hRgn;

    // Constructor/destructor/operators
    BDRgnT(HRGN hRgn = NULL) : m_hRgn(hRgn)
    { }

    ~BDRgnT()
    {
        if (t_bManaged && m_hRgn != NULL)
            DeleteObject();
    }

    BDRgnT<t_bManaged>& operator =(HRGN hRgn)
    {
        Attach(hRgn);
        return *this;
    }

    void Attach(HRGN hRgn)
    {
        if (t_bManaged && m_hRgn != NULL && m_hRgn != hRgn)
            ::DeleteObject(m_hRgn);
        m_hRgn = hRgn;
    }

    HRGN Detach()
    {
        HRGN hRgn = m_hRgn;
        m_hRgn = NULL;
        return hRgn;
    }

    operator HRGN() const { return m_hRgn; }

    bool IsNull() const { return (m_hRgn == NULL); }

    // Create methods
    HRGN CreateRectRgn(int x1, int y1, int x2, int y2)
    {
        assert(m_hRgn == NULL);
        m_hRgn = ::CreateRectRgn(x1, y1, x2, y2);
        return m_hRgn;
    }

    HRGN CreateRectRgnIndirect(LPCRECT lpRect)
    {
        assert(m_hRgn == NULL);
        m_hRgn = ::CreateRectRgnIndirect(lpRect);
        return m_hRgn;
    }

    HRGN CreateEllipticRgn(int x1, int y1, int x2, int y2)
    {
        assert(m_hRgn == NULL);
        m_hRgn = ::CreateEllipticRgn(x1, y1, x2, y2);
        return m_hRgn;
    }

    HRGN CreateEllipticRgnIndirect(LPCRECT lpRect)
    {
        assert(m_hRgn == NULL);
        m_hRgn = ::CreateEllipticRgnIndirect(lpRect);
        return m_hRgn;
    }

    HRGN CreatePolygonRgn(LPPOINT lpPoints, int nCount, int nMode)
    {
        assert(m_hRgn == NULL);
        m_hRgn = ::CreatePolygonRgn(lpPoints, nCount, nMode);
        return m_hRgn;
    }

    HRGN CreatePolyPolygonRgn(LPPOINT lpPoints, LPINT lpPolyCounts, int nCount, int nPolyFillMode)
    {
        assert(m_hRgn == NULL);
        m_hRgn = ::CreatePolyPolygonRgn(lpPoints, lpPolyCounts, nCount, nPolyFillMode);
        return m_hRgn;
    }

    HRGN CreateRoundRectRgn(int x1, int y1, int x2, int y2, int x3, int y3)
    {
        assert(m_hRgn == NULL);
        m_hRgn = ::CreateRoundRectRgn(x1, y1, x2, y2, x3, y3);
        return m_hRgn;
    }

    HRGN CreateFromPath(HDC hDC)
    {
        assert(m_hRgn == NULL);
        assert(hDC != NULL);
        m_hRgn = ::PathToRegion(hDC);
        return m_hRgn;
    }

    HRGN CreateFromData(const XFORM* lpXForm, int nCount, const RGNDATA* pRgnData)
    {
        assert(m_hRgn == NULL);
        m_hRgn = ::ExtCreateRegion(lpXForm, nCount, pRgnData);
        return m_hRgn;
    }

    BOOL DeleteObject()
    {
        assert(m_hRgn != NULL);
        BOOL bRet = ::DeleteObject(m_hRgn);
        if (bRet)
            m_hRgn = NULL;
        return bRet;
    }

    // Operations
    void SetRectRgn(int x1, int y1, int x2, int y2)
    {
        assert(m_hRgn != NULL);
        ::SetRectRgn(m_hRgn, x1, y1, x2, y2);
    }

    void SetRectRgn(LPCRECT lpRect)
    {
        assert(m_hRgn != NULL);
        ::SetRectRgn(m_hRgn, lpRect->left, lpRect->top, lpRect->right, lpRect->bottom);
    }

    int CombineRgn(HRGN hRgnSrc1, HRGN hRgnSrc2, int nCombineMode)
    {
        assert(m_hRgn != NULL);
        return ::CombineRgn(m_hRgn, hRgnSrc1, hRgnSrc2, nCombineMode);
    }

    int CombineRgn(HRGN hRgnSrc, int nCombineMode)
    {
        assert(m_hRgn != NULL);
        return ::CombineRgn(m_hRgn, m_hRgn, hRgnSrc, nCombineMode);
    }

    /*int CopyRgn(HRGN hRgnSrc)
    {
        assert(m_hRgn != NULL);
        return ::CombineRgn(m_hRgn, hRgnSrc, NULL, RGN_COPY);
    }*/

    BOOL EqualRgn(HRGN hRgn) const
    {
        assert(m_hRgn != NULL);
        return ::EqualRgn(m_hRgn, hRgn);
    }

    int OffsetRgn(int x, int y)
    {
        assert(m_hRgn != NULL);
        return ::OffsetRgn(m_hRgn, x, y);
    }

    int OffsetRgn(POINT point)
    {
        assert(m_hRgn != NULL);
        return ::OffsetRgn(m_hRgn, point.x, point.y);
    }

    int GetRgnBox(LPRECT lpRect) const
    {
        assert(m_hRgn != NULL);
        return ::GetRgnBox(m_hRgn, lpRect);
    }

    BOOL PtInRegion(int x, int y) const
    {
        assert(m_hRgn != NULL);
        return ::PtInRegion(m_hRgn, x, y);
    }

    BOOL PtInRegion(POINT point) const
    {
        assert(m_hRgn != NULL);
        return ::PtInRegion(m_hRgn, point.x, point.y);
    }

    BOOL RectInRegion(LPCRECT lpRect) const
    {
        assert(m_hRgn != NULL);
        return ::RectInRegion(m_hRgn, lpRect);
    }

    int GetRegionData(LPRGNDATA lpRgnData, int nDataSize) const
    {
        assert(m_hRgn != NULL);
        return (int)::GetRegionData(m_hRgn, nDataSize, lpRgnData);
    }
};

typedef BDRgnT<false>   BDRgnHandle;
typedef BDRgnT<true>    BDRgn;


///////////////////////////////////////////////////////////////////////////////
// BDDC - The device context class

template <bool t_bManaged>
class BDDCT
{
public:
    // Data members
    HDC m_hDC;

    // Constructor/destructor/operators
    BDDCT(HDC hDC = NULL) : m_hDC(hDC)
    {
    }

    ~BDDCT()
    {
        if (t_bManaged && (m_hDC != NULL))
            ::DeleteDC(Detach());
    }

    BDDCT<t_bManaged>& operator =(HDC hDC)
    {
        Attach(hDC);
        return *this;
    }

    void Attach(HDC hDC)
    {
        if (t_bManaged && (m_hDC != NULL) && (m_hDC != hDC))
            ::DeleteDC(m_hDC);
        m_hDC = hDC;
    }

    HDC Detach()
    {
        HDC hDC = m_hDC;
        m_hDC = NULL;
        return hDC;
    }

    operator HDC() const { return m_hDC; }

    bool IsNull() const { return (m_hDC == NULL); }

    // Operations
    HWND WindowFromDC() const
    {
        assert(m_hDC != NULL);
        return ::WindowFromDC(m_hDC);
    }

    BDPenHandle GetCurrentPen() const
    {
        assert(m_hDC != NULL);
        return BDPenHandle((HPEN)::GetCurrentObject(m_hDC, OBJ_PEN));
    }

    BDBrushHandle GetCurrentBrush() const
    {
        assert(m_hDC != NULL);
        return BDBrushHandle((HBRUSH)::GetCurrentObject(m_hDC, OBJ_BRUSH));
    }

    BDFontHandle GetCurrentFont() const
    {
        assert(m_hDC != NULL);
        return BDFontHandle((HFONT)::GetCurrentObject(m_hDC, OBJ_FONT));
    }

    BDBitmapHandle GetCurrentBitmap() const
    {
        assert(m_hDC != NULL);
        return BDBitmapHandle((HBITMAP)::GetCurrentObject(m_hDC, OBJ_BITMAP));
    }

    HDC CreateDC(LPCTSTR lpszDriverName, LPCTSTR lpszDeviceName, LPCTSTR lpszOutput, const DEVMODE* lpInitData)
    {
        assert(m_hDC == NULL);
        m_hDC = ::CreateDC(lpszDriverName, lpszDeviceName, lpszOutput, lpInitData);
        return m_hDC;
    }

    HDC CreateCompatibleDC(HDC hDC = NULL)
    {
        assert(m_hDC == NULL);
        m_hDC = ::CreateCompatibleDC(hDC);
        return m_hDC;
    }

    BOOL DeleteDC()
    {
        if (m_hDC == NULL)
            return FALSE;
        BOOL bRet = ::DeleteDC(m_hDC);
        if (bRet)
            m_hDC = NULL;
        return bRet;
    }

    // Device-Context Functions
    int SaveDC()
    {
        assert(m_hDC != NULL);
        return ::SaveDC(m_hDC);
    }

    BOOL RestoreDC(int nSavedDC)
    {
        assert(m_hDC != NULL);
        return ::RestoreDC(m_hDC, nSavedDC);
    }

    int GetDeviceCaps(int nIndex) const
    {
        assert(m_hDC != NULL);
        return ::GetDeviceCaps(m_hDC, nIndex);
    }

    UINT SetBoundsRect(LPCRECT lpRectBounds, UINT flags)
    {
        assert(m_hDC != NULL);
        return ::SetBoundsRect(m_hDC, lpRectBounds, flags);
    }

    UINT GetBoundsRect(LPRECT lpRectBounds, UINT flags) const
    {
        assert(m_hDC != NULL);
        return ::GetBoundsRect(m_hDC, lpRectBounds, flags);
    }

    BOOL ResetDC(const DEVMODE* lpDevMode)
    {
        assert(m_hDC != NULL);
        return ::ResetDC(m_hDC, lpDevMode) != NULL;
    }

    // Drawing-Tool Functions
    BOOL GetBrushOrg(LPPOINT lpPoint) const
    {
        assert(m_hDC != NULL);
        return ::GetBrushOrgEx(m_hDC, lpPoint);
    }

    BOOL SetBrushOrg(int x, int y, LPPOINT lpPoint = NULL)
    {
        assert(m_hDC != NULL);
        return ::SetBrushOrgEx(m_hDC, x, y, lpPoint);
    }

    BOOL SetBrushOrg(POINT point, LPPOINT lpPointRet = NULL)
    {
        assert(m_hDC != NULL);
        return ::SetBrushOrgEx(m_hDC, point.x, point.y, lpPointRet);
    }

    int EnumObjects(int nObjectType, int (CALLBACK* lpfn)(LPVOID, LPARAM), LPARAM lpData)
    {
        assert(m_hDC != NULL);
        return ::EnumObjects(m_hDC, nObjectType, (GOBJENUMPROC)lpfn, lpData);
    }

    // Type-safe selection helpers
    HPEN SelectPen(HPEN hPen)
    {
        assert(m_hDC != NULL);
        assert(hPen == NULL || ::GetObjectType(hPen) == OBJ_PEN || ::GetObjectType(hPen) == OBJ_EXTPEN);
        return (HPEN)::SelectObject(m_hDC, hPen);
    }

    HBRUSH SelectBrush(HBRUSH hBrush)
    {
        assert(m_hDC != NULL);
        assert(hBrush == NULL || ::GetObjectType(hBrush) == OBJ_BRUSH);
        return (HBRUSH)::SelectObject(m_hDC, hBrush);
    }

    HFONT SelectFont(HFONT hFont)
    {
        assert(m_hDC != NULL);
        assert(hFont == NULL || ::GetObjectType(hFont) == OBJ_FONT);
        return (HFONT)::SelectObject(m_hDC, hFont);
    }

    HBITMAP SelectBitmap(HBITMAP hBitmap)
    {
        assert(m_hDC != NULL);
        assert(hBitmap == NULL || ::GetObjectType(hBitmap) == OBJ_BITMAP);
        return (HBITMAP)::SelectObject(m_hDC, hBitmap);
    }

    int SelectRgn(HRGN hRgn)       // special return for regions
    {
        assert(m_hDC != NULL);
        assert(hRgn == NULL || ::GetObjectType(hRgn) == OBJ_REGION);
        return PtrToInt(::SelectObject(m_hDC, hRgn));
    }

    // Type-safe selection helpers for stock objects
    HPEN SelectStockPen(int nPen)
    {
        assert(m_hDC != NULL);
        assert(nPen == WHITE_PEN || nPen == BLACK_PEN || nPen == NULL_PEN || nPen == DC_PEN);
        return SelectPen((HPEN)::GetStockObject(nPen));
    }

    HBRUSH SelectStockBrush(int nBrush)
    {
        assert(((nBrush >= WHITE_BRUSH) && (nBrush <= HOLLOW_BRUSH)) || (nBrush == DC_BRUSH));
        return SelectBrush((HBRUSH)::GetStockObject(nBrush));
    }

    HFONT SelectStockFont(int nFont)
    {
        assert(((nFont >= OEM_FIXED_FONT) && (nFont <= SYSTEM_FIXED_FONT)) || (nFont == DEFAULT_GUI_FONT));
        return SelectFont((HFONT)::GetStockObject(nFont));
    }

    HPALETTE SelectStockPalette(int nPalette, BOOL bForceBackground)
    {
        assert(nPalette == DEFAULT_PALETTE); // the only one supported
        return SelectPalette((HPALETTE)::GetStockObject(nPalette), bForceBackground);
    }

    // Color and Color Palette Functions
    COLORREF GetNearestColor(COLORREF crColor) const
    {
        assert(m_hDC != NULL);
        return ::GetNearestColor(m_hDC, crColor);
    }

    HPALETTE SelectPalette(HPALETTE hPalette, BOOL bForceBackground)
    {
        assert(m_hDC != NULL);

        return ::SelectPalette(m_hDC, hPalette, bForceBackground);
    }

    UINT RealizePalette()
    {
        assert(m_hDC != NULL);
        return ::RealizePalette(m_hDC);
    }

    void UpdateColors()
    {
        assert(m_hDC != NULL);
        ::UpdateColors(m_hDC);
    }

    // Drawing-Attribute Functions
    COLORREF GetBkColor() const
    {
        assert(m_hDC != NULL);
        return ::GetBkColor(m_hDC);
    }

    int GetBkMode() const
    {
        assert(m_hDC != NULL);
        return ::GetBkMode(m_hDC);
    }

    int GetPolyFillMode() const
    {
        assert(m_hDC != NULL);
        return ::GetPolyFillMode(m_hDC);
    }

    int GetROP2() const
    {
        assert(m_hDC != NULL);
        return ::GetROP2(m_hDC);
    }

    int GetStretchBltMode() const
    {
        assert(m_hDC != NULL);
        return ::GetStretchBltMode(m_hDC);
    }

    COLORREF GetTextColor() const
    {
        assert(m_hDC != NULL);
        return ::GetTextColor(m_hDC);
    }

    COLORREF SetBkColor(COLORREF crColor)
    {
        assert(m_hDC != NULL);
        return ::SetBkColor(m_hDC, crColor);
    }

    int SetBkMode(int nBkMode)
    {
        assert(m_hDC != NULL);
        return ::SetBkMode(m_hDC, nBkMode);
    }

    int SetPolyFillMode(int nPolyFillMode)
    {
        assert(m_hDC != NULL);
        return ::SetPolyFillMode(m_hDC, nPolyFillMode);
    }

    int SetROP2(int nDrawMode)
    {
        assert(m_hDC != NULL);
        return ::SetROP2(m_hDC, nDrawMode);
    }

    int SetStretchBltMode(int nStretchMode)
    {
        assert(m_hDC != NULL);
        return ::SetStretchBltMode(m_hDC, nStretchMode);
    }

    COLORREF SetTextColor(COLORREF crColor)
    {
        assert(m_hDC != NULL);
        return ::SetTextColor(m_hDC, crColor);
    }

    BOOL GetColorAdjustment(LPCOLORADJUSTMENT lpColorAdjust) const
    {
        assert(m_hDC != NULL);
        return ::GetColorAdjustment(m_hDC, lpColorAdjust);
    }

    BOOL SetColorAdjustment(const COLORADJUSTMENT* lpColorAdjust)
    {
        assert(m_hDC != NULL);
        return ::SetColorAdjustment(m_hDC, lpColorAdjust);
    }

    // Mapping Functions
    int GetMapMode() const
    {
        assert(m_hDC != NULL);
        return ::GetMapMode(m_hDC);
    }

    BOOL GetViewportOrg(LPPOINT lpPoint) const
    {
        assert(m_hDC != NULL);
        return ::GetViewportOrgEx(m_hDC, lpPoint);
    }

    int SetMapMode(int nMapMode)
    {
        assert(m_hDC != NULL);
        return ::SetMapMode(m_hDC, nMapMode);
    }

    // Viewport Origin
    BOOL SetViewportOrg(int x, int y, LPPOINT lpPoint = NULL)
    {
        assert(m_hDC != NULL);
        return ::SetViewportOrgEx(m_hDC, x, y, lpPoint);
    }

    BOOL SetViewportOrg(POINT point, LPPOINT lpPointRet = NULL)
    {
        assert(m_hDC != NULL);
        return SetViewportOrg(point.x, point.y, lpPointRet);
    }

    BOOL OffsetViewportOrg(int nWidth, int nHeight, LPPOINT lpPoint = NULL)
    {
        assert(m_hDC != NULL);
        return ::OffsetViewportOrgEx(m_hDC, nWidth, nHeight, lpPoint);
    }

    // Viewport Extent
    BOOL GetViewportExt(LPSIZE lpSize) const
    {
        assert(m_hDC != NULL);
        return ::GetViewportExtEx(m_hDC, lpSize);
    }

    BOOL SetViewportExt(int x, int y, LPSIZE lpSize = NULL)
    {
        assert(m_hDC != NULL);
        return ::SetViewportExtEx(m_hDC, x, y, lpSize);
    }

    BOOL SetViewportExt(SIZE size, LPSIZE lpSizeRet = NULL)
    {
        assert(m_hDC != NULL);
        return SetViewportExt(size.cx, size.cy, lpSizeRet);
    }

    BOOL ScaleViewportExt(int xNum, int xDenom, int yNum, int yDenom, LPSIZE lpSize = NULL)
    {
        assert(m_hDC != NULL);
        return ::ScaleViewportExtEx(m_hDC, xNum, xDenom, yNum, yDenom, lpSize);
    }

    // Window Origin
    BOOL GetWindowOrg(LPPOINT lpPoint) const
    {
        assert(m_hDC != NULL);
        return ::GetWindowOrgEx(m_hDC, lpPoint);
    }

    BOOL SetWindowOrg(int x, int y, LPPOINT lpPoint = NULL)
    {
        assert(m_hDC != NULL);
        return ::SetWindowOrgEx(m_hDC, x, y, lpPoint);
    }

    BOOL SetWindowOrg(POINT point, LPPOINT lpPointRet = NULL)
    {
        assert(m_hDC != NULL);
        return SetWindowOrg(point.x, point.y, lpPointRet);
    }

    BOOL OffsetWindowOrg(int nWidth, int nHeight, LPPOINT lpPoint = NULL)
    {
        assert(m_hDC != NULL);
        return ::OffsetWindowOrgEx(m_hDC, nWidth, nHeight, lpPoint);
    }

    // Window extent
    BOOL GetWindowExt(LPSIZE lpSize) const
    {
        assert(m_hDC != NULL);
        return ::GetWindowExtEx(m_hDC, lpSize);
    }

    BOOL SetWindowExt(int x, int y, LPSIZE lpSize = NULL)
    {
        assert(m_hDC != NULL);
        return ::SetWindowExtEx(m_hDC, x, y, lpSize);
    }

    BOOL SetWindowExt(SIZE size, LPSIZE lpSizeRet = NULL)
    {
        assert(m_hDC != NULL);
        return SetWindowExt(size.cx, size.cy, lpSizeRet);
    }

    BOOL ScaleWindowExt(int xNum, int xDenom, int yNum, int yDenom, LPSIZE lpSize = NULL)
    {
        assert(m_hDC != NULL);
        return ::ScaleWindowExtEx(m_hDC, xNum, xDenom, yNum, yDenom, lpSize);
    }

    // Coordinate Functions
    BOOL DPtoLP(LPPOINT lpPoints, int nCount = 1) const
    {
        assert(m_hDC != NULL);
        return ::DPtoLP(m_hDC, lpPoints, nCount);
    }

    BOOL DPtoLP(LPRECT lpRect) const
    {
        assert(m_hDC != NULL);
        return ::DPtoLP(m_hDC, (LPPOINT)lpRect, 2);
    }

    BOOL DPtoLP(LPSIZE lpSize) const
    {
        SIZE sizeWinExt = {};
        if (!GetWindowExt(&sizeWinExt))
            return FALSE;
        SIZE sizeVpExt = {};
        if (!GetViewportExt(&sizeVpExt))
            return FALSE;
        lpSize->cx = ::MulDiv(lpSize->cx, abs(sizeWinExt.cx), abs(sizeVpExt.cx));
        lpSize->cy = ::MulDiv(lpSize->cy, abs(sizeWinExt.cy), abs(sizeVpExt.cy));
        return TRUE;
    }

    BOOL LPtoDP(LPPOINT lpPoints, int nCount = 1) const
    {
        assert(m_hDC != NULL);
        return ::LPtoDP(m_hDC, lpPoints, nCount);
    }

    BOOL LPtoDP(LPRECT lpRect) const
    {
        assert(m_hDC != NULL);
        return ::LPtoDP(m_hDC, (LPPOINT)lpRect, 2);
    }

    BOOL LPtoDP(LPSIZE lpSize) const
    {
        SIZE sizeWinExt = {};
        if (!GetWindowExt(&sizeWinExt))
            return FALSE;
        SIZE sizeVpExt = {};
        if (!GetViewportExt(&sizeVpExt))
            return FALSE;
        lpSize->cx = ::MulDiv(lpSize->cx, abs(sizeVpExt.cx), abs(sizeWinExt.cx));
        lpSize->cy = ::MulDiv(lpSize->cy, abs(sizeVpExt.cy), abs(sizeWinExt.cy));
        return TRUE;
    }

    // Special Coordinate Functions (useful for dealing with metafiles and OLE)
#define HIMETRIC_INCH   2540    // HIMETRIC units per inch

    void DPtoHIMETRIC(LPSIZE lpSize)
    {
        assert(m_hDC != NULL);
        int nMapMode = GetMapMode();
        if ((nMapMode < MM_ISOTROPIC) && (nMapMode != MM_TEXT))
        {
            // when using a constrained map mode, map against physical inch
            SetMapMode(MM_HIMETRIC);
            DPtoLP(lpSize);
            SetMapMode(nMapMode);
        }
        else
        {
            // map against logical inch for non-constrained mapping modes
            int cxPerInch = GetDeviceCaps(LOGPIXELSX);
            int cyPerInch = GetDeviceCaps(LOGPIXELSY);
            assert((cxPerInch != 0) && (cyPerInch != 0));
            lpSize->cx = ::MulDiv(lpSize->cx, HIMETRIC_INCH, cxPerInch);
            lpSize->cy = ::MulDiv(lpSize->cy, HIMETRIC_INCH, cyPerInch);
        }
    }

    void HIMETRICtoDP(LPSIZE lpSize)
    {
        assert(m_hDC != NULL);
        int nMapMode = GetMapMode();
        if ((nMapMode < MM_ISOTROPIC) && (nMapMode != MM_TEXT))
        {
            // when using a constrained map mode, map against physical inch
            this->SetMapMode(MM_HIMETRIC);
            LPtoDP(lpSize);
            this->SetMapMode(nMapMode);
        }
        else
        {
            // map against logical inch for non-constrained mapping modes
            int cxPerInch = GetDeviceCaps(LOGPIXELSX);
            int cyPerInch = GetDeviceCaps(LOGPIXELSY);
            assert((cxPerInch != 0) && (cyPerInch != 0));
            lpSize->cx = ::MulDiv(lpSize->cx, cxPerInch, HIMETRIC_INCH);
            lpSize->cy = ::MulDiv(lpSize->cy, cyPerInch, HIMETRIC_INCH);
        }
    }

    void LPtoHIMETRIC(LPSIZE lpSize) const
    {
        LPtoDP(lpSize);
        DPtoHIMETRIC(lpSize);
    }

    void HIMETRICtoLP(LPSIZE lpSize) const
    {
        HIMETRICtoDP(lpSize);
        DPtoLP(lpSize);
    }

    // Region Functions
    BOOL FillRgn(HRGN hRgn, HBRUSH hBrush)
    {
        assert(m_hDC != NULL);
        return ::FillRgn(m_hDC, hRgn, hBrush);
    }

    BOOL FrameRgn(HRGN hRgn, HBRUSH hBrush, int nWidth, int nHeight)
    {
        assert(m_hDC != NULL);
        return ::FrameRgn(m_hDC, hRgn, hBrush, nWidth, nHeight);
    }

    BOOL InvertRgn(HRGN hRgn)
    {
        assert(m_hDC != NULL);
        return ::InvertRgn(m_hDC, hRgn);
    }

    BOOL PaintRgn(HRGN hRgn)
    {
        assert(m_hDC != NULL);
        return ::PaintRgn(m_hDC, hRgn);
    }

    // Clipping Functions
    int GetClipBox(LPRECT lpRect) const
    {
        assert(m_hDC != NULL);
        return ::GetClipBox(m_hDC, lpRect);
    }

    int GetClipRgn(BDRgn& region) const
    {
        assert(m_hDC != NULL);
        if (region.IsNull())
            region.CreateRectRgn(0, 0, 0, 0);

        int nRet = ::GetClipRgn(m_hDC, region);
        if (nRet != 1)
            region.DeleteObject();

        return nRet;
    }

    BOOL PtVisible(int x, int y) const
    {
        assert(m_hDC != NULL);
        return ::PtVisible(m_hDC, x, y);
    }

    BOOL PtVisible(POINT point) const
    {
        assert(m_hDC != NULL);
        return ::PtVisible(m_hDC, point.x, point.y);
    }

    BOOL RectVisible(LPCRECT lpRect) const
    {
        assert(m_hDC != NULL);
        return ::RectVisible(m_hDC, lpRect);
    }

    int SelectClipRgn(HRGN hRgn)
    {
        assert(m_hDC != NULL);
        return ::SelectClipRgn(m_hDC, (HRGN)hRgn);
    }

    int ExcludeClipRect(int x1, int y1, int x2, int y2)
    {
        assert(m_hDC != NULL);
        return ::ExcludeClipRect(m_hDC, x1, y1, x2, y2);
    }

    int ExcludeClipRect(LPCRECT lpRect)
    {
        assert(m_hDC != NULL);
        return ::ExcludeClipRect(m_hDC, lpRect->left, lpRect->top, lpRect->right, lpRect->bottom);
    }

    int ExcludeUpdateRgn(HWND hWnd)
    {
        assert(m_hDC != NULL);
        return ::ExcludeUpdateRgn(m_hDC, hWnd);
    }

    int IntersectClipRect(int x1, int y1, int x2, int y2)
    {
        assert(m_hDC != NULL);
        return ::IntersectClipRect(m_hDC, x1, y1, x2, y2);
    }

    int IntersectClipRect(LPCRECT lpRect)
    {
        assert(m_hDC != NULL);
        return ::IntersectClipRect(m_hDC, lpRect->left, lpRect->top, lpRect->right, lpRect->bottom);
    }

    int OffsetClipRgn(int x, int y)
    {
        assert(m_hDC != NULL);
        return ::OffsetClipRgn(m_hDC, x, y);
    }

    int OffsetClipRgn(SIZE size)
    {
        assert(m_hDC != NULL);
        return ::OffsetClipRgn(m_hDC, size.cx, size.cy);
    }

    int SelectClipRgn(HRGN hRgn, int nMode)
    {
        assert(m_hDC != NULL);
        return ::ExtSelectClipRgn(m_hDC, hRgn, nMode);
    }

    // Line-Output Functions
    BOOL GetCurrentPosition(LPPOINT lpPoint) const
    {
        assert(m_hDC != NULL);
        return ::GetCurrentPositionEx(m_hDC, lpPoint);
    }

    BOOL MoveTo(int x, int y, LPPOINT lpPoint = NULL)
    {
        assert(m_hDC != NULL);
        return ::MoveToEx(m_hDC, x, y, lpPoint);
    }

    BOOL MoveTo(POINT point, LPPOINT lpPointRet = NULL)
    {
        assert(m_hDC != NULL);
        return MoveTo(point.x, point.y, lpPointRet);
    }

    BOOL LineTo(int x, int y)
    {
        assert(m_hDC != NULL);
        return ::LineTo(m_hDC, x, y);
    }

    BOOL LineTo(POINT point)
    {
        assert(m_hDC != NULL);
        return LineTo(point.x, point.y);
    }

    BOOL Arc(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
    {
        assert(m_hDC != NULL);
        return ::Arc(m_hDC, x1, y1, x2, y2, x3, y3, x4, y4);
    }

    BOOL Arc(LPCRECT lpRect, POINT ptStart, POINT ptEnd)
    {
        assert(m_hDC != NULL);
        return ::Arc(m_hDC, lpRect->left, lpRect->top,
            lpRect->right, lpRect->bottom, ptStart.x, ptStart.y,
            ptEnd.x, ptEnd.y);
    }

    BOOL Polyline(const POINT* lpPoints, int nCount)
    {
        assert(m_hDC != NULL);
        return ::Polyline(m_hDC, lpPoints, nCount);
    }

    BOOL AngleArc(int x, int y, int nRadius, float fStartAngle, float fSweepAngle)
    {
        assert(m_hDC != NULL);
        return ::AngleArc(m_hDC, x, y, nRadius, fStartAngle, fSweepAngle);
    }

    BOOL ArcTo(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
    {
        assert(m_hDC != NULL);
        return ::ArcTo(m_hDC, x1, y1, x2, y2, x3, y3, x4, y4);
    }

    BOOL ArcTo(LPCRECT lpRect, POINT ptStart, POINT ptEnd)
    {
        assert(m_hDC != NULL);
        return ArcTo(lpRect->left, lpRect->top, lpRect->right,
            lpRect->bottom, ptStart.x, ptStart.y, ptEnd.x, ptEnd.y);
    }

    int GetArcDirection() const
    {
        assert(m_hDC != NULL);
        return ::GetArcDirection(m_hDC);
    }

    int SetArcDirection(int nArcDirection)
    {
        assert(m_hDC != NULL);
        return ::SetArcDirection(m_hDC, nArcDirection);
    }

    BOOL PolyDraw(const POINT* lpPoints, const BYTE* lpTypes, int nCount)
    {
        assert(m_hDC != NULL);
        return ::PolyDraw(m_hDC, lpPoints, lpTypes, nCount);
    }

    BOOL PolylineTo(const POINT* lpPoints, int nCount)
    {
        assert(m_hDC != NULL);
        return ::PolylineTo(m_hDC, lpPoints, nCount);
    }

    BOOL PolyPolyline(const POINT* lpPoints,
        const DWORD* lpPolyPoints, int nCount)
    {
        assert(m_hDC != NULL);
        return ::PolyPolyline(m_hDC, lpPoints, lpPolyPoints, nCount);
    }

    BOOL PolyBezier(const POINT* lpPoints, int nCount)
    {
        assert(m_hDC != NULL);
        return ::PolyBezier(m_hDC, lpPoints, nCount);
    }

    BOOL PolyBezierTo(const POINT* lpPoints, int nCount)
    {
        assert(m_hDC != NULL);
        return ::PolyBezierTo(m_hDC, lpPoints, nCount);
    }

    // Simple Drawing Functions
    BOOL FillRect(LPCRECT lpRect, HBRUSH hBrush)
    {
        assert(m_hDC != NULL);
        return ::FillRect(m_hDC, lpRect, hBrush);
    }

    BOOL FillRect(LPCRECT lpRect, int nColorIndex)
    {
        assert(m_hDC != NULL);
        return ::FillRect(m_hDC, lpRect, (HBRUSH)LongToPtr(nColorIndex + 1));
    }

    BOOL FrameRect(LPCRECT lpRect, HBRUSH hBrush)
    {
        assert(m_hDC != NULL);
        return ::FrameRect(m_hDC, lpRect, hBrush);
    }

    BOOL InvertRect(LPCRECT lpRect)
    {
        assert(m_hDC != NULL);
        return ::InvertRect(m_hDC, lpRect);
    }

    BOOL DrawIcon(int x, int y, HICON hIcon)
    {
        assert(m_hDC != NULL);
        return ::DrawIcon(m_hDC, x, y, hIcon);
    }

    BOOL DrawIcon(POINT point, HICON hIcon)
    {
        assert(m_hDC != NULL);
        return ::DrawIcon(m_hDC, point.x, point.y, hIcon);
    }

    BOOL DrawIconEx(int x, int y, HICON hIcon, int cxWidth, int cyWidth, UINT uStepIfAniCur = 0, HBRUSH hbrFlickerFreeDraw = NULL, UINT uFlags = DI_NORMAL)
    {
        assert(m_hDC != NULL);
        return ::DrawIconEx(m_hDC, x, y, hIcon, cxWidth, cyWidth, uStepIfAniCur, hbrFlickerFreeDraw, uFlags);
    }

    BOOL DrawIconEx(POINT point, HICON hIcon, SIZE size, UINT uStepIfAniCur = 0, HBRUSH hbrFlickerFreeDraw = NULL, UINT uFlags = DI_NORMAL)
    {
        assert(m_hDC != NULL);
        return ::DrawIconEx(m_hDC, point.x, point.y, hIcon, size.cx, size.cy, uStepIfAniCur, hbrFlickerFreeDraw, uFlags);
    }

    BOOL DrawState(POINT pt, SIZE size, HBITMAP hBitmap, UINT nFlags, HBRUSH hBrush = NULL)
    {
        assert(m_hDC != NULL);
        return ::DrawState(m_hDC, hBrush, NULL, (LPARAM)hBitmap, 0, pt.x, pt.y, size.cx, size.cy, nFlags | DST_BITMAP);
    }

    BOOL DrawState(POINT pt, SIZE size, HICON hIcon, UINT nFlags, HBRUSH hBrush = NULL)
    {
        assert(m_hDC != NULL);
        return ::DrawState(m_hDC, hBrush, NULL, (LPARAM)hIcon, 0, pt.x, pt.y, size.cx, size.cy, nFlags | DST_ICON);
    }

    BOOL DrawState(POINT pt, SIZE size, LPCTSTR lpszText, UINT nFlags, BOOL bPrefixText = TRUE, int nTextLen = 0, HBRUSH hBrush = NULL)
    {
        assert(m_hDC != NULL);
        return ::DrawState(m_hDC, hBrush, NULL, (LPARAM)lpszText, (WPARAM)nTextLen, pt.x, pt.y, size.cx, size.cy, nFlags | (bPrefixText ? DST_PREFIXTEXT : DST_TEXT));
    }

    BOOL DrawState(POINT pt, SIZE size, DRAWSTATEPROC lpDrawProc, LPARAM lData, UINT nFlags, HBRUSH hBrush = NULL)
    {
        assert(m_hDC != NULL);
        return ::DrawState(m_hDC, hBrush, lpDrawProc, lData, 0, pt.x, pt.y, size.cx, size.cy, nFlags | DST_COMPLEX);
    }

    // Ellipse and Polygon Functions
    BOOL Chord(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
    {
        assert(m_hDC != NULL);
        return ::Chord(m_hDC, x1, y1, x2, y2, x3, y3, x4, y4);
    }

    BOOL Chord(LPCRECT lpRect, POINT ptStart, POINT ptEnd)
    {
        assert(m_hDC != NULL);
        return ::Chord(m_hDC, lpRect->left, lpRect->top, lpRect->right, lpRect->bottom, ptStart.x, ptStart.y, ptEnd.x, ptEnd.y);
    }

    void DrawFocusRect(LPCRECT lpRect)
    {
        assert(m_hDC != NULL);
        ::DrawFocusRect(m_hDC, lpRect);
    }

    BOOL Ellipse(int x1, int y1, int x2, int y2)
    {
        assert(m_hDC != NULL);
        return ::Ellipse(m_hDC, x1, y1, x2, y2);
    }

    BOOL Ellipse(LPCRECT lpRect)
    {
        assert(m_hDC != NULL);
        return ::Ellipse(m_hDC, lpRect->left, lpRect->top, lpRect->right, lpRect->bottom);
    }

    BOOL Pie(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
    {
        assert(m_hDC != NULL);
        return ::Pie(m_hDC, x1, y1, x2, y2, x3, y3, x4, y4);
    }

    BOOL Pie(LPCRECT lpRect, POINT ptStart, POINT ptEnd)
    {
        assert(m_hDC != NULL);
        return ::Pie(m_hDC, lpRect->left, lpRect->top, lpRect->right, lpRect->bottom, ptStart.x, ptStart.y, ptEnd.x, ptEnd.y);
    }

    BOOL Polygon(const POINT* lpPoints, int nCount)
    {
        assert(m_hDC != NULL);
        return ::Polygon(m_hDC, lpPoints, nCount);
    }

    BOOL PolyPolygon(const POINT* lpPoints, const INT* lpPolyCounts, int nCount)
    {
        assert(m_hDC != NULL);
        return ::PolyPolygon(m_hDC, lpPoints, lpPolyCounts, nCount);
    }

    BOOL Rectangle(int x1, int y1, int x2, int y2)
    {
        assert(m_hDC != NULL);
        return ::Rectangle(m_hDC, x1, y1, x2, y2);
    }

    BOOL Rectangle(LPCRECT lpRect)
    {
        assert(m_hDC != NULL);
        return ::Rectangle(m_hDC, lpRect->left, lpRect->top, lpRect->right, lpRect->bottom);
    }

    BOOL RoundRect(int x1, int y1, int x2, int y2, int x3, int y3)
    {
        assert(m_hDC != NULL);
        return ::RoundRect(m_hDC, x1, y1, x2, y2, x3, y3);
    }

    BOOL RoundRect(LPCRECT lpRect, POINT point)
    {
        assert(m_hDC != NULL);
        return ::RoundRect(m_hDC, lpRect->left, lpRect->top, lpRect->right, lpRect->bottom, point.x, point.y);
    }

    // Bitmap Functions
    BOOL PatBlt(int x, int y, int nWidth, int nHeight, DWORD dwRop)
    {
        assert(m_hDC != NULL);
        return ::PatBlt(m_hDC, x, y, nWidth, nHeight, dwRop);
    }

    BOOL BitBlt(int x, int y, int nWidth, int nHeight, HDC hSrcDC,
        int xSrc, int ySrc, DWORD dwRop)
    {
        assert(m_hDC != NULL);
        return ::BitBlt(m_hDC, x, y, nWidth, nHeight, hSrcDC, xSrc, ySrc, dwRop);
    }

    BOOL StretchBlt(int x, int y, int nWidth, int nHeight, HDC hSrcDC, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight, DWORD dwRop)
    {
        assert(m_hDC != NULL);
        return ::StretchBlt(m_hDC, x, y, nWidth, nHeight, hSrcDC, xSrc, ySrc, nSrcWidth, nSrcHeight, dwRop);
    }

    COLORREF GetPixel(int x, int y) const
    {
        assert(m_hDC != NULL);
        return ::GetPixel(m_hDC, x, y);
    }

    COLORREF GetPixel(POINT point) const
    {
        assert(m_hDC != NULL);
        return ::GetPixel(m_hDC, point.x, point.y);
    }

    COLORREF SetPixel(int x, int y, COLORREF crColor)
    {
        assert(m_hDC != NULL);
        return ::SetPixel(m_hDC, x, y, crColor);
    }

    COLORREF SetPixel(POINT point, COLORREF crColor)
    {
        assert(m_hDC != NULL);
        return ::SetPixel(m_hDC, point.x, point.y, crColor);
    }

    BOOL FloodFill(int x, int y, COLORREF crColor)
    {
        assert(m_hDC != NULL);
        return ::FloodFill(m_hDC, x, y, crColor);
    }

    BOOL ExtFloodFill(int x, int y, COLORREF crColor, UINT nFillType)
    {
        assert(m_hDC != NULL);
        return ::ExtFloodFill(m_hDC, x, y, crColor, nFillType);
    }

    BOOL MaskBlt(int x, int y, int nWidth, int nHeight, HDC hSrcDC, int xSrc, int ySrc, HBITMAP hMaskBitmap, int xMask, int yMask, DWORD dwRop)
    {
        assert(m_hDC != NULL);
        return ::MaskBlt(m_hDC, x, y, nWidth, nHeight, hSrcDC, xSrc, ySrc, hMaskBitmap, xMask, yMask, dwRop);
    }

    BOOL PlgBlt(LPPOINT lpPoint, HDC hSrcDC, int xSrc, int ySrc, int nWidth, int nHeight, HBITMAP hMaskBitmap, int xMask, int yMask)
    {
        assert(m_hDC != NULL);
        return ::PlgBlt(m_hDC, lpPoint, hSrcDC, xSrc, ySrc, nWidth, nHeight, hMaskBitmap, xMask, yMask);
    }

    BOOL SetPixelV(int x, int y, COLORREF crColor)
    {
        assert(m_hDC != NULL);
        return ::SetPixelV(m_hDC, x, y, crColor);
    }

    BOOL SetPixelV(POINT point, COLORREF crColor)
    {
        assert(m_hDC != NULL);
        return ::SetPixelV(m_hDC, point.x, point.y, crColor);
    }

    BOOL TransparentBlt(int x, int y, int nWidth, int nHeight, HDC hSrcDC, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight, UINT crTransparent)
    {
        assert(m_hDC != NULL);
        return ::TransparentBlt(m_hDC, x, y, nWidth, nHeight, hSrcDC, xSrc, ySrc, nSrcWidth, nSrcHeight, crTransparent);
    }

    BOOL GradientFill(const PTRIVERTEX pVertices, DWORD nVertices, void* pMeshElements, DWORD nMeshElements, DWORD dwMode)
    {
        assert(m_hDC != NULL);
        return ::GradientFill(m_hDC, pVertices, nVertices, pMeshElements, nMeshElements, dwMode);
    }

    BOOL GradientFillRect(RECT& rect, COLORREF clr1, COLORREF clr2, bool bHorizontal)
    {
        assert(m_hDC != NULL);

        TRIVERTEX arrTvx[2] = { { 0 }, { 0 } };

        arrTvx[0].x = rect.left;
        arrTvx[0].y = rect.top;
        arrTvx[0].Red = MAKEWORD(0, GetRValue(clr1));
        arrTvx[0].Green = MAKEWORD(0, GetGValue(clr1));
        arrTvx[0].Blue = MAKEWORD(0, GetBValue(clr1));
        arrTvx[0].Alpha = 0;

        arrTvx[1].x = rect.right;
        arrTvx[1].y = rect.bottom;
        arrTvx[1].Red = MAKEWORD(0, GetRValue(clr2));
        arrTvx[1].Green = MAKEWORD(0, GetGValue(clr2));
        arrTvx[1].Blue = MAKEWORD(0, GetBValue(clr2));
        arrTvx[1].Alpha = 0;

        GRADIENT_RECT gr = { 0, 1 };

        return ::GradientFill(m_hDC, arrTvx, 2, &gr, 1, bHorizontal ? GRADIENT_FILL_RECT_H : GRADIENT_FILL_RECT_V);
    }

    BOOL AlphaBlend(int x, int y, int nWidth, int nHeight, HDC hSrcDC, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight, BLENDFUNCTION bf)
    {
        assert(m_hDC != NULL);
        return ::AlphaBlend(m_hDC, x, y, nWidth, nHeight, hSrcDC, xSrc, ySrc, nSrcWidth, nSrcHeight, bf);
    }

    // Extra bitmap functions
        // Helper function for painting a disabled toolbar or menu bitmap
        // This function can take either an HBITMAP (for SS) or a DC with 
        //           the bitmap already painted (for cmdbar)
    BOOL DitherBlt(int x, int y, int nWidth, int nHeight, HDC hSrcDC, HBITMAP hBitmap, int xSrc, int ySrc,
        HBRUSH hBrushBackground = ::GetSysColorBrush(COLOR_3DFACE),
        HBRUSH hBrush3DEffect = ::GetSysColorBrush(COLOR_3DHILIGHT),
        HBRUSH hBrushDisabledImage = ::GetSysColorBrush(COLOR_3DSHADOW))
    {
        assert(m_hDC != NULL || hBitmap != NULL);
        assert(nWidth > 0 && nHeight > 0);

        // Create a generic DC for all BitBlts
        BDDCT<false> dc = (hSrcDC != NULL) ? hSrcDC : ::CreateCompatibleDC(m_hDC);
        assert(dc.m_hDC != NULL);
        if (dc.m_hDC == NULL)
            return FALSE;

        // Create a DC for the monochrome DIB section
        BDDCT<true> dcBW = ::CreateCompatibleDC(m_hDC);
        assert(dcBW.m_hDC != NULL);
        if (dcBW.m_hDC == NULL)
        {
            if (hSrcDC == NULL)
                dc.DeleteDC();
            return FALSE;
        }

        // Create the monochrome DIB section with a black and white palette
        struct RGBBWBITMAPINFO
        {
            BITMAPINFOHEADER bmiHeader;
            RGBQUAD bmiColors[2];
        };

        RGBBWBITMAPINFO rgbBWBitmapInfo =
        {
            { sizeof(BITMAPINFOHEADER), nWidth, nHeight, 1, 1, BI_RGB, 0, 0, 0, 0, 0 },
            { { 0x00, 0x00, 0x00, 0x00 }, { 0xFF, 0xFF, 0xFF, 0x00 } }
        };

        VOID* pbitsBW;
        BDBitmap bmpBW = ::CreateDIBSection(dcBW, (LPBITMAPINFO)&rgbBWBitmapInfo, DIB_RGB_COLORS, &pbitsBW, NULL, 0);
        assert(bmpBW.m_hBitmap != NULL);
        if (bmpBW.m_hBitmap == NULL)
        {
            if (hSrcDC == NULL)
                dc.DeleteDC();
            return FALSE;
        }

        // Attach the monochrome DIB section and the bitmap to the DCs
        HBITMAP hbmOldBW = dcBW.SelectBitmap(bmpBW);
        HBITMAP hbmOldDC = NULL;
        if (hBitmap != NULL)
            hbmOldDC = dc.SelectBitmap(hBitmap);

        // Block: Dark gray removal: we want (128, 128, 128) pixels to become black and not white
        {
            BDDCT<true> dcTemp1 = ::CreateCompatibleDC(m_hDC);
            BDDCT<true> dcTemp2 = ::CreateCompatibleDC(m_hDC);
            BDBitmap bmpTemp1;
            bmpTemp1.CreateCompatibleBitmap(dc, nWidth, nHeight);
            BDBitmap bmpTemp2;
            bmpTemp2.CreateBitmap(nWidth, nHeight, 1, 1, NULL);
            HBITMAP hOldBmp1 = dcTemp1.SelectBitmap(bmpTemp1);
            HBITMAP hOldBmp2 = dcTemp2.SelectBitmap(bmpTemp2);
            // Let's copy our image, it will be altered
            dcTemp1.BitBlt(0, 0, nWidth, nHeight, dc, xSrc, ySrc, SRCCOPY);

            // All dark gray pixels will become white, the others black
            dcTemp1.SetBkColor(RGB(128, 128, 128));
            dcTemp2.BitBlt(0, 0, nWidth, nHeight, dcTemp1, 0, 0, SRCCOPY);
            // Do an XOR to set to black these white pixels
            dcTemp1.BitBlt(0, 0, nWidth, nHeight, dcTemp2, 0, 0, SRCINVERT);

            // BitBlt the bitmap into the monochrome DIB section
            // The DIB section will do a true monochrome conversion
            // The magenta background being closer to white will become white
            dcBW.BitBlt(0, 0, nWidth, nHeight, dcTemp1, 0, 0, SRCCOPY);

            // Cleanup
            dcTemp1.SelectBitmap(hOldBmp1);
            dcTemp2.SelectBitmap(hOldBmp2);
        }

        // Paint the destination rectangle using hBrushBackground
        if (hBrushBackground != NULL)
        {
            RECT rc = { x, y, x + nWidth, y + nHeight };
            FillRect(&rc, hBrushBackground);
        }

        // BitBlt the black bits in the monochrome bitmap into hBrush3DEffect color in the destination DC
        // The magic ROP comes from the Charles Petzold's book
        HBRUSH hOldBrush = SelectBrush(hBrush3DEffect);
        BitBlt(x + 1, y + 1, nWidth, nHeight, dcBW, 0, 0, 0xB8074A);

        // BitBlt the black bits in the monochrome bitmap into hBrushDisabledImage color in the destination DC
        SelectBrush(hBrushDisabledImage);
        BitBlt(x, y, nWidth, nHeight, dcBW, 0, 0, 0xB8074A);

        SelectBrush(hOldBrush);
        dcBW.SelectBitmap(hbmOldBW);
        dc.SelectBitmap(hbmOldDC);

        if (hSrcDC == NULL)
            dc.DeleteDC();

        return TRUE;
    }

    // Text Functions
    BOOL TextOut(int x, int y, LPCTSTR lpszString, int nCount = -1)
    {
        assert(m_hDC != NULL);
        if (nCount == -1)
            nCount = lstrlen(lpszString);
        return ::TextOut(m_hDC, x, y, lpszString, nCount);
    }

    BOOL ExtTextOut(int x, int y, UINT nOptions, LPCRECT lpRect, LPCTSTR lpszString, int nCount = -1, LPINT lpDxWidths = NULL)
    {
        assert(m_hDC != NULL);
        if (nCount == -1)
            nCount = lstrlen(lpszString);
        assert((nCount >= 0) && (nCount <= 8192));
        return ::ExtTextOut(m_hDC, x, y, nOptions, lpRect, lpszString, (UINT)nCount, lpDxWidths);
    }

    SIZE TabbedTextOut(int x, int y, LPCTSTR lpszString, int nCount = -1, int nTabPositions = 0, LPINT lpnTabStopPositions = NULL, int nTabOrigin = 0)
    {
        assert(m_hDC != NULL);
        if (nCount == -1)
            nCount = lstrlen(lpszString);
        LONG lRes = ::TabbedTextOut(m_hDC, x, y, lpszString, nCount, nTabPositions, lpnTabStopPositions, nTabOrigin);
        SIZE size = { GET_X_LPARAM(lRes), GET_Y_LPARAM(lRes) };
        return size;
    }

    int DrawText(LPCTSTR lpstrText, int cchText, LPRECT lpRect, UINT uFormat)
    {
        assert(m_hDC != NULL);
        assert((uFormat & DT_MODIFYSTRING) == 0);
        return ::DrawText(m_hDC, lpstrText, cchText, lpRect, uFormat);
    }

    int DrawText(LPTSTR lpstrText, int cchText, LPRECT lpRect, UINT uFormat)
    {
        assert(m_hDC != NULL);
        return ::DrawText(m_hDC, lpstrText, cchText, lpRect, uFormat);
    }

    int DrawTextEx(LPTSTR lpstrText, int cchText, LPRECT lpRect, UINT uFormat, LPDRAWTEXTPARAMS lpDTParams = NULL)
    {
        assert(m_hDC != NULL);
        return ::DrawTextEx(m_hDC, lpstrText, cchText, lpRect, uFormat, lpDTParams);
    }

    // Note - ::DrawShadowText() is present only if comctl32.dll version 6 is loaded
    int DrawShadowText(LPCWSTR lpstrText, int cchText, LPRECT lpRect, DWORD dwFlags, COLORREF clrText, COLORREF clrShadow, int xOffset, int yOffset)
    {
        assert(m_hDC != NULL);
        assert(lpRect != NULL);
        return ::DrawShadowText(m_hDC, lpstrText, cchText, lpRect, dwFlags, clrText, clrShadow, xOffset, yOffset);
    }

    BOOL GetTextExtent(LPCTSTR lpszString, int nCount, LPSIZE lpSize) const
    {
        assert(m_hDC != NULL);
        if (nCount == -1)
            nCount = lstrlen(lpszString);
        return ::GetTextExtentPoint32(m_hDC, lpszString, nCount, lpSize);
    }

    BOOL GetTextExtentExPoint(LPCTSTR lpszString, int cchString, LPSIZE lpSize, int nMaxExtent, LPINT lpnFit = NULL, LPINT alpDx = NULL)
    {
        assert(m_hDC != NULL);
        return ::GetTextExtentExPoint(m_hDC, lpszString, cchString, nMaxExtent, lpnFit, alpDx, lpSize);
    }

    DWORD GetTabbedTextExtent(LPCTSTR lpszString, int nCount = -1, int nTabPositions = 0, LPINT lpnTabStopPositions = NULL) const
    {
        assert(m_hDC != NULL);
        if (nCount == -1)
            nCount = lstrlen(lpszString);
        return ::GetTabbedTextExtent(m_hDC, lpszString, nCount, nTabPositions, lpnTabStopPositions);
    }

    BOOL GrayString(HBRUSH hBrush, BOOL(CALLBACK* lpfnOutput)(HDC, LPARAM, int), LPARAM lpData, int nCount, int x, int y, int nWidth, int nHeight)
    {
        assert(m_hDC != NULL);
        return ::GrayString(m_hDC, hBrush, (GRAYSTRINGPROC)lpfnOutput, lpData, nCount, x, y, nWidth, nHeight);
    }

    UINT GetTextAlign() const
    {
        assert(m_hDC != NULL);
        return ::GetTextAlign(m_hDC);
    }

    UINT SetTextAlign(UINT nFlags)
    {
        assert(m_hDC != NULL);
        return ::SetTextAlign(m_hDC, nFlags);
    }

    int GetTextFace(LPTSTR lpszFacename, int nCount) const
    {
        assert(m_hDC != NULL);
        return ::GetTextFace(m_hDC, nCount, lpszFacename);
    }

    int GetTextFaceLen() const
    {
        assert(m_hDC != NULL);
        return ::GetTextFace(m_hDC, 0, NULL);
    }

    int GetTextFace(BDString& strFace) const
    {
        assert(m_hDC != NULL);

        int nLen = GetTextFaceLen();
        if (nLen == 0)
            return 0;

        LPTSTR lpstr = strFace.GetBufferSetLength(nLen);
        if (lpstr == NULL)
            return 0;
        int nRet = GetTextFace(lpstr, nLen);
        strFace.ReleaseBuffer();
        return nRet;
    }

    BOOL GetTextMetrics(LPTEXTMETRIC lpMetrics) const
    {
        assert(m_hDC != NULL);
        return ::GetTextMetrics(m_hDC, lpMetrics);
    }

    int SetTextJustification(int nBreakExtra, int nBreakCount)
    {
        assert(m_hDC != NULL);
        return ::SetTextJustification(m_hDC, nBreakExtra, nBreakCount);
    }

    int GetTextCharacterExtra() const
    {
        assert(m_hDC != NULL);
        return ::GetTextCharacterExtra(m_hDC);
    }

    int SetTextCharacterExtra(int nCharExtra)
    {
        assert(m_hDC != NULL);
        return ::SetTextCharacterExtra(m_hDC, nCharExtra);
    }

    // Advanced Drawing
    BOOL DrawEdge(LPRECT lpRect, UINT nEdge, UINT nFlags)
    {
        assert(m_hDC != NULL);
        return ::DrawEdge(m_hDC, lpRect, nEdge, nFlags);
    }

    BOOL DrawFrameControl(LPRECT lpRect, UINT nType, UINT nState)
    {
        assert(m_hDC != NULL);
        return ::DrawFrameControl(m_hDC, lpRect, nType, nState);
    }

    // Scrolling Functions
    BOOL ScrollDC(int dx, int dy, LPCRECT lpRectScroll, LPCRECT lpRectClip, HRGN hRgnUpdate, LPRECT lpRectUpdate)
    {
        assert(m_hDC != NULL);
        return ::ScrollDC(m_hDC, dx, dy, lpRectScroll, lpRectClip, hRgnUpdate, lpRectUpdate);
    }

    // Font Functions
    BOOL GetCharWidth(UINT nFirstChar, UINT nLastChar, LPINT lpBuffer) const
    {
        assert(m_hDC != NULL);
        return ::GetCharWidth(m_hDC, nFirstChar, nLastChar, lpBuffer);
    }

    // GetCharWidth32 is not supported under Win9x
    BOOL GetCharWidth32(UINT nFirstChar, UINT nLastChar, LPINT lpBuffer) const
    {
        assert(m_hDC != NULL);
        return ::GetCharWidth32(m_hDC, nFirstChar, nLastChar, lpBuffer);
    }

    DWORD SetMapperFlags(DWORD dwFlag)
    {
        assert(m_hDC != NULL);
        return ::SetMapperFlags(m_hDC, dwFlag);
    }

    BOOL GetAspectRatioFilter(LPSIZE lpSize) const
    {
        assert(m_hDC != NULL);
        return ::GetAspectRatioFilterEx(m_hDC, lpSize);
    }

    BOOL GetCharABCWidths(UINT nFirstChar, UINT nLastChar, LPABC lpabc) const
    {
        assert(m_hDC != NULL);
        return ::GetCharABCWidths(m_hDC, nFirstChar, nLastChar, lpabc);
    }

    DWORD GetFontData(DWORD dwTable, DWORD dwOffset, LPVOID lpData, DWORD cbData) const
    {
        assert(m_hDC != NULL);
        return ::GetFontData(m_hDC, dwTable, dwOffset, lpData, cbData);
    }

    int GetKerningPairs(int nPairs, LPKERNINGPAIR lpkrnpair) const
    {
        assert(m_hDC != NULL);
        return ::GetKerningPairs(m_hDC, nPairs, lpkrnpair);
    }

    UINT GetOutlineTextMetrics(UINT cbData, LPOUTLINETEXTMETRIC lpotm) const
    {
        assert(m_hDC != NULL);
        return ::GetOutlineTextMetrics(m_hDC, cbData, lpotm);
    }

    DWORD GetGlyphOutline(UINT nChar, UINT nFormat, LPGLYPHMETRICS lpgm, DWORD cbBuffer, LPVOID lpBuffer, const MAT2* lpmat2) const
    {
        assert(m_hDC != NULL);
        return ::GetGlyphOutline(m_hDC, nChar, nFormat, lpgm, cbBuffer, lpBuffer, lpmat2);
    }

    BOOL GetCharABCWidths(UINT nFirstChar, UINT nLastChar, LPABCFLOAT lpABCF) const
    {
        assert(m_hDC != NULL);
        return ::GetCharABCWidthsFloat(m_hDC, nFirstChar, nLastChar, lpABCF);
    }

    BOOL GetCharWidth(UINT nFirstChar, UINT nLastChar, float* lpFloatBuffer) const
    {
        assert(m_hDC != NULL);
        return ::GetCharWidthFloat(m_hDC, nFirstChar, nLastChar, lpFloatBuffer);
    }

    // Printer/Device Escape Functions
    int Escape(int nEscape, int nCount, LPCSTR lpszInData, LPVOID lpOutData)
    {
        assert(m_hDC != NULL);
        return ::Escape(m_hDC, nEscape, nCount, lpszInData, lpOutData);
    }

    int Escape(int nEscape, int nInputSize, LPCSTR lpszInputData,
        int nOutputSize, LPSTR lpszOutputData)
    {
        assert(m_hDC != NULL);
        return ::ExtEscape(m_hDC, nEscape, nInputSize, lpszInputData, nOutputSize, lpszOutputData);
    }

    int DrawEscape(int nEscape, int nInputSize, LPCSTR lpszInputData)
    {
        assert(m_hDC != NULL);
        return ::DrawEscape(m_hDC, nEscape, nInputSize, lpszInputData);
    }

    // Escape helpers
    int StartDoc(LPCTSTR lpszDocName)  // old Win3.0 version
    {
        DOCINFO di = { 0 };
        di.cbSize = sizeof(DOCINFO);
        di.lpszDocName = lpszDocName;
        return StartDoc(&di);
    }

    int StartDoc(LPDOCINFO lpDocInfo)
    {
        assert(m_hDC != NULL);
        return ::StartDoc(m_hDC, lpDocInfo);
    }

    int StartPage()
    {
        assert(m_hDC != NULL);
        return ::StartPage(m_hDC);
    }

    int EndPage()
    {
        assert(m_hDC != NULL);
        return ::EndPage(m_hDC);
    }

    int SetAbortProc(BOOL(CALLBACK* lpfn)(HDC, int))
    {
        assert(m_hDC != NULL);
        return ::SetAbortProc(m_hDC, (ABORTPROC)lpfn);
    }

    int AbortDoc()
    {
        assert(m_hDC != NULL);
        return ::AbortDoc(m_hDC);
    }

    int EndDoc()
    {
        assert(m_hDC != NULL);
        return ::EndDoc(m_hDC);
    }

    // MetaFile Functions
    BOOL PlayMetaFile(HMETAFILE hMF)
    {
        assert(m_hDC != NULL);
        if (::GetDeviceCaps(m_hDC, TECHNOLOGY) == DT_METAFILE)
        {
            // playing metafile in metafile, just use core windows API
            return ::PlayMetaFile(m_hDC, hMF);
        }

        // for special playback, lParam == pDC
        return ::EnumMetaFile(m_hDC, hMF, EnumMetaFileProc, (LPARAM)this);
    }

    BOOL PlayMetaFile(HENHMETAFILE hEnhMetaFile, LPCRECT lpBounds)
    {
        assert(m_hDC != NULL);
        return ::PlayEnhMetaFile(m_hDC, hEnhMetaFile, lpBounds);
    }

    BOOL AddMetaFileComment(UINT nDataSize, const BYTE* pCommentData) // can be used for enhanced metafiles only
    {
        assert(m_hDC != NULL);
        return ::GdiComment(m_hDC, nDataSize, pCommentData);
    }

    // Special handling for metafile playback
    static int CALLBACK EnumMetaFileProc(HDC hDC, HANDLETABLE* pHandleTable, METARECORD* pMetaRec, int nHandles, LPARAM lParam)
    {
        BDDCT<false>* pDC = (BDDCT<false>*)lParam;

        switch (pMetaRec->rdFunction)
        {
        case META_SETMAPMODE:
            pDC->SetMapMode((int)(short)pMetaRec->rdParm[0]);
            break;
        case META_SETWINDOWEXT:
            pDC->SetWindowExt((int)(short)pMetaRec->rdParm[1], (int)(short)pMetaRec->rdParm[0]);
            break;
        case META_SETWINDOWORG:
            pDC->SetWindowOrg((int)(short)pMetaRec->rdParm[1], (int)(short)pMetaRec->rdParm[0]);
            break;
        case META_SETVIEWPORTEXT:
            pDC->SetViewportExt((int)(short)pMetaRec->rdParm[1], (int)(short)pMetaRec->rdParm[0]);
            break;
        case META_SETVIEWPORTORG:
            pDC->SetViewportOrg((int)(short)pMetaRec->rdParm[1], (int)(short)pMetaRec->rdParm[0]);
            break;
        case META_SCALEWINDOWEXT:
            pDC->ScaleWindowExt((int)(short)pMetaRec->rdParm[3], (int)(short)pMetaRec->rdParm[2],
                (int)(short)pMetaRec->rdParm[1], (int)(short)pMetaRec->rdParm[0]);
            break;
        case META_SCALEVIEWPORTEXT:
            pDC->ScaleViewportExt((int)(short)pMetaRec->rdParm[3], (int)(short)pMetaRec->rdParm[2],
                (int)(short)pMetaRec->rdParm[1], (int)(short)pMetaRec->rdParm[0]);
            break;
        case META_OFFSETVIEWPORTORG:
            pDC->OffsetViewportOrg((int)(short)pMetaRec->rdParm[1], (int)(short)pMetaRec->rdParm[0]);
            break;
        case META_SAVEDC:
            pDC->SaveDC();
            break;
        case META_RESTOREDC:
            pDC->RestoreDC((int)(short)pMetaRec->rdParm[0]);
            break;
        case META_SETBKCOLOR:
            pDC->SetBkColor(*(UNALIGNED COLORREF*) & pMetaRec->rdParm[0]);
            break;
        case META_SETTEXTCOLOR:
            pDC->SetTextColor(*(UNALIGNED COLORREF*) & pMetaRec->rdParm[0]);
            break;

            // need to watch out for SelectObject(HFONT), for custom font mapping
        case META_SELECTOBJECT:
        {
            HGDIOBJ hObject = pHandleTable->objectHandle[pMetaRec->rdParm[0]];
            UINT nObjType = ::GetObjectType(hObject);
            if (nObjType == 0)
            {
                // object type is unknown, determine if it is a font
                HFONT hStockFont = (HFONT)::GetStockObject(SYSTEM_FONT);
                HFONT hFontOld = (HFONT)::SelectObject(pDC->m_hDC, hStockFont);
                HGDIOBJ hObjOld = ::SelectObject(pDC->m_hDC, hObject);
                if (hObjOld == hStockFont)
                {
                    // got the stock object back, so must be selecting a font
                    pDC->SelectFont((HFONT)hObject);
                    break;  // don't play the default record
                }
                else
                {
                    // didn't get the stock object back, so restore everything
                    ::SelectObject(pDC->m_hDC, hFontOld);
                    ::SelectObject(pDC->m_hDC, hObjOld);
                }
                // and fall through to PlayMetaFileRecord...
            }
            else if (nObjType == OBJ_FONT)
            {
                // play back as CDCHandle::SelectFont(HFONT)
                pDC->SelectFont((HFONT)hObject);
                break;  // don't play the default record
            }
        }
        // fall through...

        default:
            ::PlayMetaFileRecord(hDC, pHandleTable, pMetaRec, nHandles);
            break;
        }

        return 1;
    }

    // Path Functions
    BOOL AbortPath()
    {
        assert(m_hDC != NULL);
        return ::AbortPath(m_hDC);
    }

    BOOL BeginPath()
    {
        assert(m_hDC != NULL);
        return ::BeginPath(m_hDC);
    }

    BOOL CloseFigure()
    {
        assert(m_hDC != NULL);
        return ::CloseFigure(m_hDC);
    }

    BOOL EndPath()
    {
        assert(m_hDC != NULL);
        return ::EndPath(m_hDC);
    }

    BOOL FillPath()
    {
        assert(m_hDC != NULL);
        return ::FillPath(m_hDC);
    }

    BOOL FlattenPath()
    {
        assert(m_hDC != NULL);
        return ::FlattenPath(m_hDC);
    }

    BOOL StrokeAndFillPath()
    {
        assert(m_hDC != NULL);
        return ::StrokeAndFillPath(m_hDC);
    }

    BOOL StrokePath()
    {
        assert(m_hDC != NULL);
        return ::StrokePath(m_hDC);
    }

    BOOL WidenPath()
    {
        assert(m_hDC != NULL);
        return ::WidenPath(m_hDC);
    }

    BOOL GetMiterLimit(PFLOAT pfMiterLimit) const
    {
        assert(m_hDC != NULL);
        return ::GetMiterLimit(m_hDC, pfMiterLimit);
    }

    BOOL SetMiterLimit(float fMiterLimit)
    {
        assert(m_hDC != NULL);
        return ::SetMiterLimit(m_hDC, fMiterLimit, NULL);
    }

    int GetPath(LPPOINT lpPoints, LPBYTE lpTypes, int nCount) const
    {
        assert(m_hDC != NULL);
        return ::GetPath(m_hDC, lpPoints, lpTypes, nCount);
    }

    BOOL SelectClipPath(int nMode)
    {
        assert(m_hDC != NULL);
        return ::SelectClipPath(m_hDC, nMode);
    }

    // Misc Helper Functions
    static BDBrushHandle PASCAL GetHalftoneBrush()
    {
        HBRUSH halftoneBrush = NULL;
        WORD grayPattern[8] = {};
        for (int i = 0; i < 8; i++)
            grayPattern[i] = (WORD)(0x5555 << (i & 1));
        HBITMAP grayBitmap = CreateBitmap(8, 8, 1, 1, &grayPattern);
        if (grayBitmap != NULL)
        {
            halftoneBrush = ::CreatePatternBrush(grayBitmap);
            DeleteObject(grayBitmap);
        }
        return BDBrushHandle(halftoneBrush);
    }

    void DrawDragRect(LPCRECT lpRect, SIZE size, LPCRECT lpRectLast, SIZE sizeLast, HBRUSH hBrush = NULL, HBRUSH hBrushLast = NULL)
    {
        // first, determine the update region and select it
        BDRgn rgnOutside;
        rgnOutside.CreateRectRgnIndirect(lpRect);
        RECT rect = *lpRect;
        ::InflateRect(&rect, -size.cx, -size.cy);
        ::IntersectRect(&rect, &rect, lpRect);
        BDRgn rgnInside;
        rgnInside.CreateRectRgnIndirect(&rect);
        BDRgn rgnNew;
        rgnNew.CreateRectRgn(0, 0, 0, 0);
        rgnNew.CombineRgn(rgnOutside, rgnInside, RGN_XOR);

        HBRUSH hBrushOld = NULL;
        BDBrush brushHalftone;
        if (hBrush == NULL)
            brushHalftone = hBrush = BDDCT<false>::GetHalftoneBrush();
        if (hBrushLast == NULL)
            hBrushLast = hBrush;

        BDRgn rgnLast;
        BDRgn rgnUpdate;
        if (lpRectLast != NULL)
        {
            // find difference between new region and old region
            rgnLast.CreateRectRgn(0, 0, 0, 0);
            rgnOutside.SetRectRgn(lpRectLast->left, lpRectLast->top, lpRectLast->right, lpRectLast->bottom);
            rect = *lpRectLast;
            ::InflateRect(&rect, -sizeLast.cx, -sizeLast.cy);
            ::IntersectRect(&rect, &rect, lpRectLast);
            rgnInside.SetRectRgn(rect.left, rect.top, rect.right, rect.bottom);
            rgnLast.CombineRgn(rgnOutside, rgnInside, RGN_XOR);

            // only diff them if brushes are the same
            if (hBrush == hBrushLast)
            {
                rgnUpdate.CreateRectRgn(0, 0, 0, 0);
                rgnUpdate.CombineRgn(rgnLast, rgnNew, RGN_XOR);
            }
        }
        if ((hBrush != hBrushLast) && (lpRectLast != NULL))
        {
            // brushes are different -- erase old region first
            SelectClipRgn(rgnLast);
            GetClipBox(&rect);
            hBrushOld = SelectBrush(hBrushLast);
            PatBlt(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, PATINVERT);
            SelectBrush(hBrushOld);
            hBrushOld = NULL;
        }

        // draw into the update/new region
        SelectClipRgn(rgnUpdate.IsNull() ? rgnNew : rgnUpdate);
        GetClipBox(&rect);
        hBrushOld = SelectBrush(hBrush);
        PatBlt(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, PATINVERT);

        // cleanup DC
        if (hBrushOld != NULL)
            SelectBrush(hBrushOld);
        SelectClipRgn(NULL);
    }

    void FillSolidRect(LPCRECT lpRect, COLORREF clr)
    {
        assert(m_hDC != NULL);

        COLORREF clrOld = ::SetBkColor(m_hDC, clr);
        assert(clrOld != CLR_INVALID);
        if (clrOld != CLR_INVALID)
        {
            ::ExtTextOut(m_hDC, 0, 0, ETO_OPAQUE, lpRect, NULL, 0, NULL);
            ::SetBkColor(m_hDC, clrOld);
        }
    }

    void FillSolidRect(int x, int y, int cx, int cy, COLORREF clr)
    {
        assert(m_hDC != NULL);

        RECT rect = { x, y, x + cx, y + cy };
        FillSolidRect(&rect, clr);
    }

    void Draw3dRect(LPCRECT lpRect, COLORREF clrTopLeft, COLORREF clrBottomRight)
    {
        Draw3dRect(lpRect->left, lpRect->top, lpRect->right - lpRect->left,
            lpRect->bottom - lpRect->top, clrTopLeft, clrBottomRight);
    }

    void Draw3dRect(int x, int y, int cx, int cy, COLORREF clrTopLeft, COLORREF clrBottomRight)
    {
        FillSolidRect(x, y, cx - 1, 1, clrTopLeft);
        FillSolidRect(x, y, 1, cy - 1, clrTopLeft);
        FillSolidRect(x + cx, y, -1, cy, clrBottomRight);
        FillSolidRect(x, y + cy, cx, -1, clrBottomRight);
    }

    // DIB support
    int SetDIBitsToDevice(int x, int y, DWORD dwWidth, DWORD dwHeight, int xSrc, int ySrc, UINT uStartScan, UINT cScanLines, CONST VOID* lpvBits, CONST BITMAPINFO* lpbmi, UINT uColorUse)
    {
        assert(m_hDC != NULL);
        return ::SetDIBitsToDevice(m_hDC, x, y, dwWidth, dwHeight, xSrc, ySrc, uStartScan, cScanLines, lpvBits, lpbmi, uColorUse);
    }

    int StretchDIBits(int x, int y, int nWidth, int nHeight, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight, CONST VOID* lpvBits, CONST BITMAPINFO* lpbmi, UINT uColorUse, DWORD dwRop)
    {
        assert(m_hDC != NULL);
        return ::StretchDIBits(m_hDC, x, y, nWidth, nHeight, xSrc, ySrc, nSrcWidth, nSrcHeight, lpvBits, lpbmi, uColorUse, dwRop);
    }

    UINT GetDIBColorTable(UINT uStartIndex, UINT cEntries, RGBQUAD* pColors) const
    {
        assert(m_hDC != NULL);
        return ::GetDIBColorTable(m_hDC, uStartIndex, cEntries, pColors);
    }

    UINT SetDIBColorTable(UINT uStartIndex, UINT cEntries, CONST RGBQUAD* pColors)
    {
        assert(m_hDC != NULL);
        return ::SetDIBColorTable(m_hDC, uStartIndex, cEntries, pColors);
    }

    // OpenGL support
    int ChoosePixelFormat(CONST PIXELFORMATDESCRIPTOR* ppfd)
    {
        assert(m_hDC != NULL);
        return ::ChoosePixelFormat(m_hDC, ppfd);
    }

    int DescribePixelFormat(int iPixelFormat, UINT nBytes, LPPIXELFORMATDESCRIPTOR ppfd)
    {
        assert(m_hDC != NULL);
        return ::DescribePixelFormat(m_hDC, iPixelFormat, nBytes, ppfd);
    }

    int GetPixelFormat() const
    {
        assert(m_hDC != NULL);
        return ::GetPixelFormat(m_hDC);
    }

    BOOL SetPixelFormat(int iPixelFormat, CONST PIXELFORMATDESCRIPTOR* ppfd)
    {
        assert(m_hDC != NULL);
        return ::SetPixelFormat(m_hDC, iPixelFormat, ppfd);
    }

    BOOL SwapBuffers()
    {
        assert(m_hDC != NULL);
        return ::SwapBuffers(m_hDC);
    }

    HGLRC wglCreateContext()
    {
        assert(m_hDC != NULL);
        return ::wglCreateContext(m_hDC);
    }

    HGLRC wglCreateLayerContext(int iLayerPlane)
    {
        assert(m_hDC != NULL);
        return ::wglCreateLayerContext(m_hDC, iLayerPlane);
    }

    BOOL wglMakeCurrent(HGLRC hglrc)
    {
        assert(m_hDC != NULL);
        return ::wglMakeCurrent(m_hDC, hglrc);
    }

    BOOL wglUseFontBitmaps(DWORD dwFirst, DWORD dwCount, DWORD listBase)
    {
        assert(m_hDC != NULL);
        return ::wglUseFontBitmaps(m_hDC, dwFirst, dwCount, listBase);
    }

    BOOL wglUseFontOutlines(DWORD dwFirst, DWORD dwCount, DWORD listBase, FLOAT deviation, FLOAT extrusion, int format, LPGLYPHMETRICSFLOAT lpgmf)
    {
        assert(m_hDC != NULL);
        return ::wglUseFontOutlines(m_hDC, dwFirst, dwCount, listBase, deviation, extrusion, format, lpgmf);
    }

    BOOL wglDescribeLayerPlane(int iPixelFormat, int iLayerPlane, UINT nBytes, LPLAYERPLANEDESCRIPTOR plpd)
    {
        assert(m_hDC != NULL);
        return ::wglDescribeLayerPlane(m_hDC, iPixelFormat, iLayerPlane, nBytes, plpd);
    }

    int wglSetLayerPaletteEntries(int iLayerPlane, int iStart, int cEntries, CONST COLORREF* pclr)
    {
        assert(m_hDC != NULL);
        return ::wglSetLayerPaletteEntries(m_hDC, iLayerPlane, iStart, cEntries, pclr);
    }

    int wglGetLayerPaletteEntries(int iLayerPlane, int iStart, int cEntries, COLORREF* pclr)
    {
        assert(m_hDC != NULL);
        return ::wglGetLayerPaletteEntries(m_hDC, iLayerPlane, iStart, cEntries, pclr);
    }

    BOOL wglRealizeLayerPalette(int iLayerPlane, BOOL bRealize)
    {
        assert(m_hDC != NULL);
        return ::wglRealizeLayerPalette(m_hDC, iLayerPlane, bRealize);
    }

    BOOL wglSwapLayerBuffers(UINT uPlanes)
    {
        assert(m_hDC != NULL);
        return ::wglSwapLayerBuffers(m_hDC, uPlanes);
    }


    COLORREF GetDCPenColor() const
    {
        assert(m_hDC != NULL);
        return ::GetDCPenColor(m_hDC);
    }

    COLORREF SetDCPenColor(COLORREF clr)
    {
        assert(m_hDC != NULL);
        return ::SetDCPenColor(m_hDC, clr);
    }

    COLORREF GetDCBrushColor() const
    {
        assert(m_hDC != NULL);
        return ::GetDCBrushColor(m_hDC);
    }

    COLORREF SetDCBrushColor(COLORREF clr)
    {
        assert(m_hDC != NULL);
        return ::SetDCBrushColor(m_hDC, clr);
    }

    DWORD GetFontUnicodeRanges(LPGLYPHSET lpgs) const
    {
        assert(m_hDC != NULL);
        return ::GetFontUnicodeRanges(m_hDC, lpgs);
    }

    DWORD GetGlyphIndices(LPCTSTR lpstr, int cch, LPWORD pgi, DWORD dwFlags) const
    {
        assert(m_hDC != NULL);
        return ::GetGlyphIndices(m_hDC, lpstr, cch, pgi, dwFlags);
    }

    BOOL GetTextExtentPointI(LPWORD pgiIn, int cgi, LPSIZE lpSize) const
    {
        assert(m_hDC != NULL);
        return ::GetTextExtentPointI(m_hDC, pgiIn, cgi, lpSize);
    }

    BOOL GetTextExtentExPointI(LPWORD pgiIn, int cgi, int nMaxExtent, LPINT lpnFit, LPINT alpDx, LPSIZE lpSize) const
    {
        assert(m_hDC != NULL);
        return ::GetTextExtentExPointI(m_hDC, pgiIn, cgi, nMaxExtent, lpnFit, alpDx, lpSize);
    }

    BOOL GetCharWidthI(UINT giFirst, UINT cgi, LPWORD pgi, LPINT lpBuffer) const
    {
        assert(m_hDC != NULL);
        return ::GetCharWidthI(m_hDC, giFirst, cgi, pgi, lpBuffer);
    }

    BOOL GetCharABCWidthsI(UINT giFirst, UINT cgi, LPWORD pgi, LPABC lpabc) const
    {
        assert(m_hDC != NULL);
        return ::GetCharABCWidthsI(m_hDC, giFirst, cgi, pgi, lpabc);
    }

    // New for Windows 2000 and Windows 98
    BOOL ColorCorrectPalette(HPALETTE hPalette, DWORD dwFirstEntry, DWORD dwNumOfEntries)
    {
        assert(m_hDC != NULL);
        return ::ColorCorrectPalette(m_hDC, hPalette, dwFirstEntry, dwNumOfEntries);
    }
};

typedef BDDCT<false>   BDDCHandle;
typedef BDDCT<true>    BDDC;


///////////////////////////////////////////////////////////////////////////////
// DDC Helpers

class BDPaintDC : public BDDC
{
public:
    // Data members
    HWND m_hWnd;
    PAINTSTRUCT m_ps;

    // Constructor/destructor
    BDPaintDC(HWND hWnd)
    {
        assert(::IsWindow(hWnd));
        m_hWnd = hWnd;
        ZeroMemory(&m_ps, sizeof(m_ps));
        m_hDC = ::BeginPaint(hWnd, &m_ps);
    }

    ~BDPaintDC()
    {
        assert(m_hDC != NULL);
        assert(::IsWindow(m_hWnd));
        ::EndPaint(m_hWnd, &m_ps);
        Detach();
    }
};

class BDClientDC : public BDDC
{
public:
    // Data members
    HWND m_hWnd;

    // Constructor/destructor
    BDClientDC(HWND hWnd)
    {
        assert((hWnd == NULL) || ::IsWindow(hWnd));
        m_hWnd = hWnd;
        m_hDC = ::GetDC(hWnd);
    }

    ~BDClientDC()
    {
        assert(m_hDC != NULL);
        ::ReleaseDC(m_hWnd, Detach());
    }
};

class BDClientDCEx : public BDDC
{
public:
    // Data members
    HWND m_hWnd;

    // Constructor/destructor
    BDClientDCEx(HWND hWnd, HRGN hRgn)
    {
        assert(hWnd == NULL || ::IsWindow(hWnd));
        m_hWnd = hWnd;
        RECT r;
        int t = ::GetRgnBox(hRgn, &r);
        if (t == 0)
        {
            m_hDC = ::GetDC(hWnd);
        }
        else if (t == NULLREGION)
        {
            m_hDC = ::GetDC(hWnd);
        }
        else if (t == SIMPLEREGION)
        {
            m_hDC = ::GetDCEx(hWnd, hRgn, DCX_WINDOW | DCX_INTERSECTRGN);
        }
        else if (t == COMPLEXREGION)
        {
            m_hDC = ::GetDC(hWnd);
        }
    }

    ~BDClientDCEx()
    {
        assert(m_hDC != NULL);
        ::ReleaseDC(m_hWnd, Detach());
    }
};

class BDWindowDC : public BDDC
{
public:
    // Data members
    HWND m_hWnd;

    // Constructor/destructor
    BDWindowDC(HWND hWnd)
    {
        assert(hWnd == NULL || ::IsWindow(hWnd));
        m_hWnd = hWnd;
        m_hDC = ::GetWindowDC(hWnd);
    }

    ~BDWindowDC()
    {
        assert(m_hDC != NULL);
        ::ReleaseDC(m_hWnd, Detach());
    }
};

class BDMemoryDC : public BDDC
{
public:
    // Data members
    HDC m_hDCOriginal;
    RECT m_rcPaint;
    BDBitmap m_bmp;
    HBITMAP m_hBmpOld;

    // Constructor/destructor
    BDMemoryDC(HDC hDC, const RECT& rcPaint) : m_hDCOriginal(hDC), m_hBmpOld(NULL)
    {
        m_rcPaint = rcPaint;
        CreateCompatibleDC(m_hDCOriginal);
        assert(m_hDC != NULL);
        m_bmp.CreateCompatibleBitmap(m_hDCOriginal, m_rcPaint.right - m_rcPaint.left, m_rcPaint.bottom - m_rcPaint.top);
        assert(m_bmp.m_hBitmap != NULL);
        m_hBmpOld = SelectBitmap(m_bmp);
        SetViewportOrg(-m_rcPaint.left, -m_rcPaint.top);
    }

    ~BDMemoryDC()
    {
        ::BitBlt(m_hDCOriginal, m_rcPaint.left, m_rcPaint.top, m_rcPaint.right - m_rcPaint.left, m_rcPaint.bottom - m_rcPaint.top, m_hDC, m_rcPaint.left, m_rcPaint.top, SRCCOPY);
        SelectBitmap(m_hBmpOld);
    }
};
