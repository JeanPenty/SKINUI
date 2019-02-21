#pragma once


// CSkinManager �Ի���

//////////////////////////////////////////////////////////////////////////
enum AFX_WND_STYLE
{
	en_Wnd_Normal=0,			//�رգ���󻯣���С��ͬʱ����
	en_Wnd_MinimizeBox,			//����󻯰�ť
	en_Wnd_CloseBox,			//ֻ�йرհ�ť
	en_Wnd_None					//�ް�ť
};

class CSkinManager : public CSkinDialog
{
	DECLARE_DYNAMIC(CSkinManager)
public:
	CImageEx						*m_pImageBack;
	CImageEx						* m_pImageLogo;

	CSkinButton						m_btClose;
	CSkinButton						m_btMin;
	CSkinButton						m_btMax;

	AFX_WND_STYLE					m_enWndStyle;
	BYTE							m_bIsZoomed;
	bool							m_bShowLogo;

public:
	CSkinManager(UINT nIDTemplate,CWnd* pParent = NULL,AFX_WND_STYLE Style = en_Wnd_Normal);   // ��׼���캯��
	virtual ~CSkinManager();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	//���ڻ���
	virtual void DrawClientArea(CDC*pDC,int nWidth,int nHeight);

	void UpdateSkin();

	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickWindowMin();
	afx_msg void OnBnClickWindowMax();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();

	DECLARE_MESSAGE_MAP()
};
