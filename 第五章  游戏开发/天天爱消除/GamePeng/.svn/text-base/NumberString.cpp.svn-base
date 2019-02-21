#include "StdAfx.h"
#include "NumberString.h"

CNumberString::CNumberString(void)
{
}

CNumberString::~CNumberString(void)
{
}

//绘画数字
VOID CNumberString::DrawNumberString(CD3DDevice * pD3DDevice, CD3DTexture * pD3DTexture, LONG lNumber, INT nXPos, INT nYPos)
{
	if ( !Check_Image(pD3DTexture) ) return;

	//获取大小
	CSize SizeNumber;
	SizeNumber.SetSize(pD3DTexture->GetWidth()/10,pD3DTexture->GetHeight());

	//变量定义
	LONG lNumberCount=0;
	LONG lNumberTemp=lNumber;

	//计算数目
	do
	{
		lNumberCount++;
		lNumberTemp/=10L;
	} while (lNumberTemp>0);

	//位置定义
	INT nYDrawPos=nYPos-SizeNumber.cy/2;
	INT nXDrawPos=nXPos+lNumberCount*SizeNumber.cx/2-SizeNumber.cx;

	//绘画桌号
	for (LONG i=0;i<lNumberCount;i++)
	{
		//绘画号码
		LONG lCellNumber=lNumber%10L;
		pD3DTexture->DrawImage(pD3DDevice,nXDrawPos,nYDrawPos,SizeNumber.cx,SizeNumber.cy,lCellNumber*SizeNumber.cx,0);

		//设置变量
		lNumber/=10;
		nXDrawPos-=SizeNumber.cx;
	};

	return;
}