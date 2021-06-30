//
//  BDMisc.h
//
//  Copyright 2020. All rights reserved.
//

#pragma once

#include <windows.h>
#include <tchar.h>
#include <assert.h>
#include "BDWinApp.h"

///////////////////////////////////////////////////////////////////////////////
// Classes in this file:
//
// BDSize
// BDPoint
// BDRect
// BDString
//

// forward declarations
class BDSize;
class BDPoint;
class BDRect;

///////////////////////////////////////////////////////////////////////////////
// BDSize - Wrapper for Windows SIZE structure.

class BDSize : public SIZE
{
public:
// Constructors
    BDSize()
    {
        cx = 0;
        cy = 0;
    }

    BDSize(int initCX, int initCY)
    {
        cx = initCX;
        cy = initCY;
    }

    BDSize(SIZE initSize)
    {
        *(SIZE*)this = initSize;
    }

    BDSize(POINT initPt)
    {
        *(POINT*)this = initPt;
    }

    BDSize(DWORD dwSize)
    {
        cx = (short)LOWORD(dwSize);
        cy = (short)HIWORD(dwSize);
    }

// Operations
    BOOL operator ==(SIZE size) const
    {
        return (cx == size.cx && cy == size.cy);
    }

    BOOL operator !=(SIZE size) const
    {
        return (cx != size.cx || cy != size.cy);
    }

    void operator +=(SIZE size)
    {
        cx += size.cx;
        cy += size.cy;
    }

    void operator -=(SIZE size)
    {
        cx -= size.cx;
        cy -= size.cy;
    }

    void SetSize(int CX, int CY)
    {
        cx = CX;
        cy = CY;
    }

// Operators returning BDSize values
    BDSize operator +(SIZE size) const
    {
        return BDSize(cx + size.cx, cy + size.cy);
    }

    BDSize operator -(SIZE size) const
    {
        return BDSize(cx - size.cx, cy - size.cy);
    }

    BDSize operator -() const
    {
        return BDSize(-cx, -cy);
    }

// Operators returning BDPoint values
    BDPoint operator +(POINT point) const;
    BDPoint operator -(POINT point) const;

// Operators returning BDRect values
    BDRect operator +(const RECT* lpRect) const;
    BDRect operator -(const RECT* lpRect) const;
};


///////////////////////////////////////////////////////////////////////////////
// BDPoint - Wrapper for Windows POINT structure.

class BDPoint : public POINT
{
public:
// Constructors
    BDPoint()
    {
        x = 0;
        y = 0;
    }

    BDPoint(int initX, int initY)
    {
        x = initX;
        y = initY;
    }

    BDPoint(POINT initPt)
    {
        *(POINT*)this = initPt;
    }

    BDPoint(SIZE initSize)
    {
        *(SIZE*)this = initSize;
    }

    BDPoint(DWORD dwPoint)
    {
        x = (short)LOWORD(dwPoint);
        y = (short)HIWORD(dwPoint);
    }

// Operations
    void Offset(int xOffset, int yOffset)
    {
        x += xOffset;
        y += yOffset;
    }

    void Offset(POINT point)
    {
        x += point.x;
        y += point.y;
    }

    void Offset(SIZE size)
    {
        x += size.cx;
        y += size.cy;
    }

    BOOL operator ==(POINT point) const
    {
        return (x == point.x && y == point.y);
    }

    BOOL operator !=(POINT point) const
    {
        return (x != point.x || y != point.y);
    }

    void operator +=(SIZE size)
    {
        x += size.cx;
        y += size.cy;
    }

    void operator -=(SIZE size)
    {
        x -= size.cx;
        y -= size.cy;
    }

    void operator +=(POINT point)
    {
        x += point.x;
        y += point.y;
    }

    void operator -=(POINT point)
    {
        x -= point.x;
        y -= point.y;
    }

    void SetPoint(int X, int Y)
    {
        x = X;
        y = Y;
    }

// Operators returning BDPoint values
    BDPoint operator +(SIZE size) const
    {
        return BDPoint(x + size.cx, y + size.cy);
    }

    BDPoint operator -(SIZE size) const
    {
        return BDPoint(x - size.cx, y - size.cy);
    }

    BDPoint operator -() const
    {
        return BDPoint(-x, -y);
    }

    BDPoint operator +(POINT point) const
    {
        return BDPoint(x + point.x, y + point.y);
    }

// Operators returning BDSize values
    BDSize operator -(POINT point) const
    {
        return BDSize(x - point.x, y - point.y);
    }

// Operators returning BDRect values
    BDRect operator +(const RECT* lpRect) const;
    BDRect operator -(const RECT* lpRect) const;
};


///////////////////////////////////////////////////////////////////////////////
// BDRect - Wrapper for Windows RECT structure.

class BDRect : public RECT
{
public:
// Constructors
    BDRect()
    {
        left = 0;
        top = 0;
        right = 0;
        bottom = 0;
    }

    BDRect(int l, int t, int r, int b)
    {
        left = l;
        top = t;
        right = r;
        bottom = b;
    }

    BDRect(const RECT& srcRect)
    {
        ::CopyRect(this, &srcRect);
    }

    BDRect(LPCRECT lpSrcRect)
    {
        ::CopyRect(this, lpSrcRect);
    }

    BDRect(POINT point, SIZE size)
    {
        right = (left = point.x) + size.cx;
        bottom = (top = point.y) + size.cy;
    }

    BDRect(POINT topLeft, POINT bottomRight)
    {
        left = topLeft.x;
        top = topLeft.y;
        right = bottomRight.x;
        bottom = bottomRight.y;
    }

// Attributes (in addition to RECT members)
    int Width() const
    {
        return right - left;
    }

    int Height() const
    {
        return bottom - top;
    }

    BDSize Size() const
    {
        return BDSize(right - left, bottom - top);
    }

    BDPoint& TopLeft()
    {
        return *((BDPoint*)this);
    }

    BDPoint& BottomRight()
    {
        return *((BDPoint*)this + 1);
    }

    const BDPoint& TopLeft() const
    {
        return *((BDPoint*)this);
    }

    const BDPoint& BottomRight() const
    {
        return *((BDPoint*)this + 1);
    }

    BDPoint CenterPoint() const
    {
        return BDPoint((left + right) / 2, (top + bottom) / 2);
    }

    // convert between BDRect and LPRECT/LPCRECT (no need for &)
    operator LPRECT()
    {
        return this;
    }

    operator LPCRECT() const
    {
        return this;
    }

    BOOL IsRectEmpty() const
    {
        return ::IsRectEmpty(this);
    }

    BOOL IsRectNull() const
    {
        return (left == 0 && right == 0 && top == 0 && bottom == 0);
    }

    BOOL PtInRect(POINT point) const
    {
        return ::PtInRect(this, point);
    }

// Operations
    void SetRect(int x1, int y1, int x2, int y2)
    {
        ::SetRect(this, x1, y1, x2, y2);
    }

    void SetRect(POINT topLeft, POINT bottomRight)
    {
        ::SetRect(this, topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);
    }

    void SetRectEmpty()
    {
        ::SetRectEmpty(this);
    }

    void CopyRect(LPCRECT lpSrcRect)
    {
        ::CopyRect(this, lpSrcRect);
    }

    BOOL EqualRect(LPCRECT lpRect) const
    {
        return ::EqualRect(this, lpRect);
    }

    void InflateRect(int x, int y)
    {
        ::InflateRect(this, x, y);
    }

    void InflateRect(SIZE size)
    {
        ::InflateRect(this, size.cx, size.cy);
    }

    void InflateRect(LPCRECT lpRect)
    {
        left -= lpRect->left;
        top -= lpRect->top;
        right += lpRect->right;
        bottom += lpRect->bottom;
    }

    void InflateRect(int l, int t, int r, int b)
    {
        left -= l;
        top -= t;
        right += r;
        bottom += b;
    }

    void DeflateRect(int x, int y)
    {
        ::InflateRect(this, -x, -y);
    }

    void DeflateRect(SIZE size)
    {
        ::InflateRect(this, -size.cx, -size.cy);
    }

    void DeflateRect(LPCRECT lpRect)
    {
        left += lpRect->left;
        top += lpRect->top;
        right -= lpRect->right;
        bottom -= lpRect->bottom;
    }

    void DeflateRect(int l, int t, int r, int b)
    {
        left += l;
        top += t;
        right -= r;
        bottom -= b;
    }

    void OffsetRect(int x, int y)
    {
        ::OffsetRect(this, x, y);
    }
    void OffsetRect(SIZE size)
    {
        ::OffsetRect(this, size.cx, size.cy);
    }

    void OffsetRect(POINT point)
    {
        ::OffsetRect(this, point.x, point.y);
    }

    void NormalizeRect()
    {
        int nTemp;
        if (left > right)
        {
            nTemp = left;
            left = right;
            right = nTemp;
        }
        if (top > bottom)
        {
            nTemp = top;
            top = bottom;
            bottom = nTemp;
        }
    }

    // absolute position of rectangle
    void MoveToY(int y)
    {
        bottom = Height() + y;
        top = y;
    }

    void MoveToX(int x)
    {
        right = Width() + x;
        left = x;
    }

    void MoveToXY(int x, int y)
    {
        MoveToX(x);
        MoveToY(y);
    }

    void MoveToXY(POINT pt)
    {
        MoveToX(pt.x);
        MoveToY(pt.y);
    }

    // operations that fill '*this' with result
    BOOL IntersectRect(LPCRECT lpRect1, LPCRECT lpRect2)
    {
        return ::IntersectRect(this, lpRect1, lpRect2);
    }

    BOOL UnionRect(LPCRECT lpRect1, LPCRECT lpRect2)
    {
        return ::UnionRect(this, lpRect1, lpRect2);
    }

    BOOL SubtractRect(LPCRECT lpRectSrc1, LPCRECT lpRectSrc2)
    {
        return ::SubtractRect(this, lpRectSrc1, lpRectSrc2);
    }

// Additional Operations
    void operator =(const RECT& srcRect)
    {
        ::CopyRect(this, &srcRect);
    }

    BOOL operator ==(const RECT& rect) const
    {
        return ::EqualRect(this, &rect);
    }

    BOOL operator !=(const RECT& rect) const
    {
        return !::EqualRect(this, &rect);
    }

    void operator +=(POINT point)
    {
        ::OffsetRect(this, point.x, point.y);
    }

    void operator +=(SIZE size)
    {
        ::OffsetRect(this, size.cx, size.cy);
    }

    void operator +=(LPCRECT lpRect)
    {
        InflateRect(lpRect);
    }

    void operator -=(POINT point)
    {
        ::OffsetRect(this, -point.x, -point.y);
    }

    void operator -=(SIZE size)
    {
        ::OffsetRect(this, -size.cx, -size.cy);
    }

    void operator -=(LPCRECT lpRect)
    {
        DeflateRect(lpRect);
    }

    void operator &=(const RECT& rect)
    {
        ::IntersectRect(this, this, &rect);
    }

    void operator |=(const RECT& rect)
    {
        ::UnionRect(this, this, &rect);
    }

// Operators returning BDRect values
    BDRect operator +(POINT pt) const
    {
        BDRect rect(*this);
        ::OffsetRect(&rect, pt.x, pt.y);
        return rect;
    }

    BDRect operator -(POINT pt) const
    {
        BDRect rect(*this);
        ::OffsetRect(&rect, -pt.x, -pt.y);
        return rect;
    }

    BDRect operator +(LPCRECT lpRect) const
    {
        BDRect rect(this);
        rect.InflateRect(lpRect);
        return rect;
    }

    BDRect operator +(SIZE size) const
    {
        BDRect rect(*this);
        ::OffsetRect(&rect, size.cx, size.cy);
        return rect;
    }

    BDRect operator -(SIZE size) const
    {
        BDRect rect(*this);
        ::OffsetRect(&rect, -size.cx, -size.cy);
        return rect;
    }

    BDRect operator -(LPCRECT lpRect) const
    {
        BDRect rect(this);
        rect.DeflateRect(lpRect);
        return rect;
    }

    BDRect operator &(const RECT& rect2) const
    {
        BDRect rect;
        ::IntersectRect(&rect, this, &rect2);
        return rect;
    }

    BDRect operator |(const RECT& rect2) const
    {
        BDRect rect;
        ::UnionRect(&rect, this, &rect2);
        return rect;
    }

    BDRect MulDiv(int nMultiplier, int nDivisor) const
    {
        return BDRect(
            ::MulDiv(left, nMultiplier, nDivisor),
            ::MulDiv(top, nMultiplier, nDivisor),
            ::MulDiv(right, nMultiplier, nDivisor),
            ::MulDiv(bottom, nMultiplier, nDivisor));
    }
};


// BDSize implementation

inline BDPoint BDSize::operator +(POINT point) const
{ return BDPoint(cx + point.x, cy + point.y); }

inline BDPoint BDSize::operator -(POINT point) const
{ return BDPoint(cx - point.x, cy - point.y); }

inline BDRect BDSize::operator +(const RECT* lpRect) const
{ return BDRect(lpRect) + *this; }

inline BDRect BDSize::operator -(const RECT* lpRect) const
{ return BDRect(lpRect) - *this; }


// BDPoint implementation

inline BDRect BDPoint::operator +(const RECT* lpRect) const
{ return BDRect(lpRect) + *this; }

inline BDRect BDPoint::operator -(const RECT* lpRect) const
{ return BDRect(lpRect) - *this; }


template <class Num>
inline BDSize operator *(SIZE s, Num n) 
{
    return BDSize((int)(s.cx * n), (int)(s.cy * n));
};

template <class Num>
inline void operator *=(SIZE & s, Num n)
{
    s = s * n;
};    

template <class Num>
inline BDSize operator /(SIZE s, Num n) 
{
    return BDSize((int)(s.cx / n), (int)(s.cy / n));
};

template <class Num>
inline void operator /=(SIZE & s, Num n)
{
    s = s / n;
};    


///////////////////////////////////////////////////////////////////////////////
// BDString - String class

struct BDStringData
{
    long nRefs;     // reference count
    int nDataLength;
    int nAllocLength;
    // TCHAR data[nAllocLength]

    TCHAR* data()
    { return (TCHAR*)(this + 1); }
};

// Globals

// For an empty string, m_pchData will point here
// (note: avoids special case of checking for NULL m_pchData)
// empty string data (and locked)
_declspec(selectany) int rgInitData[] = { -1, 0, 0, 0 };
_declspec(selectany) BDStringData* _atltmpDataNil = (BDStringData*)&rgInitData;
_declspec(selectany) LPCTSTR _atltmpPchNil = (LPCTSTR)(((BYTE*)&rgInitData) + sizeof(BDStringData));


class BDString
{
public:
// Constructors
    BDString()
    {
        Init();
    }

    BDString(const BDString& stringSrc)
    {
        assert(stringSrc.GetData()->nRefs != 0);
        if (stringSrc.GetData()->nRefs >= 0)
        {
            assert(stringSrc.GetData() != _atltmpDataNil);
            m_pchData = stringSrc.m_pchData;
            InterlockedIncrement(&GetData()->nRefs);
        }
        else
        {
            Init();
            *this = stringSrc.m_pchData;
        }
    }

    BDString(TCHAR ch, int nRepeat = 1)
    {
        assert(!_istlead(ch));   // can't create a lead byte string
        Init();
        if (nRepeat >= 1)
        {
            if(AllocBuffer(nRepeat))
            {
#ifdef _UNICODE
                for (int i = 0; i < nRepeat; i++)
                    m_pchData[i] = ch;
#else
                memset(m_pchData, ch, nRepeat);
#endif
            }
        }
    }

    BDString(LPCTSTR lpsz)
    {
        Init();
        if (lpsz != NULL && HIWORD(lpsz) == NULL)
        {
            UINT nID = LOWORD((DWORD_PTR)lpsz);

        }
        else
        {
            int nLen = SafeStrlen(lpsz);
            if (nLen != 0)
            {
                if(AllocBuffer(nLen))
                    memcpy_s(m_pchData, (nLen + 1) * sizeof(TCHAR), lpsz, nLen * sizeof(TCHAR));
            }
        }
    }

#ifdef _UNICODE
    BDString(LPCSTR lpsz)
    {
        Init();
#if defined(_WIN32_WCE) && (_ATL_VER >= 0x0800)
        int nSrcLen = (lpsz != NULL) ? ATL::lstrlenA(lpsz) : 0;
#else
        int nSrcLen = (lpsz != NULL) ? lstrlenA(lpsz) : 0;
#endif
        if (nSrcLen != 0)
        {
            if(AllocBuffer(nSrcLen))
            {
                _mbstowcsz(m_pchData, lpsz, nSrcLen + 1);
                ReleaseBuffer();
            }
        }
    }
#else // !_UNICODE
    BDString(LPCWSTR lpsz)
    {
        Init();
        int nSrcLen = (lpsz != NULL) ? (int)wcslen(lpsz) : 0;
        if (nSrcLen != 0)
        {
            if(AllocBuffer(nSrcLen * 2))
            {
                _wcstombsz(m_pchData, lpsz, (nSrcLen * 2) + 1);
                ReleaseBuffer();
            }
        }
    }
#endif // !_UNICODE

    BDString(LPCTSTR lpch, int nLength)
    {
        Init();
        if (nLength != 0)
        {
            if(AllocBuffer(nLength))
                memcpy_s(m_pchData, (nLength + 1) * sizeof(TCHAR), lpch, nLength * sizeof(TCHAR));
        }
    }

#ifdef _UNICODE
    BDString(LPCSTR lpsz, int nLength)
    {
        Init();
        if (nLength != 0)
        {
            if(AllocBuffer(nLength))
            {
                int n = ::MultiByteToWideChar(CP_ACP, 0, lpsz, nLength, m_pchData, nLength + 1);
                ReleaseBuffer((n >= 0) ? n : -1);
            }
        }
    }
#else // !_UNICODE
    BDString(LPCWSTR lpsz, int nLength)
    {
        Init();
        if (nLength != 0)
        {
            if(((nLength * 2) > nLength) && AllocBuffer(nLength * 2))
            {
                int n = ::WideCharToMultiByte(CP_ACP, 0, lpsz, nLength, m_pchData, (nLength * 2) + 1, NULL, NULL);
                ReleaseBuffer((n >= 0) ? n : -1);
            }
        }
    }
#endif // !_UNICODE

    BDString(const unsigned char* lpsz)
    {
        Init();
        *this = (LPCSTR)lpsz;
    }

// Attributes & Operations
    int GetLength() const   // as an array of characters
    {
        return GetData()->nDataLength;
    }

    BOOL IsEmpty() const
    {
        return GetData()->nDataLength == 0;
    }

    void Empty()   // free up the data
    {
        if (GetData()->nDataLength == 0)
            return;

        if (GetData()->nRefs >= 0)
            Release();
        else
            *this = _T("");

        assert(GetData()->nDataLength == 0);
        assert(GetData()->nRefs < 0 || GetData()->nAllocLength == 0);
    }

    TCHAR GetAt(int nIndex) const   // 0 based
    {
        assert(nIndex >= 0);
        assert(nIndex < GetData()->nDataLength);
        return m_pchData[nIndex];
    }

    TCHAR operator [](int nIndex) const   // same as GetAt
    {
        // same as GetAt
        assert(nIndex >= 0);
        assert(nIndex < GetData()->nDataLength);
        return m_pchData[nIndex];
    }

    void SetAt(int nIndex, TCHAR ch)
    {
        assert(nIndex >= 0);
        assert(nIndex < GetData()->nDataLength);

        CopyBeforeWrite();
        m_pchData[nIndex] = ch;
    }

    operator LPCTSTR() const   // as a C string
    {
        return m_pchData;
    }

    // overloaded assignment
    BDString& operator =(const BDString& stringSrc)
    {
        if (m_pchData != stringSrc.m_pchData)
        {
            if ((GetData()->nRefs < 0 && GetData() != _atltmpDataNil) || stringSrc.GetData()->nRefs < 0)
            {
                // actual copy necessary since one of the strings is locked
                AssignCopy(stringSrc.GetData()->nDataLength, stringSrc.m_pchData);
            }
            else
            {
                // can just copy references around
                Release();
                assert(stringSrc.GetData() != _atltmpDataNil);
                m_pchData = stringSrc.m_pchData;
                InterlockedIncrement(&GetData()->nRefs);
            }
        }
        return *this;
    }

    BDString& operator =(TCHAR ch)
    {
        assert(!_istlead(ch));   // can't set single lead byte
        AssignCopy(1, &ch);
        return *this;
    }

#ifdef _UNICODE
    BDString& operator =(char ch)
    {
        *this = (TCHAR)ch;
        return *this;
    }
#endif

    BDString& operator =(LPCTSTR lpsz)
    {
        assert(lpsz == NULL || _IsValidString(lpsz));
        AssignCopy(SafeStrlen(lpsz), lpsz);
        return *this;
    }

#ifdef _UNICODE
    BDString& operator =(LPCSTR lpsz)
    {
#if defined(_WIN32_WCE) && (_ATL_VER >= 0x0800)
        int nSrcLen = (lpsz != NULL) ? ATL::lstrlenA(lpsz) : 0;
#else
        int nSrcLen = (lpsz != NULL) ? lstrlenA(lpsz) : 0;
#endif
        if(AllocBeforeWrite(nSrcLen))
        {
            _mbstowcsz(m_pchData, lpsz, nSrcLen + 1);
            ReleaseBuffer();
        }
        return *this;
    }
#else // !_UNICODE
    BDString& operator =(LPCWSTR lpsz)
    {
        int nSrcLen = (lpsz != NULL) ? (int)wcslen(lpsz) : 0;
        if(AllocBeforeWrite(nSrcLen * 2))
        {
            _wcstombsz(m_pchData, lpsz, (nSrcLen * 2) + 1);
            ReleaseBuffer();
        }
        return *this;
    }
#endif  // !_UNICODE

    BDString& operator =(const unsigned char* lpsz)
    {
        *this = (LPCSTR)lpsz;
        return *this;
    }

    // string concatenation
    BDString& operator +=(const BDString& string)
    {
        ConcatInPlace(string.GetData()->nDataLength, string.m_pchData);
        return *this;
    }

    BDString& operator +=(TCHAR ch)
    {
        ConcatInPlace(1, &ch);
        return *this;
    }

#ifdef _UNICODE
    BDString& operator +=(char ch)
    {
        *this += (TCHAR)ch;
        return *this;
    }
#endif

    BDString& operator +=(LPCTSTR lpsz)
    {
        assert(lpsz == NULL || _IsValidString(lpsz));
        ConcatInPlace(SafeStrlen(lpsz), lpsz);
        return *this;
    }

    friend BDString __stdcall operator +(const BDString& string1, const BDString& string2);
    friend BDString __stdcall operator +(const BDString& string, TCHAR ch);
    friend BDString __stdcall operator +(TCHAR ch, const BDString& string);
#ifdef _UNICODE
    friend BDString __stdcall operator +(const BDString& string, char ch);
    friend BDString __stdcall operator +(char ch, const BDString& string);
#endif
    friend BDString __stdcall operator +(const BDString& string, LPCTSTR lpsz);
    friend BDString __stdcall operator +(LPCTSTR lpsz, const BDString& string);

    // string comparison
    int Compare(LPCTSTR lpsz) const   // straight character (MBCS/Unicode aware)
    {
        return _cstrcmp(m_pchData, lpsz);
    }

    int CompareNoCase(LPCTSTR lpsz) const   // ignore case (MBCS/Unicode aware)
    {
        return _cstrcmpi(m_pchData, lpsz);
    }

#ifndef _WIN32_WCE
    // BDString::Collate is often slower than Compare but is MBSC/Unicode
    //  aware as well as locale-sensitive with respect to sort order.
    int Collate(LPCTSTR lpsz) const   // NLS aware
    {
        return _cstrcoll(m_pchData, lpsz);
    }

    int CollateNoCase(LPCTSTR lpsz) const   // ignore case
    {
        return _cstrcolli(m_pchData, lpsz);
    }
#endif // !_WIN32_WCE

    // simple sub-string extraction
    BDString Mid(int nFirst, int nCount) const
    {
        // out-of-bounds requests return sensible things
        if (nFirst < 0)
            nFirst = 0;
        if (nCount < 0)
            nCount = 0;

        if (nFirst + nCount > GetData()->nDataLength)
            nCount = GetData()->nDataLength - nFirst;
        if (nFirst > GetData()->nDataLength)
            nCount = 0;

        BDString dest;
        AllocCopy(dest, nCount, nFirst, 0);
        return dest;
    }

    BDString Mid(int nFirst) const
    {
        return Mid(nFirst, GetData()->nDataLength - nFirst);
    }

    BDString Left(int nCount) const
    {
        if (nCount < 0)
            nCount = 0;
        else if (nCount > GetData()->nDataLength)
            nCount = GetData()->nDataLength;

        BDString dest;
        AllocCopy(dest, nCount, 0, 0);
        return dest;
    }

    BDString Right(int nCount) const
    {
        if (nCount < 0)
            nCount = 0;
        else if (nCount > GetData()->nDataLength)
            nCount = GetData()->nDataLength;

        BDString dest;
        AllocCopy(dest, nCount, GetData()->nDataLength-nCount, 0);
        return dest;
    }

    BDString SpanIncluding(LPCTSTR lpszCharSet) const   // strspn equivalent
    {
        assert(_IsValidString(lpszCharSet));
        return Left(_cstrspn(m_pchData, lpszCharSet));
    }

    BDString SpanExcluding(LPCTSTR lpszCharSet) const   // strcspn equivalent
    {
        assert(_IsValidString(lpszCharSet));
        return Left(_cstrcspn(m_pchData, lpszCharSet));
    }

    // upper/lower/reverse conversion
    void MakeUpper()
    {
        CopyBeforeWrite();
        CharUpper(m_pchData);
    }

    void MakeLower()
    {
        CopyBeforeWrite();
        CharLower(m_pchData);
    }

    void MakeReverse()
    {
        CopyBeforeWrite();
        _cstrrev(m_pchData);
    }

    // trimming whitespace (either side)
    void TrimRight()
    {
        CopyBeforeWrite();

        // find beginning of trailing spaces by starting at beginning (DBCS aware)
        LPTSTR lpsz = m_pchData;
        LPTSTR lpszLast = NULL;
        while (*lpsz != _T('\0'))
        {
            if (_cstrisspace(*lpsz))
            {
                if (lpszLast == NULL)
                    lpszLast = lpsz;
            }
            else
            {
                lpszLast = NULL;
            }
            lpsz = ::CharNext(lpsz);
        }

        if (lpszLast != NULL)
        {
            // truncate at trailing space start
            *lpszLast = _T('\0');
            GetData()->nDataLength = (int)(DWORD_PTR)(lpszLast - m_pchData);
        }
    }

    void TrimLeft()
    {
        CopyBeforeWrite();

        // find first non-space character
        LPCTSTR lpsz = m_pchData;
        while (_cstrisspace(*lpsz))
            lpsz = ::CharNext(lpsz);

        // fix up data and length
        int nDataLength = GetData()->nDataLength - (int)(DWORD_PTR)(lpsz - m_pchData);
        memmove_s(m_pchData, (GetData()->nAllocLength + 1) * sizeof(TCHAR), lpsz, (nDataLength + 1) * sizeof(TCHAR));
        GetData()->nDataLength = nDataLength;
    }

    // remove continuous occurrences of chTarget starting from right
    void TrimRight(TCHAR chTarget)
    {
        // find beginning of trailing matches
        // by starting at beginning (DBCS aware)

        CopyBeforeWrite();
        LPTSTR lpsz = m_pchData;
        LPTSTR lpszLast = NULL;

        while (*lpsz != _T('\0'))
        {
            if (*lpsz == chTarget)
            {
                if (lpszLast == NULL)
                    lpszLast = lpsz;
            }
            else
                lpszLast = NULL;
            lpsz = ::CharNext(lpsz);
        }

        if (lpszLast != NULL)
        {
            // truncate at left-most matching character
            *lpszLast = _T('\0');
            GetData()->nDataLength = (int)(DWORD_PTR)(lpszLast - m_pchData);
        }
    }

    // remove continuous occcurrences of characters in passed string, starting from right
    void TrimRight(LPCTSTR lpszTargetList)
    {
        // find beginning of trailing matches by starting at beginning (DBCS aware)

        CopyBeforeWrite();
        LPTSTR lpsz = m_pchData;
        LPTSTR lpszLast = NULL;

        while (*lpsz != _T('\0'))
        {
            TCHAR* pNext = ::CharNext(lpsz);
            if(pNext > lpsz + 1)
            {
                if (_cstrchr_db(lpszTargetList, *lpsz, *(lpsz + 1)) != NULL)
                {
                    if (lpszLast == NULL)
                        lpszLast = lpsz;
                }
                else
                {
                    lpszLast = NULL;
                }
            }
            else
            {
                if (_cstrchr(lpszTargetList, *lpsz) != NULL)
                {
                    if (lpszLast == NULL)
                        lpszLast = lpsz;
                }
                else
                {
                    lpszLast = NULL;
                }
            }

            lpsz = pNext;
        }

        if (lpszLast != NULL)
        {
            // truncate at left-most matching character
            *lpszLast = _T('\0');
            GetData()->nDataLength = (int)(DWORD_PTR)(lpszLast - m_pchData);
        }
    }

    // remove continuous occurrences of chTarget starting from left
    void TrimLeft(TCHAR chTarget)
    {
        // find first non-matching character

        CopyBeforeWrite();
        LPCTSTR lpsz = m_pchData;

        while (chTarget == *lpsz)
            lpsz = ::CharNext(lpsz);

        if (lpsz != m_pchData)
        {
            // fix up data and length
            int nDataLength = GetData()->nDataLength - (int)(DWORD_PTR)(lpsz - m_pchData);
            memmove_s(m_pchData, (GetData()->nAllocLength + 1) * sizeof(TCHAR), lpsz, (nDataLength + 1) * sizeof(TCHAR));
            GetData()->nDataLength = nDataLength;
        }
    }

    // remove continuous occcurrences of characters in passed string, starting from left
    void TrimLeft(LPCTSTR lpszTargets)
    {
        // if we're not trimming anything, we're not doing any work
        if (SafeStrlen(lpszTargets) == 0)
            return;

        CopyBeforeWrite();
        LPCTSTR lpsz = m_pchData;

        while (*lpsz != _T('\0'))
        {
            TCHAR* pNext = ::CharNext(lpsz);
            if(pNext > lpsz + 1)
            {
                if (_cstrchr_db(lpszTargets, *lpsz, *(lpsz + 1)) == NULL)
                    break;
            }
            else
            {
                if (_cstrchr(lpszTargets, *lpsz) == NULL)
                    break;
            }
            lpsz = pNext;
        }

        if (lpsz != m_pchData)
        {
            // fix up data and length
            int nDataLength = GetData()->nDataLength - (int)(DWORD_PTR)(lpsz - m_pchData);
            memmove_s(m_pchData, (GetData()->nAllocLength + 1) * sizeof(TCHAR), lpsz, (nDataLength + 1) * sizeof(TCHAR));
            GetData()->nDataLength = nDataLength;
        }
    }

    // advanced manipulation
    // replace occurrences of chOld with chNew
    int Replace(TCHAR chOld, TCHAR chNew)
    {
        int nCount = 0;

        // short-circuit the nop case
        if (chOld != chNew)
        {
            // otherwise modify each character that matches in the string
            CopyBeforeWrite();
            LPTSTR psz = m_pchData;
            LPTSTR pszEnd = psz + GetData()->nDataLength;
            while (psz < pszEnd)
            {
                // replace instances of the specified character only
                if (*psz == chOld)
                {
                    *psz = chNew;
                    nCount++;
                }
                psz = ::CharNext(psz);
            }
        }
        return nCount;
    }

    // replace occurrences of substring lpszOld with lpszNew;
    // empty lpszNew removes instances of lpszOld
    int Replace(LPCTSTR lpszOld, LPCTSTR lpszNew)
    {
        // can't have empty or NULL lpszOld

        int nSourceLen = SafeStrlen(lpszOld);
        if (nSourceLen == 0)
            return 0;
        int nReplacementLen = SafeStrlen(lpszNew);

        // loop once to figure out the size of the result string
        int nCount = 0;
        LPTSTR lpszStart = m_pchData;
        LPTSTR lpszEnd = m_pchData + GetData()->nDataLength;
        LPTSTR lpszTarget = NULL;
        while (lpszStart < lpszEnd)
        {
            while ((lpszTarget = (TCHAR*)_cstrstr(lpszStart, lpszOld)) != NULL)
            {
                nCount++;
                lpszStart = lpszTarget + nSourceLen;
            }
            lpszStart += lstrlen(lpszStart) + 1;
        }

        // if any changes were made, make them
        if (nCount > 0)
        {
            CopyBeforeWrite();

            // if the buffer is too small, just allocate a new buffer (slow but sure)
            int nOldLength = GetData()->nDataLength;
            int nNewLength =  nOldLength + (nReplacementLen - nSourceLen) * nCount;
            if (GetData()->nAllocLength < nNewLength || GetData()->nRefs > 1)
            {
                BDStringData* pOldData = GetData();
                LPTSTR pstr = m_pchData;
                if(!AllocBuffer(nNewLength))
                    return -1;
                memcpy_s(m_pchData, (nNewLength + 1) * sizeof(TCHAR), pstr, pOldData->nDataLength * sizeof(TCHAR));
                BDString::Release(pOldData);
            }
            // else, we just do it in-place
            lpszStart = m_pchData;
            lpszEnd = m_pchData + GetData()->nDataLength;

            // loop again to actually do the work
            while (lpszStart < lpszEnd)
            {
                while ((lpszTarget = (TCHAR*)_cstrstr(lpszStart, lpszOld)) != NULL)
                {
                    int nBalance = nOldLength - ((int)(DWORD_PTR)(lpszTarget - m_pchData) + nSourceLen);
                    int cchBuffLen = GetData()->nAllocLength - (int)(DWORD_PTR)(lpszTarget - m_pchData);
                    memmove_s(lpszTarget + nReplacementLen, (cchBuffLen - nReplacementLen + 1) * sizeof(TCHAR), lpszTarget + nSourceLen, nBalance * sizeof(TCHAR));
                    memcpy_s(lpszTarget, (cchBuffLen + 1) * sizeof(TCHAR), lpszNew, nReplacementLen * sizeof(TCHAR));
                    lpszStart = lpszTarget + nReplacementLen;
                    lpszStart[nBalance] = _T('\0');
                    nOldLength += (nReplacementLen - nSourceLen);
                }
                lpszStart += lstrlen(lpszStart) + 1;
            }
            assert(m_pchData[nNewLength] == _T('\0'));
            GetData()->nDataLength = nNewLength;
        }

        return nCount;
    }

    // remove occurrences of chRemove
    int Remove(TCHAR chRemove)
    {
        CopyBeforeWrite();

        LPTSTR pstrSource = m_pchData;
        LPTSTR pstrDest = m_pchData;
        LPTSTR pstrEnd = m_pchData + GetData()->nDataLength;

        while (pstrSource < pstrEnd)
        {
            if (*pstrSource != chRemove)
            {
                *pstrDest = *pstrSource;
                pstrDest = ::CharNext(pstrDest);
            }
            pstrSource = ::CharNext(pstrSource);
        }
        *pstrDest = _T('\0');
        int nCount = (int)(DWORD_PTR)(pstrSource - pstrDest);
        GetData()->nDataLength -= nCount;

        return nCount;
    }

    // insert character at zero-based index; concatenates if index is past end of string
    int Insert(int nIndex, TCHAR ch)
    {
        CopyBeforeWrite();

        if (nIndex < 0)
            nIndex = 0;

        int nNewLength = GetData()->nDataLength;
        if (nIndex > nNewLength)
            nIndex = nNewLength;
        nNewLength++;

        if (GetData()->nAllocLength < nNewLength)
        {
            BDStringData* pOldData = GetData();
            LPTSTR pstr = m_pchData;
            if(!AllocBuffer(nNewLength))
                return -1;
            memcpy_s(m_pchData, (nNewLength + 1) * sizeof(TCHAR), pstr, (pOldData->nDataLength + 1) * sizeof(TCHAR));
            BDString::Release(pOldData);
        }

        // move existing bytes down
        memmove_s(m_pchData + nIndex + 1, (GetData()->nAllocLength - nIndex) * sizeof(TCHAR), m_pchData + nIndex, (nNewLength - nIndex) * sizeof(TCHAR));
        m_pchData[nIndex] = ch;
        GetData()->nDataLength = nNewLength;

        return nNewLength;
    }

    // insert substring at zero-based index; concatenates if index is past end of string
    int Insert(int nIndex, LPCTSTR pstr)
    {
        if (nIndex < 0)
            nIndex = 0;

        int nInsertLength = SafeStrlen(pstr);
        int nNewLength = GetData()->nDataLength;
        if (nInsertLength > 0)
        {
            CopyBeforeWrite();
            if (nIndex > nNewLength)
                nIndex = nNewLength;
            nNewLength += nInsertLength;

            if (GetData()->nAllocLength < nNewLength)
            {
                BDStringData* pOldData = GetData();
                LPTSTR pstrTmp = m_pchData;
                if(!AllocBuffer(nNewLength))
                    return -1;
                memcpy_s(m_pchData, (nNewLength + 1) * sizeof(TCHAR), pstrTmp, (pOldData->nDataLength + 1) * sizeof(TCHAR));
                BDString::Release(pOldData);
            }

            // move existing bytes down
            memmove_s(m_pchData + nIndex + nInsertLength, (GetData()->nAllocLength + 1 - nIndex - nInsertLength) * sizeof(TCHAR), m_pchData + nIndex, (nNewLength - nIndex - nInsertLength + 1) * sizeof(TCHAR));
            memcpy_s(m_pchData + nIndex, (GetData()->nAllocLength + 1 - nIndex) * sizeof(TCHAR), pstr, nInsertLength * sizeof(TCHAR));
            GetData()->nDataLength = nNewLength;
        }

        return nNewLength;
    }

    // delete nCount characters starting at zero-based index
    int Delete(int nIndex, int nCount = 1)
    {
        if (nIndex < 0)
            nIndex = 0;
        int nLength = GetData()->nDataLength;
        if (nCount > 0 && nIndex < nLength)
        {
            if((nIndex + nCount) > nLength)
                nCount = nLength - nIndex;
            CopyBeforeWrite();
            int nBytesToCopy = nLength - (nIndex + nCount) + 1;

            memmove_s(m_pchData + nIndex, (GetData()->nAllocLength + 1 - nIndex) * sizeof(TCHAR), m_pchData + nIndex + nCount, nBytesToCopy * sizeof(TCHAR));
            nLength -= nCount;
            GetData()->nDataLength = nLength;
        }

        return nLength;
    }

    // searching (return starting index, or -1 if not found)
    // look for a single character match
    int Find(TCHAR ch) const   // like "C" strchr
    {
        return Find(ch, 0);
    }

    int ReverseFind(TCHAR ch) const
    {
        // find last single character
        LPCTSTR lpsz = _cstrrchr(m_pchData, (_TUCHAR)ch);

        // return -1 if not found, distance from beginning otherwise
        return (lpsz == NULL) ? -1 : (int)(lpsz - m_pchData);
    }

    int Find(TCHAR ch, int nStart) const   // starting at index
    {
        int nLength = GetData()->nDataLength;
        if (nStart < 0 || nStart >= nLength)
            return -1;

        // find first single character
        LPCTSTR lpsz = _cstrchr(m_pchData + nStart, (_TUCHAR)ch);

        // return -1 if not found and index otherwise
        return (lpsz == NULL) ? -1 : (int)(lpsz - m_pchData);
    }

    int FindOneOf(LPCTSTR lpszCharSet) const
    {
        assert(_IsValidString(lpszCharSet));
        LPCTSTR lpsz = _cstrpbrk(m_pchData, lpszCharSet);
        return (lpsz == NULL) ? -1 : (int)(lpsz - m_pchData);
    }

    // look for a specific sub-string
    // find a sub-string (like strstr)
    int Find(LPCTSTR lpszSub) const   // like "C" strstr
    {
        return Find(lpszSub, 0);
    }

    int Find(LPCTSTR lpszSub, int nStart) const   // starting at index
    {
        assert(_IsValidString(lpszSub));

        int nLength = GetData()->nDataLength;
        if (nStart < 0 || nStart > nLength)
            return -1;

        // find first matching substring
        LPCTSTR lpsz = _cstrstr(m_pchData + nStart, lpszSub);

        // return -1 for not found, distance from beginning otherwise
        return (lpsz == NULL) ? -1 : (int)(lpsz - m_pchData);
    }

    // Concatentation for non strings
    BDString& Append(int n)
    {
        const int cchBuff = 12;
        TCHAR szBuffer[cchBuff] = { 0 };
        swprintf_s(szBuffer, cchBuff, _T("%d"), n);
        ConcatInPlace(SafeStrlen(szBuffer), szBuffer);
        return *this;
    }

    // simple formatting
    // formatting (using wsprintf style formatting)
    BOOL __cdecl Format(LPCTSTR lpszFormat, ...)
    {
        assert(_IsValidString(lpszFormat));

        va_list argList;
        va_start(argList, lpszFormat);
        BOOL bRet = FormatV(lpszFormat, argList);
        va_end(argList);
        return bRet;
    }

    BOOL __cdecl Format(UINT nFormatID, ...)
    {
        BDString strFormat;
        BOOL bRet = strFormat.LoadString(nFormatID);
        assert(bRet != 0);

        va_list argList;
        va_start(argList, nFormatID);
        bRet = FormatV(strFormat, argList);
        va_end(argList);
        return bRet;
    }

    BOOL FormatV(LPCTSTR lpszFormat, va_list argList)
    {
        assert(_IsValidString(lpszFormat));

        enum _FormatModifiers
        {
            FORCE_ANSI =    0x10000,
            FORCE_UNICODE =    0x20000,
            FORCE_INT64 =    0x40000
        };

        va_list argListSave = argList;

        // make a guess at the maximum length of the resulting string
        int nMaxLen = 0;
        for (LPCTSTR lpsz = lpszFormat; *lpsz != _T('\0'); lpsz = ::CharNext(lpsz))
        {
            // handle '%' character, but watch out for '%%'
            if (*lpsz != _T('%') || *(lpsz = ::CharNext(lpsz)) == _T('%'))
            {
                nMaxLen += (int)(::CharNext(lpsz) - lpsz);
                continue;
            }

            int nItemLen = 0;

            // handle '%' character with format
            int nWidth = 0;
            for (; *lpsz != _T('\0'); lpsz = ::CharNext(lpsz))
            {
                // check for valid flags
                if (*lpsz == _T('#'))
                    nMaxLen += 2;   // for '0x'
                else if (*lpsz == _T('*'))
                    nWidth = va_arg(argList, int);
                else if (*lpsz == _T('-') || *lpsz == _T('+') || *lpsz == _T('0') || *lpsz == _T(' '))
                    ;
                else // hit non-flag character
                    break;
            }
            // get width and skip it
            if (nWidth == 0)
            {
                // width indicated by
                nWidth = _cstrtoi(lpsz);
                for (; *lpsz != _T('\0') && _cstrisdigit(*lpsz); lpsz = ::CharNext(lpsz))
                    ;
            }
            assert(nWidth >= 0);

            int nPrecision = 0;
            if (*lpsz == _T('.'))
            {
                // skip past '.' separator (width.precision)
                lpsz = ::CharNext(lpsz);

                // get precision and skip it
                if (*lpsz == _T('*'))
                {
                    nPrecision = va_arg(argList, int);
                    lpsz = ::CharNext(lpsz);
                }
                else
                {
                    nPrecision = _cstrtoi(lpsz);
                    for (; *lpsz != _T('\0') && _cstrisdigit(*lpsz); lpsz = ::CharNext(lpsz))
                        ;
                }
                assert(nPrecision >= 0);
            }

            // should be on type modifier or specifier
            int nModifier = 0;
            if(lpsz[0] == _T('I'))
            {
                if((lpsz[1] == _T('6')) && (lpsz[2] == _T('4')))
                {
                    lpsz += 3;
                    nModifier = FORCE_INT64;
                }
                else if((lpsz[1] == _T('3')) && (lpsz[2] == _T('2')))
                {
                    lpsz += 3;
                }
                else
                {
                    lpsz++;
                    if(sizeof(size_t) == 8)
                        nModifier = FORCE_INT64;
                }
            }
            else
            {
                switch (*lpsz)
                {
                // modifiers that affect size
                case _T('h'):
                    nModifier = FORCE_ANSI;
                    lpsz = ::CharNext(lpsz);
                    break;
                case _T('l'):
                    nModifier = FORCE_UNICODE;
                    lpsz = ::CharNext(lpsz);
                    break;

                // modifiers that do not affect size
                case _T('F'):
                case _T('N'):
                case _T('L'):
                    lpsz = ::CharNext(lpsz);
                    break;
                }
            }

            // now should be on specifier
            switch (*lpsz | nModifier)
            {
            // single characters
            case _T('c'):
            case _T('C'):
                nItemLen = 2;
                va_arg(argList, TCHAR);
                break;
            case _T('c') | FORCE_ANSI:
            case _T('C') | FORCE_ANSI:
                nItemLen = 2;
                va_arg(argList, char);
                break;
            case _T('c') | FORCE_UNICODE:
            case _T('C') | FORCE_UNICODE:
                nItemLen = 2;
                va_arg(argList, WCHAR);
                break;

            // strings
            case _T('s'):
            {
                LPCTSTR pstrNextArg = va_arg(argList, LPCTSTR);
                if (pstrNextArg == NULL)
                {
                    nItemLen = 6;  // "(null)"
                }
                else
                {
                    nItemLen = lstrlen(pstrNextArg);
                    nItemLen = __max(1, nItemLen);
                }
                break;
            }

            case _T('S'):
            {
#ifndef _UNICODE
                LPWSTR pstrNextArg = va_arg(argList, LPWSTR);
                if (pstrNextArg == NULL)
                {
                    nItemLen = 6;  // "(null)"
                }
                else
                {
                    nItemLen = (int)wcslen(pstrNextArg);
                    nItemLen = __max(1, nItemLen);
                }
#else // _UNICODE
                LPCSTR pstrNextArg = va_arg(argList, LPCSTR);
                if (pstrNextArg == NULL)
                {
                    nItemLen = 6; // "(null)"
                }
                else
                {
#if defined(_WIN32_WCE) && (_ATL_VER >= 0x0800)
                    nItemLen = ATL::lstrlenA(pstrNextArg);
#else
                    nItemLen = lstrlenA(pstrNextArg);
#endif
                    nItemLen = __max(1, nItemLen);
                }
#endif // _UNICODE
                break;
            }

            case _T('s') | FORCE_ANSI:
            case _T('S') | FORCE_ANSI:
            {
                LPCSTR pstrNextArg = va_arg(argList, LPCSTR);
                if (pstrNextArg == NULL)
                {
                    nItemLen = 6; // "(null)"
                }
                else
                {
#if defined(_WIN32_WCE) && (_ATL_VER >= 0x0800)
                    nItemLen = ATL::lstrlenA(pstrNextArg);
#else
                    nItemLen = lstrlenA(pstrNextArg);
#endif
                    nItemLen = __max(1, nItemLen);
                }
                break;
            }

            case _T('s') | FORCE_UNICODE:
            case _T('S') | FORCE_UNICODE:
            {
                LPWSTR pstrNextArg = va_arg(argList, LPWSTR);
                if (pstrNextArg == NULL)
                {
                    nItemLen = 6; // "(null)"
                }
                else
                {
                    nItemLen = (int)wcslen(pstrNextArg);
                    nItemLen = __max(1, nItemLen);
                }
                break;
            }
            }

            // adjust nItemLen for strings
            if (nItemLen != 0)
            {
                nItemLen = __max(nItemLen, nWidth);
                if (nPrecision != 0)
                    nItemLen = __min(nItemLen, nPrecision);
            }
            else
            {
                switch (*lpsz)
                {
                // integers
                case _T('d'):
                case _T('i'):
                case _T('u'):
                case _T('x'):
                case _T('X'):
                case _T('o'):
                    if (nModifier & FORCE_INT64)
                        va_arg(argList, __int64);
                    else
                        va_arg(argList, int);
                    nItemLen = 32;
                    nItemLen = __max(nItemLen, nWidth + nPrecision);
                    break;

#ifndef _ATL_USE_CSTRING_FLOAT
                case _T('e'):
                case _T('E'):
                case _T('f'):
                case _T('g'):
                case _T('G'):
                    assert(!"Floating point (%%e, %%E, %%f, %%g, and %%G) is not supported by the WTL::BDString class.");
#ifndef _DEBUG
                    ::OutputDebugString(_T("Floating point (%%e, %%f, %%g, and %%G) is not supported by the WTL::BDString class."));
#ifndef _WIN32_WCE
                    ::DebugBreak();
#else // CE specific
                    DebugBreak();
#endif // _WIN32_WCE
#endif // !_DEBUG
                    break;
#else // _ATL_USE_CSTRING_FLOAT
                case _T('e'):
                case _T('E'):
                case _T('g'):
                case _T('G'):
                    va_arg(argList, double);
                    nItemLen = 128;
                    nItemLen = __max(nItemLen, nWidth + nPrecision);
                    break;
                case _T('f'):
                    {
                        double f = va_arg(argList, double);
                        // 312 == strlen("-1+(309 zeroes).")
                        // 309 zeroes == max precision of a double
                        // 6 == adjustment in case precision is not specified,
                        //   which means that the precision defaults to 6
                        int cchLen = __max(nWidth, 312 + nPrecision + 6);
                        CTempBuffer<TCHAR, _WTL_STACK_ALLOC_THRESHOLD> buff;
                        LPTSTR pszTemp = buff.Allocate(cchLen);
                        if(pszTemp != NULL)
                        {
                            SecureHelper::sprintf_x(pszTemp, cchLen, _T("%*.*f"), nWidth, nPrecision + 6, f);
                            nItemLen = (int)_tcslen(pszTemp);
                        }
                        else
                        {
                            nItemLen = cchLen;
                        }
                    }
                    break;
#endif // _ATL_USE_CSTRING_FLOAT

                case _T('p'):
                    va_arg(argList, void*);
                    nItemLen = 32;
                    nItemLen = __max(nItemLen, nWidth + nPrecision);
                    break;

                // no output
                case _T('n'):
                    va_arg(argList, int*);
                    break;

                default:
                    assert(FALSE);  // unknown formatting option
                }
            }

            // adjust nMaxLen for output nItemLen
            nMaxLen += nItemLen;
        }

        if(GetBuffer(nMaxLen) == NULL)
            return FALSE;
#ifndef _ATL_USE_CSTRING_FLOAT
        int nRet = vswprintf_s(m_pchData, GetAllocLength() + 1, lpszFormat, argListSave);
#else // _ATL_USE_CSTRING_FLOAT
        int nRet = vsprintf_s(m_pchData, GetAllocLength() + 1, lpszFormat, argListSave);
#endif // _ATL_USE_CSTRING_FLOAT
        nRet;   // ref
        assert(nRet <= GetAllocLength());
        ReleaseBuffer();

        va_end(argListSave);
        return TRUE;
    }

    // formatting for localization (uses FormatMessage API)
    // formatting (using FormatMessage style formatting)
    BOOL __cdecl FormatMessage(LPCTSTR lpszFormat, ...)
    {
        // format message into temporary buffer lpszTemp
        va_list argList;
        va_start(argList, lpszFormat);
        LPTSTR lpszTemp = NULL;
        BOOL bRet = TRUE;

        if ((::FormatMessage(FORMAT_MESSAGE_FROM_STRING | FORMAT_MESSAGE_ALLOCATE_BUFFER,
                lpszFormat, 0, 0, (LPTSTR)&lpszTemp, 0, &argList) == 0) || (lpszTemp == NULL))
            bRet = FALSE;

        // assign lpszTemp into the resulting string and free the temporary
        *this = lpszTemp;
        LocalFree(lpszTemp);
        va_end(argList);
        return bRet;
    }

    BOOL __cdecl FormatMessage(UINT nFormatID, ...)
    {
        // get format string from string table
        BDString strFormat;
        BOOL bRetTmp = strFormat.LoadString(nFormatID);
        bRetTmp;   // ref
        assert(bRetTmp != 0);

        // format message into temporary buffer lpszTemp
        va_list argList;
        va_start(argList, nFormatID);
        LPTSTR lpszTemp = NULL;
        BOOL bRet = TRUE;

        if ((::FormatMessage(FORMAT_MESSAGE_FROM_STRING | FORMAT_MESSAGE_ALLOCATE_BUFFER,
                strFormat, 0, 0, (LPTSTR)&lpszTemp, 0, &argList) == 0) || (lpszTemp == NULL))
            bRet = FALSE;

        // assign lpszTemp into the resulting string and free lpszTemp
        *this = lpszTemp;
        LocalFree(lpszTemp);
        va_end(argList);
        return bRet;
    }

    // Windows support
    BOOL LoadString(UINT nID)   // load from string resource (255 chars max.)
    {
#ifdef _UNICODE
        const int CHAR_FUDGE = 1;   // one TCHAR unused is good enough
#else
        const int CHAR_FUDGE = 2;   // two BYTES unused for case of DBC last char
#endif

        // try fixed buffer first (to avoid wasting space in the heap)
        TCHAR szTemp[256] = { 0 };
        int nCount =  sizeof(szTemp) / sizeof(szTemp[0]);
        int nLen = _LoadString(nID, szTemp, nCount);
        if (nCount - nLen > CHAR_FUDGE)
        {
            *this = szTemp;
            return (nLen > 0);
        }

        // try buffer size of 512, then larger size until entire string is retrieved
        int nSize = 256;
        do
        {
            nSize += 256;
            LPTSTR lpstr = GetBuffer(nSize - 1);
            if(lpstr == NULL)
            {
                nLen = 0;
                break;
            }
            nLen = _LoadString(nID, lpstr, nSize);
        } while (nSize - nLen <= CHAR_FUDGE);
        ReleaseBuffer();

        return (nLen > 0);
    }

#ifndef _UNICODE
    // ANSI <-> OEM support (convert string in place)
    void AnsiToOem()
    {
        CopyBeforeWrite();
        ::AnsiToOem(m_pchData, m_pchData);
    }

    void OemToAnsi()
    {
        CopyBeforeWrite();
        ::OemToAnsi(m_pchData, m_pchData);
    }
#endif

    // Access to string implementation buffer as "C" character array
    LPTSTR GetBuffer(int nMinBufLength)
    {
        assert(nMinBufLength >= 0);

        if (GetData()->nRefs > 1 || nMinBufLength > GetData()->nAllocLength)
        {
            // we have to grow the buffer
            BDStringData* pOldData = GetData();
            int nOldLen = GetData()->nDataLength;   // AllocBuffer will tromp it
            if (nMinBufLength < nOldLen)
                nMinBufLength = nOldLen;

            if(!AllocBuffer(nMinBufLength))
                return NULL;

            memcpy_s(m_pchData, (nMinBufLength + 1) * sizeof(TCHAR), pOldData->data(), (nOldLen + 1) * sizeof(TCHAR));
            GetData()->nDataLength = nOldLen;
            BDString::Release(pOldData);
        }
        assert(GetData()->nRefs <= 1);

        // return a pointer to the character storage for this string
        assert(m_pchData != NULL);
        return m_pchData;
    }

    void ReleaseBuffer(int nNewLength = -1)
    {
        CopyBeforeWrite();   // just in case GetBuffer was not called

        if (nNewLength == -1)
            nNewLength = lstrlen(m_pchData);   // zero terminated

        assert(nNewLength <= GetData()->nAllocLength);
        GetData()->nDataLength = nNewLength;
        m_pchData[nNewLength] = _T('\0');
    }

    LPTSTR GetBufferSetLength(int nNewLength)
    {
        assert(nNewLength >= 0);

        if(GetBuffer(nNewLength) == NULL)
            return NULL;

        GetData()->nDataLength = nNewLength;
        m_pchData[nNewLength] = _T('\0');
        return m_pchData;
    }

    void FreeExtra()
    {
        assert(GetData()->nDataLength <= GetData()->nAllocLength);
        if (GetData()->nDataLength != GetData()->nAllocLength)
        {
            BDStringData* pOldData = GetData();
            if(AllocBuffer(GetData()->nDataLength))
            {
                memcpy_s(m_pchData, (GetData()->nAllocLength + 1) * sizeof(TCHAR), pOldData->data(), pOldData->nDataLength * sizeof(TCHAR));
                assert(m_pchData[GetData()->nDataLength] == _T('\0'));
                BDString::Release(pOldData);
            }
        }
        assert(GetData() != NULL);
    }

    // Use LockBuffer/UnlockBuffer to turn refcounting off
    LPTSTR LockBuffer()
    {
        LPTSTR lpsz = GetBuffer(0);
        if(lpsz != NULL)
            GetData()->nRefs = -1;
        return lpsz;
    }

    void UnlockBuffer()
    {
        assert(GetData()->nRefs == -1);
        if (GetData() != _atltmpDataNil)
            GetData()->nRefs = 1;
    }

// Implementation
public:
    ~BDString()   //  free any attached data
    {
        if (GetData() != _atltmpDataNil)
        {
            if (InterlockedDecrement(&GetData()->nRefs) <= 0)
                delete[] (BYTE*)GetData();
        }
    }

    int GetAllocLength() const
    {
        return GetData()->nAllocLength;
    }

    static BOOL __stdcall _IsValidString(LPCTSTR lpsz, int /*nLength*/ = -1)
    {
        return (lpsz != NULL) ? TRUE : FALSE;
    }

protected:
    LPTSTR m_pchData;   // pointer to ref counted string data

    // implementation helpers
    BDStringData* GetData() const
    {
        assert(m_pchData != NULL);
        return ((BDStringData*)m_pchData) - 1;
    }

    void Init()
    {
        m_pchData = _GetEmptyString().m_pchData;
    }

    BOOL AllocCopy(BDString& dest, int nCopyLen, int nCopyIndex, int nExtraLen) const
    {
        // will clone the data attached to this string
        // allocating 'nExtraLen' characters
        // Places results in uninitialized string 'dest'
        // Will copy the part or all of original data to start of new string

        BOOL bRet = FALSE;
        int nNewLen = nCopyLen + nExtraLen;
        if (nNewLen == 0)
        {
            dest.Init();
            bRet = TRUE;
        }
        else if(nNewLen >= nCopyLen)
        {
            if(dest.AllocBuffer(nNewLen))
            {
                memcpy_s(dest.m_pchData, (nNewLen + 1) * sizeof(TCHAR), m_pchData + nCopyIndex, nCopyLen * sizeof(TCHAR));
                bRet = TRUE;
            }
        }

        return bRet;
    }

    // always allocate one extra character for '\0' termination
    // assumes [optimistically] that data length will equal allocation length
    BOOL AllocBuffer(int nLen)
    {
        assert(nLen >= 0);
        assert(nLen <= INT_MAX - 1);   // max size (enough room for 1 extra)

        if (nLen == 0)
        {
            Init();
        }
        else
        {
            BDStringData* pData = NULL;
            pData = (BDStringData*)new BYTE[sizeof(BDStringData) + (nLen + 1) * sizeof(TCHAR)];
            if(pData == NULL)
                return FALSE;

            pData->nRefs = 1;
            pData->data()[nLen] = _T('\0');
            pData->nDataLength = nLen;
            pData->nAllocLength = nLen;
            m_pchData = pData->data();
        }

        return TRUE;
    }

    // Assignment operators
    //  All assign a new value to the string
    //      (a) first see if the buffer is big enough
    //      (b) if enough room, copy on top of old buffer, set size and type
    //      (c) otherwise free old string data, and create a new one
    //
    //  All routines return the new string (but as a 'const BDString&' so that
    //      assigning it again will cause a copy, eg: s1 = s2 = "hi there".
    //
    void AssignCopy(int nSrcLen, LPCTSTR lpszSrcData)
    {
        if(AllocBeforeWrite(nSrcLen))
        {
            memcpy_s(m_pchData, (nSrcLen + 1) * sizeof(TCHAR), lpszSrcData, nSrcLen * sizeof(TCHAR));
            GetData()->nDataLength = nSrcLen;
            m_pchData[nSrcLen] = _T('\0');
        }
    }

    // Concatenation
    // NOTE: "operator +" is done as friend functions for simplicity
    //      There are three variants:
    //          BDString + BDString
    // and for ? = TCHAR, LPCTSTR
    //          BDString + ?
    //          ? + BDString
    BOOL ConcatCopy(int nSrc1Len, LPCTSTR lpszSrc1Data, int nSrc2Len, LPCTSTR lpszSrc2Data)
    {
        // -- master concatenation routine
        // Concatenate two sources
        // -- assume that 'this' is a new BDString object

        BOOL bRet = TRUE;
        int nNewLen = nSrc1Len + nSrc2Len;
        if(nNewLen < nSrc1Len || nNewLen < nSrc2Len)
        {
            bRet = FALSE;
        }
        else if(nNewLen != 0)
        {
            bRet = AllocBuffer(nNewLen);
            if (bRet)
            {
                memcpy_s(m_pchData, (nNewLen + 1) * sizeof(TCHAR), lpszSrc1Data, nSrc1Len * sizeof(TCHAR));
                memcpy_s(m_pchData + nSrc1Len, (nNewLen + 1 - nSrc1Len) * sizeof(TCHAR), lpszSrc2Data, nSrc2Len * sizeof(TCHAR));
            }
        }
        return bRet;
    }

    void ConcatInPlace(int nSrcLen, LPCTSTR lpszSrcData)
    {
        //  -- the main routine for += operators

        // concatenating an empty string is a no-op!
        if (nSrcLen == 0)
            return;

        // if the buffer is too small, or we have a width mis-match, just
        //   allocate a new buffer (slow but sure)
        if (GetData()->nRefs > 1 || GetData()->nDataLength + nSrcLen > GetData()->nAllocLength)
        {
            // we have to grow the buffer, use the ConcatCopy routine
            BDStringData* pOldData = GetData();
            if (ConcatCopy(GetData()->nDataLength, m_pchData, nSrcLen, lpszSrcData))
            {
                assert(pOldData != NULL);
                BDString::Release(pOldData);
            }
        }
        else
        {
            // fast concatenation when buffer big enough
            memcpy_s(m_pchData + GetData()->nDataLength, (GetData()->nAllocLength + 1) * sizeof(TCHAR), lpszSrcData, nSrcLen * sizeof(TCHAR));
            GetData()->nDataLength += nSrcLen;
            assert(GetData()->nDataLength <= GetData()->nAllocLength);
            m_pchData[GetData()->nDataLength] = _T('\0');
        }
    }

    void CopyBeforeWrite()
    {
        if (GetData()->nRefs > 1)
        {
            BDStringData* pData = GetData();
            Release();
            if(AllocBuffer(pData->nDataLength))
                memcpy_s(m_pchData, (GetData()->nAllocLength + 1) * sizeof(TCHAR), pData->data(), (pData->nDataLength + 1) * sizeof(TCHAR));
        }
        assert(GetData()->nRefs <= 1);
    }

    BOOL AllocBeforeWrite(int nLen)
    {
        BOOL bRet = TRUE;
        if (GetData()->nRefs > 1 || nLen > GetData()->nAllocLength)
        {
            Release();
            bRet = AllocBuffer(nLen);
        }
        assert(GetData()->nRefs <= 1);
        return bRet;
    }

    void Release()
    {
        if (GetData() != _atltmpDataNil)
        {
            assert(GetData()->nRefs != 0);
            if (InterlockedDecrement(&GetData()->nRefs) <= 0)
                delete[] (BYTE*)GetData();
            Init();
        }
    }

    static void PASCAL Release(BDStringData* pData)
    {
        if (pData != _atltmpDataNil)
        {
            assert(pData->nRefs != 0);
            if (InterlockedDecrement(&pData->nRefs) <= 0)
                delete[] (BYTE*)pData;
        }
    }

    static int PASCAL SafeStrlen(LPCTSTR lpsz)
    {
        return (lpsz == NULL) ? 0 : lstrlen(lpsz);
    }

    static int __stdcall _LoadString(UINT nID, LPTSTR lpszBuf, UINT nMaxBuf)
    {
#ifdef _DEBUG
        // LoadString without annoying warning from the Debug kernel if the
        //  segment containing the string is not present
        if (::FindResource(BDWinApp::GetAppInstance(), MAKEINTRESOURCE((nID >> 4) + 1), RT_STRING) == NULL)
        {
            lpszBuf[0] = _T('\0');
            return 0;   // not found
        }
#endif // _DEBUG

        int nLen = ::LoadString(BDWinApp::GetAppInstance(), nID, lpszBuf, nMaxBuf);
        if (nLen == 0)
            lpszBuf[0] = _T('\0');

        return nLen;
    }

    static const BDString& __stdcall _GetEmptyString()
    {
        return *(BDString*)&_atltmpPchNil;
    }

// BDString conversion helpers
    static int __cdecl _wcstombsz(char* mbstr, const wchar_t* wcstr, size_t count)
    {
        if (count == 0 && mbstr != NULL)
            return 0;

        int result = ::WideCharToMultiByte(CP_ACP, 0, wcstr, -1, mbstr, (int)count, NULL, NULL);
        assert(mbstr == NULL || result <= (int)count);
        if ((mbstr != NULL) && (result > 0))
            mbstr[result - 1] = 0;
        return result;
    }

    static int __cdecl _mbstowcsz(wchar_t* wcstr, const char* mbstr, size_t count)
    {
        if (count == 0 && wcstr != NULL)
            return 0;

        int result = ::MultiByteToWideChar(CP_ACP, 0, mbstr, -1, wcstr, (int)count);
        assert(wcstr == NULL || result <= (int)count);
        if ((wcstr != NULL) && (result > 0))
            wcstr[result - 1] = 0;
        return result;
    }

// Helpers to avoid CRT startup code
#ifdef _ATL_MIN_CRT
    static const TCHAR* _cstrchr(const TCHAR* p, TCHAR ch)
    {
        // strchr for '\0' should succeed
        while (*p != 0)
        {
            if (*p == ch)
                break;
            p = ::CharNext(p);
        }
        return (*p == ch) ? p : NULL;
    }

    static TCHAR* _cstrrev(TCHAR* pStr)
    {
        // optimize NULL, zero-length, and single-char case
        if ((pStr == NULL) || (pStr[0] == _T('\0')) || (pStr[1] == _T('\0')))
            return pStr;

        TCHAR* p = pStr;

        while (*p != 0) 
        {
            TCHAR* pNext = ::CharNext(p);
            if(pNext > p + 1)
            {
                char p1 = *(char*)p;
                *(char*)p = *(char*)(p + 1);
                *(char*)(p + 1) = p1;
            }
            p = pNext;
        }

        p--;
        TCHAR* q = pStr;

        while (q < p)
        {
            TCHAR t = *q;
            *q = *p;
            *p = t;
            q++;
            p--;
        }
        return pStr;
    }

    static const TCHAR* _cstrstr(const TCHAR* pStr, const TCHAR* pCharSet)
    {
        int nLen = lstrlen(pCharSet);
        if (nLen == 0)
            return (TCHAR*)pStr;

        const TCHAR* pRet = NULL;
        const TCHAR* pCur = pStr;
        while((pCur = _cstrchr(pCur, *pCharSet)) != NULL)
        {
            if(memcmp(pCur, pCharSet, nLen * sizeof(TCHAR)) == 0)
            {
                pRet = pCur;
                break;
            }
            pCur = ::CharNext(pCur);
        }
        return pRet;
    }

    static int _cstrspn(const TCHAR* pStr, const TCHAR* pCharSet)
    {
        int nRet = 0;
        const TCHAR* p = pStr;
        while (*p != 0)
        {
            const TCHAR* pNext = ::CharNext(p);
            if(pNext > p + 1)
            {
                if(_cstrchr_db(pCharSet, *p, *(p + 1)) == NULL)
                    break;
                nRet += 2;
            }
            else
            {
                if(_cstrchr(pCharSet, *p) == NULL)
                    break;
                nRet++;
            }
            p = pNext;
        }
        return nRet;
    }

    static int _cstrcspn(const TCHAR* pStr, const TCHAR* pCharSet)
    {
        int nRet = 0;
        TCHAR* p = (TCHAR*)pStr;
        while (*p != 0)
        {
            TCHAR* pNext = ::CharNext(p);
            if(pNext > p + 1)
            {
                if(_cstrchr_db(pCharSet, *p, *(p + 1)) != NULL)
                    break;
                nRet += 2;
            }
            else
            {
                if(_cstrchr(pCharSet, *p) != NULL)
                    break;
                nRet++;
            }
            p = pNext;
        }
        return nRet;
    }

    static const TCHAR* _cstrpbrk(const TCHAR* p, const TCHAR* lpszCharSet)
    {
        int n = _cstrcspn(p, lpszCharSet);
        return (p[n] != 0) ? &p[n] : NULL;
    }

    static int _cstrcmp(const TCHAR* pstrOne, const TCHAR* pstrOther)
    {
        return lstrcmp(pstrOne, pstrOther);
    }

    static int _cstrcmpi(const TCHAR* pstrOne, const TCHAR* pstrOther)
    {
        return lstrcmpi(pstrOne, pstrOther);
    }

    static int _cstrcoll(const TCHAR* pstrOne, const TCHAR* pstrOther)
    {
        int nRet = CompareString(GetThreadLocale(), 0, pstrOne, -1, pstrOther, -1);
        assert(nRet != 0);
        return nRet - 2;   // convert to strcmp convention
    }

    static int _cstrcolli(const TCHAR* pstrOne, const TCHAR* pstrOther)
    {
        int nRet = CompareString(GetThreadLocale(), NORM_IGNORECASE, pstrOne, -1, pstrOther, -1);
        assert(nRet != 0);
        return nRet - 2;   // convert to strcmp convention
    }
#else // !_ATL_MIN_CRT
    static const TCHAR* _cstrchr(const TCHAR* p, TCHAR ch)
    {
        return _tcschr(p, ch);
    }

    static TCHAR* _cstrrev(TCHAR* pStr)
    {
        return _tcsrev(pStr);
    }

    static const TCHAR* _cstrstr(const TCHAR* pStr, const TCHAR* pCharSet)
    {
        return _tcsstr(pStr, pCharSet);
    }

    static int _cstrspn(const TCHAR* pStr, const TCHAR* pCharSet)
    {
        return (int)_tcsspn(pStr, pCharSet);
    }

    static int _cstrcspn(const TCHAR* pStr, const TCHAR* pCharSet)
    {
        return (int)_tcscspn(pStr, pCharSet);
    }

    static const TCHAR* _cstrpbrk(const TCHAR* p, const TCHAR* lpszCharSet)
    {
        return _tcspbrk(p, lpszCharSet);
    }

    static int _cstrcmp(const TCHAR* pstrOne, const TCHAR* pstrOther)
    {
        return _tcscmp(pstrOne, pstrOther);
    }

    static int _cstrcmpi(const TCHAR* pstrOne, const TCHAR* pstrOther)
    {
        return _tcsicmp(pstrOne, pstrOther);
    }

#ifndef _WIN32_WCE
    static int _cstrcoll(const TCHAR* pstrOne, const TCHAR* pstrOther)
    {
        return _tcscoll(pstrOne, pstrOther);
    }

    static int _cstrcolli(const TCHAR* pstrOne, const TCHAR* pstrOther)
    {
        return _tcsicoll(pstrOne, pstrOther);
    }
#endif // !_WIN32_WCE
#endif // !_ATL_MIN_CRT

    static const TCHAR* _cstrrchr(const TCHAR* p, TCHAR ch)
    {
        return wcsrchr(p, ch);
    }

    static int _cstrisdigit(TCHAR ch)
    {
        return isdigit(ch);
    }

    static int _cstrisspace(TCHAR ch)
    {
        return isspace(ch);
    }

    static int _cstrtoi(const TCHAR* nptr)
    {
        return _wtoi(nptr);
    }

    static const TCHAR* _cstrchr_db(const TCHAR* p, TCHAR ch1, TCHAR ch2)
    {
        const TCHAR* lpsz = NULL;
        while (*p != 0)
        {
            if (*p == ch1 && *(p + 1) == ch2)
            {
                lpsz = p;
                break;
            }
            p = ::CharNext(p);
        }
        return lpsz;
    }
};


// Compare helpers

inline bool __stdcall operator ==(const BDString& s1, const BDString& s2)
{ return s1.Compare(s2) == 0; }

inline bool __stdcall operator ==(const BDString& s1, LPCTSTR s2)
{ return s1.Compare(s2) == 0; }

inline bool __stdcall operator ==(LPCTSTR s1, const BDString& s2)
{ return s2.Compare(s1) == 0; }

inline bool __stdcall operator !=(const BDString& s1, const BDString& s2)
{ return s1.Compare(s2) != 0; }

inline bool __stdcall operator !=(const BDString& s1, LPCTSTR s2)
{ return s1.Compare(s2) != 0; }

inline bool __stdcall operator !=(LPCTSTR s1, const BDString& s2)
{ return s2.Compare(s1) != 0; }

inline bool __stdcall operator <(const BDString& s1, const BDString& s2)
{ return s1.Compare(s2) < 0; }

inline bool __stdcall operator <(const BDString& s1, LPCTSTR s2)
{ return s1.Compare(s2) < 0; }

inline bool __stdcall operator <(LPCTSTR s1, const BDString& s2)
{ return s2.Compare(s1) > 0; }

inline bool __stdcall operator >(const BDString& s1, const BDString& s2)
{ return s1.Compare(s2) > 0; }

inline bool __stdcall operator >(const BDString& s1, LPCTSTR s2)
{ return s1.Compare(s2) > 0; }

inline bool __stdcall operator >(LPCTSTR s1, const BDString& s2)
{ return s2.Compare(s1) < 0; }

inline bool __stdcall operator <=(const BDString& s1, const BDString& s2)
{ return s1.Compare(s2) <= 0; }

inline bool __stdcall operator <=(const BDString& s1, LPCTSTR s2)
{ return s1.Compare(s2) <= 0; }

inline bool __stdcall operator <=(LPCTSTR s1, const BDString& s2)
{ return s2.Compare(s1) >= 0; }

inline bool __stdcall operator >=(const BDString& s1, const BDString& s2)
{ return s1.Compare(s2) >= 0; }

inline bool __stdcall operator >=(const BDString& s1, LPCTSTR s2)
{ return s1.Compare(s2) >= 0; }

inline bool __stdcall operator >=(LPCTSTR s1, const BDString& s2)
{ return s2.Compare(s1) <= 0; }


// BDString "operator +" functions

inline BDString __stdcall operator +(const BDString& string1, const BDString& string2)
{
    BDString s;
    s.ConcatCopy(string1.GetData()->nDataLength, string1.m_pchData, string2.GetData()->nDataLength, string2.m_pchData);
    return s;
}

inline BDString __stdcall operator +(const BDString& string, TCHAR ch)
{
    BDString s;
    s.ConcatCopy(string.GetData()->nDataLength, string.m_pchData, 1, &ch);
    return s;
}

inline BDString __stdcall operator +(TCHAR ch, const BDString& string)
{
    BDString s;
    s.ConcatCopy(1, &ch, string.GetData()->nDataLength, string.m_pchData);
    return s;
}

#ifdef _UNICODE
inline BDString __stdcall operator +(const BDString& string, char ch)
{
    return string + (TCHAR)ch;
}

inline BDString __stdcall operator +(char ch, const BDString& string)
{
    return (TCHAR)ch + string;
}
#endif // _UNICODE

inline BDString __stdcall operator +(const BDString& string, LPCTSTR lpsz)
{
    assert(lpsz == NULL || BDString::_IsValidString(lpsz));
    BDString s;
    s.ConcatCopy(string.GetData()->nDataLength, string.m_pchData, BDString::SafeStrlen(lpsz), lpsz);
    return s;
}

inline BDString __stdcall operator +(LPCTSTR lpsz, const BDString& string)
{
    assert(lpsz == NULL || BDString::_IsValidString(lpsz));
    BDString s;
    s.ConcatCopy(BDString::SafeStrlen(lpsz), lpsz, string.GetData()->nDataLength, string.m_pchData);
    return s;
}


