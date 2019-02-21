// MusicDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Music.h"
#include "MusicDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define		IDC_PREV			WM_USER+0x010
#define		IDC_PLAY			WM_USER+0x011
#define		IDC_PAUSE			WM_USER+0x012
#define		IDC_NEXT			WM_USER+0x013
#define		IDC_ABOUT			WM_USER+0x014
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMusicDlg �Ի���
CMusicDlg::CMusicDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMusicDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_StrMusicName = TEXT("�����ڣ����й�������������Ī����ֵ���ѧԱ");
}

void CMusicDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMusicDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CMusicDlg ��Ϣ�������

BOOL CMusicDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//LoadBackSkin("d:\\windows\\Desktop\\BG.png");
	LoadBackSkin("d:\\windows\\Desktop\\BACK_VIEW.jpg");
	SetExtrude(false);
	SetWindowPos(NULL,0,0,310,490,SWP_NOMOVE);

	HINSTANCE hInstance = AfxGetInstanceHandle();

	m_btPrev.Create(NULL,WS_CHILD|WS_VISIBLE,CRect(90,45,0,0),this,IDC_PREV);
	m_btPrev.SetButtonImage(hInstance,TEXT("BT_PREV"));

	m_btPlay.Create(NULL,WS_CHILD|WS_VISIBLE,CRect(130,45,0,0),this,IDC_PLAY);
	m_btPlay.SetButtonImage(hInstance,TEXT("BT_PLAY"));

	m_btPause.Create(NULL,WS_CHILD,CRect(130,45,0,0),this,IDC_PAUSE);
	m_btPause.SetButtonImage(hInstance,TEXT("BT_PAUSE"));

	m_btNext.Create(NULL,WS_CHILD|WS_VISIBLE,CRect(170,45,0,0),this,IDC_NEXT);
	m_btNext.SetButtonImage(hInstance,TEXT("BT_NEXT"));

	m_ListMusic.Create(WS_CHILD|WS_VISIBLE|LBS_OWNERDRAWVARIABLE|LBS_HASSTRINGS,CRect(1,120,309,460),this,NULL);
	m_ListMusic.SetItemHeight(32);
	
	m_HyperLink.Create(TEXT("����һ��ѧMFC"),WS_CHILD|WS_VISIBLE,CRect(210,470,310,490),this,IDC_ABOUT);
	m_HyperLink.SetHyperLinkTextColor(RGB(255,0,0),RGB(254,254,254),RGB(255,255,255));

	m_ImageDefault.LoadImage(hInstance,TEXT("DEFAULT"));

	//�����õ�
	m_ListMusic.AddString(TEXT("���� - ����"));
	m_ListMusic.AddString(TEXT("�����ս�� - �й�������"));
	m_ListMusic.AddString(TEXT("�����ڣ����й�����������"));
	m_ListMusic.AddString(TEXT("�Ұ����й� - ����"));
	m_ListMusic.AddString(TEXT("��һ�ΰ����� - ������"));

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMusicDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMusicDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMusicDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMusicDlg::OnClientDraw( CDC*pDC,INT nWidth,INT nHeight )
{
	//�������ϽǱ�־
	m_ImageDefault.DrawImage(pDC,0,0,76,76);

	pDC->SetTextColor(RGB(255,255,255));
	CRect rcText(85,10,250,26);
	DrawText(pDC, rcText,m_StrMusicName,DT_LEFT|DT_END_ELLIPSIS);

	pDC->FillSolidRect(1,76,308,44,RGB(255,255,255));
	
	pDC->SetTextColor(RGB(0,0,0));
	DrawText(pDC, CRect(5,90,300,120),TEXT("���ڲ��ţ������б�"),DT_LEFT|DT_END_ELLIPSIS,20);
}

bool CMusicDlg::OnMaxSize()
{
	CRect rcWindows;
	GetWindowRect(&rcWindows);

	static bool bMini = false;

	bMini=!bMini;

	SetWindowPos(NULL,0,0,rcWindows.Width(),(bMini? 76 : 490),SWP_NOMOVE);

	return true;
}


BOOL CMusicDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	switch ( LOWORD( wParam))
	{
	case IDC_PLAY:
		{
			m_btPause.ShowWindow(SW_SHOW);
			m_btPlay.ShowWindow(SW_HIDE);
		}
		break;
	case IDC_PAUSE:
		{
			m_btPause.ShowWindow(SW_HIDE);
			m_btPlay.ShowWindow(SW_SHOW);
		}
		break;
	case IDC_ABOUT:
		{
			ShellExecute(NULL, TEXT("open"), TEXT("http://www.gymsaga.com/category/project/developc/mfc"), NULL, NULL, SW_SHOWNORMAL);
		}
		break;
	}

	return CDialogEx::OnCommand(wParam, lParam);
}

BOOL CMusicDlg::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
	//return CDialogEx::OnEraseBkgnd(pDC);
}

void CMusicDlg::DrawText( CDC* pDC, CRect rcText,LPCTSTR lpszText,UINT uFormat,INT nHeight/*=18*/,bool bBold/*=true*/,LPCTSTR lpszName/*=TEXT("΢���ź�")*/ )
{
	CFont font;
	font.CreateFont(nHeight,0,0,0,bBold?FW_BOLD:FW_NORMAL,0,FALSE,0,0,0,0,0,0,lpszName);
	CFont*  pOldFont = pDC->SelectObject(&font);	
	pDC->DrawText(lpszText,&rcText,uFormat);
	pDC->SelectObject(pOldFont);
}
