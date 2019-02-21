// GMusicDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GMusic.h"
#include "GMusicDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define IDC_WNDOPTION				3003
#define IDC_WNDSKIN					3004
#define IDC_LIST					3005

#define IDC_MUSIC_ADD				3010
#define IDC_MUSIC_DEL				3011

#define IDC_MUSIC_PREV				3012
#define IDC_MUSIC_PLAY				3113
#define IDC_MUSIC_PAUSE				3114
#define IDC_MUSIC_LAST				3115
#define IDC_MUSIC_MUTE				3116


#define IDM_MENU_ADD				4000
#define IDM_MENU_ADDBROWER			4001
#define IDM_MENU_ADDURL				4002

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CBaseDialog
{
public:
	CAboutDlg();

	CSkinButton			m_btLink;
// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void DrawView(CDC*pDC,int nWidth,int nHeight);
// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickMainWeb()
	{
		OpenLink(TEXT("http://www.gymsaga.com"));
	}
};

CAboutDlg::CAboutDlg() : CBaseDialog(CAboutDlg::IDD,NULL,en_Wnd_CloseBox)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CBaseDialog::DoDataExchange(pDX);
}

BOOL CAboutDlg::OnInitDialog()
{
	CBaseDialog::OnInitDialog();

	CRect rcClient;
	GetClientRect(&rcClient);

	RenderEngine->AddFont(TEXT("微软雅黑"),15,false,true,true);
	m_btLink.Create(TEXT("跟我一些学MFC，点击访问博客主页"),WS_VISIBLE|WS_CHILD,CRect(20,50,rcClient.Width()-10,70),this,5000);
	m_btLink.SetParentBack(GetBackDC());
	m_btLink.SetCtrlFont(RenderEngine->GetEndFont());

	m_btLink.m_colNormalText = RGB(255,0,0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CAboutDlg::DrawView(CDC*pDC,int nWidth,int nHeight)
{
	CRect rcString(30,100,nWidth-30,nHeight);

	pDC->SelectObject(RenderEngine->GetDeaultFont());
	pDC->DrawText(TEXT("本代码仅限学习交流使用，如果对代码有任何的问题疑惑，请与我联系！"),&rcString,DT_LEFT|DT_VCENTER|DT_WORDBREAK|DT_NOCLIP);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CBaseDialog)
	ON_BN_CLICKED(5000,OnBnClickMainWeb)
END_MESSAGE_MAP()


// CGMusicDlg 对话框

CGMusicDlg::CGMusicDlg(CWnd* pParent /*=NULL*/)
	: CBaseDialog(CGMusicDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pImageDefaultRes = NULL;
	m_pBassMusic = NULL;
	m_hStream = 0;
}

void CGMusicDlg::DoDataExchange(CDataExchange* pDX)
{
	CBaseDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGMusicDlg, CBaseDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_SIZE()
	ON_LBN_DBLCLK(IDC_LIST, &CGMusicDlg::OnLbnDblclkList1)
	ON_BN_CLICKED(IDC_MUSIC_ADD,OnBnClickedMusicAdd)
	ON_BN_CLICKED(IDC_MUSIC_DEL,OnBnClickedMusicDel)
	ON_BN_CLICKED(IDC_MUSIC_PREV,OnBnClickedMusicPrev)
	ON_BN_CLICKED(IDC_MUSIC_PLAY,OnBnClickedMusicPlay)
	ON_BN_CLICKED(IDC_MUSIC_PAUSE,OnBnClickedMusicPause)
	ON_BN_CLICKED(IDC_MUSIC_MUTE,OnBnClickedMusicMute)
	ON_BN_CLICKED(IDC_MUSIC_LAST,OnBnClickedMusicLast)
	ON_BN_CLICKED(IDC_WNDSKIN,OnBnClickedSkin)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_HSCROLL()
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONDOWN()
	ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()


// CGMusicDlg 消息处理程序

BOOL CGMusicDlg::OnInitDialog()
{
	CBaseDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	//网络歌曲播放测试
	//if (BASS_Init(-1, 44100, 0, GetSafeHwnd(), NULL) == TRUE)
	//{
	//	HSTREAM hStream;
	//	hStream = BASS_StreamCreateURL("http://zhangmenshiting.baidu.com/data2/music/90350716/8930817375600320.mp3?xcode=771953d3b41695309061c1b0bc2631c2ccef84e1bc4b1406",0,BASS_SAMPLE_LOOP|BASS_SAMPLE_FX|BASS_STREAM_PRESCAN,NULL,NULL );

	//	//开始播放
	//	BASS_ChannelPlay(hStream, TRUE);
	//}

	//初始化声音组件
	m_pBassMusic = CBassMusicEngine::GetInstance();
	if ( m_pBassMusic == NULL )
	{
		if ( AfxMessageBox(TEXT("声音引擎初始化失败")) == IDOK )
		{
			PostQuitMessage(0);
			return FALSE;
		}
	}

	m_pBassMusic->Init(GetSafeHwnd(),this);

	//创建皮肤
	HDC hParentDC = GetBackDC();

	CRect rcClient;
	GetClientRect(&rcClient);

	m_btOption.Create(NULL,WS_VISIBLE|WS_CHILD,CRect(rcClient.Width()-100,25,0,0),this,IDM_ABOUTBOX);
	m_btOption.SetBackImage(TEXT("Res\\Button\\btn_option_normal.png"),TEXT("Res\\Button\\btn_option_highlight.png"),TEXT("Res\\Button\\btn_option_down.png"),TEXT("Res\\Button\\btn_option_normal.png"));
	m_btOption.SetButtonType(en_PushButton);
	m_btOption.SetParentBack(hParentDC);
	m_btOption.SetSize(18,16);

	m_btSkin.Create(NULL,WS_VISIBLE|WS_CHILD,CRect(rcClient.Width()-125,25,0,0),this,IDC_WNDSKIN);
	m_btSkin.SetBackImage(TEXT("Res\\Button\\btn_skin_normal.png"),TEXT("Res\\Button\\btn_skin_highlight.png"),TEXT("Res\\Button\\btn_skin_down.png"),TEXT("Res\\Button\\btn_skin_normal.png"));
	m_btSkin.SetButtonType(en_PushButton);
	m_btSkin.SetParentBack(hParentDC);
	m_btSkin.SetSize(20,18);

	m_WebPublicize.Create(NULL,NULL,WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN,CRect(1,64,rcClient.Width()-310,rcClient.Height()-70),this,0);
	m_WebPublicize.Navigate(TEXT("http://qianqianmini.baidu.com/static/recommend/recommend.html"));

	RenderEngine->AddFont(TEXT("微软雅黑"),12);
	m_ListMusic.Create(LBS_MULTIPLESEL | LBS_OWNERDRAWFIXED | LBS_HASSTRINGS | LBS_NOINTEGRALHEIGHT | WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN,CRect(rcClient.Width()-305,64,rcClient.Width()-2,rcClient.Height()-105),this,IDC_LIST);
	m_ListMusic.SetParentBack(hParentDC);
 	m_ListMusic.SetSelectImage(TEXT("Res\\List\\list_select.png"));
 	m_ListMusic.SetPlayedImage(TEXT("Res\\List\\list_played.png"));
 	m_ListMusic.SetHovenImage(TEXT("Res\\List\\list_highlight.png"));
	m_ListMusic.m_colNormalText = RGB(53,53,53);
	m_ListMusic.m_colSelectText = RGB(229,254,242);
	m_ListMusic.SetItemHeight(-1,32);
	m_ListMusic.SetCtrlFont(RenderEngine->GetEndFont());

	m_btPrev.Create(NULL,WS_VISIBLE|WS_CHILD,CRect(rcClient.Width()/2-80,rcClient.Height()-53,0,0),this,IDC_MUSIC_PREV);
	m_btPrev.SetBackImage(TEXT("Res\\Music\\prev_normal.png"),TEXT("Res\\Music\\prev_highlight.png"),TEXT("Res\\Music\\prev_down.png"),TEXT("Res\\Music\\prev_normal.png"));
	m_btPrev.SetButtonType(en_PushButton);
	m_btPrev.SetParentBack(hParentDC);
	m_btPrev.SetSize(47,47);

	m_btOpen.Create(NULL,WS_VISIBLE|WS_CHILD,CRect(rcClient.Width()/2-27,rcClient.Height()-57,0,0),this,IDC_MUSIC_PLAY);
	m_btOpen.SetBackImage(TEXT("Res\\Music\\open_normal.png"),TEXT("Res\\Music\\open_highlight.png"),TEXT("Res\\Music\\open_down.png"),TEXT("Res\\Music\\open_normal.png"));
	m_btOpen.SetButtonType(en_PushButton);
	m_btOpen.SetParentBack(hParentDC);
	m_btOpen.SetSize(54,54);

	m_btPause.Create(NULL,WS_CHILD,CRect(rcClient.Width()/2-27,rcClient.Height()-57,0,0),this,IDC_MUSIC_PAUSE);
	m_btPause.SetBackImage(TEXT("Res\\Music\\pause_normal.png"),TEXT("Res\\Music\\pause_highlight.png"),TEXT("Res\\Music\\pause_down.png"),TEXT("Res\\Music\\pause_normal.png"));
	m_btPause.SetButtonType(en_PushButton);
	m_btPause.SetParentBack(hParentDC);
	m_btPause.SetSize(54,54);

	m_btLast.Create(NULL,WS_VISIBLE|WS_CHILD,CRect(rcClient.Width()/2+40,rcClient.Height()-53,0,0),this,IDC_MUSIC_LAST);
	m_btLast.SetBackImage(TEXT("Res\\Music\\last_normal.png"),TEXT("Res\\Music\\last_highlight.png"),TEXT("Res\\Music\\last_down.png"),TEXT("Res\\Music\\last_normal.png"));
	m_btLast.SetButtonType(en_PushButton);
	m_btLast.SetParentBack(hParentDC);
	m_btLast.SetSize(47,47);

	m_btMute.Create(NULL,WS_VISIBLE|WS_CHILD,CRect(rcClient.Width()/2+100,rcClient.Height()-40,0,0),this,IDC_MUSIC_MUTE);
	m_btMute.SetBackImage(TEXT("Res\\Mute\\mute1_normal.png"),TEXT("Res\\Mute\\mute1_highlight.png"),TEXT("Res\\Mute\\mute1_down.png"),TEXT("Res\\Mute\\mute1_normal.png"));
	m_btMute.SetButtonType(en_PushButton);
	m_btMute.SetParentBack(hParentDC);
	m_btMute.SetSize(25,25);

	m_scVolume.Create(WS_CHILD|WS_VISIBLE|TBS_BOTH|TBS_NOTICKS,CRect(rcClient.Width()/2+130,rcClient.Height()-30,rcClient.Width()/2+190,rcClient.Height()-24),this,0);
	m_scVolume.SetParentBack(hParentDC);
	m_scVolume.SetBackImage(TEXT("Res\\Music\\sound_back.png"),false);
	m_scVolume.SetTraceImage(TEXT("Res\\Music\\sound_Trace.png"));
	m_scVolume.SetThumImage(TEXT("Res\\Music\\mute_thumb.png"));
	m_scVolume.SetRange(0,100);
	int n = m_pBassMusic->GetVolume();
	m_scVolume.SetPos(m_pBassMusic->GetVolume());
	UpdateVolume();

	RenderEngine->AddFont(TEXT("微软雅黑"),14);
	m_btAdd.Create(TEXT(" 添加"),WS_VISIBLE|WS_CHILD,CRect(rcClient.Width()-144,rcClient.Height()-92,0,0),this,IDC_MUSIC_ADD);
	m_btAdd.SetBackImage(NULL,TEXT("Res\\Music\\allbtn_highlight.png"),TEXT("Res\\Music\\allbtn_down.png"),NULL);
	m_btAdd.SetIconImage(TEXT("Res\\Music\\icon_add.png"));
	m_btAdd.SetButtonType(en_IconButton);
	m_btAdd.SetParentBack(hParentDC);
	m_btAdd.SetSize(62,25);
	m_btAdd.m_colNormalText = RGB(255,255,255);
	m_btAdd.SetCtrlFont(RenderEngine->GetEndFont());

	m_btDel.Create(TEXT(" 删除"),WS_VISIBLE|WS_CHILD,CRect(rcClient.Width()-72,rcClient.Height()-92,0,0),this,IDC_MUSIC_DEL);
	m_btDel.SetBackImage(NULL,TEXT("Res\\Music\\allbtn_highlight.png"),TEXT("Res\\Music\\allbtn_down.png"),NULL,&CRect(3,3,3,3));
	m_btDel.SetIconImage(TEXT("Res\\Music\\icon_delete.png"));
	m_btDel.SetButtonType(en_IconButton);
	m_btDel.SetParentBack(hParentDC);
	m_btDel.SetSize(62,25);
	m_btDel.m_colNormalText = RGB(255,255,255);
	m_btDel.SetCtrlFont(RenderEngine->GetEndFont());

	m_pImageDefaultRes = RenderEngine->GetImage(TEXT("Res\\Music\\Default_res.png"));

	m_scProgress.Create(WS_CHILD|WS_VISIBLE|TBS_BOTH|TBS_NOTICKS,CRect(1,rcClient.Height()-65,rcClient.Width()-2,rcClient.Height()-59),this,0);
	m_scProgress.SetParentBack(hParentDC);
	m_scProgress.SetBackImage(TEXT("Res\\Music\\sound_back.png"),CRect(2,2,2,2));
	m_scProgress.SetTraceImage(TEXT("Res\\Music\\sound_Trace.png"),CRect(2,2,2,2));
	m_scProgress.SetThumImage(TEXT("Res\\Music\\individuation_bar.png"));
	m_scProgress.SetRange(0,1000);
	m_scProgress.SetPos(0);

	SetWindowText(TEXT("GMusic播放器"));

	SetWindowPos(NULL,0,0,880,680,SWP_NOMOVE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CGMusicDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CBaseDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGMusicDlg::OnPaint()
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
		CBaseDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGMusicDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CALLBACK CGMusicDlg::DOWNLOADPROC( const void *buffer, DWORD length, void *user )
{
	
}


void CGMusicDlg::OnSize(UINT nType, int cx, int cy)
{
	CBaseDialog::OnSize(nType, cx, cy);

	//移动准备
	HDWP hDwp=BeginDeferWindowPos(64);
	UINT uFlags=SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER;

	DeferWindowPos(hDwp,m_btOption,NULL,cx-100,25,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btSkin,NULL,cx-125,25,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_WebPublicize,NULL,1,64,cx-310,cy-70-64,uFlags|SWP_NOMOVE);
	DeferWindowPos(hDwp,m_ListMusic,NULL,cx-305,64,303,cy-105-64,uFlags);

	DeferWindowPos(hDwp,m_btPrev,NULL,cx/2-80,cy-53,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btOpen,NULL,cx/2-27,cy-57,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btPause,NULL,cx/2-27,cy-57,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btLast,NULL,cx/2+40,cy-53,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btMute,NULL,cx/2+100,cy-40,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_scVolume,NULL,cx/2+130,cy-30,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btAdd,NULL,cx-144,cy-92,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btDel,NULL,cx-72,cy-92,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_scProgress,NULL,1,cy-65,cx-2,6,uFlags);

	//结束调整
	LockWindowUpdate();
	EndDeferWindowPos(hDwp);
	UnlockWindowUpdate();
}

//双击列表
void CGMusicDlg::OnLbnDblclkList1()
{
	OnBnClickedMusicPlay();
}


void CGMusicDlg::DrawView( CDC*pDC,int nWidth,int nHeight )
{
	DrawMusicInfo(pDC,nWidth,nHeight);
}

void CGMusicDlg::DrawMusicInfo( CDC*pDC,int nWidth,int nHeight )
{
	pDC->SelectObject(RenderEngine->GetDeaultFont());
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255,255,255));

	CMusicManagerMap::iterator iter = m_MusicManager.find(m_ListMusic.m_nPlayItem);
	if ( iter != m_MusicManager.end() )
	{
		CString StrTitle;
		StrTitle.Format(TEXT("%s - %s"),iter->second->szTitle,iter->second->szArtist);
		pDC->DrawText(StrTitle,&CRect(60,nHeight-48,300,nHeight),DT_LEFT|DT_TOP|DT_SINGLELINE|DT_END_ELLIPSIS);

		DWORD dwCurTime = BASS_ChannelBytes2Seconds(m_hStream,BASS_ChannelGetPosition(m_hStream,BASS_POS_BYTE));
		DWORD dwTotleTime = iter->second->dwTime;

		CString StrTime;
		StrTime.Format(TEXT("%u:%02u |"),dwCurTime/60,dwCurTime%60);
		pDC->TextOut(60,nHeight-24,StrTime);
		//pDC->DrawText(StrTime,&CRect(60,nHeight-24,100,nHeight),DT_LEFT|DT_TOP|DT_SINGLELINE|DT_END_ELLIPSIS);

		CString StrTotleTime;
		StrTotleTime.Format(TEXT(" %u:%02u"),dwTotleTime/60,dwTotleTime%60);
		pDC->DrawText(StrTotleTime,&CRect(100,nHeight-24,300,nHeight),DT_LEFT|DT_TOP|DT_SINGLELINE|DT_END_ELLIPSIS);
	}

	if ( CHECK_IMAGE(m_pImageDefaultRes) )
	{
		m_pImageDefaultRes->DrawImage(pDC,5,nHeight-55);
	}
}

//销毁消息
void CGMusicDlg::OnDestroy()
{
	CBaseDialog::OnDestroy();

	RenderEngine->RemoveImage(m_pImageDefaultRes);

	CMusicManagerMap::iterator iter = m_MusicManager.begin();

	for (;iter!=m_MusicManager.end();++iter)
	{
		SafeDelete(iter->second);
	}

	m_MusicManager.clear();
}

//添加按钮事件
void CGMusicDlg::OnBnClickedMusicAdd()
{
	//构造菜单
	CSkinMenu MainMenu;
	MainMenu.CreatePopupMenu();

	RenderEngine->AddFont(TEXT("微软雅黑"),16);
	MainMenu.SetCtrlFont(RenderEngine->GetEndFont());
	MainMenu.SetItemHeight(45);

	//建立菜单
	MainMenu.AppendMenu(IDM_MENU_ADD,TEXT("添加本地歌曲文件"));
	MainMenu.AppendMenu(IDM_MENU_ADDBROWER,TEXT("添加本地歌曲目录"));

	MainMenu.SetMenuHovenImage(TEXT("Res\\Menu\\menu_selected.png"));

	//显示菜单
	MainMenu.TrackPopupMenu(this);
}

//删除列表元素
void CGMusicDlg::OnBnClickedMusicDel()
{
	for (int i=m_ListMusic.GetCount();i>=0;i--)
	{
		if ( m_ListMusic.GetSel(i) > 0 )
		{
			m_ListMusic.DeleteString(i);

			CMusicManagerMap::iterator iter = m_MusicManager.find(i);
			if ( iter != m_MusicManager.end())
			{
				SafeDelete(iter->second);
				m_MusicManager.erase(iter);
			}
		}
	}
}

BOOL CGMusicDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
	case IDM_MENU_ADD:		//菜单事件--本地添加
		{
			CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT|OFN_ALLOWMULTISELECT,NULL, this);  

			dlg.m_ofn.lpstrFilter=TEXT("声音文件*.mp3;*.mp2;*.mp1;*.ogg;*.wav;*.aif;\0*.mp3;*.mp2;*.mp1;*.ogg;*.wav;*.aif\0\0");

			if(dlg.DoModal() == IDOK)  
			{
				InsertMusicList(dlg.GetPathName(),dlg.GetFileName());
			}
		}
		break;
	case IDM_MENU_ADDBROWER:
		{
			//打开浏览文件目录
			CString    strFolderPath;
			BROWSEINFO broInfo = {0};
			TCHAR       szDisName[MAX_PATH] = {0};

			broInfo.hwndOwner = GetSafeHwnd();
			broInfo.pidlRoot  = NULL;
			broInfo.pszDisplayName = szDisName;
			broInfo.lpszTitle = TEXT("选择保存路径");
			broInfo.ulFlags   = BIF_NEWDIALOGSTYLE | BIF_DONTGOBELOWDOMAIN | BIF_BROWSEFORCOMPUTER | BIF_RETURNONLYFSDIRS | BIF_RETURNFSANCESTORS;
			broInfo.lpfn      = NULL;
			broInfo.lParam    = NULL;
			broInfo.iImage    = IDR_MAINFRAME;

			LPITEMIDLIST pIDList = SHBrowseForFolder(&broInfo);
			if (pIDList != NULL)
			{
				memset(szDisName, 0, sizeof(szDisName));
				SHGetPathFromIDList(pIDList, szDisName);
				strFolderPath = szDisName;
			}

			if ( strFolderPath.GetLength() == 0 ) break;
			
			BrowerFolder(strFolderPath,0);
		}
		break;
	}

	return CBaseDialog::OnCommand(wParam, lParam);
}

void CGMusicDlg::BrowerFolder(CString strDir, int nDepth)
{
	CFileFind filefind;                             //声明CFileFind类型变量
	CString strWildpath = strDir + _T("\\*.*");     //所有文件都列出。
	if(filefind.FindFile(strWildpath, 0))	        //开始检索文件
	{
		BOOL bRet = TRUE;
		while(bRet)
		{
			bRet = filefind.FindNextFile();                 //枚举一个文件
			if(filefind.IsDots())                           //如果是. 或 .. 做下一个
				continue;
		
			if(!filefind.IsDirectory())                      //不是子目录，把文件名打印出来
			{
				//TODO:此处没有做处理，如果假如不是音频文件就会出错
				InsertMusicList(filefind.GetFilePath(),filefind.GetFileTitle());
			}
			else                                                    //如果是子目录，递归调用该函数
			{
				BrowerFolder(filefind.GetFilePath(), nDepth + 1);	//递归调用该函数打印子目录里的文件
			}
		}

		filefind.Close();
	}
}

//上一首
void CGMusicDlg::OnBnClickedMusicPrev()
{
	m_pBassMusic->Stop(m_hStream);

	m_ListMusic.m_nPlayItem--;

	if ( m_ListMusic.m_nPlayItem < 0 ) m_ListMusic.m_nPlayItem = 0;
	m_ListMusic.Invalidate(FALSE);

	CMusicManagerMap::iterator iter = m_MusicManager.find(m_ListMusic.m_nPlayItem);
	if ( iter == m_MusicManager.end() ) return;

	m_hStream = iter->second->hStream;

	if( m_pBassMusic->Play(m_hStream,true) )
	{
		//更换按钮显示
		m_btOpen.ShowWindow(SW_HIDE);
		m_btPause.ShowWindow(SW_SHOW);

		//设置滑块控件的长度，同时启动计时器，计算当前播放进度
		m_scProgress.SetRange(0,iter->second->dwTime);
		m_scProgress.SetPos(0);
		KillTimer(1);
		SetTimer(1,500,0);
	}
}

//播放
void CGMusicDlg::OnBnClickedMusicPlay()
{
	int nIndex = GetCurSel();

	CMusicManagerMap::iterator iter = m_MusicManager.find(nIndex);
	if ( iter == m_MusicManager.end() ) return;

	m_hStream = iter->second->hStream;

	if( m_pBassMusic->Play(m_hStream,(m_ListMusic.m_nPlayItem== nIndex) ? false : true) )
	{
		m_ListMusic.m_nPlayItem = nIndex;
		m_btOpen.ShowWindow(SW_HIDE);
		m_btPause.ShowWindow(SW_SHOW);

		m_scProgress.SetRange(0,iter->second->dwTime);
		m_scProgress.SetPos(0);
		KillTimer(1);
		SetTimer(1,500,0);
	}
}

//暂停
void CGMusicDlg::OnBnClickedMusicPause()
{
	if ( m_pBassMusic->IsPlaying(m_hStream) == FALSE ) return;
	
	if( m_pBassMusic->Pause(m_hStream) )
	{
		m_btPause.ShowWindow(SW_HIDE);
		m_btOpen.ShowWindow(SW_SHOW);
	}
}

//下一首
void CGMusicDlg::OnBnClickedMusicLast()
{
	m_pBassMusic->Stop(m_hStream);

	m_ListMusic.m_nPlayItem++;
	
	if ( m_ListMusic.m_nPlayItem > m_ListMusic.GetCount() )
	{
		m_ListMusic.m_nPlayItem = m_ListMusic.GetCount();

		m_btPause.ShowWindow(SW_HIDE);
		m_btOpen.ShowWindow(SW_SHOW);

		return;
	}

	m_ListMusic.Invalidate(FALSE);

	CMusicManagerMap::iterator iter = m_MusicManager.find(m_ListMusic.m_nPlayItem);
	if ( iter == m_MusicManager.end() ) return;

	m_hStream = iter->second->hStream;

	if( m_pBassMusic->Play(m_hStream,true) )
	{
		m_btOpen.ShowWindow(SW_HIDE);
		m_btPause.ShowWindow(SW_SHOW);

		m_scProgress.SetRange(0,iter->second->dwTime);
		m_scProgress.SetPos(0);
		KillTimer(1);
		SetTimer(1,500,0);
	}
}

//静音按钮
void CGMusicDlg::OnBnClickedMusicMute()
{
	static int nOldVolume = m_pBassMusic->GetVolume();

	int nVolume = m_pBassMusic->GetVolume();

	if ( nVolume > 0 )
	{
		m_btMute.SetBackImage(TEXT("Res\\Mute\\mute1_normal.png"),TEXT("Res\\Mute\\mute1_highlight.png"),TEXT("Res\\Mute\\mute1_down.png"),TEXT("Res\\Mute\\mute1_normal.png"));
		m_pBassMusic->SetVolume(0);
		m_scVolume.SetPos(0);
	}
	else
	{
		if ( nOldVolume <= 50 )
			m_btMute.SetBackImage(TEXT("Res\\Mute\\mute2_normal.png"),TEXT("Res\\Mute\\mute2_highlight.png"),TEXT("Res\\Mute\\mute2_down.png"),TEXT("Res\\Mute\\mute2_normal.png"));
		else
			m_btMute.SetBackImage(TEXT("Res\\Mute\\mute3_normal.png"),TEXT("Res\\Mute\\mute3_highlight.png"),TEXT("Res\\Mute\\mute3_down.png"),TEXT("Res\\Mute\\mute3_normal.png"));

		m_pBassMusic->SetVolume(nOldVolume);
		m_scVolume.SetPos(nOldVolume);
	}

	nOldVolume = nVolume;
}


//获取列表当前选择，优先从最前面开始找
int CGMusicDlg::GetCurSel()
{
	for (int i=0;i<m_ListMusic.GetCount();i++)
	{
		if( m_ListMusic.GetSel(i) > 0 )
		{
			return i;
		}
	}

	return -1;
}

//播放进度
void CGMusicDlg::OnTimer(UINT_PTR nIDEvent)
{
	switch ( nIDEvent )
	{
	case 1:
		{
			m_scProgress.SetPos((DWORD)BASS_ChannelBytes2Seconds(m_hStream,BASS_ChannelGetPosition(m_hStream,BASS_POS_BYTE)));

			CRect rcClient;
			GetClientRect(&rcClient);

			Invalidate(FALSE);
			//InvalidateRect(&CRect(60,rcClient.Height()-48,300,rcClient.Height()),FALSE);
		}
		break;
	}

	CBaseDialog::OnTimer(nIDEvent);
}


void CGMusicDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	//播放进度条
	if( (pScrollBar != NULL) && ((CSliderCtrl*)pScrollBar == &m_scProgress) )
	{
		int nPos= m_scProgress.GetPos();
		BASS_ChannelSetPosition(m_hStream,BASS_ChannelSeconds2Bytes(m_hStream,nPos),BASS_POS_BYTE);
	}

	//音量调节
	if( (pScrollBar != NULL) && ((CSliderCtrl*)pScrollBar == &m_scVolume) )
	{
		UpdateVolume();

	}

	CBaseDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CGMusicDlg::InsertMusicList( LPCTSTR lpFilePath,LPCTSTR lpFileName )
{
	//加载文件
	HSTREAM hStream = m_pBassMusic->LoadFile(lpFilePath);
	if ( hStream == -1 ) return;

	//往ListBox中添加新数据
	m_ListMusic.AddString(lpFileName);

	//获取媒体标签
	tagMusicInfo *pInfo = m_pBassMusic->GetInfo(hStream);

	//通过map和ListBox结合，一起管理播放列表
	tagMusicInfo *pMusicInfo = new tagMusicInfo;

	pMusicInfo->dwTime = pInfo->dwTime;
	pMusicInfo->hStream = pInfo->hStream;
	lstrcpyn(pMusicInfo->szArtist,pInfo->szArtist,CountArray(pMusicInfo->szArtist));
	lstrcpyn(pMusicInfo->szTitle,pInfo->szTitle,CountArray(pMusicInfo->szTitle));

	m_MusicManager.insert(pair<int,tagMusicInfo*>(m_ListMusic.GetCount()-1,pMusicInfo));
}

BOOL CGMusicDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if ( m_scVolume.GetSafeHwnd() != NULL )
	{
		int nPos = m_scVolume.GetPos();

		if (zDelta < 0)		
			m_scVolume.SetPos(nPos-5);
		else	
			m_scVolume.SetPos(nPos+5);

		UpdateVolume();

		m_scVolume.Invalidate(FALSE);
	}

	return CBaseDialog::OnMouseWheel(nFlags, zDelta, pt);
}

void CGMusicDlg::UpdateVolume()
{
	int nPos= m_scVolume.GetPos();
	m_pBassMusic->SetVolume(nPos);

	if ( nPos == 0 )
		m_btMute.SetBackImage(TEXT("Res\\Mute\\mute1_normal.png"),TEXT("Res\\Mute\\mute1_highlight.png"),TEXT("Res\\Mute\\mute1_down.png"),TEXT("Res\\Mute\\mute1_normal.png"));
	else if ( nPos <= 50 )
		m_btMute.SetBackImage(TEXT("Res\\Mute\\mute2_normal.png"),TEXT("Res\\Mute\\mute2_highlight.png"),TEXT("Res\\Mute\\mute2_down.png"),TEXT("Res\\Mute\\mute2_normal.png"));
	else
		m_btMute.SetBackImage(TEXT("Res\\Mute\\mute3_normal.png"),TEXT("Res\\Mute\\mute3_highlight.png"),TEXT("Res\\Mute\\mute3_down.png"),TEXT("Res\\Mute\\mute3_normal.png"));

	m_btMute.Invalidate(FALSE);
}

void CGMusicDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetFocus();

	CBaseDialog::OnLButtonDown(nFlags, point);
}

void CGMusicDlg::OnStop()
{
	//自动切换下一首歌
	OnBnClickedMusicLast();
}

void CGMusicDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	lpMMI->ptMinTrackSize.x = 880;
	lpMMI->ptMinTrackSize.y = 680;

	__super::OnGetMinMaxInfo(lpMMI);
}

void CGMusicDlg::OnBnClickedSkin()
{
	if ( m_SkinDlg.GetSafeHwnd() == NULL )
	{
		m_SkinDlg.Create(IDD_SKIN);
	}

	m_SkinDlg.ShowWindow(SW_SHOW);
	m_SkinDlg.CenterWindow(GetDesktopWindow());
}

