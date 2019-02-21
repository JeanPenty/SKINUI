#ifndef TYPE_HEAD_FILE
#define TYPE_HEAD_FILE

#pragma once

//以下摘自MFC源码
class cCSize;
class cCPoint;
class cCRect;

/////////////////////////////////////////////////////////////////////////////
// CSize - An extent, similar to Windows SIZE structure.

class GAME_ENGINE_CLASS cCSize : public tagSIZE
{
public:

	// Constructors
	// construct an uninitialized size
	cCSize() throw();
	// create from two integers
	cCSize(int initCX, int initCY) throw();
	// create from another size
	cCSize(SIZE initSize) throw();
	// create from a point
	cCSize(POINT initPt) throw();
	// create from a DWORD: cx = LOWORD(dw) cy = HIWORD(dw)
	cCSize(DWORD dwSize) throw();

	// Operations
	BOOL operator==(SIZE size) const throw();
	BOOL operator!=(SIZE size) const throw();
	void operator+=(SIZE size) throw();
	void operator-=(SIZE size) throw();
	void SetSize(int CX, int CY) throw();

	// Operators returning CSize values
	cCSize operator+(SIZE size) const throw();
	cCSize operator-(SIZE size) const throw();
	cCSize operator-() const throw();

	// Operators returning CPoint values
	cCPoint operator+(POINT point) const throw();
	cCPoint operator-(POINT point) const throw();

	// Operators returning CRect values
	cCRect operator+(const RECT* lpRect) const throw();
	cCRect operator-(const RECT* lpRect) const throw();
};

/////////////////////////////////////////////////////////////////////////////
// CPoint - A 2-D point, similar to Windows POINT structure.

class GAME_ENGINE_CLASS cCPoint : public tagPOINT
{
public:
	// Constructors

	// create an uninitialized point
	cCPoint() throw();
	// create from two integers
	cCPoint(int initX, int initY) throw();
	// create from another point
	cCPoint(POINT initPt) throw();
	// create from a size
	cCPoint(SIZE initSize) throw();
	// create from an LPARAM: x = LOWORD(dw) y = HIWORD(dw)
	cCPoint(LPARAM dwPoint) throw();


	// Operations

	// translate the point
	void Offset(int xOffset, int yOffset) throw();
	void Offset(POINT point) throw();
	void Offset(SIZE size) throw();
	void SetPoint(int X, int Y) throw();

	BOOL operator==(POINT point) const throw();
	BOOL operator!=(POINT point) const throw();
	void operator+=(SIZE size) throw();
	void operator-=(SIZE size) throw();
	void operator+=(POINT point) throw();
	void operator-=(POINT point) throw();

	// Operators returning CPoint values
	cCPoint operator+(SIZE size) const throw();
	cCPoint operator-(SIZE size) const throw();
	cCPoint operator-() const throw();
	cCPoint operator+(POINT point) const throw();

	// Operators returning CSize values
	cCSize operator-(POINT point) const throw();

	// Operators returning CRect values
	cCRect operator+(const RECT* lpRect) const throw();
	cCRect operator-(const RECT* lpRect) const throw();
};

/////////////////////////////////////////////////////////////////////////////
// CRect - A 2-D rectangle, similar to Windows RECT structure.

class GAME_ENGINE_CLASS cCRect : public tagRECT
{
	// Constructors
public:
	// uninitialized rectangle
	cCRect() throw();
	// from left, top, right, and bottom
	cCRect(int l, int t, int r, int b) throw();
	// copy constructor
	cCRect(const RECT& srcRect) throw();
	// from a pointer to another rect
	cCRect(LPCRECT lpSrcRect) throw();
	// from a point and size
	cCRect(POINT point, SIZE size) throw();
	// from two points
	cCRect(POINT topLeft, POINT bottomRight) throw();

	// Attributes (in addition to RECT members)

	// retrieves the width
	int Width() const throw();
	// returns the height
	int Height() const throw();
	// returns the size
	cCSize Size() const throw();
	// reference to the top-left point
	cCPoint& TopLeft() throw();
	// reference to the bottom-right point
	cCPoint& BottomRight() throw();
	// const reference to the top-left point
	const cCPoint& TopLeft() const throw();
	// const reference to the bottom-right point
	const cCPoint& BottomRight() const throw();
	// the geometric center point of the rectangle
	cCPoint CenterPoint() const throw();
	// swap the left and right
	void SwapLeftRight() throw();
	static void WINAPI SwapLeftRight(LPRECT lpRect) throw();

	// convert between CRect and LPRECT/LPCRECT (no need for &)
	operator LPRECT() throw();
	operator LPCRECT() const throw();

	// returns TRUE if rectangle has no area
	BOOL IsRectEmpty() const throw();
	// returns TRUE if rectangle is at (0,0) and has no area
	BOOL IsRectNull() const throw();
	// returns TRUE if point is within rectangle
	BOOL PtInRect(POINT point) const throw();

	// Operations

	// set rectangle from left, top, right, and bottom
	void SetRect(int x1, int y1, int x2, int y2) throw();
	void SetRect(POINT topLeft, POINT bottomRight) throw();
	// empty the rectangle
	void SetRectEmpty() throw();
	// copy from another rectangle
	void CopyRect(LPCRECT lpSrcRect) throw();
	// TRUE if exactly the same as another rectangle
	BOOL EqualRect(LPCRECT lpRect) const throw();

	// Inflate rectangle's width and height by
	// x units to the left and right ends of the rectangle
	// and y units to the top and bottom.
	void InflateRect(int x, int y) throw();
	// Inflate rectangle's width and height by
	// size.cx units to the left and right ends of the rectangle
	// and size.cy units to the top and bottom.
	void InflateRect(SIZE size) throw();
	// Inflate rectangle's width and height by moving individual sides.
	// Left side is moved to the left, right side is moved to the right,
	// top is moved up and bottom is moved down.
	void InflateRect(LPCRECT lpRect) throw();
	void InflateRect(int l, int t, int r, int b) throw();

	// deflate the rectangle's width and height without
	// moving its top or left
	void DeflateRect(int x, int y) throw();
	void DeflateRect(SIZE size) throw();
	void DeflateRect(LPCRECT lpRect) throw();
	void DeflateRect(int l, int t, int r, int b) throw();

	// translate the rectangle by moving its top and left
	void OffsetRect(int x, int y) throw();
	void OffsetRect(SIZE size) throw();
	void OffsetRect(POINT point) throw();
	void NormalizeRect() throw();

	// absolute position of rectangle
	void MoveToY(int y) throw();
	void MoveToX(int x) throw();
	void MoveToXY(int x, int y) throw();
	void MoveToXY(POINT point) throw();

	// set this rectangle to intersection of two others
	BOOL IntersectRect(LPCRECT lpRect1, LPCRECT lpRect2) throw();

	// set this rectangle to bounding union of two others
	BOOL UnionRect(LPCRECT lpRect1, LPCRECT lpRect2) throw();

	// set this rectangle to minimum of two others
	BOOL SubtractRect(LPCRECT lpRectSrc1, LPCRECT lpRectSrc2) throw();

	// Additional Operations
	void operator=(const RECT& srcRect) throw();
	BOOL operator==(const RECT& rect) const throw();
	BOOL operator!=(const RECT& rect) const throw();
	void operator+=(POINT point) throw();
	void operator+=(SIZE size) throw();
	void operator+=(LPCRECT lpRect) throw();
	void operator-=(POINT point) throw();
	void operator-=(SIZE size) throw();
	void operator-=(LPCRECT lpRect) throw();
	void operator&=(const RECT& rect) throw();
	void operator|=(const RECT& rect) throw();

	// Operators returning CRect values
	cCRect operator+(POINT point) const throw();
	cCRect operator-(POINT point) const throw();
	cCRect operator+(LPCRECT lpRect) const throw();
	cCRect operator+(SIZE size) const throw();
	cCRect operator-(SIZE size) const throw();
	cCRect operator-(LPCRECT lpRect) const throw();
	cCRect operator&(const RECT& rect2) const throw();
	cCRect operator|(const RECT& rect2) const throw();
	cCRect MulDiv(int nMultiplier, int nDivisor) const throw();
};

/////////////////////////////////////////////////////////////////////////////
// CRect - A 2-D rectangle, similar to Windows RECT structure.

//////////////////////////////////////////////////////////////////////////////////

class GAME_ENGINE_CLASS cCString
{
public:
	enum { MAX_LOCAL_STRING_LEN = 63 };

	cCString();
	cCString(const TCHAR ch);
	cCString(const cCString& src);
	cCString(LPCTSTR lpsz, int nLen = -1);
	~cCString();

	void Empty();
	int GetLength() const;
	bool IsEmpty() const;
	TCHAR GetAt(int nIndex) const;
	void Append(LPCTSTR pstr);
	void Assign(LPCTSTR pstr, int nLength = -1);
	LPCTSTR GetData() const;

	void SetAt(int nIndex, TCHAR ch);
	operator LPCTSTR() const;

	TCHAR operator[] (int nIndex) const;
	const cCString& operator=(const cCString& src);
	const cCString& operator=(const TCHAR ch);
	const cCString& operator=(LPCTSTR pstr);
#ifdef _UNICODE
	const cCString& cCString::operator=(LPCSTR lpStr);
	const cCString& cCString::operator+=(LPCSTR lpStr);
#else
	const cCString& cCString::operator=(LPCWSTR lpwStr);
	const cCString& cCString::operator+=(LPCWSTR lpwStr);
#endif
	cCString operator+(const cCString& src) const;
	cCString operator+(LPCTSTR pstr) const;
	const cCString& operator+=(const cCString& src);
	const cCString& operator+=(LPCTSTR pstr);
	const cCString& operator+=(const TCHAR ch);

	bool operator == (LPCTSTR str) const;
	bool operator != (LPCTSTR str) const;
	bool operator <= (LPCTSTR str) const;
	bool operator <  (LPCTSTR str) const;
	bool operator >= (LPCTSTR str) const;
	bool operator >  (LPCTSTR str) const;

	int Compare(LPCTSTR pstr) const;
	int CompareNoCase(LPCTSTR pstr) const;

	void MakeUpper();
	void MakeLower();

	cCString Left(int nLength) const;
	cCString Mid(int iPos, int nLength = -1) const;
	cCString Right(int nLength) const;

	int Find(TCHAR ch, int iPos = 0) const;
	int Find(LPCTSTR pstr, int iPos = 0) const;
	int ReverseFind(TCHAR ch) const;
	int Replace(LPCTSTR pstrFrom, LPCTSTR pstrTo);

	int __cdecl Format(LPCTSTR pstrFormat, ...);
	int __cdecl FormatV(LPCTSTR pstrFormat, va_list args);
	int __cdecl SmallFormat(LPCTSTR pstrFormat, ...);

protected:
	LPTSTR m_pstr;
	TCHAR m_szBuffer[MAX_LOCAL_STRING_LEN + 1];
};


#endif