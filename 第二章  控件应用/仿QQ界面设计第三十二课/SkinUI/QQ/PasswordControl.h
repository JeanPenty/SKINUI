#ifndef PASSWORD_CONTROL_HEAD_FILE
#define PASSWORD_CONTROL_HEAD_FILE

#pragma once

//////////////////////////////////////////////////////////////////////////////////

//�������
class CPasswordKeyboard : public CDialog,public ISkinControl
{
	//���ñ���
protected:
	INT								m_nRandLine[4];						//�������
	INT								m_nItemCount[4];					//�ַ���Ŀ
	TCHAR							m_szKeyboradChar[4][2][14];			//�����ַ�

	//����״̬
protected:
	bool							m_bShiftStatus;						//����״̬
	bool							m_bCapsLockStatus;					//����״̬

	//״̬����
protected:
	WORD							m_wHoverRow;						//��������
	WORD							m_wHoverLine;						//��������
	bool							m_bMouseDown;						//����״̬

	//��Դ��С
protected:
	CSize							m_SizeImageItem1;					//��Դ��С
	CSize							m_SizeImageItem2;					//��Դ��С
	CSize							m_SizeImageItem3;					//��Դ��С
	CSize							m_SizeBackGround;					//������С
	CSize							m_SizeImageButton;					//��Դ��С

	CImageEx 						*m_pImageItem1;
	CImageEx 						*m_pImageItem2;
	CImageEx 						*m_pImageItem3;
	CImageEx						*m_pImageButton;
	CImageEx						*m_pImageBackGround;

	CSkinEdit						*m_pEdit;

	//��������
public:
	//���캯��
	CPasswordKeyboard();
	//��������
	virtual ~CPasswordKeyboard();

	//�󶨺���
public:
	void SetBuddy(CSkinEdit*pEdit);

	//���غ���
protected:
	//��Ϣ����
	virtual BOOL PreTranslateMessage(MSG * pMsg);
	//��������
	virtual BOOL OnInitDialog();
	//ȷ������
	virtual VOID OnOK() { return; }
	//ȡ����Ϣ
	virtual VOID OnCancel() { return; }

	//��������
protected:
	//����λ��
	VOID SetCurrentStation(CPoint MousePoint);
	//�������
	WORD GetVirualKeyCode(WORD wHoverLine, WORD wHoverRow);

	//��Ϣ����
protected:
	//����滭
	VOID OnNcPaint();
	//�滭����
	BOOL OnEraseBkgnd(CDC * pDC);
	//ʧȥ����
	VOID OnKillFocus(CWnd * pNewWnd);
	//�����Ϣ
	VOID OnLButtonUp(UINT nFlags, CPoint Point);
	//�����Ϣ
	VOID OnLButtonDown(UINT nFlags, CPoint Point);
	//�����Ϣ
	BOOL OnSetCursor(CWnd * pWnd, UINT nHitTest, UINT uMessage);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////////

#endif