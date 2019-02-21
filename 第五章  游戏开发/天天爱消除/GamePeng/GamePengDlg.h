// GamePengDlg.h : ͷ�ļ�
//

#pragma once
#include "ScoreView.h"
#include "GameLogic.h"
#include "SpriteItem.h"

#define  		ITEM_WIDTH			48			//���ӿ��
#define  		ITEM_HEIGHT			48			//���Ӹ߶�
	
#define  		TYPE_COUNT			7			//��������
#define			CHESS_DOWN_SPEED	8			//�����ٶ�

#define			GAME_TIME			60			//��Ϸ��ʱ�䣬��λ��

// CGamePengDlg �Ի���
class CGamePengDlg : public CGameFrameView,public CNumberString
{
	//����
protected:
	CD3DTexture							* m_pTextureBack;						//��������
	CD3DTexture							* m_pTextureBomb;						//��ը����
	CD3DTexture							* m_pTextureTime;						//ʱ������
	CD3DTexture							* m_pTextureTimeThumb;					//ʱ������
	CD3DTexture							* m_pTextureTimeNumber;					//ʱ������
	CD3DTexture							* m_pTextureGameScore;					//ʱ������
	CD3DTexture							* m_pTextureChoose;						//ʱ������

	CD3DSprite							m_SpriteChess[TYPE_COUNT];				//������Դ

protected:
	CVirtualButton						m_btStart;								//��ʼ��ť
	CScoreView							m_ScoreView;							//���ִ���

protected:
	CPoint								m_ptPosition;							//����λ��
	CGameLogic							m_GameLogic;							//��Ϸ�߼�
	INT									m_nGameScore;							//��Ϸ����
	bool								m_bGameStart;							//��Ϸ��ʼ
	bool								m_bGameEnd;								//��Ϸ����
	BYTE								m_ChessInfo[ROW_COUNT][COL_COUNT];		//������Ϣ
	CPoint								m_ptConnectChess[ALL_COUNT];			//�����鱣����ȥ���ӵ�λ��

	//��������
protected:
	bool								m_bResumeFinish;						//��ԭ������־
	bool								m_bDrawMoveFinish;						//�ƶ�����������־
	bool								m_bMoveChessFinish[ALL_COUNT];			//�����ƶ�������־

	BYTE								m_bActionCount;							//���������
	BYTE								m_bActionChessType[ALL_COUNT];			//���������
	CSpriteItem							m_SpriteActionChess[ALL_COUNT];			//�����ͼƬ

	bool								m_bResetEffect;							//����Ч��
	tagChooseInfo						m_tagChooseInfo;						//������ʶ
	
	//��ը����
protected:
	CLapseCount							m_LapseBomb;							//��ը��ʱ��
	INT									m_nBombFrame;							//��ը֡��
	int									m_nBombAction;							//��ը����	
	int									m_nBatterCount;							//������Ŀ				

	//��Ч����
protected:
	HSTREAM								m_SoundCombo[6];						//������Ч
	bool								m_bPlayBatter;							//�Ƿ񲥷�

	HSTREAM								m_SoundReady;							//׼����Ч
	HSTREAM								m_SoundGameOver;						//������Ч
	HSTREAM								m_SoundBack;							//��������

	//��ʱ��
protected:
	INT									m_nGameTime;
	CLapseCount							m_LapGameTime;

// ����
public:
	CGamePengDlg(CWnd* pParent = NULL);	// ��׼���캯��

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	//���溯��
private:
	//�����ؼ�
	virtual VOID RectifyControl(INT nWidth, INT nHeight);
	//��������
	virtual VOID CartoonMovie();
	//���ý���
	virtual VOID InitGameView(CD3DDevice * pD3DDevice, INT nWidth, INT nHeight);
	//�滭����
	virtual VOID DrawGameView(CD3DDevice * pD3DDevice, INT nWidth, INT nHeight);

	//��Ϣӳ��
protected:
	//���������Ϣ
	afx_msg void OnLButtonDown(UINT nFlags,CPoint point);
	//���������Ϣ
	afx_msg void OnLButtonUp(UINT nFlags,CPoint point);

	//���ܺ���
public:
	//��Ϸ��ʼ
	void OnStartGame();
	//��Ϸ����
	void OnEndGame();
	//���ñ�ը
	bool SetBombEffect(int x,int y);

	//�߼�����
public:
	//�������
	bool CheckConnect();
	//ֹͣ����
	bool ActToStop();
	//���հ�
	bool CheckBlank();
	//��ԭ����
	void ResumeAction();

	DECLARE_MESSAGE_MAP()
};
