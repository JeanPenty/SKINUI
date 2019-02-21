#pragma once

#define		MOVE_SPEED_PIX			5		//默认移动速度


class CSpriteItem : public CD3DSprite
{
	//动画参数
protected:
	int					m_nSpeed;							//象素速度
	CSize				m_szOffset;
	
	CPoint				m_ptMoveStart;
	CPoint				m_ptMoveEnd;

public:
	CSpriteItem(void);
	~CSpriteItem(void);

	//动画函数
public:
	//设置图片位置，跳过动画
	void JumpToEnd(int nStopX=0,int nStopY=0);
	//设置移动路径
	void SetMovePath(CPoint ptStart,CPoint ptEnd,int nSpeed=MOVE_SPEED_PIX);
	//设置移动路径
	void SetMovePath(int nStartX,int nStartY,int nStopX,int nStopY,int nSpeed=MOVE_SPEED_PIX);
	
	//绘画旋转动画
	bool DrawRotateSprite(CD3DDevice*pD3DDevice,int x=0,int y=0,float rotateSpeed=1.5);
	//绘画移动动画 到达目标点返回true,否则返回false
	bool DrawMoveSprite(CD3DDevice*pD3DDevice);

	inline CPoint GetPos(){ return m_ptMoveEnd; }

	//内部函数
protected:
	//计算步进
	void SetOffset(int nSpeed);
};
