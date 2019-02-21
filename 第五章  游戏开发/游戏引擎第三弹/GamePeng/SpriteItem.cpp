#include "StdAfx.h"
#include "SpriteItem.h"

CSpriteItem::CSpriteItem(void)
{
	m_szOffset.SetSize(0,0);

	m_ptMoveStart.SetPoint(0,0);
	m_ptMoveEnd.SetPoint(0,0);
}

CSpriteItem::~CSpriteItem(void)
{
}

void CSpriteItem::JumpToEnd( int nStopX/*=0*/,int nStopY/*=0*/ )
{
	//���ñ���
	m_ptMoveStart.x=nStopX;	
	m_ptMoveStart.y=nStopY;

	return ;
}

void CSpriteItem::SetMovePath( CPoint ptStart,CPoint ptEnd,int nSpeed/*=MOVE_SPEED_PIX*/ )
{
	//���ñ���
	m_ptMoveStart = ptStart;
	m_ptMoveEnd = ptEnd;

	m_nSpeed=nSpeed;

	SetOffset(nSpeed);
}

void CSpriteItem::SetMovePath( int nStartX,int nStartY,int nStopX,int nStopY,int nSpeed/*=MOVE_SPEED_PIX*/ )
{
	SetMovePath(CPoint(nStartX,nStartY),CPoint(nStopX,nStopY),nSpeed);
}

bool CSpriteItem::DrawRotateSprite(CD3DDevice*pD3DDevice, int x/*=0*/,int y/*=0*/,float rotateSpeed/*=1.5*/ )
{
	FLOAT fAngle = rotateSpeed*timeGetTime()/500.0f;

	SetRotation(GetWidth()/2.f,GetHeight()/2.f,fAngle);

	return DrawImage(pD3DDevice,x,y);
}

bool CSpriteItem::DrawMoveSprite(CD3DDevice*pD3DDevice)
{
	//ͼƬδ�ƶ���ָ��λ�� ����false
	if( abs(m_ptMoveStart.x-m_ptMoveEnd.x)>m_nSpeed||abs(m_ptMoveStart.y-m_ptMoveEnd.y)>m_nSpeed)
	{
		if(m_ptMoveStart.x<m_ptMoveEnd.x) m_ptMoveStart.x+=m_szOffset.cx;
		if(m_ptMoveStart.x>m_ptMoveEnd.x) m_ptMoveStart.x-=m_szOffset.cx;
		if(m_ptMoveStart.y<m_ptMoveEnd.y) m_ptMoveStart.y+=m_szOffset.cy;
		if(m_ptMoveStart.y>m_ptMoveEnd.y) m_ptMoveStart.y-=m_szOffset.cy;

		DrawImage(pD3DDevice,m_ptMoveStart.x,m_ptMoveStart.y);

		return false;
	}

	//��Ⱦ����λ��
	return DrawImage(pD3DDevice,m_ptMoveEnd.x,m_ptMoveEnd.y);
}

void CSpriteItem::SetOffset( int nSpeed )
{
	//����Ĭ��ֵ
	m_szOffset.cx=nSpeed;
	m_szOffset.cy=nSpeed;	

	//����ƫ����
	int xp=abs(m_ptMoveEnd.x-m_ptMoveStart.x);//xƫ����ֵ
	int yp=abs(m_ptMoveEnd.y-m_ptMoveStart.y);//yƫ����ֵ

	//��x��y�����ϵ��ƶ�����ͬʱ�����趨����
	if(xp!=yp&&xp!=0&&yp!=0)
	{
		//ASSERT(FALSE);
		int longRange=xp>yp?xp:yp;//������
		int shortRange=xp>yp?yp:xp;//�̾���

		int longTime=longRange/nSpeed;//�ƶ�����������ʱ��

		int xspeed=xp/longTime;//x�ٶ�
		int yspeed=yp/longTime;//y�ٶ�

		m_szOffset.cx=xspeed;
		m_szOffset.cy=yspeed;
	}
}
