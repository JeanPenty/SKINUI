// ImageHandleDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ImageHandle.h"
#include "ImageHandleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CBaseDialog
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

CAboutDlg::CAboutDlg() : CBaseDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CBaseDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CBaseDialog)
END_MESSAGE_MAP()


// CImageHandleDlg �Ի���




CImageHandleDlg::CImageHandleDlg(CWnd* pParent /*=NULL*/)
	: CBaseDialog(CImageHandleDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_ptPos.SetPoint(0,0);
	m_nAngle = 0;
	m_fScale = 1.0f;
}

void CImageHandleDlg::DoDataExchange(CDataExchange* pDX)
{
	CBaseDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CImageHandleDlg, CBaseDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_GETMINMAXINFO()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_HARASIZE,OnBnClickSize)
	ON_BN_CLICKED(IDC_BIG,OnBnClickLarge)
	ON_BN_CLICKED(IDC_SMALL,OnBnClickShrink)
	ON_BN_CLICKED(IDC_OPEN,OnBnClickOpen)
	ON_BN_CLICKED(IDC_SAVE,OnBnClickSave)
	ON_BN_CLICKED(IDC_LEFT,OnBnClickLeft)
	ON_BN_CLICKED(IDC_RIGHT,OnBnClickRight)
	ON_WM_HSCROLL()
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// CImageHandleDlg ��Ϣ�������

BOOL CImageHandleDlg::OnInitDialog()
{
	CBaseDialog::OnInitDialog();

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

	HDC hParentDC = GetBackDC();

	CRect rcClient;
	GetClientRect(&rcClient);

	m_btSize.Create(NULL,WS_VISIBLE|WS_CHILD,CRect(rcClient.Width()/2-140,rcClient.Height()-37,0,0),this,IDC_HARASIZE);
	m_btSize.SetBackImage(TEXT("Res\\Tool\\size_normal.png"),TEXT("Res\\Tool\\size_highlight.png"),TEXT("Res\\Tool\\size_down.png"),TEXT("Res\\Tool\\size_normal.png"));
	m_btSize.SetButtonType(en_PushButton);
	m_btSize.SetParentBack(hParentDC);
	m_btSize.SetSize(40,34);

	m_btLarge.Create(NULL,WS_VISIBLE|WS_CHILD,CRect(rcClient.Width()/2-100,rcClient.Height()-37,0,0),this,IDC_BIG);
	m_btLarge.SetBackImage(TEXT("Res\\Tool\\big_normal.png"),TEXT("Res\\Tool\\big_highlight.png"),TEXT("Res\\Tool\\big_down.png"),TEXT("Res\\Tool\\big_normal.png"));
	m_btLarge.SetButtonType(en_PushButton);
	m_btLarge.SetParentBack(hParentDC);
	m_btLarge.SetSize(40,34);

	m_btShrink.Create(NULL,WS_VISIBLE|WS_CHILD,CRect(rcClient.Width()/2-60,rcClient.Height()-37,0,0),this,IDC_SMALL);
	m_btShrink.SetBackImage(TEXT("Res\\Tool\\small_normal.png"),TEXT("Res\\Tool\\small_highlight.png"),TEXT("Res\\Tool\\small_down.png"),TEXT("Res\\Tool\\small_normal.png"));
	m_btShrink.SetButtonType(en_PushButton);
	m_btShrink.SetParentBack(hParentDC);
	m_btShrink.SetSize(40,34);

	m_btOpen.Create(NULL,WS_VISIBLE|WS_CHILD,CRect(rcClient.Width()/2-20,rcClient.Height()-37,0,0),this,IDC_OPEN);
	m_btOpen.SetBackImage(TEXT("Res\\Tool\\open_normal.png"),TEXT("Res\\Tool\\open_highlight.png"),TEXT("Res\\Tool\\open_down.png"),TEXT("Res\\Tool\\open_normal.png"));
	m_btOpen.SetButtonType(en_PushButton);
	m_btOpen.SetParentBack(hParentDC);
	m_btOpen.SetSize(40,34);

	m_btSave.Create(NULL,WS_VISIBLE|WS_CHILD,CRect(rcClient.Width()/2+20,rcClient.Height()-37,0,0),this,IDC_SAVE);
	m_btSave.SetBackImage(TEXT("Res\\Tool\\save_normal.png"),TEXT("Res\\Tool\\save_highlight.png"),TEXT("Res\\Tool\\save_down.png"),TEXT("Res\\Tool\\save_normal.png"));
	m_btSave.SetButtonType(en_PushButton);
	m_btSave.SetParentBack(hParentDC);
	m_btSave.SetSize(40,34);

	m_btLeft.Create(NULL,WS_VISIBLE|WS_CHILD,CRect(rcClient.Width()/2+60,rcClient.Height()-37,0,0),this,IDC_LEFT);
	m_btLeft.SetBackImage(TEXT("Res\\Tool\\left_normal.png"),TEXT("Res\\Tool\\left_highlight.png"),TEXT("Res\\Tool\\left_down.png"),TEXT("Res\\Tool\\left_normal.png"));
	m_btLeft.SetButtonType(en_PushButton);
	m_btLeft.SetParentBack(hParentDC);
	m_btLeft.SetSize(40,34);

	m_btRight.Create(NULL,WS_VISIBLE|WS_CHILD,CRect(rcClient.Width()/2+100,rcClient.Height()-37,0,0),this,IDC_RIGHT);
	m_btRight.SetBackImage(TEXT("Res\\Tool\\right_normal.png"),TEXT("Res\\Tool\\right_highlight.png"),TEXT("Res\\Tool\\right_down.png"),TEXT("Res\\Tool\\right_normal.png"));
	m_btRight.SetButtonType(en_PushButton);
	m_btRight.SetParentBack(hParentDC);
	m_btRight.SetSize(40,34);

	m_scAlpha.Create(WS_CHILD|WS_VISIBLE|TBS_BOTH|TBS_NOTICKS,CRect(rcClient.Width()-160,rcClient.Height()-30,104,14),this,0);
	m_scAlpha.SetParentBack(GetBackDC());
	m_scAlpha.SetBackImage(TEXT("Res\\Tool\\individuation_disable.png"));
	m_scAlpha.SetButtonImage(TEXT("Res\\Tool\\individuation_bar.png"));
	m_scAlpha.SetRange(0,255);
	m_scAlpha.SetPos(255);

	SetWindowText(TEXT("����һ��ѧMFC ��http://www.gymsaga.com��"));

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CImageHandleDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CImageHandleDlg::OnPaint()
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
		CBaseDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CImageHandleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CImageHandleDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	lpMMI->ptMinTrackSize.x = 800;
	lpMMI->ptMinTrackSize.y = 480;

	CBaseDialog::OnGetMinMaxInfo(lpMMI);
}

void CImageHandleDlg::OnSize(UINT nType, int cx, int cy)
{
	CBaseDialog::OnSize(nType, cx, cy);

	//�ƶ�׼��
	HDWP hDwp=BeginDeferWindowPos(64);
	UINT uFlags=SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER;

	DeferWindowPos(hDwp,m_btSize,NULL,cx/2-140,cy-37,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btLarge,NULL,cx/2-100,cy-37,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btShrink,NULL,cx/2-60,cy-37,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btOpen,NULL,cx/2-20,cy-37,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btSave,NULL,cx/2+20,cy-37,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btLeft,NULL,cx/2+60,cy-37,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btRight,NULL,cx/2+100,cy-37,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_scAlpha,NULL,cx-160,cy-30,0,0,uFlags|SWP_NOSIZE);

	//��������
	LockWindowUpdate();
	EndDeferWindowPos(hDwp);
	UnlockWindowUpdate();

	static CRect rcClient(0,0,0,0);

	m_ptPos.x += (cx - rcClient.Width())/2;
	m_ptPos.y += (cy - rcClient.Height())/2;

	rcClient.SetRect(0,0,cx,cy);
}

void CImageHandleDlg::OnBnClickSize()
{
	if ( m_Image.IsNull() ) return;

	m_fScale = 1.0f;

	m_Image.SetScale(m_fScale,m_fScale);

	Invalidate(FALSE);
}

void CImageHandleDlg::OnBnClickLarge()
{
	if ( m_Image.IsNull() ) return;

	m_fScale += 0.2f;
	if( m_fScale >= 4 ) m_fScale = 4;

	m_Image.SetScale(m_fScale,m_fScale);

	Invalidate(FALSE);
}

void CImageHandleDlg::OnBnClickShrink()
{
	if ( m_Image.IsNull() ) return;

	m_fScale -= 0.2f;
	if( m_fScale <= 0.06f ) m_fScale = 0.06f;

	m_Image.SetScale(m_fScale,m_fScale);

	Invalidate(FALSE);
}

void CImageHandleDlg::OnBnClickOpen()
{
	if ( m_Image.IsNull() == false )
	{
		m_Image.DestroyImage();
	}

	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT|OFN_ALLOWMULTISELECT,NULL, this);  

	dlg.m_ofn.lpstrFilter=TEXT("ͼ���ļ�*.jpg;*.bmp;*.png;\0*.jpg;*.bmp;*.png\0\0");

	if(dlg.DoModal() == IDOK)  
	{  
		CString str = dlg.GetPathName();
		if( !m_Image.LoadImage(dlg.GetPathName()) )
		{
			AfxMessageBox(TEXT("������Դʧ�ܣ�"));
			return;
		}
	}
	else return;

	CRect rcClient;
	GetClientRect(&rcClient);

	//��ʼ������
	m_ptPos.SetPoint((rcClient.Width()-m_Image.GetWidth())/2,(rcClient.Height()-m_Image.GetHeight())/2);
	m_fScale = 1.0f;
	m_nAngle = 0;

	//�ָ�����
	m_Image.SetRotation(m_nAngle);
	m_Image.SetScale(m_fScale,m_fScale);

	Invalidate(FALSE);
}

void CImageHandleDlg::OnBnClickSave()
{
	//��bug��QQȺ�� ƫ��һ�� �ṩ
	if ( m_Image.IsNull() ) return;

	CString strFilter;
	strFilter = TEXT("λͼ�ļ�|*.bmp|JPEG ͼ���ļ�|*.jpg| GIF ͼ���ļ�|*.gif|PNG ͼ���ļ�|*.png||");
	
	CFileDialog dlg(FALSE,NULL,NULL,NULL,strFilter);
	if ( IDOK != dlg.DoModal()) return;

	//����û�û��ָ���ļ���չ������Ϊ�����һ��
	CString strFileName;
	CString strExtension;

	strFileName = dlg.m_ofn.lpstrFile;

	switch (dlg.m_ofn.nFilterIndex)
	{
	case 1:
		strExtension = TEXT("bmp"); break;
	case 2:
		strExtension = TEXT("jpeg"); break;
	case 3:
		strExtension = TEXT("gif"); break;
	case 4:
		strExtension = TEXT("png"); break;
	default:
		break;
	}

	strFileName = strFileName + TEXT('.') + strExtension;

	bool hResult = m_Image.Save(strFileName,TEXT("image/")+strExtension);
	if ( !hResult ) 
		MessageBox(TEXT("����ͼ���ļ�ʧ�ܣ�"));
}

void CImageHandleDlg::OnBnClickLeft()
{
	if ( m_Image.IsNull() ) return;

	m_nAngle -= 90;
	m_Image.SetRotation(m_nAngle);

	Invalidate(FALSE);
}

void CImageHandleDlg::OnBnClickRight()
{
	if ( m_Image.IsNull() ) return;

	m_nAngle += 90;
	m_Image.SetRotation(m_nAngle);
	
	Invalidate(FALSE);
}

void CImageHandleDlg::DrawView( CDC*pDC,int nWidth,int nHeight )
{
	if ( m_Image.IsNull() == false )
	{
		m_Image.DrawImage(pDC,m_ptPos.x,m_ptPos.y);
	}
}

void CImageHandleDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if( (pScrollBar != NULL) && ((CSliderCtrl*)pScrollBar == &m_scAlpha) )
	{
		m_Image.SetAlpha(m_scAlpha.GetPos());

		Invalidate(FALSE);
	}

	CBaseDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CImageHandleDlg::OnDropFiles(HDROP hDropInfo)
{
	UINT nCount;
	TCHAR szFilePath[MAX_PATH];

	nCount = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);
	
	if(nCount)
	{        
		DragQueryFile(hDropInfo, nCount-1, szFilePath, sizeof(szFilePath));
	}

	DragFinish(hDropInfo);

	if ( m_Image.IsNull() == false )
	{
		m_Image.DestroyImage();
	}
 
	if( !m_Image.LoadImage(szFilePath) )
	{
		AfxMessageBox(TEXT("������Դʧ�ܣ�"));
		return;
	}
	
	CRect rcClient;
	GetClientRect(&rcClient);

	//��ʼ������
	m_ptPos.SetPoint((rcClient.Width()-m_Image.GetWidth())/2,(rcClient.Height()-m_Image.GetHeight())/2);
	m_fScale = 1.0f;
	m_nAngle = 0;

	//�ָ�����
	m_Image.SetRotation(m_nAngle);
	m_Image.SetScale(m_fScale,m_fScale);

	Invalidate(FALSE);

	CBaseDialog::OnDropFiles(hDropInfo);
}
