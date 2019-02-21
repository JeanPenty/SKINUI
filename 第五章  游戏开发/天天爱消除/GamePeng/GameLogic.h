#ifndef GAME_LOGIC_HEAD_FILE
#define GAME_LOGIC_HEAD_FILE

#pragma once

#define  ROW_COUNT			9
#define  COL_COUNT			9

#define  ALL_COUNT			(ROW_COUNT*COL_COUNT)

#define  INVALID_BYTE		0xFF

struct tagChooseInfo
{
	bool		bChoosed;			//�Ƿ�ѡ��
	CPoint		ptDownPoint;		//��갴�µĵ�
	CPoint		ptDownIndex;		//��갴�µĵ�����
	CPoint		ptUpIndex;			//��굯��ĵ�����
};

//////////////////////////////////////////////////////////////////////////

//��Ϸ�߼���
class CGameLogic
{
	//��������
public:
	//���캯��
	CGameLogic();
	//��������
	virtual ~CGameLogic();

	//���ܺ���
public:
	//����ƶ�
	bool IsValidMove(CPoint start,CPoint stop,BYTE ChessInfo[ROW_COUNT][COL_COUNT]);
	//�����ȥ(����һ����ȥ��λ�õ�����)
	void CheckConnect(BYTE ChessInfo[ROW_COUNT][COL_COUNT],CPoint ConnectChessPos[ALL_COUNT]);
	//ͳ����ȥ����
	void CheckConnectScore(BYTE ChessInfo[ROW_COUNT][COL_COUNT],CPoint ConnectChessPos[ALL_COUNT],int& nGameScore);
};

//////////////////////////////////////////////////////////////////////////

#endif