#ifndef CHESS_BORAD_HEAD_FILE
#define CHESS_BORAD_HEAD_FILE

#pragma once
#include "ImageEx.h"
#include "GameLogic.h"
#include "OptionDlg.h"

//////////////////////////////////////////////////////////////////////////
//�궨��

//λ�ö���
#define EXCURSION_X					10									//ƫ������
#define EXCURSION_Y					10									//ƫ������
#define SPACE_BORAD_X				31									//��϶��С
#define SPACE_BORAD_Y				31									//��϶��С

//ѡ��ģʽ
#define SM_NO_SELECT				0x00								//��ֹѡ��
#define SM_NULL_CHESS				0x01								//ѡ��հ�
#define SM_BLACK_CHESS				0x02								//ѡ�����
#define SM_WHITE_CHESS				0x04								//ѡ�����

//��Ϣ����
#define WM_HIT_CHESS_BORAD			(WM_USER+200)						//�������

//////////////////////////////////////////////////////////////////////////
//�ṹ����

//���Ӷ���
struct tagChessInfo
{
	BYTE							cbFlag;								//���ӱ�־
	BYTE							cbColor;							//������ɫ
	BYTE							cbIdentifier;						//���ӱ�ʶ
};

//////////////////////////////////////////////////////////////////////////

//��Ϸ����
class CChessBorad : public CWnd
{
	//���ñ���
protected:
	bool							m_bShowChessID;						//��ʾ����
	bool							m_bDoubleMouse;						//˫������
	BYTE							m_cbSelectMode;						//ѡ��ģʽ

	//��������
protected:
	BYTE							m_cbXCursor;						//���λ��
	BYTE							m_cbYCursor;						//���λ��
	
	//״̬����
protected:
	BYTE							m_cbXPosFocus;						//��������
	BYTE							m_cbYPosFocus;						//��������
	tagChessInfo					m_ChessInfo[15][15];				//������Ϣ
	CGameLogic						m_GameLogic;
	COptionDlg						m_OptionDlg;

	//��Դ����
protected:
	CSize							m_BoradSize;						//���̴�С
	CImageEx						m_ImageChess;						//������Դ
	CImageEx						m_ImageBorad;						//������Դ
	CImageEx						m_ImageFrame;						//���ӿ��

	//��ս��Ϣ
protected:
	BYTE							m_cbMyColor;

	//��������
public:
	//���캯��
	CChessBorad();
	//��������
	virtual ~CChessBorad();

	//���ӿ���
public:
	//�������
	void CleanChess();
	//��������
	void SetChess(BYTE cbXPos, BYTE cbYPos, BYTE cbColor, BYTE cbIdentifier);
	//��������
	void SetChessBorad(const BYTE cbChessBorad[15][15], const BYTE cbIdentifier[15][15]);
	
	//״̬����
public:
	//��ʾ����
	void ShowChessID(bool bShowChessID);
	//˫������
	void SetDoubleMouse(bool bDoubleMouse);
	//ѡ��ģʽ
	void SetSelectMode(BYTE cbSelectMode);
	//���ý���
	void SetChessFocus(BYTE cbXPos, BYTE cbYPos);
	//��ʾʤ��
	void ShowWinChessLine(BYTE cbXFirstPos, BYTE cbYFirstPos, BYTE cbXEndPos, BYTE cbYEndPos);
	//��������
	void SetChessBorad(const WORD wBlackChess[], BYTE cbBlackCount, const WORD wWhiteChess[], BYTE cbWhiteCount);
	//��ʾ����
	void SetOption(bool bWhiteColor,bool bIGo);

	//״̬��ѯ
public:
	//��ʾ����
	bool IsShowChessID() { return m_bShowChessID; } 
	//˫������
	bool IsDoubleMouse() { return m_bDoubleMouse; }
	//ѡ��ģʽ
	BYTE GetSelectMode() { return m_cbSelectMode; }
	//��ȡ��С
	const CSize & GetChessBoradSize() { return m_BoradSize; }

	//��������
private:
	//��������
	void UpdateBoradPos(BYTE cbXPos, BYTE cbYPos);
	//ѡ���ж�
	bool EfficacySelect(BYTE cbXPos, BYTE cbYPos);
	//ת������
	void SwitchMousePos(const CPoint & MousePoint, BYTE & cbXPos, BYTE & cbYPos);
	//��ȡ����
	inline int GetChessXPos(BYTE cbXPos) { return EXCURSION_X+cbXPos*SPACE_BORAD_X; }
	//��ȡ����
	inline int GetChessYPos(BYTE cbYPos) { return EXCURSION_Y+cbYPos*SPACE_BORAD_Y; }
	//�����
	bool Detection(BYTE cbXPos, BYTE cbYPos,bool bAndroid);

	//��Ϣӳ��
protected:
	//�ػ�����
	afx_msg void OnPaint();
	//������Ϣ
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//�����Ϣ
	afx_msg void OnLButtonDown(UINT nFlags, CPoint Point);
	//���˫��
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//�����Ϣ
	afx_msg BOOL OnSetCursor(CWnd * pWnd, UINT nHitTest, UINT uMessage);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////

#endif
