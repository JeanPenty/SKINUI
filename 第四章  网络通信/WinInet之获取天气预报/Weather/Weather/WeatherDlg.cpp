// WeatherDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Weather.h"
#include "WeatherDlg.h"
#include "RenderEngine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWeatherDlg �Ի���

LPCTSTR weatherTxt[] =
{
	TEXT("��"), TEXT("����"), TEXT("��"), TEXT("����"), TEXT("������"), TEXT("�����겢���б���"), TEXT("���ѩ"), TEXT("С��"), TEXT("����"), TEXT("����"), TEXT("����"), 
	TEXT("����"), TEXT("�ش���"), TEXT("��ѩ"), TEXT("Сѩ"), TEXT("��ѩ"), TEXT("��ѩ"), TEXT("��ѩ"), TEXT("��"), TEXT("����"), TEXT("ɳ����"), TEXT("С��-����"), 
	TEXT("����-����"), TEXT("����-����"), TEXT("����-����"), TEXT("����-�ش���"), TEXT("Сѩ-��ѩ"), TEXT("��ѩ-��ѩ"), TEXT("��ѩ-��ѩ"), TEXT("����"), 
	TEXT("��ɳ"), TEXT("ǿɳ����"), TEXT("�"), TEXT("�����"), TEXT("���ߴ�ѩ"), TEXT("����"), TEXT(""), TEXT(""), TEXT(""), TEXT(""), TEXT(""), TEXT(""), TEXT(""), 
	TEXT(""), TEXT(""), TEXT(""), TEXT(""), TEXT(""), TEXT(""), TEXT(""), TEXT(""), TEXT(""), TEXT(""), TEXT("��")
};

LPCTSTR windDir[] = 
{
	TEXT(""), TEXT("������"), TEXT("����"), TEXT("���Ϸ�"), TEXT("�Ϸ�"), TEXT("���Ϸ�"), TEXT("����"), TEXT("������"), TEXT("����"), TEXT("��ת����")
};

LPCTSTR windPower[] = 
{
	TEXT("΢��"), TEXT("3-4��"), TEXT("4-5��"), TEXT("5-6��"), TEXT("6-7��"), TEXT("7-8��"), TEXT("8-9��"), TEXT("9-10��"), TEXT("10-11��"), TEXT("11-12��")
};


//////////////////////////////////////////////////////////////////////////
CWeatherDlg::CWeatherDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWeatherDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pParseJson = NULL;
	memset(&m_Weather,-1,sizeof m_Weather);
	m_Weather.szCity[0]=0;
	m_bLoadFinished = false;
}

CWeatherDlg::~CWeatherDlg()
{
}


void CWeatherDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWeatherDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_SIZE()
	ON_WM_RBUTTONDOWN()
	ON_BN_CLICKED(4000,OnBnClickOption)
END_MESSAGE_MAP()


// CWeatherDlg ��Ϣ�������

BOOL CWeatherDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	m_pParseJson = CParseJson::GetInstance();

	m_pImageBack.LoadImage(AfxGetInstanceHandle(),TEXT("VIEW_BACK"));
	SetWindowPos(NULL,0,0,m_pImageBack.GetWidth(),m_pImageBack.GetHeight(),SWP_NOMOVE);

	//����͸������
	SetWindowLong(GetSafeHwnd(),GWL_EXSTYLE,GetWindowLong(m_hWnd,GWL_EXSTYLE)|WS_EX_LAYERED);
	UpdateLayered();

	//��ȡ�����ļ�--û������Ĭ��Ϊ������
	m_strProvince = AfxGetApp()->GetProfileString(TEXT("weather"),TEXT("Province"),TEXT("������"));
	m_strCity = AfxGetApp()->GetProfileString(TEXT("weather"),TEXT("city"),TEXT("������"));

	//�����߳��������ݲ���ѯ����
	StartThread();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CWeatherDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}


//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CWeatherDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

bool CWeatherDlg::OnEventThreadRun()
{
	HINSTANCE hInstance = AfxGetInstanceHandle();

	//��������ݺܴ�û�б���ÿ�β�ѯ��ʱ�򶼲���һ������������ֻ��ʼ��һ�ξͺ���
	static bool bInit = false;
	if( !bInit )
	{
		//������Դ
		HRSRC hResource=FindResource(hInstance,TEXT("JSONDATA"),TEXT("JSON"));
		if (hResource==NULL) return false;

		//��ȡ��Դ
		LPVOID pBuffer=LoadResource(hInstance,hResource);

		m_pParseJson->SetCityJsonData((LPCTSTR)pBuffer);

		bInit = true;
	}

	CString str = m_pParseJson->GetCode(m_strCity,m_strProvince);
	if ( str.GetLength() == 0 ) 
	{
		return false;
	}

	CString strURL,StrJson;
	strURL.Format(TEXT("http://weather.gtimg.cn/city/%s.js?ref=qqchannel"),str);
	
	m_pParseJson->SetWeatherJsonData( m_HttpWeather.GetHttpFile(strURL) );

	//��ȡ����
	CString strData;
	strData.Format(TEXT("WEATHER_%d"),GetValue(TEXT("sk_wt")));
	m_ImageWeather.DestroyImage();
	m_ImageWeather.LoadImage(AfxGetInstanceHandle(),strData);
	
	m_Weather.m_nHd = GetValue(TEXT("sk_hd"));
	m_Weather.m_nPs = GetValue(TEXT("sk_ps"));
	m_Weather.m_nTp = GetValue(TEXT("sk_tp"));
	m_Weather.m_nVb = GetValue(TEXT("sk_vb"));
	m_Weather.m_nWd = GetValue(TEXT("sk_wd"));
	m_Weather.m_nWp = GetValue(TEXT("sk_wp"));
	m_Weather.m_nWt = GetValue(TEXT("sk_wt"));

	_sntprintf_s(m_Weather.szCity,-1,CountArray(m_Weather.szCity),m_strCity);

	m_bLoadFinished = true;

	UpdateLayered();

	return false;
}


void CWeatherDlg::OnDestroy()
{
	__super::OnDestroy();

	ConcludeThread(0);
}

#define CHECK_IMAGE(p)	if( !p.IsNull() )

void CWeatherDlg::UpdateLayered()
{
	if(GetSafeHwnd() == NULL || !::IsWindow(GetSafeHwnd())) return;
	if ( m_pImageBack.IsNull() ) return;

	//��������
	CImage ImageBuffer;
	ImageBuffer.Create(m_pImageBack.GetWidth(),m_pImageBack.GetHeight(),32);

	//�滭����
	CImageDC ImageDC(ImageBuffer);
	CDC * pBufferDC=CDC::FromHandle(ImageDC);

	CSize szFont(0,0);

	//�滭����
	ASSERT(pBufferDC!=NULL);
	if (pBufferDC!=NULL) 
	{
		m_pImageBack.DrawImage(pBufferDC,0,0);
		
		if( !m_ImageWeather.IsNull() )
			m_ImageWeather.DrawImage(pBufferDC,0,0);

		if( m_bLoadFinished )
		{
			//����
			DrawText(pBufferDC,m_Weather.szCity,230,60,DT_LEFT,34,FW_BOLD);

			CString strTp;
			strTp.Format(TEXT("%d��"),m_Weather.m_nTp);
			DrawText(pBufferDC,strTp,305,90);

			DrawText(pBufferDC,weatherTxt[m_Weather.m_nWt],305,117);

			CString strWdp;
			strWdp.Format(TEXT("%s(%s)"),windDir[m_Weather.m_nWd],windPower[m_Weather.m_nWp]);
			DrawText(pBufferDC,strWdp,305,143);

			CString strPs;
			strPs.Format(TEXT("��ǰ��ѹ:%dhPa"),m_Weather.m_nPs);
			DrawText(pBufferDC,strPs,305,168);

			CString strVb;
			strVb.Format(TEXT("�ܼ���:%dKm"),m_Weather.m_nVb);
			DrawText(pBufferDC,strVb,305,196);

			CString strHd;
			strHd.Format(TEXT("���ʪ��:%d%%"),m_Weather.m_nHd);
			DrawText(pBufferDC,strHd,305,223);
		}
	}

	//��������
	BLENDFUNCTION BlendFunction;
	ZeroMemory(&BlendFunction,sizeof(BlendFunction));

	//���ò���
	BlendFunction.BlendOp=0;
	BlendFunction.BlendFlags=0;
	BlendFunction.AlphaFormat=AC_SRC_ALPHA;
	BlendFunction.SourceConstantAlpha=255;

	//���÷ֲ�
	CPoint ImagePoint(0,0);
	CClientDC ClientDC(this);
	UpdateLayeredWindow(&ClientDC,NULL,&CSize(m_pImageBack.GetWidth()+szFont.cx,m_pImageBack.GetHeight()),pBufferDC,&ImagePoint,0,&BlendFunction,2);
}

void CWeatherDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));

	__super::OnLButtonDown(nFlags, point);
}

void CWeatherDlg::DrawText( CDC*pDC,LPCTSTR lpszText,int nPosX,int nPosY,int nFlag,int nSize,int Weight,COLORREF colText )
{
	if ( lpszText == NULL ) return;

	HDC hDC = pDC->GetSafeHdc();

	CFont font;
	font.CreateFont(nSize,0,0,0,Weight,0,FALSE,0,0,0,0,0,0,TEXT("΢���ź�"));
	pDC->SelectObject( font );
	
	pDC->SetTextAlign(DT_CENTER);

	UINT nChar;

	CSize szText = pDC->GetTextExtent(lpszText);

	if ( (nFlag & DT_RIGHT) )
	{
		for(int n=0; n<_tcslen(lpszText); n++)
		{
			nChar=*(lpszText+n);

			if ( nChar >= 0xa0 )
			{
				nPosX -= szText.cy;
			}
			else
			{
				nPosX -= 2;
				nPosX -= szText.cy/2;
			}

		}
	}

	for(int n=0; n<_tcslen(lpszText); n++)
	{
		nChar=*(lpszText+n);

#if !defined(_UNICODE)
 		if(nChar >= 0xa0)
 		{
 			nChar = (((nChar<<8)&0xff00) | (*(lpszText+ ++n) & 0x00ff)); //++n
 		}
#endif

		GLYPHMETRICS gmm; 
		MAT2 mat; 
		memset(&mat,0,sizeof(mat)); 
		mat.eM11.value = 1; 
		mat.eM12.value = 0; 
		mat.eM21.value = 0; 
		mat.eM22.value = 1; 

		DWORD dwSize = GetGlyphOutline( hDC, nChar, GGO_BITMAP , &gmm, 0, 0, &mat );
		if( dwSize == -1 )
			return;

		BYTE* pBuffer = new BYTE[dwSize];
		if( GetGlyphOutline( hDC, nChar, GGO_BITMAP, &gmm, dwSize, pBuffer, &mat ) == GDI_ERROR ) 
		{
			delete pBuffer;
			return;
		}

		unsigned char *pData = (unsigned char*)pBuffer; 
		unsigned int cnt = gmm.gmBlackBoxX / szText.cy+ (gmm.gmCellIncX % szText.cy ? 1 : 0); 
		cnt *= 4; 

		int nCharPosY = nPosY;

		//˫�ֽ�
 		if ( nChar < 0xa0 )
 		{
 			nPosX += 2;
			nCharPosY += 1;
 		}

		for(unsigned int row = 0; row < gmm.gmBlackBoxY; row++) 
		{ 
			for(unsigned int col = 0; col < cnt;col++) 
			{ 
				for(unsigned int i = 0; i < 8; i++) 
				{ 
					if((*pData) & (0x80 >> i)) 
					{ 
						pDC->SetPixel(nPosX+(col * 8 + i),nCharPosY+row,colText); 
					} 
				}
				pData++; 
			} 
		}

		if ( nChar >= 0xa0 )
		{
			nPosX += szText.cy;
		}
		else
		{
			nPosX += szText.cy/2;
		}

		SafeDeleteArray(pBuffer);
	}
}

int CWeatherDlg::GetValue( CString StrData )
{
	if( m_pParseJson == NULL ) return -1;

	m_pParseJson->GetData(StrData);

	return _tcstol(StrData,0,10);
}

void CWeatherDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	CMenu PopMenu;

	//�����˵�
	PopMenu.CreatePopupMenu();
	PopMenu.AppendMenu(0,4000,TEXT("��������"));
	PopMenu.AppendMenu(0,1,TEXT("�˳�"));

	//��ʾ�˵�
	ClientToScreen(&point);
	PopMenu.TrackPopupMenu(TPM_RIGHTBUTTON,point.x,point.y,this);
	PopMenu.DestroyMenu();

	__super::OnRButtonDown(nFlags, point);
}

void CWeatherDlg::OnBnClickOption()
{
	if ( m_OptionDlg.GetSafeHwnd() == NULL )
	{
		COptionDlg OptionDlg;
		
		if( OptionDlg.DoModal() == IDOK )
		{
			m_strCity = OptionDlg.m_strCity;
			m_strProvince = OptionDlg.m_strProvince;

			//д�������ļ�
			AfxGetApp()->WriteProfileString(TEXT("weather"),TEXT("Province"),m_strProvince);
			AfxGetApp()->WriteProfileString(TEXT("weather"),TEXT("city"),m_strCity);

			if ( IsRuning() ) ConcludeThread(0);
				
			StartThread();
		}
	}
}
