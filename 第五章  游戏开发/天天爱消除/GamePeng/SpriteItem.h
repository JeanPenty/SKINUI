#pragma once

#define		MOVE_SPEED_PIX			5		//Ĭ���ƶ��ٶ�


class CSpriteItem : public CD3DSprite
{
	//��������
protected:
	int					m_nSpeed;							//�����ٶ�
	CSize				m_szOffset;
	
	CPoint				m_ptMoveStart;
	CPoint				m_ptMoveEnd;

public:
	CSpriteItem(void);
	~CSpriteItem(void);

	//��������
public:
	//����ͼƬλ�ã���������
	void JumpToEnd(int nStopX=0,int nStopY=0);
	//�����ƶ�·��
	void SetMovePath(CPoint ptStart,CPoint ptEnd,int nSpeed=MOVE_SPEED_PIX);
	//�����ƶ�·��
	void SetMovePath(int nStartX,int nStartY,int nStopX,int nStopY,int nSpeed=MOVE_SPEED_PIX);
	
	//�滭��ת����
	bool DrawRotateSprite(CD3DDevice*pD3DDevice,int x=0,int y=0,float rotateSpeed=1.5);
	//�滭�ƶ����� ����Ŀ��㷵��true,���򷵻�false
	bool DrawMoveSprite(CD3DDevice*pD3DDevice);

	inline CPoint GetPos(){ return m_ptMoveEnd; }

	//�ڲ�����
protected:
	//���㲽��
	void SetOffset(int nSpeed);
};
