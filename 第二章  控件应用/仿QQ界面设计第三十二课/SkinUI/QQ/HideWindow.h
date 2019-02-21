#pragma once

//������������
enum AFX_HIDE_TYPE
{
	en_None = 0,		//������
	en_Top,				//��������
	en_Bottom,			//��������
	en_Left,			//��������
	en_Right			//��������
};

//////////////////////////////////////////////////////////////////////////

class CHideWindow
{
protected:
	bool					m_bSized;					//���ڴ�С�Ƿ�ı� 
	bool					m_bTimed;					//�Ƿ������˼������Timer

	INT 					m_nWindowHeight;			//�ɵĴ��ڿ��
	INT 					m_nTaskBarHeight;			//�������߶�
	INT 					m_nEdgeHeight;				//��Ե�߶�
	INT 					m_nEdgeWidth;				//��Ե���

	AFX_HIDE_TYPE 			m_enHideType;				//����ģʽ
	bool					m_bFinished;				//���ػ���ʾ�����Ƿ����
	bool					m_bHiding;					//�ò���ֻ����!m_hsFinished����Ч,��:��������,��:������ʾ

	HWND					m_hOwnHwnd;

public:
	CHideWindow(void);
	~CHideWindow(void);

	//���ú���
public:
	//���ô�������
	void SetHideWindow(HWND hWnd,int nEdgeHeight=3,int nEdgeWidth=3);
	//�����ƶ�ʱ���ڵĴ�С
	void FixMoving(UINT fwSide, LPRECT pRect);
	//�����ĸı䴰�ڴ�Сʱ���ڵĴ�С
	void FixSizing(UINT fwSide, LPRECT pRect);
	//������״̬��ʾ����
	void ShowWindow();
	//����ʾ״̬��������
	void HideWindow();
	//��ʱ����Ϣ
	void HideLoop( UINT nIDEvent );
	//��ʼ����
	void BeginHide(CPoint point);
	//���غ���
	BOOL SetWindowPos(HWND hWndInsertAfter,LPCRECT pCRect, UINT nFlags = SWP_SHOWWINDOW);
};
