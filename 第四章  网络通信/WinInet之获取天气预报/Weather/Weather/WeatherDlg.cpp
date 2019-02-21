// WeatherDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Weather.h"
#include "WeatherDlg.h"
#include "RenderEngine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWeatherDlg 对话框

LPCTSTR weatherTxt[] =
{
	TEXT("晴"), TEXT("多云"), TEXT("阴"), TEXT("阵雨"), TEXT("雷阵雨"), TEXT("雷阵雨并伴有冰雹"), TEXT("雨夹雪"), TEXT("小雨"), TEXT("中雨"), TEXT("大雨"), TEXT("暴雨"), 
	TEXT("大暴雨"), TEXT("特大暴雨"), TEXT("阵雪"), TEXT("小雪"), TEXT("中雪"), TEXT("大雪"), TEXT("暴雪"), TEXT("雾"), TEXT("冻雨"), TEXT("沙尘暴"), TEXT("小雨-中雨"), 
	TEXT("中雨-大雨"), TEXT("大雨-暴雨"), TEXT("暴雨-大暴雨"), TEXT("大暴雨-特大暴雨"), TEXT("小雪-中雪"), TEXT("中雪-大雪"), TEXT("大雪-暴雪"), TEXT("浮尘"), 
	TEXT("扬沙"), TEXT("强沙尘暴"), TEXT("飑"), TEXT("龙卷风"), TEXT("弱高吹雪"), TEXT("轻雾"), TEXT(""), TEXT(""), TEXT(""), TEXT(""), TEXT(""), TEXT(""), TEXT(""), 
	TEXT(""), TEXT(""), TEXT(""), TEXT(""), TEXT(""), TEXT(""), TEXT(""), TEXT(""), TEXT(""), TEXT(""), TEXT("霾")
};

LPCTSTR windDir[] = 
{
	TEXT(""), TEXT("东北风"), TEXT("东风"), TEXT("东南风"), TEXT("南风"), TEXT("西南风"), TEXT("西风"), TEXT("西北风"), TEXT("北风"), TEXT("旋转不定")
};

LPCTSTR windPower[] = 
{
	TEXT("微风"), TEXT("3-4级"), TEXT("4-5级"), TEXT("5-6级"), TEXT("6-7级"), TEXT("7-8级"), TEXT("8-9级"), TEXT("9-10级"), TEXT("10-11级"), TEXT("11-12级")
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


// CWeatherDlg 消息处理程序

BOOL CWeatherDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	m_pParseJson = CParseJson::GetInstance();

	m_pImageBack.LoadImage(AfxGetInstanceHandle(),TEXT("VIEW_BACK"));
	SetWindowPos(NULL,0,0,m_pImageBack.GetWidth(),m_pImageBack.GetHeight(),SWP_NOMOVE);

	//设置透明处理
	SetWindowLong(GetSafeHwnd(),GWL_EXSTYLE,GetWindowLong(m_hWnd,GWL_EXSTYLE)|WS_EX_LAYERED);
	UpdateLayered();

	//读取配置文件--没有数据默认为北京市
	m_strProvince = AfxGetApp()->GetProfileString(TEXT("weather"),TEXT("Province"),TEXT("北京市"));
	m_strCity = AfxGetApp()->GetProfileString(TEXT("weather"),TEXT("city"),TEXT("北京市"));

	//开启线程设置数据并查询天气
	StartThread();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CWeatherDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}


//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CWeatherDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

bool CWeatherDlg::OnEventThreadRun()
{
	HINSTANCE hInstance = AfxGetInstanceHandle();

	//这里的数据很大，没有必须每次查询的时候都插入一次容器，所以只初始化一次就好了
	static bool bInit = false;
	if( !bInit )
	{
		//查找资源
		HRSRC hResource=FindResource(hInstance,TEXT("JSONDATA"),TEXT("JSON"));
		if (hResource==NULL) return false;

		//读取资源
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

	//获取天气
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

	//创建缓冲
	CImage ImageBuffer;
	ImageBuffer.Create(m_pImageBack.GetWidth(),m_pImageBack.GetHeight(),32);

	//绘画界面
	CImageDC ImageDC(ImageBuffer);
	CDC * pBufferDC=CDC::FromHandle(ImageDC);

	CSize szFont(0,0);

	//绘画界面
	ASSERT(pBufferDC!=NULL);
	if (pBufferDC!=NULL) 
	{
		m_pImageBack.DrawImage(pBufferDC,0,0);
		
		if( !m_ImageWeather.IsNull() )
			m_ImageWeather.DrawImage(pBufferDC,0,0);

		if( m_bLoadFinished )
		{
			//城市
			DrawText(pBufferDC,m_Weather.szCity,230,60,DT_LEFT,34,FW_BOLD);

			CString strTp;
			strTp.Format(TEXT("%d℃"),m_Weather.m_nTp);
			DrawText(pBufferDC,strTp,305,90);

			DrawText(pBufferDC,weatherTxt[m_Weather.m_nWt],305,117);

			CString strWdp;
			strWdp.Format(TEXT("%s(%s)"),windDir[m_Weather.m_nWd],windPower[m_Weather.m_nWp]);
			DrawText(pBufferDC,strWdp,305,143);

			CString strPs;
			strPs.Format(TEXT("当前气压:%dhPa"),m_Weather.m_nPs);
			DrawText(pBufferDC,strPs,305,168);

			CString strVb;
			strVb.Format(TEXT("能见度:%dKm"),m_Weather.m_nVb);
			DrawText(pBufferDC,strVb,305,196);

			CString strHd;
			strHd.Format(TEXT("相对湿度:%d%%"),m_Weather.m_nHd);
			DrawText(pBufferDC,strHd,305,223);
		}
	}

	//变量定义
	BLENDFUNCTION BlendFunction;
	ZeroMemory(&BlendFunction,sizeof(BlendFunction));

	//设置参数
	BlendFunction.BlendOp=0;
	BlendFunction.BlendFlags=0;
	BlendFunction.AlphaFormat=AC_SRC_ALPHA;
	BlendFunction.SourceConstantAlpha=255;

	//设置分层
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
	font.CreateFont(nSize,0,0,0,Weight,0,FALSE,0,0,0,0,0,0,TEXT("微软雅黑"));
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

		//双字节
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

	//建立菜单
	PopMenu.CreatePopupMenu();
	PopMenu.AppendMenu(0,4000,TEXT("城市设置"));
	PopMenu.AppendMenu(0,1,TEXT("退出"));

	//显示菜单
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

			//写入配置文件
			AfxGetApp()->WriteProfileString(TEXT("weather"),TEXT("Province"),m_strProvince);
			AfxGetApp()->WriteProfileString(TEXT("weather"),TEXT("city"),m_strCity);

			if ( IsRuning() ) ConcludeThread(0);
				
			StartThread();
		}
	}
}
