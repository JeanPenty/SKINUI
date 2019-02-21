#include "stdafx.h"
#include "type.h"
#include <WindowsX.h>

// CSize
cCSize::cCSize() throw()
{ /* random filled */ }
cCSize::cCSize(int initCX, int initCY) throw()
{ cx = initCX; cy = initCY; }
cCSize::cCSize(SIZE initSize) throw()
{ *(SIZE*)this = initSize; }
cCSize::cCSize(POINT initPt) throw()
{ *(POINT*)this = initPt; }
cCSize::cCSize(DWORD dwSize) throw()
{
	cx = (short)LOWORD(dwSize);
	cy = (short)HIWORD(dwSize);
}
BOOL cCSize::operator==(SIZE size) const throw()
{ return (cx == size.cx && cy == size.cy); }
BOOL cCSize::operator!=(SIZE size) const throw()
{ return (cx != size.cx || cy != size.cy); }
void cCSize::operator+=(SIZE size) throw()
{ cx += size.cx; cy += size.cy; }
void cCSize::operator-=(SIZE size) throw()
{ cx -= size.cx; cy -= size.cy; }
void cCSize::SetSize(int CX, int CY) throw()
{ cx = CX; cy = CY; }	
cCSize cCSize::operator+(SIZE size) const throw()
{ return cCSize(cx + size.cx, cy + size.cy); }
cCSize cCSize::operator-(SIZE size) const throw()
{ return cCSize(cx - size.cx, cy - size.cy); }
cCSize cCSize::operator-() const throw()
{ return cCSize(-cx, -cy); }
cCPoint cCSize::operator+(POINT point) const throw()
{ return cCPoint(cx + point.x, cy + point.y); }
cCPoint cCSize::operator-(POINT point) const throw()
{ return cCPoint(cx - point.x, cy - point.y); }
cCRect cCSize::operator+(const RECT* lpRect) const throw()
{ return cCRect(lpRect) + *this; }
cCRect cCSize::operator-(const RECT* lpRect) const throw()
{ return cCRect(lpRect) - *this; }

// CPoint
cCPoint::cCPoint() throw()
{ /* random filled */ }
cCPoint::cCPoint(int initX, int initY) throw()
{ x = initX; y = initY; }
cCPoint::cCPoint(POINT initPt) throw()
{ *(POINT*)this = initPt; }
cCPoint::cCPoint(SIZE initSize) throw()
{ *(SIZE*)this = initSize; }
cCPoint::cCPoint(LPARAM dwPoint) throw()
{
	x = (short)GET_X_LPARAM(dwPoint);
	y = (short)GET_Y_LPARAM(dwPoint);
}
void cCPoint::Offset(int xOffset, int yOffset) throw()
{ x += xOffset; y += yOffset; }
void cCPoint::Offset(POINT point) throw()
{ x += point.x; y += point.y; }
void cCPoint::Offset(SIZE size) throw()
{ x += size.cx; y += size.cy; }
void cCPoint::SetPoint(int X, int Y) throw()
{ x = X; y = Y; }
BOOL cCPoint::operator==(POINT point) const throw()
{ return (x == point.x && y == point.y); }
BOOL cCPoint::operator!=(POINT point) const throw()
{ return (x != point.x || y != point.y); }
void cCPoint::operator+=(SIZE size) throw()
{ x += size.cx; y += size.cy; }
void cCPoint::operator-=(SIZE size) throw()
{ x -= size.cx; y -= size.cy; }
void cCPoint::operator+=(POINT point) throw()
{ x += point.x; y += point.y; }
void cCPoint::operator-=(POINT point) throw()
{ x -= point.x; y -= point.y; }
cCPoint cCPoint::operator+(SIZE size) const throw()
{ return cCPoint(x + size.cx, y + size.cy); }
cCPoint cCPoint::operator-(SIZE size) const throw()
{ return cCPoint(x - size.cx, y - size.cy); }
cCPoint cCPoint::operator-() const throw()
{ return cCPoint(-x, -y); }
cCPoint cCPoint::operator+(POINT point) const throw()
{ return cCPoint(x + point.x, y + point.y); }
cCSize cCPoint::operator-(POINT point) const throw()
{ return cCSize(x - point.x, y - point.y); }
cCRect cCPoint::operator+(const RECT* lpRect) const throw()
{ return cCRect(lpRect) + *this; }
cCRect cCPoint::operator-(const RECT* lpRect) const throw()
{ return cCRect(lpRect) - *this; }

// CRect
cCRect::cCRect() throw()
{ /* random filled */ }
cCRect::cCRect(int l, int t, int r, int b) throw()
{ left = l; top = t; right = r; bottom = b; }
cCRect::cCRect(const RECT& srcRect) throw()
{ ::CopyRect(this, &srcRect); }
cCRect::cCRect(LPCRECT lpSrcRect) throw()
{ ::CopyRect(this, lpSrcRect); }
cCRect::cCRect(POINT point, SIZE size) throw()
{ right = (left = point.x) + size.cx; bottom = (top = point.y) + size.cy; }
cCRect::cCRect(POINT topLeft, POINT bottomRight) throw()
{ left = topLeft.x; top = topLeft.y;
right = bottomRight.x; bottom = bottomRight.y; }
int cCRect::Width() const throw()
{ return right - left; }
int cCRect::Height() const throw()
{ return bottom - top; }
cCSize cCRect::Size() const throw()
{ return cCSize(right - left, bottom - top); }
cCPoint& cCRect::TopLeft() throw()
{ return *((cCPoint*)this); }
cCPoint& cCRect::BottomRight() throw()
{ return *((cCPoint*)this+1); }
const cCPoint& cCRect::TopLeft() const throw()
{ return *((cCPoint*)this); }
const cCPoint& cCRect::BottomRight() const throw()
{ return *((cCPoint*)this+1); }
cCPoint cCRect::CenterPoint() const throw()
{ return cCPoint((left+right)/2, (top+bottom)/2); }
void cCRect::SwapLeftRight() throw()
{ SwapLeftRight(LPRECT(this)); }
void WINAPI cCRect::SwapLeftRight(LPRECT lpRect) throw()
{ LONG temp = lpRect->left; lpRect->left = lpRect->right; lpRect->right = temp; }
cCRect::operator LPRECT() throw()
{ return this; }
cCRect::operator LPCRECT() const throw()
{ return this; }
BOOL cCRect::IsRectEmpty() const throw()
{ return ::IsRectEmpty(this); }
BOOL cCRect::IsRectNull() const throw()
{ return (left == 0 && right == 0 && top == 0 && bottom == 0); }
BOOL cCRect::PtInRect(POINT point) const throw()
{ return ::PtInRect(this, point); }
void cCRect::SetRect(int x1, int y1, int x2, int y2) throw()
{ ::SetRect(this, x1, y1, x2, y2); }
void cCRect::SetRect(POINT topLeft, POINT bottomRight) throw()
{ ::SetRect(this, topLeft.x, topLeft.y, bottomRight.x, bottomRight.y); }
void cCRect::SetRectEmpty() throw()
{ ::SetRectEmpty(this); }
void cCRect::CopyRect(LPCRECT lpSrcRect) throw()
{ ::CopyRect(this, lpSrcRect); }
BOOL cCRect::EqualRect(LPCRECT lpRect) const throw()
{ return ::EqualRect(this, lpRect); }
void cCRect::InflateRect(int x, int y) throw()
{ ::InflateRect(this, x, y); }
void cCRect::InflateRect(SIZE size) throw()
{ ::InflateRect(this, size.cx, size.cy); }
void cCRect::DeflateRect(int x, int y) throw()
{ ::InflateRect(this, -x, -y); }
void cCRect::DeflateRect(SIZE size) throw()
{ ::InflateRect(this, -size.cx, -size.cy); }
void cCRect::OffsetRect(int x, int y) throw()
{ ::OffsetRect(this, x, y); }
void cCRect::OffsetRect(POINT point) throw()
{ ::OffsetRect(this, point.x, point.y); }
void cCRect::OffsetRect(SIZE size) throw()
{ ::OffsetRect(this, size.cx, size.cy); }
void cCRect::MoveToY(int y) throw()
{ bottom = Height() + y; top = y; }
void cCRect::MoveToX(int x) throw()
{ right = Width() + x; left = x; }
void cCRect::MoveToXY(int x, int y) throw()
{ MoveToX(x); MoveToY(y); }
void cCRect::MoveToXY(POINT pt) throw()
{ MoveToX(pt.x); MoveToY(pt.y); }
BOOL cCRect::IntersectRect(LPCRECT lpRect1, LPCRECT lpRect2) throw()
{ return ::IntersectRect(this, lpRect1, lpRect2);}
BOOL cCRect::UnionRect(LPCRECT lpRect1, LPCRECT lpRect2) throw()
{ return ::UnionRect(this, lpRect1, lpRect2); }
void cCRect::operator=(const RECT& srcRect) throw()
{ ::CopyRect(this, &srcRect); }
BOOL cCRect::operator==(const RECT& rect) const throw()
{ return ::EqualRect(this, &rect); }
BOOL cCRect::operator!=(const RECT& rect) const throw()
{ return !::EqualRect(this, &rect); }
void cCRect::operator+=(POINT point) throw()
{ ::OffsetRect(this, point.x, point.y); }
void cCRect::operator+=(SIZE size) throw()
{ ::OffsetRect(this, size.cx, size.cy); }
void cCRect::operator+=(LPCRECT lpRect) throw()
{ InflateRect(lpRect); }
void cCRect::operator-=(POINT point) throw()
{ ::OffsetRect(this, -point.x, -point.y); }
void cCRect::operator-=(SIZE size) throw()
{ ::OffsetRect(this, -size.cx, -size.cy); }
void cCRect::operator-=(LPCRECT lpRect) throw()
{ DeflateRect(lpRect); }
void cCRect::operator&=(const RECT& rect) throw()
{ ::IntersectRect(this, this, &rect); }
void cCRect::operator|=(const RECT& rect) throw()
{ ::UnionRect(this, this, &rect); }
cCRect cCRect::operator+(POINT pt) const throw()
{ cCRect rect(*this); ::OffsetRect(&rect, pt.x, pt.y); return rect; }
cCRect cCRect::operator-(POINT pt) const throw()
{ cCRect rect(*this); ::OffsetRect(&rect, -pt.x, -pt.y); return rect; }
cCRect cCRect::operator+(SIZE size) const throw()
{ cCRect rect(*this); ::OffsetRect(&rect, size.cx, size.cy); return rect; }
cCRect cCRect::operator-(SIZE size) const throw()
{ cCRect rect(*this); ::OffsetRect(&rect, -size.cx, -size.cy); return rect; }
cCRect cCRect::operator+(LPCRECT lpRect) const throw()
{ cCRect rect(this); rect.InflateRect(lpRect); return rect; }
cCRect cCRect::operator-(LPCRECT lpRect) const throw()
{ cCRect rect(this); rect.DeflateRect(lpRect); return rect; }
cCRect cCRect::operator&(const RECT& rect2) const throw()
{ cCRect rect; ::IntersectRect(&rect, this, &rect2);
return rect; }
cCRect cCRect::operator|(const RECT& rect2) const throw()
{ cCRect rect; ::UnionRect(&rect, this, &rect2);
return rect; }
BOOL cCRect::SubtractRect(LPCRECT lpRectSrc1, LPCRECT lpRectSrc2) throw()
{ return ::SubtractRect(this, lpRectSrc1, lpRectSrc2); }

void cCRect::NormalizeRect() throw()
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

void cCRect::InflateRect(LPCRECT lpRect) throw()
{
	left -= lpRect->left;		top -= lpRect->top;
	right += lpRect->right;		bottom += lpRect->bottom;
}

void cCRect::InflateRect(int l, int t, int r, int b) throw()
{
	left -= l;			top -= t;
	right += r;			bottom += b;
}

void cCRect::DeflateRect(LPCRECT lpRect) throw()
{
	left += lpRect->left;	top += lpRect->top;
	right -= lpRect->right;	bottom -= lpRect->bottom;
}

void cCRect::DeflateRect(int l, int t, int r, int b) throw()
{
	left += l;		top += t;
	right -= r;		bottom -= b;
}

cCRect cCRect::MulDiv(int nMultiplier, int nDivisor) const throw()
{
	return cCRect(
		::MulDiv(left, nMultiplier, nDivisor),
		::MulDiv(top, nMultiplier, nDivisor),
		::MulDiv(right, nMultiplier, nDivisor),
		::MulDiv(bottom, nMultiplier, nDivisor));
}

//////////////////////////////////////////////////////////////////////////
cCString::cCString() : m_pstr(m_szBuffer)
{
	m_szBuffer[0] = '\0';
}

cCString::cCString(const TCHAR ch) : m_pstr(m_szBuffer)
{
	m_szBuffer[0] = ch;
	m_szBuffer[1] = '\0';
}

cCString::cCString(LPCTSTR lpsz, int nLen) : m_pstr(m_szBuffer)
{      
	assert(!::IsBadStringPtr(lpsz,-1) || lpsz==NULL);
	m_szBuffer[0] = '\0';
	Assign(lpsz, nLen);
}

cCString::cCString(const cCString& src) : m_pstr(m_szBuffer)
{
	m_szBuffer[0] = '\0';
	Assign(src.m_pstr);
}

cCString::~cCString()
{
	if( m_pstr != m_szBuffer ) free(m_pstr);
}

int cCString::GetLength() const
{ 
	return (int) _tcslen(m_pstr); 
}

cCString::operator LPCTSTR() const 
{ 
	return m_pstr; 
}

void cCString::Append(LPCTSTR pstr)
{
	int nNewLength = GetLength() + (int) _tcslen(pstr);
	if( nNewLength >= MAX_LOCAL_STRING_LEN ) {
		if( m_pstr == m_szBuffer ) {
			m_pstr = static_cast<LPTSTR>(malloc((nNewLength + 1) * sizeof(TCHAR)));
			_tcscpy(m_pstr, m_szBuffer);
			_tcscat(m_pstr, pstr);
		}
		else {
			m_pstr = static_cast<LPTSTR>(realloc(m_pstr, (nNewLength + 1) * sizeof(TCHAR)));
			_tcscat(m_pstr, pstr);
		}
	}
	else {
		if( m_pstr != m_szBuffer ) {
			free(m_pstr);
			m_pstr = m_szBuffer;
		}
		_tcscat(m_szBuffer, pstr);
	}
}

void cCString::Assign(LPCTSTR pstr, int cchMax)
{
	if( pstr == NULL ) pstr = _T("");
	cchMax = (cchMax < 0 ? (int) _tcslen(pstr) : cchMax);
	if( cchMax < MAX_LOCAL_STRING_LEN ) {
		if( m_pstr != m_szBuffer ) {
			free(m_pstr);
			m_pstr = m_szBuffer;
		}
	}
	else if( cchMax > GetLength() || m_pstr == m_szBuffer ) {
		if( m_pstr == m_szBuffer ) m_pstr = NULL;
		m_pstr = static_cast<LPTSTR>(realloc(m_pstr, (cchMax + 1) * sizeof(TCHAR)));
	}
	_tcsncpy(m_pstr, pstr, cchMax);
	m_pstr[cchMax] = '\0';
}

bool cCString::IsEmpty() const 
{ 
	return m_pstr[0] == '\0'; 
}

void cCString::Empty() 
{ 
	if( m_pstr != m_szBuffer ) free(m_pstr);
	m_pstr = m_szBuffer;
	m_szBuffer[0] = '\0'; 
}

LPCTSTR cCString::GetData() const
{
	return m_pstr;
}

TCHAR cCString::GetAt(int nIndex) const
{
	return m_pstr[nIndex];
}

TCHAR cCString::operator[] (int nIndex) const
{ 
	return m_pstr[nIndex];
}   

const cCString& cCString::operator=(const cCString& src)
{      
	Assign(src);
	return *this;
}

const cCString& cCString::operator=(LPCTSTR lpStr)
{      
	if ( lpStr )
	{
		assert(!::IsBadStringPtr(lpStr,-1));
		Assign(lpStr);
	}
	else
	{
		Empty();
	}
	return *this;
}

#ifdef _UNICODE

const cCString& cCString::operator=(LPCSTR lpStr)
{
	if ( lpStr )
	{
		assert(!::IsBadStringPtrA(lpStr,-1));
		int cchStr = (int) strlen(lpStr) + 1;
		LPWSTR pwstr = (LPWSTR) _alloca(cchStr);
		if( pwstr != NULL ) ::MultiByteToWideChar(::GetACP(), 0, lpStr, -1, pwstr, cchStr) ;
		Assign(pwstr);
	}
	else
	{
		Empty();
	}
	return *this;
}

const cCString& cCString::operator+=(LPCSTR lpStr)
{
	if ( lpStr )
	{
		assert(!::IsBadStringPtrA(lpStr,-1));
		int cchStr = (int) strlen(lpStr) + 1;
		LPWSTR pwstr = (LPWSTR) _alloca(cchStr);
		if( pwstr != NULL ) ::MultiByteToWideChar(::GetACP(), 0, lpStr, -1, pwstr, cchStr) ;
		Append(pwstr);
	}

	return *this;
}

#else

const cCString& cCString::operator=(LPCWSTR lpwStr)
{      
	if ( lpwStr )
	{
		assert(!::IsBadStringPtrW(lpwStr,-1));
		int cchStr = ((int) wcslen(lpwStr) * 2) + 1;
		LPSTR pstr = (LPSTR) _alloca(cchStr);
		if( pstr != NULL ) ::WideCharToMultiByte(::GetACP(), 0, lpwStr, -1, pstr, cchStr, NULL, NULL);
		Assign(pstr);
	}
	else
	{
		Empty();
	}

	return *this;
}

const cCString& cCString::operator+=(LPCWSTR lpwStr)
{
	if ( lpwStr )
	{
		assert(!::IsBadStringPtrW(lpwStr,-1));
		int cchStr = ((int) wcslen(lpwStr) * 2) + 1;
		LPSTR pstr = (LPSTR) _alloca(cchStr);
		if( pstr != NULL ) ::WideCharToMultiByte(::GetACP(), 0, lpwStr, -1, pstr, cchStr, NULL, NULL);
		Append(pstr);
	}

	return *this;
}

#endif // _UNICODE

const cCString& cCString::operator=(const TCHAR ch)
{
	Empty();
	m_szBuffer[0] = ch;
	m_szBuffer[1] = '\0';
	return *this;
}

cCString cCString::operator+(const cCString& src) const
{
	cCString sTemp = *this;
	sTemp.Append(src);
	return sTemp;
}

cCString cCString::operator+(LPCTSTR lpStr) const
{
	if ( lpStr )
	{
		assert(!::IsBadStringPtr(lpStr,-1));
		cCString sTemp = *this;
		sTemp.Append(lpStr);
		return sTemp;
	}

	return *this;
}

const cCString& cCString::operator+=(const cCString& src)
{      
	Append(src);
	return *this;
}

const cCString& cCString::operator+=(LPCTSTR lpStr)
{      
	if ( lpStr )
	{
		assert(!::IsBadStringPtr(lpStr,-1));
		Append(lpStr);
	}

	return *this;
}

const cCString& cCString::operator+=(const TCHAR ch)
{      
	TCHAR str[] = { ch, '\0' };
	Append(str);
	return *this;
}

bool cCString::operator == (LPCTSTR str) const { return (Compare(str) == 0); };
bool cCString::operator != (LPCTSTR str) const { return (Compare(str) != 0); };
bool cCString::operator <= (LPCTSTR str) const { return (Compare(str) <= 0); };
bool cCString::operator <  (LPCTSTR str) const { return (Compare(str) <  0); };
bool cCString::operator >= (LPCTSTR str) const { return (Compare(str) >= 0); };
bool cCString::operator >  (LPCTSTR str) const { return (Compare(str) >  0); };

void cCString::SetAt(int nIndex, TCHAR ch)
{
	assert(nIndex>=0 && nIndex<GetLength());
	m_pstr[nIndex] = ch;
}

int cCString::Compare(LPCTSTR lpsz) const 
{ 
	return _tcscmp(m_pstr, lpsz); 
}

int cCString::CompareNoCase(LPCTSTR lpsz) const 
{ 
	return _tcsicmp(m_pstr, lpsz); 
}

void cCString::MakeUpper() 
{ 
	_tcsupr(m_pstr); 
}

void cCString::MakeLower() 
{ 
	_tcslwr(m_pstr); 
}

cCString cCString::Left(int iLength) const
{
	if( iLength < 0 ) iLength = 0;
	if( iLength > GetLength() ) iLength = GetLength();
	return cCString(m_pstr, iLength);
}

cCString cCString::Mid(int iPos, int iLength) const
{
	if( iLength < 0 ) iLength = GetLength() - iPos;
	if( iPos + iLength > GetLength() ) iLength = GetLength() - iPos;
	if( iLength <= 0 ) return cCString();
	return cCString(m_pstr + iPos, iLength);
}

cCString cCString::Right(int iLength) const
{
	int iPos = GetLength() - iLength;
	if( iPos < 0 ) {
		iPos = 0;
		iLength = GetLength();
	}
	return cCString(m_pstr + iPos, iLength);
}

int cCString::Find(TCHAR ch, int iPos /*= 0*/) const
{
	assert(iPos>=0 && iPos<=GetLength());
	if( iPos != 0 && (iPos < 0 || iPos >= GetLength()) ) return -1;
	LPCTSTR p = _tcschr(m_pstr + iPos, ch);
	if( p == NULL ) return -1;
	return (int)(p - m_pstr);
}

int cCString::Find(LPCTSTR pstrSub, int iPos /*= 0*/) const
{
	assert(!::IsBadStringPtr(pstrSub,-1));
	assert(iPos>=0 && iPos<=GetLength());
	if( iPos != 0 && (iPos < 0 || iPos > GetLength()) ) return -1;
	LPCTSTR p = _tcsstr(m_pstr + iPos, pstrSub);
	if( p == NULL ) return -1;
	return (int)(p - m_pstr);
}

int cCString::ReverseFind(TCHAR ch) const
{
	LPCTSTR p = _tcsrchr(m_pstr, ch);
	if( p == NULL ) return -1;
	return (int)(p - m_pstr);
}

int cCString::Replace(LPCTSTR pstrFrom, LPCTSTR pstrTo)
{
	cCString sTemp;
	int nCount = 0;
	int iPos = Find(pstrFrom);
	if( iPos < 0 ) return 0;
	int cchFrom = (int) _tcslen(pstrFrom);
	int cchTo = (int) _tcslen(pstrTo);
	while( iPos >= 0 ) {
		sTemp = Left(iPos);
		sTemp += pstrTo;
		sTemp += Mid(iPos + cchFrom);
		Assign(sTemp);
		iPos = Find(pstrFrom, iPos + cchTo);
		nCount++;
	}
	return nCount;
}

int cCString::Format(LPCTSTR pstrFormat, ...)
{
	va_list argList;
	va_start(argList, pstrFormat);
	
	int iRet = FormatV(pstrFormat,argList);

	va_end(argList);
	
	return iRet;
}

int cCString::SmallFormat(LPCTSTR pstrFormat, ...)
{
	cCString sFormat = pstrFormat;
	TCHAR szBuffer[64] = { 0 };
	va_list argList;
	va_start(argList, pstrFormat);
	int iRet = ::wvsprintf(szBuffer, sFormat, argList);
	va_end(argList);
	Assign(szBuffer);
	return iRet;
}

int __cdecl cCString::FormatV( LPCTSTR pstrFormat, va_list args )
{
	LPTSTR szSprintf = NULL;
	int nLen=0;
	nLen = ::_vsntprintf(NULL, 0, pstrFormat, args);
	szSprintf = (TCHAR*)malloc((nLen + 1) * sizeof(TCHAR));
	ZeroMemory(szSprintf, (nLen + 1) * sizeof(TCHAR));
	int iRet = ::_vsntprintf(szSprintf, nLen + 1, pstrFormat, args);

	Assign(szSprintf);
	free(szSprintf);

	return iRet;
}
