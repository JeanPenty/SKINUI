// DesktoplyricDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DesktoplyricDlg.h"
#include "RenderEngine.h"
#include "resource.h"
#include <locale.h>

#pragma warning(disable:4244)
#pragma warning(disable:4018)

#define IDI_SHOWLYRIC			1
// CDesktoplyricDlg 对话框

IMPLEMENT_DYNAMIC(CDesktoplyricDlg, CDialog)

CDesktoplyricDlg::CDesktoplyricDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_LYRISDLG, pParent)
{
	m_hMemBmp=NULL;
	m_pBits=NULL;
	m_dwSize=0;
	m_dwEffWidth=0;
	m_szText[0]=0;
	m_Arraylyric.clear();
	m_nFontSize = 40;
}

CDesktoplyricDlg::~CDesktoplyricDlg()
{
	if(m_hMemBmp) ::DeleteObject(m_hMemBmp);
}

void CDesktoplyricDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDesktoplyricDlg, CDialog)
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// CDesktoplyricDlg 消息处理程序

BOOL CDesktoplyricDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//取消任务栏显示
	ModifyStyleEx(WS_EX_APPWINDOW,WS_EX_TOOLWINDOW);

	//设置透明处理
	SetWindowLong(GetSafeHwnd(),GWL_EXSTYLE,GetWindowLong(m_hWnd,GWL_EXSTYLE)|WS_EX_LAYERED);
	UpdateLayered();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDesktoplyricDlg::SetLyric( CString lpszText )
{
	_tcscpy_s(m_szText,_TRUNCATE,lpszText);
	memset(m_pBits,0,m_dwSize);
	UpdateLayered();
}

void CDesktoplyricDlg::UpdateLayered()
{
	if(GetSafeHwnd() == NULL || !::IsWindow(GetSafeHwnd())) return;

	CClientDC dc(this);
	CDC dcMemory;
	if(dcMemory.CreateCompatibleDC(&dc))
	{
		CRect rcClient;
		GetClientRect(&rcClient);
		DrawTextString(m_szText,&rcClient,RGB(100,50,50),RGB(202,100,200),m_nFontSize,DT_CENTER,NULL);
		rcClient.OffsetRect(1,1);
		DrawTextShadow(m_szText,&rcClient,RGB(10,10,10),m_nFontSize,DT_CENTER,NULL);

		if(m_hMemBmp)
		{
			dcMemory.SelectObject(m_hMemBmp);

			CRect rcWnd;
			GetWindowRect(&rcWnd);
			POINT ptWinPos={rcWnd.left,rcWnd.top};
			SIZE sizeWindow={rcWnd.Width(),rcWnd.Height()};
			POINT ptSrc={0,0};

			BLENDFUNCTION Blend={AC_SRC_OVER,0,255,AC_SRC_ALPHA};

			CDC*pDC = GetDC();
			
			UpdateLayeredWindow(pDC,&ptWinPos,&sizeWindow,&dcMemory,&ptSrc,0,&Blend,2);

			ReleaseDC(pDC);
		}
	}
}

void CDesktoplyricDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	if(cx!=0 && cy!=0)
	{
		if(m_hMemBmp)
			::DeleteObject(m_hMemBmp);
		BITMAPINFO  bmi;
		memset(&bmi, 0, sizeof(bmi));
		bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmi.bmiHeader.biWidth=cx;
		bmi.bmiHeader.biHeight=cy;
		bmi.bmiHeader.biPlanes=1;
		bmi.bmiHeader.biBitCount=32;
		bmi.bmiHeader.biCompression=BI_RGB;

		m_hMemBmp = CreateDIBSection(NULL, &bmi, DIB_RGB_COLORS, (void**)&m_pBits, 0, 0);
		if(m_hMemBmp && m_pBits)
		{
			m_dwSize=bmi.bmiHeader.biWidth * bmi.bmiHeader.biHeight * 4;
			m_dwEffWidth = ((((32 * bmi.bmiHeader.biWidth) + 31) / 32) * 4);
		}
		UpdateLayered();
	}
}

void CDesktoplyricDlg::DrawTextString(LPTSTR lpszText,CRect rc,COLORREF clr1,COLORREF clr2,UINT nFontSize/* =14 */,DWORD dwFlag/* =DT_CENTER|DT_VCENTER|DT_SINGLELINE */,CFont* pFont/* =NULL */)
{
	ASSERT(lpszText!=NULL);
	if(rc.IsRectEmpty()) return;

	HDC hdc=::GetDC(NULL);

	CDC Mdc;
	CRect rcClient;
	GetClientRect(&rcClient);

	if(Mdc.CreateCompatibleDC(CDC::FromHandle(hdc)))
	{
		HFONT hfont=NULL;
		if(pFont==NULL)
		{
			LOGFONT lf={0};
			::GetObject(::GetStockObject(DEFAULT_GUI_FONT),sizeof(LOGFONT),&lf);
			lf.lfWeight=FW_BOLD;
			lf.lfHeight = nFontSize;
			lstrcpyn(lf.lfFaceName,_T("宋体"),_countof(lf.lfFaceName));	
			hfont=::CreateFontIndirect(&lf);
		}
		else
			hfont=(HFONT)pFont->m_hObject;

		Mdc.SelectObject(hfont);	

		MAT2 mat2 = {{0,1}, {0,0}, {0,0}, {0,1}};
		GLYPHMETRICS gm={0};

		bool bHaveOffsety=false;
		short cyOffset;

		SIZE size=CRenderEngine::GetDrawSize(Mdc,lpszText,dwFlag,bHaveOffsety,cyOffset);

		int left=rc.left;
		int top=rc.top;

		BYTE nTransparent,a1;

		if(dwFlag & DT_CENTER)
		{
			left += ((rc.Width() - size.cx)>>1);
		}
		if(dwFlag & DT_VCENTER)
		{
			top += ((rc.Height() - size.cy)>>1);
		}

		CRect rc(0,0,size.cx,size.cy);
		rc.OffsetRect(left,top);

		BYTE tr,tg,tb;
		float f,f1;
		long slen=_tcslen(lpszText);
		UINT nChar;
		DWORD dwLen;
		BYTE* pBytes;
		for(int n=0; n<slen; n++)
		{
			if(left > rc.right) break;
		
			nChar=*(lpszText+n);
			//非英文
			if(nChar >= 0xa0)
			{
				nChar = (((nChar<<8)&0xff00) | (*(lpszText+ ++n) & 0x00ff)); //++n
			}
			dwLen=GetGlyphOutline(Mdc,nChar,GGO_GRAY8_BITMAP,&gm,0,NULL,&mat2);
			if(dwLen != GDI_ERROR)
			{
				pBytes=new BYTE[dwLen];
				if(pBytes)
				{
					dwLen=GetGlyphOutline(Mdc,nChar,GGO_GRAY8_BITMAP,&gm,dwLen,pBytes,&mat2);
					if(dwLen!=GDI_ERROR)
					{
						//对齐字符输出
						if(CRenderEngine::IsDoubleByteChar(nChar))
						{
							if(_istpunct(nChar) && nChar!=_T('—')) //标点符号，中文——
							{
								top=rc.bottom - gm.gmBlackBoxY - (bHaveOffsety && CRenderEngine::IsYOffset(nChar) ? cyOffset : 0);
							}
							else
							{//居中显示
								top=(rc.bottom + rc.top - gm.gmBlackBoxY)>>1;
							}
						}
						else if(nChar == _T('-'))
							top=(rc.bottom + rc.top - gm.gmBlackBoxY)>>1; //居中显示
						else
							top=rc.bottom - gm.gmBlackBoxY - (bHaveOffsety && CRenderEngine::IsYOffset(nChar) ? cyOffset : 0);

						int nByteCount = ((8 * gm.gmBlackBoxX +31) >> 5) << 2;

						//填充数据

						float fr=(float)(GetRValue(clr2)-GetRValue(clr1))/((float)rc.Height()/2+1);
						float fg=(float)(GetGValue(clr2)-GetGValue(clr1))/((float)rc.Height()/2+1);
						float fb=(float)(GetBValue(clr2)-GetBValue(clr1))/((float)rc.Height()/2+1);

						BYTE* dst,*src;
						if(nChar != _T(' '))
						{
							int i=top-rc.top+1;
							if(i > rc.Height()/2)
							{
								i-=rc.Height()/2;
								tr=GetRValue(clr2) - i * fr;
								tg=GetGValue(clr2) - i * fg;
								tb=GetBValue(clr2) - i * fb;
							}
							else
							{
								tr=i * fr + GetRValue(clr1);
								tg=i * fg + GetGValue(clr1);
								tb=i * fb + GetBValue(clr1);
							}

							for(long y=0; y<gm.gmBlackBoxY; y++)
							{
								dst=m_pBits + (rcClient.bottom - top - y - 1)*m_dwEffWidth + left*4;
								src= pBytes + y * nByteCount;
								if(top + y + 2 - rc.top> rc.Height()/2)
								{
									tr-=fr;
									tg-=fg;
									tb-=fb;
								}
								else
								{
									tr+=fr;
									tg+=fg;
									tb+=fb;
								}

								for(long x=0; x<gm.gmBlackBoxX; x++)
								{
									f=(float)(*src)/64;
									f1=1.0-f;
									a1=*(dst+3);
									nTransparent=(BYTE)(~a1);
									*dst++=((BYTE)(tb*f + (*dst)*f1)*nTransparent + a1*(*dst))>>8;
									*dst++=((BYTE)(tg*f + (*dst)*f1)*nTransparent + a1*(*dst))>>8;
									*dst++=((BYTE)(tr*f + (*dst)*f1)*nTransparent + a1*(*dst))>>8;
									*dst++=((BYTE)(255*f)*nTransparent + a1*(*dst))>>8;
									src++;
								}
							}
						}
						left+=gm.gmBlackBoxX + CRenderEngine::m_cxSpacing;
						if(nChar == _T(' '))
							left+=CRenderEngine::m_cwBlank;
					}
					delete[]pBytes;
				}
			}
		}
		if(pFont==NULL)
			::DeleteObject(hfont);
	}
	VERIFY(::ReleaseDC(NULL,hdc)==1);
}

void CDesktoplyricDlg::DrawTextShadow(LPTSTR lpszText,CRect rc,COLORREF clrText,UINT nFontSize/* =14 */,DWORD dwFlag/* =DT_CENTER|DT_VCENTER|DT_SINGLELINE */,CFont* pFont/* =NULL */)
{
	ASSERT(lpszText!=NULL);
	if(rc.IsRectEmpty()) return;

	HDC hdc=::GetDC(NULL);

	CRect rcClient;
	GetClientRect(&rcClient);

	CDC Mdc;
	if(Mdc.CreateCompatibleDC(CDC::FromHandle(hdc)))
	{
		HFONT hfont=NULL;
		if(pFont==NULL)
		{
			LOGFONT lf={0};
			::GetObject(::GetStockObject(DEFAULT_GUI_FONT),sizeof(LOGFONT),&lf);
			lf.lfWeight=FW_BOLD;
			lf.lfHeight = nFontSize;
			lstrcpyn(lf.lfFaceName,_T("宋体"),_countof(lf.lfFaceName));
			hfont=::CreateFontIndirect(&lf);
		}
		else
			hfont=(HFONT)pFont->m_hObject;

		Mdc.SelectObject(hfont);	

		BYTE nTransparent,a1;

		MAT2 mat2 = {{0,1}, {0,0}, {0,0}, {0,1}};
		GLYPHMETRICS gm={0};

		bool bHaveOffsety=false;
		short cyOffset;

		SIZE size=CRenderEngine::GetDrawSize(Mdc,lpszText,dwFlag,bHaveOffsety,cyOffset);

		int left=rc.left;
		int top=rc.top;

		if(dwFlag & DT_CENTER)
		{
			left += ((rc.Width() - size.cx)>>1);
		}
		if(dwFlag & DT_VCENTER)
		{
			top += ((rc.Height() - size.cy)>>1);
		}

		CRect rc(0,0,size.cx,size.cy);
		rc.OffsetRect(left,top);

		BYTE tr=GetRValue(clrText),tg=GetGValue(clrText),tb=GetBValue(clrText);
		float f,f1;
		long slen=_tcslen(lpszText);
		UINT nChar;
		DWORD dwLen;
		BYTE* pBytes;
	
		for(int n=0; n<slen; n++)
		{
			if(left > rc.right) break;

			nChar=*(lpszText+n);
			if(nChar >= 0xa0)
			{//非英文
				nChar = (((nChar<<8)&0xff00) | (*(lpszText+ ++n) & 0x00ff)); //++n
			}
			dwLen=GetGlyphOutline(Mdc,nChar,GGO_GRAY8_BITMAP,&gm,0,NULL,&mat2);
			if(dwLen != GDI_ERROR)
			{
				pBytes=new BYTE[dwLen];
				if(pBytes)
				{
					dwLen=GetGlyphOutline(Mdc,nChar,GGO_GRAY8_BITMAP,&gm,dwLen,pBytes,&mat2);
					if(dwLen!=GDI_ERROR)
					{
						//对齐字符输出
						if(CRenderEngine::IsDoubleByteChar(nChar))
						{
							if(_istpunct(nChar) && nChar!=_T('—')) //标点符号，中文——
							{
								top=rc.bottom - gm.gmBlackBoxY - (bHaveOffsety && CRenderEngine::IsYOffset(nChar) ? cyOffset : 0);
							}
							else
							{
								//居中显示
								top=(rc.bottom + rc.top - gm.gmBlackBoxY)>>1;
							}
						}
						else if(nChar == _T('-'))
							top=(rc.bottom + rc.top - gm.gmBlackBoxY)>>1; //居中显示
						else
							top=rc.bottom - gm.gmBlackBoxY - (bHaveOffsety && CRenderEngine::IsYOffset(nChar) ? cyOffset : 0);

						int nByteCount = ((8 * gm.gmBlackBoxX +31) >> 5) << 2;
						//填充数据
						BYTE* dst,*src;
						if(nChar != _T(' '))
						{
							for(long y=0; y<gm.gmBlackBoxY; y++)
							{
								dst=m_pBits + (rcClient.bottom - top - y - 1)*m_dwEffWidth + left*4;
								src= pBytes + y * nByteCount;
								for(long x=0; x<gm.gmBlackBoxX; x++)
								{
									f=(float)(*src)/64;
									f1=1.0-f;

									a1=*(dst+3);
									nTransparent=(BYTE)(~a1);
									*dst++=((BYTE)(tb*f + (*dst)*f1)*nTransparent + a1*(*dst))>>8;
									*dst++=((BYTE)(tg*f + (*dst)*f1)*nTransparent + a1*(*dst))>>8;
									*dst++=((BYTE)(tr*f + (*dst)*f1)*nTransparent + a1*(*dst))>>8;
									*dst++=((BYTE)(255*f)*nTransparent + a1*(*dst))>>8;

									src++;
								}
							}
						}
						left+=gm.gmBlackBoxX + CRenderEngine::m_cxSpacing;
						if(nChar == _T(' '))
							left+=CRenderEngine::m_cwBlank;
					}
					delete[]pBytes;
				}
			}
		}
		if(pFont==NULL)
			::DeleteObject(hfont);
	}
	VERIFY(::ReleaseDC(NULL,hdc)==1);
}


void CDesktoplyricDlg::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent == IDI_SHOWLYRIC)
	{
		static int nIndex=0;
		if(nIndex>=m_Arraylyric.size()) nIndex=0;
		SetLyric(m_Arraylyric[nIndex]);
		nIndex++;
	}

	CDialog::OnTimer(nIDEvent);
}

void CDesktoplyricDlg::OpenLyric(LPCTSTR lpPath)
{
	m_Arraylyric.clear();

#ifdef _UNICODE
	char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) ); 
	setlocale( LC_CTYPE, "chs" );
#endif

	CStdioFile file;
	file.Open(lpPath,CFile::modeRead);

	CString StrLyric;
	while ( file.ReadString(StrLyric) )
	{
		if((StrLyric.GetLength()>=10) && (StrLyric[0] =='[') && (StrLyric[9] ==']'))
			StrLyric = StrLyric.Right(StrLyric.GetLength()-10);

		m_Arraylyric.push_back(StrLyric);
	}

	file.Close();

#ifdef _UNICODE
	setlocale( LC_CTYPE, old_locale ); 
	free( old_locale ); 
#endif

	//测试
	if( m_Arraylyric.size() != 0 )
		SetTimer(IDI_SHOWLYRIC,2000,NULL);
}

void CDesktoplyricDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));

	CDialog::OnLButtonDown(nFlags, point);
}
