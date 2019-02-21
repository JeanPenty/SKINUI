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
	//设置变量
	m_ptMoveStart.x=nStopX;	
	m_ptMoveStart.y=nStopY;

	return ;
}

void CSpriteItem::SetMovePath( CPoint ptStart,CPoint ptEnd,int nSpeed/*=MOVE_SPEED_PIX*/ )
{
	//设置变量
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
	//图片未移动到指定位置 返回false
	if( abs(m_ptMoveStart.x-m_ptMoveEnd.x)>m_nSpeed||abs(m_ptMoveStart.y-m_ptMoveEnd.y)>m_nSpeed)
	{
		if(m_ptMoveStart.x<m_ptMoveEnd.x) m_ptMoveStart.x+=m_szOffset.cx;
		if(m_ptMoveStart.x>m_ptMoveEnd.x) m_ptMoveStart.x-=m_szOffset.cx;
		if(m_ptMoveStart.y<m_ptMoveEnd.y) m_ptMoveStart.y+=m_szOffset.cy;
		if(m_ptMoveStart.y>m_ptMoveEnd.y) m_ptMoveStart.y-=m_szOffset.cy;

		DrawImage(pD3DDevice,m_ptMoveStart.x,m_ptMoveStart.y);

		return false;
	}

	//渲染最终位置
	return DrawImage(pD3DDevice,m_ptMoveEnd.x,m_ptMoveEnd.y);
}

void CSpriteItem::SetOffset( int nSpeed )
{
	//设置默认值
	m_szOffset.cx=nSpeed;
	m_szOffset.cy=nSpeed;	

	//计算偏移量
	int xp=abs(m_ptMoveEnd.x-m_ptMoveStart.x);//x偏移数值
	int yp=abs(m_ptMoveEnd.y-m_ptMoveStart.y);//y偏移数值

	//当x与y方向上的移动量不同时重新设定步进
	if(xp!=yp&&xp!=0&&yp!=0)
	{
		//ASSERT(FALSE);
		int longRange=xp>yp?xp:yp;//长距离
		int shortRange=xp>yp?yp:xp;//短距离

		int longTime=longRange/nSpeed;//移动长距离所需时间

		int xspeed=xp/longTime;//x速度
		int yspeed=yp/longTime;//y速度

		m_szOffset.cx=xspeed;
		m_szOffset.cy=yspeed;
	}
}
